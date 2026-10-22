# CSharp / AutomationScripts.Automation

- project root: `Source/Programs/AutomationTool/Scripts`
- files: 104; symbols: 1909
- symbol kinds: class=223, const=23, ctor=78, enum=14, enumerator=63, field=429, interface=2, method=717, operator=5, property=338, record=2, record struct=2, struct=13
- access marked `*` is implicit (not written in source)

### `Source/Programs/AutomationTool/Scripts/AddAutomatedPerfTestToProject.cs` (AutomationScripts.Automation)


#### class `AddAutomatedPerfTestToProject`  
`class AddAutomatedPerfTestToProject : BuildCommand`  
_internal*; L21-284_
- attrs: `[Help("UAT command to enable PerfTesting hook ups for a project.")] [Help("-Project", "Path to the project to be instrumented.")] [Help("-Overwrite", "If set, will overwrite any template files that already exist.")]`
- inherits: `BuildCommand`
- L26 _private* const_ `const string AptPluginName = "AutomatedPerfTesting"` — The plugin name itself
- L31 _private* const_ `const string AptPathFromRoot = "Engine/Plugins/Performance/AutomatedPerfTesting"` — Path to the AutomatePerfTesting plugin
- L36 _private* const_ `const string AptTemplatesFromPluginRoot = "Resources/TemplatesForHookup"` — Path to the AutomatePerfTesting templates
- L41 _private* const_ `const string AptGauntletIncludeFile = "GauntletSettings.xml"` — Name of the Gauntlet settings that needs to be copied verbatim
- L46 _private* const_ `const string AptProjectBuildGraphTemplateFile = "AutoPerfTests.xml"` — Name of the template file with project setings that will be modified
- L51 _private* const_ `const string AptLocalTestBatchFile = "RunLocalTests.bat"` — Name of the template file for running tests locally on Windows
- L56 _private* const_ `const string AptLocalTestShellFile = "RunLocalTests.sh"` — Name of the template file for running tests locally on Mac/Linux
- L61 _private* const_ `const string EngineBatchFilesFromRoot = "Engine/Build/BatchFiles"` — Path to the engine's build/batchfiles directory relative to the engine root
- L66 _private* const_ `const string AptConfigSectionName = "/Script/AutomatedPerfTesting.AutomatedSequencePerfTestProjectSettings"` — Name of the config section for APT
- L68-109 _protected method_ `protected bool EnablePlugin(string ProjectFilePath)`
- L111-144 _protected method_ `protected bool ModifyProjectConfigFiles(string ProjectFilePath)`
- L149-152 _protected method_ `protected string GetProjectName(string ProjectFilePath)` — Return a project name from the path to .uproject
- L157-163 _protected method_ `protected string GetProjectRelativePath(string ProjectFilePath)` — Return a project path relative to the current engine root, with forward slashes.
- L168-174 _protected method_ `protected string GetRunUATRelativePath(string InFilePath)` — Return the path to RunUAT relative to the input file
- L176-225 _protected method_ `protected bool ModifyBuildGraphFiles(string ProjectFilePath, bool Overwrite=false)`
- L227-260 _protected method_ `protected bool ModifyLocalTestsBatchFile(string ProjectFilePath, bool Overwrite=false)`
- L262-283 _public method_ `public override void ExecuteBuild()`

### `Source/Programs/AutomationTool/Scripts/AnalyzeThirdPartyLibs.Automation.cs` (AutomationScripts.Automation)


#### class `PlatformLibraryInfo`  
`class PlatformLibraryInfo`  
_internal*; L19-50_
- L21 _public field_ `public List<string> PathParticles = new List<string>()`
- L22 _public field_ `public List<string> Manifest = new List<string>()`
- L23 _public field_ `public long TotalSize = 0`
- L24 _public field_ `public string PlatformName`
- L26-37 _public method_ `public bool PartOfPlatform(string Filename)`
- L39-43 _public ctor_ `public PlatformLibraryInfo(string PlatformName, params string[] Values)`
- L45-49 _public method_ `public void AddFile(string Filename, long Size)`

#### class `ThirdPartyLibraryInfo`  
`class ThirdPartyLibraryInfo`  
_internal*; L53-112_
- L55 _public field_ `public List<string> Manifest = new List<string>()`
- L57-78 _public method_ `public long GetSize(List<PlatformLibraryInfo> Platforms)`
- L80-105 _public method_ `public void FindLargeFiles(List<string> AllowedExtensions, long MinSize)`
- L107-111 _public ctor_ `public ThirdPartyLibraryInfo(string Root)`

#### class `AnalyzeThirdPartyLibs`  
`class AnalyzeThirdPartyLibs : BuildCommand`  
_internal*; L117-236_
- attrs: `[Help("Analyzes third party libraries")] [Help("Libs", "[Optional] + separated list of libraries to compile; if not specified this job will build all libraries it can find builder scripts for")] [Help("Changelist", "[Optional] a changelist to check out into; if not specified, a changelist will be created")]`
- inherits: `BuildCommand`
- L120 _private field_ `static private string LibDir = "Engine/Source/ThirdParty"`
- L123-129 _public method_ `public static string ToMegabytes(long Size)`
- L131-235 _public method_ `public override void ExecuteBuild()`

### `Source/Programs/AutomationTool/Scripts/ArchiveCommand.Automation.cs` (AutomationScripts.Automation)


#### class `AutomationScripts.Project`  
`public partial class Project : CommandUtils`  
_public; L14-91_
- inherits: `CommandUtils`
- L16-38 _public method_ `public static void CreateArchiveManifest(ProjectParams Params, DeploymentContext SC)`
- L40-51 _public method_ `public static void ApplyArchiveManifest(ProjectParams Params, DeploymentContext SC)`
- L53-90 _public method_ `public static void Archive(ProjectParams Params)`

### `Source/Programs/AutomationTool/Scripts/AssemblyInfo.InternalsVisibleTo.cs` (AutomationScripts.Automation)
_(no declarations)_


### `Source/Programs/AutomationTool/Scripts/BenchmarkBuild/BenchmarkBuild.Automation.cs` (AutomationScripts.Automation)


#### class `AutomationTool.Benchmark.BenchmarkBuild`  
`class BenchmarkBuild : BuildCommand`  
_internal*; L61-829_
- attrs: `[Help("Runs benchmarks and reports overall results")] [Help("Example1: RunUAT BenchmarkBuild -all -project=Unreal")] [Help("Example2: RunUAT BenchmarkBuild -allcompile -project=Unreal+EngineTest -platform=PS4")] [Help("Example3: RunUAT BenchmarkBuild -editor -client -cook -cooknoshaderddc -cooknoddc -xge -noxge -singlecompile -nopcompile -project=Unreal+QAGame+EngineTest -platform=WIn64+PS4+XboxOn`
- inherits: `BuildCommand`
- L401-403 _public ctor_ `public BenchmarkBuild()`
- L405-608 _public method_ `public override ExitCode Execute()`
- L610-671 _private* method_ `IEnumerable<BenchmarkTaskBase> AddBuildTests(FileReference InProjectFile, UnrealTargetPlatform InPlatform, string InTargetName, BenchmarkOptions InOptions)`
- L674-726 _private* method_ `IEnumerable<BenchmarkTaskBase> AddEditorTests<T>(ProjectTargetInfo InTargetInfo, IEnumerable<string> InMaps, IEnumerable<string> InArgVariations, IEnumerable<int> CoreVariations, IEnumerable<XGETaskOptions> InXGEOptions, IEnumerable<DDCTaskOptions> InDDCOptions, bool SkipBuildEditor) where T : BenchmarkEditorTaskBase`
- L732-810 _private* method_ `void WriteCSVResults(string InFileName, IEnumerable<BenchmarkTaskBase> InTasks, Dictionary<BenchmarkTaskBase, List<BenchmarkResult>> InResults)` — Writes our current result to a CSV file. It's expected that this function is called multiple times so results are updated as we go
- L817-828 _private* method_ `bool ProjectSupportsClientBuild(FileReference InProjectFile)` — Returns true/false based on whether the project supports a client configuration

#### class `AutomationTool.Benchmark.BenchmarkBuild.BenchmarkOptions`  
`class BenchmarkOptions : BuildCommand`  
_private*; L63-393_
- inherits: `BuildCommand`
- L65 _public field_ `public bool Preview = false`
- L67 _public field_ `public bool DoUETests = false`
- L68 _public field_ `public IEnumerable<string> ProjectsToTest = Enumerable.Empty<string>()`
- L69 _public field_ `public IEnumerable<UnrealTargetPlatform> PlatformsToTest = Enumerable.Empty<UnrealTargetPlatform>()`
- L72 _public field_ `public bool DoBuildEditorTests = false`
- L73 _public field_ `public bool DoBuildClientTests = false`
- L74 _public field_ `public bool DoCompileTests = false`
- L75 _public field_ `public bool DoNoCompileTests = false`
- L76 _public field_ `public bool DoSingleCompileTests = false`
- L78 _public field_ `public IEnumerable<int> CoresForLocalJobs = Enumerable.Empty<int>()`
- L81 _public field_ `public bool DoCookTests = false`
- L82 _public field_ `public bool DoIterativeCookTests = false`
- L85 _public field_ `public bool DoPIETests = false`
- L88 _public field_ `public bool DoLaunchEditorTests = false`
- L89 _public field_ `public bool DoLaunchEditorGameTests = false`
- L91 _public field_ `public IEnumerable<string> StartupMapList = Enumerable.Empty<string>()`
- L92 _public field_ `public IEnumerable<string> PIEMapList = Enumerable.Empty<string>()`
- L93 _public field_ `public IEnumerable<string> GameMapList = Enumerable.Empty<string>()`
- L94 _public field_ `public IEnumerable<string> CookMapList = Enumerable.Empty<string>()`
- L97 _public field_ `public int Iterations = 1`
- L98 _public field_ `public UBTBuildOptions BuildOptions = UBTBuildOptions.None`
- L99 _public field_ `public int TimeBetweenTasks = 0`
- L101 _public field_ `public List<string> UBTArgs = new List<string>()`
- L102 _public field_ `public List<string> CookArgs = new List<string>()`
- L103 _public field_ `public List<string> PIEArgs = new List<string>()`
- L104 _public field_ `public List<string> LaunchArgs = new List<string>()`
- L105 _public field_ `public string FileName = string.Format("{0}_Results.csv", Unreal.MachineName)`
- L108 _public field_ `public SortedSet<XGETaskOptions> XGEOptions = new SortedSet<XGETaskOptions>()`
- L110 _public field_ `public SortedSet<DDCTaskOptions> DDCOptions = new SortedSet<DDCTaskOptions>()`
- L113-392 _public method_ `public void ParseParams(string[] InParams)`

#### struct `AutomationTool.Benchmark.BenchmarkBuild.BenchmarkResult`  
`struct BenchmarkResult`  
_private*; L395-399_
- L397 _public property_ `public TimeSpan TaskTime { get; set; }`
- L398 _public property_ `public bool Failed { get; set; }`

### `Source/Programs/AutomationTool/Scripts/BenchmarkBuild/BenchmarkCookTask.cs` (AutomationScripts.Automation)


#### class `AutomationTool.Benchmark.BenchmarkCookTask`  
`class BenchmarkCookTask : BenchmarkEditorTaskBase`  
_internal*; L17-76_
- inherits: `BenchmarkEditorTaskBase`
- L19 _protected field_ `protected string CookPlatformName`
- L21 _private* field_ `string CookArgs`
- L23 _private* field_ `bool CookAsClient`
- L24-30 _public property_ `public override string TaskName { get; }`
- L31-50 _public ctor_ `public BenchmarkCookTask(ProjectTargetInfo InTargetInfo, ProjectTaskOptions InOptions, bool InSkipBuild) : base(InTargetInfo, InOptions, InSkipBuild)`
- L52-67 _protected method_ `protected override string GetEditorTaskArgs()`
- L69-75 _protected method_ `protected override bool PerformTask()`

#### class `AutomationTool.Benchmark.BenchmarkIterativeCookTask`  
`class BenchmarkIterativeCookTask : BenchmarkCookTask`  
_internal*; L81-142_
- inherits: `BenchmarkCookTask`
- desc: Iterative cooking test
- L83-86 _public ctor_ `public BenchmarkIterativeCookTask(ProjectTargetInfo InTargetInfo, ProjectTaskOptions InOptions, bool InSkipBuild) : base(InTargetInfo, InOptions, InSkipBuild)`
- L88-94 _public property_ `public override string TaskName { get; }`
- L96-132 _protected method_ `protected override bool PerformPrequisites()`
- L134-141 _protected method_ `protected override string GetEditorTaskArgs()`

### `Source/Programs/AutomationTool/Scripts/BenchmarkBuild/BenchmarkEditorGameTask.cs` (AutomationScripts.Automation)


#### class `AutomationTool.Benchmark.BenchmarkEditorGameTask`  
`class BenchmarkEditorGameTask : BenchmarkEditorStartupTask`  
_internal*; L10-29_
- inherits: `BenchmarkEditorStartupTask`
- L12-15 _public ctor_ `public BenchmarkEditorGameTask(ProjectTargetInfo InTargetInfo, ProjectTaskOptions InOptions, bool InSkipBuild) : base(InTargetInfo, InOptions, InSkipBuild)`
- L17-23 _public property_ `public override string TaskName { get; }`
- L25-28 _protected method_ `protected override string GetEditorTaskArgs()`

### `Source/Programs/AutomationTool/Scripts/BenchmarkBuild/BenchmarkEditorStartupTask.cs` (AutomationScripts.Automation)


#### class `AutomationTool.Benchmark.BenchmarkEditorStartupTask`  
`class BenchmarkEditorStartupTask : BenchmarkEditorTaskBase`  
_internal*; L15-33_
- inherits: `BenchmarkEditorTaskBase`
- L17-20 _public ctor_ `public BenchmarkEditorStartupTask(ProjectTargetInfo InTargetInfo, ProjectTaskOptions InOptions, bool InSkipBuild) : base(InTargetInfo, InOptions, InSkipBuild)`
- L21-27 _public property_ `public override string TaskName { get; }`
- L29-32 _protected method_ `protected override string GetEditorTaskArgs()`

### `Source/Programs/AutomationTool/Scripts/BenchmarkBuild/BenchmarkEditorTaskBase.cs` (AutomationScripts.Automation)


#### class `AutomationTool.Benchmark.ProjectTaskOptions`  
`class ProjectTaskOptions`  
_internal*; L21-42_
- desc: Options when running a task
- L23 _public property_ `public DDCTaskOptions DDCOptions { get; set; }`
- L25 _public property_ `public XGETaskOptions XGEOptions { get; set; }`
- L27 _public property_ `public string Map { get; set; }`
- L29 _public property_ `public int CoreLimit { get; set; }`
- L31 _public property_ `public string Args { get; set; }`
- L34-41 _public ctor_ `public ProjectTaskOptions(DDCTaskOptions InDDCOptions, XGETaskOptions InXGEOptions, string InArgs, string InMap = "", int InCoreLimit = 0)`

#### class `AutomationTool.Benchmark.BenchmarkEditorTaskBase`  
`abstract class BenchmarkEditorTaskBase : BenchmarkTaskBase`  
_internal*; L47-362_
- inherits: `BenchmarkTaskBase`
- desc: Abstract classs for running editor-based tasks for benchmarking
- L49 _protected field_ `protected ProjectTargetInfo ProjectTarget = null`
- L51 _protected field_ `protected ProjectTaskOptions TaskOptions = null`
- L53 _protected field_ `protected bool SkipBuild = false`
- L55-61 _protected method_ `protected static string MakeValidTaskFileName(string name)`
- L63-124 _protected ctor_ `protected BenchmarkEditorTaskBase(ProjectTargetInfo InTargetInfo, ProjectTaskOptions InOptions, bool InSkipBuild) : base(InTargetInfo.ProjectFile)`
- L126-129 _protected method_ `protected string GetEditorPath()`
- L131-159 _protected method_ `protected string GetBasicEditorCommandLine(bool bIsWarming)`
- L161-164 _protected method_ `protected virtual string GetEditorTaskArgs()`
- L166 _private field_ `private Dictionary<string, string> StoredEnvVars = ...`
- L166 _private field_ `private Dictionary< StoredEnvVars = new Dictionary<string, string>()`
- L167 _private field_ `private List<DirectoryReference> CachePaths = new List<DirectoryReference>()`
- L169-178 _private method_ `private string GetXPlatformEnvironmentKey(string InKey)`
- L180 _private* field_ `static IProcessResult CurrentProcess = null`
- L181 _private* field_ `static DateTime LastStdOutTime = DateTime.Now`
- L189-205 _private* method_ `static string EndOnMapCheckFilter(string Message)` — A filter that suppresses all output od stdout/stderr
- L207-242 _protected method_ `protected bool RunEditorAndWaitForMapLoad(bool bIsWarming)`
- L244-247 _protected method_ `protected override bool PerformTask()`
- L249 _private* field_ `static HashSet<string> BuiltEditors = new HashSet<string>()`
- L251-344 _protected method_ `protected override bool PerformPrequisites()`
- L346-361 _protected method_ `protected override void PerformCleanup()`

### `Source/Programs/AutomationTool/Scripts/BenchmarkBuild/BenchmarkNopCompileTask.cs` (AutomationScripts.Automation)


#### class `AutomationTool.Benchmark.BenchmarkNopCompileTask`  
`class BenchmarkNopCompileTask : BenchmarkBuildTask`  
_internal*; L15-33_
- inherits: `BenchmarkBuildTask`
- L19 _private field_ `private string _TaskName`
- L20-26 _public property_ `public override string TaskName { get; }`
- L28-32 _public ctor_ `public BenchmarkNopCompileTask(FileReference InProjectFile, string InTarget, UnrealTargetPlatform InPlatform, XGETaskOptions InXGEOptions) : base(InProjectFile, InTarget, InPlatform, InXGEOptions, "", 0)`

### `Source/Programs/AutomationTool/Scripts/BenchmarkBuild/BenchmarkSingleCompileTask.cs` (AutomationScripts.Automation)


#### class `AutomationTool.Benchmark.BenchmarkSingleCompileTask`  
`class BenchmarkSingleCompileTask : BenchmarkBuildTask`  
_internal*; L17-89_
- inherits: `BenchmarkBuildTask`
- L19 _private* field_ `FileReference SourceFile = null`
- L21 _private field_ `private string _TaskName`
- L22-28 _public property_ `public override string TaskName { get; }`
- L29-62 _public ctor_ `public BenchmarkSingleCompileTask(FileReference InProjectFile, string InTarget, UnrealTargetPlatform InPlatform, XGETaskOptions InXgeOption) : base(InProjectFile, InTarget, InPlatform, InXgeOption, "", 0)`
- L64-88 _protected method_ `protected override bool PerformPrequisites()`

### `Source/Programs/AutomationTool/Scripts/BenchmarkBuild/BenchmarkTaskBase.cs` (AutomationScripts.Automation)


#### enum `AutomationTool.Benchmark.UBTBuildOptions`  
`public enum UBTBuildOptions`  
_public; L17-23_
- attrs: `[Flags]`
- L19 _public* enumerator_ `None = 0`
- L20 _public* enumerator_ `PreClean = 1 << 0`
- L21 _public* enumerator_ `PostClean = 1 << 1`
- L22 _public* enumerator_ `CleanOnly = 1 << 2`

#### enum `AutomationTool.Benchmark.DDCTaskOptions`  
`public enum DDCTaskOptions`  
_public; L26-35_
- attrs: `[Flags]`
- L28 _public* enumerator_ `None = 0`
- L29 _public* enumerator_ `WarmDDC = 1 << 0`
- L30 _public* enumerator_ `ColdDDCNoShared = 1 << 1`
- L31 _public* enumerator_ `ColdDDC = 1 << 2`
- L32 _public* enumerator_ `NoShaderDDC = 1 << 3`
- L33 _public* enumerator_ `HotDDC = 1 << 4`
- L34 _public* enumerator_ `KeepMemoryDDC = 1 << 6`

#### enum `AutomationTool.Benchmark.XGETaskOptions`  
`public enum XGETaskOptions`  
_public; L38-45_
- attrs: `[Flags]`
- L40 _public* enumerator_ `None = 0`
- L41 _public* enumerator_ `NoXGE = 1 << 1`
- L42 _public* enumerator_ `WithXGE = 1 << 2`
- L43 _public* enumerator_ `NoEditorXGE = 1 << 3`
- L44 _public* enumerator_ `WithEditorXGE = 1 << 4`

#### class `AutomationTool.Benchmark.ProjectTargetInfo`  
`class ProjectTargetInfo`  
_internal*; L50-64_
- desc: Simple class that describes a target in a project
- L52 _public property_ `public FileReference ProjectFile { get; set; }`
- L54 _public property_ `public UnrealTargetPlatform TargetPlatform { get; set; }`
- L56 _public property_ `public bool BuildTargetAsClient { get; set; }`
- L58-63 _public ctor_ `public ProjectTargetInfo(FileReference InFileReference, UnrealTargetPlatform InTargetPlatform, bool InBuildTargetAsClient)`

#### class `AutomationTool.Benchmark.BenchmarkTaskBase`  
`abstract class BenchmarkTaskBase`  
_internal*; L69-265_
- desc: Base class for running tasks
- L74 _protected property_ `protected static ILogger Logger => ...` — Default logger instance
- L79 _public property_ `public bool Failed { get; set; }` — True or false based on whether the task failed
- L84 _public property_ `public string FailureString { get; set; }` — Failure message
- L89 _public property_ `public bool SkipReport { get; set; }` — Don't report this test
- L94 _public property_ `public TimeSpan TaskTime { get; set; }` — Time the task took (does not include prequisites)
- L99 _public property_ `public DateTime StartTime { get; set; }` — Time the task started
- L104 _protected method_ `virtual protected bool PerformPrequisites()` — Perform any prerequisites the task requires
- L109 _protected method_ `virtual protected void PerformCleanup()` — Perform post-task cleanup
- L114 _protected method_ `protected abstract bool PerformTask()` — Perform the actual task that is measured
- L119 _public property_ `public FileReference ProjectFile { get; set; }` — Path to the project file we're using. May be null for Unreal editor, client etc
- L126 _public property_ `public string ProjectName { get; }` — Return the name of the module this is being performed on
- L132 _public property_ `public abstract string TaskName { get; }` — Return the name of this task
- L134 _private field_ `private readonly List<string> InternalModifiers = new List<string>()`
- L139 _protected property_ `protected List<string> TaskModifiers { get; }` — A list of modifiers that can be considered when
- L145-158 _public property_ `public string ModifierString { get; }` — Return the full name of this task for reporting
- L164-177 _public property_ `public string TaskNameWithModifiers { get; }` — Returns a full name to use in reporting and logging
- L185 _public property_ `public string FullName { get; }` — Return the full name of this task for reporting
- L191-194 _public ctor_ `public BenchmarkTaskBase(FileReference InProjectFile)` — Simple constructor
- L199-244 _public method_ `public void Run()` — Run the task. Performs any prerequisites, then the actual task itself
- L249-259 _public method_ `public void Report()` — Report how long the task took
- L261-264 _public method_ `public override string ToString()`

### `Source/Programs/AutomationTool/Scripts/BenchmarkBuild/BernchmarkEditorPIETask.cs` (AutomationScripts.Automation)


#### class `AutomationTool.Benchmark.BenchmarPIEEditorTask`  
`class BenchmarPIEEditorTask : BenchmarkEditorStartupTask`  
_internal*; L10-28_
- inherits: `BenchmarkEditorStartupTask`
- L12-15 _public ctor_ `public BenchmarPIEEditorTask(ProjectTargetInfo InTargetInfo, ProjectTaskOptions InOptions, bool InSkipBuild) : base(InTargetInfo, InOptions, InSkipBuild)`
- L16-22 _public property_ `public override string TaskName { get; }`
- L24-27 _protected method_ `protected override string GetEditorTaskArgs()`

### `Source/Programs/AutomationTool/Scripts/Bisect.Automation.cs` (AutomationScripts.Automation)


#### class `AutomationTool.Bisect`  
`class Bisect : BuildCommand`  
_internal*; L21-529_
- attrs: `[Help("Bisects a range of changelists between 'good' and 'bad' (exclusive). If a failed-build is reported, then bisection expands outwards from the active changelist until bisection resumed.")] [Help("TargetStream=<Stream>", "Stream path. (Required)")] [Help("RootPath=<Stream>", "Local root path (if not specified current client root path will be used (not recommended as some files used by the scri`
- inherits: `BuildCommand`
- L155 _private field_ `private static readonly List<string> RequiredDirsToSync = new List<string>{ "Engine" }`
- L156 _private field_ `private static readonly List<string> DirsToExcludeFromSync = new List<string> { "Engine/Binaries/ThirdParty/DotNet", "Engine/Source/Programs/AutomationTool" }`
- L161 _private property_ `private string TargetStream { get; set; }`
- L162 _private property_ `private string RootPath { get; set; }`
- L163 _private property_ `private string Project { get; set; }`
- L164 _private property_ `private int GoodCL { get; set; }`
- L165 _private property_ `private int BadCL { get; set; }`
- L166 _private property_ `private string TestsToCheck { get; set; }`
- L168-178 _private method_ `private List<string> GetRequiredDirsToSync()`
- L180-196 _private method_ `private List<KeyValuePair<string, string>> GetExclusionViewParts()`
- L198-238 _private method_ `private void GetEntriesToSync(P4Connection Perforce, int CL, ProjectFileInfo ProjectFileInfo, out List<string> Dirs, out List<string> Files)`
- L240-279 _private method_ `private ProjectFileInfo GetProjectFileInfo(P4Connection Perforce)`
- L280-309 _private method_ `private bool RunExecutableInRootEnvironment(string ExecutablePath, string CommandLineArgs)`
- L311-343 _private method_ `private bool BuildProject(ProjectFileInfo ProjectFileInfo)`
- L345-356 _private method_ `private bool RunTests()`
- L358-399 _private method_ `private void ParseCommandLineArgs()`
- L404-528 _public method_ `public override void ExecuteBuild()` — Executes the command

#### class `AutomationTool.Bisect.Bisectomatron`  
`private class Bisectomatron`  
_private; L30-117_
- desc: The class is a helper class for bisection method. It stores a range of changelist indexes (between 'good' and 'bad' (exclusive)) to support bisection of the current range by calling Bad and Good methods. The class also supports Ugly method to label current changelist index with 'failed to build' mark.
- L32 _public property_ `public int GoodIndex { get; set; }`
- L33 _public property_ `public int BadIndex { get; set; }`
- L34 _public property_ `public int Index { get; set; }`
- L35 _private field_ `private int Jump`
- L36 _private field_ `private HashSet<int> UglyIndexes`
- L42-49 _public ctor_ `public Bisectomatron(int Length)` — The class constructor
- L55-58 _public operator_ `public static implicit operator bool(Bisectomatron BisectomatronInstance)` — The method is designed to check whether the object of the class is still valid to proceed bisection.
- L63-70 _private method_ `private void Bisect()` — The method performs bisection of the current indexes range with taking into account indexes of changelists that were not built correctly.
- L75-81 _public method_ `public void Good()` — The method handles current index as 'good' (build and test runs for the corresponding changelist were completed successfully) and proceed bisection if possible.
- L86-92 _public method_ `public void Bad()` — The method handles current index as 'bad' (test run for the corresponding changelist was completed with error) and proceed bisection if possible.
- L101-116 _public method_ `public void Ugly()` — The method handles current index as 'ugly' (build of corresponding changelist was completed with error) and tries to determine the closest neighboring index that has not been checked yet. While searching for the closest neighboring index that has not been checked yet the method goes in two directions. It is performed by alternating the closest left hand side and right hand side neighbors that have not been handled yet.

#### class `AutomationTool.Bisect.ProjectFileInfo`  
`private class ProjectFileInfo`  
_private; L122-153_
- desc: The class is a storage class for the project file information.
- L124 _public property_ `public string DepotPath { get; set; }`
- L125 _public property_ `public string FilePath { get; set; }`
- L131-136 _public method_ `public bool IsValid()` — Checks if the stored data is valid.
- L142-152 _public method_ `public string GetDepotDirPath()` — The method returns depot path for the corresponding project file.

### `Source/Programs/AutomationTool/Scripts/BuildAcquire.Automation.cs` (AutomationScripts.Automation)


#### class `BuildInfo`  
`class BuildInfo`  
_internal*; L23-27_
- L25 _public field_ `public string BuildVariant = null`
- L26 _public field_ `public string Platform = null`

#### class `EnumExtensions`  
`public static class EnumExtensions`  
_public; L29-72_
- L31-52 _public method_ `public static EnumDescription ConvertEnumWithDescription<T>() where T : struct, IConvertible`
- L54-65 _public method_ `public static string GetEnumDescription(Enum value)`
- L67-71 _public method_ `public static string GetEnumNameOrDescription(Enum value)`

#### class `EnumDescription`  
`public class EnumDescription`  
_public; L74-79_
- L76 _public property_ `public string Type { get; set; }`
- L77 _public property_ `public IDictionary<int, string> ValueDescriptions { get; set; }`
- L78 _public property_ `public IList<string> Descriptions { get; set; }`

#### class `BuildAcquire`  
`class BuildAcquire : BuildCommand, IProjectParamsHelpers`  
_internal*; L81-560_
- inherits: `BuildCommand, IProjectParamsHelpers`
- L106-111 _public ctor_ `public BuildAcquire()`
- L113-146 _public method_ `public override void ExecuteBuild()`
- L148-223 _private method_ `private void Initialize()`
- L225-232 _private method_ `private List<FindBuildResponse> FilterBuilds(in List<FindBuildResponse> foundBuilds, string CookPlatform)`
- L234-369 _private method_ `private void DownloadBuilds(ProjectParams Params)`
- L382-412 _private method_ `private List<string> GetCookPlatforms(ProjectParams Params)`
- L414-461 _private method_ `private void ImportSnapshot(ProjectParams Params)`
- L463-497 _private method_ `private bool IsEditorRunning(ProjectParams Params)`
- L499 _private field_ `private ICloudStorage CloudStorageService`
- L502 _private* field_ `BuildTypeEnum? _BuildType`
- L503-537 _private property_ `private BuildTypeEnum? BuildType { get; }`
- L539 _private* field_ `string Stream`
- L540 _private* field_ `string Changelist`
- L541 _private* field_ `string Buildgroup = null`
- L542 _private* field_ `bool IsPreflight = false`
- L543 _private* field_ `FileReference ProjectPath`
- L544 _private* field_ `string BuildPlatform`
- L545 _private* field_ `bool DownloadServer`
- L546 _private* field_ `bool DownloadClient`
- L547 _private* field_ `bool DownloadGame`
- L548 _private* field_ `bool DownloadSnapshot`
- L549 _private* field_ `bool ClosestSnapshot`
- L550 _private* field_ `bool SkipContentInStaged`
- L552 _private* field_ `bool SyncUGS`
- L553 _private* field_ `bool DownloadBuild`
- L554 _private* field_ `bool DryRun`
- L556 _private* field_ `FileReference UGSExePath`
- L557 _private* field_ `FileReference ZenExePath`
- L559 _private* field_ `BuildVariant BuildConfigType`

#### enum `BuildAcquire.BuildVariant`  
`public enum BuildVariant`  
_public; L83-93_
- L86 _public* enumerator_ `Development` — attrs: `[Description("Development")]`
- L88 _public* enumerator_ `Debug` — attrs: `[Description("Debug")]`
- L90 _public* enumerator_ `Test` — attrs: `[Description("Test")]`
- L92 _public* enumerator_ `Shipping` — attrs: `[Description("Shipping")]`

#### enum `BuildAcquire.BuildTypeEnum`  
`public enum BuildTypeEnum`  
_public; L95-104_
- L98 _public* enumerator_ `Staged` — attrs: `[Description("staged-build")]`
- L100 _public* enumerator_ `Packaged` — attrs: `[Description("packaged-build")]`
- L102 _public* enumerator_ `Snapshot` — attrs: `[Description("oplog")]`
- L103 _public* enumerator_ `Unspecified`

#### struct `BuildAcquire.CloudStorageConfig`  
`private struct CloudStorageConfig`  
_private; L371-380_
- L373 _public field_ `public string Host = ""`
- L374 _public field_ `public string BuildsNamespace = ""`
- L375 _public field_ `public string OAuthProviderIdentifier = ""`
- L377-379 _public ctor_ `public CloudStorageConfig()`

