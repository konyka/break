# Plugins / InterchangeDispatcher

- module root: `Plugins/Interchange/Runtime/Source/Dispatcher`
- headers: 9; symbols: 340
- symbol kinds: class=26, delegate=2, enum=5, enumerator=37, function=65, macro=5, member=76, namespace=18, prototype=95, struct=4, variable=7
- PrivateDependencyModuleNames: Json
- PublicDependencyModuleNames: Core, Sockets

### `Plugins/Interchange/Runtime/Source/Dispatcher/Public/FBX/InterchangeDispatcherFBXTasks.h` (Public)


#### class `UE::Interchange::FJsonFBXLoadSourceCmd`  
`class FJsonFBXLoadSourceCmd : public FJsonLoadSourceCmd`  
_L10-83_
- inherits: `FJsonLoadSourceCmd`
- L13 _public function_ `FJsonFBXLoadSourceCmd() : FJsonLoadSourceCmd()`
- L15 _public function_ `FJsonFBXLoadSourceCmd(const FString& InTranslatorID , const FString& InSourceFilename , const bool InbConvertScene , const bool InbForceFrontXAxis , const bool InbConvertSceneUnit , const bool InbKeepFbxNamespace , const bool InbConsiderClusterBeforePoseForMeshBindPose) : FJsonLoadSourceCmd(InTranslatorID, InSourceFilename) , bConvertScene(InbConvertScene) , bForceFrontXAxis(InbForceFrontXAxis) , bConvertSceneUnit(InbConvertSceneUnit) , bKeepFbxNamespace(InbKeepFbxNamespace) , bConsiderClusterBeforePoseForMeshBindPose(InbConsiderClusterBeforePoseForMeshBindPose)`
- L31 _public prototype_ `virtual TSharedPtr<FJsonObject> GetActionDataObject() const override;`
- L32 _public prototype_ `virtual bool IsActionDataObjectValid(const FJsonObject& ActionDataObject) override;`
- L34 _public function_ `bool GetDoesConvertScene() const`
- L41 _public function_ `bool GetDoesForceFrontXAxis() const`
- L48 _public function_ `bool GetDoesConvertSceneUnit() const`
- L55 _public function_ `bool GetDoesKeepFbxNamespace() const`
- L62 _public function_ `bool GetDoesUseFbxClustersForBindPoseMatrices() const`
- L69 _public member_ `static const TCHAR* TaskName;`
- L72 _private member_ `bool bConvertScene = true;`
- L73 _private member_ `bool bForceFrontXAxis = false;`
- L74 _private member_ `bool bConvertSceneUnit = true;`
- L75 _private member_ `bool bKeepFbxNamespace = false;`
- L76 _private member_ `bool bConsiderClusterBeforePoseForMeshBindPose = false;`
- L78 _private member_ `static const TCHAR* ConvertSceneJsonKey;`
- L79 _private member_ `static const TCHAR* ForceFrontXAxisJsonKey;`
- L80 _private member_ `static const TCHAR* ConvertSceneUnitJsonKey;`
- L81 _private member_ `static const TCHAR* KeepFbxNamespaceJsonKey;`
- L82 _private member_ `static const TCHAR* UseFbxClustersForBindPoseMatricesJsonKey;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Interchange` (scope `UE`)

### `Plugins/Interchange/Runtime/Source/Dispatcher/Public/InterchangeCommands.h` (Public)


#### class `UE::Interchange::DispatcherCommandVersion`  
`class DispatcherCommandVersion`  
_L18-71_
- L22 _public prototype_ `static int32 GetMajor();` — Major version should be updated when there is an existing API that has been change.
- L24 _public prototype_ `static int32 GetMinor();` — Minor version must be updated when there is an addition to the API.
- L26 _public prototype_ `static int32 GetPatch();` — Patch version should be update if there is some bug fixes in the private code.
- L29 _public function_ `static bool GetLWCDisabled()` — LWCDisabled version tell if the code was compile with serialization compatibility.
- L36 _public function_ `static FString ToString()` — Return the version in string format "Major.Minor.Patch"
- L42 _public function_ `static bool FromString(const FString& VersionStr, int32& OutMajor, int32& OutMinor, int32& OutPatch, bool& bOutLWCDisabled)`
- L67 _public function_ `static bool IsAPICompatible(int32 Major, int32 Minor, int32 Patch, bool bLWCDisabled)` — We consider having the same major and minor version will make the API fully compatible. Patch is only a hint in case you need a particular fixes @param Major - The Major version you want to test against the compile Major version @param Minor - The Minor version you want to test against the compile Minor version @param Patch - In case we need it later, not use currently @return true if Major and Minor version equal the compile one, InPatch is only there in case we need it in a future release

