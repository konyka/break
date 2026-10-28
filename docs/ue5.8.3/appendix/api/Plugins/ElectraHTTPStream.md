# Plugins / ElectraHTTPStream

- module root: `Plugins/Media/ElectraUtil/Source/ElectraHTTPStream`
- headers: 10; symbols: 240
- symbol kinds: class=9, delegate=3, enum=3, enumerator=15, function=73, macro=1, member=42, namespace=2, prototype=86, struct=3, typedef=3
- PrivateDependencyModuleNames: ElectraBase, HTTP
- PublicDependencyModuleNames: Core

### `Plugins/Media/ElectraUtil/Source/ElectraHTTPStream/Private/ElectraHTTPStreamModule.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogElectraHTTPStream, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogElectraHTTPStream, Log, All);`

### `Plugins/Media/ElectraUtil/Source/ElectraHTTPStream/Private/ElectraHTTPStreamResponse.h` (Private)


#### class `FElectraHTTPStreamResponse`  
`class FElectraHTTPStreamResponse : public IElectraHTTPStreamResponse`  
_L15-181_
- inherits: `IElectraHTTPStreamResponse`
- L18 _public prototype_ `FElectraHTTPStreamResponse() = default;`
- L19 _public prototype_ `virtual ~FElectraHTTPStreamResponse() = default;`
- L21 _public function_ `EStatus GetStatus() override`
- L24 _public function_ `EState GetState() override`
- L27 _public function_ `FString GetErrorMessage() override`
- L33 _public function_ `int32 GetHTTPResponseCode() override`
- L36 _public function_ `int64 GetNumResponseBytesReceived() override`
- L39 _public function_ `int64 GetNumRequestBytesSent() override`
- L42 _public function_ `FString GetEffectiveURL() override`
- L45 _public function_ `void GetAllHeaders(TArray<FElectraHTTPStreamHeader>& OutHeaders) override`
- L48 _public function_ `FString GetHTTPStatusLine() override`
- L50 _public function_ `FString GetContentLengthHeader() override`
- L52 _public function_ `FString GetContentRangeHeader() override`
- L54 _public function_ `FString GetAcceptRangesHeader() override`
- L56 _public function_ `FString GetTransferEncodingHeader() override`
- L58 _public function_ `FString GetContentTypeHeader() override`
- L61 _public function_ `IElectraHTTPStreamBuffer& GetResponseData() override`
- L64 _public function_ `double GetTimeElapsed() override`
- L67 _public function_ `double GetTimeSinceLastDataArrived() override`
- L70 _public function_ `double GetTimeUntilNameResolved() override`
- L72 _public function_ `double GetTimeUntilConnected() override`
- L74 _public function_ `double GetTimeUntilRequestSent() override`
- L76 _public function_ `double GetTimeUntilHeadersAvailable() override`
- L78 _public function_ `double GetTimeUntilFirstByte() override`
- L80 _public function_ `double GetTimeUntilFinished() override`
- L83 _public function_ `int32 GetTimingTraces(TArray<FTimingTrace>* OutTraces, int32 InNumToRemove) override`
- L100 _public function_ `void SetEnableTimingTraces() override`
- L107 _public function_ `template<typename T> void AddTrace(T InNewData, bool bAddTrace)`
- L121 _public function_ `void AddResponseData(const TArray<uint8>& InNewData, bool bAddTrace=true)`
- L126 _public function_ `void AddResponseData(TArray<uint8>&& InNewData, bool bAddTrace=true)`
- L131 _public function_ `void AddResponseData(const TConstArrayView<const uint8>& InNewData, bool bAddTrace=true)`
- L138 _public function_ `void SetEOS()`
- L141 _public function_ `void SetErrorMessage(const FString& InErrorMessage)`
- L147 _public member_ `EStatus CurrentStatus = EStatus::NotRunning;`
- L148 _public member_ `EState CurrentState = EState::Connecting;`
- L150 _public member_ `TArray<FElectraHTTPStreamHeader> ResponseHeaders;`
- L151 _public member_ `FString ContentLength;`
- L152 _public member_ `FString ContentRange;`
- L153 _public member_ `FString AcceptRanges;`
- L154 _public member_ `FString TransferEncoding;`
- L155 _public member_ `FString ContentType;`
- L157 _public member_ `FString HTTPStatusLine;`
- L158 _public member_ `FString EffectiveURL;`
- L159 _public member_ `int32 HTTPResponseCode = 0;`
- L161 _public member_ `FElectraHTTPStreamBuffer ResponseData;`
- L164 _public member_ `double StartTime = 0.0;` — Timing
- L165 _public member_ `double TimeUntilNameResolved = 0.0;`
- L166 _public member_ `double TimeUntilConnected = 0.0;`
- L167 _public member_ `double TimeUntilRequestSent = 0.0;`
- L168 _public member_ `double TimeUntilHeadersAvailable = 0.0;`
- L169 _public member_ `double TimeUntilFirstByte = 0.0;`
- L170 _public member_ `double TimeUntilFinished = 0.0;`
- L171 _public member_ `double TimeOfMostRecentReceive = 0.0;`
- L173 _public member_ `FCriticalSection Lock;`
- L176 _public member_ `FString ErrorMessage;` — Error message.
- L179 _public member_ `TArray<FTimingTrace> TimingTraces;` — Timing traces.
- L180 _public member_ `bool bCollectTimingTraces = false;`

