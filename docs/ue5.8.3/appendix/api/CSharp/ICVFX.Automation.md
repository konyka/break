# CSharp / ICVFX.Automation

- project root: `Plugins/VirtualProduction/ICVFXTesting/Build/Scripts`
- files: 1; symbols: 54
- symbol kinds: class=3, ctor=2, field=41, method=5, property=3
- access marked `*` is implicit (not written in source)

### `Plugins/VirtualProduction/ICVFXTesting/Build/Scripts/Automation/ICVFX.TestNode.cs` (ICVFX.Automation)


#### class `ICVFXTest.ICVFXTestConfig`  
`public class ICVFXTestConfig : UnrealTestConfiguration`  
_public; L11-222_
- inherits: `UnrealTestConfiguration`
- L16 _public field_ `public string TestName` — attrs: `[AutoParamWithNames("ICVFXTest.TestName")]` — Name of the test.
- L19 _public field_ `public string MapOverride` — attrs: `[AutoParamWithNames("ICVFXTest.MapOverride")]`
- L25 _public field_ `public int MaxRunCount` — attrs: `[AutoParamWithNames(1, "ICVFXTest.MaxRunCount")]` — Total number of loops to run during the test.
- L31 _public field_ `public float SoakTime` — attrs: `[AutoParamWithNames(30.0f, "ICVFXTest.SoakTime")]` — How long to spend in the sandbox, in seconds.
- L37 _public field_ `public bool SkipTestSequence` — attrs: `[AutoParamWithNames(false, "ICVFXTest.SkipTestSequence")]` — Whether to run the test sequence after the sandbox soak or not.
- L43 _public field_ `public bool StatCommands` — attrs: `[AutoParamWithNames(false, "ICVFXTest.StatCommands")]` — If true, appends the stat fps and unitgraph to ExecCmds.
- L49 _public field_ `public bool FPSChart` — attrs: `[AutoParamWithNames(false, "ICVFXTest.FPSChart")]` — If true, FPSChart start/end is automatically called for each run.
- L56 _public field_ `public bool MemReport` — attrs: `[AutoParamWithNames(false, "ICVFXTest.MemReport")]` — If true, MemReport is automatically started each run and captured periodically. @note Use the ICVFXTest.MemReportInterval CVar to set the interval.
- L63 _public field_ `public bool VideoCapture` — attrs: `[AutoParamWithNames(false, "ICVFXTest.VideoCapture")]` — If true, video captures are automatically started/ended each run. @note Requires the platform has an available gameplay media encoder.
- L69 _public field_ `public string DisplayConfigPath` — attrs: `[AutoParamWithNames("", "ICVFXTest.DisplayConfig")]` — Path to the exported ndisplay config to use for testing.
- L75 _public field_ `public string DisplayClusterNodeName` — attrs: `[AutoParamWithNames("", "ICVFXTest.DisplayClusterNodeName")]` — Name of the display cluster node to use.
- L81 _public field_ `public float ViewportScreenPercentage` — attrs: `[AutoParamWithNames(100.0f, "ICVFXTest.ViewportScreenPercentage")]` — The global viewport screen percentage to use. (1-100)
- L87 _public field_ `public bool Fullscreen` — attrs: `[AutoParamWithNames(false, "ICVFXTest.Fullscreen")]` — Should run fullscreen
- L93 _public field_ `public bool Offscreen` — attrs: `[AutoParamWithNames(false, "ICVFXTest.Offscreen")]` — Should run offscreen
- L99 _public field_ `public int WndLocX` — attrs: `[AutoParamWithNames(0, "ICVFXTest.WndLocX")]` — Window X location
- L105 _public field_ `public int WndLocY` — attrs: `[AutoParamWithNames(0, "ICVFXTest.WndLocY")]` — Window Y location
- L111 _public field_ `public int WndResX` — attrs: `[AutoParamWithNames(1920, "ICVFXTest.WndResX")]` — Window X size (width)
- L117 _public field_ `public int WndResY` — attrs: `[AutoParamWithNames(1080, "ICVFXTest.WndResY")]` — Window Y size (height)
- L123 _public field_ `public bool Lumen` — attrs: `[AutoParamWithNames(false, "ICVFXTest.Lumen")]` — Whether to use Lumen or not.
- L129 _public field_ `public bool Nanite` — attrs: `[AutoParamWithNames(false, "ICVFXTest.Nanite")]` — Whether to use nanite or not.
- L132 _public field_ `public bool D3DDebug` — attrs: `[AutoParamWithNames(false, "ICVFXTest.D3DDebug")]`
- L135 _public field_ `public bool GPUCrashDebugging` — attrs: `[AutoParamWithNames(false, "ICVFXTest.GPUCrashDebugging")]`
- L141 _public field_ `public int MaxGPUCount` — attrs: `[AutoParamWithNames(1, "ICVFXTest.MaxGPUCount")]` — Sets max number of GPUs to use.
- L147 _public field_ `public string SummaryReportType` — attrs: `[AutoParamWithNames("ICVFXTest.SummaryReportType")]` — Report type
- L153 _public field_ `public string SummaryReportPath` — attrs: `[AutoParamWithNames("ICVFXTest.SummaryReportPath")]` — Path to the exported ndisplay config to use for testing.
- L159 _public field_ `public bool RDGImmediate` — attrs: `[AutoParamWithNames(false, "ICVFXTest.RDGImmediate")]` — Whether to run with -rdgimmediate
- L165 _public field_ `public bool NoRHIThread` — attrs: `[AutoParamWithNames(false, "ICVFXTest.NoRHIThread")]` — Whether to run with -norhithread
- L168 _public field_ `public bool DisableVirtualShadowMaps` — attrs: `[AutoParamWithNames("ICVFXTest.DisableVirtualShadowMaps")]`
- L174 _public field_ `public bool EnableTrace` — attrs: `[AutoParamWithNames(false, "ICVFXTest.EnableTrace")]` — Whether to run with unreal insights.
- L180 _public field_ `public string TraceRootFolder` — attrs: `[AutoParamWithNames("ICVFXTest.TraceRootFolder")]` — When running with insights, we will overrides the trace file name to put traces in this folder.
- L186 _public field_ `public string TraceFileName` — attrs: `[AutoParamWithNames("ICVFXTest.TraceFileName")]` — Force file name to use for a trace file. If not specified, the default one will be generated.
- L193 _public field_ `public string PerfCacheFolder` — attrs: `[AutoParamWithNames("ICVFXTest.PerfCacheFolder")]` — Path to the folder where perf cache data should be stored.
- L200 _public field_ `public bool NoLocalReports` — attrs: `[AutoParamWithNames(false, "ICVFXTest.NoLocalReports")]` — Whether to generate the local test reports.
- L207 _public field_ `public bool SkipPerfReportServer` — attrs: `[AutoParamWithNames(false, "ICVFXTest.SkipPerfReportServer")]` — Whether to skip uploading gauntlet perf data to the PRS.
- L214 _public field_ `public string PerfReportServerImportDir` — attrs: `[AutoParamWithNames("", "ICVFXTest.PerfReportServerImportDir")]` — Override the server import directory for PRS.
- L221 _public field_ `public bool IsDevelopment` — attrs: `[AutoParamWithNames(false, "ICFVXTest.IsDevelopment")]` — Whether the server is running in development or not

