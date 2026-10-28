# CSharp / EpicGames.UBA

- project root: `Source/Programs/Shared/EpicGames.UBA`
- files: 21; symbols: 505
- symbol kinds: class=23, const=1, ctor=16, delegate=14, dtor=11, enum=4, enumerator=15, event=11, field=50, interface=13, method=260, property=82, record struct=1, struct=4
- access marked `*` is implicit (not written in source)

### `Source/Programs/Shared/EpicGames.UBA/IBaseInterface.cs` (EpicGames.UBA)


#### interface `EpicGames.UBA.IBaseInterface`  
`public interface IBaseInterface : IDisposable`  
_public; L10-22_
- inherits: `IDisposable`
- desc: Base interface for all classes that have unmanaged resources.
- L16 _public method_ `public abstract IntPtr GetHandle()` — Returns the handle to an unmanaged object
- L18-21 _public* ctor_ `static IBaseInterface()`

### `Source/Programs/Shared/EpicGames.UBA/ICacheClient.cs` (EpicGames.UBA)


#### record struct `EpicGames.UBA.FetchFromCacheResult`  
`public readonly record struct FetchFromCacheResult(bool Success, List<string> LogLines)`  
_public; L13-13_
- desc: Struct containing results from artifact fetch

#### interface `EpicGames.UBA.ICacheClient`  
`public interface ICacheClient : IBaseInterface`  
_public; L18-78_
- inherits: `IBaseInterface`
- desc: Base interface for a cache client
- L27 _public method_ `public abstract bool Connect(string host, int port, int desiredConnectionCount = 1)` — Connect to cache server
- L32 _public method_ `public abstract void Disconnect()` — Disconnect from cache server
- L37 _public method_ `public abstract void PopulatePathHashes()` — Traverse all path hashes that have been registered and add them to the cache server. Note, this should be done just before processing actions
- L49 _public method_ `public abstract bool WriteToCache(uint bucket, nint processHandle, byte[] inputs, uint inputsSize, byte[] outputs, uint outputsSize)` — Write to cache
- L58 _public method_ `public abstract FetchFromCacheResult FetchFromCache(ulong rootsHandle, uint bucket, ProcessStartInfo info)` — Fetch from cache
- L64 _public method_ `public abstract void RequestServerShutdown(string reason)` — Request the connected server to shutdown
- L74-77 _public method_ `public static ICacheClient CreateCacheClient(ISessionServer session, bool reportMissReason, string crypto = "", string hint = "")` — Create a ICacheClient object

### `Source/Programs/Shared/EpicGames.UBA/IConfig.cs` (EpicGames.UBA)


#### interface `EpicGames.UBA.IConfig`  
`public interface IConfig : IBaseInterface`  
_public; L10-29_
- inherits: `IBaseInterface`
- desc: Base interface for uba config file
- L17-20 _public method_ `public static IConfig LoadConfig(string configFile)` — Load a config file
- L28 _public* method_ `void AddValue(string table, string name, string value)` — Load a config file

### `Source/Programs/Shared/EpicGames.UBA/ILogger.cs` (EpicGames.UBA)


#### enum `EpicGames.UBA.LogEntryType`  
`public enum LogEntryType`  
_public; L10-36_
- desc: The verbosity of a log entry
- L15 _public* enumerator_ `Error = 0` — Error verbosity
- L20 _public* enumerator_ `Warning = 1` — Warning verbosity
- L25 _public* enumerator_ `Info = 2` — Info verbosity
- L30 _public* enumerator_ `Detail = 3` — Info verbosity
- L35 _public* enumerator_ `Debug = 4` — Info verbosity

#### interface `EpicGames.UBA.ILogger`  
`public interface ILogger : IBaseInterface`  
_public; L41-87_
- inherits: `IBaseInterface`
- desc: Base interface for logging functionality
- L46 _public method_ `public abstract void BeginScope()` — Begin logging scope
- L51 _public method_ `public abstract void EndScope()` — End logging scope
- L58 _public method_ `public abstract void Log(LogEntryType type, string message)` — Log message
- L66-76 _public method_ `public static ILogger CreateLogger(Microsoft.Extensions.Logging.ILogger logger, bool makeGlobal)` — Create a ILogger object
- L81 _public method_ `public static ILogger CreateNullLogger()` — Creates null logger
- L86 _public property_ `public static ILogger? GlobalLogger => ...` — Get the global trace if there is one

### `Source/Programs/Shared/EpicGames.UBA/IProcess.cs` (EpicGames.UBA)


#### struct `EpicGames.UBA.ProcessStartInfo`  
`public struct ProcessStartInfo`  
_public; L13-80_
- desc: Information needed to create a process
- L34 _public property_ `public string Application { get; set; }` — The path to the application binary
- L39 _public property_ `public string WorkingDirectory { get; set; }` — The working directory
- L44 _public property_ `public string Arguments { get; set; }` — The command line arguments
- L49 _public property_ `public string Description { get; set; }` — A text description of the process
- L54 _public property_ `public CommonProcessConfigs Configuration { get; set; }` — Which configuration to use
- L59 _public property_ `public ProcessPriorityClass Priority { get; set; }` — The process priority of the created process
- L64 _public property_ `public bool TrackInputs { get; set; }` — If input should be tracked
- L69 _public property_ `public string? LogFile { get; set; }` — A path to a log file, or null for not log file
- L74 _public property_ `public object? UserData { get; set; }` — Arbitary user data to pass along with the process
- L79 _public property_ `public ulong RootsHandle { get; set; }` — RootsHandle for process used to convert paths

#### enum `EpicGames.UBA.ProcessStartInfo.CommonProcessConfigs`  
`public enum CommonProcessConfigs`  
_public; L18-29_
- desc: Common configs for processes to run
- L23 _public* enumerator_ `CompileMsvc` — MSVC based compiler
- L28 _public* enumerator_ `CompileClang` — Clang based compiler

#### interface `EpicGames.UBA.IProcessStartInfo`  
`internal interface IProcessStartInfo : IBaseInterface`  
_internal; L85-97_
- inherits: `IBaseInterface`
- desc: Base interface for process start info
- L93-96 _public method_ `public static IProcessStartInfo CreateProcessStartInfo(ProcessStartInfo info, bool useExitedCallback)` — Create a IProcessStartInfo object

#### class `EpicGames.UBA.ExitedEventArgs`  
`public class ExitedEventArgs(IProcess process) : EventArgs`  
_public; L103-134_
- desc: Event args for exited event
- L108 _public property_ `public int ExitCode { get; }` — Process exit code
- L113 _public property_ `public string? ExecutingHost { get; }` — The remote host that ran the process, if run remotely
- L118 _public property_ `public List<string> LogLines { get; }` — Captured output lines
- L123 _public property_ `public TimeSpan TotalProcessorTime { get; }` — Total time spent for the processor
- L128 _public property_ `public TimeSpan TotalWallTime { get; }` — Total wall time spent
- L133 _public property_ `public object? UserData { get; }` — Total wall time spent

