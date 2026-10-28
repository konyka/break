# CSharp / JobDriver

- project root: `Source/Programs/Horde/Drivers/JobDriver`
- files: 26; symbols: 604
- symbol kinds: class=64, const=15, ctor=46, enum=2, enumerator=7, field=89, interface=3, method=200, property=174, record=4
- access marked `*` is implicit (not written in source)

### `Source/Programs/Horde/Drivers/JobDriver/Commands/Execution/ExecuteConformCommand.cs` (JobDriver)


#### class `JobDriver.Commands.Execution.ExecuteConformCommand`  
`class ExecuteConformCommand : Command`  
_internal*; L17-60_
- attrs: `[Command("Execute", "Conform", "Executes a conform")]`
- inherits: `Command`
- L20 _public property_ `public AgentId AgentId { get; set; }` — attrs: `[CommandLine("-AgentId=", Required = true)]`
- L23 _public property_ `public SessionId SessionId { get; set; }` — attrs: `[CommandLine("-SessionId=", Required = true)]`
- L26 _public property_ `public LeaseId LeaseId { get; set; }` — attrs: `[CommandLine("-LeaseId", Required = true)]`
- L29 _public property_ `public string Task { get; set; }` — attrs: `[CommandLine("-Task=", Required = true)]`
- L32 _public property_ `public DirectoryReference WorkingDir { get; set; }` — attrs: `[CommandLine("-WorkingDir=", Required = true)]`
- L34 _private* field_ `readonly HordeClientFactory _hordeClientFactory`
- L35 _private* field_ `readonly IEnumerable<IWorkspaceMaterializerFactory> _materializerFactories`
- L36 _private* field_ `readonly IOptions<DriverSettings> _driverSettings`
- L37 _private* field_ `readonly Tracer _tracer`
- L39-45 _public ctor_ `public ExecuteConformCommand(HordeClientFactory hordeClientFactory, IEnumerable<IWorkspaceMaterializerFactory> materializerFactories, IOptions<DriverSettings> driverSettings, Tracer tracer)`
- L47-59 _public method_ `public override async Task<int> ExecuteAsync(ILogger logger)`

### `Source/Programs/Horde/Drivers/JobDriver/Commands/Execution/ExecuteJobCommand.cs` (JobDriver)


#### class `JobDriver.Commands.Execution.ExecuteJobCommand`  
`class ExecuteJobCommand : Command`  
_internal*; L16-55_
- attrs: `[Command("Execute", "Job", "Executes a job")]`
- inherits: `Command`
- L19 _public property_ `public AgentId AgentId { get; set; }` — attrs: `[CommandLine("-AgentId=", Required = true)]`
- L22 _public property_ `public SessionId SessionId { get; set; }` — attrs: `[CommandLine("-SessionId=", Required = true)]`
- L25 _public property_ `public LeaseId LeaseId { get; set; }` — attrs: `[CommandLine("-LeaseId", Required = true)]`
- L28 _public property_ `public string Task { get; set; }` — attrs: `[CommandLine("-Task=", Required = true)]`
- L31 _public property_ `public DirectoryReference WorkingDir { get; set; }` — attrs: `[CommandLine("-WorkingDir=", Required = true)]`
- L33 _private* field_ `readonly HordeClientFactory _hordeClientFactory`
- L34 _private* field_ `readonly IEnumerable<IJobExecutorFactory> _jobExecutorFactories`
- L35 _private* field_ `readonly IOptions<DriverSettings> _driverSettings`
- L37-42 _public ctor_ `public ExecuteJobCommand(HordeClientFactory hordeClientFactory, IEnumerable<IJobExecutorFactory> jobExecutorFactories, IOptions<DriverSettings> driverSettings)`
- L44-54 _public method_ `public override async Task<int> ExecuteAsync(ILogger logger)`

### `Source/Programs/Horde/Drivers/JobDriver/Commands/Parse/ParseCommand.cs` (JobDriver)


#### class `JobDriver.Commands.Parse.ParseCommand`  
`class ParseCommand : Command`  
_internal*; L15-83_
- attrs: `[Command("parse", "Parses a file into structured logging output")]`
- inherits: `Command`
- desc: Installs the agent as a service
- L19 _private* property_ `FileReference InputFile { get; set; }` — attrs: `[CommandLine("-File=", Required = true)] [Description("Log file to parse rather than executing an external program.")]`
- L23 _private* property_ `FileReference? IgnorePatternsFile { get; set; }` — attrs: `[CommandLine("-Ignore=")] [Description("Path to a file containing error patterns to ignore, one regex per line.")]`
- L27 _private* property_ `DirectoryReference? WorkspaceDir { get; set; }` — attrs: `[CommandLine("-WorkspaceDir=")] [Description("The root workspace directory")]`
- L31 _private* property_ `string? Stream { get; set; }` — attrs: `[CommandLine("-Stream=")] [Description("The stream synced to the workspace")]`
- L35 _private* property_ `int? Change { get; set; }` — attrs: `[CommandLine("-Change=")] [Description("The changelist number that has been synced")]`
- L37-82 _public method_ `public override async Task<int> ExecuteAsync(ILogger logger)`

### `Source/Programs/Horde/Drivers/JobDriver/Commands/Utilities/BuildGraphCommand.cs` (JobDriver)


#### class `JobDriver.Commands.Utilities.BuildGraphCommand`  
`class BuildGraphCommand : Command`  
_internal*; L14-80_
- attrs: `[Command("buildgraph", "Executes a BuildGraph script with the given arguments using a build of UAT within the current branch, and runs the output through the log processor")]`
- inherits: `Command`
- desc: Runs a BuildGraph script and captures the processed log output
- L16 _private* field_ `readonly List<string> _arguments = new List<string>()`
- L19-29 _public method_ `public override void Configure(CommandLineArguments arguments, ILogger logger)` — (inheritdoc)
- L32-79 _public method_ `public override async Task<int> ExecuteAsync(ILogger logger)` — (inheritdoc)

### `Source/Programs/Horde/Drivers/JobDriver/DriverApp.cs` (JobDriver)


#### class `JobDriver.DriverApp`  
`public static class DriverApp`  
_public; L18-96_
- desc: Application class for the job driver
- L23-48 _public method_ `public static async Task<int> Main(string[] args)` — Main entry point
- L54-95 _public method_ `public static void RegisterServices(IServiceCollection services)` — Helper method to register services for this app

### `Source/Programs/Horde/Drivers/JobDriver/DriverSettings.cs` (JobDriver)


#### class `JobDriver.DriverSettings`  
`class DriverSettings`  
_internal*; L12-38_
- desc: Settings for the driver
- L17 _public property_ `public string Executor { get; set; }` — The executor to use for jobs
- L22 _public property_ `public bool UseWine { get; set; }` — Whether to use Wine for executing the job. This normally is configured via RpcJobOptions
- L27 _public property_ `public LocalExecutorSettings LocalExecutor { get; set; }` — Settings for the local executor
- L32 _public property_ `public PerforceExecutorSettings PerforceExecutor { get; set; }` — Settings for the perforce executor
- L37 _public property_ `public List<ProcessToTerminate> ProcessesToTerminate { get; }` — List of process names to terminate after a lease completes, but not after a job step

#### class `JobDriver.ProcessToTerminate`  
`public class ProcessToTerminate`  
_public; L43-54_
- desc: Specifies a process to terminate
- L48 _public property_ `public string Name { get; set; }` — Name of the process
- L53 _public property_ `public List<TerminateCondition>? When { get; init; }` — When to terminate this process

### `Source/Programs/Horde/Drivers/JobDriver/Execution/ConformExecutor.cs` (JobDriver)


#### class `JobDriver.Execution.ConformExecutor`  
`class ConformExecutor`  
_internal*; L16-143_
- L18 _private* field_ `readonly IHordeClient _hordeClient`
- L19 _private* field_ `readonly DirectoryReference _workingDir`
- L20 _private* field_ `readonly AgentId _agentId`
- L21 _private* field_ `readonly LeaseId _leaseId`
- L22 _private* field_ `readonly IEnumerable<IWorkspaceMaterializerFactory> _materializerFactories`
- L23 _private* field_ `readonly ConformTask _conformTask`
- L24 _private* field_ `readonly DriverSettings _driverSettings`
- L25 _private* field_ `readonly Tracer _tracer`
- L26 _private* field_ `readonly ILogger _logger`
- L28-40 _public ctor_ `public ConformExecutor(IHordeClient hordeClient, IEnumerable<IWorkspaceMaterializerFactory> materializerFactories, DirectoryReference workingDir, AgentId agentId, LeaseId leaseId, ConformTask conformTask, DriverSettings driverSettings, Tracer tracer, ILogger logger)`
- L42-53 _public method_ `public async Task ExecuteAsync(CancellationToken cancellationToken)`
- L55-142 _private* method_ `async Task ExecuteInternalAsync(CancellationToken cancellationToken)`

### `Source/Programs/Horde/Drivers/JobDriver/Execution/DefaultSystemMetrics.cs` (JobDriver)


#### class `JobDriver.Execution.DefaultSystemMetrics`  
`public class DefaultSystemMetrics : ISystemMetrics`  
_public; L13-74_
- inherits: `ISystemMetrics`
- desc: Implementation of ISystemMetrics
- L15 _private field_ `private readonly DirectoryReference? _workingDir`
- L16 _private field_ `private readonly ILogger _logger`
- L23-27 _public ctor_ `public DefaultSystemMetrics(DirectoryReference? workingDir, ILogger logger)` — Constructor
- L30 _public method_ `public CpuMetrics? GetCpu()` — (inheritdoc)
- L33 _public method_ `public CpuTimeMetrics? GetCpuTime()` — (inheritdoc)
- L36 _public method_ `public MemoryMetrics? GetMemory()` — (inheritdoc)
- L39 _public method_ `public DiskMetrics? GetWorkingDisk()` — (inheritdoc)
- L42 _public method_ `public DiskMetrics? GetSystemDisk()` — (inheritdoc)
- L49-73 _private method_ `private DiskMetrics? GetDisk(EpicGames.Horde.Agents.Metrics.DriveType type)` — Fetches root directory metrics based off drive classification

### `Source/Programs/Horde/Drivers/JobDriver/Execution/JobExecutor.cs` (JobDriver)


#### record `JobDriver.Execution.JobStepInfo`  
`public record class JobStepInfo ( JobStepId StepId, LogId LogId, string Name, IReadOnlyDictionary<string, string> Credentials, IReadOnlyDictionary<string, string> Properties, IReadOnlyDictionary<string, string> EnvVars, bool? Warnings, IReadOnlyList<string> Inputs, IReadOnlyList<string> OptionalInputs, IReadOnlyList<string> OutputNames, IList<int> PublishOutputs, IReadOnlyList<RpcCreateGraphArtifactRequest> Artifacts )`  
_public; L46-69_
- desc: Information about a job step to be executed
- L65-68 _public ctor_ `public JobStepInfo(RpcBeginStepResponse response) : this(JobStepId.Parse(response.StepId), LogId.Parse(response.LogId), response.Name, response.Credentials, response.Properties, response.EnvVars, response.Warnings, response.Inputs, response.OptionalInputs, response.OutputNames, response.PublishOutputs, response.Artifacts)` — Constructor from an RPC response

