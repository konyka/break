# CSharp / HordeServer.Storage

- project root: `Source/Programs/Horde/Plugins/Storage/HordeServer.Storage`
- files: 16; symbols: 649
- symbol kinds: class=54, const=1, ctor=32, enum=2, enumerator=9, field=111, interface=5, method=215, property=216, record=3, record struct=1
- access marked `*` is implicit (not written in source)

### `Source/Programs/Horde/Plugins/Storage/HordeServer.Storage/Debug/StorageDebugController.cs` (HordeServer.Storage)


#### class `HordeServer.Debug.StorageDebugController`  
`public class StorageDebugController : HordeControllerBase`  
_public; L23-55_
- attrs: `[ApiController] [Authorize] [DebugEndpoint] [Tags("Debug")]`
- inherits: `HordeControllerBase`
- desc: Debug functionality for the storage system
- L25 _private* field_ `readonly IServiceProvider _serviceProvider`
- L26 _private* field_ `readonly IOptionsSnapshot<StorageConfig> _storageConfig`
- L27 _private* field_ `readonly ILogger _logger`
- L32-37 _public ctor_ `public StorageDebugController(IServiceProvider serviceProvider, IOptionsSnapshot<StorageConfig> storageConfig, ILogger<StorageDebugController> logger)` — Constructor
- L44-54 _public method_ `public ActionResult WriteCacheRefStats()` — attrs: `[HttpPost] [Route("/api/v1/debug/writecacherefstats")]` — Writes stats for the storage backend cache

### `Source/Programs/Horde/Plugins/Storage/HordeServer.Storage/Properties/AssemblyInfo.cs` (HordeServer.Storage)
_(no declarations)_


### `Source/Programs/Horde/Plugins/Storage/HordeServer.Storage/Storage/BackendId.cs` (HordeServer.Storage)


#### record struct `HordeServer.Storage.BackendId`  
`public record struct BackendId(StringId Id)`  
_public; L18-37_
- attrs: `[JsonSchemaString] [TypeConverter(typeof(StringIdTypeConverter<BackendId, BackendIdConverter>))] [StringIdConverter(typeof(BackendIdConverter))] [CbConverter(typeof(StringIdCbConverter<BackendId, BackendIdConverter>))]`
- desc: Identifier for a pool
- L23 _public property_ `public static BackendId Empty { get; }` — Empty backend id
- L28-30 _public ctor_ `public BackendId(string id) : this(new StringId(id))` — Constructor
- L33 _public property_ `public bool IsEmpty => ...` — (inheritdoc)
- L36 _public method_ `public override string ToString()` — (inheritdoc)

#### class `HordeServer.Storage.BackendIdConverter`  
`class BackendIdConverter : StringIdConverter<BackendId>`  
_internal*; L42-49_
- inherits: `StringIdConverter<BackendId>`
- desc: Converter to and from StringId instances.
- L45 _public method_ `public override BackendId FromStringId(StringId id)` — (inheritdoc)
- L48 _public method_ `public override StringId ToStringId(BackendId value)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Storage/HordeServer.Storage/Storage/CollectionStatsService.cs` (HordeServer.Storage)


#### class `HordeServer.Storage.CollectionStatEntry`  
`public class CollectionStatEntry`  
_public; L16-59_
- desc: Entry for a single collection's stats within a snapshot
- L22 _public property_ `public string CollectionName { get; set; }` — attrs: `[BsonElement("name")]` — Name of the MongoDB collection
- L28 _public property_ `public long DocumentCount { get; set; }` — attrs: `[BsonElement("cnt")]` — Number of documents in the collection
- L34 _public property_ `public long DataSizeBytes { get; set; }` — attrs: `[BsonElement("dsz")]` — Total data size in bytes
- L40 _public property_ `public long IndexSizeBytes { get; set; }` — attrs: `[BsonElement("isz")]` — Total index size in bytes
- L46 _public property_ `public long StorageSizeBytes { get; set; }` — attrs: `[BsonElement("ssz")]` — Total storage size in bytes
- L52 _public property_ `public long AvgDocSizeBytes { get; set; }` — attrs: `[BsonElement("asz")]` — Average document size in bytes
- L58 _public property_ `public double FragmentationRatio { get; set; }` — attrs: `[BsonElement("frag")]` — Ratio of storage size to data size indicating fragmentation

#### class `HordeServer.Storage.CollectionStatsDocument`  
`public class CollectionStatsDocument`  
_public; L64-82_
- desc: MongoDB document for a collection stats snapshot
- L69 _public property_ `public ObjectId Id { get; set; }` — Unique identifier for this document
- L75 _public property_ `public DateTime TimeUtc { get; set; }` — attrs: `[BsonElement("tm")]` — Time this snapshot was captured
- L81 _public property_ `public List<CollectionStatEntry> Collections { get; set; }` — attrs: `[BsonElement("cols")]` — Stats for each monitored collection

#### class `HordeServer.Storage.CollectionStatsService`  
`public sealed class CollectionStatsService : IHostedService, IAsyncDisposable`  
_public; L87-218_
- inherits: `IHostedService, IAsyncDisposable`
- desc: Periodically captures MongoDB collStats for key storage collections
- L89 _private* property_ `static TimeSpan RetainDays { get; }`
- L91 _private* field_ `static readonly string[] s_targetCollections = new[] { "Storage.Blobs", "Storage.Refs", "Storage.GcMetrics", "Storage.CollectionStats", "ArtifactsV2", "Jobs", "LogFiles", "LogEvents" }`
- L103 _private* field_ `readonly IMongoCollection<CollectionStatsDocument> _collection`
- L104 _private* field_ `readonly IMongoService _mongoService`
- L105 _private* field_ `readonly IClock _clock`
- L106 _private* field_ `readonly ILogger _logger`
- L109 _private* field_ `readonly ITicker _snapshotTicker`
- L110 _private* field_ `readonly ITicker _cleanupTicker`
- L116-128 _public ctor_ `public CollectionStatsService(IMongoService mongoService, IClock clock, ILogger<CollectionStatsService> logger)` — Constructor
- L131-135 _public method_ `public async Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L138-142 _public method_ `public async Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L145-149 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L154-157 _public method_ `public async Task<CollectionStatsDocument?> GetLatestAsync(CancellationToken cancellationToken)` — Get the most recent collection stats snapshot
- L162-167 _public method_ `public async Task<IReadOnlyList<CollectionStatsDocument>> FindAsync(DateTime minTime, DateTime maxTime, int maxResults, CancellationToken cancellationToken)` — Query historical collection stats snapshots
- L169-210 _private* method_ `async ValueTask SnapshotAsync(CancellationToken cancellationToken)`
- L212-217 _private* method_ `async ValueTask CleanupAsync(CancellationToken cancellationToken)`

### `Source/Programs/Horde/Plugins/Storage/HordeServer.Storage/Storage/GcMetricsCollection.cs` (HordeServer.Storage)


#### record `HordeServer.Storage.GcMetricEntry`  
`public record GcMetricEntry`  
_public; L19-75_
- desc: Input record for adding GC metric entries
- L24 _public property_ `public NamespaceId NamespaceId { get; init; }` — Namespace for this GC metric
- L29 _public property_ `public long BlobsDeleted { get; init; }` — Number of blobs deleted during this sweep
- L34 _public property_ `public long BlobsChecked { get; init; }` — Number of blobs checked during this sweep
- L39 _public property_ `public long BytesFreed { get; init; }` — Total bytes freed during this sweep
- L44 _public property_ `public double SweepDurationMs { get; init; }` — Duration of the sweep in milliseconds
- L49 _public property_ `public bool WasPaused { get; init; }` — Whether GC was paused due to queue pressure
- L54 _public property_ `public long QueueDepth { get; init; }` — Current depth of the GC queue
- L59 _public property_ `public long BlobsIngested { get; init; }` — Number of blobs ingested since last tick
- L64 _public property_ `public long EnqueueFailures { get; init; }` — Number of enqueue failures since last tick
- L69 _public property_ `public long ThrottleEvents { get; init; }` — Number of throttle events since last tick
- L74 _public property_ `public long RefsExpired { get; init; }` — Number of refs that expired since last tick

#### class `HordeServer.Storage.GcMetricDocument`  
`public class GcMetricDocument`  
_public; L80-158_
- desc: MongoDB document for GC metric snapshots
- L85 _public property_ `public ObjectId Id { get; set; }` — Unique identifier for this document
- L91 _public property_ `public DateTime TimeUtc { get; set; }` — attrs: `[BsonElement("tm")]` — Time this metric was recorded
- L97 _public property_ `public NamespaceId NamespaceId { get; set; }` — attrs: `[BsonElement("ns")]` — Namespace for this GC metric
- L103 _public property_ `public long BlobsDeleted { get; set; }` — attrs: `[BsonElement("del")]` — Number of blobs deleted
- L109 _public property_ `public long BlobsChecked { get; set; }` — attrs: `[BsonElement("chk")]` — Number of blobs checked
- L115 _public property_ `public long BytesFreed { get; set; }` — attrs: `[BsonElement("freed")]` — Total bytes freed
- L121 _public property_ `public double SweepDurationMs { get; set; }` — attrs: `[BsonElement("sweep_ms")]` — Duration of the sweep in milliseconds
- L127 _public property_ `public bool WasPaused { get; set; }` — attrs: `[BsonElement("paused")]` — Whether GC was paused due to queue pressure
- L133 _public property_ `public long QueueDepth { get; set; }` — attrs: `[BsonElement("qdepth")]` — Current depth of the GC queue
- L139 _public property_ `public long BlobsIngested { get; set; }` — attrs: `[BsonElement("ing")]` — Number of blobs ingested
- L145 _public property_ `public long EnqueueFailures { get; set; }` — attrs: `[BsonElement("enq_fail")]` — Number of enqueue failures
- L151 _public property_ `public long ThrottleEvents { get; set; }` — attrs: `[BsonElement("throttle")]` — Number of throttle events
- L157 _public property_ `public long RefsExpired { get; set; }` — attrs: `[BsonElement("refs_exp")]` — Number of refs that expired