### `Plugins/Media/ElectraUtil/Source/ElectraHTTPStream/Private/Generic/GenericElectraHTTPStream.h` (Private)


#### class `FPlatformElectraHTTPStreamGeneric`  
`class FPlatformElectraHTTPStreamGeneric`  
_L13-19_
- L16 _public prototype_ `static void Startup();`
- L17 _public prototype_ `static void Shutdown();`
- L18 _public prototype_ `static TSharedPtr<IElectraHTTPStream, ESPMode::ThreadSafe> Create(const Electra::FParamDict& InOptions);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ELECTRAHTTPSTREAM_API`
- L21 _typedef_ `typedef FPlatformElectraHTTPStreamGeneric FPlatformElectraHTTPStream;`

### `Plugins/Media/ElectraUtil/Source/ElectraHTTPStream/Private/Utilities/DefaultHttpUserAgent.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace ElectraHTTPStream`
- L10 _prototype_ `FString GetDefaultUserAgent();` (scope `ElectraHTTPStream`)

### `Plugins/Media/ElectraUtil/Source/ElectraHTTPStream/Private/Utilities/TimeWaitableSignal.h` (Private)


#### class `FTimeWaitableSignal`  
`class FTimeWaitableSignal`  
_L11-75_
- L14 _public function_ `FTimeWaitableSignal() : Event(FPlatformProcess::GetSynchEventFromPool(true))`
- L17 _public function_ `~FTimeWaitableSignal()`
- L23 _public function_ `void Wait()`
- L28 _public function_ `void WaitAndReset()`
- L34 _public function_ `void Signal()`
- L39 _public function_ `void Reset()`
- L44 _public function_ `bool IsSignaled()`
- L49 _public function_ `bool WaitTimeout(int32 MilliSeconds)`
- L54 _public function_ `bool WaitTimeoutAndReset(int32 MilliSeconds)`
- L73 _private member_ `FEvent* Event;`

### `Plugins/Media/ElectraUtil/Source/ElectraHTTPStream/Public/ElectraHTTPStream.h` (Public)


