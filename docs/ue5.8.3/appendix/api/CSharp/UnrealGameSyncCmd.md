# CSharp / UnrealGameSyncCmd

- project root: `Source/Programs/UnrealGameSync/UnrealGameSyncCmd`
- files: 35; symbols: 203
- symbol kinds: class=48, const=2, ctor=4, field=1, interface=1, method=70, property=77
- access marked `*` is implicit (not written in source)

### `Source/Programs/UnrealGameSync/UnrealGameSyncCmd/Command.cs` (UnrealGameSyncCmd)


#### interface `UnrealGameSyncCmd.ICommand`  
`internal interface ICommand`  
_internal; L8-11_

#### class `UnrealGameSyncCmd.Command`  
`internal abstract class Command : ICommand`  
_internal; L13-18_
- inherits: `ICommand`
- L15 _internal property_ `internal static BuildConfig EditorConfig => ...`
- L17 _public method_ `public abstract Task ExecuteAsync(CommandContext context)`

### `Source/Programs/UnrealGameSync/UnrealGameSyncCmd/CommandContext.cs` (UnrealGameSyncCmd)


#### class `UnrealGameSyncCmd.CommandContext`  
`internal class CommandContext : IDisposable`  
_internal; L18-161_
- inherits: `IDisposable`
- L20 _public property_ `public CommandLineArguments? Arguments { get; set; }`
- L22 _public property_ `public IServiceProvider ServiceProvider { get; set; }`
- L24 _public property_ `public ILogger? Logger { get; set; }`
- L26 _public property_ `public ILoggerFactory? LoggerFactory { get; set; }`
- L28 _public property_ `public UserSettings? GlobalSettings { get; set; }`
- L30 _public property_ `public GlobalSettingsFile? UserSettings { get; set; }`
- L32 _public property_ `public IHordeClient? HordeClient { get; set; }`
- L34 _public property_ `public ICloudStorage? CloudStorage { get; set; }`
- L36 _public property_ `public UserWorkspaceSettings? UserWorkspaceSettings { get; set; }`
- L38 _public property_ `public UserProjectSettings? UserProjectSettings { get; set; }`
- L40 _public property_ `public IPerforceConnection? PerforceClient { get; set; }`
- L42 _public property_ `public WorkspaceStateWrapper? WorkspaceState { get; set; }`
- L44 _public property_ `public ProjectInfo? ProjectInfo { get; set; }`
- L46 _public property_ `public ConfigFile? ProjectConfig { get; set; }`
- L48-51 _private ctor_ `private CommandContext(IServiceProvider serviceProvider)`
- L53-56 _public method_ `public void Dispose()`
- L58-160 _public method_ `public static async Task<CommandContext> CreateAsync( CommandLineArguments arguments, IServiceProvider serviceProvider, ILogger logger, ILoggerFactory loggerFactory, GlobalSettingsFile userSettings, UserSettings? globalSettings, IHordeClient? hordeClient, ICloudStorage? cloudStorage)`

### `Source/Programs/UnrealGameSync/UnrealGameSyncCmd/CommandInfo.cs` (UnrealGameSyncCmd)


#### class `UnrealGameSyncCmd.CommandInfo`  
`internal class CommandInfo`  
_internal; L7-23_
- L9 _public property_ `public string Name { get; }`
- L10 _public property_ `public Type Type { get; }`
- L11 _public property_ `public Type? OptionsType { get; }`
- L12 _public property_ `public string? Usage { get; }`
- L13 _public property_ `public string? Brief { get; }`
- L15-22 _public ctor_ `public CommandInfo(string name, Type type, Type? optionsType, string? usage, string? brief)`

### `Source/Programs/UnrealGameSync/UnrealGameSyncCmd/Commands/ArchiveCommand.cs` (UnrealGameSyncCmd)


