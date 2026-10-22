# Plugins / FieldNotificationTraceEditor

- module root: `Plugins/Developer/FieldNotificationTrace/Source/FieldNotificationTraceEditor`
- headers: 6; symbols: 110
- symbol kinds: class=9, enum=1, enumerator=4, function=5, member=27, namespace=16, prototype=46, struct=2
- PrivateDependencyModuleNames: GameplayInsights, RewindDebuggerInterface, RewindDebuggerRuntimeInterface, Slate, SlateCore, TraceAnalysis, TraceLog, TraceServices
- PublicDependencyModuleNames: Core, CoreUObject, Engine, FieldNotification, FieldNotificationTrace

### `Plugins/Developer/FieldNotificationTrace/Source/FieldNotificationTraceEditor/Private/FieldNotificationRewindDebugger.h` (Private)


#### class `UE::FieldNotification::FRewindDebuggerExtension`  
`class FRewindDebuggerExtension : public IRewindDebuggerExtension`  
_L12-16_
- inherits: `IRewindDebuggerExtension`
- L15 _public prototype_ `virtual void Update(float DeltaTime, IRewindDebugger* RewindDebugger) override;`

#### class `UE::FieldNotification::FRewindDebuggerRuntimeExtension`  
`class FRewindDebuggerRuntimeExtension : public IRewindDebuggerRuntimeExtension`  
_L19-24_
- inherits: `IRewindDebuggerRuntimeExtension`
- L22 _public prototype_ `virtual void RecordingStarted() override;`
- L23 _public prototype_ `virtual void RecordingStopped() override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace FieldNotification` (scope `UE`)

### `Plugins/Developer/FieldNotificationTrace/Source/FieldNotificationTraceEditor/Private/FieldNotificationTraceAnalyzer.h` (Private)


#### class `UE::FieldNotification::FTraceAnalyzer`  
`class FTraceAnalyzer : public UE::Trace::IAnalyzer`  
_L13-34_
- inherits: `UE::Trace::IAnalyzer`
- L16 _public prototype_ `FTraceAnalyzer(TraceServices::IAnalysisSession& InSession, FTraceProvider& InProvider);`
- L18 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L19 _public function_ `virtual void OnAnalysisEnd() override`
- L20 _public prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L32 _private member_ `TraceServices::IAnalysisSession& Session;`
- L33 _private member_ `FTraceProvider& Provider;`

#### enum `UE::FieldNotification::FTraceAnalyzer::(anonymous)`  
``  
_L24-30_

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace FieldNotification` (scope `UE`)
- L8 _namespace_ `namespace TraceServices`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace FieldNotification` (scope `UE`)
- L25 _enumerator_ `RouteId_ObjectBegin` (scope `UE::FieldNotification::FTraceAnalyzer::__anon5529ff350103`)
- L26 _enumerator_ `RouteId_ObjectEnd` (scope `UE::FieldNotification::FTraceAnalyzer::__anon5529ff350103`)
- L27 _enumerator_ `RouteId_FieldValueChanged` (scope `UE::FieldNotification::FTraceAnalyzer::__anon5529ff350103`)
- L29 _enumerator_ `RouteId_StringId` (scope `UE::FieldNotification::FTraceAnalyzer::__anon5529ff350103`) — RouteId_PropertyValueChanged,

### `Plugins/Developer/FieldNotificationTrace/Source/FieldNotificationTraceEditor/Private/FieldNotificationTraceEditorModule.h` (Private)


#### class `UE::FieldNotification::FTraceEditorModule`  
`class FTraceEditorModule : public IModuleInterface`  
_L17-34_
- inherits: `IModuleInterface`
- L20 _public prototype_ `FTraceEditorModule() = default;`
- L23 _public prototype_ `virtual void StartupModule() override;`
- L24 _public prototype_ `virtual void ShutdownModule() override;`
- L28 _private member_ `FRewindDebuggerExtension RewindDebuggerExtension;`
- L29 _private member_ `FRewindDebuggerRuntimeExtension RewindDebuggerRuntimeExtension;`
- L31 _private member_ `FTracksCreator TrackCreator;`
- L33 _private member_ `FTraceServiceModule TraceModule;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace FieldNotification` (scope `UE`)