#### class `IElectraHTTPStreamBuffer`  
`class IElectraHTTPStreamBuffer`  
_L16-50_
- L19 _public prototype_ `IElectraHTTPStreamBuffer() = default;`
- L20 _public prototype_ `IElectraHTTPStreamBuffer(const IElectraHTTPStreamBuffer&) = delete;`
- L21 _public prototype_ `IElectraHTTPStreamBuffer& operator=(const IElectraHTTPStreamBuffer&) = delete;`
- L22 _public prototype_ `virtual ~IElectraHTTPStreamBuffer() = default;`
- L24 _public prototype_ `virtual void AddData(const TArray<uint8>& InNewData) = 0;`
- L25 _public prototype_ `virtual void AddData(TArray<uint8>&& InNewData) = 0;`
- L26 _public prototype_ `virtual void AddData(const TConstArrayView<const uint8>& InNewData) = 0;`
- L27 _public prototype_ `virtual void AddData(const IElectraHTTPStreamBuffer& Other, int64 Offset, int64 NumBytes) = 0;`
- L29 _public prototype_ `virtual int64 GetNumTotalBytesAdded() const = 0;`
- L30 _public prototype_ `virtual int64 GetNumTotalBytesHandedOut() const = 0;`
- L31 _public prototype_ `virtual int64 GetNumBytesAvailableForRead() const = 0;`
- L33 _public prototype_ `virtual void LockBuffer(const uint8*& OutNextReadAddress, int64& OutNumBytesAvailable) = 0;`
- L34 _public prototype_ `virtual void UnlockBuffer(int64 NumBytesConsumed) = 0;`
- L35 _public prototype_ `virtual bool RewindToBeginning() = 0;`
- L37 _public prototype_ `virtual bool GetEOS() const = 0;`
- L38 _public prototype_ `virtual void SetEOS() = 0;`
- L39 _public prototype_ `virtual void ClearEOS() = 0;`
- L41 _public prototype_ `virtual bool HasAllDataBeenConsumed() const = 0;`
- L43 _public prototype_ `virtual bool IsCachable() const = 0;`
- L44 _public prototype_ `virtual void SetIsCachable(bool bInIsCachable) = 0;`
- L46 _public prototype_ `virtual void SetLengthFromResponseHeader(int64 InLengthFromResponseHeader) = 0;`
- L47 _public prototype_ `virtual int64 GetLengthFromResponseHeader() const = 0;`
- L49 _public prototype_ `virtual void GetBaseBuffer(const uint8*& OutBaseAddress, int64& OutBytesInBuffer) = 0;`

#### enum `EElectraHTTPStreamNotificationReason`  
`enum class EElectraHTTPStreamNotificationReason`  
_L54-60_
- L56 _public enumerator_ `ReceivedHeaders`
- L57 _public enumerator_ `ReadData`
- L58 _public enumerator_ `WriteData`
- L59 _public enumerator_ `Completed`

#### struct `FElectraHTTPStreamHeader`  
`struct FElectraHTTPStreamHeader`  
_L64-68_
- L66 _public member_ `FString Header;`
- L67 _public member_ `FString Value;`