#### class `HordeServer.Storage.GcMetricsCollection`  
`public sealed class GcMetricsCollection : IHostedService, IAsyncDisposable`  
_public; L163-305_
- inherits: `IHostedService, IAsyncDisposable`
- desc: Stores per-tick GC metrics in MongoDB for dashboard trending
- L165 _private* property_ `static TimeSpan RetainDays { get; }`
- L167 _private* field_ `readonly IMongoCollection<GcMetricDocument> _collection`
- L168 _private* field_ `readonly StorageService _storageService`
- L169 _private* field_ `readonly IOptionsMonitor<StorageConfig> _storageConfig`
- L172 _private* field_ `readonly MongoBufferedWriter<GcMetricDocument> _writer`
- L173 _private* field_ `readonly ITicker _drainTicker`
- L174 _private* field_ `readonly ITicker _cleanupTicker`
- L177 _private* field_ `readonly IClock _clock`
- L178 _private* field_ `readonly ILogger _logger`
- L183-197 _public ctor_ `public GcMetricsCollection(StorageService storageService, IMongoService mongoService, IOptionsMonitor<StorageConfig> storageConfig, IClock clock, ILogger<GcMetricsCollection> logger)` — Constructor
- L200-205 _public method_ `public async Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L208-213 _public method_ `public async Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L216-222 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L227-245 _public method_ `public void Add(GcMetricEntry entry)` — Record a GC metric entry (non-blocking buffered write)
- L250-259 _public method_ `public async Task<IReadOnlyList<GcMetricDocument>> FindAsync(NamespaceId? ns, DateTime minTime, DateTime maxTime, int maxResults, CancellationToken cancellationToken)` — Query GC metrics for dashboard display
- L264 _public method_ `public ValueTask FlushAsync(CancellationToken cancellationToken)` — Flush buffered writes
- L266-297 _private* method_ `async ValueTask<TimeSpan?> DrainAsync(CancellationToken cancellationToken)`
- L299-304 _private* method_ `async ValueTask CleanupAsync(CancellationToken cancellationToken)`

### `Source/Programs/Horde/Plugins/Storage/HordeServer.Storage/Storage/IObjectStoreFactory.cs` (HordeServer.Storage)


#### interface `HordeServer.Storage.IObjectStoreFactory`  
`public interface IObjectStoreFactory`  
_public; L10-18_
- desc: Service which resolves storage backend instances
- L17 _public* method_ `IObjectStore CreateObjectStore(BackendConfig backendConfig)` — Creates a new storage backend with the given identifier

### `Source/Programs/Horde/Plugins/Storage/HordeServer.Storage/Storage/ObjectStoreFactory.cs` (HordeServer.Storage)


#### class `HordeServer.Storage.ObjectStoreFactory`  
`class ObjectStoreFactory : IObjectStoreFactory`  
_internal*; L15-81_
- inherits: `IObjectStoreFactory`
- desc: Default implementation of IObjectStoreFactory
- L17 _private* field_ `readonly IServiceProvider _serviceProvider`
- L18 _private* field_ `readonly IServerInfo _serverInfo`
- L19 _private* field_ `readonly object _lockObject = new object()`
- L20 _private* field_ `IReadOnlyDictionary<IoHash, IObjectStore> _objectStores = ...`
- L20 _private* field_ `IReadOnlyDictionary< _objectStores = new Dictionary<IoHash, IObjectStore>()`
- L21 _private* field_ `readonly ILogger _logger`
- L26-31 _public ctor_ `public ObjectStoreFactory(IServiceProvider serviceProvider, IServerInfo serverInfo, ILogger<ObjectStoreFactory> logger)` — Constructor
- L34-56 _public method_ `public IObjectStore CreateObjectStore(BackendConfig config)` — (inheritdoc)
- L63-80 _private* method_ `IObjectStore CreateObjectStoreInternal(BackendConfig config)` — Creates a storage backend with the given configuration

### `Source/Programs/Horde/Plugins/Storage/HordeServer.Storage/Storage/ObjectStores/AwsObjectStore.cs` (HordeServer.Storage)


#### class `HordeServer.Storage.ObjectStores.AwsException`  
`public sealed class AwsException : StorageException`  
_public; L22-33_
- inherits: `StorageException`
- desc: Exception wrapper for S3 requests
- L29-32 _public ctor_ `public AwsException(string message, Exception? innerException) : base(message, innerException)` — Constructor

#### enum `HordeServer.Storage.ObjectStores.AwsCredentialsType`  
`public enum AwsCredentialsType`  
_public; L38-59_
- desc: Credentials to use for AWS
- L43 _public* enumerator_ `Default` — Use default credentials from the AWS SDK
- L48 _public* enumerator_ `Profile` — Read credentials from the IAwsStorageOptions.AwsProfile profile in the AWS config file
- L53 _public* enumerator_ `AssumeRole` — Assume a particular role. Should specify ARN in IAwsStorageOptions.AwsRole
- L58 _public* enumerator_ `AssumeRoleWebIdentity` — Assume a particular role using the current environment variables.

#### interface `HordeServer.Storage.ObjectStores.IAwsStorageOptions`  
`public interface IAwsStorageOptions`  
_public; L64-95_
- desc: Options for AWS
- L69 _public property_ `public AwsCredentialsType? AwsCredentials { get; }` — Type of credentials to use
- L74 _public property_ `public string? AwsBucketName { get; }` — Name of the bucket to use
- L79 _public property_ `public string? AwsBucketPath { get; }` — Base path within the bucket
- L84 _public property_ `public string? AwsRole { get; }` — ARN of a role to assume
- L89 _public property_ `public string? AwsProfile { get; }` — The AWS profile to read credentials form
- L94 _public property_ `public string? AwsRegion { get; }` — Region to connect to

#### class `HordeServer.Storage.ObjectStores.AwsObjectStore`  
`public sealed class AwsObjectStore : IObjectStore`  
_public; L100-577_
- inherits: `IObjectStore`
- desc: Storage backend using AWS S3
- L105 _private field_ `private readonly IAmazonS3 _client` — S3 Client
- L110 _private field_ `private readonly IAwsStorageOptions _options` — Options for AWs
- L115 _private field_ `private readonly SemaphoreSlim _semaphore` — Semaphore for connecting to AWS
- L120 _private field_ `private readonly string _pathPrefix` — Prefix for objects in the bucket
- L125 _private field_ `private readonly ILogger _logger` — Logger interface
- L128 _public property_ `public bool SupportsRedirects => ...` — (inheritdoc)
- L137-149 _public ctor_ `public AwsObjectStore(IAmazonS3 client, IAwsStorageOptions options, SemaphoreSlim semaphore, ILogger<AwsObjectStore> logger)` — Constructor
- L205 _private* method_ `string GetFullPath(ObjectKey key)`
- L208-224 _public method_ `public Task<Stream> OpenAsync(ObjectKey key, int offset, int? length, CancellationToken cancellationToken)` — (inheritdoc)
- L226-333 _private* method_ `async Task<Stream> OpenAsync(ObjectKey key, ByteRange? byteRange, CancellationToken cancellationToken)`
- L336-340 _public method_ `public async Task<IReadOnlyMemoryOwner<byte>> ReadAsync(ObjectKey key, int offset, int? length, CancellationToken cancellationToken)` — (inheritdoc)
- L343 _public method_ `public ValueTask<Uri?> TryGetReadRedirectAsync(ObjectKey key, CancellationToken cancellationToken = default)` — (inheritdoc)
- L347 _public method_ `public ValueTask<Uri?> TryGetWriteRedirectAsync(ObjectKey key, CancellationToken cancellationToken = default)` — (inheritdoc)
- L353-378 _private* method_ `Uri? GetPresignedUrl(ObjectKey key, HttpVerb verb)` — Helper method to generate a presigned URL for a request
- L381-411 _public method_ `public async Task WriteAsync(ObjectKey key, Stream inputStream, CancellationToken cancellationToken = default)` — (inheritdoc)
- L414-498 _public method_ `public async Task WriteInternalAsync(string fullPath, Stream stream, CancellationToken cancellationToken)` — (inheritdoc)
- L508-520 _private* method_ `static async Task ReadExactLengthAsync(System.IO.Stream stream, byte[] buffer, int length, CancellationToken cancellationToken)` — Reads data of an exact length into a stream
- L523-532 _public method_ `public async Task DeleteAsync(ObjectKey key, CancellationToken cancellationToken)` — (inheritdoc)
- L535-552 _public method_ `public async Task<bool> ExistsAsync(ObjectKey key, CancellationToken cancellationToken)` — (inheritdoc)
- L555-573 _public method_ `public async Task<long> GetSizeAsync(ObjectKey key, CancellationToken cancellationToken)` — (inheritdoc)
- L576 _public method_ `public void GetStats(StorageStats stats)` — (inheritdoc)

#### class `HordeServer.Storage.ObjectStores.AwsObjectStore.WrappedResponseStream`  
`class WrappedResponseStream : Stream`  
_private*; L151-203_
- inherits: `Stream`
- L153 _private* field_ `readonly IDisposable _semaphore`
- L154 _private* field_ `readonly TelemetrySpan _semaphoreSpan`
- L155 _private* field_ `readonly GetObjectResponse _response`
- L156 _private* field_ `readonly Stream _responseStream`
- L158-164 _public ctor_ `public WrappedResponseStream(IDisposable semaphore, TelemetrySpan semaphoreSpan, GetObjectResponse response)`
- L166 _public property_ `public override bool CanRead => ...`
- L167 _public property_ `public override bool CanSeek => ...`
- L168 _public property_ `public override bool CanWrite => ...`
- L169 _public property_ `public override long Length => ...`
- L170 _public property_ `public override long Position { get; set; }`
- L172 _public method_ `public override void Flush()`
- L174 _public method_ `public override int Read(byte[] buffer, int offset, int count)`
- L175 _public method_ `public override ValueTask<int> ReadAsync(Memory<byte> buffer, CancellationToken cancellationToken = default)`
- L176 _public method_ `public override Task<int> ReadAsync(byte[] buffer, int offset, int count, CancellationToken cancellationToken)`
- L178 _public method_ `public override long Seek(long offset, SeekOrigin origin)`
- L179 _public method_ `public override void SetLength(long value)`
- L180 _public method_ `public override void Write(byte[] buffer, int offset, int count)`
- L182-193 _protected method_ `protected override void Dispose(bool disposing)`
- L195-202 _public method_ `public override async ValueTask DisposeAsync()`

#### class `HordeServer.Storage.ObjectStores.AwsObjectStoreFactory`  
`public sealed class AwsObjectStoreFactory : IDisposable`  
_public; L582-660_
- inherits: `IDisposable`
- desc: Factory for constructing AwsObjectStore instances
- L584 _private* field_ `readonly IConfiguration _configuration`
- L585 _private* field_ `readonly SemaphoreSlim _semaphore`
- L586 _private* field_ `readonly ILogger<AwsObjectStore> _logger`
- L591-596 _public ctor_ `public AwsObjectStoreFactory(IConfiguration configuration, ILogger<AwsObjectStore> logger)` — Constructor
- L599-602 _public method_ `public void Dispose()` — (inheritdoc)
- L608-616 _public method_ `public AwsObjectStore CreateStore(IAwsStorageOptions options)` — Create a new object store with the given configuration
- L624-659 _private* method_ `static AWSOptions GetAwsOptions(IConfiguration configuration, IAwsStorageOptions options)` — Gets the AWS options

