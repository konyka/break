# CSharp / IOS.Automation

- project root: `Source/Programs/AutomationTool/IOS`
- files: 7; symbols: 154
- symbol kinds: class=9, ctor=7, enum=1, enumerator=4, field=18, method=87, property=28
- access marked `*` is implicit (not written in source)

### `Source/Programs/AutomationTool/IOS/AppleOnWindowsAppMaker.cs` (IOS.Automation)


#### class `IOS.Automation.AppleOnWindowsAppMaker`  
`public class AppleOnWindowsAppMaker`  
_public; L20-918_
- L22-37 _public method_ `public static FileReference GetTargetReceiptFileName(UnrealTargetConfiguration Config, string InExecutablePath, DirectoryReference InEngineDir, DirectoryReference InProjectDirectory, FileReference ProjectFile, bool bIsUEGame)`
- L39-48 _private* method_ `static string MakeIPAFileName(UnrealTargetConfiguration TargetConfiguration, ProjectParams Params, DeploymentContext SC, bool bAllowDistroPrefix, string PlatformName)`
- L50-67 _public method_ `public static string GetStagedIPAPath(ProjectParams Params, DeploymentContext SC, string PlatformName)`
- L69-248 _public method_ `public static void GetFilesToArchive(ProjectParams Params, DeploymentContext SC, ILogger Logger, string PlatformName)`
- L250-257 _private method_ `private static void StageStandardLaunchScreenStoryboard(ProjectParams Params, DeploymentContext SC)`
- L259-302 _private method_ `private static void StageCustomLaunchScreenStoryboard(ProjectParams Params, DeploymentContext SC, ILogger Logger)`
- L304-321 _private method_ `private static void StageLaunchScreenStoryboard(ProjectParams Params, DeploymentContext SC, ILogger Logger)`
- L323-342 _private method_ `private static bool IsBuiltAsFramework(ProjectParams Params, DeploymentContext SC, UnrealTargetPlatform TargetPlatformType)`
- L344-359 _private method_ `private static bool ShouldUseMaxIPACompression(ProjectParams Params)`
- L361-496 _private method_ `private static void PackageIPA(ProjectParams Params, string ProjectGameExeFilename, DeploymentContext SC, string PlatformName)`
- L498-527 _private method_ `private static void WriteEntitlements(ProjectParams Params, DeploymentContext SC, UnrealTargetPlatform PlatTargetPlatformType)`
- L529-566 _private method_ `private static string EnsureXcodeProjectExists(FileReference RawProjectPath, string LocalRoot, string ShortProjectName, string ProjectRoot, bool IsCodeBasedProject, out bool bWasGenerated, string PlatformName)`
- L568-633 _public method_ `public static void CodeSign(IOSPlatform PlatformContext, string BaseDirectory, string GameName, FileReference RawProjectPath, UnrealTargetConfiguration TargetConfig, string LocalRoot, string ProjectName, string ProjectDirectory, bool IsCode, bool Distribution, string Provision, string Certificate, string Team, bool bAutomaticSigning, string SchemeName, string SchemeConfiguration, ILogger Logger)`
- L635-641 _private* method_ `static void RunIPP(string IPPArguments, ILogger Logger)`
- L643-916 _public method_ `public static void Package(IOSPlatform PlatformContext, ProjectParams Params, DeploymentContext SC, int WorkingCL, ILogger Logger)`

### `Source/Programs/AutomationTool/IOS/ExportIPAFromArchive.cs` (IOS.Automation)


