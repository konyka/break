# CSharp / HordeServer.OdbcTelemetry

- project root: `Source/Programs/Horde/Plugins/OdbcTelemetry/HordeServer.OdbcTelemetry`
- files: 6; symbols: 50
- symbol kinds: class=7, const=4, ctor=2, field=9, method=20, property=8
- access marked `*` is implicit (not written in source)

### `Source/Programs/Horde/Plugins/OdbcTelemetry/HordeServer.OdbcTelemetry/DataSources/OdbcTelemetryDataSource.cs` (HordeServer.OdbcTelemetry)


#### class `HordeServer.DataSources.OdbcTelemetryDataSource`  
`public sealed class OdbcTelemetryDataSource : IAnalyticsDataSource, IAsyncDisposable, IDisposable`  
_public; L17-169_
- inherits: `IAnalyticsDataSource, IAsyncDisposable, IDisposable`
- desc: ODBC-backed implementation of IAnalyticsDataSource. Reads the connection string from OdbcTelemetryConfig.ODBCConnectionString, folds in the OAuth bearer-token fragment (Databricks pass-through pattern) when an IAuthenticationProvider{TConfig} is registered, and caches the assembled connection string for OdbcTelemetryConfig.ODBCConnectionStringRefreshTimeMins minutes (default 5). Returns each connection as a DbConnection typed by the framework's OdbcConnection; consumers receive the abstract type and never need System.Data.Odbc themselves.
- L22 _public const_ `public const int DefaultRefreshTimeMins = 5` — Default connection-string refresh time (minutes) when OdbcTelemetryConfig.ODBCConnectionStringRefreshTimeMins is unset.
- L24 _private field_ `private readonly IOptionsMonitor<OdbcTelemetryConfig> _config`
- L25 _private field_ `private readonly IAuthenticationProvider<OdbcTelemetryConfig>? _authProvider`
- L26 _private field_ `private readonly ILogger<OdbcTelemetryDataSource> _logger`
- L27 _private field_ `private readonly ISqlDialect _dialect`
- L29 _private field_ `private readonly SemaphoreSlim _connectionStringSemaphore = new(1, 1)`
- L30 _private field_ `private string? _cachedConnectionString`
- L31 _private field_ `private DateTime _cacheExpiry = DateTime.MinValue`
- L32 _private field_ `private int _currentRefreshMins`
- L33 _private field_ `private bool _disposed`
- L36 _public property_ `public ISqlDialect Dialect => ...` — (inheritdoc)
- L45-56 _public ctor_ `public OdbcTelemetryDataSource( IOptionsMonitor<OdbcTelemetryConfig> config, ISqlDialect dialect, ILogger<OdbcTelemetryDataSource> logger, IAuthenticationProvider<OdbcTelemetryConfig>? authProvider = null)` — Constructor.
- L59-78 _public method_ `public async Task<DbConnection> OpenAsync(CancellationToken cancellationToken = default)` — (inheritdoc)
- L80-116 _private method_ `private async Task<string?> GetConnectionStringAsync(bool forceRefresh = false, CancellationToken cancellationToken = default)`
- L118-127 _private method_ `private bool CheckRefreshConfigChange()`
- L129-147 _private method_ `private async Task<string?> BuildConnectionStringAsync(string baseConnectionString)`
- L150-161 _public method_ `public void Dispose()` — (inheritdoc)
- L164-168 _public method_ `public ValueTask DisposeAsync()` — (inheritdoc)

### `Source/Programs/Horde/Plugins/OdbcTelemetry/HordeServer.OdbcTelemetry/Dialects/ClickHouseOdbcDialect.cs` (HordeServer.OdbcTelemetry)


#### class `HordeServer.Dialects.ClickHouseOdbcDialect`  
`public sealed class ClickHouseOdbcDialect : ISqlDialect`  
_public; L11-42_
- inherits: `ISqlDialect`
- desc: Hybrid SQL dialect for the "ClickHouse via the clickhouse-odbc driver" deployment shape: ODBC-style positional ? placeholders (because the driver binds positionally and ClickHouse never sees the placeholder text), but ClickHouse-style identifier handling.
- L16 _public const_ `public const string DialectIdentifier = "ClickHouseOdbc"` — Standard name of the dialect.
- L19 _public method_ `public string FormatParameterPlaceholder(string canonicalName, DbType dbType)` — (inheritdoc)
- L22-29 _public method_ `public void AddParameter(DbCommand command, string canonicalName, object? value, DbType dbType)` — (inheritdoc)
- L32 _public method_ `public string QuoteIdentifier(string identifier)` — (inheritdoc)
- L35-41 _public method_ `public string FormatTableName(string? schemaName, string tableName)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/OdbcTelemetry/HordeServer.OdbcTelemetry/Dialects/OdbcDialect.cs` (HordeServer.OdbcTelemetry)


#### class `HordeServer.Dialects.OdbcDialect`  
`public sealed class OdbcDialect : ISqlDialect`  
_public; L11-40_
- inherits: `ISqlDialect`
- desc: SQL dialect for ODBC-fronted backends. Positional ? placeholders, no identifier quoting (Simba/standard ODBC behavior).
- L17 _public const_ `public const string DialectIdentifier = "StandardOdbc"` — Standard name of the dialect.
- L20 _public method_ `public string FormatParameterPlaceholder(string canonicalName, DbType dbType)` — (inheritdoc)
- L23-30 _public method_ `public void AddParameter(DbCommand command, string canonicalName, object? value, DbType dbType)` — (inheritdoc)
- L33 _public method_ `public string QuoteIdentifier(string identifier)` — (inheritdoc)
- L36-39 _public method_ `public string FormatTableName(string? schemaName, string tableName)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/OdbcTelemetry/HordeServer.OdbcTelemetry/OdbcTelemetryConfig.cs` (HordeServer.OdbcTelemetry)