#### interface `EpicGames.UBA.IProcess`  
`public interface IProcess : IBaseInterface`  
_public; L139-206_
- inherits: `IBaseInterface`
- desc: Interface for a process instance
- L146 _public delegate_ `public delegate void ExitedEventHandler(object sender, ExitedEventArgs e)` — Delegate for Exited events
- L151 _public event_ `public abstract event ExitedEventHandler? Exited` — Exited event handler
- L156 _public property_ `public abstract int ExitCode { get; }` — Process exit code
- L161 _public property_ `public abstract string? ExecutingHost { get; }` — The remote host that ran the process, if run remotely
- L166 _public property_ `public abstract List<string> LogLines { get; }` — Captured output lines
- L171 _public property_ `public abstract TimeSpan TotalProcessorTime { get; }` — Total time spent for the processor
- L176 _public property_ `public abstract TimeSpan TotalWallTime { get; }` — Total wall time spent
- L181 _public property_ `public abstract ulong Hash { get; }` — Unique hash for this process (not stable between runs)
- L186 _public property_ `public abstract object? UserData { get; }` — Arbitary user data
- L192 _public method_ `public abstract void Cancel(bool terminate)` — Cancel the running process
- L202-205 _internal method_ `internal static IProcess CreateProcess(IntPtr handle, IProcessStartInfo info, ExitedEventHandler? exitedEventHandler, object? userData)` — Create a IProcess object

### `Source/Programs/Shared/EpicGames.UBA/IScheduler.cs` (EpicGames.UBA)


#### enum `EpicGames.UBA.ProcessExecutionType`  
`public enum ProcessExecutionType`  
_public; L12-38_
- desc: Type of execution used for process
- L17 _public* enumerator_ `Native` — Process executed locally without detouring
- L22 _public* enumerator_ `Local` — Process executed locally with detouring enabled
- L27 _public* enumerator_ `Remote` — Process executed on a remote session
- L32 _public* enumerator_ `Cache` — Process was never executed and instead downloaded from cache
- L37 _public* enumerator_ `Skip` — Process was skipped and never executed

#### interface `EpicGames.UBA.IProcessFinishedInfo`  
`public interface IProcessFinishedInfo`  
_public; L42-88_
- L47 _public* property_ `ProcessExecutionType ExecutionType { get; }` — Type of execution
- L52 _public* property_ `int ExitCode { get; }` — Process exit code
- L57 _public* property_ `List<string> LogLines { get; }` — Captured output lines
- L62 _public* property_ `string? ExecutingHost { get; }` — The remote host that ran the process, if run remotely
- L67 _public* property_ `TimeSpan TotalProcessorTime { get; }` — Total time spent for the processor
- L72 _public* property_ `TimeSpan TotalWallTime { get; }` — Total wall time spent
- L77 _public* property_ `ulong PeakMemoryUsed { get; }` — Peak memory used, requires a job object so will only be non-zero for Windows hosts.
- L82 _public* property_ `object UserData { get; }` — UserData that was provided in EnqueueProcess
- L87 _public* property_ `nint ProcessHandle { get; }` — Native uba handle to process.

#### enum `EpicGames.UBA.ProcessFinishedResponse`  
`public enum ProcessFinishedResponse`  
_public; L92-106_
- L97 _public* enumerator_ `None` — None means that nothing should be done
- L101 _public* enumerator_ `RerunLocal` — RerunLocal means that we want to re-run the process locally with detouring enabled
- L105 _public* enumerator_ `RerunNative` — RerunNative means that we want to re-run the process locally without detouring

#### interface `EpicGames.UBA.IScheduler`  
`public interface IScheduler : IBaseInterface`  
_public; L111-161_
- inherits: `IBaseInterface`
- desc: Base interface for uba config file
- L117 _public* method_ `void Start()` — Start the scheduler. It will start processing enqueued processes straight away
- L122 _public* method_ `uint EnqueueProcess(ProcessStartInfo info, double weight, bool canDetour, bool canExecuteRemotely, bool canCrossArchitecture, bool canCrossPlatform, int[]? dependencies, byte[]? knownInputs, uint knownInputsCount, uint cacheBucket, uint memoryGroup, ulong predictedMemoryUsage, object userData)` — Queue process.
- L127 _public* method_ `void Cancel()` — Cancel all active processes and skip queued ones
- L132 _public* property_ `bool IsEmpty { get; }` — Returns true if no processes are running or queued
- L137 _public* method_ `void GetProcessWeightThatCanRunRemotelyNow(out double totalWeight, out double crossArchitecture, out double crossPlatform)` — Accumulated weight of all processes that are Queued and can run right now (dependencies are done)
- L142 _public* method_ `void SetProcessFinishedCallback(Func<IProcessFinishedInfo, ProcessFinishedResponse> processFinished)` — Set callback for when process has finished
- L147 _public* method_ `void SetAllowDisableRemoteExecution()` — Allows uba to disable remote execution if running out of processes that can execute remotely
- L157-160 _public method_ `public static IScheduler CreateScheduler(ISessionServer session, IEnumerable<ICacheClient> cacheClients, IConfig config, int maxLocalProcessors, bool forceRemote)` — Create a scheduler

### `Source/Programs/Shared/EpicGames.UBA/IServer.cs` (EpicGames.UBA)


#### interface `EpicGames.UBA.IServer`  
`public interface IServer : IBaseInterface`  
_public; L10-65_
- inherits: `IBaseInterface`
- desc: Base interface for a server instance
- L19 _public method_ `public abstract bool StartServer(string ip = "", int port = -1, string crypto = "")` — Start the server
- L24 _public method_ `public abstract void StopServer()` — Stop the server
- L31 _public method_ `public abstract bool AddNamedConnection(string name)` — Add a named connection to the server
- L40 _public method_ `public abstract bool AddClient(string ip, int port, string crypto = "")` — Adds a client that server will try to connect one or more tcp connections to
- L46 _public method_ `public abstract void SetClientsConfig(IConfig config)` — Set config (.toml) that should be used by all clients.
- L56-59 _public method_ `public static IServer CreateServer(int maxWorkers, int sendSize, ILogger logger, bool useQuic)` — Create a IServer object
- L64 _public method_ `public static IServer CreateNullServer()` — Create a null server

### `Source/Programs/Shared/EpicGames.UBA/ISessionServer.cs` (EpicGames.UBA)


#### struct `EpicGames.UBA.SessionServerCreateInfo`  
`public readonly struct SessionServerCreateInfo(string rootDirectory, string traceOutputFile, bool disableCustomAllocator, bool launchVisualizer, bool resetCas, bool writeToDisk, bool detailedTrace, bool allowWaitOnMem, bool allowKillOnMem, bool storeObjFilesCompressed)`  
_public; L21-72_
- desc: Information needed to create a session server
- L26 _public property_ `public string RootDirectory { get; }` — Root directory to store content addressable data
- L31 _public property_ `public string TraceOutputFile { get; }` — Path to a trace file that records the build
- L36 _public property_ `public bool DisableCustomAllocator { get; }` — If the custom allocator should be disabled
- L41 _public property_ `public bool LaunchVisualizer { get; }` — If the visualizer should be launched
- L46 _public property_ `public bool ResetCas { get; }` — If the content addressable storage should be reset
- L51 _public property_ `public bool WriteToDisk { get; }` — If intermediate/output files should be written to disk
- L56 _public property_ `public bool DetailedTrace { get; }` — More detailed trace information
- L61 _public property_ `public bool AllowWaitOnMem { get; }` — Wait for memory before starting new processes
- L66 _public property_ `public bool AllowKillOnMem { get; }` — Kill processes when close to run out of memory
- L71 _public property_ `public bool StoreObjFilesCompressed { get; }` — Store .obj files compressed on disk

