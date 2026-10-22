# CSharp / CookedEditor.Automation

- project root: `Source/Programs/AutomationTool/CookedEditor`
- files: 3; symbols: 91
- symbol kinds: class=9, ctor=2, field=30, method=49, property=1
- access marked `*` is implicit (not written in source)

### `Source/Programs/AutomationTool/CookedEditor/CookedEditor.Automation.cs` (CookedEditor.Automation)


#### class `ConfigHelper`  
`public class ConfigHelper`  
_public; L16-72_
- L18 _private field_ `private string SpecificConfigSection`
- L19 _private field_ `private string SharedConfigSection`
- L20 _public property_ `public ConfigHierarchy GameConfig { get; }`
- L22-28 _public ctor_ `public ConfigHelper(UnrealTargetPlatform Platform, FileReference ProjectFile, bool bIsCookedCooker)`
- L30-39 _public method_ `public bool GetBool(string Key)`
- L41-53 _public method_ `public string GetString(string Key)`
- L55-71 _public method_ `public List<string> GetArray(string Key)`

#### class `ModifyStageContext`  
`public class ModifyStageContext`  
_public; L74-363_
- L77 _public field_ `public List<FileReference> UFSFilesToStage = new List<FileReference>()`
- L79 _public field_ `public List<FileReference> FilesToUncook = new List<FileReference>()`
- L81 _public field_ `public List<FileReference> NonUFSFilesToStage = new List<FileReference>()`
- L83 _public field_ `public List<FileReference> DebugNonUFSFilesToStage = new List<FileReference>()`
- L85 _public field_ `public bool bStageShaderDirs = true`
- L86 _public field_ `public bool bStagePlatformBuildDirs = true`
- L87 _public field_ `public bool bStageExtrasDirs = false`
- L88 _public field_ `public bool bStagePlatformDirs = true`
- L89 _public field_ `public bool bStageUAT = false`
- L90 _public field_ `public bool bIsForExternalDistribution = false`
- L91 _public field_ `public bool bStageCollections = false`
- L92 _public field_ `public bool bStagePython = false`
- L93 _public field_ `public bool bStageTargetFiles = false`
- L95 _public field_ `public ConfigHelper ConfigHelper`
- L97 _public field_ `public DirectoryReference EngineDirectory`
- L98 _public field_ `public DirectoryReference ProjectDirectory`
- L99 _public field_ `public string ProjectName`
- L100 _public field_ `public string IniPlatformName`
- L101 _public field_ `public bool bIsDLC`
- L104 _public field_ `public DirectoryReference ReleaseMetadataLocation = null`
- L107 _public field_ `public DirectoryReference CachedEditorDataLocation = null`
- L110 _private field_ `private BuildCommand Command`
- L112-149 _public ctor_ `public ModifyStageContext(ConfigHelper ConfigHelper, DirectoryReference EngineDirectory, ProjectParams Params, DeploymentContext SC, BuildCommand Command)`
- L151-229 _public method_ `public void Apply(DeploymentContext SC)`
- L232-264 _private method_ `private void RemoveReleasedFiles(DeploymentContext SC)`
- L265-279 _private method_ `private Dictionary<StagedFileReference, FileReference> MimicStageFiles(DeploymentContext SC, List<FileReference> SourceFiles)`
- L281-299 _private method_ `private void HandleRestrictedFiles(DeploymentContext SC, ref Dictionary<StagedFileReference, FileReference> Files)`
- L301-306 _private method_ `private void AddCookedUFSFilesToList(List<FileReference> FileList, string Extension, DeploymentContext SC)`
- L308-319 _private method_ `private void AddUFSFilesToList(List<FileReference> FileList, string Extension, DeploymentContext SC)`
- L321-348 _private method_ `private void UncookMaps(DeploymentContext SC)`
- L350-360 _private method_ `private void UnUFSFiles(DeploymentContext SC)`

