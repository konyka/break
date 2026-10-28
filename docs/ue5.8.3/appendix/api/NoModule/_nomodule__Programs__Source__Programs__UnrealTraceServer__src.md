# NoModule / _nomodule__Programs__Source__Programs__UnrealTraceServer__src

- module root: `.`
- headers: 23; symbols: 472
- symbol kinds: class=28, enum=5, enumerator=19, function=60, macro=40, member=85, namespace=3, prototype=207, struct=10, typedef=14, union=1

### `Source/Programs/UnrealTraceServer/src/Asio.h` (Other)


#### Free symbols / members of external scopes

- L7 _macro_ `# define TS_ASIO_INCLUDE_BEGIN \`
- L10 _macro_ `# define TS_ASIO_INCLUDE_END \`
- L13 _macro_ `# define TS_ASIO_INCLUDE_BEGIN`
- L14 _macro_ `# define TS_ASIO_INCLUDE_END`
- L21 _macro_ `#define ASIO_SEPARATE_COMPILATION`
- L22 _macro_ `#define ASIO_STANDALONE`
- L23 _macro_ `#define ASIO_NO_EXCEPTIONS`
- L24 _macro_ `#define ASIO_NO_TYPEID`
- L25 _macro_ `#define ASIO_DISABLE_NOEXCEPT`
- L27 _namespace_ `namespace asio`
- L28 _namespace_ `namespace detail` (scope `asio`)
- L31 _function_ `template <typename ExceptionType> void throw_exception(const ExceptionType& Exception)` (scope `asio::detail`)

### `Source/Programs/UnrealTraceServer/src/AsioContext.h` (Other)


#### class `FAsioContext`  
`class FAsioContext`  
_L11-25_
- L14 _public prototype_ `FAsioContext(int32 ThreadCount);`
- L15 _public prototype_ `~FAsioContext();`
- L16 _public prototype_ `asio::io_context& Get();`
- L17 _public prototype_ `void Start();`
- L18 _public prototype_ `void Stop(bool bWait=false);`
- L19 _public prototype_ `void Wait();`
- L22 _private member_ `asio::io_context* IoContext;`
- L23 _private member_ `TArray<std::thread> ThreadPool;`
- L24 _private member_ `bool bRunning = false;`

### `Source/Programs/UnrealTraceServer/src/AsioFile.h` (Other)


#### class `FAsioFile`  
`class FAsioFile : public FAsioReadable , public FAsioWriteable`  
_L14-40_
- inherits: `FAsioReadable,FAsioWriteable`
- L19 _public prototype_ `FAsioFile(asio::io_context& IoContext, uintptr_t OsHandle);`
- L20 _public prototype_ `asio::io_context& GetIoContext();`
- L21 _public prototype_ `static FAsioWriteable* WriteFile(asio::io_context& IoContext, const FPath& Path);`
- L22 _public prototype_ `static FAsioReadable* ReadFile(asio::io_context& IoContext, const FPath& Path);`
- L23 _public prototype_ `virtual bool IsOpen() const override;`
- L24 _public prototype_ `virtual void Close() override;`
- L25 _public prototype_ `virtual bool HasDataAvailable() const override;`
- L26 _public prototype_ `virtual bool Write(const void* Src, uint32 Size, FAsioIoSink* Sink, uint32 Id) override;`
- L27 _public prototype_ `virtual bool Read(void* Dest, uint32 Size, FAsioIoSink* Sink, uint32 Id) override;`
- L28 _public prototype_ `virtual bool ReadSome(void* Dest, uint32 BufferSize, FAsioIoSink* Sink, uint32 Id) override;`
- L31 _private typedef_ `using HandleType = #if TS_USING(TS_PLATFORM_WINDOWS) asio::windows::random_access_handle;`
- L38 _private member_ `HandleType Handle;`
- L39 _private member_ `uint64 Offset = 0;`

### `Source/Programs/UnrealTraceServer/src/AsioIoable.h` (Other)


#### class `FAsioIoSink`  
`class FAsioIoSink`  
_L8-12_
- L11 _public prototype_ `virtual void OnIoComplete(uint32 Id, int32 Size) = 0;`

#### class `FAsioIoable`  
`class FAsioIoable`  
_L15-29_
- L18 _public prototype_ `virtual ~FAsioIoable() = default;`
- L19 _public prototype_ `virtual bool IsOpen() const = 0;`
- L20 _public prototype_ `virtual void Close() = 0;`
- L23 _protected prototype_ `bool SetSink(FAsioIoSink* Ptr, uint32 Id);`
- L24 _protected prototype_ `void OnIoComplete(const asio::error_code& ErrorCode, int32 Size);`
- L27 _private member_ `FAsioIoSink* SinkPtr = nullptr;`
- L28 _private member_ `uint32 SinkId;`

#### class `FAsioReadable`  
`class FAsioReadable : public virtual FAsioIoable`  
_L32-39_
- inherits: `FAsioIoable`
- L36 _public prototype_ `virtual bool HasDataAvailable() const = 0;`
- L37 _public prototype_ `virtual bool Read(void* Dest, uint32 Size, FAsioIoSink* Sink, uint32 Id) = 0;`
- L38 _public prototype_ `virtual bool ReadSome(void* Dest, uint32 DestSize, FAsioIoSink* Sink, uint32 Id) = 0;`