#### class `JobDriver.Execution.JobExecutorOptions`  
`public class JobExecutorOptions`  
_public; L74-124_
- desc: Options for creating a job executor
- L79 _public property_ `public IHordeClient HordeClient { get; }` — The Horde client instance
- L84 _public property_ `public DirectoryReference WorkingDir { get; }` — Working directory for the executor
- L89 _public property_ `public IReadOnlyList<ProcessToTerminate>? ProcessesToTerminate { get; }` — Processes to terminate before/after execution
- L94 _public property_ `public JobId JobId { get; }` — Identifier for the job
- L99 _public property_ `public JobStepBatchId BatchId { get; }` — Identifier for the batch within the job
- L104 _public property_ `public LeaseId LeaseId { get; }` — Identifier for the lease
- L109 _public property_ `public RpcJobOptions JobOptions { get; }` — Options for the job
- L114-123 _public ctor_ `public JobExecutorOptions(IHordeClient hordeClient, DirectoryReference workingDir, IReadOnlyList<ProcessToTerminate>? processesToTerminate, JobId jobId, JobStepBatchId batchId, LeaseId leaseId, RpcJobOptions jobOptions)` — Constructor

#### class `JobDriver.Execution.JobExecutor`  
`public abstract class JobExecutor : IDisposable`  
_public; L129-2595_
- inherits: `IDisposable`
- desc: Abstract base class for job executors. Handles running BuildGraph scripts on an agent.
- L261 _private* const_ `const string ScriptArgumentPrefix = "-Script="`
- L262 _private* const_ `const string TargetArgumentPrefix = "-Target="`
- L264 _private* property_ `string PreprocessedScript => ...`
- L265 _private* property_ `string PreprocessedSchema => ...`
- L268 _protected property_ `protected List<string> Targets { get; set; }`
- L269 _protected property_ `protected string? ScriptFileName { get; set; }`
- L270 _protected property_ `protected bool PreprocessScript { get; set; }`
- L271 _protected property_ `protected bool SavePreprocessedScript { get; set; }`
- L272 _protected property_ `protected string EnginePath => ...`
- L273 _protected property_ `protected Tracer Tracer { get; }`
- L279 _protected property_ `protected ILogger Logger { get; }` — Logger for the local agent process (as opposed to job logger)
- L282 _protected property_ `protected IHordeClient HordeClient { get; }`
- L283 _protected property_ `protected DirectoryReference WorkingDir { get; }`
- L284 _protected property_ `protected JobId JobId { get; }`
- L285 _protected property_ `protected JobStepBatchId BatchId { get; }`
- L286 _protected property_ `protected LeaseId LeaseId { get; }`
- L287 _protected property_ `protected IReadOnlyList<ProcessToTerminate>? ProcessesToTerminate { get; }`
- L288 _protected property_ `protected RpcBeginBatchResponse Batch { get; set; }`
- L289 _protected property_ `protected List<string> AdditionalArguments { get; set; }`
- L290 _protected property_ `protected bool AllowTargetChanges { get; set; }`
- L291 _protected property_ `protected bool CompileAutomationTool { get; set; }`
- L292 _protected property_ `protected RpcJobOptions JobOptions { get; }`
- L293 _protected property_ `protected JobRpc.JobRpcClient JobRpc { get; set; }`
- L294 _protected property_ `protected Dictionary<string, string> RemapAgentTypes { get; set; }`
- L295 _protected property_ `protected Dictionary<string, string> EnvVars { get; set; }`
- L302 _internal field_ `internal TimeSpan _stepAbortPollInterval = TimeSpan.FromSeconds(5)` — How often to poll the server checking if a step has been aborted Exposed as internal to ease testing.
- L307 _internal field_ `internal TimeSpan _stepAbortPollRetryDelay = TimeSpan.FromSeconds(30)` — How long to wait before retrying a failed step abort check request
- L315 _internal field_ `internal CancellationTokenSource _abortCancellationSource = new()` — Cancellation source for the job executor. Will be cancelled when _abortHandle is signaled
- L328 _internal field_ `internal EventWaitHandle? _abortHandle` — The event handle that will be signaled for the job executor to abort. If the event is not created the process can still be canceled by the parent process but without the chance to complete
- L330 _private* const_ `const string AbortEventKeyName = "UE_HORDE_JOB_EXECUTOR_ABORT_EVENT_NAME"`
- L332 _private* field_ `readonly PosixSignalRegistration? _sigTermHandler`
- L337-355 _protected ctor_ `protected JobExecutor(JobExecutorOptions options, Tracer tracer, ILogger logger)` — Constructor
- L357-388 _private method_ `private static (EventWaitHandle?, PosixSignalRegistration?) CreateAbortEvent(string? name, Action<PosixSignalContext> handler)`
- L391-395 _public method_ `public void Dispose()` — (inheritdoc)
- L400-408 _protected method_ `protected virtual void Dispose(bool disposing)` — Disposes managed resources
- L410-426 _private* method_ `void SigTermHandler(PosixSignalContext context)`
- L431-453 _public method_ `public async Task ExecuteAsync(ILogger logger, CancellationToken cancellationToken)` — Executes all steps in the job batch
- L455-470 _private* method_ `static Task CancelOnEventAsync(EventWaitHandle? eventHandle, CancellationTokenSource cancellationSource, ILogger logger, CancellationToken cancellationToken = default)`
- L475-522 _protected method_ `protected virtual async Task ExecuteInternalAsync(ILogger logger, CancellationToken cancellationToken)` — Internal execution logic for the job batch, polling for and running steps
- L527-689 _private* method_ `async Task ExecuteBatchAsync(RpcBeginBatchResponse batch, ILogger logger, ILogger localLogger, CancellationToken cancellationToken)` — Executes a batch
- L699-724 _internal method_ `internal async Task<(JobStepOutcome, JobStepState)> ExecuteStepAsync(JobStepInfo step, ILogger stepLogger, CancellationToken cancellationToken, CancellationToken stepCancellationToken)` — Executes a step
- L731-745 _private* method_ `static bool IsCancellationException(Exception ex)` — Determine if the given exception was triggered due to a cancellation event
- L747-772 _internal method_ `internal async Task PollForStepAbortAsync(JobRpc.JobRpcClient rpcClient, JobId jobId, JobStepBatchId batchId, JobStepId stepId, CancellationTokenSource stepCancelSource, Task finishedTask, ILogger leaseLogger, CancellationToken cancellationToken)`
- L777-855 _public method_ `public virtual async Task InitializeAsync(RpcBeginBatchResponse batch, ILogger logger, CancellationToken cancellationToken)` — Initializes the executor with the batch response from the server
- L857-876 _private* method_ `static bool IsUserAdministrator()`
- L881-905 _public method_ `public virtual async Task<JobStepOutcome> RunAsync(JobStepInfo step, ILogger logger, CancellationToken cancellationToken)` — Runs a single job step
- L910-914 _public method_ `public virtual Task FinalizeAsync(ILogger jobLogger, CancellationToken cancellationToken)` — Finalizes the executor after all steps have completed
- L916-919 _private* method_ `static DirectoryReference GetAutomationToolDir(DirectoryReference sharedStorageDir)`
- L924-949 _protected method_ `protected void CopyAutomationTool(DirectoryReference sharedStorageDir, DirectoryReference workspaceDir, ILogger logger)` — Copies pre-built AutomationTool binaries from shared storage into the workspace
- L954-968 _protected method_ `protected void DeleteCachedBuildGraphManifests(DirectoryReference workspaceDir, ILogger logger)` — Deletes cached BuildGraph manifests from the workspace
- L973 _protected method_ `protected abstract Task<bool> SetupAsync(JobStepInfo step, ILogger logger, CancellationToken cancellationToken)` — Sets up the build environment for a step. Implemented by derived executors.
- L978 _protected method_ `protected abstract Task<bool> ExecuteAsync(JobStepInfo step, ILogger logger, CancellationToken cancellationToken)` — Executes a step. Implemented by derived executors.
- L980 _private* const_ `const string SetupStepName = "setup"`
- L981 _private* const_ `const string BuildGraphTempStorageDir = "BuildGraph"`
- L983-986 _private* method_ `IStorageNamespace GetStorageNamespace(NamespaceId namespaceId, string? token)`
- L991-1105 _protected method_ `protected virtual async Task<bool> SetupAsync(JobStepInfo step, DirectoryReference workspaceDir, bool? useP4, ILogger logger, CancellationToken cancellationToken)` — Sets up a build step by exporting the BuildGraph definition and uploading it to the server
- L1107-1293 _private method_ `private async Task<RpcUpdateGraphRequest> ParseGraphUpdateAsync(FileReference definitionFile, ILogger logger, CancellationToken cancellationToken)`
- L1295-1305 _private method_ `private static void GetRecursiveDependencies(string name, Dictionary<string, ExportedNode> nameToNode, HashSet<string> dependencies)`
- L1310-1376 _protected method_ `protected async Task<bool> ExecuteAsync(JobStepInfo step, DirectoryReference workspaceDir, bool? useP4, ILogger logger, CancellationToken cancellationToken)` — Executes a build step by running BuildGraph with the given workspace
- L1381-1424 _protected method_ `protected async Task CreateArtifactAsync(JobStepId stepId, ArtifactName name, ArtifactType type, DirectoryReference baseDir, IReadOnlyList<FileInfo> files, ILogger logger, CancellationToken cancellationToken)` — Creates and uploads an artifact for a job step
- L1426-1772 _private method_ `private async Task<bool> ExecuteWithTempStorageAsync(JobStepInfo step, DirectoryReference workspaceDir, string arguments, bool? useP4, ILogger logger, CancellationToken cancellationToken)`
- L1777-1822 _protected method_ `protected async Task<int> ExecuteAutomationToolAsync(JobStepInfo step, DirectoryReference workspaceDir, string? arguments, bool? useP4, ILogger logger, CancellationToken cancellationToken)` — Executes the Unreal AutomationTool (UAT) with the given arguments
- L1827-1853 _protected method_ `protected async Task LoadIgnorePatternsAsync(LogEventParser parser, DirectoryReference workspaceDir, ILogger logger)` — Discovers and loads ignore patterns from the workspace into the given parser
- L1855-1880 _private* method_ `List<FileReference> ValidateConfigPatternFiles(DirectoryReference workspaceDir, HashSet<FileReference> discoveredFiles, ILogger logger)`
- L1882-1892 _private* method_ `static FileReference GetCleanupScript(DirectoryReference workspaceDir)`
- L1894-1904 _private* method_ `static FileReference GetLeaseCleanupScript(DirectoryReference workspaceDir)`
- L1906-1909 _internal method_ `internal IReadOnlyDictionary<string, string> GetEnvVars()`
- L1914-1921 _protected method_ `protected static async Task ExecuteLeaseCleanupScriptAsync(DirectoryReference workspaceDir, ILogger logger)` — Runs the lease cleanup script in the workspace if present
- L1926-1936 _protected method_ `protected async Task TerminateProcessesAsync(TerminateCondition condition, ILogger logger)` — Terminates processes matching the configured termination rules
- L1938-1981 _private* method_ `static async Task ExecuteCleanupScriptAsync(FileReference cleanupScript, LogParser filter, ILogger logger)`
- L1983-2015 _private* method_ `static async Task<int> ExecuteProcessAsync(string fileName, string arguments, IReadOnlyDictionary<string, string>? newEnvironment, LogParser filter, ILogger logger, CancellationToken cancellationToken)`
- L2028-2085 _private* method_ `async Task<int> ExecuteProcessInContainerAsync(string arguments, List<DirectoryReference> mountDirs, IReadOnlyDictionary<string, string>? newEnvironment, LogParser filter, ILogger logger, CancellationToken cancellationToken)` — Execute a process inside a Linux container
- L2087-2096 _private method_ `private static List<DirectoryReference> GetContainerMountDirs(DirectoryReference workspaceDir, IReadOnlyDictionary<string, string> envVars)`
- L2098-2106 _private method_ `private static string ConformEnvironmentVariableName(string name)`
- L2108-2360 _private* method_ `async Task<int> ExecuteCommandAsync(JobStepInfo step, DirectoryReference workspaceDir, string fileName, string arguments, TelemetrySpan buildGraphSpan, ILogger jobLogger, CancellationToken cancellationToken)`
- L2362-2480 _private* method_ `async Task CreateTelemetryFilesAsync(string stepName, DirectoryInfo telemetryDir, List<FileInfo> telemetryFiles, TelemetrySpan buildGraphSpan, ILogger jobLogger, CancellationToken cancellationToken)`
- L2482-2519 _private method_ `private async Task CreateReportAsync(JobStepId stepId, FileReference reportFile, ILogger logger)`
- L2521-2544 _private method_ `private TelemetrySpan CreateTracingData(TelemetrySpan parent, TraceSpan span)`
- L2546-2556 _private method_ `private static void DecorateSpanWithArtifact(TelemetrySpan span, string prefix, RpcCreateJobArtifactRequestV2 request, RpcCreateJobArtifactResponseV2 response)`
- L2561-2585 _public method_ `public async Task UploadTestDataAsync(JobStepId jobStepId, IEnumerable<KeyValuePair<string, object>> pairs)` — Uploads test data for a job step to the server
- L2590-2594 _protected method_ `protected DirectoryReference GetUnrealRootDirectoryFromWorkspace(DirectoryReference workspaceDir)` — Gets the Unreal root directory from a workspace directory

