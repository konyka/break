# Programs / DatasmithCADWorker

- module root: `Source/Programs/Enterprise/Datasmith/DatasmithCADWorker`
- headers: 2; symbols: 22
- symbol kinds: class=1, delegate=1, member=10, prototype=10
- PrivateDependencyModuleNames: ApplicationCore, CADInterfaces, CADTools, Core, DatasmithDispatcher, Projects, Sockets
- PublicIncludePathModuleNames: Launch

### `Source/Programs/Enterprise/Datasmith/DatasmithCADWorker/Private/DatasmithCADWorker.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDatasmithCADWorker, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDatasmithCADWorker, Log, All);`

### `Source/Programs/Enterprise/Datasmith/DatasmithCADWorker/Private/DatasmithCADWorkerImpl.h` (Private)


#### class `FDatasmithCADWorkerImpl`  
`class FDatasmithCADWorkerImpl`  
_L16-50_
- L19 _public prototype_ `FDatasmithCADWorkerImpl(int32 InServerPID, int32 InServerPort, const FString& EnginePluginsPath, const FString& InCachePath);`
- L20 _public prototype_ `bool Run();`
- L23 _private prototype_ `void InitiatePing();`
- L25 _private prototype_ `void ProcessCommand(const DatasmithDispatcher::FPingCommand& PingCommand);`
- L26 _private prototype_ `void ProcessCommand(const DatasmithDispatcher::FBackPingCommand& BackPingCommand);`
- L27 _private prototype_ `void ProcessCommand(const DatasmithDispatcher::FImportParametersCommand& BackPingCommand);`
- L28 _private prototype_ `void ProcessCommand(const DatasmithDispatcher::FRunTaskCommand& TerminateCommand);`
- L33 _private prototype_ `static void CheckDuration(const CADLibrary::FFileDescriptor& FileToProcess, const int64 MaxDuration);` — @param MaxDuration is defined in seconds.
- L34 _private prototype_ `static void CheckMemory();`
- L37 _private member_ `DatasmithDispatcher::FNetworkClientNode NetworkInterface;`
- L38 _private member_ `DatasmithDispatcher::FCommandQueue CommandIO;`
- L40 _private member_ `int32 ServerPID;`
- L41 _private member_ `int32 ServerPort;`
- L42 _private member_ `FString EnginePluginsPath;`
- L43 _private member_ `FString CachePath;`
- L44 _private member_ `CADLibrary::FImportParameters ImportParameters;`
- L45 _private member_ `uint64 PingStartCycle;`
- L48 _public member_ `static std::atomic<bool> bProcessIsRunning;`
- L49 _public member_ `static std::atomic<bool> bRequestRestart;`
