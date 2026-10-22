# CSharp / Win.Automation

- project root: `Source/Programs/AutomationTool/Win`
- files: 10; symbols: 229
- symbol kinds: class=16, const=5, ctor=11, delegate=1, enum=1, enumerator=4, field=35, method=132, property=24
- access marked `*` is implicit (not written in source)

### `Source/Programs/AutomationTool/Win/MSGaming/MSGameStoreCustomDeploymentHandler.cs` (Win.Automation)


#### class `MSGameStoreCustomDeploymentHandler`  
`public class MSGameStoreCustomDeploymentHandler : CustomDeploymentHandler`  
_public; L21-380_
- attrs: `[CustomDeploymentHandlerAttribute("MSGameStore")]`
- inherits: `CustomDeploymentHandler`
- L23 _protected property_ `protected virtual string IniSection_TargetSettings => ...`
- L25 _protected property_ `protected static int GDKEdition => ...`
- L27 _protected property_ `protected static string GDKBinariesDir => ...`
- L29-41 _public ctor_ `public MSGameStoreCustomDeploymentHandler(Platform AutomationPlatform, ProjectParams Params, DeploymentContext SC) : base(AutomationPlatform, Params, SC)`
- L43-46 _public method_ `public override bool SupportsPlatform(UnrealTargetPlatform Platform)`
- L48-63 _public method_ `public override bool GetPlatformPakCommandLine(ProjectParams Params, DeploymentContext SC, ref string CmdLine)`
- L65-70 _public method_ `public override bool GetPlatformIoStoreCommandLine(ProjectParams Params, DeploymentContext SC, ref string CmdLine)`
- L72-76 _public method_ `public override bool? GetPlatformPatchesWithDiffPak(ProjectParams Params, DeploymentContext SC)`
- L78-95 _public method_ `public override bool PostStagingFileCopy(ProjectParams Params, DeploymentContext SC)`
- L98-103 _public method_ `public override void PostPackage(ProjectParams Params, DeploymentContext SC, int WorkingCL)`
- L106-195 _public method_ `public override bool Deploy(ProjectParams Params, DeploymentContext SC)` — attrs: `[SupportedOSPlatform("windows")]`
- L199-261 _public method_ `public override IProcessResult RunClient(ERunOptions ClientRunFlags, string ClientApp, string ClientCmdLine, ProjectParams Params, DeploymentContext SC)` — attrs: `[SupportedOSPlatform("windows")]`
- L264-284 _public method_ `public override bool PreGetFilesToDeployOrStage(ProjectParams Params, DeploymentContext SC)`
- L286-293 _public method_ `public override void PostGetFilesToDeployOrStage(ProjectParams Params, DeploymentContext SC)`
- L295-304 _public method_ `public override bool GetFilesToStageForDLC(ProjectParams Params, DeploymentContext SC)`
- L306-322 _public method_ `public override bool GetFilesToArchive(ProjectParams Params, DeploymentContext SC)`
- L324-333 _private method_ `private bool IsRemoteDevice(ProjectParams Params, DeploymentContext SC)`
- L336-344 _protected method_ `protected bool ExecuteSDKCommand(string Command, string CommandLine)`
- L346-351 _protected method_ `protected string ExecuteSDKCommandAndGetOutput(string Command, string CommandLine)`
- L355-378 _private method_ `private static void VerifyWindowsEnvironment()` — attrs: `[SupportedOSPlatform("windows")]`

### `Source/Programs/AutomationTool/Win/MSGaming/MSGameStoreCustomStagingHandler.cs` (Win.Automation)


