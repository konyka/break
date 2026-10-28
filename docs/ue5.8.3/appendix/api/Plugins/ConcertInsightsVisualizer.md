# Plugins / ConcertInsightsVisualizer

- module root: `Plugins/Developer/Concert/ConcertInsights/ConcertInsightsVisualizer/Source/ConcertInsightsVisualizer`
- headers: 29; symbols: 385
- symbol kinds: class=12, delegate=1, enum=2, enumerator=13, function=76, member=89, namespace=68, prototype=92, struct=24, typedef=7, union=1
- PrivateDependencyModuleNames: CoreUObject, Projects, Slate, SlateCore, TraceAnalysis, TraceInsights, TraceServices
- PublicDependencyModuleNames: Core

### `Plugins/Developer/Concert/ConcertInsights/ConcertInsightsVisualizer/Source/ConcertInsightsVisualizer/Private/ConcertInsightsStyle.h` (Private)


#### class `UE::ConcertInsightsVisualizer::FConcertInsightsStyle`  
`class FConcertInsightsStyle`  
_L10-24_
- L14 _public prototype_ `static void Initialize();`
- L15 _public prototype_ `static void Shutdown();`
- L17 _public prototype_ `static TSharedPtr<class ISlateStyle> Get();`
- L18 _public prototype_ `static FName GetStyleSetName();`
- L22 _private prototype_ `static FString InContent(const FString& RelativePath, const ANSICHAR* Extension);`
- L23 _private member_ `static TSharedPtr<FSlateStyleSet> StyleSet;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ConcertInsightsVisualizer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertInsights/ConcertInsightsVisualizer/Source/ConcertInsightsVisualizer/Private/ConcertInsightsVisualizer.h` (Private)


#### class `UE::ConcertInsightsVisualizer::FConcertInsightsVisualizerModule`  
`class FConcertInsightsVisualizerModule : public IConcertInsightsVisualizerModule`  
_L13-32_
- inherits: `IConcertInsightsVisualizerModule`
- L18 _public prototype_ `virtual void StartupModule() override;`
- L19 _public prototype_ `virtual void ShutdownModule() override;`
- L25 _private member_ `FConcertTraceInsightsModule ConcertInsightsModule;` — Adds Concert analyzer and provider.
- L27 _private member_ `FConcertTimingViewExtender TimingViewExtender;` — Adds tracks to the timing view as outlined in Trace/ConcertProtocolTrace.h.
- L30 _private prototype_ `void RegisterInsightsExtensions();` — Registers all Concert specific modular features with Insights.
- L31 _private prototype_ `void UnregisterInsightsExtensions();`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ConcertInsightsVisualizer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertInsights/ConcertInsightsVisualizer/Source/ConcertInsightsVisualizer/Private/Extension/ConcertTimingViewExtender.h` (Private)


#### class `UE::ConcertInsightsVisualizer::FConcertTimingViewExtender`  
`class FConcertTimingViewExtender : public UE::Insights::Timing::ITimingViewExtender`  
_L13-33_
- inherits: `UE::Insights::Timing::ITimingViewExtender`
- desc: Keeps track of FConcertTimingViewSession per analytics session.
- L18 _public prototype_ `virtual void OnBeginSession(UE::Insights::Timing::ITimingViewSession& InSession) override;`
- L19 _public prototype_ `virtual void OnEndSession(UE::Insights::Timing::ITimingViewSession& InSession) override;`
- L20 _public prototype_ `virtual void Tick(UE::Insights::Timing::ITimingViewSession& InTimingSession, const TraceServices::IAnalysisSession& InAnalysisSession) override;`
- L21 _public prototype_ `virtual void ExtendFilterMenu(UE::Insights::Timing::ITimingViewSession& InSession, FMenuBuilder& InMenuBuilder) override;`
- L32 _private member_ `TMap<UE::Insights::Timing::ITimingViewSession*, FPerSessionData> PerSessionDataMap;` — /  The data we host per-session

#### struct `UE::ConcertInsightsVisualizer::FConcertTimingViewExtender::FPerSessionData`  
`struct FPerSessionData`  
_L26-29_
- L28 _public member_ `TUniquePtr<FConcertTimingViewSession> SharedData;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ConcertInsightsVisualizer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertInsights/ConcertInsightsVisualizer/Source/ConcertInsightsVisualizer/Private/Extension/ConcertTimingViewSession.h` (Private)


#### class `UE::ConcertInsightsVisualizer::FConcertTimingViewSession`  
`class FConcertTimingViewSession : public FNoncopyable`  
_L19-38_
- inherits: `FNoncopyable`
- desc: Adds tracks to the timing view as outlined in Trace/ConcertProtocolTrace.h.
- L24 _public prototype_ `void OnBeginSession(UE::Insights::Timing::ITimingViewSession& InSession);` — Mirrors the ITimingViewExtender interface - called by FConcertTimingViewExtender
- L25 _public prototype_ `void OnEndSession(UE::Insights::Timing::ITimingViewSession& InSession);`
- L26 _public prototype_ `void Tick(UE::Insights::Timing::ITimingViewSession& InTimingSession, const TraceServices::IAnalysisSession& InAnalysisSession);`
- L27 _public prototype_ `void ExtendFilterMenu(UE::Insights::Timing::ITimingViewSession& InSession, FMenuBuilder& InMenuBuilder);`
- L32 _private member_ `TSharedPtr<FProtocolTrack> ObjectTrack;` — Generates the rows in the Insights UI.
- L35 _private member_ `TSharedPtr<FTraceAggregator> TraceAggregator;` — Traces related files and exposes their data.
- L37 _private prototype_ `void ConditionalInitTraceAggregator(const TraceServices::IAnalysisSession& InAnalysisSession);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Insights` (scope `UE`)
- L10 _namespace_ `namespace Timing` (scope `UE::Insights`)
- L11 _namespace_ `namespace TraceServices`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace ConcertInsightsVisualizer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertInsights/ConcertInsightsVisualizer/Source/ConcertInsightsVisualizer/Private/Extension/ConcertTraceInsightsModule.h` (Private)


#### class `UE::ConcertInsightsVisualizer::FConcertTraceInsightsModule`  
`class FConcertTraceInsightsModule : public TraceServices::IModule`  
_L10-18_
- inherits: `TraceServices::IModule`
- desc: Adds the Concert analyzer and provider when a session starts.
- L15 _public prototype_ `virtual void GetModuleInfo(TraceServices::FModuleInfo& OutModuleInfo) override;`
- L16 _public prototype_ `virtual void OnAnalysisBegin(TraceServices::IAnalysisSession& Session) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ConcertInsightsVisualizer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertInsights/ConcertInsightsVisualizer/Source/ConcertInsightsVisualizer/Private/Extension/Track/ProtocolTrack.h` (Private)