#### class `UnrealGameSyncCmd.Commands.ArchiveCommandOptions`  
`internal class ArchiveCommandOptions`  
_internal; L17-39_
- L20 _public property_ `public bool List { get; set; }` — attrs: `[CommandLine("-List")]`
- L23 _public property_ `public bool Changes { get; set; }` — attrs: `[CommandLine("-Changes")]`
- L26 _public property_ `public bool Set { get; set; }` — attrs: `[CommandLine("-Set")]`
- L29 _public property_ `public bool Unset { get; set; }` — attrs: `[CommandLine("-Unset")]`
- L32 _public property_ `public string ArchiveType { get; set; }` — attrs: `[CommandLine("-ArchiveType")]`
- L35 _public property_ `public string ArchiveName { get; set; }` — attrs: `[CommandLine("-ArchiveName")]`
- L38 _public property_ `public List<string> ArchiveSources { get; set; }` — attrs: `[CommandLine("-ArchiveSources", ListSeparator = ';')]`

#### class `UnrealGameSyncCmd.Commands.ArchiveCommand`  
`class ArchiveCommand : Command`  
_internal*; L41-207_
- inherits: `Command`
- L43-142 _public method_ `public override async Task ExecuteAsync(CommandContext context)`
- L144-152 _private method_ `private static void ResetArchiveSettings(ILogger logger, UserSettings userSettings)`
- L154-176 _private method_ `private static List<IArchiveChannel> GetSelectedArchiveChannels(UserSettings userSettings, IReadOnlyList<IArchiveChannel> archives)`
- L178-198 _private method_ `private static void DisplayArchive(ILogger logger, List<IArchiveChannel> selected, BaseArchiveChannel archive)`
- L200-206 _private method_ `private static void DisplayChanges(ILogger logger, BaseArchiveChannel archive)`

### `Source/Programs/UnrealGameSync/UnrealGameSyncCmd/Commands/ArchiveOverrideCommand.cs` (UnrealGameSyncCmd)


#### class `UnrealGameSyncCmd.Commands.ArchiveOverrideCommandOptions`  
`internal class ArchiveOverrideCommandOptions`  
_internal; L15-37_
- L18 _public property_ `public bool List { get; set; }` — attrs: `[CommandLine("-List")]`
- L21 _public property_ `public bool Set { get; set; }` — attrs: `[CommandLine("-Set")]`
- L24 _public property_ `public bool Unset { get; set; }` — attrs: `[CommandLine("-Unset")]`
- L27 _public property_ `public bool SetCompileLocally { get; set; }` — attrs: `[CommandLine("-SetCompileLocally")]`
- L30 _public property_ `public string ArchiveType { get; set; }` — attrs: `[CommandLine("-ArchiveType")]`
- L33 _public property_ `public string ArchiveName { get; set; }` — attrs: `[CommandLine("-ArchiveName")]`
- L36 _public property_ `public List<string> ArchiveSources { get; set; }` — attrs: `[CommandLine("-ArchiveSources", ListSeparator = ';')]`

#### class `UnrealGameSyncCmd.Commands.ArchiveOverrideCommand`  
`internal class ArchiveOverrideCommand : Command`  
_internal; L39-190_
- inherits: `Command`
- L41-132 _public method_ `public override async Task ExecuteAsync(CommandContext context)`
- L134-143 _private method_ `private static void ResetArchiveSettings(ILogger logger, UserProjectSettings userSettings)`
- L145-167 _private method_ `private static List<IArchiveChannel> GetSelectedArchiveChannels(UserProjectSettings userSettings, IReadOnlyList<IArchiveChannel> archives)`
- L169-189 _private method_ `private static void DisplayArchive(ILogger logger, List<IArchiveChannel> selected, BaseArchiveChannel archive)`

### `Source/Programs/UnrealGameSync/UnrealGameSyncCmd/Commands/BuildCommand.cs` (UnrealGameSyncCmd)


#### class `UnrealGameSyncCmd.Commands.BuildCommandOptions`  
`internal class BuildCommandOptions`  
_internal; L20-24_
- L23 _public property_ `public bool ListOnly { get; set; }` — attrs: `[CommandLine("-List")]`

