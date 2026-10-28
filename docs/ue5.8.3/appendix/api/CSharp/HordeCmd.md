# CSharp / HordeCmd

- project root: `Source/Programs/Horde/HordeCmd`
- files: 47; symbols: 327
- symbol kinds: class=54, const=3, ctor=27, field=13, method=89, property=140, record=1
- access marked `*` is implicit (not written in source)

### `Source/Programs/Horde/HordeCmd/CmdApp.cs` (HordeCmd)


#### class `Horde.CmdApp`  
`class CmdApp`  
_internal*; L16-106_
- L18 _private* const_ `const string ToolDescription = "Horde Command-Line Tool"`
- L20 _private* property_ `static DirectoryReference DataDir { get; }`
- L22-44 _private* method_ `static async Task<int> Main(string[] args)`
- L46-49 _private* method_ `static DirectoryReference GetAppDir()`
- L51-62 _private* method_ `static DirectoryReference GetDataDir()`
- L64-68 _public method_ `public static ILoggerFactory CreateLoggerFactory(IConfiguration configuration, CommandLineArguments arguments)`
- L70-105 _private* method_ `static Serilog.ILogger CreateSerilogLogger(IConfiguration configuration, CommandLineArguments arguments)`

### `Source/Programs/Horde/HordeCmd/Commands/Archives/ArchiveCreate.cs` (HordeCmd)


#### class `Horde.Commands.Archives.ArchiveCreate`  
`class ArchiveCreate : StorageCommandBase`  
_internal*; L14-119_
- attrs: `[Command("archive", "create", "Creates a storage archive from a folder on the local hard drive")]`
- inherits: `StorageCommandBase`
- L18 _public property_ `public FileReference? File { get; set; }` — attrs: `[CommandLine("-File=")] [Description("Output file for the ref. Either -File=.. or -Ref=.. must be set.")]`
- L22 _public property_ `public string? Ref { get; set; }` — attrs: `[CommandLine("-Ref=")] [Description("Output ref for the data. Either -File=.. or -Ref=.. must be set.")]`
- L26 _public property_ `public string Input { get; set; }` — attrs: `[CommandLine("-Input=", Required = true)] [Description("Input file or directory")]`
- L30 _public property_ `public string Filter { get; set; }` — attrs: `[CommandLine("-Filter=")] [Description("Filter for files to include, in P4 syntax (eg. Foo/...).")]`
- L34 _public property_ `public bool CleanOutput { get; set; }` — attrs: `[CommandLine("-CleanOutput")] [Description("Clean the output folder before writing any data")]`
- L36-39 _public ctor_ `public ArchiveCreate(HttpStorageClient storageClient, BundleCache bundleCache) : base(storageClient, bundleCache)`
- L41-64 _public method_ `public override async Task<int> ExecuteAsync(ILogger logger)`
- L66-118 _private* method_ `async Task<int> ExecuteInternalAsync(IStorageNamespace store, ILogger logger)`

### `Source/Programs/Horde/HordeCmd/Commands/Archives/ArchiveDump.cs` (HordeCmd)


#### class `Horde.Commands.Archives.ArchiveDump`  
`internal class ArchiveDump : Command`  
_internal; L11-83_
- attrs: `[Command("archive", "dump", "Dumps the contents of a bundle")]`
- inherits: `Command`
- L15 _public property_ `public FileReference Input { get; set; }` — attrs: `[CommandLine("-Input=", Required = true)] [Description("Path to the bundle to display information for.")]`
- L19 _public property_ `public bool Verbose { get; set; }` — attrs: `[CommandLine("-Verbose")] [Description("Include more detailed information about the bundle.")]`
- L21-82 _public method_ `public override async Task<int> ExecuteAsync(ILogger logger)`

### `Source/Programs/Horde/HordeCmd/Commands/Archives/ArchiveExtract.cs` (HordeCmd)


#### class `Horde.Commands.Archives.ArchiveExtract`  
`internal class ArchiveExtract : StorageCommandBase`  
_internal; L15-103_
- attrs: `[Command("archive", "extract", "Extracts data from a bundle to the local hard drive")]`
- inherits: `StorageCommandBase`
- L19 _public property_ `public FileReference? File { get; set; }` — attrs: `[CommandLine("-File=")] [Description("Path to a text file containing the root ref to read. -File=..., -Ref=..., or -Node=... must be specified.")]`
- L23 _public property_ `public string? Ref { get; set; }` — attrs: `[CommandLine("-Ref=")] [Description("Name of a ref to read from the default storage namespace. -File=..., -Ref=..., or -Node=... must be specified.")]`
- L27 _public property_ `public string? Node { get; set; }` — attrs: `[CommandLine("-Node=")] [Description("Locator for a node to read as the root. -File=..., -Ref=..., or -Node=... must be specified.")]`
- L31 _public property_ `public bool Stats { get; set; }` — attrs: `[CommandLine("-Stats")] [Description("Outputs stats about the extraction process.")]`
- L35 _public property_ `public DirectoryReference OutputDir { get; set; }` — attrs: `[CommandLine("-OutputDir=", Required = true)] [Description("Directory to write extracted files.")]`
- L39 _public property_ `public bool CleanOutput { get; set; }` — attrs: `[CommandLine("-CleanOutput")] [Description("If set, deletes the contents of the output directory before extraction.")]`
- L43 _public property_ `public bool VerifyOutput { get; set; }` — attrs: `[CommandLine("-VerifyOutput")] [Description("Hashes output data to ensure it is as expected")]`
- L45-48 _public ctor_ `public ArchiveExtract(HttpStorageClient storageClient, BundleCache bundleCache) : base(storageClient, bundleCache)`
- L50-87 _public method_ `public override async Task<int> ExecuteAsync(ILogger logger)`
- L89-102 _protected method_ `protected async Task ExecuteInternalAsync(IStorageNamespace store, IBlobRef<DirectoryNode> handle, ExtractOptions options, ILogger logger)`

### `Source/Programs/Horde/HordeCmd/Commands/Artifacts/ArtifactDownload.cs` (HordeCmd)


#### class `Horde.Commands.Artifacts.ArtifactDownload`  
`class ArtifactDownload : Command`  
_internal*; L15-111_
- attrs: `[Command("artifact", "download", "Downloads an artifact by id")]`
- inherits: `Command`
- L19 _public property_ `public ArtifactId Id { get; set; }` — attrs: `[CommandLine("-Id=")] [Description("Unique identifier for the artifact")]`
- L23 _public property_ `public FileReference? File { get; set; }` — attrs: `[CommandLine("-File=")] [Description("Path to a .uartifact file to download")]`
- L27 _public property_ `public DirectoryReference OutputDir { get; set; }` — attrs: `[CommandLine("-OutputDir=", Required = true)] [Description("Directory to write extracted files.")]`
- L31 _public property_ `public bool Stats { get; set; }` — attrs: `[CommandLine("-Stats")] [Description("Outputs stats about the extraction process.")]`
- L35 _public property_ `public bool CleanOutput { get; set; }` — attrs: `[CommandLine("-CleanOutput")] [Description("If set, deletes the contents of the output directory before extraction.")]`
- L39 _public property_ `public bool VerifyOutput { get; set; }` — attrs: `[CommandLine("-VerifyOutput")] [Description("Hashes output data to ensure it is as expected")]`
- L41 _private* field_ `readonly IHordeClient _hordeClient`
- L43-46 _public ctor_ `public ArtifactDownload(IHordeClient hordeClient)`
- L48-110 _public method_ `public override async Task<int> ExecuteAsync(ILogger logger)`

