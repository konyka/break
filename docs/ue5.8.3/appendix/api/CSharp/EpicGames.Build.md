# CSharp / EpicGames.Build

- project root: `Source/Programs/Shared/EpicGames.Build`
- files: 30; symbols: 732
- symbol kinds: class=44, const=21, ctor=30, enum=8, enumerator=73, field=164, interface=2, method=292, property=88, record=1, record struct=1, struct=8
- access marked `*` is implicit (not written in source)

### `Source/Programs/Shared/EpicGames.Build/Automation/CommandLine.cs` (EpicGames.Build)


#### class `UnrealBuildBase.CommandInfo`  
`public class CommandInfo(string CommandNameIn)`  
_public; L11-32_
- desc: Command to execute info.
- L13 _public property_ `public string CommandName { get; }`
- L15 _public property_ `public List<string> Arguments { get; set; }`
- L17-31 _public method_ `public override string ToString()`

#### class `UnrealBuildBase.ParsedCommandLine`  
`public partial class ParsedCommandLine(Dictionary<string, string> GlobalParameters, HashSet<string> IgnoredGlobalParameters)`  
_public; L34-121_
- L39-43 _public property_ `public Dictionary<string, string> GlobalParameters { get; set; }` — Argument name and description for known arguments
- L45-49 _public property_ `public HashSet<string> IgnoredGlobalParameters { get; set; }`
- L51 _private* field_ `readonly HashSet<string> GlobalParameterValues = new(StringComparer.InvariantCultureIgnoreCase)`
- L53-66 _public method_ `public void SetGlobal(string Parameter)`
- L68-82 _public method_ `public bool TrySetGlobal(string Parameter)`
- L84-97 _public method_ `public bool IsSetGlobal(string Parameter)`
- L99 _private* field_ `Dictionary<string, object?> UncheckedParameters = ...`
- L99 _private* field_ `Dictionary< UncheckedParameters = new(StringComparer.InvariantCultureIgnoreCase)`
- L100-103 _public method_ `public void SetUnchecked(string Name, object? Value = null)`
- L105-108 _public method_ `public bool IsSetUnchecked(string Name)`
- L110-113 _public method_ `public object? GetValueUnchecked(string Name)`
- L115-118 _public method_ `public bool IsParameterIgnored(string Parameter)`
- L120 _public field_ `public List<CommandInfo> CommandsToExecute = []`

### `Source/Programs/Shared/EpicGames.Build/Automation/ExitCode.cs` (EpicGames.Build)


#### enum `UnrealBuildBase.ExitCode`  
`public enum ExitCode`  
_public; L7-64_
- attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Naming", "CA1707:Identifiers should not contain underscores", Justification = "Intentional")]`
- L9 _public* enumerator_ `Error_UATNotFound = -1`
- L10 _public* enumerator_ `Success = 0`
- L11 _public* enumerator_ `Error_Unknown = 1`
- L12 _public* enumerator_ `Error_Arguments = 2`
- L13 _public* enumerator_ `Error_UnknownCommand = 3`
- L14 _public* enumerator_ `Error_SDKNotFound = 10`
- L15 _public* enumerator_ `Error_ProvisionNotFound = 11`
- L16 _public* enumerator_ `Error_CertificateNotFound = 12`
- L17 _public* enumerator_ `Error_ProvisionAndCertificateNotFound = 13`
- L18 _public* enumerator_ `Error_InfoPListNotFound = 14`
- L19 _public* enumerator_ `Error_KeyNotFoundInPList = 15`
- L20 _public* enumerator_ `Error_ProvisionExpired = 16`
- L21 _public* enumerator_ `Error_CertificateExpired = 17`
- L22 _public* enumerator_ `Error_CertificateProvisionMismatch = 18`
- L23 _public* enumerator_ `Error_CodeUnsupported = 19`
- L24 _public* enumerator_ `Error_PluginsUnsupported = 20`
- L25 _public* enumerator_ `Error_UnknownCookFailure = 25`
- L26 _public* enumerator_ `Error_UnknownDeployFailure = 26`
- L27 _public* enumerator_ `Error_UnknownBuildFailure = 27`
- L28 _public* enumerator_ `Error_UnknownPackageFailure = 28`
- L29 _public* enumerator_ `Error_UnknownLaunchFailure = 29`
- L30 _public* enumerator_ `Error_StageMissingFile = 30`
- L31 _public* enumerator_ `Error_FailedToCreateIPA = 31`
- L32 _public* enumerator_ `Error_FailedToCodeSign = 32`
- L33 _public* enumerator_ `Error_DeviceBackupFailed = 33`
- L34 _public* enumerator_ `Error_AppUninstallFailed = 34`
- L35 _public* enumerator_ `Error_AppInstallFailed = 35`
- L36 _public* enumerator_ `Error_AppNotFound = 36`
- L37 _public* enumerator_ `Error_StubNotSignedCorrectly = 37`
- L38 _public* enumerator_ `Error_IPAMissingInfoPList = 38`
- L39 _public* enumerator_ `Error_DeleteFile = 39`
- L40 _public* enumerator_ `Error_DeleteDirectory = 40`
- L41 _public* enumerator_ `Error_CreateDirectory = 41`
- L42 _public* enumerator_ `Error_CopyFile = 42`
- L43 _public* enumerator_ `Error_OnlyOneObbFileSupported = 50`
- L44 _public* enumerator_ `Error_FailureGettingPackageInfo = 51`
- L45 _public* enumerator_ `Error_OnlyOneTargetConfigurationSupported = 52`
- L46 _public* enumerator_ `Error_ObbNotFound = 53`
- L47 _public* enumerator_ `Error_AndroidBuildToolsPathNotFound = 54`
- L48 _public* enumerator_ `Error_NoApkSuitableForArchitecture = 55`
- L49 _public* enumerator_ `Error_FilesInstallFailed = 56`
- L50 _public* enumerator_ `Error_RemoteCertificatesNotFound = 57`
- L51 _public* enumerator_ `Error_LauncherFailed = 100`
- L52 _public* enumerator_ `Error_UATLaunchFailure = 101`
- L53 _public* enumerator_ `Error_FailedToDeleteStagingDirectory = 102`
- L54 _public* enumerator_ `Error_MissingExecutable = 103`
- L55 _public* enumerator_ `Error_DeviceNotSetupForDevelopment = 150`
- L56 _public* enumerator_ `Error_DeviceOSNewerThanSDK = 151`
- L57 _public* enumerator_ `Error_TestFailure = 152`
- L58 _public* enumerator_ `Error_SymbolizedSONotFound = 153`
- L59 _public* enumerator_ `Error_LicenseNotAccepted = 154`
- L60 _public* enumerator_ `Error_AndroidOBBError = 155`
- L61 _public* enumerator_ `Error_SDKInstallFailed = 200`
- L62 _public* enumerator_ `Error_DeviceUpdateFailed = 201`
- L63 _public* enumerator_ `Error_UBTFailure = 202`

### `Source/Programs/Shared/EpicGames.Build/Automation/FormatCommandLine.cs` (EpicGames.Build)


#### class `UnrealBuildBase.CommandLine`  
`public static partial class CommandLine`  
_public; L9-56_
- L16-28 _public method_ `public static string FormatCommandLine(IEnumerable<string> arguments)` — Converts a list of arguments to a string where each argument is separated with a space character.
- L35-55 _public method_ `public static string FormatArgumentForCommandLine(string argument)` — Format a single argument for passing on the command line, inserting quotes as necessary.

### `Source/Programs/Shared/EpicGames.Build/Automation/ProcessSingleton.cs` (EpicGames.Build)


#### class `UnrealBuildBase.ProcessSingleton`  
`public static class ProcessSingleton`  
_public; L12-95_
- L18 _public property_ `public static bool IsSoleInstance { get; set; }` — Returns true/false based on whether this is the only instance running (checked at startup).
- L26-34 _public method_ `public static async Task<ExitCode> RunSingleInstanceAsync(Func<Task<ExitCode>> main, bool bWaitForUATMutex, ILogger logger)` — Runs the specified delegate checking if this is the only instance of the application.
- L36-82 _private* method_ `static void RunSingleInstanceThread(Func<Task<ExitCode>> main, TaskCompletionSource<ExitCode> result, bool bWaitForUATMutex, ILogger logger)`
- L84-94 _private* method_ `static bool WaitMutexNoExceptions(Mutex mutex, int timeoutMs = 15 * 1000)`

### `Source/Programs/Shared/EpicGames.Build/DotnetProjectInfo.cs` (EpicGames.Build)


#### interface `UnrealBuildBase.IDotnetProjectInfo`  
`public interface IDotnetProjectInfo`  
_public; L17-48_
- L22 _public property_ `public IReadOnlyDictionary<string, string> Properties { get; }` — Evaluated properties from the project file
- L27 _public property_ `public IReadOnlyDictionary<FileReference, bool> References { get; }` — Mapping of referenced assemblies to their 'CopyLocal' (aka 'Private') setting.
- L32 _public property_ `public IReadOnlyDictionary<FileReference, bool> ProjectReferences { get; }` — Mapping of referenced projects to their 'CopyLocal' (aka 'Private') setting.
- L37 _public property_ `public IReadOnlyList<FileReference> CompileReferences { get; }` — List of compile references in the project.
- L42 _public property_ `public IReadOnlyDictionary<FileReference, bool> ContentReferences { get; }` — Mapping of content to if they are flagged Always or Newer
- L47 _public property_ `public FileReference ProjectPath { get; }` — Path to the CSProject file

#### record `UnrealBuildBase.DotnetProjectInfo`  
`public sealed record class DotnetProjectInfo : IDotnetProjectInfo`  
_public; L53-246_
- inherits: `IDotnetProjectInfo`
- desc: Information from a C# project file parsed by MSBuild.
- L55-57 _private ctor_ `private DotnetProjectInfo()`
- L60 _public property_ `public required IReadOnlyDictionary<string, string> Properties { get; init; }` — (inheritdoc)
- L63 _public property_ `public required IReadOnlyDictionary<FileReference, bool> References { get; init; }` — (inheritdoc)
- L66 _public property_ `public required IReadOnlyDictionary<FileReference, bool> ProjectReferences { get; init; }` — (inheritdoc)
- L69 _public property_ `public required IReadOnlyList<FileReference> CompileReferences { get; init; }` — (inheritdoc)
- L72 _public property_ `public required IReadOnlyDictionary<FileReference, bool> ContentReferences { get; init; }` — (inheritdoc)
- L75 _public property_ `public required FileReference ProjectPath { get; init; }` — (inheritdoc)
- L84-92 _public method_ `public static DotnetProjectInfo Read(FileReference file, IReadOnlyDictionary<string, string> globalProperties)` — attrs: `[MethodImpl(MethodImplOptions.NoInlining)]` — Reads project information for the given file.
- L101-116 _public method_ `public static bool TryRead( FileReference file, IReadOnlyDictionary<string, string> globalProperties, [NotNullWhen(true)] out DotnetProjectInfo? outProjectInfo)` — Attempts to read project information for the given file.
- L119-236 _private method_ `private static DotnetProjectInfo ReadImpl(FileReference file, IReadOnlyDictionary<string, string> globalProperties)` — attrs: `[MethodImpl(MethodImplOptions.NoInlining)]`

#### class `UnrealBuildBase.DotnetProjectInfo.MsBuildRegistration`  
`private class MsBuildRegistration : IMsBuildRegistration`  
_private; L238-245_
- inherits: `IMsBuildRegistration`
- L240 _internal field_ `internal static readonly MsBuildRegistration Instance = new()`
- L242 _public property_ `public DirectoryReference DotnetDirectory => ...`
- L244 _public property_ `public FileReference DotnetPath => ...`