#### class `ICVFXTest.ICVFXTestNode`  
`public abstract class ICVFXTestNode : UnrealTestNode<ICVFXTestConfig>`  
_public; L224-370_
- inherits: `UnrealTestNode<ICVFXTestConfig>`
- L226-234 _public ctor_ `public ICVFXTestNode(UnrealTestContext InContext) : base(InContext)`
- L236-240 _public method_ `public override bool StartTest(int Pass, int InNumPasses)`
- L267 _public property_ `public List<HandledError> HandledErrors { get; set; }` — List of errors with special-cased gauntlet messages.
- L272 _public property_ `public Guid TestGuid { get; set; }` — Guid associated with each test run for ease of differentiation between different runs on same build.
- L277 _public property_ `public static string DataPath { get; }` — Absolute path to Saloon data required during testing and report generation
- L282-285 _protected method_ `protected virtual void InitHandledErrors()` — Set up the base list of possible expected errors, plus the messages to deliver if encountered.
- L290 _private field_ `private int ICVFXTestLastLogCount` — Line count of the client log messages that have been written to the test logs.
- L295-337 _public method_ `public override void TickTest()` — Periodically called while test is running. Updates logs.
- L339-359 _protected method_ `protected override UnrealProcessResult GetExitCodeAndReason(StopReason InReason, UnrealLog InLogSummary, UnrealRoleArtifacts InArtifacts, out string ExitReason, out int ExitCode)`
- L366-369 _public method_ `public override ITestReport CreateReport(TestResult Result, UnrealTestContext Context, UnrealBuildSource Build, IEnumerable<UnrealRoleResult> Artifacts, string ArtifactPath)` — CreateReport() happens near the end of StopTest after SaveArtifacts(). Override this function within your test to set up external reporting. Include a base call so that ReportToDashboard() is called appropriately.

#### class `ICVFXTest.ICVFXTestNode.HandledError`  
`public class HandledError`  
_public; L242-262_
- L244 _public field_ `public string ClientErrorString`
- L245 _public field_ `public string GauntletErrorString`
- L250 _public field_ `public string CategoryName` — String name for the log category that should be used to filter errors. Defaults to null, i.e. no filter.
- L253 _public field_ `public bool Verbose`
- L255-261 _public ctor_ `public HandledError(string ClientError, string GauntletError, string Category, bool VerboseIn = false)`
