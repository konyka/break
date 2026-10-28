# Plugins / UdpMessagingInsights

- module root: `Plugins/Messaging/MessagingInsights/Source/UdpMessagingInsights`
- headers: 6; symbols: 156
- symbol kinds: class=6, enum=2, enumerator=6, function=9, member=47, namespace=35, prototype=37, struct=9, typedef=5
- PrivateDependencyModuleNames: ApplicationCore, Core, CoreUObject, Engine, Messaging, Networking, Slate, SlateCore, TraceAnalysis, TraceInsights, TraceInsightsCore, TraceLog, TraceServices, UdpMessaging

### `Plugins/Messaging/MessagingInsights/Source/UdpMessagingInsights/Private/UdpMessagingTimingTrack.h` (Private)


#### class `UE::MessagingInsights::FUdpMessagingTimingTrack`  
`class FUdpMessagingTimingTrack : public FTimingEventsTrack`  
_L20-49_
- inherits: `FTimingEventsTrack`
- desc: Timing track for UDP Messaging.
- L23 _private typedef_ `using Super = FTimingEventsTrack;`
- L26 _public prototype_ `FUdpMessagingTimingTrack( const FUdpMessagingTimingViewSession& InSharedData, const uint16 InNodeShortId, const EMessageDirection InDirection );`
- L33 _public prototype_ `virtual void BuildDrawState(ITimingEventsTrackDrawStateBuilder& Builder, const ITimingTrackUpdateContext& Context) override;`
- L34 _public prototype_ `virtual void InitTooltip(FTooltipDrawState& InOutTooltip, const ITimingEvent& InTooltipEvent) const override;`
- L35 _public prototype_ `virtual void OnClipboardCopyEvent(const ITimingEvent& InSelectedEvent) const override;`
- L36 _public prototype_ `virtual void BuildContextMenu(FMenuBuilder& MenuBuilder) override;`
- L37 _public prototype_ `virtual const TSharedPtr<const ITimingEvent> GetEvent(double InTime, double SecondsPerPixel, int32 Depth) const override;`
- L41 _private prototype_ `void EnumerateTimingEventFields(const FMessageTimingEvent& InSelectedEvent, TFunctionRef<void(FStringView, FStringView)> InCallback) const;`
- L44 _private member_ `const FUdpMessagingTimingViewSession& SharedData;`
- L45 _private member_ `const uint16 NodeShortId;`
- L46 _private member_ `const EMessageDirection Direction;`
- L48 _private member_ `bool bShowLifecycleEvents = true;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MessagingInsights` (scope `UE`)

### `Plugins/Messaging/MessagingInsights/Source/UdpMessagingInsights/Private/UdpMessagingTimingViewExtender.h` (Private)


#### class `UE::MessagingInsights::FUdpMessagingTimingViewExtender`  
`class FUdpMessagingTimingViewExtender : public UE::Insights::Timing::ITimingViewExtender`  
_L21-39_
- inherits: `UE::Insights::Timing::ITimingViewExtender`
- L25 _public prototype_ `virtual void OnBeginSession(UE::Insights::Timing::ITimingViewSession& InSession) override;`
- L26 _public prototype_ `virtual void OnEndSession(UE::Insights::Timing::ITimingViewSession& InSession) override;`
- L27 _public prototype_ `virtual void Tick(const UE::Insights::Timing::FTimingViewExtenderTickParams& InParams) override;`
- L28 _public prototype_ `virtual void ExtendFilterMenu(UE::Insights::Timing::ITimingViewSession& InSession, FMenuBuilder& InMenuBuilder) override;`
- L38 _private member_ `TMap<UE::Insights::Timing::ITimingViewSession*, FPerSessionData> PerSessionDataMap;` — The data we host per-session

