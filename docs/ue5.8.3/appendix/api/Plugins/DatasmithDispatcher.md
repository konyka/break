# Plugins / DatasmithDispatcher

- module root: `Plugins/Enterprise/DatasmithCADImporter/Source/DatasmithDispatcher`
- headers: 8; symbols: 185
- symbol kinds: class=14, delegate=1, enum=4, enumerator=29, function=16, macro=1, member=47, namespace=7, prototype=54, struct=3, typedef=1, variable=8
- PrivateDependencyModuleNames: 
- PublicDependencyModuleNames: CADInterfaces, CADTools, Core, Sockets

### `Plugins/Enterprise/DatasmithCADImporter/Source/DatasmithDispatcher/Public/DatasmithCommands.h` (Public)


#### enum `DatasmithDispatcher::ECommandId`  
`enum class ECommandId : uint8`  
_L16-26_
- L18 _public enumerator_ `Invalid`
- L19 _public enumerator_ `Ping`
- L20 _public enumerator_ `BackPing`
- L21 _public enumerator_ `RunTask`
- L22 _public enumerator_ `NotifyEndTask`
- L23 _public enumerator_ `ImportParams`
- L24 _public enumerator_ `Terminate`
- L25 _public enumerator_ `Last`

#### class `DatasmithDispatcher::ICommand`  
`class ICommand`  
_L30-41_
- L33 _public prototype_ `virtual ~ICommand() = default;`
- L35 _public prototype_ `virtual ECommandId GetType() const = 0;`
- L40 _protected function_ `virtual void SerializeImpl(FArchive&)`

#### class `DatasmithDispatcher::FTerminateCommand`  
`class FTerminateCommand : public ICommand`  
_L57-61_
- inherits: `ICommand`
- L60 _public function_ `virtual ECommandId GetType() const override`

#### class `DatasmithDispatcher::FPingCommand`  
`class FPingCommand : public ICommand`  
_L64-68_
- inherits: `ICommand`
- L67 _public function_ `virtual ECommandId GetType() const override`

#### class `DatasmithDispatcher::FBackPingCommand`  
`class FBackPingCommand : public ICommand`  
_L71-75_
- inherits: `ICommand`
- L74 _public function_ `virtual ECommandId GetType() const override`

#### class `DatasmithDispatcher::FRunTaskCommand`  
`class FRunTaskCommand : public ICommand`  
_L78-97_
- inherits: `ICommand`
- L81 _public prototype_ `FRunTaskCommand() = default;`
- L82 _public function_ `FRunTaskCommand(const FTask& Task) : JobFileDescription(Task.FileDescription) , Mesher(Task.Mesher) , JobIndex(Task.Index)`
- L87 _public function_ `virtual ECommandId GetType() const override`
- L90 _protected prototype_ `virtual void SerializeImpl(FArchive&) override;`
- L93 _public member_ `CADLibrary::FFileDescriptor JobFileDescription;`
- L94 _public member_ `CADLibrary::EMesher Mesher;`
- L96 _public member_ `int32 JobIndex = -1;`

#### class `DatasmithDispatcher::FCompletedTaskCommand`  
`class FCompletedTaskCommand : public ICommand`  
_L99-113_
- inherits: `ICommand`
- L102 _public function_ `virtual ECommandId GetType() const override`
- L105 _protected prototype_ `virtual void SerializeImpl(FArchive&) override;`
- L108 _public member_ `TArray<CADLibrary::FFileDescriptor> ExternalReferences;`
- L109 _public member_ `FString SceneGraphFileName;`
- L110 _public member_ `FString GeomFileName;`
- L111 _public member_ `ETaskState ProcessResult = ETaskState::Unknown;`
- L112 _public member_ `TArray<TPair<uint8, FString>> Messages;`

