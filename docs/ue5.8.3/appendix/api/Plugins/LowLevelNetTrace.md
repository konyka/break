# Plugins / LowLevelNetTrace

- module root: `Plugins/Experimental/LowLevelNetTrace/Source/LowLevelNetTrace`
- headers: 2; symbols: 12
- symbol kinds: class=2, function=2, macro=1, member=3, prototype=3, struct=1
- PrivateDependencyModuleNames: Core

### `Plugins/Experimental/LowLevelNetTrace/Source/LowLevelNetTrace/Private/ILowLevelNetTrace.h` (Private)


#### class `ILowLevelNetTrace`  
`class ILowLevelNetTrace`  
_L10-16_
- L13 _public prototype_ `virtual ~ILowLevelNetTrace() = default;`
- L15 _public prototype_ `virtual bool UpdateSnapshot( FLowLevelNetTraceSnapshot& OutSnapshot ) = 0;`

### `Plugins/Experimental/LowLevelNetTrace/Source/LowLevelNetTrace/Public/LowLevelNetTraceModule.h` (Public)


#### struct `FLowLevelNetTraceSnapshot`  
`struct FLowLevelNetTraceSnapshot`  
_L13-18_
- L15 _public member_ `double UploadMbps = 0.0;`
- L16 _public member_ `double DownloadMbps = 0.0;`
- L17 _public member_ `double TimeStamp = 0.0;`

#### class `ILowLevelNetTraceModule`  
`class ILowLevelNetTraceModule : public IModuleInterface`  
_L20-34_
- inherits: `IModuleInterface`
- L23 _public function_ `static inline ILowLevelNetTraceModule& Get()`
- L28 _public function_ `static inline bool IsAvailable()`
- L33 _public prototype_ `virtual bool GetSnapshot( FLowLevelNetTraceSnapshot& OutSnapshot ) = 0;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_LOW_LEVEL_NET_TRACE_ENABLED ((!UE_BUILD_SHIPPING) && UE_TRACE_ENABLED)`
