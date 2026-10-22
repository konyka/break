# Plugins / RenderTraceInsights

- module root: `Plugins/RenderTraceInsights/Source/RenderTraceInsights`
- headers: 8; symbols: 644
- symbol kinds: class=17, delegate=34, enum=12, enumerator=84, externvar=1, function=39, macro=1, member=174, namespace=27, prototype=229, struct=24, typedef=1, variable=1
- PrivateDependencyModuleNames: ApplicationCore, Core, CoreUObject, InputCore, RHI, RenderCore, Slate, SlateCore, TraceAnalysis, TraceInsights, TraceInsightsCore, TraceLog, TraceServices

### `Plugins/RenderTraceInsights/Source/RenderTraceInsights/Private/RenderTraceAnalyzer.h` (Private)


#### class `UE::RenderTraceInsights::FRenderTraceAnalyzer`  
`class FRenderTraceAnalyzer : public UE::Trace::IAnalyzer`  
_L15-147_
- inherits: `UE::Trace::IAnalyzer`
- L18 _public prototype_ `FRenderTraceAnalyzer(TraceServices::IAnalysisSession& InSession, IEditableRenderTraceProvider& InProvider);`
- L20 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L21 _public prototype_ `virtual void OnAnalysisEnd() override;`
- L22 _public prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& EventContext) override;`
- L74 _private member_ `TraceServices::IAnalysisSession& Session;`
- L75 _private member_ `IEditableRenderTraceProvider& Provider;`
- L77 _private member_ `uint32 GameThreadID = 0;`
- L78 _private member_ `uint32 RenderThreadID = 0;`
- L79 _private member_ `uint32 RHIThreadID = 0;`
- L80 _private member_ `TMap<uint64, uint32> LiveRDGPasses;`
- L81 _private member_ `TMap<uint64, uint32> LiveCommandLists;`
- L82 _private member_ `TMap<uint64, FLiveTranslateJob> LiveTranslateJobs;`
- L83 _private member_ `TMap<uint64, uint32> LiveRHIContexts;`
- L84 _private member_ `TMap<uint64, uint64> PlatformToRHIContext;`
- L85 _private member_ `TMap<uint32, uint32> PendingRTSubmitIDs;`
- L86 _private member_ `TMap<uint64, uint32> LivePlatformPayloads;`
- L87 _private member_ `TMap<uint64, uint32> LiveSyncPoints;`
- L88 _private member_ `TMap<uint64, uint32> ManualSyncPoints;`
- L89 _private member_ `uint32 PendingSubmissionBatchID = INVALID_EVENT_ID;`
- L90 _private member_ `uint32 PendingInterruptWakeUpID = INVALID_EVENT_ID;`
- L91 _private member_ `double FinalTimestamp = 0.0;`
- L92 _private member_ `uint64 LastThreadProviderModCount = 0;`
- L93 _private member_ `TMap<uint32, const TCHAR*> PassNameLookup;`
- L95 _private prototype_ `void BeginCmdListExecute(uint64 CmdListAppID, uint32 PermanentPassID, double Timestamp);`
- L96 _private prototype_ `void EndRDGPassExecute(uint32 PermanentPassID, double Timestamp);`
- L97 _private prototype_ `void AddCommandListToTimeline(uint32 PermanentCmdListID);`
- L98 _private prototype_ `void EndCommandList(uint32 PermanentCmdListID, double Timestamp);`
- L99 _private prototype_ `void AddTranslateTasksToTimeline(uint32 ThreadID);`
- L100 _private prototype_ `void EndTranslateTask(uint32 PermanentTaskID, double Timestamp);`
- L101 _private prototype_ `void EndPendingSubmissionBatch(double Timestamp, uint8 ExitStatus);`
- L102 _private prototype_ `void EndPendingInterruptWakeUp(double Timestamp, uint8 ExitStatus);`
- L103 _private prototype_ `FRHITranslateTask* GetTranslateJobForCmdList(uint64 CmdListID, const TCHAR* EventName, uint32 ThreadID, uint32* OutTranslateJobID);`
- L104 _private prototype_ `FPlatformPayload* FindPlatformPayload(uint64 PayloadID, const TCHAR* EventName, uint32 ThreadID);`
- L105 _private prototype_ `bool CacheThreadIDs();`
- L108 _private prototype_ `DECLARE_EVENT_PROCESSING_FUNC(CommandListCreated);`
- L109 _private prototype_ `DECLARE_EVENT_PROCESSING_FUNC(CommandListDetach);`
- L110 _private prototype_ `DECLARE_EVENT_PROCESSING_FUNC(CommandListFinishRecording);`
- L111 _private prototype_ `DECLARE_EVENT_PROCESSING_FUNC(CommandListDestroyed);`
- L112 _private prototype_ `DECLARE_EVENT_PROCESSING_FUNC(AddDispatchPassCommandList);`
- L113 _private prototype_ `DECLARE_EVENT_PROCESSING_FUNC(SubmitCommandLists);`
- L114 _private prototype_ `DECLARE_EVENT_PROCESSING_FUNC(SplitTranslateJob);`
- L115 _private prototype_ `DECLARE_EVENT_PROCESSING_FUNC(DispatchCommandList);`
- L116 _private prototype_ `DECLARE_EVENT_PROCESSING_FUNC(BeginTranslateCommandList);`
- L117 _private prototype_ `DECLARE_EVENT_PROCESSING_FUNC(ActivatePipelines);`
- L118 _private prototype_ `DECLARE_EVENT_PROCESSING_FUNC(SetTranslateContext);`
- L119 _private prototype_ `DECLARE_EVENT_PROCESSING_FUNC(EndTranslateCommandList);`
- L120 _private prototype_ `DECLARE_EVENT_PROCESSING_FUNC(FinalizeTranslateJob);`
- L121 _private prototype_ `DECLARE_EVENT_PROCESSING_FUNC(SubmitTranslateJobs);`
- L122 _private prototype_ `DECLARE_EVENT_PROCESSING_FUNC(AssociateContext);`
- L123 _private prototype_ `DECLARE_EVENT_PROCESSING_FUNC(PayloadCreated);`
- L124 _private prototype_ `DECLARE_EVENT_PROCESSING_FUNC(AddPayload);`
- L125 _private prototype_ `DECLARE_EVENT_PROCESSING_FUNC(CommandListOp);`
- L126 _private prototype_ `DECLARE_EVENT_PROCESSING_FUNC(SyncPointOp);`
- L127 _private prototype_ `DECLARE_EVENT_PROCESSING_FUNC(ManualFenceOp);`
- L128 _private prototype_ `DECLARE_EVENT_PROCESSING_FUNC(ProcessSubmissionQueueEnter);`
- L129 _private prototype_ `DECLARE_EVENT_PROCESSING_FUNC(SubmitYieldOnUnresolvedSyncPoint);`
- L130 _private prototype_ `DECLARE_EVENT_PROCESSING_FUNC(SubmitYieldOnUnresolvedManualFence);`
- L131 _private prototype_ `DECLARE_EVENT_PROCESSING_FUNC(SubmitWaitQueueFence);`
- L132 _private prototype_ `DECLARE_EVENT_PROCESSING_FUNC(SubmitWaitManualFence);`
- L133 _private prototype_ `DECLARE_EVENT_PROCESSING_FUNC(SubmitPlatformCommandLists);`
- L134 _private prototype_ `DECLARE_EVENT_PROCESSING_FUNC(SubmitSignalManualFence);`
- L135 _private prototype_ `DECLARE_EVENT_PROCESSING_FUNC(SubmitSignalQueueFence);`
- L136 _private prototype_ `DECLARE_EVENT_PROCESSING_FUNC(SubmitResolveSyncPoint);`
- L137 _private prototype_ `DECLARE_EVENT_PROCESSING_FUNC(ProcessSubmissionQueueExit);`
- L138 _private prototype_ `DECLARE_EVENT_PROCESSING_FUNC(ProcessInterruptQueueEnter);`
- L139 _private prototype_ `DECLARE_EVENT_PROCESSING_FUNC(InterruptQueueFenceSignaled);`
- L140 _private prototype_ `DECLARE_EVENT_PROCESSING_FUNC(ProcessInterruptQueueExit);`
- L144 _private prototype_ `void ProcessBeginExecuteRDGPass(const FEventData& EventData, uint32 ThreadID, double Timestamp, bool bIsDispatch);` — These are shared between regular and dispatch RDG passes so they have different signatures from the other event processing methods.
- L145 _private prototype_ `void ProcessEndExecuteRDGPass(const FEventData& EventData, uint32 ThreadID, double Timestamp, bool bIsDispatch);`
- L146 _private prototype_ `void ProcessRDGPassNameSpec(const FEventData& EventData, uint32 ThreadID, double Timestamp);`

#### enum `UE::RenderTraceInsights::FRenderTraceAnalyzer::(anonymous)`  
``  
_L26-65_

#### struct `UE::RenderTraceInsights::FRenderTraceAnalyzer::FLiveTranslateJob`  
`struct FLiveTranslateJob`  
_L67-72_
- L69 _public function_ `explicit FLiveTranslateJob(uint32 InPermanentID) : PermanentID(InPermanentID)`
- L70 _public member_ `uint32 PermanentID;`
- L71 _public member_ `bool bAddedToTimeline = false;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace TraceServices`
- L10 _namespace_ `namespace UE`
- L12 _namespace_ `namespace RenderTraceInsights` (scope `UE`)
- L27 _enumerator_ `Packet_CommandListCreated` (scope `UE::RenderTraceInsights::FRenderTraceAnalyzer::__anon0c89b8ca0103`)
- L28 _enumerator_ `Packet_CommandListDetach` (scope `UE::RenderTraceInsights::FRenderTraceAnalyzer::__anon0c89b8ca0103`)
- L29 _enumerator_ `Packet_CommandListFinishRecording` (scope `UE::RenderTraceInsights::FRenderTraceAnalyzer::__anon0c89b8ca0103`)
- L30 _enumerator_ `Packet_CommandListDestroyed` (scope `UE::RenderTraceInsights::FRenderTraceAnalyzer::__anon0c89b8ca0103`)
- L31 _enumerator_ `Packet_RDGPassNameSpec` (scope `UE::RenderTraceInsights::FRenderTraceAnalyzer::__anon0c89b8ca0103`)
- L32 _enumerator_ `Packet_BeginExecuteRDGPass` (scope `UE::RenderTraceInsights::FRenderTraceAnalyzer::__anon0c89b8ca0103`)
- L33 _enumerator_ `Packet_EndExecuteRDGPass` (scope `UE::RenderTraceInsights::FRenderTraceAnalyzer::__anon0c89b8ca0103`)
- L34 _enumerator_ `Packet_BeginExecuteDispatchPass` (scope `UE::RenderTraceInsights::FRenderTraceAnalyzer::__anon0c89b8ca0103`)
- L35 _enumerator_ `Packet_AddDispatchPassCommandList` (scope `UE::RenderTraceInsights::FRenderTraceAnalyzer::__anon0c89b8ca0103`)
- L36 _enumerator_ `Packet_EndExecuteDispatchPass` (scope `UE::RenderTraceInsights::FRenderTraceAnalyzer::__anon0c89b8ca0103`)
- L37 _enumerator_ `Packet_SubmitCommandLists` (scope `UE::RenderTraceInsights::FRenderTraceAnalyzer::__anon0c89b8ca0103`)
- L38 _enumerator_ `Packet_SplitTranslateJob` (scope `UE::RenderTraceInsights::FRenderTraceAnalyzer::__anon0c89b8ca0103`)
- L39 _enumerator_ `Packet_DispatchCommandList` (scope `UE::RenderTraceInsights::FRenderTraceAnalyzer::__anon0c89b8ca0103`)
- L40 _enumerator_ `Packet_BeginTranslateCommandList` (scope `UE::RenderTraceInsights::FRenderTraceAnalyzer::__anon0c89b8ca0103`)
- L41 _enumerator_ `Packet_ActivatePipelines` (scope `UE::RenderTraceInsights::FRenderTraceAnalyzer::__anon0c89b8ca0103`)
- L42 _enumerator_ `Packet_SetTranslateContext` (scope `UE::RenderTraceInsights::FRenderTraceAnalyzer::__anon0c89b8ca0103`)
- L43 _enumerator_ `Packet_EndTranslateCommandList` (scope `UE::RenderTraceInsights::FRenderTraceAnalyzer::__anon0c89b8ca0103`)
- L44 _enumerator_ `Packet_FinalizeTranslateJob` (scope `UE::RenderTraceInsights::FRenderTraceAnalyzer::__anon0c89b8ca0103`)
- L45 _enumerator_ `Packet_SubmitTranslateJobs` (scope `UE::RenderTraceInsights::FRenderTraceAnalyzer::__anon0c89b8ca0103`)
- L46 _enumerator_ `Packet_AssociateContext` (scope `UE::RenderTraceInsights::FRenderTraceAnalyzer::__anon0c89b8ca0103`)
- L47 _enumerator_ `Packet_PayloadCreated` (scope `UE::RenderTraceInsights::FRenderTraceAnalyzer::__anon0c89b8ca0103`)
- L48 _enumerator_ `Packet_AddPayload` (scope `UE::RenderTraceInsights::FRenderTraceAnalyzer::__anon0c89b8ca0103`)
- L49 _enumerator_ `Packet_CommandListOp` (scope `UE::RenderTraceInsights::FRenderTraceAnalyzer::__anon0c89b8ca0103`)
- L50 _enumerator_ `Packet_SyncPointOp` (scope `UE::RenderTraceInsights::FRenderTraceAnalyzer::__anon0c89b8ca0103`)
- L51 _enumerator_ `Packet_ManualFenceOp` (scope `UE::RenderTraceInsights::FRenderTraceAnalyzer::__anon0c89b8ca0103`)
- L52 _enumerator_ `Packet_ProcessSubmissionQueueEnter` (scope `UE::RenderTraceInsights::FRenderTraceAnalyzer::__anon0c89b8ca0103`)
- L53 _enumerator_ `Packet_SubmitYieldOnUnresolvedSyncPoint` (scope `UE::RenderTraceInsights::FRenderTraceAnalyzer::__anon0c89b8ca0103`)
- L54 _enumerator_ `Packet_SubmitYieldOnUnresolvedManualFence` (scope `UE::RenderTraceInsights::FRenderTraceAnalyzer::__anon0c89b8ca0103`)
- L55 _enumerator_ `Packet_SubmitWaitQueueFence` (scope `UE::RenderTraceInsights::FRenderTraceAnalyzer::__anon0c89b8ca0103`)
- L56 _enumerator_ `Packet_SubmitWaitManualFence` (scope `UE::RenderTraceInsights::FRenderTraceAnalyzer::__anon0c89b8ca0103`)
- L57 _enumerator_ `Packet_SubmitPlatformCommandLists` (scope `UE::RenderTraceInsights::FRenderTraceAnalyzer::__anon0c89b8ca0103`)
- L58 _enumerator_ `Packet_SubmitSignalManualFence` (scope `UE::RenderTraceInsights::FRenderTraceAnalyzer::__anon0c89b8ca0103`)
- L59 _enumerator_ `Packet_SubmitSignalQueueFence` (scope `UE::RenderTraceInsights::FRenderTraceAnalyzer::__anon0c89b8ca0103`)
- L60 _enumerator_ `Packet_SubmitResolveSyncPoint` (scope `UE::RenderTraceInsights::FRenderTraceAnalyzer::__anon0c89b8ca0103`)
- L61 _enumerator_ `Packet_ProcessSubmissionQueueExit` (scope `UE::RenderTraceInsights::FRenderTraceAnalyzer::__anon0c89b8ca0103`)
- L62 _enumerator_ `Packet_ProcessInterruptQueueEnter` (scope `UE::RenderTraceInsights::FRenderTraceAnalyzer::__anon0c89b8ca0103`)
- L63 _enumerator_ `Packet_InterruptQueueFenceSignaled` (scope `UE::RenderTraceInsights::FRenderTraceAnalyzer::__anon0c89b8ca0103`)
- L64 _enumerator_ `Packet_ProcessInterruptQueueExit` (scope `UE::RenderTraceInsights::FRenderTraceAnalyzer::__anon0c89b8ca0103`)
- L107 _macro_ `#define DECLARE_EVENT_PROCESSING_FUNC(EventName) void Process##EventName(const FEventData& EventData, uint32 ThreadID, double Timestamp)`
- L108 _delegate_ `DECLARE_EVENT_PROCESSING_FUNC(CommandListCreated);`
- L109 _delegate_ `DECLARE_EVENT_PROCESSING_FUNC(CommandListDetach);`
- L110 _delegate_ `DECLARE_EVENT_PROCESSING_FUNC(CommandListFinishRecording);`
- L111 _delegate_ `DECLARE_EVENT_PROCESSING_FUNC(CommandListDestroyed);`
- L112 _delegate_ `DECLARE_EVENT_PROCESSING_FUNC(AddDispatchPassCommandList);`
- L113 _delegate_ `DECLARE_EVENT_PROCESSING_FUNC(SubmitCommandLists);`
- L114 _delegate_ `DECLARE_EVENT_PROCESSING_FUNC(SplitTranslateJob);`
- L115 _delegate_ `DECLARE_EVENT_PROCESSING_FUNC(DispatchCommandList);`
- L116 _delegate_ `DECLARE_EVENT_PROCESSING_FUNC(BeginTranslateCommandList);`
- L117 _delegate_ `DECLARE_EVENT_PROCESSING_FUNC(ActivatePipelines);`
- L118 _delegate_ `DECLARE_EVENT_PROCESSING_FUNC(SetTranslateContext);`
- L119 _delegate_ `DECLARE_EVENT_PROCESSING_FUNC(EndTranslateCommandList);`
- L120 _delegate_ `DECLARE_EVENT_PROCESSING_FUNC(FinalizeTranslateJob);`
- L121 _delegate_ `DECLARE_EVENT_PROCESSING_FUNC(SubmitTranslateJobs);`
- L122 _delegate_ `DECLARE_EVENT_PROCESSING_FUNC(AssociateContext);`
- L123 _delegate_ `DECLARE_EVENT_PROCESSING_FUNC(PayloadCreated);`
- L124 _delegate_ `DECLARE_EVENT_PROCESSING_FUNC(AddPayload);`
- L125 _delegate_ `DECLARE_EVENT_PROCESSING_FUNC(CommandListOp);`
- L126 _delegate_ `DECLARE_EVENT_PROCESSING_FUNC(SyncPointOp);`
- L127 _delegate_ `DECLARE_EVENT_PROCESSING_FUNC(ManualFenceOp);`
- L128 _delegate_ `DECLARE_EVENT_PROCESSING_FUNC(ProcessSubmissionQueueEnter);`
- L129 _delegate_ `DECLARE_EVENT_PROCESSING_FUNC(SubmitYieldOnUnresolvedSyncPoint);`
- L130 _delegate_ `DECLARE_EVENT_PROCESSING_FUNC(SubmitYieldOnUnresolvedManualFence);`
- L131 _delegate_ `DECLARE_EVENT_PROCESSING_FUNC(SubmitWaitQueueFence);`
- L132 _delegate_ `DECLARE_EVENT_PROCESSING_FUNC(SubmitWaitManualFence);`
- L133 _delegate_ `DECLARE_EVENT_PROCESSING_FUNC(SubmitPlatformCommandLists);`
- L134 _delegate_ `DECLARE_EVENT_PROCESSING_FUNC(SubmitSignalManualFence);`
- L135 _delegate_ `DECLARE_EVENT_PROCESSING_FUNC(SubmitSignalQueueFence);`
- L136 _delegate_ `DECLARE_EVENT_PROCESSING_FUNC(SubmitResolveSyncPoint);`
- L137 _delegate_ `DECLARE_EVENT_PROCESSING_FUNC(ProcessSubmissionQueueExit);`
- L138 _delegate_ `DECLARE_EVENT_PROCESSING_FUNC(ProcessInterruptQueueEnter);`
- L139 _delegate_ `DECLARE_EVENT_PROCESSING_FUNC(InterruptQueueFenceSignaled);`
- L140 _delegate_ `DECLARE_EVENT_PROCESSING_FUNC(ProcessInterruptQueueExit);`