#### class `DatasmithDispatcher::FImportParametersCommand`  
`class FImportParametersCommand : public ICommand`  
_L115-134_
- inherits: `ICommand`
- L118 _public function_ `FImportParametersCommand(const CADLibrary::FImportParameters& InImportParameters) : ImportParameters(InImportParameters)`
- L123 _public function_ `FImportParametersCommand()`
- L127 _public function_ `virtual ECommandId GetType() const override`
- L130 _protected prototype_ `virtual void SerializeImpl(FArchive&) override;`
- L133 _public member_ `CADLibrary::FImportParameters ImportParameters;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace DatasmithDispatcher`
- L37 _function_ `friend void operator<<(FArchive& Ar, ICommand& C)` (scope `DatasmithDispatcher`)
- L46 _prototype_ `TSharedPtr<ICommand> CreateCommand(ECommandId CommandType);` (scope `DatasmithDispatcher`) — Create a new command from its type
- L49 _prototype_ `void SerializeCommand(ICommand& Command, TArray<uint8>& OutBuffer);` (scope `DatasmithDispatcher`) — Converts a command into a byte buffer
- L53 _prototype_ `TSharedPtr<ICommand> DeserializeCommand(const TArray<uint8>& InBuffer);` (scope `DatasmithDispatcher`) — Converts byte buffer back into a Command returns nullptr in case of error

### `Plugins/Enterprise/DatasmithCADImporter/Source/DatasmithDispatcher/Public/DatasmithDispatcher.h` (Public)


#### class `DatasmithDispatcher::FDatasmithDispatcher`  
`class FDatasmithDispatcher`  
_L17-62_
- desc: Handle a list of tasks, and a set of external workers to consume them. Concept of task is currently tightly coupled with cad usage...
- L20 _public prototype_ `FDatasmithDispatcher(const CADLibrary::FImportParameters& InImportParameters, const FString& InCacheDir, TMap<uint32, FString>& CADFileToUnrealFileMap, TMap<uint32, FString>& CADFileToUnrealGeomMap);`
- L22 _public prototype_ `void AddTask(const CADLibrary::FFileDescriptor & FileDescription, CADLibrary::EMesher Mesher);`
- L23 _public prototype_ `TOptional<FTask> GetNextTask();`
- L24 _public prototype_ `void SetTaskState(int32 TaskIndex, ETaskState TaskState);`
- L26 _public prototype_ `void Process(bool bWithProcessor);`
- L27 _public prototype_ `bool IsOver();`
- L29 _public prototype_ `void LinkCTFileToUnrealCacheFile(const CADLibrary::FFileDescriptor& CTFileDescription, const FString& UnrealSceneGraphFile, const FString& UnrealGeomFile);`
- L31 _public prototype_ `void LogMessages(const TArray<TPair<uint8, FString>>& Warnings) const;`
- L33 _public function_ `void SetWorkerCount(const int32 InNumberOfWorkers)`
- L39 _private prototype_ `void SpawnHandlers();`
- L40 _private prototype_ `int32 GetNextWorkerId();`
- L41 _private prototype_ `void CloseHandlers();`
- L43 _private prototype_ `void ProcessLocal();`
- L47 _private member_ `FCriticalSection TaskPoolCriticalSection;` — Tasks
- L48 _private member_ `TArray<FTask> TaskPool;`
- L49 _private member_ `int32 NextTaskIndex;`
- L50 _private member_ `int32 CompletedTaskCount;`
- L53 _private member_ `TMap<uint32, FString>& CADFileToUnrealFileMap;` — Scene wide state
- L54 _private member_ `TMap<uint32, FString>& CADFileToUnrealGeomMap;`
- L55 _private member_ `FString ProcessCacheFolder;`
- L56 _private member_ `CADLibrary::FImportParameters ImportParameters;`
- L59 _private member_ `int32 NumberOfWorkers;` — Workers
- L60 _private member_ `int32 NextWorkerId;`
- L61 _private member_ `TArray<FDatasmithWorkerHandler> WorkerHandlers;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace DatasmithDispatcher`

