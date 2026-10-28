# CSharp / HordeAgent

- project root: `Source/Programs/Horde/HordeAgent`
- files: 49; symbols: 991
- symbol kinds: class=88, const=73, ctor=48, delegate=3, enum=7, enumerator=31, event=2, field=233, interface=8, method=324, property=151, record=9, struct=14
- access marked `*` is implicit (not written in source)

### `Source/Programs/Horde/HordeAgent/AgentApp.cs` (HordeAgent)


#### class `HordeAgent.DefaultServices`  
`class DefaultServices`  
_internal*; L31-51_
- desc: Injectable list of existing services
- L36 _public property_ `public IConfiguration Configuration { get; }` — The base configuration object
- L41 _public property_ `public IEnumerable<ServiceDescriptor> Descriptors { get; }` — List of service descriptors
- L46-50 _public ctor_ `public DefaultServices(IConfiguration configuration, IEnumerable<ServiceDescriptor> descriptors)` — Constructor

#### class `HordeAgent.AgentApp`  
`public static class AgentApp`  
_public; L56-410_
- desc: Entry point
- L61 _public const_ `public const string HordeServerClientName = "HordeServer"` — Name of the http client
- L66 _public property_ `public static DirectoryReference AppDir { get; }` — Path to the root application directory
- L71 _public property_ `public static DirectoryReference DataDir { get; set; }` — Path to the default data directory
- L76 _public property_ `public static IReadOnlyList<string> Args { get; set; }` — The launch arguments
- L82 _public property_ `public static bool IsSelfContained => ...` — Whether agent is packaged as a self-contained package where the .NET runtime is included.
- L88 _public property_ `public static string Version { get; }` — The current application version from compile-time generated version
- L93 _public property_ `public static JsonSerializerOptions DefaultJsonSerializerOptions { get; }` — Default settings for json serialization
- L100-243 _public method_ `public static async Task<int> Main(string[] args)` — Entry point
- L245-267 _private* method_ `static ISystemMetrics CreateSystemMetrics(DirectoryReference workingDir, ILogger logger)`
- L269-331 _private* method_ `static IConfiguration CreateConfig(bool readInstalledConfig, List<FileReference> agentConfigFiles, Dictionary<string, string?> configOverrides, out List<string> configSources)`
- L333-338 _internal method_ `internal static AgentSettings BindSettings(IConfiguration configuration)`
- L340-358 _private* method_ `static async Task CopyDefaultConfigFilesAsync(DirectoryReference configDir)`
- L365-375 _private* method_ `static DirectoryReference GetAppDir()` — attrs: `[SuppressMessage("SingleFile", "IL3000:Avoid accessing Assembly file path when publishing as a single file", Justification = "Has fallback handling")]` — Gets the application directory
- L383-397 _internal method_ `internal static List<FileReference> SplitPath(string paths)` — Splits a string containing multiple file paths Uses platform-specific path separators: semicolon (;) on Windows, colon (:) on other operating systems.
- L399-409 _internal method_ `internal static void LogGcStats(ILogger logger)`

### `Source/Programs/Horde/HordeAgent/AgentSettings.cs` (HordeAgent)


#### enum `HordeAgent.AgentMode`  
`public enum AgentMode`  
_public; L17-23_
- desc: Defines the operation mode of the agent Duplicated to prevent depending on Protobuf structures (weak name reference when deserializing JSON)
- L20 _public* enumerator_ `Dedicated` — Mode.Dedicated
- L22 _public* enumerator_ `Workstation` — Mode.Workstation

#### class `HordeAgent.MountNetworkShare`  
`public class MountNetworkShare`  
_public; L28-39_
- desc: Describes a network share to mount
- L33 _public property_ `public string? MountPoint { get; set; }` — Where the share should be mounted on the local machine. Must be a drive letter for Windows.
- L38 _public property_ `public string? RemotePath { get; set; }` — Path to the remote resource

