# CSharp / AutomatedPerfTesting.Automation

- project root: `Plugins/Performance/AutomatedPerfTesting/Build/Scripts`
- files: 4; symbols: 138
- symbol kinds: class=11, ctor=7, field=55, interface=2, method=54, property=9
- access marked `*` is implicit (not written in source)

### `Plugins/Performance/AutomatedPerfTesting/Build/Scripts/AutomatedPerfTest.Bridge.cs` (AutomatedPerfTesting.Automation)


#### interface `AutomatedPerfTest.ITestBridge`  
`public interface ITestBridge`  
_public; L34-64_
- desc: Interface to be used if a project wants to configure the Automated Perf Test context, roles and/or config without making intrusive changes to the main node before launching the test. Ideally project/game specific command line parameters get set here.
- L41 _public* method_ `void Configure(UnrealTestContext Context, AutomatedPerfTestConfigBase Config)` — Initial configure call. This is invoked first.
- L49 _public* method_ `void ConfigureClient(UnrealTestRole Role, UnrealTestContext Context, AutomatedPerfTestConfigBase Config)` — Configure client role
- L57 _public* method_ `void ConfigureServer(UnrealTestRole Role, UnrealTestContext Context, AutomatedPerfTestConfigBase Config)` — Configure server role. This is invoked optionally if a server role is required for the test.
- L63 _public* method_ `bool IsServerRoleRequired()` — If this is true, server role is instantiated and configured.

#### class `AutomatedPerfTest.NullBridge`  
`public class NullBridge : ITestBridge`  
_public; L69-69_
- inherits: `ITestBridge`
- desc: Null Test Bridge

#### class `AutomatedPerfTest.AutoTestBridge`  
`public static class AutoTestBridge`  
_public; L76-225_
- desc: Static helper class to activate and invoke test bridge configuration functions.
- L78 _private field_ `private static HashSet<ITestBridge> Bridges = new HashSet<ITestBridge>()`
- L84-91 _public method_ `public static void Initialize(IEnumerable<string> InConfigBridges)` — Initialize Test Bridge instances with given list of Bridge class names.
- L93-100 _public method_ `public static void AddBridge(ITestBridge ConfigBridge)`
- L102-114 _private method_ `private static ITestBridge GetConfigBridge(string ConfigBridgeName)`
- L116-119 _public method_ `public static void Configure(UnrealTestContext Context, AutomatedPerfTestConfigBase Config)`
- L121-124 _public method_ `public static void ConfigureClient(UnrealTestRole Role, UnrealTestContext Context, AutomatedPerfTestConfigBase Config)`
- L126-129 _public method_ `public static void ConfigureServer(UnrealTestRole Role, UnrealTestContext Context, AutomatedPerfTestConfigBase Config)`
- L131-134 _public method_ `public static bool IsServerRoleRequired()`
- L136-170 _private method_ `private static bool ValidateAttributes(Type TestBridge, string ProjectName = "")`
- L187-224 _public method_ `public static void ActivateTestBridges(Type CurrentTestType, string ProjectName = "")` — Registers valid Test Bridge types which will then be used to configure the test depending on the need of the test and/or project. Following attributes used for validation: [AutoBridge] - This enables the bridge for all automated perf tests. [AutoBridgeForTest[CurrentTestType]] - This enables the bridge only for the specified test type. Multiple types are supported. [EnableForProject] - Ensures the bridge is only enabled for a given project. [EnableForParams]

#### class `AutomatedPerfTest.AutoBridge`  
`public class AutoBridge : Attribute`  
_public; L234-237_
- attrs: `[AttributeUsage(AttributeTargets.Class, AllowMultiple = false)]`
- inherits: `Attribute`
- desc: Automatically activate given Test Bridge for all Automated Perf Tests. If this is the only attribute present, it will be added to all tests by default. Example: [AutoBridge]
- L236 _public ctor_ `public AutoBridge()`

#### class `AutomatedPerfTest.AutoBridgeForTestAttribute`  
`public class AutoBridgeForTestAttribute<T> : Attribute where T : IAutomatedPerfTest`  
_public; L246-255_
- attrs: `[AttributeUsage(AttributeTargets.Class, AllowMultiple = true)]`
- inherits: `Attribute`
- constraints: `where T : IAutomatedPerfTest`
- desc: Automatically activate given Test Bridge for given Automated Perf Test type. If this is the only attribute present, it will be added to all instances of a given test type. Example: [AutoBridgeForTest[ReplayTest]]
- L249 _public property_ `public Type TestType { get; set; }`
- L251-254 _public ctor_ `public AutoBridgeForTestAttribute()`