#### class `MSGameStoreCustomStagingHandler`  
`public class MSGameStoreCustomStagingHandler : CustomStagingHandler`  
_public; L17-331_
- attrs: `[SupportedOSPlatform("windows")]`
- inherits: `CustomStagingHandler`
- L19 _protected property_ `protected virtual string IniSection_TargetSettings => ...`
- L21 _protected property_ `protected static int GDKEdition => ...`
- L23 _protected property_ `protected static string GDKBinariesDir => ...`
- L25 _private field_ `private bool bAutoGeneratePackage = true`
- L28-75 _protected method_ `protected override bool TryInitialize(ProjectParams Params, DeploymentContext SC)`
- L78-99 _public method_ `public override void GetFilesToStage(ProjectParams Params, DeploymentContext SC)`
- L101-120 _public method_ `public override void PostStagingFileCopy(ProjectParams Params, DeploymentContext SC)`
- L123-134 _public method_ `public override void Package(ProjectParams Params, DeploymentContext SC, int WorkingCL)`
- L136-149 _public method_ `public override void GetFilesToArchive(ProjectParams Params, DeploymentContext SC)`
- L153-224 _public method_ `public override bool TryDeploy(ProjectParams Params, DeploymentContext SC)`
- L227-264 _public method_ `public override IProcessResult TryRunClient(CommandUtils.ERunOptions ClientRunFlags, string ClientApp, string ClientCmdLine, ProjectParams Params, DeploymentContext SC)`
- L267-270 _private method_ `private static DirectoryReference GetPackageMetadataBasePath(DeploymentContext SC)`
- L272-275 _private method_ `private static string GetPackageOutputPathFragment(DeploymentContext SC)`
- L277-287 _private method_ `private GDKInstalledApp GetInstalledApp(string PackageFamilyName)`
- L289-297 _protected method_ `protected bool ExecuteSDKCommand(string Command, string CommandLine)`
- L299-304 _protected method_ `protected string ExecuteSDKCommandAndGetOutput(string Command, string CommandLine)`
- L306-329 _private method_ `private static void VerifyWindowsEnvironment()`

### `Source/Programs/AutomationTool/Win/MSGaming/MSGameStorePackageGenerator.cs` (Win.Automation)


#### class `AutomationUtils.GDK.MSGameStorePackageGenerator`  
`public class MSGameStorePackageGenerator : GDKPackageGenerator`  
_public; L15-202_
- inherits: `GDKPackageGenerator`
- L17 _private* field_ `UnrealTargetPlatform? CrashReportPlatform`
- L18-22 _public ctor_ `public MSGameStorePackageGenerator(FileReference InProjectPath, UnrealTargetPlatform InPlatformType, string InIniSection_TargetSettings, string CustomConfig, UnrealTargetPlatform? InCrashReportPlatform) : base(InProjectPath, InPlatformType, InIniSection_TargetSettings, CustomConfig)`
- L24-27 _protected method_ `protected override string GetPlatformSpecificPackageCommandlineOptions(ProjectParams Params, DeploymentContext SC, string DLCPackage)`
- L29-36 _protected method_ `protected override void GetPlatformSpecificPackageSymbolPaths(HashSet<string> SymbolPaths, ProjectParams Params, DeploymentContext SC)`
- L38-41 _public method_ `public override string GetPlatformPackageFileExtension()`
- L43-60 _protected method_ `protected override bool ShouldPackageFile(FileReference SrcFile, ProjectParams Params, DeploymentContext SC, UnrealTargetConfiguration? OnlyConfig = null)`
- L62-94 _protected method_ `protected override IEnumerable<StagedFileReference> GetPlatformFilesToPackage(ProjectParams Params, DeploymentContext SC, DirectoryReference PackageMetadataDir, UnrealTargetConfiguration? OnlyConfig)`
- L97-101 _protected method_ `protected override void PackageInternal(ProjectParams Params, DeploymentContext SC, DirectoryReference PackagePath, FileReference LayoutPath, DirectoryReference SourceFolder, ILogger Logger, string DLCPackage, UnrealTargetConfiguration? OnlyConfig = null, string PackageOutputPathFragment = "")`
- L103-168 _private method_ `private void GenerateInstallBatchFile(DirectoryReference OutputPath, ProjectParams Params, DeploymentContext SC, bool bIsDLC)`
- L173 _private field_ `private static readonly Dictionary<string, string> ModFolderWarningsToSuppress = ...`
- L173 _private field_ `private static readonly Dictionary< ModFolderWarningsToSuppress = new Dictionary<string, string>() { { "Warning: Most PC gaming customers expect their applications to be modifiable.", "Most PC gaming customers expect their applications to be modifiable." }, }`
- L178 _private field_ `private static readonly Dictionary<string, string> MissingPDBWarningsToSuppress = ...`
- L178 _private field_ `private static readonly Dictionary< MissingPDBWarningsToSuppress = new Dictionary<string, string>() { {"(?<msg>Warning: Symbol file not found for.*WinPixEventRuntime.dll.*)", "" }, }`
- L183-198 _protected method_ `protected override void PrepareMessageFilterForMakePkg(SpewFilterHelper Filter, ConfigHierarchy EngineIni, ProjectParams Params, DeploymentContext SC)`

