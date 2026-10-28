# CSharp / HordeServer.StructuredAnalytics

- project root: `Source/Programs/Horde/Plugins/StructuredAnalytics/HordeServer.StructuredAnalytics`
- files: 29; symbols: 611
- symbol kinds: class=72, const=7, ctor=21, enum=4, enumerator=17, event=4, field=52, interface=12, method=216, operator=2, property=201, struct=3
- access marked `*` is implicit (not written in source)

### `Source/Programs/Horde/Plugins/StructuredAnalytics/HordeServer.StructuredAnalytics/AbstractAnalyticsService.cs` (HordeServer.StructuredAnalytics)


#### interface `HordeServer.Analytics.IAuthenticationProvider`  
`public interface IAuthenticationProvider<TConfig> where TConfig : class, IOAuthClientCredentialsConfig`  
_public; L16-33_
- constraints: `where TConfig : class, IOAuthClientCredentialsConfig`
- desc: Authentication provider for an analytics service. Generic over the plugin's TConfig so DI can bind a distinct instance per plugin — each reading its own config for its own OAuth endpoint, scope, secret ID, and fragment key. Without the type parameter, every consumer would share the same provider and the same config section.
- L22 _public* method_ `Task<string?> GetTokenAsync()` — Gets the token.
- L32 _public* method_ `Task<KeyValuePair<string, string>?> GetConnectionStringAuthenticationFragmentAsync()` — Gets the connection string authentication fragment.

#### class `HordeServer.Analytics.AbstractAnalyticsService`  
`public abstract class AbstractAnalyticsService<TConfig> : IDisposable where TConfig : class, IAnalyticsBackendSelectorConfig`  
_public; L41-130_
- inherits: `IDisposable`
- constraints: `where TConfig : class, IAnalyticsBackendSelectorConfig`
- desc: Backend-agnostic base class for analytics services. Resolves an IAnalyticsDataSource from DI using the keyed-services pattern, with the key driven by IAnalyticsBackendSelectorConfig.BackendName on the consumer's config. This lets two consumers in the same deployment bind to different backend plugins (e.g. StructuredAnalytics on Odbc, PerformanceTrends on ClickHouse). Subclasses build queries against the data source's ISqlDialect and route table identifiers through the formatter.
- L45 _private field_ `private readonly ILogger _logger`
- L46 _private field_ `private readonly IOptionsMonitor<TConfig> _config`
- L47 _private field_ `private readonly IAnalyticsDataSource _dataSource`
- L48 _private field_ `private bool _isDisposed = false`
- L53 _protected property_ `protected ILogger Logger => ...` — The logger.
- L58 _protected property_ `protected IOptionsMonitor<TConfig> Config => ...` — The config used for options.
- L63 _protected property_ `protected ISqlDialect Dialect => ...` — The SQL dialect that pairs with connections from OpenConnectionAsync.
- L68 _protected const_ `protected const string TelemetryTimestampColumn = EpicGames.Analytics.AbstractTelemetryRecord.TelemetryTimestampColumnName` — Canonical column name carrying the per-record telemetry timestamp (stamped at construction by EpicGames.Analytics.AbstractTelemetryRecord's ctor and serialized by every sink). Use this for time-range filters and ORDER-BY in consumer queries instead of a string literal.
- L75-80 _public method_ `public void Dispose()` — (inheritdoc)
- L92-105 _protected ctor_ `protected AbstractAnalyticsService(IOptionsMonitor<TConfig> config, IServiceProvider serviceProvider, ILogger logger)` — Constructor. Resolves the keyed IAnalyticsDataSource matching IAnalyticsBackendSelectorConfig.BackendName on the supplied config. The selected data source carries both its ISqlDialect.
- L110-113 _protected method_ `protected Task<DbConnection> OpenConnectionAsync(CancellationToken cancellationToken = default)` — Opens a new DbConnection via the registered IAnalyticsDataSource. The caller owns the returned connection and must dispose it.
- L119-127 _protected method_ `protected virtual void Dispose(bool disposing)` — Disposes the instance.

### `Source/Programs/Horde/Plugins/StructuredAnalytics/HordeServer.StructuredAnalytics/AnalyticsController.cs` (HordeServer.StructuredAnalytics)


#### class `HordeServer.Analytics.AnalyticsController`  
`public class AnalyticsController : HordeControllerBase`  
_public; L23-507_
- attrs: `[Authorize] [ApiController]`
- inherits: `HordeControllerBase`
- desc: Analytics Controller for structured analytics queries.
- L25 _private field_ `private readonly AnalyticsService _analyticsService`
- L26 _private field_ `private readonly IOptionsSnapshot<BuildConfig> _buildConfig`
- L27 _private field_ `private readonly IOptionsSnapshot<StructuredAnalyticsConfig> _analyticsConfig`
- L35-40 _public ctor_ `public AnalyticsController(AnalyticsService analyticsService, IOptionsSnapshot<BuildConfig> buildConfig, IOptionsSnapshot<StructuredAnalyticsConfig> analyticsConfig)` — Constructor.
- L56-86 _public method_ `public async Task<IActionResult> GetJobSummariesAsync( [FromQuery] string[] streamIds, [FromQuery] int count = StructuredAnalyticsFilter.DefaultRecordCount, [FromQuery] DateTime? minDate = null, [FromQuery] DateTime? maxDate = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/structuredanalytics/jobsummary")] [ProducesResponseType(typeof(List<JobSummaryTelemetry>), StatusCodes.Status200OK)]` — Gets job summary telemetry records.
- L104-134 _public method_ `public async Task<IActionResult> GetCommitsAsync( [FromQuery] string[] streamIds, [FromQuery] int count = StructuredAnalyticsFilter.DefaultRecordCount, [FromQuery] DateTime? minDate = null, [FromQuery] DateTime? maxDate = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/structuredanalytics/commits")] [ProducesResponseType(typeof(List<CommitTelemetry>), StatusCodes.Status200OK)]` — Gets commit telemetry records.
- L153-174 _public method_ `public async Task<IActionResult> GetIssuesAsync( [FromQuery] int count = StructuredAnalyticsFilter.DefaultRecordCount, [FromQuery] DateTime? minDate = null, [FromQuery] DateTime? maxDate = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/structuredanalytics/issues")] [ProducesResponseType(typeof(List<IssueTelemetry>), StatusCodes.Status200OK)] [ProducesResponseType(StatusCodes.Status403Forbidden)]` — Gets issue telemetry records.
- L192-222 _public method_ `public async Task<IActionResult> GetIssueSpansAsync( [FromQuery] string[] streamIds, [FromQuery] int count = StructuredAnalyticsFilter.DefaultRecordCount, [FromQuery] DateTime? minDate = null, [FromQuery] DateTime? maxDate = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/structuredanalytics/issuespans")] [ProducesResponseType(typeof(List<IssueSpanTelemetry>), StatusCodes.Status200OK)]` — Gets issue span telemetry records.
- L240-270 _public method_ `public async Task<IActionResult> GetJobLabelsAsync( [FromQuery] string[] streamIds, [FromQuery] int count = StructuredAnalyticsFilter.DefaultRecordCount, [FromQuery] DateTime? minDate = null, [FromQuery] DateTime? maxDate = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/structuredanalytics/joblabels")] [ProducesResponseType(typeof(List<JobLabelTelemetry>), StatusCodes.Status200OK)]` — Gets job label telemetry records.
- L284-314 _public method_ `public async Task<IActionResult> GetJobLabelSummariesAsync( [FromQuery] string[] streamIds, [FromQuery] int count = StructuredAnalyticsFilter.DefaultRecordCount, [FromQuery] DateTime? minDate = null, [FromQuery] DateTime? maxDate = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/structuredanalytics/joblabelsummary")] [ProducesResponseType(typeof(List<JobLabelSummaryTelemetry>), StatusCodes.Status200OK)]` — Gets job label summary telemetry records.
- L332-362 _public method_ `public async Task<IActionResult> GetJobStepRefsAsync( [FromQuery] string[] streamIds, [FromQuery] int count = StructuredAnalyticsFilter.DefaultRecordCount, [FromQuery] DateTime? minDate = null, [FromQuery] DateTime? maxDate = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/structuredanalytics/jobsteprefs")] [ProducesResponseType(typeof(List<JobStepRefTelemetry>), StatusCodes.Status200OK)]` — Gets job step ref telemetry records.
- L380-407 _public method_ `public async Task<IActionResult> GetLeaseCompletesAsync( [FromQuery] string[]? streamIds = null, [FromQuery] int count = StructuredAnalyticsFilter.DefaultRecordCount, [FromQuery] DateTime? minDate = null, [FromQuery] DateTime? maxDate = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/structuredanalytics/leasecompletes")] [ProducesResponseType(typeof(List<LeaseCompleteTelemetry>), StatusCodes.Status200OK)]` — Gets lease complete telemetry records.
- L426-447 _public method_ `public async Task<IActionResult> GetAgentTelemetryAsync( [FromQuery] int count = StructuredAnalyticsFilter.DefaultRecordCount, [FromQuery] DateTime? minDate = null, [FromQuery] DateTime? maxDate = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/structuredanalytics/agenttelemetry")] [ProducesResponseType(typeof(List<AgentTelemetry>), StatusCodes.Status200OK)] [ProducesResponseType(StatusCodes.Status403Forbidden)]` — Gets agent telemetry records.
- L458-482 _private method_ `private StreamId[] FilterAuthorizedStreams(string[]? streamIds)` — Filters the provided stream IDs to only include streams the user is authorized to access.
- L489-504 _private method_ `private bool IsAuthorizedForStream(StreamId streamId)` — Checks if the user is authorized to access a single stream.

### `Source/Programs/Horde/Plugins/StructuredAnalytics/HordeServer.StructuredAnalytics/AnalyticsService.cs` (HordeServer.StructuredAnalytics)


#### class `HordeServer.Analytics.AnalyticsService`  
`public sealed class AnalyticsService : AbstractAnalyticsService<StructuredAnalyticsConfig>`  
_public; L21-604_
- inherits: `AbstractAnalyticsService<StructuredAnalyticsConfig>`
- desc: Service responsible for obtaining analytics data. Backend-agnostic: opens connections via IAnalyticsDataSource and reads results via DbDataReader.
- L29-41 _public ctor_ `public AnalyticsService(IOptionsMonitor<StructuredAnalyticsConfig> config, IServiceProvider serviceProvider, ILogger<AnalyticsService> logger) : base(config, serviceProvider, logger)` — Constructor.
- L51-107 _public method_ `public async Task<List<JobSummaryTelemetry>> GetJobSummariesAsync(StructuredAnalyticsFilter filter, CancellationToken cancellationToken)` — Obtains the job summaries.
- L115-166 _public method_ `public async Task<List<CommitTelemetry>> GetCommitsAsync(StructuredAnalyticsFilter filter, CancellationToken cancellationToken)` — Obtains the commit telemetry records.
- L174-234 _public method_ `public async Task<List<IssueTelemetry>> GetIssuesAsync(StructuredAnalyticsFilter filter, CancellationToken cancellationToken)` — Obtains the issue telemetry records.
- L242-288 _public method_ `public async Task<List<IssueSpanTelemetry>> GetIssueSpansAsync(StructuredAnalyticsFilter filter, CancellationToken cancellationToken)` — Obtains the issue span telemetry records.
- L296-343 _public method_ `public async Task<List<JobLabelTelemetry>> GetJobLabelsAsync(StructuredAnalyticsFilter filter, CancellationToken cancellationToken)` — Obtains the job label telemetry records.
- L351-401 _public method_ `public async Task<List<JobLabelSummaryTelemetry>> GetJobLabelSummariesAsync(StructuredAnalyticsFilter filter, CancellationToken cancellationToken)` — Obtains the job label summary telemetry records.
- L409-469 _public method_ `public async Task<List<JobStepRefTelemetry>> GetJobStepRefsAsync(StructuredAnalyticsFilter filter, CancellationToken cancellationToken)` — Obtains the job step ref telemetry records.
- L477-545 _public method_ `public async Task<List<LeaseCompleteTelemetry>> GetLeaseCompletesAsync(StructuredAnalyticsFilter filter, CancellationToken cancellationToken)` — Obtains the lease complete telemetry records.
- L553-601 _public method_ `public async Task<List<AgentTelemetry>> GetAgentTelemetryAsync(StructuredAnalyticsFilter filter, CancellationToken cancellationToken)` — Obtains the agent telemetry records.

### `Source/Programs/Horde/Plugins/StructuredAnalytics/HordeServer.StructuredAnalytics/ColumnHandlers.cs` (HordeServer.StructuredAnalytics)


#### class `HordeServer.Analytics.ColumnHandlers`  
`public static class ColumnHandlers`  
_public; L13-40_
- desc: Column mapper helpers.
- L15 _private field_ `private static readonly ConcurrentDictionary<Type, bool> s_registeredTypes = ...`
- L15 _private field_ `private static readonly ConcurrentDictionary< s_registeredTypes = new()`
- L21-39 _public method_ `public static void RegisterDapperColumnMapping<T>()` — Registers column mappings for a provided type. The type should have ColumnAttribute annotations.

### `Source/Programs/Horde/Plugins/StructuredAnalytics/HordeServer.StructuredAnalytics/Controllers/TelemetrySchemasController.cs` (HordeServer.StructuredAnalytics)


#### class `HordeServer.Analytics.Controllers.TelemetrySchemasController`  
`public class TelemetrySchemasController : HordeControllerBase`  
_public; L21-635_
- attrs: `[ApiController] [Authorize] [Route("/api/v1/telemetry-schemas")]`
- inherits: `HordeControllerBase`
- desc: Controller for managing telemetry schemas
- L23 _private* field_ `readonly TelemetrySchemaService _schemaService`
- L24 _private* field_ `readonly SchemaInferenceService _inferenceService`
- L25 _private* field_ `readonly ITelemetrySchemaCollection _schemaCollection`
- L26 _private* field_ `readonly IUserCollection _userCollection`
- L27 _private* field_ `readonly ISchemaMigrator? _schemaMigrator`
- L28 _private* field_ `readonly IOptionsSnapshot<BuildConfig> _buildConfig`
- L29 _private* field_ `readonly ILogger<TelemetrySchemasController> _logger`
- L37-53 _public ctor_ `public TelemetrySchemasController( TelemetrySchemaService schemaService, SchemaInferenceService inferenceService, ITelemetrySchemaCollection schemaCollection, IUserCollection userCollection, IOptionsSnapshot<BuildConfig> buildConfig, ILogger<TelemetrySchemasController> logger, ISchemaMigrator? schemaMigrator = null)` — Constructor. schemaMigrator is optional — sinks that don't need migrations (or aren't yet implemented for a given backend) can run without one and the controller falls back to writing schemas without any DDL changes (matching the pre-migrator behaviour).
- L58-61 _private* method_ `bool AuthorizeAdmin()` — Checks if the current user has admin write permissions
- L73-84 _public method_ `public async Task<ActionResult<List<GetTelemetrySchemaResponse>>> GetAllSchemasAsync( [FromQuery] bool includeNested = false, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [ProducesResponseType(typeof(List<GetTelemetrySchemaResponse>), 200)]` — Gets all schemas (latest version per event)
- L95-111 _public method_ `public async Task<ActionResult<GetTelemetrySchemaResponse>> GetSchemaAsync( string eventName, CancellationToken cancellationToken = default)` — attrs: `[HttpGet("{eventName}")] [ProducesResponseType(typeof(GetTelemetrySchemaResponse), 200)] [ProducesResponseType(404)]` — Gets the latest schema for a specific event
- L121-132 _public method_ `public async Task<ActionResult<List<GetTelemetrySchemaResponse>>> GetSchemaVersionsAsync( string eventName, CancellationToken cancellationToken = default)` — attrs: `[HttpGet("{eventName}/versions")] [ProducesResponseType(typeof(List<GetTelemetrySchemaResponse>), 200)]` — Gets all versions of a schema
- L144-161 _public method_ `public async Task<ActionResult<GetTelemetrySchemaResponse>> GetSchemaVersionAsync( string eventName, int version, CancellationToken cancellationToken = default)` — attrs: `[HttpGet("{eventName}/versions/{version:int}")] [ProducesResponseType(typeof(GetTelemetrySchemaResponse), 200)] [ProducesResponseType(404)]` — Gets a specific version of a schema
- L172-252 _public method_ `public async Task<ActionResult<GetTelemetrySchemaResponse>> CreateSchemaAsync( [FromBody] CreateTelemetrySchemaRequest request, CancellationToken cancellationToken = default)` — attrs: `[HttpPost] [ProducesResponseType(typeof(GetTelemetrySchemaResponse), 201)] [ProducesResponseType(400)]` — Manually creates a new schema (typically used for initial setup or testing)
- L266-308 _public method_ `public ActionResult<InferSchemaResponse> InferSchema( [FromBody] InferSchemaRequest request, CancellationToken cancellationToken = default)` — attrs: `[HttpPost("infer")] [RequestSizeLimit(256 * 1024)] [ProducesResponseType(typeof(InferSchemaResponse), 200)] [ProducesResponseType(400)]` — Infers a schema proposal from a single sample JSON payload. Does not write — the returned proposal is intended to pre-fill the dashboard's authoring form so the admin can review and submit via POST /api/v1/telemetry-schemas.
- L324-372 _public method_ `public async Task<ActionResult<MigrationPlanResponse>> PreviewMigrationAsync( [FromBody] CreateTelemetrySchemaRequest request, CancellationToken cancellationToken = default)` — attrs: `[HttpPost("preview-migration")] [ProducesResponseType(typeof(MigrationPlanResponse), 200)] [ProducesResponseType(400)]` — Computes the migration plan that would run if the supplied schema were approved/created right now. Dry-run only — no DDL is executed and no metadata is written. Used by the dashboard to show admins exactly what destructive operations (column drops, type changes, table renames) a pending change will perform before they confirm. First-version schemas (no existing version for the event) return a plan with no steps and IsDestructive=false — the sink will lazy-create the table on first event.
- L384-403 _public method_ `public async Task<ActionResult> DeleteSchemaVersionAsync( string eventName, int version, CancellationToken cancellationToken = default)` — attrs: `[HttpDelete("{eventName}/versions/{version:int}")] [ProducesResponseType(204)] [ProducesResponseType(404)]` — Deletes a specific schema version
- L417-428 _public method_ `public async Task<ActionResult<List<GetPendingSchemaUpdateResponse>>> GetPendingUpdatesAsync( [FromQuery] bool includeNested = false, CancellationToken cancellationToken = default)` — attrs: `[HttpGet("pending")] [ProducesResponseType(typeof(List<GetPendingSchemaUpdateResponse>), 200)]` — Gets all pending schema updates
- L439-455 _public method_ `public async Task<ActionResult<GetPendingSchemaUpdateResponse>> GetPendingUpdateAsync( string eventName, CancellationToken cancellationToken = default)` — attrs: `[HttpGet("pending/{eventName}")] [ProducesResponseType(typeof(GetPendingSchemaUpdateResponse), 200)] [ProducesResponseType(404)]` — Gets a pending update for a specific event
- L466-511 _public method_ `public async Task<ActionResult<GetTelemetrySchemaResponse>> ApproveSchemaAsync( string eventName, CancellationToken cancellationToken = default)` — attrs: `[HttpPost("pending/{eventName}/approve")] [ProducesResponseType(typeof(GetTelemetrySchemaResponse), 200)] [ProducesResponseType(404)]` — Approves a pending schema update, creating a new schema version
- L522-538 _public method_ `public async Task<ActionResult> RejectSchemaAsync( string eventName, CancellationToken cancellationToken = default)` — attrs: `[HttpPost("pending/{eventName}/reject")] [ProducesResponseType(204)] [ProducesResponseType(404)]` — Rejects a pending schema update
- L544-559 _private* method_ `static GetTelemetrySchemaResponse ToResponse(ITelemetrySchema schema)`
- L561-578 _private* method_ `static GetPendingSchemaUpdateResponse ToPendingResponse(IPendingSchemaUpdate pending)`
- L580-593 _private* method_ `static SchemaColumnResponse ToColumnResponse(SchemaColumn column)`
- L595-614 _private* method_ `static SchemaComparisonResponse ToComparisonResponse(SchemaComparison comparison)`
- L616-632 _private* method_ `static MigrationPlanResponse ToMigrationResponse(MigrationPlan plan)`

