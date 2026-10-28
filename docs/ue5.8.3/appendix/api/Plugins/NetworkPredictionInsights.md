# Plugins / NetworkPredictionInsights

- module root: `Plugins/Runtime/NetworkPredictionInsights/Source/NetworkPredictionInsights`
- headers: 17; symbols: 703
- symbol kinds: class=17, delegate=1, enum=11, enumerator=65, externvar=1, function=137, macro=3, member=266, namespace=7, prototype=162, struct=32, typedef=1
- PrivateDependencyModuleNames: ApplicationCore, AssetRegistry, Core, CoreUObject, EditorFramework, EditorWidgets, Engine, InputCore, Slate, SlateCore, TraceAnalysis, TraceInsights, TraceInsightsCore, TraceLog, TraceServices, UnrealEd

### `Plugins/Runtime/NetworkPredictionInsights/Source/NetworkPredictionInsights/Private/NetworkPredictionAnalyzer.h` (Private)


#### class `FNetworkPredictionAnalyzer`  
`class FNetworkPredictionAnalyzer : public UE::Trace::IAnalyzer`  
_L19-72_
- inherits: `UE::Trace::IAnalyzer`
- L23 _public prototype_ `FNetworkPredictionAnalyzer(TraceServices::IAnalysisSession& InSession, FNetworkPredictionProvider& InNetworkPredictionProvider);`
- L25 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L26 _public prototype_ `virtual void OnAnalysisEnd() override;`
- L27 _public prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L60 _private member_ `TraceServices::IAnalysisSession& Session;`
- L61 _private member_ `FNetworkPredictionProvider& NetworkPredictionProvider;`
- L64 _private member_ `uint64 EngineFrameNumber=0;` — WorldFrame, always from main thread
- L65 _private member_ `float DeltaTimeSeconds;`
- L70 _private member_ `TMap<uint32, FThreadState*> ThreadStatesMap;`
- L71 _private prototype_ `FThreadState& GetThreadState(uint32 ThreadId);`

#### enum `FNetworkPredictionAnalyzer::(anonymous)`  
``  
_L32-57_

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace TraceServices`
- L33 _enumerator_ `RouteId_SimulationScope` (scope `FNetworkPredictionAnalyzer::__anon64e9fbc10103`)
- L34 _enumerator_ `RouteId_SimulationState` (scope `FNetworkPredictionAnalyzer::__anon64e9fbc10103`)
- L35 _enumerator_ `RouteId_SimulationCreated` (scope `FNetworkPredictionAnalyzer::__anon64e9fbc10103`)
- L36 _enumerator_ `RouteId_SimulationConfig` (scope `FNetworkPredictionAnalyzer::__anon64e9fbc10103`)
- L37 _enumerator_ `RouteId_WorldFrameStart` (scope `FNetworkPredictionAnalyzer::__anon64e9fbc10103`)
- L38 _enumerator_ `RouteId_Version` (scope `FNetworkPredictionAnalyzer::__anon64e9fbc10103`)
- L39 _enumerator_ `RouteId_WorldPreInit` (scope `FNetworkPredictionAnalyzer::__anon64e9fbc10103`)
- L40 _enumerator_ `RouteId_PieBegin` (scope `FNetworkPredictionAnalyzer::__anon64e9fbc10103`)
- L41 _enumerator_ `RouteId_SystemFault` (scope `FNetworkPredictionAnalyzer::__anon64e9fbc10103`)
- L42 _enumerator_ `RouteId_Tick` (scope `FNetworkPredictionAnalyzer::__anon64e9fbc10103`)
- L43 _enumerator_ `RouteId_SimTick` (scope `FNetworkPredictionAnalyzer::__anon64e9fbc10103`)
- L44 _enumerator_ `RouteId_InputCmd` (scope `FNetworkPredictionAnalyzer::__anon64e9fbc10103`)
- L45 _enumerator_ `RouteId_SyncState` (scope `FNetworkPredictionAnalyzer::__anon64e9fbc10103`)
- L46 _enumerator_ `RouteId_AuxState` (scope `FNetworkPredictionAnalyzer::__anon64e9fbc10103`)
- L47 _enumerator_ `RouteId_PhysicsState` (scope `FNetworkPredictionAnalyzer::__anon64e9fbc10103`)
- L48 _enumerator_ `RouteId_NetRecv` (scope `FNetworkPredictionAnalyzer::__anon64e9fbc10103`)
- L49 _enumerator_ `RouteId_ShouldReconcile` (scope `FNetworkPredictionAnalyzer::__anon64e9fbc10103`)
- L50 _enumerator_ `RouteId_Reconcile` (scope `FNetworkPredictionAnalyzer::__anon64e9fbc10103`)
- L51 _enumerator_ `RouteId_RollbackInject` (scope `FNetworkPredictionAnalyzer::__anon64e9fbc10103`)
- L52 _enumerator_ `RouteId_PushInputFrame` (scope `FNetworkPredictionAnalyzer::__anon64e9fbc10103`)
- L53 _enumerator_ `RouteId_FixedTickOffset` (scope `FNetworkPredictionAnalyzer::__anon64e9fbc10103`)
- L54 _enumerator_ `RouteId_ProduceInput` (scope `FNetworkPredictionAnalyzer::__anon64e9fbc10103`)
- L55 _enumerator_ `RouteId_BufferedInput` (scope `FNetworkPredictionAnalyzer::__anon64e9fbc10103`)
- L56 _enumerator_ `RouteId_OOBStateMod` (scope `FNetworkPredictionAnalyzer::__anon64e9fbc10103`)

### `Plugins/Runtime/NetworkPredictionInsights/Source/NetworkPredictionInsights/Private/NetworkPredictionInsightsModule.h` (Private)


#### class `FNetworkPredictionInsightsModule`  
`class FNetworkPredictionInsightsModule : public IModuleInterface`  
_L20-38_
- inherits: `IModuleInterface`
- L24 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L25 _public prototype_ `virtual void ShutdownModule() override;`
- L28 _private prototype_ `static void StartNetworkTrace();`
- L30 _private member_ `FNetworkPredictionTraceModule NetworkPredictionTraceModule;`
- L32 _private member_ `FTSTicker::FDelegateHandle TickerHandle;`
- L33 _private member_ `FDelegateHandle StoreServiceHandle;`
- L37 _private member_ `static const FName InsightsTabName;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Trace` (scope `UE`)

### `Plugins/Runtime/NetworkPredictionInsights/Source/NetworkPredictionInsights/Private/NetworkPredictionInsightsStyle.h` (Private)
_(no declarations extracted)_

### `Plugins/Runtime/NetworkPredictionInsights/Source/NetworkPredictionInsights/Private/NetworkPredictionProvider.h` (Private)


#### class `FNetworkPredictionProvider`  
`class FNetworkPredictionProvider : public INetworkPredictionProvider`  
_L9-66_
- inherits: `INetworkPredictionProvider`
- L12 _public member_ `static FName ProviderName;`
- L14 _public prototype_ `FNetworkPredictionProvider(TraceServices::IAnalysisSession& InSession);`
- L17 _public function_ `virtual uint32 GetNetworkPredictionTraceVersion() const override`
- L18 _public function_ `virtual uint64 GetNetworkPredictionDataCounter() const`
- L22 _public function_ `void IncrementDataCounter()`
- L23 _public prototype_ `void SetNetworkPredictionTraceVersion(uint32 Version);`
- L32 _public prototype_ `FSimulationData::FConst& WriteSimulationCreated(int32 TraceID);`
- L33 _public prototype_ `void WriteSimulationTick(int32 TraceID, FSimulationData::FTick&& InTick);`
- L34 _public prototype_ `void WriteNetRecv(int32 TraceID, FSimulationData::FNetSerializeRecv&& InNetRecv);`
- L35 _public prototype_ `void WriteNetCommit(uint32 SimulationId);`
- L36 _public prototype_ `void WriteSystemFault(uint32 SimulationId, uint64 EngineFrameNumber, const TCHAR* Fmt);`
- L37 _public prototype_ `void WriteOOBStateMod(uint32 SimulationId);`
- L38 _public prototype_ `void WriteOOBStateModStr(uint32 SimulationId, const TCHAR* Fmt);`
- L39 _public prototype_ `void WriteProduceInput(uint32 SimulationId);`
- L40 _public prototype_ `void WriteBufferedInput(uint32 SimulationId, int32 NumBufferedInputCmds, bool bFault);`
- L41 _public prototype_ `void WriteSynthInput(uint32 SimulationId);`
- L42 _public prototype_ `void WriteUserState(int32 TraceID, int32 Frame, uint64 EngineFrame, ENP_UserState Type, ENP_UserStateSource UserStateSource, const TCHAR* UserStr);`
- L43 _public prototype_ `void WritePIEStart();`
- L44 _public prototype_ `void WriteReconcileStr(int32 TraceID, const TCHAR* UserStr);`
- L45 _public prototype_ `void WriteReconcile(int32 TraceID, int32 LocalFrameOffset, bool bLocalOffsetFrameChanged);`
- L47 _public prototype_ `void WriteSimulationConfig(int32 TraceID, uint64 EngineFrame, ENP_NetRole NetRole, bool bHasNetConnection, ENP_TickingPolicy TickingPolicy, ENP_NetworkLOD NetworkLOD, int32 ServiceMask);`
- L49 _public function_ `virtual TArrayView<const TSharedRef<FSimulationData>> ReadSimulationData() const override`
- L56 _private prototype_ `TSharedRef<FSimulationData>& FindOrAdd(int32 TraceID);`
- L57 _private prototype_ `TSharedRef<FSimulationData>& FindChecked(int32 TraceID);`
- L60 _private member_ `TArray<TSharedRef<FSimulationData>> ProviderData;` — Array that stores all of our traced simulation data
- L62 _private member_ `uint64 DataCounter = 0;`
- L63 _private member_ `uint32 NetworkPredictionTraceVersion = 0;`
- L64 _private member_ `int32 PIESessionCounter = 0;`
- L65 _private member_ `TraceServices::IAnalysisSession& Session;`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace TraceServices`