#### interface `EpicGames.UBA.ISessionServerCreateInfo`  
`public interface ISessionServerCreateInfo : IBaseInterface`  
_public; L77-91_
- inherits: `IBaseInterface`
- desc: Base interface for session server create info
- L87-90 _public method_ `public static ISessionServerCreateInfo CreateSessionServerCreateInfo(IStorageServer storage, IServer client, ILogger logger, SessionServerCreateInfo info)` — Create a ISessionServerCreateInfo object

#### class `EpicGames.UBA.RemoteProcessSlotAvailableEventArgs`  
`public class RemoteProcessSlotAvailableEventArgs(bool isCrossArchitecture) : EventArgs`  
_public; L97-103_
- desc: Event args for remote process slot available event
- L102 _public property_ `public bool IsCrossArchitecture { get; }` — Is true if the available remote process slot is on a cross architecture machine

#### class `EpicGames.UBA.RemoteProcessReturnedEventArgs`  
`public class RemoteProcessReturnedEventArgs(IProcess process) : EventArgs`  
_public; L109-116_
- desc: Event args for remote process returned event
- L115 _public property_ `public IProcess Process { get; }` — The remote process that was returned

#### interface `EpicGames.UBA.ISessionServer`  
`public interface ISessionServer : IBaseInterface`  
_public; L121-274_
- inherits: `IBaseInterface`
- desc: Base interface for a session server instance
- L128 _public delegate_ `public delegate void RemoteProcessSlotAvailableEventHandler(object sender, RemoteProcessSlotAvailableEventArgs e)` — Degeate for remote process slot available events
- L135 _public delegate_ `public delegate void RemoteProcessReturnedEventHandler(object sender, RemoteProcessReturnedEventArgs e)` — Degeate for remote process returned events
- L140 _public event_ `public abstract event RemoteProcessSlotAvailableEventHandler? RemoteProcessSlotAvailable` — Remote process slot available event handler
- L145 _public event_ `public abstract event RemoteProcessReturnedEventHandler? RemoteProcessReturned` — Remote process returned event handler
- L150 _public method_ `public abstract void AddInfo(string info)` — Add more info about session that show in visualizer
- L156 _public method_ `public abstract void DisableRemoteExecution()` — Will tell all remote machines that they can disconnect once their active processes are done Will also stop listening for new remote machines
- L161 _public method_ `public abstract bool DisableRemoteExecutionOnAgent(string agentName)` — Sets specific agent to finish current work and then disconnect
- L167 _public method_ `public abstract void SetMaxRemoteProcessCount(uint count)` — Set max number of processes that can be executed remotely. Setting this can let the backend disconnect remote workers earlier
- L177 _public method_ `public abstract IProcess RunProcess(ProcessStartInfo info, bool async, IProcess.ExitedEventHandler? exitedEventHandler, bool enableDetour)` — Run a local process
- L189 _public method_ `public abstract IProcess RunProcessRemote(ProcessStartInfo info, IProcess.ExitedEventHandler? exitedEventHandler, double weight = 1.0, byte[]? knownInputs = null, uint knownInputsCount = 0, bool canExecuteCrossArchitecture = false)` — Run a remote process
- L197 _public method_ `public abstract ulong RegisterRoots(byte[] rootsData, uint rootsDataSize)` — Register roots data and get handle back
- L203 _public method_ `public abstract void RefreshDirectories(params string[] directories)` — Refresh cached information about directories
- L209 _public method_ `public abstract void RegisterNewFiles(params string[] files)` — Registers external files write to session caches
- L218 _public method_ `public abstract bool RegisterVirtualFile(string name, string sourceFile, ulong sourceOffset, ulong sourceSize)` — Registers virtual files that are part of other files (mapped into sections of existing file)
- L225 _public method_ `public abstract uint BeginExternalProcess(string description)` — Registers the start of an external process
- L232 _public method_ `public abstract void EndExternalProcess(uint id, uint exitCode)` — Registers the end of an external process
- L240 _public method_ `public abstract void UpdateProgress(uint processesTotal, uint processesDone, uint errorCount)` — Writes external status to the uba trace stream which can then be visualized by ubavisualizer
- L248 _public method_ `public abstract void SetCustomCasKeyFromTrackedInputs(string file, string workingDirectory, IProcess process)` — Set a custom cas key for a process's tracked inputs
- L253 _public method_ `public abstract void CancelAll()` — Cancel all processes
- L258 _public method_ `public abstract void PrintSummary()` — Print summary information to the logger
- L263 _public method_ `public abstract ITrace GetTrace()` — Get the trace for this session
- L270-273 _public method_ `public static ISessionServer CreateSessionServer(ISessionServerCreateInfo info)` — Create a ISessionServer object

### `Source/Programs/Shared/EpicGames.UBA/IStorageServer.cs` (EpicGames.UBA)


#### struct `EpicGames.UBA.StorageServerCreateInfo`  
`public readonly struct StorageServerCreateInfo(string rootDirectory, ulong capacityBytes, bool storeCompressed, string zone)`  
_public; L14-35_
- desc: Information needed to create a storage server
- L19 _public property_ `public string RootDirectory { get; }` — The root directory for the storage
- L24 _public property_ `public ulong CapacityBytes { get; }` — The capacity of the storage in bytes
- L29 _public property_ `public bool StoreCompressed { get; }` — If the storage should be stored as compressed
- L34 _public property_ `public string Zone { get; }` — The geographical zone this machine belongs to. Can be empty

#### interface `EpicGames.UBA.IStorageServer`  
`public interface IStorageServer : IBaseInterface`  
_public; L40-68_
- inherits: `IBaseInterface`
- desc: Base interface for a storage server instance
- L45 _public method_ `public abstract void SaveCasTable()` — Save tge content addressable storage table
- L50 _public method_ `public abstract void RegisterDisallowedPath(string path)` — Register disallowed paths for clients to download
- L55 _public method_ `public abstract void PreloadCasTable()` — Preload cas table (otherwise it will be loaded on demand which might stall)
- L64-67 _public method_ `public static IStorageServer CreateStorageServer(IServer server, ILogger logger, StorageServerCreateInfo info)` — Create a IStorageServer object

### `Source/Programs/Shared/EpicGames.UBA/ITrace.cs` (EpicGames.UBA)


#### interface `EpicGames.UBA.ITrace`  
`public interface ITrace : IBaseInterface`  
_public; L10-75_
- inherits: `IBaseInterface`
- desc: Trace interface
- L15 _public property_ `public abstract string? Path { get; }` — The path to the trace file on disk, if any.
- L23 _public method_ `public abstract uint TaskBegin(string description, string details)` — Begin task. Will create a bar in uba visualizer
- L30 _public method_ `public abstract void TaskHint(uint taskId, string hint)` — Add hint to task. will show with milliseconds since start or previous hint
- L36 _public method_ `public abstract void TaskEnd(uint taskId)` — End task.
- L46 _public method_ `public abstract void UpdateStatus(uint statusRow, uint statusColumn, string statusText, LogEntryType statusType, string? statusLink = null)` — Writes external status to the uba trace stream which can then be visualized by ubavisualizer
- L55-69 _public method_ `public static ITrace Create(string? name = null, string? traceFile = null, bool makeGlobal = false, string? channel = "Default")` — Creates a new trace
- L74 _public property_ `public static ITrace? GlobalTrace => ...` — Get the global trace if there is one