### `Source/Programs/Horde/HordeCmd/Commands/Artifacts/ArtifactFind.cs` (HordeCmd)


#### class `Horde.Commands.Bundles.ArtifactFind`  
`class ArtifactFind : Command`  
_internal*; L14-111_
- attrs: `[Command("artifact", "find", "Finds artifacts matching the given query parameters")]`
- inherits: `Command`
- L18 _public property_ `public string? StreamId { get; set; }` — attrs: `[CommandLine("-StreamId=")] [Description("Stream containing the artifact")]`
- L22 _public property_ `public string? Name { get; set; }` — attrs: `[CommandLine("-Name=")] [Description("Name of the artifact")]`
- L26 _public property_ `public string? Type { get; set; }` — attrs: `[CommandLine("-Type=")] [Description("Type of artifact to find")]`
- L30 _public property_ `public string? MinCommit { get; set; }` — attrs: `[CommandLine("-MinCommit=")] [Description("Minimum commit to include in the results")]`
- L34 _public property_ `public string? MaxCommit { get; set; }` — attrs: `[CommandLine("-MaxCommit=")] [Description("Maximum commit to include in the results")]`
- L38 _public property_ `public List<string> Keys { get; }` — attrs: `[CommandLine("-Key=")] [Description("Artifact keys to search for. Multiple keys may be added to artifacts at upload time, eg. 'job:63dd5487c67f8a45453361c5/step:62ce'.")]`
- L42 _public property_ `public string? JobId { get; set; }` — attrs: `[CommandLine("-JobId=")] [Description("Finds artifacts associated with a particular job id")]`
- L46 _public property_ `public string? StepId { get; set; }` — attrs: `[CommandLine("-StepId=")] [Description("Finds artifacts produced by a particular job step. Used in conjunction with -Job.")]`
- L48 _private* field_ `readonly IHordeClient _hordeClient`
- L50-53 _public ctor_ `public ArtifactFind(IHordeClient hordeClient)`
- L55-110 _public method_ `public override async Task<int> ExecuteAsync(ILogger logger)`

### `Source/Programs/Horde/HordeCmd/Commands/Artifacts/ArtifactInfo.cs` (HordeCmd)


#### class `Horde.Commands.Artifacts.ArtifactInfo`  
`class ArtifactInfo : Command`  
_internal*; L12-56_
- attrs: `[Command("artifact", "info", "Gets information about an artifact")]`
- inherits: `Command`
- L16 _public property_ `public ArtifactId Id { get; set; }` — attrs: `[CommandLine("-Id=")] [Description("Unique identifier for the artifact")]`
- L18 _private* field_ `readonly IHordeClient _hordeClient`
- L20-23 _public ctor_ `public ArtifactInfo(IHordeClient hordeClient)`
- L25-55 _public method_ `public override async Task<int> ExecuteAsync(ILogger logger)`

### `Source/Programs/Horde/HordeCmd/Commands/Compute/ComputeRun.cs` (HordeCmd)


#### class `Horde.Commands.Compute.ComputeRun`  
`class ComputeRun : Command`  
_internal*; L22-179_
- attrs: `[Command("compute", "run", "Executes a command through the compute API")]`
- inherits: `Command`
- desc: Executes a compute command using a task definition and sandbox taken from the local machine
- L38 _public property_ `public string ClusterId { get; set; }` — attrs: `[CommandLine("-Cluster")] [Description("Name of the cluster to run the task on.")]`
- L42 _public property_ `public string? Pool { get; set; }` — attrs: `[CommandLine("-Pool")] [Description("ID of pool to run this task in")]`
- L46 _public property_ `public string? Requirements { get; set; }` — attrs: `[CommandLine("-Requirements=")] [Description("Query string to select the agent to run on")]`
- L50 _public property_ `public bool Local { get; set; }` — attrs: `[CommandLine("-Local")] [Description("Uses the local compute client, which runs the remote agent in the same process without using a Horde server.")]`
- L54 _public property_ `public bool Loopback { get; set; }` — attrs: `[CommandLine("-Loopback")] [Description("Runs an agent on the local machine in a separate process, and connect to it on the loopback adapter.")]`
- L58 _public property_ `public bool InProc { get; set; }` — attrs: `[CommandLine("-InProc")] [Description("If true, attempts to load and execute the compute process in the host process. The process to remote must be a .NET assembly invoked through the dotnet command.")]`
- L62 _public property_ `public string? Encryption { get; set; }` — attrs: `[CommandLine("-Encryption")] [Description("Encryption for communicating with compute task (Aes, Ssl, None).")]`
- L66 _public property_ `public DirectoryReference SandboxDir { get; set; }` — attrs: `[CommandLine("-Sandbox=")] [Description("Specifies the path to use for the remote sandbox.")]`
- L70 _private* property_ `FileReference TaskFile { get; set; }` — attrs: `[CommandLine("-Task=", Required = true)] [Description("Path to a JSON file describing the workload to execute. See ComputeRun.JsonComputeTask for structure of this document.")]`
- L72 _private* field_ `readonly IHordeClient _hordeClient`
- L77-80 _public ctor_ `public ComputeRun(IHordeClient hordeClient)` — Constructor
- L83-100 _public method_ `public override async Task<int> ExecuteAsync(ILogger logger)` — (inheritdoc)
- L102-132 _private* method_ `async Task<int> ExecuteAsync(IComputeClient client, ILogger logger)`
- L135-168 _private* method_ `async Task<bool> HandleRequestAsync(IComputeLease lease, ILogger logger, CancellationToken cancellationToken)` — (inheritdoc)
- L170-178 _private* method_ `static async Task<BlobLocator> CreateSandboxAsync(FileReference taskFile, IStorageNamespace storage, CancellationToken cancellationToken)`

#### class `Horde.Commands.Compute.ComputeRun.JsonComputeTask`  
`class JsonComputeTask`  
_private*; L24-34_
- L26 _public property_ `public string Executable { get; set; }`
- L27 _public property_ `public List<string> Arguments { get; set; }`
- L28 _public property_ `public string WorkingDir { get; set; }`
- L29 _public property_ `public Dictionary<string, string?> EnvVars { get; set; }`
- L30 _public property_ `public List<string> OutputPaths { get; set; }`
- L31 _public property_ `public string? ContainerImageUrl { get; set; }`
- L32 _public property_ `public bool ContainerReplaceEntrypoint { get; set; }`
- L33 _public property_ `public bool UseWine { get; set; }`

