# Plugins / FastbuildController

- module root: `Plugins/FastBuildController/Source`
- headers: 3; symbols: 93
- symbol kinds: class=5, enum=1, enumerator=8, function=17, member=29, prototype=33
- PrivateDependencyModuleNames: Core, RenderCore
- PrivateIncludePathModuleNames: DistributedBuildInterface, TargetPlatform

### `Plugins/FastBuildController/Source/Public/FastBuildControllerModule.h` (Public)


#### class `FFastBuildControllerModule`  
`class FFastBuildControllerModule : public IDistributedBuildController`  
_L11-109_
- inherits: `IDistributedBuildController`
- L13 _private member_ `bool bSupported;`
- L14 _private member_ `bool bModuleInitialized;`
- L15 _private member_ `bool bControllerInitialized;`
- L17 _private member_ `FThreadSafeCounter NextFileID;`
- L18 _private member_ `FThreadSafeCounter NextTaskID;`
- L20 _private member_ `FThreadSafeCounter PendingTasksCounter;`
- L23 _private member_ `TUniquePtr<FFastBuildJobProcessor> JobDispatcherThread;` — The thread spawned for shader compiling.
- L26 _private member_ `TSharedPtr<FCriticalSection> TasksCS;` — Taken when accessing the PendingTasks and DispatchedTasks members.
- L29 _private member_ `TQueue<FDistributedBuildTask*> PendingTasks;` — Queue of tasks submitted by the engine, but not yet dispatched to the controller.
- L32 _private member_ `TMap<uint32, FDistributedBuildTask*> DispatchedTasks;` — Map of tasks dispatched to the controller and running within FastBuild, that have not yet finished.
- L34 _private member_ `const FString RootWorkingDirectory;`
- L36 _private member_ `const FString WorkingDirectory;`
- L38 _private member_ `FString IntermediateShadersDirectory;`
- L40 _private member_ `bool bShutdown;`
- L42 _private prototype_ `void CleanWorkingDirectory();`
- L45 _public prototype_ `FFastBuildControllerModule();`
- L46 _public prototype_ `virtual ~FFastBuildControllerModule();`
- L48 _public prototype_ `virtual void StartupModule() override final;`
- L49 _public prototype_ `virtual void ShutdownModule() override final;`
- L51 _public function_ `virtual bool RequiresRelativePaths() override final`
- L53 _public prototype_ `virtual void InitializeController() override final;`
- L55 _public function_ `virtual const FString GetName() override final`
- L57 _public prototype_ `virtual FString RemapPath(const FString& SourcePath) const override final;`
- L59 _public prototype_ `virtual bool IsSupported() override final;`
- L61 _public prototype_ `virtual FString CreateUniqueFilePath() override final;`
- L62 _public prototype_ `virtual TFuture<FDistributedBuildTaskResult> EnqueueTask(const FTaskCommandData& CommandData) override final;`
- L64 _public prototype_ `void EnqueueTask(FDistributedBuildTask* Task);`
- L65 _public prototype_ `FDistributedBuildTask* DequeueTask();`
- L67 _public prototype_ `void RegisterDispatchedTask(FDistributedBuildTask* DispatchedTask);`
- L68 _public prototype_ `void ReEnqueueDispatchedTasks();`
- L69 _public prototype_ `void DeRegisterDispatchedTasks(const TArray<uint32>& InTasksID);`
- L70 _public prototype_ `void ReportJobProcessed(FDistributedBuildTask* CompletedTask, const FTaskResponse& InTaskResponse);`
- L72 _public prototype_ `static FFastBuildControllerModule& Get();`
- L74 _public function_ `inline bool AreTasksPending() const`
- L80 _public function_ `inline bool AreTasksDispatched() const`
- L86 _public function_ `inline bool AreTasksDispatchedOrPending() const`
- L92 _public function_ `int32 GetPendingTasksAmount() const`
- L94 _public function_ `FString GetRootWorkingDirectory() const`
- L96 _public function_ `FString GetWorkingDirectory() const`
- L98 _public function_ `FString GetIntermediateShadersDirectory() const`
- L100 _public function_ `const TMap<uint32, FDistributedBuildTask*>& GetDispatchedTasks() const`
- L105 _public function_ `FCriticalSection* GetTasksCS() const`

### `Plugins/FastBuildController/Source/Public/FastBuildJobProcessor.h` (Public)


#### enum `EFASTBuild_ReturnCodes`  
`enum EFASTBuild_ReturnCodes`  
_L15-25_
- L17 _public enumerator_ `FBUILD_OK = 0`
- L18 _public enumerator_ `FBUILD_BUILD_FAILED = -1`
- L19 _public enumerator_ `FBUILD_ERROR_LOADING_BFF = -2`
- L20 _public enumerator_ `FBUILD_BAD_ARGS = -3`
- L21 _public enumerator_ `FBUILD_ALREADY_RUNNING = -4`
- L22 _public enumerator_ `FBUILD_FAILED_TO_SPAWN_WRAPPER = -5`
- L23 _public enumerator_ `FBUILD_FAILED_TO_SPAWN_WRAPPER_FINAL = -6`
- L24 _public enumerator_ `FBUILD_WRAPPER_CRASHED = -7`

