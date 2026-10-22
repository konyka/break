# CSharp / Microsoft.Automation

- project root: `Source/Programs/AutomationTool/Microsoft`
- files: 3; symbols: 113
- symbol kinds: class=7, const=1, ctor=4, enum=1, enumerator=2, field=38, method=43, property=13, struct=4
- access marked `*` is implicit (not written in source)

### `Source/Programs/AutomationTool/Microsoft/GDKAutomationUtils.cs` (Microsoft.Automation)


#### class `AutomationUtils.GDK.GDKAutomationUtils`  
`public class GDKAutomationUtils`  
_public; L16-211_
- L18-32 _public method_ `public static void GenerateGameConfigForStaging(ProjectParams Params, DeploymentContext SC, string IniSection_TargetSettings, ILogger Logger)`
- L39-100 _public method_ `public static List<AppXManifestExecutable> GetGameConfigExecutables(ProjectParams Params, DeploymentContext SC, GameConfigPurpose Purpose, string IniSection_TargetSettings, UnrealTargetConfiguration? OnlyConfig = null)`
- L102-158 _public method_ `public static Dictionary<UnrealTargetConfiguration, List<string>> GetPerConfigBootstrapExecutables(ProjectParams Params, DeploymentContext SC)`
- L168-210 _private method_ `private static void ApplyIoStoreOnDemandSettings(ProjectParams Params, DirectoryReference ManifestTargetDirectory, ILogger Logger)` — Makes sure that the project config file is setup to allow enough persistent local storage for IoStoreOnDemand caching. If the project is not set up for this or has not requested enough space then the config file will be modified to satisfy our requirements.

#### enum `AutomationUtils.GDK.GDKAutomationUtils.GameConfigPurpose`  
`public enum GameConfigPurpose`  
_public; L34-38_
- L36 _public* enumerator_ `ForStaging`
- L37 _public* enumerator_ `ForPackaging`

### `Source/Programs/AutomationTool/Microsoft/GDKPackageGenerator.cs` (Microsoft.Automation)