#### class `UnrealGameSyncCmd.Commands.BuildCommand`  
`internal class BuildCommand : Command`  
_internal; L26-199_
- inherits: `Command`
- L28-142 _public method_ `public override async Task ExecuteAsync(CommandContext context)`
- L144-180 _private method_ `private static async Task<ToolUpdateMonitor?> GetToolsMonitor(ILogger logger, CommandContext context, IPerforceConnection perforceClient)`
- L182-198 _private method_ `private static bool CanRunStep(BuildStep step, ToolUpdateMonitor toolsMonitor)`

### `Source/Programs/UnrealGameSync/UnrealGameSyncCmd/Commands/ChangesCommand.cs` (UnrealGameSyncCmd)


#### class `UnrealGameSyncCmd.Commands.ChangesCommandOptions`  
`internal class ChangesCommandOptions`  
_internal; L14-21_
- L17 _public property_ `public int Count { get; set; }` — attrs: `[CommandLine("-Count=")]`
- L20 _public property_ `public int LineCount { get; set; }` — attrs: `[CommandLine("-Lines=")]`

#### class `UnrealGameSyncCmd.Commands.ChangesCommand`  
`internal class ChangesCommand : Command`  
_internal; L23-86_
- inherits: `Command`
- L25-85 _public method_ `public override async Task ExecuteAsync(CommandContext context)`

### `Source/Programs/UnrealGameSync/UnrealGameSyncCmd/Commands/ClientsCommand.cs` (UnrealGameSyncCmd)


#### class `UnrealGameSyncCmd.Commands.ClientsCommandOptions`  
`internal class ClientsCommandOptions : ServerOptions`  
_internal; L14-16_
- inherits: `ServerOptions`

#### class `UnrealGameSyncCmd.Commands.ClientsCommand`  
`internal class ClientsCommand : ICommand`  
_internal; L18-38_
- inherits: `ICommand`
- L20-37 _public method_ `public static async Task ExecuteAsync(ILogger logger, CommandLineArguments args, ILoggerFactory loggerFactory)`

### `Source/Programs/UnrealGameSync/UnrealGameSyncCmd/Commands/ConfigCommand.cs` (UnrealGameSyncCmd)


#### class `UnrealGameSyncCmd.Commands.ConfigCommand`  
`internal class ConfigCommand : Command`  
_internal; L14-46_
- inherits: `Command`
- L16-45 _public method_ `public override async Task ExecuteAsync(CommandContext context)`

### `Source/Programs/UnrealGameSync/UnrealGameSyncCmd/Commands/FilterCommand.cs` (UnrealGameSyncCmd)


#### class `UnrealGameSyncCmd.Commands.FilterCommandOptions`  
`internal class FilterCommandOptions`  
_internal; L19-61_
- L22 _public property_ `public bool Reset { get; set; }` — attrs: `[CommandLine("-Reset")]`
- L26 _public property_ `public bool? SyncBaseContent { get; set; }` — attrs: `[CommandLine("-SetSyncBaseContent", Value = "true")] [CommandLine("-UnsetSyncBaseContent", Value = "false")]`
- L29 _public property_ `public List<string> Include { get; set; }` — attrs: `[CommandLine("-Include=")]`
- L32 _public property_ `public List<string> Exclude { get; set; }` — attrs: `[CommandLine("-Exclude=")]`
- L35 _public property_ `public List<string>? View { get; set; }` — attrs: `[CommandLine("-View=", ListSeparator = ';')]`
- L38 _public property_ `public List<string> AddView { get; set; }` — attrs: `[CommandLine("-AddView=", ListSeparator = ';')]`
- L41 _public property_ `public List<string> RemoveView { get; set; }` — attrs: `[CommandLine("-RemoveView=", ListSeparator = ';')]`
- L45 _public property_ `public bool? AllProjects { get; set; }` — attrs: `[CommandLine("-AllProjects", Value = "true")] [CommandLine("-OnlyCurrent", Value = "false")]`
- L49 _public property_ `public bool? LocalProjects { get; set; }` — attrs: `[CommandLine("-LocalProjects", Value = "true")] [CommandLine("-NoExtraLocalProjects", Value = "false")]`
- L53 _public property_ `public bool? AllProjectsInSln { get; set; }` — attrs: `[CommandLine("-GpfAllProjects", Value = "true")] [CommandLine("-GpfOnlyCurrent", Value = "false")]`
- L57 _public property_ `public bool? UprojectSpecificSln { get; set; }` — attrs: `[CommandLine("-GpfMinimalSln", Value = "true")] [CommandLine("-GpfFullSln", Value = "false")]`
- L60 _public property_ `public bool Global { get; set; }` — attrs: `[CommandLine("-Global")]`

