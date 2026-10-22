# CSharp / Turnkey.Automation

- project root: `Source/Programs/AutomationTool/Turnkey`
- files: 36; symbols: 416
- symbol kinds: class=42, const=2, ctor=18, delegate=1, dtor=1, enum=5, enumerator=42, field=90, method=192, property=22, struct=1
- access marked `*` is implicit (not written in source)

### `Source/Programs/AutomationTool/Turnkey/BuildInfo.cs` (Turnkey.Automation)


#### class `Turnkey.BuildSource`  
`public class BuildSource`  
_public; L11-27_
- L13 _public field_ `public string Project`
- L14 _public field_ `public CopyAndRun[] Sources`
- L15 _public field_ `public string BuildEnumerationSuffix`
- L20-26 _internal method_ `internal void PostDeserialize()`

### `Source/Programs/AutomationTool/Turnkey/Commands/ConfigTester.cs` (Turnkey.Automation)


#### class `Turnkey.Commands.ConfigTester`  
`class ConfigTester : TurnkeyCommand`  
_internal*; L14-39_
- inherits: `TurnkeyCommand`
- L16 _protected property_ `protected override CommandGroup Group => ...`
- L18-38 _protected method_ `protected override void Execute(string[] CommandOptions)`

### `Source/Programs/AutomationTool/Turnkey/Commands/Control.cs` (Turnkey.Automation)


#### class `Turnkey.Commands.Control`  
`class Control : TurnkeyCommand`  
_internal*; L12-62_
- inherits: `TurnkeyCommand`
- L14 _protected property_ `protected override CommandGroup Group => ...`
- L16 _private delegate_ `private delegate void PerformOperation(ITargetDevice Device)`
- L18-61 _protected method_ `protected override void Execute(string[] CommandOptions)`

### `Source/Programs/AutomationTool/Turnkey/Commands/CreateBuild.cs` (Turnkey.Automation)


#### class `Turnkey.Commands.CreateBuild`  
`internal class CreateBuild : TurnkeyCommand`  
_internal; L43-809_
- inherits: `TurnkeyCommand`
- L45 _protected property_ `protected override CommandGroup Group => ...`
- L47 _private* const_ `const string SettingsSection = "/Script/UnrealEd.ProjectPackagingSettings"`
- L49-55 _internal method_ `internal static string[] SplitCommandLine(string CommandLine)`
- L57-97 _private* method_ `string GetArchiveDirectory(string[] CommandOptions, FileReference ProjectFile)`
- L99-113 _private method_ `private static string GetPlatformSetting(ConfigHierarchy Config, UnrealTargetPlatform Platform, string PerPlatformKey, string GenericKey, string Default)`
- L116 _private* field_ `static Dictionary<TargetType, string> UETargets = ...`
- L116 _private* field_ `static Dictionary< UETargets = new Dictionary<TargetType, string>() { { TargetType.Game, "UnrealGame" }, { TargetType.Client, "UnrealClient" }, { TargetType.Server, "UnrealServer" }, }`
- L123-351 _public method_ `public static string MakeCommandLineFromPackagingSettings(UnrealTargetPlatform Platform, FileReference ProjectFile, string ExistingCommandLine)`
- L353-452 _private* method_ `static string MakeCommandLineInteractively(List<UnrealTargetPlatform> Platforms, FileReference ProjectFile, string ExistingCommandLine, bool bBuild, bool bCook, bool bStage, bool bPackage, bool bArchive)`
- L454 _private* const_ `const string DividerLine = "================================================\n"`
- L456-808 _protected method_ `protected override void Execute(string[] CommandOptions)`

### `Source/Programs/AutomationTool/Turnkey/Commands/DeviceAutoSoftwareUpdates.cs` (Turnkey.Automation)


#### class `Turnkey.Commands.DeviceAutoSoftwareUpdates`  
`class DeviceAutoSoftwareUpdates : TurnkeyCommand`  
_internal*; L10-50_
- inherits: `TurnkeyCommand`
- L12 _protected property_ `protected override CommandGroup Group => ...`
- L14-49 _protected method_ `protected override void Execute(string[] CommandOptions)`

### `Source/Programs/AutomationTool/Turnkey/Commands/ExecuteBuild.cs` (Turnkey.Automation)


#### class `Turnkey.Commands.ExecuteBuild`  
`class ExecuteBuild : TurnkeyCommand`  
_internal*; L14-322_
- inherits: `TurnkeyCommand`
- L16 _protected property_ `protected override CommandGroup Group => ...`
- L18-188 _protected method_ `protected override void Execute(string[] CommandOptions)`
- L190-203 _internal method_ `internal static void ExecuteBuildCookRun(string Params)`
- L205-306 _private* method_ `string GetIniSetting(string Spec, DirectoryReference ProjectDir, UnrealTargetPlatform Platform)`
- L308-321 _private method_ `private string PerformIniReplacements(string Params, DirectoryReference ProjectDir, UnrealTargetPlatform Platform)`

### `Source/Programs/AutomationTool/Turnkey/Commands/Help.cs` (Turnkey.Automation)


#### class `Turnkey.Commands.Help`  
`class Help : TurnkeyCommand`  
_internal*; L12-66_
- inherits: `TurnkeyCommand`
- L14 _protected property_ `protected override CommandGroup Group => ...`
- L16-65 _protected method_ `protected override void Execute(string[] CommandOptions)`

### `Source/Programs/AutomationTool/Turnkey/Commands/InstallBuild.cs` (Turnkey.Automation)


#### class `Turnkey.Commands.InstallBuild`  
`class InstallBuild : TurnkeyCommand`  
_internal*; L12-135_
- inherits: `TurnkeyCommand`
- L14 _protected property_ `protected override CommandGroup Group => ...`
- L16-134 _protected method_ `protected override void Execute(string[] CommandOptions)`

### `Source/Programs/AutomationTool/Turnkey/Commands/InstallSdk.cs` (Turnkey.Automation)


