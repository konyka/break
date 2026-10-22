# Plugins / XGEController

- module root: `Plugins/XGEController/Source`
- headers: 1; symbols: 39
- symbol kinds: class=1, function=3, member=22, prototype=13
- PrivateDependencyModuleNames: Core, Engine, RHI, RenderCore, Slate
- PrivateIncludePathModuleNames: DistributedBuildInterface

### `Plugins/XGEController/Source/Public/XGEControllerModule.h` (Public)


#### class `FXGEControllerModule`  
`class FXGEControllerModule : public IDistributedBuildController`  
_L8-85_
- inherits: `IDistributedBuildController`
- L11 _private member_ `bool bSupported;` — Whether this system can use XGE shader compilation.
- L13 _private member_ `bool bModuleInitialized;` — Whether the module was initialized.
- L15 _private member_ `bool bControllerInitialized;` — Whether the controller was successfully initialized. This is only possible when bSupported is true.
- L17 _private member_ `FThreadSafeCounter NextFileID;`
- L18 _private member_ `FThreadSafeCounter NextTaskID;`
- L20 _private member_ `FProcHandle BuildProcessHandle;`
- L22 _private member_ `const FString ControlWorkerDirectory;`
- L23 _private member_ `const FString RootWorkingDirectory;`
- L24 _private member_ `const FString WorkingDirectory;`
- L25 _private member_ `const FString PipeName;`
- L26 _private member_ `FString XGConsolePath;`
- L29 _private member_ `FCriticalSection* TasksCS;` — Taken when accessing the PendingTasks and DispatchedTasks members.
- L32 _private member_ `TQueue<FDistributedBuildTask*> PendingTasks;` — Queue of tasks submitted by the engine, but not yet dispatched to the controller.
- L35 _private member_ `TMap<uint32, FDistributedBuildTask*> DispatchedTasks;` — Map of tasks dispatched to the controller and running within XGE, that have not yet finished.
- L37 _private member_ `bool bShutdown;`
- L38 _private member_ `bool bRestartWorker;`
- L39 _private member_ `TFuture<void> WriteOutThreadFuture;`
- L40 _private member_ `TFuture<void> ReadBackThreadFuture;`
- L43 _private member_ `FEventRef WriteOutThreadEvent;` — event for the thread that communicates with the XGE controller
- L46 _private member_ `FPlatformNamedPipe InputNamedPipe, OutputNamedPipe;` — We need two pipes, as the named pipe API does not support simultaneous read/write on two threads.
- L46 _private member_ `FPlatformNamedPipe InputNamedPipe, OutputNamedPipe;` — We need two pipes, as the named pipe API does not support simultaneous read/write on two threads.
- L48 _private member_ `volatile uint32 LastEventTime;`
- L50 _private function_ `inline bool AreTasksPending()`
- L56 _private function_ `inline bool AreTasksDispatchedOrPending()`
- L63 _public prototype_ `FXGEControllerModule();`
- L64 _public prototype_ `virtual ~FXGEControllerModule();`
- L66 _public prototype_ `virtual void StartupModule() override final;`
- L67 _public prototype_ `virtual void ShutdownModule() override final;`
- L69 _public prototype_ `virtual void InitializeController() override final;`
- L70 _public prototype_ `virtual bool SupportsLocalWorkers() override final;`
- L72 _public function_ `virtual const FString GetName() override final`
- L74 _public prototype_ `virtual bool IsSupported() override final;`
- L76 _public prototype_ `virtual FString CreateUniqueFilePath() override final;`
- L77 _public prototype_ `virtual TFuture<FDistributedBuildTaskResult> EnqueueTask(const FTaskCommandData& CommandData) override final;`
- L79 _public prototype_ `static FXGEControllerModule& Get();`
- L81 _public prototype_ `void WriteOutThreadProc();`
- L82 _public prototype_ `void ReadBackThreadProc();`
- L84 _public prototype_ `void CleanWorkingDirectory();`