### `Source/Programs/AutomationTool/Scripts/BuildCMakeLib.Automation.cs` (AutomationScripts.Automation)


#### class `BuildCMakeLib`  
`public sealed class BuildCMakeLib : BuildCommand`  
_public; L38-773_
- attrs: `[Help("Builds a third party library using the CMake build system.")] [Help("TargetLibRoot", "Override the path to the library's root dir.")] [Help("TargetLib", "Specify the target library to build.")] [Help("TargetLibVersion", "Specify the target library version to build.")] [Help("TargetLibSourcePath", "Override the path to source, if external to the engine. (eg. -TargetLibSourcePath=path). Defau`
- inherits: `BuildCommand`
- L81-92 _public method_ `public static void MakeFreshDirectoryIfRequired(DirectoryReference Directory)`
- L488-508 _private method_ `private TargetLib GetTargetLib()`
- L510-524 _public method_ `public List<string> GetTargetConfigurations()`
- L526-602 _private method_ `private TargetPlatform GetTargetPlatform()`
- L604-624 _private method_ `private static string RemoveOtherMakeAndCygwinFromPath(string WindowsPath)`
- L626-643 _private method_ `private void SetupBuildEnvironment()`
- L645-772 _public method_ `public override void ExecuteBuild()`

#### class `BuildCMakeLib.TargetLib`  
`public class TargetLib`  
_public; L40-79_
- L42 _public field_ `public string Name = ""`
- L43 _public field_ `public string Version = ""`
- L44 _public field_ `public string RootDir = ""`
- L45 _public field_ `public string SourcePath = ""`
- L46 _public field_ `public string BinOutputPath = ""`
- L47 _public field_ `public string LibOutputPath = ""`
- L48 _public field_ `public string CMakeProjectIncludeFile = ""`
- L49 _public field_ `public string CMakeAdditionalArguments = ""`
- L50 _public field_ `public string MakeTarget = ""`
- L52 _public property_ `public virtual Dictionary<string, string> BuildMap => ...`
- L58 _public property_ `public virtual Dictionary<string, string> BuildSuffix => ...`
- L64 _public field_ `public static DirectoryReference ThirdPartySourceDirectory = DirectoryReference.Combine(Unreal.RootDirectory, "Engine", "Source", "ThirdParty")`
- L66-76 _public method_ `public DirectoryReference GetLibSourceDirectory()`
- L78 _public method_ `public override string ToString()`

#### class `BuildCMakeLib.TargetPlatform`  
`public abstract class TargetPlatform : CommandUtils`  
_public; L94-419_
- inherits: `CommandUtils`
- L96 _public field_ `public static DirectoryReference CMakeRootDirectory = DirectoryReference.Combine(Unreal.RootDirectory, "Engine", "Extras", "ThirdPartyNotUE", "CMake")`
- L97 _public field_ `public static DirectoryReference MakeRootDirectory = DirectoryReference.Combine(Unreal.RootDirectory, "Engine", "Extras", "ThirdPartyNotUE", "GNU_Make", "make-3.81")`
- L99 _private property_ `private DirectoryReference PlatformEngineRoot => ...`
- L103-110 _private method_ `private DirectoryReference GetTargetLibRootDirectory(TargetLib TargetLib)`
- L112-119 _private method_ `private DirectoryReference GetTargetLibBaseRootDirectory(TargetLib TargetLib)`
- L121-132 _private method_ `private DirectoryReference GetTargetLibBuildScriptDirectory(TargetLib TargetLib)`
- L134-145 _private method_ `private DirectoryReference GetTargetLibBaseBuildScriptDirectory(TargetLib TargetLib)`
- L147-178 _protected method_ `protected DirectoryReference GetTargetLibPlatformCMakeDirectory(TargetLib TargetLib)`
- L180 _protected method_ `protected DirectoryReference GetProjectsDirectory(TargetLib TargetLib, string TargetConfiguration)`
- L186-208 _protected method_ `protected FileReference GetToolchainPath(TargetLib TargetLib, string TargetConfiguration)`
- L210-213 _protected method_ `protected FileReference GetProjectIncludePath(TargetLib TargetLib, string TargetConfiguration)`
- L215-218 _protected method_ `protected DirectoryReference GetOutputLibraryDirectory(TargetLib TargetLib, string TargetConfiguration)`
- L220-223 _protected method_ `protected DirectoryReference GetOutputBinaryDirectory(TargetLib TargetLib, string TargetConfiguration)`
- L225 _public property_ `public abstract string PlatformOrGroupName { get; }`
- L227 _public property_ `public virtual bool HasBinaries => ...`
- L228 _public property_ `public virtual bool UseResponseFiles => ...`
- L229 _public property_ `public virtual string TargetBuildPlatform => ...`
- L231 _public property_ `public virtual string DebugDatabaseExtension => ...`
- L232 _public property_ `public virtual string DynamicLibraryExtension => ...`
- L233 _public property_ `public virtual string StaticLibraryExtension => ...`
- L234 _public property_ `public virtual string SymbolExtension => ...`
- L236 _public property_ `public abstract bool IsPlatformExtension { get; }`
- L237 _public property_ `public abstract bool SeparateProjectPerConfig { get; }`
- L238 _public property_ `public abstract string CMakeGeneratorName { get; }`
- L240 _public property_ `public virtual string VariantDirectory => ...`
- L242-245 _public property_ `public virtual string FriendlyName { get; }`
- L247 _public property_ `public virtual string CMakeCommand => ...`
- L254 _public property_ `public virtual string MakeCommand => ...`
- L256 _public method_ `public virtual string GetToolchainName(TargetLib TargetLib, string TargetConfiguration)`
- L258-302 _public method_ `public virtual string GetCMakeSetupArguments(TargetLib TargetLib, string TargetConfiguration)`
- L305 _protected method_ `protected virtual Dictionary<string, string> GetCMakeEnvironment()`
- L307-327 _public method_ `public virtual string GetCMakeBuildArguments(TargetLib TargetLib, string TargetConfiguration)`
- L329-344 _public method_ `public virtual IEnumerable<FileReference> EnumerateOutputFiles(DirectoryReference BaseDir, string SearchPrefix, TargetLib TargetLib)`
- L346-381 _public method_ `public virtual IEnumerable<FileReference> EnumerateOutputFiles(TargetLib TargetLib, string TargetConfiguration)`
- L383-397 _public method_ `public virtual void SetupTargetLib(TargetLib TargetLib, string TargetConfiguration)`
- L399-405 _public method_ `public virtual void BuildTargetLib(TargetLib TargetLib, string TargetConfiguration)`
- L407-418 _public method_ `public virtual void CleanupTargetLib(TargetLib TargetLib, string TargetConfiguration)`

#### class `BuildCMakeLib.NMakeTargetPlatform`  
`public abstract class NMakeTargetPlatform : TargetPlatform`  
_public; L421-426_
- inherits: `TargetPlatform`
- L423 _public property_ `public override bool SeparateProjectPerConfig => ...`
- L425 _public property_ `public override string CMakeGeneratorName => ...`

#### class `BuildCMakeLib.MakefileTargetPlatform`  
`public abstract class MakefileTargetPlatform : TargetPlatform`  
_public; L428-440_
- inherits: `TargetPlatform`
- L430 _public property_ `public override bool SeparateProjectPerConfig => ...`
- L432 _public property_ `public override string CMakeGeneratorName => ...`
- L434 _public property_ `public override string MakeCommand => ...`

#### class `BuildCMakeLib.NinjaBuildTargetPlatform`  
`public abstract class NinjaBuildTargetPlatform : TargetPlatform`  
_public; L442-452_
- inherits: `TargetPlatform`
- L444 _public property_ `public override bool SeparateProjectPerConfig => ...`
- L446 _public property_ `public override string CMakeGeneratorName => ...`
- L448 _public property_ `public override string MakeCommand => ...`

#### class `BuildCMakeLib.VSTargetPlatform`  
`public abstract class VSTargetPlatform : TargetPlatform`  
_public; L454-465_
- inherits: `TargetPlatform`
- L456 _public property_ `public override bool SeparateProjectPerConfig => ...`
- L459 _protected method_ `protected override Dictionary<string, string> GetCMakeEnvironment()`

#### class `BuildCMakeLib.VS2017TargetPlatform`  
`public abstract class VS2017TargetPlatform : VSTargetPlatform`  
_public; L467-470_
- inherits: `VSTargetPlatform`
- L469 _public property_ `public override string CMakeGeneratorName => ...`

#### class `BuildCMakeLib.VS2019TargetPlatform`  
`public abstract class VS2019TargetPlatform : VSTargetPlatform`  
_public; L472-475_
- inherits: `VSTargetPlatform`
- L474 _public property_ `public override string CMakeGeneratorName => ...`

#### class `BuildCMakeLib.VS2022TargetPlatform`  
`public abstract class VS2022TargetPlatform : VSTargetPlatform`  
_public; L477-480_
- inherits: `VSTargetPlatform`
- L479 _public property_ `public override string CMakeGeneratorName => ...`

#### class `BuildCMakeLib.XcodeTargetPlatform`  
`public abstract class XcodeTargetPlatform : TargetPlatform`  
_public; L482-486_
- inherits: `TargetPlatform`
- L484 _public property_ `public override bool SeparateProjectPerConfig => ...`
- L485 _public property_ `public override string CMakeGeneratorName => ...`

#### class `VS2017TargetPlatform_Win64`  
`class VS2017TargetPlatform_Win64 : BuildCMakeLib.VS2017TargetPlatform`  
_internal*; L775-782_
- inherits: `BuildCMakeLib.VS2017TargetPlatform`
- L777 _public property_ `public override string PlatformOrGroupName => ...`
- L778 _public property_ `public override string DebugDatabaseExtension => ...`
- L779 _public property_ `public override string DynamicLibraryExtension => ...`
- L780 _public property_ `public override string StaticLibraryExtension => ...`
- L781 _public property_ `public override bool IsPlatformExtension => ...`

#### class `VS2019TargetPlatform_Win64`  
`class VS2019TargetPlatform_Win64 : BuildCMakeLib.VS2019TargetPlatform`  
_internal*; L784-805_
- inherits: `BuildCMakeLib.VS2019TargetPlatform`
- L786 _public property_ `public override string PlatformOrGroupName => ...`
- L787 _public property_ `public override string DebugDatabaseExtension => ...`
- L788 _public property_ `public override string DynamicLibraryExtension => ...`
- L789 _public property_ `public override string StaticLibraryExtension => ...`
- L790 _public property_ `public override string VariantDirectory => ...`
- L791 _public property_ `public override bool IsPlatformExtension => ...`
- L793 _private field_ `private readonly string Architecture`
- L795-798 _public ctor_ `public VS2019TargetPlatform_Win64(string Architecture = "Win64")`
- L800-804 _public method_ `public override string GetCMakeSetupArguments(BuildCMakeLib.TargetLib TargetLib, string TargetConfiguration)`

#### class `VS2022TargetPlatform_Win64`  
`class VS2022TargetPlatform_Win64 : BuildCMakeLib.VS2022TargetPlatform`  
_internal*; L807-828_
- inherits: `BuildCMakeLib.VS2022TargetPlatform`
- L809 _public property_ `public override string PlatformOrGroupName => ...`
- L810 _public property_ `public override string DebugDatabaseExtension => ...`
- L811 _public property_ `public override string DynamicLibraryExtension => ...`
- L812 _public property_ `public override string StaticLibraryExtension => ...`
- L813 _public property_ `public override string VariantDirectory => ...`
- L814 _public property_ `public override bool IsPlatformExtension => ...`
- L816 _private field_ `private readonly string Architecture`
- L818-821 _public ctor_ `public VS2022TargetPlatform_Win64(string Architecture = "Win64")`
- L823-827 _public method_ `public override string GetCMakeSetupArguments(BuildCMakeLib.TargetLib TargetLib, string TargetConfiguration)`

#### class `NMakeTargetPlatform_Win64`  
`class NMakeTargetPlatform_Win64 : BuildCMakeLib.NMakeTargetPlatform`  
_internal*; L830-837_
- inherits: `BuildCMakeLib.NMakeTargetPlatform`
- L832 _public property_ `public override string PlatformOrGroupName => ...`
- L833 _public property_ `public override string DebugDatabaseExtension => ...`
- L834 _public property_ `public override string DynamicLibraryExtension => ...`
- L835 _public property_ `public override string StaticLibraryExtension => ...`
- L836 _public property_ `public override bool IsPlatformExtension => ...`

#### class `MakefileTargetPlatform_Win64`  
`class MakefileTargetPlatform_Win64 : BuildCMakeLib.MakefileTargetPlatform`  
_internal*; L839-846_
- inherits: `BuildCMakeLib.MakefileTargetPlatform`
- L841 _public property_ `public override string PlatformOrGroupName => ...`
- L842 _public property_ `public override string DebugDatabaseExtension => ...`
- L843 _public property_ `public override string DynamicLibraryExtension => ...`
- L844 _public property_ `public override string StaticLibraryExtension => ...`
- L845 _public property_ `public override bool IsPlatformExtension => ...`

#### class `NinjaBuildTargetPlatform_Win64`  
`class NinjaBuildTargetPlatform_Win64 : BuildCMakeLib.NinjaBuildTargetPlatform`  
_internal*; L848-855_
- inherits: `BuildCMakeLib.NinjaBuildTargetPlatform`
- L850 _public property_ `public override string PlatformOrGroupName => ...`
- L851 _public property_ `public override string DebugDatabaseExtension => ...`
- L852 _public property_ `public override string DynamicLibraryExtension => ...`
- L853 _public property_ `public override string StaticLibraryExtension => ...`
- L854 _public property_ `public override bool IsPlatformExtension => ...`

#### class `NMakeTargetPlatform_Unix`  
`class NMakeTargetPlatform_Unix : BuildCMakeLib.NMakeTargetPlatform`  
_internal*; L857-870_
- inherits: `BuildCMakeLib.NMakeTargetPlatform`
- L859 _public property_ `public override string PlatformOrGroupName => ...`
- L860 _public property_ `public override string StaticLibraryExtension => ...`
- L861 _public property_ `public override string VariantDirectory => ...`
- L862 _public property_ `public override bool IsPlatformExtension => ...`
- L864 _private field_ `private readonly string Architecture`
- L866-869 _public ctor_ `public NMakeTargetPlatform_Unix(string Architecture)`

#### class `MakefileTargetPlatform_Unix`  
`class MakefileTargetPlatform_Unix : BuildCMakeLib.MakefileTargetPlatform`  
_internal*; L872-885_
- inherits: `BuildCMakeLib.MakefileTargetPlatform`
- L874 _public property_ `public override string PlatformOrGroupName => ...`
- L875 _public property_ `public override string StaticLibraryExtension => ...`
- L876 _public property_ `public override string VariantDirectory => ...`
- L877 _public property_ `public override bool IsPlatformExtension => ...`
- L879 _private field_ `private readonly string Architecture`
- L881-884 _public ctor_ `public MakefileTargetPlatform_Unix(string Architecture)`

#### class `NinjaBuildTargetPlatform_Unix`  
`class NinjaBuildTargetPlatform_Unix : BuildCMakeLib.NinjaBuildTargetPlatform`  
_internal*; L887-900_
- inherits: `BuildCMakeLib.NinjaBuildTargetPlatform`
- L889 _public property_ `public override string PlatformOrGroupName => ...`
- L890 _public property_ `public override string StaticLibraryExtension => ...`
- L891 _public property_ `public override string VariantDirectory => ...`
- L892 _public property_ `public override bool IsPlatformExtension => ...`
- L894 _private field_ `private readonly string Architecture`
- L896-899 _public ctor_ `public NinjaBuildTargetPlatform_Unix(string Architecture)`

#### class `NMakeTargetPlatform_Linux`  
`class NMakeTargetPlatform_Linux : NMakeTargetPlatform_Unix`  
_internal*; L902-910_
- inherits: `NMakeTargetPlatform_Unix`
- L904 _public property_ `public override string PlatformOrGroupName => ...`
- L906-909 _public ctor_ `public NMakeTargetPlatform_Linux(string Architecture) : base(Architecture)`

#### class `MakefileTargetPlatform_Linux`  
`class MakefileTargetPlatform_Linux : MakefileTargetPlatform_Unix`  
_internal*; L912-920_
- inherits: `MakefileTargetPlatform_Unix`
- L914 _public property_ `public override string PlatformOrGroupName => ...`
- L916-919 _public ctor_ `public MakefileTargetPlatform_Linux(string Architecture) : base(Architecture)`

#### class `NinjaBuildTargetPlatform_Linux`  
`class NinjaBuildTargetPlatform_Linux : NinjaBuildTargetPlatform_Unix`  
_internal*; L922-930_
- inherits: `NinjaBuildTargetPlatform_Unix`
- L924 _public property_ `public override string PlatformOrGroupName => ...`
- L926-929 _public ctor_ `public NinjaBuildTargetPlatform_Linux(string Architecture) : base(Architecture)`

#### class `MakefileTargetPlatform_LinuxArm64`  
`class MakefileTargetPlatform_LinuxArm64 : MakefileTargetPlatform_Unix`  
_internal*; L932-940_
- inherits: `MakefileTargetPlatform_Unix`
- L934 _public property_ `public override string PlatformOrGroupName => ...`
- L936-939 _public ctor_ `public MakefileTargetPlatform_LinuxArm64(string Architecture) : base(Architecture)`

#### class `NinjaBuildTargetPlatform_LinuxArm64`  
`class NinjaBuildTargetPlatform_LinuxArm64 : NinjaBuildTargetPlatform_Unix`  
_internal*; L942-950_
- inherits: `NinjaBuildTargetPlatform_Unix`
- L944 _public property_ `public override string PlatformOrGroupName => ...`
- L946-949 _public ctor_ `public NinjaBuildTargetPlatform_LinuxArm64(string Architecture) : base(Architecture)`

#### class `XcodeTargetPlatform_Mac`  
`class XcodeTargetPlatform_Mac : BuildCMakeLib.XcodeTargetPlatform`  
_internal*; L952-970_
- inherits: `BuildCMakeLib.XcodeTargetPlatform`
- L954 _public property_ `public override string PlatformOrGroupName => ...`
- L955 _public property_ `public override string StaticLibraryExtension => ...`
- L956 _public property_ `public override bool IsPlatformExtension => ...`
- L958 _private field_ `private readonly string Architecture`
- L960-963 _public ctor_ `public XcodeTargetPlatform_Mac(string Architecture)`
- L965-969 _public method_ `public override string GetCMakeSetupArguments(BuildCMakeLib.TargetLib TargetLib, string TargetConfiguration)`

#### class `MakefileTargetPlatform_Mac`  
`class MakefileTargetPlatform_Mac : BuildCMakeLib.MakefileTargetPlatform`  
_internal*; L972-991_
- inherits: `BuildCMakeLib.MakefileTargetPlatform`
- L974 _public property_ `public override string PlatformOrGroupName => ...`
- L975 _public property_ `public override string StaticLibraryExtension => ...`
- L976 _public property_ `public override string VariantDirectory => ...`
- L977 _public property_ `public override bool IsPlatformExtension => ...`
- L979 _private field_ `private readonly string Architecture`
- L981-984 _public ctor_ `public MakefileTargetPlatform_Mac(string Architecture)`
- L986-990 _public method_ `public override string GetCMakeSetupArguments(BuildCMakeLib.TargetLib TargetLib, string TargetConfiguration)`

#### class `NinjaBuildTargetPlatform_Mac`  
`class NinjaBuildTargetPlatform_Mac : BuildCMakeLib.NinjaBuildTargetPlatform`  
_internal*; L993-1012_
- inherits: `BuildCMakeLib.NinjaBuildTargetPlatform`
- L995 _public property_ `public override string PlatformOrGroupName => ...`
- L996 _public property_ `public override string StaticLibraryExtension => ...`
- L997 _public property_ `public override string VariantDirectory => ...`
- L998 _public property_ `public override bool IsPlatformExtension => ...`
- L1000 _private field_ `private readonly string Architecture`
- L1002-1005 _public ctor_ `public NinjaBuildTargetPlatform_Mac(string Architecture)`
- L1007-1011 _public method_ `public override string GetCMakeSetupArguments(BuildCMakeLib.TargetLib TargetLib, string TargetConfiguration)`

#### class `XcodeTargetPlatform_IOS`  
`public class XcodeTargetPlatform_IOS : BuildCMakeLib.XcodeTargetPlatform`  
_public; L1014-1026_
- inherits: `BuildCMakeLib.XcodeTargetPlatform`
- L1016 _public property_ `public override string PlatformOrGroupName => ...`
- L1017 _public property_ `public override string StaticLibraryExtension => ...`
- L1018 _public property_ `public override bool IsPlatformExtension => ...`
- L1019 _protected property_ `protected virtual string CMakeSystemName => ...`
- L1021-1025 _public method_ `public override string GetCMakeSetupArguments(BuildCMakeLib.TargetLib TargetLib, string TargetConfiguration)`

#### class `MakefileTargetPlatform_IOS`  
`public class MakefileTargetPlatform_IOS : BuildCMakeLib.MakefileTargetPlatform`  
_public; L1028-1064_
- inherits: `BuildCMakeLib.MakefileTargetPlatform`
- L1030 _public property_ `public override string PlatformOrGroupName => ...`
- L1031 _public property_ `public override string StaticLibraryExtension => ...`
- L1032 _public property_ `public override string VariantDirectory => ...`
- L1033 _public property_ `public override bool IsPlatformExtension => ...`
- L1034 _protected property_ `protected virtual string CMakeSystemName => ...`
- L1035 _protected property_ `protected virtual string SdkName => ...`
- L1036 _protected property_ `protected virtual string ClangArchitecture => ...`
- L1038 _protected field_ `protected readonly string Architecture`
- L1040-1043 _public ctor_ `public MakefileTargetPlatform_IOS(string Architecture)`
- L1045-1051 _public method_ `public override string GetCMakeSetupArguments(BuildCMakeLib.TargetLib TargetLib, string TargetConfiguration)`
- L1053-1062 _private method_ `private string GetSysRoot()`

#### class `NinjaBuildTargetPlatform_IOS`  
`public class NinjaBuildTargetPlatform_IOS : BuildCMakeLib.NinjaBuildTargetPlatform`  
_public; L1066-1101_
- inherits: `BuildCMakeLib.NinjaBuildTargetPlatform`
- L1068 _public property_ `public override string PlatformOrGroupName => ...`
- L1069 _public property_ `public override string StaticLibraryExtension => ...`
- L1070 _public property_ `public override string VariantDirectory => ...`
- L1071 _public property_ `public override bool IsPlatformExtension => ...`
- L1072 _protected property_ `protected virtual string CMakeSystemName => ...`
- L1073 _protected property_ `protected virtual string SdkName => ...`
- L1074 _protected property_ `protected virtual string ClangArchitecture => ...`
- L1076 _protected field_ `protected readonly string Architecture`
- L1078-1081 _public ctor_ `public NinjaBuildTargetPlatform_IOS(string Architecture)`
- L1083-1089 _public method_ `public override string GetCMakeSetupArguments(BuildCMakeLib.TargetLib TargetLib, string TargetConfiguration)`
- L1091-1100 _private method_ `private string GetSysRoot()`

#### class `XcodeTargetPlatform_TVOS`  
`class XcodeTargetPlatform_TVOS : XcodeTargetPlatform_IOS`  
_internal*; L1103-1107_
- inherits: `XcodeTargetPlatform_IOS`
- L1105 _public property_ `public override string PlatformOrGroupName => ...`
- L1106 _protected property_ `protected override string CMakeSystemName => ...`

#### class `MakefileTargetPlatform_TVOS`  
`class MakefileTargetPlatform_TVOS : MakefileTargetPlatform_IOS`  
_internal*; L1109-1118_
- inherits: `MakefileTargetPlatform_IOS`
- L1111 _public property_ `public override string PlatformOrGroupName => ...`
- L1112 _protected property_ `protected override string CMakeSystemName => ...`
- L1113 _protected property_ `protected override string SdkName => ...`
- L1115-1117 _public ctor_ `public MakefileTargetPlatform_TVOS(string Architecture) : base(Architecture)`

#### class `NinjaBuildTargetPlatform_TVOS`  
`class NinjaBuildTargetPlatform_TVOS : NinjaBuildTargetPlatform_IOS`  
_internal*; L1120-1129_
- inherits: `NinjaBuildTargetPlatform_IOS`
- L1122 _public property_ `public override string PlatformOrGroupName => ...`
- L1123 _protected property_ `protected override string CMakeSystemName => ...`
- L1124 _protected property_ `protected override string SdkName => ...`
- L1126-1128 _public ctor_ `public NinjaBuildTargetPlatform_TVOS(string Architecture) : base(Architecture)`

#### class `NMakeTargetPlatform_Android`  
`class NMakeTargetPlatform_Android : BuildCMakeLib.NMakeTargetPlatform`  
_internal*; L1131-1144_
- inherits: `BuildCMakeLib.NMakeTargetPlatform`
- L1133 _public property_ `public override string PlatformOrGroupName => ...`
- L1134 _public property_ `public override string StaticLibraryExtension => ...`
- L1135 _public property_ `public override string VariantDirectory => ...`
- L1136 _public property_ `public override bool IsPlatformExtension => ...`
- L1138 _private field_ `private readonly string Architecture`
- L1140-1143 _public ctor_ `public NMakeTargetPlatform_Android(string Architecture)`

#### class `MakefileTargetPlatform_Android`  
`class MakefileTargetPlatform_Android : BuildCMakeLib.MakefileTargetPlatform`  
_internal*; L1146-1159_
- inherits: `BuildCMakeLib.MakefileTargetPlatform`
- L1148 _public property_ `public override string PlatformOrGroupName => ...`
- L1149 _public property_ `public override string StaticLibraryExtension => ...`
- L1150 _public property_ `public override string VariantDirectory => ...`
- L1151 _public property_ `public override bool IsPlatformExtension => ...`
- L1153 _private field_ `private readonly string Architecture`
- L1155-1158 _public ctor_ `public MakefileTargetPlatform_Android(string Architecture)`

#### class `NinjaBuildTargetPlatform_Android`  
`class NinjaBuildTargetPlatform_Android : BuildCMakeLib.NinjaBuildTargetPlatform`  
_internal*; L1161-1174_
- inherits: `BuildCMakeLib.NinjaBuildTargetPlatform`
- L1163 _public property_ `public override string PlatformOrGroupName => ...`
- L1164 _public property_ `public override string StaticLibraryExtension => ...`
- L1165 _public property_ `public override string VariantDirectory => ...`
- L1166 _public property_ `public override bool IsPlatformExtension => ...`
- L1168 _private field_ `private readonly string Architecture`
- L1170-1173 _public ctor_ `public NinjaBuildTargetPlatform_Android(string Architecture)`

#### class `VS2019TargetPlatform_Android`  
`class VS2019TargetPlatform_Android : BuildCMakeLib.VS2019TargetPlatform`  
_internal*; L1176-1181_
- inherits: `BuildCMakeLib.VS2019TargetPlatform`
- L1178 _public property_ `public override string PlatformOrGroupName => ...`
- L1179 _public property_ `public override string StaticLibraryExtension => ...`
- L1180 _public property_ `public override bool IsPlatformExtension => ...`

### `Source/Programs/AutomationTool/Scripts/BuildCommonTools.Automation.cs` (AutomationScripts.Automation)


#### class `BuildCommonTools`  
`public class BuildCommonTools : BuildCommand`  
_public; L16-139_
- attrs: `[Help("Builds common tools used by the engine which are not part of typical editor or game builds. Useful when syncing source-only on GitHub.")] [Help("platforms=<X>+<Y>+...", "Specifies on or more platforms to build for (defaults to the current host platform)")] [Help("manifest=<Path>", "Writes a manifest of all the build products to the given path")]`
- inherits: `BuildCommand`
- L18-78 _public method_ `public override void ExecuteBuild()`
- L80-138 _public method_ `public static UnrealBuild.BuildAgenda MakeAgenda(UnrealBuildTool.UnrealTargetPlatform[] Platforms, List<string> ExtraBuildProducts)`

#### class `ZipProjectUp`  
`public class ZipProjectUp : BuildCommand`  
_public; L141-170_
- inherits: `BuildCommand`
- L143-169 _public method_ `public override void ExecuteBuild()`

### `Source/Programs/AutomationTool/Scripts/BuildCookRun.Automation.cs` (AutomationScripts.Automation)


#### class `BuildCookRun`  
`public class BuildCookRun : BuildCommand, IProjectParamsHelpers`  
_public; L24-347_
- attrs: `[Help(@"Builds/Cooks/Runs a project. For non-uprojects project targets are discovered by compiling target rule files found in the project folder. If -map is not specified, the command looks for DefaultMap entry in the project's DefaultEngine.ini and if not found, in BaseEngine.ini. If no DefaultMap can be found, the command falls back to /Engine/Maps/Entry.")] [Help("project=Path", @"Project path `
- inherits: `BuildCommand, IProjectParamsHelpers`
- L26-46 _public method_ `public override void ExecuteBuild()`
- L48-151 _protected method_ `protected ProjectParams SetupParams()`
- L158-170 _private method_ `private static string GetFirstMap(string Maps)` — In case the command line specified multiple map names with a '+', selects the first map from the list.
- L172-181 _private method_ `private string GetTargetName(Type TargetRulesType)`
- L183-223 _private method_ `private string GetDefaultMap(ProjectParams Params)`
- L225-249 _private method_ `private string GetDefaultMapFromIni(string IniFilename, bool DedicatedServer)`
- L251-275 _protected method_ `protected void DoBuildCookRun(ProjectParams Params)`
- L277-301 _private method_ `private void MakeForeignSample()`
- L303-327 _private method_ `private void MakeForeignCodeSample()`
- L329 _private field_ `private FileReference ProjectFullPath`
- L330-346 _public property_ `public virtual FileReference ProjectPath { get; }`

### `Source/Programs/AutomationTool/Scripts/BuildDerivedDataCache.Automation.cs` (AutomationScripts.Automation)


#### class `BuildDerivedDataCache`  
`public class BuildDerivedDataCache : BuildCommand`  
_public; L16-138_
- inherits: `BuildCommand`
- L18-137 _public method_ `public override void ExecuteBuild()`

### `Source/Programs/AutomationTool/Scripts/BuildHlslcc.Automation.cs` (AutomationScripts.Automation)


