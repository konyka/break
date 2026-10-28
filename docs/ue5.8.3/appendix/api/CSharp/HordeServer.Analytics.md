# CSharp / HordeServer.Analytics

- project root: `Source/Programs/Horde/Plugins/Analytics/HordeServer.Analytics`
- files: 16; symbols: 228
- symbol kinds: class=22, const=2, ctor=10, enum=1, enumerator=6, field=52, interface=5, method=65, property=63, record=1, record struct=1
- access marked `*` is implicit (not written in source)

### `Source/Programs/Horde/Plugins/Analytics/HordeServer.Analytics/AnalyticsConfig.cs` (HordeServer.Analytics)


#### class `HordeServer.AnalyticsConfig`  
`public class AnalyticsConfig : IPluginConfig`  
_public; L18-53_
- inherits: `IPluginConfig`
- desc: Config settings for analytics
- L23 _public property_ `public List<TelemetryStoreConfig> Stores { get; set; }` — Metrics to aggregate on the Horde server
- L25 _private field_ `private AclConfig _parentAcl = null!`
- L26 _private field_ `private readonly Dictionary<TelemetryStoreId, TelemetryStoreConfig> _telemetryStoreLookup = ...`
- L26 _private field_ `private readonly Dictionary< _telemetryStoreLookup = new Dictionary<TelemetryStoreId, TelemetryStoreConfig>()`
- L29-39 _public method_ `public void PostLoad(PluginConfigOptions configOptions)` — (inheritdoc)
- L42 _public method_ `public bool Authorize(AclAction action, ClaimsPrincipal user)` — (inheritdoc)
- L51 _public method_ `public bool TryGetTelemetryStore(TelemetryStoreId telemetryStoreId, [NotNullWhen(true)] out TelemetryStoreConfig? config)` — Attempts to get configuration for a pool from this object

### `Source/Programs/Horde/Plugins/Analytics/HordeServer.Analytics/AnalyticsPlugin.cs` (HordeServer.Analytics)


#### class `HordeServer.AnalyticsPlugin`  
`public class AnalyticsPlugin : IPluginStartup`  
_public; L16-38_
- attrs: `[Plugin("Analytics", GlobalConfigType = typeof(AnalyticsConfig), ServerConfigType = typeof(AnalyticsServerConfig))]`
- inherits: `IPluginStartup`
- desc: Main entry point for the analytics plugin
- L19-20 _public method_ `public void Configure(IApplicationBuilder app)` — (inheritdoc)
- L23-37 _public method_ `public void ConfigureServices(IServiceCollection services)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Analytics/HordeServer.Analytics/AnalyticsServerConfig.cs` (HordeServer.Analytics)


#### class `HordeServer.AnalyticsServerConfig`  
`public class AnalyticsServerConfig : PluginServerConfig`  
_public; L13-19_
- inherits: `PluginServerConfig`
- desc: Server configuration for the analytics system
- L18 _public property_ `public TelemetrySinkConfig Sinks { get; }` — Settings for the various telemetry sinks

#### class `HordeServer.TelemetrySinkConfig`  
`public class TelemetrySinkConfig`  
_public; L24-35_
- desc: Telemetry sinks
- L29 _public property_ `public EpicTelemetryConfig? Epic { get; set; }` — Settings for the Epic telemetry sink
- L34 _public property_ `public MongoTelemetryConfig? Mongo { get; set; }` — Settings for the MongoDB telemetry sink

#### class `HordeServer.BaseTelemetryConfig`  
`public class BaseTelemetryConfig`  
_public; L40-46_
- desc: Configuration for the telemetry sink
- L45 _public property_ `public bool Enabled { get; set; }` — Whether to enable this sink

#### class `HordeServer.EpicTelemetryConfig`  
`public class EpicTelemetryConfig : BaseTelemetryConfig, IEpicTelemetrySinkConfig`  
_public; L51-68_
- inherits: `BaseTelemetryConfig, IEpicTelemetrySinkConfig`
- desc: Configuration for the telemetry sink
- L56 _public property_ `public Uri? Url { get; set; }` — Base URL for the telemetry server
- L61 _public property_ `public string AppId { get; set; }` — Application name to send in the event messages
- L64-67 _public method_ `public override string ToString()` — (inheritdoc)