### `Plugins/Runtime/NetworkPredictionInsights/Source/NetworkPredictionInsights/Private/NetworkPredictionTraceModule.h` (Private)


#### class `FNetworkPredictionTraceModule`  
`class FNetworkPredictionTraceModule : public TraceServices::IModule`  
_L9-21_
- inherits: `TraceServices::IModule`
- L13 _public prototype_ `virtual void GetModuleInfo(TraceServices::FModuleInfo& OutModuleInfo) override;` — TraceServices::IModule interface
- L14 _public prototype_ `virtual void OnAnalysisBegin(TraceServices::IAnalysisSession& Session) override;`
- L15 _public prototype_ `virtual void GetLoggers(TArray<const TCHAR *>& OutLoggers) override;`
- L16 _public prototype_ `virtual void GenerateReports(const TraceServices::IAnalysisSession& Session, const TCHAR* CmdLine, const TCHAR* OutputDirectory) override;`
- L17 _public function_ `virtual const TCHAR* GetCommandLineArgument() override`
- L20 _private member_ `static FName ModuleName;`

### `Plugins/Runtime/NetworkPredictionInsights/Source/NetworkPredictionInsights/Private/UI/NPAxisViewportDouble.h` (Private)


#### class `FNPAxisViewportDouble`  
`class FNPAxisViewportDouble`  
_L13-191_
- L16 _private member_ `static constexpr float SLATE_UNITS_TOLERANCE = 0.1f;`
- L19 _public function_ `FNPAxisViewportDouble()`
- L24 _public function_ `void Reset()`
- L40 _public function_ `FString ToDebugString(const TCHAR* Sufix) const`
- L49 _public function_ `float GetSize() const` — Size of viewport, in pixels (Slate units). The viewport's width if this is a horizontal axis or the viewport's height if this is a vertical axis.
- L50 _public prototype_ `bool SetSize(const float InSize);`
- L52 _public function_ `int32 GetMinValue() const`
- L53 _public function_ `int32 GetMaxValue() const`
- L55 _public function_ `float GetMinPos() const`
- L56 _public function_ `float GetMaxPos() const`
- L57 _public function_ `float GetPos() const`
- L59 _public function_ `double GetMinScale() const`
- L60 _public function_ `double GetMaxScale() const`
- L63 _public function_ `double GetScale() const` — Current scale factor between Value units and Slate units (pixels), in pixels per value. [px/value_unit]
- L65 _public function_ `void SetMinMaxValueInterval(const double InMinValue, const double InMaxValue)`
- L72 _public function_ `double GetValueAtPos(const float Pos) const`
- L77 _public function_ `double GetValueAtOffset(const float Offset) const`
- L82 _public function_ `float GetPosForValue(const double Value) const`
- L87 _public function_ `float GetOffsetForValue(const double Value) const`
- L92 _public function_ `float GetRoundedOffsetForValue(const double Value) const`
- L97 _public function_ `bool ScrollAtPos(const float Pos)`
- L108 _public function_ `bool ScrollAtValue(const double Value)`
- L113 _public function_ `bool CenterOnValue(const double Value)`
- L118 _public function_ `bool CenterOnValueInterval(const double IntervalStartValue, const double IntervalEndValue)`
- L131 _public function_ `void SetScaleLimits(const double InMinScale, const double InMaxScale)`
- L137 _public prototype_ `bool SetScale(const double NewScale);`
- L138 _public prototype_ `bool ZoomWithFixedOffset(const double NewScale, const float Offset);`
- L139 _public prototype_ `bool RelativeZoomWithFixedOffset(const float Delta, const float Offset);`
- L141 _public prototype_ `void GetScrollLimits(float& OutMinPos, float& OutMaxPos);`
- L142 _public prototype_ `bool EnforceScrollLimits(const float InMinPos, const float InMaxPos, const float InterpolationFactor);`
- L143 _public prototype_ `bool UpdatePosWithinLimits();`
- L145 _public prototype_ `void OnUserScrolled(TSharedPtr<SScrollBar> ScrollBar, float ScrollOffset);`
- L146 _public prototype_ `void UpdateScrollBar(TSharedPtr<SScrollBar> ScrollBar) const;`
- L149 _private function_ `void OnSizeChanged()`
- L153 _private function_ `void OnPositionChanged()`
- L157 _private function_ `void OnScaleChanged()`
- L162 _private function_ `void UpdateMinMax()`
- L176 _private member_ `float Size;` — size of viewport, in pixels (Slate units); [px]
- L178 _private member_ `double MinValue;` — minimum value (inclusive); [value_unit]
- L179 _private member_ `double MaxValue;` — maximum value (exclusive); [value_unit]
- L184 _private member_ `float MinPosition;` — minimum position (corresponding to MinValue), in pixels (Slate units); [px]
- L185 _private member_ `float MaxPosition;` — maximum position (corresponding to MaxValue), in pixels (Slate units); [px]
- L186 _private member_ `float Position;` — current position of the viewport, in pixels (Slate units); [px]
- L188 _private member_ `double MinScale;` — minimum scale factor; [px/value_unit]
- L189 _private member_ `double MaxScale;` — maximum scale factor; [px/value_unit]
- L190 _private member_ `double Scale;` — current scale factor between Value units and Slate units (pixels); [px/value_unit]

### `Plugins/Runtime/NetworkPredictionInsights/Source/NetworkPredictionInsights/Private/UI/NPAxisViewportInt32.h` (Private)