### `Source/Programs/Horde/Plugins/Storage/HordeServer.Storage/Storage/ObjectStores/AzureObjectStore.cs` (HordeServer.Storage)


#### class `HordeServer.Storage.ObjectStores.AzureException`  
`public sealed class AzureException : Exception`  
_public; L17-28_
- inherits: `Exception`
- desc: Exception wrapper for S3 requests
- L24-27 _public ctor_ `public AzureException(string? message, Exception? innerException) : base(message, innerException)` — Constructor

#### interface `HordeServer.Storage.ObjectStores.IAzureStorageOptions`  
`public interface IAzureStorageOptions`  
_public; L33-44_
- desc: Options for Azure
- L38 _public property_ `public string? AzureConnectionString { get; }` — Connection string for Azure
- L43 _public property_ `public string? AzureContainerName { get; }` — Name of the container

#### class `HordeServer.Storage.ObjectStores.AzureObjectStore`  
`public sealed class AzureObjectStore : IObjectStore`  
_public; L49-213_
- inherits: `IObjectStore`
- desc: Storage backend using Azure
- L51 _private field_ `private readonly ILogger _logger`
- L52 _private field_ `private readonly Tracer _tracer`
- L53 _private field_ `private readonly BlobContainerClient _blobContainer`
- L56 _public property_ `public bool SupportsRedirects => ...` — (inheritdoc)
- L61-75 _public ctor_ `public AzureObjectStore(IAzureStorageOptions options, ILogger<AzureObjectStore> logger, Tracer tracer)` — Constructor
- L78-95 _public method_ `public async Task<Stream> OpenAsync(ObjectKey key, int offset, int? length, CancellationToken cancellationToken = default)` — (inheritdoc)
- L98-102 _public method_ `public async Task<IReadOnlyMemoryOwner<byte>> ReadAsync(ObjectKey key, int offset, int? length, CancellationToken cancellationToken = default)` — (inheritdoc)
- L105-118 _public method_ `public async Task WriteAsync(ObjectKey key, Stream stream, CancellationToken cancellationToken = default)` — (inheritdoc)
- L121-130 _public method_ `public async Task<bool> ExistsAsync(ObjectKey key, CancellationToken cancellationToken)` — (inheritdoc)
- L133-151 _public method_ `public async Task<long> GetSizeAsync(ObjectKey key, CancellationToken cancellationToken)` — (inheritdoc)
- L154-162 _public method_ `public async Task DeleteAsync(ObjectKey key, CancellationToken cancellationToken)` — (inheritdoc)
- L165-173 _public method_ `public async ValueTask<Uri?> TryGetReadRedirectAsync(ObjectKey key, CancellationToken cancellationToken = default)` — (inheritdoc)
- L176-184 _public method_ `public async ValueTask<Uri?> TryGetWriteRedirectAsync(ObjectKey key, CancellationToken cancellationToken = default)` — (inheritdoc)
- L189-207 _private* method_ `Uri? TryGetPresignedUrl(ObjectKey key, BlobSasPermissions permissions)` — Helper method to generate a presigned URL for a request
- L210-212 _public method_ `public void GetStats(StorageStats stats)` — (inheritdoc)

#### class `HordeServer.Storage.ObjectStores.AzureObjectStoreFactory`  
`public sealed class AzureObjectStoreFactory`  
_public; L218-240_
- desc: Factory for constructing AzureObjectStore instances
- L220 _private* field_ `readonly Tracer _tracer`
- L221 _private* field_ `readonly ILogger<AzureObjectStore> _logger`
- L226-230 _public ctor_ `public AzureObjectStoreFactory(Tracer tracer, ILogger<AzureObjectStore> logger)` — Constructor
- L236-239 _public method_ `public AzureObjectStore CreateStore(IAzureStorageOptions options)` — Create a new object store with the given configuration

### `Source/Programs/Horde/Plugins/Storage/HordeServer.Storage/Storage/ObjectStores/ChainedObjectStore.cs` (HordeServer.Storage)


#### class `HordeServer.Storage.Storage.ObjectStores.ChainedObjectStore`  
`class ChainedObjectStore : IObjectStore`  
_internal*; L11-95_
- inherits: `IObjectStore`
- desc: Object store which allows falling back to reading from a secondary object store if a key is not found in the primary store. Useful for migrations.
- L13 _private* field_ `readonly IObjectStore _primary`
- L14 _private* field_ `readonly IObjectStore _secondary`
- L17 _public property_ `public bool SupportsRedirects => ...` — (inheritdoc)
- L24-28 _public ctor_ `public ChainedObjectStore(IObjectStore primary, IObjectStore secondary)` — Constructor
- L31 _public method_ `public Task DeleteAsync(ObjectKey key, CancellationToken cancellationToken = default)` — (inheritdoc)
- L35 _public method_ `public async Task<bool> ExistsAsync(ObjectKey key, CancellationToken cancellationToken = default)` — (inheritdoc)
- L39 _public method_ `public Task<long> GetSizeAsync(ObjectKey key, CancellationToken cancellationToken = default)` — (inheritdoc)
- L43-47 _public method_ `public void GetStats(StorageStats stats)` — (inheritdoc)
- L50-60 _public method_ `public async Task<Stream> OpenAsync(ObjectKey key, int offset, int? length, CancellationToken cancellationToken = default)` — (inheritdoc)
- L63-73 _public method_ `public async Task<IReadOnlyMemoryOwner<byte>> ReadAsync(ObjectKey key, int offset, int? length, CancellationToken cancellationToken = default)` — (inheritdoc)
- L76-86 _public method_ `public async ValueTask<Uri?> TryGetReadRedirectAsync(ObjectKey key, CancellationToken cancellationToken = default)` — (inheritdoc)
- L89 _public method_ `public ValueTask<Uri?> TryGetWriteRedirectAsync(ObjectKey key, CancellationToken cancellationToken = default)` — (inheritdoc)
- L93 _public method_ `public Task WriteAsync(ObjectKey key, Stream stream, CancellationToken cancellationToken = default)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Storage/HordeServer.Storage/Storage/ObjectStores/GcsObjectStore.cs` (HordeServer.Storage)


#### class `HordeServer.Storage.ObjectStores.GcsException`  
`public sealed class GcsException : StorageException`  
_public; L22-33_
- inherits: `StorageException`
- desc: Exception wrapper for GCS requests
- L29-32 _public ctor_ `public GcsException(string message, Exception? innerException) : base(message, innerException)` — Constructor

#### interface `HordeServer.Storage.ObjectStores.IGcsStorageOptions`  
`public interface IGcsStorageOptions`  
_public; L38-49_
- desc: Options for GCS
- L43 _public property_ `public string? GcsBucketName { get; }` — Name of the GCS bucket to use
- L48 _public property_ `public string? GcsBucketPath { get; }` — Base path within the bucket

#### class `HordeServer.Storage.ObjectStores.GcsObjectStore`  
`public sealed class GcsObjectStore : IObjectStore, IDisposable`  
_public; L54-365_
- inherits: `IObjectStore, IDisposable`
- desc: Storage backend using GCP GCS
- L59 _private field_ `private readonly StorageClient _client` — GCS Client
- L64 _private field_ `private readonly IGcsStorageOptions _options` — Options for GCS
- L69 _private field_ `private readonly SemaphoreSlim _semaphore` — Semaphore for connecting to GCS
- L74 _private field_ `private readonly string _pathPrefix` — Prefix for objects in the bucket
- L79 _private field_ `private readonly ILogger _logger` — Logger interface
- L82 _public property_ `public bool SupportsRedirects => ...` — (inheritdoc)
- L90-104 _public ctor_ `public GcsObjectStore(IGcsStorageOptions options, SemaphoreSlim semaphore, ILogger<GcsObjectStore> logger)` — Constructor
- L107-111 _public method_ `public void Dispose()` — (inheritdoc)
- L167 _private* method_ `string GetFullPath(ObjectKey key)`
- L170-226 _public method_ `public async Task<Stream> OpenAsync(ObjectKey key, int offset, int? length, CancellationToken cancellationToken = default)` — (inheritdoc)
- L229-233 _public method_ `public async Task<IReadOnlyMemoryOwner<byte>> ReadAsync(ObjectKey key, int offset, int? length, CancellationToken cancellationToken = default)` — (inheritdoc)
- L236-267 _public method_ `public async Task WriteAsync(ObjectKey key, Stream stream, CancellationToken cancellationToken = default)` — (inheritdoc)
- L270-285 _public method_ `public async Task<bool> ExistsAsync(ObjectKey key, CancellationToken cancellationToken = default)` — (inheritdoc)
- L288-307 _public method_ `public async Task<long> GetSizeAsync(ObjectKey key, CancellationToken cancellationToken = default)` — (inheritdoc)
- L310-317 _public method_ `public async Task DeleteAsync(ObjectKey key, CancellationToken cancellationToken = default)` — (inheritdoc)
- L320-323 _public method_ `public async ValueTask<Uri?> TryGetReadRedirectAsync(ObjectKey key, CancellationToken cancellationToken = default)` — (inheritdoc)
- L326-329 _public method_ `public async ValueTask<Uri?> TryGetWriteRedirectAsync(ObjectKey key, CancellationToken cancellationToken = default)` — (inheritdoc)
- L335-361 _private* method_ `async Task<Uri?> GetPresignedUrlAsync(ObjectKey key, HttpMethod method, CancellationToken cancellationToken = default)` — Helper method to generate a presigned URL for a request
- L364 _public method_ `public void GetStats(StorageStats stats)` — (inheritdoc)

#### class `HordeServer.Storage.ObjectStores.GcsObjectStore.WrappedResponseStream`  
`class WrappedResponseStream(IDisposable semaphore, TelemetrySpan semaphoreSpan, MemoryStream stream, Google.Apis.Storage.v1.Data.Object obj) : Stream`  
_private*; L113-165_
- L116 _private* field_ `readonly Stream _responseStream = stream`
- L118 _public property_ `public override bool CanRead => ...`
- L119 _public property_ `public override bool CanSeek => ...`
- L120 _public property_ `public override bool CanWrite => ...`
- L121-132 _public property_ `public override long Length { get; }`
- L134 _public property_ `public override long Position { get; set; }`
- L136 _public method_ `public override void Flush()`
- L138 _public method_ `public override int Read(byte[] buffer, int offset, int count)`
- L139 _public method_ `public override ValueTask<int> ReadAsync(Memory<byte> buffer, CancellationToken cancellationToken = default)`
- L140 _public method_ `public override Task<int> ReadAsync(byte[] buffer, int offset, int count, CancellationToken cancellationToken)`
- L142 _public method_ `public override long Seek(long offset, SeekOrigin origin)`
- L143 _public method_ `public override void SetLength(long value)`
- L144 _public method_ `public override void Write(byte[] buffer, int offset, int count)`
- L146-156 _protected method_ `protected override void Dispose(bool disposing)`
- L158-164 _public method_ `public override async ValueTask DisposeAsync()`