### `Plugins/Enterprise/DatasmithCADImporter/Source/DatasmithDispatcher/Public/DatasmithDispatcherConfig.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace DatasmithDispatcher`
- L9 _namespace_ `namespace Config` (scope `DatasmithDispatcher`)
- L13 _variable_ `constexpr double AcceptTimeout_s = 6.0;` (scope `DatasmithDispatcher::Config`) — Server side timeout for connection with the client
- L16 _variable_ `constexpr double ConnectTimeout_s = 3.0;` (scope `DatasmithDispatcher::Config`) — Client side timeout for connection with the server
- L20 _variable_ `constexpr double SendCommandTimeout_s = 1.0;` (scope `DatasmithDispatcher::Config`) — Maximum time we accept to wait when a command is sent. If the command is not sent by this delay, the operation is considered as failed
- L25 _variable_ `constexpr bool CloseProcessByCommand = true;` (scope `DatasmithDispatcher::Config`) — When true, a Terminate command is sent to the processor and we wait for TerminateTimeout_s seconds for it to close, before a hard TerminateProc. When false, the process is directly closed with a TerminateProc.
- L29 _variable_ `constexpr double TerminateTimeout_s = 1.0;` (scope `DatasmithDispatcher::Config`) — Maximum time we accept to wait for the process to close after a Terminate command has been sent.
- L32 _variable_ `constexpr double IdleLoopDelay = 0.1;` (scope `DatasmithDispatcher::Config`) — Delay between successive checks for a new task, and validation of the connection
- L35 _variable_ `constexpr double ProcessingLoopDelay = 0.5;` (scope `DatasmithDispatcher::Config`) — Delay between successive validation of the connection
- L38 _variable_ `constexpr int32 MaxRestartAllowed = 1000;` (scope `DatasmithDispatcher::Config`) — Number of worker instance that can be restarted when a crash occurs in en external process

### `Plugins/Enterprise/DatasmithCADImporter/Source/DatasmithDispatcher/Public/DatasmithDispatcherLog.h` (Public)


#### Free symbols / members of external scopes

- L6 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDatasmithDispatcher, Log, All)`

### `Plugins/Enterprise/DatasmithCADImporter/Source/DatasmithDispatcher/Public/DatasmithDispatcherModule.h` (Public)


#### class `FDatasmithDispatcherModule`  
`class FDatasmithDispatcherModule : public IModuleInterface`  
_L11-19_
- inherits: `IModuleInterface`
- desc: This module exposes additional features for assets containing CoreTech data.
- L14 _public prototype_ `static FDatasmithDispatcherModule& Get();`
- L15 _public prototype_ `static bool IsAvailable();`
- L18 _private prototype_ `virtual void StartupModule() override;`

#### Free symbols / members of external scopes

- L6 _macro_ `#define DATASMITHDISPATCHER_MODULE_NAME TEXT("DatasmithDispatcher")`

### `Plugins/Enterprise/DatasmithCADImporter/Source/DatasmithDispatcher/Public/DatasmithDispatcherNetworking.h` (Public)


#### enum `DatasmithDispatcher::SocketErrorCode`  
`enum class SocketErrorCode`  
_L15-26_
- L17 _public enumerator_ `NoError = 0`
- L18 _public enumerator_ `Error_Create`
- L19 _public enumerator_ `Error_Bind`
- L20 _public enumerator_ `Error_Listen`
- L21 _public enumerator_ `UnableToReadOnSocket`
- L22 _public enumerator_ `UnableToSendData`
- L23 _public enumerator_ `CouldNotStartWSA`
- L24 _public enumerator_ `UnableToGetLocalAddress`
- L25 _public enumerator_ `ConnectionToServerFailed`

#### struct `DatasmithDispatcher::FMessageHeader`  
`struct FMessageHeader`  
_L32-43_
- L34 _public member_ `int32 ByteSize = -1;`