#### struct `EpicGames.UBA.TraceTaskScope`  
`public readonly struct TraceTaskScope : IDisposable`  
_public; L80-104_
- inherits: `IDisposable`
- desc: Helper type to track task in scope
- L82 _private field_ `private readonly ITrace _trace`
- L83 _private field_ `private readonly uint _taskId`
- L91-95 _public ctor_ `public TraceTaskScope(ITrace trace, string description, string details)` — Will create a bar in uba visualizer
- L100-103 _public method_ `public void Dispose()` — End task

### `Source/Programs/Shared/EpicGames.UBA/Impl/CacheClientImpl.cs` (EpicGames.UBA)


#### class `EpicGames.UBA.Impl.CacheClientImpl`  
`internal class CacheClientImpl : ICacheClient`  
_internal; L11-173_
- inherits: `ICacheClient`
- L13 _private* field_ `nint _handle = IntPtr.Zero`
- L14 _private* field_ `readonly ISessionServer _sessionServer`
- L16 _public delegate_ `public delegate void ExitCallback(nint userData, nint handle)`
- L20 _private* method_ `static extern nint ProcessStartInfo_Create2(string application, string arguments, string workingDir, string description, uint priorityClass, ulong rootsHandle, byte trackInputs, string logFile, ExitCallback? exit)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L23 _private* method_ `static extern void ProcessStartInfo_Destroy(nint server)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L26 _private* method_ `static extern nint CacheClient_Create(nint session, byte reportMissReason, string crypto, string hint)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L29 _private* method_ `static extern byte CacheClient_Connect(nint cacheClient, string host, int port)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L32 _private* method_ `static extern void CacheClient_Disconnect(nint cacheClient)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L35 _private* method_ `static extern byte CacheClient_WriteToCache2(nint cacheClient, uint bucket, nint info, byte[] inputs, uint inputsSize, byte[] outputs, uint outputsSize)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L38 _private* method_ `static extern nint CacheClient_FetchFromCache3(nint cacheClient, ulong rootsHandle, uint bucket, nint info)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L41 _private* method_ `static extern nint CacheResult_GetLogLine(nint result, uint index)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L44 _private* method_ `static extern uint CacheResult_GetLogLineType(nint result, uint index)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L47 _private* method_ `static extern void CacheResult_Delete(nint result)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L50 _private* method_ `static extern void CacheClient_RequestServerShutdown(nint cacheClient, string reason)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L53 _private* method_ `static extern void CacheClient_Destroy(nint cacheClient)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L56 _private* method_ `static extern byte CacheClient_RegisterPathHash(nint cacheClient, string path, string hashString)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L61 _private* dtor_ `~CacheClientImpl()`
- L63-67 _public method_ `public void Dispose()`
- L69-84 _protected method_ `protected virtual void Dispose(bool disposing)`
- L87-91 _public ctor_ `public CacheClientImpl(ISessionServer server, bool reportMissReason, string crypto, string hint)`
- L93-113 _public method_ `public bool Connect(string host, int port, int desiredConnectionCount)`
- L115-123 _public method_ `public void Disconnect()`
- L125-131 _public method_ `public void PopulatePathHashes()`
- L133-136 _public method_ `public bool WriteToCache(uint bucket, nint processHandle, byte[] inputs, uint inputsSize, byte[] outputs, uint outputsSize)`
- L138-163 _public method_ `public FetchFromCacheResult FetchFromCache(ulong rootsHandle, uint bucket, ProcessStartInfo info)`
- L165-168 _public method_ `public void RequestServerShutdown(string reason)`
- L170 _public method_ `public nint GetHandle()`
- L172 _private field_ `private List<Task>? _connectingTasks = null`

### `Source/Programs/Shared/EpicGames.UBA/Impl/ConfigImpl.cs` (EpicGames.UBA)


#### class `EpicGames.UBA.Impl.ConfigImpl`  
`internal class ConfigImpl : IConfig`  
_internal; L8-52_
- inherits: `IConfig`
- L12 _private* method_ `static extern nint Config_Load(string configFile)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L14 _private* method_ `static extern nint Config_AddTable(nint config, string name)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L16 _private* method_ `static extern nint ConfigTable_AddValueString(nint table, string name, string value)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L19 _private* field_ `readonly nint _handle = IntPtr.Zero`
- L21-24 _public ctor_ `public ConfigImpl(string configFile)`
- L26-30 _public method_ `public void AddValue(string table, string name, string value)`
- L33 _private* dtor_ `~ConfigImpl()`
- L35-39 _public method_ `public void Dispose()`
- L41-48 _protected method_ `protected virtual void Dispose(bool disposing)`
- L51 _public method_ `public nint GetHandle()`

### `Source/Programs/Shared/EpicGames.UBA/Impl/LoggerImpl.cs` (EpicGames.UBA)


#### class `EpicGames.UBA.Impl.LoggerImpl`  
`internal class LoggerImpl : ILogger`  
_internal; L14-115_
- inherits: `ILogger`
- desc: Logger implementation which logs to an ILogger
- L16 _private* delegate_ `delegate void BeginScopeCallback()`
- L17 _private* delegate_ `delegate void EndScopeCallback()`
- L18 _private* delegate_ `delegate void LogCallback(LogEntryType type, nint str, uint len)`
- L20 _private* field_ `nint _handle = IntPtr.Zero`
- L21 _private* field_ `readonly Microsoft.Extensions.Logging.ILogger _logger`
- L22 _private* field_ `readonly BeginScopeCallback _beginScopeCallbackDelegate`
- L23 _private* field_ `readonly EndScopeCallback _endScopeCallbackDelegate`
- L24 _private* field_ `readonly LogCallback _logCallbackDelegate`
- L25 _private* field_ `readonly Lock _lock = new()`
- L29 _private* method_ `static extern nint CreateCallbackLogWriter(BeginScopeCallback begin, EndScopeCallback end, LogCallback log)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L32 _private* method_ `static extern void DestroyCallbackLogWriter(nint logger)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L35-52 _public ctor_ `public LoggerImpl(Microsoft.Extensions.Logging.ILogger logger, bool makeGlobal)`
- L54 _internal property_ `internal static LoggerImpl? GlobalLoggerImpl { set; get; }`
- L57 _private* dtor_ `~LoggerImpl()`
- L60-64 _public method_ `public void Dispose()` — (inheritdoc)
- L66-77 _protected method_ `protected virtual void Dispose(bool disposing)`
- L82 _public method_ `public nint GetHandle()` — (inheritdoc)
- L85 _public method_ `public void BeginScope()` — (inheritdoc)
- L88 _public method_ `public void EndScope()` — (inheritdoc)
- L91-98 _public method_ `public void Log(LogEntryType type, string message)` — (inheritdoc)
- L101 _private* method_ `void Log(LogEntryType type, nint ptr, uint len)`
- L103-114 _private* method_ `static LogLevel LogEntryTypeToLogLevel(LogEntryType type)`

### `Source/Programs/Shared/EpicGames.UBA/Impl/NullLogger.cs` (EpicGames.UBA)


#### class `EpicGames.UBA.Impl.NullLogger`  
`internal class NullLogger : ILogger`  
_internal; L11-39_
- inherits: `ILogger`
- desc: Logger implementation which discards output
- L15 _private* method_ `static extern nint LogWriter_GetNull()` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L19 _public method_ `public void BeginScope()` — (inheritdoc)
- L22 _public method_ `public void EndScope()` — (inheritdoc)
- L25 _public method_ `public void Log(LogEntryType type, string message)` — (inheritdoc)
- L28 _public method_ `public nint GetHandle()` — (inheritdoc)
- L31-35 _public method_ `public void Dispose()` — (inheritdoc)
- L38 _protected method_ `protected virtual void Dispose(bool disposing)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.UBA/Impl/ProcessImpl.cs` (EpicGames.UBA)