#### class `FNPAxisViewportInt32`  
`class FNPAxisViewportInt32`  
_L13-209_
- L16 _private member_ `static constexpr float SLATE_UNITS_TOLERANCE = 0.1f;`
- L19 _public function_ `FNPAxisViewportInt32()`
- L24 _public function_ `void Reset()`
- L40 _public function_ `FString ToDebugString(const TCHAR* Sufix, const TCHAR* Unit) const`
- L58 _public function_ `float GetSize() const` — Size of viewport, in pixels (Slate units). The viewport's width if this is a horizontal axis or the viewport's height if this is a vertical axis.
- L59 _public prototype_ `bool SetSize(const float InSize);`
- L61 _public function_ `int32 GetMinValue() const`
- L62 _public function_ `int32 GetMaxValue() const`
- L64 _public function_ `float GetMinPos() const`
- L65 _public function_ `float GetMaxPos() const`
- L66 _public function_ `float GetPos() const`
- L68 _public function_ `float GetMinScale() const`
- L69 _public function_ `float GetMaxScale() const`
- L75 _public function_ `float GetScale() const` — Current scale factor between Value units (samples) and Slate units (pixels), in pixels per sample. [px/sample] If Scale > 1, it represents number of pixels for one sample, otherwise, the inverse of Scale represents number of samples in one pixel.
- L78 _public function_ `float GetSampleSize() const` — Returns the number of pixels (Slate units) for one viewport sample. [px]
- L81 _public function_ `int32 GetNumSamplesPerPixel() const` — Returns the number of samples in one pixel (Slate unit). [sample]
- L83 _public function_ `void SetMinMaxInterval(const int32 InMinValue, const int32 InMaxValue)`
- L90 _public function_ `int32 GetValueAtPos(const float Pos) const`
- L95 _public function_ `int32 GetValueAtOffset(const float Offset) const`
- L100 _public function_ `float GetPosForValue(const int32 Value) const`
- L105 _public function_ `float GetOffsetForValue(const int32 Value) const`
- L110 _public function_ `float GetRoundedOffsetForValue(const int32 Value) const`
- L115 _public function_ `bool ScrollAtPos(const float Pos)`
- L126 _public function_ `bool ScrollAtValue(const int32 Value)`
- L131 _public function_ `bool CenterOnValue(const int32 Value)`
- L136 _public function_ `bool CenterOnValueInterval(const int32 IntervalStartValue, const int32 IntervalEndValue)`
- L149 _public function_ `void SetScaleLimits(const float InMinScale, const float InMaxScale)`
- L155 _public prototype_ `bool SetScale(const float NewScale);`
- L156 _public prototype_ `bool ZoomWithFixedOffset(const float NewScale, const float Offset);`
- L157 _public prototype_ `bool RelativeZoomWithFixedOffset(const float Delta, const float Offset);`
- L159 _public prototype_ `void GetScrollLimits(float& OutMinPos, float& OutMaxPos);`
- L160 _public prototype_ `bool EnforceScrollLimits(const float InMinPos, const float InMaxPos, const float InterpolationFactor);`
- L161 _public prototype_ `bool UpdatePosWithinLimits();`
- L163 _public prototype_ `void OnUserScrolled(TSharedPtr<SScrollBar> ScrollBar, float ScrollOffset);`
- L164 _public prototype_ `void UpdateScrollBar(TSharedPtr<SScrollBar> ScrollBar) const;`
- L167 _private function_ `void OnSizeChanged()`
- L171 _private function_ `void OnPositionChanged()`
- L175 _private function_ `void OnScaleChanged()`
- L180 _private function_ `void UpdateMinMax()`
- L194 _private member_ `float Size;` — size of viewport (ex.: the viewport's width if this is a horizontal axis), in pixels (Slate units); [px]
- L196 _private member_ `int32 MinValue;` — minimum value (inclusive); [sample]
- L197 _private member_ `int32 MaxValue;` — maximum value (exclusive); [sample]
- L202 _private member_ `float MinPosition;` — minimum position (corresponding to MinValue), in pixels (Slate units); [px]
- L203 _private member_ `float MaxPosition;` — maximum position (corresponding to MaxValue), in pixels (Slate units); [px]
- L204 _private member_ `float Position;` — current position of the viewport, in pixels (Slate units); [px]
- L206 _private member_ `float MinScale;` — minimum scale factor; [px/sample]
- L207 _private member_ `float MaxScale;` — maximum scale factor; [px/sample]
- L208 _private member_ `float Scale;` — current scale factor between Value units (samples) and Slate units (pixels); [px/sample]

### `Plugins/Runtime/NetworkPredictionInsights/Source/NetworkPredictionInsights/Private/UI/NetworkPredictionDrawHelpers.h` (Private)


#### class `FNetworkPredictionDrawHelpers`  
`class FNetworkPredictionDrawHelpers`  
_L11-55_
- L23 _public prototype_ `static void DrawBackground(const FDrawContext& DrawContext, const FSlateBrush* BackgroundAreaBrush, const FLinearColor& ValidAreaColor, const FLinearColor& InvalidAreaColor, const FLinearColor& EdgeColor, const float X0, const float X1, const float X2, const float X3, const float X4, const float Y, const float H, float& OutValidAreaX, float& OutValidAreaW);` — Draw background. X1-X2 specifies the valid area. X0-X1 and X2-X3 specifies the invalid areas. X0    X1    X2     X3 ++++++|*****|++++++ ++++++|*****|++++++ ++++++|*****|++++++
- L38 _public prototype_ `static void DrawBackground( const FDrawContext& DrawContext, const FSlateBrush* BackgroundAreaBrush, const float X0, const float X1, const float X2, const float X3, const float X4, const float Y, const float H);`
- L48 _public prototype_ `static void DrawFutureBackground ( const FDrawContext& DrawContext, const FSlateBrush* BackgroundAreaBrush, const FLinearColor& Color, const float X0, const float X1, const float Y, const float H);`

### `Plugins/Runtime/NetworkPredictionInsights/Source/NetworkPredictionInsights/Private/UI/NetworkPredictionInsightsActionManager.h` (Private)


#### class `FNetworkPredictionInsightsActionManager`  
`class FNetworkPredictionInsightsActionManager`  
_L10-42_
- desc: Class that provides helper functions for the commands to avoid cluttering profiler manager with many small functions. Can't contain any variables. Directly operates on the profiler manager instance.
- L16 _private function_ `FNetworkPredictionInsightsActionManager(class FNetworkPredictionInsightsManager* Instance) : This(Instance)` — Private constructor.
- L41 _protected member_ `class FNetworkPredictionInsightsManager* This;` — Reference to the global instance of the profiler manager.

#### Free symbols / members of external scopes

- L23 _macro_ `#define DECLARE_TOGGLE_COMMAND(CmdName)\`

### `Plugins/Runtime/NetworkPredictionInsights/Source/NetworkPredictionInsights/Private/UI/NetworkPredictionInsightsCommands.h` (Private)


#### class `FNetworkPredictionInsightsCommands`  
`class FNetworkPredictionInsightsCommands : public TCommands<FNetworkPredictionInsightsCommands>`  
_L9-34_
- inherits: `TCommands<FNetworkPredictionInsightsCommands>`
- L13 _public prototype_ `FNetworkPredictionInsightsCommands();` — Default constructor.
- L16 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands.
- L26 _public member_ `TSharedPtr<FUICommandInfo> ToggleAutoScrollSimulationFrames;`
- L27 _public member_ `TSharedPtr<FUICommandInfo> ToggleCompactView;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> NextEngineFrame;`
- L31 _public member_ `TSharedPtr<FUICommandInfo> PrevEngineFrame;`
- L32 _public member_ `TSharedPtr<FUICommandInfo> FirstEngineFrame;`
- L33 _public member_ `TSharedPtr<FUICommandInfo> LastEngineFrame;`

### `Plugins/Runtime/NetworkPredictionInsights/Source/NetworkPredictionInsights/Private/UI/NetworkPredictionInsightsManager.h` (Private)


#### class `FNetworkPredictionInsightsManager`  
`class FNetworkPredictionInsightsManager : public TSharedFromThis<FNetworkPredictionInsightsManager>`  
_L13-103_
- inherits: `TSharedFromThis<FNetworkPredictionInsightsManager>`
- desc: This class manages the Networking Profiler state and settings.
- L19 _public prototype_ `FNetworkPredictionInsightsManager();` — Creates the Networking Profiler (Networking Insights) manager, only one instance can exist.
- L22 _public prototype_ `virtual ~FNetworkPredictionInsightsManager();` — Virtual destructor.
- L25 _public function_ `static TSharedPtr<FNetworkPredictionInsightsManager> Initialize()` — Creates an instance of the profiler manager.
- L39 _public function_ `void Shutdown()` — Shutdowns the Networking Profiler manager.
- L46 _protected prototype_ `void PostConstructor();` — Finishes initialization of the profiler manager.
- L49 _protected prototype_ `void BindCommands();` — Binds our UI commands to delegates.
- L56 _public prototype_ `static TSharedPtr<FNetworkPredictionInsightsManager> Get();` — @return the global instance of the Network Prediction Insights manager. This is an internal singleton and cannot be used outside NetworkPredictionInsights module.
- L62 _public prototype_ `static const class FNetworkPredictionInsightsCommands& GetCommands();` — @return an instance of the Networking Profiler commands.
- L65 _public prototype_ `static FNetworkPredictionInsightsActionManager& GetActionManager();` — @return an instance of the Networking Profiler action manager.
- L67 _public prototype_ `void AddProfilerWindow(const TSharedRef<SNPWindow>& InWindow);`
- L69 _public prototype_ `void RemoveProfilerWindow(const TSharedRef<SNPWindow>& InWindow);`
- L75 _public prototype_ `TSharedPtr<class SNPWindow> GetProfilerWindow(int32 Index) const;` — Converts profiler window weak pointer to a shared pointer and returns it. Make sure the returned pointer is valid before trying to dereference it.
- L79 _public prototype_ `void OnSessionChanged();`
- L83 _protected prototype_ `bool Tick(float DeltaTime);` — Updates this manager, done through FCoreTicker.
- L87 _protected member_ `FTickerDelegate OnTick;` — The delegate to be invoked when this manager ticks.
- L90 _protected member_ `FDelegateHandle OnTickHandle;` — Handle to the registered OnTick.
- L96 _protected member_ `FNetworkPredictionInsightsActionManager ActionManager;` — An instance of the Networking Profiler action manager.
- L99 _protected member_ `TArray<TWeakPtr<class SNPWindow>> NetworkPredictionInsightsWindows;` — A list of weak pointers to the Networking Profiler windows.
- L102 _protected member_ `static TSharedPtr<FNetworkPredictionInsightsManager> Instance;` — A shared pointer to the global instance of the profiler manager.

### `Plugins/Runtime/NetworkPredictionInsights/Source/NetworkPredictionInsights/Private/UI/SNPSimFrameContents.h` (Private)


#### class `SNPSimFrameContents`  
`class SNPSimFrameContents : public SCompoundWidget`  
_L14-41_
- inherits: `SCompoundWidget`
- L18 _public prototype_ `SNPSimFrameContents();`
- L19 _public prototype_ `virtual ~SNPSimFrameContents();`
- L21 _public prototype_ `void Reset();`
- L23 _public function_ `SLATE_BEGIN_ARGS(SNPSimFrameContents)`
- L24 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<SNPWindow> InNPWindow);`
- L28 _public prototype_ `void NotifyContentClicked(const FSimContentsView& InView);`
- L30 _public member_ `TSharedPtr<SHorizontalBox> ContentsHBoxPtr;`
- L31 _public member_ `TSharedPtr<SVerticalBox> SystemFaultsVBoxPtr;`
- L33 _public member_ `TSharedPtr<STextBlock> SimInfoTextBlock;`
- L34 _public member_ `TSharedPtr<STextBlock> SimTickTextBlock;`
- L36 _public member_ `TSharedPtr<STextBlock> InputCmdTextBlock;`
- L37 _public member_ `TSharedPtr<STextBlock> SyncStateTextBlock;`
- L38 _public member_ `TSharedPtr<STextBlock> AuxStateTextBlock;`
- L40 _public member_ `TSharedPtr<SNPWindow> NPWindow;`

### `Plugins/Runtime/NetworkPredictionInsights/Source/NetworkPredictionInsights/Private/UI/SNPSimFrameView.h` (Private)


#### enum `ESimFrameStatus`  
`enum class ESimFrameStatus : uint8`  
_L14-21_
- L16 _public enumerator_ `Predicted` — A predicted frame that has not been rolled back or confirmed in any way
- L17 _public enumerator_ `Repredicted` — Sim was rolled back to a point prior to this frame, and we repredicted this frame to *catch back up* to where we were
- L18 _public enumerator_ `Confirmed` — We received authoratative state > that this frame and didn't rollback/reconcile
- L19 _public enumerator_ `Trashed` — Frame that was thrown out: we rolled the sim back and ticked Repredicted frames past this one.
- L20 _public enumerator_ `Abandoned` — The sim was skipped ahead by receiving authoritative state: this frame was never used as input into the next frame

#### struct `FSimulationTrack`  
`struct FSimulationTrack`  
_L35-101_
- L91 _public member_ `TSharedRef<FSimulationData::FRestrictedView> View;`
- L93 _public member_ `float Y;`
- L94 _public member_ `float ValueY;` — untransformed by viewport/scrolling value
- L95 _public member_ `FString DisplayString;`
- L96 _public member_ `TArray<FSubTrack> SubTracks;`
- L99 _public member_ `TArray<FSubTrack::FNetRecvSource> OrphanedNetRecvSourceList;` — Orphaned Recvs don't map to a specific subtrack.
- L100 _public member_ `TArray<FSubTrack::FDrawNetRecv> OrphanedDrawNetRecvList;`

#### struct `FSimulationTrack::FSubTrack`  
`struct FSubTrack`  
_L39-89_
- desc: Processed Data about subtracks: this will indicate overlapping simulation steps essentially, how we increase the Y size of the track in the UI
- L78 _public member_ `TArray<FTickSource> TickSourceList;` — All ticks that belong to this track. These are not culled wrt the viewport
- L79 _public member_ `TArray<FNetRecvSource> NetRecvSourceList;`
- L80 _public member_ `int32 PrevMS = TNumericLimits<int32>::Min();`
- L83 _public member_ `TArray<FDrawTick> DrawTickList;` — These are the actual draw lists that get flung over to ::DrawCached
- L84 _public member_ `TArray<FDrawNetRecv> DrawNetRecvList;`
- L86 _public member_ `float ValueY=0.f;` — untransformed by viewport/scrolling value
- L87 _public member_ `float Y=0.f;`
- L88 _public member_ `float H=0.f;`

#### struct `FSimulationTrack::FSubTrack::FTickSource`  
`struct FTickSource`  
_L41-51_
- L43 _public member_ `const FSimulationData::FTick& Tick;`
- L44 _public member_ `const FSimTime OffsetStartMS;`
- L45 _public member_ `const FSimTime OffsetEndMS;`
- L46 _public member_ `const bool bDesaturate;`
- L47 _public member_ `const bool bPulse;`
- L48 _public member_ `const bool bSelected;`
- L49 _public member_ `const bool bSearchHighlighted;`
- L50 _public member_ `const ESimFrameStatus Status;`

#### struct `FSimulationTrack::FSubTrack::FNetRecvSource`  
`struct FNetRecvSource`  
_L53-60_
- L55 _public member_ `const FSimulationData::FNetSerializeRecv& NetRecv;`
- L56 _public member_ `const FSimTime OffsetNetMS;`
- L57 _public member_ `const bool bPulse;`
- L58 _public member_ `const bool bSelected;`
- L59 _public member_ `const bool bSearchHighlighted;`

#### struct `FSimulationTrack::FSubTrack::FDrawTick`  
`struct FDrawTick`  
_L62-67_
- L64 _public member_ `const float X;`
- L65 _public member_ `const float W;`
- L66 _public member_ `const FTickSource& Source;`

#### struct `FSimulationTrack::FSubTrack::FDrawNetRecv`  
`struct FDrawNetRecv`  
_L69-75_
- L71 _public function_ `static constexpr float W()`
- L73 _public member_ `float X;`
- L74 _public member_ `const FNetRecvSource& Source;`

#### struct `FSimulationActorGroup`  
`struct FSimulationActorGroup`  
_L103-124_
- L105 _public member_ `FSimNetActorID ID;`
- L107 _public member_ `FString DebugName;`
- L108 _public member_ `FName GroupName;`
- L109 _public member_ `bool bHasAutoProxy;` — Is there an auto proxy sim in this group
- L111 _public member_ `uint64 MaxEngineFrame = 0;` — Engine frame number of last simulation frame amonst all simulations for this actor
- L112 _public member_ `FSimTime MaxAllowedSimTime = 0;`
- L114 _public member_ `FSimTime OffsetSimTimeMS;` — How much to offset this group when drawing anything on the sim timeline
- L116 _public member_ `TArray<FSimulationTrack> SimulationTracks;`
- L119 _public member_ `FString DisplayString;` — Rendering Data. Only filled out if being drawn
- L120 _public member_ `float Y;`
- L121 _public member_ `float H;`
- L123 _public member_ `float ValueY;` — untransformed by viewport/scrolling value

#### enum `ESimFrameContentType`  
`enum ESimFrameContentType`  
_L126-130_
- L128 _public enumerator_ `FrameNumber`
- L129 _public enumerator_ `NumBufferedInputCmds`

#### struct `FSimulationFrameView`  
`struct FSimulationFrameView`  
_L133-146_
- desc: The overall processed data that the Simulation Frame Widget uses to draw
- L135 _public function_ `void Reset()`
- L141 _public member_ `uint64 HeadEngineFrame = 0;`
- L142 _public member_ `FSimTime PresentableTimeMS = 0;` — The "current" time that everything is anchored around
- L143 _public member_ `TArray<FSimulationActorGroup> ActorGroups;`
- L145 _public member_ `ESimFrameContentType ContentType = ESimFrameContentType::FrameNumber;`

#### struct `FSimFrameHoverView`  
`struct FSimFrameHoverView`  
_L149-163_
- desc: Cached data about what we are hovering over
- L151 _public member_ `const FSimulationData::FTick* Tick = nullptr;`
- L152 _public member_ `const FSimulationData::FNetSerializeRecv* NetRecv = nullptr;`
- L153 _public member_ `FSimTime X = 0;`
- L154 _public member_ `FSimTime Y = 0;`
- L156 _public function_ `void Reset()`

#### class `FSimFrameViewport`  
`class FSimFrameViewport`  
_L170-231_
- desc: Viewport that is simulation frame based (not real time!)
- L173 _private member_ `static constexpr float SLATE_UNITS_TOLERANCE = 0.1f;`
- L176 _public function_ `FSimFrameViewport()`
- L181 _public function_ `void Reset()`
- L187 _public function_ `const FNPAxisViewportInt32& GetHorizontalAxisViewport() const`
- L188 _public function_ `FNPAxisViewportInt32& GetHorizontalAxisViewport()`
- L190 _public function_ `const FNPAxisViewportDouble& GetVerticalAxisViewport() const`
- L191 _public function_ `FNPAxisViewportDouble& GetVerticalAxisViewport()`
- L193 _public function_ `float GetWidth() const`
- L194 _public function_ `float GetHeight() const`
- L196 _public function_ `bool SetSize(const float InWidth, const float InHeight)`
- L208 _public function_ `float GetSampleWidth() const`
- L209 _public function_ `int32 GetNumFramesPerSample() const`
- L210 _public function_ `int32 GetFirstFrameIndex() const`
- L212 _public function_ `float GetContentStartY() const` — GetVerticalAxisViewport().GetSize() - 1.f; }
- L213 _public function_ `float GetTrackPadding() const`
- L214 _public function_ `float GetSubTrackHeight() const`
- L224 _private function_ `void OnSizeChanged()`
- L229 _private member_ `FNPAxisViewportInt32 HorizontalAxisViewport;`
- L230 _private member_ `FNPAxisViewportDouble VerticalAxisViewport;`