#### class `IElectraHTTPStreamResponse`  
`class IElectraHTTPStreamResponse`  
_L71-145_
- L74 _public prototype_ `virtual ~IElectraHTTPStreamResponse() = default;`
- L106 _public prototype_ `virtual EStatus GetStatus() = 0;`
- L107 _public prototype_ `virtual EState GetState() = 0;`
- L109 _public prototype_ `virtual FString GetErrorMessage() = 0;`
- L111 _public prototype_ `virtual int32 GetHTTPResponseCode() = 0;`
- L113 _public prototype_ `virtual int64 GetNumResponseBytesReceived() = 0;`
- L114 _public prototype_ `virtual int64 GetNumRequestBytesSent() = 0;`
- L116 _public prototype_ `virtual FString GetEffectiveURL() = 0;`
- L118 _public prototype_ `virtual void GetAllHeaders(TArray<FElectraHTTPStreamHeader>& OutHeaders) = 0;`
- L119 _public prototype_ `virtual FString GetHTTPStatusLine() = 0;`
- L120 _public prototype_ `virtual FString GetContentLengthHeader() = 0;`
- L121 _public prototype_ `virtual FString GetContentRangeHeader() = 0;`
- L122 _public prototype_ `virtual FString GetAcceptRangesHeader() = 0;`
- L123 _public prototype_ `virtual FString GetTransferEncodingHeader() = 0;`
- L124 _public prototype_ `virtual FString GetContentTypeHeader() = 0;`
- L126 _public prototype_ `virtual IElectraHTTPStreamBuffer& GetResponseData() = 0;`
- L128 _public prototype_ `virtual double GetTimeElapsed() = 0;`
- L129 _public prototype_ `virtual double GetTimeSinceLastDataArrived() = 0;`
- L132 _public prototype_ `virtual double GetTimeUntilNameResolved() = 0;` — Static timings as progressing through states.
- L133 _public prototype_ `virtual double GetTimeUntilConnected() = 0;`
- L134 _public prototype_ `virtual double GetTimeUntilRequestSent() = 0;`
- L135 _public prototype_ `virtual double GetTimeUntilHeadersAvailable() = 0;`
- L136 _public prototype_ `virtual double GetTimeUntilFirstByte() = 0;`
- L137 _public prototype_ `virtual double GetTimeUntilFinished() = 0;`
- L143 _public prototype_ `virtual int32 GetTimingTraces(TArray<FTimingTrace>* OutTraces, int32 InNumToRemove) = 0;` — Appends a copy of the timing traces to the provided array and optionally removes the first n elements. Pass a nullptr to only remove elements without copying them. This is useful to first get the traces and in a second call remove those that are no longer needed. Returns number appended or removed.
- L144 _public prototype_ `virtual void SetEnableTimingTraces() = 0;`

#### enum `IElectraHTTPStreamResponse::EStatus`  
`enum class EStatus`  
_L76-83_
- L78 _public enumerator_ `NotRunning`
- L79 _public enumerator_ `Running`
- L80 _public enumerator_ `Completed`
- L81 _public enumerator_ `Canceled`
- L82 _public enumerator_ `Failed`

#### enum `IElectraHTTPStreamResponse::EState`  
`enum class EState`  
_L86-94_
- desc: This enum needs to be kept in order of data flow so states can be compared with < and >
- L88 _public enumerator_ `Connecting`
- L89 _public enumerator_ `SendingRequestData`
- L90 _public enumerator_ `WaitingForResponseHeaders`
- L91 _public enumerator_ `ReceivedResponseHeaders`
- L92 _public enumerator_ `ReceivingResponseData`
- L93 _public enumerator_ `Finished`

#### struct `IElectraHTTPStreamResponse::FTimingTrace`  
`struct FTimingTrace`  
_L96-104_
- L99 _public member_ `double TimeSinceStart;` — Seconds since the request started.
- L101 _public member_ `int64 NumBytesAdded;` — Bytes added with the most recent chunk.
- L103 _public member_ `int64 TotalBytesAdded;` — Total bytes added to the buffer including the most recent chunk.