### `Source/Programs/AutomationTool/Win/MSGaming/MSGameStorePlatformCheck.cs` (Win.Automation)


#### class `BuildScripts.Automation.MSGameStorePlatformCheck`  
`public class MSGameStorePlatformCheck : BuildCommand`  
_public; L9-51_
- inherits: `BuildCommand`
- L11-50 _public method_ `public override void ExecuteBuild()`

### `Source/Programs/AutomationTool/Win/MSGaming/MSGamingRuntimeCustomStagingHandler.cs` (Win.Automation)


#### class `MSGamingRuntimeCustomStagingHandler`  
`public class MSGamingRuntimeCustomStagingHandler : CustomStagingHandler`  
_public; L12-96_
- attrs: `[SupportedOSPlatform("windows")]`
- inherits: `CustomStagingHandler`
- L14 _protected property_ `protected virtual string IniSection_TargetSettings => ...`
- L16 _protected property_ `protected static int GDKEdition => ...`
- L18 _protected property_ `protected static string GDKBinariesDir => ...`
- L20 _private field_ `private bool bAutoGenerateStagingManifest = true`
- L23-70 _protected method_ `protected override bool TryInitialize(ProjectParams Params, DeploymentContext SC)`
- L73-83 _public method_ `public override void GetFilesToStage(ProjectParams Params, DeploymentContext SC)`
- L85-95 _public method_ `public override void GetFilesToStageForDLC(ProjectParams Params, DeploymentContext SC)`

### `Source/Programs/AutomationTool/Win/Properties/AssemblyInfo.cs` (Win.Automation)
_(no declarations)_


### `Source/Programs/AutomationTool/Win/RemoteWinSupport.cs` (Win.Automation)


#### class `RemoteWinSupport`  
`public static class RemoteWinSupport`  
_public; L35-533_
- L37 _public field_ `public static readonly string DeviceType = "RemoteWin"`
- L38 _private property_ `private static string WdRemotePath => ...`
- L40-43 _public method_ `public static bool IsAvailable()`
- L45-48 _public method_ `public static bool IsRemoteDevice( string DeviceName, UnrealTargetPlatform Platform )`
- L50-63 _public method_ `public static List<string> GetAllRemoteDeviceNames(UnrealTargetPlatform Platform)`
- L65-76 _public method_ `public static List<DeviceInfo> GetDevices(UnrealTargetPlatform Platform)`
- L78-90 _public method_ `public static bool Deploy( string DeviceName, string SourcePath, string DestinationPath )`
- L92-103 _public method_ `public static bool Run(string DeviceName, string RemoteExecutablePath, string ClientCmdLine)`
- L105-108 _public method_ `public static bool Kill(string DeviceName)`
- L110-133 _public method_ `public static bool Deploy(UnrealTargetPlatform Platform, ProjectParams Params, DeploymentContext SC)`
- L135-177 _public method_ `public static IProcessResult RunClient(UnrealTargetPlatform Platform, ERunOptions ClientRunFlags, string ClientApp, string ClientCmdLine, ProjectParams Params)`
- L179-192 _private method_ `private static string GetRemoteExecutablePath(UnrealTargetPlatform Platform, string ClientApp, ProjectParams Params)`
- L195-244 _private method_ `private static string SanitizeCommandLine(string ClientCmdLine)`
- L246-255 _public method_ `public static string GetTargetDeviceName(string DeviceName)`
- L257-281 _private method_ `private static UnrealTargetPlatform GetTargetDevicePlatform(string DeviceName, UnrealTargetPlatform DefaultPlatform)`
- L283-300 _private method_ `private static string GetDestinationRoot(UnrealTargetPlatform Platform, ProjectParams Params)`
- L303-319 _internal method_ `internal static bool RunWdRemote( string Parameters, string Device )`