#### class `JobDriver.Execution.JobExecutor.ExportedNode`  
`protected class ExportedNode`  
_protected; L132-145_
- L134 _public property_ `public string Name { get; set; }`
- L135 _public property_ `public bool RunEarly { get; set; }`
- L136 _public property_ `public bool? AllowRetry { get; set; }`
- L137 _public property_ `public bool? Warnings { get; set; }`
- L138 _public property_ `public List<string> Inputs { get; set; }`
- L139 _public property_ `public List<string> OptionalInputs { get; set; }`
- L140 _public property_ `public List<string> Outputs { get; set; }`
- L141 _public property_ `public List<string> InputDependencies { get; set; }`
- L142 _public property_ `public List<string> OptionalInputDependencies { get; set; }`
- L143 _public property_ `public List<string> OrderDependencies { get; set; }`
- L144 _public property_ `public Dictionary<string, string> Annotations { get; set; }`

#### class `JobDriver.Execution.JobExecutor.ExportedGroup`  
`protected class ExportedGroup`  
_protected; L147-151_
- L149 _public property_ `public List<string> Types { get; set; }`
- L150 _public property_ `public List<ExportedNode> Nodes { get; set; }`

#### class `JobDriver.Execution.JobExecutor.ExportedAggregate`  
`protected class ExportedAggregate`  
_protected; L153-157_
- L155 _public property_ `public string Name { get; set; }`
- L156 _public property_ `public List<string> Nodes { get; set; }`

#### class `JobDriver.Execution.JobExecutor.ExportedLabel`  
`protected class ExportedLabel`  
_protected; L159-168_
- L161 _public property_ `public string? Name { get; set; }`
- L162 _public property_ `public string? Category { get; set; }`
- L163 _public property_ `public string? UgsBadge { get; set; }`
- L164 _public property_ `public string? UgsProject { get; set; }`
- L165 _public property_ `public RpcLabelChange Change { get; set; }`
- L166 _public property_ `public List<string> RequiredNodes { get; set; }`
- L167 _public property_ `public List<string> IncludedNodes { get; set; }`

#### class `JobDriver.Execution.JobExecutor.ExportedBadge`  
`protected class ExportedBadge`  
_protected; L170-176_
- L172 _public property_ `public string Name { get; set; }`
- L173 _public property_ `public string? Project { get; set; }`
- L174 _public property_ `public int Change { get; set; }`
- L175 _public property_ `public string? Dependencies { get; set; }`

#### class `JobDriver.Execution.JobExecutor.ExportedArtifact`  
`protected class ExportedArtifact`  
_protected; L178-188_
- L180 _public property_ `public string Name { get; set; }`
- L181 _public property_ `public string? Type { get; set; }`
- L182 _public property_ `public string? Description { get; set; }`
- L183 _public property_ `public string? BasePath { get; set; }`
- L184 _public property_ `public List<string> Keys { get; set; }`
- L185 _public property_ `public List<string> Metadata { get; set; }`
- L186 _public property_ `public string NodeName { get; set; }`
- L187 _public property_ `public string OutputName { get; set; }`

#### class `JobDriver.Execution.JobExecutor.ExportedGraph`  
`protected class ExportedGraph`  
_protected; L190-197_
- L192 _public property_ `public List<ExportedGroup> Groups { get; set; }`
- L193 _public property_ `public List<ExportedAggregate> Aggregates { get; set; }`
- L194 _public property_ `public List<ExportedLabel> Labels { get; set; }`
- L195 _public property_ `public List<ExportedBadge> Badges { get; set; }`
- L196 _public property_ `public List<ExportedArtifact> Artifacts { get; set; }`

#### class `JobDriver.Execution.JobExecutor.TraceEvent`  
`class TraceEvent`  
_private*; L200-213_
- L202 _public property_ `public string Name { get; set; }`
- L203 _public property_ `public string? SpanId { get; set; }`
- L204 _public property_ `public string? ParentId { get; set; }`
- L205 _public property_ `public string? Service { get; set; }`
- L206 _public property_ `public string? Resource { get; set; }`
- L207 _public property_ `public DateTimeOffset StartTime { get; set; }`
- L208 _public property_ `public DateTimeOffset FinishTime { get; set; }`
- L209 _public property_ `public Dictionary<string, string>? Metadata { get; set; }`
- L212 _public property_ `public int Index { get; set; }` — attrs: `[JsonIgnore]`

#### class `JobDriver.Execution.JobExecutor.TraceEventList`  
`class TraceEventList`  
_private*; L215-218_
- L217 _public property_ `public List<TraceEvent> Spans { get; set; }`

#### class `JobDriver.Execution.JobExecutor.TraceSpan`  
`class TraceSpan`  
_private*; L220-237_
- L222 _public property_ `public string? Name { get; set; }`
- L223 _public property_ `public string? SpanId { get; set; }`
- L224 _public property_ `public string? ParentId { get; set; }`
- L225 _public property_ `public string? Service { get; set; }`
- L226 _public property_ `public string? Resource { get; set; }`
- L227 _public property_ `public long Start { get; set; }`
- L228 _public property_ `public long Finish { get; set; }`
- L229 _public property_ `public Dictionary<string, string>? Properties { get; set; }`
- L230 _public property_ `public List<TraceSpan>? Children { get; set; }`
- L232-236 _public method_ `public void AddChild(TraceSpan child)`

#### class `JobDriver.Execution.JobExecutor.TestDataItem`  
`class TestDataItem`  
_private*; L239-243_
- L241 _public property_ `public string Key { get; set; }`
- L242 _public property_ `public Dictionary<string, object> Data { get; set; }`

#### class `JobDriver.Execution.JobExecutor.TestData`  
`class TestData`  
_private*; L245-248_
- L247 _public property_ `public List<TestDataItem> Items { get; set; }`

#### class `JobDriver.Execution.JobExecutor.ReportData`  
`class ReportData`  
_private*; L250-259_
- L252 _public property_ `public RpcReportScope Scope { get; set; }`
- L253 _public property_ `public RpcReportPlacement Placement { get; set; }`
- L254 _public property_ `public string Name { get; set; }`
- L255 _public property_ `public string Content { get; set; }`
- L256 _public property_ `public string FileName { get; set; }`
- L257 _public property_ `public string? Message { get; set; }`
- L258 _public property_ `public string? Severity { get; set; }`

#### interface `JobDriver.Execution.IJobExecutorFactory`  
`public interface IJobExecutorFactory`  
_public; L2600-2611_
- desc: Factory interface for creating job executors
- L2605 _public* property_ `string Name { get; }` — Name of the executor type
- L2610 _public* method_ `Task<JobExecutor> CreateExecutorAsync(RpcAgentWorkspace workspaceInfo, RpcAgentWorkspace? autoSdkWorkspaceInfo, JobExecutorOptions options, CancellationToken cancellationToken)` — Creates a new executor instance for the given workspace configuration

#### class `JobDriver.Execution.JobExecutorHelpers`  
`static class JobExecutorHelpers`  
_internal*; L2613-2638_
- L2615-2637 _public method_ `public static async Task ExecuteAsync(IHordeClient hordeClient, DirectoryReference workingDir, LeaseId leaseId, ExecuteJobTask executeTask, IEnumerable<IJobExecutorFactory> executorFactories, DriverSettings driverSettings, ILogger logger, CancellationToken cancellationToken)`

### `Source/Programs/Horde/Drivers/JobDriver/Execution/LocalExecutor.cs` (JobDriver)


#### class `JobDriver.Execution.LocalExecutorSettings`  
`public class LocalExecutorSettings`  
_public; L14-25_
- desc: Settings for the local executor
- L19 _public property_ `public string? WorkspaceDir { get; set; }` — Path to the local workspace to use with the local executor
- L24 _public property_ `public bool RunSteps { get; set; }` — Whether to actually execute steps, or just do job setup

