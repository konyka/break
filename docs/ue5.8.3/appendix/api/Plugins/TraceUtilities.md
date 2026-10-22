# Plugins / TraceUtilities

- module root: `Plugins/TraceUtilities/Source/TraceUtilities`
- headers: 1; symbols: 16
- symbol kinds: class=1, macro=1, prototype=14
- PrivateDependencyModuleNames: CoreUObject, Engine, TraceLog
- PublicDependencyModuleNames: Core

### `Plugins/TraceUtilities/Source/TraceUtilities/Public/TraceUtilLibrary.h` (Public)


#### class `UTraceUtilLibrary`  
`class UTraceUtilLibrary : public UBlueprintFunctionLibrary`  
_L11-69_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L17 _public prototype_ `static bool StartTraceToFile(const FString& FileName, const TArray<FString>& Channels);` — `UFUNCTION(BlueprintCallable, Category = "Perf | Insights Trace")`
- L20 _public prototype_ `static bool StartTraceSendTo(const FString& Target, const TArray<FString>& Channels);` — `UFUNCTION(BlueprintCallable, Category = "Perf | Insights Trace")`
- L23 _public prototype_ `static bool StopTracing();` — `UFUNCTION(BlueprintCallable, Category = "Perf | Insights Trace")`
- L26 _public prototype_ `static bool PauseTracing();` — `UFUNCTION(BlueprintCallable, Category = "Perf | Insights Trace")`
- L29 _public prototype_ `static bool ResumeTracing();` — `UFUNCTION(BlueprintCallable, Category = "Perf | Insights Trace")`
- L32 _public prototype_ `static bool IsTracing();` — `UFUNCTION(BlueprintCallable, Category = "Perf | Insights Trace")`
- L35 _public prototype_ `static bool ToggleChannel(const FString& ChannelName, bool enabled);` — `UFUNCTION(BlueprintCallable, Category = "Perf | Insights Trace")`
- L38 _public prototype_ `static bool IsChannelEnabled(const FString& ChannelName);` — `UFUNCTION(BlueprintCallable, Category = "Perf | Insights Trace")`
- L41 _public prototype_ `static TArray<FString> GetEnabledChannels();` — `UFUNCTION(BlueprintCallable, Category = "Perf | Insights Trace")`
- L44 _public prototype_ `static TArray<FString> GetAllChannels();` — `UFUNCTION(BlueprintCallable, Category = "Perf | Insights Trace")`
- L50 _public prototype_ `static void TraceBookmark(const FString& Name);` — `UFUNCTION(BlueprintCallable, Category = "Perf | Insights Trace")` — Traces a bookmark with specified name.
- L56 _public prototype_ `static void TraceMarkRegionStart(const FString& Name);` — `UFUNCTION(BlueprintCallable, Category = "Perf | Insights Trace")` — Traces a begin event for a region with specified name.
- L62 _public prototype_ `static void TraceMarkRegionEnd(const FString& Name);` — `UFUNCTION(BlueprintCallable, Category = "Perf | Insights Trace")` — Traces an end event for a region with specified name.
- L68 _public prototype_ `static void TraceScreenshot(const FString& Name, bool bShowUI);` — `UFUNCTION(BlueprintCallable, Category = "Perf | Insights Trace")` — Triggers an Unreal Insights screenshot

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API TRACEUTILITIES_API`
