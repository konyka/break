# Runtime / AutomationWorker

- module root: `Source/Runtime/AutomationWorker`
- headers: 5; symbols: 116
- symbol kinds: class=3, delegate=2, enum=2, enumerator=24, function=3, member=31, namespace=2, prototype=48, struct=1
- PrivateDependencyModuleNames: Analytics, AnalyticsET, AutomationMessages, AutomationTest, CoreUObject, Engine, Json, JsonUtilities, RHI
- PrivateIncludePathModuleNames: MessagingCommon
- PublicDependencyModuleNames: Core

### `Source/Runtime/AutomationWorker/Private/AutomationAnalyticParams.h` (Private)


#### enum `EAutomationEventName::Type`  
`enum Type`  
_L8-14_
- L10 _public enumerator_ `FPSCapture`
- L11 _public enumerator_ `AutomationTestResults`
- L13 _public enumerator_ `NUM_ENGINE_EVENT_NAMES`

#### enum `EAutomationAnalyticParam::Type`  
`enum Type`  
_L20-45_
- L22 _public enumerator_ `MapName`
- L23 _public enumerator_ `TimeStamp`
- L24 _public enumerator_ `Platform`
- L25 _public enumerator_ `Spec`
- L26 _public enumerator_ `CL`
- L27 _public enumerator_ `FPS`
- L28 _public enumerator_ `BuildConfiguration`
- L29 _public enumerator_ `AverageFrameTime`
- L30 _public enumerator_ `AverageGameThreadTime`
- L31 _public enumerator_ `AverageRenderThreadTime`
- L32 _public enumerator_ `AverageGPUTime`
- L33 _public enumerator_ `PercentOfFramesAtLeast30FPS`
- L34 _public enumerator_ `PercentOfFramesAtLeast60FPS`
- L36 _public enumerator_ `TestName`
- L37 _public enumerator_ `BeautifiedName`
- L38 _public enumerator_ `ExecutionCount`
- L39 _public enumerator_ `IsSuccess`
- L40 _public enumerator_ `Duration`
- L41 _public enumerator_ `ErrorCount`
- L42 _public enumerator_ `WarningCount`
- L44 _public enumerator_ `NUM_ENGINE_PARAMS`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace EAutomationEventName`
- L18 _namespace_ `namespace EAutomationAnalyticParam`

### `Source/Runtime/AutomationWorker/Private/AutomationAnalytics.h` (Private)


#### class `FAutomationAnalytics`  
`class FAutomationAnalytics : FNoncopyable`  
_L21-78_
- inherits: `FNoncopyable`
- L31 _public prototype_ `static IAnalyticsProvider& GetProvider();` — Return the provider instance. Not valid outside of Initialize/Shutdown calls. Note: must check IsAvailable() first else this code will assert if the provider is not valid.
- L34 _public prototype_ `static void Initialize();` — Called to initialize the singleton.
- L37 _public prototype_ `static bool IsAvailable();` — Helper function to determine if the provider is valid.
- L40 _public prototype_ `static void Shutdown();` — Called to shut down the singleton
- L45 _public prototype_ `static FString GetAutomationEventName(EAutomationEventName::Type InEventName);` — Helper function to retrieve the parameter name from a given enum
- L46 _public prototype_ `static FString GetAutomationParamName(EAutomationAnalyticParam::Type InEngineParam);`
- L48 _public prototype_ `static void InititalizeAnalyticParameterNames();`
- L51 _public prototype_ `static bool IsInitialized();` — Helper to check if the Analytics provider is Initialized
- L60 _public prototype_ `static void FireEvent_FPSCapture(const FAutomationPerformanceSnapshot& PerfSnapshot);` — FPSCapture Event
- L63 _public prototype_ `static void FireEvent_AutomationTestResults(const FAutomationWorkerRunTestsReply* TestResults, const FString& BeautifiedTestName);` — AutomationTest Event
- L67 _private prototype_ `static void SetInitialParameters(TArray<FAnalyticsEventAttribute>& ParamArray);`
- L70 _private member_ `static TArray<FString> AutomationEventNames;` — Array of Analytic Parameter names
- L71 _private member_ `static TArray<FString> AutomationParamNames;`
- L72 _private member_ `static FString MachineSpec;`
- L74 _private member_ `static bool bIsInitialized;`
- L77 _private member_ `static TSharedPtr<IAnalyticsProviderET> Analytics;` — This allows us to "opt-out" of engine automation analytics. We still create a session, but we don't send any automation events.

### `Source/Runtime/AutomationWorker/Private/AutomationWorkerModule.h` (Private)


#### class `FAutomationWorkerModule`  
`class FAutomationWorkerModule : public IAutomationWorkerModule`  
_L32-203_
- inherits: `IAutomationWorkerModule`
- desc: Implements the Automation Worker module.
- L39 _public prototype_ `virtual void StartupModule() override;`
- L40 _public prototype_ `virtual void ShutdownModule() override;`
- L41 _public prototype_ `virtual bool SupportsDynamicReloading() override;`
- L47 _public prototype_ `virtual void Tick() override;`
- L52 _protected prototype_ `bool ExecuteLatentCommands();` — Execute all latent commands and when complete send results message back to the automation controller.
- L55 _protected prototype_ `bool ExecuteNetworkCommands();` — Execute all network commands and when complete send results message back to the automation controller.
- L58 _protected prototype_ `void Initialize();` — Initializes the automation worker.
- L61 _protected prototype_ `void ReportNetworkCommandComplete();` — Network phase is complete (if there were any network commands).  Send ping back to the controller.
- L64 _protected prototype_ `void ReportTestComplete();` — Test is complete. Send results back to controller.
- L71 _protected prototype_ `void SendTests(const FMessageAddress& ControllerAddress);` — Send a list of all the tests supported by the worker @param ControllerAddress The message address of the controller that requested the tests.
- L80 _protected prototype_ `void SendMessage(FAutomationWorkerMessageBase* Message, UScriptStruct* TypeInfo, const FMessageAddress& ControllerAddress);` — Send a message in an unified way with passing correct Instance Id into the message we are going to send. @param Message The message to be sent. @param TypeInfo The type information about the message to be sent. @param ControllerAddress The message address of the receiver.
- L85 _private prototype_ `void HandleFindWorkersMessage(const FAutomationWorkerFindWorkers& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Handles FAutomationWorkerFindWorkers messages.
- L88 _private prototype_ `void SendWorkerFound(const FMessageAddress& ControllerAddress);` — Deferred handler for sending "find worker" response in case the asset registry isn't loaded yet.
- L91 _private prototype_ `void HandleMessageEndpointShutdown();` — Handles message endpoint shutdowns.
- L94 _private prototype_ `void HandleNextNetworkCommandReplyMessage(const FAutomationWorkerNextNetworkCommandReply& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Handles FAutomationWorkerNextNetworkCommandReply messages.
- L97 _private prototype_ `void HandlePingMessage(const FAutomationWorkerPing& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Handles FAutomationWorkerPing messages.
- L100 _private prototype_ `void HandleStartTestSession(const FAutomationWorkerStartTestSession& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Handles FAutomationWorkerStartTestSession messages.
- L103 _private prototype_ `void HandleStopTestSession(const FAutomationWorkerStopTestSession& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Handles FAutomationWorkerStopTestSession messages.
- L106 _private prototype_ `void HandleRequestTestsMessage(const FAutomationWorkerRequestTests& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Handles FAutomationWorkerRequestTests messages.
- L109 _private prototype_ `void HandleRunTestsMessage(const FAutomationWorkerRunTests& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Handles FAutomationWorkerRunTests messages.
- L112 _private prototype_ `void HandleStopTestsMessage(const struct FAutomationWorkerStopTests& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Handles FAutomationWorkerStopTests messages.
- L115 _private prototype_ `void HandleScreenShotCompared(const FAutomationWorkerImageComparisonResults& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Handles FAutomationWorkerImageComparisonResults messages.
- L118 _private prototype_ `void HandleTestDataRetrieved(const FAutomationWorkerTestDataResponse& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Handles FAutomationWorkerTestDataResponse messages.
- L121 _private prototype_ `void HandlePerformanceDataRetrieved(const FAutomationWorkerPerformanceDataResponse& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Handles FAutomationWorkerPerformanceDataResponse messages.
- L124 _private prototype_ `void HandleTelemetryData(const FString& StorageName, const FString& InTestName, const TArray<FAutomationTelemetryData>& InItems);` — Dispatches telemetry data to data collector
- L127 _private prototype_ `void HandlePreTestingEvent();` — Handles FAutomationTestFramework PreTestingEvents.
- L130 _private prototype_ `void HandlePostTestingEvent();` — Handles FAutomationTestFramework PostTestingEvents.
- L134 _private prototype_ `void HandleScreenShotCapturedWithName(const TArray<FColor>& RawImageData, const FAutomationScreenshotData& Data);` — Invoked when we have screen shot to send.
- L137 _private prototype_ `void HandleScreenShotAndTraceCapturedWithName(const TArray<FColor>& RawImageData, const TArray<uint8>& CapturedFrameTrace, const FAutomationScreenshotData& Data);` — Invoked when we have screen shot and frame trace to send.
- L140 _private prototype_ `void HandleScreenShotComparisonReport(const FAutomationScreenshotCompareResults& Results);` — Invoked when we have a screenshot comparison result to send.
- L144 _private prototype_ `void SendAnalyticsEvents(TArray<FString>& InAnalyticsItems);` — Dispatches analytics events to the data collector.
- L147 _private prototype_ `void RecordPerformanceAnalytics(const FAutomationPerformanceSnapshot& PerfSnapshot);` — Helper for Performance Capture Analytics.
- L150 _private prototype_ `bool IsTestExcluded(const FString& InTestToRun, FString* OutReason, bool* OutWarn) const;` — Checks whether the test is in exclusion list.
- L153 _private prototype_ `void TriggerSectionNotifications();` — Trigger Notifications when entering and leaving section
- L158 _private member_ `TArray<FAutomationTestInfo> TestInfo;` — The collection of test data we are to send to a controller.
- L163 _private member_ `TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> MessageEndpoint;` — Holds the messaging endpoint.
- L166 _private member_ `FMessageAddress TestRequesterAddress;` — Message address of the controller sending the test request.
- L169 _private member_ `uint32 ExecutionCount;` — Identifier for the controller to know if the results should be discarded or not.
- L172 _private member_ `FString TestName;` — Execute one of the tests by request of the controller.
- L175 _private member_ `FString BeautifiedTestName;` — Beautified name of the test
- L178 _private member_ `FString FullTestPath;` — Full path of the test
- L181 _private member_ `bool bSendAnalytics;` — Whether to send analytics events to the backend - sent from controller
- L184 _private member_ `bool bPruneLogsOnSuccess;` — Whether to prune log events from test report on success
- L187 _private member_ `bool bExecuteNextNetworkCommand;` — Whether the controller has requested that the network command should execute
- L190 _private member_ `bool bExecutingNetworkCommandResults;` — Whether we are processing sub-commands of a network command
- L193 _private member_ `FStopTestEvent StopTestEvent;` — Delegate to fire when the test is complete
- L196 _private member_ `FString DeviceTag;` — Tag for the device on which the worker is running
- L199 _private member_ `FString ActiveSection;` — Tracking of active section
- L202 _private member_ `FGuid ActiveScreenshotComparisonId;` — Tracking of the active screenshot comparison ID

### `Source/Runtime/AutomationWorker/Private/AutomationWorkerPrivate.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAutomationAnalytics, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAutomationAnalytics, Log, All);`

### `Source/Runtime/AutomationWorker/Public/IAutomationWorkerModule.h` (Public)


#### struct `FAutomationPerformanceSnapshot`  
`struct FAutomationPerformanceSnapshot`  
_L12-64_
- desc: Wraps up useful performance capture data for automation tests.  These are usually triggered at specific intervals along a timeline inside an automation-specific cinematic asset.
- L14 _public member_ `FString Changelist;`
- L15 _public member_ `FString BuildConfiguration;`
- L16 _public member_ `FString MapName;`
- L17 _public member_ `FString SequenceName;`
- L18 _public member_ `FString AverageFPS;`
- L19 _public member_ `FString AverageFrameTime;`
- L20 _public member_ `FString AverageGameThreadTime;`
- L21 _public member_ `FString AverageRenderThreadTime;`
- L22 _public member_ `FString AverageGPUTime;`
- L23 _public member_ `FString PercentOfFramesAtLeast30FPS;`
- L24 _public member_ `FString PercentOfFramesAtLeast60FPS;`
- L28 _public function_ `FString ToCommaDelimetedString() const` — @return	Serializes this structure into a simple comma-delimited string
- L45 _public function_ `void FromCommaDelimitedString( const FString& CommaDelimitedString )` — Deserializes from a comma-delimited string created with MakeCommaDeliminedString

#### class `IAutomationWorkerModule`  
`class IAutomationWorkerModule : public IModuleInterface`  
_L70-93_
- inherits: `IModuleInterface`
- desc: Interface for AutomationWorker modules.
- L75 _public prototype_ `DECLARE_DELEGATE_ThreeParams(FStopTestEvent, bool, FString, class FAutomationTestExecutionInfo const &);` — Called whenever a test is stopped
- L80 _public prototype_ `virtual void Tick( ) = 0;` — Ticks the automation worker module.
- L92 _protected function_ `IAutomationWorkerModule()`

#### Free symbols / members of external scopes

- L75 _delegate_ `DECLARE_DELEGATE_ThreeParams(FStopTestEvent, bool, FString, class FAutomationTestExecutionInfo const &);` — Called whenever a test is stopped
