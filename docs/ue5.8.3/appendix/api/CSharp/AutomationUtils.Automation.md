# CSharp / AutomationUtils.Automation

- project root: `Source/Programs/AutomationTool/AutomationUtils`
- files: 54; symbols: 2828
- symbol kinds: class=173, const=26, ctor=98, delegate=4, dtor=2, enum=36, enumerator=259, field=772, interface=6, method=1033, operator=8, property=404, struct=7
- access marked `*` is implicit (not written in source)

### `Source/Programs/AutomationTool/AutomationUtils/Automation.cs` (AutomationUtils.Automation)


#### class `AutomationTool.Automation`  
`public static class Automation`  
_public; L26-441_
- L28 _private* property_ `static ILogger Logger => ...`
- L33 _private* field_ `static ProcessManager.CtrlHandlerDelegate CtrlHandlerDelegateInstance = CtrlHandler` — Keep a persistent reference to the delegate for handling Ctrl-C events. Since it's passed to non-managed code, we have to prevent it from being garbage collected.
- L35-44 _private* method_ `static bool CtrlHandler(CtrlTypes EventType)`
- L46-54 _private* method_ `static void Domain_ProcessExit(object sender, EventArgs e)`
- L61-238 _public method_ `public static async Task<ExitCode> ProcessAsync(ParsedCommandLine AutomationToolCommandLine, HashSet<FileReference> ScriptModuleAssemblies)` — Main method.
- L247-257 _private method_ `private static void NoThrow(System.Action Action, string ActionDesc)` — Wraps an action in an exception block. Ensures individual actions can be performed and exceptions won't prevent further actions from being executed. Useful for shutdown code where shutdown may be in several stages and it's important that all stages get a chance to run.
- L264-344 _public method_ `public static async Task<ExitCode> ExecuteAsync(List<CommandInfo> CommandsToExecute, Dictionary<string, Type> Commands)` — Execute commands specified in the command line.
- L351-366 _private method_ `private static void DisplayHelp(List<CommandInfo> CommandsToExecute, Dictionary<string, Type> Commands)` — Display help for the specified commands (to execute)
- L371-379 _private method_ `private static void DisplayHelp(Dictionary<string, string> ParamDict)` — Display AutomationTool help.
- L385-403 _private method_ `private static void ListAvailableCommands(Dictionary<string, Type> Commands)` — List all available commands.
- L412-426 _public property_ `public static bool IsBuildMachine { get; set; }` — True if this process is running on a build machine, false if locally.
- L427 _private field_ `private static bool? bIsBuildMachine`
- L429-439 _public property_ `public static bool ShouldKillProcesses { get; set; }`
- L440 _private field_ `private static bool bShouldKillProcesses = true`

#### class `AutomationTool.BuildCommandContainer`  
`public class BuildCommandContainer`  
_public; L443-446_
- L445 _public property_ `public BuildCommand CurrentCommand { get; set; }`

#### class `AutomationTool.GlobalCommandLine`  
`public class GlobalCommandLine`  
_public; L450-592_
- L454-477 _public method_ `public static void Initialize(ParsedCommandLine AutomationToolCommandLine)`
- L483 _private field_ `private static bool? bBuildMachine`
- L484-488 _public property_ `public static bool BuildMachine { get; set; }`
- L490 _private field_ `private static bool? bNoKill`
- L491-495 _public property_ `public static bool NoKill { get; set; }`
- L497 _private field_ `private static bool? bHelp`
- L498-502 _public property_ `public static bool Help { get; set; }`
- L504 _private field_ `private static bool? bNoAutoSDK`
- L505-509 _public property_ `public static bool NoAutoSDK { get; set; }`
- L511 _private field_ `private static bool? bList`
- L512-516 _public property_ `public static bool List { get; set; }`
- L518 _private field_ `private static bool? bCompileOnly`
- L519-523 _public property_ `public static bool CompileOnly { get; set; }`
- L525 _private field_ `private static bool? bVerbose`
- L526-530 _public property_ `public static bool Verbose { get; set; }`
- L532 _private field_ `private static bool? bAllowStdOutLogVerbosity`
- L533-537 _public property_ `public static bool AllowStdOutLogVerbosity { get; set; }`
- L539 _private field_ `private static bool? bUTF8Output`
- L540-544 _public property_ `public static bool UTF8Output { get; set; }`
- L546 _private field_ `private static bool? bUseLocalBuildStorage`
- L547-551 _public property_ `public static bool UseLocalBuildStorage { get; set; }`
- L553 _private field_ `private static bool? bSubmit`
- L554-558 _public property_ `public static bool Submit { get; set; }`
- L560 _private field_ `private static bool? bNoSubmit`
- L561-565 _public property_ `public static bool NoSubmit { get; set; }`
- L567 _private field_ `private static bool? bP4`
- L568-572 _public property_ `public static bool P4 { get; set; }`
- L574 _private field_ `private static bool? bNoP4`
- L575-579 _public property_ `public static bool NoP4 { get; set; }`
- L581-585 _public property_ `public static string TelemetryPath { get; set; }`
- L587-591 _public property_ `public static int WaitForStdStreams { get; set; }`

### `Source/Programs/AutomationTool/AutomationUtils/AutomationException.cs` (AutomationUtils.Automation)


#### enum `AutomationTool.AutomationExceptionOutputFormat`  
`public enum AutomationExceptionOutputFormat`  
_public; L13-34_
- desc: How the exception should be output
- L18 _public* enumerator_ `Silent` — Do not output any message; just output the exception details to the log.
- L23 _public* enumerator_ `Minimal` — Output a brief summary to the console, and the exception details to the log
- L28 _public* enumerator_ `MinimalError` — Output a brief summary to the console as an error, and the exception details to the log
- L33 _public* enumerator_ `Error` — Treat the exception as an error

#### class `AutomationTool.AutomationException`  
`public class AutomationException : System.Exception`  
_public; L40-82_
- inherits: `System.Exception`
- desc: Exception class used by the AutomationTool to throw exceptions. Allows setting an exit code that will be passed to the entry routine to return to the system on program exit. If no exit code is given, Error_Unkonwn is used.
- L42 _public field_ `public ExitCode ErrorCode = ExitCode.Error_Unknown`
- L43 _public field_ `public AutomationExceptionOutputFormat OutputFormat = AutomationExceptionOutputFormat.Error`
- L45-48 _public ctor_ `public AutomationException(string Msg) :base(Msg)`
- L50-54 _public ctor_ `public AutomationException(ExitCode ErrorCode, string Msg) : base(Msg)`
- L56-59 _public ctor_ `public AutomationException(Exception InnerException, string Format, params object[] Args) : base(string.Format(Format, Args), InnerException)`
- L61-65 _public ctor_ `public AutomationException(ExitCode ErrorCode, Exception InnerException, string Format, params object[] Args) : base(string.Format(Format, Args), InnerException)`
- L67-70 _public ctor_ `public AutomationException(string Format, params object[] Args) : base(string.Format(Format, Args))`
- L72-76 _public ctor_ `public AutomationException(ExitCode ErrorCode, string Format, params object[] Args) : base(string.Format(Format, Args))`
- L78-81 _public method_ `public override string ToString()`

### `Source/Programs/AutomationTool/AutomationUtils/BuildCommand.cs` (AutomationUtils.Automation)


#### class `AutomationTool.BuildCommand`  
`public abstract class BuildCommand : CommandUtils`  
_public; L19-448_
- inherits: `CommandUtils`
- desc: Base class for buildcommands.
- L24-28 _public property_ `public string[] Params { get; set; }` — Command line parameters for this command (empty by non-null by default)
- L30 _private field_ `private string[] _commandLineParams = new string[0]`
- L37-40 _public method_ `public bool ParseParam(string Param)` — Parses the command's Params list for a parameter and returns whether it is defined or not.
- L51-74 _public method_ `public string? ParseParamValue(string Param, string? Default = null, string? ObsoleteParam = null)` — attrs: `[return: NotNullIfNotNull("Default")]` — Parses the command's Params list for a parameter and reads its value. Ex. ParseParamValue(Args, "map=")
- L84-87 _public method_ `public string? ParseSetPropertyValue(string propertyName, string? Default = null)` — attrs: `[return: NotNullIfNotNull("Default")]` — Parses the command's Params list for a property set in the format set:<Param>=<Value> and reads its value. Ex. ParseSetPropertyValue("projectName", "") will return "Lyra" for commandline "BuildGraph -set:ProjectName=Lyra"
- L94-97 _public method_ `public string? ParseOptionalStringParam(string Param)` — Parses an argument.
- L104-112 _public method_ `public string ParseRequiredStringParam(string Param)` — Parses an argument. Throws an exception if the parameter is not specified.
- L119-130 _public method_ `public FileReference? ParseOptionalFileReferenceParam(string Param)` — Parses an file reference argument.
- L137-145 _public method_ `public FileReference ParseRequiredFileReferenceParam(string Param)` — Parses an file reference argument. Throws an exception if the parameter is not specified.
- L152-163 _public method_ `public DirectoryReference? ParseOptionalDirectoryReferenceParam(string Param)` — Parses a directory reference argument.
- L170-178 _public method_ `public DirectoryReference ParseRequiredDirectoryReferenceParam(string Param)` — Parses a directory reference argument. Throws an exception if the parameter is not specified.
- L185-201 _public method_ `public Nullable<T> ParseOptionalEnumParam<T>(string Param) where T : struct` — Parses an argument as an enum.
- L208-216 _public method_ `public T ParseRequiredEnumParamEnum<T>(string Param) where T : struct` — Parses an argument as an enum. Throws an exception if the parameter is not specified.
- L223-226 _public method_ `public string[] ParseParamValues(string Param)` — Parses the argument list for any number of parameters.
- L235-239 _public method_ `public bool ParseParamBool(string Param, bool Default = false)` — Parses the command's Params list for a parameter and reads its value. Ex. ParseParamValue(Args, "map=")
- L248-252 _public method_ `public int ParseParamInt(string Param, int Default = 0)` — Parses the command's Params list for a parameter and reads its value. Ex. ParseParamValue(Args, "map=")
- L260-271 _public method_ `public int? ParseParamNullableInt(string Param)` — Parses the command's Params list for a parameter and reads its value. Ex. ParseParamValue(Args, "map=")
- L277-311 _public method_ `public FileReference? ParseProjectString(string originalProjectName)` — Parses project name string into a FileReference. Can be "Game" or "Game.uproject" or "Path/To/Game.uproject"
- L317-353 _public method_ `public FileReference? ParseProjectParam()` — Attempts to parse the project param. Returns null if no project is found, and throws if the specified project does not exist on disk.
- L360-386 _public method_ `public void ParseProjectIdParams(out FileReference? projectFile, out string? projectName, out DirectoryReference? projectDir)` — Searches for project's .uproject filepath, user-friendly name, and directory of .uproject filepath, from commandline arguments (including -project= and -set:Project???= parameters). Caller should handle possiblity that some fields are valid and others are null.
- L392-407 _public method_ `public void CheckParamsArePresent(params string[] args)` — Checks that all of the required params are present, throws an exception if not
- L412-415 _public method_ `public virtual void ExecuteBuild()` — Build command entry point. Throws AutomationExceptions on failure.
- L420-424 _public method_ `public virtual ExitCode Execute()` — Command entry point.
- L429-432 _public method_ `public virtual Task<ExitCode> ExecuteAsync()` — Async command entry point.
- L439-447 _public method_ `public static ExitCode Execute<T>(BuildCommand ParentCommand) where T : BuildCommand, new()` — Executes a new command as a child of another command.

### `Source/Programs/AutomationTool/AutomationUtils/BuildUtils.cs` (AutomationUtils.Automation)


#### class `AutomationTool.CommandUtils`  
`public partial class CommandUtils`  
_public; L12-145_
- L22-39 _public method_ `public static void MsBuild(CommandEnvironment Env, string Project, string Arguments, string LogName)` — Runs msbuild.exe with the specified arguments. Automatically creates a logfile. When no LogName is specified, the executable name is used as logfile base name.
- L50-68 _public method_ `public static void BuildSolution(CommandEnvironment Env, string SolutionFile, string BuildConfig, string BuildPlatform, string LogName = null)` — Builds a Visual Studio solution with MsBuild (using msbuild.exe rather than devenv.com can help circumvent issues with expired Visual Studio licenses). Automatically creates a logfile. When no LogName is specified, the executable name is used as logfile base name.
- L78-91 _public method_ `public static void BuildCSharpProject(CommandEnvironment Env, string ProjectFile, string BuildConfig = "Development", string LogName = null)` — Builds a CSharp project with msbuild.exe. Automatically creates a logfile. When no LogName is specified, the executable name is used as logfile base name.
- L98-107 _public method_ `public static bool IsProbablyALinuxExe(string Filename)` — returns true if this is a linux executable using some awful conventions Filename
- L113-124 _public method_ `public static bool IsProbablyAMacOrIOSExe(string Filename)` — returns true if this is a mac executable using some awful conventions Filename
- L130-144 _public method_ `public static void FixUnixFilePermissions(string Filename)` — Sets an executable bit for Unix executables and adds read permission for all users plus write permission for owner. Filename

### `Source/Programs/AutomationTool/AutomationUtils/BundleUtils.cs` (AutomationUtils.Automation)


#### class `AutomationUtils.Automation.BundleUtils`  
`public class BundleUtils`  
_public; L19-553_
- L46-50 _public method_ `public static ConfigHierarchy LoadConfigHierarchy(DirectoryReference ProjectDir, UnrealTargetPlatform Platform, string CustomConfig)`
- L52-55 _public method_ `public static void LoadBundleConfig(ConfigHierarchy BundleConfig, out IReadOnlyDictionary<string, BundleSettings> Bundles)`
- L57-60 _public method_ `public static void LoadBundleConfig(DirectoryReference ProjectDir, UnrealTargetPlatform Platform, string CustomConfig, out IReadOnlyDictionary<string, BundleSettings> Bundles)`
- L62-262 _public method_ `public static void LoadBundleConfig<TPlatformBundleSettings>(ConfigHierarchy BundleConfig, out IReadOnlyDictionary<string, TPlatformBundleSettings> Bundles, Action<TPlatformBundleSettings, ConfigHierarchy, string> GetPlatformSettings) where TPlatformBundleSettings : BundleSettings, new()`
- L264-271 _public method_ `public static void LoadBundleConfig<TPlatformBundleSettings>(DirectoryReference ProjectDir, UnrealTargetPlatform Platform, string CustomConfig, out IReadOnlyDictionary<string, TPlatformBundleSettings> Bundles, Action<TPlatformBundleSettings, ConfigHierarchy, string> GetPlatformSettings) where TPlatformBundleSettings : BundleSettings, new()`
- L273-316 _public method_ `public static void LoadBundleSubsetConfig(ConfigHierarchy BundleConfig, out IReadOnlyDictionary<string, BundleSubsetSettings> BundlesSubsets)`
- L318-323 _public method_ `public static void LoadBundleSubsetConfig(DirectoryReference ProjectDir, UnrealTargetPlatform Platform, string CustomConfig, out IReadOnlyDictionary<string, BundleSubsetSettings> BundlesSubsets)`
- L325-348 _public method_ `public static TPlatformBundleSettings MatchBundleSettings<TPlatformBundleSettings>( string FileName, IReadOnlyDictionary<string, TPlatformBundleSettings> InstallBundles) where TPlatformBundleSettings : BundleSettings`
- L350-372 _public method_ `public static IList<BundleSubsetSettings> MatchBundleSubsetSettings(BundleSettings Bundle, string FileName, IReadOnlyDictionary<string, BundleSubsetSettings> InstallBundleSubsets)`
- L374-383 _public method_ `public static IEnumerable<string> GetCloudAppsForBundles<TPlatformBundleSettings>(IReadOnlyDictionary<string, TPlatformBundleSettings> InstallBundles) where TPlatformBundleSettings : BundleSettings`
- L385-415 _public method_ `public static IEnumerable<TPlatformBundleSettings> GetBundleDependencies<TPlatformBundleSettings>( TPlatformBundleSettings Bundle, IReadOnlyDictionary<string, TPlatformBundleSettings> InstallBundles) where TPlatformBundleSettings : BundleSettings`
- L417-423 _public method_ `public static bool HasPlatformBundleSource(DirectoryReference ProjectDir, UnrealTargetPlatform Platform, string CustomConfig)`
- L425-442 _public method_ `public static bool HasPlatformDLCBundleSource(DirectoryReference ProjectDir, UnrealTargetPlatform Platform, string CustomConfig)`
- L446-466 _public method_ `public static List<string> InferVirtualBundleTagsFromManifest(BuildPatchToolBase.ManifestMetadataOutput ManifestContents)`
- L469-486 _public method_ `public static List<string> InferVirtualBundleTagsFromManifest(string ManifestPath, BuildPatchToolBase.ToolVersion BPTVersion = BuildPatchToolBase.ToolVersion.Live)`
- L488-505 _public method_ `public static List<string> InferNonVirtualBundleTagsFromManifest(BuildPatchToolBase.ManifestMetadataOutput ManifestContents)`
- L508-522 _public method_ `public static List<string> InferNonVirtualBundleTagsFromManifest(string ManifestPath, BuildPatchToolBase.ToolVersion BPTVersion = BuildPatchToolBase.ToolVersion.Live)`
- L524-552 _public method_ `public static HashSet<string> InferVirtualBundleChildTagsFromManifest(string VirtualBundleTag, BuildPatchToolBase.ManifestMetadataOutput ManifestContents)`

#### class `AutomationUtils.Automation.BundleUtils.BundleSettings`  
`public class BundleSettings`  
_public; L21-37_
- L23 _public property_ `public string Name { get; set; }`
- L24 _public property_ `public List<string> Tags { get; set; }`
- L25 _public property_ `public List<string> Dependencies { get; set; }`
- L26 _public property_ `public List<string> FileRegex { get; set; }`
- L27 _public property_ `public List<string> Files { get; set; }`
- L28 _public property_ `public List<string> Subsets { get; set; }`
- L29 _public property_ `public bool bContainsShaderLibrary { get; set; }`
- L30 _public property_ `public int Order { get; set; }`
- L31 _public property_ `public bool UseChunkDBs { get; set; }`
- L32 _public property_ `public bool UseDetailedInstallSizes { get; set; }`
- L33 _public property_ `public string ExecFileName { get; set; }`
- L34 _public property_ `public string CloudAppNameOverride { get; set; }`
- L35 _public property_ `public List<string> VirtualBundleChildren { get; set; }`
- L36 _public property_ `public List<string> VirtualBundleParents { get; set; }`

#### class `AutomationUtils.Automation.BundleUtils.BundleSubsetSettings`  
`public class BundleSubsetSettings`  
_public; L39-44_
- L41 _public property_ `public string Name { get; set; }`
- L42 _public property_ `public List<string> Tags { get; set; }`
- L43 _public property_ `public List<string> FileRegex { get; set; }`

### `Source/Programs/AutomationTool/AutomationUtils/CloudAppDependencyTree.cs` (AutomationUtils.Automation)


#### class `AutomationUtils.CloudAppDependencyTree`  
`public class CloudAppDependencyTree`  
_public; L11-292_
- L42 _private field_ `private Dictionary<string, string> Aliases`
- L42 _private field_ `private Dictionary< Aliases`
- L44 _private field_ `private Dictionary<string, Entry> Entries`
- L44 _private field_ `private Dictionary< Entries`
- L46-50 _public ctor_ `public CloudAppDependencyTree()`
- L52-55 _public method_ `public IEnumerable<string> GetAliases()`
- L57-83 _public method_ `public void AddEntry(string CloudAppName, string ArtifactId, string Namespace, string CatalogItemId, List<string> Dependencies)`
- L93-135 _public method_ `public void UpdateCloudAppIdValues(string CloudAppName, string NewArtifactId, string NewNamespace, string NewCatalogId)` — Updates the ID values associated the provided cloud app.
- L137-140 _private method_ `private static string SanitizeCloudAppName(string CloudAppName, string BaseAppName)`
- L149-200 _public method_ `public static CloudAppDependencyTree CreateTemplateFromBundleConfig(string BaseAppName, IReadOnlyDictionary<string, BundleUtils.BundleSettings> Bundles)` — Creates a dependency tree containing placeholder values for the artifact ID, catalog ID, and namespace on each entry. For production use please update the values of the generated tree for each cloud app by using the UpdateCloudAppIdValues function.
- L202-218 _public method_ `public JsonObject ToJson()`
- L220-270 _public method_ `public bool FromJson(JsonObject Json)`
- L272-275 _public method_ `public override string ToString()`
- L277-291 _public method_ `public static bool TryParse(string JsonText, out CloudAppDependencyTree Tree)`

#### class `AutomationUtils.CloudAppDependencyTree.Entry`  
`private class Entry`  
_private; L15-39_
- L18 _public field_ `public string Namespace = ""`
- L20 _public field_ `public string CatalogItemId = ""`
- L22 _public field_ `public HashSet<string> Dependencies = new()`
- L24-31 _public method_ `public JsonObject ToJson()`
- L33-38 _public method_ `public void FromJson(JsonObject Json)`

### `Source/Programs/AutomationTool/AutomationUtils/CloudStorageUtils.cs` (AutomationUtils.Automation)


#### class `AutomationUtils.CloudStorageOptionsExtensions`  
`public static class CloudStorageOptionsExtensions`  
_public; L14-97_
- L20-52 _public method_ `public static void ReadFromIni(this CloudStorageOptions options, [CanBeNull] FileReference projectPath)` — Attempt to initialize options from inis
- L57-85 _public method_ `public static void ReadFromEnv(this CloudStorageOptions options)` — Attempt to initialize options from environment variables

#### struct `AutomationUtils.CloudStorageOptionsExtensions.IniCloudConfiguration`  
`struct IniCloudConfiguration`  
_private*; L87-96_
- L90 _public field_ `public string Host = String.Empty`
- L91 _public field_ `public string BuildsNamespace = String.Empty`
- L92 _public field_ `public string BuildsBaselineBranch = String.Empty`
- L95 _public ctor_ `public IniCloudConfiguration()`

### `Source/Programs/AutomationTool/AutomationUtils/CommandEnvironment.cs` (AutomationUtils.Automation)


#### class `AutomationTool.EnvVarNames`  
`public static class EnvVarNames`  
_public; L20-42_
- desc: Defines the environment variable names that will be used to setup the environment.
- L23 _public const_ `public const string LocalRoot = "uebp_LOCAL_ROOT"`
- L24 _public const_ `public const string LogFolder = "uebp_LogFolder"`
- L25 _public const_ `public const string FinalLogFolder = "uebp_FinalLogFolder"`
- L26 _public const_ `public const string CSVFile = "uebp_CSVFile"`
- L27 _public const_ `public const string EngineSavedFolder = "uebp_EngineSavedFolder"`
- L28 _public const_ `public const string MacMallocNanoZone = "MallocNanoZone"`
- L29 _public const_ `public const string DisableStartupMutex = "uebp_UATMutexNoWait"`
- L30 _public const_ `public const string IsChildInstance = "uebp_UATChildInstance"`
- L33 _public const_ `public const string P4Port = "uebp_PORT"`
- L34 _public const_ `public const string ClientRoot = "uebp_CLIENT_ROOT"`
- L35 _public const_ `public const string Changelist = "uebp_CL"`
- L36 _public const_ `public const string CodeChangelist = "uebp_CodeCL"`
- L37 _public const_ `public const string User = "uebp_USER"`
- L38 _public const_ `public const string Client = "uebp_CLIENT"`
- L39 _public const_ `public const string BuildRootP4 = "uebp_BuildRoot_P4"`
- L40 _public const_ `public const string BuildRootEscaped = "uebp_BuildRoot_Escaped"`
- L41 _public const_ `public const string P4Password = "uebp_PASS"`

#### class `AutomationTool.CommandEnvironment`  
`public class CommandEnvironment`  
_public; L48-308_
- desc: Environment to allow access to commonly used environment variables.
- L50 _private* property_ `static ILogger Logger => ...`
- L55 _public field_ `public static readonly string KnownFileRelativeToRoot = @"Engine/Config/BaseEngine.ini"` — Path to a file we know to always exist under the Unreal root directory.
- L57 _public property_ `public string LocalRoot { get; set; }`
- L58 _public property_ `public string EngineSavedFolder { get; set; }`
- L59 _public property_ `public string LogFolder { get; set; }`
- L60 _public property_ `public string FinalLogFolder { get; set; }`
- L61 _public property_ `public string CSVFile { get; set; }`
- L62 _public property_ `public string RobocopyExe { get; set; }`
- L63 _public property_ `public string MountExe { get; set; }`
- L64 _public property_ `public string CmdExe { get; set; }`
- L65 _public property_ `public string AutomationToolDll { get; set; }`
- L66 _public property_ `public string TimestampAsString { get; set; }`
- L67 _public property_ `public bool HasCapabilityToCompile { get; set; }`
- L68 _public property_ `public string FrameworkMsbuildPath { get; set; }`
- L69 _public property_ `public string DotnetMsbuildPath { get; set; }`
- L70 _public property_ `public string MallocNanoZone { get; set; }`
- L71 _public property_ `public bool IsChildInstance { get; set; }`
- L76-161 _internal ctor_ `internal CommandEnvironment()` — Initializes the environment.
- L170-184 _private* method_ `string GetSystemExePath(string ExeName)` — Returns the path to an executable in the System Directory. To help support running 32-bit assemblies on a 64-bit operating system, if the executable can't be found in System32, we also search Sysnative.
- L186-200 _private* method_ `void LogSettings()`
- L205-226 _private* method_ `void SetupBuildEnvironment()` — Initializes build environemnt: finds the path to msbuild.exe
- L233-261 _private method_ `private static string RootFromUATLocation(string UATLocation)` — Finds the root path of the branch by looking in progressively higher folder locations until a file known to exist in the branch is found.
- L267-277 _private method_ `private string GetInstalledLogFolder()` — Gets the log folder used when running from installed build.
- L283-307 _private method_ `private static void ClearLogFolder(string LogFolder)` — Clears out the contents of the given log folder

### `Source/Programs/AutomationTool/AutomationUtils/CommandUtils.cs` (AutomationUtils.Automation)


#### class `AutomationTool.ParamList`  
`public class ParamList<T> : List<T>`  
_public; L34-59_
- inherits: `List<T>`
- desc: Wrapper around List with support for multi parameter constructor, i.e: var Maps = new ParamList<string>("Map1", "Map2");
- L36-39 _public ctor_ `public ParamList(params T[] Args)`
- L41-44 _public ctor_ `public ParamList(ICollection<T> Collection) : base(Collection != null ? Collection : new T[] { })`
- L46-58 _public method_ `public override string ToString()`

#### enum `AutomationTool.PathSeparator`  
`public enum PathSeparator`  
_public; L61-68_
- L63 _public* enumerator_ `Default = 0`
- L64 _public* enumerator_ `Slash`
- L65 _public* enumerator_ `Backslash`
- L66 _public* enumerator_ `Depot`
- L67 _public* enumerator_ `Local`

#### class `AutomationTool.CommandUtils`  
`public partial class CommandUtils`  
_public; L79-2731_
- desc: Base utility function for script commands.
- L81 _private field_ `static private CommandEnvironment CmdEnvironment`
- L87-97 _public property_ `static public CommandEnvironment CmdEnv { get; }` — BuildEnvironment to use for this buildcommand. This is initialized by InitCommandEnvironment. As soon as the script execution in ExecuteBuild begins, the BuildEnv is set up and ready to use.
- L104-107 _internal method_ `static internal void InitCommandEnvironment()` — Initializes build environment. If the build command needs a specific env-var mapping or has an extended BuildEnvironment, it must implement this method accordingly.
- L112 _public property_ `public static ILogger Logger => ...` — Provides access to the structured logging interface
- L117 _public property_ `public static IServiceProvider ServiceProvider { get; set; }` — Shared service provider instance, constructed on startup
- L123 _public property_ `public static IServiceScope ServiceScope { get; set; }` — Access to scoped services which are created per command
- L128 _public property_ `public static ActivitySource ActivitySource => ...` — Global activity source for UAT. Can be used to add trace data and additional context to logs.
- L130 _private* field_ `static ActivityListener _activityListener`
- L132-142 _private* method_ `static ActivitySource CreateActivitySource()`
- L151-154 _public method_ `public static void LogInformation(string Format, params object[] Args)` — attrs: `[StringFormatMethod("Format")] [Obsolete("Use Logger.LogInformation with a message template instead; see https://tinyurl.com/bp96bk2r.", false)]` — Writes formatted text to log (with LogEventType.Console).
- L161-164 _public method_ `public static void LogInformation(string Message)` — attrs: `[Obsolete("Use Logger.LogInformation with a message template instead; see https://tinyurl.com/bp96bk2r.", false)]` — Writes formatted text to log (with LogEventType.Console).
- L173-176 _public method_ `public static void LogError(string Format, params object[] Args)` — attrs: `[StringFormatMethod("Format")] [Obsolete("Use Logger.LogError with a message template instead; see https://tinyurl.com/bp96bk2r.", false)]` — Writes formatted text to log (with LogEventType.Error).
- L183-186 _public method_ `public static void LogError(string Message)` — attrs: `[Obsolete("Use Logger.LogError with a message template instead; see https://tinyurl.com/bp96bk2r.", false)]` — Writes formatted text to log (with LogEventType.Error).
- L195-198 _public method_ `public static void LogWarning(string Format, params object[] Args)` — attrs: `[StringFormatMethod("Format")] [Obsolete("Use Logger.LogWarning with a message template instead; see https://tinyurl.com/bp96bk2r.", false)]` — Writes formatted text to log (with LogEventType.Warning).
- L205-208 _public method_ `public static void LogWarning(string Message)` — attrs: `[Obsolete("Use Logger.LogWarning with a message template instead; see https://tinyurl.com/bp96bk2r.", false)]` — Writes a message to log (with LogEventType.Warning).
- L217-220 _public method_ `public static void LogVerbose(string Format, params object[] Args)` — attrs: `[StringFormatMethod("Format")] [Obsolete("Use Logger.LogDebug with a message template instead; see https://tinyurl.com/bp96bk2r.", false)]` — Writes formatted text to log (with LogEventType.Verbose).
- L227-230 _public method_ `public static void LogVerbose(string Message)` — attrs: `[Obsolete("Use Logger.LogDebug with a message template instead; see https://tinyurl.com/bp96bk2r.", false)]` — Writes formatted text to log (with LogEventType.Verbose).
- L239-242 _public method_ `public static void LogVeryVerbose(string Format, params object[] Args)` — attrs: `[StringFormatMethod("Format")] [Obsolete("Use Logger.LogTrace with a message template instead; see https://tinyurl.com/bp96bk2r.", false)]` — Writes formatted text to log (with LogEventType.VeryVerbose).
- L249-252 _public method_ `public static void LogVeryVerbose(string Message)` — attrs: `[Obsolete("Use Logger.LogTrace with a message template instead; see https://tinyurl.com/bp96bk2r.", false)]` — Writes formatted text to log (with LogEventType.VeryVerbose).
- L261-264 _public method_ `public static void LogLog(string Format, params object[] Args)` — attrs: `[StringFormatMethod("Format")] [Obsolete("Use Logger.LogDebug with a message template instead; see https://tinyurl.com/bp96bk2r.", false)]` — Writes formatted text to log (with LogEventType.Log).
- L271-274 _public method_ `public static void LogLog(string Message)` — attrs: `[Obsolete("Use Logger.LogDebug with a message template instead; see https://tinyurl.com/bp96bk2r.", false)]` — Writes formatted text to log (with LogEventType.Log).
- L283-286 _public method_ `public static void LogWithVerbosity(EpicGames.Core.LogEventType Verbosity, string Format, params object[] Args)` — attrs: `[StringFormatMethod("Format")]` — Writes formatted text to log.
- L293-296 _public method_ `public static void LogWithVerbosity(EpicGames.Core.LogEventType Verbosity, string Message)` — Writes formatted text to log.
- L303-306 _public method_ `public static void LogWithVerbosity(EpicGames.Core.LogEventType Verbosity, Exception Ex)` — Dumps exception to log.
- L308-314 _public method_ `public static void LogPushProgress(bool bShowProgress, int Numerator, int Denominator)`
- L316-322 _public method_ `public static void LogPopProgress(bool bShowProgress)`
- L324-330 _public method_ `public static void LogIncrementProgress(bool bShowProgress, int Numerator, int Denominator)`
- L333-339 _public method_ `public static void LogSetProgress(bool bShowProgress, string Format, params string[] Args)` — attrs: `[StringFormatMethod("Format")]`
- L342-348 _public method_ `public static void LogSetProgress(bool bShowProgress, int Numerator, int Denominator, string Format, params string[] Args)` — attrs: `[StringFormatMethod("Format")]`
- L357-373 _public method_ `public static string[] FindFiles(string SearchPattern, bool Recursive, string PathToSearch)` — Finds files in specified paths.
- L382-385 _public method_ `public static FileReference[] FindFiles(string SearchPattern, bool Recursive, DirectoryReference PathToSearch)` — Finds files in specified paths.
- L394-409 _public method_ `public static string[] FindFiles_NoExceptions(string SearchPattern, bool Recursive, string PathToSearch)` — Finds files in specified paths.
- L418-433 _public method_ `public static string[] FindFiles_NoExceptions(bool bQuiet, string SearchPattern, bool Recursive, string PathToSearch)` — Finds files in specified paths.
- L442-458 _public method_ `public static string[] FindDirectories(bool bQuiet, string SearchPattern, bool Recursive, string PathToSearch)` — Finds files in specified paths.
- L467-482 _public method_ `public static string[] FindDirectories_NoExceptions(bool bQuiet, string SearchPattern, bool Recursive, string PathToSearch)` — Finds Directories in specified paths.
- L489-496 _public method_ `public static void DeleteFile(string FileName)` — Deletes a file(s). If the file does not exist, silently succeeds. If the deletion of the file fails, this function throws an Exception.
- L504-507 _public method_ `public static void DeleteFile(FileReference FileName)` — Deletes a file(s). If the file does not exist, silently succeeds. If the deletion of the file fails, this function throws an Exception.
- L516-523 _public method_ `public static void DeleteFile(bool bQuiet, string FileName)` — Deletes a file(s). If the file does not exist, silently succeeds. If the deletion of the file fails, this function throws an Exception.
- L530-541 _public method_ `public static bool DeleteFile_NoExceptions(string FileName)` — Deletes a file(s). If the deletion of the file fails, prints a warning.
- L548-558 _public method_ `public static bool DeleteFile_NoExceptions(string Filename, bool bQuiet = false)` — Deletes a file(s). If the deletion of the file fails, prints a warning.
- L566-573 _public method_ `public static void DeleteDirectory(bool bQuiet, string Directory)` — Deletes a directory(or directories) including its contents (recursively, will delete read-only files). If the deletion of the directory fails, this function throws an Exception.
- L580-583 _public method_ `public static void DeleteDirectory(string Directory)` — Deletes a directory(or directories) including its contents (recursively, will delete read-only files). If the deletion of the directory fails, this function throws an Exception.
- L590-593 _public method_ `public static void DeleteDirectory(DirectoryReference Directory)` — Deletes a directory(or directories) including its contents (recursively, will delete read-only files). If the deletion of the directory fails, this function throws an Exception.
- L601-625 _public method_ `public static bool DeleteDirectory_NoExceptions(bool bQuiet, string Directory)` — Deletes a directory(or directories) including its contents (recursively, will delete read-only files). If the deletion of the directory fails, prints a warning.
- L632-635 _public method_ `public static bool DeleteDirectory_NoExceptions(string DirectoryName)` — Deletes a directory(or directories) including its contents (recursively, will delete read-only files). If the deletion of the directory fails, prints a warning.
- L644-658 _public method_ `public static void DeleteDirectoryContents(string DirectoryName)` — Attempts to delete a directory, if that fails deletes all files and folder from the specified directory. This works around the issue when the user has a file open in a notepad from that directory. Somehow deleting the file works but deleting the directory with the file that's open, doesn't.
- L666-669 _public method_ `public static void DeleteDirectoryContents(DirectoryReference DirectoryName)` — Attempts to delete a directory, if that fails deletes all files and folder from the specified directory. This works around the issue when the user has a file open in a notepad from that directory. Somehow deleting the file works but deleting the directory with the file that's open, doesn't.
- L676-680 _public method_ `public static bool DirectoryExists(string DirectoryName)` — Checks if a directory(or directories) exists.
- L687-700 _public method_ `public static bool DirectoryExists_NoExceptions(string DirectoryName)` — Checks if a directory(or directories) exists.
- L710-715 _public method_ `public static void RenameDirectory(string OldName, string NewName, bool bQuiet = false, bool bRetry = true)` — Renames/moves a directory. If the rename of the directory fails, this function throws an Exception.
- L725-730 _public method_ `public static bool RenameDirectory_NoExceptions(string OldName, string NewName, bool bQuiet = false, bool bRetry = true)` — Renames/moves a directory. If the rename of the directory fails, this function prints a warning.
- L736-747 _public method_ `public static void CreateDirectory(string DirectoryName)` — Creates a directory. Throws an exception on failure.
- L753-756 _public method_ `public static void CreateDirectory(DirectoryReference Location)` — Creates a directory. Throws an exception on failure.
- L765-773 _public method_ `public static void RenameFile(string OldName, string NewName, bool bQuiet = false)` — Renames/moves a file. If the rename of the file fails, this function throws an Exception.
- L781-791 _public method_ `public static bool RenameFile_NoExceptions(string OldName, string NewName)` — Renames/moves a file. If the rename of the file fails, this function prints a warning.
- L798-803 _public method_ `public static bool FileExists(string FileName)` — Checks if a file(s) exists.
- L810-814 _public method_ `public static bool FileExists_NoExceptions(string FileName)` — Checks if a file(s) exists.
- L822-827 _public method_ `public static bool FileExists(bool bQuiet, string FileName)` — Checks if a file(s) exists.
- L835-839 _public method_ `public static bool FileExists_NoExceptions(bool bQuiet, string FileName)` — Checks if a file(s) exists.
- L841 _private* field_ `static Stack<string> WorkingDirectoryStack = new Stack<string>()`
- L847-861 _public method_ `public static void PushDir(string WorkingDirectory)` — Pushes the current working directory onto a stack and sets CWD to a new value.
- L867-883 _public method_ `public static bool PushDir_NoExceptions(string WorkingDirectory)` — Pushes the current working directory onto a stack and sets CWD to a new value.
- L888-898 _public method_ `public static void PopDir()` — Pops the last working directory from a stack and sets it as the current working directory.
- L903-916 _public method_ `public static bool PopDir_NoExceptions()` — Pops the last working directory from a stack and sets it as the current working directory.
- L921-927 _public method_ `public static void ClearDirStack()` — Clears the directory stack
- L933-944 _public method_ `public static void ChDir(string WorkingDirectory)` — Changes the current working directory.
- L950-964 _public method_ `public static bool ChDir_NoExceptions(string WorkingDirectory)` — Changes the current working directory.
- L972-987 _public method_ `public static void TouchFile(string Filename, DateTime? UtcDate = null)` — Updates a file with the specified modified and access date, creating the file if it does not already exist. An exception will be thrown if the directory does not already exist.
- L994-1004 _public method_ `public static bool IsReadOnly(string Filename)` — Determines whether the given file is read-only
- L1013-1024 _public method_ `public static void SetFileAttributes(string Filename, bool? ReadOnly = null, bool? Hidden = null, bool? Archive = null)` — Sets file attributes. Will not change attributes that have not been specified.
- L1033-1056 _public method_ `public static bool SetFileAttributes_NoExceptions(string Filename, bool? ReadOnly = null, bool? Hidden = null, bool? Archive = null)` — Sets file attributes. Will not change attributes that have not been specified.
- L1058-1094 _private method_ `private static FileAttributes InternalSetAttributes(bool? ReadOnly, bool? Hidden, bool? Archive, FileAttributes Attributes)`
- L1102-1113 _public method_ `public static void WriteToFile(string Filename, string Text)` — Writes a line of formatted string to a file. Creates the file if it does not exists. If the file does exists, appends a new line.
- L1120-1124 _public method_ `public static string[] ReadAllLines(string Filename)` — Reads all text lines from a file.
- L1131-1135 _public method_ `public static string ReadAllText(string Filename)` — Reads all text from a file.
- L1142-1149 _public method_ `public static void WriteAllLines(string Filename, string[] Lines)` — Writes lines to a file.
- L1156-1160 _public method_ `public static bool WriteAllLines_NoExceptions(string Filename, string[] Lines)` — Writes lines to a file.
- L1167-1174 _public method_ `public static void WriteAllText(string Filename, string Text)` — Writes text to a file.
- L1181-1185 _public method_ `public static bool WriteAllText_NoExceptions(string Filename, string Text)` — Writes text to a file.
- L1193-1200 _public method_ `public static void WriteAllBytes(string Filename, byte[] Bytes)` — Writes byte array to a file.
- L1207-1211 _public method_ `public static bool WriteAllBytes_NoExceptions(string Filename, byte[] Bytes)` — Writes byte array to a file.
- L1218-1235 _public method_ `public static char GetPathSeparatorChar(PathSeparator SeparatorType)` — Gets a character representing the specified separator type.
- L1242-1245 _public method_ `public static bool IsPathSeparator(char Character)` — Checks if the character is one of the two sperator types ('\' or '/')
- L1252-1255 _public method_ `public static string CombinePaths(params string[] Paths)` — Combines paths and replaces all path separators with the system default separator.
- L1263-1309 _public method_ `public static string CombinePaths(PathSeparator SeparatorType, params string[] Paths)` — Combines paths and replaces all path separators wth the system specified separator.
- L1317-1320 _public method_ `public static string ConvertSeparators(PathSeparator ToSperatorType, string PathToConvert)` — Converts all separators in path to the specified separator type.
- L1329-1380 _public method_ `public static void CopyFile(string Source, string Dest, bool bQuiet = false, bool bRetry = false)` — Copies a file, throwing an exception on failure.
- L1389-1409 _public method_ `public static bool CopyFile_NoExceptions(string Source, string Dest, bool bQuiet = false)` — Copies a file. Does not throw exceptions.
- L1417-1428 _public method_ `public static bool IsTargetFileUpToDate(FileReference Target, FileReference Source)` — Checks if the given target file is up to date with the source file (ie. it exists, and the timestamp matches)
- L1440-1478 _public method_ `public static void CopyFileIncremental(FileReference Source, FileReference Dest, OverrideCopyDelegate OverrideCopyHandler = null, bool bAllowDifferingTimestamps = false, List<string> IniKeyDenyList = null, List<string> IniSectionDenyList = null)` — Copies a file if the dest doesn't exist or (optionally) if the dest timestamp is different; after a copy, copies the timestamp
- L1499-1502 _public method_ `public static bool CopyDirectory_NoExceptions(DirectoryReference Source, DirectoryReference Dest, bool bQuiet = false)` — Copies a directory and all of it's contents recursively. Does not throw exceptions.
- L1511-1514 _public method_ `public static bool CopyDirectory_NoExceptions(string Source, string Dest, bool bQuiet = false)` — Copies a directory and all of it's contents recursively. Does not throw exceptions.
- L1523-1526 _public method_ `public static bool MergeDirectory_NoExceptions(DirectoryReference Source, DirectoryReference Dest, bool bQuiet = false)` — Copies a directory and all of it's contents recursively. Merges with the destination directory. Does not throw exceptions.
- L1535-1538 _public method_ `public static bool MergeDirectory_NoExceptions(string Source, string Dest, bool bQuiet = false)` — Copies a directory and all of it's contents recursively. Merges with the destination directory. Does not throw exceptions.
- L1547-1597 _public method_ `public static bool CopyDirectory_NoExceptions(string Source, string Dest, CopyDirectoryOptions Options)` — Copies a directory and all of it's contents recursively. Does not throw exceptions.
- L1608-1620 _public method_ `public static string GetDirectoryName(string FilePath)` — Returns directory name without filename. The difference between this and Path.GetDirectoryName is that this function will not throw away the last name if it doesn't have an extension, for example: D:\Project\Data\Asset -> D:\Project\Data\Asset D:\Project\Data\Asset.ussset -> D:\Project\Data
- L1628-1637 _public method_ `public static string GetLastDirectoryName(string FilePath)` — Returns the last directory name in the path string. For example: D:\Temp\Project\File.txt -> Project, Data\Samples -> Samples
- L1644-1652 _public method_ `public static string GetFilenameWithoutAnyExtensions(string Filename)` — Removes multi-dot extensions from a filename (i.e. *.automation.csproj)
- L1659-1691 _public method_ `public static BuildManifest ReadManifest(FileReference ManifestFile)` — Reads a file manifest and returns it
- L1694 _private field_ `private static readonly XmlSerializer BuildManifestSerializer = XmlSerializer.FromTypes(new[] { typeof(UnrealBuildTool.BuildManifest) })[0]`
- L1696-1735 _private method_ `private static void CloneDirectoryRecursiveWorker(string SourcePathBase, string TargetPathBase, List<string> ClonedFiles, bool bIncremental = false)`
- L1745-1749 _public method_ `public static void CloneDirectory(string SourcePath, string TargetPath, List<string> ClonedFiles = null)` — Clones a directory. Warning: Will delete all of the existing files in TargetPath This is recursive, copying subfolders too.
- L1758-1761 _public method_ `public static void CloneDirectoryIncremental(string SourcePath, string TargetPath, List<string> ClonedFiles = null)` — Clones a directory, skipping any files which already exist in the destination. This is recursive, copying subfolders too.
- L1769-1775 _public method_ `public static void ThreadedCopyFiles(string SourceDirectory, string DestDirectory, int MaxThreads = 64)` — Copies files using multiple threads
- L1777-1780 _public method_ `public static void ThreadedCopyFiles(DirectoryReference SourceDirectory, DirectoryReference DestDirectory, int MaxThreads = 64)`
- L1787-1790 _public method_ `public static void ThreadedCopyFiles(List<FileReference> SourceFiles, List<FileReference> TargetFiles)` — Copies files using multiple threads
- L1798-1813 _public method_ `public static void ThreadedCopyFiles(List<FileReference> SourceFiles, DirectoryReference SourceDir, DirectoryReference TargetDir)` — Copies files using multiple threads
- L1823-1838 _public method_ `public static void ThreadedCopyFiles(List<string> Source, List<string> Dest, int MaxThreads = 64, bool bQuiet = false, bool bRetry = false)` — Copies files using multiple threads
- L1849-1855 _public method_ `public static List<string> ThreadedCopyFiles(string SourceDir, string TargetDir, List<string> RelativePaths, int MaxThreads = 64, bool bRetry = false)` — Copies a set of files from one folder to another
- L1867-1874 _public method_ `public static List<string> ThreadedCopyFiles(string SourceDir, string TargetDir, FileFilter Filter, bool bIgnoreSymlinks, int MaxThreads = 64, bool bRetry = false)` — Copies a set of files from one folder to another
- L1880-1883 _public method_ `public static void ParallelMoveFiles(IEnumerable<KeyValuePair<FileReference, FileReference>> SourceAndTargetPairs)` — Moves files in parallel
- L1890-1900 _public method_ `public static void ParallelMoveFiles(IEnumerable<KeyValuePair<FileReference, FileReference>> SourceAndTargetPairs, bool Overwrite)` — Moves files in parallel
- L1907-1910 _public method_ `public static void MoveFile(FileReference SourceFile, FileReference TargetFile)` — Move a file from one place to another
- L1918-1943 _public method_ `public static void MoveFile(FileReference SourceFile, FileReference TargetFile, bool Overwrite)` — Move a file from one place to another
- L1953-1961 _public property_ `public static SymlinkMode DefaultSymlinkMode { get; }`
- L1967-1999 _public method_ `public static void FindFilesAndSymlinks(string RootPath, string Wildcard, bool bRecursive, SymlinkMode DirSymlinkMode, List<string> FoundFiles)` — Assumes directory has already been checked to exist, and that it is not a symlink itself The SymlinkMode here refers to directory links, as the file symlinks will be dealt with during the copy
- L2001-2004 _public method_ `public static void FindFilesAndSymlinks(string RootPath, string Wildcard, bool bRecursive, List<string> FoundFiles)`
- L2006-2035 _public method_ `public static void CopyFileOrSymlink(FileReference Source, FileReference Dest, SymlinkMode SymlinkMode)`
- L2037-2040 _public method_ `public static void CopyFileOrSymlink(FileReference Source, FileReference Dest)`
- L2048-2051 _public method_ `public static string GetEnvVar(string Name)` — Gets environment variable value.
- L2059-2062 _public method_ `public static string GetEnvVar(string Name, string DefaultValue)` — Gets environment variable value.
- L2070-2081 _public method_ `public static void SetEnvVar(string Name, object Value)` — Sets environment variable.
- L2088-2094 _public method_ `public static void ConditionallySetEnvVar(string VarName, string Value)` — Sets the environment variable if it hasn't been already.
- L2102-2118 _public method_ `public static bool ParseParam(string[] ArgList, string Param)` — Parses the argument list for a parameter and returns whether it is defined or not.
- L2128-2144 _public method_ `public static string ParseParamValue(object[] ArgList, string Param, string Default = null)` — Parses the argument list for a parameter and reads its value. Ex. ParseParamValue(Args, "map=")
- L2152-2170 _public method_ `public static string[] ParseParamValues(object[] ArgList, string Param)` — Parses the argument list for any number of parameters.
- L2177-2180 _public method_ `public static string MakePathSafeToUseWithCommandLine(string InPath)` — Makes sure path can be used as a command line param (adds quotes if it contains spaces)
- L2182-2185 _public method_ `public static string EscapePath(string InPath)`
- L2192-2195 _public method_ `public static bool IsNullOrEmpty(ICollection Collection)` — Checks if collection is either null or empty.
- L2200-2203 _public property_ `public static bool IsBuildMachine { get; }` — Checks if this command is running on a build machine.
- L2208-2218 _public method_ `public static DirectoryReference[] GetAllEngineDirectories()` — Return the main engine directory and any platform extension engine directories
- L2223-2233 _public method_ `public static DirectoryReference[] GetAllProjectDirectories(FileReference ProjectFile)` — Return the main project directory and any platform extension project directories
- L2238 _public field_ `public static TelemetryData Telemetry = new TelemetryData()` — Telemetry data for the current run. Add -WriteTelemetry=[Path] to the command line to export to disk.
- L2243 _private field_ `private static string CachedRootBuildStorageDirectory` — Cached location of the build root storage because the logic to compute it is a little non-trivial.
- L2249-2276 _public method_ `public static string RootBuildStorageDirectory()` — "P:\Builds" or "/Volumes/Builds". Root Folder for all build storage.
- L2278-2307 _public method_ `public static bool DirectoryExistsAndIsWritable_NoExceptions(string Dir)`
- L2309-2350 _public method_ `public static void CleanFormalBuilds(string ParentDir, string SearchPattern, double MaximumDaysToKeepTempStorage = 4, int maxParallelDeletes = 4)`
- L2357-2371 _public method_ `public static string GetGenericPlatformName(UnrealBuildTool.UnrealTargetPlatform Platform)` — Returns the generic name for a given platform (eg. "Windows" for Win32/Win64)
- L2379-2383 _public method_ `public static void ZipFiles(FileReference ZipFileName, DirectoryReference BaseDirectory, FileFilter Filter)` — Creates a zip file containing the given input files
- L2392-2428 _public method_ `public static void ZipFiles(FileReference OutputFile, DirectoryReference BaseDirectory, IEnumerable<FileReference> Files, HashSet<FileReference> ExecutableFiles = null)` — Creates a zip file containing the given input files
- L2436-2439 _public method_ `public static IEnumerable<string> UnzipFiles(string ZipFileName, string BaseDirectory)` — Extracts the contents of a zip file
- L2448-2476 _public method_ `public static IEnumerable<FileReference> UnzipFiles(FileReference ZipFileName, DirectoryReference BaseDirectory, bool OverwriteFiles = true)` — Extracts the contents of a zip file
- L2485-2547 _public method_ `public static IEnumerable<string> LegacyUnzipFiles(string ZipFileName, string BaseDirectory, bool OverwriteFiles = true)` — Extracts the contents of a zip file
- L2556-2601 _public method_ `public static IEnumerable<FileReference> ResolveFilespec(DirectoryReference DefaultDir, string Pattern, IEnumerable<string> ExcludePatterns)` — Resolve an arbitrary file specification against a directory. May contain any number of p4 wildcard operators (?, *, ...).
- L2603-2616 _public method_ `public static string FormatSizeString(long Size)`
- L2618-2686 _public method_ `public static void TakeLock(DirectoryReference LockDirectory, TimeSpan Timeout, System.Action Callback)`
- L2687-2698 _public method_ `public static void OptionallyTakeLock(bool Condition, DirectoryReference LockDirectory, TimeSpan Timeout, System.Action Callback)`
- L2700-2730 _public method_ `public static FileReference FindToolInPath(string ToolName)`

#### enum `AutomationTool.CommandUtils.CopyDirectoryOptions`  
`public enum CopyDirectoryOptions`  
_public; L1481-1490_
- attrs: `[Flags]`
- L1483 _public* enumerator_ `None = 0`
- L1484 _public* enumerator_ `SuppressLogging = 1`
- L1485 _public* enumerator_ `KeepExistingDirectories = 2`
- L1486 _public* enumerator_ `KeepExistingFiles = 4`
- L1488 _public* enumerator_ `Default = None`
- L1489 _public* enumerator_ `Merge = KeepExistingFiles | KeepExistingDirectories`

#### enum `AutomationTool.CommandUtils.SymlinkMode`  
`public enum SymlinkMode`  
_public; L1945-1950_
- L1947 _public* enumerator_ `Ignore`
- L1948 _public* enumerator_ `Follow`
- L1949 _public* enumerator_ `Retain`

#### enum `AutomationTool.TelemetryUnits`  
`public enum TelemetryUnits`  
_public; L2736-2745_
- desc: Valid units for telemetry data
- L2738 _public* enumerator_ `Count`
- L2739 _public* enumerator_ `Milliseconds`
- L2740 _public* enumerator_ `Seconds`
- L2741 _public* enumerator_ `Minutes`
- L2742 _public* enumerator_ `Bytes`
- L2743 _public* enumerator_ `Megabytes`
- L2744 _public* enumerator_ `Percentage`

#### class `AutomationTool.TelemetrySample`  
`public class TelemetrySample`  
_public; L2750-2766_
- desc: Sample for telemetry data
- L2755 _public field_ `public string Name` — Name of this sample
- L2760 _public field_ `public double Value` — The value for this sample
- L2765 _public field_ `public TelemetryUnits Units` — Units for this sample

#### class `AutomationTool.TelemetryData`  
`public class TelemetryData`  
_public; L2771-2874_
- desc: Stores a set of key/value telemetry samples which can be read and written to a JSON file
- L2776 _private* const_ `const int CurrentVersion = 1` — The current file version
- L2781 _public field_ `public List<TelemetrySample> Samples = new List<TelemetrySample>()` — Maps from a sample name to its value
- L2789-2794 _public method_ `public void Add(string Name, double Value, TelemetryUnits Units)` — Adds a telemetry sample
- L2801-2807 _public method_ `public void Merge(string Prefix, TelemetryData Other)` — Add samples from another telemetry block into this one
- L2815-2848 _public method_ `public static bool TryRead(FileReference FileName, out TelemetryData Telemetry)` — Tries to read the telemetry data from the given file
- L2854-2873 _public method_ `public void Write(string FileName)` — Writes out the telemetry data to a file

#### class `AutomationTool.TelemetryStopwatch`  
`public class TelemetryStopwatch : IDisposable`  
_public; L2879-2932_
- inherits: `IDisposable`
- desc: Timer class used for telemetry reporting.
- L2881 _private* field_ `string Name`
- L2882 _private* field_ `DateTime StartTime`
- L2883 _private* field_ `bool bFinished`
- L2886-2890 _public ctor_ `public TelemetryStopwatch(string Format, params object[] Args)` — attrs: `[StringFormatMethod("Format")]`
- L2892-2895 _public method_ `public void Cancel()`
- L2902-2926 _public method_ `public void Finish(string AlternateName = null)` — Flushes the time to CommandEnvironment.CSVFile if we are the build machine and that environment variable is specified. Call Finish manually with an alternate name to use that one instead. Useful for dynamically generated names that you can't specify at construction.
- L2928-2931 _public method_ `public void Dispose()`

#### class `AutomationTool.DateTimeStopwatch`  
`public class DateTimeStopwatch`  
_public; L2937-2952_
- desc: Stopwatch that uses DateTime.UtcNow for timing. Not hi-res, but also not subject to short time limitations of System.Diagnostics.Stopwatch.
- L2939-2942 _public method_ `public static DateTimeStopwatch Start()`
- L2947 _private ctor_ `private DateTimeStopwatch()` — Hide public ctor.
- L2949 _private* field_ `readonly DateTime StartTime = DateTime.UtcNow`
- L2951 _public property_ `public TimeSpan ElapsedTime { get; }`

#### class `AutomationTool.PushedDirectory`  
`public class PushedDirectory : IDisposable`  
_public; L2957-2969_
- inherits: `IDisposable`
- desc: Use with "using" syntax to push and pop directories in a convenient, exception-safe way
- L2959-2962 _public ctor_ `public PushedDirectory(string DirectoryName)`
- L2964-2968 _public method_ `public void Dispose()`

#### class `AutomationTool.ScopedEnvVar`  
`public class ScopedEnvVar : IDisposable`  
_public; L2974-2989_
- inherits: `IDisposable`
- desc: Use with "using" syntax to temporarily set and environment variable in a convenient, exception-safe way
- L2976 _private field_ `private string StoredEnvVar = null`
- L2978-2982 _public ctor_ `public ScopedEnvVar(string EnvVar, string Value)`
- L2984-2988 _public method_ `public void Dispose()`

#### class `AutomationTool.EMSFileInfo`  
`public class EMSFileInfo`  
_public; L2994-2998_
- desc: Helper class to associate a file and its contents
- L2996 _public property_ `public string FileName { get; set; }`
- L2997 _public property_ `public byte[] Bytes { get; set; }`

#### class `AutomationTool.EnumerationResponse`  
`public sealed class EnumerationResponse`  
_public; L3004-3023_
- attrs: `[DataContract]`
- desc: Wrapper class for the enumerate files JSON response from MCP
- L3007 _public property_ `public Boolean DoNotCache { get; set; }` — attrs: `[DataMember(Name = "doNotCache", IsRequired = true)]`
- L3010 _public property_ `public string UniqueFilename { get; set; }` — attrs: `[DataMember(Name = "uniqueFilename", IsRequired = true)]`
- L3013 _public property_ `public string Filename { get; set; }` — attrs: `[DataMember(Name = "filename", IsRequired = true)]`
- L3016 _public property_ `public string Hash { get; set; }` — attrs: `[DataMember(Name = "hash", IsRequired = true)]`
- L3019 _public property_ `public long Length { get; set; }` — attrs: `[DataMember(Name = "length", IsRequired = true)]`
- L3022 _public property_ `public string Uploaded { get; set; }` — attrs: `[DataMember(Name = "uploaded", IsRequired = true)]`

#### class `AutomationTool.CodeSignWindows`  
`static class CodeSignWindows`  
_internal*; L3025-3212_
- L3030 _private* const_ `const string SigningIdentity = "Epic Games"` — The signing identity to find a certificate for
- L3035 _private* field_ `static bool bUseMachineStoreForCertificates = true` — Whether to look in the machine store for signing certificates, rather than the user store.
- L3044 _private* field_ `static readonly string[] TimestampServersSHA1 = { "http://timestamp.digicert.com", "http://ts.ssl.com", "http://kstamp.keynectis.com/KSign" }`
- L3051 _private* field_ `static readonly string[] TimestampServersSHA256 = { "http://timestamp.digicert.com", "http://ts.ssl.com", "http://rfc3161timestamp.globalsign.com/advanced" }`
- L3058 _private* field_ `static readonly int LongestSHA1 = TimestampServersSHA1.Select(x => x.Length).Max()`
- L3059 _private* field_ `static readonly int LongestSHA256 = TimestampServersSHA1.Select(x => x.Length).Max()`
- L3062-3066 _public method_ `public static void Sign(FileReference File, SignatureType SignatureType, bool AllowMultipleSignatures = true, string Description = null, bool RunInParallel = false)` — attrs: `[SupportedOSPlatform("windows")]`
- L3069-3177 _public method_ `public static void Sign(List<FileReference> Files, SignatureType SignatureType, bool AllowMultipleSignatures = true, string Description = null, bool RunInParallel = false)` — attrs: `[SupportedOSPlatform("windows")]`
- L3184-3211 _private* method_ `static string GetSignToolPath()` — attrs: `[SupportedOSPlatform("windows")]` — Finds the path to SignTool.exe, or throws an exception.

#### enum `AutomationTool.CodeSignWindows.SignatureType`  
`public enum SignatureType`  
_public; L3037-3041_
- L3039 _public* enumerator_ `SHA1`
- L3040 _public* enumerator_ `SHA256`

#### class `AutomationTool.CodeSignHelper`  
`public class CodeSignHelper`  
_public; L3214-3260_
- L3216 _private field_ `private static ICodeSignHelper HelperClass = null`
- L3218-3259 _public method_ `public static ICodeSignHelper FindHelper(string SignToolPath)`

#### interface `AutomationTool.ICodeSignHelper`  
`public interface ICodeSignHelper`  
_public; L3267-3274_
- desc: Interface helper class handle signing as a service environments Implement a custom class for any provides
- L3269 _public method_ `public void Initialize(string SignToolPath)`
- L3270 _public method_ `public bool Validate(ILogger Logger)`
- L3271 _public method_ `public bool IsHealthy(IProcessResult Result, ILogger Logger)`
- L3272 _public method_ `public bool IsFixing()`
- L3273 _public method_ `public bool Fix(int SignAttempt, ILogger Logger)`

#### class `AutomationTool.CodeSign`  
`public class CodeSign`  
_public; L3280-3536_
- attrs: `[Help("NoSign", "Skips signing of code/content files.")]`
- desc: Code signing
- L3285-3333 _public method_ `public static void SignSingleExecutableIfEXEOrDLL(string Filename, bool bIgnoreExtension = false, string Description = null)` — Code signs the specified file
- L3338-3447 _public method_ `public static void SignMacFileOrFolder(string InPath, bool bIgnoreExtension = false, string NotarizationEntitlements = null)` — Code signs the specified file or folder
- L3457-3484 _public method_ `public static void SignMultipleIfEXEOrDLL(BuildCommand Command, IEnumerable<string> Files, string Description = null, bool bRunInParallel = false)` — Codesigns multiple files, but skips anything that's not an EXE or DLL file Will automatically skip signing if -NoSign is specified in the command line.
- L3486-3535 _public method_ `public static void SignMultipleFilesIfEXEOrDLL(List<FileReference> Files, bool bIgnoreExtension = false, string Description = null, bool bRunInParallel = false)`

#### Namespace-level symbols

- L74 _public delegate_ `public delegate bool OverrideCopyDelegate(ILogger Logger, string SourceName, string TargetName)` — Delegate to override the copy operation. Return true if the copy was handled. Otherwise false to fallback on the built in copy operation

### `Source/Programs/AutomationTool/AutomationUtils/CommandletUtils.cs` (AutomationUtils.Automation)


#### class `AutomationTool.CommandletException`  
`public class CommandletException : AutomationException`  
_public; L20-45_
- inherits: `AutomationException`
- desc: Exception thrown when the execution of a commandlet fails
- L25 _public field_ `public string LogFileName` — The log file output by this commandlet
- L30 _public field_ `public int ErrorNumber` — The exit code
- L39-44 _public ctor_ `public CommandletException(string LogFilename, int ErrorNumber, string Format, params object[] Args) : base(Format,Args)` — Constructor

#### class `AutomationTool.CommandUtils`  
`public partial class CommandUtils`  
_public; L47-590_
- L60-94 _public method_ `public static void CookCommandlet(FileReference ProjectFile, string UnrealExe = null, string[] Maps = null, string[] Dirs = null, string InternationalizationPreset = "", string[] CulturesToCook = null, string TargetPlatform = "Windows", string Parameters = "-Unversioned")` — Runs Cook commandlet.
- L104-113 _public method_ `public static void DDCCommandlet(FileReference ProjectFile, string UnrealExe = null, string[] Maps = null, string TargetPlatform = "Windows", string Parameters = "")` — Runs DDC commandlet.
- L122-131 _public method_ `public static void RebuildLightMapsCommandlet(FileReference ProjectFile, string UnrealExe = null, string[] Maps = null, string Parameters = "")` — Runs RebuildLightMaps commandlet.
- L133-136 _public method_ `public static void RebuildHLODCommandlet(FileReference ProjectName, string UnrealExe = null, string[] Maps = null, string Parameters = "")`
- L138-147 _public method_ `public static void RebuildHLODCommandlet(FileReference ProjectFile, out string DestLogFile, string UnrealExe = null, string[] Maps = null, string Parameters = "")`
- L156-165 _public method_ `public static void ResavePackagesCommandlet(FileReference ProjectFile, string UnrealExe = null, string[] Maps = null, string Parameters = "")` — Runs RebuildLightMaps commandlet.
- L175-223 _public method_ `public static List<FileReference> GenerateDistillFileSetsCommandlet(FileReference ProjectFile, string ManifestFile, string UnrealExe = null, string[] Maps = null, string Parameters = "")` — Runs GenerateDistillFileSets commandlet.
- L231-234 _public method_ `public static void UpdateGameProjectCommandlet(FileReference ProjectFile, string UnrealExe = null, string Parameters = "")` — Runs UpdateGameProject commandlet.
- L244-248 _public method_ `public static void RunCommandlet(FileReference ProjectFile, string UnrealExe, string Commandlet, string Parameters = null, uint ErrorLevel = 1)` — Runs a commandlet using Engine/Binaries/Win64/UnrealEditor-Cmd.exe.
- L258-262 _public method_ `public static void RunCommandlet(FileReference ProjectFile, string UnrealExe, string Commandlet, string Parameters, int ErrorLevel)` — Runs a commandlet using Engine/Binaries/Win64/UnrealEditor-Cmd.exe.
- L273-282 _public method_ `public static void RunCommandlet(FileReference ProjectFile, string UnrealExe, string Commandlet, string Parameters, out string DestLogFile, uint ErrorLevel = 1)` — Runs a commandlet using Engine/Binaries/Win64/UnrealEditor-Cmd.exe.
- L293-296 _public method_ `public static void RunCommandlet(FileReference ProjectFile, string UnrealExe, string Commandlet, string Parameters, out string DestLogFile, int ErrorLevel)` — Runs a commandlet using Engine/Binaries/Win64/UnrealEditor-Cmd.exe.
- L298-336 _public method_ `public static void StartRunCommandlet(FileReference ProjectFile, string UnrealExe, string Commandlet, string Parameters, ERunOptions RunOptions, out string LocalLogFile, out IProcessResult RunResult, ProcessResult.SpewFilterCallbackType SpewFilterCallback=null)`
- L338-478 _public method_ `public static void FinishRunCommandlet(FileReference ProjectFile, string Commandlet, DateTime StartTime, IProcessResult RunResult, string LocalLogFile, out string DestLogFile, uint ErrorLevel = 1)`
- L480-483 _public method_ `public static void FinishRunCommandlet(FileReference ProjectFile, string Commandlet, DateTime StartTime, IProcessResult RunResult, string LocalLogFile, out string DestLogFile, int ErrorLevel)`
- L491-506 _public method_ `public static string GetEditorCommandletExe(string BuildRoot, UnrealBuildTool.UnrealTargetPlatform HostPlatform)` — Returns the default path of the editor executable to use for running commandlets.
- L515-540 _public method_ `public static string CombineCommandletParams(IEnumerable<string> ParamValues, string Separator = "+")` — Combines a list of parameters into a single commandline param separated with '+': For example: Map1+Map2+Map3
- L547-578 _public method_ `public static FileReference GetCommandletProjectFile(string ProjectName)` — Converts project name to FileReference used by other commandlet functions
- L585-589 _public method_ `public static DirectoryReference GetCrashesDirectory(FileReference ProjectFullPath)` — Get the crashes directory for the given project file

### `Source/Programs/AutomationTool/AutomationUtils/CompatibilityShims.cs` (AutomationUtils.Automation)


#### class `Microsoft.IdentityModel.Tokens.CollectionUtilitiesShim`  
`public static class CollectionUtilitiesShim`  
_public; L15-35_
- desc: Compatibility shim restoring IsNullOrEmpty extension methods that were made internal in Microsoft.IdentityModel.Tokens v8.0.0 (see issue #2651).
- L21-24 _public method_ `public static bool IsNullOrEmpty(this string? value)` — Returns true if value is null or empty.
- L31-34 _public method_ `public static bool IsNullOrEmpty<T>(this IEnumerable<T>? enumerable)` — Returns true if enumerable is null or contains no elements.

### `Source/Programs/AutomationTool/AutomationUtils/CopyUAT.cs` (AutomationUtils.Automation)


#### class `CopyUAT`  
`public class CopyUAT : BuildCommand`  
_public; L17-61_
- inherits: `BuildCommand`
- desc: Copies all UAT and UBT build products to a directory
- L19-60 _public method_ `public override void ExecuteBuild()`

### `Source/Programs/AutomationTool/AutomationUtils/CustomDeploymentHandler.cs` (AutomationUtils.Automation)


#### class `CustomDeploymentHandler`  
`public abstract class CustomDeploymentHandler`  
_public; L12-91_
- desc: Allows a target to change how it is packaged, staged and deployed - for example, when packaging for a specific game store
- L14 _protected field_ `protected readonly Platform Platform`
- L15-18 _protected ctor_ `protected CustomDeploymentHandler( Platform AutomationPlatform, ProjectParams Params, DeploymentContext SC ) : this(AutomationPlatform)`
- L19-22 _protected ctor_ `protected CustomDeploymentHandler( Platform AutomationPlatform )`
- L23 _public method_ `public abstract bool SupportsPlatform( UnrealTargetPlatform Platform )`
- L26 _public method_ `public virtual bool GetPlatformPakCommandLine(ProjectParams Params, DeploymentContext SC, ref string CmdLine)`
- L27 _public method_ `public virtual bool GetPlatformIoStoreCommandLine(ProjectParams Params, DeploymentContext SC, ref string CmdLine)`
- L28 _public method_ `public virtual bool PrePackage(ProjectParams Params, DeploymentContext SC, int WorkingCL)`
- L29 _public method_ `public virtual bool Deploy(ProjectParams Params, DeploymentContext SC)`
- L30 _public method_ `public virtual bool PreGetFilesToDeployOrStage(ProjectParams Params, DeploymentContext SC)`
- L31 _public method_ `public virtual bool GetFilesToStageForDLC(ProjectParams Params, DeploymentContext SC)`
- L32 _public method_ `public virtual bool GetFilesToArchive(ProjectParams Params, DeploymentContext SC)`
- L33 _public method_ `public virtual bool PostStagingFileCopy(ProjectParams Params, DeploymentContext SC)`
- L36 _public method_ `public virtual void PostPackage(ProjectParams Params, DeploymentContext SC, int WorkingCL)`
- L37 _public method_ `public virtual void PostGetFilesToDeployOrStage(ProjectParams Params, DeploymentContext SC)`
- L40 _public method_ `public virtual bool? GetPlatformPatchesWithDiffPak(ProjectParams Params, DeploymentContext SC)`
- L41 _public method_ `public virtual IProcessResult RunClient(CommandUtils.ERunOptions ClientRunFlags, string ClientApp, string ClientCmdLine, ProjectParams Params, DeploymentContext SC)`
- L49-86 _public method_ `public static CustomDeploymentHandler Create(string Name, Platform AutomationPlatform, ProjectParams Params, DeploymentContext SC)` — Validate and instantiate the given custom deployment handler
- L88 _private field_ `private static Dictionary<string, Type> HandlerRegistry = ...`
- L88 _private field_ `private static Dictionary< HandlerRegistry = null`

#### class `CustomDeploymentHandlerAttribute`  
`public class CustomDeploymentHandlerAttribute : System.Attribute`  
_public; L98-105_
- attrs: `[System.AttributeUsage(System.AttributeTargets.Class)]`
- inherits: `System.Attribute`
- desc: CustomDeploymentHandler class declarations must be tagged with this, used to find the handler by name
- L100 _public field_ `public string Name`
- L101-104 _public ctor_ `public CustomDeploymentHandlerAttribute( string Name)`

### `Source/Programs/AutomationTool/AutomationUtils/CustomStageCopyHandler.cs` (AutomationUtils.Automation)


#### class `CustomStageCopyHandler`  
`public abstract class CustomStageCopyHandler`  
_public; L12-85_
- L18-21 _public method_ `public virtual bool CanCopyFile(string SourceName)` — Called when copying files to the staging directory.
- L27-30 _public method_ `public virtual bool StageFile(ILogger Logger, string SourceName, string TargetName)` — Called when copying files to the staging directory.
- L36-39 _public method_ `public virtual PluginDescriptor CreateDescriptorForPluginManifest(ILogger Logger, FileReference PluginFile)` — Called when writing plugin descriptor files to the plugin manifest file.
- L41-72 _public method_ `public static CustomStageCopyHandler Create(string Name)`
- L74-77 _public method_ `public virtual void Init(ConfigHierarchy InPlatformEngineConfig)`
- L79 _private field_ `private static Dictionary<string, Type> HandlerRegistry = ...`
- L79 _private field_ `private static Dictionary< HandlerRegistry = null`
- L84 _protected field_ `protected ConfigHierarchy PlatformEngineConfig = null` — Platform engine config hierarchy for the platform being staged.

#### class `CustomStageCopyHandlerAttribute`  
`public class CustomStageCopyHandlerAttribute : System.Attribute`  
_public; L91-98_
- attrs: `[System.AttributeUsage(System.AttributeTargets.Class)]`
- inherits: `System.Attribute`
- desc: CustomStageCopyHandler class declarations must be tagged with this, used to find the handler by name
- L93 _public field_ `public string Name`
- L94-97 _public ctor_ `public CustomStageCopyHandlerAttribute(string Name)`

### `Source/Programs/AutomationTool/AutomationUtils/CustomStagingHandler.cs` (AutomationUtils.Automation)


#### class `CustomStagingHandler`  
`public abstract class CustomStagingHandler`  
_public; L12-111_
- desc: Support for generating custom packages, for example when targeting a specific game store
- L17 _protected method_ `protected abstract bool TryInitialize(ProjectParams Params, DeploymentContext SC)` — Determines whether this custom packaging handler should be used in the given deployment context
- L22 _public method_ `public virtual void GetFilesToStage(ProjectParams Params, DeploymentContext SC)` — Hook for adding additional files for staging.
- L27 _public method_ `public virtual void GetFilesToStageForDLC(ProjectParams Params, DeploymentContext SC)` — Hook for adding additional files for staging when packaging a DLC plugin
- L32 _public method_ `public virtual void PostStagingFileCopy(ProjectParams Params, DeploymentContext SC)` — Hook for when the build has been staged and the list of staged files is available
- L37 _public method_ `public virtual void Package(ProjectParams Params, DeploymentContext SC, int WorkingCL)` — Hook for package generation
- L42 _public method_ `public virtual void GetFilesToArchive(ProjectParams Params, DeploymentContext SC )` — Hook for adding additional files for archiving.
- L48 _public method_ `public virtual bool TryDeploy(ProjectParams Params, DeploymentContext SC)` — Hook for deploying a package we have created
- L53 _public method_ `public virtual IProcessResult TryRunClient(ERunOptions ClientRunFlags, string ClientApp, string ClientCmdLine, ProjectParams Params, DeploymentContext SC)` — Hook for launching a package we have created
- L62-106 _public method_ `public static List<CustomStagingHandler> GetCustomStagingHandlers( ProjectParams Params, DeploymentContext SC)` — Validate and instantiate the given custom staging handlers for the current project. (Note this is returning a List not an IEnumerable to allow the caller to .ForEach() on the handlers)
- L108 _private field_ `private static List<Type> HandlerRegistry = null`

### `Source/Programs/AutomationTool/AutomationUtils/DeploymentContext.cs` (AutomationUtils.Automation)


#### struct `StageTarget`  
`public struct StageTarget`  
_public; L13-17_
- L15 _public field_ `public TargetReceipt Receipt`
- L16 _public field_ `public bool RequireFilesExist`

#### enum `StageFilesSearch`  
`public enum StageFilesSearch`  
_public; L22-33_
- desc: Controls which directories are searched when staging files
- L27 _public* enumerator_ `TopDirectoryOnly` — Only search the top directory
- L32 _public* enumerator_ `AllDirectories` — Search the entire directory tree

#### class `FilesToStage`  
`public class FilesToStage`  
_public; L38-96_
- desc: Contains the set of files to be staged
- L43 _public field_ `public Dictionary<StagedFileReference, FileReference> UFSFiles = ...` — After staging, this is a map from staged file to source file. These file are content, and can go into a pak file.
- L43 _public field_ `public Dictionary< UFSFiles = new Dictionary<StagedFileReference, FileReference>()` — After staging, this is a map from staged file to source file. These file are content, and can go into a pak file.
- L48 _public field_ `public Dictionary<StagedFileReference, FileReference> NonUFSFiles = ...` — After staging, this is a map from staged file to source file. These file are binaries, etc and can't go into a pak file.
- L48 _public field_ `public Dictionary< NonUFSFiles = new Dictionary<StagedFileReference, FileReference>()` — After staging, this is a map from staged file to source file. These file are binaries, etc and can't go into a pak file.
- L53 _public field_ `public Dictionary<StagedFileReference, FileReference> NonUFSDebugFiles = ...` — After staging, this is a map from staged file to source file. These file are for debugging, and should not go into a pak file.
- L53 _public field_ `public Dictionary< NonUFSDebugFiles = new Dictionary<StagedFileReference, FileReference>()` — After staging, this is a map from staged file to source file. These file are for debugging, and should not go into a pak file.
- L58 _public field_ `public Dictionary<StagedFileReference, FileReference> NonUFSSystemFiles = ...` — After staging, this is a map from staged file to source file. These files are system files, and should not be renamed or remapped.
- L58 _public field_ `public Dictionary< NonUFSSystemFiles = new Dictionary<StagedFileReference, FileReference>()` — After staging, this is a map from staged file to source file. These files are system files, and should not be renamed or remapped.
- L66-84 _public method_ `public void Add(StagedFileType FileType, StagedFileReference StagedFile, FileReference InputFile)` — Adds a file to be staged as the given type
- L92-95 _private method_ `private void AddToDictionary(Dictionary<StagedFileReference, FileReference> FilesToStage, StagedFileReference StagedFile, FileReference InputFile)` — Adds a file to be staged to the given dictionary

#### class `ZenCookedFile`  
`public class ZenCookedFile`  
_public; L98-102_
- L100 _public field_ `public string Filename`
- L101 _public field_ `public IoHash ChunkId`

#### class `PackageStoreData`  
`public class PackageStoreData`  
_public; L104-120_
- L106 _public property_ `public ZenServerStoreData ZenServerStore { get; set; }`
- L107 _public property_ `public string ManifestFullPath { get; set; }`
- L108 _public property_ `public string MarkerFullPath { get; set; }`
- L109 _public property_ `public IList<ZenCookedFile> ZenCookedFiles { get; set; }`
- L119 _public property_ `public object ChunkAssignment { get; set; }` — Cached parsed ChunkAssignment op from the cook oplog, populated by ReadZenCookedFilesFromZenServer so downstream consumers (e.g. CreatePaksUsingChunkManifests) can read pakchunk assignment without re-fetching the oplog. Null if the op was absent or the oplog wasn't read with cooked-files loading enabled. Stored as object so DeploymentContext doesn't have to take a dependency on AutomationScripts.Oplog — cast to ChunkAssignmentOp at the use site.

#### class `DeploymentContext`  
`public class DeploymentContext`  
_public; L122-1304_
- L127 _public field_ `public FileReference RawProjectPath` — Full path to the .uproject file
- L132 _public field_ `public bool bStageCrashReporter` — true if we should stage crash reporter
- L137 _public field_ `public string CookPlatform` — CookPlatform, where to get the cooked data from and use for sandboxes
- L142 _public field_ `public string FinalCookPlatform` — FinalCookPlatform, directory to stage and archive the final result to
- L147 _public field_ `public Platform CookSourcePlatform` — Source platform to get the cooked data from
- L152 _public field_ `public Platform StageTargetPlatform` — Target platform used for sandboxes and stage directory names
- L157 _public field_ `public List<UnrealTargetConfiguration> StageTargetConfigurations` — Configurations to stage. Used to determine which ThirdParty configurations to copy.
- L162 _public field_ `public List<StageTarget> StageTargets` — Receipts for the build targets that should be staged.
- L167 _public field_ `public string CustomConfig` — Extra subdirectory to load config files out of, for making multiple types of builds with the same platform
- L172 _public field_ `public CustomDeploymentHandler CustomDeployment = null` — Allows a platform to change how pak files are generated and how it is staged, packaged and deployed - for example, when packaging for a specific game store
- L177 _public field_ `public List<CustomStagingHandler> CustomStagingHandlers = []` — Support for generating custom packages, for example when targeting a specific game store
- L182 _public field_ `public DirectoryReference LocalRoot` — This is the root directory that contains the engine: d:\a\UE\
- L187 _public field_ `public DirectoryReference EngineRoot` — This is the directory that contains the engine.
- L192 _public field_ `public DirectoryReference ProjectRoot` — The directory that contains the project: d:\a\UE\ShooterGame
- L197 _public field_ `public DirectoryReference DLCRoot` — The directory that contains the DLC being processed (or null for non-DLC)
- L203 _public field_ `public List<DirectoryReference> AdditionalPluginDirectories` — The list of AdditionalPluginDirectories from the project.uproject. Files in plugins in these directories are staged into $(StageRoot)/RemappedPlugins/PluginName.
- L208 _public field_ `public string PlatformDir` — raw name used for platform subdirectories Win32
- L213 _public field_ `public DirectoryReference StageDirectory` — Directory to put all of the files in: d:\stagedir\Windows
- L218 _public field_ `public DirectoryReference DebugStageDirectory` — Directory to put all of the debug files in: d:\stagedir\Windows
- L223 _public field_ `public DirectoryReference OptionalFileStageDirectory = null` — Directory to put all of the optional (ie editor only) files in: d:\stagedir\Windows
- L228 _public field_ `public DirectoryReference OptionalFileInputDirectory = null` — Directory to read all of the optional (ie editor only) files from (written earlier with OptionalFileStageDirectory)
- L233 _public field_ `public string CookerSupportFilesSubdirectory = null` — If this is specified, any files written into the receipt with the CookerSupportFiles tag will be copied into here during staging
- L238 _public field_ `public StagedDirectoryReference RelativeProjectRootForStage` — Directory name for staged projects
- L243 _public field_ `public string ProjectArgForCommandLines` — This is what you use to test the engine which uproject you want. Many cases.
- L248 _public field_ `public DirectoryReference CookSourceRuntimeRootDir` — The directory containing the cooked data to be staged. This may be different to the target platform, eg. when creating cooked data for dedicated servers.
- L253 _public field_ `public DirectoryReference RuntimeRootDir` — This is the root that we are going to run from. This will be the stage directory if we're staging, or the input directory if not.
- L258 _public field_ `public DirectoryReference RuntimeProjectRootDir` — This is the project root that we are going to run from. Many cases.
- L263 _public field_ `public DirectoryReference MetadataDir` — The directory containing the metadata from the cooker
- L268 _public field_ `public DirectoryReference PlatformCookDir` — The directory containing the cooker generated data for this platform
- L273 _public field_ `public List<string> StageExecutables` — List of executables we are going to stage
- L278 _public const_ `public const string UProjectCommandLineArgInternalRoot = "../../../"` — Probably going away, used to construct ProjectArgForCommandLines in the case that we are running staged
- L283 _public field_ `public string PakFileInternalRoot = "../../../"` — Probably going away, used to construct the pak file list
- L288 _public field_ `public PackageStoreData PackageStoreData` — Cooked package store data if available
- L293 _public field_ `public FilesToStage FilesToStage = new FilesToStage()` — List of files to be staged
- L298 _public field_ `public Dictionary<StagedFileReference, FileReference> CrashReporterUFSFiles = ...` — Map of staged crash reporter file to source location
- L298 _public field_ `public Dictionary< CrashReporterUFSFiles = new Dictionary<StagedFileReference, FileReference>()` — Map of staged crash reporter file to source location
- L303 _public field_ `public Dictionary<string, string> ArchivedFiles = ...` — List of files to be archived
- L303 _public field_ `public Dictionary< ArchivedFiles = new Dictionary<string, string>()` — List of files to be archived
- L308 _public field_ `public HashSet<string> RestrictedFolderNames = new HashSet<string>(StringComparer.OrdinalIgnoreCase)` — List of restricted folder names which are not permitted in staged build
- L314 _public field_ `public List<Tuple<StagedDirectoryReference, StagedDirectoryReference>> RemapDirectories = ...` — List of directories to remap during staging, allowing moving files to different final paths This list is read from the +RemapDirectories=(From=, To=) array in the [Staging] section of *Game.ini files
- L314 _public field_ `public List<Tuple< RemapDirectories = new List<Tuple<StagedDirectoryReference, StagedDirectoryReference>>()` — List of directories to remap during staging, allowing moving files to different final paths This list is read from the +RemapDirectories=(From=, To=) array in the [Staging] section of *Game.ini files
- L320 _public field_ `public List<StagedDirectoryReference> DirectoriesAllowList = new List<StagedDirectoryReference>()` — List of directories to allow staging, even if they contain restricted folder names This list is read from the +AllowedDirectories=... array in the [Staging] section of *Game.ini files
- L326 _public field_ `public HashSet<StagedFileReference> ConfigFilesAllowList = new HashSet<StagedFileReference>()` — Set of config files which are allow listed to be staged. By default, we warn for config files which are not well known to prevent internal data (eg. editor/server settings) leaking in packaged builds. This list is read from the +AllowedConfigFiles=... array in the [Staging] section of *Game.ini files.
- L332 _public field_ `public HashSet<StagedFileReference> ConfigFilesDenyList = new HashSet<StagedFileReference>()` — Set of config files which are denied from staging. By default, we warn for config files which are not well known to prevent internal data (eg. editor/server settings) leaking in packaged builds. This list is read from the +DisallowedConfigFiles=... array in the [Staging] section of *Game.ini files.
- L338 _public field_ `public HashSet<StagedFileReference> ExtraFilesAllowList = new HashSet<StagedFileReference>()` — Set files which are allow listed to be staged that would otherwise be excluded by RestrictedFolderNames. This list is read from the +ExtraAllowedFiles=... array in the [Staging] section of *Game.ini files.
- L344 _public field_ `public CustomStageCopyHandler CustomStageCopyHandler = null` — Optional stage handler that during CopyOrWriteManifestFilesToStageDir will handle the copy operation of files and creation of the plugin manifest file.
- L349 _public field_ `public List<string> IniKeyDenyList = null` — List of ini keys to strip when staging
- L354 _public field_ `public List<string> IniSectionDenyList = null` — List of ini sections to strip when staging
- L359 _public field_ `public List<string> IniSuffixAllowList = null` — List of ini suffixes to always stage
- L364 _public field_ `public List<string> IniSuffixDenyList = null` — List of ini suffixes to never stage
- L370 _public field_ `public List<string> LocalizationTargetsDenyList = new List<string>()` — List of localization targets that are not included in staged build. By default, all project Content/Localization targets are automatically staged. This list is read from the +DisallowedLocalizationTargets=... array in the [Staging] section of *Game.ini files.
- L375 _public field_ `public DirectoryReference ArchiveDirectory` — Directory to archive all of the files in: d:\archivedir\Windows
- L380 _public field_ `public DirectoryReference ProjectBinariesFolder` — Directory to project binaries
- L385 _public field_ `public bool DedicatedServer` — The client connects to dedicated server to get data
- L390 _public field_ `public bool Stage` — True if this build is staged
- L395 _public field_ `public bool Archive` — True if this build is archived
- L400 _public field_ `public bool IsCodeBasedProject` — True if this project has code
- L405 _public field_ `public string ShortProjectName` — Project name (name of the uproject file without extension or directory name where the project is localed)
- L410 _public field_ `public bool bIsCombiningMultiplePlatforms = false` — If true, multiple platforms are being merged together - some behavior needs to change (but not much)
- L415 _public field_ `public bool PlatformUsesChunkManifests = false` — If true if this platform is using streaming install chunk manifests
- L420 _public field_ `public bool OnlyAllowPackagesFromStdCookPathInIoStore = false` — Temporary setting to exclude non cooked packages from I/O store container file(s)
- L425 _public field_ `public bool UsePakFileRulesIni = true` — Allows a target to ignore PakFileRules.ini when the project rules are still needed for most cases
- L427-717 _public ctor_ `public DeploymentContext( FileReference RawProjectPathOrName, DirectoryReference InLocalRoot, DirectoryReference BaseStageDirectory, DirectoryReference OptionalFileStageDirectory, DirectoryReference OptionalFileInputDirectory, DirectoryReference BaseArchiveDirectory, string CookerSupportFilesSubdirectory, Platform InSourcePlatform, Platform InTargetPlatform, List<UnrealTargetConfiguration> InTargetConfigurations, IEnumerable<StageTarget> InStageTargets, List<String> InStageExecutables, bool InServer, bool InCooked, bool InStageCrashReporter, bool InStage, bool InCookOnTheFly, bool InArchive, bool InProgram, bool IsClientInsteadOfNoEditor, bool InForceChunkManifests, bool InSeparateDebugStageDirectory, DirectoryReference InDLCRoot, List<DirectoryReference> InAdditionalPluginDirectories )`
- L726-736 _private method_ `private static void ReadAllowDenyFileList(ConfigHierarchy Config, string SectionName, string KeyName, HashSet<StagedFileReference> FilesRef)` — Read a list of allowed or denied files names from a config file
- L744-747 _public method_ `public List<FileReference> FindFilesToStage(DirectoryReference BaseDir, StageFilesSearch Option)` — Finds files to stage under a given base directory.
- L756-761 _public method_ `public List<FileReference> FindFilesToStage(DirectoryReference BaseDir, string Pattern, StageFilesSearch Option)` — Finds files to stage under a given base directory.
- L770-793 _private method_ `private void FindFilesToStageInternal(DirectoryReference BaseDir, string Pattern, StageFilesSearch Option, List<FileReference> Files)` — Finds files to stage under a given base directory.
- L800-832 _public method_ `public StagedFileReference GetStagedFileLocation(FileReference InputFile)` — Gets the default location to stage an input file
- L839-843 _public method_ `public void StageFile(StagedFileType FileType, FileReference InputFile)` — Stage a single file to its default location
- L851-854 _public method_ `public void StageFile(StagedFileType FileType, FileReference InputFile, StagedFileReference OutputFile)` — Stage a single file
- L861-867 _public method_ `public void StageFiles(StagedFileType FileType, IEnumerable<FileReference> Files)` — Stage multiple files
- L876-883 _public method_ `public void StageFiles(StagedFileType FileType, DirectoryReference InputDir, IEnumerable<FileReference> Files, StagedDirectoryReference OutputDir)` — Stage multiple files
- L891-894 _public method_ `public void StageFiles(StagedFileType FileType, DirectoryReference InputDir, StageFilesSearch Option)` — Stage multiple files
- L903-906 _public method_ `public void StageFiles(StagedFileType FileType, DirectoryReference InputDir, StageFilesSearch Option, StagedDirectoryReference OutputDir)` — Stage multiple files
- L915-922 _public method_ `public void StageFiles(StagedFileType FileType, DirectoryReference InputDir, string Pattern, StageFilesSearch Option)` — Stage multiple files
- L932-940 _public method_ `public void StageFiles(StagedFileType FileType, DirectoryReference InputDir, string Pattern, StageFilesSearch Option, StagedDirectoryReference OutputDir)` — Stage multiple files
- L948-958 _public method_ `public void StageCrashReporterFile(StagedFileType FileType, FileReference InputFile, StagedFileReference StagedFile)` — Stages a file for use by crash reporter.
- L966-969 _public method_ `public void StageCrashReporterFiles(StagedFileType FileType, DirectoryReference InputDir, StageFilesSearch Option)` — Stage multiple files for use by crash reporter
- L978-986 _public method_ `public void StageCrashReporterFiles(StagedFileType FileType, DirectoryReference InputDir, StageFilesSearch Option, StagedDirectoryReference OutputDir)` — Stage multiple files for use by crash reporter
- L988-991 _public method_ `public void StageVulkanValidationLayerFiles(ProjectParams Params, StagedFileType FileType, DirectoryReference InputDir, StageFilesSearch Option)`
- L993-1006 _public method_ `public void StageVulkanValidationLayerFiles(ProjectParams Params, StagedFileType FileType, DirectoryReference InputDir, StageFilesSearch Option, StagedDirectoryReference OutputDir)`
- L1008-1038 _public method_ `public void StageBuildProductsFromReceipt(TargetReceipt Receipt, bool RequireDependenciesToExist, bool TreatNonShippingBinariesAsDebugFiles)`
- L1040-1056 _public method_ `public void StageRuntimeDependenciesFromReceipt(TargetReceipt Receipt, bool RequireDependenciesToExist, bool bUsingPakFile)`
- L1058-1167 _public method_ `public int ArchiveFiles(string InPath, string Wildcard = "*", bool bRecursive = true, string[] ExcludeWildcard = null, string NewPath = null, UnrealTargetPlatform[] AdditionalPlatforms = null)`
- L1169-1180 _private method_ `private static string GetSanitizedDeviceNameSuffix(string DeviceName)`
- L1182-1185 _public method_ `public string GetUFSDeploymentDeltaPath(string DeviceName)`
- L1187-1190 _public method_ `public string GetNonUFSDeploymentDeltaPath(string DeviceName)`
- L1192-1195 _public method_ `public string GetUFSDeploymentObsoletePath(string DeviceName)`
- L1197-1200 _public method_ `public string GetNonUFSDeploymentObsoletePath(string DeviceName)`
- L1202-1205 _public method_ `public string GetNonUFSDeployedManifestFileName(string DeviceName)`
- L1207-1210 _public method_ `public string GetUFSDeployedManifestFileName(string DeviceName)`
- L1212-1224 _public method_ `public static StagedFileReference ApplyDirectoryRemap(DeploymentContext SC, StagedFileReference InputFile)`
- L1226-1229 _public method_ `public static StagedFileReference MakeRelativeStagedReference(DeploymentContext SC, FileSystemReference Ref)`
- L1231-1265 _public method_ `public static StagedFileReference MakeRelativeStagedReference(DeploymentContext SC, FileSystemReference Ref, out DirectoryReference RootDir)`
- L1266-1303 _public method_ `public static FileReference UnmakeRelativeStagedReference(DeploymentContext SC, StagedFileReference Ref)`

### `Source/Programs/AutomationTool/AutomationUtils/DeviceReservation.cs` (AutomationUtils.Automation)


#### class `AutomationTool.DeviceReservation.DeviceReservationAutoRenew`  
`public sealed class DeviceReservationAutoRenew : IDisposable`  
_public; L26-171_
- inherits: `IDisposable`
- desc: Co-operatively reserves remote devices for build automation. The constructor blocks until the specified type and number of devices are available. The reservation is automatically renewed for the lifetime of this object, and released when the object is disposed or garbage collected.
- L28 _private field_ `private Uri ReservationBaseUri`
- L30 _private field_ `private static readonly TimeSpan ReserveTime = TimeSpan.FromMinutes(10)`
- L31 _private field_ `private static readonly TimeSpan RenewTime = TimeSpan.FromMinutes(5)`
- L34 _private field_ `private static readonly int RenewRetryMax = 14`
- L35 _private field_ `private static readonly TimeSpan RenewRetryTime = TimeSpan.FromMinutes(1)`
- L37 _private field_ `private Thread RenewThread`
- L38 _private field_ `private AutoResetEvent WaitEvent = new AutoResetEvent(false)`
- L40 _private field_ `private Reservation ActiveReservation`
- L41 _private field_ `private List<Device> ReservedDevices`
- L47 _public property_ `public bool ForceDelete { get; set; }` — When true, the ActiveReservation will be force deleted upon termination of the auto renewal thread Force deleted reservations will clear any associated reservation blocks, regardless of the active step
- L52 _public property_ `public bool? InstallRequired => ...` — Whether the reservation requires an installation
- L54-61 _public property_ `public IReadOnlyList<Device> Devices { get; }`
- L71-80 _public ctor_ `public DeviceReservationAutoRenew(string InReservationBaseUri, int RetryMax, string PoolID, params string[] InDeviceTypes)` — Creates a device reservation for the specified type and number of devices. Blocks until the devices are available.
- L88-93 _public ctor_ `public DeviceReservationAutoRenew(string InReservationBaseUri, Reservation Reservation)` — Creates a device reservation for the specified type and number of devices. Blocks until the devices are available.
- L95-106 _private method_ `private void StartRenewThread()`
- L108-149 _private method_ `private void DoAutoRenew()`
- L151-159 _private method_ `private void StopAutoRenew()`
- L161-164 _private* dtor_ `~DeviceReservationAutoRenew()`
- L166-170 _public method_ `public void Dispose()`

#### class `AutomationTool.DeviceReservation.Utils`  
`public static class Utils`  
_public; L173-255_
- L176 _public field_ `static public ILogger Logger = EpicGames.Core.Log.Logger`
- L178-183 _public method_ `public static Uri AppendPath(this Uri BaseUri, string NewPath)`
- L185-190 _public method_ `public static Uri AppendQuery(this Uri BaseUri, string NewQuery)`
- L192-223 _public method_ `public static T InvokeAPI<T>(Uri UriToRequest, string Method, object ObjectToSerialize)`
- L225-254 _public method_ `public static void InvokeAPI(Uri UriToRequest, string Method, object ObjectToSerialize = null)`

#### class `AutomationTool.DeviceReservation.Reservation`  
`public sealed class Reservation`  
_public; L257-582_
- L259 _public property_ `public string[] DeviceNames { get; set; }`
- L260 _public property_ `public string HostName { get; set; }`
- L261 _public property_ `public DateTime StartDateTime { get; set; }`
- L262 _public property_ `public TimeSpan Duration { get; set; }`
- L263 _public property_ `public Guid Guid { get; set; }`
- L264 _public field_ `public static string ReservationDetails = ""`
- L265 _public property_ `public bool? InstallRequired { get; set; }`
- L267 _private* field_ `static readonly Utf8String DeviceIdAnnotation = new Utf8String("DeviceId")`
- L442-516 _public method_ `public static Reservation Create(Uri BaseUri, string[] DeviceTypes, TimeSpan Duration, int RetryMax = 5, string PoolID = "", string DeviceName = "", Tags Tags = null)`
- L518-542 _private method_ `private static string GetReservationErrorMessage(WebException WebEx, string RetryMessage = "")`
- L544-547 _public method_ `public void Renew(Uri BaseUri, TimeSpan NewDuration)`
- L549-559 _public method_ `public void Delete(Uri BaseUri, bool Force = false)`
- L561-580 _public method_ `static public void ReportDeviceError(string InBaseUri, string DeviceName, string Error)`

#### class `AutomationTool.DeviceReservation.Reservation.CreateReservationData`  
`private sealed class CreateReservationData`  
_private; L269-280_
- L271 _public property_ `public string[] DeviceTypes { get; set; }`
- L272 _public property_ `public string Hostname { get; set; }`
- L273 _public property_ `public TimeSpan Duration { get; set; }`
- L274 _public property_ `public string ReservationDetails { get; set; }`
- L275 _public property_ `public string PoolId { get; set; }`
- L276 _public property_ `public string JobId { get; set; }`
- L277 _public property_ `public string StepId { get; set; }`
- L278 _public property_ `public string DeviceName { get; set; }`
- L279 _public property_ `public Tags Tags { get; set; }`

#### class `AutomationTool.DeviceReservation.Reservation.Tags`  
`public class Tags : ICloneable`  
_public; L282-435_
- inherits: `ICloneable`
- L298-317 _public method_ `public void AddTag(string Tag, Type TagType)` — Adds a tag to the request
- L325-331 _public method_ `public void AddTags(IEnumerable<string> Tags, Type TagType)` — Adds multiple tags to the request
- L336 _public property_ `public IReadOnlyList<string> RequiredTags => ...` — Required tags
- L341 _public property_ `public IReadOnlyList<string> PreferredTags => ...` — Preferred Tags
- L346 _public property_ `public IReadOnlyList<string> UndesiredTags => ...` — Undesired Tags
- L351 _public property_ `public IReadOnlyList<string> BlockedTags => ...` — Blocked Tags
- L356 _private property_ `private List<string> Required { get; set; }` — Devices that do not have this tag will not be reserved
- L361 _private property_ `private List<string> Preferred { get; set; }` — Devices that have this tag will be selected over devices that do not, provided at least one is available
- L366 _private property_ `private List<string> Undesired { get; set; }` — Devices that have this tag will be de-prioritized over devices that do not
- L371 _private property_ `private List<string> Blocked { get; set; }` — Devices that have this tag will not be reserved
- L373-379 _public method_ `public override string ToString()`
- L381-394 _public method_ `public override bool Equals(object OtherObj)`
- L396-399 _public method_ `public override int GetHashCode()`
- L401 _private* method_ `object ICloneable.Clone()`
- L402-410 _public method_ `public Tags Clone()`
- L416-419 _public method_ `public bool Any()` — Does this Tag request have any tags associated with it
- L421-427 _private method_ `private void Add(string Tag, List<string> TagList)`
- L429-434 _private method_ `private string FormatTag(string Tag)`

#### enum `AutomationTool.DeviceReservation.Reservation.Tags.Type`  
`public enum Type`  
_public; L284-290_
- L286 _public* enumerator_ `Required`
- L287 _public* enumerator_ `Preferred`
- L288 _public* enumerator_ `Undesired`
- L289 _public* enumerator_ `Blocked`

#### class `AutomationTool.DeviceReservation.Reservation.DeviceErrorRequest`  
`public sealed class DeviceErrorRequest`  
_public; L437-440_
- L439 _public property_ `public string Message { get; set; }`

#### class `AutomationTool.DeviceReservation.Device`  
`public sealed class Device`  
_public; L584-603_
- L586 _public property_ `public string Name { get; set; }`
- L587 _public property_ `public string Type { get; set; }`
- L588 _public property_ `public string IPOrHostName { get; set; }`
- L589 _public property_ `public string PerfSpec { get; set; }`
- L590 _public property_ `public string Model { get; set; }`
- L591 _public property_ `public TimeSpan AvailableStartTime { get; set; }`
- L592 _public property_ `public TimeSpan AvailableEndTime { get; set; }`
- L593 _public property_ `public bool Enabled { get; set; }`
- L594 _public property_ `public string DeviceData { get; set; }`
- L595 _public property_ `public List<string> Tags { get; set; }`
- L597 _public method_ `public Device Clone()`
- L599-602 _public method_ `public static Device Get(Uri BaseUri, string DeviceName)`

#### class `AutomationTool.DeviceReservation.TimeSpanJsonConverter`  
`public class TimeSpanJsonConverter : JsonConverter<TimeSpan>`  
_public; L605-622_
- inherits: `JsonConverter<TimeSpan>`
- L607-610 _public method_ `public override bool CanConvert(Type ObjectType)`
- L612-615 _public method_ `public override TimeSpan Read(ref Utf8JsonReader Reader, Type TypeToConvert, JsonSerializerOptions Options)`
- L617-621 _public method_ `public override void Write(Utf8JsonWriter Writer, TimeSpan Value, JsonSerializerOptions Options)`

### `Source/Programs/AutomationTool/AutomationUtils/Distiller.cs` (AutomationUtils.Automation)


#### class `AutomationTool.CommandUtils`  
`public partial class CommandUtils`  
_public; L11-48_
- L19-32 _public method_ `public static string StripBaseDirectory(string InFilePath, string InBaseDirectory)` — Given a path to a file, strips off the base directory part of the path
- L42-47 _public method_ `public static string MakeRerootedFilePath(string FilePath, string BaseDirectory, string NewBaseDirectory)` — Given a path to a "source" file, re-roots the file path to be located under the "destination" folder. The part of the source file's path after the root folder is unchanged.

### `Source/Programs/AutomationTool/AutomationUtils/FileRegions.cs` (AutomationUtils.Automation)


#### enum `AutomationTool.FileRegionType`  
`public enum FileRegionType : byte`  
_public; L17-25_
- inherits: `byte`
- desc: Provides an identifier for the type of data within a given file region. NOTE: Enum values here must match those in Serialization/FileRegions.h
- L19 _public* enumerator_ `None = 0`
- L20 _public* enumerator_ `BC1 = 2`
- L21 _public* enumerator_ `BC2 = 5`
- L22 _public* enumerator_ `BC3 = 6`
- L23 _public* enumerator_ `BC4 = 3`
- L24 _public* enumerator_ `BC5 = 7`

#### struct `AutomationTool.FileRegion`  
`public struct FileRegion`  
_public; L27-93_
- L29 _public const_ `public const string RegionsFileExtension = ".uregs"`
- L31 _public field_ `public ulong Offset`
- L32 _public field_ `public ulong Length`
- L33 _public field_ `public FileRegionType Type`
- L35-60 _public method_ `public static List<FileRegion> ReadRegionsFromFile(string Filename)`
- L62-92 _public method_ `public static void PrintSummaryTable(IEnumerable<FileRegion> Regions)`

### `Source/Programs/AutomationTool/AutomationUtils/GoogleDriveHelper.cs` (AutomationUtils.Automation)


#### enum `DriveHelper.MIMETypes`  
`public enum MIMETypes`  
_public; L30-79_
- desc: File formats that we support. These are used with a ToString() to get the actual MIME Type string used in our API calls. Note: The MIME Types for some of these support a conversion to Google Docs and may not be the "pure" types. For example: CSV will only recognize the first sheet of a given spreadsheet. In many cases, it may be safer to use either PlainText or BinaryDefault rather than your specific format to ensure that the file is uploaded correctly. If you wish to add a new type, also add a return case to the ToString() function below.
- L32 _public* enumerator_ `Audio`
- L33 _public* enumerator_ `Photo`
- L34 _public* enumerator_ `Video`
- L35 _public* enumerator_ `Unknown`
- L36 _public* enumerator_ `GoogleAppScripts`
- L37 _public* enumerator_ `GoogleDocs`
- L38 _public* enumerator_ `GoogleDrawing`
- L39 _public* enumerator_ `GoogleForms`
- L40 _public* enumerator_ `GoogleFusionTables`
- L41 _public* enumerator_ `GoogleMyMaps`
- L42 _public* enumerator_ `GoogleSites`
- L43 _public* enumerator_ `GoogleSlides`
- L44 _public* enumerator_ `GoogleSheets`
- L45 _public* enumerator_ `GoogleDriveFile`
- L46 _public* enumerator_ `GoogleDriveFolder`
- L47 _public* enumerator_ `ThirdPartyShortcut`
- L48 _public* enumerator_ `MSExcel_XLS`
- L49 _public* enumerator_ `MSExcel_XLSX`
- L50 _public* enumerator_ `MSPowerPoint`
- L51 _public* enumerator_ `MSWord_DOC`
- L52 _public* enumerator_ `MSWord_DOCX`
- L53 _public* enumerator_ `OpenOfficeDoc`
- L54 _public* enumerator_ `OpenOfficePresentation`
- L55 _public* enumerator_ `OpenOfficeSheet`
- L56 _public* enumerator_ `PlainText`
- L57 _public* enumerator_ `RichText`
- L58 _public* enumerator_ `HTML`
- L59 _public* enumerator_ `ZippedHTML`
- L60 _public* enumerator_ `XML`
- L61 _public* enumerator_ `JS`
- L62 _public* enumerator_ `PHP`
- L63 _public* enumerator_ `PDF`
- L64 _public* enumerator_ `EPUB`
- L65 _public* enumerator_ `CSV`
- L66 _public* enumerator_ `TSV`
- L67 _public* enumerator_ `JPEG`
- L68 _public* enumerator_ `PNG`
- L69 _public* enumerator_ `SVG`
- L70 _public* enumerator_ `GIF`
- L71 _public* enumerator_ `BMP`
- L72 _public* enumerator_ `ZIP`
- L73 _public* enumerator_ `RAR`
- L74 _public* enumerator_ `TAR`
- L75 _public* enumerator_ `ARJ`
- L76 _public* enumerator_ `CAB`
- L77 _public* enumerator_ `MP3`
- L78 _public* enumerator_ `BinaryDefault`

#### class `DriveHelper.MIMETypesExtensions`  
`public static class MIMETypesExtensions`  
_public; L81-190_
- L87-189 _public method_ `public static string ToMimeString(this MIMETypes Type)` — Returns the properly formatted MIME Type string as opposed to a string that matches the enum value's name. For example: An argument of 'MIMETypes.PlainText' returns "text/plain".

#### class `DriveHelper.DriveServiceHelper`  
`public class DriveServiceHelper`  
_public; L192-569_
- L195 _protected field_ `protected static string[] Scopes = { DriveService.Scope.Drive }`
- L197-200 _public property_ `public DriveService Service { get; set; }`
- L205-232 _public ctor_ `public DriveServiceHelper(string AppName, string SecretKeyPath, string CredentialPath)` — A helper class that wraps a DriveService with the given auth credentials and provides common functions such as UploadFile()
- L239-268 _public method_ `public string CreateFolder(string FolderName, string ParentFolderId = "")` — Creates a new folder and returns the new folder's ID. Creates the folder within a parent folder if ParentFolderId is specified.
- L273-278 _public method_ `public bool DoesFileExist(string FileID)` — Returns true if a file exists with the given ID. This attempts to get the file then does a null check, so if your intention is to get the file if it exists, you may want to use GetFile() and null check the result instead for fewer API requests.
- L283-304 _public method_ `public void DownloadFile(string FileID, string DestinationFilePathAndName)` — Downloads a file to memory then creates a new file for it at the given file path
- L310-331 _public method_ `public void DownloadGoogleDoc(string FileID, string DestinationFilePathAndName, MIMETypes ExportFormat)` — Downloads a file to memory then creates a new file for it at the given path with a file type to match the ExportFormat. Note: This function expects the downloaded file to be one of the Google Docs types such as a Document or Sheet and the ExportFormat must be supported for that type.
- L334-381 _protected method_ `protected void HandleDownloadProgressAndCreateFileOnComplete(ref DateTime TimeStamp, ref long Percent, FileStream FileStream, long FileSize, Google.Apis.Download.IDownloadProgress Progress, string DestinationFilePathAndName)`
- L386-412 _public method_ `public Google.Apis.Drive.v3.Data.File GetFile(string FileID, IList<string> Fields)` — Gets a metadata File object (with specified fields) for the file with the given FileID
- L418-429 _public method_ `public bool TryGetFileID(string FileName, out string OutFileID)` — Searches for a file by name and outputs its ID to OutFileID. Returns true if only exactly one file with the matching name was found. Otherwise, does not set the OutFileID.
- L435-438 _public method_ `public DriveFolderWrapper GetNewFolderWrapper(string FolderID)` — Creates a new wrapper class for a folder with the given ID. Will not fail if a folder with the ID does not exist, so check NewFolder.Exists and call CreateFolder() if necessary.
- L443-462 _public method_ `public void MoveFile(string FileID, string DestinationFolderID)` — Changes a file's parent folder to the desired folder by ID
- L468-490 _public method_ `public List<Google.Apis.Drive.v3.Data.File> SearchFiles(string SearchQuery)` — Calls a ListRequest with the given SearchQuery string. For more info on Google Drive's search queries, refer to: https://developers.google.com/drive/v3/web/search-parameters
- L495-498 _public method_ `public List<Google.Apis.Drive.v3.Data.File> SearchFilesByName(string FileName)` — Searches for files with names that match the given FileName. May return no results if matching files are not found.
- L504-519 _public method_ `public List<Google.Apis.Drive.v3.Data.TeamDrive> SearchDrives(string SearchQuery)` — Calls a ListRequest with the given SearchQuery string. For more info on Google Drive's search queries, refer to: https://developers.google.com/drive/v3/web/search-parameters
- L524-530 _public method_ `public Google.Apis.Drive.v3.Data.TeamDrive SearchForDriveByName(string DriveName)` — Searches a drives with the name that match the given FileName. May return no results if matching drives are not found.
- L535-568 _public method_ `public string UploadFile(FileInfo FileToUpload, string UploadedFileName, string DestinationFolderID, MIMETypes FileType)` — Uploads the given file to the destination with the given new name and returns the new ID. Returns an empty string and logs a warning if the upload fails.

#### class `DriveHelper.DriveFolderWrapper`  
`public class DriveFolderWrapper`  
_public; L571-670_
- L574 _protected field_ `protected DriveServiceHelper ServiceHelper`
- L578-584 _public property_ `public bool Exists { get; }` — Whether a file with the matching FolderID exists
- L589-592 _public property_ `public string FolderID { get; set; }` — The file ID for our wrapped folder. Not guaranteed to represent an existing folder in the Drive.
- L597-602 _public ctor_ `public DriveFolderWrapper(DriveServiceHelper InServiceHelper, string ExistingFolderID)` — A convenient wrapper that represents an existing folder in Google Drive and provides common functions one may need in the context of working within that folder.
- L607-612 _public ctor_ `public DriveFolderWrapper(DriveServiceHelper InServiceHelper, string NewFolderName, string ParentFolderID)` — A convenient wrapper that creates a new folder in Google Drive and provides common functions one may need in the context of working within that folder.
- L617-620 _public method_ `public string CreateSubFolder(string FolderName)` — Creates a new folder within this folder and returns the new folder's ID.
- L625-628 _public method_ `public Google.Apis.Drive.v3.Data.File Get()` — Gets a file metadata object that represents the wrapped folder (which is not guaranteed to exist)
- L633-644 _public method_ `public bool ContainsFileNamed(string FileName)` — Returns true if any file within this folder has the exact FileName
- L649-652 _public method_ `public List<Google.Apis.Drive.v3.Data.File> ListFiles()` — Returns metadata objects for all files whose parents include this folder
- L657-660 _public method_ `public string UploadFile(FileInfo FileToUpload, MIMETypes FileType)` — Uploads a file to the wrapped Google Drive folder
- L665-668 _public method_ `public string UploadFile(FileInfo FileToUpload, string UploadedFileName, MIMETypes FileType)` — Uploads a file as the given UploadedFileName to the wrapped Google Drive folder

### `Source/Programs/AutomationTool/AutomationUtils/GoogleSheetsHelper.cs` (AutomationUtils.Automation)


#### enum `SheetsHelper.ESheetsDimension`  
`public enum ESheetsDimension`  
_public; L19-23_
- L21 _public* enumerator_ `ROWS`
- L22 _public* enumerator_ `COLUMNS`

#### enum `SheetsHelper.ESheetsValueInputOption`  
`public enum ESheetsValueInputOption`  
_public; L25-29_
- L27 _public* enumerator_ `RAW`
- L28 _public* enumerator_ `USER_ENTERED`

#### enum `SheetsHelper.EAuthTokenType`  
`public enum EAuthTokenType`  
_public; L31-35_
- L33 _public* enumerator_ `UserToken`
- L34 _public* enumerator_ `ServiceAccountToken`

#### class `SheetsHelper.SheetsUtils`  
`public class SheetsUtils`  
_public; L37-91_
- L39 _private field_ `private static DateTime QuotaTimeStart = new DateTime(0)`
- L40 _private field_ `private static int QuotaRequestCount = 0`
- L41 _private field_ `private static int MAX_QUERY_COUNT = 100`
- L42 _private field_ `private static int MAX_QUERY_SECONDS = 100`
- L46-72 _public method_ `public static void TryCheckQuotaSync()`
- L77-90 _public method_ `public static string ColumnIndexToA1(int ColumnIndex)` — Converts a zero-based index into a string in A1 notation. Example: ColumnIndex = 27 should return "AB".

#### class `SheetsHelper.SpreadSheetWrapper`  
`public class SpreadSheetWrapper`  
_public; L93-425_
- L95 _protected field_ `protected Spreadsheet SourceSpreadsheet`
- L96 _protected field_ `protected SheetsService Service`
- L97 _protected field_ `protected string SpreadsheetID`
- L98 _protected field_ `protected BatchUpdateSpreadsheetRequest UpdateSpreadsheetBatchRequest`
- L99 _protected field_ `protected BatchUpdateValuesRequest UpdateValuesBatchRequest`
- L101-171 _public ctor_ `public SpreadSheetWrapper(string AppTitle, string SecretKeyPath, string CredentialPath, string InSpreadsheetID, EAuthTokenType TokenType = EAuthTokenType.UserToken)`
- L173-177 _public method_ `public void Refresh()`
- L180-190 _public method_ `public SheetWrapper GetSheet(string Title)`
- L193-205 _public method_ `public SheetWrapper GetSheetByName(string Title)`
- L208-214 _public method_ `public bool SheetExists(string Title)`
- L217-235 _public method_ `public void DeleteSheet(string Title)`
- L238-254 _public method_ `public SheetWrapper AddSheet(string Title, int Index = 0)`
- L256-272 _public method_ `public SheetWrapper AddSheetAtNextIndexAlphabetically(string Title, int StartIndex = 0)`
- L277-290 _public method_ `public void BatchAddSheet(string Title, int index = 0)` — Queues a new request to add a new sheet to the spreadsheet. Call FlushSpreadsheetBatchRequest() to execute all queued spreadsheet requests.
- L295-317 _public method_ `public void BatchAppendDimension(SheetWrapper Sheet, int RowsOrColumnsToAppend = 1, ESheetsDimension Dimension = ESheetsDimension.ROWS)` — Queues a new request to append new columns or rows. Call FlushSpreadsheetBatchRequest() to execute all queued spreadsheet requests.
- L322-351 _public method_ `public void BatchInsertDimension(SheetWrapper Sheet, int RowsOrColumnsToAppend = 1, int StartIndex = 0, ESheetsDimension Dimension = ESheetsDimension.ROWS, bool? bInheritFromBefore = null)` — Queues a new request to insert new columns or rows. Call FlushSpreadsheetBatchRequest() to execute all queued spreadsheet requests.
- L356-370 _public method_ `public void BatchUpdateValueRange(SheetWrapper Sheet, string A1Range, IList<IList<object>> Values, ESheetsDimension MajorDimensions = ESheetsDimension.ROWS)` — Queues a new request to set the values of a range of cells. Call FlushValuesBatchRequest() to execute all queued value requests.
- L375-378 _public method_ `public void BatchUpdateCellValue(SheetWrapper Sheet, string A1Cell, object Value)` — Queues a new request to set the value of a specific cell. Call FlushValuesBatchRequest() to execute all queued value requests.
- L384-388 _public method_ `public void FlushBatchRequests()` — Convenience method to flush batched spreadsheet and then values requests without returning a response. Avoid using this when you have both inserts and updates batched as the inserts will happen first and the updates may apply to unintended cells.
- L393-407 _public method_ `public BatchUpdateSpreadsheetResponse FlushSpreadsheetBatchRequest()` — Executes all queued spreadsheet requests in a single batched call
- L412-424 _public method_ `public BatchUpdateValuesResponse FlushValuesBatchRequest(ESheetsValueInputOption ValueInputOption = ESheetsValueInputOption.USER_ENTERED)` — Executes all queued values requests in a single batched call

#### class `SheetsHelper.SheetWrapper`  
`public class SheetWrapper`  
_public; L427-594_
- L429 _public property_ `public SheetsService Service { get; set; }`
- L431 _public property_ `public string SpreadsheetID { get; set; }`
- L433 _public property_ `public Sheet SourceSheet { get; set; }`
- L435-438 _public property_ `public SheetProperties Properties { get; }`
- L440-443 _public property_ `public int ColumnCount { get; }`
- L445-448 _public property_ `public int RowCount { get; }`
- L450-453 _public property_ `public int SheetID { get; }`
- L455-458 _public property_ `public string Title { get; }`
- L460-465 _public ctor_ `public SheetWrapper(SheetsService InService, string InSpreadsheetID, Sheet InSheet)`
- L467-472 _public method_ `public void Refresh()`
- L475-487 _public method_ `public IList<IList<object>> GetCellValues(string A1Range, SpreadsheetsResource.ValuesResource.GetRequest.MajorDimensionEnum MajorDimension = SpreadsheetsResource.ValuesResource.GetRequest.MajorDimensionEnum.ROWS)`
- L489-516 _public method_ `public void InsertRows(int RowIndex, int RowCount)`
- L518-538 _public method_ `public void AppendColumns(int ColumnCount)`
- L540-560 _public method_ `public void AppendRows(int RowCount)`
- L562-577 _public method_ `public void SetRow(object[] Fields, string StartingCell = "A1")`
- L579-592 _public method_ `public void SetRow(List<IList<object>> Fields)`

### `Source/Programs/AutomationTool/AutomationUtils/HashCollection.cs` (AutomationUtils.Automation)


#### class `AutomationTool.HashEntry`  
`public class HashEntry : IEquatable<HashEntry>`  
_public; L21-63_
- inherits: `IEquatable<HashEntry>`
- desc: Class that holds a single hash entry. Only the hash is used for comparisons but the name and meta fields can hold related data for debugging etc.
- L23 _public property_ `public string Name { get; set; }`
- L24 _public property_ `public string MetaData { get; set; }`
- L27 _public property_ `public ContentHash Hash { get; set; }` — attrs: `[XmlIgnore]`
- L30-34 _public property_ `public byte[] HashBytes { get; set; }` — attrs: `[XmlElement(ElementName = "Hash", DataType = "hexBinary")]`
- L36-41 _public ctor_ `public HashEntry(string InName, ContentHash InHash, string InMeta)`
- L44-46 _public ctor_ `public HashEntry()`
- L49-52 _public method_ `public bool Equals(HashEntry RHS)`
- L54-57 _public method_ `public override int GetHashCode()`
- L59-62 _public method_ `public override string ToString()`

#### class `AutomationTool.HashCollection`  
`public class HashCollection`  
_public; L69-253_
- desc: Class that holds a collection of hashes with helpers for adding files, comparisions, and serialization to and from files
- L78 _public property_ `public HashSet<HashEntry> Hashes { get; set; }`
- L80-83 _public ctor_ `public HashCollection()`
- L91-110 _public method_ `public bool AddFile(FileReference InPath, HashCollection.HashType HashType)` — Adds a file to our hash collection. If the specified path does not exist an exception will be thrown
- L117-128 _public method_ `public bool AddFiles(IEnumerable<FileReference> Files, HashCollection.HashType HashType)` — Convenience function that adds a range of files
- L135-145 _public method_ `public override bool Equals(object obj)` — Compares two collections by comparing the underlying hashsets
- L152-155 _public method_ `public bool HasEntryForName(string Name)` — Debugging helper that returns true if there's a hash with the specified name
- L162-165 _public method_ `public HashEntry GetEntryForName(string Input)` — Debugging helper that returns the hash entry for the specified name
- L171-188 _public method_ `public void LogDifferences(HashCollection RHS)` — Logs differences between two collections for debugging
- L194-197 _public method_ `public override int GetHashCode()`
- L204-220 _public method_ `public static HashCollection CreateFromFile(string InPath)` — Creates a hash collection from a previously serialized file
- L226-252 _public method_ `public void SaveToFile(string OutPath)` — Saves a hash collection to the specified file path as XML.

#### enum `AutomationTool.HashCollection.HashType`  
`public enum HashType`  
_public; L71-75_
- L73 _public* enumerator_ `MetaData`
- L74 _public* enumerator_ `Content`

#### class `AutomationTool.CsProjectInfoExtensionMethods`  
`public static class CsProjectInfoExtensionMethods`  
_public; L258-289_
- desc: Extension methods for CsProject support
- L267-288 _public method_ `public static bool AddCsProjectInfo(this HashCollection Hasher, IDotnetProjectInfo Project, HashCollection.HashType HashType)` — Adds aall input/output properties of a CSProject to a hash collection

### `Source/Programs/AutomationTool/AutomationUtils/HelpUtils.cs` (AutomationUtils.Automation)


#### class `AutomationTool.HelpAttribute`  
`public class HelpAttribute : DescriptionAttribute`  
_public; L26-76_
- attrs: `[AttributeUsage(AttributeTargets.All, AllowMultiple = true)]`
- inherits: `DescriptionAttribute`
- desc: Help Attribute.
- L28 _private field_ `private bool IsParamHelp`
- L34-38 _public ctor_ `public HelpAttribute(string Description) : base(Description)` — Basic constructor for class descriptions.
- L45-49 _public ctor_ `public HelpAttribute(string ParamName, string Description) : base(FormatDescription(ParamName, Description))` — Constructor for parameter descriptions.
- L55-59 _public ctor_ `public HelpAttribute(Type AdditionalType)` — Additional type to display help for.
- L61-64 _private method_ `private static string FormatDescription(string Name, string Description)`
- L66-69 _public property_ `public bool IsParam { get; }`
- L71-75 _public property_ `public Type AdditionalHelp { get; set; }`

#### class `AutomationTool.ParamHelpAttribute`  
`public class ParamHelpAttribute : HelpAttribute`  
_public; L79-259_
- attrs: `[AttributeUsage(AttributeTargets.Class | AttributeTargets.Interface, AllowMultiple = true)]`
- inherits: `HelpAttribute`
- L90-92 _private ctor_ `private ParamHelpAttribute(string Description) : base(Description)`
- L94-97 _public ctor_ `public ParamHelpAttribute() : this("", "")`
- L99-114 _public ctor_ `public ParamHelpAttribute(string Name, string Description) : base(Name, Description)`
- L116-120 _public property_ `public string ParamName { get; set; }`
- L122 _private field_ `private string _ParamDescription = string.Empty`
- L123-159 _public property_ `public string ParamDescription { get; set; }`
- L161 _private field_ `private ParamAction _Action = ParamAction.Store`
- L162-176 _public property_ `public ParamAction Action { get; set; }`
- L178-182 _public property_ `public object DefaultValue { get; set; }`
- L184-188 _public property_ `public Type ParamType { get; set; }`
- L190 _private* field_ `object _Choices`
- L191-205 _public property_ `public object Choices { get; set; }`
- L207-211 _public property_ `public bool Required { get; set; }`
- L213-217 _public property_ `public bool IsArgument { get; set; }`
- L219-223 _public property_ `public string MultiSelectSeparator { get; set; }`
- L225-229 _public property_ `public bool Deprecated { get; set; }`
- L231 _private field_ `private string _Flag = null`
- L232-249 _public property_ `public string Flag { get; set; }`
- L254-258 _public property_ `public string ParamKeyValueDelimiter { get; set; }` — This string/character separates the flag from the value; ex. -foo=bar

#### enum `AutomationTool.ParamHelpAttribute.ParamAction`  
`public enum ParamAction`  
_public; L81-88_
- L83 _public* enumerator_ `Store`
- L84 _public* enumerator_ `Store_True`
- L85 _public* enumerator_ `Store_False`
- L86 _public* enumerator_ `Append`
- L87 _public* enumerator_ `Override`

#### class `AutomationTool.CommandUtils`  
`public partial class CommandUtils`  
_public; L264-401_
- desc: Base utility function for script commands.
- L270-276 _public method_ `public static void Help(Type Command)` — Displays help for the specified command. Command type.
- L282-288 _public method_ `public static void LogHelp(Type Command)` — Displays help for the specified Type.
- L296-335 _public method_ `public static void LogHelp(Type Command, string Description, List<string> Params)` — Displays a formatted help for the specified Command type.
- L343-389 _public method_ `public static void GetTypeHelp(Type ObjType, out string ObjectDescription, out List<string> Params)` — Gets the description and a list of parameters for the specified type.
- L391-400 _private method_ `private static List<MemberInfo> GetAllMemebers(Type ObjType)`

### `Source/Programs/AutomationTool/AutomationUtils/HordeUtils.cs` (AutomationUtils.Automation)


#### class `AutomationTool.CommandUtils`  
`public partial class CommandUtils`  
_public; L22-94_
- desc: Helper methods for Horde functionality
- L24 _private* field_ `static readonly ConcurrentDictionary<SecretId, IReadOnlyDictionary<string, string>> _cachedSecrets = ...`
- L24 _private* field_ `static readonly ConcurrentDictionary< string`
- L24 _private* field_ `static readonly ConcurrentDictionary< _cachedSecrets = new ConcurrentDictionary<SecretId, IReadOnlyDictionary<string, string>>()`
- L32-59 _public method_ `public static async Task<IReadOnlyDictionary<string, string>> GetHordeSecretAsync(SecretId secretId, CancellationToken cancellationToken = default)` — Reads a secret from Horde
- L68-76 _public method_ `public static async Task<string> GetHordeSecretAsync(SecretId secretId, string propertyName, CancellationToken cancellationToken = default)` — Reads a secret from Horde
- L78-93 _public method_ `public static async Task AddHordeJobMetadata(JobId id, IEnumerable<string>? jobMetaData = null, Dictionary<string, List<string>>? stepMetaData = null, CancellationToken cancellationToken = default)`

### `Source/Programs/AutomationTool/AutomationUtils/HostPlatform.cs` (AutomationUtils.Automation)


#### class `AutomationTool.HostPlatform`  
`public abstract class HostPlatform`  
_public; L18-109_
- desc: Host platform abstraction
- L20 _protected property_ `protected static ILogger Logger => ...`
- L25 _public field_ `public static readonly HostPlatform Current = Initialize()` — Current running host platform.
- L30-39 _private method_ `private static HostPlatform Initialize()` — Initializes the current platform.
- L45 _public method_ `abstract public string GetFrameworkMsbuildExe()` — Gets the build executable filename for NET Framework projects e.g. msbuild
- L50 _public property_ `abstract public string RelativeBinariesFolder { get; }` — Folder under UE/ to the platform's binaries.
- L57 _public method_ `abstract public string GetUnrealExePath(string UnrealExe)` — Full path to the UnrealEditor executable for the current platform.
- L62 _public property_ `abstract public string LocalBuildsLogFolder { get; }` — Log folder for local builds.
- L67 _public property_ `abstract public string P4Exe { get; }` — Name of the p4 executable.
- L74 _public method_ `abstract public Process CreateProcess(string AppName)` — Creates a process and sets it up for the current platform.
- L82 _public method_ `abstract public void SetupOptionsForRun(ref string AppName, ref CommandUtils.ERunOptions Options, ref string CommandLine)` — Sets any additional options for running an executable.
- L88 _public method_ `abstract public void SetConsoleCtrlHandler(ProcessManager.CtrlHandlerDelegate Handler)` — Sets the console control handler for the current platform.
- L93 _public property_ `abstract public UnrealBuildTool.UnrealTargetPlatform HostEditorPlatform { get; }` — Returns the type of the host editor platform.
- L98 _public property_ `public static UnrealBuildTool.UnrealTargetPlatform Platform { get; }` — Returns the type of the current running host platform
- L103 _public property_ `abstract public string PdbExtension { get; }` — Returns the pdb file extenstion for the host platform.
- L108 _public property_ `abstract public string[] DontKillProcessList { get; }` — List of processes that can't not be killed

### `Source/Programs/AutomationTool/AutomationUtils/HttpClientSingleton.cs` (AutomationUtils.Automation)


#### class `AutomationUtils.HttpClientSingleton`  
`public class HttpClientSingleton<T>`  
_public; L13-36_
- L15 _private field_ `private static readonly Lazy<HttpClient> internalInstance = new Lazy<HttpClient>(() => { AsyncRetryPolicy<HttpResponseMessage> retryPolicy = HttpPolicyExtensions .HandleTransientHttpError() .OrResult(msg => msg.StatusCode == System.Net.HttpStatusCode.NotFound  ...`
- L35 _public property_ `public static HttpClient Client { get; }`

### `Source/Programs/AutomationTool/AutomationUtils/ImagePipelineBuilder.cs` (AutomationUtils.Automation)


#### class `AutomationTool.ImagePipelineBuilder`  
`public class ImagePipelineBuilder : IDisposable`  
_public; L15-165_
- inherits: `IDisposable`
- desc: Performs a set of operations on an existing image
- L17 _private property_ `private static ILogger Logger => ...`
- L19 _private field_ `private MagickImage? image = null`
- L21-31 _public ctor_ `public ImagePipelineBuilder(string ImagePath)`
- L34-38 _public method_ `public void Dispose()` — (inheritdoc)
- L45-49 _public method_ `public ImagePipelineBuilder Rotate(double degrees)` — Rotates an image clockwise
- L55-59 _public method_ `public ImagePipelineBuilder FlipVertically()` — Flips the image vertically. Can be chained with
- L65-69 _public method_ `public ImagePipelineBuilder FlipHorizontally()` — Flips the image horizontally. Can be chained with
- L76-92 _public method_ `public ImagePipelineBuilder Scale(float Scale)` — Scales the image's current width and height by the specified value
- L99-107 _public method_ `public ImagePipelineBuilder CompressionLevel(uint Quality)` — Adjusts the images compression level for JPEG and PNG images
- L114-123 _public method_ `public bool SaveAsJpeg(string OutputPath)` — Saves the image as a JPEG
- L130-139 _public method_ `public bool SaveAsPng(string OutputPath)` — Saves the image as a PNG
- L146-164 _public method_ `public bool Save(string OutputPath)` — Saves the image using it's current format

### `Source/Programs/AutomationTool/AutomationUtils/ImageUtils.cs` (AutomationUtils.Automation)


#### class `AutomationTool.ImageUtils`  
`public static class ImageUtils`  
_public; L8-36_
- L13-16 _public method_ `public static void ResaveImageAsJpgWithScaleAndQuality(string SrcImagePath, string DstImagePath, float Scale, int JpgQuality)` — Resave an image file as a .jpg file, with the specified quality and scale.
- L21-24 _public method_ `public static void ResaveImageAsPngWithScaleAndQuality(string SrcImagePath, string DstImagePath, float Scale, int PngQuality)` — Resave an image file as a .png file, with the specified quality and scale.
- L26-35 _private* method_ `static void ResaveImageScaleAndQuality(string SrcImagePath, string DstImagePath, MagickFormat Format, float Scale, uint Quality)`

### `Source/Programs/AutomationTool/AutomationUtils/IoStoreOnDemandUtils.cs` (AutomationUtils.Automation)


#### class `AutomationTool.IoStoreOnDemandSettings`  
`public class IoStoreOnDemandSettings`  
_public; L9-105_
- L11-16 _public method_ `public void SetIASGloballyEnabled()`
- L18-37 _public method_ `public void ReadFromCommandLine(BuildCommand Command)`
- L39-42 _public method_ `public bool IsIASEnabled()`
- L44-47 _public method_ `public bool ShouldCreateDefaultOnDemandPakRule()`
- L49-52 _public method_ `public bool ShouldCreateAssetTypeOnDemandPakRule()`
- L54-64 _public method_ `public Dictionary<string, List<string>> GetEnabledAssetList()`
- L72-75 _public method_ `public bool ApplyRulesForStagingManifest()` — Poll if pak rules should be applied when staging from a manifest rather than a chunked build. This allows IAS to force the creation of 'OnDemand' container files even when chunked builds are not being used.
- L102 _protected property_ `protected IADSpecificSettings IADSettings { get; }`
- L104 _protected field_ `protected IASSpecificSettings IASSettings`

#### class `AutomationTool.IoStoreOnDemandSettings.IADSpecificSettings`  
`public class IADSpecificSettings`  
_public; L77-80_

#### class `AutomationTool.IoStoreOnDemandSettings.IASSpecificSettings`  
`public class IASSpecificSettings`  
_public; L82-100_
- L94 _public property_ `public RuleMode Mode { get; set; }`
- L96 _public field_ `public bool ApplyToStagingManifest = false`
- L99 _public property_ `public Dictionary<string, List<string>> Assets { get; set; }`

#### enum `AutomationTool.IoStoreOnDemandSettings.IASSpecificSettings.RuleMode`  
`public enum RuleMode`  
_public; L84-92_
- L87 _public* enumerator_ `None`
- L89 _public* enumerator_ `Default`
- L91 _public* enumerator_ `AssetType`

### `Source/Programs/AutomationTool/AutomationUtils/LinuxHostPlatform.cs` (AutomationUtils.Automation)


#### class `AutomationTool.LinuxHostPlatform`  
`class LinuxHostPlatform : HostPlatform`  
_internal*; L12-136_
- inherits: `HostPlatform`
- L14 _private* field_ `static string CachedFrameworkMsbuildExe = string.Empty`
- L16-34 _public method_ `public override string GetFrameworkMsbuildExe()`
- L36-39 _public property_ `public override string RelativeBinariesFolder { get; }`
- L41-62 _public method_ `public override string GetUnrealExePath(string UnrealExe)`
- L64-68 _public property_ `public override string LocalBuildsLogFolder { get; }`
- L70-73 _public property_ `public override string P4Exe { get; }`
- L75-79 _public method_ `public override Process CreateProcess(string AppName)`
- L81-109 _public method_ `public override void SetupOptionsForRun(ref string AppName, ref CommandUtils.ERunOptions Options, ref string CommandLine)`
- L111-114 _public method_ `public override void SetConsoleCtrlHandler(ProcessManager.CtrlHandlerDelegate Handler)`
- L116-119 _public property_ `public override UnrealTargetPlatform HostEditorPlatform { get; }`
- L121-124 _public property_ `public override string PdbExtension { get; }`
- L125 _private* field_ `static string[] SystemServices = new string[] { }`
- L129-135 _public property_ `public override string[] DontKillProcessList { get; }`

### `Source/Programs/AutomationTool/AutomationUtils/LogUtils.cs` (AutomationUtils.Automation)


#### class `AutomationTool.LogUtils`  
`public static class LogUtils`  
_public; L14-127_
- L19-23 _public property_ `public static FileReference LogFileName { get; set; }` — Stores the log filename.
- L28-32 _public property_ `public static FileReference FinalLogFileName { get; set; }` — Stores the final log filename. The build system uses this to display the network path that the log will be copied to once builds complete.
- L40-64 _public method_ `public static void AddLogFileListener(DirectoryReference LogFolder, DirectoryReference FinalLogFolder)` — Creates the TraceListener used for file logging. We cannot simply use a TextWriterTraceListener because we need more flexibility when the file cannot be created. TextWriterTraceListener lazily creates the file, silently failing when it cannot.
- L71-79 _public method_ `public static string FormatException(Exception Ex)` — Dumps exception info to log. @todo: Remove this function as it doesn't do a good job printing the exception information.
- L86-125 _public method_ `public static string GetUniqueLogName(string Base)` — Returns a unique logfile name.

### `Source/Programs/AutomationTool/AutomationUtils/MCPPublic.cs` (AutomationUtils.Automation)


#### class `EpicGames.MCP.Automation.CommitRollbackTransaction`  
`public class CommitRollbackTransaction : IDisposable`  
_public; L29-68_
- inherits: `IDisposable`
- desc: Utility class to provide commit/rollback functionality via an RAII-like functionality. Usage is to provide a rollback action that will be called on Dispose if the Commit() method is not called. This is expected to be used from within a using() ... clause.
- L34 _private field_ `private bool IsCommitted = false` — Track whether the transaction will be committed.
- L39 _private field_ `private System.Action RollbackAction`
- L44-47 _public method_ `public void Commit()` — Call when you want to commit your transaction. Ensures the Rollback action is not called on Dispose().
- L53-56 _public ctor_ `public CommitRollbackTransaction(System.Action InRollbackAction)` — Constructor
- L61-67 _public method_ `public void Dispose()` — Rollback the transaction if its not committed on Dispose.

#### struct `EpicGames.MCP.Automation.MCPPlatform`  
`public partial struct MCPPlatform`  
_public; L74-280_
- attrs: `[TypeConverter(typeof(MCPPlatformTypeConverter))]`
- desc: Enum that defines the MCP backend-compatible platform
- L80 _private field_ `private int Id`
- L83 _private field_ `private static UniqueStringRegistry? StringRegistry`
- L87-94 _private method_ `private static UniqueStringRegistry GetUniqueStringRegistry()`
- L96-99 _private ctor_ `private MCPPlatform(string Name)`
- L101-104 _private ctor_ `private MCPPlatform(int InId)`
- L106-109 _private method_ `static private MCPPlatform FindOrAddByName(string Name)`
- L117-120 _public operator_ `public static bool operator ==(MCPPlatform A, MCPPlatform B)`
- L128-131 _public operator_ `public static bool operator !=(MCPPlatform A, MCPPlatform B)`
- L138-146 _public method_ `public override bool Equals(object? B)`
- L152-155 _public method_ `public override int GetHashCode()`
- L163-166 _public method_ `public override string ToString()` — Return the string representation
- L174-183 _public method_ `static public bool TryParse(string Name, out MCPPlatform Platform)` — Parse string into a MCPPlatform
- L190-199 _public method_ `static public MCPPlatform Parse(string Name)` — Parse string into a MCPPlatform
- L205-208 _public method_ `public static MCPPlatform[] GetValidPlatforms()` — Get list of valid platforms
- L214-217 _public method_ `public static string[] GetValidPlatformNames()` — Get list of valid platform names
- L222 _public field_ `public static MCPPlatform Windows = FindOrAddByName("Windows")` — MCP uses Windows for Win64
- L227 _public field_ `public static MCPPlatform Win32 = FindOrAddByName("Win32")` — 32 bit Windows
- L232 _public field_ `public static MCPPlatform Mac = FindOrAddByName("Mac")` — Mac platform.
- L237 _public field_ `public static MCPPlatform Linux = FindOrAddByName("Linux")` — Linux platform.
- L242 _public field_ `public static MCPPlatform IOS = FindOrAddByName("IOS")` — IOS platform.
- L247 _public field_ `public static MCPPlatform Android = FindOrAddByName("Android")` — Android platform.
- L252 _public field_ `public static MCPPlatform WindowsCN = FindOrAddByName("WindowsCN")` — WindowsCN Platform.
- L257 _public field_ `public static MCPPlatform WindowsGFN = FindOrAddByName("WindowsGFN")` — WindowsGFN Platform.
- L262 _public field_ `public static MCPPlatform WindowsLuna = FindOrAddByName("WindowsLuna")` — WindowsLuna Platform.
- L267 _public field_ `public static MCPPlatform WindowsMSG = FindOrAddByName("WindowsMSG")` — WindowsMSG Platform.
- L272 _public field_ `public static MCPPlatform IOSCN = FindOrAddByName("IOSCN")` — IOSCN Platform.
- L277 _public field_ `public static MCPPlatform AndroidCN = FindOrAddByName("AndroidCN")` — AndroidCN Platform.

#### class `EpicGames.MCP.Automation.MCPPlatformTypeConverter`  
`internal class MCPPlatformTypeConverter : TypeConverter`  
_internal; L282-318_
- inherits: `TypeConverter`
- L284-290 _public method_ `public override bool CanConvertFrom(ITypeDescriptorContext context, Type sourceType)`
- L292-298 _public method_ `public override bool CanConvertTo(ITypeDescriptorContext context, Type destinationType)`
- L300-307 _public method_ `public override object ConvertFrom(ITypeDescriptorContext context, CultureInfo culture, object value)`
- L309-317 _public method_ `public override object ConvertTo(ITypeDescriptorContext context, CultureInfo culture, object value, Type destinationType)`

#### enum `EpicGames.MCP.Automation.CDNType`  
`public enum CDNType`  
_public; L323-334_
- desc: Enum that defines CDN types
- L328 _public* enumerator_ `Internal` — Internal HTTP CDN server
- L333 _public* enumerator_ `Production` — Production HTTP CDN server

#### class `EpicGames.MCP.Automation.BuildPatchToolStagingInfo`  
`public class BuildPatchToolStagingInfo`  
_public; L339-632_
- desc: Class that holds common state used to control the BuildPatchTool build commands that chunk and create patching manifests and publish build info to the BuildInfoService.
- L344 _public field_ `public BuildCommand OwnerCommand` — The currently running command, used to get command line overrides
- L348 _public field_ `public readonly string AppName` — name of the app. Can't always use this to define the staging dir because some apps are not staged to a place that matches their AppName.
- L352 _public field_ `public readonly string McpConfigKey` — Usually the base name of the app. Used to get the MCP key from a branch dictionary.
- L356 _public field_ `public readonly int AppID` — ID of the app (needed for the BuildPatchTool)
- L360 _public field_ `public readonly string BuildVersion` — BuildVersion of the App we are staging.
- L364 _public field_ `public BuildMetadataBase Metadata` — Metadata for the build consisting of arbitrary json data. Will be null if no metadata exists.
- L369 _public field_ `public readonly string StagingDir` — Directory where builds will be staged. Rooted at the BuildRootPath, using a subfolder passed in the ctor, and using BuildVersion/PlatformName to give each builds their own home.
- L375 _public field_ `public readonly string CloudDirRelativePath` — Path to the CloudDir where chunks will be written (relative to the BuildRootPath) This is used to copy to the web server, so it can use the same relative path to the root build directory. This allows file to be either copied from the local file system or the webserver using the same relative paths.
- L379 _public field_ `public readonly string CloudDir` — full path to the CloudDir where chunks and manifests should be staged. Rooted at the BuildRootPath, using a subfolder pass in the ctor.
- L383 _public field_ `public readonly MCPPlatform Platform` — Platform we are staging for.
- L391-407 _public property_ `public virtual string ManifestFilename { get; }` — Gets the base filename of the manifest that would be created by invoking the BuildPatchTool with the given parameters. Note that unless ManifestFilename was provided when constructing this instance, it is strongly recommended to call RetrieveManifestFilename() for existing builds to ensure that the correct filename is used. The legacy behavior of constructing of a manifest filename from appname, buildversion and platform should be considered unreliable, and will emit a warning.
- L412 _protected field_ `protected string _ManifestFilename` — If set, this allows us to over-ride the automatically constructed ManifestFilename
- L417-428 _public method_ `static public MCPPlatform ToMCPPlatform(UnrealTargetPlatform TargetPlatform)` — Determine the platform name
- L433-444 _public method_ `static public UnrealTargetPlatform FromMCPPlatform(MCPPlatform TargetPlatform)` — Determine the platform name
- L450-455 _public method_ `static public string GetBuildRootPath()` — Returns the build root path (P:\Builds on build machines usually)
- L467-481 _public ctor_ `public BuildPatchToolStagingInfo(BuildCommand InOwnerCommand, string InAppName, string InMcpConfigKey, int InAppID, string InBuildVersion, MCPPlatform platform, string stagingDirRelativePath)` — Basic constructor.
- L486-489 _public ctor_ `public BuildPatchToolStagingInfo(BuildCommand InOwnerCommand, string InAppName, string InMcpConfigKey, int InAppID, string InBuildVersion, UnrealTargetPlatform InPlatform, string StagingDirRelativePath, string StagingDirSuffix, string InManifestFilename) : this(InOwnerCommand, InAppName, InMcpConfigKey, InAppID, InBuildVersion, ToMCPPlatform(InPlatform), StagingDirRelativePath, StagingDirSuffix, InManifestFilename)` — Basic constructor with staging dir suffix override, basically to avoid having platform concatenated
- L503-518 _public ctor_ `public BuildPatchToolStagingInfo(BuildCommand InOwnerCommand, string InAppName, string InMcpConfigKey, int InAppID, string InBuildVersion, MCPPlatform InPlatform, string StagingDirRelativePath, string StagingDirSuffix, string InManifestFilename)` — Basic constructor with staging dir suffix override, basically to avoid having platform concatenated
- L523-532 _public ctor_ `public BuildPatchToolStagingInfo(BuildCommand InOwnerCommand, string InAppName, int InAppID, string InBuildVersion, MCPPlatform InPlatform, string InCloudDir)` — Constructor which supports being able to just simply call BuildPatchToolBase.Get().Execute
- L537-563 _public ctor_ `public BuildPatchToolStagingInfo(BuildCommand InOwnerCommand, string InAppName, int InAppID, string InBuildVersion, MCPPlatform InPlatform, DirectoryReference InStagingDir, DirectoryReference InCloudDir, string InManifestFilename = null)` — Constructor which sets all values directly, without assuming any default paths.
- L572-576 _public method_ `public BuildPatchToolStagingInfo WithMetadata(string Key, string Value, bool bClobber = true)` — Associates a piece of metadata (in the form of a key value pair) with the build info.
- L584-595 _public method_ `public BuildPatchToolStagingInfo WithMetadata(BuildMetadataBase NewMetadata, bool bClobber = true)` — Associates new metadata with the build info.
- L605-619 _public method_ `public string RetrieveManifestFilename(string McpConfigName, bool bForce = false)` — Returns the manifest filename, querying build info for it if necessary. If ManifestFilename has already set (either during construction or by a previous call to this method) the cached value will be returned unless bForce is specified. Otherwise, a query will be made to the specified build info service to retrieve the correct manifest filename.
- L627-631 _public method_ `public BuildMetadataBase RetrieveBuildMetadata(string McpConfigName = null, bool bClobber = false)` — Adds and returns the metadata for this build, querying build info for any additional fields.

#### class `EpicGames.MCP.Automation.BuildPatchToolBase`  
`public abstract class BuildPatchToolBase`  
_public; L637-1865_
- desc: Class that provides programmatic access to the BuildPatchTool
- L1731 _private* field_ `static BuildPatchToolBase Handler = null`
- L1733-1756 _public method_ `public static BuildPatchToolBase Get()`
- L1759 _public method_ `public abstract void Execute(ManifestMetadataOptions Opts, out ManifestMetadataOutput Output, ToolVersion Version = ToolVersion.Live)`
- L1767 _public method_ `public abstract void Execute(PatchGenerationOptions Opts, ToolVersion Version = ToolVersion.Live, bool bAllowManifestClobbering = false)` — Runs the Build Patch Tool executable to generate patch data using the supplied parameters.
- L1775 _public method_ `public abstract void Execute(UploadBinaryOptions Opts, ToolVersion Version = ToolVersion.Online_Live)` — Runs the Build Patch Tool executable to generate patch data using the supplied parameters. V2 is only available when using online version of bpt, this job encapsulates chunk, upload, and post build bpt tasks
- L1784 _public method_ `public abstract void Execute(ListBinariesOptions Opts, out ListBinariesOutput Output, ToolVersion Version = ToolVersion.Online_Live)` — Runs the Build Patch Tool executable to list binaries using the supplied parameters. V2 is only available when using online version of bpt
- L1791 _public method_ `public abstract void Execute(LabelBinaryOptions Opts, ToolVersion Version = ToolVersion.Online_Live)` — Runs the Build Patch Tool executable to label binary using the supplied parameters. NOTE: This is only available when using online version of BPT
- L1798 _public method_ `public abstract void Execute(CopyBinaryOptions Opts, ToolVersion Version = ToolVersion.Online_Live)` — Runs the Build Patch Tool executable to Copy binary using the supplied parameters. NOTE: This is only available when using online version of BPT
- L1805 _public method_ `public abstract void Execute(BinaryDeltaOptimizeOptions Opts, ToolVersion Version = ToolVersion.Online_Live)` — Runs the Build Patch Tool executable to generate optimized deltas between the two binaries provided
- L1812 _public method_ `public abstract void Execute(CompactifyOptions Opts, ToolVersion Version = ToolVersion.Live)` — Runs the Build Patch Tool executable to compactify a cloud directory using the supplied parameters.
- L1819 _public method_ `public abstract void Execute(DataEnumerationOptions Opts, ToolVersion Version = ToolVersion.Live)` — Runs the Build Patch Tool executable to enumerate patch data files referenced by a manifest using the supplied parameters.
- L1826 _public method_ `public abstract void Execute(ManifestMergeOptions Opts, ToolVersion Version = ToolVersion.Live)` — Runs the Build Patch Tool executable to merge two manifest files producing a hotfix manifest.
- L1834 _public method_ `public abstract void Execute(ManifestDiffOptions Opts, out ManifestDiffOutput Output, ToolVersion Version = ToolVersion.Live)` — Runs the Build Patch Tool executable to diff two manifest files logging out details.
- L1842 _public method_ `public abstract void Execute(BinaryDiffOptions Opts, out ManifestDiffOutput Output, ToolVersion Version = ToolVersion.Live)` — Runs the Build Patch Tool executable to diff two binaries files logging out details.
- L1849 _public method_ `public abstract void Execute(AutomationTestsOptions Opts, ToolVersion Version = ToolVersion.Live)` — Runs the Build Patch Tool executable to evaluate built in automation testing.
- L1857 _public method_ `public abstract void Execute(PackageChunksOptions Opts, out PackageChunksOutput Output, ToolVersion Version = ToolVersion.Live)` — Runs the Build Patch Tool executable to create ChunkDB file(s) consisting of multiple chunks to allow installing / patching to a specific build.
- L1864 _public method_ `public abstract void Execute(ChunkDeltaOptimiseOptions Opts, ToolVersion Version = ToolVersion.Live)` — Runs the Build Patch Tool executable to create optimised delta files which reduce download size for patching between two specific builds.

#### enum `EpicGames.MCP.Automation.BuildPatchToolBase.ToolVersion`  
`public enum ToolVersion`  
_public; L642-670_
- desc: Controls which version of BPT to use when executing.
- L647 _public* enumerator_ `Live` — The current live, tested build.
- L651 _public* enumerator_ `Next` — The latest published build, may be untested.
- L655 _public* enumerator_ `Experimental` — An experimental build, for use when one project needs early access or unique changes.
- L659 _public* enumerator_ `Source` — Use local build from source of BuildPatchTool.
- L663 _public* enumerator_ `Online_v140` — BPT publicly released online versions
- L664 _public* enumerator_ `Online_v150`
- L665 _public* enumerator_ `Online_v151`
- L666 _public* enumerator_ `Online_v152`
- L667 _public* enumerator_ `Online_v160`
- L669 _public* enumerator_ `Online_Live = Live`

#### interface `EpicGames.MCP.Automation.BuildPatchToolBase.IPerforce`  
`public interface IPerforce`  
_public; L675-704_
- desc: An interface which provides the required Perforce access implementations
- L680 _public* property_ `bool bIsEnabled { get; }` — Property to say whether Perforce access is enabled in the environment.
- L687 _public* method_ `bool FileExists(string Filename)` — Check a file exists in Perforce.
- L695 _public* method_ `bool PrintToFile(string DepotPath, string Filename)` — Gets the contents of a particular file in the depot and writes it to a local file without syncing it.
- L703 _public* method_ `bool GetLatestChange(string Filename, out int ChangeList)` — Retrieve the latest CL number for the given file.

#### class `EpicGames.MCP.Automation.BuildPatchToolBase.PatchGenerationOptions`  
`public class PatchGenerationOptions`  
_public; L706-826_
- L711 _private const_ `private const int DEFAULT_DATA_AGE_THRESHOLD = 5` — By default, we will only consider data referenced from manifests modified within five days to be reusable.
- L713-718 _public ctor_ `public PatchGenerationOptions()`
- L724 _public field_ `public int AppId` — A unique integer for this product. Deprecated. Can be safely left as 0.
- L728 _public field_ `public string AppName` — The app name for this build, which will be embedded inside the generated manifest to identify the application.
- L732 _public field_ `public string BuildVersion` — The build version being generated.
- L736 _public field_ `public MCPPlatform Platform` — Used as part of the build version string.
- L740 _public field_ `public string BuildRoot` — The directory containing the build image to be read.
- L744 _public field_ `public string CloudDir` — The directory which will receive the generated manifest and chunks.
- L748 _public field_ `public string ManifestFilename` — The name of the manifest file that will be produced.
- L752 _public field_ `public string FileInputList` — A path to a text file containing BuildRoot relative files to be included in the build.
- L756 _public field_ `public string FileIgnoreList` — A path to a text file containing BuildRoot relative files to be excluded from the build.
- L761 _public field_ `public string FileAttributeList` — A path to a text file containing quoted BuildRoot relative files followed by optional attributes such as readonly compressed executable tag:mytag, separated by \r\n line endings. These attribute will be applied when build is installed client side.
- L765 _public field_ `public string AppLaunchCmd` — The path to the app executable, must be relative to, and inside of BuildRoot.
- L769 _public field_ `public string AppLaunchCmdArgs` — The commandline to send to the app on launch.
- L773 _public field_ `public string UninstallActionPath` — The custom uninstall action executable to launch right before product uninstall, relative to the build root.
- L777 _public field_ `public string UninstallActionArgs` — The commandline to send to the custom uninstall action on launch.
- L781 _public field_ `public List<string> PrereqIds` — The list of prerequisite Ids that this prerequisite installer satisfies.
- L785 _public field_ `public string PrereqPath` — The prerequisites installer to launch on successful product install, must be relative to, and inside of BuildRoot.
- L789 _public field_ `public string PrereqArgs` — The commandline to send to prerequisites installer on launch.
- L797 _public field_ `public int DataAgeThreshold` — When identifying existing patch data to reuse in this build, only files referenced from a manifest file modified within this number of days will be considered for reuse. IMPORTANT: This should always be smaller than the minimum age at which manifest files can be deleted by any cleanup process, to ensure that we do not reuse any files which could be deleted by a concurrently running compactify. It is recommended that this number be at least two days less than the cleanup data age threshold.
- L801 _public field_ `public int ChunkWindowSize` — Specifies in bytes, the data window size that should be used when saving new chunks. Default is 1048576 (1MiB).
- L805 _public field_ `public string FeatureLevel` — Specifies the desired output FeatureLevel of BuildPatchTool, if this is not provided BPT will warn and default to LatestJson so that project scripts can be updated.
- L809 _public field_ `public bool ResaveKnownChunks` — Output includes all known chunks, not just new chunks generated
- L813 _public field_ `public List<KeyValuePair<string, string>> CustomStringArgs` — Contains a list of custom string arguments to be embedded in the generated manifest file.
- L813 _public field_ `public List<KeyValuePair< CustomStringArgs` — Contains a list of custom string arguments to be embedded in the generated manifest file.
- L817 _public field_ `public List<KeyValuePair<string, int>> CustomIntArgs` — Contains a list of custom integer arguments to be embedded in the generated manifest file.
- L817 _public field_ `public List<KeyValuePair< CustomIntArgs` — Contains a list of custom integer arguments to be embedded in the generated manifest file.
- L821 _public field_ `public List<KeyValuePair<string, float>> CustomFloatArgs` — Contains a list of custom float arguments to be embedded in the generated manifest file.
- L821 _public field_ `public List<KeyValuePair< CustomFloatArgs` — Contains a list of custom float arguments to be embedded in the generated manifest file.
- L825 _public field_ `public string AdditionalArguments` — Specifies additional arguments to be passed to BPT

#### class `EpicGames.MCP.Automation.BuildPatchToolBase.UploadBinaryOptions`  
`public class UploadBinaryOptions`  
_public; L829-960_
- L834 _private const_ `private const int DEFAULT_DATA_AGE_THRESHOLD = 5` — By default, we will only consider data referenced from manifests modified within five days to be reusable.
- L836-840 _public ctor_ `public UploadBinaryOptions()`
- L846 _public field_ `public string ArtifactId` — The id of the artifact. This will be embedded inside the generated manifest to identify the application.
- L850 _public field_ `public string BuildVersion` — The build version being generated.
- L854 _public field_ `public MCPPlatform Platform` — Used as part of the build version string.
- L858 _public field_ `public string BuildRoot` — The directory containing the build image to be read.
- L862 _public field_ `public string CloudDir` — The directory which will receive the generated manifest and chunks.
- L866 _public field_ `public string FileInputList` — A path to a text file containing BuildRoot relative files to be included in the build.
- L870 _public field_ `public string FileIgnoreList` — A path to a text file containing BuildRoot relative files to be excluded from the build.
- L875 _public field_ `public string FileAttributeList` — A path to a text file containing quoted BuildRoot relative files followed by optional attributes such as readonly compressed executable tag:mytag, separated by \r\n line endings. These attribute will be applied when build is installed client side.
- L879 _public field_ `public string AllowedlistArtifactIds` — List of artifact ids which will be used to generate patches, if this is left blank all artifact ids will be used
- L883 _public field_ `public string ClientId` — Specifies the client id allocated to you by Epic for uploading binaries to Epic's services.
- L887 _public field_ `public string ClientSecret` — Specifies the client secret allocated to you by Epic for uploading binaries to Epic's services.
- L891 _public field_ `public string ClientSecretEnvVar` — Specifies the name of an environment variable containing the client secret allocated to you by Epic for uploading binaries to Epic's services.
- L895 _public field_ `public string OrganizationId` — Specifies the id of the organization that this product belongs to.
- L899 _public field_ `public string ProductId` — Specifies the id of the product being uploaded.
- L903 _public field_ `public string AppLaunchCmd` — The path to the app executable, must be relative to, and inside of BuildRoot.
- L907 _public field_ `public string AppLaunchCmdArgs` — The commandline to send to the app on launch.
- L911 _public field_ `public string UninstallActionPath` — The custom uninstall action executable to launch right before product uninstall, relative to the build root.
- L915 _public field_ `public string UninstallActionArgs` — The commandline to send to the custom uninstall action on launch.
- L919 _public field_ `public List<string> PrereqIds` — The list of prerequisite Ids that this prerequisite installer satisfies.
- L923 _public field_ `public string PrereqPath` — The prerequisites installer to launch on successful product install, must be relative to, and inside of BuildRoot.
- L927 _public field_ `public string PrereqArgs` — The commandline to send to prerequisites installer on launch.
- L935 _public field_ `public int DataAgeThreshold` — When identifying existing patch data to reuse in this build, only files referenced from a manifest file modified within this number of days will be considered for reuse. IMPORTANT: This should always be smaller than the minimum age at which manifest files can be deleted by any cleanup process, to ensure that we do not reuse any files which could be deleted by a concurrently running compactify. It is recommended that this number be at least two days less than the cleanup data age threshold.
- L939 _public field_ `public int ChunkWindowSize` — Specifies in bytes, the data window size that should be used when saving new chunks. Default is 1048576 (1MiB).
- L943 _public field_ `public string FeatureLevel` — Specifies the desired output FeatureLevel of BuildPatchTool, if this is not provided BPT will warn and default to LatestJson so that project scripts can be updated.
- L947 _public field_ `public List<KeyValuePair<string, string>> CustomStringArgs` — Contains a list of custom string arguments to be embedded in the generated manifest file.
- L947 _public field_ `public List<KeyValuePair< CustomStringArgs` — Contains a list of custom string arguments to be embedded in the generated manifest file.
- L951 _public field_ `public List<KeyValuePair<string, int>> CustomIntArgs` — Contains a list of custom integer arguments to be embedded in the generated manifest file.
- L951 _public field_ `public List<KeyValuePair< CustomIntArgs` — Contains a list of custom integer arguments to be embedded in the generated manifest file.
- L955 _public field_ `public List<KeyValuePair<string, float>> CustomFloatArgs` — Contains a list of custom float arguments to be embedded in the generated manifest file.
- L955 _public field_ `public List<KeyValuePair< CustomFloatArgs` — Contains a list of custom float arguments to be embedded in the generated manifest file.
- L959 _public field_ `public string CommandLineFile` — File path to a file containing parameters for bpt to use (can be used in combination with parameters above, no duplicates)

#### class `EpicGames.MCP.Automation.BuildPatchToolBase.LabelBinaryOptions`  
`public class LabelBinaryOptions`  
_public; L962-1008_
- L964-966 _public ctor_ `public LabelBinaryOptions()`
- L971 _public field_ `public string ArtifactId` — The id of the artifact.
- L975 _public field_ `public string BuildVersion` — The build version that receives label
- L979 _public field_ `public string Label` — label name to apply to build version
- L983 _public field_ `public MCPPlatform Platform` — Platform for which the label will be applied
- L987 _public field_ `public string ClientId` — Specifies the client id allocated to you by Epic for uploading binaries to Epic's services.
- L991 _public field_ `public string ClientSecret` — Specifies the client secret allocated to you by Epic for uploading binaries to Epic's services.
- L995 _public field_ `public string ClientSecretEnvVar` — Specifies the name of an environment variable containing the client secret allocated to you by Epic for uploading binaries to Epic's services.
- L999 _public field_ `public string OrganizationId` — Specifies the id of the organization that this product belongs to.
- L1003 _public field_ `public string ProductId` — Specifies the id of the product being uploaded.
- L1007 _public field_ `public string CommandLineFile` — File path to a file containing parameters for bpt to use (can be used in combination with parameters above, no duplicates)

#### class `EpicGames.MCP.Automation.BuildPatchToolBase.BinaryDeltaOptimizeOptions`  
`public class BinaryDeltaOptimizeOptions`  
_public; L1011-1059_
- L1013-1015 _public ctor_ `public BinaryDeltaOptimizeOptions()`
- L1020 _public field_ `public string ArtifactId` — The id of the artifact.
- L1024 _public field_ `public string BuildVersionA` — The build version to generate optimized deltas from
- L1028 _public field_ `public string BuildVersionB` — The build version to generate optimized deltas to
- L1032 _public field_ `public string ClientId` — Specifies the client id allocated to you by Epic for uploading binaries to Epic's services.
- L1036 _public field_ `public string ClientSecret` — Specifies the client secret allocated to you by Epic for uploading binaries to Epic's services.
- L1040 _public field_ `public string ClientSecretEnvVar` — Specifies the name of an environment variable containing the client secret allocated to you by Epic for uploading binaries to Epic's services.
- L1044 _public field_ `public string OrganizationId` — Specifies the id of the organization that this product belongs to.
- L1048 _public field_ `public string ProductId` — Specifies the id of the product being uploaded.
- L1052 _public field_ `public string CommandLineFile` — File path to a file containing parameters for bpt to use (can be used in combination with parameters above, no duplicates)
- L1056 _public field_ `public string CloudDir` — The directory which will receive the generated manifest and chunks.
- L1058 _public field_ `public int ScanWindowSize = 0`

#### class `EpicGames.MCP.Automation.BuildPatchToolBase.ListBinariesOptions`  
`public class ListBinariesOptions`  
_public; L1061-1107_
- L1063-1065 _public ctor_ `public ListBinariesOptions()`
- L1070 _public field_ `public string ArtifactId` — The id of the artifact.
- L1074 _public field_ `public string ClientId` — Specifies the client id allocated to you by Epic for uploading binaries to Epic's services.
- L1078 _public field_ `public string ClientSecret` — Specifies the client secret allocated to you by Epic for uploading binaries to Epic's services.
- L1082 _public field_ `public string ClientSecretEnvVar` — Specifies the name of an environment variable containing the client secret allocated to you by Epic for uploading binaries to Epic's services.
- L1086 _public field_ `public string OrganizationId` — Specifies the id of the organization that this product belongs to.
- L1090 _public field_ `public string ProductId` — Specifies the id of the product being uploaded.
- L1094 _public field_ `public bool OnlyLabeled` — List only labeled binaries
- L1098 _public field_ `public int Num = -1` — Max Number of binaries to list
- L1102 _public field_ `public string OutputFile` — name of json formated output file to dump the binaries to
- L1106 _public field_ `public string CommandLineFile` — File path to a file containing parameters for bpt to use (can be used in combination with parameters above, no duplicates)

#### class `EpicGames.MCP.Automation.BuildPatchToolBase.ListBinariesOutput`  
`public class ListBinariesOutput`  
_public; L1109-1139_
- L1111-1112 _public ctor_ `public ListBinariesOutput()`
- L1138 _public field_ `public List<ListBinariesOutputBinary> Binaries`

#### class `EpicGames.MCP.Automation.BuildPatchToolBase.ListBinariesOutput.ListBinariesOutputBinary`  
`public class ListBinariesOutputBinary`  
_public; L1114-1137_
- L1121 _public field_ `public List<ListBinariesOutputLabel> Labels`
- L1122 _public field_ `public string ArtifactId`
- L1123 _public field_ `public string BuildVersion`
- L1124 _public field_ `public DateTime Created`
- L1125 _public field_ `public DateTime Updated`
- L1126 _public field_ `public string ManifestHash`
- L1127 _public field_ `public int Rvn`
- L1135 _public field_ `public ListBinariesOutputManifestLocation ManifestLocation`
- L1136 _public field_ `public bool IsResuable`

#### class `EpicGames.MCP.Automation.BuildPatchToolBase.ListBinariesOutput.ListBinariesOutputBinary.ListBinariesOutputLabel`  
`public class ListBinariesOutputLabel`  
_public; L1116-1120_
- L1118 _public field_ `public string LabelName`
- L1119 _public field_ `public MCPPlatform Platform`

#### class `EpicGames.MCP.Automation.BuildPatchToolBase.ListBinariesOutput.ListBinariesOutputBinary.ListBinariesOutputManifestLocation`  
`public class ListBinariesOutputManifestLocation`  
_public; L1128-1134_
- L1130 _public field_ `public string Url`
- L1131 _public field_ `public string HttpMethod`
- L1132 _public field_ `public List<string> HttpHeaders`
- L1133 _public field_ `public DateTime Expires`

#### class `EpicGames.MCP.Automation.BuildPatchToolBase.ListBinariesOutputBinaryJsonFormat`  
`public class ListBinariesOutputBinaryJsonFormat`  
_public; L1140-1186_
- L1147 _public field_ `public List<ListBinariesOutputLabelJsonFormat> Labels`
- L1148 _public field_ `public string ArtifactId`
- L1149 _public field_ `public string BuildVersion`
- L1150 _public field_ `public DateTime Created`
- L1151 _public field_ `public DateTime Updated`
- L1152 _public field_ `public string ManifestHash`
- L1153 _public field_ `public int Rvn`
- L1155 _public field_ `public ListBinariesOutput.ListBinariesOutputBinary.ListBinariesOutputManifestLocation ManifestLocation`
- L1156 _public field_ `public bool IsResuable`
- L1158-1185 _public method_ `public ListBinariesOutput.ListBinariesOutputBinary ConvertToOutputBinary()`

#### class `EpicGames.MCP.Automation.BuildPatchToolBase.ListBinariesOutputBinaryJsonFormat.ListBinariesOutputLabelJsonFormat`  
`public class ListBinariesOutputLabelJsonFormat`  
_public; L1142-1146_
- L1144 _public field_ `public string LabelName`
- L1145 _public field_ `public string Platform`

#### class `EpicGames.MCP.Automation.BuildPatchToolBase.CopyBinaryOptions`  
`public class CopyBinaryOptions`  
_public; L1189-1232_
- L1191-1193 _public ctor_ `public CopyBinaryOptions()`
- L1198 _public field_ `public string SourceArtifactId` — The id of the artifact to copy from
- L1203 _public field_ `public string DestArtifactId` — The id of the artifact to copy to
- L1207 _public field_ `public string BuildVersion` — The build version that is copied
- L1211 _public field_ `public string ClientId` — Specifies the client id allocated to you by Epic for uploading binaries to Epic's services.
- L1215 _public field_ `public string ClientSecret` — Specifies the client secret allocated to you by Epic for uploading binaries to Epic's services.
- L1219 _public field_ `public string ClientSecretEnvVar` — Specifies the name of an environment variable containing the client secret allocated to you by Epic for uploading binaries to Epic's services.
- L1223 _public field_ `public string OrganizationId` — Specifies the id of the organization that this product belongs to.
- L1227 _public field_ `public string ProductId` — Specifies the id of the product being uploaded.
- L1231 _public field_ `public string CommandLineFile` — File path to a file containing parameters for bpt to use (can be used in combination with parameters above, no duplicates)

#### class `EpicGames.MCP.Automation.BuildPatchToolBase.BuildPatchToolException`  
`public class BuildPatchToolException : AutomationTool.AutomationException`  
_public; L1234-1297_
- inherits: `AutomationTool.AutomationException`
- L1245 _public field_ `public BPTErrorCode ResolvedErrorCode`
- L1246 _public field_ `public string[] LogFileLines`
- L1247-1281 _public ctor_ `public BuildPatchToolException(string StdOutLogFileName, AutomationTool.AutomationException Exception) : base(Exception.ErrorCode, Exception.Message)`
- L1283-1291 _public method_ `public void DumpLogFile()`
- L1292-1295 _public method_ `public override string ToString()`

#### enum `EpicGames.MCP.Automation.BuildPatchToolBase.BuildPatchToolException.BPTErrorCode`  
`public enum BPTErrorCode`  
_public; L1236-1244_
- L1238 _public* enumerator_ `Success`
- L1239 _public* enumerator_ `Unknown`
- L1240 _public* enumerator_ `Copy_Failed`
- L1241 _public* enumerator_ `Copy_Failed_Binary_Exists`
- L1242 _public* enumerator_ `Copy_Failed_No_Source_Binary`
- L1243 _public* enumerator_ `Num`

#### class `EpicGames.MCP.Automation.BuildPatchToolBase.CompactifyOptions`  
`public class CompactifyOptions`  
_public; L1306-1329_
- desc: Represents the options passed to the compactify process
- L1308 _private const_ `private const int DEFAULT_DATA_AGE_THRESHOLD = 2`
- L1310-1313 _public ctor_ `public CompactifyOptions()`
- L1318 _public field_ `public string CompactifyDirectory` — BuildPatchTool will run a compactify on this directory.
- L1322 _public field_ `public bool bPreviewCompactify` — Corresponds to the -preview parameter
- L1328 _public field_ `public int DataAgeThreshold` — Patch data files modified within this number of days will *not* be deleted, to ensure that any patch files being written out by a. patch generation process are not deleted before their corresponding manifest file(s) can be written out. NOTE: this should be set to a value larger than the expected maximum time that a build could take.

#### class `EpicGames.MCP.Automation.BuildPatchToolBase.DataEnumerationOptions`  
`public class DataEnumerationOptions`  
_public; L1331-1345_
- L1336 _public field_ `public string ManifestFile` — The file path to the manifest to enumerate from.
- L1340 _public field_ `public string OutputFile` — The file path to where the list will be saved out, containing \r\n separated cloud relative file paths.
- L1344 _public field_ `public bool bIncludeSize` — When true, the output will include the size of each file on each line, separated by \t

#### class `EpicGames.MCP.Automation.BuildPatchToolBase.ManifestMergeOptions`  
`public class ManifestMergeOptions`  
_public; L1347-1378_
- L1352 _public field_ `public string ManifestA` — The file path to the base manifest.
- L1356 _public field_ `public string ManifestB` — The file path to the update manifest.
- L1360 _public field_ `public string ManifestC` — The file path to the output manifest.
- L1364 _public field_ `public string BuildVersion` — The new version string for the build being produced.
- L1368 _public field_ `public MCPPlatform Platform` — Used as part of the build version string.
- L1372 _public field_ `public HashSet<string> FilesToKeepFromA` — Optional. The set of files that should be kept from ManifestA.
- L1376 _public field_ `public HashSet<string> FilesToKeepFromB` — Optional. The set of files that should be kept from ManifestB.

#### class `EpicGames.MCP.Automation.BuildPatchToolBase.ManifestDiffOptions`  
`public class ManifestDiffOptions`  
_public; L1380-1411_
- L1385 _public field_ `public string ManifestA` — The file path to the base manifest.
- L1389 _public field_ `public HashSet<string> InstallTagsA` — The install tags to use for ManifestA.
- L1393 _public field_ `public string ManifestB` — The file path to the update manifest.
- L1397 _public field_ `public HashSet<string> InstallTagsB` — The install tags to use for ManifestB.
- L1401 _public field_ `public List<HashSet<string>> CompareTagSets` — Tag sets to be compared between manifests
- L1404 _public field_ `public List<HashSet<string>> CompareNewTagSet`
- L1407 _public field_ `public string DeltaFilenameTrailer`
- L1410 _public field_ `public bool bRequireOptimizedDelta`

#### class `EpicGames.MCP.Automation.BuildPatchToolBase.ManifestDiffOutput`  
`public class ManifestDiffOutput`  
_public; L1413-1528_
- L1519 _public field_ `public ManifestSummary ManifestA` — The manifest detail for the source build of the differential.
- L1523 _public field_ `public ManifestSummary ManifestB` — The manifest detail for the target build of the differential.
- L1527 _public field_ `public ManifestDiff Differential` — The differential details for the patch from ManifestA's build to ManifestB's build.

#### class `EpicGames.MCP.Automation.BuildPatchToolBase.ManifestDiffOutput.ManifestSummary`  
`public class ManifestSummary`  
_public; L1415-1455_
- L1420 _public field_ `public string AppName` — The AppName field from the manifest file.
- L1424 _public field_ `public uint AppId` — The AppId field from the manifest file.
- L1428 _public field_ `public string VersionString` — The VersionString field from the manifest file.
- L1432 _public field_ `public ulong DownloadSize` — The total size of chunks in the build.
- L1436 _public field_ `public ulong BuildSize` — The total size of disk space required for the build.
- L1441 _public field_ `public Dictionary<string, ulong> IndividualTagDownloadSizes` — The list of download sizes for each individual install tag that was used. Note that the sum of these can be higher than the actual total due to possibility of shares files.
- L1441 _public field_ `public Dictionary< IndividualTagDownloadSizes` — The list of download sizes for each individual install tag that was used. Note that the sum of these can be higher than the actual total due to possibility of shares files.
- L1445 _public field_ `public Dictionary<string, ulong> CompareTagSetDownloadSizes` — The list of download sizes for each tag set that was in the list to be analyzed.
- L1445 _public field_ `public Dictionary< CompareTagSetDownloadSizes` — The list of download sizes for each tag set that was in the list to be analyzed.
- L1450 _public field_ `public Dictionary<string, ulong> IndividualTagBuildSizes` — The list of build sizes for each individual install tag that was used. Note that the sum of these can be higher than the actual total due to possibility of shares files.
- L1450 _public field_ `public Dictionary< IndividualTagBuildSizes` — The list of build sizes for each individual install tag that was used. Note that the sum of these can be higher than the actual total due to possibility of shares files.
- L1454 _public field_ `public Dictionary<string, ulong> CompareTagSetBuildSizes` — The list of build sizes for each tag set that was in the list to be analyzed.
- L1454 _public field_ `public Dictionary< CompareTagSetBuildSizes` — The list of build sizes for each tag set that was in the list to be analyzed.

#### class `EpicGames.MCP.Automation.BuildPatchToolBase.ManifestDiffOutput.ManifestDiff`  
`public class ManifestDiff`  
_public; L1456-1515_
- L1461 _public field_ `public List<string> NewFilePaths` — The list of build relative paths for files which were added by the patch from ManifestA to ManifestB, subject to using the tags that were provided.
- L1465 _public field_ `public List<string> RemovedFilePaths` — The list of build relative paths for files which were removed by the patch from ManifestA to ManifestB, subject to using the tags that were provided.
- L1469 _public field_ `public List<string> ChangedFilePaths` — The list of build relative paths for files which were changed between ManifestA and ManifestB, subject to using the tags that were provided.
- L1473 _public field_ `public List<string> UnchangedFilePaths` — The list of build relative paths for files which were unchanged between ManifestA and ManifestB, subject to using the tags that were provided.
- L1477 _public field_ `public List<string> NewChunkPaths` — The list of cloud directory relative paths for all new chunks required by the patch from ManifestA to ManifestB, subject to using the tags that were provided.
- L1481 _public field_ `public ulong DeltaDownloadSize` — The required download size for the patch from ManifestA to ManifestB, subject to using the tags that were provided.
- L1485 _public field_ `public ulong TempDiskSpaceReq` — The required disk space to apply the patch from ManifestA to ManifestB, subject to using the tags that were provided.
- L1490 _public field_ `public Dictionary<string, ulong> IndividualTagDeltaSizes` — The list of delta sizes for each individual install tag that was used. Note that the sum of these can be higher than the actual total due to possibility of shares files.
- L1490 _public field_ `public Dictionary< IndividualTagDeltaSizes` — The list of delta sizes for each individual install tag that was used. Note that the sum of these can be higher than the actual total due to possibility of shares files.
- L1494 _public field_ `public Dictionary<string, ulong> CompareTagSetDeltaSizes` — The list of delta sizes for each tag set that was in the list to be analyzed.
- L1494 _public field_ `public Dictionary< CompareTagSetDeltaSizes` — The list of delta sizes for each tag set that was in the list to be analyzed.
- L1498 _public field_ `public Dictionary<string, ulong> CompareTagSetTempDiskSpaceReqs` — The list of disk space requirements to apply the patch for each tag set that was in the list to be analyzed.
- L1498 _public field_ `public Dictionary< CompareTagSetTempDiskSpaceReqs` — The list of disk space requirements to apply the patch for each tag set that was in the list to be analyzed.
- L1514 _public field_ `public List<float> InstallTimeCoefficients` — Install time coefficients represent an estimation for time to install the patch. These are not accurate timing representations, but are comparable between runs with different versions. They can be used to spot out of the ordinary time requirements for installing an update. The list if non-null will contain 6 entries as follows: InstallTimeCoefficients[0] - Low-Spec using DestructiveInstall. InstallTimeCoefficients[1] - Low-Spec using NonDestructiveInstall. InstallTimeCoefficients[2] - Mid-Spec using DestructiveInstall. InstallTimeCoefficients[3] - Mid-Spec using NonDestructiveInstall. InstallTimeCoefficients[4] - High-Spec using DestructiveInstall. InstallTimeCoefficients[5] - High-Spec using NonDestructiveInstall. Low-Spec was taken from 25 percentile as of July 2019. Mid-Spec was taken from 50 percentile as of July 2019. High-Spec was taken from 75 percentile as of July 2019. If the BPT version being used does not support this feature, or a problem occurred, InstallTimeCoefficients w

#### class `EpicGames.MCP.Automation.BuildPatchToolBase.BinaryDiffOptions`  
`public class BinaryDiffOptions`  
_public; L1530-1584_
- L1535 _public field_ `public string ArtifactId` — The id of the artifact.
- L1539 _public field_ `public HashSet<string> InstallTagsA` — The install tags to use for ManifestA.
- L1543 _public field_ `public string BuildVersionA` — The build version to generate optimized deltas from
- L1547 _public field_ `public HashSet<string> InstallTagsB` — The install tags to use for ManifestB.
- L1551 _public field_ `public string BuildVersionB` — The build version to generate optimized deltas to
- L1555 _public field_ `public string ClientId` — Specifies the client id allocated to you by Epic for uploading binaries to Epic's services.
- L1559 _public field_ `public string ClientSecret` — Specifies the client secret allocated to you by Epic for uploading binaries to Epic's services.
- L1563 _public field_ `public string ClientSecretEnvVar` — Specifies the name of an environment variable containing the client secret allocated to you by Epic for uploading binaries to Epic's services.
- L1567 _public field_ `public string OrganizationId` — Specifies the id of the organization that this product belongs to.
- L1571 _public field_ `public string ProductId` — Specifies the id of the product being uploaded.
- L1575 _public field_ `public string CommandLineFile` — File path to a file containing parameters for bpt to use (can be used in combination with parameters above, no duplicates)
- L1579 _public field_ `public List<HashSet<string>> CompareTagSets` — Tag sets to be compared between manifests
- L1583 _public field_ `public string OutputFile` — Specifies in quotes the file path where the diff will be exported as a JSON object.

#### class `EpicGames.MCP.Automation.BuildPatchToolBase.AutomationTestsOptions`  
`public class AutomationTestsOptions`  
_public; L1586-1592_
- L1591 _public field_ `public string TestList` — Optionally specify the tests to run.

#### class `EpicGames.MCP.Automation.BuildPatchToolBase.PackageChunksOptions`  
`public class PackageChunksOptions`  
_public; L1594-1650_
- L1599 _public field_ `public string ManifestFile` — Specifies the file path to the manifest to enumerate chunks from.
- L1603 _public field_ `public string PrevManifestFile` — Specifies the file path to a manifest for a previous build, this will be used to filter out chunks.
- L1607 _public field_ `public string OutputFile` — Specifies the file path to the output package. An extension of .chunkdb will be added if not present.
- L1612 _public field_ `public string CloudDir` — An optional parameter which, if present, specifies the directory where chunks to be packaged can be found. If not specified, the manifest file's location will be used as the cloud directory.
- L1619 _public field_ `public ulong? MaxOutputFileSize` — Optional value, to restrict the maximum size of each output file (in bytes). If not specified, then only one output file will be produced, containing all the data. If specified, then the output files will be generated as Name.part01.chunkdb, Name.part02.chunkdb etc. The part number will have the number of digits required for highest numbered part.
- L1626 _public field_ `public HashSet<string> PrevManifestTags` — Optionally provide a tagset to filter the files available from PrevManifestFile. This may increase chunks saved into the chunkdb files, in order to serve data from files that are not expected to be available. Most of the time this should be the union of all tags in TagSetSplit, unless tagging is changed between the two manifests. An empty string must be included to include untagged files. Leaving this variable null will include all files.
- L1635 _public field_ `public List<HashSet<string>> TagSetSplit` — Optionally provide a list of tagsets to split chunkdb files on. First all data from the tagset at index 0 will be saved, then any extra data needed for tagset at index 1, and so on. Note that this means the chunkdb files produced for tagset at index 1 will not contain some required data for that tagset if the data already got saved out as part of tagset at index 0, and thus the chunkdb files are additive with no dupes. If it is desired that each tagset's chunkdb files contain the duplicate data, then PackageChunks should be executed once per tagset rather than once will all tagsets. An empty string must be included in one of the tagsets to include untagged file data in that tagset. Leaving this variable null will include data for all files.
- L1639 _public field_ `public string FeatureLevel` — Specifies the desired output FeatureLevel of BuildPatchTool, if this is not provided BPT will default to before optimised deltas.
- L1643 _public field_ `public string AdditionalArguments` — Specifies additional arguments to be passed to BPT
- L1646 _public field_ `public string DeltaFilenameTrailer`
- L1649 _public field_ `public bool RequireOptimizedDelta`

#### class `EpicGames.MCP.Automation.BuildPatchToolBase.PackageChunksOutput`  
`public class PackageChunksOutput`  
_public; L1652-1666_
- L1657 _public field_ `public List<string> ChunkDbFilePaths` — The list of full filepaths of all created chunkdb files.
- L1665 _public field_ `public List<List<int>> TagSetLookupTable` — If PackageChunksOptions.TagSetSplit was provided, then this variable will contain a lookup table of TagSetSplit index to List of ChunkDbFilePaths indices. e.g. TagSetLookupTable[0] = [ 0, 1, 2, 3, ..., n ] TagSetLookupTable[1] = [] an empty List would mean that all data for this tagset was already included in the chunkdb(s) for previous tagset(s). TagSetLookupTable[2] = [ n+1, n+2, ..., n+m ]

#### class `EpicGames.MCP.Automation.BuildPatchToolBase.ChunkDeltaOptimiseOptions`  
`public class ChunkDeltaOptimiseOptions`  
_public; L1668-1700_
- L1673 _public field_ `public string SourceManifest` — The file path to the base manifest.
- L1677 _public field_ `public string DestinationManifest` — The file path to the update manifest. New data will be added to the cloud directory that this manifest is in.
- L1681 _public field_ `public ulong DiffAbortThreshold` — Specifies in bytes, an upper limit for original diffs to try to enhance.
- L1687 _public field_ `public Dictionary<string, List<string>> SourceManifestAliases`
- L1687 _public field_ `public Dictionary< SourceManifestAliases`
- L1688 _public field_ `public Dictionary<string, List<string>> DestinationManifestAliases`
- L1688 _public field_ `public Dictionary< DestinationManifestAliases`
- L1691 _public field_ `public List<string> SourceTagsToIgnore`
- L1692 _public field_ `public List<string> DestinationTagsToIgnore`
- L1695 _public field_ `public string DeltaFilenameTrailer`
- L1699 _public field_ `public int MinCompressionPct = 0`

#### class `EpicGames.MCP.Automation.BuildPatchToolBase.ManifestMetadataOptions`  
`public class ManifestMetadataOptions`  
_public; L1702-1706_
- L1704 _public field_ `public string SourceManifestFilename`
- L1705 _public field_ `public string OutputFilename`

#### class `EpicGames.MCP.Automation.BuildPatchToolBase.ManifestMetadataOutput`  
`public class ManifestMetadataOutput`  
_public; L1707-1728_
- L1709 _public field_ `public string FeatureLevel`
- L1710 _public field_ `public ulong AppId`
- L1711 _public field_ `public string AppName`
- L1712 _public field_ `public string VersionString`
- L1713 _public field_ `public string UniqueBuildId`
- L1714 _public field_ `public string LaunchExe`
- L1715 _public field_ `public string LaunchCommand`
- L1716 _public field_ `public ulong DownloadSize`
- L1717 _public field_ `public ulong BuildSize`
- L1718 _public field_ `public List<string> FileTagList`
- L1727 _public field_ `public List<ManifestMetadataOutputFile> Files`

#### class `EpicGames.MCP.Automation.BuildPatchToolBase.ManifestMetadataOutput.ManifestMetadataOutputFile`  
`public class ManifestMetadataOutputFile`  
_public; L1720-1726_
- L1722 _public field_ `public string Filename`
- L1723 _public field_ `public List<string> Tags`
- L1724 _public field_ `public string SHA1`
- L1725 _public field_ `public ulong FileSize`

#### class `EpicGames.MCP.Automation.BuildMetadataBase`  
`public abstract class BuildMetadataBase`  
_public; L1871-1880_
- desc: Class that provides programmatic access to the metadata field from build info.
- L1879 _public method_ `abstract public BuildMetadataBase MergeWith(BuildMetadataBase Other, bool bClobber = true)` — Merges provided metadata object into this one.

#### class `EpicGames.MCP.Automation.BuildInfoPublisherBase`  
`public abstract class BuildInfoPublisherBase`  
_public; L1885-2036_
- desc: Helper class
- L1887 _private* field_ `static BuildInfoPublisherBase Handler = null`
- L1889-1912 _public method_ `public static BuildInfoPublisherBase Get()`
- L1919 _public method_ `abstract public BuildMetadataBase CreateBuildMetadata(string JsonRepresentation)` — Creates a metadata object implementation, initialized with the provided JSON object.
- L1927 _public method_ `abstract public bool BuildExists(BuildPatchToolStagingInfo StagingInfo, string McpConfigName)` — Determines whether a given build is registered in build info
- L1933 _public method_ `abstract public void PostBuildInfo(BuildPatchToolStagingInfo stagingInfo)` — Given a MCPStagingInfo defining our build info, posts the build to the MCP BuildInfo Service.
- L1940 _public method_ `abstract public void PostBuildInfo(BuildPatchToolStagingInfo StagingInfo, string McpConfigName)` — Given a MCPStagingInfo defining our build info and a MCP config name, posts the build to the requested MCP BuildInfo Service.
- L1949 _public method_ `abstract public void SetMetadata(BuildPatchToolStagingInfo StagingInfo, string Key, string Value, string McpConfigName)` — Sets a value in the key/value pair metadata associated with the specified build.
- L1957 _public method_ `abstract public List<string> GetBuildLabels(BuildPatchToolStagingInfo StagingInfo, string McpConfigName)` — Given a BuildVersion defining our a build, return the labels applied to that build
- L1965 _public method_ `abstract public string GetBuildManifestUrl(BuildPatchToolStagingInfo StagingInfo, string McpConfigName)` — Given a staging info defining our build, return the manifest url for that registered build
- L1974 _public method_ `abstract public string GetBuildManifestUrl(string AppName, string BuildVersionWithPlatform, string McpConfigName)` — Given a staging info defining our build, return the manifest url for that registered build
- L1982 _public method_ `abstract public string GetBuildManifestHash(BuildPatchToolStagingInfo StagingInfo, string McpConfigName)` — Given a staging info defining our build, return the manifest hash for that registered build
- L1991 _public method_ `abstract public BuildMetadataBase GetBuildMetaData(BuildPatchToolStagingInfo StagingInfo, string McpConfigName, bool bClobber = false)` — Given a staging info defining our build, fetch and apply the metadata for that registered build.
- L1999 _public method_ `abstract public string GetLabelWithPlatform(string DestinationLabel, MCPPlatform Platform)` — Get a label string for the specific Platform requested.
- L2006 _public method_ `abstract public string GetBuildVersionWithPlatform(BuildPatchToolStagingInfo StagingInfo)` — Get a BuildVersion string with the Platform concatenated on.
- L2015 _public method_ `abstract public string GetLabeledBuildVersion(string AppName, string LabelName, string McpConfigName)` — Get the BuildVersion for a build that is labeled under a specific appname.
- L2023 _public method_ `abstract public void LabelBuild(BuildPatchToolStagingInfo StagingInfo, string DestinationLabelWithPlatform, string McpConfigName)` — Apply the requested label to the requested build in the BuildInfo backend for the requested MCP environment
- L2035 _public method_ `abstract public void BuildPromotionCompleted(BuildPatchToolStagingInfo stagingInfo, string AppName, string BuildVersion, string ManifestRelativePath, string PlatformName, string LabelName)` — Informs Patcher Service of a new build availability after async labeling is complete (this usually means the build was copied to a public file server before the label could be applied).

#### class `EpicGames.MCP.Automation.McpAccountServiceBase`  
`public abstract class McpAccountServiceBase`  
_public; L2041-2153_
- desc: Helpers for using the MCP account service
- L2043 _private* field_ `static McpAccountServiceBase Handler = null`
- L2045 _private* field_ `Dictionary<string, Tuple<string, DateTime>> CachedTokens = ...`
- L2045 _private* field_ `Dictionary< string`
- L2045 _private* field_ `Dictionary< CachedTokens = new Dictionary<string, Tuple<string, DateTime>>()`
- L2046 _private* field_ `readonly object CachedTokensLock = new object()`
- L2048-2071 _public method_ `public static McpAccountServiceBase Get()`
- L2079-2116 _public method_ `public string GetClientToken(McpConfigData McpConfig, bool bSuppressLogs = false)` — Gets an OAuth client token for an environment using the default client id and client secret
- L2123-2127 _public method_ `public string GetClientToken(BuildPatchToolStagingInfo StagingInfo)` — Gets an OAuth client token using the default client id and client secret and the environment for the specified staging info
- L2136-2140 _public method_ `public string GetClientToken(McpConfigData McpConfig, string ClientId, string ClientSecret)` — Gets an OAuth client token for an environment using the specified client id and client secret
- L2150 _public method_ `public abstract string GetClientToken(McpConfigData McpConfig, string ClientId, string ClientSecret, out DateTime Expiry)` — Gets an OAuth client token for an environment using the specified client id and client secret
- L2152 _public method_ `public abstract string SendWebRequest(WebRequest Upload, string Method, string ContentType, byte[] Data)`

#### class `EpicGames.MCP.Automation.CloudStorageBase`  
`public abstract class CloudStorageBase`  
_public; L2158-2581_
- desc: Helper class to manage files stored in some arbitrary cloud storage system
- L2160 _private field_ `private static readonly object LockObj = new object()`
- L2161 _private field_ `private static Dictionary<string, CloudStorageBase> Handlers = ...`
- L2161 _private field_ `private static Dictionary< Handlers = new Dictionary<string, CloudStorageBase>()`
- L2162 _private const_ `private const string DEFAULT_INSTANCE_NAME = "DefaultInstance"`
- L2168-2171 _public method_ `public static CloudStorageBase Get()` — Gets the default instance of CloudStorageBase
- L2179-2186 _public method_ `public static CloudStorageBase GetByName(string InstanceName)` — Gets an instance of CloudStorageBase. Multiple calls with the same instance name will return the same object.
- L2188-2223 _private method_ `private static CloudStorageBase GetByNameImpl(string InstanceName)`
- L2230 _public method_ `abstract public void Init(Dictionary<string,object> Config, bool bForce = false)` — Initializes the provider. Configuration data to initialize the provider. The exact format of the data is provider specific. It might, for example, contain an API key.
- L2239 _public method_ `abstract public bool FileExists(string Container, string Identifier, bool bQuiet = false)` — Retrieves a file from the cloud storage provider
- L2250 _public method_ `abstract public long DownloadFile(string Container, string Identifier, string OutputFile, out string ContentType, bool bOverwrite = false)` — Retrieves a file from the cloud storage provider and saves it to disk.
- L2259 _public method_ `abstract public byte[] GetFile(string Container, string Identifier, out string ContentType)` — Retrieves a file from the cloud storage provider.
- L2274 _public method_ `abstract public PostFileResult PostFile(string Container, string Identifier, byte[] Contents, string ContentType = null, bool bGzip = false, bool bOverwrite = true, bool bMakePublic = false, bool bQuiet = false, IDictionary<string, object> Metadata = null)` — Posts a file to the cloud storage provider.
- L2289 _public method_ `abstract public Task<PostFileResult> PostFileAsync(string Container, string Identifier, byte[] Contents, string ContentType = null, bool bGzip = false, bool bOverwrite = true, bool bMakePublic = false, bool bQuiet = false, IDictionary<string, object> Metadata = null)` — Posts a file to the cloud storage provider asynchronously.
- L2304 _public method_ `abstract public PostFileResult PostFile(string Container, string Identifier, string SourceFilePath, string ContentType = null, bool bGzip = false, bool bOverwrite = true, bool bMakePublic = false, bool bQuiet = false, IDictionary<string, object> Metadata = null)` — Posts a file to the cloud storage provider.
- L2319 _public method_ `abstract public Task<PostFileResult> PostFileAsync(string Container, string Identifier, string SourceFilePath, string ContentType = null, bool bGzip = false, bool bOverwrite = true, bool bMakePublic = false, bool bQuiet = false, IDictionary<string, object> Metadata = null)` — Posts a file to the cloud storage provider asynchronously.
- L2336-2339 _public method_ `public PostFileResult PostMultipartFile(string Container, string Identifier, string SourceFilePath, int NumConcurrentConnections, decimal PartSizeMegabytes = 5.0m, string ContentType = null, bool bGzip = false, bool bOverwrite = true, bool bMakePublic = false, bool bQuiet = false, IDictionary<string, object> Metadata = null)` — Posts a file to the cloud storage provider using multiple connections.
- L2356 _public method_ `abstract public Task<PostFileResult> PostMultipartFileAsync(string Container, string Identifier, string SourceFilePath, int NumConcurrentConnections, decimal PartSizeMegabytes = 5.0m, string ContentType = null, bool bGzip = false, bool bOverwrite = true, bool bMakePublic = false, bool bQuiet = false, IDictionary<string, object> Metadata = null)` — Posts a file to the cloud storage provider using multiple connections asynchronously.
- L2365 _public method_ `abstract public void DeleteFile(string Container, string Identifier)` — Deletes a file from cloud storage
- L2372 _public method_ `abstract public void DeleteFolder(string Container, string FolderIdentifier)` — Deletes a folder from cloud storage
- L2381-2389 _public method_ `public string[] ListFolders(string Container, string Prefix, Action<ListOptions> Options)` — Retrieves a list of folders from the cloud storage provider
- L2398 _public method_ `abstract public string[] ListFolders(string Container, string Prefix, ListOptions Options)` — Retrieves a list of folders from the cloud storage provider
- L2408-2415 _public method_ `public string[] ListFiles(string Container, string Prefix = null, bool bRecursive = true, bool bQuiet = false)` — DEPRECATED. Retrieves a list of files from the cloud storage provider. See overload with ListOptions for non-deprecated use.
- L2424-2432 _public method_ `public string[] ListFiles(string Container, string Prefix, Action<ListOptions> Options)` — Retrieves a list of files from the cloud storage provider
- L2441 _public method_ `abstract public string[] ListFiles(string Container, string Prefix, ListOptions Options)` — Retrieves a list of files from the cloud storage provider.
- L2450-2458 _public method_ `public ObjectMetadata[] ListFilesWithMetadata(string Container, string Prefix, Action<ListOptions> Options)` — Retrieves a list of files together with basic metadata from the cloud storage provider
- L2467 _public method_ `abstract public ObjectMetadata[] ListFilesWithMetadata(string Container, string Prefix, ListOptions Options)` — Retrieves a list of files together with basic metadata from the cloud storage provider.
- L2476 _public method_ `abstract public void SetMetadata(string Container, string Identifier, IDictionary<string, object> Metadata, bool bMerge = true)` — Sets one or more items of metadata on an object in cloud storage
- L2483 _public method_ `abstract public Dictionary<string, string> GetMetadata(string Container, string Identifier)` — Gets all items of metadata on an object in cloud storage. Metadata values are all returned as strings.
- L2491 _public method_ `abstract public T GetMetadata<T>(string Container, string Identifier, string MetadataKey)` — Gets an item of metadata from an object in cloud storage. The object is casted to the specified type.
- L2498 _public method_ `abstract public void TouchFile(string Container, string Identifier)` — Updates the timestamp on a particular file in cloud storage to the current time.
- L2507 _public method_ `abstract public bool CopyChunksToCloudStorage(string Container, BuildPatchToolStagingInfo StagingInfo, bool bForce = false)` — Copies manifest and chunks from a staged location to cloud storage.
- L2517 _public method_ `abstract public bool CopyChunksToCloudStorage(string Container, string RemoteCloudDir, string ManifestFilePath, bool bForce = false)` — Copies manifest and its chunks from a specific path to a given target folder in the cloud.
- L2525 _public method_ `abstract public bool IsManifestOnCloudStorage(string Container, BuildPatchToolStagingInfo StagingInfo)` — Verifies whether a manifest for a given build is in cloud storage.

#### class `EpicGames.MCP.Automation.CloudStorageBase.PostFileResult`  
`public class PostFileResult`  
_public; L2527-2543_
- L2532 _public property_ `public string ObjectURL { get; set; }` — Set to the URL of the uploaded file on success
- L2538 _public property_ `public bool bSuccess { get; set; }`
- L2542 _public property_ `public long FileSize { get; set; }` — Upload file size

#### class `EpicGames.MCP.Automation.CloudStorageBase.ListOptions`  
`public class ListOptions`  
_public; L2548-2571_
- desc: Encapsulates options used when listing files or folders using ListFiles and ListFolders
- L2550-2555 _public ctor_ `public ListOptions()`
- L2560 _public property_ `public bool bQuiet { get; set; }` — If set to true, all log output for the operation is suppressed. Defaults to false.
- L2565 _public property_ `public bool bRecursive { get; set; }` — Indicates whether the list of files returned should traverse subfolders. Defaults to false.
- L2570 _public property_ `public bool bReturnURLs { get; set; }` — If true, returns the full URL to the listed objects. If false, returns their identifier within the container. Defaults to true.

#### class `EpicGames.MCP.Automation.CloudStorageBase.ObjectMetadata`  
`public class ObjectMetadata`  
_public; L2573-2580_
- L2575 _public property_ `public string ETag { get; set; }`
- L2576 _public property_ `public string Path { get; set; }`
- L2577 _public property_ `public string Url { get; set; }`
- L2578 _public property_ `public DateTime LastModified { get; set; }`
- L2579 _public property_ `public long Size { get; set; }`

#### class `EpicGames.MCP.Automation.CatalogServiceBase`  
`public abstract class CatalogServiceBase`  
_public; L2583-2638_
- L2585 _private* field_ `static CatalogServiceBase Handler = null`
- L2587-2610 _public method_ `public static CatalogServiceBase Get()`
- L2612 _public method_ `public abstract string GetAppName(string ItemId, string[] EngineVersions, string McpConfigName)`
- L2613 _public method_ `public abstract string[] GetNamespaces(string McpConfigName)`
- L2614 _public method_ `public abstract McpCatalogItem GetItemById(string Namespace, string ItemId, string McpConfigName)`
- L2615 _public method_ `public abstract IEnumerable<McpCatalogItem> GetAllItems(string Namespace, string McpConfigName)`

#### class `EpicGames.MCP.Automation.CatalogServiceBase.McpCatalogItem`  
`public class McpCatalogItem`  
_public; L2617-2629_
- L2619 _public property_ `public string Id { get; set; }`
- L2620 _public property_ `public string Title { get; set; }`
- L2621 _public property_ `public string Description { get; set; }`
- L2622 _public property_ `public string LongDescription { get; set; }`
- L2623 _public property_ `public string TechnicalDetails { get; set; }`
- L2624 _public property_ `public string Namespace { get; set; }`
- L2625 _public property_ `public string Status { get; set; }`
- L2626 _public property_ `public DateTime CreationDate { get; set; }`
- L2627 _public property_ `public DateTime LastModifiedDate { get; set; }`
- L2628 _public property_ `public ReleaseInfo[] ReleaseInfo { get; set; }`

#### class `EpicGames.MCP.Automation.CatalogServiceBase.ReleaseInfo`  
`public class ReleaseInfo`  
_public; L2631-2637_
- L2633 _public property_ `public string AppId { get; set; }`
- L2634 _public property_ `public string[] CompatibleApps { get; set; }`
- L2635 _public property_ `public string[] Platform { get; set; }`
- L2636 _public property_ `public DateTime DateAdded { get; set; }`

#### class `EpicGames.MCP.Config.McpConfigHelper`  
`public class McpConfigHelper`  
_public; L2646-2703_
- desc: Class for retrieving MCP configuration data
- L2649 _private field_ `private static Dictionary<string, McpConfigData> Configs`
- L2649 _private field_ `private static Dictionary< Configs`
- L2651-2702 _public method_ `public static McpConfigData Find(string ConfigName)`

#### class `EpicGames.MCP.Config.McpConfigData`  
`public class McpConfigData`  
_public; L2706-2758_
- L2708 _public ctor_ `public McpConfigData()`
- L2711-2714 _public ctor_ `public McpConfigData(string InName, string InAccountBaseUrl, string InFortniteBaseUrl, string InLauncherBaseUrl, string InBuildInfoV2BaseUrl, string InLauncherV2BaseUrl, string InCatalogBaseUrl, string InArtifactBaseUrl, string InClientId, string InClientSecret) : this(InName, InAccountBaseUrl, InFortniteBaseUrl, InLauncherBaseUrl, InBuildInfoV2BaseUrl, InLauncherV2BaseUrl, InCatalogBaseUrl, InArtifactBaseUrl, InClientId, () => InClientSecret)` — attrs: `[Obsolete("This constructor is deprecated. Use the alternative which accepts a Func<string> for the client secret.", false)]`
- L2716-2728 _public ctor_ `public McpConfigData(string InName, string InAccountBaseUrl, string InFortniteBaseUrl, string InLauncherBaseUrl, string InBuildInfoV2BaseUrl, string InLauncherV2BaseUrl, string InCatalogBaseUrl, string InArtifactBaseUrl, string InClientId, Func<string> InClientSecret)`
- L2730 _public property_ `public string Name { get; set; }`
- L2731 _public property_ `public string AccountBaseUrl { get; set; }`
- L2732 _public property_ `public string FortniteBaseUrl { get; set; }`
- L2733 _public property_ `public string LauncherBaseUrl { get; set; }`
- L2734 _public property_ `public string BuildInfoV2BaseUrl { get; set; }`
- L2735 _public property_ `public string LauncherV2BaseUrl { get; set; }`
- L2736 _public property_ `public string CatalogBaseUrl { get; set; }`
- L2737 _public property_ `public string ArtifactBaseUrl { get; set; }`
- L2738 _public property_ `public string ClientId { get; set; }`
- L2739 _public field_ `public Func<string> ClientSecret`
- L2741-2743 _public method_ `public virtual void Initialize(string ConfigName)`
- L2745-2757 _public method_ `public void SpewValues()`

#### class `EpicGames.MCP.Config.McpConfigMapper`  
`public class McpConfigMapper`  
_public; L2760-2780_
- L2762-2765 _public method_ `static public McpConfigData FromMcpConfigKey(string McpConfigKey)`
- L2767-2779 _public method_ `static public McpConfigData FromStagingInfo(EpicGames.MCP.Automation.BuildPatchToolStagingInfo StagingInfo)`

### `Source/Programs/AutomationTool/AutomationUtils/MacHostPlatform.cs` (AutomationUtils.Automation)


#### class `AutomationTool.MacHostPlatform`  
`class MacHostPlatform : HostPlatform`  
_internal*; L12-171_
- inherits: `HostPlatform`
- L14 _private* field_ `static string CachedFrameworkMsbuildExe = string.Empty`
- L16-34 _public method_ `public override string GetFrameworkMsbuildExe()`
- L36-39 _public property_ `public override string RelativeBinariesFolder { get; }`
- L41-70 _public method_ `public override string GetUnrealExePath(string UnrealExe)`
- L72-75 _public property_ `public override string LocalBuildsLogFolder { get; }`
- L77 _private field_ `private string P4ExePath = null`
- L79-102 _public property_ `public override string P4Exe { get; }`
- L104-108 _public method_ `public override Process CreateProcess(string AppName)`
- L110-143 _public method_ `public override void SetupOptionsForRun(ref string AppName, ref CommandUtils.ERunOptions Options, ref string CommandLine)`
- L145-148 _public method_ `public override void SetConsoleCtrlHandler(ProcessManager.CtrlHandlerDelegate Handler)`
- L150-153 _public property_ `public override UnrealTargetPlatform HostEditorPlatform { get; }`
- L155-158 _public property_ `public override string PdbExtension { get; }`
- L160 _private* field_ `static string[] SystemServices = new string[] { }`
- L164-170 _public property_ `public override string[] DontKillProcessList { get; }`

### `Source/Programs/AutomationTool/AutomationUtils/P4Environment.cs` (AutomationUtils.Automation)


#### class `AutomationTool.P4Environment`  
`public class P4Environment`  
_public; L22-556_
- desc: Contains detected Perforce settings.
- L27-31 _public property_ `public string ServerAndPort { get; set; }` — The Perforce host and port number (eg. perforce:1666)
- L36-40 _public property_ `public string User { get; set; }` — The Perforce username
- L45-49 _public property_ `public string Client { get; set; }` — Name of the Perforce client containing UAT.
- L54-58 _public property_ `public string Branch { get; set; }` — The current branch containing UAT. This may be a depot path (e.g. //depot/UE4) or the name of a stream (e.g. //UE5/Main).
- L63-67 _public property_ `public string ClientRoot { get; set; }` — Path to the root of the branch as a client path (//MyClient/UE).
- L72-86 _public property_ `public int Changelist { get; set; }` — The currently synced changelist.
- L91 _private field_ `private int ChangelistInternal = -1` — Backing value for the current changelist property
- L96-110 _public property_ `public int CodeChangelist { get; set; }` — The currently synced code changelist.
- L115 _private field_ `private int CodeChangelistInternal = -1` — Backing value for the current code changelist
- L117 _private* property_ `static ILogger Logger => ...`
- L122-269 _internal ctor_ `internal P4Environment(CommandEnvironment CmdEnv)` — Constructor. Derives the Perforce environment settings.
- L275-303 _private method_ `private static string DetectP4Port()` — Attempts to detect source control server address from environment variables.
- L309-333 _public method_ `public static string DetectUserName(P4Connection Connection)` — Detects current user name.
- L343-405 _private method_ `private static P4ClientInfo DetectClient(P4Connection Connection, string UserName, string HostName, string AutomationToolDll)` — Detects a workspace given the current user name, host name and depot path.
- L412-430 _private method_ `private static P4ClientInfo GetMostRecentClient(List<P4ClientInfo> Clients)` — Given a list of clients with the same owner and root path, tries to find the most recently accessed one.
- L438-460 _private method_ `private static string DetectCurrentCL(P4Connection Connection, string ClientRootPath)` — Detects the current changelist the workspace is synced to.
- L466-509 _private method_ `private static async Task<int> DetectCurrentCodeCL(PerforceConnection Connection, int Changelist)` — Detects the current code changelist the workspace is synced to.
- L519-555 _private method_ `private static void DetectRootPaths(P4Connection Connection, string LocalRootPath, P4ClientInfo ThisClient, out string BuildRootPath, out string ClientRootPath)` — Detects root paths for the specified client.

### `Source/Programs/AutomationTool/AutomationUtils/P4Utils.cs` (AutomationUtils.Automation)


#### class `AutomationTool.RequireP4Attribute`  
`public class RequireP4Attribute : Attribute`  
_public; L25-27_
- inherits: `Attribute`
- desc: Declares that the command type requires P4Environment.

#### class `AutomationTool.DoesNotNeedP4CLAttribute`  
`public class DoesNotNeedP4CLAttribute : Attribute`  
_public; L32-34_
- inherits: `Attribute`
- desc: Declares that the command type does not access Changelist or CodeChangelist from P4Environment.

#### class `AutomationTool.P4Exception`  
`public class P4Exception : AutomationException`  
_public; L36-45_
- inherits: `AutomationException`
- L38-39 _public ctor_ `public P4Exception(string Msg) : base(Msg)`
- L40-41 _public ctor_ `public P4Exception(string Msg, Exception InnerException) : base(InnerException, Msg)`
- L43-44 _public ctor_ `public P4Exception(string Format, params object[] Args) : base(Format, Args)`

#### enum `AutomationTool.P4LineEnd`  
`public enum P4LineEnd`  
_public; L47-54_
- L49 _public* enumerator_ `Local = 0`
- L50 _public* enumerator_ `Unix = 1`
- L51 _public* enumerator_ `Mac = 2`
- L52 _public* enumerator_ `Win = 3`
- L53 _public* enumerator_ `Share = 4`

#### enum `AutomationTool.P4SubmitOption`  
`public enum P4SubmitOption`  
_public; L57-63_
- attrs: `[Flags]`
- L59 _public* enumerator_ `SubmitUnchanged = 1`
- L60 _public* enumerator_ `RevertUnchanged = 2`
- L61 _public* enumerator_ `LeaveUnchanged = 4`
- L62 _public* enumerator_ `Reopen = 8`

#### enum `AutomationTool.P4ClientOption`  
`public enum P4ClientOption`  
_public; L66-83_
- attrs: `[Flags]`
- L68 _public* enumerator_ `None = 0`
- L69 _public* enumerator_ `NoAllWrite = 1`
- L70 _public* enumerator_ `NoClobber = 2`
- L71 _public* enumerator_ `NoCompress = 4`
- L72 _public* enumerator_ `NoModTime = 8`
- L73 _public* enumerator_ `NoRmDir = 16`
- L74 _public* enumerator_ `Unlocked = 32`
- L75 _public* enumerator_ `AllWrite = 64`
- L76 _public* enumerator_ `Clobber = 128`
- L77 _public* enumerator_ `Compress = 256`
- L78 _public* enumerator_ `Locked = 512`
- L79 _public* enumerator_ `ModTime = 1024`
- L80 _public* enumerator_ `RmDir = 2048`
- L81 _public* enumerator_ `NoAltSync = 4096`
- L82 _public* enumerator_ `AltSync = 8192`

#### class `AutomationTool.P4ClientInfo`  
`public class P4ClientInfo`  
_public; L85-115_
- L87 _public field_ `public string Name`
- L88 _public field_ `public string RootPath`
- L89 _public field_ `public string Host`
- L90 _public field_ `public string Owner`
- L91 _public field_ `public string Stream`
- L92 _public field_ `public DateTime Access`
- L93 _public field_ `public P4LineEnd LineEnd`
- L94 _public field_ `public P4ClientOption Options`
- L95 _public field_ `public P4SubmitOption SubmitOptions = P4SubmitOption.SubmitUnchanged`
- L96 _public field_ `public List<KeyValuePair<string, string>> View = ...`
- L96 _public field_ `public List<KeyValuePair< View = new List<KeyValuePair<string, string>>()`
- L98-109 _public method_ `public bool Matches(P4ClientInfo Other)`
- L111-114 _public method_ `public override string ToString()`

#### enum `AutomationTool.P4FileType`  
`public enum P4FileType`  
_public; L117-139_
- L120 _public* enumerator_ `Unknown` — attrs: `[Description("unknown")]`
- L122 _public* enumerator_ `Text` — attrs: `[Description("text")]`
- L124 _public* enumerator_ `Binary` — attrs: `[Description("binary")]`
- L126 _public* enumerator_ `Resource` — attrs: `[Description("resource")]`
- L128 _public* enumerator_ `Temp` — attrs: `[Description("tempobj")]`
- L130 _public* enumerator_ `Symlink` — attrs: `[Description("symlink")]`
- L132 _public* enumerator_ `Apple` — attrs: `[Description("apple")]`
- L134 _public* enumerator_ `Unicode` — attrs: `[Description("unicode")]`
- L136 _public* enumerator_ `Utf16` — attrs: `[Description("utf16")]`
- L138 _public* enumerator_ `Utf8` — attrs: `[Description("utf8")]`

#### enum `AutomationTool.P4FileAttributes`  
`public enum P4FileAttributes`  
_public; L142-168_
- attrs: `[Flags]`
- L145 _public* enumerator_ `None = 0` — attrs: `[Description("")]`
- L147 _public* enumerator_ `Unicode = 1 << 0` — attrs: `[Description("u")]`
- L149 _public* enumerator_ `Executable = 1 << 1` — attrs: `[Description("x")]`
- L151 _public* enumerator_ `Writeable = 1 << 2` — attrs: `[Description("w")]`
- L153 _public* enumerator_ `LocalModTimes = 1 << 3` — attrs: `[Description("m")]`
- L155 _public* enumerator_ `RCS = 1 << 4` — attrs: `[Description("k")]`
- L157 _public* enumerator_ `Exclusive = 1 << 5` — attrs: `[Description("l")]`
- L159 _public* enumerator_ `DeltasPerRevision = 1 << 6` — attrs: `[Description("D")]`
- L161 _public* enumerator_ `Uncompressed = 1 << 7` — attrs: `[Description("F")]`
- L163 _public* enumerator_ `Compressed = 1 << 8` — attrs: `[Description("C")]`
- L165 _public* enumerator_ `Archive = 1 << 9` — attrs: `[Description("X")]`
- L167 _public* enumerator_ `Revisions = 1 << 10` — attrs: `[Description("S")]`

#### enum `AutomationTool.P4Action`  
`public enum P4Action`  
_public; L170-196_
- L173 _public* enumerator_ `None` — attrs: `[Description("none")]`
- L175 _public* enumerator_ `Add` — attrs: `[Description("add")]`
- L177 _public* enumerator_ `Edit` — attrs: `[Description("edit")]`
- L179 _public* enumerator_ `Delete` — attrs: `[Description("delete")]`
- L181 _public* enumerator_ `Branch` — attrs: `[Description("branch")]`
- L183 _public* enumerator_ `MoveAdd` — attrs: `[Description("move/add")]`
- L185 _public* enumerator_ `MoveDelete` — attrs: `[Description("move/delete")]`
- L187 _public* enumerator_ `Integrate` — attrs: `[Description("integrate")]`
- L189 _public* enumerator_ `Import` — attrs: `[Description("import")]`
- L191 _public* enumerator_ `Purge` — attrs: `[Description("purge")]`
- L193 _public* enumerator_ `Archive` — attrs: `[Description("archive")]`
- L195 _public* enumerator_ `Unknown` — attrs: `[Description("unknown")]`

#### struct `AutomationTool.P4FileStat`  
`public struct P4FileStat`  
_public; L198-218_
- L200 _public field_ `public P4FileType Type`
- L201 _public field_ `public P4FileAttributes Attributes`
- L202 _public field_ `public P4Action Action`
- L203 _public field_ `public string Change`
- L204 _public field_ `public bool IsOldType`
- L206-213 _public ctor_ `public P4FileStat(P4FileType Type, P4FileAttributes Attributes, P4Action Action)`
- L215 _public field_ `public static readonly P4FileStat Invalid = new P4FileStat(P4FileType.Unknown, P4FileAttributes.None, P4Action.None)`
- L217 _public property_ `public bool IsValid { get; }`

#### class `AutomationTool.P4WhereRecord`  
`public class P4WhereRecord`  
_public; L220-226_
- L222 _public field_ `public bool bUnmap`
- L223 _public field_ `public string DepotFile`
- L224 _public field_ `public string ClientFile`
- L225 _public field_ `public string Path`

#### class `AutomationTool.P4HaveRecord`  
`public class P4HaveRecord`  
_public; L228-240_
- L230 _public field_ `public string DepotFile`
- L231 _public field_ `public string ClientFile`
- L232 _public field_ `public int Revision`
- L234-239 _public ctor_ `public P4HaveRecord(string DepotFile, string ClientFile, int Revision)`

#### class `AutomationTool.P4Spec`  
`public class P4Spec`  
_public; L242-356_
- L244 _public field_ `public List<KeyValuePair<string, string>> Sections`
- L244 _public field_ `public List<KeyValuePair< Sections`
- L249-252 _public ctor_ `public P4Spec()` — Default constructor.
- L259-263 _public method_ `public string GetField(string Name)` — Gets the current value of a field with the given name
- L270-281 _public method_ `public void SetField(string Name, string Value)` — Sets the value of an existing field, or adds a new one with the given name
- L288-333 _public method_ `public static P4Spec FromString(string Text)` — Parses a spec (clientspec, branchspec, changespec) from an array of lines
- L339-355 _public method_ `public override string ToString()` — Formats a P4 specification as a block of text

#### enum `AutomationTool.P4IntegrateAction`  
`public enum P4IntegrateAction`  
_public; L361-471_
- desc: Describes the action performed by the user when resolving the integration
- L367 _public* enumerator_ `BranchFrom` — attrs: `[Description("branch from")]` — file did not previously exist; it was created as a copy of partner-file
- L373 _public* enumerator_ `BranchInto` — attrs: `[Description("branch into")]` — partner-file did not previously exist; it was created as a copy of file.
- L379 _public* enumerator_ `MergeFrom` — attrs: `[Description("merge from")]` — file was integrated from partner-file, accepting merge.
- L385 _public* enumerator_ `MergeInto` — attrs: `[Description("merge into")]` — file was integrated into partner-file, accepting merge.
- L391 _public* enumerator_ `MovedFrom` — attrs: `[Description("moved from")]` — file was integrated from partner-file, accepting theirs and deleting the original.
- L397 _public* enumerator_ `MovedInto` — attrs: `[Description("moved into")]` — file was integrated into partner-file, accepting theirs and creating partner-file if it did not previously exist.
- L403 _public* enumerator_ `CopyFrom` — attrs: `[Description("copy from")]` — file was integrated from partner-file, accepting theirs.
- L409 _public* enumerator_ `CopyInto` — attrs: `[Description("copy into")]` — file was integrated into partner-file, accepting theirs.
- L415 _public* enumerator_ `Ignored` — attrs: `[Description("ignored")]` — file was integrated from partner-file, accepting yours.
- L421 _public* enumerator_ `IgnoredBy` — attrs: `[Description("ignored by")]` — file was integrated into partner-file, accepting yours.
- L427 _public* enumerator_ `DeleteFrom` — attrs: `[Description("delete from")]` — file was integrated from partner-file, and partner-file had been previously deleted.
- L433 _public* enumerator_ `DeleteInto` — attrs: `[Description("delete into")]` — file was integrated into partner-file, and file had been previously deleted.
- L439 _public* enumerator_ `EditFrom` — attrs: `[Description("edit from")]` — file was integrated from partner-file, and file was edited within the p4 resolve process.
- L445 _public* enumerator_ `EditInto` — attrs: `[Description("edit into")]` — file was integrated into partner-file, and partner-file was reopened for edit before submission.
- L451 _public* enumerator_ `AddFrom` — attrs: `[Description("add from")]` — file was integrated from a deleted partner-file, and partner-file was reopened for add (that is, someone restored a deleted file by syncing back to a pre-deleted revision and adding the file).
- L457 _public* enumerator_ `AddInto` — attrs: `[Description("add into")]` — file was integrated into previously nonexistent partner-file, and partner-file was reopened for add before submission.
- L463 _public* enumerator_ `Undid` — attrs: `[Description("undid")]` — file was reverted to a previous revision
- L469 _public* enumerator_ `UndoneBy` — attrs: `[Description("undone by")]` — file was reverted to a previous revision

#### class `AutomationTool.P4IntegrationRecord`  
`public class P4IntegrationRecord`  
_public; L476-528_
- desc: Stores integration information for a file revision
- L481 _public field_ `public readonly P4IntegrateAction Action` — The integration action performed for this file
- L486 _public field_ `public readonly string OtherFile` — The partner file for this integration
- L491 _public field_ `public readonly int StartRevisionNumber` — Min revision of the partner file for this integration
- L496 _public field_ `public readonly int EndRevisionNumber` — Max revision of the partner file for this integration
- L505-511 _public ctor_ `public P4IntegrationRecord(P4IntegrateAction Action, string OtherFile, int StartRevisionNumber, int EndRevisionNumber)` — Constructor
- L517-527 _public method_ `public override string ToString()` — Summarize this record for display in the debugger

#### class `AutomationTool.P4RevisionRecord`  
`public class P4RevisionRecord`  
_public; L533-627_
- desc: Stores a revision record for a file
- L538 _public field_ `public readonly int RevisionNumber` — The revision number of this file
- L543 _public field_ `public readonly int ChangeNumber` — The changelist responsible for this revision of the file
- L548 _public field_ `public readonly P4Action Action` — Action performed to the file in this revision
- L553 _public field_ `public readonly string Type` — Type of the file
- L558 _public field_ `public readonly DateTime DateTime` — Timestamp of this modification
- L563 _public field_ `public readonly string UserName` — Author of the changelist
- L568 _public field_ `public readonly string ClientName` — Client that submitted this changelist
- L573 _public field_ `public readonly long FileSize` — Size of the file, or -1 if not specified
- L578 _public field_ `public readonly string Digest` — Digest of the file, or null if not specified
- L583 _public field_ `public readonly string Description` — Description of this changelist
- L588 _public field_ `public readonly P4IntegrationRecord[] Integrations` — Integration records for this revision
- L604-617 _public ctor_ `public P4RevisionRecord(int RevisionNumber, int ChangeNumber, P4Action Action, string Type, DateTime DateTime, string UserName, string ClientName, long FileSize, string Digest, string Description, P4IntegrationRecord[] Integrations)` — Constructor
- L623-626 _public method_ `public override string ToString()` — Format this record for display in the debugger

#### class `AutomationTool.P4FileRecord`  
`public class P4FileRecord`  
_public; L632-663_
- desc: Record output by the filelog command
- L637 _public field_ `public string DepotPath` — Path to the file in the depot
- L642 _public field_ `public P4RevisionRecord[] Revisions` — Revisions of this file
- L649-653 _public ctor_ `public P4FileRecord(string DepotPath, P4RevisionRecord[] Revisions)` — Constructor
- L659-662 _public method_ `public override string ToString()` — Return the depot path of the file for display in the debugger

#### enum `AutomationTool.P4FileLogOptions`  
`public enum P4FileLogOptions`  
_public; L669-705_
- attrs: `[Flags]`
- desc: Options for the filelog command
- L674 _public* enumerator_ `None = 0` — No options
- L679 _public* enumerator_ `ContentHistory = 1` — Display file content history instead of file name history.
- L684 _public* enumerator_ `FollowAcrossBranches = 2` — Follow file history across branches.
- L689 _public* enumerator_ `FullDescriptions = 4` — List long output, with the full text of each changelist description.
- L694 _public* enumerator_ `LongDescriptions = 8` — List long output, with the full text of each changelist description truncated at 250 characters.
- L699 _public* enumerator_ `DoNotFollowPromotedTaskStreams = 16` — When used with the ContentHistory option, do not follow content of promoted task streams.
- L704 _public* enumerator_ `IgnoreNonContributoryIntegrations = 32` — Display a shortened form of output by ignoring non-contributory integrations

#### enum `AutomationTool.P4StreamType`  
`public enum P4StreamType`  
_public; L710-736_
- desc: Type of a Perforce stream
- L715 _public* enumerator_ `Mainline` — A mainline stream
- L720 _public* enumerator_ `Development` — A development stream
- L725 _public* enumerator_ `Release` — A release stream
- L730 _public* enumerator_ `Virtual` — A virtual stream
- L735 _public* enumerator_ `Task` — A task stream

#### enum `AutomationTool.P4StreamOptions`  
`public enum P4StreamOptions`  
_public; L742-768_
- attrs: `[Flags]`
- desc: Options for a stream definition
- L747 _public* enumerator_ `Locked = 1` — The stream is locked
- L752 _public* enumerator_ `OwnerSubmit = 4` — Only the owner may submit to the stream
- L757 _public* enumerator_ `ToParent = 4` — Integrations from this stream to its parent are expected
- L762 _public* enumerator_ `FromParent = 8` — Integrations from this stream from its parent are expected
- L767 _public* enumerator_ `MergeDown = 16` — Undocumented?

#### class `AutomationTool.P4StreamRecord`  
`public class P4StreamRecord`  
_public; L774-881_
- attrs: `[DebuggerDisplay("{Stream}")]`
- desc: Contains information about a stream, as returned by the 'p4 streams' command
- L779 _public field_ `public string Stream` — Path to the stream
- L784 _public field_ `public DateTime Update` — Last time the stream definition was updated
- L789 _public field_ `public DateTime Access` — Last time the stream definition was accessed
- L794 _public field_ `public string Owner` — Owner of this stream
- L799 _public field_ `public string Name` — Name of the stream. This may be modified after the stream is initially created, but it's underlying depot path will not change.
- L804 _public field_ `public string Parent` — The parent stream
- L809 _public field_ `public P4StreamType Type` — Type of the stream
- L814 _public field_ `public string Description` — User supplied description of the stream
- L819 _public field_ `public P4StreamOptions Options` — Options for the stream definition
- L824 _public field_ `public Nullable<bool> FirmerThanParent` — Whether this stream is more stable than the parent stream
- L829 _public field_ `public bool ChangeFlowsToParent` — Whether changes from this stream flow to the parent stream
- L834 _public field_ `public bool ChangeFlowsFromParent` — Whether changes from this stream flow from the parent stream
- L839 _public field_ `public string BaseParent` — The mainline branch associated with this stream
- L857-871 _public ctor_ `public P4StreamRecord(string Stream, DateTime Update, DateTime Access, string Owner, string Name, string Parent, P4StreamType Type, string Description, P4StreamOptions Options, Nullable<bool> FirmerThanParent, bool ChangeFlowsToParent, bool ChangeFlowsFromParent, string BaseParent)` — Constructor
- L877-880 _public method_ `public override string ToString()` — Return the path of this stream for display in the debugger

#### enum `AutomationTool.P4SeverityCode`  
`public enum P4SeverityCode`  
_public; L886-893_
- desc: Error severity codes. Taken from the p4java documentation.
- L888 _public* enumerator_ `Empty = 0`
- L889 _public* enumerator_ `Info = 1`
- L890 _public* enumerator_ `Warning = 2`
- L891 _public* enumerator_ `Failed = 3`
- L892 _public* enumerator_ `Fatal = 4`

#### enum `AutomationTool.P4GenericCode`  
`public enum P4GenericCode`  
_public; L898-915_
- desc: Generic error codes that can be returned by the Perforce server. Taken from the p4java documentation.
- L900 _public* enumerator_ `None = 0`
- L901 _public* enumerator_ `Usage = 1`
- L902 _public* enumerator_ `Unknown = 2`
- L903 _public* enumerator_ `Context = 3`
- L904 _public* enumerator_ `Illegal = 4`
- L905 _public* enumerator_ `NotYet = 5`
- L906 _public* enumerator_ `Protect = 6`
- L907 _public* enumerator_ `Empty = 17`
- L908 _public* enumerator_ `Fault = 33`
- L909 _public* enumerator_ `Client = 34`
- L910 _public* enumerator_ `Admin = 35`
- L911 _public* enumerator_ `Config = 36`
- L912 _public* enumerator_ `Upgrade = 37`
- L913 _public* enumerator_ `Comm = 38`
- L914 _public* enumerator_ `TooBig = 39`

#### class `AutomationTool.P4ReturnCode`  
`public class P4ReturnCode`  
_public; L920-965_
- desc: Represents a error return value from Perforce.
- L925 _public field_ `public string Code` — The value of the "code" field returned by the server
- L930 _public field_ `public P4SeverityCode Severity` — The severity of this error
- L935 _public field_ `public P4GenericCode Generic` — The generic error code associated with this message
- L940 _public field_ `public string Message` — The message text
- L949-955 _public ctor_ `public P4ReturnCode(string Code, P4SeverityCode Severity, P4GenericCode Generic, string Message)` — Constructor
- L961-964 _public method_ `public override string ToString()` — Formats this error for display in the debugger

#### class `AutomationTool.CommandUtils`  
`public partial class CommandUtils`  
_public; L967-1169_
- L969 _private field_ `static private P4Connection PerforceConnection`
- L970 _private field_ `static private P4Environment PerforceEnvironment`
- L971 _private field_ `static private IPerforceSettings PerforceSettings`
- L973-983 _public property_ `static public P4Connection P4 { get; }`
- L985-995 _public property_ `static public P4Environment P4Env { get; }`
- L997-1007 _public property_ `static public IPerforceSettings P4Settings { get; }`
- L1013-1022 _internal method_ `static internal void InitP4Environment()` — Initializes build environment. If the build command needs a specific env-var mapping or has an extended BuildEnvironment, it must implement this method accordingly.
- L1027-1030 _internal method_ `static internal void InitDefaultP4Connection()` — Initializes default source control connection.
- L1035-1049 _public property_ `public static bool P4Enabled { get; set; }` — Check if P4 is supported.
- L1050 _private field_ `private static bool? bP4Enabled`
- L1055-1069 _public property_ `public static bool P4CLRequired { get; set; }` — Check if P4CL is required.
- L1070 _private field_ `private static bool? bP4CLRequired`
- L1075-1090 _public property_ `public static bool AllowSubmit { get; set; }` — Checks whether commands are allowed to submit files into P4.
- L1091 _private field_ `private static bool? bAllowSubmit`
- L1098-1132 _internal method_ `internal static void InitP4Support(List<CommandInfo> CommandsToExecute, Dictionary<string, Type> Commands)` — Sets up P4Enabled, AllowSubmit properties. Note that this does not initialize P4 environment.
- L1141-1168 _private method_ `private static void CheckIfCommandsRequireP4(List<CommandInfo> CommandsToExecute, Dictionary<string, Type> Commands, out bool bRequireP4, out bool bRequireCL)` — Checks if any of the commands to execute has [RequireP4] attribute.

#### class `AutomationTool.P4Label`  
`public class P4Label`  
_public; L1174-1187_
- desc: Class that stores labels info.
- L1177 _public property_ `public string Name { get; set; }`
- L1180 _public property_ `public DateTime Date { get; set; }`
- L1182-1186 _public ctor_ `public P4Label(string Name, DateTime Date)`

#### class `AutomationTool.P4Connection`  
`public partial class P4Connection`  
_public; L1192-4509_
- desc: Perforce connection.
- L1197 _private field_ `private string GlobalOptions` — List of global options for this connection (client/user)
- L1201 _private field_ `private string GlobalOptionsWithoutClient` — List of global options for this connection (client/user)
- L1205 _public property_ `public string LogPath { get; set; }` — Path where this connection's log is to go to
- L1215-1232 _public ctor_ `public P4Connection(string User, string Client, string ServerAndPort = null, string P4LogPath = null, string AdditionalOpts = null)` — Initializes P4 connection
- L1239-1242 _private* method_ `static string NoSpewFilter(string Message)` — A filter that suppresses all output od stdout/stderr
- L1253-1256 _public method_ `public IProcessResult P4(string CommandLine, string Input = null, bool AllowSpew = true, bool WithClient = true, bool SpewIsVerbose = false)` — Shortcut to Run but with P4.exe as the program name.
- L1268-1321 _public method_ `public IProcessResult P4(string ExtraGlobalOptions, string CommandLine, string Input, bool AllowSpew = true, bool WithClient = true, bool SpewIsVerbose = false)` — Shortcut to Run but with P4.exe as the program name.
- L1333-1341 _public method_ `public bool P4Output(out string Output, string ExtraGlobalOptions, string CommandLine, string Input = null, bool AllowSpew = true, bool WithClient = true)` — Calls p4 and returns the output.
- L1353-1382 _public method_ `public bool P4Output(out string[] OutputLines, string ExtraGlobalOptions, string CommandLine, string Input = null, bool AllowSpew = true, bool WithClient = true)` — Calls p4 and returns the output.
- L1393-1400 _public method_ `public void LogP4(string ExtraGlobalOptions, string CommandLine, string Input = null, bool AllowSpew = true, bool WithClient = true, bool SpewIsVerbose = false)` — Calls p4 command and writes the output to a logfile.
- L1413-1429 _public method_ `public bool LogP4Output(out string Output, string ExtraGlobalOptions, string CommandLine, string Input = null, bool AllowSpew = true, bool WithClient = true, bool SpewIsVerbose = false)` — Calls p4 and returns the output and writes it also to a logfile.
- L1437-1517 _public method_ `public List<Dictionary<string, string>> P4TaggedOutput(string CommandLine, bool WithClient = true)` — Execute a Perforce command and parse the output as marshalled Python objects. This is more robustly defined than the text-based tagged output format, because it avoids ambiguity when returned fields can have newlines.
- L1525-1563 _public method_ `public static bool VerifyReturnCode(Dictionary<string, string> RawRecord, string ExpectedCode, out P4ReturnCode OtherReturnCode)` — Checks that the raw record data includes the given return code, or creates a ReturnCode value if it doesn't
- L1568-1595 _public method_ `public string GetAuthenticationToken()` — Invokes p4 login command.
- L1616 _private* field_ `static Dictionary<string, string> UserToEmailCache = ...`
- L1616 _private* field_ `static Dictionary< UserToEmailCache = new Dictionary<string, string>()`
- L1617-1642 _public method_ `public string UserToEmail(string User)`
- L1643 _private* field_ `static Dictionary<string, List<ChangeRecord>> ChangesCache = ...`
- L1643 _private* field_ `static Dictionary< ChangesCache = new Dictionary<string, List<ChangeRecord>>()`
- L1644-1785 _public method_ `public bool Changes(out List<ChangeRecord> ChangeRecords, string CommandLine, bool AllowSpew = true, bool UseCaching = false, bool LongComment = false, bool WithClient = false)`
- L1828-1846 _public method_ `public bool DescribeChangelist(int Changelist, out DescribeRecord DescribeRecord, bool AllowSpew = true, bool bShelvedFiles = false)` — Wraps P4 describe
- L1856-2041 _public method_ `public bool DescribeChangelists(List<int> Changelists, out List<DescribeRecord> DescribeRecords, bool AllowSpew = true, bool bShelvedFiles = false)` — Wraps P4 describe
- L2051-2067 _public method_ `public void Sync(string CommandLine, bool AllowSpew = true, bool SpewIsVerbose = false, int Retries=0, int MaxWait=0)` — Invokes p4 sync command.
- L2077-2111 _public method_ `public bool PreviewSync(out List<string> FilesPreviewSynced, string CommandLine, bool AllowSpew = true, bool SpewIsVerbose = false)` — Invokes p4 preview sync command and gets a list of preview synced files.
- L2120-2123 _public method_ `public void Unshelve(int FromCL, int ToCL, string CommandLine = "", bool SpewIsVerbose = false)` — Invokes p4 unshelve command.
- L2131-2134 _public method_ `public void Shelve(int FromCL, string CommandLine = "", bool AllowSpew = true)` — Invokes p4 shelve command.
- L2143-2146 _public method_ `public void ShelveNoRevert(int FromCL, string CommandLine = "", bool AllowSpew = true)` — Invokes p4 shelve command, without reverting existing shelf first (overwrites any existing shelved file) This means that any files that are already shelved, but not in the FromCL being shelved, they will still exist
- L2153-2160 _public method_ `public void DeleteShelvedFiles(int FromCL, bool AllowSpew = true)` — Deletes shelved files from a changelist
- L2168-2187 _public method_ `public void BatchedCommand(string Command, List<string> Files, bool AllowSpew = true)` — Invoke a command on a list of files, breaking up into multiple commands so as not to blow the max commandline length
- L2196-2199 _public method_ `public void Reopen(int CL, string CommandLine, bool AllowSpew = true)` — Invokes p4 reopen command.
- L2210-2213 _public method_ `public void Reopen(int CL, List<string> Files, bool AllowSpew = true)` — Invokes p4 reopen command with a list of files. IMPORTANT: because of commandline limits the file list will be broken up across multiple commands. This will fail if a "move" operation (that is made up of two files) is split between commandlines - they must be moved in the same operation
- L2221-2224 _public method_ `public void Edit(int CL, string CommandLine, bool AllowSpew = true)` — Invokes p4 edit command.
- L2232-2235 _public method_ `public void Edit(int CL, List<string> Files, bool AllowSpew = true)` — Invokes p4 edit command with a list of files.
- L2242-2261 _public method_ `public bool Edit_NoExceptions(int CL, string CommandLine)` — Invokes p4 edit command, no exceptions
- L2268-2271 _public method_ `public void Add(int CL, string CommandLine)` — Invokes p4 add command.
- L2279-2282 _public method_ `public void Add(int CL, List<string> Files, bool AllowSpew = true)` — Invokes p4 add command with a list of files.
- L2289-2292 _public method_ `public void Delete(int CL, string CommandLine)` — Invokes p4 delete command.
- L2300-2303 _public method_ `public void Delete(int CL, List<string> Files, bool AllowSpew = true)` — Invokes p4 delete command with a list of files.
- L2311-2314 _public method_ `public void Reconcile(int CL, string CommandLine, bool AllowSpew = true)` — Invokes p4 reconcile command.
- L2320-2323 _public method_ `public void ReconcilePreview(string CommandLine)` — Invokes p4 reconcile command.
- L2332-2335 _public method_ `public void ReconcileNoDeletes(int CL, string CommandLine, bool AllowSpew = true)` — Invokes p4 reconcile command. Ignores files that were removed.
- L2343-2346 _public method_ `public void Resolve(int CL, string CommandLine)` — Invokes p4 resolve command. Resolves all files by accepting yours and ignoring theirs.
- L2353-2356 _public method_ `public void Revert(string CommandLine, bool AllowSpew = true)` — Invokes revert command.
- L2364-2367 _public method_ `public void Revert(int CL, string CommandLine = "", bool AllowSpew = true)` — Invokes revert command.
- L2375-2378 _public method_ `public void Revert(int CL, List<string> Files, bool AllowSpew = true)` — Invokes p4 revert command with a list of files.
- L2384-2388 _public method_ `public void RevertUnchanged(int CL)` — Reverts all unchanged file from the specified changelist.
- L2395-2398 _public method_ `public void RevertAll(int CL, bool SpewIsVerbose = false)` — Reverts all files from the specified changelist.
- L2406-2410 _public method_ `public void Submit(int CL, bool Force = false, bool RevertIfFail = false)` — Submits the specified changelist.
- L2419-2567 _public method_ `public void Submit(int CL, out int SubmittedCL, bool Force = false, bool RevertIfFail = false)` — Submits the specified changelist.
- L2578-2617 _public method_ `public int CreateChange(string Owner = null, string Description = null, string User = null, string Type = null, bool AllowSpew = false)` — Creates a new changelist with the specified owner and description.
- L2627-2630 _public method_ `public void UpdateChange(int CL, string NewClient, string NewDescription, bool SpewIsVerbose = false)` — Updates a changelist with the given fields
- L2640-2670 _public method_ `public void UpdateChange(int CL, string NewUser, string NewClient, string NewDescription, bool SpewIsVerbose = false)` — Updates a changelist with the given fields
- L2679-2699 _public method_ `public void DeleteChange(int CL, bool RevertFiles = true, bool SpewIsVerbose = false, bool AllowSpew = true)` — Deletes the specified changelist.
- L2706-2722 _public method_ `public bool TryDeleteEmptyChange(int CL)` — Tries to delete the specified empty changelist.
- L2730-2738 _public method_ `public string ChangeOutput(int CL, bool AllowSpew = true)` — Returns the changelist specification.
- L2747-2785 _public method_ `public bool ChangeExists(int CL, out bool Pending, bool AllowSpew = true)` — Checks whether the specified changelist exists.
- L2794-2841 _public method_ `public List<string> ChangeFiles(int CL, out bool Pending, bool AllowSpew = true)` — Returns a list of files contained in the specified changelist.
- L2847-2855 _public method_ `public string OpenedOutput()` — Returns the output from p4 opened
- L2861-2871 _public method_ `public void DeleteLabel(string LabelName, bool AllowSpew = true)` — Deletes the specified label.
- L2883-2902 _public method_ `public void CreateLabel(string Name, string Options, string View, string Owner = null, string Description = null, string Date = null, string Time = null)` — Creates a new label.
- L2911-2914 _public method_ `public void Tag(string LabelName, string FilePath, bool AllowSpew = true)` — Invokes p4 tag command. Associates a named label with a file revision.
- L2922-2937 _public method_ `public void LabelSync(string LabelName, bool AllowSpew = true, string FileToLabel = "")` — Syncs a label to the current content of the client.
- L2945-2953 _public method_ `public void LabelToLabelSync(string FromLabelName, string ToLabelName, bool AllowSpew = true)` — Syncs a label from another label.
- L2960-2964 _public method_ `public bool LabelExistsAndHasFiles(string Name)` — Checks whether the specified label exists and has any files.
- L2973-2994 _public method_ `public bool LabelDescription(string Name, out string Description, bool AllowSpew = true)` — Returns the label description.
- L3001-3009 _public method_ `public P4Spec ReadLabelSpec(string Name, bool AllowSpew = true)` — Reads a label spec
- L3016-3019 _public method_ `public void UpdateLabelSpec(P4Spec Spec, bool AllowSpew = true)` — Updates a label with a new spec
- L3027-3058 _public method_ `public void UpdateLabelDescription(string Name, string NewDescription, bool AllowSpew = true)` — Updates a label description.
- L3061 _private field_ `private static readonly Regex ChangesListOutputPattern = new Regex(@"^Change\s+(?<number>\d+)\s+.+$", RegexOptions.Compiled | RegexOptions.Multiline)`
- L3067-3083 _public method_ `public int GetLatestCLNumber()` — Gets the latest CL number submitted to the depot. It equals to the @head.
- L3086 _private* field_ `static readonly Regex LabelsListOutputPattern = new Regex(@"^Label\s+(?<name>[\w\/\.-]+)\s+(?<date>\d{4}/\d{2}/\d{2} \d{2}:\d{2}:\d{2})\s+'(?<description>.+)'\s*$", RegexOptions.Compiled | RegexOptions.Multiline)`
- L3094-3112 _public method_ `public P4Label[] GetLabels(string Filter, bool bCaseSensitive = true)` — Gets all labels satisfying given filter.
- L3118-3135 _public method_ `public bool ValidateLabelContent(string LabelName)` — Validate label for some content.
- L3143-3165 _public method_ `public string DepotToLocalPath(string DepotFile, bool AllowSpew = true)` — Given a file path in the depot, returns the local disk mapping for the current view
- L3173-3243 _public method_ `public string[] DepotToLocalPaths(string[] DepotFiles, bool AllowSpew = true)` — Given a set of file paths in the depot, returns the local disk mapping for the current view
- L3253-3315 _public method_ `public P4WhereRecord[] Where(string DepotFile, bool AllowSpew = true)` — Determines the mappings for a depot file in the workspace, without that file having to exist. NOTE: This function originally allowed multiple depot paths at once. The "file(s) not in client view" messages are written to stderr rather than stdout, and buffering them separately garbles the output when they're merged together.
- L3323-3334 _public method_ `public bool FileExistsInDepot(string DepotFile, bool AllowSpew = false)` — Determines whether a file exists in the depot.
- L3341-3389 _public method_ `public P4FileStat FStat(string Filename)` — Gets file stats.
- L3397-3414 _public method_ `public void ChangeFileType(string Filename, P4FileAttributes Attributes, string Changelist = null)` — Set file attributes (additively)
- L3421-3477 _public method_ `public Dictionary<string, string> ParseTaggedP4Output(string Output)` — Parses P4 forms and stores them as a key/value pairs.
- L3484-3496 _public method_ `public static string FormatTaggedOutput(Dictionary<string, string> Record)` — Formats a tagged record as a string
- L3504-3513 _public method_ `public bool DoesClientExist(string ClientName, bool Quiet = false)` — Checks if the client exists in P4.
- L3521-3533 _public method_ `public P4ClientInfo GetClientInfo(string ClientName, bool Quiet = false)` — Gets client info.
- L3540-3544 _private method_ `private static object ParseEnumValues(string ValueText, Type EnumType)` — Parses a string with enum values separated with spaces.
- L3551-3617 _public method_ `public P4ClientInfo GetClientInfoInternal(string ClientName)` — Gets client info (does not check if the client exists)
- L3626-3670 _public method_ `public P4ClientInfo[] GetClientsForUser(string UserName, string PathUnderClientRoot = null, string AllowedStream = null)` — Gets all clients owned by the user.
- L3672-3675 _public method_ `public bool IsValidClientForFile(P4ClientInfo Info, string PathUnderClientRoot)`
- L3677-3691 _public method_ `public bool IsValidRootPathForFile(string RootPath, string PathUnderClientRoot)`
- L3699-3702 _public method_ `public void DeleteClient(string Name, bool Force = false, bool AllowSpew = true)` — Deletes a client.
- L3710-3737 _public method_ `public P4ClientInfo CreateClient(P4ClientInfo ClientSpec, bool AllowSpew = true)` — Creates a new client.
- L3745-3763 _public method_ `public List<string> Dirs(string CommandLine)` — Lists immediate sub-directories of the specified directory.
- L3770-3789 _protected method_ `protected Dictionary<string,string> MapFileOutputToActions(string P4Output)` — Takes P4 output from files or opened and returns a dictionary of paths/actions
- L3796-3816 _public method_ `public List<string> Files(string CommandLine)` — Run 'p4 files [cmdline]'and return a list of the files in the changelist (files being deleted are excluded)
- L3823-3844 _public method_ `public List<string> Opened(string CommandLine)` — Run 'p4 opened [cmdline]'and return a list of the files in the changelist (files being deleted are excluded)
- L3852-3864 _public method_ `public string Print(string DepotPath, bool AllowSpew = true)` — Gets the contents of a particular file in the depot without syncing it
- L3872-3883 _public method_ `public void PrintToFile(string DepotPath, string FileName, bool AllowSpew = true)` — Gets the contents of a particular file in the depot and writes it to a local file without syncing it
- L3891-3917 _public method_ `public List<int> StreamInterchanges(string StreamName, bool bReverse)` — Runs the 'interchanges' command on a stream, to determine a list of changelists that have not been integrated to its parent (or vice-versa, if bReverse is set).
- L3925-3928 _public method_ `public P4FileRecord[] FileLog(P4FileLogOptions Options, params string[] FileSpecs)` — Execute the 'filelog' command
- L3937-3940 _public method_ `public P4FileRecord[] FileLog(int MaxChanges, P4FileLogOptions Options, params string[] FileSpecs)` — Execute the 'filelog' command
- L3950-3966 _public method_ `public P4FileRecord[] FileLog(int ChangeNumber, int MaxChanges, P4FileLogOptions Options, params string[] FileSpecs)` — Execute the 'filelog' command
- L3977-4098 _public method_ `public P4ReturnCode TryFileLog(int ChangeNumber, int MaxChanges, P4FileLogOptions Options, string[] FileSpecs, out P4FileRecord[] OutRecords)` — Execute the 'filelog' command
- L4100 _private* field_ `static readonly DateTime UnixEpoch = new DateTime(1970, 1, 1, 0, 0, 0, DateTimeKind.Utc)`
- L4107-4110 _public method_ `public List<P4StreamRecord> Streams(string StreamPath)` — Enumerates all streams in a depot
- L4120-4171 _public method_ `public List<P4StreamRecord> Streams(string StreamPath, int MaxResults, string Filter, bool bUnloaded)` — Enumerates all streams in a depot
- L4173 _private* field_ `static readonly Regex HaveFilesOutputPattern = new Regex(@"(?<depot>.+)#(?<revision>\d+) - (?<client>.+)", RegexOptions.Compiled)`
- L4181-4223 _public method_ `public List<P4HaveRecord> HaveFiles(string Pattern)` — Get a information about synced files (p4 have) matching the given pattern. The information for each file includes the local path, depot path and the synced revision number.
- L4230-4243 _private* method_ `static Nullable<bool> ParseNullableBool(string Text)` — Parse a nullable boolean
- L4250-4283 _private* method_ `static P4StreamOptions ParseStreamOptions(string Text)` — Parse a list of stream option flags
- L4285-4297 _private* method_ `static Dictionary<string, T> GetEnumLookup<T>()`
- L4299 _private* field_ `static Lazy<Dictionary<string, P4Action>> DescriptionToAction = ...`
- L4299 _private* field_ `static Lazy<Dictionary< DescriptionToAction = new Lazy<Dictionary<string, P4Action>>(() => GetEnumLookup<P4Action>())`
- L4301-4309 _private* method_ `static P4Action ParseActionText(string ActionText)`
- L4311 _private* field_ `static Lazy<Dictionary<string, P4IntegrateAction>> DescriptionToIntegrationAction = ...`
- L4311 _private* field_ `static Lazy<Dictionary< DescriptionToIntegrationAction = new Lazy<Dictionary<string, P4IntegrateAction>>(() => GetEnumLookup<P4IntegrateAction>())`
- L4313-4321 _private* method_ `static P4IntegrateAction ParseIntegrateActionText(string ActionText)`
- L4323-4326 _private* method_ `static DateTime ParseDateTime(string DateTimeText)`
- L4333-4360 _public method_ `public string GetIntegrationSource(string DepotPath)` — For a given file (and revision, potentially), returns where it was integrated from. Useful in conjunction with files in a P4DescribeRecord, with action = "integrate".
- L4362 _private field_ `private static object[] OldStyleBinaryFlags = new object[] { P4FileAttributes.Uncompressed, P4FileAttributes.Executable, P4FileAttributes.Compressed, P4FileAttributes.RCS }`
- L4370-4422 _private method_ `private static void ParseFileType(string Filetype, ref P4FileStat Stat)`
- L4424-4437 _private* method_ `static P4Action ParseAction(string Action)`
- L4439-4449 _private method_ `private static KeyValuePair<object, string>[] GetEnumValuesAndKeywords(Type EnumType)`
- L4451-4460 _private method_ `private static KeyValuePair<object, string>[] GetEnumValuesAndKeywords(Type EnumType, object[] Values)`
- L4462-4467 _private method_ `private static string GetEnumDescription(Type EnumType, object Value)`
- L4469-4486 _private method_ `private static string FileAttributesToString(P4FileAttributes Attributes)`
- L4488-4508 _public method_ `public bool CheckClientHasPendingChanges(string P4Client = null)`

#### class `AutomationTool.P4Connection.ChangeRecord`  
`public class ChangeRecord`  
_public; L1600-1615_
- desc: Invokes p4 changes command.
- L1602 _public field_ `public int CL = 0`
- L1603 _public field_ `public string User = ""`
- L1604 _public field_ `public string UserEmail = ""`
- L1605 _public field_ `public string Summary = ""`
- L1606-1609 _public method_ `public static int Compare(ChangeRecord A, ChangeRecord B)`
- L1611-1614 _public method_ `public override string ToString()`

#### class `AutomationTool.P4Connection.DescribeRecord`  
`public class DescribeRecord`  
_public; L1788-1818_
- L1790 _public field_ `public int CL = 0`
- L1791 _public field_ `public string User = ""`
- L1792 _public field_ `public string UserEmail = ""`
- L1793 _public field_ `public string Summary = ""`
- L1794 _public field_ `public string Header = ""`
- L1807 _public field_ `public List<DescribeFile> Files = new List<DescribeFile>()`
- L1809-1812 _public method_ `public static int Compare(DescribeRecord A, DescribeRecord B)`
- L1814-1817 _public method_ `public override string ToString()`

#### class `AutomationTool.P4Connection.DescribeRecord.DescribeFile`  
`public class DescribeFile`  
_public; L1796-1806_
- L1798 _public field_ `public string File`
- L1799 _public field_ `public int Revision`
- L1800 _public field_ `public string ChangeType`
- L1802-1805 _public method_ `public override string ToString()`

### `Source/Programs/AutomationTool/AutomationUtils/P4WriteConfig.cs` (AutomationUtils.Automation)


#### class `AutomationTool.P4WriteConfig`  
`public class P4WriteConfig : BuildCommand`  
_public; L20-213_
- attrs: `[Help("Auto-detects P4 settings based on the current path and creates a p4config file with the relevant settings.")] [ParamHelp("SetIgnore", "Adds a P4IGNORE to the default file (p4ignore in the root, or Engine/Extras/Perforce/p4ignore)", ParamType = typeof(bool), Flag = "-SetIgnore")] [ParamHelp("Path", "Write to a path other than the current directory")] [ParamHelp("ReplaceEnv", "When a filename`
- inherits: `BuildCommand`
- L22-103 _public method_ `public override ExitCode Execute()`
- L111-153 _private method_ `private (string Directory, string Filename) GenerateP4ConfigPath()` — Generate the path of the p4config file based on the users input on the commandline and the existing P4CONFIG settings in the current environment.
- L160-186 _private method_ `private (string Directory, string Filename) ParseCmdlinePath()` — Parses the cmdline arg '-Path=' and returns it split into the directory and filename components.
- L192-207 _private method_ `private string FindP4ConfigEnvValue()` — Utility to return the currently set p4config value from the users environment
- L212 _private const_ `private const string DefaultFilename = "p4config.txt"` — The standard name we should use for the p4config file if there is nothing existing set in the users environment

### `Source/Programs/AutomationTool/AutomationUtils/PackageUtils.cs` (AutomationUtils.Automation)


#### class `AutomationTool.PackageUtils`  
`public partial class PackageUtils`  
_public; L23-117_
- L25-46 _private method_ `private static void UnpakBuild(FileReference ProjectFile, string SourceDirectory, List<string> PakFiles, string TargetDirectory, string CryptoFilename, string AdditionalArgs)`
- L48-75 _private method_ `private static List<FileInfo>[] SortFilesByPatchLayers(FileInfo[] FileInfoList)`
- L77-82 _private method_ `private static void GetFileListByPatchLayers(FileInfo[] PakFiles, out List<string>[] PatchLayers)`
- L95-116 _public method_ `public static void ExtractPakFiles(DirectoryInfo SourceDirectory, string TargetDirectory, string CryptoKeysFilename, string AdditionalArgs, bool bExtractByLayers, FileReference ProjectFile=null)` — Extracts all pak files for a given project.

### `Source/Programs/AutomationTool/AutomationUtils/Platform.cs` (AutomationUtils.Automation)


#### interface `AutomationTool.ITurnkeyContext`  
`public interface ITurnkeyContext`  
_public; L19-29_
- L21 _public* method_ `string RetrieveFileSource(string Name, string InType = "Misc", string InPlatform = null, string SubType = null)`
- L22 _public* method_ `string RetrieveFileSource(object HintObject)`
- L23 _public* method_ `string GetVariable(string VariableName)`
- L24 _public* method_ `int RunExternalCommand(string Command, string Params, bool bRequiresPrivilegeElevation, bool bUnattended, bool bCreateWindow)`
- L25 _public* method_ `void Log(string Message)`
- L26 _public* method_ `void ReportError(string Message)`
- L27 _public* method_ `void PauseForUser(string Message)`
- L28 _public* method_ `int ReadInputInt(string Prompt, List<string> Options, bool bIsCancellable, int DefaultValue = -1)`

#### class `AutomationTool.DeviceInfo`  
`public class DeviceInfo`  
_public; L36-79_
- L45-48 _public ctor_ `public DeviceInfo(UnrealTargetPlatform Platform)`
- L50-64 _public ctor_ `public DeviceInfo(UnrealTargetPlatform Platform, string Name, string Id, string SoftwareVersion, string Type, bool bIsDefault, bool bCanConnect, Dictionary<string, string> PlatformValues = null, AutoSoftwareUpdateMode AutoSoftwareUpdates = AutoSoftwareUpdateMode.Unknown)`
- L66 _public field_ `public UnrealTargetPlatform Platform`
- L67 _public field_ `public string Name`
- L68 _public field_ `public string Id`
- L69 _public field_ `public string SoftwareVersion`
- L70 _public field_ `public string Type`
- L71 _public field_ `public bool bIsDefault = false`
- L74 _public field_ `public bool bCanConnect = true`
- L75 _public field_ `public AutoSoftwareUpdateMode AutoSoftwareUpdates = AutoSoftwareUpdateMode.Unknown`
- L78 _public field_ `public Dictionary<string, string> PlatformValues = ...`
- L78 _public field_ `public Dictionary< PlatformValues = new Dictionary<string, string>(StringComparer.InvariantCultureIgnoreCase)`

#### enum `AutomationTool.DeviceInfo.AutoSoftwareUpdateMode`  
`public enum AutoSoftwareUpdateMode`  
_public; L38-43_
- L40 _public* enumerator_ `Unknown`
- L41 _public* enumerator_ `Disabled`
- L42 _public* enumerator_ `Enabled`

#### struct `AutomationTool.TargetPlatformDescriptor`  
`public struct TargetPlatformDescriptor`  
_public; L84-104_
- desc: Holds information for targeting specific platform (platform type + cook flavor)
- L86 _public field_ `public UnrealTargetPlatform Type`
- L87 _public field_ `public string CookFlavor`
- L89-93 _public ctor_ `public TargetPlatformDescriptor(UnrealTargetPlatform InType)`
- L94-98 _public ctor_ `public TargetPlatformDescriptor(UnrealTargetPlatform InType, string InCookFlavor)`
- L100-103 _public method_ `public override string ToString()`

#### class `AutomationTool.Platform`  
`public class Platform : CommandUtils`  
_public; L109-1055_
- inherits: `CommandUtils`
- desc: Platform abstraction layer.
- L111 _private field_ `private static Dictionary<TargetPlatformDescriptor, Platform> AllPlatforms = ...`
- L111 _private field_ `private static Dictionary< AllPlatforms = new Dictionary<TargetPlatformDescriptor, Platform>()`
- L112-132 _internal method_ `internal static void InitializePlatforms(HashSet<Assembly> AssembliesWithPlatforms)`
- L134-186 _private method_ `private static void CreatePlatformsFromAssembly(Assembly ScriptAssembly)`
- L188 _public property_ `public UnrealTargetPlatform TargetPlatformType { get; set; }`
- L189 _public property_ `public UnrealTargetPlatform TargetIniPlatformType { get; set; }`
- L191-197 _public ctor_ `public Platform(UnrealTargetPlatform PlatformType)`
- L203-206 _public method_ `public virtual void PlatformSetupParams(ref ProjectParams ProjParams)` — Allow the platform to alter the ProjectParams
- L208-211 _public method_ `public virtual TargetPlatformDescriptor GetTargetPlatformDescriptor()`
- L218-221 _public method_ `public virtual void GetPlatformUATDependencies(DirectoryReference ProjectDirectory, List<FileReference> Dependencies)` — Allows a platform to add runtime dependencies to UAT that may not be referenced in other ways, but are needed for staging UAT
- L226-229 _public method_ `public virtual DeviceInfo[] GetDevices()`
- L231-247 _public method_ `public virtual DeviceInfo GetDeviceByName( string DeviceName )`
- L249-267 _public method_ `public virtual bool InstallSDK(BuildCommand BuildCommand, ITurnkeyContext TurnkeyContext, DeviceInfo Device, bool bUnattended, bool bSdkAlreadyInstalled)`
- L269-272 _public method_ `public virtual bool PostSDKSetup(ITurnkeyContext TurnkeyContext, bool bUnattended)`
- L279-282 _public method_ `public virtual string[] GetCodeSpecifiedSdkVersions()` — Return a list of versions that will be used to create "fake" FileSource objects which are used for install Sdks where no file downloads are needed
- L288-291 _public method_ `public virtual string[] GetCodeSpecifiedDeviceSoftwareUpdateVersions()` — Return a list of versions that will be used to create "fake" FileSource objects which are used for flash/system updates where no file downloads are needed
- L293-298 _public method_ `public virtual bool GetSDKInstallCommand(out string Command, out string Params, ref bool bRequiresPrivilegeElevation, ref bool bCreateWindow, ITurnkeyContext TurnkeyContext)`
- L300-303 _public method_ `public virtual bool GetSDKInstallCommand(out string Command, out string Params, ref bool bRequiresPrivilegeElevation, ref bool bCreateWindow, ITurnkeyContext TurnkeyContext, bool bSdkAlreadyInstalled)`
- L305-310 _public method_ `public virtual bool GetDeviceUpdateSoftwareCommand(out string Command, out string Params, ref bool bRequiresPrivilegeElevation, ref bool bCreateWindow, ITurnkeyContext TurnkeyContext, DeviceInfo Device = null)`
- L319-322 _public method_ `public virtual bool OnSDKInstallComplete(int ExitCode, ITurnkeyContext TurnkeyContext, DeviceInfo Device)` — Let's the platform handle the result of
- L324-326 _public method_ `public virtual void PersistSdkRootVar()`
- L328-331 _public method_ `public virtual string GetSDKCreationHelp()`
- L333-336 _public method_ `public virtual bool UpdateHostPrerequisites(BuildCommand Command, ITurnkeyContext TurnkeyContext, bool bVerifyOnly)`
- L338-341 _public method_ `public virtual bool UpdateDevicePrerequisites(DeviceInfo Device, BuildCommand Command, ITurnkeyContext TurnkeyContext, bool bVerifyOnly)`
- L343-347 _public method_ `public virtual bool SetDeviceAutoSoftwareUpdateMode(DeviceInfo Device, bool bEnableAutoSoftwareUpdates)`
- L357-360 _public method_ `public virtual void Package(ProjectParams Params, DeploymentContext SC, int WorkingCL)` — Package files for the current platform.
- L368-371 _public method_ `public virtual void ExtractPackage(ProjectParams Params, string SourcePath, string DestinationPath)` — Does the reverse of the output from the package process
- L378-380 _public method_ `public virtual void ProcessArchivedProject(ProjectParams Params, DeploymentContext SC)` — Allow platform to do platform specific work on archived project before it's deployed.
- L387-391 _public method_ `public virtual void GetConnectedDevices(ProjectParams Params, out List<string> Devices)` — Get all connected device names for this platform
- L398-401 _public method_ `public virtual void PreStage(ProjectParams Params, DeploymentContext SC)` — Allow platform specific work prior to touching the staging directory
- L409-412 _public method_ `public virtual void Deploy(ProjectParams Params, DeploymentContext SC)` — Deploy the application on the current platform
- L422-425 _public method_ `public virtual IProcessResult RunClient(ERunOptions ClientRunFlags, string ClientApp, string ClientCmdLine, ProjectParams Params, DeploymentContext SC)` — Run the client application on the platform
- L434-442 _public method_ `public virtual IProcessResult RunClient(ERunOptions ClientRunFlags, string ClientApp, string ClientCmdLine, ProjectParams Params)` — Run the client application on the platform
- L450-453 _public method_ `public virtual void GetTargetFile(string RemoteFilePath, string LocalFile, ProjectParams Params)` — Downloads file from target device to local pc
- L460-463 _public method_ `public virtual void PostRunClient(IProcessResult Result, ProjectParams Params)` — Allow platform specific clean-up or detection after client has run
- L470-473 _public method_ `public virtual string GetPlatformExecutableName(string InExecutableName)` — Get the platform-specific name for the executable (with out the file extension)
- L475-497 _public method_ `public virtual List<FileReference> GetExecutableNames(DeploymentContext SC)`
- L504-507 _public method_ `public virtual void GetFilesToDeployOrStage(ProjectParams Params, DeploymentContext SC)` — Get the files to deploy, specific to this platform, typically binaries
- L514-516 _public method_ `public virtual void GetFilesToStageForDLC(ProjectParams Params, DeploymentContext SC)` — Get additional platform specific files to stage when staging DLC
- L523-525 _public method_ `public virtual void PostStagingFileCopy(ProjectParams Params, DeploymentContext SC)` — Called after CopyUsingStagingManifest. Does anything platform specific that requires a final list of staged files.
- L532-535 _public method_ `public virtual void GetFilesToArchive(ProjectParams Params, DeploymentContext SC)` — Get the files to deploy, specific to this platform, typically binaries
- L543-550 _public method_ `public virtual string GetCookPlatform(bool bDedicatedServer, bool bIsClientOnly)` — Gets cook platform name for this platform.
- L557-560 _public method_ `public virtual string GetCookExtraCommandLine(ProjectParams Params)` — Gets extra cook commandline arguments for this platform.
- L566-569 _public method_ `public virtual List<string> GetCookExtraMaps()` — Gets extra maps needed on this platform.
- L578-588 _public method_ `public virtual string GetReleasePakFilePath(DeploymentContext SC, ProjectParams Params, string PakName)` — Get a release pak file path, if we are currently building a patch then get the previous release pak file path, if we are creating a new release this will be the output path
- L594-597 _public method_ `public virtual string GetEditorCookPlatform()` — Gets editor cook platform name for this platform. Cooking the editor is not useful, but this is used to fill the derived data cache
- L604-607 _public method_ `public virtual bool DeployLowerCaseFilenames(StagedFileType FileType)` — return true if we need to change the case of filenames outside of pak files
- L615-618 _public method_ `public virtual bool DeployLowerCaseFile(FileReference File, StagedFileType FileType)` — return true if we need to change the case of a particular file
- L627-630 _public method_ `public virtual string LocalPathToTargetPath(string LocalPath, string LocalRoot)` — Converts local path to target platform path.
- L637-639 _public method_ `public virtual void MakeAgenda(UnrealBuild.BuildAgenda Agenda, List<string> ExtraBuildProducts)` — Update the build agenda for this platform
- L645-648 _public method_ `public virtual List<string> GetDebugFileExtensions()` — Returns a list of the compiler produced debug file extensions
- L653-656 _public property_ `public UnrealTargetPlatform PlatformType { get; }` — UnrealTargetPlatform type for this platform.
- L661-664 _public property_ `public UnrealTargetPlatform IniPlatformType { get; }` — UnrealTargetPlatform type for this platform.
- L669-672 _public property_ `public virtual bool IsSupported { get; }` — True if this platform is supported.
- L677-680 _public property_ `public virtual bool DeployViaUFE { get; }` — True if this platform requires UFE for deploying
- L685-688 _public property_ `public virtual bool LaunchViaUFE { get; }` — True if this platform requires UFE for launching
- L695-698 _public method_ `public virtual string GetLaunchExtraCommandLine(ProjectParams Params)` — Gets extra launch commandline arguments for this platform.
- L703-705 _public method_ `public virtual void ModifyFileHostAddresses(List<string> HostAddresses)` — Modify or override the list of file host addresses for this platform.
- L710-713 _public property_ `public virtual bool UseAbsLog { get; }` — True if this platform can write to the abslog path that's on the host desktop.
- L720-723 _public method_ `public virtual bool RemapFileType(StagedFileType FileType)` — return true if we need to call Remap of a specific file type
- L728-731 _public method_ `public virtual StagedFileReference Remap(StagedFileReference Dest)` — Remaps the given content directory to its final location
- L738-741 _public method_ `public virtual PakType RequiresPak(ProjectParams Params)`
- L746-749 _public method_ `public virtual string GetPlatformPakCommandLine(ProjectParams Params, DeploymentContext SC)` — Returns platform specific command line options for UnrealPak
- L754-757 _public method_ `public virtual string GetPlatformIoStoreCommandLine(ProjectParams Params, DeploymentContext SC)` — Returns platform specific command line options for the IoStore cmdlet
- L764-767 _public method_ `public virtual CustomDeploymentHandler GetCustomDeploymentHandler(ProjectParams Params, DeploymentContext SC)` — Get the custom deployment handler for this platform,
- L772-775 _public property_ `public virtual bool SupportsMultiDeviceDeploy { get; }` — True if this platform is supported.
- L782-785 _public method_ `public virtual bool GetPlatformPatchesWithDiffPak(ProjectParams Params, DeploymentContext SC)` — Returns true if the platform wants patches to generate a small .pak file containing the difference of current data against a shipped pak file.
- L790-793 _public method_ `public virtual bool RequiresPackageToDeploy(ProjectParams Params)` — Returns whether the platform requires a package to deploy to a device
- L798-801 _public property_ `public virtual bool RequiresManifestFiles { get; }` — Returns whether the platform requires the Manifest_*_.txt files to be copied to the staged directory.
- L803-812 _public method_ `public virtual HashSet<StagedFileReference> GetFilesForCRCCheck()`
- L814-825 _public method_ `public virtual void StripSymbols(FileReference SourceFile, FileReference TargetFile)`
- L827-830 _public method_ `public virtual void StripAllSymbols(FileReference SourceFile, FileReference TargetFile)`
- L832-838 _public method_ `public virtual bool PublishSymbols(DirectoryReference SymbolStoreDirectory, List<FileReference> Files, bool bIndexSources, List<FileReference> SourceFiles, string Product, string Branch, int Change, string BuildVersion = null, string VFSMapping = null)`
- L840-844 _public method_ `public virtual int GetExecutableSize(DirectoryReference BinariesDirectory, string ClientName, HashSet<FileReference> BuildProducts)`
- L846-850 _public method_ `public virtual bool UpdatePatchPackagingParameters( string ProjectRoot, string BuildToUse, string AdditionalOptions )`
- L857-860 _public property_ `public virtual string[] SymbolServerDirectoryStructure { get; }` — When overridden, returns the directory structure of the platform's symbol server. Each element is a semi-colon separated string of possible directory names. The * wildcard is allowed in any entry. {0} will be substituted for a custom filter string.
- L866-869 _public property_ `public virtual bool SymbolServerDeleteIndividualFiles { get; }` — When overridden to return true, allows the AgeStoreTask to delete individual files in a single symbol folder, rather than requiring all files in a symbol folder to be out of date before deleting the entire directory.
- L876-879 _public property_ `public virtual bool SymbolServerSourceIndexingRequiresListOfSourceFiles { get; }` — When true, callers of PublishSymbols() must provide an explicit list of source files to create the index from. Some platforms discover the source files via other means, so it is possible to turn this step of the process off, since it can be slow.
- L886-889 _public property_ `public virtual bool SymbolServerRequiresLock { get; }` — If true, indicates the platform's symbol server directory must be locked for exclusive access before any operation is performed on it. Platforms may override this to disable if their tools support concurrent access to the symbol server directory.
- L891-894 _public method_ `public virtual void PreBuildAgenda(UnrealBuild Build, UnrealBuild.BuildAgenda Agenda, ProjectParams Params)`
- L899-902 _public property_ `public virtual UnrealTargetPlatform? CrashReportPlatform { get; }` — Allows a platform to use the crash reporter from a different (built-in) platform
- L908-911 _public method_ `public virtual int RunCommand(string Command)` — General purpose command to run generic string commands inside the platform interfeace
- L916-919 _public method_ `public virtual bool ShouldStageCommandLine(ProjectParams Params, DeploymentContext SC)` — Determines whether we should stage a UECommandLine.txt for this platform
- L924-927 _public method_ `public virtual bool CanHostPlatform(UnrealTargetPlatform Platform)` — Can host compile and cook for the platform
- L933-936 _public method_ `public virtual bool CanBeCompiled()` — Allows some platforms to not be compiled, for instance when BuildCookRun -build is performed
- L938-943 _public method_ `public virtual bool RetrieveDeployedManifests(ProjectParams Params, DeploymentContext SC, string DeviceName, out List<string> UFSManifests, out List<string> NonUFSManifests)`
- L945-948 _public method_ `public virtual bool SignExecutables(DeploymentContext SC, ProjectParams Params)`
- L950-953 _public method_ `public virtual UnrealTargetPlatform[] GetStagePlatforms()`
- L955-958 _public method_ `public virtual DirectoryReference GetProjectRootForStage(DirectoryReference RuntimeRoot, StagedDirectoryReference RelativeProjectRootForStage)`
- L960-963 _public method_ `public virtual void PrepareForDebugging(string SourcePackage, string ProjectFilePath, string ClientPlatform)`
- L965-968 _public method_ `public virtual void SetSecondaryRemoteMac(string ProjectFilePath, string ClientPlatform)`
- L972-975 _protected method_ `protected virtual string GetPlatformExeExtension()`
- L977-1004 _public method_ `public static string GetExeExtension(UnrealTargetPlatform Target)`
- L1006-1009 _public property_ `public static Dictionary<TargetPlatformDescriptor, Platform> Platforms { get; }`
- L1011-1015 _public method_ `public static Platform GetPlatform(UnrealTargetPlatform PlatformType)`
- L1017-1021 _public method_ `public static Platform GetPlatform(UnrealTargetPlatform PlatformType, string CookFlavor)`
- L1023-1026 _public method_ `public static bool IsValidTargetPlatform(TargetPlatformDescriptor PlatformDesc)`
- L1028-1054 _public method_ `public static List<TargetPlatformDescriptor> GetValidTargetPlatforms(UnrealTargetPlatform PlatformType, List<string> CookFlavors)`

#### enum `AutomationTool.Platform.PakType`  
`public enum PakType`  
_public; L736-736_
- desc: Tri-state - The intent is to override command line parameters for pak if needed per platform.
- L736 _public* enumerator_ `Always` — Tri-state - The intent is to override command line parameters for pak if needed per platform.
- L736 _public* enumerator_ `Never` — Tri-state - The intent is to override command line parameters for pak if needed per platform.
- L736 _public* enumerator_ `DontCare` — Tri-state - The intent is to override command line parameters for pak if needed per platform.

### `Source/Programs/AutomationTool/AutomationUtils/ProcessUtils.cs` (AutomationUtils.Automation)


#### class `AutomationTool.StringBuilderReader`  
`public class StringBuilderReader : IDisposable`  
_public; L28-147_
- inherits: `IDisposable`
- desc: Reads from a StringBuilder line-by-line using pooled buffers to minimize allocations. This avoids the 2GB string limitation when processing large outputs. Uses GetChunks() for O(n) iteration instead of O(n²) from indexer access.
- L31 _private field_ `private StringBuilder.ChunkEnumerator ChunkEnumerator`
- L32 _private field_ `private ReadOnlyMemory<char> CurrentChunk`
- L33 _private field_ `private int ChunkPosition`
- L34 _private field_ `private bool HasMoreChunks`
- L35 _private field_ `private char[] Buffer`
- L37-51 _public ctor_ `public StringBuilderReader(StringBuilder builder)`
- L57-125 _public method_ `public bool ReadLine(out ReadOnlySpan<char> Line)` — Reads the next line as a ReadOnlySpan. The span is only valid until the next call to ReadLine. Returns false when there are no more lines to read.
- L127-137 _private method_ `private bool MoveToNextChunk()`
- L139-146 _public method_ `public void Dispose()`

#### enum `AutomationTool.CtrlTypes`  
`public enum CtrlTypes`  
_public; L149-156_
- L151 _public* enumerator_ `CTRL_C_EVENT = 0`
- L152 _public* enumerator_ `CTRL_BREAK_EVENT`
- L153 _public* enumerator_ `CTRL_CLOSE_EVENT`
- L154 _public* enumerator_ `CTRL_LOGOFF_EVENT = 5`
- L155 _public* enumerator_ `CTRL_SHUTDOWN_EVENT`

#### interface `AutomationTool.IProcess`  
`public interface IProcess`  
_public; L158-163_
- L160 _public* method_ `void StopProcess(bool KillDescendants = true)`
- L161 _public* property_ `bool HasExited { get; }`
- L162 _public* method_ `string GetProcessName()`

#### class `AutomationTool.ProcessManager`  
`public sealed class ProcessManager`  
_public; L168-364_
- desc: Tracks all active processes.
- L170 _public delegate_ `public delegate bool CtrlHandlerDelegate(CtrlTypes EventType)`
- L173 _public method_ `public static extern bool SetConsoleCtrlHandler(CtrlHandlerDelegate Handler, bool Add)` — attrs: `[DllImport("Kernel32")]`
- L178 _private field_ `private static List<IProcess> ActiveProcesses = new List<IProcess>()` — List of active (running) processes.
- L182 _private field_ `private static object SyncObject = new object()` — Synchronization object
- L189-214 _public method_ `public static IProcessResult CreateProcess(string AppName, bool bAllowSpew, bool bCaptureSpew, Dictionary<string, string> Env = null, LogEventType SpewVerbosity = LogEventType.Console, ProcessResult.SpewFilterCallbackType SpewFilterCallback = null, string WorkingDir = null)` — Creates a new process and adds it to the tracking list.
- L216-222 _public method_ `public static void AddProcess(IProcess Proc)`
- L224-230 _public method_ `public static void RemoveProcess(IProcess Proc)`
- L232-235 _public method_ `public static bool CanBeKilled(string ProcessName)`
- L240-363 _public method_ `public static void KillAll()` — Kills all running processes.

#### interface `AutomationTool.IProcessResult`  
`public interface IProcessResult : IProcess`  
_public; L366-380_
- inherits: `IProcess`
- L368 _public* method_ `void OnProcessExited()`
- L369 _public* method_ `void DisposeProcess()`
- L370 _public* method_ `void StdOut(object sender, DataReceivedEventArgs e)`
- L371 _public* method_ `void StdErr(object sender, DataReceivedEventArgs e)`
- L372 _public* property_ `int ExitCode { get; set; }`
- L373 _public* property_ `bool bExitCodeSuccess { get; }`
- L374 _public* property_ `string Output { get; }`
- L375 _public* property_ `Process ProcessObject { get; }`
- L376 _public* method_ `string ToString()`
- L377 _public* method_ `void WaitForExit()`
- L378 _public* method_ `FileReference WriteOutputToFile(string FileName)`
- L379 _public* method_ `StringBuilderReader GetOutputReader()`

#### class `AutomationTool.ProcessResult`  
`public class ProcessResult : IProcessResult`  
_public; L385-910_
- inherits: `IProcessResult`
- desc: Class containing the result of process execution.
- L387 _public delegate_ `public delegate string SpewFilterCallbackType(string Message)`
- L389 _private field_ `private int ProcessExitCode = -1`
- L390 _private field_ `private StringBuilder ProcessOutput = null`
- L391 _private field_ `private bool AllowSpew = true`
- L392 _private field_ `private LogEventType SpewVerbosity = LogEventType.Console`
- L393 _private field_ `private SpewFilterCallbackType SpewFilterCallback = null`
- L394 _private field_ `private string AppName = String.Empty`
- L395 _private field_ `private Process Proc = null`
- L396 _private field_ `private AutoResetEvent OutputWaitHandle = new AutoResetEvent(false)`
- L397 _private field_ `private AutoResetEvent ErrorWaitHandle = new AutoResetEvent(false)`
- L398 _private field_ `private bool bStdOutSignalReceived = false`
- L399 _private field_ `private bool bStdErrSignalReceived = false`
- L400 _private field_ `private object ProcSyncObject`
- L402-420 _public ctor_ `public ProcessResult(string InAppName, Process InProc, bool bAllowSpew, bool bCaptureSpew = true, LogEventType SpewVerbosity = LogEventType.Console, SpewFilterCallbackType InSpewFilterCallback = null)`
- L422-428 _private* dtor_ `~ProcessResult()`
- L433-436 _public method_ `public void OnProcessExited()` — Removes a process from the list of tracked processes.
- L444-447 _private method_ `private void LogOutput(LogEventType Verbosity, string Message)` — Log output of a remote process at a given severity. To pretty up the output, we use a custom source so it will say the source of the process instead of this method name.
- L452-459 _public method_ `public void DisposeProcess()` — Manually dispose of Proc and set it to null.
- L466-499 _public method_ `public void StdOut(object sender, DataReceivedEventArgs e)` — Process.OutputDataReceived event handler.
- L506-539 _public method_ `public void StdErr(object sender, DataReceivedEventArgs e)` — Process.ErrorDataReceived event handler.
- L544-548 _public property_ `public int ExitCode { get; set; }` — Gets or sets the process exit code.
- L550 _public property_ `public bool bExitCodeSuccess => ...`
- L555-568 _public property_ `public string Output { get; }` — Gets all std output the process generated.
- L570-588 _public property_ `public bool HasExited { get; }`
- L590-593 _public property_ `public Process ProcessObject { get; }`
- L599-621 _public method_ `public string GetProcessName()` — Thread-safe way of getting the process name
- L627-630 _public method_ `public override string ToString()` — Object iterface.
- L632-735 _public method_ `public void WaitForExit()`
- L737-745 _public method_ `public FileReference WriteOutputToFile(string FileName)`
- L747-754 _public method_ `public StringBuilderReader GetOutputReader()`
- L763-797 _private method_ `private static bool IsOurDescendant(Process ProcessToKill, int PossiblyRelatedId, HashSet<int> VisitedPids)` — Finds child processes of the current process.
- L803-839 _public method_ `public static void KillAllDescendants(Process ProcessToKill)` — Kills all child processes of the specified process.
- L845-870 _public method_ `public static bool HasAnyDescendants(Process ProcessToCheck)` — returns true if this process has any descendants
- L872-909 _public method_ `public void StopProcess(bool KillDescendants = true)`

#### class `AutomationTool.CommandUtils`  
`public partial class CommandUtils`  
_public; L912-1477_
- L914 _private field_ `private static Dictionary<string, int> ExeToTimeInMs = ...`
- L914 _private field_ `private static Dictionary< ExeToTimeInMs = new Dictionary<string, int>()`
- L916-930 _public method_ `public static void AddRunTime(string Exe, int TimeInMs)`
- L932-942 _public method_ `public static void PrintRunTime()`
- L1004-1049 _public method_ `public static string WhichApp(string App, bool Quiet=true)` — Resolves the passed in name using the path environment
- L1057-1073 _private method_ `private static bool IsEngineExecutable(string App)` — Returns true if the given application executable is located withing the engine directory (as defined by CmdEnv.LocalRoot). This check may not be perfectly accurate because it only relies on the string paths.
- L1087-1255 _public method_ `public static IProcessResult Run(string App, string CommandLine = null, string Input = null, ERunOptions Options = ERunOptions.Default, Dictionary<string, string> Env = null, ProcessResult.SpewFilterCallbackType SpewFilterCallback = null, string Identifier = null, string WorkingDir = null)` — Runs external program.
- L1264-1271 _public method_ `public static string GetRunAndLogOnlyName(CommandEnvironment Env, string App, string LogName = null)` — Gets a logfile name for a RunAndLog call
- L1285-1288 _public method_ `public static void RunAndLog(CommandEnvironment Env, string App, string CommandLine, string LogName = null, int MaxSuccessCode = 0, string Input = null, ERunOptions Options = ERunOptions.Default, Dictionary<string, string> EnvVars = null, ProcessResult.SpewFilterCallbackType SpewFilterCallback = null)` — Runs external program and writes the output to a logfile.
- L1315-1341 _public method_ `public static string RunAndLog(string App, string CommandLine, string Logfile = null, int MaxSuccessCode = 0, string Input = null, ERunOptions Options = ERunOptions.Default, Dictionary<string, string> EnvVars = null, ProcessResult.SpewFilterCallbackType SpewFilterCallback = null)` — Runs external program and writes the output to a logfile.
- L1353-1366 _public method_ `public static string RunAndLog(string App, string CommandLine, out int SuccessCode, string Logfile = null, Dictionary<string, string> EnvVars = null, ProcessResult.SpewFilterCallbackType SpewFilterCallback = null)` — Runs external program and writes the output to a logfile.
- L1379-1382 _public method_ `public static string RunAndLog(CommandEnvironment Env, string App, string CommandLine, out int SuccessCode, string LogName = null, Dictionary<string, string> EnvVars = null, ProcessResult.SpewFilterCallbackType SpewFilterCallback = null)` — Runs external program and writes the output to a logfile.
- L1390-1429 _public method_ `public static void RunUAT(CommandEnvironment Env, string CommandLine, string Identifier)` — Runs UAT recursively
- L1431 _protected delegate_ `protected delegate bool ProcessLog(string LogText)`
- L1438-1475 _protected method_ `protected static void LogFileReaderProcess(string LogFilename, IProcessResult LogProcess, ProcessLog OnLogRead = null)` — Keeps reading a log file as it's being written to by another process until it exits.

#### enum `AutomationTool.CommandUtils.ERunOptions`  
`public enum ERunOptions`  
_public; L945-996_
- attrs: `[Flags]`
- L947 _public* enumerator_ `None = 0`
- L952 _public* enumerator_ `AllowSpew = 1 << 0` — If AllowSpew is set, then the redirected output from StdOut/StdErr is logged. Not relevant when NoStdOutRedirect is set.
- L953 _public* enumerator_ `AppMustExist = 1 << 1`
- L954 _public* enumerator_ `NoWaitForExit = 1 << 2`
- L959 _public* enumerator_ `NoStdOutRedirect = 1 << 3` — If NoStdOutRedirect is set, then StdOut/StdErr output is not redirected, logged or captured. Else, StdOut/StdErr is redirected and captured by default.
- L960 _public* enumerator_ `NoLoggingOfRunCommand = 1 << 4`
- L965 _public* enumerator_ `UTF8Output = 1 << 5` — Output of the spawned process is expected to be encoded as UTF-8.
- L968 _public* enumerator_ `SpewIsVerbose = 1 << 6` — When specified with AllowSpew, the output will be TraceEventType.Verbose instead of TraceEventType.Information
- L972 _public* enumerator_ `LoggingOfRunDuration = 1 << 7` — If NoLoggingOfRunCommand is set, it normally suppresses the run duration output. This turns it back on.
- L976 _public* enumerator_ `NoHideWindow = 1 << 8` — If set, a window is allowed to be created
- L982 _public* enumerator_ `NoStdOutCapture = 1 << 9` — If NoStdOutCapture is set, then the redirected output from StdOut/StdErr is not captured in the ProcessResult, and ProcessResult.Output will return null. Not relevant when NoStdOutRedirect is set.
- L987 _public* enumerator_ `UTF16Output = 1 << 10` — Output of the spawned process is expected to be encoded as UTF-16 (System.Text.UnicodeEncoding, in .NET terminology)
- L993 _public* enumerator_ `UseShellExecute = 1 << 11` — If set, then use the shell to create the process, else the process will be created directly from the executable. Will force NoStdOutRedirect since UseShellExecute is incompatible with redirection of stdout.
- L995 _public* enumerator_ `Default = AllowSpew | AppMustExist`

#### class `AutomationTool.CommandUtils.CommandFailedException`  
`public class CommandFailedException : AutomationException`  
_public; L1293-1302_
- inherits: `AutomationException`
- desc: Exception class for child process commands failing
- L1295-1297 _public ctor_ `public CommandFailedException(string Message) : base(Message)`
- L1299-1301 _public ctor_ `public CommandFailedException(ExitCode ExitCode, string Message) : base(ExitCode, Message)`

### `Source/Programs/AutomationTool/AutomationUtils/ProjectParams.cs` (AutomationUtils.Automation)


#### interface `AutomationTool.IProjectParamsHelpers`  
`public interface IProjectParamsHelpers`  
_public; L35-37_
- attrs: `[ParamHelp("platform", "Platform of the target", ParamType = typeof(string))] [ParamHelp("config", "Config of the target", ParamType = typeof(string))] [ParamHelp("project", "Config of the target", ParamType = typeof(string))] [ParamHelp("client", "Build, cook and run a client and a server, uses client target configuration", ParamType = typeof(bool))] [ParamHelp("noclient", "Do not run the client,`

#### class `AutomationTool.ProjectParams`  
`public class ProjectParams`  
_public; L41-3556_
- attrs: `[Help("targetplatform=PlatformName", "target platform for building, cooking and deployment (also -Platform)")] [Help("servertargetplatform=PlatformName", "target platform for building, cooking and deployment of the dedicated server (also -ServerPlatform)")]`
- L43 _private* property_ `static ILogger Logger => ...`
- L54-71 _private* method_ `bool GetParamValueIfNotSpecified(BuildCommand Command, bool? SpecifiedValue, bool Default, params string[] ParamNames)` — Gets a parameter from the command line if it hasn't been specified in the constructor. If the command line is not available, default value will be used.
- L83-86 _private* method_ `bool GetOptionalParamValueIfNotSpecified(BuildCommand Command, bool? SpecifiedValue, bool Default, string TrueParam, string FalseParam)` — Gets optional parameter from the command line if it hasn't been specified in the constructor. If the command line is not available or the command has not been specified in the command line, default value will be used.
- L98-121 _private* method_ `bool? GetOptionalParamValueIfNotSpecified(BuildCommand Command, bool? SpecifiedValue, bool? Default, string TrueParam, string FalseParam)` — Gets optional parameter from the command line if it hasn't been specified in the constructor. If the command line is not available or the command has not been specified in the command line, default value will be used.
- L135-182 _private* method_ `string ParseParamValueIfNotSpecified(BuildCommand Command, string SpecifiedValue, string ParamName, string Default = "", bool bTrimQuotes = false, string ObsoleteParamName = null, string ObsoleteSpecifiedValue = null)` — Gets a parameter value from the command line if it hasn't been specified in the constructor. If the command line is not available, default value will be used.
- L194-291 _private method_ `private List<TargetPlatformDescriptor> SetupTargetPlatforms(ref Dictionary<TargetPlatformDescriptor, TargetPlatformDescriptor> DependentPlatformMap, BuildCommand Command, List<TargetPlatformDescriptor> OverrideTargetPlatforms, List<TargetPlatformDescriptor> DefaultTargetPlatforms, bool AllowPlatformParams, params string[] PlatformParamNames)` — Sets up platforms
- L293-472 _public ctor_ `public ProjectParams(ProjectParams InParams)`
- L479-1414 _public ctor_ `public ProjectParams( FileReference RawProjectPath, FileReference RawProgramProjectOverride = null, BuildCommand Command = null, string Device = null, string MapToRun = null, string AdditionalServerMapParams = null, ParamList<string> Port = null, string RunCommandline = null, string StageCommandline = null, string BundleName = null, string StageDirectoryParam = null, string UnrealExe = null, string UE4Exe = null, string SignPak = null, List<UnrealTargetConfiguration> ClientConfigsToBuild = null, List<UnrealTargetConfiguration> ServerConfigsToBuild = null, ParamList<string> MapsToCook = null, ParamList<string> MapIniSectionsToCook = null, ParamList<string> DirectoriesToCook = null, string DDCGraph = null, string InternationalizationPreset = null, ParamList<string> CulturesToCook = null, ParamList<string> ClientCookedTargets = null, ParamList<string> EditorTargets = null, ParamList<string> ServerCookedTargets = null, List<TargetPlatformDescriptor> ClientTargetPlatforms = null, Dictionary<TargetPlatformDescriptor, TargetPlatformDescriptor> ClientDependentPlatformMap = null, List<TargetPlatformDescriptor> ServerTargetPlatforms = null, Dictionary<TargetPlatformDescriptor, TargetPlatformDescriptor> ServerDependentPlatformMap = null, List<string> ConfigOverrideParams = null, bool? Build = null, bool? SkipBuildClient = null, bool? SkipBuildEditor = null, bool? Cook = null, bool? Run = null, bool? SkipServer = null, bool? Clean = null, bool? Compressed = null, bool? ForceUncompressed = null, bool? UseMergedModules = null, string AdditionalPakOptions = null, string AdditionalIoStoreOptions = null, string ForceOodleDllVersion = null, bool? IncrementalCook = null, string IterateSharedCookedBuild = null, bool? IterateSharedBuildUsePrecompiledExe = null, bool? CookAll = null, bool? CookPartialGC = null, bool? CookInEditor = null, string CookOutputDir = null, bool? CookMapsOnly = null, bool? CookOnTheFly = null, bool? CookOnTheFlyStreaming = null, bool? UnversionedCookedContent = null, bool? OptionalContent = null, bool? EncryptIniFiles = null, bool? EncryptPakIndex = null, bool? EncryptEverything = null, bool? SkipCookingEditorContent = null, bool? SkipCookingErrorSummary = null, string AdditionalCookerOptions = null, string OriginalReleaseVersion = null, string BasedOnReleaseVersion = null, string CreateReleaseVersion = null, string CreateReleaseVersionBasePath = null, string BasedOnReleaseVersionBasePath = null, string ReferenceContainerGlobalFileName = null, string ReferenceContainerAdditionalPath = null, string ReferenceContainerChangesCSVFileName = null, string ReferenceContainerCryptoKeys = null, bool? GeneratePatch = null, bool? AddPatchLevel = null, string DiscVersion = null, string DLCName = null, string DLCOverrideCookedSubDir = null, string DLCOverrideStagedSubDir = null, FileReference DLCOverrideCryptoSettings = null, string DLCOverrideEncryptionKeyGuid = null, string DiffCookedContentPath = null, bool? DLCIncludeEngineContent = null, bool? DLCPakPluginFile = null, bool? DLCActLikePatch = null, bool? DLCSkipNamedPak = null, bool? StageOnlyCookedLocalizationForGameFeatures = null, bool? CrashReporter = null, bool? DedicatedServer = null, bool? Client = null, bool? Deploy = null, string DeployFolder = null, string GetFile = null, bool? FileServer = null, bool? Foreign = null, bool? ForeignCode = null, bool? LogWindow = null, bool? NoCleanStage = null, bool? NoClient = null, bool? NoDebugInfo = null, bool? SeparateDebugInfo = null, bool? MapFile = null, bool? NoXGE = null, bool? SkipPackage = null, bool? NeverPackage = null, bool? Package = null, bool? Pak = null, bool? IgnorePaksFromDifferentCookSource = null, bool? IoStore = null, bool? ZenStore = null, string NoZenAutoLaunch = null, string ZenWorkspaceSharePath = null, bool? ZenOmitPakFiles = null, bool? SkipIoStore = null, bool? GenerateOptimizationData = null, bool? Prereqs = null, string AppLocalDirectory = null, string CustomDeploymentHandler = null, bool? NoBootstrapExe = null, bool? SignedPak = null, bool? PakAlignForMemoryMapping = null, bool? RehydrateAssets = null, bool? NullRHI = null, bool? FakeClient = null, bool? EditorTest = null, bool? RunAutomationTests = null, string RunAutomationTest = null, int? CrashIndex = null, bool? SkipCook = null, bool? SkipCookOnTheFly = null, bool? SkipPak = null, bool? PrePak = null, bool? SkipStage = null, bool? RunChunkAssigner = null, bool? Stage = null, bool? PreStaged = null, bool? Manifests = null, bool? CreateChunkInstall = null, bool? SkipEncryption = null, bool? Unattended = null, int? NumClients = null, bool? Archive = null, string ArchiveDirectoryParam = null, bool? ArchiveMetaData = null, bool? CreateAppBundle = null, string SpecifiedClientTarget = null, string SpecifiedServerTarget = null, ParamList<string> ProgramTargets = null, bool? Distribution = null, string PackageEncryptionKeyFile = null, bool? Prebuilt = null, int? RunTimeoutSeconds = null, string SpecifiedArchitecture = null, string ServerArchitecture = null, string EditorArchitecture = null, string ClientArchitecture = null, string ProgramArchitecture = null, string UbtArgs = null, string AdditionalPackageOptions = null, bool? IterativeDeploy = null, bool? FastCook = null, bool? Snapshot = null, bool? IgnoreCookErrors = null, bool? KeepFileOpenLog = null, bool? CodeSign = null, bool? TreatNonShippingBinariesAsDebugFiles = null, bool? UseExtraFlavor = null, string Provision = null, string Certificate = null, string Team = null, bool AutomaticSigning = false, string Trace = null, string TraceHost = null, string TraceFile = null, string SessionLabel = null, ParamList<string> InMapsToRebuildLightMaps = null, ParamList<string> InMapsToRebuildHLOD = null, ParamList<string> TitleID = null, string Upload = null, IoStoreOnDemandSettings OnDemandSettings = null, bool? GenerateOptionalPakForNonChunkedBuild = null, string XcodeBuildOptions = null, bool bMakeMacNative = false )` — Constructor. Be sure to use this.ParamName to set the actual property name as parameter names and property names overlap here. If a parameter value is not set, it will be parsed from the command line; if the command is null, the default value will be used.
- L1416-1424 _private* method_ `static UnrealTargetConfiguration ParseConfig(string ConfigName)`
- L1426-1430 _private* method_ `static bool IsEpicBuildMachine()`
- L1435 _public property_ `public FileReference RawProjectPath { set; get; }` — Shared: Full path to the .uproject file
- L1441 _public property_ `public bool Foreign { set; get; }` — attrs: `[Help("foreign", "Generate a foreign uproject from blankproject and use that")]` — Shared: The current project is a foreign project, commandline: -foreign
- L1447 _public property_ `public bool ForeignCode { set; get; }` — attrs: `[Help("foreigncode", "Generate a foreign code uproject from platformergame and use that")]` — Shared: The current project is a foreign project, commandline: -foreign
- L1453 _public property_ `public bool CrashReporter { set; get; }` — attrs: `[Help("CrashReporter", "true if we should build crash reporter")]` — Shared: true if we should build crash reporter
- L1459 _public property_ `public bool Cook { set; get; }` — attrs: `[Help("cook, -cookonthefly", "Determines if the build is going to use cooked data")]` — Shared: Determines if the build is going to use cooked data, commandline: -cook, -cookonthefly
- L1465 _public property_ `public bool SkipCook { set; get; }` — attrs: `[Help("skipcook", "use a cooked build, but we assume the cooked data is up to date and where it belongs, implies -cook")]` — Shared: Determines if the build is going to use cooked data, commandline: -cook, -cookonthefly
- L1471 _public property_ `public bool SkipCookOnTheFly { set; get; }` — attrs: `[Help("skipcookonthefly", "in a cookonthefly build, used solely to pass information to the package step")]` — Shared: In a cookonthefly build, used solely to pass information to the package step. This is necessary because you can't set cookonthefly and cook at the same time, and skipcook sets cook.
- L1477 _public property_ `public bool? Clean { set; get; }` — attrs: `[Help("clean", "wipe intermediate folders before building")]` — Shared: Determines if the intermediate folders will be wiped before building, commandline: -clean
- L1483 _public property_ `public bool Unattended { set; get; }` — attrs: `[Help("unattended", "assumes no operator is present, always terminates without waiting for something.")]` — Shared: Assumes no user is sitting at the console, so for example kills clients automatically, commandline: -Unattended
- L1488 _public field_ `public List<TargetPlatformDescriptor> ClientTargetPlatforms = new List<TargetPlatformDescriptor>()` — Shared: Sets platforms to build for non-dedicated servers. commandline: -TargetPlatform
- L1493 _public field_ `public Dictionary<TargetPlatformDescriptor, TargetPlatformDescriptor> ClientDependentPlatformMap = ...` — Shared: Dictionary that maps client dependent platforms to "source" platforms that it should copy data from. commandline: -TargetPlatform=source.dependent
- L1493 _public field_ `public Dictionary< ClientDependentPlatformMap = new Dictionary<TargetPlatformDescriptor, TargetPlatformDescriptor>()` — Shared: Dictionary that maps client dependent platforms to "source" platforms that it should copy data from. commandline: -TargetPlatform=source.dependent
- L1498 _public field_ `public List<TargetPlatformDescriptor> ServerTargetPlatforms = new List<TargetPlatformDescriptor>()` — Shared: Sets platforms to build for dedicated servers. commandline: -ServerTargetPlatform
- L1503 _public field_ `public Dictionary<TargetPlatformDescriptor, TargetPlatformDescriptor> ServerDependentPlatformMap = ...` — Shared: Dictionary that maps server dependent platforms to "source" platforms that it should copy data from: -ServerTargetPlatform=source.dependent
- L1503 _public field_ `public Dictionary< ServerDependentPlatformMap = new Dictionary<TargetPlatformDescriptor, TargetPlatformDescriptor>()` — Shared: Dictionary that maps server dependent platforms to "source" platforms that it should copy data from: -ServerTargetPlatform=source.dependent
- L1509 _public property_ `public bool Pak { set; get; }` — attrs: `[Help("pak", "generate a pak file")]` — Shared: True if pak file should be generated.
- L1515 _public property_ `public bool IgnorePaksFromDifferentCookSource { get; set; }` — attrs: `[Help("pak", "disable reuse of pak files from the alternate cook source folder, if specified")]` — Stage: True if we should disable trying to re-use pak files from another staged build when we've specified a different cook source platform
- L1521 _public property_ `public bool IoStore { set; get; }` — attrs: `[Help("iostore", "generate I/O store container file(s)")]` — Shared: True if container file(s) should be generated with ZenPak.
- L1527 _public property_ `public bool ZenStore { set; get; }` — attrs: `[Help("zenstore", "save cooked output data to the Zen storage server")]` — Shared: True if the cooker should store the cooked output to the Zen storage server
- L1533 _public property_ `public string NoZenAutoLaunch { set; get; }` — attrs: `[Help("nozenautolaunch", "URL to a running Zen server")]` — Shared: URL to a running Zen server
- L1538 _public property_ `public string ZenWorkspaceSharePath { set; get; }` — Shared: Global path to a Zen workspace share to be passed to the client. Used for Zen pak streaming
- L1543 _public property_ `public bool ZenOmitPakFiles { set; get; }` — Should omit pak files when deploying build to target for Zen pak streaming
- L1549 _public property_ `public bool GenerateOptimizationData { set; get; }` — attrs: `[Help("makebinaryconfig", "generate optimized config data during staging to improve loadtimes")]` — Shared: True if optimization data is generated during staging that can improve loadtimes
- L1554-1557 _public method_ `public bool UsePak(Platform PlatformToCheck)`
- L1559 _private property_ `private string SignPakInternal { get; set; }`
- L1565-1582 _public property_ `public string SignPak { set; get; }` — attrs: `[Help("signpak=keys", "sign the generated pak file with the specified key, i.e. -signpak=C:\\Encryption.keys. Also implies -signedpak.")]` — Shared: Encryption keys used for signing the pak file.
- L1588 _public property_ `public bool PrePak { set; get; }` — attrs: `[Help("prepak", "attempt to avoid cooking and instead pull pak files from the network, implies pak and skipcook")]` — Shared: true if this build is staged, command line: -stage
- L1594 _public property_ `public bool SignedPak { set; get; }` — attrs: `[Help("signed", "the game should expect to use a signed pak file.")]` — Shared: the game will use only signed content.
- L1600 _public property_ `public bool PakAlignForMemoryMapping { set; get; }` — attrs: `[Help("PakAlignForMemoryMapping", "The game will be set up for memory mapping bulk data.")]` — Shared: The game will be set up for memory mapping bulk data.
- L1606 _public property_ `public bool RehydrateAssets { get; set; }` — attrs: `[Help("rehydrateassets", "Should virtualized assets be rehydrated?")]` — Shared: true if we want to rehydrate virtualized assets when staging.
- L1612 _public property_ `public bool SkipPak { set; get; }` — attrs: `[Help("skippak", "use a pak file, but assume it is already built, implies pak")]` — Shared: true if this build is staged, command line: -stage
- L1618 _public property_ `public bool SkipIoStore { set; get; }` — attrs: `[Help("skipiostore", "override the -iostore commandline option to not run it")]` — Shared: true if we want to skip iostore, even if -iostore is specified
- L1624 _public property_ `public bool Stage { set; get; }` — attrs: `[Help("stage", "put this build in a stage directory")]` — Shared: true if this build is staged, command line: -stage
- L1630 _public property_ `public bool SkipStage { set; get; }` — attrs: `[Help("skipstage", "uses a stage directory, but assumes everything is already there, implies -stage")]` — Shared: true if this build is staged, command line: -stage
- L1636 _public property_ `public bool RunChunkAssigner { set; get; }` — attrs: `[Help("RunChunkAssigner", "Run OplogChunkAssigner before staging to generate pak chunk manifests from the Zen oplog")]` — Staging: run OplogChunkAssigner before staging to generate pak chunk manifests from the Zen oplog.
- L1642 _public property_ `public bool PreStaged { set; get; }` — attrs: `[Help("prestaged", "the staged directory contains a build that wasn't necessarily created locally, implies -skipbuild -skipcook -skipstage (experimental)")]` — Shared: true if the staged build contains a build that may not have been created locally, command line: -prestaged (experimental)
- L1648 _public property_ `public bool Manifests { set; get; }` — attrs: `[Help("manifests", "generate streaming install manifests when cooking data")]` — Shared: true if this build is using streaming install manifests, command line: -manifests
- L1654 _public property_ `public bool CreateChunkInstall { set; get; }` — attrs: `[Help("createchunkinstall", "generate streaming install data from manifest when cooking data, requires -stage & -manifests")]` — Shared: true if this build chunk install streaming install data, command line: -createchunkinstalldata
- L1657 _public property_ `public bool SkipEncryption { set; get; }` — attrs: `[Help("skipencryption", "skips encrypting pak files even if crypto keys are provided")]`
- L1662 _public property_ `public string ChunkInstallDirectory { set; get; }` — Shared: Directory to use for built chunk install data, command line: -chunkinstalldirectory=
- L1667 _public property_ `public string ChunkInstallVersionString { set; get; }` — Shared: Version string to use for built chunk install data, command line: -chunkinstallversion=
- L1672 _public property_ `public string ChunkInstallReleaseString { set; get; }` — Shared: Release string to use for built chunk install data, command line: -chunkinstallrelease=
- L1677-1692 _public property_ `public string BaseStageDirectory { get; }` — Shared: Directory to copy the client to, command line: -stagingdirectory=
- L1695 _public field_ `public string StageDirectoryParam` — attrs: `[Help("stagingdirectory=Path", "Directory to copy the builds to, i.e. -stagingdirectory=C:\\Stage")]`
- L1698 _public field_ `public string OptionalFileStagingDirectory` — attrs: `[Help("optionalfilestagingdirectory=Path", "Directory to copy the optional files to, i.e. -optionalfilestagingdirectory=C:\\StageOptional")]`
- L1701 _public field_ `public string OptionalFileInputDirectory` — attrs: `[Help("optionalfileinputdirectory=Path", "Directory to read the optional files from, i.e. -optionalfileinputdirectory=C:\\StageOptional")]`
- L1704 _public field_ `public string CookerSupportFilesSubdirectory` — attrs: `[Help("CookerSupportFilesSubdirectory=subdir", "Subdirectory under staging to copy CookerSupportFiles (as set in Build.cs files). -CookerSupportFilesSubdirectory=SDK")]`
- L1707 _private field_ `private string SpecifiedUnrealExe = null` — attrs: `[Help("unrealexe=ExecutableName", "Name of the Unreal Editor executable, i.e. -unrealexe=UnrealEditor.exe")]`
- L1709-1725 _public property_ `public string UnrealExe { get; set; }`
- L1731 _public property_ `public bool Archive { set; get; }` — attrs: `[Help("archive", "put this build in an archive directory")]` — Shared: true if this build is archived, command line: -archive
- L1736-1742 _public property_ `public string BaseArchiveDirectory { get; }` — Shared: Directory to archive the client to, command line: -archivedirectory=
- L1745 _public field_ `public string ArchiveDirectoryParam` — attrs: `[Help("archivedirectory=Path", "Directory to archive the builds to, i.e. -archivedirectory=C:\\Archive")]`
- L1751 _public field_ `public bool ArchiveMetaData` — attrs: `[Help("archivemetadata", "Archive extra metadata files in addition to the build (e.g. build.properties)")]` — Whether the project should use non monolithic staging
- L1757 _public field_ `public bool CreateAppBundle` — attrs: `[Help("createappbundle", "When archiving for Mac, set this to true to package it in a .app bundle instead of normal loose files")]` — When archiving for Mac, set this to true to package it in a .app bundle instead of normal loose files
- L1762 _public field_ `public List<string> ConfigOverrideParams = new List<string>()` — Keeps track of any '-ini:type:[section]:value' arguments on the command line. These will override cached config settings for the current process, and can be passed along to other tools.
- L1768 _public property_ `public bool Build { set; get; }` — attrs: `[Help("build", "True if build step should be executed")]` — Build: True if build step should be executed, command: -build
- L1773 _public property_ `public bool SkipBuildClient { set; get; }` — SkipBuildClient if true then don't build the client exe
- L1778 _public property_ `public bool SkipBuildEditor { set; get; }` — SkipBuildEditor if true then don't build the editor exe
- L1784 _public property_ `public bool NoXGE { set; get; }` — attrs: `[Help("noxge", "True if XGE should NOT be used for building")]` — Build: True if XGE should NOT be used for building.
- L1789 _private field_ `private ParamList<string> EditorTargetsList = null` — Build: List of editor build targets.
- L1790-1802 _public property_ `public ParamList<string> EditorTargets { set; get; }`
- L1807 _private field_ `private ParamList<string> ProgramTargetsList = null` — Build: List of program build targets.
- L1808-1820 _public property_ `public ParamList<string> ProgramTargets { set; get; }`
- L1825 _public field_ `public List<UnrealTargetConfiguration> ClientConfigsToBuild = new List<UnrealTargetConfiguration>() { UnrealTargetConfiguration.Development }` — Build: List of client configurations
- L1830 _public field_ `public List<UnrealTargetConfiguration> ServerConfigsToBuild = new List<UnrealTargetConfiguration>() { UnrealTargetConfiguration.Development }` — Build: List of Server configurations
- L1835 _private field_ `private ParamList<string> ClientCookedTargetsList = null` — Build: List of client cooked build targets.
- L1836-1848 _public property_ `public ParamList<string> ClientCookedTargets { set; get; }`
- L1853 _private field_ `private ParamList<string> ServerCookedTargetsList = null` — Build: List of Server cooked build targets.
- L1854-1866 _public property_ `public ParamList<string> ServerCookedTargets { set; get; }`
- L1871 _private field_ `private List<string> TargetNames` — Build: Specifies the names of targets to build
- L1876 _public field_ `public ParamList<string> MapsToCook = new ParamList<string>()` — Cook: List of maps to cook.
- L1882 _public field_ `public ParamList<string> MapIniSectionsToCook = new ParamList<string>()` — Cook: List of map inisections to cook (see allmaps)
- L1888 _public field_ `public ParamList<string> DirectoriesToCook = new ParamList<string>()` — Cook: List of directories to cook.
- L1893 _public field_ `public string DDCGraph` — Cook: Which ddc graph to use when cooking.
- L1898 _public field_ `public string InternationalizationPreset` — Cook: Internationalization preset to cook.
- L1904 _public field_ `public bool StageTagMappingConfigFiles` — attrs: `[Help("StageTagMappingConfigFiles", "Include all tag mapping ini files when staging")]` — Include all tag mapping ini files when staging
- L1910 _public property_ `public bool CookPartialGC { set; get; }` — attrs: `[Help("CookPartialgc", "while cooking clean up packages as we are done with them rather then cleaning everything up when we run out of space")]` — Cook: While cooking clean up packages as we go along rather then cleaning everything (and potentially having to reload some of it) when we run out of space
- L1916 _public property_ `public bool CookInEditor { set; get; }` — attrs: `[Help("CookInEditor", "Did we cook in the editor instead of in UAT")]` — Stage: Did we cook in the editor instead of from UAT (cook in editor uses a different staging directory)
- L1921 _public field_ `public string CookOutputDir` — Cook: Output directory for cooked data
- L1926 _public field_ `public string CreateReleaseVersion` — Cook: Create a cooked release version. Also, the version. e.g. 1.0
- L1931 _public field_ `public string BasedOnReleaseVersion` — Cook: Base this cook of a already released version of the cooked data
- L1936 _public field_ `public string OriginalReleaseVersion` — The version of the originally released build. This is required by some platforms when generating patches.
- L1941 _public field_ `public string BasedOnReleaseVersionBasePath` — Cook: Path to the root of the directory where we store released versions of the game for a given version
- L1946 _public field_ `public string CreateReleaseVersionBasePath` — Cook: Path to the root of the directory to create a new released version of the game.
- L1952 _public field_ `public string ReferenceContainerGlobalFileName` — Stage: Path to the global.utoc file for a directory of iostore containers to use as a source of compressed chunks when writing new containers. See -ReferenceContainerGlobalFileName in IoStoreUtilities.cpp.
- L1957 _public field_ `public string ReferenceContainerAdditionalPath` — Stage: A directory to look for additional IoStore containers to use during staging (e.g. optional segment containers)
- L1963 _public field_ `public string ReferenceContainerChangesCSVFileName` — Stage: If ReferenceContainerChangesCSVFileName is specified, this provides a file name to write the list of changed packages/chunks to.
- L1968 _public field_ `public string ReferenceContainerCryptoKeys` — Stage: Path to the crypto.json file to use for decrypting ReferenceContainerGlobalFileName, if needed.
- L1976 _public field_ `public bool GeneratePatch` — Are we generating a patch, generate a patch from a previously released version of the game (use CreateReleaseVersion to create a release). this requires BasedOnReleaseVersion see also CreateReleaseVersion, BasedOnReleaseVersion
- L1981 _public field_ `public string DiscVersion` — Required when building remaster package
- L1985 _public field_ `public bool AddPatchLevel`
- L1990 _public field_ `public FileReference DLCFile` — Name of dlc to cook and package (if this parameter is supplied cooks the dlc and packages it into the dlc directory)
- L1996 _public field_ `public bool DLCIncludeEngineContent` — Enable cooking of engine content when cooking dlc not included in original release but is referenced by current cook
- L2002 _public field_ `public bool DLCPakPluginFile` — Enable packaging up the uplugin file inside the dlc pak. This is sometimes desired if you want the plugin to be standalone
- L2008 _public field_ `public bool DLCActLikePatch` — DLC will remap it's files to the game directory and act like a patch. This is useful if you want to override content in the main game along side your main game. For example having different main game content in different DLCs
- L2014 _public field_ `public string DLCOverrideCookedSubDir` — Sometimes a DLC may get cooked to a subdirectory of where is expected, so this can tell the staging what the subdirectory of the cooked out to find the DLC files (for instance Metadata)
- L2019 _public field_ `public string DLCOverrideStagedSubDir` — Controls where under the staged directory to output to (in case the plugin subdirectory is not desired under the StagingDirectory location)
- L2024 _public field_ `public EncryptionAndSigning.CryptoSettings DLCOverrideCryptoSettings` — Specifies keys to use rather than those generated from ini files when using a staging manifest (ignored when using chunk manifests)
- L2029 _public field_ `public string DLCOverrideEncryptionKeyGuid` — Specifies an encryption key for UnrealPak to use when using a staging manifest (not a chunk manifest)
- L2034 _public field_ `public bool DLCSkipNamedPak = false` — When true the DLC Name will not be added to the generated pak files.
- L2040 _public field_ `public bool StageOnlyCookedLocalizationForGameFeatures = false` — When true only the GameFeaturePlugins that are cooked will have thier GameFeaturePlugin data staged. This check is performed by looking for a cooked GameFeatureData asset within the GameFeaturePlugin expected folder.
- L2046 _public field_ `public string DiffCookedContentPath` — After cook completes diff the cooked content against another cooked content directory. report all errors to the log
- L2051 _public field_ `public string AdditionalBuildOptions` — Build: Additional build options to include on the build commandline
- L2056 _public field_ `public string AdditionalCookerOptions` — Cook: Additional cooker options to include on the cooker commandline
- L2061 _public field_ `public ParamList<string> CulturesToCook` — Cook: List of cultures to cook.
- L2066 _public field_ `public bool Compressed` — Compress packages during cook.
- L2071 _public field_ `public bool ForceUncompressed` — Do not compress packages during cook, override game ProjectPackagingSettings to force it off
- L2076 _public field_ `public bool UseMergedModules` — Assume that executables will be built with merged modules
- L2081 _public field_ `public bool ForceCompressed` — Compress packages during cook, override game ProjectPackagingSettings and Platform Hardware Compression settings to force it on
- L2086 _public field_ `public string AdditionalPakOptions` — Additional parameters when generating the PAK file
- L2091 _public field_ `public string AdditionalIoStoreOptions` — Additional parameters when generating iostore container files
- L2096 _public field_ `public string ForceOodleDllVersion` — If not empty, this is the dll file to use for Oodle compression. Can be "Latest" to use latest version.
- L2101 _public field_ `public bool UnversionedCookedContent = true` — Cook: Do not include a version number in the cooked content
- L2106 _public field_ `public bool OptionalContent = false` — Cook: Cook with optional data enabled
- L2112 _public field_ `public bool IncrementalCook` — attrs: `[Help("cookincremental", "Cooks incrementally using previously-cooked data or a published snapshot as a base")]` — Cook: Cooks incrementally using previously-cooked data or a published snapshot as a base
- L2118 _public field_ `public string IterateSharedCookedBuild` — attrs: `[Help("Iteratively cook from a shared cooked build")]` — Cook: Iterate from a build on the network
- L2124 _public field_ `public bool IterateSharedBuildUsePrecompiledExe` — attrs: `[Help("Iteratively cook from a shared cooked build")]` — Build: Don't build the game instead use the prebuild exe (requires iterate shared cooked build
- L2130 _public field_ `public bool CookMapsOnly` — attrs: `[Help("CookMapsOnly", "Cook only maps this only affects usage of -cookall the flag")]` — Cook: Only cook maps (and referenced content) instead of cooking everything only affects -cookall flag
- L2136 _public field_ `public bool CookAll` — attrs: `[Help("CookAll", "Cook all the things in the content directory for this project")]` — Cook: Only cook maps (and referenced content) instead of cooking everything only affects cookall flag
- L2143 _public field_ `public bool SkipCookingEditorContent` — attrs: `[Help("SkipCookingEditorContent", "Skips content under /Engine/Editor when cooking")]` — Cook: Skip cooking editor content
- L2146 _public field_ `public bool SkipCookingErrorSummary` — attrs: `[Help("SkipCookingErrorSummary", "Skips error summary when cooking")]`
- L2152 _public field_ `public bool IterativeDeploy` — attrs: `[Help("IterativeDeploy", "Runs UnrealPak and targetplatform install iteratively, command line: -iterativedeploy or -iterate")]` — Cook: Uses the iterative deploy, command line: -iterativedeploy or -iterate
- L2155 _public field_ `public bool FastCook` — attrs: `[Help("FastCook", "Uses fast cook path if supported by target")]`
- L2161 _public field_ `public bool Snapshot` — attrs: `[Help("snapshot", "Imports the most recently published project snapshot (if cooking, this forces the use of -cookincremental)")]` — Imports the most recently published project snapshot (if cooking, this forces the use of -cookincremental)
- L2167 _public property_ `public bool IgnoreCookErrors { set; get; }` — attrs: `[Help("IgnoreCookErrors", "Ignores cook errors and continues with packaging etc")]` — Cook: Ignores cook errors and continues with packaging etc.
- L2173 _public property_ `public bool KeepFileOpenLog { set; get; }` — attrs: `[Help("KeepFileOpenLog", "Keeps a log of all files opened, commandline: -fileopenlog")]` — Cook: Commandline: -fileopenlog
- L2179 _public property_ `public bool NoDebugInfo { set; get; }` — attrs: `[Help("nodebuginfo", "do not copy debug files to the stage")]` — Stage: Commandline: -nodebuginfo
- L2185 _public property_ `public bool SeparateDebugInfo { set; get; }` — attrs: `[Help("separatedebuginfo", "output debug info to a separate directory")]` — Stage: Commandline: -separatedebuginfo
- L2191 _public property_ `public bool MapFile { set; get; }` — attrs: `[Help("MapFile", "generates a *.map file")]` — Stage: Commandline: -mapfile
- L2197 _public property_ `public bool NoCleanStage { set; get; }` — attrs: `[Help("nocleanstage", "skip cleaning the stage directory")]` — true if the staging directory is to be cleaned: -cleanstage (also true if -clean is specified)
- L2198 _private field_ `private bool bNoCleanStage`
- L2204 _public field_ `public string StageCommandline` — attrs: `[Help("cmdline", "command line to put into the stage in UECommandLine.txt")]` — Stage: If non-empty, the contents will be put into the stage
- L2210 _public field_ `public string BundleName` — attrs: `[Help("bundlename", "string to use as the bundle name when deploying to mobile device")]` — Stage: If non-empty, the contents will be used for the bundle name
- L2215 _public field_ `public ParamList<string> ExtraTargetsToStageWithClient = new ParamList<string>()` — Stage: Specifies a list of extra targets that should be staged along with a client
- L2220 _public field_ `public Action<ProjectParams, DeploymentContext> PreModifyDeploymentContextCallback = ...` — Stage: Optional callback that a build script can use to modify a deployment context immediately after it is created
- L2220 _public field_ `public Action< PreModifyDeploymentContextCallback = null` — Stage: Optional callback that a build script can use to modify a deployment context immediately after it is created
- L2225 _public field_ `public Action<ProjectParams, DeploymentContext> ModifyDeploymentContextCallback = ...` — Stage: Optional callback that a build script can use to modify a deployment context before it is applied (and before it is finalized)
- L2225 _public field_ `public Action< ModifyDeploymentContextCallback = null` — Stage: Optional callback that a build script can use to modify a deployment context before it is applied (and before it is finalized)
- L2230 _public field_ `public Action<ProjectParams, DeploymentContext> FinalizeDeploymentContextCallback = ...` — Stage: Optional callback that a build script can use to finalize a deployment context before it is applied
- L2230 _public field_ `public Action< FinalizeDeploymentContextCallback = null` — Stage: Optional callback that a build script can use to finalize a deployment context before it is applied
- L2235 _public property_ `public string CustomDeploymentHandler { get; set; }` — Name of the custom deployment handler to change how the build packaged, staged and deployed - for example, when packaging for a specific game store
- L2241 _public property_ `public bool NoBootstrapExe { get; set; }` — On Windows, adds an executable to the root of the staging directory which checks for prerequisites being installed and launches the game with a path to the .uproject file.
- L2246 _public field_ `public bool bCodeSign = false` — By default we don't code sign unless it is required or requested
- L2251 _public field_ `public string Provision = null` — Provision to use
- L2256 _public field_ `public string Certificate = null` — Certificate to use
- L2261 _public field_ `public string Team = null` — Team ID to use
- L2266 _public field_ `public bool AutomaticSigning = false` — true if provisioning is automatically managed
- L2271 _public field_ `public ParamList<string> TitleID = new ParamList<string>()` — TitleID to package
- L2276 _public field_ `public bool bTreatNonShippingBinariesAsDebugFiles = false` — If true, non-shipping binaries will be considered DebugUFS files and will appear on the debugfiles manifest
- L2281 _public field_ `public bool bUseExtraFlavor = false` — If true, use chunk manifest files generated for extra flavor
- L2287 _public property_ `public bool Run { set; get; }` — attrs: `[Help("run", "run the game after it is built (including server, if -server)")]` — Run: True if the Run step should be executed, command: -run
- L2293 _public property_ `public bool CookOnTheFly { set; get; }` — attrs: `[Help("cookonthefly", "run the client with cooked data provided by cook on the fly server")]` — Run: The client runs with cooked data provided by cook on the fly server, command line: -cookonthefly
- L2299 _public property_ `public bool CookOnTheFlyStreaming { set; get; }` — attrs: `[Help("Cookontheflystreaming", "run the client in streaming cook on the fly mode (don't cache files locally instead force reget from server each file load)")]` — Run: The client should run in streaming mode when connecting to cook on the fly server
- L2307 _public property_ `public bool FileServer { set; get; }` — attrs: `[Help("fileserver", "run the client with cooked data provided by UnrealFileServer")]` — Run: The client runs with cooked data provided by UnrealFileServer, command line: -fileserver = CookByTheBook with ZenServer (zenstore)
- L2313 _public property_ `public bool DedicatedServer { set; get; }` — attrs: `[Help("dedicatedserver", "build, cook and run both a client and a server (also -server)")]` — Run: The client connects to dedicated server to get data, command line: -dedicatedserver
- L2319 _public property_ `public bool Client { set; get; }` — attrs: `[Help( "client", "build, cook and run a client and a server, uses client target configuration" )]` — Run: Uses a client target configuration, also implies -dedicatedserver, command line: -client
- L2325 _public property_ `public bool NoClient { set; get; }` — attrs: `[Help("noclient", "do not run the client, just run the server")]` — Run: Whether the client should start or not, command line (to disable): -noclient
- L2331 _public property_ `public bool LogWindow { set; get; }` — attrs: `[Help("logwindow", "create a log window for the client")]` — Run: Client should create its own log window, command line: -logwindow
- L2337 _public field_ `public string MapToRun` — attrs: `[Help("map", "map to run the game with")]` — Run: Map to run the game with.
- L2343 _public field_ `public string AdditionalServerMapParams` — attrs: `[Help("AdditionalServerMapParams", "Additional server map params, i.e ?param=value")]` — Run: Additional server map params.
- L2349 _public field_ `public ParamList<string> Devices` — attrs: `[Help("device", "Devices to run the game on")]` — Run: The target device to run the game on. Comes in the form platform@devicename.
- L2355 _public field_ `public ParamList<string> DeviceNames` — attrs: `[Help("device", "Device names without the platform prefix to run the game on")]` — Run: The target device to run the game on. No platform prefix.
- L2361 _public field_ `public string ServerDevice` — attrs: `[Help("serverdevice", "Device to run the server on")]` — Run: the target device to run the server on
- L2367 _public field_ `public bool SkipServer` — attrs: `[Help("skipserver", "Skip starting the server")]` — Run: The indicated server has already been started
- L2373 _public field_ `public int NumClients` — attrs: `[Help("numclients=n", "Start extra clients, n should be 2 or more")]` — Run: The indicated server has already been started
- L2376 _public field_ `public int DeviceLockedTimeout = 120` — attrs: `[Help("DeviceLockedTimeout=n", "Seconds to wait for a locked iOS device before failing deploy (default 120, 0 to disable)")]`
- L2382 _public field_ `public string RunCommandline` — attrs: `[Help("addcmdline", "Additional command line arguments for the program, which will not be staged in UECommandLine.txt in most cases")]` — Run: Additional command line arguments to pass to the program
- L2388 _public field_ `public string ServerCommandline` — attrs: `[Help("servercmdline", "Additional command line arguments for the program")]` — Run: Additional command line arguments to pass to the server
- L2394 _public field_ `public string ClientCommandline` — attrs: `[Help("clientcmdline", "Override command line arguments to pass to the client")]` — Run: Override command line arguments to pass to the client, if set it will not try to guess at IPs or settings
- L2400 _public field_ `public bool NullRHI` — attrs: `[Help("nullrhi", "add -nullrhi to the client commandlines")]` — Run:adds -nullrhi to the client commandline
- L2403 _public field_ `public string WriteBackMetadataToAssetRegistry` — attrs: `[Help("WriteBackMetadataToAssetRegistry", "Passthru to iostore staging, see IoStoreUtilities.cpp")]`
- L2409 _public field_ `public bool FakeClient` — attrs: `[Help("fakeclient", "adds ?fake to the server URL")]` — Run:adds ?fake to the server URL
- L2415 _public field_ `public bool EditorTest` — attrs: `[Help("editortest", "rather than running a client, run the editor instead")]` — Run:adds ?fake to the server URL
- L2421 _public field_ `public bool RunAutomationTests` — attrs: `[Help("RunAutomationTests", "when running -editortest or a client, run all automation tests, not compatible with -server")]` — Run:when running -editortest or a client, run all automation tests, not compatible with -server
- L2427 _public field_ `public string RunAutomationTest` — attrs: `[Help("RunAutomationTests", "when running -editortest or a client, run a specific automation tests, not compatible with -server")]` — Run:when running -editortest or a client, run all automation tests, not compatible with -server
- L2433 _public field_ `public int CrashIndex` — attrs: `[Help("Crash=index", "when running -editortest or a client, adds commands like debug crash, debug rendercrash, etc based on index")]` — Run: Adds commands like debug crash, debug rendercrash, etc based on index
- L2435 _public field_ `public ParamList<string> Port`
- L2441 _public field_ `public string DeviceUsername` — attrs: `[Help("deviceuser", "Linux username for unattended key genereation")]` — Run: Linux username for unattended key genereation
- L2447 _public field_ `public string DevicePassword` — attrs: `[Help("devicepass", "Linux password")]` — Run: Linux password for unattended key genereation
- L2452 _public field_ `public string ServerDeviceAddress` — Run: Server device IP address
- L2455 _public property_ `public bool Package { get; set; }` — attrs: `[Help("package", "package the project for the target platform")]`
- L2458 _public property_ `public bool SkipPackage { get; set; }` — attrs: `[Help("skippackage", "Skips packaging the project for the target platform")]`
- L2461 _public property_ `public bool NeverPackage { get; set; }` — attrs: `[Help("neverpackage", "Skips preparing data that would be used during packaging, in earlier stages. Different from skippackage which is used to optimize later stages like archive, which still was packaged at some point")]`
- L2464 _public property_ `public bool ForcePackageData { get; set; }` — attrs: `[Help("package", "Determine whether data is packaged. This can be an iteration optimization for platforms that require packages for deployment")]`
- L2467 _public property_ `public bool Distribution { get; set; }` — attrs: `[Help("distribution", "package for distribution the project")]`
- L2470 _public property_ `public string PackageEncryptionKeyFile { get; set; }` — attrs: `[Help("PackageEncryptionKeyFile", "Path to file containing encryption key to use in packaging")]`
- L2473 _public property_ `public bool Prereqs { get; set; }` — attrs: `[Help("prereqs", "stage prerequisites along with the project")]`
- L2476 _public property_ `public string AppLocalDirectory { get; set; }` — attrs: `[Help("applocaldir", "location of prerequisites for applocal deployment")]`
- L2479 _public property_ `public bool Prebuilt { get; set; }` — attrs: `[Help("Prebuilt", "this is a prebuilt cooked and packaged build")]`
- L2482 _public field_ `public int RunTimeoutSeconds` — attrs: `[Help("RunTimeoutSeconds", "timeout to wait after we lunch the game")]`
- L2485 _private field_ `private UnrealArchitectures SpecifiedArchitecture` — attrs: `[Help("SpecifiedArchitecture", "Architecture to use for building any executables (see EditorArchitecture, etc for specific target type control)")]`
- L2488 _public field_ `public UnrealArchitectures EditorArchitecture` — attrs: `[Help("EditorArchitecture", "Architecture to use for building editor executables")]`
- L2491 _public field_ `public UnrealArchitectures ServerArchitecture` — attrs: `[Help("ServerArchitecture", "Architecture to use for building server executables")]`
- L2494 _public field_ `public UnrealArchitectures ClientArchitecture` — attrs: `[Help("ClientArchitecture", "Architecture to use for building client/game executables")]`
- L2497 _public field_ `public UnrealArchitectures ProgramArchitecture` — attrs: `[Help("ProgramArchitecture", "Architecture to use for building program executables")]`
- L2500 _public field_ `public string UbtArgs` — attrs: `[Help("UbtArgs", "extra options to pass to ubt")]`
- L2503 _public property_ `public string AdditionalPackageOptions { get; set; }` — attrs: `[Help("AdditionalPackageOptions", "extra options to pass to the platform's packager")]`
- L2506 _public property_ `public bool Deploy { get; set; }` — attrs: `[Help("deploy", "deploy the project for the target platform")]`
- L2509 _public property_ `public string DeployFolder { get; set; }` — attrs: `[Help("deploy", "Location to deploy to on the target platform")]`
- L2512 _public property_ `public string GetFile { get; set; }` — attrs: `[Help("getfile", "download file from target after successful run")]`
- L2515 _public field_ `public ParamList<string> MapsToRebuildLightMaps = new ParamList<string>()` — attrs: `[Help("MapsToRebuildLightMaps", "List of maps that need light maps rebuilding")]`
- L2518 _public field_ `public ParamList<string> MapsToRebuildHLODMaps = new ParamList<string>()` — attrs: `[Help("MapsToRebuildHLODMaps", "List of maps that need HLOD rebuilding")]`
- L2521 _public property_ `public bool IgnoreLightMapErrors { get; set; }` — attrs: `[Help("IgnoreLightMapErrors", "Whether Light Map errors should be treated as critical")]`
- L2524 _public property_ `public string Trace { get; set; }` — attrs: `[Help("trace", "The list of trace channels to enable")]`
- L2527 _public property_ `public string TraceHost { get; set; }` — attrs: `[Help("tracehost", "The host address of the trace recorder")]`
- L2530 _public property_ `public string TraceFile { get; set; }` — attrs: `[Help("tracefile", "The file where the trace will be recorded")]`
- L2533 _public property_ `public string SessionLabel { get; set; }` — attrs: `[Help("sessionlabel", "A label to pass to analytics")]`
- L2536 _public property_ `public string Upload { get; set; }` — attrs: `[Help("upload", "Arguments for uploading on demand content")]`
- L2539 _public property_ `public bool ApplyIoStoreOnDemand { get; }` — attrs: `[Help("applyiostoreondemand", "Forces IoStoreOnDemand to be enabled for the project even if it is not set up for it")]`
- L2542 _public property_ `public IoStoreOnDemandSettings OnDemandSettings { get; }` — attrs: `[Help("ondemandsettings", "The settings for OnDemand data to apply to the project")]`
- L2545 _public property_ `public bool GenerateOptionalPakForNonChunkedBuild { get; }` — attrs: `[Help("GenerateOptionalPakForNonChunkedBuild", "When true non chunked builds will attempt to generate an optional pak for optional bulk data.")]`
- L2548 _public property_ `public string XcodeBuildOptions { get; set; }` — attrs: `[Help("XcodeBuildOptions", "Extra options to pass to xcodebuild")]`
- L2551 _public property_ `public bool bMakeMacNative { get; set; }` — attrs: `[Help("macnative", "Generate a \"Designed for iPad\" .app that can be run natively on a silicon Mac")]`
- L2553 _private field_ `private List<SingleTargetProperties> DetectedTargets`
- L2554 _private field_ `private Dictionary<UnrealTargetPlatform, ConfigHierarchy> LoadedEngineConfigs`
- L2554 _private field_ `private Dictionary< LoadedEngineConfigs`
- L2555 _private field_ `private Dictionary<UnrealTargetPlatform, ConfigHierarchy> LoadedGameConfigs`
- L2555 _private field_ `private Dictionary< LoadedGameConfigs`
- L2556 _private field_ `private ProjectDescriptor ProjectDescriptor`
- L2558-2561 _private method_ `private List<String> TargetNamesOfType(TargetType DesiredType)`
- L2563-2574 _private method_ `private String ChooseTarget(List<String> Targets, TargetType Type)`
- L2576-2603 _private method_ `private void SelectDefaultTarget(List<string> AvailableTargets, TargetType Type, ref string Target)`
- L2605-2858 _private method_ `private void AutodetectSettings(bool bReset)`
- L2860-2863 _public property_ `public bool HasEditorTargets { get; }`
- L2865-2868 _public property_ `public bool HasCookedTargets { get; }`
- L2870-2873 _public property_ `public bool HasServerCookedTargets { get; }`
- L2875-2878 _public property_ `public bool HasClientCookedTargets { get; }`
- L2880-2883 _public property_ `public bool HasProgramTargets { get; }`
- L2885-2888 _public property_ `public bool HasMapsToCook { get; }`
- L2890-2893 _public property_ `public bool HasMapIniSectionsToCook { get; }`
- L2895-2898 _public property_ `public bool HasDirectoriesToCook { get; }`
- L2900-2903 _public property_ `public bool HasIterateSharedCookedBuild { get; }`
- L2905-2908 _public property_ `public bool HasDDCGraph { get; }`
- L2910-2913 _public property_ `public bool HasInternationalizationPreset { get; }`
- L2915-2918 _public property_ `public bool HasCreateReleaseVersion { get; }`
- L2920-2923 _public property_ `public bool HasBasedOnReleaseVersion { get; }`
- L2925-2928 _public property_ `public bool HasOriginalReleaseVersion { get; }`
- L2930-2933 _public property_ `public bool HasAdditionalCookerOptions { get; }`
- L2935-2938 _public property_ `public bool HasDLCName { get; }`
- L2940-2943 _public property_ `public bool HasDiffCookedContentPath { get; }`
- L2945-2948 _public property_ `public bool HasCulturesToCook { get; }`
- L2950-2953 _public property_ `public bool HasGameTargetDetected { get; }`
- L2955-2958 _public property_ `public bool HasClientTargetDetected { get; }`
- L2960-2963 _public property_ `public bool HasDedicatedServerAndClient { get; }`
- L2968-2971 _public property_ `public string ShortProjectName { get; }` — Project name (name of the uproject file without extension or directory name where the project is localed)
- L2976-2979 _public property_ `public List<DirectoryReference> AdditionalPluginDirectories { get; }` — AdditionalPluginDirectories from the project.uproject file
- L2986-3017 _public method_ `public string FindPluginRelativePathFromPlatformCookDir(FileReference PluginFile, DirectoryReference ProjectRoot, DirectoryReference EngineRoot, DirectoryReference LocalRoot, string ShortProjectName)` — Get the relative path to the DLC plugin's cooked output from the deployment root of the DLC. e.g. $(ProjectName)\Plugins\$(PluginName) for plugins under the Project's plugin directories.
- L3022-3028 _public property_ `public bool IsCodeBasedProject { get; }` — True if this project contains source code.
- L3029 _private field_ `private bool bIsCodeBasedProject`
- L3031-3038 _public property_ `public FileReference CodeBasedUprojectPath { get; }`
- L3042 _public property_ `public bool IsProgramTarget { get; set; }` — True if this project is a program.
- L3047 _public property_ `public FileReference RawProgramProjectOverride { get; set; }` — Returns override for Program Project files located in non-engine projects.
- L3052-3057 _public method_ `public DirectoryReference GetProjectBinariesPathForPlatform(UnrealTargetPlatform InPlatform)` — Path where the project's game (or program) binaries are built for the given target platform.
- L3059 _private field_ `private Dictionary<UnrealTargetPlatform, DirectoryReference> ProjectPlatformBinariesPaths`
- L3059 _private field_ `private Dictionary< ProjectPlatformBinariesPaths`
- L3064-3069 _public method_ `public FileReference GetProjectExeForPlatform(UnrealTargetPlatform InPlatform)` — Filename of the target game exe (or program exe) for the given target platform
- L3071 _private field_ `private Dictionary<UnrealTargetPlatform, FileReference> ProjectExePaths`
- L3071 _private field_ `private Dictionary< ProjectExePaths`
- L3076 _public field_ `public string BasedOnReleaseVersionPathOverride = null` — Override for the computed based on release version path
- L3081-3100 _public method_ `public String GetBasedOnReleaseVersionPath(DeploymentContext SC, bool bIsClientOnly)` — Get the path to the directory of the version we are basing a diff or a patch on.
- L3105-3119 _public method_ `public String GetCreateReleaseVersionPath(DeploymentContext SC, bool bIsClientOnly)` — Get the path to the target directory for creating a new release version
- L3125-3139 _public method_ `public String GetOriginalReleaseVersionPath(DeploymentContext SC, bool bIsClientOnly)` — Get the path to the directory of the originally released version we're using to generate a patch. Only required by some platforms.
- L3144-3147 _public property_ `public bool IsGeneratingPatch { get; }` — True if we are generating a patch
- L3152-3155 _public property_ `public bool ShouldAddPatchLevel { get; }` — True if we are generating a new patch pak tier
- L3157-3168 _public property_ `public List<Platform> ClientTargetPlatformInstances { get; }`
- L3170-3177 _public method_ `public TargetPlatformDescriptor GetCookedDataPlatformForClientTarget(TargetPlatformDescriptor TargetPlatformDesc)`
- L3179-3190 _public property_ `public List<Platform> ServerTargetPlatformInstances { get; }`
- L3192-3199 _public method_ `public TargetPlatformDescriptor GetCookedDataPlatformForServerTarget(TargetPlatformDescriptor TargetPlatformType)`
- L3204-3214 _public property_ `public List<SingleTargetProperties> ProjectTargets { get; }` — All auto-detected targets for this project
- L3219-3229 _public property_ `public Dictionary<UnrealTargetPlatform, ConfigHierarchy> EngineConfigs { get; }` — List of all Engine ini files for this project
- L3234-3244 _public property_ `public Dictionary<UnrealTargetPlatform, ConfigHierarchy> GameConfigs { get; }` — List of all Game ini files for this project
- L3246-3373 _public method_ `public void Validate()`
- L3375-3402 _public method_ `public FileReference FindZenProjectStoreMarker(DeploymentContext SC)`
- L3404-3417 _public method_ `public bool ShouldTreatAsFileServer(DeploymentContext SC)`
- L3419 _protected field_ `protected bool bLogged = false`
- L3420-3555 _public method_ `public virtual void ValidateAndLog()`

### `Source/Programs/AutomationTool/AutomationUtils/ProjectUtils.cs` (AutomationUtils.Automation)


#### class `AutomationTool.SingleTargetProperties`  
`public class SingleTargetProperties`  
_public; L21-26_
- L23 _public field_ `public string TargetName`
- L24 _public field_ `public string TargetClassName`
- L25 _public field_ `public TargetRules Rules`

#### class `AutomationTool.ProjectProperties`  
`public class ProjectProperties`  
_public; L31-76_
- desc: Autodetected project properties.
- L36 _public field_ `public FileReference RawProjectPath` — Full Project path. Must be a .uproject file
- L41 _public field_ `public bool bIsCodeBasedProject` — True if the uproject contains source code.
- L46 _public field_ `public List<SingleTargetProperties> Targets = new List<SingleTargetProperties>()` — List of all targets detected for this project.
- L51 _public field_ `public List<FileReference> TargetScripts = new List<FileReference>()` — List of all scripts that were compiled to create the list of Targets
- L56 _public field_ `public Dictionary<UnrealTargetPlatform, ConfigHierarchy> EngineConfigs = ...` — List of all Engine ini files for this project
- L56 _public field_ `public Dictionary< EngineConfigs = new Dictionary<UnrealTargetPlatform,ConfigHierarchy>()` — List of all Engine ini files for this project
- L61 _public field_ `public Dictionary<UnrealTargetPlatform, ConfigHierarchy> GameConfigs = ...` — List of all Game ini files for this project
- L61 _public field_ `public Dictionary< GameConfigs = new Dictionary<UnrealTargetPlatform, ConfigHierarchy>()` — List of all Game ini files for this project
- L66 _public field_ `public List<SingleTargetProperties> Programs = new List<SingleTargetProperties>()` — List of all programs detected for this project.
- L71 _public field_ `public bool bWasGenerated = false` — Specifies if the target files were generated
- L73-75 _internal ctor_ `internal ProjectProperties()`

#### class `AutomationTool.ProjectUtils`  
`public class ProjectUtils`  
_public; L81-724_
- desc: Project related utility functions.
- L135 _private property_ `private static ILogger Logger => ...`
- L136 _private field_ `private static Dictionary<PropertyCacheKey, ProjectProperties> PropertiesCache = ...`
- L136 _private field_ `private static Dictionary< PropertiesCache = new Dictionary<PropertyCacheKey, ProjectProperties>()`
- L143-146 _public method_ `public static string GetShortProjectName(FileReference RawProjectPath)` — Gets a short project name (QAGame, Elemental, etc)
- L153-158 _public method_ `public static string GetProjectPathId(FileReference RawProjectPath)` — Gets a short alphanumeric identifier for the project path.
- L168-184 _public method_ `public static ProjectProperties GetProjectProperties(FileReference RawProjectPath, List<UnrealTargetPlatform> ClientTargetPlatforms = null, List<UnrealTargetConfiguration> ClientTargetConfigurations = null, bool AssetNativizationRequested = false)` — Gets project properties.
- L193-196 _public method_ `public static bool IsCodeBasedUProjectFile(FileReference RawProjectPath, List<UnrealTargetPlatform> ClientTargetPlatforms = null, List < UnrealTargetConfiguration> ClientTargetConfigurations = null)` — Checks if the project is a UProject file with source code.
- L205-208 _public method_ `public static bool IsCodeBasedUProjectFile(FileReference RawProjectPath, UnrealTargetPlatform ClientTargetPlatform, List<UnrealTargetConfiguration> ClientTargetConfigurations = null)` — Checks if the project is a UProject file with source code.
- L216-220 _public method_ `public static DirectoryReference GetProjectClientBinariesFolder(DirectoryReference ProjectClientBinariesPath, UnrealTargetPlatform Platform)` — Returns a path to the client binaries folder.
- L230-320 _private method_ `private static ProjectProperties DetectProjectProperties(FileReference RawProjectPath, List<UnrealTargetPlatform> ClientTargetPlatforms, List<UnrealTargetConfiguration> ClientTargetConfigurations, bool AssetNativizationRequested)` — Attempts to autodetect project properties.
- L330-351 _public method_ `public static DirectoryReference GetClientProjectBinariesRootPath(FileReference RawProjectPath, TargetType TargetType, bool bIsCodeBasedProject)` — Gets the project's root binaries folder.
- L356-368 _private method_ `private static string GetRulesAssemblyFolder()` — Gets the location where all rules assemblies should go
- L375-479 _private method_ `private static void DetectTargetsForProject(ProjectProperties Properties, List<string> ExtraSearchPaths = null)` — Finds all targets for the project.
- L488-529 _private method_ `private static void CompileAndLoadTargetsAssembly(ProjectProperties Properties, FileReference TargetsDllFilename, bool DoNotCompile, List<FileReference> TargetScripts)` — Optionally compiles and loads target rules assembly.
- L537-558 _private method_ `private static bool CheckIfScriptAssemblyIsOutOfDate(FileReference TargetsDllFilename, List<FileReference> TargetScripts)` — Checks if any of the script files in newer than the generated assembly.
- L565-574 _private method_ `private static string GetTargetName(Type TargetRulesType)` — Converts class type name (usually ends with Target) to a target name (without the postfix).
- L579-587 _public method_ `public static void CleanupFolders()` — Performs initial cleanup of target rules folder
- L594-662 _public method_ `public static FileReference FindProjectFileFromName(string GameName)` — Takes a game name (e.g "ShooterGame") and tries to find the path to the project file
- L673-705 _public method_ `public static FileSystemReference GetProjectTarget(FileReference ProjectFile, UnrealBuildTool.TargetType TargetType, UnrealBuildTool.UnrealTargetPlatform TargetPlatform, UnrealBuildTool.UnrealTargetConfiguration TargetConfiguration = UnrealBuildTool.UnrealTargetConfiguration.Development, bool Cmd = false)` — Full path to the Project executable for the current platform.
- L708-723 _public method_ `public static FileSystemReference GetEditorForProject(FileReference ProjectFile)`

#### struct `AutomationTool.ProjectUtils.PropertyCacheKey`  
`struct PropertyCacheKey : IEquatable<PropertyCacheKey>`  
_private*; L89-133_
- inherits: `IEquatable<PropertyCacheKey>`
- desc: Struct that acts as a key for the project property cache. Based on these attributes DetectProjectProperties may return different answers, e.g. Some platforms require a codebased project for targets
- L91 _private* field_ `string ProjectName`
- L93 _private* field_ `UnrealTargetPlatform[] TargetPlatforms`
- L95 _private* field_ `UnrealTargetConfiguration[] TargetConfigurations`
- L97-102 _public ctor_ `public PropertyCacheKey(string InProjectName, IEnumerable<UnrealTargetPlatform> InTargetPlatforms, IEnumerable<UnrealTargetConfiguration> InTargetConfigurations)`
- L104-109 _public method_ `public bool Equals(PropertyCacheKey Other)`
- L111-114 _public method_ `public override bool Equals(object Other)`
- L116-122 _public method_ `public override int GetHashCode()`
- L124-127 _public operator_ `public static bool operator==(PropertyCacheKey A, PropertyCacheKey B)`
- L129-132 _public operator_ `public static bool operator!=(PropertyCacheKey A, PropertyCacheKey B)`

#### class `AutomationTool.BranchInfo`  
`public class BranchInfo`  
_public; L726-800_
- L762 _public field_ `public List<BranchUProject> AllProjects = new List<BranchUProject>()`
- L764-777 _public ctor_ `public BranchInfo()`
- L779-789 _public method_ `public BranchUProject FindGame(string GameName)`
- L791-799 _public method_ `public BranchUProject FindGameChecked(string GameName)`

#### class `AutomationTool.BranchInfo.BranchUProject`  
`public class BranchUProject`  
_public; L729-760_
- attrs: `[DebuggerDisplay("{GameName}")]`
- L731 _public field_ `public string GameName`
- L732 _public field_ `public FileReference FilePath`
- L734 _private field_ `private ProjectProperties CachedProperties`
- L736-746 _public property_ `public ProjectProperties Properties { get; }`
- L748-759 _public ctor_ `public BranchUProject(FileReference ProjectFile)`

### `Source/Programs/AutomationTool/AutomationUtils/Properties/AssemblyInfo.cs` (AutomationUtils.Automation)
_(no declarations)_


### `Source/Programs/AutomationTool/AutomationUtils/ScriptManager.cs` (AutomationUtils.Automation)


#### class `AutomationTool.ScriptManager`  
`public static class ScriptManager`  
_public; L21-147_
- desc: Compiles and loads script assemblies.
- L23 _private field_ `private static Dictionary<string, Type> ScriptCommands`
- L23 _private field_ `private static Dictionary< ScriptCommands`
- L24 _public field_ `public static readonly HashSet<Assembly> AllScriptAssemblies = new HashSet<Assembly>()`
- L25 _public property_ `public static HashSet<FileReference> BuildProducts { get; set; }`
- L30-72 _private* method_ `static void EnumerateScriptCommands(ILogger Logger)` — Populates ScriptCommands
- L77-108 _private* method_ `static void EnumerateBuildProducts()` — Enumerate the contents of the output directories
- L116-141 _public method_ `public static void LoadScriptAssemblies(IEnumerable<FileReference> AssemblyPaths, ILogger Logger)` — Loads all precompiled assemblies (DLLs that end with *Scripts.dll).
- L143-146 _public property_ `public static Dictionary<string, Type> Commands { get; }`

### `Source/Programs/AutomationTool/AutomationUtils/SharedUtils.cs` (AutomationUtils.Automation)


#### class `AutomationTool.SharedUtils`  
`public class SharedUtils`  
_public; L15-93_
- L22-82 _public method_ `public static string[] ParseCommandLine(string CmdLine)` — Parses the command line string and returns an array of passed arguments. Unlike the default parsing algorithm, this will treat \r\n characters just like spaces.
- L89-92 _public method_ `public static string[] ParseCommandLineAndRemoveExe(string CmdLine)` — Implements the same functionality as ParseCommandLine(), but removes the executable as the first argument.

### `Source/Programs/AutomationTool/AutomationUtils/SourceIndexingUtils.cs` (AutomationUtils.Automation)


#### class `AutomationUtils.SourceIndexingUtils`  
`public static class SourceIndexingUtils`  
_public; L16-142_
- L26-60 _public method_ `public static VFSPathMappingList ParseVFSMapping(string VFSMapping)` — Read a list of Virtual File System path transformations from a single string. The string may have multiple entries separate by semicolons. Each entry is an assignment: LocalPath=VirtualPath. LocalPath may use [Root] which is replaced by by the current workspace root (Unreal.RootDirectory).
- L66-77 _public method_ `public static void OutputVFSMapping(VFSPathMappingList VFSMapping)` — Helper function printing the given filesystem path mapping to the log for debug purposes.
- L86-99 _public method_ `public static string ConvertLocalToVirtualized(string Local, VFSPathMappingList VFSMapping)` — Converts a local path to a virtualized path (as generated by Unreal Build Tool when using Virtual File System i.e. compiling with -vfs switch). Only the first matching rule from VFSMapping is applied.
- L108-141 _public method_ `public static Dictionary<string, P4HaveRecord> BuildSourceDatabase(string Pattern, string VFSMappingString)` — Build a database of source code files in the current Perforce workspace. By relying on the standard layout for UE projects i.e. the fact that source code is in Source directories, we may very significantly reduce the about of data sent to us from the server.

### `Source/Programs/AutomationTool/AutomationUtils/StagedDirectoryReference.cs` (AutomationUtils.Automation)


#### class `StagedDirectoryReference`  
`public class StagedDirectoryReference : StagedFileSystemReference, IEquatable<StagedDirectoryReference>`  
_public; L10-105_
- inherits: `StagedFileSystemReference, IEquatable<StagedDirectoryReference>`
- L15 _public field_ `public static readonly StagedDirectoryReference Root = new StagedDirectoryReference("")` — Shared instance representing the root directory
- L21-23 _public ctor_ `public StagedDirectoryReference(string Name) : base(Name)` — Constructor
- L31-34 _public method_ `public static StagedDirectoryReference Combine(string BaseDir, params string[] Fragments)` — Create a staged directory reference by concatenating multiple strings
- L42-45 _public method_ `public static StagedDirectoryReference Combine(StagedDirectoryReference BaseDir, params string[] Fragments)` — Create a staged directory reference by concatenating multiple strings
- L53-63 _public operator_ `public static bool operator ==(StagedDirectoryReference A, StagedDirectoryReference B)` — Compares two directory references for equality
- L71-74 _public operator_ `public static bool operator !=(StagedDirectoryReference A, StagedDirectoryReference B)` — Compares two directory references for inequality
- L81-85 _public method_ `public override bool Equals(object Obj)` — Compares against another object for equality
- L92-95 _public method_ `public bool Equals(StagedDirectoryReference Other)` — Compares against another object for equality
- L101-104 _public method_ `public override int GetHashCode()` — Gets a hash code for this reference.

### `Source/Programs/AutomationTool/AutomationUtils/StagedFileReference.cs` (AutomationUtils.Automation)


#### class `StagedFileReference`  
`public class StagedFileReference : StagedFileSystemReference, IEquatable<StagedFileReference>`  
_public; L14-190_
- inherits: `StagedFileSystemReference, IEquatable<StagedFileReference>`
- desc: Location of a staged file. Stored in a normalized format with forward slashes as directory separators.
- L20-22 _public ctor_ `public StagedFileReference(string Name) : base(Name)` — Constructor
- L29-31 _private ctor_ `private StagedFileReference(string Name, Sanitize Sanitize) : base(Name, Sanitize)` — Protected constructor. Initializes to the given parameters without validation.
- L36-50 _public property_ `public StagedDirectoryReference Directory { get; }` — Accessor for the directory containing this file
- L57-77 _public method_ `public bool ContainsName(string OtherName)` — Determines if the name contains the given fragment
- L87-99 _public method_ `public static bool TryRemap(StagedFileReference InputFile, StagedDirectoryReference SourceDir, StagedDirectoryReference TargetDir, out StagedFileReference RemappedFile)` — Attempts to remap this file reference from one directory to another
- L107-110 _public method_ `public static StagedFileReference Combine(string BaseDir, params string[] Fragments)` — Create a staged file reference by concatenating multiple strings
- L118-121 _public method_ `public static StagedFileReference Combine(StagedDirectoryReference BaseDir, params string[] Fragments)` — Create a staged file reference by concatenating multiple strings
- L127-130 _public method_ `public StagedFileReference ToLowerInvariant()` — Converts this file reference to a lowercase invariant form.
- L138-148 _public operator_ `public static bool operator ==(StagedFileReference A, StagedFileReference B)` — Compares two file references for equality
- L156-159 _public operator_ `public static bool operator !=(StagedFileReference A, StagedFileReference B)` — Compares two file references for inequality
- L166-170 _public method_ `public override bool Equals(object Obj)` — Compares against another object for equality
- L177-180 _public method_ `public bool Equals(StagedFileReference Other)` — Compares against another object for equality
- L186-189 _public method_ `public override int GetHashCode()` — Gets a hash code for this reference.

### `Source/Programs/AutomationTool/AutomationUtils/StagedFileSystemReference.cs` (AutomationUtils.Automation)


#### class `StagedFileSystemReference`  
`public abstract class StagedFileSystemReference`  
_public; L14-181_
- desc: Location of a staged file or directory. Stored in a normalized format with forward slashes as directory separators.
- L27 _public field_ `public readonly string Name` — The name of this file system entity
- L33-116 _public ctor_ `public StagedFileSystemReference(string InName)` — Constructor
- L123-126 _public ctor_ `public StagedFileSystemReference(string Name, Sanitize Sanitize)` — Protected constructor. Initializes to the given parameters without validation.
- L133-143 _public method_ `public bool HasExtension(string Extension)` — Checks whether this name has the given extension.
- L150-153 _public method_ `public bool IsUnderDirectory(StagedDirectoryReference Directory)` — Checks if this path is equal to or under the given directory
- L159-171 _protected method_ `static protected string CombineStrings(string BaseDirectory, params string[] Fragments)` — Create a full path by concatenating multiple strings
- L177-180 _public method_ `public override string ToString()` — Returns the name of this entity

#### enum `StagedFileSystemReference.Sanitize`  
`public enum Sanitize`  
_public; L19-22_
- desc: Special value used to invoke the non-sanitizing constructor overload
- L21 _public* enumerator_ `None`

### `Source/Programs/AutomationTool/AutomationUtils/StreamUtils.cs` (AutomationUtils.Automation)


#### class `AutomationTool.StreamUtils`  
`public static class StreamUtils`  
_public; L15-74_
- desc: Extension methods for Stream classes
- L23-27 _public method_ `public static Stream ReadFrom(this Stream output, Stream input)` — Read a stream into another, buffering in 4K chunks.
- L36-49 _public method_ `public static Stream ReadFrom(this Stream output, Stream input, out long totalBytesRead)` — Read a stream into another, buffering in 4K chunks.
- L56-61 _public method_ `public static MemoryStream ReadIntoMemoryStream(this Stream input)` — Read stream into a new MemoryStream. Useful for chaining together expressions.
- L69-73 _public method_ `public static Stream Write(this Stream stream, byte[] arr)` — Writes the entire contents of a byte array to the stream.

### `Source/Programs/AutomationTool/AutomationUtils/UBTUtils.cs` (AutomationUtils.Automation)


#### class `AutomationTool.CommandUtils`  
`public partial class CommandUtils`  
_public; L11-163_
- L21-36 _public method_ `public static void RunUBT(CommandEnvironment Env, string UBTExecutable, string CommandLine)` — attrs: `[Obsolete("Deprecated in UE5.1; function signature has changed")]` — Runs UBT with the specified command line. Automatically creates a logfile. When no LogName is specified, the executable name is used as logfile base name.
- L45-61 _public method_ `public static void RunUBT(CommandEnvironment Env, FileReference UnrealBuildToolDll, string CommandLine)` — Runs UBT with the specified command line. Automatically creates a logfile. When no LogName is specified, the executable name is used as logfile base name.
- L70-107 _private method_ `private static FileReference GetUBTLogLocationFromArgs(CommandEnvironment Env, string CommandLine)` — Generates a log file name from a UBT command line
- L117-129 _public method_ `public static string UBTCommandline(FileReference Project, string Target, UnrealTargetPlatform Platform, UnrealTargetConfiguration Config, string AdditionalArgs = "")` — Builds a UBT Command line.
- L143-146 _public method_ `public static void RunUBT(CommandEnvironment Env, string UBTExecutable, FileReference Project, string Target, UnrealTargetPlatform Platform, UnrealTargetConfiguration Config, string AdditionalArgs = "")` — attrs: `[Obsolete("Deprecated in UE5.1; Use the alternate version below with the UnrealBuildTool.dll, not executable")]` — Builds a target using UBT. Automatically creates a logfile. When no LogName is specified, the executable name is used as logfile base name.
- L159-162 _public method_ `public static void RunUBT(CommandEnvironment Env, FileReference UnrealBuildToolDll, FileReference Project, string Target, UnrealTargetPlatform Platform, UnrealTargetConfiguration Config, string AdditionalArgs = "")` — Builds a target using UBT. Automatically creates a logfile. When no LogName is specified, the executable name is used as logfile base name.

### `Source/Programs/AutomationTool/AutomationUtils/UnrealBuild.cs` (AutomationUtils.Automation)


#### class `AutomationTool.UnrealBuildException`  
`class UnrealBuildException : AutomationException`  
_internal*; L23-35_
- inherits: `AutomationException`
- L25-29 _public ctor_ `public UnrealBuildException(string Message) : base(ExitCode.Error_UBTFailure, "BUILD FAILED: " + Message)`
- L31-34 _public ctor_ `public UnrealBuildException(string Format, params object[] Args) : this(String.Format(Format, Args))`

#### class `AutomationTool.UnrealBuild`  
`public class UnrealBuild`  
_public; L43-773_
- attrs: `[Help("ForceMonolithic", "Toggle to combined the result into one executable")] [Help("ForceDebugInfo", "Forces debug info even in development builds")] [Help("NoXGE", "Toggle to disable the distributed build process")] [Help("ForceNonUnity", "Toggle to disable the unity build system")] [Help("ForceUnity", "Toggle to force enable the unity build system")] [Help("Licensee", "If set, this build is be`
- L45 _private field_ `private BuildCommand OwnerCommand`
- L51 _public property_ `public bool AlwaysBuildUHT { get; set; }` — attrs: `[Obsolete]` — If true we will let UBT build UHT
- L53-61 _public method_ `public void AddBuildProduct(string InFile)`
- L63-69 _private* method_ `static bool IsBuildReceipt(string FileName)`
- L71-88 _private* method_ `BuildManifest AddBuildProductsFromManifest(FileReference ManifestFile)`
- L90-101 _private method_ `private void PrepareUBT()`
- L103-121 _public method_ `public void CleanWithUBT(string TargetName, UnrealTargetPlatform Platform, UnrealTargetConfiguration Config, FileReference UprojectPath, string InAddArgs = "")`
- L123-134 _private* method_ `List<FileReference> GetManifestFiles(List<BuildTarget> Targets)`
- L136-147 _private* method_ `FileReference GetManifestFile(BuildTarget Target, int Index)`
- L149-215 _private* method_ `void BuildWithUBT(List<BuildTarget> Targets, Dictionary<BuildTarget, BuildManifest> TargetToManifest, bool DisableXGE, bool AllCores, bool SkipBuild)`
- L217-236 _private* method_ `string GetTargetArguments(BuildTarget Target, FileReference ManifestFile)`
- L238-248 _private* method_ `string[] DotNetProductExtenstions()`
- L250-261 _private* method_ `string[] SwarmBuildProducts()`
- L263-273 _private* method_ `void AddBuildProductsForCSharpProj(string CsProj)`
- L275-285 _private* method_ `void AddIOSBuildProductsForCSharpProj(string CsProj)`
- L287-308 _private* method_ `void AddSwarmBuildProducts()`
- L313-336 _public method_ `public List<FileReference> UpdateVersionFiles(bool ActuallyUpdateVersionFiles = true, int? ChangelistNumberOverride = null, int? CompatibleChangelistNumberOverride = null, string Build = null, string BuildURL = null, bool? IsPromotedOverride = null)` — Updates the engine version files
- L338-397 _public method_ `public static List<FileReference> StaticUpdateVersionFiles(int ChangelistNumber, int CompatibleChangelistNumber, string Branch, string Build, string BuildURL, bool bIsLicenseeVersion, bool bIsPromotedBuild, bool bDoUpdateVersionFiles)`
- L516-520 _public ctor_ `public UnrealBuild(BuildCommand Command)`
- L522-525 _private method_ `private bool ParseParam(string Name)`
- L527-530 _private method_ `private string ParseParamValue(string Name)`
- L532-535 _private method_ `private int ParseParamInt(string Name, int Default = 0)`
- L548-617 _public method_ `public void Build(BuildAgenda InAgenda, bool? InDeleteBuildProducts = null, bool InUpdateVersionFiles = true, bool InForceNoXGE = false, bool InAllCores = false, int? InChangelistNumberOverride = null, Dictionary<BuildTarget, BuildManifest> InTargetToManifest = null, bool InSkipBuild = false)` — Executes a build.
- L623-645 _public method_ `public static void CheckBuildProducts(HashSet<string> BuildProductFiles)` — Checks to make sure there was at least one build product, and that all files exist. Also, logs them all out.
- L653-685 _public method_ `public static void AddBuildProductsToChangelist(int WorkingCL, IEnumerable<string> Files)` — Adds or edits existing files at head revision, expecting an exclusive lock, resolving by clobbering any existing version
- L693-701 _private method_ `private static bool IsBuildProduct(string File, P4FileStat FileStats)` — Determines if this file is a build product.
- L706-716 _public method_ `public void AddUBTFilesToBuildProducts()` — Add UBT files to build products
- L721-733 _public method_ `public void AddUATFilesToBuildProducts()` — Copy the UAT files to their precompiled location, and add them as build products
- L735-746 _private* method_ `DirectoryReference GetManifestDir(FileReference ProjectFile)`
- L748-751 _private* method_ `FileReference GetManifestFile(FileReference ProjectFile)`
- L754-757 _public method_ `public static string GetUBTExecutable()` — attrs: `[Obsolete("Deprecated in UE5.1; use UnrealBuildToolDll")]`
- L760-766 _public property_ `public string UBTExecutable { get; }` — attrs: `[Obsolete("Deprecated in UE5.1; use UnrealBuildToolDll")]`
- L768 _public property_ `public static FileReference UnrealBuildToolDll => ...`
- L772 _public field_ `public readonly HashSet<string> BuildProductFiles = new HashSet<string>(StringComparer.InvariantCultureIgnoreCase)`

#### class `AutomationTool.UnrealBuild.BuildTarget`  
`public class BuildTarget`  
_public; L400-440_
- attrs: `[DebuggerDisplay("{TargetName} {Platform} {Config}")]`
- L405 _public field_ `public string TargetName` — Name of the target
- L410 _public field_ `public FileReference UprojectPath` — For code-based projects with a .uproject, the TargetName isn't enough for UBT to find the target, this will point UBT to the target
- L415 _public field_ `public UnrealTargetPlatform Platform` — Platform to build
- L420 _public field_ `public UnrealTargetConfiguration Config` — Configuration to build
- L425 _public field_ `public string UBTArgs` — Extra UBT args
- L430 _public field_ `public bool? Clean` — Whether to clean this target. If not specified, the target will be cleaned if -Clean is on the command line.
- L436-439 _public method_ `public override string ToString()` — Format as string

#### class `AutomationTool.UnrealBuild.BuildAgenda`  
`public class BuildAgenda`  
_public; L443-513_
- L449 _public field_ `public List<string> DotNetProjects = new List<string>()` — .NET .csproj files that will be compiled and included in the build. Currently we assume the output binary file names match the solution file base name, but with various different binary file extensions.
- L451 _public field_ `public string SwarmAgentProject = ""`
- L452 _public field_ `public string SwarmCoordinatorProject = ""`
- L457 _public field_ `public List<BuildTarget> Targets = new List<BuildTarget>()` — List of targets to build. These can be various Unreal projects, programs or libraries in various configurations
- L467-483 _public method_ `public void AddTarget(string TargetName, UnrealTargetPlatform InPlatform, UnrealTargetConfiguration InConfiguration, FileReference InUprojectPath = null, string InAddArgs = "")` — Adds a target with the specified configuration.
- L493-512 _public method_ `public void AddTargets(string[] TargetNames, UnrealTargetPlatform InPlatform, UnrealTargetConfiguration InConfiguration, FileReference InUprojectPath = null, string InAddArgs = "")` — Adds multiple targets with the specified configuration.

### `Source/Programs/AutomationTool/AutomationUtils/Utils.cs` (AutomationUtils.Automation)


#### class `AutomationTool.InternalUtils`  
`public static class InternalUtils`  
_public; L24-1061_
- desc: AutomationTool internal Utilities.
- L26 _private* property_ `static ILogger Logger => ...`
- L35-47 _public method_ `public static string GetEnvironmentVariable(string VarName, string Default, bool bQuiet = false)` — Gets environment variable value.
- L56-101 _public method_ `public static bool SafeCreateDirectory(string Path, bool bQuiet = false)` — Creates a directory. @todo: this function should not exchange exception context for error codes that can be ignored.
- L109-164 _public method_ `public static bool SafeDeleteFile(string Path, bool bQuiet = false)` — Deletes a file (will remove read-only flag if necessary).
- L172-201 _private method_ `private static bool RecursivelyDeleteDirectory(string Path, bool bQuiet = false)` — Recursively deletes a directory and all its files and subdirectories.
- L209-248 _public method_ `public static bool SafeDeleteEmptyDirectory(string Path, bool bQuiet = false)` — Deletes an empty directory.
- L256-270 _public method_ `public static bool SafeDeleteDirectory(string Path, bool bQuiet = false)` — Deletes a directory and all its contents. Will delete read-only files.
- L282-326 _public method_ `public static bool SafeRenameDirectory(string OldName, string NewName, bool bQuiet = false, bool bRetry = true, bool bThrow = false)` — Renames/moves a directory and all its contents
- L335-373 _public method_ `public static bool SafeRenameFile(string OldName, string NewName, bool bQuiet = false)` — Renames/moves a file.
- L376 _private field_ `private static char[] IgnoredIniValuePrefixes = { '+', '-', ' ', '\t' }`
- L378-441 _private method_ `private static void FilterIniFile(string SourceName, string TargetName, List<string> IniKeyDenyList, List<string> InSectionDenyList, List<string> InSectionAllowList)`
- L455-571 _public method_ `public static bool SafeCopyFile(string SourceName, string TargetName, bool bQuiet = false, OverrideCopyDelegate OverrideCopyHandler = null, List<string> IniKeyDenyList = null, List<string> IniSectionDenyList = null, List<string> IniSectionAllowList = null, bool bSafeCreateDirectory = false)` — Copies a file.
- L579-593 _public method_ `public static string[] SafeReadAllLines(string Filename)` — Reads all lines from a file.
- L600-614 _public method_ `public static string SafeReadAllText(string Filename)` — Reads all text from a file.
- L624-660 _public method_ `public static string[] FindFiles(string Path, string SearchPattern, bool Recursive, bool bQuiet = false)` — Finds files in the specified path.
- L670-677 _public method_ `public static string[] FindDirectories(string Path, string SearchPattern, bool Recursive, bool bQuiet = false)` — Finds directories in the specified path.
- L687-704 _public method_ `public static string[] SafeFindFiles(string Path, string SearchPattern, bool Recursive, bool bQuiet = false)` — Finds files in the specified path.
- L714-731 _public method_ `public static string[] SafeFindDirectories(string Path, string SearchPattern, bool Recursive, bool bQuiet = false)` — Finds directories in the specified path.
- L739-756 _public method_ `public static bool SafeFileExists(string Path, bool bQuiet = false)` — Checks if a file exists.
- L765-782 _public method_ `public static bool SafeDirectoryExists(string Path, bool bQuiet = false)` — Checks if a directory exists.
- L790-805 _public method_ `public static bool SafeWriteAllLines(string Path, string[] Text)` — Writes lines to a file.
- L813-828 _public method_ `public static bool SafeWriteAllText(string Path, string Text)` — Writes text to a file.
- L836-851 _public method_ `public static bool SafeWriteAllBytes(string Path, byte[] Bytes)` — Writes text to a file.
- L853-876 _public method_ `public static void Robust_CopyFile(string InputFileName, string OutputFileName)`
- L878-881 _public method_ `public static void Robust_FileExists(string Filename, string Message)`
- L883-906 _public method_ `public static void Robust_FileExists(bool bQuiet, string Filename, string Message)`
- L908-932 _public method_ `public static bool Robust_DirectoryExists_NoExceptions(string Directoryname, string Message)`
- L934-963 _public method_ `public static bool Robust_DirectoryExistsAndIsWritable_NoExceptions(string Directoryname)`
- L972-1020 _public method_ `public static bool TryResolveMappedNetworkPath( string InPath, out string UNCPath )` — Attempts to get the shared network path for a given mapped network drive e.g. X:\Shared\Path\ -> \\MyServer\Root\Shared\Path\
- L1028-1044 _public method_ `public static IEnumerable<string> EnumerateLines(this string Str)` — Efficient iterator for walking over a string line by line.
- L1056-1060 _public method_ `public static bool IsDnsEligible(System.Net.NetworkInformation.IPAddressInformation AddressInformation)` — Indicates whether the Internet Protocol (IP) address is valid to appear in a Domain Name System (DNS) server database. Addresses in the range 169.254.0.0 to 169.254.255.255 are not DNS eligible. These addresses are reserved for Automatic Private IP Addressing (APIPA). https://docs.microsoft.com/en-us/dotnet/api/system.net.networkinformation.ipaddressinformation.isdnseligible?view=netcore-3.1 NET Core 3.1 does not include a usable implementation of UnicastIPAddressInformation.IsDnsEligible() for Linux or Mac

#### class `AutomationTool.FEngineVersionSupport`  
`public class FEngineVersionSupport`  
_public; L1070-1232_
- desc: This is to ensure that UAT can produce version strings precisely compatible with FEngineVersion. WARNING: If FEngineVersion compatibility changes, this code needs to be updated.
- L1079 _public field_ `public readonly Version Version` — The version info read from the Version header. The populated fields will be Major, Minor, and Build from the MAJOR, MINOR, and PATCH lines, respectively. Expects lines like: #define APP_MAJOR_VERSION 0 #define APP_MINOR_VERSION 0 #define APP_PATCH_VERSION 0
- L1084 _public field_ `public readonly int Changelist` — The changelist this version is associated with
- L1089 _public field_ `public readonly string BranchName` — The Branch name associated with the version
- L1096-1123 _public method_ `public static Version ReadVersionFromFile(string Filename)` — Reads a Version.h file, looking for macros that define the MAJOR/MINOR/PATCH version fields. Expected to match the Version.h in the engine.
- L1131-1150 _public ctor_ `public FEngineVersionSupport(Version InVersion, int InChangelist = -1, string InBranchName = null)` — Ctor that takes a pre-determined Version. Gets the Changelist and BranchName from the current CommandUtils.P4Env.
- L1159-1167 _public method_ `public override string ToString()` — Gets a version string compatible with FEngineVersion's native parsing code.
- L1169-1175 _public method_ `public override bool Equals(object obj)`
- L1177-1180 _public method_ `public override int GetHashCode()`
- L1188-1191 _public method_ `public static FEngineVersionSupport FromVersionFile(string Filename, int InChangelist = -1, string InBranchName = null)` — Ctor initializes with the values from the supplied Version file. The BranchName and CL are also taken from the current CommandUtils.P4Env.
- L1199-1231 _public method_ `public static FEngineVersionSupport FromString(string versionString, bool bAllowNoVersion = false)` — Creates a FEngineVersionSupport from a string that matches the format given in ToString.

#### class `AutomationTool.VersionFileUpdater`  
`public class VersionFileUpdater`  
_public; L1237-1417_
- desc: VersionFileUpdater.
- L1242-1252 _public ctor_ `public VersionFileUpdater(FileReference Filename)` — Constructor
- L1260-1281 _public method_ `public void ReplaceLine(string Prefix, string Suffix, int OccurenceIdx = 0)` — Finds the line containing the same tokens as the given prefix, and change the suffix to be the given string
- L1290-1309 _private* method_ `static bool MatchCppTokens(string Line, ref int LineOffset, string Other)` — Tries to read a sequence of tokens from the given line of text, updating a position within it.
- L1317-1344 _private* method_ `static string ReadCppToken(string Line, ref int Offset)` — Reads a single token (using a very rough approximation of a C++ token) from the given line
- L1349-1374 _public method_ `public void Commit()` — Doc
- L1382-1403 _public method_ `public static void MakeFileWriteable(string FileName, bool bForce = false)` — Makes a version file writeable. If P4 is enabled, syncs it to revision 0 to prevent conflicts with the P4 have table rather than checking it out, since we never intend to submit it to Perforce. For existing writeable files, P4V prompts the user to overwrite the next time they sync.
- L1408 _protected field_ `protected FileInfo MyFile` — Doc
- L1412 _protected field_ `protected List<string> Lines` — Doc
- L1416 _protected field_ `protected List<string> OriginalLines` — Doc

### `Source/Programs/AutomationTool/AutomationUtils/WindowsHostPlatform.cs` (AutomationUtils.Automation)


#### class `AutomationTool.WindowsHostPlatform`  
`class WindowsHostPlatform : HostPlatform`  
_internal*; L13-126_
- inherits: `HostPlatform`
- L15 _private* field_ `static string CachedFrameworkMsbuildTool = ""`
- L18-50 _public method_ `public override string GetFrameworkMsbuildExe()` — attrs: `[SupportedOSPlatform("windows")]`
- L52-55 _public property_ `public override string RelativeBinariesFolder { get; }`
- L57-67 _public method_ `public override string GetUnrealExePath(string UnrealExe)`
- L69-72 _public property_ `public override string LocalBuildsLogFolder { get; }`
- L74-77 _public property_ `public override string P4Exe { get; }`
- L79-83 _public method_ `public override Process CreateProcess(string AppName)`
- L85-87 _public method_ `public override void SetupOptionsForRun(ref string AppName, ref CommandUtils.ERunOptions Options, ref string CommandLine)`
- L89-92 _public method_ `public override void SetConsoleCtrlHandler(ProcessManager.CtrlHandlerDelegate Handler)`
- L94-97 _public property_ `public override UnrealTargetPlatform HostEditorPlatform { get; }`
- L99-102 _public property_ `public override string PdbExtension { get; }`
- L104 _private* field_ `static string[] SystemServices = new string[] { "winlogon", "system idle process", "taskmgr", "spoolsv", "csrss", "smss", "svchost", "services", "lsass", "conhost", "oobe", "mmc" }`
- L119-125 _public property_ `public override string[] DontKillProcessList { get; }`

### `Source/Programs/AutomationTool/AutomationUtils/ZenUtils.cs` (AutomationUtils.Automation)


#### class `AutomationUtils.ZenWorkspace`  
`public class ZenWorkspace`  
_public; L29-35_
- L31 _public property_ `public string id { get; set; }`
- L32 _public property_ `public string root_path { get; set; }`
- L33 _public property_ `public bool allow_share_creation_from_http { get; set; }`
- L34 _public property_ `public List<ZenWorkspaceShare> shares { get; set; }`

#### class `AutomationUtils.ZenWorkspaceShare`  
`public class ZenWorkspaceShare`  
_public; L37-41_
- L39 _public property_ `public string id { get; set; }`
- L40 _public property_ `public string share_path { get; set; }`

#### class `AutomationUtils.ZenRunContext`  
`public class ZenRunContext`  
_public; L43-580_
- L45 _public property_ `public string Executable { get; set; }`
- L46 _public property_ `public string CommandLineArguments { get; set; }`
- L47 _public property_ `public string DataPath { get; set; }`
- L49 _public property_ `public string HostName { get; set; }`
- L50 _public property_ `public int HostPort { get; set; }`
- L58-61 _public method_ `public string GetHttpHostNameAndPortString()` — Return the "HostName:HostPort" string that should be used as the "servername" when creating http URLs, e.g. $"http:///{HostName}/prj/{Project}/oplog/{Oplog}" When using unixsockets we use a valid debugname string rather than than the "servername" used to open the socket for the HttpClient, which is instead a path to the .sock file on disk. @see GetRobustHostNameAndPortStrings.
- L62 _public property_ `public bool IsValid { get; set; }`
- L63 _public property_ `public bool UsingUnixSocket { get; set; }`
- L65 _public property_ `public static ILogger Logger => ...`
- L66 _public property_ `public static int DefaultPort { get; }`
- L68-72 _public method_ `public void InitializeFromHostNameAndPort(string SocketHostNameAndPort)`
- L74-77 _public method_ `public void InitializeFromHostNameAndPort(string InSocketHostName, int InHostPort)`
- L79-82 _public method_ `public void InitializeFromHostName(string InSocketHostName)`
- L84-99 _public method_ `public static ZenRunContext ReadFromContextFile(FileReference ContextFile)`
- L101-110 _public method_ `public static ZenRunContext DiscoverServerContext()`
- L112-156 _private method_ `private void InitializeInstanceData()`
- L158-172 _private method_ `private void InitializeHostNameInternal(string InHostName, int InHostPort)`
- L179-186 _private method_ `private HttpClient CreateHttpClientInternal()` — Return an HttpClient that can be used to communicate with the ZenServer. If a UnixSocket is being used, the SocketsHttpHandler of the HttpClient if set to read from the socket file.
- L193-200 _public method_ `public static HttpClient CreateHttpClient(string InSocketHostName)` — Return an HttpClient that communicates with a ZenServer at the given HostName. If the hostname specifies a UnixSocket, the SocketsHttpHandler of the HttpClient if set to read from the socket file.
- L207-219 _public method_ `public static HttpClient CreateUnixSocketHttpClient(string UnixSocketPath)` — Return an HttpClient that communicates with a ZenServer through a UnixSocketPath. Sets the SocketsHttpHandler of the HttpClient to read from the socket file.
- L229-252 _public method_ `public static void SplitHostNameAndPort(string HostNameAndPort, out string OutHostName, out int OutHostPort)` — Split a string "Hostname:HostPort" into the two parts. Silently handle edge cases such as a missing HostPort and colons in the Hostname. Leading and trailing spaces are trimmed, but spaces before or after the colon are not trimmed and are treated as part of the hostname. Valid strings: "hostname", "1.2.3.4", "[::1]" "hostname:1234", "1.2.3.4:1234", "[::1]:1234"
- L265-287 _public method_ `public static void GetRobustHostNameAndPortStrings(string InHostName, int InHostPort, out string SocketHostNameAndPort, out string HttpHostNameAndPort)` — Returns the hostname and port connection information as a single string, e.g. "localhost:8558". When not using unixsockets, OutSocketHostName and OutHttpHostName are identical, but when using unixsockets they can be different. When using unix sockets, OutSocketHostNameAndPort is the unix filepath of the .sock file and is used in an HttpClient's HttpMessageHandler. OutHttpHostNameAndPort is used in the URI passed to HttpRequestMessage. It is used only for display to the user because the HttpMessageHandler bypasses it, but it needs to be a valid hostname string and can have no path separators. When the hostname specifies a unix socket we therefore return e.g. ("/usr/path/zenserver.sock", "unixsocket").
- L293-296 _public method_ `public static bool IsUnixSocketPath(string InHostName)` — Returns whether a given HostName (string must not include a :HostPort suffix) is a unix socket path, which requires communicating through the socket file rather than an http uri.
- L302-330 _public method_ `public bool IsServiceRunning()` — Queries the server's health status to check if the the service is running
- L336-344 _public method_ `public bool DoesServerSupportWorkspaces()` — Checks if the server was run with --workspaces-enabled
- L353-384 _public method_ `public ZenWorkspace GetOrCreateWorkspace(DirectoryReference BaseDir, bool Dynamic = false)` — If there doesn't exists a workspace pointing to BaseDir (or above in the subtree) will create a new zen workspace pointing to BaseDir. If a workspace already exists it won't change its Dynamic setting.
- L391-434 _public method_ `public ZenWorkspaceShare GetOrCreateShare(DirectoryReference ShareDir)` — If there doesn't exists a workspace share pointing to ShareDir, will create a new zen workspace share pointing to it.
- L440-479 _private method_ `private List<ZenWorkspace> GetWorkspaceList()` — Queries the server for a full list of existing workspaces
- L486-503 _public method_ `public ZenWorkspace FindWorkspaceForDir(DirectoryReference BaseDir)` — Finds a zen workspace for the specified directory. Includes workspaces that are above in the directory tree
- L510-528 _public method_ `public ZenWorkspaceShare FindShareForDir(DirectoryReference ShareDir)` — Finds a zen workspace share for the specified directory.
- L539-579 _public method_ `public ZenWorkspaceShare CreateWorkspaceAndShare(DirectoryReference ShareDir)` — Creates a zen workspace share pointing to ShareDir. If necessary it creates a zen workspace in the parent directory. ShareDir must not be a root directory, e.g. d:\

#### class `AutomationUtils.ZenUtils`  
`public static class ZenUtils`  
_public; L582-712_
- L584-594 _private method_ `private static string GetServerExecutableName()`
- L596-601 _public method_ `public static string GetZenInstallPath()`
- L603-606 _public method_ `public static string GetZenRunContextFile()`
- L608-621 _public method_ `public static FileReference GetZenExeLocation(string ExecutableName)`
- L623-638 _public method_ `public static bool IsLocalZenServerRunning()`
- L640-645 _public method_ `public static bool IsZenServerRunning(string SocketHostNameAndPort)`
- L647-652 _public method_ `public static bool IsZenServerRunning(string SocketHostName, int HostPort)`
- L654-658 _public method_ `public static HttpClient CreateHttpClient(string SocketHostNameAndPort)`
- L660-667 _public method_ `public static JsonSerializerOptions GetDefaultJsonSerializerOptions()`
- L669-676 _public method_ `public static void ZenLaunch(FileReference SponsorFile)`
- L678-692 _public method_ `public static bool RunZenExe(string Command)`
- L694-711 _public method_ `public static bool ShouldSetupPakStreaming(ProjectParams Params, DeploymentContext SC)`

#### class `AutomationUtils.ZenUATProcessUtil`  
`public static class ZenUATProcessUtil`  
_public; L714-721_
- L716 _private field_ `private static readonly ConcurrentDictionary<ManagedProcess, ZenUatProcessStub> ProcessStubs = ...`
- L716 _private field_ `private static readonly ConcurrentDictionary< ProcessStubs = new ConcurrentDictionary<ManagedProcess, ZenUatProcessStub>()`
- L717-720 _public method_ `public static IProcess GetUATProcessStub(ManagedProcess process)`

#### class `AutomationUtils.ZenUatProcessStub`  
`public class ZenUatProcessStub(ManagedProcess process) : IProcess`  
_public; L723-744_
- L725-728 _public method_ `public void StopProcess(bool killDescendants = true)`
- L730 _public property_ `public bool HasExited => ...`
- L732-743 _public method_ `public string GetProcessName()`
