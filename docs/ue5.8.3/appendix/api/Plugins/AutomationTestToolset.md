# Plugins / AutomationTestToolset

- module root: `Plugins/Experimental/Toolsets/AutomationTestToolset/Source/AutomationTestToolset`
- headers: 3; symbols: 46
- symbol kinds: class=3, function=4, member=16, prototype=23
- PrivateDependencyModuleNames: AutomationController, AutomationTest, Core, CoreUObject, EditorSubsystem, Engine, Json, SessionServices, UnrealEd
- PublicDependencyModuleNames: ToolsetRegistry

### `Plugins/Experimental/Toolsets/AutomationTestToolset/Source/AutomationTestToolset/Public/AutomationTestToolset.h` (Public)


#### class `UAutomationTestToolset`  
`class UAutomationTestToolset : public UToolsetDefinition`  
_L26-93_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UToolsetDefinition`
- desc: Automation test discovery and execution toolset. Wraps the IAutomationControllerManager API (the same backend the Session Frontend uses) to let MCP clients list available tests, run them, and retrieve results. Typical workflow: 1. DiscoverTests() once per session to initialize workers and load the test list. 2. ListTests() to find tests by name or tag. 3. RunTests() with the desired test names. 4. GetTestStatus() / GetTestResults() to monitor and retrieve results. 5. StopTests() to abort if needed.
- L40 _public prototype_ `static UToolCallAsyncResultString* DiscoverTests(bool bForceRediscover = false);` — `UFUNCTION(meta = (AICallable), Category = "AutomationTestToolset")` — Initialize automation worker discovery and load the test list. Must be called once before ListTests or RunTests. Takes several seconds as it discovers the local automation worker and enumerates all registered tests. Returns an async result that completes with a JSON status object when tests are available, or an error if discovery fails. @param bForceRediscover  When true, bypass the cached report tree and re-poll workers. Used after reloading Python test modules mid-session.
- L48 _public prototype_ `static FString ListTests(const FString& NameFilter = TEXT(""), const FString& TagFilter = TEXT(""), int32 Limit = 200);` — `UFUNCTION(meta = (AICallable), Category = "AutomationTestToolset")` — List available automation tests. Requires DiscoverTests() to have completed. Returns a JSON object: {"tests": ["path1", ...], "total": N, "returned": N}. @param NameFilter  Optional substring filter applied to the test's full path. @param TagFilter   Optional substring filter applied to the test's tags. @param Limit       Maximum number of tests to return (0 = unlimited, default 200).
- L55 _public prototype_ `static UToolCallAsyncResultString* RunTests(const TArray<FString>& TestNames);` — `UFUNCTION(meta = (AICallable), Category = "AutomationTestToolset")` — Run a set of automation tests by name. Requires DiscoverTests() to have completed. Starts executing the specified tests and returns an async result that completes with a JSON summary when all tests finish. @param TestNames  Array of full test paths as returned by ListTests.
- L73 _public prototype_ `static UToolCallAsyncResultString* RunTestsByFilter(const FString& FilterExpression);` — `UFUNCTION(meta = (AICallable), Category = "AutomationTestToolset")` — Run automation tests selected by a filter expression. Requires DiscoverTests() to have completed. Much faster than RunTests when targeting a large batch because the engine narrows the report tree in a single pass instead of running a per-leaf membership check against the requested name list. Filter syntax (multiple expressions joined by '+'): "StartsWith:System.Engine"  prefix match against the full test path "^Foo"                       prefix anchor (equivalent to StartsWith:) "Bar$"                       suffix anchor "Substring"                  bare token matches anywhere in the path "Group:Smoke"                expand a named group from AutomationControllerSettings ini Groups Returns an async result that completes with the same JSON summary as RunTests. @param FilterExpression  Filter expression as described above.
- L79 _public prototype_ `static FString GetTestResults();` — `UFUNCTION(meta = (AICallable), Category = "AutomationTestToolset")` — Get detailed results for the current or most recent test run. Requires DiscoverTests() to have completed. Returns a JSON object with per-test state, duration, errors, and warnings.
- L86 _public prototype_ `static FString GetTestStatus();` — `UFUNCTION(meta = (AICallable), Category = "AutomationTestToolset")` — Get a lightweight status snapshot of the automation controller. Requires DiscoverTests() to have completed. Returns a JSON object with the controller state, enabled test count, and completion/pass/fail counts.
- L92 _public prototype_ `static bool StopTests();` — `UFUNCTION(meta = (AICallable), Category = "AutomationTestToolset")` — Stop all currently running tests. Requires DiscoverTests() to have completed. If a RunTests async result is pending, it will be completed with an error. @return True if the stop request was issued successfully.

### `Plugins/Experimental/Toolsets/AutomationTestToolset/Source/AutomationTestToolset/Public/AutomationTestToolsetModule.h` (Public)


#### class `FAutomationTestToolsetModule`  
`class FAutomationTestToolsetModule : public IModuleInterface`  
_L7-14_
- inherits: `IModuleInterface`
- L11 _public prototype_ `virtual void StartupModule() override;`
- L13 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/Toolsets/AutomationTestToolset/Source/AutomationTestToolset/Public/AutomationTestToolsetSubsystem.h` (Public)


