# Plugins / Reflex

- module root: `Plugins/Runtime/Nvidia/Reflex/Source`
- headers: 5; symbols: 131
- symbol kinds: class=5, enum=1, enumerator=3, function=34, macro=1, member=32, prototype=55

### `Plugins/Runtime/Nvidia/Reflex/Source/Private/ReflexModule.h` (Private)


#### class `FReflexModule`  
`class FReflexModule : public IModuleInterface`  
_L11-29_
- inherits: `IModuleInterface`
- L14 _public prototype_ `FReflexModule() = default;`
- L15 _public prototype_ `~FReflexModule() = default;`
- L18 _public prototype_ `virtual void StartupModule() override;`
- L19 _public prototype_ `virtual void ShutdownModule() override;`
- L22 _public prototype_ `static struct IUnknown* GetD3DDevice();`
- L26 _private member_ `TUniquePtr<FReflexMaxTickRateHandler> ReflexMaxTickRateHandler;`
- L27 _private member_ `TUniquePtr<FReflexLatencyMarkers> ReflexLatencyMarker;`
- L28 _private member_ `TUniquePtr<FReflexStatsLatencyMarkers> ReflexStatsLatencyMarker;`

### `Plugins/Runtime/Nvidia/Reflex/Source/Public/ReflexBlueprint.h` (Public)


#### enum `EReflexMode`  
`enum class EReflexMode : uint8`  
_L12-17_
- reflection: `UENUM(BlueprintType)`
- L14 _public enumerator_ `Disabled = 0 UMETA(DisplayName="Disabled")`
- L15 _public enumerator_ `Enabled = 1 UMETA(DisplayName="Enabled")`
- L16 _public enumerator_ `EnabledPlusBoost = 3 UMETA(DisplayName="Enabled + Boost")`

#### class `UReflexBlueprintLibrary`  
`class UReflexBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L21-44_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L26 _private prototype_ `static bool GetReflexAvailable();` — `UFUNCTION(BlueprintPure, Category="Reflex")`
- L29 _private prototype_ `static void SetReflexMode(const EReflexMode Mode);` — `UFUNCTION(BlueprintCallable, Category="Reflex")`
- L31 _private prototype_ `static EReflexMode GetReflexMode();` — `UFUNCTION(BlueprintPure, Category="Reflex")`
- L34 _private prototype_ `static void SetFlashIndicatorEnabled(const bool bEnabled);` — `UFUNCTION(BlueprintCallable, Category="Reflex")`
- L36 _private prototype_ `static bool GetFlashIndicatorEnabled();` — `UFUNCTION(BlueprintPure, Category="Reflex")`
- L39 _private prototype_ `static float GetGameToRenderLatencyInMs();` — `UFUNCTION(BlueprintPure, Category="Reflex")`
- L41 _private prototype_ `static float GetGameLatencyInMs();` — `UFUNCTION(BlueprintPure, Category="Reflex")`
- L43 _private prototype_ `static float GetRenderLatencyInMs();` — `UFUNCTION(BlueprintPure, Category="Reflex")`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API REFLEX_API`

### `Plugins/Runtime/Nvidia/Reflex/Source/Public/ReflexLatencyMarkers.h` (Public)