#### class `IElectraHTTPStreamRequest`  
`class IElectraHTTPStreamRequest`  
_L152-215_
- desc: HTTP request instance created by IElectraHTTPStream::CreateRequest()
- L155 _public prototype_ `virtual ~IElectraHTTPStreamRequest() = default;`
- L158 _public prototype_ `virtual void SetVerb(const FString& Verb) = 0;` — Set verb, GET, HEAD or POST. If not set GET is used by default.
- L161 _public prototype_ `virtual void EnableTimingTraces() = 0;` — Enables collection of timing traces. (disabled by default)
- L167 _public prototype_ `virtual IElectraHTTPStreamBuffer& POSTDataBuffer() = 0;` — Returns the buffer holding the data to be POSTed to the server. Make sure to include a suitable "Content-Type: xxx" header via AddHeader()
- L170 _public prototype_ `virtual void SetUserAgent(const FString& UserAgent) = 0;` — Sets a user agent for this request. If not specified an application specific default is used.
- L173 _public prototype_ `virtual void SetURL(const FString& URL) = 0;` — Sets the URL to issue the request to. Must not contain an URL fragment and must be appropriately escaped.
- L176 _public prototype_ `virtual void SetRange(const FString& Range) = 0;` — Sets a range for a GET request. Must be a valid range string.
- L179 _public prototype_ `virtual void AllowCompression(bool bAllowCompression) = 0;` — Allows for GET requests to return a compressed response using one of the platform supported algorithms.
- L182 _public prototype_ `virtual void AllowUnsafeRequestsForDebugging() = 0;` — Call this to allow unsafe connections for debugging purposes. Not enabled in shipping builds.
- L190 _public prototype_ `virtual void AddHeader(const FString& Header, const FString& Value, bool bAppendIfExists) = 0;` — Adds a request header. Only one header of a type is allowed. If one already exists it will be replaced with the new value unless bAppendIfExists is true which will append the value to the existing value with a ", " sequence. An existing header can be removed by passing an empty value with bAppendIfExists set to false. This may not be useful since you can always just not add the header to begin with.
- L198 _public prototype_ `virtual FElectraHTTPStreamNotificationDelegate& NotificationDelegate() = 0;` — Returns the notification delegate to which you bind a progress callback. This must be used only to add a delegate before adding the request for execution. Accessing this delegate while the request is running is not considered thread safe. Do not unbind your callback! Use Cancel() instead.
- L201 _public prototype_ `virtual void Cancel() = 0;` — Cancels the request and unbinds your notification delegate.
- L204 _public prototype_ `virtual IElectraHTTPStreamResponsePtr GetResponse() = 0;` — Returns the response object which is created with this request immediately and always accessible.
- L211 _public prototype_ `virtual bool HasFailed() = 0;` — Returns whether the request has failed. Please note that HTTP responses in the 4xx and 5xx range are not failures since a communication was established and a response was received. Such errors must be detected and handled by your application examining the response status!
- L214 _public prototype_ `virtual FString GetErrorMessage() = 0;` — Returns the reason the request has failed.

#### class `IElectraHTTPStream`  
`class IElectraHTTPStream`  
_L219-270_
- L225 _public prototype_ `static TSharedPtr<IElectraHTTPStream, ESPMode::ThreadSafe> Create(const Electra::FParamDict& InOptions);` — Creates an instance of the HTTP streamer class.
- L227 _public prototype_ `virtual ~IElectraHTTPStream() = default;`
- L235 _public prototype_ `DECLARE_DELEGATE(FElectraHTTPStreamThreadHandlerDelegate);` — Adds a method of your application to be called periodically from the worker thread of this handler. You may use this to drive another wrapping handler of yours that controls requests. For direct use of requests generated by this handler it is not necessary to add such a method. The NotificationDelegate() of the IElectraHTTPStreamRequestPtr request object should be all you need.
- L236 _public prototype_ `virtual void AddThreadHandlerDelegate(FElectraHTTPStreamThreadHandlerDelegate InDelegate) = 0;`
- L237 _public prototype_ `virtual void RemoveThreadHandlerDelegate() = 0;`
- L243 _public prototype_ `virtual void TriggerWorkSignal() = 0;` — Triggers a call to the registered handler delegate without waiting for the worker thread's timeout period.
- L249 _public prototype_ `virtual void Close() = 0;` — Closes this handler and all currently active or pending requests. This should be called before resetting the TSharedPtr<> returned by Create().
- L255 _public prototype_ `virtual IElectraHTTPStreamRequestPtr CreateRequest() = 0;` — Creates a request. Use the request object's methods to configure the request with the necessary parameters and then pass the request for execution to AddRequest().
- L269 _public prototype_ `virtual void AddRequest(IElectraHTTPStreamRequestPtr Request) = 0;` — Adds the request for execution. A strong reference of the request is kept internally while the request is running. It is an error to drop the request object without calling Request->Cancel() if there is a notification delegate bound to the request. The delegate will be called from a worker thread even if you have released the request because of the strong reference being held internally. If your delegate callback object has been destroyed it may result in a crash. You must hold on to the request until the callback signals completion or you have to call Cancel(). If the request fails the registered notification delegate will be invoked with the cause set to 'Completed' and the parameter set to 1. The error cause can be retrieved from the request via GetErrorMessage(). Please note that HTTP responses like 404, 503 etc. are not an error per se. Handling of such responses must be made by the caller.