#### class `HordeAgent.ServerProfile`  
`public class ServerProfile`  
_public; L44-108_
- desc: Information about a server to use
- L49 _public property_ `public string? Name { get; set; }` — Name of this server profile
- L55 _public property_ `public string Environment { get; set; }` — attrs: `[Required]` — Name of the environment (currently just used for tracing)
- L61 _public property_ `public Uri Url { get; set; }` — attrs: `[Required]` — Url of the server
- L66 _public property_ `public string? Token { get; set; }` — Bearer token to use to initiate the connection
- L71 _public property_ `public bool UseInteractiveAuth { get; set; }` — Whether to authenticate interactively in a desktop environment (for example, when agent is running on a user's workstation)
- L76 _public property_ `public string? Thumbprint { get; set; }` — Thumbprint of a certificate to trust. Allows using self-signed certs for the server.
- L81 _public property_ `public List<string> Thumbprints { get; }` — Thumbprints of certificates to trust. Allows using self-signed certs for the server.
- L86-89 _public method_ `public string? GetAuthToken()` — Returns auth token if interactive auth is disabled. Otherwise, null is returned.
- L96-107 _public method_ `public bool IsTrustedCertificate(string certificateThumbprint)` — Checks whether the given certificate thumbprint should be trusted

#### class `HordeAgent.AgentSettings`  
`public class AgentSettings`  
_public; L115-372_
- attrs: `[ConfigDoc("Agent.json (Agent)", "[Horde](../../README.md) > [Deployment](../Deployment.md) > [Agent](Agent.md)", "Deployment/AgentSettings.md", Introduction = "All Horde-specific settings are stored in a root object called 'Horde'. Other .NET functionality may be configured using properties in the root of this file.")]`
- desc: Global settings for the agent
- L120 _public const_ `public const string SectionName = "Horde"` — Name of the section containing these settings
- L125 _public property_ `public Dictionary<string, ServerProfile> ServerProfiles { get; }` — Known servers to connect to
- L130 _public property_ `public string? Server { get; set; }` — The default server, unless overridden from the command line
- L136 _public property_ `public string? Name { get; set; }` — Name of agent to report as when connecting to server. By default, the computer's hostname will be used.
- L146 _public property_ `public AgentMode? Mode { get; set; }` — Mode of operation for the agent AgentMode.Dedicated - For trusted agents in controlled environments (e.g., build farms). These agents handle all lease types and run exclusively Horde workloads. AgentMode.Workstation - For low-trust workstations, uses interactive authentication (human logs in). These agents yield to non-Horde workloads and only support compute leases for remote execution.
- L153 _public property_ `public bool Installed { get; set; }` — Whether the server is running in 'installed' mode. In this mode, on Windows, the default data directory will use the common application data folder (C:\ProgramData\Epic\Horde), and configuration data will be read from here and the registry. This setting is overridden to false for local builds from appsettings.Local.json.
- L161 _public property_ `public bool Ephemeral { get; set; }` — Whether agent should register as being ephemeral. Doing so will not persist any long-lived data on the server and once disconnected it's assumed to have been deleted permanently. Ideal for short-lived agents, such as spot instances on AWS EC2.
- L166 _public property_ `public DirectoryReference WorkingDir { get; set; }` — Working directory for leases and jobs (i.e where files from Perforce will be checked out)
- L171 _public property_ `public DirectoryReference LogsDir { get; set; }` — Directory where agent and lease logs are written
- L176 _public property_ `public bool ShareMountingEnabled { get; set; }` — Whether to mount the specified list of network shares
- L181 _public property_ `public List<MountNetworkShare> Shares { get; }` — List of network shares to mount
- L186 _public property_ `public string? WineExecutablePath { get; set; }` — Path to Wine executable. If null, execution under Wine is disabled
- L191 _public property_ `public string? ContainerEngineExecutablePath { get; set; }` — Path to container engine executable, such as /usr/bin/podman. If null, execution of compute workloads inside a container is disabled
- L196 _public property_ `public bool WriteStepOutputToLogger { get; set; }` — Whether to write step output to the logging device
- L201 _public property_ `public bool EnableAwsEc2Support { get; set; }` — Queries information about the current agent through the AWS EC2 interface
- L206 _public property_ `public bool UseLocalStorageClient { get; set; }` — Option to use a local storage client rather than connecting through the server. Primarily for convenience when debugging / iterating locally.
- L211 _public property_ `public string? ComputeIp { get; set; }` — Incoming IP for listening for compute work. If not set, it will be automatically resolved.
- L216 _public property_ `public int ComputePort { get; set; }` — Incoming port for listening for compute work. Needs to be tied with a lease. Set port to 0 to disable incoming compute requests.
- L221 _public property_ `public OpenTelemetrySettings OpenTelemetry { get; set; }` — Options for OpenTelemetry
- L226 _public property_ `public bool EnableTelemetry { get; set; }` — Whether to send telemetry back to Horde server
- L231 _public property_ `public int TelemetryReportInterval { get; set; }` — How often to report telemetry events to server in milliseconds
- L236 _public property_ `public long BundleCacheSize { get; set; }` — Maximum size of the bundle cache, in megabytes.
- L242 _public property_ `public int? CpuCount { get; set; }` — Maximum number of logical CPU cores workloads should use Currently this is only provided as a hint and requires leases to respect this value as it's set via an env variable (UE_HORDE_CPU_COUNT).
- L249 _public property_ `public double CpuMultiplier { get; set; }` — CPU core multiplier applied to CPU core count setting For example, 32 CPU cores and a multiplier of 0.5 results in max 16 CPU usage. CpuCount
- L254 _public property_ `public int? RamGb { get; set; }` — Maximum available RAM in gigabytes. Defaults to available RAM.
- L259 _public property_ `public Dictionary<string, string> Properties { get; }` — Key/value properties in addition to those set internally by the agent
- L266 _public property_ `public string[] AdminEndpoints { get; set; }` — Listen addresses for the built-in HTTP admin/management server. Disabled when empty. If activated, it's recommended to bind only to localhost for security reasons. Example: localhost:7008 to listen on localhost, port 7008
- L274 _public property_ `public string[] HealthCheckEndpoints { get; set; }` — Listen addresses for the built-in HTTP health check server. Disabled when empty. If activated, it's recommended to bind only to localhost for security reasons. Example: *:7009 to listen on all interfaces/IPs, port 7009 If all interfaces are bound with *, make sure to run process as administrator.
- L279 _public property_ `public int? TempStorageMaxBatchSize { get; set; }` — Maximum number of temp storage exports to write in a single request
- L285 _public property_ `public bool LogOptionalInputFailureAsWarning { get; set; }` — Whether to log optional input retrieval failures as warnings instead of information messages. Defaults to false (information level).
- L291-310 _public method_ `public ServerProfile GetServerProfile(string name)` — Gets the current server settings
- L312-327 _private* method_ `string GetServerProfileNames()`
- L333-347 _public method_ `public ServerProfile GetCurrentServerProfile()` — Gets the current server settings
- L353-356 _public method_ `public FileReference GetTerminationSignalFile()` — Path to file used for signaling impending termination and shutdown of the agent
- L358-361 _internal method_ `internal string GetAgentName()`
- L363-371 _internal method_ `internal Mode GetMode()`

#### class `HordeAgent.AgentSettingsExtensions`  
`public static class AgentSettingsExtensions`  
_public; L377-394_
- desc: Extension methods for retrieving config settings
- L384-393 _public method_ `public static IConfigurationSection GetCurrentServerProfile(this IConfigurationSection configSection)` — Gets the configuration section for the active server profile

### `Source/Programs/Horde/HordeAgent/Commands/Compute/AwsLambdaClient.cs` (HordeAgent)


#### class `HordeAgent.Commands.Compute.NextInvocationResponse`  
`public class NextInvocationResponse`  
_public; L12-48_
- desc: Class representing the HTTP response from next invocation request
- L17 _public property_ `public string RequestId { get; }` — Lambda request ID
- L22 _public property_ `public string InvokedFunctionArn { get; }` — Name of the Lambda function being invoked
- L27 _public property_ `public long DeadlineMs { get; }` — Deadline in milliseconds for completing the function invocation
- L32 _public property_ `public ReadOnlyMemory<byte> Data { get; }` — Data
- L41-47 _public ctor_ `public NextInvocationResponse(string requestId, string invokedFunctionArn, long deadlineMs, byte[] data)` — Constructor

#### class `HordeAgent.Commands.Compute.AwsLambdaClientException`  
`public class AwsLambdaClientException : Exception`  
_public; L53-76_
- inherits: `Exception`
- desc: Class representing an exception when communicating with the AWS Lambda Runtime API
- L58 _public property_ `public bool IsFatal { get; }` — Whether the exception is fatal and requires termination of the process (to adhere to Lambda specs)
- L63 _public property_ `public HttpStatusCode? StatusCode { get; }` — HTTP status code in response from AWS Lambda API
- L71-75 _public ctor_ `public AwsLambdaClientException(string message, bool isFatal = false, HttpStatusCode? statusCode = null) : base(message)` — Constructor

#### class `HordeAgent.Commands.Compute.AwsLambdaClient`  
`public class AwsLambdaClient`  
_public; L82-277_
- desc: Client interfacing with the AWS Lambda runtime API See https://docs.aws.amazon.com/lambda/latest/dg/runtimes-api.html
- L84 _private const_ `private const string EnvVarRuntimeApi = "AWS_LAMBDA_RUNTIME_API"`
- L85 _private const_ `private const string HeaderNameAwsRequestId = "Lambda-Runtime-Aws-Request-Id"`
- L86 _private const_ `private const string HeaderNameDeadlineMs = "Lambda-Runtime-Deadline-Ms"`
- L87 _private const_ `private const string HeaderNameInvokedFunctionArn = "Lambda-Runtime-Invoked-Function-Arn"`
- L88 _private const_ `private const string HeaderNameFuncErrorType = "Lambda-Runtime-Function-Error-Type"`
- L90 _private field_ `private readonly ILogger<AwsLambdaClient> _logger`
- L91 _private field_ `private readonly string _hostPort`
- L98-102 _public ctor_ `public AwsLambdaClient(string hostPort, ILogger<AwsLambdaClient> logger)` — Constructor
- L111-120 _public method_ `public static AwsLambdaClient InitFromEnv(ILogger<AwsLambdaClient> logger)` — Create an AwsLambdaClient from environment variables. Usually how the client is created when running inside a real AWS Lambda environment.
- L122 _private method_ `private string GetNextInvocationUrl()`
- L123 _private method_ `private string GetInvocationResponseUrl(string awsRequestId)`
- L124 _private method_ `private string GetInitErrorUrl()`
- L125 _private method_ `private string GetInvocationErrorUrl(string awsRequestId)`
- L127-130 _private method_ `private static HttpClient GetHttpClient()`
- L140-174 _private method_ `private async Task<NextInvocationResponse> GetNextInvocationAsync(CancellationToken cancellationToken)` — Get the next invocation from the Lambda runtime API Can block for many minutes waiting for a new invocation request to be received.
- L176-189 _private method_ `private async Task SendInvocationResponseAsync(string awsRequestId, ReadOnlyMemory<byte> data)`
- L198-201 _public method_ `public Task SendInitErrorAsync(string errorType, string errorMessage, List<string>? stackTrace = null)` — Notify the Lambda runtime API that an error occurred during initialization.
- L203-206 _private method_ `private Task SendInvocationErrorAsync(string awsRequestId, string errorType, string errorMessage, List<string>? stackTrace = null)`
- L217-254 _public method_ `public async Task<bool> ListenForInvocationsAsync(IAwsLambdaFunction function, CancellationToken cancellationToken)` — Listen for new Lambda invocations Call function for each new invocation received. Will block until cancellation token is triggered.
- L256-276 _private method_ `private static async Task SendErrorAsync(string url, string errorType, string errorMessage, List<string>? stackTrace)`

#### interface `HordeAgent.Commands.Compute.IAwsLambdaFunction`  
`public interface IAwsLambdaFunction`  
_public; L282-292_
- desc: Represents an AWS Lambda function that can be invoked
- L291 _public method_ `public Task<ReadOnlyMemory<byte>> OnLambdaInvokeAsync(string requestId, ReadOnlyMemory<byte> requestData, CancellationToken cancellationToken)` — Handles an AWS Lambda function call

### `Source/Programs/Horde/HordeAgent/Commands/Compute/ComputeWorkerCommand.cs` (HordeAgent)


#### class `HordeAgent.Commands.Compute.ComputeWorkerCommand`  
`class ComputeWorkerCommand : Command`  
_internal*; L17-50_
- attrs: `[Command("computeworker", "Runs the agent as a local compute host, accepting incoming connections on the loopback adapter with a given port")]`
- inherits: `Command`
- desc: Helper command for hosting a local compute worker in a separate process
- L21 _private* property_ `int Port { get; set; }` — attrs: `[CommandLine("-Port=")] [Description("Port to listen for connections on.")]`
- L23-41 _public method_ `public override async Task<int> ExecuteAsync(ILogger logger)`
- L43-49 _public method_ `public static async Task RunWorkerAsync(ComputeSocket socket, ILogger logger, CancellationToken cancellationToken)`

### `Source/Programs/Horde/HordeAgent/Commands/Service/ServiceInstall.cs` (HordeAgent)


#### record `HordeAgent.Commands.Service.InstallServiceOptions`  
`internal record InstallServiceOptions( string? UserName = null, string? Password = null, string? ServerProfile = null, string? ConfigFiles = null, string DotNetExecutable = "dotnet", bool StartService = true, bool AutoRestartService = true )`  
_internal; L12-12_

#### class `HordeAgent.Commands.Service.InstallServiceCommand`  
`class InstallServiceCommand : Command`  
_internal*; L26-173_
- attrs: `[Command("service", "install", "Installs the agent as a Windows service")]`
- inherits: `Command`
- desc: Installs the agent as a Windows service
- L31 _public const_ `public const string ServiceName = "HordeAgent"` — Name of the service
- L35 _public property_ `public string? UserName { get; set; }` — attrs: `[CommandLine("-UserName=")] [Description("Specifies the username for the service to run under")]`
- L39 _public property_ `public string? Password { get; set; }` — attrs: `[CommandLine("-Password=")] [Description("Password for the service account")]`
- L43 _public property_ `public string? Server { get; set; }` — attrs: `[CommandLine("-Server=")] [Description("The server profile to use")]`
- L47 _public property_ `public string DotNetExecutable { get; set; }` — attrs: `[CommandLine("-DotNetExecutable=")] [Description("Path to dotnet executable (dotnet.exe on Windows). When left empty, the value of \"dotnet\" will be used.")]`
- L51 _public property_ `public string? Start { get; set; }` — attrs: `[CommandLine("-Start=")] [Description("Whether to start the service after installation (true/false)")]`
- L55 _public property_ `public string? ConfigFiles { get; set; }` — attrs: `[CommandLine("-ConfigFiles=")] [Description("Paths to additional config JSON files to load, separated by colon (Linux/macOS) or semi-colon (Windows)")]`
- L59 _public property_ `public string AutoRestartService { get; set; }` — attrs: `[CommandLine("-AutoRestartService=")] [Description("Configures the Windows Service to autostart when HordeAgent crashes/exits abnormally. (true/false)")]`
- L66-84 _public method_ `public override Task<int> ExecuteAsync(ILogger logger)` — Installs the service
- L86-107 _internal method_ `internal static bool StopAndDeleteWindowsService(ILogger logger)`
- L109-172 _internal method_ `internal static int InstallService(InstallServiceOptions options, ILogger logger)`

### `Source/Programs/Horde/HordeAgent/Commands/Service/ServiceRun.cs` (HordeAgent)


#### class `HordeAgent.Commands.Service.RunCommand`  
`class RunCommand : Command`  
_internal*; L17-154_
- attrs: `[Command("service", "run", "Runs the Horde agent")]`
- inherits: `Command`
- desc: Runs the agent
- L21 _public property_ `public string LogLevelStr { get; set; }` — attrs: `[CommandLine("-LogLevel")] [Description("Log verbosity level (use normal MS levels such as debug, warning or information)")]`
- L26 _public property_ `public string? ConfigFiles { get; set; }` — attrs: `[CommandLine("-ConfigFiles=")] [Description("Paths to additional config JSON files to load, separated by colon (Linux/macOS) or semi-colon (Windows)")]`
- L28 _private* field_ `readonly DefaultServices _defaultServices`
- L33-36 _public ctor_ `public RunCommand(DefaultServices defaultServices)` — Constructor
- L42-107 _public method_ `public override async Task<int> ExecuteAsync(ILogger logger)` — Runs the service indefinitely

#### class `HordeAgent.Commands.Service.RunCommand.SingleInstanceMutex`  
`class SingleInstanceMutex : IDisposable`  
_private*; L109-153_
- inherits: `IDisposable`
- L111 _private* field_ `Thread _backgroundThread`
- L112 _private* field_ `readonly ManualResetEventSlim _quitEvent = new ManualResetEventSlim()`
- L113 _private* field_ `readonly TaskCompletionSource<bool> _waitEvent = new TaskCompletionSource<bool>()`
- L115-119 _public ctor_ `public SingleInstanceMutex()`
- L121 _public method_ `public Task<bool> HasMutexAsync()`
- L124-134 _public method_ `public void Dispose()`
- L136-152 _private* method_ `void WaitForMutex()`

### `Source/Programs/Horde/HordeAgent/Commands/Service/ServiceUninstall.cs` (HordeAgent)


#### class `HordeAgent.Commands.Service.UninstallServiceCommand`  
`class UninstallServiceCommand : Command`  
_internal*; L13-54_
- attrs: `[Command("service", "uninstall", "Uninstalls the Windows service")]`
- inherits: `Command`
- desc: Uninstalls the Windows service
- L18 _public const_ `public const string ServiceName = InstallServiceCommand.ServiceName` — Name of the service
- L25-53 _public method_ `public override Task<int> ExecuteAsync(ILogger logger)` — Uninstalls the service

### `Source/Programs/Horde/HordeAgent/Commands/Service/ServiceUpgrade.cs` (HordeAgent)


#### class `HordeAgent.Commands.Service.UpgradeCommand`  
`class UpgradeCommand : Command`  
_internal*; L19-254_
- attrs: `[Command("service", "upgrade", "Replaces a running service with the application in the current directory", Advertise = false)]`
- inherits: `Command`
- desc: Upgrades a running service to the current application
- L25 _private* property_ `int ProcessId { get; set; }` — attrs: `[CommandLine("-ProcessId=", Required = true)]` — The process ID to replace (the old but currently running agent process)
- L31 _private* property_ `DirectoryReference TargetDir { get; set; }` — attrs: `[CommandLine("-TargetDir=", Required = true)]` — The target directory to install to
- L37 _private* property_ `string Arguments { get; set; }` — attrs: `[CommandLine("-Arguments=", Required = true)]` — Arguments to forward to the target executable
- L44-108 _public method_ `public override Task<int> ExecuteAsync(ILogger logger)` — Upgrades the application to a new version
- L110 _private field_ `private static readonly int[] s_retryDelaysMs = { 500, 1000, 2000, 3000, 5000 }`
- L112-125 _private method_ `private static void UpgradeFilesInPlace(ILogger logger, HashSet<string> targetFiles, List<Tuple<string, string>> moveFiles)`
- L127-148 _internal method_ `internal static void DeleteFileWithRetry(ILogger logger, string filePath, int[] retryDelaysMs)`
- L150-172 _internal method_ `internal static void MoveFileWithRetry(ILogger logger, string sourceFile, string targetFile, int[] retryDelaysMs)`
- L174-180 _private* method_ `static void UpgradeMacService(ILogger logger, Process otherProcess, HashSet<string> targetFiles, List<Tuple<string, string>> renameFiles)`
- L182-188 _private* method_ `static void UpgradeLinuxService(ILogger logger, Process otherProcess, HashSet<string> targetFiles, List<Tuple<string, string>> renameFiles)`
- L191-253 _private* method_ `void UpgradeWindowsService(ILogger logger, Process otherProcess, HashSet<string> targetFiles, List<Tuple<string, string>> renameFiles)` — attrs: `[SupportedOSPlatform("windows")]`

### `Source/Programs/Horde/HordeAgent/Commands/Setup/SetupInstall.cs` (HordeAgent)


#### class `HordeAgent.Commands.Setup.InstallException`  
`public class InstallException(string message, int exitCode = 1, Exception? innerException = null) : Exception(message, innerException)`  
_public; L21-27_
- desc: Exception for any installer related errors
- L26 _public property_ `public int ExitCode { get; }` — Exit code

#### class `HordeAgent.Commands.Setup.SetupInstallCommand`  
`class SetupInstallCommand : Command`  
_internal*; L33-398_
- attrs: `[Command("setup", "install", "Installs the agent (on Windows)")]`
- inherits: `Command`
- desc: Install the agent as a Windows application and service
- L35 _private* const_ `const string HordeAgentDll = "HordeAgent.dll"`
- L36 _private* const_ `const string HordeAgentExe = "HordeAgent.exe"`
- L37 _private* const_ `const string HordeAgentIco = "HordeAgent.ico"`
- L38 _private* const_ `const string UninstallKeyPath = @"SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall"`
- L39 _private* const_ `const string UninstallAppName = "Unreal Horde Agent"`
- L40 _private* const_ `const string PortRange = "7000-7010"`
- L41 _internal const_ `internal const string FirewallRuleName = "Horde Agent"`
- L45 _public property_ `public string? ShowStackTrace { get; set; }` — attrs: `[CommandLine("-ShowStackTrace=")] [Description("Whether to show full stack trace on errors (true/false)")]`
- L49 _public property_ `public string? RegisterForUninstall { get; set; }` — attrs: `[CommandLine("-RegisterForUninstall=")] [Description("Whether to register the app for uninstall in Windows (true/false)")]`
- L56-83 _public method_ `public override Task<int> ExecuteAsync(ILogger logger)` — Install the
- L107-182 _public method_ `public static int Install(ILogger logger, InstallParams installParams)` — attrs: `[SupportedOSPlatform("windows")]` — Install agent on Windows
- L192-197 _private method_ `private static (string executable, string args) ResolveCommandLine(string hordeAgentDir, string args)` — Resolves path to executable and arguments to send for invoking the Horde agent executable If agent is self-contained, the binary will be a standalone executable. Otherwise, 'dotnet' executable will be used with the .dll and additional arguments appended
- L199-214 _private method_ `private static bool PatchAgentJsonFile(FileReference jsonFilePath, string key, string value)`
- L216-219 _internal method_ `internal static string GetDefaultInstallDir()`
- L221-229 _internal method_ `internal static void AddFirewallPortRule(string name, string portRange)`
- L231-236 _internal method_ `internal static bool ContainsHordeAgentExecutable(DirectoryReference dir)`
- L238-241 _internal method_ `internal static void RemoveFirewallPortRule(string name)`
- L243-256 _internal method_ `internal static int RunProcessSilently(string fileName, string arguments)`
- L268-292 _public method_ `public static void RegisterAppForUninstall(AppInfo appInfo)` — attrs: `[SupportedOSPlatform("windows")]`
- L295-305 _public method_ `public static bool UnregisterAppForUninstall(string appName = UninstallAppName)` — attrs: `[SupportedOSPlatform("windows")]`
- L308-323 _public method_ `public static DirectoryReference GetUninstallLocation(bool useRegistryPath = true)` — attrs: `[SupportedOSPlatform("windows")]`
- L333-397 _public method_ `public static void RunSelfDeleteScript(DirectoryReference deleteDir, int waitPid)` — Runs a Windows batch script that will delete the given directory The script will be executed in the background and wait for a process to exit before attempting to delete. This allows the uninstaller (HordeAgent.dll or similar) to remove itself once the main duties are completed.

#### record `HordeAgent.Commands.Setup.SetupInstallCommand.InstallParams`  
`public record InstallParams( string? SourceDir = null, string? DestDir = null, string? ConfigDir = null, string? WorkingDir = null, bool RegisterForUninstall = true )`  
_public; L93-93_
- desc: Parameters for installing agent on Windows

#### record `HordeAgent.Commands.Setup.SetupInstallCommand.AppInfo`  
`internal record AppInfo( string DisplayName, DirectoryReference InstallLocation, string Version, string Publisher, string UninstallCommand, FileReference? IconPath, long EstimatedSizeInKb)`  
_internal; L258-258_

### `Source/Programs/Horde/HordeAgent/Commands/Setup/SetupUninstall.cs` (HordeAgent)


#### class `HordeAgent.Commands.Setup.SetupUninstallCommand`  
`class SetupUninstallCommand : Command`  
_internal*; L15-82_
- attrs: `[Command("setup", "uninstall", "Uninstalls the agent (on Windows)")]`
- inherits: `Command`
- desc: Uninstall the agent from Windows
- L19 _public property_ `public string? ShowStackTrace { get; set; }` — attrs: `[CommandLine("-ShowStackTrace=")] [Description("Whether to show full stack trace on errors (true/false)")]`
- L23 _public property_ `public string? UseRegistryPath { get; set; }` — attrs: `[CommandLine("-UseRegistryPath=")] [Description("Use uninstall string as specified in registry")]`
- L30-57 _public method_ `public override Task<int> ExecuteAsync(ILogger logger)` — Uninstall the agent from Windows
- L60-81 _private method_ `private static void Uninstall(bool useRegistryPath, ILogger logger)` — attrs: `[SupportedOSPlatform("windows")]`

### `Source/Programs/Horde/HordeAgent/Commands/Utilities/CapsCommand.cs` (HordeAgent)


#### class `HordeAgent.Commands.Utilities.CapsCommand`  
`class CapsCommand : Command`  
_internal*; L14-47_
- attrs: `[Command("caps", "Lists detected capabilities of this agent")]`
- inherits: `Command`
- desc: Shows capabilities of this agent
- L16 _private* field_ `readonly CapabilitiesService _capabilitiesService`
- L21-24 _public ctor_ `public CapsCommand(CapabilitiesService capabilitiesService)` — Constructor
- L27-46 _public method_ `public override async Task<int> ExecuteAsync(ILogger logger)` — (inheritdoc)

### `Source/Programs/Horde/HordeAgent/Commands/Utilities/CreateCertCommand.cs` (HordeAgent)


#### class `HordeAgent.Commands.Certs.CreateCertCommand`  
`class CreateCertCommand : Command`  
_internal*; L15-81_
- attrs: `[Command("createcert", "Creates a self-signed certificate that can be used for server/agent gRPC connections", Advertise = false)]`
- inherits: `Command`
- desc: Creates a certificate that can be used for server/agent SSL connections
- L18 _public property_ `public string? Server { get; set; }` — attrs: `[CommandLine("-Server=")]`
- L21 _public property_ `public string? DnsName { get; set; }` — attrs: `[CommandLine("-DnsName=")]`
- L24 _public property_ `public string? PrivateCertFile { get; set; }` — attrs: `[CommandLine("-PrivateCert=")]`
- L27 _public property_ `public string? Environment { get; set; }` — attrs: `[CommandLine("-Environment=")]`
- L34-80 _public method_ `public override async Task<int> ExecuteAsync(ILogger logger)` — Main entry point for this command

### `Source/Programs/Horde/HordeAgent/Commands/Utilities/SetServerCommand.cs` (HordeAgent)


#### class `HordeAgent.Commands.Utilities.SetServerCommand`  
`class SetServerCommand : Command`  
_internal*; L17-78_
- attrs: `[Command("setserver", "Configures a server for this agent")]`
- inherits: `Command`
- desc: Shows capabilities of this agent
- L21 _public property_ `public string Name { get; set; }` — attrs: `[CommandLine("-Name=")] [Description("Name of the server to use")]`
- L25 _public property_ `public string? Url { get; set; }` — attrs: `[CommandLine("-Url=", Required = true)] [Description("URL of the server")]`
- L29 _public property_ `public string? Environment { get; set; }` — attrs: `[CommandLine("-Env=")] [Description("Environment to configure for (Prod/Dev).")]`
- L33 _public property_ `public string? Token { get; set; }` — attrs: `[CommandLine("-Token=")] [Description("Token to use for initial connection")]`
- L37 _public property_ `public string? Thumbprint { get; set; }` — attrs: `[CommandLine("-Thumbprint=")] [Description("Optional thumbprint of the server's SSL certificate. Will bypass the CA if matched. Useful for deploying self-signed certs.")]`
- L41 _public property_ `public bool Default { get; set; }` — attrs: `[CommandLine("-Default")] [Description("Makes this server the default")]`
- L44-77 _public method_ `public override async Task<int> ExecuteAsync(ILogger logger)` — (inheritdoc)

### `Source/Programs/Horde/HordeAgent/Commands/Utilities/WatchdogCommand.cs` (HordeAgent)


#### class `HordeAgent.Commands.Utilities.RuntimeWatchdogCommand`  
`class RuntimeWatchdogCommand : Command`  
_internal*; L14-80_
- attrs: `[Command("watchdog", "Test runtime watchdog")]`
- inherits: `Command`
- desc: Test runtime watchdog
- L19-21 _public ctor_ `public RuntimeWatchdogCommand()` — Constructor
- L24-40 _public method_ `public override async Task<int> ExecuteAsync(ILogger logger)` — (inheritdoc)
- L42-64 _internal method_ `internal static void StarveWorkerThreads()`
- L66-79 _private method_ `private static void LogThreadPoolState()`

### `Source/Programs/Horde/HordeAgent/IpcMessages.cs` (HordeAgent)


#### class `HordeAgent.AgentMessagePipe`  
`public static class AgentMessagePipe`  
_public; L13-19_
- desc: Constants
- L18 _public const_ `public const string PipeName = "Horde.Agent"` — Name of the pipe to communicate over

#### enum `HordeAgent.AgentMessageType`  
`public enum AgentMessageType`  
_public; L24-65_
- desc: Message
- L29 _public* enumerator_ `InvalidResponse = 0` — Response indicating that the sent message was invalid
- L34 _public* enumerator_ `GetStatusRequest = 1` — Request the current agent status.
- L39 _public* enumerator_ `GetStatusResponse = 2` — Returns the current status, as a Json-encoded AgentStatusMessage message
- L44 _public* enumerator_ `SetEnabledRequest = 3` — Sets the paused state
- L49 _public* enumerator_ `GetSettingsRequest = 4` — Gets information about the server we're connected to.
- L54 _public* enumerator_ `GetSettingsResponse = 5` — Returns information about the server we're connected to.
- L59 _public* enumerator_ `SetSettingsRequest = 6` — Set agent settings request
- L64 _public* enumerator_ `SetSettingsResponse = 7` — Set agent settings response

#### class `HordeAgent.AgentMessageBuffer`  
`public class AgentMessageBuffer`  
_public; L70-162_
- desc: Buffer used to read/write agent messages
- L72 _private* field_ `static readonly JsonSerializerOptions s_jsonOptions = new JsonSerializerOptions { PropertyNameCaseInsensitive = true, PropertyNamingPolicy = JsonNamingPolicy.CamelCase, DefaultIgnoreCondition = JsonIgnoreCondition.WhenWritingNull }`
- L74 _private* field_ `readonly ArrayMemoryWriter _writer = new ArrayMemoryWriter(256)`
- L79 _public property_ `public AgentMessageType Type { get; set; }` — Type of the message currently in the buffer
- L84 _public property_ `public ReadOnlyMemory<byte> Data => ...` — Gets the full message data
- L89-92 _public ctor_ `public AgentMessageBuffer()` — Constructor
- L99-112 _public method_ `public void Set(AgentMessageType type, object? message = null)` — Sets the current message to the given type, with a json serialized body
- L119-142 _public method_ `public async Task<bool> TryReadAsync(Stream stream, CancellationToken cancellationToken)` — Reads a message from the given stream
- L149-152 _public method_ `public async Task SendAsync(Stream stream, CancellationToken cancellationToken)` — Writes the current message to a stream
- L157-161 _public method_ `public T Parse<T>()` — Parse the message body as a particular type

#### record `HordeAgent.AgentSettingsMessage`  
`public record AgentSettingsMessage(Uri? ServerUrl)`  
_public; L168-168_
- desc: Settings for the agent

#### record `HordeAgent.AgentEnabledMessage`  
`public record AgentEnabledMessage(bool IsEnabled)`  
_public; L174-174_
- desc: Sets the enabled state for the agent

#### record `HordeAgent.AgentSetSettingsRequest`  
`public record AgentSetSettingsRequest(int CpuCount, double CpuMultiplier)`  
_public; L181-181_
- desc: Set settings request message

#### record `HordeAgent.AgentStatusMessage`  
`public record class AgentStatusMessage(bool Healthy, int NumLeases, string Detail)`  
_public; L189-205_
- desc: Current status of the agent
- L194 _public const_ `public const string Starting = "Starting up..."` — Static status object for starting an agent
- L199 _public const_ `public const string WaitingForEnrollment = "Waiting for enrollment..."` — Agent is waiting to be enrolled with the server
- L204 _public const_ `public const string ConnectingToServer = "Connecting to server..."` — Agent is connecting to the server

### `Source/Programs/Horde/HordeAgent/Leases/Handlers/ComputeHandler.cs` (HordeAgent)


#### class `HordeAgent.Leases.Handlers.ComputeHandler`  
`class ComputeHandler : LeaseHandler<ComputeTask>`  
_internal*; L22-158_
- inherits: `LeaseHandler<ComputeTask>`
- desc: Handler for compute tasks
- L24 _private* field_ `readonly ComputeListenerService _listenerService`
- L25 _private* field_ `readonly IOptionsMonitor<AgentSettings> _settings`
- L30-35 _public ctor_ `public ComputeHandler(RpcLease lease, ComputeListenerService listenerService, IOptionsMonitor<AgentSettings> settings) : base(lease)` — Constructor
- L38-120 _protected method_ `protected override async Task<LeaseResult> ExecuteAsync(ISession session, LeaseId leaseId, ComputeTask computeTask, Tracer tracer, ILogger localLogger, CancellationToken cancellationToken)` — (inheritdoc)
- L122-142 _private method_ `private static async Task<ComputeTransport> CreateTransportAsync(ComputeTask computeTask, Socket socket, CancellationToken cancellationToken)`
- L144-157 _private method_ `private void ClearTerminationSignalFile(ILogger logger)`

#### class `HordeAgent.Leases.Handlers.ComputeHandlerFactory`  
`class ComputeHandlerFactory : LeaseHandlerFactory<ComputeTask>`  
_internal*; L160-173_
- inherits: `LeaseHandlerFactory<ComputeTask>`
- L162 _private* field_ `readonly ComputeListenerService _listenerService`
- L163 _private* field_ `readonly IOptionsMonitor<AgentSettings> _settings`
- L165-169 _public ctor_ `public ComputeHandlerFactory(ComputeListenerService listenerService, IOptionsMonitor<AgentSettings> settings)`
- L171 _public method_ `public override LeaseHandler<ComputeTask> CreateHandler(RpcLease lease)`

### `Source/Programs/Horde/HordeAgent/Leases/Handlers/ConformHandler.cs` (HordeAgent)


#### class `HordeAgent.Leases.Handlers.ConformHandler`  
`internal class ConformHandler(RpcLease lease, IOptionsMonitor<AgentSettings> settings) : LeaseHandler<ConformTask>(lease)`  
_internal; L17-51_
- L20-50 _protected method_ `protected override async Task<LeaseResult> ExecuteAsync(ISession session, LeaseId leaseId, ConformTask conformTask, Tracer tracer, ILogger localLogger, CancellationToken cancellationToken)` — (inheritdoc)

#### class `HordeAgent.Leases.Handlers.ConformHandlerFactory`  
`internal class ConformHandlerFactory(IOptionsMonitor<AgentSettings> settings) : LeaseHandlerFactory<ConformTask>`  
_internal; L53-56_
- L55 _public method_ `public override LeaseHandler<ConformTask> CreateHandler(RpcLease lease)`

### `Source/Programs/Horde/HordeAgent/Leases/Handlers/JobHandler.cs` (HordeAgent)


#### class `HordeAgent.Leases.Handlers.JobHandler`  
`class JobHandler : LeaseHandler<ExecuteJobTask>`  
_internal*; L22-385_
- inherits: `LeaseHandler<ExecuteJobTask>`
- L24 _private field_ `private readonly IOptionsMonitor<AgentSettings> _settings`
- L26 _private field_ `private ManagedProcess? _driverProcess`
- L27 _private field_ `private ManagedProcessGroup? _driverProcessGroup`
- L28 _private field_ `private readonly string? _driverCancelEventName`
- L29 _private field_ `private readonly EventWaitHandle? _driverCancelEvent`
- L30 _private const_ `private const string DriverCancelEventKeyName = "UE_HORDE_JOB_EXECUTOR_ABORT_EVENT_NAME"`
- L31 _private* const_ `const double BytesPerMegabyte = 1024.0 * 1024.0`
- L32 _private field_ `private WindowsProcessMemoryTracker? _memoryTracker`
- L37 _private field_ `private readonly CancellationTokenSource _cancellationSource = new()` — The cancellation source to make sure the job driver is always terminated
- L42 _private field_ `private readonly TimeSpan _driverCancelGracePeriod = TimeSpan.FromSeconds(30)` — How long to give the job driver child process to handle the shutdown request before terminating the process ourselves
- L44-50 _public ctor_ `public JobHandler(RpcLease lease, IOptionsMonitor<AgentSettings> settings) : base(lease)`
- L52-83 _private method_ `private static (EventWaitHandle?, string?) CreateDriverCancelEvent(string name)`
- L85-101 _protected method_ `protected override void Dispose(bool disposing)`
- L104-227 _protected method_ `protected override async Task<LeaseResult> ExecuteAsync(ISession session, LeaseId leaseId, ExecuteJobTask executeTask, Tracer tracer, ILogger localLogger, CancellationToken cancellationToken)` — (inheritdoc)
- L229-255 _private method_ `private void DriverCancelHandler()`
- L257-269 _private method_ `private void StartDriverProcess(FileReference entryAssembly, IEnumerable<string> arguments, IReadOnlyDictionary<string, string>? environment, bool useNativeHost, ILogger logger)`
- L271-285 _private method_ `private void StartDriverProcess(string executable, IEnumerable<string> arguments, IReadOnlyDictionary<string, string>? environment, ILogger logger)`
- L287-323 _private method_ `private async Task<int> WaitForDriverProcessExitAsync(ILogger logger, CancellationToken cancellationToken)`
- L326 _private method_ `private static extern int kill(int pid, int sig)` — attrs: `[DllImport("libc", SetLastError = true)]`
- L328-338 _private method_ `private static bool SendSigTerm(int processId)`
- L340-352 _private method_ `private static void LogAgentMemory(long memoryStart, ILogger logger)`
- L355-384 _private method_ `private static void LogChildProcessMemory( ManagedProcessGroup processGroup, WindowsProcessMemoryTracker tracker, ILogger logger)` — attrs: `[System.Runtime.Versioning.SupportedOSPlatform("windows")]`

#### class `HordeAgent.Leases.Handlers.JobHandlerFactory`  
`class JobHandlerFactory : LeaseHandlerFactory<ExecuteJobTask>`  
_internal*; L387-398_
- inherits: `LeaseHandlerFactory<ExecuteJobTask>`
- L389 _private field_ `private readonly IOptionsMonitor<AgentSettings> _settings`
- L391-394 _public ctor_ `public JobHandlerFactory(IOptionsMonitor<AgentSettings> settings)`
- L396 _public method_ `public override LeaseHandler<ExecuteJobTask> CreateHandler(RpcLease lease)`

### `Source/Programs/Horde/HordeAgent/Leases/Handlers/RestartHandler.cs` (HordeAgent)


#### class `HordeAgent.Leases.Handlers.RestartHandler`  
`class RestartHandler : LeaseHandler<RestartTask>`  
_internal*; L14-28_
- inherits: `LeaseHandler<RestartTask>`
- L16-18 _public ctor_ `public RestartHandler(RpcLease lease) : base(lease)`
- L21-27 _protected method_ `protected override async Task<LeaseResult> ExecuteAsync(ISession session, LeaseId leaseId, RestartTask task, Tracer tracer, ILogger logger, CancellationToken cancellationToken)` — (inheritdoc)

#### class `HordeAgent.Leases.Handlers.RestartHandlerFactory`  
`class RestartHandlerFactory : LeaseHandlerFactory<RestartTask>`  
_internal*; L30-34_
- inherits: `LeaseHandlerFactory<RestartTask>`
- L32 _public method_ `public override LeaseHandler<RestartTask> CreateHandler(RpcLease lease)`

### `Source/Programs/Horde/HordeAgent/Leases/Handlers/ShutdownHandler.cs` (HordeAgent)


#### class `HordeAgent.Leases.Handlers.ShutdownHandler`  
`class ShutdownHandler : LeaseHandler<ShutdownTask>`  
_internal*; L14-28_
- inherits: `LeaseHandler<ShutdownTask>`
- L16-18 _public ctor_ `public ShutdownHandler(RpcLease lease) : base(lease)`
- L21-27 _protected method_ `protected override async Task<LeaseResult> ExecuteAsync(ISession session, LeaseId leaseId, ShutdownTask task, Tracer tracer, ILogger logger, CancellationToken cancellationToken)` — (inheritdoc)

#### class `HordeAgent.Leases.Handlers.ShutdownHandlerFactory`  
`class ShutdownHandlerFactory : LeaseHandlerFactory<ShutdownTask>`  
_internal*; L30-34_
- inherits: `LeaseHandlerFactory<ShutdownTask>`
- L32 _public method_ `public override LeaseHandler<ShutdownTask> CreateHandler(RpcLease lease)`

### `Source/Programs/Horde/HordeAgent/Leases/Handlers/UpgradeHandler.cs` (HordeAgent)


#### class `HordeAgent.Leases.Handlers.UpgradeHandler`  
`class UpgradeHandler : LeaseHandler<UpgradeTask>`  
_internal*; L20-196_
- inherits: `LeaseHandler<UpgradeTask>`
- L22-24 _public ctor_ `public UpgradeHandler(RpcLease lease) : base(lease)`
- L27-132 _protected method_ `protected override async Task<LeaseResult> ExecuteAsync(ISession session, LeaseId leaseId, UpgradeTask task, Tracer tracer, ILogger localLogger, CancellationToken cancellationToken)` — (inheritdoc)
- L134-161 _private* method_ `static async Task RunUpgradeAsync(string fileName, string arguments, ILogger logger, CancellationToken cancellationToken)`
- L168-184 _private* method_ `static async Task DeleteDirectoryContentsAsync(DirectoryInfo baseDir)` — Delete the contents of a directory without deleting it itself
- L191-195 _private* method_ `static async Task DeleteDirectoryAsync(DirectoryInfo baseDir)` — Deletes a directory and its contents

#### class `HordeAgent.Leases.Handlers.UpgradeHandlerFactory`  
`class UpgradeHandlerFactory : LeaseHandlerFactory<UpgradeTask>`  
_internal*; L198-202_
- inherits: `LeaseHandlerFactory<UpgradeTask>`
- L200 _public method_ `public override LeaseHandler<UpgradeTask> CreateHandler(RpcLease lease)`

### `Source/Programs/Horde/HordeAgent/Leases/LeaseHandler.cs` (HordeAgent)


#### class `HordeAgent.Leases.LeaseHandler`  
`abstract class LeaseHandler : IDisposable`  
_internal*; L21-306_
- inherits: `IDisposable`
- desc: Handles execution of a specific lease type
- L26 _public property_ `public LeaseId Id { get; }` — Identifier for this lease
- L31 _public property_ `public RpcLease RpcLease { get; set; }` — The RPC lease state
- L36 _public property_ `public Any RpcPayload { get; }` — Payload from the lease
- L41 _public property_ `public Task<LeaseResult> Result { get; set; }` — Result from executing the lease
- L46 _public property_ `public bool IsCancelled => ...` — Whether the lease has been cancelled
- L51 _public property_ `public string CancellationReason => ...` — Reason for cancellation
- L53 _private* field_ `readonly CancellationTokenSource _cancellationSource = new ()`
- L54 _private* field_ `LeaseOutcomeReason _outcomeReason = LeaseOutcomeReason.None`
- L59-65 _protected ctor_ `protected LeaseHandler(RpcLease rpcLease)` — Constructor
- L68-72 _public method_ `public void Dispose()` — (inheritdoc)
- L77-83 _protected method_ `protected virtual void Dispose(bool disposing)` — Overridable dispose method
- L88-102 _public method_ `public void Start(ISession session, ISystemMetrics systemMetrics, Tracer tracer, ILogger logger, LeaseLoggerFactory leaseLoggerFactory)` — Starts executing the lease
- L107-111 _public method_ `public void Cancel(LeaseOutcomeReason reason)` — Cancels the lease
- L116-172 _private* method_ `async Task<LeaseResult> HandleLeaseAsync(ISession session, ISystemMetrics systemMetrics, Tracer tracer, ILogger logger, LeaseLoggerFactory leaseLoggerFactory)` — Handle a lease request
- L177-182 _internal method_ `internal async Task<LeaseResult> HandleLeasePayloadAsync(ISession session, Tracer tracer, LeaseLoggerFactory leaseLoggerFactory)` — Dispatch a lease payload to the appropriate handler
- L188 _protected method_ `protected abstract Task<LeaseResult> ExecuteAsync(ISession session, Tracer tracer, ILogger logger, CancellationToken cancellationToken)` — Executes a lease
- L199-214 _protected method_ `protected static async Task<int> RunProcessAsync(string executable, IEnumerable<string> arguments, IReadOnlyDictionary<string, string>? environment, ILogger logger, CancellationToken cancellationToken)` — Runs a child process, piping the output to the given logger
- L219-241 _private method_ `private static async Task<int> RunProcessCoreAsync(ManagedProcess process, ILogger logger, CancellationToken cancellationToken)` — Core process execution loop
- L253-265 _protected method_ `protected static async Task<int> RunDotNetProcessAsync(FileReference entryAssembly, IEnumerable<string> arguments, IReadOnlyDictionary<string, string>? environment, bool useNativeHost, ILogger logger, CancellationToken cancellationToken)` — Runs a .NET assembly as a child process, piping the output to the given logger
- L267-305 _private method_ `private static RpcLeaseMetrics CalculateLeaseMetrics(CpuTimeMetrics? cpuTimeStart, CpuTimeMetrics? cpuTimeEnd, TimeSpan leaseDuration, TelemetrySpan span, ILogger logger)`

#### class `HordeAgent.Leases.LeaseHandler`  
`abstract class LeaseHandler<T> : LeaseHandler where T : IMessage<T>, new()`  
_internal*; L312-327_
- inherits: `LeaseHandler`
- constraints: `where T : IMessage<T>, new()`
- desc: Implementation of LeaseHandler for a specific lease type
- L314-317 _protected ctor_ `protected LeaseHandler(RpcLease rpcLease) : base(rpcLease)`
- L320-323 _protected method_ `protected override Task<LeaseResult> ExecuteAsync(ISession session, Tracer tracer, ILogger logger, CancellationToken cancellationToken)` — (inheritdoc)
- L326 _protected method_ `protected abstract Task<LeaseResult> ExecuteAsync(ISession session, LeaseId leaseId, T message, Tracer tracer, ILogger logger, CancellationToken cancellationToken)` — (inheritdoc)

#### class `HordeAgent.Leases.DefaultLeaseHandler`  
`class DefaultLeaseHandler : LeaseHandler`  
_internal*; L329-339_
- inherits: `LeaseHandler`
- L331 _private* field_ `readonly LeaseResult _result`
- L333 _public ctor_ `public DefaultLeaseHandler(RpcLease lease, LeaseResult result) : base(lease)`
- L337 _protected method_ `protected override Task<LeaseResult> ExecuteAsync(ISession session, Tracer tracer, ILogger logger, CancellationToken cancellationToken)` — (inheritdoc)

### `Source/Programs/Horde/HordeAgent/Leases/LeaseHandlerFactory.cs` (HordeAgent)


#### class `HordeAgent.Leases.LeaseHandlerFactory`  
`abstract class LeaseHandlerFactory`  
_internal*; L9-21_
- L14 _public property_ `public abstract string LeaseType { get; }` — Returns protobuf type urls for the handled message types
- L20 _public method_ `public abstract LeaseHandler CreateHandler(RpcLease lease)` — Creates a new lease handler for the given lease definition

#### class `HordeAgent.Leases.LeaseHandlerFactory`  
`abstract class LeaseHandlerFactory<T> : LeaseHandlerFactory where T : IMessage<T>, new()`  
_internal*; L27-42_
- inherits: `LeaseHandlerFactory`
- constraints: `where T : IMessage<T>, new()`
- desc: Implementation of LeaseHandler for a specific lease type
- L32 _public property_ `public static MessageDescriptor Descriptor { get; }` — Static for the message type descriptor
- L35 _public property_ `public override string LeaseType { get; }` — (inheritdoc)
- L41 _public method_ `public abstract override LeaseHandler<T> CreateHandler(RpcLease lease)` — Creates a new lease handler for the given lease definition

### `Source/Programs/Horde/HordeAgent/Leases/LeaseLoggerFactory.cs` (HordeAgent)


#### class `HordeAgent.Leases.LeaseLoggerFactory`  
`sealed class LeaseLoggerFactory : IAsyncDisposable`  
_internal*; L13-108_
- inherits: `IAsyncDisposable`
- desc: Creates local log files for leases executed on this agent
- L15 _private* property_ `static TimeSpan MaxAge { get; }`
- L17 _private* field_ `readonly IOptionsMonitor<AgentSettings> _settings`
- L18 _private* field_ `readonly DirectoryReference _logDir`
- L19 _private* field_ `readonly BackgroundTask _backgroundTask`
- L20 _private* field_ `readonly ILogger _logger`
- L25-31 _public ctor_ `public LeaseLoggerFactory(IOptionsMonitor<AgentSettings> settings, ILogger<LeaseLoggerFactory> logger)` — Constructor
- L34-37 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L42-70 _public method_ `public void Cleanup(TimeSpan maxAge)` — Remove all log files older than the given time
- L88-98 _public method_ `public ILoggerFactory CreateLoggerFactory(LeaseId leaseId)` — Create a new logger factory for the given lease id
- L100-107 _private* method_ `async Task BackgroundCleanupAsync(CancellationToken cancellationToken)`

#### class `HordeAgent.Leases.LeaseLoggerFactory.LoggerProvider`  
`class LoggerProvider : ILoggerProvider`  
_private*; L72-83_
- inherits: `ILoggerProvider`
- L74 _private* field_ `readonly ILogger _logger`
- L76 _public ctor_ `public LoggerProvider(ILogger logger)`
- L79 _public method_ `public ILogger CreateLogger(string categoryName)`
- L82 _public method_ `public void Dispose()`

### `Source/Programs/Horde/HordeAgent/Leases/LeaseManager.cs` (HordeAgent)


#### class `HordeAgent.Leases.LeaseManager`  
`class LeaseManager`  
_internal*; L24-630_
- desc: Implements the message handling loop for an agent. Runs asynchronously until disposed.
- L29 _public property_ `public int NumLeasesCompleted { get; set; }` — Number of leases completed
- L34 _public delegate_ `public delegate void LeaseEvent(RpcLease lease, LeaseResult? result = null)` — Delegate for lease active events
- L39 _public event_ `public event LeaseEvent? OnLeaseStarted` — Event triggered when a lease is accepted and started
- L44 _public event_ `public event LeaseEvent? OnLeaseFinished` — Event triggered when a lease is finished with an outcome
- L49 _public property_ `public IReadOnlyList<string> PoolIds { get; set; }` — List of pool IDs this session is a member of
- L55 _public property_ `public bool TerminateSessionAfterLease { get; set; }` — Whether to terminate session after at least one lease has finished Useful for shutting down as gracefully as possible without interrupting the current lease executing.
- L60 _private* field_ `readonly Lock _lockObject = new Lock()` — Object used for controlling access to the access tokens and active sessions list
- L65 _private* field_ `readonly List<LeaseHandler> _activeLeases = new List<LeaseHandler>()` — The list of active leases.
- L70 _private* field_ `readonly bool _unhealthy = false` — Whether the agent is currently in an unhealthy state
- L75 _private* field_ `SessionResult? _sessionResult` — Result from executing this session
- L80 _private* field_ `readonly AsyncEvent _updateLeasesEvent = new AsyncEvent()` — Task completion source used to trigger the background thread to update the leases. Must take a lock on LockObject before
- L85 _private* field_ `int _updateSessionFailures` — Number of times UpdateSession has failed
- L91 _internal field_ `internal TimeSpan _rpcConnectionRetryDelay = TimeSpan.FromSeconds(5)` — How long to wait before trying to reacquire a new connection Exposed as internal to ease testing. Using a lower delay can speed up tests.
- L93 _private* field_ `readonly ISession _session`
- L94 _private* field_ `readonly ICapabilitiesService _capabilitiesService`
- L95 _private* field_ `readonly StatusService _statusService`
- L96 _private* field_ `readonly ISystemMetrics _systemMetrics`
- L97 _private* field_ `readonly Dictionary<string, LeaseHandlerFactory> _typeUrlToLeaseHandler`
- L97 _private* field_ `readonly Dictionary< _typeUrlToLeaseHandler`
- L98 _private* field_ `readonly LeaseLoggerFactory _leaseLoggerFactory`
- L99 _private* field_ `readonly IOptionsMonitor<AgentSettings> _settings`
- L100 _private* field_ `readonly Tracer _tracer`
- L101 _private* field_ `readonly ILogger _logger`
- L103 _private* field_ `RpcAgentCapabilities? _capabilities`
- L105-125 _public ctor_ `public LeaseManager( ISession session, ICapabilitiesService capabilitiesService, StatusService statusService, ISystemMetrics systemMetrics, IEnumerable<LeaseHandlerFactory> leaseHandlerFactories, LeaseLoggerFactory leaseLoggerFactory, IOptionsMonitor<AgentSettings> settings, Tracer tracer, ILogger logger)`
- L127-138 _public ctor_ `public LeaseManager(ISession session, IServiceProvider serviceProvider) : this(session, serviceProvider.GetRequiredService<CapabilitiesService>(), serviceProvider.GetRequiredService<StatusService>(), serviceProvider.GetRequiredService<ISystemMetrics>(), serviceProvider.GetRequiredService<IEnumerable<LeaseHandlerFactory>>(), serviceProvider.GetRequiredService<LeaseLoggerFactory>(), serviceProvider.GetRequiredService<IOptionsMonitor<AgentSettings>>(), serviceProvider.GetRequiredService<Tracer>(), serviceProvider.GetRequiredService<ILogger<LeaseManager>>())`
- L140-146 _public method_ `public List<RpcLease> GetActiveLeases()`
- L157-165 _public method_ `public static Task WriteTerminationSignalFileAsync(string filePath, string reason, DateTime terminateAt, TimeSpan timeToLive, CancellationToken cancellationToken)` — Write a termination signal file to disk Used to communicate an impending termination of workload. It does require workload to be aware of the file and also act on it.
- L167-199 _public method_ `public async Task<SessionResult> RunAsync(CancellationToken stoppingToken)`
- L206-262 _private* method_ `async Task DrainLeasesAsync(LeaseOutcomeReason reason, bool graceful = false)` — Drain and terminate any currently running leases
- L264-464 _private* method_ `async Task<SessionResult> HandleSessionAsync(CancellationToken stoppingToken)`
- L466-475 _private* method_ `LeaseHandler CreateLeaseHandler(RpcLease lease)`
- L484-509 _private* method_ `async Task<RpcUpdateSessionResponse?> UpdateSessionAsync(HordeRpc.HordeRpcClient hordeRpc, RpcUpdateSessionRequest updateSessionRequest, Task waitTask)` — Wrapper for UpdateSessionInternalAsync which filters/logs exceptions
- L523-552 _private* method_ `async Task<RpcUpdateSessionResponse?> UpdateSessionInternalAsync(HordeRpc.HordeRpcClient rpcClient, RpcUpdateSessionRequest request, Task waitTask)` — Tries to update the session state on the server. This operation is a little gnarly due to the fact that we want to long-poll for the result. Since we're doing the update via a gRPC call, the way to do that without using cancellation tokens is to keep the request stream open until we want to terminate the call (see https://github.com/grpc/grpc/issues/8277). In order to do that, we need to make a bidirectional streaming call, even though we only expect one response/response.
- L557-571 _private* method_ `async Task UpdateCapabilitiesBackgroundAsync(DirectoryReference workingDir, CancellationToken cancellationToken)` — Background task that updates the capabilities of this agent
- L576-629 _private* method_ `async Task SendTelemetryAsync(HordeRpc.HordeRpcClient hordeRpc, CancellationToken cancellationToken)` — Periodically send agent telemetry to the server

### `Source/Programs/Horde/HordeAgent/Leases/LeaseResult.cs` (HordeAgent)


#### class `HordeAgent.Leases.LeaseResult`  
`internal class LeaseResult`  
_internal; L11-66_
- desc: Result from executing a lease
- L16 _public property_ `public LeaseOutcome Outcome { get; }` — Outcome of the lease (whether it completed/failed due to an internal error, etc...)
- L21 _public property_ `public LeaseOutcomeReason OutcomeReason { get; }` — Reason for the outcome of the lease
- L26 _public property_ `public byte[]? Output { get; }` — Output from executing the task
- L31 _public property_ `public SessionResult? SessionResult { get; }` — If a lease wants to terminate the current session, this specifies the subsequent action to take.
- L36 _public property_ `public static LeaseResult Success { get; }` — Static instance of a succesful result without a payload
- L41-45 _public ctor_ `public LeaseResult(LeaseOutcome outcome, LeaseOutcomeReason outcomeReason)` — Constructor
- L51-55 _public ctor_ `public LeaseResult(byte[]? output)` — Constructor for successful results
- L61-65 _public ctor_ `public LeaseResult(SessionResult sessionResult)` — Constructor for successful results that cause a session state change

### `Source/Programs/Horde/HordeAgent/Logging.cs` (HordeAgent)


#### class `HordeAgent.Logging`  
`static class Logging`  
_internal*; L16-78_
- L18 _public field_ `public static LoggingLevelSwitch LogLevelSwitch = new ()`
- L28-32 _public method_ `public static ILoggerFactory CreateLoggerFactory(IConfiguration configuration)`
- L34-64 _private* method_ `static Serilog.ILogger CreateSerilogLogger(IConfiguration configuration)`
- L66-77 _public method_ `public static ILoggerProvider CreateFileLoggerProvider(DirectoryReference baseDir, string name)`

#### class `HordeAgent.Logging.DatadogVersionLogEnricher`  
`private class DatadogVersionLogEnricher : ILogEventEnricher`  
_private; L20-26_
- inherits: `ILogEventEnricher`
- L22-25 _public method_ `public void Enrich(Serilog.Events.LogEvent logEvent, ILogEventPropertyFactory propertyFactory)`

### `Source/Programs/Horde/HordeAgent/Properties/AssemblyInfo.cs` (HordeAgent)
_(no declarations)_


### `Source/Programs/Horde/HordeAgent/Services/AwsInstanceLifecycleService.cs` (HordeAgent)


#### enum `HordeAgent.Services.Ec2InstanceState`  
`public enum Ec2InstanceState`  
_public; L16-39_
- desc: Describes state of local EC2 instance the agent is running on
- L22 _public* enumerator_ `Unknown` — Unknown state Likely because of a failed HTTP request to local IMDS server
- L27 _public* enumerator_ `InService` — Normal state
- L32 _public* enumerator_ `TerminatingSpot` — Termination is caused by a spot interruption.
- L38 _public* enumerator_ `TerminatingAsg` — Termination is caused by the auto-scaling group Can be caused by capacity re-balancing, scale-ins etc.

#### class `HordeAgent.Services.Ec2TerminationInfo`  
`internal class Ec2TerminationInfo(Ec2InstanceState state, bool isSpot, TimeSpan timeToLive, DateTime terminateAt, string reason)`  
_internal; L41-48_
- L43 _public property_ `public Ec2InstanceState State { get; }`
- L44 _public property_ `public bool IsSpot { get; }`
- L45 _public property_ `public TimeSpan TimeToLive { get; }`
- L46 _public property_ `public DateTime TerminateAt { get; }`
- L47 _public property_ `public string Reason { get; }`

#### class `HordeAgent.Services.AwsInstanceLifecycleService`  
`class AwsInstanceLifecycleService : BackgroundService`  
_internal*; L53-287_
- inherits: `BackgroundService`
- desc: Monitors the local EC2 instance lifecycle state. In particular, auto-scaling group and spot instance events.
- L58 _public const_ `public const string HttpClientName = "Horde.HttpAwsInstanceClient"` — Name of the HTTP client used for requests to IMDS
- L60 _public const_ `public const string ImdsBaseUri = "http://169.254.169.254"`
- L61 _public const_ `public const string ImdsTokenPath = "/latest/api/token"`
- L62 _public const_ `public const string ImdsInstanceLifeCyclePath = "/latest/meta-data/instance-life-cycle"`
- L63 _public const_ `public const string ImdsSpotActionPath = "/latest/meta-data/spot/instance-action"`
- L64 _public const_ `public const string ImdsAsgTargetStatePath = "/latest/meta-data/autoscaling/target-lifecycle-state"`
- L65 _public const_ `public const string ImdsTokenHeader = "X-aws-ec2-metadata-token"`
- L66 _public const_ `public const string ImdsTokenTtlHeader = "X-aws-ec2-metadata-token-ttl-seconds"`
- L67 _public const_ `public const string ImdsTokenTtl = "21600"`
- L69 _private field_ `private readonly IWorkerService _workerService`
- L70 _private field_ `private readonly HttpClient _httpClient`
- L71 _private field_ `private readonly IClock _clock`
- L72 _private field_ `private readonly FileReference _terminationSignalFile`
- L73 _private field_ `private readonly ILogger<AwsInstanceLifecycleService> _logger`
- L74 _private field_ `private readonly TimeSpan _pollInterval = TimeSpan.FromSeconds(5)`
- L75 _private field_ `private string? _imdsToken`
- L76 _private field_ `private DateTime? _imdsTokenExpireTime = DateTime.UnixEpoch`
- L78 _internal delegate_ `internal delegate Task TerminationWarningDelegate(Ec2TerminationInfo info, CancellationToken cancellationToken)`
- L79 _internal delegate_ `internal delegate Task TerminationDelegate(Ec2TerminationInfo info, CancellationToken cancellationToken)`
- L80 _internal field_ `internal TerminationWarningDelegate _terminationWarningCallback`
- L81 _internal field_ `internal TerminationDelegate _terminationCallback`
- L88 _internal field_ `internal TimeSpan _timeToLiveAsg = TimeSpan.FromSeconds(120)` — Time to live for EC2 instance once a termination is detected coming from the auto-scaling group (ASG) In practice, this is dictated by the lifecycle hook set for the ASG. Set to 120 sec to mimic the TTL for spot interruption, leading to similar handling of both for now.
- L93 _internal field_ `internal TimeSpan _timeToLiveSpot = TimeSpan.FromSeconds(120)` — Time to live for EC2 instance once a spot interruption is detected. Strictly defined by AWS EC2.
- L99 _internal field_ `internal TimeSpan _terminationBufferTime = TimeSpan.FromSeconds(30)` — Duration of the time-to-live to allocate towards shutting down the Horde agent and the machine itself. Example: if TTL is 120 seconds, 90 seconds will be reported in the termination warning.
- L104-114 _public ctor_ `public AwsInstanceLifecycleService(IWorkerService workerService, HttpClient httpClient, IClock clock, IOptionsMonitor<AgentSettings> settings, ILogger<AwsInstanceLifecycleService> logger)` — Constructor
- L116-133 _private method_ `private async Task<HttpResponseMessage> GetMetadataAsync(string path, CancellationToken cancellationToken)`
- L135-144 _internal method_ `internal async Task<bool> IsSpotInstanceAsync(CancellationToken cancellationToken)`
- L146-170 _private method_ `private async Task<Ec2InstanceState> GetStateAsync(CancellationToken cancellationToken)`
- L172-184 _private method_ `private async Task<bool> IsImdsAvailableAsync(CancellationToken cancellationToken)`
- L186-225 _internal method_ `internal async Task MonitorInstanceLifecycleAsync(CancellationToken cancellationToken)`
- L233-241 _private method_ `private TimeSpan GetTimeToLive(Ec2InstanceState state)` — Determine time to live for the current EC2 instance once a terminating state has been detected
- L243-251 _private method_ `private static string GetReason(Ec2InstanceState state)`
- L253-262 _private method_ `private async Task OnTerminationWarningAsync(Ec2TerminationInfo info, CancellationToken cancellationToken)`
- L264-273 _private method_ `private Task OnTerminationAsync(Ec2TerminationInfo info, CancellationToken cancellationToken)`
- L276-286 _protected method_ `protected override async Task ExecuteAsync(CancellationToken stoppingToken)` — (inheritdoc)

### `Source/Programs/Horde/HordeAgent/Services/CapabilitiesService.cs` (HordeAgent)


#### interface `HordeAgent.Services.ICapabilitiesService`  
`internal interface ICapabilitiesService`  
_internal; L25-33_
- L32 _public* method_ `Task<RpcAgentCapabilities> GetCapabilitiesAsync(DirectoryReference? workingDir)` — Gets the hardware capabilities of this worker

#### interface `HordeAgent.Services.ISystemCapabilities`  
`internal interface ISystemCapabilities : ICapabilitiesService`  
_internal; L38-38_
- inherits: `ICapabilitiesService`
- desc: Marker interface to separate system-specific capability services during dependency-injection

#### class `HordeAgent.Services.CapabilitiesService`  
`class CapabilitiesService : ICapabilitiesService`  
_internal*; L43-671_
- inherits: `ICapabilitiesService`
- desc: Implements the message handling loop for an agent. Runs asynchronously until disposed.
- L45 _private* field_ `static readonly DateTimeOffset s_startTime = DateTimeOffset.Now`
- L46 _private* field_ `static readonly DateTimeOffset s_bootTime = DateTimeOffset.Now - TimeSpan.FromTicks(Environment.TickCount64 * TimeSpan.TicksPerMillisecond)`
- L48 _private* field_ `readonly IOptionsMonitor<AgentSettings> _settings`
- L49 _private* field_ `readonly Tracer _tracer`
- L50 _private* field_ `readonly ILogger _logger`
- L55-60 _public ctor_ `public CapabilitiesService(IOptionsMonitor<AgentSettings> settings, Tracer tracer, ILogger<CapabilitiesService> logger)` — Constructor
- L63-88 _public method_ `public async Task<RpcAgentCapabilities> GetCapabilitiesAsync(DirectoryReference? workingDir)` — (inheritdoc)
- L95-122 _public method_ `public async Task<RpcAgentCapabilities> GetCapabilitiesWithTimeoutMonitoringAsync(DirectoryReference? workingDir)` — Gets the hardware capabilities of this worker
- L124-487 _private* method_ `async Task<RpcAgentCapabilities> GetCapabilitiesInternalAsync(DirectoryReference? workingDir)`
- L492-509 _public method_ `public static bool IsUserAdministrator()` — Determine if the current user is a running with elevated permissions on Windows (UAC)
- L520-539 _private method_ `private async Task<IPAddress?> GetLocalIpAddressAsync(string hostname, int timeoutMs = 2000)` — Resolve local IP address of agent A machine can have multiple valid IP addresses, but not all suitable for accepting incoming traffic. By establishing a socket to a well-known host on a relevant network, a better guess can be made.
- L541-562 _public method_ `public static void AddCpuInfo(AgentSettings settings, RpcAgentCapabilities capabilities, string cpuName, int numLogicalCores, int numPhysicalCores)`
- L564-570 _public method_ `public static void AddMemInfo(AgentSettings settings, RpcAgentCapabilities capabilities, int ramGb)`
- L572-617 _private* method_ `static async Task<List<Dictionary<string, string>>?> ReadLinuxHwPropsAsync(string fileName, ILogger logger)`
- L619-629 _private* method_ `async Task AddAwsPropertiesAsync(IList<string> properties, ILogger logger)`
- L631-661 _private* method_ `async Task AddAwsPropertiesInternalAsync(IList<string> properties, ILogger logger)`
- L663-670 _private* method_ `static void AddAwsProperty(string name, string awsKey, IList<string> properties)`

### `Source/Programs/Horde/HordeAgent/Services/ComputeListenerService.cs` (HordeAgent)


#### class `HordeAgent.Services.ComputeListenerService`  
`class ComputeListenerService : IHostedService, IDisposable`  
_internal*; L16-222_
- inherits: `IHostedService, IDisposable`
- desc: Service which listens for incoming connections that can be assigned for remote execution leases
- L47 _private* field_ `readonly IOptionsMonitor<AgentSettings> _settings`
- L48 _private* field_ `readonly ILogger _logger`
- L50 _private* field_ `Task _serverTask = Task.CompletedTask`
- L51 _private* field_ `readonly CancellationTokenSource _cancellationSource = new CancellationTokenSource()`
- L53 _private* field_ `readonly Lock _lockObject = new Lock()`
- L54 _private* field_ `readonly Dictionary<ByteString, WaitingClient> _waitingClients = ...`
- L54 _private* field_ `readonly Dictionary< _waitingClients = new Dictionary<ByteString, WaitingClient>()`
- L55 _private* field_ `readonly Dictionary<ByteString, TaskCompletionSource<TcpClient?>> _waitingLeases = ...`
- L55 _private* field_ `readonly Dictionary< _waitingLeases = new Dictionary<ByteString, TaskCompletionSource<TcpClient?>>()`
- L60-64 _public ctor_ `public ComputeListenerService(IOptionsMonitor<AgentSettings> settings, ILogger<ComputeListenerService> logger)` — Constructor
- L67-70 _public method_ `public void Dispose()` — (inheritdoc)
- L79-111 _public method_ `public async Task<TcpClient?> WaitForClientAsync(ByteString nonce, TimeSpan timeout, CancellationToken cancellationToken)` — Waits for a client to connect with the given connection id
- L114-121 _public method_ `public Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L128-131 _public method_ `public void Start(IPAddress address, int port)` — Starts listening for connections on the given address and port. Primarily for testing; the hosted service will use settings for this from the configuration file.
- L134-138 _public method_ `public async Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L140-162 _private* method_ `async Task RunTcpListenerAsync(IPAddress address, int port, CancellationToken cancellationToken)`
- L164-221 _private* method_ `async Task WaitForLeaseAsync(TcpClient tcpClient, CancellationToken cancellationToken)`

#### class `HordeAgent.Services.ComputeListenerService.WaitingClient`  
`class WaitingClient : IDisposable`  
_private*; L18-45_
- inherits: `IDisposable`
- L20 _private* field_ `TcpClient? _tcpClient`
- L21 _private* field_ `readonly TaskCompletionSource _takenTaskSource = new TaskCompletionSource(TaskCreationOptions.RunContinuationsAsynchronously)`
- L23-26 _public ctor_ `public WaitingClient(TcpClient tcpClient)`
- L28-37 _public method_ `public TcpClient? TakeClient()`
- L39 _public method_ `public Task WaitForTransferAsync()`
- L41-44 _public method_ `public void Dispose()`

### `Source/Programs/Horde/HordeAgent/Services/GrpcService.cs` (HordeAgent)


#### class `HordeAgent.Services.GrpcService`  
`class GrpcService`  
_internal*; L19-151_
- desc: Service which creates a configured Grpc channel
- L21 _private field_ `private readonly IOptionsMonitor<AgentSettings> _settings`
- L22 _private field_ `private readonly ServerProfile _serverProfile`
- L23 _private field_ `private readonly ILogger _logger`
- L24 _private field_ `private readonly ILoggerFactory _loggerFactory`
- L29 _public property_ `public ServerProfile ServerProfile => ...` — The current server profile
- L37-43 _public ctor_ `public GrpcService(IOptionsMonitor<AgentSettings> settings, ILogger<GrpcService> logger, ILoggerFactory loggerFactory)` — Constructor
- L49-132 _public method_ `public async Task<GrpcChannel> CreateGrpcChannelAsync(string? bearerToken, CancellationToken cancellationToken)` — Create a GRPC channel with the given bearer token
- L140-150 _public method_ `public CallInvoker GetInvoker(GrpcChannel channel)` — Get a gRPC call invoker for the given channel with extra metadata attached, such as current version and name

### `Source/Programs/Horde/HordeAgent/Services/ManagementService.cs` (HordeAgent)


#### interface `HordeAgent.Services.IHttpListenerRequest`  
`internal interface IHttpListenerRequest`  
_internal; L14-17_
- L16 _public* property_ `Uri? Url { get; }`

#### interface `HordeAgent.Services.IHttpListenerResponse`  
`internal interface IHttpListenerResponse`  
_internal; L19-28_
- L21 _public* property_ `string? ContentType { get; set; }`
- L22 _public* property_ `int StatusCode { get; set; }`
- L23 _public* property_ `long ContentLength64 { get; set; }`
- L24 _public* property_ `WebHeaderCollection Headers { get; set; }`
- L25 _public* property_ `CookieCollection Cookies { get; set; }`
- L26 _public* property_ `Stream OutputStream { get; }`
- L27 _public* method_ `void Close()`

#### class `HordeAgent.Services.WrappedHttpListenerRequest`  
`internal class WrappedHttpListenerRequest(HttpListenerRequest impl) : IHttpListenerRequest`  
_internal; L30-33_
- L32 _public property_ `public Uri? Url => ...`

#### class `HordeAgent.Services.WrappedHttpListenerResponse`  
`internal class WrappedHttpListenerResponse(HttpListenerResponse impl) : IHttpListenerResponse`  
_internal; L35-44_
- L37 _public property_ `public string? ContentType { get; set; }`
- L38 _public property_ `public int StatusCode { get; set; }`
- L39 _public property_ `public long ContentLength64 { get; set; }`
- L40 _public property_ `public WebHeaderCollection Headers { get; set; }`
- L41 _public property_ `public CookieCollection Cookies { get; set; }`
- L42 _public property_ `public Stream OutputStream => ...`
- L43 _public method_ `public void Close()`

#### class `HordeAgent.Services.ErrorResponse`  
`internal class ErrorResponse(bool success, string message)`  
_internal; L48-52_
- L50 _public property_ `public bool Success { get; set; }`
- L51 _public property_ `public string Message { get; set; }`

#### class `HordeAgent.Services.HealthCheckResponse`  
`internal class HealthCheckResponse(bool isHealthy, bool isConnected)`  
_internal; L54-58_
- L56 _public property_ `public bool IsHealthy { get; set; }`
- L57 _public property_ `public bool IsConnected { get; set; }`

#### class `HordeAgent.Services.PoolsResponse`  
`internal class PoolsResponse(List<string> poolIds)`  
_internal; L60-63_
- L62 _public property_ `public List<string> PoolIds { get; set; }`

#### class `HordeAgent.Services.ManagementService`  
`internal class ManagementService : IHostedService, IDisposable`  
_internal; L68-284_
- inherits: `IHostedService, IDisposable`
- desc: Handles agent's built-in HTTP server used for admin tasks and health check
- L70 _private field_ `private readonly HttpListener? _adminListener`
- L71 _private field_ `private readonly HttpListener? _healthListener`
- L72 _private field_ `private readonly Thread? _adminThread`
- L73 _private field_ `private readonly Thread? _healthThread`
- L74 _private field_ `private readonly ILogger<ManagementService> _logger`
- L75 _private field_ `private bool _isStopping = false`
- L76 _private field_ `private bool _isDisposed = false`
- L78 _public field_ `public static readonly JsonSerializerOptions JsonSerializerOptions = new() { WriteIndented = true, PropertyNameCaseInsensitive = true, PropertyNamingPolicy = JsonNamingPolicy.CamelCase }`
- L83 _private field_ `private readonly RoutesDict _adminRoutes = new() { ["/"] = HandleJson((_, _) => "Admin server"), }`
- L84 _private field_ `private readonly RoutesDict _healthRoutes`
- L86-96 _private method_ `private static Action<IHttpListenerRequest, IHttpListenerResponse> HandleJson<T>(Func<IHttpListenerRequest, IHttpListenerResponse, T> callback)`
- L101-146 _public ctor_ `public ManagementService(IOptionsMonitor<AgentSettings> settings, IWorkerService workerService, ILogger<ManagementService> logger)` — Constructor
- L148-170 _public method_ `public void Dispose()`
- L173-202 _public method_ `public Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L205-209 _public method_ `public Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L211-214 _internal method_ `internal void TestAdminRoute(IHttpListenerRequest req, IHttpListenerResponse res)`
- L216-219 _internal method_ `internal void TestHealthRoute(IHttpListenerRequest req, IHttpListenerResponse res)`
- L221-248 _private method_ `private void HandleRequest(IHttpListenerRequest req, IHttpListenerResponse res, RoutesDict routes)`
- L250-283 _private method_ `private void RunServerSync(HttpListener listener, RoutesDict routes, string serverType)`

### `Source/Programs/Horde/HordeAgent/Services/SessionFactory.cs` (HordeAgent)


#### interface `HordeAgent.Services.ISession`  
`interface ISession : IAsyncDisposable`  
_internal*; L24-45_
- inherits: `IAsyncDisposable`
- desc: Interface for about the current session.
- L29 _public* property_ `AgentId AgentId { get; }` — The agent identifier
- L34 _public* property_ `SessionId SessionId { get; }` — Identifier for the current session
- L39 _public* property_ `DirectoryReference WorkingDir { get; }` — Working directory for sandboxes etc..
- L44 _public* property_ `IHordeClient HordeClient { get; }` — Horde client instance

#### interface `HordeAgent.Services.ISessionFactory`  
`interface ISessionFactory`  
_internal*; L50-58_
- desc: Interface for a factory to create sessions
- L57 _public method_ `public Task<ISession> CreateAsync(CancellationToken cancellationToken)` — Creates a new session

#### class `HordeAgent.Services.Session`  
`sealed class Session : ISession`  
_internal*; L63-341_
- inherits: `ISession`
- desc: Information about the current session.
- L66 _public property_ `public AgentId AgentId { get; }` — (inheritdoc)
- L69 _public property_ `public SessionId SessionId { get; }` — (inheritdoc)
- L72 _public property_ `public DirectoryReference WorkingDir { get; }` — (inheritdoc)
- L75 _public property_ `public IHordeClient HordeClient { get; }` — (inheritdoc)
- L80-86 _public ctor_ `public Session(AgentId agentId, SessionId sessionId, DirectoryReference workingDir, IHordeClient hordeClient)` — Constructor
- L98-213 _public method_ `public static async Task<Session> CreateAsync(CapabilitiesService capabilitiesService, GrpcService grpcService, StatusService statusService, IOptionsMonitor<AgentSettings> settings, HordeClientFactory hordeClientFactory, ILogger logger, CancellationToken cancellationToken)` — Creates a new agent session
- L219-225 _public method_ `public async ValueTask DisposeAsync()` — Dispose of the current session
- L227-242 _private* method_ `static FileReference GetRegistrationFile()`
- L244-254 _private* method_ `static async Task<AgentRegistrationList> ReadRegistrationListAsync(FileReference settingsFile, CancellationToken cancellationToken)`
- L256-261 _private* method_ `static async Task WriteRegistrationListAsync(FileReference settingsFile, AgentRegistrationList registrationList, CancellationToken cancellationToken)`
- L263-328 _private* method_ `static async Task<AgentRegistration> RegisterAgentAsync(HordeClientFactory hordeClientFactory, AgentSettings agentSettings, RpcAgentCapabilities capabilities, ILogger logger, CancellationToken cancellationToken)`
- L330-340 _private* method_ `static string? GetProperty(RpcAgentCapabilities capabilities, string name)`

#### class `HordeAgent.Services.Session.AgentRegistrationList`  
`public class AgentRegistrationList`  
_public; L88-91_
- L90 _public property_ `public List<AgentRegistration> Entries { get; set; }`

#### record `HordeAgent.Services.Session.AgentRegistration`  
`public record class AgentRegistration(Uri Server, string Id, string Token)`  
_public; L93-93_

#### class `HordeAgent.Services.SessionFactory`  
`class SessionFactory : ISessionFactory`  
_internal*; L346-370_
- inherits: `ISessionFactory`
- desc: Creates session objects
- L348 _private* field_ `readonly CapabilitiesService _capabilitiesService`
- L349 _private* field_ `readonly GrpcService _grpcService`
- L350 _private* field_ `readonly StatusService _statusService`
- L351 _private* field_ `readonly HordeClientFactory _hordeClientFactory`
- L352 _private* field_ `readonly IOptionsMonitor<AgentSettings> _agentSettings`
- L353 _private* field_ `readonly ILogger _logger`
- L358-366 _public ctor_ `public SessionFactory(CapabilitiesService capabilitiesService, GrpcService grpcService, StatusService statusService, HordeClientFactory hordeClientFactory, IOptionsMonitor<AgentSettings> agentSettings, ILogger<SessionFactory> logger)` — Constructor
- L369 _public method_ `public async Task<ISession> CreateAsync(CancellationToken cancellationToken)` — (inheritdoc)

### `Source/Programs/Horde/HordeAgent/Services/SessionResult.cs` (HordeAgent)


#### enum `HordeAgent.Services.SessionOutcome`  
`enum SessionOutcome`  
_internal*; L10-26_
- desc: Outcome from a session
- L15 _public* enumerator_ `BackOff` — Continue the session with a backoff
- L20 _public* enumerator_ `Terminate` — Session completed normally, terminate the application.
- L25 _public* enumerator_ `RunCallback` — Runs the given callback then attempts to reconnect

#### enum `HordeAgent.Services.SessionReason`  
`enum SessionReason`  
_internal*; L31-47_
- desc: Reason for outcome of a session
- L36 _public* enumerator_ `Completed` — Session completed its operations normally
- L41 _public* enumerator_ `Failed` — Session encountered an unrecoverable error
- L46 _public* enumerator_ `Cancelled` — Session was explicitly cancelled by user or system

#### class `HordeAgent.Services.SessionResult`  
`class SessionResult : IEquatable<SessionResult>`  
_internal*; L52-106_
- inherits: `IEquatable<SessionResult>`
- desc: Result from executing a session
- L57 _public property_ `public SessionOutcome Outcome { get; }` — The outcome code
- L62 _public property_ `public SessionReason Reason { get; }` — Reason for the outcome
- L67 _public property_ `public Func<ILogger, CancellationToken, Task>? CallbackAsync { get; }` — Callback for running upgrades
- L72-76 _public ctor_ `public SessionResult(SessionOutcome outcome, SessionReason reason)` — Constructor
- L81-85 _public ctor_ `public SessionResult(Func<ILogger, CancellationToken, Task> callbackAsync)` — Constructor
- L87-90 _public method_ `public bool Equals(SessionResult? other)`
- L92-95 _public method_ `public override bool Equals(object? obj)`
- L97-100 _public method_ `public override int GetHashCode()`
- L102-105 _public method_ `public override string ToString()`

### `Source/Programs/Horde/HordeAgent/Services/StatusService.cs` (HordeAgent)


#### class `HordeAgent.Services.StatusService`  
`class StatusService : IHostedService, IAsyncDisposable`  
_internal*; L18-232_
- inherits: `IHostedService, IAsyncDisposable`
- desc: Tracks the current status of the agent
- L20 _private* const_ `const int NumPipes = 10`
- L22 _private field_ `private AgentStatusMessage _current`
- L23 _private field_ `private bool _isBusy`
- L24 _private field_ `private bool _isStopRequested`
- L26 _private* field_ `readonly IOptionsMonitor<AgentSettings> _settings`
- L27 _private* field_ `readonly BackgroundTask _task`
- L28 _private* field_ `readonly ILogger _logger`
- L33 _public property_ `public AgentStatusMessage Current => ...` — The current agent status
- L38-49 _public property_ `public bool IsBusy { get; set; }` — Whether the agent is busy performing other work.
- L54-65 _public property_ `public bool IsStopRequested { get; set; }` — Whether a stop of the agent is requested
- L70 _public field_ `public readonly AsyncEvent StatusChangedEvent = new()` — Status was updated
- L75-81 _public ctor_ `public StatusService(IOptionsMonitor<AgentSettings> settings, ILogger<StatusService> logger)` — Constructor
- L84-87 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L90-94 _public method_ `public Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L97-100 _public method_ `public async Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L105-109 _public method_ `public void Set(AgentStatusMessage status)` — Sets the current status
- L114 _public method_ `public void Set(bool healthy, int numLeases, string message)` — Sets the current status
- L119 _public method_ `public void SetDescription(string description)` — Sets a status description
- L125-135 _public method_ `public void Update(Func<AgentStatusMessage, AgentStatusMessage> updateFunc)` — Updates the status using a custom function
- L137-148 _private method_ `private async Task RunPipeServerAsync(CancellationToken cancellationToken)`
- L151-174 _private method_ `private async Task RunSinglePipeServerAsync(CancellationToken cancellationToken)` — attrs: `[SupportedOSPlatform("windows")]`
- L176-181 _private* method_ `AgentSettingsMessage GetSettingsMessage()`
- L184-231 _private method_ `private async Task RunPipeServerInternalAsync(CancellationToken cancellationToken)` — attrs: `[SupportedOSPlatform("windows")]`

### `Source/Programs/Horde/HordeAgent/Services/TelemetryService.cs` (HordeAgent)


#### class `HordeAgent.Services.DefaultSystemMetrics`  
`public sealed class DefaultSystemMetrics : ISystemMetrics`  
_public; L19-35_
- inherits: `ISystemMetrics`
- desc: Default implementation of ISystemMetrics
- L22 _public method_ `public CpuMetrics? GetCpu()` — (inheritdoc)
- L25 _public method_ `public CpuTimeMetrics? GetCpuTime()` — (inheritdoc)
- L28 _public method_ `public MemoryMetrics? GetMemory()` — (inheritdoc)
- L31 _public method_ `public DiskMetrics? GetWorkingDisk()` — (inheritdoc)
- L34 _public method_ `public DiskMetrics? GetSystemDisk()` — (inheritdoc)

#### class `HordeAgent.Services.WindowsSystemMetrics`  
`public sealed class WindowsSystemMetrics : ISystemMetrics`  
_public; L41-164_
- attrs: `[SupportedOSPlatform("windows")]`
- inherits: `ISystemMetrics`
- desc: Windows specific implementation for gathering system metrics
- L43 _private field_ `private readonly DirectoryReference _workingDir`
- L44 _private field_ `private readonly Stopwatch _driveInfoUpdateTimer = Stopwatch.StartNew()`
- L45 _private field_ `private DriveInfo? _workingDriveInfo`
- L46 _private field_ `private DriveInfo? _systemDriveInfo`
- L51-58 _public ctor_ `public WindowsSystemMetrics(DirectoryReference workingDir)` — Constructor
- L61-65 _public method_ `public CpuMetrics GetCpu()` — (inheritdoc)
- L68-88 _public method_ `public CpuTimeMetrics? GetCpuTime()` — (inheritdoc)
- L91-102 _public method_ `public MemoryMetrics GetMemory()` — (inheritdoc)
- L105-119 _public method_ `public DiskMetrics? GetWorkingDisk()` — (inheritdoc)
- L122-136 _public method_ `public DiskMetrics? GetSystemDisk()` — (inheritdoc)
- L141-149 _private* method_ `void RefreshDriveInfo()` — Restart the drive info poll timer if the time period has elapsed
- L156-163 _private method_ `private DriveInfo? GetDriveInfo(EpicGames.Horde.Agents.Metrics.DriveType type)` — Fetches root directory based off drive classification

#### class `HordeAgent.Services.LinuxSystemMetrics`  
`public sealed class LinuxSystemMetrics : ISystemMetrics, IDisposable`  
_public; L172-371_
- attrs: `[SupportedOSPlatform("linux")]`
- inherits: `ISystemMetrics, IDisposable`
- desc: Linux specific implementation for gathering system metrics
- L174 _private const_ `private const string ProcMeminfoPath = "/proc/meminfo"`
- L175 _private const_ `private const string ProcStatPath = "/proc/stat"`
- L176 _private const_ `private const int SC_CLK_TCK = 2`
- L177 _private const_ `private const int UserIndex = 1`
- L178 _private const_ `private const int NiceIndex = 2`
- L179 _private const_ `private const int SystemIndex = 3`
- L180 _private const_ `private const int IdleIndex = 4`
- L183 _private method_ `private static extern long sysconf(int name)` — attrs: `[DllImport("libc", SetLastError = true)]`
- L185 _private field_ `private static readonly Lazy<long> s_clockTicksPerSecond = new (() => { try { long result = sysconf(SC_CLK_TCK); if (result > 0) { return result; } } catch { } return 100; })`
- L204 _private field_ `private readonly DirectoryReference _workingDir`
- L209-212 _public ctor_ `public LinuxSystemMetrics(DirectoryReference workingDir)` — Constructor
- L215-238 _public method_ `public CpuMetrics? GetCpu()` — (inheritdoc)
- L241-251 _public method_ `public CpuTimeMetrics GetCpuTime()` — (inheritdoc)
- L254-292 _public method_ `public MemoryMetrics? GetMemory()` — (inheritdoc)
- L295 _public method_ `public DiskMetrics? GetWorkingDisk()` — (inheritdoc)
- L298 _public method_ `public DiskMetrics? GetSystemDisk()` — (inheritdoc)
- L305-325 _private method_ `private DiskMetrics? GetDiskMetrics(EpicGames.Horde.Agents.Metrics.DriveType drive)` — Fetches root directory based off drive classification
- L327-339 _private method_ `private static (long user, long system, long idle) ReadCpuTimes()`
- L365 _private method_ `private static extern int Statvfs(string path, out StatvfsStruct buf)` — attrs: `[DllImport("libc", SetLastError = true, EntryPoint = "statvfs")]`
- L368-370 _public method_ `public void Dispose()` — (inheritdoc)

#### struct `HordeAgent.Services.LinuxSystemMetrics.StatvfsStruct`  
`private struct StatvfsStruct`  
_private; L344-362_
- attrs: `[StructLayout(LayoutKind.Sequential)] [SuppressMessage("Style", "IDE1006:Naming Styles", Justification = "POSIX ABI")] [SuppressMessage("Style", "IDE0044:Add readonly modifier", Justification = "POSIX ABI")]`
- L346 _public field_ `public ulong f_bsize`
- L347 _public field_ `public ulong f_frsize`
- L348 _public field_ `public ulong f_blocks`
- L349 _public field_ `public ulong f_bfree`
- L350 _public field_ `public ulong f_bavail`
- L351 _public field_ `public ulong f_files`
- L352 _public field_ `public ulong f_ffree`
- L353 _public field_ `public ulong f_favail`
- L354 _public field_ `public ulong f_fsid`
- L355 _public field_ `public ulong f_flag`
- L356 _public field_ `public ulong f_namemax`
- L357 _private field_ `private ulong __f_spare0`
- L358 _private field_ `private ulong __f_spare1`
- L359 _private field_ `private ulong __f_spare2`
- L360 _private field_ `private ulong __f_spare3`
- L361 _private field_ `private ulong __f_spare4`

#### class `HordeAgent.Services.MacSystemMetrics`  
`public sealed class MacSystemMetrics : ISystemMetrics`  
_public; L377-460_
- attrs: `[SupportedOSPlatform("macos")]`
- inherits: `ISystemMetrics`
- desc: macOS specific implementation for gathering system metrics
- L379 _private field_ `private readonly DirectoryReference _workingDir`
- L380 _private field_ `private readonly Stopwatch _driveInfoUpdateTimer = Stopwatch.StartNew()`
- L381 _private field_ `private DriveInfo? _workingDriveInfo`
- L382 _private field_ `private DriveInfo? _systemDriveInfo`
- L387-392 _public ctor_ `public MacSystemMetrics(DirectoryReference workingDir)` — Constructor
- L395 _public method_ `public CpuMetrics? GetCpu()` — (inheritdoc)
- L398 _public method_ `public CpuTimeMetrics? GetCpuTime()` — (inheritdoc)
- L401 _public method_ `public MemoryMetrics? GetMemory()` — (inheritdoc)
- L404-418 _public method_ `public DiskMetrics? GetWorkingDisk()` — (inheritdoc)
- L421-435 _public method_ `public DiskMetrics? GetSystemDisk()` — (inheritdoc)
- L440-448 _private* method_ `void RefreshDriveInfo()` — Restart the drive info poll timer if the time period has elapsed
- L455-459 _private method_ `private DriveInfo GetDriveInfo(EpicGames.Horde.Agents.Metrics.DriveType type)` — Fetches the drive info for the given drive type

#### class `HordeAgent.Services.TelemetryService`  
`class TelemetryService : IHostedService, IDisposable`  
_internal*; L465-682_
- inherits: `IHostedService, IDisposable`
- desc: Send telemetry events back to server at regular intervals
- L467 _private field_ `private readonly TimeSpan _heartbeatInterval = TimeSpan.FromSeconds(60)`
- L468 _private field_ `private readonly TimeSpan _heartbeatMaxAllowedDiff = TimeSpan.FromSeconds(5)`
- L470 _private field_ `private readonly ILogger<TelemetryService> _logger`
- L472 _private field_ `private CancellationTokenSource? _eventLoopHeartbeatCts`
- L473 _private field_ `private Task? _eventLoopTask`
- L474 _internal property_ `internal Func<DateTime> GetUtcNow { get; set; }`
- L479-482 _public ctor_ `public TelemetryService(ILogger<TelemetryService> logger)` — Constructor
- L485-488 _public method_ `public void Dispose()` — (inheritdoc)
- L491-496 _public method_ `public Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L498-516 _public method_ `public async Task StopAsync(CancellationToken cancellationToken)`
- L522-532 _private method_ `private async Task EventLoopHeartbeatAsync(CancellationToken cancellationToken)` — Continuously run the heartbeat for the event loop
- L541-556 _public method_ `public async Task<(bool onTime, TimeSpan diff)> IsEventLoopOnTimeAsync(TimeSpan wait, TimeSpan maxDiff, CancellationToken cancellationToken)` — Checks if the async event loop is on time
- L563-611 _public method_ `public static async Task<List<string>> GetProblematicFilterDriversAsync(ILogger logger, CancellationToken cancellationToken)` — Get list of any filter drivers known to be problematic for builds
- L618-625 _public method_ `public static async Task LogProblematicFilterDriversAsync(ILogger logger, CancellationToken cancellationToken)` — Log any filter drivers known to be problematic for builds
- L627-648 _internal method_ `internal static async Task<string> ReadFltMcOutputAsync(CancellationToken cancellationToken)`
- L650-681 _internal method_ `internal static List<string>? ParseFltMcOutput(string output)`

### `Source/Programs/Horde/HordeAgent/Services/WindowsCapabilities.cs` (HordeAgent)


#### class `HordeAgent.Services.WindowsCapabilities`  
`public class WindowsCapabilities(IOptionsMonitor<AgentSettings> settings, ILogger logger, Tracer tracer) : ISystemCapabilities`  
_public; L19-261_
- attrs: `[SupportedOSPlatform("windows")]`
- desc: Get Windows-specific capabilities
- L22-65 _public method_ `public Task<RpcAgentCapabilities> GetCapabilitiesAsync(DirectoryReference? workingDir)` — (inheritdoc)
- L67 _private method_ `private static void SetProp(RpcAgentCapabilities caps, string key, string value)`
- L68 _private method_ `private static void SetProp(RpcAgentCapabilities caps, string key, bool value)`
- L74-89 _public method_ `public static (ulong total, ulong available) GetPhysicalMemory()` — Gets details of current system's physical memory
- L105-145 _public method_ `public static (float idle, float system, float user) GetCpuMetrics()` — Gets details of the current system's CPU
- L147-157 _private method_ `private static int GetNumLogicalCores()`
- L159-175 _private method_ `private static string GetCpuName()`
- L177-218 _private method_ `private static void SetGpuInfo(RpcAgentCapabilities capabilities)`
- L223 _private* method_ `static extern ushort GetActiveProcessorGroupCount()` — attrs: `[DllImport("kernel32.dll")]`
- L226 _private* method_ `static extern uint GetActiveProcessorCount(ushort GroupNumber)` — attrs: `[DllImport("kernel32.dll")]`
- L230 _private* method_ `static extern bool GlobalMemoryStatusEx([In, Out] MEMORYSTATUSEX lpBuffer)` — attrs: `[DllImport("kernel32.dll", SetLastError = true)] [return: MarshalAs(UnmanagedType.Bool)]`
- L248 _internal method_ `internal static extern bool GetSystemTimes(out FILETIME idle, out FILETIME system, out FILETIME user)` — attrs: `[DllImport("kernel32.dll", SetLastError = true)] [return: MarshalAs(UnmanagedType.Bool)]`

#### class `HordeAgent.Services.WindowsCapabilities.CpuMetrics`  
`private sealed class CpuMetrics`  
_private; L91-99_
- L93 _internal field_ `internal static FILETIME Idle, System, User`
- L93 _internal field_ `internal static FILETIME System`
- L93 _internal field_ `internal static FILETIME User`
- L95-98 _internal method_ `internal static bool IsFirstRun()`

#### class `HordeAgent.Services.WindowsCapabilities.MEMORYSTATUSEX`  
`private class MEMORYSTATUSEX`  
_private; L233-244_
- attrs: `[StructLayout(LayoutKind.Sequential)]`
- L235 _public field_ `public uint dwLength = (uint)Marshal.SizeOf(typeof(MEMORYSTATUSEX))`
- L236 _public field_ `public uint dwMemoryLoad`
- L237 _public field_ `public ulong ullTotalPhys`
- L238 _public field_ `public ulong ullAvailPhys`
- L239 _public field_ `public ulong ullTotalPageFile`
- L240 _public field_ `public ulong ullAvailPageFile`
- L241 _public field_ `public ulong ullTotalVirtual`
- L242 _public field_ `public ulong ullAvailVirtual`
- L243 _public field_ `public ulong ullAvailExtendedVirtual`

#### struct `HordeAgent.Services.WindowsCapabilities.FILETIME`  
`internal struct FILETIME`  
_internal; L251-257_
- attrs: `[StructLayout(LayoutKind.Sequential)]`
- L253 _public field_ `public uint dwLowDateTime`
- L254 _public field_ `public uint dwHighDateTime`
- L255 _public method_ `public ulong ToUInt64()`
- L256 _public property_ `public bool IsZero => ...`

### `Source/Programs/Horde/HordeAgent/Services/WorkerService.cs` (HordeAgent)


#### interface `HordeAgent.Services.IWorkerService`  
`internal interface IWorkerService`  
_internal; L16-37_
- desc: Interface for WorkerService. Mainly for extracting methods which simplifies testing and dependencies
- L21 _public method_ `public List<RpcLease> GetActiveLeases()` — Gets all the current leases held by the agent
- L26 _public method_ `public void TerminateSessionAfterLease()` — Stop the session loop after at least one lease has finished executing
- L31 _public property_ `public bool IsConnected { get; }` — Whether agent is connected to Horde server
- L36 _public property_ `public IReadOnlyList<string> PoolIds { get; }` — List of pool IDs this agent (session) currently is a member of

#### class `HordeAgent.Services.WorkerService`  
`class WorkerService : BackgroundService, IWorkerService`  
_internal*; L42-202_
- inherits: `BackgroundService, IWorkerService`
- desc: Implements the message handling loop for an agent. Runs asynchronously until disposed.
- L44 _private* field_ `readonly ILogger _logger`
- L45 _private* field_ `readonly ISessionFactory _sessionFactory`
- L46 _private* field_ `readonly StatusService _statusService`
- L47 _private* field_ `readonly IServiceProvider _serviceProvider`
- L48 _private* field_ `LeaseManager? _currentLeaseManager`
- L51 _public property_ `public IReadOnlyList<string> PoolIds => ...` — (inheritdoc)
- L53 _private* field_ `static readonly TimeSpan[] s_sessionBackOffTime = { TimeSpan.FromSeconds(5), TimeSpan.FromSeconds(10), TimeSpan.FromSeconds(30), TimeSpan.FromMinutes(1) }`
- L64-70 _public ctor_ `public WorkerService(ISessionFactory sessionFactory, StatusService statusService, IServiceProvider serviceProvider, ILogger<WorkerService> logger)` — Constructor. Registers with the server and starts accepting connections.
- L73-76 _public method_ `public List<RpcLease> GetActiveLeases()` — (inheritdoc)
- L79-85 _public method_ `public void TerminateSessionAfterLease()` — (inheritdoc)
- L88 _public property_ `public bool IsConnected { get; set; }` — (inheritdoc)
- L94-107 _protected method_ `protected override async Task ExecuteAsync(CancellationToken stoppingToken)` — Executes the ServerTaskAsync method and swallows the exception for the task being cancelled. This allows waiting for it to terminate.
- L113-201 _internal method_ `internal async Task ExecuteInnerAsync(CancellationToken stoppingToken)` — Background task to cycle access tokens and update the state of the agent with the server.

### `Source/Programs/Horde/HordeAgent/Utility/CertificateHelper.cs` (HordeAgent)


#### class `HordeAgent.Utility.CertificateHelper`  
`static class CertificateHelper`  
_internal*; L14-107_
- desc: Helper functions for dealing with certificates
- L26-106 _public method_ `public static bool CertificateValidationCallBack(ILogger logger, object sender, X509Certificate? certificate, X509Chain? chain, SslPolicyErrors sslPolicyErrors, ServerProfile serverProfile)` — Provides additional diagnostic information for SSL certificate validation

### `Source/Programs/Horde/HordeAgent/Utility/ExceptionUtils.cs` (HordeAgent)


#### class `HordeAgent.Utility.ExceptionUtils`  
`static class ExceptionUtils`  
_internal*; L10-32_
- desc: Utility methods for exceptions
- L17-31 _public method_ `public static bool IsCancellationException(this Exception ex)` — Determine if the given exception was triggered due to a cancellation event

### `Source/Programs/Horde/HordeAgent/Utility/JsonConfig.cs` (HordeAgent)


#### class `HordeAgent.Utility.JsonConfig`  
`static class JsonConfig`  
_internal*; L15-85_
- desc: Utility class for making localized changes to JSON config files
- L20-25 _public method_ `public static async Task<JsonObject> ReadAsync(FileReference file)` — Read a JSON config file from disk
- L30-38 _public method_ `public static async Task WriteAsync(FileReference file, JsonObject root)` — Writes the config file to disk
- L43-61 _public method_ `public static T FindOrAddNode<T>(JsonObject obj, string name, Func<T> factory) where T : JsonNode` — Read a node by name
- L66-84 _public method_ `public static JsonObject FindOrAddElementByKey(JsonArray array, string key, string name)` — Find or adds an array element with a particular key

### `Source/Programs/Horde/HordeAgent/Utility/NativeWindowsService.cs` (HordeAgent)


#### class `HordeAgent.Utility.NativeWindowsServiceUtils`  
`public static class NativeWindowsServiceUtils`  
_public; L12-177_
- desc: Utility class for Windows services using Win32 API via P/Invoke
- L17 _private const_ `private const uint SC_MANAGER_CONNECT = 0x0001`
- L18 _private const_ `private const uint SC_MANAGER_ENUMERATE_SERVICE = 0x0004`
- L19 _private const_ `private const uint SERVICE_WIN32 = 0x00000030`
- L20 _private const_ `private const uint SERVICE_STATE_ALL = 0x00000003`
- L21 _private const_ `private const int ERROR_MORE_DATA = 234`
- L22 _private const_ `private const int SC_ENUM_PROCESS_INFO = 0`
- L47 _private method_ `private static extern IntPtr OpenSCManager( string? machineName, string? databaseName, uint dwDesiredAccess)` — attrs: `[DllImport("advapi32.dll", SetLastError = true, CharSet = CharSet.Unicode)]`
- L54 _private method_ `private static extern bool EnumServicesStatusEx( IntPtr hSCManager, int InfoLevel, uint dwServiceType, uint dwServiceState, IntPtr lpServices, uint cbBufSize, out uint pcbBytesNeeded, out uint lpServicesReturned, IntPtr lpResumeHandle, string? pszGroupName)` — attrs: `[DllImport("advapi32.dll", SetLastError = true, CharSet = CharSet.Auto)] [return: MarshalAs(UnmanagedType.Bool)]`
- L69 _private method_ `private static extern bool CloseServiceHandle(IntPtr hSCObject)` — attrs: `[DllImport("advapi32.dll", SetLastError = true)] [return: MarshalAs(UnmanagedType.Bool)]`
- L80-176 _public method_ `public static ServiceController? GetServiceForProcess(int processId)` — attrs: `[SupportedOSPlatform("windows")]` — Try to find the service controller for the given process ID using Win32 API.

#### struct `HordeAgent.Utility.NativeWindowsServiceUtils.SERVICE_STATUS_PROCESS`  
`private struct SERVICE_STATUS_PROCESS`  
_private; L25-36_
- attrs: `[StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]`
- L27 _public field_ `public uint dwServiceType`
- L28 _public field_ `public uint dwCurrentState`
- L29 _public field_ `public uint dwControlsAccepted`
- L30 _public field_ `public uint dwWin32ExitCode`
- L31 _public field_ `public uint dwServiceSpecificExitCode`
- L32 _public field_ `public uint dwCheckPoint`
- L33 _public field_ `public uint dwWaitHint`
- L34 _public field_ `public uint dwProcessId`
- L35 _public field_ `public uint dwServiceFlags`

#### struct `HordeAgent.Utility.NativeWindowsServiceUtils.ENUM_SERVICE_STATUS_PROCESS`  
`private struct ENUM_SERVICE_STATUS_PROCESS`  
_private; L39-44_
- attrs: `[StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]`
- L41 _public field_ `public string lpServiceName`
- L42 _public field_ `public string lpDisplayName`
- L43 _public field_ `public SERVICE_STATUS_PROCESS ServiceStatusProcess`

### `Source/Programs/Horde/HordeAgent/Utility/NetworkShare.cs` (HordeAgent)


#### class `HordeAgent.Utility.NetworkShare`  
`static class NetworkShare`  
_internal*; L12-127_
- desc: Utility functions for mapping network shares
- L28 _private* const_ `const uint RESOURCETYPE_DISK = 1`
- L29 _private* const_ `const uint CONNECT_TEMPORARY = 4`
- L31 _private* const_ `const int ERROR_ALREADY_ASSIGNED = 85`
- L32 _private* const_ `const int ERROR_MORE_DATA = 234`
- L35 _private method_ `private static extern int WNetAddConnection2W(ref NETRESOURCE lpNetResource, string? lpPassword, string? lpUsername, uint dwFlags)` — attrs: `[DllImport("Mpr.dll", CharSet = CharSet.Unicode)]`
- L38 _private method_ `private static extern int WNetCancelConnectionW(string lpName, [MarshalAs(UnmanagedType.Bool)] bool fForce)` — attrs: `[DllImport("Mpr.dll", CharSet = CharSet.Unicode)]`
- L41 _private method_ `private static extern int WNetGetConnectionW(string lpLocalName, IntPtr lpRemoteName, ref int lpnLength)` — attrs: `[DllImport("Mpr.dll", CharSet = CharSet.Unicode)]`
- L48-75 _public method_ `public static void Mount(string mountPoint, string remotePath)` — Mounts a network share at the given location
- L81-88 _public method_ `public static void Unmount(string mountPoint)` — Unmounts a network share
- L96-126 _public method_ `public static bool TryGetRemotePath(string mountPoint, [NotNullWhen(true)] out string? outRemotePath)` — Gets the currently mounted path for a network share

#### struct `HordeAgent.Utility.NetworkShare.NETRESOURCE`  
`private struct NETRESOURCE`  
_private; L16-26_
- attrs: `[StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)] [SuppressMessage("Style", "IDE1006:Naming Styles", Justification = "<Pending>")]`
- L18 _public field_ `public uint dwScope`
- L19 _public field_ `public uint dwType`
- L20 _public field_ `public uint dwDisplayType`
- L21 _public field_ `public uint dwUsage`
- L22 _public field_ `public string? lpLocalName`
- L23 _public field_ `public string? lpRemoteName`
- L24 _public field_ `public string? lpComment`
- L25 _public field_ `public string? lpProvider`

### `Source/Programs/Horde/HordeAgent/Utility/OpenTelemetry.cs` (HordeAgent)


#### class `HordeAgent.Utility.OpenTelemetryDatadogLogEnricher`  
`public class OpenTelemetryDatadogLogEnricher : ILogEventEnricher`  
_public; L20-36_
- inherits: `ILogEventEnricher`
- desc: Serilog event enricher attaching trace and span ID for Datadog using current System.Diagnostics.Activity
- L23-35 _public method_ `public void Enrich(Serilog.Events.LogEvent logEvent, ILogEventPropertyFactory propertyFactory)` — (inheritdoc)

#### class `HordeAgent.Utility.OpenTelemetryHelper`  
`public static class OpenTelemetryHelper`  
_public; L41-203_
- desc: Helper for configuring OpenTelemetry
- L43 _private field_ `private static ResourceBuilder? s_resourceBuilder`
- L44 _private field_ `private static readonly HttpRequestOptionsKey<string> s_urlTemplateKey = new("url.template")`
- L50 _public const_ `public const string DatadogResourceAttribute = "resource.name"` — Name of resource name attribute in Datadog Some traces use this for prettier display inside their UI
- L55 _public const_ `public const string HordeName = "Horde"` — Name of default Horde tracer (aka activity source)
- L61 _public property_ `public static string[] SourceNames => ...` — List of all source names configured in this class. They are needed at startup when initializing OpenTelemetry
- L67 _public field_ `public static readonly Tracer Horde = TracerProvider.Default.GetTracer(HordeName)` — Default tracer used in Horde Prefer dependency-injected tracer over this static member.
- L74-88 _public method_ `public static void Configure(IServiceCollection services, OpenTelemetrySettings settings)` — Configure OpenTelemetry in Horde and ASP.NET
- L90-139 _private method_ `private static void ConfigureTracing(TracerProviderBuilder builder, OpenTelemetrySettings settings)`
- L141-159 _private method_ `private static void ConfigureMetrics(MeterProviderBuilder builder, OpenTelemetrySettings settings)`
- L166-185 _public method_ `public static void ConfigureLogging(ILoggingBuilder builder, OpenTelemetrySettings settings)` — Configure .NET logging with OpenTelemetry
- L187-202 _private method_ `private static ResourceBuilder GetResourceBuilder(OpenTelemetrySettings settings)`

#### class `HordeAgent.Utility.OpenTelemetryMeters`  
`public static class OpenTelemetryMeters`  
_public; L208-225_
- desc: Static initialization of all available OpenTelemetry meters
- L213 _public const_ `public const string HordeName = "Horde"` — Name of default Horde meter
- L219 _public property_ `public static string[] MeterNames => ...` — List of all source names configured in this class. They are needed at startup when initializing OpenTelemetry
- L224 _public field_ `public static readonly Meter Horde = new(HordeName)` — Default meter used in Horde

### `Source/Programs/Horde/HordeAgent/Utility/RuntimeWatchdog.cs` (HordeAgent)


#### class `HordeAgent.Utility.RuntimeWatchdog`  
`public sealed class RuntimeWatchdog : IHostedService, IDisposable`  
_public; L14-140_
- inherits: `IHostedService, IDisposable`
- desc: Monitor execution of the process and .NET runtime Horde agent runs in an environment where resources are often maximally utilized (CPU, memory, disk, network etc) This can lead to unexpected behaviors with delays or timeouts. This class self-monitors and ensures a heartbeat thread and task is "on time".
- L16 _internal property_ `internal TimeSpan? ArtificialThreadDelay { get; set; }`
- L17 _internal property_ `internal TimeSpan? ArtificialTaskDelay { get; set; }`
- L19 _private field_ `private long _lastTaskHeartbeatTicks`
- L20 _private field_ `private readonly Thread _heartbeatThread`
- L21 _private field_ `private Task? _heartbeatTask`
- L22 _private field_ `private volatile bool _isRunning`
- L23 _private field_ `private readonly TimeSpan _heartbeatThreadInterval = TimeSpan.FromSeconds(10)`
- L24 _private field_ `private readonly TimeSpan _heartbeatTaskInterval = TimeSpan.FromSeconds(5)`
- L25 _private field_ `private readonly TimeSpan _maxTaskStallDuration`
- L26 _private field_ `private readonly TimeSpan _maxThreadStallDuration`
- L27 _private field_ `private readonly TimeSpan _maxGcPauseDelta = TimeSpan.FromSeconds(3)`
- L28 _private field_ `private readonly ILogger<RuntimeWatchdog> _logger`
- L29 _private field_ `private readonly CancellationTokenSource _cts = new()`
- L34-41 _public ctor_ `public RuntimeWatchdog(ILogger<RuntimeWatchdog> logger)` — Constructor
- L44-47 _public method_ `public void Dispose()` — (inheritdoc)
- L50-60 _public method_ `public Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L63-74 _public method_ `public async Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L76-117 _private method_ `private void HeartbeatThreadLoop()`
- L119-139 _private method_ `private async Task HeartbeatTaskLoopAsync(CancellationToken cancellationToken)`

### `Source/Programs/Horde/HordeAgent/Utility/Shutdown.cs` (HordeAgent)


#### class `HordeAgent.Utility.Shutdown`  
`static class Shutdown`  
_internal*; L11-208_
- L13 _public const_ `public const uint TOKEN_QUERY = 0x0008`
- L14 _public const_ `public const uint TOKEN_ADJUST_PRIVILEGES = 0x0020`
- L18 _private* method_ `static extern bool OpenProcessToken(IntPtr processHandle, uint desiredAccess, out IntPtr tokenHandle)` — attrs: `[DllImport("advapi32.dll", SetLastError = true)] [return: MarshalAs(UnmanagedType.Bool)]`
- L29 _private* method_ `static extern bool LookupPrivilegeValue(string? lpSystemName, string lpName, ref LUID lpLuid)` — attrs: `[DllImport("advapi32.dll")]`
- L51 _private* method_ `static extern bool AdjustTokenPrivileges(IntPtr TokenHandle, [MarshalAs(UnmanagedType.Bool)] bool DisableAllPrivileges, ref TOKEN_PRIVILEGES NewState, uint Zero, IntPtr Null1, IntPtr Null2)` — attrs: `[DllImport("advapi32.dll", SetLastError = true)] [SuppressMessage("Style", "IDE1006:Naming Styles", Justification = "Native struct")] [return: MarshalAs(UnmanagedType.Bool)]`
- L58 _private* const_ `const uint SHTDN_REASON_MAJOR_APPLICATION = 0x00040000`
- L59 _private* const_ `const uint SHTDN_REASON_MINOR_MAINTENANCE = 0x00000001`
- L62 _private* method_ `static extern bool InitiateSystemShutdownEx(string? lpMachineName, string? lpMessage, uint dwTimeout, bool bForceAppsClosed, bool bRebootAfterShutdown, uint dwReason)` — attrs: `[DllImport("advapi32.dll", CharSet = CharSet.Auto, SetLastError = true)]`
- L64 _private* const_ `const string SE_SHUTDOWN_NAME = "SeShutdownPrivilege"`
- L66 _private* const_ `const int SE_PRIVILEGE_ENABLED = 0x00000002`
- L74-178 _public method_ `public static bool InitiateShutdown(bool restartAfterShutdown, ILogger logger)` — Initiate a shutdown operation
- L186-207 _public method_ `public static async Task ExecuteAsync(bool restart, ILogger logger, CancellationToken cancellationToken)` — Attempt to initiate a shutdown and return if it failed

#### struct `HordeAgent.Utility.Shutdown.LUID`  
`public struct LUID`  
_public; L22-26_
- attrs: `[StructLayout(LayoutKind.Sequential)] [SuppressMessage("Style", "IDE1006:Naming Styles", Justification = "Native struct")]`
- L24 _public field_ `public uint LowPart`
- L25 _public field_ `public int HighPart`

#### struct `HordeAgent.Utility.Shutdown.LUID_AND_ATTRIBUTES`  
`public struct LUID_AND_ATTRIBUTES`  
_public; L33-37_
- attrs: `[StructLayout(LayoutKind.Sequential, Pack = 4)] [SuppressMessage("Style", "IDE1006:Naming Styles", Justification = "Native struct")]`
- L35 _public field_ `public LUID Luid`
- L36 _public field_ `public uint Attributes`

#### struct `HordeAgent.Utility.Shutdown.TOKEN_PRIVILEGES`  
`struct TOKEN_PRIVILEGES`  
_private*; L40-45_
- attrs: `[SuppressMessage("Style", "IDE1006:Naming Styles", Justification = "Native struct")]`
- L42 _public field_ `public int PrivilegeCount`
- L44 _public field_ `public LUID_AND_ATTRIBUTES[] Privileges` — attrs: `[MarshalAs(UnmanagedType.ByValArray, SizeConst = 1)]`

### `Source/Programs/Horde/HordeAgent/Utility/WindowsProcessMemoryTracker.cs` (HordeAgent)


#### record `HordeAgent.Utility.ProcessMemoryInfo`  
`public record ProcessMemoryInfo( int ProcessId, string ProcessName, string CommandLine, long PeakPrivateBytes, long PeakWorkingSetBytes)`  
_public; L23-23_
- attrs: `[SupportedOSPlatform("windows")]`
- desc: Memory information for a process, tracking peak values observed across all samples

#### class `HordeAgent.Utility.WindowsProcessMemoryTracker`  
`public sealed class WindowsProcessMemoryTracker : IDisposable`  
_public; L35-300_
- attrs: `[SupportedOSPlatform("windows")]`
- inherits: `IDisposable`
- desc: Tracks memory usage for all processes in a Windows Job Object. Samples at configurable intervals and maintains peak memory values per process.
- L40 _public const_ `public const int MaxCommandLineLength = 500` — Maximum length for stored command line strings
- L47 _private* const_ `const int JobObjectBasicProcessIdList = 3`
- L58 _private* method_ `static extern bool QueryInformationJobObject( SafeFileHandle hJob, int JobObjectInformationClass, IntPtr lpJobObjectInfo, int cbJobObjectInfoLength, out int lpReturnLength)` — attrs: `[DllImport("kernel32.dll", SetLastError = true)]`
- L70 _private* field_ `readonly ManagedProcessGroup _processGroup`
- L71 _private* field_ `readonly TimeSpan _sampleInterval`
- L72 _private* field_ `readonly ILogger _logger`
- L74 _private* field_ `readonly ConcurrentDictionary<int, ProcessMemoryInfo> _peakByPid = ...`
- L74 _private* field_ `readonly ConcurrentDictionary< _peakByPid = new()`
- L75 _private* field_ `Task? _samplingTask`
- L76 _private* field_ `CancellationTokenSource? _cts`
- L84-92 _public ctor_ `public WindowsProcessMemoryTracker( ManagedProcessGroup processGroup, TimeSpan sampleInterval, ILogger logger)` — Creates a new memory tracker for the specified process group
- L97-106 _public method_ `public void Start()` — Starts the background memory sampling task
- L113-119 _public method_ `public IReadOnlyList<ProcessMemoryInfo> GetTopMemoryProcesses(int count = 5)` — Returns the top N processes by peak private memory
- L122-145 _public method_ `public void Dispose()` — (inheritdoc)
- L147-157 _private* method_ `async Task SamplingLoopAsync(CancellationToken cancellationToken)`
- L159-173 _private* method_ `void SampleProcessMemory()`
- L175-244 _private* method_ `int[] GetJobProcessIds()`
- L246-284 _private* method_ `void SampleProcess(int pid)`
- L286-299 _private* method_ `static string TruncateCommandLine(string commandLine)`

#### struct `HordeAgent.Utility.WindowsProcessMemoryTracker.JOBOBJECT_BASIC_PROCESS_ID_LIST`  
`struct JOBOBJECT_BASIC_PROCESS_ID_LIST`  
_private*; L50-55_
- attrs: `[StructLayout(LayoutKind.Sequential)]`
- L52 _public field_ `public uint NumberOfAssignedProcesses`
- L53 _public field_ `public uint NumberOfProcessIdsInList`

### `Source/Programs/Horde/HordeAgent/Utility/WindowsServiceManager.cs` (HordeAgent)


#### class `HordeAgent.Utility.Native`  
`static partial class Native`  
_internal*; L14-151_
- desc: Native methods for manipulating services on Windows
- L36 _public const_ `public const uint SC_MANAGER_ALL_ACCESS = 0xF003F`
- L39 _public method_ `public static extern ServiceHandle OpenSCManager(string? machineName, string? databaseName, uint dwAccess)` — attrs: `[DllImport("advapi32.dll", EntryPoint = "OpenSCManagerW", ExactSpelling = true, CharSet = CharSet.Unicode, SetLastError = true)]`
- L41 _public const_ `public const uint SERVICE_ALL_ACCESS = 0xf01ff`
- L43 _public const_ `public const uint SERVICE_WIN32_OWN_PROCESS = 0x00000010`
- L45 _public const_ `public const uint SERVICE_AUTO_START = 0x00000002`
- L46 _public const_ `public const uint SERVICE_DEMAND_START = 0x00000003`
- L48 _public const_ `public const uint SERVICE_ERROR_NORMAL = 0x00000001`
- L51 _public method_ `public static extern ServiceHandle CreateService(ServiceHandle hSCManager, string lpServiceName, string lpDisplayName, uint dwDesiredAccess, uint dwServiceType, uint dwStartType, uint dwErrorControl, string lpBinaryPathName, string? lpLoadOrderGroup, string? lpdwTagId, string? lpDependencies, string? lpServiceStartName, string? lpPassword)` — attrs: `[DllImport("advapi32.dll", SetLastError = true, CharSet = CharSet.Auto)]`
- L54 _public method_ `public static extern ServiceHandle OpenService(ServiceHandle hSCManager, string lpServiceName, uint dwDesiredAccess)` — attrs: `[DllImport("advapi32.dll", SetLastError = true, CharSet = CharSet.Auto)]`
- L58 _public method_ `public static extern bool StartService(ServiceHandle hService, int dwNumServiceArgs, string[]? lpServiceArgVectors)` — attrs: `[DllImport("advapi32", SetLastError = true)] [return: MarshalAs(UnmanagedType.Bool)]`
- L60 _public const_ `public const int ERROR_ACCESS_DENIED = 5`
- L61 _public const_ `public const int ERROR_SERVICE_DOES_NOT_EXIST = 1060`
- L62 _public const_ `public const int ERROR_SERVICE_NOT_ACTIVE = 1062`
- L66 _public method_ `public static extern bool CloseServiceHandle(IntPtr hSCObject)` — attrs: `[DllImport("advapi32.dll", SetLastError = true)] [return: MarshalAs(UnmanagedType.Bool)]`
- L70 _public method_ `public static extern bool DeleteService(ServiceHandle hService)` — attrs: `[DllImport("advapi32.dll", SetLastError = true)] [return: MarshalAs(UnmanagedType.Bool)]`
- L72 _public const_ `public const int SC_STATUS_PROCESS_INFO = 0`
- L90 _public method_ `public static extern bool QueryServiceStatusEx(ServiceHandle hService, int infoLevel, ref SERVICE_STATUS_PROCESS pBuffer, int cbBufSize, out int pcbBytesNeeded)` — attrs: `[DllImport("advapi32.dll", SetLastError = true)] [return: MarshalAs(UnmanagedType.Bool)]`
- L104 _public const_ `public const int SERVICE_CONTROL_STOP = 1`
- L108 _public method_ `public static extern bool ControlService(ServiceHandle hService, int dwControl, ref SERVICE_STATUS lpServiceStatus)` — attrs: `[DllImport("advapi32.dll", SetLastError = true)] [return: MarshalAs(UnmanagedType.Bool)]`
- L110 _public const_ `public const int SERVICE_CONFIG_DESCRIPTION = 1`
- L120 _public const_ `public const int SERVICE_CONFIG_FAILURE_ACTIONS = 0x2`
- L148 _public method_ `public static extern bool ChangeServiceConfig2(ServiceHandle hService, int dwInfoLevel, IntPtr lpInfo)` — attrs: `[DllImport("advapi32.dll", SetLastError = true, CharSet = CharSet.Auto)] [return: MarshalAs(UnmanagedType.Bool)]`

#### class `HordeAgent.Utility.Native.ServiceHandle`  
`public class ServiceHandle : SafeHandleZeroOrMinusOneIsInvalid`  
_public; L17-34_
- inherits: `SafeHandleZeroOrMinusOneIsInvalid`
- L19-22 _public ctor_ `public ServiceHandle() : base(true)`
- L24-28 _public ctor_ `public ServiceHandle(IntPtr handle) : base(true)`
- L30-33 _protected method_ `protected override bool ReleaseHandle()`

#### struct `HordeAgent.Utility.Native.SERVICE_STATUS_PROCESS`  
`public struct SERVICE_STATUS_PROCESS`  
_public; L75-86_
- attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Style", "IDE1006:Naming Styles", Justification = "<Pending>")]`
- L77 _public field_ `public uint dwServiceType`
- L78 _public field_ `public uint dwCurrentState`
- L79 _public field_ `public uint dwControlsAccepted`
- L80 _public field_ `public uint dwWin32ExitCode`
- L81 _public field_ `public uint dwServiceSpecificExitCode`
- L82 _public field_ `public uint dwCheckPoint`
- L83 _public field_ `public uint dwWaitHint`
- L84 _public field_ `public uint dwProcessId`
- L85 _public field_ `public uint dwServiceFlags`