#### class `UnrealGameSyncCmd.Commands.FilterCommand`  
`internal class FilterCommand : Command`  
_internal; L63-272_
- inherits: `Command`
- L65-68 _public method_ `public override async Task ExecuteAsync(CommandContext context)`
- L70-199 _private method_ `private static void ExecuteInternal(CommandContext context)`
- L200-254 _private method_ `private static void ApplyCommandOptions( ILogger logger, CommandContext context, FilterSettings settings, FilterCommandOptions commandOptions, IEnumerable<WorkspaceSyncCategory> syncCategories)`
- L256-271 _private method_ `private static Guid GetCategoryId(string text, IEnumerable<WorkspaceSyncCategory> syncCategories)`

### `Source/Programs/UnrealGameSync/UnrealGameSyncCmd/Commands/InitCommand.cs` (UnrealGameSyncCmd)


#### class `UnrealGameSyncCmd.Commands.InitCommand`  
`internal class InitCommand : ICommand`  
_internal; L23-313_
- inherits: `ICommand`
- L25-52 _public method_ `public static async Task ExecuteAsync(ILogger logger, CommandLineArguments args, ILoggerFactory loggerFactory, UserSettings? settings)`
- L54-149 _private method_ `private static async Task InitNewClientAsync(IPerforceConnection perforce, string streamName, string hostName, InitCommandOptions options, UserSettings? globalSettings, ILogger logger)`
- L151-161 _private method_ `private static DirectoryReference? TryParseRoot(string root)`
- L163-245 _private method_ `private static async Task InitExistingClientAsync(IPerforceConnection perforce, string hostName, InitCommandOptions options, UserSettings? globalSettings, ILogger logger)`
- L247-274 _private method_ `private static async Task<List<ClientsRecord>> FindExistingClients(IPerforceConnection perforce, string hostName, DirectoryReference clientDir)`
- L276-312 _private method_ `private static async Task ApplySettingsFromConfig(ILogger logger, IPerforceConnection clientPerforce, UserWorkspaceSettings settings)`

### `Source/Programs/UnrealGameSync/UnrealGameSyncCmd/Commands/InstallCommand.cs` (UnrealGameSyncCmd)


#### class `UnrealGameSyncCmd.Commands.InstallCommand`  
`internal class InstallCommand : Command`  
_internal; L8-14_
- inherits: `Command`
- L10-13 _public method_ `public override async Task ExecuteAsync(CommandContext context)`

### `Source/Programs/UnrealGameSync/UnrealGameSyncCmd/Commands/LoginCommand.cs` (UnrealGameSyncCmd)


#### class `UnrealGameSyncCmd.Commands.LoginCommand`  
`internal class LoginCommand : Command`  
_internal; L18-43_
- inherits: `Command`
- L20-42 _public method_ `public override async Task ExecuteAsync(CommandContext context)`

### `Source/Programs/UnrealGameSync/UnrealGameSyncCmd/Commands/RunCommand.cs` (UnrealGameSyncCmd)


#### class `UnrealGameSyncCmd.Commands.RunCommandOptions`  
`internal class RunCommandOptions`  
_internal; L17-21_
- L20 _public property_ `public bool UseEditorArgsFromSettings { get; set; }` — attrs: `[CommandLine("-UseEditorArgsFromSettings")]`