#### class `HordeServer.Analytics.Controllers.GetTelemetrySchemaResponse`  
`public class GetTelemetrySchemaResponse`  
_public; L642-673_
- desc: Response for a telemetry schema
- L645 _public property_ `public string Id { get; set; }` — Unique identifier
- L648 _public property_ `public string EventName { get; set; }` — The telemetry event name
- L651 _public property_ `public string TableName { get; set; }` — The database table name
- L654 _public property_ `public string? SchemaName { get; set; }` — The schema/database name
- L657 _public property_ `public int Version { get; set; }` — Schema version number
- L660 _public property_ `public List<SchemaColumnResponse> Columns { get; set; }` — Column definitions
- L663 _public property_ `public DateTime CreatedAtUtc { get; set; }` — When this schema was created
- L666 _public property_ `public string? ApprovedByUserId { get; set; }` — User who approved this schema
- L669 _public property_ `public string? ClrTypeName { get; set; }` — The CLR type name
- L672 _public property_ `public bool IsNestedSchema { get; set; }` — Whether this is a nested schema

#### class `HordeServer.Analytics.Controllers.SchemaColumnResponse`  
`public class SchemaColumnResponse`  
_public; L678-703_
- desc: Response for a schema column
- L681 _public property_ `public string PropertyName { get; set; }` — C# property name
- L684 _public property_ `public string ColumnName { get; set; }` — Database column name
- L687 _public property_ `public string ClrTypeName { get; set; }` — CLR type name
- L690 _public property_ `public string DataType { get; set; }` — Fundamental data type
- L693 _public property_ `public string? ArrayElementType { get; set; }` — Array element type if DataType is Array
- L696 _public property_ `public string? NestedSchemaEventName { get; set; }` — Nested schema event name if DataType is Object
- L699 _public property_ `public bool IsNullable { get; set; }` — Whether the column is nullable
- L702 _public property_ `public int? Order { get; set; }` — Column order

#### class `HordeServer.Analytics.Controllers.GetPendingSchemaUpdateResponse`  
`public class GetPendingSchemaUpdateResponse`  
_public; L708-745_
- desc: Response for a pending schema update
- L711 _public property_ `public string Id { get; set; }` — Unique identifier
- L714 _public property_ `public string EventName { get; set; }` — The telemetry event name
- L717 _public property_ `public int ProposedVersion { get; set; }` — Proposed version number
- L720 _public property_ `public string ProposedTableName { get; set; }` — Proposed table name
- L723 _public property_ `public string? ProposedSchemaName { get; set; }` — Proposed schema/database name
- L726 _public property_ `public List<SchemaColumnResponse> ProposedColumns { get; set; }` — Proposed columns
- L729 _public property_ `public DateTime DetectedAtUtc { get; set; }` — When this update was detected
- L732 _public property_ `public string ChangeType { get; set; }` — Type of change (New/Modified)
- L735 _public property_ `public string ChangeDescription { get; set; }` — Human-readable description
- L738 _public property_ `public SchemaComparisonResponse? Comparison { get; set; }` — Detailed comparison
- L741 _public property_ `public string? ClrTypeName { get; set; }` — CLR type name
- L744 _public property_ `public bool IsNestedSchema { get; set; }` — Whether this is a nested schema

#### class `HordeServer.Analytics.Controllers.SchemaComparisonResponse`  
`public class SchemaComparisonResponse`  
_public; L750-766_
- desc: Response for schema comparison
- L753 _public property_ `public List<string> AddedColumns { get; set; }` — Added column names
- L756 _public property_ `public List<string> RemovedColumns { get; set; }` — Removed column names
- L759 _public property_ `public List<ColumnChangeResponse> ModifiedColumns { get; set; }` — Modified columns
- L762 _public property_ `public bool TableNameChanged { get; set; }` — Whether table name changed
- L765 _public property_ `public string? OldTableName { get; set; }` — Old table name if changed

#### class `HordeServer.Analytics.Controllers.ColumnChangeResponse`  
`public class ColumnChangeResponse`  
_public; L771-793_
- desc: Response for a column change
- L774 _public property_ `public string ColumnName { get; set; }` — Column name
- L777 _public property_ `public string? OldClrTypeName { get; set; }` — Old CLR type
- L780 _public property_ `public string? NewClrTypeName { get; set; }` — New CLR type
- L783 _public property_ `public string? OldDataType { get; set; }` — Old data type
- L786 _public property_ `public string? NewDataType { get; set; }` — New data type
- L789 _public property_ `public bool? OldIsNullable { get; set; }` — Old nullable state
- L792 _public property_ `public bool? NewIsNullable { get; set; }` — New nullable state

#### class `HordeServer.Analytics.Controllers.CreateTelemetrySchemaRequest`  
`public class CreateTelemetrySchemaRequest`  
_public; L798-817_
- desc: Request to create a schema manually
- L801 _public property_ `public string EventName { get; set; }` — The telemetry event name
- L804 _public property_ `public string TableName { get; set; }` — The database table name
- L807 _public property_ `public string? SchemaName { get; set; }` — The schema/database name
- L810 _public property_ `public List<CreateSchemaColumnRequest> Columns { get; set; }` — Column definitions
- L813 _public property_ `public string? ClrTypeName { get; set; }` — CLR type name
- L816 _public property_ `public bool IsNestedSchema { get; set; }` — Whether this is a nested schema

#### class `HordeServer.Analytics.Controllers.CreateSchemaColumnRequest`  
`public class CreateSchemaColumnRequest`  
_public; L822-844_
- desc: Request to create a schema column
- L825 _public property_ `public string PropertyName { get; set; }` — C# property name
- L828 _public property_ `public string ColumnName { get; set; }` — Database column name
- L831 _public property_ `public string ClrTypeName { get; set; }` — CLR type name
- L834 _public property_ `public SchemaDataType DataType { get; set; }` — Fundamental data type
- L837 _public property_ `public SchemaDataType? ArrayElementType { get; set; }` — Array element type if DataType is Array
- L840 _public property_ `public string? NestedSchemaEventName { get; set; }` — Nested schema event name if DataType is Object
- L843 _public property_ `public bool IsNullable { get; set; }` — Whether the column is nullable

#### class `HordeServer.Analytics.Controllers.InferSchemaRequest`  
`public class InferSchemaRequest`  
_public; L849-862_
- desc: Request body for POST /api/v1/telemetry-schemas/infer.
- L852 _public property_ `public string EventName { get; set; }` — The telemetry event name. Required.
- L855 _public property_ `public string? TableName { get; set; }` — Optional table name. Defaults to a snake_case form of the event name.
- L858 _public property_ `public string? SchemaName { get; set; }` — Optional schema/database name. Null falls through to the sink's DefaultDatabaseName.
- L861 _public property_ `public JsonElement SamplePayload { get; set; }` — A single sample JSON payload representing one example of the event. Must be a JSON object.

#### class `HordeServer.Analytics.Controllers.InferSchemaResponse`  
`public class InferSchemaResponse`  
_public; L868-878_
- desc: Response for POST /api/v1/telemetry-schemas/infer. The admin reviews the proposal, edits it in the dashboard form, and submits via the existing POST / endpoint.
- L871 _public property_ `public CreateTelemetrySchemaRequest Proposal { get; set; }` — Top-level proposal to pre-fill the dashboard form.
- L874 _public property_ `public List<CreateTelemetrySchemaRequest> NestedProposals { get; set; }` — One proposal per nested object discovered in the sample. Submit these before the parent so NestedSchemaEventName references resolve.
- L877 _public property_ `public List<InferenceWarningResponse> Warnings { get; set; }` — Warnings about uncertain inferences (null fields, empty arrays, mixed-type arrays, ambiguous date strings).

