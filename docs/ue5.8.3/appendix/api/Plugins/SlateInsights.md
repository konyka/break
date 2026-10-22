# Plugins / SlateInsights

- module root: `Plugins/Slate/SlateInsights/Source/SlateInsights`
- headers: 11; symbols: 310
- symbol kinds: class=12, enum=3, enumerator=14, function=39, member=84, namespace=51, prototype=91, struct=9, typedef=7
- PrivateDependencyModuleNames: ApplicationCore, AssetRegistry, Core, CoreUObject, Engine, InputCore, Slate, SlateCore, SourceCodeAccess, TraceAnalysis, TraceInsights, TraceInsightsCore, TraceLog, TraceServices

### `Plugins/Slate/SlateInsights/Source/SlateInsights/Private/SSlateFrameSchematicView.h` (Private)


#### class `UE::SlateInsights::SSlateFrameSchematicView`  
`class SSlateFrameSchematicView : public SCompoundWidget`  
_L32-96_
- inherits: `SCompoundWidget`
- L35 _public function_ `SLATE_BEGIN_ARGS(SSlateFrameSchematicView)`
- L37 _public prototype_ `~SSlateFrameSchematicView();`
- L39 _public prototype_ `void Construct(const FArguments& InArgs);`
- L41 _public prototype_ `void SetSession(UE::Insights::Timing::ITimingViewSession* InTimingViewSession, const TraceServices::IAnalysisSession* InAnalysisSession);`
- L43 _public prototype_ `bool IsSessionSet() const;`
- L46 _private prototype_ `TSharedRef<ITableRow> HandleUniqueInvalidatedMakeTreeRowWidget(TSharedPtr<Private::FWidgetUniqueInvalidatedInfo> InInfo, const TSharedRef<STableViewBase>& OwnerTable);`
- L47 _private prototype_ `void HandleUniqueInvalidatedChildrenForInfo(TSharedPtr<Private::FWidgetUniqueInvalidatedInfo> InInfo, TArray<TSharedPtr<Private::FWidgetUniqueInvalidatedInfo>>& OutChildren);`
- L48 _private prototype_ `TSharedRef<ITableRow> HandleWidgetUpdateInfoGenerateWidget(TSharedPtr<Private::FWidgetUpdateInfo> Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L49 _private prototype_ `void HandleTimeMarkerChanged(UE::Insights::Timing::ETimeChangedFlags InFlags, double InTimeMarker);`
- L50 _private prototype_ `void HandleSelectionChanged(UE::Insights::Timing::ETimeChangedFlags InFlags, double StartTime, double EndTime);`
- L51 _private prototype_ `void HandleSelectionEventChanged(const TSharedPtr<const ITimingEvent> InEvent);`
- L53 _private prototype_ `TSharedPtr<SWidget> HandleWidgetInvalidateListContextMenu();`
- L54 _private prototype_ `FString HandleWidgetInvalidateListToStringDebug(TSharedPtr<Private::FWidgetUniqueInvalidatedInfo> Item);`
- L55 _private prototype_ `bool CanWidgetInvalidateListSearchWidget() const;`
- L56 _private prototype_ `void HandleWidgetInvalidateListSearchWidget();`
- L57 _private prototype_ `bool CanWidgetInvalidateListGotoRootWidget() const;`
- L58 _private prototype_ `void HandleWidgetInvalidateListGotoRootWidget();`
- L59 _private prototype_ `bool CanWidgetInvalidateListViewScriptAndCallStack() const;`
- L60 _private prototype_ `void HandleWidgetInvalidateListViewScriptAndCallStack();`
- L61 _private prototype_ `TSharedPtr<SWidget> HandleWidgetUpdateInfoContextMenu();`
- L62 _private prototype_ `bool CanWidgetUpdateInfoSearchWidget() const;`
- L63 _private prototype_ `void HandleWidgetUpdateInfoSearchWidget();`
- L64 _private prototype_ `void HandleWidgetUpdateInfoSort(EColumnSortPriority::Type, const FName& ColumnId, EColumnSortMode::Type SortMode);`
- L65 _private prototype_ `EColumnSortMode::Type HandleWidgetUpdateGetSortMode(FName ColumnId) const;`
- L67 _private prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L69 _private prototype_ `void RefreshNodes();`
- L70 _private prototype_ `void RefreshNodes_Invalidation(const FSlateProvider* SlateProvider);`
- L71 _private prototype_ `void RefreshNodes_Update(const FSlateProvider* SlateProvider);`
- L73 _private prototype_ `void SortWidgetUpdateInfos();`
- L76 _private member_ `const TraceServices::IAnalysisSession* AnalysisSession;`
- L77 _private member_ `UE::Insights::Timing::ITimingViewSession* TimingViewSession;`
- L79 _private member_ `TSharedPtr<STreeView<TSharedPtr<Private::FWidgetUniqueInvalidatedInfo>>> WidgetInvalidateInfoListView;`
- L80 _private member_ `TArray<TSharedPtr<Private::FWidgetUniqueInvalidatedInfo>> WidgetInvalidationInfos;`
- L82 _private member_ `TSharedPtr<SListView<TSharedPtr<Private::FWidgetUpdateInfo>>> WidgetUpdateInfoListView;`
- L83 _private member_ `TArray<TSharedPtr<Private::FWidgetUpdateInfo>> WidgetUpdateInfos;`
- L85 _private member_ `TSharedPtr<SExpandableArea> ExpandableSearchBox;`
- L86 _private member_ `TSharedPtr<Private::SSlateWidgetSearch> WidgetSearchBox;`
- L87 _private member_ `TSharedPtr<STextBlock> InvalidationSummary;`
- L88 _private member_ `TSharedPtr<STextBlock> UpdateSummary;`
- L89 _private member_ `TSharedPtr<SMultiLineEditableTextBox> ScriptAndCallStackTextBox;`
- L91 _private member_ `FName WidgetUpdateSortColumn;`
- L92 _private member_ `bool bWidgetUpdateSortAscending;`
- L94 _private member_ `double StartTime;`
- L95 _private member_ `double EndTime;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace TraceServices`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Insights` (scope `UE`)
- L11 _namespace_ `namespace Timing` (scope `UE::Insights`)
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Insights` (scope `UE`)
- L12 _namespace_ `namespace Timing` (scope `UE::Insights`)
- L22 _namespace_ `namespace UE`
- L24 _namespace_ `namespace SlateInsights` (scope `UE`)
- L28 _namespace_ `namespace Private` (scope `UE::SlateInsights`)
- L29 _namespace_ `namespace Private` (scope `UE::SlateInsights`)
- L30 _namespace_ `namespace Private` (scope `UE::SlateInsights`)

### `Plugins/Slate/SlateInsights/Source/SlateInsights/Private/SSlateTraceFlags.h` (Private)


#### class `UE::SlateInsights::SSlateTraceWidgetUpdateFlags`  
`class SSlateTraceWidgetUpdateFlags : public SLeafWidget`  
_L14-33_
- inherits: `SLeafWidget`
- L17 _public function_ `SLATE_BEGIN_ARGS(SSlateTraceWidgetUpdateFlags) : _UpdateFlags(EWidgetUpdateFlags::None)`
- L20 _public prototype_ `SLATE_ARGUMENT(EWidgetUpdateFlags, UpdateFlags) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L26 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const;`
- L29 _public prototype_ `virtual FVector2D ComputeDesiredSize(float LayoutScaleMultiplier) const override;`
- L32 _private member_ `EWidgetUpdateFlags UpdateFlagsValue;`

#### class `UE::SlateInsights::SSlateTraceInvalidateWidgetReasonFlags`  
`class SSlateTraceInvalidateWidgetReasonFlags : public SLeafWidget`  
_L35-54_
- inherits: `SLeafWidget`
- L38 _public function_ `SLATE_BEGIN_ARGS(SSlateTraceInvalidateWidgetReasonFlags) : _Reason(EInvalidateWidgetReason::None)`
- L41 _public prototype_ `SLATE_ARGUMENT(EInvalidateWidgetReason, Reason) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L47 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const;`
- L50 _public prototype_ `virtual FVector2D ComputeDesiredSize(float LayoutScaleMultiplier) const override;`
- L53 _private member_ `EInvalidateWidgetReason Reason;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SlateInsights` (scope `UE`)

### `Plugins/Slate/SlateInsights/Source/SlateInsights/Private/SlateAnalyzer.h` (Private)


#### class `UE::SlateInsights::FSlateAnalyzer`  
`class FSlateAnalyzer : public UE::Trace::IAnalyzer`  
_L16-42_
- inherits: `UE::Trace::IAnalyzer`
- L19 _public prototype_ `FSlateAnalyzer(TraceServices::IAnalysisSession& InSession, FSlateProvider& InSlateProvider);`
- L21 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L22 _public function_ `virtual void OnAnalysisEnd() override`
- L23 _public prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L40 _private member_ `TraceServices::IAnalysisSession& Session;`
- L41 _private member_ `FSlateProvider& SlateProvider;`

#### enum `UE::SlateInsights::FSlateAnalyzer::(anonymous)`  
``  
_L27-38_

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace TraceServices`
- L9 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SlateInsights` (scope `UE`)
- L28 _enumerator_ `RouteId_ApplicationTickAndDrawWidgets` (scope `UE::SlateInsights::FSlateAnalyzer::__anon873d67100103`)
- L29 _enumerator_ `RouteId_AddWidget` (scope `UE::SlateInsights::FSlateAnalyzer::__anon873d67100103`)
- L30 _enumerator_ `RouteId_WidgetInfo` (scope `UE::SlateInsights::FSlateAnalyzer::__anon873d67100103`)
- L31 _enumerator_ `RouteId_RemoveWidget` (scope `UE::SlateInsights::FSlateAnalyzer::__anon873d67100103`)
- L32 _enumerator_ `RouteId_WidgetUpdated` (scope `UE::SlateInsights::FSlateAnalyzer::__anon873d67100103`)
- L33 _enumerator_ `RouteId_WidgetInvalidated` (scope `UE::SlateInsights::FSlateAnalyzer::__anon873d67100103`)
- L34 _enumerator_ `RouteId_RootInvalidated` (scope `UE::SlateInsights::FSlateAnalyzer::__anon873d67100103`)
- L35 _enumerator_ `RouteId_RootChildOrderInvalidated` (scope `UE::SlateInsights::FSlateAnalyzer::__anon873d67100103`)
- L36 _enumerator_ `RouteId_InvalidationCallstack` (scope `UE::SlateInsights::FSlateAnalyzer::__anon873d67100103`)
- L37 _enumerator_ `RouteId_WidgetUpdateSteps` (scope `UE::SlateInsights::FSlateAnalyzer::__anon873d67100103`)

### `Plugins/Slate/SlateInsights/Source/SlateInsights/Private/SlateFrameGraphTrack.h` (Private)


#### enum `UE::SlateInsights::ESlateFrameGraphLayout`  
`enum class ESlateFrameGraphLayout : int32`  
_L23-29_
- desc: The various layouts that we display series with
- L26 _public enumerator_ `Overlay` — Draw series overlaid one on top of the other
- L28 _public enumerator_ `Stack` — Draw series in a vertical stack

#### class `UE::SlateInsights::FSlateFrameGraphTrack`  
`class FSlateFrameGraphTrack : public FGraphTrack`  
_L32-69_
- inherits: `FGraphTrack`
- desc: GraphTrack that group all the different track for the Slate Frame data.
- L35 _private typedef_ `using Super = FGraphTrack;`
- L38 _public prototype_ `FSlateFrameGraphTrack(const FSlateTimingViewSession& InSharedData);`
- L41 _public prototype_ `virtual void Draw(const ITimingTrackDrawContext& Context) const override;`
- L42 _public prototype_ `virtual void PreUpdate(const ITimingTrackUpdateContext& Context) override;`
- L43 _public prototype_ `virtual void BuildContextMenu(FMenuBuilder& MenuBuilder) override;`
- L46 _public prototype_ `void AddDefaultSeries();`
- L47 _public function_ `ESlateFrameGraphLayout GetLayout() const`
- L48 _public function_ `float GetRequestedTrackSizeScale() const`
- L51 _private prototype_ `void AddAllSeries(const ITimingTrackUpdateContext& Context);`
- L53 _private prototype_ `bool UpdateSeriesBounds(Private::FSlateFrameGraphSeries& InSeries, const FTimingTrackViewport& InViewport);`
- L54 _private prototype_ `void UpdateSeries(const FTimingTrackViewport& InViewport, TArrayView<TSharedPtr<Private::FSlateFrameGraphSeries>> Series);`
- L55 _private prototype_ `void UpdateTrackHeight(const ITimingTrackUpdateContext& Context);`
- L59 _private member_ `const FSlateTimingViewSession& SharedData;` — The shared data
- L62 _private member_ `float RequestedTrackSizeScale;` — The track size we want to be displayed at
- L65 _private member_ `int32 NumActiveSeries;` — The current number of active series
- L68 _private member_ `ESlateFrameGraphLayout Layout;` — The current series layout

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L14 _namespace_ `namespace SlateInsights` (scope `UE`)
- L20 _namespace_ `namespace Private` (scope `UE::SlateInsights`)

### `Plugins/Slate/SlateInsights/Source/SlateInsights/Private/SlateInsightsModule.h` (Private)


#### class `UE::SlateInsights::FSlateInsightsModule`  
`class FSlateInsightsModule : public IModuleInterface`  
_L21-41_
- inherits: `IModuleInterface`
- L24 _public prototype_ `static FSlateInsightsModule& Get();`
- L27 _public prototype_ `virtual void StartupModule() override;`
- L28 _public prototype_ `virtual void ShutdownModule() override;`
- L31 _public prototype_ `TSharedPtr<SSlateFrameSchematicView> GetSlateFrameSchematicViewTab(bool bInvoke);`
- L34 _private prototype_ `void RegisterTimingProfilerLayoutExtensions(FInsightsMajorTabExtender& InOutExtender);`
- L37 _private member_ `FSlateTraceModule TraceModule;`
- L38 _private member_ `FSlateTimingViewExtender TimingViewExtender;`
- L39 _private member_ `TWeakPtr<SSlateFrameSchematicView> SlateFrameSchematicView;`
- L40 _private member_ `TWeakPtr<FTabManager> InsightsTabManager;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L16 _namespace_ `namespace SlateInsights` (scope `UE`)