#### class `BuildHlslcc`  
`class BuildHlslcc : BuildCommand`  
_internal*; L28-996_
- attrs: `[Help("Builds Hlslcc using CMake build system.")] [Help("TargetPlatforms", "Specify a list of target platforms to build, separated by '+' characters (eg. -TargetPlatforms=Win64+Linux+Mac). Architectures are specified with '-'. Default is Win64+Linux.")] [Help("TargetConfigs", "Specify a list of configurations to build, separated by '+' characters (eg. -TargetConfigs=Debug+RelWithDebInfo). Default `
- inherits: `BuildCommand`
- L30 _private* const_ `const int InvalidChangeList = -1`
- L56 _private field_ `private static string[] APEXSpecialLibs = { "NvParameterized", "RenderDebug" }`
- L59 _private field_ `private static FileReference MsDev22Exe`
- L60 _private field_ `private static FileReference MsBuildExe`
- L63 _private field_ `private static DirectoryReference SourceRootDirectory = DirectoryReference.Combine(Unreal.RootDirectory, "Engine", "Source", "ThirdParty", "hlslcc", "hlslcc")`
- L64 _private field_ `private static DirectoryReference RootOutputLibDirectory = DirectoryReference.Combine(SourceRootDirectory, "lib")`
- L65 _private field_ `private static DirectoryReference ThirdPartySourceDirectory = DirectoryReference.Combine(Unreal.RootDirectory, "Engine", "Source", "ThirdParty")`
- L67-86 _private method_ `private static string GetCMakeNameAndSetupEnv(TargetPlatformData TargetData)`
- L88-109 _private method_ `private static string GetCMakeTargetDirectoryName(TargetPlatformData TargetData, WindowsCompiler TargetWindowsCompiler)`
- L111-116 _private method_ `private static DirectoryReference GetProjectDirectory(TargetPlatformData TargetData, WindowsCompiler TargetWindowsCompiler = WindowsCompiler.VisualStudio2022)`
- L118-126 _private method_ `private static string GetBundledLinuxLibCxxFlags(string ToolchainPath)`
- L128-167 _private method_ `private static string GetLinuxToolchainSettings(TargetPlatformData TargetData)`
- L169-207 _private method_ `private static string GetCMakeArguments(TargetPlatformData TargetData, string BuildConfig = "", WindowsCompiler TargetWindowsCompiler = WindowsCompiler.VisualStudio2022)`
- L209-217 _private method_ `private static string GetMsDevExe(TargetPlatformData TargetData)`
- L219-227 _private method_ `private static string GetMsBuildExe(TargetPlatformData TargetData)`
- L229-232 _private method_ `private static string GetTargetLibSolutionName()`
- L234-238 _private method_ `private static FileReference GetTargetLibSolutionFileName(TargetPlatformData TargetData, WindowsCompiler TargetWindowsCompiler)`
- L240-243 _private method_ `private static bool DoesPlatformUseMSBuild(TargetPlatformData TargetData)`
- L245-248 _private method_ `private static bool DoesPlatformUseMakefiles(TargetPlatformData TargetData)`
- L250-253 _private method_ `private static bool DoesPlatformUseXcode(TargetPlatformData TargetData)`
- L255-297 _private method_ `private List<TargetPlatformData> GetTargetPlatforms()`
- L299-313 _public method_ `public List<string> GetTargetConfigurations()`
- L315-335 _private method_ `private List<WindowsCompiler> GetTargetWindowsCompilers()`
- L337-349 _private method_ `private static void MakeFreshDirectoryIfRequired(DirectoryReference Directory)`
- L351-382 _public method_ `public static int RunLocalProcess(Process LocalProcess)`
- L384-390 _public method_ `public static int RunLocalProcessAndLogOutput(ProcessStartInfo StartInfo)`
- L392-474 _private method_ `private static void SetupBuildForTargetLibAndPlatform(TargetPlatformData TargetData, List<string> TargetConfigurations, List<WindowsCompiler> TargetWindowsCompilers, bool bCleanOnly)`
- L476-484 _private method_ `private static string GetMsDevExe(WindowsCompiler Version)`
- L486-494 _private method_ `private static string GetMsBuildExe(WindowsCompiler Version)`
- L496-517 _private method_ `private static string RemoveOtherMakeAndCygwinFromPath(string WindowsPath)`
- L518-546 _private method_ `private static void SetupStaticBuildEnvironment()`
- L548-567 _private method_ `private static void BuildMSBuildTarget(TargetPlatformData TargetData, List<string> TargetConfigurations, WindowsCompiler TargetWindowsCompiler = WindowsCompiler.VisualStudio2022)`
- L569-609 _private method_ `private static void BuildMakefileTarget(TargetPlatformData TargetData, List<string> TargetConfigurations)`
- L611-628 _private method_ `private static void BuildXcodeTarget(TargetPlatformData TargetData, List<string> TargetConfigurations)`
- L630-651 _private method_ `private static void BuildTargetLibForPlatform(TargetPlatformData TargetData, List<string> TargetConfigurations, List<WindowsCompiler> TargetWindowsCompilers)`
- L653-688 _private method_ `private static DirectoryReference GetPlatformLibDirectory(TargetPlatformData TargetData, WindowsCompiler TargetWindowsCompiler)`
- L690-702 _private method_ `private static string GetPlatformLibExtension(TargetPlatformData TargetData)`
- L704-715 _private method_ `private static void FindOutputFilesHelper(HashSet<FileReference> OutputFiles, DirectoryReference BaseDir, string SearchPrefix)`
- L717-738 _private method_ `private static void FindOutputFiles(HashSet<FileReference> OutputFiles, TargetPlatformData TargetData, string TargetConfiguration, WindowsCompiler TargetWindowsCompiler = WindowsCompiler.VisualStudio2022)`
- L740-763 _private method_ `private static bool PlatformSupportsTargetLib(TargetPlatformData TargetData)`
- L765-946 _public method_ `public override void ExecuteBuild()`
- L948-995 _private method_ `private void CopyLibsToFinalDestination(TargetPlatformData TargetData, List<string> TargetConfigurations, WindowsCompiler TargetWindowsCompiler = WindowsCompiler.VisualStudio2022)`

#### struct `BuildHlslcc.TargetPlatformData`  
`private struct TargetPlatformData`  
_private; L32-53_
- L34 _public field_ `public UnrealTargetPlatform Platform`
- L35 _public field_ `public string Architecture`
- L37-42 _public ctor_ `public TargetPlatformData(UnrealTargetPlatform InPlatform)`
- L43-47 _public ctor_ `public TargetPlatformData(UnrealTargetPlatform InPlatform, string InArchitecture)`
- L49-52 _public method_ `public override string ToString()`

### `Source/Programs/AutomationTool/Scripts/BuildPluginCommand.Automation.cs` (AutomationScripts.Automation)


#### class `BuildPlugin`  
`public sealed class BuildPlugin : BuildCommand`  
_public; L26-593_
- attrs: `[Help("Builds a plugin, and packages it for distribution")] [Help("Plugin", "Specify the path to the descriptor file for the plugin that should be packaged")] [Help("Dependencies", "Specify the path to the plugin descriptor file for a dependency of the Plugin argument - only required if it is not accessible in the Engine/Plugins directory. Can be specified multiple times, one per dependency.")] [H`
- inherits: `BuildCommand`
- L28 _private* const_ `const string MacDefaultArchitectures = "arm64+x64"`
- L29 _private* const_ `const string AndroidDefaultArchitectures = "arm64+x64"`
- L31 _private* field_ `string UnrealBuildToolDllRelativePath = @"Engine/Binaries/DotNET/UnrealBuildTool/UnrealBuildTool.dll"`
- L32 _private* field_ `FileReference UnrealBuildToolDll`
- L33 _private field_ `static private Dictionary<UnrealTargetPlatform, string> PlatformToArchitectureMap = ...`
- L33 _private field_ `static private Dictionary< PlatformToArchitectureMap = new Dictionary<UnrealTargetPlatform, string>()`
- L35-169 _public method_ `public override void ExecuteBuild()`
- L171-199 _private method_ `private FileReference CreateHostProject(FileReference HostProjectFile, FileReference PluginFile, IReadOnlyList<FileReference> DependencyPlugins)`
- L210-245 _private method_ `private static TargetPlatform GetTargetPlatform( UnrealTargetPlatform Platform )`
- L250-285 _public method_ `public static FileReference[] CompilePlugin(string UBTExe, FileReference HostProjectFile, FileReference HostProjectPluginFile, PluginDescriptor Plugin, List<UnrealTargetPlatform> HostPlatforms, List<UnrealTargetPlatform> TargetPlatforms, string AdditionalArgs = "")` — attrs: `[Obsolete("Deprecated in UE5.1; function signature changed")]`
- L287-322 _public method_ `public static FileReference[] CompilePlugin(FileReference UnrealBuildToolDll, FileReference HostProjectFile, FileReference HostProjectPluginFile, PluginDescriptor Plugin, IReadOnlyList<UnrealTargetPlatform> HostPlatforms, List<UnrealTargetPlatform> TargetPlatforms, string AdditionalArgs = "")`
- L325-367 _private* method_ `static void CompilePluginWithUBT(string UBTExe, FileReference HostProjectFile, FileReference HostProjectPluginFile, PluginDescriptor Plugin, string TargetName, TargetType TargetType, UnrealTargetPlatform Platform, UnrealTargetConfiguration Configuration, List<FileReference> ManifestFileNames, string InAdditionalArgs)` — attrs: `[Obsolete("Deprecated in UE5.1; function signature has changed")]`
- L369-417 _private* method_ `static void CompilePluginWithUBT(FileReference UnrealBuildToolDll, FileReference HostProjectFile, FileReference HostProjectPluginFile, PluginDescriptor Plugin, string TargetName, TargetType TargetType, UnrealTargetPlatform Platform, UnrealTargetConfiguration Configuration, List<FileReference> ManifestFileNames, string InAdditionalArgs)`
- L419-446 _public method_ `public static void PackagePlugin(FileReference SourcePluginFile, IEnumerable<FileReference> BuildProducts, DirectoryReference TargetDir, bool bUnversioned, IEnumerable<UnrealTargetPlatform> TargetPlatforms)`
- L448-455 _private* method_ `static void AddRulesFromFileToFilter(FileFilter Filter, FileReference FilterFile)`
- L457-489 _private* method_ `static IEnumerable<FileReference> FilterPluginFiles(FileReference PluginFile, IEnumerable<FileReference> BuildProducts, IEnumerable<UnrealTargetPlatform> TargetPlatforms)`
- L491-540 _private* method_ `static List<UnrealTargetPlatform> GetTargetPlatforms(BuildCommand Command, UnrealTargetPlatform HostPlatform)`
- L542-592 _private* method_ `static IReadOnlyList<UnrealTargetPlatform> GetHostPlatforms(BuildCommand Command)`

#### class `BuildPlugin.TargetPlatform`  
`public abstract class TargetPlatform : CommandUtils`  
_public; L201-208_
- inherits: `CommandUtils`
- L204 _public method_ `public abstract void CompilePluginWithUBT(string UBTExe, FileReference HostProjectFile, FileReference HostProjectPluginFile, PluginDescriptor Plugin, string TargetName, TargetType TargetType, UnrealTargetPlatform Platform, UnrealTargetConfiguration Configuration, List<FileReference> ManifestFileNames, string InAdditionalArgs)` — attrs: `[Obsolete("Deprecated in UE5.1; function signature changed")]`
- L206 _public method_ `public abstract void CompilePluginWithUBT(FileReference UnrealBuildToolDll, FileReference HostProjectFile, FileReference HostProjectPluginFile, PluginDescriptor Plugin, string TargetName, TargetType TargetType, UnrealTargetPlatform Platform, UnrealTargetConfiguration Configuration, List<FileReference> ManifestFileNames, string InAdditionalArgs)`

### `Source/Programs/AutomationTool/Scripts/BuildProjectCommand.Automation.cs` (AutomationScripts.Automation)


#### enum `ProjectBuildTargets`  
`public enum ProjectBuildTargets`  
_public; L15-28_
- attrs: `[Flags]`
- L17 _public* enumerator_ `None = 0`
- L18 _public* enumerator_ `Editor = 1 << 0`
- L19 _public* enumerator_ `ClientCooked = 1 << 1`
- L20 _public* enumerator_ `ServerCooked = 1 << 2`
- L21 _public* enumerator_ `Bootstrap = 1 << 3`
- L22 _public* enumerator_ `CrashReporter = 1 << 4`
- L23 _public* enumerator_ `Programs = 1 << 5`
- L24 _public* enumerator_ `UnrealPak = 1 << 6`
- L27 _public* enumerator_ `All = Editor | ClientCooked | ServerCooked | Bootstrap | CrashReporter | Programs | UnrealPak`

#### class `AutomationScripts.Project`  
`public partial class Project : CommandUtils`  
_public; L42-272_
- inherits: `CommandUtils`
- desc: Helper command used for compiling.
- L49-57 _public method_ `static public bool PlatformSupportsCrashReporter(UnrealTargetPlatform InPlatform)` — PlatformSupportsCrashReporter
- L60-271 _public method_ `public static void Build(BuildCommand Command, ProjectParams Params, int WorkingCL = -1, ProjectBuildTargets TargetMask = ProjectBuildTargets.All)`

### `Source/Programs/AutomationTool/Scripts/BuildTarget.Automation.cs` (AutomationScripts.Automation)


#### class `AutomationTool.BuildTarget`  
`public class BuildTarget : BuildCommand`  
_public; L28-304_
- attrs: `[Help("Builds the specified targets and configurations for the specified project.")] [Help("Example BuildTarget -project=QAGame -target=Editor+Game -platform=Win64+Android -configuration=Development.")] [Help("Note: Editor will only ever build for the current platform in a Development config and required tools will be included")] [Help("project=<QAGame>", "Project to build. Will search current pat`
- inherits: `BuildCommand`
- L31 _public property_ `public string ProjectName { get; set; }`
- L33 _public property_ `public string Targets { get; set; }`
- L35 _public property_ `public string Platforms { get; set; }`
- L37 _public property_ `public string Configurations { get; set; }`
- L39 _public property_ `public bool Clean { get; set; }`
- L41 _public property_ `public bool NoTools { get; set; }`
- L43 _public property_ `public string UBTArgs { get; set; }`
- L45 _public property_ `public bool Preview { get; set; }`
- L63-68 _public ctor_ `public BuildTarget()`
- L70-220 _public method_ `public override ExitCode Execute()`
- L231-303 _public method_ `public SimpleTargetInfo ProjectTargetFromTargetName(string InTargetName, FileReference InProjectFile, IEnumerable<UnrealTargetPlatform> InPlatformList, IEnumerable<UnrealTargetConfiguration> InConfigurationList)` — Takes a target type like "Editor" and returns the actual targetname used by the specified project. If no project is specified then the name of the UE types (e.g. UnrealEditor) is returned.

#### class `AutomationTool.BuildTarget.SimpleTargetInfo`  
`public class SimpleTargetInfo`  
_public; L49-60_
- L51 _public property_ `public string TargetName { get; set; }`
- L53 _public property_ `public TargetType Type { get; set; }`
- L55-59 _public ctor_ `public SimpleTargetInfo(string InName, TargetType InType)`

#### class `AutomationTool.BuildEditor`  
`class BuildEditor : BuildTarget`  
_internal*; L311-332_
- attrs: `[Help("Builds the editor for the specified project.")] [Help("Example BuildEditor -project=QAGame")] [Help("Note: Editor will only ever build for the current platform in a Development config and required tools will be included")] [Help("project=<QAGame>", "Project to build. Will search current path and paths in ueprojectdirs. If omitted will build vanilla UnrealEditor")] [Help("notools", "Don't bu`
- inherits: `BuildTarget`
- L313-316 _public ctor_ `public BuildEditor()`
- L318-331 _public method_ `public override ExitCode Execute()`

#### class `AutomationTool.BuildGame`  
`class BuildGame : BuildTarget`  
_internal*; L340-346_
- attrs: `[Help("Builds the game for the specified project.")] [Help("Example BuildGame -project=QAGame -platform=Win64+Android -configuration=Development.")] [Help("project=<QAGame>", "Project to build. Will search current path and paths in ueprojectdirs.")] [Help("platform=Wind64+Android", "Platforms to build, join multiple platforms using +")] [Help("configuration=Development+Test", "Configurations to bu`
- inherits: `BuildTarget`
- L342-345 _public ctor_ `public BuildGame()`

#### class `AutomationTool.BuildServer`  
`class BuildServer : BuildTarget`  
_internal*; L354-360_
- attrs: `[Help("Builds the server for the specified project.")] [Help("Example BuildServer -project=QAGame -platform=Win64 -configuration=Development.")] [Help("project=<QAGame>", "Project to build. Will search current path and paths in ueprojectdirs.")] [Help("platform=Win64", "Platforms to build, join multiple platforms using +")] [Help("configuration=Development+Test", "Configurations to build, join mul`
- inherits: `BuildTarget`
- L356-359 _public ctor_ `public BuildServer()`

### `Source/Programs/AutomationTool/Scripts/BuildThirdPartyLibs.Automation.cs` (AutomationScripts.Automation)


#### class `BuildThirdPartyLibs`  
`class BuildThirdPartyLibs : BuildCommand`  
_internal*; L48-168_
- attrs: `[Help("Builds third party libraries, and puts them all into a changelist")] [Help("Libs", "[Optional] + separated list of libraries to compile; if not specified this job will build all libraries it can find builder scripts for")] [Help("Changelist", "[Optional] a changelist to check out into; if not specified, a changelist will be created")] [Help("SearchDir", "[Optional] Directory to search for t`
- inherits: `BuildCommand`
- L51 _private field_ `static private string DefaultLibraryDir = "Engine/Source/ThirdParty"`
- L54 _private field_ `static private string WindowsCompileScript = "UE_BuildThirdPartyLib.bat"`
- L55 _private field_ `static private string MacCompileScript = "UE_BuildThirdPartyLib_Mac.command"`
- L56 _private field_ `static private string LinuxCompileScript = "UE_BuildThirdPartyLib_Linux.sh"`
- L58-167 _public method_ `public override void ExecuteBuild()`

### `Source/Programs/AutomationTool/Scripts/CheckBalancedMacros.cs` (AutomationScripts.Automation)


#### class `AutomationTool.CheckBalancedMacros`  
`class CheckBalancedMacros : BuildCommand`  
_internal*; L23-484_
- attrs: `[Help("Checks that all source files have balanced macros for enabling/disabling optimization, warnings, etc...")] [Help("Project=<Path>", "Path to an additional project file to consider")] [Help("File=<Path>", "Path to a file to parse in isolation, for testing")] [Help("OverrideFileList=<Path>", "Path to a text file with paths to the files you want to parse")] [Help("Ignore=<Name>", "File name (wi`
- inherits: `BuildCommand`
- L28 _public field_ `public static readonly string[] SourceDirectories = { "Platforms", "Plugins", "Restricted", "Shaders", "Source" }` — List of directories relative to the root that can contain source files
- L33 _private* field_ `static readonly string[,] MacroPairs = new string[,] { { "PRAGMA_DISABLE_OPTIMIZATION", "PRAGMA_ENABLE_OPTIMIZATION" }, { "UE_DISABLE_OPTIMIZATION_SHIP", "UE_ENABLE_OPTIMIZATION_SHIP" }, { "PRAGMA_DISABLE_DEPRECATION_WARNINGS", "PRAGMA_ENA ...` — List of macros that should be paired up
- L89 _private* field_ `static readonly Regex OpenLoctextNamespaceRegex = new Regex(@"\G#define\s+LOCTEXT_NAMESPACE")` — Regexes for LOCTEXT_NAMESPACE preprocessor identification This could be generalized like the above if we had other pairings we wanted to manage
- L90 _private* field_ `static readonly Regex CloseLoctextNamespaceRegex = new Regex(@"\G#undef\s+LOCTEXT_NAMESPACE")`
- L95 _private* field_ `HashSet<string> IgnoreFileNames = new HashSet<string>(StringComparer.OrdinalIgnoreCase) { "PreWindowsApi.h", "PostWindowsApi.h", "USDIncludesStart.h", "USDIncludesEnd.h", "PreOpenCVHeaders.h", "PostOpenCVHeaders.h", }` — List of files to ignore for balanced macros. Additional filenames may be specified on the command line via -Ignore=...
- L108-249 _public method_ `public override void ExecuteBuild()` — Main entry point for the command
- L257-280 _private* method_ `void FindSourceFiles(DirectoryInfo BaseDir, List<FileReference> SourceFiles, ThreadPoolWorkQueue Queue)` — Finds all the source files under a given directory
- L288-464 _private* method_ `void CheckSourceFile(FileReference SourceFile, Dictionary<string, List<int>> IdentifierToIndex, object LogLock)` — Checks whether macros in the given source file are matched
- L472-483 _private* method_ `int GetLineNumber(string Text, int Offset)` — Converts an offset within a text buffer into a line number

### `Source/Programs/AutomationTool/Scripts/CheckCsprojDotNetVersion.cs` (AutomationScripts.Automation)


#### class `CheckCsprojDotNetVersion`  
`class CheckCsprojDotNetVersion : BuildCommand`  
_internal*; L14-132_
- inherits: `BuildCommand`
- L16-131 _public method_ `public override void ExecuteBuild()`

### `Source/Programs/AutomationTool/Scripts/CheckForHacks.cs` (AutomationScripts.Automation)


#### class `AutomationTool.CheckForHacks`  
`class CheckForHacks : BuildCommand`  
_internal*; L20-169_
- attrs: `[Help("Audits the current branch for comments denoting a hack that was not meant to leave another branch, following a given format (\"BEGIN XXXX HACK\", where XXXX is one or more tags separated by spaces).")] [Help("Allowed tags may be specified manually on the command line. At least one must match, otherwise it will print a warning.")] [Help("The current branch name and fragments of the branch pa`
- inherits: `BuildCommand`
- L25 _private* field_ `static readonly HashSet<string> TextExtensions = new HashSet<string>(StringComparer.InvariantCultureIgnoreCase) { ".cpp", ".c", ".h", ".inl", ".m", ".mm", ".java", ".pl", ".pm", ".cs", ".sh", ".bat", ".xml", ".htm", ".html", ".xhtml", ".css", ".asp" ...` — List of file extensions to consider text, and search for hack lines
- L53 _private* field_ `static readonly Regex CompiledRegex = new Regex("(?<!\\w)(?:BEGIN|START)\\s([^;]*)\\sHACK(?!\\w)", RegexOptions.IgnoreCase | RegexOptions.Compiled)` — The pattern that should match hack comments (and captures a list of tags). Ignore anything with a semicolon between BEGIN and HACK to avoid matching statements with "HACK" as a comment (seen in LLVM).
- L58-103 _public method_ `public override void ExecuteBuild()` — Executes the command
- L111-128 _private* method_ `void FindAllFiles(ThreadPoolWorkQueue Queue, DirectoryInfo BaseDir, List<FileInfo> FilesToCheck)` — Enumerates all files under the given directory
- L135-168 _private* method_ `void ScanSourceFile(FileInfo FileToCheck, HashSet<string> AllowTags)` — Scans an individual source file for hack comments

### `Source/Programs/AutomationTool/Scripts/CheckPerforceCase.cs` (AutomationScripts.Automation)


#### class `BuildScripts.Automation.CheckPerforceCase`  
`class CheckPerforceCase : BuildCommand`  
_internal*; L18-134_
- attrs: `[RequireP4] [DoesNotNeedP4CL] [Help("Checks that the casing of files within a path on a case-insensitive Perforce server is correct.")] [Help("Path", "The path to query")]`
- inherits: `BuildCommand`
- L107-133 _public method_ `public override void ExecuteBuild()`

#### class `BuildScripts.Automation.CheckPerforceCase.TreeNode`  
`class TreeNode`  
_private*; L20-105_
- L22 _public field_ `public string Path`
- L23 _public field_ `public List<string> Files = new List<string>()`
- L24 _public field_ `public Dictionary<string, TreeNode> ChildNodes = ...`
- L24 _public field_ `public Dictionary< ChildNodes = new Dictionary<string, TreeNode>(StringComparer.Ordinal)`
- L25 _public field_ `public int Count`
- L27-30 _public ctor_ `public TreeNode(string Path)`
- L32-52 _public method_ `public void Add(string DepotPath, int Idx)`
- L54-67 _public method_ `public IEnumerable<string> EnumerateFiles()`
- L69-104 _public method_ `public int PrintIssues(ILogger Logger)`

### `Source/Programs/AutomationTool/Scripts/CheckRestrictedFolders.cs` (AutomationScripts.Automation)


#### class `AutomationTool.CheckRestrictedFolders`  
`class CheckRestrictedFolders : BuildCommand`  
_internal*; L21-74_
- attrs: `[Help("Checks a directory for folders which should not be distributed")] [Help("BaseDir=<Path>", "Path to the base directory containing files to check")] [Help("Allow=<Name1>+<Name2>...", "Specify names of folders which should be excluded from the list")]`
- inherits: `BuildCommand`
- L23-58 _public method_ `public override ExitCode Execute()`
- L60-73 _private* method_ `void FindRestrictedFolders(DirectoryInfo CurrentDir, HashSet<string> RestrictedNames, List<DirectoryInfo> ProblemFolders)`

### `Source/Programs/AutomationTool/Scripts/CheckTargetExists.cs` (AutomationScripts.Automation)


#### class `AutomationTool.CheckTargetExists`  
`class CheckTargetExists : BuildCommand`  
_internal*; L22-81_
- attrs: `[Help("Checks that the given target exists, by looking for the relevant receipt.")] [Help("-Target", "Name of the target to check")] [Help("-Platform", "Platform the target was built for")] [Help("-Configuration", "Configuration for the target")] [Help("-Architecture", "Architecture that the target was built for")] [Help("-Project", "Path to the project containing the target")]`
- inherits: `BuildCommand`
- L24-80 _public method_ `public override void ExecuteBuild()`

### `Source/Programs/AutomationTool/Scripts/CleanAutomationReports.cs` (AutomationScripts.Automation)


#### class `AutomationTool.CleanAutomationReports`  
`class CleanAutomationReports : BuildCommand`  
_internal*; L24-119_
- attrs: `[Help("Removes folders in an automation report directory that are older than a certain time.")] [Help("ReportDir=<Directory>", "Path to the root report directory")] [Help("Days=<N>", "Number of days to keep reports for")] [Help("Depth=<N>", "How many subdirectories deep to clean, defaults to 0 (top level cleaning).")]`
- inherits: `BuildCommand`
- desc: Commandlet to clean up all afolders under a temp storage root that are older than a given number of days
- L29-72 _public method_ `public override void ExecuteBuild()` — Entry point for the commandlet
- L74-118 _private method_ `private int CleanDirectories(DirectoryInfo Directory, DateTime RetainTime, List<DirectoryInfo> DirectoriesToDelete, int TargetDepth, int CurrentDepth = 0)`

### `Source/Programs/AutomationTool/Scripts/CleanFormalBuilds.Automation.cs` (AutomationScripts.Automation)


#### class `AutomationTool.CleanFormalBuilds`  
`class CleanFormalBuilds : BuildCommand`  
_internal*; L14-49_
- attrs: `[Help("Removes folders matching a pattern in a given directory that are older than a certain time.")] [Help("ParentDir=<Directory>", "Path to the root directory")] [Help("SearchPattern=<Pattern>", "Pattern to match against")] [Help("Days=<N>", "Number of days to keep in temp storage (optional - defaults to 4)")]`
- inherits: `BuildCommand`
- desc: Commandlet to clean up all builds under a root directory that follow a given pattern and are older than a given number of days
- L19-48 _public method_ `public override void ExecuteBuild()` — Entry point for the commandlet

### `Source/Programs/AutomationTool/Scripts/CookCommand.Automation.cs` (AutomationScripts.Automation)


#### class `AutomationScripts.Project`  
`public partial class Project : CommandUtils`  
_public; L28-789_
- inherits: `CommandUtils`
- desc: Helper command used for cooking.
- L30-117 _private method_ `private static string GetGenericCookCommandletParams(ProjectParams Params, ConfigHierarchy EditorConfig)`
- L119-144 _private method_ `private static HashSet<string> GetPlatformsToCook(ProjectParams Params)`
- L146-273 _public method_ `public static void GetCookByTheBookCommandletParams(ProjectParams Params, out string CommandletParams, out string[] Maps, out string[] DirectoriesToCook, out string InternationalizationPreset, out string[] CulturesToCook, out string PlatformsToCook)`
- L275-378 _public method_ `public static void Cook(ProjectParams Params)`
- L391-470 _private method_ `private static void ImportSnapshots(ProjectParams Params, string PlatformsToCook)`
- L497-771 _private method_ `private static void DiffCookedContent(ProjectParams Params)`
- L773-788 _private method_ `private static void CleanupCookedData(List<string> PlatformsToCook, ProjectParams Params)`

#### struct `AutomationScripts.Project.CloudConfiguration`  
`private struct CloudConfiguration`  
_private; L380-389_
- L382 _public field_ `public string Host = ""`
- L383 _public field_ `public string BuildsNamespace = ""`
- L384 _public field_ `public string OAuthProviderIdentifier = ""`
- L386-388 _public ctor_ `public CloudConfiguration()`

#### struct `AutomationScripts.Project.FileInfo`  
`public struct FileInfo`  
_public; L472-495_
- L474-481 _public ctor_ `public FileInfo(string InFilename)`
- L482-489 _public ctor_ `public FileInfo(string InFilename, long InFirstByteFailed, long InBytesMismatch, long InFile1Size, long InFile2Size)`
- L490 _public field_ `public string Filename`
- L491 _public field_ `public long FirstByteFailed`
- L492 _public field_ `public long BytesMismatch`
- L493 _public field_ `public long File1Size`
- L494 _public field_ `public long File2Size`

### `Source/Programs/AutomationTool/Scripts/CookDiffReportHelper.cs` (AutomationScripts.Automation)


#### class `AutomationTool.CookDiffReportHelper`  
`public class CookDiffReportHelper : BuildCommand`  
_public; L18-636_
- attrs: `[Help("CookDiffReportHelper analyses the json files created by -run=cook -diffonly -cookdiffjson=path/to/my.json ... ")] [Help("Source", "Path to the cookdiffjson file or folder")] [Help("MaxResults", "Maximum number of results to display (default is all results)")] [Help("MaxFiles", "Maximum number of files to log for a particular diff (default 10. use 0 to show all files)")]`
- inherits: `BuildCommand`
- L20-32 _public method_ `public override void ExecuteBuild()`
- L34-49 _private method_ `private void GenerateReport(DetailRoot Detail, int MaxResults, int MaxFiles )`
- L99-127 _private method_ `private IEnumerable<FileReference> FindSourceJsons(string Source)`
- L129-171 _private method_ `private async Task<DetailRoot> ParseAndMergeJsonAsync(IEnumerable<FileReference> SourceJsons)`
- L173-190 _private method_ `private DetailRoot ReadJson(string Source)`
- L193-207 _private method_ `private static string GetCleanCallstack(string Callstack)`
- L209-224 _private method_ `private static string GetCleanPackageFilename(string Filename)`

#### class `AutomationTool.CookDiffReportHelper.DetailRoot`  
`private sealed class DetailRoot`  
_private; L53-58_
- L55 _public property_ `public string ProjectName { get; set; }`
- L56 _public property_ `public string BuildVersion { get; set; }`
- L57 _public property_ `public List<Package> Packages { get; set; }`

#### class `AutomationTool.CookDiffReportHelper.Package`  
`private sealed class Package`  
_private; L60-68_
- L62 _public property_ `public string Filename { get; set; }`
- L63 _public property_ `public string ClassName { get; set; }`
- L64 _public property_ `public Section Header { get; set; }`
- L65 _public property_ `public Section Exports { get; set; }`
- L66 _public property_ `public string Diagnostics { get; set; }`
- L67 _public property_ `public IEnumerable<Section> Sections => ...`

#### class `AutomationTool.CookDiffReportHelper.Section`  
`private sealed class Section`  
_private; L70-80_
- L72 _public property_ `public string Filename { get; set; }`
- L73 _public property_ `public UInt64 SourceSize { get; set; }`
- L74 _public property_ `public UInt64 DestSize { get; set; }`
- L75 _public property_ `public bool UndiagnosedDiff { get; set; }`
- L76 _public property_ `public int UnreportedDiffs { get; set; }`
- L77 _public property_ `public List<Diff> Diffs { get; set; }`
- L78 _public property_ `public List<TableDiff> TableDiffs { get; set; }`
- L79 _public property_ `public bool SizeMismatch => ...`

#### class `AutomationTool.CookDiffReportHelper.Diff`  
`private sealed class Diff`  
_private; L82-90_
- L84 _public property_ `public Int64 LocalOffset { get; set; }`
- L85 _public property_ `public int Size { get; set; }`
- L86 _public property_ `public int Count { get; set; }`
- L87 _public property_ `public string ObjectName { get; set; }`
- L88 _public property_ `public string PropertyName { get; set; }`
- L89 _public property_ `public string Callstack { get; set; }`

#### class `AutomationTool.CookDiffReportHelper.TableDiff`  
`private sealed class TableDiff`  
_private; L92-96_
- L94 _public property_ `public string ItemName { get; set; }`
- L95 _public property_ `public string Detail { get; set; }`

#### class `AutomationTool.CookDiffReportHelper.PropertyNamePriorityReport`  
`private class PropertyNamePriorityReport`  
_private; L227-348_
- L245-347 _public method_ `public static void GenerateReport(DetailRoot Detail, ref int MaxItems, HashSet<Diff> UsedDiffs, int MaxFiles)`

#### class `AutomationTool.CookDiffReportHelper.PropertyNamePriorityReport.CallstackInfo`  
`class CallstackInfo`  
_private*; L229-233_
- L231 _public field_ `public string Callstack`
- L232 _public field_ `public HashSet<string> Filenames = []`

#### class `AutomationTool.CookDiffReportHelper.PropertyNamePriorityReport.PropertyNameInfo`  
`class PropertyNameInfo`  
_private*; L235-243_
- L237 _public field_ `public Dictionary<int,CallstackInfo> CallstackMap = ...`
- L237 _public field_ `public Dictionary< CallstackMap = []`
- L238 _public field_ `public HashSet<string> Filenames = []`
- L239 _public field_ `public Dictionary<string,int> ClassCounts = ...`
- L239 _public field_ `public Dictionary< ClassCounts = []`
- L240 _public field_ `public List<Diff> Diffs = []`
- L241 _public field_ `public int DiffBytes = 0`
- L242 _public field_ `public int SizeMismatches = 0`

