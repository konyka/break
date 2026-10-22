# Plugins / RuntimeTelemetry

- module root: `Plugins/Experimental/RuntimeTelemetry/Source`
- headers: 2; symbols: 15
- symbol kinds: class=2, delegate=1, macro=2, prototype=10
- PrivateDependencyModuleNames: Analytics, CoreUObject, StudioTelemetry
- PublicDependencyModuleNames: Core, Engine, IoStoreOnDemandCore

### `Plugins/Experimental/RuntimeTelemetry/Source/Public/RuntimeTelemetry.h` (Public)


#### class `FRuntimeTelemetry`  
`class FRuntimeTelemetry`  
_L17-34_
- L20 _public prototype_ `FRuntimeTelemetry() = default;`
- L21 _public prototype_ `~FRuntimeTelemetry() = default;`
- L23 _public prototype_ `static FRuntimeTelemetry& Get();`
- L25 _public prototype_ `void StartSession();`
- L26 _public prototype_ `void EndSession();`
- L29 _public prototype_ `void RecordEvent_IoStoreOnDemand(const FString& Context, TArray<FAnalyticsEventAttribute> Attributes = {});` — Useful event recording functions
- L30 _public prototype_ `void RecordEvent_MemoryLLM(const FString& Context, TArray<FAnalyticsEventAttribute> Attributes = {});`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API RUNTIMETELEMETRY_API`
- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogRuntimeTelemetry, Log, All);`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogRuntimeTelemetry, Log, All);`

### `Plugins/Experimental/RuntimeTelemetry/Source/Public/RuntimeTelemetryModule.h` (Public)


#### class `FRuntimeTelemetryModule`  
`class FRuntimeTelemetryModule : public IModuleInterface`  
_L10-18_
- inherits: `IModuleInterface`
- L14 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface
- L15 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API RUNTIMETELEMETRY_API`