### `Source/Programs/Horde/HordeCmd/Commands/Compute/ComputeWorker.cs` (HordeCmd)


#### class `Horde.Commands.Compute.ComputeWorkerCommand`  
`class ComputeWorkerCommand : Command`  
_internal*; L17-50_
- attrs: `[Command("compute", "worker", "Runs the agent as a local compute host, accepting incoming connections on the loopback adapter with a given port")]`
- inherits: `Command`
- desc: Helper command for hosting a local compute worker in a separate process
- L21 _private* property_ `int Port { get; set; }` — attrs: `[CommandLine("-Port=")] [Description("Port number to listen on for remote work.")]`
- L23-41 _public method_ `public override async Task<int> ExecuteAsync(ILogger logger)`
- L43-49 _public method_ `public static async Task RunWorkerAsync(ComputeSocket socket, ILogger logger, CancellationToken cancellationToken)`

### `Source/Programs/Horde/HordeCmd/Commands/ConfigCommand.cs` (HordeCmd)


#### class `Horde.Commands.ConfigCommand`  
`class ConfigCommand : Command`  
_internal*; L11-28_
- attrs: `[Command("config", "Updates the configuration for the Horde tool")]`
- inherits: `Command`
- L15 _public property_ `public string? Server { get; set; }` — attrs: `[CommandLine("-Server=")] [Description("Updates the server URL")]`
- L18-27 _public method_ `public override Task<int> ExecuteAsync(ILogger logger)` — (inheritdoc)

### `Source/Programs/Horde/HordeCmd/Commands/InstallCommand.cs` (HordeCmd)


#### class `Horde.Commands.InstallCommand`  
`class InstallCommand : Command`  
_internal*; L10-43_
- attrs: `[Command("install", "Adds the directory containing the tool to the PATH environment variable.")]`
- inherits: `Command`
- L13-17 _public method_ `public override Task<int> ExecuteAsync(ILogger logger)` — (inheritdoc)
- L19-42 _internal method_ `internal static void Execute(bool install)`

### `Source/Programs/Horde/HordeCmd/Commands/LoginCommand.cs` (HordeCmd)


#### class `Horde.Commands.LoginCommand`  
`class LoginCommand : Command`  
_internal*; L12-52_
- attrs: `[Command("login", "Logs in to a Horde server")]`
- inherits: `Command`
- L24 _public property_ `public bool Token { get; set; }` — attrs: `[CommandLine("-Token")] [Description("Echo the bearer token acquired from the server to stdout")]`
- L26 _private* field_ `readonly IHordeClient _hordeClient`
- L28-31 _public ctor_ `public LoginCommand(IHordeClient hordeClient)`
- L34-51 _public method_ `public override async Task<int> ExecuteAsync(ILogger logger)` — (inheritdoc)

#### class `Horde.Commands.LoginCommand.GetAuthConfigResponse`  
`class GetAuthConfigResponse`  
_private*; L14-20_
- L16 _public property_ `public string? Method { get; set; }`
- L17 _public property_ `public string? ServerUrl { get; set; }`
- L18 _public property_ `public string? ClientId { get; set; }`
- L19 _public property_ `public string[]? RedirectUrls { get; set; }`

### `Source/Programs/Horde/HordeCmd/Commands/Perforce/PerforceBase.cs` (HordeCmd)


#### class `Horde.Commands.Perforce.PerforceBase`  
`abstract class PerforceBase : Command`  
_internal*; L12-149_
- inherits: `Command`
- L16 _protected property_ `protected string ServerAndPort { get; set; }` — attrs: `[CommandLine("-ServerAndPort")] [Description("Specifies the Perforce server and port")]`
- L20 _protected property_ `protected string UserName { get; set; }` — attrs: `[CommandLine("-User")] [Description("Specifies the Perforce username")]`
- L24 _protected property_ `protected DirectoryReference BaseDir { get; set; }` — attrs: `[CommandLine("-BaseDir", Required = true)] [Description("Base directory to use for syncing workspaces")]`
- L28 _protected property_ `protected bool Overwrite { get; set; }` — attrs: `[CommandLine("-Overwrite")] [Description("")]`
- L32 _protected property_ `protected bool PreferNativeClient { get; set; }` — attrs: `[CommandLine("-PreferNativeClient")] [Description("Prefer to use native Perforce client (instead of launching separate p4 process)")]`
- L36 _private* property_ `string UseHaveTable { get; set; }` — attrs: `[CommandLine("-UseHaveTable")] [Description("Use have-table for syncing")]`
- L38-58 _public method_ `public override void Configure(CommandLineArguments arguments, ILogger logger)`
- L60-71 _public method_ `public override async Task<int> ExecuteAsync(ILogger logger)`
- L73 _protected method_ `protected abstract Task ExecuteAsync(IPerforceConnection perforce, ManagedWorkspace repo, ILogger logger)`
- L75-110 _protected method_ `protected static long ParseSize(string size)`
- L112-120 _protected method_ `protected static int ParseChangeNumber(string change)`
- L122-132 _protected method_ `protected static int ParseChangeNumberOrLatest(string change)`
- L134-148 _protected method_ `protected static List<string> ExpandFilters(List<string> arguments)`

### `Source/Programs/Horde/HordeCmd/Commands/Perforce/PerforceClean.cs` (HordeCmd)


#### class `Horde.Commands.Perforce.PerforceClean`  
`class PerforceClean : PerforceBase`  
_internal*; L12-22_
- attrs: `[Command("perforce", "clean", "Cleans all modified files from the workspace.")]`
- inherits: `PerforceBase`
- L16 _public property_ `public bool Incremental { get; set; }` — attrs: `[CommandLine("-Incremental")] [Description("Performs an incremental sync, without removing intermediates")]`
- L18-21 _protected method_ `protected override Task ExecuteAsync(IPerforceConnection perforce, ManagedWorkspace repo, ILogger logger)`

### `Source/Programs/Horde/HordeCmd/Commands/Perforce/PerforceClear.cs` (HordeCmd)


#### class `Horde.Commands.Perforce.PerforceClear`  
`class PerforceClear : PerforceBase`  
_internal*; L11-17_
- attrs: `[Command("perforce", "clear", "Empties the staging directory of any files, returning them to the cache")]`
- inherits: `PerforceBase`
- L13-16 _protected method_ `protected override Task ExecuteAsync(IPerforceConnection perforce, ManagedWorkspace repo, ILogger logger)`

### `Source/Programs/Horde/HordeCmd/Commands/Perforce/PerforceDump.cs` (HordeCmd)