#### class `FAsioWriteable`  
`class FAsioWriteable : public virtual FAsioIoable`  
_L44-49_
- inherits: `FAsioIoable`
- L48 _public prototype_ `virtual bool Write(const void* Src, uint32 Size, FAsioIoSink* Sink, uint32 Id) = 0;`

### `Source/Programs/UnrealTraceServer/src/AsioSocket.h` (Other)


#### class `FAsioSocket`  
`class FAsioSocket : public FAsioReadable , public FAsioWriteable`  
_L9-39_
- inherits: `FAsioReadable,FAsioWriteable`
- L23 _public prototype_ `FAsioSocket(asio::ip::tcp::socket& InSocket, const FKeepAliveConfig& KeepAlive = DefaultKeepAlive);`
- L24 _public prototype_ `virtual ~FAsioSocket();`
- L25 _public prototype_ `asio::io_context& GetIoContext();`
- L26 _public prototype_ `virtual bool IsOpen() const override;`
- L27 _public prototype_ `virtual void Close() override;`
- L28 _public prototype_ `virtual bool HasDataAvailable() const override;`
- L29 _public prototype_ `bool IsLocalConnection() const;`
- L30 _public prototype_ `uint32 GetRemoteAddress() const;`
- L31 _public prototype_ `uint32 GetRemotePort() const;`
- L32 _public prototype_ `uint32 GetLocalPort() const;`
- L33 _public prototype_ `virtual bool Read(void* Dest, uint32 Size, FAsioIoSink* Sink, uint32 Id) override;`
- L34 _public prototype_ `virtual bool ReadSome(void* Dest, uint32 DestSize, FAsioIoSink* Sink, uint32 Id) override;`
- L35 _public prototype_ `virtual bool Write(const void* Src, uint32 Size, FAsioIoSink* Sink, uint32 Id) override;`
- L38 _private member_ `asio::ip::tcp::socket Socket;`

#### struct `FAsioSocket::FKeepAliveConfig`  
`struct FKeepAliveConfig`  
_L15-20_
- L17 _public member_ `bool Enabled = false;`
- L18 _public member_ `uint32 TimeoutSec = 0;`
- L19 _public member_ `uint32 IntervalSec = 0;`

### `Source/Programs/UnrealTraceServer/src/AsioTcpServer.h` (Other)


#### class `FAsioTcpServer`  
`class FAsioTcpServer`  
_L8-24_
- L11 _public prototype_ `FAsioTcpServer(asio::io_context& IoContext);`
- L12 _public prototype_ `virtual ~FAsioTcpServer();`
- L13 _public prototype_ `asio::io_context& GetIoContext();`
- L14 _public prototype_ `bool IsOpen() const;`
- L15 _public prototype_ `void Close();`
- L16 _public prototype_ `virtual bool OnAccept(asio::ip::tcp::socket& Socket) = 0;`
- L17 _public prototype_ `uint32 GetPort() const;`
- L18 _public prototype_ `bool StartServer(uint32 Port=0, uint32 Backlog=1);`
- L19 _public prototype_ `bool StopServer();`
- L22 _private prototype_ `void AsyncAccept();`
- L23 _private member_ `asio::ip::tcp::acceptor Acceptor;`

### `Source/Programs/UnrealTraceServer/src/AsioTickable.h` (Other)


#### class `FAsioTickable`  
`class FAsioTickable`  
_L8-24_
- L11 _public prototype_ `FAsioTickable(asio::io_context& IoContext);`
- L12 _public prototype_ `virtual ~FAsioTickable();`
- L13 _public prototype_ `asio::io_context& GetIoContext();`
- L14 _public prototype_ `bool IsActive() const;`
- L15 _public prototype_ `bool StartTick(uint32 MillisecondRate);`
- L16 _public prototype_ `bool StopTick();`
- L17 _public prototype_ `bool TickOnce(uint32 MillisecondRate);`
- L18 _public prototype_ `virtual void OnTick() = 0;`
- L21 _private prototype_ `void AsyncTick();`
- L22 _private member_ `asio::steady_timer Timer;`
- L23 _private member_ `uint32 MillisecondRate = 0;`

### `Source/Programs/UnrealTraceServer/src/Cbor.h` (Other)


#### enum `ECborType`  
`enum class ECborType`  
_L15-29_
- L17 _public enumerator_ `Error = -1`
- L18 _public enumerator_ `Eof`
- L19 _public enumerator_ `Integer`
- L22 _public enumerator_ `String` — Boolean, Float,
- L23 _public enumerator_ `Array`
- L24 _public enumerator_ `Map`
- L25 _public enumerator_ `End` — ..of array/map
- L28 _public enumerator_ `_Count` — Null, Undefined,

#### class `FCborContext`  
`class FCborContext`  
_L32-48_
- L37 _public prototype_ `void Reset();`
- L38 _public prototype_ `ECborType GetType() const;`
- L39 _public prototype_ `int64 GetLength() const;`
- L40 _public prototype_ `FStringView AsString() const;`
- L41 _public prototype_ `int64 AsInteger() const;`
- L44 _private prototype_ `void SetError();`
- L45 _private member_ `const uint8* NextCursor = nullptr;`
- L46 _private member_ `int64 Param;`
- L47 _private member_ `ECborType Type;`