#### class `FFastBuildJobProcessor`  
`class FFastBuildJobProcessor : public FRunnable`  
_L26-75_
- inherits: `FRunnable`
- L30 _public prototype_ `FFastBuildJobProcessor(FFastBuildControllerModule& InControllerModule);`
- L31 _public prototype_ `virtual ~FFastBuildJobProcessor();`
- L34 _public prototype_ `virtual uint32 Run() override;` — Main loop
- L37 _public function_ `virtual void Stop() override` — Aborts the main loop as soon as possible
- L40 _public prototype_ `void StartThread();` — Creates the threads and starts the main loop
- L43 _public function_ `inline bool IsWorkDone() const` — Used to know when this thread has finished the main loop
- L48 _protected member_ `FRunnableThread* Thread;` — The runnable thread
- L50 _protected member_ `FProcHandle BuildProcessHandle;`
- L51 _protected member_ `uint32 BuildProcessID;`
- L52 _protected member_ `void* PipeRead = nullptr;`
- L53 _protected member_ `void* PipeWrite = nullptr;`
- L55 _protected member_ `uint32 LastTimeKickedOffJobs;`
- L57 _protected member_ `FFastBuildControllerModule& ControllerModule;`
- L60 _protected member_ `FThreadSafeBool bForceStop;` — Used to abort the current processing loop
- L63 _protected member_ `FThreadSafeBool bIsWorkDone;` — Set to true when the main loop finishes
- L65 _protected prototype_ `void WriteScriptFileToDisk(const TArray<FDistributedBuildTask*>& PendingTasks, const FString& ScriptFilename, const FString& WorkerName) const;`
- L68 _protected prototype_ `void SubmitPendingJobs();` — Takes all tasks from the queue and creates a FastBuild Script to the kick off the pending jobs
- L71 _protected prototype_ `void GatherBuildResults() const;` — Checks the file system to find any results form the submitted jobs
- L74 _protected prototype_ `void MonitorFastBuildProcess();` — Checks if the FastBuild process is still running properly and handles bad situations

### `Plugins/FastBuildController/Source/Public/FastBuildUtilities.h` (Public)


#### class `FDependencyEnumerator`  
`class FDependencyEnumerator : public IPlatformFile::FDirectoryVisitor`  
_L11-41_
- inherits: `IPlatformFile::FDirectoryVisitor`
- L14 _public function_ `FDependencyEnumerator(FArchive& InScriptFile, const TCHAR* InPrefix, const TCHAR* InExtension) : ScriptFile(InScriptFile) , Prefix(InPrefix) , Extension(InExtension)`
- L22 _public function_ `virtual bool Visit(const TCHAR* FilenameChar, bool bIsDirectory) override`
- L38 _public member_ `FArchive& ScriptFile;`
- L39 _public member_ `const TCHAR* Prefix;`
- L40 _public member_ `const TCHAR* Extension;`

#### class `FDependencyUniqueArrayEnumerator`  
`class FDependencyUniqueArrayEnumerator : public IPlatformFile::FDirectoryVisitor`  
_L43-71_
- inherits: `IPlatformFile::FDirectoryVisitor`
- L46 _public function_ `FDependencyUniqueArrayEnumerator(TArray<FString>& InFullUniqueDependenciesArray, const TCHAR* InPrefix, const TCHAR* InExtension) : FullUniqueDependenciesArray(InFullUniqueDependenciesArray) , Prefix(InPrefix) , Extension(InExtension)`
- L53 _public function_ `virtual bool Visit(const TCHAR* FilenameChar, bool bIsDirectory) override`
- L68 _public member_ `TArray<FString>& FullUniqueDependenciesArray;`
- L69 _public member_ `const TCHAR* Prefix;`
- L70 _public member_ `const TCHAR* Extension;`

#### class `FastBuildUtilities`  
`class FastBuildUtilities`  
_L73-88_
- L77 _public prototype_ `static void FASTBuildWriteScriptFileHeader(const TArray<FDistributedBuildTask*>& InCompilationTasks, FArchive& ScriptFile, const FString& WorkerName);`
- L78 _public prototype_ `static FArchive* CreateFileHelper(const FString& InFileName);`
- L80 _public prototype_ `static FString GetFastBuildExecutablePath();`
- L81 _public prototype_ `static FString GetFastBuildCache();`
- L84 _protected prototype_ `static void WriteShaderWorkerDependenciesToFile(FArchive& ScriptFile);`
- L85 _protected prototype_ `static FString ReplaceEnvironmentVariablesInPath(const FString& ExtraFilePartialPath);`
- L86 _protected prototype_ `static void WriteDependenciesToFileUsingWildcardPath(FArchive& ScriptFile, FString ParsedPath);`
- L87 _protected prototype_ `static void WritePlatformCompilerDependenciesToFile(FArchive& ScriptFile);`