#### class `UE::ConcertInsightsVisualizer::FProtocolTrack`  
`class FProtocolTrack : public FTimingEventsTrack`  
_L13-66_
- inherits: `FTimingEventsTrack`
- L17 _public prototype_ `FProtocolTrack(const TraceServices::IAnalysisSession& Session UE_LIFETIMEBOUND, const FProtocolMultiEndpointProvider& Provider UE_LIFETIMEBOUND);`
- L20 _public prototype_ `void ToggleShowObjectFullPaths();` — Toggles whether objects are displayed with full object paths or just the bit after PersistentLevel.
- L22 _public function_ `bool ShouldShowFullObjectPaths() const` — @return Whether objects are displayed with full object paths or just the bit after PersistentLevel
- L25 _public prototype_ `virtual void BuildDrawState(ITimingEventsTrackDrawStateBuilder& Builder, const ITimingTrackUpdateContext& Context) override;`
- L26 _public prototype_ `virtual void InitTooltip(FTooltipDrawState& InOutTooltip, const ITimingEvent& InTooltipEvent) const override;`
- L27 _public prototype_ `virtual const TSharedPtr<const ITimingEvent> SearchEvent(const FTimingEventSearchParameters& InSearchParameters) const override;`
- L51 _private member_ `const TraceServices::IAnalysisSession& Session;`
- L52 _private member_ `const FProtocolMultiEndpointProvider& Provider;`
- L55 _private member_ `bool bShouldShowFullObjectPaths = false;` — Whether the 1st row of every sequence should show the full object path or just the part behind .PersistentLevel
- L57 _private prototype_ `void BuildSequences(FBuildContext& Context) const;`
- L58 _private prototype_ `void BuildSequence(FBuildContext& Context, const FSequenceScopeInfo& Info) const;`
- L59 _private prototype_ `uint32 BuildCpuTimeline( FBuildContext& Context, const FEndpointScopeInfo& Info ) const;`
- L65 _private prototype_ `FString GetObjectDisplayString(const TCHAR* ObjectPath) const;` — Gets the final display string of ObjectPath (given the value of bShouldShowFullObjectPaths).

#### struct `UE::ConcertInsightsVisualizer::FProtocolTrack::FBuildContext`  
`struct FBuildContext`  
_L32-49_
- L34 _public member_ `ITimingEventsTrackDrawStateBuilder& Builder;`
- L35 _public member_ `const ITimingTrackUpdateContext& TimingContext;`
- L37 _public member_ `const double StartTime = GetViewport().GetStartTime();`
- L38 _public member_ `const double EndTime = GetViewport().GetEndTime();`
- L39 _public member_ `const double SecondsPerPixel = 1.0 / GetViewport().GetScaleX();`
- L41 _public member_ `uint32 CurrentDepthOffset = 0;`
- L43 _public function_ `FBuildContext(ITimingEventsTrackDrawStateBuilder& Builder, const ITimingTrackUpdateContext& Context) : Builder(Builder) , TimingContext(Context)`
- L48 _public function_ `const FTimingTrackViewport& GetViewport() const`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ConcertInsightsVisualizer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertInsights/ConcertInsightsVisualizer/Source/ConcertInsightsVisualizer/Private/LogConcertInsights.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogConcertInsights, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogConcertInsights, Log, All);`

### `Plugins/Developer/Concert/ConcertInsights/ConcertInsightsVisualizer/Source/ConcertInsightsVisualizer/Private/Trace/Analysis/IProtocolDataTarget.h` (Private)


#### class `UE::ConcertInsightsVisualizer::IProtocolDataTarget`  
`class IProtocolDataTarget`  
_L23-35_
- desc: Target for receiving data from FProtocolEndpointAnalyzer. This abstracts what is done with the data, which is important for aggregation: - The main .utrace, which is the one that is technically open, is processed on the main thread and directly inserted into FProtocolMultiEndpointProvider. - The aggregated .utrace files are processed on a separate thread. The analyzed data must be synchronized with the main thread which is controlled by FProtocolDataQueue. FProtocolMultiEndpointProvider will dequeue ready data from FProtocolDataQueue on Tick.
- L27 _public prototype_ `virtual void AppendInit(FInitMessage Message) = 0;`
- L28 _public prototype_ `virtual void AppendObjectTraceBegin(FObjectTraceBeginMessage Message) = 0;`
- L29 _public prototype_ `virtual void AppendObjectTraceEnd(FObjectTraceEndMessage Message) = 0;`
- L30 _public prototype_ `virtual void AppendObjectTransmissionStart(FObjectTransmissionStartMessage Message) = 0;`
- L31 _public prototype_ `virtual void AppendObjectTransmissionReceive(FObjectTransmissionReceiveMessage Message) = 0;`
- L32 _public prototype_ `virtual void AppendObjectSink(FObjectSinkMessage Message) = 0;`
- L34 _public prototype_ `virtual ~IProtocolDataTarget() = default;`

#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace ConcertInsightsVisualizer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertInsights/ConcertInsightsVisualizer/Source/ConcertInsightsVisualizer/Private/Trace/Analysis/ProtocolDataQueue.h` (Private)


#### struct `UE::ConcertInsightsVisualizer::FProtocolQueuedItem`  
`struct FProtocolQueuedItem`  
_L26-53_
- L45 _public member_ `} Message;`
- L48 _public member_ `EMessageType Type;` — Indicates which data in Message has been written to.
- L50 _public function_ `FProtocolQueuedItem() : Message(), Type(EMessageType::None)`
- L52 _public function_ `template<typename TMessage> FProtocolQueuedItem(const TMessage& Message) : Message(Message), Type(TMessage::Type())`

#### union `UE::ConcertInsightsVisualizer::FProtocolQueuedItem::FMessage`  
`union FMessage`  
_L28-45_
- L30 _public member_ `FInitMessage Init;`
- L31 _public member_ `FObjectTraceBeginMessage ObjectTraceBegin;`
- L32 _public member_ `FObjectTraceEndMessage ObjectTraceEnd;`
- L33 _public member_ `FObjectTransmissionStartMessage TransmissionStart;`
- L34 _public member_ `FObjectTransmissionReceiveMessage TransmissionReceive;`
- L35 _public member_ `FObjectSinkMessage Sink;`
- L37 _public prototype_ `FMessage() = default;`
- L38 _public function_ `FMessage(const FInitMessage& InitMessage) : Init(InitMessage)`
- L39 _public function_ `FMessage(const FObjectTraceBeginMessage& ObjectTraceBegin) : ObjectTraceBegin(ObjectTraceBegin)`
- L40 _public function_ `FMessage(const FObjectTraceEndMessage& ObjectTraceEnd) : ObjectTraceEnd(ObjectTraceEnd)`
- L41 _public function_ `FMessage(const FObjectTransmissionStartMessage& TransmissionStart) : TransmissionStart(TransmissionStart)`
- L42 _public function_ `FMessage(const FObjectTransmissionReceiveMessage& TransmissionEnd) : TransmissionReceive(TransmissionEnd)`
- L43 _public function_ `FMessage(const FObjectSinkMessage& Sink) : Sink(Sink)`