#### class `FCborWriter`  
`class FCborWriter`  
_L51-64_
- L54 _public prototype_ `FCborWriter(FInlineBuffer& InBuffer);`
- L55 _public prototype_ `void OpenMap(int32 ItemCount=-1);`
- L56 _public prototype_ `void OpenArray(int32 ItemCount=-1);`
- L57 _public prototype_ `void Close();`
- L58 _public prototype_ `void WriteString(const char* Value, int32 Length=-1);`
- L59 _public prototype_ `void WriteInteger(int64 Value);`
- L62 _private prototype_ `void WriteParam(uint32 MajorType, uint64 Value);`
- L63 _private member_ `FInlineBuffer& Buffer;`

#### class `FCborReader`  
`class FCborReader`  
_L67-80_
- L70 _public prototype_ `FCborReader(const uint8* Data, uint32 DataSize);`
- L71 _public prototype_ `bool ReadNext(FCborContext& Context);`
- L74 _private prototype_ `int64 ReadParam(const uint8*& Cursor);`
- L75 _private prototype_ `bool ReadContainer(FCborContext& Context, const uint8* Cursor);`
- L76 _private prototype_ `bool ReadInteger(FCborContext& Context, const uint8* Cursor);`
- L77 _private prototype_ `bool ReadString(FCborContext& Context, const uint8* Cursor);`
- L78 _private member_ `const uint8* Base;`
- L79 _private member_ `const uint8* DataEnd;`

### `Source/Programs/UnrealTraceServer/src/CborPayload.h` (Other)


#### struct `FPayload`  
`struct FPayload`  
_L10-14_
- L12 _public member_ `const uint8* Data;`
- L13 _public member_ `uint32 Size;`

#### enum `EStatusCode`  
`enum class EStatusCode`  
_L19-27_
- L21 _public enumerator_ `Unknown = 0`
- L22 _public enumerator_ `Success = 200`
- L23 _public enumerator_ `BadRequest = 400`
- L24 _public enumerator_ `Forbidden = 403`
- L25 _public enumerator_ `NotFound = 404`
- L26 _public enumerator_ `InternalError = 500`

#### class `TPayloadBuilder`  
`template <int Size=128> class TPayloadBuilder`  
_L33-46_
- L36 _public prototype_ `TPayloadBuilder(EStatusCode StatusCode);`
- L37 _public prototype_ `template <int N> TPayloadBuilder(const char (&Path)[N]);`
- L38 _public prototype_ `template <int N> TPayloadBuilder(const char (&Path)[N]);`
- L39 _public prototype_ `template <int N> TPayloadBuilder(const char (&Path)[N]);`
- L40 _public prototype_ `template <int N> TPayloadBuilder(const char (&Path)[N]);`
- L41 _public prototype_ `template <int N> void AddInteger(const char (&Name)[N], int64 Value);`
- L44 _private member_ `TInlineBuffer<Size> Buffer;`
- L45 _private member_ `FCborWriter CborWriter = { Buffer };`
- L50 _function_ `template <int Size> inline TPayloadBuilder<Size>::TPayloadBuilder(EStatusCode StatusCode)`
- L59 _function_ `template <int Size> template <int N> inline TPayloadBuilder<Size>::TPayloadBuilder(const char (&Path)[N])`
- L69 _function_ `template <int Size> template <int N> inline void TPayloadBuilder<Size>::AddInteger(const char (&Name)[N], int64 Value)`
- L78 _function_ `template<int Size> template<int N> inline void TPayloadBuilder<Size>::AddStringArray(const char(&Name)[N], const TArray<FString> Values)`
- L92 _function_ `template <int Size> template <int N> inline void TPayloadBuilder<Size>::AddString( const char (&Name)[N], const char* Value, int Length)`
- L103 _function_ `template <int Size> inline FPayload TPayloadBuilder<Size>::Done()`

#### class `FResponse`  
`class FResponse`  
_L112-127_
- L115 _public prototype_ `EStatusCode GetStatusCode() const;`
- L116 _public prototype_ `int64 GetInteger(const char* Key, int64 Default) const;`
- L118 _public prototype_ `template <int N> FStringView GetString(const char* Key, const char (&Default)[N]) const;`
- L119 _public prototype_ `const uint8* GetData() const;`
- L120 _public prototype_ `uint32 GetSize() const;`
- L121 _public prototype_ `uint8* Reserve(uint32 Size);`
- L125 _private prototype_ `template <typename Type, typename LambdaType> Type GetValue(const char* Key, Type Default, LambdaType&& Lambda) const;`
- L126 _private member_ `TArray<uint8> Buffer;`
- L130 _function_ `inline EStatusCode FResponse::GetStatusCode() const`
- L137 _function_ `inline const uint8* FResponse::GetData() const`
- L143 _function_ `inline uint32 FResponse::GetSize() const`
- L149 _function_ `inline uint8* FResponse::Reserve(uint32 Size)`
- L157 _function_ `template <typename Type, typename LambdaType> inline Type FResponse::GetValue(const char* Key, Type Default, LambdaType&& Lambda) const`
- L193 _function_ `inline int64 FResponse::GetInteger(const char* Key, int64 Default) const`
- L207 _function_ `template <int N> inline FStringView FResponse::GetString(const char* Key, const char (&Default)[N]) const`