#### class `Horde.Commands.Perforce.PerforceDump`  
`class PerforceDump : PerforceBase`  
_internal*; L11-18_
- attrs: `[Command("perforce", "dump", "Dumps the contents of the repository to the log for analysis")]`
- inherits: `PerforceBase`
- L13-17 _protected method_ `protected override Task ExecuteAsync(IPerforceConnection perforce, ManagedWorkspace repo, ILogger logger)`

### `Source/Programs/Horde/HordeCmd/Commands/Perforce/PerforcePopulate.cs` (HordeCmd)


#### class `Horde.Commands.Perforce.PerforcePopulate`  
`class PerforcePopulate : PerforceBase`  
_internal*; L12-45_
- attrs: `[Command("perforce", "populatecache", "Populates the cache with the head revision of the given streams")]`
- inherits: `PerforceBase`
- L16 _private* property_ `List<string> ClientAndStreamParams { get; set; }` — attrs: `[CommandLine("-ClientAndStream=")] [Description("Specifies client and stream pairs, in the format Client:Stream")]`
- L20 _private* property_ `List<string> Filters { get; set; }` — attrs: `[CommandLine("-Filter=")] [Description("Filters for the files to sync, in P4 syntax (eg. /Engine/...)")]`
- L24 _private* property_ `bool FakeSync { get; set; }` — attrs: `[CommandLine("-FakeSync")] [Description("Simulates the sync without actually fetching any files")]`
- L26-44 _protected method_ `protected override async Task ExecuteAsync(IPerforceConnection perforce, ManagedWorkspace repo, ILogger logger)`

### `Source/Programs/Horde/HordeCmd/Commands/Perforce/PerforcePurge.cs` (HordeCmd)


#### class `Horde.Commands.Perforce.PerforcePurge`  
`class PerforcePurge : PerforceBase`  
_internal*; L12-28_
- attrs: `[Command("perforce", "purgecache", "Shrink the size of the cache to the given size")]`
- inherits: `PerforceBase`
- L16 _private* property_ `string? SizeParam { get; set; }` — attrs: `[CommandLine("-Size=")] [Description("Maximum size of the cache")]`
- L18-27 _protected method_ `protected override Task ExecuteAsync(IPerforceConnection perforce, ManagedWorkspace repo, ILogger logger)`

### `Source/Programs/Horde/HordeCmd/Commands/Perforce/PerforceRepair.cs` (HordeCmd)


#### class `Horde.Commands.Perforce.PerforceRepair`  
`class PerforceRepair : PerforceBase`  
_internal*; L11-17_
- attrs: `[Command("perforce", "repaircache", "Checks the integrity of the cache, and removes any invalid files")]`
- inherits: `PerforceBase`
- L13-16 _protected method_ `protected override Task ExecuteAsync(IPerforceConnection perforce, ManagedWorkspace repo, ILogger logger)`

### `Source/Programs/Horde/HordeCmd/Commands/Perforce/PerforceRevert.cs` (HordeCmd)


#### class `Horde.Commands.Perforce.PerforceRevert`  
`class PerforceRevert : PerforceBase`  
_internal*; L12-23_
- attrs: `[Command("perforce", "revert", "Revert all files that are open in the current workspace. Does not replace them with valid revisions.")]`
- inherits: `PerforceBase`
- L16 _private* property_ `string ClientName { get; set; }` — attrs: `[CommandLine("-Client=", Required = true)] [Description("Client to revert all files for")]`
- L18-22 _protected method_ `protected override async Task ExecuteAsync(IPerforceConnection perforce, ManagedWorkspace repo, ILogger logger)`

### `Source/Programs/Horde/HordeCmd/Commands/Perforce/PerforceSetup.cs` (HordeCmd)


#### class `Horde.Commands.Perforce.PerforceSetup`  
`class PerforceSetup : PerforceBase`  
_internal*; L12-27_
- attrs: `[Command("perforce", "setup", "Creates or updates a client to use a given stream")]`
- inherits: `PerforceBase`
- L16 _private* property_ `string ClientName { get; set; }` — attrs: `[CommandLine("-Client=", Required = true)] [Description("Name of the client to create")]`
- L20 _private* property_ `string StreamName { get; set; }` — attrs: `[CommandLine("-Stream=", Required = true)] [Description("Name of the stream to configure")]`
- L22-26 _protected method_ `protected override async Task ExecuteAsync(IPerforceConnection perforce, ManagedWorkspace repo, ILogger logger)`

### `Source/Programs/Horde/HordeCmd/Commands/Perforce/PerforceSizes.cs` (HordeCmd)


#### class `Horde.Commands.Perforce.PerforceSizes`  
`class PerforceSizes : PerforceBase`  
_internal*; L12-31_
- attrs: `[Command("perforce", "sizes", "Gathers stats for which streams take the most amount of space in the cache for the given configuration")]`
- inherits: `PerforceBase`
- L16 _private* property_ `string TempClientName { get; set; }` — attrs: `[CommandLine("-TempClient=", Required = true)] [Description("Name of a temporary client to switch between streams gathering metadata. Will be created if it does not exist.")]`
- L20 _private* property_ `List<string> StreamNames { get; set; }` — attrs: `[CommandLine("-Stream=")] [Description("Streams that should be included in the output")]`
- L24 _private* property_ `List<string> Filters { get; set; }` — attrs: `[CommandLine("-Filter=")] [Description("Filters for the files to sync, in P4 syntax (eg. /Engine/...)")]`
- L26-30 _protected method_ `protected override async Task ExecuteAsync(IPerforceConnection perforce, ManagedWorkspace repo, ILogger logger)`

### `Source/Programs/Horde/HordeCmd/Commands/Perforce/PerforceStatus.cs` (HordeCmd)


#### class `Horde.Commands.Perforce.PerforceStatus`  
`class PerforceStatus : PerforceBase`  
_internal*; L11-17_
- attrs: `[Command("perforce", "status", "Prints information about the state of the cache and workspace")]`
- inherits: `PerforceBase`
- L13-16 _protected method_ `protected override async Task ExecuteAsync(IPerforceConnection perforce, ManagedWorkspace repo, ILogger logger)`

### `Source/Programs/Horde/HordeCmd/Commands/Perforce/PerforceSync.cs` (HordeCmd)