### `Plugins/RenderTraceInsights/Source/RenderTraceInsights/Private/RenderTraceInsightsModule.h` (Private)


#### class `UE::RenderTraceInsights::FRenderTraceInsightsModule`  
`class FRenderTraceInsightsModule : public IModuleInterface`  
_L15-28_
- inherits: `IModuleInterface`
- L18 _public prototype_ `static FRenderTraceInsightsModule& Get();`
- L21 _public prototype_ `virtual void StartupModule() override;`
- L22 _public prototype_ `virtual void ShutdownModule() override;`
- L26 _private member_ `FRenderTraceModule TraceModule;`
- L27 _private member_ `FRenderTraceTimingViewExtender TimingViewExtender;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L12 _namespace_ `namespace RenderTraceInsights` (scope `UE`)

### `Plugins/RenderTraceInsights/Source/RenderTraceInsights/Private/RenderTraceModule.h` (Private)


#### class `UE::RenderTraceInsights::FRenderTraceModule`  
`class FRenderTraceModule : public TraceServices::IModule`  
_L14-26_
- inherits: `TraceServices::IModule`
- L18 _public prototype_ `virtual void GetModuleInfo(TraceServices::FModuleInfo& OutModuleInfo) override;`
- L19 _public prototype_ `virtual void OnAnalysisBegin(TraceServices::IAnalysisSession& Session) override;`
- L20 _public prototype_ `virtual void GetLoggers(TArray<const TCHAR *>& OutLoggers) override;`
- L21 _public function_ `virtual const TCHAR* GetCommandLineArgument() override`
- L25 _private member_ `static FName ModuleName;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L9 _namespace_ `namespace RenderTraceInsights` (scope `UE`)
- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogRenderTrace, Log, All);`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogRenderTrace, Log, All);` (scope `UE::RenderTraceInsights`)