#### class `ExportIPAFromArchive`  
`public class ExportIPAFromArchive : BuildCommand`  
_public; L19-181_
- attrs: `[Help(@"Creates an IPA from an xarchive file")] [Help("method=<method>", @"Purpose of the IPA. (Development, Adhoc, Store)")] [Help("TemplateFile=<file>", @"Path to plist template that will be filled in based on other arguments. See ExportOptions.plist.template for an example")] [Help("OptionsFile", @"Path to an XML file of options that we'll select from based on method. See ExportOptions.Values.x`
- inherits: `BuildCommand`
- L21 _public property_ `public string TemplateFile { get; set; }`
- L22 _public property_ `public string OptionsFile { get; set; }`
- L23 _public property_ `public string Project { get; set; }`
- L24 _public property_ `public string Method { get; set; }`
- L25 _public property_ `public string Archive { get; set; }`
- L26 _public property_ `public string Output { get; set; }`
- L28-31 _public ctor_ `public ExportIPAFromArchive()`
- L33-44 _private* method_ `string SelectPropertyTextOrDie(XmlDocument Doc, string InProperty, string InName)`
- L46-67 _protected method_ `protected void CreateExportPlist(string OutputPath)`
- L69-75 _private* method_ `int XcodeBuild(string Arguments)`
- L77-180 _public method_ `public override ExitCode Execute()`

### `Source/Programs/AutomationTool/IOS/IOSPlatform.Automation.cs` (IOS.Automation)


#### class `IOSEnvVarNames`  
`static class IOSEnvVarNames`  
_internal*; L21-25_
- L24 _public field_ `static public readonly string CodeSignWhenStaging = "uebp_CodeSignWhenStaging"`

#### class `IOSClientProcess`  
`class IOSClientProcess : IProcessResult`  
_internal*; L27-158_
- inherits: `IProcessResult`
- L29 _private field_ `private IProcessResult childProcess`
- L30 _private field_ `private Thread consoleLogWorker`
- L33-41 _public ctor_ `public IOSClientProcess(IProcessResult inChildProcess, string inDeviceID)`
- L43-47 _public method_ `public void StopProcess(bool KillDescendants = true)`
- L49-62 _public property_ `public bool HasExited { get; }`
- L64-67 _public method_ `public string GetProcessName()`
- L69-73 _public method_ `public void OnProcessExited()`
- L75-78 _public method_ `public void DisposeProcess()`
- L80-83 _public method_ `public void StdOut(object sender, DataReceivedEventArgs e)`
- L85-88 _public method_ `public void StdErr(object sender, DataReceivedEventArgs e)`
- L90-94 _public property_ `public int ExitCode { get; set; }`
- L96 _public property_ `public bool bExitCodeSuccess => ...`
- L98-101 _public property_ `public string Output { get; }`
- L103-106 _public property_ `public Process ProcessObject { get; }`
- L108-111 _public method_ `public new string ToString()`
- L113-116 _public method_ `public void WaitForExit()`
- L118-121 _public method_ `public FileReference WriteOutputToFile(string FileName)`
- L123-127 _private method_ `private void StopConsoleOutput()`
- L129-156 _public method_ `public void ProcessConsoleOutput(string inDeviceID)`