#### class `AutomatedPerfTest.EnableForProjectAttribute`  
`public class EnableForProjectAttribute : Attribute`  
_public; L266-274_
- attrs: `[AttributeUsage(AttributeTargets.Class, AllowMultiple = true)]`
- inherits: `Attribute`
- desc: Ensures test bridge is activated only for a given project. This ensures if a given bridge is very specific and/or does not apply to any other project it can only be activated for that project. This should be combined with one of the AutoBridge attribute types to ensure auto-activation of the bridge. Example: [EnableForProject("MyProjectName")]
- L268 _public property_ `public string ProjectName { get; set; }`
- L270-273 _public ctor_ `public EnableForProjectAttribute(string InProjectName)`

#### class `AutomatedPerfTest.EnableForParamsAttribute`  
`public class EnableForParamsAttribute : Attribute`  
_public; L282-293_
- attrs: `[AttributeUsage(AttributeTargets.Class, AllowMultiple = true)]`
- inherits: `Attribute`
- desc: If a test bridge only applies for a very specific set of parameters, they can be specified here. Example: [EnableForParams("Mode=Test", "SomeBoolVal", ...)]
- L284 _public property_ `public List<KeyValuePair<string, string>> Params { get; set; }`
- L286-292 _public ctor_ `public EnableForParamsAttribute(params string[] InParams)`

### `Plugins/Performance/AutomatedPerfTesting/Build/Scripts/AutomatedPerfTest.Util.cs` (AutomatedPerfTesting.Automation)


#### class `AutomatedPerfTesting.Util`  
`internal static class Util`  
_internal; L13-109_
- desc: Internal Utility Class
- L15 _private field_ `private static Assembly[] AssemblyCache = null`
- L17-25 _private method_ `private static Assembly[] GetAssemblies()`
- L32-49 _public method_ `public static Type[] GetTypes(Func<Type, bool> Predicate)` — Get array of types which match the given predicate.
- L57-60 _public method_ `public static Type GetTypeWithInterface<TInterface>(string Name)` — Get reflected Type info of given type name if available.
- L69-86 _public method_ `public static Type GetTypeByName(string Name, Type InterfaceType = null)` — Get reflected Type info of given type name if available. Searches assemblies in current app domain.
- L94-98 _public method_ `public static Type[] GetTypesWithInterface<TInterface>()` — Get array of types which is assignable from given interface type.
- L100-103 _public method_ `public static Type[] GetTypesWithAttribute<TAttribute>()`
- L105-108 _public method_ `public static Type[] GetTypesWithAttribute(Type AttributeType)`

### `Plugins/Performance/AutomatedPerfTesting/Build/Scripts/AutomatedPerfTestConfig.cs` (AutomatedPerfTesting.Automation)