#### struct `HordeAgent.Utility.Native.SERVICE_STATUS`  
`public struct SERVICE_STATUS`  
_public; L93-102_
- attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Style", "IDE1006:Naming Styles", Justification = "<Pending>")]`
- L95 _public field_ `public uint dwServiceType`
- L96 _public field_ `public uint dwCurrentState`
- L97 _public field_ `public uint dwControlsAccepted`
- L98 _public field_ `public uint dwWin32ExitCode`
- L99 _public field_ `public uint dwServiceSpecificExitCode`
- L100 _public field_ `public uint dwCheckPoint`
- L101 _public field_ `public uint dwWaitHint`

#### struct `HordeAgent.Utility.Native.SERVICE_DESCRIPTION`  
`public struct SERVICE_DESCRIPTION`  
_public; L114-118_
- attrs: `[StructLayout(LayoutKind.Sequential)] [SuppressMessage("Style", "IDE1006:Naming Styles", Justification = "Native struct")]`
- L117 _public field_ `public string lpDescription` — attrs: `[MarshalAs(UnmanagedType.LPWStr)]`

#### struct `HordeAgent.Utility.Native.SERVICE_FAILURE_ACTIONS`  
`public struct SERVICE_FAILURE_ACTIONS`  
_public; L124-136_
- attrs: `[StructLayout(LayoutKind.Sequential)] [SuppressMessage("Style", "IDE1006:Naming Styles", Justification = "Native struct")]`
- L126 _public field_ `public int dwResetPeriod`
- L129 _public field_ `public string? lpRebootMsg` — attrs: `[MarshalAs(UnmanagedType.LPWStr)]`
- L132 _public field_ `public string? lpCommand` — attrs: `[MarshalAs(UnmanagedType.LPWStr)]`
- L134 _public field_ `public int cActions`
- L135 _public field_ `public IntPtr lpsaActions`