#### class `UnrealBuildBase.IDotnetProjectInfoExtensions`  
`public static class IDotnetProjectInfoExtensions`  
_public; L248-519_
- L253-283 _public method_ `public static bool IsDotnetCoreOrDotnet5Plus(this IDotnetProjectInfo self)` — Determines if this project is a .NET Core or .NET 5+ project
- L289-301 _public method_ `public static bool TryGetAssemblyName(this IDotnetProjectInfo self, [NotNullWhen(true)] out string? assemblyName)` — Returns the assembly name used by this project
- L309-342 _public method_ `public static void FindCompiledBuildProducts(this IDotnetProjectInfo self, DirectoryReference outputDir, HashSet<FileReference> buildProducts)` — Determines all the compiled build products (executable, etc...) directly built from this project.
- L350-369 _public method_ `public static bool TryGetOutputDir(this IDotnetProjectInfo self, [NotNullWhen(true)] out DirectoryReference? outputDir)` — Resolve the project's output directory
- L377-395 _public method_ `public static bool TryGetOutputFile(this IDotnetProjectInfo self, [NotNullWhen(true)] out FileReference? file)` — Get the ouptut file for this project
- L403-421 _public method_ `public static DirectoryReference GetOutputDir(this IDotnetProjectInfo self, DirectoryReference baseDirectory)` — Resolve the project's output directory
- L429-444 _public method_ `public static void AddReferencedAssemblyAndSupportFiles(this IDotnetProjectInfo self, FileReference outputFile, HashSet<FileReference> outputFiles)` — Adds the given file and any additional build products to the output set
- L453-484 _public method_ `public static void FindBuildProducts( this IDotnetProjectInfo self, DirectoryReference outputDir, HashSet<FileReference> buildProducts, Dictionary<FileReference, IDotnetProjectInfo> projectFileToInfo)` — Finds all build products from this project. This includes content and other assemblies marked to be copied local.
- L493-518 _private method_ `private static void FindCopiedContent( this IDotnetProjectInfo self, DirectoryReference outputDir, HashSet<FileReference> outputFiles, Dictionary<FileReference, IDotnetProjectInfo> projectFileToInfo)` — Finds all content which will be copied into the output directory for this project. This includes content from any project references as "copy local" recursively (though MSBuild only traverses a single reference for actual binaries, in such cases)

### `Source/Programs/Shared/EpicGames.Build/Exceptions/BuildException.cs` (EpicGames.Build)


#### class `UnrealBuildTool.BuildException`  
`public class BuildException : Exception`  
_public; L16-76_
- attrs: `[SuppressMessage("Naming", "CA1724:Type names should not match namespaces", Justification = "Renaming would break public api")]`
- inherits: `Exception`
- desc: Base class for exceptions thrown by UnrealBuildTool and AutomationTool
- L22-25 _public ctor_ `public BuildException(string Message) : base(Message)` — Constructor
- L32-35 _public ctor_ `public BuildException(Exception? InnerException, string Message) : base(Message, InnerException)` — Constructor which wraps another exception
- L42-45 _public ctor_ `public BuildException(string Format, params object?[] Arguments) : base(String.Format(Format, Arguments))` — Constructor
- L53-56 _public ctor_ `public BuildException(Exception InnerException, string Format, params object?[] Arguments) : base(String.Format(Format, Arguments), InnerException)` — Constructor which wraps another exception
- L62-66 _public method_ `public virtual void LogException(ILogger Logger)` — Log BuildException with a provided ILogger
- L72-75 _public method_ `public override string ToString()` — Returns the string representing the exception. Our build exceptions do not show the callstack since they are used to report known error conditions.

### `Source/Programs/Shared/EpicGames.Build/Exceptions/BuildExceptionExtensions.cs` (EpicGames.Build)


#### class `UnrealBuildBase.BuildExceptionExtensions`  
`public static class BuildExceptionExtensions`  
_public; L13-76_
- desc: Extension methods for build exceptions
- L20-46 _public method_ `public static void LogException(this Exception ex, ILogger logger)` — Log Exception with a provided ILogger
- L53-75 _public method_ `public static CompilationResult GetCompilationResult(this Exception ex)` — Get the CompilationResult for a provided Exception

### `Source/Programs/Shared/EpicGames.Build/Exceptions/BuildLogEventException.cs` (EpicGames.Build)


#### class `UnrealBuildBase.BuildLogEventException`  
`public class BuildLogEventException(Exception? InnerException, LogEvent Event) : UnrealBuildTool.BuildException(InnerException, Event.ToString())`  
_public; L14-60_
- desc: Implementation of UnrealBuildTool.BuildException that captures a full structured logging event.
- L19 _public property_ `public LogEvent Event { get; }` — The event object
- L25-28 _public ctor_ `public BuildLogEventException(LogEvent Event) : this(null, Event)` — Constructor
- L31-34 _public ctor_ `public BuildLogEventException(string Format, params object[] Arguments) : this(LogEvent.Create(LogLevel.Error, Format, Arguments))` — (inheritdoc)
- L37-40 _public ctor_ `public BuildLogEventException(Exception? InnerException, string Format, params object[] Arguments) : this(InnerException, LogEvent.Create(LogLevel.Error, default, InnerException, Format, Arguments))` — (inheritdoc)
- L49-52 _public ctor_ `public BuildLogEventException(Exception? InnerException, EventId EventId, string Format, params object[] Arguments) : this(InnerException, LogEvent.Create(LogLevel.Error, EventId, InnerException, Format, Arguments))` — Constructor which wraps another exception
- L55-59 _public method_ `public override void LogException(ILogger Logger)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Build/Exceptions/CompilationResultException.cs` (EpicGames.Build)


#### class `UnrealBuildBase.CompilationResultException`  
`public class CompilationResultException : BuildLogEventException`  
_public; L12-116_
- inherits: `BuildLogEventException`
- desc: Implementation of BuildLogEventException that will return a unique exit code.
- L17 _public property_ `public CompilationResult Result { get; }` — The exit code associated with this exception
- L19 _private* field_ `readonly bool HasMessage = true`
- L25-30 _public ctor_ `public CompilationResultException(CompilationResult Result) : base(LogEvent.Create(LogLevel.Error, "{CompilationResult}", Result))` — Constructor
- L37-41 _public ctor_ `public CompilationResultException(CompilationResult Result, LogEvent Event) : base(Event)` — Constructor
- L49-53 _public ctor_ `public CompilationResultException(CompilationResult Result, Exception? InnerException, LogEvent Event) : base(InnerException, Event)` — Constructor which wraps another exception
- L62-66 _public ctor_ `public CompilationResultException(CompilationResult Result, EventId EventId, string Format, params object[] Arguments) : base(LogEvent.Create(LogLevel.Error, EventId, Format, Arguments))` — Constructor
- L74-78 _public ctor_ `public CompilationResultException(CompilationResult Result, string Format, params object[] Arguments) : base(LogEvent.Create(LogLevel.Error, Format, Arguments))` — Constructor
- L87-91 _public ctor_ `public CompilationResultException(CompilationResult Result, Exception? InnerException, string Format, params object[] Arguments) : base(InnerException, LogEvent.Create(LogLevel.Error, default, InnerException, Format, Arguments))` — Constructor which wraps another exception
- L101-105 _public ctor_ `public CompilationResultException(CompilationResult Result, Exception? InnerException, EventId EventId, string Format, params object[] Arguments) : base(InnerException, LogEvent.Create(LogLevel.Error, EventId, InnerException, Format, Arguments))` — Constructor which wraps another exception
- L108-115 _public method_ `public override void LogException(ILogger Logger)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Build/Platform/SDKCollection.cs` (EpicGames.Build)


#### class `EpicGames.Core.SDKCollection`  
`public class SDKCollection(UEBuildPlatformSDK inPlatformSDK)`  
_public; L9-134_
- L11 _public property_ `public virtual string DefaultName => ...`
- L12-15 _public method_ `public virtual bool IsValid(string version, SDKDescriptor info)`
- L17 _public property_ `public UEBuildPlatformSDK PlatformSDK { get; init; }`
- L18 _public property_ `public List<SDKDescriptor> Sdks { get; init; }`
- L19 _public property_ `public List<SDKDescriptor> FullSdks => ...`
- L20 _public property_ `public SDKDescriptor? AutoSdk => ...`
- L22-29 _public ctor_ `public SDKCollection(SDKCollection other, UEBuildPlatformSDK platformSDK) : this(platformSDK)`
- L32-36 _public ctor_ `public SDKCollection(string? min, string? max, UEBuildPlatformSDK platformSDK) : this(platformSDK)`
- L39-46 _public ctor_ `public SDKCollection(string? current, UEBuildPlatformSDK platformSDK) : this(platformSDK)`
- L48-70 _public method_ `public bool AreAllManualSDKsValid()`
- L72-75 _public method_ `public bool IsAutoSDKValid()`
- L77-81 _public method_ `public string ToString(bool bIncludeCurrent = true)`
- L83-90 _public method_ `public string ToString(string descriptor, string? currentDescriptor = null)`
- L92-95 _public method_ `public static string ToMultilineString(bool bIncludeCurrent = true)`
- L97-100 _public method_ `public void SetupSDK(string name, string? min, string? max, string? current, string? groupName)`
- L102-105 _public method_ `public void SetupCurrent(string name, string current)`
- L107-133 _public method_ `public bool UpdateCurrentForSingle(string name, string currentVersion)`

### `Source/Programs/Shared/EpicGames.Build/Platform/SDKDescriptor.cs` (EpicGames.Build)


#### class `EpicGames.Core.SDKDescriptor`  
`public class SDKDescriptor`  
_public; L11-94_
- desc: Range of SDK versions that are valid for a platform
- L13 _public property_ `public required string Name { get; init; }`
- L14 _public property_ `public required string? Min { get; init; }`
- L15 _public property_ `public required string? Max { get; init; }`
- L16 _public property_ `public required string? Current { get; set; }`
- L20 _public property_ `public required string? GroupName { get; init; }`
- L22 _public property_ `public ulong MinInt { get; init; }`
- L23 _public property_ `public ulong MaxInt { get; init; }`
- L24 _public property_ `public ulong CurrentInt { get; set; }`
- L26 _public property_ `public SDKStatus Validity { get; set; }`
- L29-45 _public ctor_ `public SDKDescriptor(string inName, string? inMin, string? inMax, string? inCurrent, string? inGroupName, SDKCollection? collection)` — attrs: `[SetsRequiredMembers]`
- L48-51 _public ctor_ `public SDKDescriptor(string inName, string? inMin, string? inMax) : this(inName, inMin, inMax, null, null, null)` — attrs: `[SetsRequiredMembers]`
- L54-57 _public ctor_ `public SDKDescriptor(string inName, string? inCurrent) : this(inName, null, null, inCurrent, null, null)` — attrs: `[SetsRequiredMembers]`
- L59-67 _public method_ `public void UpdateCurrent(string inCurrent, string? hint, SDKCollection? collection)`
- L69-74 _private method_ `private void UpdateValidity(SDKCollection collection)`
- L76-79 _public method_ `public string ToString(bool bIncludeCurrent = true)`
- L80-93 _public method_ `public string ToString(string descriptor, string? currentDescriptor, bool bIncludeName)`

### `Source/Programs/Shared/EpicGames.Build/Platform/SDKStatus.cs` (EpicGames.Build)


#### enum `EpicGames.Core.SDKStatus`  
`public enum SDKStatus`  
_public; L8-19_
- desc: SDK installation status
- L13 _public* enumerator_ `Valid` — Desired SDK is installed and set up.
- L18 _public* enumerator_ `Invalid` — Could not find the desired SDK, SDK setup failed, etc.

### `Source/Programs/Shared/EpicGames.Build/Platform/SoftwareCollection.cs` (EpicGames.Build)


#### class `EpicGames.Core.SoftwareCollection`  
`public class SoftwareCollection : SDKCollection`  
_public; L5-26_
- inherits: `SDKCollection`
- L7-10 _public ctor_ `public SoftwareCollection(UEBuildPlatformSDK platformSDK) : base(platformSDK)`
- L11-14 _public ctor_ `public SoftwareCollection(string? min, string? max, UEBuildPlatformSDK platformSDK) : base(min, max, platformSDK)`
- L15-18 _public ctor_ `public SoftwareCollection(string? current, UEBuildPlatformSDK platformSDK) : base(current, platformSDK)`
- L20 _public property_ `public override string DefaultName => ...`
- L22-25 _public method_ `public override bool IsValid(string version, SDKDescriptor info)`

### `Source/Programs/Shared/EpicGames.Build/Platform/UEBuildPlatformSDK.cs` (EpicGames.Build)


