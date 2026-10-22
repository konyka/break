# Developer / TraceAnalysis

- module root: `Source/Developer/TraceAnalysis`
- headers: 21; symbols: 932
- symbol kinds: class=33, delegate=3, enum=15, enumerator=89, externvar=1, function=155, macro=60, member=138, namespace=39, prototype=370, struct=22, typedef=6, union=1
- PrivateDependencyModuleNames: Asio, Cbor, Core, OpenSSL, Sockets, TraceLog

### `Source/Developer/TraceAnalysis/Private/Analysis/Engine.h` (Private)


#### class `UE::Trace::FAnalysisEngine`  
`class FAnalysisEngine`  
_L17-33_
- L20 _public prototype_ `FAnalysisEngine(TArray<IAnalyzer*>&& Analyzers, FMessageDelegate&& InMessage);`
- L21 _public prototype_ `~FAnalysisEngine();`
- L22 _public prototype_ `void Begin();`
- L23 _public prototype_ `void End();`
- L24 _public prototype_ `bool OnData(FStreamReader& Reader);`
- L28 _private prototype_ `FAnalysisEngine(const FAnalysisEngine&) = delete;`
- L29 _private prototype_ `FAnalysisEngine(const FAnalysisEngine&&) = delete;`
- L30 _private prototype_ `FAnalysisEngine operator = (const FAnalysisEngine&) = delete;`
- L31 _private prototype_ `FAnalysisEngine operator = (const FAnalysisEngine&&) = delete;`
- L32 _private member_ `FImpl* Impl;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Trace` (scope `UE`)

### `Source/Developer/TraceAnalysis/Private/Analysis/Processor.h` (Private)


#### class `UE::Trace::FAnalysisProcessor::FImpl`  
`class FAnalysisProcessor::FImpl : public FRunnable`  
_L17-38_
- inherits: `FRunnable`
- L21 _public prototype_ `FImpl(IInDataStream& DataStream, TArray<IAnalyzer*>&& InAnalyzers, FMessageDelegate&& InMessage, FOnCompletedDelegate&& InOnCompleted);`
- L22 _public prototype_ `~FImpl();`
- L23 _public prototype_ `virtual uint32 Run() override;`
- L24 _public prototype_ `bool IsActive() const;`
- L25 _public prototype_ `void StopAnalysis();`
- L26 _public prototype_ `void WaitOnAnalysis();`
- L27 _public prototype_ `void PauseAnalysis(bool bState);`
- L28 _public prototype_ `FMessageLog* GetLog();`
- L31 _private member_ `FAnalysisEngine AnalysisEngine;`
- L32 _private member_ `IInDataStream& DataStream;`
- L33 _private member_ `FEvent* StopEvent;`
- L34 _private member_ `FEvent* UnpausedEvent;`
- L35 _private member_ `FRunnableThread* Thread = nullptr;`
- L36 _private member_ `volatile bool bComplete = false;`
- L37 _private member_ `FOnCompletedDelegate OnCompleted;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Trace` (scope `UE`)

### `Source/Developer/TraceAnalysis/Private/Analysis/StreamReader.h` (Private)


#### class `UE::Trace::FStreamReader`  
`class FStreamReader`  
_L13-36_
- L17 _public prototype_ `template <typename Type> Type const* GetPointer() const;`
- L19 _public prototype_ `template <typename Type> Type const* GetPointerUnchecked() const;`
- L20 _public prototype_ `const uint8* GetPointer(uint32 Size) const;`
- L21 _public prototype_ `const uint8* GetPointerUnchecked() const;`
- L22 _public prototype_ `void Advance(uint32 Size);`
- L23 _public prototype_ `bool IsEmpty() const;`
- L24 _public prototype_ `bool CanMeetDemand() const;`
- L25 _public prototype_ `uint32 GetRemaining() const;`
- L26 _public prototype_ `uint32 GetBacktrackSize(const uint8* To) const;`
- L27 _public prototype_ `bool Backtrack(const uint8* To);`
- L28 _public prototype_ `struct FMark* SaveMark() const;`
- L29 _public prototype_ `void RestoreMark(struct FMark* Mark);`
- L32 _protected member_ `uint8* Buffer = nullptr;`
- L33 _protected member_ `mutable uint32 DemandHint = 0;`
- L34 _protected member_ `uint32 Cursor = 0;`
- L35 _protected member_ `uint32 End = 0;`
- L40 _function_ `template <typename Type> Type const* FStreamReader::GetPointer() const`
- L47 _function_ `template <typename Type> Type const* FStreamReader::GetPointerUnchecked() const`
- L53 _function_ `inline const uint8* FStreamReader::GetPointerUnchecked() const`
- L58 _function_ `inline uint32 FStreamReader::GetBacktrackSize(const uint8* To) const`

#### class `UE::Trace::FStreamBuffer`  
`class FStreamBuffer : public FStreamReader`  
_L66-86_
- inherits: `FStreamReader`
- L70 _public prototype_ `FStreamBuffer() = default;`
- L71 _public prototype_ `FStreamBuffer(uint32_t InitalBufferSize);`
- L72 _public prototype_ `~FStreamBuffer();`
- L73 _public prototype_ `FStreamBuffer(FStreamBuffer&& Rhs) noexcept;`
- L74 _public prototype_ `FStreamBuffer(const FStreamBuffer&) = default;`
- L75 _public prototype_ `FStreamBuffer& operator = (FStreamBuffer&& Rhs) noexcept;`
- L76 _public prototype_ `FStreamBuffer& operator = (const FStreamBuffer&) = delete;`
- L78 _public prototype_ `template <typename Lambda> int32 Fill(Lambda&& Source);`
- L79 _public prototype_ `void Append(const uint8* Data, uint32 Size);`
- L80 _public prototype_ `uint8* Append(uint32 Size);`
- L81 _public function_ `uint32 GetBufferSize() const`
- L84 _protected prototype_ `void Consolidate();`
- L85 _protected member_ `uint32 BufferSize = 0;`
- L89 _function_ `inline FStreamBuffer::~FStreamBuffer()`
- L95 _function_ `inline FStreamBuffer::FStreamBuffer(FStreamBuffer&& Rhs) noexcept`
- L105 _function_ `inline FStreamBuffer& FStreamBuffer::operator = (FStreamBuffer&& Rhs) noexcept`
- L117 _function_ `template <typename Lambda> inline int32 FStreamBuffer::Fill(Lambda&& Source)`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Trace` (scope `UE`)

### `Source/Developer/TraceAnalysis/Private/Analysis/Transport/PacketTransport.h` (Private)


#### class `UE::Trace::FPacketTransport`  
`class FPacketTransport : public FTransport`  
_L11-33_
- inherits: `FTransport`
- L15 _public function_ `FPacketTransport()`
- L16 _public prototype_ `virtual ~FPacketTransport();`
- L17 _public prototype_ `virtual void Advance(uint32 BlockSize) override;`
- L18 _public prototype_ `virtual bool IsEmpty() const override;`
- L19 _public prototype_ `virtual void DebugBegin() override;`
- L20 _public prototype_ `virtual void DebugEnd() override;`
- L23 _protected prototype_ `virtual const uint8* GetPointerImpl(uint32 BlockSize) override;`
- L27 _private prototype_ `bool GetNextBatch();`
- L28 _private prototype_ `FPacketNode* AllocateNode();`
- L29 _private member_ `static const uint32 MaxPacketSize = 8192;`
- L30 _private member_ `FPacketNode* ActiveList = nullptr;`
- L31 _private member_ `FPacketNode* PendingList = nullptr;`
- L32 _private member_ `FPacketNode* FreeList = nullptr;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Trace` (scope `UE`)

### `Source/Developer/TraceAnalysis/Private/Analysis/Transport/TidPacketTransport.h` (Private)


#### class `UE::Trace::FTidPacketTransport`  
`class FTidPacketTransport : public FTransport`  
_L18-97_
- inherits: `FTransport`
- L41 _public function_ `FTidPacketTransport()`
- L42 _public prototype_ `virtual ~FTidPacketTransport() = default;`
- L44 _public prototype_ `virtual bool IsEmpty() const override;`
- L45 _public prototype_ `virtual void DebugBegin() override;`
- L46 _public prototype_ `virtual void DebugEnd() override;`
- L48 _public prototype_ `ETransportResult Update();`
- L49 _public prototype_ `uint32 GetThreadCount() const;`
- L50 _public prototype_ `FStreamReader* GetThreadStream(uint32 Index);`
- L51 _public prototype_ `FStreamReader* GetKnownStream(EThreadStreamIndex KnownThread);`
- L52 _public prototype_ `uint32 GetThreadId(uint32 Index) const;`
- L53 _public prototype_ `uint32 GetSyncCount() const;`
- L57 _protected member_ `uint32 Synced = 0x7fff'ffff;`
- L58 _protected member_ `uint32 NumPackets = 0;`
- L60 _protected member_ `uint64 LastPacketSerial = 0;`
- L77 _private prototype_ `EReadPacketResult ReadPacket();`
- L78 _private prototype_ `FThreadStream* FindOrAddThread(uint32 ThreadId, bool bAddIfNotFound);`
- L79 _private prototype_ `void DebugUpdate();`
- L81 _private member_ `TArray<FThreadStream> Threads = { { {}, ETransportTid::Events }, { {}, ETransportTid::Importants }, { {}, ETransportTid::PseudoImportants } };`
- L88 _private member_ `uint64 TotalPacketHeaderSize = 0;`
- L89 _private member_ `uint64 TotalPacketSize = 0;`
- L90 _private member_ `uint64 TotalDecodedSize = 0;`
- L91 _private member_ `uint32 MaxBufferSize = 0;`
- L92 _private member_ `uint32 MaxBufferSizeThreadId = 0;`
- L93 _private member_ `uint32 MaxDataSizePerBuffer = 0;`
- L94 _private member_ `uint32 MaxDataSizePerBufferThreadId = 0;`
- L95 _private member_ `TMap<uint32, uint64> DataSizePerThread;`
- L100 _function_ `inline uint32 FTidPacketTransport::GetSyncCount() const`

#### enum `UE::Trace::FTidPacketTransport::ETransportResult`  
`enum class ETransportResult : uint8`  
_L22-26_
- L24 _public enumerator_ `Ok`
- L25 _public enumerator_ `Error`

#### enum `UE::Trace::FTidPacketTransport::EThreadStreamIndex`  
`enum class EThreadStreamIndex : uint32`  
_L32-38_
- desc: The "pseudo threads" have a fixed index in the thread stream array.
- L34 _public enumerator_ `Events = 0`
- L35 _public enumerator_ `Importants = 1`
- L36 _public enumerator_ `PseudoImportants = 2`
- L37 _public enumerator_ `RealThreadsStart = 3`

#### struct `UE::Trace::FTidPacketTransport::FThreadStream`  
`struct FThreadStream`  
_L64-68_
- L66 _public member_ `FStreamBuffer Buffer;`
- L67 _public member_ `uint32 ThreadId;`

#### enum `UE::Trace::FTidPacketTransport::EReadPacketResult`  
`enum class EReadPacketResult : uint8`  
_L70-75_
- L72 _public enumerator_ `NeedMoreData`
- L73 _public enumerator_ `Continue`
- L74 _public enumerator_ `ReadError`

#### class `UE::Trace::FTidPacketTransportSync`  
`class FTidPacketTransportSync : public FTidPacketTransport`  
_L108-117_
- inherits: `FTidPacketTransport`
- L112 _public function_ `FTidPacketTransportSync()`
- L116 _public prototype_ `virtual ~FTidPacketTransportSync() = default;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Trace` (scope `UE`)

### `Source/Developer/TraceAnalysis/Private/Analysis/Transport/Transport.h` (Private)