#### struct `HordeAgent.Utility.Native.SERVICE_ACTION`  
`public struct SERVICE_ACTION`  
_public; L140-144_
- attrs: `[StructLayout(LayoutKind.Sequential)] [SuppressMessage("Style", "IDE1006:Naming Styles", Justification = "Native struct")]`
- L142 _public field_ `public WindowsServiceRecoverAction type`
- L143 _public field_ `public uint dwDelay`

#### enum `HordeAgent.Utility.WindowsServiceRecoverAction`  
`enum WindowsServiceRecoverAction : int`  
_internal*; L153-174_
- inherits: `int`
- L158 _public* enumerator_ `None = 0` — No Recover Action
- L163 _public* enumerator_ `Restart = 1` — Restart the service.
- L168 _public* enumerator_ `Reboot = 2` — Reboot the host.
- L173 _public* enumerator_ `RunCommand = 3` — Run a command

#### enum `HordeAgent.Utility.WindowsServiceStatus`  
`enum WindowsServiceStatus : uint`  
_internal*; L176-212_
- inherits: `uint`
- L181 _public* enumerator_ `Stopped = 1` — The service has stopped.
- L186 _public* enumerator_ `Starting = 2` — The service is starting.
- L191 _public* enumerator_ `Stopping = 3` — The service is stopping.
- L196 _public* enumerator_ `Running = 4` — The service is running
- L201 _public* enumerator_ `Continuing = 5` — The service is about to continue.
- L206 _public* enumerator_ `Pausing = 6` — The service is pausing
- L211 _public* enumerator_ `Paused = 7` — The service is paused.