#### class `Horde.Commands.Perforce.PerforceSync`  
`class PerforceSync : PerforceBase`  
_internal*; L12-59_
- attrs: `[Command("perforce", "sync", "Syncs the files for a particular stream and changelist")]`
- inherits: `PerforceBase`
- L16 _public property_ `public string ClientName { get; set; }` — attrs: `[CommandLine("-Client=", Required = true)] [Description("Name of the client to sync. Will be created if it does not exist.")]`
- L20 _public property_ `public string StreamName { get; set; }` — attrs: `[CommandLine("-Stream=", Required = true)] [Description("The stream to sync")]`
- L24 _public property_ `public string Change { get; set; }` — attrs: `[CommandLine("-Change=")] [Description("The change to sync. May be a changelist number, or 'Latest'")]`
- L28 _public property_ `public int PreflightChange { get; set; }` — attrs: `[CommandLine("-Preflight=")] [Description("The change to unshelve into the workspace")]`
- L32 _private* property_ `FileReference? CacheFile { get; set; }` — attrs: `[CommandLine] [Description("Optional path to a cache file used to store workspace metadata. Using a location on a network share allows multiple machines syncing the same CL to only query Perforce state once.")]`
- L36 _public property_ `public List<string> Filters { get; set; }` — attrs: `[CommandLine("-Filter=")] [Description("Filters for the files to sync, in P4 syntax (eg. /Engine/...)")]`
- L40 _public property_ `public bool IncrementalSync { get; set; }` — attrs: `[CommandLine("-Incremental")] [Description("Performs an incremental sync, without removing intermediates")]`
- L44 _public property_ `public bool FakeSync { get; set; }` — attrs: `[CommandLine("-FakeSync")] [Description("Simulates the sync without actually fetching any files")]`
- L46-58 _protected method_ `protected override async Task ExecuteAsync(IPerforceConnection perforce, ManagedWorkspace repo, ILogger logger)`

### `Source/Programs/Horde/HordeCmd/Commands/Profile/ProfileChunking.cs` (HordeCmd)


#### class `Horde.Commands.Profile.ProfileChunking`  
`class ProfileChunking : StorageCommandBase`  
_internal*; L15-166_
- attrs: `[Command("profile", "chunking", "Profiles chunking over a source directory")]`
- inherits: `StorageCommandBase`
- L21 _public property_ `public string Input { get; set; }` — attrs: `[CommandLine("-Input=", Required = true)] [Description("Input file or directory")]`
- L25 _public property_ `public DirectoryReference TraceDir { get; set; }` — attrs: `[CommandLine("-TraceDir=", Required = true)] [Description("Directory to write traces to")]`
- L28 _public property_ `public bool Verify { get; set; }` — attrs: `[CommandLine("-Verify")]`
- L30-33 _public ctor_ `public ProfileChunking(HttpStorageClient storageClient, BundleCache bundleCache) : base(storageClient, bundleCache)`
- L35-72 _public method_ `public override async Task<int> ExecuteAsync(ILogger logger)`
- L74-82 _private* method_ `static async Task ReadFilesAsync(List<FileReference> files, ChannelWriter<ChunkerSource> writer, CancellationToken cancellationToken)`
- L123-165 _private* method_ `static async Task<List<ChunkInfo>> ChunkDataAsync(FileReference file, List<FileReference> files, bool useSerialPipeline, ILogger logger)`

#### record `Horde.Commands.Profile.ProfileChunking.ChunkInfo`  
`record class ChunkInfo(long Offset, int Length, IoHash Hash)`  
_private*; L17-17_

#### class `Horde.Commands.Profile.ProfileChunking.ChunkReader`  
`class ChunkReader`  
_private*; L84-121_
- L86 _public field_ `public int _filesRead`
- L87 _public field_ `public int _chunksRead`
- L88 _public field_ `public long _bytesRead`
- L90 _private* field_ `readonly ILogger _logger`
- L92 _public field_ `public List<ChunkInfo> _chunks = new List<ChunkInfo>()`
- L94 _public ctor_ `public ChunkReader(ILogger logger)`
- L97-120 _public method_ `public async Task ReadChunksAsync(ChannelReader<ChunkerOutput> reader, CancellationToken cancellationToken)`

### `Source/Programs/Horde/HordeCmd/Commands/StorageCommandBase.cs` (HordeCmd)


#### class `Horde.Commands.StorageCommandBase`  
`abstract class StorageCommandBase : Command`  
_internal*; L13-60_
- inherits: `Command`
- desc: Base class for commands that require a configured storage namespace
- L20 _public property_ `public NamespaceId Namespace { get; set; }` — attrs: `[CommandLine("-Namespace=")] [Description("Namespace for data to manipulate")]` — Namespace to use
- L27 _public property_ `public string? Path { get; set; }` — attrs: `[CommandLine("-Path=")] [Description("Relative path on the server for the store to write to/from (eg. api/v1/storage/default)")]` — Base URI to upload to
- L32 _public property_ `public BundleCache BundleCache { get; }` — Cache for storage
- L34 _private* field_ `readonly HttpStorageClient _storageClient`
- L39-44 _public ctor_ `public StorageCommandBase(HttpStorageClient storageClient, BundleCache bundleCache)` — Constructor
- L49-59 _public method_ `public IStorageNamespace GetStorageNamespace()` — Creates a new client instance

### `Source/Programs/Horde/HordeCmd/Commands/Tools/ToolDownload.cs` (HordeCmd)


#### class `HordeCmd.Commands.Tools.ToolDownload`  
`class ToolDownload(IHordeClient hordeClient) : Command`  
_internal*; L13-43_
- attrs: `[Command("tool", "download", "Downloads a tool from the server to a local directory")]`
- L17 _public property_ `public ToolId Id { get; set; }` — attrs: `[CommandLine("-Id=", Required = true)] [Description("The tool to download")]`
- L21 _public property_ `public ToolDeploymentId? DeploymentId { get; set; }` — attrs: `[CommandLine("-Deployment=")] [Description("Deployment to fetch")]`
- L25 _public property_ `public DirectoryReference OutputDir { get; set; }` — attrs: `[CommandLine("-OutputDir=", Required = true)] [Description("Output directory for the downloaded tool data")]`
- L28-42 _public method_ `public override async Task<int> ExecuteAsync(ILogger logger)` — (inheritdoc)

### `Source/Programs/Horde/HordeCmd/Commands/Tools/ToolList.cs` (HordeCmd)


#### class `HordeCmd.Commands.Tools.ToolList`  
`class ToolList(IHordeClient hordeClient) : Command`  
_internal*; L11-29_
- attrs: `[Command("tool", "list", "List all tools available for download")]`
- L14-28 _public method_ `public override async Task<int> ExecuteAsync(ILogger logger)` — (inheritdoc)

### `Source/Programs/Horde/HordeCmd/Commands/Tools/ToolUpload.cs` (HordeCmd)


#### class `HordeCmd.Commands.Tools.ToolUpload`  
`class ToolUpload(IHordeClient hordeClient) : Command`  
_internal*; L14-46_
- attrs: `[Command("tool", "upload", "Uploads a tool from a local directory")]`
- L18 _public property_ `public ToolId ToolId { get; set; }` — attrs: `[CommandLine("-Id=", Required = true)] [Description("Identifier for the tool to upload")]`
- L22 _public property_ `public string? Version { get; set; }` — attrs: `[CommandLine("-Version=")] [Description("Optional version number for the new upload")]`
- L26 _public property_ `public DirectoryReference InputDir { get; set; }` — attrs: `[CommandLine("-InputDir=", Required = true)] [Description("Directory containing files to upload for the tool")]`
- L29-45 _public method_ `public override async Task<int> ExecuteAsync(ILogger logger)` — (inheritdoc)

