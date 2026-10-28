# CSharp / Mac.Automation

- project root: `Source/Programs/AutomationTool/Mac`
- files: 2; symbols: 23
- symbol kinds: class=1, ctor=1, field=1, method=19, property=1
- access marked `*` is implicit (not written in source)

### `Source/Programs/AutomationTool/Mac/MacPlatform.Automation.cs` (Mac.Automation)


#### class `MacPlatform`  
`public class MacPlatform : ApplePlatform`  
_public; L15-439_
- inherits: `ApplePlatform`
- L20 _protected field_ `protected UnrealArchitectures ProjectTargetArchitectures = new(UnrealArch.X64)` — Default architecture to build projects for. Defaults to Intel
- L22-26 _public ctor_ `public MacPlatform() : base(UnrealTargetPlatform.Mac)`
- L28-51 _public method_ `public override void PlatformSetupParams(ref ProjectParams ProjParams)`
- L53-68 _public method_ `public override void PersistSdkRootVar()`
- L70-83 _public method_ `public override DeviceInfo[] GetDevices()`
- L85-103 _public method_ `public override string GetCookPlatform(bool bDedicatedServer, bool bIsClientOnly)`
- L105-108 _public method_ `public override string GetEditorCookPlatform()`
- L117-133 _public method_ `public override void PreBuildAgenda(UnrealBuild Build, UnrealBuild.BuildAgenda Agenda, ProjectParams Params)` — Override PreBuildAgenda so we can control the architecture that targets are built for based on project settings and the current user environment
- L135-148 _private method_ `private void StageAppBundle(DeploymentContext SC, DirectoryReference InPath, StagedDirectoryReference NewName)`
- L150-225 _public method_ `public override void GetFilesToDeployOrStage(ProjectParams Params, DeploymentContext SC)`
- L227-242 _private* method_ `string GetValueFromInfoPlist(string InfoPlist, string Key, string DefaultValue = "")`
- L244-303 _private* method_ `void StageBootstrapExecutable(DeploymentContext SC, string ExeName, string TargetFile, string StagedRelativeTargetPath, string StagedArguments)`
- L305-340 _private method_ `private void RemoveExtraRPaths(ProjectParams Params, DeploymentContext SC)`
- L342-370 _private method_ `private void FixupFrameworks(string TargetPath)`
- L372-375 _public method_ `public override void ProcessArchivedProject(ProjectParams Params, DeploymentContext SC)`
- L377-398 _public method_ `public override IProcessResult RunClient(ERunOptions ClientRunFlags, string ClientApp, string ClientCmdLine, ProjectParams Params)`
- L400 _public property_ `public override bool IsSupported { get; }`
- L402-405 _public method_ `public override List<string> GetDebugFileExtensions()`
- L406-413 _public method_ `public override bool CanHostPlatform(UnrealTargetPlatform Platform)`
- L415-419 _public method_ `public override bool ShouldStageCommandLine(ProjectParams Params, DeploymentContext SC)`
- L421-433 _public method_ `public override bool SignExecutables(DeploymentContext SC, ProjectParams Params)`
- L435-438 _public method_ `public override void StripSymbols(FileReference SourceFile, FileReference TargetFile)`

### `Source/Programs/AutomationTool/Mac/Properties/AssemblyInfo.cs` (Mac.Automation)
_(no declarations)_