#### class `RemoteWinSupport.Placeholder_RemoteWinProcessMonitor`  
`public class Placeholder_RemoteWinProcessMonitor`  
_public; L332-446_
- L334 _public field_ `public Action<string> OutputReceived`
- L337-359 _public ctor_ `public Placeholder_RemoteWinProcessMonitor( string InDeviceName, ILogger InLogger = null )`
- L361-368 _public method_ `public void Start()`
- L369-376 _public method_ `public void Stop()`
- L378-384 _public method_ `public void WaitForExit()`
- L386-428 _private method_ `private async void RunServerThread()`
- L430 _public property_ `public bool DidLaunch => ...`
- L431 _public property_ `public bool IsAvailable { get; set; }`
- L432 _public property_ `public string ServerAddress { get; set; }`
- L434 _private const_ `private const int LaunchTimeoutSeconds = 20`
- L435 _private const_ `private const int HeartbeatTimeutSeconds = 10`
- L436 _private const_ `private const bool bNoTimeout = false`
- L438 _private field_ `private readonly string DeviceName`
- L439 _private field_ `private readonly ILogger Logger`
- L440 _private field_ `private readonly TcpListener Listener`
- L441 _private field_ `private readonly Thread ListenThread`
- L442 _private* field_ `CancellationTokenSource LaunchCTS`
- L443 _private field_ `private bool bHadRemoteConnection = false`

#### class `RemoteWinSupport.RemoteWinProcessResult`  
`private class RemoteWinProcessResult : IProcessResult`  
_private; L452-530_
- inherits: `IProcessResult`
- L454 _private field_ `private readonly string DeviceName`
- L455 _private field_ `private readonly string ProcessName`
- L456 _private field_ `private readonly Placeholder_RemoteWinProcessMonitor ProcessMonitor`
- L457 _private field_ `private readonly bool bLogToConsole`
- L458 _private field_ `private readonly bool bLogToBuffer`
- L460-479 _public ctor_ `public RemoteWinProcessResult(string InDeviceName, string InProcessName, Placeholder_RemoteWinProcessMonitor InProcessMonitor, ERunOptions RunOptions)`
- L481-491 _private method_ `private void OnOutputReceived( string Line )`
- L493-498 _public method_ `public void StopProcess(bool KillDescendants = true)`
- L500 _public property_ `public bool HasExited => ...`
- L501 _public method_ `public string GetProcessName()`
- L502 _public method_ `public void OnProcessExited()`
- L503 _public method_ `public void DisposeProcess()`
- L504 _public method_ `public void StdOut(object sender, DataReceivedEventArgs e)`
- L505 _public method_ `public void StdErr(object sender, DataReceivedEventArgs e)`
- L506 _public property_ `public int ExitCode { get; set; }`
- L507 _public property_ `public bool bExitCodeSuccess => ...`
- L508 _public property_ `public string Output { get; set; }`
- L509 _public property_ `public Process ProcessObject => ...`
- L510 _public method_ `public new string ToString()`
- L512-519 _public method_ `public void WaitForExit()`
- L521-529 _public method_ `public FileReference WriteOutputToFile(string FileName)`