#### class `HordeServer.Storage.ObjectStores.GcsObjectStoreFactory`  
`public sealed class GcsObjectStoreFactory : IDisposable`  
_public; L370-400_
- inherits: `IDisposable`
- desc: Factory for constructing GcsObjectStore instances
- L372 _private* field_ `readonly SemaphoreSlim _semaphore`
- L373 _private* field_ `readonly ILogger<GcsObjectStore> _logger`
- L378-382 _public ctor_ `public GcsObjectStoreFactory(IConfiguration _, ILogger<GcsObjectStore> logger)` — Constructor
- L385-388 _public method_ `public void Dispose()` — (inheritdoc)
- L394-399 _public method_ `public GcsObjectStore CreateStore(IGcsStorageOptions options)` — Create a new object store with the given configuration

### `Source/Programs/Horde/Plugins/Storage/HordeServer.Storage/Storage/StorageAclAction.cs` (HordeServer.Storage)


#### class `HordeServer.Storage.StorageAclAction`  
`public static class StorageAclAction`  
_public; L10-51_
- desc: ACL actions which apply to storage
- L15 _public property_ `public static AclAction ReadBlobs { get; }` — Ability to read blobs from the storage service
- L20 _public property_ `public static AclAction WriteBlobs { get; }` — Ability to write blobs to the storage service
- L25 _public property_ `public static AclAction ReadAliases { get; }` — Ability to read aliases from the storage service
- L30 _public property_ `public static AclAction WriteAliases { get; }` — Ability to write aliases to the storage service
- L35 _public property_ `public static AclAction DeleteAliases { get; }` — Ability to write aliases to the storage service
- L40 _public property_ `public static AclAction ReadRefs { get; }` — Ability to read refs from the storage service
- L45 _public property_ `public static AclAction WriteRefs { get; }` — Ability to write refs to the storage service
- L50 _public property_ `public static AclAction DeleteRefs { get; }` — Ability to delete refs

### `Source/Programs/Horde/Plugins/Storage/HordeServer.Storage/Storage/StorageController.cs` (HordeServer.Storage)


#### class `HordeServer.Storage.StorageController`  
`public class StorageController : HordeControllerBase`  
_public; L31-820_
- attrs: `[Authorize] [ApiController] [Route("[controller]")]`
- inherits: `HordeControllerBase`
- desc: Controller for the /api/v1/storage endpoint
- L33 _private* field_ `readonly StorageService _storageService`
- L34 _private* field_ `readonly IOptionsSnapshot<StorageConfig> _storageConfig`
- L35 _private* field_ `readonly IOptions<StorageServerConfig> _staticStorageConfig`
- L36 _private* field_ `readonly IAclService _aclService`
- L37 _private* field_ `readonly GcMetricsCollection _gcMetrics`
- L38 _private* field_ `readonly CollectionStatsService _collectionStats`
- L43-51 _public ctor_ `public StorageController(StorageService storageService, IOptionsSnapshot<StorageConfig> storageConfig, IOptions<StorageServerConfig> staticStorageConfig, IAclService aclService, GcMetricsCollection gcMetrics, CollectionStatsService collectionStats)` — Constructor
- L53-56 _private* method_ `bool Authorize(NamespaceId namespaceId, AclAction action)`
- L58-73 _private* method_ `bool AuthorizePaths(NamespaceId namespaceId, AclAction action, IEnumerable<string> paths)`
- L83-112 _public method_ `public async Task<ActionResult> UpdateNamespaceAsync(NamespaceId namespaceId, [FromBody] UpdateMetadataRequest request, CancellationToken cancellationToken)` — attrs: `[HttpPost] [Route("/api/v1/storage/{namespaceId}")]` — Update metadata in the storage service
- L122-135 _public method_ `public async Task<ActionResult<WriteBlobResponse>> WriteBlobAsync(NamespaceId namespaceId, WriteBlobRequest request, CancellationToken cancellationToken = default)` — attrs: `[HttpPost] [Route("/api/v1/storage/{namespaceId}/blobs")]` — Uploads data to the storage service.
- L146-159 _public method_ `public async Task<ActionResult<WriteBlobResponse>> WriteBlobAsync(NamespaceId namespaceId, BlobLocator locator, WriteBlobRequest request, CancellationToken cancellationToken = default)` — attrs: `[HttpPut] [Route("/api/v1/storage/{namespaceId}/blobs/{*locator}")]` — Uploads data to the storage service using a client-determined path.
- L161-172 _private* method_ `static string GetPathFromLocator(BlobLocator locator)`
- L182-225 _public method_ `public static async Task<ActionResult<WriteBlobResponse>> WriteBlobAsync(IStorageBackend storageBackend, BlobLocator? locator, WriteBlobRequest request, CancellationToken cancellationToken = default)` — Writes a blob to storage. Exposed as a public utility method to allow other routes with their own authentication methods to wrap their own authentication/redirection.
- L235-248 _public method_ `public async Task<ActionResult> ReadBlobAsync(NamespaceId namespaceId, BlobLocator locator, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/storage/{namespaceId}/blobs/{*locator}")]` — Retrieves data from the storage service.
- L253-306 _public method_ `public static async Task<ActionResult> ReadBlobInternalAsync(IStorageBackend storageBackend, BlobLocator locator, IHeaderDictionary headers, CancellationToken cancellationToken)` — Reads a blob from storage, without performing namespace access checks.
- L317-340 _public method_ `public async Task<ActionResult<FindNodesResponse>> FindNodesAsync(NamespaceId namespaceId, [FromQuery] string alias, [FromQuery] int? maxResults = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/storage/{namespaceId}/nodes")]` — Retrieves data from the storage service.
- L350-365 _public method_ `public async Task<ActionResult> WriteRefAsync(NamespaceId namespaceId, RefName refName, CancellationToken cancellationToken)` — attrs: `[HttpDelete] [Route("/api/v1/storage/{namespaceId}/refs/{*refName}")]` — Deletes a ref from the storage service.
- L376-398 _public method_ `public async Task<ActionResult> WriteRefAsync(NamespaceId namespaceId, RefName refName, [FromBody] WriteRefRequest request, CancellationToken cancellationToken)` — attrs: `[HttpPut] [Route("/api/v1/storage/{namespaceId}/refs/{*refName}")]` — Writes a ref to the storage service.
- L408-421 _public method_ `public async Task<ActionResult<ReadRefResponse>> ReadRefAsync(NamespaceId namespaceId, RefName refName, CancellationToken cancellationToken)` — attrs: `[HttpGet] [Route("/api/v1/storage/{namespaceId}/refs/{*refName}")]` — Retrieves a ref from the storage service.
- L426-446 _public method_ `public static async Task<ActionResult<ReadRefResponse>> ReadRefInternalAsync(IStorageClient storageClient, string basePath, NamespaceId namespaceId, RefName refName, IHeaderDictionary headers, CancellationToken cancellationToken)` — Reads a ref from storage, without performing namespace access checks.
- L456-480 _private* method_ `static bool HasPathClaim(ClaimsPrincipal user, string claimType, NamespaceId namespaceId, string entity)` — Checks whether the user has an explicit claim to read or write to a path within a namespace
- L482-496 _private* method_ `static bool HasPathPrefix(string name, ReadOnlySpan<char> prefix)`
- L498 _private* field_ `static readonly IReadOnlyDictionary<Guid, Type> s_blobGuidToType = ...`
- L498 _private* field_ `static readonly IReadOnlyDictionary< s_blobGuidToType = GetBlobGuidTypeMap()`
- L500-511 _private* method_ `static Dictionary<Guid, Type> GetBlobGuidTypeMap()`
- L525-630 _public method_ `public async Task<ActionResult<object>> GetNodeAsync(NamespaceId namespaceId, BlobLocator locator, [FromQuery] string? pkt = null, [FromQuery] string? exp = null, [FromQuery] bool data = false, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/storage/{namespaceId}/nodes/{*locator}")]` — Gets information about a particular bundle in storage
- L632-668 _private* method_ `static object? GetCbNodeObject(NamespaceId namespaceId, CbField field, IEnumerator<IBlobRef> imports)`
- L671 _private* method_ `static object? GetNodeObject(NamespaceId namespaceId, DirectoryNodeRef? nodeRef)` — attrs: `[return: NotNullIfNotNull("nodeRef")]`
- L674 _private* method_ `static object? GetNodeHandleLink(NamespaceId namespaceId, IHashedBlobRef? handle)` — attrs: `[return: NotNullIfNotNull("handle")]`
- L676 _private* method_ `static string GetNodeLink(NamespaceId namespaceId, IBlobRef handle)`
- L678 _private* method_ `static string GetNodeLink(NamespaceId namespaceId, BlobLocator locator)`
- L685-716 _public method_ `public async Task<ActionResult<GetStorageDashboardResponse>> GetDashboardAsync( [FromQuery] DateTime? minTime, [FromQuery] DateTime? maxTime, [FromQuery] int trendCount = 500, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/storage/dashboard")]` — Get consolidated storage dashboard data (admin-only)
- L718-771 _private* method_ `static StorageDashboardStatus BuildStatusResponse(StorageConfig config, StorageServerConfig serverConfig, (List<(NamespaceId Id, DateTime LastTime)> Namespaces, Dictionary<NamespaceId, long> QueueDepths) gcStatus)`
- L773-795 _private* method_ `static StorageDashboardGcMetrics BuildGcMetricsResponse(IReadOnlyList<GcMetricDocument> docs)`
- L797-819 _private* method_ `static StorageDashboardCollectionStats BuildCollectionStatsResponse(IReadOnlyList<CollectionStatsDocument> docs)`

#### class `HordeServer.Storage.WriteBlobRequest`  
`public class WriteBlobRequest`  
_public; L825-854_
- desc: Request to upload a blob
- L831-835 _public property_ `public bool Leaf { get; set; }` — attrs: `[FromForm(Name = "leaf")]` — Set to indicate that the blob does not have any imports. Used to distinguish from an "unknown" set of imports.
- L841 _public property_ `public List<BlobLocator>? Imports { get; set; }` — attrs: `[FromForm(Name = "import")]` — Imported blobs
- L847 _public property_ `public string? Prefix { get; set; }` — attrs: `[FromForm(Name = "prefix")]` — Prefix for the uploaded file
- L853 _public property_ `public IFormFile? File { get; set; }` — attrs: `[FromForm(Name = "file")]` — Data to be uploaded. May be null, in which case the server may return a separate url.