#### class `HordeServer.Analytics.Controllers.InferenceWarningResponse`  
`public class InferenceWarningResponse`  
_public; L883-890_
- desc: A single warning emitted during schema inference.
- L886 _public property_ `public string Path { get; set; }` — JSON path to the property that triggered the warning.
- L889 _public property_ `public string Message { get; set; }` — Human-readable explanation.

#### class `HordeServer.Analytics.Controllers.MigrationPlanResponse`  
`public class MigrationPlanResponse`  
_public; L898-917_
- desc: Response for POST /api/v1/telemetry-schemas/preview-migration. Empty plans (no steps, no warnings) indicate either a first-time schema or no migrator is registered for the active backend — the dashboard can submit without confirmation in either case.
- L901 _public property_ `public string EventName { get; set; }` — The event name being migrated.
- L904 _public property_ `public string TableName { get; set; }` — The proposed table name.
- L907 _public property_ `public string? SchemaName { get; set; }` — The proposed database/schema name (null = backend default).
- L910 _public property_ `public bool IsDestructive { get; set; }` — True when the plan contains drops, type changes, or table renames.
- L913 _public property_ `public List<string> Warnings { get; set; }` — Human-readable warnings the dashboard surfaces before approval.
- L916 _public property_ `public List<MigrationStepResponse> Steps { get; set; }` — Ordered DDL steps that will run if approved.

#### class `HordeServer.Analytics.Controllers.MigrationStepResponse`  
`public class MigrationStepResponse`  
_public; L920-930_
- desc: One DDL operation in a MigrationPlanResponse.
- L923 _public property_ `public string Kind { get; set; }` — Operation kind (AddColumn, DropColumn, DropAndAddColumn, NewTableLocation).
- L926 _public property_ `public string ColumnName { get; set; }` — Column name affected. Empty for table/database-level steps.
- L929 _public property_ `public string? Detail { get; set; }` — Free-form detail for display (type label, "old -> new", etc.).

### `Source/Programs/Horde/Plugins/StructuredAnalytics/HordeServer.StructuredAnalytics/Dialects/ISqlDialect.cs` (HordeServer.StructuredAnalytics)


#### interface `HordeServer.Dialects.ISqlDialect`  
`public interface ISqlDialect`  
_public; L14-43_
- desc: Describes the SQL flavor of an analytics backend so consumers can build dialect-appropriate parameter placeholders, identifier quotes, and command parameters without knowing which backend is wired up. Each backend plugin supplies one implementation alongside its IAnalyticsDataSource. The Phase 0 audit confirmed every today-shipping query is portable across backends, so the dialect surface is intentionally minimal — only the differences that matter on the wire.
- L21 _public* method_ `string FormatParameterPlaceholder(string canonicalName, DbType dbType)` — Renders the placeholder text that goes into the SQL command for a parameter. Examples: ? (ODBC, positional), @p0 (some named-binding dialects), {p0:Int32} (ClickHouse).
- L30 _public* method_ `void AddParameter(DbCommand command, string canonicalName, object? value, DbType dbType)` — Adds a single parameter to command, creating it via the command's own factory and binding by name (or position, depending on dialect).
- L35 _public* method_ `string QuoteIdentifier(string identifier)` — Wraps an identifier (table name, column name, schema name) in the dialect's quoting characters. Examples: "col" , `col` , [col] , or pass-through if no quoting is required.
- L42 _public* method_ `string FormatTableName(string? schemaName, string tableName)` — Formats a fully-qualified table reference suitable for inclusion in a FROM clause. Combines the optional schema/database name with the table name using the dialect's conventions for separators and quoting. ClickHouse may quote tables containing dots; standard ODBC backends use plain schema.table .

### `Source/Programs/Horde/Plugins/StructuredAnalytics/HordeServer.StructuredAnalytics/Dialects/PositionalQuestionMarkDialect.cs` (HordeServer.StructuredAnalytics)


#### class `HordeServer.Dialects.PositionalQuestionMarkDialect`  
`public sealed class PositionalQuestionMarkDialect : ISqlDialect`  
_public; L14-46_
- inherits: `ISqlDialect`
- desc: Default ISqlDialect used by WhereClauseBuilder when no backend-specific dialect is supplied. Emits positional ? placeholders matching ODBC/Simba behavior, with no identifier quoting and generic DbCommand.CreateParameter binding. Backend plugins ship their own dialect (e.g. OdbcDialect , ClickHouseSqlDialect ) that wins over this default once registered in DI; this class exists for tests and for filter call sites that have no DI access.
- L19 _public property_ `public static PositionalQuestionMarkDialect Instance { get; }` — Singleton instance.
- L21-23 _private ctor_ `private PositionalQuestionMarkDialect()`
- L26 _public method_ `public string FormatParameterPlaceholder(string canonicalName, DbType dbType)` — (inheritdoc)
- L29-36 _public method_ `public void AddParameter(DbCommand command, string canonicalName, object? value, DbType dbType)` — (inheritdoc)
- L39 _public method_ `public string QuoteIdentifier(string identifier)` — (inheritdoc)
- L42-45 _public method_ `public string FormatTableName(string? schemaName, string tableName)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/StructuredAnalytics/HordeServer.StructuredAnalytics/IAnalyticsBackendSelectorConfig.cs` (HordeServer.StructuredAnalytics)


#### interface `HordeServer.Analytics.IAnalyticsBackendSelectorConfig`  
`public interface IAnalyticsBackendSelectorConfig`  
_public; L10-16_
- desc: Marker interface implemented by every consumer-plugin config that drives an AbstractAnalyticsService{TConfig}. Exposes BackendName, which selects the keyed IAnalyticsDataSource registration the consumer should bind to. Each backend plugin ( OdbcTelemetry , ClickHouseTelemetry , ...) registers its data source under a well-known key ( "Odbc" , "ClickHouse" , ...). Consumers name the key they want here, and DI resolves the right backend per-consumer — so two consumers in the same deployment can hit different backends.
- L15 _public* property_ `string BackendName { get; }` — The key naming the registered IAnalyticsDataSource this consumer should bind to. Must match a key registered by an enabled backend plugin.

### `Source/Programs/Horde/Plugins/StructuredAnalytics/HordeServer.StructuredAnalytics/IAnalyticsConnectionConfig.cs` (HordeServer.StructuredAnalytics)


#### interface `HordeServer.Analytics.IAnalyticsConnectionConfig`  
`public interface IAnalyticsConnectionConfig : IOAuthClientCredentialsConfig`  
_public; L10-22_
- inherits: `IOAuthClientCredentialsConfig`
- desc: Connection configuration consumed by ODBC-based analytics services (AbstractAnalyticsService{TConfig}). Combines the OAuth fields from IOAuthClientCredentialsConfig with the ODBC connection-string concerns specific to query-side services. Sinks and other code paths that need the OAuth fields but not ODBC (e.g. ClickHouseTelemetry, which talks to ClickHouse over its native HTTP protocol) implement IOAuthClientCredentialsConfig directly instead of this richer interface.
- L16 _public* property_ `string ODBCConnectionString { get; }` — Connection string for ODBC connector.
- L21 _public* property_ `int? ODBCConnectionStringRefreshTimeMins { get; }` — Connection string refresh time, in minutes.

### `Source/Programs/Horde/Plugins/StructuredAnalytics/HordeServer.StructuredAnalytics/IAnalyticsDataSource.cs` (HordeServer.StructuredAnalytics)


#### interface `HordeServer.Analytics.IAnalyticsDataSource`  
`public interface IAnalyticsDataSource`  
_public; L13-24_
- desc: Backend-agnostic source of analytics database connections. Each backend plugin ( OdbcTelemetry , ClickHouseTelemetry , DatabricksTelemetry , ...) registers exactly one implementation; consumer plugins ( StructuredAnalytics , PerformanceTrends ) take this in via DI and never reference System.Data.Odbc directly. The bundled Dialect describes the SQL flavor of whatever backend opened the connection (parameter placeholder syntax, identifier quoting). Bundling avoids a separate DI lookup and guarantees the dialect always matches the connection.
- L18 _public* method_ `Task<DbConnection> OpenAsync(CancellationToken cancellationToken = default)` — Opens a new DbConnection against the configured analytics backend. The caller owns the connection and is responsible for disposing it.
- L23 _public* property_ `ISqlDialect Dialect { get; }` — SQL dialect that pairs with connections returned from OpenAsync. Owns parameter-placeholder formatting, identifier quoting, and table-name composition for this backend.

### `Source/Programs/Horde/Plugins/StructuredAnalytics/HordeServer.StructuredAnalytics/IOAuthClientCredentialsConfig.cs` (HordeServer.StructuredAnalytics)


#### interface `HordeServer.Analytics.IOAuthClientCredentialsConfig`  
`public interface IOAuthClientCredentialsConfig`  
_public; L10-33_
- desc: Common shape for any analytics-backend config that drives the generic OAuth2 client-credentials token exchange. Each backend plugin's config (e.g. OdbcTelemetryConfig , ClickHouseTelemetryConfig , DatabricksTelemetryConfig ) implements this directly — or via a stricter interface that adds backend-specific fields — so it can be the TConfig of OAuthClientCredentialsTokenProvider{TConfig}.
- L15 _public* property_ `string OAuthTokenEndpoint { get; }` — HTTPS endpoint for the OAuth2 client-credentials token exchange. When empty, the auth provider is inert: every call returns null, so connection strings (and HTTP requests) flow through untouched. Required only for token-authenticated backends.
- L20 _public* property_ `string OAuthScope { get; }` — OAuth2 scope passed in the client-credentials request (form field scope ). Empty omits the field. Defaults to all-apis for Databricks; other providers may need a URL-shaped scope or none at all.
- L27 _public* property_ `string OAuthAccessTokenFragmentKey { get; }` — Connection-string key the access token is folded into when building the final ODBC connection string. Defaults to Auth_AccessToken for the Simba Spark ODBC driver. Other ODBC drivers may use different keys. Irrelevant for HTTP-based backends that consume the token via the raw IAuthenticationProvider{TConfig}.GetTokenAsync path (e.g. as an Authorization: Bearer header).
- L32 _public* property_ `string OAuthCredentialsSecretId { get; }` — Secret-store ID under which the OAuth client_id and client_secret are stored. Override per deployment if multiple OAuth providers coexist.

### `Source/Programs/Horde/Plugins/StructuredAnalytics/HordeServer.StructuredAnalytics/ITableNameFormatter.cs` (HordeServer.StructuredAnalytics)


#### interface `HordeServer.Analytics.ITableNameFormatter`  
`public interface ITableNameFormatter`  
_public; L9-18_
- desc: Interface for formatting table names for different database backends. Implementations provide database-specific quoting and formatting rules.
- L17 _public* method_ `string FormatTableName(string? schema, string tableName)` — Formats a fully qualified table name for the target database.

### `Source/Programs/Horde/Plugins/StructuredAnalytics/HordeServer.StructuredAnalytics/OAuthClientCredentialsTokenProvider.cs` (HordeServer.StructuredAnalytics)


#### class `HordeServer.Analytics.OAuthClientCredentialsTokenProvider`  
`public class OAuthClientCredentialsTokenProvider<TConfig> : IAuthenticationProvider<TConfig> where TConfig : class, IOAuthClientCredentialsConfig`  
_public; L16-192_
- inherits: `IAuthenticationProvider<TConfig>`
- constraints: `where TConfig : class, IOAuthClientCredentialsConfig`
- desc: Generic OAuth2 client-credentials token provider for analytics ODBC connections. Exchanges a client_id/client_secret pair (read from the secret store) for a short-lived access token at the configured OAuthTokenEndpoint then folds the token into the ODBC connection string under the configured fragment key.
- L18 _private const_ `private const int DEFAULT_REFRESH_BUFFER = 5`
- L19 _private const_ `private const int DEFAULT_REFRESH_MIN = 5`
- L21 _private field_ `private string? _cachedToken = String.Empty`
- L22 _private field_ `private DateTime _tokenExpiry`
- L24 _private field_ `private readonly IOptionsMonitor<TConfig> _config`
- L25 _private field_ `private readonly IServiceProvider _serviceProvider`
- L26 _private field_ `private readonly IHttpClientFactory _httpClientFactory`
- L27 _private field_ `private readonly ILogger<OAuthClientCredentialsTokenProvider<TConfig>> _logger`
- L36-51 _public ctor_ `public OAuthClientCredentialsTokenProvider( IOptionsMonitor<TConfig> config, IHttpClientFactory httpClientFactory, IServiceProvider serviceProvider, ILogger<OAuthClientCredentialsTokenProvider<TConfig>> logger)` — Constructor.
- L56-74 _public method_ `public async Task<KeyValuePair<string, string>?> GetConnectionStringAuthenticationFragmentAsync()` — (inheritdoc)
- L77-189 _public method_ `public async Task<string?> GetTokenAsync()` — (inheritdoc)

### `Source/Programs/Horde/Plugins/StructuredAnalytics/HordeServer.StructuredAnalytics/Schemas/ISchemaMigrator.cs` (HordeServer.StructuredAnalytics)


#### interface `HordeServer.Analytics.Schemas.ISchemaMigrator`  
`public interface ISchemaMigrator`  
_public; L18-34_
- desc: Plans and applies destination-side schema migrations for a telemetry sink. One implementation per backend (ClickHouse, BigQuery, etc.). The schema service computes a backend-agnostic MigrationPlan, then this migrator translates it into the backend's DDL. The controller uses this in two phases: 1. PlanAsync for a dry-run preview returned to the dashboard so admins can see destructive operations before approving. 2. ApplyAsync as part of the create/approve flow, run BEFORE the new schema version is committed so a DDL failure leaves the system consistent (Mongo metadata never gets ahead of the actual table shape).
- L26 _public* method_ `Task<MigrationPlan?> PlanAsync(string eventName, IReadOnlyList<SchemaColumn> proposedColumns, string proposedTableName, string? proposedSchemaName, CancellationToken cancellationToken = default)` — Computes the steps needed to evolve the current latest stored version of eventName into proposedColumns. Returns null when no current version exists — first-time schemas need no migration; the sink will lazy-create the table on its first event.
- L33 _public* method_ `Task ApplyAsync(MigrationPlan plan, CancellationToken cancellationToken = default)` — Executes the DDL described by plan. No-op for plans with no steps. Throws on any DDL failure — callers must not commit the new schema version if this throws.