### `Plugins/RenderTraceInsights/Source/RenderTraceInsights/Private/RenderTraceProvider.h` (Private)


#### class `UE::RenderTraceInsights::FRenderTraceProvider`  
`class FRenderTraceProvider final : public IEditableRenderTraceProvider`  
_L19-149_
- inherits: `IEditableRenderTraceProvider`
- L24 _public member_ `static FName ProviderName;`
- L26 _public prototype_ `FRenderTraceProvider(TraceServices::IAnalysisSession& InSession);`
- L29 _public function_ `void BeginRead() const override` — IProvider methods.
- L30 _public function_ `void EndRead() const override`
- L31 _public function_ `void ReadAccessCheck() const override`
- L34 _public function_ `void BeginEdit() const override` — IEditableProvider methods.
- L35 _public function_ `void EndEdit() const override`
- L36 _public function_ `void EditAccessCheck() const override`
- L41 _public function_ `uint64 GetTimelinesModCount() const override`
- L43 _public prototype_ `int32 GetNumCommandLists() const override;`
- L44 _public prototype_ `const FCommandListInstance& GetCommandList(uint32 ID) const override;`
- L45 _public prototype_ `int32 GetNumCommandListTimelines() const override;`
- L46 _public prototype_ `void ReadCommandListTimelines(TFunctionRef<void(uint32, const TEventTimeline&)> Callback) const override;`
- L48 _public prototype_ `int32 GetNumRDGPasses() const override;`
- L49 _public prototype_ `const FRDGPassInstance& GetRDGPass(uint32 ID) const override;`
- L50 _public prototype_ `void ReadRDGTimelines(TFunctionRef<void(uint32, uint32, const TEventTimeline&)> Callback) const override;`
- L51 _public prototype_ `const TEventTimeline* GetRenderThreadSubmissionTimeline() const override;`
- L53 _public prototype_ `int32 GetNumRHITranslateTasks() const override;`
- L54 _public prototype_ `const FRHITranslateTask& GetRHITranslateTask(uint32 ID) const override;`
- L55 _public prototype_ `uint32 FindRHITaskByPredicate(uint32 StartAtTaskID, double TimeRange, TFunctionRef<int(const FRHITranslateTask&)> Pred) const override;`
- L56 _public prototype_ `void EnumerateRHITranslateTimelines(TFunctionRef<void(uint32, uint32, const TEventTimeline&)> Callback) const override;`
- L57 _public prototype_ `const TEventTimeline* GetRHISubmissionTimeline() const override;`
- L59 _public prototype_ `int32 GetNumPlatformPayloads() const override;`
- L60 _public prototype_ `const FPlatformPayload& GetPlatformPayload(uint32 ID) const override;`
- L62 _public prototype_ `int32 GetNumSyncPoints() const override;`
- L63 _public prototype_ `const FSyncPoint& GetSyncPoint(uint32 ID) const override;`
- L65 _public prototype_ `int32 GetNumSubmissionBatches() const override;`
- L66 _public prototype_ `const FSubmissionBatch& GetSubmissionBatch(uint32 ID) const override;`
- L67 _public prototype_ `const TEventTimeline* GetSubmissionQueueTimeline() const override;`
- L69 _public prototype_ `int32 GetNumInterruptWakeUps() const override;`
- L70 _public prototype_ `const FInterruptWakeUp& GetInterruptWakeUp(uint32 ID) const override;`
- L71 _public prototype_ `const TEventTimeline* GetInterruptTimeline() const override;`
- L76 _public prototype_ `TPair<uint32, FCommandListInstance&> AddCommandList(uint64 AppID, double Timestamp, ECommandListType Type) override;`
- L77 _public prototype_ `FCommandListInstance& EditCommandList(uint32 ID) override;`
- L78 _public prototype_ `void EnumerateCommandListsForEdit(TFunctionRef<void(uint32, FCommandListInstance&)> Callback) override;`
- L79 _public prototype_ `TPair<uint32, TEventTimeline&> AddCommandListTimeline() override;`
- L80 _public prototype_ `TEventTimeline& EditCommandListTimeline(uint32 Index) override;`
- L82 _public prototype_ `TPair<uint32, FRDGPassInstance&> AddRDGPass(const TCHAR* Name, uint32 ThreadID, double Timestamp, ERDGPassType Type) override;`
- L83 _public prototype_ `FRDGPassInstance& EditRDGPass(uint32 ID) override;`
- L84 _public prototype_ `TEventTimeline& EditRDGThreadTimeline(uint32 ThreadID) override;`
- L85 _public prototype_ `TEventTimeline& EditRenderThreadSubmissionTimeline() override;`
- L87 _public prototype_ `TPair<uint32, FRHITranslateTask&> AddRHITranslateTask(uint64 AppID, ERHITranslateTaskType Type, uint32 ThreadID, double Timestamp) override;`
- L88 _public prototype_ `FRHITranslateTask& EditRHITranslateTask(uint32 ID) override;`
- L89 _public prototype_ `TEventTimeline& EditRHITranslateThreadTimeline(uint32 ThreadID) override;`
- L90 _public prototype_ `TEventTimeline& EditRHISubmissionTimeline() override;`
- L92 _public prototype_ `TPair<uint32, FPlatformPayload&> AddPlatformPayload(uint64 InAppID, double InStartTime, uint8 InPipeIdx) override;`
- L93 _public prototype_ `FPlatformPayload& EditPlatformPayload(uint32 ID) override;`
- L95 _public prototype_ `TPair<uint32, FSyncPoint&> AddSyncPoint(uint64 InAppID, ESyncPointType InType) override;`
- L96 _public prototype_ `FSyncPoint& EditSyncPoint(uint32 ID) override;`
- L98 _public prototype_ `TPair<uint32, FSubmissionBatch&> AddSubmissionBatch(uint32 ThreadID, double Timestamp) override;`
- L99 _public prototype_ `FSubmissionBatch& EditSubmissionBatch(uint32 ID) override;`
- L100 _public prototype_ `TEventTimeline& EditSubmissionQueueTimeline() override;`
- L102 _public prototype_ `TPair<uint32, FInterruptWakeUp&> AddInterruptWakeUp(uint32 ThreadID, double Timestamp) override;`
- L103 _public prototype_ `FInterruptWakeUp& EditInterruptWakeUp(uint32 ID) override;`
- L104 _public prototype_ `TEventTimeline& EditInterruptTimeline() override;`
- L118 _private member_ `TraceServices::IAnalysisSession& Session;`
- L120 _private member_ `TArray<FCommandListInstance> CommandLists;`
- L121 _private member_ `TArray<TUniquePtr<TEventTimeline>> CommandListTimelines;`
- L123 _private member_ `TArray<FRDGPassInstance> RDGPasses;`
- L124 _private member_ `TArray<FThreadTimeline> RDGTimelines;`
- L125 _private member_ `TMap<uint32, uint32> RDGThreadToTimeline;`
- L126 _private member_ `TUniquePtr<TEventTimeline> RTSubmissionTimeline;`
- L128 _private member_ `TArray<FRHITranslateTask> RHITranslateTasks;`
- L129 _private member_ `TArray<FThreadTimeline> RHITranslateTimelines;`
- L130 _private member_ `TMap<uint32, uint32> RHIThreadToTimeline;`
- L131 _private member_ `TUniquePtr<TEventTimeline> RHISubmissionTimeline;`
- L133 _private member_ `TArray<FPlatformPayload> PlatformPayloads;`
- L134 _private member_ `TArray<FSyncPoint> SyncPoints;`
- L136 _private member_ `TArray<FSubmissionBatch> SubmissionBatches;`
- L137 _private member_ `TUniquePtr<TEventTimeline> SubmissionQueueTimeline;`
- L139 _private member_ `TArray<FInterruptWakeUp> InterruptWakeUps;`
- L140 _private member_ `TUniquePtr<TEventTimeline> InterruptTimeline;`
- L142 _private member_ `mutable TraceServices::FProviderLock Lock;`
- L148 _private member_ `uint64 TimelinesModCount = 1;` — This is incremented whenever a timeline is added to let FRenderTraceTimingViewSession know that it needs to add the corresponding tracks. We don't track other modifications right now, such as adding command lists, RDG passes etc. We start at 1 because FRenderTraceTimingViewSession starts its cached value at 0, so this was we always trigger an update on the first tick.