#### class `UnrealGameSyncCmd.Commands.RunCommand`  
`internal class RunCommand : Command`  
_internal; L23-139_
- inherits: `Command`
- L25-28 _public method_ `public override async Task ExecuteAsync(CommandContext context)`
- L30-85 _private method_ `private static void ExecuteInternal(CommandContext context)`
- L87-107 _private method_ `private static List<LockableEditorArgument> GetDefaultEditorArguments(CommandContext context)`
- L109-138 _private method_ `private static List<LockableEditorArgument> GetEditorArgumentsWithDefaults(CommandContext context)`

### `Source/Programs/UnrealGameSync/UnrealGameSyncCmd/Commands/SettingsCommand.cs` (UnrealGameSyncCmd)


#### class `UnrealGameSyncCmd.Commands.SettingsCommandOptions`  
`internal class SettingsCommandOptions`  
_internal; L18-25_
- L21 _public property_ `public string Global { get; set; }` — attrs: `[CommandLine("-Global=")]`
- L24 _public property_ `public string User { get; set; }` — attrs: `[CommandLine("-User=")]`

#### class `UnrealGameSyncCmd.Commands.SettingsCommand`  
`internal class SettingsCommand : ICommand`  
_internal; L27-96_
- inherits: `ICommand`
- L29-66 _public method_ `public static async Task ExecuteAsync(ILogger logger, ILoggerFactory loggerFactory, CommandLineArguments args, UserSettings? globalSettings, GlobalSettingsFile? userSettings)`
- L68-95 _private method_ `private static async Task WriteSettings(string path, object? settings)`

### `Source/Programs/UnrealGameSync/UnrealGameSyncCmd/Commands/StatusCommand.cs` (UnrealGameSyncCmd)


#### class `UnrealGameSyncCmd.Commands.StatusCommand`  
`internal class StatusCommand : Command`  
_internal; L15-56_
- inherits: `Command`
- L17-55 _public method_ `public override async Task ExecuteAsync(CommandContext context)`

### `Source/Programs/UnrealGameSync/UnrealGameSyncCmd/Commands/SwitchCommand.cs` (UnrealGameSyncCmd)


#### class `UnrealGameSyncCmd.Commands.SwitchCommandOptions`  
`internal class SwitchCommandOptions`  
_internal; L17-21_
- L20 _public property_ `public bool Force { get; set; }` — attrs: `[CommandLine("-Force")]`

#### class `UnrealGameSyncCmd.Commands.SwitchCommand`  
`internal class SwitchCommand : Command`  
_internal; L23-73_
- inherits: `Command`
- L25-53 _public method_ `public override async Task ExecuteAsync(CommandContext context)`
- L55-65 _private method_ `private static async Task SwitchStreamAsync(IPerforceConnection perforceClient, string streamName, bool force, ILogger logger)`
- L67-72 _private method_ `private static async Task SwitchProjectAsync(IPerforceConnection perforceClient, UserWorkspaceSettings settings, string projectName, ILogger logger)`

### `Source/Programs/UnrealGameSync/UnrealGameSyncCmd/Commands/SyncCommand.cs` (UnrealGameSyncCmd)


#### class `UnrealGameSyncCmd.Commands.SyncCommandOptions`  
`internal class SyncCommandOptions`  
_internal; L20-46_
- L23 _public property_ `public bool Clean { get; set; }` — attrs: `[CommandLine("-Clean")]`
- L26 _public property_ `public bool Build { get; set; }` — attrs: `[CommandLine("-Build")]`
- L29 _public property_ `public bool Binaries { get; set; }` — attrs: `[CommandLine("-Binaries")]`
- L33 _public property_ `public bool ProjectFiles { get; set; }` — attrs: `[CommandLine("-NoGPF", Value = "false")] [CommandLine("-NoProjectFiles", Value = "false")]`
- L36 _public property_ `public bool Clobber { get; set; }` — attrs: `[CommandLine("-Clobber")]`
- L39 _public property_ `public bool Refilter { get; set; }` — attrs: `[CommandLine("-Refilter")]`
- L42 _public property_ `public bool SingleChange { get; set; }` — attrs: `[CommandLine("-Only")]`
- L45 _public property_ `public List<string> ArchiveSources { get; set; }` — attrs: `[CommandLine("-ArchiveSources", ListSeparator = ';')]`