#### class `UE::Trace::FTransport`  
`class FTransport`  
_L11-31_
- L14 _public function_ `FTransport()`
- L15 _public prototype_ `virtual ~FTransport() = default;`
- L16 _public prototype_ `void SetReader(FStreamReader& InReader);`
- L17 _public function_ `FStreamReader* GetReader() const`
- L19 _public prototype_ `template <typename RetType> RetType const* GetPointer();`
- L21 _public prototype_ `template <typename RetType> RetType const* GetPointer(uint32 BlockSize);`
- L22 _public prototype_ `virtual void Advance(uint32 BlockSize);`
- L23 _public function_ `virtual bool IsEmpty() const`
- L24 _public function_ `virtual void DebugBegin()`
- L25 _public function_ `virtual void DebugEnd()`
- L28 _protected prototype_ `virtual const uint8* GetPointerImpl(uint32 BlockSize);`
- L30 _protected member_ `FStreamReader* Reader = nullptr;`
- L34 _function_ `inline void FTransport::SetReader(FStreamReader& InReader)`
- L41 _function_ `template <typename RetType> inline RetType const* FTransport::GetPointer()`
- L48 _function_ `template <typename RetType> inline RetType const* FTransport::GetPointer(uint32 BlockSize)`
- L54 _function_ `inline void FTransport::Advance(uint32 BlockSize)`
- L60 _function_ `inline const uint8* FTransport::GetPointerImpl(uint32 BlockSize)`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Trace` (scope `UE`)

### `Source/Developer/TraceAnalysis/Private/Common.h` (Private)
_(no declarations extracted)_

### `Source/Developer/TraceAnalysis/Private/DataStreamInternal.h` (Private)


#### class `UE::Trace::FTraceDataStream`  
`class FTraceDataStream : public IInDataStream`  
_L14-26_
- inherits: `IInDataStream`
- L18 _public prototype_ `FTraceDataStream(asio::ip::tcp::socket& InSocket);`
- L19 _public prototype_ `virtual ~FTraceDataStream();`
- L20 _public prototype_ `bool IsOpen() const;`
- L21 _public prototype_ `virtual void Close() override;`
- L22 _public prototype_ `virtual int32 Read(void* Dest, uint32 DestSize) override;`
- L25 _private member_ `asio::ip::tcp::socket Socket;`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTraceData, Log, Log);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTraceData, Log, Log);`
- L10 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Trace` (scope `UE`)

### `Source/Developer/TraceAnalysis/Private/Store/CborPayload.h` (Private)


#### struct `UE::Trace::TInlineMemoryWriter`  
`template <int BufferSize> struct TInlineMemoryWriter : public FMemoryArchive`  
_L19-28_
- inherits: `FMemoryArchive`
- L23 _public typedef_ `typedef TArray<uint8, TInlineAllocator<BufferSize>> BufferType;`
- L25 _public prototype_ `TInlineMemoryWriter();`
- L26 _public prototype_ `virtual void Serialize(void* Data, int64 Num) override;`
- L27 _public member_ `BufferType Buffer;`
- L32 _function_ `template <int BufferSize> inline TInlineMemoryWriter<BufferSize>::TInlineMemoryWriter()`
- L39 _function_ `template <int BufferSize> inline void TInlineMemoryWriter<BufferSize>::Serialize(void* Data, int64 Num)`

#### struct `UE::Trace::FPayload`  
`struct FPayload`  
_L47-51_
- L49 _public member_ `const uint8* Data;`
- L50 _public member_ `uint32 Size;`

#### enum `UE::Trace::EStatusCode`  
`enum class EStatusCode`  
_L56-63_
- L58 _public enumerator_ `Unknown = 0`
- L59 _public enumerator_ `Success = 200`
- L60 _public enumerator_ `BadRequest = 400`
- L61 _public enumerator_ `NotFound = 404`
- L62 _public enumerator_ `InternalError = 500`

#### class `UE::Trace::TPayloadBuilder`  
`template <int Size=128> class TPayloadBuilder`  
_L69-85_
- L72 _public prototype_ `TPayloadBuilder(EStatusCode StatusCode);`
- L73 _public prototype_ `template <int N> TPayloadBuilder(const char (&Path)[N]);`
- L74 _public prototype_ `template <int N> TPayloadBuilder(const char (&Path)[N]);`
- L75 _public prototype_ `template <int N> TPayloadBuilder(const char (&Path)[N]);`
- L77 _public prototype_ `template <int N> void AddInteger(const char (&Name)[N], int64 Value);`
- L79 _public prototype_ `template <int N> void AddString(const char (&Name)[N], const FStringView& String);`
- L80 _public prototype_ `FPayload Done();`
- L83 _private member_ `TInlineMemoryWriter<Size> MemoryWriter;`
- L84 _private member_ `FCborWriter CborWriter = { &MemoryWriter, ECborEndianness::StandardCompliant };`
- L89 _function_ `template <int Size> inline TPayloadBuilder<Size>::TPayloadBuilder(EStatusCode StatusCode)`
- L98 _function_ `template <int Size> template <int N> inline TPayloadBuilder<Size>::TPayloadBuilder(const char (&Path)[N])`
- L108 _function_ `template <int Size> template <int N> inline void TPayloadBuilder<Size>::AddInteger(const char (&Name)[N], int64 Value)`
- L117 _function_ `template <int Size> template <int N> inline void TPayloadBuilder<Size>::AddString( const char (&Name)[N], const char* Value, int Length)`
- L130 _function_ `template <int Size> template <int N> void TPayloadBuilder<Size>::AddString(const char(& Name)[N], const FStringView& String)`
- L140 _function_ `template<int Size> template<int N> inline void TPayloadBuilder<Size>::AddStringArray(const char(&Name)[N], const TArray<FString>& Values)`
- L153 _function_ `template <int Size> template <int N, typename T> void TPayloadBuilder<Size>::AddArray(const char(& Name)[N], const TArrayView<T>& Values)`
- L165 _function_ `template <int Size> inline FPayload TPayloadBuilder<Size>::Done()`

#### class `UE::Trace::FResponse`  
`class FResponse`  
_L174-194_
- L177 _public prototype_ `EStatusCode GetStatusCode() const;`
- L178 _public prototype_ `int64 GetInt64Checked(const char* Key, int64 Default) const;`
- L179 _public prototype_ `uint64 GetUint64Checked(const char* Key, uint64 Default) const;`
- L180 _public prototype_ `int32 GetInt32Checked(const char* Key, int32 Default) const;`
- L181 _public prototype_ `uint32 GetUint32Checked(const char* Key, uint32 Default) const;`
- L182 _public function_ `int64 GetInteger(const char* Key, int64 Default) const`
- L184 _public prototype_ `template <int N> FUtf8StringView GetString(const char* Key, const char (&Default)[N]) const;`
- L185 _public prototype_ `bool GetStringArray(const char* Key, TArray<FString>& OutArray) const;`
- L186 _public prototype_ `const uint8* GetData() const;`
- L187 _public prototype_ `uint32 GetSize() const;`
- L188 _public prototype_ `uint8* Reserve(uint32 Size);`
- L192 _private prototype_ `template <typename Type, typename LambdaType> Type GetValue(const char* Key, Type Default, LambdaType&& Lambda) const;`
- L193 _private member_ `TArray<uint8> Buffer;`
- L197 _function_ `inline EStatusCode FResponse::GetStatusCode() const`
- L204 _function_ `inline bool FResponse::GetStringArray(const char* Key, TArray<FString>& OutArray) const`
- L233 _function_ `inline const uint8* FResponse::GetData() const`
- L239 _function_ `inline uint32 FResponse::GetSize() const`
- L245 _function_ `inline uint8* FResponse::Reserve(uint32 Size)`
- L253 _function_ `template <typename Type, typename LambdaType> inline Type FResponse::GetValue(const char* Key, Type Default, LambdaType&& Lambda) const`
- L291 _function_ `inline int64 FResponse::GetInt64Checked(const char* Key, int64 Default) const`
- L304 _function_ `inline uint64 FResponse::GetUint64Checked(const char* Key, uint64 Default) const`
- L317 _function_ `inline int32 FResponse::GetInt32Checked(const char* Key, int32 Default) const`
- L332 _function_ `inline uint32 FResponse::GetUint32Checked(const char* Key, uint32 Default) const`
- L348 _function_ `template <int N> inline FUtf8StringView FResponse::GetString(const char* Key, const char (&Default)[N]) const`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Trace` (scope `UE`)
- L297 _function_ `` (scope `UE::Trace::FResponse::GetInt64Checked`)
- L310 _function_ `` (scope `UE::Trace::FResponse::GetUint64Checked`)
- L323 _function_ `` (scope `UE::Trace::FResponse::GetInt32Checked`)
- L338 _function_ `` (scope `UE::Trace::FResponse::GetUint32Checked`)
- L355 _function_ `` (scope `UE::Trace::FResponse::GetString`)

### `Source/Developer/TraceAnalysis/Private/TraceAnalysisModule.h` (Private)


#### class `FTraceAnalysisModule`  
`class FTraceAnalysisModule : public IModuleInterface`  
_L6-12_
- inherits: `IModuleInterface`
- L9 _public prototype_ `virtual void StartupModule() override;`
- L11 _public prototype_ `static FName GetMessageLogName();`

### `Source/Developer/TraceAnalysis/Public/Trace/Analysis.h` (Public)


#### enum `UE::Trace::EAnalysisMessageSeverity`  
`enum class EAnalysisMessageSeverity`  
_L18-23_
- L20 _public enumerator_ `Info`
- L21 _public enumerator_ `Warning`
- L22 _public enumerator_ `Error`

#### class `UE::Trace::FAnalysisProcessor`  
`class FAnalysisProcessor`  
_L34-62_
- desc: Represents the processing (e.g. analysis) of a trace stream. Instances are created by constructing an FAnalysisContext object to marry an event trace with how it should be analyzed. Note that the processing (and thus analysis) happens on another thread.
- L38 _public prototype_ `bool IsActive() const;` — Checks if this object instance is valid and currently processing
- L41 _public prototype_ `void Stop();` — End processing a trace stream.
- L44 _public prototype_ `void Wait();` — Wait for the entire stream to have been processed and analysed.
- L48 _public prototype_ `void Pause(bool bState);` — Pause or resume the processing. @param bState Pause if true, resume if false.
- L51 _public prototype_ `~FAnalysisProcessor();`
- L52 _public prototype_ `FAnalysisProcessor() = default;`
- L53 _public prototype_ `FAnalysisProcessor(FAnalysisProcessor&& Rhs);`
- L54 _public prototype_ `FAnalysisProcessor& operator = (FAnalysisProcessor&&);`
- L58 _private prototype_ `FAnalysisProcessor(FAnalysisProcessor&) = delete;`
- L59 _private prototype_ `FAnalysisProcessor& operator = (const FAnalysisProcessor&) = delete;`
- L61 _private member_ `FImpl* Impl = nullptr;`