#### class `AutomationTool.CookDiffReportHelper.CallstackPriorityReport`  
`private class CallstackPriorityReport`  
_private; L352-447_
- L364-446 _public method_ `public static void GenerateReport(DetailRoot Detail, ref int MaxItems, HashSet<Diff> UsedDiffs, int MaxFiles)`

#### class `AutomationTool.CookDiffReportHelper.CallstackPriorityReport.CallstackInfo`  
`class CallstackInfo`  
_private*; L354-362_
- L356 _public field_ `public string Callstack`
- L357 _public field_ `public HashSet<string> Filenames = []`
- L358 _public field_ `public Dictionary<string,int> ClassCounts = ...`
- L358 _public field_ `public Dictionary< ClassCounts = []`
- L359 _public field_ `public List<Diff> Diffs = []`
- L360 _public field_ `public int DiffBytes = 0`
- L361 _public field_ `public int SizeMismatches = 0`

#### class `AutomationTool.CookDiffReportHelper.PackagePriorityReport`  
`private class PackagePriorityReport`  
_private; L452-635_
- L454-509 _public method_ `public static void GenerateReport(DetailRoot Detail, ref int MaxItems, HashSet<Diff> UsedDiffs)`
- L511-514 _private method_ `private static bool SectionHasDiffs( Section Section, IEnumerable<Diff> SectionDiffs )`
- L516-578 _private method_ `private static void GenerateReport(Section Section, IEnumerable<Diff> SectionDiffs, HashSet<Diff> UsedDiffs)`
- L580-586 _private method_ `private static void PrintLinesIndented( string Indent, string Lines)`
- L589-595 _private method_ `private static int CalculateImportance(Package Package, HashSet<Diff> UsedDiffs)`
- L597-617 _private method_ `private static int CalculateImportance(Section Section, HashSet<Diff> UsedDiffs)`
- L619-629 _private method_ `private static int CalculateImportance(IEnumerable<Diff> Diffs, HashSet<Diff> UsedDiffs)`
- L631-634 _private method_ `private static int CalculateImportance(IEnumerable<TableDiff> TableDiffs)`

### `Source/Programs/AutomationTool/Scripts/CopyBuildToStagingDirectory.Automation.cs` (AutomationScripts.Automation)


#### class `AutomationScripts.Project`  
`public partial class Project : CommandUtils`  
_public; L42-7096_
- inherits: `CommandUtils`
- desc: Helper command used for cooking.
- L45 _private field_ `private static readonly object SyncLock = new object()`
- L116-174 _private method_ `private static List<string> GetHostAddresses(DeploymentContext SC)`
- L177-193 _private method_ `private static string GetBuildPatchToolExecutable()` — The path for the BuildPatchTool executable depending on host platform.
- L198-211 _private method_ `private static void EnsureBuildPatchToolExists()` — Checks the existence of the BuildPatchTool executable exists and builds it if it is missing
- L217-228 _private method_ `private static HashSet<string> GetFileExtensionsToSkipCompression(ConfigHierarchy PlatformGameConfig)` — returns a hash set containing file extensions that will not be compressed within pak files or null if no settings could be found.
- L234-245 _private method_ `private static HashSet<string> GetFileExtensionsToSkipEncryption(ConfigHierarchy PlatformGameConfig)` — returns a hash set containing file extensions that will not be encrypted within pak files or null if no settings could be found.
- L256-296 _private method_ `private static void WritePakResponseFile(string Filename, Dictionary<string, string> ResponseFile, bool Compressed, bool RehydrateAssets, EncryptionAndSigning.CryptoSettings CryptoSettings, bool bForceFullEncryption, HashSet<string> FileExtensionsToSkipCompression, HashSet<string> FileExtensionsToSkipEncryption)` — Writes a pak response file to disk
- L303-308 _private method_ `private static HashSet<string> ReadPakChunkManifest(DeploymentContext SC, string Filename)` — Loads streaming install chunk manifest file from disk
- L310-347 _private method_ `private static string GetCommonUnrealPakArguments(List<OrderFile> PakOrderFileLocations, string AdditionalOptions, EncryptionAndSigning.CryptoSettings CryptoSettings, FileReference CryptoKeysCacheFilename, List<OrderFile> SecondaryPakOrderFileLocations, bool bUnattended)`
- L349-376 _private method_ `static private string GetPakFileSpecificUnrealPakArguments(Dictionary<string, string> UnrealPakResponseFile, FileReference OutputLocation, string AdditionalOptions, bool Compressed, bool RehydrateAssets, EncryptionAndSigning.CryptoSettings CryptoSettings, String PatchSourceContentPath, string EncryptionKeyGuid, HashSet<string> FileExtensionsToSkipCompression, HashSet<string> FileExtensionsToSkipEncryption)`
- L378-399 _public method_ `static public string GetCreateSinglePakArguments( Dictionary<string, string> UnrealPakResponseFile, FileReference OutputLocation, List<OrderFile> PakOrderFileLocations, string AdditionalOptions, bool Compressed, EncryptionAndSigning.CryptoSettings CryptoSettings, FileReference CryptoKeysCacheFilename, String PatchSourceContentPath, string EncryptionKeyGuid, List<OrderFile> SecondaryPakOrderFileLocations, bool bUnattended)`
- L401-471 _private method_ `static private string GetIoStoreCommandArguments( Dictionary<string, string> UnrealPakResponseFile, string ContainerName, FileReference PakOutputLocation, DirectoryReference OptionalOutputLocation, bool bOnDemand, bool bCompressed, DirectoryReference OptionalStageLooseFileRootPath, EncryptionAndSigning.CryptoSettings CryptoSettings, string EncryptionKeyGuid, string PatchSourceContentPath, bool bGenerateDiffPatch, bool bIsDLC, HashSet<string> FileExtensionsToSkipCompression, HashSet<string> FileExtensionsToSkipEncryption)`
- L473-483 _public method_ `public static FileReference GetUnrealPakLocation()`
- L485-502 _public method_ `static public void RunUnrealPak(FileReference ProjectPath, string Arguments, string Scenario)`
- L504-524 _public method_ `static public void LogDeploymentContext(DeploymentContext SC)`
- L526-529 _private method_ `private static bool IsBulkDataExtension(string Extension)`
- L531-534 _private method_ `private static bool IsOptionalSegment(string Extension)`
- L536-539 _private method_ `private static bool IsMemoryMapped(string Extension)`
- L541-544 _private method_ `private static bool IsLocRes(string Extension)`
- L546-549 _private method_ `private static bool IsLocMeta(string Extension)`
- L551-566 _private method_ `private static string StripPackageExtension(string FullPath)`
- L568-589 _private method_ `private static string GetInternationalizationPreset(ProjectParams Params, ConfigHierarchy PlatformGameConfig, bool bMustExist = true)`
- L591-618 _public method_ `public static List<string> GetCulturesToStage(ProjectParams Params, ConfigHierarchy PlatformGameConfig, bool bMustExist = true)`
- L620-641 _public method_ `public static bool ShouldStageLocalizationTarget(DeploymentContext SC, ConfigHierarchy PlatformGameConfig, string LocalizationTarget)`
- L643-660 _public method_ `public static void StageLocalizationDataForPlugin(DeploymentContext SC, List<string> CulturesToStage, FileReference Plugin)`
- L662-690 _public method_ `public static void StageLocalizationDataForTarget(DeploymentContext SC, List<string> CulturesToStage, DirectoryReference SourceDirectory)`
- L692-704 _public method_ `public static void StageLocalizationDataForTargetsInDirectory(DeploymentContext SC, ConfigHierarchy PlatformGameConfig, List<string> CulturesToStage, DirectoryReference RootDirectory)`
- L706-744 _private method_ `private static void StageLocalizationDataForCulture(DeploymentContext SC, string CultureName, DirectoryReference SourceDirectory)`
- L746-815 _private method_ `private static void StageCookerSupportFilesFromReceipt(DeploymentContext SC)`
- L817-857 _private method_ `private static void StageAdditionalDirectoriesFromConfig(DeploymentContext SC, DirectoryReference ProjectContentRoot, StagedDirectoryReference StageContentRoot, ConfigHierarchy PlatformGameConfig, bool bUFS, string ConfigKeyName)`
- L867-923 _private method_ `private static List<FileReference> GetPluginsForContentProject(FileReference ProjectFile, List<TargetReceipt> Targets, List<DirectoryReference> AdditionalPluginDirectories)` — Figures out which plugins are enabled for a content-only plugins. This may include content-only plugins and editor plugins, which will not be in the default target manifest, since it was compiled elsewhere.
- L925-928 _private method_ `private static IoHash ReadChunkId(CbField Field)`
- L935-948 _private method_ `private static void GetZenHostNameAndPort(DeploymentContext SC, out string SocketHostNameAndPort, out string HttpHostNameAndPort)` — Returns the zen hostname and port connection information as a single string, e.g. "localhost:8558". When not using unixsockets, SocketHostName and HttpHostName are identical, but when using unixsockets they can be different. @see ZenRunContext.GetRobustHostNameAndPortStrings.
- L952-957 _private method_ `private static void GetZenHostNameAndPort(ZenServerStoreData ZenServer, out string SocketHostNameAndPort, out string HttpHostNameAndPort)` — @see GetZenHostNameAndPort(DeploymentContext SC,...)
- L964-981 _private method_ `private static bool WaitForZenServerRunning(string SocketHostNameAndPort, TimeSpan Timeout, TimeSpan PollInterval)` — Polls ZenServer's readiness (via ZenUtils.IsZenServerRunning -> /health/ready) until it reports running or the timeout elapses. Used instead of a single-shot check because under LimitProcessLifetime a ZenServer instance can be transiently unavailable while a previous instance tears down and a new one starts up.
- L989-1021 _private method_ `private static bool EnsureZenServerForStage(ProjectParams Params, string SocketHostNameAndPort, string PackageStoreFileArgName, string PackageStoreFileArgValue, int MaxAttempts, TimeSpan ReadyTimeout, TimeSpan ReadyPollInterval)` — Launches/attaches ZenServer for staging via UnrealPak -StartZenServerForStage and waits for it to become ready, retrying a bounded number of times. Tolerates the LimitProcessLifetime launch/teardown race where a launch can collide with a still-shutting-down instance. Returns true once ZenServer is ready, false if it could not be made ready within MaxAttempts.
- L1023-1184 _private method_ `private static List<ZenCookedFile> ReadZenCookedFilesFromZenServer(ProjectParams Params, DeploymentContext SC, bool bAutoLaunch, string PackageStoreFileArgName, string PackageStoreFileArgValue)`
- L1190-1195 _private method_ `private static string SubstituteOplogPath(string clientPath, string shortProjectName)` — Replace the /{engine}/ and /{project}/ placeholders in an oplog clientpath with the concrete Engine/ and project-name folders.
- L1197-1243 _private method_ `private static void LoadPackageStoreData(ProjectParams Params, DeploymentContext SC, bool bLoadCookedFiles = false)`
- L1245-1275 _private method_ `private static FileReference UpdateProjectStore(ProjectParams Params, DeploymentContext SC, FileReference SourceProjectStorePath)`
- L1277-1314 _private method_ `private static void AppendWorkspaceToProjectStore(DeploymentContext SC, EpicGames.Core.JsonObject ProjectStore)`
- L1319-1349 _private method_ `private static void MakeProjectStoreWithRemappings(DeploymentContext SC, EpicGames.Core.JsonObject ProjectStore)` — Updates project store json data with a new field containing the stage RemapDirectories, allowing StorageServer to apply these when requesting files
- L1351-1356 _private method_ `private static StagedFileType? GetStagingTypeForCookedFile(FileReference File)`
- L1358-1393 _private method_ `private static StagedFileType? GetStagingTypeForCookedFile(FileReference File, bool bStagingIsUsingPakFiles, out bool bShouldMaterializeZenFile)`
- L1395-1479 _public method_ `public static bool SetUpStagingSourceDirectories(ProjectParams Params, DeploymentContext SC)`
- L1481-1488 _private method_ `private static async Task<byte[]> ReadChunkId(HttpClient Client, ZenServerStoreData StoreData, IoHash ChunkId)`
- L1490-1520 _private method_ `private static FileReference ZenCookedFileToFileReference(ProjectParams Params, DeploymentContext SC, ZenCookedFile CookedFile, HttpClient Client, List<Task> TaskList, HashSet<string> TemporaryNonUFSFiles)`
- L1522-1546 _private method_ `private static void SynchronizeTemporaryNonUFSFiles(DeploymentContext SC, HashSet<string> TemporaryNonUFSFiles)`
- L1548-1582 _private method_ `private static List<FileReference> DiscoverCookedFiles(ProjectParams Params, DeploymentContext SC, bool bAlwaysFullyScanCookDir)`
- L1584-1611 _private method_ `private static void StageLocalizationForCookedGameFeaturePlugins(DeploymentContext SC, List<string> CulturesToStage, List<KeyValuePair<StagedFileReference, FileReference>> StagedGameFeaturePlugins, List<FileReference> CookedFiles)`
- L1613-2495 _public method_ `public static void CreateStagingManifest(ProjectParams Params, DeploymentContext SC)`
- L2497-2518 _private* method_ `static void StageTagConfigFiles(DeploymentContext SC, string StagedBaseFolder, string BasePath)`
- L2520-2532 _private* method_ `static void GetPossibleRestrictedPaths(string BasePath, List<string> RestrictedFolderNames, List<string> OutRestrictedFolders)`
- L2540-2568 _private* method_ `static void StageConfigFiles(DeploymentContext SC, DirectoryReference ConfigDir, string PlatformExtensionName)` — Stage the appropriate config files from the given input directory
- L2575-2601 _private* method_ `static void StagePlatformExtensionConfigFiles(DeploymentContext SC, string PlatformName)` — Looks for a potential PlatformExtension config directory
- L2611-2807 _private* method_ `static Nullable<bool> ShouldStageConfigFile(DeploymentContext SC, DirectoryReference ConfigDir, FileReference ConfigFile, string PlatformExtensionName)` — Determines if an individual config file should be staged
- L2816-2829 _private* method_ `static Nullable<bool> ShouldStageConfigSuffix(DeploymentContext SC, FileReference ConfigFile, string InvariantSuffix)` — Determines if the given config file suffix ("engine", "game", etc...) should be staged for the given context.
- L2831-2848 _private* method_ `static List<string> ParseInputPaths(List<string> ConfigLines)`
- L2850-2860 _private* method_ `static PluginDescriptor CreatePluginDescriptorForManifest(DeploymentContext SC, FileReference File)`
- L2862-2905 _private* method_ `static void CreatePluginManifest(DeploymentContext SC, Dictionary<StagedFileReference, FileReference> FileMapping, StagedFileType FileType, string ManifestName)`
- L2907-2933 _public method_ `public static void DumpTargetManifest(Dictionary<StagedFileReference, FileReference> Mapping, FileReference Filename, DirectoryReference StageDir, HashSet<StagedFileReference> CRCFiles)`
- L2935-2938 _private method_ `private static void CopyManifestFilesToStageDir(DeploymentContext SC, Dictionary<StagedFileReference, FileReference> Mapping, string ManifestName)`
- L2940-2943 _private method_ `private static void WriteManifestFilesToStageDir(DeploymentContext SC, Dictionary<StagedFileReference, FileReference> Mapping, string ManifestName)`
- L2945-2985 _private method_ `private static void CopyOrWriteManifestFilesToStageDir(bool bPerformCopy, DeploymentContext SC, Dictionary<StagedFileReference, FileReference> Mapping, string ManifestName)`
- L2987-3001 _public method_ `public static void DumpManifest(Dictionary<StagedFileReference, FileReference> Mapping, string Filename)`
- L3003-3011 _public method_ `public static void DumpManifest(DeploymentContext SC, string BaseFilename, bool DumpUFSFiles = true)`
- L3013-3047 _public method_ `public static void CopyUsingStagingManifest(ProjectParams Params, DeploymentContext SC)`
- L3110-3113 _private method_ `private static bool IsValidPakChunkName(string ChunkName)` — Returns true if the given pak chunk name matches the required "pakchunk " format.
- L3120-3387 _private method_ `private static List<PakFileRules> GetPakFileRules(ProjectParams Params, DeploymentContext SC)` — Reads Default/BasePakFileRules.ini and returns all PakFileRules objects that apply for this deployment
- L3394-3415 _private method_ `private static List<PakFileRules> CreateIoStoreOnDemandPakRules()` — Creates a list of pak file rules that will need to be applied in order for IoStoreOnDemand to work by forcing bulkdata into a 'OnDemand' container.
- L3417-3438 _private method_ `private static List<PakFileRules> CreateAssetTypeOnDemandPakRules(Dictionary<string, List<string>> AssetTypes)`
- L3448-3520 _private method_ `private static PakFileRules? ApplyPakFileRules( List<PakFileRules> RulesList, KeyValuePair<string, string> StagingFile, HashSet<ChunkDefinition> ModifyPakList, ConcurrentDictionary<string, ChunkDefinition> ChunkNameToDefinition, out bool bExcludeFromPaks)` — Attempts to apply the pak file rules to a specific staging file, returns false if it should be excluded
- L3522 _private* const_ `const string OptionalBulkDataFileExtension = ".uptnl"`
- L3529-3604 _private method_ `private static void CreatePakUsingStagingManifest(ProjectParams Params, DeploymentContext SC)` — Creates a pak file using staging context (single manifest)
- L3606-3647 _private method_ `private static void PrepareZenWorkspaceEnv(ProjectParams Params, DeploymentContext SC)`
- L3654-3667 _private method_ `private static void CreatePakForCrashReporter(ProjectParams Params, DeploymentContext SC)` — Creates a standalone pak file for crash reporter
- L3675-3776 _private method_ `private static Dictionary<string, string> CreatePakResponseFileFromStagingManifest(DeploymentContext SC, Dictionary<StagedFileReference, FileReference> FilesToStage)` — Creates a pak response file using stage context
- L3856-3866 _private method_ `private static bool ShouldSkipGeneratingPatch(ConfigHierarchy PlatformGameConfig, string Filename)`
- L3868-3886 _private method_ `private static string GetPakFilePostFix(bool bShouldGeneratePatch, bool bHasIterateSharedCookedBuild, ConfigHierarchy PlatformGameConfig, string Filename)`
- L3888-3952 _private method_ `private static bool CopyExistingContainer(FileReference InUtocFile, FileReference OutputLocation)`
- L3961-5275 _private method_ `private static void CreatePaks(ProjectParams Params, DeploymentContext SC, List<CreatePakParams> PakParamsList, EncryptionAndSigning.CryptoSettings CryptoSettings)` — Creates a pak file using response file.
- L5277-5374 _private method_ `private static void RunIoStore(ProjectParams Params, DeploymentContext SC, string CommandsFileName, List<OrderFile> OrderFiles, string AdditionalArgs)`
- L5381-5477 _private method_ `private static void CopyPaksFromNetwork(ProjectParams Params, DeploymentContext SC)` — Creates pak files using streaming install chunk manifests.
- L5517-5526 _private method_ `private static void AddChunkDefinition(ConcurrentDictionary<string, ChunkDefinition> ChunkSet, ChunkDefinition OriginalChunk, string ModifiedChunkName)`
- L5528-5564 _private method_ `private static byte[] GetChunkFromPackageStore(DeploymentContext SC, string Filename)`
- L5566-5592 _private method_ `private static string[] ReadAllLinesFilesystemOrPackageStore(DeploymentContext SC, string Filename)`
- L5601-5665 _private method_ `private static List<ChunkDefinition>? TryReadChunkAssignmentOp( DeploymentContext SC, EncryptionAndSigning.CryptoSettings PakCryptoSettings)` — Build ChunkDefinitions from the ChunkAssignment op cached on SC.PackageStoreData.ChunkAssignment by ReadZenCookedFilesFromZenServer. Returns null if the op is absent (cook didn't emit it, or the oplog wasn't read with cooked-files loading enabled).
- L5673-6147 _private method_ `private static void CreatePaksUsingChunkManifests(ProjectParams Params, DeploymentContext SC)` — Creates pak files using streaming install chunk manifests.
- L6149-6184 _private method_ `private static void GeneratePrimaryChunkManifest(string Dir, string Version, string PlatformStr)`
- L6186-6206 _private method_ `private static bool DoesChunkPakManifestExist(ProjectParams Params, DeploymentContext SC)`
- L6208-6211 _private method_ `private static string GetChunkPakManifestListFilename(ProjectParams Params, DeploymentContext SC)`
- L6213-6216 _private method_ `private static string GetChunkPakLayerListName()`
- L6218-6227 _private method_ `private static string GetChunkManifestPath(ProjectParams Params, DeploymentContext SC)`
- L6229-6241 _private method_ `private static bool ShouldCreateBinaryConfig(ProjectParams Params, DeploymentContext SC)`
- L6243-6269 _private method_ `private static bool ShouldCreateIoStoreContainerFiles(ProjectParams Params, DeploymentContext SC)`
- L6271-6296 _private method_ `private static bool ShouldCreatePak(ProjectParams Params, DeploymentContext SC)`
- L6298-6318 _private method_ `private static bool ShouldCreatePak(ProjectParams Params)`
- L6320-6327 _protected method_ `protected static void DeletePakFiles(string StagingDirectory)`
- L6329-6344 _protected method_ `protected static void CleanDirectoryExcludingPakFiles(DirectoryInfo StagingDirectory)`
- L6346-6403 _public method_ `public static void CleanStagingDirectory(ProjectParams Params, DeploymentContext SC)`
- L6405-6450 _public method_ `public static void ApplyStagingManifest(ProjectParams Params, DeploymentContext SC)`
- L6452-6455 _private method_ `private static DirectoryReference GetIntermediateCommandlineDir(DeploymentContext SC)`
- L6457-6521 _public method_ `public static void WriteStageCommandline(FileReference IntermediateCmdLineFile, ProjectParams Params, DeploymentContext SC)`
- L6523-6528 _private method_ `private static void WriteStageCommandline(ProjectParams Params, DeploymentContext SC)`
- L6530-6577 _private method_ `private static Dictionary<StagedFileReference, string> ReadDeployedManifest(ProjectParams Params, DeploymentContext SC, List<string> ManifestList)`
- L6579-6608 _protected method_ `protected static Dictionary<StagedFileReference, string> ReadStagedManifest(ProjectParams Params, DeploymentContext SC, string Manifest)`
- L6610-6631 _protected method_ `protected static void WriteObsoleteManifest(ProjectParams Params, DeploymentContext SC, Dictionary<StagedFileReference, string> DeployedFiles, Dictionary<StagedFileReference, string> StagedFiles, string ObsoleteManifest)`
- L6633-6672 _protected method_ `protected static void WriteDeltaManifest(ProjectParams Params, DeploymentContext SC, Dictionary<StagedFileReference, string> DeployedFiles, Dictionary<StagedFileReference, string> StagedFiles, string DeltaManifest)`
- L6675-6963 _public method_ `public static List<DeploymentContext> CreateDeploymentContext(ProjectParams Params, bool InDedicatedServer, bool DoCleanStage = false)`
- L6964-6984 _private method_ `private static void SetupCustomStageCopyHandler(ProjectParams Params, DeploymentContext SC)`
- L6990-7006 _private method_ `private static void RunPreStagingCommandlets(ProjectParams Params, DeploymentContext DeployContext)` — Runs OplogChunkAssigner (if requested) and any additional commandlets before staging manifests are created. Both read from cook output rather than staging output, so they can safely run before CreateStagingManifest.
- L7008-7095 _public method_ `public static void CopyBuildToStagingDirectory(ProjectParams Params)`

#### struct `AutomationScripts.Project.OrderFile`  
`public struct OrderFile : IComparable<OrderFile>`  
_public; L47-106_
- inherits: `IComparable<OrderFile>`
- L57-84 _public ctor_ `public OrderFile(FileReference FileRef, OrderFileType InType, int SpecIndex, int InPriority)`
- L86-94 _public method_ `public int CompareTo(OrderFile Other)`
- L98 _public field_ `public int AppendOrder`
- L99 _public field_ `public int OrderSpecIndex`
- L101 _public field_ `public int Priority`
- L103 _public field_ `public OrderFileType OrderType`
- L105 _public field_ `public FileReference File`

#### enum `AutomationScripts.Project.OrderFile.OrderFileType`  
`public enum OrderFileType`  
_public; L49-55_
- L51 _public* enumerator_ `Custom`
- L52 _public* enumerator_ `Game`
- L53 _public* enumerator_ `Cooker`
- L54 _public* enumerator_ `Editor`

#### struct `AutomationScripts.Project.OrderFileSpec`  
`struct OrderFileSpec`  
_private*; L108-114_
- L110 _public field_ `public string FileNamePattern`
- L111 _public field_ `public OrderFile.OrderFileType OrderType`
- L112 _public field_ `public bool Required`
- L113 _public field_ `public int Priority`

#### struct `AutomationScripts.Project.PakFileRules`  
`private struct PakFileRules`  
_private; L3050-3105_
- L3053 _public field_ `public string Name`
- L3056 _public field_ `public FileFilter Filter`
- L3059 _public field_ `public HashSet<string> ExactFileMatches`
- L3062 _public field_ `public bool bUseExactFilePathMatch`
- L3065 _public field_ `public bool bExcludeFromPaks`
- L3068 _public field_ `public bool bOverrideChunkManifest`
- L3071 _public field_ `public bool bDisabled`
- L3074 _public field_ `public List<string> OverridePaks`
- L3077 _public field_ `public bool bOnDemand`
- L3079 _public field_ `public bool bStageLoose`
- L3082 _public field_ `public string EncryptionKeyGuid`
- L3085 _public field_ `public List<Regex> OnDemandAllowedChunkFilters`
- L3088 _public field_ `public bool bGenerateNewChunk`
- L3091 _public field_ `public List<Regex> NewChunkAllowedChunkFilters`
- L3094 _public field_ `public string GeneratedChunkName`
- L3097-3104 _public method_ `public static bool IsMatch(PakFileRules PakRules, KeyValuePair<string, string> StagingFile)`

#### class `AutomationScripts.Project.CreatePakParams`  
`class CreatePakParams`  
_private*; L3782-3854_
- attrs: `[DebuggerDisplay("PakName")]`
- desc: Parameter class for CreatePaks(). Each instance stores information about a pak file to be created.
- L3787 _public field_ `public string PakName` — Path to the base output file for this pak file
- L3792 _public field_ `public Dictionary<string, string> UnrealPakResponseFile` — Map of files within the pak file to their source file on disk
- L3792 _public field_ `public Dictionary< UnrealPakResponseFile` — Map of files within the pak file to their source file on disk
- L3797 _public field_ `public bool bCompressed` — Whether to enable compression
- L3802 _public field_ `public bool bRehydrateAssets` — Whether to rehydrate the assets when creating the pak file or not
- L3807 _public field_ `public bool bAllowPerChunkCompression` — Allow the per-chunk bCompressed flag to be used instead of the global parameter
- L3812 _public field_ `public bool bOnDemand` — Whether this pak file is for content-on-demand content delivery or not
- L3817 _public field_ `public bool bStageLoose` — Whether this pak file is to copy the source files as loose files
- L3822 _public field_ `public string EncryptionKeyGuid` — GUID of the encryption key for this pak file
- L3835-3853 _public ctor_ `public CreatePakParams( string PakName, Dictionary<string, string> UnrealPakResponseFile, bool bCompressed, bool RehydrateAssets, string EncryptionKeyGuid, bool bOnDemand = false, bool bStageLoose = false, bool bAllowPerChunkCompression = false)` — Constructor

#### class `AutomationScripts.Project.ChunkDefinition`  
`private class ChunkDefinition`  
_private; L5480-5515_
- L5482-5491 _public ctor_ `public ChunkDefinition(string InChunkName)`
- L5494 _public field_ `public string ChunkName`
- L5497 _public field_ `public ConcurrentDictionary<string, string> ResponseFile`
- L5497 _public field_ `public ConcurrentDictionary< ResponseFile`
- L5500 _public field_ `public HashSet<string> Manifest`
- L5503 _public field_ `public bool bCompressed`
- L5504 _public field_ `public string EncryptionKeyGuid`
- L5505 _public field_ `public string RequestedEncryptionKeyGuid`
- L5508 _public field_ `public bool bAllowPerChunkCompression`
- L5511 _public field_ `public bool bOnDemand`
- L5514 _public field_ `public bool bStageLoose`

### `Source/Programs/AutomationTool/Scripts/CopySharedCookedBuild.Automation.cs` (AutomationScripts.Automation)


#### class `CopySharedCookedBuild`  
`class CopySharedCookedBuild : BuildCommand`  
_internal*; L12-143_
- inherits: `BuildCommand`
- L18-59 _private* property_ `FileReference ProjectFile { get; }` — attrs: `[Help("Copies the current shared cooked build from the network to the local PC")] [RequireP4] [DoesNotNeedP4CL]`
- L61-142 _public method_ `public override void ExecuteBuild()`

### `Source/Programs/AutomationTool/Scripts/CreateComponentZips.cs` (AutomationScripts.Automation)


#### class `Rocket.Automation.CreateComponentZips`  
`public class CreateComponentZips : BuildCommand`  
_public; L17-95_
- inherits: `BuildCommand`
- L25-76 _public method_ `public override void ExecuteBuild()`
- L78-94 _private* method_ `static void CreateZip(DirectoryReference SourceDir, List<FileInfo> SourceFiles, Predicate<string> Predicate, FileReference OutputFile)`

#### class `Rocket.Automation.CreateComponentZips.Category`  
`class Category`  
_private*; L19-23_
- L21 _public field_ `public string Name`
- L22 _public field_ `public FileFilter Filter = new FileFilter()`

### `Source/Programs/AutomationTool/Scripts/CreatePlatformExtension.cs` (AutomationScripts.Automation)


#### class `CreatePlatformExtension`  
`public class CreatePlatformExtension : BuildCommand`  
_public; L23-862_
- attrs: `[Help("Create stub code for platform extension")] [Help("Source", "Path to source .uplugin, .build.cs or .target.cs, or a source folder to search")] [Help("Platform", "Platform(s) or Platform Groups to generate for")] [Help("Project", "Optional path to project (only required if not creating code for Engine modules/plugins")] [Help("SkipPluginModules", "Do not generate platform extension module fil`
- inherits: `BuildCommand`
- L25 _private* field_ `readonly List<ModuleHostType> ModuleTypeDenyList = new List<ModuleHostType> { ModuleHostType.Developer, ModuleHostType.Editor, ModuleHostType.EditorNoCommandlet, ModuleHostType.EditorAndProgram, ModuleHostType.Program, }`
- L34 _private* field_ `ConfigHierarchy GameIni`
- L35 _private* field_ `DirectoryReference ProjectDir`
- L36 _private* field_ `DirectoryReference SourceDir`
- L37 _public field_ `public List<string> NewFiles = new List<string>()`
- L38 _public field_ `public List<string> ModifiedFiles = new List<string>()`
- L39 _public field_ `public List<string> WritableFiles = new List<string>()`
- L41 _private* field_ `string[] Platforms`
- L42 _public field_ `public bool bSkipPluginModules = false`
- L43 _public field_ `public bool bOverwriteExistingFile = false`
- L44 _public field_ `public bool bIsTest = false`
- L45 _public field_ `public bool bAllowPlatformExtensionsAsParents = false`
- L46 _public field_ `public int CL = -1`
- L48-179 _public method_ `public override void ExecuteBuild()`
- L185-235 _public method_ `public void GeneratePlatformExtension( string InProject, string InSource, string[] InPlatforms )` — Generates platform extensions from the given source
- L242-438 _private method_ `private void GeneratePluginPlatformExtension(FileReference PluginPath)` — Create the platform extension plugin files of the given plugin, for the given platforms
- L444-540 _private method_ `private void GenerateModulePlatformExtension(FileReference ModulePath, string[] PlatformNames)` — Creates the platform extension child class files of the given module, for the given platforms
- L547-561 _private method_ `private void GeneratePlatformExtensionFromFile(FileReference Source)` — Generates platform extension files based on the given source file name
- L575-603 _private method_ `private bool ShouldCreateChildReferenceForModule( ModuleDescriptor ModuleDesc, bool bHasPlatform, UnrealTargetPlatform Platform )` — Determines whether we should attempt to add a child module reference for the given plugin module
- L612-634 _private method_ `private bool ShouldCreateChildReferenceForDependentPlugin( PluginReferenceDescriptor PluginDesc, bool bHasPlatform, UnrealTargetPlatform Platform )` — Determines whether we should attempt to add this dependent plugin module to the child plugin references
- L641-670 _private method_ `private string MakePlatformExtensionPathFromSource( DirectoryReference RootDir, DirectoryReference SourceDir, string PlatformName, string Filename )` — Generates the final platform extension file path for the given source directory, platform and filename
- L676-693 _private method_ `private string GetPlatformExtensionBaseNameFromPath( string FileName )` — Given a full path to a plugin or module file, returns the raw file name - trimming off any _[platform] suffix too
- L700-704 _private method_ `private string LoadTemplate( string FileName )` — Load the given file from the engine templates folder
- L711-724 _private method_ `private string MakeCopyrightLine()` — Look up the project/engine specific copyright string
- L731-747 _private method_ `private bool HasChangelist()` — Returns whether there is a valid changelist for adding files to
- L753-766 _private method_ `private void AddNewFile( string NewFile )` — Adds the given file to the list of new files, optionally adding to the current changelist if applicable
- L773-805 _private method_ `private bool EditFile( string ExistingFile )` — Attempts to edit the given file, optionally checking it out if applicable. If this is just a test, read-only files are backed up and made writable
- L814-817 _private method_ `private bool PlatformArrayContainsPlatform( string[] PlatformNames, UnrealTargetPlatform Platform )` — Heler function to see if the given platform name array contains the given platform
- L823-860 _private method_ `private string[] VerifyPlatforms(string[] Platforms)` — Returns a list of validated and case-corrected platform and platform groups