### `Source/Programs/AutomationTool/Win/Tasks/SrcSrvTask.cs` (Win.Automation)


#### class `Win.Automation.SrcSrvTaskParameters`  
`public class SrcSrvTaskParameters`  
_public; L19-59_
- desc: Parameters for a task that adds source indexing information to symbol files (PDB).
- L25 _public field_ `public string BinaryFiles` — attrs: `[TaskParameter]` — List of output files. PDBs will be extracted from this list.
- L31 _public field_ `public string SourceFiles` — attrs: `[TaskParameter]` — List of source files to index and embed into the PDBs.
- L37 _public field_ `public string Branch` — attrs: `[TaskParameter]` — Branch to base all the depot source files from
- L43 _public field_ `public int Change` — attrs: `[TaskParameter]` — Changelist to sync files from
- L58 _public property_ `public string VFSMapping { get; set; }` — attrs: `[TaskParameter(Optional = true)]` — List of file path mappings to be applied during source indexing. It is needed only when using VFS (Virtual File System) feature when compiling the binary. VFS replaces the real local paths used with standardized paths like Z:\UEVFS\... Since these virtualized paths don't match paths used by the local workspace, we need to map them manually so that paths in object files/symbols matched the data we have in source indexing. It's a semicolon-separated list of path assignments e.g. "[Root]\Samples\Games\SampleGame=Z:\UEVFS\SampleGame;[Root]=Z:\UEVFS\Root" [Root] will be replaced with Unreal.RootDirectory. You need to ensure that the mapping used here matches the conventions used by Unreal Build Tool. We may improve it in the future but current the VFS mapping used during compilation is not available outside of UBT.

#### class `Win.Automation.SrcSrvTask`  
`public class SrcSrvTask : CustomTask`  
_public; L70-142_
- attrs: `[TaskElement("SrcSrv", typeof(SrcSrvTaskParameters))]`
- inherits: `CustomTask`
- desc: Task which strips symbols from a set of files Note that this task only supports source indexing for Windows-like platforms. SymStore can be considered a generalization of this task because in addition to uploading symbols it can also index sources and supports consoles as well (any missing platform that supports source indexing in general may add support for it by extending PublishSymbols). Check SymStoreTaskParameters.IndexSources/SourceFiles/Branch/Change
- L75 _private* field_ `SrcSrvTaskParameters Parameters` — Parameters for this task
- L81-84 _public ctor_ `public SrcSrvTask(SrcSrvTaskParameters InParameters)` — Construct a spawn task
- L93-98 _public method_ `public override void Execute(JobContext Job, HashSet<FileReference> BuildProducts, Dictionary<string, HashSet<FileReference>> TagNameToFileSet)` — attrs: `[SupportedOSPlatform("windows")]` — Execute the task.
- L101-108 _internal method_ `internal static void Execute(FileReference[] BinaryFiles, FileReference[] SourceFiles, string Branch, int Change, string VFSMapping)` — attrs: `[SupportedOSPlatform("windows")]`
- L113-116 _public method_ `public override void Write(XmlWriter Writer)` — Output this task out to an XML writer.
- L122-132 _public method_ `public override IEnumerable<string> FindConsumedTagNames()` — Find all the tags which are used as inputs to this task
- L138-141 _public method_ `public override IEnumerable<string> FindProducedTagNames()` — Find all the tags which are modified by this task

#### class `Win.Automation.BgStateExtensions`  
`public static partial class BgStateExtensions`  
_public; L144-162_
- L158-161 _public method_ `public static void SrcSrv(this BgContext State, HashSet<FileReference> BinaryFiles, HashSet<FileReference> SourceFiles, string Branch, int Change, string VFSMapping)` — attrs: `[SupportedOSPlatform("windows")]` — Add source indexing information to symbol files (PDB).