#### Free symbols / members of external scopes

- L9 _typedef_ `using IElectraHTTPStreamRequestPtr = TSharedPtr<IElectraHTTPStreamRequest, ESPMode::ThreadSafe>;`
- L12 _typedef_ `using IElectraHTTPStreamResponsePtr = TSharedPtr<IElectraHTTPStreamResponse, ESPMode::ThreadSafe>;`
- L62 _delegate_ `DECLARE_DELEGATE_ThreeParams(FElectraHTTPStreamNotificationDelegate, IElectraHTTPStreamRequestPtr , EElectraHTTPStreamNotificationReason , int64 );`
- L62 _prototype_ `DECLARE_DELEGATE_ThreeParams(FElectraHTTPStreamNotificationDelegate, IElectraHTTPStreamRequestPtr , EElectraHTTPStreamNotificationReason , int64 );`
- L235 _delegate_ `DECLARE_DELEGATE(FElectraHTTPStreamThreadHandlerDelegate);` — Adds a method of your application to be called periodically from the worker thread of this handler. You may use this to drive another wrapping handler of yours that controls requests. For direct use of requests generated by this handler it is not necessary to add such a method. The NotificationDelegate() of the IElectraHTTPStreamRequestPtr request object should be all you need.

### `Plugins/Media/ElectraUtil/Source/ElectraHTTPStream/Public/ElectraHTTPStreamBuffer.h` (Public)


#### class `FElectraHTTPStreamBuffer`  
`class FElectraHTTPStreamBuffer : public IElectraHTTPStreamBuffer`  
_L8-164_
- inherits: `IElectraHTTPStreamBuffer`
- L11 _public prototype_ `FElectraHTTPStreamBuffer() = default;`
- L12 _public prototype_ `FElectraHTTPStreamBuffer(const FElectraHTTPStreamBuffer&) = delete;`
- L13 _public prototype_ `FElectraHTTPStreamBuffer& operator=(const FElectraHTTPStreamBuffer&) = delete;`
- L14 _public prototype_ `virtual ~FElectraHTTPStreamBuffer() = default;`
- L16 _public function_ `virtual void AddData(const TArray<uint8>& InNewData) override`
- L23 _public function_ `virtual void AddData(TArray<uint8>&& InNewData) override`
- L30 _public function_ `virtual void AddData(const TConstArrayView<const uint8>& InNewData) override`
- L37 _public function_ `virtual void AddData(const IElectraHTTPStreamBuffer& InOther, int64 Offset, int64 NumBytes) override`
- L52 _public function_ `virtual int64 GetNumTotalBytesAdded() const override`
- L57 _public function_ `virtual int64 GetNumTotalBytesHandedOut() const override`
- L62 _public function_ `virtual int64 GetNumBytesAvailableForRead() const override`
- L69 _public function_ `virtual void LockBuffer(const uint8*& OutNextReadAddress, int64& OutNumBytesAvailable) override`
- L79 _public function_ `virtual void UnlockBuffer(int64 NumBytesConsumed) override`
- L101 _public function_ `virtual bool RewindToBeginning() override`
- L112 _public function_ `virtual bool GetEOS() const override`
- L114 _public function_ `virtual void SetEOS() override`
- L116 _public function_ `virtual void ClearEOS() override`
- L119 _public function_ `virtual bool HasAllDataBeenConsumed() const override`
- L122 _public function_ `virtual bool IsCachable() const override`
- L124 _public function_ `virtual void SetIsCachable(bool bInIsCachable) override`
- L127 _public function_ `virtual void SetLengthFromResponseHeader(int64 InLengthFromResponseHeader) override`
- L133 _public function_ `virtual int64 GetLengthFromResponseHeader() const override`
- L137 _protected function_ `virtual void GetBaseBuffer(const uint8*& OutBaseAddress, int64& OutBytesInBuffer) override`
- L145 _private member_ `mutable FCriticalSection Lock;`
- L146 _private member_ `TArray<uint8> Buffer;`
- L147 _private member_ `int64 NextReadPosInBuffer = 0;`
- L148 _private member_ `bool bIsBufferLocked = false;`
- L154 _private member_ `std::atomic_int64_t LengthFromResponseHeader { -1 };` — Total length as specified by Content-Length or Content-Range header. Could be -1 if either is absent when chunked transfer encoding is in effect. It is PERMITTED for this value to be LESS than the actual data since it is the size of the compressed data, not the uncompressed! This will also not be set for HEAD requests since no data will be downloaded.
- L156 _private member_ `bool bEOSReceived = false;`
- L158 _private member_ `int64 NumBytesAdded = 0;` — Number of bytes added to the buffer so far with calls to AddData().
- L160 _private member_ `int64 NumBytesHandedOut = 0;` — Number of bytes handed out.
- L163 _private member_ `bool bIsCachable = true;` — An indicator if the entire buffer data is still available or not. If the buffer is being truncated while read then the buffer cannot be cached any more.