### `Source/Programs/AutomationTool/Scripts/CryptoKeys.Automation.cs` (AutomationScripts.Automation)


#### class `AutomationTool.CryptoKeys`  
`class CryptoKeys : BuildCommand`  
_internal*; L15-129_
- inherits: `BuildCommand`
- L17-113 _public method_ `public override void ExecuteBuild()`
- L115 _public property_ `public bool MakeNoRedist { get; }`
- L117 _private field_ `private FileReference ProjectFullPath`
- L118-128 _public property_ `public virtual FileReference ProjectPath { get; }`

### `Source/Programs/AutomationTool/Scripts/DedupeAutomationScripts.Automation.cs` (AutomationScripts.Automation)


#### class `AutomationTool.DedupeAutomationScripts`  
`class DedupeAutomationScripts : BuildCommand`  
_internal*; L19-96_
- attrs: `[Help("Removes duplicate binaries in UAT script directories that exist in AutomationTool or AutomationUtils")]`
- inherits: `BuildCommand`
- desc: Commandlet to remove duplicate files in the UAT script directories
- L22-95 _public method_ `public override void ExecuteBuild()` — (inheritdoc)

### `Source/Programs/AutomationTool/Scripts/DeployCommand.Automation.cs` (AutomationScripts.Automation)


#### class `AutomationScripts.Project`  
`public partial class Project : CommandUtils`  
_public; L14-84_
- inherits: `CommandUtils`
- L16-83 _public method_ `public static void Deploy(ProjectParams Params)`

### `Source/Programs/AutomationTool/Scripts/DiffCDOFolders.cs` (AutomationScripts.Automation)


#### class `AutomationTool.DiffCDOFolders`  
`public class DiffCDOFolders : BuildCommand`  
_public; L12-101_
- inherits: `BuildCommand`
- L14-91 _public method_ `public override void ExecuteBuild()`
- L93-100 _private method_ `private void GenerateCDOFolders(FileReference unrealProjectPath, string firstRunFolderName, string secondRunFolderName)`

### `Source/Programs/AutomationTool/Scripts/ExportTimerStatisticsFromUtrace.cs` (AutomationScripts.Automation)


#### class `ExportTimerStatisticsFromUtrace.Automation.ExportTimerStatisticsFromUtrace`  
`class ExportTimerStatisticsFromUtrace : BuildCommand`  
_internal*; L23-83_
- attrs: `[Help("Runs UnrealInsights to export timers from a utrace file to CSV file.")] [ParamHelp("TraceFile", "Input UnrealInsights .utrace file to open", ParamType = typeof(string), Required = true)] [ParamHelp("CSVFile", "Output CSV file to write", ParamType = typeof(string), Required = true)] [ParamHelp("Threads", "Threads to export", ParamType = typeof(string), Required = false)] [ParamHelp("TimerReg`
- inherits: `BuildCommand`
- L25-53 _public method_ `public override void ExecuteBuild()`
- L56-82 _protected method_ `protected static int RunInsights(string Args, UnrealTargetConfiguration InConfiguration = UnrealTargetConfiguration.Development)`

### `Source/Programs/AutomationTool/Scripts/ExtractPaks.Automation.cs` (AutomationScripts.Automation)


#### class `ExtractPaks`  
`public class ExtractPaks : BuildCommand`  
_public; L15-73_
- inherits: `BuildCommand`
- L17-72 _public method_ `public override void ExecuteBuild()`

### `Source/Programs/AutomationTool/Scripts/FinalizeInstalledBuild.cs` (AutomationScripts.Automation)


#### class `AutomationTool.FinalizeInstalledBuild`  
`class FinalizeInstalledBuild : BuildCommand`  
_internal*; L24-201_
- attrs: `[Help("Command to perform additional steps to prepare an installed build.")] [Help("OutputDir=<RootDirectory>", "Root Directory of the installed build data (required)")] [Help("ContentOnlyPlatforms=<PlatformNameList>", "List of platforms that should be marked as only supporting content projects (optional)")] [Help("Platforms=<PlatformList>)", "List of platforms to add")] [Help("<Platform>Architect`
- inherits: `BuildCommand`
- desc: Commandlet to finalize the creation of an installed build - creating an InstalledBuild.txt file and writing out installed platform entries for all platforms/configurations where a UnrealGame .target file can be found
- L29-158 _public method_ `public override void ExecuteBuild()` — Entry point for the commandlet
- L165-176 _private* method_ `List<UnrealTargetPlatform> ParsePlatformsParamValue(string Name)` — Parse an argument containing a list of platforms
- L183-200 _private method_ `private UnrealArchitectures GetArchitecturesForPlatform(UnrealTargetPlatform Platform)` — Look for a platform's architecture(s) on the commandline, and if not, then ask the platform's config for active architectures

### `Source/Programs/AutomationTool/Scripts/FixPerforceCase.cs` (AutomationScripts.Automation)


#### class `AutomationTool.FixPerforceCase`  
`class FixPerforceCase : BuildCommand`  
_internal*; L16-119_
- attrs: `[RequireP4] [DoesNotNeedP4CL] [Help("Fixes the case of files on a case-insensitive Perforce server by removing and re-adding them.")] [Help("Files", "Pattern for files to match. Should be a full depot path with the correct case. May end with a wildcard.")]`
- inherits: `BuildCommand`
- L18 _private* const_ `const string BoilerplateText = "\n\n#rb none\n#rnx\n#preflight skip\n#jira none\n#submittool FixPerforceCase\n#okforgithub ignore"`
- L23-118 _public method_ `public override void ExecuteBuild()` — Main entry point for the command

### `Source/Programs/AutomationTool/Scripts/FixupRedirects.Automation.cs` (AutomationScripts.Automation)


#### class `FixupRedirects`  
`class FixupRedirects : BuildCommand`  
_internal*; L10-20_
- inherits: `BuildCommand`
- L12-19 _public method_ `public override void ExecuteBuild()`

### `Source/Programs/AutomationTool/Scripts/GenerateBuildStatsCommand.cs` (AutomationScripts.Automation)


#### class `AutomationTool.GenerateBuildStats`  
`public class GenerateBuildStats : BuildCommand`  
_public; L23-364_
- attrs: `[Help("Generates file size statistics for a directory tree.")] [ParamHelp("RootDir", "<path> \t\t\t\t Base directory for scanning", ParamType = typeof(string), Required = false)] [ParamHelp("OutputPath", "<path> \t\t\t\t Path where the stats file will be saved", ParamType = typeof(string), Required = false)] [ParamHelp("OutputFormat", "<csv or json> \t\t\t Output format for the stats file", ParamT`
- inherits: `BuildCommand`
- L25-50 _public method_ `public override void ExecuteBuild()`
- L52-104 _private method_ `private BuildStatsOptions ParseCommandLineParam()`
- L106-115 _private method_ `private static void LogBuildStatsOptions(BuildStatsOptions Options)`
- L117-128 _private method_ `private static void VerifyOrCreateDirectory(string OutputDir)`
- L130-165 _private method_ `private static BuildStatsDocument GenerateBuildStatsDocument(BuildStatsOptions Options)`
- L167-190 _private method_ `private static void SaveStats(BuildStatsDocument BuildStatsDocument, string OutputPath, OutputFormat OutputFormat, SmallFileHandlingMode Mode)`
- L193-216 _private method_ `private static BuildStatsDocument ProcessFiles(IEnumerable<FileEntity> Files, long MinFileSizeBytes, SmallFileHandlingMode Mode)`
- L218-222 _private method_ `private static string GenerateAggregatedStatsFilePath(string MainStatFilePath)`
- L224-235 _private method_ `private string[] ParsePathsList(string RawPatterns)`
- L237-247 _private method_ `private static OutputFormat ParseOutputFormat(string Value)`
- L249-260 _private method_ `private static SmallFileHandlingMode ParseSmallFileHandlingMode(string Value)`
- L262-280 _private method_ `private static string GetOutputDir(string OutputPathParam)`
- L282-290 _private method_ `private static string GetFilename(string OutputPathParam)`

#### interface `AutomationTool.GenerateBuildStats.IStatsWriter`  
`private interface IStatsWriter`  
_private; L293-298_
- L295 _public* method_ `void Write( IEnumerable<FileEntity> Files, string OutputFilePath)`

#### class `AutomationTool.GenerateBuildStats.JsonStatsWriter`  
`private class JsonStatsWriter : IStatsWriter`  
_private; L300-311_
- inherits: `IStatsWriter`
- L302-310 _public method_ `public void Write(IEnumerable<FileEntity> Files, string OutputFilePath)`

#### class `AutomationTool.GenerateBuildStats.CsvStatsWriter`  
`private class CsvStatsWriter : IStatsWriter`  
_private; L313-324_
- inherits: `IStatsWriter`
- L315-323 _public method_ `public void Write(IEnumerable<FileEntity> Files, string OutputFilePath)`

#### enum `AutomationTool.GenerateBuildStats.SmallFileHandlingMode`  
`private enum SmallFileHandlingMode`  
_private; L327-332_
- L329 _public* enumerator_ `Include`
- L330 _public* enumerator_ `Ignore`
- L331 _public* enumerator_ `Aggregate`

#### enum `AutomationTool.GenerateBuildStats.OutputFormat`  
`private enum OutputFormat`  
_private; L334-338_
- L336 _public* enumerator_ `Csv`
- L337 _public* enumerator_ `Json`

#### class `AutomationTool.GenerateBuildStats.FileEntity`  
`private class FileEntity`  
_private; L340-345_
- L342 _public property_ `public string RelativePath { get; init; }`
- L343 _public property_ `public long Bytes { get; init; }`
- L344 _public property_ `public string Extension { get; init; }`

#### class `AutomationTool.GenerateBuildStats.BuildStatsOptions`  
`private class BuildStatsOptions`  
_private; L347-357_
- L349 _public property_ `public string RootDir { get; init; }`
- L350 _public property_ `public string OutputDir { get; init; }`
- L351 _public property_ `public string Filename { get; init; }`
- L352 _public property_ `public OutputFormat OutputFormat { get; init; }`
- L353 _public property_ `public string[] Include { get; init; }`
- L354 _public property_ `public string[] Exclude { get; init; }`
- L355 _public property_ `public long MinFileSizeBytes { get; init; }`
- L356 _public property_ `public SmallFileHandlingMode SmallFileHandlingMode { get; init; }`

#### class `AutomationTool.GenerateBuildStats.BuildStatsDocument`  
`private class BuildStatsDocument`  
_private; L359-363_
- L361 _public property_ `public IEnumerable<FileEntity> Files { get; init; }`
- L362 _public property_ `public IEnumerable<FileEntity> SmallAggregatedFiles { get; init; }`

### `Source/Programs/AutomationTool/Scripts/GenerateDSYM.Automation.cs` (AutomationScripts.Automation)


#### class `GenerateDSYM`  
`public class GenerateDSYM : BuildCommand`  
_public; L15-147_
- attrs: `[Help(@"Generates IOS debug symbols for a remote project.")] [Help("project=Name", @"Project name (required), i.e: -project=QAGame")] [Help("config=Configuration", @"Project configuration (required), i.e: -config=Development")]`
- inherits: `BuildCommand`
- L17-146 _public method_ `public override void ExecuteBuild()`

### `Source/Programs/AutomationTool/Scripts/GeneratePlatformReport.cs` (AutomationScripts.Automation)


#### class `AutomationTool.GeneratePlatformReport`  
`class GeneratePlatformReport : BuildCommand`  
_internal*; L20-258_
- attrs: `[Help("Generates a report about all platforms and their configuration settings.")] [Help("Platforms", "Limit report to these platforms. e.g. Windows+iOS. Default is all platforms")] [Help("CsvOut", "<filename> - Generate a CSV file instead of an html file")] [Help("DDPISection", "ShaderPlatform,DataDrivenPlatformInfo - which config section to check")] [Help("UseFieldNames", "Use field names instea`
- inherits: `BuildCommand`
- L36-79 _public method_ `public override void ExecuteBuild()`
- L81-162 _private method_ `private PlatformReport GenerateDDPIReport(string[] Platforms, string DDPISection)`
- L167-199 _private method_ `private string MakeFriendlyName( string PropertyName )`
- L203-212 _private method_ `private void WriteReportToCSV(PlatformReport Report, string CSVFile)`
- L214-257 _private method_ `private void WriteReportToHTML(PlatformReport Report, string HTMLFile)`

#### class `AutomationTool.GeneratePlatformReport.PlatformReportRow`  
`class PlatformReportRow`  
_private*; L24-27_
- L26 _public field_ `public List<string> Columns = new List<string>()`

#### class `AutomationTool.GeneratePlatformReport.PlatformReport`  
`class PlatformReport`  
_private*; L29-34_
- L31 _public field_ `public string ReportName = ""`
- L32 _public field_ `public string ReportDescription = ""`
- L33 _public field_ `public List<PlatformReportRow> Rows = new List<PlatformReportRow>()`

### `Source/Programs/AutomationTool/Scripts/GetFileCommand.Automation.cs` (AutomationScripts.Automation)


#### class `AutomationScripts.Project`  
`public partial class Project : CommandUtils`  
_public; L15-42_
- inherits: `CommandUtils`
- L17-41 _public method_ `public static void GetFile(ProjectParams Params)`

### `Source/Programs/AutomationTool/Scripts/IPhonePackager.Automation.cs` (AutomationScripts.Automation)


#### class `IPhonePackager`  
`class IPhonePackager : BuildCommand`  
_internal*; L13-57_
- attrs: `[Help("UAT command to call into the integrated IPhonePackager code")]`
- inherits: `BuildCommand`
- L15-56 _public method_ `public override void ExecuteBuild()`

### `Source/Programs/AutomationTool/Scripts/LaunchMultiServer.Automation.cs` (AutomationScripts.Automation)


#### class `AutomationTool.ProcessDebugger`  
`class ProcessDebugger`  
_internal*; L21-229_
- L25 _public method_ `public static extern int CreateBindCtx(int reserved, out IBindCtx ppbc)` — attrs: `[SupportedOSPlatform("windows")] [DllImport("ole32.dll")]`
- L29 _public method_ `public static extern int GetRunningObjectTable(int reserved, out IRunningObjectTable prot)` — attrs: `[SupportedOSPlatform("windows")] [DllImport("ole32.dll")]`
- L31-45 _public method_ `public static void DebugProcess(int ProcessID, BuildCommand Command, ProjectParams Params)`
- L47-93 _public method_ `public static void DebugProcessWithRider(int ProcessId, FileReference ProjectPath, bool bUsesUProject)`
- L95-110 _public method_ `public static void DebugProcessWithVisualStudio(int ProcessID)`
- L113-146 _private method_ `private static EnvDTE._DTE GetVisualStudioInstance()` — attrs: `[SupportedOSPlatform("windows")]`
- L149-190 _private method_ `private static void AttachVisualStudioToPID(EnvDTE._DTE visualStudioInstance, int processID)` — attrs: `[SupportedOSPlatform("windows")]`
- L193-209 _private method_ `private static bool IsDebuggerAttached(EnvDTE._DTE VisualStudio, string processID)` — attrs: `[SupportedOSPlatform("windows")]`
- L212-228 _private method_ `private static bool IsDebuggerAttachedToPID(EnvDTE._DTE VisualStudio, int processID)` — attrs: `[SupportedOSPlatform("windows")]`

#### class `AutomationTool.LaunchMultiServer`  
`public class LaunchMultiServer : BuildCommand, IProjectParamsHelpers`  
_public; L241-834_
- attrs: `[Help(@"Launches multiple server processes for a project using the MultiServerReplication plugin. Example running 2 hosts locally with a single proxy server & client: -cook -notimeouts -numservers=2 -client=proxy -proxyclientcount=1 -proxycycleprimary Example running 4 clients locally connecting to single proxy server w/ a non-local cluster of 3: -cook -notimeouts -client=proxy -proxyclientcount=4`
- inherits: `BuildCommand, IProjectParamsHelpers`
- L244 _public field_ `public int BaseGameListenPort = 9000`
- L245 _public field_ `public int ProxyServerBasePort = -1`
- L248 _private field_ `private int NextStatsPort = 10100`
- L251 _public field_ `public string CustomConfig = ""` — attrs: `[CommandLine, Help("CustomConfig=<Section>", "Read a different section of the Project's GameConfig for default values")]`
- L254 _public field_ `public int NumServers = -1` — attrs: `[CommandLine, Help("NumServers=##", "Set the fleet size of servers (default: 2)")]`
- L257 _public field_ `public List<string> NonLocalServers = new List<string>()` — attrs: `[CommandLine(ListSeparator = ','), Help("NonLocalServers=Address1:Port1,Address2:Port2,etc.", "Specify servers that are not hosted locally but belong to the same fleet")]`
- L260 _public field_ `public List<string> ClientType = new List<string>()` — attrs: `[CommandLine("-Client", ListSeparator = ','), Help("Client=<Type>", "Specify the client type to connect with (proxy or direct or proxy,direct)")]`
- L263 _public field_ `public int DirectClientCount = 0` — attrs: `[CommandLine, Help("DirectClientCount=##", "Specify how many clients to launch in client=direct mode. If 0 (default), will launch one for each server.")]`
- L266 _public field_ `public int BotCount = 0` — attrs: `[CommandLine, Help("BotCount=##", "Specify how many client bots to launch. Client bots are launched with -bot it is up to the game to specify the implementation.")]`
- L269 _public field_ `public int ProxyServerCount = 1` — attrs: `[CommandLine, Help("ProxyServerCount=##", "Specify how many proxy servers to launch in client=proxy mode")]`
- L272 _public field_ `public int ProxyClientCount = 1` — attrs: `[CommandLine, Help("ProxyClientCount=##", "Specify how many clients to launch PER SERVER in client=proxy mode")]`
- L275 _public field_ `public int ProxyBotCount = 0` — attrs: `[CommandLine, Help("ProxyBotCount=##", "Specify how many bots to launch PER SERVER in client=proxy mode. Prefer -BotCount=XX.")]`
- L278 _public field_ `public string ProxyClientPrimary = ""` — attrs: `[CommandLine, Help("ProxyClientPrimary=##", "Specify which game server to prefer as the initial proxy connection, as an integer or the string \"random\"")]`
- L281 _public field_ `public bool ProxyCyclePrimary = false` — attrs: `[CommandLine, Help("ProxyCyclePrimary", "Specify that each subsequent proxy client should choose a different server")]`
- L284 _public field_ `public bool NoTimeouts = false` — attrs: `[CommandLine, Help("NoTimeouts", "Disable timeouts (recommended for debugging)")]`
- L287 _public field_ `public bool NoConsole = false` — attrs: `[CommandLine, Help("NoConsole", "Disable launching a console (not recommended, but may improve performance)")]`
- L290 _public field_ `public bool NoNewConsole = false` — attrs: `[CommandLine, Help("NoNewConsole", "Disable launching the new style console")]`
- L293 _public field_ `public bool AttachToServers = false` — attrs: `[CommandLine, Help("AttachToServers", "Force Visual Studio to attach to the servers when launched (requires VS be launched or it will hang)")]`
- L296 _public field_ `public bool AttachToProxies = false` — attrs: `[CommandLine, Help("AttachToProxies", "Force Visual Studio to attach to the proxies when launched (requires VS be launched or it will hang)")]`
- L299 _public field_ `public bool AttachToClients = false` — attrs: `[CommandLine, Help("AttachToClients", "Force Visual Studio to attach to the clients when launched (requires VS be launched or it will hang)")]`
- L302 _public field_ `public string CommonArgs = ""` — attrs: `[CommandLine, Help("CommonArgs", "Specify arguments that are run by all processes")]`
- L305 _public field_ `public bool EnableStatsPort = false` — attrs: `[CommandLine, Help("EnableStatsPort", "Enable the -statsPort argument on all launched processes")]`
- L308 _public field_ `public bool Matchmake = false` — attrs: `[CommandLine, Help("Matchmake", "Project will use a matchmaking service to connect servers instead of passing the -MultiServerPeers and -ProxyGameServers options to servers.")]`
- L311 _private* field_ `bool bParsedCommandLineArguments = false`
- L313-318 _public method_ `public string GenerateRandomSessionString(int Length)`
- L329-337 _protected method_ `protected virtual void ParseCommandLineArguments()`
- L342-444 _public method_ `public override ExitCode Execute()` — The entry point for the build command
- L450-482 _protected method_ `protected void ReadConfiguration()` — Reads the configuration from the CustomConfig specified. If no CustomConfig was specified, then rely solely on the command-line parameters. The command-line parameters should always take precedence.
- L490-500 _private* method_ `string[] GenerateLocalServerAddressRange(int NumLocalServers, int BasePort)` — Given the number of local servers and the base port, generate the array of address:port for that range of ports
- L509-551 _protected method_ `virtual protected string[] StartProcessesForDedicatedServers(int NumLocalServers, string[] NonLocalServers, string AdditionalServerArguments)` — Starts all of the server processes that should execute on the local host.
- L561-604 _protected method_ `virtual protected void StartProcessesForClients(ProcessLaunchType ClientType, string[] GameServerAddresses, string AdditionalClientArguments, int ClientsPerServer = 1, int MaxClientCount = 0)` — Start the Client processes
- L606-652 _protected method_ `virtual protected void StartProcessesForProxyServer(string[] LocalProxyServerAddresses, string[] AllGameServerAddresses, string AdditionalProxyArguments)`
- L662-734 _protected method_ `protected void ExecuteApp(ProcessLaunchType LaunchType, string AppTitle, string AdditionalArguments)` — Execute the specified LaunchType app with a particular window AppTitle and arguments
- L744-782 _protected method_ `protected bool ParseAddressAndPortRange(out string IpAddress, out int StartPort, out int EndPort, string AddressToParse)` — Helper function allows us to break-out a potential input of "address", "address:port", or "address:startPort-endPort".
- L789-802 _protected method_ `protected int CountServers(string[] ServerAddresses)` — Counts the number of servers specified in the passed-in string array. We account for port ranges.
- L809-814 _protected method_ `protected bool IsAttachingDebugger(ProcessLaunchType LaunchType)` — Are we requesting a debugger be attached to this particular process?
- L816 _private field_ `private FileReference ProjectFullPath`
- L817-833 _public property_ `public virtual FileReference ProjectPath { get; }`

#### enum `AutomationTool.LaunchMultiServer.ProcessLaunchType`  
`protected enum ProcessLaunchType`  
_protected; L320-327_
- L322 _public* enumerator_ `Server`
- L323 _public* enumerator_ `DirectClient`
- L324 _public* enumerator_ `ProxyServer`
- L325 _public* enumerator_ `ProxyClient`
- L326 _public* enumerator_ `BotClient`

### `Source/Programs/AutomationTool/Scripts/ListMobileDevices.Automation.cs` (AutomationScripts.Automation)


#### class `AutomationScripts.Automation.ListMobileDevices`  
`public class ListMobileDevices : BuildCommand`  
_public; L11-53_
- inherits: `BuildCommand`
- L13-33 _public method_ `public override void ExecuteBuild()`
- L35-52 _private method_ `private static void GetConnectedDevices(ProjectParams Params, Platform TargetPlatform)`

### `Source/Programs/AutomationTool/Scripts/ListThirdPartySoftware.Automation.cs` (AutomationScripts.Automation)


#### class `ListThirdPartySoftware`  
`class ListThirdPartySoftware : BuildCommand`  
_internal*; L18-151_
- attrs: `[Help("Lists TPS files associated with any source used to build a specified target(s). Grabs TPS files associated with source modules, content, and engine shaders.")] [Help("Target", "One or more UBT command lines to enumerate associated TPS files for (eg. UnrealGame Win64 Development).")]`
- inherits: `BuildCommand`
- L20-150 _public method_ `public override void ExecuteBuild()`

### `Source/Programs/AutomationTool/Scripts/Localisation.Automation.cs` (AutomationScripts.Automation)


#### class `Localize`  
`class Localize : BuildCommand`  
_internal*; L38-1347_
- attrs: `[Help("Updates the external localization data using the arguments provided.")] [Help("UEProjectRoot", "Optional root-path to the project we're gathering for (defaults to CmdEnv.LocalRoot if unset).")] [Help("UEProjectDirectory", "Sub-path to the project we're gathering for (relative to UEProjectRoot).")] [Help("UEProjectName", "Optional name of the project we're gathering for (should match its .up`
- inherits: `BuildCommand`
- L211 _private field_ `private string UEProjectRoot = CmdEnv.LocalRoot`
- L212 _private field_ `private string UEProjectDirectory = ""`
- L213 _private field_ `private string UEProjectName = ""`
- L214 _private field_ `private List<string> LocalizationProjectNames = new()`
- L215 _private field_ `private string LocalizationProviderName = ""`
- L216 _private field_ `private List<string> LocalizationStepNames = new()`
- L217 _private field_ `private bool bShouldGatherPlugins = false`
- L218 _private field_ `private bool bShouldEnableIncludedPlugins = false`
- L219 _private field_ `private List<string> IncludePlugins = new()`
- L220 _private field_ `private List<string> ExcludePlugins = new()`
- L221 _private field_ `private bool bShouldGatherPlatforms = false`
- L222 _private field_ `private string AdditionalCommandletArguments = ""`
- L223 _private field_ `private List<LocalizationConfigFile> TemplateLocalizationConfigFiles = new List<LocalizationConfigFile>()`
- L224 _private field_ `private bool bEnableParallelGather = false`
- L225 _private field_ `private bool bIsRunningInPreview = false`
- L226 _private field_ `private bool bPreserveAutoGeneratedResources = false`
- L227 _private field_ `private bool bConsolidateConfigFiles = false`
- L228 _private field_ `private int PendingChangeList = -1`
- L230 _private* field_ `HashSet<string> AutoGeneratedFiles = new()`
- L231 _private* field_ `HashSet<string> AutoGeneratedDirectories = new()`
- L233-374 _public method_ `public override void ExecuteBuild()`
- L376-408 _private method_ `private void ParseIncludeExcludePlugins(in String Parameter, ref List<String> ParseResult)`
- L409-532 _private method_ `private bool ParseCommandLine()`
- L534-607 _private method_ `private bool ParseTemplateLocalizationConfigFiles()`
- L609-612 _private method_ `private void AddStaticLocalizationBatches(List<LocalizationBatch> LocalizationBatches)`
- L614-632 _private method_ `private void AddPlatformLocalizationBatches(List<LocalizationBatch> LocalizationBatches)`
- L634-696 _private method_ `private void AddPluginLocalizationBatches(List<LocalizationBatch> LocalizationBatches, HashSet<string> PluginsAdded, HashSet<string> AdditionalPluginsToExclude)`
- L698-722 _private method_ `private string BuildEditorArguments()`
- L724-815 _private method_ `private void AppendEnableIncludedPluginsArgument()`
- L817-830 _private method_ `private void InitializeLocalizationProvider(List<LocalizationTask> LocalizationTasks)`
- L832-845 _private method_ `private void DownloadFilesFromLocalizationProvider(List<LocalizationTask> LocalizationTasks)`
- L847-873 _private method_ `private void UploadFilesToLocalizationProvider(List<LocalizationTask> LocalizationTasks)`
- L875-900 _private method_ `private string GetEditorExePath()`
- L902-910 _private method_ `private ERunOptions GetCommandletRunOptions()`
- L912-937 _private method_ `private void StartGatherCommands(List<LocalizationTask> LocalizationTasks)`
- L939-965 _private method_ `private void WaitForCommandletResults(List<LocalizationTask> LocalizationTasks)`
- L967-982 _private method_ `private void CleanUpGeneratedPreviewFiles(List<LocalizationBatch> LocalizationBatches)`
- L984-1035 _private method_ `private void FinalizeSourceControlState(List<LocalizationBatch> LocalizationBatches, Dictionary<string, Byte[]> InitalPOFileHashes)`
- L1037-1104 _private method_ `private void AutoGeneratePluginLocalizationFiles(HashSet<string> PluginNames)`
- L1106-1141 _private method_ `private void CleanUpAutoGeneratedFiles()`
- L1143-1195 _private method_ `private ProjectInfo GenerateProjectInfo(string RootWorkingDirectory, string ProjectName, IReadOnlyList<string> LocalizationStepNames)`
- L1197-1248 _private method_ `private ProjectImportExportInfo GenerateProjectImportExportInfo(string RootWorkingDirectory, string LocalizationConfigFile)`
- L1250-1282 _private method_ `private List<string> GetLocalizationTargetsFromDirectory(DirectoryReference ConfigDirectory)`
- L1284-1326 _private method_ `private Dictionary<string, byte[]> GetPOFileHashes(IReadOnlyList<LocalizationBatch> LocalizationBatches, string UEProjectRoot)`
- L1328-1345 _private method_ `private List<string> GetPreviewManifestFilesToDelete(IReadOnlyList<LocalizationBatch> LocalizationBatches, string UEProjectRoot)`

#### class `Localize.LocalizationBatch`  
`private class LocalizationBatch`  
_private; L40-54_
- L42-48 _public ctor_ `public LocalizationBatch(string InUEProjectDirectory, string InLocalizationTargetDirectory, string InRemoteFilenamePrefix, IReadOnlyList<string> InLocalizationProjectNames)`
- L50 _public property_ `public string UEProjectDirectory { get; set; }`
- L51 _public property_ `public string LocalizationTargetDirectory { get; set; }`
- L52 _public property_ `public string RemoteFilenamePrefix { get; set; }`
- L53 _public property_ `public IReadOnlyList<string> LocalizationProjectNames { get; set; }`

#### class `Localize.LocalizationTask`  
`private class LocalizationTask`  
_private; L56-82_
- L58-74 _public ctor_ `public LocalizationTask(LocalizationBatch InBatch, string InUEProjectRoot, string InLocalizationProviderName, int InPendingChangeList, BuildCommand InCommand)`
- L76 _public field_ `public LocalizationBatch Batch`
- L77 _public field_ `public string RootWorkingDirectory`
- L78 _public field_ `public string RootLocalizationTargetDirectory`
- L79 _public field_ `public LocalizationProvider LocProvider = null`
- L80 _public field_ `public List<ProjectInfo> ProjectInfos = new List<ProjectInfo>()`
- L81 _public field_ `public List<IProcessResult> GatherProcessResults = new List<IProcessResult>()`

#### class `Localize.IGatherTextCommandletLauncherStrategy`  
`private abstract class IGatherTextCommandletLauncherStrategy`  
_private; L84-113_
- L106-109 _public ctor_ `public IGatherTextCommandletLauncherStrategy(IGatherTextCommandletLauncherStrategy.Args InArgs)`
- L110 _public method_ `public abstract void LaunchCommandlet(List<LocalizationTask> LocalizationTasks)`
- L112 _protected field_ `protected readonly IGatherTextCommandletLauncherStrategy.Args LauncherArgs`