### `Source/Programs/Horde/HordeCmd/Commands/UninstallCommand.cs` (HordeCmd)


#### class `Horde.Commands.UinstallCommand`  
`class UinstallCommand : Command`  
_internal*; L9-17_
- attrs: `[Command("uninstall", "Removes the directory containing the tool from the PATH environment variable.")]`
- inherits: `Command`
- L12-16 _public method_ `public override Task<int> ExecuteAsync(ILogger logger)` — (inheritdoc)

### `Source/Programs/Horde/HordeCmd/Commands/Vcs/VcsBase.cs` (HordeCmd)


#### class `Horde.Commands.Vcs.VcsBase`  
`abstract class VcsBase : Command`  
_internal*; L11-359_
- inherits: `Command`
- L14 _public property_ `public DirectoryReference? BaseDir { get; set; }` — attrs: `[CommandLine("-BaseDir=")]`
- L17 _public property_ `public NamespaceId NamespaceId { get; set; }` — attrs: `[CommandLine("-Namespace=")]`
- L149 _private* const_ `const string DataDir = ".horde"`
- L150 _private* const_ `const string StateFileName = "state.dat"`
- L152 _private* field_ `readonly IStorageClient _storageClient`
- L154-157 _protected ctor_ `protected VcsBase(IStorageClient storageClient)`
- L159 _protected method_ `protected IStorageNamespace GetStorageNamespace()`
- L161-166 _protected method_ `protected static async Task<WorkspaceState> ReadStateAsync(DirectoryReference rootDir)`
- L168-183 _protected method_ `protected static async Task WriteStateAsync(DirectoryReference rootDir, WorkspaceState state)`
- L185-188 _protected method_ `protected static async Task InitAsync(DirectoryReference rootDir)`
- L190-207 _protected method_ `protected DirectoryReference FindRootDir()`
- L209 _protected method_ `protected static Task<DirectoryState> GetCurrentDirectoryState(DirectoryReference rootDir, DirectoryState? oldState)`
- L211-257 _protected method_ `protected static async Task<DirectoryState> GetCurrentDirectoryStateAsync(DirectoryInfo directoryInfo, DirectoryState? oldState)`
- L259-278 _protected method_ `protected static void RemoveAddedFiles(DirectoryState oldState, DirectoryState newState)`
- L280-304 _protected method_ `protected static DirectoryState DedupTrees(DirectoryState oldState, DirectoryState newState)`
- L306 _protected method_ `protected static void PrintDelta(DirectoryState oldState, DirectoryState newState, ILogger logger)`
- L308-341 _private* method_ `static void PrintDelta(string prefix, DirectoryState oldState, DirectoryState newState, ILogger logger)`
- L343-358 _protected method_ `protected static async Task<CommitNode?> GetCommitAsync(IStorageNamespace storageNamespace, RefName branchName, int change = 0)`

#### class `Horde.Commands.Vcs.VcsBase.FileState`  
`protected class FileState`  
_protected; L19-59_
- L21 _public property_ `public IoHash Hash { get; set; }`
- L22 _public property_ `public long Length { get; set; }`
- L23 _public property_ `public long LastModifiedTimeUtc { get; set; }`
- L25-29 _public ctor_ `public FileState(FileInfo fileInfo, IoHash hash = default)`
- L31-35 _public ctor_ `public FileState(FileState other)`
- L37-42 _public ctor_ `public FileState(IMemoryReader reader)`
- L44 _public method_ `public bool Modified(FileInfo fileInfo)`
- L46-50 _public method_ `public void Update(FileInfo fileInfo)`
- L52-58 _public method_ `public void Write(IMemoryWriter writer)`

#### class `Horde.Commands.Vcs.VcsBase.DirectoryState`  
`protected class DirectoryState`  
_protected; L61-114_
- L63 _public property_ `public IoHash Hash { get; set; }`
- L64 _public property_ `public Dictionary<string, DirectoryState> Directories { get; }`
- L65 _public property_ `public Dictionary<string, FileState> Files { get; }`
- L67-71 _public ctor_ `public DirectoryState()`
- L73-94 _public ctor_ `public DirectoryState(IMemoryReader reader)`
- L96-113 _public method_ `public void Write(IMemoryWriter writer)`

#### class `Horde.Commands.Vcs.VcsBase.WorkspaceState`  
`protected class WorkspaceState`  
_protected; L116-147_
- L118 _public property_ `public RefName Branch { get; set; }`
- L119 _public property_ `public int Change { get; set; }`
- L120 _public property_ `public DirectoryState Tree { get; set; }`
- L122-125 _public ctor_ `public WorkspaceState() : this(new RefName("main"), 0, new DirectoryState())`
- L127-132 _public ctor_ `public WorkspaceState(RefName branch, int change, DirectoryState tree)`
- L134-139 _public ctor_ `public WorkspaceState(IMemoryReader reader)`
- L141-146 _public method_ `public void Write(IMemoryWriter writer)`

### `Source/Programs/Horde/HordeCmd/Commands/Vcs/VcsBranch.cs` (HordeCmd)


#### class `Horde.Commands.Vcs.VcsBranch`  
`class VcsBranch : VcsBase`  
_internal*; L10-43_
- attrs: `[Command("vcs", "branch", "Switch to a new branch", Advertise = false)]`
- inherits: `VcsBase`
- L13 _public property_ `public string Name { get; set; }` — attrs: `[CommandLine(Prefix = "-Name=", Required = true)]`
- L15-18 _public ctor_ `public VcsBranch(IStorageClient storageClient) : base(storageClient)`
- L20-42 _public method_ `public override async Task<int> ExecuteAsync(ILogger logger)`

### `Source/Programs/Horde/HordeCmd/Commands/Vcs/VcsCheckout.cs` (HordeCmd)


#### class `Horde.Commands.Vcs.VcsCheckout`  
`class VcsCheckout : VcsBase`  
_internal*; L11-124_
- attrs: `[Command("vcs", "checkout", "Checkout a particular branch/change", Advertise = false)]`
- inherits: `VcsBase`
- L14 _public property_ `public string? Branch { get; set; }` — attrs: `[CommandLine("-Branch")]`
- L17 _public property_ `public int Change { get; set; }` — attrs: `[CommandLine("-Change=")]`
- L20 _public property_ `public bool Clean { get; set; }` — attrs: `[CommandLine("-Clean")]`
- L23 _public property_ `public bool Force { get; set; }` — attrs: `[CommandLine("-Force")]`
- L25-28 _public ctor_ `public VcsCheckout(IStorageClient storageClient) : base(storageClient)`
- L30-68 _public method_ `public override async Task<int> ExecuteAsync(ILogger logger)`
- L70-115 _protected method_ `protected static async Task<DirectoryState> RealizeAsync(DirectoryNodeRef directoryRef, DirectoryReference dirPath, DirectoryState? directoryState, bool clean, ILogger logger)`
- L117-123 _private* method_ `static async Task<FileState> CheckoutFileAsync(FileEntry fileRef, FileInfo fileInfo, ILogger logger)`