### `Plugins/Slate/SlateInsights/Source/SlateInsights/Private/SlateInsightsStyle.h` (Private)


#### class `UE::SlateInsights::FSlateInsightsStyle`  
`class FSlateInsightsStyle final : public FSlateStyleSet`  
_L19-64_
- inherits: `FSlateStyleSet`
- L22 _public function_ `FSlateInsightsStyle() : FSlateStyleSet("SlateInsightsStyle")`
- L54 _public function_ `static FSlateInsightsStyle& Get()`
- L60 _public function_ `~FSlateInsightsStyle()`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L16 _namespace_ `namespace SlateInsights` (scope `UE`)

### `Plugins/Slate/SlateInsights/Source/SlateInsights/Private/SlateProvider.h` (Private)


#### struct `UE::SlateInsights::Message::FWidgetId`  
`struct FWidgetId`  
_L27-41_
- L30 _private member_ `uint64 Value;`
- L33 _public function_ `constexpr FWidgetId() : Value(0)`
- L35 _public function_ `template<typename T, typename U = typename TEnableIf<std::is_same_v<T, uint64>>::Type> constexpr FWidgetId(T InValue) : Value(InValue)`
- L36 _public function_ `explicit operator bool() const`
- L37 _public function_ `uint64 GetValue() const`