#### class `EpicGames.UBA.Impl.ProcessStartInfoImpl`  
`internal class ProcessStartInfoImpl : IProcessStartInfo`  
_internal; L10-71_
- inherits: `IProcessStartInfo`
- L12 _private* field_ `nint _handle = IntPtr.Zero`
- L13 _public delegate_ `public delegate void ExitCallback(nint userData, nint handle)`
- L14 _public event_ `public event ExitCallback? ExitCallbackDelegate`
- L15 _public property_ `public ProcessImpl? Process { get; set; }`
- L19 _private* method_ `static extern nint ProcessStartInfo_Create2(string application, string arguments, string workingDir, string description, uint priorityClass, ulong rootsHandle, byte trackInputs, string logFile, ExitCallback? exit)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L22 _private* method_ `static extern void ProcessStartInfo_Destroy(nint server)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L25-33 _public ctor_ `public ProcessStartInfoImpl(ProcessStartInfo info, bool needCallback)`
- L35-43 _private* method_ `void RaiseExited(nint userData, nint handle)`
- L46 _private* dtor_ `~ProcessStartInfoImpl()`
- L48-52 _public method_ `public void Dispose()`
- L54-65 _protected method_ `protected virtual void Dispose(bool disposing)`
- L69 _public method_ `public nint GetHandle()`

#### class `EpicGames.UBA.Impl.ProcessImpl`  
`internal class ProcessImpl : IProcess`  
_internal; L73-178_
- inherits: `IProcess`
- L75 _private* field_ `nint _handle = IntPtr.Zero`
- L77 _private* field_ `readonly IProcessStartInfo _processStartInfo` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("CodeQuality", "IDE0052:Remove unread private members", Justification = "maintain unmanaged reference")]`
- L81 _private* method_ `static extern uint ProcessHandle_GetExitCode(nint process)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L84 _private* method_ `static extern nint ProcessHandle_GetExecutingHost(nint process)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L87 _private* method_ `static extern nint ProcessHandle_GetLogLine(nint process, uint index)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L90 _private* method_ `static extern ulong ProcessHandle_GetTotalProcessorTime(nint process)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L93 _private* method_ `static extern ulong ProcessHandle_GetTotalWallTime(nint process)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L96 _private* method_ `static extern ulong ProcessHandle_GetHash(nint process)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L99 _private* method_ `static extern void ProcessHandle_Cancel(nint process, byte terminate)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L102 _private* method_ `static extern void DestroyProcessHandle(nint process)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L105-115 _public ctor_ `public ProcessImpl(nint handle, IProcessStartInfo info, IProcess.ExitedEventHandler? exitedEventHandler, object? userData)`
- L118 _private* dtor_ `~ProcessImpl()`
- L120-124 _public method_ `public void Dispose()`
- L126-137 _protected method_ `protected virtual void Dispose(bool disposing)`
- L141 _public method_ `public nint GetHandle()`
- L142 _public event_ `public event IProcess.ExitedEventHandler? Exited`
- L144 _public property_ `public int ExitCode => ...`
- L146 _public property_ `public string? ExecutingHost => ...`
- L148-161 _public property_ `public List<string> LogLines { get; }`
- L163 _public property_ `public TimeSpan TotalProcessorTime => ...`
- L165 _public property_ `public TimeSpan TotalWallTime => ...`
- L167 _public property_ `public ulong Hash => ...`
- L169 _public property_ `public object? UserData { get; }`
- L171 _public method_ `public void Cancel(bool terminate)`
- L174-177 _internal method_ `internal void RaiseExited()`

### `Source/Programs/Shared/EpicGames.UBA/Impl/SchedulerImpl.cs` (EpicGames.UBA)


#### class `EpicGames.UBA.Impl.ProcessFinishedInfoImpl`  
`internal class ProcessFinishedInfoImpl : IProcessFinishedInfo`  
_internal; L11-66_
- inherits: `IProcessFinishedInfo`
- L15 _private* method_ `static extern uint ProcessHandle_GetExitCode(nint process)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L18 _private* method_ `static extern byte ProcessHandle_GetExecutionType(nint process)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L21 _private* method_ `static extern nint ProcessHandle_GetExecutingHost(nint process)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L24 _private* method_ `static extern nint ProcessHandle_GetLogLine(nint process, uint index)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L27 _private* method_ `static extern ulong ProcessHandle_GetTotalProcessorTime(nint process)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L30 _private* method_ `static extern ulong ProcessHandle_GetTotalWallTime(nint process)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L33 _private* method_ `static extern ulong ProcessHandle_GetPeakMemory(nint process)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L36-40 _internal ctor_ `internal ProcessFinishedInfoImpl(object userData, nint processHandle)`
- L41 _private* field_ `readonly object _userData`
- L42 _private* field_ `readonly nint _processHandle`
- L44 _public property_ `public ProcessExecutionType ExecutionType => ...`
- L45 _public property_ `public int ExitCode => ...`
- L46-59 _public property_ `public List<string> LogLines { get; }`
- L60 _public property_ `public string? ExecutingHost => ...`
- L61 _public property_ `public TimeSpan TotalProcessorTime => ...`
- L62 _public property_ `public TimeSpan TotalWallTime => ...`
- L63 _public property_ `public ulong PeakMemoryUsed => ...`
- L64 _public property_ `public object UserData => ...`
- L65 _public property_ `public nint ProcessHandle => ...`