#### class `UE::Trace::FAnalysisContext`  
`class FAnalysisContext`  
_L70-92_
- desc: Used to describe how a log of trace events should be analyzed and being the analysis on a particular trace stream.
- L75 _public prototype_ `void AddAnalyzer(IAnalyzer& Analyzer);` — Adds an analyzer instance that will subscribe to and receive event data from the trace stream.
- L78 _public prototype_ `void SetMessageDelegate(FMessageDelegate Delegate);` — Adds a callback to recieve important messages.
- L81 _public prototype_ `void SetOnCompletedDelegate(FOnCompletedDelegate Delegate);` — Adds a callback that is invoked on the analysis thread when processing completes.
- L86 _public prototype_ `FAnalysisProcessor Process(IInDataStream& DataStream);` — Creates and starts analysis returning an FAnalysisProcessor instance which represents the analysis and affords some control over it. @param DataStream Input stream of trace log data to be analysed.
- L89 _private member_ `TArray<IAnalyzer*> Analyzers;`
- L90 _private member_ `FMessageDelegate OnMessage;`
- L91 _private member_ `FOnCompletedDelegate OnCompleted;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API TRACEANALYSIS_API`
- L12 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Trace` (scope `UE`)
- L25 _delegate_ `DECLARE_DELEGATE_TwoParams(FMessageDelegate, EAnalysisMessageSeverity, FStringView);`
- L25 _prototype_ `DECLARE_DELEGATE_TwoParams(FMessageDelegate, EAnalysisMessageSeverity, FStringView);` (scope `UE::Trace`)
- L26 _delegate_ `DECLARE_DELEGATE(FOnCompletedDelegate);`
- L26 _prototype_ `DECLARE_DELEGATE(FOnCompletedDelegate);` (scope `UE::Trace`)

### `Source/Developer/TraceAnalysis/Public/Trace/Analyzer.h` (Public)


#### class `UE::Trace::IAnalyzer`  
`class IAnalyzer`  
_L28-388_
- desc: Interface that users implement to analyze the events in a trace. Analysis works by subscribing to events by name along with a user-provider "route" identifier. The IAnalyzer then receives callbacks when those events are encountered along with an interface to query the value of the event's fields. To analyze a trace, concrete IAnalyzer-derived objects are registered with a FAnalysisContext which is then asked to launch and coordinate the analysis.
- L334 _public prototype_ `virtual ~IAnalyzer() = default;`
- L339 _public function_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context)` — Called when analysis of a trace is beginning. Analyzer implementers can subscribe to the events that they are interested in at this point @param Context Contextual information and interface for subscribing to events.
- L345 _public function_ `virtual void OnAnalysisEnd()` — Indicates that the analysis of a trace log has completed and there are no further events
- L353 _public function_ `virtual void OnThreadInfo(const FThreadInfo& ThreadInfo)` — Called when information about a thread has been updated. It is entirely possible that this might get called more than once for a particular thread if its details changed. @param ThreadInfo Describes the thread whose information has changed.
- L362 _public function_ `virtual bool OnNewEvent(uint16 RouteId, const FEventTypeInfo& TypeInfo)` — When a new event type appears in the trace stream, this method is called if the event type has been subscribed to. @param RouteId User-provided identifier for this event subscription. @param TypeInfo Object describing the new event's type. @return This analyzer is removed from the analysis session if false is returned.
- L373 _public function_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context)` — For each event subscribed to in OnAnalysisBegin(), the analysis engine will call this method when those events are encountered in a trace log @param RouteId User-provided identifier given when subscribing to a particular event. @param Style Indicates the style of event. Note that EventData is *undefined* if the style is LeaveScope! @param Context Access to the instance of the subscribed event. @return This analyzer is removed from the analysis session if false is returned.
- L382 _public function_ `virtual void OnVersion(uint32 TransportVersion, uint32 ProtocolVersion)` — Called when information about trace transport and trace protocol versions are available. This is called after OnAnalysisBegin(), but before any OnNewEvent() or OnEvent() calls. @param TransportVersion The version of the trace transport (see Trace\Detail\Transport.h) @param ProtocolVersion The version of the trace protocol (see Trace\Detail\Protocols\*.h)
- L387 _private prototype_ `template <typename ValueType> static ValueType CoerceValue(const void* Addr, int8 SizeAndType);`
- L409 _function_ `template <typename ValueType> ValueType IAnalyzer::CoerceValue(const void* Addr, int8 SizeAndType)`

#### struct `UE::Trace::IAnalyzer::FInterfaceBuilder`  
`struct FInterfaceBuilder`  
_L31-50_
- L38 _public prototype_ `virtual void RouteEvent(uint16 RouteId, const ANSICHAR* Logger, const ANSICHAR* Event, bool bScoped=false) = 0;` — Subscribe to an event required for analysis. @param RouteId User-provided identifier for this event subscription. @param Logger Name of the logger that emits the event. @param Event Name of the event to subscribe to. @param bScoped Route scoped events.
- L44 _public prototype_ `virtual void RouteLoggerEvents(uint16 RouteId, const ANSICHAR* Logger, bool bScoped=false) = 0;` — Subscribe to all events from a particular logger. @param RouteId User-provided identifier for this event subscription. @param Logger Name of the logger that emits the event. @param bScoped Route scoped events.
- L49 _public prototype_ `virtual void RouteAllEvents(uint16 RouteId, bool bScoped=false) = 0;` — Subscribe to all events in the trace stream being analyzed. @param RouteId User-provided identifier for this event subscription. @param bScoped Route scoped events.

#### struct `UE::Trace::IAnalyzer::FOnAnalysisContext`  
`struct FOnAnalysisContext`  
_L52-55_
- L54 _public member_ `FInterfaceBuilder& InterfaceBuilder;`

#### struct `UE::Trace::IAnalyzer::FEventFieldInfo`  
`struct FEventFieldInfo`  
_L57-86_
- L62 _public prototype_ `const ANSICHAR* GetName() const;` — Returns the name of the field.
- L65 _public prototype_ `EType GetType() const;` — What type of field is this?
- L68 _public prototype_ `bool IsArray() const;` — Is this field an array-type field?
- L71 _public prototype_ `bool IsSigned() const;` — Is this field signed (only relevant for integer types)
- L75 _public prototype_ `uint32 GetOffset() const;` — Offset from the start of the event to this field's data.
- L79 _public prototype_ `uint8 GetSize() const;` — Gets the size in bytes for this field.
- L82 _public prototype_ `uint8 GetTypeSize() const;` — Gets the size in bytes for the type of this field.
- L85 _public prototype_ `uint32 GetRefUid() const;` — Gets the Reference Uid for this field.

#### enum `UE::Trace::IAnalyzer::FEventFieldInfo::EType`  
`enum class EType`  
_L59-59_
- L59 _public enumerator_ `enum class EType { None, Integer, Float, AnsiString, WideString, Reference8, Reference16, Reference32, Reference64 }; UE_API const ANSICHAR* GetName() const; UE_API EType GetType() const;`
- L59 _public enumerator_ `enum class EType { None, Integer, Float, AnsiString, WideString, Reference8, Reference16, Reference32, Reference64 }; UE_API const ANSICHAR* GetName() const; UE_API EType GetType() const;`
- L59 _public enumerator_ `enum class EType { None, Integer, Float, AnsiString, WideString, Reference8, Reference16, Reference32, Reference64 }; UE_API const ANSICHAR* GetName() const; UE_API EType GetType() const;`
- L59 _public enumerator_ `enum class EType { None, Integer, Float, AnsiString, WideString, Reference8, Reference16, Reference32, Reference64 }; UE_API const ANSICHAR* GetName() const; UE_API EType GetType() const;`
- L59 _public enumerator_ `enum class EType { None, Integer, Float, AnsiString, WideString, Reference8, Reference16, Reference32, Reference64 }; UE_API const ANSICHAR* GetName() const; UE_API EType GetType() const;`
- L59 _public enumerator_ `enum class EType { None, Integer, Float, AnsiString, WideString, Reference8, Reference16, Reference32, Reference64 }; UE_API const ANSICHAR* GetName() const; UE_API EType GetType() const;`
- L59 _public enumerator_ `enum class EType { None, Integer, Float, AnsiString, WideString, Reference8, Reference16, Reference32, Reference64 }; UE_API const ANSICHAR* GetName() const; UE_API EType GetType() const;`
- L59 _public enumerator_ `enum class EType { None, Integer, Float, AnsiString, WideString, Reference8, Reference16, Reference32, Reference64 }; UE_API const ANSICHAR* GetName() const; UE_API EType GetType() const;`
- L59 _public enumerator_ `enum class EType { None, Integer, Float, AnsiString, WideString, Reference8, Reference16, Reference32, Reference64 }; UE_API const ANSICHAR* GetName() const; UE_API EType GetType() const;`

#### struct `UE::Trace::IAnalyzer::FEventFieldHandle`  
`struct FEventFieldHandle`  
_L88-92_
- L90 _public function_ `bool IsValid() const`
- L91 _public member_ `int32 Detail;`

#### enum `UE::Trace::IAnalyzer::EEventFlags`  
`enum class EEventFlags : uint8`  
_L94-101_
- L96 _public enumerator_ `None = 0`
- L97 _public enumerator_ `Important = 1 << 0`
- L98 _public enumerator_ `MaybeHasAux = 1 << 1`
- L99 _public enumerator_ `NoSync = 1 << 2`
- L100 _public enumerator_ `Definition = 1 << 3`

#### struct `UE::Trace::IAnalyzer::FEventTypeInfo`  
`struct FEventTypeInfo`  
_L103-150_
- L107 _public prototype_ `uint32 GetId() const;` — Each event is assigned a unique ID when logged. Note that this is not guaranteed to be the same for the same event from one trace to the next.
- L110 _public prototype_ `EEventFlags GetFlags() const;` — Returns the event's flags.
- L111 _public function_ `inline bool IsImportant() const`
- L112 _public function_ `inline bool IsSync() const`
- L113 _public function_ `inline bool IsNoSync() const`
- L114 _public function_ `inline bool IsDefinition() const`
- L115 _public function_ `inline bool MaybeHasAux() const`
- L118 _public prototype_ `const ANSICHAR* GetName() const;` — The name of the event.
- L121 _public prototype_ `const ANSICHAR* GetLoggerName() const;` — Returns the logger name the event is associated with.
- L124 _public prototype_ `uint32 GetSize() const;` — Returns the base size of the event.
- L127 _public prototype_ `uint32 GetFieldCount() const;` — The number of member fields this event has.
- L130 _public prototype_ `const FEventFieldInfo* GetFieldInfo(uint32 Index) const;` — By-index access to fields' type information.
- L133 _public prototype_ `int32 GetFieldIndex(const ANSICHAR* FieldName) const;` — Returns the field index or -1 (if the event does not contains a field with the specified name).
- L140 _public prototype_ `template <typename ValueType> FEventFieldHandle GetFieldHandle(const ANSICHAR* FieldName) const;` — Returns a handle that can used to access events' fields. There is loose validation via ValueType, but one should still exercise caution when reading fields with handles. @param ValueType The intended type that the field will be interpreted as
- L146 _public prototype_ `FEventFieldHandle GetFieldHandleUnchecked(uint32 Index) const;` — Returns a handle without specifying type. This should only be used in circumstances where the field is treated untyped data. @param Index Index of field.
- L149 _private prototype_ `FEventFieldHandle GetFieldHandleImpl(const ANSICHAR*, int16&) const;`
- L392 _function_ `template <typename ValueType> IAnalyzer::FEventFieldHandle IAnalyzer::FEventTypeInfo::GetFieldHandle(const ANSICHAR* FieldName) const`

#### struct `UE::Trace::IAnalyzer::FArrayReader`  
`struct FArrayReader`  
_L152-170_
- L155 _public prototype_ `uint32 Num() const;` — Returns the number of elements in the array.
- L159 _public prototype_ `const uint8* GetRawData() const;` — Returns the pointer to the raw data array.
- L162 _public prototype_ `uint32 GetRawDataSize() const;` — Returns the size in bytes of the raw data array.
- L165 _public prototype_ `int8 GetSizeAndType() const;` — Returns the size and type of an array element.
- L169 _protected prototype_ `const void* GetImpl(uint32 Index, int8& SizeAndType) const;`

#### struct `UE::Trace::IAnalyzer::TArrayReader`  
`template <typename ValueType> struct TArrayReader : public FArrayReader`  
_L173-182_
- inherits: `FArrayReader`
- L178 _public prototype_ `ValueType operator [] (uint32 Index) const;` — Returns a element from the array an the given index or zero if Index is out of bounds.
- L181 _public prototype_ `const ValueType* GetData() const;` — Get a pointer to the contiguous array data
- L465 _function_ `template <typename ValueType> ValueType IAnalyzer::TArrayReader<ValueType>::operator [] (uint32 Index) const`
- L477 _function_ `template <typename ValueType> const ValueType* IAnalyzer::TArrayReader<ValueType>::GetData() const`

#### enum `UE::Trace::IAnalyzer::EStyle`  
`enum class EStyle : uint32`  
_L184-189_
- L186 _public enumerator_ `Normal`
- L187 _public enumerator_ `EnterScope`
- L188 _public enumerator_ `LeaveScope`

#### struct `UE::Trace::IAnalyzer::FEventData`  
`struct FEventData`  
_L193-284_
- L196 _public prototype_ `const FEventTypeInfo& GetTypeInfo() const;` — Returns an object describing the underlying event's type.
- L203 _public prototype_ `template <typename ValueType> ValueType GetValue(const ANSICHAR* FieldName, ValueType Default=ValueType(0)) const;` — Queries the value of a field of the event. It is not necessary to match ValueType to the type in the event. @param FieldName The name of the event's field to get the value for. @param Default Return this value if the given field was not found. @return Value of the field (coerced to ValueType) if found, otherwise 0.
- L210 _public prototype_ `template <typename ValueType> const TArrayReader<ValueType>& GetArray(const ANSICHAR* FieldName) const;` — Returns an object for reading data from an array-type field. A valid array reader object will always be return even if no field matching the given name was found. @param FieldName The name of the event's field to get the value for.
- L216 _public prototype_ `template <typename ValueType> TArrayView<const ValueType> GetArrayView(const ANSICHAR* FieldName) const;` — Returns an array view for reading data from an array-type field. A valid array view will always be returned even if no field matching the given name was found. @param FieldName The name of the event's field to get the value for.
- L223 _public prototype_ `bool GetString(const ANSICHAR* FieldName, FAnsiStringView& Out) const;` — Return the value of a string-type field. The view-type prototypes must match the underlying string type while the FString-variant is agnostic of the field's encoding. @param Out Destination object for the field's value. @return True if the field was found.
- L224 _public prototype_ `bool GetString(const ANSICHAR* FieldName, FWideStringView& Out) const;`
- L225 _public prototype_ `bool GetString(const ANSICHAR* FieldName, FString& Out) const;`
- L232 _public prototype_ `template<typename DefinitionType> TEventRef<DefinitionType> GetReferenceValue(const ANSICHAR* FieldName) const;` — Returns a value of a reference field. @param FieldName Name of field @return Reference value
- L235 _public prototype_ `template<typename DefinitionType> TEventRef<DefinitionType> GetReferenceValue(uint32 FieldIndex) const;`
- L240 _public prototype_ `template<typename DefinitionType> TEventRef<DefinitionType> GetDefinitionId() const;` — If this is a spec event, gets the unique Id for this spec. @return A valid spec id if the event is valid, otherwise an empty id.
- L243 _public prototype_ `uint32 GetSize() const;` — The size of the event in uncompressed bytes excluding the header
- L247 _public prototype_ `void SerializeToCbor(TArray<uint8>& Out) const;` — Serializes the event to Cbor object. @param Recipient of the Cbor serialization. Data is appended to Out.
- L254 _public prototype_ `const void* GetValueRaw(FEventFieldHandle Handle) const;` — Returns the raw pointer to a field value @param Handle Handle to field @return Untyped pointer to field value
- L259 _public prototype_ `const uint8* GetAttachment() const;` — Returns the event's attachment. Not that this will always return an address but if the event has no attachment then reading from that address if undefined.
- L262 _public prototype_ `uint32 GetAttachmentSize() const;` — Returns the size of the events attachment, or 0 if none.
- L266 _public prototype_ `const uint8* GetRawPointer() const;` — Provides a pointer to the raw event data.
- L269 _public prototype_ `uint32 GetRawSize() const;` — Returns the size of the raw event data (including attachment).
- L272 _public prototype_ `uint32 GetAuxSize() const;` — Returns the total uncompressed size of the aux data (including size of aux headers and terminator), in bytes.
- L275 _public prototype_ `uint32 GetTotalSize(IAnalyzer::EStyle Style, const IAnalyzer::FOnEventContext& Context, uint32 ProtocolVersion = 7) const;` — Returns the total uncompressed size of the event, in bytes (including headers and aux data).
- L279 _private prototype_ `bool IsDefinitionImpl(uint32& OutTypeId) const;`
- L280 _private prototype_ `const void* GetReferenceValueImpl(const char* FieldName, uint16& OutSizeType, uint32& OutTypeUid) const;`
- L281 _private prototype_ `const void* GetReferenceValueImpl(uint32 FieldIndex, uint32& OutTypeUid) const;`
- L282 _private prototype_ `const void* GetValueImpl(const ANSICHAR* FieldName, int8& SizeAndType) const;`
- L283 _private prototype_ `const FArrayReader* GetArrayImpl(const ANSICHAR* FieldName) const;`
- L429 _function_ `template <typename ValueType> ValueType IAnalyzer::FEventData::GetValue(const ANSICHAR* FieldName, ValueType Default) const`
- L441 _function_ `template <typename ValueType> ValueType IAnalyzer::FEventData::GetValue(FEventFieldHandle FieldHandle) const`
- L449 _function_ `template <typename ValueType> const IAnalyzer::TArrayReader<ValueType>& IAnalyzer::FEventData::GetArray(const ANSICHAR* FieldName) const`
- L457 _function_ `template <typename ValueType> TArrayView<const ValueType> IAnalyzer::FEventData::GetArrayView(const ANSICHAR* FieldName) const`
- L492 _function_ `template<typename DefinitionType> TEventRef<DefinitionType> IAnalyzer::FEventData::GetDefinitionId() const`
- L505 _function_ `template<typename DefinitionType> TEventRef<DefinitionType> IAnalyzer::FEventData::GetReferenceValue(const ANSICHAR* FieldName) const`
- L519 _function_ `template <typename DefinitionType> TEventRef<DefinitionType> IAnalyzer::FEventData::GetReferenceValue(uint32 FieldIndex) const`

#### struct `UE::Trace::IAnalyzer::FThreadInfo`  
`struct FThreadInfo`  
_L286-304_
- L289 _public prototype_ `uint32 GetId() const;` — Returns the trace-specific id for the thread
- L294 _public prototype_ `uint32 GetSystemId() const;` — Returns the system id for the thread. Because this may not be known by trace and because IDs can be reused by the system, relying on the value of this is discouraged.
- L297 _public prototype_ `int32 GetSortHint() const;` — Returns a hint for use when sorting threads.
- L300 _public prototype_ `const ANSICHAR* GetName() const;` — Returns the thread's name or an empty string
- L303 _public prototype_ `const ANSICHAR* GetGroupName() const;` — Returns the name of the group a thread has been assigned ti, or an empty string

#### struct `UE::Trace::IAnalyzer::FEventTime`  
`struct FEventTime`  
_L306-325_
- L309 _public prototype_ `uint64 GetTimestamp() const;` — Returns the integer timestamp for the event or zero if there no associated timestamp.
- L312 _public prototype_ `double AsSeconds() const;` — Time of the event in seconds (from the start of the trace). Zero if there is no time for the event.
- L315 _public prototype_ `uint64 AsCycle64() const;` — Returns a timestamp for the event compatible with FPlatformTime::Cycle64(), or zero if the event has no timestamp.
- L318 _public prototype_ `double AsSeconds(uint64 Cycles64) const;` — Returns a FPlatformTime::Cycle64() value as seconds relative to the start of the trace.
- L321 _public prototype_ `double AsSecondsAbsolute(int64 DurationCycles64) const;` — As AsSeconds(Cycles64) but absolute.
- L324 _public prototype_ `double GetBaseDateTimestamp() const;` — Returns the double timestamp in unix for when the trace started.

#### struct `UE::Trace::IAnalyzer::FOnEventContext`  
`struct FOnEventContext`  
_L327-332_
- L329 _public member_ `const FThreadInfo& ThreadInfo;`
- L330 _public member_ `const FEventTime& EventTime;`
- L331 _public member_ `const FEventData& EventData;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API TRACEANALYSIS_API`
- L16 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Trace` (scope `UE`)
- L411 _typedef_ `using integral8 = std::conditional_t<std::is_signed_v<ValueType>, int8, uint8>;` (scope `UE::Trace::IAnalyzer::CoerceValue`)
- L412 _typedef_ `using integral16 = std::conditional_t<std::is_signed_v<ValueType>, int16, uint16>;` (scope `UE::Trace::IAnalyzer::CoerceValue`)
- L413 _typedef_ `using integral32 = std::conditional_t<std::is_signed_v<ValueType>, int32, uint32>;` (scope `UE::Trace::IAnalyzer::CoerceValue`)
- L414 _typedef_ `using integral64 = std::conditional_t<std::is_signed_v<ValueType>, int64, uint64>;` (scope `UE::Trace::IAnalyzer::CoerceValue`)