#### class `Localize.IGatherTextCommandletLauncherStrategy.Args`  
`public class Args`  
_public; L86-104_
- L88 _public property_ `public string AbsoluteEditorExePath { get; set; }`
- L89 _public property_ `public ERunOptions CommandletRunOptions { get; set; }`
- L90 _public property_ `public string AbsoluteUEProjectDirectoryPath { get; set; }`
- L91 _public property_ `public string UEProjectName { get; set; }`
- L92 _public property_ `public string EditorArgs { get; set; }`
- L93 _public property_ `public List<string> LocalizationStepNames { get; set; }`
- L95-103 _public method_ `public string GetAbsoluteUEProjectPath()`

#### class `Localize.BatchedGatherTextCommandletLauncherStrategy`  
`private class BatchedGatherTextCommandletLauncherStrategy : IGatherTextCommandletLauncherStrategy`  
_private; L115-144_
- inherits: `IGatherTextCommandletLauncherStrategy`
- L117-120 _public ctor_ `public BatchedGatherTextCommandletLauncherStrategy(IGatherTextCommandletLauncherStrategy.Args InArgs) : base(InArgs)`
- L122-143 _public method_ `public override void LaunchCommandlet(List<LocalizationTask> LocalizationTasks)`

#### class `Localize.ConsolidatedGatherTextCommandletLauncherStrategy`  
`private class ConsolidatedGatherTextCommandletLauncherStrategy : IGatherTextCommandletLauncherStrategy`  
_private; L146-209_
- inherits: `IGatherTextCommandletLauncherStrategy`
- L148-151 _public ctor_ `public ConsolidatedGatherTextCommandletLauncherStrategy(IGatherTextCommandletLauncherStrategy.Args InArgs) : base(InArgs)`
- L152-208 _public method_ `public override void LaunchCommandlet(List<LocalizationTask> LocalizationTasks)`

#### class `ExportMcpTemplates`  
`public class ExportMcpTemplates : BuildCommand`  
_public; L1351-1450_
- attrs: `[Help("OnlyLoc", "Optional. Only submit generated loc files, do not submit any other generated file.")] [Help("NoRobomerge", "Optional. Do not include the markup in the CL description to allow robomerging to other branches.")]`
- inherits: `BuildCommand`
- L1353-1356 _public method_ `public static string GetGameBackendFolder(FileReference ProjectFile)`
- L1358-1434 _public method_ `public static void RunExportTemplates(FileReference ProjectFile, bool bCheckoutAndSubmit, bool bOnlyLoc, bool bbNoRobomerge, string CommandletOverride)`
- L1436-1449 _public method_ `public override void ExecuteBuild()`

#### class `Localise`  
`class Localise : Localize`  
_internal*; L1453-1455_
- inherits: `Localize`

### `Source/Programs/AutomationTool/Scripts/MegaXGE.Automation.cs` (AutomationScripts.Automation)


#### class `MegaXGE`  
`class MegaXGE : BuildCommand`  
_internal*; L19-175_
- attrs: `[Help("Compiles a bunch of stuff together with megaxge: Example arguments: -ubtargs=\"-nopdb\" -Target1=\"PlatformerGame win32|ios debug|development\"")] [Help(typeof(UnrealBuild))] [Help("ubtargs", "-args -for -ubt")] [Help("clean", "Cleans targets before building")] [Help("progress", "Reports the current steps to the log")] [Help("Target1", "target1[|target2...] platform1[|platform2...] config1[`
- inherits: `BuildCommand`
- L21-174 _public method_ `public override void ExecuteBuild()`

### `Source/Programs/AutomationTool/Scripts/MemreportHelper.cs` (AutomationScripts.Automation)


#### class `MemreportHelper`  
`public class MemreportHelper : BuildCommand`  
_public; L15-425_
- attrs: `[Help("MemreportToHelper is used to take a memreport file, extract the CSV sections and generate a GSheet from them (i.e:RunUAT.bat MemReportToGSheet -report=myFile.memreport -name=SheetName (optional)")]`
- inherits: `BuildCommand`
- L29 _private field_ `private string[] InputFileAllLines`
- L30 _private field_ `private List<MRCsvBlock> CsvBlocks = new List<MRCsvBlock>()`
- L31-96 _private method_ `private bool ReadCsvListAndAdd(string ListHeader, int LineOffset, string SizeKey, bool SkipCsvRequired=false)`
- L98-423 _public method_ `public override ExitCode Execute()`

#### class `MemreportHelper.MRCsvBlock`  
`class MRCsvBlock`  
_private*; L18-27_
- L21 _public field_ `public int LineIndex`
- L22 _public field_ `public string Title`
- L23 _public field_ `public string SizeKey`
- L24 _public field_ `public List<Dictionary<string, string>> SortedRows = ...`
- L24 _public field_ `public List<Dictionary< SortedRows = new List<Dictionary<string, string>>()`
- L25 _public field_ `public StringBuilder sb = new StringBuilder()`

### `Source/Programs/AutomationTool/Scripts/MultiClientLauncher.Automation.cs` (AutomationScripts.Automation)


#### class `MultiClientLauncher.Automation.MultiClientLauncher`  
`public class MultiClientLauncher : BuildCommand`  
_public; L34-408_
- attrs: `[Help("Run many game clients, a server, and connect them")] [ParamHelp("ClientExe", "Absolute path to the client to run", ParamType = typeof(FileReference))] [ParamHelp("ClientCount", "How many bot clients to run, must consecutively follow FirstClientNumber", ParamType = typeof(int))] [ParamHelp("BuildIdOverride", "Parameter for -buildidoverride switch, often used to narrow down matchmaking to a p`
- inherits: `BuildCommand`
- L36 _private field_ `private bool CancelClientProcesses = false`
- L38 _private field_ `private string ClientExe`
- L39 _private field_ `private string ClientLogDir`
- L40 _private field_ `private string ClientArgs`
- L41 _private field_ `private string ClientLogFilenameGuess`
- L43 _private field_ `private int FirstClientNumber`
- L44 _private field_ `private int ClientCount`
- L45 _private field_ `private int BuildIdOverride`
- L46 _private field_ `private bool NullRHI = false`
- L47 _private field_ `private bool GridLayout = true`
- L48 _private field_ `private bool NoTimeouts = false`
- L49 _private field_ `private bool DeleteExistingLogs = true`
- L51 _private field_ `private int SleepTimeBetweenLaunches = 100`
- L52 _private field_ `private int MaxRunAttemptsPerClient = 3`
- L54 _private const_ `private const int SleepTimeBetweenChecksForClientRelaunches = 1000`
- L56 _protected field_ `protected ClientLogIndicators ClientIndicators`
- L58-116 _private method_ `private void ParseCommandLine()`
- L118-121 _protected method_ `protected virtual string GetDefaultArgsFile()`
- L124-129 _protected method_ `protected virtual void InitializeClientLogIndicators()`
- L131-232 _public method_ `public override ExitCode Execute()`
- L234-239 _private method_ `private ClientProcess SpawnClientProcess(string ExeFilename, string ClientLogFilename, string ExeArguments)`
- L241-248 _private method_ `private static void KillProcesses(List<ClientProcess> Processes)`

#### struct `MultiClientLauncher.Automation.MultiClientLauncher.ClientLogIndicators`  
`protected struct ClientLogIndicators`  
_protected; L250-255_
- L252 _public field_ `public string FinishedGameAndDisconnected`
- L253 _public field_ `public string FailedToConnectToServer`
- L254 _public field_ `public string ConnectedToServer`

#### class `MultiClientLauncher.Automation.MultiClientLauncher.ClientProcess`  
`private class ClientProcess`  
_private; L257-407_
- L259 _private field_ `private readonly Process Proc`
- L260 _private field_ `private int RemainingRunAttempts`
- L262 _private field_ `private Thread LogSkimmer`
- L263 _private const_ `private const int SleepTimeBetweenLogSkims = 1000`
- L264 _private field_ `private readonly ClientLogIndicators LogIndicators`
- L265 _private field_ `private readonly string LogFilepath`
- L267 _private field_ `private readonly Stopwatch ConnectionTimer`
- L268 _private const_ `private const int MinutesUntilTimeout = 15`
- L269 _private field_ `private bool NoTimeouts = false`
- L271-283 _public ctor_ `public ClientProcess(string Exe, string Args, int MaxRunAttempts, bool IgnoreTimeouts, string ClientLog, ClientLogIndicators ClientIndicators)`
- L285-288 _public method_ `public bool Stopped()`
- L291-312 _public method_ `public bool Start()`
- L314-317 _private method_ `private string GetProcessName()`
- L319-322 _public method_ `public void Kill()`
- L324-406 _private method_ `private void MonitorClient()`

### `Source/Programs/AutomationTool/Scripts/MultiShelve.cs` (AutomationScripts.Automation)


#### class `BuildScripts.Automation.MultiShelve`  
`class MultiShelve : BuildCommand`  
_internal*; L20-83_
- attrs: `[RequireP4] [DoesNotNeedP4CL] [Help("Shelves multiple changelists into one (useful for preflighting multiple changes together")] [Help("TargetCL=<changelist>", "If not specified, the script will create a new changelist to shelve into, and write out the CL number")] [Help("SourceCLs=<cl,cl,...>", "List of changelists to shelve into the TargetCL")]`
- inherits: `BuildCommand`
- L22-82 _public method_ `public override void ExecuteBuild()`

### `Source/Programs/AutomationTool/Scripts/OpenEditor.Automation.cs` (AutomationScripts.Automation)


#### class `AutomationTool.OpenEditor`  
`public class OpenEditor : BuildCommand`  
_public; L21-98_
- attrs: `[Help("Opens the specified project.")] [Help("project=<QAGame>", "Project to open. Will search current path and paths in ueprojectdirs. If omitted will open vanilla UnrealEditor")] [ParamHelp("Run", "The name of the commandlet to run")]`
- inherits: `BuildCommand`
- L24 _public property_ `public string ProjectName { get; set; }`
- L26 _private field_ `private string _UnrealEditorApp = "UnrealEditor"`
- L27-37 _public property_ `public string UnrealEditorApp { get; set; }`
- L39 _public property_ `public bool bNoProject { get; set; }`
- L41-44 _public ctor_ `public OpenEditor()`
- L46-80 _protected method_ `protected IEnumerable<string> GetParamList()`
- L82-97 _public method_ `public override ExitCode Execute()`

#### class `AutomationTool.RunProceess`  
`public class RunProceess`  
_public; L100-115_
- L102-114 _public method_ `public static bool RunUntrackedProcess(string BinaryPath, string Args)`

### `Source/Programs/AutomationTool/Scripts/Oplog/ChunkAssigner.cs` (AutomationScripts.Automation)


#### class `AutomationScripts.Oplog.ChunkAssigner`  
`public abstract class ChunkAssigner`  
_public; L28-118_
- desc: Abstract base class for chunk assignment transforms. Games can provide a custom implementation by: Subclassing ChunkAssigner. Tagging the subclass with [ChunkAssigner("MyAssignerName")] . Setting [/Script/UnrealEd.ProjectPackagingSettings] ChunkAssigner=MyAssignerName in DefaultGame.ini. If no custom assigner is configured, the engine default (DefaultChunkAssigner) is used. This mirrors the CustomStageCopyHandler extensibility pattern.
- L46 _public method_ `public abstract ChunkAssignments AssignChunks(IReadOnlyList<OplogEntry> OplogEntries, UnrealTargetPlatform TargetPlatform, TargetReceipt Receipt)` — Assigns packages in the graph to chunks and returns the structured ChunkAssignments result. OplogEntries can be transformed into a package graph via PackageGraphBuilder.Build. All package metadata is accessible via PackageGraph.GetMetadata and PackageGraph.QueryNodes.
- L55 _public method_ `public virtual void Configure(FileReference projectFile, ConfigHierarchy engineIni, ConfigHierarchy gameIni)` — Called by CreateFromConfig after instantiation to supply the project file and game config. Override to receive either or both (e.g. PrimaryAssetChunkAssigner needs gameIni; a custom game-side assigner may need both). The default implementation is a no-op.
- L62-83 _public method_ `public static ChunkAssigner Create(string name)` — Creates a ChunkAssigner by name, scanning all loaded script assemblies for a class tagged with [ChunkAssignerAttribute("name")] .
- L91-114 _public method_ `public static ChunkAssigner CreateFromConfig(FileReference projectFile, ConfigHierarchy engineIni, ConfigHierarchy gameIni)` — Creates a ChunkAssigner by reading the ini key [/Script/UnrealEd.ProjectPackagingSettings] ChunkAssigner from the supplied game config. Falls back to DefaultChunkAssigner if the key is absent or the named type is not found.
- L117 _internal field_ `internal static Dictionary<string, Type>? s_registry`
- L117 _internal field_ `internal static Dictionary< s_registry`

#### class `AutomationScripts.Oplog.ChunkAssignerAttribute`  
`public sealed class ChunkAssignerAttribute : OplogAttribute`  
_public; L124-129_
- attrs: `[AttributeUsage(AttributeTargets.Class)]`
- inherits: `OplogAttribute`
- desc: Attribute used to register a ChunkAssigner subclass by name.
- L126-128 _public ctor_ `public ChunkAssignerAttribute(string name) : base(name)`

### `Source/Programs/AutomationTool/Scripts/Oplog/ChunkAssignmentJsonWriter.cs` (AutomationScripts.Automation)


#### class `AutomationScripts.Oplog.ChunkAssignmentJsonWriter`  
`public sealed class ChunkAssignmentJsonWriter`  
_public; L20-172_
- desc: Writes the ChunkAssignments result both as a debug JSON file and as a Zen oplog op. The JSON path is a straight reflection-based serialization of the ContainerChunks list (full shape, every property emitted). The oplog op applies the "different or no IoChunkId" filtering rule so the on-wire payload only carries PackageName/FilePath when they can't be derived from the cook oplog by IoChunkId.
- L27-50 _public method_ `public void Write(ChunkAssignments assignments, string outputDir)` — Writes assignments to chunk_assignments.json inside outputDir. Streams one ContainerChunk at a time straight to the file via Utf8JsonWriter
- L56-86 _public method_ `public void WriteOp(ChunkAssignments assignments, OplogWriter oplogWriter)` — Appends a single CbObject to the Zen oplog keyed "ChunkAssignment" . The op payload uses the same omission rules as the JSON output.
- L90-159 _private method_ `private static void WriteFileCb(CbWriter w, ContainerChunkFile file)`
- L161-171 _private method_ `private static bool HasNonZeroSegment(IReadOnlyList<BulkDataSegments> segments)`

### `Source/Programs/AutomationTool/Scripts/Oplog/ChunkAssignmentOp.cs` (AutomationScripts.Automation)


#### class `AutomationScripts.Oplog.ChunkAssignmentOp`  
`public sealed class ChunkAssignmentOp : OplogEntry`  
_public; L20-179_
- attrs: `[OplogEntry("ChunkAssignmentOp")]`
- inherits: `OplogEntry`
- desc: Reader-side counterpart to ChunkAssignmentJsonWriter.WriteOp . The op key is "ChunkAssignment" ; the attachment payload is a CbObject containing a chunks array of { id, name?, encguid?, files: [ { id?, pkg?, path?, size? } ] } . id on the file is the IoChunkId from the cook oplog's packagedata / bulkdata; pkg and path are populated only when the file has no IoChunkId or the staged path diverges from the canonical cook path.
- L22 _public property_ `public ChunkAssignments Assignments { get; set; }`
- L24 _public method_ `public override string GetKey()`
- L26-111 _public method_ `public override bool ParseData(CbField entryField, string BaseOplogURL)`
- L119-167 _public method_ `public void ResolveFilenames(IReadOnlyCollection<OplogEntry> entries)` — Fills in missing ContainerChunkFile.FilePath values by looking up each file's IoChunkId against the packagedata / bulkdata entries of all PackageOplogEntry instances in entries. Files with no IoChunkId (already carrying explicit FilePath) are left untouched.
- L169-178 _private method_ `private static string? ReadOptionalString(CbObject obj, string name)`

### `Source/Programs/AutomationTool/Scripts/Oplog/ChunkAssignments.cs` (AutomationScripts.Automation)


#### record struct `AutomationScripts.Oplog.IoChunkId`  
`public readonly record struct IoChunkId(IoHash Hash)`  
_public; L15-23_
- desc: Alias for IO Store chunk id. The C# automation layer uses IoHash for the 12-byte chunk identifier that maps to a packagedata/bulkdata entry in the cook oplog; this struct keeps the canonical C++ name and exposes the underlying hash for serialization.
- L17 _public property_ `public static IoChunkId Empty => ...`
- L19 _public property_ `public bool IsEmpty => ...`
- L21 _public operator_ `public static implicit operator IoChunkId(IoHash hash)`
- L22 _public operator_ `public static implicit operator IoHash(IoChunkId id)`

#### record `AutomationScripts.Oplog.BulkDataMapEntry`  
`public record BulkDataMapEntry(Int64 Offset, Int64 DuplicateOffset, Int64 Size, UInt32 Flags, byte CookedIndex)`  
_public; L30-30_
- desc: One entry from the cook bulk-data map (mirrors FBulkDataMapEntry on the C++ side). Carried per file so the chunk-assignment output can describe bulk slicing without re-reading the oplog at consume time.

#### record `AutomationScripts.Oplog.BulkDataSegments`  
`public record BulkDataSegments(IoChunkId ChunkId, Int64 Offset, Int64 Size)`  
_public; L35-35_
- desc: One inline bulk-data segment (a sub-range inside another IO Store chunk).

#### class `AutomationScripts.Oplog.ContainerChunkFile`  
`public class ContainerChunkFile`  
_public; L47-62_
- desc: One file assigned to a ContainerChunk. ChunkId is the identifying IoChunkId from the cook oplog. PackageName and FilePath are only carried by writers when the file path cannot be derived from ChunkId alone — i.e. the file doesn't have an IoChunkId (loose / uncooked / locres / locmeta files), or the actual staged path differs from the canonical cooked path for its package.
- L49 _public property_ `public IoChunkId ChunkId { get; set; }`
- L51 _public property_ `public string? PackageName { get; set; }`
- L53 _public property_ `public string? FilePath { get; set; }`
- L55 _public property_ `public string? UfsPath { get; set; }`
- L57 _public property_ `public Int64 Size { get; set; }`
- L59 _public property_ `public List<BulkDataMapEntry> BulkDataMap { get; init; }`
- L61 _public property_ `public List<BulkDataSegments> BulkDataSegments { get; init; }`

#### class `AutomationScripts.Oplog.ContainerChunk`  
`public class ContainerChunk`  
_public; L67-84_
- desc: One pak/iostore container chunk produced by the chunk assigner.
- L69 _public property_ `public int ContainerChunkId { get; set; }`
- L71 _public property_ `public string? Name { get; set; }`
- L73 _public property_ `public string? EncryptionKeyGuid { get; set; }`
- L75 _public property_ `public string? Path { get; set; }`
- L77 _public property_ `public bool IsOnDemand { get; set; }`
- L79 _public property_ `public bool IsSigned { get; set; }`
- L81 _public property_ `public bool EncryptIndex { get; set; }`
- L83 _public property_ `public List<ContainerChunkFile> Files { get; init; }`

#### class `AutomationScripts.Oplog.ChunkAssignments`  
`public class ChunkAssignments`  
_public; L90-93_
- desc: Result of ChunkAssigner.AssignChunks. Replaces the DataTable-based output the assigner pipeline used historically.
- L92 _public property_ `public List<ContainerChunk> ContainerChunks { get; init; }`

### `Source/Programs/AutomationTool/Scripts/Oplog/ChunkDependencyTree.cs` (AutomationScripts.Automation)


#### class `AutomationScripts.Oplog.ChunkDependencyTree`  
`public sealed class ChunkDependencyTree`  
_public; L19-447_
- desc: Reads the chunk parent hierarchy from [/Script/CoreUObject.ChunkDependencyInfo] +DependencyArray=(ChunkID=X,ParentChunkID=Y) and exposes FindHighestSharedChunk which returns the deepest common ancestor chunk for a set of chunk IDs — mirroring
- L23 _private field_ `private Dictionary<int, HashSet<int>> _childToParents`
- L23 _private field_ `private Dictionary< _childToParents`
- L27 _private field_ `private List<int> _topologicalOrder`
- L30 _private field_ `private readonly List<(int ChunkId, int ParentChunkId)> _rawDeps`
- L32-40 _private ctor_ `private ChunkDependencyTree( Dictionary<int, HashSet<int>> childToParents, List<int> topologicalOrder, List<(int ChunkId, int ParentChunkId)> rawDeps)`
- L46-75 _public method_ `public static ChunkDependencyTree ReadFromConfig(ConfigHierarchy ini)` — Reads [/Script/CoreUObject.ChunkDependencyInfo] +DependencyArray from the supplied config and builds the dependency tree.
- L83-150 _public method_ `public int FindHighestSharedChunk(IEnumerable<int> chunkIds)` — Mirrors UChunkDependencyInfo::FindHighestSharedChunk . Returns the deepest common ancestor chunk for all input chunk IDs. Returns 0 if no common ancestor is found (chunk 0 is the universal root). Returns -1 (INDEX_NONE) if any input chunk is not in the tree.
- L158-174 _public method_ `public bool HasChunk(int inChunkId)` — returns true if the chunkId was already registered in some pair.
- L186-205 _public method_ `public bool TryAddDependency(int chunkId, int parentChunkId)` — Registers a new chunk→parent dependency pair. Returns false (and does nothing) if: chunkId is 0 — the root cannot have a parent chunkId equals parentChunkId — self-reference parentChunkId is not present in the current tree The tree is not updated until Rebuild is called.
- L214-240 _public method_ `public bool TryUpdateParentChunk(int chunkId, int parentChunkId)` — Attempts to update an existing chunk -> parentChunk pair in the known dependencies.
- L247-252 _public method_ `public void Rebuild()` — Rebuilds the internal dependency maps from all registered pairs — both the original entries and any added via TryAddDependency. Safe to call multiple times.
- L256-358 _private method_ `private static ChunkDependencyTree Build(IEnumerable<(int ChunkId, int ParentChunkId)> depsInput)`
- L360-392 _private method_ `private static void BuildTransitiveClosure( int node, HashSet<int> parentsSoFar, Dictionary<int, List<int>> children, Dictionary<int, HashSet<int>> childToParents)`
- L399-446 _private method_ `private static bool TryParseChunkDependency(string entry, out int chunkId, out int parentChunkId)` — Parses "(ChunkID=10,ParentChunkID=0)" → (10, 0).

### `Source/Programs/AutomationTool/Scripts/Oplog/DefaultChunkAssigner.cs` (AutomationScripts.Automation)


#### class `AutomationScripts.Oplog.DefaultChunkAssigner`  
`public sealed class DefaultChunkAssigner : ChunkAssigner`  
_public; L17-95_
- attrs: `[ChunkAssigner("DefaultChunkAssigner")]`
- inherits: `ChunkAssigner`
- desc: Engine-default chunk assignment implementation. Gives a quick way users can write their own method for chunk assignment. This implementation assigns all packages to chunk 0 or 10.
- L19-80 _public method_ `public override ChunkAssignments AssignChunks(IReadOnlyList<OplogEntry> OplogEntries, UnrealTargetPlatform TargetPlatform, TargetReceipt Receipt)`
- L82-94 _private method_ `private static ContainerChunk GetOrAddChunk(SortedDictionary<int, ContainerChunk> map, int chunkId)`

### `Source/Programs/AutomationTool/Scripts/Oplog/GlobalOplogEntry.cs` (AutomationScripts.Automation)


#### class `AutomationScripts.Oplog.GlobalPackageMetaOp`  
`public sealed class GlobalPackageMetaOp : OplogEntry`  
_public; L15-41_
- attrs: `[OplogEntry("GlobalPackageMetaOp")]`
- inherits: `OplogEntry`
- desc: Engine-default per-package metadata reader. Reads the "meta.cook.package" attachment written by FGlobalCookArtifact::AppendPackageMetadata. Populated for every cooked package that has a known asset class. Registered via +OplogPackageMetadata=GlobalPackageMetaOp in BaseGame.ini.
- L17 _public method_ `public override string GetKey()`
- L19-37 _public method_ `public override bool ParseData(CbField entryField, string BaseOplogURL)`
- L39 _public property_ `public string Class { get; set; }`
- L40 _public property_ `public bool IsPrimaryAsset { get; set; }`

### `Source/Programs/AutomationTool/Scripts/Oplog/LocalizationOplogEntry.cs` (AutomationScripts.Automation)


#### class `AutomationScripts.Oplog.LocalizationOp`  
`public class LocalizationOp : OplogEntry`  
_public; L16-50_
- attrs: `[OplogEntry("LocalizationOp")]`
- inherits: `OplogEntry`
- desc: Oplog entry emitted by FLocalizationCookArtifact at the end of cook. Contains set of localization file paths: LocFiles — relative to the workspace root, for game and plugin source localization files. Cultures — the cultures that were being cooked for.
- L18 _public method_ `public override string GetKey()`
- L20-47 _public method_ `public override bool ParseData(CbField entryField, string BaseOplogURL)`
- L48 _public field_ `public HashSet<string> LocFiles = new HashSet<string>()`
- L49 _public field_ `public HashSet<string> Cultures = new HashSet<string>()`

### `Source/Programs/AutomationTool/Scripts/Oplog/OplogEntry.cs` (AutomationScripts.Automation)


#### class `AutomationScripts.Oplog.OplogEntry`  
`public abstract class OplogEntry`  
_public; L23-105_
- desc: Used as the base class for all Oplog Entries and their metadata. Allows for custom game oplog entries or custom metadata on each package op.
- L26 _public method_ `public abstract string GetKey()`
- L29 _public method_ `public abstract bool ParseData(CbField entryField, string BaseOplogURL)`
- L31-65 _public method_ `public static CbObject DownloadAttachment(string BaseOplogURL, IoHash Hash)`
- L80-102 _public method_ `public static OplogEntry? CreateClass(string name)` — Creates a OplogEntry by reading the ini key [/Script/UnrealEd.ProjectPackagingSettings] OplogEntry [/Script/UnrealEd.ProjectPackagingSettings] OplogPackageMetadata from the supplied game config. OplogEntry defines the particular ops we'll attempt to read OplogPackageMetadata defines the additional metadata reader each PackageOplogEntry op will read. All classes should be tagged to be a valid reader. [OplogEntry("MyCustomClass")]
- L104 _internal field_ `internal static Dictionary<string, Type>? s_registry`
- L104 _internal field_ `internal static Dictionary< s_registry`

#### class `AutomationScripts.Oplog.OplogFileRecord`  
`public sealed class OplogFileRecord`  
_public; L112-139_
- desc: One entry from an oplog op's files array. The same shape appears on package ops and the EndCook op (each file has an id, a chunkid hash, the server-side cooked path, and the client-side staged path).
- L115 _public property_ `public string Id { get; init; }` — The 24-hex CbObjectId from the id field.
- L118 _public property_ `public IoHash ChunkId { get; init; }` — The IoHash chunkid from the data field.
- L121 _public property_ `public string ServerPath { get; init; }` — The path from the serverpath field (cook-server relative).
- L124 _public property_ `public string ClientPath { get; init; }` — The path from the clientpath field (with /{engine}/ and /{project}/ placeholders).
- L127-138 _public method_ `public static OplogFileRecord ReadFrom(CbField fileField)` — Read a single record from a files array element.

#### class `AutomationScripts.Oplog.NullOplogEntry`  
`public sealed class NullOplogEntry : OplogEntry`  
_public; L141-152_
- inherits: `OplogEntry`
- L143 _public property_ `public List<CbObject> Files { get; set; }`
- L145 _public method_ `public override string GetKey()`
- L147-151 _public method_ `public override bool ParseData(CbField MetaField, string BaseOplogURL)`

#### class `AutomationScripts.Oplog.OplogEntryAttribute`  
`public sealed class OplogEntryAttribute : OplogAttribute`  
_public; L158-163_
- attrs: `[AttributeUsage(AttributeTargets.Class)]`
- inherits: `OplogAttribute`
- desc: Attribute used to register a OplogEntryAttribute subclass by name.
- L160-162 _public ctor_ `public OplogEntryAttribute(string name) : base(name)`

#### class `AutomationScripts.Oplog.PackageOplogEntry`  
`public sealed class PackageOplogEntry : OplogEntry`  
_public; L170-344_
- attrs: `[OplogEntry("PackageOplogEntry")]`
- inherits: `OplogEntry`
- desc: Internal DTO representing a single parsed oplog entry before graph construction. One instance per package entry read from the Zen server oplog.
- L172 _public property_ `public string PackageName { get; set; }`
- L175 _public property_ `public ulong PackageId { get; set; }` — FPackageId value — 64-bit hash of the package name.
- L178 _public property_ `public uint Flags { get; set; }` — EPackageStoreEntryFlags bits from the oplog.
- L181 _public property_ `public string Filename { get; set; }` — Cooked filename from the oplog packagedata (e.g. "MyGame/Saved/Cooked/.../Foo.uasset"). Empty if absent.
- L184 _public property_ `public List<ulong> ImportedPackageIds { get; set; }` — Hard dependencies: FPackageId values from importedpackageids.
- L187 _public property_ `public List<ulong> SoftPackageReferences { get; set; }` — Soft dependencies: FPackageId values from softpackagereferences.
- L190 _public property_ `public List<ulong> OptionalSegmentImportedPackageIds { get; set; }` — Optional segment imported package IDs. Additional hard dependencies
- L193 _public property_ `public List<string> RuntimeDependencies { get; set; }` — Runtime package dependencies taken from the cook.artifacts
- L196 _public property_ `public IReadOnlyList<PackageFileInfo> PackageFiles { get; set; }` — All files from the oplog packagedata array for this package (e.g. .uasset).
- L199 _public property_ `public IReadOnlyList<PackageFileInfo> BulkDataFiles { get; set; }` — All files from the oplog bulkdata array for this package (e.g. .ubulk, .uptnl).
- L206 _public property_ `public IReadOnlyList<OplogFileRecord> Files { get; set; }` — All files from the oplog top-level files array on this package entry. These are auxiliary files (fonts, shader caches, etc.) referenced by the package with id/serverpath/clientpath plus an IoHash chunkid in data .
- L209 _public field_ `public Dictionary<System.Type, OplogEntry> AdditionalMetadata = ...` — Additional metadata which knows how to read the custom additional metadata keys that might be in each op.
- L209 _public field_ `public Dictionary<System. AdditionalMetadata = new()` — Additional metadata which knows how to read the custom additional metadata keys that might be in each op.
- L211 _public method_ `public override string GetKey()`
- L213-341 _public method_ `public override bool ParseData(CbField entryField, string BaseOplogURL)`
- L343 _internal field_ `static internal readonly Dictionary<string, OplogEntry> _keyToPackageOplogMeta = ...`
- L343 _internal field_ `static internal readonly Dictionary< _keyToPackageOplogMeta = new Dictionary<string, OplogEntry>()`

#### class `AutomationScripts.Oplog.ReferencedSetOplogEntry`  
`public sealed class ReferencedSetOplogEntry : OplogEntry`  
_public; L347-362_
- attrs: `[OplogEntry("ReferencedSetOplogEntry")]`
- inherits: `OplogEntry`
- L349 _public property_ `public List<CbObject> Files { get; set; }`
- L351 _public method_ `public override string GetKey()`
- L353-361 _public method_ `public override bool ParseData(CbField entryField, string BaseOplogURL)`

#### class `AutomationScripts.Oplog.EndCookOplogEntry`  
`public sealed class EndCookOplogEntry : OplogEntry`  
_public; L365-381_
- attrs: `[OplogEntry("EndCookOplogEntry")]`
- inherits: `OplogEntry`
- L367 _public property_ `public List<OplogFileRecord> Files { get; set; }`
- L369 _public method_ `public override string GetKey()`
- L371-380 _public method_ `public override bool ParseData(CbField entryField, string BaseOplogURL)`

#### class `AutomationScripts.Oplog.CookStartupPackagesOp`  
`public class CookStartupPackagesOp : OplogEntry`  
_public; L384-409_
- attrs: `[OplogEntry("CookStartupPackagesOp")]`
- inherits: `OplogEntry`
- L386 _public method_ `public override string GetKey()`
- L388-406 _public method_ `public override bool ParseData(CbField entryField, string BaseOplogURL)`
- L408 _public field_ `public HashSet<string> StartupPackages = new HashSet<string>()`

### `Source/Programs/AutomationTool/Scripts/Oplog/OplogReader.cs` (AutomationScripts.Automation)