#### class `EpicGames.Core.UEBuildPlatformSDK`  
`public abstract class UEBuildPlatformSDK(ILogger inLogger)`  
_public; L19-2044_
- desc: SDK for a platform
- L23 _protected field_ `protected readonly ILogger Logger = inLogger`
- L25 _protected field_ `protected readonly HashSet<FileReference> LoadedConfigFiles = []`
- L35-46 _public method_ `public static void RegisterSDKForPlatform(UEBuildPlatformSDK sdk, string platformName, bool bIsSdkAllowedOnHost)` — Registers the SDK for a given platform (as a string, but equivalent to UnrealTargetPlatform)
- L48-97 _private method_ `private void Init(string inPlatformName, bool bInIsSdkAllowedOnHost)`
- L108-114 _public method_ `public static UEBuildPlatformSDK? GetSDKForPlatform(string platformName)` — Retrieves a previously registered SDK for a given platform
- L116-136 _public method_ `public static T? GetSDKForPlatformOrMakeTemp<T>(string platformName) where T : UEBuildPlatformSDK`
- L141 _public property_ `public static UEBuildPlatformSDK[] AllPlatformSDKObjects => ...` — Gets the set of all known SDKs
- L144 _public field_ `public static bool bHasAnySDKOverride = false`
- L147 _public field_ `public bool bHasSDKOverride = false`
- L150 _public field_ `public List<FileReference> ProjectsThatOverrodeSDK = []`
- L153 _public field_ `public string? PlatformName`
- L156 _public field_ `public bool bIsSdkAllowedOnHost`
- L159 _public property_ `public IEnumerable<FileItem> ExternalDependencies => ...`
- L161-190 _public method_ `public SDKCollection GetAllSDKInfo()`
- L192-195 _public method_ `public SDKDescriptor? GetSDKInfo(string sdkName)`
- L197-202 _public method_ `public SDKDescriptor? GetSoftwareInfo(string? sdkName = null)`
- L204-228 _public method_ `public SDKCollection GetAllSoftwareInfo(string? deviceType = null, string? current = null)`
- L235-239 _public method_ `public string? GetInstalledVersion(out bool bIsAutoSDK)`
- L241-244 _public method_ `public string? GetInstalledVersion()`
- L246-249 _public method_ `public string? GetInstalledVersion(string sdkName)`
- L271 _public method_ `public virtual bool IsVersionValid(string? version, string sdkType)`
- L273 _public method_ `public virtual bool IsVersionValid(string? version, SDKDescriptor info)`
- L275 _public method_ `public virtual bool IsSoftwareVersionValid(string version, string deviceType)`
- L277 _public method_ `public virtual bool IsSoftwareVersionValid(string version, SDKDescriptor info)`
- L279-283 _public method_ `public void ReactivateAutoSDK()`
- L289 _protected property_ `protected virtual string MainVersionKey => ...`
- L290 _protected property_ `protected virtual string MinVersionKey => ...`
- L291 _protected property_ `protected virtual string MaxVersionKey => ...`
- L293 _protected property_ `protected virtual string BannedSdkVersionsKey => ...`
- L299-303 _public method_ `public virtual string GetMainVersion()` — Return the SDK version that the platform wants to use (AutoSDK dir must match this, full SDKs can be in a valid range)
- L310-315 _protected method_ `protected virtual void GetValidVersionRange(out string? minVersion, out string? maxVersion)` — Gets the valid string range of Sdk versions. TryConvertVersionToInt() will need to succeed to make this usable for range checks
- L317-322 _protected method_ `protected virtual SDKCollection GetValidVersions()`
- L329-333 _protected method_ `protected virtual void GetValidSoftwareVersionRange(out string? minVersion, out string? maxVersion)` — Gets the valid string range of software/flash versions. TryConvertVersionToInt() will need to succeed to make this usable for range checks
- L335-340 _protected method_ `protected virtual SoftwareCollection GetValidSoftwareVersions()`
- L346-353 _protected method_ `protected virtual string? GetInstalledSDKVersion()` — Returns the installed SDK version, used to determine if up to date or not (
- L355-369 _protected method_ `protected virtual SDKCollection GetInstalledSDKVersions()`
- L376-379 _public method_ `public virtual string GetPlatformSpecificVersion(string versionType)` — Returns a platform-specific version string that can be retrieved from anywhere without needing to typecast the SDK object
- L385-388 _public method_ `public virtual string[] GetAllInstalledSDKVersions()` — Return a list of full SDK versions that are already installed and can be quickly switched to without running any installers.
- L394-442 _protected method_ `protected virtual string? FindBestInstalledSDKVersion()` — Find the highest valid manually-installed SDK, prioritizing the main version if it's available. Requires that the platform SDK implements GetAllInstalledSDKVersions
- L450-453 _public method_ `public virtual bool SwitchToAlternateSDK(string version, bool bSwitchForThisProcessOnly)` — Switch to another version of the SDK than what GetInstalledSDKVersion() returns. This will be one of the versions returned from GetAllInstalledSDKVersions()
- L460 _public property_ `public virtual bool ManualSDKAutoSwitchRequiresAutoSDK => ...` — Whether the automatic switching to a locally-installed manual SDK requires AutoSDK to be configured This is typically true unless the editor-side binaries do not depend on a version-specific SDK environment variable or path i.e. the SDK version is compiled into the binary and can be used directly.
- L466-472 _protected method_ `protected virtual bool TryGetEnvironmentForManualSDK(string selectedSDKVersion, out Dictionary<string, string>? envVarValues, out List<string>? pathAdds, out List<string>? pathRemoves)` — Allows a platform to switch a different version of a manually-installed SDK, if the platform supports side-by-side installations of different versions
- L480-484 _public method_ `public virtual string GetAutoSDKDirectoryForMainVersion()` — For a platform that doesn't use properly named AutoSDK directories, the directory name may not be convertible to an integer, and IsVersionValid checks could fail when checking AutoSDK version for an exact match. GetMainVersion() would return the proper, integer-convertible version number of the SDK inside of the directory returned by GetAutoSDKDirectoryForMainVersion()
- L520-558 _protected method_ `protected virtual bool IsVersionValidInternal(string? version, string? sdkType, SDKDescriptor? versionInfo)`
- L560-585 _protected method_ `protected virtual bool IsSoftwareVersionValidInternal(string? version, string? deviceType, SDKDescriptor? versionInfo)`
- L594 _public method_ `public abstract bool TryConvertVersionToInt(string? stringValue, out ulong outValue, string? hint = null)` — Only the platform can convert a version string into an integer that is usable for comparison
- L602-616 _public method_ `public ulong ConvertVersionToInt(string? stringValue, string? hint = null)` — Like TryConvertVersionToInt, but will throw an exception on failure
- L626-642 _public method_ `public int SdkVersionsCompare(string? stringValueA, string? stringValueB, string? hint = null)` — Compare two sdk versions, for Sort() purposes e.g. SdkVersions.Sort( (A,B) => PlatformSDK.SdkVersionsCompare(A,B) );
- L648-651 _public method_ `public virtual string GetAutoSDKPlatformName()` — Allow the platform SDK to override the name it will use in AutoSDK, but default to the platform name
- L657 _private field_ `private static List<FileReference> ProjectsToCheckForSDKOverrides = []`
- L658-661 _public method_ `public static void InitializePerProjectSDKVersions(IEnumerable<FileReference> projectsToCheckForOverrides)`
- L666 _private field_ `private static bool bHasShownTurnkey = false`
- L667 _private field_ `private SDKStatus? SDKInfoValidity = null`
- L668 _public field_ `public static bool bSuppressSDKWarnings = false`
- L670-744 _public method_ `public virtual SDKStatus PrintSDKInfoAndReturnValidity(LogEventType verbosity = LogEventType.Console, LogFormatOptions options = LogFormatOptions.None, LogEventType errorVerbosity = LogEventType.Error, LogFormatOptions errorOptions = LogFormatOptions.None, bool bBriefInvalidSDKWarnings = false)`
- L751 _protected field_ `protected Dictionary<string, string> CachedManualSDKVersions = ...`
- L751 _protected field_ `protected Dictionary< CachedManualSDKVersions = []`
- L752 _private field_ `private static Dictionary<string, UEBuildPlatformSDK> SDKRegistry = ...`
- L752 _private field_ `private static Dictionary< SDKRegistry = []`
- L756 _private field_ `private static Dictionary<string, UEBuildPlatformSDK> TempSDKRegistry = ...`
- L756 _private field_ `private static Dictionary< TempSDKRegistry = []`
- L758-778 _private method_ `private static SDKDescriptor? GetSDKVersionForHint(SDKCollection collection, string? hint)`
- L781 _private field_ `private Dictionary<string, string> ConfigSDKVersions = ...`
- L781 _private field_ `private Dictionary< ConfigSDKVersions = new(StringComparer.OrdinalIgnoreCase)`
- L782 _private field_ `private Dictionary<string, string[]> ConfigSDKVersionArrays = ...`
- L782 _private field_ `private Dictionary< ConfigSDKVersionArrays = new(StringComparer.OrdinalIgnoreCase)`
- L784-861 _private method_ `private void LoadJsonFile(string platform)`
- L863-900 _private method_ `private void ProcessJsonFile(FileReference sdkConfigFile, Dictionary<string, string> versionMap, Dictionary<string, string[]> versionArrayMap)`
- L902-914 _private method_ `private static string GetHostSpecificVersionName(string versionName)`
- L915-919 _public method_ `public string GetRequiredVersionFromConfig(string versionName)`
- L921-935 _public method_ `public string? GetVersionFromConfig(string versionName, bool bIsRequired = false)`
- L937-941 _protected method_ `protected VersionNumber GetRequiredVersionNumberFromConfig(string versionName)`
- L943-953 _public method_ `public VersionNumber? GetVersionNumberFromConfig(string versionName, bool bIsRequired = false)`
- L955-964 _private method_ `private static VersionNumberRange? ParseVersionNumberRange(string range)`
- L966-970 _public method_ `public VersionNumberRange? GetRequiredVersionNumberRangeFromConfig(string versionName, bool bIsRequired = false)`
- L972-990 _public method_ `public VersionNumberRange? GetVersionNumberRangeFromConfig(string versionName, bool bIsRequired = false)`
- L992-1009 _public method_ `public VersionNumberRange[] GetVersionNumberRangeArrayFromConfig(string versionName)`
- L1011-1020 _public method_ `public string[] GetStringArrayFromConfig(string name)`
- L1031 _protected const_ `protected const string CurrentlyInstalledSDKStringManifest = "CurrentlyInstalled.txt"` — Name of the file that holds currently install SDK version string
- L1036 _protected const_ `protected const string LastRunScriptVersionManifest = "CurrentlyInstalled.Version.txt"` — name of the file that holds the last succesfully run SDK setup script version
- L1041 _private const_ `private const string ScriptVersionFilename = "Version.txt"` — Filename of the script version file in each AutoSDK directory. Changing the contents of this file will force reinstallation of an AutoSDK.
- L1046 _protected const_ `protected const string SDKEnvironmentVarsFile = "OutputEnvVars.txt"` — Name of the file that holds environment variables of current SDK
- L1048 _protected const_ `protected const string ManualSDKEnvironmentVarsFile = "ManualSDKEnvVars.txt"`
- L1050 _protected const_ `protected const string SDKRootEnvVar = "UE_SDKS_ROOT"`
- L1052 _protected const_ `protected const string AutoSetupEnvVar = "AutoSDKSetup"`
- L1053 _protected const_ `protected const string ManualSetupEnvVar = "ManualSDKSetup"`
- L1055-1070 _private method_ `private static string GetAutoSDKHostPlatform()`
- L1076-1079 _protected method_ `protected virtual bool PlatformSupportsAutoSDKs()` — Whether platform supports switching SDKs during runtime
- L1081 _private field_ `private static bool bCheckedAutoSDKRootEnvVar = false`
- L1082 _private field_ `private static bool bAutoSDKSystemEnabled = false`
- L1083-1095 _private method_ `private static bool HasAutoSDKSystemEnabled()`
- L1098-1101 _protected method_ `protected bool IsAutoSDKSafe()`
- L1108-1116 _private method_ `private string GetRequiredScriptVersionString()` — Gets the version number of the SDK setup script itself. The version in the base should ALWAYS be the primary revision from the last refactor. If you need to force a rebuild for a given platform, modify the version file.
- L1122-1134 _protected method_ `protected string GetPathToPlatformAutoSDKs()` — Returns path to platform SDKs
- L1140-1153 _public method_ `public static bool TryGetHostPlatformAutoSDKDir([NotNullWhen(true)] out DirectoryReference? outPlatformDir)` — Returns path to platform SDKs
- L1161-1164 _protected method_ `protected string GetPlatformAutoSDKSetupEnvVar()` — Because most ManualSDK determination depends on reading env vars, if this process is spawned by a process that ALREADY set up AutoSDKs then all the SDK env vars will exist, and we will spuriously detect a Manual SDK. (children inherit the environment of the parent process). Therefore we write out an env variable to set in the command file (OutputEnvVars.txt) such that child processes can determine if their manual SDK detection is bogus. Make it platform specific so that platforms can be in different states.
- L1165-1168 _protected method_ `protected string GetPlatformManualSDKSetupEnvVar()`
- L1177-1211 _protected method_ `protected static bool GetCurrentlyInstalledSDKString(string platformSDKRoot, out string outInstalledSDKVersionString, out string outInstalledSDKLevel)` — Gets currently installed version
- L1219-1240 _protected method_ `protected static bool GetLastRunScriptVersionString(string platformSDKRoot, out string outLastRunScriptVersion)` — Gets the version of the last successfully run setup script.
- L1248-1269 _protected method_ `protected bool SetCurrentlyInstalledAutoSDKString(string installedSDKVersionString, string installedSDKLevelString)` — Sets currently installed version
- L1271-1303 _protected method_ `protected void SetupManualSDK()`
- L1305-1312 _public method_ `public static void ClearManualSDKEnvVarCache()`
- L1314-1396 _private method_ `private bool TrySelectBestManualSDK(out string? selectedSDKVersion)`
- L1398-1416 _protected method_ `protected bool SetLastRunAutoSDKScriptVersion(string lastRunScriptVersion)`
- L1423-1428 _protected method_ `protected virtual string GetHookExecutableName(SDKHookType hook)` — Returns Hook names as needed by the platform (e.g. can be overridden with custom executables or scripts)
- L1435-1438 _protected method_ `protected virtual bool DoesHookRequireAdmin(SDKHookType hook)` — Whether the hook must be run with administrator privileges.
- L1440-1447 _private method_ `private void LogAutoSDKHook(object sender, DataReceivedEventArgs args)`
- L1449 _private field_ `private static string[] AutoSDKLevels = [ "NONE", "BUILD", "PACKAGE", "RUN", "FULL", ]`
- L1458-1467 _private method_ `private static bool IsSDKLevelAtLeast(string value, string comparedTo)`
- L1469-1505 _private method_ `private static string GetAutoSDKLevelForPlatform(string platformSDKRoot)`
- L1516-1595 _protected method_ `protected virtual bool RunAutoSDKHooks(string platformSDKRoot, string sdkVersionString, string autoSDKLevel, SDKHookType hook, bool bHookCanBeNonExistent = true)` — Runs install/uninstall hooks for SDK
- L1604-1752 _protected method_ `protected bool SetupEnvironmentFromAutoSDK(string platformSDKRoot)` — Loads environment variables from SDK If any commands are added or removed the handling needs to be duplicated in TargetPlatformManagerModule.cpp
- L1754-1777 _protected method_ `protected void InvalidateCurrentlyInstalledAutoSDK()`
- L1783-1821 _public method_ `public SDKStatus HasRequiredAutoSDKInstalled()` — Currently installed AutoSDK is written out to a text file in a known location. This function just compares the file's contents with the current requirements.
- L1824 _private field_ `private int SDKCheckStatus = -1`
- L1827 _private field_ `private bool bLocalProcessSetupAutoSDK = false`
- L1829-1832 _protected method_ `protected bool HasSetupAutoSDK()`
- L1834-1844 _protected method_ `protected bool HasParentProcessSetupAutoSDK([NotNullWhen(true)] out string? outAutoSDKSetupValue)`
- L1846-1855 _public method_ `public SDKStatus HasRequiredManualSDK()`
- L1858-1861 _protected method_ `protected virtual bool HasAnyManualInstall()`
- L1864-1871 _protected method_ `protected virtual SDKStatus HasRequiredManualSDKInternal()`
- L1874-1877 _protected method_ `protected virtual bool AllowInvalidManualInstall()`
- L1880-1883 _protected method_ `protected virtual bool PreferAutoSDK()`
- L1888-1891 _protected method_ `protected virtual bool IsAutoSDKDestructive()`
- L1898-1952 _private method_ `private void SetupAutoSDK()` — Runs batch files if necessary to set up required AutoSDK. AutoSDKs are SDKs that have not been setup through a formal installer, but rather come from a source control directory, or other local copy.
- L1958-1961 _public method_ `public virtual string? GetInternalSDKPath()` — Allows the platform to optionally returns a path to the internal SDK
- L1977 _public field_ `public static bool bAllowAutoSDKSwitching = true`
- L1979-1991 _public method_ `public SDKStatus SetupEnvironmentFromAutoSDK()`
- L1997-2009 _public method_ `public SDKStatus HasRequiredSDKsInstalled()` — Whether the required external SDKs are installed for this platform. Could be either a manual install or an AutoSDK.
- L2012-2041 _public method_ `public void ManageAndValidateSDK()`

#### enum `EpicGames.Core.UEBuildPlatformSDK.SDKHookType`  
`public enum SDKHookType`  
_public; L1970-1974_
- desc: Enum describing types of hooks a platform SDK can have
- L1972 _public* enumerator_ `Install`
- L1973 _public* enumerator_ `Uninstall`

### `Source/Programs/Shared/EpicGames.Build/System/AppDomainExtensions.cs` (EpicGames.Build)


#### class `UnrealBuildBase.AppDomainExtensions`  
`public static class AppDomainExtensions`  
_public; L13-54_
- desc: Extensions to AppDomain
- L22-53 _public method_ `public static IEnumerable<Type> EnumerateSubclasses(this AppDomain domain, Type baseClass)` — Using reflection to find all subclasses for a class. Will check which assembly that class is in, then traverse that assmbly plus all assemblies depending on that assembly to find the base classes. This is much more efficient than parsing all loaded assemblies to find subclasses

### `Source/Programs/Shared/EpicGames.Build/System/AssemblyExtensions.cs` (EpicGames.Build)


#### class `UnrealBuildBase.AssemblyExtensions`  
`public static class AssemblyExtensions`  
_public; L12-30_
- desc: Extensions to Assembly
- L19-29 _public method_ `public static Type[] SafeGetLoadedTypes(this Assembly assembly)` — Safely get all loaded types from an assembly.

### `Source/Programs/Shared/EpicGames.Build/System/BloomFilter.cs` (EpicGames.Build)


#### class `UnrealBuildBase.BloomFilter`  
`public sealed class BloomFilter`  
_public; L12-74_
- desc: Simple bloom filter implementation which can be used to optimize searches by early out on
- L14 _private* const_ `const uint ByteCount = 128`
- L15 _private field_ `private readonly byte[] _bits = new byte[ByteCount]`
- L21-28 _public method_ `public void Add(ReadOnlySpan<char> s)` — Add string to filter
- L34-40 _public method_ `public void AddRange(IEnumerable<string> strings)` — Add multiple strings to filter
- L46-53 _public method_ `public bool MightContain(ReadOnlySpan<char> s)` — Will return false if string is guaranteed to not exist, and true if it could exist
- L61-73 _public method_ `public bool MightContainSubString(ReadOnlySpan<char> span, char separator)` — Will traverse a string to find substrings separated with separator and then test them Useful if you for example want to check if a a string might exist somewhere in a path

### `Source/Programs/Shared/EpicGames.Build/System/CompileScriptModules.cs` (EpicGames.Build)


#### class `UnrealBuildBase.CompileScriptModule`  
`public static class CompileScriptModule`  
_public; L19-695_
- L120-123 _public method_ `public static HashSet<FileReference> GetTargetPaths(IReadOnlyDictionary<FileReference, CsProjBuildRecordEntry> BuildRecords)` — Return the target paths from the collection of build records
- L130-133 _public method_ `public static FileReference GetTargetPath(KeyValuePair<FileReference, CsProjBuildRecordEntry> BuildRecord)` — Return the target path for the given build record
- L148-249 _public method_ `public static HashSet<FileReference> InitializeScriptModules(Rules.RulesFileType RulesFileType, string? ScriptsForProjectFileName, List<string>? AdditionalScriptsFolders, List<string>? AutomationProjectIncludeFilter, bool bForceCompile, bool bNoCompile, bool bUseBuildRecords, out bool bBuildSuccess, ILogger Logger)` — Locates script modules, builds them if necessary, returns set of .dll files
- L259-273 _public method_ `public static bool AreScriptModulesUpToDate(Rules.RulesFileType RulesFileType, HashSet<FileReference> FoundProjects, List<DirectoryReference> BaseDirectories, ILogger Logger)` — Test to see if all the given projects are up-to-date
- L286-393 _public method_ `public static Dictionary<FileReference, CsProjBuildRecordEntry> Build(Rules.RulesFileType RulesFileType, HashSet<FileReference> FoundProjects, IEnumerable<DirectoryReference> BaseDirectories, IReadOnlyDictionary<string, IEnumerable<string>>? CustomGlobalProperties, BuildFlags BuildFlags, out bool bBuildSuccess, ILogger Logger)` — Locates script modules, builds them if necessary, returns set of .dll files
- L401-406 _private* method_ `static Dictionary<FileReference, CsProjBuildRecordEntry> Build(HashSet<FileReference> FoundProjects, bool bForceCompile, out bool bBuildSuccess, CsProjBuildHook Hook, IEnumerable<DirectoryReference> BaseDirectories, IReadOnlyDictionary<string, IEnumerable<string>>? CustomGlobalProperties, ILogger Logger)` — attrs: `[MethodImpl(MethodImplOptions.NoInlining)]` — This method exists purely to prevent EpicGames.MsBuild from being loaded until the absolute last moment. If it is placed in the caller directly, then when the caller is invoked, the assembly will be loaded resulting in the possible Microsoft.Build.Framework load issue later on is this method isn't invoked.
- L415-460 _private* method_ `static Dictionary<FileReference, CsProjBuildRecordEntry> LoadExistingBuildRecords(CsProjBuildHook Hook, IEnumerable<DirectoryReference> BaseDirectories, ILogger Logger)` — Find and load existing build record .json files from any Intermediate/ScriptModules found in the provided lists
- L462-519 _private method_ `private static bool ValidateGlobbedFiles(DirectoryReference ProjectDirectory, List<CsProjBuildRecord.Glob> Globs, HashSet<string> Dependencies, out string ValidationFailureMessage)`
- L521-582 _private method_ `private static bool ValidateBuildRecord(CsProjBuildRecord BuildRecord, DirectoryReference ProjectDirectory, out string ValidationFailureMessage, CsProjBuildHook Hook)`
- L584-670 _private* method_ `static void ValidateBuildRecordRecursively( Dictionary<FileReference, CsProjBuildRecordEntry> BuildRecords, FileReference ProjectPath, CsProjBuildHook Hook, ILogger Logger)`
- L672-687 _private* method_ `static List<DirectoryReference> GetGameDirectories(string? ScriptsForProjectFileName, ILogger Logger)`
- L689 _private* method_ `static List<DirectoryReference> GetAdditionalDirectories(List<string>? AdditionalScriptsFolders)`
- L693 _private* method_ `static List<DirectoryReference> GetAdditionalBuildDirectories(List<DirectoryReference> GameDirectories)`

#### enum `UnrealBuildBase.CompileScriptModule.BuildFlags`  
`public enum BuildFlags`  
_public; L22-55_
- attrs: `[Flags]`
- L27 _public* enumerator_ `None = 0` — No build flags specified
- L32 _public* enumerator_ `NoCompile = 1 << 0` — Do not allow compiles of any projects
- L37 _public* enumerator_ `ErrorOnMissingTarget = 1 << 1` — If not compiling, generate error if target does not exist
- L48 _public* enumerator_ `UseBuildRecords = 1 << 2` — When NoCompile options are specified, this flag will test to see if the build records are valid. But the results of that test are currently ignored. Only the existence of the target path is considered. When NoCompile options are not specified, then the validity of the build records will be used to test to see if project files need building. If ForceCompile is specified, then this flag serves no useful purpose. If this flag is not specified, then ForceCompile is assumed.
- L54 _public* enumerator_ `ForceCompile = 1 << 3` — Force compile when the NoCompile options aren't specified regardless of the state of the build records.

#### class `UnrealBuildBase.CompileScriptModule.Hook`  
`class Hook : CsProjBuildHook`  
_private*; L57-113_
- inherits: `CsProjBuildHook`
- L59 _private field_ `private ILogger Logger`
- L60 _private field_ `private ConcurrentDictionary<string, DateTime> WriteTimes = ...`
- L60 _private field_ `private ConcurrentDictionary< WriteTimes = []`
- L61 _private field_ `private string BuildRecordDirectory`
- L62 _private field_ `private Dictionary<FileReference, CsProjBuildRecordEntry> ValidBuildRecords = ...`
- L62 _private field_ `private Dictionary< ValidBuildRecords = []`
- L64-78 _public ctor_ `public Hook(ILogger InLogger, Rules.RulesFileType InRulesFileType)`
- L80-83 _public method_ `public DateTime GetLastWriteTime(DirectoryReference BasePath, string RelativeFilePath)`
- L85-89 _public method_ `public DateTime GetLastWriteTime(string BasePath, string RelativeFilePath)`
- L91-94 _public method_ `public DirectoryReference GetBuildRecordDirectory(DirectoryReference BasePath)`
- L96-99 _public method_ `public void ValidateRecursively(Dictionary<FileReference, CsProjBuildRecordEntry> BuildRecords, FileReference ProjectPath)`
- L101-104 _public method_ `public void SetValidBuildRecords(IReadOnlyDictionary<FileReference, CsProjBuildRecordEntry> Records)`
- L106 _private* property_ `IReadOnlyDictionary<FileReference, CsProjBuildRecordEntry> CsProjBuildHook.ValidBuildRecords => ...`
- L108 _private* property_ `DirectoryReference CsProjBuildHook.EngineDirectory => ...`
- L110 _private* property_ `DirectoryReference IMsBuildRegistration.DotnetDirectory => ...`
- L112 _private* property_ `FileReference IMsBuildRegistration.DotnetPath => ...`

### `Source/Programs/Shared/EpicGames.Build/System/DirectoryEnumerator.cs` (EpicGames.Build)


#### class `UnrealBuildBase.DirectoryEnumerator`  
`public static class DirectoryEnumerator`  
_public; L15-359_
- desc: Platform optimized utility class to enumerate directory to fetch information needed by FileItem and DirectoryItem
- L33-123 _public method_ `public static unsafe List<Entry>? Enumerate(string directoryPath, int bufferSize = 128 * 1024)` — Enumerate a directory. If directory does not exist it will return null
- L131-145 _public method_ `public static bool TryGetFileFromPath(string path, out Entry entry)` — Try to get file from path
- L153-167 _public method_ `public static bool TryGetDirectoryFromPath(string path, out Entry entry)` — Try to get directory from path
- L169-184 _private method_ `private static bool TryGetEntryFromPath(string path, out Entry entry)`
- L186-229 _private method_ `private static unsafe void EnumerateWithBuffer(IntPtr dirHandle, byte* buf, int bufferSize, List<Entry> entries)`
- L231-236 _private method_ `private static void ThrowIo(int ntstatus, string op)`
- L238 _private const_ `private const int STATUS_SUCCESS = 0x00000000`
- L239 _private const_ `private const int STATUS_NO_MORE_FILES = unchecked((int)0x80000006)`
- L241 _private const_ `private const uint OBJ_CASE_INSENSITIVE = 0x00000040`
- L243 _private const_ `private const uint FILE_LIST_DIRECTORY = 0x0001`
- L244 _private const_ `private const uint FILE_SHARE_READ = 0x00000001`
- L245 _private const_ `private const uint FILE_SHARE_WRITE = 0x00000002`
- L246 _private const_ `private const uint FILE_SHARE_DELETE = 0x00000004`
- L247 _private const_ `private const uint FILE_OPEN = 0x00000001`
- L248 _private const_ `private const uint FILE_DIRECTORY_FILE = 0x00000001`
- L249 _private const_ `private const uint FILE_SYNCHRONOUS_IO_NONALERT = 0x00000020`
- L250 _private const_ `private const uint SYNCHRONIZE = 0x00100000`
- L253 _private method_ `private static extern int NtClose(IntPtr handle)` — attrs: `[DllImport("ntdll.dll")]`
- L256 _private method_ `private static extern int RtlNtStatusToDosError(int status)` — attrs: `[DllImport("ntdll.dll", ExactSpelling = true)]`
- L259 _private method_ `private static extern unsafe int NtCreateFile( out IntPtr FileHandle, uint DesiredAccess, ref OBJECT_ATTRIBUTES ObjectAttributes, out IO_STATUS_BLOCK IoStatusBlock, ref long AllocationSize, uint FileAttributes, uint ShareAccess, uint CreateDisposition, uint CreateOptions, IntPtr EaBuffer, uint EaLength)` — attrs: `[DllImport("ntdll.dll", ExactSpelling = true)]`
- L273 _private method_ `private static extern unsafe int NtQueryDirectoryFile( IntPtr FileHandle, IntPtr Event, IntPtr ApcRoutine, IntPtr ApcContext, out IO_STATUS_BLOCK IoStatusBlock, void* FileInformation, uint Length, FILE_INFORMATION_CLASS FileInformationClass, [MarshalAs(UnmanagedType.U1)] bool ReturnSingleEntry, UNICODE_STRING* FileName, [MarshalAs(UnmanagedType.U1)] bool RestartScan)` — attrs: `[DllImport("ntdll.dll", ExactSpelling = true)]`
- L287 _private method_ `private static extern bool GetFileAttributesExW(string lpFileName, GET_FILEEX_INFO_LEVELS fInfoLevelId, out WIN32_FILE_ATTRIBUTE_DATA fileData)` — attrs: `[DllImport("kernel32.dll", CharSet = CharSet.Unicode, SetLastError = true)]`

#### record struct `UnrealBuildBase.DirectoryEnumerator.Entry`  
`public readonly record struct Entry(string Name, long Size, FileAttributes Attributes, DateTime CreationTimeUtc, DateTime LastWriteTimeUtc)`  
_public; L25-25_
- desc: Struct representing a file system entry

#### enum `UnrealBuildBase.DirectoryEnumerator.GET_FILEEX_INFO_LEVELS`  
`private enum GET_FILEEX_INFO_LEVELS : int`  
_private; L289-292_
- inherits: `int`
- L291 _public* enumerator_ `GetFileExInfoStandard = 0`

#### struct `UnrealBuildBase.DirectoryEnumerator.FILETIME`  
`private struct FILETIME`  
_private; L295-299_
- attrs: `[StructLayout(LayoutKind.Sequential)]`
- L297 _public field_ `public uint dwLowDateTime`
- L298 _public field_ `public uint dwHighDateTime`

#### struct `UnrealBuildBase.DirectoryEnumerator.WIN32_FILE_ATTRIBUTE_DATA`  
`private struct WIN32_FILE_ATTRIBUTE_DATA`  
_private; L302-310_
- attrs: `[StructLayout(LayoutKind.Sequential)]`
- L304 _public field_ `public uint dwFileAttributes`
- L305 _public field_ `public FILETIME ftCreationTime`
- L306 _public field_ `public FILETIME ftLastAccessTime`
- L307 _public field_ `public FILETIME ftLastWriteTime`
- L308 _public field_ `public uint nFileSizeHigh`
- L309 _public field_ `public uint nFileSizeLow`

#### struct `UnrealBuildBase.DirectoryEnumerator.UNICODE_STRING`  
`private unsafe struct UNICODE_STRING`  
_private; L313-318_
- attrs: `[StructLayout(LayoutKind.Sequential)]`
- L315 _public field_ `public ushort Length`
- L316 _public field_ `public ushort MaximumLength`
- L317 _public field_ `public char* Buffer`

#### struct `UnrealBuildBase.DirectoryEnumerator.OBJECT_ATTRIBUTES`  
`private unsafe struct OBJECT_ATTRIBUTES`  
_private; L321-329_
- attrs: `[StructLayout(LayoutKind.Sequential)]`
- L323 _public field_ `public uint Length`
- L324 _public field_ `public IntPtr RootDirectory`
- L325 _public field_ `public UNICODE_STRING* ObjectName`
- L326 _public field_ `public uint Attributes`
- L327 _public field_ `public IntPtr SecurityDescriptor`
- L328 _public field_ `public IntPtr SecurityQualityOfService`

#### struct `UnrealBuildBase.DirectoryEnumerator.IO_STATUS_BLOCK`  
`private struct IO_STATUS_BLOCK`  
_private; L332-336_
- attrs: `[StructLayout(LayoutKind.Sequential)]`
- L334 _public field_ `public IntPtr Status`
- L335 _public field_ `public nuint Information`

#### enum `UnrealBuildBase.DirectoryEnumerator.FILE_INFORMATION_CLASS`  
`private enum FILE_INFORMATION_CLASS : int`  
_private; L338-341_
- inherits: `int`
- L340 _public* enumerator_ `FileFullDirectoryInformation = 2`

#### struct `UnrealBuildBase.DirectoryEnumerator.FILE_FULL_DIR_INFORMATION`  
`private struct FILE_FULL_DIR_INFORMATION`  
_private; L344-358_
- attrs: `[StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]`
- L346 _public field_ `public uint NextEntryOffset`
- L347 _public field_ `public uint FileIndex`
- L348 _public field_ `public long CreationTime`
- L349 _public field_ `public long LastAccessTime`
- L350 _public field_ `public long LastWriteTime`
- L351 _public field_ `public long ChangeTime`
- L352 _public field_ `public long EndOfFile`
- L353 _public field_ `public long AllocationSize`
- L354 _public field_ `public uint FileAttributes`
- L355 _public field_ `public uint FileNameLength`
- L356 _public field_ `public uint EaSize`
- L357 _public field_ `public char FileName`

### `Source/Programs/Shared/EpicGames.Build/System/DirectoryItem.cs` (EpicGames.Build)


#### class `UnrealBuildBase.DirectoryItem`  
`public class DirectoryItem`  
_public; L17-431_
- desc: Stores the state of a directory. May or may not exist.
- L22 _public property_ `public required DirectoryReference Location { get; init; }` — Full path to the directory on disk
- L27 _public property_ `public required string Name { get; init; }` — The name of this directory
- L32 _private* property_ `Dictionary<string, DirectoryItem> Directories => ...` — Accessor for map of name to subdirectory item
- L37 _private* property_ `Dictionary<string, FileItem> Files => ...` — Accessor for map of name to file
- L42 _public property_ `public string FullName => ...` — The full name of this directory
- L47 _public property_ `public bool Exists => ...` — Whether the directory exists or not
- L52 _public property_ `public DateTime LastWriteTimeUtc => ...` — The last write time of the file.
- L57 _public property_ `public DateTime CreationTimeUtc => ...` — The creation time of the file.
- L62-66 _public method_ `public DirectoryItem? GetParentDirectoryItem()` — Gets the parent directory item
- L74 _public method_ `public static DirectoryItem Combine(DirectoryItem BaseDirectory, params string[] Fragments)` — Gets a new directory item by combining the existing directory item with the given path fragments
- L82 _public method_ `public static DirectoryItem GetItemByPath(string Location)` — Finds or creates a directory item from its location
- L89 _public method_ `public static DirectoryItem GetItemByDirectoryReference(DirectoryReference Location)` — Finds or creates a directory item from its location
- L97 _public method_ `public static DirectoryItem GetItemByDirectoryInfo(DirectoryInfo Info)` — Finds or creates a directory item from a DirectoryInfo object
- L102-119 _public method_ `public void ResetCachedInfo()` — Reset the contents of the directory and allow them to be fetched again
- L126-160 _public method_ `public void PrepopulateCache(List<string> files)` — This function can be used to force the cache to be populated with files that do not yet exist. Useful when wanting to run things in parallel and one thread write files while the other uses the list of files in the directory.
- L165-171 _public method_ `public static void ResetCachedInfo(string Path)` — Resets the cached info, if the DirectoryInfo is not found don't create a new entry
- L176-184 _public method_ `public static void ResetAllCachedInfo_SLOW()` — Resets all cached directory info. Significantly reduces performance; do not use unless strictly necessary.
- L189 _public method_ `public bool CacheDirectories()` — Caches the subdirectories of this directories
- L195-199 _public method_ `public IEnumerable<DirectoryItem> EnumerateDirectories()` — Enumerates all the subdirectories
- L207-225 _public method_ `public bool TryGetDirectory(string Name, [NotNullWhen(true)] out DirectoryItem? OutDirectory)` — Attempts to get a sub-directory by name
- L228-235 _private* ctor_ `DirectoryItem(DirectoryReference location, string name, Info? info)` — attrs: `[SetsRequiredMembers]`
- L237-252 _private* method_ `Info Update()`
- L254-260 _internal method_ `internal void Update(DirectoryEnumerator.Entry entry, bool force)`
- L266-331 _private* method_ `(Dictionary<string, DirectoryItem>, Dictionary<string, FileItem>) Scan()` — Scans the directory for directories and files, used for lazy initialization.
- L336 _public method_ `public bool CacheFiles()` — Caches the files in this directory
- L342-346 _public method_ `public IEnumerable<FileItem> EnumerateFiles()` — Enumerates all the files
- L353-356 _public method_ `public bool ContainsFiles(SearchOption searchOption = SearchOption.TopDirectoryOnly)` — Check if this directory contains any files
- L365-369 _public method_ `public bool TryGetFile(string Name, [NotNullWhen(true)] out FileItem? OutFile)` — Attempts to get a file from this directory by name. Unlike creating a file item and checking whether it exists, this will not create a permanent FileItem object if it does not exist.
- L375 _public method_ `public override string ToString()` — Formats this object as a string for debugging
- L380 _public field_ `public static readonly IComparer<DirectoryItem?> SortByPath = new SortByPathComparer()` — Sort file items by full path
- L385-399 _public method_ `public static void WriteDebugFileWithAllEnumeratedFiles(string OutFile)` — Writes out all the enumerated files full names sorted to OutFile
- L408 _private* field_ `Info? _info`
- L409 _private* field_ `Lazy<(Dictionary<string, DirectoryItem>, Dictionary<string, FileItem>)> _cache`
- L410 _private* field_ `static ConcurrentDictionary<DirectoryReference, DirectoryItem> LocationToItem = ...`
- L410 _private* field_ `static ConcurrentDictionary< LocationToItem = []`

#### class `UnrealBuildBase.DirectoryItem.Info`  
`class Info`  
_private*; L401-406_
- L403 _internal field_ `internal bool Exists`
- L404 _internal field_ `internal DateTime LastWriteTimeUtc`
- L405 _internal field_ `internal DateTime CreationTimeUtc`

#### class `UnrealBuildBase.DirectoryItem.SortByPathComparer`  
`class SortByPathComparer : IComparer<DirectoryItem?>`  
_private*; L412-430_
- inherits: `IComparer<DirectoryItem?>`
- L414-429 _public method_ `public int Compare(DirectoryItem? a, DirectoryItem? b)`

#### class `UnrealBuildBase.DirectoryItemExtensionMethods`  
`public static class DirectoryItemExtensionMethods`  
_public; L436-480_
- desc: Helper functions for serialization
- L443-447 _public method_ `public static DirectoryItem? ReadDirectoryItem(this BinaryArchiveReader Reader)` — Read a directory item from a binary archive
- L454-458 _public method_ `public static void WriteDirectoryItem(this BinaryArchiveWriter Writer, DirectoryItem DirectoryItem)` — Write a directory item to a binary archive
- L465-469 _public method_ `public static void WriteCompactDirectoryReference(this BinaryArchiveWriter Writer, DirectoryReference Directory)` — Writes a directory reference to a binary archive
- L476-479 _public method_ `public static DirectoryReference ReadCompactDirectoryReference(this BinaryArchiveReader Reader)` — Reads a directory reference from a binary archive

### `Source/Programs/Shared/EpicGames.Build/System/DirectoryLookupCache.cs` (EpicGames.Build)


#### class `UnrealBuildBase.DirectoryLookupCache`  
`public static class DirectoryLookupCache`  
_public; L10-42_
- L12-15 _public method_ `public static bool FileExists(FileReference File)`
- L17-20 _public method_ `public static bool DirectoryExists(DirectoryReference Directory)`
- L22-26 _public method_ `public static bool DirectoryExistsAndContainsFiles(DirectoryReference Directory, SearchOption searchOption = SearchOption.TopDirectoryOnly)`
- L28-31 _public method_ `public static IEnumerable<FileReference> EnumerateFiles(DirectoryReference Directory)`
- L33-36 _public method_ `public static IEnumerable<DirectoryReference> EnumerateDirectories(DirectoryReference Directory)`
- L38-41 _public method_ `public static void InvalidateCachedDirectory(DirectoryReference Directory)`

### `Source/Programs/Shared/EpicGames.Build/System/EnumeratePlugins.cs` (EpicGames.Build)


#### class `UnrealBuildBase.PluginsBase`  
`public class PluginsBase`  
_public; L12-236_
- L17 _private* field_ `static ConcurrentDictionary<DirectoryReference, Lazy<List<FileReference>>> PluginFileCache = ...` — Cache of plugin filenames under each directory
- L17 _private* field_ `static ConcurrentDictionary< PluginFileCache = new()` — Cache of plugin filenames under each directory
- L23 _private* field_ `static Dictionary<FileReference, FileReference> UbtPluginFileCache = ...` — Cache of all UBT plugins that have been built. When generating projects, there is a good chance that a UBT project might need to be rebuilt.
- L23 _private* field_ `static Dictionary< UbtPluginFileCache = []` — Cache of all UBT plugins that have been built. When generating projects, there is a good chance that a UBT project might need to be rebuilt.
- L29-33 _public method_ `public static void InvalidateCache_SLOW()` — Invalidate cached plugin data so that we can pickup new things Warning: Will make subsequent plugin lookups and directory scans slow until the caches are repopulated
- L40-49 _public method_ `public static List<FileReference> EnumeratePlugins(FileReference? ProjectFile)` — Enumerates all the plugin files available to the given project
- L55-73 _public method_ `public static List<FileReference> EnumeratePlugins(DirectoryReference ParentDirectory)` — Find paths to all the plugins under a given parent directory (recursively)
- L81-107 _private* method_ `static void EnumeratePluginsInternal(DirectoryItem ParentDirectory, List<FileReference> FileNames, ParallelQueue Queue)` — Find paths to all the plugins under a given parent directory (recursively)
- L114-132 _public method_ `public static List<FileReference> EnumerateUbtPlugins(FileReference? ProjectFile)` — Enumerates all the UBT plugin files available to the given project
- L143-176 _public method_ `public static bool BuildUbtPlugins(FileReference? ProjectFile, IEnumerable<FileReference> FoundPlugins, IReadOnlyDictionary<string, IEnumerable<string>>? CustomGlobalProperties, ILogger Logger, out (FileReference ProjectFile, FileReference TargetAssembly)[]? Plugins)` — Build the given collection of plugins
- L185-235 _private method_ `private static bool BuildUbtPluginsInternal(PluginSet PluginSet, FileReference? ProjectFile, List<FileReference> Built, IEnumerable<FileReference> NotBuilt, IReadOnlyDictionary<string, IEnumerable<string>>? CustomGlobalProperties, ILogger Logger)`

#### enum `UnrealBuildBase.PluginsBase.PluginSet`  
`private enum PluginSet`  
_private; L178-183_
- L180 _public* enumerator_ `EngineOnly`
- L181 _public* enumerator_ `ProjectOnly`
- L182 _public* enumerator_ `Both`

### `Source/Programs/Shared/EpicGames.Build/System/FileHasher.cs` (EpicGames.Build)


#### class `UnrealBuildBase.FileHasher`  
`public class FileHasher(ILogger? logger = null)`  
_public; L20-142_
- desc: FileHasher constructor
- L40 _private* field_ `ConcurrentDictionary<string, CachedDigest> CachedDigests = ...`
- L40 _private* field_ `ConcurrentDictionary< CachedDigests = new()`
- L46-51 _public method_ `public async Task Save(FileReference location)` — Saves cached digests to disk.
- L57-71 _public method_ `public async Task Load(FileReference location)` — Loads cached digests from disk, replacing existing cache.
- L76-82 _public method_ `public void PurgeStale()` — Purges stale cached digests.
- L91-109 _public method_ `public async Task<IoHash> GetDigestAsync(FileItem item, CancellationToken cancellationToken = default)` — Get the IoHash digest of a file's contents.
- L117-121 _public method_ `public void SetDigest(FileItem item, IoHash hash)` — In systems where the IoHash is already available, this allows it to be updated directly and not recomputed.
- L130 _public method_ `public Task<IoHash> GetDigestAsync(FileReference location, CancellationToken cancellationToken = default)` — Get the IoHash digest of a file's contents.
- L132 _public method_ `public IoHash GetDigest(FileItem item)`
- L133 _public method_ `public IoHash GetDigest(FileReference location)`
- L135-141 _private* method_ `static async Task<CachedDigest> ComputeDigest(FileItem item, ILogger? logger, CancellationToken CancellationToken = default)`

#### struct `UnrealBuildBase.FileHasher.CachedDigest`  
`private readonly struct CachedDigest(FileItem item, IoHash digest)`  
_private; L22-37_
- L25 _public property_ `public long Length { get; init; }` — attrs: `[JsonPropertyName("l")]`
- L27 _public property_ `public long LastWriteTimeUtc { get; init; }` — attrs: `[JsonPropertyName("w")]`
- L29 _public property_ `public IoHash Digest { get; init; }` — attrs: `[JsonPropertyName("d")]`
- L36 _public method_ `public bool UpToDate(FileItem item)` — Check if a digest is up to date for a FileItem

### `Source/Programs/Shared/EpicGames.Build/System/FileItem.cs` (EpicGames.Build)


#### class `UnrealBuildBase.FileItem`  
`public class FileItem`  
_public; L21-304_
- desc: Represents a file on disk that is used as an input or output of a build action. FileItem instances are unique for a given path. Use FileItem.GetItemByFileReference to get the FileItem for a specific path.
- L26 _private* field_ `Lazy<DirectoryItem> _cachedDirectory` — The directory containing this file
- L31 _public property_ `public required FileReference Location { get; init; }` — Location of this file
- L36 _public property_ `public required string Name { get; init; }` — Name of this file
- L41 _public property_ `public string FullName => ...` — Full name of this file
- L46 _public property_ `public string AbsolutePath => ...` — Accessor for the absolute path to the file
- L51 _public property_ `public DirectoryItem Directory => ...` — Gets the directory that this file is in
- L56 _public property_ `public bool Exists => ...` — Whether the file exists.
- L61 _public property_ `public long Length => ...` — Size of the file if it exists, otherwise -1
- L66 _public property_ `public FileAttributes Attributes => ...` — The attributes for this file
- L71 _public property_ `public DateTime LastWriteTimeUtc => ...` — The last write time of the file.
- L76 _public property_ `public DateTime CreationTimeUtc => ...` — The creation time of the file.
- L83 _public method_ `public bool HasExtension(string Extension)` — Determines if the file has the given extension
- L89 _public method_ `public DirectoryItem GetDirectoryItem()` — Gets the directory containing this file
- L95-102 _public method_ `public void UpdateCachedDirectory(DirectoryItem Directory)` — Updates the cached directory for this file. Used by DirectoryItem when enumerating files, to avoid having to look this up later.
- L107 _public property_ `public bool IsPlaceholder => ...` — Returns true if file is a placeholder file which can only be used to check if it exists. Length, create/write date are not valid
- L114 _public method_ `public static FileItem GetItemByPath(string FilePath)` — Gets a FileItem corresponding to the given path
- L121 _public method_ `public static FileItem GetItemByFileInfo(FileInfo Info)` — Gets a FileItem for a given path
- L128 _public method_ `public static FileItem GetItemByFileReference(FileReference Location)` — Gets a FileItem for a given path
- L134-176 _public method_ `public void Delete(ILogger Logger)` — Deletes the file.
- L181-184 _public method_ `public void ResetCachedInfo()` — Resets the cached file info
- L189-195 _public method_ `public static void ResetCachedInfo(string Path)` — Resets the cached info, if the FileInfo is not found don't create a new entry
- L200-203 _public method_ `public static void ResetAllCachedInfo_SLOW()` — Resets all cached file info. Significantly reduces performance; do not use unless strictly necessary.
- L209 _public method_ `public override string ToString()` — Return the path to this FileItem to debugging
- L214 _public field_ `public static readonly IComparer<FileItem?> SortByPath = new SortByPathComparer()` — Sort file items by full path
- L219 _public property_ `public bool HasInfo => ...` — For debugging purposes, to know if info has been populated
- L222-231 _internal ctor_ `internal FileItem(FileReference Location, string name, Info? info, DirectoryItem? directory)` — attrs: `[SetsRequiredMembers]`
- L233-250 _private method_ `private Info Update()`
- L252-260 _private method_ `private Info UpdateCheckPlaceholder(string property)`
- L262-268 _internal method_ `internal void Update(DirectoryEnumerator.Entry entry, bool force)`
- L273 _internal field_ `internal static ConcurrentDictionary<FileReference, FileItem> UniqueSourceFileMap = ...` — A case-insensitive dictionary that's used to map each unique file name to a single FileItem object.
- L273 _internal field_ `internal static ConcurrentDictionary< UniqueSourceFileMap = new(-1, 100000)` — A case-insensitive dictionary that's used to map each unique file name to a single FileItem object.
- L283 _private* field_ `Info? _info`

#### class `UnrealBuildBase.FileItem.Info`  
`internal class Info`  
_internal; L275-281_
- L277 _internal field_ `internal FileAttributes Attributes`
- L278 _internal field_ `internal long Length`
- L279 _internal field_ `internal DateTime LastWriteTimeUtc`
- L280 _internal field_ `internal DateTime CreationTimeUtc`

#### class `UnrealBuildBase.FileItem.SortByPathComparer`  
`class SortByPathComparer : IComparer<FileItem?>`  
_private*; L285-303_
- inherits: `IComparer<FileItem?>`
- L287-302 _public method_ `public int Compare(FileItem? a, FileItem? b)`

#### class `UnrealBuildBase.FileItemExtensionMethods`  
`public static class FileItemExtensionMethods`  
_public; L309-374_
- desc: Helper functions for serialization
- L316-319 _public method_ `public static FileItem? ReadFileItem(this BinaryArchiveReader Reader)` — Read a file item from a binary archive
- L326-329 _public method_ `public static void WriteFileItem(this BinaryArchiveWriter Writer, FileItem? FileItem)` — Write a file item to a binary archive
- L338-346 _private* method_ `static FileItem ReadCompactFileItemData(this BinaryArchiveReader Reader)` — attrs: `[MethodImpl(MethodImplOptions.AggressiveInlining)]` — Read a file item as a DirectoryItem and name. This is slower than reading it directly, but results in a significantly smaller archive where most files are in the same directories.
- L354-358 _public method_ `public static FileItem ReadCompactFileItem(this BinaryArchiveReader Reader)` — attrs: `[MethodImpl(MethodImplOptions.AggressiveInlining)]` — Read a file item in a format which de-duplicates directory names.
- L365-373 _public method_ `public static void WriteCompactFileItem(this BinaryArchiveWriter Writer, FileItem FileItem)` — Writes a file item in a format which de-duplicates directory names.

### `Source/Programs/Shared/EpicGames.Build/System/GlobalSingleInstanceMutex.cs` (EpicGames.Build)


#### class `UnrealBuildBase.GlobalSingleInstanceMutex`  
`public static class GlobalSingleInstanceMutex`  
_public; L15-49_
- desc: Helper methods for single instance mutexes.
- L22-26 _public method_ `public static string GetUniqueMutexForPath(string name, string uniquePath)` — Gets the name of a mutex unique for the given path
- L33 _public method_ `public static string GetUniqueMutexForPath(string name, FileSystemReference? uniquePath)` — Gets the name of a mutex unique for the given path
- L41-48 _public method_ `public static IDisposable AcquireNowOrThrow(string name)` — Tries to acquire a global mutex with the given name if it's available, and throws if it is not.

### `Source/Programs/Shared/EpicGames.Build/System/NativeProjectsBase.cs` (EpicGames.Build)


#### class `UnrealBuildBase.NativeProjectsBase`  
`public class NativeProjectsBase`  
_public; L16-191_
- desc: Utility functions for querying native projects (ie. those found via a .uprojectdirs query)
- L21 _protected field_ `static protected Lock LockObject = new()` — Object used for synchronizing access to static fields
- L26 _private* field_ `static HashSet<DirectoryReference>? CachedBaseDirectories` — The native project base directories
- L31 _private* field_ `static HashSet<FileReference>? CachedProjectFiles` — Cached list of project files within all the base directories
- L36-40 _public method_ `public static void ClearCacheBase()` — Clear our cached properties. Generally only needed if your script has modified local files...
- L45-81 _public method_ `public static IEnumerable<DirectoryReference> EnumerateBaseDirectories(ILogger Logger)` — Retrieve the list of base directories for native projects
- L87-124 _public method_ `public static IEnumerable<FileReference> EnumerateProjectFiles(ILogger Logger)` — Returns a list of all the projects
- L132-137 _public method_ `public static FileReference? FindRelativeFileReference(string File, ILogger Logger)` — Searches base directories for an existing relative pathed file
- L145-150 _public method_ `public static DirectoryReference? FindRelativeDirectoryReference(string Directory, ILogger Logger)` — Searches base directories for an existing relative pathed directory
- L158-178 _public method_ `public static FileReference? FindProjectFile(string Project, ILogger Logger)` — Takes a project name (e.g "ShooterGame") or path and attempt to find the existing uproject file in the base directories
- L186-190 _public method_ `public static bool IsNativeProject(FileReference ProjectFile, ILogger Logger)` — Checks if a given project is a native project

### `Source/Programs/Shared/EpicGames.Build/System/Parallel2.cs` (EpicGames.Build)


#### class `UnrealBuildBase.Parallel2`  
`public static class Parallel2`  
_public; L17-225_
- desc: Parallel2 is a collection of concurrent utilities designed for wall time throughput. Proven to reduce wall time in UBT when running lots of Parallel.ForEach etc.
- L32-119 _public method_ `public static void ForEach<TSource>(IEnumerable<TSource> source, Action<TSource> body, int helperCount = -1, bool useTasks = true)` — Loops through elements in an enumerator and run them in parallel. There is a very important difference compared to normal Parallel.ForEach and that is that there is no "join" of scheduled tasks. This will make Parallel2.ForEach much faster when there are lots of queued tasks since it will not wait for scheduled tasks before exiting. Parallel2.ForEach is much more friendly to nesting lots of parallel foreach.
- L129-203 _public method_ `public static void For(int from, int to, Action<int> body, int helperCount = -1, bool useTasks = true)` — Read information about Parallel2.ForEach
- L224 _public field_ `public static readonly int MaxHelperCount = Math.Max(Environment.ProcessorCount - 1, 0)`

#### class `UnrealBuildBase.Parallel2.ForEachContext`  
`private class ForEachContext<TSource>`  
_private; L205-213_
- L207 _internal field_ `internal required IEnumerator<TSource> Enumerator`
- L208 _internal field_ `internal required ManualResetEventSlim Handle`
- L209 _internal field_ `internal int Count`
- L210 _internal field_ `internal int Finished`
- L211 _internal field_ `internal bool Done`
- L212 _internal field_ `internal ExceptionDispatchInfo? Exception`

#### class `UnrealBuildBase.Parallel2.ForContext`  
`private class ForContext`  
_private; L215-222_
- L217 _internal field_ `internal required ManualResetEventSlim Handle`
- L218 _internal field_ `internal int Index`
- L219 _internal field_ `internal int End`
- L220 _internal field_ `internal int Finished`
- L221 _internal field_ `internal ExceptionDispatchInfo? Exception`

#### class `UnrealBuildBase.ParallelQueue`  
`public sealed class ParallelQueue : IDisposable`  
_public; L233-342_
- inherits: `IDisposable`
- desc: Parallel queue. Enqueue actions and then call Drain() to execute actions in parallel Actions are allowed to enqueue more actions from inside the actions There is a very important implementation detail and that is that there is no "join" of scheduled tasks. It will really exit as early as possible
- L239-249 _public method_ `public void Enqueue(Action body)` — Enqueue work which will directly be picked up by workers if inside Run action to run
- L256-320 _public method_ `public void Drain(int helperCount = -1, bool useTasks = true)` — Drain the queue. Can only be done once
- L322-330 _public method_ `public void Dispose()`
- L332 _private field_ `private readonly ConcurrentQueue<Action> _queue = new()`
- L333 _private field_ `private readonly SemaphoreSlim _available = new(0)`
- L334 _private field_ `private int _outstanding`
- L335 _private field_ `private int _accepting = 1`
- L336 _private field_ `private int _done`
- L337 _private field_ `private int _helperCount`
- L338 _private field_ `private int _workerCount`
- L339 _private field_ `private ExceptionDispatchInfo? _exception`
- L341 _public field_ `public static readonly int MaxHelperCount = Math.Max(Environment.ProcessorCount - 1, 0)`

### `Source/Programs/Shared/EpicGames.Build/System/Rules.cs` (EpicGames.Build)


#### class `UnrealBuildBase.Rules`  
`public class Rules`  
_public; L12-426_
- L50-122 _public method_ `public static List<FileReference> FindAllRulesSourceFiles(RulesFileType RulesFileType, List<DirectoryReference>? GameFolders, List<FileReference>? ForeignPlugins, List<DirectoryReference>? AdditionalSearchPaths, bool bIncludeEngine = true, bool bIncludeTempTargets = true)`
- L128-142 _public method_ `public static void InvalidateRulesFileCache(string DirectoryPath)` — Invalidate the cache for the givcen directory
- L158 _private* field_ `static Directory Root = new()`
- L159 _private* field_ `static ReaderWriterLockSlim RootLock = new()`
- L161-182 _private* method_ `static Directory? FindDirectory(DirectoryReference dirRef, bool createIfNotFound)`
- L188-223 _public method_ `public static void Populate(IEnumerable<DirectoryReference> dirs)` — Populate rule files from provided directories
- L231-256 _public method_ `public static List<FileReference> Get(IEnumerable<DirectoryReference> dirs, RulesFileType type)` — Get all rule files of type. Requires populate to have been run for this to work
- L258-282 _private method_ `private static void DistinctSortedList(List<FileReference> files)`
- L284-316 _private method_ `private static void GetRecursively(List<FileReference> outFiles, Directory dir, RulesFileType type)`
- L318-425 _private method_ `private static void PopulateRecursively(DirectoryItem dirItem, Directory dir, ParallelQueue queue)`

#### enum `UnrealBuildBase.Rules.RulesFileType`  
`public enum RulesFileType`  
_public; L17-38_
- desc: Enum for types of rules files. Should match extensions in RulesFileExtensions.
- L22 _public* enumerator_ `Module` — .build.cs files
- L27 _public* enumerator_ `Target` — .target.cs files
- L32 _public* enumerator_ `AutomationModule` — .automation.csproj files
- L37 _public* enumerator_ `UbtPlugin` — .ubtplugin.csproj files

#### class `UnrealBuildBase.Rules.Files`  
`class Files`  
_private*; L144-150_
- L146 _public field_ `public List<FileReference> ModuleRules = []`
- L147 _public field_ `public List<FileReference> TargetRules = []`
- L148 _public field_ `public List<FileReference> AutomationModules = []`
- L149 _public field_ `public List<FileReference> UbtPlugins = []`

#### class `UnrealBuildBase.Rules.Directory`  
`class Directory`  
_private*; L152-157_
- L154 _internal field_ `internal Files? Files`
- L155 _internal field_ `internal Dictionary<string, Directory>? SubDirectories`
- L155 _internal field_ `internal Dictionary< SubDirectories`
- L156 _internal field_ `internal bool IsScanned`

### `Source/Programs/Shared/EpicGames.Build/System/Timeline.cs` (EpicGames.Build)


#### interface `UnrealBuildBase.ITimelineEvent`  
`public interface ITimelineEvent : IDisposable`  
_public; L16-19_
- inherits: `IDisposable`
- desc: Public interface for a timeline scope. Should be disposed to exit the scope.
- L18 _public* method_ `void Finish()`

#### class `UnrealBuildBase.Timeline`  
`public static class Timeline`  
_public; L24-350_
- desc: Tracks simple high-level timing data
- L118 _public field_ `public static Func<string, uint>? OnEventBegin`
- L118 _public field_ `public static Func< OnEventBegin`
- L119 _public field_ `public static Action<uint>? OnEventEnd`
- L124 _private* field_ `static Stopwatch Stopwatch = new()` — The stopwatch used for timing
- L129 _private* field_ `static List<Event> Events = []` — The recorded events
- L134 _public property_ `public static TimeSpan Elapsed => ...` — Property for the total time elapsed
- L139-142 _public method_ `public static void Start()` — Start the stopwatch
- L147-150 _public method_ `public static void Stop()` — Stop the stopwatch
- L156-163 _public method_ `public static void AddEvent(string Name)` — Records a timeline marker with the given name
- L170-178 _public method_ `public static ITimelineEvent ScopeEvent(string Name)` — Enters a scope event with the given name. Should be disposed to terminate the scope.
- L188-196 _public method_ `public static ITimelineEvent ScopeEvent(string Name, ILogger Logger, LogLevel Verbosity = LogLevel.Information)` — Enters a scope event with the given name. Should be disposed to terminate the scope. Also logs the finish of the event at the provided verbosity.
- L206-279 _public method_ `public static void Print(TimeSpan? MinKnownTime, TimeSpan MaxUnknownTime, int? MaxDepth, LogLevel Verbosity, ILogger Logger)` — Prints this information to the log
- L290-298 _private* method_ `static void UpdateLastEventTime(ref TimeSpan LastTime, TimeSpan NewTime, TimeSpan MaxUnknownTime, List<Event> OuterEvents, LogLevel Verbosity, ILogger Logger)` — Updates the last event time
- L310-338 _private* method_ `static void Print(TimeSpan StartTime, TimeSpan? FinishTime, TimeSpan? MinKnownTime, string Label, List<Event> OuterEvents, LogLevel Verbosity, ILogger Logger)` — Prints an individual event to the log
- L345-349 _private* method_ `static string FormatTime(TimeSpan Time)` — Formats a timespan in milliseconds

#### class `UnrealBuildBase.Timeline.Event`  
`class Event : ITimelineEvent`  
_private*; L30-116_
- attrs: `[DebuggerDisplay("{Name}")]`
- inherits: `ITimelineEvent`
- desc: A marker in the timeline
- L35 _public field_ `public readonly string Name` — Name of the marker
- L40 _public field_ `public readonly TimeSpan StartTime` — Time at which the event ocurred
- L45 _public field_ `public TimeSpan? FinishTime` — Time at which the event ended
- L50 _public field_ `public readonly ITraceSpan Span` — The trace span for external tracing
- L55 _private* field_ `ILogger? Logger` — Optional output logger
- L60 _private* field_ `LogLevel? Verbosity` — Optional output verbosity
- L62 _private* field_ `uint Id = 0`
- L72-85 _public ctor_ `public Event(string Name, TimeSpan StartTime, TimeSpan? FinishTime = null, ILogger? Logger = null, LogLevel? Verbosity = null)` — Constructor
- L90-107 _public method_ `public void Finish()` — Finishes the current event
- L112-115 _public method_ `public void Dispose()` — Disposes of the current event

#### struct `UnrealBuildBase.TimelineEventScope`  
`public readonly struct TimelineEventScope : IDisposable`  
_public; L355-381_
- inherits: `IDisposable`
- desc: Will add and remove to OnEvent
- L357 _private* field_ `readonly Func<string, uint>? _begin`
- L357 _private* field_ `readonly Func< _begin`
- L358 _private* field_ `readonly Action<uint>? _end`
- L365-371 _public ctor_ `public TimelineEventScope(Func<string, uint>? begin, Action<uint>? end)` — Ctor
- L376-380 _public method_ `public void Dispose()` — Dispose

### `Source/Programs/Shared/EpicGames.Build/Unreal.cs` (EpicGames.Build)


#### class `UnrealBuildBase.Unreal`  
`public static class Unreal`  
_public; L15-550_
- L17-98 _private method_ `private static DirectoryReference FindRootDirectory()`
- L100-120 _private method_ `private static FileReference FindUnrealBuildToolDll()`
- L122 _private const_ `private const string DotnetVersionDirectory = "10.0"`
- L124-145 _private method_ `private static string FindRelativeDotnetDirectory(RuntimePlatform.Type hostPlatform)`
- L147 _private method_ `private static string FindRelativeDotnetDirectory()`
- L149-157 _private method_ `private static Version GetDotnetFileVersion()`
- L163 _public property_ `public static string RelativeDotnetDirectory => ...` — Relative path to the dotnet executable from EngineDir
- L164 _private field_ `private static readonly Lazy<string> s_relativeDotnetDirectory = new(FindRelativeDotnetDirectory)`
- L166 _private method_ `private static DirectoryReference FindDotnetDirectory()`
- L171 _public property_ `public static DirectoryReference RootDirectory => ...` — The full name of the root UE directory
- L172 _private field_ `private static readonly Lazy<DirectoryReference> s_rootDirectory = new(FindRootDirectory)`
- L177 _public property_ `public static DirectoryReference EngineDirectory => ...` — The full name of the Engine directory
- L178 _private field_ `private static readonly Lazy<DirectoryReference> s_engineDirectory = new(() => DirectoryReference.Combine(RootDirectory, "Engine"))`
- L183 _public property_ `public static DirectoryReference EngineSourceDirectory => ...` — The full name of the Engine/Source directory
- L184 _private field_ `private static readonly Lazy<DirectoryReference> s_engineSourceDirectory = new(() => DirectoryReference.Combine(EngineDirectory, "Source"))`
- L189 _public property_ `public static DirectoryReference ApplicationSettingDirectory => ...` — Returns the Application Settings Directory path. This matches FPlatformProcess::ApplicationSettingsDir().
- L190 _private field_ `private static readonly Lazy<DirectoryReference> s_applicationSettingDirectory = new(GetApplicationSettingDirectory)`
- L195 _public property_ `public static DirectoryReference UserSettingDirectory => ...` — Returns the User Settings Directory path. This matches FPlatformProcess::UserSettingsDir().
- L196 _private field_ `private static readonly Lazy<DirectoryReference> s_userSettingDirectory = new(GetUserSettingDirectory)`
- L201 _public property_ `public static DirectoryReference? UserDirectory => ...` — Returns the User Directory path. This matches FPlatformProcess::UserDir().
- L202 _private field_ `private static readonly Lazy<DirectoryReference?> s_userDirectory = new(GetUserDirectory)`
- L207 _public property_ `public static DirectoryReference WritableEngineDirectory => ...` — Writable engine directory. Uses the user's settings folder for installed builds.
- L208 _private field_ `private static readonly Lazy<DirectoryReference> s_writableEngineDirectory = new(() => IsEngineInstalled() ? DirectoryReference.Combine(UserSettingDirectory, "UnrealEngine") : EngineDirectory)`
- L213 _public property_ `public static DirectoryReference EngineProgramSavedDirectory => ...` — The engine saved programs directory
- L214 _private field_ `private static readonly Lazy<DirectoryReference> s_engineProgramSavedDirectory = new(() => IsEngineInstalled() ? UserSettingDirectory : DirectoryReference.Combine(EngineDirectory, "Programs"))`
- L220 _public property_ `public static FileReference UnrealBuildToolPath => ...` — attrs: `[Obsolete("Deprecated in UE5.1; to launch UnrealBuildTool, use this dll as the first argument with DonetPath")]` — The path to UBT
- L225 _public property_ `public static FileReference UnrealBuildToolDllPath => ...` — The path to UBT
- L226 _private field_ `private static readonly Lazy<FileReference> s_unrealBuildToolDllPath = new(FindUnrealBuildToolDll)`
- L231 _public property_ `public static DirectoryReference DotnetDirectory => ...` — The directory containing the bundled .NET installation
- L232 _private field_ `private static readonly Lazy<DirectoryReference> s_dotnetDirectory = new(FindDotnetDirectory)`
- L237 _public property_ `public static FileReference DotnetPath => ...` — The path of the bundled dotnet executable
- L238 _private field_ `private static readonly Lazy<FileReference> s_dotnetPath = new(() => FileReference.Combine(DotnetDirectory, $"dotnet{RuntimePlatform.ExeExtension}"))`
- L243 _public property_ `public static Version DotnetVersion => ...` — The version of the bundled dotnet executable
- L244 _private field_ `private static readonly Lazy<Version> s_dotnetVersion = new(GetDotnetFileVersion)`
- L250 _public method_ `public static bool IsBuildMachine()` — Returns true if the application is running on a build machine
- L251 _private field_ `private static readonly Lazy<bool> s_isBuildMachine = new(() => String.Equals("1", Environment.GetEnvironmentVariable("IsBuildMachine")?.Trim(), StringComparison.Ordinal))`
- L257 _public method_ `public static bool IsEngineInstalled()` — Returns true if the application is running using installed Engine components
- L258 _private field_ `private static readonly Lazy<bool> s_isEngineInstalled = new(() => FileReference.Exists(FileReference.Combine(EngineDirectory, "Build", "InstalledBuild.txt")))`
- L263 _private field_ `private static readonly Lazy<FileReference?> s_installedProjectFile = new(() => { FileReference installedProjectLocationFile = FileReference.Combine(EngineDirectory, "Build", "InstalledProjectBuild.txt"); return FileReference.Exists(installedProjectLocationFile) ? FileR ...` — If we are running with an installed project, specifies the path to it
- L275 _public property_ `public static DirectoryReference OriginalCompilationRootDirectory => ...` — The original root directory that was used to compile the installed engine Used to remap source code paths when debugging.
- L276 _private field_ `private static readonly Lazy<DirectoryReference> s_originalCompilationRootDirectory = new(FindOriginalCompilationRootDirectory)`
- L283 _public method_ `public static DirectoryReference FindDotnetDirectoryForPlatform(RuntimePlatform.Type hostPlatform)` — Returns where another platform's Dotnet is located
- L289 _public method_ `public static bool IsProjectInstalled()` — Returns true if the application is running using an installed project (ie. a mod kit)
- L295 _public method_ `public static FileReference? GetInstalledProjectFile()` — Gets the installed project file
- L302-313 _public method_ `public static bool IsFileInstalled(FileReference file)` — Checks whether the given file is under an installed directory, and should not be overridden
- L315-347 _private method_ `private static DirectoryReference FindOriginalCompilationRootDirectory()`
- L359 _private field_ `private static readonly Lazy<HashSet<string>> s_iniPresentForPlatform = new(() => { HashSet<string> set = new(StringComparer.OrdinalIgnoreCase); foreach (DirectoryReference engineConfigDir in GetExtensionDirs(EngineDirectory, "Config", bIncludeRestrictedDirectories: false ...`
- L392 _private method_ `private static bool DataDrivenPlatformInfoIniIsPresent(string platformName)`
- L395 _private field_ `private static readonly ConcurrentDictionary<DirectoryReference, Lazy<(List<DirectoryReference>, List<DirectoryReference>)>> s_cachedExtensionDirectories = ...`
- L395 _private field_ `private static readonly ConcurrentDictionary< s_cachedExtensionDirectories = new()`
- L405-456 _public method_ `public static List<DirectoryReference> GetExtensionDirs(DirectoryReference baseDir, bool bIncludePlatformDirectories = true, bool bIncludeRestrictedDirectories = true, bool bIncludeBaseDirectory = true)` — Finds all the extension directories for the given base directory. This includes platform extensions and restricted folders.
- L467-472 _public method_ `public static List<DirectoryReference> GetExtensionDirs(DirectoryReference baseDir, string subDir, bool bIncludePlatformDirectories = true, bool bIncludeRestrictedDirectories = true, bool bIncludeBaseDirectory = true)` — Finds all the extension directories for the given base directory. This includes platform extensions and restricted folders.f
- L477 _private method_ `private static DirectoryReference GetApplicationSettingDirectory()` — Returns the Application Settings Directory path. This matches FPlatformProcess::ApplicationSettingsDir().
- L485-510 _private method_ `private static DirectoryReference GetUserSettingDirectory()` — Returns the User Settings Directory path. This matches FPlatformProcess::UserSettingsDir().
- L515-526 _private method_ `private static DirectoryReference? GetUserDirectory()` — Returns the User Directory path. This matches FPlatformProcess::UserDir().
- L531 _public property_ `public static string MachineName => ...` — The current Machine name
- L532 _private field_ `private static readonly Lazy<string> s_machineName = new(() => { try { string machineName = System.Net.Dns.GetHostName(); if (OperatingSystem.IsMacOS() && machineName.EndsWith(".local", StringComparison.OrdinalIgnoreCase)) { machineName = machineName.Re ...`

#### class `UnrealBuildBase.Unreal.LocationOverride`  
`public static class LocationOverride`  
_public; L349-355_
- L354 _public property_ `public static DirectoryReference? RootDirectory { get; set; }` — If set, this value will be used to populate Unreal.RootDirectory
