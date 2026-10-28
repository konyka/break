# Runtime / StorageServerClientDebug

- module root: `Source/Runtime/StorageServerClientDebug`
- headers: 1; symbols: 28
- symbol kinds: class=1, function=1, member=19, prototype=6, struct=1
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, Json, Sockets, StorageServerClient

### `Source/Runtime/StorageServerClientDebug/Private/StorageServerConnectionDebug.h` (Private)


#### class `FStorageServerConnectionDebug`  
`class FStorageServerConnectionDebug`  
_L12-60_
- L15 _public function_ `FStorageServerConnectionDebug( IStorageServerPlatformFile* InStorageServerPlatformFile ) : StorageServerPlatformFile(InStorageServerPlatformFile) , HostAddress(InStorageServerPlatformFile->GetHostAddr())`
- L22 _public prototype_ `bool OnTick(float);` — FTickerDelegate
- L23 _public prototype_ `void OnDraw(UCanvas*, APlayerController*);` — FDebugDrawDelegate
- L26 _private prototype_ `void LoadZenStreamingSettings();`
- L28 _private prototype_ `void DrawZenIndicator(UCanvas* Canvas);`
- L29 _private prototype_ `void CreateZenIcon();`
- L30 _private prototype_ `void DestroyZenIcon();`
- L32 _private member_ `double MaxReqThroughput = 0.0;`
- L33 _private member_ `double MinReqThroughput = 0.0;`
- L34 _private member_ `uint32 ReqCount = 0;`
- L35 _private member_ `double Throughput = 0.0;`
- L46 _private member_ `std::vector<HistoryItem> History = {{0, 0, 0, 0, 0}};`
- L48 _private member_ `static constexpr float UpdateStatsTimer = 1.0;`
- L49 _private member_ `double UpdateStatsTime = 0.0;`
- L51 _private member_ `IStorageServerPlatformFile* StorageServerPlatformFile = nullptr;`
- L52 _private member_ `FString HostAddress;`
- L54 _private member_ `FCriticalSection CS;`
- L56 _private member_ `class UTexture2D* ZenIcon = nullptr;`
- L57 _private member_ `bool bDestroyZenIcon = false;`
- L58 _private member_ `double IndicatorElapsedTime = 0.0;`
- L59 _private member_ `double IndicatorLastTime = 0.0;`

#### struct `FStorageServerConnectionDebug::HistoryItem`  
`struct HistoryItem`  
_L37-44_
- L39 _public member_ `double Time;`
- L40 _public member_ `double MaxRequestThroughput;`
- L41 _public member_ `double MinRequestThroughput;`
- L42 _public member_ `double Throughput;`
- L43 _public member_ `uint32 RequestCount;`