#### class `DatasmithDispatcher::FNetworkNode`  
`class FNetworkNode`  
_L46-79_
- L49 _public prototype_ `virtual ~FNetworkNode();`
- L53 _public prototype_ `bool SendMessage(const TArray<uint8>& Buffer, double Timeout_s);` — Send a byte buffer as an atomic message returns true when a message is successfully sent
- L57 _public prototype_ `bool ReceiveMessage(TArray<uint8>& OutBuffer, double Timeout_s);` — Receive a byte buffer as an atomic message returns true when a message is fetched. In that case, OutBuffer contains the message.
- L59 _public function_ `bool IsValid() const`
- L67 _protected prototype_ `FSocket* CreateInternalSocket(const FString& Description);`
- L68 _protected prototype_ `void CloseSocket(FSocket*& Socket);`
- L69 _protected prototype_ `bool IsConnected();`
- L72 _protected member_ `FSocket* ConnectedSocket = nullptr;`
- L73 _protected member_ `SocketErrorCode ConnectedSocketError = SocketErrorCode::NoError;`
- L75 _protected member_ `FMessage IncommingMessage;`
- L77 _protected member_ `bool bReadError = false;`
- L78 _protected member_ `bool bWriteError = false;`

#### struct `DatasmithDispatcher::FNetworkNode::FMessage`  
`struct FMessage`  
_L62-66_
- L64 _public member_ `FMessageHeader Header;`
- L65 _public member_ `TArray<uint8> Content;`

#### class `DatasmithDispatcher::FNetworkServerNode`  
`class FNetworkServerNode : public FNetworkNode`  
_L84-94_
- inherits: `FNetworkNode`
- desc: Create, Bind, Listen, Accept sequence
- L87 _public prototype_ `FNetworkServerNode();`
- L88 _public prototype_ `~FNetworkServerNode();`
- L89 _public prototype_ `int32 GetListeningPort();`
- L90 _public prototype_ `bool Accept(const FString& Description, double Timeout_s);`
- L93 _private member_ `FSocket* ListeningSocket;`

#### class `DatasmithDispatcher::FNetworkClientNode`  
`class FNetworkClientNode : public FNetworkNode`  
_L99-103_
- inherits: `FNetworkNode`
- desc: Create, Connect sequence
- L102 _public prototype_ `bool Connect(const FString& Description, int32 ServerPort, double Timeout_s);`

#### class `DatasmithDispatcher::FCommandQueue`  
`class FCommandQueue`  
_L108-126_
- L111 _public prototype_ `void SetNetworkInterface(FNetworkNode* InNetworkInterface);`
- L113 _public prototype_ `TSharedPtr<ICommand> GetNextCommand(double Timeout_s);`
- L114 _public prototype_ `bool SendCommand(ICommand& Commmand, double Timeout_s);`
- L116 _public function_ `bool IsValid()`
- L118 _public prototype_ `void Disconnect(double Timeout_s);`
- L121 _private prototype_ `bool Poll(double Timeout_s);`
- L122 _private member_ `TQueue<TSharedPtr<ICommand>> InCommands;`
- L125 _private member_ `FNetworkNode* NetworkInterface = nullptr;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace DatasmithDispatcher`
- L36 _function_ `friend void operator<< (FArchive& Ar, FMessageHeader& H)` (scope `DatasmithDispatcher`)

### `Plugins/Enterprise/DatasmithCADImporter/Source/DatasmithDispatcher/Public/DatasmithDispatcherTask.h` (Public)