#### class `JobDriver.Execution.LocalExecutor`  
`class LocalExecutor : JobExecutor`  
_internal*; L30-83_
- inherits: `JobExecutor`
- desc: Job executor which runs out of a local workspace
- L32 _private field_ `private readonly LocalExecutorSettings _settings`
- L33 _private field_ `private readonly DirectoryReference _localWorkspaceDir`
- L35-47 _public ctor_ `public LocalExecutor(JobExecutorOptions options, LocalExecutorSettings settings, Tracer tracer, ILogger logger) : base(options, tracer, logger)`
- L49-64 _private* method_ `static DirectoryReference FindWorkspaceRoot()`
- L66-69 _protected method_ `protected override Task<bool> SetupAsync(JobStepInfo step, ILogger logger, CancellationToken cancellationToken)`
- L71-82 _protected method_ `protected override Task<bool> ExecuteAsync(JobStepInfo step, ILogger logger, CancellationToken cancellationToken)`

#### class `JobDriver.Execution.LocalExecutorFactory`  
`class LocalExecutorFactory : IJobExecutorFactory`  
_internal*; L85-104_
- inherits: `IJobExecutorFactory`
- L87 _private* field_ `readonly LocalExecutorSettings _settings`
- L88 _private* field_ `readonly Tracer _tracer`
- L89 _private* field_ `readonly ILogger<LocalExecutor> _logger`
- L91 _public property_ `public string Name => ...`
- L93-98 _public ctor_ `public LocalExecutorFactory(IOptions<LocalExecutorSettings> settings, Tracer tracer, ILogger<LocalExecutor> logger)`
- L100-103 _public method_ `public Task<JobExecutor> CreateExecutorAsync(RpcAgentWorkspace workspaceInfo, RpcAgentWorkspace? autoSdkWorkspaceInfo, JobExecutorOptions options, CancellationToken cancellationToken)`

### `Source/Programs/Horde/Drivers/JobDriver/Execution/ManagedWorkspaceMaterializer.cs` (JobDriver)


#### class `JobDriver.Execution.ManagedWorkspaceMaterializer`  
`public sealed class ManagedWorkspaceMaterializer : IWorkspaceMaterializer`  
_public; L17-196_
- inherits: `IWorkspaceMaterializer`
- desc: Workspace materializer wrapping ManagedWorkspace and WorkspaceInfo
- L22 _public const_ `public const string TypeName = "ManagedWorkspace"` — Name of this materializer
- L24 _private field_ `private readonly RpcAgentWorkspace _agentWorkspace`
- L25 _private field_ `private readonly bool _useCacheFile`
- L26 _private field_ `private readonly bool _cleanDuringFinalize`
- L27 _private field_ `private readonly WorkspaceInfo _workspace`
- L28 _private field_ `private readonly Tracer _tracer`
- L29 _private field_ `private readonly ILogger _logger`
- L30 _private field_ `private PerforceMetadataLogger? _perforceLogger`
- L31 _private field_ `private int? _lastSyncedChangeNum`
- L34 _public property_ `public DirectoryReference SyncDir => ...` — (inheritdoc)
- L37 _public property_ `public DirectoryReference BaseDir => ...` — (inheritdoc)
- L40 _public property_ `public string Name => ...` — (inheritdoc)
- L43 _public property_ `public string Identifier => ...` — (inheritdoc)
- L46 _public property_ `public IReadOnlyDictionary<string, string> EnvironmentVariables { get; }` — (inheritdoc)
- L49 _public property_ `public bool IsPerforceWorkspace => ...` — (inheritdoc)
- L60-85 _private ctor_ `private ManagedWorkspaceMaterializer( RpcAgentWorkspace agentWorkspace, bool useCacheFile, bool cleanDuringFinalize, WorkspaceInfo workspace, Tracer tracer, ILogger logger)` — Constructor
- L88-90 _public method_ `public void Dispose()` — (inheritdoc)
- L93-98 _public method_ `public static async Task<ManagedWorkspaceMaterializer> CreateAsync(RpcAgentWorkspace agentWorkspace, DirectoryReference workingDir, bool useCacheFile, bool cleanDuringFinalize, Tracer tracer, ILogger logger, CancellationToken cancellationToken)` — (inheritdoc)
- L101-106 _public method_ `public ILogger GetLogger(ILogger logger)` — (inheritdoc)
- L109-144 _public method_ `public async Task SyncAsync(int changeNum, int preflightChangeNum, SyncOptions options, CancellationToken cancellationToken)` — (inheritdoc)
- L147-156 _public method_ `public async Task FinalizeAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L159-163 _public method_ `public Task ConformAsync(bool removeUntrackedFiles, CancellationToken cancellationToken)` — (inheritdoc)
- L169-172 _public method_ `public WorkspaceInfo? GetWorkspaceInfo()` — Get info for Perforce workspace
- L174-180 _private method_ `private void AddClientViewToLogger()`
- L182-195 _private method_ `private TelemetrySpan CreateTraceSpan(string operationName)`

#### class `JobDriver.Execution.ManagedWorkspaceMaterializerFactory`  
`class ManagedWorkspaceMaterializerFactory : IWorkspaceMaterializerFactory`  
_internal*; L198-223_
- inherits: `IWorkspaceMaterializerFactory`
- L200 _private* field_ `readonly IServiceProvider _serviceProvider`
- L202 _public ctor_ `public ManagedWorkspaceMaterializerFactory(IServiceProvider serviceProvider)`
- L205-222 _public method_ `public async Task<IWorkspaceMaterializer?> CreateMaterializerAsync(string name, RpcAgentWorkspace workspaceInfo, DirectoryReference workspaceDir, bool forAutoSdk, CancellationToken cancellationToken)` — (inheritdoc)

### `Source/Programs/Horde/Drivers/JobDriver/Execution/PerforceExecutor.cs` (JobDriver)


#### class `JobDriver.Execution.PerforceExecutorSettings`  
`public class PerforceExecutorSettings`  
_public; L20-26_
- desc: Settings for the perforce executor
- L25 _public property_ `public bool RunConform { get; set; }` — Whether to run conform jobs

#### class `JobDriver.Execution.PerforceExecutor`  
`class PerforceExecutor : JobExecutor`  
_internal*; L31-594_
- inherits: `JobExecutor`
- desc: Executor which syncs workspaces from Perforce
- L33 _public const_ `public const string Name = "Perforce"`
- L35 _protected field_ `protected RpcAgentWorkspace _workspaceInfo`
- L36 _protected field_ `protected RpcAgentWorkspace? _autoSdkWorkspaceInfo`
- L37 _protected field_ `protected DirectoryReference _rootDir`
- L39 _protected field_ `protected WorkspaceInfo? _autoSdkWorkspace`
- L40 _protected field_ `protected WorkspaceInfo _workspace`
- L42-49 _public ctor_ `public PerforceExecutor(RpcAgentWorkspace workspaceInfo, RpcAgentWorkspace? autoSdkWorkspaceInfo, JobExecutorOptions options, Tracer tracer, ILogger logger) : base(options, tracer, logger)`
- L51-170 _public method_ `public override async Task InitializeAsync(RpcBeginBatchResponse batch, ILogger logger, CancellationToken cancellationToken)`
- L172-192 _internal method_ `internal static void DeleteEngineUserSettings(ILogger logger)`
- L194-212 _private method_ `private static void DeleteEngineUserSettings(DirectoryReference baseDir, string[] subDirNames, ILogger logger)`
- L214-223 _public method_ `public static PerforceMetadataLogger CreatePerforceLogger(ILogger logger, int changeNum, WorkspaceInfo workspace, WorkspaceInfo? autoSdkWorkspace)`
- L225-230 _protected method_ `protected override async Task<bool> SetupAsync(JobStepInfo step, ILogger logger, CancellationToken cancellationToken)`
- L232-237 _protected method_ `protected override async Task<bool> ExecuteAsync(JobStepInfo step, ILogger logger, CancellationToken cancellationToken)`
- L239-248 _public method_ `public override async Task FinalizeAsync(ILogger logger, CancellationToken cancellationToken)`
- L250-440 _public method_ `public static async Task ConformAsync( DirectoryReference rootDir, IList<RpcAgentWorkspace> pendingWorkspaces, bool removeUntrackedFiles, List<DirectoryReference> ignoreDirs, Tracer tracer, ILogger logger, CancellationToken cancellationToken)`
- L442-454 _internal method_ `internal static string? GetMaterializerName(string method)`
- L456-533 _public method_ `public static async Task ConformMaterializersAsync( IEnumerable<IWorkspaceMaterializerFactory> factories, DirectoryReference rootDir, IList<RpcAgentWorkspace> workspaces, bool removeUntrackedFiles, List<DirectoryReference> ignoreDirs, Tracer tracer, ILogger logger, CancellationToken cancellationToken)`
- L544-593 _public method_ `public static async Task DeleteUnusedClientsAsync(IPerforceConnection perforce, List<string> clientsToKeep, DirectoryReference rootDir, ILogger logger, CancellationToken cancellationToken)` — Deletes Perforce client workspaces that are no longer needed, cleaning up old or orphaned clients on the current machine under the specified root directory.

#### class `JobDriver.Execution.PerforceExecutorFactory`  
`class PerforceExecutorFactory : IJobExecutorFactory`  
_internal*; L596-613_
- inherits: `IJobExecutorFactory`
- L598 _private* field_ `readonly ILogger<PerforceExecutor> _logger`
- L599 _private* field_ `readonly Tracer _tracer`
- L601 _public property_ `public string Name => ...`
- L603-607 _public ctor_ `public PerforceExecutorFactory(Tracer tracer, ILogger<PerforceExecutor> logger)`
- L609-612 _public method_ `public Task<JobExecutor> CreateExecutorAsync(RpcAgentWorkspace workspaceInfo, RpcAgentWorkspace? autoSdkWorkspaceInfo, JobExecutorOptions options, CancellationToken cancellationToken)`

### `Source/Programs/Horde/Drivers/JobDriver/Execution/PerforceMaterializer.cs` (JobDriver)


#### record `JobDriver.Execution.PerforceMaterializerOptions`  
`public record PerforceMaterializerOptions( string DirPath, RpcAgentWorkspace AgentWorkspace, string? HostName, IReadOnlyDictionary<string, string>? EnvVars, int SyncThreads, int SyncBatch, int SyncBatchSize, int MaxFileConcurrency, int MaxFileScanConcurrency, bool UseModTime = false)`  
_public; L30-115_
- desc: Options for PerforceMaterializer
- L43-55 _public ctor_ `public PerforceMaterializerOptions(string dirPath, RpcAgentWorkspace agentWorkspace, string? hostName = null, IReadOnlyDictionary<string, string>? envVars = null, int syncThreads = -1, int syncBatch = -1, int syncBatchSize = -1, int? maxFileConcurrency = null, int? maxFileScanConcurrency = null, bool bUseModTime = false) : this( dirPath, agentWorkspace, hostName, envVars, syncThreads, syncBatch, syncBatchSize, maxFileConcurrency ?? GetDefaultThreadCount(4), maxFileScanConcurrency ?? GetDefaultThreadCount(4), bUseModTime)` — (inheritdoc)
- L57 _private* method_ `static int GetDefaultThreadCount(int defaultValue)`
- L65-114 _public method_ `public static PerforceMaterializerOptions FromMethodString(string dirPath, RpcAgentWorkspace agentWorkspace)` — Parse options from RpcAgentWorkspace.Method as HTTP query string

#### class `JobDriver.Execution.PerforceMaterializer`  
`public sealed class PerforceMaterializer : IWorkspaceMaterializer`  
_public; L122-881_
- inherits: `IWorkspaceMaterializer`
- desc: Materializer using standard Perforce client for syncing files Main use-case are for agents using only a single stream. For example, incremental build agents, as stream switching has not been optimized.
- L127 _public const_ `public const string TypeName = "Perforce"` — Name of this materializer
- L129 _internal const_ `internal const int CurrentStateVersion = 2`
- L144 _public property_ `public DirectoryReference SyncDir { get; }` — (inheritdoc)
- L147 _public property_ `public DirectoryReference BaseDir { get; }` — (inheritdoc)
- L150 _public property_ `public string Name => ...` — (inheritdoc)
- L153 _public property_ `public string Identifier { get; }` — (inheritdoc)
- L156 _public property_ `public IReadOnlyDictionary<string, string> EnvironmentVariables { get; set; }` — (inheritdoc)
- L159 _public property_ `public bool IsPerforceWorkspace { get; }` — (inheritdoc)
- L161 _private field_ `private static readonly JsonSerializerOptions s_jsonOptions = new() { WriteIndented = true }`
- L162 _private field_ `private readonly PerforceMaterializerOptions _options`
- L163 _private field_ `private readonly Tracer _tracer`
- L164 _private field_ `private readonly ILogger _logger`
- L165 _private field_ `private readonly DirectoryReference _metadataDir`
- L166 _private field_ `private readonly DirectoryReference _workspaceDir`
- L167 _private field_ `private PerforceSettings? _perforceSettings`
- L168 _private field_ `private IPerforceConnection? _perforceWithoutClient`
- L169 _private field_ `private IPerforceConnection? _perforceWithClient`
- L170 _private field_ `private List<string>? _streamView`
- L171 _private field_ `private int? _lastSyncedChangeNum`
- L172 _private field_ `private SyncOptions? _lastSyncOptions`
- L173 _private field_ `private bool _isFreshSync`
- L174 _private const_ `private const string StateFilename = "State.json"`
- L175 _private const_ `private const bool PreferNativePerforceClient = true`
- L176 _private const_ `private const int MaxFilesLogged = 500`
- L177 _private field_ `private readonly string _stateFile`
- L178 _private field_ `private readonly string _stateTempFile`
- L179 _private field_ `private PerforceMetadataLogger? _perforceLogger`
- L184-197 _public ctor_ `public PerforceMaterializer(PerforceMaterializerOptions options, Tracer tracer, ILogger logger)` — Constructor
- L200-204 _public method_ `public void Dispose()` — (inheritdoc)
- L206-261 _private method_ `private async Task InitializeAsync(CancellationToken cancellationToken)`
- L264-269 _public method_ `public ILogger GetLogger(ILogger logger)` — (inheritdoc)
- L272-409 _public method_ `public async Task SyncAsync(int changeNum, int shelveChangeNum, SyncOptions options, CancellationToken cancellationToken)` — (inheritdoc)
- L412-422 _public method_ `public async Task FinalizeAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L425-448 _public method_ `public async Task ConformAsync(bool removeUntrackedFiles, CancellationToken cancellationToken)` — (inheritdoc)
- L455-553 _public method_ `public async Task UnshelveAsync(IPerforceConnection perforce, ClientRecord client, int changeNum, int shelveChangeNum, CancellationToken cancellationToken)` — Replays the effects of unshelving a changelist But clobbering files in the workspace rather than actually unshelving them. This to prevent problems with multiple machines locking them.
- L555-578 _internal method_ `internal static async Task<IPerforceConnection> CreatePerforceWithoutClientAsync(RpcAgentWorkspace agentWorkspace, ILogger logger, CancellationToken cancellationToken)`
- L580-608 _internal method_ `internal static async Task<string> GetClientNameAsync(IPerforceConnection perforce, string prefix, string workspaceIdentifier, CancellationToken cancellationToken)`
- L610-616 _internal method_ `internal static async Task<IPerforceConnection> CreatePerforceWithClientAsync(RpcAgentWorkspace agentWorkspace, ILogger logger, CancellationToken cancellationToken)`
- L618-630 _internal method_ `internal async Task<IPerforceConnection> GetPerforceWithClientAsync()`
- L632-686 _private method_ `private async Task RevertInternalAsync(IPerforceConnection perforce, CancellationToken cancellationToken)`
- L688-730 _private method_ `private async Task CleanAsync(IPerforceConnection perforce, CancellationToken cancellationToken)`
- L732-795 _private method_ `private async Task<(ClientRecord client, bool wasRecreated)> CreateOrUpdateClientAsync(bool forceCreate, CancellationToken cancellationToken)`
- L797-810 _internal method_ `internal static string ConvertHordeViewToClientView(string hordeView, string stream, string clientName)`
- L812-816 _private method_ `private Task SaveStateAsync(TransactionStatus status, string client, int changelist, int shelvedChangelist, List<WorkspaceFile> dirtyFiles, CancellationToken cancellationToken)`
- L818-822 _private method_ `private async Task SaveStateAsync(TransactionStatus status, CancellationToken cancellationToken)`
- L824-837 _private method_ `private async Task SaveStateAsync(State state, CancellationToken cancellationToken)`
- L839-856 _private method_ `private async Task<State?> LoadStateAsync(CancellationToken cancellationToken)`
- L858-864 _private method_ `private void AddClientViewToLogger()`
- L866 _private method_ `private static int GetDefaultThreadCount(int defaultValue)`
- L868-875 _internal method_ `internal async Task DeleteClientForTestAsync(CancellationToken cancellationToken)`
- L877-880 _internal method_ `internal Task<State?> LoadStateForTestAsync(CancellationToken cancellationToken)`