### `Source/Developer/TraceAnalysis/Public/Trace/ControlClient.h` (Public)


#### class `UE::Trace::FControlClient`  
`class FControlClient`  
_L18-68_
- desc: Simple helper class for communicating with trace system of a running instance.
- L23 _public prototype_ `~FControlClient();` — The destructor will ensure disconnection the FControlClient class goes out of scope.
- L28 _public prototype_ `bool Connect(const TCHAR* Host, uint16 Port=1985);` — Initiates a connection to a runtime instance to control. @param Host IP address or host name of where the runtime is to be found. @returns True if a connection was made successfully.
- L33 _public prototype_ `bool Connect(const FInternetAddr& Address);` — Initiates a connection to a runtime instance to control. @param Fully qualified FInternetAddr object of the runtime's location. @returns True if a connection was made successfully.
- L36 _public prototype_ `void Disconnect();` — Disconnects the client from the runtime.
- L39 _public prototype_ `bool IsConnected() const;` — Returns true if the client is currently connected to a runtime
- L43 _public prototype_ `void SendSendTo(const TCHAR* Host);` — Tells the runtime to attempt to record its trace event log to a socket. @param Host Host IP address that the runtime should send events to.
- L47 _public prototype_ `void SendWriteTo(const TCHAR* Path);` — Tells the runtime to attempt to record its trace event log to a file. @param Path File system path that the runtime should write events to.
- L50 _public prototype_ `void SendStop();` — Tells the runtime to stop tracing.
- L58 _public prototype_ `void SendToggleChannel(const TCHAR* Channels, bool bState = true);` — Toggles one or more channels on and off. A channel or a comma separated list of channels can be controlled. @param Channels A single channel name or a comma separated list of channel names. @param bState True to enable channel(s), false to disable.
- L62 _public prototype_ `void Send(const TCHAR* Command);` — Sends a raw command to the instance. @param Command The command to send to the runtime (CRLF terminator not required).
- L65 _private prototype_ `void FormatAndSend(const TCHAR* Format, ...);`
- L66 _private prototype_ `void Send(const uint8* Data, int Length);`
- L67 _private member_ `FSocket* Socket = nullptr;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API TRACEANALYSIS_API`
- L12 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Trace` (scope `UE`)

### `Source/Developer/TraceAnalysis/Public/Trace/DataStream.h` (Public)


#### class `UE::Trace::IInDataStream`  
`class IInDataStream`  
_L19-47_
- L22 _public prototype_ `virtual ~IInDataStream() = default;`
- L31 _public prototype_ `virtual int32 Read(void* Data, uint32 Size) = 0;` — Reads bytes from the stream. @param Data - The pointer to buffer to read into @param Size - The maximum size that can be read in bytes @returns the number of bytes read from the stream. Zero indicates end of stream and negative values indicate errors.
- L37 _public function_ `virtual void Close()` — Closes the stream. Reading from a closed stream is considered an error.
- L46 _public function_ `virtual bool WaitUntilReady()` — Waits for the the stream to be ready to read from. Some streams may need to establish the data stream before reading can begin. A stream may not block indefinitely. @returns if the stream is ready to be read from

#### class `UE::Trace::FFileDataStream`  
`class FFileDataStream : public IInDataStream`  
_L52-73_
- inherits: `IInDataStream`
- desc: An implementation of IInDataStream that reads from a file on disk.
- L55 _public prototype_ `FFileDataStream();`
- L65 _public prototype_ `bool Open(const TCHAR* Path, bool bAllowWrite = false);` — Open the file. @param Path - The path to the file @param bAllowWrite - If true, other processes may write to the file while it is open @returns true if the file was opened successfully
- L67 _public prototype_ `virtual int32 Read(void* Data, uint32 Size) override;`
- L68 _public prototype_ `virtual void Close() override;`
- L71 _private member_ `TUniquePtr<IFileHandle> Handle;`
- L72 _private member_ `uint64 Remaining;`

#### class `UE::Trace::FDirectSocketStream`  
`class FDirectSocketStream : public IInDataStream, public FRunnable`  
_L80-131_
- inherits: `IInDataStream,FRunnable`
- desc: Creates a stream to directly consume a trace stream from the tracing application. Sets up a listening socket and stream is not considered ready until a connection is made. If a valid file writer is provided during construction, the trace data will also be written to disk.
- L83 _public prototype_ `FDirectSocketStream();`
- L84 _public prototype_ `FDirectSocketStream(TUniquePtr<FArchiveFileWriterGeneric>&& InFileWriter);`
- L93 _public prototype_ `uint16 StartListening(uint16 Port = 0);` — Initiates listening sockets. Must be called before attempting to read from the stream. @param Port - The specific port number to connect to or 0 to use any available port @returns the actual port number used for listening
- L102 _public prototype_ `bool BindToExistingConnection(FSocket&& ExistingConnectedSocket);` — Binds this instance to an existing connection that has already been established. Using this method allows you to service connections off a single listen port, then create instances of FDirectSocketStream for each connection. @param ExistingConnectedSocket is the existing socket that will transfer its ownership to this instance, even if the function fails. @returns true if the binding was successful. Note: Even if it returns false, you will have lost ownership of ExistingConnectedSocket.
- L104 _public prototype_ `virtual int32 Read(void* Data, uint32 Size) override;`
- L115 _private prototype_ `virtual bool WaitUntilReady() override;` — IInDataStream interface
- L116 _private prototype_ `virtual void Close() override;`
- L119 _private prototype_ `virtual uint32 Run() override;` — FRunnable interface
- L120 _private prototype_ `virtual void Stop() override;`
- L122 _private prototype_ `void Accept();`
- L123 _private prototype_ `bool CreateSocket(uint16 Port);`
- L126 _private member_ `TUniquePtr<struct FDirectSocketContext> AsioContext;`
- L127 _private member_ `TUniquePtr<class FTraceDataStream> InternalStream;`
- L128 _private member_ `TUniquePtr<class FRunnableThread> ListeningThread;`
- L129 _private member_ `TUniquePtr<FArchiveFileWriterGeneric> FileWriter;`
- L130 _private member_ `FEvent* ConnectionEvent;`

#### enum `UE::Trace::FDirectSocketStream::(anonymous)`  
``  
_L108-112_

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TRACEANALYSIS_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Trace` (scope `UE`)
- L109 _enumerator_ `DefaultPort = 1986` (scope `UE::Trace::FDirectSocketStream::__anone659a0950103`) — Default port to use.
- L110 _enumerator_ `MaxPortAttempts = 16` (scope `UE::Trace::FDirectSocketStream::__anone659a0950103`) — How many port increments are tried if fail to bind default.
- L111 _enumerator_ `MaxQueuedConnections = 4` (scope `UE::Trace::FDirectSocketStream::__anone659a0950103`) — Size of connection queue.

### `Source/Developer/TraceAnalysis/Public/Trace/OutDataStream.h` (Public)


#### class `UE::Trace::IOutDataStream`  
`class IOutDataStream`  
_L16-44_
- L19 _public prototype_ `virtual ~IOutDataStream() = default;`
- L28 _public prototype_ `virtual int32 Write(void* Data, uint32 Size) = 0;` — Writes bytes to the stream. @param Data - The pointer to the data buffer to read from and write to the stream @param Size - The number of bytes to read from the Data buffer and to write to the stream @returns the number of bytes written to the stream. Negative values indicate errors.
- L34 _public function_ `virtual void Close()` — Closes the stream. Writing to a closed stream is considered an error.
- L43 _public function_ `virtual bool WaitUntilReady()` — Waits for the stream to be ready to write to. Some streams may need to establish the data stream before writing can begin. A stream may not block indefinitely. @returns if the stream is ready to be write to

#### class `UE::Trace::FFileOutDataStream`  
`class FFileOutDataStream : public IOutDataStream`  
_L49-68_
- inherits: `IOutDataStream`
- desc: An implementation of IOutDataStream that writes to a file on disk.
- L52 _public prototype_ `FFileOutDataStream();`
- L61 _public prototype_ `bool Open(const TCHAR* Path);` — Open the file. @param Path - The path to the file @returns true if the file was opened successfully
- L63 _public prototype_ `virtual int32 Write(void* Data, uint32 Size) override;`
- L64 _public prototype_ `virtual void Close() override;`
- L67 _private member_ `TUniquePtr<IFileHandle> Handle;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TRACEANALYSIS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Trace` (scope `UE`)

### `Source/Developer/TraceAnalysis/Public/Trace/SecureDataStream.h` (Public)