#### Free symbols / members of external scopes

- L199 _function_ `` (scope `FResponse::GetInteger`)
- L214 _function_ `` (scope `FResponse::GetString`)

### `Source/Programs/UnrealTraceServer/src/CrashHandler.h` (Other)


#### Free symbols / members of external scopes

- L9 _prototype_ `void InstallCrashHandler(const FPath& LogDir);` — Call once at startup after the log directory is known. Installs platform crash handlers and pre-computes the crash report path.

### `Source/Programs/UnrealTraceServer/src/Foundation.h` (Other)


#### struct `TArray`  
`template <typename Type> struct TArray : protected std::vector<Type>`  
_L11-33_
- inherits: `std::vector<Type>`
- L14 _public typedef_ `using Super = std::vector<Type>;`
- L20 _public function_ `void Add(const Type& Value)`
- L21 _public function_ `void SetNum(int32 Num)`
- L22 _public function_ `int32 Num() const`
- L23 _public function_ `Type* GetData()`
- L24 _public function_ `const Type* GetData() const`
- L25 _public function_ `void Empty()`
- L26 _public function_ `void SetNumUninitialized(int Num)`
- L27 _public function_ `void Append(const void* Data, int Num)`
- L28 _public function_ `Type& Last()`
- L30 _public prototype_ `template<typename Lambda> uint32 RemoveIf(Lambda&& Pred);`
- L32 _public prototype_ `template<typename Lambda> bool FindOrAdd(const Type& Item, Lambda&& Pred);`
- L37 _function_ `template<typename Type> template<typename Lambda> inline uint32 TArray<Type>::RemoveIf(Lambda&& Pred)`
- L57 _function_ `template<typename Type> template<typename Lambda> inline bool TArray<Type>::FindOrAdd(const Type& Item, Lambda&& Compare)`

#### struct `FStringView`  
`struct FStringView : protected std::basic_string_view<char>`  
_L71-83_
- inherits: `std::basic_string_view<char>`
- L74 _public typedef_ `typedef std::basic_string_view<char> Super;`
- L78 _public function_ `const char* GetData() const`
- L79 _public function_ `uint32 Len() const`
- L81 _public function_ `int Compare(const char* Rhs) const`
- L82 _public function_ `void RemovePrefix(uint32 n)`

#### struct `FString`  
`struct FString : public std::string`  
_L86-98_
- inherits: `std::string`
- L89 _public typedef_ `typedef std::string Super;`
- L93 _public function_ `FString(const std::string& Rhs) : Super(Rhs)`
- L94 _public function_ `FString(std::string&& Rhs) : Super(Rhs)`
- L95 _public function_ `FString(FStringView Rhs) : Super(Rhs.GetData(), Rhs.Len())`
- L96 _public function_ `const char* operator * () const`
- L97 _public function_ `void operator += (const FStringView& Rhs)`

#### struct `FWinApiStr`  
`struct FWinApiStr`  
_L138-159_
- L140 _public function_ `FWinApiStr(const char* Utf8)`
- L147 _public function_ `~FWinApiStr()`
- L152 _public function_ `operator LPCWSTR () const`
- L158 _private member_ `wchar_t* Buffer = nullptr;`

#### struct `FGuid`  
`struct FGuid`  
_L164-201_
- L166 _public member_ `uint32 Bits[4] = { 0, 0, 0, 0 };`
- L168 _public function_ `static bool ParseGuid(FStringView Source, FGuid& OutGuid)`
- L196 _public function_ `static bool Equal(const FGuid& Rhs, const FGuid Lhs)`

#### Free symbols / members of external scopes

- L6 _macro_ `#define MoveTemp(x) std::move(x)`
- L7 _macro_ `#define check(x)`
- L101 _typedef_ `typedef std::filesystem::path FPath;`
- L105 _namespace_ `namespace fs`
- L109 _function_ `inline FString ToFString(const path& Path)` (scope `fs`)

### `Source/Programs/UnrealTraceServer/src/InstanceInfo.h` (Other)


#### struct `FInstanceInfo`  
`struct FInstanceInfo`  
_L8-29_
- L11 _public member_ `static constexpr uint32 NumSponsorQueueSlots = 128;`
- L12 _public member_ `static const uint32 CurrentVersion = #if TS_USING(TS_BUILD_DEBUG) 0x8000'0000 | #endif ((TS_VERSION_PROTOCOL & 0xffff) << 16) | (TS_VERSION_MINOR & 0xffff);`
- L18 _public prototype_ `void Set();`
- L19 _public prototype_ `void WaitForReady() const;`
- L20 _public prototype_ `bool IsOlder() const;`
- L21 _public prototype_ `bool AddSponsor(uint32 Pid);`
- L23 _public member_ `std::atomic<uint32> Published;`
- L24 _public member_ `uint32 Version;`
- L25 _public member_ `uint32 Pid;`
- L28 _public member_ `std::atomic<uint32> SponsorPids[NumSponsorQueueSlots];` — Queue slots used to add sponsor processes. The running instance regularly polls these slots and moves the pid to an internal representation.

### `Source/Programs/UnrealTraceServer/src/Lifetime.h` (Other)