#### class `MakeCookedEditor`  
`public class MakeCookedEditor : BuildCommand`  
_public; L366-1322_
- inherits: `BuildCommand`
- L368 _protected field_ `protected bool bIsCookedCooker`
- L369 _protected field_ `protected FileReference ProjectFile`
- L371 _protected field_ `protected ConfigHelper ConfigHelper`
- L374 _protected field_ `protected DirectoryReference CookedEditorStageDirectory = null`
- L375 _protected field_ `protected DirectoryReference ReleaseStageDirectory = null`
- L379 _protected field_ `protected DirectoryReference ReleaseOptionalFileStageDirectory = null`
- L381-443 _public method_ `public override void ExecuteBuild()`
- L445-483 _protected method_ `protected virtual void StageEngineEditorFiles(ProjectParams Params, DeploymentContext SC, ModifyStageContext Context)`
- L485-581 _protected method_ `protected virtual void StageProjectEditorFiles(ProjectParams Params, DeploymentContext SC, ModifyStageContext Context)`
- L583-662 _protected method_ `protected virtual void StageUAT(ProjectParams Params, DeploymentContext SC, ModifyStageContext Context)`
- L664-670 _protected method_ `protected virtual void StagePluginDirectory(DirectoryReference PluginDir, ModifyStageContext Context, bool bStageUncookedContent)`
- L672-699 _protected method_ `protected virtual void StagePluginSubdirectory(DirectoryReference PluginSubdir, ModifyStageContext Context, bool bStageUncookedContent)`
- L701-704 _protected method_ `protected virtual ModifyStageContext CreateContext(ProjectParams Params, DeploymentContext SC)`
- L706-708 _protected method_ `protected virtual void ModifyParams(ProjectParams BuildParams)`
- L710-712 _protected method_ `protected virtual void ModifyReleaseParams(ProjectParams ReleaseParams)`
- L714-716 _protected method_ `protected virtual void FinalizeRelease(ProjectParams ReleaseParams)`
- L718-725 _protected method_ `protected virtual void PreModifyDeploymentContext(ProjectParams Params, DeploymentContext SC)`
- L727-751 _protected method_ `protected virtual void ModifyDeploymentContext(ProjectParams Params, DeploymentContext SC)`
- L753-755 _protected method_ `protected virtual void FinalizeDeploymentContext(ProjectParams Params, DeploymentContext SC)`
- L757-788 _protected method_ `protected virtual void SetupDLCMode(FileReference ProjectFile, out string DLCName, out string ReleaseVersion, out TargetType Type)`
- L796-855 _protected method_ `protected void StagePlatformExtensionFiles(ProjectParams Params, DeploymentContext SC, ModifyStageContext Context, DirectoryReference RootDir)`
- L857-883 _protected method_ `protected void StagePluginFiles(ProjectParams Params, DeploymentContext SC, ModifyStageContext Context, bool bEnginePlugins)`
- L885-989 _protected method_ `protected void StageIniPathArray(ProjectParams Params, DeploymentContext SC, string IniKey, DirectoryReference BaseDirectory, ModifyStageContext Context)`
- L992-995 _protected method_ `protected void DefaultPreModifyDeploymentContext(ProjectParams Params, DeploymentContext SC, ModifyStageContext Context)`
- L996-1080 _protected method_ `protected void DefaultModifyDeploymentContext(ProjectParams Params, DeploymentContext SC, ModifyStageContext Context)`
- L1082-1089 _protected method_ `protected virtual string GetReleaseTargetName(UnrealTargetPlatform Platform, TargetType ReleaseType)`
- L1091-1094 _protected method_ `protected virtual string GetReleaseVersionPath(string ReleaseVersionName, string ReleaseTargetName)`
- L1096-1109 _protected method_ `protected virtual ProjectParams MakeParams(string DLCName, string BasedOnReleaseVersion)`
- L1111-1226 _private method_ `private ProjectParams GetParams()`
- L1228-1266 _private method_ `private ProjectParams GetReleaseParams(ProjectParams MainParams, string[] Options)`
- L1269-1272 _protected method_ `protected static void GatherTargetDependencies(ProjectParams Params, DeploymentContext SC, ModifyStageContext Context, string ReceiptName)`
- L1274-1321 _protected method_ `protected static void GatherTargetDependencies(ProjectParams Params, DeploymentContext SC, ModifyStageContext Context, string ReceiptName, UnrealTargetConfiguration Configuration)`

### `Source/Programs/AutomationTool/CookedEditor/PlatformWrappers.cs` (CookedEditor.Automation)


#### class `WindowsCookedEditor`  
`public class WindowsCookedEditor : Win64Platform`  
_public; L7-17_
- inherits: `Win64Platform`
- L9-12 _public method_ `public override string GetCookPlatform(bool bDedicatedServer, bool bIsClientOnly)`
- L13-16 _public method_ `public override TargetPlatformDescriptor GetTargetPlatformDescriptor()`

#### class `LinuxCookedEditor`  
`public class LinuxCookedEditor : GenericLinuxPlatform`  
_public; L19-30_
- inherits: `GenericLinuxPlatform`
- L21-24 _public method_ `public override string GetCookPlatform(bool bDedicatedServer, bool bIsClientOnly)`
- L25-28 _public method_ `public override TargetPlatformDescriptor GetTargetPlatformDescriptor()`

#### class `MacCookedEditor`  
`public class MacCookedEditor : MacPlatform`  
_public; L32-43_
- inherits: `MacPlatform`
- L34-37 _public method_ `public override string GetCookPlatform(bool bDedicatedServer, bool bIsClientOnly)`
- L38-41 _public method_ `public override TargetPlatformDescriptor GetTargetPlatformDescriptor()`

#### class `WindowsCookedCooker`  
`public class WindowsCookedCooker : Win64Platform`  
_public; L46-56_
- inherits: `Win64Platform`
- L48-51 _public method_ `public override string GetCookPlatform(bool bDedicatedServer, bool bIsClientOnly)`
- L52-55 _public method_ `public override TargetPlatformDescriptor GetTargetPlatformDescriptor()`

#### class `LinuxCookedCooker`  
`public class LinuxCookedCooker : GenericLinuxPlatform`  
_public; L58-69_
- inherits: `GenericLinuxPlatform`
- L60-63 _public method_ `public override string GetCookPlatform(bool bDedicatedServer, bool bIsClientOnly)`
- L64-67 _public method_ `public override TargetPlatformDescriptor GetTargetPlatformDescriptor()`

#### class `MacCookedCooker`  
`public class MacCookedCooker : MacPlatform`  
_public; L71-82_
- inherits: `MacPlatform`
- L73-76 _public method_ `public override string GetCookPlatform(bool bDedicatedServer, bool bIsClientOnly)`
- L77-80 _public method_ `public override TargetPlatformDescriptor GetTargetPlatformDescriptor()`

### `Source/Programs/AutomationTool/CookedEditor/Properties/AssemblyInfo.cs` (CookedEditor.Automation)
_(no declarations)_