#### struct `UE::SlateInsights::Message::FWidgetInfo`  
`struct FWidgetInfo`  
_L43-53_
- L45 _public member_ `FWidgetId WidgetId;`
- L46 _public member_ `FString Path;`
- L47 _public member_ `FString DebugInfo;`
- L48 _public member_ `uint64 EventIndex;`
- L50 _public prototype_ `FWidgetInfo() = default;`
- L51 _public prototype_ `FWidgetInfo(const UE::Trace::IAnalyzer::FEventData& EventData);`

#### struct `UE::SlateInsights::Message::FWidgetUpdatedMessage`  
`struct FWidgetUpdatedMessage`  
_L55-66_
- L57 _public member_ `FWidgetId WidgetId;`
- L59 _public member_ `double Duration;` — How long the update took.
- L61 _public member_ `int32 AffectedCount;` — Number of widget that was affected by the updated widget.
- L63 _public member_ `EWidgetUpdateFlags UpdateFlags;` — Flag that was set by an invalidation or on the widget directly.
- L65 _public prototype_ `FWidgetUpdatedMessage(const UE::Trace::IAnalyzer::FEventData& EventData, const UE::Trace::IAnalyzer::FEventTime& EventTime);`

#### struct `UE::SlateInsights::Message::FWidgetInvalidatedMessage`  
`struct FWidgetInvalidatedMessage`  
_L68-81_
- L70 _public member_ `uint64 SourceCycle;`
- L71 _public member_ `FWidgetId WidgetId;`
- L72 _public member_ `FWidgetId InvestigatorId;`
- L73 _public member_ `EInvalidateWidgetReason InvalidationReason = EInvalidateWidgetReason::None;`
- L74 _public member_ `bool bRootInvalidated = false;`
- L75 _public member_ `bool bRootChildOrderInvalidated = false;`
- L76 _public member_ `FString ScriptTrace;`
- L78 _public prototype_ `static FWidgetInvalidatedMessage FromWidget(const UE::Trace::IAnalyzer::FEventData& EventData);`
- L79 _public prototype_ `static FWidgetInvalidatedMessage FromRoot(const UE::Trace::IAnalyzer::FEventData& EventData);`
- L80 _public prototype_ `static FWidgetInvalidatedMessage FromChildOrder(const UE::Trace::IAnalyzer::FEventData& EventData);`