#### class `AutomationUtils.GDK.GDKPackageGenerator`  
`public abstract class GDKPackageGenerator`  
_public; L24-1692_
- L26 _protected field_ `protected readonly string IniSection_TargetSettings`
- L27 _protected field_ `protected readonly UnrealTargetPlatform PlatformType`
- L28 _protected field_ `protected readonly ConfigHierarchy EngineIni`
- L31 _public property_ `public bool GenerateSinglePackages { get; set; }` — Whether to generate separate packages for each configuration
- L34 _public property_ `public bool GenerateCombinedPackage { get; set; }` — Whether to generate a single package containing all configurations combined
- L37 _public property_ `public bool PrecachePackageLayout { get; set; }` — Whether to create metadata during staging that can be used to make the package. This ensures that only the explicitly staged files will be included in the package. The alternative is that everything in the staging directory is scraped and packaged
- L40 _public property_ `public bool ParallelizePackageGeneration { get; set; }` — Whether to parallelize calls to makepkg when generating multiple configuration packages. This requires PrecachePackageLayout
- L43 _public property_ `public bool NoDebugInfoSkipsSymbolBundling { get; set; }` — When true, specifying -NoDebugInfo will cause /skipsymbolbundling to be passed to the package generator for non-submission packages. This will mean the symbols zip file for uploading to Partner Center will not be created. Potentially useful for iteration.
- L46 _protected property_ `protected static int GDKEdition => ...`
- L47 _protected property_ `protected static string GDKRootDir => ...`
- L48 _protected property_ `protected static string GDKBinariesDir => ...`
- L51-90 _public ctor_ `public GDKPackageGenerator(FileReference InProjectPath, UnrealTargetPlatform InPlatformType, string InIniSection_TargetSettings, string CustomConfig)`
- L93 _public method_ `public abstract string GetPlatformPackageFileExtension()`
- L95 _protected method_ `protected abstract string GetPlatformSpecificPackageCommandlineOptions(ProjectParams Params, DeploymentContext SC, string DLCPackage)`
- L97-99 _protected method_ `protected virtual void GetPlatformSpecificPackageSymbolPaths(HashSet<string> SymbolPaths, ProjectParams Params, DeploymentContext SC)`
- L101-117 _protected method_ `protected string GetPackagingEncryptionOptions(ProjectParams Params)`
- L119-132 _protected method_ `protected string GetPackageEncryptionOptions(string PackagePath)`
- L134-152 _protected method_ `protected string FindPackageFile(DirectoryReference PackagePath)`
- L154-171 _private* method_ `string GetOptionalConfigGuidOption(string KeyName, string Parameter)`
- L173-189 _public method_ `public void GetPackageFilesToArchive(ProjectParams Params, DeploymentContext SC, string PackageOutputPathFragment = "")`
- L193-232 _public method_ `public void GeneratePackages(ProjectParams Params, DeploymentContext SC, DirectoryReference PackageMetadataBasePath = null, string PackageOutputPathFragment = "")`
- L234-241 _public method_ `public void GeneratePackageMetadata(ProjectParams Params, DeploymentContext SC, DirectoryReference PackageMetadataBasePath)`
- L264-288 _private method_ `private List<PackageRequest> MakePackageRequests(ProjectParams Params, DeploymentContext SC)`
- L290-324 _public method_ `public void GenerateSinglePackage(ProjectParams Params, DeploymentContext SC, string DLCPackage, DirectoryReference PackageMetadataBasePath = null, UnrealTargetConfiguration? OnlyConfig = null, ILogger CustomLogger = null, string PackageOutputPathFragment = "")`
- L329-549 _protected method_ `protected virtual void PackageInternal(ProjectParams Params, DeploymentContext SC, DirectoryReference PackagePath, FileReference LayoutPath, DirectoryReference SourceFolder, ILogger Logger, string DLCPackage, UnrealTargetConfiguration? OnlyConfig = null, string PackageOutputPathFragment = "")`
- L552-567 _private method_ `private List<FileReference> MoveFiles(List<FileReference> Files, DirectoryReference SrcDir, DirectoryReference DstDir)`
- L569-575 _private method_ `private void DeleteFiles(List<FileReference> Files)`
- L579-608 _protected method_ `protected void PackageImmediate(ProjectParams Params, DeploymentContext SC, DirectoryReference PackagePath, ILogger Logger, string DLCPackage, UnrealTargetConfiguration? OnlyConfig = null, string PackageOutputPathFragment = "")`
- L613-632 _private method_ `private List<FileReference> GetGDKManifestFilesInDirectory(DirectoryReference Directory)`
- L636-642 _protected method_ `protected void VerifyWindowsToolsEnvironment()`
- L700 _private field_ `private static readonly Dictionary<string, string> SubmissionValidatorErrorsToDowngrade = ...`
- L700 _private field_ `private static readonly Dictionary< SubmissionValidatorErrorsToDowngrade = new Dictionary<string, string>() { { "Error: A required update to Submission Validator is available", "Warning: A required update to Submission Validator is available (this will be an error in Shippin ...`
- L705 _private field_ `private static readonly Dictionary<string, string> StoreAssociationMessageToAlter = ...`
- L705 _private field_ `private static readonly Dictionary< StoreAssociationMessageToAlter = new Dictionary<string, string>() { { "Please use the MicrosoftGame.config Editor \"Associate with Store\" feature", "Please use the \"Update Partner Center Association\" button in Unreal Editor's Proj ...`
- L710-733 _protected method_ `protected virtual void PrepareMessageFilterForMakePkg(SpewFilterHelper Filter, ConfigHierarchy EngineIni, ProjectParams Params, DeploymentContext SC)`
- L739-770 _protected method_ `protected virtual bool ShouldPackageFile(FileReference SrcFile, ProjectParams Params, DeploymentContext SC, UnrealTargetConfiguration? OnlyConfig = null)`
- L772-786 _private method_ `private Dictionary<StagedFileReference, FileReference> FindStagedFilesToPackage(ProjectParams Params, DeploymentContext SC, UnrealTargetConfiguration? OnlyConfig = null)`
- L1017 _private* const_ `const int OSChunkIdOffset = 2`
- L1114-1531 _private method_ `private void GeneratePackageMetadataInternal(ProjectParams Params, DeploymentContext SC, IEnumerable<StagedFileReference> FilesToInclude, IEnumerable<StagedFileReference> GeneratedFilesToInclude, DirectoryReference LayoutDirectory, ILogger Logger, string DLCPackage)`
- L1538-1619 _public method_ `public void GenerateSinglePackageMetadata(ProjectParams Params, DeploymentContext SC, DirectoryReference PackageMetadataDir, string DLCPackage, UnrealTargetConfiguration? OnlyConfig = null)` — Generates the layout.xml and associated files required for packaging in the given layout directory
- L1621-1624 _protected method_ `protected virtual IEnumerable<StagedFileReference> GetPlatformFilesToPackage(ProjectParams Params, DeploymentContext SC, DirectoryReference PackageMetadataDir, UnrealTargetConfiguration? OnlyConfig)`
- L1630-1642 _protected method_ `protected static bool TryGetValue<T>(Dictionary<string, string> Dictionary, string Key, out T Value)` — attempt to parse out a typed value from the given dictionary & key
- L1645-1657 _protected method_ `protected static bool TryGetValue(Dictionary<string, string> Dictionary, string Key, out string[] Value)` — attempt to parse out an array of strings from the given dictionary & key
- L1660-1667 _protected method_ `protected static XAttribute opt_XAttribute(string Key, string OptValue, bool bAdditionalPrerequisite = true)` — create an XAttribute as long as the value is not null and the additionl prerequisite is true
- L1670-1677 _protected method_ `protected static XAttribute opt_XAttribute(string Key, string[] Values)` — create an XAttribute of semicolon-separated values as long as there are values
- L1680-1687 _protected method_ `protected static XAttribute opt_XAttribute(string Key, bool OptValue)` — create an XAttribute as long as the value is true