#### class `UE::Trace::FSecureSocketStream`  
`class FSecureSocketStream : public UE::Trace::IInDataStream, public ::FRunnable`  
_L30-144_
- inherits: `UE::Trace::IInDataStream,::FRunnable`
- L33 _public prototype_ `FSecureSocketStream();`
- L34 _public prototype_ `FSecureSocketStream(TUniquePtr<FArchiveFileWriterGeneric>&& InFileWriter);`
- L45 _public prototype_ `bool ConnectWithCertificate(FStringView Host, uint16 Port, TConstArrayView<uint8> AuthToken, FStringView CertificatePath);` — Connect to a tracing host. Specify a authorization token and an optional trusted CA certificate file. @param Host Hostname to connect to. @param Port Port to connect to. @param AuthToken Authorization token to send. @param CertificatePath Optional path to trusted root certificate @return True on success, false if not.
- L55 _public prototype_ `bool ConnectWithSelfSigned(FStringView Host, uint16 Port, TConstArrayView<uint8> AuthToken, TConstArrayView<uint8> Certificate);` — Connect to a tracing host. Specify a authorization token and an optional trusted in-memory CA certificate. @param Host Hostname to connect to. @param Port Port to connect to. @param AuthToken Authorization token to send. @param Certificate A self-signed root certificate in DER format. @return True on success, false if not.
- L65 _public prototype_ `bool ConnectWithPreSharedKey(FStringView Host, uint16 Port, TConstArrayView<uint8> PreSharedKey, FAnsiStringView Identity);` — Connect to a tracing host. Specify an authorization token used for pre-shared key verification. @param Host Hostname to connect to. @param Port Port to connect to. @param PreSharedKey Key to use in secure handshake @param Identity Identity to use in secure handshake @return True on success, false if not.
- L68 _public prototype_ `virtual int32 Read(void* Data, uint32 Size) override;`
- L89 _private prototype_ `bool ConnectInternal(FStringView Host, uint16 Port, TConstArrayView<uint8> AuthToken);`
- L92 _private prototype_ `virtual bool WaitUntilReady() override;` — IInStream interface
- L93 _private prototype_ `virtual void Close() override;`
- L96 _private prototype_ `virtual uint32 Run() override;` — FRunnable interface
- L97 _private prototype_ `virtual void Stop() override;`
- L100 _private prototype_ `void AsyncHandshake();` — Async data functions
- L101 _private prototype_ `void AsyncAuthenticate(int32 Offset = 0);`
- L103 _private prototype_ `void AsyncRecieveData();`
- L106 _private prototype_ `bool LoadCertificateAuthority(FStringView InCertificatePath);`
- L107 _private prototype_ `bool SetCertificateAuthority(TConstArrayView<uint8> CA);`
- L108 _private prototype_ `bool SetPreSharedKey();`
- L109 _private prototype_ `void SetState(EState NewState, bool bTriggerReady);`
- L128 _private member_ `TUniquePtr<struct FSecureSocketContext> AsioContext;`
- L129 _private member_ `TUniquePtr<class FRunnableThread> IoThread;`
- L130 _private member_ `FEvent* ReadyToReadEvent;`
- L131 _private member_ `TUniquePtr<class FArchiveFileWriterGeneric> FileWriter;`
- L132 _private member_ `EState State;`
- L133 _private member_ `TArray<uint8> AuthToken;`
- L134 _private member_ `FAnsiString Identity;`
- L135 _private member_ `ESecureMode Mode = ESecureMode::None;`
- L137 _private member_ `static constexpr int32 BufferCapacity = 512 * 1024;`
- L138 _private member_ `TArray<uint8> ReadBuffer;`
- L139 _private member_ `uint32 BufferedBytes = 0u;`
- L140 _private member_ `TSpscQueue<FData> ReadQueue;`

#### enum `UE::Trace::FSecureSocketStream::(anonymous)`  
``  
_L72-76_

#### enum `UE::Trace::FSecureSocketStream::EState`  
`enum class EState : uint8`  
_L78-87_
- L80 _public enumerator_ `None = 0`
- L81 _public enumerator_ `Closed`
- L82 _public enumerator_ `Connecting`
- L83 _public enumerator_ `Handshaking`
- L84 _public enumerator_ `Authenticating`
- L85 _public enumerator_ `Open`
- L86 _public enumerator_ `Failed = 0xff`

#### enum `UE::Trace::FSecureSocketStream::ESecureMode`  
`enum class ESecureMode : uint8`  
_L113-118_
- L115 _public enumerator_ `None`
- L116 _public enumerator_ `Certificates`
- L117 _public enumerator_ `PreSharedKeys`

#### class `UE::Trace::FSecureSocketStream::FData`  
`class FData : public TArray<uint8>`  
_L120-126_
- inherits: `TArray<uint8>`
- L123 _public function_ `FData(uint8* Data, int32 Size) : TArray<uint8>(TArrayView<uint8>(Data, Size))`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API TRACEANALYSIS_API`
- L17 _macro_ `#define UE_TRACE_ANALYSIS_SSS_ENABLED WITH_SHARED_ASIO_SSL_SUPPORT` — Secure socket stream support depends on SSL support in ASIO
- L21 _macro_ `#define UE_TRACE_ANALYSIS_SSS_BUFFERED 1` — Enables experimental buffered receiving path for FSecureSocketStream
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace Trace` (scope `UE`)
- L73 _enumerator_ `DefaultPort = 1986` (scope `UE::Trace::FSecureSocketStream::__anon37f8433c0103`) — Default port to use.
- L74 _enumerator_ `MaxPortAttempts = 16` (scope `UE::Trace::FSecureSocketStream::__anon37f8433c0103`) — How many port increments are tried if fail to bind default.
- L75 _enumerator_ `MaxQueuedConnections = 4` (scope `UE::Trace::FSecureSocketStream::__anon37f8433c0103`) — Size of connection queue.

### `Source/Developer/TraceAnalysis/Public/Trace/StoreClient.h` (Public)


#### class `UE::Trace::FStoreClient`  
`class FStoreClient`  
_L19-93_
- L56 _public prototype_ `~FStoreClient() = default;`
- L58 _public prototype_ `static FStoreClient* Connect(const TCHAR* Host, uint32 Port = 0);` — `UE_DEPRECATED(5.8, "Connect has been deprecated. Please use Create which returns a TUniquePtr instead.")`
- L59 _public prototype_ `static TUniquePtr<FStoreClient> Create(const TCHAR* Host, uint32 Port = 0);`
- L60 _public prototype_ `bool Reconnect(const TCHAR* Host, uint32 Port);`
- L61 _public prototype_ `void operator delete (void* Addr);`
- L62 _public prototype_ `bool IsValid() const;`
- L63 _public prototype_ `uint32 GetStoreAddress() const;`
- L64 _public prototype_ `uint32 GetStorePort() const;`
- L65 _public prototype_ `const FStatus* GetStatus() const;`
- L66 _public prototype_ `const FVersion* GetVersion() const;`
- L67 _public prototype_ `uint32 GetTraceCount() const;`
- L68 _public prototype_ `const FTraceInfo* GetTraceInfo(uint32 Index) const;`
- L69 _public prototype_ `const FTraceInfo* GetTraceInfoById(uint32 Id) const;`
- L70 _public prototype_ `FTraceData ReadTrace(uint32 Id) const;`
- L71 _public prototype_ `bool SetStoreDirectories(const TCHAR* StoreDir, const TArray<FString>& AddWatchDirs, const TArray<FString>& RemoveWatchDirs);`
- L72 _public prototype_ `bool SetSponsored(bool bSponsored);`
- L81 _public prototype_ `uint32 GetSessionCount() const;`
- L82 _public prototype_ `const FSessionInfo* GetSessionInfo(uint32 Index) const;`
- L83 _public prototype_ `const FSessionInfo* GetSessionInfoById(uint32 Id) const;`
- L84 _public prototype_ `const FSessionInfo* GetSessionInfoByTraceId(uint32 TraceId) const;`
- L85 _public prototype_ `const FSessionInfo* GetSessionInfoByGuid(const FGuid& TraceGuid) const;`
- L88 _private prototype_ `FStoreClient() = default;`
- L89 _private prototype_ `FStoreClient(const FStoreClient&) = delete;`
- L90 _private prototype_ `FStoreClient(const FStoreClient&&) = delete;`
- L91 _private prototype_ `void operator = (const FStoreClient&) = delete;`
- L92 _private prototype_ `void operator = (const FStoreClient&&) = delete;`

#### struct `UE::Trace::FStoreClient::FStatus`  
`struct FStatus`  
_L22-31_
- L24 _public prototype_ `FUtf8StringView GetStoreDir() const;`
- L25 _public prototype_ `uint32 GetRecorderPort() const;`
- L26 _public prototype_ `uint32 GetStorePort() const;`
- L27 _public prototype_ `bool GetSponsored() const;`
- L28 _public prototype_ `uint32 GetChangeSerial() const;`
- L29 _public prototype_ `uint32 GetSettingsSerial() const;`
- L30 _public prototype_ `void GetWatchDirectories(TArray<FString>& OutDirs) const;`

#### struct `UE::Trace::FStoreClient::FVersion`  
`struct FVersion`  
_L33-38_
- L35 _public prototype_ `uint32 GetMajorVersion() const;`
- L36 _public prototype_ `uint32 GetMinorVersion() const;`
- L37 _public prototype_ `FUtf8StringView GetConfiguration() const;`

#### struct `UE::Trace::FStoreClient::FTraceInfo`  
`struct FTraceInfo`  
_L40-48_
- L42 _public prototype_ `FUtf8StringView GetName() const;`
- L43 _public prototype_ `uint32 GetId() const;`
- L44 _public prototype_ `uint64 GetSize() const;`
- L45 _public prototype_ `uint64 GetTimestamp() const;`
- L46 _public prototype_ `FUtf8StringView GetUri() const;`
- L47 _public prototype_ `FUtf8StringView GetMetadataUri() const;`

#### struct `UE::Trace::FStoreClient::FTraceData`  
`struct FTraceData : public TUniquePtr<IInDataStream>`  
_L50-54_
- inherits: `TUniquePtr<IInDataStream>`

#### struct `UE::Trace::FStoreClient::FSessionInfo`  
`struct FSessionInfo`  
_L74-80_
- L76 _public prototype_ `uint32 GetId() const;`
- L77 _public prototype_ `uint32 GetTraceId() const;`
- L78 _public prototype_ `uint32 GetIpAddress() const;`
- L79 _public prototype_ `uint32 GetControlPort() const;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TRACEANALYSIS_API`
- L13 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Trace` (scope `UE`)

### `Source/Developer/TraceAnalysis/Public/Trace/StoreConnection.h` (Public)


#### class `UE::Trace::FStoreConnection`  
`class FStoreConnection`  
_L18-57_
- L21 _public prototype_ `FStoreConnection();`
- L22 _public prototype_ `virtual ~FStoreConnection();`
- L24 _public prototype_ `bool ConnectToStore(const TCHAR* Host, uint32 Port = 0);`
- L30 _public prototype_ `bool ReconnectToStore();` — Attempt to reconnect to the store if the connection was severed, without recreating the store client. @return True on success, false on failure
- L32 _public prototype_ `void Disconnect();`
- L34 _public function_ `UE::Trace::FStoreClient* GetStoreClient() const`
- L35 _public function_ `FCriticalSection& GetStoreClientCriticalSection() const`
- L37 _public prototype_ `bool GetStoreAddressAndPort(uint32& OutStoreAddress, uint32& OutStorePort) const;`
- L38 _public prototype_ `FString GetStoreDir() const;`
- L40 _public function_ `const FString& GetLastStoreHost() const`
- L41 _public function_ `uint32 GetLastStorePort() const`
- L43 _public function_ `const bool IsLocalHost() const`
- L44 _public function_ `const bool CanChangeStoreSettings() const`
- L48 _private member_ `TUniquePtr<UE::Trace::FStoreClient> StoreClient;` — The client used to connect to the trace store. It is not thread safe!
- L51 _private member_ `mutable FCriticalSection StoreClientCriticalSection;` — CriticalSection for using the store client's API.
- L53 _private member_ `FString LastStoreHost;`
- L54 _private member_ `uint32 LastStorePort = 0;`
- L56 _private member_ `bool bIsLocalHost = false;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TRACEANALYSIS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Trace` (scope `UE`)

### `Source/Developer/TraceAnalysis/Public/Trace/StoreService.h` (Public)


#### class `UE::Trace::FStoreService`  
`class FStoreService`  
_L14-36_
- L24 _public prototype_ `~FStoreService() = default;`
- L25 _public prototype_ `static FStoreService* Create(const FDesc& Desc);`
- L26 _public prototype_ `void operator delete (void* Addr);`
- L27 _public prototype_ `uint32 GetPort() const;`
- L28 _public prototype_ `uint32 GetRecorderPort() const;`
- L31 _private prototype_ `FStoreService() = default;`
- L32 _private prototype_ `FStoreService(const FStoreService&) = delete;`
- L33 _private prototype_ `FStoreService(const FStoreService&&) = delete;`
- L34 _private prototype_ `void operator = (const FStoreService&) = delete;`
- L35 _private prototype_ `void operator = (const FStoreService&&) = delete;`

#### struct `UE::Trace::FStoreService::FDesc`  
`struct FDesc`  
_L17-22_
- L19 _public member_ `const TCHAR* StoreDir;`
- L20 _public member_ `int32 RecorderPort = 0;` — 0:auto-assign, -1:off
- L21 _public member_ `int32 ThreadCount = 0;` — <=0:logical CPU count

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API TRACEANALYSIS_API`
- L10 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Trace` (scope `UE`)

### `Source/Developer/TraceAnalysis/Public/Trace/TraceWriter.h` (Public)


#### class `UE::Trace::FTraceWriterThreadInfo`  
`class FTraceWriterThreadInfo final`  
_L31-57_
- L36 _public prototype_ `FTraceWriterThreadInfo() = default;`
- L37 _public function_ `FTraceWriterThreadInfo(uint32 InThreadId, FAnsiStringView InName, uint32 InSystemId = 0, int32 InSortHint = 0) : Id(InThreadId) , Name(InName) , SystemId(InSystemId) , SortHint(InSortHint)`
- L45 _public function_ `[[nodiscard]] uint32 GetId() const`
- L46 _public function_ `[[nodiscard]] const FAnsiString& GetName() const`
- L47 _public function_ `[[nodiscard]] uint32 GetSystemId() const`
- L48 _public function_ `[[nodiscard]] int32 GetSortHint() const`
- L50 _public member_ `static constexpr uint32 InvalidThreadId = ~0u;`
- L53 _private member_ `uint32 Id = InvalidThreadId;`
- L54 _private member_ `FAnsiString Name;`
- L55 _private member_ `uint32 SystemId = 0;`
- L56 _private member_ `int32 SortHint = 0;`

