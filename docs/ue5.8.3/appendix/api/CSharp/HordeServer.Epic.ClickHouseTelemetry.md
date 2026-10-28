# CSharp / HordeServer.Epic.ClickHouseTelemetry

- project root: `Source/Programs/Horde/Plugins/ClickHouseTelemetry/HordeServer.Epic.ClickHouseTelemetry`
- files: 14; symbols: 160
- symbol kinds: class=17, const=11, ctor=6, field=33, method=67, property=25, record=1
- access marked `*` is implicit (not written in source)

### `Source/Programs/Horde/Plugins/ClickHouseTelemetry/HordeServer.Epic.ClickHouseTelemetry/BearerTokenInjectingHandler.cs` (HordeServer.Epic.ClickHouseTelemetry)


#### class `HordeServer.ClickHouseTelemetry.BearerTokenInjectingHandler`  
`internal sealed class BearerTokenInjectingHandler : HttpClientHandler`  
_internal; L16-38_
- inherits: `HttpClientHandler`
- desc: HTTP message handler that asks the registered IAuthenticationProvider{TConfig} for a token on each outbound request and, when one is available, attaches it as Authorization: Bearer <token> . When the provider returns null (the inert path — empty OAuthTokenEndpoint ), no header is added and the request flies through unchanged so ClickHouse can consume whatever auth is already in the connection string (UID/PWD, or none). Plugged into ClickHouseConnection 's HttpClientHandler overload so it transparently covers every HTTP call the native client makes — queries, bulk-copy inserts, schema migrations, table existence checks. Token caching/refresh happens inside the provider; this handler just reads the current token per request.
- L18 _private* field_ `readonly IAuthenticationProvider<ClickHouseTelemetryConfig> _authProvider`
- L20-26 _public ctor_ `public BearerTokenInjectingHandler(IAuthenticationProvider<ClickHouseTelemetryConfig> authProvider)`
- L29-37 _protected method_ `protected override async Task<HttpResponseMessage> SendAsync(HttpRequestMessage request, CancellationToken cancellationToken)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/ClickHouseTelemetry/HordeServer.Epic.ClickHouseTelemetry/ClickHouseHttpClientFactory.cs` (HordeServer.Epic.ClickHouseTelemetry)


#### class `HordeServer.ClickHouseTelemetry.ClickHouseHttpClientFactory`  
`internal static class ClickHouseHttpClientFactory`  
_internal; L12-29_
- desc: Builds the HttpClient used by every ClickHouse code path (sink, schema migrator, query-side data source). Centralises construction so the OAuth-bearer-token injection, certificate-revocation check, and decompression behavior live in exactly one place. The returned HttpClient owns its handler ( disposeHandler=true default), so the caller need only dispose the client when the owning component shuts down. ClickHouseConnection wraps a long-lived connection around one of these clients.
- L18-28 _public method_ `public static HttpClient Create(IAuthenticationProvider<ClickHouseTelemetryConfig> authProvider)` — Builds a fresh HttpClient with a BearerTokenInjectingHandler attached. Each call returns a new instance — callers own its lifetime.

### `Source/Programs/Horde/Plugins/ClickHouseTelemetry/HordeServer.Epic.ClickHouseTelemetry/ClickHouseSchemaMigrator.cs` (HordeServer.Epic.ClickHouseTelemetry)