#### enum `JobDriver.Execution.PerforceMaterializer.TransactionStatus`  
`internal enum TransactionStatus`  
_internal; L130-130_
- L130 _public* enumerator_ `Clean = 0`
- L130 _public* enumerator_ `Dirty = 1`

#### record `JobDriver.Execution.PerforceMaterializer.WorkspaceFile`  
`internal record WorkspaceFile(string ClientFile, string LocalFile)`  
_internal; L132-132_

#### record `JobDriver.Execution.PerforceMaterializer.State`  
`internal record State( int Version, TransactionStatus Status, string Client, string Identifier, string Stream, int Changelist, int ShelvedChangelist, List<WorkspaceFile> DirtyFiles)`  
_internal; L133-133_

#### class `JobDriver.Execution.PerforceMaterializerFactory`  
`class PerforceMaterializerFactory(IServiceProvider serviceProvider) : IWorkspaceMaterializerFactory`  
_internal*; L883-904_
- L886-903 _public method_ `public async Task<IWorkspaceMaterializer?> CreateMaterializerAsync(string name, RpcAgentWorkspace workspaceInfo, DirectoryReference workspaceDir, bool forAutoSdk, CancellationToken cancellationToken)` — (inheritdoc)

### `Source/Programs/Horde/Drivers/JobDriver/Execution/TestExecutor.cs` (JobDriver)


#### class `JobDriver.Execution.TestExecutor`  
`class TestExecutor : JobExecutor`  
_internal*; L15-223_
- inherits: `JobExecutor`
- L17 _public const_ `public const string Name = "Test"`
- L19 _private* field_ `readonly Dictionary<string, string> _arguments = ...`
- L19 _private* field_ `readonly Dictionary< _arguments = new Dictionary<string, string>(StringComparer.OrdinalIgnoreCase)`
- L21-24 _public ctor_ `public TestExecutor(JobExecutorOptions options, Tracer tracer, ILogger logger) : base(options, tracer, logger)`
- L27-35 _private* method_ `string? GetArgument(string name, string? defaultValue)` — attrs: `[return: NotNullIfNotNull("defaultValue")]`
- L37-45 _private* method_ `bool GetArgument(string name, bool defaultValue)`
- L47-69 _public method_ `public override async Task InitializeAsync(RpcBeginBatchResponse batch, ILogger logger, CancellationToken cancellationToken)`
- L71-120 _protected method_ `protected override async Task<bool> SetupAsync(JobStepInfo step, ILogger logger, CancellationToken cancellationToken)`
- L122-127 _private* method_ `static RpcCreateGroupRequest CreateGroup(string agentType)`
- L129-137 _private* method_ `static RpcCreateNodeRequest CreateNode(string name, string[] inputDependencies, JobStepOutcome outcome)`
- L139-147 _private* method_ `static RpcCreateLabelRequest CreateLabel(string category, string name, string[] requiredNodes, string[] includedNodes, Dictionary<string, string[]> dependencyMap)`
- L149-171 _private* method_ `static Dictionary<string, string[]> CreateDependencyMap(IEnumerable<RpcCreateGroupRequest> groups)`
- L173-216 _protected method_ `protected override async Task<bool> ExecuteAsync(JobStepInfo step, ILogger logger, CancellationToken cancellationToken)`
- L218-222 _public method_ `public override Task FinalizeAsync(ILogger logger, CancellationToken cancellationToken)`

#### class `JobDriver.Execution.TestExecutorFactory`  
`class TestExecutorFactory : IJobExecutorFactory`  
_internal*; L225-242_
- inherits: `IJobExecutorFactory`
- L227 _private* field_ `readonly Tracer _tracer`
- L228 _private* field_ `readonly ILogger<TestExecutor> _logger`
- L230 _public property_ `public string Name => ...`
- L232-236 _public ctor_ `public TestExecutorFactory(Tracer tracer, ILogger<TestExecutor> logger)`
- L238-241 _public method_ `public Task<JobExecutor> CreateExecutorAsync(RpcAgentWorkspace workspaceInfo, RpcAgentWorkspace? autoSdkWorkspaceInfo, JobExecutorOptions options, CancellationToken cancellationToken)`

### `Source/Programs/Horde/Drivers/JobDriver/Execution/WorkspaceExecutor.cs` (JobDriver)