#### class `FLifetime`  
`class FLifetime : public FAsioTickable`  
_L10-33_
- inherits: `FAsioTickable`
- L13 _public prototype_ `FLifetime( asio::io_context& IoContext, class FStoreService* Service, class FStoreSettings* Settings, struct FInstanceInfo* InstanceInfo );`
- L21 _private prototype_ `void CheckNewSponsors(struct FInstanceInfo* InstanceInfo);`
- L22 _private prototype_ `void AddPid(uint32);`
- L23 _private prototype_ `bool ShutdownStoreIfNoConnections();`
- L24 _private prototype_ `bool IsAnySponsorActive();`
- L25 _private prototype_ `virtual void OnTick() override;`
- L27 _private typedef_ `using FProcHandle = void*;`
- L29 _private member_ `TArray<FProcHandle> SponsorHandles;`
- L30 _private member_ `class FStoreService* StoreService;`
- L31 _private member_ `class FStoreSettings* Settings;`
- L32 _private member_ `struct FInstanceInfo* InstanceInfo;`

### `Source/Programs/UnrealTraceServer/src/Logging.h` (Other)


#### class `FLogging`  
`class FLogging`  
_L12-27_
- L15 _public prototype_ `static void Log(const char* Format, ...);`
- L19 _private prototype_ `FLogging(FPath& Path);`
- L20 _private prototype_ `~FLogging();`
- L21 _private prototype_ `FLogging(const FLogging&) = delete;`
- L22 _private prototype_ `FLogging(FLogging&&) = default;`
- L23 _private prototype_ `void LogImpl(const char* String) const;`
- L24 _private member_ `static FLogging* Instance;`
- L25 _private member_ `FPath Path;`
- L26 _private member_ `FILE* File = nullptr;`

#### struct `FLoggingScope`  
`struct FLoggingScope`  
_L30-37_
- L32 _public prototype_ `FLoggingScope(FPath& Path, const char* LogFileName = nullptr);`
- L33 _public prototype_ `~FLoggingScope();`
- L36 _private member_ `FLogging* PreviousScope = nullptr;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define TS_LOG(Format, ...) \`

### `Source/Programs/UnrealTraceServer/src/Pch.h` (Other)


#### Free symbols / members of external scopes

- L14 _macro_ `#define TS_ON +`
- L15 _macro_ `#define TS_OFF -`
- L16 _macro_ `#define TS_USING(x) ((1 x 1) == 2)`
- L18 _macro_ `#define TS_PLATFORM_WINDOWS TS_OFF`
- L19 _macro_ `#define TS_PLATFORM_LINUX TS_OFF`
- L20 _macro_ `#define TS_PLATFORM_MAC TS_OFF`
- L22 _macro_ `#define TS_ARCH_X64 TS_ON`
- L23 _macro_ `#define TS_ARCH_ARM64 TS_OFF`
- L27 _macro_ `# define TS_PLATFORM_WINDOWS TS_ON`
- L32 _macro_ `# define TS_PLATFORM_LINUX TS_ON`
- L37 _macro_ `# define TS_PLATFORM_MAC TS_ON`
- L41 _macro_ `# define TS_ARCH_X64 TS_OFF`
- L42 _macro_ `# define TS_ARCH_ARM64 TS_ON`
- L46 _macro_ `#define TS_ARRAY_COUNT(x) (sizeof(x) / sizeof((x)[0]))`
- L49 _macro_ `# define TS_BUILD_DEBUG TS_OFF`
- L57 _macro_ `# define _HAS_EXCEPTIONS 0`
- L58 _macro_ `# define _CRT_SECURE_NO_WARNINGS 0`
- L75 _macro_ `# define _WIN32_WINNT 0x0a00`
- L76 _macro_ `# define WIN32_LEAN_AND_MEAN`
- L77 _macro_ `# define NOMINMAX`
- L89 _typedef_ `using int8 = int8_t;`
- L90 _typedef_ `using int16 = int16_t;`
- L91 _typedef_ `using int32 = int32_t;`
- L92 _typedef_ `using int64 = int64_t;`
- L93 _typedef_ `using uint8 = uint8_t;`
- L94 _typedef_ `using uint16 = uint16_t;`
- L95 _typedef_ `using uint32 = uint32_t;`
- L96 _typedef_ `using uint64 = uint64_t;`
- L102 _macro_ `#define TS_CONCAT_(a, b) a##b`
- L103 _macro_ `#define TS_CONCAT(a, b) TS_CONCAT_(a, b)`

### `Source/Programs/UnrealTraceServer/src/Recorder.h` (Other)


#### class `FRecorder`  
`class FRecorder : public FAsioTcpServer , public FAsioTickable`  
_L14-46_
- inherits: `FAsioTcpServer,FAsioTickable`
- L35 _public prototype_ `FRecorder(asio::io_context& IoContext, FStore& InStore);`
- L36 _public prototype_ `~FRecorder();`
- L37 _public prototype_ `void Close();`
- L38 _public prototype_ `uint32 GetSessionCount() const;`
- L39 _public prototype_ `const FSession* GetSessionInfo(uint32 Index) const;`
- L42 _private prototype_ `virtual bool OnAccept(asio::ip::tcp::socket& Socket) override;`
- L43 _private prototype_ `virtual void OnTick() override;`
- L44 _private member_ `TArray<FSession> Sessions;`
- L45 _private member_ `FStore& Store;`

