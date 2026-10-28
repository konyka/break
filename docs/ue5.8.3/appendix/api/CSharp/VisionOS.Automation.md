# CSharp / VisionOS.Automation

- project root: `Platforms/VisionOS/Source/Programs/AutomationTool`
- files: 3; symbols: 22
- symbol kinds: class=4, ctor=3, method=4, property=11
- access marked `*` is implicit (not written in source)

### `Platforms/VisionOS/Source/Programs/AutomationTool/Properties/AssemblyInfo.cs` (VisionOS.Automation)
_(no declarations)_


### `Platforms/VisionOS/Source/Programs/AutomationTool/Scripts/BuildCMakeLib_VisionOS.Automation.cs` (VisionOS.Automation)


#### class `XcodeTargetPlatform_VisionOS`  
`class XcodeTargetPlatform_VisionOS : XcodeTargetPlatform_IOS`  
_internal*; L5-10_
- inherits: `XcodeTargetPlatform_IOS`
- L7 _public property_ `public override string PlatformOrGroupName => ...`
- L8 _public property_ `public override bool IsPlatformExtension => ...`
- L9 _protected property_ `protected override string CMakeSystemName => ...`

#### class `MakefileTargetPlatform_VisionOS`  
`class MakefileTargetPlatform_VisionOS : MakefileTargetPlatform_IOS`  
_internal*; L12-23_
- inherits: `MakefileTargetPlatform_IOS`
- L14 _public property_ `public override string PlatformOrGroupName => ...`
- L15 _public property_ `public override bool IsPlatformExtension => ...`
- L16 _protected property_ `protected override string CMakeSystemName => ...`
- L17 _protected property_ `protected override string SdkName => ...`
- L19-21 _public ctor_ `public MakefileTargetPlatform_VisionOS(string Architecture) : base(Architecture)`

#### class `NinjaBuildTargetPlatform_VisionOS`  
`class NinjaBuildTargetPlatform_VisionOS : NinjaBuildTargetPlatform_IOS`  
_internal*; L25-36_
- inherits: `NinjaBuildTargetPlatform_IOS`
- L27 _public property_ `public override string PlatformOrGroupName => ...`
- L28 _public property_ `public override bool IsPlatformExtension => ...`
- L29 _protected property_ `protected override string CMakeSystemName => ...`
- L30 _protected property_ `protected override string SdkName => ...`
- L32-34 _public ctor_ `public NinjaBuildTargetPlatform_VisionOS(string Architecture) : base(Architecture)`

### `Platforms/VisionOS/Source/Programs/AutomationTool/VisionOSPlatform.Automation.cs` (VisionOS.Automation)


#### class `VisionOSPlatform`  
`public class VisionOSPlatform : IOSPlatform`  
_public; L12-161_
- inherits: `IOSPlatform`
- L14-18 _public ctor_ `public VisionOSPlatform() :base(UnrealTargetPlatform.VisionOS)`
- L20-33 _public method_ `public override bool PrepForUATPackageOrDeploy(UnrealTargetConfiguration Config, FileReference ProjectFile, string InProjectName, DirectoryReference InProjectDirectory, FileReference Executable, DirectoryReference InEngineDir, bool bForDistribution, string CookFlavor, bool bIsDataDeploy, bool bCreateStubIPA, bool bIsUEGame)`
- L35-38 _public method_ `public override bool DeployGeneratePList(FileReference ProjectFile, UnrealTargetConfiguration Config, DirectoryReference ProjectDirectory, bool bIsUEGame, string GameName, bool bIsClient, string ProjectName, DirectoryReference InEngineDir, DirectoryReference AppDirectory, TargetReceipt Receipt)`
- L40-43 _public method_ `public override string GetCookPlatform(bool bDedicatedServer, bool bIsClientOnly)`
- L45-160 _public method_ `public override void GetFilesToDeployOrStage(ProjectParams Params, DeploymentContext SC)`