#### class `Turnkey.Commands.InstallSdk`  
`class InstallSdk : TurnkeyCommand`  
_internal*; L13-341_
- inherits: `TurnkeyCommand`
- L15 _protected property_ `protected override CommandGroup Group => ...`
- L17-24 _protected method_ `protected override Dictionary<string, string[]> GetExtendedCommandsWithOptions()`
- L27-328 _protected method_ `protected override void Execute(string[] CommandOptions)`
- L331-339 _private method_ `private DeviceInfo GetDevice(AutomationTool.Platform Platform, string DeviceName)`

### `Source/Programs/AutomationTool/Turnkey/Commands/ListPlatforms.cs` (Turnkey.Automation)


#### class `Turnkey.Commands.ListPlatforms`  
`class ListPlatforms : TurnkeyCommand`  
_internal*; L10-111_
- inherits: `TurnkeyCommand`
- L12 _protected property_ `protected override CommandGroup Group => ...`
- L14-110 _protected method_ `protected override void Execute(string[] CommandOptions)`

### `Source/Programs/AutomationTool/Turnkey/Commands/ListSdks.cs` (Turnkey.Automation)


#### class `Turnkey.Commands.ListSdks`  
`class ListSdks : TurnkeyCommand`  
_internal*; L11-51_
- inherits: `TurnkeyCommand`
- L13 _protected property_ `protected override CommandGroup Group => ...`
- L15-50 _protected method_ `protected override void Execute(string[] CommandOptions)`

### `Source/Programs/AutomationTool/Turnkey/Commands/ManageSettings.cs` (Turnkey.Automation)


#### class `Turnkey.Commands.ManageSettings`  
`class ManageSettings : TurnkeyCommand`  
_internal*; L11-106_
- inherits: `TurnkeyCommand`
- L13 _protected property_ `protected override CommandGroup Group => ...`
- L15-21 _protected method_ `protected override Dictionary<string, string[]> GetExtendedCommandsWithOptions()`
- L23-105 _protected method_ `protected override void Execute(string[] CommandOptions)`

### `Source/Programs/AutomationTool/Turnkey/Commands/QuickSwitchSdk.cs` (Turnkey.Automation)


#### class `Turnkey.Commands.QuickSwitchSdk`  
`class QuickSwitchSdk : TurnkeyCommand`  
_internal*; L11-68_
- inherits: `TurnkeyCommand`
- L13 _protected property_ `protected override CommandGroup Group => ...`
- L15-67 _protected method_ `protected override void Execute(string[] CommandOptions)`

### `Source/Programs/AutomationTool/Turnkey/Commands/VerifySdk.cs` (Turnkey.Automation)


#### class `Turnkey.Commands.VerifySdk`  
`class VerifySdk : TurnkeyCommand`  
_internal*; L15-339_
- inherits: `TurnkeyCommand`
- L17 _protected property_ `protected override CommandGroup Group => ...`
- L19-338 _protected method_ `protected override void Execute(string[] CommandOptions)`

### `Source/Programs/AutomationTool/Turnkey/CopyAndRun.cs` (Turnkey.Automation)


#### class `Turnkey.CopyAndRun`  
`public class CopyAndRun`  
_public; L15-164_
- attrs: `[XmlRoot(ElementName = "Source")]`
- L19 _public field_ `public string PlatformString = null` — attrs: `[XmlElement("HostPlatform")]`
- L22 _public field_ `public UnrealTargetPlatform? Platform = null` — attrs: `[XmlIgnore]`
- L24 _public field_ `public string Copy = null`
- L26 _public field_ `public string CommandPath = null`
- L28 _public field_ `public string CommandLine = null`
- L33-34 _private* ctor_ `CopyAndRun()` — Needs a parameterless constructor for Xml deserialization
- L40-43 _public ctor_ `public CopyAndRun(string CopyOperation)` — Create a one-of local object with just a Copy operation
- L44-51 _public ctor_ `public CopyAndRun(CopyAndRun Other)`
- L53-65 _internal method_ `internal void PostDeserialize()`
- L67-163 _public method_ `public static int RunExternalCommand(string CommandPath, string CommandLine, ITurnkeyContext TurnkeyContext, bool bUnattended, bool bRequiresPrivilegeElevation, bool bCreateWindow)`

### `Source/Programs/AutomationTool/Turnkey/CopyProvider.cs` (Turnkey.Automation)


#### enum `Turnkey.CopyExecuteSpecialMode`  
`public enum CopyExecuteSpecialMode`  
_public; L18-23_
- attrs: `[Flags]`
- L20 _public* enumerator_ `None = 0`
- L21 _public* enumerator_ `UsePermanentStorage = 1`
- L22 _public* enumerator_ `DownloadOnly = 2`

