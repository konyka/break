# CSharp / Linux.Automation

- project root: `Source/Programs/AutomationTool/Linux`
- files: 2; symbols: 43
- symbol kinds: class=7, ctor=7, field=4, method=24, property=1
- access marked `*` is implicit (not written in source)

### `Source/Programs/AutomationTool/Linux/LinuxPlatform.Automation.cs` (Linux.Automation)


#### class `BaseLinuxPlatform`  
`public abstract class BaseLinuxPlatform : Platform`  
_public; L15-452_
- inherits: `Platform`
- L18 _private* field_ `static Regex DeviceRegex = new Regex(@"\w.+@([A-Za-z0-9\.\-]+)[\+]?")`
- L20 _private* field_ `static string PScpPath = MakePathSafeToUseWithCommandLine(CombinePaths(Unreal.RootDirectory.FullName, "Engine", "Extras", "ThirdPartyNotUE", "putty", "PSCP.EXE"))`
- L21 _private* field_ `static string PlinkPath = MakePathSafeToUseWithCommandLine(CombinePaths(Unreal.RootDirectory.FullName, "Engine", "Extras", "ThirdPartyNotUE", "putty", "PLINK.EXE"))`
- L22 _private* field_ `static string LaunchOnHelperShellScriptName = "LaunchOnHelper.sh"`
- L24-27 _public ctor_ `public BaseLinuxPlatform(UnrealTargetPlatform P) : base(P)`
- L29-48 _public method_ `public override DeviceInfo[] GetDevices()`
- L50-65 _public method_ `public override void PersistSdkRootVar()`
- L67-150 _public method_ `public override void GetFilesToDeployOrStage(ProjectParams Params, DeploymentContext SC)`
- L152-155 _public method_ `public override bool ShouldStageCommandLine(ProjectParams Params, DeploymentContext SC)`
- L157-200 _private* method_ `void StageBootstrapExecutable(DeploymentContext SC, string ExeName, string TargetFile, string StagedRelativeTargetPath, string StagedArguments)`
- L202-219 _public method_ `public override string GetCookPlatform(bool bDedicatedServer, bool bIsClientOnly)`
- L221-229 _public method_ `public override string GetEditorCookPlatform()`
- L235-238 _public method_ `public override bool DeployLowerCaseFilenames(StagedFileType FileType)` — return true if we need to change the case of filenames outside of pak files
- L245-325 _public method_ `public override void Deploy(ProjectParams Params, DeploymentContext SC)` — Deploy the application on the current platform
- L327-331 _public method_ `public override void Package(ProjectParams Params, DeploymentContext SC, int WorkingCL)`
- L333-340 _public method_ `public override bool CanHostPlatform(UnrealTargetPlatform Platform)`
- L342-346 _public method_ `public override void GetTargetFile(string RemoteFilePath, string LocalFile, ProjectParams Params)`
- L352-415 _public method_ `public override void PlatformSetupParams(ref ProjectParams ProjParams)` — Allow the platform to alter the ProjectParams
- L416-440 _public method_ `public override IProcessResult RunClient(ERunOptions ClientRunFlags, string ClientApp, string ClientCmdLine, ProjectParams Params)`
- L441-444 _public method_ `public override List<string> GetDebugFileExtensions()`
- L446 _public property_ `public override bool IsSupported { get; }`
- L448-451 _public method_ `public override void StripSymbols(FileReference SourceFile, FileReference TargetFile)`

#### class `GenericLinuxPlatform`  
`public class GenericLinuxPlatform : BaseLinuxPlatform`  
_public; L455-461_
- inherits: `BaseLinuxPlatform`
- L457-460 _public ctor_ `public GenericLinuxPlatform() : base(UnrealTargetPlatform.Linux)`

#### class `GenericLinuxPlatformArm64`  
`public class GenericLinuxPlatformArm64 : BaseLinuxPlatform`  
_public; L463-469_
- inherits: `BaseLinuxPlatform`
- L465-468 _public ctor_ `public GenericLinuxPlatformArm64() : base(UnrealTargetPlatform.LinuxArm64)`

#### class `LinuxPlatformArm64DXT`  
`public class LinuxPlatformArm64DXT : GenericLinuxPlatformArm64`  
_public; L471-487_
- inherits: `GenericLinuxPlatformArm64`
- L473-476 _public ctor_ `public LinuxPlatformArm64DXT() : base()`
- L478-481 _public method_ `public override TargetPlatformDescriptor GetTargetPlatformDescriptor()`
- L483-486 _public method_ `public override string GetCookPlatform(bool bDedicatedServer, bool bIsClientOnly)`

#### class `LinuxPlatformArm64ASTC`  
`public class LinuxPlatformArm64ASTC : GenericLinuxPlatformArm64`  
_public; L489-505_
- inherits: `GenericLinuxPlatformArm64`
- L491-494 _public ctor_ `public LinuxPlatformArm64ASTC() : base()`
- L496-499 _public method_ `public override TargetPlatformDescriptor GetTargetPlatformDescriptor()`
- L501-504 _public method_ `public override string GetCookPlatform(bool bDedicatedServer, bool bIsClientOnly)`

#### class `LinuxPlatformArm64ETC2`  
`public class LinuxPlatformArm64ETC2 : GenericLinuxPlatformArm64`  
_public; L507-523_
- inherits: `GenericLinuxPlatformArm64`
- L509-512 _public ctor_ `public LinuxPlatformArm64ETC2() : base()`
- L514-517 _public method_ `public override TargetPlatformDescriptor GetTargetPlatformDescriptor()`
- L519-522 _public method_ `public override string GetCookPlatform(bool bDedicatedServer, bool bIsClientOnly)`

#### class `LinuxPlatformArm64Multi`  
`public class LinuxPlatformArm64Multi : GenericLinuxPlatformArm64`  
_public; L525-541_
- inherits: `GenericLinuxPlatformArm64`
- L527-530 _public ctor_ `public LinuxPlatformArm64Multi() : base()`
- L532-535 _public method_ `public override TargetPlatformDescriptor GetTargetPlatformDescriptor()`
- L537-540 _public method_ `public override string GetCookPlatform(bool bDedicatedServer, bool bIsClientOnly)`

### `Source/Programs/AutomationTool/Linux/Properties/AssemblyInfo.cs` (Linux.Automation)
_(no declarations)_

