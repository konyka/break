# CSharp / EpicGames.Analytics.PerformanceTrends

- project root: `Source/Programs/Shared/EpicGames.Analytics.PerformanceTrends`
- files: 2; symbols: 69
- symbol kinds: class=1, const=20, ctor=3, field=2, method=5, property=36, record=2
- access marked `*` is implicit (not written in source)

### `Source/Programs/Shared/EpicGames.Analytics.PerformanceTrends/KeyStatTelemetryRecord.cs` (EpicGames.Analytics.PerformanceTrends)


#### record `EpicGames.Analytics.KeyStatTelemetryRecord`  
`public record KeyStatTelemetryRecord : PerformanceTrendTelemetry`  
_public; L15-108_
- attrs: `[AnalyticsTableGen] [TelemetryEvent(DefaultEventName)] [Table("horde.state_performance_key_stats", Schema = "ingest")]`
- inherits: `PerformanceTrendTelemetry`
- desc: Telemetry record that describes key stats for performance tests.
- L20 _public const_ `public const string DefaultEventName = "State.Performance.KeyStats"` — Default event name for the KeyStatTelemetryRecord.
- L25 _public field_ `public static readonly int CurrentSchemaVersion = 1` — Current schema version.
- L31 _public property_ `public int DynamicResolutionPercentageMax { get; init; }` — attrs: `[Column("dynamic_resolution_percentage_max")]` — Dynamic resolution max percentage.
- L37 _public property_ `public string? CsvId { get; init; }` — attrs: `[Column("csvid")]` — Csv id used to create this record.
- L43 _public property_ `public float GpuTimeAvg { get; init; }` — attrs: `[Column("gp_utime_avg")]` — Average GPU time.
- L49 _public property_ `public float PhysicalUsedMbMax { get; init; }` — attrs: `[Column("physical_used_mb_max")]` — Max physical memory used.
- L55 _public property_ `public int DynamicResolutionVsmNanite { get; init; }` — attrs: `[Column("dynamic_resolution_vsm_nanite")]` — Dynamic resolution through Nanite.
- L61 _public property_ `public float MVP { get; init; }` — attrs: `[Column("mvp")]` — MVP.
- L67 _public property_ `public float HitchesMin { get; init; }` — attrs: `[Column("hitches_min")]` — Hitches per minute.
- L73 _public property_ `public float HitchTimePercent { get; init; }` — attrs: `[Column("hitch_time_percent")]` — Hitch time percent.
- L79 _public property_ `public float GameThreadtimeAvg { get; init; }` — attrs: `[Column("game_threadtime_avg")]` — Game thread time average.
- L85 _public property_ `public float RenderThreadtimeAvg { get; init; }` — attrs: `[Column("render_threadtime_avg")]` — Render thread time average.
- L91 _public property_ `public float FrametimeAvg { get; init; }` — attrs: `[Column("frametime_avg")]` — Frame time average.
- L97 _public property_ `public float DynamicResolutionPercentageAvg { get; init; }` — attrs: `[Column("dynamic_resolution_percentage_avg")]` — Dynamic resolution percentage average.
- L103-107 _public ctor_ `public KeyStatTelemetryRecord() : base()` — No arg constructor for ORM construction.

### `Source/Programs/Shared/EpicGames.Analytics.PerformanceTrends/PerformanceTrendTelemetry.cs` (EpicGames.Analytics.PerformanceTrends)


#### class `EpicGames.Analytics.PerformanceTrends.StandardTelemetryMetadata`  
`public static class StandardTelemetryMetadata`  
_public; L14-138_
- desc: Utility class to handle standard telemetry operations, and metadata processing.
- L18 _internal const_ `internal const string EngineVersion = "engineversion"`
- L19 _internal const_ `internal const string EngineReleaseVersion = "enginereleaseversion"`
- L20 _internal const_ `internal const string BuildVersion = "buildversion"`
- L21 _internal const_ `internal const string Platform = "platform"`
- L22 _internal const_ `internal const string TestId = "testid"`
- L23 _internal const_ `internal const string TestName = "testname"`
- L24 _internal const_ `internal const string TestConfigName = "testconfigname"`
- L25 _internal const_ `internal const string GauntletTestType = "gauntlettesttype"`
- L26 _internal const_ `internal const string GauntletSubTest = "gauntletsubtest"`
- L27 _internal const_ `internal const string Branch = "branch"`
- L28 _internal const_ `internal const string Changelist = "changelist"`
- L29 _internal const_ `internal const string StartTimestamp = "starttimestamp"`
- L30 _internal const_ `internal const string EndTimestamp = "endtimestamp"`
- L31 _internal const_ `internal const string BuildSuffix = "buildsuffix"`
- L32 _internal const_ `internal const string TestBuildIsPreflight = "testbuildispreflight"`
- L33 _internal const_ `internal const string Cpu = "cpu"`
- L34 _internal const_ `internal const string Gpu = "gpu"`
- L35 _internal const_ `internal const string VerbatimRhiName = "verbatimrhiname"`
- L36 _internal const_ `internal const string DeviceProfile = "deviceprofile"`
- L47-88 _public method_ `public static Hashtable? SanitizeHashtable(Hashtable source)` — Sanitizes keys of the provided source hashtable.
- L93 _public field_ `public static readonly string[] StandardMetadataKeys = [ EngineVersion, EngineReleaseVersion, BuildVersion, Platform, TestId, TestName, TestConfigName, GauntletTestType, GauntletSubTest, Branch, Changelist, StartTimestamp, EndTimestamp, BuildSuffix, TestB ...` — The standard metadata keys.
- L121-135 _public method_ `public static Hashtable CreateFilteredHashtable(Hashtable sourceTable)` — Creates a new hashtable only with the required metadata entries retained (if they exist).