#### struct `AutomationUtils.GDK.GDKPackageGenerator.PackageRequest`  
`struct PackageRequest`  
_private*; L245-262_
- L247-249 _public ctor_ `public PackageRequest()`
- L251-254 _public ctor_ `public PackageRequest(UnrealTargetConfiguration? InConfig)`
- L255-258 _public ctor_ `public PackageRequest(string InDLCPackage)`
- L260 _public field_ `public readonly UnrealTargetConfiguration? Config = null`
- L261 _public field_ `public readonly string DLCPackage = null`

#### class `AutomationUtils.GDK.GDKPackageGenerator.SpewFilterHelper`  
`protected class SpewFilterHelper`  
_protected; L648-697_
- L650 _private field_ `private List<string> IgnoreList = new List<string>()`
- L651 _private field_ `private Dictionary<string, string> ReplaceDict = ...`
- L651 _private field_ `private Dictionary< ReplaceDict = new Dictionary<string, string>()`
- L652 _private field_ `private Dictionary<string, string> RegExReplaceDict = ...`
- L652 _private field_ `private Dictionary< RegExReplaceDict = new Dictionary<string, string>()`
- L654-660 _public method_ `public void ReplaceMessages(Dictionary<string, string> Replacements)`
- L662-668 _public method_ `public void RegExReplaceMessages(Dictionary<string, string> Replacements)`
- L670-673 _public method_ `public void IgnoreMessages(List<string> Ignore)`
- L675-696 _public method_ `public string FilterMessage(string Message)`

#### struct `AutomationUtils.GDK.GDKPackageGenerator.IntelligentInstallRecipe`  
`internal struct IntelligentInstallRecipe`  
_internal; L792-832_
- L794 _public field_ `public string Id`
- L795 _public field_ `public string[] FeatureIds`
- L796 _public field_ `public string[] Devices`
- L797 _public field_ `public string[] StoreIds`
- L799-831 _internal method_ `internal static IEnumerable<IntelligentInstallRecipe> GetFromConfig(ProjectParams Params, DeploymentContext SC, string IniSection_TargetSettings)`