#### class `HordeServer.OdbcTelemetryConfig`  
`public class OdbcTelemetryConfig : IPluginConfig, IOAuthClientCredentialsConfig`  
_public; L13-51_
- inherits: `IPluginConfig, IOAuthClientCredentialsConfig`
- desc: Configuration for the OdbcTelemetry plugin. Provides an ODBC-backed IAnalyticsDataSource for any consumer plugin (StructuredAnalytics, PerformanceTrends, ...). Today's Databricks-via-Simba shape lives here; Snowflake-via-Simba and other ODBC-accessible backends fit the same plugin. Implements IOAuthClientCredentialsConfig so the plugin can fold an OAuth bearer token into the ODBC connection string at open time (Databricks pass-through auth pattern).
- L19 _public property_ `public string ODBCConnectionString { get; set; }` — Connection string for the ODBC connector.
- L24 _public property_ `public int? ODBCConnectionStringRefreshTimeMins { get; set; }` — Connection-string refresh time, in minutes. Controls how often the auth-fragment-folded connection string is rebuilt.
- L30 _public property_ `public string OAuthTokenEndpoint { get; set; }` — HTTPS endpoint for the OAuth2 client-credentials token exchange. When empty, no token is fetched and the connection string is used as-is.
- L35 _public property_ `public string OAuthScope { get; set; }` — OAuth2 scope sent in the token request. Defaults to all-apis (Databricks). Set to empty to omit the scope form field.
- L40 _public property_ `public string OAuthAccessTokenFragmentKey { get; set; }` — Connection-string key the access token is folded into. Defaults to Auth_AccessToken (Simba Spark ODBC driver convention).
- L45 _public property_ `public string OAuthCredentialsSecretId { get; set; }` — Secret-store ID for the OAuth client_id / client_secret pair.
- L48-50 _public method_ `public void PostLoad(PluginConfigOptions configOptions)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/OdbcTelemetry/HordeServer.OdbcTelemetry/OdbcTelemetryPlugin.cs` (HordeServer.OdbcTelemetry)


#### class `HordeServer.OdbcTelemetryPlugin`  
`public class OdbcTelemetryPlugin : IPluginStartup`  
_public; L18-65_
- attrs: `[Plugin("OdbcTelemetry", EnabledByDefault = false, GlobalConfigType = typeof(OdbcTelemetryConfig), ServerConfigType = typeof(OdbcTelemetryServerConfig))]`
- inherits: `IPluginStartup`
- desc: Entry point for the OdbcTelemetry plugin. Registers an ODBC-backed IAnalyticsDataSource + ISqlDialect + IAuthenticationProvider{TConfig} for any consumer plugin (StructuredAnalytics, PerformanceTrends, ...) that takes IAnalyticsDataSource in via DI.
- L23-25 _public ctor_ `public OdbcTelemetryPlugin()` — Constructor
- L28-30 _public method_ `public void Configure(IApplicationBuilder app)` — (inheritdoc)
- L35 _public const_ `public const string BackendKey = "Odbc"` — Key under which this plugin's IAnalyticsDataSource is registered. Consumer plugins reference this in their BackendName config field.
- L38-50 _public method_ `public void ConfigureServices(IServiceCollection serviceCollection)` — (inheritdoc)
- L55-64 _internal method_ `internal static ISqlDialect CreateDialect(OdbcTelemetryServerConfig serverConfig)` — Maps the configured dialect string to its concrete ISqlDialect implementation. Throws on unrecognised values so a typo in OdbcTelemetryServerConfig.Dialect fails loudly at first request rather than silently falling back to a wrong default.

#### class `HordeServer.OdbcTelemetryExtensions`  
`public static class OdbcTelemetryExtensions`  
_public; L70-83_
- desc: Helper methods for OdbcTelemetry plugin config
- L75 _public method_ `public static void AddOdbcTelemetryConfig(this IDictionary<PluginName, IPluginConfig> dictionary, OdbcTelemetryConfig config)` — Configures the OdbcTelemetry plugin
- L81 _public method_ `public static OdbcTelemetryConfig GetOdbcTelemetryConfig(this IDictionary<PluginName, IPluginConfig> dictionary)` — Gets configuration for the OdbcTelemetry plugin

### `Source/Programs/Horde/Plugins/OdbcTelemetry/HordeServer.OdbcTelemetry/OdbcTelemetryServerConfig.cs` (HordeServer.OdbcTelemetry)


#### class `HordeServer.OdbcTelemetryServerConfig`  
`public class OdbcTelemetryServerConfig : PluginServerConfig`  
_public; L10-17_
- inherits: `PluginServerConfig`
- desc: Server configuration for the OdbcTelemetry plugin. Read at boot time during the plugin's ConfigureServices phase, so any value here drives DI shape rather than per-request behavior.
- L16 _public property_ `public string Dialect { get; set; }` — Selects which ISqlDialect implementation to register for the OdbcTelemetry data source. Operators register a custom ISqlDialect in their composition root if neither built-in fits.
