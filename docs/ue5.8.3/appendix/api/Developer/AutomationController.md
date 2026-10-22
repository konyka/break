# Developer / AutomationController

- module root: `Source/Developer/AutomationController`
- headers: 12; symbols: 650
- symbol kinds: class=14, delegate=9, enum=5, enumerator=28, function=95, macro=1, member=168, namespace=4, prototype=305, struct=13, typedef=5, variable=3
- PrivateDependencyModuleNames: AssetRegistry, AutomationMessages, EditorFramework, Engine, HTTP, Json, JsonUtilities, MessageLog, ScreenShotComparisonTools, UnrealEd, UnrealEdMessages
- PrivateIncludePathModuleNames: MessagingCommon
- PublicDependencyModuleNames: AutomationTest, Core, CoreUObject

### `Source/Developer/AutomationController/Private/AutomationControllerManager.h` (Private)


#### struct `FAutomatedTestResult`  
`struct FAutomatedTestResult`  
_L25-110_
- reflection: `USTRUCT()`
- L30 _public member_ `TSharedPtr<IAutomationReport> Test;`
- L33 _public member_ `FString TestDisplayName;` — `UPROPERTY()`
- L36 _public member_ `FString FullTestPath;` — `UPROPERTY()`
- L39 _public member_ `TArray<FString> Tags;` — `UPROPERTY()`
- L42 _public member_ `EAutomationState State;` — `UPROPERTY()`
- L45 _public member_ `TArray<FString> DeviceInstance;` — `UPROPERTY()`
- L48 _public member_ `float Duration;` — `UPROPERTY()`
- L51 _public member_ `FDateTime DateTime;` — `UPROPERTY()`
- L53 _public function_ `FAutomatedTestResult()`
- L62 _public function_ `void SetEvents(const TArray<FAutomationExecutionEntry>& InEntries, int32 InWarnings, int32 InErrors)`
- L69 _public function_ `void AddEvent(EAutomationEventType EvenType, const FString& InMessage)`
- L86 _public function_ `void SetArtifacts(const TArray<FAutomationArtifact>& InArtifacts)`
- L91 _public function_ `int32 GetWarningTotal() const`
- L92 _public function_ `int32 GetErrorTotal() const`
- L94 _public function_ `const TArray<FAutomationExecutionEntry>& GetEntries() const`
- L95 _public function_ `TArray<FAutomationArtifact>& GetArtifacts()`
- L100 _private member_ `TArray<FAutomationExecutionEntry> Entries;` — `UPROPERTY()`
- L103 _private member_ `int32 Warnings;` — `UPROPERTY()`
- L106 _private member_ `int32 Errors;` — `UPROPERTY()`
- L109 _private member_ `TArray<FAutomationArtifact> Artifacts;` — `UPROPERTY()`

#### struct `FAutomatedTestPassResults`  
`struct FAutomatedTestPassResults`  
_L113-196_
- reflection: `USTRUCT()`
- L118 _public function_ `FAutomatedTestPassResults() : ReportCreatedOn(0) , Succeeded(0) , SucceededWithWarnings(0) , Failed(0) , NotRun(0) , InProcess(0) , TotalDuration(0) , ComparisonExported(false) , IsRequired(false)`
- L132 _public member_ `TArray<FAutomationDeviceInfo> Devices;` — `UPROPERTY()`
- L135 _public member_ `FDateTime ReportCreatedOn;` — `UPROPERTY()`
- L138 _public member_ `int32 Succeeded;` — `UPROPERTY()`
- L141 _public member_ `int32 SucceededWithWarnings;` — `UPROPERTY()`
- L144 _public member_ `int32 Failed;` — `UPROPERTY()`
- L147 _public member_ `int32 NotRun;` — `UPROPERTY()`
- L150 _public member_ `int32 InProcess;` — `UPROPERTY()`
- L153 _public member_ `float TotalDuration;` — `UPROPERTY()`
- L156 _public member_ `bool ComparisonExported;` — `UPROPERTY()`
- L159 _public member_ `FString ComparisonExportDirectory;` — `UPROPERTY()`
- L162 _public member_ `TArray<FAutomatedTestResult> Tests;` — `UPROPERTY()`
- L164 _public member_ `TMap<FString, uint32> TestsMapIndex;`
- L166 _public member_ `bool IsRequired;`
- L168 _public function_ `int32 GetTotalTests() const`
- L173 _public prototype_ `void AddTestResult(const IAutomationReportPtr& TestReport);`
- L175 _public prototype_ `FAutomatedTestResult& GetTestResult(const IAutomationReportPtr& TestReport);`
- L177 _public prototype_ `void ReBuildTestsMapIndex();`
- L179 _public prototype_ `bool ReflectResultStateToReport(IAutomationReportPtr& TestReport);`
- L181 _public prototype_ `void UpdateTestResultStatus(const IAutomationReportPtr& TestReport, EAutomationState State, bool bHasWarning = false);`
- L183 _public function_ `void ClearAllEntries()`

