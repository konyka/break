# Runtime / IoStoreHttpClient

- module root: `Source/Runtime/Experimental/IoStore/HttpClient`
- headers: 14; symbols: 1419
- symbol kinds: class=44, enum=24, enumerator=104, function=487, macro=22, member=259, namespace=63, prototype=356, struct=34, typedef=13, union=6, variable=7
- PrivateDependencyModuleNames: OpenSSL, nghttp2
- PublicDependencyModuleNames: Core, TraceLog

### `Source/Runtime/Experimental/IoStore/HttpClient/Internal/IO/Http/Client.h` (Internal)


#### enum `UE::IoStore::HTTP::EHttpVersion`  
`enum class EHttpVersion : uint8`  
_L23-28_
- L25 _public enumerator_ `Default`
- L26 _public enumerator_ `One` — 1.1 in actuality
- L27 _public enumerator_ `Two`

#### enum `UE::IoStore::HTTP::EMimeType`  
`enum class EMimeType`  
_L31-42_
- L33 _public enumerator_ `Unknown = 0`
- L34 _public enumerator_ `Text`
- L35 _public enumerator_ `Binary`
- L36 _public enumerator_ `Json`
- L37 _public enumerator_ `Xml`
- L38 _public enumerator_ `CbObject`
- L39 _public enumerator_ `CbPackage`
- L40 _public enumerator_ `CompressedBuffer`
- L41 _public enumerator_ `Count`

#### enum `UE::IoStore::HTTP::EStatusCodeClass`  
`enum class EStatusCodeClass`  
_L45-53_
- L47 _public enumerator_ `Informational`
- L48 _public enumerator_ `Successful`
- L49 _public enumerator_ `Redirection`
- L50 _public enumerator_ `ClientError`
- L51 _public enumerator_ `ServerError`
- L52 _public enumerator_ `Unknown`