#### struct `UE::SlateInsights::Message::FApplicationTickedMessage`  
`struct FApplicationTickedMessage`  
_L83-97_
- L85 _public member_ `float DeltaTime;`
- L86 _public member_ `uint32 WidgetCount;`
- L87 _public member_ `uint32 TickCount;`
- L88 _public member_ `uint32 TimerCount;`
- L89 _public member_ `uint32 RepaintCount;`
- L90 _public member_ `uint32 VolatilePaintCount;`
- L91 _public member_ `uint32 PaintCount;`
- L92 _public member_ `uint32 InvalidateCount;`
- L93 _public member_ `uint32 RootInvalidatedCount;`
- L94 _public member_ `ESlateTraceApplicationFlags Flags;`
- L96 _public prototype_ `FApplicationTickedMessage(const UE::Trace::IAnalyzer::FEventData& EventData);`

#### struct `UE::SlateInsights::Message::FInvalidationCallstackMessage`  
`struct FInvalidationCallstackMessage`  
_L99-105_
- L101 _public member_ `uint64 SourceCycle;`
- L102 _public member_ `FString Callstack;`
- L104 _public prototype_ `FInvalidationCallstackMessage(const Trace::IAnalyzer::FEventData& EventData);`

#### struct `UE::SlateInsights::Message::FWidgetUpdateStep`  
`struct FWidgetUpdateStep`  
_L107-113_
- L110 _public member_ `FWidgetId WidgetId;`
- L111 _public member_ `int32 Depth;`
- L112 _public member_ `EUpdateStepType UpdateStep = EUpdateStepType::Paint;`