#### enum `UE::Interchange::ECommandId`  
`enum class ECommandId : uint8`  
_L73-85_
- L75 _public enumerator_ `Invalid`
- L76 _public enumerator_ `Error`
- L77 _public enumerator_ `Ping`
- L78 _public enumerator_ `BackPing`
- L79 _public enumerator_ `RunTask`
- L80 _public enumerator_ `NotifyEndTask`
- L81 _public enumerator_ `QueryTaskProgress`
- L82 _public enumerator_ `CompletedQueryTaskProgress`
- L83 _public enumerator_ `Terminate`
- L84 _public enumerator_ `Last`

#### class `UE::Interchange::ICommand`  
`class ICommand`  
_L87-98_
- L90 _public prototype_ `virtual ~ICommand() = default;`
- L92 _public prototype_ `virtual ECommandId GetType() const = 0;`
- L97 _protected function_ `virtual void SerializeImpl(FArchive&)`

#### class `UE::Interchange::FTerminateCommand`  
`class FTerminateCommand : public ICommand`  
_L114-118_
- inherits: `ICommand`
- L117 _public function_ `virtual ECommandId GetType() const override`

#### class `UE::Interchange::FErrorCommand`  
`class FErrorCommand : public ICommand`  
_L120-129_
- inherits: `ICommand`
- L123 _public function_ `virtual ECommandId GetType() const override`
- L126 _protected prototype_ `virtual void SerializeImpl(FArchive&) override;`
- L128 _public member_ `FString ErrorMessage;`

#### class `UE::Interchange::FPingCommand`  
`class FPingCommand : public ICommand`  
_L131-135_
- inherits: `ICommand`
- L134 _public function_ `virtual ECommandId GetType() const override`

#### class `UE::Interchange::FBackPingCommand`  
`class FBackPingCommand : public ICommand`  
_L138-142_
- inherits: `ICommand`
- L141 _public function_ `virtual ECommandId GetType() const override`

#### class `UE::Interchange::FRunTaskCommand`  
`class FRunTaskCommand : public ICommand`  
_L144-157_
- inherits: `ICommand`
- L147 _public prototype_ `FRunTaskCommand() = default;`
- L148 _public function_ `FRunTaskCommand(const FTask& Task) : JsonDescription(Task.JsonDescription), TaskIndex(Task.Index)`
- L149 _public function_ `virtual ECommandId GetType() const override`
- L152 _protected prototype_ `virtual void SerializeImpl(FArchive&) override;`
- L155 _public member_ `FString JsonDescription;`
- L156 _public member_ `int32 TaskIndex = -1;`

#### class `UE::Interchange::FCompletedTaskCommand`  
`class FCompletedTaskCommand : public ICommand`  
_L159-172_
- inherits: `ICommand`
- L162 _public function_ `virtual ECommandId GetType() const override`
- L165 _protected prototype_ `virtual void SerializeImpl(FArchive&) override;`
- L168 _public member_ `ETaskState ProcessResult = ETaskState::Unknown;`
- L169 _public member_ `FString JSonResult;`
- L170 _public member_ `TArray<FString> JSonMessages;`
- L171 _public member_ `int32 TaskIndex = INDEX_NONE;`

#### class `UE::Interchange::FQueryTaskProgressCommand`  
`class FQueryTaskProgressCommand : public ICommand`  
_L174-186_
- inherits: `ICommand`
- L177 _public prototype_ `FQueryTaskProgressCommand() = default;`
- L178 _public prototype_ `FQueryTaskProgressCommand(const TArray<int32>& Tasks);`
- L179 _public function_ `virtual ECommandId GetType() const override`
- L182 _protected prototype_ `virtual void SerializeImpl(FArchive&) override;`
- L185 _public member_ `TArray<int32> TaskIndexes;`