#### class `UE::ConcertInsightsVisualizer::FProtocolDataQueue`  
`class FProtocolDataQueue : public IProtocolDataTarget`  
_L61-76_
- inherits: `IProtocolDataTarget`
- desc: Used to synchronize analyzed data between two threads. Aggregated .utrace files are analyzed by FProtocolEndpointAnalyzer on a separate thread. FProtocolMultiEndpoint will load the data every tick on the main thread.
- L66 _public member_ `TQueue<FProtocolQueuedItem> MessageQueue;` — Queue of messages in the call order of the below functions.
- L69 _public function_ `virtual void AppendInit(FInitMessage Message) override`
- L70 _public function_ `virtual void AppendObjectTraceBegin(FObjectTraceBeginMessage Message) override`
- L71 _public function_ `virtual void AppendObjectTraceEnd(FObjectTraceEndMessage Message) override`
- L72 _public function_ `virtual void AppendObjectTransmissionStart(FObjectTransmissionStartMessage Message) override`
- L73 _public function_ `virtual void AppendObjectTransmissionReceive(FObjectTransmissionReceiveMessage Message) override`
- L74 _public function_ `virtual void AppendObjectSink(FObjectSinkMessage Message) override`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace ConcertInsightsVisualizer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertInsights/ConcertInsightsVisualizer/Source/ConcertInsightsVisualizer/Private/Trace/Analysis/ProtocolEndpointAnalyzer.h` (Private)


#### class `UE::ConcertInsightsVisualizer::FProtocolEndpointAnalyzer`  
`class FProtocolEndpointAnalyzer : public Trace::IAnalyzer`  
_L14-47_
- inherits: `Trace::IAnalyzer`
- desc: Processes raw .utrace data, structures it into messages, and passes them to a IProtocolDataTarget.
- L22 _public prototype_ `FProtocolEndpointAnalyzer(TraceServices::IAnalysisSession& Session UE_LIFETIMEBOUND, IProtocolDataTarget& DataTarget UE_LIFETIMEBOUND);` — @param Session Caller is responsible for ensuring it outlives the constructed object. @param DataTarget Caller is responsible for ensuring it outlives the constructed object.
- L25 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L26 _public function_ `virtual void OnAnalysisEnd() override`
- L27 _public prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L43 _private member_ `TraceServices::IAnalysisSession& Session;` — The session this provider operates on.
- L46 _private member_ `IProtocolDataTarget& DataTarget;` — Stores the analyzed data.

#### enum `UE::ConcertInsightsVisualizer::FProtocolEndpointAnalyzer::(anonymous)`  
``  
_L33-40_

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace TraceServices`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ConcertInsightsVisualizer` (scope `UE`)
- L34 _enumerator_ `RouteId_Init` (scope `UE::ConcertInsightsVisualizer::FProtocolEndpointAnalyzer::__anon73dd74d10103`)
- L35 _enumerator_ `RouteId_ObjectTraceBegin` (scope `UE::ConcertInsightsVisualizer::FProtocolEndpointAnalyzer::__anon73dd74d10103`)
- L36 _enumerator_ `RouteId_ObjectTraceEnd` (scope `UE::ConcertInsightsVisualizer::FProtocolEndpointAnalyzer::__anon73dd74d10103`)
- L37 _enumerator_ `RouteId_ObjectTransmissionStart` (scope `UE::ConcertInsightsVisualizer::FProtocolEndpointAnalyzer::__anon73dd74d10103`)
- L38 _enumerator_ `RouteId_ObjectTransmissionReceive` (scope `UE::ConcertInsightsVisualizer::FProtocolEndpointAnalyzer::__anon73dd74d10103`)
- L39 _enumerator_ `RouteId_ObjectSink` (scope `UE::ConcertInsightsVisualizer::FProtocolEndpointAnalyzer::__anon73dd74d10103`)

### `Plugins/Developer/Concert/ConcertInsights/ConcertInsightsVisualizer/Source/ConcertInsightsVisualizer/Private/Trace/Messages/BaseObjectMessage.h` (Private)


#### struct `UE::ConcertInsightsVisualizer::FBaseObjectMessage`  
`struct FBaseObjectMessage`  
_L19-30_
- desc: Shared data for messages about objects.
- L21 _public member_ `FProtocolId Protocol;`
- L22 _public member_ `FSequenceId SequenceId;`
- L24 _public member_ `const TCHAR* ObjectPath;` — Points to string stored in IAnalysisSession::StoreString
- L26 _public prototype_ `FBaseObjectMessage() = default;`
- L27 _public prototype_ `FBaseObjectMessage(const Trace::IAnalyzer::FEventData& EventData, TraceServices::IAnalysisSession& Session UE_LIFETIMEBOUND);`
- L29 _public function_ `FSoftObjectPath GetSoftObjectPath() const`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace TraceServices`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace ConcertInsightsVisualizer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertInsights/ConcertInsightsVisualizer/Source/ConcertInsightsVisualizer/Private/Trace/Messages/EMessageType.h` (Private)


#### enum `UE::ConcertInsightsVisualizer::EMessageType`  
`enum class EMessageType : uint8`  
_L9-18_
- L11 _public enumerator_ `None`
- L12 _public enumerator_ `Init`
- L13 _public enumerator_ `ObjectTraceBegin`
- L14 _public enumerator_ `ObjectTraceEnd`
- L15 _public enumerator_ `ObjectTransmissionStart`
- L16 _public enumerator_ `ObjectTransmissionReceive`
- L17 _public enumerator_ `ObjectSink`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ConcertInsightsVisualizer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertInsights/ConcertInsightsVisualizer/Source/ConcertInsightsVisualizer/Private/Trace/Messages/InitMessage.h` (Private)