#### enum `UE::SlateInsights::Message::FWidgetUpdateStep::EUpdateStepType`  
`enum class EUpdateStepType : uint8`  
_L109-109_
- L109 _public enumerator_ `enum class EUpdateStepType : uint8 { Layout, Paint }; FWidgetId WidgetId; int32 Depth; EUpdateStepType UpdateStep = EUpdateStepType::Paint;`
- L109 _public enumerator_ `enum class EUpdateStepType : uint8 { Layout, Paint }; FWidgetId WidgetId; int32 Depth; EUpdateStepType UpdateStep = EUpdateStepType::Paint;`

#### class `UE::SlateInsights::FSlateProvider`  
`class FSlateProvider : public TraceServices::IProvider`  
_L117-222_
- inherits: `TraceServices::IProvider`
- L120 _public member_ `static FName ProviderName;`
- L122 _public prototype_ `FSlateProvider(TraceServices::IAnalysisSession& InSession);`
- L125 _public prototype_ `void AddWidget(double Seconds, uint64 WidgetId);`
- L126 _public prototype_ `void SetWidgetInfo(double Seconds, Message::FWidgetInfo Info);`
- L127 _public prototype_ `void RemoveWidget(double Seconds, uint64 WidgetId);`
- L130 _public prototype_ `void AddApplicationTickedEvent(double Seconds, Message::FApplicationTickedMessage Message);`
- L131 _public prototype_ `void AddWidgetUpdatedEvent(double Seconds, Message::FWidgetUpdatedMessage UpdatedMessage);`
- L132 _public prototype_ `void AddWidgetInvalidatedEvent(double Seconds, Message::FWidgetInvalidatedMessage InvalidatedMessage);`
- L133 _public prototype_ `void ProcessInvalidationCallstack(Message::FInvalidationCallstackMessage InvalidatedMessage);`
- L134 _public prototype_ `void ProcessWidgetUpdateSteps(const UE::Trace::IAnalyzer::FEventTime& EventTime, const UE::Trace::IAnalyzer::FEventData& EventData);`
- L137 _public typedef_ `using FApplicationTickedTimeline = TraceServices::TPointTimeline<Message::FApplicationTickedMessage>;`
- L138 _public function_ `const FApplicationTickedTimeline& GetApplicationTickedTimeline() const`
- L145 _public typedef_ `using FWidgetUpdatedTimeline = TraceServices::TPointTimeline<Message::FWidgetUpdatedMessage>;`
- L146 _public function_ `const FWidgetUpdatedTimeline& GetWidgetUpdatedTimeline() const`
- L153 _public typedef_ `using FWidgetInvalidatedTimeline = TraceServices::TPointTimeline<Message::FWidgetInvalidatedMessage>;`
- L154 _public function_ `const FWidgetInvalidatedTimeline& GetWidgetInvalidatedTimeline() const`
- L161 _public typedef_ `using FWidgetTimeline = TraceServices::TIntervalTimeline<Message::FWidgetId>;`
- L162 _public function_ `const FWidgetTimeline& GetWidgetTimeline() const`
- L169 _public typedef_ `using FWidgetUpdateStepsTimeline = TraceServices::TIntervalTimeline<Message::FWidgetUpdateStep>;`
- L170 _public function_ `const FWidgetUpdateStepsTimeline GetWidgetUpdateStepsTimeline() const`
- L196 _public function_ `const Message::FWidgetInfo* FindWidget(Message::FWidgetId WidgetId) const`
- L202 _public function_ `const FString* FindInvalidationCallstack(uint64 SourceCycle) const` — Find a callstack that should have been saved off from the Slate Provider
- L208 _private member_ `TraceServices::IAnalysisSession& Session;`
- L210 _private member_ `TMap<Message::FWidgetId, Message::FWidgetInfo> WidgetInfos;`
- L211 _private member_ `TMap<uint64, FString> InvalidationCallstacks;`
- L213 _private member_ `FWidgetTimeline WidgetTimelines;`
- L214 _private member_ `FApplicationTickedTimeline ApplicationTickedTimeline;`
- L215 _private member_ `FWidgetUpdatedTimeline WidgetUpdatedTimeline;`
- L216 _private member_ `FWidgetInvalidatedTimeline WidgetInvalidatedTimeline;`
- L217 _private member_ `FWidgetUpdateStepsTimeline WidgetPaintTimelines;`
- L219 _private member_ `TArray<TTuple<uint64, Message::FWidgetId>> WidgetUpdateStepsEventIndexes;`
- L220 _private member_ `uint32 WidgetUpdateStepsBufferNumber;`
- L221 _private member_ `bool bAcceptWidgetUpdateStepsComand;`

