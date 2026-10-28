# Plugins / EditorTelemetry

- module root: `Plugins/Experimental/EditorTelemetry/Source`
- headers: 2; symbols: 71
- symbol kinds: class=2, macro=2, member=47, prototype=20
- PrivateDependencyModuleNames: Analytics, AssetRegistry, ContentBrowser, ContentBrowserData, CoreUObject, DerivedDataCache, Engine, HTTP, Json, StudioTelemetry, TelemetryUtils, UnrealEd, Zen
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/EditorTelemetry/Source/Public/EditorTelemetry.h` (Public)


#### class `FEditorTelemetry`  
`class FEditorTelemetry`  
_L22-103_
- desc: A class that implements a variety of pre-configured Core and Editor telemetry events that can be used to evaluate the efficiency of the most common developer workflows
- L26 _public prototype_ `FEditorTelemetry() = default;`
- L27 _public prototype_ `~FEditorTelemetry() = default;`
- L29 _public prototype_ `static FEditorTelemetry& Get();`
- L31 _public prototype_ `void StartSession();`
- L32 _public prototype_ `void EndSession();`
- L35 _public prototype_ `void RecordEvent_Cooking(const FString& Context, const TArray<FAnalyticsEventAttribute>& Attributes = {});` — Useful event recording functions
- L36 _public prototype_ `void RecordEvent_Loading(const FString& Context, double LoadingSeconds, const TArray<FAnalyticsEventAttribute>& Attributes = {});`
- L37 _public prototype_ `void RecordEvent_CoreSystems(const FString& Context, const TArray<FAnalyticsEventAttribute>& Attributes = {});`
- L38 _public prototype_ `void RecordEvent_DDCResource(const FString& Context, const TArray<FAnalyticsEventAttribute>& Attributes = {});`
- L39 _public prototype_ `void RecordEvent_DDCSummary(const FString& Context, const TArray<FAnalyticsEventAttribute>& Attributes = {});`
- L40 _public prototype_ `void RecordEvent_DDCVerification(const FString& Context, const TArray<FAnalyticsEventAttribute>& Attributes = {});`
- L41 _public prototype_ `void RecordEvent_Zen(const FString& Context, const TArray<FAnalyticsEventAttribute>& Attributes = {});`
- L42 _public prototype_ `void RecordEvent_VirtualAssets(const FString& Context, const TArray<FAnalyticsEventAttribute>& Attributes = {});`
- L43 _public prototype_ `void RecordEvent_MemoryLLM(const FString& Context, const TArray<FAnalyticsEventAttribute>& Attributes = {});`
- L44 _public prototype_ `void RecordEvent_ShaderStats(const FString& Context, const TArray<FAnalyticsEventAttribute>& Attributes = {});`
- L46 _public prototype_ `void RegisterCollectionWorkflowDelegates(FTelemetryRouter& Router);`
- L50 _private prototype_ `void HitchSamplerCallback();`
- L51 _private prototype_ `void HeartbeatCallback();`
- L53 _private member_ `TSharedPtr<IAnalyticsSpan> EditorSpan;`
- L54 _private member_ `TSharedPtr<IAnalyticsSpan> EditorBootSpan;`
- L55 _private member_ `TSharedPtr<IAnalyticsSpan> EditorInteractSpan;`
- L56 _private member_ `TSharedPtr<IAnalyticsSpan> EditorInitilizeSpan;`
- L57 _private member_ `TSharedPtr<IAnalyticsSpan> EditorLoadMapSpan;`
- L58 _private member_ `TSharedPtr<IAnalyticsSpan> PIESpan;`
- L59 _private member_ `TSharedPtr<IAnalyticsSpan> PIEPreBeginSpan;`
- L60 _private member_ `TSharedPtr<IAnalyticsSpan> PIEStartupSpan;`
- L61 _private member_ `TSharedPtr<IAnalyticsSpan> PIELoadMapSpan;`
- L62 _private member_ `TSharedPtr<IAnalyticsSpan> PIEInteractSpan;`
- L63 _private member_ `TSharedPtr<IAnalyticsSpan> PIEShutdownSpan;`
- L64 _private member_ `TSharedPtr<IAnalyticsSpan> CookingSpan;`
- L65 _private member_ `TSharedPtr<IAnalyticsSpan> HitchingSpan;`
- L66 _private member_ `TSharedPtr<IAnalyticsSpan> AssetRegistryScanSpan;`
- L68 _private member_ `const FName EditorSpanName = TEXT("Edi`
- L69 _private member_ `const FName EditorBootSpanName = TEXT("Edi`
- L70 _private member_ `const FName EditorInitilizeSpanName = TEXT("Edi`
- L71 _private member_ `const FName EditorInteractSpanName = TEXT("Edi`
- L72 _private member_ `const FName EditorLoadMapSpanName = TEXT("Edi`
- L73 _private member_ `const FName AssetRegistryScanSpanName = TEXT("Edi`
- L74 _private member_ `const FName PIESpanName = TEXT("PIE`
- L75 _private member_ `const FName PIEStartupSpanName = TEXT("PIE`
- L76 _private member_ `const FName PIEPreBeginSpanName = TEXT("PIE`
- L77 _private member_ `const FName PIELoadMapSpanName = TEXT("PIE`
- L78 _private member_ `const FName PIEInteractSpanName = TEXT("PIE`
- L79 _private member_ `const FName PIEShutdownSpanName = TEXT("PIE`
- L80 _private member_ `const FName CookingSpanName = TEXT("Coo`
- L81 _private member_ `const FName HitchingSpanName = TEXT("Hit`
- L82 _private member_ `const FName OpenAssetEditorSpan = TEXT("Ope`
- L83 _private member_ `const float HeartbeatIntervalSeconds = 1.0;`
- L84 _private member_ `const float HitchSamplerIntervalSeconds = 0.1f;`
- L85 _private member_ `const float MinFPSForHitching = 5.0f;`
- L87 _private member_ `TMap<FGuid, TSharedPtr<IAnalyticsSpan>> TaskSpans;`
- L88 _private member_ `FCriticalSection TaskSpanCriticalSection;`
- L90 _private member_ `FTimerHandle TelemetryHeartbeatTimerHandle;`
- L91 _private member_ `FTimerHandle TelemetryHitchSamplerTimerHandle;`
- L92 _private member_ `FString EditorMapName;`
- L93 _private member_ `FString PIEMapName;`
- L94 _private member_ `uint32 EditorSessionCount = 0;`
- L95 _private member_ `uint32 PIESessionCount = 0;`
- L96 _private member_ `double SessionStartTime;`
- L97 _private member_ `double AssetOpenStartTime;`
- L98 _private member_ `double TimeToBootEditor;`
- L99 _private member_ `double HitchAvergageFPS = 0;`
- L100 _private member_ `uint32 HitchSampleCount = 0;`
- L101 _private member_ `uint32 TotalPluginCount = 0;`
- L102 _private member_ `uint32 AssetRegistryScanCount = 0;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API EDITORTELEMETRY_API`

### `Plugins/Experimental/EditorTelemetry/Source/Public/EditorTelemetryModule.h` (Public)


#### class `FEditorTelemetryModule`  
`class FEditorTelemetryModule : public IModuleInterface`  
_L10-18_
- inherits: `IModuleInterface`
- L14 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface
- L15 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API EDITORTELEMETRY_API`
