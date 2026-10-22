# CSharp / NoProject__Platforms__VisionOS__Source__Programs

- project root: `Platforms/VisionOS/Source/Programs`
- files: 6; symbols: 33
- symbol kinds: class=8, ctor=6, field=1, method=14, property=4
- access marked `*` is implicit (not written in source)

### `Platforms/VisionOS/Source/Programs/UnrealBuildTool/UEBuildVisionOS.cs` (NoProject__Platforms__VisionOS__Source__Programs)


#### class `UnrealBuildTool.VisionOSProjectSettings`  
`class VisionOSProjectSettings : IOSProjectSettings`  
_internal*; L8-18_
- inherits: `IOSProjectSettings`
- L11 _public property_ `public override string RuntimeDevices => ...`
- L12 _public property_ `public override string RuntimeVersion => ...`
- L14-17 _public ctor_ `public VisionOSProjectSettings(FileReference? ProjectFile, string? Bundle) : base(ProjectFile, UnrealTargetPlatform.VisionOS, Bundle)`

#### class `UnrealBuildTool.VisionOSPlatform`  
`class VisionOSPlatform : IOSPlatform`  
_internal*; L20-130_
- inherits: `IOSPlatform`
- L23 _private field_ `private float SDKVersionFloat = 0.0f`
- L25-28 _public ctor_ `public VisionOSPlatform(UEBuildPlatformSDK InSDK, ILogger Logger) : base(InSDK, UnrealTargetPlatform.VisionOS, Logger)`
- L30-41 _public method_ `public override void ValidateTarget(TargetRules Target)`
- L43-46 _public method_ `public new VisionOSProjectSettings ReadProjectSettings(FileReference? ProjectFile, string Bundle = "")`
- L48-51 _protected method_ `protected override IOSProjectSettings CreateProjectSettings(FileReference? ProjectFile, string? Bundle)`
- L53-86 _public method_ `public override void ModifyModuleRulesForOtherPlatform(string ModuleName, ModuleRules Rules, ReadOnlyTargetRules Target)`
- L94-111 _public method_ `public override void SetUpEnvironment(ReadOnlyTargetRules Target, CppCompileEnvironment CompileEnvironment, LinkEnvironment LinkEnvironment)` — Setup the target environment for building
- L118-124 _public method_ `public override UEToolChain CreateToolChain(ReadOnlyTargetRules Target)` — Creates a toolchain instance for the given platform.
- L126-129 _public method_ `public override void Deploy(TargetReceipt Receipt)`

#### class `UnrealBuildTool.VisionOSPlatformFactory`  
`class VisionOSPlatformFactory : UEBuildPlatformFactory`  
_internal*; L132-148_
- inherits: `UEBuildPlatformFactory`
- L134 _public property_ `public override UnrealTargetPlatform TargetPlatform => ...`
- L139-147 _public method_ `public override void RegisterBuildPlatforms(ILogger Logger)` — Register the platform with the UEBuildPlatform class

### `Platforms/VisionOS/Source/Programs/UnrealBuildTool/UEDeployVisionOS.cs` (NoProject__Platforms__VisionOS__Source__Programs)


#### class `UnrealBuildTool.UEDeployVisionOS`  
`class UEDeployVisionOS : UEDeployIOS`  
_internal*; L13-197_
- inherits: `UEDeployIOS`
- L16-19 _public ctor_ `public UEDeployVisionOS(ILogger InLogger) : base(InLogger)`
- L21-24 _protected method_ `protected override string GetTargetPlatformName()`
- L26-191 _public method_ `public static bool GenerateVisionOSPList(string ProjectDirectory, bool bIsUnrealGame, string GameName, bool bIsClient, string ProjectName, string InEngineDir, string AppDirectory, UnrealPluginLanguage? UPL, string? BundleID)`
- L193-196 _public method_ `public override bool GeneratePList(FileReference? ProjectFile, UnrealTargetConfiguration Config, string ProjectDirectory, bool bIsUnrealGame, string GameName, bool bIsClient, string ProjectName, string InEngineDir, string AppDirectory, List<string> UPLScripts, string? BundleID, bool bBuildAsFramework)`

### `Platforms/VisionOS/Source/Programs/UnrealBuildTool/VisionOSExports.cs` (NoProject__Platforms__VisionOS__Source__Programs)


#### class `UnrealBuildTool.VisionOSExports`  
`public static class VisionOSExports`  
_public; L11-54_
- desc: Public VisionOS functions exposed to UAT
- L29-33 _public method_ `public static bool PrepForUATPackageOrDeploy(UnrealTargetConfiguration Config, FileReference ProjectFile, string InProjectName, DirectoryReference InProjectDirectory, FileReference Executable, DirectoryReference InEngineDir, bool bForDistribution, string CookFlavor, bool bIsDataDeploy, bool bCreateStubIPA, FileReference BuildReceiptFileName, ILogger Logger)`
- L50-53 _public method_ `public static bool GeneratePList(FileReference ProjectFile, UnrealTargetConfiguration Config, DirectoryReference ProjectDirectory, bool bIsUnrealGame, string GameName, bool bIsClient, string ProjectName, DirectoryReference InEngineDir, DirectoryReference AppDirectory, TargetReceipt Receipt, ILogger Logger)`

### `Platforms/VisionOS/Source/Programs/UnrealBuildTool/VisionOSProjectGenerator.cs` (NoProject__Platforms__VisionOS__Source__Programs)


#### class `UnrealBuildTool.VisionOSProjectGenerator`  
`class VisionOSProjectGenerator : IOSProjectGenerator`  
_internal*; L9-28_
- inherits: `IOSProjectGenerator`
- L16-19 _public ctor_ `public VisionOSProjectGenerator(CommandLineArguments Arguments, ILogger Logger) : base(Arguments, Logger)` — Constructor
- L24-27 _public method_ `public override IEnumerable<UnrealTargetPlatform> GetPlatforms()` — Enumerate all the platforms that this generator supports

### `Platforms/VisionOS/Source/Programs/UnrealBuildTool/VisionOSToolChain.cs` (NoProject__Platforms__VisionOS__Source__Programs)


#### class `UnrealBuildTool.VisionOSToolChain`  
`class VisionOSToolChain : IOSToolChain`  
_internal*; L7-15_
- inherits: `IOSToolChain`
- L9 _protected property_ `protected override string XnuPlatformDefine => ...`
- L11-14 _public ctor_ `public VisionOSToolChain(ReadOnlyTargetRules InTarget, VisionOSProjectSettings InProjectSettings, ILogger InLogger) : base(InTarget, InProjectSettings, () => new VisionOSToolChainSettings(InProjectSettings, InLogger), ClangToolChainOptions.None, InLogger)`

### `Platforms/VisionOS/Source/Programs/UnrealBuildTool/VisionOSToolChainSettings.cs` (NoProject__Platforms__VisionOS__Source__Programs)


#### class `UnrealBuildTool.VisionOSToolChainSettings`  
`class VisionOSToolChainSettings : IOSToolChainSettings`  
_internal*; L7-13_
- inherits: `IOSToolChainSettings`
- L9-12 _public ctor_ `public VisionOSToolChainSettings(IOSProjectSettings ProjectSettings, ILogger Logger) : base("XROS", "XRSimulator", "xros", ProjectSettings, Logger)`