#### class `IOSPlatform`  
`public class IOSPlatform : ApplePlatform`  
_public; L160-1942_
- inherits: `ApplePlatform`
- L170 _private property_ `private static string GoIOSPath => ...`
- L174 _private field_ `private static ManagedProcessGroup s_tunnelProcessGroup`
- L176 _public field_ `public bool bCreatedIPA = false`
- L178 _public field_ `public string PlatformName = null`
- L179 _public field_ `public string SDKName = null`
- L180-183 _public ctor_ `public IOSPlatform() : this(UnrealTargetPlatform.IOS)`
- L185-190 _public ctor_ `public IOSPlatform(UnrealTargetPlatform TargetPlatform) : base(TargetPlatform)`
- L192-221 _public method_ `public override bool GetDeviceUpdateSoftwareCommand(out string Command, out string Params, ref bool bRequiresPrivilegeElevation, ref bool bCreateWindow, ITurnkeyContext TurnkeyContext, DeviceInfo Device)`
- L437-441 _private* method_ `string GetConfiguratorLocation()`
- L520-579 _public method_ `public override DeviceInfo[] GetDevices()`
- L581-592 _public method_ `public override string GetPlatformPakCommandLine(ProjectParams Params, DeploymentContext SC)`
- L594-597 _public method_ `public virtual void GetProvisioningData(FileReference InProject, bool bDistribution, out string MobileProvision, out string SigningCertificate, out string TeamUUID, out bool bAutomaticSigning)`
- L599-602 _public method_ `public virtual bool DeployGeneratePList(FileReference ProjectFile, UnrealTargetConfiguration Config, DirectoryReference ProjectDirectory, bool bIsUEGame, string GameName, bool bIsClient, string ProjectName, DirectoryReference InEngineDir, DirectoryReference AppDirectory, TargetReceipt Receipt)`
- L605-632 _public method_ `public bool GetCodeSignDesirability(ProjectParams Params)`
- L634-653 _private method_ `private void StageCustomLocalizationResources(ProjectParams Params, DeploymentContext SC)`
- L655-665 _public method_ `public override void Package(ProjectParams Params, DeploymentContext SC, int WorkingCL)`
- L667-672 _public method_ `public virtual bool PrepForUATPackageOrDeploy(UnrealTargetConfiguration Config, FileReference ProjectFile, string InProjectName, DirectoryReference InProjectDirectory, FileReference Executable, DirectoryReference InEngineDir, bool bForDistribution, string CookFlavor, bool bIsDataDeploy, bool bCreateStubIPA, bool bIsUEGame)`
- L674-787 _public method_ `public override void GetFilesToDeployOrStage(ProjectParams Params, DeploymentContext SC)`
- L789-801 _protected method_ `protected void StageMovieFiles(DirectoryReference InputDir, DeploymentContext SC)`
- L802-815 _protected method_ `protected void StageMovieFile(DirectoryReference InputDir, string Filename, DeploymentContext SC)`
- L817-827 _public method_ `public override void GetFilesToArchive(ProjectParams Params, DeploymentContext SC)`
- L829-918 _public method_ `public override bool RetrieveDeployedManifests(ProjectParams Params, DeploymentContext SC, string DeviceName, out List<string> UFSManifests, out List<string> NonUFSManifests)`
- L920-937 _private method_ `private string GetPathToLibiMobileDeviceTool(string LibimobileExec)`
- L939-948 _private method_ `private string GetLibimobileDeviceNetworkedArgument(string EntryArguments, string UDID)`
- L950-996 _private method_ `private void DeployManifestContent(string BaseFolder, DeploymentContext SC, ProjectParams Params, ref string Files, ref string BundleIdentifier)`
- L998-1007 _private method_ `private static bool IsDeviceLockedError(string Output)`
- L1009-1013 _private method_ `private static bool IsGoIOSDeviceLocked(string UDID)`
- L1015-1033 _private method_ `private static bool WaitForDeviceUnlockRetry(Stopwatch Timer, int MaxWaitSeconds)`
- L1035-1190 _public method_ `public override void Deploy(ProjectParams Params, DeploymentContext SC)`
- L1192-1195 _public method_ `public override string GetCookPlatform(bool bDedicatedServer, bool bIsClientOnly)`
- L1197-1201 _public method_ `public override bool DeployLowerCaseFilenames(StagedFileType FileType)`
- L1203-1206 _public method_ `public override string LocalPathToTargetPath(string LocalPath, string LocalRoot)`
- L1208 _public property_ `public override bool IsSupported { get; }`
- L1210 _public property_ `public override bool LaunchViaUFE { get; }`
- L1212-1218 _public property_ `public override bool UseAbsLog { get; }`
- L1220-1226 _public method_ `public override bool RemapFileType(StagedFileType FileType)`
- L1228-1231 _public method_ `public override StagedFileReference Remap(StagedFileReference Dest)`
- L1232-1235 _public method_ `public override List<string> GetDebugFileExtensions()`
- L1236-1425 _public method_ `public override IProcessResult RunClient(ERunOptions ClientRunFlags, string ClientApp, string ClientCmdLine, ProjectParams Params)`
- L1427-1461 _private method_ `private IProcessResult HandleLaunchFailure(IOSLaunchTool LaunchTool, IProcessResult ClientProcess, string BundleIdentifier, ProjectParams Params)`
- L1463-1494 _private method_ `private static void StartGoIOSTunnel(string UDID, string TunnelArgs)`
- L1496-1528 _private method_ `private static string GetGoIOSTunnelArgs(VersionNumber IOSVersion, string UDID)`
- L1530-1543 _private method_ `private VersionNumber GetDeviceIOSVersion(string UDID)`
- L1545-1550 _private method_ `private static int GetChunkCount(ProjectParams Params, DeploymentContext SC)`
- L1552-1555 _private method_ `private static string GetChunkPakManifestListFilename(ProjectParams Params, DeploymentContext SC)`
- L1557-1560 _private method_ `private static string GetChunkManifestPath(ProjectParams Params, DeploymentContext SC)`
- L1562-1618 _private method_ `private static StringBuilder AppendKeyValue(StringBuilder Text, string Key, object Value, int Level)`
- L1620-1644 _private method_ `private static void GeneratePlist(Dictionary<string, object> KeyValues, string PlistFile)`
- L1646-1652 _private method_ `private static void GenerateAssetPlist(string BundleIdentifier, string[] Tags, string AssetDir)`
- L1654-1669 _private method_ `private static void GenerateAssetPackManifestPlist(KeyValuePair<string, string>[] ChunkData, string AssetDir)`
- L1671-1691 _private method_ `private static void GenerateOnDemandResourcesPlist(KeyValuePair<string, string>[] ChunkData, string AssetDir)`
- L1693-1770 _public method_ `public override void PostStagingFileCopy(ProjectParams Params, DeploymentContext SC)`
- L1772-1775 _public method_ `public override bool RequiresPackageToDeploy(ProjectParams Params)`
- L1777-1782 _public method_ `public override HashSet<StagedFileReference> GetFilesForCRCCheck()`
- L1783-1789 _public property_ `public override bool SupportsMultiDeviceDeploy { get; }`
- L1791-1794 _public method_ `public override void StripSymbols(FileReference SourceFile, FileReference TargetFile)`
- L1796-1799 _public method_ `public override DirectoryReference GetProjectRootForStage(DirectoryReference RuntimeRoot, StagedDirectoryReference RelativeProjectRootForStage)`
- L1801-1805 _public method_ `public override void SetSecondaryRemoteMac(string ProjectFilePath, string ClientPlatform)`
- L1807-1912 _public method_ `public override void PrepareForDebugging(string SourcePackage, string ProjectFilePath, string ClientPlatform)`
- L1914-1941 _public method_ `public void UnzipPackage(string PackageToUnzip)`