#### class `UE::Interchange::FCompletedQueryTaskProgressCommand`  
`class FCompletedQueryTaskProgressCommand : public ICommand`  
_L188-207_
- inherits: `ICommand`
- L191 _public prototype_ `FCompletedQueryTaskProgressCommand() = default;`
- L192 _public function_ `virtual ECommandId GetType() const override`
- L195 _protected prototype_ `virtual void SerializeImpl(FArchive&) override;`
- L206 _public member_ `TArray<FTaskProgressData> TaskStates;`

#### struct `UE::Interchange::FCompletedQueryTaskProgressCommand::FTaskProgressData`  
`struct FTaskProgressData`  
_L198-205_
- L200 _public member_ `int32 TaskIndex;`
- L201 _public member_ `ETaskState TaskState;`
- L202 _public member_ `float TaskProgress;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INTERCHANGEDISPATCHER_API`
- L13 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Interchange` (scope `UE`)
- L94 _function_ `friend void operator<<(FArchive& Ar, ICommand& C)` (scope `UE::Interchange`)
- L103 _prototype_ `TSharedPtr<ICommand> CreateCommand(ECommandId CommandType);` (scope `UE::Interchange`) — Create a new command from its type
- L106 _prototype_ `void SerializeCommand(ICommand& Command, TArray<uint8>& OutBuffer);` (scope `UE::Interchange`) — Converts a command into a byte buffer
- L110 _prototype_ `TSharedPtr<ICommand> DeserializeCommand(const TArray<uint8>& InBuffer);` (scope `UE::Interchange`) — Converts byte buffer back into a Command returns nullptr in case of error

### `Plugins/Interchange/Runtime/Source/Dispatcher/Public/InterchangeDispatcher.h` (Public)


#### class `UE::Interchange::FInterchangeDispatcher`  
`class FInterchangeDispatcher`  
_L18-80_
- desc: Handle a list of tasks, and a set of external workers to consume them.
- L23 _public prototype_ `FInterchangeDispatcher(const FString& InResultFolder, int32 WorkerCount = 1);` — If WorkerCount == 0, the dispatcher will determine the number of worker processes to start based on main application's workload, threads and memory wise.
- L24 _public function_ `virtual ~FInterchangeDispatcher()`
- L26 _public prototype_ `int32 AddTask(const FString& JsonDescription);`
- L27 _public prototype_ `int32 AddTask(const FString& JsonDescription, FInterchangeDispatcherTaskCompleted TaskCompledDelegate);`
- L28 _public prototype_ `TOptional<FTask> GetNextTask();`
- L29 _public prototype_ `void SetTaskState(int32 TaskIndex, ETaskState TaskState, const FString& JsonResult, const TArray<FString>& JSonMessages);`
- L30 _public prototype_ `void GetTaskState(int32 TaskIndex, ETaskState& TaskState, double& TaskRunningStateStartTime);`
- L31 _public prototype_ `void GetTaskState(int32 TaskIndex, ETaskState& TaskState, FString& JsonResult, TArray<FString>& JSonMessages);`
- L33 _public prototype_ `void StartProcess();`
- L34 _public prototype_ `virtual void StopProcess(bool bBlockUntilTerminated);`
- L35 _public prototype_ `virtual void TerminateProcess();`
- L36 _public prototype_ `void WaitAllTaskToCompleteExecution();`
- L37 _public prototype_ `bool IsOver();`
- L39 _public function_ `virtual const TCHAR* GetWorkerApplicationName()`
- L44 _public prototype_ `const FString& GetWorkerApplicationPath();`
- L46 _public function_ `void SetInterchangeWorkerFatalError(FString& ErrorMessage)`
- L51 _public function_ `FString GetInterchangeWorkerFatalError()`
- L56 _public prototype_ `bool IsValid();`
- L59 _protected prototype_ `void CloseHandlers();`
- L62 _protected member_ `FString ResultFolder;` — Path where the result files are dump
- L63 _protected member_ `TArray<FTask> TaskPool;`
- L66 _private prototype_ `void SpawnHandlers();`
- L67 _private prototype_ `void EmptyQueueTasks();`
- L70 _private member_ `FCriticalSection TaskPoolCriticalSection;` — Tasks
- L71 _private member_ `int32 NextTaskIndex;`
- L72 _private member_ `int32 CompletedTaskCount;`
- L74 _private member_ `FString InterchangeWorkerFatalError;`
- L77 _private member_ `FString WorkerApplicationPath;` — Workers
- L78 _private member_ `TArray<TUniquePtr<FInterchangeWorkerHandler>> WorkerHandlers;`
- L79 _private member_ `TUniquePtr<FInterchangeWorkerHandler> WorkerHandler_Deprecated = nullptr;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API INTERCHANGEDISPATCHER_API`
- L12 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Interchange` (scope `UE`)