#### class `UnrealGameSyncCmd.Commands.SyncCommand`  
`internal class SyncCommand : Command`  
_internal; L48-241_
- inherits: `Command`
- L50-54 _private method_ `private static async Task<bool> IsCodeChangeAsync(IPerforceConnection perforce, int change)`
- L56-66 _private method_ `private static bool IsCodeChange(DescribeRecord describeRecord)`
- L68-228 _public method_ `public override async Task ExecuteAsync(CommandContext context)`
- L230-240 _private* method_ `static WorkspaceLock? CreateWorkspaceLock(DirectoryReference rootDir)`

### `Source/Programs/UnrealGameSync/UnrealGameSyncCmd/Commands/ToolsCommand.cs` (UnrealGameSyncCmd)


#### class `UnrealGameSyncCmd.Commands.ToolsCommandCommandOptions`  
`internal class ToolsCommandCommandOptions`  
_internal; L20-33_
- L23 _public property_ `public List<string> Install { get; set; }` — attrs: `[CommandLine("-Install=", ListSeparator = ',')]`
- L26 _public property_ `public List<string> Uninstall { get; set; }` — attrs: `[CommandLine("-Uninstall=", ListSeparator = ',')]`
- L29 _public property_ `public bool List { get; set; }` — attrs: `[CommandLine("-List")]`
- L32 _public property_ `public bool Update { get; set; }` — attrs: `[CommandLine("-Update")]`

#### class `UnrealGameSyncCmd.Commands.ToolsCommand`  
`internal class ToolsCommand : ICommand`  
_internal; L35-185_
- inherits: `ICommand`
- L37-184 _public method_ `public static async Task ExecuteAsync(ILogger logger, CommandLineArguments args, UserSettings? globalSettings)`

### `Source/Programs/UnrealGameSync/UnrealGameSyncCmd/Commands/UninstallCommand.cs` (UnrealGameSyncCmd)


#### class `UnrealGameSyncCmd.Commands.UninstallCommand`  
`internal class UninstallCommand : Command`  
_internal; L8-14_
- inherits: `Command`
- L10-13 _public method_ `public override async Task ExecuteAsync(CommandContext context)`

### `Source/Programs/UnrealGameSync/UnrealGameSyncCmd/Commands/UpgradeCommand.cs` (UnrealGameSyncCmd)


#### class `UnrealGameSyncCmd.Commands.UpgradeCommandOptions`  
`internal class UpgradeCommandOptions`  
_internal; L19-26_
- L22 _public property_ `public bool Check { get; set; }` — attrs: `[CommandLine("-Check")]`
- L25 _public property_ `public bool Force { get; set; }` — attrs: `[CommandLine("-Force")]`

#### class `UnrealGameSyncCmd.Commands.UpgradeCommand`  
`internal class UpgradeCommand : ICommand`  
_internal; L28-90_
- inherits: `ICommand`
- L30-89 _public method_ `public static async Task ExecuteAsync(ILogger logger, CommandLineArguments args)`

### `Source/Programs/UnrealGameSync/UnrealGameSyncCmd/Commands/VersionCommand.cs` (UnrealGameSyncCmd)


#### class `UnrealGameSyncCmd.Commands.VersionCommand`  
`internal class VersionCommand : ICommand`  
_internal; L8-16_
- inherits: `ICommand`
- L10-15 _public method_ `public static void Execute(ILogger logger)`

### `Source/Programs/UnrealGameSync/UnrealGameSyncCmd/CommandsFactory.cs` (UnrealGameSyncCmd)


#### class `UnrealGameSyncCmd.CommandsFactory`  
`internal static class CommandsFactory`  
_internal; L13-118_
- L15-27 _internal method_ `internal static CommandInfo[] GetCommands()`
- L29-98 _private method_ `private static List<CommandInfo> PortableCommands()`
- L100-117 _private method_ `private static List<CommandInfo> GetWinCommand()`