#### enum `IOSPlatform.IOSLaunchTool`  
`private enum IOSLaunchTool`  
_private; L162-168_
- L164 _public* enumerator_ `Libimobiledevice`
- L165 _public* enumerator_ `GoIOS`
- L166 _public* enumerator_ `XcrunDevicectl`
- L167 _public* enumerator_ `Open`

#### class `IOSPlatform.VerifyIOSSettings`  
`private class VerifyIOSSettings`  
_private; L227-433_
- L229 _public field_ `public string CodeSigningIdentity = null`
- L230 _public field_ `public string BundleId = null`
- L231 _public field_ `public string Account = null`
- L232 _public field_ `public string Password = null`
- L233 _public field_ `public string Team = null`
- L234 _public field_ `public string Provision = null`
- L236 _public field_ `public string RubyScript = Path.Combine(Unreal.EngineDirectory.FullName, "Build/Turnkey/VerifyIOS.ru")`
- L237 _public field_ `public string InstallCertScript = Path.Combine(Unreal.EngineDirectory.FullName, "Build/Turnkey/InstallCert.ru")`
- L239 _private field_ `private ITurnkeyContext TurnkeyContext`
- L241-277 _public ctor_ `public VerifyIOSSettings(BuildCommand Command, ITurnkeyContext TurnkeyContext)`
- L279-353 _public method_ `public bool RunCommandMaybeInteractive(string Command, string Params, bool bInteractive)`
- L355-395 _public method_ `public bool RunRubyCommand(bool bVerifyOnly, string DeviceName)`
- L397-432 _private method_ `private bool InstallCert()`

### `Source/Programs/AutomationTool/IOS/MakeIPA.cs` (IOS.Automation)