#### class `FRecorder::FSession`  
`class FSession`  
_L19-33_
- L22 _public prototype_ `uint32 GetId() const;`
- L23 _public prototype_ `uint32 GetTraceId() const;`
- L24 _public prototype_ `uint32 GetIpAddress() const;`
- L25 _public prototype_ `uint32 GetControlPort() const;`
- L26 _public prototype_ `const FGuid& GetSessionGuid() const;`
- L27 _public prototype_ `const FGuid& GetTraceGuid() const;`
- L31 _private member_ `FRecorderRelay* Relay;`
- L32 _private member_ `uint32 Id;`

### `Source/Programs/UnrealTraceServer/src/Store.h` (Other)


#### enum `EStoreVersion`  
`enum class EStoreVersion`  
_L16-19_
- L18 _public enumerator_ `Value = 0x0100` — 0xMMmm MM=major, mm=minor

#### class `FStore`  
`class FStore`  
_L22-107_
- L84 _public prototype_ `void SetupMounts();`
- L85 _public prototype_ `FStore(asio::io_context& IoContext, const FStoreSettings* InSettings);`
- L86 _public prototype_ `~FStore();`
- L87 _public prototype_ `void Close();`
- L88 _public prototype_ `FString GetStoreDir() const;`
- L89 _public prototype_ `uint32 GetChangeSerial() const;`
- L90 _public prototype_ `uint32 GetTraceCount() const;`
- L91 _public prototype_ `const FTrace* GetTraceInfo(uint32 Index) const;`
- L92 _public prototype_ `bool HasTrace(uint32 Id) const;`
- L93 _public prototype_ `FNewTrace CreateTrace();`
- L94 _public prototype_ `FAsioReadable* OpenTrace(uint32 Id);`
- L95 _public prototype_ `void OnSettingsChanged();`
- L98 _private prototype_ `bool AddMount(const FPath& Dir, bool bCreate);`
- L99 _private prototype_ `bool RemoveMount(uint32 Id);`
- L100 _private prototype_ `FTrace* GetTrace(uint32 Id, FMount** OutMount=nullptr) const;`
- L101 _private prototype_ `void Refresh();`
- L103 _private member_ `asio::io_context& IoContext;`
- L104 _private member_ `TArray<FMount*> Mounts;`
- L105 _private member_ `uint32 ChangeSerial;`
- L106 _private member_ `const FStoreSettings* Settings;`

#### class `FStore::FTrace`  
`class FTrace`  
_L25-43_
- L28 _public prototype_ `FTrace(const FPath& InPath);`
- L29 _public prototype_ `const FPath& GetPath() const;`
- L30 _public prototype_ `FString GetName() const;`
- L31 _public prototype_ `uint32 GetId() const;`
- L32 _public prototype_ `uint64 GetSize() const;`
- L33 _public prototype_ `uint64 GetTimestamp() const;`
- L34 _public prototype_ `bool HasMetadata() const;`
- L35 _public prototype_ `FString GetMetadataUri() const;`
- L39 _private member_ `FPath Path;`
- L40 _private member_ `uint64 Timestamp;`
- L41 _private member_ `uint32 Id = 0;`
- L42 _private member_ `FPath MetadataPath;` — Path to .utrace.ini sidecar (empty if not found)

#### struct `FStore::FNewTrace`  
`struct FNewTrace`  
_L45-49_
- L47 _public member_ `uint32 Id;`
- L48 _public member_ `FAsioWriteable* Writeable;`

#### class `FStore::FMount`  
`class FMount`  
_L51-82_
- L54 _public prototype_ `static FMount* Create(FStore* InParent, asio::io_context& InIoContext, const FPath& InDir, bool bCreate);`
- L56 _public prototype_ `void Close();`
- L57 _public prototype_ `uint32 GetId() const;`
- L58 _public prototype_ `FString GetDir() const;`
- L59 _public prototype_ `const FPath& GetPath() const;`
- L60 _public prototype_ `uint32 GetTraceCount() const;`
- L61 _public prototype_ `const FTrace* GetTraceInfo(uint32 Index) const;`
- L66 _private prototype_ `FMount(FStore* InParent, asio::io_context& InIoContext, const FPath& InDir);`
- L67 _private prototype_ `~FMount();`
- L68 _private prototype_ `FTrace* GetTrace(uint32 Id) const;`
- L69 _private prototype_ `FTrace* AddTrace(const FPath& Path);`
- L70 _private prototype_ `void ClearTraces();`
- L71 _private prototype_ `uint32 Refresh();`
- L72 _private prototype_ `void WatchDir();`
- L74 _private member_ `FPath Dir;`
- L75 _private member_ `TArray<FTrace*> Traces;`
- L76 _private member_ `uint32 Id;`
- L77 _private member_ `FDirWatcher* DirWatcher = nullptr;`
- L78 _private member_ `FStore* Parent = nullptr;`
- L80 _private member_ `asio::io_context& IoContext;`

### `Source/Programs/UnrealTraceServer/src/StoreCborServer.h` (Other)


