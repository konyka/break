# Plugins / DisplayClusterFillDerivedDataCache

- module root: `Plugins/Runtime/nDisplay/Source/DisplayClusterFillDerivedDataCache`
- headers: 3; symbols: 37
- symbol kinds: class=2, delegate=1, function=4, member=14, prototype=16
- PrivateDependencyModuleNames: AssetRegistry, AssetTools, ContentBrowser, CoreUObject, EditorStyle, EditorWidgets, Engine, InputCore, Kismet, Messaging, Networking, Projects, PropertyEditor, Slate, SlateCore, ToolMenus, ToolWidgets, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: Core, OutputLog, UnrealEd

### `Plugins/Runtime/nDisplay/Source/DisplayClusterFillDerivedDataCache/Public/DisplayClusterFillDerivedDataCacheLog.h` (Public)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_CLASS(LogDisplayClusterFillDerivedDataCache, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_CLASS(LogDisplayClusterFillDerivedDataCache, Log, All);`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterFillDerivedDataCache/Public/DisplayClusterFillDerivedDataCacheModule.h` (Public)


#### class `FDisplayClusterFillDerivedDataCacheModule`  
`class FDisplayClusterFillDerivedDataCacheModule : public IModuleInterface`  
_L8-27_
- inherits: `IModuleInterface`
- L12 _public prototype_ `static FDisplayClusterFillDerivedDataCacheModule& Get();`
- L15 _public prototype_ `virtual void StartupModule() override;`
- L16 _public prototype_ `virtual void ShutdownModule() override;`
- L21 _protected prototype_ `void CreateAsyncTaskWorker();`
- L22 _protected member_ `TUniquePtr<class FDisplayClusterFillDerivedDataCacheWorker> AsyncTaskWorker;`
- L26 _private prototype_ `void OnFEngineLoopInitComplete();`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterFillDerivedDataCache/Public/DisplayClusterFillDerivedDataCacheWorker.h` (Public)


#### class `FDisplayClusterFillDerivedDataCacheWorker`  
`class FDisplayClusterFillDerivedDataCacheWorker : public FRunnable, public FSingleThreadRunnable`  
_L16-85_
- inherits: `FRunnable,FSingleThreadRunnable`
- L20 _public prototype_ `FDisplayClusterFillDerivedDataCacheWorker();`
- L25 _public function_ `virtual uint32 Run() override`
- L30 _public function_ `virtual void Stop() override`
- L37 _public function_ `virtual void Tick() override`
- L41 _public function_ `virtual FSingleThreadRunnable* GetSingleThreadInterface() override`
- L47 _public prototype_ `void CancelTask();`
- L48 _public prototype_ `void CompleteCommandletAndShowNotification();`
- L52 _protected prototype_ `void RegexParseForEnumerationCount(const FString& LogString);`
- L53 _protected prototype_ `void RegexParseForLoadingProgress(const FString& LogString);`
- L54 _protected prototype_ `void RegexParseForCompilationProgress(const FString& LogString);`
- L56 _protected prototype_ `FString GetDdcCommandletParams() const;`
- L57 _protected prototype_ `FString GetTargetPlatformParams() const;`
- L59 _protected prototype_ `FString GetLastWholeLogBlock(const FString& LogString);`
- L61 _protected prototype_ `void ReadCommandletOutputAndUpdateEditorNotification();`
- L64 _protected member_ `TUniquePtr<FAsyncTaskNotification> ProgressNotification;` — Progress notification
- L68 _private member_ `TUniquePtr<FRunnableThread> Thread;`
- L70 _private member_ `int32 ResultCode = 0;`
- L71 _private member_ `bool bWasCancelled = false;`
- L72 _private member_ `FProcHandle ProcessHandle;`
- L74 _private member_ `void* ReadPipe = nullptr;`
- L75 _private member_ `void* WritePipe = nullptr;`
- L77 _private member_ `FString LastPartialLogLine;`
- L79 _private member_ `int32 LoadingTotal = INDEX_NONE;`
- L80 _private member_ `int32 CompileTotal = INDEX_NONE;`
- L81 _private member_ `int32 AssetsWaitingToCompile = INDEX_NONE;`
- L83 _private member_ `FString CurrentExecutableName;`
- L84 _private member_ `FString Arguments;`