#### class `AutomatedPerfTest.AutomatedPerfTestConfigBase`  
`public class AutomatedPerfTestConfigBase : EpicGameTestConfig`  
_public; L15-377_
- inherits: `EpicGameTestConfig`
- L30 _public field_ `public string DataSourceProjectNameOverride = ""` — attrs: `[AutoParamWithNames("AutomatedPerfTest.DataSourceProjectNameOverride")]` — Used to override the project name portion of the data source name Will be inserted into Automation.{dataSourceProjectName}.{dataSourceType} to construct the full data source name for the test. This is useful when the actual project differs from the name displayed downstream in dashboards. Values must follow rules similar to standard ProjectNames: 1. Must start with a letter. 2. Can only use alpha numeric characters and _. 3. Must be 20 characters or less. The full string can be overridden with AutomatedPerfTest.DataSourceNameOverride
- L39 _public field_ `public string DataSourceTypeOverride = ""` — attrs: `[AutoParamWithNames("AutomatedPerfTest.DataSourceTypeOverride")]` — Used to override the test controller portion of the data source name Will be appended to Automation.ProjectName to construct the full data source name for the test The full string can be overridden with AutomatedPerfTest.DataSourceNameOverride
- L45 _public field_ `public string DataSourceNameOverride = ""` — attrs: `[AutoParamWithNames("AutomatedPerfTest.DataSourceNameOverride")]` — Fully override the data source name
- L51 _public field_ `public string TestID = ""` — attrs: `[AutoParamWithNames("AutomatedPerfTest.TestID")]` — Name of the test, useful for identifying it later
- L57 _public field_ `public bool DoInsightsTrace` — attrs: `[AutoParamWithNames(false, "AutomatedPerfTest.DoInsightsTrace")]` — If data from the test should be gathered with Unreal Insights
- L63 _public field_ `public string TraceChannels = "default,screenshot,stats"` — attrs: `[AutoParamWithNames("AutomatedPerfTest.TraceChannels")]` — Which trace channels to test with
- L69 _public field_ `public bool DoCSVProfiler` — attrs: `[AutoParamWithNames(false, "AutomatedPerfTest.DoCSVProfiler")]` — If data from the test should be gathered with the CSV Profiler
- L75 _public field_ `public bool DoFPSChart` — attrs: `[AutoParamWithNames(false, "AutomatedPerfTest.DoFPSChart")]` — If data from the test should be gathered with FPS Charts
- L81 _public field_ `public bool WaitForAttach` — attrs: `[AutoParamWithNames(false, "AutomatedPerfTest.WaitForAttach")]` — Whether to wait for a debugger to attach to an APT launched test
- L87 _public field_ `public string NullOSSPlatforms` — attrs: `[AutoParamWithNames("AutomatedPerfTest.NullOSSPlatforms")]` — List of '+' separated platforms on which to use the null online subsystem service
- L93 _public field_ `public bool DoLLM` — attrs: `[AutoParamWithNames(false, "AutomatedPerfTest.DoLLM")]` — Whether to run the test with -llm
- L99 _public field_ `public bool DoGPUPerf` — attrs: `[AutoParamWithNames(false, "AutomatedPerfTest.DoGPUPerf")]` — Whether to run GPU perf test, that is, dynres is fixed, while GPU async work gets reduced, serializing passes to be timed separately
- L105 _public field_ `public bool DoGPUReshape` — attrs: `[AutoParamWithNames(false, "AutomatedPerfTest.DoGPUReshape")]` — Whether to run GPU Reshape's instrumentation on the target
- L111 _public field_ `public string GPUReshapeWorkspace` — attrs: `[AutoParamWithNames("BasicWorkspace", "AutomatedPerfTest.GPUReshapeWorkspace")]` — The assigned GPU Reshape workspace
- L117 _public field_ `public bool DoBuildZenStreaming` — attrs: `[AutoParamWithNames(false, "AutomatedPerfTest.DoBuildZenStreaming")]` — Whether to run Zen Streaming Import tests with -DoBuildZenStreaming
- L123 _public field_ `public bool Deterministic` — attrs: `[AutoParamWithNames(true, "AutomatedPerfTest.Deterministic")]` — If enabled, runs with -deterministic
- L129 _public field_ `public string ZenStoreHost` — attrs: `[AutoParamWithNames("", "AutomatedPerfTest.ZenStoreHost")]` — The IP/Web Address of the Zen Server
- L135 _public field_ `public string ZenStorePort` — attrs: `[AutoParamWithNames("", "AutomatedPerfTest.ZenStorePort")]` — The port of the Zen Server
- L141 _public field_ `public string ZenStoreProject` — attrs: `[AutoParamWithNames("", "AutomatedPerfTest.ZenStoreProject")]` — The project identifier for the Zen Server
- L147 _public field_ `public string ZenStorePlatform` — attrs: `[AutoParamWithNames("", "AutomatedPerfTest.ZenStorePlatform")]` — The platform identifier for the Zen Server
- L153 _public field_ `public bool DoLocalZenTest` — attrs: `[AutoParamWithNames(false, "AutomatedPerfTest.DoLocalZenTest")]` — Whether or not to run a test against a local Zen Server
- L159 _public field_ `public bool LockDynamicRes` — attrs: `[AutoParamWithNames(false,"AutomatedPerfTest.LockDynamicRes")]` — Whether to lock dynamic resolution. This is applied automatically when GPUPerf test is run.
- L165 _public field_ `public string PerfOutputPath` — attrs: `[AutoParamWithNames("", "AutomatedPerfTest.PerfOutputPath")]` — Path where Perf Test artifacts (Logs, CSVs, Reports, Cache) will be stored.
- L171 _public field_ `public string PerfCacheRoot` — attrs: `[AutoParamWithNames("", "AutomatedPerfTest.PerfCacheRoot")]` — Let BuildGraph tell us where we should output the Insights trace after running a test so that we know where to grab it from when we're done
- L177 _public field_ `public string IgnoredIssuesConfigAbsPath` — attrs: `[AutoParamWithNames("", "AutomatedPerfTest.IgnoredIssuesConfigAbsPath")]` — Path to a JSON file with ignored issues (ensures, warnings, errros). Can be used to suppress hard-to-fix issues, on a per-branch basis
- L183 _public field_ `public bool DoVideoCapture` — attrs: `[AutoParamWithNames(false, "AutomatedPerfTest.DoVideoCapture")]` — If we should trigger a video capture
- L190 _public field_ `public bool UseShippingInsights` — attrs: `[AutoParamWithNames(false, "AutomatedPerfTest.UseShippingInsights")]` — If true, will look for the shipping configuration of Unreal Insights in order to parse Insights trace files This should be True unless you need to test an issue in parsing the Insights file itself.
- L197 _public field_ `public bool WaitForDebugger` — attrs: `[AutoParamWithNames(false, "AutomatedPerfTest.WaitForDebugger")]` — If true, this will pass `-WaitForDebugger` to Client command line parameters. This is helpful for local testing and local dev iteration.
- L204 _public field_ `public string ReportConfigDir` — attrs: `[AutoParamWithNames("", "AutomatedPerfTest.ReportConfigDir")]` — Used to find the report type and report graph xmls for generating local reports Defaults to those provided in the AutomatedPerfTesting plugin
- L210 _public field_ `public string ReportPath` — attrs: `[AutoParamWithNames("", "AutomatedPerfTest.ReportPath")]` — Used to specify where performance reports should be saved
- L218 _public field_ `public bool UsePlatformExtraDebugMemory` — attrs: `[AutoParamWithNames(false, "AutomatedPerfTest.UsePlatformExtraDebugMemory")]` — Specify whether this test requires additional debug memory on target device. The allocation of this memory is entirely dependent on the target device and may not be guaranteed.
- L227 _public field_ `public bool IgnoreTestBuildLogging` — attrs: `[AutoParamWithNames(true, "AutomatedPerfTest.IgnoreTestBuildLogging")]` — If true, logs will not be considered when passing or failing a test in Test builds. Useful if logging is disabled in Test builds and we do not want to fail the test if no logs are found.
- L233 _public field_ `public string TestConfigName = ""` — attrs: `[AutoParamWithNames("", "AutomatedPerfTest.TestConfigName")]` — Used to specify a different test name in the CSV meta data, primarily used to distinguish between RHIs
- L239 _public field_ `public string TestBuildVersion = ""` — attrs: `[AutoParamWithNames("", "AutomatedPerfTest.TestBuildVersion")]` — Overrides test build version. If empty, default build version will be used.
- L245 _public field_ `public string BuildVersion = ""` — attrs: `[AutoParamWithNames("", "AutomatedPerfTest.BuildVersion")]` — Overrides build version. If empty, default build version will be used.
- L251 _public field_ `public string ConfigBridges = ""` — attrs: `[AutoParamWithNames("AutomatedPerfTest.NullBridge", "AutomatedPerfTest.ConfigBridges")]` — Comma separated list of Bridges which will be initialized and invoked during configuration.
- L257 _public field_ `public string ManagedAcountPool` — attrs: `[AutoParamWithNames("", "AutomatedPerfTest.ManagedAccountPool")]` — Overrides managed account pool instance with the one provided.
- L263 _public field_ `public string CVars` — attrs: `[AutoParamWithNames("", "AutomatedPerfTest.CVars")]` — Optional CVars to be passed to client, comma separated.
- L271 _public field_ `public bool OverrideArtifactOutputPath` — attrs: `[AutoParamWithNames(false, "AutomatedPerfTest.OverrideArtifactPath")]` — Overrides default artifact output path by passing the artifact path to the client instance. This is useful if the project has set the artifact to output to a non-standard default output path causing report generation to fail because of missing CSV artifacts.
- L273 _public field_ `public string DataSourceName`
- L281-312 _public method_ `public string GetDataSourceName(string ProjectName, string DataSourceType="")` — Call this in the test node's GetConfiguration function to set the DataSourceName used for later data processing
- L314-325 _public method_ `public override void ApplyToConfig(UnrealAppConfig AppConfig, UnrealSessionRole ConfigRole, IEnumerable<UnrealSessionRole> OtherRoles)`
- L333-376 _private method_ `private bool IsProjectNameLike(string ProjectName, out string OutFailReason)` — Validation function to ensure a project name override is valid. This mirrors relevant validation in GameProjectUtils::IsValidProjectFileForCreation valid overrides should follow the same set of constraints.