#### struct `UE::ConcertInsightsVisualizer::FInitMessage`  
`struct FInitMessage`  
_L20-55_
- L22 _public prototype_ `FInitMessage() = default;`
- L23 _public prototype_ `FInitMessage(const Trace::IAnalyzer::FEventData& EventData, const Trace::IAnalyzer::FEventTime& EventTime, TraceServices::IAnalysisSession& Session UE_LIFETIMEBOUND);`
- L25 _public function_ `static constexpr EMessageType Type()`
- L27 _public function_ `ConcertTrace::EConcertTraceVersion GetVersion() const`
- L28 _public function_ `TOptional<FGuid> GetEndpointId() const`
- L30 _public function_ `FDateTime GetTraceInitTimeUtc() const` — The UTC time reported on the sending machine when the init event was started. Used to correlate cycles across multiple machines.
- L32 _public function_ `double GetStartTime() const` — Seconds since start of the trace.
- L34 _public function_ `TOptional<const TCHAR*> GetClientDisplayName() const` — Points to string stored in IAnalysisSession::StoreString
- L35 _public function_ `bool IsServer() const`
- L39 _private member_ `ConcertTrace::EConcertTraceVersion Version;`
- L41 _private member_ `bool bHasEndpointId;`
- L42 _private member_ `uint32 EndpointId_A;`
- L43 _private member_ `uint32 EndpointId_B;`
- L44 _private member_ `uint32 EndpointId_C;`
- L45 _private member_ `uint32 EndpointId_D;`
- L48 _private member_ `int64 TraceInitUtc_Ticks;` — The UTC time reported on the sending machine when the init event was started. Used to correlate cycles across multiple machines.
- L50 _private member_ `double StartTime;` — Seconds since start of the trace.
- L53 _private member_ `const TCHAR* ClientDisplayName;` — Points to string stored in IAnalysisSession::StoreString
- L54 _private member_ `bool bIsServer;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace ConcertTrace` (scope `UE`)
- L16 _namespace_ `namespace TraceServices`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace ConcertInsightsVisualizer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertInsights/ConcertInsightsVisualizer/Source/ConcertInsightsVisualizer/Private/Trace/Messages/ObjectSinkMessage.h` (Private)


#### struct `UE::ConcertInsightsVisualizer::FObjectSinkMessage`  
`struct FObjectSinkMessage : FBaseObjectMessage`  
_L15-31_
- inherits: `FBaseObjectMessage`
- L18 _public member_ `double Time;` — The time at which the message was generated. Seconds since start of trace.
- L21 _public member_ `const TCHAR* SinkName;` — Points to string stored in IAnalysisSession::StoreString
- L23 _public prototype_ `FObjectSinkMessage() = default;`
- L24 _public prototype_ `FObjectSinkMessage( const Trace::IAnalyzer::FEventData& EventData, const Trace::IAnalyzer::FEventTime& EventTime, TraceServices::IAnalysisSession& Session UE_LIFETIMEBOUND );`
- L30 _public function_ `static constexpr EMessageType Type()`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace ConcertInsightsVisualizer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertInsights/ConcertInsightsVisualizer/Source/ConcertInsightsVisualizer/Private/Trace/Messages/ObjectTraceMessage.h` (Private)


#### struct `UE::ConcertInsightsVisualizer::FObjectTraceMessage`  
`struct FObjectTraceMessage : FBaseObjectMessage`  
_L13-25_
- inherits: `FBaseObjectMessage`
- L16 _public member_ `double Time;` — Time of the event. Seconds since start of trace.
- L17 _public member_ `const TCHAR* EventName;`
- L19 _public prototype_ `FObjectTraceMessage() = default;`
- L20 _public prototype_ `FObjectTraceMessage( const Trace::IAnalyzer::FEventData& EventData, const Trace::IAnalyzer::FEventTime& EventTime, TraceServices::IAnalysisSession& Session UE_LIFETIMEBOUND );`

#### struct `UE::ConcertInsightsVisualizer::FObjectTraceBeginMessage`  
`struct FObjectTraceBeginMessage : FObjectTraceMessage`  
_L28-39_
- inherits: `FObjectTraceMessage`
- L30 _public prototype_ `FObjectTraceBeginMessage() = default;`
- L31 _public function_ `FObjectTraceBeginMessage( const Trace::IAnalyzer::FEventData& EventData, const Trace::IAnalyzer::FEventTime& EventTime, TraceServices::IAnalysisSession& Session UE_LIFETIMEBOUND ) : FObjectTraceMessage(EventData, EventTime, Session)`
- L38 _public function_ `static constexpr EMessageType Type()`

#### struct `UE::ConcertInsightsVisualizer::FObjectTraceEndMessage`  
`struct FObjectTraceEndMessage : FObjectTraceMessage`  
_L42-53_
- inherits: `FObjectTraceMessage`
- L44 _public prototype_ `FObjectTraceEndMessage() = default;`
- L45 _public function_ `FObjectTraceEndMessage( const Trace::IAnalyzer::FEventData& EventData, const Trace::IAnalyzer::FEventTime& EventTime, TraceServices::IAnalysisSession& Session UE_LIFETIMEBOUND ) : FObjectTraceMessage(EventData, EventTime, Session)`
- L52 _public function_ `static constexpr EMessageType Type()`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ConcertInsightsVisualizer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertInsights/ConcertInsightsVisualizer/Source/ConcertInsightsVisualizer/Private/Trace/Messages/ObjectTransmissionReceiveMessage.h` (Private)


#### struct `UE::ConcertInsightsVisualizer::FObjectTransmissionReceiveMessage`  
`struct FObjectTransmissionReceiveMessage : FBaseObjectMessage`  
_L15-28_
- inherits: `FBaseObjectMessage`
- L18 _public member_ `double Time;` — The time at which the message was generated. Seconds since start of trace.
- L20 _public prototype_ `FObjectTransmissionReceiveMessage() = default;`
- L21 _public prototype_ `FObjectTransmissionReceiveMessage( const Trace::IAnalyzer::FEventData& EventData, const Trace::IAnalyzer::FEventTime& EventTime, TraceServices::IAnalysisSession& Session UE_LIFETIMEBOUND );`
- L27 _public function_ `static constexpr EMessageType Type()`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace ConcertInsightsVisualizer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertInsights/ConcertInsightsVisualizer/Source/ConcertInsightsVisualizer/Private/Trace/Messages/ObjectTransmissionStartMessage.h` (Private)


#### struct `UE::ConcertInsightsVisualizer::FObjectTransmissionStartMessage`  
`struct FObjectTransmissionStartMessage : FBaseObjectMessage`  
_L15-39_
- inherits: `FBaseObjectMessage`
- L17 _public prototype_ `FObjectTransmissionStartMessage() = default;`
- L18 _public prototype_ `FObjectTransmissionStartMessage( const Trace::IAnalyzer::FEventData& EventData, const Trace::IAnalyzer::FEventTime& EventTime, TraceServices::IAnalysisSession& Session UE_LIFETIMEBOUND );`
- L24 _public function_ `static constexpr EMessageType Type()`
- L26 _public function_ `FGuid GetDestinationEdnpointId() const`
- L27 _public function_ `double GetTime() const`
- L32 _private member_ `int64 DestinationEndpointId_A;` — Used to form FGuid for the destination endpoint
- L33 _private member_ `int64 DestinationEndpointId_B;`
- L34 _private member_ `int64 DestinationEndpointId_C;`
- L35 _private member_ `int64 DestinationEndpointId_D;`
- L38 _private member_ `double Time;` — The time at which the message was generated. Seconds since start of trace.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace ConcertInsightsVisualizer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertInsights/ConcertInsightsVisualizer/Source/ConcertInsightsVisualizer/Private/Trace/ObjectSequence/ObjectNetworkScope.h` (Private)


#### struct `UE::ConcertInsightsVisualizer::FObjectNetworkScope`  
`struct FObjectNetworkScope`  
_L14-25_
- desc: Nested right under FObjectSequence. Indicates on which client the object was (or whether it was in transit).
- L21 _public member_ `TOptional<FEndpointId> ProcessingEndpoint;` — The endpoint that corresponds to this scope, if any. Unset means that this is a network transit of the packet from one to another endpoint. FEndpointId can be used to resolve the display name in FProtocolMultiEndpointProvider.
- L23 _public function_ `bool IsEndpoint() const`
- L24 _public function_ `bool IsTransportAcrossNetwork() const`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ConcertInsightsVisualizer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertInsights/ConcertInsightsVisualizer/Source/ConcertInsightsVisualizer/Private/Trace/ObjectSequence/ObjectProcessingStep.h` (Private)