#### class `FReflexLatencyMarkers`  
`class FReflexLatencyMarkers : public ILatencyMarkerModule, public FTickableGameObject, public FSelfRegisteringExec`  
_L10-81_
- inherits: `ILatencyMarkerModule,FTickableGameObject,FSelfRegisteringExec`
- L13 _public prototype_ `virtual ~FReflexLatencyMarkers() = default;`
- L15 _public member_ `bool bFeatureSupport = false;`
- L17 _public member_ `float AverageTotalLatencyMs = 0.0f;`
- L18 _public member_ `float AverageGameLatencyMs = 0.0f;`
- L19 _public member_ `float AverageRenderLatencyMs = 0.0f;`
- L21 _public member_ `float AverageSimulationLatencyMs = 0.0f;`
- L22 _public member_ `float AverageRenderSubmitLatencyMs = 0.0f;`
- L23 _public member_ `float AveragePresentLatencyMs = 0.0f;`
- L24 _public member_ `float AverageDriverLatencyMs = 0.0f;`
- L25 _public member_ `float AverageOSRenderQueueLatencyMs = 0.0f;`
- L26 _public member_ `float AverageGPURenderLatencyMs = 0.0f;`
- L28 _public member_ `float RenderSubmitOffsetMs = 0.0f;`
- L29 _public member_ `float PresentOffsetMs = 0.0f;`
- L30 _public member_ `float DriverOffsetMs = 0.0f;`
- L31 _public member_ `float OSRenderQueueOffsetMs = 0.0f;`
- L32 _public member_ `float GPURenderOffsetMs = 0.0f;`
- L34 _public member_ `bool bEnabled = false;`
- L35 _public member_ `bool bFlashIndicatorEnabled = false;`
- L36 _public member_ `bool bFlashIndicatorDriverControlled = false;`
- L38 _public prototype_ `virtual void Tick(float DeltaTime);`
- L39 _public function_ `virtual bool IsTickable() const`
- L40 _public function_ `virtual bool IsTickableInEditor() const`
- L41 _public function_ `virtual bool IsTickableWhenPaused() const`
- L42 _public function_ `virtual TStatId GetStatId(void) const`
- L44 _public prototype_ `virtual void Initialize() override;`
- L46 _public prototype_ `virtual void SetEnabled(bool bInEnabled) override;`
- L47 _public prototype_ `virtual bool GetEnabled() override;`
- L48 _public prototype_ `virtual bool GetAvailable() override;`
- L49 _public prototype_ `virtual void SetFlashIndicatorEnabled(bool bInEnabled) override;`
- L50 _public prototype_ `virtual bool GetFlashIndicatorEnabled() override;`
- L52 _public prototype_ `virtual void SetInputSampleLatencyMarker(uint64 FrameNumber) override;`
- L53 _public prototype_ `virtual void SetSimulationLatencyMarkerStart(uint64 FrameNumber) override;`
- L54 _public prototype_ `virtual void SetSimulationLatencyMarkerEnd(uint64 FrameNumber) override;`
- L55 _public prototype_ `virtual void SetRenderSubmitLatencyMarkerStart(uint64 FrameNumber) override;`
- L56 _public prototype_ `virtual void SetRenderSubmitLatencyMarkerEnd(uint64 FrameNumber) override;`
- L57 _public prototype_ `virtual void SetPresentLatencyMarkerStart(uint64 FrameNumber) override;`
- L58 _public prototype_ `virtual void SetPresentLatencyMarkerEnd(uint64 FrameNumber) override;`
- L59 _public prototype_ `virtual void SetFlashIndicatorLatencyMarker(uint64 FrameNumber) override;`
- L60 _public prototype_ `virtual void SetCustomLatencyMarker(uint32 MarkerId, uint64 FrameNumber) override;`
- L62 _public function_ `virtual float GetTotalLatencyInMs() override`
- L63 _public function_ `virtual float GetGameLatencyInMs() override` — This is defined as "Game simulation start to driver submission end"
- L64 _public function_ `virtual float GetRenderLatencyInMs() override` — This is defined as "OS render queue start to GPU render end"
- L66 _public function_ `virtual float GetSimulationLatencyInMs() override`
- L67 _public function_ `virtual float GetRenderSubmitLatencyInMs() override`
- L68 _public function_ `virtual float GetPresentLatencyInMs() override`
- L69 _public function_ `virtual float GetDriverLatencyInMs() override`
- L70 _public function_ `virtual float GetOSRenderQueueLatencyInMs() override`
- L71 _public function_ `virtual float GetGPURenderLatencyInMs() override`
- L73 _public function_ `virtual float GetRenderSubmitOffsetFromFrameStartInMs() override`
- L74 _public function_ `virtual float GetPresentOffsetFromFrameStartInMs() override`
- L75 _public function_ `virtual float GetDriverOffsetFromFrameStartInMs() override`
- L76 _public function_ `virtual float GetOSRenderQueueOffsetFromFrameStartInMs() override`
- L77 _public function_ `virtual float GetGPURenderOffsetFromFrameStartInMs() override`
- L80 _protected prototype_ `virtual bool Exec_Runtime(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;`

### `Plugins/Runtime/Nvidia/Reflex/Source/Public/ReflexMaxTickRateHandler.h` (Public)