#### struct `UE::SlateInsights::FSlateProvider::TScopedEnumerateOutsideRange`  
`template<typename T> struct TScopedEnumerateOutsideRange`  
_L178-193_
- L180 _public function_ `TScopedEnumerateOutsideRange(const T& InTimeline) : Timeline(InTimeline)`
- L185 _public function_ `~TScopedEnumerateOutsideRange()`
- L189 _public prototype_ `TScopedEnumerateOutsideRange(const TScopedEnumerateOutsideRange&) = delete;`
- L190 _public prototype_ `TScopedEnumerateOutsideRange& operator= (const TScopedEnumerateOutsideRange&) = delete;`
- L192 _private member_ `const T& Timeline;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace TraceServices`
- L19 _namespace_ `namespace UE`
- L21 _namespace_ `namespace SlateInsights` (scope `UE`)
- L24 _namespace_ `namespace Message` (scope `UE::SlateInsights`)
- L38 _function_ `friend uint32 GetTypeHash(const FWidgetId& Key)` (scope `UE::SlateInsights::Message`)
- L39 _function_ `friend bool operator==(const FWidgetId A, const FWidgetId B)` (scope `UE::SlateInsights::Message`)
- L40 _function_ `friend bool operator!=(const FWidgetId A, const FWidgetId B)` (scope `UE::SlateInsights::Message`)
- L52 _function_ `friend bool operator==(const FWidgetInfo& A, FWidgetId B)` (scope `UE::SlateInsights::Message`)