#### class `FSimFrameViewDrawHelper`  
`class FSimFrameViewDrawHelper`  
_L235-283_
- L246 _public prototype_ `explicit FSimFrameViewDrawHelper(const FDrawContext& InDrawContext, const FSimFrameViewport& InViewport);`
- L251 _public prototype_ `FSimFrameViewDrawHelper(const FSimFrameViewDrawHelper&) = delete;` — Non-copyable
- L252 _public prototype_ `FSimFrameViewDrawHelper& operator=(const FSimFrameViewDrawHelper&) = delete;`
- L254 _public prototype_ `void DrawBackground(FSimTime PresentableLine) const;`
- L255 _public prototype_ `void DrawCached(const FSimulationFrameView& View, float MinY) const;`
- L257 _public prototype_ `FLinearColor GetFramColorByStatus(ESimFrameStatus Status, const bool bDesaturate) const;`
- L258 _public prototype_ `FLinearColor GetRecvColorByStatus(ENetSerializeRecvStatus Status) const;`
- L272 _private member_ `const FDrawContext& DrawContext;`
- L273 _private member_ `const FSimFrameViewport& Viewport;`
- L275 _private member_ `const FSlateBrush* WhiteBrush;`
- L276 _private member_ `const FSlateBrush* HoveredEventBorderBrush;`
- L277 _private member_ `const FSlateBrush* SelectedEventBorderBrush;`
- L278 _private member_ `const FSlateFontInfo SelectionFont;`
- L281 _private member_ `mutable int32 NumFrames = 0;` — Debug stats.
- L282 _private member_ `mutable int32 NumDrawSamples = 0;`