#### class `HordeServer.Storage.GetStorageDashboardResponse`  
`public class GetStorageDashboardResponse`  
_public; L859-869_
- desc: Consolidated storage dashboard response
- L862 _public property_ `public StorageDashboardStatus Status { get; set; }` — Live status, config, namespaces, backends
- L865 _public property_ `public StorageDashboardGcMetrics GcMetrics { get; set; }` — GC metric history
- L868 _public property_ `public StorageDashboardCollectionStats CollectionStats { get; set; }` — MongoDB collection stats history

#### class `HordeServer.Storage.StorageDashboardStatus`  
`public class StorageDashboardStatus`  
_public; L874-911_
- desc: Live GC configuration and namespace status
- L877 _public property_ `public bool EnableGc { get; set; }` — Primary GC switch
- L880 _public property_ `public bool EnableGcVerification { get; set; }` — Verification mode (log-only, no deletes)
- L883 _public property_ `public int GcWorkerCount { get; set; }` — Concurrent reachability check workers
- L886 _public property_ `public long GcQueueLimit { get; set; }` — Max Redis queue entries before pausing ingestion
- L889 _public property_ `public bool EnableReliableGcEnqueue { get; set; }` — Awaited Redis enqueue vs fire-and-forget
- L892 _public property_ `public bool EnablePerNamespaceQueueIsolation { get; set; }` — Per-namespace queue limits vs global
- L895 _public property_ `public int GcBlobIngestionBatchSize { get; set; }` — Blobs scanned per ingestion tick
- L898 _public property_ `public int GcBatchSize { get; set; }` — Blob IDs per $in reachability query
- L901 _public property_ `public string? BundleCacheDir { get; set; }` — Local bundle cache directory
- L904 _public property_ `public string BundleCacheSize { get; set; }` — Max bundle cache size
- L907 _public property_ `public List<StorageNamespaceStatus> Namespaces { get; set; }` — Per-namespace status
- L910 _public property_ `public List<StorageBackendInfo> Backends { get; set; }` — Backend configurations

#### class `HordeServer.Storage.StorageNamespaceStatus`  
`public class StorageNamespaceStatus`  
_public; L916-944_
- desc: Per-namespace status information
- L919 _public property_ `public string Id { get; set; }` — Namespace ID
- L922 _public property_ `public string Backend { get; set; }` — Backend ID
- L925 _public property_ `public string Prefix { get; set; }` — Storage key prefix
- L928 _public property_ `public double GcFrequencyHrs { get; set; }` — Hours between GC sweeps
- L931 _public property_ `public double GcDelayHrs { get; set; }` — Grace period before deleting orphaned blobs (hours)
- L934 _public property_ `public long GcQueueDepth { get; set; }` — Current Redis GC queue depth
- L937 _public property_ `public bool IsPaused { get; set; }` — Whether ingestion is paused (queue at limit)
- L940 _public property_ `public DateTime? LastGcTime { get; set; }` — Time of last GC sweep
- L943 _public property_ `public bool EnableAliases { get; set; }` — Whether alias queries are enabled

#### class `HordeServer.Storage.StorageBackendInfo`  
`public class StorageBackendInfo`  
_public; L949-980_
- desc: Storage backend configuration info
- L952 _public property_ `public string Id { get; set; }` — Backend ID
- L955 _public property_ `public string Type { get; set; }` — Backend type (Aws, Azure, Gcs, FileSystem, Memory)
- L958 _public property_ `public string? BucketName { get; set; }` — S3 bucket name
- L961 _public property_ `public string? BucketPath { get; set; }` — S3 bucket path
- L964 _public property_ `public string? Region { get; set; }` — AWS region
- L967 _public property_ `public string? ContainerName { get; set; }` — Azure container name
- L970 _public property_ `public string? GcsBucketName { get; set; }` — GCS bucket name
- L973 _public property_ `public string? GcsBucketPath { get; set; }` — GCS bucket path
- L976 _public property_ `public string? BaseDir { get; set; }` — Filesystem base directory
- L979 _public property_ `public string? SecondaryBackend { get; set; }` — Secondary backend for migration

#### class `HordeServer.Storage.StorageDashboardGcMetrics`  
`public class StorageDashboardGcMetrics`  
_public; L985-989_
- desc: GC metric entries container
- L988 _public property_ `public List<StorageGcMetricEntry> Entries { get; set; }` — Metric entries

#### class `HordeServer.Storage.StorageGcMetricEntry`  
`public class StorageGcMetricEntry`  
_public; L994-1031_
- desc: Single GC metric entry (per-tick snapshot)
- L997 _public property_ `public DateTime Time { get; set; }` — Timestamp
- L1000 _public property_ `public string NamespaceId { get; set; }` — Namespace ID
- L1003 _public property_ `public long BlobsDeleted { get; set; }` — Blobs deleted in this tick
- L1006 _public property_ `public long BlobsChecked { get; set; }` — Blobs checked for reachability
- L1009 _public property_ `public long BytesFreed { get; set; }` — Bytes freed by deletion
- L1012 _public property_ `public long BlobsIngested { get; set; }` — Blobs ingested into GC queue
- L1015 _public property_ `public long QueueDepth { get; set; }` — Queue depth at recording time
- L1018 _public property_ `public double SweepDurationMs { get; set; }` — Sweep duration in milliseconds
- L1021 _public property_ `public bool WasPaused { get; set; }` — Whether namespace was paused
- L1024 _public property_ `public long EnqueueFailures { get; set; }` — Redis enqueue failures
- L1027 _public property_ `public long ThrottleEvents { get; set; }` — Queue backpressure events
- L1030 _public property_ `public long RefsExpired { get; set; }` — Refs expired and blobs queued for GC

#### class `HordeServer.Storage.StorageDashboardCollectionStats`  
`public class StorageDashboardCollectionStats`  
_public; L1036-1040_
- desc: Collection stats entries container
- L1039 _public property_ `public List<CollectionStatsSnapshotResponse> Entries { get; set; }` — Snapshot entries

#### class `HordeServer.Storage.CollectionStatsSnapshotResponse`  
`public class CollectionStatsSnapshotResponse`  
_public; L1045-1052_
- desc: A single collection stats snapshot in time
- L1048 _public property_ `public DateTime Time { get; set; }` — Snapshot timestamp
- L1051 _public property_ `public List<CollectionStatResponse> Collections { get; set; }` — Per-collection stats

#### class `HordeServer.Storage.CollectionStatResponse`  
`public class CollectionStatResponse`  
_public; L1057-1079_
- desc: Stats for a single MongoDB collection
- L1060 _public property_ `public string Name { get; set; }` — Collection name
- L1063 _public property_ `public long DocumentCount { get; set; }` — Number of documents
- L1066 _public property_ `public long DataSizeBytes { get; set; }` — Data size in bytes
- L1069 _public property_ `public long IndexSizeBytes { get; set; }` — Index size in bytes
- L1072 _public property_ `public long StorageSizeBytes { get; set; }` — Storage size in bytes
- L1075 _public property_ `public long AvgDocSizeBytes { get; set; }` — Average document size in bytes
- L1078 _public property_ `public double FragmentationRatio { get; set; }` — Fragmentation ratio (storageSize / dataSize)

### `Source/Programs/Horde/Plugins/Storage/HordeServer.Storage/Storage/StorageService.cs` (HordeServer.Storage)


#### interface `HordeServer.Storage.IStorageService`  
`public interface IStorageService : IStorageClient`  
_public; L38-40_
- inherits: `IStorageClient`
- desc: Interface for the storage service