#### struct `UE::ConcertInsightsVisualizer::FObjectProcessingStep`  
`struct FObjectProcessingStep`  
_L10-14_
- desc: Nested under FObjectNetworkScope. Describes what an endpoint spent CPU time on while processing an object in a sequence.
- L13 _public member_ `const TCHAR* EventName;` — Name of the processing step

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ConcertInsightsVisualizer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertInsights/ConcertInsightsVisualizer/Source/ConcertInsightsVisualizer/Private/Trace/ObjectSequence/ObjectSequence.h` (Private)


#### struct `UE::ConcertInsightsVisualizer::FObjectSequence`  
`struct FObjectSequence`  
_L13-17_
- desc: A sequence is a time range in which an object was processed across multiple endpoints. This data is displayed top-most event.
- L16 _public member_ `FSequenceId SequenceId;` — ID for the object update.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ConcertInsightsVisualizer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertInsights/ConcertInsightsVisualizer/Source/ConcertInsightsVisualizer/Private/Trace/ProtocolMultiEndpointProvider.h` (Private)


#### class `UE::ConcertInsightsVisualizer::FProtocolMultiEndpointProvider`  
`class FProtocolMultiEndpointProvider : public TraceServices::IProvider , public TraceServices::IEditableProvider , public IProtocolDataTarget`  
_L44-245_
- inherits: `TraceServices::IProvider,TraceServices::IEditableProvider,IProtocolDataTarget`
- desc: This is the final provider that is visualized in Insights. It aggregates multiple FSingleProtocolEndpointProvider into timelines that are then displayed. There is a main provider, which is the one for which the .utrace is opened, to which all other traces are made relative. This is what the data will be visualized as in the Insights graph: [--------------------------------------------- FObjectSequence - ActorName - Sequence 1 --------------------------------------------] [--------- FObjectNetworkScope - Client 1---------][FObjectNetworkScope - Transit][--------- FObjectNetworkScope - Client 2---------] [FObjectProcessingStep 1] [FObjectProcessingStep 2]                               [FObjectProcessingStep 1] [FObjectProcessingStep 2] Sequence 2 would go under this, etc.
- L52 _public member_ `static const FName ProviderName;` — ID used for registration with Insights.
- L54 _public prototype_ `FProtocolMultiEndpointProvider(TraceServices::IAnalysisSession& Session UE_LIFETIMEBOUND);`
- L58 _public prototype_ `const TCHAR* GetEndpointDisplayName(FEndpointId EndpointId) const;` — Utility for getting the display name of a particular endpoint. Returns nullptr if invalid.
- L61 _public prototype_ `void EnumerateProtocols(TFunctionRef<TraceServices::EEventEnumerate(FProtocolId)> Callback) const;` — Gets all protocols for which objects were traced.
- L63 _public prototype_ `void EnumerateObjects(FProtocolId Protocol, TFunctionRef<TraceServices::EEventEnumerate(FObjectPath Object)> Callback) const;` — Gets all objects for which data was traced.
- L65 _public prototype_ `void EnumerateEndpointsInSequence(const FSequenceScopeInfo& Info, TFunctionRef<TraceServices::EEventEnumerate(FEndpointId EndpointId)> Callback) const;` — Gets all endpoints that participate in the given sequence.
- L68 _public prototype_ `void EnumerateSequences(double Start, double End, const FObjectScopeInfo&, TFunctionRef<TraceServices::EEventEnumerate(FSequenceId Sequence)> Callback) const;` — 1st row. Gets the timeline of all sequences for a particular object.
- L71 _public prototype_ `TOptional<FVector2d> GetSequenceBounds(const FSequenceScopeInfo& Info) const;` — @return Start and end time of the sequence relative to the main trace file.
- L74 _public prototype_ `void EnumerateNetworkScopes(double Start, double End, const FSequenceScopeInfo& Info, TFunctionRef<TraceServices::EEventEnumerate(double StartTime, double EndTime, const FObjectNetworkScope& NetworkScope)> Callback) const;` — 2nd row. Lists out all network scopes that are active in the given time range. A scope is a time period in which an endpoint is doing processing or the object is in transit.
- L77 _public prototype_ `void ReadProcessingStepTimeline(const FEndpointScopeInfo& Info, TFunctionRef<void(const TraceServices::ITimeline<FObjectProcessingStep>& Timeline)> Callback) const;` — 3rd row+. Gets the timeline of all processing steps performed by a specific endpoint for a particular object sequence.
- L80 _public prototype_ `virtual void AppendInit(FInitMessage Message) override;`
- L81 _public function_ `virtual void AppendObjectTraceBegin(FObjectTraceBeginMessage Message) override`
- L82 _public function_ `virtual void AppendObjectTraceEnd(FObjectTraceEndMessage Message) override`
- L83 _public function_ `virtual void AppendObjectTransmissionStart(FObjectTransmissionStartMessage Message) override`
- L84 _public function_ `virtual void AppendObjectTransmissionReceive(FObjectTransmissionReceiveMessage Message) override`
- L85 _public function_ `virtual void AppendObjectSink(FObjectSinkMessage Message) override`
- L90 _private typedef_ `using FEndpointCpuTimeline = TraceServices::TMonotonicTimeline<FObjectProcessingStep>;`
- L91 _private typedef_ `using FNetworkScopeTimeline = TraceServices::TIntervalTimeline<FEndpointId>;`
- L92 _private typedef_ `using FSequenceEventTimeline = TraceServices::TPointTimeline<FSequenceId>;`
- L179 _private member_ `TraceServices::IAnalysisSession& Session;` — The main session this provider is for. Outlives this object.
- L181 _private member_ `FTraceAggregator Aggregator;` — Traces related files and exposes their data. Set once the session starts.
- L183 _private member_ `const FTSTicker::FDelegateHandle TickHandle;` — Handle to ProcessGeneratedTraceData.
- L186 _private member_ `TSet<FProtocolId> ActiveProtocols;` — Keeps track of all the protocols encountered so far.
- L188 _private member_ `TMap<FObjectScopeInfo, FPerObjectData> PerObjectData;`
- L189 _private member_ `TMap<FSequenceScopeInfo, FPerSequenceData> PerSequenceData;`
- L190 _private member_ `TMap<FEndpointScopeInfo, FPerSequenceEndpointData> PerSequenceEndpointData;`
- L193 _private member_ `TOptional<FInitMessage> MainTraceInitData;` — Contains the init data found in the Session's trace.
- L195 _private member_ `TMap<FEndpointId, FInitMessage> EndpointInitData;` — Maps .utrace file ID to the init data found in that file. The endpoint ID is the same as the .utrace file ID. Does not contain MainTraceInitData.
- L197 _private function_ `uint64 GetMainTraceId() const`
- L200 _private prototype_ `bool ProcessGeneratedTraceData(float DeltaTime);` — Process the data from Aggregator. This is run after Slate ticks: take a look at FUserInterfaceCommand::Run.
- L201 _private prototype_ `void ProcessAggregatedTraceData(FEndpointId EndpointId, FProtocolDataQueue& DataQueue);`
- L203 _private prototype_ `void ProcessInit(FEndpointId EndpointId, const FInitMessage& Init);`
- L204 _private prototype_ `void ProcessObjectTraceBegin(FEndpointId EndpointId, const FObjectTraceMessage& Message);`
- L205 _private prototype_ `void ProcessObjectTraceEnd(FEndpointId EndpointId, const FObjectTraceMessage& Message);`
- L206 _private prototype_ `void ProcessObjectTransmissionStart(FEndpointId EndpointId, const FObjectTransmissionStartMessage& Message);`
- L207 _private prototype_ `void ProcessObjectTransmissionReceive(FEndpointId EndpointId, const FObjectTransmissionReceiveMessage& Message);`
- L208 _private prototype_ `void ProcessObjectSink(FEndpointId EndpointId, const FObjectSinkMessage& Message);`
- L211 _private function_ `const FPerObjectData* FindObjectData(const FObjectScopeInfo& Info) const` — Getters
- L212 _private function_ `const FPerSequenceData* FindSequenceData(const FSequenceScopeInfo& Info) const`
- L213 _private function_ `FPerSequenceData* FindSequenceData(const FSequenceScopeInfo& Info)`
- L214 _private function_ `const FPerSequenceEndpointData* FindSequenceEndpointData(const FEndpointScopeInfo& Info) const`
- L216 _private function_ `FPerObjectData& FindOrAddObjectData(const FObjectScopeInfo& Info)` — Setters
- L217 _private function_ `FPerSequenceData& FindOrAddSequenceData(const FSequenceScopeInfo& Info, double Start)`
- L218 _private function_ `FPerSequenceData& FindSequenceDataChecked(const FSequenceScopeInfo& Info)`
- L219 _private function_ `FPerSequenceEndpointData& FindOrAddSequenceEndpointData(const FEndpointScopeInfo& Info)`
- L231 _private prototype_ `bool OpenNetworkScopeIfNotOpen(const FEndpointScopeInfo& Info, double ConvertedTime, FPerSequenceData& SequenceData);` — Opens a network scope. Usually opened by TransmissionReceive. Also used whenever any message is received to check whether a scope was opened implicitly: At the beginning of a sequence, there is usually no TransmissionReceive but a scope needs to be opened. @return Whether a scope was opened
- L233 _private prototype_ `void EndOpenNetworkScope(double ConvertedTime, const FEndpointScopeInfo& Info);` — Used by TransmissionStart or ObjectSink event to end the scope of the current network user.
- L239 _private prototype_ `void UpdateSequenceStats(const FEndpointScopeInfo& Info, double Time);` — Converts Time using ConvertEndpointCycleToTime, updates ActiveProtocols, updates the known start and end times of the sequence, and caches that events occured at the times (for speeding up search which events happened in a certain time window).
- L241 _private prototype_ `void UpdateSequenceStats_AlreadyConverted(const FEndpointScopeInfo& Info, double Time);` — Overload that already accepts an already converted Time (ConvertEndpointCycleToTime was already called, just store the Time that is passed in).
- L244 _private prototype_ `TOptional<double> ConvertEndpointCycleToTime(FEndpointId Endpoint, double OtherEndpointTime) const;` — Computes what time on the main .utrace file another endpoint's time corresponds to. Fails if that endpoint did not send any init event.