#### struct `UE::RenderTraceInsights::FRenderTraceProvider::FThreadTimeline`  
`struct FThreadTimeline`  
_L107-116_
- L109 _public function_ `FThreadTimeline(uint32 InThreadID, TraceServices::ILinearAllocator& InAllocator) : ThreadID(InThreadID) , Timeline(MakeUnique<TEventTimeline>(InAllocator))`
- L114 _public member_ `uint32 ThreadID;`
- L115 _public member_ `TUniquePtr<TEventTimeline> Timeline;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace TraceServices`
- L12 _namespace_ `namespace UE`
- L14 _namespace_ `namespace RenderTraceInsights` (scope `UE`)
- L17 _externvar_ `extern thread_local TraceServices::FProviderLock::FThreadLocalState GRenderTraceProviderLockState;` (scope `UE::RenderTraceInsights`)

### `Plugins/RenderTraceInsights/Source/RenderTraceInsights/Private/RenderTraceTimingViewExtender.h` (Private)


#### class `UE::RenderTraceInsights::FRenderTraceTimingViewExtender`  
`class FRenderTraceTimingViewExtender : public UE::Insights::Timing::ITimingViewExtender`  
_L17-35_
- inherits: `UE::Insights::Timing::ITimingViewExtender`
- L21 _public prototype_ `virtual void OnBeginSession(UE::Insights::Timing::ITimingViewSession& InSession) override;`
- L22 _public prototype_ `virtual void OnEndSession(UE::Insights::Timing::ITimingViewSession& InSession) override;`
- L23 _public prototype_ `virtual void Tick(UE::Insights::Timing::ITimingViewSession& InSession, const TraceServices::IAnalysisSession& InAnalysisSession) override;`
- L24 _public prototype_ `virtual void ExtendFilterMenu(UE::Insights::Timing::ITimingViewSession& InSession, FMenuBuilder& InMenuBuilder) override;`
- L34 _private member_ `TMap<UE::Insights::Timing::ITimingViewSession*, FPerSessionData> PerSessionDataMap;` — The data we host per-session

#### struct `UE::RenderTraceInsights::FRenderTraceTimingViewExtender::FPerSessionData`  
`struct FPerSessionData`  
_L28-31_
- L30 _public member_ `TSharedPtr<FRenderTraceTimingViewSession> SharedData;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Insights` (scope `UE`)
- L8 _namespace_ `namespace Timing` (scope `UE::Insights`)
- L9 _namespace_ `namespace TraceServices`
- L12 _namespace_ `namespace UE`
- L14 _namespace_ `namespace RenderTraceInsights` (scope `UE`)

### `Plugins/RenderTraceInsights/Source/RenderTraceInsights/Private/RenderTraceTimingViewSession.h` (Private)


