# Plugins / UbaController

- module root: `Plugins/UbaController/Source`
- headers: 3; symbols: 76
- symbol kinds: class=2, delegate=1, function=7, macro=2, member=30, prototype=32, typedef=2
- PrivateDependencyModuleNames: Core, DistributedBuildInterface, HTTP, Horde, Json, Projects, RenderCore, Sockets, TargetPlatform, UbaCoordinatorHorde

### `Plugins/UbaController/Source/Private/UbaStringConversion.h` (Private)


#### Free symbols / members of external scopes

- L8 _typedef_ `using FStringToUbaStringConversion = TStringConversion<TStringConvert<TCHAR, uba::tchar>>;`
- L9 _typedef_ `using FUbaStringToStringConversion = TStringConversion<TStringConvert<uba::tchar, TCHAR>>;`
- L11 _macro_ `#define TCHAR_TO_UBASTRING(STR) FStringToUbaStringConversion(STR).Get()`
- L12 _macro_ `#define UBASTRING_TO_TCHAR(STR) FUbaStringToStringConversion(STR).Get()`

### `Plugins/UbaController/Source/Public/UbaControllerModule.h` (Public)


#### class `FUbaControllerModule`  
`class FUbaControllerModule : public IDistributedBuildController , public TSharedFromThis<FUbaControllerModule>`  
_L12-77_
- inherits: `IDistributedBuildController,TSharedFromThis<FUbaControllerModule>`
- L16 _public prototype_ `FUbaControllerModule();`
- L19 _public prototype_ `static FUbaControllerModule& Get();`
- L20 _public prototype_ `virtual bool IsSupported() override final;`
- L22 _public function_ `virtual const FString GetName() override final`
- L24 _public prototype_ `virtual void StartupModule() override final;`
- L25 _public prototype_ `virtual void ShutdownModule() override final;`
- L26 _public prototype_ `virtual void InitializeController() override final;`
- L27 _public prototype_ `virtual bool SupportsLocalWorkers() override final;`
- L28 _public prototype_ `virtual FString CreateUniqueFilePath() override final;`
- L29 _public prototype_ `virtual bool SupportsVirtualFiles() const override final;`
- L30 _public prototype_ `virtual TFuture<FDistributedBuildTaskResult> EnqueueTask(const FTaskCommandData& CommandData) override final;`
- L31 _public prototype_ `virtual bool PollStats(FDistributedBuildStats& OutStats) override final;`
- L33 _public prototype_ `void CleanWorkingDirectory() const;`
- L35 _public function_ `const FString& GetRootWorkingDirectory() const`
- L36 _public function_ `const FString& GetWorkingDirectory() const`
- L37 _public function_ `const FString& GetDebugInfoPath() const`
- L40 _public member_ `TQueue<FDistributedBuildTask*, EQueueMode::Spsc> PendingRequestedCompilationTasks;` — Queue of tasks submitted by the engine, but not yet dispatched to the controller.
- L41 _public member_ `std::atomic<uint32> PendingRequestedCompilationCount;`
- L44 _public member_ `FEventRef ProcessorWakeEvent;` — Event used to wake the FUbaJobProcessor instance when new tasks are available or a shutdown is requested (the instance will block on this event when out of work)
- L46 _public function_ `virtual void SetMaxLocalWorkers(int32 InMaxNumLocalWorkers) override final`
- L51 _public function_ `inline int32 GetMaxNumLocalWorkers() const`
- L56 _public prototype_ `static FString GetTempDir();`
- L59 _private prototype_ `void LoadDependencies();`
- L61 _private prototype_ `void StartDispatcherThread();`
- L62 _private prototype_ `void StopAndWaitForDispatcherThread();`
- L64 _private member_ `bool bSupported;`
- L65 _private member_ `bool bModuleInitialized;`
- L66 _private member_ `bool bControllerInitialized;`
- L68 _private member_ `FString RootWorkingDirectory;`
- L69 _private member_ `FString WorkingDirectory;`
- L70 _private member_ `FString DebugInfoPath;`
- L72 _private member_ `TAtomic<int32> NextFileID;`
- L73 _private member_ `TAtomic<int32> NextTaskID;`
- L74 _private member_ `TAtomic<int32> MaxNumLocalWorkers = -1;`
- L76 _private member_ `TUniquePtr<FUbaJobProcessor> JobDispatcherThread;`

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogUbaController, Log, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogUbaController, Log, All);`

### `Plugins/UbaController/Source/Public/UbaJobProcessor.h` (Public)


#### class `FUbaJobProcessor`  
`class FUbaJobProcessor : public FRunnable, public TSharedFromThis<FUbaJobProcessor>`  
_L15-86_
- inherits: `FRunnable,TSharedFromThis<FUbaJobProcessor>`
- L18 _public prototype_ `FUbaJobProcessor(FUbaControllerModule& InControllerModule);`
- L23 _public prototype_ `virtual uint32 Run() override;` — Main loop
- L26 _public prototype_ `virtual void Stop() override;` — Aborts the main loop as soon as possible
- L29 _public prototype_ `bool IsUsingVirtualFiles() const;` — Indicates whether the job processor instance is using the UBA virtual file mechanism
- L32 _public prototype_ `void StartThread();` — Creates the threads and starts the main loop
- L33 _public prototype_ `void HandleUbaJobFinished(FDistributedBuildTask* CompileTask, TArray<uint8>&& OutputFileData, uint32 ExitCode);`
- L36 _public function_ `bool IsWorkDone() const` — Used to know when this thread has finished the main loop
- L38 _public prototype_ `bool HasJobsInFlight() const;`
- L40 _public prototype_ `bool PollStats(FDistributedBuildStats& OutStats);`
- L44 _private prototype_ `void UpdateMaxLocalParallelJobs();`
- L45 _private prototype_ `void CalculateKnownInputs();`
- L46 _private prototype_ `void RunTaskWithUba(FDistributedBuildTask* Task);`
- L48 _private prototype_ `void StartUba();`
- L49 _private prototype_ `void ShutDownUba();`
- L51 _private prototype_ `void UpdateStats();`
- L53 _private prototype_ `void SaveSnapshotOfTrace();`
- L56 _private member_ `FRunnableThread* Thread = nullptr;` — The runnable thread
- L58 _private member_ `FUbaControllerModule& ControllerModule;`
- L60 _private member_ `int32 MaxLocalParallelJobs = 0;`
- L63 _private member_ `TAtomic<bool> bForceStop;` — Used to abort the current processing loop
- L66 _private member_ `uint32 LastTimeCheckedForTasks = 0;` — Used to abort the current processing loop
- L69 _private member_ `bool bIsWorkDone = false;` — Set to true when the main loop finishes
- L71 _private member_ `FString TraceOutputFilename;`
- L73 _private member_ `uba::NetworkServer* UbaServer = nullptr;`
- L74 _private member_ `uba::StorageServer* UbaStorageServer = nullptr;`
- L75 _private member_ `uba::SessionServer* UbaSessionServer = nullptr;`
- L76 _private member_ `uba::Scheduler* UbaScheduler = nullptr;`
- L77 _private member_ `TUniquePtr<FUbaHordeAgentManager> HordeAgentManager;`
- L79 _private member_ `uint32 KnownInputsCount = 0;`
- L80 _private member_ `TArray<uba::tchar> KnownInputsBuffer;`
- L82 _private member_ `uba::CallbackLogWriter LogWriter;`
- L84 _private member_ `FCriticalSection StatsLock;`
- L85 _private member_ `FDistributedBuildStats Stats;`