#### enum `UE::Trace::ETraceWriterEventFlags`  
`enum class ETraceWriterEventFlags : uint8`  
_L65-75_
- desc: Flags for a trace event. See UE::Trace::Protocol6::EEventFlags (Trace\Detail\Protocols\Protocol6.h in TraceLog module). See UE::Trace::IAnalyzer::EEventFlags (Trace\Analyzer.h in TraceAnalysis module).
- L67 _public enumerator_ `None = 0`
- L69 _public enumerator_ `Important = 1 << 0`
- L70 _public enumerator_ `MaybeHasAux = 1 << 1`
- L71 _public enumerator_ `NoSync = 1 << 2`
- L72 _public enumerator_ `Definition = 1 << 3`
- L74 _public enumerator_ `ImportantNoSync = Important | NoSync`

#### enum `UE::Trace::ETraceWriterFieldType`  
`enum class ETraceWriterFieldType : uint8`  
_L86-139_
- desc: Field type. See UE::Trace::Protocol0::EFieldType (Trace\Detail\Protocols\Protocol0.h in TraceLog module). { Bool = 0, Int8, Int16, Int32, Int64, Uint8 = 0, Uint16, Uint32, Uint64, ..., Pointer = Uint64, ..., Array } See also UE::Trace::IAnalyzer::FEventFieldInfo::EType { None, Integer, Float, AnsiString, WideString, Reference8, Reference16, Reference32, Reference64 }
- L88 _public enumerator_ `ArrayFlag = 0x80`
- L89 _public enumerator_ `ReferenceFlag = 0x40` — can be combined with Uint8,Uint16,Uint32,Uint64 types
- L90 _public enumerator_ `DefinitionIdFlag = 0x20` — can be combined with Uint8,Uint16,Uint32,Uint64 types
- L91 _public enumerator_ `FlagsMask = 0xE0`
- L92 _public enumerator_ `IndexMask = 0x1F`
- L94 _public enumerator_ `None = 0`
- L97 _public enumerator_ `Bool = 1` — Boolean type
- L100 _public enumerator_ `Uint8 = 2` — Unsigned integer types
- L101 _public enumerator_ `Uint16 = 3`
- L102 _public enumerator_ `Uint32 = 4`
- L104 _public enumerator_ `Uint64 = 6` — VarUInt32           = 5, // variable size, 1 to 5 bytes
- L108 _public enumerator_ `Int8 = 8` — Signed integer types
- L109 _public enumerator_ `Int16 = 9`
- L110 _public enumerator_ `Int32 = 10`
- L112 _public enumerator_ `Int64 = 12` — VarInt32            = 11, // variable size, 1 to 5 bytes
- L116 _public enumerator_ `Float32 = 14` — Floating-point number types
- L117 _public enumerator_ `Float64 = 15` — double
- L120 _public enumerator_ `AnsiString = 16` — String types
- L121 _public enumerator_ `WideString = 17`
- L124 _public enumerator_ `Pointer = 19` — void* (64 bits)
- L126 _public enumerator_ `Count = 20`
- L129 _public enumerator_ `Reference8 = ReferenceFlag | Uint8` — Reference composed types
- L130 _public enumerator_ `Reference16 = ReferenceFlag | Uint16`
- L131 _public enumerator_ `Reference32 = ReferenceFlag | Uint32`
- L132 _public enumerator_ `Reference64 = ReferenceFlag | Uint64`
- L135 _public enumerator_ `DefinitionId8 = DefinitionIdFlag | Uint8` — DefinitionId composed types
- L136 _public enumerator_ `DefinitionId16 = DefinitionIdFlag | Uint16`
- L137 _public enumerator_ `DefinitionId32 = DefinitionIdFlag | Uint32`
- L138 _public enumerator_ `DefinitionId64 = DefinitionIdFlag | Uint64`

#### struct `UE::Trace::FTraceWriterFieldTypeResolver`  
`struct FTraceWriterFieldTypeResolver`  
_L144-212_
- L147 _public function_ `template <typename NativeType> static constexpr ETraceWriterFieldType GetType()`

#### class `UE::Trace::FTraceWriterEventFieldInfo`  
`class FTraceWriterEventFieldInfo final`  
_L216-244_
- L222 _public prototype_ `FTraceWriterEventFieldInfo() = delete;`
- L223 _public function_ `FTraceWriterEventFieldInfo(FAnsiStringView InFieldName, ETraceWriterFieldType InFieldType) : Name(FAnsiString(InFieldName)) , Type(InFieldType)`
- L229 _public function_ `[[nodiscard]] const FAnsiString& GetName() const`
- L230 _public function_ `[[nodiscard]] ETraceWriterFieldType GetType() const`
- L231 _public function_ `[[nodiscard]] uint16 GetSize() const`
- L232 _public function_ `[[nodiscard]] uint16 GetRefUid() const`
- L234 _public prototype_ `[[nodiscard]] inline uint8 GetProtocolFieldFamily() const;`
- L235 _public prototype_ `[[nodiscard]] inline uint8 GetProtocolFieldType() const;`
- L237 _public function_ `bool IsArray() const`
- L240 _private member_ `FAnsiString Name;`
- L241 _private member_ `ETraceWriterFieldType Type = ETraceWriterFieldType::None;`
- L242 _private member_ `uint16 Size = 0;`
- L243 _private member_ `uint16 RefUid = 0;`
- L1099 _function_ `uint8 FTraceWriterEventFieldInfo::GetProtocolFieldFamily() const`
- L1106 _function_ `uint8 FTraceWriterEventFieldInfo::GetProtocolFieldType() const`

#### class `UE::Trace::FTraceWriterEventInfo`  
`class FTraceWriterEventInfo final`  
_L248-286_
- L254 _private prototype_ `FTraceWriterEventInfo() = delete;`
- L257 _private function_ `FTraceWriterEventInfo(FAnsiStringView InLoggerName, FAnsiStringView InEventName, ETraceWriterEventFlags InEventFlags) : LoggerName(FAnsiString(InLoggerName)) , Name(FAnsiString(InEventName)) , Flags(InEventFlags)` — Constructor only accessible from the FTraceWriter class
- L265 _public function_ `[[nodiscard]] uint32 GetId() const`
- L266 _public function_ `[[nodiscard]] const FAnsiString& GetLoggerName() const`
- L267 _public function_ `[[nodiscard]] const FAnsiString& GetName() const`
- L268 _public function_ `[[nodiscard]] ETraceWriterEventFlags GetFlags() const`
- L269 _public function_ `[[nodiscard]] uint32 GetNumFields() const`
- L270 _public function_ `[[nodiscard]] const FTraceWriterEventFieldInfo& GetField(uint32 InFieldIndex) const`
- L271 _public function_ `[[nodiscard]] const TArray<FTraceWriterEventFieldInfo>& GetFields() const`
- L272 _public prototype_ `[[nodiscard]] uint32 GetFieldIndex(FAnsiStringView InFieldName) const;`
- L274 _public function_ `bool IsNoSync() const`
- L275 _public function_ `bool IsSync() const`
- L276 _public function_ `bool IsImportant() const`
- L277 _public function_ `bool MaybeHasAux() const`
- L278 _public function_ `bool IsDefinition() const`
- L281 _private member_ `uint32 Id = 0;`
- L282 _private member_ `FAnsiString LoggerName;`
- L283 _private member_ `FAnsiString Name;`
- L284 _private member_ `ETraceWriterEventFlags Flags = ETraceWriterEventFlags::None;`
- L285 _private member_ `TArray<FTraceWriterEventFieldInfo> Fields;`

#### class `UE::Trace::FTraceWriterEventDeclarationBuilder`  
`class FTraceWriterEventDeclarationBuilder final`  
_L290-349_
- L295 _private prototype_ `FTraceWriterEventDeclarationBuilder() = delete;`
- L298 _private function_ `FTraceWriterEventDeclarationBuilder(FTraceWriter& InWriter, FTraceWriterEventInfo& InEventInfo) : Writer(InWriter) , EventInfo(InEventInfo)` — Constructor only accessible from the FTraceWriter class
- L304 _private prototype_ `~FTraceWriterEventDeclarationBuilder();`
- L307 _public function_ `[[nodiscard]] FTraceWriterEventInfo& GetEventInfo() const`
- L319 _public prototype_ `FTraceWriterEventDeclarationBuilder& Field(FAnsiStringView InFieldName, ETraceWriterFieldType InFieldType);` — Adds a new regular field to the current event declaration. @param InFieldName - The name of the field. @param InFieldType - The type of the field. @returns - The event declaration builder object.
- L329 _public prototype_ `FTraceWriterEventDeclarationBuilder& ReferenceField(FAnsiStringView InFieldName, ETraceWriterFieldType InFieldType, uint16 InRefUid);` — Adds a new Reference field to the current event declaration. @param InFieldName - The name of the field. @param InFieldType - The type of the field. Can only be Reference8, Reference16, Reference32 or Reference64. @param InRefUid - The reference unique id. @returns - The event declaration builder object.
- L336 _public prototype_ `FTraceWriterEventDeclarationBuilder& DefinitionIdField(ETraceWriterFieldType InFieldType);` — Adds a new DefinitionId field to the current event declaration. @param InFieldType - The type of the field. Can only be DefinitionId8, DefinitionId16, DefinitionId32 or DefinitionI64. @returns - The event declaration builder object.
- L343 _public prototype_ `[[nodiscard]] uint32 End();` — Signals the event declaration is complete. @returns the event id of the newly declared event
- L346 _private member_ `FTraceWriter& Writer;`
- L347 _private member_ `FTraceWriterEventInfo& EventInfo;`
- L348 _private member_ `bool bIsCompleted = false;`

#### class `UE::Trace::FTraceWriterFieldData`  
`class FTraceWriterFieldData`  
_L353-378_
- L356 _public prototype_ `FTraceWriterFieldData() = default;`
- L357 _public prototype_ `~FTraceWriterFieldData();`
- L359 _public function_ `const void* GetData() const`
- L363 _public function_ `uint32 GetSize() const`
- L367 _public prototype_ `void SetData(const void* InData, uint32 InDataSize);`
- L370 _private member_ `static constexpr uint32 MaxInlineDataSize = 12;` — Data + Data2
- L376 _private member_ `uint32 Data2 = 0;`
- L377 _private member_ `uint32 Size = 0;`

#### union `UE::Trace::FTraceWriterFieldData::(anonymous)`  
``  
_L372-375_

#### class `UE::Trace::FTraceWriterEventBuilder`  
`class FTraceWriterEventBuilder final`  
_L383-602_
- L388 _private function_ `FTraceWriterEventBuilder(FTraceWriter& InWriter, const FTraceWriterEventInfo& InEventInfo) : Writer(InWriter) , EventInfo(InEventInfo)`
- L398 _private prototype_ `~FTraceWriterEventBuilder();`
- L401 _public function_ `[[nodiscard]] const FTraceWriterEventInfo& GetEventInfo() const`
- L410 _public prototype_ `FTraceWriterEventBuilder& Field(uint32 Index, const void* Data, uint32 DataSize);`
- L412 _public function_ `FTraceWriterEventBuilder& Field(FAnsiStringView Name, const void* Data, uint32 DataSize)`
- L418 _public function_ `template <typename T> FTraceWriterEventBuilder& Field(uint32 Index, TConstArrayView<T> ArrayView)`
- L424 _public function_ `template <typename T> FTraceWriterEventBuilder& Field(uint32 Index, TArrayView<T> ArrayView)`
- L439 _public function_ `FTraceWriterEventBuilder& Field(uint32 Index, T Value)`
- L452 _public function_ `FTraceWriterEventBuilder& Field(uint32 Index, const void* Value)`
- L461 _public function_ `FTraceWriterEventBuilder& Field(FAnsiStringView Name, const void* Value)`
- L466 _public function_ `FTraceWriterEventBuilder& Field(uint32 Index, void* Value)`
- L475 _public function_ `FTraceWriterEventBuilder& Field(FAnsiStringView Name, void* Value)`
- L483 _public function_ `FTraceWriterEventBuilder& Field(uint32 Index, UE::Trace::FEventRef8 Value)`
- L492 _public function_ `FTraceWriterEventBuilder& Field(uint32 Index, UE::Trace::FEventRef16 Value)`
- L501 _public function_ `FTraceWriterEventBuilder& Field(uint32 Index, UE::Trace::FEventRef32 Value)`
- L510 _public function_ `FTraceWriterEventBuilder& Field(uint32 Index, UE::Trace::FEventRef64 Value)`
- L524 _public function_ `template <typename T = FAnsiStringView> FTraceWriterEventBuilder& Field(uint32 Index, FAnsiStringView Value UE_LIFETIMEBOUND)` — Construct field from an FAnsiStringView.
- L535 _public function_ `template <typename T = const ANSICHAR*> FTraceWriterEventBuilder& Field(uint32 Index, const ANSICHAR* InData UE_LIFETIMEBOUND)` — Construct field from the null-terminated string pointed to by InData.
- L542 _public function_ `template <typename T = const FAnsiString&> FTraceWriterEventBuilder& Field(uint32 Index, const FAnsiString& Value UE_LIFETIMEBOUND)` — Construct field from an FAnsiString.
- L552 _public function_ `template <typename T = FStringView> FTraceWriterEventBuilder& Field(uint32 Index, const FStringView Value UE_LIFETIMEBOUND)` — Construct field from an FStringView.
- L563 _public function_ `template <typename T = const TCHAR*> FTraceWriterEventBuilder& Field(uint32 Index, const TCHAR* Value UE_LIFETIMEBOUND)` — Construct field from the null-terminated string pointed to by InData.
- L570 _public function_ `template <typename T = const FString&> FTraceWriterEventBuilder& Field(uint32 Index, const FString& Value UE_LIFETIMEBOUND)` — Construct field from an FString.
- L579 _public function_ `template <typename T> FTraceWriterEventBuilder& Field(FAnsiStringView Name, T Value)`
- L586 _public prototype_ `void End();`
- L589 _private prototype_ `void SetErrorInvalidFieldIndex(uint32 Index);`
- L590 _private prototype_ `void SetErrorInvalidFieldType(uint32 Index);`
- L591 _private prototype_ `void SetErrorInvalidFieldData(uint32 Index);`
- L593 _private prototype_ `bool CheckValidPodField(uint32 Index, ETraceWriterFieldType FieldType, uint32 Size);`
- L594 _private prototype_ `bool CheckValidExactFieldType(uint32 Index, ETraceWriterFieldType FieldType);`
- L595 _private prototype_ `void SetField(uint32 Index, const void* Data, uint32 DataSize);`
- L598 _private member_ `FTraceWriter& Writer;`
- L599 _private member_ `const FTraceWriterEventInfo& EventInfo;`
- L600 _private member_ `TArray<FTraceWriterFieldData> Fields;`
- L601 _private member_ `bool bIsCompleted = false;`