#### class `AutomationUtils.GDK.GDKPackageGenerator.IntelligentInstallFeature`  
`internal class IntelligentInstallFeature`  
_internal; L835-901_
- L837 _public field_ `public string Id`
- L838 _public field_ `public string[] Tags`
- L839 _public field_ `public bool bHidden`
- L840 _public field_ `public string DisplayNameResourceId`
- L841 _public field_ `public string ImageFileName`
- L843-892 _internal method_ `internal static IEnumerable<IntelligentInstallFeature> GetFromConfig(ProjectParams Params, DeploymentContext SC, string IniSection_TargetSettings)`
- L894-900 _internal method_ `internal void AddTag(string Tag)`

#### class `AutomationUtils.GDK.GDKPackageGenerator.IntelligentInstallChunk`  
`internal class IntelligentInstallChunk`  
_internal; L904-1007_
- L906 _public field_ `public int ChunkId`
- L907 _public field_ `public string ChunkTag = ""`
- L909 _public field_ `public string Detail_Devices = ""`
- L910 _public field_ `public string Detail_Languages = ""`
- L911 _public field_ `public bool Detail_bRequiredForLaunch = false`
- L914 _public property_ `public bool IsOnDemand => ...`
- L915 _public property_ `public string[] Tags => ...`
- L916 _public property_ `public string[] CultureIDs => ...`
- L918-1006 _internal method_ `internal static IEnumerable<IntelligentInstallChunk> GetFromConfig(ProjectParams Params, DeploymentContext SC, string IniSection_TargetSettings)`

#### class `AutomationUtils.GDK.GDKPackageGenerator.GDKBundleSettings`  
`protected class GDKBundleSettings : BundleUtils.BundleSettings`  
_protected; L1010-1014_
- inherits: `BundleUtils.BundleSettings`
- L1012 _public property_ `public int ChunkID { get; set; }`
- L1013 _public property_ `public string PlatformChunkName { get; set; }`

#### struct `AutomationUtils.GDK.GDKPackageGenerator.CustomChunkMapping`  
`protected struct CustomChunkMapping`  
_protected; L1022-1052_
- desc: The CustomChunkMapping table is used to assign files to specific chunks using wildcard path matching. +CustomChunkMapping=(Pattern="shootergame/content/movies/*",ChunkId=1) +CustomChunkMapping=(Pattern="shootergame/content/movies/movie1.mp4",ChunkId=1)
- L1024 _public field_ `public string Pattern`
- L1025 _public field_ `public int ChunkId`
- L1027-1051 _internal method_ `internal static IEnumerable<CustomChunkMapping> GetFromConfig(ProjectParams Params, DeploymentContext SC, string IniSection_TargetSettings)`

#### struct `AutomationUtils.GDK.GDKPackageGenerator.DLCChunks`  
`protected struct DLCChunks`  
_protected; L1056-1095_
- L1059 _public field_ `public string DLCName`
- L1060 _public field_ `public int ChunkId`
- L1062-1094 _internal method_ `internal static Dictionary<string,IEnumerable<int>> GetFromConfig(ProjectParams Params, DeploymentContext SC, string IniSection_TargetSettings)`

#### class `AutomationUtils.GDK.GDKPackageGenerator.PackageFileDesc`  
`class PackageFileDesc`  
_private*; L1102-1110_
- L1104 _public field_ `public StagedFileReference File`
- L1105 _public field_ `public string RelativeSourceDir`
- L1106 _public field_ `public int ChunkId`
- L1107 _public field_ `public bool bAllowInManifest`
- L1108 _public field_ `public bool bAllowInLayout`
- L1109 _public field_ `public bool bAutoGenerated`

### `Source/Programs/AutomationTool/Microsoft/Properties/AssemblyInfo.cs` (Microsoft.Automation)
_(no declarations)_