### `Source/Programs/UnrealGameSync/UnrealGameSyncCmd/Exceptions/UserErrorException.cs` (UnrealGameSyncCmd)


#### class `UnrealGameSyncCmd.Exceptions.UserErrorException`  
`public sealed class UserErrorException : Exception`  
_public; L9-25_
- inherits: `Exception`
- L11 _public property_ `public LogEvent Event { get; }`
- L12 _public property_ `public int Code { get; }`
- L14-19 _public ctor_ `public UserErrorException(LogEvent evt) : base(evt.ToString())`
- L21-24 _public ctor_ `public UserErrorException(string message, params object[] args) : this(LogEvent.Create(LogLevel.Error, message, args))`

### `Source/Programs/UnrealGameSync/UnrealGameSyncCmd/Options/ConfigCommandOptions.cs` (UnrealGameSyncCmd)


#### class `UnrealGameSyncCmd.Options.ConfigCommandOptions`  
`internal class ConfigCommandOptions : ServerOptions`  
_internal; L7-20_
- inherits: `ServerOptions`
- L9-19 _public method_ `public void ApplyTo(UserWorkspaceSettings settings)`

### `Source/Programs/UnrealGameSync/UnrealGameSyncCmd/Options/InitCommandOptions.cs` (UnrealGameSyncCmd)


#### class `UnrealGameSyncCmd.Options.InitCommandOptions`  
`internal class InitCommandOptions : ConfigCommandOptions`  
_internal; L7-23_
- inherits: `ConfigCommandOptions`
- L10 _public property_ `public string? ClientName { get; set; }` — attrs: `[CommandLine("-Client=")]`
- L13 _public property_ `public string? BranchPath { get; set; }` — attrs: `[CommandLine("-Branch=")]`
- L16 _public property_ `public string? ProjectName { get; set; }` — attrs: `[CommandLine("-Project=")]`
- L19 _public property_ `public string? ClientRoot { get; set; }` — attrs: `[CommandLine("-ClientRoot=")]`
- L22 _public property_ `public bool IgnoreExistingClients { get; set; }` — attrs: `[CommandLine("-IgnoreExistingClients")]`

### `Source/Programs/UnrealGameSync/UnrealGameSyncCmd/Options/ServerOptions.cs` (UnrealGameSyncCmd)


#### class `UnrealGameSyncCmd.Options.ServerOptions`  
`internal class ServerOptions`  
_internal; L7-14_
- L10 _public property_ `public string? ServerAndPort { get; set; }` — attrs: `[CommandLine("-Server=")]`
- L13 _public property_ `public string? UserName { get; set; }` — attrs: `[CommandLine("-User=")]`

### `Source/Programs/UnrealGameSync/UnrealGameSyncCmd/Program.cs` (UnrealGameSyncCmd)


#### class `UnrealGameSyncCmd.Program`  
`public static class Program`  
_public; L31-299_
- L33 _private* field_ `static readonly CommandInfo[] _commands = CommandsFactory.GetCommands()`
- L35-240 _public method_ `public static async Task<int> Main(string[] rawArgs)`
- L242-245 _private method_ `private static bool IsUpgradeAvailable(GlobalSettingsFile settings, string version)`
- L247-269 _private method_ `private static void PrintHelp()`
- L271-298 _private method_ `private static string GetUsage(CommandInfo commandInfo)`

### `Source/Programs/UnrealGameSync/UnrealGameSyncCmd/Utils/InstallUtils.cs` (UnrealGameSyncCmd)


#### class `UnrealGameSyncCmd.Utils.InstallUtils`  
`internal static class InstallUtils`  
_internal; L16-151_
- L18-78 _internal method_ `internal static async Task UpdateInstallAsync(bool install, ILogger logger)`
- L80-91 _internal method_ `internal static DirectoryReference? GetInstallFolder()`
- L93-125 _internal method_ `internal static void UpdateInstalledFiles(bool install, DirectoryReference installDir, ILogger logger)`
- L127-150 _internal method_ `internal static async Task UpdateAliasAsync(FileReference configFile, bool install, DirectoryReference installDir, ILogger logger)`