#### class `HordeServer.ClickHouseTelemetry.ClickHouseSchemaMigrator`  
`public class ClickHouseSchemaMigrator : ISchemaMigrator`  
_public; L28-307_
- inherits: `ISchemaMigrator`
- desc: Computes and applies ClickHouse-side schema migrations when a new schema version is approved or created. Runs before the new version is committed to MongoDB so a DDL failure leaves the system consistent — the metadata never gets ahead of the actual table shape. Behaviour per change kind (matches the agreed-on policy): - Add column → ALTER TABLE … ADD COLUMN IF NOT EXISTS (additive) - Drop column → ALTER TABLE … DROP COLUMN IF EXISTS (destroys history; warned) - Rename or type change → DROP old + ADD new (destroys history; warned) - Table/database rename → no DDL; warned that old data is left behind and the sink will lazy-create the new table on first event First-version schemas (no previous Mongo row) need no migration; the sink's existing CREATE TABLE IF NOT EXISTS handles them.
- L30 _private* field_ `readonly IOptionsMonitor<ClickHouseTelemetryConfig> _globalConfig`
- L31 _private* field_ `readonly ITelemetrySchemaCollection _schemaCollection`
- L32 _private* field_ `readonly IAuthenticationProvider<ClickHouseTelemetryConfig> _authProvider`
- L33 _private* field_ `readonly ISqlDialect _dialect = new ClickHouseSqlDialect()`
- L34 _private* field_ `readonly ILogger<ClickHouseSchemaMigrator> _logger`
- L39-45 _public ctor_ `public ClickHouseSchemaMigrator(IOptionsMonitor<ClickHouseTelemetryConfig> globalConfig, ITelemetrySchemaCollection schemaCollection, IAuthenticationProvider<ClickHouseTelemetryConfig> authProvider, ILogger<ClickHouseSchemaMigrator> logger)` — Constructor
- L48-160 _public method_ `public async Task<MigrationPlan?> PlanAsync( string eventName, IReadOnlyList<SchemaColumn> proposedColumns, string proposedTableName, string? proposedSchemaName, CancellationToken cancellationToken = default)` — (inheritdoc)
- L163-221 _public method_ `public async Task ApplyAsync(MigrationPlan plan, CancellationToken cancellationToken = default)` — (inheritdoc)
- L229-237 _private* method_ `static async Task<bool> TableExistsAsync(ClickHouseConnection connection, string quotedTableName, CancellationToken cancellationToken)` — Checks whether a fully-qualified ClickHouse table identifier exists. Uses EXISTS TABLE which returns a UInt8 (0 or 1) rather than the system.tables join — keeps the dependency on system catalogue layout out of this code path.
- L250-278 _private* method_ `static string BuildDdl(MigrationStep step, string quotedTableName)` — Translates a single migration step into ClickHouse ALTER TABLE syntax. The portable SchemaColumn on the step is resolved here via this plugin's own ClickHouseTypeMapper — the migration plan stays backend-agnostic and the DDL translation stays local to this file. ClickHouse does not support a table-level "ALTER TABLE IF EXISTS" guard, so callers must pre-check table existence (see TableExistsAsync). The per-column IF EXISTS / IF NOT EXISTS clauses ARE supported and we use them so individual operations are idempotent on partial failure.
- L284-288 _private* method_ `static SchemaColumn RequireColumn(MigrationStep step)` — Guards against a step that should carry a column definition but doesn't. Any miss here is a planner bug, not user input — fail loudly.
- L291-299 _private* method_ `static string TypeLabel(SchemaColumn column)` — Compact human-readable type label for warnings (no ClickHouse DDL syntax).
- L302-306 _private* method_ `string QualifiedName(string? schemaName, string tableName)` — Pretty database.table for warning text. Falls back to default DB when schema is null.

### `Source/Programs/Horde/Plugins/ClickHouseTelemetry/HordeServer.Epic.ClickHouseTelemetry/ClickHouseTelemetryConfig.cs` (HordeServer.Epic.ClickHouseTelemetry)