#### class `HordeServer.Analytics.Schemas.MigrationPlan`  
`public class MigrationPlan`  
_public; L40-70_
- desc: Backend-agnostic description of the work required to evolve a stored schema's underlying table from the current shape to a proposed shape.
- L43 _public property_ `public string EventName { get; set; }` — The event name being migrated.
- L46 _public property_ `public string TableName { get; set; }` — The proposed table name.
- L49 _public property_ `public string? SchemaName { get; set; }` — The proposed database/schema name (null = backend default).
- L55 _public property_ `public List<MigrationStep> Steps { get; set; }` — Ordered DDL steps. Apply in order; on any failure, abort and do not commit the metadata change.
- L62 _public property_ `public List<string> Warnings { get; set; }` — Human-readable warnings the dashboard surfaces to the admin before approval. Populated for every destructive step (drops, type changes, renames, table/database changes).
- L69 _public property_ `public bool IsDestructive { get; set; }` — True when the plan contains any irreversible operation: column drops, type changes (drop+readd), or a table/database rename (old data orphaned). The dashboard uses this to gate a confirmation dialog.

#### class `HordeServer.Analytics.Schemas.MigrationStep`  
`public class MigrationStep`  
_public; L73-95_
- desc: One DDL operation in a MigrationPlan.
- L76 _public property_ `public MigrationStepKind Kind { get; set; }` — The kind of operation.
- L79 _public property_ `public string ColumnName { get; set; }` — Column name affected. Empty for table/database-level steps.
- L85 _public property_ `public string? Detail { get; set; }` — Free-form detail for display (e.g. "Int64 -> String" for a type change, or the old table name for a rename).
- L94 _public property_ `public SchemaColumn? Column { get; set; }` — Portable column definition for AddColumn and DropAndAddColumn steps — carries the StructuredAnalytics-native types (SchemaDataType, SchemaColumn.IsNullable, etc.). Backend migrators translate to their own DDL via their existing type mappers at apply time. Null for DropColumn and NewTableLocation steps which need no type info.

#### enum `HordeServer.Analytics.Schemas.MigrationStepKind`  
`public enum MigrationStepKind`  
_public; L102-123_
- desc: Distinct kinds of migration step. The dashboard categorises these into "safe" (additive) and "destructive" (drops, type changes, table renames) for the warning UX.
- L105 _public* enumerator_ `AddColumn` — ALTER TABLE ... ADD COLUMN. Non-destructive. Existing rows get NULL/default.
- L108 _public* enumerator_ `DropColumn` — ALTER TABLE ... DROP COLUMN. Destroys all stored data for that column.
- L115 _public* enumerator_ `DropAndAddColumn` — Drop existing column then add fresh with the new type. Used for both renames (different name) and type changes (same name). Destroys all stored data for that column.
- L122 _public* enumerator_ `NewTableLocation` — Table or database name has changed in the new version. No DDL is run against the existing table; the sink will lazy-create the new table on its first event. Old data is left in place at the old name.

### `Source/Programs/Horde/Plugins/StructuredAnalytics/HordeServer.StructuredAnalytics/Schemas/ITelemetrySchemaCache.cs` (HordeServer.StructuredAnalytics)


#### interface `HordeServer.Analytics.Schemas.ITelemetrySchemaCache`  
`public interface ITelemetrySchemaCache`  
_public; L11-26_
- desc: In-memory snapshot of the latest telemetry schemas, kept fresh across worker instances via a Redis-backed version counter on ITelemetrySchemaCollection. Hot-path consumers should read Schemas rather than calling ITelemetrySchemaCollection.GetLatestSchemaAsync per event.
- L17 _public* property_ `IReadOnlyDictionary<string, ITelemetrySchema> Schemas { get; }` — Snapshot of the latest schemas keyed by event name. The dictionary reference is replaced atomically on refresh; readers see an internally consistent snapshot.
- L25 _public* event_ `event Action<IReadOnlyDictionary<string, ITelemetrySchema>> SchemasChanged` — Raised after the cache has been updated. Handlers receive the new snapshot. Subscribe with += ; unsubscribe with -= . Handlers are invoked on the refresh ticker thread, one at a time, with exceptions logged and isolated — keep handlers fast and avoid blocking work.
- L25 _public* event_ `event Action<IReadOnlyDictionary<ITelemetrySchema>> SchemasChanged` — Raised after the cache has been updated. Handlers receive the new snapshot. Subscribe with += ; unsubscribe with -= . Handlers are invoked on the refresh ticker thread, one at a time, with exceptions logged and isolated — keep handlers fast and avoid blocking work.

### `Source/Programs/Horde/Plugins/StructuredAnalytics/HordeServer.StructuredAnalytics/Schemas/ITelemetrySchemaCollection.cs` (HordeServer.StructuredAnalytics)


#### interface `HordeServer.Analytics.Schemas.ITelemetrySchemaCollection`  
`public interface ITelemetrySchemaCollection`  
_public; L10-145_
- desc: Collection for managing telemetry schemas and pending updates
- L27 _public* method_ `Task<ITelemetrySchema> AddSchemaAsync( string eventName, string tableName, string? schemaName, int version, List<SchemaColumn> columns, string? clrTypeName, bool isNestedSchema, UserId? approvedByUserId = null, CancellationToken cancellationToken = default)` — Adds a new schema version
- L44 _public* method_ `Task<ITelemetrySchema?> GetLatestSchemaAsync(string eventName, CancellationToken cancellationToken = default)` — Gets the latest schema version for an event name
- L53 _public* method_ `Task<ITelemetrySchema?> GetSchemaAsync(string eventName, int version, CancellationToken cancellationToken = default)` — Gets a specific schema version
- L61 _public* method_ `Task<List<ITelemetrySchema>> GetSchemaVersionsAsync(string eventName, CancellationToken cancellationToken = default)` — Gets all versions of a schema
- L69 _public* method_ `Task<List<ITelemetrySchema>> GetAllLatestSchemasAsync(bool includeNested = false, CancellationToken cancellationToken = default)` — Gets the latest schema for all event names
- L78 _public* method_ `Task<bool> DeleteSchemaAsync(string eventName, int version, CancellationToken cancellationToken = default)` — Deletes a specific schema version
- L86 _public* method_ `Task<int> GetHighestVersionAsync(string eventName, CancellationToken cancellationToken = default)` — Gets the highest version number for an event name
- L107 _public* method_ `Task<IPendingSchemaUpdate> UpsertPendingUpdateAsync( string eventName, int proposedVersion, string proposedTableName, string? proposedSchemaName, List<SchemaColumn> proposedColumns, SchemaChangeType changeType, string changeDescription, SchemaComparison? comparison, string? clrTypeName, bool isNestedSchema, CancellationToken cancellationToken = default)` — Creates or updates a pending schema update (supersedes existing)
- L126 _public* method_ `Task<IPendingSchemaUpdate?> GetPendingUpdateAsync(string eventName, CancellationToken cancellationToken = default)` — Gets a pending update for an event name
- L134 _public* method_ `Task<List<IPendingSchemaUpdate>> GetAllPendingUpdatesAsync(bool includeNested = false, CancellationToken cancellationToken = default)` — Gets all pending updates
- L142 _public* method_ `Task<bool> DeletePendingUpdateAsync(string eventName, CancellationToken cancellationToken = default)` — Deletes a pending update

### `Source/Programs/Horde/Plugins/StructuredAnalytics/HordeServer.StructuredAnalytics/Schemas/PendingSchemaUpdateDocument.cs` (HordeServer.StructuredAnalytics)


#### interface `HordeServer.Analytics.Schemas.IPendingSchemaUpdate`  
`public interface IPendingSchemaUpdate`  
_public; L11-72_
- desc: Interface for a pending schema update awaiting admin approval
- L16 _public* property_ `ObjectId Id { get; }` — Unique identifier
- L21 _public* property_ `string EventName { get; }` — The telemetry event name this update applies to
- L26 _public* property_ `int ProposedVersion { get; }` — The proposed version number (highest existing + 1)
- L31 _public* property_ `string ProposedTableName { get; }` — The proposed table name
- L36 _public* property_ `string? ProposedSchemaName { get; }` — The proposed schema/database name
- L41 _public* property_ `IReadOnlyList<SchemaColumn> ProposedColumns { get; }` — The proposed column definitions
- L46 _public* property_ `DateTime DetectedAtUtc { get; }` — When this pending update was detected
- L51 _public* property_ `SchemaChangeType ChangeType { get; }` — Type of change (New or Modified)
- L56 _public* property_ `string ChangeDescription { get; }` — Human-readable description of the changes
- L61 _public* property_ `SchemaComparison? Comparison { get; }` — Detailed comparison with previous schema (null for new schemas)
- L66 _public* property_ `string? ClrTypeName { get; }` — The fully qualified CLR type name
- L71 _public* property_ `bool IsNestedSchema { get; }` — True if this is a nested schema

#### class `HordeServer.Analytics.Schemas.PendingSchemaUpdateDocument`  
`class PendingSchemaUpdateDocument : IPendingSchemaUpdate`  
_internal*; L77-190_
- inherits: `IPendingSchemaUpdate`
- desc: MongoDB document representing a pending schema change awaiting approval
- L83 _public property_ `public ObjectId Id { get; set; }` — attrs: `[BsonRequired, BsonId]` — Unique identifier
- L90 _public property_ `public string EventName { get; set; }` — attrs: `[BsonRequired]` — The telemetry event name this update applies to. Unique index ensures only one pending update per event.
- L96 _public property_ `public int ProposedVersion { get; set; }` — attrs: `[BsonRequired]` — The proposed version number (highest existing + 1)
- L102 _public property_ `public string ProposedTableName { get; set; }` — attrs: `[BsonRequired]` — The proposed table name
- L108 _public property_ `public string? ProposedSchemaName { get; set; }` — attrs: `[BsonIgnoreIfNull]` — The proposed schema/database name
- L114 _public property_ `public List<SchemaColumn> ProposedColumns { get; set; }` — attrs: `[BsonRequired]` — The proposed column definitions
- L116 _private* property_ `IReadOnlyList<SchemaColumn> IPendingSchemaUpdate.ProposedColumns => ...`
- L122 _public property_ `public DateTime DetectedAtUtc { get; set; }` — attrs: `[BsonRequired]` — When this pending update was detected
- L128 _public property_ `public SchemaChangeType ChangeType { get; set; }` — attrs: `[BsonRequired]` — Type of change (New or Modified)
- L134 _public property_ `public string ChangeDescription { get; set; }` — attrs: `[BsonRequired]` — Human-readable description of the changes
- L140 _public property_ `public SchemaComparison? Comparison { get; set; }` — attrs: `[BsonIgnoreIfNull]` — Detailed comparison with previous schema (null for new schemas)
- L146 _public property_ `public string? ClrTypeName { get; set; }` — attrs: `[BsonIgnoreIfNull]` — The fully qualified CLR type name
- L152 _public property_ `public bool IsNestedSchema { get; set; }` — attrs: `[BsonRequired]` — True if this is a nested schema
- L158-160 _private ctor_ `private PendingSchemaUpdateDocument()` — attrs: `[BsonConstructor]` — Private constructor for MongoDB deserialization
- L165-189 _public ctor_ `public PendingSchemaUpdateDocument( string eventName, int proposedVersion, string proposedTableName, string? proposedSchemaName, List<SchemaColumn> proposedColumns, SchemaChangeType changeType, string changeDescription, SchemaComparison? comparison, string? clrTypeName, bool isNestedSchema)` — Creates a new pending schema update document

### `Source/Programs/Horde/Plugins/StructuredAnalytics/HordeServer.StructuredAnalytics/Schemas/SchemaColumn.cs` (HordeServer.StructuredAnalytics)


#### enum `HordeServer.Analytics.Schemas.SchemaDataType`  
`public enum SchemaDataType`  
_public; L11-49_
- desc: Fundamental data types supported by telemetry schemas. These are database-agnostic types that sinks map to their native types.
- L16 _public* enumerator_ `String` — String type. CLR mappings: string, char, Guid, enums
- L21 _public* enumerator_ `Int64` — 64-bit integer. CLR mappings: byte, sbyte, short, ushort, int, uint, long, ulong, TimeSpan (as ticks)
- L26 _public* enumerator_ `Double` — Double-precision floating point. CLR mappings: float, double, decimal
- L31 _public* enumerator_ `Bool` — Boolean. CLR mappings: bool
- L36 _public* enumerator_ `DateTime` — Date and time. CLR mappings: DateTime, DateTimeOffset
- L42 _public* enumerator_ `Object` — Nested object with its own schema. CLR mappings: complex types References a nested schema via NestedSchemaEventName
- L48 _public* enumerator_ `Array` — Array/list of elements. CLR mappings: T[], List<T>, IEnumerable<T> Element type specified via ArrayElementType

#### class `HordeServer.Analytics.Schemas.SchemaColumn`  
`public class SchemaColumn`  
_public; L54-105_
- desc: Represents a column in a telemetry schema
- L60 _public property_ `public string PropertyName { get; set; }` — attrs: `[BsonRequired]` — The C# property name
- L66 _public property_ `public string ColumnName { get; set; }` — attrs: `[BsonRequired]` — The database column name (from [Column] attribute)
- L73 _public property_ `public string ClrTypeName { get; set; }` — attrs: `[BsonRequired]` — The CLR type name (e.g., "System.String", "System.Int32", "System.Nullable`1[[System.DateTime]]") Used for advanced scenarios like enum parsing via TypeHandlers
- L79 _public property_ `public SchemaDataType DataType { get; set; }` — attrs: `[BsonRequired]` — The fundamental schema data type
- L85 _public property_ `public SchemaDataType? ArrayElementType { get; set; }` — attrs: `[BsonIgnoreIfNull]` — If DataType is Array, specifies the element type
- L92 _public property_ `public string? NestedSchemaEventName { get; set; }` — attrs: `[BsonIgnoreIfNull]` — If DataType is Object (or Array of Object), references the nested schema's event name. Nested schemas use synthetic event names like "__nested.{FullTypeName}"
- L98 _public property_ `public bool IsNullable { get; set; }` — attrs: `[BsonRequired]` — Whether the column is nullable
- L104 _public property_ `public int? Order { get; set; }` — attrs: `[BsonIgnoreIfNull]` — Optional ordering hint to preserve property order from reflection