#### class `EpicGames.UBA.Impl.SchedulerProcess`  
`internal class SchedulerProcess`  
_internal; L68-103_
- L72 _private* method_ `static extern nint ProcessStartInfo_Create2(string application, string arguments, string workingDir, string description, uint priorityClass, ulong rootsHandle, byte trackInputs, string logFile, ExitCallback? exit)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L75-81 _public ctor_ `public SchedulerProcess(SchedulerImpl scheduler, ProcessStartInfo info, object userData)`
- L83-95 _private* method_ `void RaiseExited(nint userData, nint processHandle, ref byte exitedResponse)`
- L97 _public delegate_ `public delegate void ExitCallback(nint userData, nint processHandle, ref byte exitedResponse)`
- L98 _private* field_ `readonly SchedulerImpl _scheduler`
- L99 _private* field_ `readonly object _userData`
- L100 _private* event_ `event ExitCallback ExitCallbackDelegate`
- L101 _public field_ `public nint _startInfoHandle`
- L102 _public field_ `public uint _index = UInt32.MaxValue`

#### class `EpicGames.UBA.Impl.SchedulerImpl`  
`internal class SchedulerImpl : IScheduler`  
_internal; L105-223_
- inherits: `IScheduler`
- L109 _private* method_ `static extern nint Scheduler_Create3(nint session, nint[] cacheClients, uint cacheClientCount, nint config)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L112 _private* method_ `static extern void Scheduler_Destroy(nint scheduler)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L115 _private* method_ `static extern void Scheduler_Start(nint scheduler)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L118 _private* method_ `static extern void Scheduler_Cancel(nint scheduler)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L121 _private* method_ `static extern byte Scheduler_IsEmpty(nint scheduler)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L124 _private* method_ `static extern uint Scheduler_EnqueueProcess4(nint scheduler, nint info, float weight, byte canDetour, byte canExecuteRemotely, byte canCrossArchitecture, byte canCrossPlatform, int[]? dependencies, int dependencyCount, byte[]? knownInputs, int knownInputsBytes, uint knownInputsCount, uint cacheBucket, uint memoryGroup, ulong predictedMemoryUsage)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L127 _private* method_ `static extern float Scheduler_GetProcessWeightThatCanRunRemotelyNow2(nint scheduler, out float totalWeight, out float crossArchitecture, out float crossPlatform)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L130 _private* method_ `static extern float Scheduler_SetAllowDisableRemoteExecution(nint scheduler, byte allow)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L133 _private* field_ `nint _schedulerHandle = IntPtr.Zero`
- L134 _internal field_ `internal Func<IProcessFinishedInfo, ProcessFinishedResponse>? _processFinishedCallback`
- L134 _internal field_ `internal Func< _processFinishedCallback`
- L135 _private* field_ `readonly List<SchedulerProcess> _processes = []`
- L137-152 _internal ctor_ `internal SchedulerImpl(ISessionServer server, IEnumerable<ICacheClient> cacheClients, IConfig config, int maxLocalProcessors, bool forceRemote)`
- L154-157 _public method_ `public void Start()`
- L159-169 _public method_ `public uint EnqueueProcess(ProcessStartInfo info, double weight, bool canDetour, bool canExecuteRemotely, bool canCrossArchitecture, bool canCrossPlatform, int[]? dependencies, byte[]? knownInputs, uint knownInputsCount, uint cacheBucket, uint memoryGroup, ulong predictedMemoryUsage, object userData)`
- L171-174 _public method_ `public void Cancel()`
- L176-179 _public method_ `public void SetProcessFinishedCallback(Func<IProcessFinishedInfo, ProcessFinishedResponse> processFinished)`
- L181-184 _public method_ `public void SetAllowDisableRemoteExecution()`
- L186 _public property_ `public bool IsEmpty => ...`
- L188-197 _public method_ `public void GetProcessWeightThatCanRunRemotelyNow(out double totalWeight, out double crossArchitecture, out double crossPlatform)`
- L199 _public method_ `public nint GetHandle()`
- L202 _private* dtor_ `~SchedulerImpl()`
- L204-208 _public method_ `public void Dispose()`
- L210-221 _protected method_ `protected virtual void Dispose(bool disposing)`

### `Source/Programs/Shared/EpicGames.UBA/Impl/ServerImpl.cs` (EpicGames.UBA)


#### class `EpicGames.UBA.Impl.ServerImpl`  
`internal class ServerImpl : IServer`  
_internal; L8-93_
- inherits: `IServer`
- L10 _private* field_ `nint _handle = IntPtr.Zero`
- L11 _private* field_ `readonly ILogger _logger`
- L15 _private* method_ `static extern nint NetworkServer_Create(nint logger, int workerCount, int sendSize, int receiveTimeoutSeconds, byte useQuic)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L18 _private* method_ `static extern void NetworkServer_Destroy(nint server)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L22 _private* method_ `static extern byte NetworkServer_StartListen(nint server, int port, string ip, string crypto)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L25 _private* method_ `static extern byte NetworkServer_AddClient(nint server, string ip, int port, string crypto)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L28 _private* method_ `static extern byte NetworkServer_AddNamedConnection(nint server, string name)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L31 _private* method_ `static extern byte NetworkServer_SetClientsConfig(nint server, nint config)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L34 _private* method_ `static extern byte NetworkServer_Stop(nint server)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L36 _private* const_ `const int DEFAULT_PORT = 1345`
- L39-44 _public ctor_ `public ServerImpl(int maxWorkers, int sendSize, ILogger logger, bool useQuic)`
- L47 _private* dtor_ `~ServerImpl()`
- L50-54 _public method_ `public void Dispose()` — (inheritdoc)
- L56-67 _protected method_ `protected virtual void Dispose(bool disposing)`
- L72 _public method_ `public nint GetHandle()` — (inheritdoc)
- L75 _public method_ `public bool StartServer(string ip = "", int port = -1, string crypto = "")` — (inheritdoc)
- L78 _public method_ `public void StopServer()` — (inheritdoc)
- L81 _public method_ `public bool AddClient(string ip, int port, string crypto = "")` — (inheritdoc)
- L84 _public method_ `public bool AddNamedConnection(string name)` — (inheritdoc)
- L87-90 _public method_ `public void SetClientsConfig(IConfig config)` — (inheritdoc)

#### class `EpicGames.UBA.Impl.NullServer`  
`internal class NullServer : IServer`  
_internal; L98-120_
- inherits: `IServer`
- desc: Null server
- L101 _public method_ `public bool StartServer(string ip = "", int port = -1, string crypto = "")` — (inheritdoc)
- L103 _public method_ `public void StopServer()` — (inheritdoc)
- L105 _public method_ `public bool AddNamedConnection(string name)` — (inheritdoc)
- L107 _public method_ `public bool AddClient(string ip, int port, string crypto = "")` — (inheritdoc)
- L109 _public method_ `public void SetClientsConfig(IConfig config)` — (inheritdoc)
- L111 _public method_ `public nint GetHandle()` — (inheritdoc)
- L113-117 _public method_ `public void Dispose()` — (inheritdoc)
- L119 _protected method_ `protected virtual void Dispose(bool disposing)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.UBA/Impl/SessionServerImpl.cs` (EpicGames.UBA)


#### class `EpicGames.UBA.Impl.SessionServerCreateInfoImpl`  
`internal class SessionServerCreateInfoImpl : ISessionServerCreateInfo`  
_internal; L13-63_
- inherits: `ISessionServerCreateInfo`
- L15 _private* field_ `nint _handle = IntPtr.Zero`
- L16 _private* field_ `readonly IStorageServer _storage`
- L17 _private* field_ `readonly IServer _client`
- L18 _private* field_ `readonly ILogger _logger`
- L22 _private* method_ `static extern nint SessionServerCreateInfo_Create(nint storage, nint client, nint logger, string rootDir, string traceOutputFile, byte disableCustomAllocator, byte launchVisualizer, byte resetCas, byte writeToDisk, byte detailedTrace, byte allowWaitOnMem, byte allowKillOnMem, byte storeObjFilesCompressed)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L26 _private* method_ `static extern void SessionServerCreateInfo_Destroy(nint server)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L29-35 _public ctor_ `public SessionServerCreateInfoImpl(IStorageServer storage, IServer client, ILogger logger, SessionServerCreateInfo info)`
- L38 _private* dtor_ `~SessionServerCreateInfoImpl()`
- L40-44 _public method_ `public void Dispose()`
- L46-57 _protected method_ `protected virtual void Dispose(bool disposing)`
- L61 _public method_ `public nint GetHandle()`