#### class `HordeServer.MongoTelemetryConfig`  
`public class MongoTelemetryConfig : BaseTelemetryConfig`  
_public; L73-79_
- inherits: `BaseTelemetryConfig`
- desc: Configuration for the telemetry sink
- L78 _public property_ `public double RetainDays { get; set; }` — Number of days worth of telmetry events to keep

### `Source/Programs/Horde/Plugins/Analytics/HordeServer.Analytics/Properties/AssemblyInfo.cs` (HordeServer.Analytics)
_(no declarations)_


### `Source/Programs/Horde/Plugins/Analytics/HordeServer.Analytics/Telemetry/ITelemetrySink.cs` (HordeServer.Analytics)


#### interface `HordeServer.Telemetry.ITelemetrySink`  
`public interface ITelemetrySink : IAsyncDisposable`  
_public; L10-30_
- inherits: `IAsyncDisposable`
- desc: Interface for a telemetry sink
- L15 _public* property_ `bool Enabled { get; }` — Whether the sink is enabled
- L22 _public* method_ `ValueTask FlushAsync(CancellationToken cancellationToken)` — Flush any queued metrics to underlying service
- L29 _public* method_ `void SendEvent(TelemetryStoreId storeId, TelemetryEvent telemetryEvent)` — Sends a telemetry event with the given information

### `Source/Programs/Horde/Plugins/Analytics/HordeServer.Analytics/Telemetry/Metrics/IMetric.cs` (HordeServer.Analytics)


#### interface `HordeServer.Telemetry.Metrics.IMetric`  
`public interface IMetric`  
_public; L10-36_
- desc: Interface for a metric event
- L15 _public* property_ `MetricId MetricId { get; }` — Unique identifier for this event
- L20 _public* property_ `DateTime Time { get; }` — Start time for this aggregation interval
- L25 _public* property_ `string? Group { get; }` — Grouping key for this metric
- L30 _public* property_ `double Value { get; }` — Aggregated value for the metric
- L35 _public* property_ `int Count { get; }` — Number of samples

#### interface `HordeServer.Telemetry.Metrics.IMetricMeta`  
`public interface IMetricMeta`  
_public; L41-67_
- desc: Interface for metric meta data
- L46 _public* property_ `MetricId MetricId { get; }` — Unique identifier for this event
- L51 _public* property_ `string GroupBy { get; }` — GroupBy for the metric
- L56 _public* property_ `List<string> Groups { get; }` — Unique groups
- L61 _public property_ `public int TopN { get; }` — TopN aggregation
- L66 _public property_ `public int BottomN { get; }` — BottomN aggregation

### `Source/Programs/Horde/Plugins/Analytics/HordeServer.Analytics/Telemetry/Metrics/IMetricCollection.cs` (HordeServer.Analytics)


#### interface `HordeServer.Telemetry.Metrics.IMetricCollection`  
`public interface IMetricCollection`  
_public; L12-49_
- desc: Collection of aggregated metrics
- L19 _public* method_ `void AddEvent(TelemetryStoreId storeId, JsonNode node)` — Adds a new event to the collection
- L30 _public* method_ `Task<List<IMetricMeta>> FindMetaAsync(TelemetryStoreId storeId, MetricId[] metricIds, DateTime? minTime = null, DateTime? maxTime = null, int maxResults = 50, CancellationToken cancellationToken = default)` — Finds metrics over a given time period
- L42 _public* method_ `Task<List<IMetric>> FindAsync(TelemetryStoreId storeId, MetricId[] metricIds, DateTime? minTime = null, DateTime? maxTime = null, string[]? groups = null, int maxResults = 50, CancellationToken cancellationToken = default)` — Finds metrics over a given time period
- L48 _public* method_ `Task FlushAsync(CancellationToken cancellationToken)` — Flush all the pending events to storage

### `Source/Programs/Horde/Plugins/Analytics/HordeServer.Analytics/Telemetry/Metrics/MetricCollection.cs` (HordeServer.Analytics)