### `Source/Programs/Horde/HordeCmd/Commands/Vcs/VcsClone.cs` (HordeCmd)


#### class `Horde.Commands.Vcs.VcsClone`  
`class VcsClone : VcsCheckout`  
_internal*; L11-42_
- attrs: `[Command("vcs", "clone", "Initialize a directory for VCS-like operations", Advertise = false)]`
- inherits: `VcsCheckout`
- L13-16 _public ctor_ `public VcsClone(IStorageClient storageClient) : base(storageClient)`
- L18-41 _public method_ `public override async Task<int> ExecuteAsync(ILogger logger)`

### `Source/Programs/Horde/HordeCmd/Commands/Vcs/VcsCommit.cs` (HordeCmd)


#### class `Horde.Commands.Vcs.VcsCommit`  
`class VcsCommit : VcsBase`  
_internal*; L10-133_
- attrs: `[Command("vcs", "commit", "Commits data to the VCS store", Advertise = false)]`
- inherits: `VcsBase`
- L13 _public property_ `public string UserName { get; set; }` — attrs: `[CommandLine("-User=")]`
- L16 _public property_ `public string? Message { get; set; }` — attrs: `[CommandLine("-Message=")]`
- L18-21 _public ctor_ `public VcsCommit(IStorageClient storageClient) : base(storageClient)`
- L23-102 _public method_ `public override Task<int> ExecuteAsync(ILogger logger)`

### `Source/Programs/Horde/HordeCmd/Commands/Vcs/VcsInit.cs` (HordeCmd)


#### class `Horde.Commands.Vcs.VcsInit`  
`class VcsInit : VcsBase`  
_internal*; L10-24_
- attrs: `[Command("vcs", "init", "Initialize a directory for VCS-like operations", Advertise = false)]`
- inherits: `VcsBase`
- L12-15 _public ctor_ `public VcsInit(IStorageClient storageClient) : base(storageClient)`
- L17-23 _public method_ `public override async Task<int> ExecuteAsync(ILogger logger)`

### `Source/Programs/Horde/HordeCmd/Commands/Vcs/VcsLog.cs` (HordeCmd)


#### class `Horde.Commands.Vcs.VcsLog`  
`class VcsLog : VcsBase`  
_internal*; L12-57_
- attrs: `[Command("vcs", "log", "Print a history of commits", Advertise = false)]`
- inherits: `VcsBase`
- L15 _public property_ `public int Count { get; set; }` — attrs: `[CommandLine("-Count")]`
- L17-20 _public ctor_ `public VcsLog(IStorageClient storageClient) : base(storageClient)`
- L22-56 _public method_ `public override async Task<int> ExecuteAsync(ILogger logger)`

### `Source/Programs/Horde/HordeCmd/Commands/Vcs/VcsStatus.cs` (HordeCmd)


#### class `Horde.Commands.Vcs.VcsStatus`  
`class VcsStatus : VcsBase`  
_internal*; L10-39_
- attrs: `[Command("vcs", "status", "Find status of local files", Advertise = false)]`
- inherits: `VcsBase`
- L12-15 _public ctor_ `public VcsStatus(IStorageClient storageClient) : base(storageClient)`
- L17-38 _public method_ `public override async Task<int> ExecuteAsync(ILogger logger)`

### `Source/Programs/Horde/HordeCmd/Commands/Workspace/WorkspaceClean.cs` (HordeCmd)


#### class `Horde.Commands.Workspace.WorkspaceClean`  
`class WorkspaceClean : WorkspaceStatusBase`  
_internal*; L11-15_
- attrs: `[Command("workspace", "clean", "Removes all untracked files from the workspace")]`
- inherits: `WorkspaceStatusBase`
- L13 _protected method_ `protected override Task ExecuteInternalAsync(Workspace workspace, FileFilter? filter, WorkspaceStatusFlags flags, CancellationToken cancellationToken)`

### `Source/Programs/Horde/HordeCmd/Commands/Workspace/WorkspaceDrop.cs` (HordeCmd)


#### class `Horde.Commands.Workspace.WorkspaceDrop`  
`class WorkspaceDrop : Command`  
_internal*; L13-43_
- attrs: `[Command("workspace", "drop", "Drops a layer from a workspace")]`
- inherits: `Command`
- L17 _public property_ `public DirectoryReference? RootDir { get; set; }` — attrs: `[CommandLine("-Root=")] [Description("Root directory for the workspace.")]`
- L21 _public property_ `public WorkspaceLayerId LayerId { get; set; }` — attrs: `[CommandLine("-Layer=")] [Description("Name of the layer to remove.")]`
- L23-42 _public method_ `public override async Task<int> ExecuteAsync(ILogger logger)`

### `Source/Programs/Horde/HordeCmd/Commands/Workspace/WorkspaceForget.cs` (HordeCmd)


#### class `Horde.Commands.Workspace.WorkspaceForget`  
`class WorkspaceForget : Command`  
_internal*; L13-44_
- attrs: `[Command("workspace", "forget", "Removes files in the workspace from tracking", AcceptsPositionalArguments = true)]`
- inherits: `Command`
- L17 _public property_ `public DirectoryReference? RootDir { get; set; }` — attrs: `[CommandLine("-Root=")] [Description("Root directory for the workspace.")]`
- L21 _public property_ `public WorkspaceLayerId LayerId { get; set; }` — attrs: `[CommandLine("-Layer=")] [Description("Layer to remove files from")]`
- L25 _private* property_ `List<string> Paths { get; set; }` — attrs: `[CommandLine("-Path=", Positional = true, Required = true)] [Description("Filter for the files to remove")]`
- L27-43 _public method_ `public override async Task<int> ExecuteAsync(ILogger logger)`

### `Source/Programs/Horde/HordeCmd/Commands/Workspace/WorkspaceInit.cs` (HordeCmd)


#### class `Horde.Commands.Workspace.WorkspaceInit`  
`class WorkspaceInit : Command`  
_internal*; L12-27_
- attrs: `[Command("workspace", "init", "Initialize a managed workspace in the current folder")]`
- inherits: `Command`
- L16 _public property_ `public DirectoryReference? RootDir { get; set; }` — attrs: `[CommandLine("-Root=")] [Description("Root directory for the managed workspace.")]`
- L18-26 _public method_ `public override async Task<int> ExecuteAsync(ILogger logger)`

### `Source/Programs/Horde/HordeCmd/Commands/Workspace/WorkspaceLayers.cs` (HordeCmd)


#### class `Horde.Commands.Workspace.WorkspaceLayers`  
`class WorkspaceLayers : Command`  
_internal*; L13-40_
- attrs: `[Command("workspace", "layers", "Lists all layers in the workspace")]`
- inherits: `Command`
- L17 _public property_ `public DirectoryReference? RootDir { get; set; }` — attrs: `[CommandLine("-Root=")] [Description("Root directory for the workspace.")]`
- L19-39 _public method_ `public override async Task<int> ExecuteAsync(ILogger logger)`

