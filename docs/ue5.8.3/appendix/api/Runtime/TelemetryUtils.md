# Runtime / TelemetryUtils

- module root: `Source/Runtime/Analytics/TelemetryUtils`
- headers: 2; symbols: 36
- symbol kinds: class=2, function=12, member=5, namespace=3, prototype=11, struct=1, variable=2
- PublicDependencyModuleNames: Core

### `Source/Runtime/Analytics/TelemetryUtils/Public/TelemetryRouter.h` (Public)


#### class `FTelemetryRouter`  
`class FTelemetryRouter`  
_L69-156_
- desc: Provides an interface for routing structured telemetry data between prooducers (engine/editor systems) and consumers (modules which will format the data for a particular telemetry endpoint) Usage: Declare a unique type for telemetry data. This type needs a static FGuid data member called TelemetryID. Provide data to any interested aggregators with the method ProvideTelemetry. Aggregators can register a callback for telemetry data with the method OnTelemetry. The guid associated with a type for routing should not be relied on by consumers to be stable across engine versions or even across different processes, it is only used for runtime routing purposes. It should not be sent to telemetry endpoints. @thread_safety Functions are internally synchronized. Re-entrant calls to the public API during callbacks are unsupported. Data is routed on the same thread it is provided. Users should copy data and schedule tasks to execute on a specified thread if they require that.
- L72 _public prototype_ `FTelemetryRouter();`
- L73 _public prototype_ `~FTelemetryRouter();`
- L75 _public prototype_ `static FTelemetryRouter& Get();`
- L83 _public function_ `template<typename DATA_TYPE> inline void ProvideTelemetry(const DATA_TYPE& Data)` — Sends data in a type-safe manner to consumers expecting this data type. @param Data Strongly typed data to be sent. Type must implement a static method called GetTelemetryID returning an FGuid.
- L94 _public function_ `template<typename DATA_TYPE> inline FDelegateHandle OnTelemetry(TDelegate<void(const DATA_TYPE&)> Sink)` — Registers a delegate as callback to receive telemetry of a certain type. @return a handle that can be used to unregister this sink later so it is no longer called.
- L113 _public function_ `inline FDelegateHandle OnTelemetry(CALLABLE&& Sink)`
- L128 _public function_ `template<typename DATA_TYPE> inline void UnregisterTelemetrySink(FDelegateHandle Handle)` — Removes a previously registered callback.
- L137 _private prototype_ `void RegisterTelemetrySinkInternal(FGuid Key, SIZE_T ExpectedSize, FDelegateHandle InHandle, TFunction<bool(FMemoryView)> Sink);` — Register a callback to receive telemetry. The callback should return false if the sink is stale and should be removed from future consideration.
- L138 _private prototype_ `void UnregisterTelemetrySinkInternal(FGuid Key, FDelegateHandle InHandle);`
- L139 _private prototype_ `void ProvideTelemetryInternal(FGuid Key, FMemoryView Data);`
- L140 _private prototype_ `void CheckNotReentrant();`
- L142 _private member_ `FRWLock SinkLock;`
- L155 _private member_ `TMap<FGuid, FSinkSet> KeyToSinks;`

#### struct `FTelemetryRouter::FSinkSet`  
`struct FSinkSet`  
_L144-153_
- L146 _public member_ `SIZE_T DataSize;`
- L147 _public member_ `TMap<FDelegateHandle, TFunction<bool(FMemoryView)>> Delegates;`
- L149 _public function_ `FSinkSet(SIZE_T InDataSize) : DataSize(InDataSize)`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Telemetry` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Telemetry`)
- L16 _variable_ `template<typename DATA_TYPE, typename = void> constexpr bool HasTelemetryID = false;` (scope `UE::Telemetry::Private`)
- L19 _variable_ `template<typename DATA_TYPE> constexpr bool HasTelemetryID< DATA_TYPE, std::enable_if_t<std::is_same_v<std::decay_t<decltype(DATA_TYPE::TelemetryID)>, FGuid>>> = true;` (scope `UE::Telemetry::Private`)
- L24 _function_ `template <typename DATA_TYPE> auto GetDataKeyInternal()` (scope `UE::Telemetry::Private`)
- L37 _function_ `template <typename DATA_TYPE> FGuid GetDataKey()` (scope `UE::Telemetry::Private`)
- L99 _function_ `RegisterTelemetrySinkInternal(UE::Telemetry::Private::GetDataKey<DATA_TYPE>(), sizeof(DATA_TYPE), Handle, [Sink=MoveTemp(Sink)](FMemoryView Data) -> bool { return Sink.ExecuteIfBound(*reinterpret_cast<const DATA_TYPE*>(Data.GetData())); });` (scope `FTelemetryRouter::OnTelemetry`)
- L117 _function_ `RegisterTelemetrySinkInternal(UE::Telemetry::Private::GetDataKey<DATA_TYPE>(), sizeof(DATA_TYPE), Handle, [Sink=MoveTemp(Sink)](FMemoryView Data) -> bool { Sink(*reinterpret_cast<const DATA_TYPE*>(Data.GetData())); return true; });` (scope `FTelemetryRouter::OnTelemetry`)

### `Source/Runtime/Analytics/TelemetryUtils/Public/TelemetryUtils.h` (Public)


#### class `FTelemetryUtils`  
`class FTelemetryUtils : public IModuleInterface`  
_L14-44_
- inherits: `IModuleInterface`
- L17 _public prototype_ `FTelemetryUtils();`
- L18 _public prototype_ `virtual ~FTelemetryUtils();`
- L20 _public function_ `static inline FTelemetryUtils& Get()`
- L25 _public function_ `static inline bool IsAvailable()`
- L33 _public function_ `static FTelemetryRouter& GetRouter()` — Returns an object used for routing structured telemetry data between producers and consumers.
- L39 _private prototype_ `virtual void StartupModule() override;`
- L40 _private prototype_ `virtual void ShutdownModule() override;`
- L43 _private member_ `TUniquePtr<FTelemetryRouter> Router;`
