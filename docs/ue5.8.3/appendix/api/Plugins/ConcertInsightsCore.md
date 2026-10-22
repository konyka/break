# Plugins / ConcertInsightsCore

- module root: `Plugins/Developer/Concert/ConcertInsights/ConcertInsightsCore/Source/ConcertInsightsCore`
- headers: 4; symbols: 73
- symbol kinds: class=3, delegate=2, enum=2, enumerator=5, function=13, member=15, namespace=8, prototype=18, struct=7
- PrivateDependencyModuleNames: Concert, ConcertTransport, CoreUObject, Slate, SlateCore, TraceLog
- PublicDependencyModuleNames: Core

### `Plugins/Developer/Concert/ConcertInsights/ConcertInsightsCore/Source/ConcertInsightsCore/Private/ConcertInsightsSynchronizedTrace.h` (Private)


#### class `UE::ConcertInsightsSyncTrace::FConcertInsightsSyncTraceModule`  
`class FConcertInsightsSyncTraceModule : public IConcertInsightsSyncTraceModule`  
_L9-17_
- inherits: `IConcertInsightsSyncTraceModule`
- L14 _public prototype_ `virtual void StartupModule() override;`
- L15 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ConcertInsightsSyncTrace` (scope `UE`)

### `Plugins/Developer/Concert/ConcertInsights/ConcertInsightsCore/Source/ConcertInsightsCore/Public/IConcertInsightsSyncTraceModule.h` (Public)


#### class `UE::ConcertInsightsSyncTrace::IConcertInsightsSyncTraceModule`  
`class IConcertInsightsSyncTraceModule : public IModuleInterface`  
_L19-45_
- inherits: `IModuleInterface`
- desc: This module provides the base code for starting synchronized tracing across multiple machines. Synchronized tracing means that certain machines in the session are requested to start tracing at the same time. Each machine will generate a separate .utrace file. When any of these files are analyzed in Unreal Insights, ConcertInsights collects the other relevant files and aggregates them in the UI. This module houses the shared code needed to synchronize events across multiple machines, for example the Concert events that are sent to the other machines. ConcertInsightsServer and ConcertInsightsEditor depend on this module's exposed events.
- L29 _public function_ `static inline IConcertInsightsSyncTraceModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L40 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() during shutdown if IsAvailable() returns true. @return True if the module is loaded and ready to use

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ConcertInsightsSyncTrace` (scope `UE`)

### `Plugins/Developer/Concert/ConcertInsights/ConcertInsightsCore/Source/ConcertInsightsCore/Public/TraceControls.h` (Public)


#### struct `UE::ConcertInsightsCore::FStartTraceArgs`  
`struct FStartTraceArgs : FConcertTrace_StartTraceArgs`  
_L14-18_
- inherits: `FConcertTrace_StartTraceArgs`
- L16 _public member_ `FTraceAuxiliary::FOptions* Options = nullptr;`
- L17 _public member_ `const FTraceAuxiliary::FLogCategoryAlias& LogCategory = LogCore;`

#### struct `UE::ConcertInsightsCore::FInitArgs`  
`struct FInitArgs`  
_L20-25_
- L22 _public member_ `TOptional<FGuid> EndpointId;`
- L23 _public member_ `FString DisplayString;`
- L24 _public member_ `bool bIsServer;`

#### class `UE::ConcertInsightsCore::FTraceControls`  
`class FTraceControls : public FNoncopyable`  
_L33-127_
- inherits: `FNoncopyable`
- desc: Manages synchronized traces. This listens for remote requests for starting traces. Intended to be subclassed.
- L38 _public function_ `template<typename TControls, typename... TArgs> static TUniquePtr<TControls> Make(TArgs&&... Arg)`
- L49 _public prototype_ `virtual ~FTraceControls();`
- L52 _public prototype_ `bool IsTracing() const;` — Whether a trace is currently occuring
- L55 _public prototype_ `bool StartSynchronizedTrace(TSharedRef<IConcertSession> Session, const FStartTraceArgs& Args, FText* FailReason = nullptr);` — Starts a synchronized trace across multiple endpoints.
- L56 _public function_ `bool StartSynchronizedTrace(TSharedRef<IConcertSession> Session, FText* FailReason = nullptr)`
- L59 _public prototype_ `void StopSynchronizedTrace();` — Stops a synchronized trace if one is ongoing.
- L62 _public function_ `virtual FStartTraceArgs GetDefaultSynchronizedTraceArgs() const` — Gets the default trace arguments to use
- L64 _public function_ `bool IsInSynchronizedTrace() const`
- L66 _public prototype_ `DECLARE_EVENT(FTraceControls, FOnSynchronizedTraceStarted);`
- L68 _public function_ `FOnSynchronizedTraceStarted& OnSynchronizedTraceStarted()` — Broadcasts when a synchronized trace is started for any reason, such as the local machine starting it or a remote request being accepted.
- L70 _public prototype_ `DECLARE_EVENT(FTraceControls, FOnSynchronizedTraceStopped);`
- L72 _public function_ `FOnSynchronizedTraceStopped& OnSynchronizedTraceStopped()` — Broadcasts when a synchronized trace is stopped for any reason, such as the local machine stopping it or being told so by a remote request.
- L76 _protected prototype_ `FTraceControls();`
- L79 _protected prototype_ `void RegisterTraceRequestsHandler(const TSharedRef<IConcertSession>& Session);` — Registers handlers for trace requests.
- L82 _protected prototype_ `void OnLeaveSession(IConcertSession& Session);` — Called by subclasses to notify that the local application has left the session.
- L85 _protected function_ `virtual bool CanSendRequestsToEndpoint(const FGuid& EndpointId, const IConcertSession& Session) const` — @return Allows subclass to decide whether a trace start request should be sent to this endpoint.
- L87 _protected function_ `virtual void OnSynchronizedTraceAccepted(const FConcertSessionContext& Context, const FConcertTrace_StartSyncTrace_Request& Request, const TSharedRef<IConcertSession>& Session)` — Called when an incoming synchronized trace was accepted.
- L90 _protected prototype_ `virtual FInitArgs GetInitEventArgs() const = 0;` — Checks whether joining a trace is ok and if so, return the data to put into the ConcertInsights init event.
- L101 _private member_ `TSet<TWeakPtr<IConcertSession>> RegisteredSessions;` — Sessions these controls are listening for requests on.
- L104 _private member_ `TOptional<FSynchronizedSessionData> InProgressSynchronizedTrace;` — Data for the currently running synchronized trace. Unset if not running.
- L106 _private member_ `FOnSynchronizedTraceStarted OnSynchronizedTraceStartedDelegate;`
- L107 _private member_ `FOnSynchronizedTraceStopped OnSynchronizedTraceStoppedDelegate;`
- L110 _private prototype_ `EConcertSessionResponseCode HandleTraceStartRequest(const FConcertSessionContext& Context, const FConcertTrace_StartSyncTrace_Request& Request, FConcertTrace_StartSyncTrace_Response& Response, const TSharedRef<IConcertSession>& Session);` — Handles networked requests from other endpoints to start tracing.
- L112 _private function_ `void HandleTraceStopRequest(const FConcertSessionContext&, const FConcertTrace_StopSyncTrace&)` — Handles networked requests from other endpoints to stop tracing.
- L115 _private function_ `void OnTraceStarted(FTraceAuxiliary::EConnectionType, const FString&)` — Local callback for when tracing begins
- L116 _private prototype_ `void OnTraceStopped(FTraceAuxiliary::EConnectionType, const FString&);`
- L119 _private prototype_ `bool StartLocalConcertTrace(const FStartTraceArgs& Args);` — Starts tracing (if not already), enables the Concert trace channel, and ensures everything for ConcertInsights is set up (init event is sent).
- L121 _private prototype_ `void StopLocalConcertTrace();` — Stops tracing locally
- L124 _private prototype_ `void SendInitEventIfNeeded();` — Sends the init event if we're tracing, the Concert channel is enabled, and the init event has not yet been sent during this session.
- L126 _private prototype_ `bool LocallyStartSynchronizedTrace(FSynchronizedSessionData Data, const FStartTraceArgs& Args);`

#### struct `UE::ConcertInsightsCore::FTraceControls::FSynchronizedSessionData`  
`struct FSynchronizedSessionData`  
_L94-98_
- L97 _public member_ `TWeakPtr<IConcertSession> TraceInitiator;` — The session that the synchronized trace was started on.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ConcertInsightsCore` (scope `UE`)
- L66 _delegate_ `DECLARE_EVENT(FTraceControls, FOnSynchronizedTraceStarted);`
- L70 _delegate_ `DECLARE_EVENT(FTraceControls, FOnSynchronizedTraceStopped);`