#### class `AutomationScripts.Oplog.OplogReader`  
`public sealed class OplogReader`  
_public; L23-217_
- desc: Reads cooked package entries from the Zen store oplog via HTTP. The oplog is served as CompactBinary (application/x-ue-cb).
- L25 _private field_ `private readonly string _socketHostNameAndPort`
- L26 _private field_ `private readonly string _httpHostNameAndPort`
- L27 _private field_ `private readonly string _projectId`
- L28 _private field_ `private readonly string _oplogId`
- L29 _private field_ `private readonly Dictionary<string, OplogEntry> _keyToOplogEntry = ...`
- L29 _private field_ `private readonly Dictionary< _keyToOplogEntry = new Dictionary<string, OplogEntry>()`
- L31 _public property_ `public static HttpClient? HttpClient { get; set; }`
- L37-85 _public ctor_ `public OplogReader(string SocketHostNameAndPort, string HttpHostNameAndPort, string projectId, string oplogId, ConfigHierarchy? gameIni)` — Zen server hostname (e.g. "localhost"). Zen server port (e.g. 8558). Zen project ID. Zen oplog ID.
- L93-104 _public method_ `public IReadOnlyList<OplogEntry> ReadEntries()` — Fetches all package entries from the oplog and returns them as raw DTOs. Entries that do not have a valid packagestoreentry field (e.g. the "EndCook" sentinel) are silently skipped.
- L108-111 _public method_ `public string GetBaseOplogURL()`
- L112-148 _private method_ `private byte[] FetchRawOplog()`
- L150-216 _private method_ `private IReadOnlyList<OplogEntry> ParseEntries(byte[] oplogData)`

### `Source/Programs/AutomationTool/Scripts/Oplog/OplogWriter.cs` (AutomationScripts.Automation)


#### class `AutomationScripts.Oplog.OplogWriter`  
`public sealed class OplogWriter`  
_public; L26-157_
- desc: Writes a single op into a Zen store oplog by POSTing a CbPackage to /prj/{projectId}/oplog/{oplogId}/new . Mirrors the C++ FZenStoreWriter::AppendOp(FName, FCbObject) path in Engine/Source/Developer/IoStoreUtilities/Private/ZenStoreWriter.cpp : the payload is wrapped in a { key, value: BinaryAttachment } root CbObject with a single Oodle-compressed-binary attachment.
- L28 _private field_ `private readonly string _socketHostNameAndPort`
- L29 _private field_ `private readonly string _httpHostNameAndPort`
- L30 _private field_ `private readonly string _projectId`
- L31 _private field_ `private readonly string _oplogId`
- L32 _private field_ `private readonly HttpClient _httpClient`
- L34 _private field_ `private static readonly MediaTypeHeaderValue CbPackageMediaType = new("application/x-ue-cbpkg")`
- L36-57 _public ctor_ `public OplogWriter(string SocketHostNameAndPort, string HttpHostNameAndPort, string projectId, string oplogId)`
- L65-104 _public method_ `public void AppendOp(string keyName, CbObject payload)` — Append a new op to the oplog. The payload is wrapped in a Zen CbPackage with one Oodle-compressed binary attachment containing the serialized CbObject. Throws AutomationTool.AutomationException on network or server failure.
- L106-109 _public method_ `public string GetBaseOplogURL()`
- L120-156 _private method_ `private static byte[] BuildCbPackage(string keyName, CbObject payload)` — Builds the Zen CbPackage wire format produced by C++ SaveCbPackage : a sequence of top-level CB fields with no framing — root object, object-attachment hash, then per-attachment (binary blob + binary-attachment hash), then a terminating null. NOT the same format as EpicGames.Serialization.CbPackageBuilder , which adds a Jupiter header.

### `Source/Programs/AutomationTool/Scripts/Oplog/PackageGraph.cs` (AutomationScripts.Automation)


#### struct `AutomationScripts.Oplog.PackageNode`  
`public readonly struct PackageNode : IEquatable<PackageNode>`  
_public; L18-38_
- inherits: `IEquatable<PackageNode>`
- desc: Opaque handle to a node in a PackageGraph. The internal representation (index) is an implementation detail that can change. Instances are only obtained via PackageGraph lookup methods.
- L21 _public field_ `public readonly int Index` — Internal index into the graph's data arrays. Not part of the public contract.
- L24 _internal field_ `internal readonly PackageGraph Graph` — The graph this node belongs to. Prevents cross-graph comparisons.
- L26-30 _internal ctor_ `internal PackageNode(PackageGraph graph, int index)`
- L32 _public method_ `public bool Equals(PackageNode other)`
- L33 _public method_ `public override bool Equals(object? obj)`
- L34 _public method_ `public override int GetHashCode()`
- L36 _public operator_ `public static bool operator ==(PackageNode left, PackageNode right)`
- L37 _public operator_ `public static bool operator !=(PackageNode left, PackageNode right)`

#### enum `AutomationScripts.Oplog.EPackageFileType`  
`public enum EPackageFileType`  
_public; L41-46_
- desc: Identifies which oplog array a PackageFileInfo was read from.
- L43 _public* enumerator_ `PackageData`
- L44 _public* enumerator_ `Bulk`
- L45 _public* enumerator_ `BulkOptional`

#### record struct `AutomationScripts.Oplog.PackageFileInfo`  
`public readonly record struct PackageFileInfo( string Id, long Size, string Filename, EPackageFileType FileType, IoHash ChunkId )`  
_public; L49-49_
- desc: Metadata for a single physical file associated with a cooked package.

#### class `AutomationScripts.Oplog.PackageMetadata`  
`public sealed class PackageMetadata`  
_public; L62-110_
- desc: Metadata for a package node in the package graph. All fields reflect what was stored in the oplog at cook time. Fields marked "cook TODO" default to safe values until the cook step is updated to write them.
- L65 _public property_ `public string PackageName { get; }` — Lowercase package name (e.g. "/game/foo/bar").
- L68 _public property_ `public ulong PackageId { get; }` — FPackageId value — 64-bit hash of the package name.
- L71 _public property_ `public uint Flags { get; }` — EPackageStoreEntryFlags bits (HasPackageData, AutoOptional, etc.).
- L77 _public property_ `public bool IsStartupPackage { get; }` — Whether this package is a startup package that must live in chunk 0. Defaults to false until the cook step writes this field.
- L80 _public property_ `public string Class { get; }` — Full class path (e.g. "/Script/Engine.World"). Empty if unknown.
- L83 _public property_ `public bool IsPrimaryAsset { get; }` — True if the asset's class derives from UPrimaryDataAsset.
- L86 _public property_ `public IReadOnlyList<PackageFileInfo> PackageFiles { get; }` — Files from the oplog packagedata array for this package (e.g. .uasset).
- L89 _public property_ `public IReadOnlyList<PackageFileInfo> BulkDataFiles { get; }` — Files from the oplog bulkdata array for this package (e.g. .ubulk, .uptnl).
- L91-109 _internal ctor_ `internal PackageMetadata( string packageName, ulong packageId, uint flags, bool isStartupPackage, string className = "", bool isPrimaryAsset = false, IReadOnlyList<PackageFileInfo>? packageFiles = null, IReadOnlyList<PackageFileInfo>? bulkDataFiles = null)`

#### class `AutomationScripts.Oplog.PackageGraphData`  
`internal sealed class PackageGraphData`  
_internal; L117-150_
- desc: Compact internal storage for the package graph. All arrays are indexed by the node's integer index. This class is an implementation detail — callers use PackageGraph.
- L119 _internal field_ `internal int NodeCount`
- L123 _internal field_ `internal PackageMetadata[] Metadata`
- L126 _internal field_ `internal int[][] HardDeps`
- L127 _internal field_ `internal int[][] SoftDeps`
- L128 _internal field_ `internal int[][] RuntimeDeps`
- L129 _internal field_ `internal int[][] HardRefs`
- L130 _internal field_ `internal int[][] SoftRefs`
- L131 _internal field_ `internal int[][] RuntimeRefs`
- L134 _internal field_ `internal Dictionary<ulong, int> IndexById`
- L134 _internal field_ `internal Dictionary< IndexById`
- L135 _internal field_ `internal Dictionary<string, int> IndexByName`
- L135 _internal field_ `internal Dictionary< IndexByName`
- L137-149 _internal ctor_ `internal PackageGraphData(int capacity)`

#### class `AutomationScripts.Oplog.PackageGraph`  
`public sealed class PackageGraph`  
_public; L163-592_
- desc: Immutable directed graph of cooked packages, built from the Zen store oplog. Nodes are PackageNode handles (opaque). Use TryGetNode to obtain a handle by package name or ID, then traverse edges with GetDependencies / GetReferencers and read metadata with GetMetadata. The internal storage format is an implementation detail and may change.
- L165 _private field_ `private readonly PackageGraphData _data`
- L167-170 _internal ctor_ `internal PackageGraph(PackageGraphData data)`
- L173 _public property_ `public int NodeCount => ...` — Total number of package nodes in the graph.
- L176-185 _public property_ `public IEnumerable<PackageNode> AllNodes { get; }` — Enumerate all nodes in the graph.
- L190-199 _public method_ `public bool TryGetNode(string packageName, out PackageNode node)` — Look up a node by lowercase package name (e.g. "/game/foo/bar").
- L202-211 _public method_ `public bool TryGetNode(ulong packageId, out PackageNode node)` — Look up a node by FPackageId (64-bit value).
- L224-247 _public method_ `public IReadOnlyList<PackageNode> GetDependencies(PackageNode node, bool includeRuntimeDependencies = true)` — Returns the hard dependencies (imported packages) of the given node. By default the result also includes runtime dependencies (entries from the cook artifacts RuntimeDependencies set), since callers historically treated runtime deps as hard deps. Pass includeRuntimeDependencies = false to get only the package-store hard imports.
- L250-254 _public method_ `public IReadOnlyList<PackageNode> GetRuntimeDependencies(PackageNode node)` — Returns only the runtime dependencies (from cook artifacts) of the given node.
- L257-261 _public method_ `public IReadOnlyList<PackageNode> GetSoftDependencies(PackageNode node)` — Returns the soft dependencies (soft package references) of the given node.
- L272-295 _public method_ `public IReadOnlyList<PackageNode> GetReferencers(PackageNode node, bool includeRuntimeReferencers = true)` — Returns all packages that hard-import the given node. By default the result also includes packages that runtime-depend on this node (i.e. reverse edges of GetRuntimeDependencies). Pass includeRuntimeReferencers = false to get only the package-store hard referencers.
- L298-302 _public method_ `public IReadOnlyList<PackageNode> GetRuntimeReferencers(PackageNode node)` — Returns only the packages that runtime-depend on the given node.
- L305-309 _public method_ `public IReadOnlyList<PackageNode> GetSoftReferencers(PackageNode node)` — Returns all packages that soft-reference the given node.
- L333-414 _public method_ `public HashSet<PackageNode> GetExclusiveDependencyClosure( IEnumerable<PackageNode> seeds, bool includeRuntimeDependencies = true)` — Returns the set of nodes that are exclusively dependencies of the given seed set — i.e. every node reachable from seeds that cannot also be reached from any node outside seeds. The seeds themselves are always included in the result. Tests under - \Engine\Source\Programs\AutomationTool.Tests\Oplog\PackageGraphTests.cs dotnet test " /Engine/Source/Programs/AutomationTool.Tests/AutomationTool.Tests.csproj" Formally: let R be the forward-reachable closure of seeds and let T ⊂ R\seeds be the set of nodes in R that have at least one path from a node in V\R, or transitively from another tainted R-node. The returned set is R \ T (which always contains the seeds). Edges traversed follow the same hard/runtime semantics as GetDependencies: soft dependencies are not followed. includeRuntimeDependencies toggles whether runtime deps (from cook artifacts) count as edges, on both the forward and reverse traversals.
- L419-423 _public method_ `public PackageMetadata GetMetadata(PackageNode node)` — Returns the metadata for the given node.
- L436-447 _public method_ `public IEnumerable<PackageNode> QueryNodes(Predicate<PackageMetadata> predicate)` — Filters all nodes by the given metadata predicate. // All primary assets of class "Texture2d" var nodes = graph.QueryNodes(m => m.IsPrimaryAsset && m.ClassType == "Texture2d");
- L450-461 _public method_ `public IEnumerable<PackageNode> GetStartupPackages()` — Returns all startup packages (IsStartupPackage == true).
- L465-471 _private method_ `private void ValidateNode(PackageNode node)`
- L473-486 _private method_ `private PackageNode[] ToNodeList(int[] indices)`
- L488-522 _private method_ `private void ExpandForward(int n, BitArray reachMask, Queue<int> queue, bool includeRuntime)`
- L524-555 _private method_ `private bool HasExternalReferencer(int n, BitArray reachMask, bool includeRuntime)`
- L557-591 _private method_ `private void PropagateTaint(int n, BitArray reachMask, BitArray seedMask, BitArray taintMask, Queue<int> taintQueue, bool includeRuntime)`

### `Source/Programs/AutomationTool/Scripts/Oplog/PackageGraphBuilder.cs` (AutomationScripts.Automation)


#### class `AutomationScripts.Oplog.PackageGraphBuilder`  
`public static class PackageGraphBuilder`  
_public; L17-180_
- desc: Builds a PackageGraph from a list of OplogEntry objects. Uses a two-pass approach: Pass 1 — allocate node arrays and assign indices; populate all metadata. Pass 2 — resolve PackageId references to node indices; fill edge arrays and build reverse edges.
- L19-133 _public method_ `public static PackageGraph Build(IReadOnlyList<OplogEntry> entries)`
- L139-156 _private method_ `private static int[] ResolveIds(List<ulong> ids, Dictionary<ulong, int> indexById)` — Resolves a list of PackageId values to node indices. PackageIds that are not found in the graph (e.g. engine/script packages) are silently skipped.
- L162-179 _private method_ `private static int[] ResolveIds(List<string> packageNames, Dictionary<string, int> indexByPackage)` — Resolves a list of PackageId values to node indices. PackageIds that are not found in the graph (e.g. engine/script packages) are silently skipped.

### `Source/Programs/AutomationTool/Scripts/OplogChunkAssigner.Automation.cs` (AutomationScripts.Automation)


#### class `AutomationScripts.Oplog.OplogChunkAssigner`  
`public class OplogChunkAssigner : BuildCommand`  
_public; L58-280_
- attrs: `[Help("Generates pak chunk manifests from an oplog fetched from the Zen cook store.")] [Help("Project=<path>", "Path to the .uproject for this operation.")] [Help("ZenHost=<host>", "Zen server hostname (default: localhost)")] [Help("ZenPort=<port>", "Zen server port (default: 8558)")] [Help("ProjectId=<id>", "Zen project ID")] [Help("OplogId=<id>", "Zen oplog ID")] [Help("Target=<name>", "Target n`
- inherits: `BuildCommand`
- desc: Reads a cooked package oplog from the Zen store, builds a dependency graph, assigns packages to chunks using a configurable ChunkAssigner, and writes pakchunkN.txt / pakchunklist.txt manifests compatible with CreatePaksUsingChunkManifests.
- L61-82 _public method_ `public override void ExecuteBuild()`
- L87-108 _public method_ `public static void RunFromStagingContext(ProjectParams Params, DeploymentContext SC)` — Run OplogChunkAssigner from a staging context, deriving parameters from ProjectParams and DeploymentContext.
- L110-237 _private method_ `private static void Run( FileReference ProjectFile, string SocketHostNameAndPort, string HttpHostNameAndPort, string projectId, string oplogId, string targetName, string configName, string platform, string cookPlatform, string cookDir, string outputDir, bool skipLocalization, BuildCommand? context)`
- L245-279 _internal method_ `internal static Dictionary<string, Type> BuildRegistry(Type[] Subclasses)`

#### class `AutomationScripts.Oplog.OplogChunkAssigner.OplogAttribute`  
`public class OplogAttribute : Attribute`  
_public; L240-244_
- inherits: `Attribute`
- L242 _public property_ `public string Name { get; }`
- L243 _public ctor_ `public OplogAttribute(string name)`

### `Source/Programs/AutomationTool/Scripts/PackageCommand.Automation.cs` (AutomationScripts.Automation)


#### class `AutomationScripts.Project`  
`public partial class Project : CommandUtils`  
_public; L13-63_
- inherits: `CommandUtils`
- L15-62 _public method_ `public static void Package(ProjectParams Params, int WorkingCL = -1)`

### `Source/Programs/AutomationTool/Scripts/ParseMsvcTimingInfo.cs` (AutomationScripts.Automation)


#### class `AutomationTool.ParseMsvcTimingInfo`  
`class ParseMsvcTimingInfo : BuildCommand`  
_internal*; L16-143_
- attrs: `[Help("Parses Visual C++ timing information (as generated by UBT with the -Timing flag), and converts it into JSON format which can be visualized using the chrome://tracing tab")] [Help("-File=<Path>", "Path to the input file")]`
- inherits: `BuildCommand`
- L18-43 _public method_ `public override void ExecuteBuild()`
- L45-100 _private* method_ `int ParseIncludeHeaders(string[] Lines, int LineIdx, FileReference OutputFile)`
- L102-142 _private* method_ `int ParseDefinitions(string[] Lines, int LineIdx, FileReference OutputFile)`

### `Source/Programs/AutomationTool/Scripts/PluginHierarchy.cs` (AutomationScripts.Automation)


#### class `AutomationScripts.PluginHierarchy`  
`public sealed class PluginHierarchy`  
_public; L25-166_
- desc: Engine-level utility that scans all .uplugin files under the engine and project plugin directories and provides access to their PluginDescriptor objects and transitive dependency sets. This is intentionally engine-generic — no game-specific logic lives here.
- L28 _private field_ `private readonly IReadOnlyDictionary<string, PluginDescriptor> _descriptors`
- L28 _private field_ `private readonly IReadOnlyDictionary< _descriptors`
- L29 _private field_ `private readonly IReadOnlyDictionary<string, FileReference> _pluginFiles`
- L29 _private field_ `private readonly IReadOnlyDictionary< _pluginFiles`
- L32 _private field_ `private readonly Dictionary<string, IReadOnlySet<string>> _transitiveCache = ...`
- L32 _private field_ `private readonly Dictionary< _transitiveCache = new Dictionary<string, IReadOnlySet<string>>(StringComparer.OrdinalIgnoreCase)`
- L35-41 _private ctor_ `private PluginHierarchy( IReadOnlyDictionary<string, PluginDescriptor> descriptors, IReadOnlyDictionary<string, FileReference> pluginFiles)`
- L46 _public property_ `public IEnumerable<string> AllPluginNames => ...` — All known plugin names (from the scan).
- L52 _public method_ `public IReadOnlyDictionary<string, PluginDescriptor> GetPluginDescriptors()` — Returns the plugin-name → PluginDescriptor dictionary built during the scan. The dictionary is populated once (during ReadFromProject) and cached.
- L59 _public method_ `public bool TryGetPluginFile(string pluginName, out FileReference? file)` — Tries to return the .uplugin FileReference for the given plugin. Callers that need to read additional non-standard JSON fields (e.g. game-specific metadata) or inspect the on-disk location of a plugin can use this to open the file directly.
- L67-86 _internal method_ `internal IReadOnlySet<string> GetTransitiveDependencies(string pluginName)` — Returns the transitive set of plugin dependencies for pluginName, including the plugin itself. Computed lazily and cached on first call. Returns an empty set if the plugin is not known.
- L94-108 _public method_ `public static PluginHierarchy ReadFromProject(FileReference projectFile)` — Scans .uplugin files under {root}/Engine/Plugins/ and {root}/{projectName}/Plugins/ in parallel and builds the hierarchy.
- L112-142 _private method_ `private static void ScanPluginDirectory( DirectoryReference dir, ConcurrentDictionary<string, PluginDescriptor> descriptors, ConcurrentDictionary<string, FileReference> pluginFiles)`
- L146-165 _private method_ `private void ComputeTransitiveDeps(string pluginName, HashSet<string> visited)`

### `Source/Programs/AutomationTool/Scripts/Properties/AssemblyInfo.cs` (AutomationScripts.Automation)
_(no declarations)_


### `Source/Programs/AutomationTool/Scripts/RebuildHLODCommand.Automation.cs` (AutomationScripts.Automation)


#### class `AutomationScripts.Automation.RebuildHLOD`  
`public class RebuildHLOD : BuildCommand`  
_public; L31-426_
- attrs: `[RequireP4]`
- inherits: `BuildCommand`
- desc: Helper command used for rebuilding a projects Hierarchical LODs.
- L33-85 _public method_ `public override void ExecuteBuild()`
- L87-105 _private method_ `private void BuildNecessaryTargets()`
- L107-115 _private method_ `private int GetLatestCodeChange()`
- L117-124 _private method_ `private void CreateChangelist(ProjectParams Params)`
- L126-196 _private method_ `private void RunRebuildHLODCommandlet(ProjectParams Params)`
- L198-209 _private method_ `private void SubmitRebuiltMaps(ref int SubmittedCL)`
- L216-233 _private method_ `private bool FoundCheckOutErrorInP4Output(string Output)`
- L238-257 _private method_ `private void HandleFailure(String FailureMessage)`
- L262-272 _private method_ `private void HandleSuccess(int SubmittedCL)`
- L274-284 _private method_ `private void HandleSuccessNoCheckin(int SubmittedCL)`
- L289-330 _private* method_ `void SendCompletionMessage(bool bWasSuccessful, String MessageBody)`
- L333-347 _private* property_ `List<string> StakeholdersEmailAddresses { get; }`
- L349-372 _private property_ `private string RobomergeCommand { get; }`
- L375 _private field_ `private int WorkingCL = -1`
- L378-384 _private property_ `private String CommandletTargetName { get; }`
- L387 _private field_ `private FileReference ProjectFullPath`
- L388-425 _public property_ `public virtual FileReference ProjectPath { get; }`

### `Source/Programs/AutomationTool/Scripts/RebuildLightMapsCommand.Automation.cs` (AutomationScripts.Automation)


#### class `AutomationScripts.Automation.RebuildLightMaps`  
`public class RebuildLightMaps : BuildCommand`  
_public; L26-361_
- attrs: `[RequireP4] [Help("Helper command used for rebuilding a projects light maps")] [Help("Project", "Absolute path to a .uproject file")] [Help("MapsToRebuildLightMaps", "A list of '+' delimited maps we wish to build lightmaps for.")] [Help("CommandletTargetName", "The Target used in running the commandlet")] [Help("StakeholdersEmailAddresses", "Users to notify of completion")]`
- inherits: `BuildCommand`
- desc: Helper command used for rebuilding a projects light maps.
- L28-66 _public method_ `public override void ExecuteBuild()`
- L68-87 _private method_ `private void BuildNecessaryTargets()`
- L89-97 _private method_ `private int GetLatestCodeChange()`
- L99-106 _private method_ `private void CreateChangelist(ProjectParams Params)`
- L108-168 _private method_ `private void RunRebuildLightmapsCommandlet(ProjectParams Params)`
- L170-181 _private method_ `private void SubmitRebuiltMaps(ref int SubmittedCL)`
- L188-205 _private method_ `private bool FoundCheckOutErrorInP4Output(string Output)`
- L210-229 _private method_ `private void HandleFailure(String FailureMessage)`
- L234-244 _private method_ `private void HandleSuccess(int SubmittedCL)`
- L249-290 _private* method_ `void SendCompletionMessage(bool bWasSuccessful, String MessageBody)`
- L293-307 _private* property_ `List<String> StakeholdersEmailAddresses { get; }`
- L310 _private field_ `private int WorkingCL = -1`
- L313-319 _private property_ `private String CommandletTargetName { get; }`
- L322 _private field_ `private FileReference ProjectFullPath`
- L323-360 _public property_ `public virtual FileReference ProjectPath { get; }`

### `Source/Programs/AutomationTool/Scripts/RecordPerformance.Automation.cs` (AutomationScripts.Automation)


#### class `RecordPerformance`  
`class RecordPerformance : BuildCommand`  
_internal*; L13-228_
- attrs: `[Help("UAT command to run performance test demo using different RHIs and compare results")]`
- inherits: `BuildCommand`
- L15 _private field_ `private string[] ProjectsToRun = { "SubwaySequencer", "InfiltratorDemo", "ElementalDemo", "ShowdownDemo" }`
- L23 _private field_ `private string ProjectToRun`
- L24 _private field_ `private DirectoryReference RootDir`
- L25 _private const_ `private const string PerformanceMonitorConfig = "Default"`
- L26 _private field_ `private DirectoryReference OutputDir`
- L28-103 _public method_ `public override void ExecuteBuild()`
- L105-120 _private method_ `private IEnumerable<string> ParseMultipleParams(string ParamName)`
- L122-136 _private method_ `private IEnumerable<string> GetRhisForPlatform(string PlatformName)`
- L138-147 _private method_ `private Platform GetPlatformByName(string PlatformName)`
- L149-153 _private method_ `private void RunCsvTool(string ToolName, string Arguments)`
- L155-160 _private method_ `private void CreateChart(string StatName)`
- L162-170 _private method_ `private void CombineStats(Platform Platform, string Rhi)`
- L172-179 _private method_ `private void SetupPaths()`
- L181-215 _private method_ `private void RunGame(Platform Platform, string Rhi, int RunNumber, bool UseStats)`
- L217-222 _private method_ `private void BuildAndCookPlatform(UnrealTargetPlatform Platform)`
- L224-227 _private method_ `private void RunBCR(string Arguments)`

### `Source/Programs/AutomationTool/Scripts/ReplaceAssetsUsingManifest.cs` (AutomationScripts.Automation)


#### class `ReplaceAssetsUsingManifest`  
`public class ReplaceAssetsUsingManifest : BuildCommand`  
_public; L13-94_
- inherits: `BuildCommand`
- L15-93 _public method_ `public override void ExecuteBuild()`

### `Source/Programs/AutomationTool/Scripts/ReportItemizedExecutableCode.cs` (AutomationScripts.Automation)


#### struct `ReportItemizedExecutableCode.Automation.ModuleInfo`  
`struct ModuleInfo`  
_internal*; L17-39_
- L20 _public field_ `public string Name`
- L24 _public property_ `public string ShortName { get; set; }` — attrs: `[JsonPropertyName("shortName")]`
- L28 _public property_ `public string ModuleDirectory { get; set; }` — attrs: `[JsonPropertyName("moduleDirectory")]`
- L32 _public property_ `public string IntermediateDirectory { get; set; }` — attrs: `[JsonPropertyName("intermediateDirectory")]`
- L34 _public property_ `public bool IsEngineModule => ...`
- L35 _public property_ `public bool IsEnginePlugin => ...`
- L36 _public property_ `public bool IsGameModule => ...`
- L37 _public property_ `public bool IsGamePlugin => ...`
- L38 _public property_ `public bool IsGameFeaturePlugin => ...`

#### struct `ReportItemizedExecutableCode.Automation.ModuleResult`  
`struct ModuleResult`  
_internal*; L41-47_
- L44 _public field_ `public string Name`
- L46 _public field_ `public ModuleInfo? ModuleInfo`

#### struct `ReportItemizedExecutableCode.Automation.ModuleInfos`  
`struct ModuleInfos`  
_internal*; L49-93_
- L52 _public field_ `public Dictionary<string, uint> Modules`
- L52 _public field_ `public Dictionary< Modules`
- L55 _public field_ `public Dictionary<string, List<string>> ModuleNameToSources`
- L55 _public field_ `public Dictionary< ModuleNameToSources`
- L58 _public field_ `public List<string> SourcesWithoutModule`
- L61 _public field_ `public uint Total = 0`
- L64 _public field_ `public uint TotalUnclassified = 0`
- L67 _public field_ `public uint TotalEngineSize = 0`
- L70 _public field_ `public uint TotalGameSize = 0`
- L73 _public field_ `public uint TotalEnginePluginSize = 0`
- L76 _public field_ `public uint TotalGamePluginSize = 0`
- L79 _public field_ `public uint TotalGameFeaturesSize = 0`
- L82 _public field_ `public uint TotalExternalLibs = 0`
- L85 _public field_ `public uint TotalUnattributed = 0`
- L87-92 _public ctor_ `public ModuleInfos()`

#### class `ReportItemizedExecutableCode.Automation.ReportItemizedExecutableCode`  
`class ReportItemizedExecutableCode : BuildCommand`  
_internal*; L166-995_
- attrs: `[Help("Reports itemized binary size in a format consumed by PerfReportServer")] [ParamHelp("ExeToItemize", "Absolute path to the binary to itemize", ParamType = typeof(FileReference), Required = true)] [ParamHelp("SymbolsExe", "Absolute path to the symbolicated binary", ParamType = typeof(FileReference))] [ParamHelp("ReportPath", "Absolute path to the directory to write the reports to.", ParamType`
- inherits: `BuildCommand`
- L169 _private field_ `private bool bVerbose = false`
- L171 _private field_ `private List<ModuleInfo> Modules = new()`
- L173-179 _private method_ `private void VerboseLog(string Message)`
- L181-194 _private method_ `private string[] GetReportDestDirectories()`
- L197-302 _private* method_ `string ParseModuleName(string SourcePath)`
- L304-365 _private* method_ `ModuleResult? FindModule(string SourcePath)`
- L368-375 _private method_ `private static string SanitizeModuleName(string ModuleName)`
- L377-385 _private method_ `private static bool IsValidModuleName(string ModuleName)`
- L387-394 _private method_ `private static bool IsPathLike(string InString)`
- L397-534 _protected method_ `protected ModuleInfos ItemizeExecutableWithBloaty(FileReference Binary, FileReference SymbolsBinary)`
- L537-540 _public method_ `virtual public ModuleInfos PlatformItemizeExecutable(FileReference Binary, FileReference SymbolsBinary)`
- L542-575 _public method_ `public override void ExecuteBuild()`
- L577-650 _private method_ `private List<ModuleInfo> BuildModuleList()`
- L652-697 _private method_ `private void ExecuteItemization(FileReference ExecutableFileToItemize, string[] DestDirs)`
- L699-710 _private method_ `private void WriteItemizedReport(FileReference ExecutableFileToItemize, string[] DestPaths)`
- L712-792 _private method_ `private void WriteItemizedReport(ModuleInfos Info, string[] DestPaths)`
- L794-827 _private method_ `private void WriteTotalsReport(ModuleInfos Info, string[] DestPaths)`
- L829-864 _private method_ `private void WriteSectionsReport(FileReference ExecutableFile, string[] DestPaths)`
- L867-901 _protected method_ `protected static string[] RunBloaty(string Args, string ResultsOverride = null)`
- L903-994 _private method_ `private void ExecuteMergedModulesAnalysis(DirectoryReference DllRoot, string[] DestDirs)`

#### enum `ReportItemizedExecutableCode.Automation.MergedModulePlatform`  
`internal enum MergedModulePlatform`  
_internal; L999-1002_
- L1001 _public* enumerator_ `Auto`
- L1001 _public* enumerator_ `Switch`
- L1001 _public* enumerator_ `Win64`
- L1001 _public* enumerator_ `PS4`
- L1001 _public* enumerator_ `PS5`
- L1001 _public* enumerator_ `Android`
- L1001 _public* enumerator_ `iOS`
- L1001 _public* enumerator_ `Xbox`

#### class `ReportItemizedExecutableCode.Automation.MergedModulePlatformConfig`  
`internal sealed class MergedModulePlatformConfig`  
_internal; L1006-1107_
- L1008 _public property_ `public MergedModulePlatform Platform { get; set; }`
- L1009 _public property_ `public string[] ModuleExtensions { get; set; }`
- L1010 _public property_ `public string[] EagerPrefixes { get; set; }`
- L1011 _public property_ `public string[] PackageMarkerSuffixes { get; set; }`
- L1013 _private ctor_ `private MergedModulePlatformConfig()`
- L1016-1086 _public method_ `public static MergedModulePlatformConfig Create(string PlatformArg, string ExtsArg, string EagerArg, string PkgArg)`
- L1088-1106 _public method_ `public static MergedModulePlatform ParsePlatform(string S)`

#### class `ReportItemizedExecutableCode.Automation.MergedModuleScanner`  
`internal static class MergedModuleScanner`  
_internal; L1112-1249_
- L1130-1177 _public method_ `public static List<Row> EnumerateModules(DirectoryReference Root, MergedModulePlatformConfig Cfg, bool PackagedOnly, string ConfigFilter)`
- L1180-1197 _public method_ `public static void WriteMergedModulesRollupCsv(string OutCsvPath, List<Row> Rows)`
- L1200-1204 _public method_ `public static void WriteMergedModulesRollupCsv(DirectoryReference Root, string OutCsvPath, MergedModulePlatformConfig Cfg)`
- L1207-1218 _private method_ `private static string[] AutoDetectExtensions(DirectoryReference Root)`
- L1221-1231 _private method_ `private static bool IsEager(string Name, HashSet<string> EagerPrefixesUpper)`
- L1234-1248 _private method_ `private static string TryFindPackage(DirectoryInfo Start, string[] Suffixes)`