#### class `FAutomationControllerManager`  
`class FAutomationControllerManager : public IAutomationControllerManager`  
_L202-704_
- inherits: `IAutomationControllerManager`
- desc: Implements the AutomationController module.
- L205 _public prototype_ `FAutomationControllerManager();`
- L208 _public prototype_ `virtual void RequestAvailableWorkers( const FGuid& InSessionId ) override;` — IAutomationController Interface
- L209 _public prototype_ `virtual bool IsReadyForTests() override;`
- L210 _public prototype_ `virtual void RequestTests() override;`
- L211 _public prototype_ `virtual void RunTests( const bool bIsLocalSession) override;`
- L212 _public prototype_ `virtual void StopTests() override;`
- L213 _public prototype_ `virtual void Init() override;`
- L214 _public prototype_ `virtual void RequestLoadAsset( const FString& InAssetName ) override;`
- L215 _public prototype_ `virtual void Tick() override;`
- L217 _public function_ `virtual void SetNumPasses(const int32 InNumPasses) override`
- L222 _public function_ `virtual int32 GetNumPasses() override`
- L227 _public function_ `virtual bool IsSendAnalytics() const override`
- L232 _public function_ `virtual void SetSendAnalytics(const bool bNewValue) override`
- L237 _public function_ `virtual bool KeepPIEOpen() const override`
- L242 _public function_ `virtual void SetKeepPIEOpen(const bool bNewValue) override`
- L247 _public function_ `virtual void SetFilter( TSharedPtr< AutomationFilterCollection > InFilter ) override`
- L252 _public function_ `virtual TArray <TSharedPtr <IAutomationReport> >& GetFilteredReports() override`
- L257 _public function_ `virtual TArray <TSharedPtr <IAutomationReport> > GetEnabledReports() override`
- L262 _public function_ `virtual int32 GetNumDeviceClusters() const override`
- L267 _public function_ `virtual int32 GetNumDevicesInCluster(const int32 ClusterIndex) const override`
- L272 _public function_ `virtual FString GetClusterGroupName(const int32 ClusterIndex) const override`
- L277 _public function_ `virtual FString GetDeviceTypeName(const int32 ClusterIndex) const override`
- L282 _public function_ `virtual FString GetDeviceName(const int32 ClusterIndex, const int32 DeviceIndex) const override`
- L287 _public function_ `virtual FGuid GetGameInstanceId(const int32 ClusterIndex, const int32 DeviceIndex) const override`
- L292 _public function_ `virtual FString GetGameInstanceName(const int32 ClusterIndex, const int32 DeviceIndex) const override`
- L297 _public function_ `virtual void SetVisibleTestsEnabled(const bool bEnabled) override`
- L302 _public function_ `virtual int32 GetEnabledTestsNum() const override`
- L307 _public function_ `virtual void GetEnabledTestNames(TArray<FString>& OutEnabledTestNames) const override`
- L312 _public function_ `virtual void GetFilteredTestNames(TArray<FString>& OutFilteredTestNames) const override`
- L317 _public function_ `virtual void SetEnabledTests(const TArray<FString>& EnabledTests) override`
- L322 _public function_ `virtual EAutomationControllerModuleState::Type GetTestState( ) const override`
- L327 _public function_ `virtual void SetDeveloperDirectoryIncluded(const bool bInDeveloperDirectoryIncluded) override`
- L332 _public function_ `virtual bool IsDeveloperDirectoryIncluded(void) const override`
- L337 _public function_ `virtual void SetRequestedTestFlags(const EAutomationTestFlags InRequestedTestFlags) override`
- L343 _public function_ `virtual const bool CheckTestResultsAvailable() const override`
- L348 _public function_ `virtual const bool ReportsHaveErrors() const override`
- L353 _public function_ `virtual const bool ReportsHaveWarnings() const override`
- L358 _public function_ `virtual const bool ReportsHaveLogs() const override`
- L363 _public function_ `virtual void ClearAutomationReports() override`
- L368 _public prototype_ `virtual const bool ExportReport(uint32 FileExportTypeMask) override;`
- L369 _public prototype_ `virtual bool IsTestRunnable( IAutomationReportPtr InReport ) const override;`
- L370 _public prototype_ `virtual void RemoveCallbacks() override;`
- L371 _public prototype_ `virtual void Shutdown() override;`
- L372 _public prototype_ `virtual void Startup() override;`
- L374 _public function_ `virtual FOnAutomationControllerManagerShutdown& OnShutdown( ) override`
- L379 _public function_ `virtual FOnAutomationControllerManagerTestsAvailable& OnTestsAvailable( ) override`
- L384 _public function_ `virtual FOnAutomationControllerTestsRefreshed& OnTestsRefreshed( ) override`
- L389 _public function_ `virtual FOnAutomationControllerTestsComplete& OnTestsComplete() override`
- L394 _public function_ `virtual FOnAutomationControllerReset& OnControllerReset() override`
- L400 _public prototype_ `virtual bool IsDeviceGroupFlagSet( EAutomationDeviceGroupTypes::Type InDeviceGroup ) const override;`
- L401 _public prototype_ `virtual void ToggleDeviceGroupFlag( EAutomationDeviceGroupTypes::Type InDeviceGroup ) override;`
- L402 _public prototype_ `virtual void UpdateDeviceGroups() override;`
- L404 _public prototype_ `virtual FString GetReportOutputPath() const override;`
- L406 _public prototype_ `virtual void ResetAutomationTestTimeout(const TCHAR* Reason) override;`
- L415 _protected prototype_ `void AddPingResult(const FGuid& ResponderInstanceId);` — Adds a ping result from a running test. @param ResponderInstanceId The worker instance identifier that responded to a ping.
- L420 _protected prototype_ `void ReportTestResults();` — Spew all of our results of the test out to the log.
- L425 _protected prototype_ `bool GenerateJsonTestPassSummary(FAutomatedTestPassResults& SerializedPassResults, FString& OutTestReportJson);` — Generates a serialized json string that contains all of our test report data
- L430 _protected prototype_ `bool SaveJsonTestPassSummary(const FString& TestReportJson);` — Create a json file that contains all of our test report data at /saved/automation/logs/AutomationReport-{CL}-{DateTime}.json
- L435 _protected prototype_ `void BroadcastJsonTestPassSummary(const FString& TestReportJson);` — Braodcasts a serialized json string that contains all of our test report data
- L440 _protected prototype_ `bool GenerateTestPassHtmlIndex();` — Generates a full html report of the testing, which may include links to images.  All of it will be bundled under a folder.
- L445 _protected prototype_ `bool LoadJsonTestPassSummary(FString& ReportFilePath, TArray<IAutomationReportPtr> TestReports);` — Load test results from previous json test pass summary file and reflect results on reports
- L453 _protected prototype_ `void CollectTestResults(TSharedPtr<IAutomationReport> Report, const FAutomationTestResults& Results);` — Gather all info, warning, and error lines generated over the course of a test. @param TestName The test that was just run. @param TestResult All of the messages of note generated during the test case.
- L460 _protected prototype_ `void CheckChildResult( TSharedPtr< IAutomationReport > InReport );` — Checks the child result. @param InReport The child result to check.
- L462 _protected prototype_ `FString SlugString(const FString& DisplayString) const;`
- L464 _protected prototype_ `FString CopyArtifact(const FString& DestFolder, const FString& SourceFile) const;`
- L472 _protected prototype_ `void ExecuteNextTask( int32 ClusterIndex, OUT bool& bAllTestsCompleted );` — Execute the next task thats available. @param ClusterIndex The Cluster index of the device type we intend to use. @param bAllTestsCompleted Whether all tests have been completed.
- L475 _protected prototype_ `void ReportImageComparisonResult(const FAutomationWorkerImageComparisonResults& Result);` — Report an image comparison result
- L478 _protected prototype_ `void ProcessComparisonQueue();` — Process the comparison queue to see if there are comparisons we need to respond to the test with.
- L481 _protected prototype_ `void ProcessAvailableTasks();` — Distributes any tests that are pending and deal with tests finishing.
- L484 _protected prototype_ `void ProcessResults();` — Processes the results after tests are complete.
- L491 _protected prototype_ `void RemoveTestRunning(const FGuid& OwnerInstanceId);` — Removes the test info. @param OwnerInstanceId Instance identifier of the test to remove.
- L494 _protected prototype_ `void SetControllerStatus( EAutomationControllerModuleState::Type AutomationTestState );` — Changes the controller state.
- L497 _protected prototype_ `void SetTestNames(const FGuid& AutomationWorkerInstanceId, TArray<FAutomationTestInfo>& TestInfo);` — Stores the tests that are valid for a particular device classification.
- L500 _protected prototype_ `void UpdateTests();` — Updates the tests to ensure they are all still running.
- L503 _protected prototype_ `void StopStartedTestSessions();` — Sends stop session message to worker instances.
- L512 _protected prototype_ `void SendMessage(FAutomationWorkerMessageBase* Message, UScriptStruct* TypeInfo, const FMessageAddress& ControllerAddress);` — Send a message in an unified way with passing correct Instance Id into the message we are going to send. @param Message The message to be sent. @param TypeInfo The type information about the message to be sent. @param ControllerAddress The message address of the receiver.
- L517 _private prototype_ `void HandleFindWorkersResponseMessage( const FAutomationWorkerFindWorkersResponse& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context );` — Handles FAutomationWorkerFindWorkersResponse messages.
- L520 _private prototype_ `void HandlePongMessage( const FAutomationWorkerPong& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context );` — Handles FAutomationWorkerPong messages.
- L523 _private prototype_ `void HandleReceivedScreenShot( const FAutomationWorkerScreenImage& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context );` — Handles FAutomationWorkerScreenImage messages.
- L526 _private prototype_ `void HandleReceivedComparisonResult( const FAutomationWorkerImageComparisonResults& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context );` — Handles FAutomationWorkerScreenshotComparisonResult messages.
- L529 _private prototype_ `void HandleTestDataRequest(const FAutomationWorkerTestDataRequest& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Handles FAutomationWorkerTestDataRequest messages.
- L532 _private prototype_ `void HandlePerformanceDataRequest(const FAutomationWorkerPerformanceDataRequest& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Handles FAutomationWorkerPerformanceDataRequest messages.
- L535 _private prototype_ `void HandleRequestNextNetworkCommandMessage( const FAutomationWorkerRequestNextNetworkCommand& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context );` — Handles FAutomationWorkerRequestNextNetworkCommand messages.
- L538 _private prototype_ `void HandleRequestTestsReplyCompleteMessage(const FAutomationWorkerRequestTestsReplyComplete& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Handles FAutomationWorkerRequestTestsReplyComplete messages.
- L541 _private prototype_ `void HandleRunTestsReplyMessage( const FAutomationWorkerRunTestsReply& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context );` — Handles FAutomationWorkerRunTestsReply messages.
- L544 _private prototype_ `void HandleWorkerOfflineMessage( const FAutomationWorkerWorkerOffline& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context );` — Handles FAutomationWorkerWorkerOffline messages.
- L547 _private prototype_ `void HandleReceivedTelemetryData(const FAutomationWorkerTelemetryData& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Handles FAutomationWorkerTelemetryData messages.
- L550 _private prototype_ `void ReportAutomationResult(const TSharedPtr<IAutomationReport> InReport, int32 ClusterIndex, int32 PassIndex);` — Writes out this automation result to the log
- L554 _private member_ `FGuid ActiveSessionId;` — Session this controller is currently communicating with
- L557 _private member_ `EAutomationControllerModuleState::Type AutomationTestState;` — The automation test state
- L560 _private member_ `uint32 DeviceGroupFlags = 0;` — Which grouping flags are enabled
- L563 _private member_ `bool bDeveloperDirectoryIncluded = false;` — Whether to include developer content in the automation tests
- L566 _private member_ `bool bHasErrors = false;` — Some tests have errors
- L569 _private member_ `bool bHasWarning = false;` — Some tests have warnings
- L572 _private member_ `bool bHasLogs = false;` — Some tests have logs
- L575 _private member_ `bool bIsLocalSession;` — Is this a local session
- L578 _private member_ `bool bTestResultsAvailable = false;` — Are tests results available
- L581 _private member_ `EAutomationTestFlags RequestedTestFlags = EAutomationTestFlags::None;` — Which sets of tests to consider
- L584 _private member_ `double CheckTestTimer;` — Timer to keep track of the last time tests were updated
- L587 _private member_ `float CheckTestIntervalSeconds = 1.0f;` — The time to wait between test updates in seconds
- L590 _private member_ `float GameInstanceLostTimerSeconds = 300.0f;` — The time to wait before considering a game instance as lost in seconds
- L593 _private member_ `uint32 ClusterDistributionMask;` — Whether tick is still executing tests for different clusters
- L596 _private member_ `FAutomationDeviceClusterManager DeviceClusterManager;` — Available worker GUIDs
- L599 _private member_ `uint32 ExecutionCount = 0;` — The iteration number of executing the tests.  Ensures restarting the tests won't allow stale results to try and commit
- L602 _private member_ `double LastTimeUpdateTicked = 0;` — Last time the update tests function was ticked
- L605 _private member_ `TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> MessageEndpoint;` — Holds the messaging endpoint.
- L608 _private member_ `uint32 RefreshTestResponses = 0;` — Counter for number of workers we have received responses from for Refreshing the Test List
- L611 _private member_ `FAutomationReportManager ReportManager;` — Available stats/status for all tests.
- L631 _private member_ `TArray< FTestRunningInfo > TestRunningArray;` — A array of running tests.
- L634 _private member_ `TSet< FGuid > StartedTestSessionWorkerInstanceIdSet;` — Set of worker instance identifiers for started sessions.
- L637 _private member_ `int32 NumTestPasses = 0;` — The number of test passes to perform.
- L640 _private member_ `int32 CurrentTestPass = 0;` — The current test pass we are on.
- L643 _private member_ `bool bSendAnalytics = false;` — If we should send result to analytics
- L646 _private member_ `bool bKeepPIEOpen = false;` — If we should send keep the PIE open when test pass end
- L649 _private member_ `bool bSortTestsByFailure = false;` — If we should sort tests by failure type in json/html report
- L652 _private member_ `bool bPruneLogsOnSuccess = true;` — If we should prune log events from test report on success
- L655 _private member_ `bool bRequiresReportGeneration = false;` — If the test requires any sort of reporting to be handled (delegate or writing to file)
- L658 _private member_ `FAutomatedTestPassResults JsonTestPassResults;` — The list of results generated by our test pass.
- L661 _private member_ `IScreenShotManagerPtr ScreenshotManager;` — The screenshot manager.
- L674 _private member_ `TQueue<TSharedPtr<FComparisonEntry>> ComparisonQueue;` — Pending image comparisons
- L677 _private member_ `FString ReportExportPath;` — The report folder override path that may have been provided over the commandline, -ReportOutputPath=""
- L678 _private member_ `FString ReportURLPath;`
- L680 _private member_ `FString DeveloperReportUrl;`
- L682 _private member_ `bool bResumeRunTest;`
- L685 _private member_ `TSharedPtr<class FWaitForInteractiveFrameRate> InteractiveFrameRateCheck;`
- L691 _private member_ `FOnAutomationControllerManagerShutdown ShutdownDelegate;` — Holds a delegate that is invoked when the controller shuts down.
- L694 _private member_ `FOnAutomationControllerManagerTestsAvailable TestsAvailableDelegate;` — Holds a delegate that is invoked when the controller has tests available.
- L697 _private member_ `FOnAutomationControllerTestsRefreshed TestsRefreshedDelegate;` — Holds a delegate that is invoked when the controller's tests are being refreshed.
- L700 _private member_ `FOnAutomationControllerReset ControllerResetDelegate;` — Holds a delegate that is invoked when the controller's reset.
- L703 _private member_ `FOnAutomationControllerTestsComplete TestsCompleteDelegate;` — Holds a delegate that is invoked when the tests have completed.

#### struct `FAutomationControllerManager::FTestRunningInfo`  
`struct FTestRunningInfo`  
_L614-628_
- desc: A data holder to keep track of how long tests have been running.
- L616 _public function_ `FTestRunningInfo( FMessageAddress InMessageAddress, FGuid InInstanceId): OwnerMessageAddress( InMessageAddress), OwnerInstanceId( InInstanceId ), LastPingTime( 0.f )`
- L623 _public member_ `FMessageAddress OwnerMessageAddress;` — The test runners message address
- L625 _public member_ `FGuid OwnerInstanceId;` — The test runner's instance ID
- L627 _public member_ `double LastPingTime;` — The time since we had a ping from the instance

#### struct `FAutomationControllerManager::FComparisonEntry`  
`struct FComparisonEntry`  
_L666-671_
- desc: Holds the information required to perform a screen comparison asynchronously.
- L668 _public member_ `FMessageAddress Sender;`
- L669 _public member_ `FGuid InstanceId;`
- L670 _public member_ `TFuture<FImageComparisonResult> PendingComparison;`

### `Source/Developer/AutomationController/Private/AutomationControllerModule.h` (Private)


#### class `FAutomationControllerModule`  
`class FAutomationControllerModule : public IAutomationControllerModule`  
_L11-34_
- inherits: `IAutomationControllerModule`
- desc: Implements the AutomationController module.
- L18 _public prototype_ `virtual IAutomationControllerManagerRef GetAutomationController( ) override;`
- L19 _public prototype_ `virtual void Init() override;`
- L20 _public prototype_ `virtual void Tick() override;`
- L26 _public prototype_ `virtual void StartupModule() override;`
- L27 _public prototype_ `virtual void ShutdownModule() override;`
- L28 _public prototype_ `virtual bool SupportsDynamicReloading() override;`
- L33 _private member_ `static IAutomationControllerManagerPtr AutomationControllerSingleton;` — Holds the automation controller singleton.

### `Source/Developer/AutomationController/Private/AutomationDeviceClusterManager.h` (Private)


#### struct `FAutomationDeviceInfo`  
`struct FAutomationDeviceInfo`  
_L16-67_
- reflection: `USTRUCT()`
- desc: Hold information about the Device
- L22 _public member_ `FString DeviceName;` — `UPROPERTY()` — The name of device
- L26 _public member_ `FGuid Instance;` — `UPROPERTY()` — The instance ID
- L30 _public member_ `FString InstanceName;` — `UPROPERTY()` — The instance Name
- L34 _public member_ `FString Platform;` — `UPROPERTY()` — The name of the platform
- L38 _public member_ `FString OSVersion;` — `UPROPERTY()` — The name of the operating system version
- L42 _public member_ `FString Model;` — `UPROPERTY()` — The name of the device model
- L46 _public member_ `FString GPU;` — `UPROPERTY()` — The name of the GPU
- L50 _public member_ `FString CPUModel;` — `UPROPERTY()` — The name of the CPU model
- L54 _public member_ `uint32 RAMInGB = 0;` — `UPROPERTY()` — The amount of RAM this device has in gigabytes
- L58 _public member_ `FString RenderMode;` — `UPROPERTY()` — The name of the current render mode
- L62 _public member_ `FString RHI;` — `UPROPERTY()` — The name of the current RHI
- L66 _public member_ `FString AppInstanceLog;` — `UPROPERTY()` — The path to the application instance log

#### class `FAutomationDeviceClusterManager`  
`class FAutomationDeviceClusterManager`  
_L72-267_
- desc: Managers groups of devices for job distribution
- L76 _public prototype_ `void Reset();` — Clear out all clusters for a new session
- L85 _public prototype_ `void AddDeviceFromMessage(const FMessageAddress& MessageAddress, const FAutomationWorkerFindWorkersResponse& Message, const uint32 GroupFlags);` — Add a new device from an AutomationWorkerFindWorkersResponse message, creating new clusters as needed. @param MessageAddress The network address of an available worker. @param Message The message that contains the device info. @param GroupFlags Used find out which group to put the new device into.
- L93 _public prototype_ `void UpdateDeviceFromMessage(const FMessageAddress& MessageAddress, const FAutomationWorkerMessageBase& Message);` — Update existing device's network address. @param MessageAddress The network address of an available worker. @param Message The message that contains the device info.
- L96 _public prototype_ `void Remove(const FGuid& DeviceInstanceId);` — Remove a device (went offline, etc).
- L99 _public prototype_ `int32 GetNumClusters() const;` — Returns number of unique device types.
- L102 _public prototype_ `int32 GetTotalNumDevices() const;` — Returns the sum of the device counts per cluster.
- L105 _public prototype_ `int32 GetNumDevicesInCluster (const int32 ClusterIndex) const;` — Returns the number of devices in of a particular device type.
- L108 _public prototype_ `int32 GetNumActiveDevicesInCluster(const int32 ClusterIndex) const;` — Returns the number of active devices in of a particular device type.
- L111 _public prototype_ `FString GetClusterGroupName(const int32 ClusterIndex) const;` — Returns the name of the cluster group.
- L114 _public prototype_ `FString GetClusterDeviceType (const int32 ClusterIndex) const;` — Returns the name of the devices within this cluster.
- L117 _public prototype_ `FString GetClusterDeviceName(const int32 ClusterIndex, const int32 DeviceIndex) const;` — Returns the name of a device within a cluster.
- L120 _public prototype_ `FString GetClusterGameInstance(const int32 ClusterIndex, const int32 DeviceIndex) const;` — Returns the instance of the game within a cluster.
- L123 _public prototype_ `FGuid GetClusterGameInstanceId(const int32 ClusterIndex, const int32 DeviceIndex) const;` — Returns the instance identifier of the game within a cluster.
- L126 _public prototype_ `const FAutomationDeviceInfo& GetDeviceInfo(const int32 ClusterIndex, const int32 DeviceIndex) const;` — Returns the name of a device within a cluster.
- L136 _public prototype_ `bool FindDevice(const FGuid& InstanceId, int32& OutClusterIndex, int32& OutDeviceIndex);` — Finds the cluster/device index for a particular GUID. @param InstanceId The device instance identifier. @param OutClusterIndex The index of the platform this device was in. @param OutDeviceIndex The index of the device within OutClusterIndex. @return true if the device was found within a cluster.
- L146 _public prototype_ `FMessageAddress GetDeviceMessageAddress(const int32 ClusterIndex, const int32 DeviceIndex) const;` — Returns the message address of the device specified. @param ClusterIndex Index of the device cluster. @param DeviceIndex Index of the device within the cluster. @return The message address of this device
- L155 _public prototype_ `TArray<FMessageAddress> GetDevicesReservedForTest(const int32 ClusterIndex, TSharedPtr <IAutomationReport> Report);` — Returns the devices that have been reserved for a particular test. @param ClusterIndex The device type we are testing. @param Report The automation test that we are trying to run (when we have enough participants). @return The array of devices that are currently signed up for running this test.
- L164 _public prototype_ `TSharedPtr <IAutomationReport> GetTest(const int32 ClusterIndex, const int32 DeviceIndex) const;` — Returns the current test this device should be running. @param ClusterIndex Index of the device cluster. @param DeviceIndex Index of the device within the cluster. @return nullptr if this device is available or the test structure if it is in-process.
- L173 _public prototype_ `void SetTest(const int32 ClusterIndex, const int32 DeviceIndex, TSharedPtr <IAutomationReport> NewReport);` — Sets the current test being run by the particular device. @param ClusterIndex The Cluster which holds the device we intend to run the test on. @param DeviceIndex The devices index in the cluster where we intend to run the test on. @param NewReport The test we are going to run.
- L181 _public prototype_ `void ResetAllDevicesRunningTest( const int32 ClusterIndex, IAutomationReportPtr InTest );` — Resets all cases on devices which are running the specified test to NULL. @param ClusterIndex The Cluster where we want all devices running the test to cease. @param InTest The test we are stopping.
- L189 _public prototype_ `void DisableDevice( const int32 ClusterIndex, const int32 DeviceIndex );` — Disable a device as it is no longer available - keep around to get the results. @param ClusterIndex The index of the platform this device was in. @param DeviceIndex The index of the device within OutClusterIndex.
- L197 _public prototype_ `bool DeviceEnabled( const int32 ClusterIndex, const int32 DeviceIndex );` — Check if a device is enabled. @param ClusterIndex The index of the platform this device was in. @param DeviceIndex The index of the device within OutClusterIndex.
- L204 _public prototype_ `bool HasActiveDevice();` — Check if there are any active game instances left. @return True if there are some game instances.
- L207 _public prototype_ `void ReGroupDevices( const uint32 GroupFlags );` — Regroups the device clusters based off the current group flags.
- L263 _private prototype_ `FString GetGroupNameForDevice(const FDeviceState& DeviceState, const uint32 DeviceGroupFlags);` — Generates a group name based off the device info and current group flags
- L266 _private member_ `TArray <FDeviceCluster> Clusters;` — Array of all clusters

#### class `FAutomationDeviceClusterManager::FDeviceState`  
`class FDeviceState`  
_L212-244_
- desc: per actual device, the network address and current test being run
- L215 _public function_ `FDeviceState(FMessageAddress NewMessageAddress, const FAutomationWorkerFindWorkersResponse& Message )`
- L234 _public member_ `FMessageAddress DeviceMessageAddress;` — Network address for device
- L237 _public member_ `FAutomationDeviceInfo Info;` — The Device full info
- L240 _public member_ `TSharedPtr <IAutomationReport> Report;` — NULL if this device is available to do work
- L243 _public member_ `bool IsDeviceAvailable;` — Hold if the game instance is available

#### class `FAutomationDeviceClusterManager::FDeviceCluster`  
`class FDeviceCluster`  
_L247-258_
- desc: for each cluster, the name and array of known devices
- L251 _public member_ `FString ClusterName;` — Name of the Cluster
- L254 _public member_ `FString DeviceTypeName;` — Name of the platform
- L257 _public member_ `TArray <FDeviceState> Devices;` — Guids/state for each device of this type

### `Source/Developer/AutomationController/Private/AutomationReport.h` (Private)


#### class `FAutomationReport`  
`class FAutomationReport : public IAutomationReport`  
_L13-122_
- inherits: `IAutomationReport`
- desc: Interface for automation test results modules.
- L17 _public prototype_ `FAutomationReport(FAutomationTestInfo& TestInfo, bool bIsParent = false);`
- L23 _public prototype_ `virtual void Empty() override;`
- L24 _public prototype_ `virtual FString GetTestParameter() const override;`
- L25 _public prototype_ `virtual FString GetTags() const override;`
- L26 _public prototype_ `virtual TArray<FString> GetTagsArray() const override;`
- L27 _public prototype_ `virtual FString GetAssetPath() const override;`
- L28 _public prototype_ `virtual FString GetOpenCommand() const override;`
- L29 _public prototype_ `virtual FString GetCommand() const override;`
- L30 _public prototype_ `virtual const FString& GetDisplayName() const override;`
- L31 _public prototype_ `virtual const FString& GetFullTestPath() const override;`
- L32 _public prototype_ `virtual FString GetDisplayNameWithDecoration() const override;`
- L33 _public prototype_ `virtual int32 GetTotalNumChildren() const override;`
- L34 _public prototype_ `virtual int32 GetTotalNumFilteredChildren() const override;`
- L35 _public prototype_ `virtual int32 GetEnabledTestsNum() const override;`
- L36 _public prototype_ `virtual void GetEnabledTestNames(TArray<FString>& OutEnabledTestNames, FString CurrentPath) const override;`
- L37 _public prototype_ `virtual void GetFilteredTestNames(TArray<FString>& OutFilteredTestNames, FString CurrentPath) const override;`
- L38 _public prototype_ `virtual void SetEnabledTests(const TArray<FString>& EnabledTests, FString CurrentPath) override;`
- L39 _public prototype_ `virtual bool IsEnabled() const override;`
- L40 _public prototype_ `virtual void SetEnabled(bool bShouldBeEnabled) override;`
- L41 _public prototype_ `virtual void SetSupport(const int32 ClusterIndex) override;`
- L42 _public prototype_ `virtual bool IsSupported(const int32 ClusterIndex) const override;`
- L43 _public prototype_ `virtual void SetTestFlags(const EAutomationTestFlags TestFlags) override;`
- L44 _public prototype_ `virtual EAutomationTestFlags GetTestFlags( ) const override;`
- L45 _public prototype_ `virtual FString GetSourceFile() const override;`
- L46 _public prototype_ `virtual int32 GetSourceFileLine() const override;`
- L47 _public prototype_ `virtual const bool IsParent( ) override;`
- L48 _public prototype_ `virtual const bool IsSmokeTest( ) override;`
- L49 _public prototype_ `virtual bool SetFilter( TSharedPtr< AutomationFilterCollection > InFilter, const bool ParentPassedFilter = false ) override;`
- L50 _public prototype_ `virtual TArray<TSharedPtr<IAutomationReport> >& GetFilteredChildren() override;`
- L51 _public prototype_ `virtual TArray<TSharedPtr<IAutomationReport> >& GetChildReports() override;`
- L52 _public prototype_ `virtual void ClustersUpdated(const int32 NumClusters) override;`
- L53 _public prototype_ `virtual void ResetForExecution(const int32 NumTestPasses) override;`
- L54 _public prototype_ `virtual void SetResults(const int32 ClusterIndex, const int32 PassIndex, const FAutomationTestResults& InResults) override;`
- L55 _public prototype_ `virtual void AddArtifact(const int32 ClusterIndex, const int32 PassIndex, const FAutomationArtifact& Artifact) override;`
- L56 _public prototype_ `virtual void GetCompletionStatus(const int32 ClusterIndex, const int32 PassIndex, FAutomationCompleteState& OutCompletionState) override;`
- L57 _public prototype_ `virtual EAutomationState GetState(const int32 ClusterIndex, const int32 PassIndex) const override;`
- L58 _public prototype_ `virtual void SetState(const EAutomationState State) override;`
- L59 _public prototype_ `virtual const FAutomationTestResults& GetResults( const int32 ClusterIndex, const int32 PassIndex ) override;`
- L60 _public prototype_ `virtual const int32 GetNumResults( const int32 ClusterIndex ) override;`
- L61 _public prototype_ `virtual const int32 GetCurrentPassIndex( const int32 ClusterIndex ) override;`
- L62 _public prototype_ `virtual FString GetGameInstanceName( const int32 ClusterIndex ) override;`
- L63 _public prototype_ `virtual TSharedPtr<IAutomationReport> EnsureReportExists(FAutomationTestInfo& TestInfo, const int32 ClusterIndex, const int32 NumPasses) override;`
- L64 _public prototype_ `virtual TSharedPtr<IAutomationReport> GetNextReportToExecute(bool& bOutAllTestsComplete, const int32 ClusterIndex, const int32 PassIndex, const int32 NumDevicesInCluster) override;`
- L65 _public prototype_ `virtual void GetEnabledTestReports(TArray<TSharedPtr<IAutomationReport>>& OutReports) override;`
- L66 _public prototype_ `virtual const bool HasErrors() override;`
- L67 _public prototype_ `virtual const bool HasWarnings() override;`
- L68 _public prototype_ `virtual const bool GetDurationRange(float& OutMinTime, float& OutMaxTime) override;`
- L69 _public prototype_ `virtual const int32 GetNumDevicesRunningTest() const override;`
- L70 _public prototype_ `virtual const int32 GetNumParticipantsRequired() const override;`
- L71 _public prototype_ `virtual void SetNumParticipantsRequired( const int32 NewCount ) override;`
- L72 _public prototype_ `virtual bool IncrementNetworkCommandResponses() override;`
- L73 _public prototype_ `virtual void ResetNetworkCommandResponses() override;`
- L74 _public prototype_ `virtual const bool ExpandInUI() const override;`
- L75 _public prototype_ `virtual void StopRunningTest() override;`
- L76 _public prototype_ `virtual bool IsToBeSkipped(FName* OutReason = nullptr, bool* OutWarn = nullptr) const override;`
- L77 _public prototype_ `virtual bool IsToBeSkippedOnConditions() const override;`
- L78 _public prototype_ `virtual bool IsToBeSkippedByPropagation() const override;`
- L79 _public prototype_ `virtual void SetSkipFlag(bool bEnableSkip, const FAutomationTestExcludelistEntry* Template = nullptr, bool bFromPropagation = false) override;`
- L80 _public prototype_ `virtual TSharedPtr<FAutomationTestExcludeOptions> GetExcludeOptions() override;`
- L85 _private member_ `bool bEnabled;` — True if this test should be executed
- L88 _private member_ `bool bIsParent;` — True if this test is a parent
- L91 _private member_ `bool bNodeExpandInUI;` — True if this report should be expanded in the UI
- L94 _private member_ `bool bSelfPassesFilter;` — True if this report has passed the filter and should be highlighted in the UI
- L97 _private member_ `uint32 SupportFlags;` — List of bits that represents which device types requested this test
- L100 _private member_ `uint32 NumberNetworkResponsesReceived;` — Number of responses from network commands
- L103 _private member_ `TArray<TSharedPtr<IAutomationReport> >ChildReports;` — All child tests
- L106 _private member_ `TMap<uint32, uint32> ChildReportNameHashes;` — Map of all Report Name hashes to avoid iterating all items to test for existance
- L109 _private member_ `TArray<TSharedPtr<IAutomationReport> >FilteredChildReports;` — Filtered child tests
- L112 _private member_ `TArray< TArray<FAutomationTestResults> > Results;` — Results from execution of the test (per cluster)
- L115 _private member_ `FAutomationTestInfo TestInfo;` — Structure holding the test info
- L118 _private member_ `FAutomationTestExcludelistEntry ExcludeTestInfo;` — Structure holding the info on the exclude test
- L121 _private member_ `bool bNeedToSkip = false;` — True if this item is inside the exclude list

### `Source/Developer/AutomationController/Private/AutomationReportManager.h` (Private)


#### class `FAutomationReportManager`  
`class FAutomationReportManager`  
_L11-121_
- desc: Wrapper class to obfuscate the hierarchy of tests
- L15 _public prototype_ `FAutomationReportManager();` — default constructor
- L18 _public prototype_ `void Empty();` — Clears out all reports
- L21 _public prototype_ `void ClustersUpdated( const int32 NumClusters );` — Updates the automation reports when the number of clusters changes
- L27 _public prototype_ `void ResetForExecution(const int32 NumTestPasses);` — Resets for the next run of tests @param NumTestPasses The number of test results to store
- L30 _public prototype_ `void StopRunningTests();` — Stops all tests from running
- L40 _public prototype_ `TSharedPtr<IAutomationReport> GetNextReportToExecute(bool& bOutAllTestsComplete, const int32 ClusterIndex, const int32 PassIndex, const int32 NumDevicesInCluster);` — Searches for the next test to execute. @param bOutAllTestsComplete Returns True if all tests for this device cluster have been completed. @param ClusterIndex Index of the platform reporting the results of this test.  See AutomationDeviceClusterManager. @param PassIndex Index of the current test pass we are on. @param NumDevicesInCluster The number of devices which are available in this cluster.
- L47 _public prototype_ `TArray<TSharedPtr<IAutomationReport>> GetEnabledTestReports();` — Returns all the enabled test reports. @return an array of all reports
- L57 _public prototype_ `TSharedPtr<IAutomationReport> EnsureReportExists(FAutomationTestInfo& TestInfo, const int32 ClusterIndex, const int32 NumPasses);` — Ensures the nested tree exists ("blueprint.test.all") would have 3 levels other than the root. @param TestInfo Structure containing the test info. @param ClusterIndex Index of the platform reporting the results of this test.  See AutomationDeviceClusterManager. @param NumPasses The number of test passes to create reports for. @return The automation report.
- L60 _public prototype_ `void SetFilter( TSharedPtr< AutomationFilterCollection > InFilter );` — Filters the visible tests based on name, status, speed.
- L63 _public prototype_ `TArray <TSharedPtr <IAutomationReport> >& GetFilteredReports();` — gets array of filtered tests to display in the UI.
- L66 _public prototype_ `void SetVisibleTestsEnabled(const bool bEnabled);` — Sets whether all visible tests are enabled or not.
- L69 _public prototype_ `int32 GetEnabledTestsNum () const;` — Returns number of tests that will be run.
- L72 _public prototype_ `void GetEnabledTestNames(TArray<FString>& OutEnabledTestNames) const;` — Gets the names of enabled tests.
- L75 _public prototype_ `void GetFilteredTestNames(TArray<FString>& OutFilteredTestNames) const;` — Gets the names of filtered tests.
- L78 _public prototype_ `void SetEnabledTests(const TArray<FString>& EnabledTests);` — Sets the enabled tests based off the passed list of enabled tests.
- L81 _public function_ `void SetCurrentTestPass(int32 PassIndex)` — Sets the current test pass.
- L89 _public prototype_ `const bool ExportReport( uint32 FileExportTypeMask, const int32 NumDeviceClusters );` — Export the automation report. @param FileExportTypeMask The file export mask - errors, warning etc. @param NumDeviceClusters The number of devices in a cluster.
- L101 _protected prototype_ `void AddResultReport( TSharedPtr< IAutomationReport > InReport, const int32 NumDeviceClusters, TArray< FString >& ResultsLog, uint32 FileExportTypeMask );` — Used in report generation to find leaf reports. @param InReport The report to add. @param NumDeviceClusters - The number of devices in a cluster. @param ResultsLog - Message log to store the test results. @param FileExportTypeMask - The file export mask - errors, warning etc.
- L111 _protected prototype_ `void FindLeafReport( TSharedPtr< IAutomationReport > InReport, const int32 NumDeviceClusters, TArray< FString >& ResultsLog, uint32 FileExportTypeMask );` — Used in report generation to find leaf reports. @param InReport The parent report. @param NumDeviceClusters The number of devices in a cluster. @param ResultsLog Message log to store the test results. @param FileExportTypeMask The file export mask - errors, warning etc.
- L117 _private member_ `TSharedPtr <IAutomationReport> ReportRoot;` — Root node of the hierarchy, just there to ensure little code duplication.
- L120 _private member_ `int32 CurrentTestPass;` — Which test pass we are currently on.

### `Source/Developer/AutomationController/Private/AutomationTelemetry.h` (Private)


#### class `FAutomationTelemetry`  
`class FAutomationTelemetry : FNoncopyable`  
_L11-84_
- inherits: `FNoncopyable`
- L17 _public prototype_ `static void Initialize();` — Called to initialize the singleton.
- L20 _public prototype_ `static bool IsInitialized();` — Helper to check if the Analytics provider is Initialized
- L25 _public prototype_ `static void HandleAddTelemetry(const FAutomationWorkerTelemetryData& Data);` — Handle adding telemetry data to output
- L29 _private member_ `static bool bIsInitialized;`
- L30 _private member_ `static FString TelemetryDirectory;`
- L31 _private member_ `static bool bResetTelemetryStorageOnNewSession;`
- L46 _private function_ `static FString ToColumnName(uint8 Index)`
- L76 _private prototype_ `static FString ToColumnValue(uint8 Index, const FAutomationWorkerTelemetryData& Data, const FAutomationWorkerTelemetryItem& Item);`
- L79 _private prototype_ `static bool InitiateStorage(const FString& StorageName);` — Initiate telemetry storage csv file
- L82 _private prototype_ `static FString GetStorageFilePath(const FString& StorageName);` — Get telemetry storage file path using automation settings

#### enum `FAutomationTelemetry::Columns`  
`enum Columns : uint8`  
_L33-44_
- L35 _public enumerator_ `Configuration`
- L36 _public enumerator_ `Platform`
- L37 _public enumerator_ `DateTime`
- L38 _public enumerator_ `TestName`
- L39 _public enumerator_ `Context`
- L40 _public enumerator_ `DataPoint`
- L41 _public enumerator_ `Measurement`
- L43 _public enumerator_ `Count` — number of columns

### `Source/Developer/AutomationController/Public/AutomationControllerSettings.h` (Public)


#### struct `FAutomatedTestFilterBase`  
`struct FAutomatedTestFilterBase`  
_L25-75_
- reflection: `USTRUCT()`
- desc: Describes a base filter for a test group.
- L31 _public function_ `FAutomatedTestFilterBase(FString InContains, bool InMatchFromStart = false, bool InMatchFromEnd = false) : Contains(InContains), MatchFromStart(InMatchFromStart), MatchFromEnd(InMatchFromEnd)`
- L36 _public function_ `FAutomatedTestFilterBase() : FAutomatedTestFilterBase(TEXT(""))`
- L38 _public prototype_ `virtual ~FAutomatedTestFilterBase() = default;`
- L42 _public member_ `FString Contains;` — `UPROPERTY(Config)` — String that the test must contain
- L46 _public member_ `bool MatchFromStart;` — `UPROPERTY(Config)` — If true start matching from the start of the string, else anywhere
- L50 _public member_ `bool MatchFromEnd;` — `UPROPERTY(Config)` — If true start matching from the end of the string, else anywhere
- L52 _public function_ `virtual bool PassesFilter(const TSharedPtr< IAutomationReport >& InReport) const`

#### struct `FAutomatedTestTagFilter`  
`struct FAutomatedTestTagFilter`  
_L81-124_
- reflection: `USTRUCT()`
- desc: Describes a tag-based filter for tests
- L92 _public function_ `FAutomatedTestTagFilter(const FString& InContains)` — @param InContains - String of concatenated tags and boolean operators @see FTextFilterExpressionEvaluator
- L106 _public prototype_ `virtual ~FAutomatedTestTagFilter() = default;`
- L108 _public function_ `FAutomatedTestTagFilter() : FAutomatedTestTagFilter(TEXT(""))`
- L110 _public function_ `virtual bool PassesFilter(const TSharedPtr< IAutomationReport >& InReport) const`
- L123 _private member_ `TSharedPtr<FTextFilterExpressionEvaluator> TagFilter;`

#### struct `FAutomatedTestFilter`  
`struct FAutomatedTestFilter : public FAutomatedTestFilterBase`  
_L131-183_
- reflection: `USTRUCT()`
- inherits: `FAutomatedTestFilterBase`
- desc: Describes a filter for a test group with exclude and tag options.
- L137 _public function_ `FAutomatedTestFilter(FString InContains, bool InMatchFromStart = false, bool InMatchFromEnd = false) : FAutomatedTestFilterBase(InContains, InMatchFromStart, InMatchFromEnd)`
- L142 _public function_ `FAutomatedTestFilter() : FAutomatedTestFilter(TEXT(""))`
- L146 _public member_ `TArray<FAutomatedTestFilterBase> Exclude;` — `UPROPERTY(Config)` — List of filters to exclude
- L150 _public member_ `TArray<FAutomatedTestTagFilter> Tags;` — `UPROPERTY(Config)` — List of tag filters specific to this group
- L152 _public function_ `virtual bool PassesFilter(const TSharedPtr< IAutomationReport >& InReport) const override`

#### struct `FAutomatedTestGroup`  
`struct FAutomatedTestGroup`  
_L189-200_
- reflection: `USTRUCT()`
- desc: Describes a group of tests. Each group has a name and a set of filters that determine group membership
- L196 _public member_ `FString Name;` — `UPROPERTY(Config)`
- L199 _public member_ `TArray<FAutomatedTestFilter> Filters;` — `UPROPERTY(Config)`

#### class `UAutomationControllerSettings`  
`class UAutomationControllerSettings : public UObject`  
_L208-279_
- reflection: `UCLASS(MinimalAPI, config = Engine, defaultconfig)`
- inherits: `UObject`
- desc: Implements the Editor's user settings.
- L216 _public member_ `TArray<FAutomatedTestGroup> Groups;` — `UPROPERTY(Config)` — List of user-defined test groups
- L220 _public member_ `bool bSuppressLogErrors;` — `UPROPERTY(Config)` — Whether to suppress log from test results (default=false)
- L224 _public member_ `bool bSuppressLogWarnings;` — `UPROPERTY(Config)` — Whether to suppress log warnings from test results (default=false)
- L228 _public member_ `bool bElevateLogWarningsToErrors;` — `UPROPERTY(Config)` — Whether to treat log warnings as log errors (default=true)
- L232 _public member_ `TArray<FString> SuppressedLogCategories;` — `UPROPERTY(Config)` — Log categories where warnings/errors will not affect the result of tests. A finer-grained way of preventing rogue systems from leading to test warnings/errors
- L236 _public member_ `bool bKeepPIEOpen;` — `UPROPERTY(Config)` — Whether to keep the PIE Open in the editor at the end of a test pass (default=false)
- L240 _public member_ `bool bAutoExpandSingleItemSubgroups;` — `UPROPERTY(Config)` — Whether to automatically expand Automation Tests tree subgroups that have single non-leaf item as a child (default=true)
- L244 _public member_ `bool bSortTestsByFailure;` — `UPROPERTY(Config)` — Whether to Sort tests by failure type in json/html report
- L248 _public member_ `bool bPruneLogsOnSuccess;` — `UPROPERTY(Config)` — Whether to prune log events from test report on success
- L253 _private member_ `bool bTreatLogWarningsAsTestErrors;` — `UPROPERTY(Config, Meta = (DeprecatedProperty, DeprecationMessage = "Use bElevateLogWarningsToErrors instead."))` — Whether to treat log warnings as test errors (default=true)
- L258 _public member_ `float CheckTestIntervalSeconds;` — `UPROPERTY(Config)` — How long to wait between test updates (default=1sec)
- L262 _public member_ `float GameInstanceLostTimerSeconds;` — `UPROPERTY(Config)` — The maximum response wait time for detecting a lost game instance (default=300sec)
- L266 _public member_ `FString TelemetryDirectory;` — `UPROPERTY(Config)` — Path to where telemetry files are saved (default=<project>/Saved/Automation/Telemetry/)
- L270 _public member_ `bool bResetTelemetryStorageOnNewSession;` — `UPROPERTY(Config)` — Whether to reset data stored in telemetry file (default=false)
- L272 _public prototype_ `virtual void PostInitProperties() override;`
- L275 _public member_ `TArray<FString> InitialSelectedTestsNames;` — List of pre-selected tests to filter by when requesting tests
- L278 _public member_ `bool bOpenTagEditorWhenInitialSelectedTestsNames;` — Prepare to open test tag editor when a list of InitialSelectedTestsNames is provided

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API AUTOMATIONCONTROLLER_API`

### `Source/Developer/AutomationController/Public/AutomationFilter.h` (Public)


#### class `FAutomationFilter`  
`class FAutomationFilter : public IFilter<const TSharedPtr<class IAutomationReport>&>`  
_L9-176_
- inherits: `IFilter<constTSharedPtr<classIAutomationReport>&>`
- L15 _public function_ `FAutomationFilter() : OnlySmokeTests( false ) , ShowErrors( false ) , ShowWarnings( false ) , OnlyExcludedTests ( false )` — Default constructor.
- L30 _public function_ `void SetShowWarnings( const bool InShowWarnings )` — Set if we should only show warnings. @param InShowWarnings If we should show warnings or not. @see SetOnlyShowSmokeTests, SetShowErrors, ShouldShowWarnings
- L41 _public function_ `const bool ShouldShowWarnings( ) const` — Should we show warnings. @return True if we should be showing warnings. @see SetShowErrors, SetShowWarnings
- L52 _public function_ `void SetShowErrors( const bool InShowErrors )` — Set if we should only show errors. @param InShowErrors If we should show errors. @see SetOnlyShowSmokeTests, SetShowWarnings, ShouldShowErrors
- L63 _public function_ `const bool ShouldShowErrors( ) const` — Should we show errors. @return True if we should be showing errors. @see SetShowErrors, ShouldShowWarnings
- L73 _public function_ `void SetOnlyShowSmokeTests( const bool InOnlySmokeTests )` — Set if we should only show smoke tests. @param InOnlySmokeTests If we should show smoke tests.
- L84 _public function_ `const bool OnlyShowSmokeTests( ) const` — Should we only show errors. @return True if we should be showing errors. @see SetOnlyShowSmokeTests, ShouldShowErrors, ShouldShowWarnings
- L95 _public function_ `const bool ShouldShowOnlyExcludedTests() const` — Should we only show excluded tests. @return True if we should be showing only excluded tests. @see SetOnlyShowSmokeTests, ShouldShowErrors, ShouldShowWarnings
- L105 _public function_ `void SetShowOnlyExcludedTests(const bool InOnlyExcludedTests)` — Set if we should only show excluded tests. @param InOnlyExcludedTests If we should show excluded tests.
- L114 _public prototype_ `DECLARE_DERIVED_EVENT(FAutomationFilter, IFilter< const TSharedPtr< class IAutomationReport >& >::FChangedEvent, FChangedEvent);`
- L115 _public function_ `virtual FChangedEvent& OnChanged() override`
- L117 _public function_ `virtual bool PassesFilter( const TSharedPtr< IAutomationReport >& InReport ) const override`
- L163 _private member_ `FChangedEvent ChangedEvent;` — The event that broadcasts whenever a change occurs to the filter.
- L166 _private member_ `bool OnlySmokeTests;` — Only smoke tests will pass the test.
- L169 _private member_ `bool ShowErrors;` — Only errors will pass the test.
- L172 _private member_ `bool ShowWarnings;` — Only warnings will pass the test.
- L175 _private member_ `bool OnlyExcludedTests;` — Only exclude tests.

#### Free symbols / members of external scopes

- L114 _delegate_ `DECLARE_DERIVED_EVENT(FAutomationFilter, IFilter< const TSharedPtr< class IAutomationReport >& >::FChangedEvent, FChangedEvent);`

### `Source/Developer/AutomationController/Public/AutomationGroupFilter.h` (Public)


#### class `FAutomationGroupFilter`  
`class FAutomationGroupFilter : public IFilter<const TSharedPtr<class IAutomationReport>&>`  
_L10-99_
- inherits: `IFilter<constTSharedPtr<classIAutomationReport>&>`
- L16 _public function_ `FAutomationGroupFilter()` — Default constructor.
- L20 _public function_ `FAutomationGroupFilter(const TArray<FAutomatedTestFilter>& InFilters) : Filters(InFilters)` — Default constructor with array param.
- L25 _public function_ `FAutomationGroupFilter(const FAutomatedTestFilter& InFilter)` — Default constructor, group with single elements.
- L37 _public function_ `void SetFilters(const TArray<FAutomatedTestFilter>& InFilters)` — Set the list of strings the group filter checks for substrings in test display name. @param InFilters An array of strings to filter against test display names. @see FAutomatedTestFilterBase::MatchFromStart, FAutomatedTestFilterBase::MatchFromEnd
- L49 _public function_ `void SetTagFilter(const TArray < FAutomatedTestTagFilter>& InFilters)` — Set the list of search syntax strings evaluated against test tags. @param InFilters An array of strings to filter against test tags. @see FTextFilterExpressionEvaluator
- L58 _public prototype_ `DECLARE_DERIVED_EVENT(FAutomationGroupFilter, IFilter< const TSharedPtr< class IAutomationReport >& >::FChangedEvent, FChangedEvent);`
- L59 _public function_ `virtual FChangedEvent& OnChanged() override`
- L61 _public function_ `virtual bool PassesFilter(const TSharedPtr< IAutomationReport >& InReport) const override`
- L91 _private member_ `FChangedEvent ChangedEvent;` — The event that broadcasts whenever a change occurs to the filter.
- L94 _private member_ `TArray<FAutomatedTestFilter> Filters;` — The array of FAutomatedTestFilter to filter against test names. At least one from the list must be matched.
- L97 _private member_ `TArray<FAutomatedTestTagFilter> TagFilters;` — The array of FAutomatedTestTagFilter to filter against test tags. At least one from the list must be matched.

#### Free symbols / members of external scopes

- L58 _delegate_ `DECLARE_DERIVED_EVENT(FAutomationGroupFilter, IFilter< const TSharedPtr< class IAutomationReport >& >::FChangedEvent, FChangedEvent);`

### `Source/Developer/AutomationController/Public/IAutomationControllerManager.h` (Public)


#### enum `EAutomationControllerModuleState::Type`  
`enum Type`  
_L20-28_
- L23 _public enumerator_ `Ready` — Has workers available
- L25 _public enumerator_ `Running` — Is running tests
- L27 _public enumerator_ `Disabled` — No workers available

#### enum `EFileExportType::Type`  
`enum Type`  
_L37-44_
- L39 _public enumerator_ `FET_Status = 0x00000001` — Export test status
- L40 _public enumerator_ `FET_Warnings = 0x00000002` — Export warnings
- L41 _public enumerator_ `FET_Errors = 0x00000004` — Export Errors
- L42 _public enumerator_ `FET_Logs = 0x00000008` — Export logs
- L43 _public enumerator_ `FET_All = 0x00000010` — Export everything

#### enum `EAutomationDeviceGroupTypes::Type`  
`enum Type`  
_L91-102_
- L93 _public enumerator_ `MachineName` — Group by machine name
- L94 _public enumerator_ `Platform` — Group by platform
- L95 _public enumerator_ `OSVersion` — Group by operating system version
- L96 _public enumerator_ `Model` — Group by machine model
- L97 _public enumerator_ `GPU` — Group by GPU
- L98 _public enumerator_ `CPUModel` — Group by CPU Model
- L99 _public enumerator_ `RamInGB` — Group by RAM in gigabytes
- L100 _public enumerator_ `RenderMode` — Group by RenderMode (D3D11_SM5, OpenGL_SM4, etc)
- L101 _public enumerator_ `Max`

#### class `IAutomationControllerManager`  
`class IAutomationControllerManager`  
_L162-475_
- desc: Interface for AutomationController .
- L171 _public prototype_ `virtual void RequestAvailableWorkers( const FGuid& InSessionId ) = 0;` — Broadcast a request for workers to ping if they are available. @param InSessionID the session ID to run the test on.
- L177 _public prototype_ `virtual bool IsReadyForTests() = 0;` — Return true when the manager is ready and capable of executing tests. if RunTests is called earlier it may block until internally these conditions are met
- L180 _public prototype_ `virtual void RequestTests() = 0;` — Send request for tests that are available to run.
- L187 _public prototype_ `virtual void RunTests( const bool bIsLocalSession = false ) = 0;` — Resets all enabled tests to be able to run during Tick by local/remote machines. @param bIsLocalSeesion Indicate if this is a local session. We do not time out local session automation tests.
- L190 _public prototype_ `virtual void StopTests() = 0;` — Stops all running tests.
- L193 _public prototype_ `virtual void Init() = 0;` — Initializes the automation controller.
- L200 _public prototype_ `virtual void RequestLoadAsset( const FString& InAssetName ) = 0;` — Request an asset to be loaded in the editor. @param InAssetName The asset name.
- L203 _public prototype_ `virtual void Tick() = 0;` — Tick function that will execute enabled tests for different device clusters.
- L210 _public prototype_ `virtual void SetNumPasses(const int32 InNumPasses) = 0;` — Sets the number of test passes. @param InNumPasses The number of test passes to perform.
- L217 _public prototype_ `virtual int32 GetNumPasses() = 0;` — Get the number of test passes. @return Number of passes.
- L222 _public prototype_ `virtual bool IsSendAnalytics() const = 0;` — Returns if analytics should be sent
- L227 _public prototype_ `virtual void SetSendAnalytics(const bool bNewValue) = 0;` — Sets if analytics should be sent
- L232 _public prototype_ `virtual bool KeepPIEOpen() const = 0;` — Returns if PIE should be kept open when test pass end
- L237 _public prototype_ `virtual void SetKeepPIEOpen(const bool bNewValue) = 0;` — Sets if PIE should be kept open when test pass end
- L242 _public prototype_ `virtual void SetFilter( TSharedPtr< AutomationFilterCollection > InFilter ) = 0;` — Filters the visible list of tests.
- L247 _public prototype_ `virtual TArray <TSharedPtr <IAutomationReport> >& GetFilteredReports() = 0;` — Gives the array of filtered test results to the UI.
- L252 _public prototype_ `virtual TArray <TSharedPtr <IAutomationReport> > GetEnabledReports() = 0;` — Gives the array of enabled test results to the UI.
- L257 _public prototype_ `virtual int32 GetNumDeviceClusters() const = 0;` — Get num devices types.
- L262 _public prototype_ `virtual int32 GetNumDevicesInCluster(const int32 ClusterIndex) const = 0;` — Get num devices in specified cluster.
- L267 _public prototype_ `virtual FString GetClusterGroupName(const int32 ClusterIndex) const =0;` — Get the group name of the specified cluster.
- L272 _public prototype_ `virtual FString GetDeviceTypeName(const int32 ClusterIndex) const = 0;` — Get name of a particular device cluster.
- L281 _public prototype_ `virtual FGuid GetGameInstanceId(const int32 ClusterIndex, const int32 DeviceIndex) const = 0;` — Get a game instance ID. @param ClusterIndex The cluster Index. @param DeviceIndex The Device Index. @return identifier of a game.
- L289 _public prototype_ `virtual FString GetGameInstanceName(const int32 ClusterIndex, const int32 DeviceIndex) const = 0;` — Get a game instance name. @param ClusterIndex The cluster Index. @param DeviceIndex The Device Index.
- L297 _public prototype_ `virtual FString GetDeviceName(const int32 ClusterIndex, const int32 DeviceIndex) const = 0;` — Get a device name. @param ClusterIndex The cluster Index. @param DeviceIndex The Device Index.
- L302 _public prototype_ `virtual void SetVisibleTestsEnabled(const bool bEnabled) = 0;` — Sets whether all visible tests are enabled or not.
- L307 _public prototype_ `virtual int32 GetEnabledTestsNum() const = 0;` — Returns number of tests that will be run.
- L314 _public prototype_ `virtual void GetEnabledTestNames(TArray<FString>& OutEnabledTestNames) const = 0;` — Gets the names of all the enabled tests. @param OutEnabledTestNames The list to populate with enabled test names.
- L321 _public prototype_ `virtual void GetFilteredTestNames(TArray<FString>& OutFilteredTestNames) const = 0;` — Gets the names of all the filtered tests. @param OutFilteredTestNames The list to populate with filtered test names.
- L328 _public prototype_ `virtual void SetEnabledTests(const TArray<FString>& EnabledTests) = 0;` — Sets any tests that match a name in the enabled tests array. @param EnabledTests An array of test names that will be enabled.
- L335 _public prototype_ `virtual EAutomationControllerModuleState::Type GetTestState( ) const = 0;` — Gets the controller's current test state. @return The test state.
- L340 _public prototype_ `virtual void SetDeveloperDirectoryIncluded(const bool bInDeveloperDirectoryIncluded) = 0;` — Sets whether the automation tests should include developer content directories.
- L345 _public prototype_ `virtual bool IsDeveloperDirectoryIncluded(void) const = 0;` — Returns whether the automation tests should include developer content directories.
- L350 _public prototype_ `virtual void SetRequestedTestFlags(const EAutomationTestFlags InRequestedTestFlags) = 0;` — Sets what flags we're considering automation tests from
- L357 _public prototype_ `virtual const bool CheckTestResultsAvailable() const = 0;` — Check if the automation tests have completed. @return true if the tests are available.
- L364 _public prototype_ `virtual const bool ReportsHaveErrors() const = 0;` — Check if the automation tests results have errors. @return true if the tests have errors.
- L371 _public prototype_ `virtual const bool ReportsHaveWarnings() const = 0;` — Check if the automation tests results have warnings. @return true if the tests have warnings.
- L378 _public prototype_ `virtual const bool ReportsHaveLogs() const = 0;` — Check if the automation tests results have logs. @return true if the tests have logs.
- L383 _public prototype_ `virtual void ClearAutomationReports() = 0;` — Remove results from the automation controller module.
- L390 _public prototype_ `virtual const bool ExportReport( uint32 FileExportTypeMask ) = 0;` — Generate an automation report. @param FileExporTypeMask The types of report to export. Warning errors etc.
- L398 _public prototype_ `virtual bool IsTestRunnable( IAutomationReportPtr InReport ) const = 0;` — Check that the test we are looking to run is runnable. @param InReport The test we are checking is runnable. @return true if the test can be run, false if not.
- L401 _public prototype_ `virtual void RemoveCallbacks() = 0;` — Removes all callbacks.
- L404 _public prototype_ `virtual void Shutdown() = 0;` — Shuts down the manager.
- L407 _public prototype_ `virtual void Startup() = 0;` — Starts up the manager.
- L410 _public prototype_ `virtual bool IsDeviceGroupFlagSet( EAutomationDeviceGroupTypes::Type InDeviceGroup ) const = 0;` — Checks if a device group flag is set.
- L413 _public prototype_ `virtual void ToggleDeviceGroupFlag( EAutomationDeviceGroupTypes::Type InDeviceGroup ) = 0;` — Toggles a device group flag.
- L416 _public prototype_ `virtual void UpdateDeviceGroups( ) = 0;` — Updates the clusters when the device grouping changes.
- L418 _public prototype_ `virtual FString GetReportOutputPath() const = 0;`
- L420 _public prototype_ `virtual void ResetAutomationTestTimeout(const TCHAR* Reason) = 0;`
- L429 _public prototype_ `virtual FOnAutomationControllerManagerShutdown& OnShutdown( ) = 0;` — Gets the multicast delegate that is invoked when the controller manager shuts down. @return The delegate.
- L436 _public prototype_ `virtual FOnAutomationControllerManagerTestsAvailable& OnTestsAvailable( ) = 0;` — Gets the multicast delegate that is invoked when the controller has tests available. @return The delegate.
- L443 _public prototype_ `virtual FOnAutomationControllerTestsRefreshed& OnTestsRefreshed( ) = 0;` — Gets the multicast delegate that is invoked when the controller's test status changes. @return The delegate.
- L448 _public prototype_ `virtual FOnAutomationControllerTestsComplete& OnTestsComplete( ) = 0;` — Gets the test complete multicast delegate.
- L455 _public prototype_ `virtual FOnAutomationControllerReset& OnControllerReset() = 0;` — Gets a delegate that is invoked when the controller's reset. @return The delegate.
- L462 _public function_ `virtual FOnAutomationControllerReportGenerated& OnTestReportGenerated()` — Gets a delegate that is invoked when the controller generates a report. @return The delegate.
- L470 _public prototype_ `virtual ~IAutomationControllerManager() = default;` — Virtual destructor.
- L474 _protected member_ `FOnAutomationControllerReportGenerated TestReportGeneratedDelegate;` — Holds a delegate that is invoked when the tests have generated a report.

#### Free symbols / members of external scopes

- L11 _typedef_ `typedef TSharedPtr<class IAutomationControllerManager> IAutomationControllerManagerPtr;` — Type definition for shared pointers to instances of IAutomationControllerManager.
- L14 _typedef_ `typedef TSharedRef<class IAutomationControllerManager> IAutomationControllerManagerRef;` — Type definition for shared references to instances of IAutomationControllerManager.
- L18 _namespace_ `namespace EAutomationControllerModuleState`
- L35 _namespace_ `namespace EFileExportType`
- L55 _function_ `FORCEINLINE static bool IsSet( const uint32& InMask, const EFileExportType::Type InFlag )` (scope `EFileExportType`) — Check if a flag is set @param InMask The mask to check @param InFlag The flag to check @return True if the flag is set
- L70 _function_ `FORCEINLINE static void RemoveFlag( uint32& InMask, const EFileExportType::Type InFlag )` (scope `EFileExportType`) — Remove a flag @param InMask The mask to unset the flag on @param InFlag The flag to remove
- L81 _function_ `FORCEINLINE static void SetFlag( uint32& InMask, const EFileExportType::Type InFlag )` (scope `EFileExportType`) — Set a flag @param InMask The mask to set the flag on @param InFlag The flag to set
- L89 _namespace_ `namespace EAutomationDeviceGroupTypes`
- L104 _function_ `static FText ToName( const Type DeviceGroupType )` (scope `EAutomationDeviceGroupTypes`)
- L121 _function_ `static FText ToDescription(const Type DeviceGroupType)` (scope `EAutomationDeviceGroupTypes`)
- L141 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnAutomationControllerReset);` — Console command delegate type (takes no arguments.)  This is a void callback function.
- L141 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnAutomationControllerReset);` — Console command delegate type (takes no arguments.)  This is a void callback function.
- L144 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnAutomationControllerTestsRefreshed);` — Console command delegate type (takes no arguments.)  This is a void callback function.
- L144 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnAutomationControllerTestsRefreshed);` — Console command delegate type (takes no arguments.)  This is a void callback function.
- L147 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAutomationControllerManagerTestsAvailable, EAutomationControllerModuleState::Type);` — Delegate for setting the automation controller status in the UI
- L147 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAutomationControllerManagerTestsAvailable, EAutomationControllerModuleState::Type);` — Delegate for setting the automation controller status in the UI
- L150 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnAutomationControllerManagerShutdown);` — Delegate to call when the automation controller is shutdown.
- L150 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnAutomationControllerManagerShutdown);` — Delegate to call when the automation controller is shutdown.
- L153 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnAutomationControllerTestsComplete);` — Delegate to call when the tests are complete.
- L153 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnAutomationControllerTestsComplete);` — Delegate to call when the tests are complete.
- L156 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAutomationControllerReportGenerated, const FString&);` — Delegate for receiving a test report upon test pass completion.
- L156 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAutomationControllerReportGenerated, const FString&);` — Delegate for receiving a test report upon test pass completion.

### `Source/Developer/AutomationController/Public/IAutomationControllerModule.h` (Public)


#### struct `FAutomationResultEmitter`  
`struct FAutomationResultEmitter`  
_L21-28_
- desc: Emit test results in the format Gauntlet's AutomationLogParser expects. Shares the file-scoped format #defines with ReportAutomationResult in AutomationControllerManager.cpp. Both call sites use the same defines but are not yet consolidated into a single code path. TODO: Refactor ReportAutomationResult to call these functions, making them the single entry point for Gauntlet protocol emission.
- L23 _public prototype_ `static void EmitTestStarted(const FString& Name, const FString& Path);`
- L24 _public prototype_ `static void EmitTestCompleted(const FString& State, const FString& Name, const FString& Path);`
- L25 _public prototype_ `static void EmitBeginEvents(const FString& Path);`
- L26 _public prototype_ `static void EmitEndEvents(const FString& Path);`
- L27 _public prototype_ `static void EmitEntry(const FAutomationExecutionEntry& Entry);`

#### class `IAutomationControllerModule`  
`class IAutomationControllerModule : public IModuleInterface`  
_L33-55_
- inherits: `IModuleInterface`
- desc: Interface for AutomationController modules.
- L43 _public prototype_ `virtual IAutomationControllerManagerRef GetAutomationController( ) = 0;` — Gets the automation controller. @return a reference to the automation controller.
- L46 _public prototype_ `virtual void Init() = 0;` — Init message bus usage.
- L49 _public prototype_ `virtual void Tick() = 0;` — Tick function that will execute enabled tests for different device clusters.
- L51 _public function_ `static IAutomationControllerModule& Get()`

### `Source/Developer/AutomationController/Public/IAutomationReport.h` (Public)


#### enum `EAutomationArtifactType`  
`enum class EAutomationArtifactType : uint8`  
_L27-32_
- reflection: `UENUM()`
- L29 _public enumerator_ `None`
- L30 _public enumerator_ `Image`
- L31 _public enumerator_ `Comparison`

#### struct `FAutomationArtifact`  
`struct FAutomationArtifact`  
_L44-81_
- reflection: `USTRUCT()`
- L49 _public function_ `FAutomationArtifact() : Name() , Type(EAutomationArtifactType::None)`
- L55 _public function_ `FAutomationArtifact(FGuid InUniqueId, const FString& InName, EAutomationArtifactType InType, const TMap<FString, FString>& InLocalFiles) : Id(InUniqueId) , Name(InName) , Type(InType) , LocalFiles(InLocalFiles)`
- L66 _public member_ `FGuid Id;` — `UPROPERTY()`
- L69 _public member_ `FString Name;` — `UPROPERTY()`
- L72 _public member_ `EAutomationArtifactType Type;` — `UPROPERTY()`
- L75 _public member_ `TMap<FString, FString> Files;` — `UPROPERTY()`
- L80 _public member_ `TMap<FString, FString> LocalFiles;`

#### struct `FAutomationTestResults`  
`struct FAutomationTestResults`  
_L86-156_
- desc: A struct to maintain a collection of data which was reported as part of an automation test result.
- L91 _public function_ `FAutomationTestResults() : State( EAutomationState::NotRun )` — Default Constructor
- L99 _public function_ `void Reset()`
- L108 _public function_ `void SetEvents(const TArray<FAutomationExecutionEntry>& InEvents, int32 InWarningTotal, int32 InErrorTotal)`
- L115 _public function_ `void AddEvent(const FAutomationExecutionEntry& Event)`
- L130 _public function_ `const TArray<FAutomationExecutionEntry>& GetEntries() const`
- L132 _public function_ `int32 GetLogTotal() const`
- L133 _public function_ `int32 GetWarningTotal() const`
- L134 _public function_ `int32 GetErrorTotal() const`
- L138 _public member_ `EAutomationState State;` — The current state of this test
- L141 _public member_ `float Duration;` — The time this test took to complete
- L144 _public member_ `FString GameInstance;` — The instance which reported these results
- L147 _public member_ `TArray<FAutomationArtifact> Artifacts;` — Artifacts generated during the run of the test.
- L151 _private member_ `TArray<FAutomationExecutionEntry> Entries;` — All events reported as part of this test
- L153 _private member_ `int32 WarningTotal;`
- L155 _private member_ `int32 ErrorTotal;`

#### struct `FAutomationCompleteState`  
`struct FAutomationCompleteState`  
_L160-189_
- desc: Intermediate structure for calculating how complete a automation test is
- L162 _public function_ `FAutomationCompleteState() : NumEnabledTestsPassed(0) , NumEnabledTestsWarnings(0) , NumEnabledTestsFailed(0) , NumEnabledTestsCouldntBeRun(0) , NumEnabledInProcess(0) , TotalEnabled(0) , NumDisabledTestsPassed(0) , NumDisabledTestsWarnings(0) , NumDisabledTestsFailed(0) , NumDisabledTestsCouldntBeRun(0)`
- L177 _public member_ `uint32 NumEnabledTestsPassed;` — Stats for enabled tests
- L178 _public member_ `uint32 NumEnabledTestsWarnings;`
- L179 _public member_ `uint32 NumEnabledTestsFailed;`
- L180 _public member_ `uint32 NumEnabledTestsCouldntBeRun;`
- L181 _public member_ `uint32 NumEnabledInProcess;`
- L182 _public member_ `uint32 TotalEnabled;`
- L185 _public member_ `uint32 NumDisabledTestsPassed;` — stats for disabled tests
- L186 _public member_ `uint32 NumDisabledTestsWarnings;`
- L187 _public member_ `uint32 NumDisabledTestsFailed;`
- L188 _public member_ `uint32 NumDisabledTestsCouldntBeRun;`

#### class `IAutomationReport`  
`class IAutomationReport : public TSharedFromThis<IAutomationReport>`  
_L194-551_
- inherits: `TSharedFromThis<IAutomationReport>`
- desc: Interface for automation test results
- L198 _public prototype_ `virtual ~IAutomationReport() = default;` — virtual destructor
- L201 _public prototype_ `virtual void Empty() = 0;` — Remove all child tests
- L206 _public prototype_ `virtual FString GetCommand() const = 0;` — Returns the complete command for an automation test including any relevant parameters.  This is the class name + the parameter.
- L215 _public prototype_ `virtual const FString& GetDisplayName() const = 0;` — Returns the name of this level in the test hierarchy for the purposes of grouping. (Editor.Maps.LoadAll.parameters) would have 3 internal tree nodes and a variable number of leaf nodes depending on how many maps existed @param bAddDecoration true is the name should have the number of child tests appended. @return the name of this level in the hierarchy for use in UI.
- L220 _public prototype_ `virtual const FString& GetFullTestPath() const = 0;` — Returns the full path for the test, e.g. System.Audio.PlaySoundTest.
- L228 _public prototype_ `virtual FString GetDisplayNameWithDecoration() const = 0;` — Returns the name of this level in the test hierarchy for the purposes of UI. (Editor.Maps.LoadAll.parameters) would have 3 internal tree nodes and a variable number of leaf nodes depending on how many maps existed @return the name of this level in the hierarchy for use in UI.
- L235 _public prototype_ `virtual FString GetTestParameter() const = 0;` — Get the name of the asset associated with this test. @return the asset name.
- L242 _public prototype_ `virtual FString GetTags() const = 0;` — Get the tags associated with this test. @return the tags concatenated into a single string.
- L249 _public prototype_ `virtual TArray<FString> GetTagsArray() const = 0;` — Get the tags associated with this test, as an array. @return the tags as a string array.
- L256 _public prototype_ `virtual FString GetAssetPath() const = 0;` — Gets the asset path associated with a test, it may not have one. @return the asset name.
- L258 _public prototype_ `virtual FString GetOpenCommand() const = 0;`
- L265 _public prototype_ `virtual EAutomationTestFlags GetTestFlags() const = 0;` — Get the test type. @return the test type.
- L268 _public prototype_ `virtual FString GetSourceFile() const = 0;` — Gets the source file the test was defined on.
- L271 _public prototype_ `virtual int32 GetSourceFileLine() const = 0;` — Gets the source file line number the test was defined on.
- L274 _public prototype_ `virtual int32 GetTotalNumChildren() const = 0;` — Recursively gets the number of child nodes
- L277 _public prototype_ `virtual int32 GetTotalNumFilteredChildren() const = 0;` — Recursively gets the total number of filtered children
- L280 _public prototype_ `virtual void GetEnabledTestNames(TArray<FString>& OutEnabledTestNames, FString CurrentPath) const = 0;` — Gets the names of all the enabled tests
- L283 _public prototype_ `virtual void GetFilteredTestNames(TArray<FString>& OutFilteredTestNames, FString CurrentPath) const = 0;` — Gets the names of all the filtered tests
- L286 _public prototype_ `virtual void SetEnabledTests(const TArray<FString>& EnabledTests, FString CurrentPath) = 0;` — Sets which tests are enabled based off the enabled tests list
- L289 _public prototype_ `virtual int32 GetEnabledTestsNum() const = 0;` — Recursively gets the number of enabled tests
- L292 _public prototype_ `virtual bool IsEnabled() const = 0;` — Return if this test should be executed
- L299 _public prototype_ `virtual const bool IsParent() = 0;` — Is this a parent type. @return true if this is a parent type.
- L306 _public prototype_ `virtual const bool IsSmokeTest() = 0;` — Is this a smoke test. @return true if this is a smoke test.
- L309 _public prototype_ `virtual void SetEnabled(bool bShouldBeEnabled) = 0;` — Sets whether this test should be executed or not.
- L312 _public prototype_ `virtual void SetSupport(const int32 ClusterIndex) = 0;` — Sets whether this test is supported on a particular platform.
- L319 _public prototype_ `virtual void SetTestFlags(const EAutomationTestFlags InTestFlags) = 0;` — Set the test flags. @param InTestFlags The EAutomationTestFlags of the test.
- L322 _public prototype_ `virtual bool IsSupported(const int32 ClusterIndex) const = 0;` — Returns if a particular platform is supported
- L331 _public prototype_ `virtual bool SetFilter( TSharedPtr< AutomationFilterCollection > InFilter, const bool ParentPassedFilter = false ) = 0;` — Filters the visible tests based on search text, execution status, regression test, etc. @param InFilterDesc The description of how to decide if this report should be visible. @param ParentPassedFilter If the parent passed the filter. @return whether this report or any of its children passed the filter.
- L334 _public prototype_ `virtual TArray<TSharedPtr<IAutomationReport> >& GetFilteredChildren() = 0;` — Returns the array of child reports that should be visible to the UI based on filtering.
- L337 _public prototype_ `virtual TArray<TSharedPtr<IAutomationReport> >& GetChildReports() = 0;` — Returns the array of child reports.
- L340 _public prototype_ `virtual void ClustersUpdated(const int32 NumClusters) = 0;` — Updates the report when the number of clusters changes.
- L347 _public prototype_ `virtual void ResetForExecution(const int32 NumTestPasses) = 0;` — Recursively resets the report to "needs to be run", clears cached warnings and errors. @param NumTestPasses The number of test passes so we know how many results to create.
- L356 _public prototype_ `virtual void SetResults(const int32 ClusterIndex, const int32 PassIndex, const FAutomationTestResults& InResults) = 0;` — Sets the results of the test for use by the UI. @param ClusterIndex Index of the platform reporting the results of this test.  See AutomationDeviceClusterManager. @param PassIndex Which test pass these results are for. @param InResults The new set of results.
- L358 _public prototype_ `virtual void AddArtifact(const int32 ClusterIndex, const int32 PassIndex, const FAutomationArtifact& Artifact) = 0;`
- L367 _public prototype_ `virtual void GetCompletionStatus(const int32 ClusterIndex, const int32 PassIndex, FAutomationCompleteState& OutCompletionState) = 0;` — Returns completion statistics for this branch of the testing hierarchy. @param ClusterIndex Index of the platform reporting the results of this test.  See AutomationDeviceClusterManager. @param PassIndex Which test pass to get the status of. @param OutCompletionState Collection structure for execution statistics.
- L376 _public prototype_ `virtual EAutomationState GetState(const int32 ClusterIndex, const int32 PassIndex) const = 0;` — Returns the state of the test (not run, in process, success, failure). @param ClusterIndex Index of the platform reporting the results of this test.  See AutomationDeviceClusterManager. @param PassIndex Which test pass to get the state of. @return the current state of the test.
- L383 _public prototype_ `virtual void SetState(const EAutomationState State) = 0;` — Set the state of the test (not run, in process, success, failure). @param State EAutomationState state to set.
- L392 _public prototype_ `virtual const FAutomationTestResults& GetResults( const int32 ClusterIndex, const int32 PassIndex ) = 0;` — Gets a copy of errors and warnings that were found @param ClusterIndex Index of the platform we are requesting test results for. @param PassIndex Index of the test pass to get the results for. @return The collection of results for the given cluster index
- L400 _public prototype_ `virtual const int32 GetNumResults( const int32 ClusterIndex ) = 0;` — Gets the number of available test results for a given cluster. @param ClusterIndex Index of the platform. @return The number of results available for this cluster
- L407 _public prototype_ `virtual const int32 GetCurrentPassIndex( const int32 ClusterIndex ) = 0;` — Finds the current pass by looking at the current state @param ClusterIndex - Index of the platform. @return The current pass index
- L415 _public prototype_ `virtual FString GetGameInstanceName(const int32 ClusterIndex) = 0;` — Gets the name of the instance that ran the test. @param ClusterIndex - Index of the platform reporting the results of this test.  See AutomationDeviceClusterManager. @return the name of the device.
- L426 _public prototype_ `virtual TSharedPtr<IAutomationReport> EnsureReportExists(FAutomationTestInfo& TestInfo, const int32 ClusterIndex, const int32 NumPasses) = 0;` — Add a child test to the hierarchy, creating internal tree nodes as needed. If NewTestName is Editor.Maps.Loadall.TestName, this will create nodes for Editor, Maps, Loadall, and then a leaf node for the test name with the associated command line @param TestInfo Structure containing all the test info. @param ClusterIndex Index of the platform reporting the results of this test.  See AutomationDeviceClusterManager. @param NumPasses The number of passes we are going to perform.  Used to make sure we have enough results.. @return The automation report.
- L437 _public prototype_ `virtual TSharedPtr<IAutomationReport> GetNextReportToExecute(bool& bOutAllTestsComplete, const int32 ClusterIndex, const int32 PassIndex, const int32 NumDevicesInCluster) = 0;` — Returns the next test in the hierarchy to run. @param bOutAllTestsComplete Whether or not all enabled tests have completed execution for this platform (cluster index). @param ClusterIndex Index of the platform reporting the results of this test.  See AutomationDeviceClusterManager. @param PassIndex Which test pass we are currently on. @param NumDevicesInCluster The number of devices which are in this cluster. @return The next report
- L444 _public prototype_ `virtual void GetEnabledTestReports(TArray<TSharedPtr<IAutomationReport>>& OutReports) = 0;` — Returns all the enabled test reports. @param an array to be filled with all reports
- L451 _public prototype_ `virtual const bool HasErrors() = 0;` — Returns if there have been any errors in the test. @return True If there were errors.
- L458 _public prototype_ `virtual const bool HasWarnings() = 0;` — Returns if there have been any warnings in the test. @return True If there were errors.
- L467 _public prototype_ `virtual const bool GetDurationRange(float& OutMinTime, float& OutMaxTime) = 0;` — Gets the min and max time this test took to execute. @param OutMinTime Minimum execution time for all device types. @param OutMaxTime Maximum execution time for all device types. @return whether any test has completed successfully.
- L474 _public prototype_ `virtual const int32 GetNumDevicesRunningTest() const = 0;` — Get the number of devices which have been given this test to run. @return The number of devices who have been given this test to run.
- L481 _public prototype_ `virtual const int32 GetNumParticipantsRequired() const = 0;` — Get the number of participants this test requires. @Return The number of devices needed for this test to execute.
- L488 _public prototype_ `virtual void SetNumParticipantsRequired( const int32 NewCount ) = 0;` — Set the number of participants this test requires if less than what is already set. @param NewCount The number of further devices .
- L495 _public prototype_ `virtual bool IncrementNetworkCommandResponses() = 0;` — Increment the number of network responses. @return true if responses from all participants were received, false otherwise.
- L498 _public prototype_ `virtual void ResetNetworkCommandResponses() = 0;` — Resets the number of network responses back to zero.
- L505 _public prototype_ `virtual const bool ExpandInUI() const = 0;` — Should we expand this node in the UI - A child has passed the filter. @return true If we should expand the node
- L508 _public prototype_ `virtual void StopRunningTest() = 0;` — Stop the test which is creating this report.
- L517 _public prototype_ `virtual bool IsToBeSkipped(FName* OutReason = nullptr, bool* OutWarn = nullptr) const = 0;` — Is the test need to be skipped. @param OutReasaon the related reason of the exclusion information @param OutWarn the related warning of the exclusion @return true if the test is inside exclude list.
- L524 _public prototype_ `virtual bool IsToBeSkippedOnConditions() const = 0;` — Is the test need to be skipped on specific conditions. @return true if the test is inside exclude list.
- L531 _public prototype_ `virtual bool IsToBeSkippedByPropagation() const = 0;` — Is the test is to be skipped through propagation. @return true if the test is inside exclude list via a propagation.
- L538 _public prototype_ `virtual void SetSkipFlag(bool bEnableSkip, const FAutomationTestExcludelistEntry* Template = nullptr, bool bFromPropagation = false) = 0;` — Add or remove test from exclude list. @param if true, add this item to the exclude list, remove otherwise.
- L545 _public prototype_ `virtual TSharedPtr<FAutomationTestExcludeOptions> GetExcludeOptions() = 0;` — Produce exclude options . @return exclude options based on report exclude info.
- L549 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnSetResultsEvent, TSharedPtr<IAutomationReport>);` — Event that allows log to refresh once a test has finished
- L550 _public member_ `FOnSetResultsEvent OnSetResults;`

#### Free symbols / members of external scopes

- L18 _typedef_ `typedef TFilterCollection< const TSharedPtr< class IAutomationReport >& > AutomationFilterCollection;` — The automation filter collection - used for updating the automation report list
- L21 _typedef_ `typedef TSharedPtr<class IAutomationReport> IAutomationReportPtr;`
- L23 _typedef_ `typedef TSharedRef<class IAutomationReport> IAutomationReportRef;`
- L34 _namespace_ `namespace ComparisonFileTypes`
- L38 _variable_ `const FString Unapproved = TEXT("una` (scope `ComparisonFileTypes`) — Use const string here instead of an enum, because FAutomationArtifact.Files property is a dictionary string/string FAutomationArtifact should be able to be used as an adhoc key/file association.
- L39 _variable_ `const FString Approved = TEXT("app` (scope `ComparisonFileTypes`)
- L40 _variable_ `const FString Difference = TEXT("dif` (scope `ComparisonFileTypes`)
- L549 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSetResultsEvent, TSharedPtr<IAutomationReport>);` — Event that allows log to refresh once a test has finished