### `Source/Programs/AutomationTool/Win/WinPlatform.Automation.cs` (Win.Automation)


#### class `Win64Platform`  
`public class Win64Platform : Platform`  
_public; L23-1079_
- inherits: `Platform`
- L25-28 _public ctor_ `public Win64Platform() : base(UnrealTargetPlatform.Win64)`
- L30-33 _protected ctor_ `protected Win64Platform(UnrealTargetPlatform PlatformType) : base(PlatformType)`
- L35-51 _public method_ `public override DeviceInfo[] GetDevices()`
- L53-64 _public method_ `public override void Deploy(ProjectParams Params, DeploymentContext SC)`
- L66-78 _public method_ `public override IProcessResult RunClient(ERunOptions ClientRunFlags, string ClientApp, string ClientCmdLine, ProjectParams Params)`
- L80-83 _protected method_ `protected override string GetPlatformExeExtension()`
- L85 _public property_ `public override bool IsSupported { get; }`
- L87-90 _public property_ `public virtual UnrealTargetPlatform? BootstrapExePlatform { get; }`
- L93-223 _public method_ `public override void GetFilesToDeployOrStage(ProjectParams Params, DeploymentContext SC)`
- L228-240 _protected method_ `protected bool ShouldStageGameInputWindowsRedist(DeploymentContext SC)`
- L242-251 _protected method_ `protected void StageGameInputWindowsRedist(DeploymentContext SC)`
- L253-255 _public method_ `public override void ExtractPackage(ProjectParams Params, string SourcePath, string DestinationPath)`
- L257-261 _public method_ `public override void GetTargetFile(string RemoteFilePath, string LocalFile, ProjectParams Params)`
- L263-352 _private* method_ `void StageBootstrapExecutable(DeploymentContext SC, string ExeName, FileReference TargetFile, StagedFileReference StagedRelativeTargetPath, string StagedArguments, Dictionary<UnrealArch,StagedFileReference> PerArchitectureStagedRelativeTargetPath = null)`
- L354-372 _public method_ `public override string GetCookPlatform(bool bDedicatedServer, bool bIsClientOnly)`
- L374-377 _public method_ `public override string GetEditorCookPlatform()`
- L379-391 _public method_ `public override string GetPlatformPakCommandLine(ProjectParams Params, DeploymentContext SC)`
- L393-421 _public method_ `public override void Package(ProjectParams Params, DeploymentContext SC, int WorkingCL)`
- L423-426 _public property_ `public override bool UseAbsLog { get; }`
- L428-435 _public method_ `public override bool CanHostPlatform(UnrealTargetPlatform Platform)`
- L437-440 _public method_ `public override bool ShouldStageCommandLine(ProjectParams Params, DeploymentContext SC)`
- L442-445 _public method_ `public override List<string> GetDebugFileExtensions()`
- L447-463 _public method_ `public override CustomDeploymentHandler GetCustomDeploymentHandler(ProjectParams Params, DeploymentContext SC)`
- L465-472 _public method_ `public override bool SignExecutables(DeploymentContext SC, ProjectParams Params)`
- L474-506 _public method_ `public void StageAppLocalDependencies(ProjectParams Params, DeploymentContext SC, string SourcePlatformDir, UnrealArch Architecture)`
- L508-529 _private* method_ `static void StageAppLocalDependenciesToDir(DeploymentContext SC, DirectoryReference BaseAppLocalDependenciesPath, UnrealArch Architecture, StagedDirectoryReference StagedBinariesDir)`
- L532-569 _public method_ `public void UpdateStagedSxSManifest( DeploymentContext SC, UnrealArch Architecture, StagedDirectoryReference StagedBinariesDir)`
- L572-582 _public method_ `public override void PostStagingFileCopy(ProjectParams Params, DeploymentContext SC)`
- L590-619 _private method_ `private static FileReference GetSymStoreExe()` — attrs: `[SupportedOSPlatform("windows")]` — Try to get the symstore.exe path from the given Windows SDK version
- L622-656 _public method_ `public static bool TryGetPdbCopyLocation(out FileReference OutLocation)` — attrs: `[SupportedOSPlatform("windows")]`
- L659-689 _public method_ `public override void StripSymbols(FileReference SourceFile, FileReference TargetFile)` — attrs: `[SupportedOSPlatform("windows")]`
- L692-833 _public method_ `public override bool PublishSymbols(DirectoryReference SymbolStoreDirectory, List<FileReference> Files, bool bIndexSources, List<FileReference> SourceFiles, string Product, string Branch, int Change, string BuildVersion = null, string VFSMapping = null)` — attrs: `[SupportedOSPlatform("windows")]`
- L836-884 _private method_ `private IEnumerable<FileReference> CopySymbolsWithSourceIndexing(DirectoryReference TargetDirectory, IEnumerable<FileReference> SymbolFiles, IEnumerable<FileReference> SourceFiles, string Branch, int Change, string VFSMapping)` — attrs: `[SupportedOSPlatform("windows")]`
- L886-897 _private* method_ `bool IsSymbolFile(FileReference File)`
- L908-971 _public method_ `public void AddSourceIndexToSymbols(IEnumerable<FileReference> PdbFiles, IEnumerable<FileReference> SourceFiles, string Branch, int Change, string VFSMappingString)` — attrs: `[SupportedOSPlatform("windows")]`
- L981-1020 _private* method_ `static void ExecutePdbStrTool(FileReference PdbStrExe, FileReference PdbFile, FileReference SrcSrvIni, ParallelLoopState State)` — Executes the PdbStr tool.
- L1027-1057 _private* method_ `static FileReference GetPdbStrExe()` — attrs: `[SupportedOSPlatform("windows")]` — Try to get the pdbstr.exe path from the Windows SDK
- L1059-1069 _public property_ `public override string[] SymbolServerDirectoryStructure { get; }`
- L1072-1078 _public property_ `public override bool SymbolServerRequiresLock { get; }`