#### struct `UE::MessagingInsights::FUdpMessagingTimingViewExtender::FPerSessionData`  
`struct FPerSessionData`  
_L32-35_
- L34 _public member_ `TPimplPtr<FUdpMessagingTimingViewSession> SharedData;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace TraceServices`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Insights` (scope `UE`)
- L10 _namespace_ `namespace Timing` (scope `UE::Insights`)
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Insights` (scope `UE`)
- L11 _namespace_ `namespace Timing` (scope `UE::Insights`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MessagingInsights` (scope `UE`)

### `Plugins/Messaging/MessagingInsights/Source/UdpMessagingInsights/Private/UdpMessagingTimingViewSession.h` (Private)


#### class `UE::MessagingInsights::FUdpMessagingTimingViewSession`  
`class FUdpMessagingTimingViewSession`  
_L19-62_
- L22 _public prototype_ `FUdpMessagingTimingViewSession();`
- L24 _public prototype_ `void OnBeginSession(UE::Insights::Timing::ITimingViewSession& InTimingViewSession);`
- L25 _public prototype_ `void OnEndSession(UE::Insights::Timing::ITimingViewSession& InTimingViewSession);`
- L26 _public prototype_ `void Tick(const UE::Insights::Timing::FTimingViewExtenderTickParams& InParams);`
- L27 _public prototype_ `void ExtendFilterMenu(FMenuBuilder& InMenuBuilder);`
- L30 _public function_ `const TraceServices::IAnalysisSession& GetAnalysisSession() const` — Get the last cached analysis session
- L37 _public prototype_ `void ToggleMessageTracks();` — Show/hide the message tracks.
- L40 _public function_ `UE::Insights::Timing::ITimingViewSession* GetTimingView() const` — The timing view for the session.
- L47 _private member_ `const TraceServices::IAnalysisSession* AnalysisSession = nullptr;` — Cached analysis session, set in Tick()
- L50 _private member_ `UE::Insights::Timing::ITimingViewSession* TimingViewSession = nullptr;` — Cached timing view session, set in OnBeginSession/OnEndSession
- L58 _private member_ `TMap<uint16, FDuplexTracks> LocalNodeTracks;`
- L61 _private member_ `bool bMessageTracksEnabled = true;` — Whether message tracks are enabled.

#### struct `UE::MessagingInsights::FUdpMessagingTimingViewSession::FDuplexTracks`  
`struct FDuplexTracks`  
_L52-56_
- L54 _public member_ `TSharedRef<FUdpMessagingTimingTrack> SendTrack;`
- L55 _public member_ `TSharedRef<FUdpMessagingTimingTrack> ReceiveTrack;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace TraceServices`
- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Insights` (scope `UE`)
- L8 _namespace_ `namespace Timing` (scope `UE::Insights`)
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Insights` (scope `UE`)
- L9 _namespace_ `namespace Timing` (scope `UE::Insights`)
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Insights` (scope `UE`)
- L10 _namespace_ `namespace Timing` (scope `UE::Insights`)
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MessagingInsights` (scope `UE`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MessagingInsights` (scope `UE`)

### `Plugins/Messaging/MessagingInsights/Source/UdpMessagingInsights/Private/UdpMessagingTraceAnalyzer.h` (Private)


#### class `UE::MessagingInsights::FUdpMessagingAnalyzer`  
`class FUdpMessagingAnalyzer : public UE::Trace::IAnalyzer`  
_L20-42_
- inherits: `UE::Trace::IAnalyzer`
- L23 _public prototype_ `FUdpMessagingAnalyzer(TraceServices::IAnalysisSession& InSession, FUdpMessagingProvider& InProvider);`
- L26 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L27 _public prototype_ `virtual void OnAnalysisEnd() override;`
- L28 _public prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L40 _private member_ `TraceServices::IAnalysisSession& Session;`
- L41 _private member_ `FUdpMessagingProvider& Provider;`

#### enum `UE::MessagingInsights::FUdpMessagingAnalyzer::(anonymous)`  
``  
_L33-38_

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace TraceServices`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MessagingInsights` (scope `UE`)
- L34 _enumerator_ `RouteId_DiscoveredNode` (scope `UE::MessagingInsights::FUdpMessagingAnalyzer::__anon0c134be50103`)
- L35 _enumerator_ `RouteId_MessageSummary` (scope `UE::MessagingInsights::FUdpMessagingAnalyzer::__anon0c134be50103`)
- L36 _enumerator_ `RouteId_MessageTypeInfo` (scope `UE::MessagingInsights::FUdpMessagingAnalyzer::__anon0c134be50103`)
- L37 _enumerator_ `RouteId_MessageLifecycle` (scope `UE::MessagingInsights::FUdpMessagingAnalyzer::__anon0c134be50103`)

### `Plugins/Messaging/MessagingInsights/Source/UdpMessagingInsights/Private/UdpMessagingTraceModule.h` (Private)


#### class `UE::MessagingInsights::FUdpMessagingTraceModule`  
`class FUdpMessagingTraceModule : public TraceServices::IModule`  
_L11-20_
- inherits: `TraceServices::IModule`
- L13 _private member_ `static FName ModuleName;`
- L17 _public prototype_ `virtual void GetModuleInfo(TraceServices::FModuleInfo& OutModuleInfo) override;`
- L18 _public prototype_ `virtual void OnAnalysisBegin(TraceServices::IAnalysisSession& Session) override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace MessagingInsights` (scope `UE`)

### `Plugins/Messaging/MessagingInsights/Source/UdpMessagingInsights/Private/UdpMessagingTraceProvider.h` (Private)


#### struct `UE::MessagingInsights::FNodeDiscoveredEvent`  
`struct FNodeDiscoveredEvent`  
_L29-44_
- L31 _public member_ `uint64 Cycle;`
- L32 _public member_ `uint16 ShortId;`
- L33 _public member_ `uint16 DiscoveredByShortId;`
- L34 _public member_ `FGuid Id;`
- L35 _public member_ `FIPv4Endpoint Endpoint;`
- L36 _public member_ `uint8 ProtocolVersion;`
- L38 _public prototype_ `static FNodeDiscoveredEvent FromEventData(const UE::Trace::IAnalyzer::FEventData& EventData);`
- L40 _public function_ `bool IsLocalNode() const`

#### struct `UE::MessagingInsights::FMessageSummary`  
`struct FMessageSummary`  
_L46-55_
- L48 _public member_ `uint16 SenderShortId;`
- L49 _public member_ `uint16 RecipientShortId;`
- L50 _public member_ `uint32 MessageId;`
- L51 _public member_ `uint64 Size;`
- L52 _public member_ `uint32 NumSegments;`
- L54 _public prototype_ `static FMessageSummary FromEventData(const UE::Trace::IAnalyzer::FEventData& EventData);`

#### struct `UE::MessagingInsights::FMessageLifecycleEvent`  
`struct FMessageLifecycleEvent`  
_L57-85_
- L59 _public member_ `uint64 Cycle;`
- L60 _public member_ `uint16 SenderShortId;`
- L61 _public member_ `uint16 RecipientShortId;`
- L62 _public member_ `uint32 MessageId;`
- L74 _public member_ `TVariant<FOuterEvent, FInnerEvent> Details;`
- L77 _public member_ `int32 LaneDepth = 0;` — Computed/derived values
- L79 _public prototype_ `static FMessageLifecycleEvent FromEventData(const UE::Trace::IAnalyzer::FEventData& EventData);`
- L81 _public function_ `FMessageKey GetMessageKey() const`

#### struct `UE::MessagingInsights::FMessageLifecycleEvent::FOuterEvent`  
`struct FOuterEvent`  
_L64-67_
- L66 _public member_ `UE::UdpMessaging::Trace::EUdpMessageLifecycleEvent TerminalEventType;`

#### struct `UE::MessagingInsights::FMessageLifecycleEvent::FInnerEvent`  
`struct FInnerEvent`  
_L69-72_
- L71 _public member_ `UE::UdpMessaging::Trace::EUdpMessageLifecycleEvent EventType;`

#### enum `UE::MessagingInsights::EMessageDirection`  
`enum class EMessageDirection : uint8`  
_L88-92_
- L90 _public enumerator_ `Send`
- L91 _public enumerator_ `Receive`

#### class `UE::MessagingInsights::FUdpMessagingProvider`  
`class FUdpMessagingProvider : public TraceServices::IProvider`  
_L95-190_
- inherits: `TraceServices::IProvider`
- L97 _private typedef_ `using FEventTiming = TPair<double, FMessageLifecycleEvent>;`
- L100 _public member_ `static const FName ProviderName;`
- L102 _public prototype_ `FUdpMessagingProvider(TraceServices::IAnalysisSession& InSession);`
- L104 _public typedef_ `using FNodeDiscoveredTimeline = TraceServices::TPointTimeline<FNodeDiscoveredEvent>;`
- L105 _public function_ `const FNodeDiscoveredTimeline& GetNodeDiscoveredTimeline() const`
- L110 _public prototype_ `void AddNodeDiscoveredEvent(double InEventTimeSeconds, FNodeDiscoveredEvent&& InEvent);`
- L112 _public typedef_ `using FMessageTimeline = TraceServices::TIntervalTimeline<FMessageLifecycleEvent>;`
- L113 _public function_ `const FMessageTimeline* GetMessageTimeline(uint16 InLocalNodeShortId, EMessageDirection InDirection) const`
- L129 _public prototype_ `void EnumerateOutstandingMessages( uint16 InLocalNodeShortId, EMessageDirection InDirection, double InIntervalStart, double InIntervalEnd, TraceServices::ITimeline<FMessageLifecycleEvent>::EventRangeCallback InCallback ) const;`
- L135 _public function_ `uint32 GetNumLocalNodes() const`
- L141 _public function_ `uint16 GetLocalNodeShortId(uint32 InLocalNodeIdx) const`
- L148 _public prototype_ `const FNodeDiscoveredEvent* GetNodeByShortId(uint16 InShortId) const;`
- L150 _public prototype_ `void AddMessageEvent(double InEventTimeSeconds, FMessageLifecycleEvent&& InEvent);`
- L152 _public prototype_ `void AddMessageSummary(uint16 InSenderShortId, uint16 InRecipientShortId, uint32 InMessageId, FMessageSummary&& InMessageSummary);`
- L153 _public prototype_ `const FMessageSummary* GetMessageSummary(uint16 InSenderShortId, uint16 InRecipientShortId, uint32 InMessageId) const;`
- L155 _public prototype_ `void AddMessageTypeInfo(uint16 InSenderShortId, uint16 InRecipientShortId, uint32 InMessageId, const TCHAR* InPackage, const TCHAR* InAsset);`
- L156 _public prototype_ `TPair<const TCHAR*, const TCHAR*> GetMessageTypeInfo(uint16 InSenderShortId, uint16 InRecipientShortId, uint32 InMessageId) const;`
- L159 _private member_ `TraceServices::IAnalysisSession& Session;`
- L161 _private member_ `FNodeDiscoveredTimeline NodeDiscoveredTimeline;`
- L162 _private member_ `TMap<uint16, uint64> NodeShortIdToDiscoveredEvent;`
- L165 _private member_ `TArray<uint16> LocalNodeShortIds;` — Contains the short IDs just for local nodes (typically just a few).
- L184 _private member_ `TMap<uint16, FLocalNode> LocalNodes;`
- L187 _private member_ `TMap<FMessageKey, TPair<const TCHAR*, const TCHAR*>> MessageKeyToTypeInfo;` — Pointers are to strings owned by TraceServices::FStringDefinition, guaranteed valid for the analysis session.
- L189 _private member_ `TMap<FMessageKey, FMessageSummary> MessageKeyToSummary;`

#### struct `UE::MessagingInsights::FUdpMessagingProvider::FLocalNodeTimeline`  
`struct FLocalNodeTimeline`  
_L167-176_
- L169 _public member_ `FMessageTimeline MessageTimeline;`
- L170 _public member_ `TArray<double> LaneFreeTimes;`
- L172 _public member_ `TMap<FMessageKey, TArray<FEventTiming>> OutstandingMessageEvents;`
- L174 _public prototype_ `void AddMessageEvent(double InEventTimeSeconds, FMessageLifecycleEvent&& InEvent);`
- L175 _public prototype_ `int32 AllocLaneDepth(double InStartTime, double InEndTime);`

#### struct `UE::MessagingInsights::FUdpMessagingProvider::FLocalNode`  
`struct FLocalNode`  
_L178-182_
- L180 _public member_ `FLocalNodeTimeline SendTimeline;`
- L181 _public member_ `FLocalNodeTimeline ReceiveTimeline;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UdpMessaging` (scope `UE`)
- L11 _namespace_ `namespace Trace` (scope `UE::UdpMessaging`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace MessagingInsights` (scope `UE`)
- L19 _typedef_ `using FMessageKey = uint64;` (scope `UE::MessagingInsights`)
- L21 _function_ `inline FMessageKey MakeMessageKey(uint16 SenderShortId, uint16 RecipientShortId, uint32 MessageId)` (scope `UE::MessagingInsights`)