#### class `HordeAgent.Utility.WindowsService`  
`class WindowsService : IDisposable`  
_internal*; L217-400_
- inherits: `IDisposable`
- desc: Wrapper around
- L222 _private field_ `private readonly Native.ServiceHandle _handle` — Handle to the service
- L228-231 _public ctor_ `public WindowsService(Native.ServiceHandle handle)` — Constructor
- L236 _public property_ `public bool IsValid => ...` — Determines if the service is valid
- L242-250 _public method_ `public WindowsServiceStatus GetStatus()` — Gets the current service status
- L257-272 _public method_ `public WindowsServiceStatus WaitForStatusChange(WindowsServiceStatus transitionStatus, TimeSpan maxWaitTime)` — Waits for the status to change
- L278-294 _public method_ `public void SetDescription(string description)` — Sets the service description
- L301-353 _public method_ `public void ChangeServiceFailureActions(params WindowsServiceRecoverAction[] recoveryActions)` — Set the recovery actions for the windows service
- L358-364 _public method_ `public void Start()` — Starts the service
- L369-380 _public method_ `public void Stop()` — Stops the service
- L385-391 _public method_ `public void Delete()` — Deletes the service
- L396-399 _public method_ `public void Dispose()` — Dispose of the service handle

#### class `HordeAgent.Utility.WindowsServiceManager`  
`class WindowsServiceManager : IDisposable`  
_internal*; L405-477_
- inherits: `IDisposable`
- desc: Helper functionality for manipulating Windows services
- L410 _private field_ `private readonly Native.ServiceHandle _serviceManagerHandle` — Native handle to the service manager
- L415-430 _public ctor_ `public WindowsServiceManager()` — Constructor. Opens a handle to the service manager.
- L435-438 _public method_ `public void Dispose()` — Dispose of this object
- L445-457 _public method_ `public WindowsService Open(string serviceName)` — Opens a service with the given name
- L468-476 _public method_ `public WindowsService Create(string name, string displayName, string commandLine, string? userName, string? password)` — Creates a service with the given settings