#### struct `UE::ConcertInsightsVisualizer::FProtocolMultiEndpointProvider::FPerSequenceEndpointData`  
`struct FPerSequenceEndpointData`  
_L94-111_
- L100 _public member_ `FEndpointCpuTimeline CpuTimeline;` — Timelines where endpoints spent CPU time. Displayed as 3rd row for a sequence.
- L106 _public member_ `TOptional<uint64> LastScopeStartEventId;` — Result of FNetworkScopeTimeline::AppendBeginEvent for FPerSequenceData::NetworkScopeTimeline. Set when a scope has been started, unset when it has ended.
- L108 _public function_ `FPerSequenceEndpointData(TraceServices::ILinearAllocator& Allocator) : CpuTimeline(Allocator)`

#### struct `UE::ConcertInsightsVisualizer::FProtocolMultiEndpointProvider::FSequenceEndData`  
`struct FSequenceEndData`  
_L113-119_
- L116 _public member_ `double End;` — The time of the sequence event with the latest time processed so far. Set once the sink event has been received; the track will display an infinite time until then.
- L118 _public member_ `FEndpointId SinkEndpoint;` — The endpoint for which the sequence ended.

#### struct `UE::ConcertInsightsVisualizer::FProtocolMultiEndpointProvider::FPerSequenceData`  
`struct FPerSequenceData`  
_L121-146_
- L124 _public member_ `double Start;` — The time of the sequence event with the earliest time processed so far; updated as new events come in.
- L126 _public member_ `TOptional<FSequenceEndData> SinkData;` — Set when the sequence sink has been encountered
- L129 _public member_ `TSet<FEndpointId> Endpoints;` — Endpoints that participated in this sequence
- L135 _public member_ `FNetworkScopeTimeline NetworkScopeTimeline;` — Indicates the intervals at which an object was processed by an endpoint. Does NOT contain intervals for transit scopes; those are determined implicitly in EnumerateNetworkScopes.
- L138 _public function_ `double GetEndTime() const` — Gets the end time as it should be displayed: infinite if pending and the actual end time if the sequence has ended.
- L140 _public function_ `bool HasSequenceEnded() const` — Whether a sink event has been received for the sequence.
- L142 _public function_ `FPerSequenceData(TraceServices::ILinearAllocator& Allocator, double Start) : Start(Start) , NetworkScopeTimeline(Allocator)`