### `Source/Programs/AutomationTool/Win/WinResources.cs` (Win.Automation)


#### enum `ResourceType`  
`public enum ResourceType`  
_public; L10-16_
- L12 _public* enumerator_ `Icon = 3`
- L13 _public* enumerator_ `RawData = 10`
- L14 _public* enumerator_ `GroupIcon = 14`
- L15 _public* enumerator_ `Version = 16`

#### class `IconResource`  
`public class IconResource`  
_public; L18-41_
- L20 _public field_ `public byte Width`
- L21 _public field_ `public byte Height`
- L22 _public field_ `public byte ColorCount`
- L23 _public field_ `public ushort Planes`
- L24 _public field_ `public ushort BitCount`
- L25 _public field_ `public byte[] Data`
- L27-35 _public ctor_ `public IconResource(byte InWidth, byte InHeight, byte InColorCount, ushort InPlanes, ushort InBitCount, byte[] InData)`
- L37-40 _public method_ `public override string ToString()`

#### class `GroupIconResource`  
`public class GroupIconResource`  
_public; L43-161_
- L45 _public field_ `public IconResource[] Icons`
- L47-50 _public ctor_ `public GroupIconResource(IconResource[] InIcons)`
- L52-79 _public method_ `public static GroupIconResource FromIco(string FileName)`
- L81-88 _public method_ `public static GroupIconResource FromExe(string FileName)`
- L90-116 _public method_ `public static GroupIconResource FromByteArray(byte[] GroupData, ModuleResourceLibary Module)`
- L118-136 _public method_ `public byte[] ToByteArray()`
- L138-149 _public method_ `public static IconResource ReadIconHeader(BinaryReader Reader)`
- L151-160 _public method_ `public void WriteIconHeader(BinaryWriter Writer, IconResource Icon)`