### `Plugins/Performance/AutomatedPerfTesting/Build/Scripts/AutomatedPerfTestNode.cs` (AutomatedPerfTesting.Automation)


#### interface `AutomatedPerfTest.IAutomatedPerfTest`  
`public interface IAutomatedPerfTest`  
_public; L24-27_
- L26 _public* method_ `List<string> GetTestsFromConfig()`

#### class `AutomatedPerfTest.AutomatedPerfTestNode`  
`public abstract class AutomatedPerfTestNode<TConfigClass> : UnrealTestNode<TConfigClass> where TConfigClass : AutomatedPerfTestConfigBase, new()`  
_public; L33-1448_
- inherits: `UnrealTestNode<TConfigClass>`
- constraints: `where TConfigClass : AutomatedPerfTestConfigBase, new()`
- desc: Implementation of a Gauntlet TestNode for AutomatedPerfTest plugin
- L36 _public field_ `public string SummaryTable = "default"`
- L37-51 _public ctor_ `public AutomatedPerfTestNode(UnrealTestContext InContext) : base(InContext)`
- L53-57 _public method_ `public override bool StartTest(int Pass, int InNumPasses)`
- L84 _private field_ `private readonly bool ForceArchiveDevArtifacts = true` — Should we archive dev artifacts even if -dev is passed down.
- L89 _public property_ `public List<HandledError> HandledErrors { get; set; }` — List of errors with special-cased gauntlet messages.
- L94 _public property_ `public Guid TestGuid { get; set; }` — Guid associated with each test run for ease of differentiation between different runs on same build.
- L99 _public property_ `public string BaseOutputPath { get; set; }` — Base artifact output path for current instance of this test node.
- L104 _public property_ `public string HordeJobLink { get; set; }` — The Horde job link.
- L111-119 _public method_ `public string GetPerformanceReportArtifactOutputPath(UnrealTargetPlatform Platform, TConfigClass Config = null)` — Returns the APT Performance Artifact Path.
- L124 _private field_ `private UnrealLogStreamParser LogParser` — Track client log messages that have been written to the test logs.
- L129 _private property_ `private DirectoryInfo TempPerfCSVDir => ...`
- L134 _private field_ `private string OriginalBuildName = null`
- L139 _private field_ `private bool GenerateLocalReport = false` — If true, local reports will be generated at the end of the perf test.
- L145 _private field_ `private bool GeneratePRSReport = false` — If true, the resulting CSV files will be imported via Perf Report Server importer.
- L150 _private field_ `private bool GenerateHordeTelemetry = false` — If true, the resulting CSV files will be emitted to Horde Telemetry.
- L155 _private field_ `private bool IsPRSAdded = false` — To ensure that PRS report is added only once per report
- L160-163 _protected method_ `protected virtual void InitHandledErrors()` — Set up the base list of possible expected errors, plus the messages to deliver if encountered.
- L165 _protected method_ `protected virtual string GetNormalizedInsightsFileName(string FileName)`
- L167-181 _protected method_ `protected string GetNormalizedInsightsFileName(string CSVFileName, string TestTypeLiteral)`
- L186-234 _public method_ `public override void TickTest()` — Periodically called while test is running. Updates logs.
- L242-284 _protected method_ `protected override UnrealLog CreateLogSummaryFromArtifact(UnrealRoleArtifacts InArtifacts)` — This allows using a per-branch config to ignore certain issues that were inherited from Main and will be addressed there
- L286-346 _protected method_ `protected override UnrealProcessResult GetExitCodeAndReason(StopReason InReason, UnrealLog InLogSummary, UnrealRoleArtifacts InArtifacts, out string ExitReason, out int ExitCode)`
- L348-553 _public method_ `public override ITestReport CreateReport(TestResult Result, UnrealTestContext Context, UnrealBuildSource Build, IEnumerable<UnrealRoleResult> Artifacts, string ArtifactPath)`
- L556 _protected property_ `protected override string HordeReportTestKey => ...` — (inheritdoc)
- L562-567 _protected method_ `protected virtual string CreateTestIdentity(TConfigClass Config = null)` — Gets the test identity of the AutomatedPerfTestNode{TConfigClass}.
- L575-592 _private method_ `private void GetReportType(out string ReportType, out string SummaryTableType, out string HistoricalReportType)` — Get report type for current configuration
- L598-779 _private method_ `private bool GenerateLocalPerfReport(UnrealTargetPlatform Platform, string OutputPath)` — Produces a detailed csv report using PerfReportTool. Also, stores perf data in the perf cache, and generates a historic report using the data the cache contains.
- L789-876 _private method_ `private bool GenerateHordePerfReportTelemetry(UnrealTargetPlatform Platform, string TestIdentity, string OutputPath, string SummaryTable = "KeyStats")` — Emits performance trend telemetry to Horde via Performance Report Tool.
- L878-939 _private method_ `private void CopyPerfFilesToOutputDir(string FromArtifactPath, string ToOutputDir = null)`
- L941-954 _protected method_ `protected virtual bool CopyCSVs(List<FileInfo> CsvFiles, DirectoryInfo CSVDirectory)`
- L956-964 _protected method_ `protected void CopyCSV(FileInfo CSVFile, DirectoryInfo CSVDirectory)`
- L966-1003 _protected method_ `protected virtual string GetSubtestName(TConfigClass Config)`
- L1005-1191 _public method_ `public override TConfigClass GetConfiguration()`
- L1193-1232 _private method_ `private void RenderGPUReshapeReport(string ArtifactPath, string OutputPath)`
- L1234-1278 _private method_ `private void AddTestReportArtifacts(TestResult Result, ITestReport Report, string ArtifactName, string OutputPath, string FileFilter)`
- L1280-1330 _public method_ `public void CopyInsightsTraceToOutput(string FromArtifactPath, string ToOutputPath, out string OutTraceName)`
- L1332-1399 _protected method_ `protected void ConfigureCSVProfiler(TConfigClass Config, UnrealTestRole ClientRole)`
- L1401-1413 _private method_ `private void ConfigureServerRole(TConfigClass Config)`
- L1415-1429 _private method_ `private static void OverrideManagedAccountPool(string ManagedAccountPool)`
- L1431-1434 _protected method_ `static protected void GetConfigValues(UnrealTestContext Context, string IniSection, string IniElement, out IReadOnlyList<string> Values)`
- L1436-1439 _protected method_ `static protected string GetPathInProject(UnrealTestContext Context, string InPath)`
- L1441-1447 _protected method_ `static protected void ReadConfigArray(UnrealTestContext Context, string IniSection, string IniElement, Action<string> Process)`