#### class `FStoreCborServer`  
`class FStoreCborServer : public FAsioTcpServer , public FAsioTickable`  
_L17-43_
- inherits: `FAsioTcpServer,FAsioTickable`
- L24 _public prototype_ `FStoreCborServer(asio::io_context& IoContext, FStoreSettings* InSettings, FStore& InStore, FRecorder& InRecorder);`
- L25 _public prototype_ `~FStoreCborServer();`
- L26 _public prototype_ `void Close();`
- L27 _public prototype_ `FStore& GetStore() const;`
- L28 _public prototype_ `FRecorder& GetRecorder() const;`
- L29 _public prototype_ `FTraceRelay* RelayTrace(uint32 Id);`
- L30 _public prototype_ `void OnSettingsChanged();`
- L31 _public function_ `uint32 GetActivePeerCount() const`
- L34 _private prototype_ `virtual bool OnAccept(asio::ip::tcp::socket& Socket) override;`
- L35 _private prototype_ `virtual void OnTick() override;`
- L36 _private function_ `FStoreSettings* GetSettings() const`
- L38 _private member_ `TArray<FStoreCborPeer*> Peers;`
- L39 _private member_ `TArray<FTraceRelay*> Relays;`
- L40 _private member_ `FStore& Store;`
- L41 _private member_ `FRecorder& Recorder;`
- L42 _private member_ `FStoreSettings* Settings;`

### `Source/Programs/UnrealTraceServer/src/StoreService.h` (Other)


#### class `FStoreService`  
`class FStoreService`  
_L10-26_
- L13 _public prototype_ `~FStoreService() = default;`
- L14 _public prototype_ `static FStoreService* Create(FStoreSettings* Desc, struct FInstanceInfo* InstanceInfo);`
- L15 _public prototype_ `void operator delete (void* Addr);`
- L16 _public prototype_ `uint32 GetPort() const;`
- L17 _public prototype_ `uint32 GetRecorderPort() const;`
- L18 _public prototype_ `bool ShutdownIfNoConnections();`
- L21 _private prototype_ `FStoreService() = default;`
- L22 _private prototype_ `FStoreService(const FStoreService&) = delete;`
- L23 _private prototype_ `FStoreService(const FStoreService&&) = delete;`
- L24 _private prototype_ `void operator = (const FStoreService&) = delete;`
- L25 _private prototype_ `void operator = (const FStoreService&&) = delete;`

### `Source/Programs/UnrealTraceServer/src/StoreSettings.h` (Other)


#### class `FStoreSettings`  
`class FStoreSettings`  
_L8-29_
- L11 _public member_ `FPath SettingsFile;` — Path to settings file
- L12 _public member_ `FPath StoreDir;` — Path to active store
- L13 _public member_ `TArray<FPath> AdditionalWatchDirs;` — Additional directories to watch
- L14 _public member_ `int32 StorePort = 1989;` — Changes doesn't take effect until restart
- L15 _public member_ `int32 RecorderPort = 1981;` — Changes doesn't take effect until restart
- L16 _public member_ `int32 ThreadCount = 0;` — <=0:logical CPU count
- L17 _public member_ `int32 Sponsored = 1;` — When non-zero store will close when there are
- L20 _public prototype_ `void ReadFromSettings(const FPath& Path);`
- L21 _public prototype_ `void WriteToSettingsFile() const;`
- L22 _public prototype_ `void ApplySettingsFromCbor(const uint8* Buffer, uint32 NumBytes);`
- L23 _public prototype_ `void SerializeToCbor(TArray<uint8>& OutBuffer) const;`
- L24 _public function_ `uint32 GetChangeSerial() const`
- L25 _public prototype_ `void PrintToLog() const;`
- L28 _private member_ `uint32 ChangeSerial = 1;`

### `Source/Programs/UnrealTraceServer/src/TraceRelay.h` (Other)


#### class `FTraceRelay`  
`class FTraceRelay : public FAsioTcpServer , public FAsioIoSink , public FAsioTickable`  
_L15-37_
- inherits: `FAsioTcpServer,FAsioIoSink,FAsioTickable`
- L21 _public prototype_ `FTraceRelay(asio::io_context& IoContext, FAsioReadable* InInput, uint32 InTraceIf, FRecorder& InRecorder);`
- L22 _public prototype_ `~FTraceRelay();`
- L23 _public prototype_ `bool IsOpen() const;`
- L24 _public prototype_ `void Close();`
- L27 _private prototype_ `virtual bool OnAccept(asio::ip::tcp::socket& Socket) override;`
- L28 _private prototype_ `virtual void OnTick() override;`
- L29 _private prototype_ `virtual void OnIoComplete(uint32 Id, int32 Size) override;`
- L31 _private member_ `static const uint32 BufferSize = 64 << 10;`
- L32 _private member_ `FAsioReadable* Input;`
- L33 _private member_ `FAsioSocket* Output = nullptr;`
- L34 _private member_ `FRecorder& Recorder;`
- L35 _private member_ `uint32 SessionId;`
- L36 _private member_ `uint8 Buffer[BufferSize];`

#### enum `FTraceRelay::(anonymous)`  
`enum`  
_L30-30_

#### Free symbols / members of external scopes