#### class `FReflexMaxTickRateHandler`  
`class FReflexMaxTickRateHandler : public IMaxTickRateHandlerModule, public FSelfRegisteringExec`  
_L9-38_
- inherits: `IMaxTickRateHandlerModule,FSelfRegisteringExec`
- L12 _public prototype_ `virtual ~FReflexMaxTickRateHandler() = default;`
- L14 _public prototype_ `virtual void Initialize() override;`
- L15 _public prototype_ `virtual void SetEnabled(bool bInEnabled) override;`
- L16 _public prototype_ `virtual bool GetEnabled() override;`
- L17 _public prototype_ `virtual bool GetAvailable() override;`
- L20 _public prototype_ `virtual void SetFlags(uint32 Flags);` — Used to provide a generic customization interface for custom tick rate handlers
- L21 _public prototype_ `virtual uint32 GetFlags();`
- L23 _public prototype_ `virtual bool HandleMaxTickRate(float DesiredMaxTickRate) override;`
- L25 _public member_ `bool bEnabled = false;`
- L26 _public member_ `bool bWasEnabled = false;`
- L27 _public member_ `bool bProperDriverVersion = false;`
- L28 _public member_ `bool bFeatureSupport = false;`
- L29 _public member_ `float MinimumInterval = -1.0f;`
- L30 _public member_ `bool bLowLatencyMode = true;`
- L31 _public member_ `bool bBoost = false;`
- L33 _public member_ `uint32 CustomFlags = 0;`
- L34 _public member_ `uint32 LastCustomFlags = 0;`
- L37 _protected prototype_ `virtual bool Exec_Runtime(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;`

### `Plugins/Runtime/Nvidia/Reflex/Source/Public/ReflexStatsLatencyMarkers.h` (Public)


#### class `FReflexStatsLatencyMarkers`  
`class FReflexStatsLatencyMarkers: public ILatencyMarkerModule, public IWindowsMessageHandler`  
_L7-51_
- inherits: `ILatencyMarkerModule,IWindowsMessageHandler`
- L10 _public prototype_ `virtual ~FReflexStatsLatencyMarkers();`
- L12 _public prototype_ `virtual void Initialize() override;`
- L14 _public prototype_ `virtual void SetEnabled(bool bInEnabled) override;`
- L15 _public prototype_ `virtual bool GetEnabled() override;`
- L16 _public prototype_ `virtual bool GetAvailable() override;`
- L18 _public function_ `virtual void SetFlashIndicatorEnabled(bool bInEnabled) override`
- L19 _public function_ `virtual bool GetFlashIndicatorEnabled() override`
- L21 _public prototype_ `virtual void SetInputSampleLatencyMarker(uint64 FrameNumber) override;`
- L22 _public prototype_ `virtual void SetSimulationLatencyMarkerStart(uint64 FrameNumber) override;`
- L23 _public prototype_ `virtual void SetSimulationLatencyMarkerEnd(uint64 FrameNumber) override;`
- L24 _public prototype_ `virtual void SetPresentLatencyMarkerStart(uint64 FrameNumber) override;`
- L25 _public prototype_ `virtual void SetPresentLatencyMarkerEnd(uint64 FrameNumber) override;`
- L26 _public prototype_ `virtual void SetRenderSubmitLatencyMarkerStart(uint64 FrameNumber) override;`
- L27 _public prototype_ `virtual void SetRenderSubmitLatencyMarkerEnd(uint64 FrameNumber) override;`
- L28 _public prototype_ `virtual void SetFlashIndicatorLatencyMarker(uint64 FrameNumber) override;`
- L29 _public prototype_ `virtual void SetCustomLatencyMarker(uint32 MarkerId, uint64 FrameNumber) override;`
- L31 _public function_ `virtual float GetTotalLatencyInMs() override`
- L32 _public function_ `virtual float GetGameLatencyInMs() override`
- L33 _public function_ `virtual float GetRenderLatencyInMs() override`
- L34 _public function_ `virtual float GetSimulationLatencyInMs() override`
- L35 _public function_ `virtual float GetRenderSubmitLatencyInMs() override`
- L36 _public function_ `virtual float GetPresentLatencyInMs() override`
- L37 _public function_ `virtual float GetDriverLatencyInMs() override`
- L38 _public function_ `virtual float GetOSRenderQueueLatencyInMs() override`
- L39 _public function_ `virtual float GetGPURenderLatencyInMs() override`
- L40 _public function_ `virtual float GetRenderSubmitOffsetFromFrameStartInMs() override`
- L41 _public function_ `virtual float GetPresentOffsetFromFrameStartInMs() override`
- L42 _public function_ `virtual float GetDriverOffsetFromFrameStartInMs() override`
- L43 _public function_ `virtual float GetOSRenderQueueOffsetFromFrameStartInMs() override`
- L44 _public function_ `virtual float GetGPURenderOffsetFromFrameStartInMs() override`
- L46 _public prototype_ `virtual bool ProcessMessage(HWND hwnd, uint32 msg, WPARAM wParam, LPARAM lParam, int32& OutResult) override;`
- L49 _protected member_ `bool bReflexStatsEnabled = false;`
- L50 _protected member_ `bool bFlashIndicatorEnabled = false;`