#### record `EpicGames.Analytics.PerformanceTrends.PerformanceTrendTelemetry`  
`public abstract record PerformanceTrendTelemetry : HordeContextTelemetryRecord`  
_public; L146-430_
- attrs: `[AnalyticsTableGen] [Table("default")]`
- inherits: `HordeContextTelemetryRecord`
- desc: Abstract record that describes the shared metadata for performance trend telemetry.
- L154 _public property_ `public string? EngineVersion { get; init; }` — attrs: `[Column("engineversion")]` — The engine version of the telemetry.
- L160 _public property_ `public string? EngineReleaseVersion { get; init; }` — attrs: `[Column("enginereleaseversion")]` — The engine release version of the telemetry.
- L166 _public property_ `public string? BuildVersion { get; init; }` — attrs: `[Column("buildversion")]` — The build version of the telemetry.
- L172 _public property_ `public string? Platform { get; init; }` — attrs: `[Column("platform")]` — The platform of the telemetry.
- L178 _public property_ `public string? TestId { get; init; }` — attrs: `[Column("testid")]` — The test id for the telemetry, if applicable.
- L184 _public property_ `public string? TestName { get; init; }` — attrs: `[Column("testname")]` — The test name for the telemetry, if applicable.
- L190 _public property_ `public string? TestConfigName { get; init; }` — attrs: `[Column("testconfigname")]` — The test config name for the telemetry, if applicable.
- L196 _public property_ `public string? GauntletTestType { get; init; }` — attrs: `[Column("gauntlettesttype")]` — The test type, if applicable.
- L202 _public property_ `public string? GauntletSubTest { get; init; }` — attrs: `[Column("gauntletsubtest")]` — The sub test type, if applicable.
- L208 _public property_ `public bool Collated { get; init; }` — attrs: `[Column("collated")]` — Whether this represents collated data, or not.
- L214 _public property_ `public string? Branch { get; init; }` — attrs: `[Column("branch")]` — The branch the underlying test build was produced from.
- L220 _public property_ `public int? Changelist { get; init; }` — attrs: `[Column("changelist")]` — The changelist the underlying test build was produced from.
- L227 _public property_ `public long? StartTimestamp { get; init; }` — attrs: `[Column("starttimestamp")]` — The start timestamp of the performance trend session.
- L234 _public property_ `public long? EndTimestamp { get; init; }` — attrs: `[Column("endtimestamp")]` — The end timestamp of the performance trend session.
- L241 _public property_ `public string? BuildSuffix { get; init; }` — attrs: `[Column("buildsuffix")]` — The build suffix for the build string.
- L247 _public property_ `public int TestBuildIsPreflight { get; init; }` — attrs: `[Column("testbuildispreflight")]` — Int boolean representation of whether the test build was generated by preflight or not.
- L253 _public property_ `public string? Cpu { get; init; }` — attrs: `[Column("cpu")]` — The CPU of the hardware the performance telemetry was generated from.
- L259 _public property_ `public string? Gpu { get; init; }` — attrs: `[Column("gpu")]` — The GPU of the hardware the performance telemetry was generated from.
- L265 _public property_ `public string? VerbatimRhiName { get; init; }` — attrs: `[Column("verbatimrhiname")]` — The RHI name of the hardware the performance telemetry was generated from.
- L271 _public property_ `public string? DeviceProfile { get; init; }` — attrs: `[Column("deviceprofile")]` — The device profile the performance telemetry was generated from.
- L277 _public property_ `public string? TestIdentity { get; init; }` — attrs: `[Column("test_identity")]` — The data source of the performance trend telemetry.
- L283 _public property_ `public string SummaryName { get; init; }` — attrs: `[Column("summary_name")]` — Summary table name.
- L295 _public property_ `public string? ComputedPlatform { get; init; }` — attrs: `[Column("computed_platform")]` — The semantic platform the telemetry was produced on.
- L305 _public property_ `public string? ComputedStream { get; init; }` — attrs: `[Column("computed_stream")]` — The stream the underlying build was produced from.
- L315-318 _protected ctor_ `protected PerformanceTrendTelemetry() : base()` — No arg constructor for ORM construction.
- L340-367 _protected ctor_ `protected PerformanceTrendTelemetry(Hashtable source, string eventName, int schemaVersion, string? sessionId, string? sessionLabel, bool isBuildMachine, string? hordeUrlStr, string? streamId, string? templateId, string? jobId, string? stepId, int? commitIdOrdered, string? commitId, string summaryName, bool collated, string? testIdentity) : base(eventName, schemaVersion, sessionId, sessionLabel, isBuildMachine, hordeUrlStr, streamId, templateId, jobId, stepId, commitIdOrdered, commitId)` — Constructor.
- L371-379 _private method_ `private static string? GetString(Hashtable table, string key)`
- L381-403 _private method_ `private static int? GetInt(Hashtable table, string key)`
- L405-427 _private method_ `private static long? GetLong(Hashtable table, string key)`