#### class `ModuleResourceLibary`  
`public class ModuleResourceLibary : IDisposable`  
_public; L163-228_
- inherits: `IDisposable`
- L165 _private* const_ `const uint LOAD_LIBRARY_AS_DATAFILE = 0x00000002`
- L167 _private* delegate_ `delegate bool EnumResourceNamesDelegate(IntPtr ModuleHandle, IntPtr Type, IntPtr Name, IntPtr Param)`
- L170 _private* method_ `extern static IntPtr LoadLibraryEx(string FileName, IntPtr FileHandle, uint Flags)` — attrs: `[DllImport("kernel32.dll", SetLastError=true)]`
- L173 _private* method_ `extern static bool FreeLibrary(IntPtr Handle)` — attrs: `[DllImport("kernel32.dll", SetLastError=true)]`
- L176 _private* method_ `static extern bool EnumResourceNames(IntPtr ModuleHandle, IntPtr Type, EnumResourceNamesDelegate EnumDelegate, IntPtr Param)` — attrs: `[DllImport("kernel32.dll", SetLastError=true)]`
- L179 _private* method_ `static extern IntPtr FindResource(IntPtr ModuleHandle, IntPtr Name, IntPtr Type)` — attrs: `[DllImport("kernel32.dll", SetLastError=true)]`
- L182 _private* method_ `static extern IntPtr LoadResource(IntPtr ModuleHandle, IntPtr ResourceHandle)` — attrs: `[DllImport("kernel32.dll", SetLastError=true)]`
- L185 _private* method_ `static extern IntPtr LockResource(IntPtr ResourceDataHandle)` — attrs: `[DllImport("kernel32.dll", SetLastError=true)]`
- L188 _private* method_ `static extern uint SizeofResource(IntPtr ModuleHandle, IntPtr ResourceDataHandle)` — attrs: `[DllImport("kernel32.dll", SetLastError=true)]`
- L190 _private* field_ `IntPtr ModuleHandle`
- L192-195 _public ctor_ `public ModuleResourceLibary(string FileName)`
- L197-200 _public method_ `public void Dispose()`
- L202-205 _public method_ `public byte[] ReadResource(int ResourceId, ResourceType Type)`
- L207-212 _public method_ `public byte[] ReadFirstResource(ResourceType Type)`
- L214-227 _private* method_ `byte[] ReadResourceInternal(IntPtr Name, IntPtr Type)`

#### class `ModuleResourceUpdate`  
`public class ModuleResourceUpdate : IDisposable`  
_public; L230-292_
- inherits: `IDisposable`
- L233 _private* method_ `static extern IntPtr BeginUpdateResource(string pFileName, [MarshalAs(UnmanagedType.Bool)]bool bDeleteExistingResources)` — attrs: `[DllImport("kernel32.dll", SetLastError=true)]`
- L236 _private* method_ `static extern bool UpdateResource(IntPtr hUpdate, IntPtr lpType, IntPtr lpName, ushort wLanguage, IntPtr lpData, uint cbData)` — attrs: `[DllImport("kernel32.dll", SetLastError=true)]`
- L239 _private* method_ `static extern bool EndUpdateResource(IntPtr hUpdate, bool fDiscard)` — attrs: `[DllImport("kernel32.dll", SetLastError=true)]`
- L241 _private* const_ `const ushort DefaultLanguage = 1033`
- L243 _private* field_ `IntPtr UpdateHandle`
- L244 _private* field_ `List<IntPtr> UnmanagedPointers = new List<IntPtr>()`
- L246-250 _public ctor_ `public ModuleResourceUpdate(string OutputFile, bool bRemoveExisting)`
- L252-267 _public method_ `public void SetData(int ResourceId, ResourceType Type, byte[] Data)`
- L269-279 _public method_ `public void SetIcons(int ResourceId, GroupIconResource GroupIcon)`
- L281-291 _public method_ `public void Dispose()`