#### class `HordeServer.Storage.StorageService`  
`public sealed class StorageService : IHostedService, IStorageService, IAsyncDisposable`  
_public; L45-1864_
- inherits: `IHostedService, IStorageService, IAsyncDisposable`
- desc: Functionality related to the storage service
- L300 _private* const_ `const int CurrentGcVersion = 2`
- L455 _private* field_ `readonly IRedisService _redisService`
- L456 _private* field_ `readonly IClock _clock`
- L457 _private* field_ `readonly BundleCache _bundleCache`
- L458 _private* field_ `readonly IMemoryCache _memoryCache`
- L459 _private* field_ `readonly IObjectStoreFactory _objectStoreFactory`
- L460 _private* field_ `readonly IOptionsMonitor<StorageConfig> _storageConfig`
- L461 _private* field_ `readonly IOptions<StorageServerConfig> _staticStorageConfig`
- L462 _private* field_ `readonly Tracer _tracer`
- L463 _private* field_ `readonly ILogger _logger`
- L465 _private* field_ `readonly Counter<long> _gcBlobsDeletedCounter`
- L466 _private* field_ `readonly Counter<long> _gcBlobsIngestedCounter`
- L467 _private* field_ `readonly Counter<long> _gcEnqueueFailuresCounter`
- L468 _private* field_ `readonly Counter<long> _gcTickThrottleEventsCounter`
- L469 _private* field_ `readonly Histogram<double> _gcReachabilityCheckDuration`
- L471 _private* field_ `readonly ConcurrentDictionary<NamespaceId, GcCounters> _gcCounters = ...`
- L471 _private* field_ `readonly ConcurrentDictionary< _gcCounters = new()`
- L509 _private* method_ `GcCounters GetOrAddCounters(NamespaceId ns)`
- L511 _private* field_ `readonly IMongoCollection<BlobInfo> _blobCollection`
- L512 _private* field_ `readonly IMongoCollection<RefInfo> _refCollection`
- L514 _private* field_ `readonly ITicker _blobTicker`
- L515 _private* field_ `readonly ITicker _refTicker`
- L517 _private* field_ `readonly SingletonDocument<GcState> _gcState`
- L518 _private* field_ `readonly ITicker _gcTicker`
- L520 _private* field_ `readonly SingletonDocument<LengthScanState> _lengthScanState`
- L521 _private* field_ `readonly ITicker _lengthScanTicker`
- L523 _private* field_ `readonly object _lockObject = new object()`
- L525 _private* field_ `string? _lastConfigRevision`
- L526 _private* field_ `State? _lastState`
- L528 _internal property_ `internal IMongoCollection<BlobInfo> BlobCollection => ...`
- L530 _private* field_ `static readonly FieldDefinition<BlobInfo, string> s_blobAliasField = ...`
- L530 _private* field_ `static readonly FieldDefinition< s_blobAliasField = new StringFieldDefinition<BlobInfo, string>($"{GetFieldName<BlobInfo>(x => x.Aliases)}.{GetFieldName<AliasInfo>(x => x.Name)}")`
- L542-545 _private* ctor_ `static StorageService()`
- L550-588 _public ctor_ `public StorageService(IMongoService mongoService, IRedisService redisService, IClock clock, BundleCache bundleCache, IMemoryCache memoryCache, IObjectStoreFactory objectStoreFactory, IOptionsMonitor<StorageConfig> storageConfig, IOptions<StorageServerConfig> staticStorageConfig, Tracer tracer, Meter meter, ILogger<StorageService> logger)` — Constructor
- L590-595 _private* method_ `static string GetFieldName<TClass>(Expression<Func<TClass, object?>> expr)`
- L598-604 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L606 _internal method_ `internal static ObjectKey GetObjectKey(BlobLocator locator)`
- L626 _public method_ `public IStorageClient CreateStorageClient(StorageConfig storageConfig)` — Creates a new storage namespace factory using the current global config value
- L630-636 _public method_ `public async Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L639-645 _public method_ `public async Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L648-651 _public method_ `public IStorageBackend CreateBackend(NamespaceId namespaceId)` — (inheritdoc)
- L654 _public method_ `public IStorageBackend? TryCreateBackend(NamespaceId namespaceId)` — (inheritdoc)
- L658-662 _public method_ `public IStorageBackend? TryCreateBackend(StorageConfig storageConfig, NamespaceId namespaceId)` — (inheritdoc)
- L665 _public method_ `public IStorageNamespace? TryGetNamespace(NamespaceId namespaceId)` — (inheritdoc)
- L669 _public method_ `public IStorageNamespace? TryCreateClient(NamespaceId namespaceId, BundleOptions? bundleOptions = null)` — (inheritdoc)
- L673-686 _public method_ `public IStorageNamespace? TryCreateClient(StorageConfig storageConfig, NamespaceId namespaceId, BundleOptions? bundleOptions = null)` — (inheritdoc)
- L690-727 _private* method_ `State CreateState(StorageConfig storageConfig)`
- L729-745 _private* method_ `IObjectStore CreateObjectStore(StorageConfig storageConfig, BackendId backendId)`
- L751-777 _internal method_ `internal async Task<BlobInfo> AddBlobAsync(NamespaceId namespaceId, BlobLocator locator, IReadOnlyCollection<BlobLocator> imports, List<AliasInfo>? exports = null, CancellationToken cancellationToken = default)`
- L779-856 _private* method_ `async Task<List<ObjectId>> FindOrAddShadowBlobsAsync(NamespaceId namespaceId, IReadOnlyCollection<BlobLocator> imports, CancellationToken cancellationToken = default)`
- L858-861 _internal method_ `internal async Task<BlobInfo?> GetBlobAsync(ObjectId id, CancellationToken cancellationToken = default)`
- L863-866 _internal method_ `internal async Task<BlobInfo?> FindBlobAsync(NamespaceId namespaceId, BlobLocator locator, CancellationToken cancellationToken = default)`
- L868-891 _private* method_ `async ValueTask CheckBlobExistsAsync(NamespaceId namespaceId, BlobLocator locator, CancellationToken cancellationToken)`
- L893-908 _private* method_ `async Task<bool> IsBlobReferencedAsync(ObjectId blobInfoId, CancellationToken cancellationToken = default)`
- L914-1046 _internal method_ `internal async ValueTask TickBlobsAsync(CancellationToken cancellationToken)` — Finds blobs at least 30 minutes old and computes import metadata for them. Done with a delay to allow write redirects.
- L1048-1072 _private* method_ `async Task DrainDeferredSetsAsync(GcState gcState, StorageConfig storageConfig, CancellationToken cancellationToken)`
- L1074-1089 _private* method_ `async Task<HashSet<NamespaceId>?> GetPausedNamespacesAsync(StorageConfig storageConfig, IEnumerable<BlobInfo> blobs, CancellationToken cancellationToken)`
- L1095-1155 _private* method_ `async Task AddAliasesAsync(NamespaceId namespaceId, IEnumerable<AddAliasRequest> addAliases, CancellationToken cancellationToken)`
- L1157-1215 _private* method_ `async Task RemoveAliasesAsync(NamespaceId namespaceId, IEnumerable<RemoveAliasRequest> removeAliases, CancellationToken cancellationToken)`
- L1224-1245 _private* method_ `async Task<List<(BlobLocator, AliasInfo)>> FindAliasesAsync(NamespaceId namespaceId, string name, CancellationToken cancellationToken = default)` — Finds nodes with the given type and hash
- L1261-1271 _private* method_ `RefCacheValue AddRefToCache(NamespaceId namespaceId, RefName name, RefInfo? value)` — Adds a ref value to the cache
- L1277-1315 _private* method_ `async ValueTask TickRefsAsync(CancellationToken cancellationToken)` — Expires any refs that are no longer valid
- L1318-1322 _private* method_ `async Task<bool> RemoveRefAsync(NamespaceId namespaceId, RefName name, CancellationToken cancellationToken = default)` — (inheritdoc)
- L1327-1331 _private* method_ `async Task RemoveExpiredRefAsync(RefInfo refDocument, CancellationToken cancellationToken = default)` — Deletes a ref document that has reached its expiry time
- L1333-1349 _private* method_ `async Task<bool> RemoveRefInternalAsync(NamespaceId namespaceId, RefName name, FilterDefinition<RefInfo> filter, CancellationToken cancellationToken = default)`
- L1352-1381 _private* method_ `async Task<RefInfo?> TryReadRefAsync(NamespaceId namespaceId, RefName name, RefCacheTime cacheTime = default, CancellationToken cancellationToken = default)` — (inheritdoc)
- L1384-1414 _private* method_ `async Task AddRefAsync(NamespaceId namespaceId, RefName name, HashedBlobRefValue value, RefOptions? options = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L1420 _private* method_ `uint GetGcTimestamp()`
- L1421 _private* method_ `static uint GetGcTimestamp(DateTime utcTime)`
- L1423 _private* method_ `static RedisKey GetRedisKey(string suffix)`
- L1424 _private* method_ `static RedisKey GetRedisKey(NamespaceId namespaceId, string suffix)`
- L1426 _private* method_ `static RedisSortedSetKey<ObjectId> GetGcCheckSet(NamespaceId namespaceId)`
- L1428 _private* method_ `static RedisKey GetDeferredScanSet(NamespaceId namespaceId)`
- L1435-1513 _private* method_ `async ValueTask TickGcAsync(CancellationToken cancellationToken)` — Find the next namespace to run GC on
- L1544-1598 _private* method_ `async Task TickGcForNamespaceAsync(NamespaceInfo namespaceInfo, ObjectId lastImportBlobInfoId, DateTime utcNow, CancellationToken cancellationToken)`
- L1601-1648 _private* method_ `async Task FindBlobsForReachabilityCheckAsync(NamespaceInfo namespaceInfo, ChannelWriter<SortedSetEntry<ObjectId>> writer, AsyncEvent queueChangeEvent, CancellationToken cancellationToken)`
- L1651-1713 _private* method_ `async ValueTask CheckReachabilityAsync(NamespaceInfo namespaceInfo, SortedSetEntry<ObjectId> entry, ObjectId lastImportBlobInfoId, GcSweepState state, StorageConfig storageConfig, AsyncEvent queueChangeEvent, CancellationToken cancellationToken)`
- L1715-1730 _private* method_ `static void SyncNamespaceList(GcState state, List<NamespaceConfig> namespaces)`
- L1732-1739 _private* method_ `void AddGcCheckRecord(NamespaceId namespaceId, ObjectId id, ObjectId lastImportBlobId)`
- L1744-1756 _public method_ `public Dictionary<NamespaceId, (long BlobsDeleted, long BlobsChecked, long BytesFreed, double SweepDurationMs, long BlobsIngested, long EnqueueFailures, long RefsExpired)> ReadAndResetGcCounters()` — Reads and resets accumulated GC counters for all namespaces
- L1761-1780 _public method_ `public async Task<(List<(NamespaceId Id, DateTime LastTime)> Namespaces, Dictionary<NamespaceId, long> QueueDepths)> GetGcStatusAsync(CancellationToken cancellationToken)` — Gets per-namespace GC status (last GC time, queue depth) for dashboard
- L1790-1802 _internal method_ `internal async ValueTask TickLengthsAsync(CancellationToken cancellationToken)` — Scan new blobs for their sizes
- L1804-1846 _private* method_ `async Task FindBlobsForLengthScanAsync(ChannelWriter<BlobInfo> writer, CancellationToken cancellationToken)`
- L1848-1861 _private* method_ `async ValueTask FindBlobLengthsAsync(BlobInfo blobInfo, State state, CancellationToken cancellationToken)`

#### class `HordeServer.Storage.StorageService.RefCount`  
`class RefCount`  
_private*; L47-54_
- L49 _private* field_ `int _value`
- L51 _public ctor_ `public RefCount()`
- L52 _public method_ `public void AddRef()`
- L53 _public method_ `public int Release()`

#### class `HordeServer.Storage.StorageService.StorageBackendImpl`  
`sealed class StorageBackendImpl : IStorageBackend`  
_private*; L56-232_
- inherits: `IStorageBackend`
- L58 _private* field_ `readonly StorageService _outer`
- L59 _private* field_ `readonly IObjectStore _store`
- L60 _private* field_ `readonly NamespaceConfig _config`
- L62 _public property_ `public NamespaceConfig Config => ...`
- L63 _public property_ `public NamespaceId NamespaceId => ...`
- L66 _public property_ `public bool SupportsRedirects { get; }` — (inheritdoc)
- L68-75 _public ctor_ `public StorageBackendImpl(StorageService outer, NamespaceConfig config, IObjectStore store)`
- L79-83 _public method_ `public async Task<Stream> OpenBlobAsync(BlobLocator locator, int offset, int? length, CancellationToken cancellationToken = default)`
- L86-90 _public method_ `public async Task<IReadOnlyMemoryOwner<byte>> ReadBlobAsync(BlobLocator locator, int offset, int? length, CancellationToken cancellationToken = default)` — (inheritdoc)
- L93-98 _public method_ `public async Task<BlobLocator> WriteBlobAsync(Stream stream, IReadOnlyCollection<BlobLocator> imports, string? basePath = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L101-105 _public method_ `public async Task WriteBlobAsync(BlobLocator locator, Stream stream, IReadOnlyCollection<BlobLocator> imports, CancellationToken cancellationToken = default)` — (inheritdoc)
- L108-112 _public method_ `public async ValueTask<Uri?> TryGetBlobReadRedirectAsync(BlobLocator locator, CancellationToken cancellationToken = default)` — (inheritdoc)
- L115-130 _public method_ `public async ValueTask<Uri?> TryGetBlobWriteRedirectAsync(BlobLocator locator, IReadOnlyCollection<BlobLocator> imports, CancellationToken cancellationToken = default)` — (inheritdoc)
- L133-149 _public method_ `public async ValueTask<(BlobLocator, Uri)?> TryGetBlobWriteRedirectAsync(IReadOnlyCollection<BlobLocator> imports, string? prefix = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L156-164 _public method_ `public async Task<BlobAliasLocator[]> FindAliasesAsync(string alias, int? maxResults, CancellationToken cancellationToken = default)` — (inheritdoc)
- L171-179 _public method_ `public async Task<HashedBlobRefValue?> TryReadRefAsync(RefName name, RefCacheTime cacheTime, CancellationToken cancellationToken)` — (inheritdoc)
- L182 _public method_ `public Task WriteRefAsync(RefName name, HashedBlobRefValue value, RefOptions? options = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L186 _public method_ `public Task<bool> DeleteRefAsync(RefName name, CancellationToken cancellationToken = default)` — (inheritdoc)
- L192-215 _public method_ `public async Task UpdateMetadataAsync(UpdateMetadataRequest request, CancellationToken cancellationToken = default)` — (inheritdoc)
- L217-228 _private* method_ `async ValueTask WrapAsync(Func<Task> func)`
- L231 _public method_ `public void GetStats(StorageStats stats)` — (inheritdoc)

#### class `HordeServer.Storage.StorageService.State`  
`class State`  
_private*; L234-253_
- L236 _public property_ `public StorageConfig Config { get; }`
- L237 _public property_ `public Dictionary<NamespaceId, NamespaceInfo> Namespaces { get; }`
- L239-242 _public ctor_ `public State(StorageConfig config)`
- L244-252 _public method_ `public IStorageBackend? TryCreateBackend(NamespaceId namespaceId)`

#### class `HordeServer.Storage.StorageService.NamespaceInfo`  
`class NamespaceInfo`  
_private*; L255-268_
- L257 _public property_ `public NamespaceId Id => ...`
- L258 _public property_ `public NamespaceConfig Config { get; }`
- L259 _public property_ `public IObjectStore Store { get; }`
- L260 _public property_ `public StorageBackendImpl Backend { get; }`
- L262-267 _public ctor_ `public NamespaceInfo(NamespaceConfig config, IObjectStore store, StorageBackendImpl backend)`

#### class `HordeServer.Storage.StorageService.AliasInfo`  
`internal class AliasInfo`  
_internal; L270-298_
- L273 _public property_ `public string Name { get; set; }` — attrs: `[BsonElement("nam")]`
- L276 _public property_ `public string Fragment { get; set; }` — attrs: `[BsonElement("frg")]`
- L279 _public property_ `public int Rank { get; set; }` — attrs: `[BsonElement("rnk"), BsonIgnoreIfDefault]`
- L282 _public property_ `public byte[]? Data { get; set; }` — attrs: `[BsonElement("dat"), BsonIgnoreIfNull]`
- L285-289 _public ctor_ `public AliasInfo()` — attrs: `[BsonConstructor]`
- L291-297 _public ctor_ `public AliasInfo(string name, string fragment, byte[]? data, int rank)`

#### class `HordeServer.Storage.StorageService.BlobInfo`  
`internal class BlobInfo`  
_internal; L302-344_
- L304 _public property_ `public ObjectId Id { get; set; }`
- L307 _public property_ `public NamespaceId NamespaceId { get; set; }` — attrs: `[BsonElement("ns")]`
- L310 _public property_ `public string Path { get; set; }` — attrs: `[BsonElement("blob")]`
- L313 _public property_ `public List<ObjectId>? Imports { get; set; }` — attrs: `[BsonElement("imp"), BsonIgnoreIfNull]`
- L316 _public property_ `public List<AliasInfo>? Aliases { get; set; }` — attrs: `[BsonElement("ali"), BsonIgnoreIfNull]`
- L319 _public property_ `public bool Shadow { get; set; }` — attrs: `[BsonElement("shd"), BsonIgnoreIfDefault]`
- L322 _public property_ `public int GcVersion { get; set; }` — attrs: `[BsonElement("del"), BsonIgnoreIfDefault]`
- L325 _public property_ `public long Length { get; set; }` — attrs: `[BsonElement("len"), BsonIgnoreIfDefault]`
- L328 _public property_ `public int? UpdateIndex { get; set; }` — attrs: `[BsonElement("idx"), BsonIgnoreIfDefault]`
- L331 _public property_ `public BlobLocator Locator => ...` — attrs: `[BsonIgnore]`
- L333-336 _public ctor_ `public BlobInfo()`
- L338-343 _public ctor_ `public BlobInfo(ObjectId id, NamespaceId namespaceId, BlobLocator locator)`

#### class `HordeServer.Storage.StorageService.RefInfo`  
`internal class RefInfo : ISupportInitialize`  
_internal; L346-409_
- inherits: `ISupportInitialize`
- L349 _public property_ `public ObjectId Id { get; set; }` — attrs: `[BsonIgnoreIfDefault]`
- L352 _public property_ `public NamespaceId NamespaceId { get; set; }` — attrs: `[BsonElement("ns")]`
- L355 _public property_ `public RefName Name { get; set; }` — attrs: `[BsonElement("name")]`
- L358 _public property_ `public IoHash Hash { get; set; }` — attrs: `[BsonElement("hash")]`
- L361 _public property_ `public BlobLocator Target { get; set; }` — attrs: `[BsonElement("tgt")]`
- L364 _public property_ `public ObjectId TargetBlobId { get; set; }` — attrs: `[BsonElement("binf")]`
- L367 _public property_ `public DateTime? ExpiresAtUtc { get; set; }` — attrs: `[BsonElement("xa"), BsonIgnoreIfDefault]`
- L370 _public property_ `public TimeSpan? Lifetime { get; set; }` — attrs: `[BsonElement("xt"), BsonIgnoreIfDefault]`
- L374 _private* property_ `BsonDocument? ExtraElements { get; set; }` — attrs: `[BsonExtraElements]`
- L378-381 _public ctor_ `public RefInfo()` — attrs: `[BsonConstructor]`
- L383-390 _public ctor_ `public RefInfo(NamespaceId namespaceId, RefName name, IoHash hash, BlobLocator target, ObjectId targetBlobId)`
- L392 _public method_ `public bool HasExpired(DateTime utcNow)`
- L394 _public method_ `public bool RequiresTouch(DateTime utcNow)`
- L396 _private* method_ `void ISupportInitialize.BeginInit()`
- L398-408 _private* method_ `void ISupportInitialize.EndInit()`

#### class `HordeServer.Storage.StorageService.GcState`  
`class GcState : SingletonBase`  
_private*; L412-434_
- attrs: `[SingletonDocument("gc-state")]`
- inherits: `SingletonBase`
- L414 _public property_ `public ObjectId LastImportBlobInfoId { get; set; }`
- L415 _public property_ `public List<GcNamespaceState> Namespaces { get; set; }`
- L416 _public property_ `public bool Reset { get; set; }`
- L418-422 _public method_ `public void DoReset()`
- L424-433 _public method_ `public GcNamespaceState FindOrAddNamespace(NamespaceId namespaceId)`

#### class `HordeServer.Storage.StorageService.LengthScanState`  
`class LengthScanState : SingletonBase`  
_private*; L437-447_
- attrs: `[SingletonDocument("length-scan-state")]`
- inherits: `SingletonBase`
- L439 _public property_ `public ObjectId LastImportBlobInfoId { get; set; }`
- L440 _public property_ `public bool Reset { get; set; }`
- L442-446 _public method_ `public void DoReset()`

#### class `HordeServer.Storage.StorageService.GcNamespaceState`  
`class GcNamespaceState`  
_private*; L449-453_
- L451 _public property_ `public NamespaceId Id { get; set; }`
- L452 _public property_ `public DateTime LastTime { get; set; }`

#### class `HordeServer.Storage.StorageService.GcCounters`  
`internal class GcCounters`  
_internal; L473-507_
- L475 _private* field_ `long _blobsDeleted`
- L476 _private* field_ `long _blobsChecked`
- L477 _private* field_ `long _bytesFreed`
- L478 _private* field_ `long _sweepDurationUs`
- L479 _private* field_ `long _blobsIngested`
- L480 _private* field_ `long _enqueueFailures`
- L481 _private* field_ `long _refsExpired`
- L483-489 _public method_ `public void AddSweep(long deleted, long checked_, long bytesFreed, double sweepMs)`
- L491 _public method_ `public void AddIngested(long count)`
- L492 _public method_ `public void AddEnqueueFailures(long count)`
- L493 _public method_ `public void AddRefsExpired(long count)`
- L495-506 _public method_ `public (long BlobsDeleted, long BlobsChecked, long BytesFreed, double SweepDurationMs, long BlobsIngested, long EnqueueFailures, long RefsExpired) ReadAndReset()`

#### class `HordeServer.Storage.StorageService.ObjectIdRedisConverter`  
`class ObjectIdRedisConverter : IRedisConverter<ObjectId>`  
_private*; L533-540_
- inherits: `IRedisConverter<ObjectId>`
- L535 _public method_ `public ObjectId FromRedisValue(RedisValue value)`
- L538 _public method_ `public RedisValue ToRedisValue(ObjectId value)`

#### class `HordeServer.Storage.StorageService.StorageClient`  
`class StorageClient : IStorageClient`  
_private*; L608-621_
- inherits: `IStorageClient`
- L610 _private* field_ `readonly StorageService _storageService`
- L611 _private* field_ `readonly StorageConfig _storageConfig`
- L613-617 _public ctor_ `public StorageClient(StorageService storageService, StorageConfig storageConfig)`
- L619 _public method_ `public IStorageNamespace? TryGetNamespace(NamespaceId namespaceId)`

#### record `HordeServer.Storage.StorageService.RefCacheKey`  
`record RefCacheKey(NamespaceId NamespaceId, RefName Name)`  
_private*; L1251-1251_

#### record `HordeServer.Storage.StorageService.RefCacheValue`  
`record RefCacheValue(RefInfo? Value, DateTime Time)`  
_private*; L1252-1252_

#### class `HordeServer.Storage.StorageService.GcSweepState`  
`class GcSweepState`  
_private*; L1515-1542_
- L1517 _private* field_ `long _score`
- L1518 _private* field_ `int _numItemsRemoved`
- L1519 _private* field_ `long _bytesFreed`
- L1520 _private* field_ `int _numItemsChecked`
- L1522 _public property_ `public int NumRemovedItems => ...`
- L1525 _public property_ `public long BytesFreed => ...`
- L1526 _public property_ `public int NumItemsChecked => ...`
- L1528 _public ctor_ `public GcSweepState(double score)`
- L1531 _public method_ `public double GetNextScore()`
- L1534-1538 _public method_ `public void OnRemovedItem(long length)`
- L1540 _public method_ `public void OnCheckedItem()`

### `Source/Programs/Horde/Plugins/Storage/HordeServer.Storage/StorageConfig.cs` (HordeServer.Storage)


#### class `HordeServer.Storage.Namespace`  
`public static class Namespace`  
_public; L26-32_
- desc: Well-known namespace identifiers
- L31 _public property_ `public static NamespaceId Logs { get; }` — Log data

#### class `HordeServer.Storage.StorageConfig`  
`public class StorageConfig : IPluginConfig`  
_public; L37-210_
- inherits: `IPluginConfig`
- desc: Configuration for storage
- L43 _public property_ `public AclConfig Acl { get; set; }` — attrs: `[JsonIgnore]` — ACL for the storage system
- L49 _public property_ `public string Revision { get; set; }` — attrs: `[JsonIgnore]` — Hash of the current object revision to allow detecting changes
- L54 _public property_ `public bool EnableGc { get; set; }` — Whether to enable garbage collection
- L59 _public property_ `public bool EnableGcVerification { get; set; }` — Whether to enable garbage collection in verification mode (nothing deleted, just logging on access to deleted blobs)
- L66 _public property_ `public int GcWorkerCount { get; set; }` — Number of concurrent GC reachability-check workers. Default 8. Reachability checks are I/O-bound (MongoDB queries), so higher values scale throughput roughly linearly up to the database's capacity.
- L72 _public property_ `public long GcQueueLimit { get; set; }` — Maximum number of entries in a namespace's Redis GC queue before the blob scanner pauses. Default 50,000.
- L79 _public property_ `public bool EnableReliableGcEnqueue { get; set; }` — Whether to await Redis writes when enqueuing blobs for GC checking. When false (default), uses fire-and-forget which can silently drop entries on Redis failures. Set true for reliable enqueue.
- L86 _public property_ `public bool EnablePerNamespaceQueueIsolation { get; set; }` — Whether to isolate GC queue limits per-namespace. When false (default), one backed-up namespace pauses the scanner for ALL namespaces. When true, only the backed-up namespace is paused and its blobs are deferred.
- L93 _public property_ `public int GcBlobIngestionBatchSize { get; set; }` — Number of blobs to process per blob-ingestion tick (TickBlobsAsync). Default 500. Raise to increase scan throughput when catching up on a backlog of unscanned blobs.
- L100 _public property_ `public int GcBatchSize { get; set; }` — Number of blob IDs to batch together for the import-reachability check. Default 1 (current per-blob behavior). When greater than 1, uses $in query to check multiple blobs in a single MongoDB round-trip. Values of 50-200 recommended.
- L105 _public property_ `public List<BackendConfig> Backends { get; set; }` — List of storage backends
- L110 _public property_ `public List<NamespaceConfig> Namespaces { get; set; }` — List of namespaces for storage
- L112 _private field_ `private readonly Dictionary<BackendId, BackendConfig> _backendLookup = ...`
- L112 _private field_ `private readonly Dictionary< _backendLookup = new Dictionary<BackendId, BackendConfig>()`
- L113 _private field_ `private readonly Dictionary<NamespaceId, NamespaceConfig> _namespaceLookup = ...`
- L113 _private field_ `private readonly Dictionary< _namespaceLookup = new Dictionary<NamespaceId, NamespaceConfig>()`
- L118-167 _public method_ `public void PostLoad(PluginConfigOptions configOptions)` — Called after the config has been read from disk
- L169-193 _private* method_ `static BackendConfig MergeBackendConfigs(BackendId backendId, Dictionary<BackendId, BackendConfig> baseIdToConfig, Dictionary<BackendId, BackendConfig> mergedIdToConfig)`
- L201 _public method_ `public bool TryGetBackend(BackendId backendId, [NotNullWhen(true)] out BackendConfig? backendConfig)` — Gets a backend with the given id
- L209 _public method_ `public bool TryGetNamespace(NamespaceId namespaceId, [NotNullWhen(true)] out NamespaceConfig? namespaceConfig)` — Gets a namespace with the given id

#### class `HordeServer.Storage.StorageServerConfig`  
`public class StorageServerConfig : PluginServerConfig`  
_public; L215-236_
- inherits: `PluginServerConfig`
- desc: Static settings for the storage system
- L220 _public property_ `public string? BundleCacheDir { get; set; }` — Directory to use for the coarse-grained backend cache. This caches full bundles downloaded from the upstream object store.
- L225 _public property_ `public string BundleCacheSize { get; set; }` — Maximum size of the storage cache on disk. Accepts standard binary suffixes (kb, mb, gb, tb, etc...)
- L230 _public property_ `public long BundleCacheSizeBytes => ...` — Accessor for the bundle cache size in bytes
- L235 _public property_ `public List<BackendConfig> Backends { get; set; }` — Overridden settings for storage backends. Useful for running against a production server with custom backends.

#### enum `HordeServer.Storage.StorageBackendType`  
`public enum StorageBackendType`  
_public; L241-267_
- desc: Types of storage backend to use
- L246 _public* enumerator_ `FileSystem` — Local filesystem
- L251 _public* enumerator_ `Aws` — AWS S3
- L256 _public* enumerator_ `Azure` — Azure blob store
- L261 _public* enumerator_ `Gcs` — Google Cloud Storage
- L266 _public* enumerator_ `Memory` — In-memory only (for testing)

#### class `HordeServer.Storage.BackendConfig`  
`public class BackendConfig : IAwsStorageOptions, IAzureStorageOptions, IGcsStorageOptions`  
_public; L273-353_
- attrs: `[DebuggerDisplay("{Id}")]`
- inherits: `IAwsStorageOptions, IAzureStorageOptions, IGcsStorageOptions`
- desc: Common settings object for different providers
- L279 _public property_ `public BackendId Id { get; set; }` — attrs: `[Required]` — The storage backend ID
- L284 _public property_ `public BackendId Base { get; set; }` — Base backend to copy default settings from
- L289 _public property_ `public BackendId Secondary { get; set; }` — Specifies another backend to read from if an object is not found in this one. Can be used when migrating data from one backend to another.
- L292 _public property_ `public StorageBackendType? Type { get; set; }` — (inheritdoc)
- L295 _public property_ `public string? BaseDir { get; set; }` — (inheritdoc)
- L298 _public property_ `public string? AwsBucketName { get; set; }` — (inheritdoc)
- L301 _public property_ `public string? AwsBucketPath { get; set; }` — (inheritdoc)
- L304 _public property_ `public AwsCredentialsType? AwsCredentials { get; set; }` — (inheritdoc)
- L307 _public property_ `public string? AwsRole { get; set; }` — (inheritdoc)
- L310 _public property_ `public string? AwsProfile { get; set; }` — (inheritdoc)
- L313 _public property_ `public string? AwsRegion { get; set; }` — (inheritdoc)
- L316 _public property_ `public string? AzureConnectionString { get; set; }` — (inheritdoc)
- L319 _public property_ `public string? AzureContainerName { get; set; }` — (inheritdoc)
- L322 _public property_ `public string? RelayServer { get; set; }` — (inheritdoc)
- L325 _public property_ `public string? RelayToken { get; set; }` — (inheritdoc)
- L328 _public property_ `public string? GcsBucketName { get; set; }` — (inheritdoc)
- L331 _public property_ `public string? GcsBucketPath { get; set; }` — (inheritdoc)
- L337 _internal property_ `internal IoHash Hash { get; set; }` — attrs: `[JsonIgnore]` — Hash of this backend config. Used for caching backend instances.
- L343-352 _public method_ `public void MergeDefaults(BackendConfig other)` — Merge default values from another object

#### class `HordeServer.Storage.NamespaceConfig`  
`public class NamespaceConfig`  
_public; L359-413_
- attrs: `[DebuggerDisplay("{Id}")]`
- desc: Configuration of a particular namespace
- L365 _public property_ `public NamespaceId Id { get; set; }` — attrs: `[Required]` — Identifier for this namespace
- L371 _public property_ `public BackendId Backend { get; set; }` — attrs: `[Required]` — Backend to use for this namespace
- L376 _public property_ `public string Prefix { get; set; }` — Prefix for items within this namespace
- L381 _public property_ `public double GcFrequencyHrs { get; set; }` — How frequently to run garbage collection, in hours.
- L386 _public property_ `public double GcDelayHrs { get; set; }` — How long to keep newly uploaded orphanned objects before allowing them to be deleted, in hours.
- L391 _public property_ `public bool EnableAliases { get; set; }` — Support querying exports by their aliases
- L396 _public property_ `public AclConfig Acl { get; set; }` — Access list for this namespace
- L401-404 _public method_ `public void PostLoad(AclConfig parentAcl)` — Callback once the configuration has been read from disk
- L411 _public method_ `public bool Authorize(AclAction action, ClaimsPrincipal user)` — Authorizes a user to perform a given action

### `Source/Programs/Horde/Plugins/Storage/HordeServer.Storage/StoragePlugin.cs` (HordeServer.Storage)


#### class `HordeServer.Storage.StoragePlugin`  
`public class StoragePlugin : IPluginStartup`  
_public; L20-70_
- attrs: `[Plugin("Storage", GlobalConfigType = typeof(StorageConfig), ServerConfigType = typeof(StorageServerConfig))]`
- inherits: `IPluginStartup`
- desc: Entry point for the storage plugin
- L22 _private* field_ `readonly IServerInfo _serverInfo`
- L23 _private* field_ `readonly StorageServerConfig _staticConfig`
- L28-32 _public ctor_ `public StoragePlugin(IServerInfo serverInfo, StorageServerConfig staticConfig)` — Constructor
- L35-36 _public method_ `public void Configure(IApplicationBuilder app)` — (inheritdoc)
- L39-62 _public method_ `public void ConfigureServices(IServiceCollection services)` — (inheritdoc)
- L64-69 _private* method_ `StorageBackendCache CreateStorageBackendCache(IServiceProvider serviceProvider)`

#### class `HordeServer.Storage.StoragePluginExtensions`  
`public static class StoragePluginExtensions`  
_public; L75-82_
- desc: Helper methods for storage config
- L80 _public method_ `public static void AddStorageConfig(this IDictionary<PluginName, IPluginConfig> dictionary, StorageConfig storageConfig)` — Configures the storage plugin
