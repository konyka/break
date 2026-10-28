# CSharp / HordeServer.Build

- project root: `Source/Programs/Horde/Plugins/Build/HordeServer.Build`
- files: 157; symbols: 5835
- symbol kinds: class=399, const=58, ctor=324, delegate=5, enum=10, enumerator=41, event=6, field=686, interface=80, method=1547, property=2637, record=25, record struct=12, struct=5
- access marked `*` is implicit (not written in source)

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Agents/AgentReportService.cs` (HordeServer.Build)


#### class `HordeServer.Agents.AgentReport`  
`public class AgentReport`  
_public; L17-28_
- desc: Report for the state of agents in the farm
- L22 _public property_ `public List<(AgentId, int)> ConformLoop { get; }` — List of agents stuck in a conform loop, plus the number of times they've attempted to conform
- L27 _public property_ `public List<(AgentId, int)> UpgradeLoop { get; }` — List of agents stuck in a upgrade loop, plus the number of times they've attempted to upgrade

#### class `HordeServer.Agents.AgentReportState`  
`class AgentReportState : SingletonBase`  
_internal*; L31-34_
- attrs: `[SingletonDocument("agent-report-state", "6268871c211d05611b3e4fd8")]`
- inherits: `SingletonBase`
- L33 _public property_ `public DateTime LastUpdateUtc { get; set; }`

#### class `HordeServer.Agents.AgentReportService`  
`public sealed class AgentReportService : IHostedService, IAsyncDisposable`  
_public; L39-114_
- inherits: `IHostedService, IAsyncDisposable`
- desc: Posts summaries for all the open issues in different streams to Slack channels
- L41 _private* field_ `readonly SingletonDocument<AgentReportState> _state`
- L42 _private* field_ `readonly IAgentCollection _agentCollection`
- L43 _private* field_ `readonly INotificationService _notificationService`
- L44 _private* field_ `readonly IClock _clock`
- L45 _private* field_ `readonly ITicker _ticker`
- L50-57 _public ctor_ `public AgentReportService(IMongoService mongoService, IAgentCollection agentCollection, INotificationService notificationService, IClock clock, ILogger<AgentReportService> logger)` — Constructor
- L60-63 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L66-69 _public method_ `public async Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L72-75 _public method_ `public async Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L77-113 _private* method_ `async ValueTask TickAsync(CancellationToken cancellationToken)`

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Agents/ConformList.cs` (HordeServer.Build)


#### class `HordeServer.Agents.ConformListEntry`  
`public class ConformListEntry`  
_public; L16-35_
- desc: Entry to the conform list
- L22 _public property_ `public AgentId AgentId { get; set; }` — attrs: `[BsonElement("a")]` — The agent id
- L28 _public property_ `public LeaseId LeaseId { get; set; }` — attrs: `[BsonElement("l")]` — The lease id
- L34 _public property_ `public DateTime? LastCheckTimeUtc { get; set; }` — attrs: `[BsonElement("t"), BsonIgnoreIfNull]` — Last timestamp that the lease was checked for validity

#### class `HordeServer.Agents.ConformListServer`  
`public class ConformListServer`  
_public; L40-56_
- desc: List of entries for a particular server
- L45 _public property_ `public string Cluster { get; set; }` — The perforce cluster
- L50 _public property_ `public string ServerAndPort { get; set; }` — The server and port
- L55 _public property_ `public List<ConformListEntry> Entries { get; set; }` — List of entries

#### class `HordeServer.Agents.ConformList`  
`public class ConformList : SingletonBase`  
_public; L62-73_
- attrs: `[SingletonDocument("conform-list", "60afc737f0d2a70754229300")]`
- inherits: `SingletonBase`
- desc: List of machines that are currently conforming
- L67 _public property_ `public List<ConformListEntry> Entries { get; set; }` — List of conforming servers [DEPRECATED]
- L72 _public property_ `public List<ConformListServer> Servers { get; set; }` — List of conforming servers

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Agents/Fleet/JobQueueStrategy.cs` (HordeServer.Build)


#### class `HordeServer.Agents.Fleet.JobQueueStrategy`  
`public class JobQueueStrategy : IPoolSizeStrategy`  
_public; L26-172_
- inherits: `IPoolSizeStrategy`
- desc: Calculate pool size by observing the number of jobs in waiting state Allows for more proactive scaling compared to LeaseUtilizationStrategy. LeaseUtilizationStrategy
- L28 _private const_ `private const string CacheKey = nameof(JobQueueStrategy)`
- L29 _internal property_ `internal JobQueueSettings Settings { get; }`
- L31 _private field_ `private readonly IJobCollection _jobs`
- L32 _private field_ `private readonly IGraphCollection _graphs`
- L33 _private field_ `private readonly IClock _clock`
- L34 _private field_ `private readonly IMemoryCache _cache`
- L35 _private field_ `private readonly bool _isDowntimeActive`
- L36 _private field_ `private readonly IOptionsMonitor<BuildConfig> _buildConfig`
- L41-50 _public ctor_ `public JobQueueStrategy(IJobCollection jobs, IGraphCollection graphs, IClock clock, IMemoryCache cache, bool isDowntimeActive, IOptionsMonitor<BuildConfig> buildConfig, JobQueueSettings? settings = null)` — Constructor
- L53 _public property_ `public string Name { get; }` — (inheritdoc)
- L62-99 _private method_ `private async Task<List<(IJob Job, IJobStepBatch Batch, PoolId PoolId)>> GetJobBatchesWithPoolsAsync(IJob job, Dictionary<StreamId, StreamConfig> streams, CancellationToken cancellationToken)` — Extract all job step batches from a job, with their associated pool
- L101-128 _internal method_ `internal async Task<Dictionary<PoolId, int>> GetPoolQueueSizesAsync(DateTimeOffset jobsCreatedAfter, CancellationToken cancellationToken = default)`
- L131-171 _public method_ `public async Task<PoolSizeResult> CalculatePoolSizeAsync(IPoolConfig pool, List<IAgent> agents, CancellationToken cancellationToken = default)` — (inheritdoc)

#### class `HordeServer.Agents.Fleet.JobQueueStrategyFactory`  
`class JobQueueStrategyFactory( IGraphCollection graphCollection, IJobCollection jobCollection, IDowntimeService downtimeService, IClock clock, IMemoryCache memoryCache, IOptionsMonitor<BuildConfig> buildConfig) : PoolSizeStrategyFactory<JobQueueSettings>(PoolSizeStrategy.JobQueue)`  
_internal*; L174-185_
- L183 _public method_ `public override IPoolSizeStrategy Create(JobQueueSettings settings)`

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Agents/Pools/PoolUpdateService.cs` (HordeServer.Build)


#### class `HordeServer.Agents.Pools.PoolUpdateService`  
`public sealed class PoolUpdateService : IHostedService, IAsyncDisposable`  
_public; L19-253_
- inherits: `IHostedService, IAsyncDisposable`
- desc: Periodically updates pool documents to contain the correct workspaces
- L21 _private* field_ `readonly AgentService _agentService`
- L22 _private* field_ `readonly PoolService _poolService`
- L23 _private* field_ `readonly IPoolCollection _pools`
- L24 _private* field_ `readonly IClock _clock`
- L25 _private* field_ `readonly IOptionsMonitor<BuildConfig> _buildConfig`
- L26 _private* field_ `readonly IOptionsMonitor<ComputeConfig> _computeConfig`
- L27 _private* field_ `readonly ILogger<PoolUpdateService> _logger`
- L28 _private* field_ `readonly Tracer _tracer`
- L29 _private* field_ `readonly ITicker _updatePoolsTicker`
- L30 _private* field_ `readonly ITicker _shutdownDisabledAgentsTicker`
- L31 _private* field_ `readonly ITicker _autoConformAgentsTicker`
- L36-49 _public ctor_ `public PoolUpdateService(AgentService agentService, PoolService poolService, IPoolCollection pools, IClock clock, IOptionsMonitor<BuildConfig> buildConfig, IOptionsMonitor<ComputeConfig> computeConfig, Tracer tracer, ILogger<PoolUpdateService> logger)` — Constructor
- L52-57 _public method_ `public async Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L60-65 _public method_ `public async Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L68-73 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L80-100 _internal method_ `internal async ValueTask ShutdownDisabledAgentsAsync(CancellationToken cancellationToken)` — Shutdown agents that have been disabled for longer than the configured grace period
- L102-117 _private method_ `private bool HasGracePeriodExpired(IAgent agent, IReadOnlyList<IPoolConfig> pools, TimeSpan? globalGracePeriod)`
- L119-124 _private method_ `private static TimeSpan? GetGracePeriod(IAgent agent, IReadOnlyList<IPoolConfig> pools)`
- L126-130 _private method_ `private static bool IsAgentAutoScaled(IAgent agent, IReadOnlyList<IPoolConfig> pools)`
- L137-147 _internal method_ `internal async ValueTask AutoConformAgentsAsync(CancellationToken cancellationToken)` — Find and conform any agents below the disk free conform threshold for a workspace
- L154-252 _internal method_ `internal async ValueTask UpdatePoolsAsync(CancellationToken cancellationToken)` — Execute the background task

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Artifacts/ArtifactAclAction.cs` (HordeServer.Build)


#### class `HordeServer.Artifacts.ArtifactAclAction`  
`public static class ArtifactAclAction`  
_public; L10-36_
- desc: ACL actions for artifacts
- L15 _public property_ `public static AclAction ReadArtifact { get; }` — Permission to read from an artifact
- L20 _public property_ `public static AclAction WriteArtifact { get; }` — Permission to write to an artifact
- L25 _public property_ `public static AclAction DeleteArtifact { get; }` — Permission to delete to an artifact
- L30 _public property_ `public static AclAction UploadArtifact { get; }` — Ability to create an artifact. Typically just for debugging; agents have this access for a particular session.
- L35 _public property_ `public static AclAction DownloadArtifact { get; }` — Ability to download an artifact

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Artifacts/ArtifactCollection.cs` (HordeServer.Build)


#### class `HordeServer.Artifacts.ArtifactCollection`  
`class ArtifactCollection : IArtifactCollection, IHostedService, IAsyncDisposable`  
_internal*; L29-475_
- inherits: `IArtifactCollection, IHostedService, IAsyncDisposable`
- desc: Implementation of IArtifactCollection
- L194 _private* field_ `readonly IMongoCollection<ArtifactDocument> _artifactCollection`
- L195 _private* field_ `readonly IMongoCollection<ArtifactExpiryDocument> _artifactExpiryCollection`
- L196 _private* field_ `readonly IClock _clock`
- L197 _private* field_ `readonly ICommitService _commitService`
- L198 _private* field_ `readonly IOptionsMonitor<BuildConfig> _buildConfig`
- L199 _private* field_ `readonly StorageService _storageService`
- L200 _private* field_ `readonly ITicker _ticker`
- L201 _private* field_ `readonly ILogger _logger`
- L206-225 _public ctor_ `public ArtifactCollection(IMongoService mongoService, IClock clock, ICommitService commitService, StorageService storageService, IOptionsMonitor<BuildConfig> buildConfig, ILogger<ArtifactCollection> logger)` — Constructor
- L228 _public method_ `public ValueTask DisposeAsync()` — (inheritdoc)
- L232 _public method_ `public async Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L236 _public method_ `public async Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L239-243 _private* method_ `IBlobRef<DirectoryNode> Open(Artifact artifact)`
- L246 _private* method_ `static string NormalizeKey(string key)`
- L253 _public method_ `public static string GetArtifactPath(StreamId streamId, ArtifactType type)` — Gets the base path for a set of artifacts
- L256-290 _public method_ `public async Task<IArtifactBuilder> CreateAsync(ArtifactName name, ArtifactType type, string? description, StreamId streamId, CommitId commitId, IEnumerable<string> keys, IEnumerable<string> metadata, CancellationToken cancellationToken = default)` — (inheritdoc)
- L292-297 _private* method_ `async Task AddExpiryRecordAsync(StreamId streamId, ArtifactType type, DateTime utcNow, CancellationToken cancellationToken = default)`
- L299-343 _public method_ `public async IAsyncEnumerable<IArtifact> FindAsync(ArtifactId[]? ids = null, StreamId? streamId = null, CommitId? minCommitId = null, CommitId? maxCommitId = null, ArtifactName? name = null, ArtifactType? type = null, IEnumerable<string>? keys = null, int maxResults = 100, [EnumeratorCancellation] CancellationToken cancellationToken = default)` — (inheritdoc)
- L345-390 _private* method_ `async ValueTask ExpireArtifactsAsync(CancellationToken cancellationToken)`
- L392-432 _private* method_ `async Task ExpireArtifactsForStreamAsync(StreamId streamId, ArtifactTypeConfig artifactTypeConfig, DateTime utcNow, CancellationToken cancellationToken)`
- L434-443 _private* method_ `async Task DeleteArtifactAsync(ArtifactDocument artifact, CancellationToken cancellationToken)`
- L445-460 _private* method_ `async Task DeleteArtifactsAsync(IEnumerable<ArtifactDocument> deleteArtifacts, CancellationToken cancellationToken)`
- L463-474 _public method_ `public async Task<IArtifact?> GetAsync(ArtifactId artifactId, CancellationToken cancellationToken = default)` — (inheritdoc)

#### class `HordeServer.Artifacts.ArtifactCollection.Artifact`  
`class Artifact : IArtifact`  
_private*; L31-61_
- inherits: `IArtifact`
- L33 _private* field_ `readonly ArtifactCollection _collection`
- L34 _private* field_ `readonly ArtifactDocument _document`
- L36 _public property_ `public ArtifactDocument Document => ...`
- L38 _public property_ `public ArtifactId Id => ...`
- L39 _private* property_ `ArtifactName IArtifact.Name => ...`
- L40 _private* property_ `ArtifactType IArtifact.Type => ...`
- L41 _private* property_ `string? IArtifact.Description => ...`
- L42 _private* property_ `StreamId IArtifact.StreamId => ...`
- L43 _private* property_ `CommitIdWithOrder IArtifact.CommitId => ...`
- L44 _private* property_ `IReadOnlyList<string> IArtifact.Keys => ...`
- L45 _private* property_ `IReadOnlyList<string> IArtifact.Metadata => ...`
- L46 _private* property_ `NamespaceId IArtifact.NamespaceId => ...`
- L47 _private* property_ `RefName IArtifact.RefName => ...`
- L48 _private* property_ `DateTime IArtifact.CreatedAtUtc => ...`
- L50 _private* property_ `IBlobRef<DirectoryNode> IArtifact.Content => ...`
- L53-57 _public ctor_ `public Artifact(ArtifactCollection collection, ArtifactDocument document)`
- L59 _public method_ `public Task DeleteAsync(CancellationToken cancellationToken)`

#### class `HordeServer.Artifacts.ArtifactCollection.ArtifactDocument`  
`class ArtifactDocument`  
_private*; L63-130_
- L66 _public property_ `public ObjectId Id { get; set; }` — attrs: `[BsonRequired, BsonId]`
- L69 _public property_ `public ArtifactName Name { get; set; }` — attrs: `[BsonElement("nam")]`
- L72 _public property_ `public ArtifactType Type { get; set; }` — attrs: `[BsonElement("typ")]`
- L75 _public property_ `public string? Description { get; set; }` — attrs: `[BsonElement("dsc"), BsonIgnoreIfNull]`
- L78 _public property_ `public StreamId StreamId { get; set; }` — attrs: `[BsonElement("str")]`
- L81 _public property_ `public string? CommitName { get; set; }` — attrs: `[BsonElement("com")]`
- L84 _public property_ `public int CommitOrder { get; set; }` — attrs: `[BsonElement("chg")]`
- L87-91 _public property_ `public CommitIdWithOrder CommitId { get; set; }` — attrs: `[BsonIgnore]`
- L94 _public property_ `public List<string> Keys { get; set; }` — attrs: `[BsonElement("key")]`
- L97 _public property_ `public List<string> Metadata { get; set; }` — attrs: `[BsonElement("met")]`
- L100 _public property_ `public NamespaceId NamespaceId { get; set; }` — attrs: `[BsonElement("ns")]`
- L103 _public property_ `public RefName RefName { get; set; }` — attrs: `[BsonElement("ref")]`
- L106 _public property_ `public DateTime CreatedAtUtc { get; set; }` — attrs: `[BsonElement("cre")]`
- L109 _public property_ `public int UpdateIndex { get; set; }` — attrs: `[BsonElement("upd")]`
- L112-114 _private ctor_ `private ArtifactDocument()` — attrs: `[BsonConstructor]`
- L116-129 _public ctor_ `public ArtifactDocument(ObjectId id, ArtifactName name, ArtifactType type, string? description, StreamId streamId, CommitIdWithOrder commitId, IEnumerable<string> keys, IEnumerable<string> metadata, NamespaceId namespaceId, RefName refName, DateTime createdAtUtc)`

#### class `HordeServer.Artifacts.ArtifactCollection.ArtifactExpiryDocument`  
`class ArtifactExpiryDocument`  
_private*; L132-144_
- L134 _public property_ `public ObjectId Id { get; set; }`
- L137 _public property_ `public StreamId StreamId { get; set; }` — attrs: `[BsonElement("str")]`
- L140 _public property_ `public ArtifactType Type { get; set; }` — attrs: `[BsonElement("typ")]`
- L143 _public property_ `public DateTime Time { get; set; }` — attrs: `[BsonElement("tim")]`

#### class `HordeServer.Artifacts.ArtifactCollection.ArtifactBuilder`  
`class ArtifactBuilder : IArtifactBuilder`  
_private*; L146-192_
- inherits: `IArtifactBuilder`
- L150 _private* field_ `readonly IArtifact _artifact`
- L151 _private* field_ `readonly IStorageNamespace _storage`
- L152 _private* field_ `readonly List<AliasInfo> _aliases = new List<AliasInfo>()`
- L154 _public property_ `public ArtifactId Id => ...`
- L155 _public property_ `public ArtifactName Name => ...`
- L156 _public property_ `public ArtifactType Type => ...`
- L157 _public property_ `public string? Description => ...`
- L158 _public property_ `public StreamId StreamId => ...`
- L159 _public property_ `public CommitIdWithOrder CommitId => ...`
- L160 _public property_ `public IReadOnlyList<string> Keys => ...`
- L161 _public property_ `public IReadOnlyList<string> Metadata => ...`
- L162 _public property_ `public NamespaceId NamespaceId => ...`
- L163 _public property_ `public RefName RefName => ...`
- L165-169 _public ctor_ `public ArtifactBuilder(Artifact artifact, IStorageNamespace storage)`
- L171-175 _public method_ `public Task AddAliasAsync(string name, IBlobRef handle, int rank = 0, ReadOnlyMemory<byte> data = default, CancellationToken cancellationToken = default)`
- L177-188 _public method_ `public async Task<IArtifact> CompleteAsync(IHashedBlobRef blobRef, CancellationToken cancellationToken = default)`
- L190 _public method_ `public IBlobWriter CreateBlobWriter()`

#### record `HordeServer.Artifacts.ArtifactCollection.ArtifactBuilder.AliasInfo`  
`record class AliasInfo(string Name, IBlobRef BlobRef, int Rank, ReadOnlyMemory<byte> Data)`  
_private*; L148-148_

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Artifacts/ArtifactTypeConfig.cs` (HordeServer.Build)


#### class `HordeServer.Artifacts.ArtifactTypeConfig`  
`public class ArtifactTypeConfig`  
_public; L12-56_
- desc: Configuration for an artifact
- L18-22 _public property_ `public ArtifactType Name { get; set; }` — attrs: `[Obsolete("Use Type instead")]` — Legacy 'Name' property
- L27 _public property_ `public ArtifactType Type { get; set; }` — Name of the artifact type
- L32 _public property_ `public AclConfig? Acl { get; set; }` — Acl for the artifact type
- L37 _public property_ `public int? KeepCount { get; set; }` — Number of artifacts to retain
- L42 _public property_ `public int? KeepDays { get; set; }` — Number of days to retain artifacts of this type
- L47 _public property_ `public NamespaceId NamespaceId { get; set; }` — Storage namespace to use for this artifact types
- L52-55 _public method_ `public void PostLoad(AclConfig parentAcl)` — Fixup an artifact type after reading the config

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Artifacts/ArtifactsController.cs` (HordeServer.Build)


#### class `HordeServer.Artifacts.ArtifactsController`  
`public class ArtifactsController : HordeControllerBase`  
_public; L43-946_
- attrs: `[Authorize] [ApiController]`
- inherits: `HordeControllerBase`
- desc: Public interface for artifacts
- L45 _private* field_ `readonly IArtifactCollection _artifactCollection`
- L46 _private* field_ `readonly StorageService _storageService`
- L47 _private* field_ `readonly ILeaseCollection _leaseCollection`
- L48 _private* field_ `readonly IJobCollection _jobCollection`
- L49 _private* field_ `readonly IAclService _aclService`
- L50 _private* field_ `readonly UnsyncCache _unsyncCache`
- L51 _private* field_ `readonly IBlockCache _blockCache`
- L52 _private* field_ `readonly IServerInfo _serverInfo`
- L53 _private* field_ `readonly BuildConfig _buildConfig`
- L54 _private* field_ `readonly ILogger _logger`
- L59-71 _public ctor_ `public ArtifactsController(IArtifactCollection artifactCollection, StorageService storageService, ILeaseCollection leaseCollection, IJobCollection jobCollection, IAclService aclService, UnsyncCache unsyncCache, IBlockCache blockCache, IServerInfo serverInfo, IOptionsSnapshot<BuildConfig> buildConfig, ILogger<ArtifactsController> logger)` — Constructor
- L81-144 _public method_ `public async Task<ActionResult<CreateArtifactResponse>> CreateArtifactAsync([FromBody] CreateArtifactRequest request, CancellationToken cancellationToken = default)` — attrs: `[HttpPost] [Route("/api/v2/artifacts")]` — Creates a new artifact. Actual data for the artifact can be uploaded using a storage namespace pointed to the blobs endpoint.
- L146-157 _private* method_ `async Task<ActionResult<CreateArtifactResponse>> CreateArtifactInternalAsync(ArtifactName name, ArtifactType type, string? description, StreamId streamId, CommitId commitId, List<string> keys, List<string> metadata, CancellationToken cancellationToken)`
- L159-181 _private* method_ `async Task<RefName?> GetPrevRefNameForArtifactAsync(IArtifactBuilder artifact, CancellationToken cancellationToken)`
- L199-211 _public method_ `public async Task<ActionResult<object>> FindArtifactsAsync([FromQuery(Name = "id")] ArtifactId[]? ids = null, [FromQuery] StreamId? streamId = null, [FromQuery] CommitId? minChange = null, [FromQuery] CommitId? maxChange = null, [FromQuery(Name = "name")] ArtifactName? name = null, [FromQuery(Name = "type")] ArtifactType? type = null, [FromQuery(Name = "key")] IEnumerable<string>? keys = null, [FromQuery] int maxResults = 100, [FromQuery] PropertyFilter? filter = null)` — attrs: `[HttpGet] [Route("/api/v2/artifacts")] [ProducesResponseType(typeof(FindArtifactsResponse), 200)]` — Finds artifacts matching certain criteria
- L222-235 _public method_ `public async Task<ActionResult<object>> GetArtifactAsync(ArtifactId id, [FromQuery] PropertyFilter? filter = null)` — attrs: `[HttpGet] [Route("/api/v2/artifacts/{id}")] [ProducesResponseType(typeof(GetArtifactResponse), 200)]` — Gets metadata about an artifact object
- L244-258 _public method_ `public async Task<ActionResult> DeleteArtifactAsync(ArtifactId id, CancellationToken cancellationToken)` — attrs: `[HttpDelete] [Route("/api/v2/artifacts/{id}")]` — Deletes an artifact object
- L269-287 _public method_ `public async Task<ActionResult> ReadArtifactBlobAsync(ArtifactId id, BlobLocator locator, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v2/artifacts/{id}/blobs/{*locator}")]` — Retrieves bundles for a particular artifact
- L297-310 _public method_ `public async Task<ActionResult<ReadRefResponse>> ReadArtifactRefAsync(ArtifactId id, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v2/artifacts/{id}/refs/default")]` — Retrieves the root blob for an artifact
- L324-371 _public method_ `public async Task<ActionResult<object>> BrowseArtifactAsync(ArtifactId id, [FromQuery] string? path = null, [FromQuery] string? search = null, [FromQuery] PropertyFilter? filter = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v2/artifacts/{id}/browse")] [ProducesResponseType(typeof(GetArtifactDirectoryResponse), 200)]` — Gets metadata about an artifact object
- L373-395 _private* method_ `static async Task ExpandDirectoriesAsync(DirectoryNode directoryNode, int depth, GetArtifactDirectoryResponse response, CancellationToken cancellationToken)`
- L397-401 _private* method_ `static async Task SearchDirectoriesAsync(DirectoryNode directoryNode, string search, GetArtifactDirectoryResponse response, CancellationToken cancellationToken)`
- L403-428 _private* method_ `static async Task SearchDirectoriesFullAsync(DirectoryNode directoryNode, string path, string search, GetArtifactDirectoryResponse response, CancellationToken cancellationToken)`
- L430-447 _private* method_ `static void FilterInlineResponses(int depth, GetArtifactDirectoryResponse response)`
- L449-465 _private* method_ `static bool IncludeInlineResponse(int depth, int numDirectories, int numFiles)`
- L476-479 _public method_ `public Task<ActionResult<object>> BrowseFileAsync(ArtifactId id, string path, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v2/artifacts/{id}/browse/{*path}")]` — Browse to an individual file from an artifact
- L491-534 _public method_ `public async Task<ActionResult<object>> GetFileAsync(ArtifactId id, [FromQuery] string path, [FromQuery] bool inline = false, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v2/artifacts/{id}/file")]` — Downloads an individual file from an artifact
- L546-549 _public method_ `public async Task<ActionResult<object>> DownloadAsync(ArtifactId id, [FromQuery] DownloadArtifactFormat? format, [FromQuery(Name = "filter")] string[]? filter, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v2/artifacts/{id}/download")]` — Downloads the artifact data
- L561-564 _public method_ `public async Task<ActionResult<object>> DownloadWithFilterAsync(ArtifactId id, [FromQuery] DownloadArtifactFormat? format, CreateZipRequest request, CancellationToken cancellationToken = default)` — attrs: `[HttpPost] [Route("/api/v2/artifacts/{id}/download")]` — Downloads an individual file from an artifact
- L566-587 _private* method_ `async Task<ActionResult> DownloadInternalAsync(ArtifactId id, DownloadArtifactFormat? format, IReadOnlyList<string>? fileFilter, CancellationToken cancellationToken)`
- L589-604 _private* method_ `async Task<ActionResult> GetZipInternalAsync(IArtifact artifact, IEnumerable<string>? fileFilter, CancellationToken cancellationToken)`
- L606-657 _private* method_ `ActionResult GetDescriptorInternal(IArtifact artifact, IReadOnlyList<string>? fileFilter)`
- L681-702 _public method_ `public async Task<ActionResult> GetUnsyncManifestAsync(ArtifactId id, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v2/artifacts/{id}/unsync")]` — Creates an Unsync manifest for an artifact
- L714-890 _public method_ `public async Task<ActionResult> GetUnsyncBlobsAsync(ArtifactId id, [FromBody] GetUnsyncDataRequest request, [FromQuery] bool compress = true, CancellationToken cancellationToken = default)` — attrs: `[HttpPost] [Route("/api/v2/artifacts/{id}/unsync-blobs")]` — Creates an Unsync manifest for an artifact
- L892 _private* method_ `static string GetUnsyncBlockKey(IoHash hash, bool compressed)`
- L895 _private* const_ `const int BlockHeaderSize = (sizeof(long) * 3) + IoHash.NumBytes`
- L897-909 _private* method_ `static void WriteBlockHeader(Span<byte> data, long compressedSize, IoHash decompressedHash, long decompressedSize)`
- L911-917 _private* method_ `static void WriteErrorHeader(ArrayMemoryWriter writer, string message)`
- L928-931 _public method_ `public async Task<ActionResult> GetZipAsync(ArtifactId id, [FromQuery(Name = "filter")] string[]? filter, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v2/artifacts/{id}/zip")]` — Downloads an individual file from an artifact
- L942-945 _public method_ `public async Task<ActionResult<object>> CreateZipFromFilterAsync(ArtifactId id, CreateZipRequest request, CancellationToken cancellationToken = default)` — attrs: `[HttpPost] [Route("/api/v2/artifacts/{id}/zip")]` — Downloads an individual file from an artifact

#### class `HordeServer.Artifacts.ArtifactsController.ManifestStreamResult`  
`class ManifestStreamResult : FileStreamResult`  
_private*; L659-672_
- inherits: `FileStreamResult`
- L661-664 _public ctor_ `public ManifestStreamResult(System.IO.Stream stream, string mimeType) : base(stream, mimeType)`
- L667-671 _public method_ `public override Task ExecuteResultAsync(ActionContext context)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Artifacts/BlockCache.cs` (HordeServer.Build)


#### record `HordeServer.Artifacts.BlockCacheStats`  
`public record class BlockCacheStats(int NumItems, int NumBlocks, int NumFreeBlocks, int BlockSize, long TotalSize, long UsedSize, long AllocatedSize)`  
_public; L20-20_
- desc: Stats for the cache

#### class `HordeServer.Artifacts.BlockCache`  
`public sealed class BlockCache : IBlockCache, IDisposable`  
_public; L25-497_
- inherits: `IBlockCache, IDisposable`
- desc: Implements a simple key-value cache using memory mapped files.
- L28 _private* const_ `const int PageSizeLog2 = 10`
- L29 _private* const_ `const int PageSize = 1 << PageSizeLog2`
- L32 _private* const_ `const int DefaultBlockSize = 32768`
- L35 _private* const_ `const int DefaultNumBlocksPerPartition = 32768`
- L38 _private* const_ `const int NumEvictionSamples = 10`
- L39 _private* const_ `const int NumEvictionEntries = 4`
- L184 _private* field_ `readonly Random _rng = new Random(0)`
- L185 _private* field_ `readonly Partition[] _partitions`
- L186 _private* field_ `readonly int _numBlocks`
- L187 _private* field_ `readonly int _numBlocksPerPartition`
- L188 _private* field_ `readonly int _numBlocksPerPartitionLog2`
- L189 _private* field_ `readonly int _blockSize`
- L190 _private* field_ `readonly int _blockSizeLog2`
- L191 _private* field_ `readonly ConcurrentDictionary<IoHash, BlockState> _lookup = ...`
- L191 _private* field_ `readonly ConcurrentDictionary< _lookup = new ConcurrentDictionary<IoHash, BlockState>()`
- L192 _private* field_ `readonly ConcurrentQueue<int> _freeBlocks = new ConcurrentQueue<int>()`
- L193 _private* field_ `readonly ILogger _logger`
- L195 _private* field_ `int _numAllocatedBlocks = 0`
- L204-222 _private* ctor_ `BlockCache(Partition[] partitions, int numBlocksPerPartition, int blockSize, ILogger? logger)` — Constructor
- L231-243 _public method_ `public static BlockCache CreateInMemory(int numPartitions, int numBlocksPerPartition = DefaultNumBlocksPerPartition, int blockSize = DefaultBlockSize, ILogger? logger = null)` — Creates a new cache from memory
- L253-274 _public method_ `public static BlockCache Create(DirectoryReference rootDir, int numPartitions, int numBlocksPerPartition = DefaultNumBlocksPerPartition, int blockSize = DefaultBlockSize, ILogger? logger = null)` — Create a new cache backed by files on disk
- L276 _private* method_ `static int GetPartitionSize(int numBlocks, int blockSize)`
- L279 _private* method_ `static int PageAlign(int value)`
- L283-289 _public method_ `public void Dispose()` — (inheritdoc)
- L294-314 _public method_ `public BlockCacheStats GetStats()` — Gets stats for the cache
- L316-356 _private* method_ `int GetNextFreeBlockIdx()`
- L358-372 _private* method_ `bool TryDelete(IoHash hash, BlockState blockState)`
- L374-379 _private* method_ `BlockHeader GetBlockHeader(int blockIdx)`
- L381-386 _private* method_ `void SetBlockHeader(int blockIdx, BlockHeader header)`
- L388-393 _private* method_ `Memory<byte> GetBlockData(int blockIdx, int blockLength)`
- L396-435 _public method_ `public bool Add(string key, ReadOnlyMemory<byte> value)` — (inheritdoc)
- L437-442 _private* method_ `static long ComputeDigest(ReadOnlySpan<byte> span)`
- L449-482 _public method_ `public IBlockCacheValue? Get(string key)` — Gets the data associated with a given key
- L487-496 _internal method_ `internal void DangerousCorruptValue(string key)` — Helper method for testing corruption handling

#### record struct `HordeServer.Artifacts.BlockCache.BlockHeader`  
`record struct BlockHeader(IoHash Key, uint PackedData, long Digest)`  
_private*; L42-68_
- L44 _public const_ `public const int NumBytes = 32`
- L46 _public property_ `public int Index => ...`
- L47 _public property_ `public int Count => ...`
- L48 _public property_ `public int Length => ...`
- L50-52 _public ctor_ `public BlockHeader(IoHash key, int index, int count, int length, long digest) : this(key, ((uint)index << 24) | ((uint)count << 16) | (uint)(length - 1), digest)`
- L54-60 _public method_ `public static BlockHeader Read(ReadOnlySpan<byte> data)`
- L62-67 _public method_ `public void Write(Span<byte> data)`

#### class `HordeServer.Artifacts.BlockCache.Partition`  
`class Partition : IDisposable`  
_private*; L70-87_
- inherits: `IDisposable`
- L72 _public property_ `public Memory<byte> BlockHeaders { get; }`
- L73 _public property_ `public Memory<byte> BlockData { get; }`
- L75-83 _public ctor_ `public Partition(int numBlocks, Memory<byte> data)`
- L85-86 _public method_ `public virtual void Dispose()`

#### class `HordeServer.Artifacts.BlockCache.MemoryMappedFilePartition`  
`class MemoryMappedFilePartition : Partition`  
_private*; L89-118_
- inherits: `Partition`
- L91 _private* field_ `readonly MemoryMappedFile _memoryMappedFile`
- L92 _private* field_ `readonly MemoryMappedView _memoryMappedView`
- L94-99 _private ctor_ `private MemoryMappedFilePartition(MemoryMappedFile memoryMappedFile, MemoryMappedView memoryMappedView, int numBlocks, Memory<byte> data) : base(numBlocks, data)`
- L101-109 _public method_ `public static MemoryMappedFilePartition Create(FileReference file, int numBlocks, int blockSize)`
- L111-117 _public method_ `public override void Dispose()`

#### class `HordeServer.Artifacts.BlockCache.BlockCacheValue`  
`class BlockCacheValue : IBlockCacheValue`  
_private*; L120-143_
- inherits: `IBlockCacheValue`
- L122 _private* field_ `ReadOnlySequence<byte> _data`
- L123 _private* field_ `BlockState? _state`
- L125-129 _public ctor_ `public BlockCacheValue(ReadOnlySequence<byte> data, BlockState state)`
- L131 _public property_ `public ReadOnlySequence<byte> Data => ...`
- L133-142 _public method_ `public void Dispose()`

#### class `HordeServer.Artifacts.BlockCache.BlockState`  
`class BlockState`  
_private*; L145-182_
- L147 _public property_ `public int[] BlockIdxs { get; }`
- L148 _public property_ `public long LastAccessTicks { get; set; }`
- L149 _public property_ `public int LastBlockLength { get; }`
- L151 _private* field_ `int _readerCount`
- L153-158 _public ctor_ `public BlockState(int[] blockIdxs, int lastBlockLength)`
- L160 _public method_ `public void Touch()`
- L163-175 _public method_ `public bool TryAddReadLock()`
- L177 _public method_ `public bool TryAddWriteLock()`
- L180 _public method_ `public void ReleaseReadLock()`

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Artifacts/IBlockCache.cs` (HordeServer.Build)


#### interface `HordeServer.Artifacts.IBlockCache`  
`public interface IBlockCache`  
_public; L10-26_
- desc: Implements a key/value cache store.
- L18 _public* method_ `bool Add(string key, ReadOnlyMemory<byte> value)` — Adds a new item to the cache
- L25 _public* method_ `IBlockCacheValue? Get(string key)` — Retrieves an item from the cache. If successful, the value must be disposed by the caller.

#### interface `HordeServer.Artifacts.IBlockCacheValue`  
`public interface IBlockCacheValue : IDisposable`  
_public; L31-37_
- inherits: `IDisposable`
- desc: Handle to a value in the block cache.
- L36 _public* property_ `ReadOnlySequence<byte> Data { get; }` — The underlying data

#### class `HordeServer.Artifacts.BlockCacheExtensions`  
`public static class BlockCacheExtensions`  
_public; L42-52_
- desc: Extension methods for IBlockCache
- L47-51 _public method_ `public static bool Contains(this IBlockCache blockCache, string key)` — Determines if the cache contains a particular key

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Artifacts/UnsyncCache.cs` (HordeServer.Build)


#### record `HordeServer.Artifacts.UnsyncManifest`  
`public record class UnsyncManifest(IReadOnlyList<UnsyncFile> Files)`  
_public; L20-20_
- desc: Manifest for Unsync

#### record `HordeServer.Artifacts.UnsyncFile`  
`public record class UnsyncFile(Utf8String Name, bool ReadOnly, bool Executable, long Length, DateTime ModTime, IReadOnlyList<UnsyncBlock> Blocks)`  
_public; L31-31_
- desc: Output file for an unsync manifest

#### record `HordeServer.Artifacts.UnsyncBlock`  
`public record class UnsyncBlock(long Offset, long Length, uint RollingHash, IHashedBlobRef<LeafChunkedDataNode> Blob)`  
_public; L40-40_
- desc: Describes a block of data in an unsync manifest

#### class `HordeServer.Artifacts.UnsyncCache`  
`public sealed class UnsyncCache : IDisposable`  
_public; L45-282_
- inherits: `IDisposable`
- desc: Implements a cache for downloading Unsync blobs
- L61 _private* field_ `readonly IStorageService _storageService`
- L62 _private* field_ `readonly MemoryCache _cache`
- L63 _private* field_ `readonly object _lockObject = new object()`
- L64 _private* field_ `readonly ILogger _logger`
- L69-74 _public ctor_ `public UnsyncCache(IStorageService storageService, ILogger<UnsyncCache> logger)` — Constructor
- L77 _public method_ `public void Dispose()` — (inheritdoc)
- L83-87 _public method_ `public async ValueTask<UnsyncManifest?> GetManifestAsync(IArtifact artifact, CancellationToken cancellationToken = default)` — Gets the manifest for an artifact
- L92-101 _public method_ `public async ValueTask<ReadOnlyMemory<byte>> GetManifestDataAsync(IArtifact artifact, CancellationToken cancellationToken = default)` — Gets the json manifest data for an artifact
- L103-127 _private* method_ `async Task<ArtifactInfo?> GetArtifactInfoAsync(IArtifact artifact, CancellationToken cancellationToken = default)`
- L129-181 _private* method_ `static byte[] SerializeManifest(UnsyncManifest manifest)`
- L190-205 _public method_ `public async ValueTask<IHashedBlobRef?> ReadBlobRefAsync(IArtifact artifact, IoHash blobHash, CancellationToken cancellationToken = default)` — Reads a blob from an artifact
- L207-233 _private* method_ `async Task<ArtifactInfo?> ReadArtifactAsync(IArtifact artifact, CancellationToken cancellationToken)`
- L235-264 _private* method_ `static async Task FindFilesAsync(Utf8StringBuilder path, IHashedBlobRef<DirectoryNode> directoryNodeRef, List<UnsyncFile> files, CancellationToken cancellationToken)`
- L266-281 _private* method_ `static async Task FindBlocksAsync(long offset, ChunkedDataNodeRef nodeRef, List<UnsyncBlock> blocks, CancellationToken cancellationToken)`

#### class `HordeServer.Artifacts.UnsyncCache.ArtifactInfo`  
`class ArtifactInfo`  
_private*; L47-59_
- L49 _public property_ `public UnsyncManifest Manifest { get; }`
- L50 _public property_ `public ReadOnlyMemory<byte> ManifestData { get; }`
- L51 _public property_ `public FrozenDictionary<IoHash, IHashedBlobRef<LeafChunkedDataNode>> Blobs { get; }`
- L53-58 _public ctor_ `public ArtifactInfo(UnsyncManifest manifest, ReadOnlyMemory<byte> manifestData, FrozenDictionary<IoHash, IHashedBlobRef<LeafChunkedDataNode>> blobs)`

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/BuildAclModifier.cs` (HordeServer.Build)


#### class `HordeServer.BuildAclModifier`  
`class BuildAclModifier : IDefaultAclModifier`  
_internal*; L19-50_
- inherits: `IDefaultAclModifier`
- L22-49 _public method_ `public void Apply(DefaultAclBuilder acl)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/BuildConfig.cs` (HordeServer.Build)


#### class `HordeServer.BuildConfig`  
`public class BuildConfig : IPluginConfig`  
_public; L38-501_
- inherits: `IPluginConfig`
- desc: Configuration for the build plugin
- L44 _public property_ `public AclConfig Acl { get; set; }` — attrs: `[JsonIgnore]` — Acl of this scope
- L49 _public property_ `public List<PerforceCluster> PerforceClusters { get; set; }` — List of Perforce clusters
- L54 _public property_ `public DeviceConfig? Devices { get; set; }` — Device configuration
- L59 _public property_ `public int MaxConformCount { get; set; }` — Maximum number of conforms to run at once
- L65 _public property_ `public TimeSpan? AgentShutdownIfDisabledGracePeriod { get; set; }` — Time to wait before shutting down an agent that has been disabled Used if no value is set on the actual pool.
- L71 _public property_ `public RoboMergeConfig? Robomerge { get; set; }` — RoboMerge branchmap file configuration for the merge graph service. When null or empty, the service is inert (no Perforce connections, no API data).
- L76 _public property_ `public List<ArtifactTypeConfig> ArtifactTypes { get; set; }` — Configuration for different artifact types
- L81 _public property_ `public List<ProjectConfig> Projects { get; set; }` — List of projects
- L87 _public property_ `public IReadOnlyList<StreamConfig> Streams { get; set; }` — attrs: `[JsonIgnore]` — Enumerates all the streams
- L92 _public property_ `public bool EnableConformTasks { get; set; }` — Whether to allow conform tasks to run
- L97 _public property_ `public bool EnableJobTaskConformCheck { get; set; }` — Whether to check if a conform is required on an agent before assigning a lease for a job task source.
- L102 _public property_ `public string IssueFixedTag { get; set; }` — Commit tag to use for marking issues as fixed
- L107 _public property_ `public IssueConfig? Issues { get; set; }` — Build health issue configurations
- L112 _public property_ `public bool EnableIssueRootCauseAnalysisNotifications { get; set; }` — Whether to allow notifications for Root Cause Analysis to be sent
- L118 _public property_ `public bool EnableAutoRcaSlackNotifications { get; set; }` — Global kill switch for posting auto-RCA results to Slack triage threads. When false (default), no auto-RCA Slack notifications are sent regardless of per-workflow AutoRcaSlackEnabled settings.
- L123 _public property_ `public bool AutoRcaUseMultiStage { get; set; }` — Whether to use multi-stage LLM analysis for auto-RCA. Multi-stage is slower but potentially more accurate. Set to false for faster processing with higher throughput.
- L129 _public property_ `public int MaxConcurrentRcaRequests { get; set; }` — Maximum number of concurrent auto-RCA requests. Limits load on the external LLM API. Set to 0 to disable auto-RCA globally (acts as a kill switch).
- L135 _public property_ `public IReadOnlyDictionary<string, string> IssueChannelGroups { get; set; }` — attrs: `[JsonIgnore]` — Issue channel groupings
- L140 _public property_ `public int IssueFindSuspectsMaxSuccessDays { get; set; }` — The maximum days since node success to scan for suspects
- L145 _public property_ `public int IssueFindSuspectsMaxScoringSeconds { get; set; }` — The maximum number of seconds to spend scording suspects
- L153 _public property_ `public int IssueFindSuspectsMaxChanges { get; set; }` — Maximum number of commits to examine for suspects. Previously hardcoded as const MaxChanges = 500.
- L159 _public property_ `public bool IssueFindSuspectsEnableParallelScoring { get; set; }` — Enable parallel scoring of commits for suspect finding. When enabled, commits are scored concurrently up to MaxParallelism.
- L165 _public property_ `public int IssueFindSuspectsMaxParallelism { get; set; }` — Maximum concurrent commit file lookups when parallel scoring is enabled. Higher values improve speed but increase Perforce server load.
- L171 _public property_ `public bool IssueFindSuspectsEnableEarlyExit { get; set; }` — Enable early exit when theoretical maximum score is achieved. Only exits early if the best possible score has been found.
- L177 _public property_ `public bool IssueFindSuspectsEnableBidirectionalQuery { get; set; }` — Enable bidirectional commit query to capture both recent and old commits. Queries half the limit from each end of the commit range.
- L183 _public property_ `public bool IssueFindSuspectsEnableFingerprintFallback { get; set; }` — Enable fingerprint-based fallback when no suspects are found. Helps prevent duplicate issues when commit range exceeds MaxChanges.
- L189 _public property_ `public int IssueFingerprintFallbackMinScore { get; set; }` — Minimum score required for fingerprint fallback matching. Higher values are more conservative (fewer false matches).
- L194 _public property_ `public int IssueFingerprintFallbackMaxAgeDays { get; set; }` — Maximum age in days for issues to be considered in fingerprint fallback.
- L199 _public property_ `public List<string> IssueFingerprintFallbackExcludedTypes { get; set; }` — Fingerprint types excluded from fallback matching (too generic).
- L208 _public property_ `public bool EnableExpandedIgnorePatterns { get; set; }` — Whether to enable expanded IgnorePatterns discovery (workspace-wide scanning + config-specified files). When false (default), only Engine directory is scanned for ignore patterns.
- L216 _public property_ `public List<string> LowContextFingerprintTypes { get; set; }` — Fingerprint type prefixes considered "low context" for suspect mention suppression. When an issue's fingerprint type starts with any of these prefixes AND all suspects are tied at rank 0, @ mentions are suppressed in Slack. Suspects are still listed without mentions. Set to an empty array to disable suppression entirely.
- L218 _private field_ `private readonly Dictionary<ProjectId, ProjectConfig> _projectLookup = ...`
- L218 _private field_ `private readonly Dictionary< _projectLookup = new Dictionary<ProjectId, ProjectConfig>()`
- L219 _private field_ `private readonly Dictionary<StreamId, StreamConfig> _streamLookup = ...`
- L219 _private field_ `private readonly Dictionary< _streamLookup = new Dictionary<StreamId, StreamConfig>()`
- L222-272 _public method_ `public void PostLoad(PluginConfigOptions configOptions)` — (inheritdoc)
- L274-336 _private* method_ `void UpdateWorkspacesForPools(IEnumerable<IPluginConfig> plugins)`
- L345-355 _public method_ `public bool Authorize(IJob? job, AclAction action, ClaimsPrincipal user)` — Determines if the user is authorized to perform an action on a particular stream
- L360-381 _public method_ `public bool AuthorizeArtifact(ArtifactType type, StreamId streamId, AclAction action, ClaimsPrincipal user)` — Authorize an action to perform on an artifact
- L383-387 _private* method_ `static bool? AuthorizeArtifactType(IReadOnlyList<ArtifactTypeConfig> artifactTypes, ArtifactType artifactType, AclAction action, ClaimsPrincipal user)`
- L395 _public method_ `public bool TryGetProject(ProjectId projectId, [NotNullWhen(true)] out ProjectConfig? config)` — Attempts to get configuration for a project from this object
- L402-410 _public method_ `public StreamConfig GetStream(StreamId streamId)` — Get configuration for a stream from this object
- L418 _public method_ `public bool TryGetStream(StreamId streamId, [NotNullWhen(true)] out StreamConfig? config)` — Attempts to get configuration for a stream from this object
- L427-435 _public method_ `public bool TryGetTemplate(StreamId streamId, TemplateId templateId, [NotNullWhen(true)] out TemplateRefConfig? config)` — Attempts to get configuration for a stream from this object
- L438 _public method_ `public bool Authorize(AclAction action, ClaimsPrincipal principal)` — (inheritdoc)
- L447-455 _public method_ `public PerforceCluster GetPerforceCluster(string? name, string? serverAndPort = null)` — Finds a perforce cluster with the given name or that contains the provided server
- L463-485 _public method_ `public PerforceCluster? FindPerforceCluster(string? name, string? serverAndPort = null)` — Finds a perforce cluster with the given name or that contains the provided server
- L487 _private* property_ `static List<PerforceCluster> DefaultClusters { get; }`
- L489-500 _private* method_ `static List<PerforceCluster> GetDefaultClusters()`

#### class `HordeServer.AutoSdkWorkspace`  
`public class AutoSdkWorkspace`  
_public; L506-528_
- desc: Path to a platform and stream to use for syncing AutoSDK
- L511 _public property_ `public string? Name { get; set; }` — Name of this workspace
- L516 _public property_ `public List<string> Properties { get; set; }` — The agent properties to check (eg. "OSFamily=Windows")
- L521 _public property_ `public string? UserName { get; set; }` — Username for logging in to the server
- L527 _public property_ `public string? Stream { get; set; }` — attrs: `[Required]` — Stream to use

#### class `HordeServer.PerforceServer`  
`public class PerforceServer`  
_public; L533-566_
- desc: Information about an individual Perforce server
- L540 _public property_ `public string ServerAndPort { get; set; }` — The server and port. The server may be a DNS entry with multiple records, in which case it will be actively load balanced. If "ssl:" prefix is used, ensure P4 server's fingerprint/certificate is trusted. See Horde's documentation on connecting to SSL-enabled Perforce servers.
- L545 _public property_ `public bool HealthCheck { get; set; }` — Whether to query the healthcheck address under each server
- L550 _public property_ `public bool ResolveDns { get; set; }` — Whether to resolve the DNS entries and load balance between different hosts
- L555 _public property_ `public int MaxConformCount { get; set; }` — Maximum number of simultaneous conforms on this server
- L560 _public property_ `public Condition? Condition { get; set; }` — Optional condition for a machine to be eligible to use this server
- L565 _public property_ `public List<string>? Properties { get; set; }` — List of properties for an agent to be eligible to use this server

#### class `HordeServer.PerforceCredentials`  
`public class PerforceCredentials`  
_public; L571-589_
- desc: Credentials for a Perforce user
- L576 _public property_ `public string UserName { get; set; }` — The username
- L582 _public property_ `public string? Password { get; set; }` — attrs: `[ResolveSecret]` — Password for the user
- L588 _public property_ `public string? Ticket { get; set; }` — attrs: `[ResolveSecret]` — Login ticket for the user (will be used instead of password if set)

#### class `HordeServer.PerforceCluster`  
`public class PerforceCluster`  
_public; L595-637_
- attrs: `[DebuggerDisplay("{Name}")]`
- desc: Information about a cluster of Perforce servers.
- L600 _public const_ `public const string DefaultName = "Default"` — The default cluster name
- L606 _public property_ `public string Name { get; set; }` — attrs: `[Required]` — Name of the cluster
- L611 _public property_ `public string? ServiceAccount { get; set; }` — Username for Horde to log in to this server. Will use the first account specified below if not overridden.
- L616 _public property_ `public bool CanImpersonate { get; set; }` — Whether the service account can impersonate other users
- L621 _public property_ `public bool SupportsPartitionedWorkspaces { get; set; }` — Whether to use partitioned workspaces on this server
- L626 _public property_ `public List<PerforceServer> Servers { get; set; }` — List of servers
- L631 _public property_ `public List<PerforceCredentials> Credentials { get; set; }` — List of server credentials
- L636 _public property_ `public List<AutoSdkWorkspace> AutoSdk { get; set; }` — List of autosdk streams

#### class `HordeServer.RoboMergeConfig`  
`public class RoboMergeConfig`  
_public; L642-663_
- desc: Configuration for the RoboMerge branchmap service
- L649 _public property_ `public List<string> BranchmapFiles { get; set; }` — Perforce depot paths to branchmap JSON files. Plain depot paths (e.g. "//MyProject/Main/Build/Streams/myproject.branchmap.json"). All files are read from the Perforce cluster specified by PerforceCluster.
- L656 _public property_ `public string PerforceCluster { get; set; }` — Perforce cluster name to connect to for reading branchmap files. Maps to a connection configured in BuildServerConfig.Perforce[]. Default: "default" (uses the default Perforce connection).
- L662 _public property_ `public TimeSpan TickInterval { get; set; }` — How often to poll Perforce for branchmap file changes. Default: 5 minutes. Changing this requires a server restart (ticker interval is set at construction time).

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/BuildHealth/BuildHealthFilterAclAction.cs` (HordeServer.Build)


#### class `HordeServer.Build.BuildHealth.BuildHealthFilterAclAction`  
`public static class BuildHealthFilterAclAction`  
_public; L10-16_
- desc: ACL Actions used for build health filters.
- L15 _public property_ `public static AclAction AddUpdateDeleteBuildHealthFilter { get; }` — Ability to add, update, and delete build health filters.

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/BuildHealth/BuildHealthFilterCollection.cs` (HordeServer.Build)


#### class `HordeServer.Build.BuildHealth.BuildHealthFilterCollection`  
`class BuildHealthFilterCollection : IBuildHealthFilterCollection`  
_internal*; L18-178_
- inherits: `IBuildHealthFilterCollection`
- desc: Build Health Filter Collection implementation.
- L22 _private* field_ `readonly IMongoCollection<BuildHealthFilterDocument> _buildHealthFilterDocuments`
- L23 _private* field_ `readonly ILogger<BuildHealthFilterCollection> _logger`
- L34-38 _public ctor_ `public BuildHealthFilterCollection(IMongoService mongoService, ILogger<BuildHealthFilterCollection> logger)` — Constructor.
- L45-57 _public method_ `public async Task<IBuildHealthFilter?> AddBuildHealthFilterAsync(UserId? owner, BuildHealthFilterAddRequest filterRequest, CancellationToken cancellationToken)` — (inheritdoc)
- L60-106 _public method_ `public async Task<IBuildHealthFilter?> UpdateBuildHealthFilterAsync(BuildHealthFilterId filterId, UserId? owner, BuildHealthFilterUpdateRequest filterRequest, CancellationToken cancellationToken)` — (inheritdoc)
- L109-115 _public method_ `public async Task<IBuildHealthFilter?> GetBuildHealthFilterAsync(BuildHealthFilterId filterId, CancellationToken cancellationToken)` — (inheritdoc)
- L118-128 _public method_ `public async Task<IEnumerable<IBuildHealthFilter>> GetBuildHealthFiltersAsync(ProjectId projectId, CancellationToken cancellationToken)` — (inheritdoc)
- L131-137 _public method_ `public async Task<bool> DeleteBuildHealthFilterAsync(BuildHealthFilterId filterId, UserId? owner, CancellationToken cancellationToken)` — (inheritdoc)

#### class `HordeServer.Build.BuildHealth.BuildHealthFilterCollection.BuildHealthFilterDocument`  
`class BuildHealthFilterDocument : IBuildHealthFilter`  
_private*; L146-175_
- inherits: `IBuildHealthFilter`
- desc: Build health filter document.
- L150 _public property_ `public BuildHealthFilterId Id { get; set; }` — attrs: `[BsonRequired, BsonId]` — (inheritdoc)
- L154 _public property_ `public string FilterName { get; set; }` — attrs: `[BsonElement("fn")]` — (inheritdoc)
- L158 _public property_ `public string? FilterDescription { get; set; }` — attrs: `[BsonElement("fd")]` — (inheritdoc)
- L162 _public property_ `public ProjectId FilterProject { get; set; }` — attrs: `[BsonElement("fp")]` — (inheritdoc)
- L166 _public property_ `public string FilterQuery { get; set; }` — attrs: `[BsonElement("fq")]` — (inheritdoc)
- L170 _public property_ `public UserId? Owner { get; set; }` — attrs: `[BsonElement("o")]` — (inheritdoc)
- L174 _public property_ `public DateTime UpdateTimeUtc { get; set; }` — attrs: `[BsonElement("ut")]` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/BuildHealth/BuildHealthFilterController.cs` (HordeServer.Build)


#### class `HordeServer.Build.BuildHealth.BuildHealthFilterController`  
`public class BuildHealthFilterController : HordeControllerBase`  
_public; L22-318_
- attrs: `[ApiController] [Authorize] [Route("[controller]")]`
- inherits: `HordeControllerBase`
- desc: Controller for build health filters.
- L27 _private* field_ `readonly IBuildHealthFilterCollection _buildHealthFilterCollection`
- L28 _private* field_ `readonly IUserCollection _userCollection`
- L29 _private field_ `private readonly IOptionsSnapshot<BuildConfig> _buildConfig`
- L41-46 _public ctor_ `public BuildHealthFilterController(IBuildHealthFilterCollection buildHealthFilterCollection, IUserCollection userCollection, IOptionsSnapshot<BuildConfig> buildConfig)` — Constructor.
- L62-103 _public method_ `public async Task<ActionResult<BuildHealthFilterResponse>?> AddBuildHealthFilterAsync([FromBody] BuildHealthFilterAddRequest filterUpdateRequest, CancellationToken cancellationToken = default)` — attrs: `[HttpPost] [Route("/api/v1/buildhealth/filters")] [ProducesResponseType(typeof(BuildHealthFilterResponse), 200)]` — Adds a new build health filter given the request.
- L116-167 _public method_ `public async Task<ActionResult<BuildHealthFilterResponse>?> UpdateBuildHealthFilterAsync(BuildHealthFilterId filterId, [FromBody] BuildHealthFilterUpdateRequest filterUpdateRequest, CancellationToken cancellationToken = default)` — attrs: `[HttpPut] [Route("/api/v1/buildhealth/filters/{filterId}")] [ProducesResponseType(typeof(BuildHealthFilterResponse), 200)]` — Updates the filter based off the request.
- L178-194 _public method_ `public async Task<ActionResult<BuildHealthFilterResponse>?> GetBuildHealthFilterAsync(BuildHealthFilterId filterId, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/buildhealth/filters/{filterId}")] [ProducesResponseType(typeof(BuildHealthFilterResponse), 200)]` — Gets filter with specific filter id.
- L205-224 _public method_ `public async Task<ActionResult<List<BuildHealthFilterResponse>>> GetBuildHealthFiltersAsync([FromQuery] ProjectId projectId, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/buildhealth/filters")] [ProducesResponseType(typeof(List<BuildHealthFilterResponse>), 200)]` — Gets all applicable filters given the filter criteria.
- L235-273 _public method_ `public async Task<ActionResult> DeleteBuildHealthFiltersAsync(BuildHealthFilterId filterId, CancellationToken cancellationToken = default)` — attrs: `[HttpDelete] [Route("/api/v1/buildhealth/filters/{filterId}")]` — Deletes a filter.
- L279-292 _private method_ `private async Task<BuildHealthFilterResponse> CreateBuildHealthFilterResponseWithOwnerAsync(IBuildHealthFilter filter, CancellationToken cancellationToken)`
- L299-315 _private method_ `private (bool isValidationSuccessful, ActionResult actionResult) VerifyAndAuthorizeProject(ProjectId projectId)` — Helper method to verify and authorize project.

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/BuildPlugin.cs` (HordeServer.Build)


#### class `HordeServer.BuildPlugin`  
`public class BuildPlugin : IPluginStartup`  
_public; L54-254_
- attrs: `[Plugin("Build", GlobalConfigType = typeof(BuildConfig), ServerConfigType = typeof(BuildServerConfig))]`
- inherits: `IPluginStartup`
- desc: Entry point for the build plugin
- L56 _private* field_ `readonly IServerInfo _serverInfo`
- L57 _private* field_ `readonly BuildServerConfig _staticConfig`
- L62-66 _public ctor_ `public BuildPlugin(IServerInfo serverInfo, BuildServerConfig staticConfig)` — Constructor
- L71-74 _private* ctor_ `static BuildPlugin()` — Static constructor
- L77-83 _public method_ `public void Configure(IApplicationBuilder app)` — (inheritdoc)
- L86-247 _public method_ `public void ConfigureServices(IServiceCollection services)` — (inheritdoc)
- L249-253 _private* method_ `BlockCache CreateBlockCache()`

#### class `HordeServer.BuildPluginExtensions`  
`public static class BuildPluginExtensions`  
_public; L259-290_
- desc: Helper methods for build config
- L264 _public method_ `public static void AddBuildConfig(this IDictionary<PluginName, IPluginConfig> dictionary, BuildConfig buildConfig)` — Configures the build plugin
- L270 _public method_ `public static BuildConfig GetBuildConfig(this IDictionary<PluginName, IPluginConfig> dictionary)` — Gets configuration for the build plugin
- L276-289 _public method_ `public static bool TryGetBuildConfig(this IDictionary<PluginName, IPluginConfig> dictionary, [NotNullWhen(true)] out BuildConfig? buildConfig)` — Gets configuration for the build plugin

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/BuildResponseFilter.cs` (HordeServer.Build)


#### class `HordeServer.BuildResponseFilter`  
`class BuildResponseFilter : IPluginResponseFilter`  
_internal*; L10-48_
- inherits: `IPluginResponseFilter`
- L12 _private* field_ `readonly BuildServerConfig _staticBuildConfig`
- L14-17 _public ctor_ `public BuildResponseFilter(IOptions<BuildServerConfig> staticBuildConfig)`
- L20-47 _public method_ `public void Apply(HttpContext context, object response)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/BuildServerConfig.cs` (HordeServer.Build)


#### class `HordeServer.BuildServerConfig`  
`public class BuildServerConfig : PluginServerConfig`  
_public; L16-177_
- inherits: `PluginServerConfig`
- desc: Static configuration for the build plugin
- L21 _public property_ `public List<PerforceConnectionSettings> Perforce { get; set; }` — Perforce connections for use by the Horde server (not agents)
- L26 _public property_ `public bool UseLocalPerforceEnv { get; set; }` — Whether to use the local Perforce environment
- L31 _public property_ `public int PerforceConnectionPoolSize { get; set; }` — Number of pooled perforce connections to keep
- L36 _public property_ `public bool EnableConformTasks { get; set; }` — Whether to enable the conform task source.
- L41 _public property_ `public Uri? P4SwarmUrl { get; set; }` — Url of P4 Swarm installation
- L46 _public property_ `public Uri? RobomergeUrl { get; set; }` — Url of Robomerge installation
- L51 _public property_ `public Uri? CommitsViewerUrl { get; set; }` — Url of Commits Viewer
- L56 _public property_ `public string? JiraUsername { get; set; }` — The Jira service account user name
- L61 _public property_ `public string? JiraApiToken { get; set; }` — The Jira service account API token
- L66 _public property_ `public Uri? JiraUrl { get; set; }` — The Uri for the Jira installation
- L71 _public property_ `public int SharedDeviceCheckoutDays { get; set; }` — The number of days shared device checkouts are held
- L76 _public property_ `public int DeviceProblemCooldownMinutes { get; set; }` — The number of cooldown minutes for device problems
- L81 _public property_ `public string? DeviceReportChannel { get; set; }` — Channel to send device reports to
- L86 _public property_ `public bool DisableBisection { get; set; }` — Whether to disable bisection tasks
- L91 _public property_ `public bool DisableSchedules { get; set; }` — Whether to run scheduled jobs.
- L96 _public property_ `public string? SlackToken { get; set; }` — Bot token for interacting with Slack (xoxb-*)
- L101 _public property_ `public string? SlackSocketToken { get; set; }` — Token for opening a socket to slack (xapp-*)
- L106 _public property_ `public string? SlackAdminToken { get; set; }` — Admin user token for Slack (xoxp-*). This is only required when using the admin endpoints to invite users.
- L111 _public property_ `public string? SlackUsers { get; set; }` — Filtered list of slack users to send notifications to. Should be Slack user ids, separated by commas.
- L116 _public property_ `public string SlackErrorPrefix { get; set; }` — Prefix to use when reporting errors
- L121 _public property_ `public string SlackWarningPrefix { get; set; }` — Prefix to use when reporting warnings
- L126 _public property_ `public string? ConfigNotificationChannel { get; set; }` — Channel for sending messages related to config update failures
- L131 _public property_ `public string? UpdateStreamsNotificationChannel { get; set; }` — Channel to send stream notification update failures to
- L136 _public property_ `public string? JobNotificationChannel { get; set; }` — Slack channel to send job related notifications to. Multiple channels can be specified, separated by ;
- L141 _public property_ `public string? AgentNotificationChannel { get; set; }` — Slack channel to send agent related notifications to.
- L146 _public property_ `public int TestDataRetainMonths { get; set; }` — The number of months to retain test data
- L151 _public property_ `public int TestHealthHistoryEvaluationDays { get; set; }` — The number of days to go back in historical data to evaluate test health
- L156 _public property_ `public int TestHealthReportRemindDays { get; set; }` — The number of days after which a test health report remind for improvement
- L161 _public property_ `public string? BlockCacheDir { get; set; }` — Directory to store the fine-grained block cache. This caches individual exports embedded in bundles.
- L166 _public property_ `public string BlockCacheSize { get; set; }` — Maximum size of the block cache. Accepts standard binary suffixes. Currently only allocates in multiples of 1024mb.
- L171 _public property_ `public long BlockCacheSizeBytes => ...` — Accessor for the block cache size in bytes
- L176 _public property_ `public CommitSettings Commits { get; set; }` — Options for the commit service

#### record struct `HordeServer.PerforceConnectionId`  
`public record struct PerforceConnectionId(StringId Id)`  
_public; L186-197_
- attrs: `[JsonSchemaString] [StringIdConverter(typeof(PerforceConnectionIdConverter))] [TypeConverter(typeof(StringIdTypeConverter<PerforceConnectionId, PerforceConnectionIdConverter>))]`
- desc: Identifier for a pool
- L191-193 _public ctor_ `public PerforceConnectionId(string id) : this(new StringId(id))` — Constructor
- L196 _public method_ `public override string ToString()` — (inheritdoc)

#### class `HordeServer.PerforceConnectionIdConverter`  
`class PerforceConnectionIdConverter : StringIdConverter<PerforceConnectionId>`  
_internal*; L202-209_
- inherits: `StringIdConverter<PerforceConnectionId>`
- desc: Converter to and from StringId instances.
- L205 _public method_ `public override PerforceConnectionId FromStringId(StringId id)` — (inheritdoc)
- L208 _public method_ `public override StringId ToStringId(PerforceConnectionId value)` — (inheritdoc)

#### class `HordeServer.PerforceConnectionSettings`  
`public class PerforceConnectionSettings`  
_public; L214-267_
- desc: Perforce connection information for use by the Horde server (for reading config files, etc...)
- L219 _public property_ `public static PerforceConnectionId Default { get; }` — Identifier for the default perforce connection profile
- L224 _public property_ `public PerforceConnectionId Id { get; set; }` — Identifier for this server
- L229 _public property_ `public string? ServerAndPort { get; set; }` — Server and port
- L234 _public property_ `public PerforceCredentials? Credentials { get; set; }` — Credentials for the server
- L240-266 _public method_ `public PerforceSettings ToPerforceSettings()` — Create a PerforceSettings object with these settings as overrides

#### class `HordeServer.CommitSettings`  
`public class CommitSettings`  
_public; L272-293_
- desc: Options for the commit service
- L277 _public property_ `public bool ReplicateMetadata { get; set; }` — Whether to mirror commit metadata to the database
- L282 _public property_ `public bool ReplicateContent { get; set; }` — Whether to mirror commit data to storage
- L287 _public property_ `public BundleOptions Bundle { get; set; }` — Options for how objects are packed together
- L292 _public property_ `public ChunkingOptions Chunking { get; set; }` — Options for how objects are sliced

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Commands/RelayCommand.cs` (HordeServer.Build)


#### class `HordeServer.Commands.RelayCommand`  
`class RelayCommand : Command`  
_internal*; L17-103_
- attrs: `[Command("relay", "Run server in relay mode")]`
- inherits: `Command`
- desc: Run server in relay mode
- L24 _public property_ `public string LogLevelStr { get; set; }` — attrs: `[CommandLine("-LogLevel")] [Description("Log verbosity level level (use Serilog levels such as debug, warning or information)")]` — Log verbosity level level (use Serilog levels such as debug, warning or information)
- L31 _public property_ `public string ClusterId { get; set; }` — attrs: `[CommandLine("-ClusterId=", Required = true)] [Description("Compute cluster ID this relay server belong to")]` — Compute cluster ID this relay server belong to
- L38 _public property_ `public string AgentId { get; set; }` — attrs: `[CommandLine("-ServerId=", Required = true)] [Description("Unique ID of this relay server instance (arbitrary string)")]` — Unique ID of this relay server instance (arbitrary string)
- L45 _public property_ `public string ServerUrl { get; set; }` — attrs: `[CommandLine("-ServerUrl=", Required = true)] [Description("gRPC URL to Horde server")]` — gRPC URL to Horde server
- L52 _public property_ `public string ListenIpsStr { get; set; }` — attrs: `[CommandLine("-ListenIps=", Required = true)] [Description("IP addresses this relay server can be addressed at. Multiple IPs are separated with comma.")]` — IP addresses this relay server can be addressed at. Multiple IPs are separated with comma.
- L59 _public property_ `public bool RunWithSudo { get; set; }` — attrs: `[CommandLine("-RunWithSudo=")] [Description("Whether to run 'nft' executable with sudo (true/false)")]` — Run 'nft' executable with sudo
- L64-66 _public ctor_ `public RelayCommand()` — Constructor
- L72-102 _public method_ `public override async Task<int> ExecuteAsync(ILogger logger)` — Runs the service indefinitely

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Commits/CommitService.cs` (HordeServer.Build)


#### class `HordeServer.Commits.CommitService`  
`public class CommitService : ICommitService`  
_public; L14-58_
- inherits: `ICommitService`
- desc: Provides commit information for streams
- L16 _private* field_ `readonly IOptionsMonitor<BuildConfig> _buildConfig`
- L18 _private* field_ `readonly Dictionary<string, IVersionControlService> _vcsServices = ...`
- L18 _private* field_ `readonly Dictionary< _vcsServices = new Dictionary<string, IVersionControlService>(StringComparer.OrdinalIgnoreCase)`
- L23-34 _public ctor_ `public CommitService(IEnumerable<IVersionControlService> versionControlServices, IOptionsMonitor<BuildConfig> buildConfig)` — Constructor
- L37-45 _public method_ `public ICommitCollection GetCollection(StreamConfig streamConfig)` — (inheritdoc)
- L48-57 _public method_ `public async ValueTask<CommitIdWithOrder> GetOrderedAsync(StreamId streamId, CommitId commitId, CancellationToken cancellationToken = default)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Commits/ICommitService.cs` (HordeServer.Build)


#### interface `HordeServer.Commits.ICommitService`  
`public interface ICommitService`  
_public; L12-29_
- desc: Provides information about commits to a stream
- L19 _public* method_ `ICommitCollection GetCollection(StreamConfig streamConfig)` — Gets a commit collection for the given stream
- L28 _public* method_ `ValueTask<CommitIdWithOrder> GetOrderedAsync(StreamId streamId, CommitId commitId, CancellationToken cancellationToken = default)` — Gets a numbered commit id

#### class `HordeServer.Commits.StreamNotFoundException`  
`public sealed class StreamNotFoundException : Exception`  
_public; L34-46_
- inherits: `Exception`
- desc: Exception thrown when a stream can't be found
- L39 _public property_ `public StreamId StreamId { get; }` — The stream identifier
- L44 _public ctor_ `public StreamNotFoundException(StreamId streamId) : base($"Stream {streamId} not found")` — Constructor

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Devices/DeviceAclAction.cs` (HordeServer.Build)


#### class `HordeServer.Devices.DeviceAclAction`  
`public static class DeviceAclAction`  
_public; L10-21_
- desc: ACL actions which apply to devices
- L15 _public property_ `public static AclAction DeviceRead { get; }` — Ability to read devices
- L20 _public property_ `public static AclAction DeviceWrite { get; }` — Ability to write devices

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Devices/DeviceCollection.cs` (HordeServer.Build)


#### class `HordeServer.Devices.DeviceCollection`  
`public class DeviceCollection : IDeviceCollection`  
_public; L23-1481_
- inherits: `IDeviceCollection`
- desc: Collection of device documents
- L454 _private* field_ `readonly IMongoCollection<DeviceDocument> _devices`
- L456 _private* field_ `readonly IMongoCollection<DeviceReservationDocument> _reservations`
- L458 _private* field_ `readonly IMongoCollection<DeviceTelemetryDocument> _deviceTelemetry`
- L460 _private* field_ `readonly IMongoCollection<DevicePoolTelemetryDocument> _poolTelemetry`
- L462 _private* field_ `readonly IUserCollection _userCollection`
- L464 _private* field_ `readonly IAuditLog<DeviceId> _auditLog`
- L465 _private* field_ `readonly ILogger<DeviceCollection> _logger`
- L470-486 _public ctor_ `public DeviceCollection(IMongoService mongoService, IUserCollection userCollection, ILogger<DeviceCollection> logger, IAuditLog<DeviceId> auditLog)` — Constructor
- L489-494 _public method_ `public async Task<IDevice?> TryAddDeviceAsync(DeviceId id, string name, DevicePlatformId platformId, DevicePoolId poolId, bool? enabled, string? address, string? modelId, UserId? userId, List<string>? tags = null)` — (inheritdoc)
- L497-515 _public method_ `public async Task<List<IDevice>> FindAllDevicesAsync(List<DeviceId>? deviceIds = null, DevicePoolId? poolId = null, DevicePlatformId? platformId = null)` — (inheritdoc)
- L518-521 _public method_ `public async Task<IDevice?> GetDeviceAsync(DeviceId deviceId)` — (inheritdoc)
- L524-527 _public method_ `public async Task<IDevice?> GetDeviceByNameAsync(string deviceName)` — (inheritdoc)
- L530-554 _public method_ `public async Task CheckoutDeviceAsync(DeviceId deviceId, UserId? checkedOutByUserId)` — (inheritdoc)
- L557-786 _public method_ `public async Task UpdateDeviceAsync(DeviceId deviceId, DevicePoolId? newPoolId, string? newName, string? newAddress, string? newModelId, string? newNotes, bool? newEnabled, bool? newProblem, bool? newMaintenance, UserId? modifiedByUserId = null, string? message = null, List<string>? newTags = null)` — (inheritdoc)
- L789-833 _public method_ `public async Task UpdateDeviceCleaningAsync(DeviceId deviceId, bool? cleaning = null, bool? cleanRequired = null)` — (inheritdoc)
- L836-841 _public method_ `public async Task<bool> DeleteDeviceAsync(DeviceId deviceId)` — (inheritdoc)
- L844-847 _public method_ `public async Task<IReadOnlyList<IDeviceReservation>> FindAllDeviceReservationsAsync(DevicePoolId? poolId = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L850-868 _public method_ `public async Task<IDeviceReservation?> TryFindReserveBlockAsync(JobId? jobId, JobStepId? stepId)` — (inheritdoc)
- L871-1148 _public method_ `public async Task<(IDeviceReservation?, bool)> TryAddReservationAsync(DevicePoolId poolId, List<DeviceRequestData> request, int problemCooldown, string? hostname, string? reservationDetails, IJob? job, JobStepId? stepId, string? stepName, List<JobStepId>? stepIds)` — (inheritdoc)
- L1151-1174 _public method_ `public async Task<IDeviceReservation?> TryUpdateReservationAsync(ObjectId id, DeviceId? problemDevice = null, List<DeviceId>? deviceIds = null, bool? clearProblemDevice = null)` — (inheritdoc)
- L1177-1187 _public method_ `public async Task<bool> DeleteReservationAsync(ObjectId id)` — (inheritdoc)
- L1192-1225 _public method_ `public async Task<List<(UserId, IDevice)>?> ExpireCheckedOutAsync(int checkoutDays)` — Deletes expired user checkouts
- L1230-1258 _public method_ `public async Task<List<(UserId, IDevice)>?> ExpireNotificatonsAsync(int checkoutDays)` — Gets a list of users to notify that their device is about to expire in the next 24 hours
- L1261-1265 _public method_ `public async Task<List<IDeviceReservation>> FindAllReservationsAsync()` — (inheritdoc)
- L1268-1271 _public method_ `public async Task<IDeviceReservation?> TryGetReservationAsync(ObjectId reservationId)` — (inheritdoc)
- L1274-1277 _public method_ `public async Task<IDeviceReservation?> TryGetReservationFromLegacyGuidAsync(string legacyGuid)` — (inheritdoc)
- L1280-1284 _public method_ `public async Task<IDeviceReservation?> TryGetDeviceReservationAsync(DeviceId id)` — (inheritdoc)
- L1287-1309 _public method_ `public async Task<List<IDeviceTelemetry>> FindDeviceTelemetryAsync(DeviceId[]? deviceIds = null, DateTimeOffset? minCreateTime = null, DateTimeOffset? maxCreateTime = null, int? index = null, int? count = null)` — (inheritdoc)
- L1326-1416 _public method_ `public async Task CreatePoolTelemetrySnapshotAsync(List<IDevicePool> pools, int problemCooldown)` — Create a device pool telemetry snapshot
- L1419-1436 _public method_ `public async Task<List<IDevicePoolTelemetry>> FindPoolTelemetryAsync(DateTimeOffset? minCreateTime = null, DateTimeOffset? maxCreateTime = null, int? index = null, int? count = null)` — (inheritdoc)
- L1439-1475 _public method_ `public async Task UpgradeAsync()` — (inheritdoc)
- L1477-1480 _private* method_ `IAuditLogChannel<DeviceId> GetDeviceLogger(DeviceId deviceId)`

#### class `HordeServer.Devices.DeviceCollection.DeviceReservationDocument`  
`class DeviceReservationDocument : IDeviceReservation`  
_private*; L29-120_
- inherits: `IDeviceReservation`
- desc: Document representing a reservation of devices
- L35 _public property_ `public ObjectId Id { get; set; }` — attrs: `[BsonRequired, BsonId]` — Randomly generated unique id for this reservation.
- L38 _public property_ `public DevicePoolId PoolId { get; set; }` — attrs: `[BsonRequired]`
- L41 _public property_ `public string? StreamId { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L44 _public property_ `public string? JobId { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L50 _public property_ `public string? StepId { get; set; }` — attrs: `[BsonIgnoreIfNull]` — Current Step Id
- L53 _public property_ `public string? JobName { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L56 _public property_ `public string? StepName { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L62 _public property_ `public UserId? UserId { get; set; }` — attrs: `[BsonIgnoreIfNull]` — Reservations held by a user, requires a token like download code
- L68 _public property_ `public string? Hostname { get; set; }` — attrs: `[BsonIgnoreIfNull]` — The hostname of the machine which has made the reservation
- L74 _public property_ `public string? ReservationDetails { get; set; }` — attrs: `[BsonIgnoreIfNull]` — Optional string holding details about the reservation
- L79 _public property_ `public List<DeviceId> Devices { get; set; }` — DeviceIds in the reservation
- L81 _public property_ `public List<string> RequestedDevicePlatforms { get; set; }`
- L83 _public property_ `public DateTime CreateTimeUtc { get; set; }`
- L85 _public property_ `public DateTime UpdateTimeUtc { get; set; }`
- L88 _public property_ `public string LegacyGuid { get; set; }`
- L91 _public property_ `public List<JobStepId>? ReservedStepIds { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L94 _public property_ `public DeviceId? ProblemDevice { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L97-100 _private ctor_ `private DeviceReservationDocument()` — attrs: `[BsonConstructor]`
- L102-119 _public ctor_ `public DeviceReservationDocument(ObjectId id, DevicePoolId poolId, List<DeviceId> devices, List<string> requestedDevicePlatforms, DateTime createTimeUtc, string? hostname, string? reservationDetails, string? streamId, string? jobId, string? stepId, string? jobName, string? stepName, List<JobStepId>? reservedStepIds)`

#### class `HordeServer.Devices.DeviceCollection.DeviceDocument`  
`class DeviceDocument : IDevice`  
_private*; L125-221_
- inherits: `IDevice`
- desc: Concrete implementation of an device document
- L127 _public field_ `public static int CurrentVersion = 1`
- L130 _public property_ `public DeviceId Id { get; set; }` — attrs: `[BsonRequired, BsonId]`
- L132 _public property_ `public DevicePlatformId PlatformId { get; set; }`
- L134 _public property_ `public DevicePoolId PoolId { get; set; }`
- L136 _public property_ `public string Name { get; set; }`
- L138 _public property_ `public bool Enabled { get; set; }`
- L141 _public property_ `public string? ModelId { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L144 _public property_ `public string? Address { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L147 _public property_ `public string? CheckedOutByUser { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L150 _public property_ `public DateTime? CheckOutTime { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L153 _public property_ `public bool? CheckoutExpiringNotificationSent { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L156 _public property_ `public DateTime? ProblemTimeUtc { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L159 _public property_ `public DateTime? MaintenanceTimeUtc { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L165 _public property_ `public DateTime? CleanStartTimeUtc { get; set; }` — attrs: `[BsonIgnoreIfNull]` — The time the last clean started,
- L171 _public property_ `public DateTime? CleanFinishTimeUtc { get; set; }` — attrs: `[BsonIgnoreIfNull]` — The time the least clean finished
- L177 _public property_ `public bool? CleanRequired { get; set; }` — attrs: `[BsonIgnoreIfNull]` — Whether a clean is required
- L183 _public property_ `public DateTime? ReservationTimeUtc { get; set; }` — attrs: `[BsonIgnoreIfNull]` — The last time this device was reserved, used to cycle devices for reservations
- L186 _public property_ `public string? ModifiedByUser { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L189 _public property_ `public string? Notes { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L195 _public property_ `public List<DeviceUtilizationTelemetry>? Utilization { get; set; }` — attrs: `[BsonIgnoreIfNull]` — [DEPRECATED]
- L198 _public property_ `public int? Version { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L201 _public property_ `public List<string>? Tags { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L204-206 _private ctor_ `private DeviceDocument()` — attrs: `[BsonConstructor]`
- L208-220 _public ctor_ `public DeviceDocument(DeviceId id, DevicePlatformId platformId, DevicePoolId poolId, string name, bool enabled, string? address, string? modelId, UserId? userId, List<string>? tags)`

#### class `HordeServer.Devices.DeviceCollection.DeviceTelemetryDocument`  
`class DeviceTelemetryDocument : IDeviceTelemetry`  
_private*; L226-320_
- inherits: `IDeviceTelemetry`
- desc: Device telemetry information for an individual device
- L232 _public property_ `public ObjectId TelemetryId { get; set; }` — attrs: `[BsonRequired, BsonId]` — Id of telemetry document
- L238 _public property_ `public DeviceId DeviceId { get; set; }` — attrs: `[BsonRequired, BsonElement("did")]` — The device id
- L244 _public property_ `public DateTime CreateTimeUtc { get; set; }` — attrs: `[BsonRequired, BsonElement("c")]` — The time this telemetry data was created
- L250 _public property_ `public string? StreamId { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("sid")]` — The stream id which utilized device
- L256 _public property_ `public string? JobId { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("job")]` — The job id which utilized device
- L262 _public property_ `public string? JobName { get; set; }` — attrs: `[BsonIgnoreIfNull]` — The job name
- L268 _public property_ `public string? StepId { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("step")]` — The job's step id
- L274 _public property_ `public string? StepName { get; set; }` — attrs: `[BsonIgnoreIfNull]` — The step name
- L280 _public property_ `public ObjectId? ReservationId { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("rid")]` — Reservation Id (transient, reservations are deleted upon expiration)
- L286 _public property_ `public DateTime? ReservationStartUtc { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("rs")]` — The time device was reserved
- L292 _public property_ `public DateTime? ReservationFinishUtc { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("rf")]` — The time device was freed
- L298 _public property_ `public DateTime? ProblemTimeUtc { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("p")]` — If the device reported a problem
- L301-303 _private ctor_ `private DeviceTelemetryDocument()` — attrs: `[BsonConstructor]`
- L305-319 _public ctor_ `public DeviceTelemetryDocument(DeviceId deviceId, ObjectId? reservationId = null, DateTime? reservationStartTime = null, string? streamId = null, string? jobId = null, string? stepId = null, string? jobName = null, string? stepName = null)`

#### class `HordeServer.Devices.DeviceCollection.DeviceReservationPoolTelemetryDocument`  
`class DeviceReservationPoolTelemetryDocument : IDevicePoolReservationTelemetry`  
_private*; L322-353_
- inherits: `IDevicePoolReservationTelemetry`
- L326 _public property_ `public DeviceId DeviceId { get; set; }` — attrs: `[BsonRequired, BsonElement("did")]` — (inheritdoc)
- L329 _public property_ `public string? JobId { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("ji")]`
- L332 _public property_ `public string? StepId { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("si")]`
- L335 _public property_ `public string? JobName { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("jn")]`
- L338 _public property_ `public string? StepName { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("sn")]`
- L341-343 _private ctor_ `private DeviceReservationPoolTelemetryDocument()` — attrs: `[BsonConstructor]`
- L345-352 _public ctor_ `public DeviceReservationPoolTelemetryDocument(DeviceId deviceId, string? jobId, string? stepId, string? jobName, string? stepName)`

#### class `HordeServer.Devices.DeviceCollection.DevicePlatformTelemetryDocument`  
`class DevicePlatformTelemetryDocument : IDevicePlatformTelemetry`  
_private*; L355-414_
- inherits: `IDevicePlatformTelemetry`
- L358 _public property_ `public DevicePlatformId PlatformId { get; set; }` — attrs: `[BsonRequired, BsonElement("pid")]`
- L361 _public property_ `public List<DeviceId>? Available { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("a")]`
- L362 _private* property_ `IReadOnlyList<DeviceId>? IDevicePlatformTelemetry.Available => ...`
- L365 _public property_ `public List<DeviceId>? Maintenance { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("m")]`
- L366 _private* property_ `IReadOnlyList<DeviceId>? IDevicePlatformTelemetry.Maintenance => ...`
- L369 _public property_ `public List<DeviceId>? Problem { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("p")]`
- L370 _private* property_ `IReadOnlyList<DeviceId>? IDevicePlatformTelemetry.Problem => ...`
- L373 _public property_ `public List<DeviceId>? Disabled { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("d")]`
- L374 _private* property_ `IReadOnlyList<DeviceId>? IDevicePlatformTelemetry.Disabled => ...`
- L377 _public property_ `public Dictionary<StreamId, List<DeviceReservationPoolTelemetryDocument>>? Reserved { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("r"), BsonDictionaryOptions(DictionaryRepresentation.ArrayOfDocuments)]`
- L378 _private* property_ `IReadOnlyDictionary<StreamId, IReadOnlyList<IDevicePoolReservationTelemetry>>? IDevicePlatformTelemetry.Reserved => ...`
- L381-383 _private ctor_ `private DevicePlatformTelemetryDocument()` — attrs: `[BsonConstructor]`
- L385-413 _public ctor_ `public DevicePlatformTelemetryDocument(DevicePlatformId platformId, List<DeviceId>? available, Dictionary<StreamId, List<DeviceReservationPoolTelemetryDocument>>? reserved, List<DeviceId>? maintenance, List<DeviceId>? problem, List<DeviceId>? disabled)`

#### class `HordeServer.Devices.DeviceCollection.DevicePoolTelemetryDocument`  
`class DevicePoolTelemetryDocument : IDevicePoolTelemetry`  
_private*; L419-452_
- inherits: `IDevicePoolTelemetry`
- desc: Device telemetry information for pools
- L425 _public property_ `public ObjectId TelemetryId { get; set; }` — attrs: `[BsonRequired, BsonId]` — Id of telemetry document
- L431 _public property_ `public DateTime CreateTimeUtc { get; set; }` — attrs: `[BsonRequired]` — The time this telemetry data was created
- L437 _public property_ `public Dictionary<DevicePoolId, List<DevicePlatformTelemetryDocument>> Pools { get; set; }` — attrs: `[BsonRequired]` — Pool platform state
- L439 _private* property_ `IReadOnlyDictionary<DevicePoolId, IReadOnlyList<IDevicePlatformTelemetry>> IDevicePoolTelemetry.Pools => ...`
- L442-444 _private ctor_ `private DevicePoolTelemetryDocument()` — attrs: `[BsonConstructor]`
- L446-451 _public ctor_ `public DevicePoolTelemetryDocument(Dictionary<DevicePoolId, List<DevicePlatformTelemetryDocument>> pools)`

#### struct `HordeServer.Devices.DeviceCollection.DevicePoolTelemetryHelper`  
`struct DevicePoolTelemetryHelper`  
_private*; L1311-1320_
- L1313 _public field_ `public List<DeviceId> _available = new List<DeviceId>()`
- L1314 _public field_ `public List<DeviceId> _problem = new List<DeviceId>()`
- L1315 _public field_ `public List<DeviceId> _maintenance = new List<DeviceId>()`
- L1316 _public field_ `public List<DeviceId> _disabled = new List<DeviceId>()`
- L1317 _public field_ `public Dictionary<StreamId, List<DeviceReservationPoolTelemetryDocument>> _reserved = ...`
- L1317 _public field_ `public Dictionary< _reserved = new Dictionary<StreamId, List<DeviceReservationPoolTelemetryDocument>>()`
- L1319 _public ctor_ `public DevicePoolTelemetryHelper()`

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Devices/DeviceConfig.cs` (HordeServer.Build)


#### class `HordeServer.Devices.DeviceConfig`  
`public class DeviceConfig`  
_public; L16-27_
- desc: Configuration for devices
- L21 _public property_ `public List<DevicePlatformConfig> Platforms { get; set; }` — List of device platforms
- L26 _public property_ `public List<DevicePoolConfig> Pools { get; set; }` — List of device pools

#### class `HordeServer.Devices.DevicePlatformConfig`  
`public class DevicePlatformConfig : IDevicePlatform`  
_public; L33-63_
- attrs: `[DebuggerDisplay("{Id}")]`
- inherits: `IDevicePlatform`
- desc: Configuration for a device platform
- L39 _public property_ `public DevicePlatformId Id { get; set; }` — attrs: `[Required]` — The id for this platform
- L45 _public property_ `public string Name { get; set; }` — attrs: `[Required]` — Name of the platform
- L50 _public property_ `public List<string>? Models { get; set; }` — A list of platform models
- L51 _private* property_ `IReadOnlyList<string>? IDevicePlatform.Models => ...`
- L56 _public property_ `public List<string>? LegacyNames { get; set; }` — Legacy names which older versions of Gauntlet may be using
- L57 _private* property_ `IReadOnlyList<string>? IDevicePlatform.LegacyNames => ...`
- L62 _public property_ `public string? LegacyPerfSpecHighModel { get; set; }` — Model name for the high perf spec, which may be requested by Gauntlet

#### class `HordeServer.Devices.DevicePoolConfig`  
`public class DevicePoolConfig : IDevicePool`  
_public; L69-94_
- attrs: `[DebuggerDisplay("{Id}")]`
- inherits: `IDevicePool`
- desc: Configuration for a device pool
- L75 _public property_ `public DevicePoolId Id { get; set; }` — attrs: `[Required]` — The id for this platform
- L81 _public property_ `public string Name { get; set; }` — attrs: `[Required]` — The name of the pool
- L88 _public property_ `public DevicePoolType PoolType { get; set; }` — attrs: `[Required] [JsonConverter(typeof(JsonStringEnumConverter))]` — The type of the pool
- L93 _public property_ `public List<ProjectId>? ProjectIds { get; set; }` — List of project ids associated with pool

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Devices/DeviceReportService.cs` (HordeServer.Build)


#### class `HordeServer.Devices.DeviceReport`  
`public class DeviceReport`  
_public; L18-73_
- L20 _public property_ `public string DeviceId { get; }`
- L21 _public property_ `public string DeviceName { get; }`
- L22 _public property_ `public string DeviceAddress { get; }`
- L24 _public property_ `public string PlatformId { get; }`
- L25 _public property_ `public string PlatformName { get; }`
- L27 _public property_ `public string PoolId { get; }`
- L28 _public property_ `public string PoolName { get; }`
- L33 _public property_ `public int ProblemDelta { get; set; }` — Problems reported since the last report
- L38 _public property_ `public int ProblemPercent { get; set; }` — Percent of reported problems against the number of reservation (rounded down)
- L43 _public property_ `public TimeSpan? CleaningTime { get; set; }` — Time elapse in cleaning
- L48 _public property_ `public string? LastProblemDesc { get; set; }` — The last problem Description
- L53 _public property_ `public string? LastProblemURL { get; set; }` — The last problem encountered
- L58 _public property_ `public string? DevicePoolURL { get; set; }` — The URL to the device on the pool view
- L60 _public property_ `public List<IDeviceTelemetry> Telemetry { get; }`
- L62-72 _public ctor_ `public DeviceReport(string platformId, string platformName, string deviceId, string deviceName, string deviceAddress, string poolId, string poolName, List<IDeviceTelemetry> telemetry)`

#### class `HordeServer.Devices.DevicePlatformReport`  
`public class DevicePlatformReport`  
_public; L75-86_
- L77 _public property_ `public string PlatformId { get; }`
- L78 _public property_ `public string PlatformName { get; }`
- L79 _public property_ `public List<DeviceReport> DeviceReports { get; set; }`
- L81-85 _public ctor_ `public DevicePlatformReport(string platformId, string platformName)`

#### class `HordeServer.Devices.DeviceUsageEvent`  
`public class DeviceUsageEvent`  
_public; L88-109_
- L93 _public property_ `public DateTime Start { get; }` — Start of the usage event.
- L97 _public property_ `public int Increment { get; }` — Increment(positive value) or decrement(negative value) usage, usually by one.
- L101 _public property_ `public bool HasProblem { get; }` — Whether a problem was reported during that event.
- L103-108 _public ctor_ `public DeviceUsageEvent(DateTime start, int increment, bool hasProblem = false)`

#### class `HordeServer.Devices.DevicePoolMetrics`  
`public class DevicePoolMetrics`  
_public; L111-187_
- L116 _public property_ `public string PlatformId { get; }` — Platform Id
- L120 _public property_ `public string PlatformName { get; }` — Platform Name
- L124 _public property_ `public string? PlatformURL { get; set; }` — The URL to the platform on the pool view
- L128 _public property_ `public int Total { get; set; }` — Number total of devices in the pool
- L132 _public property_ `public int Disabled { get; set; }` — Number of disabled devices in the pool
- L136 _public property_ `public int Maintenance { get; set; }` — Number of devices marked as Maintenance in the pool
- L140 _public property_ `public int Problems { get; set; }` — Total number of reported problems
- L144 _public property_ `public TimeSpan TotalReservationDuration { get; set; }` — Cumulated reservation duration in the pool
- L148 _public property_ `public int AverageLoadPercentage { get; set; }` — Percentage of the average load per device in the pool
- L152 _public property_ `public int SaturationSpikes { get; set; }` — Total number of pool saturation spikes
- L156 _public property_ `public TimeSpan SpikesDuration { get; set; }` — Cumulated duration of the saturation spikes
- L160 _public property_ `public TimeSpan SpikeDurationAverage { get; set; }` — Average duration a saturation spike
- L164 _public property_ `public int SpikeDurationPercentage { get; set; }` — Percentage of the cumulated spikes duration against the total reservation duration
- L168 _public property_ `public int MaxConcurrentProblems { get; set; }` — Maximum concurrent reported problems at any one time
- L172 _public property_ `public int MaxConcurrentProblemsPercentage { get; set; }` — Percentage of the maximum concurrent reported problems against the total number of available devices
- L176 _public property_ `public List<DeviceUsageEvent> UsageEvents { get; }` — Usage time series
- L180 _public property_ `public HashSet<string> Streams { get; }` — Collection of streams from which device reservation where made
- L182-186 _public ctor_ `public DevicePoolMetrics(string platformId, string platformName)`

#### class `HordeServer.Devices.DevicePoolReport`  
`public class DevicePoolReport`  
_public; L189-206_
- L191 _public property_ `public string PoolId { get; }`
- L192 _public property_ `public string PoolName { get; }`
- L194 _public property_ `public List<DevicePoolMetrics> Metrics { get; }`
- L199 _public property_ `public string? PoolURL { get; set; }` — The URL to the whole pool view
- L201-205 _public ctor_ `public DevicePoolReport(string poolId, string poolName)`

#### class `HordeServer.Devices.DeviceIssueReport`  
`public class DeviceIssueReport`  
_public; L208-220_
- L210 _public property_ `public string Channel { get; }`
- L212 _public property_ `public List<DevicePlatformReport> PlatformReports { get; set; }`
- L214 _public property_ `public List<DevicePoolReport> PoolReports { get; set; }`
- L216-219 _public ctor_ `public DeviceIssueReport(string channel)`

#### struct `HordeServer.Devices.DeviceReportData`  
`public struct DeviceReportData`  
_public; L222-228_
- L224 _public property_ `public List<IDevicePool> Pools { get; init; }`
- L225 _public property_ `public List<IDevicePlatform> Platforms { get; init; }`
- L226 _public property_ `public List<IDevice> Devices { get; init; }`
- L227 _public property_ `public List<IDeviceTelemetry> DeviceTelemetry { get; init; }`

#### struct `HordeServer.Devices.DeviceReportSettings`  
`public struct DeviceReportSettings`  
_public; L230-238_
- L232 _public property_ `public string Channel { get; init; }`
- L233 _public property_ `public int ReportMinutes { get; init; }`
- L234 _public property_ `public int DeviceProblemCoolDownMinutes { get; init; }`
- L235 _public property_ `public int DeviceSaturationSpikeThresholdMinutes { get; init; }`
- L236 _public property_ `public int DeviceCleaningThresholdHours { get; init; }`
- L237 _public property_ `public Uri ServerUrl { get; init; }`

#### class `HordeServer.Devices.DeviceReportState`  
`class DeviceReportState : SingletonBase`  
_internal*; L243-246_
- attrs: `[SingletonDocument("device-report-state", "6491bc0ce39f8b70b1ef2feb")]`
- inherits: `SingletonBase`
- L245 _public property_ `public DateTime ReportTime { get; set; }`

#### class `HordeServer.Devices.DeviceReportService`  
`public class DeviceReportService : IHostedService`  
_public; L251-563_
- inherits: `IHostedService`
- desc: Posts summaries for all the open issues in different streams to Slack channels
- L253 _private* field_ `readonly SingletonDocument<DeviceReportState> _state`
- L254 _private* field_ `readonly DeviceService _deviceService`
- L255 _private* field_ `readonly INotificationService _notificationService`
- L256 _private* field_ `readonly IClock _clock`
- L257 _private* field_ `readonly ITicker _ticker`
- L258 _private* field_ `readonly IServerInfo _serverInfo`
- L259 _private* field_ `readonly IOptions<BuildServerConfig> _staticBuildConfig`
- L260 _private* field_ `readonly ILogger<DeviceReportService> _logger`
- L262 _private* field_ `readonly int _reportIntervalMinutes = 12 * 60`
- L264 _private* field_ `readonly int _deviceProblemCoolDownMinutes = 10`
- L265 _private* field_ `readonly int _deviceSaturationSpikeThresholdMinutes = 10`
- L266 _private* field_ `readonly int _deviceCleaningThresholdHours = 6`
- L271-281 _public ctor_ `public DeviceReportService(IMongoService mongoService, DeviceService deviceService, INotificationService notificationService, IClock clock, IServerInfo serverInfo, IOptions<BuildServerConfig> staticBuildConfig, ILogger<DeviceReportService> logger)` — Constructor
- L284-287 _public method_ `public async Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L290-293 _public method_ `public async Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L295-353 _private* method_ `async ValueTask TickAsync(CancellationToken cancellationToken)`
- L355-562 _internal method_ `internal static DeviceIssueReport CreateDeviceReport(DeviceReportData deviceData, DeviceReportSettings settings)`

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Devices/DeviceService.cs` (HordeServer.Build)


#### class `HordeServer.Devices.DevicePoolAuthorization`  
`public class DevicePoolAuthorization`  
_public; L29-58_
- desc: Device Pool Authorization (convenience class for pool ACL's)
- L34 _public property_ `public IDevicePool Pool { get; set; }` — The device pool
- L39 _public property_ `public bool Read { get; set; }` — Read access to pool
- L44 _public property_ `public bool Write { get; set; }` — Write access to pool
- L52-57 _public ctor_ `public DevicePoolAuthorization(IDevicePool pool, bool read, bool write)` — Constructor

#### class `HordeServer.Devices.DeviceService`  
`public sealed class DeviceService : IHostedService, IAsyncDisposable`  
_public; L63-843_
- inherits: `IHostedService, IAsyncDisposable`
- desc: Device management service
- L65 _private* field_ `readonly INotificationService _notificationService`
- L66 _private* field_ `readonly JobService _jobService`
- L67 _private* field_ `readonly IUserCollection _userCollection`
- L68 _private* field_ `readonly Tracer _tracer`
- L69 _private* field_ `readonly ILogger<DeviceService> _logger`
- L70 _private* field_ `readonly IDeviceCollection _devices`
- L71 _private* field_ `readonly ITicker _ticker`
- L72 _private* field_ `readonly ITicker _telemetryTicker`
- L73 _private* field_ `readonly IServerInfo _serverInfo`
- L74 _private* field_ `readonly IAuditLog<DeviceId> _auditLog`
- L75 _private* field_ `readonly IOptionsMonitor<BuildServerConfig> _settings`
- L76 _private* field_ `readonly IOptionsMonitor<BuildConfig> _buildConfig`
- L78 _private* field_ `bool _runUpgrade = true`
- L83 _public property_ `public int SharedDeviceCheckoutDays => ...` — The number of days shared device sheckouts are held
- L88-102 _public ctor_ `public DeviceService(IDeviceCollection devices, IUserCollection userCollection, JobService jobService, IServerInfo serverInfo, IOptionsMonitor<BuildServerConfig> settings, IOptionsMonitor<BuildConfig> buildConfig, INotificationService notificationService, IClock clock, Tracer tracer, ILogger<DeviceService> logger, IAuditLog<DeviceId> auditLog)` — Device service constructor
- L105-109 _public method_ `public async Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L112-116 _public method_ `public async Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L119-123 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L130-133 _public method_ `public IAuditLogChannel<DeviceId> GetDeviceLogger(DeviceId deviceId)` — Get the logger for the specified device id
- L138-146 _private* method_ `async ValueTask TickTelemetryAsync(CancellationToken stoppingToken)` — Ticks service
- L151-211 _private* method_ `async ValueTask TickAsync(CancellationToken cancellationToken)` — Ticks service
- L213-217 _internal method_ `internal async Task TickForTestingAsync()`
- L219-259 _private* method_ `static bool CheckReservedNodesComplete(IJob job, List<JobStepId> reservedStepIds)`
- L261-304 _private* method_ `async Task<bool> ExpireReservationsAsync(CancellationToken cancellationToken)`
- L309-312 _public method_ `public List<IDevicePlatform> GetPlatforms()` — Get a list of existing device platforms
- L316-319 _public method_ `public IDevicePlatform? GetPlatform(DevicePlatformId id)` — Get a specific device platform
- L324-327 _public method_ `public IDevicePool? GetPool(DevicePoolId id)` — Get a device pool by id
- L332-335 _public method_ `public List<IDevicePool> GetPools()` — Get a list of existing device pools
- L340-343 _public method_ `public async Task<List<IDevice>> GetDevicesAsync(List<DeviceId>? deviceIds = null, DevicePoolId? poolId = null, DevicePlatformId? platformId = null)` — Get a list of devices, optionally filtered to provided ids
- L348-351 _public method_ `public async Task<List<IDeviceTelemetry>> GetDeviceTelemetryAsync(DeviceId[]? deviceIds = null, DateTimeOffset? minCreateTime = null, DateTimeOffset? maxCreateTime = null, int? index = null, int? count = null)` — Get device telemetry
- L356-359 _public method_ `public async Task<List<IDevicePoolTelemetry>> GetDevicePoolTelemetryAsync(DateTimeOffset? minCreateTime = null, DateTimeOffset? maxCreateTime = null, int? index = null, int? count = null)` — Get device pool telemetry
- L364-367 _public method_ `public async Task<IDevice?> GetDeviceAsync(DeviceId id)` — Get a specific device
- L372-375 _public method_ `public async Task<IDevice?> GetDeviceByNameAsync(string deviceName)` — Get a device by name
- L380-383 _public method_ `public async Task<bool> DeleteDeviceAsync(DeviceId id)` — Delete a device
- L398-401 _public method_ `public async Task<IDevice?> TryCreateDeviceAsync(DeviceId id, string name, DevicePlatformId platformId, DevicePoolId poolId, bool? enabled, string? address, string? modelId, UserId? userId = null, List<string>? tags = null)` — Create a new device
- L406-417 _public method_ `public async Task UpdateDeviceAsync(DeviceId deviceId, DevicePoolId? newPoolId = null, string? newName = null, string? newAddress = null, string? newModelId = null, string? newNotes = null, bool? newEnabled = null, bool? newProblem = null, bool? newMaintenance = null, UserId? modifiedByUserId = null, string? message = null, List<string>? newTags = null)` — Update a device
- L422-425 _public method_ `public async Task CheckoutDeviceAsync(DeviceId deviceId, UserId? userId)` — Checkout a device
- L430-433 _public method_ `public async Task CleanDeviceAsync(DeviceId deviceId, bool cleaning)` — Clean a device
- L438-597 _public method_ `public async Task<(IDeviceReservation?, string? errorMessage, bool installRequired)> TryCreateReservationAsync(DevicePoolId poolId, List<DeviceRequestData> request, string? hostname = null, string? reservationDetails = null, JobId? jobId = null, JobStepId? stepId = null, CancellationToken cancellationToken = default)` — Try to create a reservation satisfying the specified device platforms and models
- L602-605 _public method_ `public Task<IDeviceReservation?> TryUpdateReservationAsync(ObjectId id, DeviceId? problemDevice = null)` — Update/renew an existing reservation
- L610-628 _public method_ `public async Task<bool> DeleteReservationAsync(ObjectId id, bool force = false)` — Delete an existing reservation
- L633-636 _public method_ `public async Task<IDeviceReservation?> TryGetReservationFromLegacyGuidAsync(string legacyGuid)` — Get a reservation from a legacy guid
- L641-644 _public method_ `public async Task<IDeviceReservation?> TryGetDeviceReservationAsync(DeviceId deviceId)` — Get a reservation from a device id
- L649-652 _public method_ `public async Task<List<IDeviceReservation>> GetReservationsAsync()` — Get a list of existing device reservations
- L657-716 _public method_ `public async Task NotifyDeviceServiceAsync(BuildConfig buildConfig, string message, DeviceId? deviceId = null, string? jobId = null, string? stepId = null, UserId? userId = null, CancellationToken cancellationToken = default)`
- L725-745 _public method_ `public static bool Authorize(AclAction action, ClaimsPrincipal user, BuildConfig buildConfig)` — Authorize device action
- L753-829 _public method_ `public List<DevicePoolAuthorization> GetUserPoolAuthorizations(ClaimsPrincipal user, BuildConfig buildConfig)` — Get list of pool authorizations for a user
- L838-842 _public method_ `public DevicePoolAuthorization? GetUserPoolAuthorization(DevicePoolId id, ClaimsPrincipal user, BuildConfig buildConfig)` — Get list of pool authorizations for a user

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Devices/DevicesController.cs` (HordeServer.Build)


#### class `HordeServer.Devices.DevicesController`  
`public class DevicesController : ControllerBase`  
_public; L21-1099_
- inherits: `ControllerBase`
- desc: Controller for device service
- L23 _private* field_ `readonly IUserCollection _userCollection`
- L24 _private* field_ `readonly DeviceService _deviceService`
- L25 _private* field_ `readonly IOptionsMonitor<BuildConfig> _buildConfig`
- L30 _private field_ `private readonly ILogger<DevicesController> _logger` — Logger for controller
- L35-41 _public ctor_ `public DevicesController(IUserCollection userCollection, DeviceService deviceService, IOptionsMonitor<BuildConfig> buildConfig, ILogger<DevicesController> logger)` — Constructor
- L51-99 _public method_ `public async Task<ActionResult<CreateDeviceResponse>> CreateDeviceAsync([FromBody] CreateDeviceRequest deviceRequest, CancellationToken cancellationToken = default)` — attrs: `[HttpPost] [Authorize] [Route("/api/v2/devices")]` — Create a new device
- L108-143 _public method_ `public async Task<ActionResult<List<object>>> GetDevicesAsync()` — attrs: `[HttpGet] [Authorize] [Route("/api/v2/devices")] [ProducesResponseType(typeof(List<GetDeviceResponse>), 200)]` — Get list of devices
- L152-186 _public method_ `public async Task<ActionResult<object>> GetDeviceAsync(string deviceId)` — attrs: `[HttpGet] [Authorize] [Route("/api/v2/devices/{deviceId}")] [ProducesResponseType(typeof(GetDeviceResponse), 200)]` — Get a specific device
- L194-246 _public method_ `public async Task<ActionResult> UpdateDeviceAsync(string deviceId, [FromBody] UpdateDeviceRequest update, CancellationToken cancellationToken = default)` — attrs: `[HttpPut] [Authorize] [Route("/api/v2/devices/{deviceId}")]` — Update a specific device
- L254-295 _public method_ `public async Task<ActionResult> CheckoutDeviceAsync(string deviceId, [FromBody] CheckoutDeviceRequest request, CancellationToken cancellationToken)` — attrs: `[HttpPut] [Authorize] [Route("/api/v2/devices/{deviceId}/checkout")]` — Checkout a device
- L303-325 _public method_ `public async Task<ActionResult> CleanDeviceAsync(string deviceId, [FromBody] CleanDeviceRequest request)` — attrs: `[HttpPut] [Authorize] [Route("/api/v2/devices/{deviceId}/clean")]` — Clean a device
- L333-357 _public method_ `public async Task<ActionResult> DeleteDeviceAsync(string deviceId)` — attrs: `[HttpDelete] [Authorize] [Route("/api/v2/devices/{deviceId}")]` — Delete a specific device
- L368-386 _public method_ `public ActionResult<List<object>> GetDevicePlatforms()` — attrs: `[HttpGet] [Authorize] [Route("/api/v2/devices/platforms")] [ProducesResponseType(typeof(List<GetDevicePlatformResponse>), 200)]` — Get a list of supported device platforms
- L397-418 _public method_ `public ActionResult<List<object>> GetDevicePools()` — attrs: `[HttpGet] [Authorize] [Route("/api/v2/devices/pools")] [ProducesResponseType(typeof(List<GetDevicePoolResponse>), 200)]` — Get a list of existing device pools
- L427-482 _public method_ `public async Task<ActionResult<List<GetDevicePoolTelemetryResponse>>> GetDevicePoolTelemetryAsync( [FromQuery] DateTimeOffset? minCreateTime = null, [FromQuery] DateTimeOffset? maxCreateTime = null, [FromQuery] int index = 0, [FromQuery] int count = 1024)` — attrs: `[HttpGet] [Authorize] [Route("/api/v2/devices/pools/telemetry")] [ProducesResponseType(typeof(List<GetDevicePoolTelemetryResponse>), 200)]` — Get device telemetry
- L493-581 _public method_ `public async Task<ActionResult<CreateDeviceReservationResponse>> CreateDeviceReservationAsync([FromBody] CreateDeviceReservationRequest request)` — attrs: `[HttpPost] [Authorize] [Route("/api/v2/devices/reservations")] [ProducesResponseType(typeof(CreateDeviceReservationResponse), 200)]` — Create a new device reservation
- L590-624 _public method_ `public async Task<ActionResult<List<GetDeviceReservationResponse>>> GetDeviceReservationsAsync()` — attrs: `[HttpGet] [Authorize] [Route("/api/v2/devices/reservations")] [ProducesResponseType(typeof(List<GetDeviceReservationResponse>), 200)]` — Get active device reservations
- L632-649 _public method_ `public async Task<ActionResult> UpdateReservationAsync(string reservationId)` — attrs: `[HttpPut] [Authorize] [Route("/api/v2/devices/reservations/{reservationId}")]` — Renew an existing reservation
- L657-669 _public method_ `public async Task<ActionResult> DeleteReservationAsync(string reservationId)` — attrs: `[HttpDelete] [Authorize] [Route("/api/v2/devices/reservations/{reservationId}")]` — Delete a reservation
- L680-756 _public method_ `public async Task<ActionResult<List<GetDeviceTelemetryResponse>>> GetDeviceTelemetryAsync( [FromQuery(Name = "Id")] string[]? deviceIds = null, [FromQuery] string? poolId = null, [FromQuery] string? platformId = null, [FromQuery] DateTimeOffset? minCreateTime = null, [FromQuery] DateTimeOffset? maxCreateTime = null, [FromQuery] int index = 0, [FromQuery] int count = 1024)` — attrs: `[HttpGet] [Authorize] [Route("/api/v2/devices/telemetry")] [ProducesResponseType(typeof(List<GetDeviceTelemetryResponse>), 200)]` — Get device telemetry
- L769-783 _public method_ `public async Task<ActionResult> GetDeviceHistoryAsync(DeviceId deviceId, [FromQuery] DateTime? minTime = null, [FromQuery] DateTime? maxTime = null, [FromQuery] int index = 0, [FromQuery] int count = 50)` — attrs: `[HttpGet] [Route("/api/v1/devices/{deviceId}/history")]` — Retrieve historical information about a specific device
- L801-952 _public method_ `public async Task<ActionResult<GetLegacyReservationResponse>> CreateDeviceReservationV1Async([FromBody] LegacyCreateReservationRequest request)` — attrs: `[HttpPost] [Route("/api/v1/reservations")] [ProducesResponseType(typeof(GetLegacyReservationResponse), 200)]` — Create a device reservation
- L960-989 _public method_ `public async Task<ActionResult<GetLegacyReservationResponse>> UpdateReservationV1Async(string reservationGuid )` — attrs: `[HttpPut] [Route("/api/v1/reservations/{reservationGuid}")] [ProducesResponseType(typeof(GetLegacyReservationResponse), 200)]` — Renew a reservation
- L996-1008 _public method_ `public async Task<ActionResult> DeleteReservationV1Async(string reservationGuid, [FromQuery] bool force = false)` — attrs: `[HttpDelete] [Route("/api/v1/reservations/{reservationGuid}")]` — Delete a reservation
- L1016-1079 _public method_ `public async Task<ActionResult<GetLegacyDeviceResponse>> GetDeviceV1Async(string deviceName)` — attrs: `[HttpGet] [Route("/api/v1/devices/{deviceName}")] [ProducesResponseType(typeof(GetLegacyDeviceResponse), 200)]` — Get device info for a reserved device
- L1086-1098 _public method_ `public async Task<ActionResult> PutDeviceErrorAsync(string deviceName, [FromBody] DeviceErrorRequest? request = null)` — attrs: `[HttpPut] [Route("/api/v1/deviceerror/{deviceName}")]` — Mark a problem device

#### enum `HordeServer.Devices.DevicesController.LegacyPerfSpec`  
`enum LegacyPerfSpec`  
_private*; L787-793_
- L789 _public* enumerator_ `Unspecified`
- L790 _public* enumerator_ `Minimum`
- L791 _public* enumerator_ `Recommended`
- L792 _public* enumerator_ `High`

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Devices/IDevice.cs` (HordeServer.Build)


#### interface `HordeServer.Devices.IDeviceReservation`  
`public interface IDeviceReservation`  
_public; L16-102_
- desc: A reservation containing one or more devices
- L21 _public property_ `public ObjectId Id { get; }` — Randomly generated unique id for this reservation
- L26 _public property_ `public DevicePoolId PoolId { get; }` — Which device pool the reservation is in
- L31 _public property_ `public string? StreamId { get; }` — Strwam id holding reservation
- L36 _public property_ `public string? JobId { get; }` — JobID holding reservation
- L41 _public property_ `public string? StepId { get; }` — Job step id holding reservation
- L46 _public property_ `public string? JobName { get; }` — Job name holding reservation
- L51 _public property_ `public string? StepName { get; }` — Job step name holding reservation
- L56 _public property_ `public UserId? UserId { get; }` — Reservations held by a user, requires a token
- L61 _public* property_ `string? Hostname { get; }` — The hostname of machine holding reservation
- L66 _public* property_ `string? ReservationDetails { get; }` — The hostname of machine holding reservation
- L71 _public* property_ `DateTime CreateTimeUtc { get; }` — The UTC time when the reservation was created
- L76 _public* property_ `DateTime UpdateTimeUtc { get; }` — The last update time for reservation renewal (for expiration)
- L81 _public property_ `public List<DeviceId> Devices { get; }` — The reserved devices
- L86 _public property_ `public List<JobStepId>? ReservedStepIds { get; }` — StepIds that use the reservation
- L91 _public property_ `public DeviceId? ProblemDevice { get; }` — Whether a device problem was reported for the reservation
- L96 _public property_ `public List<string> RequestedDevicePlatforms { get; }` — The requested device platforms for reservation, which may differ from IDevice platform due to devices that support more than one platform, or legacy platforms
- L101 _public property_ `public string LegacyGuid { get; }` — The legacy reservation system guid, to be removed once can update Gauntlet client in all streams

#### interface `HordeServer.Devices.IDevicePlatform`  
`public interface IDevicePlatform`  
_public; L107-133_
- desc: A device platform
- L112 _public property_ `public DevicePlatformId Id { get; }` — Unique identifier of device platform
- L117 _public* property_ `string Name { get; }` — Device platform name, for example Android, PS5, etc
- L122 _public property_ `public IReadOnlyList<string>? Models { get; }` — A list of valid models for the platform
- L127 _public property_ `public IReadOnlyList<string>? LegacyNames { get; }` — Legacy names which older versions of Gauntlet may be using
- L132 _public property_ `public string? LegacyPerfSpecHighModel { get; }` — Model name for the high perf spec, which may be requested by Gauntlet

#### interface `HordeServer.Devices.IDevicePool`  
`public interface IDevicePool`  
_public; L138-159_
- desc: A logical pool of devices
- L143 _public property_ `public DevicePoolId Id { get; }` — Unique identifier of pool
- L148 _public property_ `public DevicePoolType PoolType { get; }` — The type of pool
- L153 _public property_ `public List<ProjectId>? ProjectIds { get; }` — Projects associated with this device pool
- L158 _public* property_ `string Name { get; }` — Friendly name of the pool

#### class `HordeServer.Devices.DeviceUtilizationTelemetry`  
`public class DeviceUtilizationTelemetry`  
_public; L164-202_
- desc: A device utilization snapshot [DEPRECATED]
- L169 _public property_ `public string? JobId { get; set; }` — The job id which utilized device
- L174 _public property_ `public string? StepId { get; set; }` — The job's step id
- L179 _public property_ `public DateTime ReservationStartUtc { get; set; }` — The time device was reserved
- L184 _public property_ `public DateTime? ReservationFinishUtc { get; set; }` — The time device was freed
- L190-192 _private ctor_ `private DeviceUtilizationTelemetry()` — attrs: `[BsonConstructor]` — Private constructor
- L198-201 _public ctor_ `public DeviceUtilizationTelemetry(DateTime reservationStartUtc)` — Constructor

#### interface `HordeServer.Devices.IDeviceTelemetry`  
`public interface IDeviceTelemetry`  
_public; L207-263_
- desc: Device telemetry information
- L212 _public property_ `public DateTime CreateTimeUtc { get; }` — The creation time of this telemetry data
- L217 _public property_ `public DeviceId DeviceId { get; }` — The device id for telemetry
- L222 _public property_ `public string? StreamId { get; }` — The stream id which utilized device
- L227 _public property_ `public string? JobId { get; }` — The job id which utilized device
- L232 _public property_ `public string? JobName { get; }` — The job name which utilized device
- L237 _public property_ `public string? StepId { get; }` — The job's step id
- L242 _public property_ `public string? StepName { get; }` — The job name which utilized device
- L247 _public property_ `public ObjectId? ReservationId { get; }` — Reservation Id (transient, reservations are deleted upon expiration)
- L252 _public property_ `public DateTime? ReservationStartUtc { get; }` — The time device was reserved
- L257 _public property_ `public DateTime? ReservationFinishUtc { get; }` — The time device was freed
- L262 _public property_ `public DateTime? ProblemTimeUtc { get; }` — If the device reported a problem

#### interface `HordeServer.Devices.IDevice`  
`public interface IDevice`  
_public; L268-359_
- desc: A physical device
- L273 _public property_ `public DeviceId Id { get; }` — The unique id of the device
- L278 _public property_ `public DevicePlatformId PlatformId { get; }` — The platform of the device
- L283 _public property_ `public DevicePoolId PoolId { get; }` — Which pool the device belongs to
- L288 _public property_ `public string Name { get; }` — Friendly name of the device
- L293 _public property_ `public string? ModelId { get; }` — The model of the device
- L298 _public property_ `public string? Address { get; }` — Address if the device supports shared network connections
- L303 _public property_ `public bool Enabled { get; }` — Whether the device is currently enabled
- L308 _public property_ `public string? ModifiedByUser { get; }` — Id of the user that last modified this device
- L313 _public property_ `public string? CheckedOutByUser { get; }` — Id of the user that has this device checked out
- L318 _public property_ `public DateTime? CheckOutTime { get; }` — The last time this device was checked out
- L323 _public property_ `public DateTime? ProblemTimeUtc { get; }` — The last time a problem was reported
- L328 _public property_ `public DateTime? MaintenanceTimeUtc { get; }` — The time device was marked for maintenance
- L333 _public property_ `public string? Notes { get; }` — Markdown notes for device if any
- L338 _public property_ `public List<string>? Tags { get; }` — Metadata tags on the device
- L343 _public property_ `public bool? CleanRequired { get; }` — Whether the device requires a clean
- L348 _public property_ `public DateTime? CleanStartTimeUtc { get; }` — The time device the device cleaning started
- L353 _public property_ `public DateTime? CleanFinishTimeUtc { get; }` — The time the device cleaning finished
- L358 _public property_ `public List<DeviceUtilizationTelemetry>? Utilization { get; set; }` — Device job utilization history

#### interface `HordeServer.Devices.IDevicePoolReservationTelemetry`  
`public interface IDevicePoolReservationTelemetry`  
_public; L364-390_
- desc: Stream device telemetry for pool snapshot
- L369 _public property_ `public DeviceId DeviceId { get; }` — Device id for reservation
- L374 _public property_ `public string? JobId { get; }` — Job id associated with reservation
- L379 _public property_ `public string? StepId { get; }` — The step id of reservation
- L384 _public property_ `public string? JobName { get; }` — The name of the job holding reservation
- L389 _public property_ `public string? StepName { get; }` — The name of the step holding reservation

#### interface `HordeServer.Devices.IDevicePlatformTelemetry`  
`public interface IDevicePlatformTelemetry`  
_public; L395-426_
- desc: Platform telemetry for a device pool
- L400 _public property_ `public DevicePlatformId PlatformId { get; }` — The corresponding platform id
- L405 _public property_ `public IReadOnlyList<DeviceId>? Available { get; }` — Available devices of this platform
- L410 _public property_ `public IReadOnlyList<DeviceId>? Maintenance { get; }` — Number of devices in maintenance state
- L415 _public property_ `public IReadOnlyList<DeviceId>? Problem { get; }` — Number of devices in problem state
- L420 _public property_ `public IReadOnlyList<DeviceId>? Disabled { get; }` — Number of devices in disabled state
- L425 _public property_ `public IReadOnlyDictionary<StreamId, IReadOnlyList<IDevicePoolReservationTelemetry>>? Reserved { get; }` — Number of reserved devices of this platform

#### interface `HordeServer.Devices.IDevicePoolTelemetry`  
`public interface IDevicePoolTelemetry`  
_public; L431-442_
- desc: A snapshot of device pool telemetry
- L436 _public property_ `public DateTime CreateTimeUtc { get; }` — The creation time of this telemetry data
- L441 _public property_ `public IReadOnlyDictionary<DevicePoolId, IReadOnlyList<IDevicePlatformTelemetry>> Pools { get; }` — Pool platform telemetry

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Devices/IDeviceCollection.cs` (HordeServer.Build)


#### class `HordeServer.Devices.DeviceRequestData`  
`public class DeviceRequestData`  
_public; L13-58_
- desc: Device reservation request data
- L18 _public property_ `public DevicePlatformId PlatformId { get; set; }` — The platform of the device to reserve
- L23 _public property_ `public string RequestedPlatform { get; set; }` — The platform client requested, which can differ from the devices platformid due to mapping
- L28 _public property_ `public List<string> IncludeModels { get; set; }` — Models to include for this request
- L33 _public property_ `public List<string> ExcludeModels { get; set; }` — Models to exclude for this request
- L38 _public property_ `public string? DeviceName { get; set; }` — Specific device to reserve
- L43 _public property_ `public DeviceTagsRequest? Tags { get; set; }` — Desired Tags of the device
- L48-57 _public ctor_ `public DeviceRequestData(DevicePlatformId platformId, string requestedPlatform, List<string>? includeModels = null, List<string>? excludeModels = null, string? deviceName = null, DeviceTagsRequest? tags = null)` — Constructor

#### interface `HordeServer.Devices.IDeviceCollection`  
`public interface IDeviceCollection`  
_public; L63-245_
- desc: A collection for device management
- L70 _public* method_ `Task<IDevice?> GetDeviceAsync(DeviceId deviceId)` — Get a device by id
- L75 _public* method_ `Task<IDevice?> GetDeviceByNameAsync(string deviceName)` — Get a device by name
- L83 _public* method_ `Task<List<IDevice>> FindAllDevicesAsync(List<DeviceId>? deviceIds, DevicePoolId? poolId = null, DevicePlatformId? platformId = null)` — Get a list of all devices
- L97 _public* method_ `Task<IDevice?> TryAddDeviceAsync(DeviceId id, string name, DevicePlatformId platformId, DevicePoolId poolId, bool? enabled, string? address, string? modelId, UserId? userId, List<string>? tags = null)` — Adds a new device
- L114 _public* method_ `Task UpdateDeviceAsync(DeviceId deviceId, DevicePoolId? newPoolId, string? newName, string? newAddress, string? newModelId, string? newNotes, bool? newEnabled, bool? newProblem, bool? newMaintenance, UserId? modifiedByUserId = null, string? message = null, List<string>? newTags = null)` — Update a device
- L123 _public* method_ `Task UpdateDeviceCleaningAsync(DeviceId deviceId, bool? cleaning = null, bool? cleanRequired = null)` — Updates a device's cleaning status
- L129 _public* method_ `Task<bool> DeleteDeviceAsync(DeviceId deviceId)` — Delete a device from the collection
- L137 _public* method_ `Task CheckoutDeviceAsync(DeviceId deviceId, UserId? checkedOutByUserId)` — Checkout or checkin the specified device
- L147 _public* method_ `Task<IDeviceReservation?> TryFindReserveBlockAsync(JobId? jobId, JobStepId? stepId)` — Tries to find an existing reservation block
- L161 _public* method_ `Task<(IDeviceReservation?, bool)> TryAddReservationAsync(DevicePoolId poolId, List<DeviceRequestData> request, int problemCooldown, string? hostname, string? reservationDetails, IJob? job, JobStepId? stepId, string? stepName, List<JobStepId>? stepIds)` — Create a new reseveration in the pool with the specified devices
- L167 _public* method_ `Task<IDeviceReservation?> TryGetReservationFromLegacyGuidAsync(string legacyGuid)` — Gets a reservation by guid for legacy clients
- L173 _public* method_ `Task<IDeviceReservation?> TryGetReservationAsync(ObjectId reservationId)` — Gets a reservation by reservation id
- L179 _public* method_ `Task<IDeviceReservation?> TryGetDeviceReservationAsync(DeviceId id)` — Gets a reservation by device id
- L184 _public* method_ `Task<List<IDeviceReservation>> FindAllReservationsAsync()` — Get a list of all reservations
- L193 _public method_ `public Task<IDeviceReservation?> TryUpdateReservationAsync(ObjectId id, DeviceId? problemDevice = null, List<DeviceId>? deviceIds = null, bool? clearProblemDevice = null)` — Updates a reservation to the current time, for expiration
- L199 _public method_ `public Task<bool> DeleteReservationAsync(ObjectId id)` — Deletes a reservation and releases reserved devices
- L205 _public method_ `public Task<List<(UserId, IDevice)>?> ExpireCheckedOutAsync(int checkoutDays)` — Deletes user device checkouts
- L211 _public method_ `public Task<List<(UserId, IDevice)>?> ExpireNotificatonsAsync(int checkoutDays)` — Gets a list of users to notify whose device checkout is about to expire
- L222 _public method_ `public Task<List<IDeviceTelemetry>> FindDeviceTelemetryAsync(DeviceId[]? deviceIds = null, DateTimeOffset? minCreateTime = null, DateTimeOffset? maxCreateTime = null, int? index = null, int? count = null)` — Find device telemetry
- L228 _public method_ `public Task CreatePoolTelemetrySnapshotAsync(List<IDevicePool> pools, int poolCooldown)` — Creates a device pool telemetry snapshot
- L238 _public method_ `public Task<List<IDevicePoolTelemetry>> FindPoolTelemetryAsync(DateTimeOffset? minCreateTime = null, DateTimeOffset? maxCreateTime = null, int? index = null, int? count = null)` — Gets pool telemetry for an optional date range
- L243 _public method_ `public Task UpgradeAsync()` — Upgrades the collection

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Issues/DebugIssuesController.cs` (HordeServer.Build)


#### class `HordeServer.Issues.DebugIssuesController`  
`public class DebugIssuesController : HordeControllerBase`  
_public; L28-193_
- attrs: `[ApiController] [Authorize] [DebugEndpoint] [Tags("Debug")]`
- inherits: `HordeControllerBase`
- desc: Debug functionality for issues
- L30 _private field_ `private readonly IIssueCollection _issueCollection`
- L31 _private field_ `private readonly IssueService _issueService`
- L32 _private field_ `private readonly IUserCollection _userCollection`
- L33 _private field_ `private readonly IOptionsSnapshot<BuildConfig> _buildConfig`
- L38-48 _public ctor_ `public DebugIssuesController( IIssueCollection issueCollection, IssueService issueService, IUserCollection userCollection, IOptionsSnapshot<BuildConfig> buildConfig)` — Constructor
- L56-192 _public method_ `public async Task<ActionResult> CreateTestIssueAsync( [FromQuery] StreamId streamId, [FromQuery] int commitId, [FromQuery] string[] suspectLogins, [FromQuery] int[] suspectCommitIds, [FromQuery] TemplateId? templateId = null, [FromQuery] string? nodeName = null, [FromQuery] string? summary = null, [FromQuery] string? fingerprintType = null, [FromQuery] string? jobId = null, [FromQuery] string? batchId = null, [FromQuery] string? stepId = null, [FromQuery] string? workflowId = null, [FromQuery] int? lastSuccessCommitId = null, [FromQuery] int? maxSuspectRank = null, [FromQuery] bool promoted = true)` — attrs: `[HttpPost] [Route("/api/v1/debug/issues/create-test-issue")]` — Creates a test issue with synthetic suspects and triggers the notification pipeline. Useful for testing Slack DM notifications without requiring real Perforce commits and job failures.

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Issues/External/IExternalIssue.cs` (HordeServer.Build)


#### interface `HordeServer.Issues.External.IExternalIssue`  
`public interface IExternalIssue`  
_public; L8-49_
- L13 _public property_ `public string Key { get; set; }` — The issue key or tracking id
- L18 _public property_ `public string? Link { get; set; }` — The issue link on external tracking site
- L23 _public property_ `public string? StatusName { get; set; }` — The issue status name, "To Do", "In Progress", etc
- L28 _public property_ `public string? ResolutionName { get; set; }` — The issue resolution name, "Fixed", "Closed", etc
- L33 _public property_ `public string? PriorityName { get; set; }` — The issue priority name, "1 - Critical", "2 - Major", etc
- L38 _public property_ `public string? AssigneeName { get; set; }` — The current assignee's user name
- L43 _public property_ `public string? AssigneeDisplayName { get; set; }` — The current assignee's display name
- L48 _public property_ `public string? AssigneeEmailAddress { get; set; }` — The current assignee's email address

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Issues/External/IExternalIssueService.cs` (HordeServer.Build)


#### interface `HordeServer.Issues.External.IExternalIssueProject`  
`public interface IExternalIssueProject`  
_public; L12-38_
- desc: External issue tracking project
- L17 _public* property_ `string Key { get; }` — Project key
- L22 _public* property_ `string Name { get; }` — Project name
- L27 _public* property_ `string Id { get; }` — Project id
- L32 _public* property_ `Dictionary<string, string> Components { get; }` — component id => name
- L37 _public* property_ `Dictionary<string, string> IssueTypes { get; }` — // IssueType id => name

#### interface `HordeServer.Issues.External.IExternalIssueService`  
`public interface IExternalIssueService : IHostedService`  
_public; L43-82_
- inherits: `IHostedService`
- desc: Interface for an external issue tracking service
- L50 _public* method_ `string? GetIssueUrl(string key)` — Gets the URL for an issue from a key
- L58 _public* method_ `Task<List<IExternalIssue>> GetIssuesAsync(string[] keys, CancellationToken cancellationToken)` — Get issues associated with provided keys
- L73 _public* method_ `Task<(string? key, string? url)> CreateIssueAsync(IUser user, string? externalIssueUser, int issueId, string summary, string projectId, string componentId, string issueType, string? description, string? hordeIssueLink, CancellationToken cancellationToken)` — Create and link an external issue
- L81 _public* method_ `Task<List<IExternalIssueProject>> GetProjectsAsync(StreamConfig streamConfig, CancellationToken cancellationToken)` — Get projects for provided keys

#### class `HordeServer.Issues.External.DefaultExternalIssueService`  
`public class DefaultExternalIssueService : IExternalIssueService`  
_public; L87-118_
- inherits: `IExternalIssueService`
- desc: Default external issue service
- L90-93 _public method_ `public string? GetIssueUrl(string key)` — (inheritdoc)
- L96-99 _public method_ `public Task<List<IExternalIssue>> GetIssuesAsync(string[] keys, CancellationToken cancellationToken)` — (inheritdoc)
- L102-105 _public method_ `public Task<(string? key, string? url)> CreateIssueAsync(IUser user, string? externalIssueUser, int issueId, string summary, string projectId, string componentId, string issueType, string? description, string? hordeIssueLink, CancellationToken cancellationToken)` — (inheritdoc)
- L108-111 _public method_ `public Task<List<IExternalIssueProject>> GetProjectsAsync(StreamConfig streamConfig, CancellationToken cancellationToken)` — (inheritdoc)
- L114 _public method_ `public Task StartAsync(CancellationToken token)` — (inheritdoc)
- L117 _public method_ `public Task StopAsync(CancellationToken token)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Issues/External/JiraService.cs` (HordeServer.Build)


#### class `HordeServer.Issues.External.JiraIssue`  
`internal class JiraIssue : IExternalIssue`  
_internal; L21-62_
- inherits: `IExternalIssue`
- desc: Jira issue information
- L26 _public property_ `public string Key { get; set; }` — The Jira issue key
- L31 _public property_ `public string? Link { get; set; }` — The Jira issue link
- L36 _public property_ `public string? StatusName { get; set; }` — The issue status name, "To Do", "In Progress", etc
- L41 _public property_ `public string? ResolutionName { get; set; }` — The issue resolution name, "Fixed", "Closed", etc
- L46 _public property_ `public string? PriorityName { get; set; }` — The issue priority name, "1 - Critical", "2 - Major", etc
- L51 _public property_ `public string? AssigneeName { get; set; }` — The current assignee's user name
- L56 _public property_ `public string? AssigneeDisplayName { get; set; }` — The current assignee's display name
- L61 _public property_ `public string? AssigneeEmailAddress { get; set; }` — The current assignee's email address

#### class `HordeServer.Issues.External.JiraCreateResponse`  
`internal class JiraCreateResponse`  
_internal; L64-71_
- L69 _public property_ `public string Key { get; set; }` — Key of external issue

#### class `HordeServer.Issues.External.JiraProject`  
`internal class JiraProject : IExternalIssueProject`  
_internal; L73-87_
- inherits: `IExternalIssueProject`
- L75 _public property_ `public string Key { get; set; }`
- L77 _public property_ `public string Name { get; set; }`
- L79 _public property_ `public string Id { get; set; }`
- L82 _public property_ `public Dictionary<string, string> Components { get; set; }`
- L85 _public property_ `public Dictionary<string, string> IssueTypes { get; set; }`

#### class `HordeServer.Issues.External.JiraService`  
`internal sealed class JiraService : IExternalIssueService, IHostedService, IAsyncDisposable`  
_internal; L92-752_
- inherits: `IExternalIssueService, IHostedService, IAsyncDisposable`
- desc: Jira service functionality
- L97 _private* field_ `static readonly JsonSerializerOptions s_jsonOptions = new JsonSerializerOptions { PropertyNameCaseInsensitive = true }` — Cached JsonSerializerOptions for case-insensitive deserialization
- L102-106 _private* method_ `static Uri NormalizeUrl(Uri url)` — Normalizes a URL by ensuring it has a trailing slash
- L108 _private* field_ `readonly ILogger _logger`
- L113 _private* field_ `readonly BuildServerConfig _settings` — The server settings
- L114 _private* field_ `readonly HttpClient _client`
- L115 _private* field_ `readonly AsyncPolicy<HttpResponseMessage> _retryPolicy`
- L116 _private* field_ `readonly ConcurrentDictionary<string, JiraCacheValue> _issueCache = ...`
- L116 _private* field_ `readonly ConcurrentDictionary< _issueCache = new ConcurrentDictionary<string, JiraCacheValue>()`
- L121 _private* field_ `readonly IssueService _issueService` — Singleton instance of the project service
- L123 _private* field_ `readonly IUserCollection _userCollection`
- L125 _private* field_ `readonly ITicker _ticker`
- L126 _private* field_ `readonly ITicker _updateTicker`
- L128 _private* field_ `readonly Uri _jiraUrl`
- L134 _private* field_ `Uri _jiraBaseUrl` — Base URL returned from Jira's serverInfo endpoint, used for all REST calls. Initialized to configured URL, updated after serverInfo detection.
- L137 _private* field_ `readonly TimeSpan _tickInitialDelay = TimeSpan.FromSeconds(15)`
- L138 _private* field_ `readonly TimeSpan _tickInterval = TimeSpan.FromMinutes(2)`
- L139 _private* field_ `readonly TimeSpan _updateTickInterval = TimeSpan.FromMinutes(1)`
- L144 _private* field_ `JiraDeploymentType _deploymentType = JiraDeploymentType.Unknown` — Detected Jira deployment type (Cloud vs Server/Data Center)
- L149 _private* property_ `bool IsCloud => ...` — Returns true if connected to Jira Cloud, false for Server/Data Center
- L151 _private* field_ `readonly Dictionary<string, JiraProject> _cachedJiraProjects = ...`
- L151 _private* field_ `readonly Dictionary< _cachedJiraProjects = new Dictionary<string, JiraProject>()`
- L153 _private* field_ `readonly IOptionsMonitor<BuildConfig> _buildConfig`
- L164-182 _public ctor_ `public JiraService(IOptions<BuildServerConfig> settings, IssueService issueService, IUserCollection userCollection, IClock clock, IOptionsMonitor<BuildConfig> buildConfig, ILogger<JiraService> logger)` — Jira service constructor
- L185-190 _public method_ `public async Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L195-221 _private* method_ `async Task DetectDeploymentTypeAsync(CancellationToken cancellationToken)` — Detects whether the Jira instance is Cloud or Server/Data Center by querying the serverInfo endpoint
- L224-228 _public method_ `public async Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L231-236 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L239 _public method_ `public string? GetIssueUrl(string key)` — (inheritdoc)
- L241-268 _public method_ `public Task<List<IExternalIssueProject>> GetProjectsAsync(StreamConfig streamConfig, CancellationToken cancellationToken)`
- L270-369 _private* method_ `async Task UpdateJiraProjectsAsync(string[] jiraProjectKeys, CancellationToken cancellationToken)`
- L374-422 _private* method_ `async ValueTask TickUpdateAsync(CancellationToken stoppingToken)` — Periodically syncs Horde issue ownership with Jira assignees by matching email addresses
- L427-465 _private* method_ `async ValueTask<TimeSpan?> TickAsync(CancellationToken cancellationToken)` — Periodically refreshes Jira project metadata and issue status for all open Horde issues with linked Jira keys
- L467-558 _public method_ `public async Task<(string? key, string? url)> CreateIssueAsync(IUser user, string? externalIssueUser, int issueId, string summary, string projectId, string componentId, string issueType, string? description, string? hordeIssueLink, CancellationToken cancellationToken)`
- L561-653 _public method_ `public async Task<List<IExternalIssue>> GetIssuesAsync(string[] jiraKeys, CancellationToken cancellationToken)` — (inheritdoc)

#### struct `HordeServer.Issues.External.JiraService.JiraCacheValue`  
`struct JiraCacheValue`  
_private*; L657-661_
- L659 _public field_ `public JiraIssue _issue`
- L660 _public field_ `public DateTime _cacheTime`

#### class `HordeServer.Issues.External.JiraService.IssueQueryResponse`  
`class IssueQueryResponse`  
_private*; L663-668_
- L665 _public property_ `public int Total { get; set; }`
- L667 _public property_ `public List<IssueResponse> Issues { get; set; }`

#### class `HordeServer.Issues.External.JiraService.IssueResponse`  
`class IssueResponse`  
_private*; L670-675_
- L672 _public property_ `public string Key { get; set; }`
- L674 _public property_ `public IssueFields? Fields { get; set; }`

#### class `HordeServer.Issues.External.JiraService.IssueFields`  
`class IssueFields`  
_private*; L677-686_
- L679 _public property_ `public AssigneeField? Assignee { get; set; }`
- L681 _public property_ `public StatusField? Status { get; set; }`
- L683 _public property_ `public ResolutionField? Resolution { get; set; }`
- L685 _public property_ `public PriorityField? Priority { get; set; }`

#### class `HordeServer.Issues.External.JiraService.AssigneeField`  
`class AssigneeField`  
_private*; L688-703_
- L693 _public property_ `public string? Name { get; set; }` — User name (Server/Data Center only, not present in Cloud v3)
- L698 _public property_ `public string? AccountId { get; set; }` — Account ID (Cloud only, not present in Server/Data Center)
- L700 _public property_ `public string? DisplayName { get; set; }`
- L702 _public property_ `public string? EmailAddress { get; set; }`

#### class `HordeServer.Issues.External.JiraService.StatusField`  
`class StatusField`  
_private*; L705-708_
- L707 _public property_ `public string? Name { get; set; }`

#### class `HordeServer.Issues.External.JiraService.PriorityField`  
`class PriorityField`  
_private*; L710-713_
- L712 _public property_ `public string? Name { get; set; }`

#### class `HordeServer.Issues.External.JiraService.ResolutionField`  
`class ResolutionField`  
_private*; L715-718_
- L717 _public property_ `public string? Name { get; set; }`

#### enum `HordeServer.Issues.External.JiraService.JiraDeploymentType`  
`enum JiraDeploymentType`  
_private*; L723-739_
- desc: Jira deployment type
- L728 _public* enumerator_ `Unknown` — Unknown deployment type (not yet detected)
- L733 _public* enumerator_ `Cloud` — Jira Cloud deployment
- L738 _public* enumerator_ `OnPremise` — Jira Server or Data Center (on-premise) deployment

#### class `HordeServer.Issues.External.JiraService.ServerInfoResponse`  
`class ServerInfoResponse`  
_private*; L744-751_
- desc: Response from /rest/api/2/serverInfo endpoint
- L746 _public property_ `public string? BaseUrl { get; set; }`
- L747 _public property_ `public string? Version { get; set; }`
- L748 _public property_ `public string? DeploymentType { get; set; }`
- L749 _public property_ `public int[]? VersionNumbers { get; set; }`
- L750 _public property_ `public string? ServerTitle { get; set; }`

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Issues/IIssue.cs` (HordeServer.Build)


#### interface `HordeServer.Issues.IIssue`  
`public interface IIssue`  
_public; L14-185_
- desc: Stores information about a build health issue
- L19 _public* property_ `static UserId ResolvedByTimeoutId { get; }` — Id for resolved by system
- L24 _public* property_ `static UserId ResolvedByUnknownId { get; }` — Id for resolved by unknown user
- L29 _public property_ `public int Id { get; }` — The unique object id
- L34 _public property_ `public string Summary { get; }` — Summary for this issue
- L39 _public property_ `public string? UserSummary { get; }` — Summary set by users
- L44 _public property_ `public string? Description { get; }` — Notes set by the user
- L49 _public property_ `public IReadOnlyList<IIssueFingerprint> Fingerprints { get; }` — Fingerprint for this issue
- L54 _public property_ `public IssueSeverity Severity { get; }` — Severity of this issue
- L59 _public property_ `public bool Promoted { get; }` — Whether this issue is promoted to be publicly visible
- L64 _public property_ `public UserId? OwnerId { get; }` — User id of the owner
- L69 _public property_ `public UserId? NominatedById { get; }` — User id of the person that nominated the owner
- L74 _public property_ `public DateTime CreatedAt { get; }` — Time at which the issue was created
- L79 _public property_ `public DateTime? NominatedAt { get; }` — Time that the current owner was nominated
- L84 _public property_ `public DateTime? AcknowledgedAt { get; }` — Time at which the issue was acknowledged
- L89 _public property_ `public DateTime? ResolvedAt { get; }` — Time at which the issue was resolved
- L94 _public property_ `public UserId? ResolvedById { get; }` — User that resolved the issue
- L99 _public property_ `public DateTime? VerifiedAt { get; }` — Time at which the issue was verified fixed
- L104 _public property_ `public DateTime LastSeenAt { get; }` — Time at which the issue was last seen.
- L109 _public property_ `public CommitId? FixCommitId { get; }` — Fix commit for this issue
- L114 _public property_ `public CommitId? RootCommitId { get; }` — Root commit for this issue
- L119 _public property_ `public UserId? RootCauseOwnerId { get; }` — User to provide the root cause analysis for this issue
- L124 _public property_ `public string? RootCauseCategory { get; }` — Root cause category for this issue
- L129 _public property_ `public string? RootCauseSummary { get; }` — Root cause summary for this issue
- L134 _public property_ `public int? DuplicateIssueId { get; }` — An issue id that is marked as a duplicate
- L139 _public property_ `public bool FixSystemic { get; }` — Whether the issue is marked fixed as systemic
- L149 _public property_ `public IReadOnlyList<IIssueStream> Streams { get; }` — List of streams affected by this issue
- L154 _public property_ `public List<ObjectId>? ExcludeSpans { get; }` — Spans which should be excluded from this issue
- L159 _public property_ `public int UpdateIndex { get; }` — Update index for this instance
- L164 _public property_ `public string? ExternalIssueKey { get; }` — External issue linked to this issue
- L169 _public property_ `public UserId? QuarantinedByUserId { get; set; }` — User who quarantined the issue
- L174 _public property_ `public DateTime? QuarantineTimeUtc { get; set; }` — The UTC time when the issue was quarantined
- L179 _public property_ `public UserId? ForceClosedByUserId { get; set; }` — User who force closed the issue
- L184 _public property_ `public Uri? WorkflowThreadUrl { get; set; }` — The workflow thread url created for this issue

#### interface `HordeServer.Issues.IIssueStream`  
`public interface IIssueStream`  
_public; L190-211_
- desc: Information about a stream affected by an issue
- L195 _public* property_ `StreamId StreamId { get; }` — The stream id
- L200 _public* property_ `bool? MergeOrigin { get; }` — Whether this stream is the merge origin for other streams
- L205 _public* property_ `bool? ContainsFix { get; }` — Whether this stream contains the fix change
- L210 _public* property_ `bool? FixFailed { get; }` — Whether the fix failed in this stream

#### interface `HordeServer.Issues.IIssueSuspect`  
`public interface IIssueSuspect`  
_public; L216-242_
- desc: Suspect for an issue
- L221 _public* property_ `ObjectId Id { get; }` — Unique id for this suspect
- L226 _public* property_ `int IssueId { get; }` — Issue that this suspect belongs to
- L231 _public* property_ `UserId AuthorId { get; }` — The user id of the change's author
- L236 _public* property_ `CommitIdWithOrder CommitId { get; }` — The commit suspected of causing this issue (in the origin stream)
- L241 _public* property_ `DateTime? DeclinedAt { get; }` — Time at which the author declined the issue

#### class `HordeServer.Issues.IssueExtensions`  
`static class IssueExtensions`  
_internal*; L247-272_
- desc: Extension methods for issues
- L252 _public method_ `public static bool IsMarkedFixed(this IIssue issue)` — Test whether an issue is marked as fixed
- L260-271 _public method_ `public static Dictionary<StreamId, bool> GetFixStreamIds(this IIssue issue)` — Creates a lookup from stream id to whether it's fixed

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Issues/IIssueCollection.cs` (HordeServer.Build)


#### interface `HordeServer.Issues.IIssueCollection`  
`public interface IIssueCollection`  
_public; L24-236_
- desc: Interface for an issue collection
- L31 _public* method_ `Task<IAsyncDisposable> EnterCriticalSectionAsync(string purpose)` — Attempts to enters a critical section over the issue collection. Used for performing operations that require coordination of several documents (eg. attaching spans to issues).
- L41 _public* method_ `Task<IIssue> AddIssueAsync(string summary, CancellationToken cancellationToken = default)` — Creates a new issue
- L49 _public* method_ `Task<IIssue?> GetIssueAsync(int issueId, CancellationToken cancellationToken = default)` — Retrieves and issue by id
- L57 _public* method_ `Task<IReadOnlyList<IIssueSuspect>> FindSuspectsAsync(int issueId, CancellationToken cancellationToken = default)` — Finds the suspects for an issue
- L73 _public* method_ `Task<IReadOnlyList<IIssue>> FindIssuesAsync(IEnumerable<int>? ids = null, UserId? ownerId = null, StreamId? streamId = null, CommitId? minCommitId = null, CommitId? maxCommitId = null, bool? resolved = null, bool? promoted = null, int? index = null, int? count = null, CancellationToken cancellationToken = default)` — Searches for open issues
- L81 _public* method_ `Task<IReadOnlyList<IIssue>> FindIssuesForChangesAsync(List<CommitIdWithOrder> commits, CancellationToken cancellationToken = default)` — Searches for open issues
- L91 _public* method_ `Task<IIssue?> TryUpdateIssueAsync(IIssue issue, UserId? initiatedByUserId, UpdateIssueOptions options, CancellationToken cancellationToken = default)` — Try to update the state of an issue
- L107 _public* method_ `Task<IIssue?> TryUpdateIssueDerivedDataAsync(IIssue issue, string newSummary, IssueSeverity newSeverity, List<NewIssueFingerprint> newFingerprints, List<NewIssueStream> newStreams, List<NewIssueSuspectData> newSuspects, DateTime? newResolvedAt, DateTime? newVerifiedAt, DateTime newLastSeenAt, CancellationToken cancellationToken = default)` — Updates derived data for an issue (ie. data computed from the spans attached to it). Also clears the issue's 'modified' state.
- L120 _public* method_ `Task<IIssueSpan> AddSpanAsync(int issueId, NewIssueSpanData newSpan, CancellationToken cancellationToken = default)` — Creates a new span from the given failure
- L128 _public* method_ `Task<IIssueSpan?> GetSpanAsync(ObjectId spanId, CancellationToken cancellationToken = default)` — Gets a particular span
- L142 _public* method_ `Task<IIssueSpan?> TryUpdateSpanAsync(IIssueSpan span, NewIssueStepData? newLastSuccess = null, NewIssueStepData? newFailure = null, NewIssueStepData? newNextSuccess = null, List<NewIssueSpanSuspectData>? newSuspects = null, int? newMaxSuspectRank = null, int? newIssueId = null, CancellationToken cancellationToken = default)` — Updates the given span. Note that data in the span's issue may be derived from this, and the issue should be updated afterwards.
- L150 _public* method_ `Task<IReadOnlyList<IIssueSpan>> FindSpansAsync(int issueId, CancellationToken cancellationToken = default)` — Gets all the spans for a particular issue
- L158 _public* method_ `Task<IReadOnlyList<IIssueSpan>> FindSpansAsync(IEnumerable<ObjectId> spanIds, CancellationToken cancellationToken = default)` — Retrieves multiple spans
- L169 _public* method_ `Task<IReadOnlyList<IIssueSpan>> FindOpenSpansAsync(StreamId streamId, TemplateId templateId, string name, CommitId commitId, CancellationToken cancellationToken = default)` — Finds the open issues for a given stream
- L184 _public* method_ `Task<IReadOnlyList<IIssueSpan>> FindSpansAsync(IEnumerable<ObjectId>? ids = null, IEnumerable<int>? issueIds = null, StreamId? streamId = null, CommitId? minCommitId = null, CommitId? maxCommitId = null, bool? resolved = null, int? index = null, int? count = null, CancellationToken cancellationToken = default)` — Searches for open issues
- L195 _public* method_ `Task<IReadOnlyList<int>> FindSpanIssueIdsAsync(StreamId streamId, CommitId? minCommitId = null, CommitId? maxCommitId = null, bool? resolved = null, CancellationToken cancellationToken = default)` — Gets distinct issue ids from spans matching the given filter, using an aggregate pipeline to avoid transferring full span documents.
- L208 _public* method_ `Task<IIssueStep> AddStepAsync(ObjectId spanId, NewIssueStepData newStep, CancellationToken cancellationToken = default)` — Adds a new step
- L216 _public* method_ `Task<IReadOnlyList<IIssueStep>> FindStepsAsync(IEnumerable<ObjectId> spanIds, CancellationToken cancellationToken = default)` — Find steps for the given spans
- L226 _public* method_ `Task<IReadOnlyList<IIssueStep>> FindStepsAsync(JobId jobId, JobStepBatchId? batchId, JobStepId? stepId, CancellationToken cancellationToken = default)` — Find steps for the given spans
- L235 _public* method_ `IAuditLogChannel<int> GetLogger(int issueId)` — Gets the logger for a particular issue

#### record `HordeServer.Issues.UpdateIssueOptions`  
`public record class UpdateIssueOptions ( IssueSeverity? Severity = null, string? Summary = null, string? UserSummary = null, string? Description = null, bool? Promoted = null, UserId? OwnerId = null, UserId? NominatedById = null, bool? Acknowledged = null, UserId? DeclinedById = null, CommitId? FixCommitId = null, bool? FixSystemic = null, CommitId? RootCommitId = null, UserId? RootCauseOwnerId = null, string? RootCauseCategory = null, string? RootCauseSummary = null, int? DuplicateIssueId = null, UserId? ResolvedById = null, List<ObjectId>? ExcludeSpanIds = null, DateTime? LastSeenAt = null, string? ExternalIssueKey = null, UserId? QuarantinedById = null, UserId? ForceClosedById = null, Uri? WorkflowThreadUrl = null )`  
_public; L264-264_
- desc: Options for updating an issue

#### class `HordeServer.Issues.IssueCollectionExtensions`  
`public static class IssueCollectionExtensions`  
_public; L294-355_
- desc: Extension methods for issues
- L303-306 _public method_ `public static Task<IReadOnlyList<IIssueSuspect>> FindSuspectsAsync(this IIssueCollection issueCollection, IIssue issue, CancellationToken cancellationToken = default)` — Find suspects for the given issue
- L315-318 _public method_ `public static Task<IReadOnlyList<IIssueStep>> FindStepsAsync(this IIssueCollection issueCollection, ObjectId spanId, CancellationToken cancellationToken = default)` — Find steps for the given spans
- L336-354 _public method_ `public static async Task<IReadOnlyList<IIssue>> FindIssuesForJobAsync(this IIssueCollection issueCollection, IJob job, IGraph graph, JobStepId? stepId = null, JobStepBatchId? batchId = null, int? labelIdx = null, UserId? ownerId = null, bool? resolved = null, bool? promoted = null, int? index = null, int? count = null, CancellationToken cancellationToken = default)` — Searches for open issues affecting a job

#### class `HordeServer.Issues.NewIssueFingerprint`  
`public class NewIssueFingerprint : IIssueFingerprint, IEquatable<IIssueFingerprint>`  
_public; L360-545_
- inherits: `IIssueFingerprint, IEquatable<IIssueFingerprint>`
- desc: Fingerprint for an issue
- L363 _public property_ `public string Type { get; set; }` — (inheritdoc)
- L366 _public property_ `public string SummaryTemplate { get; set; }` — (inheritdoc)
- L369 _public property_ `public HashSet<IssueKey> Keys { get; set; }` — (inheritdoc)
- L372 _private* property_ `IReadOnlySet<IssueKey> IIssueFingerprint.Keys => ...` — (inheritdoc)
- L375 _public property_ `public HashSet<IssueKey> RejectKeys { get; set; }` — (inheritdoc)
- L378 _private* property_ `IReadOnlySet<IssueKey>? IIssueFingerprint.RejectKeys => ...` — (inheritdoc)
- L381 _public property_ `public HashSet<IssueMetadata> Metadata { get; set; }` — (inheritdoc)
- L384 _private* property_ `IReadOnlySet<IssueMetadata>? IIssueFingerprint.Metadata => ...` — (inheritdoc)
- L387 _public property_ `public string ChangeFilter { get; set; }` — (inheritdoc)
- L395-400 _public ctor_ `public NewIssueFingerprint(string type, string summaryTemplate, string changeFilter)` — Constructor
- L411-427 _public ctor_ `public NewIssueFingerprint(string type, string summaryTemplate, IEnumerable<IssueKey> keys, IEnumerable<IssueKey>? rejectKeys, IEnumerable<IssueMetadata>? metadata, string changeFilter)` — Constructor
- L433-436 _public ctor_ `public NewIssueFingerprint(IIssueFingerprint other) : this(other.Type, other.SummaryTemplate, other.Keys, other.RejectKeys, other.Metadata, other.ChangeFilter)` — Copy constructor
- L442-455 _public method_ `public void MergeWith(IIssueFingerprint other)` — Merges another fingerprint into this one
- L458 _public method_ `public override bool Equals(object? other)` — (inheritdoc)
- L461-479 _public method_ `public bool Equals(IIssueFingerprint? otherFingerprint)` — (inheritdoc)
- L485-489 _public method_ `public override int GetHashCode()` — Gets a hashcode for this fingerprint
- L497-507 _private* method_ `static bool ContentsEqual<T>(IReadOnlySet<T>? setA, IReadOnlySet<T>? setB)` — Checks if the contents of two sets are equal
- L514-525 _private* method_ `static int GetContentsHash<T>(IEnumerable<T>? set)` — Gets the hash of the contents of a case insensitive set
- L533-538 _public method_ `public static NewIssueFingerprint Merge(IIssueFingerprint a, IIssueFingerprint b)` — Merges two fingerprints togetherthis issue fingerprint with another
- L541-544 _public method_ `public override string ToString()` — (inheritdoc)

#### class `HordeServer.Issues.NewIssueSpanData`  
`public class NewIssueSpanData`  
_public; L550-594_
- desc: Information about a new span
- L553 _public property_ `public StreamId StreamId { get; set; }` — (inheritdoc)
- L556 _public property_ `public string StreamName { get; set; }` — (inheritdoc)
- L559 _public property_ `public TemplateId TemplateRefId { get; set; }` — (inheritdoc)
- L562 _public property_ `public string NodeName { get; set; }` — (inheritdoc)
- L565 _public property_ `public NewIssueFingerprint Fingerprint { get; set; }` — (inheritdoc)
- L568 _public property_ `public NewIssueStepData? LastSuccess { get; set; }` — (inheritdoc)
- L571 _public property_ `public NewIssueStepData FirstFailure { get; set; }` — (inheritdoc)
- L574 _public property_ `public NewIssueStepData? NextSuccess { get; set; }` — (inheritdoc)
- L577 _public property_ `public List<NewIssueSpanSuspectData> Suspects { get; set; }` — (inheritdoc)
- L580 _public property_ `public int? MaxSuspectRank { get; set; }` — (inheritdoc)
- L585-593 _public ctor_ `public NewIssueSpanData(StreamId streamId, string streamName, TemplateId templateRefId, string nodeName, NewIssueFingerprint fingerprint, NewIssueStepData firstFailure)` — Constructor

#### class `HordeServer.Issues.NewIssueStepData`  
`public class NewIssueStepData`  
_public; L599-683_
- desc: Identifies a particular changelist and job
- L602 _public property_ `public CommitIdWithOrder CommitId { get; set; }` — (inheritdoc)
- L605 _public property_ `public IssueSeverity Severity { get; set; }` — (inheritdoc)
- L608 _public property_ `public string JobName { get; set; }` — (inheritdoc)
- L611 _public property_ `public JobId JobId { get; set; }` — (inheritdoc)
- L614 _public property_ `public JobStepBatchId BatchId { get; set; }` — (inheritdoc)
- L617 _public property_ `public JobStepId StepId { get; set; }` — (inheritdoc)
- L620 _public property_ `public DateTime StepTime { get; set; }` — (inheritdoc)
- L623 _public property_ `public LogId? LogId { get; set; }` — (inheritdoc)
- L626 _public property_ `public NodeAnnotations? Annotations { get; set; }` — (inheritdoc)
- L629 _public property_ `public bool PromoteByDefault { get; set; }` — (inheritdoc)
- L644-659 _public ctor_ `public NewIssueStepData(CommitIdWithOrder commitId, IssueSeverity severity, string jobName, JobId jobId, JobStepBatchId batchId, JobStepId stepId, DateTime stepTime, LogId? logId, IReadOnlyNodeAnnotations? annotations, bool promoted)` — Constructor
- L670-673 _public ctor_ `public NewIssueStepData(IJob job, IJobStepBatch batch, IJobStep step, IssueSeverity severity, IReadOnlyNodeAnnotations? annotations, bool promoted) : this(job.CommitId, severity, job.Name, job.Id, batch.Id, step.Id, step.StartTimeUtc ?? default, step.LogId, annotations, promoted)` — Constructor
- L679-682 _public ctor_ `public NewIssueStepData(IJobStepRef jobStepRef) : this(jobStepRef.CommitId, IssueSeverity.Unspecified, jobStepRef.JobName, jobStepRef.Id.JobId, jobStepRef.Id.BatchId, jobStepRef.Id.StepId, jobStepRef.StartTimeUtc, jobStepRef.LogId, null, false)` — Constructor for sentinel steps

#### class `HordeServer.Issues.NewIssueSuspectData`  
`public class NewIssueSuspectData`  
_public; L688-706_
- desc: Information about a suspect changelist that may have caused an issue
- L691 _public property_ `public UserId AuthorId { get; set; }` — (inheritdoc)
- L694 _public property_ `public CommitIdWithOrder CommitId { get; set; }` — (inheritdoc)
- L701-705 _public ctor_ `public NewIssueSuspectData(UserId authorId, CommitIdWithOrder commitId)` — Constructor

#### class `HordeServer.Issues.NewIssueSpanSuspectData`  
`public class NewIssueSpanSuspectData`  
_public; L711-732_
- desc: Information about a suspect changelist that may have caused an issue
- L714 _public property_ `public CommitIdWithOrder CommitId { get; set; }` — (inheritdoc)
- L717 _public property_ `public UserId AuthorId { get; set; }` — (inheritdoc)
- L720 _public property_ `public CommitIdWithOrder? SourceCommitId { get; set; }` — (inheritdoc)
- L727-731 _public ctor_ `public NewIssueSpanSuspectData(CommitIdWithOrder change, UserId authorId)` — Constructor

#### class `HordeServer.Issues.NewIssueStream`  
`public class NewIssueStream : IIssueStream`  
_public; L737-759_
- inherits: `IIssueStream`
- desc: Information about a stream containing an issue
- L740 _public property_ `public StreamId StreamId { get; set; }` — (inheritdoc)
- L743 _public property_ `public bool? MergeOrigin { get; set; }` — (inheritdoc)
- L746 _public property_ `public bool? ContainsFix { get; set; }` — (inheritdoc)
- L749 _public property_ `public bool? FixFailed { get; set; }` — (inheritdoc)
- L755-758 _public ctor_ `public NewIssueStream(StreamId streamId)` — Constructor

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Issues/IIssueDetails.cs` (HordeServer.Build)


#### interface `HordeServer.Issues.IIssueDetails`  
`public interface IIssueDetails`  
_public; L11-90_
- desc: Cached issue information
- L16 _public* property_ `IIssue Issue { get; }` — The issue instance
- L21 _public* property_ `IUser? Owner { get; }` — The user that currently owns this issue
- L26 _public* property_ `IUser? NominatedBy { get; }` — The user that nominated the current owner
- L31 _public* property_ `IUser? ResolvedBy { get; }` — The user that resolved the issue
- L36 _public* property_ `IUser? RootCauseOwner { get; }` — The user that provided the root cause analysis
- L41 _public* property_ `IReadOnlyList<IIssueSpan> Spans { get; }` — List of spans for the issue
- L46 _public* property_ `IReadOnlyList<IIssueStep> Steps { get; }` — List of steps for the issue
- L51 _public* property_ `IReadOnlyList<IIssueSuspect> Suspects { get; }` — List of suspects for the issue
- L56 _public* property_ `IReadOnlyList<IUser> SuspectUsers { get; }` — List of users that are suspects for this issue
- L61 _public* property_ `string? ExternalIssueKey { get; }` — Issue key in external issue tracker
- L66 _public* property_ `IUser? QuarantinedBy { get; }` — User who quarantined the issue
- L71 _public* property_ `DateTime? QuarantineTimeUtc { get; }` — The UTC time when the issue was quarantined
- L76 _public* property_ `IUser? ForceClosedBy { get; }` — User who force closed the issue
- L82 _public* method_ `bool ShowNotifications()` — Determines whether the given user should be notified about the given issue
- L89 _public* method_ `bool IncludeForUser(UserId userId)` — Determines if the issue is relevant to the given user

#### class `HordeServer.Issues.IssueDetailsExtensions`  
`public static class IssueDetailsExtensions`  
_public; L95-113_
- desc: Extension methods for IIssueService implementations
- L104-112 _public method_ `public static async Task<IIssueDetails?> GetIssueDetailsAsync(this IssueService issueService, int issueId, CancellationToken cancellationToken)` — Gets an issue details object for a specific issue id

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Issues/IIssueSpan.cs` (HordeServer.Build)


#### interface `HordeServer.Issues.IIssueSpan`  
`public interface IIssueSpan`  
_public; L15-88_
- desc: Trace of a set of errors in a single step across multiple jobs
- L20 _public property_ `public ObjectId Id { get; }` — Unique id for the span
- L25 _public property_ `public StreamId StreamId { get; }` — The unique stream id
- L30 _public property_ `public string StreamName { get; }` — The stream name
- L35 _public property_ `public TemplateId TemplateRefId { get; }` — The template containing this node
- L40 _public property_ `public string NodeName { get; }` — Name of the node
- L45 _public property_ `public IIssueFingerprint Fingerprint { get; }` — Fingerprint for this issue
- L50 _public property_ `public IIssueStep? LastSuccess { get; }` — The previous build
- L55 _public property_ `public IIssueStep FirstFailure { get; }` — Maximum changelist number that failed
- L60 _public property_ `public IIssueStep LastFailure { get; }` — Minimum changelist number that failed
- L65 _public property_ `public IIssueStep? NextSuccess { get; }` — The following successful build
- L70 _public property_ `public bool PromoteByDefault { get; }` — Whether to promote issues containing this span by default
- L75 _public property_ `public IReadOnlyList<IIssueSpanSuspect> Suspects { get; }` — Suspects for this span
- L82 _public property_ `public int? MaxSuspectRank { get; }` — The maximum rank achieved during suspect scoring for this span. A value of 0 means all suspects are tied with no meaningful differentiation (no file/symbol/note matches). Null if not yet computed or for spans created before this property was added.
- L87 _public property_ `public int IssueId { get; }` — The issue that this span is assigned to

#### interface `HordeServer.Issues.IIssueSpanSuspect`  
`public interface IIssueSpanSuspect`  
_public; L93-109_
- desc: Information about a suspect changelist that may have caused an issue
- L98 _public property_ `public CommitIdWithOrder CommitId { get; }` — The submitted changelist
- L103 _public property_ `public UserId AuthorId { get; }` — Id of the changelist's author
- L108 _public property_ `public CommitIdWithOrder? SourceCommitId { get; }` — The original changelist number, if merged from another branch. For changes merged between several branches, this is the originally submitted change.

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Issues/IIssueStep.cs` (HordeServer.Build)


#### interface `HordeServer.Issues.IIssueStep`  
`public interface IIssueStep`  
_public; L15-71_
- desc: Identifies a particular commit and job that contributes to a span
- L20 _public property_ `public ObjectId SpanId { get; }` — The span that this step belongs to
- L25 _public property_ `public CommitIdWithOrder CommitId { get; }` — The commit
- L30 _public property_ `public IssueSeverity Severity { get; }` — Severity of the issue in this step
- L35 _public property_ `public string JobName { get; }` — Name of the job
- L40 _public property_ `public JobId JobId { get; }` — The unique job id
- L45 _public property_ `public JobStepBatchId BatchId { get; }` — Unique id of the batch within the job
- L50 _public property_ `public JobStepId StepId { get; }` — Unique id of the step within the job
- L55 _public property_ `public DateTime StepTime { get; }` — Time that the step started
- L60 _public property_ `public IReadOnlyNodeAnnotations Annotations { get; }` — Annotations for this step
- L65 _public property_ `public bool PromoteByDefault { get; }` — Whether to promote spans including this step by default
- L70 _public property_ `public LogId? LogId { get; }` — The log id for this step

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Issues/IssueCollection.cs` (HordeServer.Build)


#### class `HordeServer.Issues.IssueCollection`  
`class IssueCollection : IIssueCollection, ILogExtIssueProvider`  
_internal*; L37-1980_
- inherits: `IIssueCollection, ILogExtIssueProvider`
- L695 _private* field_ `readonly IRedisService _redisService`
- L696 _private* field_ `readonly IUserCollection _userCollection`
- L697 _private* field_ `readonly ICommitService _commitService`
- L698 _private* field_ `readonly ISingletonDocument<IssueLedger> _ledgerSingleton`
- L699 _private* field_ `readonly IMongoCollection<IssueDocument> _issues`
- L700 _private* field_ `readonly IMongoCollection<IssueSpanDocument> _issueSpans`
- L701 _private* field_ `readonly IMongoCollection<IssueStepDocument> _issueSteps`
- L702 _private* field_ `readonly IMongoCollection<IssueSuspectDocument> _issueSuspects`
- L703 _private* field_ `readonly IAuditLog<int> _auditLog`
- L704 _private* field_ `readonly ITelemetryWriter _telemetryWriter`
- L705 _private* field_ `readonly IOptionsMonitor<BuildConfig> _buildConfig`
- L706 _private* field_ `readonly Tracer _tracer`
- L707 _private* field_ `readonly ILogger _logger`
- L709-726 _private* ctor_ `static IssueCollection()`
- L728-765 _public ctor_ `public IssueCollection(IMongoService mongoService, IRedisService redisService, IUserCollection userCollection, ICommitService commitService, IAuditLogFactory<int> auditLogFactory, ITelemetryWriter telemetryWriter, IOptionsMonitor<BuildConfig> buildConfig, Tracer tracer, ILogger<IssueCollection> logger)`
- L768-787 _public method_ `public async Task<IAsyncDisposable> EnterCriticalSectionAsync(string purpose)` — (inheritdoc)
- L789-804 _private* method_ `async Task<IssueDocument?> TryUpdateIssueAsync(IIssue issue, UpdateDefinition<IssueDocument> update, CancellationToken cancellationToken)`
- L806-821 _private* method_ `async Task<IssueSpanDocument?> TryUpdateSpanAsync(IIssueSpan issueSpan, UpdateDefinition<IssueSpanDocument> update, CancellationToken cancellationToken)`
- L826-838 _public method_ `public async Task<IIssue> AddIssueAsync(string summary, CancellationToken cancellationToken)` — (inheritdoc)
- L840-855 _private* method_ `void SendTelemetry(IIssue issue)`
- L857-879 _private* method_ `async ValueTask<string> GetUserNameAsync(UserId? userId, CancellationToken cancellationToken)`
- L881-886 _private* method_ `async Task LogIssueChangesAsync(UserId? initiatedByUserId, IssueDocument oldIssue, IssueDocument newIssue, CancellationToken cancellationToken)`
- L888-1086 _private* method_ `async Task LogIssueChangesImplAsync(ILogger issueLogger, IssueDocument oldIssue, IssueDocument newIssue, CancellationToken cancellationToken)`
- L1088-1119 _private* method_ `async Task LogIssueSuspectChangesAsync(ILogger issueLogger, IReadOnlyList<IssueSuspectDocument> oldIssueSuspects, List<IssueSuspectDocument> newIssueSuspects, CancellationToken cancellationToken)`
- L1122-1126 _public method_ `public async Task<IIssue?> GetIssueAsync(int issueId, CancellationToken cancellationToken)` — (inheritdoc)
- L1129-1132 _public method_ `public async Task<IReadOnlyList<IIssueSuspect>> FindSuspectsAsync(int issueId, CancellationToken cancellationToken)` — (inheritdoc)
- L1141-1155 _public method_ `public async Task<IReadOnlyList<IIssue>> FindIssuesAsync(IEnumerable<int>? ids = null, UserId? ownerId = null, StreamId? streamId = null, CommitId? minCommitId = null, CommitId? maxCommitId = null, bool? resolved = null, bool? promoted = null, int? index = null, int? count = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L1157-1224 _private* method_ `async Task<IReadOnlyList<IIssue>> FilterIssuesByStreamIdAsync(IEnumerable<int>? ids, StreamId? streamId, CommitId? minCommitId, CommitId? maxCommitId, bool? resolved, bool? promoted, int index, int? count, CancellationToken cancellationToken)`
- L1226-1256 _private* method_ `async Task<List<IssueDocument>> FilterIssuesByOtherFieldsAsync(IEnumerable<int>? ids, bool? resolved, bool? promoted, int index, int? count, CancellationToken cancellationToken)`
- L1267-1287 _private* method_ `static async Task<List<IssueDocument>> PaginatedJoinAsync(IAsyncCursor<ProjectedIssueId> cursor, Func<IEnumerable<int>, int, int?, Task<List<IssueDocument>>> nextStageFunc, int index, int? count, CancellationToken cancellationToken)` — Performs a client-side join of a filtered set of issues against another query
- L1290-1295 _public method_ `public async Task<IReadOnlyList<IIssue>> FindIssuesForChangesAsync(List<CommitIdWithOrder> commits, CancellationToken cancellationToken)` — (inheritdoc)
- L1298-1576 _public method_ `public async Task<IIssue?> TryUpdateIssueAsync(IIssue issue, UserId? initiatedByUserId, UpdateIssueOptions options, CancellationToken cancellationToken = default)` — (inheritdoc)
- L1579-1696 _public method_ `public async Task<IIssue?> TryUpdateIssueDerivedDataAsync(IIssue issue, string newSummary, IssueSeverity newSeverity, List<NewIssueFingerprint> newFingerprints, List<NewIssueStream> newStreams, List<NewIssueSuspectData> newSuspects, DateTime? newResolvedAt, DateTime? newVerifiedAt, DateTime newLastSeenAt, CancellationToken cancellationToken)` — (inheritdoc)
- L1698-1727 _private* method_ `async Task<List<IssueSuspectDocument>> UpdateIssueSuspectsAsync(int issueId, IReadOnlyList<IssueSuspectDocument> oldSuspectImpls, List<NewIssueSuspectData> newSuspects, DateTime? resolvedAt, CancellationToken cancellationToken)`
- L1729-1740 _private method_ `private static UserId? TryAutoAssignFromSuspects(List<IssueSuspectDocument> suspects)`
- L1747-1753 _public method_ `public async Task<IIssueSpan> AddSpanAsync(int issueId, NewIssueSpanData newSpan, CancellationToken cancellationToken)` — (inheritdoc)
- L1755-1761 _private* method_ `void SendTelemetry(IIssueSpan issueSpan)`
- L1764-1767 _public method_ `public async Task<IIssueSpan?> GetSpanAsync(ObjectId spanId, CancellationToken cancellationToken)` — (inheritdoc)
- L1770-1835 _public method_ `public async Task<IIssueSpan?> TryUpdateSpanAsync(IIssueSpan span, NewIssueStepData? newLastSuccess = null, NewIssueStepData? newFailure = null, NewIssueStepData? newNextSuccess = null, List<NewIssueSpanSuspectData>? newSuspects = null, int? newMaxSuspectRank = null, int? newIssueId = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L1838-1841 _public method_ `public async Task<IReadOnlyList<IIssueSpan>> FindSpansAsync(int issueId, CancellationToken cancellationToken)` — (inheritdoc)
- L1844-1847 _public method_ `public async Task<IReadOnlyList<IIssueSpan>> FindSpansAsync(IEnumerable<ObjectId> spanIds, CancellationToken cancellationToken)` — (inheritdoc)
- L1850-1854 _public method_ `public async Task<IReadOnlyList<IIssueSpan>> FindOpenSpansAsync(StreamId streamId, TemplateId templateId, string nodeName, CommitId commitId, CancellationToken cancellationToken)` — (inheritdoc)
- L1857-1898 _public method_ `public async Task<IReadOnlyList<IIssueSpan>> FindSpansAsync(IEnumerable<ObjectId>? spanIds, IEnumerable<int>? issueIds, StreamId? streamId, CommitId? minCommitId, CommitId? maxCommitId, bool? resolved, int? index, int? count, CancellationToken cancellationToken)` — (inheritdoc)
- L1901-1930 _public method_ `public async Task<IReadOnlyList<int>> FindSpanIssueIdsAsync(StreamId streamId, CommitId? minCommitId, CommitId? maxCommitId, bool? resolved, CancellationToken cancellationToken)` — (inheritdoc)
- L1937-1942 _public method_ `public async Task<IIssueStep> AddStepAsync(ObjectId spanId, NewIssueStepData newStep, CancellationToken cancellationToken)` — (inheritdoc)
- L1945-1949 _public method_ `public async Task<IReadOnlyList<IIssueStep>> FindStepsAsync(IEnumerable<ObjectId> spanIds, CancellationToken cancellationToken)` — (inheritdoc)
- L1952-1964 _public method_ `public async Task<IReadOnlyList<IIssueStep>> FindStepsAsync(JobId jobId, JobStepBatchId? batchId, JobStepId? stepId, CancellationToken cancellationToken)` — (inheritdoc)
- L1969-1972 _public method_ `public IAuditLogChannel<int> GetLogger(int issueId)` — (inheritdoc)
- L1975-1979 _public method_ `public async ValueTask<int?> GetIssueIdAsync(ObjectId spanId, CancellationToken cancellationToken = default)` — (inheritdoc)

#### class `HordeServer.Issues.IssueCollection.IssueLedger`  
`class IssueLedger : SingletonBase`  
_private*; L40-43_
- attrs: `[SingletonDocument("issue-ledger", "5e4c226440ce25fa3207a9af")]`
- inherits: `SingletonBase`
- L42 _public property_ `public int NextId { get; set; }`

#### class `HordeServer.Issues.IssueCollection.IssueDocument`  
`class IssueDocument : IIssue`  
_private*; L46-213_
- attrs: `[DebuggerDisplay("{Id}: {Summary}")]`
- inherits: `IIssue`
- L49 _public property_ `public int Id { get; set; }` — attrs: `[BsonId]`
- L51 _public property_ `public string Summary { get; set; }`
- L54 _public property_ `public string? UserSummary { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L57 _public property_ `public string? Description { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L60 _public property_ `public IssueFingerprintDocument? Fingerprint { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L61 _public property_ `public List<IssueFingerprintDocument>? Fingerprints { get; set; }`
- L63 _public property_ `public IssueSeverity Severity { get; set; }`
- L66 _public property_ `public bool Promoted { get; set; }` — attrs: `[BsonElement("PromotedV2")]`
- L69 _public property_ `public bool? ManuallyPromoted { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L72 _public property_ `public bool? ManuallyPromotedDeprecated { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("Promoted")]`
- L75 _public property_ `public UserId? OwnerId { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L78 _public property_ `public UserId? DefaultOwnerId { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L81 _public property_ `public UserId? NominatedById { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L83 _public property_ `public DateTime CreatedAt { get; set; }`
- L86 _public property_ `public DateTime? NominatedAt { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L89 _public property_ `public DateTime? AcknowledgedAt { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L92 _public property_ `public DateTime? ResolvedAt { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L95 _public property_ `public UserId? ResolvedById { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L98 _public property_ `public DateTime? VerifiedAt { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L100 _public property_ `public DateTime LastSeenAt { get; set; }`
- L103-107 _public property_ `public CommitId? FixCommitId { get; set; }` — attrs: `[BsonIgnore]`
- L110 _public property_ `public string? FixCommitName { get; set; }` — attrs: `[BsonElement("FixCommit"), BsonIgnoreIfNull]`
- L113 _public property_ `public int? FixChange { get; set; }` — attrs: `[BsonElement("FixChange"), BsonIgnoreIfNull]`
- L116 _public property_ `public bool FixSystemic { get; set; }` — attrs: `[BsonIgnoreIfDefault, BsonDefaultValue(false)]`
- L119-123 _public property_ `public CommitId? RootCommitId { get; set; }` — attrs: `[BsonIgnore]`
- L126 _public property_ `public string? RootCommitName { get; set; }` — attrs: `[BsonElement("RootCommit"), BsonIgnoreIfNull]`
- L129 _public property_ `public UserId? RootCauseOwnerId { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L132 _public property_ `public string? RootCauseCategory { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L135 _public property_ `public string? RootCauseSummary { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L138 _public property_ `public int? DuplicateIssueId { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L140 _public property_ `public List<IssueStreamDocument> Streams { get; set; }`
- L143 _public property_ `public List<IssueSuspectDocument>? SuspectsDeprecated { get; set; }` — attrs: `[BsonElement("Suspects"), BsonIgnoreIfNull]`
- L146 _public property_ `public List<ObjectId>? ExcludeSpans { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L148 _public property_ `public int UpdateIndex { get; set; }`
- L150 _private* property_ `IReadOnlyList<IIssueFingerprint> IIssue.Fingerprints => ...`
- L151 _private* property_ `UserId? IIssue.OwnerId => ...`
- L152 _private* property_ `IReadOnlyList<IIssueStream> IIssue.Streams => ...`
- L153 _private* property_ `DateTime IIssue.LastSeenAt => ...`
- L156 _public property_ `public string? ExternalIssueKey { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L159 _public property_ `public UserId? QuarantinedByUserId { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L162 _public property_ `public DateTime? QuarantineTimeUtc { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L165 _public property_ `public UserId? ForceClosedByUserId { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L168 _public property_ `public Uri? WorkflowThreadUrl { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L171-175 _private ctor_ `private IssueDocument()` — attrs: `[BsonConstructor]`
- L177-183 _public ctor_ `public IssueDocument(int id, string summary)`
- L185-196 _private* method_ `UserId? GetDefaultOwnerId()`
- L198-212 _public property_ `public string FingerprintsDesc { get; }`

#### class `HordeServer.Issues.IssueCollection.IssueStreamDocument`  
`class IssueStreamDocument : IIssueStream`  
_private*; L215-233_
- inherits: `IIssueStream`
- L217 _public property_ `public StreamId StreamId { get; set; }`
- L218 _public property_ `public bool? MergeOrigin { get; set; }`
- L219 _public property_ `public bool? ContainsFix { get; set; }`
- L220 _public property_ `public bool? FixFailed { get; set; }`
- L222-224 _public ctor_ `public IssueStreamDocument()`
- L226-232 _public ctor_ `public IssueStreamDocument(IIssueStream other)`

#### class `HordeServer.Issues.IssueCollection.IssueSuspectDocument`  
`class IssueSuspectDocument : IIssueSuspect`  
_private*; L235-284_
- inherits: `IIssueSuspect`
- L237 _public property_ `public ObjectId Id { get; set; }`
- L238 _public property_ `public int IssueId { get; set; }`
- L239 _public property_ `public UserId AuthorId { get; set; }`
- L242-246 _public property_ `public CommitIdWithOrder CommitId { get; set; }` — attrs: `[BsonIgnore]`
- L249 _public property_ `public string? CommitName { get; set; }` — attrs: `[BsonElement("Commit")]`
- L252 _public property_ `public int CommitOrder { get; set; }` — attrs: `[BsonElement("Change")]`
- L254 _public property_ `public DateTime? DeclinedAt { get; set; }`
- L255 _public property_ `public DateTime? ResolvedAt { get; set; }`
- L257-259 _private ctor_ `private IssueSuspectDocument()`
- L261-268 _public ctor_ `public IssueSuspectDocument(int issueId, NewIssueSuspectData newSuspect, DateTime? resolvedAt)`
- L270-273 _public ctor_ `public IssueSuspectDocument(int issueId, IIssueSpanSuspect suspect) : this(issueId, suspect.AuthorId, suspect.SourceCommitId ?? suspect.CommitId, null, null)`
- L275-283 _public ctor_ `public IssueSuspectDocument(int issueId, UserId authorId, CommitIdWithOrder commit, DateTime? declinedAt, DateTime? resolvedAt)`

#### class `HordeServer.Issues.IssueCollection.IssueFingerprintDocument`  
`class IssueFingerprintDocument : IIssueFingerprint`  
_private*; L286-449_
- inherits: `IIssueFingerprint`
- L288 _public property_ `public string Type { get; set; }`
- L291 _private* property_ `string? SummaryTemplateValue { get; set; }` — attrs: `[BsonElement("summary"), BsonIgnoreIfNull]`
- L294 _public property_ `public string SummaryTemplate => ...` — attrs: `[BsonIgnore]`
- L297 _public property_ `public HashSet<IssueKey> Keys { get; set; }` — attrs: `[BsonElement("inc")]`
- L299 _private* property_ `IReadOnlySet<IssueKey> IIssueFingerprint.Keys => ...`
- L302 _public property_ `public HashSet<IssueKey>? RejectKeys { get; set; }` — attrs: `[BsonElement("exc"), BsonIgnoreIfNull]`
- L304 _private* property_ `IReadOnlySet<IssueKey>? IIssueFingerprint.RejectKeys => ...`
- L307 _public property_ `public HashSet<IssueMetadata>? Metadata { get; set; }` — attrs: `[BsonElement("met"), BsonIgnoreIfNull]`
- L309 _private* property_ `IReadOnlySet<IssueMetadata>? IIssueFingerprint.Metadata => ...`
- L312 _public property_ `public string? ChangeFilter { get; set; }` — attrs: `[BsonElement("fl2")]`
- L316-320 _public property_ `public List<string>? LegacyChangeFilter { get; set; }` — attrs: `[Obsolete("Use ChangeFilter instead")] [BsonElement("flt"), BsonIgnoreIfNull]`
- L322 _private* property_ `string IIssueFingerprint.ChangeFilter => ...`
- L325-328 _private ctor_ `private IssueFingerprintDocument()` — attrs: `[BsonConstructor]`
- L330-346 _public ctor_ `public IssueFingerprintDocument(IIssueFingerprint fingerprint)`
- L352-356 _private* property_ `CaseInsensitiveStringSet? LegacyKeys { get; set; }` — attrs: `[BsonElement("Keys"), BsonIgnoreIfNull]`
- L359-363 _private* property_ `CaseInsensitiveStringSet? LegacyRejectKeys { get; set; }` — attrs: `[BsonElement("RejectKeys"), BsonIgnoreIfNull]`
- L366-370 _private* property_ `CaseInsensitiveStringSet? LegacyMetadata { get; set; }` — attrs: `[BsonElement("Metadata"), BsonIgnoreIfNull]`
- L374 _private* method_ `static HashSet<IssueKey>? ParseKeySet(CaseInsensitiveStringSet? set)` — attrs: `[return: NotNullIfNotNull("set")]`
- L376-396 _private* method_ `static IssueKey ParseKey(string key)`
- L399-412 _private* method_ `static HashSet<IssueMetadata>? ParseMetadata(CaseInsensitiveStringSet? set)` — attrs: `[return: NotNullIfNotNull("set")]`
- L416 _private* field_ `static readonly Dictionary<StringView, LegacyHandlerInfo> s_legacyHandlers = ...`
- L416 _private* field_ `static readonly Dictionary< s_legacyHandlers = new Dictionary<StringView, LegacyHandlerInfo> { ["BuildGraph"] = new("BuildGraph {Severity} in {Files}", IssueChangeFilter.All), ["Compile"] = new("{Meta:CompileType} {Severity} in {Files}", IssueChan ...`
- L434-446 _private* method_ `static LegacyHandlerInfo GetLegacyHandlerInfo(string type)`

#### record `HordeServer.Issues.IssueCollection.IssueFingerprintDocument.LegacyHandlerInfo`  
`record class LegacyHandlerInfo(string SummaryTemplate, IReadOnlyList<string> ChangeFilter)`  
_private*; L414-414_

#### class `HordeServer.Issues.IssueCollection.IssueSpanDocument`  
`class IssueSpanDocument : IIssueSpan`  
_private*; L451-545_
- inherits: `IIssueSpan`
- L453 _public property_ `public ObjectId Id { get; set; }`
- L456 _public property_ `public StreamId StreamId { get; set; }` — attrs: `[BsonRequired]`
- L459 _public property_ `public string StreamName { get; set; }` — attrs: `[BsonRequired]`
- L462 _public property_ `public TemplateId TemplateRefId { get; set; }` — attrs: `[BsonRequired]`
- L465 _public property_ `public string NodeName { get; set; }` — attrs: `[BsonRequired]`
- L466 _public property_ `public DateTime? ResolvedAt { get; set; }`
- L469 _public property_ `public IssueFingerprintDocument Fingerprint { get; set; }` — attrs: `[BsonRequired]`
- L472 _public property_ `public int MinCommitOrder { get; set; }` — attrs: `[BsonElement("MinChange")]`
- L475 _public property_ `public int MaxCommitOrder { get; set; }` — attrs: `[BsonElement("MaxChange")]`
- L477 _public property_ `public IssueStepDocument? LastSuccess { get; set; }`
- L480 _public property_ `public IssueStepDocument FirstFailure { get; set; }` — attrs: `[BsonRequired]`
- L483 _public property_ `public IssueStepDocument LastFailure { get; set; }` — attrs: `[BsonRequired]`
- L485 _public property_ `public IssueStepDocument? NextSuccess { get; set; }`
- L487 _public property_ `public bool? PromoteByDefault { get; set; }`
- L490 _public property_ `public bool NotifySuspectsDeprecated { get; set; }` — attrs: `[BsonElement("NotifySuspects"), BsonIgnoreIfDefault(false)]`
- L492 _private* property_ `bool IIssueSpan.PromoteByDefault => ...`
- L494 _public property_ `public List<IssueSpanSuspectDocument> Suspects { get; set; }`
- L497 _public property_ `public int? MaxSuspectRank { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L499 _public property_ `public int IssueId { get; set; }`
- L500 _public property_ `public int UpdateIndex { get; set; }`
- L502 _private* property_ `IIssueStep? IIssueSpan.LastSuccess => ...`
- L503 _private* property_ `IIssueStep IIssueSpan.FirstFailure => ...`
- L504 _private* property_ `IIssueStep IIssueSpan.LastFailure => ...`
- L505 _private* property_ `IIssueStep? IIssueSpan.NextSuccess => ...`
- L506 _private* property_ `IReadOnlyList<IIssueSpanSuspect> IIssueSpan.Suspects => ...`
- L507 _private* property_ `int? IIssueSpan.MaxSuspectRank => ...`
- L508 _private* property_ `IIssueFingerprint IIssueSpan.Fingerprint => ...`
- L510-518 _private ctor_ `private IssueSpanDocument()`
- L520-544 _public ctor_ `public IssueSpanDocument(int issueId, NewIssueSpanData newSpan)`

#### class `HordeServer.Issues.IssueCollection.IssueSpanSuspectDocument`  
`class IssueSpanSuspectDocument : IIssueSpanSuspect`  
_private*; L547-588_
- inherits: `IIssueSpanSuspect`
- L550-554 _public property_ `public CommitIdWithOrder CommitId { get; set; }` — attrs: `[BsonIgnore]`
- L557 _private property_ `private string? CommitName { get; set; }` — attrs: `[BsonElement("Commit")]`
- L560 _private property_ `private int CommitOrder { get; set; }` — attrs: `[BsonElement("Change")]`
- L562 _public property_ `public UserId AuthorId { get; set; }`
- L565-569 _public property_ `public CommitIdWithOrder? SourceCommitId { get; set; }` — attrs: `[BsonIgnore]`
- L572 _public property_ `public string? SourceCommitName { get; set; }` — attrs: `[BsonElement("SourceCommit")]`
- L575 _public property_ `public int? SourceCommitOrder { get; set; }` — attrs: `[BsonElement("OriginatingChange")]`
- L578-580 _private ctor_ `private IssueSpanSuspectDocument()` — attrs: `[BsonConstructor]`
- L582-587 _public ctor_ `public IssueSpanSuspectDocument(NewIssueSpanSuspectData newSuspectData)`

#### class `HordeServer.Issues.IssueCollection.IssueStepDocument`  
`class IssueStepDocument : IIssueStep`  
_private*; L590-658_
- inherits: `IIssueStep`
- L592 _public property_ `public ObjectId Id { get; set; }`
- L593 _public property_ `public ObjectId SpanId { get; set; }`
- L596-600 _public property_ `public CommitIdWithOrder CommitId { get; set; }` — attrs: `[BsonIgnore]`
- L603 _public property_ `public string? CommitName { get; set; }` — attrs: `[BsonElement("Commit")]`
- L606 _public property_ `public int CommitOrder { get; set; }` — attrs: `[BsonElement("Change")]`
- L608 _public property_ `public IssueSeverity Severity { get; set; }`
- L611 _public property_ `public string JobName { get; set; }` — attrs: `[BsonRequired]`
- L614 _public property_ `public JobId JobId { get; set; }` — attrs: `[BsonRequired]`
- L617 _public property_ `public JobStepBatchId BatchId { get; set; }` — attrs: `[BsonRequired]`
- L620 _public property_ `public JobStepId StepId { get; set; }` — attrs: `[BsonRequired]`
- L622 _public property_ `public DateTime StepTime { get; set; }`
- L624 _public property_ `public LogId? LogId { get; set; }`
- L627 _public property_ `public NodeAnnotations? Annotations { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L629 _public property_ `public bool? PromoteByDefault { get; set; }`
- L632 _public property_ `public bool NotifySuspectsDeprecated { get; set; }` — attrs: `[BsonElement("NotifySuspects"), BsonIgnoreIfDefault(false)]`
- L634 _private* property_ `IReadOnlyNodeAnnotations IIssueStep.Annotations => ...`
- L635 _private* property_ `bool IIssueStep.PromoteByDefault => ...`
- L638-641 _private ctor_ `private IssueStepDocument()` — attrs: `[BsonConstructor]`
- L643-657 _public ctor_ `public IssueStepDocument(ObjectId spanId, NewIssueStepData stepData)`

#### class `HordeServer.Issues.IssueCollection.IssueLock`  
`sealed class IssueLock : IAsyncDisposable`  
_private*; L661-693_
- inherits: `IAsyncDisposable`
- L663 _private* field_ `readonly RedisLock _redisLock`
- L664 _private* field_ `readonly string _purpose`
- L665 _private* field_ `readonly Stopwatch _timer = Stopwatch.StartNew()`
- L666 _private* field_ `readonly TelemetrySpan _telemetrySpan`
- L667 _private* field_ `readonly ILogger _logger`
- L669-675 _public ctor_ `public IssueLock(RedisLock redisLock, string purpose, Tracer tracer, ILogger logger)`
- L677-692 _public method_ `public async ValueTask DisposeAsync()`

#### class `HordeServer.Issues.IssueCollection.ProjectedIssueId`  
`class ProjectedIssueId`  
_private*; L1134-1138_
- L1137 _public property_ `public int? _id { get; set; }` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Style", "IDE1006:Naming Styles")]`

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Issues/IssueConfig.cs` (HordeServer.Build)


#### class `HordeServer.Issues.IssueChannelGroupConfig`  
`public class IssueChannelGroupConfig`  
_public; L13-19_
- desc: Configuration for grouping to apply based on logging channels
- L18 _public property_ `public List<string>? Channels { get; set; }` — A list of channel logging boundaries to group issues on

#### class `HordeServer.Issues.IssueConfig`  
`public class IssueConfig`  
_public; L29-51_
- attrs: `[JsonSchema("https://unrealengine.com/horde/issues")] [JsonSchemaCatalog("Horde Issue", "Horde issue configuration file", new[] { "*.issues.json", "Issues/*.json" })] [ConfigDoc("*.issues.json", "[Horde](../../../README.md) > [Configuration](../../Config.md)", "Config/Schema/Issues.md")] [ConfigIncludeRoot] [ConfigMacroScope]`
- desc: Stores configuration for build health issues
- L34 _public property_ `public List<ConfigInclude> Include { get; set; }` — Includes for other configuration files
- L39 _public property_ `public List<IssueChannelGroupConfig>? ChannelGroups { get; set; }` — Issue grouping channels
- L44-50 _public method_ `public void PostLoad()` — Process Issue Config

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Issues/IssueReportService.cs` (HordeServer.Build)


#### class `HordeServer.Issues.WorkflowStats`  
`public class WorkflowStats`  
_public; L24-28_
- L26 _public property_ `public int NumSteps { get; set; }`
- L27 _public property_ `public int NumPassingSteps { get; set; }`

#### class `HordeServer.Issues.IssueReport`  
`public class IssueReport`  
_public; L30-48_
- L32 _public property_ `public StreamId StreamId { get; }`
- L33 _public property_ `public WorkflowId WorkflowId { get; }`
- L34 _public property_ `public WorkflowStats WorkflowStats { get; }`
- L35 _public property_ `public string? TriageChannel { get; }`
- L36 _public property_ `public List<IIssue> Issues { get; }`
- L37 _public property_ `public List<IIssueSpan> IssueSpans { get; }`
- L38 _public property_ `public bool GroupByTemplate { get; }`
- L40-47 _public ctor_ `public IssueReport(StreamId streamId, WorkflowId workflowId, WorkflowStats workflowStats, string? triageChannel, bool groupByTemplate)`

#### class `HordeServer.Issues.IssueReportGroup`  
`public class IssueReportGroup`  
_public; L50-61_
- L52 _public property_ `public string Channel { get; }`
- L53 _public property_ `public DateTime Time { get; }`
- L54 _public property_ `public List<IssueReport> Reports { get; }`
- L56-60 _public ctor_ `public IssueReportGroup(string channel, DateTime time)`

#### class `HordeServer.Issues.IssueReportState`  
`class IssueReportState : SingletonBase`  
_internal*; L66-70_
- attrs: `[SingletonDocument("issue-report-state", "6268871c211d05611b3e4fd8")]`
- inherits: `SingletonBase`
- L69 _public property_ `public Dictionary<string, DateTime> ReportTimes { get; set; }` — attrs: `[BsonDictionaryOptions(DictionaryRepresentation.ArrayOfDocuments)]`

#### class `HordeServer.Issues.IssueReportService`  
`public class IssueReportService : IHostedService`  
_public; L75-297_
- inherits: `IHostedService`
- desc: Posts summaries for all the open issues in different streams to Slack channels
- L77 _private* field_ `readonly SingletonDocument<IssueReportState> _state`
- L78 _private* field_ `readonly IIssueCollection _issueCollection`
- L79 _private* field_ `readonly IGraphCollection _graphCollection`
- L80 _private* field_ `readonly IJobCollection _jobCollection`
- L81 _private* field_ `readonly INotificationService _notificationService`
- L82 _private* field_ `readonly IClock _clock`
- L83 _private* field_ `readonly ITicker _ticker`
- L84 _private* field_ `readonly IOptionsMonitor<BuildConfig> _buildConfig`
- L85 _private* field_ `readonly ILogger<IssueReportService> _logger`
- L90-101 _public ctor_ `public IssueReportService(IMongoService mongoService, IIssueCollection issueCollection, IGraphCollection graphCollection, IJobCollection jobCollection, INotificationService notificationService, IClock clock, IOptionsMonitor<BuildConfig> buildConfig, ILogger<IssueReportService> logger)` — Constructor
- L104-107 _public method_ `public async Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L110-113 _public method_ `public async Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L115-224 _private* method_ `async ValueTask TickAsync(CancellationToken cancellationToken)`
- L226-275 _private method_ `private async Task<Dictionary<WorkflowId, WorkflowStats>> GetWorkflowStatsAsync(StreamConfig streamConfig, DateTime minTime, CancellationToken cancellationToken)`
- L277-296 _private* method_ `static DateTime GetLastScheduledReportTime(WorkflowConfig workflow, DateTime currentTimeUtc, TimeZoneInfo timeZone)`

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Issues/IssueService.cs` (HordeServer.Build)


#### class `HordeServer.Issues.IssueDetails`  
`class IssueDetails : IIssueDetails`  
_internal*; L34-142_
- inherits: `IIssueDetails`
- desc: Detailed issue information
- L37 _public property_ `public IIssue Issue { get; }` — (inheritdoc)
- L40 _public property_ `public IUser? Owner { get; }` — (inheritdoc)
- L43 _public property_ `public IUser? NominatedBy { get; }` — (inheritdoc)
- L46 _public property_ `public IUser? ResolvedBy { get; }` — (inheritdoc)
- L49 _public property_ `public IUser? RootCauseOwner { get; }` — (inheritdoc)
- L52 _public property_ `public IUser? QuarantinedBy { get; set; }` — (inheritdoc)
- L55 _public property_ `public DateTime? QuarantineTimeUtc { get; set; }` — (inheritdoc)
- L58 _public property_ `public IUser? ForceClosedBy { get; set; }` — (inheritdoc)
- L61 _public property_ `public string? ExternalIssueKey { get; }` — (inheritdoc)
- L64 _public property_ `public IReadOnlyList<IIssueSpan> Spans { get; }` — (inheritdoc)
- L67 _public property_ `public IReadOnlyList<IIssueStep> Steps { get; }` — (inheritdoc)
- L70 _public property_ `public IReadOnlyList<IIssueSuspect> Suspects { get; }` — (inheritdoc)
- L73 _public property_ `public IReadOnlyList<IUser> SuspectUsers { get; }` — (inheritdoc)
- L76 _private* field_ `readonly bool _showDesktopAlerts` — (inheritdoc)
- L79 _private* field_ `readonly HashSet<UserId> _notifyUsers` — (inheritdoc)
- L97-122 _public ctor_ `public IssueDetails(IIssue issue, IUser? owner, IUser? nominatedBy, IUser? resolvedBy, IUser? quarantinedBy, IUser? forceClosedBy, IUser? rootCauseOwner, IReadOnlyList<IIssueSpan> spans, IReadOnlyList<IIssueStep> steps, IReadOnlyList<IIssueSuspect> suspects, IReadOnlyList<IUser> suspectUsers, bool showDesktopAlerts, string? externalIssueKey)` — Constructor
- L128-131 _public method_ `public bool ShowNotifications()` — Determines whether the given user should be notified about the given issue
- L138-141 _public method_ `public bool IncludeForUser(UserId userId)` — Determines if the issue is relevant to the given user

#### class `HordeServer.Issues.IssueService`  
`public sealed class IssueService : IHostedService, IAsyncDisposable`  
_public; L147-2117_
- inherits: `IHostedService, IAsyncDisposable`
- desc: Wraps functionality for manipulating build health issues
- L197 _private* field_ `readonly JobService _jobService`
- L198 _private* field_ `readonly IJobStepRefCollection _jobStepRefs`
- L199 _private* field_ `readonly IIssueCollection _issueCollection`
- L200 _private* field_ `readonly ICommitService _commitService`
- L201 _private* field_ `readonly IUserCollection _userCollection`
- L202 _private* field_ `readonly ILogCollection _logCollection`
- L203 _private* field_ `readonly IClock _clock`
- L204 _private* field_ `readonly ITicker _ticker`
- L205 _private* field_ `readonly Channel<CompleteStep> _completeSteps`
- L206 _private* field_ `readonly BackgroundTask _completeStepUpdateTask`
- L211 _public property_ `public IIssueCollection Collection => ...` — Accessor for the issue collection
- L216 _public delegate_ `public delegate void IssueUpdatedEvent(IIssue issue)` — Delegate for issue creation events
- L221 _public event_ `public event IssueUpdatedEvent? OnIssueUpdated`
- L224 _private* field_ `readonly (Type Type, IssueHandlerAttribute Attribute)[] _handlerTypes`
- L229 _private* field_ `IReadOnlyList<IIssueDetails> _cachedIssues = new List<IIssueDetails>()` — Cached list of currently open issues
- L234 _private* field_ `Dictionary<StreamId, HashSet<TemplateId>> _cachedDesktopAlerts = ...` — Cache of templates to show desktop alerts for
- L234 _private* field_ `Dictionary< _cachedDesktopAlerts = new Dictionary<StreamId, HashSet<TemplateId>>()` — Cache of templates to show desktop alerts for
- L239 _private* field_ `readonly Tracer _tracer` — Tracer
- L244 _private* field_ `readonly ILogger<IssueService> _logger` — Logger for tracing
- L249 _public property_ `public IReadOnlyList<IIssueDetails> CachedOpenIssues => ...` — Accessor for list of cached open issues
- L251 _private* field_ `readonly IOptionsMonitor<BuildConfig> _buildConfig`
- L252 _private* field_ `readonly IRcaEnqueuer? _rcaEnqueuer`
- L257-292 _public ctor_ `public IssueService(JobService jobService, IIssueCollection issueCollection, ICommitService commitService, IJobStepRefCollection jobStepRefs, IUserCollection userCollection, ILogCollection logCollection, IClock clock, IOptionsMonitor<BuildConfig> buildConfig, Tracer tracer, ILogger<IssueService> logger, IRcaEnqueuer? rcaEnqueuer = null)` — Constructor
- L295-301 _public method_ `public async Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L304-312 _public method_ `public async Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L315-319 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L321-327 _private* method_ `void OnJobStepComplete(IJob job, IGraph graph, JobStepBatchId batchId, JobStepId stepId)`
- L334-402 _private* method_ `async ValueTask TickAsync(CancellationToken cancellationToken)` — Periodically update the list of cached open issues
- L405-418 _public method_ `public async Task<IIssueDetails?> GetCachedIssueDetailsAsync(int issueId, CancellationToken cancellationToken = default)` — (inheritdoc)
- L421-447 _public method_ `public async Task<IIssueDetails> GetIssueDetailsAsync(IIssue issue, CancellationToken cancellationToken = default)` — (inheritdoc)
- L450-471 _public method_ `public bool ShowDesktopAlertsForIssue(IIssue issue, IReadOnlyList<IIssueSpan> spans)` — (inheritdoc)
- L501-583 _public method_ `public async Task<bool> UpdateIssueAsync(int id, string? summary = null, string? description = null, bool? promoted = null, UserId? ownerId = null, UserId? nominatedById = null, bool? acknowledged = null, UserId? declinedById = null, CommitId? fixCommitId = null, bool? fixSystemic = null, CommitId? rootCommitId = null, UserId? rootCauseOwnerId = null, string? rootCauseCategory = null, string? rootCauseSummary = null, int? duplicateIssueId = null, UserId? resolvedById = null, List<ObjectId>? addSpanIds = null, List<ObjectId>? removeSpanIds = null, string? externalIssueKey = null, UserId? quarantinedById = null, UserId? forceClosedById = null, UserId? initiatedById = null, Uri? workflowThreadUrl = null, CancellationToken cancellationToken = default)` — Updates the state of an issue
- L585-618 _private* method_ `async Task UpdateCompleteStepsAsync(CancellationToken cancellationToken)`
- L620-726 _internal method_ `internal async Task UpdateCompleteStepAsync(IJob job, IGraph graph, JobStepBatchId batchId, JobStepId stepId, CancellationToken cancellationToken = default)`
- L739-873 _private* method_ `async Task<HashSet<IssueEventGroupInternal>> GetEventGroupsForStepAsync(IJob job, IJobStepBatch batch, IJobStep step, INode node, IReadOnlyNodeAnnotations annotations, WorkflowConfig? workflow, CancellationToken cancellationToken)` — Gets a set of events for the given step
- L888-943 _private* method_ `async Task<bool> AddEventsToExistingSpansAsync(IJob job, IJobStepBatch batch, IJobStep step, HashSet<IssueEventGroupInternal> newEventGroups, IReadOnlyList<IIssueSpan> openSpans, HashSet<ObjectId> checkedSpanIds, IReadOnlyNodeAnnotations? annotations, bool promoteByDefault, CancellationToken cancellationToken)` — Adds events to open spans
- L950-966 _private* method_ `static IssueSeverity GetIssueSeverity(IEnumerable<IssueEvent> events)` — Gets an issue severity from its events
- L973-990 _private* method_ `static void EmitIssueAuditLogs(ILogger auditLogger, List<IssueEventGroupInternal> eventGroups)` — Dedupes and emits all buffered audit log entries in the event groups
- L1006-1075 _private* method_ `async Task<bool> AddEventsToNewSpansAsync(StreamConfig streamConfig, IJob job, IJobStepBatch batch, IJobStep step, INode node, List<IIssueSpan> openSpans, HashSet<IssueEventGroupInternal> newEventGroups, IReadOnlyNodeAnnotations? annotations, bool promoteByDefault, CancellationToken cancellationToken)` — Adds new spans for the given events
- L1077 _internal method_ `internal Task<IIssue?> UpdateDerivedDataAsync(int issueId, CancellationToken cancellationToken)`
- L1080-1088 _private* method_ `async Task<IIssue?> UpdateIssueDerivedDataAsync(int issueId, CancellationToken cancellationToken)`
- L1090-1096 _private* method_ `static void GetChangeMap(IIssueSpan span, Dictionary<CommitId, CommitIdWithOrder> originChangeToSuspectChange)`
- L1098-1109 _private* method_ `static int CompareSpans(Dictionary<CommitId, CommitIdWithOrder> originChangeToSuspectChange, IIssueSpan span)`
- L1111-1140 _internal method_ `internal static List<IIssueSpan> FindMergeOriginSpans(IReadOnlyList<IIssueSpan> spans)`
- L1142-1320 _private* method_ `async Task<IIssue?> UpdateIssueDerivedDataAsync(IIssue issue, CancellationToken cancellationToken)`
- L1325-1350 _private* method_ `async Task<bool> HasFixFailedAsync(IEnumerable<IIssueSpan> spans, CommitId? fixCommit, DateTime resolvedAt, IReadOnlyList<NewIssueStream> streams, CancellationToken cancellationToken)` — Determine if an issue should be marked as fix failed
- L1355-1371 _private* method_ `async ValueTask<bool> ContainsFixChangeAsync(BuildConfig buildConfig, StreamId streamId, CommitId fixChange, Dictionary<(StreamId, CommitId), bool> cachedContainsFixChange, CancellationToken cancellationToken)` — Figure out if a stream contains a fix changelist
- L1376 _private* const_ `const int MaxFilesForSuspects = 100` — Maximum number of files to look at when looking for suspects
- L1390-1693 _private* method_ `async Task<(List<NewIssueSpanSuspectData> Suspects, int? MaxRank)> FindSuspectsForSpanAsync(StreamConfig streamConfig, IIssueFingerprint fingerprint, CommitId lastSuccess, DateTime lastSuccessTime, CommitId firstFailure, DateTime firstFailureTime, ILogger? issueLogger, CancellationToken cancellationToken)` — Find suspects that can match a given span
- L1695-1737 _private* method_ `static async ValueTask<int> GetChangeScoreAsync(ICommit commit, FileFilter filter, HashSet<string> suspectFiles, HashSet<string> suspectNotes, HashSet<string> suspectSymbols, Tracer tracer, ILogger? issueLogger)`
- L1746-1764 _private* method_ `static int CalculateTheoreticalMaxScore(HashSet<string> suspectFiles, HashSet<string> suspectSymbols)` — Calculate the theoretical maximum score for a fingerprint. Used for early exit optimization when the best possible score has been achieved.
- L1772-1792 _private* method_ `async Task<IIssue> FindOrAddIssueForSpanAsync(IIssueSpan span, CancellationToken cancellationToken)` — Find an existing issue that may match one of the given suspect changes
- L1801-1846 _private* method_ `async Task<IIssue> FindOrAddIssueForSpanAsync(NewIssueSpanData span, ILogger? issueLogger, CancellationToken cancellationToken)` — Find an existing issue that may match one of the given suspect changes
- L1852-1901 _private* method_ `async Task<IIssue?> TryFindIssueByFingerprintFallbackAsync(NewIssueSpanData span, ILogger? issueLogger, CancellationToken cancellationToken)` — Attempt to find a matching issue by fingerprint when no suspects were found. This helps prevent duplicate issues when the commit range exceeds MaxChanges.
- L1907-1939 _private* method_ `static int CalculateFingerprintMatchScore(IIssueFingerprint spanFingerprint, IIssueFingerprint issueFingerprint)` — Calculate a match score between two fingerprints. Higher scores indicate stronger matches.
- L1947-1979 _private* method_ `static string GetSummary(IIssueFingerprint fingerprint, IssueSeverity severity)` — Gets the summary text for a particular fingerprint
- L1981-2022 _private* method_ `static bool TryAppendSummaryVar(ReadOnlySpan<char> name, IIssueFingerprint fingerprint, IssueSeverity severity, StringBuilder summary)`
- L2024 _private* field_ `static readonly IssueMetadata s_duplicateEventIdMetadata = new IssueMetadata("EventId", KnownLogEvents.Linker_DuplicateSymbol.Id.ToString())`
- L2026-2054 _private* method_ `static string GetSymbolIssueSummary(IIssueFingerprint fingerprint, IssueSeverity severity)`
- L2066-2116 _private* method_ `async Task<bool> TryUpdateSentinelsAsync(IReadOnlyList<IIssueSpan> spans, StreamConfig streamConfig, IJob job, IJobStepBatch batch, IJobStep step, CancellationToken cancellationToken)` — Update the sentinels for the given list of issues

#### class `HordeServer.Issues.IssueService.IssueEventInternal`  
`class IssueEventInternal : IssueEvent`  
_private*; L149-167_
- inherits: `IssueEvent`
- L151 _public property_ `public ILogAnchor Anchor { get; }`
- L152 _public property_ `public ILogEventData EventData { get; }`
- L154-159 _public ctor_ `public IssueEventInternal(ILogAnchor anchor, ILogEventData logEventData) : base(anchor.LineIndex, GetLogLevelFromSeverity(logEventData.Severity), logEventData.EventId, logEventData.Lines)`
- L161 _private* method_ `static LogLevel GetLogLevelFromSeverity(LogEventSeverity severity)`

#### class `HordeServer.Issues.IssueService.IssueEventGroupInternal`  
`class IssueEventGroupInternal`  
_private*; L169-193_
- L171 _public property_ `public int Id { get; }`
- L172 _public property_ `public NewIssueFingerprint Fingerprint { get; }`
- L173 _public property_ `public List<IssueEventInternal> Events { get; }`
- L175 _private* field_ `static int s_nextId = 1`
- L177-181 _public ctor_ `public IssueEventGroupInternal(NewIssueFingerprint fingerprint)`
- L183-189 _public method_ `public IssueEventGroupInternal MergeWith(IssueEventGroupInternal otherGroup)`
- L192 _public method_ `public override string ToString()` — (inheritdoc)

#### record `HordeServer.Issues.IssueService.CompleteStep`  
`record class CompleteStep(JobId JobId, JobStepBatchId BatchId, JobStepId StepId)`  
_private*; L195-195_

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Issues/IssueTagService.cs` (HordeServer.Build)


#### class `HordeServer.Issues.IssueTagService`  
`public sealed class IssueTagService : IHostedService, IAsyncDisposable`  
_public; L22-173_
- inherits: `IHostedService, IAsyncDisposable`
- desc: Polls revision control for fix changelist numbers in commits using the syntax '#horde 1234'
- L31 _private* field_ `readonly ISingletonDocument<State> _state`
- L32 _private* field_ `readonly ICommitService _commitService`
- L33 _private* field_ `readonly IIssueCollection _issueCollection`
- L34 _private* field_ `readonly IOptionsMonitor<BuildConfig> _buildConfig`
- L35 _private* field_ `readonly ITicker _ticker`
- L36 _private* field_ `readonly ILogger _logger`
- L41-49 _public ctor_ `public IssueTagService(IMongoService mongoService, ICommitService commitService, IIssueCollection issueCollection, IClock clock, IOptionsMonitor<BuildConfig> buildConfig, ILogger<IssueTagService> logger)` — Constructor
- L52 _public method_ `public ValueTask DisposeAsync()` — (inheritdoc)
- L55 _public method_ `public Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L58 _public method_ `public Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L60-103 _private* method_ `async ValueTask TickAsync(CancellationToken cancellationToken)`
- L105-118 _private* method_ `async Task TickStreamGuardedAsync(StreamConfig streamConfig, State initialState, CancellationToken cancellationToken)`
- L120-154 _private* method_ `async ValueTask TickStreamAsync(StreamConfig streamConfig, State initialState, CancellationToken cancellationToken)`
- L156-172 _internal method_ `internal static IEnumerable<int> ParseTags(string issueFixedTag, string description)`

#### class `HordeServer.Issues.IssueTagService.State`  
`class State : SingletonBase`  
_private*; L25-29_
- attrs: `[SingletonDocument("issue-tags")]`
- inherits: `SingletonBase`
- L28 _public property_ `public Dictionary<StreamId, CommitId> Streams { get; set; }` — attrs: `[BsonElement("streams"), BsonDictionaryOptions(DictionaryRepresentation.ArrayOfDocuments)]`

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Issues/IssueTelemetry.cs` (HordeServer.Build)


#### record `HordeServer.Issues.IssueTelemetry`  
`public record IssueTelemetry : AbstractTelemetryRecord`  
_public; L23-207_
- attrs: `[AnalyticsTableGen] [TelemetryEvent(DefaultEventName)] [Table("horde.state_issue", Schema = "ingest")]`
- inherits: `AbstractTelemetryRecord`
- desc: Record used for Issue telemetry. Models a IIssue.
- L28 _public const_ `public const string DefaultEventName = "State.Issue"` — Default event name for the IssueTelemetry.
- L33 _public const_ `public const string DefaultContext = "Horde"` — Default context for the Horde Issue Telemetry.
- L38 _public field_ `public static readonly int CurrentSchemaVersion = 4` — Current schema version.
- L44 _public property_ `public string Context { get; init; }` — attrs: `[Column("context")]` — The context for this issue telemetry.
- L50 _public property_ `public int Id { get; init; }` — attrs: `[Column("id")]` — The issue ID.
- L56 _public property_ `public DateTime? AcknowledgedAt { get; init; }` — attrs: `[Column("acknowledged_at")]` — The time the issue was acknowledged.
- L62 _public property_ `public DateTime CreatedAt { get; init; }` — attrs: `[Column("created_at")]` — The time the issue was created.
- L68 _public property_ `public UserId? OwnerId { get; init; }` — attrs: `[Column("owner_id")]` — The owner of the issue.
- L74 _public property_ `public string? ExternalIssueKey { get; init; }` — attrs: `[Column("external_issue_key")]` — The external issue key (e.g., Jira ticket).
- L80 _public property_ `public CommitId? FixChange { get; init; }` — attrs: `[Column("fix_change")]` — The commit that fixed this issue.
- L86 _public property_ `public bool FixedSystemic { get; init; }` — attrs: `[Column("fixed_systemic")]` — Whether the fix was systemic.
- L92 _public property_ `public CommitId? RootChange { get; init; }` — attrs: `[Column("root_change")]` — The root commit that caused this issue.
- L98 _public property_ `public DateTime LastSeenAt { get; init; }` — attrs: `[Column("last_seen_at")]` — The time the issue was last seen.
- L104 _public property_ `public DateTime? NominatedAt { get; init; }` — attrs: `[Column("nominated_at")]` — The time the issue was nominated.
- L110 _public property_ `public UserId? NominatedById { get; init; }` — attrs: `[Column("nominated_by_id")]` — The user who nominated the issue.
- L116 _public property_ `public DateTime? ResolvedAt { get; init; }` — attrs: `[Column("resolved_at")]` — The time the issue was resolved.
- L122 _public property_ `public UserId? ResolvedById { get; init; }` — attrs: `[Column("resolved_by_id")]` — The user who resolved the issue.
- L128 _public property_ `public IssueSeverity Severity { get; init; }` — attrs: `[Column("severity")]` — The severity of the issue.
- L134 _public property_ `public string Summary { get; init; }` — attrs: `[Column("summary")]` — The summary of the issue.
- L140 _public property_ `public DateTime? VerifiedAt { get; init; }` — attrs: `[Column("verified_at")]` — The time the issue was verified.
- L146 _public property_ `public int? DuplicateIssueId { get; init; }` — attrs: `[Column("duplicate_issue_id")]` — The ID of the duplicate issue, if any.
- L152 _public property_ `public UserId? RootCauseOwnerId { get; init; }` — attrs: `[Column("root_cause_owner_id")]` — The owner of the root cause.
- L158 _public property_ `public string? RootCauseCategory { get; init; }` — attrs: `[Column("root_cause_category")]` — The category of the root cause.
- L164 _public property_ `public string? RootCauseSummary { get; init; }` — attrs: `[Column("root_cause_summary")]` — The summary of the root cause.
- L170-178 _public ctor_ `public IssueTelemetry() : base(DefaultEventName, CurrentSchemaVersion)` — Default constructor for an empty telemetry object.
- L183-206 _public ctor_ `public IssueTelemetry(IIssue issue) : base(DefaultEventName, CurrentSchemaVersion)` — Telemetry payload for IIssue.

#### record `HordeServer.Issues.FingerprintTelemetry`  
`public record FingerprintTelemetry`  
_public; L215-257_
- attrs: `[AnalyticsTableGen] [Table("default")]`
- desc: Record used for IssueFingerprint telemetry. Models a IIssueFingerprint.
- L221 _public property_ `public string Type { get; init; }` — attrs: `[Column("type")]` — The type of the fingerprint.
- L227 _public property_ `public IReadOnlySet<IssueKey> Keys { get; init; }` — attrs: `[Column("keys")]` — The keys associated with the fingerprint.
- L232-236 _public ctor_ `public FingerprintTelemetry()` — Default constructor for ORM mapping.
- L243-247 _public ctor_ `public FingerprintTelemetry(string type, IReadOnlySet<IssueKey> keys)` — Constructor.
- L253-256 _public ctor_ `public FingerprintTelemetry(IIssueFingerprint issueFingerprint) : this(issueFingerprint.Type, issueFingerprint.Keys)` — Constructor.

#### record `HordeServer.Issues.FailureInfoTelemetry`  
`public record FailureInfoTelemetry`  
_public; L265-316_
- attrs: `[AnalyticsTableGen] [Table("default")]`
- desc: Record used for FailureInfo telemetry.
- L271 _public property_ `public JobId JobId { get; init; }` — attrs: `[Column("job_id")]` — The job ID.
- L277 _public property_ `public string JobName { get; init; }` — attrs: `[Column("job_name")]` — The job name.
- L283 _public property_ `public CommitIdWithOrder Change { get; init; }` — attrs: `[Column("change")]` — The change/commit information.
- L289 _public property_ `public ObjectId StepId { get; init; }` — attrs: `[Column("step_id")]` — The step ID.
- L294-300 _public ctor_ `public FailureInfoTelemetry()` — Default constructor for ORM mapping.
- L309-315 _public ctor_ `public FailureInfoTelemetry(JobId jobId, string jobName, CommitIdWithOrder change, ObjectId stepId)` — Constructor.

#### record `HordeServer.Issues.IssueSpanTelemetry`  
`public record IssueSpanTelemetry : AbstractTelemetryRecord`  
_public; L325-417_
- attrs: `[AnalyticsTableGen] [TelemetryEvent(DefaultEventName)] [Table("horde.state_issue_span", Schema = "ingest")]`
- inherits: `AbstractTelemetryRecord`
- desc: Record used for IssueSpan telemetry. Models a IIssueSpan.
- L330 _public const_ `public const string DefaultEventName = "State.IssueSpan"` — Default event name for the IssueSpanTelemetry.
- L335 _public field_ `public static readonly int CurrentSchemaVersion = 1` — Current schema version.
- L341 _public property_ `public ObjectId Id { get; init; }` — attrs: `[Column("id")]` — The issue span ID.
- L347 _public property_ `public int IssueId { get; init; }` — attrs: `[Column("issue_id")]` — The issue ID this span belongs to.
- L353 _public property_ `public FingerprintTelemetry Fingerprint { get; init; }` — attrs: `[Column("fingerprint")]` — The fingerprint of the issue span.
- L359 _public property_ `public FailureInfoTelemetry FirstFailure { get; init; }` — attrs: `[Column("first_failure")]` — The first failure in this span.
- L365 _public property_ `public FailureInfoTelemetry? LastFailure { get; init; }` — attrs: `[Column("last_failure")]` — The last failure in this span.
- L371 _public property_ `public StreamId StreamId { get; init; }` — attrs: `[Column("stream_id")]` — The stream ID.
- L377 _public property_ `public string StreamName { get; init; }` — attrs: `[Column("stream_name")]` — The stream name.
- L383 _public property_ `public TemplateId TemplateRefId { get; init; }` — attrs: `[Column("template_ref_id")]` — The template ref ID.
- L389-398 _public ctor_ `public IssueSpanTelemetry() : base(DefaultEventName, CurrentSchemaVersion)` — Default constructor for an empty telemetry object.
- L404-416 _public ctor_ `public IssueSpanTelemetry(IIssueSpan issueSpan) : base(DefaultEventName, CurrentSchemaVersion)` — Constructor.

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Issues/IssuesController.cs` (HordeServer.Build)


#### class `HordeServer.Issues.IssuesController`  
`public class IssuesController : HordeControllerBase`  
_public; L33-1035_
- attrs: `[Authorize] [ApiController] [Route("[controller]")]`
- inherits: `HordeControllerBase`
- desc: Controller for the /api/v1/issues endpoint
- L35 _private field_ `private readonly IIssueCollection _issueCollection`
- L36 _private field_ `private readonly IssueService _issueService`
- L37 _private field_ `private readonly IExternalIssueService _externalIssueService`
- L38 _private field_ `private readonly JobService _jobService`
- L39 _private field_ `private readonly IUserCollection _userCollection`
- L40 _private field_ `private readonly ILogCollection _logCollection`
- L41 _private field_ `private readonly IOptionsSnapshot<BuildConfig> _buildConfig`
- L42 _private field_ `private readonly ILogger<IssuesController> _logger`
- L47-57 _public ctor_ `public IssuesController(IIssueCollection issueCollection, IssueService issueService, JobService jobService, IUserCollection userCollection, ILogCollection logCollection, IExternalIssueService externalIssueService, IOptionsSnapshot<BuildConfig> buildConfig, ILogger<IssuesController> logger)` — Constructor
- L75-205 _public method_ `public async Task<ActionResult<object>> FindIssuesV2Async([FromQuery(Name = "Id")] int[]? ids = null, [FromQuery] StreamId? streamId = null, [FromQuery] CommitId? minChange = null, [FromQuery] CommitId? maxChange = null, [FromQuery] bool? resolved = null, [FromQuery] int index = 0, [FromQuery] int count = 10, [FromQuery] PropertyFilter? filter = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v2/issues")] [ProducesResponseType(typeof(List<FindIssueResponse>), 200)]` — Retrieve information about a specific issue
- L207-223 _private* method_ `static FindIssueSpanResponse NewFindIssueSpanResponse(IIssueSpan span, WorkflowId? workflowId)`
- L225-237 _private* method_ `static GetIssueStepResponse NewGetIssueStepResponse(IIssueStep issueStep)`
- L251-298 _private* method_ `static FindIssueResponse NewFindIssueResponse(IIssue issue, IUser? owner, IUser? nominatedBy, IUser? resolvedBy, IUser? quarantinedBy, IUser? rootCauseOwner, IssueSeverity? streamSeverity, List<FindIssueSpanResponse> spans, List<WorkflowId> openWorkflows)` — Constructs a new issue
- L323-375 _public method_ `public async Task<ActionResult<object>> FindIssuesAsync([FromQuery(Name = "Id")] int[]? ids = null, [FromQuery] string? streamId = null, [FromQuery] CommitId? change = null, [FromQuery] CommitId? minChange = null, [FromQuery] CommitId? maxChange = null, [FromQuery] JobId? jobId = null, [FromQuery] JobStepBatchId? batchId = null, [FromQuery] JobStepId? stepId = null, [FromQuery(Name = "label")] int? labelIdx = null, [FromQuery] string? ownerId = null, [FromQuery] bool? resolved = null, [FromQuery] bool? promoted = null, [FromQuery] int index = 0, [FromQuery] int count = 10, [FromQuery] PropertyFilter? filter = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/issues")] [ProducesResponseType(typeof(List<GetIssueResponse>), 200)]` — Retrieve information about a specific issue
- L387-401 _public method_ `public async Task<ActionResult<object>> GetIssueAsync(int issueId, [FromQuery] PropertyFilter? filter = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/issues/{issueId}")] [ProducesResponseType(typeof(GetIssueResponse), 200)]` — Retrieve information about a specific issue
- L414-420 _public method_ `public async Task GetAgentHistoryAsync(int issueId, [FromQuery] DateTime? minTime = null, [FromQuery] DateTime? maxTime = null, [FromQuery] int index = 0, [FromQuery] int count = 50)` — attrs: `[HttpGet] [Route("/api/v1/issues/{issueId}/history")]` — Retrieve historical information about a specific issue
- L428-444 _private* method_ `GetIssueResponse CreateIssueResponse(IIssueDetails details, bool showDesktopAlerts)` — Create an issue response object
- L452-485 _private* method_ `static GetIssueAffectedStreamResponse NewGetIssueAffectedStreamResponse(IIssueDetails details, StreamConfig? streamConfig, IEnumerable<IIssueSpan> spans)` — Constructor
- L494-502 _private* method_ `static GetIssueAffectedTemplateResponse NewGetIssueAffectedTemplateResponse(TemplateId templateId, string templateName, bool resolved, IssueSeverity severity = IssueSeverity.Unspecified)` — Constructor
- L510-574 _private* method_ `static GetIssueResponse NewGetIssueResponse(IIssueDetails details, List<GetIssueAffectedStreamResponse> affectedStreams, bool showDesktopAlerts)` — Constructs a new issue
- L586-609 _public method_ `public async Task<ActionResult<List<object>>> GetIssueStreamsAsync(int issueId, [FromQuery] PropertyFilter? filter = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/issues/{issueId}/streams")] [ProducesResponseType(typeof(List<GetIssueStreamResponse>), 200)]` — Retrieve events for a specific issue
- L611-629 _private* method_ `static GetIssueStreamResponse NewGetIssueStreamResponse(StreamId streamId, List<IIssueSpan> spans, List<IIssueStep> steps)`
- L631-642 _private* method_ `static GetIssueSpanResponse NewGetIssueSpanResponse(IIssueSpan span, List<IIssueStep> steps)`
- L655-681 _public method_ `public async Task<ActionResult<object>> GetIssueStreamAsync(int issueId, StreamId streamId, [FromQuery] PropertyFilter? filter = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/issues/{issueId}/streams/{streamId}")] [ProducesResponseType(typeof(List<GetIssueStreamResponse>), 200)]` — Retrieve events for a specific issue
- L700-794 _public method_ `public async Task<ActionResult<List<object>>> GetIssueEventsAsync( int issueId, [FromQuery] JobId? jobId = null, [FromQuery] JobStepBatchId? batchId = null, [FromQuery] JobStepId? stepId = null, [FromQuery(Name = "label")] int? labelIdx = null, [FromQuery] string[]? logIds = null, [FromQuery] int index = 0, [FromQuery] int count = 10, [FromQuery] PropertyFilter? filter = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/issues/{issueId}/events")] [ProducesResponseType(typeof(List<GetLogEventResponse>), 200)]` — Retrieve events for a specific issue
- L801-811 _private method_ `private bool AuthorizeIssue(IIssueDetails issue)` — Authorize the current user to see an issue
- L821-886 _public method_ `public async Task<ActionResult> UpdateIssueAsync(int issueId, [FromBody] UpdateIssueRequest request)` — attrs: `[HttpPut] [Route("/api/v1/issues/{issueId}")]` — Update an issue
- L896-924 _public method_ `public async Task<ActionResult<List<GetExternalIssueResponse>>> GetExternalIssuesAsync([FromQuery] StreamId streamId, [FromQuery] string[] keys, CancellationToken cancellationToken)` — attrs: `[HttpGet] [Authorize] [Route("/api/v1/issues/external")]` — Get external issue information for provided keys
- L926-938 _private* method_ `static GetExternalIssueResponse NewGetExternalIssueResponse(IExternalIssue issue)`
- L946-978 _public method_ `public async Task<ActionResult<CreateExternalIssueResponse>> CreateExternalIssueAsync([FromBody] CreateExternalIssueRequest issueRequest, CancellationToken cancellationToken)` — attrs: `[HttpPost] [Authorize] [Route("/api/v1/issues/external")]` — Create a new external issue
- L989-1015 _public method_ `public async Task<ActionResult<List<GetExternalIssueProjectResponse>>> GetExternalIssueProjectsAsync([FromQuery] string streamId, CancellationToken cancellationToken)` — attrs: `[HttpGet] [Authorize] [Route("/api/v1/issues/external/projects")]` — Gets external issue tracking projects associated with the provided stream
- L1025-1034 _private* method_ `static GetExternalIssueProjectResponse NewGetExternalIssueProjectResponse(string key, string name, string id, Dictionary<string, string> components, Dictionary<string, string> issueTypes)` — Constructor

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Issues/RcaQueueService.cs` (HordeServer.Build)


#### class `HordeServer.Issues.RcaQueueService`  
`public sealed class RcaQueueService : IRcaEnqueuer, IHostedService, IAsyncDisposable`  
_public; L21-215_
- inherits: `IRcaEnqueuer, IHostedService, IAsyncDisposable`
- desc: Redis-backed queue for RCA processing requests. Ensures every eligible issue gets processed with retry support and crash resilience.
- L26 _private* const_ `const int MaxRetries = 3` — Maximum number of retry attempts before discarding a queue item
- L31 _private* field_ `static readonly TimeSpan s_minimumAge = TimeSpan.FromSeconds(5)` — Minimum age before a queue item is processed, to allow audit logs to be emitted after issue creation
- L39 _private* field_ `static readonly RedisListKey<RcaQueueItem> s_rcaQueue = "rca/queue"`
- L41 _private* field_ `readonly IRedisService _redisService`
- L45 _private* field_ `readonly Lazy<IRcaProcessor?> _rcaProcessor`
- L46 _private* field_ `readonly IIssueCollection _issueCollection`
- L47 _private* field_ `readonly IOptionsMonitor<BuildConfig> _buildConfig`
- L48 _private* field_ `readonly ITicker _ticker`
- L49 _private* field_ `readonly ILogger<RcaQueueService> _logger`
- L54-62 _public ctor_ `public RcaQueueService(IRedisService redisService, IIssueCollection issueCollection, IClock clock, IOptionsMonitor<BuildConfig> buildConfig, ILogger<RcaQueueService> logger, Lazy<IRcaProcessor?> rcaProcessor)` — Constructor
- L65 _public method_ `public ValueTask DisposeAsync()` — (inheritdoc)
- L68 _public method_ `public Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L71 _public method_ `public Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L74-91 _public method_ `public async Task EnqueueAsync(int issueId, StreamId streamId, WorkflowId? workflowId, CancellationToken cancellationToken)` — (inheritdoc)
- L93-153 _private* method_ `async ValueTask ProcessQueueAsync(CancellationToken cancellationToken)`
- L155-192 _private* method_ `async Task ProcessItemAsync(RcaQueueItem item, CancellationToken cancellationToken)`
- L194-214 _private* method_ `bool IsEligibleForRca(RcaQueueItem item)`

#### record `HordeServer.Issues.RcaQueueService.RcaQueueItem`  
`record class RcaQueueItem(int IssueId, string StreamId, string? WorkflowId, int RetryCount, DateTime EnqueuedUtc)`  
_private*; L37-37_
- attrs: `[RedisConverter(typeof(RedisJsonConverter<>))]`
- desc: Item stored in the Redis RCA queue

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Issues/WorkflowConfig.cs` (HordeServer.Build)


#### class `HordeServer.Issues.WorkflowConfig`  
`public class WorkflowConfig : IWorkflow`  
_public; L14-105_
- inherits: `IWorkflow`
- desc: Configuration for an issue workflow
- L17 _public property_ `public WorkflowId Id { get; set; }` — (inheritdoc)
- L20 _public property_ `public List<TimeSpan> ReportTimes { get; set; }` — (inheritdoc)
- L21 _private* property_ `IReadOnlyList<TimeSpan> IWorkflow.ReportTimes => ...`
- L24 _public property_ `public string? SummaryTab { get; set; }` — (inheritdoc)
- L27 _public property_ `public string? ReportChannel { get; set; }` — (inheritdoc)
- L30 _public property_ `public bool ReportWarnings { get; set; }` — (inheritdoc)
- L33 _public property_ `public bool GroupIssuesByTemplate { get; set; }` — (inheritdoc)
- L36 _public property_ `public string? TriageChannel { get; set; }` — (inheritdoc)
- L39 _public property_ `public string? TriagePrefix { get; set; }` — (inheritdoc)
- L42 _public property_ `public string? TriageSuffix { get; set; }` — (inheritdoc)
- L45 _public property_ `public string? TriageInstructions { get; set; }` — (inheritdoc)
- L48 _public property_ `public string? TriageAlias { get; set; }` — (inheritdoc)
- L51 _public property_ `public bool TriageErrors { get; set; }` — (inheritdoc)
- L54 _public property_ `public bool TriageWarnings { get; set; }` — (inheritdoc)
- L57 _public property_ `public Dictionary<string, string>? TriageTypeAliases { get; set; }` — (inheritdoc)
- L58 _private* property_ `IReadOnlyDictionary<string, string>? IWorkflow.TriageTypeAliases => ...`
- L61 _public property_ `public string? EscalateAlias { get; set; }` — (inheritdoc)
- L64 _public property_ `public List<int> EscalateTimes { get; set; }` — (inheritdoc)
- L66 _private* property_ `IReadOnlyList<int> IWorkflow.EscalateTimes => ...`
- L69 _public property_ `public List<int> EscalateRootCauseAnalysisTimes { get; set; }` — (inheritdoc)
- L71 _private* property_ `IReadOnlyList<int> IWorkflow.EscalateRootCauseAnalysisTimes => ...`
- L74 _public property_ `public bool AutoRcaEnabled { get; set; }` — (inheritdoc)
- L77 _public property_ `public bool AutoRcaSlackEnabled { get; set; }` — (inheritdoc)
- L80 _public property_ `public int MaxMentions { get; set; }` — (inheritdoc)
- L83 _public property_ `public bool AllowMentions { get; set; }` — (inheritdoc)
- L86 _public property_ `public bool InviteRestrictedUsers { get; set; }` — (inheritdoc)
- L89 _public property_ `public bool SkipWhenEmpty { get; set; }` — (inheritdoc)
- L92 _public property_ `public bool ShowMergeWarnings { get; set; }` — (inheritdoc)
- L95 _public property_ `public NodeAnnotations Annotations { get; set; }` — (inheritdoc)
- L96 _private* property_ `IReadOnlyNodeAnnotations IWorkflow.Annotations => ...`
- L99 _public property_ `public WorkflowExternalIssuesConfig? ExternalIssues { get; set; }` — (inheritdoc)
- L100 _private* property_ `IWorkflowExternalIssues? IWorkflow.ExternalIssues => ...`
- L103 _public property_ `public List<string>? IssueHandlers { get; set; }` — (inheritdoc)
- L104 _private* property_ `IReadOnlyList<string>? IWorkflow.IssueHandlers => ...`

#### class `HordeServer.Issues.WorkflowExternalIssuesConfig`  
`public class WorkflowExternalIssuesConfig : IWorkflowExternalIssues`  
_public; L110-123_
- inherits: `IWorkflowExternalIssues`
- desc: External issue tracking configuration for a workflow
- L114 _public property_ `public string ProjectKey { get; set; }` — attrs: `[Required]` — (inheritdoc)
- L118 _public property_ `public string DefaultComponentId { get; set; }` — attrs: `[Required]` — (inheritdoc)
- L122 _public property_ `public string DefaultIssueTypeId { get; set; }` — attrs: `[Required]` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/Bisect/BisectController.cs` (HordeServer.Build)


#### class `HordeServer.Jobs.Bisect.CreateBisectTaskRequest`  
`public class CreateBisectTaskRequest`  
_public; L27-69_
- desc: Request to create a new bisect task
- L32 _public property_ `public JobId JobId { get; set; }` — Job containing the node to check
- L37 _public property_ `public string NodeName { get; set; }` — Name of the node to query
- L42 _public property_ `public List<CommitTag>? CommitTags { get; set; }` — Commit tag to filter possible changes against
- L48-52 _public property_ `public List<int>? IgnoreChanges { get; set; }` — attrs: `[Obsolete("Use IgnoreCommitIds instead")]` — Set of changes to ignore. Can be modified later through UpdateBisectTaskRequest.
- L53 _private* field_ `List<int>? _ignoreChanges`
- L58-62 _public property_ `public List<CommitId>? IgnoreCommitIds { get; set; }` — Set of changes to ignore. Can be modified later through UpdateBisectTaskRequest.
- L63 _private* field_ `List<CommitId>? _ignoreCommitIds`
- L68 _public property_ `public List<JobId>? IgnoreJobs { get; set; }` — Set of jobs to ignore. Can be modified later through UpdateBisectTaskRequest.

#### class `HordeServer.Jobs.Bisect.CreateBisectTaskResponse`  
`public class CreateBisectTaskResponse`  
_public; L74-82_
- desc: Response from creating a bisect task
- L79 _public property_ `public BisectTaskId BisectTaskId { get; }` — Identifier for the new bisect task
- L81 _internal ctor_ `internal CreateBisectTaskResponse(IBisectTask bisectTask)`

#### class `HordeServer.Jobs.Bisect.GetBisectTaskResponse`  
`public class GetBisectTaskResponse`  
_public; L87-189_
- desc: Information about a bisect task
- L89 _private* field_ `readonly IBisectTask _bisectTask`
- L92 _public property_ `public BisectTaskId Id => ...` — (inheritdoc)
- L95 _public property_ `public BisectTaskState State => ...` — (inheritdoc)
- L98 _public property_ `public GetThinUserInfoResponse? Owner { get; }` — (inheritdoc)
- L101 _public property_ `public StreamId StreamId => ...` — (inheritdoc)
- L104 _public property_ `public TemplateId TemplateId => ...` — (inheritdoc)
- L107 _public property_ `public string NodeName => ...` — (inheritdoc)
- L110 _public property_ `public JobStepOutcome Outcome => ...` — (inheritdoc)
- L113 _public property_ `public string InitialJobId => ...` — Initial Job Id
- L116 _public property_ `public string InitialBatchId => ...` — Initial Job Batch Id
- L119 _public property_ `public string InitialStepId => ...` — Initial Job Step Id
- L123 _public property_ `public int InitialChange => ...` — attrs: `[Obsolete("Use InitialCommitId instead")]` — (inheritdoc)
- L126 _public property_ `public CommitIdWithOrder InitialCommitId => ...` — (inheritdoc)
- L129 _public property_ `public string? MinJobId => ...` — Min Job Id
- L132 _public property_ `public string? MinBatchId => ...` — Min Job Batch Id
- L135 _public property_ `public string? MinStepId => ...` — Min Job Step Id
- L139 _public property_ `public int? MinChange => ...` — attrs: `[Obsolete("Use MinCommitId instead")]` — (inheritdoc)
- L142 _public property_ `public CommitIdWithOrder? MinCommitId => ...` — (inheritdoc)
- L145 _public property_ `public string CurrentJobId => ...` — Current Job Id
- L148 _public property_ `public string CurrentBatchId => ...` — Current Job Batch Id
- L151 _public property_ `public string CurrentStepId => ...` — Current Job Step Id
- L155 _public property_ `public int CurrentChange => ...` — attrs: `[Obsolete("Use CurrentCommit instead")]` — (inheritdoc)
- L158 _public property_ `public CommitIdWithOrder CurrentCommitId => ...` — (inheritdoc)
- L163 _public property_ `public JobId? NextJobId { get; }` — The next job id for a running bisection task
- L169 _public property_ `public int? NextJobChange => ...` — attrs: `[Obsolete("Use NextJobCommit instead")]` — The next job change
- L174 _public property_ `public CommitIdWithOrder? NextJobCommit { get; }` — The next job change
- L179 _public property_ `public List<GetJobStepRefResponse> Steps { get; }` — The steps involved in the bisection
- L181-188 _internal ctor_ `internal GetBisectTaskResponse(IBisectTask bisectTask, GetThinUserInfoResponse? owner, List<IJobStepRef> steps, IJob? nextJob)`

#### class `HordeServer.Jobs.Bisect.UpdateBisectTaskRequest`  
`public class UpdateBisectTaskRequest`  
_public; L194-252_
- desc: Updates the state of a bisect task
- L199 _public property_ `public bool? Cancel { get; set; }` — Cancels the current task
- L205-209 _public property_ `public List<int> IncludeChanges { get; set; }` — attrs: `[Obsolete("Use IncludeCommits instead")]` — List of change numbers to include in the search.
- L210 _private* field_ `List<int>? _includeChanges`
- L215-219 _public property_ `public List<CommitId> IncludeCommitIds { get; set; }` — List of commits to include in the search.
- L220 _private* field_ `List<CommitId>? _includeCommitIds`
- L226-230 _public property_ `public List<int> ExcludeChanges { get; set; }` — attrs: `[Obsolete("Use ExcludeCommitIds instead")]` — List of change numbers to exclude from the search.
- L231 _private* field_ `List<int>? _excludeChanges`
- L236-240 _public property_ `public List<CommitId> ExcludeCommitIds { get; set; }` — List of commits to exclude from the search
- L241 _private* field_ `List<CommitId>? _excludeCommitIds`
- L246 _public property_ `public List<JobId> IncludeJobs { get; set; }` — List of jobs to include in the search.
- L251 _public property_ `public List<JobId> ExcludeJobs { get; set; }` — List of jobs to exclude from the search.

#### class `HordeServer.Jobs.Bisect.BisectTasksController`  
`public class BisectTasksController : HordeControllerBase`  
_public; L260-603_
- attrs: `[ApiController] [Authorize] [Route("[controller]")]`
- inherits: `HordeControllerBase`
- desc: Controller for the /api/v1/bisect endpoint
- L262 _private* field_ `readonly IBisectTaskCollection _bisectTaskCollection`
- L263 _private* field_ `readonly IJobCollection _jobCollection`
- L264 _private* field_ `readonly JobService _jobService`
- L265 _private* field_ `readonly IJobStepRefCollection _jobStepRefs`
- L266 _private* field_ `readonly IGraphCollection _graphCollection`
- L267 _private* field_ `readonly IUserCollection _userCollection`
- L268 _private* field_ `readonly IOptionsSnapshot<BuildConfig> _buildConfig`
- L269 _private* field_ `readonly IOptions<BuildServerConfig> _staticConfig`
- L270 _private field_ `private readonly ILogger<BisectTasksController> _logger`
- L271 _private* field_ `readonly Tracer _tracer`
- L276-288 _public ctor_ `public BisectTasksController(IBisectTaskCollection bisectTaskCollection, JobService jobService, IJobCollection jobCollection, IJobStepRefCollection jobStepRefs, IGraphCollection graphCollection, IUserCollection userCollection, Tracer tracer, ILogger<BisectTasksController> logger, IOptionsSnapshot<BuildConfig> buildConfig, IOptions<BuildServerConfig> staticConfig)` — Constructor
- L298-377 _public method_ `public async Task<ActionResult<CreateBisectTaskResponse>> CreateAsync([FromBody] CreateBisectTaskRequest create, CancellationToken cancellationToken = default)` — attrs: `[HttpPost] [Route("/api/v1/bisect")]` — Creates a new bisect task
- L387-411 _public method_ `public async Task<ActionResult<GetBisectTaskResponse>> GetAsync([FromRoute] BisectTaskId bisectTaskId, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/bisect/{bisectTaskId}")]` — Gets information about a bisection task
- L422-469 _public method_ `public async Task<ActionResult> UpdateAsync([FromRoute] BisectTaskId bisectTaskId, [FromBody] UpdateBisectTaskRequest request, CancellationToken cancellationToken)` — attrs: `[HttpPatch] [Route("/api/v1/bisect/{bisectTaskId}")]` — Creates a new bisect task
- L471-491 _private* method_ `async Task<GetBisectTaskResponse> CreateBisectTaskResponseAsync(IBisectTask task, CancellationToken cancellationToken = default)`
- L501-528 _public method_ `public async Task<ActionResult<List<GetBisectTaskResponse>>> GetJobBisectTasksAsync([FromRoute] JobId jobId, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/bisect/job/{jobId}")]` — Gets the bisections run on a specific job
- L537-602 _public method_ `public async Task<ActionResult<List<GetBisectTaskResponse>>> FindBisectTasksAsync( [FromQuery(Name = "id")] string[]? ids = null, [FromQuery] string? ownerId = null, [FromQuery] string? jobId = null, [FromQuery] DateTimeOffset? minCreateTime = null, [FromQuery] DateTimeOffset? maxCreateTime = null, [FromQuery] int index = 0, [FromQuery] int count = 100, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/bisect")] [ProducesResponseType(typeof(List<GetBisectTaskResponse>), 200)]` — Gets bisection tasks based on specified criteria

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/Bisect/BisectIdUtils.cs` (HordeServer.Build)


#### class `HordeServer.Jobs.Bisect.BisectTaskIdUtils`  
`static class BisectTaskIdUtils`  
_internal*; L11-17_
- desc: Server helper methods for BisectTaskId
- L16 _public method_ `public static BisectTaskId GenerateNewId()` — Creates a new BisectTaskId

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/Bisect/BisectService.cs` (HordeServer.Build)


#### class `HordeServer.Jobs.Bisect.BisectService`  
`class BisectService : IHostedService`  
_internal*; L19-212_
- inherits: `IHostedService`
- L21 _private* field_ `readonly IBisectTaskCollection _bisectTaskCollection`
- L22 _private* field_ `readonly IJobCollection _jobCollection`
- L23 _private* field_ `readonly IJobStepRefCollection _jobStepRefCollection`
- L24 _private* field_ `readonly ITemplateCollectionInternal _templateCollection`
- L25 _private* field_ `readonly IGraphCollection _graphCollection`
- L26 _private* field_ `readonly ICommitService _commitService`
- L27 _private* field_ `readonly IOptionsMonitor<BuildConfig> _buildConfig`
- L28 _private* field_ `readonly IOptions<BuildServerConfig> _staticConfig`
- L29 _private* field_ `readonly ILogger _logger`
- L30 _private* field_ `readonly ITicker _ticker`
- L32-44 _public ctor_ `public BisectService(IBisectTaskCollection bisectTaskCollection, IJobCollection jobCollection, IJobStepRefCollection jobStepRefCollection, ITemplateCollectionInternal templateCollection, IGraphCollection graphCollection, ICommitService commitService, IOptionsMonitor<BuildConfig> buildConfig, IOptions<BuildServerConfig> staticConfig, IClock clock, ILogger<BisectService> logger)`
- L47-50 _public method_ `public async Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L53-56 _public method_ `public async Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L58-85 _private* method_ `async ValueTask TickAsync(CancellationToken cancellationToken)`
- L87-181 _private* method_ `async Task<BisectTaskState?> TryUpdateBisectTaskAsync(IBisectTask bisectTask, BuildConfig buildConfig, CancellationToken cancellationToken)`
- L183-211 _private* method_ `async Task<(IJobStepRef? Current, IJobStepRef? Next)> GetBisectRangeAsync(IBisectTask bisectTask, CancellationToken cancellationToken)`

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/Bisect/BisectTaskAclAction.cs` (HordeServer.Build)


#### class `HordeServer.Jobs.Bisect.BisectTaskAclAction`  
`public static class BisectTaskAclAction`  
_public; L10-26_
- desc: ACL actions valid for manipulating jobs
- L15 _public property_ `public static AclAction CreateBisectTask { get; }` — Ability to start new bisect tasks
- L20 _public property_ `public static AclAction UpdateBisectTask { get; }` — Ability to update a bisect task
- L25 _public property_ `public static AclAction ViewBisectTask { get; }` — Ability to view a bisect task

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/Bisect/BisectTaskCollection.cs` (HordeServer.Build)


#### class `HordeServer.Jobs.Bisect.BisectTaskCollection`  
`class BisectTaskCollection : IBisectTaskCollection`  
_internal*; L20-301_
- inherits: `IBisectTaskCollection`
- L118 _private* field_ `readonly Tracer _tracer`
- L119 _private* field_ `readonly IMongoCollection<BisectTaskDoc> _bisectTasks`
- L120 _private* field_ `readonly MongoIndex<BisectTaskDoc> _runningIndex`
- L122-131 _public ctor_ `public BisectTaskCollection(Tracer tracer, IMongoService mongoService)`
- L134-170 _public method_ `public async Task<IBisectTask> CreateAsync(IJob job, JobStepBatchId batchId, JobStepId stepId, string nodeName, JobStepOutcome outcome, UserId ownerId, CreateBisectTaskOptions? options, CancellationToken cancellationToken = default)` — (inheritdoc)
- L173-191 _public method_ `public async IAsyncEnumerable<IBisectTask> FindActiveAsync([EnumeratorCancellation] CancellationToken cancellationToken = default)` — (inheritdoc)
- L194-197 _public method_ `public async Task<IBisectTask?> GetAsync(BisectTaskId bisectTaskId, CancellationToken cancellationToken = default)` — (inheritdoc)
- L200-238 _public method_ `public async Task<IReadOnlyList<IBisectTask>> FindAsync(BisectTaskId[]? taskIds = null, JobId? jobId = null, UserId? ownerId = null, DateTime? minCreateTime = null, DateTime? maxCreateTime = null, int? index = null, int? count = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L241-300 _public method_ `public async Task<IBisectTask?> TryUpdateAsync(IBisectTask bisectTask, UpdateBisectTaskOptions options, CancellationToken cancellationToken = default)` — (inheritdoc)

#### class `HordeServer.Jobs.Bisect.BisectTaskCollection.BisectTaskDoc`  
`class BisectTaskDoc : IBisectTask`  
_private*; L22-116_
- inherits: `IBisectTask`
- L24 _public property_ `public BisectTaskId Id { get; set; }`
- L27 _public property_ `public bool? Running { get; set; }` — attrs: `[BsonElement("running"), BsonIgnoreIfNull]`
- L30 _public property_ `public BisectTaskState State { get; set; }` — attrs: `[BsonElement("state")]`
- L33 _public property_ `public UserId OwnerId { get; set; }` — attrs: `[BsonElement("oid")]`
- L36 _public property_ `public StreamId StreamId { get; set; }` — attrs: `[BsonElement("sid")]`
- L39 _public property_ `public TemplateId TemplateId { get; set; }` — attrs: `[BsonElement("tid")]`
- L42 _public property_ `public string NodeName { get; set; }` — attrs: `[BsonElement("step")]`
- L45 _public property_ `public JobStepOutcome Outcome { get; set; }` — attrs: `[BsonElement("out")]`
- L48 _public property_ `public JobId InitialJobId { get; set; }` — attrs: `[BsonElement("ijobid")]`
- L51 _public property_ `public JobStepRefId InitialJobStep { get; set; }` — attrs: `[BsonElement("ijob")]`
- L54-58 _public property_ `public CommitIdWithOrder InitialCommitId { get; set; }` — attrs: `[BsonIgnore]`
- L61 _public property_ `public string? InitialCommitName { get; set; }` — attrs: `[BsonElement("icom")]`
- L64 _public property_ `public int InitialCommitOrder { get; set; }` — attrs: `[BsonElement("ichg")]`
- L67 _public property_ `public JobStepRefId CurrentJobStep { get; set; }` — attrs: `[BsonElement("curjob")]`
- L70-74 _public property_ `public CommitIdWithOrder CurrentCommitId { get; set; }` — attrs: `[BsonIgnore]`
- L77 _public property_ `public string? CurrentCommitName { get; set; }` — attrs: `[BsonElement("curCom")]`
- L80 _public property_ `public int CurrentCommitOrder { get; set; }` — attrs: `[BsonElement("curChg")]`
- L84 _public property_ `public JobStepRefId? MinJobStep { get; set; }` — attrs: `[BsonElement("minJob"), BsonIgnoreIfNull]`
- L86-90 _public property_ `public CommitIdWithOrder? MinCommitId { get; set; }`
- L93 _public property_ `public string? MinCommitName { get; set; }` — attrs: `[BsonElement("minCom"), BsonIgnoreIfNull]`
- L96 _public property_ `public int? MinCommitOrder { get; set; }` — attrs: `[BsonElement("minChg"), BsonIgnoreIfNull]`
- L99 _public property_ `public List<JobStepRefId> Steps { get; set; }` — attrs: `[BsonElement("steps")]`
- L100 _private* property_ `IReadOnlyList<JobStepRefId> IBisectTask.Steps => ...`
- L103 _public property_ `public int UpdateIdx { get; set; }` — attrs: `[BsonElement("idx")]`
- L106 _public property_ `public List<CommitTag>? CommitTags { get; set; }` — attrs: `[BsonElement("tags"), BsonIgnoreIfNull]`
- L107 _private* property_ `IReadOnlyList<CommitTag>? IBisectTask.CommitTags => ...`
- L110 _public property_ `public HashSet<CommitId> IgnoreCommitIds { get; set; }` — attrs: `[BsonElement("nochg")]`
- L111 _private* property_ `IReadOnlySet<CommitId> IBisectTask.IgnoreCommitIds => ...`
- L114 _public property_ `public HashSet<JobId> IgnoreJobs { get; set; }` — attrs: `[BsonElement("nojob")]`
- L115 _private* property_ `IReadOnlySet<JobId> IBisectTask.IgnoreJobIds => ...`

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/Bisect/IBisectTask.cs` (HordeServer.Build)


#### enum `HordeServer.Jobs.Bisect.BisectTaskState`  
`public enum BisectTaskState`  
_public; L15-51_
- desc: State of a bisect task
- L20 _public* enumerator_ `Running` — Currently running
- L25 _public* enumerator_ `Cancelled` — Cancelled by a user
- L30 _public* enumerator_ `Succeeded` — Finished running. The first job/change identifies the first failure.
- L35 _public* enumerator_ `MissingHistory` — Task failed due to not having a job before the first failure.
- L40 _public* enumerator_ `MissingStream` — Task failed due to the stream no longer existing.
- L45 _public* enumerator_ `MissingJob` — Task failed due to the first job no longer existing.
- L50 _public* enumerator_ `MissingTemplate` — Task failed due to template no longer existing.

#### interface `HordeServer.Jobs.Bisect.IBisectTask`  
`public interface IBisectTask`  
_public; L56-142_
- desc: State of a search for a build breakage
- L61 _public property_ `public BisectTaskId Id { get; }` — Identifier for this task
- L66 _public property_ `public BisectTaskState State { get; }` — Current task state
- L71 _public property_ `public UserId OwnerId { get; }` — User that initiated the search
- L76 _public property_ `public StreamId StreamId { get; }` — Stream being searched
- L81 _public property_ `public TemplateId TemplateId { get; }` — Template within the stream to execute
- L86 _public property_ `public string NodeName { get; }` — Name of the step to search for
- L91 _public property_ `public JobStepOutcome Outcome { get; }` — Outcome to search for
- L96 _public property_ `public JobStepRefId InitialJobStep { get; }` — Starting job id for the bisection
- L101 _public property_ `public CommitIdWithOrder InitialCommitId { get; }` — Starting change for the bisection
- L106 _public property_ `public JobStepRefId CurrentJobStep { get; }` — First known job id that is broken
- L111 _public property_ `public CommitIdWithOrder CurrentCommitId { get; }` — Changelist number of the first broken job id
- L116 _public property_ `public JobStepRefId? MinJobStep { get; }` — Lower bound of bisection job Id
- L121 _public property_ `public CommitIdWithOrder? MinCommitId { get; }` — Lower bound of bisection changelist number
- L126 _public property_ `public IReadOnlyList<JobStepRefId> Steps { get; }` — The steps involved in the bisection
- L131 _public property_ `public IReadOnlyList<CommitTag>? CommitTags { get; }` — Tags to filter changes to consider for this task
- L136 _public property_ `public IReadOnlySet<CommitId> IgnoreCommitIds { get; }` — Set of changes to ignore while doing the bisection
- L141 _public property_ `public IReadOnlySet<JobId> IgnoreJobIds { get; }` — Set of jobs to ignore while doing the bisection

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/Bisect/IBisectTaskCollection.cs` (HordeServer.Build)


#### interface `HordeServer.Jobs.Bisect.IBisectTaskCollection`  
`public interface IBisectTaskCollection`  
_public; L15-66_
- desc: Manages a collection of bisect tasks
- L29 _public method_ `public Task<IBisectTask> CreateAsync(IJob job, JobStepBatchId batchId, JobStepId stepId, string nodeName, JobStepOutcome outcome, UserId ownerId, CreateBisectTaskOptions? options = null, CancellationToken cancellationToken = default)` — Creates a new bisect task
- L36 _public method_ `public IAsyncEnumerable<IBisectTask> FindActiveAsync(CancellationToken cancellationToken = default)` — Finds all the active bisect tasks
- L50 _public method_ `public Task<IReadOnlyList<IBisectTask>> FindAsync(BisectTaskId[]? taskIds = null, JobId? jobId = null, UserId? ownerId = null, DateTime? minCreateTime = null, DateTime? maxCreateTime = null, int? index = null, int? count = null, CancellationToken cancellationToken = default)` — Finds all bisect tasks for the provided criteria
- L57 _public method_ `public Task<IBisectTask?> GetAsync(BisectTaskId bisectTaskId, CancellationToken cancellationToken = default)` — Gets a bisect task by id
- L65 _public method_ `public Task<IBisectTask?> TryUpdateAsync(IBisectTask bisectTask, UpdateBisectTaskOptions options, CancellationToken cancellationToken = default)` — Updates the state of a bisect task

#### class `HordeServer.Jobs.Bisect.CreateBisectTaskOptions`  
`public class CreateBisectTaskOptions`  
_public; L71-87_
- desc: Settings for creating a new bisect task
- L76 _public property_ `public IReadOnlyList<CommitTag>? CommitTags { get; set; }` — Filter the changes considered for the bisection
- L81 _public property_ `public IReadOnlyList<CommitId>? IgnoreCommitIds { get; set; }` — Changes to exclude from the bisection
- L86 _public property_ `public IReadOnlyList<JobId>? IgnoreJobIds { get; set; }` — Jobs to exclude from the bisection

#### class `HordeServer.Jobs.Bisect.UpdateBisectTaskOptions`  
`public class UpdateBisectTaskOptions`  
_public; L92-133_
- desc: Settings for updating a bisect task
- L97 _public property_ `public (JobStepRefId Step, CommitIdWithOrder CommitId)? CurrentJobStep { get; set; }` — First job to bisect from
- L102 _public property_ `public (JobStepRefId Step, CommitIdWithOrder CommitId)? MinJobStep { get; set; }` — The lower bounds of the bisection task
- L107 _public property_ `public BisectTaskState? State { get; set; }` — New state for the task
- L112 _public property_ `public JobStepRefId? NewJobStep { get; set; }` — New job step to add to bisection
- L117 _public property_ `public IReadOnlyList<CommitId>? IncludeCommitIds { get; set; }` — Changes to include in the bisection
- L122 _public property_ `public IReadOnlyList<CommitId>? ExcludeCommitIds { get; set; }` — Changes to exclude from the bisection
- L127 _public property_ `public IReadOnlyList<JobId>? IncludeJobs { get; set; }` — Jobs to include in the bisection
- L132 _public property_ `public IReadOnlyList<JobId>? ExcludeJobs { get; set; }` — Jobs to exclude from the bisection

#### class `HordeServer.Jobs.Bisect.BisectTaskCollectionExtensions`  
`static class BisectTaskCollectionExtensions`  
_internal*; L135-164_
- L137-163 _public method_ `public static async Task UpdateAsync(this IBisectTaskCollection bisectTasks, IJob job, IJobStepBatch batch, IJobStep step, IGraph graph, ILogger? logger = null, CancellationToken cancellationToken = default)`

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/DebugJobsController.cs` (HordeServer.Build)


#### class `HordeServer.Jobs.DebugJobsController`  
`public class DebugJobsController : HordeControllerBase`  
_public; L27-453_
- attrs: `[ApiController] [Authorize] [DebugEndpoint] [Tags("Debug")]`
- inherits: `HordeControllerBase`
- desc: Debug functionality for jobs
- L29 _private field_ `private readonly JobService _jobService`
- L30 _private field_ `private readonly JobTaskSource _jobTaskSource`
- L31 _private field_ `private readonly ILeaseCollection _leaseCollection`
- L32 _private field_ `private readonly IOptionsSnapshot<BuildConfig> _buildConfig`
- L33 _private field_ `private readonly ILogger<DebugJobsController> _logger`
- L38-50 _public ctor_ `public DebugJobsController( JobService jobService, JobTaskSource jobTaskSource, ILeaseCollection leaseCollection, IOptionsSnapshot<BuildConfig> buildConfig, ILogger<DebugJobsController> logger)` — Constructor
- L58-66 _public method_ `public ActionResult<object> GetQueueStatus()` — attrs: `[HttpGet] [Route("/api/v1/debug/queue")]` — Returns diagnostic information about the current state of the queue
- L74-125 _public method_ `public ActionResult GetJobOptions([FromQuery] string? format = "html")` — attrs: `[HttpGet] [Route("/api/v1/debug/job-options")]` — Display a table listing each template with what job options are enabled
- L127-146 _private method_ `private ActionResult GetJobOptionsAsCsv(List<PropertyInfo> jobOptionsProps)`
- L178-243 _public method_ `public async Task<ActionResult> GetJobTimingsAsync( [FromQuery] DateTimeOffset? minCreateTime = null, [FromQuery] DateTimeOffset? maxCreateTime = null, [FromQuery] bool onlySetupBuild = false, [FromQuery] string? format = "html")` — attrs: `[HttpGet] [Route("/api/v1/debug/job-timings")]` — Display a table listing each template with job timings (setup, work and teardown durations)
- L245-263 _private method_ `private static ActionResult GetJobTimingsAsCsv(IEnumerable<JobTiming> jobTimings)`
- L265-308 _private method_ `private async Task<List<JobTiming>> CalculateJobTimingsAsync(IEnumerable<IJob> jobs)`
- L310-327 _private method_ `private static IReadOnlyList<JobTiming> GroupJobTimings(IEnumerable<JobTiming> jobTimings)`
- L334-359 _public method_ `public async Task<ActionResult> RepairJobsAsync([FromQuery] DateTime? minTime, [FromQuery] DateTime? maxTime)` — attrs: `[HttpPost] [Route("/api/v1/debug/repair-jobs")]` — Repairs any inconsistencies with jobs created in a particular time range
- L367-399 _public method_ `public async Task<ActionResult> RepairJobAsync(JobId jobId)` — attrs: `[HttpPost] [Route("/api/v1/debug/repair-job/{jobId}")]` — Repairs any inconsistencies with a particular job
- L401-426 _private* method_ `async Task<IJob?> TryRepairJobAsync(StreamConfig streamConfig, IJob job, CancellationToken cancellationToken)`
- L434-452 _public method_ `public async Task<ActionResult> DebugBatchUpdateAsync(string jobId, string batchId)` — attrs: `[HttpGet] [Route("/api/v1/debug/batchupdate/{JobId}/{BatchId}")]` — Forces an update of a job's batches to debug issues such as updating dependencies

#### record `HordeServer.Jobs.DebugJobsController.JobTiming`  
`record JobTiming( string StreamId, string TemplateId, string Name, IReadOnlySet<string> StepNames, TimeSpan BatchSetupDuration, TimeSpan BatchWorkDuration, TimeSpan BatchTeardownDuration)`  
_private*; L148-170_
- L157-169 _public method_ `public JobTiming Merge(JobTiming jt)`

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/Graphs/GraphCollection.cs` (HordeServer.Build)


#### class `HordeServer.Jobs.Graphs.GraphCollection`  
`public sealed class GraphCollection : IGraphCollection, IDisposable`  
_public; L21-547_
- inherits: `IGraphCollection, IDisposable`
- desc: Collection of graph documents
- L431 _private* field_ `readonly IMongoCollection<GraphDocument> _graphs` — The jobs collection
- L436 _private* const_ `const int MaxGraphs = 2000` — Maximum number of graphs to keep in the cache
- L442 _private field_ `private readonly MemoryCache _memoryCache = new MemoryCache(new MemoryCacheOptions() { SizeLimit = MaxGraphs })` — Cache for graphs Use a non-shared cache to ensure enough space for graphs
- L447-450 _public ctor_ `public GraphCollection(IMongoService mongoService)` — Constructor
- L453-456 _public method_ `public void Dispose()` — (inheritdoc)
- L464-480 _private* method_ `async Task AddAsync(GraphDocument graph, CancellationToken cancellationToken)` — Adds a new graph document
- L483-491 _public method_ `public async Task<IGraph> AddAsync(ITemplate template, CancellationToken cancellationToken)` — (inheritdoc)
- L494-499 _public method_ `public async Task<IGraph> AppendAsync(IGraph? baseGraph, List<NewGroup>? newGroupRequests, List<NewAggregate>? newAggregateRequests, List<NewLabel>? newLabelRequests, List<NewGraphArtifact>? newArtifactRequests, CancellationToken cancellationToken)` — (inheritdoc)
- L502-520 _public method_ `public async Task<IGraph> GetAsync(ContentHash? hash, CancellationToken cancellationToken)` — (inheritdoc)
- L523-546 _public method_ `public async Task<List<IGraph>> FindAllAsync(ContentHash[]? hashes, int? index, int? count, CancellationToken cancellationToken)` — (inheritdoc)

#### class `HordeServer.Jobs.Graphs.GraphCollection.Node`  
`class Node : INode`  
_private*; L27-101_
- attrs: `[DebuggerDisplay("{Name}")]`
- inherits: `INode`
- desc: Represents a node in the graph
- L30 _public property_ `public string Name { get; set; }` — attrs: `[BsonRequired]`
- L33 _public property_ `public NodeOutputRef[]? Inputs { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L36 _public property_ `public NodeOutputRef[]? OptionalInputs { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L39 _public property_ `public string[]? OutputNames { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L42 _public property_ `public NodeRef[] InputDependencies { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L45 _public property_ `public NodeRef[]? OptionalInputDependencies { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L48 _public property_ `public NodeRef[] OrderDependencies { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L50 _public property_ `public Priority Priority { get; set; }`
- L51 _public property_ `public bool AllowRetry { get; set; }`
- L52 _public property_ `public bool RunEarly { get; set; }`
- L53 _public property_ `public bool Warnings { get; set; }`
- L56 _public property_ `public Dictionary<string, string>? Credentials { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L59 _public property_ `public Dictionary<string, string>? Properties { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L63 _public property_ `public NodeAnnotations? Annotations { get; set; }` — attrs: `[BsonIgnoreIfNull] [BsonDictionaryOptions(DictionaryRepresentation.ArrayOfDocuments)]`
- L65 _private* property_ `IReadOnlyList<NodeOutputRef> INode.Inputs => ...`
- L66 _private* property_ `IReadOnlyList<NodeOutputRef> INode.OptionalInputs => ...`
- L67 _private* property_ `IReadOnlyList<string> INode.OutputNames => ...`
- L68 _private* property_ `IReadOnlyDictionary<string, string>? INode.Credentials => ...`
- L69 _private* property_ `IReadOnlyDictionary<string, string>? INode.Properties => ...`
- L70 _private* property_ `NodeRef[] INode.OptionalInputDependencies => ...`
- L71 _private* property_ `IReadOnlyNodeAnnotations INode.Annotations => ...`
- L74-79 _private ctor_ `private Node()` — attrs: `[BsonConstructor]`
- L81-100 _public ctor_ `public Node(string name, NodeOutputRef[]? inputs, NodeOutputRef[]? optionalInputs, string[]? outputNames, NodeRef[] inputDependencies, NodeRef[]? optionalInputDependencies, NodeRef[] orderDependencies, Priority priority, bool allowRetry, bool runEarly, bool warnings, Dictionary<string, string>? credentials, Dictionary<string, string>? properties, IReadOnlyNodeAnnotations? annotations)`

#### class `HordeServer.Jobs.Graphs.GraphCollection.NodeGroup`  
`class NodeGroup : INodeGroup`  
_private*; L103-130_
- inherits: `INodeGroup`
- L105 _public property_ `public string AgentType { get; set; }`
- L106 _public property_ `public List<Node> Nodes { get; set; }`
- L108 _private* property_ `IReadOnlyList<INode> INodeGroup.Nodes => ...`
- L114-118 _private ctor_ `private NodeGroup()` — attrs: `[BsonConstructor]` — Private constructor for BSON serializer
- L125-129 _public ctor_ `public NodeGroup(string agentType, List<Node> nodes)` — Constructor

#### class `HordeServer.Jobs.Graphs.GraphCollection.Aggregate`  
`class Aggregate : IAggregate`  
_private*; L132-150_
- inherits: `IAggregate`
- L134 _public property_ `public string Name { get; set; }`
- L135 _public property_ `public List<NodeRef> Nodes { get; set; }`
- L137 _private* property_ `IReadOnlyList<NodeRef> IAggregate.Nodes => ...`
- L139-143 _private ctor_ `private Aggregate()`
- L145-149 _public ctor_ `public Aggregate(string name, List<NodeRef> nodes)`

#### class `HordeServer.Jobs.Graphs.GraphCollection.Label`  
`class Label : ILabel`  
_private*; L152-197_
- inherits: `ILabel`
- L155 _public property_ `public string? Name { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L158 _public property_ `public string? Category { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L161 _public property_ `public string? DashboardName { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L164 _public property_ `public string? DashboardCategory { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L167 _public property_ `public string? UgsName { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L170 _public property_ `public string? UgsProject { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L173 _public property_ `public LabelChange Change { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L175 _public property_ `public List<NodeRef> RequiredNodes { get; set; }`
- L176 _public property_ `public List<NodeRef> IncludedNodes { get; set; }`
- L178 _private* property_ `string? ILabel.DashboardName => ...`
- L179 _private* property_ `string? ILabel.DashboardCategory => ...`
- L181-185 _private ctor_ `private Label()`
- L187-196 _public ctor_ `public Label(string? dashboardName, string? dashboardCategory, string? ugsName, string? ugsProject, LabelChange change, List<NodeRef> requiredNodes, List<NodeRef> includedNodes)`

#### class `HordeServer.Jobs.Graphs.GraphCollection.GraphArtifact`  
`class GraphArtifact : IGraphArtifact`  
_private*; L199-232_
- inherits: `IGraphArtifact`
- L201 _public property_ `public ArtifactName Name { get; set; }`
- L202 _public property_ `public ArtifactType Type { get; set; }`
- L203 _public property_ `public string Description { get; set; }`
- L204 _public property_ `public string BasePath { get; set; }`
- L205 _public property_ `public List<string> Keys { get; set; }`
- L206 _public property_ `public List<string> Metadata { get; set; }`
- L207 _public property_ `public string? NodeName { get; set; }`
- L208 _public property_ `public string? OutputName { get; set; }`
- L210 _private* property_ `IReadOnlyList<string> IGraphArtifact.Keys => ...`
- L211 _private* property_ `IReadOnlyList<string> IGraphArtifact.Metadata => ...`
- L213-219 _private ctor_ `private GraphArtifact()`
- L221-231 _public ctor_ `public GraphArtifact(ArtifactName name, ArtifactType type, string description, string basePath, IReadOnlyList<string> keys, IReadOnlyList<string> metadata, string? nodeName, string? outputName)`

#### class `HordeServer.Jobs.Graphs.GraphCollection.GraphDocument`  
`class GraphDocument : IGraph`  
_private*; L234-426_
- inherits: `IGraph`
- L236 _public property_ `public static GraphDocument Empty { get; }`
- L239 _public property_ `public ContentHash Id { get; set; }` — attrs: `[BsonRequired, BsonId]`
- L241 _public property_ `public int Schema { get; set; }`
- L242 _public property_ `public List<NodeGroup> Groups { get; set; }`
- L243 _public property_ `public List<Aggregate> Aggregates { get; set; }`
- L244 _public property_ `public List<Label> Labels { get; set; }`
- L245 _public property_ `public List<GraphArtifact> Artifacts { get; set; }`
- L248 _private* field_ `IReadOnlyDictionary<string, NodeRef>? _cachedNodeNameToRef` — attrs: `[BsonIgnore]`
- L248 _private* field_ `IReadOnlyDictionary< _cachedNodeNameToRef` — attrs: `[BsonIgnore]`
- L251 _private* field_ `IReadOnlyDictionary<string, NodeOutputRef>? _cachedNodeOutputNameToRef` — attrs: `[BsonIgnore]`
- L251 _private* field_ `IReadOnlyDictionary< _cachedNodeOutputNameToRef` — attrs: `[BsonIgnore]`
- L253 _private* property_ `IReadOnlyList<INodeGroup> IGraph.Groups => ...`
- L254 _private* property_ `IReadOnlyList<IAggregate> IGraph.Aggregates => ...`
- L255 _private* property_ `IReadOnlyList<ILabel> IGraph.Labels => ...`
- L256 _private* property_ `IReadOnlyList<IGraphArtifact> IGraph.Artifacts => ...`
- L259-261 _private ctor_ `private GraphDocument()` — attrs: `[BsonConstructor]`
- L263-270 _public ctor_ `public GraphDocument(List<NodeGroup> groups, List<Aggregate> aggregates, List<Label> labels, List<GraphArtifact> artifacts)`
- L272-380 _public ctor_ `public GraphDocument(GraphDocument baseGraph, List<NewGroup>? newGroupRequests, List<NewAggregate>? newAggregateRequests, List<NewLabel>? newLabelRequests, List<NewGraphArtifact>? newArtifactRequests)`
- L382-399 _public method_ `public IReadOnlyDictionary<string, NodeRef> GetNodeNameToRef()`
- L401-425 _public method_ `public IReadOnlyDictionary<string, NodeOutputRef> GetNodeOutputNameToRef()`

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/Graphs/IGraphCollection.cs` (HordeServer.Build)


#### interface `HordeServer.Jobs.Graphs.IGraphCollection`  
`public interface IGraphCollection`  
_public; L12-51_
- desc: Interface for a collection of graph documents
- L20 _public* method_ `Task<IGraph> AddAsync(ITemplate template, CancellationToken cancellationToken = default)` — Adds a graph from a template
- L32 _public* method_ `Task<IGraph> AppendAsync(IGraph? baseGraph, List<NewGroup>? newGroupRequests = null, List<NewAggregate>? newAggregateRequests = null, List<NewLabel>? newLabelRequests = null, List<NewGraphArtifact>? newArtifactRequests = null, CancellationToken cancellationToken = default)` — Creates a graph by appending groups and aggregates to an existing graph.
- L40 _public* method_ `Task<IGraph> GetAsync(ContentHash hash, CancellationToken cancellationToken = default)` — Gets the graph for a job
- L50 _public* method_ `Task<List<IGraph>> FindAllAsync(ContentHash[]? hashes = null, int? index = null, int? count = null, CancellationToken cancellationToken = default)` — Finds all graphs stored in the collection

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/IJobCollection.cs` (HordeServer.Build)


#### class `HordeServer.Jobs.CreateJobOptions`  
`public class CreateJobOptions`  
_public; L21-114_
- desc: Options for creating a new job
- L24 _public property_ `public CommitId? PreflightCommitId { get; set; }` — (inheritdoc)
- L27 _public property_ `public string? PreflightDescription { get; set; }` — (inheritdoc)
- L30 _public property_ `public UserId? StartedByUserId { get; set; }` — (inheritdoc)
- L33 _public property_ `public BisectTaskId? StartedByBisectTaskId { get; set; }` — (inheritdoc)
- L36 _public property_ `public Priority? Priority { get; set; }` — (inheritdoc)
- L39 _public property_ `public bool? AutoSubmit { get; set; }` — (inheritdoc)
- L42 _public property_ `public bool? UpdateIssues { get; set; }` — (inheritdoc)
- L45 _public property_ `public bool? PromoteIssuesByDefault { get; set; }` — (inheritdoc)
- L48 _public property_ `public JobOptions? JobOptions { get; set; }` — (inheritdoc)
- L51 _public property_ `public List<AclClaimConfig> Claims { get; set; }` — (inheritdoc)
- L56 _public property_ `public List<ChainedJobTemplateConfig> JobTriggers { get; }` — List of downstream job triggers
- L59 _public property_ `public bool ShowUgsBadges { get; set; }` — (inheritdoc)
- L62 _public property_ `public bool ShowUgsAlerts { get; set; }` — (inheritdoc)
- L65 _public property_ `public string? NotificationChannel { get; set; }` — (inheritdoc)
- L68 _public property_ `public string? NotificationChannelFilter { get; set; }` — (inheritdoc)
- L71 _public property_ `public Dictionary<ParameterId, string> Parameters { get; }` — (inheritdoc)
- L74 _public property_ `public List<string> Arguments { get; }` — (inheritdoc)
- L77 _public property_ `public List<string>? Targets { get; set; }` — (inheritdoc)
- L80 _public property_ `public List<string> AdditionalArguments { get; }` — (inheritdoc)
- L83 _public property_ `public Dictionary<string, string> Environment { get; }` — (inheritdoc)
- L86 _public property_ `public JobId? ParentJobId { get; set; }` — (inheritdoc)
- L89 _public property_ `public JobStepId? ParentJobStepId { get; set; }` — (inheritdoc)
- L94-96 _public ctor_ `public CreateJobOptions()` — Default constructor
- L101-113 _public ctor_ `public CreateJobOptions(TemplateRefConfig templateRefConfig)` — Constructor

#### interface `HordeServer.Jobs.IJobCollection`  
`public interface IJobCollection`  
_public; L119-225_
- desc: Interface for a collection of job documents
- L135 _public* method_ `Task<IJob> AddAsync(JobId jobId, StreamId streamId, TemplateId templateRefId, ContentHash templateHash, IGraph graph, string name, CommitId commitId, CommitId? codeCommitId, CreateJobOptions options, CancellationToken cancellationToken = default)` — Creates a new job
- L143 _public* method_ `Task<IJob?> GetAsync(JobId jobId, CancellationToken cancellationToken = default)` — Gets a job with the given unique id
- L151 _public* method_ `Task RemoveStreamAsync(StreamId streamId, CancellationToken cancellationToken = default)` — Delete all the jobs for a stream
- L161 _public* method_ `Task<IReadOnlyList<IJob>> FindAsync(FindJobOptions options, int? index = null, int? count = null, CancellationToken cancellationToken = default)` — Searches for jobs matching the given criteria
- L170 _public* method_ `IAsyncEnumerable<IJob> FindBisectTaskJobsAsync(BisectTaskId bisectTaskId, bool? running, CancellationToken cancellationToken = default)` — Searches for jobs matching the given criteria
- L184 _public* method_ `Task<IReadOnlyList<IJob>> FindLatestByStreamWithTemplatesAsync(StreamId streamId, TemplateId[] templates, UserId? preflightStartedByUser = null, DateTimeOffset? maxCreateTime = null, DateTimeOffset? modifiedAfter = null, int? index = null, int? count = null, bool consistentRead = false, CancellationToken cancellationToken = default)` — Searches for jobs in a specified stream and templates
- L193 _public* method_ `Task AddIssueToJobAsync(JobId jobId, int issueId, CancellationToken cancellationToken = default)` — Adds an issue to a job
- L200 _public* method_ `Task<IReadOnlyList<IJob>> GetDispatchQueueAsync(CancellationToken cancellationToken = default)` — Gets a queue of jobs to consider for execution
- L208 _public* method_ `void JobAudit(JobId jobId, string? message, params object?[] args)` — Write to the job's audit log
- L218 _public* method_ `Task<IJob?> UpdateMetadataAsync(JobId jobId, List<string>? jobMetadata = null, Dictionary<JobStepId, List<string>>? stepMetadata = null, CancellationToken cancellationToken = default)` — Update a job and step metadata
- L224 _public* method_ `Task UpgradeDocumentsAsync()` — Upgrade all documents in the collection

#### record `HordeServer.Jobs.FindJobOptions`  
`public record class FindJobOptions ( JobId[]? JobIds = null, StreamId? StreamId = null, string? Name = null, TemplateId[]? Templates = null, CommitId? MinCommitId = null, CommitId? MaxCommitId = null, CommitId? PreflightCommitId = null, bool? PreflightOnly = null, bool? IncludePreflight = null, UserId? PreflightStartedByUser = null, UserId? StartedByUser = null, DateTimeOffset? MinCreateTime = null, DateTimeOffset? MaxCreateTime = null, DateTimeOffset? ModifiedBefore = null, DateTimeOffset? ModifiedAfter = null, string? Target = null, JobStepState[]? State = null, JobStepOutcome[]? Outcome = null, JobStepBatchState? BatchState = null, bool? ExcludeUserJobs = null, bool? ExcludeCancelled = null )`  
_public; L251-251_
- desc: Options for finding jobs

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/IJobStepRefCollection.cs` (HordeServer.Build)


#### interface `HordeServer.Jobs.IJobStepRefCollection`  
`public interface IJobStepRefCollection`  
_public; L18-112_
- desc: Interface for a collection of JobStepRef documents
- L44 _public* method_ `Task<IJobStepRef> InsertOrReplaceAsync(JobStepRefId id, string jobName, string stepName, StreamId streamId, TemplateId templateId, CommitIdWithOrder commitId, LogId? logId, PoolId? poolId, AgentId? agentId, JobStepState? state, JobStepOutcome? outcome, bool updateIssues, CommitIdWithOrder? lastSuccess, CommitIdWithOrder? lastWarning, float waitTime, float initTime, DateTime jobStartTimeUtc, DateTime startTimeUtc, DateTime? finishTimeUtc, List<string>? stepMetadata = null, ILogger? logger = null)` — Inserts or replaces a JobStepRef.
- L54 _public* method_ `Task<IJobStepRef?> UpdateAsync(JobId jobId, JobStepBatchId batchId, JobStepId stepId, List<int>? issueIds)` — Updates a job step ref
- L63 _public* method_ `Task<IJobStepRef?> FindAsync(JobId jobId, JobStepBatchId batchId, JobStepId stepId)` — Gets a specific job step ref
- L71 _public* method_ `Task<List<IJobStepRef>> FindAsync(JobStepRefId[] ids, CancellationToken cancellationToken)` — Gets job step references given an array of ids
- L85 _public* method_ `Task<List<IJobStepRef>> GetStepsForNodeAsync(StreamId streamId, TemplateId templateId, string nodeName, CommitIdWithOrder? commitId, bool includeFailed, int maxCount, bool includePreStartAndSkippedStates, CancellationToken cancellationToken = default)` — Gets the history of a given node
- L98 _public* method_ `Task<IJobStepRef?> GetPrevStepForNodeAsync(StreamId streamId, TemplateId templateId, string nodeName, CommitIdWithOrder commitId, JobStepOutcome? outcome = null, bool? updateIssues = null, IEnumerable<JobId>? excludeJobIds = null)` — Gets the previous job that ran a given step
- L110 _public* method_ `Task<IJobStepRef?> GetNextStepForNodeAsync(StreamId streamId, TemplateId templateId, string nodeName, CommitIdWithOrder commitId, JobStepOutcome? outcome = null, bool? updateIssues = null)` — Gets the next job that ran a given step

#### class `HordeServer.Jobs.JobStepRefCollectionExtensions`  
`static class JobStepRefCollectionExtensions`  
_internal*; L114-169_
- L126-168 _public method_ `public static async Task UpdateAsync(this IJobStepRefCollection jobStepRefs, IJob job, IJobStepBatch batch, IJobStep step, IGraph graph, ILogger? logger = null)` — Updates a job step ref.

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/IWorkspaceMessageEnricher.cs` (HordeServer.Build)


#### interface `HordeServer.Jobs.IWorkspaceMessageEnricher`  
`public interface IWorkspaceMessageEnricher`  
_public; L13-26_
- desc: Interface for enriching workspace messages before they are sent to agents. Plugins can implement this to modify workspace credentials, add custom fields, etc.
- L25 _public* method_ `Task EnrichAsync(RpcAgentWorkspace workspace, AgentWorkspaceInfo workspaceInfo, IAgent agent, IJob job, CancellationToken cancellationToken)` — Enriches a workspace message before it's sent to an agent. Called after the base workspace message is created but before it's assigned to a task.

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/JobAclAction.cs` (HordeServer.Build)


#### class `HordeServer.Jobs.JobAclAction`  
`public static class JobAclAction`  
_public; L10-41_
- desc: ACL actions valid for manipulating jobs
- L15 _public property_ `public static AclAction CreateJob { get; }` — Ability to start new jobs
- L20 _public property_ `public static AclAction UpdateJob { get; }` — Rename a job, modify its priority, etc...
- L25 _public property_ `public static AclAction DeleteJob { get; }` — Delete a job properties
- L30 _public property_ `public static AclAction ExecuteJob { get; }` — Allows updating a job metadata (name, changelist number, step properties, new groups, job states, etc...). Typically granted to agents. Not user facing.
- L35 _public property_ `public static AclAction RetryJobStep { get; }` — Ability to retry a failed job step
- L40 _public property_ `public static AclAction ViewJob { get; }` — Ability to view a job

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/JobCollection.cs` (HordeServer.Build)


#### class `HordeServer.Jobs.JobCollection`  
`public class JobCollection : IJobCollection`  
_public; L46-2958_
- inherits: `IJobCollection`
- desc: Wrapper around the jobs collection in a mongo DB
- L844 _private* const_ `const int MaxRetries = 2` — Maximum number of times a step can be retried (after the original run)
- L846 _private* field_ `readonly IMongoCollection<JobDocument> _jobs`
- L849 _private* field_ `readonly MongoIndex<JobDocument> _streamThenTemplateThenCreationTimeIndex` — attrs: `[SuppressMessage("CodeQuality", "IDE0052:Remove unread private members")]`
- L850 _private* field_ `readonly MongoIndex<JobDocument> _startedByBisectTaskIdIndex`
- L851 _private* field_ `readonly ITelemetryWriter _telemetryWriter`
- L852 _private* field_ `readonly IClock _clock`
- L853 _private* field_ `readonly IGraphCollection _graphCollection`
- L854 _private* field_ `readonly ILogCollection _logCollection`
- L855 _private* field_ `readonly ICommitService _commitService`
- L856 _private* field_ `readonly Tracer _tracer`
- L857 _private* field_ `readonly IOptionsMonitor<BuildConfig> _buildConfig`
- L858 _private* field_ `readonly ILogger<JobCollection> _logger`
- L859 _private* field_ `readonly IAuditLog<JobId> _auditLog`
- L864-888 _public ctor_ `public JobCollection(IMongoService mongoService, IClock clock, IGraphCollection graphCollection, ILogCollection logCollection, ICommitService commitService, ITelemetryWriter telemetryWriter, IOptionsMonitor<BuildConfig> buildConfig, Tracer tracer, ILogger<JobCollection> logger, IAuditLog<JobId> auditLog)` — Constructor
- L895-898 _private* method_ `IAuditLogChannel<JobId> GetJobLogger(JobId jobId)` — Get Job Logger
- L906-918 _public method_ `public void JobAudit(JobId jobId, string? message, params object?[] args)` — Log to a job audit
- L928-940 _private* method_ `static void JobAudit(JobId jobId, ILogger logger, IAuditLogChannel<JobId> jobLogger, string? message, params object?[] args)` — Log to job audit static flavor
- L942-949 _private* method_ `static Task PostLoadAsync(JobDocument job)`
- L951-961 _private* method_ `static JobDocument Clone(JobDocument job)`
- L964-988 _public method_ `public async Task<IJob> AddAsync(JobId jobId, StreamId streamId, TemplateId templateRefId, ContentHash templateHash, IGraph graph, string name, CommitId commitId, CommitId? codeCommitId, CreateJobOptions options, CancellationToken cancellationToken)` — (inheritdoc)
- L991-1001 _public method_ `public async Task<IJob?> GetAsync(JobId jobId, CancellationToken cancellationToken)` — (inheritdoc)
- L1004-1025 _private* method_ `async Task<bool> TryDeleteAsync(JobDocument job, CancellationToken cancellationToken)` — (inheritdoc)
- L1028-1031 _public method_ `public async Task RemoveStreamAsync(StreamId streamId, CancellationToken cancellationToken)` — (inheritdoc)
- L1034-1120 _public method_ `public async Task<IReadOnlyList<IJob>> FindAsync(FindJobOptions options, int? index = null, int? count = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L1125-1128 _private* method_ `static bool WasCancelled(IJob job)` — Test whether a job was cancelled
- L1131-1247 _public method_ `public async Task<IReadOnlyList<IJob>> FindInternalAsync(FindJobOptions options, int? index = null, int? count = null, bool consistentRead = false, string? indexHint = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L1250-1275 _public method_ `public async IAsyncEnumerable<IJob> FindBisectTaskJobsAsync(BisectTaskId bisectTaskId, bool? running, [EnumeratorCancellation] CancellationToken cancellationToken)` — (inheritdoc)
- L1278-1301 _public method_ `public async Task<IReadOnlyList<IJob>> FindLatestByStreamWithTemplatesAsync(StreamId streamId, TemplateId[] templates, UserId? preflightStartedByUser, DateTimeOffset? maxCreateTime, DateTimeOffset? modifiedAfter, int? index, int? count, bool consistentRead, CancellationToken cancellationToken)` — (inheritdoc)
- L1304-1434 _private* method_ `async Task<JobDocument?> TryUpdateJobAsync(JobDocument jobDocument, IGraph graph, string? name, Priority? priority, bool? autoSubmit, int? autoSubmitChange, string? autoSubmitMessage, UserId? abortedByUserId, NotificationTriggerId? notificationTriggerId, List<JobReport>? reports, List<string>? arguments, KeyValuePair<int, NotificationTriggerId>? labelIdxToTriggerId, KeyValuePair<TemplateId, JobId>? jobTrigger, string? cancellationReason, CancellationToken cancellationToken)` — (inheritdoc)
- L1437-1526 _private* method_ `async Task<JobDocument?> TryUpdateBatchAsync(JobDocument jobDocument, IGraph graph, JobStepBatchId batchId, LogId? newLogId, JobStepBatchState? newState, JobStepBatchError? newError, CancellationToken cancellationToken)` — (inheritdoc)
- L1531-1584 _private* method_ `static void RetryNodesRecursive(JobDocument jobDocument, IGraph graph, int groupIdx, int nodeIdx, UserId retryByUserId, List<UpdateDefinition<JobDocument>> updates)` — Marks a node for retry and - if it's a skipped node - all of the nodes that caused it to be skipped
- L1587-1801 _private* method_ `async Task<JobDocument?> TryUpdateStepAsync(JobDocument jobDocument, IGraph graph, JobStepBatchId batchId, JobStepId stepId, JobStepState newState, JobStepOutcome newOutcome, JobStepError? newError, bool? newAbortRequested, UserId? newAbortByUserId, LogId? newLogId, NotificationTriggerId? newNotificationTriggerId, UserId? newRetryByUserId, Priority? newPriority, List<JobReport>? newReports, Dictionary<string, string?>? newProperties, string? newCancellationReason, JobId? newSpawnedJob, CancellationToken cancellationToken)` — (inheritdoc)
- L1804-1814 _private* method_ `Job? CreateJobObject(JobDocument? document, IGraph graph)` — attrs: `[return: NotNullIfNotNull("document")]`
- L1817-1821 _private* method_ `async Task<Job> CreateJobObjectAsync(JobDocument document, CancellationToken cancellationToken)` — attrs: `[return: NotNullIfNotNull("document")]`
- L1823-1833 _private* method_ `Task<JobDocument?> TryUpdateAsync(JobDocument job, List<UpdateDefinition<JobDocument>> updates, CancellationToken cancellationToken)`
- L1835-1844 _private* method_ `async Task<JobDocument?> TryUpdateAsync(JobDocument job, UpdateDefinition<JobDocument> update, CancellationToken cancellationToken)`
- L1847-1860 _private* method_ `async Task<JobDocument?> TryRemoveFromDispatchQueueAsync(JobDocument jobDocument, CancellationToken cancellationToken)` — (inheritdoc)
- L1863-1936 _private* method_ `async Task<JobDocument?> TryUpdateGraphAsync(JobDocument jobDocument, IGraph oldGraph, IGraph newGraph, CancellationToken cancellationToken)` — (inheritdoc)
- L1938-1969 _private* method_ `static bool NodesMatch(IGraph oldGraph, INode oldNode, IGraph newGraph, INode newNode)`
- L1971-1974 _private* method_ `static bool CompareListsIgnoreOrder(IEnumerable<string> seq1, IEnumerable<string> seq2)`
- L1977-1982 _public method_ `public async Task AddIssueToJobAsync(JobId jobId, int issueId, CancellationToken cancellationToken)` — (inheritdoc)
- L1985-1996 _public method_ `public async Task<IReadOnlyList<IJob>> GetDispatchQueueAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L1999-2029 _private* method_ `async Task<JobDocument?> TrySkipAllBatchesAsync(JobDocument jobDocument, IGraph graph, JobStepBatchError reason, CancellationToken cancellationToken)` — (inheritdoc)
- L2032-2060 _private* method_ `async Task<JobDocument?> TrySkipBatchAsync(JobDocument jobDocument, JobStepBatchId batchId, IGraph graph, JobStepBatchError reason, CancellationToken cancellationToken)` — (inheritdoc)
- L2063-2086 _private* method_ `async Task<JobDocument?> TryAssignLeaseAsync(JobDocument jobDocument, int batchIdx, PoolId poolId, AgentId agentId, SessionId sessionId, LeaseId leaseId, LogId logId, CancellationToken cancellationToken)` — (inheritdoc)
- L2089-2108 _private* method_ `async Task<JobDocument?> TryCancelLeaseAsync(JobDocument jobDocument, int batchIdx, CancellationToken cancellationToken)` — (inheritdoc)
- L2111-2167 _private* method_ `async Task<JobDocument?> TryFailBatchAsync(JobDocument jobDocument, int batchIdx, IGraph graph, JobStepBatchError error, CancellationToken cancellationToken)` — (inheritdoc)
- L2170-2174 _private method_ `private void UpdateBatchesInternal(JobDocument job, IGraph graph, List<UpdateDefinition<JobDocument>> updates, ILogger logger, IAuditLogChannel<JobId> jobAudit)`
- L2177-2181 _private method_ `private void CreateBatchesInternal(JobDocument job, IGraph graph, ILogger logger, IAuditLogChannel<JobId> jobAudit)`
- L2190-2193 _private method_ `private void CreateBatches(JobDocument job, IGraph graph, ILogger logger, IAuditLogChannel<JobId> jobAudit)` — Populate the list of batches for a job
- L2203-2216 _private* method_ `void UpdateBatches(JobDocument job, IGraph graph, List<UpdateDefinition<JobDocument>> updates, ILogger logger, IAuditLogChannel<JobId> jobAudit)` — Updates the list of batches for a job
- L2218-2229 _private* method_ `static void RemoveSteps(JobStepBatchDocument batch, Predicate<JobStepDocument> predicate, Dictionary<NodeRef, JobStepId> recycleStepIds)`
- L2231-2242 _private* method_ `static void RemoveBatches(JobDocument job, Predicate<JobStepBatchDocument> predicate, Dictionary<int, JobStepBatchId> recycleBatchIds)`
- L2251-2624 _private method_ `private static void CreateOrUpdateBatches(JobDocument job, IGraph graph, ILogger logger, IAuditLogChannel<JobId> jobAudit)` — Update the jobsteps for the given node graph
- L2629-2632 _private* method_ `static bool IsFatalBatchError(JobStepBatchError error)` — Test whether the nodes in a batch can still be run
- L2637-2640 _private* method_ `static bool CanRetryNode(JobDocument job, int groupIdx, int nodeIdx)` — Tests whether a node can be retried again
- L2646-2649 _public method_ `public static int GetSchedulePriority(IJob job)` — Gets the scheduling priority of this job
- L2651-2662 _private* method_ `static int GetSchedulePriority(JobDocument job)`
- L2673-2794 _private* method_ `static void RefreshDependentJobSteps(JobDocument job, IGraph graph, List<UpdateDefinition<JobDocument>> updates, ILogger logger, IAuditLogChannel<JobId> jobAudit, TelemetryContext? telemetryContext = null)` — Update the state of any jobsteps that are dependent on other jobsteps (eg. transition them from waiting to ready based on other steps completing)
- L2803-2813 _private* method_ `static void RefreshJobPriority(JobDocument job, List<UpdateDefinition<JobDocument>> updates, ILogger logger, IAuditLogChannel<JobId> jobAudit)` — Updates the schedule priority of a job
- L2822-2834 _private* method_ `static List<JobStepDocument> GetDependentSteps(IGraph graph, INode node, Dictionary<INode, JobStepDocument> stepForNode)` — Gets the steps that a node depends on
- L2836-2847 _private* method_ `static List<JobStepDocument> GetOptionalInputDependentSteps(IGraph graph, INode node, Dictionary<INode, JobStepDocument> stepForNode)`
- L2858-2893 _private* method_ `static JobStepBatchState GetBatchState(JobDocument job, IGraph graph, JobStepBatchDocument batch, Dictionary<INode, JobStepDocument> stepForNode, out DateTime? outReadyTimeUtc)` — Gets the new state for a batch
- L2896-2939 _public method_ `public async Task<IJob?> UpdateMetadataAsync(JobId jobId, List<string>? jobMetadata = null, Dictionary<JobStepId, List<string>>? stepMetadata = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L2942-2957 _public method_ `public async Task UpgradeDocumentsAsync()` — (inheritdoc)

#### struct `HordeServer.Jobs.JobCollection.TelemetryContext`  
`internal struct TelemetryContext`  
_internal; L51-67_
- desc: Ease of use struct used to pass telemetry context for job telemetry.
- L56 _internal property_ `internal IJob? Job { get; set; }` — The job that relates to the telemetry.
- L61 _internal property_ `internal IOptionsMonitor<BuildConfig> BuildConfig { get; set; }` — The build config object to use when deriving telemetry sinks.
- L66 _internal property_ `internal ITelemetryWriter TelemetryWriter { get; set; }` — The telemetry writer used to publish telemetry.

#### class `HordeServer.Jobs.JobCollection.Job`  
`class Job : IJob`  
_private*; L69-264_
- inherits: `IJob`
- L71 _private* field_ `readonly JobCollection _collection`
- L72 _private* field_ `readonly JobDocument _document`
- L73 _private* field_ `readonly IGraph _graph`
- L74 _private* field_ `readonly List<JobStepBatch> _batches`
- L76 _public property_ `public JobDocument Document => ...`
- L77 _public property_ `public IGraph Graph => ...`
- L78 _public property_ `public List<JobStepBatch> Batches => ...`
- L80 _public property_ `public List<string> Metadata => ...`
- L82 _private* property_ `JobId IJob.Id => ...`
- L83 _private* property_ `StreamId IJob.StreamId => ...`
- L84 _private* property_ `TemplateId IJob.TemplateId => ...`
- L85 _private* property_ `ContentHash? IJob.TemplateHash => ...`
- L86 _private* property_ `ContentHash IJob.GraphHash => ...`
- L87 _private* property_ `UserId? IJob.StartedByUserId => ...`
- L88 _private* property_ `UserId? IJob.AbortedByUserId => ...`
- L89 _private* property_ `string? IJob.CancellationReason => ...`
- L91 _private* property_ `BisectTaskId? IJob.StartedByBisectTaskId => ...`
- L92 _private* property_ `string IJob.Name => ...`
- L93 _private* property_ `CommitIdWithOrder IJob.CommitId => ...`
- L94 _private* property_ `CommitIdWithOrder? IJob.CodeCommitId => ...`
- L95 _private* property_ `CommitId? IJob.PreflightCommitId => ...`
- L96 _private* property_ `string? IJob.PreflightDescription => ...`
- L97 _private* property_ `Priority IJob.Priority => ...`
- L98 _private* property_ `bool IJob.AutoSubmit => ...`
- L99 _private* property_ `int? IJob.AutoSubmitChange => ...`
- L100 _private* property_ `string? IJob.AutoSubmitMessage => ...`
- L101 _private* property_ `bool IJob.UpdateIssues => ...`
- L102 _private* property_ `bool IJob.PromoteIssuesByDefault => ...`
- L103 _private* property_ `DateTime IJob.CreateTimeUtc => ...`
- L104 _private* property_ `JobOptions? IJob.JobOptions => ...`
- L105 _private* property_ `IReadOnlyList<IAclClaim> IJob.Claims => ...`
- L106 _private* property_ `IReadOnlyList<IJobStepBatch> IJob.Batches => ...`
- L107 _private* property_ `IReadOnlyDictionary<ParameterId, string> IJob.Parameters => ...`
- L108 _private* property_ `IReadOnlyList<string> IJob.Arguments => ...`
- L109 _private* property_ `IReadOnlyList<string>? IJob.Targets => ...`
- L110 _private* property_ `IReadOnlyList<string> IJob.AdditionalArguments => ...`
- L111 _private* property_ `IReadOnlyDictionary<string, string> IJob.Environment => ...`
- L112 _private* property_ `IReadOnlyList<int> IJob.Issues => ...`
- L113 _private* property_ `NotificationTriggerId? IJob.NotificationTriggerId => ...`
- L114 _private* property_ `bool IJob.ShowUgsBadges => ...`
- L115 _private* property_ `bool IJob.ShowUgsAlerts => ...`
- L116 _private* property_ `string? IJob.NotificationChannel => ...`
- L117 _private* property_ `string? IJob.NotificationChannelFilter => ...`
- L118 _private* property_ `IReadOnlyDictionary<int, NotificationTriggerId> IJob.LabelIdxToTriggerId => ...`
- L119 _private* property_ `IReadOnlyList<IJobReport>? IJob.Reports => ...`
- L120 _private* property_ `IReadOnlyList<IChainedJob> IJob.ChainedJobs => ...`
- L122 _private* property_ `JobId? IJob.ParentJobId => ...`
- L123 _private* property_ `JobStepId? IJob.ParentJobStepId => ...`
- L125 _private* property_ `DateTime IJob.UpdateTimeUtc => ...`
- L126 _private* property_ `int IJob.UpdateIndex => ...`
- L128 _private* field_ `Dictionary<JobStepBatchId, JobStepBatch>? _batchIdToBatch`
- L128 _private* field_ `Dictionary< _batchIdToBatch`
- L129 _private* field_ `Dictionary<JobStepId, JobStep>? _stepIdToStep`
- L129 _private* field_ `Dictionary< _stepIdToStep`
- L131 _private* field_ `Dictionary<NodeRef, JobStepId>? _cachedNodeRefToStepId`
- L131 _private* field_ `Dictionary< _cachedNodeRefToStepId`
- L132 _public property_ `public IReadOnlyDictionary<NodeRef, JobStepId> NodeRefToStepId => ...`
- L134-138 _private* method_ `bool TryGetBatch(JobStepBatchId batchId, [NotNullWhen(true)] out JobStepBatch? batch)`
- L140-152 _private* method_ `bool IJob.TryGetBatch(JobStepBatchId batchId, [NotNullWhen(true)] out IJobStepBatch? batch)`
- L154-158 _private* method_ `bool TryGetStep(JobStepId stepId, [NotNullWhen(true)] out JobStep? step)`
- L160-172 _private* method_ `bool IJob.TryGetStep(JobStepId stepId, [NotNullWhen(true)] out IJobStep? step)`
- L174-189 _private* method_ `Dictionary<NodeRef, JobStepId> CreateNodeRefToStepId()`
- L191-197 _public ctor_ `public Job(JobCollection collection, JobDocument document, IGraph graph)`
- L199 _public method_ `public Task<IJob?> RefreshAsync(CancellationToken cancellationToken = default)`
- L202-206 _public method_ `public async Task<IJob?> TryAssignLeaseAsync(int batchIdx, PoolId poolId, AgentId agentId, SessionId sessionId, LeaseId leaseId, LogId logId, CancellationToken cancellationToken = default)`
- L208-212 _public method_ `public async Task<IJob?> TryCancelLeaseAsync(int batchIdx, CancellationToken cancellationToken = default)`
- L214 _public method_ `public Task<bool> TryDeleteAsync(CancellationToken cancellationToken = default)`
- L217-221 _public method_ `public async Task<IJob?> TryFailBatchAsync(int batchIdx, JobStepBatchError reason, CancellationToken cancellationToken = default)`
- L223-227 _public method_ `public async Task<IJob?> TryRemoveFromDispatchQueueAsync(CancellationToken cancellationToken = default)`
- L229-233 _public method_ `public async Task<IJob?> TrySkipAllBatchesAsync(JobStepBatchError reason, CancellationToken cancellationToken = default)`
- L235-239 _public method_ `public async Task<IJob?> TrySkipBatchAsync(JobStepBatchId batchId, JobStepBatchError reason, CancellationToken cancellationToken = default)`
- L241-245 _public method_ `public async Task<IJob?> TryUpdateBatchAsync(JobStepBatchId batchId, LogId? newLogId, JobStepBatchState? newState, JobStepBatchError? newError, CancellationToken cancellationToken = default)`
- L247-251 _public method_ `public async Task<IJob?> TryUpdateGraphAsync(IGraph newGraph, CancellationToken cancellationToken = default)`
- L253-257 _public method_ `public async Task<IJob?> TryUpdateJobAsync(string? name = null, Priority? priority = null, bool? autoSubmit = null, int? autoSubmitChange = null, string? autoSubmitMessage = null, UserId? abortedByUserId = null, NotificationTriggerId? notificationTriggerId = null, List<JobReport>? reports = null, List<string>? arguments = null, KeyValuePair<int, NotificationTriggerId>? labelIdxToTriggerId = null, KeyValuePair<TemplateId, JobId>? jobTrigger = null, string? cancellationReason = null, CancellationToken cancellationToken = default)`
- L259-263 _public method_ `public async Task<IJob?> TryUpdateStepAsync(JobStepBatchId batchId, JobStepId stepId, JobStepState newState = JobStepState.Unspecified, JobStepOutcome newOutcome = JobStepOutcome.Unspecified, JobStepError? newError = null, bool? newAbortRequested = null, UserId? newAbortByUserId = null, LogId? newLogId = null, NotificationTriggerId? newNotificationTriggerId = null, UserId? newRetryByUserId = null, Priority? newPriority = null, List<JobReport>? newReports = null, Dictionary<string, string?>? newProperties = null, string? newCancellationReason = null, JobId? newSpawnedJob = null, CancellationToken cancellationToken = default)`

#### class `HordeServer.Jobs.JobCollection.JobStepBatch`  
`class JobStepBatch : IJobStepBatch`  
_private*; L267-302_
- attrs: `[DebuggerDisplay("{Document.Id} (Group {Document.GroupIdx})")]`
- inherits: `IJobStepBatch`
- L269 _public property_ `public Job Job { get; }`
- L270 _public property_ `public JobStepBatchDocument Document { get; }`
- L271 _public property_ `public INodeGroup Group { get; }`
- L272 _public property_ `public List<JobStep> Steps { get; }`
- L274 _private* property_ `IJob IJobStepBatch.Job => ...`
- L275 _private* property_ `JobStepBatchId IJobStepBatch.Id => ...`
- L278 _private* property_ `string IJobStepBatch.AgentType => ...`
- L281 _private* property_ `LogId? IJobStepBatch.LogId => ...`
- L282 _private* property_ `int IJobStepBatch.GroupIdx => ...`
- L283 _private* property_ `JobStepBatchState IJobStepBatch.State => ...`
- L284 _private* property_ `JobStepBatchError IJobStepBatch.Error => ...`
- L285 _private* property_ `IReadOnlyList<IJobStep> IJobStepBatch.Steps => ...`
- L286 _private* property_ `PoolId? IJobStepBatch.PoolId => ...`
- L287 _private* property_ `AgentId? IJobStepBatch.AgentId => ...`
- L288 _private* property_ `SessionId? IJobStepBatch.SessionId => ...`
- L289 _private* property_ `LeaseId? IJobStepBatch.LeaseId => ...`
- L290 _private* property_ `int IJobStepBatch.SchedulePriority => ...`
- L291 _private* property_ `DateTime? IJobStepBatch.ReadyTimeUtc => ...`
- L292 _private* property_ `DateTime? IJobStepBatch.StartTimeUtc => ...`
- L293 _private* property_ `DateTime? IJobStepBatch.FinishTimeUtc => ...`
- L295-301 _public ctor_ `public JobStepBatch(Job job, JobStepBatchDocument document, INodeGroup group)`

#### class `HordeServer.Jobs.JobCollection.JobStep`  
`class JobStep : IJobStep`  
_private*; L305-460_
- attrs: `[DebuggerDisplay("{Document.Id} (Node {Batch.Document.GroupIdx},{Document.NodeIdx})")]`
- inherits: `IJobStep`
- L307 _public property_ `public Job Job => ...`
- L308 _public property_ `public JobStepBatch Batch { get; }`
- L309 _public property_ `public JobStepDocument Document { get; }`
- L310 _public property_ `public INode Node { get; }`
- L312 _private* property_ `IJob IJobStep.Job => ...`
- L313 _private* property_ `IJobStepBatch IJobStep.Batch => ...`
- L314 _private* property_ `JobStepId IJobStep.Id => ...`
- L315 _private* property_ `INode IJobStep.Node => ...`
- L316 _private* property_ `int IJobStep.NodeIdx => ...`
- L319 _private* property_ `string IJobStep.Name => ...`
- L321 _private* field_ `List<JobStepOutputRef>? _inputs`
- L322 _private* property_ `IReadOnlyList<JobStepOutputRef> IJobStep.Inputs => ...`
- L324 _private* field_ `List<JobStepOutputRef>? _optionalInputs`
- L325 _private* property_ `IReadOnlyList<JobStepOutputRef> IJobStep.OptionalInputs => ...`
- L327 _private* property_ `IReadOnlyList<string> IJobStep.OutputNames => ...`
- L329 _private* field_ `List<JobStepId>? _inputDependencies`
- L330 _private* property_ `IReadOnlyList<JobStepId> IJobStep.InputDependencies => ...`
- L332 _private* field_ `List<JobStepId>? _optionalInputDependencies`
- L333 _private* property_ `IReadOnlyList<JobStepId> IJobStep.OptionalInputDependencies => ...`
- L335 _private* field_ `List<JobStepId>? _orderDependencies`
- L336 _private* property_ `IReadOnlyList<JobStepId> IJobStep.OrderDependencies => ...`
- L338 _private* property_ `bool IJobStep.AllowRetry => ...`
- L339 _private* property_ `bool IJobStep.RunEarly => ...`
- L340 _private* property_ `bool IJobStep.Warnings => ...`
- L341 _private* property_ `IReadOnlyDictionary<string, string>? IJobStep.Credentials => ...`
- L342 _private* property_ `IReadOnlyNodeAnnotations IJobStep.Annotations => ...`
- L343 _private* property_ `IReadOnlyList<string> IJobStep.Metadata => ...`
- L346 _private* property_ `JobStepState IJobStep.State => ...`
- L347 _private* property_ `JobStepOutcome IJobStep.Outcome => ...`
- L348 _private* property_ `JobStepError IJobStep.Error => ...`
- L349 _private* property_ `LogId? IJobStep.LogId => ...`
- L350 _private* property_ `NotificationTriggerId? IJobStep.NotificationTriggerId => ...`
- L351 _private* property_ `DateTime? IJobStep.ReadyTimeUtc => ...`
- L352 _private* property_ `DateTime? IJobStep.StartTimeUtc => ...`
- L353 _private* property_ `DateTime? IJobStep.FinishTimeUtc => ...`
- L354 _private* property_ `Priority? IJobStep.Priority => ...`
- L355 _private* property_ `UserId? IJobStep.RetriedByUserId => ...`
- L356 _private* property_ `bool IJobStep.AbortRequested => ...`
- L357 _private* property_ `UserId? IJobStep.AbortedByUserId => ...`
- L358 _private* property_ `string? IJobStep.CancellationReason => ...`
- L359 _private* property_ `IReadOnlyList<IJobReport>? IJobStep.Reports => ...`
- L360 _private* property_ `IReadOnlyDictionary<string, string>? IJobStep.Properties => ...`
- L362 _private* property_ `IReadOnlyList<JobId>? IJobStep.SpawnedJobs => ...`
- L364-369 _public ctor_ `public JobStep(JobStepBatch batch, JobStepDocument document, INode node)`
- L371-386 _private* method_ `List<JobStepOutputRef> CreateInputDependencyList()`
- L388-403 _private* method_ `List<JobStepId> CreateInputDependenciesList()`
- L405-420 _private* method_ `List<JobStepOutputRef> CreateOptionalInputDependencyList()`
- L422-437 _private* method_ `List<JobStepId> CreateOptionalInputDependenciesList()`
- L439-454 _private* method_ `List<JobStepId> CreateOrderDependenciesList()`
- L456-459 _private* method_ `static void MissingNodeRef(NodeRef nodeRef)`

#### class `HordeServer.Jobs.JobCollection.JobDocument`  
`class JobDocument`  
_private*; L462-658_
- L465 _public property_ `public JobId Id { get; set; }` — attrs: `[BsonRequired, BsonId]`
- L467 _public property_ `public StreamId StreamId { get; set; }`
- L468 _public property_ `public TemplateId TemplateId { get; set; }`
- L469 _public property_ `public ContentHash? TemplateHash { get; set; }`
- L470 _public property_ `public ContentHash GraphHash { get; set; }`
- L473 _public property_ `public UserId? StartedByUserId { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L476 _public property_ `public BisectTaskId? StartedByBisectTaskId { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L479 _public property_ `public string? StartedByUserDeprecated { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("StartedByUser")]`
- L482 _public property_ `public UserId? AbortedByUserId { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L485 _public property_ `public string? AbortedByUserDeprecated { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("AbortedByUser")]`
- L488 _public property_ `public string? CancellationReason { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L491 _public property_ `public string Name { get; set; }` — attrs: `[BsonRequired]`
- L494-498 _public property_ `public CommitIdWithOrder CommitId { get; set; }` — attrs: `[BsonIgnore]`
- L501 _public property_ `public string? CommitName { get; set; }` — attrs: `[BsonElement("Commit")]`
- L504 _public property_ `public int CommitOrder { get; set; }` — attrs: `[BsonElement("Change")]`
- L507-511 _public property_ `public CommitIdWithOrder? CodeCommitId { get; set; }` — attrs: `[BsonIgnore]`
- L514 _public property_ `public string? CodeCommitName { get; set; }` — attrs: `[BsonElement("CodeCommit")]`
- L517 _public property_ `public int CodeCommitOrder { get; set; }` — attrs: `[BsonElement("CodeChange")]`
- L520-524 _public property_ `public CommitId? PreflightCommitId { get; set; }` — attrs: `[BsonIgnore]`
- L527 _public property_ `public string? PreflightCommitName { get; set; }` — attrs: `[BsonElement("PreflightCommit")]`
- L530 _public property_ `public int PreflightChange { get; set; }`
- L532 _public property_ `public string? PreflightDescription { get; set; }`
- L533 _public property_ `public Priority Priority { get; set; }`
- L536 _public property_ `public bool AutoSubmit { get; set; }` — attrs: `[BsonIgnoreIfDefault]`
- L539 _public property_ `public int? AutoSubmitChange { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L542 _public property_ `public string? AutoSubmitMessage { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L544 _public property_ `public bool UpdateIssues { get; set; }`
- L546 _public property_ `public bool PromoteIssuesByDefault { get; set; }`
- L549 _public property_ `public DateTimeOffset? CreateTime { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L552 _public property_ `public JobOptions? JobOptions { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L554 _public property_ `public List<AclClaimConfig> Claims { get; set; }`
- L557 _public property_ `public DateTime? CreateTimeUtc { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L559 _public property_ `public int SchedulePriority { get; set; }`
- L560 _public property_ `public List<JobStepBatchDocument> Batches { get; set; }`
- L561 _public property_ `public List<JobReport>? Reports { get; set; }`
- L564 _public property_ `public Dictionary<ParameterId, string> Parameters { get; set; }` — attrs: `[BsonDictionaryOptions(Representation = DictionaryRepresentation.ArrayOfDocuments)]`
- L566 _public property_ `public List<string> Arguments { get; set; }`
- L567 _public property_ `public List<string> AdditionalArguments { get; set; }`
- L570 _public property_ `public List<string>? Targets { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L573 _public property_ `public Dictionary<string, string> Environment { get; set; }` — attrs: `[BsonDictionaryOptions(DictionaryRepresentation.ArrayOfDocuments)]`
- L575 _public property_ `public List<int> ReferencedByIssues { get; set; }`
- L576 _public property_ `public NotificationTriggerId? NotificationTriggerId { get; set; }`
- L577 _public property_ `public bool ShowUgsBadges { get; set; }`
- L578 _public property_ `public bool ShowUgsAlerts { get; set; }`
- L579 _public property_ `public string? NotificationChannel { get; set; }`
- L580 _public property_ `public string? NotificationChannelFilter { get; set; }`
- L581 _public field_ `public List<LabelNotificationDocument> _labelNotifications = new List<LabelNotificationDocument>()`
- L582 _public property_ `public List<ChainedJobDocument> ChainedJobs { get; set; }`
- L585 _public property_ `public JobId? ParentJobId { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L587 _public property_ `public JobStepId? ParentJobStepId { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L590 _public property_ `public List<NodeRef>? RetriedNodes { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L591 _public property_ `public SubResourceId NextSubResourceId { get; set; }`
- L594 _public property_ `public DateTimeOffset? UpdateTime { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L597 _public property_ `public DateTime? UpdateTimeUtc { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L600 _public property_ `public List<string> Metadata { get; set; }` — attrs: `[BsonElement("Metadata")]`
- L603 _public property_ `public int UpdateIndex { get; set; }` — attrs: `[BsonRequired]`
- L606-610 _private ctor_ `private JobDocument()` — attrs: `[BsonConstructor]`
- L612-654 _public ctor_ `public JobDocument(JobId id, StreamId streamId, TemplateId templateId, ContentHash templateHash, ContentHash graphHash, string name, CommitIdWithOrder commitId, CommitIdWithOrder? codeCommitId, CreateJobOptions options, DateTime createTimeUtc, List<string> metadata)`
- L656 _public method_ `public DateTime GetCreateTimeOrDefault()`

#### class `HordeServer.Jobs.JobCollection.JobStepBatchDocument`  
`class JobStepBatchDocument`  
_private*; L660-722_
- L663 _public property_ `public JobStepBatchId Id { get; set; }` — attrs: `[BsonRequired]`
- L665 _public property_ `public LogId? LogId { get; set; }`
- L668 _public property_ `public int GroupIdx { get; set; }` — attrs: `[BsonRequired]`
- L671 _public property_ `public JobStepBatchState State { get; set; }` — attrs: `[BsonRequired]`
- L674 _public property_ `public JobStepBatchError Error { get; set; }` — attrs: `[BsonIgnoreIfDefault, BsonDefaultValue(JobStepBatchError.None)]`
- L676 _public property_ `public List<JobStepDocument> Steps { get; set; }`
- L679 _public property_ `public PoolId? PoolId { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L682 _public property_ `public AgentId? AgentId { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L685 _public property_ `public SessionId? SessionId { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L688 _public property_ `public LeaseId? LeaseId { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L690 _public property_ `public int SchedulePriority { get; set; }`
- L693 _public property_ `public DateTimeOffset? ReadyTime { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L696 _public property_ `public DateTimeOffset? StartTime { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L699 _public property_ `public DateTimeOffset? FinishTime { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L702-704 _private ctor_ `private JobStepBatchDocument()` — attrs: `[BsonConstructor]`
- L706-710 _public ctor_ `public JobStepBatchDocument(JobStepBatchId id, int groupIdx)`
- L712-721 _public method_ `public override string ToString()`

#### class `HordeServer.Jobs.JobCollection.JobStepDocument`  
`class JobStepDocument`  
_private*; L725-812_
- attrs: `[BsonIgnoreExtraElements]`
- L728 _public property_ `public JobStepId Id { get; set; }` — attrs: `[BsonRequired]`
- L731 _public property_ `public int NodeIdx { get; set; }` — attrs: `[BsonRequired]`
- L734 _public property_ `public JobStepState State { get; set; }` — attrs: `[BsonRequired]`
- L736 _public property_ `public JobStepOutcome Outcome { get; set; }`
- L738 _public property_ `public JobStepError Error { get; set; }`
- L740 _public property_ `public List<string> Metadata { get; set; }`
- L743 _public property_ `public LogId? LogId { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L746 _public property_ `public NotificationTriggerId? NotificationTriggerId { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L749 _public property_ `public DateTimeOffset? ReadyTime { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L752 _public property_ `public DateTimeOffset? StartTime { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L755 _public property_ `public DateTimeOffset? FinishTime { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L758 _public property_ `public Priority? Priority { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L761 _public property_ `public bool Retry { get; set; }` — attrs: `[BsonIgnoreIfDefault, BsonDefaultValue(false)]`
- L763 _public property_ `public UserId? RetriedByUserId { get; set; }`
- L766 _public property_ `public string? RetriedByUserDeprecated { get; set; }` — attrs: `[BsonElement("RetryByUser")]`
- L768 _public property_ `public bool AbortRequested { get; set; }`
- L770 _public property_ `public UserId? AbortedByUserId { get; set; }`
- L773 _public property_ `public string? AbortedByUserDeprecated { get; set; }` — attrs: `[BsonElement("AbortByUser")]`
- L776 _public property_ `public string? CancellationReason { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L779 _public property_ `public List<JobReport>? Reports { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L782 _public property_ `public List<JobId>? SpawnedJobs { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L785 _public property_ `public Dictionary<string, string>? Properties { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L788-790 _private ctor_ `private JobStepDocument()` — attrs: `[BsonConstructor]`
- L792-796 _public ctor_ `public JobStepDocument(JobStepId id, int nodeIdx)`
- L798-811 _public method_ `public override string ToString()`

#### class `HordeServer.Jobs.JobCollection.ChainedJobDocument`  
`class ChainedJobDocument : IChainedJob`  
_private*; L814-833_
- inherits: `IChainedJob`
- L816 _public property_ `public string Target { get; set; }`
- L817 _public property_ `public TemplateId TemplateRefId { get; set; }`
- L818 _public property_ `public JobId? JobId { get; set; }`
- L819 _public property_ `public bool UseDefaultChangeForTemplate { get; set; }`
- L822-825 _private ctor_ `private ChainedJobDocument()` — attrs: `[BsonConstructor]`
- L827-832 _public ctor_ `public ChainedJobDocument(ChainedJobTemplateConfig trigger)`

#### class `HordeServer.Jobs.JobCollection.LabelNotificationDocument`  
`class LabelNotificationDocument`  
_private*; L835-839_
- L837 _public field_ `public int _labelIdx`
- L838 _public field_ `public NotificationTriggerId _triggerId`

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/JobExpirationService.cs` (HordeServer.Build)


#### class `HordeServer.Jobs.JobExpirationService`  
`public sealed class JobExpirationService : IHostedService, IAsyncDisposable`  
_public; L16-172_
- inherits: `IHostedService, IAsyncDisposable`
- desc: Expires jobs a certain amount of time after they have run
- L21 _public field_ `public static readonly TimeSpan StepTimeout = TimeSpan.FromHours(24.0)` — Maximum duration a step can run before being timed out
- L23 _private* field_ `readonly IJobCollection _jobCollection`
- L24 _private* field_ `readonly IClock _clock`
- L25 _private* field_ `readonly IOptionsMonitor<BuildConfig> _buildConfig`
- L26 _private* field_ `readonly ITicker _ticker`
- L27 _private* field_ `readonly ILogger _logger`
- L32-39 _public ctor_ `public JobExpirationService(IJobCollection jobCollection, IClock clock, IOptionsMonitor<BuildConfig> buildConfig, ILogger<JobExpirationService> logger)` — Constructor
- L42 _public method_ `public ValueTask DisposeAsync()` — (inheritdoc)
- L45 _public method_ `public Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L48 _public method_ `public Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L50-121 _private* method_ `async ValueTask TickAsync(CancellationToken cancellationToken)`
- L124-171 _private* method_ `async Task TimeoutStuckStepsAsync(DateTime currentTime, CancellationToken cancellationToken)` — attrs: `[SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Stuck job steps disabled")]`

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/JobIdUtils.cs` (HordeServer.Build)


#### class `HordeServer.Jobs.JobIdUtils`  
`public static class JobIdUtils`  
_public; L11-20_
- desc: Utility methods for JobId
- L16-19 _public method_ `public static JobId GenerateNewId()` — Creates a new, random JobId

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/JobRpcService.cs` (HordeServer.Build)


#### class `HordeServer.Jobs.JobRpcService`  
`public class JobRpcService : JobRpc.JobRpcBase`  
_public; L44-1029_
- attrs: `[Authorize]`
- inherits: `JobRpc.JobRpcBase`
- desc: Implements the Horde gRPC service for bots updating their status and dequeing work
- L46 _private* field_ `readonly IAclService _aclService`
- L47 _private* field_ `readonly JobService _jobService`
- L48 _private* field_ `readonly AgentService _agentService`
- L49 _private* field_ `readonly PoolService _poolService`
- L50 _private* field_ `readonly ConformTaskSource _conformTaskSource`
- L51 _private* field_ `readonly IArtifactCollection _artifactCollection`
- L52 _private* field_ `readonly IJobCollection _jobCollection`
- L53 _private* field_ `readonly ILogCollection _logCollection`
- L54 _private* field_ `readonly IGraphCollection _graphs`
- L55 _private* field_ `readonly ITestDataCollection _testData`
- L56 _private* field_ `readonly ITestDataCollectionV2 _testDataV2`
- L57 _private* field_ `readonly IJobStepRefCollection _jobStepRefCollection`
- L58 _private* field_ `readonly ITemplateCollection _templateCollection`
- L59 _private* field_ `readonly HttpClient _httpClient`
- L60 _private* field_ `readonly IClock _clock`
- L61 _private* field_ `readonly IOptionsSnapshot<BuildConfig> _buildConfig`
- L62 _private* field_ `readonly ILogger _logger`
- L67-86 _public ctor_ `public JobRpcService(IAclService aclService, JobService jobService, AgentService agentService, PoolService poolService, ConformTaskSource conformTaskSource, IArtifactCollection artifactCollection, IJobCollection jobCollection, ILogCollection logCollection, IGraphCollection graphs, ITestDataCollection testData, ITestDataCollectionV2 testDataV2, IJobStepRefCollection jobStepRefCollection, ITemplateCollection templateCollection, HttpClient httpClient, IClock clock, IOptionsSnapshot<BuildConfig> buildConfig, ILogger<JobRpcService> logger)` — Constructor
- L89-145 _public method_ `public override async Task<RpcUpdateAgentWorkspacesResponse> UpdateAgentWorkspaces(RpcUpdateAgentWorkspacesRequest request, ServerCallContext context)` — (inheritdoc)
- L153-179 _public method_ `public override async Task<RpcGetJobResponse> GetJob(RpcGetJobRequest request, ServerCallContext context)` — Gets information about a job
- L187-203 _public method_ `public override async Task<Empty> UpdateJob(RpcUpdateJobRequest request, ServerCallContext context)` — Updates properties on a job
- L211-269 _public method_ `public override async Task<RpcBeginBatchResponse> BeginBatch(RpcBeginBatchRequest request, ServerCallContext context)` — Starts executing a batch
- L277-292 _public method_ `public override async Task<Empty> FinishBatch(RpcFinishBatchRequest request, ServerCallContext context)` — Finishes executing a batch
- L300-311 _public method_ `public override async Task<RpcBeginStepResponse> BeginStep(RpcBeginStepRequest request, ServerCallContext context)` — Starts executing a step
- L313-547 _private* method_ `async Task<RpcBeginStepResponse?> TryBeginStepAsync(RpcBeginStepRequest request, Boxed<ILog?> log, ServerCallContext context)`
- L558-587 _private* method_ `async Task<string?> AllocateTokenAsync(TokenConfig config, CancellationToken cancellationToken)`
- L589-597 _private* method_ `async Task<IJob> GetJobAsync(JobId jobId, CancellationToken cancellationToken)`
- L599-622 _private* method_ `static IJobStepBatch AuthorizeBatch(IJob job, JobStepBatchId batchId, ServerCallContext context)`
- L630-658 _public method_ `public override async Task<Empty> UpdateStep(RpcUpdateStepRequest request, ServerCallContext context)` — Updates the state of a jobstep
- L666-678 _public method_ `public override async Task<RpcGetStepResponse> GetStep(RpcGetStepRequest request, ServerCallContext context)` — Get the state of a jobstep
- L686-779 _public method_ `public override async Task<RpcUpdateGraphResponse> UpdateGraph(RpcUpdateGraphRequest request, ServerCallContext context)` — Updates the state of a jobstep
- L788-817 _public method_ `public override async Task<Empty> CreateEvents(RpcCreateLogEventsRequest request, ServerCallContext context)` — attrs: `[Obsolete("Use LogRpc.CreateLogEvents instead")]` — Creates a set of events
- L825-880 _public method_ `public override async Task<RpcUploadTestDataResponse> UploadTestData(IAsyncStreamReader<RpcUploadTestDataRequest> reader, ServerCallContext context)` — Uploads new test data
- L883-914 _public method_ `public override async Task<RpcCreateJobArtifactResponseV2> CreateArtifactV2(RpcCreateJobArtifactRequestV2 request, ServerCallContext context)` — (inheritdoc)
- L917-941 _public method_ `public override async Task<RpcGetJobArtifactResponse> GetArtifact(RpcGetJobArtifactRequest request, ServerCallContext context)` — (inheritdoc)
- L943-946 _private* method_ `Task<(IJob, IJobStepBatch, IJobStep)> AuthorizeAsync(string jobId, string stepId, ServerCallContext context)`
- L948-977 _private* method_ `async Task<(IJob, IJobStepBatch, IJobStep)> AuthorizeAsync(JobId jobId, JobStepId stepId, ServerCallContext context)`
- L985-1028 _public method_ `public override async Task<RpcCreateReportResponse> CreateReport(RpcCreateReportRequest request, ServerCallContext context)` — Create a new report on a job or job step

#### class `HordeServer.Jobs.JobRpcService.GetTokenResponse`  
`class GetTokenResponse`  
_private*; L549-556_
- L552 _public property_ `public string TokenType { get; set; }` — attrs: `[JsonPropertyName("token_type")]`
- L555 _public property_ `public string AccessToken { get; set; }` — attrs: `[JsonPropertyName("access_token")]`

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/JobService.cs` (HordeServer.Build)


#### class `HordeServer.Jobs.RetryNotAllowedException`  
`public class RetryNotAllowedException : Exception`  
_public; L41-57_
- inherits: `Exception`
- desc: Exception thrown when attempting to retry executing a node that does not allow retries
- L46 _public property_ `public string NodeName { get; set; }` — The node name
- L52-56 _public ctor_ `public RetryNotAllowedException(string nodeName) : base($"Node '{nodeName}' does not permit retries")` — Constructor

#### class `HordeServer.Jobs.JobPermissionsCache`  
`public class JobPermissionsCache`  
_public; L62-68_
- desc: Cache of information about job ACLs
- L67 _public property_ `public Dictionary<JobId, StreamId> Jobs { get; set; }` — Map of job id to permissions for that job

#### class `HordeServer.Jobs.JobService`  
`public class JobService : ILogExtAuthProvider`  
_public; L73-1420_
- inherits: `ILogExtAuthProvider`
- desc: Wraps funtionality for manipulating jobs, jobsteps, and jobstep runs
- L75 _private* field_ `readonly IJobCollection _jobs`
- L76 _private* field_ `readonly IGraphCollection _graphs`
- L77 _private* field_ `readonly IAgentCollection _agents`
- L78 _private* field_ `readonly IJobStepRefCollection _jobStepRefs`
- L79 _private* field_ `readonly IBisectTaskCollection _bisectTasks`
- L80 _private* field_ `readonly IJobTimingCollection _jobTimings`
- L81 _private* field_ `readonly IUserCollection _userCollection`
- L82 _private* field_ `readonly INotificationTriggerCollection _triggerCollection`
- L83 _private* field_ `readonly JobTaskSource _jobTaskSource`
- L84 _private* field_ `readonly ITemplateCollectionInternal _templateCollection`
- L85 _private* field_ `readonly IPerforceService _perforceService`
- L86 _private* field_ `readonly IOptionsMonitor<BuildConfig> _buildConfig`
- L87 _private* field_ `readonly Tracer _tracer`
- L88 _private* field_ `readonly ILogger _logger`
- L89 _private* field_ `readonly IAuditLog<JobId> _auditLog`
- L90 _private* field_ `readonly ITelemetryWriter _telemetryWriter`
- L95 _public delegate_ `public delegate void LabelUpdateEvent(IJob job, IReadOnlyList<(LabelState, LabelOutcome)> oldLabelStates, IReadOnlyList<(LabelState, LabelOutcome)> newLabelStates)` — Delegate for label update events
- L100 _public event_ `public event LabelUpdateEvent? OnLabelUpdate` — Event triggered when a label state changes
- L105 _public delegate_ `public delegate void JobAbortedEvent(IJob job, IGraph graph)` — Delegate for job aborted events
- L110 _public event_ `public event JobAbortedEvent? OnJobAborted` — Event triggered when a job has been aborted
- L115 _public delegate_ `public delegate void JobStepCompleteEvent(IJob job, IGraph graph, JobStepBatchId batchId, JobStepId stepId)` — Delegate for job step complete events
- L120 _public event_ `public event JobStepCompleteEvent? OnJobStepComplete` — Event triggered when a job step completes
- L127 _public event_ `public event JobTaskSource.JobScheduleEvent? OnJobScheduled` — Event triggered when a job is scheduled on the underlying JobTaskSource Exposed and duplicated here to avoid dependency on the exact JobTaskSource
- L132-155 _public ctor_ `public JobService(IJobCollection jobs, IGraphCollection graphs, IAgentCollection agents, IJobStepRefCollection jobStepRefs, IBisectTaskCollection bisectTasks, IJobTimingCollection jobTimings, IUserCollection userCollection, INotificationTriggerCollection triggerCollection, JobTaskSource jobTaskSource, ITemplateCollectionInternal templateCollection, IPerforceService perforceService, Tracer tracer, IOptionsMonitor<BuildConfig> buildConfig, ILogger<JobService> logger, IAuditLog<JobId> auditLog, ITelemetryWriter telemetryWriter)` — Constructor
- L171-237 _public method_ `public async Task<IJob> CreateJobAsync(JobId? jobId, StreamConfig streamConfig, TemplateId templateRefId, ContentHash templateHash, IGraph graph, string name, CommitId commitId, CommitId? codeCommitId, CreateJobOptions options, CancellationToken cancellationToken = default)` — Creates a new job
- L239-291 _private method_ `private async Task AbortAnyDuplicateJobsAsync(IJob newJob, CancellationToken cancellationToken)`
- L298-333 _public method_ `public async Task<bool> DeleteJobAsync(IJob job, CancellationToken cancellationToken)` — Deletes a job
- L341-344 _public method_ `public async Task DeleteJobsForStreamAsync(StreamId streamId, CancellationToken cancellationToken)` — Delete all the jobs for a stream
- L360-410 _public method_ `public async Task<IJob?> UpdateJobAsync(IJob job, string? name = null, Priority? priority = null, bool? autoSubmit = null, UserId? abortedByUserId = null, NotificationTriggerId? onCompleteTriggerId = null, List<JobReport>? reports = null, List<string>? arguments = null, KeyValuePair<int, NotificationTriggerId>? labelIdxToTriggerId = null, string? cancellationReason = null, CancellationToken cancellationToken = default)` — Updates a new job
- L416-427 _public method_ `public async Task<CommitIdWithOrder?> EvaluateChangeQueriesAsync(StreamId streamId, IEnumerable<IChangeQuery> queries, List<CommitTag>? commitTags, ICommitCollection commits, CancellationToken cancellationToken)` — Evaluate a change query to determine which CL to run a job at
- L433-462 _public method_ `public async ValueTask<CommitIdWithOrder?> EvaluateChangeQueryAsync(StreamId streamId, IChangeQuery query, List<CommitTag>? commitTags, ICommitCollection commits, CancellationToken cancellationToken)` — Evaluate a change query to determine which CL to run a job at
- L464-478 _private* method_ `static IEnumerable<string> GetTagPropertyValues(string propertyName, List<CommitTag>? commitTags)`
- L488-526 _private* method_ `async Task CancelLeaseAsync(AgentId agentId, LeaseId leaseId, LeaseOutcomeReason reason, CancellationToken cancellationToken)` — Cancel an active lease
- L534-537 _public method_ `public Task<IJob?> GetJobAsync(JobId jobId, CancellationToken cancellationToken = default)` — Gets a job with the given unique id
- L545-548 _public method_ `public Task<IGraph> GetGraphAsync(IJob job, CancellationToken cancellationToken = default)` — Gets the graph for a job
- L558-561 _public method_ `public Task<IReadOnlyList<IJob>> FindJobsAsync(FindJobOptions options, int? index = null, int? count = null, CancellationToken cancellationToken = default)` — Searches for jobs matching the given criteria
- L576-579 _public method_ `public async Task<IReadOnlyList<IJob>> FindJobsByStreamWithTemplatesAsync(StreamId streamId, TemplateId[] templates, UserId? preflightStartedByUser = null, DateTimeOffset? maxCreateTime = null, DateTimeOffset? modifiedAfter = null, int? index = null, int? count = null, bool consistentRead = true, CancellationToken cancellationToken = default)` — Searches for jobs matching a stream with given templates
- L588-605 _public method_ `public async Task<IJob?> TryUpdateGraphAsync(IJob job, IGraph newGraph, CancellationToken cancellationToken)` — Attempts to update the node groups to be executed for a job. Fails if another write happens in the meantime.
- L614-677 _public method_ `public async Task<IJobTiming> GetJobTimingAsync(IJob job, ILogger logger, CancellationToken cancellationToken)` — Gets the timing info for a particular job.
- L688-725 _private* method_ `async Task<JobStepTimingData> GetStepTimingInfoAsync(StreamId streamId, TemplateId templateId, string nodeName, CommitIdWithOrder? commitId, CancellationToken cancellationToken)` — Finds the average duration for the given step
- L737-841 _public method_ `public async Task<IJob?> UpdateBatchAsync(IJob job, JobStepBatchId batchId, StreamConfig streamConfig, LogId? newLogId = null, JobStepBatchState? newState = null, CancellationToken cancellationToken = default)` — Updates the state of a batch
- L843-868 _private* method_ `async Task<JobStepBatchError?> CheckJobAsync(IJob job, StreamConfig streamConfig, CancellationToken cancellationToken)`
- L880-884 _public method_ `public async Task<IJob?> TryUpdateBatchAsync(IJob job, JobStepBatchId batchId, LogId? newLogId = null, JobStepBatchState? newState = null, JobStepBatchError? newError = null, CancellationToken cancellationToken = default)` — Attempts to update the state of a batch
- L908-932 _public method_ `public async Task<IJob?> UpdateStepAsync(IJob job, JobStepBatchId batchId, JobStepId stepId, StreamConfig streamConfig, JobStepState newState = JobStepState.Unspecified, JobStepOutcome newOutcome = JobStepOutcome.Unspecified, JobStepError? newError = null, bool? newAbortRequested = null, UserId? newAbortByUserId = null, LogId? newLogId = null, NotificationTriggerId? newNotificationTriggerId = null, UserId? newRetryByUserId = null, Priority? newPriority = null, List<JobReport>? newReports = null, Dictionary<string, string?>? newProperties = null, string? newCancellationReason = null, JobId? newSpawnedJob = null, CancellationToken cancellationToken = default)` — Update a jobstep state
- L956-1126 _public method_ `public async Task<IJob?> TryUpdateStepAsync(IJob job, JobStepBatchId batchId, JobStepId stepId, StreamConfig streamConfig, JobStepState newState = JobStepState.Unspecified, JobStepOutcome newOutcome = JobStepOutcome.Unspecified, JobStepError? newError = null, bool? newAbortRequested = null, UserId? newAbortByUserId = null, LogId? newLogId = null, NotificationTriggerId? newTriggerId = null, UserId? newRetryByUserId = null, Priority? newPriority = null, List<JobReport>? newReports = null, Dictionary<string, string?>? newProperties = null, string? newCancellationReason = null, JobId? newSpawnedJob = null, CancellationToken cancellationToken = default)` — Update a jobstep state
- L1136-1139 _public method_ `public async Task<IJob?> UpdateMetadataAsync(JobId jobId, List<string>? jobMetadata = null, Dictionary<JobStepId, List<string>>? stepMetadata = null, CancellationToken cancellationToken = default)` — Update a job and step metadata
- L1149-1218 _private method_ `private async Task<IJob> AutoSubmitChangeAsync(StreamConfig streamConfig, IJob job, IGraph graph, CancellationToken cancellationToken)` — Submit the given change for a preflight
- L1226-1243 _private method_ `private Task<bool> DeleteShelvedChangeAsync(string clusterName, CommitId change)` — Deletes a shelved changelist, catching and logging any exceptions
- L1253-1331 _private method_ `private async Task<IJob?> FireJobTriggerAsync(IJob job, IGraph graph, IChainedJob jobTrigger, StreamConfig streamConfig)` — Fires a trigger for a chained job
- L1342-1346 _public method_ `public async Task<bool> AuthorizeAsync(JobId jobId, AclAction action, ClaimsPrincipal user, BuildConfig buildConfig, CancellationToken cancellationToken)` — Determines if the user is authorized to perform an action on a particular stream
- L1349-1352 _public method_ `public async ValueTask<bool> AuthorizeAsync(ILog log, AclAction action, ClaimsPrincipal principal, CancellationToken cancellationToken)` — (inheritdoc)
- L1360-1363 _public method_ `public static bool AuthorizeSession(IJob job, ClaimsPrincipal user)` — Determines if the user is authorized to perform an action on a particular stream
- L1371-1399 _public method_ `public static bool AuthorizeSession(IJobStepBatch batch, ClaimsPrincipal user)` — Determines if the user is authorized to perform an action on a particular stream
- L1406-1409 _public method_ `public static string GetAllBatchSessionIds(IJob job)` — Get a list of each batch's session ID formatted as a string for debugging purposes
- L1416-1419 _public method_ `public IAuditLogChannel<JobId> GetJobLogger(JobId jobId)` — Get the logger for the specified job id

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/JobStepRefCollection.cs` (HordeServer.Build)


#### class `HordeServer.Jobs.JobStepRefCollection`  
`public class JobStepRefCollection : IJobStepRefCollection`  
_public; L25-348_
- inherits: `IJobStepRefCollection`
- desc: Collection of JobStepRef documents
- L151 _private* field_ `readonly IMongoCollection<JobStepRef> _jobStepRefs`
- L152 _private* field_ `readonly ITelemetryWriter _telemetryWriter`
- L153 _private* field_ `readonly IOptionsMonitor<BuildConfig> _buildConfig`
- L158-172 _public ctor_ `public JobStepRefCollection(IMongoService mongoService, ITelemetryWriter telemetryWriter, IOptionsMonitor<BuildConfig> buildConfig)` — Constructor
- L175-219 _public method_ `public async Task<IJobStepRef> InsertOrReplaceAsync(JobStepRefId id, string jobName, string stepName, StreamId streamId, TemplateId templateId, CommitIdWithOrder commitId, LogId? logId, PoolId? poolId, AgentId? agentId, JobStepState? state, JobStepOutcome? outcome, bool updateIssues, CommitIdWithOrder? lastSuccess, CommitIdWithOrder? lastWarning, float waitTime, float initTime, DateTime jobStartTimeUtc, DateTime startTimeUtc, DateTime? finishTimeUtc, List<string>? stepMetadata = null, ILogger? logger = null)` — (inheritdoc)
- L222-239 _public method_ `public async Task<IJobStepRef?> UpdateAsync(JobId jobId, JobStepBatchId batchId, JobStepId stepId, List<int>? issueIds)` — (inheritdoc)
- L242-246 _public method_ `public async Task<IJobStepRef?> FindAsync(JobId jobId, JobStepBatchId batchId, JobStepId stepId)` — (inheritdoc)
- L249-257 _public method_ `public async Task<List<IJobStepRef>> FindAsync(JobStepRefId[] ids, CancellationToken cancellationToken)` — (inheritdoc)
- L260-286 _public method_ `public async Task<List<IJobStepRef>> GetStepsForNodeAsync(StreamId streamId, TemplateId templateId, string nodeName, CommitIdWithOrder? commitId, bool includeFailed, int maxCount, bool includePreStartAndSkippedStates, CancellationToken cancellationToken)` — (inheritdoc)
- L289-319 _public method_ `public async Task<IJobStepRef?> GetPrevStepForNodeAsync(StreamId streamId, TemplateId templateId, string nodeName, CommitIdWithOrder commitId, JobStepOutcome? outcome = null, bool? updateIssues = null, IEnumerable<JobId>? excludeJobIds = null)` — (inheritdoc)
- L322-347 _public method_ `public async Task<IJobStepRef?> GetNextStepForNodeAsync(StreamId streamId, TemplateId templateId, string nodeName, CommitIdWithOrder commitId, JobStepOutcome? outcome = null, bool? updateIssues = null)` — (inheritdoc)

#### class `HordeServer.Jobs.JobStepRefCollection.JobStepRef`  
`class JobStepRef : IJobStepRef`  
_private*; L27-149_
- inherits: `IJobStepRef`
- L30 _public property_ `public JobStepRefId Id { get; set; }` — attrs: `[BsonId]`
- L32 _public property_ `public JobId? JobId { get; set; }`
- L34 _public property_ `public JobStepBatchId? BatchId { get; set; }`
- L36 _public property_ `public JobStepId? StepId { get; set; }`
- L38 _public property_ `public string JobName { get; set; }`
- L40 _public property_ `public string Name { get; set; }`
- L42 _public property_ `public StreamId StreamId { get; set; }`
- L43 _public property_ `public TemplateId TemplateId { get; set; }`
- L46-50 _public property_ `public CommitIdWithOrder CommitId { get; set; }` — attrs: `[BsonIgnore]`
- L53 _public property_ `public string? CommitName { get; set; }` — attrs: `[BsonElement("Commit")]`
- L56 _public property_ `public int CommitOrder { get; set; }` — attrs: `[BsonElement("Change")]`
- L58 _public property_ `public LogId? LogId { get; set; }`
- L59 _public property_ `public PoolId? PoolId { get; set; }`
- L60 _public property_ `public AgentId? AgentId { get; set; }`
- L61 _public property_ `public JobStepState? State { get; set; }`
- L62 _public property_ `public JobStepOutcome? Outcome { get; set; }`
- L65 _public property_ `public List<string>? Metadata { get; set; }` — attrs: `[BsonElement("md"), BsonIgnoreIfNull]`
- L68-72 _public property_ `public CommitIdWithOrder? LastSuccess { get; set; }` — attrs: `[BsonIgnore]`
- L75 _public property_ `public string? LastSuccessName { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L78 _public property_ `public int? LastSuccessOrder { get; set; }` — attrs: `[BsonElement("LastSuccess"), BsonIgnoreIfNull]`
- L81-85 _public property_ `public CommitIdWithOrder? LastWarning { get; set; }` — attrs: `[BsonIgnore]`
- L88 _public property_ `public string? LastWarningName { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L91 _public property_ `public int? LastWarningOrder { get; set; }` — attrs: `[BsonElement("LastWarning"), BsonIgnoreIfNull]`
- L93 _public property_ `public float BatchWaitTime { get; set; }`
- L94 _public property_ `public float BatchInitTime { get; set; }`
- L96 _public property_ `public DateTime JobStartTimeUtc { get; set; }`
- L99 _public property_ `public DateTimeOffset? StartTime { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L102 _public property_ `public DateTime? StartTimeUtc { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L105 _public property_ `public DateTimeOffset? FinishTime { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L108 _public property_ `public DateTime? FinishTimeUtc { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L111 _public property_ `public bool? UpdateIssues { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L114 _public property_ `public List<int>? IssueIds { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L116 _private* property_ `DateTime IJobStepRef.StartTimeUtc => ...`
- L117 _private* property_ `DateTime? IJobStepRef.FinishTimeUtc => ...`
- L118 _private* property_ `string IJobStepRef.NodeName => ...`
- L119 _private* property_ `bool IJobStepRef.UpdateIssues => ...`
- L120 _private* property_ `IReadOnlyList<int>? IJobStepRef.IssueIds => ...`
- L121 _private* property_ `IReadOnlyList<string>? IJobStepRef.Metadata => ...`
- L123-148 _public ctor_ `public JobStepRef(JobStepRefId id, JobId? jobId, JobStepBatchId? batchId, JobStepId? stepId, string jobName, string nodeName, StreamId streamId, TemplateId templateId, CommitIdWithOrder commitId, LogId? logId, PoolId? poolId, AgentId? agentId, JobStepState? state, JobStepOutcome? outcome, bool updateIssues, CommitIdWithOrder? lastSuccess, CommitIdWithOrder? lastWarning, float batchWaitTime, float batchInitTime, DateTime jobStartTimeUtc, DateTime startTimeUtc, DateTime? finishTimeUtc, List<string>? stepMetadata = null)`

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/JobStepRefIdSerializer.cs` (HordeServer.Build)


#### class `HordeServer.Jobs.JobStepRefIdSerializer`  
`public sealed class JobStepRefIdSerializer : IBsonSerializer<JobStepRefId>`  
_public; L11-39_
- inherits: `IBsonSerializer<JobStepRefId>`
- desc: Serializer for JobStepRefId objects
- L14 _public property_ `public Type ValueType => ...` — (inheritdoc)
- L17-20 _private* method_ `void IBsonSerializer.Serialize(BsonSerializationContext context, BsonSerializationArgs args, object value)` — (inheritdoc)
- L23-26 _private* method_ `object IBsonSerializer.Deserialize(BsonDeserializationContext context, BsonDeserializationArgs args)` — (inheritdoc)
- L29-32 _public method_ `public JobStepRefId Deserialize(BsonDeserializationContext context, BsonDeserializationArgs args)` — (inheritdoc)
- L35-38 _public method_ `public void Serialize(BsonSerializationContext context, BsonSerializationArgs args, JobStepRefId value)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/JobTaskSource.cs` (HordeServer.Build)


#### class `HordeServer.Jobs.JobTaskSource`  
`public sealed class JobTaskSource : TaskSourceBase<ExecuteJobTask>, IHostedService, IAsyncDisposable`  
_public; L40-1308_
- inherits: `TaskSourceBase<ExecuteJobTask>, IHostedService, IAsyncDisposable`
- desc: Background service to dispatch pending work to agents in priority order.
- L43 _public property_ `public override string Type => ...` — (inheritdoc)
- L46 _public property_ `public override TaskSourceFlags Flags => ...` — (inheritdoc)
- L190 _private* field_ `readonly Lazy<AgentService> _agentService` — Use lazy initialization of agent service to prevent circular dependency as AgentService depend on this class
- L192 _private* field_ `readonly IAclService _aclService`
- L193 _private* field_ `readonly IStreamCollection _streamCollection`
- L194 _private* field_ `readonly ILogCollection _logCollection`
- L195 _private* field_ `readonly IJobCollection _jobs`
- L196 _private* field_ `readonly IJobStepRefCollection _jobStepRefs`
- L197 _private* field_ `readonly IGraphCollection _graphs`
- L198 _private* field_ `readonly IPoolCollection _poolCollection`
- L199 _private* field_ `readonly IBisectTaskCollection _bisectTasks`
- L200 _private* field_ `readonly PoolService _poolService`
- L201 _private* field_ `readonly IUgsMetadataCollection _ugsMetadataCollection`
- L202 _private* field_ `readonly PerforceLoadBalancer _perforceLoadBalancer`
- L203 _private* field_ `readonly IClock _clock`
- L204 _private* field_ `readonly IServerInfo _serverInfo`
- L205 _private* field_ `readonly IOptionsMonitor<BuildServerConfig> _settings`
- L206 _private* field_ `readonly IOptionsMonitor<BuildConfig> _buildConfig`
- L207 _private* field_ `readonly ILogger<JobTaskSource> _logger`
- L208 _private* field_ `readonly Tracer _tracer`
- L209 _private* field_ `readonly ITicker _ticker`
- L210 _private* field_ `readonly IEnumerable<IWorkspaceMessageEnricher> _workspaceEnrichers`
- L213 _private* field_ `readonly object _lockObject = new object()`
- L216 _private* field_ `SortedSet<QueueItem> _queue = new SortedSet<QueueItem>(new QueueItemComparer())`
- L219 _private* field_ `Dictionary<(JobId, JobStepBatchId), QueueItem> _batchIdToQueueItem = ...`
- L219 _private* field_ `Dictionary<(JobId, _batchIdToQueueItem = new Dictionary<(JobId, JobStepBatchId), QueueItem>()`
- L222 _private* field_ `readonly HashSet<QueueWaiter> _waiters = new HashSet<QueueWaiter>()`
- L225 _private* field_ `readonly HashSet<(JobId, JobStepBatchId)> _scheduledNotificationFired = new HashSet<(JobId, JobStepBatchId)>()`
- L228 _private* field_ `List<QueueItem>? _newQueueItemsDuringUpdate`
- L233 _public delegate_ `public delegate void JobScheduleEvent(IPoolConfig pool, bool hasAgentsOnline, IJob job, IGraph graph, JobStepBatchId batchId)` — Delegate for job schedule events
- L238 _public event_ `public event JobScheduleEvent? OnJobScheduled` — Event triggered when a job is scheduled
- L241 _private* field_ `static readonly TimeSpan s_refreshInterval = TimeSpan.FromSeconds(5.0)`
- L246-270 _public ctor_ `public JobTaskSource(IAclService aclService, Lazy<AgentService> agentService, IJobCollection jobs, IJobStepRefCollection jobStepRefs, IBisectTaskCollection bisectTasks, IGraphCollection graphs, IPoolCollection pools, PoolService poolService, IUgsMetadataCollection ugsMetadataCollection, IStreamCollection streamCollection, ILogCollection logCollection, PerforceLoadBalancer perforceLoadBalancer, IClock clock, IServerInfo serverInfo, IOptionsMonitor<BuildServerConfig> settings, IOptionsMonitor<BuildConfig> buildConfig, Tracer tracer, ILogger<JobTaskSource> logger, IEnumerable<IWorkspaceMessageEnricher> workspaceEnrichers)` — Constructor
- L273 _public method_ `public Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L276 _public method_ `public Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L279 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L285-303 _public method_ `public object GetStatus()` — Gets an object containing the stats of the queue for diagnostic purposes.
- L309-320 _public method_ `public void CancelLongPollForAgent(AgentId agentId)` — Cancel any pending wait for an agent, allowing it to cycle its session state immediately
- L346-363 _internal method_ `internal static Dictionary<PoolId, PoolStatus> GetPoolStatus(DateTime utcNow, IReadOnlyList<IPoolConfig> pools, IReadOnlyList<IAgent> agents)` — Calculate status of agents for a pool
- L370-550 _internal method_ `internal async ValueTask TickAsync(CancellationToken cancellationToken)` — Background task
- L552-564 _private method_ `private async Task<IJob?> SkipBatchAsync(IJob job, JobStepBatchId batchId, IGraph graph, JobStepBatchError reason, CancellationToken cancellationToken)`
- L570-576 _internal method_ `internal SortedSet<QueueItem> GetQueueForTesting()` — Get the queue, for internal testing only
- L578-590 _private* method_ `void AssignAnyQueueItemToWaiter(QueueWaiter waiter)`
- L598-616 _private* method_ `void AssignQueueItemToAnyWaiter(QueueItem item)` — attrs: `[SuppressMessage("Maintainability", "CA1508:Avoid dead conditional code", Justification = "<Pending>")]` — Attempt to find a waiter that can handle the given queue item
- L624-638 _private* method_ `bool TryAssignItemToWaiter(QueueItem item, QueueWaiter waiter)` — Attempts to assign a queue item to an agent waiting for work
- L645-725 _public method_ `public void UpdateQueuedJob(IJob job, IGraph graph)` — Updates the current state of a job
- L728-750 _public method_ `public override Task<Task<CreateLeaseOptions?>> AssignLeaseAsync(IAgent agent, CancellationToken cancellationToken)` — (inheritdoc)
- L752-768 _private method_ `private async Task<CreateLeaseOptions?> WaitForLeaseAsync(QueueWaiter waiter, CancellationToken cancellationToken)`
- L771-774 _public method_ `public override Task CancelLeaseAsync(IAgent agent, LeaseId leaseId, ExecuteJobTask task, CancellationToken cancellationToken)` — (inheritdoc)
- L776-795 _private method_ `private async Task<bool> AutoConformAgentAsync(IAgent agent, CancellationToken cancellationToken)`
- L804-927 _private method_ `private async Task<CreateLeaseOptions?> TryCreateLeaseAsync(QueueItem item, QueueWaiter waiter, CancellationToken cancellationToken)` — Assign a new batch to be executed by the given agent
- L929-1017 _private* method_ `async Task<ExecuteJobTask?> CreateExecuteJobTaskAsync(LeaseId leaseId, StreamConfig streamConfig, IJob job, IJobStepBatch batch, IAgent agent, AgentWorkspaceInfo workspace, AgentWorkspaceInfo? autoSdkWorkspace, LogId logId, CancellationToken cancellationToken)`
- L1019-1032 _private* method_ `static RpcJobOptions GetRpcJobOptions(JobOptions options)`
- L1034-1042 _private* method_ `static RpcJobContainerOptions GetRpcJobContainerOptions(JobContainerOptions options)`
- L1052-1055 _public method_ `public async Task UpdateUgsBadgesAsync(IJob job, IGraph graph, IReadOnlyList<(LabelState, LabelOutcome)> oldLabelStates, CancellationToken cancellationToken)` — Send any badge updates for this job
- L1066-1158 _public method_ `public async Task UpdateUgsBadgesAsync(IJob job, IGraph graph, IReadOnlyList<(LabelState, LabelOutcome)> oldLabelStates, IReadOnlyList<(LabelState, LabelOutcome)> newLabelStates, CancellationToken cancellationToken)` — Send any badge updates for this job
- L1161-1232 _public method_ `public override async Task OnLeaseFinishedAsync(IAgent agent, LeaseId leaseId, ExecuteJobTask task, LeaseOutcome outcome, ReadOnlyMemory<byte> output, ILogger logger, CancellationToken cancellationToken)` — (inheritdoc)
- L1242-1273 _private* method_ `async Task CancelLeaseAsync(IAgent agent, JobId jobId, JobStepBatchId batchId, CancellationToken cancellationToken)`
- L1284-1293 _private* method_ `void InsertQueueItem(IJob job, int batchIdx, PoolId poolId, AgentWorkspaceInfo workspace, bool useAutoSdk)` — Inserts an item into the queue
- L1299-1307 _private* method_ `void RemoveQueueItem(QueueItem item)` — Removes an item from the queue

#### class `HordeServer.Jobs.JobTaskSource.QueueItem`  
`internal class QueueItem`  
_internal; L52-115_
- attrs: `[DebuggerDisplay("{_job.Id}:{Batch.Id} ({_poolId})")]`
- desc: An item in the queue to be executed
- L57 _public field_ `public IJob _job` — The job instance
- L62 _public field_ `public int _batchIdx` — Index of the batch within this job to be executed
- L67 _public field_ `public PoolId _poolId` — The pool of machines to allocate from
- L72 _public field_ `public AgentWorkspaceInfo _workspace` — The type of workspace that this item should run in
- L77 _public field_ `public bool _useAutoSdk` — Whether or not to use the AutoSDK.
- L82 _public field_ `public Task? _assignTask` — Task for creating a lease and assigning to a waiter
- L87 _public property_ `public IJobStepBatch Batch => ...` — Accessor for the batch referenced by this item
- L92 _public property_ `public (JobId, JobStepBatchId) Id => ...` — Returns an identifier describing this unique batch
- L97 _public field_ `public bool _removed` — Whether the item has been removed from the list
- L107-114 _public ctor_ `public QueueItem(IJob job, int batchIdx, PoolId poolId, AgentWorkspaceInfo workspace, bool useAutoSdk)` — Constructor

#### class `HordeServer.Jobs.JobTaskSource.QueueItemComparer`  
`class QueueItemComparer : IComparer<QueueItem>`  
_private*; L120-150_
- inherits: `IComparer<QueueItem>`
- desc: Comparer for items in the queue
- L128-149 _public method_ `public int Compare([AllowNull] QueueItem x, [AllowNull] QueueItem y)` — Compare two items

#### class `HordeServer.Jobs.JobTaskSource.QueueWaiter`  
`class QueueWaiter`  
_private*; L155-185_
- desc: Information about an agent waiting for work
- L160 _public property_ `public IAgent Agent { get; }` — The agent performing the wait
- L165 _public property_ `public Task<CreateLeaseOptions?> Task => ...` — Task to wait for a lease to be assigned
- L170 _public property_ `public TaskCompletionSource<CreateLeaseOptions?> LeaseSource { get; }` — Completion source for the waiting agent. If a new queue item becomes available, the result will be passed through
- L175 _public property_ `public bool Skip { get; set; }` — Ignore the waiting agent when trying to assign a new queue item
- L181-184 _public ctor_ `public QueueWaiter(IAgent agent)` — Constructor

#### class `HordeServer.Jobs.JobTaskSource.PoolStatus`  
`internal class PoolStatus`  
_internal; L322-337_
- L324 _public field_ `public readonly IPoolConfig Pool`
- L325 _public field_ `public readonly bool HasAgents`
- L326 _public field_ `public readonly bool HasEnabledAgents`
- L327 _public field_ `public readonly bool HasOnlineAgents`
- L328 _public property_ `public bool IsAutoScaled => ...`
- L330-336 _public ctor_ `public PoolStatus(IPoolConfig pool, bool hasAgents, bool hasEnabledAgents, bool hasOnlineAgents)`

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/JobTelemetry.cs` (HordeServer.Build)


#### record `HordeServer.Jobs.JobSummaryTelemetry`  
`public record JobSummaryTelemetry : AbstractTelemetryRecord`  
_public; L24-200_
- attrs: `[AnalyticsTableGen] [Table("horde.state_job_summary", Schema = "ingest")] [TelemetryEvent(DefaultEventName)]`
- inherits: `AbstractTelemetryRecord`
- desc: Record used for Job Summary telemetry. Models a IJob.
- L30 _public property_ `public JobId JobId { get; init; }` — attrs: `[Column("job_id")]` — The job Id.
- L36 _public property_ `public TemplateId TemplateId { get; init; }` — attrs: `[Column("template_id")]` — The template of the job.
- L42 _public property_ `public StreamId StreamId { get; init; }` — attrs: `[Column("stream_id")]` — The stream of the job.
- L48 _public property_ `public string CommitId { get; init; }` — attrs: `[Column("commit_id")]` — The commit of the job. IJob.CommitId.
- L54 _public property_ `public string CodeCommitId { get; init; }` — attrs: `[Column("code_commit_id")]` — The code commit of the job. IJob.CodeCommitId.
- L60 _public property_ `public DateTime CreateTimeUtc { get; init; }` — attrs: `[Column("create_time_utc")]` — The created time of the job.
- L66 _public property_ `public DateTime FinishTimeUtc { get; init; }` — attrs: `[Column("finish_time_utc")]` — The finish time of the job.
- L72 _public property_ `public float JobStepsTotalTime { get; init; }` — attrs: `[Column("job_steps_total_time")]` — The summed duration of all steps.
- L78 _public property_ `public float JobWallTime { get; init; }` — attrs: `[Column("job_wall_time")]` — The wall time of the job, in seconds.
- L84 _public property_ `public float PassRatio { get; init; }` — attrs: `[Column("pass_ratio")]` — JobStepsCompletionInfo.PassRatio.
- L90 _public property_ `public float PassWithWarningRatio { get; init; }` — attrs: `[Column("pass_with_warning_ratio")]` — JobStepsCompletionInfo.PassWithWarningRatio.
- L96 _public property_ `public float WarningRatio { get; init; }` — attrs: `[Column("warning_ratio")]` — JobStepsCompletionInfo.WarningRatio.
- L102 _public property_ `public float FailureRatio { get; init; }` — attrs: `[Column("failure_ratio")]` — JobStepsCompletionInfo.FailureRatio.
- L108 _public property_ `public int StepPassCount { get; init; }` — attrs: `[Column("step_pass_count")]` — JobStepsCompletionInfo.StepPassCount.
- L114 _public property_ `public int StepWarningCount { get; init; }` — attrs: `[Column("step_warning_count")]` — JobStepsCompletionInfo.StepWarningCount.
- L120 _public property_ `public int StepFailureCount { get; init; }` — attrs: `[Column("step_failure_count")]` — JobStepsCompletionInfo.StepFailureCount.
- L126 _public property_ `public int StepTotalCount { get; init; }` — attrs: `[Column("step_total_count")]` — JobStepsCompletionInfo.StepTotalCount.
- L132 _public property_ `public bool IsPreflight { get; init; }` — attrs: `[Column("is_preflight")]` — Whether the job was a preflight or not.
- L137 _public const_ `public const string DefaultEventName = "State.JobSummary"` — Default event name for the JobSummaryTelemetry.
- L142 _public field_ `public static readonly int CurrentSchemaVersion = 2` — Current schema version.
- L149-172 _public ctor_ `public JobSummaryTelemetry(IJob job, DateTime finishTimeUtc) : base(DefaultEventName, CurrentSchemaVersion)` — Constructs a JobSummary Telemetry event.
- L178-199 _public ctor_ `public JobSummaryTelemetry() : base(DefaultEventName, CurrentSchemaVersion)` — Default constructor for an empty telemetry object,

#### class `HordeServer.Jobs.JobLabelTelemetryHelpers`  
`public static class JobLabelTelemetryHelpers`  
_public; L205-274_
- desc: Helpers associated with producing JobLabelTelemetry and JobLabelSummaryTelemetry.
- L210 _public const_ `public const string FullyQualifiedLabelDelimiter = "-"` — Delimiter used in separating the Label Category and the Label Name.
- L218-221 _public method_ `public static string CreateFullyQualifiedLabel(GetLabelStateResponse response)` — Creates a fully qualified label name.
- L230-233 _public method_ `public static string CreateFullyQualifiedLabel(string? dashboardCategory, string? dashboardName)` — Creates a fully qualified label name.
- L241-255 _public method_ `public static IList<JobLabelTelemetry> CreateJobLabelTelemetryEvents(IJob job, IGraph graph)` — Creates a list of job label telemetry events for a given job and graph.
- L264-273 _public method_ `public static void EmitJobLabelTelemetry(ITelemetryWriter telemetryWriter, TelemetryStoreId telemetryStoreId, IJob job, IGraph graph)` — Emits all job label telemetry for a given job and graph.

#### record `HordeServer.Jobs.JobLabelSummaryTelemetry`  
`public record JobLabelSummaryTelemetry : AbstractTelemetryRecord`  
_public; L282-432_
- attrs: `[AnalyticsTableGen] [Table("horde.state_job_label_summary", Schema = "ingest")] [TelemetryEvent(DefaultEventName)]`
- inherits: `AbstractTelemetryRecord`
- desc: Record used for Job Label Summary telemetry. Models a IJob and IGraph.
- L288 _public property_ `public JobId JobId { get; init; }` — attrs: `[Column("job_id")]` — The job Id.
- L294 _public property_ `public string GraphContentHash { get; init; }` — attrs: `[Column("graph_content_hash")]` — The graph content hash.
- L300 _public property_ `public TemplateId TemplateId { get; init; }` — attrs: `[Column("template_id")]` — The template of the job.
- L306 _public property_ `public StreamId StreamId { get; init; }` — attrs: `[Column("stream_id")]` — The stream of the job.
- L312 _public property_ `public string CommitId { get; init; }` — attrs: `[Column("commit_id")]` — The commit of the job. IJob.CommitId.
- L318 _public property_ `public string?[] SuccessfulLabels { get; init; }` — attrs: `[Column("successful_labels")]` — Array representing all labels that were successful in the job.
- L324 _public property_ `public string?[] WarningLabels { get; init; }` — attrs: `[Column("warning_labels")]` — Array representing all labels that were warnings in the job.
- L330 _public property_ `public string?[] FailedLabels { get; init; }` — attrs: `[Column("failed_labels")]` — Array representing all labels that were failures in the job.
- L336 _public property_ `public string?[] SuccessfulCategories { get; init; }` — attrs: `[Column("successful_categories")]` — Array representing all categories that were successful in the job.
- L342 _public property_ `public string?[] WarningCategories { get; init; }` — attrs: `[Column("warning_categories")]` — Array representing all categories that were warnings in the job.
- L348 _public property_ `public string?[] FailedCategories { get; init; }` — attrs: `[Column("failed_categories")]` — Array representing all categories that were failures in the job.
- L353 _public const_ `public const string DefaultEventName = "State.JobLabelSummary"` — Default event name for the JobLabelSummaryTelemetry.
- L358 _public field_ `public static readonly int CurrentSchemaVersion = 1` — Current schema version.
- L364-377 _public ctor_ `public JobLabelSummaryTelemetry() : base(DefaultEventName, CurrentSchemaVersion)` — Default constructor for an empty telemetry object.
- L384-431 _public ctor_ `public JobLabelSummaryTelemetry(IJob job, IGraph graph) : base(DefaultEventName, CurrentSchemaVersion)` — Constructor.

#### record `HordeServer.Jobs.JobLabelTelemetry`  
`public record JobLabelTelemetry : AbstractTelemetryRecord`  
_public; L440-540_
- attrs: `[AnalyticsTableGen] [Table("horde.state_job_label", Schema = "ingest")] [TelemetryEvent(DefaultEventName)]`
- inherits: `AbstractTelemetryRecord`
- desc: Record used for Job Label telemetry. Models a IJob and IGraph.
- L446 _public property_ `public JobId JobId { get; init; }` — attrs: `[Column("job_id")]` — The job Id.
- L452 _public property_ `public string GraphContentHash { get; init; }` — attrs: `[Column("graph_content_hash")]` — The graph content hash.
- L458 _public property_ `public TemplateId TemplateId { get; init; }` — attrs: `[Column("template_id")]` — The template of the job.
- L464 _public property_ `public StreamId StreamId { get; init; }` — attrs: `[Column("stream_id")]` — The stream of the job.
- L470 _public property_ `public string CommitId { get; init; }` — attrs: `[Column("commit_id")]` — The commit of the job. IJob.CommitId.
- L476 _public property_ `public string? Category { get; init; }` — attrs: `[Column("category")]` — The category of the label.
- L482 _public property_ `public string? Label { get; init; }` — attrs: `[Column("label")]` — The label.
- L488 _public property_ `public LabelOutcome? Outcome { get; init; }` — attrs: `[Column("outcome")]` — The outcome of the label.
- L494 _public property_ `public LabelState? State { get; init; }` — attrs: `[Column("state")]` — The state of the label.
- L499 _public const_ `public const string DefaultEventName = "State.JobLabel"` — Default event name for the JobLabelTelemetry.
- L504 _public field_ `public static readonly int CurrentSchemaVersion = 1` — Current schema version.
- L510-517 _public ctor_ `public JobLabelTelemetry() : base(DefaultEventName, CurrentSchemaVersion)` — Default constructor for an empty telemetry object.
- L528-539 _public ctor_ `public JobLabelTelemetry(IJob job, IGraph graph, string? category, string? name, LabelOutcome? outcome, LabelState? state) : base(DefaultEventName, CurrentSchemaVersion)` — Constructor.

#### record `HordeServer.Jobs.JobStepRefTelemetry`  
`public record JobStepRefTelemetry : AbstractTelemetryRecord`  
_public; L548-820_
- attrs: `[AnalyticsTableGen] [Table("horde.state_job_step_ref", Schema = "ingest")] [TelemetryEvent(DefaultEventName)]`
- inherits: `AbstractTelemetryRecord`
- desc: Record used for Job Step Ref telemetry. Models a Job Step Ref.
- L554 _public property_ `public string Id { get; init; }` — attrs: `[Column("id")]` — The job step ref id.
- L560 _public property_ `public string JobId { get; init; }` — attrs: `[Column("job_id")]` — The job id.
- L566 _public property_ `public string BatchId { get; init; }` — attrs: `[Column("batch_id")]` — The batch id.
- L572 _public property_ `public string StepId { get; init; }` — attrs: `[Column("step_id")]` — The step id.
- L578 _public property_ `public float BatchInitTime { get; init; }` — attrs: `[Column("batch_init_time")]` — The init time of the batch.
- L584 _public property_ `public float BatchWaitTime { get; init; }` — attrs: `[Column("batch_wait_time")]` — The wait time of the batch.
- L590 _public property_ `public string? Change { get; init; }` — attrs: `[Column("change")]` — The commit id.
- L596 _public property_ `public string JobName { get; init; }` — attrs: `[Column("job_name")]` — The job name.
- L602 _public property_ `public DateTime? FinishTime { get; init; }` — attrs: `[Column("finish_time")]` — The step finish time.
- L608 _public property_ `public DateTime? JobStartTime { get; init; }` — attrs: `[Column("job_start_time")]` — The owning job's start time.
- L614 _public property_ `public string StepName { get; init; }` — attrs: `[Column("step_name")]` — The step name.
- L620 _public property_ `public JobStepState? State { get; init; }` — attrs: `[Column("state")]` — The step state.
- L626 _public property_ `public JobStepOutcome? Outcome { get; init; }` — attrs: `[Column("outcome")]` — The step outcome.
- L632 _public property_ `public PoolId? PoolId { get; init; }` — attrs: `[Column("pool_id")]` — The pool id of the associated agent.
- L638 _public property_ `public DateTime? StartTime { get; init; }` — attrs: `[Column("start_time")]` — The start time of the step.
- L644 _public property_ `public StreamId StreamId { get; init; }` — attrs: `[Column("stream_id")]` — The stream id.
- L650 _public property_ `public TemplateId TemplateId { get; init; }` — attrs: `[Column("template_id")]` — The template id of the owning job.
- L656 _public property_ `public AgentId? AgentId { get; init; }` — attrs: `[Column("agent_id")]` — The id of the agent that ran the step.
- L662 _public property_ `public bool UpdateIssues { get; init; }` — attrs: `[Column("update_issues")]` — Whether issues have been updated or not.
- L668 _public property_ `public double? Duration { get; init; }` — attrs: `[Column("duration")]` — The duration of the step.
- L674 _public property_ `public string? Message { get; init; }` — attrs: `[Column("message")]` — The message from the step report, if any.
- L680 _public property_ `public string? MessageSeverity { get; init; }` — attrs: `[Column("message_severity")]` — The severity from the step report message, if any.
- L685 _public const_ `public const string DefaultEventName = "State.JobStepRef"` — The default event name.
- L690 _public field_ `public static readonly int CurrentSchemaVersion = 2` — Current schema version.
- L696-709 _public ctor_ `public JobStepRefTelemetry() : base(DefaultEventName, CurrentSchemaVersion)` — Default constructor for an empty telemetry object.
- L736-760 _public ctor_ `public JobStepRefTelemetry(string id, string jobId, string batchId, string stepId, AgentId? agentId, float batchInitTime, float batchWaitTime, string? change, DateTime? finishTime, string jobName, DateTime? jobStartTime, string stepName, JobStepState? state, JobStepOutcome? outcome, PoolId? poolId, DateTime? startTime, StreamId streamId, TemplateId templateId, bool updateIssues, double? duration, string? message = null, string? messageSeverity = null) : base(DefaultEventName, CurrentSchemaVersion)` — Constructor.
- L772-819 _public method_ `public static JobStepRefTelemetry? ConstructJobStepRefTelemetryFromJob(IJob? job, int batchIdx, int stepIdx, JobStepOutcome newOutcome, JobStepState newStepState)` — Create method used to construct a JobStepRef telemetry event from a job, the provided batch index, and step index. This will take a new outcome and state to use in the telemetry emission.

#### record `HordeServer.Jobs.JobCreatedTelemetry`  
`public record JobCreatedTelemetry : AbstractTelemetryRecord`  
_public; L828-960_
- attrs: `[AnalyticsTableGen] [Table("horde.state_job", Schema = "ingest")] [TelemetryEvent(DefaultEventName)]`
- inherits: `AbstractTelemetryRecord`
- desc: Record used for Job Created telemetry. Emitted when a new job is created.
- L834 _public property_ `public JobId JobId { get; init; }` — attrs: `[Column("job_id")]` — The job Id.
- L840 _public property_ `public StreamId StreamId { get; init; }` — attrs: `[Column("stream_id")]` — The stream of the job.
- L846 _public property_ `public string[] Args { get; init; }` — attrs: `[Column("args")]` — The arguments passed to the job.
- L852 _public property_ `public bool? AutoSubmit { get; init; }` — attrs: `[Column("auto_submit")]` — Whether the job should auto-submit on completion.
- L858 _public property_ `public string Change { get; init; }` — attrs: `[Column("change")]` — The commit/change for this job.
- L864 _public property_ `public string? CodeChange { get; init; }` — attrs: `[Column("code_change")]` — The code commit/change for this job.
- L870 _public property_ `public DateTime CreateTimeUtc { get; init; }` — attrs: `[Column("create_time_utc")]` — The created time of the job.
- L876 _public property_ `public string GraphHash { get; init; }` — attrs: `[Column("graph_hash")]` — The graph hash for this job.
- L882 _public property_ `public string Name { get; init; }` — attrs: `[Column("name")]` — The name of the job.
- L888 _public property_ `public string? PreflightChange { get; init; }` — attrs: `[Column("preflight_change")]` — The preflight commit/change, if this is a preflight job.
- L894 _public property_ `public string? PreflightDescription { get; init; }` — attrs: `[Column("preflight_description")]` — Description of the preflight, if this is a preflight job.
- L900 _public property_ `public Priority Priority { get; init; }` — attrs: `[Column("priority")]` — The priority of the job.
- L906 _public property_ `public string? StartedByUserId { get; init; }` — attrs: `[Column("started_by_user_id")]` — The user who started this job.
- L912 _public property_ `public TemplateId TemplateId { get; init; }` — attrs: `[Column("template_id")]` — The template of the job.
- L917 _public const_ `public const string DefaultEventName = "State.Job"` — Default event name for the JobCreatedTelemetry.
- L922 _public field_ `public static readonly int CurrentSchemaVersion = 1` — Current schema version.
- L928-937 _public ctor_ `public JobCreatedTelemetry() : base(DefaultEventName, CurrentSchemaVersion)` — Default constructor for an empty telemetry object.
- L943-959 _public ctor_ `public JobCreatedTelemetry(IJob job) : base(DefaultEventName, CurrentSchemaVersion)` — Constructs a JobCreatedTelemetry event from a job.

#### class `HordeServer.Jobs.JobReportMetadataKeys`  
`static class JobReportMetadataKeys`  
_internal*; L965-981_
- desc: Keys used to store job report data in step metadata.
- L970 _public const_ `public const string MessageKey = "ReportStepMessage"` — Key for the report message.
- L975 _public const_ `public const string MessageSeverityKey = "ReportStepSeverity"` — Key for the report severity.
- L980 _public const_ `public const string ColorKey = "ReportStepColor"` — Key for the report color.

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/JobsController.cs` (HordeServer.Build)


#### class `HordeServer.Jobs.JobsController`  
`public class JobsController : HordeControllerBase`  
_public; L45-2548_
- attrs: `[ApiController] [Authorize] [Route("[controller]")]`
- inherits: `HordeControllerBase`
- desc: Controller for the /api/v1/jobs endpoint
- L47 _private field_ `private readonly IGraphCollection _graphs`
- L48 _private field_ `private readonly ICommitService _commitService`
- L49 _private field_ `private readonly IPerforceService _perforce`
- L50 _private field_ `private readonly JobService _jobService`
- L51 _private field_ `private readonly ITemplateCollectionInternal _templateCollection`
- L52 _private field_ `private readonly IArtifactCollection _artifactCollection`
- L53 _private field_ `private readonly IUserCollection _userCollection`
- L54 _private field_ `private readonly INotificationService _notificationService`
- L55 _private field_ `private readonly AgentService _agentService`
- L56 _private field_ `private readonly ILeaseCollection _leaseCollection`
- L57 _private field_ `private readonly IIssueCollection _issueCollection`
- L58 _private field_ `private readonly IMergeGraphService _mergeGraphService`
- L59 _private field_ `private readonly ILogCollection _logCollection`
- L60 _private field_ `private readonly IOptionsSnapshot<BuildConfig> _buildConfig`
- L61 _private field_ `private readonly ILogger<JobsController> _logger`
- L66-83 _public ctor_ `public JobsController(IGraphCollection graphs, ICommitService commitService, IPerforceService perforce, JobService jobService, ITemplateCollectionInternal templateCollection, IArtifactCollection artifactCollection, IUserCollection userCollection, INotificationService notificationService, AgentService agentService, ILeaseCollection leaseCollection, IIssueCollection issueCollection, IMergeGraphService mergeGraphService, ILogCollection logCollection, IOptionsSnapshot<BuildConfig> buildConfig, ILogger<JobsController> logger)` — Constructor
- L93-333 _public method_ `public async Task<ActionResult<CreateJobResponse>> CreateJobAsync([FromBody] CreateJobRequest create, CancellationToken cancellationToken = default)` — attrs: `[HttpPost] [Route("/api/v1/jobs")]` — Creates a new job
- L335-361 _private* method_ `async ValueTask<CommitIdWithOrder> GetChangeToBuildAsync(CreateJobRequest create, StreamId streamId, ITemplate template, ShelfInfo? shelfInfo, ICommitCollection commits, CancellationToken cancellationToken)`
- L371-387 _public method_ `public async Task<ActionResult> DeleteJobAsync(JobId jobId, CancellationToken cancellationToken)` — attrs: `[HttpDelete] [Route("/api/v1/jobs/{jobId}")]` — Deletes a specific job.
- L397-434 _public method_ `public async Task<ActionResult> UpdateJobAsync(JobId jobId, [FromBody] UpdateJobRequest request)` — attrs: `[HttpPut] [Route("/api/v1/jobs/{jobId}")]` — Updates a specific job.
- L445-481 _public method_ `public async Task<ActionResult> UpdateJobMetaDataAsync(JobId jobId, [FromBody] PutJobMetadataRequest request, CancellationToken cancellationToken = default)` — attrs: `[HttpPut] [Route("/api/v1/jobs/{jobId}/metadata")]` — Updates a specific job.
- L492-520 _public method_ `public async Task<ActionResult> UpdateNotificationsAsync(JobId jobId, [FromBody] UpdateNotificationsRequest request, CancellationToken cancellationToken)` — attrs: `[HttpPut] [Route("/api/v1/jobs/{jobId}/notifications")]` — Updates notifications for a specific job.
- L530-559 _public method_ `public async Task<ActionResult<GetNotificationResponse>> GetNotificationsAsync(JobId jobId, CancellationToken cancellationToken)` — attrs: `[HttpGet] [Route("/api/v1/jobs/{jobId}/notifications")]` — Gets information about a specific job.
- L572-602 _public method_ `public async Task<ActionResult<object>> GetJobAsync(JobId jobId, [FromQuery] DateTimeOffset? modifiedAfter = null, [FromQuery] PropertyFilter? filter = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/jobs/{jobId}")] [ProducesResponseType(typeof(GetJobResponse), 200)]` — Gets information about a specific job.
- L613-623 _private* method_ `async Task<object> CreateJobResponseAsync(IJob job, IGraph graph, bool includeCosts, PropertyFilter? filter, CancellationToken cancellationToken)` — Creates a response containing information about this object
- L636-731 _private* method_ `async ValueTask<GetJobResponse> CreateJobResponseAsync(IJob job, IGraph graph, bool includeBatches, bool includeLabels, bool includeCosts, bool includeArtifacts, CancellationToken cancellationToken)` — Creates a response containing information about this object
- L733-739 _private* method_ `static bool IncludeArtifactInResponse(IArtifact artifact)`
- L741-776 _private* method_ `static GetJobResponse CreateGetJobResponse(IJob job, GetThinUserInfoResponse? startedByUserInfo, GetThinUserInfoResponse? abortedByUserInfo, bool canUpdate)`
- L778-786 _private* method_ `static GetJobReportResponse CreateGetReportResponse(IJobReport report)`
- L795-821 _private* method_ `async ValueTask<GetJobBatchResponse> CreateBatchResponseAsync(IJobStepBatch batch, bool includeCosts, CancellationToken cancellationToken)` — Get the response object for a batch
- L831-851 _private* method_ `static GetJobBatchResponse CreateGetBatchResponse(IJobStepBatch batch, List<GetJobStepResponse> steps, double? agentRate, List<string>? leaseOutcomeReasons)` — Converts this batch into a public response object
- L858-870 _private* method_ `static List<string>? ToFlagNames(LeaseOutcomeReason reason)` — Converts a LeaseOutcomeReason flags enum to a list of flag names
- L878-893 _private* method_ `async ValueTask<GetJobStepResponse> CreateStepResponseAsync(IJobStep step, CancellationToken cancellationToken)` — Get the response object for a step
- L901-962 _private* method_ `static GetJobStepResponse CreateGetStepResponse(IJobStep step, GetThinUserInfoResponse? abortedByUserInfo, GetThinUserInfoResponse? retriedByUserInfo)` — Constructor
- L973-993 _public method_ `public async Task<ActionResult<object>> GetJobGraphAsync(JobId jobId, [FromQuery] PropertyFilter? filter = null)` — attrs: `[HttpGet] [Route("/api/v1/jobs/{jobId}/graph")] [ProducesResponseType(typeof(GetGraphResponse), 200)]` — Gets information about the graph for a specific job.
- L995-1011 _private* method_ `static GetGraphResponse CreateGetGraphResponse(IGraph graph)`
- L1013-1018 _private* method_ `static GetGroupResponse CreateGetGroupResponse(INodeGroup group, IReadOnlyList<INodeGroup> groups)`
- L1020-1037 _private* method_ `static GetNodeResponse CreateGetNodeResponse(INode node, IReadOnlyList<INodeGroup> groups)`
- L1039-1044 _private* method_ `static GetAggregateResponse CreateGetAggregateResponse(IAggregate aggregate, IReadOnlyList<INodeGroup> groups)`
- L1046-1056 _private* method_ `static GetLabelResponse CreateGetLabelResponse(ILabel label, IReadOnlyList<INodeGroup> groups)`
- L1068-1089 _public method_ `public async Task<ActionResult<object>> GetJobTimingAsync(JobId jobId, [FromQuery] PropertyFilter? filter = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/jobs/{jobId}/timing")] [ProducesResponseType(typeof(GetJobTimingResponse), 200)]` — Gets timing information about the graph for a specific job.
- L1091-1119 _private method_ `private async Task<GetJobTimingResponse> CreateJobTimingResponseAsync(IJob job, IGraph graph, IJobTiming jobTiming, ILogger logger, bool includeJobResponse = false, CancellationToken cancellationToken = default)`
- L1121-1131 _private* method_ `static GetLabelTimingInfoResponse CreateGetLabelTimingInfoResponse(ILabel label, TimingInfo timingInfo)`
- L1133-1143 _private* method_ `static GetStepTimingInfoResponse CreateGetStepTimingInfoResponse(string? name, TimingInfo jobTimingInfo)`
- L1157-1188 _public method_ `public async Task<ActionResult<object>> FindJobTimingsAsync( [FromQuery] string? streamId = null, [FromQuery(Name = "template")] string[]? templates = null, [FromQuery] PropertyFilter? filter = null, [FromQuery] int count = 100, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/jobs/timing")] [ProducesResponseType(typeof(FindJobTimingsResponse), 200)]` — Find timing information about the graph for multiple jobs
- L1199-1224 _public method_ `public async Task<ActionResult<object>> GetJobTemplateAsync(JobId jobId, [FromQuery] PropertyFilter? filter = null)` — attrs: `[HttpGet] [Route("/api/v1/jobs/{jobId}/template")] [ProducesResponseType(typeof(GetTemplateResponse), 200)]` — Gets information about the template for a specific job.
- L1255-1318 _public method_ `public async Task<ActionResult<List<object>>> FindJobsAsync( [FromQuery(Name = "Id")] string[]? ids = null, [FromQuery] string? streamId = null, [FromQuery] string? name = null, [FromQuery(Name = "template")] string[]? templates = null, [FromQuery(Name = "t")] string[]? templateIds = null, [FromQuery] CommitId? minChange = null, [FromQuery] CommitId? maxChange = null, [FromQuery] bool includePreflight = true, [FromQuery] bool? preflightOnly = null, [FromQuery] CommitId? preflightChange = null, [FromQuery] string? preflightStartedByUserId = null, [FromQuery] string? startedByUserId = null, [FromQuery] DateTimeOffset? minCreateTime = null, [FromQuery] DateTimeOffset? maxCreateTime = null, [FromQuery] DateTimeOffset? modifiedBefore = null, [FromQuery] DateTimeOffset? modifiedAfter = null, [FromQuery] string? target = null, [FromQuery] JobStepState[]? state = null, [FromQuery] JobStepOutcome[]? outcome = null, [FromQuery] PropertyFilter? filter = null, [FromQuery] int index = 0, [FromQuery] int count = 100)` — attrs: `[HttpGet] [Route("/api/v1/jobs")] [ProducesResponseType(typeof(List<GetJobResponse>), 200)]` — Find jobs matching a criteria
- L1338-1378 _public method_ `public async Task<ActionResult<List<object>>> FindJobsByStreamWithTemplatesAsync( string streamId, [FromQuery(Name = "template")] string[]? templates = null, [FromQuery(Name = "t")] string[]? templateIds = null, [FromQuery] string? preflightStartedByUserId = null, [FromQuery] DateTimeOffset? maxCreateTime = null, [FromQuery] DateTimeOffset? modifiedAfter = null, [FromQuery] PropertyFilter? filter = null, [FromQuery] int index = 0, [FromQuery] int count = 100, [FromQuery] bool consistentRead = false, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/jobs/streams/{streamId}")] [ProducesResponseType(typeof(List<GetJobResponse>), 200)]` — Find jobs for a stream with given templates, sorted by creation date
- L1380-1397 _private method_ `private async Task<List<object>> CreateAuthorizedJobResponsesAsync(IReadOnlyList<IJob> jobs, PropertyFilter? filter = null, CancellationToken cancellationToken = default)`
- L1409-1437 _public method_ `public async Task<ActionResult> CreateGroupsAsync(JobId jobId, [FromBody] List<NewGroup> requests, CancellationToken cancellationToken = default)` — attrs: `[HttpPost] [Obsolete("Modifying graph through REST API is not supported")] [Route("/api/v1/jobs/{jobId}/groups")]` — Adds an array of nodes to be executed for a job
- L1450-1470 _public method_ `public async Task<ActionResult<List<object>>> GetGroupsAsync(JobId jobId, [FromQuery] PropertyFilter? filter = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Obsolete("Query entire job instead")] [Route("/api/v1/jobs/{jobId}/groups")] [ProducesResponseType(typeof(List<GetGroupResponse>), 200)]` — Gets the nodes to be executed for a job
- L1484-1509 _public method_ `public async Task<ActionResult<object>> GetGroupAsync(JobId jobId, int groupIdx, [FromQuery] PropertyFilter? filter = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Obsolete("Query entire job instead")] [Route("/api/v1/jobs/{jobId}/groups/{groupIdx}")] [ProducesResponseType(typeof(GetGroupResponse), 200)]` — Gets the nodes in a group to be executed for a job
- L1521-1546 _public method_ `public async Task<ActionResult<List<object>>> GetNodesAsync(JobId jobId, int groupIdx, [FromQuery] PropertyFilter? filter = null)` — attrs: `[HttpGet] [Obsolete("Query entire job instead")] [Route("/api/v1/jobs/{jobId}/groups/{groupIdx}/nodes")] [ProducesResponseType(typeof(List<GetNodeResponse>), 200)]` — Gets the nodes for a particular group
- L1559-1588 _public method_ `public async Task<ActionResult<object>> GetNodeAsync(JobId jobId, int groupIdx, int nodeIdx, [FromQuery] PropertyFilter? filter = null)` — attrs: `[HttpGet] [Obsolete("Query entire job instead")] [Route("/api/v1/jobs/{jobId}/groups/{groupIdx}/nodes/{nodeIdx}")] [ProducesResponseType(typeof(GetNodeResponse), 200)]` — Gets a particular node definition
- L1601-1628 _public method_ `public async Task<ActionResult<List<object>>> GetBatchesAsync(JobId jobId, [FromQuery] PropertyFilter? filter = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Obsolete("Query entire job instead")] [Route("/api/v1/jobs/{jobId}/batches")] [ProducesResponseType(typeof(List<GetJobBatchResponse>), 200)]` — Gets the steps currently scheduled to be executed for a job
- L1639-1667 _public method_ `public async Task<ActionResult> UpdateBatchAsync(JobId jobId, JobStepBatchId batchId, [FromBody] UpdateBatchRequest request)` — attrs: `[HttpPut] [Obsolete("Query entire job instead")] [Route("/api/v1/jobs/{jobId}/batches/{batchId}")]` — Updates the state of a jobstep
- L1681-1710 _public method_ `public async Task<ActionResult<object>> GetBatchAsync(JobId jobId, JobStepBatchId batchId, [FromQuery] PropertyFilter? filter = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Obsolete("Query entire job instead")] [Route("/api/v1/jobs/{jobId}/batches/{batchId}")] [ProducesResponseType(typeof(GetJobBatchResponse), 200)]` — Gets a particular step currently scheduled to be executed for a job
- L1724-1757 _public method_ `public async Task<ActionResult<List<object>>> GetStepsAsync(JobId jobId, JobStepBatchId batchId, [FromQuery] PropertyFilter? filter = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Obsolete("Query entire job instead")] [Route("/api/v1/jobs/{jobId}/batches/{batchId}/steps")] [ProducesResponseType(typeof(List<GetJobStepResponse>), 200)]` — Gets the steps currently scheduled to be executed for a job
- L1768-1844 _public method_ `public async Task<ActionResult<UpdateStepResponse>> UpdateStepAsync(JobId jobId, JobStepBatchId batchId, JobStepId stepId, [FromBody] UpdateStepRequest request)` — attrs: `[HttpPut] [Route("/api/v1/jobs/{jobId}/batches/{batchId}/steps/{stepId}")]` — Updates the state of a jobstep
- L1859-1894 _public method_ `public async Task<ActionResult<object>> GetStepAsync(JobId jobId, JobStepBatchId batchId, JobStepId stepId, [FromQuery] PropertyFilter? filter = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Obsolete("Query entire job instead")] [Route("/api/v1/jobs/{jobId}/batches/{batchId}/steps/{stepId}")] [ProducesResponseType(typeof(GetJobStepResponse), 200)]` — Gets a particular step currently scheduled to be executed for a job
- L1907-1947 _public method_ `public async Task<ActionResult> UpdateStepNotificationsAsync(JobId jobId, JobStepBatchId batchId, JobStepId stepId, [FromBody] UpdateNotificationsRequest request, CancellationToken cancellationToken)` — attrs: `[HttpPut] [Route("/api/v1/jobs/{jobId}/batches/{batchId}/steps/{stepId}/notifications")]` — Updates notifications for a specific job.
- L1959-1997 _public method_ `public async Task<ActionResult<GetNotificationResponse>> GetStepNotificationsAsync(JobId jobId, JobStepBatchId batchId, JobStepId stepId, CancellationToken cancellationToken)` — attrs: `[HttpGet] [Route("/api/v1/jobs/{jobId}/batches/{batchId}/steps/{stepId}/notifications")]` — Gets information about a specific job.
- L2008-2048 _public method_ `public async Task<ActionResult> UpdateLabelNotificationsAsync(JobId jobId, int labelIndex, [FromBody] UpdateNotificationsRequest request, CancellationToken cancellationToken)` — attrs: `[HttpPut] [Route("/api/v1/jobs/{jobId}/labels/{labelIndex}/notifications")]` — Updates notifications for a specific label.
- L2059-2077 _public method_ `public async Task<ActionResult<GetNotificationResponse>> GetLabelNotificationsAsync(JobId jobId, int labelIndex, CancellationToken cancellationToken)` — attrs: `[HttpGet] [Route("/api/v1/jobs/{jobId}/labels/{labelIndex}/notifications")]` — Gets notification info about a specific label in a job.
- L2091-2116 _public method_ `public async Task<ActionResult> GetJobHistoryAsync(JobId jobId, [FromQuery] DateTime? minTime = null, [FromQuery] DateTime? maxTime = null, [FromQuery] int index = 0, [FromQuery] int count = 50, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/jobs/{jobId}/history")]` — Retrieve historical information about a specific job
- L2129-2244 _public method_ `public async Task<ActionResult<GetLabelDetailsResponse>> GetLabelDetailsAsync(JobId jobId, int labelIndex, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/jobs/{jobId}/labels/{labelIndex}/details")] [ProducesResponseType(typeof(GetLabelDetailsResponse), 200)]` — Get aggregated label details for hover card display. Returns steps, log events, issues, previous build status, and cross-stream merge chain in a single response.
- L2246-2319 _private* method_ `async Task<Dictionary<string, GetLabelLogEventsResponse>> GetLabelLogEventsAsync(List<GetLabelStepResponse> steps, CancellationToken cancellationToken)`
- L2321-2371 _private* method_ `async Task<List<GetLabelIssueResponse>> GetLabelIssuesAsync(IJob job, IGraph graph, int labelIndex, CancellationToken cancellationToken)`
- L2373-2421 _private* method_ `async Task<GetLabelPreviousBuildResponse?> GetLabelPreviousBuildAsync(IJob job, ILabel label, CancellationToken cancellationToken)`
- L2423-2547 _private* method_ `async Task<GetLabelCrossStreamChainResponse?> GetLabelCrossStreamChainAsync(IJob job, ILabel label, LabelState currentState, LabelOutcome currentOutcome, CancellationToken cancellationToken)`

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/LabelDetailsMessages.cs` (HordeServer.Build)


#### class `HordeServer.Jobs.GetLabelDetailsResponse`  
`public class GetLabelDetailsResponse`  
_public; L13-59_
- desc: Aggregated label details for the hover card — all data needed in a single response
- L16 _public property_ `public string? DashboardName { get; set; }` — Label display name
- L19 _public property_ `public string? DashboardCategory { get; set; }` — Label category
- L22 _public property_ `public LabelState State { get; set; }` — Current label state
- L25 _public property_ `public LabelOutcome Outcome { get; set; }` — Current label outcome
- L32 _public property_ `public List<GetLabelStepResponse> Steps { get; set; }` — Steps in this label. When outcome is Failure or Warning, only failing/warning steps are included. When outcome is Success or Running, all steps are included (for the step count). Capped at 20 steps to bound response size.
- L39 _public property_ `public Dictionary<string, GetLabelLogEventsResponse> LogEvents { get; set; }` — Log events for failing steps, keyed by logId string. Pre-fetched server-side in a single batch call. Only populated for steps with Failure outcome.
- L42 _public property_ `public int TotalStepCount { get; set; }` — Total number of steps in the label (may exceed Steps.Count due to cap)
- L45 _public property_ `public List<GetLabelIssueResponse> Issues { get; set; }` — Build health issues affecting this label
- L51 _public property_ `public GetLabelPreviousBuildResponse? PreviousBuild { get; set; }` — Previous build: the matching label from the most recent earlier job in the same stream with the same template. Null if no previous job found.
- L58 _public property_ `public GetLabelCrossStreamChainResponse? CrossStreamChain { get; set; }` — Cross-stream merge chain with label status per stream. Entries are pre-ordered by RoboMerge merge flow (oldest release at [0], Main at [N-1]). Null when IMergeGraphService has no chain for this stream.

#### class `HordeServer.Jobs.GetLabelStepResponse`  
`public class GetLabelStepResponse`  
_public; L62-91_
- desc: Step summary within a label
- L65 _public property_ `public string Id { get; set; }` — Step ID
- L68 _public property_ `public string Name { get; set; }` — Step name
- L71 _public property_ `public JobStepState State { get; set; }` — Step state
- L74 _public property_ `public JobStepOutcome Outcome { get; set; }` — Step outcome
- L77 _public property_ `public string? LogId { get; set; }` — Log ID (for linking to log viewer)
- L80 _public property_ `public DateTime? StartTime { get; set; }` — Step start time
- L83 _public property_ `public DateTime? FinishTime { get; set; }` — Step finish time
- L90 _public property_ `public string? DiagnosticMessage { get; set; }` — Step diagnostic message extracted from step metadata (ReportStepMessage). Pre-extracted server-side so the frontend doesn't need getStepRefMessageInfo(). Null if no diagnostic message is present.

#### class `HordeServer.Jobs.GetLabelLogEventsResponse`  
`public class GetLabelLogEventsResponse`  
_public; L94-101_
- desc: Log events for a single step's log
- L97 _public property_ `public int Total { get; set; }` — Total number of events matching the severity filter
- L100 _public property_ `public List<GetLogEventResponse> Events { get; set; }` — Event entries (capped at 20 per log), using the existing GetLogEventResponse DTO

#### class `HordeServer.Jobs.GetLabelIssueResponse`  
`public class GetLabelIssueResponse`  
_public; L104-129_
- desc: Build health issue summary
- L107 _public property_ `public int Id { get; set; }` — Issue ID
- L110 _public property_ `public string Summary { get; set; }` — Issue summary text
- L113 _public property_ `public IssueSeverity Severity { get; set; }` — Severity (Error, Warning, etc.)
- L116 _public property_ `public GetThinUserInfoResponse? Owner { get; set; }` — Current owner
- L119 _public property_ `public bool Acknowledged { get; set; }` — Whether the issue has been acknowledged
- L122 _public property_ `public bool ResolvedInStream { get; set; }` — Whether the issue is resolved in this stream
- L125 _public property_ `public string? ExternalIssueKey { get; set; }` — External issue key (e.g. Jira ticket like "FORT-123456"), null if not linked
- L128 _public property_ `public Uri? WorkflowThreadUrl { get; set; }` — Workflow thread URL (Slack thread), null if not created

#### class `HordeServer.Jobs.GetLabelPreviousBuildResponse`  
`public class GetLabelPreviousBuildResponse`  
_public; L132-148_
- desc: Previous build's label status
- L135 _public property_ `public string JobId { get; set; }` — Previous job ID
- L138 _public property_ `public int Change { get; set; }` — Previous job's CL number
- L141 _public property_ `public int LabelIndex { get; set; }` — The matching label's index in the previous job's graph
- L144 _public property_ `public LabelState State { get; set; }` — The matching label's state in the previous job
- L147 _public property_ `public LabelOutcome Outcome { get; set; }` — The matching label's outcome in the previous job

#### class `HordeServer.Jobs.GetLabelCrossStreamChainResponse`  
`public class GetLabelCrossStreamChainResponse`  
_public; L154-165_
- desc: Cross-stream label status ordered by merge chain. Assembled server-side using IMergeGraphService (in-memory, zero I/O for topology).
- L157 _public property_ `public string BotName { get; set; }` — Bot name from IMergeGraphService (e.g. "fortnite")
- L164 _public property_ `public List<GetLabelCrossStreamEntry> Entries { get; set; }` — Chain entries in merge-flow display order: oldest release at [0], Main at [N-1]. Only includes streams that have the matching templateId. The current stream is included inline with IsCurrent=true.

#### class `HordeServer.Jobs.GetLabelCrossStreamEntry`  
`public class GetLabelCrossStreamEntry`  
_public; L168-190_
- desc: Single entry in the cross-stream merge chain
- L171 _public property_ `public string StreamId { get; set; }` — Horde stream ID
- L174 _public property_ `public string BranchName { get; set; }` — Branch name from the merge chain (e.g. "Main", "Dev-FN-40")
- L177 _public property_ `public string? JobId { get; set; }` — Job ID of the latest job with matching template, null if none found
- L180 _public property_ `public LabelState? State { get; set; }` — Label state in the sibling stream's latest job, null if no matching label
- L183 _public property_ `public LabelOutcome? Outcome { get; set; }` — Label outcome in the sibling stream's latest job
- L186 _public property_ `public bool HasApprovalGateBefore { get; set; }` — Whether there's an approval gate between the previous chain entry and this one
- L189 _public property_ `public bool IsCurrent { get; set; }` — Whether this is the current stream (the job being hovered)

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/Schedules/ScheduleConfig.cs` (HordeServer.Build)


#### class `HordeServer.Jobs.Schedules.ScheduleConfig`  
`public class ScheduleConfig`  
_public; L15-79_
- desc: Parameters to create a new schedule
- L20 _public property_ `public bool Enabled { get; set; }` — Whether the schedule should be enabled
- L27 _public property_ `public Condition? Condition { get; set; }` — Condition for whether the schedule should be enabled. When a condition is provided the result of the expression will be logically AND with the Enabled property to decide if the schedule should be enabled.
- L32 _public property_ `public int MaxActive { get; set; }` — Maximum number of builds that can be active at once
- L37 _public property_ `public int MaxChanges { get; set; }` — Maximum number of changes the schedule can fall behind head revision. If greater than zero, builds will be triggered for every submitted changelist until the backlog is this size.
- L42 _public property_ `public bool RequireSubmittedChange { get; set; }` — Whether the build requires a change to be submitted
- L47 _public property_ `public ScheduleGateConfig? Gate { get; set; }` — Gate allowing the schedule to trigger
- L52 _public property_ `public List<CommitTag> Commits { get; set; }` — Commit tags for this schedule
- L57 _public property_ `public List<ScheduleClaimConfig>? Claims { get; set; }` — Roles to impersonate for this schedule
- L63 _public property_ `public List<ChangeContentFlags>? Filter { get; set; }` — attrs: `[Obsolete("Use Commits instead")]` — The types of changes to run for
- L68 _public property_ `public List<string>? Files { get; set; }` — Files that should cause the job to trigger
- L73 _public property_ `public Dictionary<string, string> TemplateParameters { get; set; }` — Parameters for the template
- L78 _public property_ `public List<SchedulePatternConfig> Patterns { get; set; }` — New patterns for the schedule

#### class `HordeServer.Jobs.Schedules.ScheduleClaimConfig`  
`public class ScheduleClaimConfig : IScheduleClaim`  
_public; L84-93_
- inherits: `IScheduleClaim`
- desc: Claim to grant to leases running a scheduled job
- L88 _public property_ `public string Type { get; set; }` — attrs: `[Required]` — (inheritdoc)
- L92 _public property_ `public string Value { get; set; }` — attrs: `[Required]` — (inheritdoc)

#### class `HordeServer.Jobs.Schedules.ScheduleGateConfig`  
`public class ScheduleGateConfig : IScheduleGate`  
_public; L98-111_
- inherits: `IScheduleGate`
- desc: Gate allowing a schedule to trigger.
- L104 _public property_ `public TemplateId TemplateId { get; set; }` — attrs: `[Required]` — The template containing the dependency
- L110 _public property_ `public string Target { get; set; }` — attrs: `[Required]` — Target to wait for

#### class `HordeServer.Jobs.Schedules.SchedulePatternConfig`  
`public class SchedulePatternConfig : ISchedulePattern`  
_public; L116-161_
- inherits: `ISchedulePattern`
- desc: Parameters to create a new schedule
- L121 _public property_ `public List<DayOfWeek>? DaysOfWeek { get; set; }` — Days of the week to run this schedule on. If null, the schedule will run every day.
- L126 _public property_ `public ScheduleTimeOfDay MinTime { get; set; }` — Time during the day for the first schedule to trigger. Measured in minutes from midnight.
- L131 _public property_ `public ScheduleTimeOfDay? MaxTime { get; set; }` — Time during the day for the last schedule to trigger. Measured in minutes from midnight.
- L136 _public property_ `public ScheduleInterval? Interval { get; set; }` — Interval between each schedule triggering
- L138 _private* property_ `IReadOnlyList<DayOfWeek>? ISchedulePattern.DaysOfWeek => ...`
- L143-145 _public ctor_ `public SchedulePatternConfig()` — Constructor
- L154-160 _public ctor_ `public SchedulePatternConfig(List<DayOfWeek>? daysOfWeek, int minTime, int? maxTime, int? interval)` — Constructor

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/Schedules/ScheduleService.cs` (HordeServer.Build)


#### record `HordeServer.Jobs.Schedules.ScheduleId`  
`public record class ScheduleId(StreamId StreamId, TemplateId TemplateId)`  
_public; L33-38_
- desc: Identifier for writing log messages to a particular template
- L36 _public method_ `public override string ToString()` — (inheritdoc)

#### class `HordeServer.Jobs.Schedules.ScheduleService`  
`public sealed class ScheduleService : IHostedService, IAsyncDisposable`  
_public; L43-674_
- inherits: `IHostedService, IAsyncDisposable`
- desc: Manipulates schedule instances
- L68 _private* field_ `readonly IAuditLog<ScheduleId> _auditLog`
- L69 _private* field_ `readonly IGraphCollection _graphs`
- L70 _private* field_ `readonly IJobCollection _jobCollection`
- L71 _private* field_ `readonly IDowntimeService _downtimeService`
- L72 _private* field_ `readonly JobService _jobService`
- L73 _private* field_ `readonly IStreamCollection _streamCollection`
- L74 _private* field_ `readonly ITemplateCollectionInternal _templateCollection`
- L75 _private* field_ `readonly IClock _clock`
- L76 _private* field_ `readonly Tracer _tracer`
- L77 _private* field_ `readonly ILogger _logger`
- L78 _private* field_ `readonly IRedisService _redis`
- L79 _private* field_ `static readonly RedisKey s_baseLockKey = "scheduler/locks"`
- L80 _private* field_ `static readonly RedisKey s_tickLockKey = s_baseLockKey.Append("/tick")`
- L81 _private* field_ `static readonly RedisSortedSetKey<QueueItem> s_queueKey = "scheduler/queue"`
- L82 _private* field_ `readonly IOptionsMonitor<BuildConfig> _buildConfig`
- L83 _private* field_ `readonly ITicker _ticker`
- L88-111 _public ctor_ `public ScheduleService(IAuditLog<ScheduleId> auditLog, IRedisService redis, IGraphCollection graphs, IJobCollection jobCollection, JobService jobService, IDowntimeService downtimeService, IStreamCollection streamCollection, ITemplateCollectionInternal templateCollection, IMongoService mongoService, IClock clock, IOptionsMonitor<BuildConfig> buildConfig, Tracer tracer, ILogger<ScheduleService> logger)` — Constructor
- L114-117 _public method_ `public async Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L120-123 _public method_ `public async Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L126-129 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L131-192 _private* method_ `async ValueTask TickAsync(CancellationToken cancellationToken)`
- L194-209 _private* method_ `async Task<QueueItem?> PopQueueItemAsync()`
- L211-216 _internal method_ `internal async Task ResetAsync()`
- L218-222 _internal method_ `internal async Task TickForTestingAsync()`
- L227-264 _public method_ `public async Task UpdateQueueAsync(DateTime utcNow, CancellationToken cancellationToken)` — Get the current set of streams and ensure there's an entry for each item
- L271 _public method_ `public IAuditLogChannel GetAuditLog(StreamId streamId, TemplateId templateId)` — Gets the audit log for a particular template
- L282-350 _internal method_ `internal async Task<bool> TriggerAsync(StreamId streamId, TemplateId templateId, DateTime utcNow, CancellationToken cancellationToken)` — Trigger a schedule to run
- L365-561 _private method_ `private async Task TriggerAsync(IStream stream, TemplateId templateId, ITemplateRef templateRef, ISchedule schedule, int numActiveJobs, DateTime utcNow, ILogger scheduleLogger, TelemetrySpan linkedSpan, CancellationToken cancellationToken)` — Trigger a schedule to run
- L571-595 _private method_ `private async ValueTask<bool> ShouldBuildChangeAsync(ICommit commit, IReadOnlyList<CommitTag>? filterTags, FileFilter? fileFilter, CancellationToken cancellationToken)` — Tests whether a schedule should build a particular change, based on its requested change filters
- L600-673 _private method_ `private async Task<CommitIdWithOrder?> GetNextChangeForGateAsync(StreamId streamId, TemplateId templateRefId, IScheduleGate gate, CommitIdWithOrder? minCommitId, CommitIdWithOrder? maxCommitId, ILogger scheduleLogger, CancellationToken cancellationToken)` — Gets the next change to build for a schedule on a gate

#### class `HordeServer.Jobs.Schedules.ScheduleService.QueueItem`  
`class QueueItem`  
_private*; L46-66_
- attrs: `[RedisConverter(typeof(RedisCbConverter<QueueItem>))]`
- L49 _public property_ `public StreamId StreamId { get; set; }` — attrs: `[CbField("sid")]`
- L52 _public property_ `public TemplateId TemplateId { get; set; }` — attrs: `[CbField("tid")]`
- L54-56 _public ctor_ `public QueueItem()`
- L58-62 _public ctor_ `public QueueItem(StreamId streamId, TemplateId templateId)`
- L64 _public method_ `public static DateTime GetTimeFromScore(double score)`
- L65 _public method_ `public static double GetScoreFromTime(DateTime time)`

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/Templates/ITemplateCollectionInternal.cs` (HordeServer.Build)


#### interface `HordeServer.Jobs.Templates.ITemplateCollectionInternal`  
`public interface ITemplateCollectionInternal : ITemplateCollection`  
_public; L11-19_
- inherits: `ITemplateCollection`
- desc: Internal implementation of ITemplateCollection which allows registering new template instances.
- L18 _public* method_ `Task<ITemplate> GetOrAddAsync(TemplateConfig templateConfig)` — Gets a template instance from its configuration

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/Templates/TemplateCollection.cs` (HordeServer.Build)


#### class `HordeServer.Jobs.Templates.TemplateCollection`  
`public sealed class TemplateCollection : ITemplateCollectionInternal, IDisposable`  
_public; L17-455_
- inherits: `ITemplateCollectionInternal, IDisposable`
- desc: Collection of template documents
- L389 _private* field_ `readonly IMongoCollection<TemplateDocument> _templates` — Template documents
- L394 _private* field_ `readonly MemoryCache _templateCache` — Cache of template documents
- L400-406 _public ctor_ `public TemplateCollection(IMongoService mongoService)` — Constructor
- L409-412 _public method_ `public void Dispose()` — (inheritdoc)
- L415-434 _public method_ `public async Task<ITemplate?> GetAsync(ContentHash templateId)` — (inheritdoc)
- L437-454 _public method_ `public async Task<ITemplate> GetOrAddAsync(TemplateConfig config)` — (inheritdoc)

#### class `HordeServer.Jobs.Templates.TemplateCollection.TemplateDocument`  
`class TemplateDocument : ITemplate`  
_private*; L22-92_
- inherits: `ITemplate`
- desc: Document describing a job template. These objects are considered immutable once created and uniquely referenced by hash, in order to de-duplicate across all job runs.
- L25 _public property_ `public ContentHash Id { get; set; }` — attrs: `[BsonRequired, BsonId]`
- L28 _public property_ `public string Name { get; set; }` — attrs: `[BsonRequired]`
- L31 _public property_ `public string? Description { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L33 _public property_ `public Priority? Priority { get; set; }`
- L34 _public property_ `public bool AllowPreflights { get; set; }`
- L35 _public property_ `public bool UpdateIssues { get; set; }`
- L36 _public property_ `public bool PromoteIssuesByDefault { get; set; }`
- L37 _public property_ `public string? InitialAgentType { get; set; }`
- L40 _public property_ `public string? SubmitNewChange { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L43 _public property_ `public string? SubmitDescription { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L45 _public property_ `public List<string> Arguments { get; set; }`
- L46 _public property_ `public List<ParameterDocument> Parameters { get; set; }`
- L48 _private* property_ `ContentHash ITemplate.Hash => ...`
- L49 _private* property_ `IReadOnlyList<string> ITemplate.Arguments => ...`
- L50 _private* property_ `IReadOnlyList<ITemplateParameter> ITemplate.Parameters => ...`
- L53-56 _private ctor_ `private TemplateDocument()` — attrs: `[BsonConstructor]`
- L58-74 _public ctor_ `public TemplateDocument(TemplateConfig config)`
- L76-91 _private* method_ `static ParameterDocument CreateParameterDocument(TemplateParameterConfig config)`

#### class `HordeServer.Jobs.Templates.TemplateCollection.ParameterDocument`  
`abstract class ParameterDocument : ITemplateParameter`  
_private*; L96-100_
- attrs: `[BsonDiscriminator(RootClass = true)] [BsonKnownTypes(typeof(BoolParameterDocument), typeof(TextParameterDocument), typeof(ListParameterDocument))]`
- inherits: `ITemplateParameter`
- L98 _public method_ `public abstract void GetArguments(IReadOnlyDictionary<ParameterId, string> parameters, bool scheduledBuild, List<string> arguments)`
- L99 _public method_ `public abstract void GetDefaultParameters(Dictionary<ParameterId, string> parameters, bool scheduledBuild)`

#### class `HordeServer.Jobs.Templates.TemplateCollection.BoolParameterDocument`  
`sealed class BoolParameterDocument : ParameterDocument, ITemplateBoolParameter`  
_private*; L103-204_
- attrs: `[BsonDiscriminator("BoolParameter")]`
- inherits: `ParameterDocument, ITemplateBoolParameter`
- L105 _public property_ `public ParameterId Id { get; set; }`
- L106 _public property_ `public string Label { get; set; }`
- L109 _public property_ `public string? ArgumentIfEnabled { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L112 _public property_ `public List<string>? ArgumentsIfEnabled { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L115 _public property_ `public string? ArgumentIfDisabled { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L118 _public property_ `public List<string>? ArgumentsIfDisabled { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L121 _public property_ `public bool Default { get; set; }` — attrs: `[BsonIgnoreIfDefault, BsonDefaultValue(false)]`
- L124 _public property_ `public bool? ScheduleOverride { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L126 _public property_ `public string? ToolTip { get; set; }`
- L128 _private* property_ `IReadOnlyList<string>? ITemplateBoolParameter.ArgumentsIfEnabled => ...`
- L129 _private* property_ `IReadOnlyList<string>? ITemplateBoolParameter.ArgumentsIfDisabled => ...`
- L131-134 _public ctor_ `public BoolParameterDocument()`
- L136-147 _public ctor_ `public BoolParameterDocument(TemplateBoolParameterConfig config)`
- L149-163 _public method_ `public static bool? GetValue(ParameterId parameterId, IReadOnlyDictionary<ParameterId, string> parameters)`
- L166-170 _public method_ `public override void GetArguments(IReadOnlyDictionary<ParameterId, string> parameters, bool scheduledBuild, List<string> arguments)` — (inheritdoc)
- L173-177 _public method_ `public override void GetDefaultParameters(Dictionary<ParameterId, string> parameters, bool scheduledBuild)` — (inheritdoc)
- L179-203 _private* method_ `void GetCommandLineArgumentsForItem(bool value, List<string> arguments)`

#### class `HordeServer.Jobs.Templates.TemplateCollection.TextParameterDocument`  
`sealed class TextParameterDocument : ParameterDocument, ITemplateTextParameter`  
_private*; L207-262_
- attrs: `[BsonDiscriminator("TextParameter")]`
- inherits: `ParameterDocument, ITemplateTextParameter`
- L209 _public property_ `public ParameterId Id { get; set; }`
- L210 _public property_ `public string Label { get; set; }`
- L211 _public property_ `public string Argument { get; set; }`
- L212 _public property_ `public string Default { get; set; }`
- L213 _public property_ `public string? ScheduleOverride { get; set; }`
- L214 _public property_ `public string? Hint { get; set; }`
- L217 _public property_ `public string? Validation { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L220 _public property_ `public string? ValidationError { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L222 _public property_ `public string? ToolTip { get; set; }`
- L224-229 _public ctor_ `public TextParameterDocument()`
- L231-242 _public ctor_ `public TextParameterDocument(TemplateTextParameterConfig config)`
- L245-255 _public method_ `public override void GetArguments(IReadOnlyDictionary<ParameterId, string> parameters, bool scheduledBuild, List<string> arguments)` — (inheritdoc)
- L258-261 _public method_ `public override void GetDefaultParameters(Dictionary<ParameterId, string> parameters, bool scheduledBuild)` — (inheritdoc)

#### class `HordeServer.Jobs.Templates.TemplateCollection.ListParameterDocument`  
`sealed class ListParameterDocument : ParameterDocument, ITemplateListParameter`  
_private*; L265-336_
- attrs: `[BsonDiscriminator("ListParameter")]`
- inherits: `ParameterDocument, ITemplateListParameter`
- L267 _public property_ `public string Label { get; set; }`
- L268 _public property_ `public TemplateListParameterStyle Style { get; set; }`
- L269 _public property_ `public List<ListParameterItemDocument> Items { get; set; }`
- L270 _public property_ `public string? ToolTip { get; set; }`
- L272 _private* property_ `IReadOnlyList<ITemplateListParameterItem> ITemplateListParameter.Items => ...`
- L277-281 _public ctor_ `public ListParameterDocument()` — Private constructor for serialization
- L283-289 _public ctor_ `public ListParameterDocument(TemplateListParameterConfig config)`
- L292-299 _public method_ `public override void GetArguments(IReadOnlyDictionary<ParameterId, string> parameters, bool scheduledBuild, List<string> arguments)` — (inheritdoc)
- L302-309 _public method_ `public override void GetDefaultParameters(Dictionary<ParameterId, string> parameters, bool scheduledBuild)` — (inheritdoc)
- L311-335 _private* method_ `static void GetCommandLineArgumentsForItem(ListParameterItemDocument item, bool value, List<string> arguments)`

#### class `HordeServer.Jobs.Templates.TemplateCollection.ListParameterItemDocument`  
`class ListParameterItemDocument : ITemplateListParameterItem`  
_private*; L338-384_
- inherits: `ITemplateListParameterItem`
- L340 _public property_ `public ParameterId Id { get; set; }`
- L343 _public property_ `public string? Group { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L345 _public property_ `public string Text { get; set; }`
- L348 _public property_ `public string? ArgumentIfEnabled { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L351 _public property_ `public List<string>? ArgumentsIfEnabled { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L354 _public property_ `public string? ArgumentIfDisabled { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L357 _public property_ `public List<string>? ArgumentsIfDisabled { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L360 _public property_ `public bool Default { get; set; }` — attrs: `[BsonIgnoreIfDefault, BsonDefaultValue(false)]`
- L362 _public property_ `public bool? ScheduleOverride { get; set; }`
- L364 _private* property_ `IReadOnlyList<string>? ITemplateListParameterItem.ArgumentsIfEnabled => ...`
- L365 _private* property_ `IReadOnlyList<string>? ITemplateListParameterItem.ArgumentsIfDisabled => ...`
- L367-370 _public ctor_ `public ListParameterItemDocument()`
- L372-383 _public ctor_ `public ListParameterItemDocument(TemplateListParameterItemConfig config)`

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/Templates/TemplateConfig.cs` (HordeServer.Build)


#### class `HordeServer.Jobs.Templates.TemplateConfig`  
`public class TemplateConfig`  
_public; L20-97_
- desc: Parameters to create a new template
- L26 _public property_ `public string Name { get; set; }` — attrs: `[Required]` — Name for the new template
- L31 _public property_ `public string? Description { get; set; }` — Description for the template
- L36 _public property_ `public Priority? Priority { get; set; }` — Default priority for this job
- L41 _public property_ `public bool AllowPreflights { get; set; }` — Whether to allow preflights of this template
- L46 _public property_ `public bool UpdateIssues { get; set; }` — Whether issues should be updated for all jobs using this template
- L51 _public property_ `public bool PromoteIssuesByDefault { get; set; }` — Whether issues should be promoted by default for this template, promoted issues will generate user notifications
- L56 _public property_ `public string? InitialAgentType { get; set; }` — Initial agent type to parse the buildgraph script on
- L61 _public property_ `public string? SubmitNewChange { get; set; }` — Path to a file within the stream to submit to generate a new changelist for jobs
- L66 _public property_ `public string? SubmitDescription { get; set; }` — Description for new changelists
- L72 _public property_ `public List<ChangeQueryConfig>? DefaultChange { get; set; }` — attrs: `[ConfigMergeStrategy(ConfigMergeStrategy.Append)]` — Default change to build at. Each object has a condition parameter which can evaluated by the server to determine which change to use.
- L78 _public property_ `public List<string> Arguments { get; set; }` — attrs: `[ConfigMergeStrategy(ConfigMergeStrategy.Append)]` — Fixed arguments for the new job
- L84 _public property_ `public List<TemplateParameterConfig> Parameters { get; set; }` — attrs: `[ConfigMergeStrategy(ConfigMergeStrategy.Append)]` — Parameters for this template
- L90 _public property_ `public JobOptions JobOptions { get; set; }` — attrs: `[ConfigMergeStrategy(ConfigMergeStrategy.Recursive)]` — Default settings for jobs
- L96 _internal property_ `internal ContentHash? CachedHash { get; set; }` — attrs: `[JsonIgnore]` — The cached hash of this template.

#### class `HordeServer.Jobs.Templates.ChangeQueryConfig`  
`public class ChangeQueryConfig : IChangeQuery`  
_public; L102-122_
- inherits: `IChangeQuery`
- desc: Query selecting the base changelist to use
- L105 _public property_ `public string? Name { get; set; }` — (inheritdoc)
- L108 _public property_ `public Condition? Condition { get; set; }` — (inheritdoc)
- L111 _public property_ `public TemplateId? TemplateId { get; set; }` — (inheritdoc)
- L114 _public property_ `public string? Target { get; set; }` — (inheritdoc)
- L117 _public property_ `public List<JobStepOutcome>? Outcomes { get; set; }` — (inheritdoc)
- L118 _private* property_ `IReadOnlyList<JobStepOutcome>? IChangeQuery.Outcomes => ...`
- L121 _public property_ `public CommitTag? CommitTag { get; set; }` — (inheritdoc)

#### class `HordeServer.Jobs.Templates.TemplateParameterConfig`  
`public abstract class TemplateParameterConfig`  
_public; L128-185_
- attrs: `[JsonKnownTypes(typeof(TemplateTextParameterConfig), typeof(TemplateListParameterConfig), typeof(TemplateBoolParameterConfig))]`
- desc: Base class for template parameters
- L133 _public method_ `public abstract void PostLoad(HashSet<ParameterId> parameterIds)` — Callback after a parameter has been read.
- L142-156 _protected method_ `protected static ParameterId AddParameterId(ParameterId explicitParameterId, string name, HashSet<ParameterId> parameterIds)` — Adds the given parameter id to the set of known ids, or create a new one
- L163-184 _protected method_ `protected static ParameterId CreateUniqueParameterId(string name, HashSet<ParameterId> parameterIds)` — Creates a unique parameter id based on the given name

#### class `HordeServer.Jobs.Templates.TemplateBoolParameterConfig`  
`public class TemplateBoolParameterConfig : TemplateParameterConfig`  
_public; L191-285_
- attrs: `[JsonDiscriminator("Bool")]`
- inherits: `TemplateParameterConfig`
- desc: Allows the user to toggle an option on or off
- L196 _public property_ `public ParameterId Id { get; set; }` — Identifier for this parameter
- L201 _public property_ `public string Label { get; set; }` — Name of the parameter associated with this parameter.
- L206 _public property_ `public string? ArgumentIfEnabled { get; set; }` — Argument to add if this parameter is enabled
- L211 _public property_ `public List<string>? ArgumentsIfEnabled { get; set; }` — Argument to add if this parameter is enabled
- L216 _public property_ `public string? ArgumentIfDisabled { get; set; }` — Argument to add if this parameter is enabled
- L221 _public property_ `public List<string>? ArgumentsIfDisabled { get; set; }` — Arguments to add if this parameter is disabled
- L226 _public property_ `public bool Default { get; set; }` — Whether this argument is enabled by default
- L231 _public property_ `public bool? ScheduleOverride { get; set; }` — Override for this parameter in scheduled builds
- L236 _public property_ `public string? ToolTip { get; set; }` — Tool tip text to display
- L241-244 _public ctor_ `public TemplateBoolParameterConfig()` — Private constructor for serialization
- L258-269 _public ctor_ `public TemplateBoolParameterConfig(ParameterId id, string label, string? argumentIfEnabled, List<string>? argumentsIfEnabled, string? argumentIfDisabled, List<string>? argumentsIfDisabled, bool defaultValue, bool? scheduleOverride, string? toolTip)` — Constructor
- L272-284 _public method_ `public override void PostLoad(HashSet<ParameterId> parameterIds)` — (inheritdoc)

#### class `HordeServer.Jobs.Templates.TemplateTextParameterConfig`  
`public class TemplateTextParameterConfig : TemplateParameterConfig`  
_public; L291-378_
- attrs: `[JsonDiscriminator("Text")]`
- inherits: `TemplateParameterConfig`
- desc: Free-form text entry parameter
- L296 _public property_ `public ParameterId Id { get; set; }` — Identifier for this parameter
- L301 _public property_ `public string Label { get; set; }` — Name of the parameter associated with this parameter.
- L306 _public property_ `public string Argument { get; set; }` — Argument to pass to the executor
- L311 _public property_ `public string Default { get; set; }` — Default value for this argument
- L316 _public property_ `public string? ScheduleOverride { get; set; }` — Override for the default value for this parameter when running a scheduled build
- L321 _public property_ `public string? Hint { get; set; }` — Hint text for this parameter
- L326 _public property_ `public string? Validation { get; set; }` — Regex used to validate this parameter
- L331 _public property_ `public string? ValidationError { get; set; }` — Message displayed if validation fails, informing user of valid values.
- L336 _public property_ `public string? ToolTip { get; set; }` — Tool-tip text to display
- L341-346 _public ctor_ `public TemplateTextParameterConfig()` — Private constructor for serialization
- L360-371 _public ctor_ `public TemplateTextParameterConfig(ParameterId id, string label, string argument, string defaultValue, string? scheduleOverride, string? hint, string? validation, string? validationError, string? toolTip)` — Constructor
- L374-377 _public method_ `public override void PostLoad(HashSet<ParameterId> parameterIds)` — (inheritdoc)

#### class `HordeServer.Jobs.Templates.TemplateListParameterConfig`  
`public class TemplateListParameterConfig : TemplateParameterConfig`  
_public; L384-447_
- attrs: `[JsonDiscriminator("List")]`
- inherits: `TemplateParameterConfig`
- desc: Allows the user to select a value from a constrained list of choices
- L389 _public property_ `public string Label { get; set; }` — Label to display next to this parameter. Defaults to the parameter name.
- L394 _public property_ `public TemplateListParameterStyle Style { get; set; }` — The type of list parameter
- L399 _public property_ `public List<TemplateListParameterItemConfig> Items { get; set; }` — List of values to display in the list
- L404 _public property_ `public string? ToolTip { get; set; }` — Tool tip text to display
- L409-413 _public ctor_ `public TemplateListParameterConfig()` — Private constructor
- L422-428 _public ctor_ `public TemplateListParameterConfig(string label, TemplateListParameterStyle style, List<TemplateListParameterItemConfig> items, string? toolTip)` — List of possible values
- L431-446 _public method_ `public override void PostLoad(HashSet<ParameterId> parameterIds)` — (inheritdoc)

#### class `HordeServer.Jobs.Templates.TemplateListParameterItemConfig`  
`public class TemplateListParameterItemConfig`  
_public; L452-531_
- desc: Possible option for a list parameter
- L457 _public property_ `public ParameterId Id { get; set; }` — Identifier for this parameter
- L462 _public property_ `public string? Group { get; set; }` — Optional group heading to display this entry under, if the picker style supports it.
- L467 _public property_ `public string Text { get; set; }` — Name of the parameter associated with this list.
- L472 _public property_ `public string? ArgumentIfEnabled { get; set; }` — Argument to pass with this parameter.
- L477 _public property_ `public List<string>? ArgumentsIfEnabled { get; set; }` — Arguments to pass with this parameter.
- L482 _public property_ `public string? ArgumentIfDisabled { get; set; }` — Argument to pass with this parameter.
- L487 _public property_ `public List<string>? ArgumentsIfDisabled { get; set; }` — Arguments to pass if this parameter is disabled.
- L492 _public property_ `public bool Default { get; set; }` — Whether this item is selected by default
- L497 _public property_ `public bool? ScheduleOverride { get; set; }` — Overridden value for this property in schedule builds
- L502-505 _public ctor_ `public TemplateListParameterItemConfig()` — Private constructor for serialization
- L519-530 _public ctor_ `public TemplateListParameterItemConfig(ParameterId id, string? group, string text, string? argumentIfEnabled, List<string>? argumentsIfEnabled, string? argumentIfDisabled, List<string>? argumentsIfDisabled, bool defaultValue, bool? scheduleOverride)` — Constructor

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/TestData/ITestData.cs` (HordeServer.Build)


#### interface `HordeServer.Jobs.TestData.ITestMeta`  
`public interface ITestMeta`  
_public; L17-53_
- desc: Defines a testing environment based on platforms, configurations, targets, etc.
- L22 _public* property_ `TestMetaId Id { get; }` — The test meta id
- L27 _public* property_ `IReadOnlyList<string> Platforms { get; }` — The name of the test platform
- L32 _public* property_ `IReadOnlyList<string> Configurations { get; }` — The configuration the test was run on
- L37 _public* property_ `IReadOnlyList<string> BuildTargets { get; }` — The build target, editor, server, client, etc
- L42 _public* property_ `string ProjectName { get; }` — The uproject name associated with this test, note: may not be directly related to Horde project
- L47 _public* property_ `string RHI { get; }` — The rendering hardware interface used for the test
- L52 _public* property_ `string Variation { get; }` — The variation of the meta data, for example address sanitizing

#### interface `HordeServer.Jobs.TestData.ITest`  
`public interface ITest`  
_public; L58-84_
- desc: A test that runs in a stream
- L63 _public* property_ `TestId Id { get; }` — The test id
- L68 _public* property_ `string Name { get; }` — The fully qualified name of the test
- L73 _public* property_ `string? DisplayName { get; }` — The display name of the test
- L78 _public* property_ `string? SuiteName { get; }` — The name of the associated suite if any
- L83 _public* property_ `IReadOnlyList<TestMetaId> Metadata { get; }` — The meta data for the test

#### interface `HordeServer.Jobs.TestData.ITestSuite`  
`public interface ITestSuite`  
_public; L89-110_
- desc: A test suite that runs in a stream
- L94 _public* property_ `TestSuiteId Id { get; }` — The test suite id
- L99 _public* property_ `string Name { get; }` — The name of the test suite
- L104 _public* property_ `IReadOnlyList<TestId> Tests { get; }` — The tests that compose the suite
- L109 _public* property_ `IReadOnlyList<TestMetaId> Metadata { get; }` — The meta data for the test suite

#### interface `HordeServer.Jobs.TestData.ISuiteTestData`  
`public interface ISuiteTestData`  
_public; L115-146_
- desc: Suite test data
- L120 _public* property_ `TestId TestId { get; }` — The test id
- L125 _public* property_ `TestOutcome Outcome { get; }` — The outcome of the suite test
- L130 _public* property_ `TimeSpan Duration { get; }` — How long the suite test ran
- L135 _public* property_ `string UID { get; }` — Test UID for looking up in test details
- L140 _public* property_ `int? WarningCount { get; }` — The number of warnings
- L145 _public* property_ `int? ErrorCount { get; }` — The number of errors

#### interface `HordeServer.Jobs.TestData.ITestDataRef`  
`public interface ITestDataRef`  
_public; L151-222_
- desc: Data ref with minimal data required for aggregate views
- L156 _public* property_ `TestRefId Id { get; }` — The test ref id
- L161 _public* property_ `StreamId StreamId { get; }` — The associated stream
- L166 _public* property_ `JobId? JobId { get; }` — The associated job
- L171 _public* property_ `JobStepId? StepId { get; }` — The associated job step
- L176 _public* property_ `TimeSpan Duration { get; }` — How long the test ran
- L181 _public* property_ `CommitIdWithOrder BuildCommitId { get; }` — The build changelist upon which the test ran, may not correspond to the job changelist
- L186 _public* property_ `TestMetaId Metadata { get; }` — The environment the test ran in
- L191 _public* property_ `TestId? TestId { get; }` — The ITest in stream
- L196 _public* property_ `TestOutcome? Outcome { get; }` — The outcome of the test
- L201 _public* property_ `TestSuiteId? SuiteId { get; }` — The ITestSuite in stream
- L206 _public* property_ `int? SuiteSkipCount { get; }` — Suite tests skipped
- L211 _public* property_ `int? SuiteWarningCount { get; }` — Suite test warnings
- L216 _public* property_ `int? SuiteErrorCount { get; }` — Suite test errors
- L221 _public* property_ `int? SuiteSuccessCount { get; }` — Suite test successes

#### interface `HordeServer.Jobs.TestData.ITestDataDetails`  
`public interface ITestDataDetails`  
_public; L227-243_
- desc: Test data details
- L232 _public* property_ `TestRefId Id { get; }` — The corresponding test ref
- L237 _public* property_ `IReadOnlyList<ObjectId> TestDataIds { get; }` — The full details test data for this ref
- L242 _public* property_ `IReadOnlyList<ISuiteTestData>? SuiteTests { get; }` — Suite test data

#### interface `HordeServer.Jobs.TestData.ITestStream`  
`public interface ITestStream`  
_public; L248-264_
- desc: The tests and suites running in a given stream
- L253 _public* property_ `StreamId StreamId { get; }` — The stream id
- L258 _public* property_ `IReadOnlyList<TestId> Tests { get; }` — Test ids of tests running in the stream
- L263 _public* property_ `IReadOnlyList<TestSuiteId> TestSuites { get; }` — Test suite ids

#### interface `HordeServer.Jobs.TestData.ITestNameRef`  
`public interface ITestNameRef`  
_public; L271-307_
- desc: A test name reference
- L276 _public* property_ `TestId Id { get; }` — The test id
- L281 _public* property_ `string Key { get; }` — The test data key that identify the test uniquely
- L286 _public* property_ `string Name { get; }` — The display name of the test
- L291 _public* property_ `string? Team { get; }` — The team associated with the test
- L296 _public* property_ `string? Intent { get; }` — The test intent
- L301 _public* property_ `string? Harness { get; }` — The harness used by the test
- L306 _public* property_ `string? Profile { get; }` — The test profile (unit test, functional, performance, etc)

#### interface `HordeServer.Jobs.TestData.ITestPhaseRef`  
`public interface ITestPhaseRef`  
_public; L312-333_
- desc: A test phase reference
- L317 _public* property_ `TestPhaseId Id { get; }` — The test phase id
- L322 _public* property_ `TestId TestNameRef { get; }` — The test reference associated with the phase
- L327 _public* property_ `string Key { get; }` — The test phase key that identify the phase uniquely
- L332 _public* property_ `string Name { get; }` — The test phase (display) name

#### interface `HordeServer.Jobs.TestData.ITestMetaEntry`  
`public interface ITestMetaEntry`  
_public; L338-349_
- desc: A metadata entry key value pair
- L343 _public* property_ `string Key { get; }` — The meta key
- L348 _public* property_ `string Value { get; }` — The meta value

#### interface `HordeServer.Jobs.TestData.ITestMetaRef`  
`public interface ITestMetaRef`  
_public; L354-365_
- desc: A metadata key/value pairs reference
- L359 _public* property_ `TestMetaId Id { get; }` — The metadata id
- L364 _public* property_ `IReadOnlyList<ITestMetaEntry> Entries { get; }` — The key/value pairs that this metadata references

#### interface `HordeServer.Jobs.TestData.ITestParamEntry`  
`public interface ITestParamEntry`  
_public; L370-381_
- desc: A param entry key value pair
- L375 _public* property_ `string Key { get; }` — The param key
- L380 _public* property_ `object Value { get; }` — The param value

#### interface `HordeServer.Jobs.TestData.ITestRecipeRef`  
`public interface ITestRecipeRef`  
_public; L386-437_
- desc: A test recipe reference
- L391 _public* property_ `TestRecipeId Id { get; }` — The test recipe id
- L396 _public* property_ `TestId NameRef { get; }` — The test name id associated with this recipe
- L401 _public* property_ `StreamId StreamId { get; }` — The stream id associated with this recipe
- L406 _public* property_ `TemplateId JobTemplateId { get; }` — The job template associated with this recipe
- L411 _public* property_ `string JobStep { get; }` — The job step node name associated with this recipe
- L416 _public* property_ `WorkflowId? WorkflowId { get; }` — The workflow associated with this recipe
- L421 _public* property_ `string NodeClass { get; }` — The test node class
- L426 _public* property_ `string Version { get; }` — The test version
- L431 _public* property_ `float TimeoutMinutes { get; }` — The test timeout in minute
- L436 _public* property_ `IReadOnlyList<ITestParamEntry>? Params { get; }` — The test params

#### interface `HordeServer.Jobs.TestData.ITestHealthReport`  
`public interface ITestHealthReport`  
_public; L442-508_
- desc: A test health report
- L447 _public* property_ `ObjectId Id { get; }` — The report id
- L452 _public* property_ `TestId TestId { get; }` — The test id associated with this report
- L457 _public* property_ `string TestName { get; }` — The test name associated with this report
- L462 _public* property_ `StreamId StreamId { get; }` — The stream id associated with this report
- L467 _public* property_ `DateTime LastUpdateDateUtc { get; }` — The last update date associated with this report
- L472 _public* property_ `bool IsHealthy { get; }` — Whether or not the test is healthy
- L477 _public* property_ `string State { get; }` — The state associated with this test health
- L482 _public* property_ `string? PreviousState { get; }` — The previous state associated with this test health
- L487 _public* property_ `int SuccessRate { get; }` — The success rate of the test health
- L492 _public* property_ `int FailureRate { get; }` — The failure rate of the test health
- L497 _public* property_ `int CatastrophicFailureRate { get; }` — The catastrophic rate of the failure
- L502 _public* property_ `int RedundantErrorRate { get; }` — The rate of the redundant errors
- L507 _public* property_ `DateTime? NotificationLastDateUtc { get; }` — The date of the last notification sent for this report

#### interface `HordeServer.Jobs.TestData.ITestNotificationSettings`  
`public interface ITestNotificationSettings`  
_public; L513-524_
- desc: A test notification settings
- L518 _public* property_ `StreamId Stream { get; }` — The Stream associated with this entry
- L523 _public* property_ `WorkflowId Workflow { get; }` — The Workflow associated with this entry

#### interface `HordeServer.Jobs.TestData.ITestAudit`  
`public interface ITestAudit`  
_public; L529-610_
- desc: A test audit entry
- L534 _public* property_ `TestAuditId Id { get; }` — The test audit id
- L539 _public* property_ `TestId TestId { get; }` — The test name id associated with this audit
- L544 _public* property_ `DateTime UserInputDate { get; }` — The date at which this audit was filed
- L549 _public* property_ `bool Archived { get; }` — Whether or not this entry is archived
- L554 _public* property_ `UserId UserId { get; }` — The user id that updated the audit
- L559 _public* property_ `bool EnableSchedule { get; }` — Whether or not the associated test should be run on the schedule
- L564 _public* property_ `DateTime? LastAuditDate { get; }` — The date at which the audit was last officially taken place
- L569 _public* property_ `bool? IsUnderAudit { get; }` — Whether or not the associated test is under audit
- L574 _public* property_ `UserId? Owner { get; }` — The owner user id of the associated test
- L579 _public* property_ `IReadOnlyList<UserId>? Customers { get; }` — The customer user ids of the associated test
- L584 _public* property_ `IReadOnlyList<ITestNotificationSettings>? Notifications { get; }` — The workflow notification settings associated with this test
- L589 _public* property_ `string? Team { get; }` — The team associated with this test
- L594 _public* property_ `string? Harness { get; }` — The harness associated with this test
- L599 _public* property_ `string? Intent { get; }` — The intent associated with this test
- L604 _public* property_ `string? Profile { get; }` — The profile associated with this test
- L609 _public* property_ `string? Notes { get; }` — Notes associated with this test

#### interface `HordeServer.Jobs.TestData.ITestTagRef`  
`public interface ITestTagRef`  
_public; L615-626_
- desc: A test tag reference
- L620 _public* property_ `TestTagId Id { get; }` — The tag id
- L625 _public* property_ `string Name { get; }` — The tag name

#### interface `HordeServer.Jobs.TestData.ITestSession`  
`public interface ITestSession`  
_public; L631-726_
- desc: Test session
- L636 _public* property_ `TestSessionId Id { get; }` — The test session id
- L641 _public* property_ `TestMetaId Metadata { get; }` — The metadata associated with the test session
- L646 _public* property_ `TestRecipeId? Recipe { get; }` — The recipe associated with this test session
- L651 _public* property_ `IReadOnlyList<TestTagId>? Tags { get; }` — The tags associated with the test session
- L656 _public* property_ `ObjectId TestDataId { get; }` — The test data id for this test session
- L661 _public* property_ `CommitIdWithOrder BuildCommitId { get; }` — The build changelist upon which the test ran, may not correspond to the job changelist
- L666 _public* property_ `TestId NameRef { get; }` — Reference Id to test name
- L671 _public* property_ `StreamId StreamId { get; }` — The associated stream
- L676 _public* property_ `JobId JobId { get; }` — The associated job
- L681 _public* property_ `JobStepId StepId { get; }` — The associated job step
- L686 _public* property_ `TimeSpan Duration { get; }` — How long the test session ran
- L691 _public* property_ `DateTime StartDateTime { get; }` — Date time at which the test session was started
- L700 _public* property_ `TestOutcome Outcome { get; }` — The outcome of the test session if PhasesUndefinedCount > 0 => Undefiened if PhasesFailedCount > 0 => Failure if PhasesTotalCount > 0 and PhasesSucceededCount > 0 => Success else => Skipped
- L705 _public* property_ `int PhasesTotalCount { get; }` — The total number the test session contains
- L710 _public* property_ `int PhasesSucceededCount { get; }` — The number of phases that succeeded during the test session
- L715 _public* property_ `int PhasesUndefinedCount { get; }` — The number of phases that were left undefined during the test session
- L720 _public* property_ `int PhasesFailedCount { get; }` — The number of phases that failed during the test session
- L725 _public* property_ `IReadOnlyList<IErrorFingerprintEntry>? ErrorFingerprints { get; }` — The unique error fingerprints collected from the phase events

#### interface `HordeServer.Jobs.TestData.IErrorFingerprintEntry`  
`public interface IErrorFingerprintEntry`  
_public; L731-742_
- desc: A error fingerprint entry
- L736 _public* property_ `string Key { get; }` — The error fingerprint key
- L741 _public* property_ `IReadOnlyList<string> Phases { get; }` — The phase keys associated with the error fingerprint

#### interface `HordeServer.Jobs.TestData.ITestSessionStream`  
`public interface ITestSessionStream`  
_public; L747-768_
- desc: The test sessions running in a given stream
- L752 _public* property_ `StreamId StreamId { get; }` — The stream id
- L757 _public* property_ `IReadOnlyList<TestId> Tests { get; }` — Test ids of tests running in the stream
- L762 _public* property_ `IReadOnlyList<TestMetaId> Metadata { get; }` — Test metadata ids from running tests in the stream
- L767 _public* property_ `IReadOnlyList<TestTagId> Tags { get; }` — Test tag ids from running tests in the stream

#### interface `HordeServer.Jobs.TestData.ITestPhaseSession`  
`public interface ITestPhaseSession`  
_public; L773-849_
- desc: A Test phase outcome from a test session
- L778 _public* property_ `TestPhaseSessionId Id { get; }` — The test phase session id
- L783 _public* property_ `TestPhaseId PhaseRef { get; }` — The test phase reference id
- L788 _public* property_ `TestPhaseOutcome Outcome { get; }` — The phase outcome
- L793 _public* property_ `TestSessionId SessionId { get; }` — The test session that run that phase
- L798 _public* property_ `TestMetaId Metadata { get; }` — The metadata associated with this test session
- L803 _public* property_ `string? EventStreamPath { get; }` — The path to the event stream
- L808 _public* property_ `bool? HasWarning { get; }` — Whether the test phase encountered at least one warning
- L813 _public* property_ `string? ErrorFingerprint { get; }` — The error fingerprint from the event stream
- L818 _public* property_ `IReadOnlyList<TestTagId>? Tags { get; }` — The tags associated with the phase session
- L823 _public* property_ `StreamId StreamId { get; }` — The associated stream
- L828 _public* property_ `JobId JobId { get; }` — The associated job
- L833 _public* property_ `JobStepId StepId { get; }` — The associated job step
- L838 _public* property_ `CommitIdWithOrder BuildCommitId { get; }` — The build changelist upon which the test ran, may not correspond to the job changelist
- L843 _public* property_ `TimeSpan Duration { get; }` — How long the test phase session ran
- L848 _public* property_ `DateTime StartDateTime { get; }` — Date time at which the test phase session was started

#### interface `HordeServer.Jobs.TestData.ITestData`  
`public interface ITestData`  
_public; L854-900_
- desc: Stores information about the results of a test
- L859 _public* property_ `ObjectId Id { get; }` — Unique id of the test data
- L864 _public* property_ `StreamId StreamId { get; }` — Stream that generated the test data
- L869 _public* property_ `TemplateId TemplateRefId { get; }` — The template reference id
- L874 _public* property_ `JobId JobId { get; }` — The job which produced the data
- L879 _public* property_ `JobStepId StepId { get; }` — The step that ran
- L884 _public* property_ `CommitIdWithOrder CommitId { get; }` — The commit that contained the data
- L889 _public* property_ `CommitId? PreflightCommitId { get; }` — The preflight commit id if any
- L894 _public* property_ `string Key { get; }` — Key used to identify the particular data
- L899 _public* property_ `BsonDocument Data { get; }` — The data stored for this test

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/TestData/ITestDataCollection.cs` (HordeServer.Build)


#### interface `HordeServer.Jobs.TestData.ITestDataCollection`  
`public interface ITestDataCollection`  
_public; L16-140_
- desc: Collection of test data documents
- L24 _public* method_ `Task<IReadOnlyList<ITestStream>> FindTestStreamsAsync(StreamId[] streamIds, CancellationToken cancellationToken = default)` — Gets the tests running in provided streams
- L39 _public* method_ `Task<IReadOnlyList<ITestDataRef>> FindTestRefsAsync(StreamId[] streamIds, TestMetaId[]? metaIds = null, TestId[]? testIds = null, TestSuiteId[]? suiteIds = null, DateTime? minCreateTime = null, DateTime? maxCreateTime = null, CommitId? minCommitId = null, CommitId? maxCommitId = null, CancellationToken cancellationToken = default)`
- L47 _public* method_ `Task<IReadOnlyList<ITestDataDetails>> FindTestDetailsAsync(TestRefId[] ids, CancellationToken cancellationToken = default)` — Find test details
- L55 _public* method_ `Task<IReadOnlyList<ITest>> FindTestsAsync(TestId[] testIds, CancellationToken cancellationToken = default)` — Find tests
- L63 _public* method_ `Task<IReadOnlyList<ITestSuite>> FindTestSuitesAsync(TestSuiteId[] suiteIds, CancellationToken cancellationToken = default)` — Find test suites
- L73 _public* method_ `Task<IReadOnlyList<ITestData>> AddAsync(IJob job, IJobStep step, (string key, BsonDocument value)[] data, CancellationToken cancellationToken = default)` — Creates a new test data document
- L81 _public* method_ `Task<ITestData?> GetAsync(ObjectId id, CancellationToken cancellationToken = default)` — Gets a stream by ID
- L96 _public* method_ `Task<IReadOnlyList<ITestData>> FindAsync(StreamId? streamId, CommitId? minCommitId, CommitId? maxCommitId, JobId? jobId, JobStepId? stepId, string? key = null, int index = 0, int count = 10, CancellationToken cancellationToken = default)` — Searches for test data that matches a set of criteria
- L110 _public* method_ `Task<IReadOnlyList<ITestMeta>> FindTestMetaAsync(string[]? projectNames = null, string[]? platforms = null, string[]? configurations = null, string[]? buildTargets = null, string? rhi = null, string? variation = null, TestMetaId[]? metaIds = null, CancellationToken cancellationToken = default)` — Find test meta data
- L118 _public* method_ `Task DeleteAsync(ObjectId id, CancellationToken cancellationToken = default)` — Delete the test data
- L125 _public method_ `public Task PruneDataAsync(CancellationToken cancellationToken = default)` — Prune test data from collection
- L133 _public method_ `public Task<bool> UpdateAsync(int retainMonths, CancellationToken cancellationToken = default)` — Run a tick on the collection
- L139 _public method_ `public Task UpgradeAsync(CancellationToken cancellationToken = default)` — Upgrades the collection

#### interface `HordeServer.Jobs.TestData.ITestDataCollectionV2`  
`public interface ITestDataCollectionV2`  
_public; L145-331_
- desc: Collection of test data documents v2
- L153 _public* method_ `Task<IReadOnlyList<ITestSessionStream>> FindTestSessionStreamsAsync(StreamId[] streamIds, CancellationToken cancellationToken = default)` — Gets the test sessions running in provided streams
- L167 _public* method_ `Task<IReadOnlyList<ITestSession>> FindTestSessionsAsync(StreamId[] streamIds, TestId[]? testIds = null, TestMetaId[]? metaIds = null, DateTime? minCreateTime = null, DateTime? maxCreateTime = null, CommitId? minCommitId = null, CommitId? maxCommitId = null, CancellationToken cancellationToken = default)` — Find test sessions
- L176 _public* method_ `Task<IReadOnlyList<ITestNameRef>> FindTestNameRefsAsync(TestId[]? testIds = null, string[]? keys = null, CancellationToken cancellationToken = default)` — Find test name references
- L186 _public* method_ `Task<IReadOnlyList<ITestData>> AddAsync(IJob job, IJobStep step, (string key, BsonDocument value)[] data, CancellationToken cancellationToken = default)` — Creates a new test data document
- L195 _public* method_ `Task<IReadOnlyList<ITestData>> GetJobStepTestDataAsync(JobId jobId, JobStepId? stepId = null, CancellationToken cancellationToken = default)` — Gets testdata ids run within a job step
- L203 _public* method_ `Task<ITestData?> GetAsync(ObjectId id, CancellationToken cancellationToken = default)` — Gets a testdata by ID
- L212 _public* method_ `Task<IReadOnlyList<ITestMetaRef>> FindTestMetaAsync(TestMetaId[]? metaIds = null, IReadOnlyDictionary<string, string>? keyValues = null, CancellationToken cancellationToken = default)` — Find test metadata set
- L221 _public* method_ `Task<IReadOnlyList<ITestPhaseRef>> FindTestPhasesAsync(TestId[] testIds, string[]? keys = null, CancellationToken cancellationToken = default)` — Find test phase references associated with a set of tests
- L230 _public* method_ `Task<IReadOnlyList<ITestTagRef>> FindTestTagsAsync(TestTagId[]? tagIds = null, string[]? names = null, CancellationToken cancellationToken = default)` — Find test tag references
- L240 _public* method_ `Task<IReadOnlyList<ITestRecipeRef>> FindTestRecipesAsync(TestRecipeId[]? recipeIds = null, TestId[]? testIds = null, StreamId[]? streamIds = null, CancellationToken cancellationToken = default)` — Find test recipe references
- L253 _public* method_ `Task<IReadOnlyList<ITestPhaseSession>> FindTestPhaseSessionsAsync(StreamId[] streamIds, TestPhaseId[] phaseIds, DateTime? minCreateTime = null, DateTime? maxCreateTime = null, CommitId? minCommitId = null, CommitId? maxCommitId = null, CancellationToken cancellationToken = default)` — Find test phase sessions from a set of test phases
- L263 _public* method_ `Task<ITestAudit> AddTestAuditAsync(UserId userId, TestId testId, TestAuditOptions options, CancellationToken cancellationToken = default)` — Add test audit entry
- L272 _public* method_ `Task<IReadOnlyList<ITestAudit>> FindTestAuditsAsync(TestId[] testIds, DateTime? minCreateTime = null, CancellationToken cancellationToken = default)` — Find audits related to tests
- L279 _public* method_ `Task<IReadOnlyList<ITestAudit>> FindTestWithAuditNotificationWorkflowAsync(CancellationToken cancellationToken = default)` — Find audits related to tests with notification workflow
- L286 _public* method_ `IAuditLogChannel<TestId> GetTestAuditLogger(TestId testId)` — Get the logger for the specified test id
- L297 _public* method_ `Task<ITestHealthReport> AddOrUpdateTestHealthReportAsync(TestId testId, StreamId streamId, string testName, ComputedTestHealth testHealth, CancellationToken cancellationToken = default)` — Add or update test health report
- L306 _public* method_ `Task<IReadOnlyList<ITestHealthReport>> FindTestHealthReportsAsync(StreamId[] streamIds, TestId[]? testIds, CancellationToken cancellationToken = default)` — Find Test health reports associated with test ids and stream ids
- L315 _public* method_ `Task UpdateTestHealthReportNotificationDateAsync(ObjectId reportId, bool resetDate, CancellationToken cancellationToken = default)` — Update test health report notification date
- L322 _public* method_ `Task PruneDataAsync(CancellationToken cancellationToken = default)` — Prune test data from collection
- L330 _public* method_ `Task<bool> UpdateAsync(int retainMonths, CancellationToken cancellationToken = default)` — Run a tick on the collection

#### class `HordeServer.Jobs.TestData.TestNotificationSettingsOptions`  
`public class TestNotificationSettingsOptions`  
_public; L336-347_
- desc: Test notification setting options
- L341 _public property_ `public StreamId Stream { get; set; }` — The stream id
- L346 _public property_ `public WorkflowId Workflow { get; set; }` — The workflow id associated with the stream

#### class `HordeServer.Jobs.TestData.TestAuditOptions`  
`public class TestAuditOptions`  
_public; L352-408_
- desc: The test audit options
- L357 _public property_ `public bool EnableSchedule { get; set; }` — Whether or not the test schedule is enabled
- L362 _public property_ `public DateTime? LastAuditDate { get; set; }` — The last audit Date
- L367 _public property_ `public bool? IsUnderAudit { get; set; }` — Whether or not the test is under audit
- L372 _public property_ `public UserId? Owner { get; set; }` — The owner of the related test
- L377 _public property_ `public List<UserId>? Customers { get; set; }` — The customers of the related test
- L382 _public property_ `public List<TestNotificationSettingsOptions>? Notifications { get; set; }` — The notifications settings options
- L387 _public property_ `public string? Team { get; set; }` — The team associated with the test
- L392 _public property_ `public string? Harness { get; set; }` — The harness associated with the test
- L397 _public property_ `public string? Intent { get; set; }` — The intent of the test
- L402 _public property_ `public string? Profile { get; set; }` — The profile associated with the test
- L407 _public property_ `public string? Notes { get; set; }` — The notes associated with the test audit

#### class `HordeServer.Jobs.TestData.ComputedTestHealth`  
`public class ComputedTestHealth`  
_public; L413-444_
- desc: The computed health for a report
- L418 _public property_ `public bool IsHealthy { get; set; }` — Whether the rates distribution is deemed healthy
- L423 _public property_ `public string State { get; set; }` — A label that describes the health state
- L428 _public property_ `public int SuccessRate { get; set; }` — The rate of success
- L433 _public property_ `public int FailureRate { get; set; }` — The rate of failure
- L438 _public property_ `public int CatastrophicFailureRate { get; set; }` — The rate of catastrophic failure
- L443 _public property_ `public int RedundantErrorRate { get; set; }` — The rate of redundant error

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/TestData/TestAuditId.cs` (HordeServer.Build)


#### record struct `HordeServer.Jobs.TestData.TestAuditId`  
`public record struct TestAuditId(ObjectId Id)`  
_public; L17-54_
- attrs: `[JsonSchemaString] [TypeConverter(typeof(ObjectIdTypeConverter<TestAuditId, TestAuditIdConverter>))] [ObjectIdConverter(typeof(TestAuditIdConverter))]`
- desc: Identifier for a test audit
- L22 _public property_ `public static TestAuditId Empty { get; }` — Default empty value for test audit id
- L27 _public method_ `public static TestAuditId GenerateNewId()` — Creates a new TestAuditId
- L34 _public method_ `public static TestAuditId GenerateNewId(DateTime time)` — Creates a new TestAuditId
- L37 _public method_ `public static TestAuditId Parse(string text)` — (inheritdoc)
- L40-50 _public method_ `public static bool TryParse(string text, out TestAuditId id)` — (inheritdoc)
- L53 _public method_ `public override string ToString()` — (inheritdoc)

#### class `HordeServer.Jobs.TestData.TestAuditIdConverter`  
`class TestAuditIdConverter : ObjectIdConverter<TestAuditId>`  
_internal*; L59-66_
- inherits: `ObjectIdConverter<TestAuditId>`
- desc: Converter to and from ObjectId instances.
- L62 _public method_ `public override TestAuditId FromObjectId(ObjectId id)` — (inheritdoc)
- L65 _public method_ `public override ObjectId ToObjectId(TestAuditId value)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/TestData/TestDataAclAction.cs` (HordeServer.Build)


#### class `HordeServer.Jobs.TestData.TestDataAclAction`  
`public static class TestDataAclAction`  
_public; L10-21_
- desc: ACL actions which apply to test data
- L15 _public property_ `public static AclAction TestHealthRead { get; }` — Ability to read test health
- L20 _public property_ `public static AclAction TestHealthWrite { get; }` — Ability to write test health

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/TestData/TestDataCollection.cs` (HordeServer.Build)


#### class `HordeServer.Jobs.TestData.TestDataCollection`  
`public class TestDataCollection : ITestDataCollection`  
_public; L24-1721_
- inherits: `ITestDataCollection`
- desc: Collection of test data documents
- L388 _private* field_ `readonly IMongoCollection<TestDataDocument> _testDataDocuments`
- L389 _private* field_ `readonly IMongoCollection<TestMetaDocument> _testMeta`
- L390 _private* field_ `readonly IMongoCollection<TestDocument> _tests`
- L391 _private* field_ `readonly IMongoCollection<TestSuiteDocument> _testSuites`
- L392 _private* field_ `readonly IMongoCollection<TestDataRefDocument> _testRefs`
- L393 _private* field_ `readonly IMongoCollection<TestDataDetailsDocument> _testDetails`
- L394 _private* field_ `readonly IMongoCollection<TestStreamDocument> _testStreams`
- L395 _private* field_ `readonly ICommitService _commitService`
- L396 _private* field_ `readonly Tracer _tracer`
- L397 _private* field_ `readonly ILogger _logger`
- L402-435 _public ctor_ `public TestDataCollection(IMongoService mongoService, ICommitService commitService, Tracer tracer, ILogger<TestDataCollection> logger)` — Constructor
- L438-501 _public method_ `public async Task<IReadOnlyList<ITestDataRef>> FindTestRefsAsync(StreamId[] streamIds, TestMetaId[]? metaIds = null, TestId[]? testIds = null, TestSuiteId[]? suiteIds = null, DateTime? minCreateTime = null, DateTime? maxCreateTime = null, CommitId? minCommitId = null, CommitId? maxCommitId = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L504-541 _public method_ `public async Task<IReadOnlyList<ITestData>> AddAsync(IJob job, IJobStep step, (string key, BsonDocument value)[] data, CancellationToken cancellationToken = default)` — (inheritdoc)
- L544-547 _public method_ `public async Task<ITestData?> GetAsync(ObjectId id, CancellationToken cancellationToken)` — (inheritdoc)
- L550-583 _public method_ `public async Task<IReadOnlyList<ITestData>> FindAsync(StreamId? streamId, CommitId? minCommitId, CommitId? maxCommitId, JobId? jobId, JobStepId? stepId, string? key = null, int index = 0, int count = 10, CancellationToken cancellationToken = default)` — (inheritdoc)
- L586-589 _public method_ `public async Task DeleteAsync(ObjectId id, CancellationToken cancellationToken = default)` — (inheritdoc)
- L592-607 _public method_ `public async Task<IReadOnlyList<ITestDataDetails>> FindTestDetailsAsync(TestRefId[] ids, CancellationToken cancellationToken = default)` — (inheritdoc)
- L610-686 _public method_ `public async Task<IReadOnlyList<ITestMeta>> FindTestMetaAsync(string[]? projectNames = null, string[]? platforms = null, string[]? configurations = null, string[]? buildTargets = null, string? rhi = null, string? variation = null, TestMetaId[]? metaIds = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L689-693 _public method_ `public async Task<IReadOnlyList<ITest>> FindTestsAsync(TestId[] testIds, CancellationToken cancellationToken = default)` — (inheritdoc)
- L696-700 _public method_ `public async Task<IReadOnlyList<ITestSuite>> FindTestSuitesAsync(TestSuiteId[] suiteIds, CancellationToken cancellationToken = default)` — (inheritdoc)
- L702-773 _private method_ `private async Task<List<TestDocument>> FindTestsAsync(bool? suiteTests = null, string[]? projectNames = null, string[]? testNames = null, string[]? suiteNames = null, TestMetaId[]? metaIds = null, TestId[]? testIds = null, CancellationToken cancellationToken = default)`
- L775-811 _private method_ `private async Task<List<TestSuiteDocument>> FindTestSuitesAsync(string[] suiteNames, TestMetaId[]? metaIds = null, string[]? projectNames = null, CancellationToken cancellationToken = default)`
- L814-817 _public method_ `public async Task<IReadOnlyList<ITestStream>> FindTestStreamsAsync(StreamId[] streamIds, CancellationToken cancellationToken)` — (inheritdoc)
- L819-873 _private* method_ `async Task AddTestRefAsync(TestDataRefDocument testRef, CancellationToken cancellationToken)`
- L884-955 _private method_ `private async Task<ITestMeta?> AddTestMetaAsync(Dictionary<string, string> metaData, IJob job, IJobStep step, string testName, CancellationToken cancellationToken)`
- L957-1003 _private* method_ `async Task<TestDocument?> AddOrUpdateTestAsync(ITestMeta metaData, string testName, string? suiteName = null, string? displayName = null, CancellationToken cancellationToken = default)`
- L1005-1049 _private method_ `private async Task<TestSuiteDocument?> AddOrUpdateTestSuiteAsync(string suiteName, ITestMeta metaData, List<TestId> testIds, CancellationToken cancellationToken)`
- L1051-1096 _private* method_ `async Task AddTestReportDataAsync(IJob job, IJobStep step, List<TestDataDocument> documents, CancellationToken cancellationToken = default)`
- L1099-1232 _public method_ `public async Task PruneDataAsync(CancellationToken cancellationToken = default)` — (inheritdoc)
- L1234-1243 _private* method_ `static async Task<long> ExpireCollectionAsync<DocType>(IMongoCollection<DocType> collection, DateTime expireTime, CancellationToken cancellationToken) where DocType : ITestExpire`
- L1245-1305 _private* method_ `async Task ExpireTestDataAsync(int retainMonths, CancellationToken cancellationToken)`
- L1308-1313 _public method_ `public async Task<bool> UpdateAsync(int retainMonths, CancellationToken cancellationToken)` — (inheritdoc)
- L1316-1406 _public method_ `public async Task UpgradeAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L1486-1539 _private* method_ `async Task AddSimpleReportDataAsync(IJob job, IJobStep step, ObjectId testDataId, BsonDocument testDoc, CancellationToken cancellationToken)`
- L1541-1720 _private* method_ `async Task AddTestSessionReportDataAsync(IJob job, IJobStep step, List<TestDataDocument> documents, List<AutomatedTestSessionData> sessions, List<UnrealAutomatedTestData> tests, CancellationToken cancellationToken)`

#### interface `HordeServer.Jobs.TestData.TestDataCollection.ITestExpire`  
`internal interface ITestExpire`  
_internal; L26-29_
- L28 _public* property_ `DateTime? LastSeenUtc { get; }`

#### class `HordeServer.Jobs.TestData.TestDataCollection.TestMetaDocument`  
`class TestMetaDocument : ITestMeta, ITestExpire`  
_private*; L31-88_
- inherits: `ITestMeta, ITestExpire`
- L34 _public property_ `public TestMetaId Id { get; set; }` — attrs: `[BsonRequired, BsonId]`
- L37 _public property_ `public List<string> Platforms { get; set; }` — attrs: `[BsonRequired, BsonElement("p")]`
- L38 _private* property_ `IReadOnlyList<string> ITestMeta.Platforms => ...`
- L41 _public property_ `public List<string> Configurations { get; set; }` — attrs: `[BsonRequired, BsonElement("c")]`
- L42 _private* property_ `IReadOnlyList<string> ITestMeta.Configurations => ...`
- L45 _public property_ `public List<string> BuildTargets { get; set; }` — attrs: `[BsonRequired, BsonElement("bt")]`
- L46 _private* property_ `IReadOnlyList<string> ITestMeta.BuildTargets => ...`
- L49 _public property_ `public string ProjectName { get; set; }` — attrs: `[BsonRequired, BsonElement("pn")]`
- L52 _public property_ `public string RHI { get; set; }` — attrs: `[BsonRequired, BsonElement("r")]`
- L55 _public property_ `public string Variation { get; set; }` — attrs: `[BsonElement("v")]`
- L58 _public property_ `public DateTime? LastSeenUtc { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("s")]`
- L61 _public property_ `public int? Version { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("vn")]`
- L63 _public field_ `public static int CurrentVersion = 1`
- L65-74 _private ctor_ `private TestMetaDocument()`
- L76-87 _public ctor_ `public TestMetaDocument(List<string> platforms, List<string> configurations, List<string> buildTargets, string projectName, string? rhi, string? variation)`

#### class `HordeServer.Jobs.TestData.TestDataCollection.TestDocument`  
`class TestDocument : ITest, ITestExpire`  
_private*; L90-132_
- inherits: `ITest, ITestExpire`
- L93 _public property_ `public TestId Id { get; set; }` — attrs: `[BsonRequired, BsonId]`
- L96 _public property_ `public string Name { get; set; }` — attrs: `[BsonRequired, BsonElement("n")]`
- L99 _public property_ `public string? SuiteName { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("sn")]`
- L102 _public property_ `public string? DisplayName { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("dn")]`
- L105 _public property_ `public List<TestMetaId> Metadata { get; set; }` — attrs: `[BsonRequired, BsonElement("m")]`
- L106 _private* property_ `IReadOnlyList<TestMetaId> ITest.Metadata => ...`
- L109 _public property_ `public int? Version { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("vn")]`
- L112 _public property_ `public DateTime? LastSeenUtc { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("s")]`
- L114 _public field_ `public static int CurrentVersion = 1`
- L116-120 _private ctor_ `private TestDocument()`
- L122-131 _public ctor_ `public TestDocument(string name, List<TestMetaId> meta, string? suiteName = null, string? displayName = null)`

#### class `HordeServer.Jobs.TestData.TestDataCollection.TestSuiteDocument`  
`class TestSuiteDocument : ITestSuite, ITestExpire`  
_private*; L134-174_
- inherits: `ITestSuite, ITestExpire`
- L137 _public property_ `public TestSuiteId Id { get; set; }` — attrs: `[BsonRequired, BsonId]`
- L140 _public property_ `public string Name { get; set; }` — attrs: `[BsonRequired, BsonElement("n")]`
- L143 _public property_ `public List<TestMetaId> Metadata { get; set; }` — attrs: `[BsonRequired, BsonElement("m")]`
- L144 _private* property_ `IReadOnlyList<TestMetaId> ITestSuite.Metadata => ...`
- L147 _public property_ `public List<TestId> Tests { get; set; }` — attrs: `[BsonRequired, BsonElement("t")]`
- L148 _private* property_ `IReadOnlyList<TestId> ITestSuite.Tests => ...`
- L151 _public property_ `public DateTime? LastSeenUtc { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("s")]`
- L154 _public property_ `public int? Version { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("vn")]`
- L156 _public field_ `public static int CurrentVersion = 1`
- L158-163 _private ctor_ `private TestSuiteDocument()`
- L165-173 _public ctor_ `public TestSuiteDocument(string name, List<TestMetaId> metaIds, List<TestId> tests)`

#### class `HordeServer.Jobs.TestData.TestDataCollection.TestStreamDocument`  
`class TestStreamDocument : ITestStream`  
_private*; L179-205_
- inherits: `ITestStream`
- desc: Stores the tests and suites running in a stream
- L182 _public property_ `public ObjectId Id { get; set; }` — attrs: `[BsonRequired, BsonId]`
- L185 _public property_ `public StreamId StreamId { get; set; }` — attrs: `[BsonRequired]`
- L188 _public property_ `public List<TestId> Tests { get; set; }` — attrs: `[BsonRequired]`
- L189 _private* property_ `IReadOnlyList<TestId> ITestStream.Tests => ...`
- L192 _public property_ `public List<TestSuiteId> TestSuites { get; set; }` — attrs: `[BsonRequired]`
- L193 _private* property_ `IReadOnlyList<TestSuiteId> ITestStream.TestSuites => ...`
- L195-198 _private ctor_ `private TestStreamDocument()`
- L200-204 _public ctor_ `public TestStreamDocument(StreamId streamId)`

#### class `HordeServer.Jobs.TestData.TestDataCollection.SuiteTestData`  
`class SuiteTestData : ISuiteTestData`  
_private*; L207-236_
- inherits: `ISuiteTestData`
- L210 _public property_ `public TestId TestId { get; set; }` — attrs: `[BsonRequired, BsonElement("tid")]`
- L213 _public property_ `public TestOutcome Outcome { get; set; }` — attrs: `[BsonRequired, BsonElement("o")]`
- L216 _public property_ `public TimeSpan Duration { get; set; }` — attrs: `[BsonRequired, BsonElement("d")]`
- L219 _public property_ `public string UID { get; set; }` — attrs: `[BsonRequired, BsonElement("uid")]`
- L222 _public property_ `public int? WarningCount { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("wc")]`
- L225 _public property_ `public int? ErrorCount { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("ec")]`
- L227-235 _public ctor_ `public SuiteTestData(TestId id, TestOutcome outcome, TimeSpan duration, string uid, int? warningCount, int? errorCount)`

#### class `HordeServer.Jobs.TestData.TestDataCollection.TestDataRefDocument`  
`class TestDataRefDocument : ITestDataRef`  
_private*; L238-303_
- inherits: `ITestDataRef`
- L241 _public property_ `public TestRefId Id { get; set; }` — attrs: `[BsonRequired, BsonId]`
- L244 _public property_ `public StreamId StreamId { get; set; }` — attrs: `[BsonRequired, BsonElement("sid")]`
- L247 _public property_ `public TestMetaId Metadata { get; set; }` — attrs: `[BsonRequired, BsonElement("m")]`
- L249-253 _public property_ `public CommitIdWithOrder BuildCommitId { get; set; }`
- L256 _public property_ `public string? BuildCommitName { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("bcn")]`
- L259 _public property_ `public int BuildCommitOrder { get; set; }` — attrs: `[BsonRequired, BsonElement("bcl")]`
- L262 _public property_ `public TimeSpan Duration { get; set; }` — attrs: `[BsonRequired, BsonElement("d")]`
- L266 _public property_ `public TestId? TestId { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("tid")]`
- L269 _public property_ `public TestOutcome? Outcome { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("o")]`
- L273 _public property_ `public TestSuiteId? SuiteId { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("suid")]`
- L276 _public property_ `public int? SuiteSkipCount { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("ssc")]`
- L279 _public property_ `public int? SuiteWarningCount { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("swc")]`
- L282 _public property_ `public int? SuiteErrorCount { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("sec")]`
- L285 _public property_ `public int? SuiteSuccessCount { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("spc")]`
- L288 _public property_ `public JobId? JobId { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("jid")]`
- L291 _public property_ `public JobStepId? StepId { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("stepid")]`
- L293-296 _private ctor_ `private TestDataRefDocument()`
- L298-302 _public ctor_ `public TestDataRefDocument(StreamId streamId)`

#### class `HordeServer.Jobs.TestData.TestDataCollection.TestDataDetailsDocument`  
`class TestDataDetailsDocument : ITestDataDetails`  
_private*; L305-338_
- inherits: `ITestDataDetails`
- L311 _public property_ `public TestRefId Id { get; set; }` — attrs: `[BsonRequired, BsonId]` — The corresponding test ref for these details
- L317 _public property_ `public List<ObjectId> TestDataIds { get; set; }` — attrs: `[BsonRequired, BsonElement("tdid")]` — The full (raw) data for this test, which can be consumed by various clients
- L318 _private* property_ `IReadOnlyList<ObjectId> ITestDataDetails.TestDataIds => ...`
- L324 _public property_ `public List<SuiteTestData>? SuiteTests { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("sts")]` — Suite test data
- L325 _private* property_ `IReadOnlyList<ISuiteTestData>? ITestDataDetails.SuiteTests => ...`
- L327-330 _private ctor_ `private TestDataDetailsDocument()`
- L332-337 _public ctor_ `public TestDataDetailsDocument(TestRefId id, List<ObjectId> testDataIds, List<SuiteTestData>? suiteTests = null)`

#### class `HordeServer.Jobs.TestData.TestDataCollection.TestDataDocument`  
`class TestDataDocument : ITestData`  
_private*; L343-386_
- inherits: `ITestData`
- desc: Information about a test data document
- L345 _public property_ `public ObjectId Id { get; set; }`
- L346 _public property_ `public StreamId StreamId { get; set; }`
- L347 _public property_ `public TemplateId TemplateRefId { get; set; }`
- L348 _public property_ `public JobId JobId { get; set; }`
- L349 _public property_ `public JobStepId StepId { get; set; }`
- L352-356 _public property_ `public CommitIdWithOrder CommitId { get; set; }` — attrs: `[BsonIgnore]`
- L358 _public property_ `public string? CommitName { get; set; }`
- L361 _public property_ `public int CommitOrder { get; set; }` — attrs: `[BsonElement("Change")]`
- L364 _public property_ `public CommitId? PreflightCommitId => ...` — attrs: `[BsonIgnore]`
- L366 _public property_ `public string Key { get; set; }`
- L367 _public property_ `public BsonDocument Data { get; set; }`
- L369-373 _private ctor_ `private TestDataDocument()`
- L375-385 _public ctor_ `public TestDataDocument(IJob job, IJobStep jobStep, string key, BsonDocument value)`

#### class `HordeServer.Jobs.TestData.TestDataCollection.AutomatedTestSessionData`  
`class AutomatedTestSessionData`  
_private*; L1410-1437_
- L1431 _public property_ `public string Type { get; set; }`
- L1432 _public property_ `public string Name { get; set; }`
- L1434 _public property_ `public TestSessionInfoType? TestSessionInfo { get; set; }`
- L1435 _public property_ `public Dictionary<string, string> Metadata { get; set; }`

#### class `HordeServer.Jobs.TestData.TestDataCollection.AutomatedTestSessionData.SessionTest`  
`public class SessionTest`  
_public; L1412-1422_
- L1414 _public property_ `public string Name { get; set; }`
- L1415 _public property_ `public string TestUID { get; set; }`
- L1416 _public property_ `public string Suite { get; set; }`
- L1417 _public property_ `public string State { get; set; }`
- L1418 _public property_ `public List<string> DeviceAppInstanceName { get; set; }`
- L1419 _public property_ `public int ErrorCount { get; set; }`
- L1420 _public property_ `public int WarningCount { get; set; }`
- L1421 _public property_ `public double TimeElapseSec { get; set; }`

#### class `HordeServer.Jobs.TestData.TestDataCollection.AutomatedTestSessionData.TestSessionInfoType`  
`public class TestSessionInfoType`  
_public; L1424-1429_
- L1426 _public property_ `public double TimeElapseSec { get; set; }`
- L1427 _public property_ `public Dictionary<string, SessionTest> Tests { get; set; }`
- L1428 _public property_ `public string TestResultsTestDataUID { get; set; }`

#### class `HordeServer.Jobs.TestData.TestDataCollection.UnrealAutomatedTestData`  
`class UnrealAutomatedTestData`  
_private*; L1439-1456_
- L1451 _public property_ `public string Type { get; set; }`
- L1452 _public property_ `public double TotalDurationSeconds { get; set; }`
- L1453 _public property_ `public List<UnrealTest> Tests { get; set; }`
- L1454 _public property_ `public Dictionary<string, string> Metadata { get; set; }`

#### class `HordeServer.Jobs.TestData.TestDataCollection.UnrealAutomatedTestData.UnrealTest`  
`public class UnrealTest`  
_public; L1441-1449_
- L1443 _public property_ `public string TestDisplayName { get; set; }`
- L1444 _public property_ `public string FullTestPath { get; set; }`
- L1445 _public property_ `public string State { get; set; }`
- L1446 _public property_ `public string DeviceInstance { get; set; }`
- L1447 _public property_ `public int Errors { get; set; }`
- L1448 _public property_ `public int Warnings { get; set; }`

#### class `HordeServer.Jobs.TestData.TestDataCollection.TestRole`  
`class TestRole`  
_private*; L1460-1465_
- L1462 _public property_ `public string Type { get; set; }`
- L1463 _public property_ `public string Platform { get; set; }`
- L1464 _public property_ `public string Configuration { get; set; }`

#### class `HordeServer.Jobs.TestData.TestDataCollection.SimpleTestData`  
`class SimpleTestData`  
_private*; L1467-1484_
- L1469 _public property_ `public string TestName { get; set; }`
- L1470 _public property_ `public string Description { get; set; }`
- L1471 _public property_ `public string ReportCreatedOn { get; set; }`
- L1472 _public property_ `public double TotalDurationSeconds { get; set; }`
- L1473 _public property_ `public bool HasSucceeded { get; set; }`
- L1474 _public property_ `public string Status { get; set; }`
- L1475 _public property_ `public string URLLink { get; set; }`
- L1476 _public property_ `public int BuildChangeList { get; set; }`
- L1477 _public property_ `public TestRole? MainRole { get; set; }`
- L1478 _public property_ `public List<TestRole>? Roles { get; set; }`
- L1479 _public property_ `public string TestResult { get; set; }`
- L1480 _public property_ `public List<string> Logs { get; set; }`
- L1481 _public property_ `public List<string> Errors { get; set; }`
- L1482 _public property_ `public List<string> Warnings { get; set; }`
- L1483 _public property_ `public Dictionary<string, string> Metadata { get; set; }`

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/TestData/TestDataCollectionV2.cs` (HordeServer.Build)


#### class `HordeServer.Jobs.TestData.TestDataCollectionV2`  
`public class TestDataCollectionV2 : ITestDataCollectionV2`  
_public; L25-1869_
- inherits: `ITestDataCollectionV2`
- desc: Collection of test data documents v2
- L723 _private* field_ `readonly IMongoCollection<TestDataDocument> _testDataDocuments`
- L724 _private* field_ `readonly IMongoCollection<TestMetadataDocument> _testMeta`
- L725 _private* field_ `readonly IMongoCollection<TestRecipeDocument> _testRecipes`
- L726 _private* field_ `readonly IMongoCollection<TestTagDocument> _testTags`
- L727 _private* field_ `readonly IMongoCollection<TestNameDocument> _tests`
- L728 _private* field_ `readonly IMongoCollection<TestPhaseDocument> _testPhases`
- L729 _private* field_ `readonly IMongoCollection<TestSessionDocument> _testSessions`
- L730 _private* field_ `readonly IMongoCollection<TestPhaseSessionDocument> _testPhaseSessions`
- L731 _private* field_ `readonly IMongoCollection<TestSessionStreamDocument> _testStreams`
- L732 _private* field_ `readonly IMongoCollection<TestAuditDocument> _testAudits`
- L733 _private* field_ `readonly IMongoCollection<TestHealthReportDocument> _testHealthReports`
- L734 _private* field_ `readonly Tracer _tracer`
- L735 _private* field_ `readonly ILogger _logger`
- L736 _private* field_ `readonly IAuditLog<TestId> _auditLog`
- L741-790 _public ctor_ `public TestDataCollectionV2(IMongoService mongoService, Tracer tracer, ILogger<TestDataCollection> logger, IAuditLog<TestId> auditLog)` — Constructor
- L793-796 _public method_ `public async Task<IReadOnlyList<ITestSessionStream>> FindTestSessionStreamsAsync(StreamId[] streamIds, CancellationToken cancellationToken = default)` — (inheritdoc)
- L799-848 _public method_ `public async Task<IReadOnlyList<ITestSession>> FindTestSessionsAsync(StreamId[] streamIds, TestId[]? testIds = null, TestMetaId[]? metaIds = null, DateTime? minCreateTime = null, DateTime? maxCreateTime = null, CommitId? minCommitId = null, CommitId? maxCommitId = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L851-867 _public method_ `public async Task<IReadOnlyList<ITestNameRef>> FindTestNameRefsAsync(TestId[]? testIds = null, string[]? keys = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L870-890 _public method_ `public async Task<IReadOnlyList<ITestMetaRef>> FindTestMetaAsync(TestMetaId[]? metaIds = null, IReadOnlyDictionary<string, string>? keyValues = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L893-906 _public method_ `public async Task<IReadOnlyList<ITestPhaseRef>> FindTestPhasesAsync(TestId[] testIds, string[]? keys = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L909-925 _public method_ `public async Task<IReadOnlyList<ITestTagRef>> FindTestTagsAsync(TestTagId[]? tagIds = null, string[]? names = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L928-949 _public method_ `public async Task<IReadOnlyList<ITestRecipeRef>> FindTestRecipesAsync(TestRecipeId[]? recipeIds = null, TestId[]? testIds = null, StreamId[]? streamIds = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L952-992 _public method_ `public async Task<IReadOnlyList<ITestPhaseSession>> FindTestPhaseSessionsAsync(StreamId[] streamIds, TestPhaseId[] phaseIds, DateTime? minCreateTime = null, DateTime? maxCreateTime = null, CommitId? minCommitId = null, CommitId? maxCommitId = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L995-1030 _public method_ `public async Task<IReadOnlyList<ITestData>> AddAsync(IJob job, IJobStep step, (string key, BsonDocument value)[] data, CancellationToken cancellationToken = default)` — (inheritdoc)
- L1033-1046 _public method_ `public async Task<IReadOnlyList<ITestData>> GetJobStepTestDataAsync(JobId jobId, JobStepId? stepId = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L1049-1052 _public method_ `public async Task<ITestData?> GetAsync(ObjectId id, CancellationToken cancellationToken)` — (inheritdoc)
- L1137-1266 _private method_ `private async Task AddTestReportDataAsync(IJob job, IJobStep step, IReadOnlyList<TestDataDocument> data, CancellationToken cancellationToken = default)`
- L1268-1298 _private method_ `private async Task<ITestMetaRef> AddTestMetadataAsync(IReadOnlyDictionary<string, string> metaData, CancellationToken cancellationToken)`
- L1300-1344 _private method_ `private async Task<ITestRecipeRef?> AddTestRecipeAsync(TestId nameRef, AutomatedTestSessionData.TestRecipe recipe, IJob job, IJobStep jobStep, StreamId streamId, CancellationToken cancellationToken)`
- L1346-1379 _private method_ `private async Task<IReadOnlyList<ITestTagRef>?> AddTestTagsAsync(IReadOnlyList<string>? tags, CancellationToken cancellationToken)`
- L1381-1431 _private method_ `private async Task<ITestNameRef> AddTestAsync(string key, string name, TestMetaId metadataId, IReadOnlyList<TestTagId>? tags, AutomatedTestSessionData.TestDescription? description, StreamId streamId, CancellationToken cancellationToken)`
- L1433-1482 _private method_ `private async Task AddTestToStreamSessionAsync(TestId testRef, TestMetaId metadataId, IReadOnlyList<TestTagId>? tags, StreamId streamId, CancellationToken cancellationToken)`
- L1484-1510 _private method_ `private async Task<ITestPhaseRef> AddTestPhaseAsync(TestId testId, string key, string name, CancellationToken cancellationToken)`
- L1513-1554 _public method_ `public async Task<ITestAudit> AddTestAuditAsync(UserId userId, TestId testId, TestAuditOptions options, CancellationToken cancellationToken = default)` — (inheritdoc)
- L1557-1578 _public method_ `public async Task<IReadOnlyList<ITestAudit>> FindTestAuditsAsync(TestId[] testIds, DateTime? minCreateTime = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L1581-1593 _public method_ `public async Task<IReadOnlyList<ITestAudit>> FindTestWithAuditNotificationWorkflowAsync(CancellationToken cancellationToken = default)` — (inheritdoc)
- L1596-1599 _public method_ `public IAuditLogChannel<TestId> GetTestAuditLogger(TestId testId)` — (inheritdoc)
- L1602-1641 _public method_ `public async Task<ITestHealthReport> AddOrUpdateTestHealthReportAsync(TestId testId, StreamId streamId, string testName, ComputedTestHealth testHealth, CancellationToken cancellationToken = default)` — (inheritdoc)
- L1644-1658 _public method_ `public async Task<IReadOnlyList<ITestHealthReport>> FindTestHealthReportsAsync(StreamId[] streamIds, TestId[]? testIds, CancellationToken cancellationToken = default)` — (inheritdoc)
- L1661-1667 _public method_ `public async Task UpdateTestHealthReportNotificationDateAsync(ObjectId reportId, bool resetDate, CancellationToken cancellationToken = default)` — (inheritdoc)
- L1670-1675 _public method_ `public async Task<bool> UpdateAsync(int retainMonths, CancellationToken cancellationToken)` — (inheritdoc)
- L1677-1685 _private* method_ `static async Task<long> ExpireCollectionAsync<DocType>(IMongoCollection<DocType> collection, DateTime expireTime, CancellationToken cancellationToken) where DocType : ITestExpire`
- L1687-1764 _private method_ `private async Task ExpireTestDataAsync(int retainMonths, CancellationToken cancellationToken)`
- L1767-1868 _public method_ `public async Task PruneDataAsync(CancellationToken cancellationToken = default)` — (inheritdoc)

#### interface `HordeServer.Jobs.TestData.TestDataCollectionV2.ITestExpire`  
`internal interface ITestExpire`  
_internal; L30-33_
- desc: Interface to handle expiration
- L32 _public* property_ `DateTime LastSeenUtc { get; }`

#### class `HordeServer.Jobs.TestData.TestDataCollectionV2.TestMetaEntry`  
`class TestMetaEntry : ITestMetaEntry`  
_private*; L38-57_
- inherits: `ITestMetaEntry`
- desc: Metadata key value pair
- L41 _public property_ `public string Key { get; set; }` — attrs: `[BsonRequired, BsonElement("k")]`
- L44 _public property_ `public string Value { get; set; }` — attrs: `[BsonRequired, BsonElement("v")]`
- L46-50 _private ctor_ `private TestMetaEntry()`
- L52-56 _public ctor_ `public TestMetaEntry(string key, string data)`

#### class `HordeServer.Jobs.TestData.TestDataCollectionV2.TestMetadataDocument`  
`class TestMetadataDocument : ITestMetaRef, ITestExpire`  
_private*; L62-85_
- inherits: `ITestMetaRef, ITestExpire`
- desc: Test metadata document
- L65 _public property_ `public TestMetaId Id { get; set; }` — attrs: `[BsonRequired, BsonId]`
- L68 _public property_ `public List<TestMetaEntry> Entries { get; set; }` — attrs: `[BsonRequired, BsonElement("m")]`
- L69 _private* property_ `IReadOnlyList<ITestMetaEntry> ITestMetaRef.Entries => ...`
- L72 _public property_ `public DateTime LastSeenUtc { get; set; }` — attrs: `[BsonRequired, BsonElement("s")]`
- L74-77 _private ctor_ `private TestMetadataDocument()`
- L79-84 _public ctor_ `public TestMetadataDocument(IReadOnlyDictionary<string, string> entries)`

#### class `HordeServer.Jobs.TestData.TestDataCollectionV2.TestParamEntry`  
`class TestParamEntry : ITestParamEntry`  
_private*; L90-109_
- inherits: `ITestParamEntry`
- desc: Param key value pair
- L93 _public property_ `public string Key { get; set; }` — attrs: `[BsonRequired, BsonElement("k")]`
- L96 _public property_ `public object Value { get; set; }` — attrs: `[BsonRequired, BsonElement("v")]`
- L98-102 _private ctor_ `private TestParamEntry()`
- L104-108 _public ctor_ `public TestParamEntry(string key, object data)`

#### class `HordeServer.Jobs.TestData.TestDataCollectionV2.TestRecipeDocument`  
`class TestRecipeDocument : ITestRecipeRef, ITestExpire`  
_private*; L114-177_
- inherits: `ITestRecipeRef, ITestExpire`
- desc: Test recipe reference document
- L117 _public property_ `public TestRecipeId Id { get; set; }` — attrs: `[BsonRequired, BsonId]`
- L120 _public property_ `public TestId NameRef { get; set; }` — attrs: `[BsonRequired, BsonElement("t")]`
- L123 _public property_ `public StreamId StreamId { get; set; }` — attrs: `[BsonRequired, BsonElement("sid")]`
- L126 _public property_ `public string NodeClass { get; set; }` — attrs: `[BsonRequired, BsonElement("n")]`
- L129 _public property_ `public string Version { get; set; }` — attrs: `[BsonRequired, BsonElement("v")]`
- L132 _public property_ `public float TimeoutMinutes { get; set; }` — attrs: `[BsonRequired, BsonElement("o")]`
- L135 _public property_ `public TemplateId JobTemplateId { get; set; }` — attrs: `[BsonRequired, BsonElement("jt")]`
- L138 _public property_ `public string JobStep { get; set; }` — attrs: `[BsonRequired, BsonElement("js")]`
- L141 _public property_ `public WorkflowId? WorkflowId { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("w")]`
- L144 _public property_ `public List<TestParamEntry>? Params { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("p")]`
- L145 _private* property_ `IReadOnlyList<ITestParamEntry>? ITestRecipeRef.Params => ...`
- L148 _public property_ `public DateTime LastSeenUtc { get; set; }` — attrs: `[BsonRequired, BsonElement("s")]`
- L150-155 _private ctor_ `private TestRecipeDocument()`
- L157-169 _public ctor_ `public TestRecipeDocument(TestId testId, StreamId streamId, TemplateId jobTemplate, string jobStep, string nodeClass, string version, float timeoutMinutes, WorkflowId? workflow = null)`
- L171-176 _public method_ `public IReadOnlyList<ITestParamEntry> UpdateParams(IReadOnlyDictionary<string, object> @params)`

#### class `HordeServer.Jobs.TestData.TestDataCollectionV2.TestTagDocument`  
`class TestTagDocument : ITestTagRef, ITestExpire`  
_private*; L182-204_
- inherits: `ITestTagRef, ITestExpire`
- desc: Test tag reference document
- L185 _public property_ `public TestTagId Id { get; set; }` — attrs: `[BsonRequired, BsonId]`
- L188 _public property_ `public string Name { get; set; }` — attrs: `[BsonRequired, BsonElement("n")]`
- L191 _public property_ `public DateTime LastSeenUtc { get; set; }` — attrs: `[BsonRequired, BsonElement("s")]`
- L193-196 _private ctor_ `private TestTagDocument()`
- L198-203 _public ctor_ `public TestTagDocument(string name)`

#### class `HordeServer.Jobs.TestData.TestDataCollectionV2.TestNameDocument`  
`class TestNameDocument : ITestNameRef, ITestExpire`  
_private*; L209-256_
- inherits: `ITestNameRef, ITestExpire`
- desc: Test name reference document
- L212 _public property_ `public TestId Id { get; set; }` — attrs: `[BsonRequired, BsonId]`
- L215 _public property_ `public string Name { get; set; }` — attrs: `[BsonRequired, BsonElement("n")]`
- L218 _public property_ `public string Key { get; set; }` — attrs: `[BsonRequired, BsonElement("k")]`
- L221 _public property_ `public string? Team { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("t")]`
- L224 _public property_ `public string? Intent { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("i")]`
- L227 _public property_ `public string? Harness { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("h")]`
- L230 _public property_ `public string? Profile { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("p")]`
- L233 _public property_ `public DateTime LastSeenUtc { get; set; }` — attrs: `[BsonRequired, BsonElement("s")]`
- L235-239 _private ctor_ `private TestNameDocument()`
- L241-247 _public ctor_ `public TestNameDocument(string key, string name)`
- L249-255 _public method_ `public void AddDescription(string? team, string? intent, string? harness, string? profile)`

#### class `HordeServer.Jobs.TestData.TestDataCollectionV2.TestPhaseDocument`  
`class TestPhaseDocument : ITestPhaseRef, ITestExpire`  
_private*; L261-292_
- inherits: `ITestPhaseRef, ITestExpire`
- desc: Test phase reference document
- L264 _public property_ `public TestPhaseId Id { get; set; }` — attrs: `[BsonRequired, BsonId]`
- L267 _public property_ `public TestId TestNameRef { get; set; }` — attrs: `[BsonRequired, BsonElement("tid")]`
- L270 _public property_ `public string Name { get; set; }` — attrs: `[BsonRequired, BsonElement("n")]`
- L273 _public property_ `public string Key { get; set; }` — attrs: `[BsonRequired, BsonElement("k")]`
- L276 _public property_ `public DateTime LastSeenUtc { get; set; }` — attrs: `[BsonRequired, BsonElement("s")]`
- L278-282 _private ctor_ `private TestPhaseDocument()`
- L284-291 _public ctor_ `public TestPhaseDocument(TestId testId, string key, string name)`

#### class `HordeServer.Jobs.TestData.TestDataCollectionV2.TestSessionStreamDocument`  
`class TestSessionStreamDocument : ITestSessionStream`  
_private*; L297-327_
- inherits: `ITestSessionStream`
- desc: Stores the tests running in a stream
- L300 _public property_ `public ObjectId Id { get; set; }` — attrs: `[BsonRequired, BsonId]`
- L303 _public property_ `public StreamId StreamId { get; set; }` — attrs: `[BsonRequired, BsonElement("sid")]`
- L306 _public property_ `public List<TestId> Tests { get; set; }` — attrs: `[BsonRequired, BsonElement("t")]`
- L307 _private* property_ `IReadOnlyList<TestId> ITestSessionStream.Tests => ...`
- L310 _public property_ `public List<TestMetaId> Metadata { get; set; }` — attrs: `[BsonRequired, BsonElement("m")]`
- L311 _private* property_ `IReadOnlyList<TestMetaId> ITestSessionStream.Metadata => ...`
- L314 _public property_ `public List<TestTagId> Tags { get; set; }` — attrs: `[BsonRequired, BsonElement("tg")]`
- L315 _private* property_ `IReadOnlyList<TestTagId> ITestSessionStream.Tags => ...`
- L317-320 _private ctor_ `private TestSessionStreamDocument()`
- L322-326 _public ctor_ `public TestSessionStreamDocument(StreamId streamId)`

#### class `HordeServer.Jobs.TestData.TestDataCollectionV2.TestErrorfingerprintEntry`  
`class TestErrorfingerprintEntry : IErrorFingerprintEntry`  
_private*; L332-352_
- inherits: `IErrorFingerprintEntry`
- desc: Store the error fingerprint entries
- L336 _public property_ `public string Key { get; set; }` — attrs: `[BsonRequired, BsonElement("k")]`
- L339 _public property_ `public IReadOnlyList<string> Phases { get; set; }` — attrs: `[BsonRequired, BsonElement("p")]`
- L341-345 _private ctor_ `private TestErrorfingerprintEntry()`
- L347-351 _public ctor_ `public TestErrorfingerprintEntry(string key, IReadOnlyList<string> phases)`

#### class `HordeServer.Jobs.TestData.TestDataCollectionV2.TestSessionDocument`  
`class TestSessionDocument : ITestSession`  
_private*; L357-436_
- inherits: `ITestSession`
- desc: Store the test session overall result
- L360 _public property_ `public TestSessionId Id { get; set; }` — attrs: `[BsonRequired, BsonId]`
- L363 _public property_ `public StreamId StreamId { get; set; }` — attrs: `[BsonRequired, BsonElement("sid")]`
- L366 _public property_ `public TestMetaId Metadata { get; set; }` — attrs: `[BsonRequired, BsonElement("m")]`
- L369 _public property_ `public TestRecipeId? Recipe { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("r")]`
- L372 _public property_ `public IReadOnlyList<TestTagId>? Tags { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("tg")]`
- L375 _public property_ `public List<TestErrorfingerprintEntry>? ErrorFingerprints { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("ef")]`
- L376 _private* property_ `IReadOnlyList<IErrorFingerprintEntry>? ITestSession.ErrorFingerprints => ...`
- L379 _public property_ `public ObjectId TestDataId { get; set; }` — attrs: `[BsonRequired, BsonElement("did")]`
- L381-385 _public property_ `public CommitIdWithOrder BuildCommitId { get; set; }`
- L388 _public property_ `public string? BuildCommitName { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("bcn")]`
- L391 _public property_ `public int BuildCommitOrder { get; set; }` — attrs: `[BsonRequired, BsonElement("bcl")]`
- L394 _public property_ `public TimeSpan Duration { get; set; }` — attrs: `[BsonRequired, BsonElement("d")]`
- L397 _public property_ `public DateTime StartDateTime { get; set; }` — attrs: `[BsonRequired, BsonElement("s")]`
- L400 _public property_ `public TestId NameRef { get; set; }` — attrs: `[BsonRequired, BsonElement("tid")]`
- L403 _public property_ `public TestOutcome Outcome { get; set; }` — attrs: `[BsonRequired, BsonElement("o")]`
- L406 _public property_ `public int PhasesTotalCount { get; set; }` — attrs: `[BsonRequired, BsonElement("ptc")]`
- L409 _public property_ `public int PhasesSucceededCount { get; set; }` — attrs: `[BsonRequired, BsonElement("psc")]`
- L412 _public property_ `public int PhasesUndefinedCount { get; set; }` — attrs: `[BsonRequired, BsonElement("puc")]`
- L415 _public property_ `public int PhasesFailedCount { get; set; }` — attrs: `[BsonRequired, BsonElement("pfc")]`
- L418 _public property_ `public JobId JobId { get; set; }` — attrs: `[BsonRequired, BsonElement("jid")]`
- L421 _public property_ `public JobStepId StepId { get; set; }` — attrs: `[BsonRequired, BsonElement("sjid")]`
- L423-426 _private ctor_ `private TestSessionDocument()`
- L428-435 _public ctor_ `public TestSessionDocument(StreamId streamId, ObjectId testDataId, TestId testId, TestMetaId metaId)`

#### class `HordeServer.Jobs.TestData.TestDataCollectionV2.TestPhaseSessionDocument`  
`class TestPhaseSessionDocument : ITestPhaseSession`  
_private*; L441-510_
- inherits: `ITestPhaseSession`
- desc: Store the test phase result
- L444 _public property_ `public TestPhaseSessionId Id { get; set; }` — attrs: `[BsonRequired, BsonId]`
- L447 _public property_ `public TestPhaseId PhaseRef { get; set; }` — attrs: `[BsonRequired, BsonElement("tid")]`
- L450 _public property_ `public TestSessionId SessionId { get; set; }` — attrs: `[BsonRequired, BsonElement("tsid")]`
- L453 _public property_ `public StreamId StreamId { get; set; }` — attrs: `[BsonRequired, BsonElement("sid")]`
- L456 _public property_ `public TestMetaId Metadata { get; set; }` — attrs: `[BsonRequired, BsonElement("m")]`
- L458-462 _public property_ `public CommitIdWithOrder BuildCommitId { get; set; }`
- L465 _public property_ `public string? BuildCommitName { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("bcn")]`
- L468 _public property_ `public int BuildCommitOrder { get; set; }` — attrs: `[BsonRequired, BsonElement("bcl")]`
- L471 _public property_ `public TimeSpan Duration { get; set; }` — attrs: `[BsonRequired, BsonElement("d")]`
- L474 _public property_ `public DateTime StartDateTime { get; set; }` — attrs: `[BsonRequired, BsonElement("s")]`
- L477 _public property_ `public TestPhaseOutcome Outcome { get; set; }` — attrs: `[BsonRequired, BsonElement("o")]`
- L480 _public property_ `public string? EventStreamPath { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("esp")]`
- L483 _public property_ `public bool? HasWarning { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("hw")]`
- L486 _public property_ `public string? ErrorFingerprint { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("ef")]`
- L489 _public property_ `public IReadOnlyList<TestTagId>? Tags { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("tg")]`
- L492 _public property_ `public JobId JobId { get; set; }` — attrs: `[BsonRequired, BsonElement("jid")]`
- L495 _public property_ `public JobStepId StepId { get; set; }` — attrs: `[BsonRequired, BsonElement("sjid")]`
- L497-500 _private ctor_ `private TestPhaseSessionDocument()`
- L502-509 _public ctor_ `public TestPhaseSessionDocument(StreamId streamId, TestSessionId sessionId, TestPhaseId phaseId, TestMetaId metaId)`

#### class `HordeServer.Jobs.TestData.TestDataCollectionV2.TestHealthReportDocument`  
`class TestHealthReportDocument : ITestHealthReport`  
_private*; L515-566_
- inherits: `ITestHealthReport`
- desc: Store test health report info
- L518 _public property_ `public ObjectId Id { get; set; }` — attrs: `[BsonRequired, BsonId]`
- L521 _public property_ `public TestId TestId { get; set; }` — attrs: `[BsonRequired, BsonElement("tid")]`
- L524 _public property_ `public string TestName { get; set; }` — attrs: `[BsonRequired, BsonElement("tn")]`
- L527 _public property_ `public StreamId StreamId { get; set; }` — attrs: `[BsonRequired, BsonElement("sid")]`
- L530 _public property_ `public DateTime LastUpdateDateUtc { get; set; }` — attrs: `[BsonRequired, BsonElement("lud")]`
- L533 _public property_ `public bool IsHealthy { get; set; }` — attrs: `[BsonRequired, BsonElement("h")]`
- L536 _public property_ `public string State { get; set; }` — attrs: `[BsonRequired, BsonElement("s")]`
- L539 _public property_ `public string? PreviousState { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("ps")]`
- L542 _public property_ `public int SuccessRate { get; set; }` — attrs: `[BsonRequired, BsonElement("sr")]`
- L545 _public property_ `public int FailureRate { get; set; }` — attrs: `[BsonRequired, BsonElement("fr")]`
- L548 _public property_ `public int CatastrophicFailureRate { get; set; }` — attrs: `[BsonRequired, BsonElement("cr")]`
- L551 _public property_ `public int RedundantErrorRate { get; set; }` — attrs: `[BsonRequired, BsonElement("rer")]`
- L554 _public property_ `public DateTime? NotificationLastDateUtc { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("nld")]`
- L556 _private ctor_ `private TestHealthReportDocument()`
- L558-565 _public ctor_ `public TestHealthReportDocument(TestId testId, string testName, StreamId streamId)`

#### class `HordeServer.Jobs.TestData.TestDataCollectionV2.TestNotificationSettingsEntry`  
`class TestNotificationSettingsEntry : ITestNotificationSettings`  
_private*; L571-578_
- inherits: `ITestNotificationSettings`
- desc: Store test notification settings for a stream
- L574 _public property_ `public StreamId Stream { get; set; }` — attrs: `[BsonRequired, BsonElement("s")]`
- L577 _public property_ `public WorkflowId Workflow { get; set; }` — attrs: `[BsonRequired, BsonElement("w")]`

#### class `HordeServer.Jobs.TestData.TestDataCollectionV2.TestAuditDocument`  
`class TestAuditDocument : ITestAudit`  
_private*; L583-666_
- inherits: `ITestAudit`
- desc: Store a test audit entry
- L586 _public property_ `public TestAuditId Id { get; set; }` — attrs: `[BsonRequired, BsonId]`
- L589 _public property_ `public TestId TestId { get; set; }` — attrs: `[BsonRequired, BsonElement("tid")]`
- L592 _public property_ `public DateTime UserInputDate { get; set; }` — attrs: `[BsonRequired, BsonElement("ui")]`
- L595 _public property_ `public bool Archived { get; set; }` — attrs: `[BsonRequired, BsonElement("a")]`
- L598 _public property_ `public UserId UserId { get; set; }` — attrs: `[BsonRequired, BsonElement("uid")]`
- L601 _public property_ `public bool EnableSchedule { get; set; }` — attrs: `[BsonRequired, BsonElement("e")]`
- L604 _public property_ `public DateTime? LastAuditDate { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("la")]`
- L607 _public property_ `public bool? IsUnderAudit { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("ua")]`
- L610 _public property_ `public UserId? Owner { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("o")]`
- L613 _public property_ `public IReadOnlyList<UserId>? Customers { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("c")]`
- L616 _public property_ `public IReadOnlyList<TestNotificationSettingsEntry>? Notifications { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("ns")]`
- L617 _private* property_ `IReadOnlyList<ITestNotificationSettings>? ITestAudit.Notifications => ...`
- L620 _public property_ `public string? Team { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("t")]`
- L623 _public property_ `public string? Harness { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("h")]`
- L626 _public property_ `public string? Intent { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("i")]`
- L629 _public property_ `public string? Profile { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("p")]`
- L632 _public property_ `public string? Notes { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("n")]`
- L634 _private ctor_ `private TestAuditDocument()`
- L636-644 _public ctor_ `public TestAuditDocument(UserId userId, TestId testId)`
- L646-665 _public method_ `public void UpdateOptions(TestAuditOptions options)`

#### class `HordeServer.Jobs.TestData.TestDataCollectionV2.TestDataDocument`  
`class TestDataDocument : ITestData`  
_private*; L671-721_
- inherits: `ITestData`
- desc: Information about a test data document
- L673 _public property_ `public ObjectId Id { get; set; }`
- L674 _public property_ `public StreamId StreamId { get; set; }`
- L675 _public property_ `public TemplateId TemplateRefId { get; set; }`
- L676 _public property_ `public JobId JobId { get; set; }`
- L677 _public property_ `public JobStepId StepId { get; set; }`
- L680-684 _public property_ `public CommitIdWithOrder CommitId { get; set; }` — attrs: `[BsonIgnore]`
- L686 _public property_ `public string? CommitName { get; set; }`
- L689 _public property_ `public int CommitOrder { get; set; }` — attrs: `[BsonElement("Change")]`
- L692-696 _public property_ `public CommitId? PreflightCommitId { get; set; }` — attrs: `[BsonIgnore]`
- L698 _public property_ `public string? PreflightCommitName { get; set; }`
- L700 _public property_ `public string Key { get; set; }`
- L701 _public property_ `public BsonDocument Data { get; set; }`
- L703-707 _private ctor_ `private TestDataDocument()`
- L709-720 _public ctor_ `public TestDataDocument(IJob job, IJobStep jobStep, string key, BsonDocument value)`

#### class `HordeServer.Jobs.TestData.TestDataCollectionV2.AutomatedTestSessionData`  
`class AutomatedTestSessionData`  
_private*; L1055-1135_
- L1124 _public property_ `public TestSessionSummary? Summary { get; set; }` — attrs: `[BsonRequired, BsonElement("summary")]`
- L1126 _public property_ `public List<TestPhase> Phases { get; set; }` — attrs: `[BsonRequired, BsonElement("phases")]`
- L1128 _public property_ `public Dictionary<string, string> Metadata { get; set; }` — attrs: `[BsonRequired, BsonElement("metadata")]`
- L1130 _public property_ `public List<string>? Tags { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("tags")]`
- L1132 _public property_ `public TestDescription? Description { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("description")]`
- L1134 _public property_ `public TestRecipe? Recipe { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("recipe")]`

#### class `HordeServer.Jobs.TestData.TestDataCollectionV2.AutomatedTestSessionData.TestSessionSummary`  
`public class TestSessionSummary`  
_public; L1057-1075_
- L1060 _public property_ `public string TestName { get; set; }` — attrs: `[BsonRequired, BsonElement("testName")]`
- L1062 _public property_ `public string? DateTime { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("dateTime")]`
- L1064 _public property_ `public double TimeElapseSec { get; set; }` — attrs: `[BsonRequired, BsonElement("timeElapseSec")]`
- L1066 _public property_ `public string? CommandLine { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("commandline")]`
- L1068 _public property_ `public int PhasesTotalCount { get; set; }` — attrs: `[BsonRequired, BsonElement("phasesTotalCount")]`
- L1070 _public property_ `public int PhasesSucceededCount { get; set; }` — attrs: `[BsonRequired, BsonElement("phasesSucceededCount")]`
- L1072 _public property_ `public int PhasesUndefinedCount { get; set; }` — attrs: `[BsonRequired, BsonElement("phasesUndefinedCount")]`
- L1074 _public property_ `public int PhasesFailedCount { get; set; }` — attrs: `[BsonRequired, BsonElement("phasesFailedCount")]`

#### class `HordeServer.Jobs.TestData.TestDataCollectionV2.AutomatedTestSessionData.TestPhase`  
`public class TestPhase`  
_public; L1077-1097_
- L1080 _public property_ `public string Name { get; set; }` — attrs: `[BsonRequired, BsonElement("name")]`
- L1082 _public property_ `public string Key { get; set; }` — attrs: `[BsonRequired, BsonElement("key")]`
- L1084 _public property_ `public string? DateTime { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("dateTime")]`
- L1086 _public property_ `public double TimeElapseSec { get; set; }` — attrs: `[BsonRequired, BsonElement("timeElapseSec")]`
- L1088 _public property_ `public TestPhaseOutcome Outcome { get; set; }` — attrs: `[BsonRequired, BsonElement("outcome")]`
- L1090 _public property_ `public string? ErrorFingerprint { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("errorFingerprint")]`
- L1092 _public property_ `public bool? HasWarning { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("hasWarning")]`
- L1094 _public property_ `public string? EventStreamPath { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("eventStreamPath")]`
- L1096 _public property_ `public List<string>? Tags { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("tags")]`

#### class `HordeServer.Jobs.TestData.TestDataCollectionV2.AutomatedTestSessionData.TestDescription`  
`public class TestDescription`  
_public; L1099-1109_
- L1102 _public property_ `public string? Team { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("team")]`
- L1104 _public property_ `public string? Intent { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("intent")]`
- L1106 _public property_ `public string? Profile { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("profile")]`
- L1108 _public property_ `public string? Harness { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("harness")]`

#### class `HordeServer.Jobs.TestData.TestDataCollectionV2.AutomatedTestSessionData.TestRecipe`  
`public class TestRecipe`  
_public; L1111-1121_
- L1114 _public property_ `public string NodeClass { get; set; }` — attrs: `[BsonRequired, BsonElement("nodeClass")]`
- L1116 _public property_ `public string Version { get; set; }` — attrs: `[BsonRequired, BsonElement("version")]`
- L1118 _public property_ `public float? TimeoutMinutes { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("timeoutMinutes")]`
- L1120 _public property_ `public Dictionary<string, object>? Params { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("params")]`

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/TestData/TestDataController.cs` (HordeServer.Build)


#### class `HordeServer.Jobs.TestData.TestDataController`  
`public class TestDataController : ControllerBase`  
_public; L30-1186_
- attrs: `[ApiController] [Authorize] [Route("[controller]")]`
- inherits: `ControllerBase`
- desc: Controller for the /api/v1/testdata endpoint
- L35 _private field_ `private readonly JobService _jobService` — Collection of job documents
- L40 _private field_ `private readonly ITestDataCollection _testDataCollection` — Collection of test data documents
- L42 _private field_ `private readonly IUserCollection _userCollection`
- L44 _private* field_ `readonly TestDataService _testDataService`
- L46 _private* field_ `readonly IOptionsSnapshot<BuildConfig> _buildConfig`
- L51-58 _public ctor_ `public TestDataController(TestDataService testDataService, JobService jobService, ITestDataCollection testDataCollection, IOptionsSnapshot<BuildConfig> buildConfig, IUserCollection userCollection)` — Constructor
- L71-89 _public method_ `public async Task<ActionResult<List<GetTestMetaResponse>>> GetTestMetaAsync( [FromQuery(Name = "project")] string[]? projects = null, [FromQuery(Name = "platform")] string[]? platforms = null, [FromQuery(Name = "target")] string[]? targets = null, [FromQuery(Name = "configuration")] string[]? configurations = null)` — attrs: `[HttpGet] [Route("/api/v2/testdata/metadata")] [ProducesResponseType(typeof(List<GetTestMetaResponse>), 200)]` — Get metadata
- L99-117 _public method_ `public async Task<ActionResult<List<GetTestDataDetailsResponse>>> GetTestDetailsAsync([FromQuery(Name = "id")] string[] ids)` — attrs: `[HttpGet] [Route("/api/v2/testdata/details")] [ProducesResponseType(typeof(List<GetTestDataDetailsResponse>), 200)]` — Get test details from provided refs
- L127-141 _public method_ `public async Task<ActionResult<List<GetTestResponse>>> GetTestsAsync([FromBody] GetTestsRequest request)` — attrs: `[HttpPost] [Route("/api/v2/testdata/tests")] [ProducesResponseType(typeof(List<GetTestResponse>), 200)]` — Get test details from provided refs
- L151-292 _public method_ `public async Task<ActionResult<List<GetTestStreamResponse>>> GetTestStreamsAsync([FromQuery(Name = "Id")] string[] streamIds)` — attrs: `[HttpGet] [Route("/api/v2/testdata/streams")] [ProducesResponseType(typeof(List<GetTestStreamResponse>), 200)]` — Get stream test data for the provided ids
- L309-361 _public method_ `public async Task<ActionResult<List<GetTestDataRefResponse>>> GetTestDataRefAsync( [FromQuery(Name = "Id")] string[] streamIds, [FromQuery(Name = "Mid")] string[] metaIds, [FromQuery(Name = "Tid")] string[]? testIds = null, [FromQuery(Name = "Sid")] string[]? suiteIds = null, [FromQuery] DateTimeOffset? minCreateTime = null, [FromQuery] DateTimeOffset? maxCreateTime = null, [FromQuery] CommitId? minChange = null, [FromQuery] CommitId? maxChange = null)` — attrs: `[HttpGet] [Route("/api/v2/testdata/refs")] [ProducesResponseType(typeof(List<GetTestDataRefResponse>), 200)]` — Gets test data refs
- L369-391 _public method_ `public async Task<ActionResult<CreateTestDataResponse>> CreateAsync(CreateTestDataRequest request)` — attrs: `[HttpPost] [Route("/api/v1/testdata")]` — Creates a new TestData document
- L410-441 _public method_ `public async Task<ActionResult<List<object>>> FindTestDataAsync([FromQuery] string? streamId = null, [FromQuery] CommitId? minChange = null, [FromQuery] CommitId? maxChange = null, JobId? jobId = null, JobStepId? jobStepId = null, string? key = null, int index = 0, int count = 10, PropertyFilter? filter = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/testdata")] [ProducesResponseType(typeof(List<GetTestDataResponse>), 200)]` — Searches for test data that matches a set of criteria
- L453-476 _public method_ `public async Task<ActionResult<object>> GetTestDataAsync(string testDataId, [FromQuery] PropertyFilter? filter = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/testdata/{testDataId}")] [ProducesResponseType(typeof(GetTestDataResponse), 200)]` — Retrieve information about a specific issue
- L488-504 _public method_ `public async Task<ActionResult<List<GetJobStepTestDataIDResponse>>> GetJobStepTestDataV2Async([FromQuery] string jobId, [FromQuery] string? stepId = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v3/testdata/")] [ProducesResponseType(typeof(List<GetJobStepTestDataIDResponse>), 200)]` — Retrieve list of testdata ids run within a job or job step
- L516-540 _public method_ `public async Task<ActionResult<object>> GetTestDataV2Async(string testDataId, [FromQuery] PropertyFilter? filter = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v3/testdata/{testDataId}")] [ProducesResponseType(typeof(GetTestDataResponse), 200)]` — Retrieve information about a specific issue
- L551-640 _public method_ `public async Task<ActionResult<List<GetTestSessionStreamResponse>>> GetTestStreamsV2Async([FromBody] GetStreamTestsRequest request, CancellationToken cancellationToken = default)` — attrs: `[HttpPost] [Route("/api/v3/testdata/streams")] [ProducesResponseType(typeof(List<GetTestSessionStreamResponse>), 200)]` — Get stream test data for the provided ids
- L651-667 _public method_ `public async Task<ActionResult<List<GetTestNameResponse>>> GetTestNameRefV2Async([FromBody] GetTestsRequest request, CancellationToken cancellationToken = default)` — attrs: `[HttpPost] [Route("/api/v3/testdata/tests")] [ProducesResponseType(typeof(List<GetTestNameResponse>), 200)]` — Get test names from provided ids
- L678-689 _public method_ `public async Task<ActionResult<List<GetTestMetadataResponse>>> GetTestMetadataV2Async([FromBody] GetMetadataRequest request, CancellationToken cancellationToken = default)` — attrs: `[HttpPost] [Route("/api/v3/testdata/metadata")] [ProducesResponseType(typeof(List<GetTestMetadataResponse>), 200)]` — Get test metadata from provided ids
- L700-711 _public method_ `public async Task<ActionResult<List<GetTestTagResponse>>> GetTestTagRefV2Async([FromBody] GetTestTagRequest request, CancellationToken cancellationToken = default)` — attrs: `[HttpPost] [Route("/api/v3/testdata/tags")] [ProducesResponseType(typeof(List<GetTestTagResponse>), 200)]` — Get test tags from provided ids
- L722-745 _public method_ `public async Task<ActionResult<List<GetTestRecipeResponse>>> GetTestRecipeRefV2Async([FromBody] GetTestRecipesRequest request, CancellationToken cancellationToken = default)` — attrs: `[HttpPost] [Route("/api/v3/testdata/recipes")] [ProducesResponseType(typeof(List<GetTestRecipeResponse>), 200)]` — Get test recipes from provided ids
- L756-783 _public method_ `public async Task<ActionResult<List<GetTestPhaseResponse>>> GetTestPhaseRefFromTestV2Async([FromBody] GetTestPhasesRequest request, CancellationToken cancellationToken = default)` — attrs: `[HttpPost] [Route("/api/v3/testdata/phases")] [ProducesResponseType(typeof(List<GetTestPhaseResponse>), 200)]` — Get test phases from provide test keys and refs
- L798-861 _public method_ `public async Task<ActionResult<List<GetTestSessionResponse>>> GetTestSessionsV2Async( [FromBody] GetTestSessionsRequest request, [FromQuery] DateTimeOffset? minCreateTime = null, [FromQuery] DateTimeOffset? maxCreateTime = null, [FromQuery] CommitId? minChange = null, [FromQuery] CommitId? maxChange = null, CancellationToken cancellationToken = default)` — attrs: `[HttpPost] [Route("/api/v3/testdata/session/tests")] [ProducesResponseType(typeof(List<GetTestSessionResponse>), 200)]` — Gets test data sessions
- L876-930 _public method_ `public async Task<ActionResult<List<GetTestPhaseSessionResponse>>> GetTestPhaseSessionsV2Async( [FromBody] GetPhaseSessionsRequest request, [FromQuery] DateTimeOffset? minCreateTime = null, [FromQuery] DateTimeOffset? maxCreateTime = null, [FromQuery] CommitId? minChange = null, [FromQuery] CommitId? maxChange = null, CancellationToken cancellationToken = default)` — attrs: `[HttpPost] [Route("/api/v3/testdata/session/phases")] [ProducesResponseType(typeof(List<GetTestPhaseSessionResponse>), 200)]` — Gets test data phase sessions
- L941-993 _public method_ `public async Task<ActionResult<GetTestAuditResponse>> AddTestAuditV2Async([FromBody] AddTestAuditRequest request, CancellationToken cancellationToken = default)` — attrs: `[HttpPost] [Route("/api/v3/testdata/audit/post")] [ProducesResponseType(typeof(GetTestAuditResponse), 200)]` — Post a test audit
- L995-1061 _private method_ `private async Task LogAuditChangesAsync(UserId userId, TestId testId, TestAuditOptions options, ITestAudit? prevAudit, CancellationToken cancellationToken = default)`
- L1073-1083 _public method_ `public async Task<ActionResult<List<GetTestAuditResponse>>> GetTestAuditsV2Async( [FromBody] GetTestAuditRequest request, [FromQuery] DateTimeOffset? minCreateTime = null, CancellationToken cancellationToken = default)` — attrs: `[HttpPost] [Route("/api/v3/testdata/audit/history")] [ProducesResponseType(typeof(List<GetTestAuditResponse>), 200)]` — Get test audit history
- L1085-1106 _private method_ `private GetTestAuditResponse GetNewTestAutditResponse(ITestAudit audit)`
- L1120-1135 _public method_ `public async Task<ActionResult> GetAuditLogHistoryAsync(string testId, [FromQuery] DateTime? minTime = null, [FromQuery] DateTime? maxTime = null, [FromQuery] int index = 0, [FromQuery] int count = 50, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v3/testdata/audit/log/{testId}")]` — Retrieve historical information about a specific test audit
- L1146-1185 _public method_ `public async Task<ActionResult<List<GetTestHealthReportResponse>>> GetTestHealthReportsV2Async([FromBody] GetTestHealthReportRequest request, CancellationToken cancellationToken = default)` — attrs: `[HttpPost] [Route("/api/v3/testdata/health/reports")] [ProducesResponseType(typeof(List<GetTestHealthReportResponse>), 200)]` — Get test health reports

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/TestData/TestDataService.cs` (HordeServer.Build)


#### class `HordeServer.Jobs.TestData.TestDataService`  
`public sealed class TestDataService : IHostedService, IAsyncDisposable`  
_public; L19-380_
- inherits: `IHostedService, IAsyncDisposable`
- desc: TestData management service
- L22 _private* field_ `readonly ITestDataCollection _testData`
- L23 _private* field_ `readonly ITestDataCollectionV2 _testDataV2`
- L24 _private* field_ `readonly IOptionsMonitor<BuildServerConfig> _settings`
- L25 _private* field_ `readonly ITicker _ticker`
- L26 _private* field_ `readonly ILogger<TestDataService> _logger`
- L31-38 _public ctor_ `public TestDataService(ITestDataCollection testData, ITestDataCollectionV2 testDataV2, IOptionsMonitor<BuildServerConfig> settings, IClock clock, ILogger<TestDataService> logger)` — TestData service constructor
- L41-53 _public method_ `public async Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L56-59 _public method_ `public async Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L62-65 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L70-91 _private* method_ `async ValueTask TickAsync(CancellationToken stoppingToken)` — Ticks service
- L93-96 _internal method_ `internal async Task TickForTestingAsync()`
- L104-107 _public method_ `public async Task<IReadOnlyList<ITestStream>> FindTestStreamsAsync(StreamId[] streamIds, CancellationToken cancellationToken = default)` — Find test streams
- L115-118 _public method_ `public async Task<IReadOnlyList<ITest>> FindTestsAsync(TestId[] testIds, CancellationToken cancellationToken = default)` — Find tests
- L126-129 _public method_ `public async Task<IReadOnlyList<ITestSuite>> FindTestSuitesAsync(TestSuiteId[] suiteIds, CancellationToken cancellationToken = default)` — Find test suites
- L143-146 _public method_ `public async Task<IReadOnlyList<ITestMeta>> FindTestMetaAsync(string[]? projectNames = null, string[]? platforms = null, string[]? configurations = null, string[]? buildTargets = null, string? rhi = null, string? variation = null, TestMetaId[]? metaIds = null, CancellationToken cancellationToken = default)` — Find test meta data
- L161-167 _public method_ `public async Task<IReadOnlyList<ITestDataRef>> FindTestRefsAsync(StreamId[] streamIds, TestMetaId[] metaIds, string[]? testIds = null, string[]? suiteIds = null, DateTime? minCreateTime = null, DateTime? maxCreateTime = null, CommitId? minCommitId = null, CommitId? maxCommitId = null, CancellationToken cancellationToken = default)` — Gets test data refs
- L175-178 _public method_ `public async Task<IReadOnlyList<ITestDataDetails>> FindTestDetailsAsync(TestRefId[] ids, CancellationToken cancellationToken = default)` — Find test details
- L187-190 _public method_ `public async Task<IReadOnlyList<ITestData>> GetJobStepTestDataV2Async(JobId jobId, JobStepId? stepId = null, CancellationToken cancellationToken = default)` — Gets testdata ids run within a job step
- L198-201 _public method_ `public async Task<ITestData?> GetTestDataV2Async(ObjectId id, CancellationToken cancellationToken)` — Gets a testdata by ID
- L209-212 _public method_ `public async Task<IReadOnlyList<ITestSessionStream>> FindTestSessionStreamsV2Async(StreamId[] streamIds, CancellationToken cancellationToken = default)` — Gets the test sessions running in provided streams
- L226-229 _public method_ `public async Task<IReadOnlyList<ITestSession>> FindTestSessionsV2Async(StreamId[] streamIds, TestId[]? testIds = null, TestMetaId[]? metaIds = null, DateTime? minCreateTime = null, DateTime? maxCreateTime = null, CommitId? minCommitId = null, CommitId? maxCommitId = null, CancellationToken cancellationToken = default)` — Find test sessions
- L238-241 _public method_ `public async Task<IReadOnlyList<ITestNameRef>> FindTestNameRefsV2Async(TestId[]? testIds = null, string[]? keys = null, CancellationToken cancellationToken = default)` — Find test name references
- L250-253 _public method_ `public async Task<IReadOnlyList<ITestMetaRef>> FindTestMetaV2Async(TestMetaId[]? metaIds = null, IReadOnlyDictionary<string, string>? keyValues = null, CancellationToken cancellationToken = default)` — Find test metadata set
- L262-265 _public method_ `public async Task<IReadOnlyList<ITestPhaseRef>> FindTestPhasesV2Async(TestId[] testIds, string[]? keys = null, CancellationToken cancellationToken = default)` — Find test phase references associated with a set of tests
- L274-277 _public method_ `public async Task<IReadOnlyList<ITestTagRef>> FindTestTagsV2Async(TestTagId[]? tagIds, string[]? names = null, CancellationToken cancellationToken = default)` — Find test tag references
- L287-290 _public method_ `public async Task<IReadOnlyList<ITestRecipeRef>> FindTestRecipesV2Async(TestRecipeId[]? recipeIds = null, TestId[]? testIds = null, StreamId[]? streamIds = null, CancellationToken cancellationToken = default)` — Find test recipe references
- L303-306 _public method_ `public async Task<IReadOnlyList<ITestPhaseSession>> FindTestPhaseSessionsV2Async(StreamId[] streamIds, TestPhaseId[] phaseIds, DateTime? minCreateTime = null, DateTime? maxCreateTime = null, CommitId? minCommitId = null, CommitId? maxCommitId = null, CancellationToken cancellationToken = default)` — Find test phase sessions from a set of test phases
- L316-319 _public method_ `public async Task<ITestAudit> AddTestAuditAsync(UserId userId, TestId testId, TestAuditOptions options, CancellationToken cancellationToken = default)` — Add a test audit entry
- L328-331 _public method_ `public async Task<IReadOnlyList<ITestAudit>> FindTestAuditsV2Async(TestId[] testIds, DateTime? minCreateTime = null, CancellationToken cancellationToken = default)` — Find audit associated with the tests
- L342-345 _public method_ `public async Task<ITestHealthReport> AddOrUpdateTestHealthReportV2Async(TestId testId, StreamId streamId, string testName, ComputedTestHealth testHealth, CancellationToken cancellationToken = default)` — Add or update test health report
- L352-355 _public method_ `public IAuditLogChannel<TestId> GetTestAuditLogger(TestId testId)` — Get the logger for the specified test id
- L364-367 _public method_ `public async Task<IReadOnlyList<ITestHealthReport>> FindTestHealthReportsV2Async(StreamId[] streamIds, TestId[]? testIds, CancellationToken cancellationToken = default)` — Find Test health report associated with stream and test ids
- L376-379 _public method_ `public async Task UpdateTestHealthReportNotificationDateAsync(ObjectId reportId, bool resetDate, CancellationToken cancellationToken = default)` — Update test health report notification information

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/TestData/TestHealthService.cs` (HordeServer.Build)


#### class `HordeServer.Jobs.TestData.TestHealthReportState`  
`class TestHealthReportState : SingletonBase`  
_internal*; L20-23_
- attrs: `[SingletonDocument("test-health-report-state")]`
- inherits: `SingletonBase`
- L22 _public property_ `public DateTime ReportTime { get; set; }`

#### enum `HordeServer.Jobs.TestData.TestHealthState`  
`enum TestHealthState`  
_internal*; L25-32_
- L27 _public* enumerator_ `Healthy = 5`
- L28 _public* enumerator_ `Fair = 4`
- L29 _public* enumerator_ `Unstable = 3`
- L30 _public* enumerator_ `Bad = 2`
- L31 _public* enumerator_ `Broken = 1`

#### class `HordeServer.Jobs.TestData.TestHealthService`  
`public sealed class TestHealthService : IHostedService, IAsyncDisposable`  
_public; L37-328_
- inherits: `IHostedService, IAsyncDisposable`
- desc: Test Health Service
- L39 _private* field_ `readonly ILogger<TestHealthService> _logger`
- L40 _private* field_ `readonly Tracer _tracer`
- L41 _private* field_ `readonly ITicker _ticker`
- L42 _private* field_ `readonly IClock _clock`
- L43 _private* field_ `readonly ITestDataCollectionV2 _testData`
- L44 _private* field_ `readonly SingletonDocument<TestHealthReportState> _state`
- L45 _private* field_ `readonly IOptions<BuildServerConfig> _staticBuildConfig`
- L46 _private* field_ `readonly IOptions<BuildConfig> _buildConfig`
- L47 _private* field_ `readonly INotificationService _notificationService`
- L49 _private* field_ `readonly int _reportIntervalMinutes = 12 * 60`
- L50 _private field_ `private bool _forceReport = false`
- L63-74 _public ctor_ `public TestHealthService(IMongoService mongoService, ITestDataCollectionV2 testData, INotificationService notificationService, IClock clock, ILogger<TestHealthService> logger, Tracer tracer, IOptions<BuildServerConfig> staticBuildConfig, IOptions<BuildConfig> buildConfig)` — Test Health Service constructor
- L77-80 _public method_ `public async Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L83-86 _public method_ `public async Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L89-92 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L94-98 _internal method_ `internal async Task TickForTestingAsync(bool bForceReport = false)`
- L103-231 _private* method_ `async ValueTask TickAsync(CancellationToken cancellationToken)` — Ticks service
- L238-306 _private method_ `private static ComputedTestHealth? ComputeHealthHeuristic(List<ITestSession> history)` — Compute Health Heuristic
- L308-327 _private method_ `private static string[]? GetAuditAttachedUsers(ITestAudit testAudit)`

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/TestData/TestId.cs` (HordeServer.Build)


#### record struct `HordeServer.Jobs.TestData.TestId`  
`public record struct TestId(ObjectId Id)`  
_public; L17-49_
- attrs: `[JsonSchemaString] [TypeConverter(typeof(ObjectIdTypeConverter<TestId, TestIdConverter>))] [ObjectIdConverter(typeof(TestIdConverter))]`
- desc: Identifier for a session
- L22 _public property_ `public static TestId Empty { get; }` — Default empty value for session id
- L27 _public method_ `public static TestId GenerateNewId()` — Creates a new TestId
- L30 _public method_ `public static TestId Parse(string text)` — (inheritdoc)
- L33-45 _public method_ `public static bool TryParse(string text, out TestId id)` — (inheritdoc)
- L48 _public method_ `public override string ToString()` — (inheritdoc)

#### class `HordeServer.Jobs.TestData.TestIdConverter`  
`class TestIdConverter : ObjectIdConverter<TestId>`  
_internal*; L54-61_
- inherits: `ObjectIdConverter<TestId>`
- desc: Converter to and from ObjectId instances.
- L57 _public method_ `public override TestId FromObjectId(ObjectId id)` — (inheritdoc)
- L60 _public method_ `public override ObjectId ToObjectId(TestId value)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/TestData/TestMetaId.cs` (HordeServer.Build)


#### record struct `HordeServer.Jobs.TestData.TestMetaId`  
`public record struct TestMetaId(ObjectId Id)`  
_public; L17-49_
- attrs: `[JsonSchemaString] [TypeConverter(typeof(ObjectIdTypeConverter<TestMetaId, TestMetaIdConverter>))] [ObjectIdConverter(typeof(TestMetaIdConverter))]`
- desc: Identifier for a session
- L22 _public property_ `public static TestMetaId Empty { get; }` — Default empty value for session id
- L27 _public method_ `public static TestMetaId GenerateNewId()` — Creates a new TestMetaId
- L30 _public method_ `public static TestMetaId Parse(string text)` — (inheritdoc)
- L33-45 _public method_ `public static bool TryParse(string text, out TestMetaId id)` — (inheritdoc)
- L48 _public method_ `public override string ToString()` — (inheritdoc)

#### class `HordeServer.Jobs.TestData.TestMetaIdConverter`  
`class TestMetaIdConverter : ObjectIdConverter<TestMetaId>`  
_internal*; L54-61_
- inherits: `ObjectIdConverter<TestMetaId>`
- desc: Converter to and from ObjectId instances.
- L57 _public method_ `public override TestMetaId FromObjectId(ObjectId id)` — (inheritdoc)
- L60 _public method_ `public override ObjectId ToObjectId(TestMetaId value)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/TestData/TestPhaseId.cs` (HordeServer.Build)


#### record struct `HordeServer.Jobs.TestData.TestPhaseId`  
`public record struct TestPhaseId(ObjectId Id)`  
_public; L17-47_
- attrs: `[JsonSchemaString] [TypeConverter(typeof(ObjectIdTypeConverter<TestPhaseId, TestPhaseIdConverter>))] [ObjectIdConverter(typeof(TestPhaseIdConverter))]`
- desc: Identifier for a test phase
- L22 _public property_ `public static TestPhaseId Empty { get; }` — Default empty value for phase id
- L27 _public method_ `public static TestPhaseId GenerateNewId()` — Creates a new TestPhaseId
- L30 _public method_ `public static TestPhaseId Parse(string text)` — (inheritdoc)
- L33-43 _public method_ `public static bool TryParse(string text, out TestPhaseId id)` — (inheritdoc)
- L46 _public method_ `public override string ToString()` — (inheritdoc)

#### class `HordeServer.Jobs.TestData.TestPhaseIdConverter`  
`class TestPhaseIdConverter : ObjectIdConverter<TestPhaseId>`  
_internal*; L52-59_
- inherits: `ObjectIdConverter<TestPhaseId>`
- desc: Converter to and from ObjectId instances.
- L55 _public method_ `public override TestPhaseId FromObjectId(ObjectId id)` — (inheritdoc)
- L58 _public method_ `public override ObjectId ToObjectId(TestPhaseId value)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/TestData/TestPhaseSessionId.cs` (HordeServer.Build)


#### record struct `HordeServer.Jobs.TestData.TestPhaseSessionId`  
`public record struct TestPhaseSessionId(ObjectId Id)`  
_public; L17-52_
- attrs: `[JsonSchemaString] [TypeConverter(typeof(ObjectIdTypeConverter<TestPhaseSessionId, TestPhaseSessionIdConverter>))] [ObjectIdConverter(typeof(TestPhaseSessionIdConverter))]`
- desc: Identifier for a test phase session
- L22 _public property_ `public static TestPhaseSessionId Empty { get; }` — Default empty value for session id
- L27 _public method_ `public static TestPhaseSessionId GenerateNewId()` — Creates a new TestPhaseSessionId
- L32 _public method_ `public static TestPhaseSessionId GenerateNewId(DateTime time)` — Creates a new TestPhaseSessionId
- L35 _public method_ `public static TestPhaseSessionId Parse(string text)` — (inheritdoc)
- L38-48 _public method_ `public static bool TryParse(string text, out TestPhaseSessionId id)` — (inheritdoc)
- L51 _public method_ `public override string ToString()` — (inheritdoc)

#### class `HordeServer.Jobs.TestData.TestPhaseSessionIdConverter`  
`class TestPhaseSessionIdConverter : ObjectIdConverter<TestPhaseSessionId>`  
_internal*; L57-64_
- inherits: `ObjectIdConverter<TestPhaseSessionId>`
- desc: Converter to and from ObjectId instances.
- L60 _public method_ `public override TestPhaseSessionId FromObjectId(ObjectId id)` — (inheritdoc)
- L63 _public method_ `public override ObjectId ToObjectId(TestPhaseSessionId value)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/TestData/TestRecipeId.cs` (HordeServer.Build)


#### record struct `HordeServer.Jobs.TestData.TestRecipeId`  
`public record struct TestRecipeId(ObjectId Id)`  
_public; L17-49_
- attrs: `[JsonSchemaString] [TypeConverter(typeof(ObjectIdTypeConverter<TestRecipeId, TestRecipeIdConverter>))] [ObjectIdConverter(typeof(TestRecipeIdConverter))]`
- desc: Identifier for a test recipe
- L22 _public property_ `public static TestRecipeId Empty { get; }` — Default empty value for test recipe id
- L27 _public method_ `public static TestRecipeId GenerateNewId()` — Creates a new TestRecipeId
- L30 _public method_ `public static TestRecipeId Parse(string text)` — (inheritdoc)
- L33-45 _public method_ `public static bool TryParse(string text, out TestRecipeId id)` — (inheritdoc)
- L48 _public method_ `public override string ToString()` — (inheritdoc)

#### class `HordeServer.Jobs.TestData.TestRecipeIdConverter`  
`class TestRecipeIdConverter : ObjectIdConverter<TestRecipeId>`  
_internal*; L54-61_
- inherits: `ObjectIdConverter<TestRecipeId>`
- desc: Converter to and from ObjectId instances.
- L57 _public method_ `public override TestRecipeId FromObjectId(ObjectId id)` — (inheritdoc)
- L60 _public method_ `public override ObjectId ToObjectId(TestRecipeId value)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/TestData/TestRefId.cs` (HordeServer.Build)


#### record struct `HordeServer.Jobs.TestData.TestRefId`  
`public record struct TestRefId(ObjectId Id)`  
_public; L17-54_
- attrs: `[JsonSchemaString] [TypeConverter(typeof(ObjectIdTypeConverter<TestRefId, TestRefIdConverter>))] [ObjectIdConverter(typeof(TestRefIdConverter))]`
- desc: Identifier for a session
- L22 _public property_ `public static TestRefId Empty { get; }` — Default empty value for session id
- L27 _public method_ `public static TestRefId GenerateNewId()` — Creates a new TestRefId
- L32 _public method_ `public static TestRefId GenerateNewId(DateTime time)` — Creates a new TestRefId
- L35 _public method_ `public static TestRefId Parse(string text)` — (inheritdoc)
- L38-50 _public method_ `public static bool TryParse(string text, out TestRefId id)` — (inheritdoc)
- L53 _public method_ `public override string ToString()` — (inheritdoc)

#### class `HordeServer.Jobs.TestData.TestRefIdConverter`  
`class TestRefIdConverter : ObjectIdConverter<TestRefId>`  
_internal*; L59-66_
- inherits: `ObjectIdConverter<TestRefId>`
- desc: Converter to and from ObjectId instances.
- L62 _public method_ `public override TestRefId FromObjectId(ObjectId id)` — (inheritdoc)
- L65 _public method_ `public override ObjectId ToObjectId(TestRefId value)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/TestData/TestSessionId.cs` (HordeServer.Build)


#### record struct `HordeServer.Jobs.TestData.TestSessionId`  
`public record struct TestSessionId(ObjectId Id)`  
_public; L17-57_
- attrs: `[JsonSchemaString] [TypeConverter(typeof(ObjectIdTypeConverter<TestSessionId, TestSessionIdConverter>))] [ObjectIdConverter(typeof(TestSessionIdConverter))]`
- desc: Identifier for a test session
- L22 _public property_ `public static TestSessionId Empty { get; }` — Default empty value for session id
- L27 _public method_ `public static TestSessionId GenerateNewId()` — Creates a new TestSessionId
- L32 _public method_ `public static TestSessionId GenerateNewId(DateTime time)` — Creates a new TestSessionId
- L35 _public method_ `public static TestSessionId Parse(string text)` — (inheritdoc)
- L38-48 _public method_ `public static bool TryParse(string text, out TestSessionId id)` — (inheritdoc)
- L51 _public method_ `public override string ToString()` — (inheritdoc)
- L56 _public property_ `public DateTime CreationTime => ...` — The creation time of the id (derived from timestamp)

#### class `HordeServer.Jobs.TestData.TestSessionIdConverter`  
`class TestSessionIdConverter : ObjectIdConverter<TestSessionId>`  
_internal*; L62-69_
- inherits: `ObjectIdConverter<TestSessionId>`
- desc: Converter to and from ObjectId instances.
- L65 _public method_ `public override TestSessionId FromObjectId(ObjectId id)` — (inheritdoc)
- L68 _public method_ `public override ObjectId ToObjectId(TestSessionId value)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/TestData/TestSuiteId.cs` (HordeServer.Build)


#### record struct `HordeServer.Jobs.TestData.TestSuiteId`  
`public record struct TestSuiteId(ObjectId Id)`  
_public; L17-49_
- attrs: `[JsonSchemaString] [TypeConverter(typeof(ObjectIdTypeConverter<TestSuiteId, TestSuiteIdConverter>))] [ObjectIdConverter(typeof(TestSuiteIdConverter))]`
- desc: Identifier for a session
- L22 _public property_ `public static TestSuiteId Empty { get; }` — Default empty value for session id
- L27 _public method_ `public static TestSuiteId GenerateNewId()` — Creates a new TestSuiteId
- L30 _public method_ `public static TestSuiteId Parse(string text)` — (inheritdoc)
- L33-45 _public method_ `public static bool TryParse(string text, out TestSuiteId id)` — (inheritdoc)
- L48 _public method_ `public override string ToString()` — (inheritdoc)

#### class `HordeServer.Jobs.TestData.TestSuiteIdConverter`  
`class TestSuiteIdConverter : ObjectIdConverter<TestSuiteId>`  
_internal*; L54-61_
- inherits: `ObjectIdConverter<TestSuiteId>`
- desc: Converter to and from ObjectId instances.
- L57 _public method_ `public override TestSuiteId FromObjectId(ObjectId id)` — (inheritdoc)
- L60 _public method_ `public override ObjectId ToObjectId(TestSuiteId value)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/TestData/TestTagId.cs` (HordeServer.Build)


#### record struct `HordeServer.Jobs.TestData.TestTagId`  
`public record struct TestTagId(ObjectId Id)`  
_public; L17-47_
- attrs: `[JsonSchemaString] [TypeConverter(typeof(ObjectIdTypeConverter<TestTagId, TestTagIdConverter>))] [ObjectIdConverter(typeof(TestTagIdConverter))]`
- desc: Identifier for a tag
- L22 _public property_ `public static TestTagId Empty { get; }` — Default empty value for session id
- L27 _public method_ `public static TestTagId GenerateNewId()` — Creates a new TestTagId
- L30 _public method_ `public static TestTagId Parse(string text)` — (inheritdoc)
- L33-43 _public method_ `public static bool TryParse(string text, out TestTagId id)` — (inheritdoc)
- L46 _public method_ `public override string ToString()` — (inheritdoc)

#### class `HordeServer.Jobs.TestData.TestTagIdConverter`  
`class TestTagIdConverter : ObjectIdConverter<TestTagId>`  
_internal*; L52-59_
- inherits: `ObjectIdConverter<TestTagId>`
- desc: Converter to and from ObjectId instances.
- L55 _public method_ `public override TestTagId FromObjectId(ObjectId id)` — (inheritdoc)
- L58 _public method_ `public override ObjectId ToObjectId(TestTagId value)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/Timing/IJobTimingCollection.cs` (HordeServer.Build)


#### class `HordeServer.Jobs.Timing.JobStepTimingData`  
`public class JobStepTimingData`  
_public; L12-60_
- desc: Average timing information for a node
- L17 _public property_ `public string Name { get; set; }` — Name of the node
- L23 _public property_ `public float? AverageWaitTime { get; set; }` — attrs: `[BsonIgnoreIfNull]` — Wait time before executing the group containing this node
- L29 _public property_ `public float? AverageInitTime { get; set; }` — attrs: `[BsonIgnoreIfNull]` — Time taken for the group containing this node to initialize
- L35 _public property_ `public float? AverageDuration { get; set; }` — attrs: `[BsonIgnoreIfNull]` — Time spent executing this node
- L41-44 _private ctor_ `private JobStepTimingData()` — attrs: `[BsonConstructor]` — Constructor for serialization
- L53-59 _public ctor_ `public JobStepTimingData(string name, float? averageWaitTime, float? averageInitTime, float? averageDuration)` — Constructor

#### interface `HordeServer.Jobs.Timing.IJobTimingCollection`  
`public interface IJobTimingCollection`  
_public; L65-89_
- desc: Interface for a collection of JobTiming documents
- L73 _public* method_ `Task<IJobTiming?> TryAddAsync(JobId jobId, List<JobStepTimingData> steps)` — Add timing information for the given job
- L80 _public* method_ `Task<IJobTiming?> TryGetAsync(JobId jobId)` — Attempts to get the timing information for a particular job
- L88 _public* method_ `Task<IJobTiming?> TryAddStepsAsync(IJobTiming jobTiming, List<JobStepTimingData> steps)` — Adds timing information for the particular job

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Jobs/Timing/JobTimingCollection.cs` (HordeServer.Build)


#### class `HordeServer.Jobs.Timing.JobTimingCollection`  
`public class JobTimingCollection : IJobTimingCollection`  
_public; L17-139_
- inherits: `IJobTimingCollection`
- desc: Concrete implementation of IJobTimingCollection
- L77 _private* field_ `readonly IMongoCollection<JobTimingDocument> _collection` — Collection of timing documents
- L83-86 _public ctor_ `public JobTimingCollection(IMongoService mongoService)` — Constructor
- L89-112 _public method_ `public async Task<IJobTiming?> TryAddAsync(JobId jobId, List<JobStepTimingData> steps)` — (inheritdoc)
- L115-118 _public method_ `public async Task<IJobTiming?> TryGetAsync(JobId jobId)` — (inheritdoc)
- L121-138 _public method_ `public async Task<IJobTiming?> TryAddStepsAsync(IJobTiming jobTiming, List<JobStepTimingData> steps)` — (inheritdoc)

#### class `HordeServer.Jobs.Timing.JobTimingCollection.JobStepTimingDocument`  
`class JobStepTimingDocument : IJobStepTiming`  
_private*; L22-42_
- inherits: `IJobStepTiming`
- desc: Timing information for a particular step
- L24 _public property_ `public string Name { get; set; }`
- L25 _public property_ `public float? AverageWaitTime { get; set; }`
- L26 _public property_ `public float? AverageInitTime { get; set; }`
- L27 _public property_ `public float? AverageDuration { get; set; }`
- L30-33 _private ctor_ `private JobStepTimingDocument()` — attrs: `[BsonConstructor]`
- L35-41 _public ctor_ `public JobStepTimingDocument(string name, float? averageWaitTime, float? averageInitTime, float? averageDuration)`

#### class `HordeServer.Jobs.Timing.JobTimingCollection.JobTimingDocument`  
`class JobTimingDocument : IJobTiming`  
_private*; L47-72_
- inherits: `IJobTiming`
- desc: Timing information for a particular job
- L49 _public property_ `public JobId Id { get; set; }`
- L50 _public property_ `public List<JobStepTimingDocument> Steps { get; set; }`
- L51 _public property_ `public int UpdateIndex { get; set; }`
- L54 _public field_ `public Dictionary<string, IJobStepTiming>? _nameToStep` — attrs: `[BsonIgnore]`
- L54 _public field_ `public Dictionary< _nameToStep` — attrs: `[BsonIgnore]`
- L56-71 _public method_ `public bool TryGetStepTiming(string name, ILogger logger, [NotNullWhen(true)] out IJobStepTiming? timing)`

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Notifications/DeepLinkController.cs` (HordeServer.Build)


#### class `HordeServer.Notifications.DeepLinkController`  
`public class DeepLinkController : ControllerBase`  
_public; L17-108_
- attrs: `[ApiController] [Authorize] [Route("[controller]")]`
- inherits: `ControllerBase`
- desc: Controller for the /api/v1/deeplink endpoint
- L19 _private field_ `private readonly INotificationService _notificationService`
- L20 _private field_ `private readonly ILogger _logger`
- L25-29 _public ctor_ `public DeepLinkController(INotificationService notificationService, ILogger<DeepLinkController> logger)` — Constructor
- L40-64 _public method_ `public async Task<ActionResult<GetDirectMessageLinkResponse>> GetDirectMessageDeepLinkAsync([FromBody] GetDirectMessageLinkRequest request, CancellationToken cancellationToken = default)` — attrs: `[HttpPost] [Route("/api/v1/deeplink/directmessage")] [ProducesResponseType(typeof(GetDirectMessageLinkResponse), 200)]` — Get direct message deep link
- L75-89 _public method_ `public async Task<ActionResult<GetChannelLinkResponse>> GetChannelDeepLinkAsync([FromQuery] string channelId, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/deeplink/channel")] [ProducesResponseType(typeof(GetChannelLinkResponse), 200)]` — Get channel deep link
- L96-107 _private* method_ `static UserId? TryParseUserId(string userId)` — Parse a user id from a string. Return null if failed to parse.

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Notifications/DeepLinkMessages.cs` (HordeServer.Build)


#### class `HordeServer.Notifications.GetDirectMessageLinkRequest`  
`public class GetDirectMessageLinkRequest`  
_public; L8-14_
- desc: A direct message link request
- L13 _public property_ `public List<string> UserIds { get; set; }` — the user ids

#### class `HordeServer.Notifications.GetDirectMessageLinkResponse`  
`public class GetDirectMessageLinkResponse`  
_public; L19-25_
- desc: The Direct Message link response
- L24 _public property_ `public string? Url { get; set; }` — The result deep link

#### class `HordeServer.Notifications.GetChannelLinkResponse`  
`public class GetChannelLinkResponse`  
_public; L30-36_
- desc: The Channel link response
- L35 _public property_ `public string? Url { get; set; }` — The result deep link

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Notifications/IEvent.cs` (HordeServer.Build)


#### interface `HordeServer.Notifications.IEvent`  
`public interface IEvent`  
_public; L11-18_
- desc: Base interface for events that users can subscribe for notifications to
- L17 _public method_ `public EventRecord ToRecord()` — Converts this event into an API event record

#### interface `HordeServer.Notifications.IJobCompleteEvent`  
`public interface IJobCompleteEvent : IEvent`  
_public; L23-34_
- inherits: `IEvent`
- desc: Event that occurs when a job completes
- L28 _public* property_ `StreamId StreamId { get; }` — The stream id
- L33 _public* property_ `TemplateId TemplateId { get; }` — The template id

#### interface `HordeServer.Notifications.ILabelCompleteEvent`  
`public interface ILabelCompleteEvent : IEvent`  
_public; L39-55_
- inherits: `IEvent`
- desc: Event that occurs when a label completes
- L44 _public* property_ `StreamId StreamId { get; }` — The stream id
- L49 _public* property_ `TemplateId TemplateId { get; }` — The template id
- L54 _public* property_ `string LabelName { get; }` — Name of the label to monitor

#### interface `HordeServer.Notifications.IStepCompleteEvent`  
`public interface IStepCompleteEvent : IEvent`  
_public; L60-76_
- inherits: `IEvent`
- desc: Event that occurs when a job step completes
- L65 _public* property_ `StreamId StreamId { get; }` — The stream id
- L70 _public* property_ `TemplateId TemplateId { get; }` — The template id
- L75 _public* property_ `string StepName { get; }` — Name of the step to monitor

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Notifications/INotificationService.cs` (HordeServer.Build)


#### interface `HordeServer.Notifications.INotification`  
`public interface INotification<T> : IEquatable<T>`  
_public; L24-24_
- attrs: `[SuppressMessage("Design", "CA1040:Avoid empty interfaces", Justification = "Marker interface for generic type handling")]`
- inherits: `IEquatable<T>`
- desc: Marker interface for (serializable) notifications Implements IEquatable primarily for being IMemoryCache-compatible.

#### class `HordeServer.Notifications.JobScheduledNotification`  
`public class JobScheduledNotification : INotification<JobScheduledNotification>`  
_public; L29-90_
- inherits: `INotification<JobScheduledNotification>`
- desc: Notification for job scheduled events
- L32 _public property_ `public string JobId { get; }` — Job ID
- L35 _public property_ `public string JobName { get; }` — Job name
- L38 _public property_ `public string PoolName { get; }` — Pool name job got scheduled in
- L46-51 _public ctor_ `public JobScheduledNotification(string jobId, string jobName, string poolName)` — Constructor
- L54-65 _public method_ `public bool Equals(JobScheduledNotification? other)` — (inheritdoc)
- L68-83 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L86-89 _public method_ `public override int GetHashCode()` — (inheritdoc)

#### interface `HordeServer.Notifications.INotificationService`  
`public interface INotificationService`  
_public; L95-224_
- desc: Interface for the notification service
- L106 _public* method_ `Task<bool> UpdateSubscriptionsAsync(NotificationTriggerId triggerId, ClaimsPrincipal user, bool? email, bool? slack, CancellationToken cancellationToken)` — Updates a subscription to a trigger
- L115 _public* method_ `Task<INotificationSubscription?> GetSubscriptionsAsync(NotificationTriggerId triggerId, ClaimsPrincipal user, CancellationToken cancellationToken)` — Gets the current subscriptions for a user
- L122 _public* method_ `void NotifyJobAborted(IJob job, IGraph graph)` — Notify all subscribers that a job has been cancelled
- L132 _public* method_ `void NotifyJobStepComplete(IJob job, IGraph graph, JobStepBatchId batchId, JobStepId stepId)` — Notify all subscribers that a job step has finished
- L141 _public* method_ `void NotifyLabelUpdate(IJob job, IReadOnlyList<(LabelState, LabelOutcome)> oldLabelStates, IReadOnlyList<(LabelState, LabelOutcome)> newLabelStates)` — Notify all subscribers that a job step's outcome has changed
- L147 _public* method_ `void NotifyConfigUpdate(ConfigUpdateInfo info)` — Notify slack channel about a configuration update
- L157 _public* method_ `void NotifyConfigUpdateFailure(string errorMessage, string fileName, int? change = null, IUser? author = null, string? description = null)` — Notify slack channel about a stream update failure
- L163 _public* method_ `void NotifyIssueUpdated(IIssue issue)` — Sends a notification to a user regarding a build health issue.
- L176 _public* method_ `void NotifyDeviceService(string message, IDevice? device = null, IDevicePool? pool = null, StreamConfig? streamConfig = null, IJob? job = null, IJobStep? step = null, INode? node = null, IUser? user = null)` — Send a device service notification
- L183 _public* method_ `Task SendDeviceIssueReportAsync(DeviceIssueReport report, CancellationToken cancellationToken)` — Post a notification for device issues
- L190 _public* method_ `Task SendAgentReportAsync(AgentReport report, CancellationToken cancellationToken)` — Post a notification for any agents encountering issues
- L197 _public* method_ `Task SendIssueReportAsync(IssueReportGroup report, CancellationToken cancellationToken)` — Post a notification for the open issues in a stream
- L207 _public* method_ `Task NotifyTestHealthReportAsync(ITestHealthReport report, string recipient, string[]? carbonCopies, CancellationToken cancellationToken)` — Post a notification for test health report
- L215 _public* method_ `Task<string?> GetDirectMessageLinkAsync(IReadOnlyList<UserId> userIds, CancellationToken cancellationToken = default)` — Get Direct Message link
- L223 _public* method_ `Task<string?> GetChannelLinkAsync(string channel, CancellationToken cancellationToken = default)` — Get Channel link

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Notifications/INotificationSink.cs` (HordeServer.Build)


#### interface `HordeServer.Notifications.INotificationSink`  
`public interface INotificationSink`  
_public; L23-192_
- desc: Implements a notification method
- L31 _public* method_ `Task NotifyJobScheduledAsync(List<JobScheduledNotification> notifications, CancellationToken cancellationToken)` — Send notifications that a job has been scheduled
- L41 _public* method_ `Task NotifyJobCompleteAsync(IJob job, IGraph graph, LabelOutcome outcome, CancellationToken cancellationToken)` — Send notifications that a job has completed
- L52 _public* method_ `Task NotifyJobCompleteAsync(IUser user, IJob job, IGraph graph, LabelOutcome outcome, CancellationToken cancellationToken)` — Send notifications that a job has completed
- L65 _public* method_ `Task NotifyJobStepAbortedAsync(IEnumerable<IUser>? usersToNotify, IJob job, IJobStepBatch batch, IJobStep step, INode node, List<ILogEventData> jobStepEventData, CancellationToken cancellationToken)` — Send notifications that a job step has been canceled
- L78 _public* method_ `Task NotifyJobStepCompleteAsync(IEnumerable<IUser>? usersToNotify, IJob job, IJobStepBatch batch, IJobStep step, INode node, List<ILogEventData> jobStepEventData, CancellationToken cancellationToken)` — Send notifications that a job step has completed
- L91 _public* method_ `Task NotifyLabelCompleteAsync(IUser user, IJob job, ILabel label, int labelIdx, LabelOutcome outcome, List<(string, JobStepOutcome, Uri)> stepData, CancellationToken cancellationToken)` — Send notifications that a job step has completed
- L101 _public* method_ `Task NotifyIssueUpdatedAsync(IIssue issue, CancellationToken cancellationToken)` — Send notifications that a new issue has been created or assigned
- L109 _public* method_ `Task SendIssueReportAsync(IssueReportGroup report, CancellationToken cancellationToken)` — Notify the status of issues in a stream
- L118 _public* method_ `Task NotifyConfigUpdateAsync(ConfigUpdateInfo info, CancellationToken cancellationToken)` — Notification that the configuration state has changed
- L130 _public* method_ `Task NotifyConfigUpdateFailureAsync(string errorMessage, string fileName, int? change = null, IUser? author = null, string? description = null, CancellationToken cancellationToken = default)` — Notification that a stream has failed to update
- L145 _public* method_ `Task NotifyDeviceServiceAsync(string message, IDevice? device = null, IDevicePool? pool = null, StreamConfig? streamConfig = null, IJob? job = null, IJobStep? step = null, INode? node = null, IUser? user = null, CancellationToken cancellationToken = default)` — Notification for device service
- L153 _public* method_ `Task SendDeviceIssueReportAsync(DeviceIssueReport report, CancellationToken cancellationToken)` — Notify the status of devices
- L158 _public* method_ `Task SendAgentReportAsync(AgentReport report, CancellationToken cancellationToken)` — Notify the status of agents in the farm
- L165 _public* method_ `Task SendSessionConflictReportAsync(IReadOnlyList<(AgentId Id, int Count)> conflicts, CancellationToken cancellationToken)` — Send a batched report of session conflicts detected in the last 12 hours
- L175 _public* method_ `Task NotifyTestHealthReportAsync(ITestHealthReport report, string recipient, string[]? carbonCopies, CancellationToken cancellationToken)` — Post a notification for test health report
- L183 _public* method_ `Task<string?> GetDirectMessageLinkAsync(IReadOnlyList<UserId> userIds, CancellationToken cancellationToken = default)` — Get Direct Message Link
- L191 _public* method_ `Task<string?> GetChannelLinkAsync(string channel, CancellationToken cancellationToken = default)` — Get Channel link

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Notifications/INotificationTrigger.cs` (HordeServer.Build)


#### interface `HordeServer.Notifications.INotificationSubscription`  
`public interface INotificationSubscription`  
_public; L11-27_
- desc: An individual subscription
- L16 _public property_ `public UserId UserId { get; }` — Name of the user
- L21 _public property_ `public bool Email { get; }` — Whether to receive email notifications
- L26 _public property_ `public bool Slack { get; }` — Whether to receive Slack notifications

#### interface `HordeServer.Notifications.INotificationTrigger`  
`public interface INotificationTrigger`  
_public; L32-48_
- desc: Trigger for notifications to be sent
- L37 _public* property_ `NotificationTriggerId Id { get; }` — Unique id for this subscription list
- L42 _public* property_ `bool Fired { get; }` — Whether this trigger has been fired
- L47 _public property_ `public IReadOnlyList<INotificationSubscription> Subscriptions { get; }` — List of subscriptions to this event

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Notifications/INotificationTriggerCollection.cs` (HordeServer.Build)


#### interface `HordeServer.Notifications.INotificationTriggerCollection`  
`public interface INotificationTriggerCollection`  
_public; L13-65_
- desc: Collection of notification triggers
- L21 _public* method_ `Task<INotificationTrigger> FindOrAddAsync(NotificationTriggerId triggerId, CancellationToken cancellationToken)` — Finds or adds a trigger
- L29 _public* method_ `Task<INotificationTrigger?> GetAsync(NotificationTriggerId triggerId, CancellationToken cancellationToken)` — Finds an existing trigger with the given id, or adds one if it does not exist
- L37 _public* method_ `Task DeleteAsync(NotificationTriggerId triggerId, CancellationToken cancellationToken)` — Deletes a trigger
- L45 _public* method_ `Task DeleteAsync(List<NotificationTriggerId> triggerIds, CancellationToken cancellationToken)` — Deletes a trigger
- L53 _public* method_ `Task<INotificationTrigger?> FireAsync(INotificationTrigger trigger, CancellationToken cancellationToken)` — Fires the trigger, and marks notifications has having been sent
- L64 _public* method_ `Task<INotificationTrigger?> UpdateSubscriptionsAsync(INotificationTrigger trigger, UserId userId, bool? email, bool? slack, CancellationToken cancellationToken)` — Adds a subscriber to a particular trigger

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Notifications/ISubscription.cs` (HordeServer.Build)


#### enum `HordeServer.Notifications.NotificationType`  
`public enum NotificationType`  
_public; L12-18_
- desc: The type of notification to send
- L17 _public* enumerator_ `Slack` — Send a DM on Slack

#### interface `HordeServer.Notifications.ISubscription`  
`public interface ISubscription`  
_public; L23-44_
- desc: Subscription to a type of event
- L28 _public property_ `public string Id { get; }` — Unique id for this subscription
- L33 _public property_ `public IEvent Event { get; }` — Name of the event to subscribe to
- L38 _public property_ `public UserId UserId { get; }` — User to notify
- L43 _public property_ `public NotificationType NotificationType { get; }` — Type of notification to receive

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Notifications/ISubscriptionCollection.cs` (HordeServer.Build)


#### class `HordeServer.Notifications.NewSubscription`  
`public class NewSubscription`  
_public; L10-39_
- desc: Information for creating a new subscription
- L15 _public property_ `public EventRecord Event { get; set; }` — Name of the event
- L20 _public property_ `public UserId UserId { get; set; }` — The user name
- L25 _public property_ `public NotificationType NotificationType { get; set; }` — Type of notification to send
- L33-38 _public ctor_ `public NewSubscription(EventRecord eventRecord, UserId userId, NotificationType notificationType)` — Constructor

#### interface `HordeServer.Notifications.ISubscriptionCollection`  
`public interface ISubscriptionCollection`  
_public; L44-80_
- desc: Interface for a collection of subscriptions
- L51 _public method_ `public Task<List<ISubscription>> AddAsync(IEnumerable<NewSubscription> subscriptions)` — Add new subscription documents
- L58 _public method_ `public Task RemoveAsync(IEnumerable<ISubscription> subscriptions)` — Remove a set of existing subscriptions
- L65 _public method_ `public Task<ISubscription?> GetAsync(string subscriptionId)` — Gets a subscription by id
- L72 _public method_ `public Task<List<ISubscription>> FindSubscribersAsync(EventRecord eventRecord)` — Find all subscribers of a certain event
- L79 _public method_ `public Task<List<ISubscription>> FindSubscriptionsAsync(UserId userId)` — Find subscriptions for a particular user

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Notifications/NotificationAclAction.cs` (HordeServer.Build)


#### class `HordeServer.Notifications.NotificationAclAction`  
`public static class NotificationAclAction`  
_public; L10-16_
- desc: ACL actions which apply to notifications
- L15 _public property_ `public static AclAction CreateSubscription { get; }` — Ability to subscribe to notifications

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Notifications/NotificationMessages.cs` (HordeServer.Build)


#### class `HordeServer.Notifications.UpdateNotificationsRequest`  
`public class UpdateNotificationsRequest`  
_public; L8-19_
- desc: A request from a user to be notified when something happens.
- L13 _public property_ `public bool? Email { get; set; }` — Request notifications by email
- L18 _public property_ `public bool? Slack { get; set; }` — Request notifications on Slack

#### class `HordeServer.Notifications.GetNotificationResponse`  
`public class GetNotificationResponse`  
_public; L24-53_
- desc: A request from a user to be notified when something happens.
- L29 _public property_ `public bool Email { get; set; }` — Request notifications by email
- L34 _public property_ `public bool Slack { get; set; }` — Request notifications on Slack
- L40-52 _internal ctor_ `internal GetNotificationResponse(INotificationSubscription? subscription)` — Constructor

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Notifications/NotificationService.cs` (HordeServer.Build)


#### class `HordeServer.Notifications.NotificationService`  
`public sealed class NotificationService : IHostedService, INotificationService, IAsyncDisposable`  
_public; L37-994_
- inherits: `IHostedService, INotificationService, IAsyncDisposable`
- desc: Wraps functionality for delivering notifications.
- L42 _private field_ `private readonly List<INotificationSink> _sinks` — The available notification sinks
- L47 _private field_ `private readonly ISubscriptionCollection _subscriptionCollection` — Collection of subscriptions
- L52 _private field_ `private readonly INotificationTriggerCollection _triggerCollection` — Collection of notification request documents.
- L57 _private field_ `private readonly IGraphCollection _graphCollection` — Instance of the _graphCollection.
- L62 _private field_ `private readonly IUserCollection _userCollection`
- L67 _private field_ `private readonly JobService _jobService` — Job service instance
- L72 _private field_ `private readonly IssueService _issueService`
- L77 _private field_ `private readonly ILogCollection _logCollection` — Instance of the ILogCollection.
- L82 _private field_ `private readonly IMemoryCache _cache` — Cache for de-duplicating queued notifications
- L88 _private field_ `private readonly object _cacheLock = new object()` — Lock object for manipulating the above cache Used since batch notification queue handling is run async.
- L93 _private field_ `private readonly RedisConnectionPool _redisConnectionPool` — Connection pool for Redis databases
- L98 _private field_ `private readonly IOptionsMonitor<BuildServerConfig> _settings` — Settings for the application.
- L103 _private field_ `private readonly List<Task> _tasks = []` — Async notification tasks currently executing. Tracked so they can be awaited before shutting down
- L104 _private field_ `private readonly object _tasksLock = new()`
- L109 _private field_ `private readonly ILogger<NotificationService> _logger` — Settings for the application.
- L114 _internal field_ `internal ITicker _ticker` — Ticker for running batch sender method
- L119 _internal field_ `internal TimeSpan _notificationBatchInterval = TimeSpan.FromHours(12)` — Interval at which queued notifications should be sent as a batch
- L121 _private* field_ `readonly IServerInfo _serverInfo`
- L122 _private* field_ `readonly SessionConflictService _sessionConflictService`
- L123 _private* field_ `readonly Counter<int> _jobCounter`
- L124 _private* field_ `readonly Histogram<double> _jobDurationHistogram`
- L126 _private* method_ `static string RedisQueueListKey(string notificationType)`
- L131-175 _public ctor_ `public NotificationService( IEnumerable<INotificationSink> sinks, IOptionsMonitor<BuildServerConfig> settings, ILogger<NotificationService> logger, IGraphCollection graphCollection, ISubscriptionCollection subscriptionCollection, INotificationTriggerCollection triggerCollection, IUserCollection userCollection, JobService jobService, IssueService issueService, ILogCollection logCollection, Meter meter, IMemoryCache cache, IRedisService redisService, IConfigService configService, IServerInfo serverInfo, SessionConflictService sessionConflictService, IClock clock)` — Constructor
- L178-181 _public method_ `public async Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L184-188 _public method_ `public async Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L191-200 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L202-225 _private method_ `private async Task WaitForAsyncTasksToCompleteAsync(CancellationToken ct)`
- L228-240 _public method_ `public async Task<bool> UpdateSubscriptionsAsync(NotificationTriggerId triggerId, ClaimsPrincipal user, bool? email, bool? slack, CancellationToken cancellationToken)` — (inheritdoc)
- L243-258 _public method_ `public async Task<INotificationSubscription?> GetSubscriptionsAsync(NotificationTriggerId triggerId, ClaimsPrincipal user, CancellationToken cancellationToken)` — (inheritdoc)
- L261-270 _public method_ `public void NotifyJobAborted(IJob job, IGraph graph)` — (inheritdoc)
- L273-289 _public method_ `public void NotifyJobStepComplete(IJob job, IGraph graph, JobStepBatchId batchId, JobStepId stepId)` — (inheritdoc)
- L299-305 _public method_ `public void NotifyJobScheduled(IPoolConfig pool, bool poolHasAgentsOnline, IJob job, IGraph graph, JobStepBatchId batchId)` — Notify all subscribers that a job step was scheduled
- L308-319 _public method_ `public void NotifyLabelUpdate(IJob job, IReadOnlyList<(LabelState, LabelOutcome)> oldLabelStates, IReadOnlyList<(LabelState, LabelOutcome)> newLabelStates)` — (inheritdoc)
- L322-326 _public method_ `public void NotifyIssueUpdated(IIssue issue)` — (inheritdoc)
- L329-333 _public method_ `public void NotifyConfigUpdate(ConfigUpdateInfo info)` — (inheritdoc)
- L336-339 _public method_ `public void NotifyConfigUpdateFailure(string errorMessage, string fileName, int? change = null, IUser? author = null, string? description = null)` — (inheritdoc)
- L342-345 _public method_ `public void NotifyDeviceService(string message, IDevice? device = null, IDevicePool? pool = null, StreamConfig? streamConfig = null, IJob? job = null, IJobStep? step = null, INode? node = null, IUser? user = null)` — (inheritdoc)
- L348-361 _public method_ `public async Task SendDeviceIssueReportAsync(DeviceIssueReport report, CancellationToken cancellationToken)` — (inheritdoc)
- L364-377 _public method_ `public async Task NotifyTestHealthReportAsync(ITestHealthReport report, string recipient, string[]? carbonCopies, CancellationToken cancellationToken)` — (inheritdoc)
- L383-410 _private* method_ `void EnqueueTask(Func<CancellationToken, Task> taskFunc)` — Enqueues an async task
- L416-422 _private* method_ `void EnqueueTasks(Func<INotificationSink, CancellationToken, Task> taskFunc)` — Enqueues an async task
- L430-454 _private method_ `private async Task EnqueueNotificationForBatchSendingAsync<T>(T notification, bool deduplicate = true) where T : INotification<T>` — Enqueue a notification in Redis for batch sending later on
- L456-490 _private method_ `private async ValueTask TickEveryTwelveHoursAsync(CancellationToken cancellationToken)`
- L498-527 _private method_ `private async Task<List<T>> GetAllQueuedNotificationsAsync<T>() where T : INotification<T>` — Get and clear all queued notifications of type T from Redis
- L536-550 _private method_ `private async Task<INotificationTrigger?> GetNotificationTriggerAsync(NotificationTriggerId? triggerId, bool fireTrigger, CancellationToken cancellationToken)` — Gets the INotificationTrigger for a given trigger ID, if any.
- L552-578 _private method_ `private async Task SendJobNotificationsAsync(IJob job, IGraph graph, CancellationToken cancellationToken)`
- L580-636 _private method_ `private Task RecordJobCompleteMetricsAsync(IJob job, CancellationToken cancellationToken)`
- L638-675 _private method_ `private async Task<IReadOnlyList<IUser>> GetUsersToNotifyAsync(EventRecord? eventRecord, NotificationTriggerId? notificationTriggerId, bool fireTrigger, CancellationToken cancellationToken)`
- L677-808 _private method_ `private async Task SendJobStepNotificationsAsync(IJob job, JobStepBatchId batchId, JobStepId stepId, CancellationToken cancellationToken)`
- L810-880 _private method_ `private async Task SendAllLabelNotificationsAsync(IJob job, IReadOnlyList<(LabelState State, LabelOutcome Outcome)> oldLabelStates, IReadOnlyList<(LabelState, LabelOutcome)> newLabelStates, CancellationToken cancellationToken)`
- L882-901 _private method_ `private void SendLabelUpdateNotifications(IJob job, IGraph graph, IReadOnlyDictionary<NodeRef, IJobStep> stepForNode, ILabel label, int labelIdx, LabelOutcome outcome, IReadOnlyList<IUser> slackUsers)`
- L904-917 _public method_ `public async Task SendAgentReportAsync(AgentReport report, CancellationToken cancellationToken)` — (inheritdoc)
- L920-934 _public method_ `public async Task SendIssueReportAsync(IssueReportGroup report, CancellationToken cancellationToken)` — (inheritdoc)
- L938-964 _public method_ `public async Task<string?> GetDirectMessageLinkAsync(IReadOnlyList<UserId> userIds, CancellationToken cancellationToken)` — (inheritdoc)
- L968-993 _public method_ `public async Task<string?> GetChannelLinkAsync(string channel, CancellationToken cancellationToken)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Notifications/NotificationTriggerCollection.cs` (HordeServer.Build)


#### class `HordeServer.Notifications.NotificationTriggerCollection`  
`public class NotificationTriggerCollection : INotificationTriggerCollection`  
_public; L17-246_
- inherits: `INotificationTriggerCollection`
- desc: Collection of notification triggers
- L60 _private* field_ `readonly IMongoCollection<TriggerDocument> _triggers`
- L61 _private* field_ `readonly IUserCollection _userCollection`
- L68-72 _public ctor_ `public NotificationTriggerCollection(IMongoService mongoService, IUserCollection userCollection)` — Constructor
- L75-102 _public method_ `public async Task<INotificationTrigger?> GetAsync(NotificationTriggerId triggerId, CancellationToken cancellationToken)` — (inheritdoc)
- L105-132 _public method_ `public async Task<INotificationTrigger> FindOrAddAsync(NotificationTriggerId triggerId, CancellationToken cancellationToken)` — (inheritdoc)
- L141-159 _private* method_ `async Task<INotificationTrigger?> TryUpdateAsync(INotificationTrigger trigger, TransactionBuilder<TriggerDocument> transaction, CancellationToken cancellationToken)` — Updates an existing document
- L162-166 _public method_ `public async Task DeleteAsync(NotificationTriggerId triggerId, CancellationToken cancellationToken)` — (inheritdoc)
- L169-174 _public method_ `public async Task DeleteAsync(List<NotificationTriggerId> triggerIds, CancellationToken cancellationToken)` — (inheritdoc)
- L177-201 _public method_ `public async Task<INotificationTrigger?> FireAsync(INotificationTrigger trigger, CancellationToken cancellationToken)` — (inheritdoc)
- L204-245 _public method_ `public async Task<INotificationTrigger?> UpdateSubscriptionsAsync(INotificationTrigger trigger, UserId userId, bool? email, bool? slack, CancellationToken cancellationToken)` — (inheritdoc)

#### class `HordeServer.Notifications.NotificationTriggerCollection.SubscriptionDocument`  
`class SubscriptionDocument : INotificationSubscription`  
_private*; L19-47_
- inherits: `INotificationSubscription`
- L22 _public property_ `public string? User { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L24 _public property_ `public UserId UserId { get; set; }`
- L25 _public property_ `public bool Email { get; set; }`
- L26 _public property_ `public bool Slack { get; set; }`
- L29-32 _private ctor_ `private SubscriptionDocument()` — attrs: `[BsonConstructor]`
- L34-39 _public ctor_ `public SubscriptionDocument(UserId userId, bool email, bool slack)`
- L41-46 _public ctor_ `public SubscriptionDocument(INotificationSubscription subscription)`

#### class `HordeServer.Notifications.NotificationTriggerCollection.TriggerDocument`  
`class TriggerDocument : INotificationTrigger`  
_private*; L49-58_
- inherits: `INotificationTrigger`
- L51 _public property_ `public ObjectId Id { get; set; }`
- L52 _public property_ `public bool Fired { get; set; }`
- L53 _public property_ `public List<SubscriptionDocument> Subscriptions { get; set; }`
- L54 _public property_ `public int UpdateIndex { get; set; }`
- L56 _private* property_ `NotificationTriggerId INotificationTrigger.Id => ...`
- L57 _private* property_ `IReadOnlyList<INotificationSubscription> INotificationTrigger.Subscriptions => ...`

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Notifications/Sinks/SlackNotificationSink.cs` (HordeServer.Build)


#### class `HordeServer.Notifications.Sinks.SlackNotificationSink`  
`public sealed class SlackNotificationSink : IHostedService, INotificationSink, IAvatarService, IRcaNotifier, IAsyncDisposable`  
_public; L58-4228_
- inherits: `IHostedService, INotificationSink, IAvatarService, IRcaNotifier, IAsyncDisposable`
- desc: Maintains a connection to Slack, in order to receive socket-mode notifications of user interactions
- L60 _private* const_ `const bool DefaultAllowMentions = true`
- L62 _private* const_ `const int MaxLineLength = 2048`
- L65 _private* const_ `const string ErrorColor = "#ec4c47"`
- L68 _private* const_ `const string WarningColor = "#f7d154"`
- L71 _private* const_ `const string SuccessColor = "#4db507"`
- L74 _private* const_ `const int RcaThreadLookupMaxAttempts = 4`
- L77 _private* const_ `const int RcaThreadLookupBaseDelaySecs = 5`
- L80 _private* const_ `const string YellowgBadge = ":large_yellow_square:"`
- L81 _private* const_ `const string OrangeBadge = ":large_orange_square:"`
- L82 _private* const_ `const string RedBadge = ":large_red_square:"`
- L83 _private* const_ `const string BlueBadge = ":large_blue_square:"`
- L84 _private* const_ `const string BlackBadge = ":black_square:"`
- L226 _private* field_ `readonly IRedisService _redisService`
- L227 _private* field_ `readonly IssueService _issueService`
- L228 _private* field_ `readonly ICommitService _commitService`
- L229 _private* field_ `readonly IUserCollection _userCollection`
- L230 _private* field_ `readonly ILogCollection _logCollection`
- L231 _private* field_ `readonly IWebHostEnvironment _environment`
- L232 _private* field_ `readonly BuildServerConfig _settings`
- L233 _private* field_ `readonly IMongoCollection<MessageStateDocument> _messageStates`
- L234 _private* field_ `readonly IMongoCollection<SlackUserDocument> _slackUsers`
- L235 _private* field_ `readonly HashSet<string>? _allowUsers`
- L236 _private* field_ `readonly IExternalIssueService _externalIssueService`
- L237 _private* field_ `readonly JsonSerializerOptions _jsonSerializerOptions`
- L238 _private* field_ `readonly ITicker _escalateTicker`
- L239 _private* field_ `static readonly RedisSortedSetKey<int> s_escalateIssues = "slack/escalate"`
- L240 _private* field_ `static readonly RedisSortedSetKey<int> s_escalateRootCauseAnalysis = "slack/escalate-rca"`
- L241 _private* field_ `readonly BackgroundTask _backgroundTask`
- L242 _private* field_ `readonly IServerInfo _serverInfo`
- L243 _private* field_ `readonly IOptionsMonitor<BuildConfig> _buildConfig`
- L244 _private* field_ `readonly ILogger _logger`
- L246 _private* field_ `readonly ITicker _issueQueueTicker`
- L247 _private* field_ `static readonly RedisListKey<int> s_redisIssueQueue = "slack/issue-queue"`
- L248 _private* field_ `readonly string _redisIssueLockPrefix`
- L250 _private* field_ `readonly SlackClient _slackClient`
- L251 _private* field_ `readonly SlackClient? _adminSlackClient`
- L256 _private field_ `private readonly MemoryCache _userCache = new MemoryCache(new MemoryCacheOptions())` — Map of email address to Slack user ID.
- L261 _private field_ `private readonly MemoryCache _dmChannelCache = new MemoryCache(new MemoryCacheOptions() { SizeLimit = 1024, ExpirationScanFrequency = TimeSpan.FromMinutes(10) })` — Map of Slack user IDs to DM channel.
- L266-302 _public ctor_ `public SlackNotificationSink(IMongoService mongoService, IRedisService redisService, IssueService issueService, ICommitService commitService, IUserCollection userCollection, ILogCollection logCollection, IExternalIssueService externalIssueService, IWebHostEnvironment environment, IOptions<BuildServerConfig> settings, IClock clock, IServerInfo serverInfo, IOptionsMonitor<BuildConfig> buildConfig, ILogger<SlackNotificationSink> logger)` — Constructor
- L305-314 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L317-322 _public method_ `public async Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L325-330 _public method_ `public async Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L335-338 _public method_ `public async Task<IAvatar?> GetAvatarAsync(IUser user, CancellationToken cancellationToken)` — (inheritdoc)
- L344-367 _private* method_ `async Task<(MessageStateDocument, bool)> AddOrUpdateMessageStateAsync(string recipient, string eventId, UserId? userId, string digest, SlackMessageId? messageId, CancellationToken cancellationToken)`
- L369-373 _private* method_ `async Task<MessageStateDocument?> GetMessageStateAsync(string recipient, string eventId, CancellationToken cancellationToken)`
- L375-380 _private* method_ `async Task<bool> DeleteMessageStateAsync(string recipient, string eventId, CancellationToken cancellationToken)`
- L382-398 _private* method_ `async Task UpdateMessageStateAsync(ObjectId stateId, SlackMessageId id, string? permalink = null, CancellationToken cancellationToken = default)`
- L403-414 _public method_ `public async Task NotifyJobScheduledAsync(List<JobScheduledNotification> notifications, CancellationToken cancellationToken)` — (inheritdoc)
- L416-448 _private method_ `private async Task SendJobScheduledOnEmptyAutoScaledPoolMessageAsync(string recipient, List<JobScheduledNotification> notifications, CancellationToken cancellationToken)`
- L453-468 _public method_ `public async Task NotifyJobCompleteAsync(IJob job, IGraph graph, LabelOutcome outcome, CancellationToken cancellationToken)` — (inheritdoc)
- L470-496 _private* method_ `async Task SendJobCompleteNotificationToChannelAsync(string notificationChannel, string? notificationFilter, StreamConfig streamConfig, IJob job, IGraph graph, LabelOutcome outcome, CancellationToken cancellationToken)`
- L499-512 _public method_ `public async Task NotifyJobCompleteAsync(IUser slackUser, IJob job, IGraph graph, LabelOutcome outcome, CancellationToken cancellationToken)` — (inheritdoc)
- L514-608 _private method_ `private async Task SendJobCompleteMessageAsync(string recipient, StreamConfig streamConfig, IJob job, IGraph graph, CancellationToken cancellationToken)`
- L615 _public method_ `public Task NotifyJobStepAbortedAsync(IEnumerable<IUser>? usersToNotify, IJob job, IJobStepBatch batch, IJobStep step, INode node, List<ILogEventData> jobStepEventData, CancellationToken cancellationToken)` — (inheritdoc)
- L619-660 _public method_ `public async Task NotifyJobStepCompleteAsync(IEnumerable<IUser>? usersToNotify, IJob job, IJobStepBatch batch, IJobStep step, INode node, List<ILogEventData> jobStepEventData, CancellationToken cancellationToken)` — (inheritdoc)
- L671-726 _private method_ `private Task SendJobStepCompleteMessageAsync(string recipient, IJob job, IJobStep step, INode node, List<ILogEventData> events, CancellationToken cancellationToken)` — Creates a Slack message about a completed step job.
- L733-747 _public method_ `public async Task NotifyLabelCompleteAsync(IUser user, IJob job, ILabel label, int labelIdx, LabelOutcome outcome, List<(string, JobStepOutcome, Uri)> stepData, CancellationToken cancellationToken)` — (inheritdoc)
- L749-791 _private* method_ `Task SendLabelUpdateMessageAsync(string recipient, StreamConfig streamConfig, IJob job, ILabel label, int labelIdx, LabelOutcome outcome, List<(string, JobStepOutcome, Uri)> jobStepData, CancellationToken cancellationToken)`
- L798-810 _public method_ `public async Task NotifyIssueUpdatedAsync(IIssue issue, CancellationToken cancellationToken)` — (inheritdoc)
- L816-833 _private* method_ `async ValueTask ProcessIssueQueueAsync(CancellationToken cancellationToken)` — Processes the issue queue
- L835-850 _private* method_ `async ValueTask<bool> TryUpdateIssueAsync(BuildConfig buildConfig, int issueId, CancellationToken cancellationToken)`
- L852-963 _private* method_ `async Task NotifyIssueUpdatedInternalAsync(BuildConfig buildConfig, int issueId, CancellationToken cancellationToken)`
- L965-986 _private* method_ `async Task<IIssueStep?> GetFixFailedStepAsync(IIssue issue, IEnumerable<IIssueSpan> spans, CancellationToken cancellationToken)`
- L988-1009 _private* method_ `async Task<IIssueSpan?> GetFixFailedSpanAsync(IIssue issue, IReadOnlyList<IIssueSpan> spans, CancellationToken cancellationToken)`
- L1011-1052 _private* method_ `async Task InviteUsersAsync(string channel, IEnumerable<UserId> userIds, bool inviteUsersAsAdmin, CancellationToken cancellationToken)`
- L1054 _private* method_ `static string GetTriageThreadEventId(int issueId)`
- L1069-1490 _private* method_ `async Task CreateOrUpdateWorkflowThreadAsync(string triageChannel, IIssue issue, IIssueSpan span, IReadOnlyList<IIssueSpan> spans, WorkflowConfig workflow, CancellationToken cancellationToken)`
- L1492-1582 _private method_ `private async Task UpdateReactionsAsync(string triageChannel, IIssue issue, IIssueSpan? fixFailedSpan, IReadOnlyList<IIssueSuspect> suspects, string eventId, SlackMessageId threadId, CancellationToken cancellationToken)`
- L1584-1594 _private* method_ `Uri? GetSwarmLinkForSpan(IIssueSpan span)`
- L1596-1606 _private* method_ `Uri? GetRobomergeTrackChangesUrlForSpan(IIssueSpan span)`
- L1608-1631 _private* method_ `Uri? GetCommitsViewerLinkForSpan(IIssueSpan span)`
- L1633-1641 _private* method_ `async Task PostSingleMessageToThreadAsync(string recipient, string eventId, SlackMessageId threadId, string message, CancellationToken cancellationToken)`
- L1644-1711 _public method_ `public async Task NotifyRcaCompleteAsync(int issueId, RcaResult result, CancellationToken cancellationToken)` — (inheritdoc)
- L1713 _private* const_ `const int MaxRunnerUpsInSlack = 3`
- L1714 _private* const_ `const int MaxReasonLength = 700`
- L1716 _private* method_ `static string TruncateReason(string reason)`
- L1719-1753 _private* method_ `string FormatAutoRcaMessage(RcaResult result)`
- L1755-1764 _private* method_ `async Task NotifyIssueUpdatedAsync(BuildConfig buildConfig, IUser user, IIssue issue, IIssueDetails details, CancellationToken cancellationToken)`
- L1766-1769 _private* method_ `Uri GetJobUrl(JobId jobId)`
- L1771-1774 _private* method_ `Uri GetStepUrl(JobId jobId, JobStepId stepId)`
- L1776-1779 _private* method_ `Uri GetIssueUrl(IIssue issue, IIssueStep step)`
- L1781-1963 _private* method_ `async Task SendIssueMessageAsync(BuildConfig buildConfig, string recipient, IIssue issue, IIssueDetails details, UserId? userId, bool allowMentions, CancellationToken cancellationToken)`
- L1965-1968 _private* method_ `static string GetIssueEventId(IIssue issue)`
- L1970-1973 _private* method_ `static string GetIssueEventId(IIssue issue, string recipient)`
- L1975-1983 _private* method_ `async Task<string> FormatNameAsync(UserId userId, CancellationToken cancellationToken)`
- L1985-2003 _private* method_ `static string GetDefaultUserName(UserId userId)`
- L2005-2017 _private* method_ `string FormatChange(CommitId change)`
- L2019-2024 _private* method_ `string FormatRobomergeTrackChangeLinkChange(CommitId change)`
- L2026 _private* method_ `string FormatJobStep(IIssueStep step, string name)`
- L2028-2039 _private* method_ `string FormatExternalIssue(string key)`
- L2041-2051 _private* method_ `static string FormatUserOrGroupMention(string userOrGroup)`
- L2053-2076 _private* method_ `async Task<string> FormatMentionAsync(UserId userId, bool allowMentions, CancellationToken cancellationToken)`
- L2078-2081 _private* method_ `static string FormatSlackTime(DateTimeOffset time)`
- L2107 _private* method_ `static string GetReportEventId(StreamId streamId, WorkflowId workflowId)`
- L2109 _private* method_ `static string GetReportBlockEventId(string ts, int idx)`
- L2112-2125 _public method_ `public async Task SendIssueReportAsync(IssueReportGroup group, CancellationToken cancellationToken)` — (inheritdoc)
- L2127-2235 _private* method_ `async Task SendIssueReportForStreamAsync(BuildConfig buildConfig, string channel, DateTime time, IssueReport report, CancellationToken cancellationToken)`
- L2237-2250 _private* method_ `static bool IsIssueOpenForWorkflow(StreamId streamId, TemplateId templateId, WorkflowId workflowId, IEnumerable<IIssueSpan> spans)`
- L2252-2335 _private* method_ `async Task UpdateReportsAsync(BuildConfig buildConfig, IIssue issue, IReadOnlyList<IIssueSpan> spans, CancellationToken cancellationToken)`
- L2337-2370 _private* method_ `async Task UpdateReportBlockAsync(string channel, string eventId, DateTime reportTime, StreamConfig streamConfig, TemplateId templateId, List<(IIssue, IIssueSpan?, bool)> issues, string? triageChannel, bool templateHeader, CancellationToken cancellationToken)`
- L2372-2375 _private* method_ `string GetSeverityPrefix(IssueSeverity severity)`
- L2377-2463 _private* method_ `async ValueTask<string> FormatIssueAsync(IIssue issue, IIssueSpan? span, string? triageChannel, DateTime reportTime, bool open, CancellationToken cancellationToken)`
- L2465-2480 _private* method_ `static string FormatReadableTimeSpan(TimeSpan timeSpan)`
- L2487-2584 _public method_ `public async Task NotifyConfigUpdateAsync(ConfigUpdateInfo info, CancellationToken cancellationToken)` — (inheritdoc)
- L2586-2600 _private* method_ `static string FormatConfigFileUri(Uri uri)`
- L2602-2613 _private* method_ `static string FormatConfigFileRevision(IConfigFile file)`
- L2616-2642 _public method_ `public async Task NotifyConfigUpdateFailureAsync(string errorMessage, string fileName, int? change = null, IUser? author = null, string? description = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L2644-2672 _private method_ `private async Task SendConfigUpdateFailureMessageAsync(string recipient, string errorMessage, string fileName, int? change = null, string? author = null, string? description = null, CancellationToken cancellationToken = default)`
- L2679-2798 _public method_ `public async Task SendDeviceIssueReportAsync(DeviceIssueReport report, CancellationToken cancellationToken)` — (inheritdoc)
- L2801-2823 _public method_ `public async Task NotifyDeviceServiceAsync(string message, IDevice? device = null, IDevicePool? pool = null, StreamConfig? streamConfig = null, IJob? job = null, IJobStep? step = null, INode? node = null, IUser? user = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L2838-2878 _private method_ `private Task SendDeviceServiceMessageAsync(string recipient, string message, IDevice? device = null, IDevicePool? pool = null, StreamConfig? streamConfig = null, IJob? job = null, IJobStep? step = null, INode? node = null, IUser? user = null, CancellationToken cancellationToken = default)` — Creates a Slack message for a device service notification
- L2885-2953 _public method_ `public async Task NotifyTestHealthReportAsync(ITestHealthReport report, string recipient, string[]? carbonCopies, CancellationToken cancellationToken)` — (inheritdoc)
- L2955-2965 _private* method_ `static string GenerateTestHealthSlackMessageTitle(ITestHealthReport report, StreamConfig streamConfig, string testHealthDetailsUrlLink)`
- L2967 _private* method_ `static string GetTestHealthEventId(ITestHealthReport report)`
- L2971-2987 _private* method_ `static string QuoteText(string text, int maxLength = MaxLineLength)`
- L2989 _private* const_ `const int MaxJobStepEvents = 5`
- L2991-3001 _private* method_ `static string GetJobChangeText(IJob job)`
- L3003-3020 _private* method_ `static bool ShouldUpdateUser(SlackUserDocument? document)`
- L3022-3025 _private method_ `private async Task<string?> GetSlackUserIdAsync(IUser user, CancellationToken cancellationToken)`
- L3027 _private field_ `private readonly HashSet<UserId> _usersWithoutEmail = new HashSet<UserId>()`
- L3029-3062 _private method_ `private async Task<SlackUserDocument?> GetSlackUserAsync(IUser user, CancellationToken cancellationToken)`
- L3064-3074 _private method_ `private async Task<SlackMessageId?> SendMessageAsync(string recipient, SlackMessage message, CancellationToken cancellationToken)`
- L3076-3084 _private* method_ `bool IsRecipientAllowed(string recipient, string? description)`
- L3086-3089 _private method_ `private async Task<(MessageStateDocument, bool)> SendOrUpdateMessageAsync(string recipient, string eventId, UserId? userId, SlackMessage message, CancellationToken cancellationToken)`
- L3091-3094 _private method_ `private static string GetMessageDigest(SlackMessage message)`
- L3096-3140 _private method_ `private async Task<(MessageStateDocument, bool)> SendOrUpdateMessageToThreadAsync(string recipient, string eventId, UserId? userId, SlackMessageId? threadId, SlackMessage message, CancellationToken cancellationToken)`
- L3142-3188 _private* method_ `async ValueTask EscalateAsync(CancellationToken cancellationToken)`
- L3190-3229 _private* method_ `async ValueTask EscalateIssuesForKeyAsync(RedisSortedSetKey<int> key, double time, DateTime utcNow, string notificationName, Func<int, DateTime, string, CancellationToken, Task<double?>> escalateSingleIssueAsync, CancellationToken cancellationToken)`
- L3231-3341 _private* method_ `async Task<double?> EscalateSingleIssueAsync(BuildConfig buildConfig, int issueId, DateTime utcNow, CancellationToken cancellationToken)`
- L3343-3448 _private* method_ `async Task<double?> EscalateSingleRootCauseAnalysisAsync(int issueId, DateTime utcNow, string notificationName, CancellationToken cancellationToken)`
- L3450-3475 _private* method_ `double GetNextEscalationTime(IIssue issue, DateTime whence, DateTime utcNow, List<int> escalationTimes, string notificationName)`
- L3478-3532 _private* method_ `async Task ExecuteAsync(CancellationToken stoppingToken)` — (inheritdoc)
- L3539-3558 _private method_ `private async Task<Uri?> GetWebSocketUrlAsync(CancellationToken stoppingToken)` — Get the url for opening a websocket to Slack
- L3566-3642 _private method_ `private async Task HandleSocketAsync(Uri socketUrl, CancellationToken stoppingToken)` — Handle the lifetime of a websocket connection
- L3646-3824 _private method_ `private async Task<object?> HandleInteractionMessageAsync(EventPayload payload, CancellationToken cancellationToken)` — Handle a button being clicked
- L3826-3839 _private* method_ `static bool TryMatch(string input, string pattern, [NotNullWhen(true)] out Match? match)`
- L3841-3872 _private* method_ `async Task HandleIssueDmResponseAsync(int issueId, string verb, UserId userId, string userName, CancellationToken cancellationToken)`
- L3874-4074 _private* method_ `async Task HandleIssueChannelResponseAsync(int issueId, string verb, string slackUserId, string triggerId, CancellationToken cancellationToken)`
- L4077-4137 _public method_ `public async Task SendAgentReportAsync(AgentReport report, CancellationToken cancellationToken)` — (inheritdoc)
- L4140-4162 _public method_ `public async Task SendSessionConflictReportAsync(IReadOnlyList<(AgentId Id, int Count)> conflicts, CancellationToken cancellationToken)` — (inheritdoc)
- L4164 _private* const_ `const string DeepLinkUrl = "https://slack.com/app_redirect"`
- L4165 _private* const_ `const int MaxDirectMessageUsers = 8`
- L4168-4204 _public method_ `public async Task<string?> GetDirectMessageLinkAsync(IReadOnlyList<UserId> userIds, CancellationToken cancellationToken)` — (inheritdoc)
- L4206-4221 _private* method_ `async Task<string?> GetSlackUserIdAsync(UserId userId, CancellationToken cancellationToken)`
- L4224-4227 _public method_ `public Task<string?> GetChannelLinkAsync(string channelId, CancellationToken cancellationToken)` — (inheritdoc)

#### class `HordeServer.Notifications.Sinks.SlackNotificationSink.SocketResponse`  
`class SocketResponse`  
_private*; L86-93_
- L89 _public property_ `public bool Ok { get; set; }` — attrs: `[JsonPropertyName("ok")]`
- L92 _public property_ `public Uri? Url { get; set; }` — attrs: `[JsonPropertyName("url")]`

#### class `HordeServer.Notifications.Sinks.SlackNotificationSink.EventMessage`  
`class EventMessage`  
_private*; L95-105_
- L98 _public property_ `public string? EnvelopeId { get; set; }` — attrs: `[JsonPropertyName("envelope_id")]`
- L101 _public property_ `public string? Type { get; set; }` — attrs: `[JsonPropertyName("type")]`
- L104 _public property_ `public EventPayload? Payload { get; set; }` — attrs: `[JsonPropertyName("payload")]`

#### class `HordeServer.Notifications.Sinks.SlackNotificationSink.EventResponse`  
`class EventResponse`  
_private*; L107-114_
- L110 _public property_ `public string? EnvelopeId { get; set; }` — attrs: `[JsonPropertyName("envelope_id")]`
- L113 _public property_ `public object? Payload { get; set; }` — attrs: `[JsonPropertyName("payload")]`

#### class `HordeServer.Notifications.Sinks.SlackNotificationSink.EventPayload`  
`class EventPayload`  
_private*; L116-135_
- L119 _public property_ `public string? Type { get; set; }` — attrs: `[JsonPropertyName("type")]`
- L122 _public property_ `public string? TriggerId { get; set; }` — attrs: `[JsonPropertyName("trigger_id")]`
- L125 _public property_ `public SlackUser? User { get; set; }` — attrs: `[JsonPropertyName("user")]`
- L128 _public property_ `public string? ResponseUrl { get; set; }` — attrs: `[JsonPropertyName("response_url")]`
- L131 _public property_ `public List<ActionInfo> Actions { get; set; }` — attrs: `[JsonPropertyName("actions")]`
- L134 _public property_ `public SlackView? View { get; set; }` — attrs: `[JsonPropertyName("view")]`

#### class `HordeServer.Notifications.Sinks.SlackNotificationSink.ActionInfo`  
`class ActionInfo`  
_private*; L137-147_
- L140 _public property_ `public string BlockId { get; set; }` — attrs: `[JsonPropertyName("blockId")]`
- L143 _public property_ `public string ActionId { get; set; }` — attrs: `[JsonPropertyName("action_id")]`
- L146 _public property_ `public string Value { get; set; }` — attrs: `[JsonPropertyName("value")]`

#### class `HordeServer.Notifications.Sinks.SlackNotificationSink.MessageStateDocument`  
`class MessageStateDocument`  
_private*; L149-177_
- L152 _public property_ `public ObjectId Id { get; set; }` — attrs: `[BsonId]`
- L155 _public property_ `public string Recipient { get; set; }` — attrs: `[BsonElement("uid")]`
- L158 _public property_ `public UserId? UserId { get; set; }` — attrs: `[BsonElement("usr")]`
- L161 _public property_ `public string EventId { get; set; }` — attrs: `[BsonElement("eid")]`
- L164 _public property_ `public string Channel { get; set; }` — attrs: `[BsonElement("ch")]`
- L167 _public property_ `public string Ts { get; set; }` — attrs: `[BsonElement("ts")]`
- L170 _public property_ `public string Digest { get; set; }` — attrs: `[BsonElement("dig")]`
- L173 _public property_ `public string? Permalink { get; set; }` — attrs: `[BsonElement("lnk"), BsonIgnoreIfNull]`
- L176 _public property_ `public SlackMessageId MessageId => ...` — attrs: `[BsonIgnore]`

#### class `HordeServer.Notifications.Sinks.SlackNotificationSink.SlackUserDocument`  
`class SlackUserDocument : IAvatar`  
_private*; L179-224_
- inherits: `IAvatar`
- L181 _public const_ `public const int CurrentVersion = 2`
- L183 _public property_ `public UserId Id { get; set; }`
- L186 _public property_ `public string? SlackUserId { get; set; }` — attrs: `[BsonElement("u")]`
- L189 _public property_ `public string? Image24 { get; set; }` — attrs: `[BsonElement("i24")]`
- L192 _public property_ `public string? Image32 { get; set; }` — attrs: `[BsonElement("i32")]`
- L195 _public property_ `public string? Image48 { get; set; }` — attrs: `[BsonElement("i48")]`
- L198 _public property_ `public string? Image72 { get; set; }` — attrs: `[BsonElement("i72")]`
- L201 _public property_ `public DateTime Time { get; set; }` — attrs: `[BsonElement("t")]`
- L204 _public property_ `public int Version { get; set; }` — attrs: `[BsonElement("v")]`
- L206-208 _private ctor_ `private SlackUserDocument()`
- L210-223 _public ctor_ `public SlackUserDocument(UserId id, SlackUser? info)`

#### enum `HordeServer.Notifications.Sinks.SlackNotificationSink.ReactionFlags`  
`enum ReactionFlags`  
_private*; L1057-1066_
- attrs: `[Flags]`
- L1059 _public* enumerator_ `None = 0`
- L1060 _public* enumerator_ `Acknowledged = 1`
- L1061 _public* enumerator_ `Quarantined = 2`
- L1062 _public* enumerator_ `FixFailed = 4`
- L1063 _public* enumerator_ `Resolved = 8`
- L1064 _public* enumerator_ `AssignedButNotAcknowledged = 16`
- L1065 _public* enumerator_ `NoSuspects = 32`

#### class `HordeServer.Notifications.Sinks.SlackNotificationSink.ReportBlock`  
`class ReportBlock`  
_private*; L2083-2096_
- L2086 _public property_ `public bool TemplateHeader { get; set; }` — attrs: `[JsonPropertyName("h")]`
- L2089 _public property_ `public StreamId StreamId { get; set; }` — attrs: `[JsonPropertyName("s")]`
- L2092 _public property_ `public TemplateId TemplateId { get; set; }` — attrs: `[JsonPropertyName("t")]`
- L2095 _public property_ `public List<int> IssueIds { get; set; }` — attrs: `[JsonPropertyName("i")]`

#### class `HordeServer.Notifications.Sinks.SlackNotificationSink.ReportState`  
`class ReportState`  
_private*; L2098-2105_
- L2101 _public property_ `public DateTime Time { get; set; }` — attrs: `[JsonPropertyName("tm")]`
- L2104 _public property_ `public List<ReportBlock> Blocks { get; set; }` — attrs: `[JsonPropertyName("msg")]`

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Notifications/SubscriptionCollection.cs` (HordeServer.Build)


#### class `HordeServer.Notifications.SubscriptionCollection`  
`public class SubscriptionCollection : ISubscriptionCollection`  
_public; L20-238_
- inherits: `ISubscriptionCollection`
- desc: Collection of subscription documents
- L175 _private* field_ `readonly IMongoCollection<Subscription> _collection`
- L181-187 _public ctor_ `public SubscriptionCollection(IMongoService mongoService)` — Constructor
- L190-208 _public method_ `public async Task<List<ISubscription>> AddAsync(IEnumerable<NewSubscription> newSubscriptions)` — (inheritdoc)
- L211-215 _public method_ `public async Task RemoveAsync(IEnumerable<ISubscription> subscriptions)` — (inheritdoc)
- L218-222 _public method_ `public async Task<ISubscription?> GetAsync(string subscriptionId)` — (inheritdoc)
- L225-230 _public method_ `public async Task<List<ISubscription>> FindSubscribersAsync(EventRecord eventRecord)` — (inheritdoc)
- L233-237 _public method_ `public async Task<List<ISubscription>> FindSubscriptionsAsync(UserId userId)` — (inheritdoc)

#### class `HordeServer.Notifications.SubscriptionCollection.Event`  
`abstract class Event : IEvent`  
_private*; L23-49_
- attrs: `[BsonKnownTypes(typeof(JobCompleteEvent), typeof(LabelCompleteEvent), typeof(StepCompleteEvent))]`
- inherits: `IEvent`
- L25-46 _public method_ `public static Event FromRecord(EventRecord record)`
- L48 _public method_ `public abstract EventRecord ToRecord()`

#### class `HordeServer.Notifications.SubscriptionCollection.JobCompleteEvent`  
`class JobCompleteEvent : Event, IJobCompleteEvent`  
_private*; L51-77_
- inherits: `Event, IJobCompleteEvent`
- L53 _public property_ `public StreamId StreamId { get; set; }`
- L54 _public property_ `public TemplateId TemplateId { get; set; }`
- L55 _public property_ `public LabelOutcome Outcome { get; set; }`
- L57-59 _public ctor_ `public JobCompleteEvent()`
- L61-66 _public ctor_ `public JobCompleteEvent(JobCompleteEventRecord record)`
- L68-71 _public method_ `public override EventRecord ToRecord()`
- L73-76 _public method_ `public override string ToString()`

#### class `HordeServer.Notifications.SubscriptionCollection.LabelCompleteEvent`  
`class LabelCompleteEvent : Event, ILabelCompleteEvent`  
_private*; L79-117_
- inherits: `Event, ILabelCompleteEvent`
- L81 _public property_ `public StreamId StreamId { get; set; }`
- L82 _public property_ `public TemplateId TemplateId { get; set; }`
- L83 _public property_ `public string? CategoryName { get; set; }`
- L84 _public property_ `public string LabelName { get; set; }`
- L85 _public property_ `public LabelOutcome Outcome { get; set; }`
- L87-90 _public ctor_ `public LabelCompleteEvent()`
- L92-99 _public ctor_ `public LabelCompleteEvent(LabelCompleteEventRecord record)`
- L101-104 _public method_ `public override EventRecord ToRecord()`
- L106-116 _public method_ `public override string ToString()`

#### class `HordeServer.Notifications.SubscriptionCollection.StepCompleteEvent`  
`class StepCompleteEvent : Event, IStepCompleteEvent`  
_private*; L119-148_
- inherits: `Event, IStepCompleteEvent`
- L121 _public property_ `public StreamId StreamId { get; set; }`
- L122 _public property_ `public TemplateId TemplateId { get; set; }`
- L123 _public property_ `public string StepName { get; set; }`
- L124 _public property_ `public JobStepOutcome Outcome { get; set; }`
- L126-129 _public ctor_ `public StepCompleteEvent()`
- L131-137 _public ctor_ `public StepCompleteEvent(StepCompleteEventRecord record)`
- L139-142 _public method_ `public override EventRecord ToRecord()`
- L144-147 _public method_ `public override string ToString()`

#### class `HordeServer.Notifications.SubscriptionCollection.Subscription`  
`class Subscription : ISubscription`  
_private*; L150-173_
- inherits: `ISubscription`
- L152 _public property_ `public string Id { get; set; }`
- L153 _public property_ `public Event Event { get; set; }`
- L154 _public property_ `public UserId UserId { get; set; }`
- L155 _public property_ `public NotificationType NotificationType { get; set; }`
- L157 _private* property_ `IEvent ISubscription.Event => ...`
- L160-164 _private ctor_ `private Subscription()` — attrs: `[BsonConstructor]`
- L166-172 _public ctor_ `public Subscription(NewSubscription subscription)`

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Notifications/SubscriptionMessages.cs` (HordeServer.Build)


#### class `HordeServer.Notifications.CreateSubscriptionRequest`  
`public class CreateSubscriptionRequest`  
_public; L14-32_
- desc: Request object for creating a new subscription
- L20 _public property_ `public EventRecord Event { get; set; }` — attrs: `[Required]` — The event to create a subscription for
- L26 _public property_ `public string UserId { get; set; }` — attrs: `[Required]` — The user to subscribe. Defaults to the current user if unspecified.
- L31 _public property_ `public NotificationType NotificationType { get; set; }` — Type of notification to send

#### class `HordeServer.Notifications.CreateSubscriptionResponse`  
`public class CreateSubscriptionResponse`  
_public; L37-52_
- desc: Response from creating a subscription
- L42 _public property_ `public string Id { get; set; }` — The subscription id
- L48-51 _public ctor_ `public CreateSubscriptionResponse(ISubscription subscription)` — Constructor

#### class `HordeServer.Notifications.GetSubscriptionResponse`  
`public class GetSubscriptionResponse`  
_public; L57-90_
- desc: Response describing a subscription
- L62 _public property_ `public string Id { get; set; }` — The subscription id
- L67 _public property_ `public EventRecord Event { get; set; }` — Information about the specific event
- L72 _public property_ `public string UserId { get; set; }` — Unique id of the user subscribed to the event
- L77 _public property_ `public NotificationType NotificationType { get; set; }` — The type of notification to receive
- L83-89 _public ctor_ `public GetSubscriptionResponse(ISubscription subscription)` — Constructor

#### class `HordeServer.Notifications.EventRecord`  
`public class EventRecord`  
_public; L96-98_
- attrs: `[JsonKnownTypes(typeof(JobCompleteEventRecord), typeof(LabelCompleteEventRecord), typeof(StepCompleteEventRecord))]`
- desc: Base class for event records

#### class `HordeServer.Notifications.JobCompleteEventRecord`  
`public class JobCompleteEventRecord : EventRecord`  
_public; L104-144_
- attrs: `[JsonDiscriminator("Job")]`
- inherits: `EventRecord`
- desc: Event that occurs when a job completes
- L110 _public property_ `public string StreamId { get; set; }` — attrs: `[Required]` — The stream id
- L116 _public property_ `public string TemplateId { get; set; }` — attrs: `[Required]` — The template id
- L121 _public property_ `public LabelOutcome Outcome { get; set; }` — Outcome of the job
- L126-130 _public ctor_ `public JobCompleteEventRecord()` — Default constructor
- L138-143 _public ctor_ `public JobCompleteEventRecord(StreamId streamId, TemplateId templateId, LabelOutcome outcome)` — Constructor

#### class `HordeServer.Notifications.LabelCompleteEventRecord`  
`public class LabelCompleteEventRecord : EventRecord`  
_public; L150-206_
- attrs: `[JsonDiscriminator("Label")]`
- inherits: `EventRecord`
- desc: Event that occurs when a label completes
- L156 _public property_ `public string StreamId { get; set; }` — attrs: `[Required]` — The stream id
- L162 _public property_ `public string TemplateId { get; set; }` — attrs: `[Required]` — The template id
- L167 _public property_ `public string? CategoryName { get; set; }` — Name of the category for this label
- L173 _public property_ `public string LabelName { get; set; }` — attrs: `[Required]` — Name of the label to monitor
- L178 _public property_ `public LabelOutcome Outcome { get; set; }` — Outcome of the job
- L183-188 _public ctor_ `public LabelCompleteEventRecord()` — Default constructor
- L198-205 _public ctor_ `public LabelCompleteEventRecord(StreamId streamId, TemplateId templateId, string? categoryName, string labelName, LabelOutcome outcome)` — Constructor

#### class `HordeServer.Notifications.StepCompleteEventRecord`  
`public class StepCompleteEventRecord : EventRecord`  
_public; L212-261_
- attrs: `[JsonDiscriminator("Step")]`
- inherits: `EventRecord`
- desc: Event that occurs when a step completes
- L218 _public property_ `public string StreamId { get; set; }` — attrs: `[Required]` — The stream id
- L224 _public property_ `public string TemplateId { get; set; }` — attrs: `[Required]` — The template id
- L230 _public property_ `public string StepName { get; set; }` — attrs: `[Required]` — Name of the step to monitor
- L235 _public property_ `public JobStepOutcome Outcome { get; set; }` — Outcome of the job step
- L240-245 _public ctor_ `public StepCompleteEventRecord()` — Default constructor
- L254-260 _public ctor_ `public StepCompleteEventRecord(StreamId streamId, TemplateId templateId, string stepName, JobStepOutcome outcome)` — Constructor

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Notifications/SubscriptionsController.cs` (HordeServer.Build)


#### class `HordeServer.Notifications.SubscriptionsController`  
`public class SubscriptionsController : ControllerBase`  
_public; L18-161_
- attrs: `[ApiController] [Authorize] [Route("[controller]")]`
- inherits: `ControllerBase`
- desc: Controller for the /api/v1/agents endpoint
- L20 _private* field_ `readonly ISubscriptionCollection _subscriptionCollection`
- L21 _private* field_ `readonly IOptionsSnapshot<BuildConfig> _buildConfig`
- L26-30 _public ctor_ `public SubscriptionsController(ISubscriptionCollection subscriptionCollection, IOptionsSnapshot<BuildConfig> buildConfig)` — Constructor
- L41-55 _public method_ `public async Task<ActionResult<List<object>>> GetSubscriptionsAsync([FromQuery] string userId, [FromQuery] PropertyFilter? filter = null)` — attrs: `[HttpGet] [Route("/api/v1/subscriptions")] [ProducesResponseType(typeof(List<GetSubscriptionResponse>), 200)]` — Find subscriptions matching a criteria
- L66-79 _public method_ `public async Task<ActionResult<object>> GetSubscriptionAsync(string subscriptionId, [FromQuery] PropertyFilter? filter = null)` — attrs: `[HttpGet] [Route("/api/v1/subscriptions/{subscriptionId}")] [ProducesResponseType(typeof(GetSubscriptionResponse), 200)]` — Find subscriptions matching a criteria
- L89-103 _public method_ `public async Task<ActionResult> DeleteSubscriptionAsync(string subscriptionId)` — attrs: `[HttpDelete] [Route("/api/v1/subscriptions/{subscriptionId}")] [ProducesResponseType(typeof(List<GetSubscriptionResponse>), 200)]` — Remove a subscription
- L112-139 _public method_ `public async Task<ActionResult<List<CreateSubscriptionResponse>>> CreateSubscriptionsAsync(List<CreateSubscriptionRequest> subscriptions)` — attrs: `[HttpPost] [Route("/api/v1/subscriptions")]` — Find subscriptions matching a criteria
- L147-160 _private* method_ `static bool TryParseUserId(string userName, out UserId objectId)` — Parse a user id from a string. Allows passing the user's name as well as their objectid value.

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Projects/ProjectAclAction.cs` (HordeServer.Build)


#### class `HordeServer.Projects.ProjectAclAction`  
`public static class ProjectAclAction`  
_public; L10-31_
- desc: ACL actions that can be performed on projects
- L15 _public property_ `public static AclAction CreateProject { get; }` — Allows the creation of new projects
- L20 _public property_ `public static AclAction DeleteProject { get; }` — Allows deletion of projects.
- L25 _public property_ `public static AclAction UpdateProject { get; }` — Modify attributes of a project (name, categories, etc...)
- L30 _public property_ `public static AclAction ViewProject { get; }` — View information about a project

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Projects/ProjectConfig.cs` (HordeServer.Build)


#### class `HordeServer.Projects.ProjectConfig`  
`public class ProjectConfig`  
_public; L35-167_
- attrs: `[JsonSchema("https://unrealengine.com/horde/project")] [JsonSchemaCatalog("Horde Project", "Horde project configuration file", new[] { "*.project.json", "Projects/*.json" })] [ConfigDoc("*.project.json", "[Horde](../../../README.md) > [Configuration](../../Config.md)", "Config/Schema/Projects.md")] [ConfigIncludeRoot] [ConfigMacroScope] [DebuggerDisplay("{Id}")]`
- desc: Stores configuration for a project
- L40 _public property_ `public ProjectId Id { get; set; }` — The project id
- L45 _public property_ `public string Name { get; set; }` — Name for the new project
- L51 _public property_ `public string? Path { get; set; }` — attrs: `[ConfigInclude, ConfigRelativePath]` — Direct include path for the project config. For backwards compatibility with old config files when including from a GlobalConfig object.
- L56 _public property_ `public List<ConfigInclude> Include { get; set; }` — Includes for other configuration files
- L61 _public property_ `public List<ConfigMacro> Macros { get; set; }` — Macros within the global scope
- L66 _public property_ `public int Order { get; set; }` — Order of this project on the dashboard
- L71 _public property_ `public ConfigResource? Logo { get; set; }` — Path to the project logo
- L76 _public property_ `public ConfigResource? LogoDarkTheme { get; set; }` — Optional path to the project logo for the dark theme
- L81 _public property_ `public List<PoolConfig> Pools { get; set; }` — List of pools for this project
- L86 _public property_ `public List<ProjectCategoryConfig> Categories { get; set; }` — Categories to include in this project
- L91 _public property_ `public JobOptions JobOptions { get; set; }` — Default settings for executing jobs
- L96 _public property_ `public RetentionOptions RetentionOptions { get; set; }` — Default storage retention options for all streams in this project
- L102 _public property_ `public Dictionary<string, WorkspaceConfig> WorkspaceTypes { get; set; }` — Default workspace types for streams These are added to the list of each stream's workspace types.
- L109 _public property_ `public List<string>? IgnorePatternFiles { get; set; }` — Additional ignore pattern files applied to all streams in this project. Streams can append additional files via their own IgnorePatternFiles property. Paths are relative to workspace root.
- L114 _public property_ `public TelemetryStoreId TelemetryStoreId { get; set; }` — Telemetry store for Horde data for this project
- L119 _public property_ `public List<StreamConfig> Streams { get; set; }` — List of streams
- L124 _public property_ `public List<ArtifactTypeConfig> ArtifactTypes { get; set; }` — Permissions for artifact types
- L129 _public property_ `public AclConfig Acl { get; set; }` — Acl entries
- L131 _private* field_ `readonly Dictionary<ArtifactType, ArtifactTypeConfig> _artifactTypeLookup = ...`
- L131 _private* field_ `readonly Dictionary< _artifactTypeLookup = new Dictionary<ArtifactType, ArtifactTypeConfig>()`
- L134 _public method_ `public bool Authorize(AclAction action, ClaimsPrincipal user)` — (inheritdoc)
- L144-166 _public method_ `public void PostLoad(ProjectId id, AclConfig parentAcl, IEnumerable<ArtifactTypeConfig> parentArtifactTypes, ILogger? logger)` — Callback after this configuration has been read

#### class `HordeServer.Projects.ProjectCategoryConfig`  
`public class ProjectCategoryConfig`  
_public; L172-199_
- desc: Information about a category to display for a stream
- L178 _public property_ `public string Name { get; set; }` — attrs: `[Required]` — Name of this category
- L183 _public property_ `public int Row { get; set; }` — Index of the row to display this category on
- L188 _public property_ `public bool ShowOnNavMenu { get; set; }` — Whether to show this category on the nav menu
- L193 _public property_ `public List<string> IncludePatterns { get; set; }` — Patterns for stream names to include
- L198 _public property_ `public List<string> ExcludePatterns { get; set; }` — Patterns for stream names to exclude

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Projects/ProjectsController.cs` (HordeServer.Build)


#### class `HordeServer.Projects.ProjectsController`  
`public class ProjectsController : HordeControllerBase`  
_public; L22-201_
- attrs: `[ApiController] [Authorize] [CppApi] [Route("[controller]")]`
- inherits: `HordeControllerBase`
- desc: Controller for the /api/v1/projects endpoint
- L24 _private field_ `private readonly IOptionsSnapshot<BuildConfig> _buildConfig`
- L26 _private field_ `private static readonly FileExtensionContentTypeProvider s_contentTypeProvider = new FileExtensionContentTypeProvider()`
- L31-34 _public ctor_ `public ProjectsController(IOptionsSnapshot<BuildConfig> buildConfig)` — Constructor
- L46-64 _public method_ `public ActionResult<List<object>> GetProjects([FromQuery(Name = "Streams")] bool includeStreams = false, [FromQuery(Name = "Categories")] bool includeCategories = false, [FromQuery] PropertyFilter? filter = null)` — attrs: `[HttpGet] [Route("/api/v1/projects")] [ProducesResponseType(typeof(List<GetProjectResponse>), 200)]` — Query all the projects
- L75-97 _public method_ `public ActionResult<object> GetProject(ProjectId projectId, [FromQuery] PropertyFilter? filter = null)` — attrs: `[HttpGet] [Route("/api/v1/projects/{projectId}")] [ProducesResponseType(typeof(List<GetProjectResponse>), 200)]` — Retrieve information about a specific project
- L107-132 _public method_ `public ActionResult<object> GetProjectLogo(ProjectId projectId, [FromQuery] bool darkTheme = false)` — attrs: `[HttpGet] [Route("/api/v1/projects/{projectId}/logo")]` — Retrieve information about a specific project
- L136-176 _internal method_ `internal static GetProjectResponse CreateGetProjectResponse(ProjectConfig projectConfig, bool includeStreams, bool includeCategories, List<StreamConfig>? streamConfigs)`
- L178-185 _internal method_ `internal static GetProjectCategoryResponse CreateGetProjectCategoryResponse(ProjectCategoryConfig streamCategory)`
- L188-198 _private* method_ `static bool MatchCategory(string name, GetProjectCategoryResponse category)`

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Properties/AssemblyInfo.cs` (HordeServer.Build)
_(no declarations)_


### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Replicators/IReplicator.cs` (HordeServer.Build)


#### interface `HordeServer.Replicators.IReplicator`  
`public interface IReplicator`  
_public; L10-106_
- desc: Snapshot of the state for a replicator; a process which transfers data from an external source control provider into Horde.
- L15 _public* property_ `ReplicatorId Id { get; }` — Identifier for this replicator
- L22 _public* property_ `bool Pause { get; }` — Whether replication is paused
- L27 _public* property_ `bool Clean { get; }` — Whether to take a clean snapshot from the current change rather than intermentally syncing from the previous change
- L32 _public* property_ `bool Reset { get; }` — Whether to reset the change history from the current change
- L37 _public* property_ `bool SingleStep { get; }` — Pauses replication after the current change
- L42 _public* property_ `int? NextChange { get; }` — The next change to replicate, requested by the user.
- L51 _public* property_ `int? LastChange { get; }` — The last change that was replicated
- L56 _public* property_ `DateTime? LastChangeFinishTime { get; }` — Time at which the last change was replicated
- L61 _public* property_ `int? CurrentChange { get; }` — The current change being replicated. May be null if no change is currently being replicated.
- L66 _public* property_ `DateTime? CurrentChangeStartTime { get; }` — Time at which the current change was replicated
- L71 _public* property_ `long? CurrentSize { get; }` — Total size of data to be replicated for the current change
- L76 _public* property_ `long? CurrentCopiedSize { get; }` — Size of data that has been replicated for the current change
- L81 _public* property_ `string? CurrentError { get; }` — Last error with replication, if there is one.
- L90 _public* method_ `Task<IReplicator?> RefreshAsync(CancellationToken cancellationToken = default)` — Refreshes the replicator, ensuring it's the latest version
- L97 _public* method_ `Task<bool> TryDeleteAsync(CancellationToken cancellationToken = default)` — Attempts to delete the replicator.
- L105 _public* method_ `Task<IReplicator?> TryUpdateAsync(UpdateReplicatorOptions options, CancellationToken cancellationToken = default)` — Attempt to update the replicator

#### record `HordeServer.Replicators.UpdateReplicatorOptions`  
`public record class UpdateReplicatorOptions(bool? Pause = null, bool? Clean = null, bool? Reset = null, bool? SingleStep = null, int? LastChange = null, int? NextChange = null, int? CurrentChange = null, long? CurrentSize = null, long? CurrentCopiedSize = null, string? CurrentError = null)`  
_public; L111-111_
- desc: Parameters for updating IReplicator

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Replicators/IReplicatorCollection.cs` (HordeServer.Build)


#### interface `HordeServer.Replicators.IReplicatorCollection`  
`public interface IReplicatorCollection`  
_public; L10-34_
- desc: Interface for a collection of replicators
- L17 _public* method_ `Task<List<IReplicator>> FindAsync(CancellationToken cancellationToken = default)` — Finds all replicators
- L25 _public* method_ `Task<IReplicator?> GetAsync(ReplicatorId id, CancellationToken cancellationToken = default)` — Gets the state of a replicator from the collection
- L33 _public* method_ `Task<IReplicator> GetOrAddAsync(ReplicatorId id, CancellationToken cancellationToken = default)` — Gets the state of a replicator or adds a new one to the collection

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Replicators/PerforceReplicator.cs` (HordeServer.Build)


#### class `HordeServer.Replicators.ReplicatorModifiedException`  
`public class ReplicatorModifiedException : Exception`  
_public; L24-29_
- inherits: `Exception`
- desc: Exception thrown to indicate that the state of a replicator has been modified externally
- L26-28 _internal ctor_ `internal ReplicatorModifiedException() : base("The replicator has been modified externally")`

#### class `HordeServer.Replicators.PerforceReplicator`  
`public class PerforceReplicator`  
_public; L34-928_
- desc: Replicates commits from Perforce into Horde's internal storage
- L116 _private* const_ `const uint FST_BINARY = 0x0002`
- L118 _private* const_ `const uint FST_UTF16 = 0x000e`
- L120 _private* const_ `const uint FST_MASK = 0x000f`
- L123 _private* const_ `const uint FPM_RO = 0`
- L125 _private* const_ `const uint FPM_ROO = 2`
- L126 _private* const_ `const uint FPM_RXO = 3`
- L128 _private* const_ `const uint FPM_RWXO = 5`
- L258 _private* field_ `readonly Dictionary<StreamId, ReplicationClient> _cachedPerforceClients = ...`
- L258 _private* field_ `readonly Dictionary< _cachedPerforceClients = new Dictionary<StreamId, ReplicationClient>()`
- L260 _private* field_ `readonly IPerforceService _perforceService`
- L261 _private* field_ `readonly StorageService _storageService`
- L262 _private* field_ `readonly IReplicatorCollection _replicatorCollection`
- L263 _private* field_ `readonly ILogger _logger`
- L268-274 _public ctor_ `public PerforceReplicator(IPerforceService perforceService, StorageService storageService, IReplicatorCollection replicatorCollection, ILogger<PerforceReplicator> logger)` — Constructor
- L281 _public method_ `public static RefName GetRefName(ReplicatorId replicatorId)` — Gets the ref name for a given stream
- L288 _private* method_ `static RefName GetIncrementalRefName(ReplicatorId replicatorId)` — Gets the ref name for a given stream
- L293-308 _public method_ `public async Task RunAsync(ReplicatorId replicatorId, BuildConfig buildConfig, StreamConfig streamConfig, ReplicatorConfig replicatorConfig, CancellationToken cancellationToken = default)` — Runs a replication loop for a stream
- L313-393 _public method_ `public async Task<IReplicator> RunOnceAsync(IReplicator replicator, BuildConfig buildConfig, StreamConfig streamConfig, ReplicatorConfig replicatorConfig, CancellationToken cancellationToken)` — Runs the replicator for a single change
- L395-757 _private* method_ `async Task<IReplicator> WriteInternalAsync(IReplicator replicator, int change, BuildConfig buildConfig, StreamConfig streamConfig, ReplicatorConfig replicatorConfig, BlobSerializerOptions blobOptions, CancellationToken cancellationToken = default)`
- L759-763 _private* method_ `static async Task<IReplicator> UpdateReplicatorAsync(IReplicator replicator, UpdateReplicatorOptions options, CancellationToken cancellationToken)`
- L765-773 _private* method_ `static int GetFileOffset(string path)`
- L775-803 _private* method_ `static DirectoryToSync FindOrAddDirectoryTree(Dictionary<string, DirectoryToSync> pathToDirectory, string directoryPath, StringComparer comparer)`
- L805 _private* method_ `static string NormalizePathSeparators(string path)`
- L807-824 _private* method_ `async Task FlushWorkspaceAsync(ReplicationClient clientInfo, IPerforceConnection perforce, int change, CancellationToken cancellationToken)`
- L826-838 _private* method_ `static void UnpackOpenPayload(ReadOnlyMemory<byte> data, out Utf8String path, out int flags, out int type, out int perms)`
- L840-848 _private* method_ `static void UnpackUnlinkPayload(ReadOnlyMemory<byte> data, out string path)`
- L850-857 _private* method_ `static string GetClientRelativePath(string path, string clientRoot)`
- L859-877 _private* method_ `async Task<ReplicationClient?> FindReplicationClientAsync(StreamConfig streamConfig, CancellationToken cancellationToken)`
- L879-927 _private* method_ `async Task<ReplicationClient> FindOrAddReplicationClientAsync(BuildConfig buildConfig, StreamConfig streamConfig, CancellationToken cancellationToken = default)`

#### class `HordeServer.Replicators.PerforceReplicator.StateNode`  
`class StateNode`  
_private*; L37-55_
- attrs: `[BlobConverter(typeof(StateNodeConverter))]`
- L39 _public property_ `public int Change { get; }`
- L40 _public property_ `public int ParentChange { get; }`
- L41 _public property_ `public IHashedBlobRef<CommitNode>? ParentHandle { get; }`
- L42 _public property_ `public long CopiedSize { get; set; }`
- L43 _public property_ `public IHashedBlobRef<DirectoryNode>? Contents { get; set; }`
- L44 _public property_ `public List<string> Paths { get; }`
- L46-54 _public ctor_ `public StateNode(int number, int parentNumber, IHashedBlobRef<CommitNode>? parentHandle, long copiedSize, IHashedBlobRef<DirectoryNode>? contents, List<string>? paths = null)`

#### class `HordeServer.Replicators.PerforceReplicator.StateNodeConverter`  
`class StateNodeConverter : BlobConverter<StateNode>`  
_private*; L57-112_
- inherits: `BlobConverter<StateNode>`
- L59 _private* field_ `static readonly BlobType s_blobType = new BlobType("{8C874966-4273-2E89-9FAC-ABA46DC89154}", 2)`
- L61-86 _public method_ `public override StateNode Read(IBlobReader reader, BlobSerializerOptions options)`
- L89-111 _public method_ `public override BlobType Write(IBlobWriter writer, StateNode value, BlobSerializerOptions options)` — (inheritdoc)

#### class `HordeServer.Replicators.PerforceReplicator.DirectoryToSync`  
`class DirectoryToSync`  
_private*; L131-142_
- attrs: `[DebuggerDisplay("{Path}")]`
- L133 _public field_ `public readonly string Path`
- L134 _public field_ `public readonly Dictionary<string, long> FileNameToSize`
- L134 _public field_ `public readonly Dictionary< FileNameToSize`
- L135 _public field_ `public long _size`
- L137-141 _public ctor_ `public DirectoryToSync(string path, StringComparer comparer)`

#### record `HordeServer.Replicators.PerforceReplicator.FileInfo`  
`record class FileInfo(string Path, FileEntryFlags Flags, long Length, byte[] Md5, LeafChunkedData LeafChunkedData)`  
_private*; L144-144_

#### class `HordeServer.Replicators.PerforceReplicator.FileWriter`  
`class FileWriter : IDisposable`  
_private*; L146-238_
- inherits: `IDisposable`
- L170 _private* field_ `readonly IBlobWriter _writer`
- L171 _private* field_ `readonly LeafChunkedDataNodeOptions _options`
- L172 _private* field_ `readonly Stack<Handle> _freeHandles = new Stack<Handle>()`
- L173 _private* field_ `readonly Dictionary<int, Handle> _openHandles = ...`
- L173 _private* field_ `readonly Dictionary< _openHandles = new Dictionary<int, Handle>()`
- L174 _private* field_ `readonly ILogger _logger`
- L176-181 _public ctor_ `public FileWriter(IBlobWriter writer, LeafChunkedDataNodeOptions options, ILogger logger)`
- L183-193 _public method_ `public void Dispose()`
- L195-210 _public method_ `public void Open(int fd, string path, long size, FileEntryFlags flags)`
- L212-219 _public method_ `public async Task AppendAsync(int fd, ReadOnlyMemory<byte> data, CancellationToken cancellationToken)`
- L221-237 _public method_ `public async Task<FileInfo> CloseAsync(int fd, CancellationToken cancellationToken)`

#### class `HordeServer.Replicators.PerforceReplicator.FileWriter.Handle`  
`class Handle : IDisposable`  
_private*; L148-168_
- inherits: `IDisposable`
- L150 _public field_ `public string? _path`
- L151 _public field_ `public FileEntryFlags _flags`
- L152 _public field_ `public readonly LeafChunkedDataWriter FileWriter`
- L153 _public field_ `public long _size`
- L154 _public field_ `public long _sizeWritten`
- L155 _public field_ `public readonly IncrementalHash Hash`
- L157-161 _public ctor_ `public Handle(IBlobWriter writer, LeafChunkedDataNodeOptions options)`
- L163-167 _public method_ `public void Dispose()`

#### class `HordeServer.Replicators.PerforceReplicator.ReplicationClient`  
`class ReplicationClient`  
_private*; L240-256_
- L242 _public property_ `public PerforceSettings Settings { get; }`
- L243 _public property_ `public string ClusterName { get; }`
- L244 _public property_ `public InfoRecord ServerInfo { get; }`
- L245 _public property_ `public ClientRecord Client { get; }`
- L246 _public property_ `public int Change { get; set; }`
- L248-255 _public ctor_ `public ReplicationClient(PerforceSettings settings, string clusterName, InfoRecord serverInfo, ClientRecord client, int change)`

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Replicators/ReplicationService.cs` (HordeServer.Build)


#### class `HordeServer.Replicators.ReplicationException`  
`public sealed class ReplicationException : Exception`  
_public; L17-22_
- inherits: `Exception`
- desc: Exception triggered during content replication
- L19-21 _internal ctor_ `internal ReplicationException(string message) : base(message)`

#### class `HordeServer.Replicators.ReplicationService`  
`sealed class ReplicationService : IHostedService`  
_internal*; L27-126_
- inherits: `IHostedService`
- desc: Service which replicates content from Perforce
- L29 _private* field_ `readonly IReplicatorCollection _replicatorCollection`
- L30 _private* field_ `readonly PerforceReplicator _replicator`
- L31 _private* field_ `readonly ITicker _ticker`
- L32 _private* field_ `readonly IOptionsMonitor<BuildConfig> _buildConfig`
- L33 _private* field_ `readonly ILogger _logger`
- L38-45 _public ctor_ `public ReplicationService(IReplicatorCollection replicatorCollection, PerforceReplicator replicator, IClock clock, IOptionsMonitor<BuildConfig> buildConfig, ILogger<ReplicationService> logger)` — Constructor
- L48-51 _public method_ `public async Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L54-57 _public method_ `public async Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L59-108 _private* method_ `async ValueTask TickSharedAsync(CancellationToken cancellationToken)`
- L110-125 _private* method_ `async Task RunReplicationGuardedAsync(ReplicatorId replicatorId, BuildConfig buildConfig, StreamConfig streamConfig, ReplicatorConfig replicatorConfig, CancellationToken cancellationToken)`

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Replicators/ReplicatorAclAction.cs` (HordeServer.Build)


#### class `HordeServer.Replicators.ReplicatorAclAction`  
`public static class ReplicatorAclAction`  
_public; L10-21_
- desc: ACL actions that can be performed on replicators
- L15 _public property_ `public static AclAction UpdateReplicator { get; }` — Allows deletion of projects.
- L20 _public property_ `public static AclAction ViewReplicator { get; }` — Allows the creation of new projects

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Replicators/ReplicatorCollection.cs` (HordeServer.Build)


#### class `HordeServer.Replicators.ReplicatorCollection`  
`class ReplicatorCollection : IReplicatorCollection`  
_internal*; L16-275_
- inherits: `IReplicatorCollection`
- desc: Default implementation of IReplicatorCollection.
- L100 _private* field_ `readonly IMongoCollection<ReplicatorDoc> _documents`
- L101 _private* field_ `readonly IClock _clock`
- L103-110 _private* ctor_ `static ReplicatorCollection()`
- L115-119 _public ctor_ `public ReplicatorCollection(IMongoService mongoService, IClock clock)` — Constructor
- L122-126 _public method_ `public async Task<List<IReplicator>> FindAsync(CancellationToken cancellationToken = default)` — (inheritdoc)
- L129-137 _public method_ `public async Task<IReplicator?> GetAsync(ReplicatorId id, CancellationToken cancellationToken = default)` — (inheritdoc)
- L140-164 _public method_ `public async Task<IReplicator> GetOrAddAsync(ReplicatorId id, CancellationToken cancellationToken = default)` — (inheritdoc)
- L167-171 _private* method_ `async Task<bool> TryDeleteAsync(ReplicatorDoc replicator, CancellationToken cancellationToken)` — (inheritdoc)
- L174-274 _private* method_ `async Task<ReplicatorDoc?> TryUpdateAsync(ReplicatorDoc current, UpdateReplicatorOptions options, CancellationToken cancellationToken = default)` — (inheritdoc)

#### class `HordeServer.Replicators.ReplicatorCollection.ReplicatorDoc`  
`class ReplicatorDoc`  
_private*; L18-60_
- L20 _public property_ `public ReplicatorId Id { get; set; }`
- L23 _public property_ `public bool Pause { get; set; }` — attrs: `[BsonElement("pause"), BsonIgnoreIfDefault]`
- L26 _public property_ `public bool Clean { get; set; }` — attrs: `[BsonElement("clean"), BsonIgnoreIfDefault]`
- L29 _public property_ `public bool Reset { get; set; }` — attrs: `[BsonElement("reset"), BsonIgnoreIfDefault]`
- L32 _public property_ `public bool SingleStep { get; set; }` — attrs: `[BsonElement("sstep"), BsonIgnoreIfDefault]`
- L35 _public property_ `public int? LastChange { get; set; }` — attrs: `[BsonElement("lch")]`
- L38 _public property_ `public DateTime? LastChangeFinishTime { get; set; }` — attrs: `[BsonElement("lct")]`
- L41 _public property_ `public int? NextChange { get; set; }` — attrs: `[BsonElement("nch")]`
- L44 _public property_ `public int? CurrentChange { get; set; }` — attrs: `[BsonElement("cch")]`
- L47 _public property_ `public DateTime? CurrentChangeStartTime { get; set; }` — attrs: `[BsonElement("cct")]`
- L50 _public property_ `public long? CurrentSize { get; set; }` — attrs: `[BsonElement("tsz"), BsonIgnoreIfDefault]`
- L53 _public property_ `public long? CurrentCopiedSize { get; set; }` — attrs: `[BsonElement("csz"), BsonIgnoreIfDefault]`
- L56 _public property_ `public string? CurrentError { get; set; }` — attrs: `[BsonElement("err")]`
- L59 _public property_ `public int UpdateIndex { get; set; }` — attrs: `[BsonElement("idx")]`

#### class `HordeServer.Replicators.ReplicatorCollection.Replicator`  
`class Replicator : IReplicator`  
_private*; L62-98_
- inherits: `IReplicator`
- L64 _private* field_ `readonly ReplicatorCollection _collection`
- L65 _private* field_ `readonly ReplicatorDoc _document`
- L67-71 _public ctor_ `public Replicator(ReplicatorCollection collection, ReplicatorDoc document)`
- L73 _public property_ `public ReplicatorId Id => ...`
- L74 _public property_ `public bool Pause => ...`
- L75 _public property_ `public bool Clean => ...`
- L76 _public property_ `public bool Reset => ...`
- L77 _public property_ `public bool SingleStep => ...`
- L78 _public property_ `public int? LastChange => ...`
- L79 _public property_ `public int? NextChange => ...`
- L80 _public property_ `public DateTime? LastChangeFinishTime => ...`
- L81 _public property_ `public int? CurrentChange => ...`
- L82 _public property_ `public DateTime? CurrentChangeStartTime => ...`
- L83 _public property_ `public long? CurrentSize => ...`
- L84 _public property_ `public long? CurrentCopiedSize => ...`
- L85 _public property_ `public string? CurrentError => ...`
- L87 _public method_ `public Task<IReplicator?> RefreshAsync(CancellationToken cancellationToken = default)`
- L90 _public method_ `public Task<bool> TryDeleteAsync(CancellationToken cancellationToken = default)`
- L93-97 _public method_ `public async Task<IReplicator?> TryUpdateAsync(UpdateReplicatorOptions options, CancellationToken cancellationToken = default)`

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Replicators/ReplicatorConfig.cs` (HordeServer.Build)


#### class `HordeServer.Replicators.ReplicatorConfig`  
`public class ReplicatorConfig`  
_public; L11-42_
- desc: Configuration for a stream replicator
- L16 _public property_ `public StreamReplicatorId Id { get; set; }` — Identifier for the replicator within the current stream
- L21 _public property_ `public bool Enabled { get; set; }` — Whether the replicator is enabled
- L26 _public property_ `public int? MinChange { get; set; }` — Minimum change number to replicate
- L31 _public property_ `public int? MaxChange { get; set; }` — Maximum change number to replicate
- L36 _public property_ `public bool IncludeContent { get; set; }` — Whether to include content in the replication, or just metadata
- L41 _public property_ `public NamespaceId NamespaceId { get; set; }` — Namespace to replicate data to

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Replicators/ReplicatorsController.cs` (HordeServer.Build)


#### class `HordeServer.Replicators.ReplicatorsController`  
`public class ReplicatorsController : HordeControllerBase`  
_public; L20-196_
- attrs: `[ApiController] [Authorize]`
- inherits: `HordeControllerBase`
- desc: Controller for the /api/v1/projects endpoint
- L22 _private* field_ `readonly IReplicatorCollection _replicatorCollection`
- L23 _private* field_ `readonly IOptionsSnapshot<BuildConfig> _buildConfig`
- L28-32 _public ctor_ `public ReplicatorsController(IReplicatorCollection replicatorCollection, IOptionsSnapshot<BuildConfig> buildConfig)` — Constructor
- L43-69 _public method_ `public async Task<ActionResult<object>> GetReplicatorsAsync([FromQuery] StreamId? streamId = null, [FromQuery] PropertyFilter? filter = null)` — attrs: `[HttpGet] [Route("/api/v1/replicators")] [ProducesResponseType(typeof(List<GetReplicatorResponse>), 200)]` — Query all the replicators
- L80-100 _public method_ `public async Task<ActionResult<object>> GetReplicatorsAsync(ReplicatorId replicatorId, [FromQuery] PropertyFilter? filter = null)` — attrs: `[HttpGet] [Route("/api/v1/replicator/{replicatorId}")] [ProducesResponseType(typeof(GetReplicatorResponse), 200)]` — Query a replicator state
- L110-139 _public method_ `public async Task<ActionResult<object>> UpdateReplicatorAsync(ReplicatorId replicatorId, [FromBody] UpdateReplicatorRequest request, CancellationToken cancellationToken)` — attrs: `[HttpPut] [Route("/api/v1/replicator/{replicatorId}")]` — Update a replicator state
- L141-165 _private* method_ `static GetReplicatorResponse CreateGetReplicatorResponse(ReplicatorId replicatorId, IReplicator? replicator)`
- L167-195 _private* method_ `static string GetStatusMessage(IReplicator? replicator)`

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/RoboMerge/IMergeGraphService.cs` (HordeServer.Build)


#### interface `HordeServer.RoboMerge.IMergeGraphService`  
`public interface IMergeGraphService`  
_public; L10-67_
- desc: Abstraction for merge topology — not coupled to RoboMerge specifics. Other Horde services (e.g. dashboard cross-stream status) use this interface. All methods are synchronous reads against an in-memory snapshot.
- L15 _public* method_ `IReadOnlyList<MergeGraph> GetMergeGraphs()` — Get all available merge graphs (one per bot)
- L21 _public* method_ `MergeGraph? GetMergeGraph(string botName)` — Get a specific bot's merge graph by name or alias (case-insensitive). Checks the primary bot name first, then falls back to alias lookup.
- L27 _public* method_ `IReadOnlyList<MergeGraphBranchRef> FindBranchesForStreamPath(string streamPath)` — Find all branches across all bots that map to a given Perforce stream path (e.g. "//Fortnite/Main"). Useful for finding which bots manage a given Horde stream.
- L33 _public* method_ `IReadOnlyList<MergeGraphBranchRef> FindBranchesForStream(string streamDepot, string streamName)` — Find all branches across all bots that map to a given stream depot + stream name. Useful for finding which bots manage a given Horde stream.
- L40 _public* method_ `MergeChain? GetMergeChain(string botName)` — Get the ordered merge chain (release spine) for a bot. Returns branches ordered from oldest release at [0] to Main at [N-1], following forceFlowTo. Returns null if the bot doesn't exist or has no valid spine.
- L46 _public* method_ `IReadOnlyList<MergeChain> GetMergeChains()` — Get all computed merge chains across all bots. Returns only bots that have a valid release spine.
- L54 _public* method_ `IReadOnlySet<string> GetReachableBranches(string botName, string branchName)` — Get the set of branches reachable from a given branch by following flowsTo transitively. Useful for answering "where will a commit on this branch eventually flow?" Uses the pre-computed reachability index for O(1) lookup. Returns empty if the bot or branch doesn't exist.
- L60 _public* method_ `MergeEdge? GetEdge(string botName, string fromBranch, string toBranch)` — Get the edge definition between two branches in a bot, if one exists. Uses the pre-built edge index for O(1) lookup.
- L66 _public* property_ `DateTime? LastTickUtc { get; }` — When the last successful tick completed. Null if no tick has completed yet. Useful for operational diagnostics — distinguishes "never ticked" from "ticked but all files failed".

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/RoboMerge/MergeGraphModels.cs` (HordeServer.Build)


#### class `HordeServer.RoboMerge.MergeGraph`  
`public class MergeGraph`  
_public; L10-51_
- desc: A merge graph represents one RoboMerge bot's branch topology
- L13 _public property_ `public string BotName { get; init; }` — Bot name derived from branchmap filename
- L16 _public property_ `public string DefaultStreamDepot { get; init; }` — Default Perforce stream depot (e.g. "Fortnite", "UE5")
- L19 _public property_ `public bool IsDefaultBot { get; init; }` — Whether this is the default bot for its depot
- L22 _public property_ `public IReadOnlyList<string> Aliases { get; init; }` — Alternative names for this bot
- L25 _public property_ `public IReadOnlyList<string> Visibility { get; init; }` — Visibility/access tags (e.g. ["fn", "fte"])
- L28 _public property_ `public bool ReportToBuildHealth { get; init; }` — Whether this bot reports to Horde's build health system
- L31 _public property_ `public IReadOnlyList<string> ExcludeAuthors { get; init; }` — Authors excluded from merge operations
- L34 _public property_ `public string? SlackChannel { get; init; }` — Slack channel for this bot's notifications
- L37 _public property_ `public IReadOnlyList<MergeBranch> Branches { get; init; }` — Branches (nodes) in the merge graph
- L40 _public property_ `public IReadOnlyList<MergeEdge> Edges { get; init; }` — Edges with special merge behavior
- L43 _public property_ `public IReadOnlyDictionary<string, IReadOnlyList<string>> Macros { get; init; }` — Named macro definitions — keys are macro names, values are integration command templates (e.g. "#robomerge[bot1] Main")
- L47 _public property_ `public int HeadChange { get; init; }` — Perforce head changelist of the branchmap file (for staleness detection)
- L50 _public property_ `public DateTime LastRefreshedUtc { get; init; }` — When this graph was last read from Perforce

#### class `HordeServer.RoboMerge.MergeBranch`  
`public class MergeBranch`  
_public; L56-116_
- desc: A branch (node) in the merge graph
- L59 _public property_ `public string Name { get; init; }` — Unique branch identifier within the bot
- L62 _public property_ `public IReadOnlyList<string> Aliases { get; init; }` — Alternative names for this branch
- L65 _public property_ `public string? StreamName { get; init; }` — Perforce stream name (may differ from Name)
- L68 _public property_ `public string? StreamDepot { get; init; }` — Perforce stream depot override
- L71 _public property_ `public IReadOnlyList<string> FlowsTo { get; init; }` — All merge targets
- L74 _public property_ `public IReadOnlyList<string> ForceFlowTo { get; init; }` — Mandatory merge targets (the release spine)
- L77 _public property_ `public IReadOnlyList<string> DefaultFlow { get; init; }` — Default merge targets (subset of FlowsTo that are merged by default)
- L80 _public property_ `public IReadOnlyList<string> BlockAssetFlow { get; init; }` — Targets where asset flow is blocked
- L83 _public property_ `public bool DisallowDeadend { get; init; }` — Whether deadend merges are disallowed
- L86 _public property_ `public bool DisallowSkip { get; init; }` — Whether skip merges are disallowed
- L89 _public property_ `public bool Disabled { get; init; }` — Whether this branch is disabled from integrations
- L92 _public property_ `public string? Resolver { get; init; }` — Default resolver for merge conflicts
- L95 _public property_ `public string? BadgeProject { get; init; }` — Badge project association
- L98 _public property_ `public string? GraphNodeColor { get; init; }` — Color hint for dashboard graph visualization (e.g. "#FF0000")
- L101 _public property_ `public bool IncognitoMode { get; init; }` — Whether this branch is hidden from normal views
- L104 _public property_ `public IReadOnlyList<string>? Visibility { get; init; }` — Branch-level visibility/access tags (overrides graph-level visibility if set)
- L107 _public property_ `public IReadOnlyDictionary<string, IReadOnlyList<string>>? Macros { get; init; }` — Branch-level macro definitions (overrides/extends graph-level macros for this branch)
- L114 _public method_ `public string GetStreamPath(string defaultStreamDepot)` — Compute the full Perforce stream path for this branch (e.g. "//Fortnite/Main"). Uses the branch's StreamDepot if set, otherwise falls back to the graph's DefaultStreamDepot. Uses the branch's StreamName if set, otherwise falls back to the branch Name.

#### class `HordeServer.RoboMerge.MergeEdge`  
`public class MergeEdge`  
_public; L121-149_
- desc: An edge with special merge behavior between two branches
- L124 _public property_ `public string From { get; init; }` — Source branch name
- L127 _public property_ `public string To { get; init; }` — Target branch name
- L130 _public property_ `public MergeApprovalGate? Approval { get; init; }` — Approval gate on this edge, if any
- L133 _public property_ `public string? IntegrationMethod { get; init; }` — Integration method override
- L136 _public property_ `public bool DisallowSkip { get; init; }` — Whether skip merges are disallowed on this edge
- L139 _public property_ `public string? Resolver { get; init; }` — Edge-specific conflict resolver (overrides branch-level resolver)
- L142 _public property_ `public bool Terminal { get; init; }` — Whether this is a terminal edge — changes don't flow beyond this edge
- L145 _public property_ `public IReadOnlyList<string> ImplicitCommands { get; init; }` — Implicit commands applied to merges on this edge (e.g. "#robomerge[all]")
- L148 _public property_ `public string? Branchspec { get; init; }` — Custom branchspec for this edge, if any

#### class `HordeServer.RoboMerge.MergeApprovalGate`  
`public class MergeApprovalGate`  
_public; L154-161_
- desc: Approval gate on a merge edge
- L157 _public property_ `public string? Description { get; init; }` — Human-readable description of the gate
- L160 _public property_ `public bool Block { get; init; }` — Whether the gate blocks merges until approved

#### class `HordeServer.RoboMerge.MergeGraphBranchRef`  
`public class MergeGraphBranchRef`  
_public; L166-176_
- desc: Reference to a branch within a specific bot's graph
- L169 _public property_ `public string BotName { get; init; }` — Bot that owns this branch
- L172 _public property_ `public MergeBranch Branch { get; init; }` — The branch
- L175 _public property_ `public string StreamPath { get; init; }` — Pre-computed full Perforce stream path (e.g. "//Fortnite/Main")

#### class `HordeServer.RoboMerge.MergeChain`  
`public class MergeChain`  
_public; L181-188_
- desc: An ordered merge chain (the "release spine" of a bot)
- L184 _public property_ `public string BotName { get; init; }` — Bot name
- L187 _public property_ `public IReadOnlyList<MergeChainEntry> Entries { get; init; }` — Chain entries ordered: oldest release at [0], Main at [N-1]

#### class `HordeServer.RoboMerge.MergeChainEntry`  
`public class MergeChainEntry`  
_public; L193-203_
- desc: A single entry in a merge chain
- L196 _public property_ `public MergeBranch Branch { get; init; }` — The branch at this position in the chain
- L199 _public property_ `public string StreamPath { get; init; }` — Pre-computed full Perforce stream path (e.g. "//Fortnite/Main"), avoids extra graph lookup on read path
- L202 _public property_ `public bool HasApprovalGateBefore { get; init; }` — Whether there's an approval gate between the previous entry and this one

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/RoboMerge/RoboMergeBranchmapParser.cs` (HordeServer.Build)


#### class `HordeServer.RoboMerge.RoboMergeBranchmapParser`  
`internal static class RoboMergeBranchmapParser`  
_internal; L12-556_
- desc: Parser for RoboMerge branchmap JSON files
- L17 _private* field_ `static readonly HashSet<string> s_reservedNames = new HashSet<string>(StringComparer.OrdinalIgnoreCase) { "NONE", "DEFAULT", "IGNORE", "DEADEND", "" }` — Reserved branch names that are filtered from flow target arrays
- L32-135 _public method_ `public static MergeGraph Parse(string depotPath, byte[] data, int headChange, ILogger? logger = null)` — Parse branchmap JSON bytes into a MergeGraph. Bot name is derived from the depot path filename (e.g. "myproject.branchmap.json" → "myproject").
- L141-332 _public method_ `public static MergeChain? ComputeMergeChain(MergeGraph graph, ILogger? logger = null)` — Compute the merge chain (release spine) from a MergeGraph. Returns null if no valid spine can be computed.
- L338-343 _public method_ `public static string ExtractBotName(string depotPath)` — Extract the bot name from a branchmap depot path. Strips ".branchmap.json" suffix from the last path segment.
- L345-399 _private* method_ `static MergeBranch? ParseBranch(JsonElement elem)`
- L401-432 _private* method_ `static MergeEdge? ParseEdge(JsonElement elem)`
- L434-441 _private* method_ `static IReadOnlyDictionary<string, IReadOnlyList<string>> ParseMacros(JsonElement root)`
- L443-456 _private* method_ `static IReadOnlyDictionary<string, IReadOnlyList<string>> ParseMacrosElement(JsonElement macrosElem)`
- L458-467 _private* method_ `static void ValidateFlowTargets(string branchName, string fieldName, IReadOnlyList<string> targets, HashSet<string> branchNames, ILogger? logger)`
- L469-495 _private* method_ `static IReadOnlyList<string> FilterReservedNames(IReadOnlyList<string> names)`
- L497-504 _private* method_ `static string GetStringOrDefault(JsonElement elem, string propertyName)`
- L506-513 _private* method_ `static string? GetStringOrNull(JsonElement elem, string propertyName)`
- L515-529 _private* method_ `static bool GetBoolOrDefault(JsonElement elem, string propertyName)`
- L531-538 _private* method_ `static IReadOnlyList<string> GetStringArrayOrEmpty(JsonElement elem, string propertyName)`
- L540-555 _private* method_ `static IReadOnlyList<string> ParseStringArray(JsonElement arrayElem)`

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/RoboMerge/RoboMergeController.cs` (HordeServer.Build)


#### class `HordeServer.RoboMerge.RoboMergeController`  
`public class RoboMergeController : HordeControllerBase`  
_public; L18-337_
- attrs: `[Authorize] [ApiController] [Tags("RoboMerge")]`
- inherits: `HordeControllerBase`
- desc: Controller for RoboMerge merge graph data
- L20 _private* field_ `readonly IMergeGraphService _mergeGraphService`
- L21 _private* field_ `readonly IOptionsSnapshot<BuildConfig> _buildConfig`
- L26-30 _public ctor_ `public RoboMergeController(IMergeGraphService mergeGraphService, IOptionsSnapshot<BuildConfig> buildConfig)` — Constructor
- L36-40 _private* method_ `bool AuthorizeMergeGraphByBotName(string botName)` — Check whether the current user can view at least one Horde stream in the given merge graph. Falls back to allowing access if no Horde streams match any branch (topology-only data).
- L42-64 _private* method_ `bool AuthorizeMergeGraph(MergeGraph graph)`
- L72-83 _public method_ `public ActionResult<GetRoboMergeStatusResponse> GetStatus()` — attrs: `[HttpGet] [Route("/api/v1/robomerge/status")] [ProducesResponseType(typeof(GetRoboMergeStatusResponse), 200)]` — Get the service status
- L91-103 _public method_ `public ActionResult<List<GetMergeGraphSummaryResponse>> GetMergeGraphs()` — attrs: `[HttpGet] [Route("/api/v1/robomerge/graphs")] [ProducesResponseType(typeof(List<GetMergeGraphSummaryResponse>), 200)]` — List all merge graphs (summary)
- L112-124 _public method_ `public ActionResult<GetMergeGraphResponse> GetMergeGraph(string botName)` — attrs: `[HttpGet] [Route("/api/v1/robomerge/graphs/{botName}")] [ProducesResponseType(typeof(GetMergeGraphResponse), 200)] [ProducesResponseType(404)]` — Get a specific bot's full merge graph
- L133-150 _public method_ `public ActionResult<GetMergeChainResponse> GetMergeChain(string botName)` — attrs: `[HttpGet] [Route("/api/v1/robomerge/graphs/{botName}/chain")] [ProducesResponseType(typeof(GetMergeChainResponse), 200)] [ProducesResponseType(404)]` — Get the merge chain for a bot
- L158-164 _public method_ `public ActionResult<List<GetMergeChainResponse>> GetMergeChains()` — attrs: `[HttpGet] [Route("/api/v1/robomerge/chains")] [ProducesResponseType(typeof(List<GetMergeChainResponse>), 200)]` — Get all merge chains
- L172-198 _public method_ `public ActionResult<List<GetMergeBranchRefResponse>> FindBranches( [FromQuery] string? streamPath, [FromQuery] string? depot, [FromQuery] string? stream)` — attrs: `[HttpGet] [Route("/api/v1/robomerge/branches")] [ProducesResponseType(typeof(List<GetMergeBranchRefResponse>), 200)]` — Find branches matching a stream
- L207-229 _public method_ `public ActionResult<GetReachableBranchesResponse> GetReachableBranches(string botName, string branchName)` — attrs: `[HttpGet] [Route("/api/v1/robomerge/graphs/{botName}/branches/{branchName}/reachable")] [ProducesResponseType(typeof(GetReachableBranchesResponse), 200)] [ProducesResponseType(404)]` — Get branches reachable from a given branch via transitive flowsTo
- L239-263 _public method_ `public ActionResult<GetMergeEdgeResponse> GetEdge( string botName, [FromQuery] string? from, [FromQuery] string? to)` — attrs: `[HttpGet] [Route("/api/v1/robomerge/graphs/{botName}/edges")] [ProducesResponseType(typeof(GetMergeEdgeResponse), 200)] [ProducesResponseType(400)] [ProducesResponseType(404)]` — Get the edge between two branches in a bot
- L265 _private* method_ `static GetMergeGraphResponse CreateGetMergeGraphResponse(MergeGraph graph)`
- L285 _private* method_ `static GetMergeBranchResponse CreateGetMergeBranchResponse(MergeBranch branch, string streamPath)`
- L308 _private* method_ `static GetMergeEdgeResponse CreateGetMergeEdgeResponse(MergeEdge edge)`
- L326 _private* method_ `static GetMergeChainResponse CreateGetMergeChainResponse(MergeChain chain)`

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/RoboMerge/RoboMergeMessages.cs` (HordeServer.Build)


#### class `HordeServer.RoboMerge.GetRoboMergeStatusResponse`  
`public class GetRoboMergeStatusResponse`  
_public; L8-24_
- desc: Overall status of the RoboMerge merge graph service
- L11 _public property_ `public bool IsConfigured { get; set; }` — Whether the service is configured with branchmap files
- L14 _public property_ `public bool GraphsLoaded { get; set; }` — Whether graph data has been loaded (false between startup and first tick)
- L17 _public property_ `public int GraphCount { get; set; }` — Number of merge graphs currently loaded
- L20 _public property_ `public List<string> BotNames { get; set; }` — Names of all loaded bots
- L23 _public property_ `public DateTime? LastTickUtc { get; set; }` — When the last tick completed (null if no tick has completed yet)

#### class `HordeServer.RoboMerge.GetMergeGraphSummaryResponse`  
`public class GetMergeGraphSummaryResponse`  
_public; L29-51_
- desc: Summary of a merge graph (for list endpoint)
- L32 _public property_ `public string BotName { get; set; }` — Bot name
- L35 _public property_ `public string DefaultStreamDepot { get; set; }` — Default Perforce stream depot
- L38 _public property_ `public int BranchCount { get; set; }` — Number of branches in the graph
- L41 _public property_ `public int EdgeCount { get; set; }` — Number of edges in the graph
- L44 _public property_ `public bool ReportToBuildHealth { get; set; }` — Whether this bot reports to build health
- L47 _public property_ `public int HeadChange { get; set; }` — Perforce head changelist of the branchmap file
- L50 _public property_ `public DateTime LastRefreshedUtc { get; set; }` — When this graph was last read from Perforce

#### class `HordeServer.RoboMerge.GetMergeGraphResponse`  
`public class GetMergeGraphResponse`  
_public; L56-96_
- desc: Full merge graph for a single bot
- L59 _public property_ `public string BotName { get; set; }` — Bot name
- L62 _public property_ `public string DefaultStreamDepot { get; set; }` — Default Perforce stream depot
- L65 _public property_ `public bool IsDefaultBot { get; set; }` — Whether this is the default bot for its depot
- L68 _public property_ `public List<string> Aliases { get; set; }` — Alternative bot names
- L71 _public property_ `public List<string> Visibility { get; set; }` — Visibility/access tags
- L74 _public property_ `public bool ReportToBuildHealth { get; set; }` — Whether this bot reports to build health
- L77 _public property_ `public List<string> ExcludeAuthors { get; set; }` — Authors excluded from merge operations
- L80 _public property_ `public string? SlackChannel { get; set; }` — Slack channel for this bot's notifications
- L83 _public property_ `public int HeadChange { get; set; }` — Perforce head changelist of the branchmap file
- L86 _public property_ `public DateTime LastRefreshedUtc { get; set; }` — When this graph was last read from Perforce
- L89 _public property_ `public List<GetMergeBranchResponse> Branches { get; set; }` — Branches (nodes) in the graph
- L92 _public property_ `public List<GetMergeEdgeResponse> Edges { get; set; }` — Edges with special merge behavior
- L95 _public property_ `public Dictionary<string, List<string>>? Macros { get; set; }` — Named macro definitions

#### class `HordeServer.RoboMerge.GetMergeBranchResponse`  
`public class GetMergeBranchResponse`  
_public; L101-156_
- desc: A branch in a merge graph
- L104 _public property_ `public string Name { get; set; }` — Branch name
- L107 _public property_ `public List<string> Aliases { get; set; }` — Alternative branch names
- L110 _public property_ `public string? StreamName { get; set; }` — Perforce stream name
- L113 _public property_ `public string? StreamDepot { get; set; }` — Perforce stream depot override
- L116 _public property_ `public string StreamPath { get; set; }` — Full Perforce stream path (e.g. "//Fortnite/Main")
- L119 _public property_ `public List<string> FlowsTo { get; set; }` — All merge targets
- L122 _public property_ `public List<string> ForceFlowTo { get; set; }` — Mandatory merge targets
- L125 _public property_ `public List<string> DefaultFlow { get; set; }` — Default merge targets
- L128 _public property_ `public List<string> BlockAssetFlow { get; set; }` — Targets where asset flow is blocked
- L131 _public property_ `public bool DisallowDeadend { get; set; }` — Whether deadend merges are disallowed
- L134 _public property_ `public bool DisallowSkip { get; set; }` — Whether skip merges are disallowed
- L137 _public property_ `public bool Disabled { get; set; }` — Whether this branch is disabled from integrations
- L140 _public property_ `public string? Resolver { get; set; }` — Default resolver for merge conflicts
- L143 _public property_ `public string? BadgeProject { get; set; }` — Badge project association
- L146 _public property_ `public string? GraphNodeColor { get; set; }` — Color hint for dashboard graph visualization
- L149 _public property_ `public bool IncognitoMode { get; set; }` — Whether this branch is hidden from normal views
- L152 _public property_ `public List<string>? Visibility { get; set; }` — Branch-level visibility/access tags (null if inheriting from graph)
- L155 _public property_ `public Dictionary<string, List<string>>? Macros { get; set; }` — Branch-level macro definitions (null if no branch-level macros)

#### class `HordeServer.RoboMerge.GetMergeEdgeResponse`  
`public class GetMergeEdgeResponse`  
_public; L161-189_
- desc: A merge edge
- L164 _public property_ `public string From { get; set; }` — Source branch name
- L167 _public property_ `public string To { get; set; }` — Target branch name
- L170 _public property_ `public GetMergeApprovalGateResponse? Approval { get; set; }` — Approval gate, if any
- L173 _public property_ `public string? IntegrationMethod { get; set; }` — Integration method override
- L176 _public property_ `public bool DisallowSkip { get; set; }` — Whether skip merges are disallowed
- L179 _public property_ `public string? Resolver { get; set; }` — Edge-specific conflict resolver
- L182 _public property_ `public bool Terminal { get; set; }` — Whether this is a terminal edge (changes don't flow beyond)
- L185 _public property_ `public List<string> ImplicitCommands { get; set; }` — Implicit commands applied to merges on this edge
- L188 _public property_ `public string? Branchspec { get; set; }` — Custom branchspec for this edge

#### class `HordeServer.RoboMerge.GetMergeApprovalGateResponse`  
`public class GetMergeApprovalGateResponse`  
_public; L194-201_
- desc: Approval gate on a merge edge
- L197 _public property_ `public string? Description { get; set; }` — Gate description
- L200 _public property_ `public bool Block { get; set; }` — Whether the gate blocks merges

#### class `HordeServer.RoboMerge.GetMergeChainResponse`  
`public class GetMergeChainResponse`  
_public; L206-213_
- desc: Merge chain for a bot
- L209 _public property_ `public string BotName { get; set; }` — Bot name
- L212 _public property_ `public List<GetMergeChainEntryResponse> Entries { get; set; }` — Chain entries, oldest release at [0], Main at [N-1]

#### class `HordeServer.RoboMerge.GetMergeChainEntryResponse`  
`public class GetMergeChainEntryResponse`  
_public; L218-228_
- desc: A single entry in a merge chain
- L221 _public property_ `public string BranchName { get; set; }` — Branch name
- L224 _public property_ `public string StreamPath { get; set; }` — Full Perforce stream path (e.g. "//Fortnite/Main")
- L227 _public property_ `public bool HasApprovalGateBefore { get; set; }` — Whether there's an approval gate between the previous entry and this one

#### class `HordeServer.RoboMerge.GetMergeBranchRefResponse`  
`public class GetMergeBranchRefResponse`  
_public; L233-240_
- desc: A branch reference (branch + owning bot name)
- L236 _public property_ `public string BotName { get; set; }` — Bot that owns this branch
- L239 _public property_ `public GetMergeBranchResponse Branch { get; set; }` — The branch

#### class `HordeServer.RoboMerge.GetReachableBranchesResponse`  
`public class GetReachableBranchesResponse`  
_public; L245-255_
- desc: Branches reachable from a given branch via transitive flowsTo
- L248 _public property_ `public string BotName { get; set; }` — Bot name
- L251 _public property_ `public string BranchName { get; set; }` — Starting branch name
- L254 _public property_ `public List<string> ReachableBranches { get; set; }` — Branch names reachable via transitive flowsTo (excludes the starting branch)

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/RoboMerge/RoboMergeService.cs` (HordeServer.Build)


#### class `HordeServer.RoboMerge.MergeGraphSnapshot`  
`internal sealed class MergeGraphSnapshot`  
_internal; L20-61_
- desc: Immutable snapshot of all parsed merge graph data. Swapped atomically via volatile write so readers never see partial updates between graphs and chains.
- L23 _public property_ `public ImmutableDictionary<string, MergeGraph> Graphs { get; init; }` — All parsed merge graphs, keyed by bot name (case-insensitive)
- L27 _public property_ `public IReadOnlyList<MergeGraph> AllGraphs { get; init; }` — Pre-computed list of all graphs (avoids allocation on every read)
- L30 _public property_ `public ImmutableDictionary<string, string> AliasIndex { get; init; }` — Bot alias → primary bot name lookup (case-insensitive)
- L34 _public property_ `public ImmutableDictionary<string, MergeChain> Chains { get; init; }` — Computed merge chains, keyed by bot name (case-insensitive)
- L38 _public property_ `public IReadOnlyList<MergeChain> AllChains { get; init; }` — Pre-computed list of all chains (avoids allocation on every read)
- L44 _public property_ `public ImmutableDictionary<string, ImmutableArray<MergeGraphBranchRef>> StreamPathIndex { get; init; }` — Pre-built index mapping normalized stream paths (case-insensitive) to branch references. Avoids linear scan on every FindBranchesForStream call.
- L50 _public property_ `public ImmutableDictionary<string, MergeEdge> EdgeIndex { get; init; }` — Pre-built edge lookup: "botName|from|to" → MergeEdge (case-insensitive).
- L56 _public property_ `public ImmutableDictionary<string, ImmutableHashSet<string>> ReachabilityIndex { get; init; }` — Pre-computed reachability sets: "botName|branchName" → set of reachable branch names.
- L60 _public property_ `public DateTime? LastTickUtc { get; init; }` — When the last tick completed (null before first tick).

#### class `HordeServer.RoboMerge.RoboMergeService`  
`internal sealed class RoboMergeService : IHostedService, IAsyncDisposable, IMergeGraphService`  
_internal; L67-503_
- inherits: `IHostedService, IAsyncDisposable, IMergeGraphService`
- desc: Ticking service that reads RoboMerge branchmap files from Perforce and serves them as in-memory merge graph snapshots.
- L69 _private* field_ `readonly IPerforceService _perforceService`
- L70 _private* field_ `readonly IOptionsMonitor<BuildConfig> _buildConfig`
- L71 _private* field_ `readonly ILogger<RoboMergeService> _logger`
- L73 _private* field_ `readonly ITicker _ticker`
- L76 _private* field_ `readonly Counter<int> _parseFailureCounter`
- L77 _private* field_ `readonly Histogram<double> _tickDurationSeconds`
- L80 _private* field_ `volatile MergeGraphSnapshot _snapshot = new MergeGraphSnapshot()`
- L84 _private* field_ `readonly Dictionary<string, int> _headChanges = ...`
- L84 _private* field_ `readonly Dictionary< _headChanges = new Dictionary<string, int>(StringComparer.OrdinalIgnoreCase)`
- L87 _private* field_ `ImmutableSortedSet<string> _previousBotNames = ImmutableSortedSet<string>.Empty`
- L92 _private* field_ `static readonly TimeSpan s_initialDelay = TimeSpan.FromSeconds(15)` — Initial delay before first tick. Short so data is available quickly after startup.
- L95 _private* field_ `readonly TimeSpan _tickInterval` — Configured tick interval for subsequent ticks after the initial load.
- L100-117 _public ctor_ `public RoboMergeService( IPerforceService perforceService, IOptionsMonitor<BuildConfig> buildConfig, IClock clock, Meter meter, ILogger<RoboMergeService> logger)` — Constructor
- L120 _public method_ `public async Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L124 _public method_ `public async Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L128 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L134-138 _private* method_ `async ValueTask<TimeSpan?> TickInternalAsync(CancellationToken cancellationToken)` — Tick wrapper — delegates to TickAsync and returns the configured interval.
- L143-382 _private* method_ `async ValueTask TickAsync(CancellationToken cancellationToken)` — Tick callback — reads branchmap files from Perforce and updates in-memory snapshot.
- L387-394 _private* method_ `void PreserveExistingGraph(Dictionary<string, MergeGraph> newGraphs, string depotPath)` — Helper to preserve a previously-loaded graph when a file can't be read.
- L399 _public property_ `public DateTime? LastTickUtc => ...` — (inheritdoc)
- L402 _public method_ `public IReadOnlyList<MergeGraph> GetMergeGraphs()` — (inheritdoc)
- L406-418 _public method_ `public MergeGraph? GetMergeGraph(string botName)` — (inheritdoc)
- L421-436 _public method_ `public IReadOnlyList<MergeGraphBranchRef> FindBranchesForStreamPath(string streamPath)` — (inheritdoc)
- L439-448 _public method_ `public IReadOnlyList<MergeGraphBranchRef> FindBranchesForStream(string streamDepot, string streamName)` — (inheritdoc)
- L451-463 _public method_ `public MergeChain? GetMergeChain(string botName)` — (inheritdoc)
- L466 _public method_ `public IReadOnlyList<MergeChain> GetMergeChains()` — (inheritdoc)
- L470-486 _public method_ `public IReadOnlySet<string> GetReachableBranches(string botName, string branchName)` — (inheritdoc)
- L489-502 _public method_ `public MergeEdge? GetEdge(string botName, string fromBranch, string toBranch)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Streams/RetentionOptions.cs` (HordeServer.Build)


#### class `HordeServer.Streams.RetentionOptions`  
`public class RetentionOptions`  
_public; L10-42_
- desc: Options controlling storage retention and GC behavior for a stream. Boolean flags are safety valves: only false is meaningful (disables behavior). null means "not disabled" (default). Setting true is identical to null .
- L17 _public property_ `public bool? EnableJobExpiration { get; set; }` — Whether job expiration is enabled for this stream. When null (default), expiration runs normally if ExpireAfterDays is greater than 0. When explicitly false, disables expiration regardless of ExpireAfterDays (safety valve).
- L23 _public property_ `public bool? EnableArtifactExpiration { get; set; }` — Override for artifact retention behavior. When false, artifact expiry is paused for this stream (useful during investigations).
- L31 _public property_ `public int? MaxJobDeletionsPerTick { get; set; }` — Maximum number of jobs to delete per hourly expiration tick, per stream. Prevents thundering-herd behavior when ExpireAfterDays is first enabled on a stream with a large backlog. Default null, treated as 1000 by consumers via null-coalescing (safe-by-default cap). Set to 0 for unlimited.
- L36-41 _public method_ `public void MergeDefaults(RetentionOptions other)` — Merge defaults from another options object

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Streams/StreamAclAction.cs` (HordeServer.Build)


#### class `HordeServer.Streams.StreamAclAction`  
`public static class StreamAclAction`  
_public; L10-41_
- desc: ACL actions that can be performed on streams
- L15 _public property_ `public static AclAction CreateStream { get; }` — Allows the creation of new streams within a project
- L20 _public property_ `public static AclAction UpdateStream { get; }` — Allows updating a stream (agent types, templates, schedules)
- L25 _public property_ `public static AclAction DeleteStream { get; }` — Allows deleting a stream
- L30 _public property_ `public static AclAction ViewStream { get; }` — Ability to view a stream
- L35 _public property_ `public static AclAction ViewChanges { get; }` — View changes submitted to a stream. NOTE: this returns responses from the server's Perforce account, which may be a priviledged user.
- L40 _public property_ `public static AclAction ViewTemplate { get; }` — View template associated with a stream

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Streams/StreamCollection.cs` (HordeServer.Build)


#### class `HordeServer.Streams.StreamCollection`  
`public class StreamCollection : IStreamCollection`  
_public; L25-634_
- inherits: `IStreamCollection`
- desc: Collection of stream documents
- L305 _private* field_ `readonly IMongoCollection<StreamDoc> _streams`
- L306 _private* field_ `readonly ICommitService _commitService`
- L307 _private* field_ `readonly IOptionsMonitor<BuildConfig> _buildConfig`
- L308 _private* field_ `readonly IClock _clock`
- L313-319 _public ctor_ `public StreamCollection(IMongoService mongoService, ICommitService commitService, IOptionsMonitor<BuildConfig> buildConfig, IClock clock)` — Constructor
- L322-332 _public method_ `public async Task<IStream?> GetAsync(StreamId id, CancellationToken cancellationToken)` — (inheritdoc)
- L334-348 _private* method_ `async Task<StreamDoc> GetInternalAsync(StreamConfig streamConfig, CancellationToken cancellationToken)`
- L351-371 _public method_ `public async Task<IReadOnlyList<IStream>> FindAsync(IReadOnlyList<StreamId>? ids = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L373-393 _private* method_ `async Task<List<StreamDoc>> GetInternalAsync(IReadOnlyList<StreamConfig> streamConfigs, CancellationToken cancellationToken)`
- L395-408 _private* method_ `async ValueTask<bool> PostLoadAsync(StreamDoc streamDoc, StreamConfig streamConfig, CancellationToken cancellationToken)`
- L411-494 _private* method_ `async Task<StreamDoc?> TryUpdateTemplateRefAsync(StreamDoc document, TemplateId templateId, List<UpdateStepStateRequest>? stepStates = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L497-508 _private* method_ `async Task<StreamDoc?> TryUpdatePauseStateAsync(StreamDoc document, DateTime? newPausedUntil, string? newPauseComment, CancellationToken cancellationToken)` — (inheritdoc)
- L511-549 _private* method_ `async Task<StreamDoc?> TryUpdateScheduleTriggerAsync(StreamDoc streamDoc, TemplateId templateId, DateTime? lastTriggerTimeUtc, CommitIdWithOrder? lastTriggerCommitId, List<JobId> newActiveJobs, CancellationToken cancellationToken)` — (inheritdoc)
- L558-565 _private method_ `private async Task<StreamDoc?> TryUpdateStreamAsync(StreamDoc streamDoc, UpdateDefinition<StreamDoc> update, CancellationToken cancellationToken)` — Update a stream
- L570-633 _public method_ `public static void Validate(StreamId streamId, StreamConfig config)` — Checks the stream definition for consistency

#### class `HordeServer.Streams.StreamCollection.Stream`  
`class Stream : IStream`  
_private*; L27-102_
- inherits: `IStream`
- L29 _private* field_ `readonly StreamCollection _collection`
- L30 _private* field_ `readonly StreamConfig _config`
- L31 _private* field_ `readonly StreamDoc _document`
- L32 _private* field_ `readonly Dictionary<TemplateId, ITemplateRef> _templateRefs = ...`
- L32 _private* field_ `readonly Dictionary< _templateRefs = new Dictionary<TemplateId, ITemplateRef>()`
- L34 _public property_ `public StreamDoc Document => ...`
- L36 _public property_ `public StreamId Id => ...`
- L37 _public property_ `public StreamConfig Config => ...`
- L38 _public property_ `public IReadOnlyDictionary<TemplateId, ITemplateRef> Templates => ...`
- L39 _public property_ `public DateTime? PausedUntil => ...`
- L40 _public property_ `public string? PauseComment => ...`
- L42 _private* property_ `ProjectId IStream.ProjectId => ...`
- L43 _private* property_ `string IStream.Name => ...`
- L44 _private* property_ `string? IStream.ConfigPath => ...`
- L45 _private* property_ `string IStream.ConfigRevision => ...`
- L46 _private* property_ `int IStream.Order => ...`
- L47 _private* property_ `string? IStream.NotificationChannel => ...`
- L48 _private* property_ `string? IStream.NotificationChannelFilter => ...`
- L49 _private* property_ `string? IStream.TriageChannel => ...`
- L50 _private* property_ `IReadOnlyList<IStreamTab> IStream.Tabs => ...`
- L51 _private* property_ `IDefaultPreflight? IStream.DefaultPreflight => ...`
- L53 _private* field_ `IReadOnlyDictionary<string, IAgentType>? _cachedAgentTypes`
- L53 _private* field_ `IReadOnlyDictionary< _cachedAgentTypes`
- L54 _private* property_ `IReadOnlyDictionary<string, IAgentType> IStream.AgentTypes => ...`
- L57 _private* field_ `IReadOnlyDictionary<string, IWorkspaceType>? _cachedWorkspaceTypes`
- L57 _private* field_ `IReadOnlyDictionary< _cachedWorkspaceTypes`
- L58 _private* property_ `IReadOnlyDictionary<string, IWorkspaceType> IStream.WorkspaceTypes => ...`
- L61 _private* property_ `IReadOnlyList<IWorkflow> IStream.Workflows => ...`
- L63 _private* field_ `IReadOnlyList<IStreamAlias>? _cachedAliases`
- L64 _private* property_ `IReadOnlyList<IStreamAlias> IStream.Aliases => ...`
- L67 _private* property_ `ICommitCollection IStream.Commits => ...`
- L69-80 _public ctor_ `public Stream(StreamCollection collection, StreamConfig config, StreamDoc document)`
- L82 _public method_ `public Task<IStream?> RefreshAsync(CancellationToken cancellationToken = default)`
- L85-89 _public method_ `public async Task<IStream?> TryUpdatePauseStateAsync(DateTime? newPausedUntil, string? newPauseComment, CancellationToken cancellationToken = default)`
- L91-95 _public method_ `public async Task<IStream?> TryUpdateScheduleTriggerAsync(TemplateId templateRefId, DateTime? lastTriggerTimeUtc, CommitIdWithOrder? lastTriggerCommitId, List<JobId> newActiveJobs, CancellationToken cancellationToken = default)`
- L97-101 _public method_ `public async Task<IStream?> TryUpdateTemplateRefAsync(TemplateId templateRefId, List<UpdateStepStateRequest>? stepStates = null, CancellationToken cancellationToken = default)`

#### class `HordeServer.Streams.StreamCollection.TemplateRef`  
`class TemplateRef : ITemplateRef`  
_private*; L104-134_
- inherits: `ITemplateRef`
- L106 _private* field_ `readonly TemplateRefConfig _config`
- L107 _private* field_ `readonly TemplateRefDoc _document`
- L108 _private* field_ `readonly Schedule? _schedule`
- L110-119 _public ctor_ `public TemplateRef(TemplateRefConfig config, TemplateRefDoc document)`
- L121 _public property_ `public TemplateId Id => ...`
- L122 _public property_ `public ITemplate Template => ...`
- L123 _public property_ `public TemplateRefConfig Config => ...`
- L124 _public property_ `public ISchedule? Schedule => ...`
- L125 _public property_ `public IReadOnlyList<ITemplateStep> StepStates => ...`
- L127 _private* property_ `bool ITemplateRef.ShowUgsBadges => ...`
- L128 _private* property_ `bool ITemplateRef.ShowUgsAlerts => ...`
- L129 _private* property_ `string? ITemplateRef.NotificationChannel => ...`
- L130 _private* property_ `string? ITemplateRef.NotificationChannelFilter => ...`
- L131 _private* property_ `string? ITemplateRef.TriageChannel => ...`
- L132 _private* property_ `IReadOnlyList<IChainedJobTemplate>? ITemplateRef.ChainedJobs => ...`
- L133 _private* property_ `IReadOnlyList<IChangeQuery>? ITemplateRef.DefaultChange => ...`

#### class `HordeServer.Streams.StreamCollection.Schedule`  
`class Schedule : ISchedule`  
_private*; L136-160_
- inherits: `ISchedule`
- L138 _private* field_ `readonly ScheduleConfig _config`
- L139 _private* field_ `readonly ScheduleDoc _document`
- L141 _public property_ `public IReadOnlyList<IScheduleClaim>? Claims => ...`
- L142 _public property_ `public bool Enabled => ...`
- L143 _public property_ `public int MaxActive => ...`
- L144 _public property_ `public int MaxChanges => ...`
- L145 _public property_ `public bool RequireSubmittedChange => ...`
- L146 _public property_ `public IScheduleGate? Gate => ...`
- L147 _public property_ `public IReadOnlyList<CommitTag> Commits => ...`
- L148 _public property_ `public CommitIdWithOrder? LastTriggerCommitId => ...`
- L149 _public property_ `public DateTime LastTriggerTimeUtc => ...`
- L150 _public property_ `public IReadOnlyList<JobId> ActiveJobs => ...`
- L151 _public property_ `public IReadOnlyList<ISchedulePattern> Patterns => ...`
- L152 _public property_ `public IReadOnlyList<string>? Files => ...`
- L153 _public property_ `public IReadOnlyDictionary<string, string> TemplateParameters => ...`
- L155-159 _public ctor_ `public Schedule(ScheduleConfig config, ScheduleDoc document)`

#### class `HordeServer.Streams.StreamCollection.StreamDoc`  
`class StreamDoc`  
_private*; L165-209_
- desc: Information about a stream
- L168 _public property_ `public StreamId Id { get; set; }` — attrs: `[BsonRequired, BsonId]`
- L170 _public property_ `public Dictionary<TemplateId, TemplateRefDoc> Templates { get; set; }`
- L171 _public property_ `public DateTime? PausedUntil { get; set; }`
- L172 _public property_ `public string? PauseComment { get; set; }`
- L174 _public property_ `public int UpdateIndex { get; set; }`
- L177-179 _private ctor_ `private StreamDoc()` — attrs: `[BsonConstructor]`
- L181-184 _public ctor_ `public StreamDoc(StreamId id)`
- L186-208 _public method_ `public bool PostLoad(StreamConfig config, DateTime utcNow)`

#### class `HordeServer.Streams.StreamCollection.TemplateRefDoc`  
`class TemplateRefDoc`  
_private*; L211-251_
- L214 _public property_ `public ScheduleDoc? Schedule { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L217 _public property_ `public List<TemplateStepDoc>? StepStates { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L219-250 _public method_ `public bool PostLoad(TemplateRefConfig config, DateTime utcNow)`

#### class `HordeServer.Streams.StreamCollection.ScheduleDoc`  
`class ScheduleDoc`  
_private*; L253-282_
- L255-259 _public property_ `public CommitIdWithOrder LastTriggerCommitId { get; set; }`
- L261 _public property_ `public string? LastTriggerCommitName { get; set; }`
- L264 _public property_ `public int LastTriggerCommitOrder { get; set; }` — attrs: `[BsonElement("LastTriggerChange")]`
- L267 _public property_ `public DateTimeOffset? LastTriggerTime { get; set; }` — attrs: `[BsonIgnoreIfNull, Obsolete("Use LastTriggerTimeUtc instead")]`
- L269 _public property_ `public DateTime LastTriggerTimeUtc { get; set; }`
- L270 _public property_ `public List<JobId> ActiveJobs { get; set; }`
- L272-281 _public method_ `public void PostLoad()`

#### class `HordeServer.Streams.StreamCollection.TemplateStepDoc`  
`class TemplateStepDoc : ITemplateStep`  
_private*; L284-303_
- inherits: `ITemplateStep`
- L286 _public property_ `public string Name { get; set; }`
- L287 _public property_ `public UserId? PausedByUserId { get; set; }`
- L288 _public property_ `public DateTime? PauseTimeUtc { get; set; }`
- L290 _private* property_ `UserId ITemplateStep.PausedByUserId => ...`
- L291 _private* property_ `DateTime ITemplateStep.PauseTimeUtc => ...`
- L293-295 _public ctor_ `public TemplateStepDoc()`
- L297-302 _public ctor_ `public TemplateStepDoc(string name, UserId pausedByUserId, DateTime pauseTimeUtc)`

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Streams/StreamConfig.cs` (HordeServer.Build)


#### enum `HordeServer.Streams.ChangeContentFlags`  
`public enum ChangeContentFlags`  
_public; L49-60_
- attrs: `[Flags] [Obsolete("Use tags instead")]`
- desc: Flags identifying content of a changelist
- L54 _public* enumerator_ `ContainsCode = 1` — The change contains code
- L59 _public* enumerator_ `ContainsContent = 2` — The change contains content

#### enum `HordeServer.Streams.ContentReplicationMode`  
`public enum ContentReplicationMode`  
_public; L65-81_
- desc: How to replicate data for this stream
- L70 _public* enumerator_ `None` — No content will be replicated for this stream
- L75 _public* enumerator_ `RevisionsOnly` — Only replicate depot path and revision data for each file
- L80 _public* enumerator_ `Full` — Replicate full stream contents to storage

#### class `HordeServer.Streams.StreamTag`  
`public class StreamTag`  
_public; L86-97_
- desc: Tags for a stream
- L91 _public property_ `public string Name { get; set; }` — Name of the tag
- L96 _public property_ `public bool Enabled { get; set; }` — Whether the tag should be enabled

#### class `HordeServer.Streams.StreamConfig`  
`public class StreamConfig`  
_public; L108-665_
- attrs: `[JsonSchema("https://unrealengine.com/horde/stream")] [JsonSchemaCatalog("Horde Stream", "Horde stream configuration file", new[] { "*.stream.json", "Streams/*.json" })] [ConfigDoc("*.stream.json", "[Horde](../../../README.md) > [Configuration](../../Config.md)", "Config/Schema/Streams.md")] [ConfigIncludeRoot] [ConfigMacroScope] [DebuggerDisplay("{Id}")]`
- desc: Config for a stream
- L114 _public property_ `public ProjectConfig ProjectConfig { get; set; }` — attrs: `[JsonIgnore]` — Accessor for the project containing this stream
- L119 _public property_ `public StreamId Id { get; set; }` — Identifier for the stream
- L124 _public property_ `public string VCS { get; set; }` — Version control service for stream commits
- L129 _public property_ `public string? RepositoryName { get; set; }` — Repository name for version control systems that support multiple repositories
- L135 _public property_ `public string? DefaultBranchName { get; set; }` — Default branch name for version control systems that use branches (e.g., "main"). If not set, defaults to "main".
- L141 _public property_ `public string? Path { get; set; }` — attrs: `[ConfigInclude, ConfigRelativePath]` — Direct include path for the stream config. For backwards compatibility with old config files when including from a ProjectConfig object.
- L146 _public property_ `public List<ConfigInclude> Include { get; set; }` — Includes for other configuration files
- L151 _public property_ `public List<ConfigMacro> Macros { get; set; }` — Macros within this stream
- L157 _public property_ `public string Revision { get; set; }` — attrs: `[JsonIgnore]` — Revision identifier for this configuration object
- L162 _public property_ `public string Name { get; set; }` — Name of the stream
- L167 _public property_ `public string EnginePath { get; set; }` — Path to the engine directory within the workspace. Used for launching UAT.
- L175 _public property_ `public List<string>? IgnorePatternFiles { get; set; }` — attrs: `[ConfigMergeStrategy(ConfigMergeStrategy.Append)]` — Additional file paths (relative to workspace root) containing ignore patterns for the log parser. Each file should contain one regex per line, with lines starting with '#' treated as comments. Inherits from ProjectConfig and appends stream-level entries.
- L180 _public property_ `public string ClusterName { get; set; }` — The perforce cluster containing the stream
- L185 _public property_ `public int Order { get; set; }` — Order for this stream
- L190 _public property_ `public string? InitialAgentType { get; set; }` — Default initial agent type for templates
- L195 _public property_ `public string? NotificationChannel { get; set; }` — Notification channel for all jobs in this stream
- L200 _public property_ `public string? NotificationChannelFilter { get; set; }` — Notification channel filter for this template. Can be Success, Failure, or Warnings.
- L205 _public property_ `public string? TriageChannel { get; set; }` — Channel to post issue triage notifications
- L210 _public property_ `public JobOptions JobOptions { get; set; }` — Default settings for executing jobs
- L215 _public property_ `public RetentionOptions RetentionOptions { get; set; }` — Storage retention options for this stream
- L220 _public property_ `public TelemetryStoreId TelemetryStoreId { get; set; }` — Telemetry store for Horde data for this stream
- L225 _public property_ `public List<string>? AutoSdkView { get; set; }` — View for the AutoSDK paths to sync. If null, the whole thing will be synced.
- L231-235 _public property_ `public string? DefaultPreflightTemplate { get; set; }` — attrs: `[Obsolete("Use DefaultPreflight instead")]` — Legacy name for the default preflight template
- L240 _public property_ `public DefaultPreflightConfig? DefaultPreflight { get; set; }` — Default template for running preflights
- L245 _public property_ `public List<CommitTagConfig> CommitTags { get; set; }` — List of tags to apply to commits. Allows fast searching and classification of different commit types (eg. code vs content).
- L250 _public property_ `public List<TabConfig> Tabs { get; set; }` — List of tabs to show for the new stream
- L255 _public property_ `public Dictionary<string, string>? Environment { get; set; }` — Global environment variables for all agents in this stream
- L260 _public property_ `public Dictionary<string, AgentConfig> AgentTypes { get; set; }` — Map of agent name to type
- L265 _public property_ `public Dictionary<string, WorkspaceConfig> WorkspaceTypes { get; set; }` — Map of workspace name to type
- L270 _public property_ `public List<TemplateRefConfig> Templates { get; set; }` — List of templates to create
- L276 _public property_ `public List<StreamAliasConfig> Aliases { get; set; }` — Stream aliases configured for this stream. Each alias provides a named subset of the stream's templates.
- L281 _public property_ `public AclConfig Acl { get; set; }` — Custom permissions for this object
- L286 _public property_ `public DateTime? PausedUntil { get; set; }` — Pause stream builds until specified date
- L291 _public property_ `public string? PauseComment { get; set; }` — Reason for pausing builds of the stream
- L296 _public property_ `public List<ReplicatorConfig> Replicators { get; set; }` — Configuration for workers to replicate commit data into Horde Storage.
- L301 _public property_ `public List<WorkflowConfig> Workflows { get; set; }` — Workflows for dealing with new issues
- L306 _public property_ `public List<TokenConfig> Tokens { get; set; }` — Tokens to create for each job step
- L311 _public property_ `public List<ArtifactTypeConfig> ArtifactTypes { get; set; }` — Permissions for artifact types
- L316 _public property_ `public List<StreamTag> StreamTags { get; set; }` — Tags for the stream
- L318 _private* field_ `readonly Dictionary<ArtifactType, ArtifactTypeConfig> _artifactTypeLookup = ...`
- L318 _private* field_ `readonly Dictionary< _artifactTypeLookup = new Dictionary<ArtifactType, ArtifactTypeConfig>()`
- L321 _public method_ `public bool Authorize(AclAction action, ClaimsPrincipal user)` — (inheritdoc)
- L331-484 _public method_ `public void PostLoad(StreamId id, ProjectConfig projectConfig, IEnumerable<ArtifactTypeConfig> parentArtifactTypes, ILogger? logger)` — Callback after reading this stream configuration
- L489 _public method_ `public IEnumerable<ArtifactTypeConfig> GetAllArtifactTypes()` — Get all artifact types for this stream
- L497 _public method_ `public bool TryGetArtifactType(ArtifactType type, [NotNullWhen(true)] out ArtifactTypeConfig? artifactTypeConfig)` — Finds an artifact type configuration block
- L500-508 _private* method_ `void EnsureDefaultArtifactType(ArtifactType artifactType)`
- L514-531 _public method_ `public IEnumerable<CommitTagConfig> GetAllCommitTags()` — Enumerates all commit tags, including the default tags for code and content.
- L539-562 _public method_ `public bool TryGetCommitTag(CommitTag tag, [NotNullWhen(true)] out CommitTagConfig? config)` — Gets the configuration for a commit tag
- L568-581 _public method_ `public bool TryGetCommitTagFilter(CommitTag tag, [NotNullWhen(true)] out FileFilter? filter)` — Constructs a FileFilter from the rules in this configuration object
- L586-610 _private* method_ `bool TryGetCommitTagFilter(CommitTag tag, FileFilter filter, HashSet<CommitTag> visitedTags)` — Find the filter for a given tag, recursively
- L618-622 _public method_ `public bool TryGetReplicator(StreamReplicatorId replicatorId, [NotNullWhen(true)] out ReplicatorConfig? replicatorConfig)` — Tries to find a replicator with the given id
- L630-634 _public method_ `public bool TryGetTemplate(TemplateId templateRefId, [NotNullWhen(true)] out TemplateRefConfig? templateConfig)` — Tries to find a template with the given id
- L642-646 _public method_ `public bool TryGetWorkflow(WorkflowId workflowId, [NotNullWhen(true)] out WorkflowConfig? workflowConfig)` — Tries to find a workflow with the given id
- L652-655 _public method_ `public string GetEscapedName()` — The escaped name of this stream. Removes all non-identifier characters.
- L661-664 _public method_ `public string GetDefaultWorkspaceIdentifier()` — Gets the default identifier for workspaces created for this stream. Just includes an escaped depot name.

#### class `HordeServer.Streams.TabConfig`  
`public class TabConfig : IStreamTab`  
_public; L670-704_
- inherits: `IStreamTab`
- desc: Information about a page to display in the dashboard for a stream
- L674 _public property_ `public string Title { get; set; }` — attrs: `[Required]` — (inheritdoc)
- L677 _public property_ `public string Type { get; set; }` — (inheritdoc)
- L680 _public property_ `public TabStyle Style { get; set; }` — (inheritdoc)
- L683-687 _public property_ `public bool ShowNames { get; set; }` — (inheritdoc)
- L688 _private* field_ `bool? _showNames`
- L691 _public property_ `public bool? ShowPreflights { get; set; }` — (inheritdoc)
- L694 _public property_ `public List<string>? JobNames { get; set; }` — (inheritdoc)
- L695 _private* property_ `IReadOnlyList<string>? IStreamTab.JobNames => ...`
- L698 _public property_ `public List<TemplateId>? Templates { get; set; }` — (inheritdoc)
- L699 _private* property_ `IReadOnlyList<TemplateId>? IStreamTab.Templates => ...`
- L702 _public property_ `public List<TabColumnConfig>? Columns { get; set; }` — (inheritdoc)
- L703 _private* property_ `IReadOnlyList<IStreamTabColumn>? IStreamTab.Columns => ...`

#### class `HordeServer.Streams.TabColumnConfig`  
`public class TabColumnConfig : IStreamTabColumn`  
_public; L709-726_
- inherits: `IStreamTabColumn`
- desc: Describes a column to display on the jobs page
- L712 _public property_ `public TabColumnType Type { get; set; }` — (inheritdoc)
- L716 _public property_ `public string Heading { get; set; }` — attrs: `[Required]` — (inheritdoc)
- L719 _public property_ `public string? Category { get; set; }` — (inheritdoc)
- L722 _public property_ `public string? Parameter { get; set; }` — (inheritdoc)
- L725 _public property_ `public int? RelativeWidth { get; set; }` — (inheritdoc)

#### class `HordeServer.Streams.AgentConfig`  
`public class AgentConfig : IAgentType`  
_public; L731-782_
- inherits: `IAgentType`
- desc: Mapping from a BuildGraph agent type to a set of machines on the farm
- L736 _public property_ `public string? Base { get; set; }` — Base agent config to inherit settings from
- L741 _public property_ `public PoolId Pool { get; set; }` — Pool of agents to use for this agent type
- L746 _public property_ `public string? Workspace { get; set; }` — Name of the workspace to sync
- L751 _public property_ `public string? TempStorageDir { get; set; }` — Path to the temporary storage dir
- L756 _public property_ `public Dictionary<string, string>? Environment { get; set; }` — Environment variables to be set when executing the job
- L757 _private* property_ `IReadOnlyDictionary<string, string>? IAgentType.Environment => ...`
- L763 _public property_ `public List<TokenConfig>? Tokens { get; set; }` — attrs: `[ConfigMergeStrategy(ConfigMergeStrategy.Append)]` — Tokens to allocate for this agent type
- L769-781 _public method_ `public RpcGetAgentTypeResponse ToRpcResponse()` — Creates an API response object from this stream

#### class `HordeServer.Streams.WorkspaceConfig`  
`public class WorkspaceConfig : IWorkspaceType`  
_public; L787-831_
- inherits: `IWorkspaceType`
- desc: Information about a workspace type
- L790 _public property_ `public string? Base { get; set; }` — (inheritdoc)
- L793 _public property_ `public string? Cluster { get; set; }` — (inheritdoc)
- L796 _public property_ `public string? ServerAndPort { get; set; }` — (inheritdoc)
- L799 _public property_ `public string? UserName { get; set; }` — (inheritdoc)
- L802 _public property_ `public string? Identifier { get; set; }` — (inheritdoc)
- L805 _public property_ `public string? Stream { get; set; }` — (inheritdoc)
- L809 _public property_ `public List<string>? View { get; set; }` — attrs: `[ConfigMergeStrategy(ConfigMergeStrategy.Append)]` — (inheritdoc)
- L810 _private* property_ `IReadOnlyList<string>? IWorkspaceType.View => ...`
- L813 _public property_ `public bool? Incremental { get; set; }` — (inheritdoc)
- L816 _public property_ `public bool? UseAutoSdk { get; set; }` — (inheritdoc)
- L820 _public property_ `public List<string>? AutoSdkView { get; set; }` — attrs: `[ConfigMergeStrategy(ConfigMergeStrategy.Append)]` — (inheritdoc)
- L821 _private* property_ `IReadOnlyList<string>? IWorkspaceType.AutoSdkView => ...`
- L824 _public property_ `public string? Method { get; set; }` — (inheritdoc)
- L827 _public property_ `public long? MinScratchSpace { get; set; }` — (inheritdoc)
- L830 _public property_ `public long? ConformDiskFreeSpace { get; set; }` — (inheritdoc)

#### class `HordeServer.Streams.DefaultPreflightConfig`  
`public class DefaultPreflightConfig : IDefaultPreflight`  
_public; L836-851_
- inherits: `IDefaultPreflight`
- desc: Specifies defaults for running a preflight
- L841 _public property_ `public TemplateId? TemplateId { get; set; }` — The template id to query
- L847 _public property_ `public ChangeQueryConfig? Change { get; set; }` — attrs: `[Obsolete("Set on template instead")]` — Query for the change to use
- L850 _private* property_ `IChangeQuery? IDefaultPreflight.Change => ...` — attrs: `[Obsolete("Set on template instead")]`

#### class `HordeServer.Streams.ChainedJobTemplateConfig`  
`public class ChainedJobTemplateConfig : IChainedJobTemplate`  
_public; L856-868_
- inherits: `IChainedJobTemplate`
- desc: Trigger for another template
- L860 _public property_ `public string Trigger { get; set; }` — attrs: `[Required]` — (inheritdoc)
- L864 _public property_ `public TemplateId TemplateId { get; set; }` — attrs: `[Required]` — (inheritdoc)
- L867 _public property_ `public bool UseDefaultChangeForTemplate { get; set; }` — (inheritdoc)

#### class `HordeServer.Streams.TemplateRefConfig`  
`public class TemplateRefConfig : TemplateConfig`  
_public; L874-971_
- attrs: `[DebuggerDisplay("{Id}")]`
- inherits: `TemplateConfig`
- desc: Parameters to create a template within a stream
- L880 _public property_ `public StreamConfig StreamConfig { get; set; }` — attrs: `[JsonIgnore]` — The owning stream config
- L885 _public property_ `public TemplateId Id { get; set; }` — Optional identifier for this ref. If not specified, an id will be generated from the name.
- L890 _public property_ `public TemplateId Base { get; set; }` — Base template id to copy from
- L895 _public property_ `public bool ShowUgsBadges { get; set; }` — Whether to show badges in UGS for these jobs
- L900 _public property_ `public bool ShowUgsAlerts { get; set; }` — Whether to show alerts in UGS for these jobs
- L905 _public property_ `public string? NotificationChannel { get; set; }` — Notification channel for this template. Overrides the stream channel if set.
- L910 _public property_ `public string? NotificationChannelFilter { get; set; }` — Notification channel filter for this template. Can be a combination of "Success", "Failure" and "Warnings" separated by pipe characters.
- L915 _public property_ `public string? TriageChannel { get; set; }` — Triage channel for this template. Overrides the stream channel if set.
- L920-924 _public property_ `public WorkflowId? WorkflowId { get; set; }` — Workflow to user for this stream
- L929 _public property_ `public NodeAnnotations Annotations { get; set; }` — Default annotations to apply to nodes in this template
- L935 _public property_ `public ScheduleConfig? Schedule { get; set; }` — attrs: `[ConfigMergeStrategy(ConfigMergeStrategy.Recursive)]` — Schedule to execute this template
- L941 _public property_ `public List<ChainedJobTemplateConfig>? ChainedJobs { get; set; }` — attrs: `[ConfigMergeStrategy(ConfigMergeStrategy.Append)]` — List of chained job triggers
- L947 _public property_ `public AclConfig Acl { get; set; }` — attrs: `[ConfigMergeStrategy(ConfigMergeStrategy.Recursive)]` — The ACL for this template
- L950 _public method_ `public bool Authorize(AclAction action, ClaimsPrincipal user)` — (inheritdoc)
- L957-970 _public method_ `public void PostLoad(StreamConfig streamConfig)` — Callback after the config is loaded

#### class `HordeServer.Streams.TokenConfig`  
`public class TokenConfig`  
_public; L976-1003_
- desc: Configuration for allocating access tokens for each job
- L982 _public property_ `public Uri Url { get; set; }` — attrs: `[Required]` — URL to request tokens from
- L989 _public property_ `public string ClientId { get; set; }` — attrs: `[Required] [ResolveSecret]` — Client id to use to request a new token
- L996 _public property_ `public string ClientSecret { get; set; }` — attrs: `[Required] [ResolveSecret]` — Client secret to request a new access token
- L1002 _public property_ `public string EnvVar { get; set; }` — attrs: `[Required]` — Environment variable to set with the access token

#### class `HordeServer.Streams.StreamAliasConfig`  
`public class StreamAliasConfig : IStreamAlias`  
_public; L1008-1018_
- inherits: `IStreamAlias`
- desc: Configuration for a stream alias, which represents a named subset of templates
- L1012 _public property_ `public string Name { get; set; }` — attrs: `[Required]` — (inheritdoc)
- L1016 _public property_ `public List<TemplateId> Templates { get; set; }` — attrs: `[Required]` — (inheritdoc)
- L1017 _private* property_ `IReadOnlyList<TemplateId> IStreamAlias.Templates => ...`

#### class `HordeServer.Streams.CommitTagConfig`  
`public class CommitTagConfig`  
_public; L1023-1058_
- desc: Configuration for custom commit filters
- L1029 _public property_ `public CommitTag Name { get; set; }` — attrs: `[Required]` — Name of the tag
- L1034 _public property_ `public CommitTag Base { get; set; }` — Base tag to copy settings from
- L1039 _public property_ `public List<string> Filter { get; set; }` — List of files to be included in this filter
- L1044 _public property_ `public static CommitTagConfig CodeDefault { get; }` — Default config for code filters
- L1053 _public property_ `public static CommitTagConfig ContentDefault { get; }` — Default config for content filters

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Streams/StreamsController.cs` (HordeServer.Build)


#### class `HordeServer.Streams.StreamsController`  
`public class StreamsController : HordeControllerBase`  
_public; L35-643_
- attrs: `[ApiController] [Authorize] [Route("[controller]")]`
- inherits: `HordeControllerBase`
- desc: Controller for the /api/v1/streams endpoint
- L37 _private field_ `private readonly IStreamCollection _streamCollection`
- L38 _private field_ `private readonly ICommitService _commitService`
- L39 _private field_ `private readonly ITemplateCollectionInternal _templateCollection`
- L40 _private field_ `private readonly IJobStepRefCollection _jobStepRefCollection`
- L41 _private field_ `private readonly IUserCollection _userCollection`
- L42 _private field_ `private readonly ScheduleService _scheduleService`
- L43 _private field_ `private readonly Tracer _tracer`
- L44 _private field_ `private readonly ILogger _logger`
- L45 _private field_ `private readonly IOptionsSnapshot<BuildConfig> _buildConfig`
- L46 _private field_ `private readonly TimeZoneInfo _timeZone`
- L51-63 _public ctor_ `public StreamsController(IStreamCollection streamCollection, ICommitService commitService, ITemplateCollectionInternal templateCollection, IJobStepRefCollection jobStepRefCollection, IUserCollection userCollection, ScheduleService scheduleService, Tracer tracer, IClock clock, IOptionsSnapshot<BuildConfig> buildConfig, ILogger<StreamsController> logger)` — Constructor
- L75-105 _public method_ `public async Task<ActionResult<List<object>>> GetStreamsAsync([FromQuery(Name = "ProjectId")] string[] projectIds, [FromQuery] PropertyFilter? filter = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/streams")] [ProducesResponseType(typeof(List<GetStreamResponse>), 200)]` — Query all the streams for a particular project.
- L117-136 _public method_ `public async Task<ActionResult<object>> GetStreamAsync(StreamId streamId, [FromQuery] PropertyFilter? filter = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/streams/{streamId}")] [ProducesResponseType(typeof(GetStreamResponse), 200)]` — Retrieve information about a specific stream.
- L145-187 _private* method_ `async Task<GetStreamResponse> CreateGetStreamResponseAsync(IStream stream, StreamConfig streamConfig, CancellationToken cancellationToken)` — Create a stream response object, including all the templates
- L192 _public const_ `public const string MissingCommitsHeader = "X-Missing-Commits"` — Headers key utilized for expressing missing commits in GetChangesAsync and GetBatchedChangesAsync.
- L194 _private const_ `private const int MaxConcurrentSCMChangeRequests = 32`
- L217-264 _public method_ `public async Task<ActionResult<List<object>>> GetChangesAsync(StreamId streamId, [FromQuery] CommitId? min = null, [FromQuery] CommitId? max = null, [FromQuery] CommitId[]? changeNumbers = null, [FromQuery] int results = 50, [FromQuery] string? tags = null, PropertyFilter? filter = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/streams/{streamId}/changes")] [ProducesResponseType(typeof(List<GetCommitResponse>), 200)]` — Gets a list of changes for a stream
- L281-318 _public method_ `public async Task<ActionResult<List<object>>> GetBatchedChangesAsync(StreamId streamId, [FromBody] CommitId[]? changeNumbers = null, PropertyFilter? filter = null, CancellationToken cancellationToken = default)` — attrs: `[HttpPost] [Route("/api/v1/streams/{streamId}/changes")] [ProducesResponseType(typeof(List<GetCommitResponse>), 200)]` — Gets a list of changes for a stream
- L320-351 _private* method_ `async Task<(List<ICommit>, IReadOnlyCollection<string>)> GetBatchedCommitsAsync(StreamConfig streamConfig, CommitId[] changeNumbers, CancellationToken cancellationToken)`
- L353-366 _private* method_ `static GetCommitResponse CreateGetCommitResponse(ICommit commit, IUser author, IReadOnlyList<CommitTag>? tags, IReadOnlyList<string>? files)`
- L380-403 _public method_ `public async Task<ActionResult<object>> GetChangeDetailsAsync(StreamId streamId, CommitId changeNumber, int maxFiles = 100, PropertyFilter? filter = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/streams/{streamId}/changes/{changeNumber}")] [ProducesResponseType(typeof(GetCommitResponse), 200)]` — Gets a list of changes for a stream
- L419-441 _public method_ `public async Task<ActionResult<List<object>>> GetStepHistoryAsync(StreamId streamId, [FromQuery] string templateId, [FromQuery] string step, [FromQuery] CommitId? change = null, [FromQuery] int count = 10, [FromQuery] PropertyFilter? filter = null)` — attrs: `[HttpGet] [Route("/api/v1/streams/{streamId}/history")] [ProducesResponseType(typeof(List<GetJobStepRefResponse>), 200)]` — Gets the history of a step in the stream
- L443 _private const_ `private const int MaxConcurrentStepHistoryRequests = 32`
- L460-517 _public method_ `public async Task<ActionResult<List<object>>> GetStepHistoryAsync(StreamId streamId, [FromQuery] string templateId, [FromQuery] string[] steps, [FromQuery] CommitId? change = null, [FromQuery] int count = 10, [FromQuery] PropertyFilter? filter = null, CancellationToken cancellationToken = default)` — attrs: `[HttpPost] [Route("/api/v1/streams/{streamId}/history")] [ProducesResponseType(typeof(List<GetJobStepRefResponse>), 200)]` — Gets the history of a set of steps given a stream and template context.
- L523-542 _internal method_ `internal static GetJobStepRefResponse CreateGetJobStepRefResponse(IJobStepRef jobStepRef)` — Constructor
- L554-574 _public method_ `public async Task<ActionResult<object>> GetTemplateAsync(StreamId streamId, TemplateId templateId, [FromQuery] PropertyFilter? filter = null)` — attrs: `[HttpGet] [Route("/api/v1/streams/{streamId}/templates/{templateId}")] [ProducesResponseType(typeof(List<GetTemplateResponse>), 200)]` — Gets a template for a stream
- L588-615 _public method_ `public async Task<ActionResult> GetTemplateHistoryAsync(StreamId streamId, TemplateId templateId, [FromQuery] DateTime? minTime = null, [FromQuery] DateTime? maxTime = null, [FromQuery] int index = 0, [FromQuery] int count = 50)` — attrs: `[HttpGet] [Route("/api/v1/streams/{streamId}/templates/{templateId}/history")]` — Retrieve historical information about a specific schedule
- L623-642 _public method_ `public async Task<ActionResult> UpdateStreamTemplateRefAsync(StreamId streamId, TemplateId templateRefId, [FromBody] UpdateTemplateRefRequest update)` — attrs: `[HttpPut] [Authorize] [Route("/api/v1/streams/{streamId}/templates/{templateRefId}")]` — Update a stream template ref

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Tasks/ConformTaskSource.cs` (HordeServer.Build)


#### class `HordeServer.Tasks.ConformTaskSource`  
`public sealed class ConformTaskSource : TaskSourceBase<ConformTask>, IHostedService, IAsyncDisposable`  
_public; L26-415_
- inherits: `TaskSourceBase<ConformTask>, IHostedService, IAsyncDisposable`
- desc: Generates tasks telling agents to sync their workspaces
- L29 _public property_ `public override string Type => ...` — (inheritdoc)
- L32 _public property_ `public override TaskSourceFlags Flags => ...` — (inheritdoc)
- L34 _private* field_ `readonly IAgentCollection _agentCollection`
- L35 _private* field_ `readonly PoolService _poolService`
- L36 _private* field_ `readonly SingletonDocument<ConformList> _conformList`
- L37 _private* field_ `readonly PerforceLoadBalancer _perforceLoadBalancer`
- L38 _private* field_ `readonly ILogCollection _logCollection`
- L39 _private* field_ `readonly ILogger _logger`
- L40 _private* field_ `readonly IOptionsMonitor<BuildServerConfig> _settings`
- L41 _private* field_ `readonly IOptionsMonitor<BuildConfig> _buildConfig`
- L42 _private* field_ `readonly ITicker _tickConformList`
- L47-60 _public ctor_ `public ConformTaskSource(IMongoService mongoService, IAgentCollection agentCollection, PoolService poolService, ILogCollection logCollection, PerforceLoadBalancer perforceLoadBalancer, IClock clock, IOptionsMonitor<BuildServerConfig> settings, IOptionsMonitor<BuildConfig> buildConfig, ILogger<ConformTaskSource> logger)` — Constructor
- L63 _public method_ `public Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L66 _public method_ `public Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L69 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L76-108 _private* method_ `async ValueTask CleanConformListAsync(CancellationToken cancellationToken)` — Clean up the conform list of any outdated entries
- L116-123 _private* method_ `static void UpdateConformList(ConformList list, DateTime utcNow, Dictionary<LeaseId, bool> removeLeases)` — Remove items from the conform list, and update timestamps for them
- L131-148 _private* method_ `static void UpdateConformList(List<ConformListEntry> entries, DateTime utcNow, Dictionary<LeaseId, bool> removeLeases)` — Remove items from the conform list, and update timestamps for them
- L151-197 _public method_ `public override async Task<Task<CreateLeaseOptions?>> AssignLeaseAsync(IAgent agent, CancellationToken cancellationToken)` — (inheritdoc)
- L200-203 _public method_ `public override Task CancelLeaseAsync(IAgent agent, LeaseId leaseId, ConformTask payload, CancellationToken cancellationToken)` — (inheritdoc)
- L206-221 _public method_ `public async Task<bool> GetWorkspacesAsync(IAgent agent, IList<RpcAgentWorkspace> workspaces, CancellationToken cancellationToken)` — (inheritdoc)
- L224-227 _public method_ `public override Task OnLeaseFinishedAsync(IAgent agent, LeaseId leaseId, ConformTask payload, LeaseOutcome outcome, ReadOnlyMemory<byte> output, ILogger logger, CancellationToken cancellationToken)` — (inheritdoc)
- L237-293 _private method_ `private async Task<bool> AllocateConformLeaseAsync(AgentId agentId, IEnumerable<RpcAgentWorkspace> workspaces, LeaseId leaseId, CancellationToken cancellationToken)` — Atempt to allocate a conform resource for the given lease
- L301-317 _public method_ `public async Task ReleaseConformLeaseAsync(LeaseId leaseId, CancellationToken cancellationToken)` — Terminate a conform lease
- L326-382 _private method_ `private async Task<bool> IsConformPendingAsync(IAgent agent, DateTime utcNow, CancellationToken cancellationToken)` — Determine if an agent should be conformed
- L390-414 _private method_ `private static bool IsConformCoolDownPeriod(IAgent agent, DateTime utcNow)` — Determines if the given agent is in a cooldown period, waiting to retry after a failed conform

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Ugs/IUgsMetadataCollection.cs` (HordeServer.Build)


#### interface `HordeServer.Ugs.IUgsMetadataCollection`  
`public interface IUgsMetadataCollection`  
_public; L10-58_
- desc: Collection of stream documents
- L20 _public* method_ `Task<IUgsMetadata> FindOrAddAsync(string stream, int change, string? project, CancellationToken cancellationToken = default)` — Finds or adds metadata for a given changelist
- L34 _public* method_ `Task<IUgsMetadata> UpdateUserAsync(IUgsMetadata metadata, string userName, bool? synced, UgsUserVote? vote, bool? investigating, bool? starred, string? comment, CancellationToken cancellationToken = default)` — Adds information to a change
- L45 _public* method_ `Task<IUgsMetadata> UpdateBadgeAsync(IUgsMetadata metadata, string name, Uri? url, UgsBadgeState state, CancellationToken cancellationToken = default)` — Updates the state of a badge
- L57 _public* method_ `Task<List<IUgsMetadata>> FindAsync(string stream, IReadOnlyList<int>? changes, int? minChange, int? maxChange = null, long? afterTicks = null, CancellationToken cancellationToken = default)` — Searches for metadata updates

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Ugs/UgsController.cs` (HordeServer.Build)


#### class `HordeServer.Ugs.UgsController`  
`public sealed class UgsController : ControllerBase`  
_public; L23-428_
- attrs: `[ApiController] [Route("[controller]")]`
- inherits: `ControllerBase`
- desc: Controller for the /api/v1/issues endpoint
- L25 _private* field_ `readonly IssueService _issueService`
- L26 _private* field_ `readonly IUgsMetadataCollection _ugsMetadataCollection`
- L27 _private* field_ `readonly IUserCollection _userCollection`
- L28 _private* field_ `readonly ILogCollection _logCollection`
- L29 _private* field_ `readonly IServerInfo _serverInfo`
- L30 _private* field_ `readonly ILogger _logger`
- L35-43 _public ctor_ `public UgsController(IssueService issueService, IUgsMetadataCollection ugsMetadataCollection, IUserCollection userCollection, ILogCollection logCollection, IServerInfo serverInfo, ILogger<UgsController> logger)` — Constructor
- L51-55 _public method_ `public ActionResult<object> GetLatest()` — attrs: `[HttpGet] [Route("/ugs/api/latest")]` — Gets the latest version info
- L64-86 _public method_ `public async Task<ActionResult> AddMetadataAsync(AddUgsMetadataRequest request)` — attrs: `[HttpPost] [Route("/ugs/api/metadata")]` — Adds new metadata to the database
- L100-128 _public method_ `public async Task<GetUgsMetadataListResponse> FindMetadataAsync([FromQuery] string stream, [FromQuery(Name = "change")] List<int>? changes = null, [FromQuery] int? minChange = null, [FromQuery] int? maxChange = null, [FromQuery(Name = "project")] List<string>? projects = null, [FromQuery] long? sequence = null)` — attrs: `[HttpGet] [Route("/ugs/api/metadata")]` — Searches for metadata updates
- L130-139 _private* method_ `static GetUgsMetadataResponse CreateGetUgsMetadataResponse(IUgsMetadata metadata)`
- L141-152 _private* method_ `static GetUgsUserResponse CreateGetUgsUserResponse(IUgsUserData userData)`
- L154-162 _private* method_ `static GetUgsBadgeResponse CreateGetUgsBadgeResponse(IUgsBadgeData badgeData)`
- L175-207 _public method_ `public async Task<ActionResult<List<GetUgsIssueResponse>>> GetIssuesAsync([FromQuery] string? user = null, [FromQuery] bool includeResolved = false, [FromQuery] int maxResults = 100, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/ugs/api/issues")] [ProducesResponseType(typeof(GetUgsIssueResponse), 200)]` — Retrieve information about open issues
- L219-228 _public method_ `public async Task<ActionResult<object>> GetIssueAsync(int issueId, [FromQuery] PropertyFilter? filter = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/ugs/api/issues/{issueId}")] [ProducesResponseType(typeof(GetUgsIssueBuildResponse), 200)]` — Retrieve information about a specific issue
- L240-266 _public method_ `public async Task<ActionResult<List<object>>> GetIssueBuildsAsync(int issueId, [FromQuery] PropertyFilter? filter = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/ugs/api/issues/{issueId}/builds")] [ProducesResponseType(typeof(List<GetUgsIssueBuildResponse>), 200)]` — Retrieve information about builds for a specific issue
- L277-295 _public method_ `public async Task<ActionResult<List<GetUgsIssueDiagnosticResponse>>> GetIssueDiagnosticsAsync(int issueId, CancellationToken cancellationToken)` — attrs: `[HttpGet] [Route("/ugs/api/issues/{issueId}/diagnostics")] [ProducesResponseType(typeof(List<GetUgsIssueDiagnosticResponse>), 200)]` — Retrieve information about builds for a specific issue
- L304-312 _private* method_ `async Task<GetUgsIssueResponse> CreateIssueResponseAsync(IIssueDetails details, bool notify, CancellationToken cancellationToken)` — Gets the URL for a failing step in the
- L314-334 _private* method_ `static GetUgsIssueResponse CreateGetUgsIssueResponse(IIssueDetails details, IUser? owner, IUser? nominatedBy, bool notify, Uri? buildUrl)`
- L341-352 _private* method_ `Uri? GetIssueBuildUrl(IIssueDetails issue)` — Gets the URL for a failing step in the given issue
- L361-371 _private* method_ `GetUgsIssueBuildResponse CreateBuildResponse(IIssueSpan span, IIssueStep step, IssueBuildOutcome outcome)` — Creates the response for a particular build
- L381-416 _public method_ `public async Task<ActionResult> UpdateIssueAsync(int issueId, [FromBody] UpdateUgsIssueRequest request)` — attrs: `[HttpPut] [Route("/ugs/api/issues/{issueId}")]` — Update an issue
- L423-427 _public method_ `public ActionResult<object> PostNetCoreInfo(string? user = null, string? machine = null, bool netCore = false)` — attrs: `[HttpPost] [Route("/ugs/api/netcore")]` — Post information about net core installation.

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Ugs/UgsMetadata.cs` (HordeServer.Build)


#### interface `HordeServer.Ugs.IUgsUserData`  
`public interface IUgsUserData`  
_public; L10-41_
- desc: Metadata for a particular user
- L15 _public* property_ `string User { get; }` — The user name
- L20 _public property_ `public long? SyncTime { get; }` — Time that this change was synced
- L25 _public property_ `public UgsUserVote Vote { get; }` — State of the user
- L30 _public* property_ `bool? Starred { get; }` — Whether the change is starred
- L35 _public* property_ `bool? Investigating { get; }` — Whether the change is under investigation
- L40 _public* property_ `string? Comment { get; }` — Comment text

#### interface `HordeServer.Ugs.IUgsBadgeData`  
`public interface IUgsBadgeData`  
_public; L46-62_
- desc: Metadata for a badge
- L51 _public* property_ `string Name { get; }` — The badge name
- L56 _public* property_ `Uri? Url { get; }` — The URL to open when the badge is clicked
- L61 _public* property_ `UgsBadgeState State { get; }` — State of the badge

#### interface `HordeServer.Ugs.IUgsMetadata`  
`public interface IUgsMetadata`  
_public; L67-98_
- desc: Metadata for a particular changelist and project
- L72 _public* property_ `int Change { get; }` — The changelist number
- L77 _public* property_ `string Stream { get; }` — Stream for the metadata
- L82 _public* property_ `string Project { get; }` — The project identifier
- L87 _public* property_ `IReadOnlyList<IUgsUserData>? Users { get; }` — List of user states
- L92 _public* property_ `IReadOnlyList<IUgsBadgeData>? Badges { get; }` — List of badge states
- L97 _public* property_ `long UpdateTicks { get; }` — Time that this object was last updated

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Ugs/UgsMetadataCollection.cs` (HordeServer.Build)


#### class `HordeServer.Ugs.UgsMetadataCollection`  
`class UgsMetadataCollection : IUgsMetadataCollection`  
_internal*; L17-368_
- inherits: `IUgsMetadataCollection`
- desc: Concrete implementation of IUgsMetadataCollection
- L87 _private* field_ `readonly IMongoCollection<UgsMetadataDocument> _collection`
- L88 _private* field_ `readonly ILogger<UgsMetadataCollection> _logger`
- L93-100 _public ctor_ `public UgsMetadataCollection(IMongoService mongoService, ILogger<UgsMetadataCollection> logger)` — Constructor
- L110-138 _public method_ `public async Task<IUgsMetadata> FindOrAddAsync(string stream, int change, string? project, CancellationToken cancellationToken)` — Find or add a document for the given change
- L141-217 _public method_ `public async Task<IUgsMetadata> UpdateUserAsync(IUgsMetadata metadata, string userName, bool? synced, UgsUserVote? vote, bool? investigating, bool? starred, string? comment, CancellationToken cancellationToken)` — (inheritdoc)
- L220-269 _public method_ `public async Task<IUgsMetadata> UpdateBadgeAsync(IUgsMetadata metadata, string name, Uri? url, UgsBadgeState state, CancellationToken cancellationToken)` — (inheritdoc)
- L272-304 _public method_ `public async Task<List<IUgsMetadata>> FindAsync(string stream, IReadOnlyList<int>? changes = null, int? minChange = null, int? maxChange = null, long? minTime = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L312-315 _private method_ `private static string GetNormalizedStream(string stream)` — attrs: `[SuppressMessage("Globalization", "CA1308:Normalize strings to uppercase")]` — Normalize a stream argument
- L323-333 _private method_ `private static string GetNormalizedProject(string? project)` — attrs: `[SuppressMessage("Globalization", "CA1308:Normalize strings to uppercase")]` — Normalize a project argument
- L342-367 _private method_ `private async Task<bool> TryUpdateAsync(UgsMetadataDocument document, UpdateDefinition<UgsMetadataDocument> update, CancellationToken cancellationToken)` — Try to update a metadata document

#### class `HordeServer.Ugs.UgsMetadataCollection.UgsUserDataDocument`  
`class UgsUserDataDocument : IUgsUserData`  
_private*; L19-46_
- inherits: `IUgsUserData`
- L21 _public property_ `public string User { get; set; }`
- L24 _public property_ `public long? SyncTime { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L27 _public property_ `public UgsUserVote? Vote { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L30 _public property_ `public bool? Starred { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L33 _public property_ `public bool? Investigating { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L36 _public property_ `public string? Comment { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L38 _private* property_ `string IUgsUserData.User => ...`
- L39 _private* property_ `long? IUgsUserData.SyncTime => ...`
- L40 _private* property_ `UgsUserVote IUgsUserData.Vote => ...`
- L42-45 _public ctor_ `public UgsUserDataDocument(string user)`

#### class `HordeServer.Ugs.UgsMetadataCollection.UgsBadgeDataDocument`  
`class UgsBadgeDataDocument : IUgsBadgeData`  
_private*; L48-56_
- inherits: `IUgsBadgeData`
- L50 _public property_ `public string Name { get; set; }`
- L53 _public property_ `public Uri? Url { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L55 _public property_ `public UgsBadgeState State { get; set; }`

#### class `HordeServer.Ugs.UgsMetadataCollection.UgsMetadataDocument`  
`class UgsMetadataDocument : IUgsMetadata`  
_private*; L58-85_
- inherits: `IUgsMetadata`
- L60 _public property_ `public ObjectId Id { get; set; }`
- L61 _public property_ `public string Stream { get; set; }`
- L62 _public property_ `public int Change { get; set; }`
- L63 _public property_ `public string Project { get; set; }`
- L64 _public property_ `public List<UgsUserDataDocument> Users { get; set; }`
- L65 _public property_ `public List<UgsBadgeDataDocument> Badges { get; set; }`
- L66 _public property_ `public int UpdateIndex { get; set; }`
- L67 _public property_ `public long UpdateTicks { get; set; }`
- L69 _private* property_ `IReadOnlyList<IUgsUserData>? IUgsMetadata.Users => ...`
- L70 _private* property_ `IReadOnlyList<IUgsBadgeData>? IUgsMetadata.Badges => ...`
- L73-76 _private ctor_ `private UgsMetadataDocument()` — attrs: `[BsonConstructor]`
- L78-84 _public ctor_ `public UgsMetadataDocument(string stream, int change, string project)`

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Utilities/ConformUtilities.cs` (HordeServer.Build)


#### class `HordeServer.Utilities.ConformUtilities`  
`public static class ConformUtilities`  
_public; L13-53_
- desc: Utilities for conforming agents
- L24-52 _public method_ `public static async Task<bool> AutoConformAgentAsync(IAgent agent, PoolService poolService, BuildConfig config, ILogger logger, CancellationToken cancellationToken)` — Conform an agent that is below the disk free conform threshold for a workspace

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Utilities/OpenTelemetryExtensions.cs` (HordeServer.Build)


#### class `HordeServer.Utilities.OpenTelemetryExtensions`  
`public static class OpenTelemetryExtensions`  
_public; L14-40_
- desc: Extensions for OpenTelemetry spans
- L18-22 _public method_ `public static TelemetrySpan SetAttribute(this TelemetrySpan span, string key, ContentHash value)` — Set a key:value tag on the span
- L26-30 _public method_ `public static TelemetrySpan SetAttribute(this TelemetrySpan span, string key, SubResourceId value)` — Set a key:value tag on the span
- L33 _public method_ `public static TelemetrySpan SetAttribute(this TelemetrySpan span, string key, StreamId? value)` — (inheritdoc)
- L36 _public method_ `public static TelemetrySpan SetAttribute(this TelemetrySpan span, string key, TemplateId? value)` — (inheritdoc)
- L39 _public method_ `public static TelemetrySpan SetAttribute(this TelemetrySpan span, string key, TemplateId[]? values)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/Utilities/TransactionBuilder.cs` (HordeServer.Build)


#### class `HordeServer.Utilities.TransactionBuilder`  
`public class TransactionBuilder<TDocument> where TDocument : class`  
_public; L13-296_
- constraints: `where TDocument : class`
- desc: Allows building a transactional MongoDB update of several fields, and applying those to an in-memory object. Useful for transactional updates.
- L73 _private* field_ `readonly List<FieldUpdate> _fieldUpdates = new List<FieldUpdate>()` — List of field updates
- L78 _public property_ `public bool IsEmpty => ...` — Whether the transaction is currenty empty
- L86-91 _public method_ `public void Set<TField>(Expression<Func<TDocument, TField>> expr, TField value)` — Adds a setting to this transaction
- L97-102 _public method_ `public void Unset(Expression<Func<TDocument, object>> expr)` — Adds an update to remove a field
- L109-126 _public method_ `public void UpdateDictionary<TKey, TValue>(Expression<Func<TDocument, Dictionary<TKey, TValue>>> expr, IEnumerable<KeyValuePair<TKey, TValue?>> updates) where TKey : class where TValue : class` — Updates a property dictionary with a set of adds and removes
- L132-138 _public method_ `public void ApplyTo(TDocument target)` — Applies this transaction to the given update
- L146-187 _private* method_ `static void Assign(object? target, LambdaExpression fieldExpression, object? value)` — Assign a value to a field
- L194-234 _private* method_ `static void Unassign(object? target, Expression body)` — Removes an entry from a dictionary
- L242-287 _private* method_ `static object? Evaluate(Expression expression, object? parameter)` — Evaluates an expression
- L292-295 _public method_ `public UpdateDefinition<TDocument> ToUpdateDefinition()` — Converts this transaction to an update definition

#### class `HordeServer.Utilities.TransactionBuilder.FieldUpdate`  
`class FieldUpdate`  
_private*; L18-40_
- desc: Information about an update to a field
- L23 _public field_ `public UpdateDefinition<TDocument> _update` — The update definition
- L28 _public field_ `public Action<object> _apply` — Applies an update to the given object
- L35-39 _public ctor_ `public FieldUpdate(UpdateDefinition<TDocument> update, Action<object> apply)` — Constructor

#### class `HordeServer.Utilities.TransactionBuilder.Reflection`  
`static class Reflection<T>`  
_private*; L46-68_
- desc: Helper class for determining the indexer for a particular type
- L51 _public property_ `public static PropertyInfo Indexer { get; }` — Caches the indexer for this type
- L57-67 _private* method_ `static PropertyInfo GetIndexerProperty()` — Finds the indexer property from a type

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/VersionControl/IVersionControlService.cs` (HordeServer.Build)


#### interface `HordeServer.VersionControl.IVersionControlService`  
`public interface IVersionControlService`  
_public; L11-24_
- desc: Version Control interface
- L16 _public* property_ `string Name { get; }` — Name of the service
- L23 _public method_ `public ICommitCollection GetCommits(StreamConfig streamConfig)` — Creates a commit source for the given stream

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/VersionControl/Perforce/ChangelistFileReader.cs` (HordeServer.Build)


#### class `HordeServer.VersionControl.Perforce.ChangelistFileReader`  
`public class ChangelistFileReader : IChangelistFileReader`  
_public; L12-69_
- inherits: `IChangelistFileReader`
- desc: Reads config files from shelved Perforce changelists for diff/validation.
- L14 _private* field_ `readonly IPerforceService _perforceService`
- L15 _private* field_ `readonly ILogger<ChangelistFileReader> _logger`
- L20-24 _public ctor_ `public ChangelistFileReader(IPerforceService perforceService, ILogger<ChangelistFileReader> logger)` — Constructor
- L27-68 _public method_ `public async Task<Dictionary<Uri, byte[]>> ReadChangelistFilesAsync( int changelist, string? cluster, CancellationToken cancellationToken)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/VersionControl/Perforce/CommitTelemetry.cs` (HordeServer.Build)


#### record `HordeServer.VersionControl.Perforce.CommitTelemetry`  
`public record CommitTelemetry : AbstractTelemetryRecord`  
_public; L20-189_
- attrs: `[AnalyticsTableGen] [TelemetryEvent(DefaultEventName)] [Table("horde.state_change", Schema = "ingest")]`
- inherits: `AbstractTelemetryRecord`
- desc: Record used for Commit telemetry. Models a ICommit.
- L25 _public const_ `public const string UnableToSourceUserId = "NoUserIdFound"` — Identifier used when no corresponding user Id can be found when enacting user-to-userId conversion.
- L30 _public const_ `public const string DefaultEventName = "State.Change"` — Default event name for the CommitTelemetry.
- L35 _public field_ `public static readonly int CurrentSchemaVersion = 5` — Current schema version.
- L41 _public property_ `public UserId SubmittedBy { get; init; }` — attrs: `[Column("submitted_by")]` — The user who submitted this commit.
- L47 _public property_ `public StreamId StreamId { get; init; }` — attrs: `[Column("stream_id")]` — The stream this commit belongs to.
- L53 _public property_ `public int Change { get; init; }` — attrs: `[Column("change")]` — The change number.
- L59 _public property_ `public int OriginalChange { get; init; }` — attrs: `[Column("original_change")]` — The original change number (before any merges).
- L65 _public property_ `public DateTime SubmittedAt { get; init; }` — attrs: `[Column("submitted_at")]` — The time the commit was submitted.
- L71 _public property_ `public string? ExternalIssueKey { get; init; }` — attrs: `[Column("external_issue_key")]` — The external issue key (e.g., Jira ticket).
- L77 _public property_ `public string? RobomergeAuthorTag { get; init; }` — attrs: `[Column("robomerge_author_tag")]` — The Robomerge author tag.
- L83 _public property_ `public string? RobomergeSourceTag { get; init; }` — attrs: `[Column("robomerge_source_tag")]` — The Robomerge source tag.
- L89 _public property_ `public string? RobomergeOwnerTag { get; init; }` — attrs: `[Column("robomerge_owner_tag")]` — The Robomerge owner tag.
- L95 _public property_ `public string? RobomergeBotTag { get; init; }` — attrs: `[Column("robomerge_bot_tag")]` — The Robomerge bot tag.
- L101 _public property_ `public string? ReviewTag { get; init; }` — attrs: `[Column("review_tag")]` — The review tag.
- L107 _public property_ `public string? PreflightTag { get; init; }` — attrs: `[Column("preflight_tag")]` — The preflight tag.
- L113 _public property_ `public string? Virtualized { get; init; }` — attrs: `[Column("virtualized")]` — The virtualized tag.
- L119-126 _public ctor_ `public CommitTelemetry() : base(DefaultEventName, CurrentSchemaVersion)` — Default constructor for an empty telemetry object.
- L134-149 _public ctor_ `public CommitTelemetry(ICommit commit, CommitDescriptionTagContainer commitTagContainer) : base(DefaultEventName, CurrentSchemaVersion)` — Constructs a CommitTelemetry event based on the provided commit and commit tag container.
- L159-188 _public method_ `public static async Task<CommitTelemetry> CreateCommitTelemetryWithUserIdAsync(IUserCollection userCollection, ICommit commit, CommitDescriptionTagContainer commitTagContainer)` — Create method used to construct a CommitTelemetry record.

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/VersionControl/Perforce/IPerforceService.cs` (HordeServer.Build)


#### enum `HordeServer.VersionControl.Perforce.CheckShelfResult`  
`public enum CheckShelfResult`  
_public; L15-41_
- desc: Result from checking a shelved change status
- L20 _public* enumerator_ `Ok` — The shelf is ok
- L25 _public* enumerator_ `NoChange` — Changelist does not exist
- L30 _public* enumerator_ `NoShelvedFiles` — The change does not contain any shelved files
- L35 _public* enumerator_ `MixedStream` — The shelf contains *some* files from a different stream
- L40 _public* enumerator_ `WrongStream` — The shelf contains only files from a different stream

#### class `HordeServer.VersionControl.Perforce.ShelfInfo`  
`public class ShelfInfo`  
_public; L46-66_
- desc: Information about a shelved change
- L51 _public property_ `public string Description { get; set; }` — Description for the change
- L56 _public property_ `public List<CommitTag> Tags { get; set; }` — Tags for the change
- L61-65 _public ctor_ `public ShelfInfo(string description, List<CommitTag> tags)` — Constructor

#### interface `HordeServer.VersionControl.Perforce.IPooledPerforceConnection`  
`public interface IPooledPerforceConnection : IPerforceConnection, IDisposable`  
_public; L71-92_
- inherits: `IPerforceConnection, IDisposable`
- desc: A connection returned by the Perforce service
- L76 _public* property_ `ClientRecord? Client { get; }` — The client used by the connection
- L83 _public* method_ `ValueTask<InfoRecord> GetInfoAsync(CancellationToken cancellationToken)` — Gets the server information, returning a cached copy if possible
- L91 _public* method_ `ValueTask<PerforceViewMap> GetCachedStreamViewAsync(StreamConfig streamConfig, CancellationToken cancellationToken)` — Gets a cached stream view for the given stream

#### class `HordeServer.VersionControl.Perforce.PooledPerforceConnectionExtensions`  
`public static class PooledPerforceConnectionExtensions`  
_public; L97-126_
- desc: Extension methods for PerforceService
- L107-110 _public method_ `public static Task<List<string>> GetStreamFilesAsync(this IPooledPerforceConnection perforce, StreamConfig streamConfig, DescribeRecord describeRecord, CancellationToken cancellationToken)` — Map files from a DescribeRecord to relative paths within a stream
- L120-125 _public method_ `public static async Task<List<string>> GetStreamFilesAsync(this IPooledPerforceConnection perforce, StreamConfig streamConfig, List<string> depotPaths, CancellationToken cancellationToken)` — Map files from a DescribeRecord to relative paths within a stream

#### interface `HordeServer.VersionControl.Perforce.IPerforceService`  
`public interface IPerforceService : IVersionControlService`  
_public; L131-204_
- inherits: `IVersionControlService`
- desc: Wrapper around Perforce functionality. Can use a local p4.exe client for development purposes, or a separate HordePerforceBridge instance over REST for deployments.
- L138 _public method_ `public Task RefreshCachedCommitAsync(string clusterName, int change)` — Refreshes any cached metadata for the given change
- L147 _public method_ `public Task<IPooledPerforceConnection> ConnectAsync(string clusterName, string? userName = null, CancellationToken cancellationToken = default)` — Connect to the given Perforce cluster
- L156 _public method_ `public ValueTask<IUser> FindOrAddUserAsync(string clusterName, string userName, CancellationToken cancellationToken = default)` — Finds or adds a user from the given Perforce server, adding the user (and populating their profile with Perforce data) if they do not currently exist
- L165 _public method_ `public Task<(CheckShelfResult, ShelfInfo?)> CheckShelfAsync(StreamConfig streamConfig, int changeNumber, CancellationToken cancellationToken = default)` — Checks a shelf is valid for the given stream
- L174 _public method_ `public Task<int> DuplicateShelvedChangeAsync(string clusterName, int shelvedChange, CancellationToken cancellationToken = default)` — Duplicates a shelved changelist
- L184 _public method_ `public Task<(int? Change, string Message)> SubmitShelvedChangeAsync(StreamConfig streamConfig, int shelvedChange, int originalChange, CancellationToken cancellationToken = default)` — Submit a shelved changelist
- L193 _public method_ `public Task DeleteShelvedChangeAsync(string clusterName, int shelvedChange, CancellationToken cancellationToken = default)` — Deletes a changelist containing shelved files.
- L203 _public method_ `public Task UpdateChangelistDescriptionAsync(string clusterName, int change, Func<string, string> updateFunc, CancellationToken cancellationToken = default)` — Updates a changelist description

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/VersionControl/Perforce/PerforceConfigSource.cs` (HordeServer.Build)


#### class `HordeServer.VersionControl.Perforce.PerforceConfigSource`  
`public sealed class PerforceConfigSource : IConfigSource`  
_public; L17-218_
- inherits: `IConfigSource`
- desc: Perforce cluster config file source
- L43 _public const_ `public const string Scheme = "perforce"` — Name of the scheme for this source
- L46 _private* property_ `string IConfigSource.Scheme => ...` — (inheritdoc)
- L49 _public property_ `public TimeSpan UpdateInterval => ...` — (inheritdoc)
- L51 _private* field_ `readonly IOptionsMonitor<BuildServerConfig> _settings`
- L52 _private* field_ `readonly IUserCollection _userCollection`
- L53 _private* field_ `readonly IMemoryCache _cache`
- L54 _private* field_ `readonly ILogger _logger`
- L59-65 _public ctor_ `public PerforceConfigSource(IOptionsMonitor<BuildServerConfig> settings, IUserCollection userCollection, IMemoryCache cache, ILogger<PerforceConfigSource> logger)` — Constructor
- L68-102 _public method_ `public async Task<IConfigFile[]> GetFilesAsync(Uri[] uris, CancellationToken cancellationToken)` — (inheritdoc)
- L104-118 _private* method_ `async ValueTask<IUser?> GetAuthorAsync(IPerforceConnection perforce, string host, int change, CancellationToken cancellationToken)`
- L120-144 _private* method_ `async ValueTask<ReadOnlyMemory<byte>> ReadAsync(Uri uri, int change, CancellationToken cancellationToken)`
- L146-177 _private* method_ `async Task<IPerforceConnection> ConnectAsync(string host, CancellationToken cancellationToken)`
- L180-204 _public method_ `public async Task GetUpdateInfoAsync(IReadOnlyDictionary<Uri, string> files, IReadOnlyDictionary<Uri, string>? prevFiles, ConfigUpdateInfo updateInfo, CancellationToken cancellationToken)` — (inheritdoc)
- L206-217 _private* method_ `async Task FindAuthorsAsync(IPerforceConnection perforce, string fileSpec, HashSet<UserId> authors, CancellationToken cancellationToken)`

#### class `HordeServer.VersionControl.Perforce.PerforceConfigSource.ConfigFileImpl`  
`class ConfigFileImpl : IConfigFile`  
_private*; L19-38_
- inherits: `IConfigFile`
- L21 _public property_ `public Uri Uri { get; }`
- L22 _public property_ `public int Change { get; }`
- L23 _public property_ `public string Revision { get; }`
- L24 _public property_ `public IUser? Author { get; }`
- L26 _private* field_ `readonly PerforceConfigSource _owner`
- L28-35 _public ctor_ `public ConfigFileImpl(Uri uri, int change, IUser? author, PerforceConfigSource owner)`
- L37 _public method_ `public ValueTask<ReadOnlyMemory<byte>> ReadAsync(CancellationToken cancellationToken)`

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/VersionControl/Perforce/PerforceController.cs` (HordeServer.Build)


#### class `HordeServer.VersionControl.Perforce.PerforceController`  
`public class PerforceController : ControllerBase`  
_public; L21-70_
- attrs: `[Authorize] [ApiController] [Route("[controller]")]`
- inherits: `ControllerBase`
- desc: Controller for Perforce triggers and callbacks
- L23 _private field_ `private readonly PerforceLoadBalancer _perforceLoadBalancer`
- L24 _private field_ `private readonly IOptionsSnapshot<BuildConfig> _buildConfig`
- L29-33 _public ctor_ `public PerforceController(PerforceLoadBalancer perforceLoadBalancer, IOptionsSnapshot<BuildConfig> buildConfig)` — Constructor
- L41-51 _public method_ `public async Task<ActionResult<List<object>>> GetStatusAsync(CancellationToken cancellationToken)` — attrs: `[HttpGet] [Route("/api/v1/perforce/status")]` — Get the current server status
- L59-69 _public method_ `public ActionResult<List<PerforceCluster>> GetPerforceSettings()` — attrs: `[HttpGet] [Route("/api/v1/perforce/settings")]` — Gets the current perforce settinsg

#### class `HordeServer.VersionControl.Perforce.PerforceTriggerRequest`  
`public class PerforceTriggerRequest`  
_public; L75-245_
- desc: Body of Perforce trigger request (deserialized from JSON)
- L80 _public property_ `public string TriggerType { get; }` — Type of trigger (change-commit, form-save etc)
- L85 _public property_ `public string Client { get; }` — Triggering user’s client workspace name.
- L90 _public property_ `public string ClientHost { get; }` — Hostname of the user’s workstation (even if connected through a proxy, broker, replica, or an edge server.)
- L95 _public property_ `public string ClientIp { get; }` — The IP address of the user’s workstation (even if connected through a proxy, broker, replica, or an edge server.)
- L100 _public property_ `public string ClientProg { get; }` — The name of the user’s client application. For example, P4V, P4Win
- L105 _public property_ `public string ClientVersion { get; }` — The version of the user’s client application.
- L111 _public property_ `public string PeerHost { get; }` — If the command was sent through a proxy, broker, replica, or edge server, the hostname of the proxy, broker, replica, or edge server. (If the command was sent directly, %peerhost% matches %clienthost%)
- L117 _public property_ `public string PeerIp { get; }` — If the command was sent through a proxy, broker, replica, or edge server, the IP address of the proxy, broker, replica, or edge server. (If the command was sent directly, %peerip% matches %clientip%)
- L122 _public property_ `public string ServerHost { get; }` — Hostname of the Helix Core Server.
- L127 _public property_ `public string ServerId { get; }` — The value of the Helix Core Server’s server.id. See p4 serverid in the Helix Core Command-Line (P4) Reference.
- L132 _public property_ `public string ServerIp { get; }` — The IP address of the server.
- L137 _public property_ `public string ServerName { get; }` — The value of the Helix Core Server’s P4NAME.
- L142 _public property_ `public string ServerPort { get; }` — The transport, IP address, and port of the Helix Core Server, in the format prefix:ip_address:port.
- L150 _public property_ `public string? SubmitServerId { get; }` — In a distributed installation, for any change trigger: If the submit was run on the commit server, %submitserverid% equals %serverid%. If the submit was run on the edge server, %submitserverid% does not equal %serverid%. In this case, %submitserverid% holds the edge server’s server id. If this is not a distributed installation, %submitserverid% is always empty.
- L155 _public property_ `public string User { get; }` — Helix Server username of the triggering user.
- L160 _public property_ `public string? FormName { get; }` — Name of form (for instance, a branch name or a changelist number).
- L165 _public property_ `public string? FormType { get; }` — Type of form (for instance, branch, change, and so on).
- L171 _public property_ `public string? ChangeNumberString { get; }` — attrs: `[JsonPropertyName("ChangeNumber")]` — The number of the changelist being submitted. Not set for form-save.
- L176 _public property_ `public string? ChangeRoot { get; }` — The root path of files submitted.
- L183 _public property_ `public int ChangeNumber { get; }` — attrs: `[JsonIgnore]` — Change number Normalized as form-save stores the change number in 'formname'
- L207-238 _public ctor_ `public PerforceTriggerRequest(string triggerType, string client, string clientHost, string clientIp, string clientProg, string clientVersion, string peerHost, string peerIp, string serverHost, string serverId, string serverIp, string serverName, string serverPort, string submitServerId, string user, string formName, string formType, string changeNumberString, string changeRoot)` — Constructor
- L241-244 _public method_ `public override string ToString()` — (inheritdoc)

#### class `HordeServer.VersionControl.Perforce.PublicPerforceController`  
`public class PublicPerforceController : ControllerBase`  
_public; L253-304_
- attrs: `[ApiController] [Tags("Perforce")] [Route("[controller]")]`
- inherits: `ControllerBase`
- desc: Controller for Perforce triggers and callbacks
- L255 _private field_ `private readonly IPerforceService _perforceService`
- L256 _private field_ `private readonly Tracer _tracer`
- L257 _private field_ `private readonly ILogger<PerforceController> _logger`
- L262-267 _public ctor_ `public PublicPerforceController(IPerforceService perforceService, Tracer tracer, ILogger<PerforceController> logger)` — Constructor
- L275-303 _public method_ `public async Task<ActionResult> TriggerCallbackAsync(string cluster, [FromBody] PerforceTriggerRequest trigger)` — attrs: `[HttpPost] [Route("/api/v1/perforce/{cluster}/trigger")]` — Endpoint which trigger scripts in Perforce will call

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/VersionControl/Perforce/PerforceLoadBalancer.cs` (HordeServer.Build)


#### enum `HordeServer.VersionControl.Perforce.PerforceServerStatus`  
`public enum PerforceServerStatus`  
_public; L31-52_
- desc: Health of a particular server
- L36 _public* enumerator_ `Unknown` — Server could not be reached
- L41 _public* enumerator_ `Unhealthy` — Bad. Do not use.
- L46 _public* enumerator_ `Degraded` — Degraded, but functioning
- L51 _public* enumerator_ `Healthy` — Good

#### interface `HordeServer.VersionControl.Perforce.IPerforceServer`  
`public interface IPerforceServer`  
_public; L57-98_
- desc: Perforce server infomation
- L62 _public property_ `public string ServerAndPort { get; }` — The server and port
- L67 _public property_ `public string BaseServerAndPort { get; }` — The server and port before doing DNS resolution
- L72 _public property_ `public string Cluster { get; }` — The cluster this server belongs to
- L77 _public property_ `public bool SupportsPartitionedWorkspaces { get; }` — Whether this server supports partitioned workspaces
- L82 _public property_ `public PerforceServerStatus Status { get; }` — Current status
- L87 _public property_ `public int NumLeases { get; }` — Number of leases using this server
- L92 _public property_ `public string? Detail { get; }` — Error message related to this server
- L97 _public property_ `public DateTime? LastUpdateTime { get; }` — Last update time for this server

#### class `HordeServer.VersionControl.Perforce.PerforceLoadBalancer`  
`public sealed class PerforceLoadBalancer : IHostedService, IAsyncDisposable`  
_public; L103-772_
- inherits: `IHostedService, IAsyncDisposable`
- desc: Load balancer for Perforce edge servers
- L153 _private* field_ `readonly IRedisService _redisService`
- L154 _private* field_ `readonly ILeaseCollection _leaseCollection`
- L155 _private* field_ `readonly SingletonDocument<PerforceServerList> _serverListSingleton`
- L156 _private* field_ `readonly Random _random = new Random()`
- L157 _private* field_ `readonly HttpClient _httpClient`
- L158 _private* field_ `readonly IOptionsMonitor<BuildConfig> _buildConfig`
- L159 _private* field_ `readonly IHealthMonitor _health`
- L160 _private* field_ `readonly Tracer _tracer`
- L161 _private* field_ `readonly ILogger _logger`
- L162 _private* field_ `readonly ITicker _ticker`
- L167-188 _public ctor_ `public PerforceLoadBalancer(IMongoService mongoService, IRedisService redisService, ILeaseCollection leaseCollection, IClock clock, HttpClient httpClient, IOptionsMonitor<BuildConfig> buildConfig, IHealthMonitor<PerforceLoadBalancer> health, Tracer tracer, ILogger<PerforceLoadBalancer> logger)` — Constructor
- L191 _public method_ `public Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L194 _public method_ `public Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L197-200 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L206-221 _private* method_ `async Task<PerforceServerList> GetServerListAsync(CancellationToken cancellationToken)` — Get the current server list
- L227-231 _public method_ `public async Task<List<IPerforceServer>> GetServersAsync(CancellationToken cancellationToken)` — Get the perforce servers
- L237-248 _public method_ `public async Task<IPerforceServer?> GetServerAsync(string cluster, CancellationToken cancellationToken)` — Allocates a server for use by a lease
- L256-260 _public method_ `public Task<IPerforceServer?> SelectServerAsync(PerforceCluster cluster, CancellationToken cancellationToken)` — Select a Perforce server to use by the Horde server
- L269-272 _public method_ `public Task<IPerforceServer?> SelectServerAsync(PerforceCluster cluster, IAgent agent, CancellationToken cancellationToken)` — Select a Perforce server to use
- L277-292 _private* method_ `static bool EvaluateCondition(Condition? condition, IReadOnlyList<string> properties)` — Evaluate a server condition using standard Horde syntax
- L297-306 _private* method_ `static IEnumerable<string> GetPropertyValues(IReadOnlyList<string> properties, string name)` — Get property values from a list starting with the given key
- L316-417 _public method_ `public async Task<IPerforceServer?> SelectServerAsync(string key, PerforceCluster cluster, IReadOnlyList<string> properties, CancellationToken cancellationToken)` — Select a Perforce server to use
- L419-431 _private* method_ `static int GetWeight(PerforceServerEntry candidate, PerforceServerEntry? prevCandidate, int totalLeases)`
- L433-436 _internal method_ `internal ValueTask TickInternalTestOnlyAsync(CancellationToken cancellationToken)`
- L438-479 _private* method_ `async ValueTask TickInternalAsync(CancellationToken cancellationToken)`
- L481-509 _private* method_ `static (HealthStatus health, string? message) GetPerforceHealth(List<PerforceServerEntry> servers)`
- L511-528 _private* method_ `static void MergeServerList(PerforceServerList serverList, List<PerforceServerEntry> newEntries)`
- L530-577 _private* method_ `async Task UpdateLeaseCountsAsync(IEnumerable<PerforceServerEntry> newServerEntries, CancellationToken cancellationToken)`
- L579-590 _private* method_ `static void IncrementLeaseCount(string cluster, string serverAndPort, Dictionary<string, Dictionary<string, PerforceServerEntry>> newServers)`
- L592-623 _private* method_ `async Task UpdateServerAsync(PerforceCluster cluster, PerforceServer server, List<PerforceServerEntry> newServers, CancellationToken cancellationToken)`
- L631-645 _private* method_ `async Task ResolveDnsHostnameAsync(string hostName, List<string> ipAddresses, CancellationToken cancellationToken)` — Find all the IP addresses for a hostname
- L647-660 _private* method_ `async Task UpdateHealthGuardedAsync(PerforceServerEntry entry, CancellationToken cancellationToken)`
- L665-679 _private* method_ `async Task UpdateHealthAsync(PerforceServerEntry entry, CancellationToken cancellationToken)` — Checks and updates the health of a Perforce server
- L681-686 _internal method_ `internal async Task UpdateHealthTestOnlyAsync(string cluster, string serverAndPort, string? healthCheckUrl, CancellationToken cancellationToken)`
- L688-700 _private* method_ `static void UpdateHealth(PerforceServerList serverList, string serverAndPort, PerforceServerStatus status, string detail, DateTime? updateTime)`
- L710-747 _private* method_ `async Task<ServerHealth> GetServerHealthViaHttpAsync(string healthCheckUrl, CancellationToken cancellationToken)` — Queries the server's associated health check URL for status
- L756-771 _internal method_ `internal static async Task<ServerHealth> GetServerHealthViaP4InfoAsync(string serverAndPort, ILogger logger, CancellationToken cancellationToken)` — Checks the health of given Perforce server by invoking the equivalent of "p4 info"

#### class `HordeServer.VersionControl.Perforce.PerforceLoadBalancer.PerforceServerEntry`  
`class PerforceServerEntry : IPerforceServer`  
_private*; L108-142_
- inherits: `IPerforceServer`
- desc: Information about a resolved Perforce server
- L114 _public property_ `public string ServerAndPort { get; set; }` — Resolved host:port for this Perforce server. Mapping this separately from BaseServerAndPort is useful when a DNS name has multiple IP lookups for load balancing
- L117 _public property_ `public string BaseServerAndPort { get; set; }` — (inheritdoc)
- L118 _public property_ `public string? HealthCheckUrl { get; set; }`
- L119 _public property_ `public string Cluster { get; set; }`
- L120 _public property_ `public bool SupportsPartitionedWorkspaces { get; set; }`
- L121 _public property_ `public PerforceServerStatus Status { get; set; }`
- L122 _public property_ `public string? Detail { get; set; }`
- L123 _public property_ `public int NumLeases { get; set; }`
- L124 _public property_ `public DateTime? LastUpdateTime { get; set; }`
- L127-129 _private ctor_ `private PerforceServerEntry()` — attrs: `[BsonConstructor]`
- L131-141 _public ctor_ `public PerforceServerEntry(string serverAndPort, string baseServerAndPort, string? healthCheckUrl, string cluster, bool supportsPartitionedWorkspaces, PerforceServerStatus status, string? detail, DateTime? lastUpdateTime)`

#### class `HordeServer.VersionControl.Perforce.PerforceLoadBalancer.PerforceServerList`  
`class PerforceServerList : SingletonBase`  
_private*; L148-151_
- attrs: `[SingletonDocument("perforce-server-list", "6046aec374a9283100967ee7")]`
- inherits: `SingletonBase`
- L150 _public property_ `public List<PerforceServerEntry> Servers { get; set; }`

#### record `HordeServer.VersionControl.Perforce.PerforceLoadBalancer.ServerHealth`  
`internal record ServerHealth(PerforceServerStatus Status, string Detail)`  
_internal; L702-702_

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/VersionControl/Perforce/PerforceService.cs` (HordeServer.Build)


#### class `HordeServer.VersionControl.Perforce.PerforceServiceException`  
`public class PerforceServiceException(string? message) : Exception(message)`  
_public; L28-28_
- desc: Exception raised by errors in PerforceService

#### class `HordeServer.VersionControl.Perforce.PerforceService`  
`class PerforceService : IPerforceService, IAsyncDisposable`  
_internal*; L33-1399_
- inherits: `IPerforceService, IAsyncDisposable`
- desc: P4API implementation of the Perforce service
- L39 _protected const_ `protected const int MaxFiles = 1000` — Max number of files in a changelist to query for, or store This is to prevent performance issues with large merge commits with lots of files.
- L255 _public property_ `public string Name { get; }`
- L257 _private* field_ `readonly PerforceLoadBalancer _loadBalancer`
- L258 _private* field_ `readonly IOptionsMonitor<BuildConfig> _buildConfig`
- L259 _private* field_ `readonly Tracer _tracer`
- L260 _private* field_ `readonly ILogger _logger`
- L263 _private* field_ `readonly string? _perforceServerOverride`
- L264 _private* field_ `readonly string? _perforceUserOverride`
- L266 _private* field_ `readonly BuildServerConfig _settings`
- L267 _private* field_ `readonly Dictionary<string, Dictionary<string, Credentials>> _userCredentialsByCluster = ...`
- L267 _private* field_ `readonly Dictionary< string`
- L267 _private* field_ `readonly Dictionary< _userCredentialsByCluster = new Dictionary<string, Dictionary<string, Credentials>>(StringComparer.OrdinalIgnoreCase)`
- L268 _private* field_ `readonly IUserCollection _userCollection`
- L269 _private* field_ `readonly MemoryCache _userCache = new MemoryCache(new MemoryCacheOptions { SizeLimit = 2000 })`
- L270 _private* field_ `readonly MemoryCache _streamCache = new MemoryCache(new MemoryCacheOptions())`
- L272 _private* field_ `readonly List<PooledConnection> _pooledConnections = new List<PooledConnection>()`
- L277-292 _public ctor_ `public PerforceService(PerforceLoadBalancer loadBalancer, IUserCollection userCollection, IOptions<BuildServerConfig> settings, IOptionsMonitor<BuildConfig> buildConfig, Tracer tracer, ILogger<PerforceService> logger)` — Constructor
- L294-305 _public method_ `public virtual ValueTask DisposeAsync()`
- L307-327 _private* method_ `async Task<PooledConnectionHandle> CreatePooledConnectionAsync(string serverAndPort, Credentials credentials, ClientRecord? clientRecord, CancellationToken cancellationToken)`
- L329-345 _private* method_ `PooledConnectionHandle? GetPooledConnection(Predicate<PooledConnection> predicate)`
- L347-351 _private* method_ `PooledConnectionHandle? GetPooledConnectionForUser(PerforceCluster cluster, string? userName)`
- L353-357 _private* method_ `PooledConnectionHandle? GetPooledConnectionForClient(PerforceCluster cluster, string? userName, string clientName)`
- L359-363 _private* method_ `PooledConnectionHandle? GetPooledConnectionForStream(PerforceCluster cluster, string? userName, string streamName)`
- L365-376 _private* method_ `bool IsValidServer(PooledConnection connection, PerforceCluster cluster)`
- L378-390 _private* method_ `void ReleaseExpiredConnections()`
- L392-404 _private* method_ `void ReleasePooledConnection(PooledConnection connection)`
- L406-433 _private* method_ `Credentials GetServiceUserCredentials(PerforceCluster cluster)`
- L435-456 _private* method_ `async Task<Credentials> GetCredentialsAsync(PerforceCluster cluster, string? userName, CancellationToken cancellationToken)`
- L458-462 _public method_ `public async Task<IPooledPerforceConnection> ConnectAsync(string clusterName, string? userName = null, CancellationToken cancellationToken = default)`
- L464-488 _private* method_ `async Task<PooledConnectionHandle> ConnectAsync(PerforceCluster cluster, string? userName, CancellationToken cancellationToken)`
- L490-537 _private* method_ `async Task<PooledConnectionHandle> ConnectAsChangeOwnerAsync(PerforceCluster cluster, int change, CancellationToken cancellationToken)`
- L539-565 _private* method_ `async Task<PooledConnectionHandle> ConnectWithStreamClientAsync(string clusterName, string? userName, string streamName, CancellationToken cancellationToken)`
- L567-570 _private* method_ `Task<PooledConnectionHandle> ConnectWithStreamClientAsync(StreamConfig streamConfig, string? userName, CancellationToken cancellationToken)`
- L572-622 _private* method_ `async Task<Credentials> GetTicketAsync(PerforceCluster cluster, string userName, CancellationToken cancellationToken)`
- L624-628 _public method_ `public async ValueTask<IUser> FindOrAddUserAsync(string clusterName, string userName, CancellationToken cancellationToken = default)`
- L630-666 _public method_ `public async ValueTask<IUser> FindOrAddUserAsync(PerforceCluster cluster, string userName, CancellationToken cancellationToken = default)`
- L668-679 _private* method_ `async Task<IPerforceServer> GetServerAsync(PerforceCluster cluster, CancellationToken cancellationToken)`
- L681-691 _private* method_ `static string GetClientName(string? serviceUserName, string serverId, string stream, bool readOnly)`
- L693-700 _private* method_ `static string SanitizeClientName(string clientName)`
- L702-728 _private* method_ `async ValueTask<Commit> CreateCommitInternalAsync(StreamConfig streamConfig, int number, string author, string description, string? basePath, DateTime dateUtc, CancellationToken cancellationToken)`
- L730-752 _protected method_ `protected async ValueTask<ICommit> CreateCommitAsync(IPooledPerforceConnection perforce, StreamConfig streamConfig, DescribeRecord describeRecord, bool hasAllFiles, InfoRecord serverInfo, CancellationToken cancellationToken, List<string>? preComputedFiles = null)`
- L754-761 _private* method_ `async ValueTask<Commit> CreateCommitAsync(StreamConfig streamConfig, ChangesRecord changesRecord, InfoRecord serverInfo, CancellationToken cancellationToken)`
- L768-780 _private* method_ `static int? ParseRobomergeSource(string description)` — Attempts to parse the Robomerge source from this commit information
- L787-799 _private* method_ `static string? ParseRobomergeOwner(string description)` — Attempts to parse the Robomerge owner from this commit information
- L802-823 _public method_ `public async Task<ICommit> GetChangeDetailsAsync(StreamConfig streamConfig, int changeNumber, CancellationToken cancellationToken)` — (inheritdoc)
- L826-890 _public method_ `public async Task<(CheckShelfResult, ShelfInfo?)> CheckShelfAsync(StreamConfig streamConfig, int changeNumber, CancellationToken cancellationToken)` — (inheritdoc)
- L893-896 _public method_ `public Task<int> DuplicateShelvedChangeAsync(string clusterName, int shelvedChange, CancellationToken cancellationToken)` — (inheritdoc)
- L899-912 _public method_ `public async Task DeleteShelvedChangeAsync(string clusterName, int shelvedChange, CancellationToken cancellationToken)` — (inheritdoc)
- L915-940 _public method_ `public async Task UpdateChangelistDescriptionAsync(string clusterName, int change, Func<string, string> updateFunc, CancellationToken cancellationToken)` — (inheritdoc)
- L943 _public method_ `public virtual Task RefreshCachedCommitAsync(string clusterName, int change)` — (inheritdoc)
- L945-955 _private* method_ `static async Task ResetClientAsync(IPerforceConnection perforce, CancellationToken cancellationToken)`
- L958-1098 _public method_ `public async Task<int> CreateNewChangeAsync(string clusterName, string streamName, string filePath, string description, CancellationToken cancellationToken)` — (inheritdoc)
- L1101-1158 _public method_ `public async Task<(int? Change, string Message)> SubmitShelvedChangeAsync(StreamConfig streamConfig, int change, int originalChange, CancellationToken cancellationToken)` — (inheritdoc)
- L1167-1183 _public method_ `public static string GetFilter(string basePath, int? minChange, int? maxChange)` — Gets the wildcard filter for a particular range of changes
- L1192-1209 _public method_ `public static bool TryGetStreamRelativePath(string depotFile, string streamName, [NotNullWhen(true)] out string? relativePath)` — Gets a stream-relative path from a depot path
- L1390-1393 _public method_ `public virtual ICommitCollection GetCommits(StreamConfig streamConfig)` — (inheritdoc)
- L1398 _protected property_ `protected IUserCollection UserCollection => ...` — The user collection.

#### class `HordeServer.VersionControl.Perforce.PerforceService.PooledConnection`  
`protected sealed class PooledConnection : IDisposable`  
_protected; L41-69_
- inherits: `IDisposable`
- L43 _public property_ `public IPerforceConnection Perforce { get; }`
- L44 _public property_ `public IPerforceSettings Settings => ...`
- L45 _public property_ `public Credentials Credentials { get; }`
- L46 _public property_ `public ClientRecord? Client { get; }`
- L47 _public property_ `public DateTime ExpiresAt { get; }`
- L49 _private* field_ `InfoRecord? _info`
- L51-57 _public ctor_ `public PooledConnection(IPerforceConnection perforce, Credentials credentials, ClientRecord? client, DateTime expiresAt)`
- L59-62 _public method_ `public void Dispose()`
- L64-68 _public method_ `public async ValueTask<InfoRecord> GetInfoAsync(CancellationToken cancellationToken)`

#### class `HordeServer.VersionControl.Perforce.PerforceService.PooledConnectionHandle`  
`protected class PooledConnectionHandle : IPooledPerforceConnection`  
_protected; L71-137_
- inherits: `IPooledPerforceConnection`
- L73 _private* field_ `readonly PerforceService _owner`
- L74 _private* field_ `PooledConnection _inner`
- L76 _public property_ `public ClientRecord? Client => ...`
- L77 _public property_ `public Credentials Credentials => ...`
- L79-83 _public ctor_ `public PooledConnectionHandle(PerforceService owner, PooledConnection inner)`
- L86-93 _public method_ `public void Dispose()` — (inheritdoc)
- L96 _public property_ `public IPerforceSettings Settings => ...` — (inheritdoc)
- L99 _public property_ `public ILogger Logger => ...` — (inheritdoc)
- L102 _public property_ `public Tracer Tracer => ...` — (inheritdoc)
- L105-108 _public method_ `public IPerforceOutput Command(string command, IReadOnlyList<string> arguments, IReadOnlyList<string>? fileArguments, byte[]? inputData, string? promptResponse, bool interceptIo)` — (inheritdoc)
- L111-114 _public method_ `public PerforceRecord CreateRecord(List<KeyValuePair<string, object>> fields)` — (inheritdoc)
- L117 _public method_ `public ValueTask<InfoRecord> GetInfoAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L120-136 _public method_ `public async ValueTask<PerforceViewMap> GetCachedStreamViewAsync(StreamConfig streamConfig, CancellationToken cancellationToken)` — (inheritdoc)

#### class `HordeServer.VersionControl.Perforce.PerforceService.Credentials`  
`protected class Credentials`  
_protected; L139-153_
- L141 _public property_ `public string UserName { get; }`
- L142 _public property_ `public string? Password { get; }`
- L143 _public property_ `public string? Ticket { get; }`
- L144 _public property_ `public DateTime? ExpiresAt { get; }`
- L146-152 _public ctor_ `public Credentials(string userName, string? password, string? ticket, DateTime? expiresAt)`

#### class `HordeServer.VersionControl.Perforce.PerforceService.Commit`  
`class Commit : ICommit`  
_private*; L155-253_
- inherits: `ICommit`
- L157 _private* field_ `readonly PerforceService _owner`
- L158 _private* field_ `readonly StreamConfig _streamConfig`
- L160 _public property_ `public StreamId StreamId => ...`
- L162 _public property_ `public int Number { get; }`
- L163 _private* property_ `CommitIdWithOrder ICommit.Id => ...`
- L165 _public property_ `public int OriginalChange { get; }`
- L166 _private* property_ `CommitIdWithOrder ICommit.OriginalCommitId => ...`
- L168 _public property_ `public UserId AuthorId { get; }`
- L169 _public property_ `public UserId OwnerId { get; }`
- L170 _public property_ `public string Description { get; }`
- L171 _public property_ `public string BasePath { get; }`
- L172 _public property_ `public DateTime DateUtc { get; }`
- L174 _private* field_ `IReadOnlyList<string> _files = Array.Empty<string>()`
- L175 _private* field_ `bool _hasAllFiles`
- L177-189 _public ctor_ `public Commit(PerforceService owner, StreamConfig streamConfig, int number, int originalChange, UserId authorId, UserId ownerId, string description, string basePath, DateTime dateUtc)`
- L191-195 _public method_ `public void SetFiles(IReadOnlyList<string> files, bool hasAllFiles)`
- L197-208 _public method_ `public async ValueTask<IReadOnlyList<CommitTag>> GetTagsAsync(CancellationToken cancellationToken)`
- L210-231 _public method_ `public async ValueTask<bool> MatchesFilterAsync(FileFilter filter, CancellationToken cancellationToken)`
- L233-252 _public method_ `public async ValueTask<IReadOnlyList<string>> GetFilesAsync(int? minFiles, int? maxFiles, CancellationToken cancellationToken)`

#### class `HordeServer.VersionControl.Perforce.PerforceService.CommitSource`  
`protected class CommitSource : ICommitCollection`  
_protected; L1214-1387_
- inherits: `ICommitCollection`
- desc: Implementation of ICommitCollection to return commits from a particular stream
- L1216 _protected property_ `protected PerforceService PerforceService { get; }`
- L1217 _protected property_ `protected StreamConfig StreamConfig { get; }`
- L1218 _protected property_ `protected ILogger Logger { get; }`
- L1220-1225 _public ctor_ `public CommitSource(PerforceService perforceService, StreamConfig streamConfig, ILogger logger)`
- L1228-1246 _public method_ `public async Task<CommitIdWithOrder> CreateNewAsync(string path, string description, CancellationToken cancellationToken = default)` — (inheritdoc)
- L1248-1251 _public method_ `public IAsyncEnumerable<ICommit> FindAsync(CommitId? minChange = null, bool includeMinChange = true, CommitId? maxChange = null, bool includeMaxChange = true, int? maxResults = null, IReadOnlyList<CommitTag>? tags = null, CommitSortOrder sortOrder = CommitSortOrder.Descending, CancellationToken cancellationToken = default)`
- L1253-1339 _public method_ `public virtual async IAsyncEnumerable<ICommit> FindAsync(int? minChange, bool includeMinChange, int? maxChange, bool includeMaxChange, int? maxResults, IReadOnlyList<CommitTag>? tags, CommitSortOrder sortOrder, [EnumeratorCancellation] CancellationToken cancellationToken = default)`
- L1342 _public method_ `public Task<ICommit> GetAsync(CommitId changeNumber, CancellationToken cancellationToken = default)` — (inheritdoc)
- L1346 _public method_ `public virtual Task<ICommit> GetAsync(int changeNumber, CancellationToken cancellationToken = default)` — (inheritdoc)
- L1350 _public method_ `public ValueTask<CommitIdWithOrder> GetOrderedAsync(CommitId commit, CancellationToken cancellationToken = default)` — (inheritdoc)
- L1354 _public method_ `public IAsyncEnumerable<ICommit> SubscribeAsync(CommitId minCommit, IReadOnlyList<CommitTag>? tags = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L1358-1386 _public method_ `public virtual async IAsyncEnumerable<ICommit> SubscribeAsync(int minChange, IReadOnlyList<CommitTag>? tags = null, [EnumeratorCancellation] CancellationToken cancellationToken = default)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/VersionControl/Perforce/PerforceServiceCache.cs` (HordeServer.Build)


#### class `HordeServer.VersionControl.Perforce.PerforceServiceCache`  
`class PerforceServiceCache : PerforceService, IHostedService`  
_internal*; L31-928_
- inherits: `PerforceService, IHostedService`
- desc: Service which mirrors changes from Perforce
- L245 _private* field_ `readonly IMongoService _mongoService`
- L246 _private* field_ `readonly IRedisService _redisService`
- L247 _private* field_ `readonly IDowntimeService _downtimeService`
- L248 _private* field_ `readonly IMongoCollection<CachedCommitDoc> _commits`
- L249 _private* field_ `readonly IOptionsMonitor<BuildConfig> _buildConfig`
- L250 _private* field_ `readonly ITelemetryWriter _telemetryWriter`
- L251 _private* field_ `readonly Tracer _tracer`
- L252 _private* field_ `readonly ILogger _logger`
- L254 _private* field_ `static readonly RedisChannel<StreamId> s_commitUpdateChannel = new RedisChannel<StreamId>(RedisChannel.Literal("commit-update"))`
- L256 _private* field_ `readonly ITicker _updateCommitsTicker`
- L261-279 _public ctor_ `public PerforceServiceCache(PerforceLoadBalancer loadBalancer, IMongoService mongoService, IRedisService redisService, IDowntimeService downtimeService, IUserCollection userCollection, IClock clock, IOptions<BuildServerConfig> settings, IOptionsMonitor<BuildConfig> buildConfig, ITelemetryWriter telemetryWriter, Tracer tracer, ILogger<PerforceService> logger) : base(loadBalancer, userCollection, settings, buildConfig, tracer, logger)` — Constructor
- L282-287 _public method_ `public override async ValueTask DisposeAsync()` — (inheritdoc)
- L290-293 _public method_ `public async Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L296-299 _public method_ `public async Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L306-360 _private* method_ `async ValueTask UpdateCommitsAsync(CancellationToken cancellationToken)` — Polls Perforce for submitted changes
- L362-381 _private* method_ `async Task<Dictionary<string, List<StreamInfo>>> CreateStreamInfoAsync(CancellationToken cancellationToken)`
- L383-397 _private* method_ `async Task<List<StreamInfo>> CreateStreamInfoForClusterAsync(string clusterName, IEnumerable<StreamConfig> streams, CancellationToken cancellationToken)`
- L399-404 _private* method_ `ClusterTicker StartTicker(string clusterName, List<StreamInfo> streamInfos)`
- L406-416 _private* method_ `async ValueTask StopTickerAsync(ClusterTicker ticker)`
- L418-444 _private* method_ `async Task UpdateClusterAsync(ClusterTicker ticker, CancellationToken cancellationToken)`
- L446-465 _internal method_ `internal async Task UpdateClusterInternalAsync(string clusterName, List<StreamInfo> streamInfos, SpanContext? parentContext, CancellationToken cancellationToken)`
- L467-625 _private* method_ `async Task<ClusterState?> UpdateClusterCommitsAsync(string clusterName, List<StreamInfo> streamInfos, ClusterState state, SpanContext parentContext, CancellationToken cancellationToken)`
- L627-639 _private* method_ `async Task AddCachedCommitAsync(CachedCommitDoc commitDoc, CancellationToken cancellationToken)`
- L642 _private* method_ `static RedisSetKey<int> GetRefreshSetKey(string clusterName)`
- L646-650 _public method_ `public override async Task RefreshCachedCommitAsync(string clusterName, int change)` — (inheritdoc)
- L922-925 _public method_ `public override ICommitCollection GetCommits(StreamConfig streamConfig)` — (inheritdoc)

#### class `HordeServer.VersionControl.Perforce.PerforceServiceCache.CacheState`  
`class CacheState : SingletonBase`  
_private*; L34-38_
- attrs: `[SingletonDocument("commit-cache")]`
- inherits: `SingletonBase`
- L37 _public property_ `public Dictionary<string, ClusterState> Clusters { get; set; }` — attrs: `[BsonDictionaryOptions(DictionaryRepresentation.ArrayOfDocuments)]`

#### class `HordeServer.VersionControl.Perforce.PerforceServiceCache.ClusterState`  
`class ClusterState`  
_private*; L40-49_
- L42 _public property_ `public int MaxChange { get; set; }`
- L45 _public property_ `public Dictionary<StreamId, IoHash> Streams { get; set; }` — attrs: `[BsonDictionaryOptions(DictionaryRepresentation.ArrayOfDocuments)]`
- L48 _public property_ `public Dictionary<StreamId, int> MinChanges { get; set; }` — attrs: `[BsonDictionaryOptions(DictionaryRepresentation.ArrayOfDocuments)]`

#### class `HordeServer.VersionControl.Perforce.PerforceServiceCache.CommitTagInfo`  
`internal class CommitTagInfo`  
_internal; L51-61_
- L53 _public property_ `public CommitTag Name { get; }`
- L54 _public property_ `public FileFilter Filter { get; }`
- L56-60 _public ctor_ `public CommitTagInfo(CommitTag name, FileFilter filter)`

#### class `HordeServer.VersionControl.Perforce.PerforceServiceCache.StreamInfo`  
`internal class StreamInfo`  
_internal; L63-105_
- L65 _public property_ `public StreamConfig StreamConfig { get; set; }`
- L66 _public property_ `public PerforceViewMap View { get; }`
- L67 _public property_ `public PerforceChangeView ChangeView { get; }`
- L68 _public property_ `public IoHash Hash { get; }`
- L70 _public property_ `public IReadOnlyList<CommitTagInfo> CommitTags { get; }`
- L72-104 _public ctor_ `public StreamInfo(StreamConfig streamConfig, PerforceViewMap view, PerforceChangeView changeView)`

#### class `HordeServer.VersionControl.Perforce.PerforceServiceCache.ClusterTicker`  
`sealed class ClusterTicker : IAsyncDisposable`  
_private*; L107-134_
- inherits: `IAsyncDisposable`
- L109 _public property_ `public string ClusterName { get; }`
- L110 _public property_ `public BackgroundTask? Task { get; set; }`
- L113 _private field_ `private volatile List<StreamInfo> _streams`
- L114-118 _public property_ `public List<StreamInfo> Streams { get; set; }`
- L120-124 _public ctor_ `public ClusterTicker(string name, List<StreamInfo> streamInfos)`
- L126-133 _public method_ `public async ValueTask DisposeAsync()`

#### class `HordeServer.VersionControl.Perforce.PerforceServiceCache.CachedCommitDoc`  
`class CachedCommitDoc : ICommit`  
_private*; L136-243_
- inherits: `ICommit`
- L139 _private* field_ `PerforceServiceCache _owner = null!` — attrs: `[BsonIgnore]`
- L142 _private* field_ `StreamConfig _streamConfig = null!` — attrs: `[BsonIgnore]`
- L145 _public property_ `public ObjectId Id { get; set; }` — attrs: `[BsonIgnoreIfDefault]`
- L147 _public property_ `public StreamId StreamId { get; set; }`
- L149 _public property_ `public int Number { get; set; }`
- L150 _private* property_ `CommitIdWithOrder ICommit.Id => ...`
- L152 _public property_ `public int OriginalChange { get; set; }`
- L153 _private* property_ `CommitIdWithOrder ICommit.OriginalCommitId => ...`
- L155 _public property_ `public UserId AuthorId { get; set; }`
- L156 _public property_ `public UserId OwnerId { get; set; }`
- L157 _public property_ `public string Description { get; set; }`
- L158 _public property_ `public string BasePath { get; set; }`
- L159 _public property_ `public DateTime DateUtc { get; set; }`
- L161 _public property_ `public List<CommitTag> CommitTags { get; set; }`
- L162 _public property_ `public List<string> Files { get; set; }`
- L165 _public property_ `public bool HasAllFiles { get; set; }` — attrs: `[BsonElement("haf")]`
- L168-175 _private* ctor_ `CachedCommitDoc()` — attrs: `[BsonConstructor]`
- L177-198 _public ctor_ `public CachedCommitDoc(ICommit commit, List<CommitTag> commitTags, List<string> files, bool hasAllFiles)`
- L200-206 _public method_ `public static async Task<CachedCommitDoc> FromCommitAsync(ICommit commit, CancellationToken cancellationToken)`
- L208-212 _public method_ `public void PostLoad(PerforceServiceCache owner, StreamConfig streamConfig)`
- L214-217 _public method_ `public ValueTask<IReadOnlyList<CommitTag>> GetTagsAsync(CancellationToken cancellationToken)`
- L219-228 _public method_ `public async ValueTask<bool> MatchesFilterAsync(FileFilter filter, CancellationToken cancellationToken)`
- L230-242 _public method_ `public async ValueTask<IReadOnlyList<string>> GetFilesAsync(int? minFiles, int? maxFiles, CancellationToken cancellationToken)`

#### class `HordeServer.VersionControl.Perforce.PerforceServiceCache.CachedCommitSource`  
`class CachedCommitSource : CommitSource`  
_private*; L659-919_
- inherits: `CommitSource`
- desc: Returns commits within the cached range
- L661 _private* field_ `readonly PerforceServiceCache _owner`
- L663-667 _public ctor_ `public CachedCommitSource(PerforceServiceCache owner, StreamConfig stream, ILogger logger) : base(owner, stream, logger)`
- L669-813 _public method_ `public override async IAsyncEnumerable<ICommit> FindAsync(int? minChange = null, bool includeMinChange = true, int? maxChange = null, bool includeMaxChange = true, int? maxResults = null, IReadOnlyList<CommitTag>? tags = null, CommitSortOrder sortOrder = CommitSortOrder.Descending, [EnumeratorCancellation] CancellationToken cancellationToken = default)`
- L815-831 _private* method_ `static bool TryUpdateRange(CacheState state, StreamConfig streamConfig, int newMinChange, int? maxChange)`
- L833-842 _public method_ `public override async Task<ICommit> GetAsync(int changeNumber, CancellationToken cancellationToken = default)`
- L845-888 _public method_ `public override async IAsyncEnumerable<ICommit> SubscribeAsync(int minChange, IReadOnlyList<CommitTag>? tags = null, [EnumeratorCancellation] CancellationToken cancellationToken = default)` — (inheritdoc)
- L890-918 _private* method_ `async IAsyncEnumerable<ICommit> FindCachedCommitsInAscendingOrderAsync(int minChange, IReadOnlyList<CommitTag>? tags, [EnumeratorCancellation] CancellationToken cancellationToken)`

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/VersionControl/Perforce/PerforceWorkspace.cs` (HordeServer.Build)


#### class `HordeServer.VersionControl.Perforce.PerforceWorkspace`  
`public static class PerforceWorkspace`  
_public; L16-332_
- desc: Helper methods for dealing with Perforce workspaces
- L25-38 _public method_ `public static AgentWorkspaceInfo? GetAutoSdkWorkspace(this IAgent agent, PerforceCluster cluster, IEnumerable<IPool> pools)` — Get the AutoSDK workspace required for an agent
- L47-57 _public method_ `public static AgentWorkspaceInfo? GetAutoSdkWorkspace(this IAgent agent, PerforceCluster cluster, AutoSdkConfig autoSdkConfig)` — Get the AutoSDK workspace required for an agent
- L69-142 _public method_ `public static async Task<bool> TryAddWorkspaceMessageAsync(this IAgent agent, AgentWorkspaceInfo workspace, PerforceCluster cluster, PerforceLoadBalancer loadBalancer, IList<RpcAgentWorkspace> workspaceMessages, CancellationToken cancellationToken)` — Converts this workspace to an RPC message
- L152-228 _public method_ `public static bool TryGetAgentWorkspace(this StreamConfig streamConfig, IAgentType agentType, [NotNullWhen(true)] out AgentWorkspaceInfo? workspace, out AutoSdkConfig? autoSdkConfig)` — Tries to get an agent workspace definition from the given type name
- L239-267 _public method_ `public static async Task<HashSet<AgentWorkspaceInfo>> GetWorkspacesAsync(this PoolService poolService, IAgent agent, DateTime validAtTime, BuildConfig buildConfig, CancellationToken cancellationToken)` — Get a list of workspaces for the given agent
- L269-277 _private* method_ `static AutoSdkConfig? GetAutoSdkConfig(IEnumerable<IPoolConfig> pools)`
- L287-298 _public method_ `public static async Task<AgentWorkspaceInfo?> GetAutoSdkWorkspaceAsync(this PoolService poolService, IAgent agent, PerforceCluster cluster, CancellationToken cancellationToken)` — Gets all the autosdk workspaces required for an agent
- L309-331 _public method_ `public static async Task<AgentWorkspaceInfo?> GetAutoSdkWorkspaceAsync(this PoolService poolService, IAgent agent, PerforceCluster perforceCluster, DateTime validAtTime, CancellationToken cancellationToken)` — Get a list of workspaces for the given agent

### `Source/Programs/Horde/Plugins/Build/HordeServer.Build/VersionControl/Perforce/ServerPerforceController.cs` (HordeServer.Build)


#### class `HordeServer.VersionControl.Perforce.ServerPerforceController`  
`public class ServerPerforceController : HordeControllerBase`  
_public; L18-63_
- attrs: `[ApiController] [Authorize] [Route("[controller]")]`
- inherits: `HordeControllerBase`
- desc: Implements preflight of config changes with Perforce
- L20 _private* field_ `readonly IConfigService _configService`
- L21 _private* field_ `readonly IChangelistFileReader _fileReader`
- L26-30 _public ctor_ `public ServerPerforceController(IConfigService configService, IChangelistFileReader fileReader)` — Constructor
- L37-62 _public method_ `public async Task<ActionResult<PreflightConfigResponse>> PreflightConfigAsync(PreflightConfigRequest request, CancellationToken cancellationToken)` — attrs: `[HttpPost] [Route("/api/v1/server/preflightconfig")]` — Returns settings for automating auth against this server