#### class `HordeServer.Telemetry.Metrics.MetricMeta`  
`class MetricMeta : IMetricMeta`  
_internal*; L22-48_
- inherits: `IMetricMeta`
- L27 _public property_ `public MetricId MetricId { get; set; }` — Unique identifier for this event
- L32 _public property_ `public string GroupBy { get; set; }` — Metric GroupBy
- L37 _public property_ `public List<string> Groups { get; set; }` — Unique groups
- L42 _public property_ `public int TopN { get; set; }` — TopN aggregation
- L47 _public property_ `public int BottomN { get; set; }` — BottomN aggregation

#### class `HordeServer.Telemetry.Metrics.MetricCollection`  
`class MetricCollection : IMetricCollection, IHostedService, IAsyncDisposable`  
_internal*; L50-607_
- inherits: `IMetricCollection, IHostedService, IAsyncDisposable`
- L86 _private* field_ `readonly Lock _lockObject = new Lock()`
- L87 _private* field_ `readonly IMongoCollection<MetricDocument> _metrics`
- L88 _private* field_ `readonly AsyncEvent _newDataEvent = new AsyncEvent()`
- L89 _private* field_ `readonly AsyncEvent _flushEvent = new AsyncEvent()`
- L90 _private* field_ `readonly BackgroundTask _processTask`
- L91 _private* field_ `readonly BackgroundTask _flushTask`
- L92 _private* field_ `readonly IClock _clock`
- L93 _private* field_ `readonly IOptionsMonitor<AnalyticsConfig> _analyticsConfig`
- L94 _private* field_ `readonly ILogger _logger`
- L96 _private* field_ `int _numDroppedItems`
- L97 _private* field_ `readonly Channel<(TelemetryStoreId, JsonNode)> _events`
- L98 _private* field_ `readonly Dictionary<QualifiedMetricId, TimeSpan> _slowMetrics = ...`
- L98 _private* field_ `readonly Dictionary< _slowMetrics = new Dictionary<QualifiedMetricId, TimeSpan>()`
- L99 _private* field_ `Dictionary<SampleKey, List<double>> _queuedSamples = ...`
- L99 _private* field_ `Dictionary< _queuedSamples = new Dictionary<SampleKey, List<double>>()`
- L101-114 _public ctor_ `public MetricCollection(IMongoService mongoService, IClock clock, IOptionsMonitor<AnalyticsConfig> analyticsConfig, ILogger<MetricCollection> logger)`
- L117-122 _public method_ `public Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L125-129 _public method_ `public async Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L132-136 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L139-145 _public method_ `public void AddEvent(TelemetryStoreId storeId, JsonNode node)` — (inheritdoc)
- L147-167 _private* method_ `async Task BackgroundProcessAsync(CancellationToken cancellationToken)`
- L169-200 _private* method_ `void ProcessEvent(TelemetryStoreId storeId, JsonNode node)`
- L202-301 _private* method_ `void ProcessEventInternal(TelemetryStoreId telemetryStoreId, MetricConfig metric, JsonNode node, JsonArray array)`
- L303-306 _private* method_ `static string EscapeCsv(IEnumerable<string> items)`
- L308 _private* field_ `static readonly char[] s_csvEscapeChars = { ',', '\n', '\"' }`
- L310-318 _private* method_ `static string? EscapeCsv(string text)`
- L320-329 _private* method_ `void QueueSampleValues(SampleKey key, List<double> values)`
- L332-343 _public method_ `public async Task FlushAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L345-399 _private* method_ `async Task BackgroundFlushAsync(CancellationToken cancellationToken)`
- L401-420 _private* method_ `async Task WriteQueuedSamplesAsync(CancellationToken cancellationToken)`
- L422-476 _private* method_ `async Task CombineValuesAsync(TelemetryStoreId telemetryStoreId, MetricConfig metricConfig, string group, DateTime time, List<double> values, CancellationToken cancellationToken)`
- L488-527 _public method_ `public async Task<List<IMetricMeta>> FindMetaAsync(TelemetryStoreId telemetryStoreId, MetricId[] metricIds, DateTime? minTime = null, DateTime? maxTime = null, int maxResults = 50, CancellationToken cancellationToken = default)` — (inheritdoc)
- L530-606 _public method_ `public async Task<List<IMetric>> FindAsync(TelemetryStoreId telemetryStoreId, MetricId[] metricIds, DateTime? minTime = null, DateTime? maxTime = null, string[]? groups = null, int maxResults = 50, CancellationToken cancellationToken = default)` — (inheritdoc)

#### class `HordeServer.Telemetry.Metrics.MetricCollection.MetricDocument`  
`class MetricDocument : IMetric`  
_private*; L52-76_
- inherits: `IMetric`
- L54 _public property_ `public ObjectId Id { get; set; }`
- L57 _public property_ `public TelemetryStoreId TelemetryStoreId { get; set; }` — attrs: `[BsonElement("ts")]`
- L60 _public property_ `public MetricId MetricId { get; set; }` — attrs: `[BsonElement("met")]`
- L63 _public property_ `public string Group { get; set; }` — attrs: `[BsonElement("grp")]`
- L66 _public property_ `public DateTime Time { get; set; }` — attrs: `[BsonElement("time")]`
- L69 _public property_ `public double Value { get; set; }` — attrs: `[BsonElement("value")]`
- L72 _public property_ `public int Count { get; set; }` — attrs: `[BsonElement("count")]`
- L75 _public property_ `public byte[]? State { get; set; }` — attrs: `[BsonElement("state")]`

#### record `HordeServer.Telemetry.Metrics.MetricCollection.SampleKey`  
`record class SampleKey(TelemetryStoreId Store, MetricId Metric, string Group, DateTime Time)`  
_private*; L78-78_

#### record struct `HordeServer.Telemetry.Metrics.MetricCollection.QualifiedMetricId`  
`record struct QualifiedMetricId(TelemetryStoreId StoreId, MetricId MetricId)`  
_private*; L80-84_
- L82 _public method_ `public override string ToString()`

### `Source/Programs/Horde/Plugins/Analytics/HordeServer.Analytics/Telemetry/Metrics/MetricConfig.cs` (HordeServer.Analytics)


#### enum `HordeServer.Telemetry.Metrics.AggregationFunction`  
`public enum AggregationFunction`  
_public; L21-52_
- desc: Method for aggregating samples into a metric
- L26 _public* enumerator_ `Count` — Count the number of matching elements
- L31 _public* enumerator_ `Min` — Take the minimum value of all samples
- L36 _public* enumerator_ `Max` — Take the maximum value of all samples
- L41 _public* enumerator_ `Sum` — Sum all the reported values
- L46 _public* enumerator_ `Average` — Average all the samples
- L51 _public* enumerator_ `Percentile` — Estimates the value at a certain percentile

#### class `HordeServer.Telemetry.Metrics.MetricConfig`  
`public class MetricConfig`  
_public; L57-132_
- desc: Configures a metric to aggregate on the server
- L62 _public property_ `public MetricId Id { get; set; }` — Identifier for this metric
- L68 _public property_ `public JsonPath? Filter { get; set; }` — attrs: `[JsonSchemaString]` — Filter expression to evaluate to determine which events to include. This query is evaluated against an array.
- L74 _public property_ `public JsonPath? Property { get; set; }` — attrs: `[JsonSchemaString]` — Property to aggregate
- L79-96 _public property_ `public string GroupBy { get; set; }` — Property to group by. Specified as a comma-separated list of JSON path expressions.
- L99 _private* field_ `string _groupBy = String.Empty` — attrs: `[JsonIgnore]`
- L105 _public property_ `public List<JsonPath> GroupByPaths { get; }` — attrs: `[JsonIgnore]` — Accessor for the GroupBy field, parsed as a list of json paths
- L110 _public property_ `public AggregationFunction Function { get; set; }` — How to aggregate samples for this metric
- L115 _public property_ `public int Percentile { get; set; }` — For the percentile function, specifies the percentile to measure
- L120 _public property_ `public int TopN { get; set; }` — TopN aggregation
- L125 _public property_ `public int BottomN { get; set; }` — BottomN aggregation
- L131 _public property_ `public TimeSpan Interval { get; set; }` — attrs: `[JsonConverter(typeof(IntervalJsonConverter))]` — Interval for each metric. Supports times such as "2d", "1h", "1h30m", "20s".

#### class `HordeServer.Telemetry.Metrics.TelemetryStoreConfig`  
`public class TelemetryStoreConfig`  
_public; L142-198_
- attrs: `[JsonSchema("https://unrealengine.com/horde/telemetry")] [JsonSchemaCatalog("Horde Telemetry", "Horde telemetry configuration file", new[] { "*.telemetry.json", "*.metrics.json", "Metrics/*.json" })] [ConfigDoc("*.telemetry.json", "[Horde](../../../README.md) > [Configuration](../../Config.md)", "Config/Schema/Telemetry.md")] [ConfigIncludeRoot] [ConfigMacroScope]`
- desc: Config for metrics
- L147 _public property_ `public TelemetryStoreId Id { get; set; }` — Identifier for this store
- L152 _public property_ `public AclConfig Acl { get; set; }` — Permissions for this store
- L157 _public property_ `public List<MetricConfig> Metrics { get; set; }` — Metrics to aggregate on the Horde server
- L162 _public property_ `public List<TelemetryViewConfig> Views { get; set; }` — Configuration for telemetry views
- L167 _public property_ `public List<ConfigInclude> Include { get; set; }` — Includes for other configuration files
- L169 _private* field_ `readonly Dictionary<MetricId, MetricConfig> _metricLookup = ...`
- L169 _private* field_ `readonly Dictionary< _metricLookup = new Dictionary<MetricId, MetricConfig>()`
- L174 _public property_ `public List<ConfigMacro> Macros { get; set; }` — Macros within this configuration
- L179-188 _public method_ `public void PostLoad(AclConfig parentAcl)` — Called after the store has been deserialized to compute cached values
- L196 _public method_ `public bool TryGetMetric(MetricId metricId, [NotNullWhen(true)] out MetricConfig? metricConfig)` — Attempt to get config for a metric with the given id

### `Source/Programs/Horde/Plugins/Analytics/HordeServer.Analytics/Telemetry/Sinks/EpicTelemetrySink.cs` (HordeServer.Analytics)


#### interface `HordeServer.Telemetry.Sinks.IEpicTelemetrySinkConfig`  
`public interface IEpicTelemetrySinkConfig`  
_public; L21-32_
- desc: Options for the Epic telemetry sink
- L26 _public property_ `public Uri? Url { get; }` — Base URL for sending events
- L31 _public property_ `public string AppId { get; }` — The application id

#### class `HordeServer.Telemetry.Sinks.EpicTelemetrySink`  
`public sealed class EpicTelemetrySink : ITelemetrySink`  
_public; L37-280_
- inherits: `ITelemetrySink`
- desc: Epic internal telemetry sink using the data router
- L58 _public const_ `public const string HttpClientName = "EpicTelemetrySink"` — Name of the HTTP client for writing telemetry data
- L60 _private* field_ `static readonly Utf8String s_packetPrefix = new Utf8String("{\"Events\":[")`
- L61 _private* field_ `static readonly Utf8String s_packetSuffix = new Utf8String("]}")`
- L63 _private* field_ `readonly Lock _lockObject = new Lock()`
- L65 _private* field_ `readonly HttpClient _httpClient`
- L66 _private* field_ `readonly Uri? _baseUrl`
- L67 _private* field_ `readonly JsonSerializerOptions _jsonOptions`
- L125 _private* field_ `readonly IServerInfo _serverInfo`
- L126 _private* field_ `readonly Dictionary<TelemetryRecordMeta, Writer> _writers = ...`
- L126 _private* field_ `readonly Dictionary< _writers = new Dictionary<TelemetryRecordMeta, Writer>()`
- L127 _private* field_ `readonly ILogger _logger`
- L130 _public property_ `public bool Enabled => ...` — (inheritdoc)
- L135-147 _public ctor_ `public EpicTelemetrySink(IEpicTelemetrySinkConfig config, IServerInfo serverInfo, ILogger<EpicTelemetrySink> logger)` — Constructor
- L149-160 _private* method_ `static HttpClient CreateHttpClient()`
- L163-171 _public method_ `public ValueTask DisposeAsync()` — (inheritdoc)
- L174-235 _public method_ `public async ValueTask FlushAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L238-279 _public method_ `public void SendEvent(TelemetryStoreId telemetryStoreId, TelemetryEvent telemetryEvent)` — (inheritdoc)

