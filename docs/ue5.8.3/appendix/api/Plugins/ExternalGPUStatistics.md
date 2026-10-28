# Plugins / ExternalGPUStatistics

- module root: `Plugins/Runtime/ExternalGPUStatistics/Source/ExternalGPUStatistics`
- headers: 2; symbols: 31
- symbol kinds: class=1, enum=1, enumerator=4, function=2, member=10, namespace=3, prototype=7, struct=3
- PrivateDependencyModuleNames: Engine, NVML, RHI, RenderCore, oneAPILevelZero
- PublicDependencyModuleNames: Core

### `Plugins/Runtime/ExternalGPUStatistics/Source/ExternalGPUStatistics/Private/Vendors/Intel.h` (Private)


#### struct `UE::GPUStats::Intel::FIntelDriver`  
`struct FIntelDriver`  
_L17-21_
- desc: Bundle these two together because it is only permissible to have one context per driver And as we shut down we want to destroy both of these
- L19 _public member_ `ze_driver_handle_t DriverHandle = nullptr;`
- L20 _public member_ `ze_context_handle_t ContextHandle = nullptr;`

#### struct `UE::GPUStats::Intel::FIntelDevice`  
`struct FIntelDevice`  
_L23-31_
- L27 _public member_ `FIntelDriver Driver;` — These are pointers, so it should be fine to just duplicate these Also should avoid an additional cache miss
- L28 _public member_ `ze_device_handle_t DeviceHandle = nullptr;`
- L30 _public member_ `uint32 CoreClockRate = 0;` — Used to determine our clock frequency percentage

#### enum `UE::GPUStats::Intel::EIntelMetricsToLookFor`  
`enum EIntelMetricsToLookFor`  
_L34-40_
- desc: These indices are not tied to the API but are just a way to index into the string and not have a dynamic array in the Metrics Streamer
- L36 _public enumerator_ `AvgGpuCoreFrequencyMHz = 0`
- L37 _public enumerator_ `GpuBusy = 1`
- L38 _public enumerator_ `SlmBytesWritten = 2`
- L39 _public enumerator_ `MAX_METRICS = 3`

#### struct `UE::GPUStats::Intel::FIntelMetricsStreamer`  
`struct FIntelMetricsStreamer`  
_L42-52_
- L44 _public member_ `zet_metric_streamer_handle_t MetricStreamerHandle = nullptr;`
- L46 _public member_ `uint32 NumMetrics = 0;` — Used for iteration over the individual reports, which are done at the group level
- L47 _public member_ `int32 MetricIndices[MAX_METRICS];` — These are the indices at which we should read from the metrics report
- L49 _public member_ `TArray<uint8> RawData;` — The Metrics Streamer provides data in a raw format of bytes which is then consumed by a separate function
- L51 _public member_ `TArray<zet_typed_value_t> CollectedMetrics;` — The properly typed data for user consumption

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace GPUStats` (scope `UE`)
- L12 _namespace_ `namespace Intel` (scope `UE::GPUStats`)
- L54 _prototype_ `bool GetDrivers(TArray<FIntelDriver> & Drivers);` (scope `UE::GPUStats::Intel`)
- L55 _prototype_ `bool GetDevicesForDriver(const FIntelDriver Driver, TArray<FIntelDevice> & Devices);` (scope `UE::GPUStats::Intel`)
- L56 _prototype_ `bool SetupMetricsForDevice(const FIntelDevice & Device, TArray<zet_metric_group_handle_t> & MetricsForDevice);` (scope `UE::GPUStats::Intel`)
- L57 _prototype_ `bool SetupMetricsStreamersForDevice(const FIntelDevice & Device, TArray<zet_metric_group_handle_t> & MetricsForDevice, TArray<FIntelMetricsStreamer> & MetricsStreamersForDevice);` (scope `UE::GPUStats::Intel`)
- L58 _prototype_ `bool CalculateMetrics(const FIntelDevice & Device, const TArray<zet_metric_group_handle_t> & Metrics, TArray<FIntelMetricsStreamer> & MetricsStreamers, float & OutFrequencyScaling, float & OutCurrentGPUUtilization, uint64_t & OutCurrentGPUMemoryUsage);` (scope `UE::GPUStats::Intel`)
- L60 _prototype_ `bool ShutdownMetricStreamer(FIntelMetricsStreamer & MetricsStreamer);` (scope `UE::GPUStats::Intel`) — Only these two have Level Zero API functions that special attention, the Metric Streamer may not even need it
- L61 _prototype_ `bool ShutdownDriver(FIntelDriver & Driver);` (scope `UE::GPUStats::Intel`)

### `Plugins/Runtime/ExternalGPUStatistics/Source/ExternalGPUStatistics/Public/IExternalGPUStatistics.h` (Public)


#### class `IExternalGPUStatistics`  
`class IExternalGPUStatistics : public IModuleInterface`  
_L14-39_
- inherits: `IModuleInterface`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L25 _public function_ `static inline IExternalGPUStatistics& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L35 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