#### enum `FSimFrameViewDrawHelper::EHighlightMode`  
`enum class EHighlightMode : uint32`  
_L238-243_
- L240 _public enumerator_ `Hovered = 1`
- L241 _public enumerator_ `Selected = 2`
- L242 _public enumerator_ `SelectedAndHovered = 3`

#### class `SNPSimFrameView`  
`class SNPSimFrameView : public SCompoundWidget`  
_L288-464_
- inherits: `SCompoundWidget`
- L293 _public member_ `static constexpr float MOUSE_SNAP_DISTANCE = 2.0f;` — Number of pixels.
- L303 _public prototype_ `SNPSimFrameView();`
- L304 _public prototype_ `virtual ~SNPSimFrameView();`
- L306 _public function_ `SLATE_BEGIN_ARGS(SNPSimFrameView)`
- L310 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<SNPWindow> InNetworkPredictionWindow);`
- L314 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L316 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L317 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L318 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L319 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L320 _public prototype_ `virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L321 _public prototype_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;`
- L322 _public prototype_ `virtual FReply OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L324 _public prototype_ `virtual void DrawHorizontalAxisGrid(FDrawContext& DrawContext, const FSlateBrush* Brush, const FSlateFontInfo& Font) const;`
- L326 _public function_ `const FSimFrameViewport& GetViewport() const`
- L327 _public function_ `const FVector2D& GetMousePosition() const`
- L329 _public function_ `bool GetAutoScroll() const`
- L330 _public prototype_ `void SetAutoScroll(bool bIn);`
- L331 _public prototype_ `void SetAutoScrollDirty();`
- L333 _public member_ `static float PulsePCT;`
- L335 _public prototype_ `void OnGetOptionsMenu(FMenuBuilder& Builder);`
- L337 _public prototype_ `void SearchUserData(const FText& InFilterText);`
- L341 _private prototype_ `void Reset();`
- L342 _private prototype_ `void UpdateState();`
- L343 _private prototype_ `void BuildSimulationView_ActorGroups(const struct FFilteredDataCollection& FilteredDataCollection);`
- L344 _private prototype_ `void BuildSimulationView_Tracks();`
- L347 _private prototype_ `void UpdateDraw();`
- L349 _private prototype_ `void HorizontalScrollBar_OnUserScrolled(float ScrollOffset);`
- L350 _private prototype_ `void VerticalScrollBar_OnUserScrolled(float ScrollOffset);`
- L351 _private prototype_ `void UpdateHorizontalScrollBar();`
- L352 _private prototype_ `void UpdateVerticalScrollBar();`
- L353 _private prototype_ `void OnUserScroll();`
- L355 _private prototype_ `void ZoomHorizontally(const float Delta, const float X);`
- L380 _private prototype_ `FMouseOverInfo GetMouseOverInfo(FVector2D InMousePosition) const;`
- L383 _private member_ `TSharedPtr<SNPWindow> NetworkPredictionWindow;`
- L386 _private member_ `FSimFrameViewport Viewport;` — The track's viewport. Encapsulates info about position and scale.
- L387 _private member_ `bool bIsViewportDirty = false;`
- L390 _private member_ `TSharedPtr<SScrollBar> HorizontalScrollBar;` — The slot that contains this widget's descendants.
- L391 _private member_ `TSharedPtr<SScrollBar> VerticalScrollBar;`
- L393 _private member_ `bool bIsStateDirty = false;` — What we want to draw has changed: underlying analyzed data or filtering/settings.
- L394 _private member_ `bool bIsDrawDirty = false;` — What we need to draw (may) have changed: scrolling, viewport changes etc can trigger this as well.
- L396 _private member_ `bool bAutoScroll = true;` — User wants to auto scroll
- L397 _private member_ `bool bAutoScrollDirty = false;` — We need to update our view to scroll to latest
- L399 _private member_ `class IUnrealInsightsModule* InsightsModule;`
- L405 _private member_ `FVector2D MousePosition;` — The current mouse position.
- L408 _private member_ `FVector2D MousePositionOnButtonDown;` — Mouse position during the call on mouse button down.
- L409 _private member_ `float ViewportPosXOnButtonDown;`
- L410 _private member_ `float ViewportPosYOnButtonDown;`
- L413 _private member_ `FVector2D MousePositionOnButtonUp;` — Mouse position during the call on mouse button up.
- L415 _private member_ `bool bIsLMB_Pressed = false;`
- L416 _private member_ `bool bIsRMB_Pressed = false;`
- L419 _private member_ `bool bIsScrolling = false;` — True, if the user is currently interactively scrolling the view (ex.: by holding the left mouse button and dragging).
- L424 _private member_ `FGeometry ThisGeometry;`
- L427 _private member_ `ECursorType CursorType;` — Cursor type.
- L429 _private member_ `FSimulationFrameView SimulationFrameView;`
- L431 _private member_ `FSimFrameHoverView HoverView;`
- L433 _private member_ `mutable float TooltipOpacity = 0.f;`
- L434 _private member_ `float PulseAccumulator=0;`
- L436 _private function_ `bool CompactSimFrameView() const`
- L437 _private function_ `bool LinearSimFrameView() const`
- L439 _private function_ `void ToggleCompactSimFrameView()`
- L440 _private function_ `void ToggleLinearSimFrameview()`
- L442 _private member_ `bool bCompactSimFrameView = false;`
- L443 _private member_ `bool bLinearSimFrameView = true;`
- L445 _private member_ `FSimTime ViewportMaxSimTimeMS = 0;`
- L446 _private member_ `FSimTime ViewportMinSimTimeMS = 0;`
- L447 _private member_ `float ViewportYMaxValue = 0.f;`
- L448 _private member_ `float ViewportYContentStartValue = 30.f;`
- L450 _private member_ `FString UserStateSearchString;`
- L451 _private prototype_ `bool PerformSearch(const FSimulationData::FTick&, const FSimulationData::FRestrictedView& SimView);`
- L452 _private prototype_ `bool PerformSearch(const FSimulationData::FNetSerializeRecv&, const FSimulationData::FRestrictedView& SimView);`
- L453 _private prototype_ `bool PerformSearchInternal(const TArrayView<const FSimulationData::FUserState* const>& UserStates);`
- L455 _private prototype_ `void SortActorGroupToTop(const FSimulationActorGroup* Group);`
- L457 _private member_ `TArray<FSimNetActorID> UserSortedNetActors;`
- L459 _private function_ `bool IsFrameContentView_FrameNumber() const`
- L460 _private function_ `bool IsFrameContentView_BufferedInputCmds() const`
- L462 _private function_ `void SetFrameContentView_FrameNumber()`
- L463 _private function_ `void SetFrameContentView_NumBufferdInputCmds()`

#### enum `SNPSimFrameView::ECursorType`  
`enum class ECursorType`  
_L295-300_
- L297 _public enumerator_ `Default`
- L298 _public enumerator_ `Arrow`
- L299 _public enumerator_ `Hand`

#### struct `SNPSimFrameView::FMouseOverInfo`  
`struct FMouseOverInfo`  
_L357-378_
- L359 _public member_ `const FSimulationActorGroup* Group = nullptr;`
- L360 _public member_ `const FSimulationTrack* Track = nullptr;`
- L361 _public member_ `const FSimulationTrack::FSubTrack* SubTrack = nullptr;`
- L362 _public member_ `const FSimulationTrack::FSubTrack::FDrawNetRecv* DrawNetRecv = nullptr;`
- L363 _public member_ `const FSimulationTrack::FSubTrack::FDrawTick* DrawSimTick = nullptr;`
- L365 _public function_ `const FSimulationData::FNetSerializeRecv* GetNetRecv(uint64 MaxEngineFrame)`

### `Plugins/Runtime/NetworkPredictionInsights/Source/NetworkPredictionInsights/Private/UI/SNPToolbar.h` (Private)