#### struct `DatasmithDispatcher::FTask`  
`struct FTask`  
_L13-29_
- L15 _public prototype_ `FTask() = default;`
- L17 _public function_ `FTask(const CADLibrary::FFileDescriptor& InFile, const CADLibrary::EMesher InMesher) : FileDescription(InFile) , Mesher(InMesher) , State(ETaskState::UnTreated)`
- L24 _public member_ `CADLibrary::FFileDescriptor FileDescription;`
- L25 _public member_ `CADLibrary::EMesher Mesher;`
- L26 _public member_ `int32 Index = -1;`
- L27 _public member_ `ETaskState State = ETaskState::Unknown;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace DatasmithDispatcher`
- L11 _typedef_ `using ETaskState = CADLibrary::ECADParsingResult;` (scope `DatasmithDispatcher`)

### `Plugins/Enterprise/DatasmithCADImporter/Source/DatasmithDispatcher/Public/DatasmithWorkerHandler.h` (Public)


#### class `DatasmithDispatcher::FDatasmithWorkerHandler`  
`class FDatasmithWorkerHandler`  
_L21-82_
- desc: Handle a Worker by socket communication
- L44 _public prototype_ `FDatasmithWorkerHandler(FDatasmithDispatcher& InDispatcher, const CADLibrary::FImportParameters& InImportParameters, FString& InCachePath, uint32 Id);`
- L45 _public prototype_ `~FDatasmithWorkerHandler();`
- L47 _public prototype_ `void Run();`
- L48 _public prototype_ `bool IsAlive() const;`
- L49 _public prototype_ `bool IsRestartable() const;`
- L50 _public prototype_ `void Stop();`
- L53 _private prototype_ `void RunInternal();`
- L54 _private prototype_ `void StartWorkerProcess();`
- L55 _private prototype_ `void ValidateConnection();`
- L57 _private prototype_ `void ProcessCommand(ICommand& Command);`
- L58 _private prototype_ `void ProcessCommand(FPingCommand& PingCommand);`
- L59 _private prototype_ `void ProcessCommand(FCompletedTaskCommand& RunTaskCommand);`
- L60 _private prototype_ `const TCHAR* EWorkerErrorStateAsString(EWorkerErrorState e);`
- L63 _private member_ `FDatasmithDispatcher& Dispatcher;`
- L66 _private member_ `FNetworkServerNode NetworkInterface;` — Send and receive commands
- L67 _private member_ `FCommandQueue CommandIO;`
- L68 _private member_ `UE::Tasks::FTask IOTask;`
- L69 _private member_ `FString ThreadName;`
- L72 _private member_ `FProcHandle WorkerHandle;` — External process
- L73 _private member_ `TAtomic<EWorkerState> WorkerState;`
- L74 _private member_ `EWorkerErrorState ErrorState;`
- L77 _private member_ `FString CachePath;` — self
- L78 _private member_ `FImportParametersCommand ImportParametersCommand;`
- L79 _private member_ `TOptional<FTask> CurrentTask;`
- L80 _private member_ `bool bShouldTerminate;`

#### enum `DatasmithDispatcher::FDatasmithWorkerHandler::EWorkerState`  
`enum class EWorkerState`  
_L23-30_
- L25 _public enumerator_ `Uninitialized`
- L26 _public enumerator_ `Idle` — Initialized, available for processing
- L27 _public enumerator_ `Processing` — Currently processing a task
- L28 _public enumerator_ `Closing` — in the process of terminating
- L29 _public enumerator_ `Terminated` — aka. Not Alive

#### enum `DatasmithDispatcher::FDatasmithWorkerHandler::EWorkerErrorState`  
`enum class EWorkerErrorState`  
_L32-41_
- L34 _public enumerator_ `Ok`
- L35 _public enumerator_ `ConnectionFailed_NotBound`
- L36 _public enumerator_ `ConnectionFailed_NoClient`
- L37 _public enumerator_ `ConnectionLost`
- L38 _public enumerator_ `ConnectionLost_SendFailed`
- L39 _public enumerator_ `WorkerProcess_CantCreate`
- L40 _public enumerator_ `WorkerProcess_Lost`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace DatasmithDispatcher`
