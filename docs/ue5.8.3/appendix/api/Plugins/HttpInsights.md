# Plugins / HttpInsights

- module root: `Plugins/Experimental/HttpInsights/Source`
- headers: 2; symbols: 68
- symbol kinds: class=2, macro=1, member=40, namespace=4, prototype=11, struct=9, typedef=1
- PrivateDependencyModuleNames: Core, CoreUObject, InputCore, Slate, SlateCore, ToolMenus, ToolWidgets, TraceAnalysis, TraceInsights, TraceInsightsCore, TraceServices

### `Plugins/Experimental/HttpInsights/Source/Private/Model.h` (Private)


#### struct `UE::HttpInsights::FHttpDispatcher`  
`struct FHttpDispatcher`  
_L16-20_
- L18 _public member_ `const uint64 Handle = 0;`
- L19 _public member_ `const FString Name;`

#### struct `UE::HttpInsights::FHttpChunkRange`  
`struct FHttpChunkRange`  
_L23-29_
- L25 _public member_ `FHttpChunkRange* Next = nullptr;`
- L26 _public member_ `FIoChunkId ChunkId = FIoChunkId::InvalidChunkId;`
- L27 _public member_ `uint32 Start = MAX_uint32;`
- L28 _public member_ `uint32 End = MIN_uint32;`

#### struct `UE::HttpInsights::FHttpRequest`  
`struct FHttpRequest`  
_L32-45_
- L34 _public member_ `const FHttpDispatcher& Dispatcher;`
- L35 _public member_ `double StartTime = 0.0;`
- L36 _public member_ `double CompletionTime = 0.0;`
- L37 _public member_ `uint32 StatusCode = 0;`
- L38 _public member_ `uint32 ContentLength = 0;`
- L39 _public member_ `uint32 SeqNo = 0;`
- L40 _public member_ `FHttpChunkRange* ChunkRanges = nullptr;`
- L41 _public member_ `FString Host;`
- L42 _public member_ `FString Url;`
- L43 _public member_ `const FString* CategoryName = nullptr;`
- L44 _public member_ `uint8 Category = MAX_uint8;`

#### struct `UE::HttpInsights::FHttpDispatcherCreated`  
`struct FHttpDispatcherCreated`  
_L48-52_
- L50 _public member_ `uint64 Dispatcher = 0;`
- L51 _public member_ `FAnsiString Name;`

#### struct `UE::HttpInsights::FHttpCategoryCreated`  
`struct FHttpCategoryCreated`  
_L55-59_
- L57 _public member_ `uint8 Category = MAX_uint8;`
- L58 _public member_ `FAnsiString Name;`

#### struct `UE::HttpInsights::FHttpRequestStarted`  
`struct FHttpRequestStarted`  
_L62-71_
- L64 _public member_ `uint64 Dispatcher = 0;`
- L65 _public member_ `uint64 Request = 0;`
- L66 _public member_ `double StartTime = 0.0;`
- L67 _public member_ `int32 Priority = 0;`
- L68 _public member_ `uint32 Category = 0;`
- L69 _public member_ `FHttpChunkRange* ChunkRanges = nullptr;`
- L70 _public member_ `FAnsiString Url;`

#### struct `UE::HttpInsights::FHttpChunkRangeAdded`  
`struct FHttpChunkRangeAdded`  
_L74-80_
- L76 _public member_ `uint64 Request = 0;`
- L77 _public member_ `uint32 Start = MAX_uint32;`
- L78 _public member_ `uint32 End = MIN_uint32;`
- L79 _public member_ `FIoChunkId ChunkId = FIoChunkId::InvalidChunkId;`

#### struct `UE::HttpInsights::FHttpRequestCompleted`  
`struct FHttpRequestCompleted`  
_L83-90_
- L85 _public member_ `uint64 Request = 0;`
- L86 _public member_ `double CompletionTime = 0.0;`
- L87 _public member_ `uint32 StatusCode = 0;`
- L88 _public member_ `uint32 ContentLength = 0;`
- L89 _public member_ `FAnsiString Host;`

#### struct `UE::HttpInsights::FPackageIdMapped`  
`struct FPackageIdMapped`  
_L93-97_
- L95 _public member_ `FPackageId PackageId;`
- L96 _public member_ `const TCHAR* PackageName = nullptr;`

#### class `UE::HttpInsights::IHttpLogModel`  
`class IHttpLogModel : public TraceServices::IProvider`  
_L100-116_
- inherits: `TraceServices::IProvider`
- L104 _public member_ `inline static const FName ProviderName = TEXT("Htt`
- L105 _public typedef_ `using FReadLogFunc = TFunctionRef<void(const FHttpRequest&)>;`
- L107 _public prototype_ `virtual ~IHttpLogModel() = default;`
- L108 _public prototype_ `virtual void ProcesEvent(FHttpDispatcherCreated&&) = 0;`
- L109 _public prototype_ `virtual void ProcesEvent(FHttpCategoryCreated&&) = 0;`
- L110 _public prototype_ `virtual void ProcesEvent(FHttpRequestStarted&&) = 0;`
- L111 _public prototype_ `virtual void ProcesEvent(FHttpChunkRangeAdded&&) = 0;`
- L112 _public prototype_ `virtual void ProcesEvent(FHttpRequestCompleted&&) = 0;`
- L113 _public prototype_ `virtual void ProcesEvent(FPackageIdMapped&&) = 0;`
- L114 _public prototype_ `virtual int32 IterateLog(int32 StartIndex, FReadLogFunc&&) const = 0;`
- L115 _public prototype_ `virtual const TCHAR* GetPackageName(const FIoChunkId&) const = 0;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace HttpInsights` (scope `UE`)
- L119 _prototype_ `TSharedPtr<IHttpLogModel> MakeHttpLogModel(TraceServices::IAnalysisSession& Session);` (scope `UE::HttpInsights`)

### `Plugins/Experimental/HttpInsights/Source/Public/HttpInsights/ModuleInterface.h` (Public)


#### class `UE::HttpInsights::IHttpInsightsModule`  
`class IHttpInsightsModule : public IModuleInterface`  
_L17-21_
- inherits: `IModuleInterface`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API HTTPINSIGHTS_API`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogHttpInsights, Log, All);`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace HttpInsights` (scope `UE`)