#### class `SNPToolbar`  
`class SNPToolbar : public SCompoundWidget`  
_L13-39_
- inherits: `SCompoundWidget`
- L17 _public prototype_ `SNPToolbar();` — Default constructor.
- L20 _public prototype_ `virtual ~SNPToolbar();` — Virtual destructor.
- L22 _public function_ `SLATE_BEGIN_ARGS(SNPToolbar)`
- L23 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<SNPWindow> InProfilerWindow);`
- L33 _private member_ `TSharedPtr<SNPWindow> ParentWindow;`
- L35 _private prototype_ `TSharedRef<SWidget> OnGetOptionsMenu();`
- L37 _private member_ `TSharedPtr<SComboBox<TSharedPtr<int32>>> PIESessionComboBox;`

### `Plugins/Runtime/NetworkPredictionInsights/Source/NetworkPredictionInsights/Private/UI/SNPWindow.h` (Private)


#### struct `FNetworkPredictionInsightsTabs`  
`struct FNetworkPredictionInsightsTabs`  
_L28-34_
- L31 _public member_ `static const FName ToolbarID;` — Tab identifiers
- L32 _public member_ `static const FName SimFrameViewID;`
- L33 _public member_ `static const FName SimFrameContentsID;`

#### struct `FNPFilter`  
`struct FNPFilter`  
_L60-64_
- L62 _public member_ `uint64 MinEngineFrame=0;` — Inclusive (0 = "start at frame 0")
- L63 _public member_ `uint64 MaxEngineFrame=0;` — 0 = open ended. Otherwise, exclusive (1 = "only frame 0")

#### struct `FNPUnfilteredDataView`  
`struct FNPUnfilteredDataView`  
_L67-71_
- desc: Some cached values about our data that is not filtered
- L69 _public member_ `uint64 FirstEngineFrame = 0;` — First Engine frame that had NP data
- L70 _public member_ `uint64 LastEngineFrame = 0;` — Last engine frame that had NP data

#### struct `FFilter`  
`struct FFilter`  
_L78-82_
- L80 _public member_ `uint64 MinEngineFrame=0;` — Inclusive (0 = "start at frame 0")
- L81 _public member_ `uint64 MaxEngineFrame=0;` — 0 = open ended. Otherwise, exclusive (1 = "only frame 0")

#### struct `FFilteredDataCollection`  
`struct FFilteredDataCollection`  
_L85-91_
- desc: This is the main data structure that is passed into the various widgets. Widgets should avoid reading directly from the provider API
- L87 _public member_ `TArray<TSharedRef<FSimulationData::FRestrictedView>> Simulations;`
- L89 _public member_ `uint64 FirstEngineFrame = 0;`
- L90 _public member_ `uint64 LastEngineFrame = 0;`

#### struct `FSimContentsView`  
`struct FSimContentsView`  
_L94-100_
- desc: View into a specific piece of simulation content. E.g, something you click on in the sim timeline view.
- L96 _public member_ `TSharedPtr<FSimulationData::FRestrictedView> SimView;`
- L98 _public member_ `const FSimulationData::FTick* SimTick = nullptr;`
- L99 _public member_ `const FSimulationData::FNetSerializeRecv* NetRecv = nullptr;`

#### class `SNPWindow`  
`class SNPWindow : public SCompoundWidget`  
_L105-223_
- inherits: `SCompoundWidget`
- desc: Network Prediction Window, this is the top level / starting point for the NP Insights UI
- L110 _public prototype_ `SNPWindow();`
- L111 _public prototype_ `virtual ~SNPWindow();`
- L113 _public function_ `SLATE_BEGIN_ARGS(SNPWindow)`
- L114 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<SDockTab>& ConstructUnderMajorTab, const TSharedPtr<SWindow>& ConstructUnderWindow);`
- L117 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L119 _public prototype_ `void Reset();`
- L121 _public function_ `const TSharedPtr<FUICommandList> GetCommandList() const`
- L122 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L138 _public prototype_ `const bool AutoScrollSimulationFrames() const;`
- L139 _public prototype_ `void SetAutoScrollSimulationFrames(const bool bAutoScroll);`
- L140 _public prototype_ `void SetAutoScrollDirty();` — Forces one auto scroll but does not change user-selectable state
- L142 _public prototype_ `void SetEngineFrame(uint64 InFrame, const bool bSetAutoScrollDirty=false);`
- L143 _public prototype_ `uint64 GetCurrentEngineFrame() const;`
- L144 _public prototype_ `uint64 GetMinEngineFrame() const;`
- L145 _public prototype_ `uint64 GetMaxEngineFrame() const;`
- L147 _public prototype_ `void NextEngineFrame();`
- L148 _public prototype_ `bool CanNextEngineFrame() const;`
- L150 _public prototype_ `void PrevEngineFrame();`
- L151 _public prototype_ `bool CanPrevEngineFrame() const;`
- L153 _public prototype_ `void FirstEngineFrame();`
- L154 _public prototype_ `bool CanFirstEngineFrame() const;`
- L156 _public prototype_ `void LastEngineFrame();`
- L157 _public prototype_ `bool CanLastEngineFrame() const;`
- L159 _public prototype_ `void JumpPreviousViewedEngineFrame();`
- L160 _public prototype_ `void JumpNextViewedEngineFrame();`
- L164 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnFilteredDataCollectionChange, const FFilteredDataCollection&) FOnFilteredDataCollectionChange OnFilteredDataCollectionChange;` — Called when the filtered view of our data has changed. Note this won't be called just because new data (within our filter) has been added by the provider
- L167 _public function_ `const FFilteredDataCollection& GetFilteredDataCollection() const`
- L169 _public prototype_ `void OnGetOptionsMenu(FMenuBuilder& Builder);`
- L172 _public prototype_ `void NotifySimContentClicked(const FSimContentsView& Content);` — Notifies from SimFrame Timeline View
- L174 _public function_ `const FSimContentsView& GetSelectedContent() const`
- L176 _public prototype_ `void SearchUserData(const FText& InFilterText);`
- L179 _public prototype_ `FText PIESessionComboBox_GetSelectionText() const;`
- L180 _public prototype_ `void PIESessionComboBox_OnSelectionChanged(TSharedPtr<int32> NewPIEMode, ESelectInfo::Type SelectInfo);`
- L181 _public prototype_ `TSharedRef<SWidget> PIESessionComboBox_OnGenerateWidget(TSharedPtr<int32> InPIEMode) const;`
- L183 _public member_ `TArray<TSharedPtr<int32>> PIESessionOptions;`
- L184 _public member_ `int32 SelectedPIESession = -1;`
- L188 _private prototype_ `void PopulateFilteredDataView();`
- L190 _private member_ `FNPFilter Filter;`
- L191 _private member_ `FNPUnfilteredDataView UnfilteredDataView;`
- L193 _private member_ `FFilteredDataCollection FilteredDataCollection;`
- L195 _private prototype_ `void FillMenu(FMenuBuilder& MenuBuilder, const TSharedPtr<FTabManager> TabManager);`
- L197 _private prototype_ `void BindCommands();`
- L200 _private member_ `TSharedPtr<FUICommandList> CommandList;` — Commandlist used in the window (Maps commands to window specific actions)
- L203 _private member_ `TSharedPtr<FTabManager> TabManager;` — Holds the tab manager that manages the front-end's tabs.
- L205 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Toolbar(const FSpawnTabArgs& Args);`
- L206 _private prototype_ `TSharedRef<SDockTab> SpawnTab_SimFrameView(const FSpawnTabArgs& Args);`
- L207 _private prototype_ `TSharedRef<SDockTab> SpawnTab_SimFrameContentView(const FSpawnTabArgs& Args);`
- L208 _private prototype_ `void OnToolbarTabClosed(TSharedRef<SDockTab> TabBeingClosed);`
- L209 _private prototype_ `void OnSimFrameViewTabClosed(TSharedRef<SDockTab> TabBeingClosed);`
- L210 _private prototype_ `void OnSimFrameContentTabClosed(TSharedRef<SDockTab> TabBeingClosed);`
- L212 _private member_ `TSharedPtr<SNPSimFrameView> FrameView;`
- L213 _private member_ `TSharedPtr<SNPSimFrameContents> SimFrameContents;`
- L215 _private member_ `class IUnrealInsightsModule* InsightsModule;`
- L217 _private member_ `FSimContentsView SelectedContent;`
- L219 _private member_ `uint64 CachedProviderDataCounter = 0;`
- L221 _private member_ `TArray<uint64> MaxEngineFrameHistory;`
- L222 _private member_ `int32 EngineFrameHistoryIndex = -1;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace ESelectInfo`
- L18 _namespace_ `namespace TraceServices`
- L124 _macro_ `#define DECLARE_TOGGLE_COMMAND(CmdName)\`
- L164 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnFilteredDataCollectionChange, const FFilteredDataCollection&) FOnFilteredDataCollectionChange OnFilteredDataCollectionChange;` — Called when the filtered view of our data has changed. Note this won't be called just because new data (within our filter) has been added by the provider