#### class `HordeServer.ClickHouseTelemetryConfig`  
`public class ClickHouseTelemetryConfig : IPluginConfig, IOAuthClientCredentialsConfig`  
_public; L17-102_
- inherits: `IPluginConfig, IOAuthClientCredentialsConfig`
- desc: Configuration for the ClickHouseTelemetry plugin. Implements IOAuthClientCredentialsConfig so the sink can optionally participate in the shared OAuth2 token-exchange machinery for backends that front ClickHouse with bearer-token auth (e.g. ClickHouse Cloud behind an API gateway, or a future managed offering with OIDC). Empty OAuthTokenEndpoint = inert; the connection string is used verbatim with whatever auth (UID/PWD or none) it carries.
- L23 _public property_ `public string ConnectionString { get; set; }` — Connection string for the ClickHouse database. Example: "Host=localhost;Port=8123;Database=horde_telemetry"
- L29 _public property_ `public List<string> AllowList { get; set; }` — Allow list of event names to process. If empty, all events are processed. Events not in this list will be ignored.
- L35 _public property_ `public bool AutoCreateTables { get; set; }` — Whether to automatically create tables for telemetry record types. When enabled, tables are created based on AbstractTelemetryRecord attributes.
- L40 _public property_ `public string DefaultDatabaseName { get; set; }` — Database name to use for telemetry tables.
- L45 _public property_ `public int BatchSize { get; set; }` — Batch size for bulk inserts.
- L50 _public property_ `public int FlushIntervalSeconds { get; set; }` — Flush interval in seconds. Events are batched and flushed at this interval.
- L58 _public property_ `public bool EnableUnstructuredPath { get; set; }` — Whether to enable the unstructured telemetry path. When true, events with [TelemetryEventAttribute] but without [AnalyticsTableGen] are stored in a raw staging table for future schematization. When false, such events are dropped.
- L69 _public property_ `public bool NormalizePropertiesOnIngest { get; set; }` — When true, property names from incoming events and schema PropertyNames are both normalised (lowercased, '.', '_' and '-' stripped) before being matched against each other. This lets a column named JobId pick up an incoming property called job_id , job-id , job.id , or any casing variant — useful when ingest sources don't agree on naming conventions and rewriting the producer isn't an option. Off by default: matching stays case-insensitive but otherwise exact, preserving the original behaviour.
- L77 _public property_ `public string OAuthTokenEndpoint { get; set; }` — HTTPS endpoint for the OAuth2 client-credentials token exchange. When empty (default), no bearer token is fetched and the ClickHouse connection string passes through verbatim — same wire behaviour as before this field existed.
- L83 _public property_ `public string OAuthScope { get; set; }` — OAuth2 scope sent in the token request. Defaults to all-apis matching the StructuredAnalytics convention. Set to empty to omit.
- L91 _public property_ `public string OAuthAccessTokenFragmentKey { get; set; }` — Connection-string key the access token would be folded into for ODBC backends. Unused for the ClickHouse native HTTP path (which uses Authorization: Bearer headers instead) but kept on the config for interface symmetry with the rest of the analytics OAuth surface.
- L96 _public property_ `public string OAuthCredentialsSecretId { get; set; }` — Secret-store ID for the OAuth client_id / client_secret pair.
- L99-101 _public method_ `public void PostLoad(PluginConfigOptions configOptions)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/ClickHouseTelemetry/HordeServer.Epic.ClickHouseTelemetry/ClickHouseTelemetryPlugin.cs` (HordeServer.Epic.ClickHouseTelemetry)


#### class `HordeServer.ClickHouseTelemetryPlugin`  
`public class ClickHouseTelemetryPlugin : IPluginStartup`  
_public; L19-55_
- attrs: `[Plugin("ClickHouseTelemetry", EnabledByDefault = false, GlobalConfigType = typeof(ClickHouseTelemetryConfig), ServerConfigType = typeof(ClickHouseTelemetryServerConfig))]`
- inherits: `IPluginStartup`
- desc: Entry point for the ClickHouseTelemetry plugin
- L24-26 _public ctor_ `public ClickHouseTelemetryPlugin()` — Constructor
- L29-31 _public method_ `public void Configure(IApplicationBuilder app)` — (inheritdoc)
- L34-49 _public method_ `public void ConfigureServices(IServiceCollection serviceCollection)` — (inheritdoc)
- L54 _public const_ `public const string BackendKey = "ClickHouse"` — Key under which this plugin's IAnalyticsDataSource is registered. Consumer plugins reference this in their BackendName config field.

#### class `HordeServer.ClickHouseTelemetryExtensions`  
`public static class ClickHouseTelemetryExtensions`  
_public; L60-73_
- desc: Helper methods for ClickHouseTelemetry plugin config
- L65 _public method_ `public static void AddClickHouseTelemetryConfig(this IDictionary<PluginName, IPluginConfig> dictionary, ClickHouseTelemetryConfig config)` — Configures the ClickHouseTelemetry plugin
- L71 _public method_ `public static ClickHouseTelemetryConfig GetClickHouseTelemetryConfig(this IDictionary<PluginName, IPluginConfig> dictionary)` — Gets configuration for the ClickHouseTelemetry plugin