### `Plugins/Interchange/Runtime/Source/Dispatcher/Public/InterchangeDispatcherConfig.h` (Public)


#### Free symbols / members of external scopes

- L4 _namespace_ `namespace UE`
- L6 _namespace_ `namespace Interchange` (scope `UE`)
- L8 _namespace_ `namespace Config` (scope `UE::Interchange`)
- L11 _variable_ `constexpr double AcceptTimeout_s = 3.0;` (scope `UE::Interchange::Config`) — Server side timeout for connection with the client
- L14 _variable_ `constexpr double ConnectTimeout_s = 3.0;` (scope `UE::Interchange::Config`) — Client side timeout for connection with the server
- L18 _variable_ `constexpr double SendCommandTimeout_s = 1.0;` (scope `UE::Interchange::Config`) — Maximum time we accept to wait when a command is sent. If the command is not sent by this delay, the operation is considered as failed
- L23 _variable_ `constexpr bool CloseProcessByCommand = true;` (scope `UE::Interchange::Config`) — When true, a Terminate command is sent to the processor and we wait for TerminateTimeout_s seconds for it to close, before a hard TerminateProc. When false, the process is directly closed with a TerminateProc.
- L27 _variable_ `constexpr double TerminateTimeout_s = 1.0;` (scope `UE::Interchange::Config`) — Maximum time we accept to wait for the process to close after a Terminate command has been sent.
- L30 _variable_ `constexpr double IdleLoopDelay = 0.1;` (scope `UE::Interchange::Config`) — Delay between successive checks for a new task, and validation of the connection
- L33 _variable_ `constexpr double ProcessingLoopDelay = 0.5;` (scope `UE::Interchange::Config`) — Delay between successive validation of the connection

### `Plugins/Interchange/Runtime/Source/Dispatcher/Public/InterchangeDispatcherLog.h` (Public)


#### Free symbols / members of external scopes

- L6 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogInterchangeDispatcher, Log, All)`

### `Plugins/Interchange/Runtime/Source/Dispatcher/Public/InterchangeDispatcherModule.h` (Public)


#### class `FInterchangeDispatcherModule`  
`class FInterchangeDispatcherModule : public IModuleInterface`  
_L11-19_
- inherits: `IModuleInterface`
- desc: This module allows out-of-process Interchange translators in case a third-party SDK is not thread-safe.
- L14 _public prototype_ `static FInterchangeDispatcherModule& Get();`
- L15 _public prototype_ `static bool IsAvailable();`
- L18 _private prototype_ `virtual void StartupModule() override;`

#### Free symbols / members of external scopes

- L6 _macro_ `#define INTERCHANGEDISPATCHER_MODULE_NAME TEXT("InterchangeDispatcher")`

### `Plugins/Interchange/Runtime/Source/Dispatcher/Public/InterchangeDispatcherNetworking.h` (Public)


#### enum `UE::Interchange::SocketErrorCode`  
`enum class SocketErrorCode`  
_L19-30_
- L21 _public enumerator_ `NoError = 0`
- L22 _public enumerator_ `Error_Create`
- L23 _public enumerator_ `Error_Bind`
- L24 _public enumerator_ `Error_Listen`
- L25 _public enumerator_ `UnableToReadOnSocket`
- L26 _public enumerator_ `UnableToSendData`
- L27 _public enumerator_ `CouldNotStartWSA`
- L28 _public enumerator_ `UnableToGetLocalAddress`
- L29 _public enumerator_ `ConnectionToServerFailed`

