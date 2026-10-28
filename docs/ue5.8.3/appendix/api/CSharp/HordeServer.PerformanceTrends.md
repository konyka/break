# CSharp / HordeServer.PerformanceTrends

- project root: `Source/Programs/Horde/Plugins/PerformanceTrends/HordeServer.PerformanceTrends`
- files: 13; symbols: 133
- symbol kinds: class=14, const=1, ctor=10, field=10, interface=2, method=48, property=47, struct=1
- access marked `*` is implicit (not written in source)

### `Source/Programs/Horde/Plugins/PerformanceTrends/HordeServer.PerformanceTrends/IPerformanceSummaryTrendHandler.cs` (HordeServer.PerformanceTrends)


#### interface `HordeServer.PerformanceTrends.IPerformanceSummaryTrendHandler`  
`public interface IPerformanceSummaryTrendHandler`  
_public; L20-66_
- desc: Interface that describes performance trend summary handler that is used for dispatch based off of the summary type. It is closely related to a IPerformanceTrendsService, in that it defines and performs the data retrieval as made specific by the summary type.
- L25 _public* property_ `string PerformanceSummaryType { get; }` — The type the handler is designed to be dispatched for.
- L35 _public* method_ `Task<IEnumerable<PerformanceTrendTelemetry>> ProcessGeneralMetricRequest(DbConnection dbConnection, PerformanceTrendFilter filter, ILogger logger, CancellationToken cancellationToken)` — Gets a collection of PerformanceTrendTelemetry that corresponds to the underlying metric type.
- L45 _public* method_ `Task<IEnumerable<PerformanceTrendTelemetry>> ProcessDistinctTestProjectRequestAsync(DbConnection dbConnection, PerformanceTrendFilter filter, ILogger logger, CancellationToken cancellationToken)` — Gets the distinct test projects for a specific Summary Trend.
- L55 _public* method_ `Task<IEnumerable<PerformanceTrendTelemetry>> GetDistinctPlatformsAsync(DbConnection dbConnection, PerformanceTrendFilter filter, ILogger logger, CancellationToken cancellationToken = default)` — Gets the distinct platforms for a specific filter criteria.
- L65 _public* method_ `Task<IEnumerable<PerformanceTrendTelemetry>> GetDistinctCommitsAsync(DbConnection dbConnection, PerformanceTrendFilter filter, ILogger logger, CancellationToken cancellationToken = default)` — Gets the distinct commits for a specific filter criteria.