### `Plugins/Runtime/NetworkPredictionInsights/Source/NetworkPredictionInsights/Public/INetworkPredictionInsightsModule.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace NetworkPredictionInsightsTabs`
- L9 _externvar_ `extern const FName DocumentTab;` (scope `NetworkPredictionInsightsTabs`)

### `Plugins/Runtime/NetworkPredictionInsights/Source/NetworkPredictionInsights/Public/INetworkPredictionProvider.h` (Public)


#### enum `ENP_NetRole`  
`enum class ENP_NetRole: uint8`  
_L19-30_
- desc: Mirroring this is unavoidable in order to keep NetworkPredictionInsights from depending on EngineTypes
- L22 _public enumerator_ `None` — No role at all.
- L24 _public enumerator_ `SimulatedProxy` — Locally simulated proxy of this actor.
- L26 _public enumerator_ `AutonomousProxy` — Locally autonomous proxy of this actor.
- L28 _public enumerator_ `Authority` — Authoritative control over the actor.
- L29 _public enumerator_ `MAX`

#### enum `ENP_TickingPolicy`  
`enum class ENP_TickingPolicy: uint8`  
_L33-37_
- desc: Must be kept in sync with ENetworkPredictionTickingPolicy
- L35 _public enumerator_ `Independent = 1 << 0`
- L36 _public enumerator_ `Fixed = 1 << 1`

#### enum `ENP_NetworkLOD`  
`enum class ENP_NetworkLOD: uint8`  
_L40-45_
- desc: Must be kept in sync with ENetworkLOD
- L42 _public enumerator_ `Interpolated`
- L43 _public enumerator_ `SimExtrapolate`
- L44 _public enumerator_ `ForwardPredict`

#### enum `ENP_UserState`  
`enum class ENP_UserState: uint8`  
_L47-54_
- L49 _public enumerator_ `Input`
- L50 _public enumerator_ `Sync`
- L51 _public enumerator_ `Aux`
- L52 _public enumerator_ `Physics`
- L53 _public enumerator_ `MAX`

#### enum `ENP_UserStateSource`  
`enum class ENP_UserStateSource: uint8`  
_L56-65_
- L58 _public enumerator_ `Unknown = 1 << 0` — not set yet
- L59 _public enumerator_ `ProduceInput = 1 << 1` — System called produce input to sample new input locally (should only apply to InputCmd state)
- L60 _public enumerator_ `SynthInput = 1 << 2` — System created input synthetically: based on previous state or some guess.
- L61 _public enumerator_ `SimTick = 1 << 3` — Generated during a simulation tick
- L62 _public enumerator_ `NetRecv = 1 << 4` — Received from network but not committed to buffers
- L63 _public enumerator_ `NetRecvCommit = 1 << 5` — Received from network and committed to the buffers
- L64 _public enumerator_ `OOB = 1 << 6` — Out of band modification (e.g, game code)

#### enum `ENetSerializeRecvStatus`  
`enum class ENetSerializeRecvStatus: uint8`  
_L67-76_
- L69 _public enumerator_ `Unknown` — The moment we trace a Net Recv, its status is unknown.
- L71 _public enumerator_ `Confirm` — Valid data that did not cause a correction.
- L72 _public enumerator_ `Rollback` — Caused simulation to rollback. A correction.
- L73 _public enumerator_ `Jump` — Caused simulation to jump forward, effectively reseting its state
- L74 _public enumerator_ `Fault` — Unable to process the data. For example, received frame we no longer had in our local buffers
- L75 _public enumerator_ `Stale` — Received multiple bunches in a frame, this was effectively replaced by a newer one and not processed.

#### struct `FSimNetActorID`  
`struct FSimNetActorID`  
_L85-94_
- desc: How we identify actors across network connection and PIE sessions
- L87 _public member_ `int32 SimID;`
- L88 _public member_ `int32 PIESession;`
- L90 _public function_ `bool operator==(const FSimNetActorID& Other) const`

#### struct `TRestrictedPageViewIterator`  
`template<typename T> struct TRestrictedPageViewIterator`  
_L105-127_
- L107 _public function_ `TRestrictedPageViewIterator(const TRestrictedPageArrayView<T>& InPageArrayView, uint64 StartItemIndex=0) : PageArrayView(InPageArrayView), CurrentItemIdx(StartItemIndex)`
- L113 _public function_ `void operator++()`
- L114 _public function_ `void operator--()`
- L115 _public function_ `operator bool()`
- L117 _public function_ `const T& operator* () const`
- L118 _public function_ `const T* operator->() const`
- L122 _private function_ `bool Valid() const`
- L124 _private member_ `const TRestrictedPageArrayView<T>& PageArrayView;`
- L125 _private member_ `mutable TraceServices::TPagedArrayIterator<T, typename TraceServices::TPagedArray<T>::PageType> It;`
- L126 _private member_ `uint64 CurrentItemIdx;` — Kind of unfortunate but we store this ourselves to avoid calculating it off the iter each time

#### struct `TRestrictedPageArrayView`  
`template<typename T> struct TRestrictedPageArrayView`  
_L130-174_
- L132 _public function_ `TRestrictedPageArrayView(const TraceServices::TPagedArray<T>& InPageArray, uint64 InStart, uint64 InEnd) : PageArray(InPageArray), StartItemIdx(InStart), EndItemIdx(InEnd)`
- L135 _public function_ `TRestrictedPageViewIterator<T> GetIterator() const`
- L140 _public function_ `TRestrictedPageViewIterator<T> GetIteratorFromEnd() const`
- L145 _public function_ `const T& GetLast() const`
- L150 _public function_ `const T& GetFirst() const`
- L155 _public function_ `const T& operator[](uint64 Index) const`
- L161 _public function_ `int32 GetNum() const`
- L171 _private member_ `const TraceServices::TPagedArray<T>& PageArray;`
- L172 _private member_ `uint64 StartItemIdx;`
- L173 _private member_ `uint64 EndItemIdx;`

#### struct `TSparseFrameData`  
`template<typename T> struct TSparseFrameData`  
_L290-331_
- L292 _public function_ `const TSharedRef<const T> Read(uint64 EngineFrame) const`
- L307 _public function_ `const TSharedRef<T>& Write(uint64 EngineFrame)`
- L330 _private member_ `TArray<TSharedRef<T>> SparseData;`

#### struct `FSimulationData`  
`struct FSimulationData`  
_L334-629_
- desc: Holds all data we traced for a given simulation.
- L336 _public function_ `FSimulationData(int32 InTraceID, TraceServices::ILinearAllocator& Allocator) : TraceID(InTraceID) , Ticks(Allocator, 1024) , NetRecv(Allocator, 1024) , UserData(Allocator)`
- L582 _public function_ `TSharedRef<FRestrictedView> MakeRestrictedView(uint64 MinEngineFrame, uint64 MaxEngineFrame) const`
- L596 _public member_ `int32 TraceID;`
- L598 _public member_ `TraceServices::TPagedArray<FTick> Ticks;`
- L599 _public member_ `TraceServices::TPagedArray<FNetSerializeRecv> NetRecv;` — Actually holds the allocated recv records
- L601 _public member_ `TSparseFrameData<FSparse> SparseData;`
- L602 _public member_ `FConst ConstData;`
- L604 _public member_ `FUserData UserData;`
- L628 _public member_ `} Analysis;`

#### struct `FSimulationData::FSystemFault`  
`struct FSystemFault`  
_L345-348_
- L347 _public member_ `const TCHAR* Str;` — Traced Fmt string of fault

#### struct `FSimulationData::FNetSerializeRecv`  
`struct FNetSerializeRecv`  
_L350-363_
- L353 _public member_ `uint64 EngineFrame;` — Traced Data:
- L354 _public member_ `FSimTime SimTimeMS;`
- L355 _public member_ `int32 Frame;`
- L358 _public member_ `ENetSerializeRecvStatus Status = ENetSerializeRecvStatus::Unknown;` — Analysis Data:
- L359 _public member_ `bool bOrphan = true;` — Hasn't been attached to FTick::StartNetRecv
- L361 _public member_ `FSimulationData::FTick* NextTick = nullptr;`
- L362 _public member_ `TArray<FSystemFault> SystemFaults;` — System faults encountered during recv

#### struct `FSimulationData::FTick`  
`struct FTick`  
_L366-390_
- desc: Data for a single simulation tick
- L369 _public member_ `uint64 EngineFrame;` — Traced Data:
- L371 _public member_ `FSimTime StartMS;`
- L372 _public member_ `FSimTime EndMS;`
- L374 _public member_ `int32 OutputFrame;`
- L375 _public member_ `int32 LocalOffsetFrame;`
- L376 _public member_ `int32 NumBufferedInputCmds;`
- L377 _public member_ `bool bInputFault;`
- L382 _public member_ `const FNetSerializeRecv* StartNetRecv = nullptr;` — Net Recv that was processed prior to this tick. Will often be null. Used to ensure the ticks are drawn on the right sub track (Y)
- L384 _public member_ `uint64 ConfirmedEngineFrame = 0;` — Engine frame this became confirmed (we serialized a time past this)
- L385 _public member_ `uint64 TrashedEngineFrame = 0;` — Engine frame this became trashed (we resimulated this time in a later frame)
- L386 _public member_ `bool bRepredict = false;` — This tick was a repredict: we had already simulated up to this point before
- L388 _public member_ `bool bReconcileDueToOffsetChange = false;`
- L389 _public member_ `const TCHAR* ReconcileStr = nullptr;`