#### struct `UE::ConcertInsightsVisualizer::FProtocolMultiEndpointProvider::FPerObjectData`  
`struct FPerObjectData`  
_L148-176_
- L166 _public member_ `mutable TArray<FSequenceId> CachedTimelineSortedByStart;` — When bIsTimelineDirty == false, this contains all sequences sorted by their start time. Every time new sequence is added or the sequence bounds change (FPerSequenceData::Start or FPerSequenceData::End), this needs to be resorted. This is resorted lazily, i.e. only when EnumerateSequences is called. Context: - USUALLY sequences start a monotonous, i.e. id x < y implies that sequence x started before y, but we do not want to enforce this to make it easier for the trace API user. - OFTEN sequence are processed in order (i.e. usually we can just CachedTimelineSortedByStart.Add new sequence) but they can be processed out of order. - Asymptotically, it is cheaper to dirty this array with with an O(1) update and do one full O(nlogn) resort rather than keeping this array sorted making each update O(n), which effectively boils down to insertion sort of O(n^2). Whether this is also better in practice is not profiled. For the above 3 points in mind, we opt for a full resort in EnumerateSequences. Mutable because const function EnumerateSequences updates this. In the perspective of the API user, the internal state does not change.
- L175 _public member_ `mutable bool bIsTimelineDirty = false;` — When true, CachedTimelineSortedByStart needs to be re-sorted. This flag is set when either 1. a new sequence ID is added, or 2. a FPerSequenceData::Start or FPerSequenceData::End time value is changed. Mutable because const function EnumerateSequences updates this. In the perspective of the API user, the internal state does not change.

#### Free symbols / members of external scopes

- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace ConcertInsightsVisualizer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertInsights/ConcertInsightsVisualizer/Source/ConcertInsightsVisualizer/Private/Trace/TraceAggregator.h` (Private)


#### struct `UE::ConcertInsightsVisualizer::FTraceCachedInfo`  
`struct FTraceCachedInfo`  
_L20-28_
- L22 _public member_ `uint64 Id;`
- L23 _public member_ `uint64 Timestamp;`
- L24 _public function_ `FTraceCachedInfo(const Trace::FStoreClient::FTraceInfo& Info) : Id(Info.GetId()) , Timestamp(Info.GetTimestamp())`

#### class `UE::ConcertInsightsVisualizer::FTraceAggregator`  
`class FTraceAggregator : public FNoncopyable`  
_L31-87_
- inherits: `FNoncopyable`
- desc: Analyses trace files that relate to a main .utrace.
- L35 _public prototype_ `FTraceAggregator(const Trace::FStoreClient& StoreClient UE_LIFETIMEBOUND, uint64 MainTraceId);`
- L43 _public prototype_ `void StartAggregatedAnalysis();` — Finds related trace files and kicks of the analyzing threads. Data will be enqueued so it can be read from the main thread. You are expected to call ProcessEnqueuedData at regular intervals from the main thread and transfer data, e.g. every tick.
- L46 _public prototype_ `void EnumerateTraceFiles(TFunctionRef<TraceServices::EEventEnumerate(uint64 TraceId)> Callback) const;` — Enumerates all trace files currently being analyzed.
- L49 _public prototype_ `void ProcessEnqueuedData(uint64 TraceId, TFunctionRef<void(FProtocolDataQueue& DataQueue)> Callback);` — Gets the data that has been produced since the last time.
- L76 _private member_ `const Trace::FStoreClient& StoreClient;` — Client from which to obtain related trace files.
- L78 _private member_ `const uint64 MainTraceId;` — ID of the trace being aggregated into.
- L81 _private member_ `TMap<uint64, TUniquePtr<FTraceData>> AggregatedTraces;` — The files being analyzed
- L83 _private prototype_ `void AnalyzeCompletedTraces(const FTraceCachedInfo& MainTraceInfo);`
- L85 _private prototype_ `static bool ShouldAnalyzeTrace(const Trace::FStoreClient::FTraceInfo& ConsideredTraceInfo, const FTraceCachedInfo& MainTraceInfo);`
- L86 _private prototype_ `void AnalyzeTrace(uint64 TraceId);`

#### struct `UE::ConcertInsightsVisualizer::FTraceAggregator::FTraceData`  
`struct FTraceData`  
_L53-73_
- L60 _public member_ `TSharedRef<TraceServices::IAnalysisSession> Session;` — Session created for this trace file. Does not any processing (FAnalysisSession::Start not called) but simply exists for storing strings. Owns the underlying IInDataStream and keeps it alive.
- L63 _public member_ `FProtocolDataQueue DataQueue;` — Holds the analyzed data. This is actively dequeued
- L65 _public member_ `FProtocolEndpointAnalyzer Analyzer;` — Fills Provider with data
- L68 _public member_ `Trace::FAnalysisContext AnalysisContext;` — Context that instruments the analysis
- L70 _public member_ `Trace::FAnalysisProcessor AnalysisProcessor;` — Handle to thread doing the processing
- L72 _public prototype_ `FTraceData(TSharedRef<TraceServices::IAnalysisSession> InSession);`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Trace` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace ConcertInsightsVisualizer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertInsights/ConcertInsightsVisualizer/Source/ConcertInsightsVisualizer/Private/Trace/Types/EndpointId.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ConcertInsightsVisualizer` (scope `UE`)
- L10 _typedef_ `using FEndpointId = uint64;` (scope `UE::ConcertInsightsVisualizer`) — Id of a network endpoint, which can do processing of an object.

### `Plugins/Developer/Concert/ConcertInsights/ConcertInsightsVisualizer/Source/ConcertInsightsVisualizer/Private/Trace/Types/ProtocolId.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ConcertInsightsVisualizer` (scope `UE`)
- L9 _typedef_ `using FProtocolId = uint8;` (scope `UE::ConcertInsightsVisualizer`)

### `Plugins/Developer/Concert/ConcertInsights/ConcertInsightsVisualizer/Source/ConcertInsightsVisualizer/Private/Trace/Types/ScopeInfos.h` (Private)


#### struct `UE::ConcertInsightsVisualizer::FObjectScopeInfo`  
`struct FObjectScopeInfo`  
_L16-32_
- desc: Identifies all data associated with an object
- L18 _public member_ `FProtocolId ProtocolId;`
- L19 _public member_ `FObjectPath ObjectPath;`
- L21 _public prototype_ `FObjectScopeInfo() = default;`
- L22 _public function_ `FObjectScopeInfo(FProtocolId ProtocolId, const FObjectPath& ObjectPath) : ProtocolId(ProtocolId) , ObjectPath(ObjectPath)`
- L27 _public prototype_ `struct FSequenceScopeInfo MakeSequenceInfo(FSequenceId SequenceId) const;`
- L71 _function_ `FORCEINLINE FSequenceScopeInfo FObjectScopeInfo::MakeSequenceInfo(FSequenceId SequenceId) const`

#### struct `UE::ConcertInsightsVisualizer::FSequenceScopeInfo`  
`struct FSequenceScopeInfo : FObjectScopeInfo`  
_L35-50_
- inherits: `FObjectScopeInfo`
- desc: Identifies a sequence of an object
- L37 _public member_ `FSequenceId SequenceId;`
- L39 _public prototype_ `FSequenceScopeInfo() = default;`
- L40 _public function_ `FSequenceScopeInfo(FProtocolId ProtocolId, const FObjectPath& ObjectPath, FSequenceId SequenceId) : FObjectScopeInfo(ProtocolId, ObjectPath) , SequenceId(SequenceId)`
- L45 _public prototype_ `struct FEndpointScopeInfo MakeEndpointInfo(FEndpointId EndpointId) const;`
- L76 _function_ `FORCEINLINE FEndpointScopeInfo FSequenceScopeInfo::MakeEndpointInfo(FEndpointId EndpointId) const`

#### struct `UE::ConcertInsightsVisualizer::FEndpointScopeInfo`  
`struct FEndpointScopeInfo : FSequenceScopeInfo`  
_L53-68_
- inherits: `FSequenceScopeInfo`
- desc: Identifies an endpoint that did processing in a sequence.
- L55 _public prototype_ `FEndpointScopeInfo() = default;`
- L56 _public function_ `FEndpointScopeInfo(FProtocolId ProtocolId, const FObjectPath& ObjectPath, FSequenceId SequenceId, FEndpointId EndpointId) : FSequenceScopeInfo(ProtocolId, ObjectPath, SequenceId) , EndpointId(EndpointId)`
- L61 _public member_ `FEndpointId EndpointId;`
- L63 _public function_ `FString ToString() const`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ConcertInsightsVisualizer` (scope `UE`)
- L13 _typedef_ `using FObjectPath = FStringView;` (scope `UE::ConcertInsightsVisualizer`)
- L29 _function_ `friend bool operator==(const FObjectScopeInfo& Left, const FObjectScopeInfo& Right)` (scope `UE::ConcertInsightsVisualizer`)
- L30 _function_ `friend bool operator!=(const FObjectScopeInfo& Left, const FObjectScopeInfo& Right)` (scope `UE::ConcertInsightsVisualizer`)
- L31 _function_ `friend uint32 GetTypeHash(const FObjectScopeInfo& Info)` (scope `UE::ConcertInsightsVisualizer`)
- L47 _function_ `friend bool operator==(const FSequenceScopeInfo& Left, const FSequenceScopeInfo& Right)` (scope `UE::ConcertInsightsVisualizer`)
- L48 _function_ `friend bool operator!=(const FSequenceScopeInfo& Left, const FSequenceScopeInfo& Right)` (scope `UE::ConcertInsightsVisualizer`)
- L49 _function_ `friend uint32 GetTypeHash(const FSequenceScopeInfo& Info)` (scope `UE::ConcertInsightsVisualizer`)
- L65 _function_ `friend bool operator==(const FEndpointScopeInfo& Left, const FEndpointScopeInfo& Right)` (scope `UE::ConcertInsightsVisualizer`)
- L66 _function_ `friend bool operator!=(const FEndpointScopeInfo& Left, const FEndpointScopeInfo& Right)` (scope `UE::ConcertInsightsVisualizer`)
- L67 _function_ `friend uint32 GetTypeHash(const FEndpointScopeInfo& Info)` (scope `UE::ConcertInsightsVisualizer`)