#### struct `UE::Interchange::FMessageHeader`  
`struct FMessageHeader`  
_L33-44_
- L35 _public member_ `int32 ByteSize = -1;`

#### class `UE::Interchange::FNetworkNode`  
`class FNetworkNode`  
_L47-82_
- L50 _public prototype_ `virtual ~FNetworkNode();`
- L54 _public prototype_ `bool SendMessage(const TArray<uint8>& Buffer, double Timeout_s);` — Send a byte buffer as an atomic message returns true when a message is successfully sent
- L58 _public prototype_ `bool ReceiveMessage(TArray<uint8>& OutBuffer, double Timeout_s);` — Receive a byte buffer as an atomic message returns true when a message is fetched. In that case, OutBuffer contains the message.
- L60 _public function_ `bool IsValid() const`
- L68 _protected prototype_ `FSocket* CreateInternalSocket(const FString& Description);`
- L69 _protected prototype_ `void CloseSocket(FSocket*& Socket);`
- L70 _protected prototype_ `bool IsConnected();`
- L73 _protected member_ `FSocket* ConnectedSocket = nullptr;`
- L74 _protected member_ `SocketErrorCode ConnectedSocketError = SocketErrorCode::NoError;`
- L76 _protected member_ `FMessage IncommingMessage;`
- L78 _protected member_ `bool bReadError = false;`
- L79 _protected member_ `bool bWriteError = false;`
- L81 _protected member_ `FCriticalSection SendReceiveCriticalSection;`

#### struct `UE::Interchange::FNetworkNode::FMessage`  
`struct FMessage`  
_L63-67_
- L65 _public member_ `FMessageHeader Header;`
- L66 _public member_ `TArray<uint8> Content;`

#### class `UE::Interchange::FNetworkServerNode`  
`class FNetworkServerNode : public FNetworkNode`  
_L87-97_
- inherits: `FNetworkNode`
- desc: Create, Bind, Listen, Accept sequence
- L90 _public prototype_ `FNetworkServerNode();`
- L91 _public prototype_ `~FNetworkServerNode();`
- L92 _public prototype_ `int32 GetListeningPort();`
- L93 _public prototype_ `bool Accept(const FString& Description, double Timeout_s);`
- L96 _private member_ `FSocket* ListeningSocket;`

#### class `UE::Interchange::FNetworkClientNode`  
`class FNetworkClientNode : public FNetworkNode`  
_L102-106_
- inherits: `FNetworkNode`
- desc: Create, Connect sequence
- L105 _public prototype_ `bool Connect(const FString& Description, int32 ServerPort, double Timeout_s);`