#### class `JobDriver.Execution.WorkspaceExecutor`  
`class WorkspaceExecutor : JobExecutor`  
_internal*; L16-132_
- inherits: `JobExecutor`
- L18 _public const_ `public const string Name = "Workspace"`
- L20 _private field_ `private DirectoryReference? _sharedStorageDir`
- L21 _private field_ `private readonly IWorkspaceMaterializer _workspace`
- L22 _private field_ `private readonly IWorkspaceMaterializer? _autoSdkWorkspace`
- L24-29 _public ctor_ `public WorkspaceExecutor(JobExecutorOptions options, IWorkspaceMaterializer workspace, IWorkspaceMaterializer? autoSdkWorkspace, Tracer tracer, ILogger logger) : base(options, tracer, logger)`
- L31-40 _protected method_ `protected override void Dispose(bool disposing)`
- L42-95 _public method_ `public override async Task InitializeAsync(RpcBeginBatchResponse batch, ILogger logger, CancellationToken cancellationToken)`
- L98-103 _protected method_ `protected override async Task<bool> SetupAsync(JobStepInfo step, ILogger logger, CancellationToken cancellationToken)` — (inheritdoc)
- L106-111 _protected method_ `protected override async Task<bool> ExecuteAsync(JobStepInfo step, ILogger logger, CancellationToken cancellationToken)` — (inheritdoc)
- L114-126 _public method_ `public override async Task FinalizeAsync(ILogger logger, CancellationToken cancellationToken)` — (inheritdoc)
- L128-131 _private method_ `private ILogger GetLogger(ILogger logger)`

#### class `JobDriver.Execution.WorkspaceExecutorFactory`  
`class WorkspaceExecutorFactory : IJobExecutorFactory`  
_internal*; L134-197_
- inherits: `IJobExecutorFactory`
- L136 _private field_ `private readonly IEnumerable<IWorkspaceMaterializerFactory> _materializerFactories`
- L137 _private field_ `private readonly Tracer _tracer`
- L138 _private field_ `private readonly ILoggerFactory _loggerFactory`
- L140 _public property_ `public string Name => ...`
- L142-147 _public ctor_ `public WorkspaceExecutorFactory(IEnumerable<IWorkspaceMaterializerFactory> materializerFactories, Tracer tracer, ILoggerFactory loggerFactory)`
- L149-169 _public method_ `public async Task<JobExecutor> CreateExecutorAsync(RpcAgentWorkspace workspaceInfo, RpcAgentWorkspace? autoSdkWorkspaceInfo, JobExecutorOptions options, CancellationToken cancellationToken)`
- L171-196 _internal method_ `internal async Task<IWorkspaceMaterializer> CreateMaterializerAsync(RpcJobOptions jobOptions, RpcAgentWorkspace workspaceInfo, DirectoryReference workspaceDir, bool forAutoSdk, CancellationToken cancellationToken)`

### `Source/Programs/Horde/Drivers/JobDriver/Execution/WorkspaceMaterializer.cs` (JobDriver)


#### class `JobDriver.Execution.WorkspaceMaterializationException`  
`public class WorkspaceMaterializationException : Exception`  
_public; L12-27_
- inherits: `Exception`
- desc: Exception for workspace materializer
- L17-19 _public ctor_ `public WorkspaceMaterializationException(string? message) : base(message)` — Constructor
- L24-26 _public ctor_ `public WorkspaceMaterializationException(string? message, Exception? innerException) : base(message, innerException)` — Constructor

#### class `JobDriver.Execution.SyncOptions`  
`public class SyncOptions`  
_public; L32-44_
- desc: Options passed to SyncAsync
- L37 _public property_ `public bool RemoveUntracked { get; set; }` — Remove any files not referenced by changelist
- L43 _public property_ `public bool FakeSync { get; set; }` — If true, skip syncing actual file data and instead create empty placeholder files. Used for testing.

#### interface `JobDriver.Execution.IWorkspaceMaterializer`  
`public interface IWorkspaceMaterializer : IDisposable`  
_public; L50-126_
- inherits: `IDisposable`
- desc: Interface for materializing a file tree to the local file system. One instance roughly equals one Perforce stream.
- L55 _public const_ `public const int LatestChangeNumber = -2` — Placeholder for resolving the latest available change number of stream during sync
- L60 _public* property_ `string Name { get; }` — Name of this materializer
- L65 _public* property_ `DirectoryReference SyncDir { get; }` — Path to local file system directory where files from changelist are materialized
- L70 _public* property_ `DirectoryReference BaseDir { get; }` — Path to local file system directory where materializer contain all its metadata, state and synchronized files
- L75 _public* property_ `string Identifier { get; }` — Identifier for this workspace
- L81 _public* property_ `IReadOnlyDictionary<string, string> EnvironmentVariables { get; }` — Environment variables expected to be set for applications executing inside the workspace Mostly intended for Perforce-specific variables when IsPerforceWorkspace is set to true
- L88 _public* property_ `bool IsPerforceWorkspace { get; }` — Whether the materialized workspace is a true Perforce workspace This flag is provided as a stop-gap solution to allow replacing ManagedWorkspace with WorkspaceMaterializer. It's *highly* recommended to set this to false for any new implementations of IWorkspaceMaterializer.
- L95 _public* method_ `ILogger GetLogger(ILogger logger)` — Get a logger capable of decorating log lines with materializer specific hints (resolving of paths or change numbers)
- L107 _public* method_ `Task SyncAsync(int changeNum, int shelveChangeNum, SyncOptions options, CancellationToken cancellationToken)` — Materialize (or sync) a Perforce stream at a given change number Once method has completed, file tree is available on disk.
- L115 _public* method_ `Task FinalizeAsync(CancellationToken cancellationToken)` — Finalize and clean file system. Usually called after the workspace has been used (e.g a build operation completed)
- L125 _public* method_ `Task ConformAsync(bool removeUntrackedFiles, CancellationToken cancellationToken)` — Resets a workspace Removes unneeded files from workspace as well as cleaning up resources or state in VCS server (e.g workspaces/clients) and syncs

#### interface `JobDriver.Execution.IWorkspaceMaterializerFactory`  
`public interface IWorkspaceMaterializerFactory`  
_public; L131-143_
- desc: Factory for creating new workspace materializers
- L142 _public* method_ `Task<IWorkspaceMaterializer?> CreateMaterializerAsync(string name, RpcAgentWorkspace workspaceInfo, DirectoryReference workingDir, bool forAutoSdk = false, CancellationToken cancellationToken = default)` — Creates a new workspace materializer instance

#### class `JobDriver.Execution.WorkspaceMaterializerFactory`  
`public class WorkspaceMaterializerFactory(IEnumerable<IWorkspaceMaterializerFactory> factories) : IWorkspaceMaterializerFactory`  
_public; L149-178_
- desc: Helper class for creating workspace materializer
- L152-163 _public method_ `public async Task<IWorkspaceMaterializer?> CreateMaterializerAsync(string name, RpcAgentWorkspace agentWorkspace, DirectoryReference workingDir, bool forAutoSdk = false, CancellationToken cancellationToken = default)` — (inheritdoc)
- L174-177 _public method_ `public async Task<IWorkspaceMaterializer> CreateMaterializerOrThrowAsync(string name, RpcAgentWorkspace workspaceInfo, DirectoryReference workingDir, bool forAutoSdk = false, CancellationToken cancellationToken = default)` — Creates a new workspace materializer instance, throws an exception if not found

### `Source/Programs/Horde/Drivers/JobDriver/Parser/LogParser.cs` (JobDriver)


#### class `JobDriver.Parser.LogParser`  
`public class LogParser : LogEventParser`  
_public; L13-59_
- inherits: `LogEventParser`
- desc: Turns raw text output into structured logging events
- L20-25 _public ctor_ `public LogParser(ILogger logger, List<ILogEventSink>? logEventSinks = null) : base(logger, logEventSinks)` — Constructor
- L33-50 _public ctor_ `public LogParser(ILogger logger, List<string> ignorePatterns, List<ILogEventSink>? logEventSinks = null) : base(logger, logEventSinks)` — Constructor
- L55-58 _private* ctor_ `static LogParser()` — Static constructor

### `Source/Programs/Horde/Drivers/JobDriver/Properties/AssemblyInfo.cs` (JobDriver)
_(no declarations)_


### `Source/Programs/Horde/Drivers/JobDriver/Properties/Resources.Designer.cs` (JobDriver)


#### class `HordeAgent.Driver.Properties.Resources`  
`internal class Resources`  
_internal; L27-87_
- attrs: `[global::System.CodeDom.Compiler.GeneratedCodeAttribute("System.Resources.Tools.StronglyTypedResourceBuilder", "16.0.0.0")] [global::System.Diagnostics.DebuggerNonUserCodeAttribute()] [global::System.Runtime.CompilerServices.CompilerGeneratedAttribute()]`
- L29 _private field_ `private static global::System.Resources.ResourceManager resourceMan`
- L31 _private field_ `private static global::System.Globalization.CultureInfo resourceCulture`
- L34-35 _internal ctor_ `internal Resources()` — attrs: `[global::System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1811:AvoidUncalledPrivateCode")]`
- L41-49 _internal property_ `internal static global::System.Resources.ResourceManager ResourceManager { get; }` — attrs: `[global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]` — Returns the cached ResourceManager instance used by this class.
- L56-63 _internal property_ `internal static global::System.Globalization.CultureInfo Culture { get; set; }` — attrs: `[global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]` — Overrides the current thread's CurrentUICulture property for all resource lookups using this strongly typed resource class.
- L82-86 _internal property_ `internal static string IgnorePatterns { get; }` — Looks up a localized string similar to # UAT spam that just adds noise .*Exception in AutomationTool: BUILD FAILED.* RunUAT ERROR: AutomationTool was unable to run successfully. # Linux error caused by linking against libfbx .*the use of `tempnam&apos; is dangerous.* .*the use of `tmpnam_r&apos; is dangerous.* # Warning about object files not definining any public symbols in non-unity builds .*warning LNK4221:.* # Warning about static libraries missing PDB files for XboxOne .*warning LNK4099:.* # Warning from Android monolithic builds ab [rest of string was truncated]&quot;;.

### `Source/Programs/Horde/Drivers/JobDriver/Utilities/HordeRpc.cs` (JobDriver)


#### class `Horde.Common.Rpc.RpcGetJobRequest`  
`partial class RpcGetJobRequest`  
_internal*; L13-19_
- L15-18 _public ctor_ `public RpcGetJobRequest(JobId jobId)`

#### class `Horde.Common.Rpc.RpcBeginBatchRequest`  
`partial class RpcBeginBatchRequest`  
_internal*; L21-29_
- L23-28 _public ctor_ `public RpcBeginBatchRequest(JobId jobId, JobStepBatchId batchId, LeaseId leaseId)`

#### class `Horde.Common.Rpc.RpcFinishBatchRequest`  
`partial class RpcFinishBatchRequest`  
_internal*; L31-39_
- L33-38 _public ctor_ `public RpcFinishBatchRequest(JobId jobId, JobStepBatchId batchId, LeaseId leaseId)`