### `Plugins/Slate/SlateInsights/Source/SlateInsights/Private/SlateTimingViewExtender.h` (Private)


#### class `UE::SlateInsights::FSlateTimingViewExtender`  
`class FSlateTimingViewExtender : public UE::Insights::Timing::ITimingViewExtender`  
_L18-36_
- inherits: `UE::Insights::Timing::ITimingViewExtender`
- L22 _public prototype_ `virtual void OnBeginSession(UE::Insights::Timing::ITimingViewSession& InSession) override;`
- L23 _public prototype_ `virtual void OnEndSession(UE::Insights::Timing::ITimingViewSession& InSession) override;`
- L24 _public prototype_ `virtual void Tick(UE::Insights::Timing::ITimingViewSession& InSession, const TraceServices::IAnalysisSession& InAnalysisSession) override;`
- L25 _public prototype_ `virtual void ExtendFilterMenu(UE::Insights::Timing::ITimingViewSession& InSession, FMenuBuilder& InMenuBuilder) override;`
- L35 _private member_ `TMap<UE::Insights::Timing::ITimingViewSession*, FPerSessionData> PerSessionDataMap;` — The data we host per-session

#### struct `UE::SlateInsights::FSlateTimingViewExtender::FPerSessionData`  
`struct FPerSessionData`  
_L29-32_
- L31 _public member_ `TUniquePtr<FSlateTimingViewSession> SharedData;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace TraceServices`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Insights` (scope `UE`)
- L9 _namespace_ `namespace Timing` (scope `UE::Insights`)
- L13 _namespace_ `namespace UE`
- L15 _namespace_ `namespace SlateInsights` (scope `UE`)

### `Plugins/Slate/SlateInsights/Source/SlateInsights/Private/SlateTimingViewSession.h` (Private)


#### class `UE::SlateInsights::FSlateTimingViewSession`  
`class FSlateTimingViewSession`  
_L20-74_
- L23 _public prototype_ `FSlateTimingViewSession();`
- L25 _public prototype_ `void OnBeginSession(UE::Insights::Timing::ITimingViewSession& InTimingViewSession);`
- L26 _public prototype_ `void OnEndSession(UE::Insights::Timing::ITimingViewSession& InTimingViewSession);`
- L27 _public prototype_ `void Tick(UE::Insights::Timing::ITimingViewSession& InTimingViewSession, const TraceServices::IAnalysisSession& InAnalysisSession);`
- L28 _public prototype_ `void ExtendFilterMenu(FMenuBuilder& InMenuBuilder);`
- L31 _public function_ `const TraceServices::IAnalysisSession& GetAnalysisSession() const` — Get the last cached analysis session
- L37 _public function_ `bool IsAnalysisSessionValid() const` — Check whether the analysis session is valid
- L43 _public prototype_ `void ToggleSlateTrack();` — Show/Hide the slate track
- L46 _public prototype_ `void ToggleWidgetUpdateTrack();` — Show/Hide the Update track
- L49 _public prototype_ `void OpenSlateFrameTab() const;` — Open a resume of the frame
- L52 _public function_ `UE::Insights::Timing::ITimingViewSession* GetTimingView() const` — The timing view for the session
- L59 _private member_ `const TraceServices::IAnalysisSession* AnalysisSession;` — Cached analysis session, set in Tick()
- L62 _private member_ `UE::Insights::Timing::ITimingViewSession* TimingViewSession;` — Cached timing view session, set in OnBeginSession/OnEndSession
- L65 _private member_ `TSharedPtr<FSlateFrameGraphTrack> SlateFrameGraphTrack;` — All the tracks we manage
- L68 _private member_ `TSharedPtr<FSlateWidgetUpdateStepsTimingTrack> WidgetUpdateStepsGraphTrack;` — The widget timing track
- L71 _private member_ `bool bApplicationTracksEnabled;` — Flags controlling whether the Application Tick tracks is enabled
- L73 _private member_ `bool bWidgetUpdateStepsTracksEnabled;` — Flags controlling whether the Layout/Paint tracks is enabled

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace TraceServices`
- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Insights` (scope `UE`)
- L8 _namespace_ `namespace Timing` (scope `UE::Insights`)
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Insights` (scope `UE`)
- L9 _namespace_ `namespace Timing` (scope `UE::Insights`)
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SlateInsights` (scope `UE`)
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SlateInsights` (scope `UE`)
- L15 _namespace_ `namespace UE`
- L17 _namespace_ `namespace SlateInsights` (scope `UE`)