#### class `ReportItemizedExecutableCode.Automation.MergedModuleScanner.Row`  
`internal sealed class Row`  
_internal; L1114-1122_
- L1116 _public field_ `public string Name = ""`
- L1117 _public field_ `public long Bytes`
- L1118 _public field_ `public double MB`
- L1119 _public field_ `public string Package = ""`
- L1120 _public field_ `public string Bucket = "demand"`
- L1121 _public field_ `public string Path = ""`

### `Source/Programs/AutomationTool/Scripts/ResavePackagesCommand.Automation.cs` (AutomationScripts.Automation)


#### class `AutomationScripts.Automation.ResavePackages`  
`public class ResavePackages : BuildCommand`  
_public; L28-356_
- attrs: `[RequireP4]`
- inherits: `BuildCommand`
- desc: Helper command used for resaving a projects packages.
- L30-68 _public method_ `public override void ExecuteBuild()`
- L70-89 _private method_ `private void BuildNecessaryTargets()`
- L91-99 _private method_ `private int GetLatestCodeChange()`
- L101-108 _private method_ `private void CreateChangelist(ProjectParams Params)`
- L110-170 _private method_ `private void RunResavePackagesCommandlet(ProjectParams Params)`
- L172-184 _private method_ `private void SubmitResavedPackages()`
- L191-208 _private method_ `private bool FoundCheckOutErrorInP4Output(string Output)`
- L213-232 _private method_ `private void HandleFailure(String FailureMessage)`
- L237-247 _private method_ `private void HandleSuccess()`
- L252-285 _private* method_ `void SendCompletionMessage(bool bWasSuccessful, String MessageBody)`
- L288-302 _private* property_ `List<String> StakeholdersEmailAddresses { get; }`
- L305 _private field_ `private int WorkingCL = -1`
- L308-314 _private property_ `private String CommandletTargetName { get; }`
- L317 _private field_ `private FileReference ProjectFullPath`
- L318-355 _public property_ `public virtual FileReference ProjectPath { get; }`

### `Source/Programs/AutomationTool/Scripts/RunProjectCommand.Automation.cs` (AutomationScripts.Automation)


#### class `AutomationScripts.Project`  
`public partial class Project : CommandUtils`  
_public; L35-1095_
- inherits: `CommandUtils`
- desc: Helper command to run a game.
- L40 _private field_ `private static Thread ClientLogReaderThread = null` — Thread used to read client log file.
- L45 _public field_ `public static IProcessResult CookServerProcess` — Process for the cook server, can be set by the cook command when a cook on the fly server is used
- L50 _private field_ `private static IProcessResult DedicatedServerProcess` — Process for the dedicated server
- L53 _public field_ `public static string[] CrashCommands = { "crash", "CHECK", "GPF", "ASSERT", "ENSURE", "RENDERCRASH", "RENDERCHECK", "RENDERGPF", "THREADCRASH", "THREADCHECK", "THREADGPF", }`
- L72-77 _private method_ `private static string GetLogFolderOutsideOfSandbox()` — For not-installed runs, returns a temp log folder to make sure it doesn't fall into sandbox paths
- L82-95 _private method_ `private static void CopyLogsBackToLogFolder()` — For not-installed runs, copies all logs from the temp log folder back to the UAT log folder.
- L97-170 _private method_ `private static bool WaitForProcessReady(IProcessResult Process, string Name, string LogFile, string[] ReadyTexts, int MaxLogWaitTimeInSeconds = -1)`
- L172-230 _public method_ `public static void Run(ProjectParams Params)`
- L232-298 _private method_ `private static void RunInternal( ProjectParams Params, string CookServerLogFile, string DedicatedServerLogFile, string ClientLogFile)`
- L300-318 _private method_ `private static IProcessResult RunClientInternal( ERunOptions ClientRunFlags, string ClientApp, string ClientCmdLine, ProjectParams Params, DeploymentContext SC )`
- L320-591 _private method_ `private static void RunClient( List<DeploymentContext> DeployContextList, string ClientLogFile, ERunOptions ClientRunFlags, string ClientApp, string ClientCmdLine, ProjectParams Params)`
- L593-786 _private method_ `private static void SetupClientParams(List<DeploymentContext> DeployContextList, ProjectParams Params, string ClientLogFile, out ERunOptions ClientRunFlags, out string ClientApp, out string ClientCmdLine)`
- L788-841 _private method_ `private static List<string> GetFileHostAddresses(DeploymentContext SC)`
- L843-876 _private method_ `private static string GetFileHostCommandline(ProjectParams Params, DeploymentContext SC)`
- L878-891 _private method_ `private static void ClientLogReaderProc(object ArgsContainer)`
- L893-1032 _private method_ `private static IProcessResult RunDedicatedServer(ProjectParams Params, string ServerLogFile, string AdditionalCommandLine)`
- L1034-1063 _private method_ `private static IProcessResult RunCookOnTheFlyServer(ProjectParams Params, string ServerLogFile, string AdditionalCommandLine)`
- L1065-1094 _private method_ `private static bool StartUnrealTrace()`

### `Source/Programs/AutomationTool/Scripts/SetSecondaryRemoteMac.Automation.cs` (AutomationScripts.Automation)


#### class `AutomationScripts.SetSecondaryRemoteMac`  
`public class SetSecondaryRemoteMac : BuildCommand`  
_public; L12-37_
- inherits: `BuildCommand`
- L14-36 _public method_ `public override void ExecuteBuild()`

### `Source/Programs/AutomationTool/Scripts/SharedCookedBuild.cs` (AutomationScripts.Automation)


#### class `SharedCookedBuild`  
`public class SharedCookedBuild`  
_public; L18-405_
- L20 _private const_ `private const string SyncedBuildFileName = "SyncedBuild.txt"`
- L49 _private property_ `private FileReference ProjectFile { get; set; }`
- L50 _private property_ `private DirectoryReference InstallPath { get; set; }`
- L51 _private property_ `private HashSet<string> TargetPlatforms { get; set; }`
- L52 _private property_ `private SharedCookType BuildType { get; set; }`
- L53 _private property_ `private List<ISharedCookedBuild> CandidateBuilds { get; set; }`
- L54 _private property_ `private BuildVersion LocalSync { get; set; }`
- L56-66 _public ctor_ `public SharedCookedBuild(ProjectParams Params)`
- L68-71 _public ctor_ `public SharedCookedBuild(FileReference ProjectFile, IEnumerable<string> TargetPlatforms, SharedCookType BuildType)`
- L73-85 _private method_ `private void SharedCookedBuildConstructor(FileReference ProjectFile, IEnumerable<string> Platforms, SharedCookType BuildType)`
- L87-115 _public method_ `public void CopySharedCookedBuilds()`
- L117-139 _public method_ `public static BuildVersion GetLocalSync()`
- L141-220 _public method_ `public List<ISharedCookedBuild> FindBestBuilds()`
- L222-246 _public method_ `public List<ISharedCookedBuild> FindValidManifestBuilds(string Path, string TargetPlatform)`
- L248-280 _public method_ `public List<ISharedCookedBuild> FindValidLooseBuilds(string Path, string TargetPlatform)`
- L283-299 _private method_ `private static bool IsValidCL(int CL, SharedCookType BuildType, BuildVersion Version)`
- L301-308 _private method_ `private static Regex RegexFromWildcards(string Path, BuildVersion Version, string TargetPlatform)`
- L310-315 _private method_ `private static Tuple<string, string> SplitOnFixedPrefix(string Path)`

#### enum `SharedCookedBuild.SharedCookType`  
`public enum SharedCookType`  
_public; L25-41_
- desc: Types of shared cook base builds
- L30 _public* enumerator_ `Exact` — Only allow shared cook build of version identical to local sync
- L35 _public* enumerator_ `Content` — Allow any previous version that is only a content change from local sync
- L40 _public* enumerator_ `Any` — Closest previous version, regardless of code/content changes

#### enum `SharedCookedBuild.SharedCookSource`  
`public enum SharedCookSource`  
_public; L43-47_
- L45 _public* enumerator_ `Manifest`
- L46 _public* enumerator_ `LooseFiles`

#### interface `SharedCookedBuild.ISharedCookedBuild`  
`public interface ISharedCookedBuild`  
_public; L317-322_
- L319 _public* property_ `int CL { get; set; }`
- L320 _public* property_ `string Platform { get; set; }`
- L321 _public* method_ `bool CopyBuild(DirectoryReference InstallPath)`

#### class `SharedCookedBuild.ManifestSharedCookedBuild`  
`private class ManifestSharedCookedBuild : ISharedCookedBuild`  
_private; L324-363_
- inherits: `ISharedCookedBuild`
- L326 _public property_ `public int CL { get; set; }`
- L327 _public property_ `public string Platform { get; set; }`
- L328 _public property_ `public FileReference Manifest { get; set; }`
- L330-362 _public method_ `public bool CopyBuild(DirectoryReference InstallPath)`

#### class `SharedCookedBuild.LooseSharedCookedBuild`  
`private class LooseSharedCookedBuild : ISharedCookedBuild`  
_private; L365-392_
- inherits: `ISharedCookedBuild`
- L367 _public property_ `public int CL { get; set; }`
- L368 _public property_ `public string Platform { get; set; }`
- L369 _public property_ `public DirectoryReference Path { get; set; }`
- L370-391 _public method_ `public bool CopyBuild(DirectoryReference InstallPath)`

#### class `SharedCookedBuild.ExistingSharedCookedBuild`  
`private class ExistingSharedCookedBuild : ISharedCookedBuild`  
_private; L394-404_
- inherits: `ISharedCookedBuild`
- L396 _public property_ `public int CL { get; set; }`
- L397 _public property_ `public string Platform { get; set; }`
- L399-403 _public method_ `public bool CopyBuild(DirectoryReference InstallPath)`

### `Source/Programs/AutomationTool/Scripts/StageLiveLinkHub.Automation.cs` (AutomationScripts.Automation)


#### class `AutomationTool.StageLiveLinkHub`  
`class StageLiveLinkHub : BuildCommand`  
_internal*; L20-222_
- attrs: `[Help("Command to stage livelink hub plugin dependencies for an installed build.")] [Help("Platform=<Platform>", "Target platform for which livelinkhub was built. (required)")] [Help("Verbose", "Whether to stage with verbose logging. (optional)")]`
- inherits: `BuildCommand`
- L23 _private field_ `private DirectoryReference OutputDir`
- L26 _private field_ `private DirectoryReference LiveLinkHubPluginsDirectory`
- L29 _private field_ `private bool Verbose = false`
- L32 _private field_ `private ConfigHierarchy Config`
- L35 _private field_ `private UnrealTargetPlatform TargetPlatform`
- L40-70 _public method_ `public override void ExecuteBuild()` — Entry point for the commandlet
- L73-89 _private method_ `private void StagePlugins()`
- L92-104 _private method_ `private void StageRemappedDependencies()`
- L107-127 _private method_ `private void StageDirectDependencies()`
- L130-145 _private method_ `private void StageRemappedDependency(string RemappedDependencyPath)`
- L148-163 _private method_ `private void StageDirectDependency(string DirectDependencyPath)`
- L166-170 _private method_ `private ConfigHierarchy GetLiveLinkHubConfig()`
- L173-221 _private method_ `private void StagePlugin(string PluginPath)`

### `Source/Programs/AutomationTool/Scripts/StashTarget.cs` (AutomationScripts.Automation)


#### class `AutomationTool.StashTarget`  
`public class StashTarget : BuildCommand`  
_public; L23-65_
- attrs: `[Help("Copy all the binaries for a target into a different folder. Can be restored using the UnstashTarget command. Useful for A/B testing.")] [Help("-Name", "Name of the target")] [Help("-Platform", "Platform that the target was built for")] [Help("-Configuration", "Architecture that the target was built for")] [Help("-Architecture", "Architecture that the target was built for")] [Help("-Project"`
- inherits: `BuildCommand`
- L25-64 _public method_ `public override void ExecuteBuild()`

#### class `AutomationTool.UnstashTarget`  
`public class UnstashTarget : BuildCommand`  
_public; L69-88_
- attrs: `[Help("Copy all the binaries from a target back into the root directory. Use in combination with the StashTarget command.")] [Help("-From", "Directory to copy from")]`
- inherits: `BuildCommand`
- L71-87 _public method_ `public override void ExecuteBuild()`

### `Source/Programs/AutomationTool/Scripts/SyncBinariesFromUGS.Automation.cs` (AutomationScripts.Automation)


#### class `SyncBinariesFromUGS`  
`class SyncBinariesFromUGS : SyncProjectBase`  
_internal*; L21-209_
- attrs: `[Help("Attempts to sync UGS binaries for the specified project at the currently synced CL of the project/engine folders")] [Help("project=<FortniteGame>", "Project to sync. Will search current path and paths in ueprojectdirs.")] [Help("preview", "If specified show actions but do not perform them.")] [RequireP4] [DoesNotNeedP4CL]`
- inherits: `SyncProjectBase`
- L27 _public field_ `public string ProjectArg = ""` — Project name or file that we will sync binaries for
- L32 _public field_ `public bool Preview = false` — If true no actions will be performed
- L34-168 _public method_ `public override ExitCode Execute()`
- L177-208 _private* method_ `string GetZippedBinaryPathFromUGSConfig(DirectoryReference LocalProjectDir, string ProjectDepotPath)` — Returns the depot path used to store zipped biaries for this project by looking in the UnrealGameSync.ini file for an entry matching the stream or depot that contains the project

### `Source/Programs/AutomationTool/Scripts/SyncDDC.cs` (AutomationScripts.Automation)


#### class `AutomationTool.SyncDDC`  
`class SyncDDC : BuildCommand`  
_internal*; L22-529_
- attrs: `[Help("Merge one or more remote DDC shares into a local share, taking files with the newest timestamps and keeping the size below a certain limit")] [Help("LocalDir=<Path>", "The local DDC directory to add/remove files from")] [Help("RemoteDir=<Path>", "The remote DDC directory to pull from. May be specified multiple times.")] [Help("MaxSize=<Size>", "Maximum size of the local DDC directory. TB/MB`
- inherits: `BuildCommand`
- L93-263 _public method_ `public override void ExecuteBuild()` — Execute the command
- L273-331 _private* method_ `static void ForEach<T>(IList<T> Items, Func<T, ConcurrentQueue<string>, Action> CreateAction, string Message, CancellationToken? CancellationToken = null)` — Execute a command for each item in the given list, printing progress messages and queued up error strings
- L339-350 _private* method_ `static void EnumerateFiles(DirectoryInfo BaseDir, string PathPrefix, ConcurrentBag<CacheFile> Files)` — Enumerates all the files in a given directory, and adds them to a bag
- L359-397 _private* method_ `static void CopyFile(CacheFile SourceFile, DirectoryInfo TargetDir, ConcurrentQueue<string> Messages, CopyStats Stats)` — Copies a file from one DDC to another
- L406-447 _private* method_ `static bool TryCopyFile(CacheFile SourceFile, DirectoryInfo TargetDir, out string Message)` — Tries to copy a file from one DDC to another
- L455-466 _private* method_ `static void RemoveFile(DirectoryInfo BaseDir, string RelativePath, ConcurrentQueue<string> Messages)` — Removes a file from the DDC
- L474-500 _private* method_ `static bool TryParseSize(string Text, out long Size)` — Parses a size argument as number of bytes, which may be specified in tb/gb/mb/kb units.
- L508-528 _private* method_ `static bool TryParseTime(string Text, out int TimeSeconds)` — Parses a time argument as number of seconds, which may be specified in h/m/s units.

#### class `AutomationTool.SyncDDC.CacheFile`  
`class CacheFile`  
_private*; L27-72_
- desc: Stores information about a file in the DDC
- L32 _public field_ `public string RelativePath` — Relative path from the root of the DDC store
- L37 _public field_ `public string FullName` — Full path to the actual location on the store
- L42 _public field_ `public long Length` — Size of the file
- L47 _public field_ `public DateTime LastWriteTimeUtc` — Last time the file was written to
- L56-62 _public ctor_ `public CacheFile(string RelativePath, string FullName, long Length, DateTime LastWriteTimeUtc)` — Constructor
- L68-71 _public method_ `public override string ToString()` — Format this object as a string for debugging

#### class `AutomationTool.SyncDDC.CopyStats`  
`class CopyStats`  
_private*; L77-88_
- desc: Statistics for copying files
- L82 _public field_ `public int NumFiles` — The number of files transferred
- L87 _public field_ `public long NumBytes` — The number of bytes transferred

### `Source/Programs/AutomationTool/Scripts/SyncDepotPath.cs` (AutomationScripts.Automation)


#### class `AutomationTool.SyncDepotPath`  
`class SyncDepotPath : BuildCommand`  
_internal*; L16-66_
- attrs: `[Help("Creates a temporary client and syncs a path from Perforce.")] [RequireP4] [DoesNotNeedP4CL]`
- inherits: `BuildCommand`
- L18-65 _public method_ `public override void ExecuteBuild()`

### `Source/Programs/AutomationTool/Scripts/SyncPerforceServers.cs` (AutomationScripts.Automation)


#### class `BuildScripts.Automation.SyncPerforceServers`  
`class SyncPerforceServers : BuildCommand`  
_internal*; L42-338_
- attrs: `[RequireP4] [DoesNotNeedP4CL] [Help("Syncs a clean clientspec (should NOT be the client you are running this out of), and mirrors it into another p4 server via 3 streams. See the SyncPerforceServers.cs for details")] [Help("SourceClient=<client>", "p4 client on the source server (which is the active server that normal UAT p4 scripts would use")] [Help("Server=<server:port>", "p4 server for the tar`
- inherits: `BuildCommand`
- L44-63 _protected method_ `protected P4ClientInfo GetClientInfoForParent(P4Connection Connection, string User, string StreamName, string ClientDesc)`
- L65-337 _public method_ `public override void ExecuteBuild()`

### `Source/Programs/AutomationTool/Scripts/SyncProject.Automation.cs` (AutomationScripts.Automation)


#### class `SyncProjectBase`  
`abstract class SyncProjectBase : BuildCommand`  
_internal*; L15-89_
- inherits: `BuildCommand`
- L17-83 _protected method_ `protected bool FindProjectFileAndP4Path(string InProjectArgument, out FileReference OutProjectFile, out string OutP4ProjectPath)`
- L85-88 _protected method_ `protected P4WhereRecord GetP4RecordForPath(string FilePath)`

#### class `SyncProject`  
`class SyncProject : SyncProjectBase`  
_internal*; L108-354_
- attrs: `[Help("Syncs and builds all the binaries required for a project")] [Help("project=<FortniteGame>", "Project to sync. Will search current path and paths in ueprojectdirs. If omitted will sync projectdirs")] [Help("threads=N", "How many threads to use when syncing. Default=2. When >1 all output happens first")] [Help("cl=<12345>", "Changelist to sync to. If omitted will sync to latest CL of the work`
- inherits: `SyncProjectBase`
- L110-353 _public method_ `public override ExitCode Execute()`

### `Source/Programs/AutomationTool/Scripts/UnrealBuildUtils.cs` (AutomationScripts.Automation)


#### class `UnrealBuildUtils`  
`public class UnrealBuildUtils : CommandUtils`  
_public; L14-62_
- inherits: `CommandUtils`
- desc: Common UEBuild utilities
- L21-30 _public method_ `public static void BuildBuildPatchTool(BuildCommand Command, UnrealBuildTool.UnrealTargetPlatform InPlatform)` — Builds BuildPatchTool for the specified platform.
- L32-53 _private method_ `private static void BuildProduct(BuildCommand Command, UnrealBuild.BuildTarget Target)`

#### class `UnrealBuildUtils.UnrealBuildUtilDummyBuildCommand`  
`class UnrealBuildUtilDummyBuildCommand : BuildCommand`  
_private*; L55-61_
- inherits: `BuildCommand`
- L57-60 _public method_ `public override void ExecuteBuild()`

### `Source/Programs/AutomationTool/Scripts/UnsignedFilesViolationCheck.Automation.cs` (AutomationScripts.Automation)


#### class `UnsignedFilesViolationCheck`  
`public class UnsignedFilesViolationCheck : BuildCommand`  
_public; L17-103_
- inherits: `BuildCommand`
- desc: Unsigned files violation check
- L24-34 _public method_ `public static void RunPowershellCommand(string Command, string WorkingDirectory)` — Runs powershell command.
- L41-61 _private* method_ `static (int, List<string>) CheckWordInOutput(string OutputFile, string ExpectedWord)` — Checks expected word in file.
- L63-102 _public method_ `public override void ExecuteBuild()`

### `Source/Programs/AutomationTool/Scripts/UpdateLocalVersion.Automation.cs` (AutomationScripts.Automation)


#### class `UpdateLocalVersion`  
`public class UpdateLocalVersion : BuildCommand`  
_public; L17-32_
- attrs: `[Help("Updates your local versions based on your P4 sync")] [Help("CL", "Overrides the automatically disovered changelist number with the specified one")] [Help("CompatibleCL", "Overrides the changelist that the engine is API-compatible with")] [Help("Promoted", "Value for whether this is a promoted build (defaults to 1).")] [Help("Branch", "Overrides the branch string.")] [Help("Licensee", "When `
- inherits: `BuildCommand`
- L19-31 _public method_ `public override void ExecuteBuild()`

### `Source/Programs/AutomationTool/Scripts/UpdateRobomergeGate.cs` (AutomationScripts.Automation)


#### class `BuildScripts.Automation.UpdateRoboMergeGate`  
`class UpdateRoboMergeGate : BuildCommand`  
_internal*; L26-176_
- attrs: `[Help("Tool for updating a gate for robomerge")] [Help("Stream=<Name>", "Stream that contains the gate")] [Help("Change=<value>", "Change to set in the gate")] [Help("File=<Path>", "Path to update (relative to Stream)")] [Help("Client=<Name>", "The Perforce client to use")] [Help("UpdateIfLater", "Only write the gate if the current time is later or equal to this (HH:MM, default 00:00)")] [Help("Up`
- inherits: `BuildCommand`
- L28-175 _public method_ `public override void ExecuteBuild()`

### `Source/Programs/AutomationTool/Scripts/UploadDDCToAWS.cs` (AutomationScripts.Automation)


#### class `AutomationTool.UploadDDCToAWS`  
`class UploadDDCToAWS : BuildCommand`  
_internal*; L27-833_
- inherits: `BuildCommand`
- L169 _protected const_ `protected const uint BundleSignature = (uint)'D' | ((uint)'D' << 8) | ((uint)'B' << 16)`
- L170 _protected const_ `protected const uint BundleSignatureV1 = BundleSignature | (1 << 24)`
- L171 _protected const_ `protected const long MinBundleSize = 40 * 1024 * 1024`
- L172 _protected const_ `protected const long MaxBundleSize = 100 * 1024 * 1024`
- L174 _private* field_ `static readonly Amazon.RegionEndpoint Region = Amazon.RegionEndpoint.USEast1`
- L176-610 _public method_ `public override void ExecuteBuild()`
- L612-616 _private method_ `private string CreateObjectName()`
- L618-649 _private method_ `private bool TryDownloadFile(AmazonS3Client Client, string BucketName, string Key, FileReference OutputFile)`
- L651-661 _private method_ `private void DecompressFile(FileReference CompressedFile, FileReference UncompressedFile)`
- L663-679 _private method_ `private void ReadFileInfo(DirectoryReference BaseDir, string Path, ConcurrentBag<DerivedDataFile> Files)`
- L681-692 _private method_ `private void ReadFileData(DerivedDataFile DerivedDataFile, ConcurrentBag<Tuple<DerivedDataFile, byte[]>> FilesToInclude)`
- L694-718 _protected method_ `protected void ParallelExecute(IEnumerable<Action> Actions)`
- L720-725 _protected method_ `protected List<U> ParallelExecute<T, U>(IEnumerable<T> Source, Action<T, ConcurrentBag<U>> Transform)`
- L727-741 _protected method_ `protected void UploadFile(AmazonS3Client Client, string BucketName, FileReference File, long Length, string Key, SemaphoreSlim Semaphore, UploadState State)`
- L743-769 _protected method_ `protected void UploadFileInner(AmazonS3Client Client, string BucketName, FileReference File, long Length, string Key, SemaphoreSlim Semaphore, UploadState State)`
- L771-781 _protected method_ `protected void DeleteFile(AmazonS3Client Client, string BucketName, string Key, SemaphoreSlim Semaphore, DeleteState State)`
- L783-802 _protected method_ `protected void DeleteFileInner(AmazonS3Client Client, string BucketName, string Key, SemaphoreSlim Semaphore, DeleteState State)`
- L804-807 _protected method_ `protected void Retry(Action ActionToRetry, int MaxAttempts)`
- L809-832 _protected method_ `protected T Retry<T>(Func<T> FuncToRetry, int MaxAttempts)`

#### class `AutomationTool.UploadDDCToAWS.DerivedDataFile`  
`class DerivedDataFile`  
_private*; L29-48_
- L31 _public property_ `public FileInfo Info { get; }`
- L32 _public property_ `public string Key { get; }`
- L33 _public property_ `public ContentHash KeyHash { get; }`
- L35-40 _public ctor_ `public DerivedDataFile(FileInfo Info, string Key)`
- L42-47 _public method_ `public static ContentHash GetKeyHash(string Key)`

#### class `AutomationTool.UploadDDCToAWS.BundleManifest`  
`class BundleManifest`  
_private*; L50-103_
- L61 _public field_ `public List<Entry> Entries = new List<Entry>()`
- L63-76 _public method_ `public void Read(JsonObject Object)`
- L78-84 _public method_ `public void Save(FileReference File)`
- L86-102 _public method_ `public void Write(JsonWriter Writer)`

#### class `AutomationTool.UploadDDCToAWS.BundleManifest.Entry`  
`public class Entry`  
_public; L52-59_
- L54 _public field_ `public string Name`
- L55 _public field_ `public string ObjectKey`
- L56 _public field_ `public DateTime Time`
- L57 _public field_ `public int CompressedLength`
- L58 _public field_ `public int UncompressedLength`

#### class `AutomationTool.UploadDDCToAWS.RootManifest`  
`public class RootManifest`  
_public; L105-156_
- L113 _public field_ `public string AccessKey`
- L114 _public field_ `public string SecretKey`
- L115 _public field_ `public List<Entry> Entries = new List<Entry>()`
- L117-130 _public method_ `public void Read(JsonObject Object)`
- L132-138 _public method_ `public void Save(FileReference File)`
- L140-155 _public method_ `public void Write(JsonWriter Writer)`

#### class `AutomationTool.UploadDDCToAWS.RootManifest.Entry`  
`public class Entry`  
_public; L107-111_
- L109 _public field_ `public DateTime CreateTime`
- L110 _public field_ `public string Key`

#### class `AutomationTool.UploadDDCToAWS.UploadState`  
`protected class UploadState`  
_protected; L158-162_
- L160 _public field_ `public int NumFiles`
- L161 _public field_ `public long NumBytes`

#### class `AutomationTool.UploadDDCToAWS.DeleteState`  
`protected class DeleteState`  
_protected; L164-167_
- L166 _public field_ `public int NumFiles`

### `Source/Programs/AutomationTool/Scripts/Virtualization.Automation.cs` (AutomationScripts.Automation)


#### class `AutomationScripts.Automation.VirtualizationBase`  
`public abstract class VirtualizationBase : BuildCommand`  
_public; L19-163_
- attrs: `[RequireP4]`
- inherits: `BuildCommand`
- L21-24 _protected ctor_ `protected VirtualizationBase(string InCommandletName)`
- L25-60 _public method_ `public override void ExecuteBuild()`
- L62 _protected method_ `protected abstract void RunCommandlet(ProjectParams Params)`
- L63-67 _private method_ `private void BuildEditor(ProjectParams Params)`
- L69-87 _private method_ `private void ParseProjectPerforceCommandline()`
- L89-96 _private method_ `private void CreateChangelist(ProjectParams Params)`
- L98-112 _private method_ `private void SubmitPackages()`
- L114-134 _private method_ `private void HandleFailure()`
- L136-152 _public property_ `public virtual FileReference ProjectPath { get; }`
- L154 _private field_ `private string CommandletName`
- L156 _private field_ `private P4Connection ProjectP4`
- L158 _protected field_ `protected string ProjectP4Client`
- L160 _private field_ `private FileReference ProjectFullPath`
- L162 _protected field_ `protected int WorkingCL = -1`

#### class `AutomationScripts.Automation.RehydrateProject`  
`public class RehydrateProject : VirtualizationBase`  
_public; L165-192_
- inherits: `VirtualizationBase`
- L172-176 _public ctor_ `public RehydrateProject() : base("Rehydrate Project")` — attrs: `[Help("Rehydrates all eligible packages in the given project")] [Help("Usage: RehydrateProject -Project=\"???\" -ProjectP4Client=\"???\" -Submit")] [Help("-Project=???", "Path to the .uproject file of the project you want to rehydrate ")] [`
- L177-191 _protected method_ `protected override void RunCommandlet(ProjectParams Params)`

#### class `AutomationScripts.Automation.VirtualizeProject`  
`public class VirtualizeProject : VirtualizationBase`  
_public; L199-221_
- attrs: `[Help("Virtualizes all eligible packages in the given project")] [Help("Usage: VirtualizeProject -Project=\"???\" -ProjectP4Client=\"???\" -Submit")] [Help("-Project=???", "Path to the .uproject file of the project you want to virtualize ")] [Help("-ProjectP4Client=???", "[Optional] The p4 client spec (workspace) to use to checkout & submit the packages.")] [Help("-Submit", "[Optional] Submit the `
- inherits: `VirtualizationBase`
- L201-205 _public ctor_ `public VirtualizeProject() : base("Virtualize Project")`
- L206-220 _protected method_ `protected override void RunCommandlet(ProjectParams Params)`

### `Source/Programs/AutomationTool/Scripts/WorldPartitionBuilder.Automation.cs` (AutomationScripts.Automation)


#### class `AutomationScripts.Automation.WorldPartitionBuilder`  
`public class WorldPartitionBuilder : BuildCommand`  
_public; L17-76_
- attrs: `[Help("Execute a World Partition builder")] [Help("Builder=<Name>", "Name of the builder to run")] [Help("CommandletArgs=<value>", "Arguments to provide to the builder commandlet")] [Help("Submit", "If the files modified by the builder should be submitted at the end of the process")] [Help("ShelveUser=<Name>", "If provided (along with -ShelveWorkspace, modified files will be shelved for the P4 Use`
- inherits: `BuildCommand`
- L19-75 _public method_ `public override void ExecuteBuild()`

### `Source/Programs/AutomationTool/Scripts/WrangleContentForDebugging.Automation.cs` (AutomationScripts.Automation)


#### class `AutomationScripts.WrangleContentForDebugging`  
`public class WrangleContentForDebugging : BuildCommand`  
_public; L12-38_
- inherits: `BuildCommand`
- L14-37 _public method_ `public override void ExecuteBuild()`

### `Source/Programs/AutomationTool/Scripts/ZipUtils.Automation.cs` (AutomationScripts.Automation)


#### class `ZipUtils`  
`public class ZipUtils : BuildCommand`  
_public; L18-164_
- attrs: `[Help("ZipUtils is used to zip/unzip (i.e:RunUAT.bat ZipUtils -archive=D:/Content.zip -add=D:/UE/Pojects/SampleGame/Content/) or (i.e:RunUAT.bat ZipUtils -archive=D:/Content.zip -extract=D:/UE/Pojects/SampleGame/Content/)")] [Help("archive=<PathToArchive>", "Path to folder that should be add to the archive.")] [Help("add=<Path>", "Path to folder that should be add to the archive.")] [Help("extract`
- inherits: `BuildCommand`
- L20-105 _public method_ `public override ExitCode Execute()`
- L114-132 _internal method_ `internal static void InternalZipFiles(FileReference ZipFileName, DirectoryReference BaseDirectory, FileFilter Filter, int CompressionValue = 0)` — Creates a zip file containing the given input files
- L140-163 _public method_ `public static IEnumerable<string> InternalUnzipFiles(string ZipFileName, string BaseDirectory)` — Extracts the contents of a zip file