#### class `Horde.Common.Rpc.RpcBeginStepRequest`  
`partial class RpcBeginStepRequest`  
_internal*; L41-49_
- L43-48 _public ctor_ `public RpcBeginStepRequest(JobId jobId, JobStepBatchId batchId, LeaseId leaseId)`

#### class `Horde.Common.Rpc.RpcUpdateStepRequest`  
`partial class RpcUpdateStepRequest`  
_internal*; L51-61_
- L53-60 _public ctor_ `public RpcUpdateStepRequest(JobId jobId, JobStepBatchId batchId, JobStepId stepId, JobStepState state, JobStepOutcome outcome)`

#### class `Horde.Common.Rpc.RpcGetStepRequest`  
`partial class RpcGetStepRequest`  
_internal*; L63-71_
- L65-70 _public ctor_ `public RpcGetStepRequest(JobId jobId, JobStepBatchId batchId, JobStepId stepId)`

#### class `Horde.Common.Rpc.RpcGetStepResponse`  
`partial class RpcGetStepResponse`  
_internal*; L73-81_
- L75-80 _public ctor_ `public RpcGetStepResponse(JobStepOutcome outcome, JobStepState state, bool abortRequested)`

#### class `HordeCommon.Rpc.Tasks.RpcJobOptions`  
`partial class RpcJobOptions`  
_internal*; L86-113_
- L88-112 _public method_ `public void DecorateSpan(TelemetrySpan span)`

### `Source/Programs/Horde/Drivers/JobDriver/Utility/JobStepLogger.cs` (JobDriver)


#### class `JobDriver.Utility.JobStepLogger`  
`class JobStepLogger : IServerLogger`  
_internal*; L15-146_
- inherits: `IServerLogger`
- desc: Logger which updates the job step outcome whenever a warning or error is detected.
- L20 _public property_ `public JobStepOutcome Outcome => ...` — The current outcome for this step. Updated to reflect any errors and warnings that occurred.
- L22 _private* field_ `readonly IHordeClient _hordeClient`
- L23 _private* field_ `readonly JobId _jobId`
- L24 _private* field_ `readonly JobStepBatchId _jobBatchId`
- L25 _private* field_ `readonly JobStepId _jobStepId`
- L26 _private* field_ `readonly bool _warnings`
- L28 _private* field_ `readonly IServerLogger _serverLogger`
- L29 _private* field_ `readonly ILogger _localLogger`
- L30 _private* field_ `JobStepOutcome _outcome`
- L31 _private* field_ `Task _updateOutcomeTask`
- L32 _private* field_ `readonly CancellationTokenSource _cancellationSource`
- L33 _private* field_ `readonly ILogger _internalLogger`
- L38-51 _public ctor_ `public JobStepLogger(IHordeClient hordeClient, LogId logId, ILogger localLogger, JobId jobId, JobStepBatchId jobBatchId, JobStepId jobStepId, bool? warnings, LogLevel outputLevel, ILogger internalLogger)` — Constructor
- L54 _public method_ `public IDisposable? BeginScope<TState>(TState state) where TState : notnull` — (inheritdoc)
- L58-75 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L78 _public method_ `public bool IsEnabled(LogLevel logLevel)` — (inheritdoc)
- L82-121 _public method_ `public void Log<TState>(LogLevel logLevel, EventId eventId, TState state, Exception? exception, Func<TState, Exception?, string> formatter)` — (inheritdoc)
- L124-128 _public method_ `public async Task StopAsync()` — (inheritdoc)
- L130-145 _private* method_ `async Task UpdateOutcomeAsync(Task prevTask, JobStepOutcome newOutcome, CancellationToken cancellationToken)`

### `Source/Programs/Horde/Drivers/JobDriver/Utility/LinuxInterop.cs` (JobDriver)


#### class `JobDriver.Utility.LinuxInterop`  
`static class LinuxInterop`  
_internal*; L10-25_
- desc: Linux specific P/Invoke calls
- L17 _internal method_ `internal static extern uint getuid()` — attrs: `[DllImport("libc", SetLastError = true)]` — Get user identity
- L24 _internal method_ `internal static extern uint getgid()` — attrs: `[DllImport("libc", SetLastError = true)]` — Get group identity

### `Source/Programs/Horde/Drivers/JobDriver/Utility/OpenTelemetry.cs` (JobDriver)


#### class `JobDriver.Utility.OpenTelemetryDatadogLogEnricher`  
`public class OpenTelemetryDatadogLogEnricher : ILogEventEnricher`  
_public; L21-37_
- inherits: `ILogEventEnricher`
- desc: Serilog event enricher attaching trace and span ID for Datadog using current System.Diagnostics.Activity
- L24-36 _public method_ `public void Enrich(Serilog.Events.LogEvent logEvent, ILogEventPropertyFactory propertyFactory)` — (inheritdoc)

#### class `JobDriver.Utility.OpenTelemetryHelper`  
`public static class OpenTelemetryHelper`  
_public; L42-179_
- desc: Helper for configuring OpenTelemetry
- L44 _private field_ `private static ResourceBuilder? s_resourceBuilder`
- L46 _private field_ `private static readonly Tracer s_noOpTracer = TracerProvider.Default.GetTracer("NoOp")`
- L47 _private field_ `private static readonly Meter s_noOpMeter = new("NoOp")`
- L54-71 _public method_ `public static void Configure(IServiceCollection services, OpenTelemetrySettings settings)` — Configure OpenTelemetry in Horde and ASP.NET
- L73-115 _private method_ `private static void ConfigureTracing(TracerProviderBuilder builder, OpenTelemetrySettings settings)`
- L117-135 _private method_ `private static void ConfigureMetrics(MeterProviderBuilder builder, OpenTelemetrySettings settings)`
- L142-161 _public method_ `public static void ConfigureLogging(ILoggingBuilder builder, OpenTelemetrySettings settings)` — Configure .NET logging with OpenTelemetry
- L163-178 _private method_ `private static ResourceBuilder GetResourceBuilder(OpenTelemetrySettings settings)`

### `Source/Programs/Horde/Drivers/JobDriver/Utility/TempStorage.cs` (JobDriver)


#### class `JobDriver.Utility.TempStorageException`  
`public sealed class TempStorageException : Exception`  
_public; L24-33_
- inherits: `Exception`
- desc: Exception thrown by the temp storage system
- L29-32 _public ctor_ `public TempStorageException(string message, Exception? innerException = null) : base(message, innerException)` — Constructor

#### class `JobDriver.Utility.TempStorageBlockRef`  
`public class TempStorageBlockRef`  
_public; L38-90_
- desc: Stores the name of a temp storage block
- L44 _public property_ `public string NodeName { get; set; }` — attrs: `[XmlAttribute]` — Name of the node
- L50 _public property_ `public string OutputName { get; set; }` — attrs: `[XmlAttribute]` — Name of the output from this node
- L55-59 _private ctor_ `private TempStorageBlockRef()` — Default constructor, for XML serialization.
- L66-70 _public ctor_ `public TempStorageBlockRef(string nodeName, string outputName)` — Construct a temp storage block
- L77 _public method_ `public override bool Equals(object? other)` — Tests whether two temp storage blocks are equal
- L83 _public method_ `public override int GetHashCode()` — Returns a hash code for this block name
- L89 _public method_ `public override string ToString()` — Returns the name of this block for debugging purposes

#### class `JobDriver.Utility.TempStorageFile`  
`public class TempStorageFile : IEquatable<TempStorageFile>`  
_public; L96-322_
- attrs: `[DebuggerDisplay("{RelativePath}")]`
- inherits: `IEquatable<TempStorageFile>`
- desc: Information about a single file in temp storage
- L102 _public property_ `public string RelativePath { get; set; }` — attrs: `[XmlAttribute]` — The path of the file, relative to the engine root. Stored using forward slashes.
- L108 _public property_ `public long LastWriteTimeUtcTicks { get; set; }` — attrs: `[XmlAttribute]` — The last modified time of the file, in UTC ticks since the Epoch.
- L114 _public property_ `public long Length { get; set; }` — attrs: `[XmlAttribute]` — Length of the file
- L120 _public property_ `public string? Digest { get; set; }` — attrs: `[XmlAttribute]` — Digest for the file. Not all files are hashed.
- L125-128 _private ctor_ `private TempStorageFile()` — Default constructor, for XML serialization.
- L133-139 _public ctor_ `public TempStorageFile(string relativePath, long lastWriteTimeUtcTicks, long length, string? digest)` — Constructor
- L146-167 _public ctor_ `public TempStorageFile(FileInfo fileInfo, DirectoryReference rootDir)` — Constructor
- L175-194 _public method_ `public bool Compare(DirectoryReference rootDir, ILogger logger)` — Compare stored for this file with the one on disk, and output an error if they differ.
- L202-266 _public method_ `public bool Compare(DirectoryReference rootDir, [NotNullWhen(false)] out string? message)` — Compare stored for this file with the one on disk, and output an error if they differ.
- L272-275 _private* method_ `bool RequireMatchingTimestamps()` — Whether we should compare timestamps for this file. Some build products are harmlessly overwritten as part of the build process, so we flag those here.
- L281-284 _private* method_ `bool GenerateDigest()` — Determines whether to generate a digest for the current file
- L290-293 _public method_ `public bool ShouldSerializeDigest()` — Determine whether to serialize the digest property
- L300-303 _public method_ `public FileReference ToFileReference(DirectoryReference rootDir)` — Gets a local file reference for this file, given a root directory to base it from.
- L306 _public method_ `public override bool Equals(object? other)` — (inheritdoc)
- L310-317 _public method_ `public bool Equals(TempStorageFile? other)` — (inheritdoc)
- L320 _public method_ `public override int GetHashCode()` — (inheritdoc)

#### class `JobDriver.Utility.TempStorageBlockManifest`  
`public class TempStorageBlockManifest`  
_public; L328-413_
- attrs: `[XmlRoot(ElementName = "TempStorageManifest")]`
- desc: A manifest storing information about build products for a node's output
- L335 _public property_ `public TempStorageFile[] Files { get; set; }` — attrs: `[XmlArray] [XmlArrayItem("File")]` — List of output files
- L340 _private* field_ `static readonly XmlSerializer s_serializer = XmlSerializer.FromTypes(new Type[] { typeof(TempStorageBlockManifest) })[0]!` — Construct a static Xml serializer to avoid throwing an exception searching for the reflection info at runtime
- L345-348 _private ctor_ `private TempStorageBlockManifest()` — Construct an empty temp storage manifest
- L353-356 _public ctor_ `public TempStorageBlockManifest(TempStorageFile[] files)` — Construct a temp storage manifest
- L363-366 _public ctor_ `public TempStorageBlockManifest(FileInfo[] files, DirectoryReference rootDir)` — Creates a manifest from a flat list of files (in many folders) and a BaseFolder from which they are rooted.
- L372-380 _public method_ `public long GetTotalSize()` — Gets the total size of the files stored in this manifest
- L386-396 _public method_ `public static TempStorageBlockManifest Load(FileReference file)` — Load a manifest from disk
- L402-412 _public method_ `public void Save(FileReference file)` — Saves a manifest to disk