### `Plugins/Developer/Concert/ConcertInsights/ConcertInsightsCore/Source/ConcertInsightsCore/Public/TraceMessages.h` (Public)


#### enum `EConcertTraceTargetType`  
`enum class EConcertTraceTargetType : uint8`  
_L10-19_
- reflection: `UENUM()`
- desc: See /ref FTraceAuxiliary::EConnectionType for more info.
- L13 _public enumerator_ `Network` — Connect to a trace server. Target is IP address or hostname.
- L18 _public enumerator_ `File` — Write to a file. Target string is filename. Absolute or relative current working directory. If target is null the current date and time is used.

#### struct `FConcertTrace_StartTraceArgs`  
`struct FConcertTrace_StartTraceArgs`  
_L32-47_
- reflection: `USTRUCT()`
- desc: Arguments to pass to FTraceAuxiliary::Start
- L38 _public member_ `EConcertTraceTargetType ConnectionType = EConcertTraceTargetType::Network;` — `UPROPERTY()` — How target is supposed to be interpreted.
- L42 _public member_ `FString Target = TEXT("loc` — `UPROPERTY()` — String to use for connection. See /ref EConcertTraceTargetType for details
- L46 _public member_ `FString Channels = TEXT("def` — `UPROPERTY()` — Channels to use. Comma separated.

