# CSharp / TVOS.Automation

- project root: `Source/Programs/AutomationTool/TVOS`
- files: 2; symbols: 7
- symbol kinds: class=1, ctor=1, method=5
- access marked `*` is implicit (not written in source)

### `Source/Programs/AutomationTool/TVOS/Properties/AssemblyInfo.cs` (TVOS.Automation)
_(no declarations)_


### `Source/Programs/AutomationTool/TVOS/TVOSPlatform.Automation.cs` (TVOS.Automation)


#### class `TVOSPlatform`  
`public class TVOSPlatform : IOSPlatform`  
_public; L12-178_
- inherits: `IOSPlatform`
- L14-18 _public ctor_ `public TVOSPlatform() :base(UnrealTargetPlatform.TVOS)`
- L20-33 _public method_ `public override bool PrepForUATPackageOrDeploy(UnrealTargetConfiguration Config, FileReference ProjectFile, string InProjectName, DirectoryReference InProjectDirectory, FileReference Executable, DirectoryReference InEngineDir, bool bForDistribution, string CookFlavor, bool bIsDataDeploy, bool bCreateStubIPA, bool bIsUEGame)`
- L35-38 _public method_ `public override void GetProvisioningData(FileReference InProject, bool bDistribution, out string MobileProvision, out string SigningCertificate, out string Team, out bool bAutomaticSigning)`
- L40-43 _public method_ `public override bool DeployGeneratePList(FileReference ProjectFile, UnrealTargetConfiguration Config, DirectoryReference ProjectDirectory, bool bIsUEGame, string GameName, bool bIsClient, string ProjectName, DirectoryReference InEngineDir, DirectoryReference AppDirectory, TargetReceipt Receipt)`
- L45-48 _public method_ `public override string GetCookPlatform(bool bDedicatedServer, bool bIsClientOnly)`
- L50-177 _public method_ `public override void GetFilesToDeployOrStage(ProjectParams Params, DeploymentContext SC)`