#### enum `UE::Trace::ETraceWriterBeginOptions`  
`enum class ETraceWriterBeginOptions : uint32`  
_L606-614_
- L608 _public enumerator_ `None = 0`
- L610 _public enumerator_ `DeclareDefaultEvents = 1 << 1`
- L611 _public enumerator_ `WriteNewTraceEvent = 1 << 2`
- L613 _public enumerator_ `Default = DeclareDefaultEvents | WriteNewTraceEvent`

#### class `UE::Trace::FTraceWriter`  
`class FTraceWriter`  
_L619-1095_
- L632 _public prototype_ `FTraceWriter(IOutDataStream& InStream);`
- L633 _public prototype_ `~FTraceWriter();`
- L635 _public prototype_ `FTraceWriter(const FTraceWriter&) = delete;`
- L636 _public prototype_ `FTraceWriter& operator=(const FTraceWriter&) = delete;`
- L641 _public prototype_ `UE::Trace::ETransport GetTransportProtocolVersion() const;` — Returns the version of the transport protocol used by this trace writer.
- L650 _public prototype_ `uint8 GetTraceProtocolVersion() const;` — Returns the version of the trace protocol used by this trace writer. Currently this is Protocol 7. \details See UE::Trace::Protocol7::EProtocol::Id (Trace/Detail/Protocols/Protocol7.h).
- L658 _public prototype_ `void Begin(ETraceWriterBeginOptions Options = ETraceWriterBeginOptions::Default);` — Begins the trace stream. Calls DeclareDefaultEvents() and WriteNewTraceEvent() depending on Options flags. @param Options - Various toggle options to allow custom control of Begin() behavior
- L666 _public prototype_ `void End();` — Ends the trace stream. \details Calls Close() for the stream.
- L674 _public prototype_ `void DeclareDefaultEvents();` — Declares the default trace events. \details Declares: $Trace.* events
- L683 _public prototype_ `void WriteNewTraceEvent();` — Writes the $Trace.NewTrace event. Changes the current thread to be the "Importants" thread. \details Writes: $Trace.NewTrace
- L701 _public prototype_ `uint32 RegisterThread(FAnsiStringView ThreadName, uint32 SystemId = 0, int32 SortHint = 0, bool bShouldWriteThreadInfo = true);` — Registers a new trace thread. If a thread with same name is already registered, this will just return the registered thread id. If successfully registering a new thread and bShouldWriteThreadInfo is true, then this function will call WriteThreadInfo() automatically. @param ThreadName - The thread name @param SystemId - The system thread id @param SortHint - A hint for sorting priority @param bShouldWriteThreadInfo - Wherever should write the $Trace.ThreadInfo or not @returns the thread id for the new trace thread
- L715 _public prototype_ `void RegisterCustomThread(uint32 ThreadId, FAnsiStringView ThreadName, uint32 SystemId = 0, int32 SortHint = 0, bool bShouldWriteThreadInfo = true);` — Registers a trace thread with a known id. If a thread with the specified id is already registered, this will fail. If successfully registering a new thread and bShouldWriteThreadInfo is true, then this function will call WriteThreadInfo() automatically. @param ThreadId - The thread id @param ThreadName - The thread name @param SystemId - The system thread id @param SortHint - A hint for sorting priority @param bShouldWriteThreadInfo - Wherever should write the $Trace.ThreadInfo or not
- L723 _public function_ `const FTraceWriterThreadInfo* GetThreadInfo(uint32 ThreadId)` — Gets the info for a registered thread identified by Id. @param ThreadId - The thread id @returns a pointer to the thread info or nullptr if the ThreadId is not valid (thread not registered).
- L737 _public prototype_ `void WriteThreadInfo(uint32 ThreadId);` — Writes the $Trace.ThreadInfo event for a registered thread, identified by id. Changes the current thread to be the "Importants" thread. \details Writes: $Trace.ThreadInfo @param ThreadId - The thread id
- L751 _public prototype_ `void WriteThreadInfo(uint32 ThreadId, FAnsiStringView ThreadName, uint32 SystemId = 0, int32 SortHint = 0);` — Writes the $Trace.ThreadInfo event. Changes the current thread to be the "Importants" thread. \details Writes: $Trace.ThreadInfo @param ThreadId - The thread id @param ThreadName - The thread name @param SystemId - The system thread id @param SortHint - A hint for sorting priority
- L758 _public prototype_ `void SetCurrentThread(uint32 ThreadId);` — Sets the current thread id. @param ThreadId - The thread id.
- L763 _public function_ `void SetCurrentThreadEvents()` — Sets the current thread to be the "Events" thread.
- L768 _public function_ `void SetCurrentThreadImportants()` — Sets the current thread to be the "Importants" thread.
- L775 _public function_ `uint32 GetCurrentThread() const` — Gets the current thread id. @returns the current thread id
- L782 _public prototype_ `void WriteThreadTimingEvent(uint64 BaseTimestamp);` — Writes a $Trace.ThreadTiming event for the current thread. @param BaseTimestamp - The base timestamp [ticks]
- L793 _public prototype_ `void WriteThreadGroupBeginEvent(FAnsiStringView GroupName);` — Writes a $Trace.ThreadGroupBegin event. Changes the current thread to be the "Importants" thread. \details Writes: $Trace.ThreadGroupBegin @param GroupName - The group name
- L802 _public prototype_ `void WriteThreadGroupEndEvent();` — Writes a $Trace.ThreadGroupEnd event. Changes the current thread to be the "Importants" thread. \details Writes: $Trace.ThreadGroupEnd
- L812 _public function_ `const FTraceWriterEventInfo* GetEventInfo(uint32 EventId) const` — Gets the info for an event identified by Id. @param EventId - The event id, one returned by DeclareEvent().[...].End() or similar method. @returns a pointer to the event info or nullptr if the EventId is not valid.
- L824 _public prototype_ `const FTraceWriterEventInfo* FindEvent(FAnsiStringView LoggerName, FAnsiStringView EventName) const;` — Gets the info for an event identified by logger and event names. @param LoggerName - The logger name @param Name - The event name @returns a pointer to the event info or nullptr if the event is not found.
- L842 _public prototype_ `[[nodiscard]] FTraceWriterEventDeclarationBuilder& DeclareEvent(FAnsiStringView LoggerName, FAnsiStringView Name, ETraceWriterEventFlags Flags = ETraceWriterEventFlags::None);` — Declares a new trace event. The End() call for the returned builder will change the current thread to be the "Events" thread. \details Declares: the new trace event Writes: $Trace.NewEvent @param LoggerName - The logger name @param Name - The event name @param Flags - The event flags (Important, NoSync, etc.) @returns an event declaration builder object (FTraceWriterEventDeclarationBuilder); The builder object is used to further declare the event fields. User needs to call the builder's End() to complete the event declaration and to get the event id for the newly declared event.
- L851 _public prototype_ `[[nodiscard]] uint32 DeclareDiagnosticsSession2Event();` — Declares the Diagnostics.Session2 event. \details Declares: Diagnostics.Session2 event Writes: $Trace.NewEvent
- L861 _public prototype_ `[[nodiscard]] FTraceWriterEventBuilder& WriteEvent(uint32 EventId);` — Writes the specified event, on the current thread. @param EventId - The event id, one returned by DeclareEvent().[...].End() @returns an event builder object (FTraceWriterEventBuilder); The builder object is used to further set values for each event field. User needs to call the builder's End() to complete the event.
- L869 _public prototype_ `void WriteEnterScopeEvent();` — Writes the EnterScope event, on the current thread.
- L873 _public prototype_ `void WriteLeaveScopeEvent();` — Writes the LeaveScope event, on the current thread.
- L880 _public prototype_ `void WriteStampedEnterScopeEvent(uint64 Timestamp);` — Writes the EnterScope_TB event, on the current thread, using the specified timestamp. @param Timestamp - The current session time (i.e. one returned by GetTime()).
- L887 _public prototype_ `void WriteStampedLeaveScopeEvent(uint64 Timestamp);` — Writes the LeaveScope_TB event, on the current thread, using the specified timestamp. @param Timestamp - The current session time (i.e. one returned by GetTime()).
- L892 _public function_ `[[nodiscard]] static ETraceWriterEventFlags ConvertEventFlags(UE::Trace::IAnalyzer::EEventFlags Flags)`
- L901 _public function_ `[[nodiscard]] static uint8 GetProtocolEventFlags(ETraceWriterEventFlags Flags)`
- L914 _public prototype_ `static uint16 GetByteSizeForFieldType(ETraceWriterFieldType Type);`
- L916 _public function_ `[[nodiscard]] static bool IsArrayFieldType(ETraceWriterFieldType Type)`
- L920 _public function_ `[[nodiscard]] static bool IsSignedFieldType(ETraceWriterFieldType Type)`
- L924 _public function_ `[[nodiscard]] static bool IsReferenceFieldType(ETraceWriterFieldType Type)`
- L928 _public function_ `[[nodiscard]] static bool IsDefinitionIdFieldType(ETraceWriterFieldType Type)`
- L933 _public prototype_ `[[nodiscard]] static uint8 GetProtocolFieldFamily(ETraceWriterFieldType Type);`
- L934 _public prototype_ `[[nodiscard]] static uint8 GetProtocolFieldType(ETraceWriterFieldType Type);`
- L936 _public prototype_ `[[nodiscard]] static ETraceWriterFieldType ConvertFieldType(const UE::Trace::IAnalyzer::FEventFieldInfo& FieldInfo);`
- L950 _public function_ `void SetCustomClock(uint64 InTimeFrequency, TFunction<uint64()> InTimeGetter, uint64 InStartTime, double InStartTimeSinceEpoch)` — Sets the custom clock for the session time. Warning: It is only valid to set these before writer's Begin(). @param InTimeFrequency - The time frequency; the number of [ticks] in a second. @param InTimeGetter - The custom getter for the session time; when called it is expected to return the current session time, in [ticks]. @param InStartTime - The start session timestamp, in [ticks]. @param InStartTimeSinceEpoch - The start session time since Unix Epoch (January 1st of 1970), in [seconds]. Should match InStartTime.
- L964 _public function_ `[[nodiscard]] uint64 GetTimeFrequency() const` — Returns the frequency of the session time, specified as number of [ticks] per second. @returns the frequency of the session time.
- L974 _public function_ `[[nodiscard]] uint64 GetStartTime() const` — Gets the start session time, in [ticks]. @returns the start session time.
- L984 _public function_ `[[nodiscard]] double GetStartTimeSinceEpoch() const` — Gets the start session time since the Unix Epoch (January 1st of 1970), in [seconds]. @returns the start session time since the Unix Epoch.
- L994 _public function_ `[[nodiscard]] uint64 GetTime() const` — Gets the current session time, in [ticks]. @returns the current session time.
- L1004 _public function_ `[[nodiscard]] double GetTimeSinceEpoch() const` — Gets the current session time since the Unix Epoch (January 1st of 1970), in [seconds]. @returns the current session time since the Unix Epoch.
- L1016 _public prototype_ `[[nodiscard]] const FString& GetLastError() const;` — Returns the last error message from the stack. Returns an empty string if there was no error. Continuing to call GetLastError() will extract the previous emitted error until the stack is empty.
- L1021 _public function_ `void ClearErrors()` — Clears the stack of error messages, if any.
- L1026 _public function_ `bool IsSafeModeEnabled() const` — Returns wherever safe mode is enabled or not.
- L1029 _private prototype_ `void Reset();`
- L1030 _private prototype_ `static void GenerateGuid(FTraceGuid* OutGuid);`
- L1031 _private prototype_ `uint32 GetOrDeclareUnknownEventId();`
- L1033 _private prototype_ `void WriteEventDeclaration(const FTraceWriterEventDeclarationBuilder& Builder);`
- L1034 _private prototype_ `void WriteEventDeclaration(const FTraceWriterEventInfo& EventInfo);`
- L1035 _private prototype_ `void WriteEvent(const FTraceWriterEventBuilder& Builder);`
- L1036 _private prototype_ `void WriteEvent(const FTraceWriterEventBuilder& Builder, const FTraceWriterEventInfo& EventInfo);`
- L1037 _private prototype_ `void WriteAuxData(uint32 Index, const void* Data, uint32 Size, bool bIsImportant);`
- L1038 _private prototype_ `void WriteAuxDataSegment(uint32 Index, const void* SegmentData, uint32 SegmentSize, bool bIsImportant);`
- L1040 _private prototype_ `void WriteScopeEventPrivate(uint8 Uid);`
- L1041 _private prototype_ `void WriteStampedScopeEventPrivate(uint8 Uid, uint64 Timestamp);`
- L1043 _private prototype_ `uint8* GetBuffer(uint32 RequiredDataSize);`
- L1044 _private prototype_ `void AdvanceBuffer(uint32 DataSize);`
- L1045 _private prototype_ `void BeginEvent();`
- L1046 _private prototype_ `void EndEvent();`
- L1047 _private prototype_ `void WritePacket();`
- L1049 _private prototype_ `void InitDefaultClock();`
- L1050 _private prototype_ `void SetError(FString&& InError);`
- L1053 _private member_ `IOutDataStream& Stream;`
- L1055 _private member_ `FTraceGuid TraceGuid;`
- L1056 _private member_ `FTraceGuid SessionGuid;`
- L1058 _private member_ `uint64 CycleFrequency = 0;` — [ticks] per second
- L1059 _private member_ `TFunction<uint64()> TimeGetter;` — returns session time, in [ticks]
- L1060 _private member_ `uint64 StartCycle = 0;` — [ticks]
- L1061 _private member_ `double StartTimeSinceEpoch = 0.0;` — [seconds] since epoch
- L1062 _private member_ `bool bUseCustomClock = false;`
- L1064 _private member_ `uint32 NextSerial = 0;`
- L1066 _private member_ `uint32 UnknownEventId = 0;`
- L1067 _private member_ `uint32 NewTraceEventId = 0;`
- L1068 _private member_ `uint32 ThreadTimingEventId = 0;`
- L1069 _private member_ `uint32 ThreadInfoEventId = 0;`
- L1070 _private member_ `uint32 ThreadGroupBeginEventId = 0;`
- L1071 _private member_ `uint32 ThreadGroupEndEventId = 0;`
- L1073 _private member_ `TArray<FTraceWriterThreadInfo> Threads;`
- L1075 _private member_ `TArray<FTraceWriterEventInfo*> EventInfos;`
- L1076 _private member_ `FTraceWriterEventDeclarationBuilder* PendingEventDeclaration = nullptr;`
- L1077 _private member_ `FTraceWriterEventBuilder* PendingEvent = nullptr;`
- L1079 _private member_ `uint32 CurrentThreadId = ETransportTid::Events;`
- L1080 _private member_ `uint8* EventBuffer = nullptr;`
- L1081 _private member_ `uint32 EventBufferSize = 0;`
- L1082 _private member_ `static constexpr uint32 MaxPacketHeaderSize = 8;` — >= sizeof(FTidPacketEncoded), >= sizeof(FTidPacket)
- L1083 _private member_ `static constexpr uint32 EncodingOverhead = 64;` — LZ4_COMPRESSBOUND
- L1084 _private member_ `static constexpr uint32 MaxPacketBufferSize = 64 << 10;`
- L1085 _private member_ `static constexpr uint32 MaxEncodedBufferSize = MaxPacketBufferSize - EncodingOverhead - MaxPacketHeaderSize;`
- L1086 _private member_ `static constexpr uint32 MaxDecodedBufferSize = MaxEncodedBufferSize;`
- L1087 _private member_ `static constexpr uint32 MinEncodedBufferSize = 384;`
- L1088 _private member_ `static constexpr uint32 FlushPacketThreshold = 32 << 10;`
- L1089 _private member_ `uint32 EventBufferDataSize = 0;`
- L1090 _private member_ `uint32 CompletedEventsDataSize = 0;`
- L1091 _private member_ `uint8* PacketBuffer = nullptr;`
- L1093 _private member_ `mutable TArray<FString> Errors;`
- L1094 _private member_ `mutable FString LastError;`