#### class `HordeServer.Analytics.Schemas.ColumnChange`  
`public class ColumnChange`  
_public; L110-153_
- desc: Describes a change to a single column
- L116 _public property_ `public string ColumnName { get; set; }` — attrs: `[BsonRequired]` — The column name that changed
- L122 _public property_ `public string? OldClrTypeName { get; set; }` — attrs: `[BsonIgnoreIfNull]` — The old CLR type name (null if column was added)
- L128 _public property_ `public string? NewClrTypeName { get; set; }` — attrs: `[BsonIgnoreIfNull]` — The new CLR type name (null if column was removed)
- L134 _public property_ `public SchemaDataType? OldDataType { get; set; }` — attrs: `[BsonIgnoreIfNull]` — The old data type (null if column was added)
- L140 _public property_ `public SchemaDataType? NewDataType { get; set; }` — attrs: `[BsonIgnoreIfNull]` — The new data type (null if column was removed)
- L146 _public property_ `public bool? OldIsNullable { get; set; }` — attrs: `[BsonIgnoreIfNull]` — The old nullable state (null if column was added)
- L152 _public property_ `public bool? NewIsNullable { get; set; }` — attrs: `[BsonIgnoreIfNull]` — The new nullable state (null if column was removed)

#### class `HordeServer.Analytics.Schemas.SchemaComparison`  
`public class SchemaComparison`  
_public; L158-221_
- desc: Detailed comparison between two schema versions
- L163 _public property_ `public List<string> AddedColumns { get; set; }` — Column names that were added
- L168 _public property_ `public List<string> RemovedColumns { get; set; }` — Column names that were removed
- L173 _public property_ `public List<ColumnChange> ModifiedColumns { get; set; }` — Columns that changed type or nullability
- L178 _public property_ `public bool TableNameChanged { get; set; }` — Whether the table name changed
- L184 _public property_ `public string? OldTableName { get; set; }` — attrs: `[BsonIgnoreIfNull]` — The old table name if it changed
- L190 _public property_ `public bool HasColumnChanges => ...` — attrs: `[BsonIgnore]` — Returns true if there are any column changes
- L195-220 _public method_ `public string GetChangeDescription()` — Generates a human-readable description of the changes

#### enum `HordeServer.Analytics.Schemas.SchemaChangeType`  
`public enum SchemaChangeType`  
_public; L226-237_
- desc: Type of schema change
- L231 _public* enumerator_ `New` — First-time schema (no previous version exists)
- L236 _public* enumerator_ `Modified` — Modification to existing schema

### `Source/Programs/Horde/Plugins/StructuredAnalytics/HordeServer.StructuredAnalytics/Schemas/SchemaInferenceService.cs` (HordeServer.StructuredAnalytics)


#### class `HordeServer.Analytics.Schemas.InferenceResult`  
`public class InferenceResult`  
_public; L13-32_
- desc: Result of inferring a schema from a sample JSON payload.
- L18 _public property_ `public required CreateTelemetrySchemaRequest Proposal { get; set; }` — Top-level proposal the admin will review and submit via POST /api/v1/telemetry-schemas.
- L25 _public property_ `public List<CreateTelemetrySchemaRequest> NestedProposals { get; set; }` — One proposal per nested object discovered in the sample. The caller must submit these before submitting Proposal so the parent's NestedSchemaEventName references resolve at lookup time.
- L31 _public property_ `public List<InferenceWarning> Warnings { get; set; }` — Warnings about uncertain inferences the admin should review (null fields, empty arrays, mixed-type arrays, ambiguous date strings).

#### class `HordeServer.Analytics.Schemas.InferenceWarning`  
`public class InferenceWarning`  
_public; L37-48_
- desc: A single warning emitted during schema inference.
- L42 _public property_ `public required string Path { get; set; }` — JSON path to the property that triggered the warning (e.g. "details.items[0]").
- L47 _public property_ `public required string Message { get; set; }` — Human-readable explanation.

#### class `HordeServer.Analytics.Schemas.SchemaInferenceService`  
`public class SchemaInferenceService`  
_public; L55-363_
- desc: Walks a single sample JSON payload and produces a CreateTelemetrySchemaRequest proposal that an admin can review and submit. Never writes to MongoDB or Redis; the inference endpoint is a pure pre-fill helper for the schema authoring form.
- L57 _private* field_ `readonly ILogger<SchemaInferenceService> _logger`
- L62 _private* field_ `static readonly Regex s_iso8601Regex = new(@"^\d{4}-\d{2}-\d{2}([T ]\d{2}:\d{2}(:\d{2})?(\.\d+)?(Z|[+-]\d{2}:?\d{2})?)?$", RegexOptions.Compiled)`
- L65 _private* field_ `static readonly Regex s_acronymBoundary = new(@"([A-Z]+)([A-Z][a-z])", RegexOptions.Compiled)`
- L66 _private* field_ `static readonly Regex s_wordBoundary = new(@"([a-z\d])([A-Z])", RegexOptions.Compiled)`
- L71-74 _public ctor_ `public SchemaInferenceService(ILogger<SchemaInferenceService> logger)` — Constructor
- L84-116 _public method_ `public InferenceResult Infer(string eventName, string? tableName, string? schemaName, JsonElement samplePayload)` — Infers a schema proposal from a single sample JSON object.
- L122-142 _private* method_ `List<CreateSchemaColumnRequest> InferObjectColumns( JsonElement obj, string contextEventName, string parentJsonPath, List<InferenceWarning> warnings, List<CreateTelemetrySchemaRequest> nested)` — Walks the properties of a JSON object and produces one column per property. Recurses into nested objects, emitting sibling proposals into nested.
- L150-171 _private* method_ `CreateSchemaColumnRequest? InferColumn( string propertyName, JsonElement value, string contextEventName, string jsonPath, List<InferenceWarning> warnings, List<CreateTelemetrySchemaRequest> nested)` — Produces a single column from a JSON property value. Admin-authored schemas don't have a separate CLR property → DB column mapping; the JSON key is both the PropertyName the sink looks up at runtime AND the ColumnName the table uses. Keep them identical so producers' JSON keys match table columns 1:1.
- L177-254 _private* method_ `(SchemaDataType DataType, SchemaDataType? ArrayElementType, string? NestedSchemaEventName, string? ClrTypeName) InferType( JsonElement value, string contextEventName, string propertyName, string jsonPath, List<InferenceWarning> warnings, List<CreateTelemetrySchemaRequest> nested)` — Determines the schema type for a JSON value. For objects, also enqueues a nested proposal in nested via recursive inference.
- L260-321 _private* method_ `(SchemaDataType DataType, SchemaDataType? ArrayElementType, string? NestedSchemaEventName, string? ClrTypeName) InferArrayType( JsonElement array, string contextEventName, string propertyName, string jsonPath, List<InferenceWarning> warnings, List<CreateTelemetrySchemaRequest> nested)` — Determines the element type for a JSON array. Empty arrays default to String with a warning. Mixed-kind arrays fall back to String element + warning.
- L323-326 _private* method_ `static bool LooksLikeIso8601DateTime(string? s)`
- L333-338 _private* method_ `static string DefaultTableNameFor(string eventName)` — Default table name when the caller does not supply one. Lowercases the event name and replaces dots with underscores so identifiers like "State.Agent.Telemetry" become "state_agent_telemetry" (a valid ClickHouse identifier).
- L344-362 _internal method_ `internal static string ToSnakeCase(string name)` — Converts a CamelCase / camelCase / acronym-prefixed name to snake_case. "JobId" → "job_id"; "HTTPServer" → "http_server"; "agentId" → "agent_id".

### `Source/Programs/Horde/Plugins/StructuredAnalytics/HordeServer.StructuredAnalytics/Schemas/TelemetrySchemaCache.cs` (HordeServer.StructuredAnalytics)


#### class `HordeServer.Analytics.Schemas.TelemetrySchemaCache`  
`public sealed class TelemetrySchemaCache : ITelemetrySchemaCache, IHostedService, IAsyncDisposable`  
_public; L20-180_
- inherits: `ITelemetrySchemaCache, IHostedService, IAsyncDisposable`
- desc: Polls a Redis version counter set by TelemetrySchemaCollection on schema mutations. When the counter advances, reloads the latest schemas from MongoDB into an in-memory snapshot and notifies subscribers. Owning the polling loop here means each Horde worker runs at most one ticker and one MongoDB reload per change, regardless of how many sinks or plugins consume the schemas.
- L22 _private* field_ `readonly ITelemetrySchemaCollection _schemaCollection`
- L23 _private* field_ `readonly IRedisService _redisService`
- L24 _private* field_ `readonly ITicker _refreshTicker`
- L25 _private* field_ `readonly ILogger _logger`
- L31 _private* field_ `volatile Dictionary<string, ITelemetrySchema> _schemas = ...`
- L31 _private* field_ `volatile Dictionary< _schemas = new(StringComparer.OrdinalIgnoreCase)`
- L32 _private* field_ `long _lastSeenVersion = -1`
- L33 _private* field_ `bool _disposed`
- L35 _private* field_ `static readonly TimeSpan s_refreshInterval = TimeSpan.FromMinutes(5)`
- L38 _public property_ `public IReadOnlyDictionary<string, ITelemetrySchema> Schemas => ...` — (inheritdoc)
- L41 _public event_ `public event Action<IReadOnlyDictionary<string, ITelemetrySchema>>? SchemasChanged` — (inheritdoc)
- L41 _public event_ `public event Action<IReadOnlyDictionary<ITelemetrySchema>>? SchemasChanged` — (inheritdoc)
- L46-56 _public ctor_ `public TelemetrySchemaCache( ITelemetrySchemaCollection schemaCollection, IRedisService redisService, IClock clock, ILogger<TelemetrySchemaCache> logger)` — Constructor
- L61-65 _private* method_ `async ValueTask<TimeSpan?> TickAsync(CancellationToken cancellationToken)` — Ticker entry point: run a refresh check, then schedule the next tick s_refreshInterval later.
- L68-71 _public method_ `public Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L74-77 _public method_ `public async Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L80-88 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L95-121 _private* method_ `async ValueTask RefreshIfChangedAsync(CancellationToken cancellationToken)` — Ticker callback. Reads the Redis version counter; if it has advanced past the last-seen value, reloads the cache from MongoDB. A Redis or Mongo failure leaves the existing cache in place — never clears it on error.
- L126-131 _private* method_ `async Task<long> ReadVersionAsync()` — Reads the current Redis schema-version counter. Returns 0 if the key is unset.
- L138-154 _private* method_ `async Task ReloadAsync(long version, CancellationToken cancellationToken)` — Loads all latest schemas (including nested) from MongoDB, atomically replaces the in-memory snapshot, records the new last-seen version, and notifies subscribers.
- L160-179 _private* method_ `void NotifySubscribers(IReadOnlyDictionary<string, ITelemetrySchema> snapshot)` — Invokes each subscriber with the new snapshot. A faulty subscriber is logged and isolated so it cannot block other subscribers or take down the ticker.

### `Source/Programs/Horde/Plugins/StructuredAnalytics/HordeServer.StructuredAnalytics/Schemas/TelemetrySchemaCollection.cs` (HordeServer.StructuredAnalytics)