### `Source/Programs/Horde/HordeCmd/Commands/Workspace/WorkspaceStatus.cs` (HordeCmd)


#### class `Horde.Commands.Workspace.WorkspaceStatus`  
`class WorkspaceStatus : WorkspaceStatusBase`  
_internal*; L13-17_
- attrs: `[Command("workspace", "status", "Prints the current status of the workspace", AcceptsPositionalArguments = true)]`
- inherits: `WorkspaceStatusBase`
- L15 _protected method_ `protected override Task ExecuteInternalAsync(Workspace workspace, FileFilter? filter, WorkspaceStatusFlags flags, CancellationToken cancellationToken)`

#### class `Horde.Commands.Workspace.WorkspaceStatusBase`  
`abstract class WorkspaceStatusBase : Command`  
_internal*; L19-125_
- inherits: `Command`
- L23 _public property_ `public DirectoryReference? RootDir { get; set; }` — attrs: `[CommandLine("-Root=")] [Description("Root directory for the workspace.")]`
- L27 _public property_ `public List<string> Paths { get; set; }` — attrs: `[CommandLine("-Path=", Positional = true)] [Description("Path of the files to query")]`
- L31 _public property_ `public bool All { get; set; }` — attrs: `[CommandLine("-All")] [Description("Show all files")]`
- L35 _public property_ `public bool Added { get; set; }` — attrs: `[CommandLine("-Added")] [Description("Show added files")]`
- L39 _public property_ `public bool Modified { get; set; }` — attrs: `[CommandLine("-Modified")] [Description("Show modified files")]`
- L43 _public property_ `public bool Unmodified { get; set; }` — attrs: `[CommandLine("-Unmodified")] [Description("Show all unmodified files")]`
- L47 _public property_ `public bool Removed { get; set; }` — attrs: `[CommandLine("-Removed")] [Description("Show removed files")]`
- L51 _public property_ `public bool IgnoreAdded { get; set; }` — attrs: `[CommandLine("-IgnoreAdded")] [Description("Ignore added files")]`
- L55 _public property_ `public bool IgnoreModified { get; set; }` — attrs: `[CommandLine("-IgnoreModified")] [Description("Ignore modified files")]`
- L59 _public property_ `public bool IgnoreUnmodified { get; set; }` — attrs: `[CommandLine("-IgnoreUnmodified")] [Description("Ignore unmodified files")]`
- L63 _public property_ `public bool IgnoreRemoved { get; set; }` — attrs: `[CommandLine("-IgnoreRemoved")] [Description("Ignore removed files")]`
- L65-122 _public method_ `public override async Task<int> ExecuteAsync(ILogger logger)`
- L124 _protected method_ `protected abstract Task ExecuteInternalAsync(Workspace workspace, FileFilter? filter, WorkspaceStatusFlags flags, CancellationToken cancellationToken)`

### `Source/Programs/Horde/HordeCmd/Commands/Workspace/WorkspaceSync.cs` (HordeCmd)


#### class `Horde.Commands.Workspace.WorkspaceSync`  
`class WorkspaceSync : Command`  
_internal*; L17-151_
- attrs: `[Command("workspace", "sync", "Extracts an archive into the workspace")]`
- inherits: `Command`
- L21 _public property_ `public DirectoryReference? RootDir { get; set; }` — attrs: `[CommandLine("-Root=")] [Description("Root directory for the managed workspace.")]`
- L25 _public property_ `public DirectoryReference? TargetDir { get; set; }` — attrs: `[CommandLine("-Target=")] [Description("Directory to extract files to. Must be under the workspace root.")]`
- L29 _public property_ `public string? Artifact { get; set; }` — attrs: `[CommandLine("-Artifact=")] [Description("Artifact to extract into the workspace")]`
- L33 _public property_ `public string Namespace { get; set; }` — attrs: `[CommandLine("-Namespace=")] [Description("Namespace containing the node or ref to extract")]`
- L37 _public property_ `public string? Ref { get; set; }` — attrs: `[CommandLine("-Ref=")] [Description("Name of a ref to extract to this workspace.")]`
- L41 _public property_ `public string? Node { get; set; }` — attrs: `[CommandLine("-Node=")] [Description("Locator for a node to extract to this workspace.")]`
- L45 _public property_ `public WorkspaceLayerId LayerId { get; set; }` — attrs: `[CommandLine("-Layer=")] [Description("Name of the layer to extract to.")]`
- L49 _public property_ `public bool Stats { get; set; }` — attrs: `[CommandLine("-Stats")] [Description("Outputs stats for the extraction operation.")]`
- L51 _private* field_ `readonly IHordeClient _hordeClient`
- L53-56 _public ctor_ `public WorkspaceSync(IHordeClient hordeClient)`
- L58-97 _public method_ `public override async Task<int> ExecuteAsync(ILogger logger)`
- L99-150 _private* method_ `async Task<int> ExecuteInternalAsync(IStorageNamespace store, IBlobRef<DirectoryNode> handle, ILogger logger)`

### `Source/Programs/Horde/HordeCmd/Commands/Workspace/WorkspaceTrack.cs` (HordeCmd)


#### class `Horde.Commands.Workspace.WorkspaceTrack`  
`class WorkspaceTrack : Command`  
_internal*; L13-72_
- attrs: `[Command("workspace", "track", "Tracks files in their current state with the workspace", AcceptsPositionalArguments = true)]`
- inherits: `Command`
- L17 _public property_ `public DirectoryReference? RootDir { get; set; }` — attrs: `[CommandLine("-Root=")] [Description("Root directory for the workspace.")]`
- L21 _public property_ `public WorkspaceLayerId LayerId { get; set; }` — attrs: `[CommandLine("-Layer=")] [Description("Layer to add new files to")]`
- L25 _public property_ `public List<string> Paths { get; set; }` — attrs: `[CommandLine("-Path=", Positional = true)] [Description("List of files to reconcile")]`
- L27-45 _public method_ `public override async Task<int> ExecuteAsync(ILogger logger)`
- L47-71 _public method_ `public static FileFilter CreateFilter(DirectoryReference rootDir, List<string> paths)`

### `Source/Programs/Horde/HordeCmd/Commands/Workspace/WorkspaceVerify.cs` (HordeCmd)


#### class `Horde.Commands.Workspace.WorkspaceVerify`  
`class WorkspaceVerify : Command`  
_internal*; L13-39_
- attrs: `[Command("workspace", "verify", "Verify the integrity of the workspace")]`
- inherits: `Command`
- L17 _public property_ `public DirectoryReference? RootDir { get; set; }` — attrs: `[CommandLine("-Root=")] [Description("Root directory for the workspace.")]`
- L19-38 _public method_ `public override async Task<int> ExecuteAsync(ILogger logger)`
