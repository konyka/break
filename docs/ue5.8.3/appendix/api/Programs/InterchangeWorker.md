# Programs / InterchangeWorker

- module root: `Source/Programs/InterchangeWorker`
- headers: 2; symbols: 24
- symbol kinds: class=1, delegate=1, member=10, prototype=12
- PrivateDependencyModuleNames: ApplicationCore, Core, CoreUObject, InterchangeCore, InterchangeDispatcher, InterchangeFbxParser, InterchangeNodes, Json, Projects, Sockets
- PublicIncludePathModuleNames: Launch

### `Source/Programs/InterchangeWorker/Private/InterchangeWorker.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogInterchangeWorker, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogInterchangeWorker, Log, All);`

### `Source/Programs/InterchangeWorker/Private/InterchangeWorkerImpl.h` (Private)


#### class `FInterchangeWorkerImpl`  
`class FInterchangeWorkerImpl`  
_L16-47_
- L19 _public prototype_ `FInterchangeWorkerImpl(int32 InServerPID, int32 InServerPort, FString& InResultFolder);`
- L20 _public prototype_ `bool Run(const FString& WorkerVersionError);`
- L23 _private prototype_ `void InitiatePing();`
- L24 _private prototype_ `void ProcessCommand(const UE::Interchange::FPingCommand& PingCommand);`
- L25 _private prototype_ `void ProcessCommand(const UE::Interchange::FBackPingCommand& BackPingCommand);`
- L26 _private prototype_ `void ProcessCommand(const TSharedPtr<UE::Interchange::ICommand> Command, const FString& ThreadName);`
- L27 _private prototype_ `void ProcessCommand(const UE::Interchange::FQueryTaskProgressCommand& QueryTaskProgressCommand);`
- L29 _private prototype_ `UE::Interchange::ETaskState LoadFbxFile(const UE::Interchange::FJsonFBXLoadSourceCmd& LoadSourceCommand, FString& OutJSonResult, TArray<FString>& OutJSonMessages);`
- L30 _private prototype_ `UE::Interchange::ETaskState FetchFbxPayload(const UE::Interchange::FJsonFetchPayloadCmd& FetchPayloadCommand, FString& OutJSonResult, TArray<FString>& OutJSonMessages);`
- L31 _private prototype_ `UE::Interchange::ETaskState FetchFbxPayload(const UE::Interchange::FJsonFetchMeshPayloadCmd& FetchMeshPayloadCommand, FString& OutJSonResult, TArray<FString>& OutJSonMessages);`
- L32 _private prototype_ `UE::Interchange::ETaskState FetchFbxPayload(const UE::Interchange::FJsonFetchAnimationQueriesCmd& FetchAnimationBakeTransformPayloadCommand, FString& OutJSonResult, TArray<FString>& OutJSonMessages);`
- L34 _private member_ `UE::Interchange::FNetworkClientNode NetworkInterface;`
- L35 _private member_ `UE::Interchange::FCommandQueue CommandIO;`
- L37 _private member_ `int32 ServerPID;`
- L38 _private member_ `int32 ServerPort;`
- L39 _private member_ `uint64 PingStartCycle;`
- L40 _private member_ `FString ResultFolder;`
- L41 _private member_ `FCriticalSection TFinishThreadCriticalSection;`
- L42 _private member_ `TArray<FString> CurrentFinishThreads;`
- L43 _private member_ `TMap<FString, TFuture<bool> > ActiveThreads;`
- L45 _private member_ `UE::Interchange::FInterchangeFbxParser FbxParser;`