#### struct `UE::Trace::FTraceWriter::FTraceGuid`  
`struct FTraceGuid`  
_L626-629_
- L628 _public member_ `uint32 Bits[4];`

#### Free symbols / members of external scopes

- L21 _macro_ `#define UE_API TRACEANALYSIS_API`
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace Trace` (scope `UE`)
- L76 _prototype_ `ENUM_CLASS_FLAGS(ETraceWriterEventFlags);` (scope `UE::Trace`)
- L140 _prototype_ `ENUM_CLASS_FLAGS(ETraceWriterFieldType);` (scope `UE::Trace`)
- L149 _typedef_ `using EType = ETraceWriterFieldType;` (scope `UE::Trace::FTraceWriterFieldTypeResolver::GetType`)
- L373 _member_ `void* Buffer;` (scope `UE::Trace::FTraceWriterFieldData::__anon81cf2cfb010a`)
- L374 _member_ `uint64 Data = 0;` (scope `UE::Trace::FTraceWriterFieldData::__anon81cf2cfb010a`)
- L615 _prototype_ `ENUM_CLASS_FLAGS(ETraceWriterBeginOptions);` (scope `UE::Trace`)
- L1113 _macro_ `#define UE_ADHOC_TRACE_BEGIN_DECLARE_EVENT(Writer, LoggerName, EventName, Flags) \`
- L1116 _macro_ `#define UE_ADHOC_TRACE_DECLARE_FIELD(Type, FieldName) \`
- L1119 _macro_ `#define UE_ADHOC_TRACE_END_DECLARE_EVENT \`
- L1122 _macro_ `#define __UE_ADHOC_TRACE_NARG(...) __UE_ADHOC_TRACE_NARG_(__VA_ARGS__, __UE_ADHOC_TRACE_RSEQ_N())`
- L1123 _macro_ `#define __UE_ADHOC_TRACE_NARG_(...) __UE_ADHOC_TRACE_ARG_N(__VA_ARGS__)`
- L1124 _macro_ `#define __UE_ADHOC_TRACE_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, N, ...) N`
- L1125 _macro_ `#define __UE_ADHOC_TRACE_RSEQ_N() 8, 7, 6, 5, 4, 3, 2, 1, 0`
- L1127 _macro_ `#define __UE_ADHOC_TRACE_CONCATENATE(a, b) __UE_ADHOC_TRACE_CONCATENATE2(a, b)`
- L1128 _macro_ `#define __UE_ADHOC_TRACE_CONCATENATE2(a, b) a##b`
- L1130 _macro_ `#define __UE_ADHOC_TRACE_LOG_ARGS_1(Arg0) .Field(0, Arg0)`
- L1131 _macro_ `#define __UE_ADHOC_TRACE_LOG_ARGS_2(Arg0, Arg1) .Field(0, Arg0).Field(1, Arg1)`
- L1132 _macro_ `#define __UE_ADHOC_TRACE_LOG_ARGS_3(Arg0, Arg1, Arg2) .Field(0, Arg0).Field(1, Arg1).Field(2, Arg2)`
- L1133 _macro_ `#define __UE_ADHOC_TRACE_LOG_ARGS_4(Arg0, Arg1, Arg2, Arg3) .Field(0, Arg0).Field(1, Arg1).Field(2, Arg2).Field(3, Arg3)`
- L1134 _macro_ `#define __UE_ADHOC_TRACE_LOG_ARGS_5(Arg0, Arg1, Arg2, Arg3, Arg4) .Field(0, Arg0).Field(1, Arg1).Field(2, Arg2).Field(3, Arg3).Field(4, Arg4)`
- L1135 _macro_ `#define __UE_ADHOC_TRACE_LOG_ARGS_6(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5) .Field(0, Arg0).Field(1, Arg1).Field(2, Arg2).Field(3, Arg3).Field(4, Arg4).Field(5, Arg5)`
- L1136 _macro_ `#define __UE_ADHOC_TRACE_LOG_ARGS_7(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6) .Field(0, Arg0).Field(1, Arg1).Field(2, Arg2).Field(3, Arg3).Field(4, Arg4).Field(5, Arg5).Field(6, Arg6)`
- L1137 _macro_ `#define __UE_ADHOC_TRACE_LOG_ARGS_8(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7) .Field(0, Arg0).Field(1, Arg1).Field(2, Arg2).Field(3, Arg3).Field(4, Arg4).Field(5, Arg5).Field(6, Arg6).Field(7, Arg7)`
- L1139 _macro_ `#define UE_ADHOC_TRACE_LOG(Writer, Uid, ...) \`

### `Source/Developer/TraceAnalysis/Public/TraceAnalysisDebug.h` (Public)


#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_TRACE_ANALYSIS_DEBUG_API 0`
- L16 _macro_ `#define UE_TRACE_ANALYSIS_DEBUG 0`
- L30 _macro_ `#define UE_TRACE_ANALYSIS_DEBUG_LOG_IMPL 1`
- L35 _macro_ `#define UE_TRACE_ANALYSIS_DEBUG_LOG(format, ...) printf(format "\n", ##__VA_ARGS__)`
- L36 _macro_ `#define UE_TRACE_ANALYSIS_DEBUG_BeginStringBuilder()`
- L37 _macro_ `#define UE_TRACE_ANALYSIS_DEBUG_Append(s) printf("%s", s)`
- L38 _macro_ `#define UE_TRACE_ANALYSIS_DEBUG_Appendf(format, ...) printf(format, ##__VA_ARGS__)`
- L39 _macro_ `#define UE_TRACE_ANALYSIS_DEBUG_AppendChar(c) printf("%c", c)`
- L40 _macro_ `#define UE_TRACE_ANALYSIS_DEBUG_EndStringBuilder() printf("\n")`
- L41 _macro_ `#define UE_TRACE_ANALYSIS_DEBUG_ResetStringBuilder()`
- L46 _macro_ `#define UE_TRACE_ANALYSIS_DEBUG_BeginStringBuilder() TAnsiStringBuilder<1024> StringBuilder;`
- L47 _macro_ `#define UE_TRACE_ANALYSIS_DEBUG_Append StringBuilder.Append`
- L48 _macro_ `#define UE_TRACE_ANALYSIS_DEBUG_Appendf StringBuilder.Appendf`
- L49 _macro_ `#define UE_TRACE_ANALYSIS_DEBUG_AppendChar StringBuilder.AppendChar`
- L50 _macro_ `#define UE_TRACE_ANALYSIS_DEBUG_EndStringBuilder() printf("%s\n", StringBuilder.ToString())`
- L51 _macro_ `#define UE_TRACE_ANALYSIS_DEBUG_ResetStringBuilder() StringBuilder.Reset()`
- L60 _macro_ `#define UE_TRACE_ANALYSIS_DEBUG_LOG(format, ...) { TAnsiStringBuilder<1024> SB; SB.Appendf(format, ##__VA_ARGS__); GLog->Logf(TEXT("%hs"), SB.ToString()); }`
- L65 _macro_ `#define UE_TRACE_ANALYSIS_DEBUG_EndStringBuilder() GLog->Logf(TEXT("%hs"), StringBuilder.ToString())`
- L72 _macro_ `#define UE_TRACE_ANALYSIS_DEBUG_LOG(format, ...) { TAnsiStringBuilder<1024> SB; SB.Appendf(format, ##__VA_ARGS__); FPlatformMisc::LowLevelOutputDebugStringf(TEXT("%hs\n"), SB.ToString()); }`
- L74 _macro_ `#define UE_TRACE_ANALYSIS_DEBUG_Append(s) FPlatformMisc::LowLevelOutputDebugStringf(TEXT("%hs"), s)`
- L75 _macro_ `#define UE_TRACE_ANALYSIS_DEBUG_Appendf(format, ...) { TAnsiStringBuilder<1024> SB; SB.Appendf(format, ##__VA_ARGS__); FPlatformMisc::LowLevelOutputDebugStringf(TEXT("%hs"), SB.ToString()); }`
- L76 _macro_ `#define UE_TRACE_ANALYSIS_DEBUG_AppendChar(c) FPlatformMisc::LowLevelOutputDebugStringf(TEXT("%hc"), c)`
- L77 _macro_ `#define UE_TRACE_ANALYSIS_DEBUG_EndStringBuilder() FPlatformMisc::LowLevelOutputDebugString(TEXT("\n"))`
- L84 _macro_ `#define UE_TRACE_ANALYSIS_DEBUG_LOG(format, ...)`
- L86 _macro_ `#define UE_TRACE_ANALYSIS_DEBUG_Append(s)`
- L87 _macro_ `#define UE_TRACE_ANALYSIS_DEBUG_Appendf(format, ...)`
- L88 _macro_ `#define UE_TRACE_ANALYSIS_DEBUG_AppendChar(c)`
- L89 _macro_ `#define UE_TRACE_ANALYSIS_DEBUG_EndStringBuilder()`
- L97 _namespace_ `namespace UE`
- L97 _namespace_ `namespace Trace` (scope `UE`)
- L97 _namespace_ `namespace Analysis` (scope `UE::Trace`)
- L101 _externvar_ `extern uint32 GDebugLevel;` (scope `UE::Trace::Analysis`) — Log level (1 = minimum, 2 = normal, 3 = verbose, 4 = verbose+). It is used only when UE_TRACE_ANALYSIS_DEBUG is enabled.
- L104 _macro_ `#define UE_TRACE_ANALYSIS_DEBUG_LOG_EX(level, format, ...) \`
- L114 _macro_ `#define UE_TRACE_ANALYSIS_DEBUG_LOG_EX(level, format, ...)`