#### class `HordeServer.Telemetry.Sinks.EpicTelemetrySink.TableauDateTimeConverter`  
`class TableauDateTimeConverter : JsonConverter<DateTime>`  
_private*; L40-53_
- inherits: `JsonConverter<DateTime>`
- L42 _private* const_ `const string Format = "yyyy-MM-dd HH:mm:ss"`
- L44-47 _public method_ `public override void Write(Utf8JsonWriter writer, DateTime date, JsonSerializerOptions options)`
- L49-52 _public method_ `public override DateTime Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)`

#### class `HordeServer.Telemetry.Sinks.EpicTelemetrySink.Writer`  
`class Writer : IDisposable`  
_private*; L69-123_
- inherits: `IDisposable`
- L71 _private* field_ `readonly Uri _uri`
- L72 _private* field_ `readonly JsonSerializerOptions _jsonOptions`
- L73 _private* field_ `readonly ArrayMemoryWriter _packetMemoryWriter`
- L74 _private* field_ `readonly Utf8JsonWriter _packetWriter`
- L76 _public property_ `public Stopwatch Timer { get; }`
- L77 _public property_ `public Uri Uri => ...`
- L78 _public property_ `public bool HasData => ...`
- L80-86 _public ctor_ `public Writer(Uri uri, JsonSerializerOptions jsonOptions)`
- L88-91 _public method_ `public void Dispose()`
- L93-112 _public method_ `public void AddEvent(object payload)`
- L114-122 _public method_ `public byte[] Flush()`