### `Plugins/Developer/Concert/ConcertInsights/ConcertInsightsVisualizer/Source/ConcertInsightsVisualizer/Private/Trace/Types/SequenceEndpointPair.h` (Private)


#### struct `UE::ConcertInsightsVisualizer::FSequenceEndpointPair`  
`struct FSequenceEndpointPair`  
_L11-19_
- L13 _public member_ `FSequenceId SequenceId;`
- L14 _public member_ `FEndpointId EndpointId;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ConcertInsightsVisualizer` (scope `UE`)
- L16 _function_ `friend bool operator==(const FSequenceEndpointPair& Left, const FSequenceEndpointPair& Right)` (scope `UE::ConcertInsightsVisualizer`)
- L17 _function_ `friend bool operator!=(const FSequenceEndpointPair& Left, const FSequenceEndpointPair& Right)` (scope `UE::ConcertInsightsVisualizer`)
- L18 _function_ `friend uint32 GetTypeHash(const FSequenceEndpointPair& Pair)` (scope `UE::ConcertInsightsVisualizer`)

### `Plugins/Developer/Concert/ConcertInsights/ConcertInsightsVisualizer/Source/ConcertInsightsVisualizer/Private/Trace/Types/SequenceId.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ConcertInsightsVisualizer` (scope `UE`)
- L9 _typedef_ `using FSequenceId = uint32;` (scope `UE::ConcertInsightsVisualizer`)

### `Plugins/Developer/Concert/ConcertInsights/ConcertInsightsVisualizer/Source/ConcertInsightsVisualizer/Private/Util/TimeSyncUtils.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ConcertInsightsVisualizer` (scope `UE`)
- L7 _namespace_ `namespace TimeSyncUtils` (scope `UE::ConcertInsightsVisualizer`)
- L33 _prototype_ `double ConvertSourceToTargetTime( const FDateTime& TargetInitUtc, const FDateTime& SourceInitUtc, double TargetInitTime, double SourceInitTime, double SourceTime );` (scope `UE::ConcertInsightsVisualizer::TimeSyncUtils`) — Given a source and target timeline, converts SourceTime to the equivalent time in the target timeline. Time is assumed to flow at the same pace (i.e. 1s in target timeline corresponds to 1s in source timeline). Example: Suppose in the below scenario, every character is 1 second and "[" indicates time 0 in the local timeline. Global	0123456789_ Target	[Init567x9] Source	-[1Init6y8] So this function answers: Given that event y occurs in source's timeline, we want to know the value of x in target's timeline. Given the following input: - TargetInitUtc	= 22/02/2024 12:00:01 (random time I choose) - SourceInitUtc	= 22/02/2024 12:00:03 (because init event occured 2s after target's init event) - TargetInitTime = 1 (see target graph time of I) - SourceInitTime = 2 (see source graph time of I) - SourceTime		= 7 (see source graph time of y) This yields x = ConvertSourceToTargetTime(22/02/2024 12:00:02, 22/02/2024 12:00:04, 1, 2, 7) = 8 @param TargetInitUtc UTC time of target's init event in target timeline @param SourceInitUtc UTC time of source's init event in source timeline @param TargetInitTime When the target's init event occured in the target timeline (intended in absolute seconds) @param SourceInitTime When the source's init event occured in the source timeline (intended in absolute seconds) @param SourceTime The time to convert into the target timeline (intended in absolute seconds)

### `Plugins/Developer/Concert/ConcertInsights/ConcertInsightsVisualizer/Source/ConcertInsightsVisualizer/Public/IConcertInsightsVisualizerModule.h` (Public)


#### class `UE::ConcertInsightsVisualizer::IConcertInsightsVisualizerModule`  
`class IConcertInsightsVisualizerModule : public IModuleInterface`  
_L10-36_
- inherits: `IModuleInterface`
- desc: This module extends and manages all the Concert UI in Unreal Insights.
- L20 _public function_ `static inline IConcertInsightsVisualizerModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L31 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() during shutdown if IsAvailable() returns true. @return True if the module is loaded and ready to use

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ConcertInsightsVisualizer` (scope `UE`)