#### class `HordeServer.Analytics.Schemas.TelemetrySchemaCollection`  
`public class TelemetrySchemaCollection : ITelemetrySchemaCollection`  
_public; L15-298_
- inherits: `ITelemetrySchemaCollection`
- desc: MongoDB implementation of the telemetry schema collection
- L22 _public const_ `public const string RedisSchemaVersionKey = "structured_analytics:schemas:version"` — Redis key holding a monotonic counter of schema collection mutations. Subscribers (e.g. ClickHouseTelemetrySink) compare against their last-seen value to detect cluster-wide schema changes without polling MongoDB.
- L24 _private* field_ `readonly IMongoCollection<TelemetrySchemaDocument> _schemas`
- L25 _private* field_ `readonly IMongoCollection<PendingSchemaUpdateDocument> _pendingUpdates`
- L26 _private* field_ `readonly IRedisService _redisService`
- L27 _private* field_ `readonly ILogger<TelemetrySchemaCollection> _logger`
- L31 _private* field_ `readonly MongoIndex<TelemetrySchemaDocument> _eventNameVersionIndex`
- L36-80 _public ctor_ `public TelemetrySchemaCollection(IMongoService mongoService, IRedisService redisService, ILogger<TelemetrySchemaCollection> logger)` — Constructor
- L92 _private* method_ `static string Normalize(string eventName)` — Canonical form of every event name that crosses this collection's API surface. Both writes (AddSchemaAsync, UpsertPendingUpdateAsync) and reads (Get*, Delete*) normalize before touching MongoDB so casing differences between admin authoring, REST API producers, and reflection-detected schemas can never produce silent duplicates or missed lookups.
- L96-109 _public method_ `public async Task<ITelemetrySchema> AddSchemaAsync(string eventName, string tableName, string? schemaName, int version, List<SchemaColumn> columns, string? clrTypeName, bool isNestedSchema, UserId? approvedByUserId = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L112-124 _public method_ `public async Task<ITelemetrySchema?> GetLatestSchemaAsync(string eventName, CancellationToken cancellationToken = default)` — (inheritdoc)
- L127-131 _public method_ `public async Task<ITelemetrySchema?> GetSchemaAsync(string eventName, int version, CancellationToken cancellationToken = default)` — (inheritdoc)
- L134-140 _public method_ `public async Task<List<ITelemetrySchema>> GetSchemaVersionsAsync(string eventName, CancellationToken cancellationToken = default)` — (inheritdoc)
- L143-153 _public method_ `public async Task<List<ITelemetrySchema>> GetAllLatestSchemasAsync(bool includeNested = false, CancellationToken cancellationToken = default)` — (inheritdoc)
- L156-168 _public method_ `public async Task<bool> DeleteSchemaAsync(string eventName, int version, CancellationToken cancellationToken = default)` — (inheritdoc)
- L176-192 _private* method_ `async Task BumpRedisSchemaVersionAsync()` — Atomically bumps the Redis schema-version counter so subscribers in other workers detect the change on their next refresh tick. Mongo write must succeed first; a failure here is logged but does not propagate (Mongo is the source of truth and a missed bump is recovered by the next successful write or a periodic backstop reload).
- L195-208 _public method_ `public async Task<int> GetHighestVersionAsync(string eventName, CancellationToken cancellationToken = default)` — (inheritdoc)
- L215-254 _public method_ `public async Task<IPendingSchemaUpdate> UpsertPendingUpdateAsync( string eventName, int proposedVersion, string proposedTableName, string? proposedSchemaName, List<SchemaColumn> proposedColumns, SchemaChangeType changeType, string changeDescription, SchemaComparison? comparison, string? clrTypeName, bool isNestedSchema, CancellationToken cancellationToken = default)` — (inheritdoc)
- L257-264 _public method_ `public async Task<IPendingSchemaUpdate?> GetPendingUpdateAsync(string eventName, CancellationToken cancellationToken = default)` — (inheritdoc)
- L267-279 _public method_ `public async Task<List<IPendingSchemaUpdate>> GetAllPendingUpdatesAsync(bool includeNested = false, CancellationToken cancellationToken = default)` — (inheritdoc)
- L282-295 _public method_ `public async Task<bool> DeletePendingUpdateAsync(string eventName, CancellationToken cancellationToken = default)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/StructuredAnalytics/HordeServer.StructuredAnalytics/Schemas/TelemetrySchemaDocument.cs` (HordeServer.StructuredAnalytics)


#### interface `HordeServer.Analytics.Schemas.ITelemetrySchema`  
`public interface ITelemetrySchema`  
_public; L12-65_
- desc: Interface for a telemetry schema
- L17 _public* property_ `ObjectId Id { get; }` — Unique identifier
- L23 _public* property_ `string EventName { get; }` — The telemetry event name (from [TelemetryEvent] attribute). For nested schemas, uses synthetic format: "__nested.{FullTypeName}"
- L28 _public* property_ `string TableName { get; }` — The database table name (from [Table] attribute)
- L34 _public* property_ `string? SchemaName { get; }` — The schema/database name (from [Table] attribute Schema property). May be null/empty if no schema was specified.
- L39 _public* property_ `int Version { get; }` — Schema version number. Latest = highest version for a given EventName.
- L44 _public* property_ `IReadOnlyList<SchemaColumn> Columns { get; }` — Column definitions
- L49 _public* property_ `DateTime CreatedAtUtc { get; }` — When this schema version was created
- L54 _public* property_ `UserId? ApprovedByUserId { get; }` — User who approved this schema (null for auto-created first versions)
- L59 _public* property_ `string? ClrTypeName { get; }` — The fully qualified CLR type name that this schema represents
- L64 _public* property_ `bool IsNestedSchema { get; }` — True if this is a nested schema (referenced by Object columns in other schemas)

#### class `HordeServer.Analytics.Schemas.TelemetrySchemaDocument`  
`class TelemetrySchemaDocument : ITelemetrySchema`  
_internal*; L70-183_
- inherits: `ITelemetrySchema`
- desc: MongoDB document representing an approved telemetry schema version
- L75 _public const_ `public const string NestedSchemaPrefix = "__nested."` — Prefix for synthetic event names used by nested schemas
- L81 _public property_ `public ObjectId Id { get; set; }` — attrs: `[BsonRequired, BsonId]` — Unique identifier
- L88 _public property_ `public string EventName { get; set; }` — attrs: `[BsonRequired]` — The telemetry event name (from [TelemetryEvent] attribute). For nested schemas, uses synthetic format: "__nested.{FullTypeName}"
- L94 _public property_ `public string TableName { get; set; }` — attrs: `[BsonRequired]` — The database table name (from [Table] attribute)
- L101 _public property_ `public string? SchemaName { get; set; }` — attrs: `[BsonIgnoreIfNull]` — The schema/database name (from [Table] attribute Schema property). May be null/empty if no schema was specified.
- L107 _public property_ `public int Version { get; set; }` — attrs: `[BsonRequired]` — Schema version number. Latest = highest version for a given EventName.
- L113 _public property_ `public List<SchemaColumn> Columns { get; set; }` — attrs: `[BsonRequired]` — Column definitions
- L115 _private* property_ `IReadOnlyList<SchemaColumn> ITelemetrySchema.Columns => ...`
- L121 _public property_ `public DateTime CreatedAtUtc { get; set; }` — attrs: `[BsonRequired]` — When this schema version was created
- L127 _public property_ `public UserId? ApprovedByUserId { get; set; }` — attrs: `[BsonIgnoreIfNull]` — User who approved this schema (null for auto-created first versions)
- L133 _public property_ `public string? ClrTypeName { get; set; }` — attrs: `[BsonIgnoreIfNull]` — The fully qualified CLR type name that this schema represents
- L139 _public property_ `public bool IsNestedSchema { get; set; }` — attrs: `[BsonRequired]` — True if this is a nested schema (referenced by Object columns in other schemas)
- L145-147 _private ctor_ `private TelemetrySchemaDocument()` — attrs: `[BsonConstructor]` — Private constructor for MongoDB deserialization
- L152-172 _public ctor_ `public TelemetrySchemaDocument( string eventName, string tableName, string? schemaName, int version, List<SchemaColumn> columns, string? clrTypeName, bool isNestedSchema, UserId? approvedByUserId = null)` — Creates a new schema document
- L177 _public method_ `public static string GetNestedSchemaEventName(string clrTypeName)` — Generates a synthetic event name for a nested schema
- L182 _public method_ `public static bool IsNestedSchemaEventName(string eventName)` — Checks if an event name represents a nested schema

### `Source/Programs/Horde/Plugins/StructuredAnalytics/HordeServer.StructuredAnalytics/Schemas/TelemetrySchemaService.cs` (HordeServer.StructuredAnalytics)


#### class `HordeServer.Analytics.Schemas.ReflectedSchema`  
`public class ReflectedSchema`  
_public; L14-50_
- desc: Represents a schema extracted from a CLR type via reflection
- L19 _public property_ `public required string EventName { get; init; }` — The telemetry event name (from TelemetryEventAttribute attribute)
- L24 _public property_ `public required string TableName { get; init; }` — The database table name (from TableAttribute attribute)
- L29 _public property_ `public string? SchemaName { get; init; }` — The schema/database name (from TableAttribute attribute Schema property)
- L34 _public property_ `public required Type ClrType { get; init; }` — The CLR type that this schema represents
- L39 _public property_ `public required List<SchemaColumn> Columns { get; init; }` — Column definitions
- L44 _public property_ `public required bool IsNestedSchema { get; init; }` — Whether this is a nested schema
- L49 _public property_ `public required List<Type> ReferencedNestedTypes { get; init; }` — Nested types that this schema references.

#### class `HordeServer.Analytics.Schemas.TelemetrySchemaService`  
`public class TelemetrySchemaService`  
_public; L56-798_
- desc: Service for managing telemetry schemas, including reflection-based schema extraction, comparison, and approval workflows.
- L58 _private* field_ `readonly ITelemetrySchemaCollection _schemaCollection`
- L59 _private* field_ `readonly ILogger<TelemetrySchemaService> _logger`
- L64-70 _public ctor_ `public TelemetrySchemaService( ITelemetrySchemaCollection schemaCollection, ILogger<TelemetrySchemaService> logger)` — Constructor
- L78-151 _public method_ `public ReflectedSchema? BuildSchemaFromType(Type type)` — Builds a schema from a CLR type that has AnalyticsTableGenAttribute and TelemetryEventAttribute attributes
- L157-179 _public method_ `public ReflectedSchema? BuildNestedSchema(Type type)` — Builds a nested schema from a complex type (no attributes required)
- L181-309 _private* method_ `ReflectedSchema? BuildSchemaFromTypeInternal(Type type, string eventName, string tableName, string? schemaName, bool isNestedSchema)`
- L315-326 _private* method_ `(SchemaDataType DataType, SchemaDataType? ArrayElementType, Type? NestedType) MapClrTypeToSchemaTypeSafe(Type clrType)` — Maps a CLR type to the fundamental schema type system (safe version with try/catch)
- L331-479 _private* method_ `static (SchemaDataType DataType, SchemaDataType? ArrayElementType, Type? NestedType) MapClrTypeToSchemaType(Type clrType)` — Maps a CLR type to the fundamental schema type system
- L484-494 _private* method_ `static string GetClrTypeNameSafe(Type type)` — Gets the full CLR type name for storage (safe version)
- L499-513 _private* method_ `static bool IsNullableTypeSafe(Type type)` — Checks if a type is nullable (reference type or Nullable<T>) - safe version
- L523-540 _private* method_ `static bool IsPrimitiveLikeType(Type type)` — Determines if a type is "primitive-like" - meaning it has a well-defined string representation and should not be treated as a nested schema. Common examples: StreamId, UserId, ProjectId, etc.
- L549-637 _public method_ `public SchemaComparison CompareSchemas( IReadOnlyList<SchemaColumn> existingColumns, string existingTableName, IReadOnlyList<SchemaColumn> newColumns, string newTableName)` — Compares two schemas and returns the differences
- L650-690 _public method_ `public async Task<ITelemetrySchema?> ApproveSchemaAsync( string eventName, UserId approvedByUserId, CancellationToken cancellationToken = default)` — Approves a pending schema update, creating a new schema version
- L698-716 _public method_ `public async Task<bool> RejectSchemaAsync(string eventName, CancellationToken cancellationToken = default)` — Rejects a pending schema update
- L729-795 _public method_ `public async Task<SchemaSyncResult> SyncSchemaAsync(ReflectedSchema reflected, CancellationToken cancellationToken = default)` — Syncs a reflected schema with the database. Creates new schema if none exists, or creates pending update if columns differ.

#### enum `HordeServer.Analytics.Schemas.SchemaSyncResult`  
`public enum SchemaSyncResult`  
_public; L803-824_
- desc: Result of syncing a schema with the database
- L808 _public* enumerator_ `Created` — Schema was auto-created (first version)
- L813 _public* enumerator_ `Unchanged` — Schema exists and matches - no action taken
- L818 _public* enumerator_ `PendingCreated` — Schema differs - pending update created
- L823 _public* enumerator_ `Error` — An error occurred during sync

### `Source/Programs/Horde/Plugins/StructuredAnalytics/HordeServer.StructuredAnalytics/Schemas/TelemetrySchemaStartupService.cs` (HordeServer.StructuredAnalytics)


#### class `HordeServer.Analytics.Schemas.TelemetrySchemaStartupService`  
`public class TelemetrySchemaStartupService : BackgroundService`  
_public; L15-279_
- inherits: `BackgroundService`
- desc: Background service that scans assemblies shortly after startup to discover and sync telemetry schemas. Runs off the host startup critical path so a slow or unreachable database cannot block boot or trip the health-check grace period.
- L17 _private* field_ `readonly TelemetrySchemaService _schemaService`
- L18 _private* field_ `readonly ILogger<TelemetrySchemaStartupService> _logger`
- L23-29 _public ctor_ `public TelemetrySchemaStartupService( TelemetrySchemaService schemaService, ILogger<TelemetrySchemaStartupService> logger)` — Constructor
- L32-50 _protected method_ `protected override async Task ExecuteAsync(CancellationToken stoppingToken)` — (inheritdoc)
- L56-243 _private* method_ `async Task ScanAndSyncSchemasAsync(CancellationToken cancellationToken)` — Scans all loaded assemblies for types with [AnalyticsTableGen] and [TelemetryEvent] attributes, then syncs them with the database.
- L248-260 _private* method_ `static bool HasRequiredAttributes(Type type)` — Quick check for required attributes without full reflection
- L266-278 _private* method_ `static bool ShouldSkipAssembly(string assemblyName)` — Determines if an assembly should be skipped for telemetry scanning. Only skips Microsoft/System standard library assemblies.

### `Source/Programs/Horde/Plugins/StructuredAnalytics/HordeServer.StructuredAnalytics/StructuredAnalyticsConfig.cs` (HordeServer.StructuredAnalytics)


#### class `HordeServer.StructuredAnalyticsConfig`  
`public class StructuredAnalyticsConfig : IPluginConfig, IAnalyticsBackendSelectorConfig`  
_public; L13-37_
- inherits: `IPluginConfig, IAnalyticsBackendSelectorConfig`
- desc: Configuration for the StructuredAnalytics plugin. StructuredAnalytics is backend-agnostic: it consumes whatever HordeServer.Analytics.IAnalyticsDataSource the named backend plugin registers under BackendName. Connection strings, OAuth fields, and ODBC plumbing live on the backend plugin's config — not here.
- L18 _public property_ `public string BackendName { get; set; }` — Selects which backend plugin's IAnalyticsDataSource this consumer binds to. Must match a key registered by an enabled backend plugin (e.g. "Odbc" for OdbcTelemetry , "ClickHouse" for ClickHouseTelemetry ).
- L24 _public property_ `public bool DisableStreamBasedAuth { get; set; }` — Whether to disable stream-based authorization for analytics endpoints. When true, all authenticated users can access analytics data without stream-level ACL checks.
- L31 _public property_ `public bool AllowNonAdminQueryAccess { get; set; }` — Whether to allow non-admin users to access the endpoints that don't have stream guards. When false (default), only users with admin claims can access analytics data. When true, all authenticated users can access analytics telemetry data.
- L34-36 _public method_ `public void PostLoad(PluginConfigOptions configOptions)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/StructuredAnalytics/HordeServer.StructuredAnalytics/StructuredAnalyticsFilter.cs` (HordeServer.StructuredAnalytics)


#### struct `HordeServer.Analytics.ParameterEntry`  
`public readonly struct ParameterEntry : IEquatable<ParameterEntry>`  
_public; L14-59_
- inherits: `IEquatable<ParameterEntry>`
- desc: One bound parameter — name, value, and logical DbType — produced by WhereClauseBuilder and consumed by WhereClauseResult.ApplyTo. Backend-agnostic; the concrete DbParameter is materialised from the command's own factory at apply time.
- L19 _public property_ `public string Name { get; }` — Auto-generated parameter name (e.g. p0 , p1 ) corresponding to the placeholder in the clause text.
- L24 _public property_ `public object? Value { get; }` — Parameter value. Null is preserved here and converted to DBNull.Value by the dialect at bind time.
- L29 _public property_ `public DbType DbType { get; }` — Logical type of the value.
- L34-39 _public ctor_ `public ParameterEntry(string name, object? value, DbType dbType)` — Constructor.
- L42 _public method_ `public bool Equals(ParameterEntry other)` — (inheritdoc)
- L45 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L48 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L53 _public operator_ `public static bool operator ==(ParameterEntry left, ParameterEntry right)` — Equality.
- L58 _public operator_ `public static bool operator !=(ParameterEntry left, ParameterEntry right)` — Inequality.

#### class `HordeServer.Analytics.WhereClauseBuilder`  
`public class WhereClauseBuilder`  
_public; L67-339_
- desc: Fluent builder for constructing SQL WHERE clauses with parameterized queries.
- L69 _private field_ `private readonly ISqlDialect _dialect`
- L70 _private field_ `private readonly List<string> _clauses = new()`
- L71 _private field_ `private readonly List<ParameterEntry> _parameters = new()`
- L72 _private field_ `private readonly StringBuilder _currentGroup = new()`
- L73 _private field_ `private string _pendingOperator = String.Empty`
- L78-80 _public ctor_ `public WhereClauseBuilder() : this(PositionalQuestionMarkDialect.Instance)` — Constructs a builder that emits positional ? placeholders. Used by tests and by call sites that don't have access to a backend's dialect via DI.
- L85-88 _public ctor_ `public WhereClauseBuilder(ISqlDialect dialect)` — Constructs a builder that delegates placeholder formatting and parameter binding to dialect. Backend-fronted call sites (e.g. AbstractAnalyticsService.Dialect ) supply this.
- L97-107 _public method_ `public WhereClauseBuilder And(string column, string op, object value, DbType dbType)` — Adds an AND condition.
- L116-126 _public method_ `public WhereClauseBuilder Or(string column, string op, object value, DbType dbType)` — Adds an OR condition.
- L132-144 _public method_ `public WhereClauseBuilder AndIsNotNull(string column)` — Adds an AND IS NOT NULL condition.
- L150-162 _public method_ `public WhereClauseBuilder AndIsNull(string column)` — Adds an AND IS NULL condition.
- L172-180 _public method_ `public WhereClauseBuilder AndIf(bool condition, string column, string op, object value, DbType dbType)` — Conditionally adds an AND condition.
- L188-196 _public method_ `public WhereClauseBuilder AndIfNotEmpty(string? value, string column, DbType dbType = DbType.AnsiString)` — Conditionally adds an AND condition for non-null/empty strings.
- L206-214 _public method_ `public WhereClauseBuilder AndIfNotNull<T>(T? value, string column, string op, DbType dbType) where T : struct` — Conditionally adds an AND condition for non-null values.
- L219-231 _public method_ `public WhereClauseBuilder BeginGroupAnd()` — Starts a grouped expression with AND (opens parenthesis).
- L236-248 _public method_ `public WhereClauseBuilder BeginGroupOr()` — Starts a grouped expression with OR (opens parenthesis).
- L253-259 _public method_ `public WhereClauseBuilder EndGroup()` — Ends a grouped expression (closes parenthesis).
- L265-277 _public method_ `public WhereClauseResult Build()` — Builds the final WHERE clause result.
- L284-304 _public method_ `public static WhereClauseBuilder From(WhereClauseResult existing)` — Creates a builder initialized with an existing WhereClauseResult. Inherits the existing result's dialect so the merged builder emits matching placeholders.
- L308-314 _private method_ `private bool NeedsOperator()`
- L316-327 _private method_ `private void AppendCondition(string column, string op, object value, DbType dbType)`
- L329-336 _private method_ `private void FlushCurrentGroup()`

#### struct `HordeServer.Analytics.WhereClauseResult`  
`public readonly struct WhereClauseResult`  
_public; L344-405_
- desc: Utility struct representing a where clause and its bound parameters. Apply via ApplyTo on any DbCommand.
- L351 _public property_ `public string Clause { get; }` — The string representation of the where clause.
- L356 _public property_ `public IReadOnlyList<ParameterEntry> Parameters { get; }` — The parameters associated with the where Clause.
- L361 _public property_ `public ISqlDialect Dialect { get; }` — The dialect that produced this result. Reused by ApplyTo for parameter binding and by WhereClauseBuilder.From when extending.
- L368-371 _public ctor_ `public WhereClauseResult(string clause, IReadOnlyList<ParameterEntry> parameters) : this(clause, parameters, PositionalQuestionMarkDialect.Instance)` — Constructor that defaults to the positional ? dialect. Used by tests and by call sites that don't have access to a backend's dialect.
- L379-384 _public ctor_ `public WhereClauseResult(string clause, IReadOnlyList<ParameterEntry> parameters, ISqlDialect dialect)` — Constructor that captures a backend-specific dialect.
- L390-402 _public method_ `public void ApplyTo(DbCommand command)` — Applies the where clause's parameters to a provided command. Binds via the captured dialect so the concrete DbParameter instances match the command (Odbc, ClickHouse, ADBC, etc.).

#### struct `HordeServer.Analytics.StructuredAnalyticsFilter`  
`public struct StructuredAnalyticsFilter`  
_public; L410-491_
- desc: Filter object for structured analytics queries.
- L415 _public const_ `public const int MaximumRecordCount = 10000` — The maximum record count to return from a query.
- L420 _public const_ `public const int DefaultRecordCount = 100` — The default record count to return from a query.
- L422 _private field_ `private int _recordCount`
- L427-431 _public property_ `public int RecordCount { get; set; }` — The maximum number of records to obtain.
- L436 _public property_ `public StreamId[]? StreamIds { get; set; }` — The stream IDs to filter by.
- L441 _public property_ `public DateTime? MinDate { get; set; }` — The minimum date to obtain.
- L446 _public property_ `public DateTime? MaxDate { get; set; }` — The maximum date to obtain.
- L451 _public property_ `public int? MinSchemaVersion { get; set; }` — The minimum schema version to filter by.
- L461-490 _public method_ `public WhereClauseResult BuildWhereClause(string streamIdColumn, string? dateColumn = null, string? schemaVersionColumn = null, ISqlDialect? dialect = null)` — Constructs a WhereClauseResult based on the AND of every enabled filter parameter.

### `Source/Programs/Horde/Plugins/StructuredAnalytics/HordeServer.StructuredAnalytics/StructuredAnalyticsPlugin.cs` (HordeServer.StructuredAnalytics)


#### class `HordeServer.StructuredAnalyticsPlugin`  
`public class StructuredAnalyticsPlugin : IPluginStartup`  
_public; L16-49_
- attrs: `[Plugin("StructuredAnalytics", EnabledByDefault = false, GlobalConfigType = typeof(StructuredAnalyticsConfig), ServerConfigType = typeof(StructuredAnalyticsServerConfig))]`
- inherits: `IPluginStartup`
- desc: Entry point for the StructuredAnalytics plugin
- L21-23 _public ctor_ `public StructuredAnalyticsPlugin()` — Constructor
- L26-28 _public method_ `public void Configure(IApplicationBuilder app)` — (inheritdoc)
- L31-48 _public method_ `public void ConfigureServices(IServiceCollection serviceCollection)` — (inheritdoc)

#### class `HordeServer.StructuredAnalyticsExtensions`  
`public static class StructuredAnalyticsExtensions`  
_public; L54-67_
- desc: Helper methods for StructuredAnalytics plugin config
- L59 _public method_ `public static void AddStructuredAnalyticsConfig(this IDictionary<PluginName, IPluginConfig> dictionary, StructuredAnalyticsConfig config)` — Configures the StructuredAnalytics plugin
- L65 _public method_ `public static StructuredAnalyticsConfig GetStructuredAnalyticsConfig(this IDictionary<PluginName, IPluginConfig> dictionary)` — Gets configuration for the StructuredAnalytics plugin

### `Source/Programs/Horde/Plugins/StructuredAnalytics/HordeServer.StructuredAnalytics/StructuredAnalyticsServerConfig.cs` (HordeServer.StructuredAnalytics)


#### class `HordeServer.StructuredAnalyticsServerConfig`  
`public class StructuredAnalyticsServerConfig : PluginServerConfig`  
_public; L10-12_
- inherits: `PluginServerConfig`
- desc: Server-specific configuration for the StructuredAnalytics plugin

### `Source/Programs/Horde/Plugins/StructuredAnalytics/HordeServer.StructuredAnalytics/TypeHandlers.cs` (HordeServer.StructuredAnalytics)


#### class `HordeServer.Analytics.TypeHandlers`  
`public static class TypeHandlers`  
_public; L27-69_
- desc: Type handler helpers.
- L32-62 _public method_ `public static void RegisterTypeHandlers()` — Registers type handlers.
- L67 _internal method_ `internal static bool IsNullOrEmpty(object? value)` — Helper to check if a value is null or empty for parsing purposes.

#### class `HordeServer.Analytics.StringArrayTypeHandler`  
`public class StringArrayTypeHandler : SqlMapper.TypeHandler<string?[]>`  
_public; L74-91_
- inherits: `SqlMapper.TypeHandler<string?[]>`
- desc: Type handler for string arrays (JSON serialized).
- L77-84 _public method_ `public override string?[] Parse(object? value)` — (inheritdoc)
- L87-90 _public method_ `public override void SetValue(IDbDataParameter parameter, string?[]? value)` — (inheritdoc)

#### class `HordeServer.Analytics.StreamIdHandler`  
`public class StreamIdHandler : SqlMapper.TypeHandler<StreamId>`  
_public; L98-107_
- inherits: `SqlMapper.TypeHandler<StreamId>`
- desc: Type handler for StreamId.
- L100 _internal method_ `internal static StreamId ParseCore(object value)`
- L103 _public method_ `public override void SetValue(IDbDataParameter parameter, StreamId value)` — (inheritdoc)
- L106 _public method_ `public override StreamId Parse(object? value)` — (inheritdoc)

#### class `HordeServer.Analytics.NullableStreamIdHandler`  
`public class NullableStreamIdHandler : SqlMapper.TypeHandler<StreamId?>`  
_public; L112-119_
- inherits: `SqlMapper.TypeHandler<StreamId?>`
- desc: Type handler for nullable StreamId.
- L115 _public method_ `public override void SetValue(IDbDataParameter parameter, StreamId? value)` — (inheritdoc)
- L118 _public method_ `public override StreamId? Parse(object? value)` — (inheritdoc)

#### class `HordeServer.Analytics.TemplateIdHandler`  
`public class TemplateIdHandler : SqlMapper.TypeHandler<TemplateId>`  
_public; L124-133_
- inherits: `SqlMapper.TypeHandler<TemplateId>`
- desc: Type handler for TemplateId.
- L126 _internal method_ `internal static TemplateId ParseCore(object value)`
- L129 _public method_ `public override void SetValue(IDbDataParameter parameter, TemplateId value)` — (inheritdoc)
- L132 _public method_ `public override TemplateId Parse(object? value)` — (inheritdoc)

#### class `HordeServer.Analytics.JobIdHandler`  
`public class JobIdHandler : SqlMapper.TypeHandler<JobId>`  
_public; L138-147_
- inherits: `SqlMapper.TypeHandler<JobId>`
- desc: Type handler for JobId.
- L140 _internal method_ `internal static JobId ParseCore(object value)`
- L143 _public method_ `public override void SetValue(IDbDataParameter parameter, JobId value)` — (inheritdoc)
- L146 _public method_ `public override JobId Parse(object? value)` — (inheritdoc)

#### class `HordeServer.Analytics.JobStepIdHandler`  
`public class JobStepIdHandler : SqlMapper.TypeHandler<JobStepId>`  
_public; L152-161_
- inherits: `SqlMapper.TypeHandler<JobStepId>`
- desc: Type handler for JobStepId.
- L154 _internal method_ `internal static JobStepId ParseCore(object value)`
- L157 _public method_ `public override void SetValue(IDbDataParameter parameter, JobStepId value)` — (inheritdoc)
- L160 _public method_ `public override JobStepId Parse(object? value)` — (inheritdoc)

#### class `HordeServer.Analytics.ObjectIdHandler`  
`public class ObjectIdHandler : SqlMapper.TypeHandler<ObjectId>`  
_public; L166-175_
- inherits: `SqlMapper.TypeHandler<ObjectId>`
- desc: Type handler for ObjectId.
- L168 _internal method_ `internal static ObjectId ParseCore(object value)`
- L171 _public method_ `public override void SetValue(IDbDataParameter parameter, ObjectId value)` — (inheritdoc)
- L174 _public method_ `public override ObjectId Parse(object? value)` — (inheritdoc)

#### class `HordeServer.Analytics.AgentIdHandler`  
`public class AgentIdHandler : SqlMapper.TypeHandler<AgentId>`  
_public; L180-189_
- inherits: `SqlMapper.TypeHandler<AgentId>`
- desc: Type handler for AgentId.
- L182 _internal method_ `internal static AgentId ParseCore(object value)`
- L185 _public method_ `public override void SetValue(IDbDataParameter parameter, AgentId value)` — (inheritdoc)
- L188 _public method_ `public override AgentId Parse(object? value)` — (inheritdoc)

#### class `HordeServer.Analytics.LeaseIdHandler`  
`public class LeaseIdHandler : SqlMapper.TypeHandler<LeaseId>`  
_public; L194-203_
- inherits: `SqlMapper.TypeHandler<LeaseId>`
- desc: Type handler for LeaseId.
- L196 _internal method_ `internal static LeaseId ParseCore(object value)`
- L199 _public method_ `public override void SetValue(IDbDataParameter parameter, LeaseId value)` — (inheritdoc)
- L202 _public method_ `public override LeaseId Parse(object? value)` — (inheritdoc)

#### class `HordeServer.Analytics.NullableLeaseIdHandler`  
`public class NullableLeaseIdHandler : SqlMapper.TypeHandler<LeaseId?>`  
_public; L208-215_
- inherits: `SqlMapper.TypeHandler<LeaseId?>`
- desc: Type handler for nullable LeaseId.
- L211 _public method_ `public override void SetValue(IDbDataParameter parameter, LeaseId? value)` — (inheritdoc)
- L214 _public method_ `public override LeaseId? Parse(object? value)` — (inheritdoc)

#### class `HordeServer.Analytics.SessionIdHandler`  
`public class SessionIdHandler : SqlMapper.TypeHandler<SessionId>`  
_public; L220-229_
- inherits: `SqlMapper.TypeHandler<SessionId>`
- desc: Type handler for SessionId.
- L222 _internal method_ `internal static SessionId ParseCore(object value)`
- L225 _public method_ `public override void SetValue(IDbDataParameter parameter, SessionId value)` — (inheritdoc)
- L228 _public method_ `public override SessionId Parse(object? value)` — (inheritdoc)

#### class `HordeServer.Analytics.PoolIdHandler`  
`public class PoolIdHandler : SqlMapper.TypeHandler<PoolId>`  
_public; L234-243_
- inherits: `SqlMapper.TypeHandler<PoolId>`
- desc: Type handler for PoolId.
- L236 _internal method_ `internal static PoolId ParseCore(object value)`
- L239 _public method_ `public override void SetValue(IDbDataParameter parameter, PoolId value)` — (inheritdoc)
- L242 _public method_ `public override PoolId Parse(object? value)` — (inheritdoc)

#### class `HordeServer.Analytics.NullablePoolIdHandler`  
`public class NullablePoolIdHandler : SqlMapper.TypeHandler<PoolId?>`  
_public; L248-255_
- inherits: `SqlMapper.TypeHandler<PoolId?>`
- desc: Type handler for nullable PoolId.
- L251 _public method_ `public override void SetValue(IDbDataParameter parameter, PoolId? value)` — (inheritdoc)
- L254 _public method_ `public override PoolId? Parse(object? value)` — (inheritdoc)

#### class `HordeServer.Analytics.LogIdHandler`  
`public class LogIdHandler : SqlMapper.TypeHandler<LogId>`  
_public; L260-269_
- inherits: `SqlMapper.TypeHandler<LogId>`
- desc: Type handler for LogId.
- L262 _internal method_ `internal static LogId ParseCore(object value)`
- L265 _public method_ `public override void SetValue(IDbDataParameter parameter, LogId value)` — (inheritdoc)
- L268 _public method_ `public override LogId Parse(object? value)` — (inheritdoc)

#### class `HordeServer.Analytics.NullableLogIdHandler`  
`public class NullableLogIdHandler : SqlMapper.TypeHandler<LogId?>`  
_public; L274-281_
- inherits: `SqlMapper.TypeHandler<LogId?>`
- desc: Type handler for nullable LogId.
- L277 _public method_ `public override void SetValue(IDbDataParameter parameter, LogId? value)` — (inheritdoc)
- L280 _public method_ `public override LogId? Parse(object? value)` — (inheritdoc)

#### class `HordeServer.Analytics.UserIdHandler`  
`public class UserIdHandler : SqlMapper.TypeHandler<UserId>`  
_public; L286-295_
- inherits: `SqlMapper.TypeHandler<UserId>`
- desc: Type handler for UserId.
- L288 _internal method_ `internal static UserId ParseCore(object value)`
- L291 _public method_ `public override void SetValue(IDbDataParameter parameter, UserId value)` — (inheritdoc)
- L294 _public method_ `public override UserId Parse(object? value)` — (inheritdoc)

#### class `HordeServer.Analytics.NullableUserIdHandler`  
`public class NullableUserIdHandler : SqlMapper.TypeHandler<UserId?>`  
_public; L300-307_
- inherits: `SqlMapper.TypeHandler<UserId?>`
- desc: Type handler for nullable UserId.
- L303 _public method_ `public override void SetValue(IDbDataParameter parameter, UserId? value)` — (inheritdoc)
- L306 _public method_ `public override UserId? Parse(object? value)` — (inheritdoc)

#### class `HordeServer.Analytics.CommitIdHandler`  
`public class CommitIdHandler : SqlMapper.TypeHandler<CommitId>`  
_public; L312-324_
- inherits: `SqlMapper.TypeHandler<CommitId>`
- desc: Type handler for CommitId.
- L314 _internal method_ `internal static CommitId ParseCore(object value)`
- L317-320 _public method_ `public override void SetValue(IDbDataParameter parameter, CommitId? value)` — (inheritdoc)
- L323 _public method_ `public override CommitId Parse(object? value)` — (inheritdoc)

#### class `HordeServer.Analytics.NullableCommitIdHandler`  
`public class NullableCommitIdHandler : SqlMapper.TypeHandler<CommitId?>`  
_public; L329-336_
- inherits: `SqlMapper.TypeHandler<CommitId?>`
- desc: Type handler for nullable CommitId.
- L332 _public method_ `public override void SetValue(IDbDataParameter parameter, CommitId? value)` — (inheritdoc)
- L335 _public method_ `public override CommitId? Parse(object? value)` — (inheritdoc)

#### class `HordeServer.Analytics.LeaseOutcomeHandler`  
`public class LeaseOutcomeHandler : SqlMapper.TypeHandler<LeaseOutcome>`  
_public; L345-360_
- inherits: `SqlMapper.TypeHandler<LeaseOutcome>`
- desc: Type handler for LeaseOutcome.
- L348 _public method_ `public override void SetValue(IDbDataParameter parameter, LeaseOutcome value)` — (inheritdoc)
- L351-359 _public method_ `public override LeaseOutcome Parse(object? value)` — (inheritdoc)

#### class `HordeServer.Analytics.LeaseOutcomeReasonHandler`  
`public class LeaseOutcomeReasonHandler : SqlMapper.TypeHandler<LeaseOutcomeReason>`  
_public; L365-379_
- inherits: `SqlMapper.TypeHandler<LeaseOutcomeReason>`
- desc: Type handler for LeaseOutcomeReason.
- L368 _public method_ `public override void SetValue(IDbDataParameter parameter, LeaseOutcomeReason value)` — (inheritdoc)
- L371-378 _public method_ `public override LeaseOutcomeReason Parse(object? value)` — (inheritdoc)

#### class `HordeServer.Analytics.JobStepOutcomeHandler`  
`public class JobStepOutcomeHandler : SqlMapper.TypeHandler<JobStepOutcome>`  
_public; L384-395_
- inherits: `SqlMapper.TypeHandler<JobStepOutcome>`
- desc: Type handler for JobStepOutcome.
- L386 _internal method_ `internal static JobStepOutcome ParseCore(object value)`
- L390 _public method_ `public override void SetValue(IDbDataParameter parameter, JobStepOutcome value)` — (inheritdoc)
- L393 _public method_ `public override JobStepOutcome Parse(object? value)` — (inheritdoc)

#### class `HordeServer.Analytics.NullableJobStepOutcomeHandler`  
`public class NullableJobStepOutcomeHandler : SqlMapper.TypeHandler<JobStepOutcome?>`  
_public; L400-408_
- inherits: `SqlMapper.TypeHandler<JobStepOutcome?>`
- desc: Type handler for nullable JobStepOutcome.
- L403 _public method_ `public override void SetValue(IDbDataParameter parameter, JobStepOutcome? value)` — (inheritdoc)
- L406 _public method_ `public override JobStepOutcome? Parse(object? value)` — (inheritdoc)

#### class `HordeServer.Analytics.JobStepStateHandler`  
`public class JobStepStateHandler : SqlMapper.TypeHandler<JobStepState>`  
_public; L413-424_
- inherits: `SqlMapper.TypeHandler<JobStepState>`
- desc: Type handler for JobStepState.
- L415 _internal method_ `internal static JobStepState ParseCore(object value)`
- L419 _public method_ `public override void SetValue(IDbDataParameter parameter, JobStepState value)` — (inheritdoc)
- L422 _public method_ `public override JobStepState Parse(object? value)` — (inheritdoc)

#### class `HordeServer.Analytics.NullableJobStepStateHandler`  
`public class NullableJobStepStateHandler : SqlMapper.TypeHandler<JobStepState?>`  
_public; L429-437_
- inherits: `SqlMapper.TypeHandler<JobStepState?>`
- desc: Type handler for nullable JobStepState.
- L432 _public method_ `public override void SetValue(IDbDataParameter parameter, JobStepState? value)` — (inheritdoc)
- L435 _public method_ `public override JobStepState? Parse(object? value)` — (inheritdoc)

#### class `HordeServer.Analytics.FingerprintTelemetryHandler`  
`public class FingerprintTelemetryHandler : SqlMapper.TypeHandler<FingerprintTelemetry>`  
_public; L446-508_
- inherits: `SqlMapper.TypeHandler<FingerprintTelemetry>`
- desc: Type handler for FingerprintTelemetry.
- L448 _private field_ `private static readonly JsonSerializerOptions s_jsonOptions = new JsonSerializerOptions { PropertyNameCaseInsensitive = true }`
- L451-454 _public method_ `public override void SetValue(IDbDataParameter parameter, FingerprintTelemetry? value)` — (inheritdoc)
- L456-487 _internal method_ `internal static FingerprintTelemetry ParseCore(object value)`
- L490 _public method_ `public override FingerprintTelemetry Parse(object? value)` — (inheritdoc)

#### class `HordeServer.Analytics.FingerprintTelemetryHandler.FingerprintDto`  
`private class FingerprintDto`  
_private; L493-500_
- L496 _public property_ `public string? Type { get; set; }` — attrs: `[System.Text.Json.Serialization.JsonPropertyName(HordeServer_Issues_FingerprintTelemetryGen.Type)]`
- L499 _public property_ `public List<IssueKeyDto>? Keys { get; set; }` — attrs: `[System.Text.Json.Serialization.JsonPropertyName(HordeServer_Issues_FingerprintTelemetryGen.Keys)]`

#### class `HordeServer.Analytics.FingerprintTelemetryHandler.IssueKeyDto`  
`private class IssueKeyDto`  
_private; L502-507_
- L504 _public property_ `public string? Name { get; set; }`
- L505 _public property_ `public string? Type { get; set; }`
- L506 _public property_ `public string? Scope { get; set; }`

#### class `HordeServer.Analytics.FailureInfoTelemetryHandler`  
`public class FailureInfoTelemetryHandler : SqlMapper.TypeHandler<FailureInfoTelemetry>`  
_public; L513-590_
- inherits: `SqlMapper.TypeHandler<FailureInfoTelemetry>`
- desc: Type handler for FailureInfoTelemetry.
- L515 _private field_ `private static readonly JsonSerializerOptions s_jsonOptions = new JsonSerializerOptions { PropertyNameCaseInsensitive = true }`
- L518-521 _public method_ `public override void SetValue(IDbDataParameter parameter, FailureInfoTelemetry? value)` — (inheritdoc)
- L523-561 _internal method_ `internal static FailureInfoTelemetry ParseCore(object value)`
- L564 _public method_ `public override FailureInfoTelemetry Parse(object? value)` — (inheritdoc)

#### class `HordeServer.Analytics.FailureInfoTelemetryHandler.FailureInfoDto`  
`private class FailureInfoDto`  
_private; L567-580_
- L570 _public property_ `public string? JobId { get; set; }` — attrs: `[System.Text.Json.Serialization.JsonPropertyName(HordeServer_Issues_FailureInfoTelemetryGen.JobId)]`
- L573 _public property_ `public string? JobName { get; set; }` — attrs: `[System.Text.Json.Serialization.JsonPropertyName(HordeServer_Issues_FailureInfoTelemetryGen.JobName)]`
- L576 _public property_ `public CommitIdWithOrderDto? Change { get; set; }` — attrs: `[System.Text.Json.Serialization.JsonPropertyName(HordeServer_Issues_FailureInfoTelemetryGen.Change)]`
- L579 _public property_ `public string? StepId { get; set; }` — attrs: `[System.Text.Json.Serialization.JsonPropertyName(HordeServer_Issues_FailureInfoTelemetryGen.StepId)]`

#### class `HordeServer.Analytics.FailureInfoTelemetryHandler.CommitIdWithOrderDto`  
`private class CommitIdWithOrderDto`  
_private; L582-589_
- L585 _public property_ `public string? Name { get; set; }` — attrs: `[System.Text.Json.Serialization.JsonPropertyName("name")]`
- L588 _public property_ `public int Order { get; set; }` — attrs: `[System.Text.Json.Serialization.JsonPropertyName("order")]`

#### class `HordeServer.Analytics.NullableFailureInfoTelemetryHandler`  
`public class NullableFailureInfoTelemetryHandler : SqlMapper.TypeHandler<FailureInfoTelemetry?>`  
_public; L595-604_
- inherits: `SqlMapper.TypeHandler<FailureInfoTelemetry?>`
- desc: Type handler for nullable FailureInfoTelemetry.
- L598 _public method_ `public override void SetValue(IDbDataParameter parameter, FailureInfoTelemetry? value)` — (inheritdoc)
- L602 _public method_ `public override FailureInfoTelemetry? Parse(object? value)` — (inheritdoc)