#### class `UE::RenderTraceInsights::FRenderTraceTimingViewSession`  
`class FRenderTraceTimingViewSession : public TSharedFromThis<FRenderTraceTimingViewSession>`  
_L27-72_
- inherits: `TSharedFromThis<FRenderTraceTimingViewSession>`
- L30 _public prototype_ `FRenderTraceTimingViewSession() = default;`
- L32 _public prototype_ `void OnBeginSession(UE::Insights::Timing::ITimingViewSession& InTimingViewSession);`
- L33 _public prototype_ `void OnEndSession(UE::Insights::Timing::ITimingViewSession& InTimingViewSession);`
- L34 _public prototype_ `void Tick(UE::Insights::Timing::ITimingViewSession& InTimingViewSession, const TraceServices::IAnalysisSession& InAnalysisSession);`
- L35 _public prototype_ `void ExtendFilterMenu(FMenuBuilder& InMenuBuilder);`
- L37 _public function_ `const TraceServices::IAnalysisSession& GetAnalysisSession() const`
- L38 _public function_ `UE::Insights::Timing::ITimingViewSession* GetTimingViewSession() const`
- L39 _public function_ `const IRenderTraceProvider* GetRenderTraceProvider() const`
- L40 _public prototype_ `TSharedPtr<const FRDGThreadTrack> GetRDGThreadTrack(uint32 ThreadID) const;`
- L41 _public function_ `TSharedPtr<const FCommandListTrack> GetCommandListTrack(int32 Index) const`
- L42 _public prototype_ `TSharedPtr<const FRHIThreadTrack> GetRHIThreadTrack(uint32 ThreadID) const;`
- L43 _public function_ `TSharedPtr<const FSubmissionQueueTrack> GetSubmissionTrack() const`
- L44 _public function_ `TSharedPtr<const FInterruptTrack> GetInterruptTrack() const`
- L46 _public prototype_ `TSharedPtr<const FBaseTimingTrack> GetCpuThreadTrack(uint32 ThreadID) const;`
- L49 _private prototype_ `void ClearState();`
- L50 _private prototype_ `void ToggleRenderTraceTrack();`
- L51 _private prototype_ `void OnEventSelected(TSharedPtr<const ITimingEvent> InSelectedEvent);`
- L53 _private member_ `const TraceServices::IAnalysisSession* AnalysisSession = nullptr;`
- L54 _private member_ `UE::Insights::Timing::ITimingViewSession* TimingViewSession = nullptr;`
- L55 _private member_ `const IRenderTraceProvider* RenderTraceProvider = nullptr;`
- L57 _private member_ `TArray<TSharedPtr<FRDGThreadTrack>> RDGPassTracks;`
- L58 _private member_ `TMap<uint32, uint32> RDGThreadToTrackIndex;`
- L60 _private member_ `TArray<TSharedPtr<FCommandListTrack>> CommandListTracks;`
- L62 _private member_ `TArray<TSharedPtr<FRHIThreadTrack>> RHIThreadTracks;`
- L63 _private member_ `TMap<uint32, uint32> RHIThreadToTrackIndex;`
- L65 _private member_ `TSharedPtr<FSubmissionQueueTrack> SubmissionQueueTrack;`
- L66 _private member_ `TSharedPtr<FInterruptTrack> InterruptTrack;`
- L68 _private member_ `bool bTracksVisible = true;`
- L69 _private member_ `uint64 LastTimelinesModCount = 0;`
- L71 _private member_ `mutable TMap<uint32, TWeakPtr<FBaseTimingTrack>> CpuThreadTrackCache;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace TraceServices`
- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Insights` (scope `UE`)
- L8 _namespace_ `namespace Timing` (scope `UE::Insights`)
- L14 _namespace_ `namespace UE`
- L16 _namespace_ `namespace RenderTraceInsights` (scope `UE`)

### `Plugins/RenderTraceInsights/Source/RenderTraceInsights/Private/RenderTraceTrack.h` (Private)


#### class `UE::RenderTraceInsights::FRenderTraceRelation`  
`class FRenderTraceRelation : public ITimingEventRelation`  
_L23-42_
- inherits: `ITimingEventRelation`
- L29 _public prototype_ `FRenderTraceRelation(TSharedPtr<const FBaseTimingTrack> InSourceTrack, double InSourceTime, uint32 InSourceDepth, TSharedPtr<const FBaseTimingTrack> InTargetTrack, double InTargetTime, uint32 InTargetDepth, const FLinearColor& InColor);`
- L30 _public prototype_ `virtual ~FRenderTraceRelation() = default;`
- L32 _public prototype_ `void Draw(const UE::Insights::FDrawContext& DrawContext, const FTimingTrackViewport& Viewport, const ITimingViewDrawHelper& Helper, const ITimingEventRelation::EDrawFilter Filter) override;`
- L35 _private member_ `TWeakPtr<const FBaseTimingTrack> SourceTrack;`
- L36 _private member_ `TWeakPtr<const FBaseTimingTrack> TargetTrack;`
- L37 _private member_ `double SourceTime;`
- L38 _private member_ `double TargetTime;`
- L39 _private member_ `uint32 SourceDepth;`
- L40 _private member_ `uint32 TargetDepth;`
- L41 _private member_ `FLinearColor Color;`

#### class `UE::RenderTraceInsights::FRenderTraceTrack`  
`class FRenderTraceTrack : public FTimingEventsTrack`  
_L44-69_
- inherits: `FTimingEventsTrack`
- L49 _public prototype_ `FRenderTraceTrack(const FRenderTraceTimingViewSession& InSharedData, const FString& Name, const IRenderTraceProvider::TEventTimeline* InTimeline);`
- L52 _public prototype_ `const TSharedPtr<const ITimingEvent> GetEvent(double InTime, double SecondsPerPixel, int32 Depth) const override;` — FBaseTimingTrack interface.
- L53 _public prototype_ `void InitTooltip(FTooltipDrawState& Tooltip, const ITimingEvent& TooltipEvent) const override;`
- L54 _public prototype_ `void OnClipboardCopyEvent(const ITimingEvent& InSelectedEvent) const override;`
- L57 _public prototype_ `void BuildDrawState(ITimingEventsTrackDrawStateBuilder& Builder, const ITimingTrackUpdateContext& Context) override;` — FTimingEventsTrack interface.
- L60 _public function_ `virtual void OnRenderTraceEventSelected(const FTimingEvent& InSelectedEvent) const` — Interface that subclasses must implement.
- L61 _public function_ `virtual FString GetEventName(const IRenderTraceProvider* Provider, uint32 InDepth, const FRenderTraceEvent& InEvent) const`
- L62 _public function_ `virtual void PopulateEventDetails(IEventDetailsBuilder& Builder, const FTimingEvent& Event) const`
- L63 _public function_ `virtual void CustomizeEventDrawState(ITimingEventsTrackDrawStateBuilder& Builder, double StartTime, double EndTime, uint32 Depth, const FRenderTraceEvent& Event) const`
- L64 _public function_ `virtual TSharedPtr<FTimingEvent> GetEventAtTime(double EventTime, int32 EventDepth, double TimelineEventStart, double TimelineEventEnd, int32 TimelineEventDepth, const FRenderTraceEvent& TimelineEvent) const`
- L67 _protected member_ `const FRenderTraceTimingViewSession& SharedData;`
- L68 _protected member_ `const IRenderTraceProvider::TEventTimeline* Timeline;`

#### class `UE::RenderTraceInsights::FCommandListTrack`  
`class FCommandListTrack : public FRenderTraceTrack`  
_L71-88_
- inherits: `FRenderTraceTrack`
- L76 _public prototype_ `FCommandListTrack(const FRenderTraceTimingViewSession& InSharedData, const FString& Name, const IRenderTraceProvider::TEventTimeline* InTimeline);`
- L79 _public prototype_ `void OnRenderTraceEventSelected(const FTimingEvent& InSelectedEvent) const override;` — FRenderTraceTrack interface.
- L80 _public prototype_ `FString GetEventName(const IRenderTraceProvider* Provider, uint32 InDepth, const FRenderTraceEvent& InEvent) const override;`
- L81 _public prototype_ `void PopulateEventDetails(IEventDetailsBuilder& Builder, const FTimingEvent& Event) const override;`
- L84 _private prototype_ `void OnCommandListSelected(const FTimingEvent& InSelectedEvent) const;`
- L85 _private prototype_ `void OnRecordingEventSelected(const FTimingEvent& InSelectedEvent) const;`
- L86 _private prototype_ `void PopulateCommandListEventDetails(IEventDetailsBuilder& Builder, uint32 CmdListID) const;`
- L87 _private prototype_ `void PopulateRecordingEventDetails(IEventDetailsBuilder& Builder, uint32 PassID, double StartTime, double EndTime) const;`

#### class `UE::RenderTraceInsights::FRDGThreadTrack`  
`class FRDGThreadTrack : public FRenderTraceTrack`  
_L90-101_
- inherits: `FRenderTraceTrack`
- L95 _public prototype_ `FRDGThreadTrack(const FRenderTraceTimingViewSession& InSharedData, const FString& Name, const IRenderTraceProvider::TEventTimeline* InTimeline);`
- L98 _public prototype_ `void OnRenderTraceEventSelected(const FTimingEvent& InSelectedEvent) const override;` — FRenderTraceTrack interface.
- L99 _public prototype_ `FString GetEventName(const IRenderTraceProvider* Provider, uint32 InDepth, const FRenderTraceEvent& InEvent) const override;`
- L100 _public prototype_ `void PopulateEventDetails(IEventDetailsBuilder& Builder, const FTimingEvent& Event) const override;`

#### class `UE::RenderTraceInsights::FRenderThreadSubmissionTrack`  
`class FRenderThreadSubmissionTrack : public FRenderTraceTrack`  
_L103-114_
- inherits: `FRenderTraceTrack`
- L108 _public prototype_ `FRenderThreadSubmissionTrack(const FRenderTraceTimingViewSession& InSharedData, const FString& Name, const IRenderTraceProvider::TEventTimeline* InTimeline);`
- L111 _public prototype_ `void OnRenderTraceEventSelected(const FTimingEvent& InSelectedEvent) const override;` — FRenderTraceTrack interface.
- L112 _public prototype_ `FString GetEventName(const IRenderTraceProvider* Provider, uint32 InDepth, const FRenderTraceEvent& InEvent) const override;`
- L113 _public prototype_ `void PopulateEventDetails(IEventDetailsBuilder& Builder, const FTimingEvent& Event) const override;`

#### class `UE::RenderTraceInsights::FRHIThreadTrack`  
`class FRHIThreadTrack : public FRenderTraceTrack`  
_L116-140_
- inherits: `FRenderTraceTrack`
- L121 _public prototype_ `FRHIThreadTrack(const FRenderTraceTimingViewSession& InSharedData, const FString& Name, const IRenderTraceProvider::TEventTimeline* InTimeline);`
- L124 _public prototype_ `void OnRenderTraceEventSelected(const FTimingEvent& InSelectedEvent) const override;` — FRenderTraceTrack interface.
- L125 _public prototype_ `FString GetEventName(const IRenderTraceProvider* Provider, uint32 InDepth, const FRenderTraceEvent& InEvent) const override;`
- L126 _public prototype_ `void PopulateEventDetails(IEventDetailsBuilder& Builder, const FTimingEvent& Event) const override;`
- L127 _public prototype_ `void CustomizeEventDrawState(ITimingEventsTrackDrawStateBuilder& Builder, double StartTime, double EndTime, uint32 Depth, const FRenderTraceEvent& Event) const override;`
- L128 _public prototype_ `TSharedPtr<FTimingEvent> GetEventAtTime(double EventTime, int32 EventDepth, double TimelineEventStart, double TimelineEventEnd, int32 TimelineEventDepth, const FRenderTraceEvent& TimelineEvent) const override;`
- L131 _private prototype_ `void CacheSplitFromTask(const IRenderTraceProvider& Provider, uint32 TaskID) const;`
- L132 _private prototype_ `void CacheSplitToTask(const IRenderTraceProvider& Provider, uint32 TaskID) const;`
- L133 _private prototype_ `void OnTranslateEventSelected(const FTimingEvent& InSelectedEvent) const;`
- L134 _private prototype_ `void OnTranslateCommandListEventSelected(const FTimingEvent& InSelectedEvent) const;`
- L135 _private prototype_ `void OnPayloadEventSelected(const FTimingEvent& InSelectedEvent, uint32 TranslateJobID, uint8 PipeIdx, uint32 PayloadIdx) const;`
- L136 _private prototype_ `void PopulateTranslateJobDetails(IEventDetailsBuilder& Builder, uint32 TaskID, const FRHITranslateTask& Task) const;`
- L137 _private prototype_ `void ListSyncPoints(IEventDetailsBuilder& Builder, const TCHAR* Title, TConstArrayView<uint32> SyncPointIDs) const;`
- L138 _private prototype_ `void PopulatePayloadDetails(IEventDetailsBuilder& Builder, uint32 TranslateJobID, uint32 PipeIdx, uint32 PayloadIdx) const;`
- L139 _private prototype_ `void PopulateTranslateContextDetails(IEventDetailsBuilder& Builder, uint32 TranslateJobID, uint32 PipeIdx) const;`

#### class `UE::RenderTraceInsights::FRHISubmissionTrack`  
`class FRHISubmissionTrack : public FRenderTraceTrack`  
_L142-158_
- inherits: `FRenderTraceTrack`
- L147 _public prototype_ `FRHISubmissionTrack(const FRenderTraceTimingViewSession& InSharedData, const FString& Name, const IRenderTraceProvider::TEventTimeline* InTimeline);`
- L150 _public prototype_ `void OnRenderTraceEventSelected(const FTimingEvent& InSelectedEvent) const override;` — FRenderTraceTrack interface.
- L151 _public prototype_ `FString GetEventName(const IRenderTraceProvider* Provider, uint32 InDepth, const FRenderTraceEvent& InEvent) const override;`
- L152 _public prototype_ `void PopulateEventDetails(IEventDetailsBuilder& Builder, const FTimingEvent& Event) const override;`
- L155 _private prototype_ `void OnSubmitEventSelected(const FTimingEvent& InSelectedEvent) const;`
- L156 _private prototype_ `void OnSubmitTranslateJobEventSelected(const FTimingEvent& InSelectedEvent) const;`
- L157 _private prototype_ `void PopulateSubmitTaskDetails(IEventDetailsBuilder& Builder, uint32 TaskID, const FRHITranslateTask& Task) const;`

#### class `UE::RenderTraceInsights::FSubmissionQueueTrack`  
`class FSubmissionQueueTrack : public FRenderTraceTrack`  
_L160-177_
- inherits: `FRenderTraceTrack`
- L165 _public prototype_ `FSubmissionQueueTrack(const FRenderTraceTimingViewSession& InSharedData, const FString& Name, const IRenderTraceProvider::TEventTimeline* InTimeline);`
- L168 _public prototype_ `void OnRenderTraceEventSelected(const FTimingEvent& InSelectedEvent) const override;` — FRenderTraceTrack interface.
- L169 _public prototype_ `FString GetEventName(const IRenderTraceProvider* Provider, uint32 InDepth, const FRenderTraceEvent& InEvent) const override;`
- L170 _public prototype_ `void PopulateEventDetails(IEventDetailsBuilder& Builder, const FTimingEvent& Event) const override;`
- L173 _private prototype_ `void PopulateSubmissionBatchDetails(IEventDetailsBuilder& Builder, uint32 ItemID) const;`
- L174 _private prototype_ `void OnSubmissionBatchSelected(const FTimingEvent& InSelectedEvent, uint32 BatchID) const;`
- L175 _private prototype_ `void OnResolveSyncPointEventSelected(const FTimingEvent& InSelectedEvent, const FSubmissionEvent::FResolveSyncPoint& ResolveEvent) const;`
- L176 _private prototype_ `void OnExecuteEventSelected(const FTimingEvent& InSelectedEvent, const FSubmissionEvent::FExecute& ExecEvent) const;`

#### class `UE::RenderTraceInsights::FInterruptTrack`  
`class FInterruptTrack : public FRenderTraceTrack`  
_L179-190_
- inherits: `FRenderTraceTrack`
- L184 _public prototype_ `FInterruptTrack(const FRenderTraceTimingViewSession& InSharedData, const FString& Name, const IRenderTraceProvider::TEventTimeline* InTimeline);`
- L187 _public prototype_ `void OnRenderTraceEventSelected(const FTimingEvent& InSelectedEvent) const override;` — FRenderTraceTrack interface.
- L188 _public prototype_ `FString GetEventName(const IRenderTraceProvider* Provider, uint32 InDepth, const FRenderTraceEvent& InEvent) const override;`
- L189 _public prototype_ `void PopulateEventDetails(IEventDetailsBuilder& Builder, const FTimingEvent& Event) const override;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L18 _namespace_ `namespace RenderTraceInsights` (scope `UE`)