### `Source/Programs/Horde/Plugins/Analytics/HordeServer.Analytics/Telemetry/Sinks/MetricTelemetrySink.cs` (HordeServer.Analytics)


#### class `HordeServer.Telemetry.Sinks.MetricTelemetrySink`  
`class MetricTelemetrySink : ITelemetrySink`  
_internal*; L14-45_
- inherits: `ITelemetrySink`
- desc: Consumes telemetry events and generates metrics
- L16 _private* field_ `readonly IMetricCollection _metricCollection`
- L17 _private* field_ `readonly JsonSerializerOptions _jsonOptions`
- L19-25 _public ctor_ `public MetricTelemetrySink(IMetricCollection metricCollection)`
- L28 _public property_ `public bool Enabled => ...` — (inheritdoc)
- L31 _public method_ `public ValueTask DisposeAsync()` — (inheritdoc)
- L34 _public method_ `public ValueTask FlushAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L37-44 _public method_ `public void SendEvent(TelemetryStoreId telemetryStoreId, TelemetryEvent telemetryEvent)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Analytics/HordeServer.Analytics/Telemetry/Sinks/MongoTelemetrySink.cs` (HordeServer.Analytics)


#### class `HordeServer.Telemetry.Sinks.MongoTelemetrySink`  
`public sealed class MongoTelemetrySink : ITelemetrySink, IHostedService, IAsyncDisposable`  
_public; L20-123_
- inherits: `ITelemetrySink, IHostedService, IAsyncDisposable`
- desc: Telemetry sink which writes data to a MongoDB collection
- L46 _private* field_ `readonly MongoTelemetryConfig? _config`
- L47 _private* field_ `readonly IMongoCollection<EventDocument> _collection`
- L49 _private* field_ `readonly MongoBufferedWriter<EventDocument> _writer`
- L51 _private* field_ `readonly ITicker _cleanupTicker`
- L52 _private* field_ `readonly JsonSerializerOptions _jsonOptions`
- L53 _private* field_ `readonly ILogger _logger`
- L56 _public property_ `public bool Enabled => ...` — (inheritdoc)
- L61-71 _public ctor_ `public MongoTelemetrySink(IMongoService mongoService, IClock clock, IOptions<AnalyticsServerConfig> serverSettings, ILogger<MongoTelemetrySink> logger)` — Constructor
- L74-81 _public method_ `public async Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L84-88 _public method_ `public async Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L90-103 _private* method_ `async ValueTask CleanupAsync(CancellationToken cancellationToken)`
- L106-111 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L114 _public method_ `public ValueTask FlushAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L118-122 _public method_ `public void SendEvent(TelemetryStoreId telemetryStoreId, TelemetryEvent telemetryEvent)` — (inheritdoc)