#### class `UAutomationTestToolsetSubsystem`  
`class UAutomationTestToolsetSubsystem : public UEditorSubsystem`  
_L22-114_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorSubsystem`
- desc: Manages the automation controller lifecycle for the AutomationTestToolset. Handles session discovery, worker communication, and test execution polling. The toolset's static tool functions delegate to this subsystem for state management.
- L28 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L30 _public prototype_ `virtual void Deinitialize() override;`
- L33 _public prototype_ `void SetToolsetEnabled(bool bEnabled);` — Register or unregister the toolset with UToolsetRegistry at runtime.
- L36 _public function_ `IAutomationControllerManagerPtr GetAutomationController() const` — Get the automation controller.
- L39 _public function_ `bool IsControllerReady() const` — Whether workers have been found and the test list is populated.
- L43 _public prototype_ `void RequestWorkerDiscovery();` — Load SessionServices and begin polling for the local session. Once found, requests available automation workers.
- L46 _public prototype_ `void SetPendingDiscoveryResult(UToolCallAsyncResultString* InResult);` — Store a pending async result that will resolve when test discovery completes.
- L50 _public prototype_ `void SetPendingRunResult(UToolCallAsyncResultString* InResult, const TArray<FString>& InTestNames);` — Store a pending async result for the current test run. Resolves with results JSON when tests finish.
- L53 _public prototype_ `UToolCallAsyncResultString* GetPendingRunResult() const;` — Get the pending run result, if any.
- L56 _public prototype_ `void EnableRunResultPolling();` — Start polling for test completion. Call after RunTests() has started execution.
- L62 _public function_ `void SetRestoreFilterOnComplete(bool bRestore)` — Mark that the controller filter should be reset to empty and visible tests re-enabled when the current run completes. RunTestsByFilter narrows the report tree via SetFilter; this widens it back so subsequent ListTests and DiscoverTests calls see the full test set.
- L65 _public function_ `const TSet<FString>& GetRunningTestNames() const` — Get the test names from the current or most recent run.
- L68 _public prototype_ `static FString FormatResultsJson(const IAutomationControllerManagerPtr& Controller, const TSet<FString>& TestNames);` — Build a JSON results string for the given test names from the controller's report tree.
- L71 _public prototype_ `static void CollectLeafReports(const TArray<TSharedPtr<IAutomationReport>>& Reports, TArray<TSharedPtr<IAutomationReport>>& OutLeaves);` — Recursively collect leaf (runnable) reports from a report tree.
- L75 _private member_ `static constexpr float DiscoveryTimeoutSeconds = 60.0f;`
- L77 _private prototype_ `bool OnTick(float DeltaTime);`
- L79 _private prototype_ `void HandleTestsAvailable(EAutomationControllerModuleState::Type State);`
- L81 _private prototype_ `void HandleTestsRefreshed();`
- L83 _private prototype_ `void CompleteTestRun();`
- L85 _private member_ `TSharedPtr<ISessionManager> SessionManager;`
- L87 _private member_ `IAutomationControllerManagerPtr AutomationController;`
- L89 _private member_ `TStrongObjectPtr<UToolCallAsyncResultString> PendingDiscoveryResult;`
- L91 _private member_ `TStrongObjectPtr<UToolCallAsyncResultString> PendingRunResult;`
- L93 _private member_ `TSet<FString> RunningTestNames;`
- L95 _private member_ `FTSTicker::FDelegateHandle TickerHandle;`
- L97 _private member_ `FDelegateHandle TestsAvailableHandle;`
- L99 _private member_ `FDelegateHandle TestsRefreshedHandle;`
- L101 _private member_ `float DiscoveryElapsedSeconds = 0.0f;`
- L103 _private member_ `bool bToolsetRegistered = false;`
- L105 _private member_ `bool bControllerReady = false;`
- L107 _private member_ `bool bDiscoveryRequested = false;`
- L109 _private member_ `bool bWorkersRequested = false;`
- L111 _private member_ `bool bWaitingForResults = false;`
- L113 _private member_ `bool bRestoreFilterOnComplete = false;`