### `Plugins/RenderTraceInsights/Source/RenderTraceInsights/Public/IRenderTraceProvider.h` (Public)


#### struct `UE::RenderTraceInsights::FTimeInterval`  
`struct FTimeInterval`  
_L22-29_
- L24 _public function_ `FTimeInterval() : Start(0.0), End(0.0)`
- L25 _public function_ `explicit FTimeInterval(double InStart) : Start(InStart), End(0.0)`
- L26 _public function_ `FTimeInterval(double InStart, double InEnd) : Start(InStart), End(InEnd)`
- L27 _public member_ `double Start;`
- L28 _public member_ `double End;`

#### struct `UE::RenderTraceInsights::FEventInterval`  
`struct FEventInterval`  
_L31-38_
- L33 _public function_ `FEventInterval(uint32 InItemID, double InStartTime) : ItemID(InItemID), Start(InStartTime), End(0.0)`
- L34 _public function_ `FEventInterval(uint32 InItemID, double InStartTime, double InEndTime) : ItemID(InItemID), Start(InStartTime), End(InEndTime)`
- L35 _public member_ `uint32 ItemID;`
- L36 _public member_ `double Start;`
- L37 _public member_ `double End;`

#### struct `UE::RenderTraceInsights::FRenderTraceEvent`  
`struct FRenderTraceEvent`  
_L40-47_
- L42 _public function_ `FRenderTraceEvent() : ItemID(INVALID_EVENT_ID), ParentItemID(INVALID_EVENT_ID)`
- L43 _public function_ `explicit FRenderTraceEvent(uint32 InItemID, uint32 InParentItemID = INVALID_EVENT_ID) : ItemID(InItemID), ParentItemID(InParentItemID)`
- L45 _public member_ `uint32 ItemID;`
- L46 _public member_ `uint32 ParentItemID;`

#### enum `UE::RenderTraceInsights::ECommandListType`  
`enum class ECommandListType : uint8`  
_L49-54_
- L51 _public enumerator_ `Regular`
- L52 _public enumerator_ `Immediate`
- L53 _public enumerator_ `Detached`

#### enum `UE::RenderTraceInsights::ECommandListRecordingFlags`  
`enum ECommandListRecordingFlags`  
_L56-59_
- L58 _public enumerator_ `ECommandListRecordingFlag_UsesLockFence = 1 << 0`

#### enum `UE::RenderTraceInsights::ERHITranslateJobSplitFlags`  
`enum ERHITranslateJobSplitFlags`  
_L61-67_
- L63 _public enumerator_ `ERHITranslateJobSplitFlag_Parallel = 1 << 0`
- L64 _public enumerator_ `ERHITranslateJobSplitFlag_Threshold = 1 << 1`
- L65 _public enumerator_ `ERHITranslateJobSplitFlag_ParentChild = 1 << 2`
- L66 _public enumerator_ `ERHITranslateJobSplitFlag_JumpThreads = 1 << 3`

#### struct `UE::RenderTraceInsights::FCommandListInstance`  
`struct FCommandListInstance`  
_L69-106_
- L72 _public function_ `FCommandListInstance(uint64 InAppID, double InCreateTime, ECommandListType InType) : AppID(InAppID) , Type(InType) , CreateTime(InCreateTime)`
- L78 _public member_ `uint64 AppID;`
- L79 _public member_ `ECommandListType Type;`
- L82 _public member_ `double CreateTime;` — Important timestamps for the lifetime of the command list.
- L83 _public member_ `double FinishRecordingTime{};`
- L84 _public member_ `double SubmitTime{};`
- L85 _public member_ `uint32 SubmitPassID = INVALID_EVENT_ID;`
- L86 _public member_ `double DestroyTime{};`
- L89 _public member_ `TArray<FEventInterval, TInlineAllocator<8>> RecordingEvents;` — Recording information.
- L90 _public member_ `uint8 RecordingFlags = 0;` — ECommandListRecordingFlags
- L93 _public member_ `uint32 DetachedCmdListID = INVALID_EVENT_ID;` — Detach information.
- L94 _public member_ `double DetachTime{};`
- L95 _public member_ `uint32 SourceCmdListID = INVALID_EVENT_ID;`
- L98 _public member_ `double DispatchTime{};` — Dispatch and translate information.
- L99 _public member_ `uint32 TranslateTaskID = INVALID_EVENT_ID;`
- L100 _public member_ `uint64 TranslatePrevJobAppID = 0;`
- L101 _public member_ `uint8 TranslateSplitFlags = 0;` — ERHITranslateJobSplitFlags
- L104 _public member_ `double TimelineStart{};` — Timeline information.
- L105 _public member_ `int32 TimelineIndex = -1;`

#### enum `UE::RenderTraceInsights::ERDGPassType`  
`enum class ERDGPassType : uint8`  
_L108-113_
- L110 _public enumerator_ `Regular`
- L111 _public enumerator_ `Dispatch`
- L112 _public enumerator_ `Submit`

#### enum `UE::RenderTraceInsights::ERDGPassFlags`  
`enum ERDGPassFlags`  
_L116-126_
- desc: Must be kept in sync with the enum of the same name in RenderGraphDefinitions.h.
- L118 _public enumerator_ `ERDGPassFlag_Raster = 1 << 0`
- L119 _public enumerator_ `ERDGPassFlag_Compute = 1 << 1`
- L120 _public enumerator_ `ERDGPassFlag_AsyncCompute = 1 << 2`
- L121 _public enumerator_ `ERDGPassFlag_Copy = 1 << 3`
- L122 _public enumerator_ `ERDGPassFlag_NeverCull = 1 << 4`
- L123 _public enumerator_ `ERDGPassFlag_SkipRenderPass = 1 << 5`
- L124 _public enumerator_ `ERDGPassFlag_NeverMerge = 1 << 6`
- L125 _public enumerator_ `ERDGPassFlag_NeverParallel = 1 << 7`

#### enum `UE::RenderTraceInsights::ERDGPassTaskMode`  
`enum class ERDGPassTaskMode : uint8`  
_L129-135_
- desc: Must be kept in sync with the enum of the same name in RenderGraphPass.h.
- L131 _public enumerator_ `Inline = 0`
- L132 _public enumerator_ `Await = 1`
- L133 _public enumerator_ `Async = 2`
- L134 _public enumerator_ `NotSet = 0xff`

#### enum `UE::RenderTraceInsights::ERDGPassSubmitFlags`  
`enum ERDGPassSubmitFlags`  
_L138-148_
- desc: Must be kept in sync ERHISubmitFlags. We don't want to use the enum in RHICommandList.h directly because some values are conditionally compiled.
- L140 _public enumerator_ `ERDGPassSubmitFlag_SubmitToGPU = 1 << 0`
- L141 _public enumerator_ `ERDGPassSubmitFlag_DeleteResources = 1 << 1`
- L142 _public enumerator_ `ERDGPassSubmitFlag_FlushRHIThread = 1 << 2`
- L143 _public enumerator_ `ERDGPassSubmitFlag_EndFrame = 1 << 3`
- L144 _public enumerator_ `ERDGPassSubmitFlag_EnableBypass = 1 << 4`
- L145 _public enumerator_ `ERDGPassSubmitFlag_DisableBypass = 1 << 5`
- L146 _public enumerator_ `ERDGPassSubmitFlag_EnableDrawEvents = 1 << 6`
- L147 _public enumerator_ `ERDGPassSubmitFlag_DisableDrawEvents = 1 << 7`