#### class `MakeIPA`  
`public class MakeIPA : BuildCommand`  
_public; L19-153_
- attrs: `[Help(@"Creates an IPA from an xarchive file")] [Help("method=<method>", @"Purpose of the IPA. (Development, Adhoc, Store)")] [Help("TemplateFile=<file>", @"Path to plist template that will be filled in based on other arguments. See ExportOptions.plist.template for an example")] [Help("OptionsFile", @"Path to an XML file of options that we'll select from based on method. See ExportOptions.Values.x`
- inherits: `BuildCommand`
- L21 _protected property_ `protected string TemplateFile { get; set; }`
- L22 _protected property_ `protected string OptionsFile { get; set; }`
- L23 _protected property_ `protected string Project { get; set; }`
- L24 _protected property_ `protected string Method { get; set; }`
- L26-29 _public ctor_ `public MakeIPA()`
- L31-42 _private* method_ `string SelectPropertyTextOrDie(XmlDocument Doc, string InProperty, string InName)`
- L44-64 _protected method_ `protected void CreateExportPlist(string OutputPath)`
- L66-72 _private* method_ `int XcodeBuild(string Arguments)`
- L74-152 _public method_ `public override ExitCode Execute()`

### `Source/Programs/AutomationTool/IOS/Properties/AssemblyInfo.cs` (IOS.Automation)
_(no declarations)_


### `Source/Programs/AutomationTool/IOS/Properties/Resources.Designer.cs` (IOS.Automation)


#### class `iPhonePackager.Properties.Resources`  
`internal class Resources`  
_internal; L25-76_
- attrs: `[global::System.CodeDom.Compiler.GeneratedCodeAttribute("System.Resources.Tools.StronglyTypedResourceBuilder", "4.0.0.0")] [global::System.Diagnostics.DebuggerNonUserCodeAttribute()] [global::System.Runtime.CompilerServices.CompilerGeneratedAttribute()]`
- L27 _private field_ `private static global::System.Resources.ResourceManager resourceMan`
- L29 _private field_ `private static global::System.Globalization.CultureInfo resourceCulture`
- L32-33 _internal ctor_ `internal Resources()` — attrs: `[global::System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1811:AvoidUncalledPrivateCode")]`
- L39-47 _internal property_ `internal static global::System.Resources.ResourceManager ResourceManager { get; }` — attrs: `[global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]` — Returns the cached ResourceManager instance used by this class.
- L54-61 _internal property_ `internal static global::System.Globalization.CultureInfo Culture { get; set; }` — attrs: `[global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]` — Overrides the current thread's CurrentUICulture property for all resource lookups using this strongly typed resource class.
- L63-68 _internal property_ `internal static System.Drawing.Bitmap GreenCheck { get; }`
- L70-75 _internal property_ `internal static System.Drawing.Bitmap GreyCheck { get; }`

### `Source/Programs/AutomationTool/IOS/WriteIniValueToPlist.cs` (IOS.Automation)


#### class `WriteIniValueToPlist`  
`public class WriteIniValueToPlist : BuildCommand`  
_public; L21-130_
- attrs: `[Help(@"Pulls a value from an ini file and inserts it into a plist.")] [Help(@"Note currently only looks at values irrespective of sections!")] [Help("IniFile=<file>", @"Path to ini file to read from")] [Help("IniProperty=<name>", @"Name of the ini property to read. E.g. 'Version' for 'Version=12.0'")] [Help("PlistFile=<file>", @"Path to plist file to update")] [Help("PlistProperty=<name>", @"Plis`
- inherits: `BuildCommand`
- L26 _protected property_ `protected string IniFile { get; set; }` — Path to the ini file to be read
- L31 _protected property_ `protected string IniProperty { get; set; }` — Ini property to read
- L36 _protected property_ `protected string PlistFile { get; set; }` — Path to the plist file to be updated
- L41 _protected property_ `protected string PlistProperty { get; set; }` — Plist property to update
- L47-129 _public method_ `public override ExitCode Execute()` — UAT command entry point