#### struct `FConcertTrace_StartSyncTrace_Request`  
`struct FConcertTrace_StartSyncTrace_Request`  
_L55-62_
- reflection: `USTRUCT()`
- desc: A request for the receive to: - start tracing, - ensure the .utrace contains a CONCERT_TRACE_INIT event
- L61 _public member_ `FConcertTrace_StartTraceArgs TraceArgs;` — `UPROPERTY()` — Info about how the trace is supposed to be started.

#### enum `EConcertTraceErrorCode`  
`enum class EConcertTraceErrorCode : uint8`  
_L65-70_
- reflection: `UENUM()`
- L67 _public enumerator_ `Timeout`
- L68 _public enumerator_ `Joined`
- L69 _public enumerator_ `Rejected`

#### struct `FConcertTrace_StartSyncTrace_Response`  
`struct FConcertTrace_StartSyncTrace_Response`  
_L73-79_
- reflection: `USTRUCT()`
- L78 _public member_ `EConcertTraceErrorCode ErrorCode = EConcertTraceErrorCode::Timeout;` — `UPROPERTY()`

#### struct `FConcertTrace_StopSyncTrace`  
`struct FConcertTrace_StopSyncTrace`  
_L82-85_
- reflection: `USTRUCT()`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace ConcertInsightsSync` (scope `UE`)
- L23 _function_ `FORCEINLINE FTraceAuxiliary::EConnectionType ConvertTraceTargetType(EConcertTraceTargetType ConnectionType)` (scope `UE::ConcertInsightsSync`)