#### struct `FSimulationData::FSparse`  
`struct FSparse`  
_L393-405_
- desc: Data that changes rarely over time about the simulation
- L395 _public function_ `FSparse(uint64 InEngineFrame) : EngineFrame(InEngineFrame)`
- L399 _public member_ `uint64 EngineFrame;` — engine frame this data became valid
- L400 _public member_ `ENP_NetRole NetRole = ENP_NetRole::None;`
- L401 _public member_ `bool bHasNetConnection = false;`
- L402 _public member_ `ENP_TickingPolicy TickingPolicy = ENP_TickingPolicy::Independent;`
- L403 _public member_ `ENP_NetworkLOD NetworkLOD = ENP_NetworkLOD::Interpolated;`
- L404 _public member_ `int32 ServiceMask = 0;`

#### struct `FSimulationData::FConst`  
`struct FConst`  
_L408-413_
- desc: Data that never changes about the simulation
- L410 _public member_ `FSimNetActorID ID;`
- L411 _public member_ `FName GroupName;`
- L412 _public member_ `FString DebugName;`

#### struct `FSimulationData::FUserState`  
`struct FUserState`  
_L415-423_
- L417 _public member_ `uint64 EngineFrame;` — EngineFrame this was written
- L418 _public member_ `int32 SimFrame;` — This states sim frame (what frame# it was inserted into the buffer at)
- L419 _public member_ `FUserState* Prev = nullptr;` — Previously written user state at this SimFrame number. Prev->EngineFrame < this->EngineFrame.
- L420 _public member_ `const TCHAR* UserStr = nullptr;` — stable pointer to traced string representation of user state
- L421 _public member_ `ENP_UserStateSource Source = ENP_UserStateSource::Unknown;` — Analyzed source of this user state
- L422 _public member_ `const TCHAR* OOBStr = nullptr;` — if OOB mod, this is the user traced string (telling us who did it)

#### struct `FSimulationData::FUserStateStore`  
`struct FUserStateStore`  
_L425-512_
- L427 _public function_ `FUserStateStore(TraceServices::ILinearAllocator& Allocator) : UserStates(Allocator, 1024)`
- L430 _public function_ `FORCENOINLINE FUserState& Push(int32 Frame, uint64 EngineFrame)`
- L457 _public function_ `FORCENOINLINE const FUserState* Get(int32 InFrame, uint64 MaxEngineFrame, uint8 ExcludeSourceMask, bool bSparseAccess) const`
- L509 _private member_ `TraceServices::TPagedArray<FUserState> UserStates;` — Holds the actual FUserState. Pointers to these elements are stable
- L510 _private member_ `TMap<int32, FUserState*> FrameMap;` — Acceleration map to find head FUserState for given simulation frame
- L511 _private member_ `TBitArray<> PopulatedFrames;` — Bit array for which simulation frames are populated. Accelerates finding "last valid" state in sparse cases.

#### struct `FSimulationData::FUserData`  
`struct FUserData`  
_L514-521_
- L516 _public function_ `FUserData(TraceServices::ILinearAllocator& Allocator) : Store`
- L520 _public member_ `FUserStateStore Store[(int32)ENP_UserState::MAX];`

#### struct `FSimulationData::FRestrictedUserStateView`  
`struct FRestrictedUserStateView`  
_L523-540_
- L525 _public function_ `FRestrictedUserStateView(const FUserData& InUserData, uint64 InMaxEngineFrame) : UserData(InUserData), MaxEngineFrame(InMaxEngineFrame)`
- L529 _public function_ `FORCENOINLINE const FUserState* Get(ENP_UserState Type, int32 SimFrame, uint64 InEngineFrame, uint8 ExcludeMask) const`
- L538 _private member_ `const FUserData& UserData;`
- L539 _private member_ `uint64 MaxEngineFrame;`

#### struct `FSimulationData::FRestrictedView`  
`struct FRestrictedView`  
_L544-580_
- L546 _public member_ `const TRestrictedPageArrayView<FTick> Ticks;`
- L547 _public member_ `const TRestrictedPageArrayView<FNetSerializeRecv> NetRecv;`
- L548 _public member_ `const FRestrictedUserStateView UserData;`
- L549 _public member_ `const TSharedRef<const FSparse> SparseData;`
- L550 _public member_ `const FConst& ConstData;`
- L551 _public member_ `const int32 TraceID;`
- L553 _public function_ `int32 GetMaxSimTime() const`
- L567 _public function_ `uint64 GetMaxEngineFrame() const`

#### struct `FSimulationData::FAnalysis`  
`struct FAnalysis`  
_L607-628_
- desc: Data that is only used as a temp/scratch pad during the analysis page. This should not show up in the UI or FRestrictedView
- L610 _public member_ `TArray<FNetSerializeRecv*> PendingNetSerializeRecv;` — NetRecvs that we haven't matched with a tick or declared orphaned yet
- L612 _public member_ `uint64 NetRecvItemIdx = 0;`
- L613 _public member_ `uint64 TrashItemIdx = 0;`
- L615 _public member_ `FSimTime MaxTickSimTimeMS = 0;` — Highest EndMS we have seen so far from Tick traces
- L617 _public member_ `int32 NumBufferedInputCmds = 0;`
- L618 _public member_ `bool bInputFault = false;`
- L620 _public member_ `TArray<FUserState*> PendingCommitUserStates;` — NetRecv'd state that hasn't been commited
- L621 _public member_ `TArray<FSystemFault> PendingSystemFaults;`
- L622 _public member_ `const TCHAR* PendingOOBStr = nullptr;`
- L623 _public member_ `const TCHAR* PendingReconcileStr = nullptr;`
- L625 _public member_ `int32 LocalFrameOffset = 0;`
- L626 _public member_ `bool bLocalFrameOffsetChanged = false;`

#### class `INetworkPredictionProvider`  
`class INetworkPredictionProvider : public TraceServices::IProvider`  
_L631-644_
- inherits: `TraceServices::IProvider`
- L637 _public prototype_ `virtual uint32 GetNetworkPredictionTraceVersion() const = 0;` — Return the version reported in the trace A return value of 0 indicates no NetworkPrediction trace data
- L640 _public prototype_ `virtual uint64 GetNetworkPredictionDataCounter() const = 0;` — Returns generic counter that increments everytime we analyse network prediction related data.
- L643 _public prototype_ `virtual TArrayView<const TSharedRef<FSimulationData>> ReadSimulationData() const = 0;` — Returns all simulation data that has been analyzed

#### Free symbols / members of external scopes

- L13 _macro_ `#define NP_INSIGHTS_SIM_TIME int32`
- L16 _typedef_ `using FSimTime = NP_INSIGHTS_SIM_TIME;`
- L78 _prototype_ `const TCHAR* LexToString(ENP_NetRole Role);`
- L79 _prototype_ `const TCHAR* LexToString(ENP_UserState State);`
- L80 _prototype_ `const TCHAR* LexToString(ENP_UserStateSource Source);`
- L81 _prototype_ `const TCHAR* LexToString(ENetSerializeRecvStatus Status);`
- L82 _prototype_ `const TCHAR* LexToString(ENP_TickingPolicy Policy);`
- L177 _function_ `template<typename T> typename TEnableIf<!TIsPointer<T>::Value, uint64>::Type GetEngineFrame(const T& Element)`
- L183 _function_ `template<typename T> typename TEnableIf<TIsPointer<T>::Value, uint64>::Type GetEngineFrame(const T& Element)`
- L191 _function_ `template<typename T> uint64 FindMinIndexPagedArray(const TraceServices::TPagedArray<T>& PageArray, uint64 MinFrameNumber)` — Searches through PageArray for index of first element >= MinFrameNumber
- L218 _function_ `template<typename T> uint64 FindMaxIndexPagedArray(const TraceServices::TPagedArray<T>& PageArray, uint64 MaxFrameNumber)` — Searches through PageArray for index+1 of first element > MinFrameNumber. E.g, index to iterate up to (<) for valid EngineFrameNumber. Fixme: it probably makes more sense to just give this a start index and pickup where FindMinIndex left off
- L258 _function_ `template<typename T> int32 FindMinIndexTArray(const TArray<const T*>& Array, uint64 MinFrameNumber)`
- L272 _function_ `template<typename T> int32 FindMaxIndexTArray(const TArray<const T*>& Array, uint64 MaxFrameNumber, int32 StartIdx=0)`
- L460 _function_ `` (scope `FSimulationData::FUserStateStore::Get`)
- L646 _prototype_ `const INetworkPredictionProvider* ReadNetworkPredictionProvider(const TraceServices::IAnalysisSession& Session);`