#### class `UE::Interchange::FCommandQueue`  
`class FCommandQueue`  
_L110-128_
- L113 _public prototype_ `void SetNetworkInterface(FNetworkNode* InNetworkInterface);`
- L115 _public prototype_ `TSharedPtr<ICommand> GetNextCommand(double Timeout_s);`
- L116 _public prototype_ `bool SendCommand(ICommand& Commmand, double Timeout_s);`
- L118 _public function_ `bool IsValid()`
- L120 _public prototype_ `void Disconnect(double Timeout_s);`
- L123 _private prototype_ `bool Poll(double Timeout_s);`
- L124 _private member_ `TQueue<TSharedPtr<ICommand>> InCommands;`
- L127 _private member_ `FNetworkNode* NetworkInterface = nullptr;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API INTERCHANGEDISPATCHER_API`
- L14 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Interchange` (scope `UE`)
- L37 _function_ `friend void operator<< (FArchive& Ar, FMessageHeader& H)` (scope `UE::Interchange`)

### `Plugins/Interchange/Runtime/Source/Dispatcher/Public/InterchangeDispatcherTask.h` (Public)


#### enum `UE::Interchange::ETaskState`  
`enum class ETaskState`  
_L24-31_
- L26 _public enumerator_ `Unknown`
- L27 _public enumerator_ `Running`
- L28 _public enumerator_ `UnTreated`
- L29 _public enumerator_ `ProcessOk`
- L30 _public enumerator_ `ProcessFailed`

#### struct `UE::Interchange::FTask`  
`struct FTask`  
_L33-50_
- L35 _public prototype_ `FTask() = delete;`
- L37 _public function_ `FTask(const FString& InJsonDescription)`
- L43 _public member_ `FString JsonDescription;`
- L44 _public member_ `int32 Index = -1;`
- L45 _public member_ `ETaskState State = ETaskState::Unknown;`
- L46 _public member_ `FString JsonResult;`
- L47 _public member_ `TArray<FString> JsonMessages;`
- L48 _public member_ `FInterchangeDispatcherTaskCompleted OnTaskCompleted;`
- L49 _public member_ `double RunningStateStartTime = 0;`

#### class `UE::Interchange::IJsonCmdBase`  
`class IJsonCmdBase`  
_L55-88_
- desc: Json cmd helper to be able to read and write a FTask::JsonDescription
- L58 _public prototype_ `virtual ~IJsonCmdBase() = default;`
- L60 _public prototype_ `virtual FString GetAction() const = 0;`
- L61 _public prototype_ `virtual FString GetTranslatorID() const = 0;`
- L62 _public prototype_ `virtual FString ToJson() const = 0;`
- L67 _public prototype_ `virtual bool FromJson(const FString& JsonString) = 0;` — Return false if the JsonString do not match the command, true otherwise.
- L69 _public function_ `static FString GetCommandIDJsonKey()`
- L74 _public function_ `static FString GetTranslatorIDJsonKey()`
- L79 _public function_ `static FString GetCommandDataJsonKey()`
- L87 _protected member_ `bool bIsDataInitialize = false;` — Use this member to know if the data is initialize before using it

#### class `UE::Interchange::FJsonLoadSourceCmd`  
`class FJsonLoadSourceCmd : public IJsonCmdBase`  
_L90-172_
- inherits: `IJsonCmdBase`
- L93 _public function_ `FJsonLoadSourceCmd()`
- L98 _public prototype_ `virtual ~FJsonLoadSourceCmd() = default;`
- L100 _public function_ `FJsonLoadSourceCmd(const FString& InTranslatorID , const FString& InSourceFilename) : TranslatorID(InTranslatorID) , SourceFilename(InSourceFilename)`
- L108 _public function_ `virtual FString GetAction() const override`
- L114 _public function_ `virtual FString GetTranslatorID() const override`
- L121 _public prototype_ `virtual FString ToJson() const;`
- L122 _public prototype_ `virtual bool FromJson(const FString& JsonString);`
- L124 _public prototype_ `virtual TSharedPtr<FJsonObject> GetActionDataObject() const;`
- L125 _public function_ `virtual bool IsActionDataObjectValid(const FJsonObject& ActionDataObject)`
- L130 _public function_ `FString GetSourceFilename() const`
- L137 _public function_ `static FString GetSourceFilenameJsonKey()`
- L170 _private member_ `FString TranslatorID = FString();`
- L171 _private member_ `FString SourceFilename = FString();`

#### class `UE::Interchange::FJsonLoadSourceCmd::JsonResultParser`  
`class JsonResultParser`  
_L146-167_
- desc: Use this class helper to create the cmd result json string and to read it
- L149 _public function_ `FString GetResultFilename() const`
- L153 _public function_ `void SetResultFilename(const FString& InResultFilename)`
- L157 _public prototype_ `FString ToJson() const;`
- L158 _public prototype_ `bool FromJson(const FString& JsonString);`
- L160 _public function_ `static FString GetResultFilenameJsonKey()`
- L166 _private member_ `FString ResultFilename = FString();`

#### class `UE::Interchange::FJsonFetchPayloadCmd`  
`class FJsonFetchPayloadCmd : public IJsonCmdBase`  
_L174-248_
- inherits: `IJsonCmdBase`
- L177 _public function_ `FJsonFetchPayloadCmd()`
- L182 _public function_ `FJsonFetchPayloadCmd(const FString& InTranslatorID, const FString& InPayloadKey) : TranslatorID(InTranslatorID) , PayloadKey(InPayloadKey)`
- L190 _public function_ `virtual FString GetAction() const override`
- L196 _public function_ `virtual FString GetTranslatorID() const override`
- L203 _public prototype_ `virtual FString ToJson() const;`
- L204 _public prototype_ `virtual bool FromJson(const FString& JsonString);`
- L206 _public function_ `FString GetPayloadKey() const`
- L213 _public function_ `static FString GetPayloadKeyJsonKey()`
- L246 _protected member_ `FString TranslatorID = FString();`
- L247 _protected member_ `FString PayloadKey = FString();`

#### class `UE::Interchange::FJsonFetchPayloadCmd::JsonResultParser`  
`class JsonResultParser`  
_L222-243_
- desc: Use this class helper to create the cmd result json string and to read it
- L225 _public function_ `FString GetResultFilename() const`
- L229 _public function_ `void SetResultFilename(const FString& InResultFilename)`
- L233 _public prototype_ `FString ToJson() const;`
- L234 _public prototype_ `bool FromJson(const FString& JsonString);`
- L236 _public function_ `static FString GetResultFilenameJsonKey()`
- L242 _private member_ `FString ResultFilename = FString();`

#### class `UE::Interchange::FJsonFetchMeshPayloadCmd`  
`class FJsonFetchMeshPayloadCmd : public FJsonFetchPayloadCmd`  
_L251-282_
- inherits: `FJsonFetchPayloadCmd`
- desc: Mesh payload require a transform to bake the mesh to avoid degenerate triangle when importing a small mesh scale by a scene node.
- L254 _public function_ `FJsonFetchMeshPayloadCmd()`
- L259 _public function_ `FJsonFetchMeshPayloadCmd(const FString& InTranslatorID , const FString& InPayloadKey , const FTransform& InMeshGlobalTransform) : FJsonFetchPayloadCmd(InTranslatorID, InPayloadKey) , MeshGlobalTransform(InMeshGlobalTransform)`
- L266 _public prototype_ `virtual FString ToJson() const override;`
- L267 _public prototype_ `virtual bool FromJson(const FString& JsonString) override;`
- L269 _public function_ `FTransform GetMeshGlobalTransform() const`
- L275 _public function_ `static FString GetMeshGlobalTransformJsonKey()`
- L281 _protected member_ `FTransform MeshGlobalTransform = FTransform::Identity;`

#### class `UE::Interchange::FJsonFetchAnimationQueriesCmd`  
`class FJsonFetchAnimationQueriesCmd : public FJsonFetchPayloadCmd`  
_L284-346_
- inherits: `FJsonFetchPayloadCmd`
- L287 _public function_ `FJsonFetchAnimationQueriesCmd()`
- L292 _public function_ `FJsonFetchAnimationQueriesCmd(const FString& InTranslatorID, const FString& InQueriesJsonString) : FJsonFetchPayloadCmd(InTranslatorID, TEXT("AnimationQueries")) , QueriesJsonString(InQueriesJsonString)`
- L298 _public prototype_ `virtual FString ToJson() const override;`
- L299 _public prototype_ `virtual bool FromJson(const FString& JsonString) override;`
- L301 _public function_ `static FString GetQueriesJsonStringKey()`
- L307 _public function_ `FString GetQueriesJsonString() const`
- L345 _protected member_ `FString QueriesJsonString;`

#### class `UE::Interchange::FJsonFetchAnimationQueriesCmd::JsonAnimationQueriesResultParser`  
`class JsonAnimationQueriesResultParser`  
_L315-342_
- desc: Use this class helper to create the cmd result json string and to read it
- L318 _public function_ `TMap<FString, FString> GetResultFilename() const`
- L322 _public function_ `void SetHashToFilenames(const TMap<FString, FString>& InHashToFilenames)`
- L327 _public prototype_ `FString ToJson() const;`
- L328 _public prototype_ `bool FromJson(const FString& JsonString);`
- L330 _public function_ `static FString GetHashToFilenamesKey()`
- L336 _public function_ `const TMap<FString, FString>& GetHashToFilenames() const`
- L341 _private member_ `TMap<FString, FString> HashToFilenames;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Interchange` (scope `UE`)
- L18 _delegate_ `DECLARE_DELEGATE_OneParam(FInterchangeDispatcherTaskCompleted, int32 TaskIndex);`
- L18 _prototype_ `DECLARE_DELEGATE_OneParam(FInterchangeDispatcherTaskCompleted, int32 TaskIndex);`
- L20 _namespace_ `namespace UE`
- L22 _namespace_ `namespace Interchange` (scope `UE`)

### `Plugins/Interchange/Runtime/Source/Dispatcher/Public/InterchangeWorkerHandler.h` (Public)


#### enum `UE::Interchange::EWorkerState`  
`enum class EWorkerState : uint8`  
_L26-33_
- L28 _public enumerator_ `Uninitialized = 0`
- L29 _public enumerator_ `Processing = 1 << 0` — send task and receive result
- L30 _public enumerator_ `Idle = 1 << 1` — waiting for a new task
- L31 _public enumerator_ `Closing = 1 << 2` — in the process of terminating
- L32 _public enumerator_ `Terminated = 1 << 3` — worker does not run

#### class `UE::Interchange::FInterchangeWorkerHandler`  
`class FInterchangeWorkerHandler`  
_L37-103_
- desc: Handle a Worker by socket communication
- L52 _public prototype_ `FInterchangeWorkerHandler(FInterchangeDispatcher& InDispatcher, FString& InResultFolder);`
- L53 _public prototype_ `~FInterchangeWorkerHandler();`
- L55 _public prototype_ `void Run();`
- L56 _public prototype_ `bool IsAlive() const;`
- L57 _public prototype_ `void Stop();`
- L58 _public prototype_ `void StopBlocking();`
- L60 _public function_ `bool IsPingCommandReceived()`
- L62 _public member_ `FSimpleMulticastDelegate OnWorkerHandlerExitLoop;`
- L64 _protected prototype_ `void ProcessCommand(ICommand& Command);`
- L66 _private prototype_ `void RunInternal();`
- L67 _private prototype_ `void StartWorkerProcess();`
- L68 _private prototype_ `void ValidateConnection();`
- L70 _private prototype_ `void ProcessCommand(FPingCommand& PingCommand);`
- L71 _private prototype_ `void ProcessCommand(FErrorCommand& ErrorCommand);`
- L72 _private prototype_ `void ProcessCommand(FCompletedTaskCommand& RunTaskCommand);`
- L73 _private prototype_ `void ProcessCommand(FCompletedQueryTaskProgressCommand& CompletedQueryTaskProgressCommand);`
- L74 _private prototype_ `const TCHAR* EWorkerErrorStateAsString(EWorkerErrorState e);`
- L76 _private prototype_ `void KillAllCurrentTasks();`
- L79 _private member_ `FInterchangeDispatcher& Dispatcher;`
- L82 _private member_ `FNetworkServerNode NetworkInterface;` — Send and receive commands
- L83 _private member_ `FCommandQueue CommandIO;`
- L84 _private member_ `FThread IOThread;`
- L85 _private member_ `FString ThreadName;`
- L88 _private member_ `FProcHandle WorkerHandle;` — External process
- L89 _private member_ `TAtomic<EWorkerState> WorkerState;`
- L90 _private member_ `EWorkerErrorState ErrorState;`
- L93 _private member_ `FString ResultFolder;` — self
- L94 _private member_ `FCriticalSection CurrentTasksLock;`
- L95 _private member_ `TArray<int32> CurrentTasks;`
- L96 _private member_ `bool bShouldTerminate;`
- L97 _private member_ `double LastProgressMessageTime;`
- L100 _private member_ `bool bPingCommandReceived = false;` — When the worker start, it send a ping command. This flag is turn on when we receive the ping command

#### enum `UE::Interchange::FInterchangeWorkerHandler::EWorkerErrorState`  
`enum class EWorkerErrorState`  
_L39-49_
- L41 _public enumerator_ `Ok`
- L42 _public enumerator_ `ConnectionFailed_NotBound`
- L43 _public enumerator_ `ConnectionFailed_NoClient`
- L44 _public enumerator_ `ConnectionLost`
- L45 _public enumerator_ `ConnectionLost_SendFailed`
- L46 _public enumerator_ `WorkerProcess_CantCreate`
- L47 _public enumerator_ `WorkerProcess_Lost`
- L48 _public enumerator_ `WorkerProcess_Crashed`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API INTERCHANGEDISPATCHER_API`
- L15 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Interchange` (scope `UE`)
- L19 _namespace_ `namespace Dispatcher` (scope `UE::Interchange`)
- L34 _prototype_ `ENUM_CLASS_FLAGS(EWorkerState);` (scope `UE::Interchange`)