### `Source/Programs/Horde/Plugins/ClickHouseTelemetry/HordeServer.Epic.ClickHouseTelemetry/ClickHouseTelemetryServerConfig.cs` (HordeServer.Epic.ClickHouseTelemetry)


#### class `HordeServer.ClickHouseTelemetryServerConfig`  
`public class ClickHouseTelemetryServerConfig : PluginServerConfig`  
_public; L10-12_
- inherits: `PluginServerConfig`
- desc: Server configuration for the ClickHouseTelemetry plugin

### `Source/Programs/Horde/Plugins/ClickHouseTelemetry/HordeServer.Epic.ClickHouseTelemetry/ClickHouseTelemetrySink.cs` (HordeServer.Epic.ClickHouseTelemetry)


#### class `HordeServer.ClickHouseTelemetry.ClickHouseTelemetrySink`  
`public sealed class ClickHouseTelemetrySink : ITelemetrySink, IHostedService, IAsyncDisposable`  
_public; L31-745_
- inherits: `ITelemetrySink, IHostedService, IAsyncDisposable`
- desc: Telemetry sink that forwards events to ClickHouse. Events are routed based on their attributes: - Events with BOTH TelemetryEventAttribute AND AnalyticsTableGenAttribute go to structured tables. - Events with only TelemetryEventAttribute go to raw_telemetry_events (if EnableUnstructuredPath is true). - Events without TelemetryEventAttribute are dropped.
- L33 _private* field_ `readonly IOptionsMonitor<ClickHouseTelemetryConfig> _globalConfig`
- L34 _private* field_ `readonly IOptionsMonitor<ClickHouseTelemetryServerConfig> _serverConfig`
- L35 _private* field_ `readonly ITelemetrySchemaCache _schemaCache`
- L36 _private* field_ `readonly IAuthenticationProvider<ClickHouseTelemetryConfig> _authProvider`
- L37 _private* field_ `readonly ISqlDialect _dialect = new ClickHouseSqlDialect()`
- L38 _private* field_ `readonly ITicker _flushTicker`
- L39 _private* field_ `readonly ILogger _logger`
- L40 _private* field_ `readonly JsonSerializerOptions _jsonOptions`
- L42 _private* field_ `readonly ConcurrentDictionary<string, bool> _tableExistsCache = ...`
- L42 _private* field_ `readonly ConcurrentDictionary< _tableExistsCache = new()`
- L43 _private* field_ `readonly ConcurrentDictionary<string, bool> _databaseExistsCache = ...`
- L43 _private* field_ `readonly ConcurrentDictionary< _databaseExistsCache = new()`
- L44 _private* field_ `readonly ConcurrentQueue<QueuedEvent> _eventQueue = new()`
- L45 _private* field_ `readonly IDisposable? _configChangeSubscription`
- L47 _private* field_ `HashSet<string> _eventAllowList`
- L49 _private* field_ `ClickHouseConnection? _connection`
- L50 _private* field_ `HttpClient? _connectionHttpClient`
- L51 _private* field_ `bool _disposed`
- L54 _public property_ `public bool Enabled => ...` — (inheritdoc)
- L65-84 _public ctor_ `public ClickHouseTelemetrySink(IOptionsMonitor<ClickHouseTelemetryConfig> config, IOptionsMonitor<ClickHouseTelemetryServerConfig> serverConfig, ITelemetrySchemaCache schemaCache, IAuthenticationProvider<ClickHouseTelemetryConfig> authProvider, IClock clock, ILogger<ClickHouseTelemetrySink> logger)` — Constructor
- L87-119 _public method_ `public async Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L122-131 _public method_ `public async Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L134-155 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L158-161 _public method_ `public async ValueTask FlushAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L163-201 _private* method_ `async ValueTask FlushInternalAsync(CancellationToken cancellationToken)`
- L204-253 _public method_ `public void SendEvent(TelemetryStoreId telemetryStoreId, TelemetryEvent telemetryEvent)` — (inheritdoc)
- L258-296 _private* method_ `void SendJsonEvent(TelemetryStoreId telemetryStoreId, TelemetryEvent telemetryEvent, JsonElement jsonElement)` — Handles JSON payloads from REST API
- L302-350 _private* method_ `void SendJsonEventFromSchema(TelemetryStoreId telemetryStoreId, TelemetryEvent telemetryEvent, JsonElement jsonElement, ITelemetrySchema schema)` — Sends a JSON event using schema from ITelemetrySchemaCollection. For JSON payloads from REST API when a MongoDB schema exists.
- L359-410 _private* method_ `void SendEventFromSchema(TelemetryStoreId telemetryStoreId, TelemetryEvent telemetryEvent, ITelemetrySchema schema)` — Sends an event using schema from ITelemetrySchemaCollection. For object payloads from TelemetryManager. Uses JSON serialization to convert the payload, which ensures consistency with other telemetry sinks and respects custom JsonConverter attributes.
- L415-430 _private* method_ `void SendUnstructuredEvent(TelemetryStoreId telemetryStoreId, TelemetryEvent telemetryEvent, string eventName, object payload)` — Sends an unstructured event to the raw staging table
- L435-450 _private* method_ `void SendUnstructuredJsonEvent(TelemetryStoreId telemetryStoreId, TelemetryEvent telemetryEvent, string eventName, JsonElement jsonElement)` — Sends an unstructured JSON event to the raw staging table
- L455-468 _private* method_ `static void AddMetadataColumns(Dictionary<string, object?> values, TelemetryStoreId telemetryStoreId, TelemetryEvent telemetryEvent)` — Adds standard metadata columns to the values dictionary
- L473-488 _private* method_ `static string? GetEventName(object payload)` — Gets the event name from a payload via TelemetryEventAttribute or EventName property
- L504-522 _private* method_ `object? ConvertJsonValueBySchemaType(JsonElement element, SchemaColumn col, bool normalize)` — Converts a JsonElement value based on SchemaColumn. Used when extracting values from JSON-serialized payloads. For nested objects, uses the nested schema to serialize with correct column names.
- L529-546 _private* method_ `async Task EnsureDatabaseExistsInternalAsync(string databaseName, CancellationToken cancellationToken)` — Ensures a specific database exists (with caching)
- L551-570 _private* method_ `async Task EnsureUnstructuredTableExistsAsync(CancellationToken cancellationToken)` — Ensures the unstructured telemetry table exists
- L575-598 _private* method_ `void EnsureTableExistsFromSchema(ITelemetrySchema schema)` — Ensures table exists based on ITelemetrySchema (fire-and-forget)
- L600-627 _private* method_ `async Task EnsureTableExistsFromSchemaAsync(ITelemetrySchema schema, CancellationToken cancellationToken)`
- L632-703 _private* method_ `async Task InsertBatchAsync(string tableName, string? schemaName, List<QueuedEvent> events, CancellationToken cancellationToken)` — Inserts a batch of events into a table
- L708-729 _private* method_ `async Task<List<string>> GetTableColumnsAsync(string quotedTableName, CancellationToken cancellationToken)` — Gets column names for a table
- L734-737 _private* method_ `static string SanitizeConnectionString(string connectionString)` — Sanitizes a connection string for logging (removes password)
- L739-742 _private method_ `private static HashSet<string> BuildAllowList(List<string> allowList)`

#### record `HordeServer.ClickHouseTelemetry.ClickHouseTelemetrySink.QueuedEvent`  
`record QueuedEvent(string TableName, string? SchemaName, Dictionary<string, object?> Values)`  
_private*; L744-744_

### `Source/Programs/Horde/Plugins/ClickHouseTelemetry/HordeServer.Epic.ClickHouseTelemetry/ClickHouseTelemetrySinkHelpers.cs` (HordeServer.Epic.ClickHouseTelemetry)


#### class `HordeServer.ClickHouseTelemetry.ClickHouseTelemetrySinkHelpers`  
`internal static class ClickHouseTelemetrySinkHelpers`  
_internal; L10-275_
- L19-31 _internal method_ `internal static string NormalizePropertyName(string name)` — Normalises a property name for ingest matching when NormalizePropertiesOnIngest is enabled on the sink config. Lowercases and strips '.', '_' and '-' so producer naming conventions (camelCase / snake_case / kebab-case / dot.case) all collapse to the same key. Lives here rather than on the sink so the nested-object helper can use the same routine when it does its own property matching.
- L40-70 _internal method_ `internal static object? ConvertJsonArray(JsonElement element, SchemaDataType? elementType, ILogger logger)`
- L77-89 _internal method_ `internal static DateTime? ConvertJsonToDateTime(JsonElement element)`
- L96-114 _internal method_ `internal static double? ConvertJsonToDouble(JsonElement element)`
- L121-124 _internal method_ `internal static bool? ConvertToBool(JsonElement element)`
- L132-173 _internal method_ `internal static long? ConvertJsonToInt64(JsonElement element, ILogger logger)`
- L180-190 _internal method_ `internal static string? ConvertJsonToString(JsonElement element)`
- L197-215 _internal method_ `internal static bool ElementMatchesSchemaType(JsonElement item, SchemaDataType elementType)` — Tests whether a single array element's JSON kind is compatible with the declared schema element type. Object/Array element types accept any object/array shape and rely on downstream validation; null is always permitted.
- L221-274 _internal method_ `internal static string ConvertNestedObject(JsonElement element, string? nestedSchemaEventName, ITelemetrySchemaCache schemaCache, ILogger logger, bool normalize = false)` — Converts a nested object JSON element using schema column names. Uses the warm schema cache for nested schema resolution (no blocking, no MongoDB).

### `Source/Programs/Horde/Plugins/ClickHouseTelemetry/HordeServer.Epic.ClickHouseTelemetry/ClickHouseTypeMapper.cs` (HordeServer.Epic.ClickHouseTelemetry)


#### class `HordeServer.ClickHouseTelemetry.ClickHouseTypeMapper`  
`public static class ClickHouseTypeMapper`  
_public; L11-112_
- desc: Maps fundamental schema types to ClickHouse types
- L19-39 _public method_ `public static string MapToClickHouseType(SchemaDataType dataType, bool isNullable)` — Maps a SchemaDataType to a ClickHouse type string
- L44-47 _public method_ `public static string MapColumnToClickHouseType(SchemaColumn column)` — Maps a SchemaColumn to its ClickHouse type string
- L54-67 _public method_ `public static void AppendMetadataColumnsDdl(System.Text.StringBuilder sb, IReadOnlySet<string>? alreadyDeclaredColumns = null)` — Appends the standard metadata column definitions to a StringBuilder. These columns are added to every telemetry table the sink manages. The AbstractTelemetryRecord.TelemetryTimestampColumnName column is conditionally emitted only when the supplied schema doesn't already declare it (which it does for every AbstractTelemetryRecord-derived type via codegen).
- L73-78 _public method_ `public static void AppendTableOptionsDdl(System.Text.StringBuilder sb)` — Appends the standard table options (ENGINE, ORDER BY, PARTITION BY) to a StringBuilder.
- L83-111 _public method_ `public static string GetCreateTableDdl(ITelemetrySchema schema, string quotedTableName)` — Gets the CREATE TABLE DDL for a schema

### `Source/Programs/Horde/Plugins/ClickHouseTelemetry/HordeServer.Epic.ClickHouseTelemetry/DataSources/ClickHouseAnalyticsDataSource.cs` (HordeServer.Epic.ClickHouseTelemetry)


#### class `HordeServer.DataSources.ClickHouseAnalyticsDataSource`  
`public sealed class ClickHouseAnalyticsDataSource : IAnalyticsDataSource, IAsyncDisposable, IDisposable`  
_public; L17-82_
- inherits: `IAnalyticsDataSource, IAsyncDisposable, IDisposable`
- desc: ClickHouse-native implementation of IAnalyticsDataSource. Mirrors ClickHouseTelemetrySink 's connection pattern: a single long-lived HttpClient wraps a BearerTokenInjectingHandler (so OAuth tokens are folded as Authorization: Bearer headers when the provider is configured), and each OpenAsync creates a fresh ClickHouseConnection against that shared HttpClient. Connection-string source: ClickHouseTelemetryConfig.ConnectionString — the same field the sink uses, so query and write paths point at the same cluster by construction.
- L19 _private field_ `private readonly IOptionsMonitor<ClickHouseTelemetryConfig> _config`
- L20 _private field_ `private readonly ISqlDialect _dialect = new ClickHouseSqlDialect()`
- L21 _private field_ `private readonly HttpClient _httpClient`
- L22 _private field_ `private bool _disposed`
- L25 _public property_ `public ISqlDialect Dialect => ...` — (inheritdoc)
- L30-34 _public ctor_ `public ClickHouseAnalyticsDataSource(IOptionsMonitor<ClickHouseTelemetryConfig> config, IAuthenticationProvider<ClickHouseTelemetryConfig> authProvider)` — Constructor.
- L37-47 _public method_ `public Task<DbConnection> OpenAsync(CancellationToken cancellationToken = default)` — (inheritdoc)
- L49-61 _private method_ `private static async Task<DbConnection> OpenInternalAsync(ClickHouseConnection connection, CancellationToken cancellationToken)`
- L64-74 _public method_ `public void Dispose()` — (inheritdoc)
- L77-81 _public method_ `public ValueTask DisposeAsync()` — (inheritdoc)

### `Source/Programs/Horde/Plugins/ClickHouseTelemetry/HordeServer.Epic.ClickHouseTelemetry/Dialects/ClickHouseSqlDialect.cs` (HordeServer.Epic.ClickHouseTelemetry)


#### class `HordeServer.Dialects.ClickHouseSqlDialect`  
`public sealed class ClickHouseSqlDialect : ISqlDialect`  
_public; L11-70_
- inherits: `ISqlDialect`
- desc: SQL dialect for ClickHouse's native ADO.NET driver. Emits parameter placeholders as {name:Type} per ClickHouse's HTTP/native protocol convention, and binds values via the command's own DbCommand.CreateParameter factory so the driver materialises ClickHouseParameter instances.
- L16 _public const_ `public const string DialectIdentifier = "ClickHouse"` — Standard name of the dialect.
- L19-23 _public method_ `public string FormatParameterPlaceholder(string canonicalName, DbType dbType)` — (inheritdoc)
- L26-33 _public method_ `public void AddParameter(DbCommand command, string canonicalName, object? value, DbType dbType)` — (inheritdoc)
- L36 _public method_ `public string QuoteIdentifier(string identifier)` — (inheritdoc)
- L39-48 _public method_ `public string FormatTableName(string? schemaName, string tableName)` — (inheritdoc)
- L53 _private method_ `private static string MapDbTypeToClickHouseTypeName(DbType dbType)` — Maps a DbType to the ClickHouse type name used in {name:Type} placeholders. Covers the types used by today's analytics queries (per the Phase 0 audit); additional types can be added when new queries demand them.

### `Source/Programs/Horde/Plugins/ClickHouseTelemetry/HordeServer.Epic.ClickHouseTelemetry/StructuredEventSchema.cs` (HordeServer.Epic.ClickHouseTelemetry)


#### class `HordeServer.ClickHouseTelemetry.StructuredEventSchema`  
`public sealed class StructuredEventSchema`  
_public; L12-44_
- desc: Cached schema metadata for a structured telemetry type. Built via reflection at startup from types with both [TelemetryEventAttribute] and [AnalyticsTableGen].
- L17 _public property_ `public required string EventName { get; init; }` — Event name from [TelemetryEventAttribute]
- L22 _public property_ `public required string TableName { get; init; }` — Table name from [Table] attribute
- L27 _public property_ `public string? SchemaName { get; init; }` — Schema/database name from [Table] attribute Schema property
- L32 _public property_ `public required Type RecordType { get; init; }` — The telemetry record type
- L37 _public property_ `public required IReadOnlyList<ColumnMapping> Columns { get; init; }` — Cached property info with column names
- L43 _public property_ `public required IReadOnlyDictionary<string, ColumnMapping> ColumnsByName { get; init; }` — Lookup from column name to column mapping (case-insensitive). Used for JSON property to column mapping.

#### class `HordeServer.ClickHouseTelemetry.ColumnMapping`  
`public sealed class ColumnMapping`  
_public; L49-70_
- desc: Maps a property to its ClickHouse column.
- L54 _public property_ `public required PropertyInfo Property { get; init; }` — The property to read from
- L59 _public property_ `public required string ColumnName { get; init; }` — Column name from [Column] attribute
- L64 _public property_ `public required string ClickHouseType { get; init; }` — ClickHouse type for this column
- L69 _public property_ `public required bool IsNullable { get; init; }` — Whether this column is nullable

### `Source/Programs/Horde/Plugins/ClickHouseTelemetry/HordeServer.Epic.ClickHouseTelemetry/StructuredTelemetryRegistry.cs` (HordeServer.Epic.ClickHouseTelemetry)


#### class `HordeServer.ClickHouseTelemetry.StructuredTelemetryRegistry`  
`public sealed class StructuredTelemetryRegistry`  
_public; L14-218_
- desc: Registry of structured telemetry schemas, built at startup via reflection. Only types with BOTH [TelemetryEventAttribute] AND [AnalyticsTableGen] are registered.
- L16 _private* field_ `readonly Dictionary<string, StructuredEventSchema> _byEventName`
- L16 _private* field_ `readonly Dictionary< _byEventName`
- L17 _private* field_ `readonly Dictionary<Type, StructuredEventSchema> _byType`
- L17 _private* field_ `readonly Dictionary< _byType`
- L18 _private* field_ `readonly ILogger _logger`
- L23-30 _public ctor_ `public StructuredTelemetryRegistry(ILogger<StructuredTelemetryRegistry> logger)` — Constructor. Scans assemblies immediately.
- L35 _public property_ `public IEnumerable<StructuredEventSchema> AllSchemas => ...` — All registered schemas
- L40 _public method_ `public bool TryGetByEventName(string eventName, out StructuredEventSchema? schema)` — Try to get schema by event name
- L46 _public method_ `public bool TryGetByType(Type type, out StructuredEventSchema? schema)` — Try to get schema by payload type
- L52 _public method_ `public bool IsStructuredEvent(string eventName)` — Check if an event name is registered as structured
- L58-128 _private* method_ `void ScanAndRegisterTypes()` — Scans loaded assemblies for types with both required attributes.
- L133-171 _private* method_ `static List<ColumnMapping> BuildColumnMappings(Type type)` — Builds column mappings by walking the type hierarchy and finding [Column] attributes.
- L176-205 _private* method_ `static string MapTypeToClickHouse(Type type)` — Maps a CLR type to a ClickHouse type string.
- L210-217 _private* method_ `static bool IsNullableType(Type type)` — Checks if a type is nullable (reference type or Nullable<T>).

### `Source/Programs/Horde/Plugins/ClickHouseTelemetry/HordeServer.Epic.ClickHouseTelemetry/UnstructuredTelemetry.cs` (HordeServer.Epic.ClickHouseTelemetry)


#### class `HordeServer.ClickHouseTelemetry.UnstructuredColumns`  
`public static class UnstructuredColumns`  
_public; L8-33_
- desc: Column names for the raw telemetry table
- L11 _public const_ `public const string EventName = "event_name"` — Event name from TelemetryEventAttribute
- L14 _public const_ `public const string InsertTime = "insert_time"` — Time the event was inserted
- L17 _public const_ `public const string TelemetryStoreId = "telemetry_store_id"` — Telemetry store ID
- L20 _public const_ `public const string AppId = "app_id"` — Application ID
- L23 _public const_ `public const string AppVersion = "app_version"` — Application version
- L26 _public const_ `public const string AppEnvironment = "app_environment"` — Application environment
- L29 _public const_ `public const string SessionId = "session_id"` — Session ID
- L32 _public const_ `public const string Payload = "payload"` — JSON serialized payload

#### class `HordeServer.ClickHouseTelemetry.UnstructuredTelemetry`  
`public static class UnstructuredTelemetry`  
_public; L39-67_
- desc: Constants and helpers for the unstructured telemetry staging table. Events with [TelemetryEventAttribute] but without [AnalyticsTableGen] are routed here.
- L44 _public const_ `public const string TableName = "raw_telemetry_events"` — Table name for raw/unstructured telemetry events
- L51-66 _public method_ `public static string GetCreateTableSql(string databaseName)` — Gets the CREATE TABLE SQL for the raw telemetry staging table.