### `Plugins/Slate/SlateInsights/Source/SlateInsights/Private/SlateTraceModule.h` (Private)


#### class `UE::SlateInsights::FSlateTraceModule`  
`class FSlateTraceModule : public TraceServices::IModule`  
_L14-27_
- inherits: `TraceServices::IModule`
- L18 _public prototype_ `virtual void GetModuleInfo(TraceServices::FModuleInfo& OutModuleInfo) override;`
- L19 _public prototype_ `virtual void OnAnalysisBegin(TraceServices::IAnalysisSession& Session) override;`
- L20 _public prototype_ `virtual void GetLoggers(TArray<const TCHAR *>& OutLoggers) override;`
- L21 _public prototype_ `virtual void GenerateReports(const TraceServices::IAnalysisSession& Session, const TCHAR* CmdLine, const TCHAR* OutputDirectory) override;`
- L22 _public function_ `virtual const TCHAR* GetCommandLineArgument() override`
- L26 _private member_ `static FName ModuleName;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SlateInsights` (scope `UE`)

### `Plugins/Slate/SlateInsights/Source/SlateInsights/Private/SlateWidgetUpdateStepsTimingTrack.h` (Private)


#### class `UE::SlateInsights::FSlateWidgetUpdateStepsTimingTrack`  
`class FSlateWidgetUpdateStepsTimingTrack : public FTimingEventsTrack`  
_L17-87_
- inherits: `FTimingEventsTrack`
- desc: Timing track for Widget Update (Prepass/Paint).
- L20 _private typedef_ `using Super = FTimingEventsTrack;`
- L23 _public prototype_ `FSlateWidgetUpdateStepsTimingTrack(const FSlateTimingViewSession& InSharedData);`
- L26 _public prototype_ `virtual void BuildDrawState(ITimingEventsTrackDrawStateBuilder& Builder, const ITimingTrackUpdateContext& Context) override;`
- L28 _public prototype_ `virtual void InitTooltip(FTooltipDrawState& InOutTooltip, const ITimingEvent& InTooltipEvent) const override;` — virtual void BuildFilteredDrawState(ITimingEventsTrackDrawStateBuilder& Builder, const ITimingTrackUpdateContext& Context) override;
- L29 _public prototype_ `virtual void BuildContextMenu(FMenuBuilder& MenuBuilder) override;`
- L33 _protected prototype_ `virtual const TSharedPtr<const ITimingEvent> GetEvent(double InTime, double SecondsPerPixel, int32 Depth) const override;`
- L36 _private function_ `void SetShowChildWhenTrackIsTooSmall(bool bValue)`
- L41 _private function_ `void ToggleShowChildWhenTrackIsTooSmall()`
- L46 _private function_ `bool IsHideChildWhenTrackIsTooSmall() const`
- L51 _private function_ `void SetShowPaintEvent(bool bValue)`
- L56 _private function_ `void ToggleShowPaintEvent()`
- L61 _private function_ `bool IsShowPaintEvents() const`
- L66 _private function_ `void SetShowLayoutEvent(bool bValue)`
- L71 _private function_ `void ToggleShowLayoutEvent()`
- L76 _private function_ `bool IsShowLayoutEvents() const`
- L82 _private member_ `const FSlateTimingViewSession& SharedData;` — The shared data
- L84 _private member_ `bool bShowChildWhenTrackIsTooSmall = false;`
- L85 _private member_ `bool bShowPaintEvent = true;`
- L86 _private member_ `bool bShowLayoutEvent = true;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SlateInsights` (scope `UE`)