#### class `HordeServer.Telemetry.Sinks.MongoTelemetrySink.EventDocument`  
`class EventDocument`  
_private*; L22-44_
- L24 _public property_ `public ObjectId Id { get; set; }`
- L27 _public property_ `public TelemetryStoreId TelemetryStoreId { get; set; }` — attrs: `[BsonElement("ts")]`
- L30 _public property_ `public BsonDocument Data { get; set; }` — attrs: `[BsonElement("data")]`
- L33-36 _public ctor_ `public EventDocument()` — attrs: `[BsonConstructor]`
- L38-43 _public ctor_ `public EventDocument(TelemetryStoreId telemetryStoreId, BsonDocument data)`

### `Source/Programs/Horde/Plugins/Analytics/HordeServer.Analytics/Telemetry/Sinks/NullTelemetrySink.cs` (HordeServer.Analytics)


#### class `HordeServer.Telemetry.Sinks.NullTelemetrySink`  
`public sealed class NullTelemetrySink : ITelemetrySink`  
_public; L10-26_
- inherits: `ITelemetrySink`
- desc: Telemetry sink that discards all events
- L13 _public property_ `public bool Enabled => ...` — (inheritdoc)
- L16 _public method_ `public ValueTask DisposeAsync()` — (inheritdoc)
- L20 _public method_ `public ValueTask FlushAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L24-25 _public method_ `public void SendEvent(TelemetryStoreId telemetryStoreId, TelemetryEvent telemetryEvent)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Analytics/HordeServer.Analytics/Telemetry/TelemetryController.cs` (HordeServer.Analytics)


#### class `HordeServer.Telemetry.TelemetryController`  
`public class TelemetryController : HordeControllerBase`  
_public; L20-251_
- attrs: `[ApiController] [Route("[controller]")]`
- inherits: `HordeControllerBase`
- desc: Controller for the /api/v1/telemetry endpoint
- L22 _private* field_ `readonly TelemetryManager _telemetryManager`
- L23 _private* field_ `readonly IMetricCollection _metricCollection`
- L24 _private* field_ `readonly IOptionsSnapshot<AnalyticsConfig> _analyticsConfig`
- L29-34 _public ctor_ `public TelemetryController(TelemetryManager telemetryManager, IMetricCollection metricCollection, IOptionsSnapshot<AnalyticsConfig> analyticsConfig)` — Constructor
- L49-52 _public method_ `public Task<ActionResult<List<GetTelemetryMetricsResponse>>> GetMetricsAsync([FromQuery] MetricId[] id, [FromQuery] DateTime? minTime = null, [FromQuery] DateTime? maxTime = null, [FromQuery] string? group = null, [FromQuery] int results = 50, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Authorize] [Route("/api/v1/telemetry/metrics")] [Obsolete("Pass a telemetry store id in the route instead")]` — Queries aggregated metrics from the telemetry system
- L66-89 _public method_ `public async Task<ActionResult<List<GetTelemetryMetricsMetaResponse>>> GetMetricsMetaAsync(TelemetryStoreId storeId, [FromQuery] MetricId[] id, [FromQuery] DateTime? minTime = null, [FromQuery] DateTime? maxTime = null, [FromQuery] int results = 50, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Authorize] [Route("/api/v1/telemetry/{storeId}/metrics/meta")]` — Queries aggregated metrics from the telemetry system
- L104-153 _public method_ `public async Task<ActionResult<List<GetTelemetryMetricsResponse>>> GetMetricsAsync(TelemetryStoreId storeId, [FromQuery] MetricId[] id, [FromQuery] DateTime? minTime = null, [FromQuery] DateTime? maxTime = null, [FromQuery] int results = 50, [FromQuery(Name = "group")] string[]? groups = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Authorize] [Route("/api/v1/telemetry/{storeId}/metrics")]` — Queries aggregated metrics from the telemetry system
- L166-169 _public method_ `public ActionResult PostEvent([FromBody] PostTelemetryEventStreamRequest request, [FromQuery][Required] string appId, [FromQuery][Required] string appVersion, [FromQuery][Required] string appEnvironment, [FromQuery][Required] TelemetryUploadType uploadType, [FromQuery] string? sessionId = null)` — attrs: `[HttpPost] [Route("/api/v1/telemetry")]` — Posts a new telemetry event. This API is modeled after Epic's external data router, allowing events in the engine to be sent to Horde using the same mechanism.
- L183-197 _public method_ `public ActionResult PostEvent(TelemetryStoreId storeId, [FromBody] PostTelemetryEventStreamRequest request, [FromQuery][Required] string appId, [FromQuery][Required] string appVersion, [FromQuery][Required] string appEnvironment, [FromQuery][Required] TelemetryUploadType uploadType, [FromQuery] string? sessionId = null)` — attrs: `[HttpPost] [Route("/api/v1/telemetry/{storeId}")]` — Posts a new telemetry event. This API is modeled after Epic's external data router, allowing events in the engine to be sent to Horde using the same mechanism.
- L206-250 _public method_ `public ActionResult<List<GetTelemetryViewResponse>> GetDashboardViews()` — attrs: `[HttpGet] [Authorize] [Route("/api/v1/telemetry/views")]` — Get telemetry views

### `Source/Programs/Horde/Plugins/Analytics/HordeServer.Analytics/Telemetry/TelemetryEvent.cs` (HordeServer.Analytics)


#### class `HordeServer.Telemetry.TelemetryEvent`  
`public class TelemetryEvent`  
_public; L8-28_
- desc: Wrapper around native telemetry objects
- L13 _public property_ `public TelemetryRecordMeta RecordMeta { get; set; }` — Record metadata
- L18 _public property_ `public object Payload { get; }` — Accessor for the native object
- L23-27 _public ctor_ `public TelemetryEvent(TelemetryRecordMeta recordMeta, object payload)` — Constructor

### `Source/Programs/Horde/Plugins/Analytics/HordeServer.Analytics/Telemetry/TelemetryManager.cs` (HordeServer.Analytics)


#### class `HordeServer.Telemetry.TelemetryManager`  
`public sealed class TelemetryManager : ITelemetryWriter, IHostedService`  
_public; L19-139_
- inherits: `ITelemetryWriter, IHostedService`
- desc: Telemetry sink dispatching incoming events to all registered sinks
- L22 _public property_ `public bool Enabled => ...` — (inheritdoc)
- L24 _private field_ `private readonly List<ITelemetrySink> _telemetrySinks = new()`
- L25 _private field_ `private readonly ITicker _ticker`
- L26 _private field_ `private readonly Tracer _tracer`
- L27 _private field_ `private readonly ILogger<TelemetryManager> _logger`
- L28 _private field_ `private readonly TelemetryRecordMeta _serverEventMetadata`
- L33-60 _public ctor_ `public TelemetryManager(IServiceProvider serviceProvider, IServerInfo serverInfo, IClock clock, IOptions<AnalyticsServerConfig> serverSettings, Tracer tracer, ILoggerFactory loggerFactory)` — Constructor
- L63-66 _public method_ `public void WriteEvent(TelemetryStoreId telemetryStoreId, object payload)` — (inheritdoc)
- L69-92 _public method_ `public void WriteEvent(TelemetryStoreId telemetryStoreId, TelemetryRecordMeta metadata, object payload)` — (inheritdoc)
- L94-107 _private* method_ `static string GetEventText(TelemetryEvent telemetryEvent)`
- L110-113 _public method_ `public async Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L116-119 _public method_ `public async Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L122-129 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L132-138 _public method_ `public async ValueTask FlushAsync(CancellationToken cancellationToken)` — (inheritdoc)