#### enum `UE::IoStore::HTTP::EContentStatus`  
`enum class EContentStatus`  
_L56-61_
- L58 _public enumerator_ `NoContent` — response has no content; head, 100-class, 204, 304, etc.
- L59 _public enumerator_ `KnownSize` — "content-length" present
- L60 _public enumerator_ `UnknownSize` — no "content-length" field, streamed transfer (e.g. h1's chunked)

#### class `UE::IoStore::HTTP::FCertRoots`  
`class FCertRoots`  
_L70-91_
- L73 _public prototype_ `FCertRoots() = default;`
- L74 _public prototype_ `~FCertRoots();`
- L75 _public prototype_ `FCertRoots(FMemoryView PemData);`
- L76 _public function_ `FCertRoots(FCertRoots&& Rhs)`
- L77 _public function_ `FCertRoots& operator = (FCertRoots&& Rhs)`
- L78 _public function_ `bool IsValid() const`
- L79 _public prototype_ `int32 Num() const;`
- L80 _public prototype_ `static void SetDefault(FCertRoots&& CertRoots);`
- L81 _public prototype_ `static FCertRootsRef NoTls();`
- L82 _public prototype_ `static FCertRootsRef Default();`
- L83 _public prototype_ `static FCertRootsRef Explicit(const FCertRoots& CertRoots);`
- L86 _private member_ `UPTRINT Handle = 0;`
- L89 _private prototype_ `FCertRoots(const FCertRoots&) = delete;`
- L90 _private prototype_ `FCertRoots& operator = (const FCertRoots&) = delete;`

#### class `UE::IoStore::HTTP::FConnectionPool`  
`class FConnectionPool`  
_L94-132_
- L114 _public prototype_ `FConnectionPool() = default;`
- L115 _public prototype_ `FConnectionPool(const FParams& Params);`
- L116 _public prototype_ `~FConnectionPool();`
- L117 _public function_ `FConnectionPool(FConnectionPool&& Rhs)`
- L118 _public function_ `FConnectionPool& operator = (FConnectionPool&& Rhs)`
- L119 _public prototype_ `bool Resolve();`
- L120 _public prototype_ `uint32 GetIps(uint32* Out, uint32 Count) const;`
- L121 _public prototype_ `void Describe(FAnsiStringBuilderBase&) const;`
- L123 _public prototype_ `static bool IsValidHostUrl(FAnsiStringView Url);`
- L127 _private member_ `class FHost* Ptr = nullptr;`
- L130 _private prototype_ `FConnectionPool(const FConnectionPool&) = delete;`
- L131 _private prototype_ `FConnectionPool& operator = (const FConnectionPool&) = delete;`

#### struct `UE::IoStore::HTTP::FConnectionPool::FParams`  
`struct FParams`  
_L97-112_
- L99 _public prototype_ `int32 SetHostFromUrl(FAnsiStringView Url);`
- L100 _public member_ `FAnsiStringView HostName;`
- L101 _public member_ `FCertRootsRef VerifyCert = FCertRoots::NoTls();`
- L102 _public member_ `int32 SendBufSize = -1;`
- L103 _public member_ `int32 RecvBufSize = -1;`
- L104 _public member_ `uint32 Port = 0;`
- L105 _public member_ `uint16 ConnectionCount = 1;`
- L106 _public member_ `EHttpVersion HttpVersion = EHttpVersion::One;`
- L107 _public member_ `uint8 MaxInflight = 1;`

#### class `UE::IoStore::HTTP::FRequest`  
`class FRequest`  
_L135-154_
- L138 _public prototype_ `~FRequest();`
- L139 _public prototype_ `FRequest(FRequest&& Rhs);`
- L140 _public prototype_ `FRequest(const FRequest&) = delete;`
- L141 _public prototype_ `FRequest& operator = (FRequest&& Rhs);`
- L142 _public prototype_ `FRequest& operator = (const FRequest&) = delete;`
- L143 _public function_ `bool IsValid() const`
- L144 _public prototype_ `void Accept(EMimeType MimeType);`
- L145 _public prototype_ `void Accept(FAnsiStringView MimeType);`
- L146 _public prototype_ `void Header(FAnsiStringView Key, FAnsiStringView Value);`
- L147 _public prototype_ `void Content(const void* Data, SIZE_T Size, EMimeType MimeType);`
- L148 _public prototype_ `void Content(const void* Data, SIZE_T Size, FAnsiStringView MimeType);`
- L152 _private prototype_ `FRequest() = default;`
- L153 _private member_ `FActivityNode* Ptr = nullptr;`

#### class `UE::IoStore::HTTP::FResponse`  
`class FResponse`  
_L157-179_
- L160 _public typedef_ `using FHeaderSink = TFunction<bool (FAnsiStringView, FAnsiStringView)>;`
- L162 _public prototype_ `EStatusCodeClass GetStatus() const;`
- L163 _public prototype_ `uint32 GetStatusCode() const;`
- L164 _public prototype_ `FAnsiStringView GetStatusMessage() const;`
- L165 _public prototype_ `EContentStatus GetContentStatus() const;`
- L166 _public prototype_ `int64 GetContentLength() const;`
- L167 _public prototype_ `EMimeType GetContentType() const;`
- L168 _public prototype_ `void GetContentType(FAnsiStringView& Out) const;`
- L169 _public prototype_ `FAnsiStringView GetHeader(FAnsiStringView Name) const;`
- L170 _public prototype_ `void ReadHeaders(FHeaderSink Sink) const;`
- L171 _public prototype_ `void SetDestination(FIoBuffer* Buffer);`
- L174 _private prototype_ `FResponse() = delete;`
- L175 _private prototype_ `FResponse(const FResponse&) = delete;`
- L176 _private prototype_ `FResponse(FResponse&&) = delete;`
- L177 _private prototype_ `FResponse& operator = (const FResponse&) = delete;`
- L178 _private prototype_ `FResponse& operator = (FResponse&&) = delete;`

#### class `UE::IoStore::HTTP::FTicketPerf`  
`class FTicketPerf`  
_L182-196_
- L195 _public prototype_ `FSample GetSample() const;`
- L199 _function_ `inline FTicketPerf::FSample FTicketPerf::GetSample() const`

#### struct `UE::IoStore::HTTP::FTicketPerf::FSample`  
`struct FSample`  
_L185-193_
- L187 _public member_ `uint16 SendMs;`
- L188 _public member_ `uint16 WaitMs;`
- L189 _public member_ `uint16 RecvMs;`
- L190 _public member_ `uint16 RecvKiBps;`
- L191 _public function_ `uint32 GetTotalMs() const`
- L192 _public function_ `uint32 GetSizeEstKiB() const`

#### class `UE::IoStore::HTTP::FTicketStatus`  
`class FTicketStatus`  
_L203-231_
- L214 _public prototype_ `EId GetId() const;`
- L215 _public prototype_ `UPTRINT GetParam() const;`
- L216 _public prototype_ `FTicket GetTicket() const;`
- L217 _public prototype_ `uint32 GetIndex() const;`
- L218 _public prototype_ `bool IsComplete() const;`
- L219 _public prototype_ `FResponse& GetResponse() const;` — if GetId() == EId::Response
- L220 _public prototype_ `const FIoBuffer& GetContent() const;` — if GetId() == EId::Content
- L221 _public prototype_ `uint32 GetContentLength() const;` — |
- L222 _public prototype_ `const FTicketPerf& GetPerf() const;` — _|_
- L223 _public prototype_ `FError GetError() const;` — if GetId() == EId::Error
- L226 _private prototype_ `FTicketStatus() = delete;`
- L227 _private prototype_ `FTicketStatus(const FTicketStatus&) = delete;`
- L228 _private prototype_ `FTicketStatus(FTicketStatus&&) = delete;`
- L229 _private prototype_ `FTicketStatus& operator = (const FTicketStatus&) = delete;`
- L230 _private prototype_ `FTicketStatus& operator = (FTicketStatus&&) = delete;`

#### enum `UE::IoStore::HTTP::FTicketStatus::EId`  
`enum class EId : uint8`  
_L206-206_
- L206 _public enumerator_ `enum class EId : uint8 { Response, Content, Cancelled, Error }; struct FError { const char* Reason; uint32 Code; };`
- L206 _public enumerator_ `enum class EId : uint8 { Response, Content, Cancelled, Error }; struct FError { const char* Reason; uint32 Code; };`
- L206 _public enumerator_ `enum class EId : uint8 { Response, Content, Cancelled, Error }; struct FError { const char* Reason; uint32 Code; };`
- L206 _public enumerator_ `enum class EId : uint8 { Response, Content, Cancelled, Error }; struct FError { const char* Reason; uint32 Code; };`

#### struct `UE::IoStore::HTTP::FTicketStatus::FError`  
`struct FError`  
_L208-212_
- L210 _public member_ `const char* Reason;`
- L211 _public member_ `uint32 Code;`

#### class `UE::IoStore::HTTP::FLoopPerf`  
`class FLoopPerf`  
_L236-253_
- L241 _public prototype_ `uint32 GetTotalRecvKiB() const;`
- L242 _public prototype_ `uint32 GetRecvKiBpsCount() const;`
- L243 _public prototype_ `uint32 GetRecvKiBps(uint32 Index) const;`
- L244 _public prototype_ `void GetRecvKiBps(uint32 (&Out)[RecvBucketCount]) const;`
- L245 _public prototype_ `uint32 GetRecvKiBps() const;`
- L246 _public prototype_ `uint32 GetTimeToFirstByteMs() const;`
- L250 _private member_ `uint64 TtfbSamples;`
- L251 _private member_ `uint32 RecvKiB;`
- L252 _private member_ `uint16 RecvKiBps[RecvBucketCount];`

#### enum `UE::IoStore::HTTP::FLoopPerf::(anonymous)`  
`enum`  
_L239-239_

#### class `UE::IoStore::HTTP::FEventLoop`  
`class FEventLoop`  
_L256-297_
- L261 _public member_ `static const uint32 MaxActiveTickets = 64;`
- L273 _public function_ `template <typename... T> [[nodiscard]] FRequest Get(T&&... t)`
- L274 _public function_ `template <typename... T> [[nodiscard]] FRequest Get(T&&... t)`
- L276 _public prototype_ `FEventLoop();`
- L277 _public prototype_ `~FEventLoop();`
- L278 _public prototype_ `void SamplePerf(FLoopPerf& Perf) const;`
- L279 _public prototype_ `uint32 Tick(int32 PollTimeoutMs=0);`
- L280 _public prototype_ `void Throttle(uint32 KiBPerSec);`
- L281 _public prototype_ `void SetFailTimeout(int32 TimeoutMs);`
- L282 _public prototype_ `bool IsIdle() const;`
- L283 _public prototype_ `void Cancel(FTicket Ticket);`
- L284 _public prototype_ `[[nodiscard]] FRequest Request(FAnsiStringView Method, FAnsiStringView Url, const FRequestParams* Params=nullptr);`
- L285 _public prototype_ `[[nodiscard]] FRequest Request(FAnsiStringView Method, FAnsiStringView Path, FConnectionPool& Pool, const FRequestParams* Params=nullptr);`
- L286 _public prototype_ `FTicket Send(FRequest&& Request, FTicketSink Sink, UPTRINT SinkParam=0);`
- L289 _private prototype_ `bool Redirect(const FTicketStatus& Status, FTicketSink& OuterSink);`
- L290 _private member_ `FImpl* Impl;`
- L293 _private prototype_ `FEventLoop(const FEventLoop&) = delete;`
- L294 _private prototype_ `FEventLoop(FEventLoop&&) = delete;`
- L295 _private prototype_ `FEventLoop& operator = (const FEventLoop&) = delete;`
- L296 _private prototype_ `FEventLoop& operator = (FEventLoop&&) = delete;`

#### struct `UE::IoStore::HTTP::FEventLoop::FRequestParams`  
`struct FRequestParams`  
_L263-271_
- L265 _public member_ `FCertRootsRef VerifyCert = {};`
- L266 _public member_ `uint32 ContentSizeEst = 0;`
- L267 _public member_ `uint16 BufferSize = 256;`
- L268 _public member_ `bool bAutoRedirect = false;`
- L269 _public member_ `bool bAllowChunked = true;`
- L270 _public member_ `EHttpVersion HttpVersion = EHttpVersion::Default;`

#### Free symbols / members of external scopes

- L11 _macro_ `# define IAS_HTTP_WITH_PERF 1`
- L14 _macro_ `#define UE_API IOSTOREHTTPCLIENT_API`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace IoStore` (scope `UE`)
- L19 _namespace_ `namespace HTTP` (scope `UE::IoStore`)
- L64 _typedef_ `using FCertRootsRef = UPTRINT;` (scope `UE::IoStore::HTTP`)
- L65 _typedef_ `using FTicket = uint64;` (scope `UE::IoStore::HTTP`)
- L233 _typedef_ `using FTicketSink = TFunction<void (const FTicketStatus&)>;` (scope `UE::IoStore::HTTP`)
- L239 _enumerator_ `enum { RecvBucketCount = 8 }; UE_API uint32 GetTotalRecvKiB() const; UE_API uint32 GetRecvKiBpsCount() const; UE_API uint32 GetRecvKiBps(uint32 Index) const; UE_API void GetRecvKiBps(uint32 (&Out)[RecvBucketCount]) const; UE_API uint32 GetRecvKiBps() const; UE_API uint32 GetTimeToFirstByteMs() const;` (scope `UE::IoStore::HTTP::FLoopPerf::__anonf6337a9f0103`)

### `Source/Runtime/Experimental/IoStore/HttpClient/Internal/IO/Http/LaneTrace.h` (Internal)


#### struct `trace::FLaneTraceSpec`  
`struct FLaneTraceSpec`  
_L35-41_
- L37 _public member_ `FAnsiStringView Name;`
- L38 _public member_ `FAnsiStringView Group = "La`
- L39 _public member_ `const void* Channel;`
- L40 _public member_ `int32 Weight = 100;`

#### struct `trace::FLanePostcode`  
`struct FLanePostcode`  
_L55-60_
- L57 _public function_ `FLanePostcode(const void* In) : Value(UPTRINT(In))`
- L58 _public function_ `FLanePostcode(UPTRINT In) : Value(In)`
- L59 _public member_ `UPTRINT Value;`

#### class `trace::FLaneTraceScope`  
`class FLaneTraceScope`  
_L77-91_
- L80 _public prototype_ `FLaneTraceScope(FLaneTrace* InLane, uint32 Scope);`
- L81 _public prototype_ `FLaneTraceScope() = default;`
- L82 _public prototype_ `~FLaneTraceScope();`
- L83 _public prototype_ `FLaneTraceScope(FLaneTraceScope&& Rhs);`
- L84 _public prototype_ `FLaneTraceScope& operator = (FLaneTraceScope&& Rhs);`
- L85 _public prototype_ `void Change(uint32 Scope) const;`
- L88 _private prototype_ `FLaneTraceScope(const FLaneTraceScope&) = delete;`
- L89 _private prototype_ `FLaneTraceScope& operator = (const FLaneTraceScope&) = delete;`
- L90 _private member_ `FLaneTrace* Lane = nullptr;`
- L94 _function_ `inline FLaneTraceScope::FLaneTraceScope(FLaneTrace* InLane, uint32 Scope) : Lane(InLane)`
- L101 _function_ `inline FLaneTraceScope::~FLaneTraceScope()`
- L110 _function_ `inline FLaneTraceScope::FLaneTraceScope(FLaneTraceScope&& Rhs)`
- L116 _function_ `inline FLaneTraceScope& FLaneTraceScope::operator = (FLaneTraceScope&& Rhs)`
- L123 _function_ `inline void FLaneTraceScope::Change(uint32 Scope) const`
- L133 _public function_ `FLaneTraceScope(...)`
- L134 _public function_ `void Change(uint32) const`

#### class `trace::FLaneTraceScope`  
`class FLaneTraceScope`  
_L130-135_
- L80 _public prototype_ `FLaneTraceScope(FLaneTrace* InLane, uint32 Scope);`
- L81 _public prototype_ `FLaneTraceScope() = default;`
- L82 _public prototype_ `~FLaneTraceScope();`
- L83 _public prototype_ `FLaneTraceScope(FLaneTraceScope&& Rhs);`
- L84 _public prototype_ `FLaneTraceScope& operator = (FLaneTraceScope&& Rhs);`
- L85 _public prototype_ `void Change(uint32 Scope) const;`
- L88 _private prototype_ `FLaneTraceScope(const FLaneTraceScope&) = delete;`
- L89 _private prototype_ `FLaneTraceScope& operator = (const FLaneTraceScope&) = delete;`
- L90 _private member_ `FLaneTrace* Lane = nullptr;`
- L94 _function_ `inline FLaneTraceScope::FLaneTraceScope(FLaneTrace* InLane, uint32 Scope) : Lane(InLane)`
- L101 _function_ `inline FLaneTraceScope::~FLaneTraceScope()`
- L110 _function_ `inline FLaneTraceScope::FLaneTraceScope(FLaneTraceScope&& Rhs)`
- L116 _function_ `inline FLaneTraceScope& FLaneTraceScope::operator = (FLaneTraceScope&& Rhs)`
- L123 _function_ `inline void FLaneTraceScope::Change(uint32 Scope) const`
- L133 _public function_ `FLaneTraceScope(...)`
- L134 _public function_ `void Change(uint32) const`

#### Free symbols / members of external scopes

- L11 _macro_ `# define UE_LANETRACE_ENABLED 2`
- L12 _macro_ `# define IOSTOREHTTPCLIENT_API`
- L17 _macro_ `# define UE_LANETRACE_ENABLED CPUPROFILERTRACE_ENABLED && !UE_BUILD_SHIPPING`
- L21 _macro_ `# define LANETRACE_OFF_IMPL(...)`
- L22 _macro_ `# define UE_API IOSTOREHTTPCLIENT_API`
- L24 _macro_ `# define LANETRACE_OFF_IMPL(...) { return __VA_ARGS__ ; }`
- L25 _macro_ `# define UE_API inline`
- L31 _namespace_ `namespace trace`
- L44 _prototype_ `FLaneTrace* LaneTrace_New(const FLaneTraceSpec& Spec) LANETRACE_OFF_IMPL(nullptr);` (scope `trace`)
- L45 _prototype_ `void LaneTrace_Delete(FLaneTrace* Lane) LANETRACE_OFF_IMPL();` (scope `trace`)
- L46 _prototype_ `uint32 LaneTrace_NewScope(const FAnsiStringView& Name) LANETRACE_OFF_IMPL(1);` (scope `trace`)
- L47 _prototype_ `void LaneTrace_Enter(FLaneTrace* Lane, uint32 ScopeId) LANETRACE_OFF_IMPL();` (scope `trace`)
- L48 _prototype_ `void LaneTrace_Change(FLaneTrace* Lane, uint32 ScopeId) LANETRACE_OFF_IMPL();` (scope `trace`)
- L49 _prototype_ `void LaneTrace_Leave(FLaneTrace* Lane) LANETRACE_OFF_IMPL();` (scope `trace`)
- L50 _prototype_ `void LaneTrace_LeaveAll(FLaneTrace* Lane) LANETRACE_OFF_IMPL();` (scope `trace`)
- L63 _prototype_ `FLaneEstate* LaneEstate_New(const FLaneTraceSpec& Spec) LANETRACE_OFF_IMPL(nullptr);` (scope `trace`)
- L64 _prototype_ `void LaneEstate_Delete(FLaneEstate* Estate) LANETRACE_OFF_IMPL();` (scope `trace`)
- L65 _prototype_ `FLaneTrace* LaneEstate_Build(FLaneEstate* Estate, FLanePostcode Postcode) LANETRACE_OFF_IMPL(nullptr);` (scope `trace`)
- L66 _prototype_ `FLaneTrace* LaneEstate_Lookup(FLaneEstate* Estate, FLanePostcode Postcode) LANETRACE_OFF_IMPL(nullptr);` (scope `trace`)
- L67 _prototype_ `void LaneEstate_Demolish(FLaneEstate* Estate, FLanePostcode Postcode)LANETRACE_OFF_IMPL();` (scope `trace`)

### `Source/Runtime/Experimental/IoStore/HttpClient/Private/Activity.inl` (Private)


#### class `UE::IoStore::HTTP::FStopwatch`  
`class FStopwatch`  
_L11-24_
- L14 _public prototype_ `uint64 GetInterval(uint32 i) const;`
- L15 _public function_ `void SendStart()`
- L16 _public function_ `void SendEnd()`
- L17 _public function_ `void RecvStart()`
- L18 _public function_ `void RecvEnd()`
- L21 _private prototype_ `void Impl(uint32 Index);`
- L22 _private member_ `uint64 Samples[4] = {};`
- L23 _private member_ `uint32 Counts[2] = {};`
- L27 _function_ `uint64 FStopwatch::GetInterval(uint32 i) const`
- L37 _function_ `void FStopwatch::Impl(uint32 Index)`

#### struct `UE::IoStore::HTTP::FActivity`  
`struct FActivity`  
_L63-169_
- L88 _public prototype_ `FActivity(const FParams& Params);`
- L89 _public prototype_ `void AddHeader(FAnsiStringView Key, FAnsiStringView Value);`
- L90 _public prototype_ `FOutcome Tick(FHttpPeer& Peer, int32* MaxRecvSize=nullptr);`
- L91 _public prototype_ `void SetSink(FTicketSink&& InSink, UPTRINT Param);`
- L92 _public prototype_ `void SetDestination(FIoBuffer* InDest);`
- L93 _public prototype_ `bool CancelTransaction(FHttpPeer& Peer);`
- L94 _public prototype_ `void Cancel();`
- L95 _public prototype_ `void Done();`
- L96 _public prototype_ `void Fail(const FOutcome& Outcome);`
- L97 _public prototype_ `EStage GetStage() const;`
- L98 _public prototype_ `FTransactId GetTransactId() const;`
- L99 _public prototype_ `const FTransactRef& GetTransaction() const;`
- L100 _public prototype_ `FAnsiStringView GetMethod() const;`
- L101 _public prototype_ `FAnsiStringView GetPath() const;`
- L102 _public prototype_ `FHost* GetHost() const;`
- L103 _public prototype_ `void EnumerateHeaders(FResponse::FHeaderSink HeaderSink) const;`
- L104 _public prototype_ `UPTRINT GetSinkParam() const;`
- L105 _public prototype_ `FIoBuffer& GetContent() const;`
- L106 _public prototype_ `uint32 GetRemainingKiB() const;`
- L107 _public prototype_ `FOutcome GetError() const;`
- L110 _public prototype_ `const FStopwatch& GetStopwatch() const;`
- L128 _private prototype_ `void CallSink();`
- L129 _private prototype_ `void ChangeState(EState InState);`
- L130 _private prototype_ `FOutcome Transact(FHttpPeer& Peer);`
- L131 _private prototype_ `FOutcome Send(FHttpPeer& Peer);`
- L132 _private prototype_ `FOutcome RecvMessage(FHttpPeer& Peer);`
- L133 _private prototype_ `FOutcome RecvContent(FHttpPeer& Peer, int32& MaxRecvSize);`
- L134 _private prototype_ `FOutcome RecvStream(FHttpPeer& Peer, int32& MaxRecvSize);`
- L135 _private prototype_ `FOutcome Recv(FHttpPeer& Peer, int32& MaxRecvSize);`
- L137 _private member_ `EState State = EState::Build;`
- L138 _private member_ `uint8 bAllowChunked : 1;`
- L139 _private member_ `uint8 _Unused : 3;`
- L140 _private member_ `uint8 LengthScore : 4;`
- L141 _private member_ `uint8 MethodOffset;`
- L142 _private member_ `uint8 PathOffset;`
- L143 _private member_ `uint16 PathLength;`
- L144 _private member_ `uint16 HeaderCount = 0;`
- L145 _private member_ `FTransactId TransactId = 0;`
- L147 _private member_ `FStopwatch Stopwatch;`
- L154 _private member_ `UPTRINT SinkParam;`
- L155 _private member_ `FTicketSink Sink;`
- L156 _private member_ `FTransactRef Transaction;`
- L157 _private member_ `FBuffer Buffer;`
- L172 _function_ `FActivity::FActivity(const FParams& Params) : bAllowChunked(Params.bAllowChunked) , Host(Params.Host) , Buffer(Params.Buffer, Params.BufferSize)`
- L205 _function_ `void FActivity::AddHeader(FAnsiStringView Key, FAnsiStringView Value)`
- L226 _function_ `void FActivity::SetSink(FTicketSink&& InSink, UPTRINT Param)`
- L233 _function_ `void FActivity::SetDestination(FIoBuffer* InDest)`
- L239 _function_ `bool FActivity::CancelTransaction(FHttpPeer& Peer)`
- L251 _function_ `void FActivity::Cancel()`
- L263 _function_ `void FActivity::Done()`
- L271 _function_ `void FActivity::Fail(const FOutcome& Outcome)`
- L286 _function_ `void FActivity::ChangeState(EState InState)`
- L295 _function_ `void FActivity::CallSink()`
- L306 _function_ `FActivity::EStage FActivity::GetStage() const`
- L325 _function_ `FTransactId FActivity::GetTransactId() const`
- L332 _function_ `const FTransactRef& FActivity::GetTransaction() const`
- L340 _function_ `FAnsiStringView FActivity::GetMethod() const`
- L346 _function_ `FAnsiStringView FActivity::GetPath() const`
- L352 _function_ `FHost* FActivity::GetHost() const`
- L359 _function_ `void FActivity::EnumerateHeaders(FResponse::FHeaderSink HeaderSink) const`
- L376 _function_ `UPTRINT FActivity::GetSinkParam() const`
- L382 _function_ `FIoBuffer& FActivity::GetContent() const`
- L389 _function_ `uint32 FActivity::GetRemainingKiB() const`
- L397 _function_ `FOutcome FActivity::GetError() const`
- L407 _function_ `const FStopwatch& FActivity::GetStopwatch() const`
- L414 _function_ `FOutcome FActivity::Transact(FHttpPeer& Peer)`
- L438 _function_ `FOutcome FActivity::Send(FHttpPeer& Peer)`
- L469 _function_ `FOutcome FActivity::RecvMessage(FHttpPeer& Peer)`
- L559 _function_ `FOutcome FActivity::RecvContent(FHttpPeer& Peer, int32& MaxRecvSize)`
- L591 _function_ `FOutcome FActivity::RecvStream(FHttpPeer& Peer, int32& MaxRecvSize)`
- L640 _function_ `FOutcome FActivity::Recv(FHttpPeer& Peer, int32& MaxRecvSize)`
- L653 _function_ `FOutcome FActivity::Tick(FHttpPeer& Peer, int32* MaxRecvSize)`

#### struct `UE::IoStore::HTTP::FActivity::FParams`  
`struct FParams`  
_L65-75_
- L67 _public member_ `FAnsiStringView Method;`
- L68 _public member_ `FAnsiStringView Path;`
- L69 _public member_ `FHost* Host = nullptr;`
- L70 _public member_ `char* Buffer = nullptr;`
- L71 _public member_ `uint32 ContentSizeEst = 0;`
- L72 _public member_ `uint16 BufferSize = 0;`
- L73 _public member_ `bool bIsKeepAlive = false;`
- L74 _public member_ `bool bAllowChunked = true;`

#### enum `UE::IoStore::HTTP::FActivity::EStage`  
`enum class EStage : int32`  
_L77-86_
- L79 _public enumerator_ `Build = -1`
- L80 _public enumerator_ `Request = -2`
- L81 _public enumerator_ `Response = -3`
- L82 _public enumerator_ `Content = -4`
- L83 _public enumerator_ `Done = -5`
- L84 _public enumerator_ `Cancelled = -6`
- L85 _public enumerator_ `Failed = -7`

#### enum `UE::IoStore::HTTP::FActivity::EState`  
`enum class EState : uint8`  
_L114-126_
- L116 _public enumerator_ `Build`
- L117 _public enumerator_ `Send`
- L118 _public enumerator_ `RecvMessage`
- L119 _public enumerator_ `RecvStream`
- L120 _public enumerator_ `RecvContent`
- L121 _public enumerator_ `RecvDone`
- L122 _public enumerator_ `Completed`
- L123 _public enumerator_ `Cancelled`
- L124 _public enumerator_ `Failed`
- L125 _public enumerator_ `_Num`

#### union `UE::IoStore::HTTP::FActivity::(anonymous)`  
`union`  
_L149-153_

#### struct `UE::IoStore::HTTP::FActivity::FHeaderRecord`  
`struct FHeaderRecord`  
_L159-164_
- L161 _public member_ `int16 Key;`
- L162 _public member_ `uint16 ValueLength;`
- L163 _public member_ `char Data[];`

#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace IoStore` (scope `UE`)
- L5 _namespace_ `namespace HTTP` (scope `UE::IoStore`)
- L51 _prototype_ `static void Trace(const struct FActivity*, ETrace, uint32);` (scope `UE::IoStore::HTTP`)
- L53 _variable_ `static FLaneEstate* GActivityTraceEstate = LaneEstate_New({ .Name = "Iax/Activity", .Group = "Iax", .Channel = GetIaxTraceChannel(), .Weight = 11, });` (scope `UE::IoStore::HTTP`)
- L150 _member_ `FHost* Host;` (scope `UE::IoStore::HTTP::FActivity::__anonbef6d650010a`)
- L151 _member_ `FIoBuffer* Dest;` (scope `UE::IoStore::HTTP::FActivity::__anonbef6d650010a`)
- L152 _member_ `UPTRINT Error;` (scope `UE::IoStore::HTTP::FActivity::__anonbef6d650010a`)
- L184 _function_ `` (scope `UE::IoStore::HTTP::FActivity::FActivity`)
- L427 _function_ `` (scope `UE::IoStore::HTTP::FActivity::Transact`)
- L677 _function_ `static void Trace(const struct FActivity* Activity, ETrace Action, uint32 Param)` (scope `UE::IoStore::HTTP`)

### `Source/Runtime/Experimental/IoStore/HttpClient/Private/Api.inl` (Private)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace IoStore` (scope `UE`)
- L5 _namespace_ `namespace HTTP` (scope `UE::IoStore`)
- L11 _function_ `static FAnsiStringView MimeTypeToString(EMimeType MimeType)` (scope `UE::IoStore::HTTP`)
- L27 _function_ `FRequest::FRequest(FRequest&& Rhs)` (scope `UE::IoStore::HTTP::FRequest`)
- L33 _function_ `FRequest& FRequest::operator = (FRequest&& Rhs)` (scope `UE::IoStore::HTTP::FRequest`)
- L40 _function_ `FRequest::~FRequest()` (scope `UE::IoStore::HTTP::FRequest`)
- L51 _function_ `void FRequest::Accept(EMimeType MimeType)` (scope `UE::IoStore::HTTP::FRequest`)
- L58 _function_ `void FRequest::Accept(FAnsiStringView MimeType)` (scope `UE::IoStore::HTTP::FRequest`)
- L67 _function_ `void FRequest::Header(FAnsiStringView Key, FAnsiStringView Value)` (scope `UE::IoStore::HTTP::FRequest`)
- L77 _function_ `EStatusCodeClass FResponse::GetStatus() const` (scope `UE::IoStore::HTTP::FResponse`)
- L89 _function_ `uint32 FResponse::GetStatusCode() const` (scope `UE::IoStore::HTTP::FResponse`)
- L96 _function_ `FAnsiStringView FResponse::GetStatusMessage() const` (scope `UE::IoStore::HTTP::FResponse`)
- L103 _function_ `EContentStatus FResponse::GetContentStatus() const` (scope `UE::IoStore::HTTP::FResponse`)
- L114 _function_ `int64 FResponse::GetContentLength() const` (scope `UE::IoStore::HTTP::FResponse`)
- L121 _function_ `EMimeType FResponse::GetContentType() const` (scope `UE::IoStore::HTTP::FResponse`)
- L138 _function_ `void FResponse::GetContentType(FAnsiStringView& Out) const` (scope `UE::IoStore::HTTP::FResponse`)
- L149 _function_ `FAnsiStringView FResponse::GetHeader(FAnsiStringView Name) const` (scope `UE::IoStore::HTTP::FResponse`)
- L153 _function_ `` (scope `UE::IoStore::HTTP::FResponse::GetHeader`)
- L166 _function_ `void FResponse::ReadHeaders(FHeaderSink Sink) const` (scope `UE::IoStore::HTTP::FResponse`)
- L173 _function_ `void FResponse::SetDestination(FIoBuffer* Buffer)` (scope `UE::IoStore::HTTP::FResponse`)
- L184 _function_ `FTicketStatus::EId FTicketStatus::GetId() const` (scope `UE::IoStore::HTTP::FTicketStatus`)
- L199 _function_ `UPTRINT FTicketStatus::GetParam() const` (scope `UE::IoStore::HTTP::FTicketStatus`)
- L206 _function_ `FTicket FTicketStatus::GetTicket() const` (scope `UE::IoStore::HTTP::FTicketStatus`)
- L213 _function_ `uint32 FTicketStatus::GetIndex() const` (scope `UE::IoStore::HTTP::FTicketStatus`)
- L220 _function_ `bool FTicketStatus::IsComplete() const` (scope `UE::IoStore::HTTP::FTicketStatus`)
- L245 _function_ `FResponse& FTicketStatus::GetResponse() const` (scope `UE::IoStore::HTTP::FTicketStatus`)
- L253 _function_ `uint32 FTicketStatus::GetContentLength() const` (scope `UE::IoStore::HTTP::FTicketStatus`)
- L261 _function_ `const FTicketPerf& FTicketStatus::GetPerf() const` (scope `UE::IoStore::HTTP::FTicketStatus`)
- L269 _function_ `const FIoBuffer& FTicketStatus::GetContent() const` (scope `UE::IoStore::HTTP::FTicketStatus`)
- L277 _function_ `FTicketStatus::FError FTicketStatus::GetError() const` (scope `UE::IoStore::HTTP::FTicketStatus`)
- L292 _function_ `FTicketPerf::FSample FTicketPerf::GetSample() const` (scope `UE::IoStore::HTTP::FTicketPerf`)
- L302 _function_ `auto Clamp = [] (auto Value)` (scope `UE::IoStore::HTTP::FTicketPerf::GetSample`)
- L303 _function_ `auto ToMs = [&] (uint64 Value)` (scope `UE::IoStore::HTTP::FTicketPerf::GetSample`)

### `Source/Runtime/Experimental/IoStore/HttpClient/Private/ConnectionPool.inl` (Private)


#### class `UE::IoStore::HTTP::FHost`  
`class FHost`  
_L9-52_
- L13 _public member_ `static const uint32 InvalidIp = 0x00ff'ffff;`
- L26 _public prototype_ `FHost(const FParams& Params);`
- L27 _public prototype_ `void SetBufferSize(EDirection Dir, int32 Size);`
- L28 _public prototype_ `int32 GetBufferSize(EDirection Dir) const;`
- L29 _public prototype_ `FOutcome Connect(FSocket& Socket);`
- L30 _public prototype_ `int32 IsResolved() const;`
- L31 _public prototype_ `FOutcome ResolveHostName();`
- L32 _public function_ `FCertRootsRef GetVerifyCert() const`
- L33 _public function_ `uint32 GetMaxConnections() const`
- L34 _public function_ `uint32 GetMaxInflight() const`
- L35 _public function_ `EHttpVersion GetHttpVersion() const`
- L36 _public function_ `bool IsPooled() const`
- L37 _public function_ `uint32 GetIpAddress() const`
- L38 _public function_ `FAnsiStringView GetHostName() const`
- L39 _public function_ `uint32 GetPort() const`
- L42 _private member_ `FCertRootsRef VerifyCert;`
- L43 _private member_ `const ANSICHAR* HostName;`
- L44 _private member_ `uint32 IpAddresses[4] = {};`
- L45 _private member_ `int16 SendBufKb = -1;`
- L46 _private member_ `int16 RecvBufKb = -1;`
- L47 _private member_ `uint16 Port;`
- L48 _private member_ `uint8 MaxConnections;`
- L49 _private member_ `uint8 MaxInflight;`
- L50 _private member_ `EHttpVersion HttpVersion;`
- L51 _private member_ `bool bPooled;`
- L55 _function_ `FHost::FHost(const FParams& Params) : VerifyCert(Params.VerifyCert) , HostName(Params.HostName) , Port(uint16(Params.Port)) , MaxConnections(uint8(Params.MaxConnections)) , MaxInflight(Params.MaxInflight) , HttpVersion(Params.HttpVersion) , bPooled(Params.bPooled)`
- L73 _function_ `void FHost::SetBufferSize(EDirection Dir, int32 Size)`
- L79 _function_ `int32 FHost::GetBufferSize(EDirection Dir) const`
- L85 _function_ `FOutcome FHost::ResolveHostName()`
- L144 _function_ `int32 FHost::IsResolved() const`
- L155 _function_ `FOutcome FHost::Connect(FSocket& Socket)`

#### enum `UE::IoStore::HTTP::FHost::EDirection`  
`enum class EDirection : uint8`  
_L12-12_
- L12 _public enumerator_ `enum class EDirection : uint8 { Send, Recv }; static const uint32 InvalidIp = 0x00ff'ffff; struct FParams { const ANSICHAR* HostName; uint32 Port = 0; uint16 MaxConnections = 1;`
- L12 _public enumerator_ `enum class EDirection : uint8 { Send, Recv }; static const uint32 InvalidIp = 0x00ff'ffff; struct FParams { const ANSICHAR* HostName; uint32 Port = 0; uint16 MaxConnections = 1;`

#### struct `UE::IoStore::HTTP::FHost::FParams`  
`struct FParams`  
_L15-24_
- L17 _public member_ `const ANSICHAR* HostName;`
- L18 _public member_ `uint32 Port = 0;`
- L19 _public member_ `uint16 MaxConnections = 1;`
- L20 _public member_ `bool bPooled = false;`
- L21 _public member_ `uint8 MaxInflight = 1;`
- L22 _public member_ `EHttpVersion HttpVersion = EHttpVersion::One;`
- L23 _public member_ `FCertRootsRef VerifyCert = {};`

#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace IoStore` (scope `UE`)
- L5 _namespace_ `namespace HTTP` (scope `UE::IoStore`)
- L216 _function_ `int32 FConnectionPool::FParams::SetHostFromUrl(FAnsiStringView Url)` (scope `UE::IoStore::HTTP::FConnectionPool::FParams`)
- L242 _function_ `FConnectionPool::FConnectionPool(const FParams& Params)` (scope `UE::IoStore::HTTP::FConnectionPool`)
- L275 _function_ `FConnectionPool::~FConnectionPool()` (scope `UE::IoStore::HTTP::FConnectionPool`)
- L284 _function_ `bool FConnectionPool::Resolve()` (scope `UE::IoStore::HTTP::FConnectionPool`)
- L290 _function_ `uint32 FConnectionPool::GetIps(uint32* Out, uint32 Count) const` (scope `UE::IoStore::HTTP::FConnectionPool`)
- L308 _function_ `void FConnectionPool::Describe(FAnsiStringBuilderBase& OutString) const` (scope `UE::IoStore::HTTP::FConnectionPool`)
- L334 _function_ `bool FConnectionPool::IsValidHostUrl(FAnsiStringView Url)` (scope `UE::IoStore::HTTP::FConnectionPool`)

### `Source/Runtime/Experimental/IoStore/HttpClient/Private/Loop.inl` (Private)


#### class `UE::IoStore::HTTP::FRecvStats`  
`class FRecvStats`  
_L19-51_
- L22 _public prototype_ `FRecvStats() = default;`
- L23 _public prototype_ `void Update(uint32 NowMs, uint32 RecvSizeKiB, uint32 TtfbMs);`
- L24 _public prototype_ `void Flush();`
- L25 _public prototype_ `void Sample(uint32 NowMs, FLoopPerf& Out) const;`
- L43 _private prototype_ `void UpdateRecv(uint32 NowMs, uint32 RecvSizeKiB);`
- L44 _private prototype_ `void UpdateTtfb(uint32 TtfbMs);`
- L45 _private member_ `FBucket Buckets[8] = {};`
- L46 _private member_ `FBucket::FData Accumulator = {};`
- L47 _private member_ `std::atomic<uint64> TtfbSamples = 0;`
- L48 _private member_ `std::atomic<uint32> TotalRecvKiB = 0;`
- L49 _private member_ `uint32 LastMs = 0;`
- L50 _private member_ `uint8 Cursor = 0;`
- L54 _function_ `void FRecvStats::Update(uint32 NowMs, uint32 RecvSizeKiB, uint32 TtfbMs)`
- L61 _function_ `void FRecvStats::UpdateRecv(uint32 NowMs, uint32 RecvSizeKiB)`
- L112 _function_ `void FRecvStats::UpdateTtfb(uint32 TtfbMs)`
- L125 _function_ `void FRecvStats::Flush()`
- L138 _function_ `void FRecvStats::Sample(uint32 NowMs, FLoopPerf& Out) const`

#### enum `UE::IoStore::HTTP::FRecvStats::(anonymous)`  
``  
_L29-31_

#### union `UE::IoStore::HTTP::FRecvStats::FBucket`  
`union FBucket`  
_L33-41_
- L40 _public member_ `std::atomic<uint64> Value;`

#### struct `UE::IoStore::HTTP::FRecvStats::FBucket::FData`  
`struct FData`  
_L35-39_
- L37 _public member_ `uint32 RecvKiB;`
- L38 _public member_ `uint32 TimeMs;`

#### union `UE::IoStore::HTTP::FRecvStats::Sample::FData`  
`union FData`  
_L144-148_
- L146 _public member_ `FBucket::FData Data;`
- L147 _public member_ `uint64 Value;`

#### struct `UE::IoStore::HTTP::FActivityNode`  
`struct FActivityNode : public FActivity`  
_L288-307_
- inherits: `FActivity`
- L298 _public prototype_ `static FActivityNode* Create(FParams& Params, FAnsiStringView Url={}, FCertRootsRef VerifyCert={});`
- L299 _public prototype_ `static void Destroy(FActivityNode* Activity);`
- L300 _public member_ `FActivityNode* Next = nullptr;`
- L301 _public member_ `int8 Slot = -1;`
- L302 _public member_ `bool bFollow30x;`
- L305 _private prototype_ `FActivityNode(const FParams& Params);`
- L306 _private prototype_ `~FActivityNode() = default;`
- L310 _function_ `FActivityNode::FActivityNode(const FParams& Params) : FActivity(Params) , bFollow30x(Params.bFollow30x)`
- L317 _function_ `FActivityNode* FActivityNode::Create(FParams& Params, FAnsiStringView Url, FCertRootsRef VerifyCert)`
- L416 _function_ `void FActivityNode::Destroy(FActivityNode* Ptr)`

#### struct `UE::IoStore::HTTP::FActivityNode::FParams`  
`struct FParams : public FActivity::FParams`  
_L291-296_
- inherits: `FActivity::FParams`
- L294 _public member_ `bool bFollow30x = false;`
- L295 _public member_ `EHttpVersion HttpVersion = EHttpVersion::Default;`

#### class `UE::IoStore::HTTP::FActivityList`  
`class FActivityList`  
_L426-452_
- L429 _public prototype_ `FActivityList() = default;`
- L430 _public prototype_ `~FActivityList();`
- L431 _public function_ `FActivityList(FActivityList&& Rhs)`
- L432 _public function_ `void operator = (FActivityList&& Rhs)`
- L433 _public prototype_ `FActivityList(const FActivityList&) = delete;`
- L434 _public prototype_ `void operator = (const FActivityList&) = delete;`
- L435 _public function_ `int32 IsEmpty() const`
- L436 _public function_ `FActivityNode* GetHead() const`
- L437 _public function_ `FActivityNode* Detach()`
- L438 _public prototype_ `void Reverse();`
- L439 _public prototype_ `void Join(FActivityList& Rhs);`
- L440 _public prototype_ `void Prepend(FActivityNode* Node);`
- L441 _public prototype_ `void Append(FActivityNode* Node);`
- L442 _public prototype_ `FActivityNode* Pop();`
- L443 _public prototype_ `void PopPrepend(FActivityList& ToList);`
- L444 _public prototype_ `void PopAppend(FActivityList& ToList);`
- L447 _public prototype_ `template <typename LAMBDA> FActivityNode* MoveToHead(LAMBDA&& Predicate);`
- L450 _private prototype_ `FActivityNode* PopImpl();`
- L451 _private member_ `FActivityNode* Head = nullptr;`
- L455 _function_ `FActivityList::~FActivityList()`
- L462 _function_ `template <typename LAMBDA> FActivityNode* FActivityList::MoveToHead(LAMBDA&& Predicate)`
- L489 _function_ `void FActivityList::Reverse()`
- L502 _function_ `void FActivityList::Join(FActivityList& Rhs)`
- L516 _function_ `void FActivityList::Prepend(FActivityNode* Node)`
- L524 _function_ `void FActivityList::Append(FActivityNode* Node)`
- L539 _function_ `FActivityNode* FActivityList::Pop()`
- L549 _function_ `FActivityNode* FActivityList::PopImpl()`
- L558 _function_ `void FActivityList::PopPrepend(FActivityList& ToList)`
- L566 _function_ `void FActivityList::PopAppend(FActivityList& ToList)`

#### struct `UE::IoStore::HTTP::FTickState`  
`struct FTickState`  
_L576-587_
- L578 _public member_ `FActivityList DoneList;`
- L579 _public member_ `uint64 Cancels;`
- L580 _public member_ `int32& RecvAllowance;`
- L581 _public member_ `class FWorkQueue* Work;`
- L582 _public member_ `int32 PollTimeoutMs;`
- L583 _public member_ `int32 FailTimeoutMs;`
- L584 _public member_ `uint32 NowMs;`
- L585 _public member_ `uint32 RecvSizeKiB = 0;`
- L586 _public member_ `uint32 TtfbMs = 0;`

#### class `UE::IoStore::HTTP::FWorkQueue`  
`class FWorkQueue`  
_L592-606_
- L595 _public prototype_ `FWorkQueue() = default;`
- L596 _public function_ `bool HasWork() const`
- L597 _public prototype_ `void AddActivity(FActivityNode* Activity);`
- L598 _public prototype_ `FActivityNode* PopActivity();`
- L599 _public prototype_ `void TickCancels(FTickState& State);`
- L602 _private member_ `FActivityList List;`
- L603 _private member_ `uint64 ActiveSlots = 0;`
- L609 _function_ `void FWorkQueue::AddActivity(FActivityNode* Activity)`
- L618 _function_ `FActivityNode* FWorkQueue::PopActivity()`
- L634 _function_ `void FWorkQueue::TickCancels(FTickState& State)`

#### class `UE::IoStore::HTTP::FPeerGroup`  
`class FPeerGroup`  
_L670-700_
- L673 _public prototype_ `FPeerGroup() = default;`
- L674 _public prototype_ `uint32 CollectRecvSizeKiB();`
- L675 _public prototype_ `void SetMaxInflight(uint32 Maximum);`
- L676 _public function_ `void Unwait()`
- L677 _public prototype_ `FWaiter GetWaiter() const;`
- L678 _public prototype_ `bool Tick(FTickState& State);`
- L679 _public prototype_ `void TickSend(FTickState& State, FHost& Host, FPoller& Poller);`
- L680 _public prototype_ `void Fail(FTickState& State, FOutcome Reason);`
- L683 _private prototype_ `bool MaybeStartNewWork(FTickState& State);`
- L684 _private prototype_ `void TickCancels(FTickState& State);`
- L685 _private prototype_ `void Negotiate(FTickState& State);`
- L686 _private prototype_ `void RecvInternal(FTickState& State);`
- L687 _private prototype_ `void SendInternal(FTickState& State);`
- L688 _private member_ `FActivityList Send;`
- L689 _private member_ `FActivityList Recv;`
- L690 _private member_ `FHttpPeer Peer;`
- L691 _private member_ `uint64 LastRecvSize = 0;`
- L692 _private member_ `uint32 LastUseMs = 0;`
- L693 _private member_ `uint8 IsKeepAlive = 0;`
- L694 _private member_ `int8 InflightNum = 0;`
- L695 _private member_ `int8 InflightMax = 1;`
- L696 _private member_ `bool bNegotiating = false;`
- L697 _private member_ `bool bWaiting = false;`
- L703 _function_ `uint32 FPeerGroup::CollectRecvSizeKiB()`
- L718 _function_ `void FPeerGroup::SetMaxInflight(uint32 Maximum)`
- L724 _function_ `FWaiter FPeerGroup::GetWaiter() const`
- L739 _function_ `void FPeerGroup::Fail(FTickState& State, FOutcome Reason)`
- L762 _function_ `bool FPeerGroup::MaybeStartNewWork(FTickState& State)`
- L798 _function_ `void FPeerGroup::Negotiate(FTickState& State)`
- L823 _function_ `void FPeerGroup::RecvInternal(FTickState& State)`
- L923 _function_ `void FPeerGroup::SendInternal(FTickState& State)`
- L956 _function_ `bool FPeerGroup::Tick(FTickState& State)`
- L982 _function_ `void FPeerGroup::TickSend(FTickState& State, FHost& Host, FPoller& Poller)`
- L1072 _function_ `void FPeerGroup::TickCancels(FTickState& State)`

#### class `UE::IoStore::HTTP::FHostGroup`  
`class FHostGroup`  
_L1120-1139_
- L1123 _public prototype_ `FHostGroup(FHost& InHost);`
- L1124 _public function_ `bool IsBusy() const`
- L1125 _public function_ `const FHost& GetHost() const`
- L1126 _public prototype_ `void Tick(FTickState& State);`
- L1127 _public prototype_ `void AddActivity(FActivityNode* Activity);`
- L1130 _private prototype_ `int32 Wait(const FTickState& State);`
- L1131 _private member_ `TArray<FPeerGroup> PeerGroups;`
- L1132 _private member_ `FWorkQueue Work;`
- L1133 _private member_ `FHost& Host;`
- L1134 _private member_ `FPoller Poller;`
- L1135 _private member_ `uint32 BusyCount = 0;`
- L1136 _private member_ `int32 WaitTimeAccum = 0;`
- L1142 _function_ `FHostGroup::FHostGroup(FHost& InHost) : Host(InHost)`
- L1155 _function_ `int32 FHostGroup::Wait(const FTickState& State)`
- L1227 _function_ `void FHostGroup::Tick(FTickState& State)`
- L1276 _function_ `void FHostGroup::AddActivity(FActivityNode* Activity)`

#### class `UE::IoStore::HTTP::FEventLoop::FImpl`  
`class FEventLoop::FImpl`  
_L1289-1314_
- L1292 _public prototype_ `~FImpl();`
- L1293 _public prototype_ `void SamplePerf(FLoopPerf& Perf) const;`
- L1294 _public prototype_ `uint32 Tick(int32 PollTimeoutMs=0);`
- L1295 _public prototype_ `bool IsIdle() const;`
- L1296 _public prototype_ `void Throttle(uint32 KiBPerSec);`
- L1297 _public prototype_ `void SetFailTimeout(int32 TimeoutMs);`
- L1298 _public prototype_ `void Cancel(FTicket Ticket);`
- L1299 _public prototype_ `FRequest Request(FActivityNode* Activity);`
- L1300 _public prototype_ `FTicket Send(FActivityNode* Activity);`
- L1303 _private prototype_ `void ReceiveWork();`
- L1304 _private member_ `FRecvStats RecvStats;`
- L1305 _private member_ `FCriticalSection Lock;`
- L1306 _private member_ `std::atomic<uint64> FreeSlots = ~0ull;`
- L1307 _private member_ `std::atomic<uint64> Cancels = 0;`
- L1308 _private member_ `uint64 PrevFreeSlots = ~0ull;`
- L1309 _private member_ `FActivityList Pending;`
- L1310 _private member_ `FThrottler Throttler;`
- L1311 _private member_ `TArray<FHostGroup> Groups;`
- L1312 _private member_ `int32 FailTimeoutMs = GIdleMs;`
- L1313 _private member_ `uint32 BusyCount = 0;`
- L1317 _function_ `FEventLoop::FImpl::~FImpl()`
- L1323 _function_ `void FEventLoop::FImpl::SamplePerf(FLoopPerf& Out) const`
- L1330 _function_ `FRequest FEventLoop::FImpl::Request(FActivityNode* Activity)`
- L1340 _function_ `FTicket FEventLoop::FImpl::Send(FActivityNode* Activity)`
- L1374 _function_ `bool FEventLoop::FImpl::IsIdle() const`
- L1380 _function_ `void FEventLoop::FImpl::Throttle(uint32 KiBPerSec)`
- L1386 _function_ `void FEventLoop::FImpl::SetFailTimeout(int32 TimeoutMs)`
- L1399 _function_ `void FEventLoop::FImpl::Cancel(FTicket Ticket)`
- L1405 _function_ `void FEventLoop::FImpl::ReceiveWork()`
- L1443 _function_ `uint32 FEventLoop::FImpl::Tick(int32 PollTimeoutMs)`

#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace IoStore` (scope `UE`)
- L5 _namespace_ `namespace HTTP` (scope `UE::IoStore`)
- L9 _variable_ `static bool GInflightCancels = true;` (scope `UE::IoStore::HTTP`)
- L10 _variable_ `static FAutoConsoleVariableRef CVar_IaxInflightCancels( TEXT("iax.HttpInflightCancels"), GInflightCancels, TEXT("Allows cancelling of in-flight requests if supported by peer") );` (scope `UE::IoStore::HTTP`)
- L30 _enumerator_ `BucketMs = 1000` (scope `UE::IoStore::HTTP::FRecvStats::__anone03b3b1d0103`)
- L197 _function_ `uint32 FLoopPerf::GetTotalRecvKiB() const` (scope `UE::IoStore::HTTP::FLoopPerf`)
- L203 _function_ `uint32 FLoopPerf::GetRecvKiBpsCount() const` (scope `UE::IoStore::HTTP::FLoopPerf`)
- L209 _function_ `uint32 FLoopPerf::GetRecvKiBps(uint32 Index) const` (scope `UE::IoStore::HTTP::FLoopPerf`)
- L216 _function_ `void FLoopPerf::GetRecvKiBps(uint32 (&Out)[RecvBucketCount]) const` (scope `UE::IoStore::HTTP::FLoopPerf`)
- L228 _function_ `uint32 FLoopPerf::GetRecvKiBps() const` (scope `UE::IoStore::HTTP::FLoopPerf`)
- L248 _function_ `uint32 FLoopPerf::GetTimeToFirstByteMs() const` (scope `UE::IoStore::HTTP::FLoopPerf`)
- L842 _function_ `` (scope `UE::IoStore::HTTP::FPeerGroup::RecvInternal`)
- L1080 _function_ `` (scope `UE::IoStore::HTTP::FPeerGroup::TickCancels`)
- L1286 _variable_ `static const FEventLoop::FRequestParams GDefaultParams;` (scope `UE::IoStore::HTTP`)
- L1430 _function_ `auto Pred = [&Host] (const FHostGroup& Lhs)` (scope `UE::IoStore::HTTP::FEventLoop::FImpl::ReceiveWork`)
- L1547 _function_ `FEventLoop::FEventLoop()` (scope `UE::IoStore::HTTP::FEventLoop`)
- L1548 _function_ `FEventLoop::~FEventLoop()` (scope `UE::IoStore::HTTP::FEventLoop`)
- L1549 _function_ `void FEventLoop::SamplePerf(FLoopPerf& Out) const` (scope `UE::IoStore::HTTP::FEventLoop`)
- L1550 _function_ `uint32 FEventLoop::Tick(int32 PollTimeoutMs)` (scope `UE::IoStore::HTTP::FEventLoop`)
- L1551 _function_ `bool FEventLoop::IsIdle() const` (scope `UE::IoStore::HTTP::FEventLoop`)
- L1552 _function_ `void FEventLoop::Cancel(FTicket Ticket)` (scope `UE::IoStore::HTTP::FEventLoop`)
- L1553 _function_ `void FEventLoop::Throttle(uint32 KiBPerSec)` (scope `UE::IoStore::HTTP::FEventLoop`)
- L1554 _function_ `void FEventLoop::SetFailTimeout(int32 Ms)` (scope `UE::IoStore::HTTP::FEventLoop`)
- L1557 _function_ `FRequest FEventLoop::Request( FAnsiStringView Method, FAnsiStringView Url, const FRequestParams* Params)` (scope `UE::IoStore::HTTP::FEventLoop`)
- L1582 _function_ `FRequest FEventLoop::Request( FAnsiStringView Method, FAnsiStringView Path, FConnectionPool& Pool, const FRequestParams* Params)` (scope `UE::IoStore::HTTP::FEventLoop`)
- L1608 _function_ `bool FEventLoop::Redirect(const FTicketStatus& Status, FTicketSink& OuterSink)` (scope `UE::IoStore::HTTP::FEventLoop`)
- L1668 _function_ `` (scope `UE::IoStore::HTTP::FEventLoop::Redirect`)
- L1682 _function_ `FTicket FEventLoop::Send(FRequest&& Request, FTicketSink Sink, UPTRINT SinkParam)` (scope `UE::IoStore::HTTP::FEventLoop`)
- L1694 _function_ `` (scope `UE::IoStore::HTTP::FEventLoop::Send`)

### `Source/Runtime/Experimental/IoStore/HttpClient/Private/Misc.inl` (Private)


#### enum `UE::IoStore::HTTP::ETrace`  
`enum class ETrace`  
_L11-28_
- L13 _public enumerator_ `LoopCreate`
- L14 _public enumerator_ `LoopTick`
- L15 _public enumerator_ `LoopDestroy`
- L16 _public enumerator_ `ActivityCreate`
- L17 _public enumerator_ `ActivityDestroy`
- L18 _public enumerator_ `SocketCreate`
- L19 _public enumerator_ `SocketDestroy`
- L20 _public enumerator_ `RequestBegin`
- L21 _public enumerator_ `StateChange`
- L22 _public enumerator_ `Wait`
- L23 _public enumerator_ `Unwait`
- L24 _public enumerator_ `Connect`
- L25 _public enumerator_ `Send`
- L26 _public enumerator_ `Recv`
- L27 _public enumerator_ `StartWork`

#### class `UE::IoStore::HTTP::FOutcome`  
`class FOutcome`  
_L93-130_
- L96 _public prototype_ `static FOutcome Ok(int32 Result=0);`
- L97 _public prototype_ `static FOutcome Waiting(int32 Result=0);`
- L98 _public prototype_ `static FOutcome WaitBuffer(int32 Result=0);`
- L99 _public prototype_ `static FOutcome WaitStream(int32 Result=0);`
- L100 _public prototype_ `static FOutcome Error(const char* Message, int32 Code=-1);`
- L101 _public function_ `static FOutcome None()`
- L102 _public function_ `bool IsError() const`
- L103 _public function_ `bool IsWaiting() const`
- L104 _public function_ `bool IsWaitData() const`
- L105 _public function_ `bool IsWaitBuffer() const`
- L106 _public function_ `bool IsWaitStream() const`
- L107 _public function_ `bool IsOk() const`
- L108 _public function_ `FAnsiStringView GetMessage() const`
- L109 _public function_ `int32 GetErrorCode() const`
- L110 _public function_ `uint32 GetResult() const`
- L113 _private prototype_ `FOutcome() = default;`
- L115 _private member_ `static uint32 const OkTag = 0x0000'8000;`
- L116 _private member_ `static uint32 const WaitTag = 0x0001'8000;`
- L117 _private member_ `static uint32 const BufferTag = 0x0002'0000;`
- L118 _private member_ `static uint32 const StreamTag = 0x0004'0000;`
- L134 _function_ `FOutcome FOutcome::Ok(int32 Result)`
- L143 _function_ `FOutcome FOutcome::Waiting(int32 Result)`
- L152 _function_ `FOutcome FOutcome::WaitBuffer(int32 Result)`
- L162 _function_ `FOutcome FOutcome::WaitStream(int32 Result)`
- L172 _function_ `FOutcome FOutcome::Error(const char* Message, int32 Code)`

#### union `UE::IoStore::HTTP::FOutcome::(anonymous)`  
`union`  
_L120-129_

#### struct `UE::IoStore::HTTP::FOutcome::__anon0709076f010a::(anonymous)`  
`struct`  
_L121-124_

#### struct `UE::IoStore::HTTP::FOutcome::__anon0709076f010a::(anonymous)`  
`struct`  
_L125-128_

#### struct `UE::IoStore::HTTP::FUrlOffsets`  
`struct FUrlOffsets`  
_L223-240_
- L235 _public member_ `Slice UserInfo;`
- L236 _public member_ `Slice HostName;`
- L237 _public member_ `Slice Port;`
- L238 _public member_ `uint8 Path;`
- L239 _public member_ `uint8 SchemeLength;`

#### struct `UE::IoStore::HTTP::FUrlOffsets::Slice`  
`struct Slice`  
_L225-234_
- L227 _public prototype_ `Slice() = default;`
- L228 _public function_ `Slice(int32 l, int32 r) : Left(uint8(l)), Right(uint8(r))`
- L229 _public function_ `FAnsiStringView Get(FAnsiStringView Url) const`
- L230 _public function_ `operator bool () const`
- L231 _public function_ `int32 Len() const`
- L232 _public member_ `uint8 Left;`
- L233 _public member_ `uint8 Right;`

#### struct `UE::IoStore::HTTP::ParseUrl::(anonymous)`  
`struct`  
_L278-278_

#### class `UE::IoStore::HTTP::FBuffer`  
`class FBuffer`  
_L362-402_
- L371 _public prototype_ `FBuffer() = default;`
- L372 _public prototype_ `FBuffer(char* InData, uint32 InMax);`
- L373 _public prototype_ `~FBuffer();`
- L374 _public prototype_ `void Resize(uint32 Size);`
- L375 _public prototype_ `const char* GetData() const;`
- L376 _public prototype_ `uint32 GetSize() const;`
- L377 _public prototype_ `template <typename T> T* Alloc(uint32 Count=1);`
- L378 _public prototype_ `template <typename T> T* Alloc(uint32 Count=1);`
- L379 _public prototype_ `void AdvanceUsed(uint32 Delta);`
- L382 _private prototype_ `uint32 GetCapacity() const;`
- L383 _private prototype_ `char* GetDataPtr();`
- L384 _private prototype_ `void Extend(uint32 AtLeast, uint32 PageSize);`
- L385 _private member_ `UPTRINT Data;`
- L386 _private member_ `uint32 Max = 0;`
- L398 _private prototype_ `FBuffer(FBuffer&&) = delete;`
- L399 _private prototype_ `FBuffer(const FBuffer&) = delete;`
- L400 _private prototype_ `FBuffer& operator = (const FBuffer&) = delete;`
- L401 _private prototype_ `FBuffer& operator = (FBuffer&& Rhs) = delete;`
- L405 _function_ `FBuffer::FBuffer(char* InData, uint32 InMax) : Data(UPTRINT(InData)) , Max(InMax)`
- L413 _function_ `FBuffer::~FBuffer()`
- L422 _function_ `void FBuffer::Resize(uint32 Size)`
- L429 _function_ `char* FBuffer::GetDataPtr()`
- L435 _function_ `const char* FBuffer::GetData() const`
- L441 _function_ `uint32 FBuffer::GetSize() const`
- L447 _function_ `uint32 FBuffer::GetCapacity() const`
- L454 _function_ `template <typename T> T* FBuffer::Alloc(uint32 Count)`
- L474 _function_ `FBuffer::FMutableSection FBuffer::GetMutableFree(uint32 MinSize, uint32 PageSize)`
- L488 _function_ `void FBuffer::AdvanceUsed(uint32 Delta)`
- L495 _function_ `void FBuffer::Extend(uint32 AtLeast, uint32 PageSize)`

#### struct `UE::IoStore::HTTP::FBuffer::FMutableSection`  
`struct FMutableSection`  
_L365-369_
- L367 _public member_ `char* Data;`
- L368 _public member_ `uint32 Size;`

#### union `UE::IoStore::HTTP::FBuffer::(anonymous)`  
``  
_L388-395_

#### struct `UE::IoStore::HTTP::FBuffer::__anon0709076f050a::(anonymous)`  
``  
_L390-393_

#### class `UE::IoStore::HTTP::FThrottler`  
`class FThrottler`  
_L522-542_
- L525 _public prototype_ `FThrottler();`
- L526 _public prototype_ `void SetLimit(uint32 KiBPerSec);`
- L527 _public prototype_ `int32 GetAllowance();`
- L528 _public prototype_ `void ReturnUnused(int32 Unused);`
- L532 _private prototype_ `int32 GetAllowance(int64 CycleDelta);`
- L533 _private member_ `int64 CycleFreq;`
- L534 _private member_ `int64 CycleLast = 0;`
- L535 _private member_ `int64 CyclePeriod = 0;`
- L536 _private member_ `uint32 Limit = 0;`
- L545 _function_ `FThrottler::FThrottler()`
- L552 _function_ `void FThrottler::SetLimit(uint32 KiBPerSec)`
- L564 _function_ `int32 FThrottler::GetAllowance()`
- L573 _function_ `int32 FThrottler::GetAllowance(int64 CycleDelta)`
- L594 _function_ `void FThrottler::ReturnUnused(int32 Unused)`

#### enum `UE::IoStore::HTTP::FThrottler::(anonymous)`  
`enum : uint32`  
_L538-541_

#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace IoStore` (scope `UE`)
- L5 _namespace_ `namespace HTTP` (scope `UE::IoStore`)
- L33 _prototype_ `static void Trace(const struct FActivity*, ETrace, uint32);` (scope `UE::IoStore::HTTP`)
- L34 _prototype_ `static void Trace(UPTRINT, ETrace Action, const class FOutcome* =nullptr);` (scope `UE::IoStore::HTTP`)
- L36 _function_ `static void Trace(ETrace Action)` (scope `UE::IoStore::HTTP`)
- L37 _function_ `static void Trace(const void*, ETrace Action, ...)` (scope `UE::IoStore::HTTP`)
- L40 _function_ `const void* GetIaxTraceChannel()` (scope `UE::IoStore::HTTP`)
- L48 _function_ `static void Trace(...)` (scope `UE::IoStore::HTTP`)
- L58 _macro_ `#define IAS_CVAR(Type, Name, Default, Desc, ...) \`
- L73 _function_ `uint32 GetNowMs()` (scope `UE::IoStore::HTTP`)
- L122 _member_ `UPTRINT Message : 48;` (scope `UE::IoStore::HTTP::FOutcome::__anon0709076f010a::__anon0709076f0208`)
- L123 _member_ `PTRINT Code : 16;` (scope `UE::IoStore::HTTP::FOutcome::__anon0709076f010a::__anon0709076f0208`)
- L126 _member_ `int32 Result;` (scope `UE::IoStore::HTTP::FOutcome::__anon0709076f010a::__anon0709076f0308`)
- L127 _member_ `uint32 Tag;` (scope `UE::IoStore::HTTP::FOutcome::__anon0709076f010a::__anon0709076f0308`)
- L187 _function_ `template <uint32 Base=10> static int64 CrudeToInt(FAnsiStringView View)` (scope `UE::IoStore::HTTP`)
- L220 _prototype_ `template <uint32 Base=10> static int64 CrudeToInt(const char*) = delete;` (scope `UE::IoStore::HTTP`)
- L242 _function_ `static int32 ParseUrl(FAnsiStringView Url, FUrlOffsets& Out)` (scope `UE::IoStore::HTTP`)
- L278 _member_ `struct { int32 c; int32 i; } Seps[2];` (scope `UE::IoStore::HTTP::ParseUrl::__anon0709076f0408`)
- L278 _member_ `struct { int32 c; int32 i; } Seps[2];` (scope `UE::IoStore::HTTP::ParseUrl::__anon0709076f0408`)
- L391 _member_ `uint32 Used : 31;` (scope `UE::IoStore::HTTP::FBuffer::__anon0709076f050a::__anon0709076f0608`)
- L392 _member_ `uint32 Inline : 1;` (scope `UE::IoStore::HTTP::FBuffer::__anon0709076f050a::__anon0709076f0608`)
- L394 _member_ `uint32 UsedInline = 0;` (scope `UE::IoStore::HTTP::FBuffer::__anon0709076f050a`)
- L519 _prototype_ `static void ThrottleTest(FAnsiStringView);` (scope `UE::IoStore::HTTP`)
- L539 _enumerator_ `LIMITLESS = MAX_int32` (scope `UE::IoStore::HTTP::FThrottler::__anon0709076f0703`)
- L540 _enumerator_ `SLICES_POW2 = 5` (scope `UE::IoStore::HTTP::FThrottler::__anon0709076f0703`)

### `Source/Runtime/Experimental/IoStore/HttpClient/Private/Overlapped.inl` (Private)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace IoStore` (scope `UE`)
- L5 _namespace_ `namespace HTTP` (scope `UE::IoStore`)
- L10 _typedef_ `using SocketType = SOCKET;` (scope `UE::IoStore::HTTP`)

### `Source/Runtime/Experimental/IoStore/HttpClient/Private/Peer.inl` (Private)


#### struct `UE::IoStore::HTTP::ECertRootsRefType`  
`struct ECertRootsRefType`  
_L35-39_
- L37 _public member_ `static const FCertRootsRef None = 0;`
- L38 _public member_ `static const FCertRootsRef Default = ~0ull;`

#### class `UE::IoStore::HTTP::FPeer`  
`class FPeer`  
_L44-57_
- L47 _public prototype_ `FPeer() = default;`
- L48 _public prototype_ `FPeer(FSocket InSocket);`
- L49 _public function_ `uint64 GetRecvSize() const`
- L50 _public function_ `FWaitable GetWaitable() const`
- L51 _public function_ `FOutcome Send(const char* Data, int32 Size)`
- L52 _public function_ `FOutcome Recv(char* Out, int32 MaxSize)`
- L53 _public function_ `bool IsValid() const`
- L56 _private member_ `FSocket Socket;`
- L60 _function_ `FPeer::FPeer(FSocket InSocket) : Socket(MoveTemp(InSocket))`

#### class `UE::IoStore::HTTP::FTlsPeer`  
`class FTlsPeer : public FPeer`  
_L495-512_
- inherits: `FPeer`
- L499 _public prototype_ `FTlsPeer() = default;`
- L500 _public prototype_ `~FTlsPeer();`
- L501 _public function_ `FTlsPeer(FTlsPeer&& Rhs)`
- L502 _public function_ `FTlsPeer& operator = (FTlsPeer&& Rhs)`
- L503 _public prototype_ `FTlsPeer(FSocket InSocket, FCertRootsRef Certs=ECertRootsRefType::None, const char* HostName=nullptr);`
- L504 _public prototype_ `bool IsUsingTls() const;`
- L505 _public prototype_ `FOutcome Handshake();`
- L506 _public prototype_ `FOutcome Send(const char* Data, int32 Size);`
- L507 _public prototype_ `FOutcome Recv(char* Out, int32 MaxSize);`
- L510 _protected prototype_ `FTlsPeer& Move(FTlsPeer&& Rhs);`
- L511 _protected member_ `SSL* Ssl = nullptr;`
- L515 _function_ `FTlsPeer::FTlsPeer(FSocket InSocket, FCertRootsRef Certs, const char* HostName) : FPeer(MoveTemp(InSocket))`
- L528 _function_ `FTlsPeer::~FTlsPeer()`
- L537 _function_ `bool FTlsPeer::IsUsingTls() const`
- L543 _function_ `FTlsPeer& FTlsPeer::Move(FTlsPeer&& Rhs)`
- L555 _function_ `FOutcome FTlsPeer::Handshake()`
- L566 _function_ `FOutcome FTlsPeer::Send(const char* Data, int32 Size)`
- L577 _function_ `FOutcome FTlsPeer::Recv(char* Out, int32 MaxSize)`

#### class `UE::IoStore::HTTP::FHttpPeer`  
`class FHttpPeer : public FTlsPeer`  
_L599-628_
- inherits: `FTlsPeer`
- L611 _public prototype_ `FHttpPeer() = default;`
- L612 _public prototype_ `~FHttpPeer();`
- L613 _public prototype_ `FHttpPeer(FHttpPeer&& Rhs) = delete;`
- L614 _public prototype_ `FHttpPeer(const FHttpPeer& Rhs) = delete;`
- L615 _public prototype_ `FHttpPeer& operator = (FHttpPeer&& Rhs);`
- L616 _public prototype_ `FHttpPeer& operator = (const FHttpPeer& Rhs) = delete;`
- L617 _public prototype_ `FHttpPeer(FParams&& Params);`
- L618 _public prototype_ `uint32 GetVersion() const;`
- L619 _public prototype_ `FOutcome Handshake();`
- L620 _public prototype_ `FTransactRef Transact();`
- L621 _public prototype_ `bool Cancel(FTransactId Id);`
- L622 _public prototype_ `FOutcome GetPendingTransactId();`
- L623 _public prototype_ `void SkipPendingTransactId();`
- L626 _private member_ `void* PeerData = nullptr;`
- L627 _private member_ `uint8 Proto = 0;`
- L631 _function_ `FHttpPeer::FHttpPeer(FParams&& Params) : FTlsPeer(MoveTemp(Params.Socket), Params.Certs, Params.HostName) , Proto(uint8(Params.HttpVersion))`
- L642 _function_ `FHttpPeer::~FHttpPeer()`
- L653 _function_ `FHttpPeer& FHttpPeer::operator = (FHttpPeer&& Rhs)`
- L664 _function_ `uint32 FHttpPeer::GetVersion() const`
- L670 _function_ `FOutcome FHttpPeer::Handshake()`
- L706 _function_ `FTransactRef FHttpPeer::Transact()`
- L717 _function_ `bool FHttpPeer::Cancel(FTransactId Id)`
- L728 _function_ `void FHttpPeer::SkipPendingTransactId()`
- L739 _function_ `FOutcome FHttpPeer::GetPendingTransactId()`

#### struct `UE::IoStore::HTTP::FHttpPeer::FParams`  
`struct FParams`  
_L603-609_
- L605 _public member_ `FSocket Socket;`
- L606 _public member_ `FCertRootsRef Certs = ECertRootsRefType::None;`
- L607 _public member_ `const char* HostName = nullptr;`
- L608 _public member_ `EHttpVersion HttpVersion = EHttpVersion::One;`

#### Free symbols / members of external scopes

- L6 _macro_ `# define IAS_HTTP_HAS_OPENSSL 0`
- L29 _namespace_ `namespace UE`
- L29 _namespace_ `namespace IoStore` (scope `UE`)
- L29 _namespace_ `namespace HTTP` (scope `UE::IoStore`)
- L33 _variable_ `static FCertRoots GDefaultCertRoots;` (scope `UE::IoStore::HTTP`)
- L70 _function_ `static void Ssl_ContextDestroy(UPTRINT Handle)` (scope `UE::IoStore::HTTP`)
- L77 _function_ `static uint32 Ssl_ContextProvision(SSL_CTX* Context)` (scope `UE::IoStore::HTTP`)
- L118 _function_ `static uint32 Ssl_ContextProvision(SSL_CTX* Context, FMemoryView PemData)` (scope `UE::IoStore::HTTP`)
- L145 _function_ `static UPTRINT Ssl_ContextCreate(FMemoryView PemData)` (scope `UE::IoStore::HTTP`)
- L204 _function_ `static int32 Ssl_ContextCertNum(UPTRINT Handle)` (scope `UE::IoStore::HTTP`)
- L213 _function_ `static int32 Ssl_BioWrite(BIO* Bio, const char* Data, size_t Size, size_t* BytesWritten)` (scope `UE::IoStore::HTTP`)
- L236 _function_ `static int32 Ssl_BioRead(BIO* Bio, char* Data, size_t Size, size_t* BytesRead)` (scope `UE::IoStore::HTTP`)
- L259 _function_ `static long Ssl_BioControl(BIO*, int Cmd, long, void*)` (scope `UE::IoStore::HTTP`)
- L265 _function_ `static SSL* Ssl_Create(FCertRootsRef Certs, const char* HostName=nullptr)` (scope `UE::IoStore::HTTP`)
- L305 _function_ `static void Ssl_Destroy(SSL* Ssl)` (scope `UE::IoStore::HTTP`)
- L311 _function_ `static void Ssl_AssociatePeer(SSL* Ssl, FPeer* Peer)` (scope `UE::IoStore::HTTP`)
- L319 _function_ `static void Ssl_SetupAlpn(SSL* Ssl, int32 HttpVersion)` (scope `UE::IoStore::HTTP`)
- L334 _function_ `static int32 Ssl_GetProtocolVersion(SSL* Ssl)` (scope `UE::IoStore::HTTP`)
- L372 _function_ `static FOutcome Ssl_GetOutcome(SSL* Ssl, int32 SslResult, const char* Message="tls error")` (scope `UE::IoStore::HTTP`)
- L383 _function_ `static FOutcome Ssl_Handshake(SSL* Ssl)` (scope `UE::IoStore::HTTP`)
- L408 _function_ `static FOutcome Ssl_Write(SSL* Ssl, const char* Data, int32 Size)` (scope `UE::IoStore::HTTP`)
- L415 _function_ `static FOutcome Ssl_Read(SSL* Ssl, char* Out, int32 MaxSize)` (scope `UE::IoStore::HTTP`)
- L424 _function_ `static void Ssl_ContextDestroy(...)` (scope `UE::IoStore::HTTP`)
- L425 _function_ `static UPTRINT Ssl_ContextCreate(...)` (scope `UE::IoStore::HTTP`)
- L426 _function_ `static int32 Ssl_ContextCertNum(...)` (scope `UE::IoStore::HTTP`)
- L427 _function_ `static SSL* Ssl_Create(...)` (scope `UE::IoStore::HTTP`)
- L428 _function_ `static void Ssl_Destroy(...)` (scope `UE::IoStore::HTTP`)
- L429 _function_ `static void Ssl_AssociatePeer(...)` (scope `UE::IoStore::HTTP`)
- L430 _function_ `static void Ssl_SetupAlpn(...)` (scope `UE::IoStore::HTTP`)
- L431 _function_ `static int32 Ssl_GetProtocolVersion(...)` (scope `UE::IoStore::HTTP`)
- L432 _function_ `static FOutcome Ssl_Handshake(...)` (scope `UE::IoStore::HTTP`)
- L433 _function_ `static FOutcome Ssl_Write(...)` (scope `UE::IoStore::HTTP`)
- L434 _function_ `static FOutcome Ssl_Read(...)` (scope `UE::IoStore::HTTP`)
- L441 _function_ `FCertRoots::~FCertRoots()` (scope `UE::IoStore::HTTP::FCertRoots`)
- L450 _function_ `FCertRoots::FCertRoots(FMemoryView PemData)` (scope `UE::IoStore::HTTP::FCertRoots`)
- L456 _function_ `int32 FCertRoots::Num() const` (scope `UE::IoStore::HTTP::FCertRoots`)
- L467 _function_ `void FCertRoots::SetDefault(FCertRoots&& CertRoots)` (scope `UE::IoStore::HTTP::FCertRoots`)
- L474 _function_ `FCertRootsRef FCertRoots::NoTls()` (scope `UE::IoStore::HTTP::FCertRoots`)
- L480 _function_ `FCertRootsRef FCertRoots::Default()` (scope `UE::IoStore::HTTP::FCertRoots`)
- L486 _function_ `FCertRootsRef FCertRoots::Explicit(const FCertRoots& CertRoots)` (scope `UE::IoStore::HTTP::FCertRoots`)
- L595 _namespace_ `namespace UE`
- L595 _namespace_ `namespace IoStore` (scope `UE`)
- L595 _namespace_ `namespace HTTP` (scope `UE::IoStore`)

### `Source/Runtime/Experimental/IoStore/HttpClient/Private/Socket.inl` (Private)


#### enum `UE::IoStore::HTTP::(anonymous)`  
`enum`  
_L36-39_

#### class `UE::IoStore::HTTP::FWaitable`  
`class FWaitable`  
_L129-146_
- L132 _public prototype_ `FWaitable() = default;`
- L133 _public prototype_ `FWaitable(FWaitable&&) = default;`
- L134 _public prototype_ `FWaitable& operator = (FWaitable&&) = default;`
- L140 _private prototype_ `FWaitable(SocketType InSocket);`
- L141 _private member_ `SocketType Socket = InvalidSocket;`
- L144 _private prototype_ `FWaitable(const FWaitable&) = delete;`
- L145 _private prototype_ `FWaitable& operator = (const FWaitable&) = delete;`
- L149 _function_ `FWaitable::FWaitable(SocketType InSocket) : Socket(InSocket)`

#### struct `UE::IoStore::HTTP::FPollFdBase`  
`struct FPollFdBase`  
_L162-172_
- L164 _public member_ `SocketType fd;`
- L165 _public member_ `int16 events;`
- L166 _public member_ `int16 revents;`
- L167 _public member_ `static const int16 POLLIN = 1 << 0;`
- L168 _public member_ `static const int16 POLLOUT = 1 << 1;`
- L169 _public member_ `static const int16 POLLERR = 1 << 2;`
- L170 _public member_ `static const int16 POLLHUP = POLLERR;`
- L171 _public member_ `static const int16 POLLNVAL= POLLERR;`

#### struct `UE::IoStore::HTTP::FPollFd`  
`struct FPollFd : public FPollFdBase`  
_L176-203_
- inherits: `FPollFdBase`
- L179 _public member_ `static const int16 PollIn = int16(POLLIN);`
- L180 _public member_ `static const int16 PollOut = int16(POLLOUT);`
- L181 _public member_ `static const int16 PollErr = int16(POLLERR);`
- L182 _public member_ `static const int16 PollHup = int16(POLLHUP);`
- L183 _public member_ `static const int16 PollNVal= int16(POLLNVAL);`
- L184 _public member_ `static const int16 PollAll = PollIn|PollOut|PollErr|PollHup|PollNVal;`
- L186 _public function_ `FPollFd(SocketType Socket, int16 Events)`
- L193 _public function_ `bool HasTrigger() const`
- L194 _public function_ `bool HasSendTrigger() const`
- L195 _public function_ `bool HasRecvTrigger() const`
- L201 _private typedef_ `using FdType = decltype(fd);` — The following is odd because POLLFD varies subtly from one platform to the next. With typedefs we can cleanly set members and not get narrowing warnings from the compiler.
- L202 _private typedef_ `using EventType = decltype(events);`

#### class `UE::IoStore::HTTP::FPoller`  
`class FPoller`  
_L206-220_
- L209 _public function_ `FPoller()`
- L210 _public function_ `FPoller(FPoller&& Rhs)`
- L211 _public function_ `~FPoller()`
- L212 _public function_ `FPoller& operator = (FPoller&& Rhs)`
- L213 _public function_ `bool Register(const FWaitable& Waitable)`
- L214 _public prototype_ `int32 Wait(FPollFd* Polls, int32 Num, int32 TimeOutMs);`
- L217 _private prototype_ `FPoller(const FPoller&) = delete;`
- L218 _private prototype_ `FPoller& operator = (const FPoller&) = delete;`
- L219 _private member_ `PollType Handle = 0;`
- L223 _function_ `int32 FPoller::Wait(FPollFd* Polls, int32 Num, int32 TimeOutMs)`

#### class `UE::IoStore::HTTP::FWaiter`  
`class FWaiter`  
_L280-312_
- L291 _public prototype_ `static int32 Wait(TArrayView<FWaiter> Waiters, FPoller& Poller, int32 TimeoutMs);`
- L293 _public prototype_ `FWaiter() = default;`
- L294 _public prototype_ `FWaiter(FWaitable&& Waitable);`
- L295 _public prototype_ `FWaiter(FWaiter&&) = default;`
- L296 _public prototype_ `FWaiter& operator = (FWaiter&&) = default;`
- L297 _public function_ `bool IsValid() const`
- L298 _public function_ `bool IsReady() const`
- L299 _public function_ `void WaitFor(EWhat What)`
- L300 _public function_ `void SetIndex(uint32 InIndex)`
- L301 _public function_ `uint32 GetIndex() const`
- L304 _private member_ `SocketType Socket = InvalidSocket;`
- L305 _private member_ `uint16 Index = 0;`
- L306 _private member_ `EWhat WaitOn = EWhat::None;`
- L307 _private member_ `uint8 Ready = 0;`
- L310 _private prototype_ `FWaiter(const FWaiter&) = delete;`
- L311 _private prototype_ `FWaiter& operator = (const FWaiter&) = delete;`
- L315 _function_ `FWaiter::FWaiter(FWaitable&& Waitable) : Socket(Waitable.Socket)`
- L321 _function_ `int32 FWaiter::Wait(TArrayView<FWaiter> Waiters, FPoller& Poller, int32 TimeoutMs)`

#### enum `UE::IoStore::HTTP::FWaiter::EWhat`  
`enum class EWhat : uint8`  
_L283-289_
- L285 _public enumerator_ `None = 0b00`
- L286 _public enumerator_ `Send = 0b01`
- L287 _public enumerator_ `Recv = 0b10`
- L288 _public enumerator_ `Both = Send|Recv`

#### class `UE::IoStore::HTTP::FSocket`  
`class FSocket`  
_L366-393_
- L369 _public prototype_ `FSocket() = default;`
- L370 _public function_ `~FSocket()`
- L371 _public function_ `FSocket(FSocket&& Rhs)`
- L372 _public function_ `FSocket& operator = (FSocket&& Rhs)`
- L373 _public function_ `bool IsValid() const`
- L374 _public function_ `FWaitable GetWaitable() const`
- L375 _public prototype_ `uint64 GetRecvSize() const;`
- L376 _public prototype_ `bool Create();`
- L377 _public prototype_ `void Destroy();`
- L378 _public prototype_ `FOutcome Connect(uint32 Ip, uint32 Port);`
- L379 _public prototype_ `void Disconnect();`
- L380 _public prototype_ `FOutcome Send(const char* Data, uint32 Size);`
- L381 _public prototype_ `FOutcome Recv(char* Dest, uint32 Size);`
- L382 _public prototype_ `bool SetBlocking(bool bBlocking);`
- L383 _public prototype_ `bool SetSendBufSize(int32 Size);`
- L384 _public prototype_ `bool SetRecvBufSize(int32 Size);`
- L387 _private prototype_ `void Move(FSocket&& Rhs);`
- L388 _private member_ `uint64 RecvSize = 0;`
- L389 _private member_ `SocketType Socket = InvalidSocket;`
- L391 _private prototype_ `FSocket(const FSocket&) = delete;`
- L392 _private prototype_ `FSocket& operator = (const FSocket&) = delete;`
- L396 _function_ `void FSocket::Move(FSocket&& Rhs)`
- L404 _function_ `uint64 FSocket::GetRecvSize() const`
- L410 _function_ `bool FSocket::Create()`
- L428 _function_ `void FSocket::Destroy()`
- L442 _function_ `FOutcome FSocket::Connect(uint32 IpAddress, uint32 Port)`
- L475 _function_ `void FSocket::Disconnect()`
- L482 _function_ `FOutcome FSocket::Send(const char* Data, uint32 Size)`
- L515 _function_ `FOutcome FSocket::Recv(char* Dest, uint32 Size)`
- L539 _function_ `bool FSocket::SetBlocking(bool bBlocking)`
- L561 _function_ `bool FSocket::SetSendBufSize(int32 Size)`
- L567 _function_ `bool FSocket::SetRecvBufSize(int32 Size)`

#### Free symbols / members of external scopes

- L7 _macro_ `#define IAS_HTTP_SOCKET_FORWARD(Src, Dest) \`
- L32 _namespace_ `namespace UE`
- L32 _namespace_ `namespace IoStore` (scope `UE`)
- L32 _namespace_ `namespace HTTP` (scope `UE::IoStore`)
- L34 _typedef_ `using MsgFlagType = int;` (scope `UE::IoStore::HTTP`)
- L37 _enumerator_ `SHUT_RDWR = SD_BOTH` (scope `UE::IoStore::HTTP::__anone536f5ac0103`)
- L38 _enumerator_ `MSG_NOSIGNAL = 0` (scope `UE::IoStore::HTTP::__anone536f5ac0103`)
- L41 _macro_ `# define IAS_HTTP_USE_POLL`
- L43 _function_ `template <typename... ArgTypes> static auto poll(ArgTypes&&... Args)` (scope `UE::IoStore::HTTP`)
- L58 _namespace_ `namespace UE`
- L58 _namespace_ `namespace IoStore` (scope `UE`)
- L58 _namespace_ `namespace HTTP` (scope `UE::IoStore`)
- L60 _typedef_ `using SocketType = int;` (scope `UE::IoStore::HTTP`)
- L62 _function_ `static int32 closesocket(int32 Socket)` (scope `UE::IoStore::HTTP`)
- L70 _namespace_ `namespace UE`
- L70 _namespace_ `namespace IoStore` (scope `UE`)
- L70 _namespace_ `namespace HTTP` (scope `UE::IoStore`)
- L83 _typedef_ `using PollType = UPTRINT;` (scope `UE::IoStore::HTTP`)
- L84 _function_ `static PollType Poll_CreateContext()` (scope `UE::IoStore::HTTP`)
- L85 _function_ `static void Poll_DestroyContext(PollType)` (scope `UE::IoStore::HTTP`)
- L86 _function_ `static bool Poll_Register(...)` (scope `UE::IoStore::HTTP`)
- L90 _function_ `template <typename... ArgTypes> static auto Poll_Wait(PollType, ArgTypes&&... Args)` (scope `UE::IoStore::HTTP`)
- L98 _namespace_ `namespace UE`
- L98 _namespace_ `namespace IoStore` (scope `UE`)
- L98 _namespace_ `namespace HTTP` (scope `UE::IoStore`)
- L101 _variable_ `static const SocketType InvalidSocket = SocketType(~0ull);` (scope `UE::IoStore::HTTP`)
- L106 _function_ `static int32 LastSocketResult()` (scope `UE::IoStore::HTTP`)
- L107 _macro_ `# define IsSocketResult(err) (LastSocketResult() == WSA##err)`
- L110 _macro_ `# define IsSocketResult(err) int32(LastSocketResult() == err)`
- L116 _function_ `uint32 Socket_HtoNl(uint32 v)` (scope `UE::IoStore::HTTP`) — hton* can sometimes be implemented as a macro which does not work with the forward approach above. Hence we have our own here. Thanks for reading!
- L117 _function_ `uint16 Socket_HtoNs(uint16 v)` (scope `UE::IoStore::HTTP`)
- L123 _namespace_ `namespace UE`
- L123 _namespace_ `namespace IoStore` (scope `UE`)
- L123 _namespace_ `namespace HTTP` (scope `UE::IoStore`)
- L160 _typedef_ `using FPollFdBase = pollfd;` (scope `UE::IoStore::HTTP`)
- L447 _function_ `auto Return = [this] (FOutcome Outcome)` (scope `UE::IoStore::HTTP::FSocket::Connect`)
- L487 _function_ `auto Return = [this] (FOutcome Outcome)` (scope `UE::IoStore::HTTP::FSocket::Send`)
- L520 _function_ `auto Return = [this] (FOutcome Outcome)` (scope `UE::IoStore::HTTP::FSocket::Recv`)
- L575 _variable_ `static FLaneEstate* GSocketLaneEstate = LaneEstate_New({ .Name = "Iax/Socket", .Group = "Iax", .Channel = GetIaxTraceChannel(), .Weight = 12, });` (scope `UE::IoStore::HTTP`)
- L583 _function_ `static void Trace(UPTRINT Socket, ETrace Action, const FOutcome* Outcome)` (scope `UE::IoStore::HTTP`)

### `Source/Runtime/Experimental/IoStore/HttpClient/Private/Socks.inl` (Private)


#### struct `UE::IoStore::HTTP::ConnectSocks4::FSocks4Request`  
`struct FSocks4Request`  
_L52-58_
- L54 _public member_ `uint8 Version = 4;`
- L55 _public member_ `uint8 Command = 1;`
- L56 _public member_ `uint16 Port;`
- L57 _public member_ `uint32 IpAddress;`

#### struct `UE::IoStore::HTTP::ConnectSocks4::FSocks4Reply`  
`struct FSocks4Reply`  
_L60-66_
- L62 _public member_ `uint8 Version;`
- L63 _public member_ `uint8 Code;`
- L64 _public member_ `uint16 Port;`
- L65 _public member_ `uint32 IpAddress;`

#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace IoStore` (scope `UE`)
- L5 _namespace_ `namespace HTTP` (scope `UE::IoStore`)
- L16 _function_ `static uint32 GetSocksIpAddress()` (scope `UE::IoStore::HTTP`)
- L50 _function_ `static FOutcome ConnectSocks4(FSocket& Socket, uint32 IpAddress, uint32 Port)` (scope `UE::IoStore::HTTP`)
- L100 _function_ `static FOutcome ConnectSocks5(FSocket& Socket, uint32 IpAddress, uint32 Port)` (scope `UE::IoStore::HTTP`)
- L162 _function_ `static FOutcome MaybeConnectSocks(FSocket& Socket, uint32 IpAddress, uint32 Port)` (scope `UE::IoStore::HTTP`)

### `Source/Runtime/Experimental/IoStore/HttpClient/Private/Test.inl` (Private)


#### enum `UE::IoStore::HTTP::ThrottleTest::(anonymous)`  
`enum`  
_L173-173_

#### enum `UE::IoStore::HTTP::RedirectTest::ReTyp`  
`enum ReTyp`  
_L294-294_
- L294 _public enumerator_ `enum ReTyp { ReAbs, ReAbsTls, ReRel, ReRelTls }; enum { RecvDataSize = 48 }; TAnsiStringBuilder<64> Builder; auto BuildUrl = [&] (ReTyp Typ, uint32 Code) -> const auto& { bool bTls = (Typ & 1); Builder.Reset();`
- L294 _public enumerator_ `enum ReTyp { ReAbs, ReAbsTls, ReRel, ReRelTls }; enum { RecvDataSize = 48 }; TAnsiStringBuilder<64> Builder; auto BuildUrl = [&] (ReTyp Typ, uint32 Code) -> const auto& { bool bTls = (Typ & 1); Builder.Reset();`
- L294 _public enumerator_ `enum ReTyp { ReAbs, ReAbsTls, ReRel, ReRelTls }; enum { RecvDataSize = 48 }; TAnsiStringBuilder<64> Builder; auto BuildUrl = [&] (ReTyp Typ, uint32 Code) -> const auto& { bool bTls = (Typ & 1); Builder.Reset();`
- L294 _public enumerator_ `enum ReTyp { ReAbs, ReAbsTls, ReRel, ReRelTls }; enum { RecvDataSize = 48 }; TAnsiStringBuilder<64> Builder; auto BuildUrl = [&] (ReTyp Typ, uint32 Code) -> const auto& { bool bTls = (Typ & 1); Builder.Reset();`

#### enum `UE::IoStore::HTTP::RedirectTest::(anonymous)`  
`enum`  
_L295-295_

#### struct `UE::IoStore::HTTP::ChunkedTest::FTestState`  
`struct FTestState`  
_L425-431_
- L427 _public member_ `int32 Size = 0;`
- L428 _public member_ `uint32 Hash = 0x493;`
- L429 _public member_ `uint32 ExpectedHash = 0;`
- L430 _public member_ `int32 ExpectedSize = -1;`

#### struct `UE::IoStore::HTTP::HttpTest::(anonymous)`  
``  
_L567-570_

#### struct `UE::IoStore::HTTP::HttpTest::(anonymous)`  
`struct`  
_L834-837_

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace IoStore` (scope `UE`)
- L10 _namespace_ `namespace HTTP` (scope `UE::IoStore`)
- L16 _function_ `static void MiscTest()` (scope `UE::IoStore::HTTP`)
- L18 _macro_ `#define CRLF "\r\n"`
- L50 _function_ `` (scope `UE::IoStore::HTTP::MiscTest`)
- L62 _function_ `auto IsBar = [&] (auto, auto Value)` (scope `UE::IoStore::HTTP::MiscTest`)
- L171 _function_ `static void ThrottleTest(FAnsiStringView TestUrl)` (scope `UE::IoStore::HTTP`)
- L173 _enumerator_ `enum { TheMax = 0x7fff'fffful }; check(FThrottler().GetAllowance() >= TheMax); FThrottler Throttler; uint64 OneSecond = Throttler.CycleFreq; FIoBuffer RecvData;` (scope `UE::IoStore::HTTP::ThrottleTest::__anon4a2087230303`)
- L194 _function_ `Loop.Send(MoveTemp(Request), [&] (const FTicketStatus& Status) { check(Status.GetId() != FTicketStatus::EId::Error); if (Status.GetId() == FTicketStatus::EId::Response) { Status.GetResponse().SetDestination(&RecvData); } });` (scope `UE::IoStore::HTTP::ThrottleTest`)
- L224 _function_ `static void TlsLoadRootCerts()` (scope `UE::IoStore::HTTP`)
- L244 _function_ `static void TlsTest()` (scope `UE::IoStore::HTTP`)
- L248 _function_ `auto WaitForLoopIdle = [&]` (scope `UE::IoStore::HTTP::TlsTest`)
- L252 _function_ `auto OkSink = [Dest=FIoBuffer()] (const FTicketStatus& Status) mutable` (scope `UE::IoStore::HTTP::TlsTest`)
- L282 _function_ `static void RedirectTest(const ANSICHAR* TestHost, FCertRootsRef VerifyCert)` (scope `UE::IoStore::HTTP`)
- L286 _function_ `auto WaitForLoopIdle = [&]` (scope `UE::IoStore::HTTP::RedirectTest`)
- L295 _enumerator_ `enum { RecvDataSize = 48 }; TAnsiStringBuilder<64> Builder; auto BuildUrl = [&] (ReTyp Typ, uint32 Code) -> const auto& { bool bTls = (Typ & 1); Builder.Reset(); Builder << ((bTls) ? "https:` (scope `UE::IoStore::HTTP::RedirectTest::__anon4a2087230803`)
- L299 _function_ `` (scope `UE::IoStore::HTTP::RedirectTest`)
- L315 _function_ `auto OkSink = [Dest=FIoBuffer(), SinkParam, &RecvCount] (const FTicketStatus& Status) mutable` (scope `UE::IoStore::HTTP::RedirectTest`)
- L389 _function_ `static void ChunkedTest(const ANSICHAR* TestHost)` (scope `UE::IoStore::HTTP`)
- L394 _function_ `` (scope `UE::IoStore::HTTP::ChunkedTest`)
- L540 _function_ `static void SeedHttp(const ANSICHAR* TestHost, uint32 Seed)` (scope `UE::IoStore::HTTP`)
- L546 _function_ `Loop.Send(MoveTemp(Request), [] (const FTicketStatus&) {});` (scope `UE::IoStore::HTTP::SeedHttp`)
- L551 _function_ `static void HttpTest(const ANSICHAR* TestHost, FCertRootsRef VerifyCert)` (scope `UE::IoStore::HTTP`)
- L557 _function_ `` (scope `UE::IoStore::HTTP::HttpTest`)
- L568 _member_ `FIoBuffer Dest;` (scope `UE::IoStore::HTTP::HttpTest::__anon4a2087231208`)
- L569 _member_ `uint64 Hash = 0;` (scope `UE::IoStore::HTTP::HttpTest::__anon4a2087231208`)
- L613 _function_ `auto NullSink = [] (const FTicketStatus&)` (scope `UE::IoStore::HTTP::HttpTest`)
- L633 _function_ `auto LoopTask = UE::Tasks::Launch(TEXT("IasHttpTest.Loop"), [&] () { uint32 DelaySeed = 493; while (!LoopStop) { while (Loop.Tick()) { if (!LoopTickDelay) { continue; } float DelayFloat = float(DelaySeed % 75) / 1000.0f; FPlatformProcess::SleepNoStats(DelayFloat); DelaySeed *= 0xa93; } FPlatformProcess::SleepNoStats(0.005f); } });` (scope `UE::IoStore::HTTP::HttpTest`)
- L797 _function_ `auto MixTh = [Th=uint32(0)] () mutable` (scope `UE::IoStore::HTTP::HttpTest`)
- L818 _function_ `Loop.Send(MoveTemp(Request), [] (const FTicketStatus& Status) { if (Status.GetId() == FTicketStatus::EId::Response) { FResponse& Response = Status.GetResponse(); check(Response.GetStatusCode() == 431);` (scope `UE::IoStore::HTTP::HttpTest`)
- L835 _member_ `const ANSICHAR* Uri;` (scope `UE::IoStore::HTTP::HttpTest::__anon4a2087231d08`)
- L836 _member_ `bool Disconnect;` (scope `UE::IoStore::HTTP::HttpTest::__anon4a2087231d08`)
- L897 _function_ `auto StressTaskEntry = [&]` (scope `UE::IoStore::HTTP::HttpTest`)
- L912 _function_ `StressTask = UE::Tasks::Launch(TEXT("StressTask"), [&] { StressTaskEn` (scope `UE::IoStore::HTTP::HttpTest`)
- L967 _function_ `void IasHttpTest(const ANSICHAR* TestHost="localhost", uint32 Seed=493)` (scope `UE::IoStore::HTTP`)
- L990 _function_ `Loop.Send(MoveTemp(Request), [&] (const FTicketStatus& Status) { check(Status.GetId() != FTicketStatus::EId::Error); if (Status.GetId() == FTicketStatus::EId::Response) { FResponse& Response = Status.GetResponse(); Response.SetDestination(&CertBuffer); } });` (scope `UE::IoStore::HTTP::IasHttpTest`)

### `Source/Runtime/Experimental/IoStore/HttpClient/Private/TransactionOne.inl` (Private)


#### struct `UE::IoStore::HTTP::FMessageOffsets`  
`struct FMessageOffsets`  
_L9-14_
- L11 _public member_ `uint8 StatusCode;`
- L12 _public member_ `uint8 Message;`
- L13 _public member_ `uint16 Headers;`

#### class `UE::IoStore::HTTP::DetailOne::FBase`  
`class FBase`  
_L136-152_
- L139 _public prototype_ `FBase();`
- L142 _protected typedef_ `using FMutableSection = FBuffer::FMutableSection;`
- L144 _protected prototype_ `const char* GetData() const;`
- L145 _protected prototype_ `uint32 GetSize() const;`
- L146 _protected prototype_ `FMutableSection GetMutableFree(uint32 MinSize, uint32 PageSize=256);`
- L147 _protected prototype_ `void AdvanceUsed(uint32 Delta);`
- L150 _private member_ `FBuffer Buffer;`
- L151 _private member_ `char Data[256];`
- L155 _function_ `FBase::FBase() : Buffer(Data, sizeof(Data))`
- L161 _function_ `const char* FBase::GetData() const`
- L167 _function_ `uint32 FBase::GetSize() const`
- L173 _function_ `FBase::FMutableSection FBase::GetMutableFree(uint32 MinSize, uint32 PageSize)`
- L179 _function_ `void FBase::AdvanceUsed(uint32 Delta)`

#### class `UE::IoStore::HTTP::DetailOne::FRequest`  
`class FRequest : public FBase`  
_L187-205_
- inherits: `FBase`
- L193 _public prototype_ `void Begin(FAnsiStringView Host, FAnsiStringView Method, FAnsiStringView Path);`
- L194 _public prototype_ `void AddHeader(FAnsiStringView Key, FAnsiStringView Value);`
- L195 _public prototype_ `FTransactId End(bool bKeepAlive);`
- L196 _public prototype_ `FOutcome TrySendRequest(FTlsPeer& Peer);`
- L199 _private prototype_ `FRequest& operator << (FAnsiStringView Value);`
- L200 _private member_ `uint16 HeaderLeft;`
- L201 _private member_ `uint16 AlreadySent = 0;`
- L202 _private member_ `int16 HeaderRight = -1;`
- L203 _private member_ `int8 MethodLength = -1;`
- L204 _private member_ `uint8 _Unnused;`
- L208 _function_ `void FRequest::Begin(FAnsiStringView Host, FAnsiStringView Method, FAnsiStringView Path)`
- L220 _function_ `void FRequest::AddHeader(FAnsiStringView Key, FAnsiStringView Value)`
- L227 _function_ `FTransactId FRequest::End(bool bKeepAlive)`
- L242 _function_ `FRequest& FRequest::operator << (FAnsiStringView Value)`
- L252 _function_ `FOutcome FRequest::TrySendRequest(FTlsPeer& Peer)`

#### class `UE::IoStore::HTTP::DetailOne::FStatusHeaders`  
`class FStatusHeaders : public FRequest`  
_L281-308_
- inherits: `FRequest`
- L287 _public prototype_ `FOutcome TryRecvResponse(FTlsPeer& Peer);`
- L288 _public prototype_ `bool IsKeepAlive() const;`
- L289 _public prototype_ `uint32 GetStatusCode() const;`
- L290 _public prototype_ `FAnsiStringView GetStatusMessage() const;`
- L291 _public prototype_ `int64 GetContentLength() const;`
- L292 _public prototype_ `bool IsChunked() const;`
- L293 _public prototype_ `void ReadHeaders(FResponse::FHeaderSink Sink) const;`
- L296 _protected prototype_ `const char* GetMessageRight() const;`
- L299 _private prototype_ `FOutcome Parse();`
- L300 _private member_ `int64 ContentLength = -1;`
- L301 _private member_ `FMessageOffsets Offsets = {};`
- L302 _private member_ `int16 MessageLeft = -1;`
- L303 _private member_ `int16 MessageRight = -1;`
- L304 _private member_ `uint16 StatusCode = 0;`
- L305 _private member_ `uint8 bKeepAlive : 1;`
- L306 _private member_ `uint8 bChunked : 1;`
- L307 _private member_ `uint8 _Unused : 7;`
- L311 _function_ `bool FStatusHeaders::IsKeepAlive() const`
- L317 _function_ `uint32 FStatusHeaders::GetStatusCode() const`
- L324 _function_ `FAnsiStringView FStatusHeaders::GetStatusMessage() const`
- L332 _function_ `int64 FStatusHeaders::GetContentLength() const`
- L339 _function_ `bool FStatusHeaders::IsChunked() const`
- L346 _function_ `void FStatusHeaders::ReadHeaders(FResponse::FHeaderSink Sink) const`
- L356 _function_ `const char* FStatusHeaders::GetMessageRight() const`
- L362 _function_ `FOutcome FStatusHeaders::TryRecvResponse(FTlsPeer& Peer)`
- L428 _function_ `FOutcome FStatusHeaders::Parse()`

#### class `UE::IoStore::HTTP::DetailOne::FBody`  
`class FBody : public FStatusHeaders`  
_L513-542_
- inherits: `FStatusHeaders`
- L519 _public prototype_ `int64 GetRemaining() const;`
- L520 _public prototype_ `FOutcome TryRecv(FMutableMemoryView Dest, FTlsPeer& Peer);`
- L525 _private prototype_ `FOutcome Gather(FMutableMemoryView Dest, FTlsPeer& Peer);`
- L526 _private prototype_ `FOutcome Init(FMutableMemoryView Dest, FTlsPeer& Peer);`
- L527 _private prototype_ `FOutcome Recv(FMutableMemoryView Dest, FTlsPeer& Peer);`
- L528 _private prototype_ `FOutcome Prologue(FMutableMemoryView Dest, FTlsPeer& Peer);`
- L529 _private prototype_ `FOutcome Chunk(FMutableMemoryView Dest, FTlsPeer& Peer);`
- L530 _private prototype_ `FOutcome Epilogue(FMutableMemoryView Dest, FTlsPeer& Peer);`
- L531 _private member_ `FMemoryView Overspill;`
- L532 _private member_ `FMutableMemoryView Scratch;`
- L533 _private member_ `int64 Remaining = 0;`
- L534 _private member_ `EState State = EState::Init;`
- L545 _function_ `int64 FBody::GetRemaining() const`
- L551 _function_ `FOutcome FBody::TryRecv(FMutableMemoryView Dest, FTlsPeer& Peer)`
- L577 _function_ `FOutcome FBody::Gather(FMutableMemoryView Dest, FTlsPeer& Peer)`
- L614 _function_ `FOutcome FBody::Init(FMutableMemoryView Dest, FTlsPeer& Peer)`
- L648 _function_ `FOutcome FBody::Recv(FMutableMemoryView Dest, FTlsPeer& Peer)`
- L702 _function_ `FOutcome FBody::Prologue(FMutableMemoryView Dest, FTlsPeer& Peer)`
- L810 _function_ `FOutcome FBody::Chunk(FMutableMemoryView Dest, FTlsPeer& Peer)`
- L830 _function_ `FOutcome FBody::Epilogue(FMutableMemoryView Dest, FTlsPeer& Peer)`

#### enum `UE::IoStore::HTTP::DetailOne::FBody::EState`  
`enum class EState : uint8`  
_L523-523_
- L523 _public enumerator_ `enum class EState : uint8 { Init, Recv, Prologue, Chunk, Epilogue, Done }; FOutcome Gather(FMutableMemoryView Dest, FTlsPeer& Peer); FOutcome Init(FMutableMemoryView Dest, FTlsPeer& Peer); FOutcome Recv(FMutableMemoryView Dest, FTlsPeer& Peer); FOutcome Prologue(FMutableMemoryView Dest, FTlsPeer& Peer); FOutcome Chunk(FMutableMemoryView Dest, FTlsPeer& Peer); FOutcome Epilogue(FMutableMemoryView Dest, FTlsPeer& Peer);`
- L523 _public enumerator_ `enum class EState : uint8 { Init, Recv, Prologue, Chunk, Epilogue, Done }; FOutcome Gather(FMutableMemoryView Dest, FTlsPeer& Peer); FOutcome Init(FMutableMemoryView Dest, FTlsPeer& Peer); FOutcome Recv(FMutableMemoryView Dest, FTlsPeer& Peer); FOutcome Prologue(FMutableMemoryView Dest, FTlsPeer& Peer); FOutcome Chunk(FMutableMemoryView Dest, FTlsPeer& Peer); FOutcome Epilogue(FMutableMemoryView Dest, FTlsPeer& Peer);`
- L523 _public enumerator_ `enum class EState : uint8 { Init, Recv, Prologue, Chunk, Epilogue, Done }; FOutcome Gather(FMutableMemoryView Dest, FTlsPeer& Peer); FOutcome Init(FMutableMemoryView Dest, FTlsPeer& Peer); FOutcome Recv(FMutableMemoryView Dest, FTlsPeer& Peer); FOutcome Prologue(FMutableMemoryView Dest, FTlsPeer& Peer); FOutcome Chunk(FMutableMemoryView Dest, FTlsPeer& Peer); FOutcome Epilogue(FMutableMemoryView Dest, FTlsPeer& Peer);`
- L523 _public enumerator_ `enum class EState : uint8 { Init, Recv, Prologue, Chunk, Epilogue, Done }; FOutcome Gather(FMutableMemoryView Dest, FTlsPeer& Peer); FOutcome Init(FMutableMemoryView Dest, FTlsPeer& Peer); FOutcome Recv(FMutableMemoryView Dest, FTlsPeer& Peer); FOutcome Prologue(FMutableMemoryView Dest, FTlsPeer& Peer); FOutcome Chunk(FMutableMemoryView Dest, FTlsPeer& Peer); FOutcome Epilogue(FMutableMemoryView Dest, FTlsPeer& Peer);`
- L523 _public enumerator_ `enum class EState : uint8 { Init, Recv, Prologue, Chunk, Epilogue, Done }; FOutcome Gather(FMutableMemoryView Dest, FTlsPeer& Peer); FOutcome Init(FMutableMemoryView Dest, FTlsPeer& Peer); FOutcome Recv(FMutableMemoryView Dest, FTlsPeer& Peer); FOutcome Prologue(FMutableMemoryView Dest, FTlsPeer& Peer); FOutcome Chunk(FMutableMemoryView Dest, FTlsPeer& Peer); FOutcome Epilogue(FMutableMemoryView Dest, FTlsPeer& Peer);`
- L523 _public enumerator_ `enum class EState : uint8 { Init, Recv, Prologue, Chunk, Epilogue, Done }; FOutcome Gather(FMutableMemoryView Dest, FTlsPeer& Peer); FOutcome Init(FMutableMemoryView Dest, FTlsPeer& Peer); FOutcome Recv(FMutableMemoryView Dest, FTlsPeer& Peer); FOutcome Prologue(FMutableMemoryView Dest, FTlsPeer& Peer); FOutcome Chunk(FMutableMemoryView Dest, FTlsPeer& Peer); FOutcome Epilogue(FMutableMemoryView Dest, FTlsPeer& Peer);`

#### enum `UE::IoStore::HTTP::DetailOne::FBody::(anonymous)`  
``  
_L537-541_

#### class `UE::IoStore::HTTP::FTransactionOne`  
`class FTransactionOne : public DetailOne::FBody`  
_L870-875_
- inherits: `DetailOne::FBody`

#### class `UE::IoStore::HTTP::FTransaction`  
`class FTransaction`  
_L899-939_
- L926 _private function_ `void Destruct()`

#### class `UE::IoStore::HTTP::FTransactRef`  
`class FTransactRef`  
_L944-962_
- L947 _public prototype_ `FTransactRef() = default;`
- L948 _public prototype_ `~FTransactRef();`
- L949 _public prototype_ `FTransactRef(UPTRINT Ptr, int32 Ver);`
- L950 _public prototype_ `FTransactRef(FTransactRef&&) = delete;`
- L951 _public prototype_ `FTransactRef(const FTransactRef&) = delete;`
- L952 _public prototype_ `void operator = (const FTransactRef& Rhs) = delete;`
- L953 _public prototype_ `void operator = (FTransactRef&& Rhs);`
- L954 _public prototype_ `const FTransaction* operator -> () const;`
- L955 _public prototype_ `FTransaction* operator -> ();`
- L956 _public prototype_ `bool IsValid() const;`
- L959 _private prototype_ `const FTransaction* Get() const;`
- L960 _private prototype_ `FTransaction* Get();`
- L961 _private member_ `UPTRINT Self = 0;`
- L965 _function_ `FTransactRef::FTransactRef(UPTRINT Ptr, int32 Ver) : Self(Ptr | (Ver == 2))`
- L972 _function_ `void FTransactRef::operator = (FTransactRef&& Rhs)`
- L978 _function_ `const FTransaction* FTransactRef::operator -> () const`
- L984 _function_ `FTransaction* FTransactRef::operator -> ()`
- L990 _function_ `bool FTransactRef::IsValid() const`
- L996 _function_ `const FTransaction* FTransactRef::Get() const`
- L1002 _function_ `FTransaction* FTransactRef::Get()`
- L1008 _function_ `FTransactRef::~FTransactRef()`

#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace IoStore` (scope `UE`)
- L5 _namespace_ `namespace HTTP` (scope `UE::IoStore`)
- L16 _function_ `static int32 ParseMessage(FAnsiStringView Message, FMessageOffsets& Out)` (scope `UE::IoStore::HTTP`)
- L77 _function_ `template <typename LambdaType> static void EnumerateHeaders(FAnsiStringView Headers, LambdaType&& Lambda)` (scope `UE::IoStore::HTTP`)
- L82 _function_ `auto IsOws = [] (int32 c)` (scope `UE::IoStore::HTTP::EnumerateHeaders`)
- L132 _namespace_ `namespace DetailOne` (scope `UE::IoStore::HTTP`)
- L365 _function_ `` (scope `UE::IoStore::HTTP::DetailOne::FStatusHeaders::TryRecvResponse`)
- L456 _function_ `` (scope `UE::IoStore::HTTP::DetailOne::FStatusHeaders::Parse`)
- L538 _enumerator_ `HeaderBufSize = 32` (scope `UE::IoStore::HTTP::DetailOne::FBody::__anon5c7414cb0403`)
- L539 _enumerator_ `CrLfLength = 2` (scope `UE::IoStore::HTTP::DetailOne::FBody::__anon5c7414cb0403`)
- L540 _enumerator_ `EndOfXfer = -1` (scope `UE::IoStore::HTTP::DetailOne::FBody::__anon5c7414cb0403`)
- L705 _function_ `` (scope `UE::IoStore::HTTP::DetailOne::FBody::Prologue`)
- L880 _function_ `FOutcome HandshakeOne(FTlsPeer&, void*)` (scope `UE::IoStore::HTTP`)
- L886 _function_ `FOutcome TickOne(FTlsPeer&, void*)` (scope `UE::IoStore::HTTP`)
- L892 _function_ `void GoAwayOne(FTlsPeer&, void*)` (scope `UE::IoStore::HTTP`)
- L902 _macro_ `#define TR_METHOD(x, ...) \`
- L1021 _function_ `FTransactRef CreateTransactOne(void*&)` (scope `UE::IoStore::HTTP`)
- L1029 _function_ `FTransactRef CreateTransactTwo(void* PeerData)` (scope `UE::IoStore::HTTP`)

### `Source/Runtime/Experimental/IoStore/HttpClient/Private/TransactionTwo.inl` (Private)


#### enum `UE::IoStore::HTTP::IsStatusCodeOk::(anonymous)`  
`enum`  
_L20-20_

#### enum `UE::IoStore::HTTP::DetailTwo::(anonymous)`  
`enum`  
_L69-69_

#### struct `UE::IoStore::HTTP::DetailTwo::FFrame`  
`struct FFrame`  
_L72-105_
- L96 _public member_ `uint8 Size[3];`
- L97 _public member_ `EType Type;`
- L98 _public member_ `uint8 Flags;`
- L99 _public member_ `uint8 Id[4];`
- L101 _public function_ `int32 IsPertinent() const`
- L102 _public function_ `uint32 GetSize() const`
- L103 _public function_ `uint32 GetId() const`
- L104 _public function_ `uint32 GetIdFast() const`

#### enum `UE::IoStore::HTTP::DetailTwo::FFrame::EType`  
`enum class EType : uint8`  
_L74-87_
- L76 _public enumerator_ `Data` — = 0x00,
- L77 _public enumerator_ `Headers` — = 0x01,
- L78 _public enumerator_ `Priority` — = 0x02,
- L79 _public enumerator_ `RstStream` — = 0x03,
- L80 _public enumerator_ `Settings` — = 0x04,
- L81 _public enumerator_ `PushPromise` — = 0x05,
- L82 _public enumerator_ `Ping` — = 0x06,
- L83 _public enumerator_ `Goaway` — = 0x07,
- L84 _public enumerator_ `WindowUpdate` — = 0x08,
- L85 _public enumerator_ `Continuation` — = 0x09,
- L86 _public enumerator_ `_Num`

#### enum `UE::IoStore::HTTP::DetailTwo::FFrame::(anonymous)`  
``  
_L90-94_

#### class `UE::IoStore::HTTP::DetailTwo::FBufferNg`  
`class FBufferNg`  
_L111-131_
- L114 _public prototype_ `FBufferNg() = default;`
- L115 _public function_ `~FBufferNg()`
- L116 _public function_ `FBufferNg(nghttp2_rcbuf* InRcBuf)`
- L117 _public function_ `FBufferNg(FBufferNg&& Rhs)`
- L118 _public prototype_ `FBufferNg(const FBufferNg&) = delete;`
- L119 _public function_ `FBufferNg& operator = (FBufferNg&& Rhs)`
- L120 _public prototype_ `FBufferNg& operator = (const FBufferNg&) = delete;`
- L122 _public function_ `FAnsiStringView Get() const`
- L130 _private member_ `nghttp2_rcbuf* Inner = nullptr;`

#### struct `UE::IoStore::HTTP::DetailTwo::FHeaderNg`  
`struct FHeaderNg`  
_L134-138_
- L136 _public member_ `FBufferNg Key;`
- L137 _public member_ `FBufferNg Value;`

#### class `UE::IoStore::HTTP::DetailTwo::FDriverHeaders`  
`class FDriverHeaders`  
_L143-157_
- L146 _public prototype_ `FDriverHeaders() = default;`
- L147 _public prototype_ `void Add(FAnsiStringView Key, FAnsiStringView Value);`
- L152 _private function_ `const nghttp2_nv* GetData() const`
- L153 _private function_ `int32 Num() const`
- L154 _private member_ `TArray<nghttp2_nv> Headers;`
- L160 _function_ `void FDriverHeaders::Add(FAnsiStringView Key, FAnsiStringView Value)`

#### class `UE::IoStore::HTTP::DetailTwo::FDriverNg`  
`class FDriverNg`  
_L175-209_
- L178 _public prototype_ `FDriverNg(FTlsPeer& Peer);`
- L179 _public prototype_ `bool IsUsingTls() const;`
- L180 _public prototype_ `void GoAway(FTlsPeer& Peer);`
- L181 _public prototype_ `FOutcome Handshake(FTlsPeer& Peer);`
- L182 _public prototype_ `FOutcome GetTransactId(FTlsPeer& Peer);`
- L183 _public prototype_ `FTransactId Submit(const FDriverHeaders& Headers);`
- L184 _public prototype_ `FOutcome Send(FTlsPeer& Peer);`
- L185 _public prototype_ `FOutcome RecvResponse(FTlsPeer& Peer, TArray<FHeaderNg>* Sink);`
- L186 _public prototype_ `FOutcome RecvBody(FTlsPeer& Peer, FMutableMemoryView Dest);`
- L187 _public prototype_ `bool CancelTransaction(FTlsPeer& Peer, FTransactId Id);`
- L188 _public prototype_ `void SkipTransaction();`
- L191 _private prototype_ `FOutcome Tick(FTlsPeer& Peer);`
- L192 _private prototype_ `FOutcome TickInner(FTlsPeer& Peer);`
- L193 _private prototype_ `FOutcome PumpSend(FTlsPeer& Peer);`
- L194 _private prototype_ `FOutcome PumpRecv(FTlsPeer& Peer, FMemoryView Data);`
- L195 _private prototype_ `int32 OnHeader(nghttp2_rcbuf* Name, nghttp2_rcbuf* Value);`
- L196 _private member_ `nghttp2_session* Session;`
- L197 _private member_ `TArray<FHeaderNg>* ResponseHeaders = nullptr;`
- L198 _private member_ `FMemoryView SendPending;`
- L199 _private member_ `int32 RecvRemaining;`
- L200 _private member_ `bool bWithTls;`
- L201 _private member_ `uint8 RecvBuffer[512 - sizeof(FFrame)];`
- L212 _function_ `FDriverNg::FDriverNg(FTlsPeer& Peer) : bWithTls(Peer.IsUsingTls())`
- L257 _function_ `void FDriverNg::GoAway(FTlsPeer& Peer)`
- L271 _function_ `bool FDriverNg::IsUsingTls() const`
- L277 _function_ `FOutcome FDriverNg::PumpSend(FTlsPeer& Peer)`
- L325 _function_ `FOutcome FDriverNg::PumpRecv(FTlsPeer& Peer, FMemoryView Data)`
- L351 _function_ `FOutcome FDriverNg::Handshake(FTlsPeer& Peer)`
- L365 _function_ `FOutcome FDriverNg::GetTransactId(FTlsPeer& Peer)`
- L377 _function_ `FOutcome FDriverNg::Tick(FTlsPeer& Peer)`
- L390 _function_ `FOutcome FDriverNg::TickInner(FTlsPeer& Peer)`
- L468 _function_ `FTransactId FDriverNg::Submit(const FDriverHeaders& Headers)`
- L475 _function_ `FOutcome FDriverNg::Send(FTlsPeer& Peer)`
- L481 _function_ `FOutcome FDriverNg::RecvResponse(FTlsPeer& Peer, TArray<FHeaderNg>* Sink)`
- L566 _function_ `FOutcome FDriverNg::RecvBody(FTlsPeer& Peer, FMutableMemoryView Dest)`
- L638 _function_ `bool FDriverNg::CancelTransaction(FTlsPeer& Peer, FTransactId Id)`
- L651 _function_ `void FDriverNg::SkipTransaction()`
- L662 _function_ `int32 FDriverNg::OnHeader(nghttp2_rcbuf* Name, nghttp2_rcbuf* Value)`

#### union `UE::IoStore::HTTP::DetailTwo::FDriverNg::(anonymous)`  
``  
_L203-206_

#### struct `UE::IoStore::HTTP::DetailTwo::FDriverNg::FDriverNg::FStaticsNg`  
`struct FStaticsNg`  
_L215-222_
- L217 _public function_ `~FStaticsNg()`
- L221 _public member_ `nghttp2_session_callbacks* Instance = nullptr;`

#### class `UE::IoStore::HTTP::DetailTwo::FBase`  
`class FBase`  
_L677-687_
- L680 _public prototype_ `FBase(FDriverNg& InDriver);`
- L683 _protected prototype_ `FDriverNg& GetDriver();`
- L686 _private member_ `FDriverNg& Driver;`
- L690 _function_ `FBase::FBase(FDriverNg& InDriver) : Driver(InDriver)`
- L696 _function_ `FDriverNg& FBase::GetDriver()`

#### class `UE::IoStore::HTTP::DetailTwo::FRequest`  
`class FRequest : public FBase`  
_L704-721_
- inherits: `FBase`
- L710 _public prototype_ `void Begin(FAnsiStringView Host, FAnsiStringView Method, FAnsiStringView Path);`
- L711 _public prototype_ `void AddHeader(FAnsiStringView Key, FAnsiStringView Value);`
- L712 _public prototype_ `FTransactId End(bool bKeepAlive);`
- L713 _public prototype_ `FOutcome TrySendRequest(FTlsPeer& Peer);`
- L716 _protected prototype_ `FTransactId GetTransactId() const;`
- L719 _private member_ `FDriverHeaders RequestHeaders;`
- L720 _private member_ `FTransactId Id;`
- L724 _function_ `void FRequest::Begin(FAnsiStringView Host, FAnsiStringView Method, FAnsiStringView Path)`
- L734 _function_ `void FRequest::AddHeader(FAnsiStringView Key, FAnsiStringView Value)`
- L751 _function_ `FTransactId FRequest::GetTransactId() const`
- L757 _function_ `FTransactId FRequest::End(bool )`
- L764 _function_ `FOutcome FRequest::TrySendRequest(FTlsPeer& Peer)`

#### class `UE::IoStore::HTTP::DetailTwo::FStatusHeaders`  
`class FStatusHeaders : public FRequest`  
_L772-790_
- inherits: `FRequest`
- L778 _public prototype_ `FOutcome TryRecvResponse(FTlsPeer& Peer);`
- L779 _public prototype_ `bool IsKeepAlive() const;`
- L780 _public prototype_ `uint32 GetStatusCode() const;`
- L781 _public prototype_ `FAnsiStringView GetStatusMessage() const;`
- L782 _public prototype_ `int64 GetContentLength() const;`
- L783 _public prototype_ `bool IsChunked() const;`
- L784 _public prototype_ `void ReadHeaders(FResponse::FHeaderSink Sink) const;`
- L787 _private member_ `TArray<FHeaderNg> ResponseHeaders;`
- L788 _private member_ `int64 ContentLength = -1;`
- L789 _private member_ `uint32 StatusCode = 0;`
- L793 _function_ `bool FStatusHeaders::IsKeepAlive() const`
- L799 _function_ `uint32 FStatusHeaders::GetStatusCode() const`
- L805 _function_ `FAnsiStringView FStatusHeaders::GetStatusMessage() const`
- L811 _function_ `int64 FStatusHeaders::GetContentLength() const`
- L817 _function_ `bool FStatusHeaders::IsChunked() const`
- L823 _function_ `void FStatusHeaders::ReadHeaders(FResponse::FHeaderSink Sink) const`
- L837 _function_ `FOutcome FStatusHeaders::TryRecvResponse(FTlsPeer& Peer)`

#### enum `UE::IoStore::HTTP::DetailTwo::FStatusHeaders::TryRecvResponse::(anonymous)`  
`enum : uint32`  
_L845-849_

#### class `UE::IoStore::HTTP::DetailTwo::FBody`  
`class FBody : public FStatusHeaders`  
_L889-900_
- inherits: `FStatusHeaders`
- L895 _public prototype_ `int64 GetRemaining() const;`
- L896 _public prototype_ `FOutcome TryRecv(FMutableMemoryView Dest, FTlsPeer& Peer);`
- L899 _private member_ `int64 Remaining = -1;`
- L903 _function_ `int64 FBody::GetRemaining() const`
- L909 _function_ `FOutcome FBody::TryRecv(FMutableMemoryView Dest, FTlsPeer& Peer)`

#### class `UE::IoStore::HTTP::FTransactionTwo`  
`class FTransactionTwo : public DetailTwo::FBody`  
_L935-940_
- inherits: `DetailTwo::FBody`
- L1023 _public function_ `void Begin(...)`
- L1024 _public function_ `void AddHeader(...)`
- L1025 _public function_ `FTransactId End(...)`
- L1026 _public function_ `FOutcome TrySendRequest(FTlsPeer&)`
- L1027 _public function_ `FOutcome TryRecvResponse(FTlsPeer&)`
- L1028 _public function_ `bool IsKeepAlive() const`
- L1029 _public function_ `uint32 GetStatusCode() const`
- L1030 _public function_ `FAnsiStringView GetStatusMessage() const`
- L1031 _public function_ `int64 GetContentLength() const`
- L1032 _public function_ `bool IsChunked() const`
- L1033 _public function_ `int64 GetRemaining() const`
- L1034 _public function_ `void ReadHeaders(FResponse::FHeaderSink) const`
- L1035 _public function_ `FOutcome TryRecv(FMutableMemoryView, FTlsPeer&)`

#### class `UE::IoStore::HTTP::FTransactionTwo`  
`class FTransactionTwo`  
_L1020-1036_
- L1023 _public function_ `void Begin(...)`
- L1024 _public function_ `void AddHeader(...)`
- L1025 _public function_ `FTransactId End(...)`
- L1026 _public function_ `FOutcome TrySendRequest(FTlsPeer&)`
- L1027 _public function_ `FOutcome TryRecvResponse(FTlsPeer&)`
- L1028 _public function_ `bool IsKeepAlive() const`
- L1029 _public function_ `uint32 GetStatusCode() const`
- L1030 _public function_ `FAnsiStringView GetStatusMessage() const`
- L1031 _public function_ `int64 GetContentLength() const`
- L1032 _public function_ `bool IsChunked() const`
- L1033 _public function_ `int64 GetRemaining() const`
- L1034 _public function_ `void ReadHeaders(FResponse::FHeaderSink) const`
- L1035 _public function_ `FOutcome TryRecv(FMutableMemoryView, FTlsPeer&)`

#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace IoStore` (scope `UE`)
- L5 _namespace_ `namespace HTTP` (scope `UE::IoStore`)
- L9 _typedef_ `using FTransactId = uint32;` (scope `UE::IoStore::HTTP`)
- L12 _function_ `bool IsContentless(uint32 StatusCode)` (scope `UE::IoStore::HTTP`)
- L18 _function_ `bool IsStatusCodeOk(uint32 StatusCode)` (scope `UE::IoStore::HTTP`)
- L20 _enumerator_ `enum { MinCode = 100, MaxCode = 999 }; return uint32(StatusCode - MinCode) <= uint32(MaxCode - MinCode);` (scope `UE::IoStore::HTTP::IsStatusCodeOk::__anonf30aa7430103`)
- L20 _enumerator_ `enum { MinCode = 100, MaxCode = 999 }; return uint32(StatusCode - MinCode) <= uint32(MaxCode - MinCode);` (scope `UE::IoStore::HTTP::IsStatusCodeOk::__anonf30aa7430103`)
- L30 _macro_ `# define WITH_NGHTTP2 0`
- L34 _macro_ `# define WITH_NGHTTP2 1`
- L40 _macro_ `# define IAS_HTTP_WITH_TWO WITH_NGHTTP2`
- L47 _macro_ `# define NGHTTP2_NO_SSIZE_T`
- L50 _macro_ `# define NGHTTP2_STATICLIB`
- L62 _namespace_ `namespace UE`
- L62 _namespace_ `namespace IoStore` (scope `UE`)
- L62 _namespace_ `namespace HTTP` (scope `UE::IoStore`)
- L65 _namespace_ `namespace DetailTwo` (scope `UE::IoStore::HTTP`)
- L69 _enumerator_ `enum { RECV_WINDOW_SIZE = 1024 << 10 }; struct FFrame { enum class EType : uint8 { Data,` (scope `UE::IoStore::HTTP::DetailTwo::__anonf30aa7430203`)
- L91 _enumerator_ `Flag_Padding = 0x08` (scope `UE::IoStore::HTTP::DetailTwo::FFrame::__anonf30aa7430303`)
- L92 _enumerator_ `Flag_EndHeaders = 0x04` (scope `UE::IoStore::HTTP::DetailTwo::FFrame::__anonf30aa7430303`)
- L93 _enumerator_ `Flag_EndStream = 0x01` (scope `UE::IoStore::HTTP::DetailTwo::FFrame::__anonf30aa7430303`)
- L204 _member_ `FFrame RecvFrame;` (scope `UE::IoStore::HTTP::DetailTwo::FDriverNg::__anonf30aa743040a`)
- L205 _member_ `uint8 RecvFrameData[sizeof(RecvFrame)];` (scope `UE::IoStore::HTTP::DetailTwo::FDriverNg::__anonf30aa743040a`)
- L233 _function_ `` (scope `UE::IoStore::HTTP::DetailTwo::FDriverNg::FDriverNg`)
- L244 _function_ `.mem_user_data = nullptr, .malloc = [] (size_t Size, void*)` (scope `UE::IoStore::HTTP::DetailTwo::FDriverNg::FDriverNg`)
- L247 _function_ `.malloc = [] (size_t Size, void*)` (scope `UE::IoStore::HTTP::DetailTwo::FDriverNg::FDriverNg`)
- L846 _enumerator_ `Flag_Code = 1 << 0` (scope `UE::IoStore::HTTP::DetailTwo::FStatusHeaders::TryRecvResponse::__anonf30aa7430a03`)
- L847 _enumerator_ `Flag_Length = 1 << 1` (scope `UE::IoStore::HTTP::DetailTwo::FStatusHeaders::TryRecvResponse::__anonf30aa7430a03`)
- L848 _enumerator_ `Flag_All = Flag_Code | Flag_Length` (scope `UE::IoStore::HTTP::DetailTwo::FStatusHeaders::TryRecvResponse::__anonf30aa7430a03`)
- L945 _function_ `FOutcome HandshakeTwo(FTlsPeer& Peer, void*& PeerData)` (scope `UE::IoStore::HTTP`)
- L959 _function_ `FOutcome TickTwo(FTlsPeer& Peer, void* PeerData)` (scope `UE::IoStore::HTTP`)
- L973 _function_ `bool CancelTwo(FTlsPeer& Peer, void* PeerData, FTransactId Id)` (scope `UE::IoStore::HTTP`)
- L987 _function_ `void SkipPendingTransactTwo(FTlsPeer&, void* PeerData)` (scope `UE::IoStore::HTTP`)
- L999 _function_ `void GoAwayTwo(FTlsPeer& Peer, void* PeerData)` (scope `UE::IoStore::HTTP`)
- L1018 _namespace_ `namespace UE`
- L1018 _namespace_ `namespace IoStore` (scope `UE`)
- L1018 _namespace_ `namespace HTTP` (scope `UE::IoStore`)
- L1038 _function_ `FOutcome HandshakeTwo(FTlsPeer&, void*&)` (scope `UE::IoStore::HTTP`)
- L1039 _function_ `FOutcome TickTwo(FTlsPeer&, void*)` (scope `UE::IoStore::HTTP`)
- L1040 _function_ `bool CancelTwo(FTlsPeer&, void*, FTransactId)` (scope `UE::IoStore::HTTP`)
- L1041 _function_ `void SkipPendingTransactTwo(FTlsPeer&, void*)` (scope `UE::IoStore::HTTP`)
- L1042 _function_ `void GoAwayTwo(FTlsPeer&, void*)` (scope `UE::IoStore::HTTP`)