#### class `EpicGames.UBA.Impl.SessionServerImpl`  
`internal class SessionServerImpl : ISessionServer`  
_internal; L65-288_
- inherits: `ISessionServer`
- L67 _private* delegate_ `delegate void RemoteProcessSlotAvailableCallback(nint userData, byte isCrossArchitecture)`
- L68 _private* delegate_ `delegate void RemoteProcessReturnedCallback(nint handle)`
- L70 _private* field_ `nint _handle = IntPtr.Zero`
- L71 _private* field_ `readonly ITrace _trace`
- L72 _private* field_ `readonly ISessionServerCreateInfo _info`
- L73 _private* field_ `readonly RemoteProcessSlotAvailableCallback _remoteProcessSlotAvailableCallbackDelegate`
- L74 _private* field_ `readonly RemoteProcessReturnedCallback _remoteProcessReturnedCallbackDelegate`
- L75 _private* field_ `readonly ConcurrentDictionary<ulong, IProcess> _remoteProcesses = ...`
- L75 _private* field_ `readonly ConcurrentDictionary< _remoteProcesses = new()`
- L79 _private* method_ `static extern nint SessionServer_Create(nint info, byte[] environment, uint environmentSize)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L82 _private* method_ `static extern void SessionServer_SetRemoteProcessAvailable(nint server, RemoteProcessSlotAvailableCallback func, nint userData)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L85 _private* method_ `static extern void SessionServer_SetRemoteProcessReturned(nint server, RemoteProcessReturnedCallback func)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L88 _private* method_ `static extern void SessionServer_RefreshDirectory(nint server, string directory)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L91 _private* method_ `static extern void SessionServer_RegisterNewFile(nint server, string filename)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L94 _private* method_ `static extern byte SessionServer_RegisterVirtualFile(nint server, string filename, string sourceFile, ulong sourceOffset, ulong sourceSize)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L97 _private* method_ `static extern uint SessionServer_BeginExternalProcess(nint server, string description)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L100 _private* method_ `static extern void SessionServer_EndExternalProcess(nint server, uint id, uint exitCode)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L103 _private* method_ `static extern void SessionServer_UpdateProgress(nint server, uint processesTotal, uint processesDone, uint errorCount)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L106 _private* method_ `static extern nint SessionServer_RunProcess(nint server, nint info, bool async, bool enableDetour)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L109 _private* method_ `static extern nint SessionServer_RunProcessRemote(nint server, nint info, float weight, byte[]? knownInputs, uint knownInputsCount, bool allowCrossArchitecture)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L112 _private* method_ `static extern ulong SessionServer_RegisterRoots(nint server, byte[] rootsData, uint rootsDataSize)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L115 _private* method_ `static extern void SessionServer_SetMaxRemoteProcessCount(nint server, uint count)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L118 _private* method_ `static extern void SessionServer_AddInfo(nint server, string info)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L121 _private* method_ `static extern void SessionServer_DisableRemoteExecution(nint server)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L124 _private* method_ `static extern byte SessionServer_DisableRemoteExecutionOnAgent(nint server, string agentName)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L127 _private* method_ `static extern void SessionServer_SetCustomCasKeyFromTrackedInputs(nint server, nint process, string filename, string workingdir)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L130 _private* method_ `static extern void SessionServer_RegisterCrossArchitectureMapping(nint server, string from, string to)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L133 _private* method_ `static extern void SessionServer_PrintSummary(nint server)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L136 _private* method_ `static extern void SessionServer_CancelAll(nint server)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L139 _private* method_ `static extern nint SessionServer_GetTrace(nint server)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L142 _private* method_ `static extern void SessionServer_Destroy(nint server)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L145-183 _public ctor_ `public SessionServerImpl(ISessionServerCreateInfo info)`
- L186 _private* dtor_ `~SessionServerImpl()`
- L188-192 _public method_ `public void Dispose()`
- L194-210 _protected method_ `protected virtual void Dispose(bool disposing)`
- L214 _public method_ `public nint GetHandle()`
- L216 _public event_ `public event ISessionServer.RemoteProcessSlotAvailableEventHandler? RemoteProcessSlotAvailable`
- L218 _public event_ `public event ISessionServer.RemoteProcessReturnedEventHandler? RemoteProcessReturned`
- L220-226 _public method_ `public IProcess RunProcess(ProcessStartInfo info, bool async, IProcess.ExitedEventHandler? exitedEventHandler, bool enableDetour)`
- L228-235 _public method_ `public IProcess RunProcessRemote(ProcessStartInfo info, IProcess.ExitedEventHandler? exitedEventHandler, double weight, byte[]? knownInputs, uint knownInputsCount, bool canExecuteCrossArchitecture)`
- L237 _public method_ `public ulong RegisterRoots(byte[] rootsData, uint rootsDataSize)`
- L239 _public method_ `public void DisableRemoteExecution()`
- L241 _public method_ `public bool DisableRemoteExecutionOnAgent(string agentName)`
- L243 _public method_ `public void AddInfo(string info)`
- L245 _public method_ `public void SetMaxRemoteProcessCount(uint count)`
- L247 _public method_ `public void RefreshDirectories(params string[] directories)`
- L249 _public method_ `public void RegisterNewFiles(params string[] files)`
- L250 _public method_ `public bool RegisterVirtualFile(string name, string sourceFile, ulong sourceOffset, ulong sourceSize)`
- L252 _public method_ `public uint BeginExternalProcess(string description)`
- L254 _public method_ `public void EndExternalProcess(uint id, uint exitCode)`
- L256 _public method_ `public void UpdateProgress(uint processesTotal, uint processesDone, uint errorCount)`
- L258 _public method_ `public void SetCustomCasKeyFromTrackedInputs(string file, string workingDirectory, IProcess process)`
- L260 _public method_ `public void PrintSummary()`
- L262 _public method_ `public void CancelAll()`
- L264 _public method_ `public ITrace GetTrace()`
- L268-271 _private* method_ `void RaiseRemoteProcessSlotAvailable(nint userData, byte isCrossArchitecture)`
- L273-287 _private* method_ `void RaiseRemoteProcessReturned(nint handle)`

### `Source/Programs/Shared/EpicGames.UBA/Impl/StorageServerImpl.cs` (EpicGames.UBA)