### `Plugins/Developer/FieldNotificationTrace/Source/FieldNotificationTraceEditor/Private/FieldNotificationTraceProvider.h` (Private)


#### class `UE::FieldNotification::FTraceProvider`  
`class FTraceProvider : public TraceServices::IProvider`  
_L18-67_
- inherits: `TraceServices::IProvider`
- L35 _public member_ `static FName ProviderName;`
- L37 _public prototype_ `FTraceProvider(TraceServices::IAnalysisSession& InSession);`
- L39 _public prototype_ `void EnumerateObjects(double InStartTime, double InEndTime, TFunctionRef<void(double InStartTime, double InEndTime, uint32 InDepth, const FObject&)> Callback) const;`
- L40 _public prototype_ `void EnumerateFieldNotifies(uint64 InObjectId, double InStartTime, double InEndTime, TFunctionRef<void(double InStartTime, double InEndTime, uint32 InDepth, const FFieldNotifyEvent&)> Callback) const;`
- L41 _public prototype_ `void EnumerateRecordingFieldNotifies(uint64 InObjectId, double InStartTime, double InEndTime, TFunctionRef<void(double InStartTime, double InEndTime, uint32 InDepth, const FFieldNotifyEvent&)> Callback) const;`
- L42 _public prototype_ `FFieldNotificationId GetFieldNotificationId(uint32 InFieldNotifyId) const;`
- L44 _public function_ `bool HasData() const`
- L49 _public function_ `bool HasData(uint64 InObjectId) const`
- L54 _public prototype_ `void AppendObjectBegin(uint64 InObjectId, double InProfileTime);`
- L55 _public prototype_ `void AppendObjectEnd(uint64 InObjectId, double InProfileTime);`
- L56 _public prototype_ `void AppendFieldValueChanged(uint64 InObjectId, double InProfileTime, double InRecordingTime, uint32 InFieldNotifyId);`
- L57 _public prototype_ `void AppendFieldNotify(uint32 InFieldNotifyId, FName InValue);`
- L60 _private member_ `TraceServices::IAnalysisSession& Session;`
- L62 _private member_ `TMap<uint32, FName> FieldNotifyIdToFieldNotifyName;`
- L63 _private member_ `TMap<uint64, TSharedRef<FObject>> ObjectIdToObject;`
- L66 _private member_ `TraceServices::TIntervalTimeline<TSharedRef<FObject>> ObjectLifetimes;` — Timeline containing intervals where an object exists

#### struct `UE::FieldNotification::FTraceProvider::FFieldNotifyEvent`  
`struct FFieldNotifyEvent`  
_L21-24_
- L23 _public member_ `uint32 FieldNotifyId = 0;`