#### class `AutomatedPerfTest.AutomatedPerfTestNode.HandledError`  
`public class HandledError`  
_public; L59-79_
- L61 _public field_ `public string ClientErrorString`
- L62 _public field_ `public string GauntletErrorString`
- L67 _public field_ `public string CategoryName` — String name for the log category that should be used to filter errors. Defaults to null, i.e. no filter.
- L70 _public field_ `public bool Verbose`
- L72-78 _public ctor_ `public HandledError(string ClientError, string GauntletError, string Category, bool VerboseIn = false)`

#### class `AutomatedPerfTest.DefaultTest`  
`public class DefaultTest : AutomatedPerfTestNode<AutomatedPerfTestConfigBase>`  
_public; L1450-1522_
- inherits: `AutomatedPerfTestNode<AutomatedPerfTestConfigBase>`
- L1452-1456 _public ctor_ `public DefaultTest(UnrealTestContext InContext) : base(InContext)`
- L1458-1486 _private method_ `private ITestNode CreateDefaultTestType(out Type TestNodeType)`
- L1488-1491 _public method_ `public void InitDefaultTestTypes()`
- L1493-1519 _public method_ `public override AutomatedPerfTestConfigBase GetConfiguration()`
- L1521 _private field_ `private HashSet<Type> CandidateTestTypes = new HashSet<Type>()`