### `Source/Programs/UnrealGameSync/UnrealGameSyncCmd/Utils/PerforceConnectionUtils.cs` (UnrealGameSyncCmd)


#### class `UnrealGameSyncCmd.Utils.PerforceConnectionUtils`  
`public static class PerforceConnectionUtils`  
_public; L12-35_
- L14-29 _public method_ `public static Task<IPerforceConnection> ConnectAsync(string? serverAndPort, string? userName, string? clientName, ILoggerFactory loggerFactory)`
- L31-34 _public method_ `public static Task<IPerforceConnection> ConnectAsync(UserWorkspaceSettings settings, ILoggerFactory loggerFactory)`

### `Source/Programs/UnrealGameSync/UnrealGameSyncCmd/Utils/ProjectUtils.cs` (UnrealGameSyncCmd)


#### class `UnrealGameSyncCmd.Utils.ProjectUtils`  
`internal static class ProjectUtils`  
_internal; L13-53_
- L15 _internal const_ `internal const string UProjectExtension = ".uproject"`
- L16 _internal const_ `internal const string UProjectDirsExtension = ".uprojectdirs"`
- L18-52 _internal method_ `internal static async Task<string> FindProjectPathAsync(IPerforceConnection perforce, string clientName, string branchPath, string? projectName)`

### `Source/Programs/UnrealGameSync/UnrealGameSyncCmd/Utils/SyncFilterUtils.cs` (UnrealGameSyncCmd)


#### class `UnrealGameSyncCmd.Utils.SyncFilterUtils`  
`internal static class SyncFilterUtils`  
_internal; L9-39_
- L11-38 _internal method_ `internal static string[] ReadSyncFilter( UserWorkspaceSettings workspaceSettings, UserProjectSettings contextUserProjectSettings, GlobalSettingsFile userSettings, ConfigFile projectConfig, string projectIdentifier)`

### `Source/Programs/UnrealGameSync/UnrealGameSyncCmd/Utils/UserSettingsUtils.cs` (UnrealGameSyncCmd)


#### class `UnrealGameSyncCmd.Utils.UserSettingsUtils`  
`public static class UserSettingsUtils`  
_public; L8-40_
- L10-29 _public method_ `public static UserWorkspaceSettings? ReadOptionalUserWorkspaceSettings()`
- L31-39 _public method_ `public static UserWorkspaceSettings ReadRequiredUserWorkspaceSettings()`

### `Source/Programs/UnrealGameSync/UnrealGameSyncCmd/Utils/VersionUtils.cs` (UnrealGameSyncCmd)


#### class `UnrealGameSyncCmd.Utils.DeploymentInfo`  
`public class DeploymentInfo`  
_public; L16-19_
- L18 _public property_ `public string Version { get; set; }`

#### class `UnrealGameSyncCmd.Utils.VersionUtils`  
`public static class VersionUtils`  
_public; L21-90_
- L23-27 _public method_ `public static string GetVersion()`
- L29-66 _public method_ `public static async Task<string?> GetLatestVersionAsync(ILogger? logger, CancellationToken cancellationToken)`
- L68-89 _public method_ `public static string? GetUpgradeToolName()`

### `Source/Programs/UnrealGameSync/UnrealGameSyncCmd/Utils/WorkspaceStateUtils.cs` (UnrealGameSyncCmd)


#### class `UnrealGameSyncCmd.Utils.WorkspaceStateUtils`  
`internal static class WorkspaceStateUtils`  
_internal; L12-25_
- L14-24 _public method_ `public static async Task<WorkspaceStateWrapper> ReadWorkspaceState(IPerforceConnection perforceClient, UserWorkspaceSettings settings, GlobalSettingsFile userSettings, ILogger logger)`