#### class `Turnkey.CopyProvider`  
`abstract class CopyProvider`  
_internal*; L25-217_
- L30 _public property_ `public abstract string ProviderToken { get; }` — Unique provider token to direct a copy operation ("perforce://UE5/Main/...)
- L39 _public method_ `public abstract string Execute(string Operation, CopyExecuteSpecialMode SpecialMode, string SpecialModeHint)` — Perform the copy operation
- L48 _public method_ `public abstract string[] Enumerate(string Operation, List<List<string>> Expansions)` — Uses the CopyProvider to return a list of files and directories (a directory MUST end with a / or \ character to denote directory since we can't test locally what type it is
- L53 _private field_ `private static Dictionary<string, CopyProvider> CachedProviders = ...`
- L53 _private field_ `private static Dictionary< CachedProviders = new Dictionary<string, CopyProvider>(StringComparer.OrdinalIgnoreCase)`
- L55-66 _private* ctor_ `static CopyProvider()`
- L68-98 _private method_ `private static bool ParseOperation(string Operation, out CopyProvider Provider, out string ProviderParam, bool bCanFail)`
- L107-202 _public method_ `public static string ExecuteCopy(string CopyOperation, CopyExecuteSpecialMode SpecialMode = CopyExecuteSpecialMode.None, string SpecialModeHint = null)` — Runs a Copy command, and returns the local path (either a directory or a file, depending on the operation
- L204-216 _public method_ `public static string[] ExecuteEnumerate(string CopyOperation, List<List<string>> Expansions=null)`

#### class `Turnkey.TurnkeyContextImpl`  
`class TurnkeyContextImpl : ITurnkeyContext`  
_internal*; L219-323_
- inherits: `ITurnkeyContext`
- L221 _public field_ `public List<string> ErrorMessages = new List<string>()`
- L223-237 _public method_ `public string RetrieveFileSource(object HintObject)`
- L239-254 _public method_ `public int RunExternalCommand(string Command, string Params, bool bRequiresPrivilegeElevation, bool bUnattended, bool bCreateWindow)`
- L256-295 _public method_ `public string RetrieveFileSource(string Name, string InType, string InPlatform, string SubType)`
- L297-300 _public method_ `public string GetVariable(string VariableName)`
- L302-305 _public method_ `public void Log(string Message)`
- L307-311 _public method_ `public void ReportError(string Message)`
- L313-316 _public method_ `public void PauseForUser(string Message)`
- L318-321 _public method_ `public int ReadInputInt(string Prompt, List<string> Options, bool bIsCancellable, int DefaultValue)`

### `Source/Programs/AutomationTool/Turnkey/FileSource.cs` (Turnkey.Automation)


#### class `Turnkey.CopySource`  
`public class CopySource`  
_public; L16-80_
- L20 _public field_ `public string HostPlatformString = null` — attrs: `[XmlAttribute("HostPlatform")]`
- L22 _public field_ `public UnrealTargetPlatform? Platform = null` — attrs: `[XmlIgnore]`
- L26 _public field_ `public string CopyOverride = null` — attrs: `[XmlAttribute]`
- L29 _public field_ `public string Operation` — attrs: `[XmlText]`
- L34-35 _public ctor_ `public CopySource()` — Needs a parameterless constructor for Xml deserialization
- L37-43 _public ctor_ `public CopySource(CopySource Other)`
- L45-48 _public method_ `public string GetOperation()`
- L50-61 _public method_ `public void PostDeserialize()`
- L63-66 _public method_ `public bool ShouldExecute()`
- L67-75 _public method_ `public bool NeedsExpansion(out string OperationForExpansion)`
- L76-79 _public method_ `public bool NeedsExpansion()`

#### class `Turnkey.FileSource`  
`public class FileSource`  
_public; L82-1022_
- L98 _public field_ `public string PlatformString = null` — attrs: `[XmlElement("Platform")]`
- L100 _private field_ `private List<UnrealTargetPlatform> Platforms` — attrs: `[XmlIgnore]`
- L103 _public field_ `public string TypeString = null` — attrs: `[XmlElement("Type")]`
- L105 _public field_ `public SourceType Type = SourceType.Full` — attrs: `[XmlIgnore]`
- L107 _public field_ `public string SpecificSDKType = null` — attrs: `[XmlIgnore]`
- L110 _public field_ `public CopySource[] Sources = null` — attrs: `[XmlElement("Source")]`
- L114 _public field_ `public string Version = null`
- L115 _public field_ `public string Name = null`
- L116 _public field_ `public string AllowedFlashDeviceTypes = null`
- L119 _public field_ `public string Project`
- L120 _public field_ `public string BuildPlatformEnumerationSuffix`
- L123-133 _public method_ `public static FileSource CreateCodeSpecifiedSource(string Name, string Version, UnrealTargetPlatform Platform)`
- L135-168 _public method_ `public FileSource CloneForExpansion(string NewValue, Action<FileSource, string> Setter)`
- L196-199 _public method_ `public bool NeedsFileExpansion()`
- L201-204 _public method_ `public bool SupportsPlatform(UnrealTargetPlatform Platform)`
- L206-209 _public method_ `public bool IsSdkType()`
- L211-248 _public method_ `public bool IsVersionValid(UnrealTargetPlatform Platform, DeviceInfo Device=null)`
- L250-253 _public method_ `public UnrealTargetPlatform[] GetPlatforms()`
- L256-260 _public method_ `public string GetCopySourceOperation()`
- L262-303 _public method_ `static public FileSource ChooseBest(List<FileSource> Sdks, UEBuildPlatformSDK PlatformSDK)`
- L305-391 _public method_ `static public FileSource FindMatchingSdk(AutomationTool.Platform Platform, SourceType[] TypePriority, bool bSelectBest, string DeviceType = null, string CurrentSdk = null, string SpecificType = null)`
- L393-428 _public method_ `public bool DownloadOrInstall(UnrealTargetPlatform Platform, ITurnkeyContext TurnkeyContext, DeviceInfo Device, bool bUnattended, bool bSdkAlreadyInstalled)`
- L751 _private field_ `static private Regex ExpansionRegex = new Regex(@"^listexpansion:(\w*)=(.*)$")`
- L752-795 _private method_ `private List<FileSource> CheckForListExpansions(List<FileSource> Sources, Func<FileSource, string> Getter, Action<FileSource, string> Setter)`
- L797-813 _internal method_ `internal List<FileSource> ConditionalExpandLists()`
- L814-923 _internal method_ `internal List<FileSource> ExpandCopySource()`
- L926-986 _internal method_ `internal void PostDeserialize()`
- L989-992 _private method_ `private string Indent(int Num)`
- L994-997 _public method_ `public override string ToString()`
- L998-1021 _public method_ `public string ToString(int BaseIndent)`

#### enum `Turnkey.FileSource.SourceType`  
`public enum SourceType`  
_public; L84-93_
- L86 _public* enumerator_ `BuildOnly`
- L87 _public* enumerator_ `AutoSdk`
- L88 _public* enumerator_ `RunOnly`
- L89 _public* enumerator_ `Full`
- L90 _public* enumerator_ `Flash`
- L91 _public* enumerator_ `Misc`
- L92 _public* enumerator_ `Build`

### `Source/Programs/AutomationTool/Turnkey/IOProvider.cs` (Turnkey.Automation)


#### class `Turnkey.IOProvider`  
`abstract class IOProvider`  
_internal*; L11-27_
- L13 _public method_ `public abstract void Log(string Message, bool bAppendNewLine)`
- L15-18 _public method_ `public virtual void Report(string Message, bool bAppendNewLine)`
- L20 _public method_ `public abstract void PauseForUser(string Message, bool bAppendNewLine)`
- L22 _public method_ `public abstract string ReadInput(string Prompt, string DefaultValue, bool bAppendNewLine)`
- L24 _public method_ `public abstract int ReadInputInt(string Prompt, List<string> Options, bool bIsCancellable, int DefaultValue, bool bAppendNewLine)`
- L26 _public method_ `public abstract bool GetUserConfirmation(string Message, bool bDefaultValue, bool bAppendNewLine)`

### `Source/Programs/AutomationTool/Turnkey/LocalCache.cs` (Turnkey.Automation)


#### class `Turnkey.CacheData`  
`public class CacheData`  
_public; L11-46_
- attrs: `[Serializable]`
- L13 _public field_ `public string LocalPath`
- L14 _public field_ `public string Version`
- L15 _public field_ `public bool bIsFile`
- L16 _public field_ `public Dictionary<string, long> FileToTimeCache = ...`
- L16 _public field_ `public Dictionary< FileToTimeCache = new Dictionary<string, long>()`
- L18-21 _public ctor_ `public CacheData()`
- L23-44 _public ctor_ `public CacheData(string LocalPath, string Version)`

#### class `Turnkey.SavedCache`  
`public class SavedCache`  
_public; L49-56_
- attrs: `[Serializable]`
- L51 _public field_ `public Dictionary<string, CacheData> Cache = ...`
- L51 _public field_ `public Dictionary< Cache = new Dictionary<string, CacheData>()`
- L52-55 _public ctor_ `public SavedCache()`

#### class `Turnkey.LocalCache`  
`static class LocalCache`  
_internal*; L60-260_
- L62-71 _public method_ `public static string CreateTempDirectory()`
- L74-87 _public method_ `public static void CacheLocationByTag(string Tag, string CachePath, string VersionMatch = "")`
- L89-121 _public method_ `public static string GetCachedPathByTag(string Tag, string VersionMatch = "")`
- L123-126 _public method_ `public static string CreateDownloadCacheDirectory()`
- L128-132 _public method_ `public static string GetInstallCacheDirectory()`
- L139 _public field_ `public static string TempCacheLocation = Path.Combine(Path.GetTempPath(), "Turnkey", "TempFiles")`
- L141 _public field_ `public static string DownloadCacheLocation = Path.Combine(Path.GetTempPath(), "Turnkey", "DownloadCache")`
- L145-155 _private* method_ `static void SerializeObject(SavedCache Object, string Filename)`
- L157-187 _private* method_ `static SavedCache DeserializeObject(string Filename)`
- L191 _private* field_ `static SavedCache TagToDownloadCache`
- L192 _private* field_ `static string TagCacheFile = Path.Combine(DownloadCacheLocation, "TagCache.xml")`
- L195 _private* field_ `static SavedCache TagToTempCache = new SavedCache()`
- L197-237 _private* ctor_ `static LocalCache()`
- L239-259 _public method_ `public static void CleanCacheByTag(string Tag)`

### `Source/Programs/AutomationTool/Turnkey/Properties/AssemblyInfo.cs` (Turnkey.Automation)
_(no declarations)_


### `Source/Programs/AutomationTool/Turnkey/Properties/Resources.Designer.cs` (Turnkey.Automation)


#### class `Gauntlet.Automation.Properties.Resources`  
`internal class Resources`  
_internal; L25-62_
- attrs: `[global::System.CodeDom.Compiler.GeneratedCodeAttribute("System.Resources.Tools.StronglyTypedResourceBuilder", "4.0.0.0")] [global::System.Diagnostics.DebuggerNonUserCodeAttribute()] [global::System.Runtime.CompilerServices.CompilerGeneratedAttribute()]`
- L27 _private field_ `private static global::System.Resources.ResourceManager resourceMan`
- L29 _private field_ `private static global::System.Globalization.CultureInfo resourceCulture`
- L32-33 _internal ctor_ `internal Resources()` — attrs: `[global::System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1811:AvoidUncalledPrivateCode")]`
- L39-47 _internal property_ `internal static global::System.Resources.ResourceManager ResourceManager { get; }` — attrs: `[global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]` — Returns the cached ResourceManager instance used by this class.
- L54-61 _internal property_ `internal static global::System.Globalization.CultureInfo Culture { get; set; }` — attrs: `[global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]` — Overrides the current thread's CurrentUICulture property for all resource lookups using this strongly typed resource class.

### `Source/Programs/AutomationTool/Turnkey/Providers/ConsoleIOProvider.cs` (Turnkey.Automation)


#### class `Turnkey.ConsoleIOProvider`  
`class ConsoleIOProvider : IOProvider`  
_internal*; L10-115_
- inherits: `IOProvider`
- L12-22 _public method_ `public override void Log(string Message, bool bAppendNewLine)`
- L24-29 _public method_ `public override void PauseForUser(string Message, bool bAppendNewLine)`
- L31-47 _public method_ `public override string ReadInput(string Prompt, string Default, bool bAppendNewLine)`
- L49-100 _public method_ `public override int ReadInputInt(string Prompt, List<string> Options, bool bIsCancellable, int DefaultValue, bool bAppendNewLine)`
- L102-114 _public method_ `public override bool GetUserConfirmation(string Message, bool bDefaultValue, bool bAppendNewLine)`

### `Source/Programs/AutomationTool/Turnkey/Providers/GoogleDriveCopyProvider.cs` (Turnkey.Automation)


#### class `Turnkey.GoogleDriveCopyProvider`  
`class GoogleDriveCopyProvider : CopyProvider`  
_internal*; L13-511_
- inherits: `CopyProvider`
- L15 _public property_ `public override string ProviderToken { get; }`
- L18 _private field_ `private static DriveServiceHelper ServiceHelper = null`
- L19 _private field_ `private Dictionary<string, Google.Apis.Drive.v3.Data.File> PathToFileCache`
- L19 _private field_ `private Dictionary< PathToFileCache`
- L22-151 _public method_ `public override string Execute(string Operation, CopyExecuteSpecialMode SpecialMode, string SpecialModeHint)`
- L154-206 _public method_ `public override string[] Enumerate(string Operation, List<List<string>> Expansions)`
- L209-221 _private method_ `private Google.Apis.Drive.v3.Data.File GetFileForId(string Id)`
- L223-257 _private method_ `private bool Prepare()`
- L288-402 _private method_ `private Google.Apis.Drive.v3.Data.File GetFileForPath(string DrivePath)`
- L406-421 _private method_ `private void DownloadFile(Google.Apis.Drive.v3.Data.File File, string LocalPath)`
- L423-510 _private method_ `private void ExpandWildcards(string Prefix, string PathString, Dictionary<string, Tuple<Google.Apis.Drive.v3.Data.File, List<string>>> Output, List<string> ExpansionSet)`

### `Source/Programs/AutomationTool/Turnkey/Providers/HttpCopyProvider.cs` (Turnkey.Automation)


#### class `Turnkey.HttpCopyProvider`  
`class HttpCopyProvider : CopyProvider`  
_internal*; L16-131_
- inherits: `CopyProvider`
- L18 _public property_ `public override string ProviderToken { get; }`
- L20-117 _public method_ `public override string Execute(string Operation, CopyExecuteSpecialMode SpecialMode, string SpecialModeHint)`
- L120-130 _public method_ `public override string[] Enumerate(string Operation, List<List<string>> Expansions)`

#### class `Turnkey.HttpsCopyProvider`  
`class HttpsCopyProvider : HttpCopyProvider`  
_internal*; L133-137_
- inherits: `HttpCopyProvider`
- L135 _public property_ `public override string ProviderToken { get; }`

### `Source/Programs/AutomationTool/Turnkey/Providers/HybridIOProvider.cs` (Turnkey.Automation)


#### class `Turnkey.HybridIOProvider`  
`class HybridIOProvider : ConsoleIOProvider`  
_internal*; L14-137_
- inherits: `ConsoleIOProvider`
- L16-18 _private* ctor_ `static HybridIOProvider()`
- L20-40 _private method_ `private string ShowMacDialog(string Prompt, string Default)`
- L42-73 _private method_ `private string ShowDialog(string Prompt, string Default, bool bIsList)`
- L75-78 _public method_ `public override void PauseForUser(string Message, bool bAppendNewLine)`
- L80-83 _public method_ `public override string ReadInput(string Prompt, string Default, bool bAppendNewLine)`
- L85-136 _public method_ `public override int ReadInputInt(string Prompt, List<string> Options, bool bIsCancellable, int DefaultValue, bool bAppendNewLine)`

### `Source/Programs/AutomationTool/Turnkey/Providers/NullCopyProvider.cs` (Turnkey.Automation)


#### class `Turnkey.NullCopyProvider`  
`class NullCopyProvider : CopyProvider`  
_internal*; L19-316_
- inherits: `CopyProvider`
- L21 _public property_ `public override string ProviderToken { get; }`
- L23-46 _private method_ `private void FixupOperation(ref string Operation)`
- L48-127 _public method_ `public override string Execute(string Operation, CopyExecuteSpecialMode SpecialMode, string SpecialModeHint)`
- L130-178 _private method_ `private bool VerifyPathAccess( string PathString )`
- L180-300 _private method_ `private void ExpandWildcards(string Prefix, string PathString, Dictionary<string, List<string>> Output, List<string> ExpansionSet)`
- L302-315 _public method_ `public override string[] Enumerate(string Operation, List<List<string>> Expansions)`

### `Source/Programs/AutomationTool/Turnkey/Providers/PerforceCopyProvider.cs` (Turnkey.Automation)


#### class `Turnkey.PerforceCopyProvider`  
`class PerforceCopyProvider : CopyProvider`  
_internal*; L14-357_
- inherits: `CopyProvider`
- L16 _public property_ `public override string ProviderToken { get; }`
- L19-71 _public method_ `public override string Execute(string Operation, CopyExecuteSpecialMode SpecialMode, string SpecialModeHint)`
- L73-111 _public method_ `public override string[] Enumerate(string Operation, List<List<string>> Expansions)`
- L116-131 _private method_ `private string GetDirectoryBeforeWildcard(string Input)`
- L134 _private field_ `static private P4Connection PerforceConnection = null`
- L135 _private field_ `static private P4ClientInfo PerforceClient = null`
- L137 _private field_ `static private string ConnectedRoot = null`
- L139-167 _private method_ `private P4ClientInfo DetectClientForStream(string Stream, string Username, string Hostname)`
- L169-189 _private method_ `private P4ClientInfo CanClientHandleOperation(string ClientName, string Operation, string Hostname)`
- L191-236 _private method_ `private P4ClientInfo DetectClientForDepot(string Operation, string Username, string Hostname)`
- L238-354 _private method_ `private bool PrepareForOperation(string Operation)`

### `Source/Programs/AutomationTool/Turnkey/Providers/ReportIOProvider.cs` (Turnkey.Automation)


#### class `Turnkey.ReportIOProvider`  
`class ReportIOProvider : ConsoleIOProvider`  
_internal*; L11-42_
- inherits: `ConsoleIOProvider`
- L13 _private field_ `private System.IO.StreamWriter Out`
- L15-18 _public ctor_ `public ReportIOProvider(string ReportFilename)`
- L20-31 _public method_ `public override void Report(string Message, bool bAppendNewLine)`
- L33-36 _public method_ `public override string ReadInput(string Prompt, string Default, bool bAppendNewLine)`
- L38-41 _public method_ `public override int ReadInputInt(string Prompt, List<string> Options, bool bIsCancellable, int DefaultValue, bool bAppendNewLine)`

### `Source/Programs/AutomationTool/Turnkey/Providers/TurnkeyEditorIOClient.cs` (Turnkey.Automation)


#### class `Turnkey.EditorIOClient`  
`class EditorIOClient : IOProvider`  
_internal*; L14-322_
- inherits: `IOProvider`
- L16 _private* field_ `readonly int Version = 1`
- L18 _private* field_ `int Port`
- L19 _private* field_ `Socket IOSocket`
- L20 _private* field_ `Lazy<IOProvider> FallbackIOProvider`
- L21 _private* field_ `bool bVerbose = false`
- L23-27 _public ctor_ `public EditorIOClient( int InPort )`
- L29-32 _private* dtor_ `~EditorIOClient()`
- L34-40 _private method_ `private void VerboseMessage( string Message )`
- L42-53 _public method_ `public override void Log(string Message, bool bAppendNewLine)`
- L55-79 _public method_ `public override void PauseForUser(string Message, bool bAppendNewLine)`
- L81-111 _public method_ `public override string ReadInput(string Prompt, string Default, bool bAppendNewLine)`
- L113-149 _public method_ `public override int ReadInputInt(string Prompt, List<string> Options, bool bIsCancellable, int DefaultValue, bool bAppendNewLine)`
- L151-182 _public method_ `public override bool GetUserConfirmation(string Message, bool bDefaultValue, bool bAppendNewLine)`
- L187-204 _private* method_ `bool Connect()`
- L206-214 _private* method_ `void Disconnect()`
- L216-270 _protected method_ `protected JsonObject ReceiveMessage()`
- L274-298 _protected method_ `protected bool SendMessage( Action<JsonWriter> MessageFunc )`
- L300-306 _protected method_ `protected bool SendAck()`
- L308-319 _protected method_ `protected bool SendAction( string Type, Action<JsonWriter> ActionFunc )`

### `Source/Programs/AutomationTool/Turnkey/SdkInfo.cs` (Turnkey.Automation)


#### class `Turnkey.SdkUtils`  
`static class SdkUtils`  
_internal*; L15-289_
- L48-159 _public method_ `static public LocalAvailability GetLocalAvailability(AutomationTool.Platform AutomationPlatform, bool bAllowUpdatingPrerequisites, TurnkeyContextImpl TurnkeyContext)`
- L162-288 _public method_ `public static bool SetupAutoSdk(FileSource Source, ITurnkeyContext TurnkeyContext, UnrealTargetPlatform Platform, bool bUnattended)`

#### enum `Turnkey.SdkUtils.LocalAvailability`  
`public enum LocalAvailability`  
_public; L18-46_
- attrs: `[Flags]`
- L20 _public* enumerator_ `None = 0`
- L21 _public* enumerator_ `AutoSdk_VariableExists = (1 << 0)`
- L22 _public* enumerator_ `AutoSdk_ValidVersionExists = (1 << 1)`
- L23 _public* enumerator_ `AutoSdk_InvalidVersionExists = (1 << 2)`
- L25 _public* enumerator_ `InstalledSdk_ValidInactiveVersionExists = (1 << 3)`
- L26 _public* enumerator_ `InstalledSdk_ValidVersionExists = (1 << 4)`
- L27 _public* enumerator_ `InstalledSdk_InvalidVersionExists = (1 << 5)`
- L29 _public* enumerator_ `Platform_ValidHostPrerequisites = (1 << 6)`
- L30 _public* enumerator_ `Platform_InvalidHostPrerequisites = (1 << 7)`
- L32 _public* enumerator_ `Device_InvalidPrerequisites = (1 << 8)`
- L33 _public* enumerator_ `Device_InstallSoftwareValid = (1 << 9)`
- L34 _public* enumerator_ `Device_InstallSoftwareInvalid = (1 << 10)`
- L35 _public* enumerator_ `Device_CannotConnect = (1 << 11)`
- L37 _public* enumerator_ `Support_FullSdk = (1 << 12)`
- L38 _public* enumerator_ `Support_AutoSdk = (1 << 13)`
- L40 _public* enumerator_ `Sdk_HasBestVersion = (1 << 14)`
- L42 _public* enumerator_ `Device_AutoSoftwareUpdates_Disabled = (1 << 15)`
- L43 _public* enumerator_ `Device_AutoSoftwareUpdates_Enabled = (1 << 16)`
- L45 _public* enumerator_ `Host_Unsupported = (1 << 17)`

### `Source/Programs/AutomationTool/Turnkey/Turnkey.Automation.cs` (Turnkey.Automation)


#### class `Turnkey.Turnkey`  
`class Turnkey : BuildCommand`  
_internal*; L12-115_
- inherits: `BuildCommand`
- L14-40 _public method_ `public override ExitCode Execute()`
- L42 _private* field_ `static bool bHasBeenInitialized = false`
- L43-101 _public method_ `public static ExitCode Execute(IOProvider IOProvider, BuildCommand CommandUtilHelper)`
- L105-111 _private method_ `private static void SetupVisuals()`

### `Source/Programs/AutomationTool/Turnkey/TurnkeyCommand.cs` (Turnkey.Automation)


#### class `Turnkey.CommandInfo`  
`class CommandInfo`  
_internal*; L12-30_
- L14 _public field_ `public TurnkeyCommand Command`
- L15 _public field_ `public string DisplayString`
- L16 _public field_ `public string[] Options`
- L18-23 _public ctor_ `public CommandInfo(TurnkeyCommand InCommand)`
- L24-29 _public ctor_ `public CommandInfo(TurnkeyCommand InCommand, string InDisplayString, string[] InOptions)`

#### class `Turnkey.TurnkeyCommand`  
`abstract class TurnkeyCommand`  
_internal*; L32-178_
- L43 _protected property_ `protected abstract CommandGroup Group { get; }`
- L44 _protected method_ `protected abstract void Execute(string[] CommandOptions)`
- L45-48 _protected method_ `protected virtual Dictionary<string, string[]> GetExtendedCommandsWithOptions()`
- L49-52 _internal method_ `internal void InternalExecute(string[] CommandOptions)`
- L56 _private field_ `private static Dictionary<string, TurnkeyCommand> CachedCommandsByName = ...`
- L56 _private field_ `private static Dictionary< CachedCommandsByName = new Dictionary<string, TurnkeyCommand>(StringComparer.OrdinalIgnoreCase)`
- L57 _private field_ `private static List<CommandInfo> CachedCommandsByIndex = new List<CommandInfo>()`
- L58 _private field_ `private static Dictionary<CommandGroup, List<CommandInfo>> CachedCommandsByGroup = ...`
- L58 _private field_ `private static Dictionary< CachedCommandsByGroup = new Dictionary<CommandGroup, List<CommandInfo>>()`
- L60-103 _private* ctor_ `static TurnkeyCommand()`
- L105 _private* field_ `static bool bExitAfterCommand = false`
- L106-109 _public method_ `public static void ExitTurnkeyLoopAfterCommand()`
- L111-156 _public method_ `public static bool ExecuteCommand(string CommandString=null)`
- L158-177 _private method_ `private static int PromptForCommand()`

#### enum `Turnkey.TurnkeyCommand.CommandGroup`  
`protected enum CommandGroup`  
_protected; L34-41_
- L36 _public* enumerator_ `Sdk`
- L37 _public* enumerator_ `Builds`
- L38 _public* enumerator_ `Informational`
- L39 _public* enumerator_ `Settings`
- L40 _public* enumerator_ `Misc`

### `Source/Programs/AutomationTool/Turnkey/TurnkeyGauntletUtils.cs` (Turnkey.Automation)


#### class `Turnkey.TurnkeyGauntletUtils`  
`static class TurnkeyGauntletUtils`  
_internal*; L12-77_
- L15-27 _public method_ `static public ITargetDevice GetGauntletDevice(UnrealTargetPlatform Platform, string DeviceName)`
- L29-41 _public method_ `static public ITargetDevice GetGauntletDevice(DeviceInfo Device)`
- L43-55 _public method_ `static public List<ITargetDevice> GetGauntletDevices(UnrealTargetPlatform Platform, List<string> DeviceNames)`
- L57-60 _public method_ `static public List<ITargetDevice> GetGauntletDevices(List<DeviceInfo> Devices)`
- L62-74 _public method_ `static public List<ITargetDevice> GetDefaultGauntletDevices(UnrealTargetPlatform Platform)`

### `Source/Programs/AutomationTool/Turnkey/TurnkeyManifest.cs` (Turnkey.Automation)


#### class `Turnkey.TurnkeyManifest`  
`public class TurnkeyManifest`  
_public; L16-264_
- L18 _private field_ `static private string StandardManifestName = "TurnkeyManifest.xml"`
- L21 _public field_ `public FileSource[] FileSources = null` — attrs: `[XmlElement("FileSource")]`
- L24 _public field_ `public string[] AdditionalManifests = null` — attrs: `[XmlArrayItem(ElementName = "Manifest")]`
- L26 _public field_ `public SavedSetting[] SavedSettings = null`
- L28-62 _internal method_ `internal void PostDeserialize()`
- L64 _private* field_ `static List<FileSource> DiscoveredFileSources = null`
- L66-76 _public method_ `public static List<UnrealTargetPlatform> GetPlatformsWithSdks()`
- L78-88 _public method_ `public static List<string> GetProjectsWithBuilds()`
- L91-94 _public method_ `public static List<FileSource> GetAllDiscoveredFileSources()`
- L96-121 _private method_ `private static List<FileSource> ExpandFilteredSources(List<FileSource> Sources)`
- L123-140 _public method_ `public static List<FileSource> FilterDiscoveredFileSources(UnrealTargetPlatform? Platform, FileSource.SourceType? Type)`
- L142-150 _public method_ `public static List<FileSource> FilterDiscoveredBuilds(string Project)`
- L152-192 _public method_ `public static void DiscoverManifests()`
- L194-258 _public method_ `public static List<TurnkeyManifest> LoadManifestsFromProvider(string EnumerationOperation)`
- L260-263 _public method_ `public void Write(string Path)`

### `Source/Programs/AutomationTool/Turnkey/TurnkeySettings.cs` (Turnkey.Automation)


#### struct `Turnkey.SavedSetting`  
`public struct SavedSetting`  
_public; L12-16_
- L14 _public field_ `public string Variable`
- L15 _public field_ `public string Value`

#### class `Turnkey.UserSetting`  
`public class UserSetting`  
_public; L18-30_
- L20 _public field_ `public string VariableName`
- L21 _public field_ `public string DefaultValue`
- L22 _public field_ `public string Description`
- L24-29 _public ctor_ `public UserSetting(string VariableName, string DefaultValue, string Description)`

#### class `Turnkey.TurnkeySettings`  
`static public class TurnkeySettings`  
_public; L33-157_
- L35 _public field_ `public static string UserSettingManifestLocation = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData), "Unreal Engine", "UnrealTurnkey", "UserSettingsManifest.xml")`
- L37 _public field_ `public static UserSetting[] AllUserSettings = { new UserSetting("User_QuickSwitchSdkLocation", null, "Location for downloaded Sdks to be stored (currently just for Google Drive, perforce will sync per clientspec)"), new UserSetting("User_AppleDev ...`
- L49 _public field_ `public static UserSetting[] AllStudioSettings = { new UserSetting("Studio_AppleSigningCertPassword", null, "A shared password that is used across Apple Signing Certificates"), new UserSetting("Studio_GoogleDriveCredentials", null, "The location of  ...`
- L59 _private* field_ `static Dictionary<string, string> SetUserSettings = ...`
- L59 _private* field_ `static Dictionary< SetUserSettings = new Dictionary<string, string>()`
- L62-79 _public method_ `public static void Initialize()`
- L81-84 _public method_ `public static bool HasSetUserSetting(string VariableName)`
- L85-88 _public method_ `public static Dictionary<string, string> GetSetUserSettings()`
- L90-120 _public method_ `public static string GetUserSetting(string VariableName)`
- L122-125 _public method_ `public static string GetUserSettingIfSet(string VariableName, string DefaultIfNotSet)`
- L127-140 _public method_ `public static string SetUserSetting(string VariableName, string Value)`
- L143-156 _public method_ `public static void Save()`

### `Source/Programs/AutomationTool/Turnkey/TurnkeyUtils.cs` (Turnkey.Automation)


#### class `Turnkey.TurnkeyUtils`  
`static class TurnkeyUtils`  
_internal*; L19-913_
- L22 _public field_ `static public BuildCommand CommandUtilHelper`
- L25 _public field_ `static public ExitCode ExitCode = ExitCode.Success`
- L27-43 _public method_ `static public void Initialize(IOProvider InIOProvider, BuildCommand InCommandUtilHelper)`
- L47 _private* field_ `static Dictionary<string, string> TurnkeyVariables = ...`
- L47 _private* field_ `static Dictionary< TurnkeyVariables = new Dictionary<string, string>()`
- L49-55 _public method_ `public static string SetVariable(string Key, string Value)`
- L56-64 _public method_ `public static string GetVariableValue(string Key)`
- L66-69 _public method_ `public static void ClearVariable(string Key)`
- L70-73 _public method_ `public static bool HasVariable(string Key)`
- L75-85 _public method_ `public static string ExpandVariables(string Str, bool bUseOnlyTurnkeyVariables = false)`
- L91-95 _public method_ `public static bool ParseParam(string Param, string[] ExtraOptions)`
- L97-107 _public method_ `public static string ParseParamValue(string Param, string Default, string[] ExtraOptions)`
- L109-117 _private method_ `private static List<UnrealTargetPlatform> GetAllValidPlatforms(List<UnrealTargetPlatform> SourcePlatforms=null)`
- L119-191 _public method_ `public static List<UnrealTargetPlatform> GetPlatformsFromCommandLineOrUser(string[] CommandOptions, List<UnrealTargetPlatform> PossiblePlatforms)`
- L205-386 _public method_ `public static FileReference GetProjectFromCommandLineOrUser(string[] CommandOptions)`
- L388-401 _private method_ `private static DeviceInfo GetDeviceByPlatformAndName(UnrealTargetPlatform Platform, string DeviceName)`
- L403-419 _private method_ `private static DeviceInfo[] GetDevicesForPlatform(UnrealTargetPlatform Platform)`
- L422-425 _public method_ `public static List<DeviceInfo> GetDevicesFromCommandLineOrUser(string[] CommandOptions, UnrealTargetPlatform Platform)`
- L431-582 _public method_ `public static List<DeviceInfo> GetDevicesFromCommandLineOrUser(string[] CommandOptions, List<UnrealTargetPlatform> PossiblePlatforms)`
- L584-609 _public method_ `public static void GetPlatformsAndDevicesFromCommandLineOrUser(string[] CommandOptions, bool bSkipAskUserForDevice, out List<UnrealTargetPlatform> Platforms, out List<DeviceInfo> Devices, List<UnrealTargetPlatform> AllowedPlatforms=null)`
- L611-614 _public method_ `public static string GetGenericOption(string[] CommandOptions, List<string> Options, string CommandLineOption)`
- L616-646 _public method_ `public static string GetGenericOption(string[] CommandOptions, List<string> Options, string CommandLineOption, out bool bWasOnCommandLine)`
- L652 _private field_ `private static Dictionary<string, string> SavedEnvVars`
- L652 _private field_ `private static Dictionary< SavedEnvVars`
- L653 _private field_ `private static Dictionary<string, string> EnvVarsToSaveToBatchFile = ...`
- L653 _private field_ `private static Dictionary< EnvVarsToSaveToBatchFile = new()`
- L655-697 _private method_ `private static Dictionary<string, string> GetCombinedEnvironmentVariables()`
- L699-702 _public method_ `public static void StartTrackingExternalEnvVarChanges()`
- L704-751 _public method_ `public static void EndTrackingExternalEnvVarChanges()`
- L757-765 _private* method_ `static bool TryConvertToUint64(string InValue, out UInt64 OutValue)`
- L767-825 _public method_ `public static bool IsValueValid(string Value, string AllowedValues, AutomationTool.Platform Platform)`
- L830 _private field_ `static private IOProvider IOProvider`
- L832-835 _public method_ `public static void Log(string Message)`
- L836-840 _public method_ `public static void Log(ref StringBuilder Message)`
- L841-844 _public method_ `public static void Log(string Message, params object[] Params)`
- L846-849 _public method_ `public static void Report(string Message)`
- L850-854 _public method_ `public static void Report(ref StringBuilder Message)`
- L855-858 _public method_ `public static void Report(string Message, params object[] Params)`
- L860-863 _public method_ `public static void PauseForUser(string Message, params object[] Params)`
- L865-868 _public method_ `public static string ReadInput(string Prompt, string Default = "")`
- L869-874 _public method_ `public static int ReadInputInt(ref StringBuilder Prompt, List<string> Options, bool bIsCancellable, int DefaultValue = -1)`
- L875-878 _public method_ `public static int ReadInputInt(string Prompt, List<string> Options, bool bIsCancellable, int DefaultValue = -1)`
- L880-883 _public method_ `public static bool GetUserConfirmation(string Message, bool bDefaultValue)`
- L887 _private* field_ `static List<string> PathsToCleanup = new List<string>()`
- L888-891 _public method_ `public static void AddPathToCleanup(string Path)`
- L893-911 _public method_ `public static void CleanupPaths()`

#### enum `Turnkey.TurnkeyUtils.ProjectMode`  
`private enum ProjectMode`  
_private; L193-203_
- L195 _public* enumerator_ `Normal`
- L196 _public* enumerator_ `Templates`
- L197 _public* enumerator_ `Sandbox`
- L198 _public* enumerator_ `Misc`
- L199 _public* enumerator_ `Samples`
- L200 _public* enumerator_ `Collaboration`
- L201 _public* enumerator_ `Personal`
- L202 _public* enumerator_ `Recent`