#### class `JobDriver.Utility.TempStorageTagManifest`  
`public class TempStorageTagManifest`  
_public; L419-541_
- attrs: `[XmlRoot(ElementName = "TempStorageFileList")]`
- desc: Stores the contents of a tagged file set
- L426 _public property_ `public string[] LocalFiles { get; set; }` — attrs: `[XmlArray] [XmlArrayItem("LocalFile")]` — List of files that are in this tag set, relative to the root directory
- L433 _public property_ `public string[] ExternalFiles { get; set; }` — attrs: `[XmlArray] [XmlArrayItem("LocalFile")]` — List of files that are in this tag set, but not relative to the root directory
- L440 _public property_ `public TempStorageBlockRef[] Blocks { get; set; }` — attrs: `[XmlArray] [XmlArrayItem("Block")]` — List of referenced storage blocks
- L445 _private* field_ `static readonly XmlSerializer s_serializer = XmlSerializer.FromTypes(new Type[] { typeof(TempStorageTagManifest) })[0]!` — Construct a static Xml serializer to avoid throwing an exception searching for the reflection info at runtime
- L450-455 _private ctor_ `private TempStorageTagManifest()` — Construct an empty file list for deserialization
- L463-468 _public ctor_ `public TempStorageTagManifest(string[] localFiles, string[] externalFiles, TempStorageBlockRef[] blocks)`
- L476-495 _public ctor_ `public TempStorageTagManifest(IEnumerable<FileReference> files, DirectoryReference rootDir, IEnumerable<TempStorageBlockRef> blocks)` — Creates a manifest from a flat list of files (in many folders) and a BaseFolder from which they are rooted.
- L501-511 _public method_ `public static TempStorageTagManifest Load(FileReference file)` — Load this list of files from disk
- L517-527 _public method_ `public void Save(FileReference file)` — Saves this list of files to disk
- L534-540 _public method_ `public HashSet<FileReference> ToFileSet(DirectoryReference rootDir)` — Converts this file list into a set of FileReference objects

#### class `JobDriver.Utility.TempStorage`  
`static class TempStorage`  
_internal*; L553-906_
- desc: Tracks the state of the current build job using the filesystem, allowing jobs to be restarted after a failure or expanded to include larger targets, and providing a proxy for different machines executing parts of the build in parallel to transfer build products and share state as part of a build system. If a shared temp storage directory is provided - typically a mounted path on a network share - all build products potentially needed as inputs by another node are compressed and copied over, along with metadata for them (see TempStorageFile) and flags for build events that have occurred (see TempStorageEvent). The local temp storage directory contains the same information, with the exception of the archived build products. Metadata is still kept to detect modified build products between runs. If data is not present in local temp storage, it's retrieved from shared temp storage and cached in local storage.
- L559-594 _public method_ `public static ArtifactName GetArtifactNameForNode(string name)` — Gets the ref name for a particular node
- L608-643 _public method_ `public static async Task<TempStorageTagManifest> RetrieveTagAsync(IHordeClient hordeClient, JobId jobId, JobStepId stepId, string nodeName, string tagName, DirectoryReference manifestDir, ILogger logger, CancellationToken cancellationToken)` — Reads a set of tagged files from disk
- L658-671 _public method_ `public static async Task<FileEntry> ArchiveTagAsync(DirectoryReference manifestDir, string nodeName, string tagName, DirectoryReference workspaceDir, IEnumerable<FileReference> files, TempStorageBlockRef[] blocks, IBlobWriter writer, ILogger logger, CancellationToken cancellationToken)` — Saves a tag to temp storage
- L678-688 _private* method_ `static string GetBlockDirectoryName(string blockName)` — Gets the directory name for storing data from a block
- L702-723 _public method_ `public static async Task<DirectoryEntry> ArchiveBlockAsync(DirectoryReference manifestDir, string nodeName, string blockName, DirectoryReference workspaceDir, IEnumerable<FileReference> files, IBlobWriter writer, ILogger logger, CancellationToken cancellationToken)` — Saves the given files (that should be rooted at the branch root) to a shared temp storage manifest with the given temp storage node and game.
- L738-828 _public method_ `public static async Task<TempStorageBlockManifest> RetrieveBlockAsync(IHordeClient hordeClient, JobId jobId, JobStepId stepId, string nodeName, string blockName, DirectoryReference rootDir, DirectoryReference manifestDir, ILogger logger, CancellationToken cancellationToken)` — Retrieve an output of the given node. Fetches and decompresses the files from shared storage if necessary, or validates the local files.
- L836-839 _public method_ `public static FileReference GetBlockManifestLocation(DirectoryReference baseDir, string nodeName, string? blockName)` — Gets the path to the manifest created for a node's output.
- L847-851 _public method_ `public static FileReference GetTagManifestLocation(DirectoryReference baseDir, string nodeName, string tagName)` — Gets the path to the file created to store a tag manifest for a node
- L859-905 _public method_ `public static bool IsDuplicateBuildProduct(FileReference localFile)` — Checks whether the given path is allowed as a build product that can be produced by more than one node (timestamps may be modified, etc..). Used to suppress warnings about build products being overwritten.

### `Source/Programs/Horde/Drivers/JobDriver/Utility/TerminateProcessHelper.cs` (JobDriver)


#### enum `JobDriver.Utility.TerminateCondition`  
`public enum TerminateCondition`  
_public; L12-38_
- attrs: `[Flags]`
- desc: Flags for processes to terminate
- L17 _public* enumerator_ `None = 0` — Not specified; terminate in all circumstances
- L22 _public* enumerator_ `BeforeConform = 2` — Before running a conform
- L27 _public* enumerator_ `BeforeBatch = 4` — Before executing a batch
- L32 _public* enumerator_ `AfterBatch = 8` — Terminate at the end of a batch
- L37 _public* enumerator_ `AfterStep = 16` — After a step completes

#### class `JobDriver.Utility.TerminateProcessHelper`  
`public static class TerminateProcessHelper`  
_public; L43-87_
- desc: Utility methods for terminating processes
- L48-53 _public method_ `public static Task TerminateProcessesAsync(TerminateCondition condition, DirectoryReference workingDir, IReadOnlyList<ProcessToTerminate>? processesToTerminate, ILogger logger, CancellationToken cancellationToken)` — Terminate processes matching certain criteria
- L58-86 _private* method_ `static bool ShouldTerminateProcess(FileReference imageFile, TerminateCondition condition, DirectoryReference workingDir, IReadOnlyList<ProcessToTerminate>? processesToTerminate)` — Callback for determining whether a process should be terminated

### `Source/Programs/Horde/Drivers/JobDriver/Utility/WorkspaceInfo.cs` (JobDriver)


#### class `JobDriver.Utility.WorkspaceInfo`  
`public sealed class WorkspaceInfo`  
_public; L20-515_
- desc: Stores information about a managed Perforce workspace
- L25 _public property_ `public PerforceSettings PerforceSettings { get; }` — The perforce settings
- L30 _public property_ `public string ServerAndPort => ...` — The Perforce server and port. This is checked to not be null in the constructor.
- L35 _public property_ `public string ClientName => ...` — The Perforce client name. This is checked to not be null in the constructor.
- L40 _public property_ `public string UserName => ...` — The Perforce user name. This is checked to not be null in the constructor.
- L45 _public property_ `public string HostName { get; }` — The hostname
- L50 _public property_ `public string StreamName { get; }` — The current stream
- L55 _public property_ `public PerforceViewMap StreamView { get; }` — View for the stream
- L60 _public property_ `public DirectoryReference MetadataDir { get; }` — The directory containing metadata for this workspace
- L65 _public property_ `public DirectoryReference WorkspaceDir { get; }` — The directory containing workspace data
- L70 _public property_ `public IReadOnlyList<string> View { get; }` — The view for files to sync
- L75 _public property_ `public bool RemoveUntrackedFiles { get; }` — Whether untracked files should be removed from this workspace
- L80 _public property_ `public ManagedWorkspace Repository { get; }` — The managed repository instance
- L94-111 _public ctor_ `public WorkspaceInfo(PerforceSettings perforceSettings, string hostName, string streamName, PerforceViewMap streamView, DirectoryReference metadataDir, DirectoryReference workspaceDir, IList<string>? view, bool removeUntrackedFiles, ManagedWorkspace repository)` — Constructor
- L123-216 _public method_ `public static async Task<WorkspaceInfo> CreateWorkspaceInfoAsync(RpcAgentWorkspace workspace, DirectoryReference rootDir, ManagedWorkspaceOptions options, Tracer tracer, ILogger logger, CancellationToken cancellationToken)` — Creates a new managed workspace
- L224-238 _public method_ `public async Task SetupWorkspaceAsync(IPerforceConnection perforceClient, CancellationToken cancellationToken)` — Creates a new managed workspace
- L245-269 _public method_ `public static bool ShouldUseHaveTable(string? method)` — Parse a text string as a query string to determine use of have table
- L276-334 _public method_ `public static ManagedWorkspaceOptions GetMwOptions(RpcAgentWorkspace workspace)` — Create manage workspace options
- L342-345 _public method_ `public Task<int> GetLatestChangeAsync(IPerforceConnection perforceClient, CancellationToken cancellationToken)` — Gets the latest change in the stream
- L353-357 _public method_ `public async Task CleanAsync(IPerforceConnection perforceClient, CancellationToken cancellationToken)` — Revert any open files in the workspace and clean it
- L364-368 _public method_ `public static void RemoveLocalCacheMarker(FileReference cacheFile)` — Removes the given cache file if it's invalid, and updates the metadata to reflect the version about to be synced
- L377-404 _public method_ `public async Task<bool> UpdateLocalCacheMarkerAsync(FileReference cacheFile, int change, int preflightChange)` — Removes the given cache file if it's invalid, and updates the metadata to reflect the version about to be synced
- L406-431 _private* method_ `string GetCacheMarkerDescriptor(int change, int preflightChange)`
- L442-453 _public method_ `public async Task SyncAsync(IPerforceConnection perforceClient, int change, int preflightChange, FileReference? cacheFile, CancellationToken cancellationToken)` — Sync the workspace to a given changelist, and capture it so we can quickly clean in the future
- L462-468 _private* method_ `async Task UnshelveAsync(IPerforceConnection perforceClient, int change, CancellationToken cancellationToken)` — Unshelves a changelist Assumes base changelist already has been synced.
- L475-478 _public method_ `public static string GetNormalizedHostName(string hostName)` — Strip the domain suffix to get the host name
- L483-514 _public method_ `public static async Task RevertAllChangesAsync(IPerforceConnection perforce, ILogger logger, CancellationToken cancellationToken)` — Revert all files in a workspace