#### class `EpicGames.UBA.Impl.StorageServerImpl`  
`internal class StorageServerImpl : IStorageServer`  
_internal; L9-72_
- inherits: `IStorageServer`
- L11 _private* field_ `nint _handle = IntPtr.Zero`
- L12 _private* field_ `readonly IServer _server`
- L13 _private* field_ `readonly ILogger _logger`
- L17 _private* method_ `static extern nint StorageServer_Create(nint server, string rootDir, ulong casCapacityBytes, byte storeCompressed, nint logger, string zone)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L20 _private* method_ `static extern void StorageServer_Destroy(nint server)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L23 _private* method_ `static extern void StorageServer_SaveCasTable(nint server)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L26 _private* method_ `static extern void StorageServer_RegisterDisallowedPath(nint server, string path)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L29 _private* method_ `static extern void StorageServer_PreloadCasTable(nint server)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L32-38 _public ctor_ `public StorageServerImpl(IServer server, ILogger logger, StorageServerCreateInfo info)`
- L41 _private* dtor_ `~StorageServerImpl()`
- L43-47 _public method_ `public void Dispose()`
- L49-60 _protected method_ `protected virtual void Dispose(bool disposing)`
- L64 _public method_ `public nint GetHandle()`
- L66 _public method_ `public void SaveCasTable()`
- L68 _public method_ `public void RegisterDisallowedPath(string path)`
- L70 _public method_ `public void PreloadCasTable()`

### `Source/Programs/Shared/EpicGames.UBA/Impl/TraceImpl.cs` (EpicGames.UBA)


#### class `EpicGames.UBA.TraceImpl`  
`internal class TraceImpl : ITrace`  
_internal; L8-104_
- inherits: `ITrace`
- L10 _private* field_ `nint _handle = IntPtr.Zero`
- L11 _private* field_ `readonly string? _traceFile`
- L12 _private* field_ `readonly bool _ownsHandle = false`
- L16 _private* method_ `static extern uint Trace_TaskBegin(nint trace, string description, string details)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L19 _private* method_ `static extern void Trace_TaskHint(nint trace, uint taskId, string hint)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L22 _private* method_ `static extern void Trace_TaskEnd(nint trace, uint taskId, bool success)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L25 _private* method_ `static extern void Trace_UpdateStatus(nint trace, uint statusRow, uint statusColumn, string statusText, byte statusType, string? statusLink)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L28 _private* method_ `static extern nint Trace_Create(string? name, string? channel)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L31 _private* method_ `static extern void Trace_Destroy(nint trace, string? writeFile)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L34 _private* method_ `static extern void Trace_SetGlobal(nint trace)` — attrs: `[DllImport("UbaHost", CharSet = CharSet.Auto)]`
- L37-40 _internal ctor_ `internal TraceImpl(nint handle)`
- L42-58 _internal ctor_ `internal TraceImpl(string? name, string? traceFile, bool makeGlobal, string? channel)`
- L60 _internal property_ `internal static TraceImpl? GlobalTraceImpl { set; get; }`
- L63 _private* dtor_ `~TraceImpl()`
- L65-69 _public method_ `public void Dispose()`
- L71-90 _protected method_ `protected virtual void Dispose(bool disposing)`
- L93 _public property_ `public string? Path => ...`
- L95 _public method_ `public nint GetHandle()`
- L97 _public method_ `public uint TaskBegin(string description, string details)`
- L99 _public method_ `public void TaskHint(uint taskId, string hint)`
- L101 _public method_ `public void TaskEnd(uint taskId)`
- L103 _public method_ `public void UpdateStatus(uint statusRow, uint statusColumn, string statusText, LogEntryType statusType, string? statusLink)`

#### class `EpicGames.UBA.TraceNull`  
`internal class TraceNull : ITrace`  
_internal; L106-115_
- inherits: `ITrace`
- L108 _public method_ `public nint GetHandle()`
- L109 _public method_ `public void Dispose()`
- L110 _public property_ `public string? Path => ...`
- L111 _public method_ `public uint TaskBegin(string description, string details)`
- L112 _public method_ `public void TaskHint(uint taskId, string hint)`
- L113 _public method_ `public void TaskEnd(uint taskId)`
- L114 _public method_ `public void UpdateStatus(uint statusRow, uint statusColumn, string statusText, LogEntryType statusType, string? statusLink = null)`

### `Source/Programs/Shared/EpicGames.UBA/Utils.cs` (EpicGames.UBA)


#### class `EpicGames.UBA.Utils`  
`public static partial class Utils`  
_public; L17-154_
- desc: Utils
- L22 _public method_ `public static bool IsAvailable()` — Is UBA available?
- L23 _private* field_ `static readonly Lazy<bool> s_available = new(() => File.Exists(GetLibraryPath()))`
- L29 _public property_ `public static IEnumerable<DirectoryReference> DisallowedPaths => ...` — Paths that are not allowed to be transferred over the network for UBA remote agents.
- L30 _private* field_ `static readonly ConcurrentBag<DirectoryReference> s_disallowedPaths = []`
- L36 _public property_ `public static IEnumerable<KeyValuePair<DirectoryReference, DirectoryReference>> CrossArchitecturePaths => ...` — Mapping of binary paths for cross architecture host binaries, to allow for using helpers of a different architecture.
- L37 _private* field_ `static readonly ConcurrentDictionary<DirectoryReference, DirectoryReference> s_crossArchitecturePaths = ...`
- L37 _private* field_ `static readonly ConcurrentDictionary< s_crossArchitecturePaths = []`
- L42 _public property_ `public static IEnumerable<KeyValuePair<DirectoryReference, string>> PathHashes => ...` — Mapping of a folder path to a single hash, to allow for hashing an entire folder so each individual file does not need to be processed.
- L43 _private* field_ `static readonly ConcurrentDictionary<DirectoryReference, string> s_pathHashes = ...`
- L43 _private* field_ `static readonly ConcurrentDictionary< s_pathHashes = []`
- L49-63 _public method_ `public static void RegisterDisallowedPaths(params DirectoryReference[] paths)` — Registers a path that is not allowed to be transferred over the network for UBA remote agents.
- L70-78 _public method_ `public static void RegisterCrossArchitecturePath(DirectoryReference path, DirectoryReference crossPath)` — Registers a path mapping for cross architecture binaries
- L85-92 _public method_ `public static void RegisterPathHash(DirectoryReference path, string hash)` — Registers a hash for a path
- L99 _public delegate_ `public delegate void DisallowedPathRegisteredEventHandler(IEnumerable<DirectoryReference> sender, DisallowedPathRegisteredEventArgs e)` — Delegate for registering a remote disallowed path
- L106 _public delegate_ `public delegate void CrossArchitecturePathRegisteredEventHandler(IEnumerable<KeyValuePair<DirectoryReference, DirectoryReference>> sender, CrossArchitecturePathRegisteredEventArgs e)` — Delegate for registering a cross architecture path
- L113 _public delegate_ `public delegate void PathHashRegisteredEventHandler(IEnumerable<KeyValuePair<DirectoryReference, string>> sender, PathHashRegisteredEventArgs e)` — Delegate for registering a path hash
- L118 _public event_ `public static event DisallowedPathRegisteredEventHandler? DisallowedPathRegistered` — Remote disallowed path registered event handler
- L123 _public event_ `public static event CrossArchitecturePathRegisteredEventHandler? CrossArchitecturePathRegistered` — Cross architecture path registered event handler
- L128 _public event_ `public static event PathHashRegisteredEventHandler? PathHashRegistered` — Remote disallowed path registered event handler
- L136-153 _private* method_ `static string GetLibraryPath()` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Globalization", "CA1308:Normalize strings to uppercase", Justification = "folder path is lowercase")]` — Get the path to the p/invoke library that would be loaded

#### class `EpicGames.UBA.DisallowedPathRegisteredEventArgs`  
`public sealed class DisallowedPathRegisteredEventArgs(params DirectoryReference[] paths) : EventArgs`  
_public; L159-165_
- desc: Event args for registering a remote disallowed path
- L164 _public property_ `public IEnumerable<DirectoryReference> Paths { get; }` — The paths being registered

#### class `EpicGames.UBA.CrossArchitecturePathRegisteredEventArgs`  
`public sealed class CrossArchitecturePathRegisteredEventArgs(DirectoryReference path, DirectoryReference crossPath) : EventArgs`  
_public; L170-181_
- desc: Event args for registering a cross architecture path
- L175 _public property_ `public DirectoryReference Path { get; }` — The host architecture path being registered
- L180 _public property_ `public DirectoryReference CrossPath { get; }` — The cross architecture path being registered

#### class `EpicGames.UBA.PathHashRegisteredEventArgs`  
`public sealed class PathHashRegisteredEventArgs(DirectoryReference path, string hash) : EventArgs`  
_public; L186-197_
- desc: Event args for registering a path hash
- L191 _public property_ `public DirectoryReference Path { get; }` — The path being registered
- L196 _public property_ `public string Hash { get; }` — The hash for the path being registered