#### struct `UE::RenderTraceInsights::FRDGPassInstance`  
`struct FRDGPassInstance`  
_L150-178_
- L153 _public function_ `FRDGPassInstance(const TCHAR* InName, uint32 InExecThreadID, double InStartTime, ERDGPassType InType) : Name(InName) , Type(InType) , StartTime(InStartTime) , ExecThreadID(InExecThreadID)`
- L163 _public member_ `const TCHAR* Name;` — Pass names are allocated from the session's linear allocator using the IAnalysisSession::StoreString, so we can just point to them because the lifetime of the pass instances is tied to the lifetime of the session.
- L164 _public member_ `ERDGPassType Type;`
- L165 _public member_ `uint16 Flags = 0;` — Either ERDGPassFlags or ERDGPassSubmitFlags.
- L166 _public member_ `ERDGPassTaskMode TaskMode = ERDGPassTaskMode::NotSet;`
- L169 _public member_ `double StartTime;` — Execution information.
- L170 _public member_ `double EndTime{};`
- L171 _public member_ `uint32 ExecThreadID;`
- L174 _public member_ `TArray<uint32, TInlineAllocator<8>> CommandListIDs;` — Recording command lists.
- L177 _public member_ `uint32 SubmitTaskID = INVALID_EVENT_ID;` — Extra data for render thread submit events.

#### enum `UE::RenderTraceInsights::ESyncPointType`  
`enum class ESyncPointType : uint8`  
_L180-185_
- L182 _public enumerator_ `GPU = 0`
- L183 _public enumerator_ `GPUAndCPU = 1`
- L184 _public enumerator_ `Manual = 2`

#### struct `UE::RenderTraceInsights::FSyncPoint`  
`struct FSyncPoint`  
_L187-195_
- L190 _public function_ `FSyncPoint(uint64 InAppID, ESyncPointType InType) : AppID(InAppID), Type(InType)`
- L191 _public member_ `uint64 AppID;`
- L192 _public member_ `uint64 ResolvedValue = 0;`
- L193 _public member_ `ESyncPointType Type;`
- L194 _public member_ `uint32 ResolvedByPayload = INVALID_EVENT_ID;`

#### struct `UE::RenderTraceInsights::FPlatformPayload`  
`struct FPlatformPayload`  
_L197-212_
- L200 _public function_ `explicit FPlatformPayload(uint64 InAppID, double InStartTime, uint8 InPipeIdx) : AppID(InAppID), StartTime(InStartTime), PipeIdx(InPipeIdx)`
- L201 _public member_ `uint64 AppID;`
- L202 _public member_ `double StartTime;`
- L203 _public member_ `double EndTime = 0.0;`
- L204 _public member_ `uint8 PipeIdx;`
- L205 _public member_ `TArray<uint32, TInlineAllocator<1>> WaitSyncPoints;`
- L206 _public member_ `TArray<uint64, TInlineAllocator<1>> CmdLists;`
- L207 _public member_ `TArray<uint32, TInlineAllocator<1>> SignalSyncPoints;`
- L208 _public member_ `FRenderTraceEvent TranslateEvent;`
- L209 _public member_ `FRenderTraceEvent ExecutionEvent;`
- L210 _public member_ `FRenderTraceEvent InterruptEvent;`
- L211 _public member_ `TArray<FRenderTraceEvent> ResolveSyncPointEvents;`

#### struct `UE::RenderTraceInsights::FRHITranslateContext`  
`struct FRHITranslateContext`  
_L214-221_
- L217 _public function_ `FRHITranslateContext()`
- L218 _public member_ `uint64 RHIContextID = 0;`
- L219 _public member_ `TArray<FTimeInterval, TInlineAllocator<4>> ActiveIntervals;`
- L220 _public member_ `TArray<uint32, TInlineAllocator<2>> PayloadIDs;`

#### enum `UE::RenderTraceInsights::ERHITranslateTaskType`  
`enum class ERHITranslateTaskType : uint8`  
_L223-227_
- L225 _public enumerator_ `Translate`
- L226 _public enumerator_ `Submit`

#### enum `UE::RenderTraceInsights::ERHITranslateJobFlags`  
`enum ERHITranslateJobFlags`  
_L229-233_
- L231 _public enumerator_ `ERHITranslateJobFlag_Parallel = 1 << 0`
- L232 _public enumerator_ `ERHITranslateJobFlag_UsingSubCmdLists = 1 << 1`

#### struct `UE::RenderTraceInsights::FRHITranslateTask`  
`struct FRHITranslateTask`  
_L235-274_
- L239 _public function_ `FRHITranslateTask(uint64 InAppID, ERHITranslateTaskType InType, uint32 InThreadID, double InStartTime) : AppID(InAppID) , Type(InType) , ThreadID(InThreadID) , StartTime(InStartTime)`
- L247 _public member_ `uint64 AppID;` — Information about the task.
- L248 _public member_ `ERHITranslateTaskType Type;`
- L249 _public member_ `uint32 ThreadID;`
- L250 _public member_ `double StartTime;`
- L251 _public member_ `double EndTime{};`
- L254 _public member_ `TArray<FEventInterval, TInlineAllocator<8>> ProcessedItems;` — Items processed by the job (command lists, translate jobs etc.).
- L257 _public member_ `uint32 NextPhaseTaskID = INVALID_EVENT_ID;` — Next task in the translate chain (e.g. dispatch -> translate).
- L259 _public member_ `uint8 JobFlags = 0;` — ERHITranslateJobFlags
- L264 _public member_ `uint32 SubmitTaskID = INVALID_EVENT_ID;` — For a submit task, this identifies the render-thread submit pass ID if the instigator is the render thread, or the translate job if it's an eager submit. For a translate tasks, this identifies the submission it triggered, if any.
- L265 _public member_ `bool bEagerSubmission = false;`
- L269 _public member_ `mutable uint32 SplitFromTranslateTaskID = INVALID_EVENT_ID;` — Previous and next jobs when a translate chain is split. This is not computed during analysis because it's too complicated. Instead, we compute and cache these values on demand when an event is selected.
- L270 _public member_ `mutable uint32 SplitToTranslateTaskID = INVALID_EVENT_ID;`
- L273 _public member_ `FRHITranslateContext Contexts[2];` — Translation contexts, one per pipe: direct and async compute.

#### enum `UE::RenderTraceInsights::ESubmissionEvent`  
`enum ESubmissionEvent`  
_L277-287_
- desc: Must be kept in the same order as the subtype declarations in the FSubmissionEvent::Data variant.
- L279 _public enumerator_ `ESubmissionEvent_YieldSyncPoint`
- L280 _public enumerator_ `ESubmissionEvent_YieldManualFence`
- L281 _public enumerator_ `ESubmissionEvent_WaitQueueFence`
- L282 _public enumerator_ `ESubmissionEvent_WaitManualFence`
- L283 _public enumerator_ `ESubmissionEvent_Execute`
- L284 _public enumerator_ `ESubmissionEvent_SignalManualFence`
- L285 _public enumerator_ `ESubmissionEvent_SignalQueueFence`
- L286 _public enumerator_ `ESubmissionEvent_ResolveSyncPoint`

#### struct `UE::RenderTraceInsights::FSubmissionEvent`  
`struct FSubmissionEvent`  
_L289-353_
- L292 _public function_ `FSubmissionEvent(double InTimestamp, uint8 InQueue) : Timestamp(InTimestamp), Queue(InQueue)`
- L293 _public prototype_ `~FSubmissionEvent() = default;`
- L295 _public member_ `double Timestamp;`
- L296 _public member_ `uint8 Queue;`
- L352 _public member_ `TVariant<FYieldSyncPoint, FYieldManualFence, FWaitQueueFence, FWaitManualFence, FExecute, FSignalManualFence, FSignalQueueFence, FResolveSyncPoint> Data;`

#### struct `UE::RenderTraceInsights::FSubmissionEvent::FYieldSyncPoint`  
`struct FYieldSyncPoint`  
_L298-302_
- L300 _public member_ `uint64 PayloadID;`
- L301 _public member_ `uint64 SyncPointID;`

#### struct `UE::RenderTraceInsights::FSubmissionEvent::FYieldManualFence`  
`struct FYieldManualFence`  
_L304-309_
- L306 _public member_ `uint64 PayloadID;`
- L307 _public member_ `uint64 FenceID;`
- L308 _public member_ `uint64 FenceValue;`

#### struct `UE::RenderTraceInsights::FSubmissionEvent::FWaitQueueFence`  
`struct FWaitQueueFence`  
_L311-316_
- L313 _public member_ `uint64 PayloadID;`
- L314 _public member_ `uint8 OtherQueue;`
- L315 _public member_ `uint64 Value;`

#### struct `UE::RenderTraceInsights::FSubmissionEvent::FWaitManualFence`  
`struct FWaitManualFence`  
_L318-323_
- L320 _public member_ `uint64 PayloadID;`
- L321 _public member_ `uint64 FenceID;`
- L322 _public member_ `uint64 Value;`

#### struct `UE::RenderTraceInsights::FSubmissionEvent::FExecute`  
`struct FExecute`  
_L325-330_
- L327 _public function_ `FExecute(TConstArrayView<uint32> InPayloadIDs, TConstArrayView<uint64> InPlatformCmdListIDs) : PayloadIDs(InPayloadIDs), PlatformCmdListIDs(InPlatformCmdListIDs)`
- L328 _public member_ `TArray<uint32> PayloadIDs;`
- L329 _public member_ `TArray<uint64> PlatformCmdListIDs;`

#### struct `UE::RenderTraceInsights::FSubmissionEvent::FSignalManualFence`  
`struct FSignalManualFence`  
_L332-337_
- L334 _public member_ `uint64 PayloadID;`
- L335 _public member_ `uint64 FenceID;`
- L336 _public member_ `uint64 Value;`

#### struct `UE::RenderTraceInsights::FSubmissionEvent::FSignalQueueFence`  
`struct FSignalQueueFence`  
_L339-343_
- L341 _public member_ `uint64 PayloadID;`
- L342 _public member_ `uint64 Value;`

#### struct `UE::RenderTraceInsights::FSubmissionEvent::FResolveSyncPoint`  
`struct FResolveSyncPoint`  
_L345-350_
- L347 _public member_ `uint32 PayloadID;`
- L348 _public member_ `uint32 SyncPointID;`
- L349 _public member_ `uint64 Value;`