- L30 _enumerator_ `enum { OpStart, OpRead, OpSend }; static const uint32 BufferSize = 64 << 10; FAsioReadable* Input; FAsioSocket* Output = nullptr; FRecorder& Recorder; uint32 SessionId; uint8 Buffer[BufferSize];` (scope `FTraceRelay::__anon70b392c50103`)
- L30 _enumerator_ `enum { OpStart, OpRead, OpSend }; static const uint32 BufferSize = 64 << 10; FAsioReadable* Input; FAsioSocket* Output = nullptr; FRecorder& Recorder; uint32 SessionId; uint8 Buffer[BufferSize];` (scope `FTraceRelay::__anon70b392c50103`)
- L30 _enumerator_ `enum { OpStart, OpRead, OpSend }; static const uint32 BufferSize = 64 << 10; FAsioReadable* Input; FAsioSocket* Output = nullptr; FRecorder& Recorder; uint32 SessionId; uint8 Buffer[BufferSize];` (scope `FTraceRelay::__anon70b392c50103`)

### `Source/Programs/UnrealTraceServer/src/Utils.h` (Other)


#### class `FInlineBufferBase`  
`class FInlineBufferBase`  
_L8-21_
- L11 _public prototype_ `FInlineBufferBase() = default;`
- L12 _public prototype_ `FInlineBufferBase(uint32 InlineMax);`
- L13 _public prototype_ `uint32 GetSize() const;`
- L14 _public prototype_ `bool HasOverflowed() const;`
- L17 _protected prototype_ `void SetMax(uint32 NewMax);`
- L18 _protected prototype_ `uint32 GetMax() const;`
- L19 _protected member_ `uint32 Used = 0;`
- L20 _protected member_ `int32 Max;`
- L24 _function_ `inline FInlineBufferBase::FInlineBufferBase(uint32 InlineMax) : Max(int32(~InlineMax))`
- L30 _function_ `inline uint32 FInlineBufferBase::GetSize() const`
- L36 _function_ `inline bool FInlineBufferBase::HasOverflowed() const`
- L42 _function_ `inline void FInlineBufferBase::SetMax(uint32 NewMax)`
- L48 _function_ `inline uint32 FInlineBufferBase::GetMax() const`

#### class `FInlineBuffer`  
`class FInlineBuffer : public FInlineBufferBase`  
_L56-66_
- inherits: `FInlineBufferBase`
- L60 _public prototype_ `uint8* Append(uint32 AppendSize);`
- L61 _public prototype_ `void Append(const void* Data, uint32 DataSize);`
- L62 _public prototype_ `const uint8* GetData() const;`
- L65 _private member_ `uint8 Buffer[];`
- L69 _function_ `inline uint8* FInlineBuffer::Append(uint32 AppendSize)`
- L106 _function_ `inline void FInlineBuffer::Append(const void* Data, uint32 DataSize)`
- L113 _function_ `inline const uint8* FInlineBuffer::GetData() const`

#### class `TInlineBuffer`  
`template <int Size> class TInlineBuffer : protected FInlineBufferBase`  
_L122-139_
- inherits: `FInlineBufferBase`
- L126 _public prototype_ `TInlineBuffer();`
- L127 _public prototype_ `~TInlineBuffer();`
- L128 _public prototype_ `operator FInlineBuffer& ();`
- L129 _public prototype_ `FInlineBuffer* operator -> ();`
- L143 _function_ `template <int Size> TInlineBuffer<Size>::TInlineBuffer() : FInlineBufferBase(BufferSize)`
- L150 _function_ `template <int Size> TInlineBuffer<Size>::~TInlineBuffer()`
- L160 _function_ `template <int Size> TInlineBuffer<Size>::operator FInlineBuffer& ()`
- L167 _function_ `template <int Size> FInlineBuffer* TInlineBuffer<Size>::operator -> ()`

#### enum `TInlineBuffer::(anonymous)`  
`enum`  
_L132-132_

#### union `TInlineBuffer::(anonymous)`  
``  
_L135-138_

#### Free symbols / members of external scopes

- L71 _function_ `auto GrowthPolicy = [] (uint32 Size, uint32 Demand) -> uint32` (scope `FInlineBuffer::Append`)
- L132 _enumerator_ `enum { BufferSize = (Size >= 16) ? Size : 16 }; union { uint8* Ptr; uint8 Buffer[BufferSize]; };` (scope `TInlineBuffer::__anonda6d814a0203`)
- L136 _member_ `uint8* Ptr;` (scope `TInlineBuffer::__anonda6d814a030a`)
- L137 _member_ `uint8 Buffer[BufferSize];` (scope `TInlineBuffer::__anonda6d814a030a`)
- L176 _function_ `template <typename Type> inline uint32 QuickStoreHash(const Type* String)`
- L187 _function_ `inline uint32 QuickStoreHash(FStringView View)`
- L201 _macro_ `# define DEBUG_BREAK() do { __debugbreak(); } while (0)`
- L203 _macro_ `# define DEBUG_BREAK() do { __builtin_trap(); exit(-1); } while (0)`
- L206 _macro_ `#define REQUIRE(x) \`

### `Source/Programs/UnrealTraceServer/src/Version.h` (Other)


#### Free symbols / members of external scopes

- L6 _macro_ `# define TS_VERSION_PROTOCOL 1`
- L10 _macro_ `# define TS_VERSION_MINOR 24`
- L13 _macro_ `#define TS_ICON_ID 493`