#### struct `UE::FieldNotification::FTraceProvider::FObject`  
`struct FObject`  
_L26-33_
- L28 _public prototype_ `FObject(TraceServices::IAnalysisSession& InSession);`
- L29 _public member_ `uint64 SelfObjectId = 0;`
- L30 _public member_ `uint64 TimelineId = 0;`
- L31 _public member_ `TraceServices::TPointTimeline<FFieldNotifyEvent> FieldNotifies;`
- L32 _public member_ `TraceServices::TPointTimeline<FFieldNotifyEvent> FieldNotifiesRecording;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace TraceServices`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace FieldNotification` (scope `UE`)

### `Plugins/Developer/FieldNotificationTrace/Source/FieldNotificationTraceEditor/Private/FieldNotificationTraceServices.h` (Private)


#### class `UE::FieldNotification::FTraceServiceModule`  
`class FTraceServiceModule : public TraceServices::IModule`  
_L13-28_
- inherits: `TraceServices::IModule`
- L17 _public prototype_ `virtual void GetModuleInfo(TraceServices::FModuleInfo& OutModuleInfo) override;`
- L18 _public prototype_ `virtual void OnAnalysisBegin(TraceServices::IAnalysisSession& Session) override;`
- L19 _public prototype_ `virtual void GetLoggers(TArray<const TCHAR *>& OutLoggers) override;`
- L20 _public prototype_ `virtual void GenerateReports(const TraceServices::IAnalysisSession& Session, const TCHAR* CmdLine, const TCHAR* OutputDirectory) override;`
- L21 _public function_ `virtual const TCHAR* GetCommandLineArgument() override`
- L27 _private member_ `static FName ModuleName;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace FieldNotification` (scope `UE`)

### `Plugins/Developer/FieldNotificationTrace/Source/FieldNotificationTraceEditor/Private/FieldNotificationTrack.h` (Private)


#### class `UE::FieldNotification::FFieldNotifyTrack`  
`class FFieldNotifyTrack : public RewindDebugger::FRewindDebuggerTrack`  
_L15-45_
- inherits: `RewindDebugger::FRewindDebuggerTrack`
- L18 _public prototype_ `FFieldNotifyTrack(uint64 InObjectId, uint32 InFieldNotifyId, FFieldNotificationId InFieldNotify);`
- L20 _public function_ `uint32 GetFieldNotifyId() const`
- L26 _private prototype_ `virtual bool UpdateInternal() override;`
- L27 _private prototype_ `TSharedPtr<SWidget> GetDetailsViewInternal() override;`
- L28 _private prototype_ `virtual TSharedPtr<SWidget> GetTimelineViewInternal() override;`
- L29 _private prototype_ `virtual FSlateIcon GetIconInternal() override;`
- L30 _private prototype_ `virtual FName GetNameInternal() const override;`
- L31 _private prototype_ `virtual FText GetDisplayNameInternal() const override;`
- L32 _private prototype_ `virtual uint64 GetObjectIdInternal() const override;`
- L33 _private prototype_ `virtual bool HandleDoubleClickInternal() override;`
- L35 _private prototype_ `TSharedPtr<SEventTimelineView::FTimelineEventData> GetEventData() const;`
- L37 _private member_ `mutable TSharedPtr<SEventTimelineView::FTimelineEventData> EventData;`
- L38 _private member_ `mutable int EventUpdateRequested = 0;`
- L40 _private member_ `uint64 ObjectId;`
- L41 _private member_ `uint32 FieldNotifyId;`
- L42 _private member_ `FFieldNotificationId FieldNotify;`
- L43 _private member_ `FSlateIcon Icon;`
- L44 _private member_ `FText TrackName;`

#### class `UE::FieldNotification::FObjectTrack`  
`class FObjectTrack : public RewindDebugger::FRewindDebuggerTrack`  
_L48-66_
- inherits: `RewindDebugger::FRewindDebuggerTrack`
- L51 _public prototype_ `FObjectTrack(uint64 InObjectId);`
- L53 _private prototype_ `virtual bool UpdateInternal() override;`
- L54 _private prototype_ `virtual TSharedPtr<SWidget> GetDetailsViewInternal() override;`
- L56 _private prototype_ `virtual FSlateIcon GetIconInternal() override;`
- L57 _private prototype_ `virtual FName GetNameInternal() const override;`
- L58 _private prototype_ `virtual FText GetDisplayNameInternal() const override;`
- L59 _private prototype_ `virtual uint64 GetObjectIdInternal() const override;`
- L60 _private prototype_ `virtual TConstArrayView<TSharedPtr<FRewindDebuggerTrack>> GetChildrenInternal(TArray<TSharedPtr<FRewindDebuggerTrack>>& OutTracks) const override;`
- L62 _private member_ `FSlateIcon Icon;`
- L63 _private member_ `uint64 ObjectId;`
- L65 _private member_ `TArray<TSharedPtr<FFieldNotifyTrack>> Children;`

#### class `UE::FieldNotification::FTracksCreator`  
`class FTracksCreator : public RewindDebugger::IRewindDebuggerTrackCreator`  
_L70-78_
- inherits: `RewindDebugger::IRewindDebuggerTrackCreator`
- L73 _private prototype_ `virtual FName GetTargetTypeNameInternal() const;`
- L74 _private prototype_ `virtual FName GetNameInternal() const override;`
- L75 _private prototype_ `virtual void GetTrackTypesInternal(TArray<RewindDebugger::FRewindDebuggerTrackType>& Types) const override;`
- L76 _private prototype_ `virtual TSharedPtr<RewindDebugger::FRewindDebuggerTrack> CreateTrackInternal(const RewindDebugger::FObjectId& InObjectId) const override;`
- L77 _private prototype_ `virtual bool HasDebugInfoInternal(const RewindDebugger::FObjectId& InObjectId) const override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace FieldNotification` (scope `UE`)