#### class `HordeServer.PerformanceTrends.AbstractPerformanceSummaryTrendHandler`  
`public abstract class AbstractPerformanceSummaryTrendHandler<TTelemetry> : IPerformanceSummaryTrendHandler where TTelemetry : PerformanceTrendTelemetry`  
_public; L71-254_
- inherits: `IPerformanceSummaryTrendHandler`
- constraints: `where TTelemetry : PerformanceTrendTelemetry`
- desc: Abstract class that defines the basic interface for a summary trend handler, as well as provides default implementations for common metadata filters on summary tables.
- L76-78 _protected ctor_ `protected AbstractPerformanceSummaryTrendHandler()` — Constructor.
- L81 _public property_ `public abstract string PerformanceSummaryType { get; }` — (inheritdoc)
- L88 _public method_ `public abstract Task<IEnumerable<PerformanceTrendTelemetry>> ProcessGeneralMetricRequest(DbConnection dbConnection, PerformanceTrendFilter filter, ILogger logger, CancellationToken cancellationToken)` — (inheritdoc)
- L95-141 _public method_ `public virtual async Task<IEnumerable<PerformanceTrendTelemetry>> ProcessDistinctTestProjectRequestAsync(DbConnection dbConnection, PerformanceTrendFilter filter, ILogger logger, CancellationToken cancellationToken)` — (inheritdoc)
- L144-181 _public method_ `public virtual async Task<IEnumerable<PerformanceTrendTelemetry>> GetDistinctPlatformsAsync(DbConnection dbConnection, PerformanceTrendFilter filter, ILogger logger, CancellationToken cancellationToken = default)` — (inheritdoc)
- L184-221 _public method_ `public virtual async Task<IEnumerable<PerformanceTrendTelemetry>> GetDistinctCommitsAsync(DbConnection dbConnection, PerformanceTrendFilter filter, ILogger logger, CancellationToken cancellationToken = default)` — (inheritdoc)
- L226 _protected property_ `protected abstract string? SchemaName { get; }` — The schema/database the underlying table lives in (e.g. ingest ), or null to use the backend's default database.
- L232 _protected property_ `protected abstract string TableName { get; }` — The unqualified table name (may itself contain dots, e.g. horde.state_job_summary ).
- L238-242 _protected method_ `protected string GetTableName(PerformanceTrendFilter filter)` — Returns the fully qualified, backend-formatted identifier suitable for inclusion in a SQL FROM clause. Routes through the dialect carried on the per-call filter (set by the calling service from the active backend's IAnalyticsDataSource.Dialect) so handlers always format identifiers per the consumer's selected backend.
- L249 _protected method_ `protected abstract IReadOnlyList<PerformanceTrendTelemetry> ParseTypeFromReader(DbDataReader reader)` — Parses the concrete type from the reader, and returns the abstract telemetry type.

### `Source/Programs/Horde/Plugins/PerformanceTrends/HordeServer.PerformanceTrends/IPerformanceTrendsService.cs` (HordeServer.PerformanceTrends)


#### interface `HordeServer.PerformanceTrends.IPerformanceTrendsService`  
`public interface IPerformanceTrendsService`  
_public; L11-51_
- desc: Interface for the Performance Trends service used for handling requests for performance trend data.
- L20 _public* method_ `Task<List<PerformanceTrendTelemetry>> GetPerformanceSummaryRecordsAsync(PerformanceTrendFilter filter, string type, CancellationToken cancellationToken)` — Gets the performance summary records of a requested type.
- L28 _public* method_ `Task<List<PerformanceTrendTelemetry>> GetPerformanceTrendTestProjectsAsync(bool excludeOrphanedSummaryTypes = true, CancellationToken cancellationToken = default)` — Gets the distinct test projects across all known summary type handlers.
- L36 _public* method_ `Task<List<PerformanceTrendTelemetry>> GetPerformanceSummaryPlatformsAsync(PerformanceTrendFilter filter, CancellationToken cancellationToken)` — Gets the distinct platforms for a specific filter criteria.
- L44 _public* method_ `Task<List<PerformanceTrendTelemetry>> GetPerformanceSummaryCommitsAsync(PerformanceTrendFilter filter, CancellationToken cancellationToken)` — Gets the distinct commits for a specific filter criteria.
- L50 _public* method_ `List<string> GetPerformanceTrendTypes()` — Gets the list of performance trend types registered to the service.

### `Source/Programs/Horde/Plugins/PerformanceTrends/HordeServer.PerformanceTrends/KeyStatsPerformanceSummaryHandler.cs` (HordeServer.PerformanceTrends)


#### class `HordeServer.PerformanceTrends.KeyStatsPerformanceSummaryHandler`  
`public class KeyStatsPerformanceSummaryHandler : AbstractPerformanceSummaryTrendHandler<KeyStatTelemetryRecord>`  
_public; L17-124_
- inherits: `AbstractPerformanceSummaryTrendHandler<KeyStatTelemetryRecord>`
- desc: Summary Handler for the KeyStats type.
- L22-25 _private* ctor_ `static KeyStatsPerformanceSummaryHandler()` — Static constructor — registers Dapper column mappings once per type.
- L30-32 _public ctor_ `public KeyStatsPerformanceSummaryHandler()` — Constructor.
- L37 _public property_ `public override string PerformanceSummaryType => ...` — (inheritdoc)
- L40 _protected property_ `protected override string? SchemaName => ...` — (inheritdoc)
- L43 _protected property_ `protected override string TableName => ...` — (inheritdoc)
- L46-115 _public method_ `public override async Task<IEnumerable<PerformanceTrendTelemetry>> ProcessGeneralMetricRequest(DbConnection dbConnection, PerformanceTrendFilter filter, ILogger logger, CancellationToken cancellationToken)` — (inheritdoc)
- L118-121 _protected method_ `protected override IReadOnlyList<PerformanceTrendTelemetry> ParseTypeFromReader(DbDataReader reader)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/PerformanceTrends/HordeServer.PerformanceTrends/PerformanceBudgetCollection.cs` (HordeServer.PerformanceTrends)


#### class `HordeServer.PerformanceTrends.PerformanceBudgetCollection`  
`class PerformanceBudgetCollection : IPerformanceBudgetCollection`  
_internal*; L16-296_
- inherits: `IPerformanceBudgetCollection`
- desc: Performance Budget Collection implementation.
- L20 _private* field_ `readonly IMongoCollection<PerformanceBudgetDocument> _performanceBudgetDocuments`
- L21 _private* field_ `readonly ILogger<PerformanceBudgetCollection> _logger`
- L32-48 _public ctor_ `public PerformanceBudgetCollection(IMongoService mongoService, ILogger<PerformanceBudgetCollection> logger)` — Constructor.
- L55-91 _public method_ `public async Task<IPerformanceBudget?> AddPerformanceBudgetAsync(UserId? owner, PerformanceBudgetAddRequest request, CancellationToken cancellationToken)` — (inheritdoc)
- L94-161 _public method_ `public async Task<IPerformanceBudget?> UpdatePerformanceBudgetAsync(PerformanceBudgetId budgetId, PerformanceBudgetUpdateRequest request, CancellationToken cancellationToken)` — (inheritdoc)
- L164-170 _public method_ `public async Task<IPerformanceBudget?> GetPerformanceBudgetAsync(PerformanceBudgetId budgetId, CancellationToken cancellationToken)` — (inheritdoc)
- L173-199 _public method_ `public async Task<IEnumerable<IPerformanceBudget>> GetPerformanceBudgetsAsync(string computedStream, string? testProject = null, string? platform = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L202-208 _public method_ `public async Task<bool> DeletePerformanceBudgetAsync(PerformanceBudgetId budgetId, CancellationToken cancellationToken)` — (inheritdoc)

#### class `HordeServer.PerformanceTrends.PerformanceBudgetCollection.MetricThresholdDocument`  
`class MetricThresholdDocument : IMetricThreshold`  
_private*; L217-234_
- inherits: `IMetricThreshold`
- desc: Metric threshold document for storage in MongoDB.
- L221 _public property_ `public string TestType { get; set; }` — attrs: `[BsonElement("tt")]` — (inheritdoc)
- L225 _public property_ `public string MetricName { get; set; }` — attrs: `[BsonElement("mn")]` — (inheritdoc)
- L229 _public property_ `public double ThresholdValue { get; set; }` — attrs: `[BsonElement("tv")]` — (inheritdoc)
- L233 _public property_ `public bool LargerIsWorse { get; set; }` — attrs: `[BsonElement("liw")]` — (inheritdoc)

#### class `HordeServer.PerformanceTrends.PerformanceBudgetCollection.PerformanceBudgetDocument`  
`class PerformanceBudgetDocument : IPerformanceBudget`  
_private*; L239-293_
- inherits: `IPerformanceBudget`
- desc: Performance budget document.
- L243 _public property_ `public PerformanceBudgetId Id { get; set; }` — attrs: `[BsonRequired, BsonId]` — (inheritdoc)
- L247 _public property_ `public string Name { get; set; }` — attrs: `[BsonElement("n")]` — (inheritdoc)
- L251 _public property_ `public string? Description { get; set; }` — attrs: `[BsonElement("d")]` — (inheritdoc)
- L255 _public property_ `public UserId? Owner { get; set; }` — attrs: `[BsonElement("o")]` — (inheritdoc)
- L259 _public property_ `public string ComputedStream { get; set; }` — attrs: `[BsonElement("cs")]` — (inheritdoc)
- L263 _public property_ `public string TestProject { get; set; }` — attrs: `[BsonElement("tp")]` — (inheritdoc)
- L267 _public property_ `public List<string>? Platforms { get; set; }` — attrs: `[BsonElement("pls")]` — (inheritdoc)
- L274 _public property_ `public bool AppliesToAllPlatforms { get; set; }` — attrs: `[BsonElement("aap")]` — Computed flag indicating this budget applies to all platforms. Set to true when Platforms is null or empty. Used for efficient indexing.
- L279 _private* property_ `IReadOnlyList<string>? IPerformanceBudget.Platforms => ...` — The platforms as a read-only list for the interface.
- L283 _public property_ `public List<MetricThresholdDocument> Thresholds { get; set; }` — attrs: `[BsonElement("th")]` — (inheritdoc)
- L288 _private* property_ `IReadOnlyList<IMetricThreshold> IPerformanceBudget.Thresholds => ...` — The thresholds as a read-only list for the interface.
- L292 _public property_ `public DateTime UpdateTimeUtc { get; set; }` — attrs: `[BsonElement("ut")]` — (inheritdoc)

### `Source/Programs/Horde/Plugins/PerformanceTrends/HordeServer.PerformanceTrends/PerformanceTrendFilter.cs` (HordeServer.PerformanceTrends)


#### struct `HordeServer.PerformanceTrends.PerformanceTrendFilter`  
`public struct PerformanceTrendFilter`  
_public; L13-156_
- desc: Filter object for common performance trend queries.
- L18 _public const_ `public const int MaximumRecordCount = 10000` — The maximum record count to return from a performance trend.
- L20 _private field_ `private int _recordCount`
- L25-29 _public property_ `public int RecordCount { get; set; }` — The maximum number of records to obtain.
- L34 _public property_ `public string? SummaryName { get; set; }` — The summary name to filter by.
- L39 _public property_ `public string[]? Platforms { get; set; }` — The platforms to filter by.
- L44 _public property_ `public int? MinChangelist { get; set; }` — The minimum changelist to obtain.
- L49 _public property_ `public int? MaxChangelist { get; set; }` — The maximum changelist to obtain.
- L54 _public property_ `public DateTime? MinDate { get; set; }` — The minimum date to obtain.
- L59 _public property_ `public DateTime? MaxDate { get; set; }` — The maximum date to obtain.
- L64 _public property_ `public string? TestProject { get; set; }` — The test project to limit the selection to.
- L69 _public property_ `public string? TestIdentity { get; set; }` — The test identity to limit the selection to.
- L74 _public property_ `public string[]? TestTypes { get; set; }` — The test types to limit the selection to.
- L79 _public property_ `public int? MinSchemaVersion { get; set; }` — The minimum schema version to apply.
- L87 _public property_ `public string[]? ComputedStreams { get; set; }` — The set of compute streams to limit the selection to.
- L92 _public property_ `public ISqlDialect? Dialect { get; set; }` — Backend dialect used by handlers for WHERE-clause materialisation, table-name formatting, and parameter binding. Set by the calling service so handlers don't need to thread it through their method signatures. Falls back to positional ? placeholders when null (ODBC/test behavior).
- L98-155 _public method_ `public WhereClauseResult BuildWhereClause()` — Constructs a WhereClauseResult based on the AND of every enabled filter parameter.

### `Source/Programs/Horde/Plugins/PerformanceTrends/HordeServer.PerformanceTrends/PerformanceTrendsConfig.cs` (HordeServer.PerformanceTrends)


#### class `HordeServer.PerformanceTrendsConfig`  
`public class PerformanceTrendsConfig : StructuredAnalyticsConfig`  
_public; L8-19_
- inherits: `StructuredAnalyticsConfig`
- desc: Configuration for the PerformanceTrends plugin
- L13 _public property_ `public int? MinQuerySchemaVersion { get; set; }` — The minimum Performance Trend Schema Version to allow.
- L18 _public property_ `public bool HideExternalResults { get; set; }` — Whether to hide external results. A result is considered external if the source data did not originate from a Horde job.

### `Source/Programs/Horde/Plugins/PerformanceTrends/HordeServer.PerformanceTrends/PerformanceTrendsController.cs` (HordeServer.PerformanceTrends)


#### class `HordeServer.PerformanceTrends.PerformanceTrendsController`  
`public class PerformanceTrendsController : HordeControllerBase`  
_public; L24-678_
- attrs: `[Authorize] [ApiController]`
- inherits: `HordeControllerBase`
- desc: Performance Trends Controller
- L26 _private field_ `private readonly IPerformanceTrendsService _performanceTrendsService`
- L27 _private field_ `private readonly IPerformanceBudgetCollection _performanceBudgetCollection`
- L28 _private field_ `private readonly IUserCollection _userCollection`
- L29 _private field_ `private readonly IOptionsSnapshot<BuildConfig> _buildConfig`
- L30 _private field_ `private readonly IOptionsSnapshot<PerformanceTrendsConfig> _performanceTrendsConfig`
- L40-47 _public ctor_ `public PerformanceTrendsController(IPerformanceTrendsService performanceTrendsService, IPerformanceBudgetCollection performanceBudgetCollection, IUserCollection userCollection, IOptionsSnapshot<PerformanceTrendsConfig> performanceTrendsConfig, IOptionsSnapshot<BuildConfig> buildConfig)` — Constructor.
- L68-120 _public method_ `public async Task<IActionResult> GetPerformanceMetricsAsync([FromQuery] string type, [FromQuery] string[] streams, [FromQuery] int count = 100, [FromQuery] string? testProject = null, [FromQuery] string? testIdentity = null, [FromQuery] string[]? testTypes = null, [FromQuery] string[]? platforms = null, [FromQuery] int? startCommitIdOrdered = null, [FromQuery] int? endCommitIdOrdered = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/performancetrends/metrics")] [ProducesResponseType(typeof(List<PerformanceTrendTelemetry>), StatusCodes.Status200OK)]` — Gets performance metrics.
- L131-173 _public method_ `public async Task<ActionResult<List<TestProjectResponse>>> GetPerformanceTestProjectsAsync([FromQuery] bool excludeOrphanedSummaryTypes = true, [FromQuery] string[]? streams = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/performancetrends/testprojects")]` — Gets all the known test projects across all summary table types.
- L187-243 _public method_ `public async Task<ActionResult<List<TestProjectPlatformResponse>>> GetPlatformsAsync([FromQuery] string metricSummaryType, [FromQuery] string[] streams, [FromQuery] string? testProject = null, [FromQuery] string? testIdentity = null, [FromQuery] string[]? testTypes = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/performancetrends/platforms")]` — Gets the distinct platforms given the filter parameters.
- L258-319 _public method_ `public async Task<ActionResult<List<TestProjectCommitResponse>>> GetCommitsAsync([FromQuery] string metricSummaryType, [FromQuery] string[] streams, [FromQuery] string? testProject = null, [FromQuery] string? testIdentity = null, [FromQuery] string[]? testTypes = null, [FromQuery] string[]? platforms = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/performancetrends/commits")]` — Gets the distinct commits given the filter parameters.
- L327-330 _public method_ `public ActionResult<List<string>> GetPerformanceTrendTypes()` — attrs: `[HttpGet] [Route("/api/v1/performancetrends/types")]` — Gets the types of performance trends available.
- L346-385 _public method_ `public async Task<ActionResult<PerformanceBudgetResponse>?> AddPerformanceBudgetAsync([FromBody] PerformanceBudgetAddRequest request, CancellationToken cancellationToken = default)` — attrs: `[HttpPost] [Route("/api/v1/performancetrends/budgets")] [ProducesResponseType(typeof(PerformanceBudgetResponse), 200)]` — Creates a new performance budget group.
- L398-442 _public method_ `public async Task<ActionResult<PerformanceBudgetResponse>?> UpdatePerformanceBudgetAsync(PerformanceBudgetId budgetId, [FromBody] PerformanceBudgetUpdateRequest request, CancellationToken cancellationToken = default)` — attrs: `[HttpPut] [Route("/api/v1/performancetrends/budgets/{budgetId}")] [ProducesResponseType(typeof(PerformanceBudgetResponse), 200)]` — Updates an existing performance budget group.
- L453-469 _public method_ `public async Task<ActionResult<PerformanceBudgetResponse>?> GetPerformanceBudgetAsync(PerformanceBudgetId budgetId, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/performancetrends/budgets/{budgetId}")] [ProducesResponseType(typeof(PerformanceBudgetResponse), 200)]` — Gets a performance budget by ID.
- L482-501 _public method_ `public async Task<ActionResult<List<PerformanceBudgetResponse>>> GetPerformanceBudgetsAsync([FromQuery] string computedStream, [FromQuery] string? testProject = null, [FromQuery] string? platform = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/performancetrends/budgets")] [ProducesResponseType(typeof(List<PerformanceBudgetResponse>), 200)]` — Gets performance budget groups matching the specified criteria.
- L512-544 _public method_ `public async Task<ActionResult> DeletePerformanceBudgetAsync(PerformanceBudgetId budgetId, CancellationToken cancellationToken = default)` — attrs: `[HttpDelete] [Route("/api/v1/performancetrends/budgets/{budgetId}")]` — Deletes a performance budget.
- L550-563 _private method_ `private async Task<PerformanceBudgetResponse> CreatePerformanceBudgetResponseWithOwnerAsync(IPerformanceBudget budget, CancellationToken cancellationToken)`
- L570-594 _private method_ `private (bool isValidationSuccessful, ActionResult actionResult) VerifyAndAuthorizeStream(string computedStream)` — Helper method to verify and authorize stream.
- L601-605 _private method_ `private static bool IsNonHordeStream(string stream)` — Determines if the given stream identifier is a non-Horde stream format.
- L612-635 _private method_ `private string[] FilterAuthorizedStreams(string[]? streams)` — Filters the provided streams array to only include streams the user is authorized to access.
- L643-675 _private method_ `private bool IsAuthorizedForStream(string? stream)` — Checks if the user is authorized to access a single stream.

### `Source/Programs/Horde/Plugins/PerformanceTrends/HordeServer.PerformanceTrends/PerformanceTrendsPlugin.cs` (HordeServer.PerformanceTrends)


#### class `HordeServer.PerformanceTrendsPlugin`  
`public class PerformanceTrendsPlugin : IPluginStartup`  
_public; L15-40_
- attrs: `[Plugin("PerformanceTrends", EnabledByDefault = false, GlobalConfigType = typeof(PerformanceTrendsConfig), ServerConfigType = typeof(PerformanceTrendsServerConfig))]`
- inherits: `IPluginStartup`
- desc: Entry point for the PerformanceTrends plugin
- L20-22 _public ctor_ `public PerformanceTrendsPlugin()` — Constructor
- L25-27 _public method_ `public void Configure(IApplicationBuilder app)` — (inheritdoc)
- L30-39 _public method_ `public void ConfigureServices(IServiceCollection serviceCollection)` — (inheritdoc)

#### class `HordeServer.PerformanceTrendsExtensions`  
`public static class PerformanceTrendsExtensions`  
_public; L45-58_
- desc: Helper methods for PerformanceTrends plugin config
- L50 _public method_ `public static void AddPerformanceTrendsConfig(this IDictionary<PluginName, IPluginConfig> dictionary, PerformanceTrendsConfig config)` — Configures the PerformanceTrends plugin
- L56 _public method_ `public static PerformanceTrendsConfig GetPerformanceTrendsConfig(this IDictionary<PluginName, IPluginConfig> dictionary)` — Gets configuration for the PerformanceTrends plugin

### `Source/Programs/Horde/Plugins/PerformanceTrends/HordeServer.PerformanceTrends/PerformanceTrendsServerConfig.cs` (HordeServer.PerformanceTrends)


#### class `HordeServer.PerformanceTrendsServerConfig`  
`public class PerformanceTrendsServerConfig : PluginServerConfig`  
_public; L10-12_
- inherits: `PluginServerConfig`
- desc: Server-specific configuration for the PerformanceTrends plugin

### `Source/Programs/Horde/Plugins/PerformanceTrends/HordeServer.PerformanceTrends/PerformanceTrendsService.cs` (HordeServer.PerformanceTrends)


#### class `HordeServer.PerformanceTrends.PerformanceTrendsService`  
`public class PerformanceTrendsService : AbstractAnalyticsService<PerformanceTrendsConfig>, IPerformanceTrendsService`  
_public; L16-169_
- inherits: `AbstractAnalyticsService<PerformanceTrendsConfig>, IPerformanceTrendsService`
- desc: Horde Performance Trends service used for handling requests for performance trend data, and delegating them to the corresponding handlers. This service owns the primary Api around access, and filtering.
- L18 _private field_ `private readonly Dictionary<string, IPerformanceSummaryTrendHandler> _handlersByType = ...`
- L18 _private field_ `private readonly Dictionary< _handlersByType = new Dictionary<string, IPerformanceSummaryTrendHandler>(StringComparer.OrdinalIgnoreCase)`
- L27-42 _public ctor_ `public PerformanceTrendsService(IOptionsMonitor<PerformanceTrendsConfig> config, IServiceProvider serviceProvider, ILogger<PerformanceTrendsService> logger, IEnumerable<IPerformanceSummaryTrendHandler> handlers) : base(config, serviceProvider, logger)` — Constructor.
- L47-72 _public method_ `public async Task<List<PerformanceTrendTelemetry>> GetPerformanceSummaryRecordsAsync(PerformanceTrendFilter filter, string type, CancellationToken cancellationToken)` — (inheritdoc)
- L75-104 _public method_ `public async Task<List<PerformanceTrendTelemetry>> GetPerformanceTrendTestProjectsAsync(bool excludeOrphanedSummaryTypes = true, CancellationToken cancellationToken = default)` — (inheritdoc)
- L107-132 _public method_ `public async Task<List<PerformanceTrendTelemetry>> GetPerformanceSummaryPlatformsAsync(PerformanceTrendFilter filter, CancellationToken cancellationToken)` — (inheritdoc)
- L135-160 _public method_ `public async Task<List<PerformanceTrendTelemetry>> GetPerformanceSummaryCommitsAsync(PerformanceTrendFilter filter, CancellationToken cancellationToken)` — (inheritdoc)
- L163-166 _public method_ `public List<string> GetPerformanceTrendTypes()` — (inheritdoc)

### `Source/Programs/Horde/Plugins/PerformanceTrends/HordeServer.PerformanceTrends/Responses/TestProjectCommitResponse.cs` (HordeServer.PerformanceTrends)


#### class `HordeServer.PerformanceTrends.Responses.TestProjectCommitResponse`  
`public class TestProjectCommitResponse`  
_public; L11-37_
- desc: Models a response for a project's commit set.
- L16 _public property_ `public TestProjectResponse OwningTestProject { get; init; }` — The owning test project.
- L21 _public property_ `public int[] CommitIds { get; init; }` — The commit ids associated with the OwningTestProject.
- L32-36 _public ctor_ `public TestProjectCommitResponse(string summaryType, string? testName, string? testIdentity, string? testType, string? stream, int[] commitIds)` — Constructor.

### `Source/Programs/Horde/Plugins/PerformanceTrends/HordeServer.PerformanceTrends/Responses/TestProjectPlatformResponse.cs` (HordeServer.PerformanceTrends)


#### class `HordeServer.PerformanceTrends.Responses.TestProjectPlatformResponse`  
`public class TestProjectPlatformResponse`  
_public; L11-37_
- desc: Models a response for a project's platform set.
- L16 _public property_ `public TestProjectResponse OwningTestProject { get; init; }` — The owning test project.
- L21 _public property_ `public string[] Platforms { get; init; }` — The platforms associated with the OwningTestProject.
- L32-36 _public ctor_ `public TestProjectPlatformResponse(string summaryType, string? testName, string? testIdentity, string? testType, string? stream, string[] platforms)` — Constructor.

### `Source/Programs/Horde/Plugins/PerformanceTrends/HordeServer.PerformanceTrends/Responses/TestProjectResponse.cs` (HordeServer.PerformanceTrends)


#### class `HordeServer.PerformanceTrends.Responses.TestProjectResponse`  
`public class TestProjectResponse`  
_public; L20-79_
- desc: Models a response for a test project.
- L25 _public property_ `public string SummaryType { get; init; }` — The summary type this test project belongs to.
- L30 _public property_ `public string? TestName { get; init; }` — The name of the test project.
- L35 _public property_ `public string? TestIdentity { get; init; }` — The test identity of the performance trend telemetry.
- L41 _public property_ `public string? TestType { get; init; }` — The test type of the performance trend telemetry.
- L49 _public property_ `public string? ComputedStream { get; init; }` — The computed stream of the performance trend telemetry.
- L59-66 _public ctor_ `public TestProjectResponse(string summaryType, string? testName, string? testIdentity, string? testType, string? computedStream)` — Constructor.
- L73-78 _public method_ `public static TestProjectResponse CreateTestProjectResponse(PerformanceTrendTelemetry telemetry)` — Creates a Test Project Response from a base performance trend telemetry event.