### `Plugins/Media/ElectraUtil/Source/ElectraHTTPStream/Public/ElectraHTTPStreamPerf.h` (Public)
_(no declarations extracted)_

### `Plugins/Media/ElectraUtil/Source/ElectraHTTPStream/Public/IElectraHTTPStreamModule.h` (Public)


#### class `IElectraHTTPStreamModule`  
`class IElectraHTTPStreamModule : public IModuleInterface`  
_L11-15_
- inherits: `IModuleInterface`
- desc: Interface for the 'ElectraHTTPStream' module.
- L14 _public prototype_ `virtual ~IElectraHTTPStreamModule() = default;`

### `Plugins/Media/ElectraUtil/Source/ElectraHTTPStream/Public/Utilities/HttpRangeHeader.h` (Public)


#### struct `ElectraHTTPStream::FHttpRange`  
`struct FHttpRange`  
_L10-168_
- L12 _public function_ `void Reset()`
- L18 _public function_ `bool IsSet() const`
- L22 _public function_ `bool Equals(const FHttpRange& Other)`
- L27 _public function_ `bool IsEverything() const` — Check if the range would result in "0-" for the entire resource in which case we don't need to use range request.
- L31 _public function_ `FString GetString(bool bWithUnitPrefix=false) const`
- L55 _public function_ `int64 GetNumberOfBytes() const` — Returns the number of bytes in the range, which must be fully specified. An unset or partially open range will return -1.
- L63 _public function_ `int64 GetStart() const`
- L67 _public function_ `int64 GetEndIncluding() const`
- L71 _public function_ `bool IsOpenEnded() const`
- L75 _public function_ `void Set(const FString& InString)`
- L100 _public function_ `void SetStart(int64 InStart)`
- L104 _public function_ `void SetEndIncluding(int64 InEndIncluding)`
- L108 _public function_ `int64 GetDocumentSize() const`
- L112 _public function_ `bool ParseFromContentRangeResponse(const FString& ContentRangeHeader)`
- L165 _public member_ `int64 Start = -1;`
- L166 _public member_ `int64 EndIncluding = -1;`
- L167 _public member_ `int64 DocumentSize = -1;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace ElectraHTTPStream`