#### struct `UE::RenderTraceInsights::FSubmissionBatch`  
`struct FSubmissionBatch`  
_L355-365_
- L358 _public function_ `FSubmissionBatch(uint32 InThreadID, double InStartTime) : ThreadID(InThreadID), StartTime(InStartTime)`
- L360 _public member_ `uint32 ThreadID;`
- L361 _public member_ `double StartTime;`
- L362 _public member_ `double EndTime = 0.0;`
- L363 _public member_ `uint8 ExitStatus = 0;`
- L364 _public member_ `TArray<FSubmissionEvent> Events;`

#### struct `UE::RenderTraceInsights::FInterruptFenceSignaledEvent`  
`struct FInterruptFenceSignaledEvent`  
_L367-377_
- L369 _public function_ `FInterruptFenceSignaledEvent(double InTimestamp, uint8 InQueue, uint32 InPayloadID, uint64 InFenceValue, uint64 InLastCPUSignaledFenceValue) : Timestamp(InTimestamp), Queue(InQueue), PayloadID(InPayloadID), FenceValue(InFenceValue), LastCPUSignaledFenceValue(InLastCPUSignaledFenceValue)`
- L372 _public member_ `double Timestamp;`
- L373 _public member_ `uint8 Queue;`
- L374 _public member_ `uint32 PayloadID;`
- L375 _public member_ `uint64 FenceValue;`
- L376 _public member_ `uint64 LastCPUSignaledFenceValue;`

#### struct `UE::RenderTraceInsights::FInterruptWakeUp`  
`struct FInterruptWakeUp`  
_L379-390_
- L382 _public function_ `FInterruptWakeUp(uint32 InThreadID, double InStartTime) : ThreadID(InThreadID), StartTime(InStartTime)`
- L384 _public member_ `uint32 ThreadID;`
- L385 _public member_ `double StartTime;`
- L386 _public member_ `double EndTime = 0.0;`
- L387 _public member_ `uint8 ExitStatus = 0;`
- L389 _public member_ `TArray<FInterruptFenceSignaledEvent, TInlineAllocator<2>> SignalEvents;`

#### class `UE::RenderTraceInsights::IRenderTraceProvider`  
`class IRenderTraceProvider : public TraceServices::IProvider`  
_L392-438_
- inherits: `TraceServices::IProvider`
- L395 _public typedef_ `using TEventTimeline = TraceServices::TMonotonicTimeline<FRenderTraceEvent>;`
- L397 _public prototype_ `virtual uint64 GetTimelinesModCount() const = 0;`
- L403 _public prototype_ `virtual int32 GetNumCommandLists() const = 0;` — RHI command list handling.
- L404 _public prototype_ `virtual const FCommandListInstance& GetCommandList(uint32 ID) const = 0;`
- L405 _public prototype_ `virtual int32 GetNumCommandListTimelines() const = 0;`
- L406 _public prototype_ `virtual void ReadCommandListTimelines(TFunctionRef<void(uint32, const TEventTimeline&)> Callback) const = 0;`
- L409 _public prototype_ `virtual int32 GetNumRDGPasses() const = 0;` — RDG pass handling.
- L410 _public prototype_ `virtual const FRDGPassInstance& GetRDGPass(uint32 ID) const = 0;`
- L411 _public prototype_ `virtual void ReadRDGTimelines(TFunctionRef<void(uint32, uint32, const TEventTimeline&)> Callback) const = 0;`
- L412 _public prototype_ `virtual const TEventTimeline* GetRenderThreadSubmissionTimeline() const = 0;`
- L415 _public prototype_ `virtual int32 GetNumRHITranslateTasks() const = 0;` — RHI translate task handling.
- L416 _public prototype_ `virtual const FRHITranslateTask& GetRHITranslateTask(uint32 ID) const = 0;`
- L417 _public prototype_ `virtual uint32 FindRHITaskByPredicate(uint32 StartAtTaskID, double TimeRange, TFunctionRef<int(const FRHITranslateTask&)> Pred) const = 0;`
- L418 _public prototype_ `virtual void EnumerateRHITranslateTimelines(TFunctionRef<void(uint32, uint32, const TEventTimeline&)> Callback) const = 0;`
- L419 _public prototype_ `virtual const TEventTimeline* GetRHISubmissionTimeline() const = 0;`
- L422 _public prototype_ `virtual int32 GetNumPlatformPayloads() const = 0;` — Platform payload handling.
- L423 _public prototype_ `virtual const FPlatformPayload& GetPlatformPayload(uint32 ID) const = 0;`
- L426 _public prototype_ `virtual int32 GetNumSyncPoints() const = 0;` — Sync point handling.
- L427 _public prototype_ `virtual const FSyncPoint& GetSyncPoint(uint32 ID) const = 0;`
- L430 _public prototype_ `virtual int32 GetNumSubmissionBatches() const = 0;` — Submission queue handling.
- L431 _public prototype_ `virtual const FSubmissionBatch& GetSubmissionBatch(uint32 ID) const = 0;`
- L432 _public prototype_ `virtual const TEventTimeline* GetSubmissionQueueTimeline() const = 0;`
- L435 _public prototype_ `virtual int32 GetNumInterruptWakeUps() const = 0;` — Interrupt queue handling.
- L436 _public prototype_ `virtual const FInterruptWakeUp& GetInterruptWakeUp(uint32 ID) const = 0;`
- L437 _public prototype_ `virtual const TEventTimeline* GetInterruptTimeline() const = 0;`

#### class `UE::RenderTraceInsights::IEditableRenderTraceProvider`  
`class IEditableRenderTraceProvider : public IRenderTraceProvider, public TraceServices::IEditableProvider`  
_L440-472_
- inherits: `IRenderTraceProvider,TraceServices::IEditableProvider`
- L443 _public prototype_ `virtual TPair<uint32, FCommandListInstance&> AddCommandList(uint64 AppID, double Timestamp, ECommandListType Type) = 0;`
- L444 _public prototype_ `virtual FCommandListInstance& EditCommandList(uint32 ID) = 0;`
- L445 _public prototype_ `virtual void EnumerateCommandListsForEdit(TFunctionRef<void(uint32, FCommandListInstance&)> Callback) = 0;`
- L446 _public prototype_ `virtual TPair<uint32, TEventTimeline&> AddCommandListTimeline() = 0;`
- L447 _public prototype_ `virtual TEventTimeline& EditCommandListTimeline(uint32 Index) = 0;`
- L449 _public prototype_ `virtual TPair<uint32, FRDGPassInstance&> AddRDGPass(const TCHAR* Name, uint32 ThreadID, double Timestamp, ERDGPassType Type) = 0;`
- L450 _public prototype_ `virtual FRDGPassInstance& EditRDGPass(uint32 ID) = 0;`
- L451 _public prototype_ `virtual TEventTimeline& EditRDGThreadTimeline(uint32 ThreadID) = 0;`
- L452 _public prototype_ `virtual TEventTimeline& EditRenderThreadSubmissionTimeline() = 0;`
- L454 _public prototype_ `virtual TPair<uint32, FRHITranslateTask&> AddRHITranslateTask(uint64 AppID, ERHITranslateTaskType Type, uint32 ThreadID, double Timestamp) = 0;`
- L455 _public prototype_ `virtual FRHITranslateTask& EditRHITranslateTask(uint32 ID) = 0;`
- L456 _public prototype_ `virtual TEventTimeline& EditRHITranslateThreadTimeline(uint32 ThreadID) = 0;`
- L457 _public prototype_ `virtual TEventTimeline& EditRHISubmissionTimeline() = 0;`
- L459 _public prototype_ `virtual TPair<uint32, FPlatformPayload&> AddPlatformPayload(uint64 InAppID, double InStartTime, uint8 InPipeIdx) = 0;`
- L460 _public prototype_ `virtual FPlatformPayload& EditPlatformPayload(uint32 ID) = 0;`
- L462 _public prototype_ `virtual TPair<uint32, FSyncPoint&> AddSyncPoint(uint64 InAppID, ESyncPointType InType) = 0;`
- L463 _public prototype_ `virtual FSyncPoint& EditSyncPoint(uint32 ID) = 0;`
- L465 _public prototype_ `virtual TPair<uint32, FSubmissionBatch&> AddSubmissionBatch(uint32 ThreadID, double Timestamp) = 0;`
- L466 _public prototype_ `virtual FSubmissionBatch& EditSubmissionBatch(uint32 ID) = 0;`
- L467 _public prototype_ `virtual TEventTimeline& EditSubmissionQueueTimeline() = 0;`
- L469 _public prototype_ `virtual TPair<uint32, FInterruptWakeUp&> AddInterruptWakeUp(uint32 ThreadID, double Timestamp) = 0;`
- L470 _public prototype_ `virtual FInterruptWakeUp& EditInterruptWakeUp(uint32 ID) = 0;`
- L471 _public prototype_ `virtual TEventTimeline& EditInterruptTimeline() = 0;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace TraceServices`
- L15 _namespace_ `namespace UE`
- L17 _namespace_ `namespace RenderTraceInsights` (scope `UE`)
- L20 _variable_ `static constexpr uint32 INVALID_EVENT_ID = ~0u;` (scope `UE::RenderTraceInsights`)
- L474 _prototype_ `FName GetRenderTraceProviderName();` (scope `UE::RenderTraceInsights`)
- L475 _prototype_ `const IRenderTraceProvider* ReadRenderTraceProvider(const TraceServices::IAnalysisSession& Session);` (scope `UE::RenderTraceInsights`)
- L476 _prototype_ `IEditableRenderTraceProvider* EditRenderTraceProvider(TraceServices::IAnalysisSession& Session);` (scope `UE::RenderTraceInsights`)
