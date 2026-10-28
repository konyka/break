# CSharp / HordeServer.Compute

- project root: `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute`
- files: 97; symbols: 2424
- symbol kinds: class=179, const=30, ctor=154, delegate=2, enum=10, enumerator=35, event=4, field=378, indexer=3, interface=29, method=739, property=830, record=21, record struct=9, struct=1
- access marked `*` is implicit (not written in source)

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/AgentAclAction.cs` (HordeServer.Compute)


#### class `HordeServer.Agents.AgentAclAction`  
`public static class AgentAclAction`  
_public; L10-41_
- desc: ACL actions which apply to agents
- L15 _public property_ `public static AclAction CreateAgent { get; }` — Ability to create an agent. This may be done explicitly, or granted to agents to allow them to self-register.
- L20 _public property_ `public static AclAction CreateWorkstationAgent { get; }` — Ability to create a workstation agent. Granted to users with hardware to offer.
- L25 _public property_ `public static AclAction UpdateAgent { get; }` — Update an agent's name, pools, etc...
- L30 _public property_ `public static AclAction DeleteAgent { get; }` — Soft-delete an agent
- L35 _public property_ `public static AclAction ViewAgent { get; }` — View an agent
- L40 _public property_ `public static AclAction ListAgents { get; }` — List the available agents

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/AgentClaimExtensions.cs` (HordeServer.Compute)


#### class `HordeServer.Agents.ClaimExtensions`  
`public static class ClaimExtensions`  
_public; L14-71_
- desc: Extension methods for getting agent-related claims from principals
- L19-22 _public method_ `public static bool HasAgentClaim(this ClaimsPrincipal user, AgentId agentId)` — Test whether a principal is the given agent
- L27-30 _public method_ `public static bool HasLeaseClaim(this ClaimsPrincipal user, LeaseId leaseId)` — Test whether a principal is the given lease
- L35-38 _public method_ `public static bool HasSessionClaim(this ClaimsPrincipal user, SessionId sessionId)` — Test whether a principal is the given session
- L43-54 _public method_ `public static LeaseId? GetLeaseClaim(this ClaimsPrincipal user)` — Attempts to get the lease id from the given principal
- L59-70 _public method_ `public static SessionId? GetSessionClaim(this ClaimsPrincipal user)` — Attempts to get the session id from the given principal

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/AgentCollection.cs` (HordeServer.Compute)


#### class `HordeServer.Agents.AgentCollection`  
`public sealed class AgentCollection : IAgentCollection, IHostedService`  
_public; L36-1473_
- inherits: `IAgentCollection, IHostedService`
- desc: Collection of agent documents
- L267 _private* field_ `readonly IMongoCollection<AgentDocument> _agentCollection`
- L268 _private* field_ `readonly IMongoCollection<SessionDocument> _sessionCollection`
- L269 _private* field_ `readonly ILeaseCollection _leaseCollection`
- L270 _private* field_ `readonly IAgentScheduler _scheduler`
- L271 _private* field_ `readonly IAuditLog<AgentId> _auditLog`
- L272 _private* field_ `readonly IClock _clock`
- L273 _private* field_ `readonly ITicker _sharedTicker`
- L274 _private* field_ `readonly ConcurrentDictionary<SessionId, TaskCompletionSource> _sessionIdToTcs = ...`
- L274 _private* field_ `readonly ConcurrentDictionary< _sessionIdToTcs = new ConcurrentDictionary<SessionId, TaskCompletionSource>()`
- L275 _private* field_ `readonly Tracer _tracer`
- L276 _private* field_ `readonly ILogger _logger`
- L281-299 _public ctor_ `public AgentCollection(IMongoService mongoService, ILeaseCollection leaseCollection, IAgentScheduler scheduler, IClock clock, IAuditLog<AgentId> auditLog, Tracer tracer, ILogger<AgentCollection> logger)` — Constructor
- L302-305 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L308-312 _public method_ `public async Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L315-319 _public method_ `public async Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L321-327 _internal method_ `internal async ValueTask TickSharedAsync(CancellationToken stoppingToken)`
- L329-349 _internal method_ `internal async Task TerminateExpiredSessionsAsync(CancellationToken cancellationToken)`
- L351-383 _internal method_ `internal async Task DeleteExpiredEphemeralAgentsAsync(CancellationToken cancellationToken)`
- L386-419 _private* method_ `async ValueTask<AgentDocument?> PostLoadAsync(AgentDocument? document, CancellationToken cancellationToken)`
- L421-467 _private* method_ `async Task<bool> MoveLeasesToSchedulerAsync(AgentDocument document, CancellationToken cancellationToken)`
- L471-483 _private* method_ `async ValueTask<List<AgentDocument>> PostLoadAsync(List<AgentDocument> documents, CancellationToken cancellationToken)`
- L485 _private* method_ `ValueTask<Agent?> CreateAgentObjectAsync(AgentDocument? document, CancellationToken cancellationToken)`
- L488-530 _private* method_ `async Task<List<IAgent>> CreateAgentObjectsBatchedAsync(List<AgentDocument> documents, CancellationToken cancellationToken)`
- L532-590 _private* method_ `async ValueTask<Agent?> CreateAgentObjectAsync(AgentDocument? document, RpcSession? session, CancellationToken cancellationToken)`
- L593-604 _public method_ `public async Task<IAgent> AddAsync(CreateAgentOptions options, CancellationToken cancellationToken)` — (inheritdoc)
- L607-629 _private* method_ `async Task<Agent?> TryResetAsync(Agent agent, bool ephemeral, string enrollmentKey, CancellationToken cancellationToken = default)` — (inheritdoc)
- L632-657 _private* method_ `async Task<Agent?> TryDeleteAsync(Agent agent, CancellationToken cancellationToken)` — (inheritdoc)
- L660-664 _public method_ `public async Task<IAgent?> GetAsync(AgentId agentId, CancellationToken cancellationToken)` — (inheritdoc)
- L666-671 _private* method_ `async Task<AgentDocument?> GetDocumentAsync(AgentId agentId, CancellationToken cancellationToken)`
- L674-679 _public method_ `public async Task<IReadOnlyList<IAgent>> GetManyAsync(List<AgentId> agentIds, CancellationToken cancellationToken)` — (inheritdoc)
- L682-726 _public method_ `public async IAsyncEnumerable<IAgent> FindAsync(PoolId? poolId, DateTime? modifiedAfter, string? property, AgentStatus? status, bool? enabled, bool includeDeleted, bool consistentRead, [EnumeratorCancellation] CancellationToken cancellationToken)` — (inheritdoc)
- L728-734 _private* method_ `async Task<SessionDocument?> GetSessionAsync(AgentId agentId, SessionId sessionId, CancellationToken cancellationToken = default)`
- L736-751 _private* method_ `async Task<List<SessionDocument>> FindSessionsAsync(AgentId agentId, DateTime? startTime, DateTime? finishTime, int index, int count, CancellationToken cancellationToken = default)`
- L760-769 _private method_ `private async Task<AgentDocument?> TryUpdateAsync(AgentDocument current, UpdateDefinition<AgentDocument> update, CancellationToken cancellationToken)` — Update a single document
- L771-844 _private* method_ `async Task<Agent?> TryUpdateSettingsAsync(Agent agent, UpdateAgentOptions options, CancellationToken cancellationToken)`
- L846-1036 _private* method_ `async Task<Agent?> TryUpdateSessionAsync(Agent agent, UpdateSessionOptions options, CancellationToken cancellationToken)`
- L1039-1059 _private* method_ `static LeaseMetrics? ToNativeLeaseMetrics(RpcLeaseMetrics? metrics)` — attrs: `[SuppressMessage("Maintainability", "CA1508:Avoid dead conditional code", Justification = "Protobuf generated code may contain null fields")]`
- L1061-1066 _private* method_ `static void SetPoolProperties(List<string> properties, List<PoolId> pools)`
- L1073-1101 _private* method_ `List<string> MergeOverrideProperties(AgentId agentId, IEnumerable<string> properties, IReadOnlyList<string> overrides)` — Merges override properties into a property list. For each key present in both the overrides and the existing properties, existing entries with that key are replaced by the override entries. Override entries with keys not present in the existing properties are ignored.
- L1107-1126 _private* method_ `Dictionary<string, int>? MergeOverrideResources(AgentId agentId, IReadOnlyDictionary<string, int>? resources, IReadOnlyDictionary<string, int> overrides)` — Merges override resources into an existing resource dictionary, replacing values for existing keys. Override entries with keys not present in the existing resources are ignored.
- L1132-1136 _private* method_ `static string GetPropertyKey(string property)` — Extracts the key portion from a "KEY=VALUE" property string. Returns the full string if no '=' is found.
- L1138 _private* method_ `static List<PoolId> CreatePoolsList(IEnumerable<PoolId> pools)`
- L1141-1167 _private* method_ `static List<PoolId> CreatePoolsList(IEnumerable<PoolId> dynamicPools, IEnumerable<PoolId> explicitPools, IEnumerable<string>? properties)`
- L1169-1189 _private* method_ `static bool ResourcesEqual(IReadOnlyDictionary<string, int>? dictA, IReadOnlyDictionary<string, int>? dictB)`
- L1192-1209 _private* method_ `async Task<Agent?> TryUpdateWorkspacesAsync(Agent agent, List<AgentWorkspaceInfo> workspaces, bool requestConform, CancellationToken cancellationToken)` — (inheritdoc)
- L1212-1276 _private* method_ `async Task<Agent?> TryCreateSessionAsync(Agent agent, CreateSessionOptions options, CancellationToken cancellationToken)` — (inheritdoc)
- L1279-1283 _private* method_ `async Task<Agent?> TryTerminateSessionAsync(Agent agent, CancellationToken cancellationToken)` — (inheritdoc)
- L1286-1350 _private* method_ `async Task<Agent?> TryCreateLeaseAsync(Agent agent, CreateLeaseOptions options, CancellationToken cancellationToken)` — (inheritdoc)
- L1352-1376 _private* method_ `static void GetNewLeaseUpdates(AgentDocument agent, ReadOnlySpan<byte> payloadData, List<UpdateDefinition<AgentDocument>> updates)`
- L1379-1423 _private* method_ `async Task<Agent?> TryCancelLeaseAsync(Agent agent, int leaseIdx, LeaseOutcomeReason? reason, CancellationToken cancellationToken)` — (inheritdoc)
- L1425-1432 _private* method_ `void OnSessionUpdate(SessionId sessionId)`
- L1434-1443 _private* method_ `async Task<Agent?> WaitForSessionUpdateAsync(Agent agent, CancellationToken cancellationToken)`
- L1445-1466 _private* method_ `async Task<RpcSession?> WaitForSessionUpdateAsync(RpcSession session, CancellationToken cancellationToken)`
- L1469-1472 _public method_ `public IAuditLogChannel<AgentId> GetLogger(AgentId agentId)` — (inheritdoc)

#### class `HordeServer.Agents.AgentCollection.Agent`  
`class Agent : IAgent`  
_private*; L38-138_
- inherits: `IAgent`
- L40 _private* property_ `static IReadOnlyList<string> DefaultProperties { get; }`
- L41 _private* property_ `static IReadOnlyDictionary<string, int> DefaultResources { get; }`
- L43 _public property_ `public AgentDocument Document => ...`
- L44 _public property_ `public RpcSession? Session => ...`
- L46 _private* field_ `readonly AgentCollection _collection`
- L47 _private* field_ `readonly AgentDocument _document`
- L48 _private* field_ `readonly RpcSession? _session`
- L50 _public property_ `public AgentId Id => ...`
- L51 _private* property_ `SessionId? IAgent.SessionId => ...`
- L52 _private* property_ `DateTime? IAgent.SessionExpiresAt => ...`
- L53 _private* property_ `AgentStatus IAgent.Status => ...`
- L54 _private* property_ `DateTime? IAgent.LastOnlineTime => ...`
- L55 _private* property_ `bool IAgent.Enabled => ...`
- L56 _private* property_ `bool IAgent.Ephemeral => ...`
- L57 _private* property_ `AgentMode IAgent.Mode => ...`
- L58 _private* property_ `bool IAgent.Deleted => ...`
- L59 _private* property_ `string? IAgent.Version => ...`
- L60 _private* property_ `string? IAgent.Comment => ...`
- L61 _private* property_ `IReadOnlyList<string> IAgent.ServerDefinedProperties => ...`
- L62 _private* property_ `IReadOnlyList<string> IAgent.Properties => ...`
- L63 _private* property_ `IReadOnlyDictionary<string, int> IAgent.Resources => ...`
- L64 _private* property_ `string? IAgent.LastUpgradeVersion => ...`
- L65 _private* property_ `DateTime? IAgent.LastUpgradeTime => ...`
- L66 _private* property_ `int? IAgent.UpgradeAttemptCount => ...`
- L67 _private* property_ `IReadOnlyList<PoolId> IAgent.Pools => ...`
- L68 _private* property_ `IReadOnlyList<PoolId> IAgent.DynamicPools => ...`
- L69 _private* property_ `IReadOnlyList<PoolId> IAgent.ExplicitPools => ...`
- L70 _private* property_ `bool IAgent.RequestConform => ...`
- L71 _private* property_ `bool IAgent.RequestFullConform => ...`
- L72 _private* property_ `bool IAgent.RequestRestart => ...`
- L73 _private* property_ `bool IAgent.RequestShutdown => ...`
- L74 _private* property_ `bool IAgent.RequestForceRestart => ...`
- L75 _private* property_ `string? IAgent.LastShutdownReason => ...`
- L76 _private* property_ `IReadOnlyList<AgentWorkspaceInfo> IAgent.Workspaces => ...`
- L77 _private* property_ `DateTime IAgent.LastConformTime => ...`
- L78 _private* property_ `int? IAgent.ConformAttemptCount => ...`
- L79 _private* property_ `IReadOnlyList<IAgentLease> IAgent.Leases => ...`
- L80 _private* property_ `string IAgent.EnrollmentKey => ...`
- L81 _private* property_ `DateTime IAgent.UpdateTime => ...`
- L82 _private* property_ `uint IAgent.UpdateIndex => ...`
- L84-89 _public ctor_ `public Agent(AgentCollection collection, AgentDocument document, RpcSession? session)`
- L92 _public method_ `public async Task<ISession?> GetSessionAsync(SessionId sessionId, CancellationToken cancellationToken = default)` — (inheritdoc)
- L96 _public method_ `public async Task<IReadOnlyList<ISession>> FindSessionsAsync(DateTime? startTime, DateTime? finishTime, int index, int count, CancellationToken cancellationToken = default)` — (inheritdoc)
- L100 _public method_ `public async Task<IAgent?> TryCreateLeaseAsync(CreateLeaseOptions options, CancellationToken cancellationToken = default)` — (inheritdoc)
- L104 _public method_ `public async Task<IAgent?> TryCancelLeaseAsync(int leaseIdx, LeaseOutcomeReason? reason = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L108 _public method_ `public async Task<IAgent?> TryDeleteAsync(CancellationToken cancellationToken = default)` — (inheritdoc)
- L112 _public method_ `public async Task<IAgent?> TryResetAsync(bool ephemeral, string enrollmentKey, CancellationToken cancellationToken = default)` — (inheritdoc)
- L116 _public method_ `public async Task<IAgent?> TryCreateSessionAsync(CreateSessionOptions options, CancellationToken cancellationToken = default)` — (inheritdoc)
- L120 _public method_ `public async Task<IAgent?> TryTerminateSessionAsync(CancellationToken cancellationToken = default)` — (inheritdoc)
- L124 _public method_ `public async Task<IAgent?> TryUpdateSessionAsync(UpdateSessionOptions options, CancellationToken cancellationToken = default)` — (inheritdoc)
- L128 _public method_ `public async Task<IAgent?> TryUpdateAsync(UpdateAgentOptions options, CancellationToken cancellationToken = default)` — (inheritdoc)
- L132 _public method_ `public async Task<IAgent?> TryUpdateWorkspacesAsync(List<AgentWorkspaceInfo> workspaces, bool requestConform, CancellationToken cancellationToken = default)` — (inheritdoc)
- L136 _public method_ `public async Task<IAgent?> WaitForUpdateAsync(CancellationToken cancellationToken = default)` — (inheritdoc)

#### class `HordeServer.Agents.AgentCollection.AgentDocument`  
`class AgentDocument`  
_private*; L143-233_
- desc: Concrete implementation of an agent document
- L146 _public property_ `public AgentId Id { get; set; }` — attrs: `[BsonRequired, BsonId]`
- L148 _public property_ `public SessionId? SessionId { get; set; }`
- L152 _public property_ `public AgentStatus? Status { get; set; }` — attrs: `[BsonIgnoreIfNull] [Obsolete("Session state now stored in Redis")]`
- L154 _public property_ `public DateTime? LastOnlineTime { get; set; }`
- L157 _public property_ `public bool Enabled { get; set; }` — attrs: `[BsonRequired]`
- L159 _public property_ `public bool Ephemeral { get; set; }`
- L161 _public property_ `public AgentMode Mode { get; set; }`
- L164 _public property_ `public bool Deleted { get; set; }` — attrs: `[BsonIgnoreIfDefault, BsonDefaultValue(false)]`
- L167 _public property_ `public string? Version { get; set; }` — attrs: `[BsonElement("Version2")]`
- L169 _public property_ `public List<string>? ServerDefinedProperties { get; set; }`
- L170 _public property_ `public List<string>? Properties { get; set; }`
- L171 _public property_ `public Dictionary<string, int>? Resources { get; set; }`
- L174 _public property_ `public string? LastUpgradeVersion { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L177 _public property_ `public DateTime? LastUpgradeTime { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L180 _public property_ `public int? UpgradeAttemptCount { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L182 _public property_ `public List<PoolId> Pools { get; set; }`
- L183 _public property_ `public List<PoolId> DynamicPools { get; set; }`
- L184 _public property_ `public List<PoolId> ExplicitPools { get; set; }`
- L187 _public property_ `public bool RequestConform { get; set; }` — attrs: `[BsonIgnoreIfDefault, BsonDefaultValue(false)]`
- L190 _public property_ `public bool RequestFullConform { get; set; }` — attrs: `[BsonIgnoreIfDefault, BsonDefaultValue(false)]`
- L193 _public property_ `public bool RequestRestart { get; set; }` — attrs: `[BsonIgnoreIfDefault, BsonDefaultValue(false)]`
- L196 _public property_ `public bool RequestShutdown { get; set; }` — attrs: `[BsonIgnoreIfDefault, BsonDefaultValue(false)]`
- L199 _public property_ `public bool RequestForceRestart { get; set; }` — attrs: `[BsonIgnoreIfDefault, BsonDefaultValue(false)]`
- L202 _public property_ `public string? LastShutdownReason { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L204 _public property_ `public List<AgentWorkspaceInfo> Workspaces { get; set; }`
- L205 _public property_ `public DateTime LastConformTime { get; set; }`
- L208 _public property_ `public int? ConformAttemptCount { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L212 _public property_ `public List<AgentLease>? Leases { get; set; }` — attrs: `[BsonIgnoreIfNull] [Obsolete("Session state now stored in Redis")]`
- L214 _public property_ `public DateTime UpdateTime { get; set; }`
- L215 _public property_ `public uint UpdateIndex { get; set; }`
- L216 _public property_ `public string EnrollmentKey { get; set; }`
- L217 _public property_ `public string? Comment { get; set; }`
- L220 _public property_ `public int DocumentVersion { get; set; }` — attrs: `[BsonElement("dv")]`
- L223-225 _private ctor_ `private AgentDocument()` — attrs: `[BsonConstructor]`
- L227-232 _public ctor_ `public AgentDocument(AgentId id, bool ephemeral, string enrollmentKey)`

#### class `HordeServer.Agents.AgentCollection.SessionDocument`  
`class SessionDocument : ISession`  
_private*; L238-265_
- inherits: `ISession`
- desc: Concrete implementation of ISession
- L241 _public property_ `public SessionId Id { get; set; }` — attrs: `[BsonRequired, BsonId]`
- L244 _public property_ `public AgentId AgentId { get; set; }` — attrs: `[BsonRequired]`
- L246 _public property_ `public DateTime StartTime { get; set; }`
- L247 _public property_ `public DateTime? FinishTime { get; set; }`
- L248 _public property_ `public string Version { get; set; }`
- L251-253 _private ctor_ `private SessionDocument()` — attrs: `[BsonConstructor]`
- L255-264 _public ctor_ `public SessionDocument(SessionId id, AgentId agentId, DateTime startTime, string? version)`

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/AgentScheduler.cs` (HordeServer.Compute)


#### class `HordeServer.Agents.AgentScheduler`  
`internal class AgentScheduler : IAgentScheduler, IHostedService, IAsyncDisposable`  
_internal; L20-823_
- inherits: `IAgentScheduler, IHostedService, IAsyncDisposable`
- L25 _public property_ `public static TimeSpan ExpireFiltersTime { get; }` — Time after which we expire filters
- L82 _internal method_ `internal static string SessionStateKey(string sessionId)`
- L84-88 _private* method_ `SessionId FromSessionStateKey(string sessionStateKey)`
- L117 _public event_ `public event Action<SessionId>? SessionUpdated`
- L119 _private* field_ `readonly IRedisService _redisService`
- L120 _private* field_ `readonly IClock _clock`
- L121 _private* field_ `readonly ITicker _updateCachedFiltersTicker`
- L122 _private* field_ `readonly ITicker _expireFiltersTicker`
- L123 _private* field_ `readonly ILogger _logger`
- L124 _private* field_ `readonly MemoryCache _localSessionCache`
- L125 _private* field_ `readonly MemoryCache _requirementsCache`
- L127 _private* field_ `LocalFilter[] _cachedFilters = Array.Empty<LocalFilter>()`
- L129 _private* field_ `static readonly RedisChannel<SessionId> s_sessionUpdateChannel = new RedisChannel<SessionId>(RedisChannel.Literal("compute:sessions:update"))`
- L131-138 _private* method_ `void AddLocalSessionToCache(SessionId sessionId, LocalSession localSession)`
- L140-194 _private* method_ `async ValueTask<LocalSession?> TryGetLocalSessionAsync(RpcSession session, CancellationToken cancellationToken)`
- L196 _private* field_ `IAsyncDisposable? _updateEventSubscription`
- L201-210 _public ctor_ `public AgentScheduler(IRedisService redisService, IClock clock, ILogger<AgentScheduler> logger)` — Constructor
- L213-226 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L228 _private* method_ `void OnSessionUpdate(SessionId sessionId)`
- L232-238 _public method_ `public async Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L241-251 _public method_ `public async Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L256-290 _public method_ `public async Task<RpcSession?> TryCreateSessionAsync(AgentId agentId, SessionId sessionId, RpcAgentCapabilities capabilities, CancellationToken cancellationToken = default)` — (inheritdoc)
- L293-297 _public method_ `public async Task<RpcSession?> TryGetSessionAsync(SessionId sessionId, CancellationToken cancellationToken = default)` — (inheritdoc)
- L300-328 _public method_ `public async Task<Dictionary<SessionId, RpcSession>> TryGetSessionsAsync(IReadOnlyList<SessionId> sessionIds, CancellationToken cancellationToken = default)` — (inheritdoc)
- L331-335 _public method_ `public async Task<RpcAgentCapabilities?> TryGetCapabilitiesAsync(RpcSession session, CancellationToken cancellationToken = default)` — (inheritdoc)
- L338-450 _public method_ `public async Task<RpcSession?> TryUpdateSessionAsync(RpcSession session, RpcSession? newSession, RpcAgentCapabilities? newCapabilities, CancellationToken cancellationToken)` — (inheritdoc)
- L453-470 _public method_ `public async IAsyncEnumerable<RpcSession> FindExpiredSessionsAsync([EnumeratorCancellation] CancellationToken cancellationToken = default)` — (inheritdoc)
- L473-496 _public method_ `public async Task<List<SessionId>> RemoveOrphanedSessionsAsync(CancellationToken cancellationToken = default)` — (inheritdoc)
- L502-533 _public method_ `public async Task<IoHash> CreateFilterAsync(RpcAgentRequirements requirements, CancellationToken cancellationToken = default)` — (inheritdoc)
- L538-547 _private* method_ `async ValueTask UpdateCachedFiltersTickAsync(CancellationToken cancellationToken)` — Update all the cached filters
- L549-571 _private* method_ `async Task<bool> TryUpdateCachedFiltersAsync(CancellationToken cancellationToken)`
- L576-599 _private* method_ `async ValueTask ExpireFiltersAsync(CancellationToken cancellationToken)` — Expire all the filters older than the standard expiry time
- L602-607 _public method_ `public async Task TouchFilterAsync(IoHash requirementsHash, CancellationToken cancellationToken = default)` — (inheritdoc)
- L610-614 _public method_ `public async Task<IoHash[]> GetFiltersAsync(CancellationToken cancellationToken = default)` — (inheritdoc)
- L616-641 _public method_ `public async Task ForceUpdateFiltersAsync(CancellationToken cancellationToken)`
- L643-687 _private* method_ `static void UpdateFilters(ITransaction transaction, SessionId sessionId, IReadOnlyDictionary<IoHash, bool> oldFilters, IReadOnlyDictionary<IoHash, bool> newFilters)`
- L689-704 _private* method_ `Dictionary<IoHash, bool> FindMatchingFilters(LocalCapabilities capabilities, RpcSession session)`
- L706-723 _private* method_ `static bool MeetsRequirements(LocalCapabilities capabilities, RpcAgentRequirements requirements)`
- L725-757 _private* method_ `static bool IsAvailable(LocalCapabilities capabilities, RpcSession session, RpcAgentRequirements requirements)`
- L759-766 _private* method_ `void AddRequirementsToCache(IoHash requirementsHash, RpcAgentRequirements requirements)`
- L769-783 _public method_ `public async ValueTask<RpcAgentRequirements?> TryGetFilterRequirementsAsync(IoHash requirementsHash, CancellationToken cancellationToken)` — (inheritdoc)
- L786-796 _public method_ `public async IAsyncEnumerable<SessionId> EnumerateFilteredSessionsAsync(IoHash requirementsHash, SessionFilterType type, [EnumeratorCancellation] CancellationToken cancellationToken = default)` — (inheritdoc)
- L802-806 _public method_ `public async Task<LeaseId[]> FindActiveLeaseIdsAsync(CancellationToken cancellationToken = default)` — (inheritdoc)
- L809-813 _public method_ `public async Task<int> GetChildLeaseCountAsync(LeaseId id, CancellationToken cancellationToken = default)` — (inheritdoc)
- L816-820 _public method_ `public async Task<LeaseId[]> GetChildLeaseIdsAsync(LeaseId id, CancellationToken cancellationToken = default)` — (inheritdoc)

#### class `HordeServer.Agents.AgentScheduler.Keys`  
`static class Keys`  
_private*; L28-38_
- L30 _public property_ `public static FilterCollectionKeys Filters { get; }`
- L33 _public property_ `public static SessionCollectionKeys Sessions { get; }`
- L36 _public property_ `public static LeaseCollectionKeys Leases { get; }`

#### record struct `HordeServer.Agents.AgentScheduler.FilterCollectionKeys`  
`record struct FilterCollectionKeys`  
_private*; L40-47_
- L42 _public property_ `public RedisHashKey<IoHash, long> Current => ...`
- L45 _public indexer_ `public FilterKeys this[IoHash requirementsHash]`

#### record struct `HordeServer.Agents.AgentScheduler.FilterKeys`  
`record struct FilterKeys(IoHash RequirementsHash)`  
_private*; L49-59_
- L51 _public property_ `public RedisSetKey<SessionId> AvailableSessions => ...`
- L54 _public property_ `public RedisSetKey<SessionId> PotentialSessions => ...`
- L57 _public property_ `public RedisStringKey<RpcAgentRequirements> Requirements => ...`

#### record struct `HordeServer.Agents.AgentScheduler.SessionCollectionKeys`  
`record struct SessionCollectionKeys`  
_private*; L61-68_
- L63 _public property_ `public RedisHashKey<SessionId, long> Current => ...`
- L66 _public indexer_ `public SessionKeys this[SessionId sessionId]`

#### record struct `HordeServer.Agents.AgentScheduler.SessionKeys`  
`record struct SessionKeys(SessionId SessionId)`  
_private*; L70-80_
- L72 _public property_ `public RedisStringKey<RpcAgentCapabilities> Capabilities => ...`
- L75 _public property_ `public RedisHashKey<IoHash, bool> Filters => ...`
- L78 _public property_ `public RedisStringKey<RpcSession> State => ...`

#### record struct `HordeServer.Agents.AgentScheduler.LeaseCollectionKeys`  
`record struct LeaseCollectionKeys`  
_private*; L90-97_
- L92 _public property_ `public RedisSetKey<LeaseId> Current => ...`
- L95 _public indexer_ `public LeaseKeys this[LeaseId leaseId]`

#### record struct `HordeServer.Agents.AgentScheduler.LeaseKeys`  
`record struct LeaseKeys(LeaseId LeaseId)`  
_private*; L99-103_
- L101 _public property_ `public RedisSetKey<LeaseId> Children => ...`

#### record `HordeServer.Agents.AgentScheduler.LocalFilter`  
`record class LocalFilter(IoHash Hash, RpcAgentRequirements Requirements)`  
_private*; L107-107_

#### record `HordeServer.Agents.AgentScheduler.LocalCapabilities`  
`record class LocalCapabilities(IoHash Hash, RpcAgentCapabilities Message, IReadOnlySet<string> Properties)`  
_private*; L109-113_
- L111-112 _public ctor_ `public LocalCapabilities(IoHash hash, RpcAgentCapabilities message) : this(hash, message, new HashSet<string>(message.Properties, StringComparer.Ordinal))`

#### record `HordeServer.Agents.AgentScheduler.LocalSession`  
`record class LocalSession(long UpdateTicks, LocalCapabilities Capabilities, IReadOnlyDictionary<IoHash, bool> Filters)`  
_private*; L115-115_

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/AgentService.cs` (HordeServer.Compute)


#### class `HordeServer.Agents.AgentRateTable`  
`public class AgentRateTable`  
_public; L35-42_
- attrs: `[RedisConverter(typeof(RedisCbConverter<>))]`
- desc: Singleton used to store agent costs
- L41 _public property_ `public List<AgentRateConfig> Entries { get; set; }` — attrs: `[CbField]` — List of costs for different agent types

#### class `HordeServer.Agents.AgentService`  
`public sealed class AgentService : IHostedService, IAsyncDisposable`  
_public; L47-898_
- inherits: `IHostedService, IAsyncDisposable`
- desc: Wraps functionality for manipulating agents
- L52 _public field_ `public static readonly TimeSpan SessionExpiryTime = RpcSession.ExpireAfterTime` — Maximum time between updates for an agent to be considered online
- L57 _public field_ `public static readonly TimeSpan SessionLongPollTime = TimeSpan.FromSeconds(55)` — Time before a session expires that we will poll until
- L62 _public field_ `public static readonly TimeSpan SessionRenewTime = TimeSpan.FromSeconds(50)` — Time after which a session will be renewed
- L67 _public property_ `public IAgentCollection Agents { get; }` — Collection of agent documents
- L69 _private* field_ `readonly ILeaseCollection _leases`
- L70 _private* field_ `readonly IAclService _aclService`
- L71 _private* field_ `readonly IDowntimeService _downtimeService`
- L72 _private* field_ `readonly ITaskSource[] _taskSources`
- L73 _private* field_ `readonly IRedisService _redisService`
- L74 _private* field_ `readonly IHostApplicationLifetime _applicationLifetime`
- L75 _private* field_ `readonly IOptionsMonitor<ComputeConfig> _computeConfig`
- L76 _private* field_ `readonly IClock _clock`
- L77 _private* field_ `readonly Tracer _tracer`
- L78 _private* field_ `readonly ILogger _logger`
- L79 _private* field_ `readonly ITicker _ticker`
- L82 _private* field_ `readonly AsyncCachedValue<IReadOnlyList<IPoolConfig>> _cachedPools` — Lazily updated list of current pools
- L85 _private* field_ `IReadOnlyDictionary<AgentId, IAgent>? _cachedAgents` — Manually updated cached list of current agents
- L85 _private* field_ `IReadOnlyDictionary< _cachedAgents` — Manually updated cached list of current agents
- L88 _private* field_ `IEnumerable<Measurement<int>> _measurements = new List<Measurement<int>>()` — OpenTelemetry measurements (gauges)
- L93-123 _public ctor_ `public AgentService( IAgentCollection agents, ILeaseCollection leases, IAclService aclService, IDowntimeService downtimeService, IPoolCollection poolCollection, IEnumerable<ITaskSource> taskSources, IRedisService redisService, IHostApplicationLifetime applicationLifetime, IOptionsMonitor<ComputeConfig> computeConfig, IClock clock, Tracer tracer, Meter meter, ILogger<AgentService> logger)` — Constructor
- L126-129 _public method_ `public async Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L132-135 _public method_ `public async Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L138-142 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L150-167 _public method_ `public async ValueTask<Dictionary<string, string>?> GetPayloadDetailsAsync(ReadOnlyMemory<byte>? payload, CancellationToken cancellationToken = default)` — Gets user-readable payload information
- L176-183 _public method_ `public async ValueTask<string> IssueSessionTokenAsync(AgentId agentId, SessionId sessionId, CancellationToken cancellationToken = default)` — Issues a bearer token for the given session id
- L191-207 _public method_ `public async Task<IAgent> CreateAgentAsync(CreateAgentOptions options, CancellationToken cancellationToken = default)` — Register a new agent
- L215-218 _public method_ `public Task<IAgent?> GetAgentAsync(AgentId agentId, CancellationToken cancellationToken = default)` — Gets an agent by ID
- L229-232 _public method_ `public IAsyncEnumerable<IAgent> FindAgentsAsync(PoolId? poolId, DateTime? modifiedAfter, string? property, bool includeDeleted, CancellationToken cancellationToken)` — Finds all agents matching certain criteria
- L239-254 _public method_ `public async Task<IReadOnlyList<IAgent>> GetCachedAgentsAsync(CancellationToken cancellationToken)` — Get all agents from local in-memory cache
- L264-270 _public method_ `public async Task<bool> TryUpdateWorkspacesAsync(IAgent agent, List<AgentWorkspaceInfo> workspaces, bool pendingConform, CancellationToken cancellationToken)` — Update the current workspaces for an agent.
- L278-304 _public method_ `public async Task DeleteAgentAsync(IAgent? agent, CancellationToken cancellationToken = default)` — Marks the agent as deleted
- L306-320 _private* method_ `async ValueTask<List<PoolId>> GetDynamicPoolsAsync(IAgent agent, CancellationToken cancellationToken)`
- L330-369 _public method_ `public async Task<IAgent> CreateSessionAsync(IAgent agent, RpcAgentCapabilities capabilities, string? version, CancellationToken cancellationToken = default)` — Creates a new agent session
- L378-385 _private method_ `private static RpcAgentCapabilities NormalizeCapabilities(IAgent agent, RpcAgentCapabilities capabilities)` — Filters untrusted resource and property keys from capabilities Also injects potential server-controlled properties
- L390-406 _private* method_ `bool CanUseTaskSource(IAgent agent, ITaskSource taskSource)` — Determines whether a task source can currently issue tasks
- L411-423 _private method_ `private static void LogPropertyChanges(IAuditLogChannel<AgentId> agentLogger, IReadOnlyList<string> before, IReadOnlyList<string> after)` — Compare properties and write changes to audit log
- L432-529 _public method_ `public async Task<IAgent?> WaitForLeaseAsync(IAgent? agent, IList<HordeCommon.Rpc.Messages.RpcLease> newLeases, CancellationToken cancellationToken = default)` — Waits for a lease to be assigned to an agent
- L531-548 _private* method_ `async Task<Task<(ITaskSource, CreateLeaseOptions)?>> GuardedAssignLeaseAsync(ITaskSource source, IAgent agent, CancellationTokenSource cancellationSource)`
- L550-578 _private* method_ `(ITaskSource, CreateLeaseOptions)? WrapAssignedLease(ITaskSource source, Task<CreateLeaseOptions?> task, CancellationTokenSource cancellationSource)`
- L586-615 _public method_ `public async Task<bool> CancelLeaseAsync(ILease lease, LeaseOutcomeReason outcomeReason, CancellationToken cancellationToken)` — Cancels the specified agent lease
- L620-635 _public method_ `public async Task<IAgent?> UpdateSessionWithWaitAsync(IAgent inAgent, SessionId sessionId, AgentStatus status, RpcAgentCapabilities? capabilities, IList<HordeCommon.Rpc.Messages.RpcLease> newLeases, RpcAgentCapabilities? capabilityOverrides = null, CancellationToken cancellationToken = default)`
- L648-703 _public method_ `public async Task<IAgent?> UpdateSessionAsync(IAgent inAgent, SessionId sessionId, AgentStatus status, RpcAgentCapabilities? capabilities, IList<HordeCommon.Rpc.Messages.RpcLease> newLeases, RpcAgentCapabilities? capabilityOverrides = null, CancellationToken cancellationToken = default)` — Updates the state of the current agent session
- L711-721 _private method_ `private static async Task<IAgent?> TryTerminateSessionAsync(IAgent agent, CancellationToken cancellationToken = default)` — Terminates an existing session. Does not update the agent itself, if it's currently
- L734-737 _public method_ `public Task<IReadOnlyList<ILease>> FindLeasesAsync(AgentId? agentId, SessionId? sessionId, DateTime? startTime, DateTime? finishTime, int index, int count, CancellationToken cancellationToken = default)` — Finds all leases matching a set of criteria
- L748-751 _public method_ `public Task<IReadOnlyList<ILease>> FindLeasesByFinishTimeAsync(DateTime? minFinishTime, DateTime? maxFinishTime, int? index, int? count, CancellationToken cancellationToken = default)` — Finds all leases by finish time
- L759-762 _public method_ `public Task<ILease?> GetLeaseAsync(LeaseId leaseId, CancellationToken cancellationToken = default)` — Gets a specific lease
- L770-810 _public method_ `public async ValueTask<double?> GetRateAsync(AgentId agentId, CancellationToken cancellationToken = default)` — Gets the rate for the given agent
- L812-817 _internal method_ `internal async ValueTask TickAsync(CancellationToken stoppingToken)`
- L824-835 _public method_ `public async Task RefreshCachedAgentsAsync(CancellationToken cancellationToken = default)` — Updates the in-memory cache of current agents Called by ticker to avoid blocking reads. Updates in the background, in favor of slightly more stale agents
- L837-866 _private method_ `private async Task CollectMetricsAsync(CancellationToken cancellationToken = default)`
- L875-897 _public method_ `public bool AuthorizeSession(IAgent agent, ClaimsPrincipal user, out string reason)` — Determines if the user is authorized to perform an action on a particular agent

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/AgentVersionProvider.cs` (HordeServer.Compute)


#### class `HordeServer.Agents.AgentVersionProvider`  
`class AgentVersionProvider : IAgentVersionProvider`  
_internal*; L12-40_
- inherits: `IAgentVersionProvider`
- desc: Advertises the version number of the agent tool for the /api/v1/server/info endpoint
- L14 _private* field_ `readonly IToolCollection _toolCollection`
- L15 _private* field_ `readonly IClock _clock`
- L20-24 _public ctor_ `public AgentVersionProvider(IToolCollection toolCollection, IClock clock)` — Constructor
- L27-39 _public method_ `public async Task<string?> GetAsync(CancellationToken cancellationToken = default)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/AgentsController.cs` (HordeServer.Compute)


#### class `HordeServer.Agents.AgentsController`  
`public class AgentsController : HordeControllerBase`  
_public; L29-554_
- attrs: `[ApiController] [Authorize] [Route("[controller]")]`
- inherits: `HordeControllerBase`
- desc: Controller for the /api/v1/agents endpoint
- L31 _private* field_ `readonly AgentService _agentService`
- L32 _private* field_ `readonly IAgentTelemetryCollection _agentTelemetryCollection`
- L33 _private* field_ `readonly ILeaseCollection _leaseCollection`
- L34 _private* field_ `readonly IOptionsSnapshot<ComputeConfig> _computeConfig`
- L35 _private* field_ `readonly Tracer _tracer`
- L36 _private* field_ `readonly ILogger<AgentsController> _logger`
- L41-49 _public ctor_ `public AgentsController(AgentService agentService, IAgentTelemetryCollection agentTelemetryCollection, ILeaseCollection leaseCollection, IOptionsSnapshot<ComputeConfig> computeConfig, Tracer tracer, ILogger<AgentsController> logger)` — Constructor
- L67-118 _public method_ `public async Task<ActionResult<List<object>>> FindAgentsAsync( [FromQuery] PoolId? poolId = null, [FromQuery] Condition? condition = null, [FromQuery] bool includeDeleted = false, [FromQuery] bool invalidateCache = false, [FromQuery] int? index = null, [FromQuery] int? count = null, [FromQuery] DateTimeOffset? modifiedAfter = null, [FromQuery] string? propsFilter = null, [FromQuery] PropertyFilter? filter = null)` — attrs: `[HttpGet] [Route("/api/v1/agents")] [ProducesResponseType(typeof(List<GetAgentResponse>), 200)]` — Finds the agents matching specified criteria.
- L129-143 _public method_ `public async Task<ActionResult<object>> GetAgentAsync(AgentId agentId, [FromQuery] PropertyFilter? filter = null)` — attrs: `[HttpGet] [Route("/api/v1/agents/{agentId}")] [ProducesResponseType(typeof(GetAgentResponse), 200)]` — Retrieve information about a specific agent
- L148-175 _private* method_ `async ValueTask<object> GetAgentResponseAsync(IAgent agent, string? propFilter = null, PropertyFilter? filter = null, CancellationToken cancellationToken = default)` — Gets an individual agent response
- L177-183 _internal method_ `internal static GetAgentLeaseResponse CreateGetAgentLeaseResponse(ILease lease, Dictionary<string, string>? details, double? agentRate)`
- L185-197 _private method_ `private static string[] ToFlagNames(LeaseOutcomeReason reason)`
- L199-222 _private method_ `private static List<string> FilterProperties(List<string> properties, string? filter)`
- L224-254 _private* method_ `static GetAgentResponse CreateGetAgentResponse(IAgent agent, List<GetAgentLeaseResponse> leases, double? rate, string? propFilter)`
- L256-259 _internal method_ `internal static GetAgentWorkspaceResponse CreateGetAgentWorkspaceResponse(AgentWorkspaceInfo workspace)`
- L269-332 _public method_ `public async Task<ActionResult> UpdateAgentAsync(AgentId agentId, [FromBody] UpdateAgentRequest update)` — attrs: `[HttpPut] [Route("/api/v1/agents/{agentId}")]` — Update an agent's properties.
- L341-356 _public method_ `public async Task<ActionResult> DeleteAgentAsync(AgentId agentId)` — attrs: `[HttpDelete] [Route("/api/v1/agents/{agentId}")]` — Remove a registered agent.
- L369-383 _public method_ `public async Task<ActionResult> GetAgentHistoryAsync(AgentId agentId, [FromQuery] DateTime? minTime = null, [FromQuery] DateTime? maxTime = null, [FromQuery] int index = 0, [FromQuery] int count = 50)` — attrs: `[HttpGet] [Route("/api/v1/agents/{agentId}/history")]` — Retrieve historical information about a specific agent
- L396-411 _public method_ `public async Task<ActionResult<List<GetSessionResponse>>> FindSessionsAsync(AgentId agentId, [FromQuery] DateTimeOffset? startTime, [FromQuery] DateTimeOffset? finishTime, [FromQuery] int index = 0, [FromQuery] int count = 50)` — attrs: `[HttpGet] [Route("/api/v1/agents/{agentId}/sessions")]` — Find all the sessions of a particular agent
- L413-416 _private* method_ `static GetSessionResponse CreateGetSessionResponse(ISession session)`
- L426-446 _public method_ `public async Task<ActionResult<GetSessionResponse>> GetSessionAsync(AgentId agentId, SessionId sessionId)` — attrs: `[HttpGet] [Route("/api/v1/agents/{agentId}/sessions/{sessionId}")]` — Find all the sessions of a particular agent
- L456-469 _public method_ `public async Task<ActionResult<GetAgentTelemetryResponse>> FindTelemetryAsync(AgentId agentId, [FromQuery] DateTime minTime, [FromQuery] DateTime maxTime)` — attrs: `[HttpGet] [Route("/api/v1/agents/{agentId}/telemetry")]` — Finds telemetry for an agent within a time range
- L486-515 _public method_ `public async Task<ActionResult<List<object>>> FindLeasesAsync(AgentId agentId, [FromQuery] SessionId? sessionId, [FromQuery] DateTimeOffset? startTime, [FromQuery] DateTimeOffset? finishTime, [FromQuery] int index = 0, [FromQuery] int count = 1000, [FromQuery] PropertyFilter? filter = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/agents/{agentId}/leases")] [ProducesResponseType(200, Type = typeof(List<GetAgentLeaseResponse>))]` — Find all the leases for a particular agent
- L526-553 _public method_ `public async Task<ActionResult<GetAgentLeaseResponse>> GetLeaseAsync(AgentId agentId, LeaseId leaseId, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/agents/{agentId}/leases/{leaseId}")]` — Get info about a particular lease

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Enrollment/EnrollmentController.cs` (HordeServer.Compute)


#### class `HordeServer.Agents.Enrollment.EnrollmentController`  
`public class EnrollmentController : HordeControllerBase`  
_public; L17-97_
- attrs: `[ApiController] [Authorize]`
- inherits: `HordeControllerBase`
- desc: Controller for the /api/v1/enrollment endpoint
- L19 _private* field_ `readonly EnrollmentService _registrationService`
- L20 _private* field_ `readonly IOptionsSnapshot<ComputeConfig> _computeConfig`
- L25-29 _public ctor_ `public EnrollmentController(EnrollmentService registrationService, IOptionsSnapshot<ComputeConfig> computeConfig)` — Constructor
- L40-51 _public method_ `public async Task<ActionResult<object>> GetPendingAgentsAsync([FromQuery] PropertyFilter? filter = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/enrollment")] [ProducesResponseType(typeof(GetPendingAgentsResponse), 200)]` — Finds the agents matching specified criteria.
- L60-63 _public method_ `public Task<ActionResult<object>> LegacyGetPendingAgentsAsync([FromQuery] PropertyFilter? filter = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/registration")] [Obsolete("Use api/v1/enrollment instead")] [ProducesResponseType(typeof(GetPendingAgentsResponse), 200)]` — Legacy endpoint for enrollment
- L72-85 _public method_ `public async Task<ActionResult> ApproveAgentsAsync([FromBody] ApproveAgentsRequest request, CancellationToken cancellationToken)` — attrs: `[HttpPost] [Route("/api/v1/enrollment")]` — Retrieve information about a specific agent
- L93-96 _public method_ `public Task<ActionResult> LegacyApproveAgentsAsync([FromBody] ApproveAgentsRequest request, CancellationToken cancellationToken)` — attrs: `[HttpPost] [Route("/api/v1/registration")] [Obsolete("Use api/v1/enrollment instead")]` — Legacy registration method

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Enrollment/EnrollmentRpc.cs` (HordeServer.Compute)


#### class `HordeServer.Agents.Enrollment.EnrollmentRpc`  
`public class EnrollmentRpc : Horde.Common.Rpc.EnrollmentRpc.EnrollmentRpcBase`  
_public; L18-80_
- attrs: `[AllowAnonymous]`
- inherits: `Horde.Common.Rpc.EnrollmentRpc.EnrollmentRpcBase`
- desc: Allow agents to register with the server
- L20 _private* field_ `readonly EnrollmentService _registrationService`
- L21 _private* field_ `readonly AgentService _agentService`
- L22 _private* field_ `readonly IAclService _aclService`
- L23 _private* field_ `readonly ILogger _logger`
- L28-34 _public ctor_ `public EnrollmentRpc(EnrollmentService registrationService, AgentService agentService, IAclService aclService, ILogger<EnrollmentRpc> logger)` — Constructor
- L37-79 _public method_ `public override async Task EnrollAgent(IAsyncStreamReader<EnrollAgentRequest> requestStream, IServerStreamWriter<EnrollAgentResponse> responseStream, ServerCallContext context)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Enrollment/EnrollmentService.cs` (HordeServer.Compute)


#### record `HordeServer.Agents.Enrollment.EnrollmentRequest`  
`public record class EnrollmentRequest(string Key, string HostName, string Description)`  
_public; L17-17_
- attrs: `[RedisConverter(typeof(RedisJsonConverter<>))]`
- desc: Information about a machine requesting to be registered

#### class `HordeServer.Agents.Enrollment.EnrollmentService`  
`public sealed class EnrollmentService : IHostedService, IAsyncDisposable`  
_public; L22-211_
- inherits: `IHostedService, IAsyncDisposable`
- desc: Service which tracks agents pending enrollment
- L24 _private* field_ `readonly IRedisService _redisService`
- L25 _private* field_ `readonly IClock _clock`
- L26 _private* field_ `readonly RedisChannel _updateChannel`
- L27 _private* field_ `readonly RedisSortedSetKey<string> _keys = new("agents:registration:expire")`
- L28 _private* field_ `readonly RedisHashKey<string, EnrollmentRequest> _requests = ...`
- L28 _private* field_ `readonly RedisHashKey< _requests = new("agents:registration:requests")`
- L29 _private* field_ `readonly RedisHashKey<string, string> _approvals = ...`
- L29 _private* field_ `readonly RedisHashKey< _approvals = new("agents:registration:approvals")`
- L30 _private* field_ `readonly AsyncEvent _approvalEvent = new AsyncEvent()`
- L31 _private* field_ `readonly IOptionsMonitor<ComputeServerConfig> _staticComputeConfig`
- L33 _private* field_ `RedisSubscription? _subscription`
- L38-44 _public ctor_ `public EnrollmentService(IRedisService redisService, IClock clock, IOptionsMonitor<ComputeServerConfig> staticComputeConfig)` — Constructor
- L47-50 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L52 _private* method_ `static double GetTimestamp(DateTime time)`
- L56-59 _public method_ `public async Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L62-65 _public method_ `public async Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L67-74 _private* method_ `async Task StopSubscriptionAsync()`
- L76-89 _private* method_ `async Task ExpireKeysAsync(IDatabase redis, CancellationToken cancellationToken)`
- L98-119 _public method_ `public async Task<bool> AddAsync(string key, string hostName, string description, CancellationToken cancellationToken)` — Adds an agent as a candidate for the farm
- L127-156 _public method_ `public async Task<bool> ApproveAsync(string key, AgentId? agentId, CancellationToken cancellationToken = default)` — Approve an agent for connecting to the farm
- L162-169 _public method_ `public async Task<IReadOnlyList<EnrollmentRequest>> FindAsync(CancellationToken cancellationToken = default)` — Find all candidate machines that we can allow to connect
- L176-184 _public method_ `public async Task<AgentId?> GetApprovalAsync(string key, CancellationToken cancellationToken)` — Waits until a particular agent is approved
- L193-210 _public method_ `public async Task<AgentId> WaitForApprovalAsync(string key, string hostName, string description, CancellationToken cancellationToken)` — Waits until a particular agent is approved

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Fleet/AwsAutoScalingLifecycle.cs` (HordeServer.Compute)


#### class `HordeServer.Agents.Fleet.AwsAutoScalingLifecycleService`  
`public sealed class AwsAutoScalingLifecycleService : IHostedService, IAsyncDisposable`  
_public; L32-437_
- inherits: `IHostedService, IAsyncDisposable`
- desc: Service handling callbacks and lifecycle events triggered by EC2 auto-scaling in AWS
- L38 _public const_ `public const string ActionContinue = "CONTINUE"` — Lifecycle action for continue In the case of terminating instances, setting this result means the instance should *continue* be kept alive
- L44 _public const_ `public const string ActionAbandon = "ABANDON"` — Lifecycle action for abandon In the case of terminating instances, setting this result means the instance should be *terminated*
- L49 _public const_ `public const string OriginWarmPool = "WarmPool"` — Warm pool origin
- L54 _public const_ `public const string OriginAsg = "AutoScalingGroup"` — Normal auto-scaling group origin
- L59 _public property_ `public TimeSpan LifecycleUpdaterInterval { get; }` — How often instance lifecycles for auto-scaling should be updated with AWS
- L61 _private const_ `private const string RedisKey = "aws-asg-lifecycle"`
- L62 _private field_ `private readonly AgentService _agentService`
- L63 _private field_ `private readonly IRedisService _redisService`
- L64 _private field_ `private readonly IAgentCollection _agents`
- L65 _private field_ `private readonly IClock _clock`
- L66 _private field_ `private readonly Tracer _tracer`
- L67 _private field_ `private readonly ILogger<AwsAutoScalingLifecycleService> _logger`
- L68 _private field_ `private readonly ITicker _updateLifecyclesTicker`
- L69 _private field_ `private readonly List<BackgroundTask> _lifecycleEventListenerTasks = new()`
- L70 _private field_ `private readonly string[] _sqsQueueUrls`
- L73 _private field_ `private IAmazonAutoScaling? _awsAutoScaling`
- L74 _private field_ `private IAmazonSQS? _awsSqs`
- L80-107 _public ctor_ `public AwsAutoScalingLifecycleService( AgentService agentService, IRedisService redisService, IAgentCollection agents, IClock clock, IOptionsMonitor<ComputeServerConfig> staticComputeConfig, IServiceProvider serviceProvider, Tracer tracer, ILogger<AwsAutoScalingLifecycleService> logger)` — Constructor
- L109-113 _internal method_ `internal void SetAmazonClientsTesting(IAmazonAutoScaling awsAutoScaling, IAmazonSQS awsSqs)`
- L116-124 _public method_ `public async Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L127-135 _public method_ `public async Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L138-145 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L152-173 _private method_ `private async Task ListenForLifecycleEventsAsync(string sqsQueueUrl, CancellationToken cancellationToken = default)` — Continuously request and receive messages from SQS
- L181-208 _internal method_ `internal async Task ReceiveLifecycleEventsAsync(string sqsQueueUrl, CancellationToken cancellationToken)` — Receive any queued messages from SQS. This is a one-time operation, if more messages are expected, call this method again.
- L210-221 _private method_ `private async Task DeleteMessageAsync(string sqsQueueUrl, Message message, CancellationToken cancellationToken)`
- L223-226 _private method_ `private IAmazonSQS GetSqs()`
- L237-271 _public method_ `public async Task<bool> InitiateTerminationAsync(LifecycleActionEvent e, CancellationToken cancellationToken)` — Gracefully terminate an EC2 instance running the Horde agent This call is initiated by an event coming from AWS auto-scaling group and will request the agent to shutdown. Since the agent can be busy running a job, it's possible it cannot be terminated immediately. The termination request from AWS is therefore tracked and updated continuously as the agent shutdown progresses.
- L281-313 _public method_ `public async Task<List<string>> GetInstancesAvailableForTerminationAsync(TerminationPolicyEvent e, CancellationToken cancellationToken)` — Get instances available for termination. An AWS Lambda function is set to handle termination policy queries from an auto-scaling group That function is configured to call Horde server and invoke this method
- L315-322 _private method_ `private async Task TrackAgentLifecycleAsync(AgentId agentId, LifecycleActionEvent e, CancellationToken cancellationToken)`
- L324-348 _private method_ `private async Task SendCompleteLifecycleActionAsync(LifecycleActionEvent laEvent, ActionResult result, CancellationToken cancellationToken)`
- L357-408 _internal method_ `internal async ValueTask UpdateLifecyclesAsync(CancellationToken cancellationToken)` — Update AWS auto-scaling on the lifecycle status for each agent being tracked for shutdown. This ensures the EC2 instance is not released for termination until it gracefully finished any outstanding work. That is, the agent status is set to stopped in Horde server.

#### class `HordeServer.Agents.Fleet.AwsAutoScalingLifecycleService.AgentLifecycleInfo`  
`private class AgentLifecycleInfo`  
_private; L413-427_
- desc: Class for agent lifecycle state. Serialized and stored in Redis.
- L415 _public property_ `public string AgentId { get; set; }`
- L416 _public property_ `public DateTime CreatedAt { get; set; }`
- L417 _public property_ `public DateTime UpdatedAt { get; set; }`
- L418 _public property_ `public LifecycleActionEvent Event { get; set; }`
- L420-426 _public ctor_ `public AgentLifecycleInfo(string agentId, DateTime createdAt, DateTime updatedAt, LifecycleActionEvent @event)`

#### enum `HordeServer.Agents.Fleet.AwsAutoScalingLifecycleService.ActionResult`  
`private enum ActionResult`  
_private; L429-436_
- L432 _public* enumerator_ `Continue` — (inheritdoc)
- L435 _public* enumerator_ `Abandon` — (inheritdoc)

#### class `HordeServer.Agents.Fleet.AwsAutoScalingLifecycleController`  
`public class AwsAutoScalingLifecycleController : HordeControllerBase`  
_public; L445-472_
- attrs: `[ApiController] [Authorize] [Route("[controller]")]`
- inherits: `HordeControllerBase`
- desc: Controller handling callbacks for AWS auto-scaling
- L447 _private field_ `private readonly AwsAutoScalingLifecycleService _lifecycleService`
- L452-455 _public ctor_ `public AwsAutoScalingLifecycleController(AwsAutoScalingLifecycleService lifecycleService)` — Constructor
- L467-471 _public method_ `public async Task<ActionResult> TerminationPolicyAsync([FromBody] TerminationPolicyEvent tpe, CancellationToken cancellationToken)` — attrs: `[HttpPost] [Route("/api/v1/aws/asg-termination-policy")] [ProducesResponseType(StatusCodes.Status200OK)]` — Called by AWS auto-scaling group to get which instance IDs are valid for termination AwsAutoScalingLifecycleService.GetInstancesAvailableForTerminationAsync

#### class `HordeServer.Agents.Fleet.LifecycleActionEvent`  
`public class LifecycleActionEvent`  
_public; L478-509_
- desc: Lifecycle action event from AWS auto-scaling group The property names are explicitly set to highlight these are not controlled by Horde but sent from AWS API.
- L483 _public property_ `public string LifecycleHookName { get; set; }` — attrs: `[JsonPropertyName("LifecycleHookName")]` — Name of the lifecycle hook
- L488 _public property_ `public string LifecycleActionToken { get; set; }` — attrs: `[JsonPropertyName("LifecycleActionToken")]` — Token for the lifecycle action
- L493 _public property_ `public string LifecycleTransition { get; set; }` — attrs: `[JsonPropertyName("LifecycleTransition")]` — Lifecycle transition (e.g EC2_INSTANCE_LAUNCHING, EC2_INSTANCE_TERMINATING)
- L498 _public property_ `public string AutoScalingGroupName { get; set; }` — attrs: `[JsonPropertyName("AutoScalingGroupName")]` — Name of the auto-scaling group being handled
- L503 _public property_ `public string Ec2InstanceId { get; set; }` — attrs: `[JsonPropertyName("EC2InstanceId")]` — Instance ID
- L508 _public property_ `public string Origin { get; set; }` — attrs: `[JsonPropertyName("Origin")]` — Origin of the instance (e.g an agent in service or in a warm pool)

#### class `HordeServer.Agents.Fleet.TerminationPolicyInstance`  
`public class TerminationPolicyInstance`  
_public; L514-575_
- desc: Instance referenced by TerminationPolicyEvent
- L519 _public property_ `public string AvailabilityZone { get; set; }` — attrs: `[JsonPropertyName("AvailabilityZone")]` — Availability zone of the instance (such as 'us-east-1c')
- L524 _public property_ `public int? Capacity { get; set; }` — attrs: `[JsonPropertyName("Capacity")]` — Capacity to terminate (number of instances)
- L529 _public property_ `public string? InstanceId { get; set; }` — attrs: `[JsonPropertyName("InstanceId")]` — Instance ID (such as 'i-123456789')
- L534 _public property_ `public string? InstanceType { get; set; }` — attrs: `[JsonPropertyName("InstanceType")]` — Instance type (such as 'm5.xlarge')
- L539 _public property_ `public string InstanceMarketOption { get; set; }` — attrs: `[JsonPropertyName("InstanceMarketOption")]` — Instance market options (such as 'on-demand' or 'spot')
- L544-546 _public ctor_ `public TerminationPolicyInstance()` — Constructor
- L554-559 _public ctor_ `public TerminationPolicyInstance(int capacity, string availabilityZone = "us-east-1a", string instanceMarketOption = "on-demand")` — Constructor
- L568-574 _public ctor_ `public TerminationPolicyInstance(string instanceId, string availabilityZone = "us-east-1a", string instanceType = "m5.large", string instanceMarketOption = "on-demand")` — Constructor

#### class `HordeServer.Agents.Fleet.TerminationPolicyEvent`  
`public class TerminationPolicyEvent`  
_public; L581-607_
- desc: Termination policy event from AWS auto-scaling group The property names are explicitly set to highlight these are not controlled by Horde but sent from AWS API.
- L586 _public property_ `public string AutoScalingGroupArn { get; set; }` — attrs: `[JsonPropertyName("AutoScalingGroupARN")]` — ARN of the auto-scaling group
- L591 _public property_ `public string AutoScalingGroupName { get; set; }` — attrs: `[JsonPropertyName("AutoScalingGroupName")]` — Name of the auto-scaling group
- L596 _public property_ `public List<TerminationPolicyInstance> CapacityToTerminate { get; set; }` — attrs: `[JsonPropertyName("CapacityToTerminate")]` — Capacity that's been requested to be terminated
- L601 _public property_ `public List<TerminationPolicyInstance> Instances { get; set; }` — attrs: `[JsonPropertyName("Instances")]` — Instances available to terminate
- L606 _public property_ `public string Cause { get; set; }` — attrs: `[JsonPropertyName("Cause")]` — Cause of the termination (such as 'SCALE_IN' or 'INSTANCE_REFRESH')

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Fleet/ComputeQueueAwsMetricStrategy.cs` (HordeServer.Compute)


#### class `HordeServer.Agents.Fleet.ComputeQueueAwsMetricSettings`  
`public class ComputeQueueAwsMetricSettings`  
_public; L20-50_
- desc: Settings for ComputeQueueAwsMetricStrategy
- L25 _public property_ `public string ComputeClusterId { get; set; }` — Compute cluster ID to observe
- L30 _public property_ `public string Namespace { get; set; }` — AWS CloudWatch namespace to write metrics in
- L36-38 _public ctor_ `public ComputeQueueAwsMetricSettings()` — attrs: `[JsonConstructor]` — Constructor used for JSON serialization
- L45-49 _public ctor_ `public ComputeQueueAwsMetricSettings(string computeClusterId, string cloudWatchNamespace = "Horde")` — Constructor

#### class `HordeServer.Agents.Fleet.ComputeServiceExtensions`  
`static class ComputeServiceExtensions`  
_internal*; L52-60_
- L54-59 _public method_ `public static Task<int> GetNumQueuedTasksForPoolAsync(this ComputeTaskSource computeTaskSource, ClusterId clusterId, IPoolConfig pool)`

#### class `HordeServer.Agents.Fleet.ComputeQueueAwsMetricStrategy`  
`public class ComputeQueueAwsMetricStrategy : IPoolSizeStrategy`  
_public; L66-154_
- inherits: `IPoolSizeStrategy`
- desc: A no-op strategy that reports size of compute task queue for a given pool as AWS CloudWatch metrics A metric that later can be used as a source for AWS-controlled auto-scaling policies.
- L68 _private field_ `private readonly IAmazonCloudWatch _cloudWatch`
- L69 _private field_ `private readonly ComputeTaskSource _computeTaskSource`
- L70 _private field_ `private readonly ComputeQueueAwsMetricSettings _settings`
- L71 _private field_ `private readonly ILogger<ComputeQueueAwsMetricStrategy> _logger`
- L80-87 _public ctor_ `public ComputeQueueAwsMetricStrategy(IAmazonCloudWatch cloudWatch, ComputeTaskSource computeTaskSource, ComputeQueueAwsMetricSettings settings, ILogger<ComputeQueueAwsMetricStrategy> logger)` — Constructor
- L90 _public property_ `public string Name { get; }` — (inheritdoc)
- L93-153 _public method_ `public async Task<PoolSizeResult> CalculatePoolSizeAsync(IPoolConfig pool, List<IAgent> agents, CancellationToken cancellationToken)` — (inheritdoc)

#### class `HordeServer.Agents.Fleet.ComputeQueueAwsMetricStrategyFactory`  
`public class ComputeQueueAwsMetricStrategyFactory : PoolSizeStrategyFactory<ComputeQueueAwsMetricSettings>`  
_public; L159-179_
- inherits: `PoolSizeStrategyFactory<ComputeQueueAwsMetricSettings>`
- desc: Factory for LeaseUtilizationStrategy
- L161 _private* field_ `readonly IAmazonCloudWatch _cloudWatch`
- L162 _private* field_ `readonly ComputeTaskSource _computeTaskSource`
- L163 _private* field_ `readonly ILogger<ComputeQueueAwsMetricStrategy> _logger`
- L168-174 _public ctor_ `public ComputeQueueAwsMetricStrategyFactory(IAmazonCloudWatch cloudWatch, ComputeTaskSource computeTaskSource, ILogger<ComputeQueueAwsMetricStrategy> logger) : base(PoolSizeStrategy.ComputeQueueAwsMetric)` — Constructor
- L177 _public method_ `public override IPoolSizeStrategy Create(ComputeQueueAwsMetricSettings settings)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Fleet/FleetManagerFactory.cs` (HordeServer.Compute)


#### interface `HordeServer.Agents.Fleet.IFleetManagerFactory`  
`public interface IFleetManagerFactory`  
_public; L22-32_
- desc: Interface for fleet manager factory
- L31 _public method_ `public IFleetManager CreateFleetManager(FleetManagerType type, JsonObject? config = null)` — Create a fleet manager

#### class `HordeServer.Agents.Fleet.FleetManagerFactory`  
`public sealed class FleetManagerFactory : IFleetManagerFactory`  
_public; L37-138_
- inherits: `IFleetManagerFactory`
- desc: Factory creating instances of fleet managers
- L39 _private field_ `private readonly IAgentCollection _agentCollection`
- L40 _private field_ `private readonly IClock _clock`
- L41 _private field_ `private readonly Meter _meter`
- L42 _private field_ `private readonly IServiceProvider _provider`
- L43 _private field_ `private readonly IOptionsMonitor<ComputeServerConfig> _staticComputeConfig`
- L44 _private field_ `private readonly Tracer _tracer`
- L45 _private field_ `private readonly ILoggerFactory _loggerFactory`
- L47 _private field_ `private IAmazonAutoScaling? _awsAutoScaling`
- L48 _private field_ `private IAmazonEC2? _awsEc2`
- L53-62 _public ctor_ `public FleetManagerFactory(IAgentCollection agentCollection, IClock clock, Meter meter, IServiceProvider provider, IOptionsMonitor<ComputeServerConfig> staticComputeConfig, Tracer tracer, ILoggerFactory loggerFactory)` — Constructor
- L65-83 _public method_ `public IFleetManager CreateFleetManager(FleetManagerType type, JsonObject? config)` — (inheritdoc)
- L85-105 _private method_ `private static T DeserializeSettings<T>(JsonObject? config)`
- L107-121 _private method_ `private IAmazonEC2 GetAwsEc2(FleetManagerType type)`
- L123-137 _private method_ `private IAmazonAutoScaling GetAwsAutoScaling(FleetManagerType type)`

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Fleet/FleetService.cs` (HordeServer.Compute)


#### class `HordeServer.Agents.Fleet.PoolWithAgents`  
`public class PoolWithAgents`  
_public; L22-44_
- desc: Parameters required for calculating pool size
- L27 _public property_ `public IPoolConfig Pool { get; }` — Pool being resized
- L32 _public property_ `public List<IAgent> Agents { get; }` — All agents currently associated with the pool
- L39-43 _public ctor_ `public PoolWithAgents(IPoolConfig pool, List<IAgent> agents)` — Constructor

#### class `HordeServer.Agents.Fleet.FleetService`  
`public sealed class FleetService : IHostedService, IAsyncDisposable`  
_public; L49-448_
- inherits: `IHostedService, IAsyncDisposable`
- desc: Service for managing the autoscaling of agent pools
- L54 _private const_ `private const int MaxParallelTasks = 10` — Max number of auto-scaling calculations to be done concurrently (sizing calculations and fleet manager calls)
- L56 _private field_ `private readonly AgentService _agentService`
- L57 _private field_ `private readonly IPoolCollection _poolCollection`
- L58 _private field_ `private readonly IDowntimeService _downtimeService`
- L59 _private field_ `private readonly IFleetManagerFactory _fleetManagerFactory`
- L60 _private field_ `private readonly IClock _clock`
- L61 _private field_ `private readonly IEnumerable<IPoolSizeStrategyFactory> _poolSizeStrategyFactories`
- L62 _private field_ `private readonly ITicker _ticker`
- L63 _private field_ `private readonly ITicker _tickerHighFrequency`
- L64 _private field_ `private readonly TimeSpan _defaultScaleOutCooldown`
- L65 _private field_ `private readonly TimeSpan _defaultScaleInCooldown`
- L66 _private field_ `private readonly IOptions<ComputeServerConfig> _staticComputeConfig`
- L67 _private field_ `private readonly Tracer _tracer`
- L68 _private field_ `private readonly ILogger<FleetService> _logger`
- L73-102 _public ctor_ `public FleetService( AgentService agentService, IPoolCollection poolCollection, IDowntimeService downtimeService, IFleetManagerFactory fleetManagerFactory, IClock clock, IEnumerable<IPoolSizeStrategyFactory> poolSizeStrategyFactories, IOptions<ComputeServerConfig> staticComputeConfig, Tracer tracer, ILogger<FleetService> logger)` — Constructor
- L105-108 _public method_ `public Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L111-114 _public method_ `public Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L117-121 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L123-148 _internal method_ `internal async ValueTask TickLeaderAsync(CancellationToken cancellationToken)`
- L150-162 _internal method_ `internal async ValueTask TickHighFrequencyAsync(CancellationToken stoppingToken)`
- L164-169 _internal method_ `internal async Task CalculateSizeAndScaleAsync(IPoolConfig pool, List<IAgent> agents, CancellationToken cancellationToken)`
- L171-180 _internal method_ `internal async Task<List<PoolWithAgents>> GetPoolsWithAgentsAsync(CancellationToken cancellationToken = default)`
- L182-303 _internal method_ `internal async Task<ScaleResult> ScalePoolAsync(IPoolConfig poolConfig, List<IAgent> agents, PoolSizeResult poolSizeResult, CancellationToken cancellationToken)`
- L305-321 _internal method_ `internal IEnumerable<string> GetPropValues(string name)`
- L329-343 _public method_ `public IFleetManager CreateFleetManager(IPool pool)` — Instantiate a fleet manager using the list of conditions/configs in IPool
- L352-401 _public method_ `public IPoolSizeStrategy CreatePoolSizeStrategy(IPoolConfig pool)` — Instantiate a sizing strategy for the given pool Can resolve either from the list of strategies or the old legacy way
- L413-431 _private method_ `private async Task<int> CancelPendingShutdownsAsync(IPool pool, int count, CancellationToken cancellationToken)` — Cancel a number of pending agent shutdowns for a pool By preventing a shutdown, the agent can immediately be put back to service without requiring the provisioning of a new one
- L433-447 _private method_ `private async Task<ScaleResult> ExpandWithPendingShutdownsFirstAsync(IPool pool, int agentsToAdd, Func<int, Task<ScaleResult>> scaleOutFunc, CancellationToken cancellationToken)`

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Fleet/IFleetManager.cs` (HordeServer.Compute)


#### enum `HordeServer.Agents.Fleet.FleetManagerType`  
`public enum FleetManagerType`  
_public; L10-41_
- desc: Available fleet managers
- L15 _public* enumerator_ `Default` — Default fleet manager
- L20 _public* enumerator_ `NoOp` — No-op fleet manager.
- L25 _public* enumerator_ `Aws` — Fleet manager for handling AWS EC2 instances. Will create and/or terminate instances from scratch.
- L30 _public* enumerator_ `AwsReuse` — Fleet manager for handling AWS EC2 instances. Will start already existing but stopped instances to reuse existing EBS disks.
- L35 _public* enumerator_ `AwsRecycle` — Fleet manager for handling AWS EC2 instances. Will start already existing but stopped instances to reuse existing EBS disks.
- L40 _public* enumerator_ `AwsAsg` — Fleet manager for handling AWS EC2 instances. Uses an EC2 auto-scaling group for controlling the number of running instances.

#### enum `HordeServer.Agents.Fleet.FleetManagerOutcome`  
`public enum FleetManagerOutcome`  
_public; L46-67_
- desc: Outcome of a scaling operation
- L51 _public* enumerator_ `Success` — Scaling operation completed as intended.
- L56 _public* enumerator_ `PartialSuccess` — Scaling operation was only partly fulfilled.
- L61 _public* enumerator_ `Failure` — Scaling operation failed
- L66 _public* enumerator_ `NoOp` — No operation took place (disabled or skipped)

#### class `HordeServer.Agents.Fleet.ScaleResult`  
`public class ScaleResult`  
_public; L72-144_
- desc: Result from a scaling operation
- L77 _public property_ `public FleetManagerOutcome Outcome { get; }` — Outcome
- L82 _public property_ `public int AgentsAddedCount { get; }` — Agents added as part of operation
- L87 _public property_ `public int AgentsRemovedCount { get; }` — Agents added as part of operation
- L92 _public property_ `public string Message { get; }` — Human-readable log message
- L101-107 _public ctor_ `public ScaleResult(FleetManagerOutcome outcome, int agentsAddedCount, int agentsRemovedCount, string message = "")` — Constructor
- L110-113 _protected method_ `protected bool Equals(ScaleResult other)` — (inheritdoc)
- L116-131 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L134-137 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L140-143 _public method_ `public override string ToString()` — (inheritdoc)

#### interface `HordeServer.Agents.Fleet.IFleetManager`  
`public interface IFleetManager`  
_public; L149-178_
- desc: Service to manage a fleet of machines
- L159 _public* method_ `Task<ScaleResult> ExpandPoolAsync(IPool pool, IReadOnlyList<IAgent> agents, int count, CancellationToken cancellationToken = default)` — Expand the given pool
- L169 _public* method_ `Task<ScaleResult> ShrinkPoolAsync(IPool pool, IReadOnlyList<IAgent> agents, int count, CancellationToken cancellationToken = default)` — Shrink the given pool
- L177 _public* method_ `Task<int> GetNumStoppedInstancesAsync(IPoolConfig pool, CancellationToken cancellationToken = default)` — Returns the number of stopped instances in the given pool

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Fleet/IPoolSizeStrategy.cs` (HordeServer.Compute)


#### enum `HordeServer.Agents.Fleet.PoolSizeStrategy`  
`public enum PoolSizeStrategy`  
_public; L12-42_
- desc: Available pool sizing strategies
- L18 _public* enumerator_ `LeaseUtilization` — Strategy based on lease utilization LeaseUtilizationStrategy
- L23 _public* enumerator_ `JobQueue` — Strategy based on size of job build queue
- L29 _public* enumerator_ `NoOp` — No-op strategy used as fallback/default behavior NoOpPoolSizeStrategy
- L35 _public* enumerator_ `ComputeQueueAwsMetric` — A no-op strategy that reports metrics to let an external AWS auto-scaling policy scale the fleet ComputeQueueAwsMetric
- L41 _public* enumerator_ `LeaseUtilizationAwsMetric` — A no-op strategy that reports metrics to let an external AWS auto-scaling policy scale the fleet LeaseUtilizationAwsMetric

#### class `HordeServer.Agents.Fleet.PoolSizeStrategyExtensions`  
`public static class PoolSizeStrategyExtensions`  
_public; L47-62_
- desc: Extensions for pool size strategy
- L54-61 _public method_ `public static bool SupportsHighFrequency(this PoolSizeStrategy strategy)` — Checks whether the strategy can be called more often than normal (i.e it's cheap to run)

#### class `HordeServer.Agents.Fleet.PoolSizeResult`  
`public class PoolSizeResult`  
_public; L67-96_
- desc: Result from calculating pool size
- L72 _public property_ `public int CurrentAgentCount { get; }` — The agent count as it appeared when pool sizing was calculated
- L77 _public property_ `public int DesiredAgentCount { get; }` — The desired agent count as calculated by pool sizing strategy
- L82 _public property_ `public IReadOnlyDictionary<string, object>? Status { get; }` — Log-friendly metadata object describing the output of the size calculation through key/values
- L90-95 _public ctor_ `public PoolSizeResult(int currentAgentCount, int desiredAgentCount, IReadOnlyDictionary<string, object>? status = null)` — Constructor

#### interface `HordeServer.Agents.Fleet.IPoolSizeStrategy`  
`public interface IPoolSizeStrategy`  
_public; L101-116_
- desc: Interface for different agent pool sizing strategies
- L110 _public* method_ `Task<PoolSizeResult> CalculatePoolSizeAsync(IPoolConfig pool, List<IAgent> agents, CancellationToken cancellationToken = default)` — Calculate the adequate number of agents to be online for given pools
- L115 _public* property_ `string Name { get; }` — Name of the strategy

#### interface `HordeServer.Agents.Fleet.IPoolSizeStrategyFactory`  
`public interface IPoolSizeStrategyFactory`  
_public; L121-132_
- desc: Factory for creating IPoolSizeStrategy instances
- L126 _public* property_ `PoolSizeStrategy Type { get; }` — Strategy type
- L131 _public* method_ `IPoolSizeStrategy Create(JsonObject config)` — Create a new IPoolSizeStrategy instance from the given configuration

#### class `HordeServer.Agents.Fleet.PoolSizeStrategyFactory`  
`public abstract class PoolSizeStrategyFactory<TConfig> : IPoolSizeStrategyFactory where TConfig : new()`  
_public; L137-166_
- inherits: `IPoolSizeStrategyFactory`
- constraints: `where TConfig : new()`
- desc: Base implementation of IPoolSizeStrategyFactory which deserializes options into a concrete settings type
- L140 _public property_ `public PoolSizeStrategy Type { get; }` — (inheritdoc)
- L145 _protected ctor_ `protected PoolSizeStrategyFactory(PoolSizeStrategy type)` — Constructor
- L149 _public method_ `public IPoolSizeStrategy Create(JsonObject? config)` — (inheritdoc)
- L155 _public method_ `public abstract IPoolSizeStrategy Create(TConfig config)` — Creates a new strategy object from the given config
- L157-165 _private method_ `private static T DeserializeConfig<T>(JsonObject? json)`

#### class `HordeServer.Agents.Fleet.NoOpPoolSizeStrategy`  
`public class NoOpPoolSizeStrategy : IPoolSizeStrategy`  
_public; L172-182_
- inherits: `IPoolSizeStrategy`
- desc: No-operation strategy that won't resize pools, just return the existing count. Used to ensure there's always a strategy available for dependency injection, even if it does nothing.
- L175-178 _public method_ `public Task<PoolSizeResult> CalculatePoolSizeAsync(IPoolConfig pool, List<IAgent> agents, CancellationToken cancellationToken)` — (inheritdoc)
- L181 _public property_ `public string Name { get; }` — (inheritdoc)

#### class `HordeServer.Agents.Fleet.NoOpPoolSizeStrategyFactory`  
`class NoOpPoolSizeStrategyFactory : IPoolSizeStrategyFactory`  
_internal*; L184-190_
- inherits: `IPoolSizeStrategyFactory`
- L186 _public property_ `public PoolSizeStrategy Type => ...`
- L188 _public method_ `public IPoolSizeStrategy Create(JsonObject? config)`

#### class `HordeServer.Agents.Fleet.ExtraAgentCountStrategy`  
`public class ExtraAgentCountStrategy : IPoolSizeStrategy`  
_public; L196-221_
- inherits: `IPoolSizeStrategy`
- desc: Pool size strategy wrapping a normal strategy and applies an extra agent count to the desired agent count.
- L198 _private field_ `private readonly IPoolSizeStrategy _backingStrategy`
- L199 _private field_ `private readonly int _extraAgentCount`
- L206-210 _public ctor_ `public ExtraAgentCountStrategy(IPoolSizeStrategy backingStrategy, int extraAgentCount)` — Constructor
- L213-217 _public method_ `public async Task<PoolSizeResult> CalculatePoolSizeAsync(IPoolConfig pool, List<IAgent> agents, CancellationToken cancellationToken)` — (inheritdoc)
- L220 _public property_ `public string Name => ...` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Fleet/JobQueueSettings.cs` (HordeServer.Compute)


#### class `HordeServer.Agents.Fleet.JobQueueSettings`  
`public class JobQueueSettings`  
_public; L11-69_
- desc: Job queue sizing settings for a pool
- L18 _public property_ `public double ScaleOutFactor { get; set; }` — Factor translating queue size to additional agents to grow the pool with The result is always rounded up to nearest integer. Example: if there are 20 jobs in queue, a factor 0.25 will result in 5 new agents being added (20 * 0.25)
- L25 _public property_ `public double ScaleInFactor { get; set; }` — Factor by which to shrink the pool size with when queue is empty The result is always rounded up to nearest integer. Example: when the queue size is zero, a default value of 0.9 will shrink the pool by 10% (current agent count * 0.9)
- L30 _public property_ `public int SamplePeriodMin { get; set; }` — How far back in time to look for job batches (that potentially are in the queue)
- L38 _public property_ `public int ReadyTimeThresholdSec { get; set; }` — Time spent in ready state before considered truly waiting for an agent A job batch can be in ready state before getting picked up and executed. This threshold will help ensure only batches that have been waiting longer than this value will be considered.
- L44-46 _public ctor_ `public JobQueueSettings()` — attrs: `[JsonConstructor]` — Constructor used for JSON serialization
- L53-57 _public ctor_ `public JobQueueSettings(double? scaleOutFactor = null, double? scaleInFactor = null)` — Constructor
- L60-68 _public method_ `public override string ToString()` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Fleet/LeaseUtilizationAwsMetricStrategy.cs` (HordeServer.Compute)


#### class `HordeServer.Agents.Fleet.LeaseUtilizationAwsMetricSettings`  
`public class LeaseUtilizationAwsMetricSettings`  
_public; L19-50_
- desc: Settings for LeaseUtilizationAwsMetricStrategy
- L25 _public property_ `public int SamplePeriodSec { get; set; }` — Time window backwards in time to sample for active leases A value of 60 sec, will query for active leases the last minute.
- L30 _public property_ `public string CloudWatchNamespace { get; set; }` — AWS CloudWatch namespace to write metrics in
- L36-38 _public ctor_ `public LeaseUtilizationAwsMetricSettings()` — attrs: `[JsonConstructor]` — Constructor used for JSON serialization
- L45-49 _public ctor_ `public LeaseUtilizationAwsMetricSettings(int samplePeriodSec, string cloudWatchNamespace)` — Constructor

#### class `HordeServer.Agents.Fleet.LeaseUtilizationAwsMetricStrategy`  
`public class LeaseUtilizationAwsMetricStrategy : IPoolSizeStrategy`  
_public; L56-134_
- inherits: `IPoolSizeStrategy`
- desc: A no-op strategy that reports lease utilization for a given pool as AWS CloudWatch metrics A metric that later can be used as a source for AWS-controlled auto-scaling policies.
- L58 _internal property_ `internal LeaseUtilizationAwsMetricSettings Settings { get; }`
- L60 _private field_ `private readonly ILeaseCollection _leaseCollection`
- L61 _private field_ `private readonly IAmazonCloudWatch _cloudWatch`
- L62 _private field_ `private readonly IClock _clock`
- L63 _private field_ `private readonly ILogger<LeaseUtilizationAwsMetricStrategy> _logger`
- L73-80 _public ctor_ `public LeaseUtilizationAwsMetricStrategy(ILeaseCollection leaseCollection, IAmazonCloudWatch cloudWatch, LeaseUtilizationAwsMetricSettings settings, IClock clock, ILogger<LeaseUtilizationAwsMetricStrategy> logger)` — Constructor
- L83 _public property_ `public string Name { get; }` — (inheritdoc)
- L86-133 _public method_ `public async Task<PoolSizeResult> CalculatePoolSizeAsync(IPoolConfig pool, List<IAgent> agents, CancellationToken cancellationToken = default)` — (inheritdoc)

#### class `HordeServer.Agents.Fleet.LeaseUtilizationAwsMetricStrategyFactory`  
`public class LeaseUtilizationAwsMetricStrategyFactory : PoolSizeStrategyFactory<LeaseUtilizationAwsMetricSettings>`  
_public; L139-161_
- inherits: `PoolSizeStrategyFactory<LeaseUtilizationAwsMetricSettings>`
- desc: Factory for LeaseUtilizationAwsMetricStrategy
- L141 _private* field_ `readonly ILeaseCollection _leaseCollection`
- L142 _private* field_ `readonly IAmazonCloudWatch _cloudWatch`
- L143 _private* field_ `readonly IClock _clock`
- L144 _private* field_ `readonly ILogger<LeaseUtilizationAwsMetricStrategy> _logger`
- L149-156 _public ctor_ `public LeaseUtilizationAwsMetricStrategyFactory(ILeaseCollection leaseCollection, IAmazonCloudWatch cloudWatch, IClock clock, ILogger<LeaseUtilizationAwsMetricStrategy> logger) : base(PoolSizeStrategy.LeaseUtilizationAwsMetric)` — Constructor
- L159 _public method_ `public override IPoolSizeStrategy Create(LeaseUtilizationAwsMetricSettings settings)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Fleet/LeaseUtilizationStrategy.cs` (HordeServer.Compute)


#### class `HordeServer.Agents.Fleet.LeaseUtilizationSettings`  
`public class LeaseUtilizationSettings`  
_public; L20-58_
- desc: Lease utilization sizing settings for a pool
- L25 _public property_ `public int SampleTimeSec { get; set; }` — Time period for each sample
- L30 _public property_ `public int NumSamples { get; set; }` — Number of samples to collect for calculating lease utilization
- L35 _public property_ `public int NumSamplesForResult { get; set; }` — Min number of samples for a valid result
- L40 _public property_ `public int MinAgents { get; set; }` — The minimum number of agents to keep in the pool
- L45 _public property_ `public int NumReserveAgents { get; set; }` — The minimum number of idle agents to hold in reserve
- L48-57 _public method_ `public override string ToString()` — (inheritdoc)

#### class `HordeServer.Agents.Fleet.LeaseUtilizationStrategy`  
`public class LeaseUtilizationStrategy : IPoolSizeStrategy`  
_public; L63-285_
- inherits: `IPoolSizeStrategy`
- desc: Calculate pool size by looking at previously finished leases
- L65 _private const_ `private const string CacheKey = nameof(LeaseUtilizationStrategy)`
- L123 _internal property_ `internal LeaseUtilizationSettings Settings { get; }`
- L125 _private field_ `private readonly AgentService _agentService`
- L126 _private field_ `private readonly IPoolCollection _poolCollection`
- L127 _private field_ `private readonly ILeaseCollection _leaseCollection`
- L128 _private field_ `private readonly IClock _clock`
- L129 _private field_ `private readonly IMemoryCache _cache`
- L140-148 _public ctor_ `public LeaseUtilizationStrategy(AgentService agentService, IPoolCollection poolCollection, ILeaseCollection leaseCollection, IClock clock, IMemoryCache cache, LeaseUtilizationSettings settings)` — Constructor
- L150-197 _private method_ `private async Task<Dictionary<AgentId, AgentData>> GetAgentDataAsync(CancellationToken cancellationToken)`
- L199-224 _private method_ `private async Task<Dictionary<PoolId, PoolData>> GetPoolDataAsync(CancellationToken cancellationToken)`
- L227 _public property_ `public string Name { get; }` — (inheritdoc)
- L230-273 _public method_ `public async Task<PoolSizeResult> CalculatePoolSizeAsync(IPoolConfig pool, List<IAgent> agents, CancellationToken cancellationToken)` — (inheritdoc)
- L280-284 _private method_ `private static string GetDensityMap(IEnumerable<double> values)` — Creates a string of characters indicating a sequence of 0-1 values over time

#### struct `HordeServer.Agents.Fleet.LeaseUtilizationStrategy.UtilizationSample`  
`struct UtilizationSample`  
_private*; L67-71_
- L69 _public field_ `public double _jobWork`
- L70 _public field_ `public double _otherWork`

#### class `HordeServer.Agents.Fleet.LeaseUtilizationStrategy.AgentData`  
`class AgentData`  
_private*; L73-98_
- L75 _public property_ `public IAgent Agent { get; }`
- L76 _public property_ `public UtilizationSample[] Samples { get; }`
- L77 _public property_ `public List<ILease> Leases { get; }`
- L78 _private field_ `private readonly int _numSamples`
- L80-85 _public ctor_ `public AgentData(IAgent agent, int numSamples)`
- L87-97 _public method_ `public void Add(double minT, double maxT, double jobWork, double otherWork)`

#### class `HordeServer.Agents.Fleet.LeaseUtilizationStrategy.PoolData`  
`class PoolData`  
_private*; L100-121_
- L102 _public property_ `public IPoolConfig Pool { get; }`
- L103 _public property_ `public List<IAgent> Agents { get; }`
- L104 _public property_ `public UtilizationSample[] Samples { get; }`
- L106-110 _public ctor_ `public PoolData(IPoolConfig pool, int numSamples)`
- L112-120 _public method_ `public void Add(AgentData agentData)`

#### class `HordeServer.Agents.Fleet.LeaseUtilizationStrategyFactory`  
`public class LeaseUtilizationStrategyFactory : PoolSizeStrategyFactory<LeaseUtilizationSettings>`  
_public; L290-314_
- inherits: `PoolSizeStrategyFactory<LeaseUtilizationSettings>`
- desc: Factory for LeaseUtilizationStrategy
- L292 _private* field_ `readonly AgentService _agentService`
- L293 _private* field_ `readonly IPoolCollection _poolCollection`
- L294 _private* field_ `readonly ILeaseCollection _leaseCollection`
- L295 _private* field_ `readonly IClock _clock`
- L296 _private* field_ `readonly IMemoryCache _memoryCache`
- L301-309 _public ctor_ `public LeaseUtilizationStrategyFactory(AgentService agentService, IPoolCollection poolCollection, ILeaseCollection leaseCollection, IClock clock, IMemoryCache memoryCache) : base(PoolSizeStrategy.LeaseUtilization)` — Constructor
- L312 _public method_ `public override IPoolSizeStrategy Create(LeaseUtilizationSettings settings)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Fleet/Providers/AwsAsgFleetManager.cs` (HordeServer.Compute)


#### class `HordeServer.Agents.Fleet.Providers.AwsAsgSettings`  
`public class AwsAsgSettings`  
_public; L17-34_
- desc: Settings for controlling an EC2 auto-scaling group (ASG)
- L22 _public property_ `public string Name { get; }` — Name of the auto-scaling group
- L29-33 _public ctor_ `public AwsAsgSettings(string? name)` — attrs: `[JsonConstructor]` — Constructor

#### class `HordeServer.Agents.Fleet.Providers.AwsAsgFleetManager`  
`public sealed class AwsAsgFleetManager : IFleetManager`  
_public; L40-105_
- inherits: `IFleetManager`
- desc: Fleet manager for handling AWS EC2 instances Uses an EC2 auto-scaling group for controlling the number of running instances.
- L42 _internal property_ `internal AwsAsgSettings Settings { get; }`
- L43 _private field_ `private readonly IAmazonAutoScaling _awsAutoScaling`
- L44 _private field_ `private readonly Tracer _tracer`
- L45 _private field_ `private readonly ILogger _logger`
- L50-56 _public ctor_ `public AwsAsgFleetManager(IAmazonAutoScaling awsAutoScaling, AwsAsgSettings asgSettings, Tracer tracer, ILogger<AwsAsgFleetManager> logger)` — Constructor
- L59-71 _public method_ `public async Task<ScaleResult> ExpandPoolAsync(IPool pool, IReadOnlyList<IAgent> agents, int count, CancellationToken cancellationToken)` — (inheritdoc)
- L74-86 _public method_ `public async Task<ScaleResult> ShrinkPoolAsync(IPool pool, IReadOnlyList<IAgent> agents, int count, CancellationToken cancellationToken)` — (inheritdoc)
- L88-98 _private method_ `private async Task UpdateAsgAsync(PoolId poolId, int desiredCapacity, TelemetrySpan span, CancellationToken cancellationToken)`
- L101-104 _public method_ `public Task<int> GetNumStoppedInstancesAsync(IPoolConfig pool, CancellationToken cancellationToken)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Fleet/Providers/AwsFleetManager.cs` (HordeServer.Compute)


#### class `HordeServer.Agents.Fleet.Providers.AwsFleetManagerSettings`  
`public class AwsFleetManagerSettings`  
_public; L17-117_
- desc: Settings for the AWS fleet manager
- L22 _public property_ `public string Region { get; }` — AWS region (e.g us-east-1)
- L27 _public property_ `public string ImageId { get; }` — Amazon Machine Image (AMI) to use (e.g ami-0c2e245e4936a2ab2)
- L32 _public property_ `public string InstanceType { get; }` — An EC2 instance type (see https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/instance-types.html for full list)
- L37 _public property_ `public string? IamInstanceProfile { get; }` — IAM instance profile
- L42 _public property_ `public IReadOnlyDictionary<string, string> Tags { get; }` — Key/value tags for the instance
- L48 _public property_ `public List<string> SubnetIds { get; }` — List of subnet IDs this instance can run in. Will implicitly pick the VPC. A random subnet ID will be picked during instance creation.
- L53 _public property_ `public List<string> SecurityGroupIds { get; }` — Security group IDs to apply. Must exist in the same VPC as the subnets.
- L58 _public property_ `public string? UserData { get; }` — User data to pass to the instance. Commonly used for cloud-init scripts that configures the instance during boot up.
- L64 _public property_ `public string? KeyName { get; }` — Key name for the instance (optional). If skipped, alternative ways to administer the instance must be enabled, such as the AWS SSM Agent.
- L78-90 _public ctor_ `public AwsFleetManagerSettings(string region, string imageId, string instanceType, string? iamInstanceProfile, IReadOnlyDictionary<string, string> tags, List<string> subnetIds, List<string> securityGroupIds, string? userData, string? keyName)` — Constructor
- L96-100 _public method_ `public string GetRandomSubnetId()` — Get a random subnet ID. Used for
- L107-116 _public method_ `public string? GetUserDataAsBase64()` — Get user-data as base64 Required when interacting with the EC2 API.

#### class `HordeServer.Agents.Fleet.Providers.AwsFleetManager`  
`public sealed class AwsFleetManager : IFleetManager`  
_public; L123-361_
- inherits: `IFleetManager`
- desc: Fleet manager for handling AWS EC2 instances Will create and/or terminate instances from scratch.
- L129 _public const_ `public const string AwsTagPoolName = "Horde_Autoscale_Pool"` — EC2 tag prefix signaling an instance belong to agent pool, through pool name Deprecated in favor of AwsTagPoolId as pool ID is the stable reference to a pool.
- L134 _public const_ `public const string AwsTagPoolId = "Horde_Autoscale_PoolId"` — EC2 tag prefix signaling an instance belong to agent pool, through pool ID
- L136 _private const_ `private const string AwsTagPropertyName = "aws-tag"`
- L141 _public property_ `public AwsFleetManagerSettings Settings { get; }` — Settings for fleet manager
- L143 _private field_ `private readonly IAmazonEC2 _ec2`
- L144 _private field_ `private readonly IAgentCollection _agentCollection`
- L145 _private field_ `private readonly Tracer _tracer`
- L146 _private field_ `private readonly ILogger _logger`
- L151-158 _public ctor_ `public AwsFleetManager(IAmazonEC2 ec2, IAgentCollection agentCollection, AwsFleetManagerSettings settings, Tracer tracer, ILogger<AwsFleetManager> logger)` — Constructor
- L161-224 _public method_ `public async Task<ScaleResult> ExpandPoolAsync(IPool pool, IReadOnlyList<IAgent> agents, int count, CancellationToken cancellationToken)` — (inheritdoc)
- L227-231 _public method_ `public async Task<ScaleResult> ShrinkPoolAsync(IPool pool, IReadOnlyList<IAgent> agents, int count, CancellationToken cancellationToken)` — (inheritdoc)
- L242-268 _public method_ `public static async Task ShrinkPoolViaAgentShutdownRequestAsync(IAgentCollection agentCollection, IPool pool, IReadOnlyList<IAgent> agents, int count, CancellationToken cancellationToken)` — Shrink pool by gracefully requesting a shutdown for the agent Allowing the agent to terminate at next best possible moment (usually when all the leases have finished).
- L270-295 _private method_ `private static async Task<bool> TryRequestShutdownAsync(IAgentCollection agentCollection, IPool pool, IAgent agent, CancellationToken cancellationToken)`
- L298-301 _public method_ `public async Task<int> GetNumStoppedInstancesAsync(IPoolConfig pool, CancellationToken cancellationToken)` — (inheritdoc)
- L312-315 _public method_ `public static Task<List<Instance>> GetInstancesInPoolAsync(IAmazonEC2 ec2, InstanceStateName? instanceState, IPoolConfig pool, Tracer tracer, CancellationToken cancellationToken)` — Get instances that are part of given Horde agent pool
- L327-360 _public method_ `public static async Task<List<Instance>> GetInstancesInPoolAsync(IAmazonEC2 ec2, InstanceStateName? instanceState, string poolId, string poolName, Tracer tracer, CancellationToken cancellationToken)` — Get instances that are part of given Horde agent pool

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Fleet/Providers/AwsRecyclingFleetManager.cs` (HordeServer.Compute)


#### class `HordeServer.Agents.Fleet.Providers.AwsRecyclingFleetManagerSettings`  
`public class AwsRecyclingFleetManagerSettings`  
_public; L18-34_
- desc: Settings for AWS fleet manager that reuses instances
- L24 _public property_ `public List<string>? InstanceTypes { get; }` — Prioritized list of instance types to use waking up an instance If set to null, the instance will be awakened with its last instance type.
- L30-33 _public ctor_ `public AwsRecyclingFleetManagerSettings(List<string>? instanceTypes = null)` — Constructor

#### class `HordeServer.Agents.Fleet.Providers.AwsFleetManagerException`  
`public class AwsFleetManagerException : Exception`  
_public; L39-46_
- inherits: `Exception`
- desc: Base exception for AWS fleet managers
- L42 _public ctor_ `public AwsFleetManagerException()` — (inheritdoc)
- L45 _public ctor_ `public AwsFleetManagerException(string message) : base(message)` — (inheritdoc)

#### class `HordeServer.Agents.Fleet.Providers.AwsBadHttpResponseException`  
`public class AwsBadHttpResponseException : AwsFleetManagerException`  
_public; L51-58_
- inherits: `AwsFleetManagerException`
- desc: Generic HTTP response error from AWS API
- L57 _public ctor_ `public AwsBadHttpResponseException(HttpStatusCode statusCode) : base($"HTTP status code {statusCode}")` — Constructor

#### class `HordeServer.Agents.Fleet.Providers.AwsRecyclingFleetManager`  
`public sealed class AwsRecyclingFleetManager : IFleetManager`  
_public; L65-440_
- inherits: `IFleetManager`
- desc: Fleet manager for handling AWS EC2 instances Will start already existing but stopped instances to reuse existing EBS disks. See AwsFleetManager for creating and terminating instances from scratch.
- L67 _private field_ `private static readonly Random s_random = new()`
- L72 _public property_ `public AwsRecyclingFleetManagerSettings Settings { get; }` — Settings for fleet manager
- L74 _private field_ `private readonly IAmazonEC2 _ec2`
- L75 _private field_ `private readonly IAgentCollection _agentCollection`
- L76 _private field_ `private readonly Meter _meter`
- L77 _private field_ `private readonly IClock _clock`
- L78 _private field_ `private readonly Tracer _tracer`
- L79 _private field_ `private readonly ILogger _logger`
- L80 _private field_ `private readonly Counter<int> _ec2StartInstanceCounter`
- L85-95 _public ctor_ `public AwsRecyclingFleetManager(IAmazonEC2 ec2, IAgentCollection agentCollection, Meter meter, IClock clock, AwsRecyclingFleetManagerSettings settings, Tracer tracer, ILogger<AwsRecyclingFleetManager> logger)` — Constructor
- L98-155 _public method_ `public async Task<ScaleResult> ExpandPoolAsync(IPool pool, IReadOnlyList<IAgent> agents, int requestedInstancesCount, CancellationToken cancellationToken)` — (inheritdoc)
- L157-168 _private method_ `private static Dictionary<string, List<Instance>> GetInstancesToLaunch( Dictionary<string, List<Instance>> candidatesPerAz, Dictionary<string, int> requestCountPerAz)`
- L178-213 _internal method_ `internal static Dictionary<string, int> DistributeInstanceRequestsOverAzs( int requestedInstancesCount, IReadOnlyDictionary<string, int> instanceCountPerAz, out int remainingInstancesCount, bool randomizeAzOrdering = true)` — Balance number of instance requests evenly over given availability zones (AZs)
- L223-291 _private method_ `private async Task StartInstancesWithRetriesAsync(List<Instance> instances, IReadOnlyList<InstanceType>? instanceTypePriority, CancellationToken cancellationToken)` — Wake up already stopped instances If an insufficient capacity error, all instance types will be changed according to the priority type list. Capacity errors typically occurs per instance type, so retrying using a different one may circumvent the issue.
- L293-336 _internal method_ `internal async Task StartInstancesAsync(List<Instance> instances, InstanceType? instanceType, CancellationToken cancellationToken)`
- L345-372 _private method_ `private async Task ChangeInstanceTypeAsync(List<Instance> instances, InstanceType newInstanceType, CancellationToken cancellationToken)` — Change instance type of given instances
- L379-400 _private method_ `private async Task StopStuckPendingInstancesAsync(IPool pool, CancellationToken cancellationToken)` — Stop instances that have been stuck in state pending for longer than X time
- L408-420 _private method_ `private async Task<Dictionary<string, List<Instance>>> GetCandidateInstancesAsync(IPool pool, CancellationToken cancellationToken)` — Get list of stopped instances from EC2 API that can be used scaling out a given pool
- L423-427 _public method_ `public async Task<ScaleResult> ShrinkPoolAsync(IPool pool, IReadOnlyList<IAgent> agents, int count, CancellationToken cancellationToken)` — (inheritdoc)
- L430-434 _public method_ `public async Task<int> GetNumStoppedInstancesAsync(IPoolConfig pool, CancellationToken cancellationToken)` — (inheritdoc)
- L436-439 _private method_ `private static bool IsResponseSuccessful(AmazonWebServiceResponse response)`

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Fleet/Providers/AwsReuseFleetManager.cs` (HordeServer.Compute)


#### class `HordeServer.Agents.Fleet.Providers.AwsReuseFleetManagerSettings`  
`public class AwsReuseFleetManagerSettings`  
_public; L14-30_
- desc: Settings for AWS fleet manager that reuses instances
- L20 _public property_ `public List<string>? InstanceTypes { get; }` — Prioritized list of instance types to use waking up an instance If set to null, the instance will be awakened with its last instance type.
- L26-29 _public ctor_ `public AwsReuseFleetManagerSettings(List<string>? instanceTypes = null)` — Constructor

#### class `HordeServer.Agents.Fleet.Providers.AwsReuseFleetManager`  
`public sealed class AwsReuseFleetManager : IFleetManager`  
_public; L37-165_
- inherits: `IFleetManager`
- desc: Fleet manager for handling AWS EC2 instances Will start already existing but stopped instances to reuse existing EBS disks. See AwsFleetManager for creating and terminating instances from scratch.
- L42 _public property_ `public AwsReuseFleetManagerSettings Settings { get; }` — Settings for fleet manager
- L44 _private field_ `private readonly IAmazonEC2 _ec2`
- L45 _private field_ `private readonly IAgentCollection _agentCollection`
- L46 _private field_ `private readonly Tracer _tracer`
- L47 _private field_ `private readonly ILogger _logger`
- L52-59 _public ctor_ `public AwsReuseFleetManager(IAmazonEC2 ec2, IAgentCollection agentCollection, AwsReuseFleetManagerSettings settings, Tracer tracer, ILogger<AwsReuseFleetManager> logger)` — Constructor
- L62-151 _public method_ `public async Task<ScaleResult> ExpandPoolAsync(IPool pool, IReadOnlyList<IAgent> agents, int requestedInstancesCount, CancellationToken cancellationToken)` — (inheritdoc)
- L154-158 _public method_ `public async Task<ScaleResult> ShrinkPoolAsync(IPool pool, IReadOnlyList<IAgent> agents, int count, CancellationToken cancellationToken)` — (inheritdoc)
- L161-164 _public method_ `public async Task<int> GetNumStoppedInstancesAsync(IPoolConfig pool, CancellationToken cancellationToken)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Fleet/Providers/NoOpFleetManager.cs` (HordeServer.Compute)


#### class `HordeServer.Agents.Fleet.Providers.NoOpFleetManager`  
`public class NoOpFleetManager : IFleetManager`  
_public; L11-40_
- inherits: `IFleetManager`
- desc: No-op implementation of IFleetManager
- L13 _private* field_ `readonly ILogger _logger`
- L19-22 _public ctor_ `public NoOpFleetManager(ILogger<NoOpFleetManager> logger)` — Constructor
- L25-29 _public method_ `public Task<ScaleResult> ExpandPoolAsync(IPool pool, IReadOnlyList<IAgent> agents, int count, CancellationToken cancellationToken)` — (inheritdoc)
- L32-36 _public method_ `public Task<ScaleResult> ShrinkPoolAsync(IPool pool, IReadOnlyList<IAgent> agents, int count, CancellationToken cancellationToken)` — (inheritdoc)
- L39 _public method_ `public Task<int> GetNumStoppedInstancesAsync(IPoolConfig pool, CancellationToken cancellationToken)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/IAgent.cs` (HordeServer.Compute)


#### enum `HordeServer.Agents.AgentMode`  
`public enum AgentMode`  
_public; L30-53_
- desc: Defines the operation mode of the agent
- L35 _public* enumerator_ `Unspecified = 0` — For backwards compatibility
- L43 _public* enumerator_ `Dedicated = 1` — Dedicated mode - Trusted agent running in a controlled environment (e.g., build farm) - Does not run any other non-Horde workloads - Capable of executing all lease types
- L52 _public* enumerator_ `Workstation = 2` — Workstation mode - Agent authenticates as the current user through interactive authentication via EpicGames.OIDC - Low trust level, typically used for spare on-premise hardware like workstations - Lease execution is inherently unreliable as these agents yield to non-Horde workloads - Limited to compute leases only, primarily to support remote execution

#### interface `HordeServer.Agents.IAgent`  
`public interface IAgent`  
_public; L58-321_
- desc: Mirrors an Agent document in the database
- L63 _public property_ `public AgentId Id { get; }` — Identifier for this agent.
- L68 _public property_ `public SessionId? SessionId { get; }` — The current session id, if it's online
- L73 _public property_ `public DateTime? SessionExpiresAt { get; }` — Time at which the current session expires.
- L78 _public property_ `public AgentStatus Status { get; }` — Current status of this agent
- L83 _public property_ `public DateTime? LastOnlineTime { get; }` — Last time that the agent was online. Null if the agent is currently online.
- L88 _public property_ `public bool Enabled { get; }` — Whether the agent is enabled
- L93 _public property_ `public bool Ephemeral { get; }` — Whether the agent is ephemeral
- L98 _public property_ `public AgentMode Mode { get; }` — Operation mode of agent
- L103 _public property_ `public bool Deleted { get; }` — Whether the agent should be included on the dashboard. This is set to true for ephemeral agents once they are no longer online, or agents that are explicitly deleted.
- L108 _public property_ `public string? Version { get; }` — Version of the software running on this agent
- L113 _public property_ `public string? Comment { get; }` — Arbitrary comment for the agent (useful for disable reasons etc)
- L118 _public property_ `public IReadOnlyList<string> ServerDefinedProperties { get; }` — List of server-defined properties (will overwrite and merge with agent-reported properties)
- L123 _public property_ `public IReadOnlyList<string> Properties { get; }` — List of properties for this agent
- L128 _public property_ `public IReadOnlyDictionary<string, int> Resources { get; }` — List of resources available to the agent
- L133 _public property_ `public string? LastUpgradeVersion { get; }` — Last upgrade that was attempted
- L138 _public property_ `public DateTime? LastUpgradeTime { get; }` — Time that which the last upgrade was attempted
- L143 _public property_ `public int? UpgradeAttemptCount { get; }` — Number of times an upgrade job has failed
- L148 _public property_ `public IReadOnlyList<PoolId> Pools { get; }` — All pools for this agent
- L153 _public property_ `public IReadOnlyList<PoolId> DynamicPools { get; }` — Dynamically applied pools
- L158 _public property_ `public IReadOnlyList<PoolId> ExplicitPools { get; }` — List of manually assigned pools for agent
- L163 _public property_ `public bool RequestConform { get; }` — Whether a conform is requested
- L168 _public property_ `public bool RequestFullConform { get; }` — Whether a full conform is requested
- L173 _public property_ `public bool RequestRestart { get; }` — Whether a machine restart is requested
- L178 _public property_ `public bool RequestShutdown { get; }` — Whether the machine should be shutdown
- L183 _public property_ `public bool RequestForceRestart { get; }` — Whether a forced machine restart is requested
- L188 _public property_ `public string? LastShutdownReason { get; }` — The reason for the last agent shutdown
- L193 _public property_ `public IReadOnlyList<AgentWorkspaceInfo> Workspaces { get; }` — List of workspaces currently synced to this machine
- L198 _public property_ `public DateTime LastConformTime { get; }` — Time at which the last conform job ran
- L203 _public property_ `public int? ConformAttemptCount { get; }` — Number of times a conform job has failed
- L208 _public property_ `public IReadOnlyList<IAgentLease> Leases { get; }` — Array of active leases.
- L213 _public property_ `public string EnrollmentKey { get; }` — Key used to validate that a particular enrollment is still valid for this agent
- L218 _public property_ `public DateTime UpdateTime { get; }` — Last time that the agent was modified
- L223 _public property_ `public uint UpdateIndex { get; }` — Update counter for this document. Any updates should compare-and-swap based on the value of this counter, or increment it in the case of server-side updates.
- L231 _public* method_ `Task<ISession?> GetSessionAsync(SessionId sessionId, CancellationToken cancellationToken = default)` — Gets a sessions for the agent
- L242 _public* method_ `Task<IReadOnlyList<ISession>> FindSessionsAsync(DateTime? startTime = null, DateTime? finishTime = null, int index = 0, int count = 10, CancellationToken cancellationToken = default)` — Find sessions for the given agent
- L250 _public* method_ `Task<IAgent?> TryResetAsync(bool ephemeral, string enrollmentKey, CancellationToken cancellationToken = default)` — Resets an agent to use new settings
- L257 _public* method_ `Task<IAgent?> TryDeleteAsync(CancellationToken cancellationToken = default)` — Deletes an agent
- L265 _public* method_ `Task<IAgent?> TryUpdateAsync(UpdateAgentOptions options, CancellationToken cancellationToken = default)` — Update an agent's settings
- L274 _public* method_ `Task<IAgent?> TryUpdateWorkspacesAsync(List<AgentWorkspaceInfo> workspaces, bool requestConform, CancellationToken cancellationToken = default)` — Update the current workspaces for an agent.
- L282 _public* method_ `Task<IAgent?> TryCreateSessionAsync(CreateSessionOptions options, CancellationToken cancellationToken = default)` — Sets the current session
- L290 _public* method_ `Task<IAgent?> TryUpdateSessionAsync(UpdateSessionOptions options, CancellationToken cancellationToken = default)` — Attempt to update the current session
- L297 _public* method_ `Task<IAgent?> TryTerminateSessionAsync(CancellationToken cancellationToken = default)` — Terminates the current session
- L305 _public* method_ `Task<IAgent?> TryCreateLeaseAsync(CreateLeaseOptions options, CancellationToken cancellationToken = default)` — Attempts to add a lease to an agent
- L314 _public* method_ `Task<IAgent?> TryCancelLeaseAsync(int leaseIdx, LeaseOutcomeReason? reason = null, CancellationToken cancellationToken = default)` — Attempts to cancel a lease
- L320 _public* method_ `Task<IAgent?> WaitForUpdateAsync(CancellationToken cancellationToken = default)` — Wait for this agent to be updated

#### record `HordeServer.Agents.CreateLeaseOptions`  
`public record CreateLeaseOptions(LeaseId Id, LeaseId? ParentId, string Name, StreamId? StreamId, PoolId? PoolId, LogId? LogId, IReadOnlyDictionary<string, int>? Resources, bool Exclusive, IMessage Payload)`  
_public; L326-326_
- desc: Information for a new lease

#### record `HordeServer.Agents.CreateAgentOptions`  
`public record CreateAgentOptions(AgentId Id, AgentMode Mode, bool Ephemeral, string EnrollmentKey, IReadOnlyList<string>? ServerDefinedProperties = null)`  
_public; L336-336_
- desc: Options for creating an agent

#### record `HordeServer.Agents.UpdateAgentOptions`  
`public record UpdateAgentOptions(bool? Enabled = null, bool? RequestConform = null, bool? RequestFullConform = null, bool? RequestRestart = null, bool? RequestShutdown = null, bool? RequestForceRestart = null, string? ShutdownReason = null, List<PoolId>? ExplicitPools = null, string? Comment = null)`  
_public; L350-350_
- desc: Options for updating an agent

#### record `HordeServer.Agents.CreateSessionOptions`  
`public record CreateSessionOptions(RpcAgentCapabilities Capabilities, IReadOnlyList<PoolId> DynamicPools, string? Version)`  
_public; L358-358_
- desc: Options for starting a new agent session

#### record `HordeServer.Agents.UpdateSessionOptions`  
`public record UpdateSessionOptions(AgentStatus? Status = null, RpcAgentCapabilities? Capabilities = null, IReadOnlyList<PoolId>? DynamicPools = null, IEnumerable<RpcLease>? Leases = null, LeaseOutcomeReason? DefaultLeaseOutcomeReason = null, RpcAgentCapabilities? CapabilityOverrides = null)`  
_public; L369-369_
- desc: Options for updating a new agent session

#### class `HordeServer.Agents.AgentExtensions`  
`public static class AgentExtensions`  
_public; L374-708_
- desc: Extension methods for IAgent
- L380 _public property_ `public static ToolId AgentToolId { get; }` — Default tool ID for agent software (multi-platform, shipped without a .NET runtime) This is being deprecated in favor of the platform-specific and self-contained versions of the agent below
- L385 _public property_ `public static ToolId AgentWinX64ToolId { get; }` — Tool ID for Windows-specific and self-contained agent software
- L390 _public property_ `public static ToolId AgentLinuxX64ToolId { get; }` — Tool ID for Linux-specific and self-contained agent software
- L395 _public property_ `public static ToolId AgentMacX64ToolId { get; }` — Tool ID for Mac-specific and self-contained agent software
- L400 _public field_ `public static readonly HashSet<string> ServerDefinedPropertyNames = [KnownPropertyNames.Trusted]` — Set of property names that can only be set by the server
- L408-441 _public method_ `public static ToolId GetSoftwareToolId(this IAgent agent, ComputeConfig computeConfig)` — Gets the tool ID for the software the given agent should be running
- L447-450 _public method_ `public static bool IsSessionValid(this IAgent agent, DateTime utcNow)` — Determines whether this agent is online
- L458-461 _public method_ `public static bool IsInPool(this IAgent agent, PoolId poolId)` — Tests whether an agent is in the given pool
- L468-472 _public method_ `public static bool IsSelfContained(this IAgent agent)` — Tests whether an agent has reported as being a self-contained .NET package
- L479-483 _public method_ `public static bool IsAutoUpdateEnabled(this IAgent agent)` — Checks whether an agent wants to auto-update itself
- L489-493 _public method_ `public static string? GetToolId(this IAgent agent)` — Get optional tool ID as reported by agent KnownPropertyNames.ToolId
- L500-504 _public method_ `public static long? GetDiskFreeSpace(this IAgent agent)` — Get free disk space on agent (as reported through primary device capabilities)
- L511-526 _public method_ `public static RuntimePlatform.Type? GetOsFamily(this IAgent agent)` — Get operating system family of agent
- L534-537 _public method_ `public static bool HasProperty(this IAgent agent, string property)` — Tests whether an agent has a particular property
- L545-548 _public method_ `public static bool IsPropertyServerDefined(string propName)` — Check if a property name (incl value) is controlled by the server Such properties are protected and cannot be set by the agent.
- L555-558 _public method_ `public static IReadOnlyList<string> RemoveServerDefinedProperties(IReadOnlyList<string> properties)` — Filters a list of properties from server-defined properties
- L566-596 _public method_ `public static IEnumerable<string> GetPropertyValues(this IAgent agent, string name)` — Finds property values from a sorted list of Name=Value pairs
- L604-607 _public method_ `public static bool SatisfiesCondition(this IAgent agent, Condition condition)` — Evaluates a condition against an agent
- L617-632 _public method_ `public static bool MeetsRequirements(this IAgent agent, Requirements requirements, Dictionary<string, int> assignedResources, List<Condition> conditions)` — Determine whether it's possible to add a lease for the given resources
- L645-707 _public method_ `public static bool MeetsRequirements(this IAgent agent, PoolId? poolId, List<Condition> conditions, IEnumerable<string>? properties, Dictionary<string, ResourceRequirements>? resources, bool exclusive, Dictionary<string, int> assignedResources)` — Determine whether it's possible to add a lease for the given resources

#### class `HordeServer.Agents.AgentWorkspaceInfo`  
`public class AgentWorkspaceInfo`  
_public; L713-863_
- desc: Information about a workspace synced to an agent
- L718 _public property_ `public string? Cluster { get; set; }` — Name of the Perforce cluster to use
- L723 _public property_ `public string? UserName { get; set; }` — User to log into Perforce with (eg. buildmachine)
- L728 _public property_ `public string Identifier { get; set; }` — Identifier to distinguish this workspace from other workspaces
- L733 _public property_ `public string Stream { get; set; }` — The stream to sync
- L738 _public property_ `public List<string>? View { get; set; }` — Custom view for the workspace
- L743 _public property_ `public bool Incremental { get; set; }` — Whether to use an incremental workspace
- L748 _public property_ `public string? Method { get; set; }` — Method to use when syncing/materializing data from Perforce
- L753 _public property_ `public long? MinScratchSpace { get; set; }` — Minimum disk space that must be available *after* syncing this workspace (in megabytes)
- L758 _public property_ `public long? ConformDiskFreeSpace { get; set; }` — Threshold for when to trigger an automatic conform of agent. Measured in megabytes free on disk.
- L772-789 _public ctor_ `public AgentWorkspaceInfo(string? cluster, string? userName, string identifier, string stream, List<string>? view, bool incremental, string? method, long? minScratchSpace = null, long? conformDiskFreeSpace = null)` — Constructor
- L795-803 _public ctor_ `public AgentWorkspaceInfo(RpcAgentWorkspace workspace) : this(workspace.ConfiguredCluster, workspace.ConfiguredUserName, workspace.Identifier, workspace.Stream, (workspace.View.Count > 0) ? workspace.View.ToList() : null, workspace.Incremental, workspace.Method, workspace.MinScratchSpace, workspace.ConformDiskFreeSpace)` — Constructor
- L809-818 _public method_ `public string GetDigest()` — Gets a digest of the settings for this workspace
- L821-844 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L847-850 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L858-862 _public method_ `public static bool SetEquals(IReadOnlyList<AgentWorkspaceInfo> workspacesA, IReadOnlyList<AgentWorkspaceInfo> workspacesB)` — Checks if two workspace sets are equivalent, ignoring order

#### class `HordeServer.Agents.AutoSdkConfig`  
`public class AutoSdkConfig`  
_public; L868-944_
- desc: Configuration for an AutoSDK workspace
- L873 _public property_ `public static AutoSdkConfig None { get; }` — Disables use of AutoSDK.
- L878 _public property_ `public static AutoSdkConfig Full { get; }` — Syncs the entire AutoSDK folder.
- L883 _public property_ `public List<string> View { get; set; }` — Additive filter for paths to include in the workspace
- L888-891 _public ctor_ `public AutoSdkConfig()` — Constructor
- L897-907 _public ctor_ `public AutoSdkConfig(IEnumerable<string>? filter)` — Constructor
- L914-926 _public method_ `public static AutoSdkConfig? Merge(AutoSdkConfig? lhs, AutoSdkConfig? rhs)` — attrs: `[return: NotNullIfNotNull("lhs")] [return: NotNullIfNotNull("rhs")]` — Merge two workspaces together
- L931-943 _public method_ `public static bool Equals(AutoSdkConfig? lhs, AutoSdkConfig? rhs)` — Test whether two views are equal

#### interface `HordeServer.Agents.IAgentLease`  
`public interface IAgentLease`  
_public; L948-979_
- desc: Document describing an active lease
- L953 _public* property_ `LeaseId Id { get; }` — Name of this lease
- L958 _public* property_ `LeaseId? ParentId { get; }` — The parent lease id
- L963 _public* property_ `LeaseState State { get; }` — The current state of the lease
- L968 _public* property_ `IReadOnlyDictionary<string, int>? Resources { get; }` — Resources used by this lease
- L973 _public* property_ `bool Exclusive { get; }` — Whether the lease requires exclusive access to the agent
- L978 _public* property_ `Any? Payload { get; }` — For leases in the pending state, encodes an "any" protobuf containing the payload for the agent to execute the lease.

#### class `HordeServer.Agents.AgentLease`  
`public class AgentLease : IAgentLease`  
_public; L984-1051_
- inherits: `IAgentLease`
- desc: Document describing an active lease
- L988 _public property_ `public LeaseId Id { get; set; }` — attrs: `[BsonRequired]` — (inheritdoc)
- L991 _public property_ `public LeaseId? ParentId { get; set; }` — (inheritdoc)
- L994 _public property_ `public LeaseState State { get; set; }` — (inheritdoc)
- L997 _public property_ `public IReadOnlyDictionary<string, int>? Resources { get; set; }` — (inheritdoc)
- L1000 _public property_ `public bool Exclusive { get; set; }` — (inheritdoc)
- L1003 _public property_ `public byte[]? Payload { get; set; }` — (inheritdoc)
- L1005 _private* property_ `Any? IAgentLease.Payload => ...`
- L1011-1013 _private ctor_ `private AgentLease()` — attrs: `[BsonConstructor]` — Private constructor
- L1018-1021 _public ctor_ `public AgentLease(IAgentLease other) : this(other.Id, other.ParentId, other.State, other.Resources, other.Exclusive, other.Payload?.ToByteArray())` — Constructor
- L1032-1040 _public ctor_ `public AgentLease(LeaseId id, LeaseId? parentId, LeaseState state, IReadOnlyDictionary<string, int>? resources, bool exclusive, byte[]? payload)` — Constructor
- L1047-1050 _public ctor_ `public AgentLease(CreateLeaseOptions options) : this(options.Id, options.ParentId, LeaseState.Pending, options.Resources, options.Exclusive, Any.Pack(options.Payload).ToByteArray())` — Create a lease from

#### class `HordeServer.Agents.AgentLeaseExtensions`  
`static class AgentLeaseExtensions`  
_internal*; L1053-1067_
- L1059-1066 _public method_ `public static RpcLease ToRpcMessage(this IAgentLease agentLease)` — Converts this lease to an RPC message

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/IAgentCollection.cs` (HordeServer.Compute)


#### interface `HordeServer.Agents.IAgentCollection`  
`public interface IAgentCollection`  
_public; L14-59_
- desc: Interface for a collection of agent documents
- L21 _public* method_ `Task<IAgent> AddAsync(CreateAgentOptions options, CancellationToken cancellationToken = default)` — Adds a new agent with the given properties
- L29 _public* method_ `Task<IAgent?> GetAsync(AgentId agentId, CancellationToken cancellationToken = default)` — Gets an agent by ID
- L37 _public* method_ `Task<IReadOnlyList<IAgent>> GetManyAsync(List<AgentId> agentIds, CancellationToken cancellationToken = default)` — Gets multiple agents by ID
- L51 _public* method_ `IAsyncEnumerable<IAgent> FindAsync(PoolId? poolId = null, DateTime? modifiedAfter = null, string? property = null, AgentStatus? status = null, bool? enabled = null, bool includeDeleted = false, bool consistentRead = true, CancellationToken cancellationToken = default)` — Finds all agents matching certain criteria
- L58 _public* method_ `IAuditLogChannel<AgentId> GetLogger(AgentId agentId)` — Gets the log channel for an agent

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/IAgentScheduler.cs` (HordeServer.Compute)


#### enum `HordeServer.Agents.SessionFilterType`  
`public enum SessionFilterType`  
_public; L14-25_
- desc: Type of data to return from enumeration calls
- L19 _public* enumerator_ `Available = 0` — Return only sessions which can satisfy resource/exclusivity requirements
- L24 _public* enumerator_ `Potential = 1` — Return all active sessions in the response, even if they are currently busy

#### interface `HordeServer.Agents.IAgentScheduler`  
`public interface IAgentScheduler`  
_public; L30-166_
- desc: Interface for a scheduler that manages agent sessions and leases.
- L37 _public* event_ `event Action<SessionId>? SessionUpdated` — Event raised whenever a session is updated (locally or remotely)
- L47 _public* method_ `Task<RpcSession?> TryCreateSessionAsync(AgentId agentId, SessionId sessionId, RpcAgentCapabilities capabilities, CancellationToken cancellationToken = default)` — Attempts to create a new session for the given agent. Fails if the agent is already executing a session.
- L55 _public* method_ `Task<RpcSession?> TryGetSessionAsync(SessionId sessionId, CancellationToken cancellationToken = default)` — Attempt to get the latest state of the given session
- L63 _public* method_ `Task<Dictionary<SessionId, RpcSession>> TryGetSessionsAsync(IReadOnlyList<SessionId> sessionIds, CancellationToken cancellationToken = default)` — Batch fetch the latest state of multiple sessions in a single round-trip
- L71 _public* method_ `Task<RpcAgentCapabilities?> TryGetCapabilitiesAsync(RpcSession session, CancellationToken cancellationToken = default)` — Attempt to get capabilities for the given session
- L81 _public* method_ `Task<RpcSession?> TryUpdateSessionAsync(RpcSession session, RpcSession? newSession = null, RpcAgentCapabilities? newCapabilities = null, CancellationToken cancellationToken = default)` — Attempts to create a new session for the given agent. Fails if the agent is already executing a session.
- L91 _public* method_ `Task<IoHash> CreateFilterAsync(RpcAgentRequirements requirements, CancellationToken cancellationToken = default)` — Create a new filter for agents matching with the given requirements
- L98 _public* method_ `Task TouchFilterAsync(IoHash requirementsHash, CancellationToken cancellationToken = default)` — Update the timestamp on the given filter
- L105 _public* method_ `Task<IoHash[]> GetFiltersAsync(CancellationToken cancellationToken = default)` — Gets the hash of all current filters
- L113 _public* method_ `ValueTask<RpcAgentRequirements?> TryGetFilterRequirementsAsync(IoHash requirementsHash, CancellationToken cancellationToken)` — Gets the requirements for a particular filter
- L122 _public* method_ `IAsyncEnumerable<SessionId> EnumerateFilteredSessionsAsync(IoHash requirementsHash, SessionFilterType sessionType = SessionFilterType.Potential, CancellationToken cancellationToken = default)` — Enumerate all the sessions in a filter
- L132 _public* method_ `IAsyncEnumerable<RpcSession> FindExpiredSessionsAsync(CancellationToken cancellationToken = default)` — Enumerates all the sessions which have expired
- L140 _public method_ `public Task<List<SessionId>> RemoveOrphanedSessionsAsync(CancellationToken cancellationToken = default)` — Remove session states that are not registered in the "current session key" This can happen when upgrading Horde to a newer version and old agents that created new sessions after that. Clearing Redis can also fix this issue.
- L147 _public* method_ `Task<LeaseId[]> FindActiveLeaseIdsAsync(CancellationToken cancellationToken = default)` — Finds all active agent lease IDs
- L155 _public* method_ `Task<int> GetChildLeaseCountAsync(LeaseId id, CancellationToken cancellationToken = default)` — Find how many child leases a particular lease has
- L163 _public* method_ `Task<LeaseId[]> GetChildLeaseIdsAsync(LeaseId id, CancellationToken cancellationToken = default)` — Get all child lease IDs

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Leases/ILease.cs` (HordeServer.Compute)


#### interface `HordeServer.Agents.Leases.ILease`  
`public interface ILease`  
_public; L17-93_
- desc: Document describing a lease. This exists to permanently record a lease; the agent object tracks internal state of any active leases through AgentLease objects.
- L22 _public property_ `public LeaseId Id { get; }` — The unique id of this lease
- L27 _public property_ `public LeaseId? ParentId { get; }` — Identifier for the parent lease. Used to terminate hierarchies of leases.
- L32 _public property_ `public string Name { get; }` — Name of this lease
- L37 _public property_ `public AgentId AgentId { get; }` — Unique id of the agent
- L42 _public property_ `public SessionId SessionId { get; }` — Unique id of the agent session
- L47 _public property_ `public StreamId? StreamId { get; }` — The stream this lease belongs to
- L52 _public property_ `public PoolId? PoolId { get; }` — Pool for the work being executed
- L57 _public property_ `public LogId? LogId { get; }` — The log for this lease, if applicable
- L62 _public property_ `public DateTime StartTime { get; }` — Time at which this lease started
- L67 _public property_ `public DateTime? FinishTime { get; }` — Time at which this lease completed
- L72 _public property_ `public ReadOnlyMemory<byte> Payload { get; }` — Payload for this lease. A packed Google.Protobuf.Any object.
- L77 _public property_ `public LeaseOutcome Outcome { get; }` — Outcome of the lease
- L82 _public property_ `public LeaseOutcomeReason OutcomeReason { get; set; }` — Reason for the outcome. Can be a combination of reasons.
- L87 _public property_ `public ReadOnlyMemory<byte> Output { get; }` — Output from executing the lease
- L92 _public property_ `public LeaseMetrics? Metrics { get; }` — Metrics collected during execution of lease

#### record `HordeServer.Agents.Leases.LeaseCpuTime`  
`public record LeaseCpuTime(TimeSpan User, TimeSpan System, TimeSpan Idle)`  
_public; L101-101_
- desc: CPU timings for a lease

#### record `HordeServer.Agents.Leases.LeaseMetrics`  
`public record LeaseMetrics( TimeSpan SetupTime, TimeSpan TeardownTime, int CpuCount, double GlobalCpuUtilization, LeaseCpuTime GlobalCpuTime )`  
_public; L112-112_
- desc: Metrics collected during execution of lease Machine-wide metrics assumes the lease has exclusive access to the agent and other background work is negligible.

#### class `HordeServer.Agents.Leases.LeaseExtensions`  
`public static class LeaseExtensions`  
_public; L123-145_
- desc: Extension methods for leases
- L130-133 _public method_ `public static Any GetTask(this ILease lease)` — Gets the task from a lease, encoded as an Any protobuf object
- L141-144 _public method_ `public static T GetTask<T>(this ILease lease) where T : IMessage<T>, new()` — Gets a typed task object from a lease

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Leases/ILeaseCollection.cs` (HordeServer.Compute)


#### interface `HordeServer.Agents.Leases.ILeaseCollection`  
`public interface ILeaseCollection`  
_public; L15-119_
- desc: Interface for a collection of lease documents
- L32 _public* method_ `Task<ILease> AddAsync(LeaseId id, LeaseId? parentId, string name, AgentId agentId, SessionId sessionId, StreamId? streamId, PoolId? poolId, LogId? logId, DateTime startTime, byte[] payload, CancellationToken cancellationToken = default)` — Adds a lease to the collection
- L40 _public* method_ `Task DeleteAsync(LeaseId leaseId, CancellationToken cancellationToken = default)` — Deletes a lease from the collection
- L48 _public* method_ `Task<ILease?> GetAsync(LeaseId leaseId, CancellationToken cancellationToken = default)` — Gets a specific lease
- L64 _public* method_ `Task<IReadOnlyList<ILease>> FindLeasesAsync(LeaseId? parentId = null, AgentId? agentId = null, SessionId? sessionId = null, DateTime? minTime = null, DateTime? maxTime = null, int? index = null, int? count = null, string? indexHint = null, bool consistentRead = true, CancellationToken cancellationToken = default)` — Finds all leases matching a set of criteria
- L77 _public* method_ `Task<IReadOnlyList<ILease>> FindLeasesByFinishTimeAsync(DateTime? minFinishTime, DateTime? maxFinishTime, int? index, int? count, string? indexHint = null, bool consistentRead = true, CancellationToken cancellationToken = default)` — Finds all leases by finish time
- L87 _public* method_ `Task<IReadOnlyList<ILease>> FindLeasesAsync(DateTime? minTime, DateTime? maxTime, CancellationToken cancellationToken = default)` — Finds all leases between min and/or max time Preferred over the more generic FindLeasesAsync as this one use a better index and relaxed read consistency
- L96 _public* method_ `Task<IReadOnlyList<ILease>> FindActiveLeasesAsync(int? index = null, int? count = null, CancellationToken cancellationToken = default)` — Finds all active leases
- L109 _public* method_ `Task<bool> TrySetOutcomeAsync(LeaseId leaseId, DateTime finishTime, LeaseOutcome outcome, LeaseOutcomeReason outcomeReason, byte[]? output, LeaseMetrics? metrics, CancellationToken cancellationToken = default)` — Sets the outcome of a lease
- L118 _public* method_ `Task<bool> TryAddOutcomeReasonsAsync(LeaseId leaseId, LeaseOutcomeReason outcomeReason, CancellationToken cancellationToken = default)` — Adds outcome reasons to an existing lease. This can be used to merge reasons even after the lease has finished.

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Leases/LeaseAclAction.cs` (HordeServer.Compute)


#### class `HordeServer.Agents.Leases.LeaseAclAction`  
`public static class LeaseAclAction`  
_public; L10-21_
- desc: ACL actions which apply to leases
- L15 _public property_ `public static AclAction ViewLeases { get; }` — View all the leases that an agent has worked on
- L20 _public property_ `public static AclAction ViewLeaseTasks { get; }` — View the task data for a lease

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Leases/LeaseCollection.cs` (HordeServer.Compute)


#### class `HordeServer.Agents.Leases.LeaseCollection`  
`public class LeaseCollection : ILeaseCollection`  
_public; L26-282_
- inherits: `ILeaseCollection`
- desc: Collection of lease documents
- L117 _private* field_ `readonly IMongoCollection<LeaseDocument> _leases`
- L118 _private* field_ `readonly Tracer _tracer`
- L119 _private* field_ `readonly MongoIndex<LeaseDocument> _finishTimeStartTimeCompoundIndex`
- L122 _public event_ `public event OnLeaseCompleteDelegate? OnLeaseComplete` — (inheritdoc)
- L127-139 _public ctor_ `public LeaseCollection(IMongoService mongoService, Tracer tracer)` — Constructor
- L142-147 _public method_ `public async Task<ILease> AddAsync(LeaseId id, LeaseId? parentId, string name, AgentId agentId, SessionId sessionId, StreamId? streamId, PoolId? poolId, LogId? logId, DateTime startTime, byte[] payload, CancellationToken cancellationToken)` — (inheritdoc)
- L150-153 _public method_ `public async Task DeleteAsync(LeaseId leaseId, CancellationToken cancellationToken)` — (inheritdoc)
- L156-159 _public method_ `public async Task<ILease?> GetAsync(LeaseId leaseId, CancellationToken cancellationToken)` — (inheritdoc)
- L162-198 _public method_ `public async Task<IReadOnlyList<ILease>> FindLeasesAsync(LeaseId? parentId, AgentId? agentId, SessionId? sessionId, DateTime? minTime, DateTime? maxTime, int? index, int? count, string? indexHint = null, bool consistentRead = true, CancellationToken cancellationToken = default)` — (inheritdoc)
- L201-222 _public method_ `public async Task<IReadOnlyList<ILease>> FindLeasesByFinishTimeAsync(DateTime? minFinishTime, DateTime? maxFinishTime, int? index, int? count, string? indexHint, bool consistentRead, CancellationToken cancellationToken)` — (inheritdoc)
- L225-228 _public method_ `public async Task<IReadOnlyList<ILease>> FindLeasesAsync(DateTime? minTime, DateTime? maxTime, CancellationToken cancellationToken = default)` — (inheritdoc)
- L231-234 _public method_ `public async Task<IReadOnlyList<ILease>> FindActiveLeasesAsync(int? index = null, int? count = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L237-266 _public method_ `public async Task<bool> TrySetOutcomeAsync(LeaseId leaseId, DateTime finishTime, LeaseOutcome outcome, LeaseOutcomeReason outcomeReason, byte[]? output, LeaseMetrics? metrics, CancellationToken cancellationToken)` — (inheritdoc)
- L269-281 _public method_ `public async Task<bool> TryAddOutcomeReasonsAsync(LeaseId leaseId, LeaseOutcomeReason outcomeReason, CancellationToken cancellationToken)` — (inheritdoc)

#### record `HordeServer.Agents.Leases.LeaseCollection.LeaseMetricsDocument`  
`record LeaseMetricsDocument( [property: BsonElement("setup")] int SetupTimeMs, [property: BsonElement("teardown")] int TeardownTimeMs, [property: BsonElement("cpus")] int CpuCount, [property: BsonElement("cpuUtil")] double GlobalCpuUtilization, [property: BsonElement("cpuUsr")] long GlobalCpuUserMs, [property: BsonElement("cpuSys")] long GlobalCpuSystemMs, [property: BsonElement("cpuIdl")] long GlobalCpuIdleMs )`  
_private*; L28-61_
- L38-47 _public method_ `public LeaseMetrics ToLeaseMetrics()`
- L49-60 _public method_ `public static LeaseMetricsDocument FromLeaseMetrics(LeaseMetrics metrics)`

#### class `HordeServer.Agents.Leases.LeaseCollection.LeaseDocument`  
`class LeaseDocument : ILease`  
_private*; L66-115_
- inherits: `ILease`
- desc: Concrete implementation of a lease document
- L68 _public property_ `public LeaseId Id { get; set; }`
- L71 _public property_ `public LeaseId? ParentId { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L73 _public property_ `public string Name { get; set; }`
- L74 _public property_ `public AgentId AgentId { get; set; }`
- L75 _public property_ `public SessionId SessionId { get; set; }`
- L76 _public property_ `public StreamId? StreamId { get; set; }`
- L77 _public property_ `public PoolId? PoolId { get; set; }`
- L78 _public property_ `public LogId? LogId { get; set; }`
- L79 _public property_ `public DateTime StartTime { get; set; }`
- L80 _public property_ `public DateTime? FinishTime { get; set; }`
- L81 _public property_ `public byte[] Payload { get; set; }`
- L82 _public property_ `public LeaseOutcome Outcome { get; set; }`
- L83 _public property_ `public LeaseMetricsDocument? Metrics { get; set; }`
- L86 _public property_ `public LeaseOutcomeReason OutcomeReason { get; set; }` — attrs: `[BsonRepresentation(BsonType.Int64)]`
- L89 _public property_ `public byte[]? Output { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L91 _private* property_ `ReadOnlyMemory<byte> ILease.Payload => ...`
- L92 _private* property_ `ReadOnlyMemory<byte> ILease.Output => ...`
- L93 _private* property_ `LeaseMetrics? ILease.Metrics => ...`
- L96-100 _private ctor_ `private LeaseDocument()` — attrs: `[BsonConstructor]`
- L102-114 _public ctor_ `public LeaseDocument(LeaseId id, LeaseId? parentId, string name, AgentId agentId, SessionId sessionId, StreamId? streamId, PoolId? poolId, LogId? logId, DateTime startTime, byte[] payload)`

#### Namespace-level symbols

- L21 _public delegate_ `public delegate void OnLeaseCompleteDelegate(ILease lease)` — Notification that a lease has been updated

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Leases/LeaseService.cs` (HordeServer.Compute)


#### class `HordeServer.Agents.Leases.LeaseService`  
`public class LeaseService( LeaseCollection leaseCollection, ITelemetryWriter telemetryWriter, IOptionsMonitor<ComputeConfig> computeConfig, ILogger<LeaseService> logger) : IHostedService`  
_public; L13-58_
- desc: Service that emits telemetry when leases complete.
- L20 _private field_ `private readonly ILogger _logger = logger`
- L23-27 _public method_ `public Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L30-34 _public method_ `public Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L36-57 _private method_ `private void OnLeaseComplete(ILease lease)`

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Leases/LeaseTelemetry.cs` (HordeServer.Compute)


#### record `HordeServer.Agents.Leases.LeaseCompleteTelemetry`  
`public record LeaseCompleteTelemetry : AbstractTelemetryRecord`  
_public; L20-187_
- attrs: `[AnalyticsTableGen] [Table("ingest.horde.state_lease_complete")]`
- inherits: `AbstractTelemetryRecord`
- desc: Telemetry record emitted when a lease completes. Models an ILease.
- L26 _public property_ `public LeaseId LeaseId { get; init; }` — attrs: `[Column("lease_id")]` — The lease id.
- L32 _public property_ `public LeaseId? ParentId { get; init; }` — attrs: `[Column("parent_id")]` — The parent lease id, if any.
- L38 _public property_ `public string Name { get; init; }` — attrs: `[Column("name")]` — Name of the lease.
- L44 _public property_ `public AgentId AgentId { get; init; }` — attrs: `[Column("agent_id")]` — The agent that executed the lease.
- L50 _public property_ `public SessionId SessionId { get; init; }` — attrs: `[Column("session_id")]` — The session in which the lease ran.
- L56 _public property_ `public StreamId? StreamId { get; init; }` — attrs: `[Column("stream_id")]` — The stream associated with the lease, if any.
- L62 _public property_ `public PoolId? PoolId { get; init; }` — attrs: `[Column("pool_id")]` — The pool associated with the lease, if any.
- L68 _public property_ `public LogId? LogId { get; init; }` — attrs: `[Column("log_id")]` — The log for this lease, if any.
- L74 _public property_ `public DateTime StartTimeUtc { get; init; }` — attrs: `[Column("start_time_utc")]` — Time at which the lease started.
- L80 _public property_ `public DateTime FinishTimeUtc { get; init; }` — attrs: `[Column("finish_time_utc")]` — Time at which the lease finished.
- L86 _public property_ `public double DurationSecs { get; init; }` — attrs: `[Column("duration_secs")]` — Duration of the lease in seconds.
- L92 _public property_ `public LeaseOutcome Outcome { get; init; }` — attrs: `[Column("outcome")]` — Outcome of the lease.
- L98 _public property_ `public LeaseOutcomeReason OutcomeReason { get; init; }` — attrs: `[Column("outcome_reason")]` — Reason for the outcome.
- L104 _public property_ `public double? SetupTimeSecs { get; init; }` — attrs: `[Column("setup_time_secs")]` — Time spent in setup, in seconds.
- L110 _public property_ `public double? TeardownTimeSecs { get; init; }` — attrs: `[Column("teardown_time_secs")]` — Time spent in teardown, in seconds.
- L116 _public property_ `public int? CpuCount { get; init; }` — attrs: `[Column("cpu_count")]` — Number of logical CPU cores available.
- L122 _public property_ `public double? GlobalCpuUtilization { get; init; }` — attrs: `[Column("global_cpu_utilization")]` — Machine-wide CPU utilization during the lease.
- L128 _public property_ `public double? CpuUserTimeSecs { get; init; }` — attrs: `[Column("cpu_user_time_secs")]` — Machine-wide user CPU time in seconds.
- L134 _public property_ `public double? CpuSystemTimeSecs { get; init; }` — attrs: `[Column("cpu_system_time_secs")]` — Machine-wide system CPU time in seconds.
- L140 _public property_ `public double? CpuIdleTimeSecs { get; init; }` — attrs: `[Column("cpu_idle_time_secs")]` — Machine-wide idle CPU time in seconds.
- L145 _public const_ `public const string DefaultEventName = "State.LeaseComplete"` — Default event name for this telemetry record.
- L150 _public field_ `public static readonly int CurrentSchemaVersion = 1` — Current schema version.
- L156-178 _public ctor_ `public LeaseCompleteTelemetry(ILease lease) : base(DefaultEventName, CurrentSchemaVersion)` — Constructs a lease completion telemetry event from a completed lease.
- L183-186 _public ctor_ `public LeaseCompleteTelemetry() : base(DefaultEventName, CurrentSchemaVersion)` — Default constructor for ORM mapping.

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Leases/LeasesController.cs` (HordeServer.Compute)


#### class `HordeServer.Agents.Leases.LeasesController`  
`public class LeasesController : HordeControllerBase`  
_public; L23-238_
- attrs: `[ApiController] [Authorize] [Route("[controller]")]`
- inherits: `HordeControllerBase`
- desc: Controller for the /api/v1/leases endpoint
- L25 _private* field_ `readonly AgentService _agentService`
- L26 _private* field_ `readonly IEnumerable<ITaskSource> _taskSources`
- L27 _private* field_ `readonly IOptionsSnapshot<ComputeConfig> _computeConfig`
- L28 _private* field_ `readonly Tracer _tracer`
- L33-39 _public ctor_ `public LeasesController(AgentService agentService, IEnumerable<ITaskSource> taskSources, IOptionsSnapshot<ComputeConfig> computeConfig, Tracer tracer)` — Constructor
- L58-108 _public method_ `public async Task<ActionResult<List<object>>> FindLeasesAsync( [FromQuery] AgentId? agentId, [FromQuery] SessionId? sessionId, [FromQuery] DateTimeOffset? startTime, [FromQuery] DateTimeOffset? finishTime, [FromQuery] DateTimeOffset? minFinishTime, [FromQuery] DateTimeOffset? maxFinishTime, [FromQuery] int index = 0, [FromQuery] int count = 1000, [FromQuery] PropertyFilter? filter = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/leases")] [ProducesResponseType(200, Type = typeof(List<GetAgentLeaseResponse>))]` — Find all the leases for a particular agent
- L118-140 _public method_ `public async Task<ActionResult<GetAgentLeaseResponse>> GetLeaseAsync(LeaseId leaseId, CancellationToken cancellationToken)` — attrs: `[HttpGet] [Route("/api/v1/leases/{leaseId}")]` — Get info about a particular lease
- L150-175 _public method_ `public async Task<ActionResult<object>> GetLeaseTaskAsync(LeaseId leaseId, CancellationToken cancellationToken)` — attrs: `[HttpGet] [Route("/api/v1/leases/{leaseId}/task")]` — Gets the protobuf task descriptor for a lease
- L186-205 _public method_ `public async Task<ActionResult> GetLeaseLogAsync(LeaseId leaseId, string? path = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/leases/{leaseId}/log/{*path}")]` — Get lease log, redirecting from lease id to log id
- L216-237 _public method_ `public async Task<ActionResult> UpdateLeaseAsync(LeaseId leaseId, [FromBody] UpdateLeaseRequest request, CancellationToken cancellationToken)` — attrs: `[HttpPut] [Route("/api/v1/leases/{leaseId}")]` — Update a particular lease

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Pools/IPool.cs` (HordeServer.Compute)


#### class `HordeServer.Agents.Pools.PoolSizeStrategyInfo`  
`public class PoolSizeStrategyInfo`  
_public; L14-72_
- desc: Metadata for configuring and picking a pool sizing strategy
- L19 _public property_ `public PoolSizeStrategy Type { get; set; }` — Strategy implementation to use
- L24 _public property_ `public Condition? Condition { get; set; }` — Condition if this strategy should be enabled (right now, using date/time as a distinguishing factor)
- L30 _public property_ `public JsonObject Config { get; set; }` — attrs: `[JsonConverter(typeof(JsonObjectOrStringConverter))]` — Configuration for the strategy, serialized as JSON
- L35 _public property_ `public int ExtraAgentCount { get; set; }` — Integer to add after pool size has been calculated. Can also be negative.
- L41-43 _public ctor_ `public PoolSizeStrategyInfo()` — attrs: `[JsonConstructor]` — Empty constructor for JSON serialization
- L48-53 _public ctor_ `public PoolSizeStrategyInfo(PoolSizeStrategy type, Condition? condition, int extraAgentCount = 0)` — Constructor
- L58-71 _public ctor_ `public PoolSizeStrategyInfo(PoolSizeStrategy type, Condition? condition, string config, int extraAgentCount = 0)` — Constructor

#### class `HordeServer.Agents.Pools.FleetManagerInfo`  
`public class FleetManagerInfo`  
_public; L77-128_
- desc: Metadata for configuring and picking a fleet manager
- L82 _public property_ `public FleetManagerType Type { get; set; }` — Fleet manager type implementation to use
- L87 _public property_ `public Condition? Condition { get; set; }` — Condition if this strategy should be enabled (right now, using date/time as a distinguishing factor)
- L93 _public property_ `public JsonObject? Config { get; set; }` — attrs: `[JsonConverter(typeof(JsonObjectOrStringConverter))]` — Configuration for the strategy, serialized as JSON
- L98-100 _public ctor_ `public FleetManagerInfo()` — Empty constructor for BSON/JSON serialization
- L106-110 _public ctor_ `public FleetManagerInfo(FleetManagerType type, Condition? condition)` — attrs: `[JsonConstructor]` — Constructor
- L115-127 _public ctor_ `public FleetManagerInfo(FleetManagerType type, Condition? condition, string config)` — Constructor

#### class `HordeServer.Agents.Pools.JsonObjectOrStringConverter`  
`class JsonObjectOrStringConverter : JsonConverter<JsonObject>`  
_internal*; L133-156_
- inherits: `JsonConverter<JsonObject>`
- desc: Allows parsing a string or json object into a native JsonObject instance
- L135 _private* field_ `static readonly JsonNodeOptions s_nodeOptions = new JsonNodeOptions { PropertyNameCaseInsensitive = true }`
- L136 _private* field_ `static readonly JsonDocumentOptions s_documentOptions = new JsonDocumentOptions { AllowTrailingCommas = true, CommentHandling = JsonCommentHandling.Skip }`
- L139-151 _public method_ `public override JsonObject? Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — (inheritdoc)
- L154 _public method_ `public override void Write(Utf8JsonWriter writer, JsonObject value, JsonSerializerOptions options)` — (inheritdoc)

#### interface `HordeServer.Agents.Pools.IPool`  
`public interface IPool : IPoolConfig`  
_public; L161-194_
- inherits: `IPoolConfig`
- desc: Pool of machines
- L166 _public property_ `public DateTime? LastScaleUpTime { get; }` — Last time the pool was (auto) scaled up
- L171 _public property_ `public DateTime? LastScaleDownTime { get; }` — Last time the pool was (auto) scaled down
- L176 _public property_ `public int? LastAgentCount { get; }` — Last known agent count
- L181 _public property_ `public int? LastDesiredAgentCount { get; }` — Last known desired agent count
- L186 _public property_ `public ScaleResult? LastScaleResult { get; }` — Last result from scaling the pool
- L193 _public* method_ `Task<IPool?> TryUpdateAsync(UpdatePoolOptions options, CancellationToken cancellationToken = default)` — Updates a pool

#### record `HordeServer.Agents.Pools.UpdatePoolOptions`  
`public record UpdatePoolOptions(DateTime? LastScaleUpTime = null, DateTime? LastScaleDownTime = null, ScaleResult? LastScaleResult = null, int? LastAgentCount = null, int? LastDesiredAgentCount = null)`  
_public; L204-204_
- desc: Settings for updating a pool state

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Pools/IPoolCollection.cs` (HordeServer.Compute)


#### interface `HordeServer.Agents.Pools.IPoolCollection`  
`public interface IPoolCollection`  
_public; L14-65_
- desc: Collection of pool documents
- L25 _public* method_ `Task CreateConfigAsync(PoolId id, string name, CreatePoolConfigOptions options, CancellationToken cancellationToken = default)` — attrs: `[Obsolete("Pools should be configured through globals.json")]` — Creates a new pool
- L32 _public* method_ `Task<IReadOnlyList<IPoolConfig>> GetConfigsAsync(CancellationToken cancellationToken = default)` — Enumerates all the pools
- L40 _public* method_ `Task<IPool?> GetAsync(PoolId id, CancellationToken cancellationToken = default)` — Gets a pool by ID
- L46 _public* method_ `Task<List<PoolId>> GetPoolIdsAsync(CancellationToken cancellationToken = default)` — Gets a list of all valid pool ids
- L55 _public* method_ `Task<bool> DeleteConfigAsync(PoolId id, CancellationToken cancellationToken = default)` — attrs: `[Obsolete("Pools should be configured through globals.json")]` — Gets a pool by ID
- L64 _public* method_ `Task<bool> UpdateConfigAsync(PoolId poolId, UpdatePoolConfigOptions options, CancellationToken cancellationToken = default)` — attrs: `[Obsolete("Pools should be configured through globals.json")]` — Updates a pool

#### class `HordeServer.Agents.Pools.CreatePoolConfigOptions`  
`public class CreatePoolConfigOptions`  
_public; L70-141_
- desc: Settings for creating a new pool
- L75 _public property_ `public Condition? Condition { get; set; }` — Condition for agents to be included in this pool
- L80 _public property_ `public bool? EnableAutoscaling { get; set; }` — Whether to enable autoscaling for this pool
- L85 _public property_ `public int? MinAgents { get; set; }` — Minimum number of agents in the pool
- L90 _public property_ `public int? NumReserveAgents { get; set; }` — Minimum number of idle agents to maintain
- L95 _public property_ `public TimeSpan? ConformInterval { get; set; }` — Interval between conforms. Set to zero to disable.
- L100 _public property_ `public TimeSpan? ScaleOutCooldown { get; set; }` — Cooldown time between scale-out events
- L105 _public property_ `public TimeSpan? ScaleInCooldown { get; set; }` — Cooldown time between scale-in events
- L110 _public property_ `public List<PoolSizeStrategyInfo>? SizeStrategies { get; set; }` — Pool sizing strategies
- L115 _public property_ `public List<FleetManagerInfo>? FleetManagers { get; set; }` — Fleet managers
- L120 _public property_ `public PoolSizeStrategy? SizeStrategy { get; set; }` — Pool sizing strategy
- L125 _public property_ `public LeaseUtilizationSettings? LeaseUtilizationSettings { get; set; }` — Settings for lease utilization strategy
- L130 _public property_ `public JobQueueSettings? JobQueueSettings { get; set; }` — Settings for job queue strategy
- L135 _public property_ `public ComputeQueueAwsMetricSettings? ComputeQueueAwsMetricSettings { get; set; }` — Settings for compute queue AWS metric strategy
- L140 _public property_ `public IEnumerable<KeyValuePair<string, string>>? Properties { get; set; }` — Properties for the pool

#### class `HordeServer.Agents.Pools.UpdatePoolConfigOptions`  
`public class UpdatePoolConfigOptions`  
_public; L146-242_
- desc: Settings for updating a pool state
- L151 _public property_ `public string? Name { get; set; }` — New name for the pool
- L156 _public property_ `public Condition? Condition { get; set; }` — New condition for the pool
- L161 _public property_ `public bool? EnableAutoscaling { get; set; }` — New setting for whether to enable autoscaling
- L166 _public property_ `public int? MinAgents { get; set; }` — Minimum number of agents in the pool
- L171 _public property_ `public int? NumReserveAgents { get; set; }` — Minimum number of idle agents to maintain
- L176 _public property_ `public List<AgentWorkspaceInfo>? Workspaces { get; set; }` — New workspaces for the pool
- L181 _public property_ `public AutoSdkConfig? AutoSdkConfig { get; set; }` — Settings for the autosdk workspace
- L186 _public property_ `public Dictionary<string, string?>? Properties { get; set; }` — New properties for the pool
- L191 _public property_ `public TimeSpan? ConformInterval { get; set; }` — Interval between conforms. Set to zero to disable.
- L196 _public property_ `public TimeSpan? ScaleOutCooldown { get; set; }` — Cooldown time between scale-out events
- L201 _public property_ `public TimeSpan? ScaleInCooldown { get; set; }` — Cooldown time between scale-in events
- L206 _public property_ `public TimeSpan? ShutdownIfDisabledGracePeriod { get; set; }` — Time to wait before shutting down a disabled agent
- L211 _public property_ `public PoolSizeStrategy? SizeStrategy { get; set; }` — Pool sizing strategy
- L216 _public property_ `public List<PoolSizeStrategyInfo>? SizeStrategies { get; set; }` — List of pool sizing strategies
- L221 _public property_ `public List<FleetManagerInfo>? FleetManagers { get; set; }` — List of fleet managers
- L226 _public property_ `public LeaseUtilizationSettings? LeaseUtilizationSettings { get; set; }` — Settings for lease utilization strategy
- L231 _public property_ `public JobQueueSettings? JobQueueSettings { get; set; }` — Settings for job queue strategy
- L236 _public property_ `public ComputeQueueAwsMetricSettings? ComputeQueueAwsMetricSettings { get; set; }` — Settings for compute queue AWS metric strategy
- L241 _public property_ `public bool? UseDefaultStrategy { get; set; }` — Whether to use the default strategy

#### class `HordeServer.Agents.Pools.PoolConflictException`  
`public sealed class PoolConflictException : Exception`  
_public; L247-274_
- inherits: `Exception`
- desc: Exception when conflicting definitions for a pool are encountered
- L252 _public property_ `public PoolId PoolId { get; }` — Pool with conflicting definitions
- L257 _public property_ `public string PrevRevision { get; }` — The first revision string
- L262 _public property_ `public string NextRevision { get; }` — The second revision string
- L267-273 _public ctor_ `public PoolConflictException(PoolId poolId, string prevRevision, string nextRevision) : base($"Duplicate definitions for {poolId} - first in {prevRevision}, now {nextRevision}")` — Constructor

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Pools/PoolAclAction.cs` (HordeServer.Compute)


#### class `HordeServer.Agents.Pools.PoolAclAction`  
`public static class PoolAclAction`  
_public; L10-36_
- desc: ACL actions for pools
- L15 _public property_ `public static AclAction CreatePool { get; }` — Create a global pool of agents
- L20 _public property_ `public static AclAction UpdatePool { get; }` — Modify an agent pool
- L25 _public property_ `public static AclAction DeletePool { get; }` — Delete an agent pool
- L30 _public property_ `public static AclAction ViewPool { get; }` — Ability to view a pool
- L35 _public property_ `public static AclAction ListPools { get; }` — View all the available agent pools

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Pools/PoolCollection.cs` (HordeServer.Compute)


#### class `HordeServer.Agents.Pools.PoolCollection`  
`public class PoolCollection : IPoolCollection`  
_public; L18-545_
- inherits: `IPoolCollection`
- desc: Collection of pool documents
- L220 _private* field_ `readonly IOptionsMonitor<ComputeConfig> _computeConfig`
- L221 _private* field_ `readonly IMongoCollection<PoolDocumentV1> _poolsV1`
- L222 _private* field_ `readonly IMongoCollection<PoolDocumentV2> _poolsV2`
- L229-234 _public ctor_ `public PoolCollection(IMongoService mongoService, IOptionsMonitor<ComputeConfig> computeConfig)` — Constructor
- L237-271 _public method_ `public async Task CreateConfigAsync(PoolId id, string name, CreatePoolConfigOptions options, CancellationToken cancellationToken = default)` — (inheritdoc)
- L274-287 _public method_ `public async Task<IReadOnlyList<IPoolConfig>> GetConfigsAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L290-340 _public method_ `public async Task<IPool?> GetAsync(PoolId id, CancellationToken cancellationToken)` — (inheritdoc)
- L343-359 _public method_ `public async Task<List<PoolId>> GetPoolIdsAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L362-367 _public method_ `public async Task<bool> DeleteConfigAsync(PoolId id, CancellationToken cancellationToken)` — (inheritdoc)
- L370-515 _public method_ `public async Task<bool> UpdateConfigAsync(PoolId poolId, UpdatePoolConfigOptions options, CancellationToken cancellationToken)` — (inheritdoc)
- L517-544 _private* method_ `async Task<PoolDocumentV2> UpdateStateAsync(PoolDocumentV2 document, UpdatePoolOptions options, CancellationToken cancellationToken)`

#### class `HordeServer.Agents.Pools.PoolCollection.PoolDocumentV1`  
`class PoolDocumentV1 : IPoolConfig`  
_private*; L21-137_
- inherits: `IPoolConfig`
- L24 _public property_ `public PoolId Id { get; set; }` — attrs: `[BsonId]`
- L27 _public property_ `public string Name { get; set; }` — attrs: `[BsonRequired]`
- L30 _public property_ `public Condition? Condition { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L32 _public property_ `public List<AgentWorkspaceInfo> Workspaces { get; set; }`
- L34 _private* property_ `PoolColor IPoolConfig.Color => ...`
- L35 _private* property_ `IReadOnlyList<AgentWorkspaceInfo> IPoolConfig.Workspaces => ...`
- L38 _public property_ `public AutoSdkConfig? AutoSdkConfig { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L40 _public property_ `public Dictionary<string, string> Properties { get; set; }`
- L43 _public property_ `public bool EnableAutoscaling { get; set; }` — attrs: `[BsonIgnoreIfDefault, BsonDefaultValue(true)]`
- L46 _public property_ `public int? MinAgents { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L49 _public property_ `public int? NumReserveAgents { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L52 _public property_ `public TimeSpan? ConformInterval { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L55 _public property_ `public DateTime? LastScaleUpTime { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L58 _public property_ `public DateTime? LastScaleDownTime { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L61 _public property_ `public TimeSpan? ScaleOutCooldown { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L64 _public property_ `public TimeSpan? ScaleInCooldown { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L67 _public property_ `public TimeSpan? ShutdownIfDisabledGracePeriod { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L70 _public property_ `public ScaleResult? LastScaleResult { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L73 _public property_ `public int? LastAgentCount { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L76 _public property_ `public int? LastDesiredAgentCount { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L79 _public property_ `public PoolSizeStrategy? SizeStrategy { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L82 _public property_ `public List<PoolSizeStrategyInfo>? SizeStrategies { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L85 _public property_ `public List<FleetManagerInfo>? FleetManagers { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L88 _public property_ `public LeaseUtilizationSettings? LeaseUtilizationSettings { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L91 _public property_ `public JobQueueSettings? JobQueueSettings { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L94 _public property_ `public ComputeQueueAwsMetricSettings? ComputeQueueAwsMetricSettings { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L97 _public property_ `public string? Revision { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L99 _public property_ `public int UpdateIndex { get; set; }`
- L101 _private* property_ `IReadOnlyDictionary<string, string> IPoolConfig.Properties => ...`
- L102 _private* property_ `IReadOnlyList<PoolSizeStrategyInfo> IPoolConfig.SizeStrategies => ...`
- L103 _private* property_ `IReadOnlyList<FleetManagerInfo> IPoolConfig.FleetManagers => ...`
- L105-107 _public ctor_ `public PoolDocumentV1()`
- L109-136 _public ctor_ `public PoolDocumentV1(IPoolConfig other, string? otherRevision)`

#### class `HordeServer.Agents.Pools.PoolCollection.PoolDocumentV2`  
`class PoolDocumentV2`  
_private*; L139-160_
- L142 _public property_ `public PoolId Id { get; set; }` — attrs: `[BsonId]`
- L145 _public property_ `public DateTime? LastScaleUpTime { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L148 _public property_ `public DateTime? LastScaleDownTime { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L151 _public property_ `public ScaleResult? LastScaleResult { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L154 _public property_ `public int? LastAgentCount { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L157 _public property_ `public int? LastDesiredAgentCount { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L159 _public property_ `public int UpdateIndex { get; set; }`

#### class `HordeServer.Agents.Pools.PoolCollection.Pool`  
`class Pool : IPool`  
_private*; L162-218_
- inherits: `IPool`
- L164 _private* field_ `readonly PoolCollection _collection`
- L165 _private* field_ `readonly IPoolConfig _config`
- L166 _private* field_ `readonly PoolDocumentV2 _document`
- L168-173 _public ctor_ `public Pool(PoolCollection collection, IPoolConfig config, PoolDocumentV2 document)`
- L175 _public property_ `public PoolId Id => ...`
- L176 _public property_ `public DateTime? LastScaleUpTime => ...`
- L177 _public property_ `public DateTime? LastScaleDownTime => ...`
- L178 _public property_ `public int? LastAgentCount => ...`
- L179 _public property_ `public int? LastDesiredAgentCount => ...`
- L180 _public property_ `public ScaleResult? LastScaleResult => ...`
- L181 _public property_ `public int UpdateIndex => ...`
- L185 _public property_ `public string Name => ...`
- L186 _public property_ `public Condition? Condition => ...`
- L187 _public property_ `public IReadOnlyDictionary<string, string>? Properties => ...`
- L188 _public property_ `public PoolColor Color => ...`
- L189 _public property_ `public bool EnableAutoscaling => ...`
- L190 _public property_ `public IReadOnlyList<AgentWorkspaceInfo> Workspaces => ...`
- L191 _public property_ `public AutoSdkConfig? AutoSdkConfig => ...`
- L192 _public property_ `public TimeSpan? ScaleOutCooldown => ...`
- L193 _public property_ `public TimeSpan? ScaleInCooldown => ...`
- L194 _public property_ `public int? MinAgents => ...`
- L195 _public property_ `public int? NumReserveAgents => ...`
- L196 _public property_ `public TimeSpan? ConformInterval => ...`
- L197 _public property_ `public TimeSpan? ShutdownIfDisabledGracePeriod => ...`
- L200 _public property_ `public PoolSizeStrategy? SizeStrategy => ...` — attrs: `[Obsolete]`
- L202 _public property_ `public IReadOnlyList<PoolSizeStrategyInfo>? SizeStrategies => ...`
- L203 _public property_ `public IReadOnlyList<FleetManagerInfo>? FleetManagers => ...`
- L204 _public property_ `public LeaseUtilizationSettings? LeaseUtilizationSettings => ...`
- L205 _public property_ `public JobQueueSettings? JobQueueSettings => ...`
- L209-217 _public method_ `public async Task<IPool?> TryUpdateAsync(UpdatePoolOptions options, CancellationToken cancellationToken)`

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Pools/PoolCondition.cs` (HordeServer.Compute)


#### class `HordeServer.Agents.Pools.PoolPropertyNames`  
`static class PoolPropertyNames`  
_internal*; L11-57_
- desc: Defined pool property names, for use in dashboard filter expressions
- L16 _public const_ `public const string Id = "Id"` — Identifier for the pool
- L21 _public const_ `public const string NumAgents = "NumAgents"` — Number of agents which are in the pool
- L26 _public const_ `public const string NumOnline = "NumOnline"` — Number of agents in the pool which are online
- L31 _public const_ `public const string NumOffline = "NumOffline"` — Number of agents in the pool which are offline
- L36 _public const_ `public const string NumEnabled = "NumEnabled"` — Number of agents in the pool which are enabled
- L41 _public const_ `public const string NumDisabled = "NumDisabled"` — Number of agents in the pool which are disabled
- L46 _public const_ `public const string NumBusy = "NumBusy"` — Number of agents in the pool which are currently executing work
- L51 _public const_ `public const string NumIdle = "NumIdle"` — Number of agents in the pool which are idle
- L56 _public const_ `public const string PropertiesPrefix = "Properties."` — Prefix for properties within the pool configuration

#### class `HordeServer.Agents.Pools.PoolInfo`  
`class PoolInfo`  
_internal*; L62-96_
- desc: Information about a pool
- L64 _public property_ `public int NumAgents { get; set; }`
- L65 _public property_ `public int NumIdle { get; set; }`
- L66 _public property_ `public int NumBusy { get; set; }`
- L67 _public property_ `public int NumOffline { get; set; }`
- L68 _public property_ `public int NumDisabled { get; set; }`
- L69 _public property_ `public List<IAgent>? Agents { get; set; }`
- L70 _public property_ `public List<double>? Utilization { get; set; }`
- L72-95 _public method_ `public void AddAgent(IAgent agent, DateTime utcNow)`

#### class `HordeServer.Agents.Pools.PoolCondition`  
`static class PoolCondition`  
_internal*; L101-148_
- desc: Static methods for querying pools
- L106-109 _public method_ `public static bool Evaluate(Condition condition, IPoolConfig poolConfig, PoolInfo? poolInfo)` — Check whether a pool satisfies a condition
- L111-130 _private* method_ `static IEnumerable<string> GetPoolProperties(string name, IPoolConfig poolConfig, PoolInfo? poolInfo)`
- L132 _private* field_ `static readonly Dictionary<string, Func<IPoolConfig, PoolInfo?, string>> s_poolPropertyHandlers = ...`
- L132 _private* field_ `static readonly Dictionary< IPoolConfig`
- L132 _private* field_ `static readonly Dictionary< PoolInfo`
- L132 _private* field_ `static readonly Dictionary< s_poolPropertyHandlers = CreatePoolPropertyHandlers()`
- L134-144 _private* method_ `static Dictionary<string, Func<IPoolConfig, PoolInfo?, string>> CreatePoolPropertyHandlers()`
- L146 _private* method_ `static PoolInfo MustDeref(PoolInfo? poolInfo)`

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Pools/PoolConfig.cs` (HordeServer.Compute)


#### enum `HordeServer.Agents.Pools.PoolColor`  
`public enum PoolColor`  
_public; L20-29_
- desc: Color to use for labels of this pool
- L23 _public* enumerator_ `Default = 0`
- L24 _public* enumerator_ `Blue`
- L25 _public* enumerator_ `Orange`
- L26 _public* enumerator_ `Green`
- L27 _public* enumerator_ `Gray`

#### interface `HordeServer.Agents.Pools.IPoolConfig`  
`public interface IPoolConfig`  
_public; L34-130_
- desc: Configuration for a pool of machines
- L39 _public* property_ `PoolId Id { get; }` — Unique id for this pool
- L44 _public* property_ `string Name { get; }` — Name of the pool
- L49 _public* property_ `Condition? Condition { get; }` — Condition for agents to automatically be included in this pool
- L54 _public* property_ `PoolColor Color { get; }` — Color to use for this pool on the dashboard
- L59 _public* property_ `IReadOnlyList<AgentWorkspaceInfo> Workspaces { get; }` — List of workspaces currently assigned to this pool
- L64 _public* property_ `IReadOnlyDictionary<string, string>? Properties { get; }` — Arbitrary properties related to this pool
- L69 _public* property_ `bool EnableAutoscaling { get; }` — Whether to enable autoscaling for this pool
- L74 _public* property_ `AutoSdkConfig? AutoSdkConfig { get; }` — AutoSDK view for this pool
- L79 _public* property_ `TimeSpan? ScaleOutCooldown { get; }` — Cooldown time between scale-out events
- L84 _public* property_ `TimeSpan? ScaleInCooldown { get; }` — Cooldown time between scale-in events
- L89 _public* property_ `int? MinAgents { get; }` — The minimum number of agents to keep in the pool
- L94 _public* property_ `int? NumReserveAgents { get; }` — The minimum number of idle agents to hold in reserve
- L99 _public* property_ `TimeSpan? ConformInterval { get; }` — Interval between conforms. If zero, the pool will not conform on a schedule.
- L104 _public* property_ `TimeSpan? ShutdownIfDisabledGracePeriod { get; }` — Time to wait before shutting down an agent that has been disabled
- L108 _public* property_ `PoolSizeStrategy? SizeStrategy { get; }` — attrs: `[Obsolete("Use SizeStrategies instead")]` — (inheritdoc)
- L113 _public* property_ `IReadOnlyList<PoolSizeStrategyInfo>? SizeStrategies { get; }` — List of pool sizing strategies for this pool. The first strategy with a matching condition will be picked.
- L119 _public* property_ `IReadOnlyList<FleetManagerInfo>? FleetManagers { get; }` — List of fleet managers for this pool. The first strategy with a matching condition will be picked. If empty or no conditions match, a default fleet manager will be used.
- L124 _public* property_ `LeaseUtilizationSettings? LeaseUtilizationSettings { get; }` — Settings for lease utilization pool sizing strategy (if used)
- L129 _public* property_ `JobQueueSettings? JobQueueSettings { get; }` — Settings for job queue pool sizing strategy (if used)

#### class `HordeServer.Agents.Pools.PoolConfig`  
`public class PoolConfig : IPoolConfig`  
_public; L136-227_
- attrs: `[DebuggerDisplay("{Id}")]`
- inherits: `IPoolConfig`
- desc: Mutable configuration for a pool
- L138 _private* field_ `PoolId _id`
- L141-145 _public property_ `public PoolId Id { get; set; }` — (inheritdoc)
- L150 _public property_ `public PoolId? Base { get; set; }` — Base pool config to copy settings from
- L153 _public property_ `public string Name { get; set; }` — (inheritdoc)
- L156 _public property_ `public Condition? Condition { get; set; }` — (inheritdoc)
- L159 _public property_ `public Dictionary<string, string>? Properties { get; set; }` — (inheritdoc)
- L162 _private* property_ `IReadOnlyDictionary<string, string>? IPoolConfig.Properties => ...` — (inheritdoc)
- L165 _public property_ `public PoolColor? Color { get; set; }` — (inheritdoc)
- L167 _private* property_ `PoolColor IPoolConfig.Color => ...`
- L171 _public property_ `public List<AgentWorkspaceInfo> Workspaces { get; set; }` — attrs: `[JsonIgnore]` — (inheritdoc)
- L173 _private* property_ `IReadOnlyList<AgentWorkspaceInfo> IPoolConfig.Workspaces => ...`
- L176 _public property_ `public bool? EnableAutoscaling { get; set; }` — (inheritdoc)
- L179 _private* property_ `bool IPoolConfig.EnableAutoscaling => ...` — (inheritdoc)
- L183 _public property_ `public AutoSdkConfig? AutoSdkConfig { get; set; }` — attrs: `[JsonIgnore]` — (inheritdoc)
- L186 _public property_ `public int? MinAgents { get; set; }` — (inheritdoc)
- L189 _public property_ `public int? NumReserveAgents { get; set; }` — (inheritdoc)
- L192 _public property_ `public TimeSpan? ConformInterval { get; set; }` — (inheritdoc)
- L195 _public property_ `public TimeSpan? ScaleOutCooldown { get; set; }` — (inheritdoc)
- L198 _public property_ `public TimeSpan? ScaleInCooldown { get; set; }` — (inheritdoc)
- L201 _public property_ `public TimeSpan? ShutdownIfDisabledGracePeriod { get; set; }` — (inheritdoc)
- L205 _public property_ `public PoolSizeStrategy? SizeStrategy { get; set; }` — attrs: `[Obsolete("Use SizeStrategies instead")]` — (inheritdoc)
- L208 _public property_ `public List<PoolSizeStrategyInfo>? SizeStrategies { get; set; }` — (inheritdoc)
- L211 _private* property_ `IReadOnlyList<PoolSizeStrategyInfo>? IPoolConfig.SizeStrategies => ...` — (inheritdoc)
- L214 _public property_ `public List<FleetManagerInfo>? FleetManagers { get; set; }` — (inheritdoc)
- L217 _private* property_ `IReadOnlyList<FleetManagerInfo>? IPoolConfig.FleetManagers => ...` — (inheritdoc)
- L220 _public property_ `public LeaseUtilizationSettings? LeaseUtilizationSettings { get; set; }` — (inheritdoc)
- L223 _public property_ `public JobQueueSettings? JobQueueSettings { get; set; }` — (inheritdoc)
- L226 _public property_ `public ComputeQueueAwsMetricSettings? ComputeQueueAwsMetricSettings { get; set; }` — (inheritdoc)

#### class `HordeServer.Agents.Pools.PoolConfigExtensions`  
`public static class PoolConfigExtensions`  
_public; L232-346_
- desc: Extension methods for IPool
- L242 _private* field_ `static readonly RgbColor[] s_colorTable = { new RgbColor(0x00, 0xbc, 0xf2), new RgbColor(0x5a, 0xc9, 0x5a), new RgbColor(0xff, 0x66, 0x00), new RgbColor(0xdf, 0x8b, 0xe5), new RgbColor(0x00, 0xbc, 0xf2), }`
- L251 _private* field_ `static readonly Dictionary<PoolColor, RgbColor[]> s_colorNameToTable = ...`
- L251 _private* field_ `static readonly Dictionary< s_colorNameToTable = new Dictionary<PoolColor, RgbColor[]>() { [PoolColor.Blue] = new[] { new RgbColor(0x00, 0x80, 0xf2), new RgbColor(0x00, 0xbc, 0xf2), }, [PoolColor.Orange] = new[] { new RgbColor(0xff, 0x70, 0x00), new ...`
- L278-297 _public method_ `public static string GetColorValue(this IPoolConfig poolConfig)` — Gets the color for a pool
- L299-308 _private* method_ `static string GetColorValue(float slider, RgbColor[] colorTable)`
- L316-327 _public method_ `public static bool SatisfiesCondition(this IPoolConfig poolConfig, Condition condition)` — Evaluates a condition against a pool
- L337-345 _public method_ `public static bool MeetsRequirements(this IPoolConfig poolConfig, Requirements requirements)` — Determine whether a pool offers agents that are compatible with the given requirements. Since a pool does not have beforehand knowledge of what type of agents will be created, their expected properties must be specified on the IPool.

#### record struct `HordeServer.Agents.Pools.PoolConfigExtensions.RgbColor`  
`record struct RgbColor(byte R, byte G, byte B)`  
_private*; L234-240_
- L236 _public method_ `public static RgbColor Lerp(RgbColor lhs, RgbColor rhs, float t)`
- L239 _public method_ `public string ToHexString()`

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Pools/PoolMessages.cs` (HordeServer.Compute)


#### class `HordeServer.Agents.Pools.PoolSizeStrategyMessage`  
`public class PoolSizeStrategyMessage`  
_public; L15-64_
- desc: PoolSizeStrategyInfo
- L20 _public property_ `public PoolSizeStrategy Type { get; set; }` — Strategy implementation to use
- L25 _public property_ `public Condition? Condition { get; set; }` — Condition if this strategy should be enabled (right now, using date/time as a distinguishing factor)
- L30 _public property_ `public JsonObject Config { get; set; }` — Configuration for the strategy, serialized as JSON
- L35 _public property_ `public int ExtraAgentCount { get; set; }` — Integer to add after pool size has been calculated. Can also be negative.
- L40-42 _public ctor_ `public PoolSizeStrategyMessage()` — Empty constructor for JSON serialization
- L48-54 _public ctor_ `public PoolSizeStrategyMessage(PoolSizeStrategyInfo strategy)` — Construct a public REST API representation from the internal one
- L60-63 _public method_ `public PoolSizeStrategyInfo Convert()` — Convert this public REST API object to an internal representation

#### class `HordeServer.Agents.Pools.FleetManagerMessage`  
`public class FleetManagerMessage`  
_public; L67-110_
- desc: FleetManagerInfo
- L72 _public property_ `public FleetManagerType Type { get; set; }` — Strategy implementation to use
- L77 _public property_ `public Condition? Condition { get; set; }` — Condition if this strategy should be enabled (right now, using date/time as a distinguishing factor)
- L82 _public property_ `public JsonObject? Config { get; set; }` — Configuration for the strategy, serialized as JSON
- L87-89 _public ctor_ `public FleetManagerMessage()` — Empty constructor for JSON serialization
- L95-100 _public ctor_ `public FleetManagerMessage(FleetManagerInfo info)` — Construct a public REST API representation from the internal one
- L106-109 _public method_ `public FleetManagerInfo Convert()` — Convert this public REST API object to an internal representation

#### class `HordeServer.Agents.Pools.LeaseUtilizationSettingsMessage`  
`public class LeaseUtilizationSettingsMessage`  
_public; L113-134_
- desc: LeaseUtilizationSettings
- L120-123 _public ctor_ `public LeaseUtilizationSettingsMessage(LeaseUtilizationSettings settings)` — Construct a public REST API representation from the internal one
- L129-133 _public method_ `public LeaseUtilizationSettings Convert()` — Convert this public REST API object to an internal representation

#### class `HordeServer.Agents.Pools.JobQueueSettingsMessage`  
`public class JobQueueSettingsMessage`  
_public; L137-178_
- desc: JobQueueSettings
- L144 _public property_ `public double ScaleOutFactor { get; set; }` — Factor translating queue size to additional agents to grow the pool with The result is always rounded up to nearest integer. Example: if there are 20 jobs in queue, a factor 0.25 will result in 5 new agents being added (20 * 0.25)
- L151 _public property_ `public double ScaleInFactor { get; set; }` — Factor by which to shrink the pool size with when queue is empty The result is always rounded up to nearest integer. Example: when the queue size is zero, a default value of 0.9 will shrink the pool by 10% (current agent count * 0.9)
- L156-158 _public ctor_ `public JobQueueSettingsMessage()` — Constructor
- L164-168 _public ctor_ `public JobQueueSettingsMessage(JobQueueSettings settings)` — Construct a public REST API representation from the internal one
- L174-177 _public method_ `public JobQueueSettings Convert()` — Convert this public REST API object to an internal representation

#### class `HordeServer.Agents.Pools.ComputeQueueAwsMetricSettingsMessage`  
`public class ComputeQueueAwsMetricSettingsMessage`  
_public; L181-218_
- desc: ComputeQueueAwsMetricSettings
- L186 _public property_ `public string ComputeClusterId { get; set; }` — Compute cluster ID to observe
- L191 _public property_ `public string Namespace { get; set; }` — AWS CloudWatch namespace to write metrics in
- L196-198 _public ctor_ `public ComputeQueueAwsMetricSettingsMessage()` — Constructor
- L204-208 _public ctor_ `public ComputeQueueAwsMetricSettingsMessage(ComputeQueueAwsMetricSettings settings)` — Construct a public REST API representation from the internal one
- L214-217 _public method_ `public ComputeQueueAwsMetricSettings Convert()` — Convert this public REST API object to an internal representation

#### class `HordeServer.Agents.Pools.CreatePoolRequest`  
`public class CreatePoolRequest`  
_public; L223-300_
- desc: Parameters to create a new pool
- L229 _public property_ `public string Name { get; set; }` — attrs: `[Required]` — Name for the new pool
- L234 _public property_ `public Condition? Condition { get; set; }` — Condition to satisfy for agents to be included in this pool
- L239 _public property_ `public bool? EnableAutoscaling { get; set; }` — Whether to enable autoscaling for this pool
- L244 _public property_ `public int? ConformInterval { get; set; }` — Interval between conforms in hours. Set to zero to disable.
- L249 _public property_ `public int? ScaleOutCooldown { get; set; }` — Cooldown time between scale-out events in seconds
- L254 _public property_ `public int? ScaleInCooldown { get; set; }` — Cooldown time between scale-in events in seconds
- L259 _public property_ `public List<PoolSizeStrategyMessage>? SizeStrategies { get; set; }` — Pool sizing strategies
- L264 _public property_ `public List<FleetManagerMessage>? FleetManagers { get; set; }` — Fleet managers
- L269 _public property_ `public PoolSizeStrategy? SizeStrategy { get; set; }` — Pool sizing strategy
- L274 _public property_ `public LeaseUtilizationSettingsMessage? LeaseUtilizationSettings { get; set; }` — Settings for lease utilization pool sizing strategy (if used)
- L279 _public property_ `public JobQueueSettingsMessage? JobQueueSettings { get; set; }` — Settings for job queue pool sizing strategy (if used)
- L284 _public property_ `public ComputeQueueAwsMetricSettingsMessage? ComputeQueueAwsMetricSettings { get; set; }` — Settings for compute queue pool sizing strategy for AWS metrics (if used)
- L289 _public property_ `public int? MinAgents { get; set; }` — The minimum number of agents to retain in this pool
- L294 _public property_ `public int? NumReserveAgents { get; set; }` — The minimum number of idle agents in this pool, if autoscaling is enabled
- L299 _public property_ `public Dictionary<string, string>? Properties { get; set; }` — Properties for the new pool

#### class `HordeServer.Agents.Pools.CreatePoolResponse`  
`public class CreatePoolResponse`  
_public; L305-320_
- desc: Response from creating a new pool
- L310 _public property_ `public string Id { get; set; }` — Unique id for the new pool
- L316-319 _public ctor_ `public CreatePoolResponse(string id)` — Constructor

#### class `HordeServer.Agents.Pools.UpdatePoolRequest`  
`public class UpdatePoolRequest`  
_public; L325-406_
- desc: Parameters to update a pool
- L330 _public property_ `public string? Name { get; set; }` — Optional new name for the pool
- L335 _public property_ `public Condition? Condition { get; set; }` — Requirements for this pool
- L340 _public property_ `public bool? EnableAutoscaling { get; set; }` — Whether to enable autoscaling for this pool
- L345 _public property_ `public int? ConformInterval { get; set; }` — Interval between conforms in hours. Set to -1 to reset to the default, or 0 to disable.
- L350 _public property_ `public int? ScaleOutCooldown { get; set; }` — Cooldown time between scale-out events in seconds
- L355 _public property_ `public int? ScaleInCooldown { get; set; }` — Cooldown time between scale-in events in seconds
- L360 _public property_ `public PoolSizeStrategy? SizeStrategy { get; set; }` — Pool sizing strategy
- L365 _public property_ `public List<PoolSizeStrategyMessage>? SizeStrategies { get; set; }` — Pool sizing strategies
- L370 _public property_ `public List<FleetManagerMessage>? FleetManagers { get; set; }` — Fleet managers
- L375 _public property_ `public bool? UseDefaultStrategy { get; set; }` — Set pool to use default strategy
- L380 _public property_ `public LeaseUtilizationSettingsMessage? LeaseUtilizationSettings { get; set; }` — Settings for lease utilization pool sizing strategy (if used)
- L385 _public property_ `public JobQueueSettingsMessage? JobQueueSettings { get; set; }` — Settings for job queue pool sizing strategy (if used)
- L390 _public property_ `public ComputeQueueAwsMetricSettingsMessage? ComputeQueueAwsMetricSettings { get; set; }` — Settings for compute queue AWS metric pool sizing strategy (if used)
- L395 _public property_ `public int? MinAgents { get; set; }` — The minimum number of agents to retain in this pool
- L400 _public property_ `public int? NumReserveAgents { get; set; }` — The minimum number of idle agents in this pool, if autoscaling is enabled
- L405 _public property_ `public Dictionary<string, string?>? Properties { get; set; }` — Properties to update for the pool. Properties set to null will be removed.

#### class `HordeServer.Agents.Pools.BatchUpdatePoolRequest`  
`public class BatchUpdatePoolRequest`  
_public; L411-428_
- desc: Parameters to update a pool
- L417 _public property_ `public string Id { get; set; }` — attrs: `[Required]` — ID of the pool to update
- L422 _public property_ `public string? Name { get; set; }` — Optional new name for the pool
- L427 _public property_ `public Dictionary<string, string?>? Properties { get; set; }` — Properties to update for the pool. Properties set to null will be removed.

#### class `HordeServer.Agents.Pools.GetPoolResponse`  
`public class GetPoolResponse`  
_public; L433-577_
- desc: Response describing a pool
- L438 _public property_ `public string Id { get; set; }` — Unique id of the pool
- L443 _public property_ `public string Name { get; set; }` — Name of the pool
- L448 _public property_ `public Condition? Condition { get; set; }` — Condition for agents to be auto-added to the pool
- L453 _public property_ `public string ColorValue { get; set; }` — Color to display for this pool
- L458 _public property_ `public bool EnableAutoscaling { get; set; }` — Whether to enable autoscaling for this pool
- L463 _public property_ `public int? ConformInterval { get; set; }` — Frequency to run conforms, in hours.
- L468 _public property_ `public int? ScaleOutCooldown { get; set; }` — Cooldown time between scale-out events in seconds
- L473 _public property_ `public int? ScaleInCooldown { get; set; }` — Cooldown time between scale-in events in seconds
- L478 _public property_ `public List<PoolSizeStrategyMessage> SizeStrategies { get; set; }` — Pool sizing strategies to be used for this pool
- L483 _public property_ `public List<FleetManagerMessage> FleetManagers { get; set; }` — Fleet managers to be used for this pool
- L488 _public property_ `public PoolSizeStrategy? SizeStrategy { get; set; }` — Pool sizing strategy to be used for this pool (deprecated, see SizeStrategies field)
- L493 _public property_ `public LeaseUtilizationSettingsMessage? LeaseUtilizationSettings { get; set; }` — Settings for lease utilization pool sizing strategy (deprecated, see SizeStrategies field)
- L498 _public property_ `public JobQueueSettingsMessage? JobQueueSettings { get; set; }` — Settings for job queue pool sizing strategy (deprecated, see SizeStrategies field)
- L503 _public property_ `public ComputeQueueAwsMetricSettingsMessage? ComputeQueueAwsMetricSettings { get; set; }` — Settings for compute queue pool sizing strategy for AWS metrics (deprecated, see SizeStrategies field)
- L508 _public property_ `public int? MinAgents { get; set; }` — The minimum nunmber of agents to retain in this pool
- L513 _public property_ `public int? NumReserveAgents { get; set; }` — The minimum number of idle agents in this pool, if autoscaling is enabled
- L518 _public property_ `public TimeSpan? ShutdownIfDisabledGracePeriod { get; set; }` — Time to wait before shutting down an agent that has been disabled
- L523 _public property_ `public List<GetAgentWorkspaceResponse> Workspaces { get; set; }` — List of workspaces that this agent contains
- L528 _public property_ `public AutoSdkConfig? AutoSdkConfig { get; set; }` — AutoSDK configuration for the pool
- L533 _public property_ `public IReadOnlyDictionary<string, string> Properties { get; set; }` — Arbitrary properties for this pool.
- L540 _public property_ `public bool? ConfigManaged { get; set; }` — Whether this pool is managed via config files (true) or the database (false). Null when the distinction is not applicable (V0/V1/V2). Config-managed pools cannot be edited through the REST API or dashboard.
- L547 _public property_ `public bool? HasDatabaseEntry { get; set; }` — Whether this config-managed pool also has a database entry (shadow pool). When true, the database entry can be deleted to complete migration cleanup. Only set when ConfigManaged is true.
- L553-576 _public ctor_ `public GetPoolResponse(IPoolConfig pool)` — Constructor

#### record `HordeServer.Agents.Pools.GetPoolSummaryResponse`  
`public record class GetPoolSummaryResponse(PoolId Id, string Name, string ColorValue, bool Autoscaled, GetPoolStatsResponse? Stats, List<GetPoolAgentSummaryResponse>? Agents, List<double>? Utilization, bool? ConfigManaged = null, bool? HasDatabaseEntry = null)`  
_public; L591-591_
- desc: Response describing a pool

#### record `HordeServer.Agents.Pools.GetPoolStatsResponse`  
`public record class GetPoolStatsResponse(int NumAgents, int NumIdle, int NumOffline, int NumDisabled)`  
_public; L600-600_
- desc: Numbers of agents matching various criteria

#### record `HordeServer.Agents.Pools.GetPoolAgentSummaryResponse`  
`public record class GetPoolAgentSummaryResponse(AgentId AgentId, bool? Idle = null, bool? Offline = null, bool? Disabled = null)`  
_public; L609-609_
- desc: Response describing an agent in a pool

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Pools/PoolService.cs` (HordeServer.Compute)


#### class `HordeServer.Agents.Pools.PoolService`  
`public class PoolService`  
_public; L12-166_
- desc: Wraps functionality for manipulating pools
- L17 _private* field_ `readonly IPoolCollection _pools` — Collection of pool documents
- L22 _private* field_ `readonly IClock _clock` — Returns the current time
- L27 _private* field_ `Tuple<DateTime, Dictionary<PoolId, IPoolConfig>>? _cachedPoolLookup` — Cached set of pools, along with the timestamp that it was obtained
- L27 _private* field_ `Tuple< PoolId` — Cached set of pools, along with the timestamp that it was obtained
- L27 _private* field_ `Tuple< _cachedPoolLookup` — Cached set of pools, along with the timestamp that it was obtained
- L34-38 _public ctor_ `public PoolService(IPoolCollection pools, IClock clock)` — Constructor
- L48-51 _public method_ `public Task CreatePoolAsync(string name, CreatePoolConfigOptions options, CancellationToken cancellationToken = default)` — attrs: `[Obsolete("Pools should be configured through globals.json")]` — Creates a new pool
- L60-63 _public method_ `public Task<bool> DeletePoolAsync(PoolId poolId, CancellationToken cancellationToken = default)` — attrs: `[Obsolete("Pools should be configured through globals.json")]` — Deletes a pool
- L73-76 _public method_ `public Task UpdateConfigAsync(PoolId poolId, UpdatePoolConfigOptions options, CancellationToken cancellationToken)` — attrs: `[Obsolete("Pools should be configured through globals.json")]` — Updates an existing pool
- L83-86 _public method_ `public Task<IReadOnlyList<IPoolConfig>> GetPoolsAsync(CancellationToken cancellationToken)` — Gets all the available pools
- L94-97 _public method_ `public Task<IPool?> GetPoolAsync(PoolId poolId, CancellationToken cancellationToken = default)` — Gets a pool by ID
- L106-111 _public method_ `public async Task<IPoolConfig?> GetPoolAsync(PoolId poolId, DateTime validAtTime, CancellationToken cancellationToken)` — Gets a cached pool definition
- L120-134 _public method_ `public async Task<List<IPoolConfig>> GetPoolsAsync(IAgent agent, DateTime validAtTime, CancellationToken cancellationToken)` — Gets a cached pool definition
- L142-165 _public method_ `public async Task<IReadOnlyDictionary<PoolId, IPoolConfig>> GetPoolLookupAsync(DateTime validAtTime, CancellationToken cancellationToken)` — Gets a mapping from pool identifiers to definitions

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Pools/PoolsController.cs` (HordeServer.Compute)


#### class `HordeServer.Agents.Pools.PoolsController`  
`public class PoolsController : HordeControllerBase`  
_public; L22-376_
- attrs: `[ApiController] [Authorize] [Route("[controller]")]`
- inherits: `HordeControllerBase`
- desc: Controller for the /api/v1/pools endpoint
- L24 _private* field_ `readonly AgentService _agentService`
- L25 _private* field_ `readonly IPoolCollection _poolCollection`
- L26 _private* field_ `readonly IUtilizationDataCollection _utilizationDataCollection`
- L27 _private* field_ `readonly IClock _clock`
- L28 _private* field_ `readonly IOptionsSnapshot<ComputeConfig> _computeConfig`
- L33-40 _public ctor_ `public PoolsController(AgentService agentService, IPoolCollection poolCollection, IUtilizationDataCollection utilizationDataCollection, IClock clock, IOptionsSnapshot<ComputeConfig> computeConfig)` — Constructor
- L50-92 _public method_ `public async Task<ActionResult<CreatePoolResponse>> CreatePoolAsync([FromBody] CreatePoolRequest create)` — attrs: `[HttpPost] [Obsolete("Pools should be configured through globals.json")] [Route("/api/v1/pools")]` — Creates a new pool
- L103-119 _public method_ `public async Task<ActionResult<List<object>>> GetPoolsAsync([FromQuery] PropertyFilter? filter = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/pools")] [ProducesResponseType(typeof(List<GetPoolResponse>), 200)]` — Query all the pools
- L133-237 _public method_ `public async Task<ActionResult<List<object>>> GetPoolSummariesAsync([FromQuery] Condition? condition = null, [FromQuery] bool stats = false, [FromQuery] int numAgents = 0, [FromQuery] int numUtilizationSamples = 0, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v2/pools")] [ProducesResponseType(typeof(List<GetPoolResponse>), 200)]` — Query all the pools
- L248-264 _public method_ `public async Task<ActionResult<object>> GetPoolAsync(string poolId, [FromQuery] PropertyFilter? filter = null)` — attrs: `[HttpGet] [Route("/api/v1/pools/{poolId}")] [ProducesResponseType(typeof(GetPoolResponse), 200)]` — Retrieve information about a specific pool
- L275-315 _public method_ `public async Task<ActionResult> UpdatePoolAsync(string poolId, [FromBody] UpdatePoolRequest update)` — attrs: `[HttpPut] [Obsolete("Pools should be configured through globals.json")] [Route("/api/v1/pools/{poolId}")]` — Update a pool's properties.
- L325-344 _public method_ `public async Task<ActionResult> DeletePoolAsync(string poolId)` — attrs: `[HttpDelete] [Obsolete("Pools should be configured through globals.json")] [Route("/api/v1/pools/{poolId}")]` — Delete a pool
- L354-375 _public method_ `public async Task<ActionResult> UpdatePoolAsync([FromBody] List<BatchUpdatePoolRequest> batchUpdates)` — attrs: `[HttpPut] [Obsolete("Pools should be configured through globals.json")] [Route("/api/v1/pools")]` — Batch update pool properties

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Relay/AgentRelayClient.cs` (HordeServer.Compute)


#### class `HordeServer.Agents.Relay.AgentRelayClient`  
`public class AgentRelayClient`  
_public; L16-174_
- desc: Relay service mirroring port mappings sent from server These mappings will port forward specific ports to agents sitting behind a firewall. An agent using this relay mode usually has multiple IPs assigned to allow bridging.
- L21 _public property_ `public TimeSpan CooldownOnException { get; set; }` — Cooldown after an exception occurs. Primarily set to speed up tests.
- L26 _public property_ `public int RevisionNumber { get; set; }` — Last received revision number after a long-polling responses has returned
- L28 _private field_ `private readonly string _clusterId`
- L29 _private field_ `private readonly string _agentId`
- L30 _private field_ `private readonly List<string> _ipAddresses`
- L31 _private field_ `private readonly Nftables _nftables`
- L32 _private field_ `private readonly RelayRpc.RelayRpcClient _relayRpcClient`
- L33 _private field_ `private readonly IClock _clock`
- L34 _private field_ `private readonly ILogger _logger`
- L35 _private field_ `private List<PortMapping>? _lastPortMappings`
- L47-56 _public ctor_ `public AgentRelayClient(string clusterId, string agentId, List<string> ipAddresses, Nftables nftables, RelayRpc.RelayRpcClient relayRpcClient, IClock clock, ILogger logger)` — Constructor
- L65-84 _public method_ `public async Task<List<PortMapping>?> GetPortMappingsLongPollAsync(CancellationToken cancellationToken)` — Get a list of port mappings from the server using a streaming response. Using streaming, the relay service can act immediately once new mappings are sent. This avoids excessive and repetitive polling, and in turn load on the server.
- L90-120 _public method_ `public async Task ListenForPortMappingsAsync(CancellationToken cancellationToken)` — Continuously listen for port mappings from server and apply them
- L122-148 _private method_ `private void LogPortMappingChanges(List<PortMapping> portMappings)`
- L163-173 _internal method_ `internal static (IReadOnlySet<PortMapping> added, IReadOnlySet<PortMapping> removed) ComparePortMappings(List<PortMapping>? oldMappings, List<PortMapping> newMappings)`

#### class `HordeServer.Agents.Relay.AgentRelayClient.PortMappingComparer`  
`private class PortMappingComparer : IEqualityComparer<PortMapping>`  
_private; L150-161_
- inherits: `IEqualityComparer<PortMapping>`
- L152-155 _public method_ `public bool Equals(PortMapping? x, PortMapping? y)`
- L157-160 _public method_ `public int GetHashCode(PortMapping obj)`

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Relay/AgentRelayService.cs` (HordeServer.Compute)


#### class `HordeServer.Agents.Relay.AgentRelayException`  
`public class AgentRelayException : Exception`  
_public; L28-37_
- inherits: `Exception`
- desc: Exception thrown by agent relay related code
- L34-36 _public ctor_ `public AgentRelayException(string? message) : base(message)` — Constructor

#### class `HordeServer.Agents.Relay.PortMappingResult`  
`public class PortMappingResult`  
_public; L42-64_
- desc: Result of a requested port forward for a specific agent
- L47 _public property_ `public IReadOnlyList<string> IpAddresses { get; }` — IP addresses to relays that are listening and forwarding traffic for the specified ports
- L52 _public property_ `public IReadOnlyList<Port> Ports { get; }` — Mapping between relay and local agent ports
- L59-63 _public ctor_ `public PortMappingResult(IReadOnlyList<string> ipAddresses, IReadOnlyList<Port> ports)` — Constructor

#### class `HordeServer.Agents.Relay.AgentRelayService`  
`public sealed class AgentRelayService : RelayRpc.RelayRpcBase, IHostedService, IAsyncDisposable`  
_public; L71-563_
- inherits: `RelayRpc.RelayRpcBase, IHostedService, IAsyncDisposable`
- desc: Service handling relaying of agent traffic The Horde agent can be started in a special mode where it will relay traffic to and from other agents. It connects back to this service over gRPC and mirror the current port mappings set by the server.
- L75 _private field_ `private string _redisChannelUpdate = "relay/update"`
- L76 _private method_ `private static string KeyClusters()`
- L77 _private method_ `private static string KeyPortMappings(ClusterId clusterId)`
- L78 _private method_ `private static string KeyPortMappingRevision(ClusterId clusterId)`
- L79 _private method_ `private static string KeyUsedPorts(ClusterId clusterId)`
- L80 _private method_ `private static string KeyAgents(ClusterId clusterId)`
- L82 _private field_ `private readonly IRedisService _redis`
- L83 _private field_ `private readonly IClock _clock`
- L84 _private field_ `private readonly Tracer _tracer`
- L85 _private field_ `private readonly ILogger<AgentRelayService> _logger`
- L86 _private field_ `private readonly object _lock = new()`
- L87 _private field_ `private TaskCompletionSource _onPortMappingUpdated = new()`
- L88 _private field_ `private readonly ConcurrentDictionary<ClusterId, PortMappingsInfo> _clusterPortMappings = ...`
- L88 _private field_ `private readonly ConcurrentDictionary< _clusterPortMappings = new()`
- L89 _private field_ `private TimeSpan _longPollTimeout = TimeSpan.FromSeconds(20)`
- L90 _private field_ `private TimeSpan _agentExpirationTimeout`
- L91 _private field_ `private readonly AsyncTaskQueue _updateTaskQueue`
- L92 _private field_ `private IAsyncDisposable? _redisSubscription`
- L93 _private field_ `private int _minPort = 10000`
- L94 _private field_ `private int _maxPort = 30000`
- L95 _private field_ `private Random _random = new ()`
- L96 _private field_ `private Func<Task>? _testDelayBeforeTaskCapture`
- L105-113 _public ctor_ `public AgentRelayService(IRedisService redis, IClock clock, Tracer tracer, ILogger<AgentRelayService> logger)` — Constructor
- L116-119 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L122-125 _public method_ `public async Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L128-136 _public method_ `public async Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L142-147 _public method_ `public async Task<HashSet<ClusterId>> GetClustersAsync()` — Get a list of all cluster IDs having registered a port mapping
- L155-160 _public method_ `public async Task<PortMapping?> GetPortMappingAsync(ClusterId clusterId, LeaseId leaseId)` — Retrieve a specific port mapping
- L167-182 _public method_ `public async Task<(int revision, List<PortMapping> portMappings)> GetPortMappingsAsync(ClusterId clusterId)` — Retrieve all current port mappings
- L195-253 _public method_ `public async Task<PortMapping> AddPortMappingAsync(ClusterId clusterId, LeaseId leaseId, IPAddress? clientIp, IPAddress agentIp, IList<Port> ports, int numRetries = 10)` — Add a new port mapping
- L261-284 _public method_ `public async Task<bool> RemovePortMappingAsync(ClusterId clusterId, LeaseId leaseId)` — Remove a port mapping for a lease
- L291-301 _public method_ `public async Task<bool> RemovePortMappingAsync(LeaseId leaseId)` — Remove a port mapping for a lease from all clusters
- L313-325 _public method_ `public async Task<PortMappingResult> RequestPortMappingAsync(ClusterId clusterId, LeaseId leaseId, IPAddress? clientIp, IPAddress agentIp, IList<Port> ports)` — Request a port mapping for a given lease and agent
- L327-345 _internal method_ `internal async Task<List<RelayAgentInfo>> GetAvailableRelayAgentsAsync(ClusterId clusterId)`
- L347-351 _private method_ `private async Task<List<RelayAgentInfo>> GetRelayAgentsAsync(ClusterId clusterId)`
- L353-358 _internal method_ `internal async Task UpdateAgentHeartbeatAsync(ClusterId clusterId, string agentRelayId, IEnumerable<IPAddress> ipAddresses)`
- L360-363 _private method_ `private Task PublishUpdateEventAsync(string clusterId)`
- L365-368 _private method_ `private async Task<IAsyncDisposable> SubscribeToUpdateEventAsync(Action<string> onUpdate)`
- L370-373 _private method_ `private void OnPortMappingUpdate(string clusterIdStr)`
- L375-392 _private method_ `private async Task OnPortMappingUpdateAsync(string clusterIdStr)`
- L394-406 _internal method_ `internal static IReadOnlySet<int> FindAvailablePortRange(IReadOnlySet<int> usedPorts, int numPorts, int minPort, int maxPort)`
- L418-453 _internal method_ `internal static IReadOnlySet<int> FindAvailablePorts(Random random, IReadOnlySet<int> usedPorts, int numPorts, int minPort, int maxPort)` — Find random ports available
- L455-459 _internal method_ `internal void SetMinMaxPorts(int minPort, int maxPort)`
- L461-465 _internal method_ `internal void SetTimeouts(int longPollMs, int expirationMs)`
- L467-470 _internal method_ `internal void SetRandomSeed(int seed)`
- L472-475 _internal method_ `internal void SetRedisChannel(string channel)`
- L477-480 _internal method_ `internal void SetTestDelayBeforeTaskCapture(Func<Task>? delay)`
- L482-491 _private method_ `private static void AddPortMappingMetadataToSpan(TelemetrySpan span, PortMapping portMapping)`
- L494-562 _public method_ `public override async Task GetPortMappings(GetPortMappingsRequest request, IServerStreamWriter<GetPortMappingsResponse> responseStream, ServerCallContext context)` — (inheritdoc)

#### record `HordeServer.Agents.Relay.AgentRelayService.PortMappingsInfo`  
`private record PortMappingsInfo(int Revision, List<PortMapping> PortMappings)`  
_private; L73-73_

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Relay/Nftables.cs` (HordeServer.Compute)


#### class `HordeServer.Agents.Relay.NftablesException`  
`public class NftablesException : Exception`  
_public; L15-24_
- inherits: `Exception`
- desc: nftables specific exception
- L21-23 _public ctor_ `public NftablesException(string? message) : base(message)` — Constructor

#### class `HordeServer.Agents.Relay.Nftables`  
`public class Nftables`  
_public; L31-194_
- desc: Class wrapping invocation of 'nft' CLI tool which controls nftables nftables are used to do port forwarding for relaying traffic to agents behind a firewall Requires Linux and appropriate packages installed for nft/nftables
- L33 _private const_ `private const string NftablesExecutable = "nft"`
- L34 _private field_ `private static readonly SemaphoreSlim s_nftSemaphore = new (1, 1)`
- L39 _public property_ `public bool RunWithSudo { get; set; }` — Prefix the invocation of 'nft' executable with 'sudo'
- L41 _private field_ `private readonly ILogger<Nftables> _logger`
- L42 _private field_ `private int? _configurableExitCode`
- L43 _private field_ `private string? _configurableOutputText`
- L49-52 _public ctor_ `public Nftables(ILogger<Nftables> logger)` — Constructor
- L61-68 _internal method_ `internal static Nftables CreateNull(int exitCode = 0, string outputText = "", ILogger<Nftables>? logger = null)` — Create a nullable version of this class, used for testing
- L73-77 _public method_ `public async Task InitializeAsync(CancellationToken cancellationToken)` — Initialize nftables
- L82-92 _public method_ `public async Task ApplyPortForwardingAsync(List<PortMapping> portMappings)` — Configure nftables to relay traffic through port forwarding
- L94-123 _internal method_ `internal async Task<(int exitCode, string output)> ExecuteNftAsync(List<string> arguments, string? stdin = null, CancellationToken cancellationToken = default)`
- L125-138 _private method_ `private void LogPortMappings(List<PortMapping> leaseMappings)`
- L140-154 _private method_ `private async Task<string> GetNftablesVersionAsync(CancellationToken cancellationToken)`
- L156-174 _internal method_ `internal static List<string> GenerateNftRules(List<PortMapping> leaseMappings)`
- L176-193 _internal method_ `internal static string GenerateNftFile(List<PortMapping> leaseMappings)`

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/SessionConflictService.cs` (HordeServer.Compute)


#### class `HordeServer.Agents.SessionConflictService`  
`public class SessionConflictService`  
_public; L13-60_
- desc: Tracks session conflict counts per agent in a Redis sorted set. Consumed by NotificationService to produce a 12-hour Slack report.
- L15 _private* field_ `static readonly RedisKey s_redisKey = new("session-conflicts")`
- L16 _private* field_ `static readonly TimeSpan s_keyTtl = TimeSpan.FromHours(48)`
- L18 _private* field_ `readonly IRedisService _redisService`
- L23 _public ctor_ `public SessionConflictService(IRedisService redisService)` — Constructor
- L30-37 _public method_ `public async Task<long> RecordConflictAsync(AgentId agentId, CancellationToken cancellationToken = default)` — Record a session conflict for the given agent.
- L43-59 _public method_ `public async Task<List<(AgentId Id, int Count)>> DrainConflictsAsync(CancellationToken cancellationToken = default)` — Drains all recorded conflicts and clears the set. Returns each agent ID paired with its total mismatch count since the last drain.

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Sessions/ISession.cs` (HordeServer.Compute)


#### interface `HordeServer.Agents.Sessions.ISession`  
`public interface ISession`  
_public; L11-37_
- desc: Information about an agent session.
- L16 _public property_ `public SessionId Id { get; }` — Unique id for this session
- L21 _public property_ `public AgentId AgentId { get; }` — The agent id
- L26 _public property_ `public DateTime StartTime { get; }` — Start time for this session
- L31 _public property_ `public DateTime? FinishTime { get; }` — Finishing time for this session
- L36 _public property_ `public string Version { get; }` — Version of the agent software

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Sessions/SessionAclAction.cs` (HordeServer.Compute)


#### class `HordeServer.Agents.Sessions.SessionAclAction`  
`public static class SessionAclAction`  
_public; L10-21_
- desc: Actions valid for agent sessions
- L15 _public property_ `public static AclAction CreateSession { get; }` — Granted to agents to call CreateSession, which returns a bearer token identifying themselves valid to call UpdateSesssion via gRPC.
- L20 _public property_ `public static AclAction ViewSession { get; }` — Allows viewing information about an agent session

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Sessions/SessionIdUtils.cs` (HordeServer.Compute)


#### class `HordeServer.Agents.Sessions.SessionIdUtils`  
`static class SessionIdUtils`  
_internal*; L11-17_
- desc: Server helper methods for SessionId
- L16 _public method_ `public static SessionId GenerateNewId()` — Creates a new SessionId

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Software/AgentSoftwareAclAction.cs` (HordeServer.Compute)


#### class `HordeServer.Agents.Software.AgentSoftwareAclAction`  
`public static class AgentSoftwareAclAction`  
_public; L10-26_
- desc: ACL actions for agent software
- L15 _public property_ `public static AclAction UploadSoftware { get; }` — Ability to upload new versions of the agent software
- L20 _public property_ `public static AclAction DownloadSoftware { get; }` — Ability to download the agent software
- L25 _public property_ `public static AclAction DeleteSoftware { get; }` — Ability to delete agent software

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Software/AgentSoftwareController.cs` (HordeServer.Compute)


#### class `HordeServer.Agents.Software.GetAgentSoftwareChannelResponse`  
`public class GetAgentSoftwareChannelResponse`  
_public; L15-21_
- desc: Information about an agent software channel
- L20 _public property_ `public string? Version { get; set; }` — Version number of this software

#### class `HordeServer.Agents.Software.AgentSoftwareController`  
`public class AgentSoftwareController : ControllerBase`  
_public; L29-105_
- attrs: `[ApiController] [Authorize] [Route("[controller]")]`
- inherits: `ControllerBase`
- desc: Controller for the /api/v1/agentsoftware endpoint
- L31 _private field_ `private readonly IToolCollection _toolCollection`
- L32 _private field_ `private readonly IClock _clock`
- L33 _private field_ `private readonly IOptionsSnapshot<ComputeConfig> _computeConfig`
- L38-43 _public ctor_ `public AgentSoftwareController(IToolCollection toolCollection, IClock clock, IOptionsSnapshot<ComputeConfig> computeConfig)` — Constructor
- L53-73 _public method_ `public async Task<ActionResult<object>> FindSoftwareAsync()` — attrs: `[HttpGet] [Obsolete("Agent software is now stored as a tool. This endpoint exists for backwards compatibility, but will be removed in the future.")] [Route("/api/v1/agentsoftware/default")] [ProducesResponseType(typeof(GetAgentSoftwareChann` — Finds all uploaded software matching the given criteria
- L83-104 _public method_ `public async Task<ActionResult> GetArchiveAsync(CancellationToken cancellationToken)` — attrs: `[HttpGet] [Obsolete("Agent software is now stored as a tool. This endpoint exists for backwards compatibility, but will be removed in the future.")] [Route("/api/v1/agentsoftware/default/zip")]` — Gets the zip file for a specific channel

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Telemetry/AgentTelemetry.cs` (HordeServer.Compute)


#### record `HordeServer.Agents.AgentTelemetry`  
`public record AgentTelemetry : AbstractTelemetryRecord`  
_public; L17-138_
- attrs: `[AnalyticsTableGen] [TelemetryEvent(DefaultEventName)] [Table("horde.state_agent_telemetry", Schema = "ingest")]`
- inherits: `AbstractTelemetryRecord`
- desc: Record used for Agent telemetry.
- L23 _public property_ `public AgentId AgentId { get; init; }` — attrs: `[Column("agent_id")]` — The ID of the agent we're reporting telemetry from.
- L29 _public property_ `public float UserCpu { get; init; }` — attrs: `[Column("user_cpu")]` — The user cpu usage.
- L35 _public property_ `public float IdleCpu { get; init; }` — attrs: `[Column("idle_cpu")]` — The idle cpu usage.
- L41 _public property_ `public float SystemCpu { get; init; }` — attrs: `[Column("system_cpu")]` — The system cpu usage.
- L47 _public property_ `public int FreeRamMb { get; init; }` — attrs: `[Column("free_ram_mb")]` — Free memory in MB.
- L53 _public property_ `public int UsedRamMb { get; init; }` — attrs: `[Column("used_ram_mb")]` — Used memory in MB.
- L59 _public property_ `public int TotalRamMb { get; init; }` — attrs: `[Column("total_ram_mb")]` — Total memory in MB.
- L65 _public property_ `public long WorkingFreeDiskMb { get; init; }` — attrs: `[Column("working_free_disk_mb")]` — The agent's working disk free space in MB.
- L71 _public property_ `public long WorkingTotalDiskMb { get; init; }` — attrs: `[Column("working_total_disk_mb")]` — The agent's working disk total space in MB.
- L77 _public property_ `public long SystemFreeDiskMb { get; init; }` — attrs: `[Column("system_free_disk_mb")]` — The system's free disk in MB.
- L83 _public property_ `public long SystemTotalDiskMb { get; init; }` — attrs: `[Column("system_total_disk_mb")]` — The system's total disk in MB.
- L88 _public const_ `public const string DefaultEventName = "State.Agent.Telemetry"` — Default event name for the Agent Telemetry event.
- L93 _public field_ `public static readonly int CurrentSchemaVersion = 1` — Current schema version.
- L100-115 _public ctor_ `public AgentTelemetry(NewAgentTelemetry telemetry, AgentId agentId) : base(DefaultEventName, CurrentSchemaVersion)` — Constructor from pre-existing NewAgentTelemetry object
- L117 _private const_ `private const string ORMPlaceholder = "_"`
- L122-137 _public ctor_ `public AgentTelemetry() : base(DefaultEventName, CurrentSchemaVersion)` — Default constructor for ORM mapping.

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Telemetry/AgentTelemetryCollection.cs` (HordeServer.Compute)


#### class `HordeServer.Agents.Telemetry.AgentTelemetryCollection`  
`public sealed class AgentTelemetryCollection : IAgentTelemetryCollection, IHostedService, IAsyncDisposable`  
_public; L18-145_
- inherits: `IAgentTelemetryCollection, IHostedService, IAsyncDisposable`
- desc: Collection which writes agent data to a MongoDB collection
- L61 _private* property_ `static TimeSpan RetainDays { get; }`
- L63 _private* field_ `readonly IClock _clock`
- L64 _private* field_ `readonly IMongoCollection<AgentTelemetryDocument> _collection`
- L66 _private* field_ `readonly MongoBufferedWriter<AgentTelemetryDocument> _writer`
- L68 _private* field_ `readonly ITicker _cleanupTicker`
- L69 _private* field_ `readonly ILogger _logger`
- L74-86 _public ctor_ `public AgentTelemetryCollection(IMongoService mongoService, IClock clock, ILogger<AgentTelemetryCollection> logger)` — Constructor
- L89-93 _public method_ `public async Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L96-100 _public method_ `public async Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L102-107 _private* method_ `async ValueTask CleanupAsync(CancellationToken cancellationToken)`
- L110-115 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L118 _public method_ `public ValueTask FlushAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L122-138 _public method_ `public void Add(AgentId agentId, NewAgentTelemetry telemetry)` — (inheritdoc)
- L141-144 _public method_ `public async Task<IReadOnlyList<IAgentTelemetry>> FindAsync(AgentId agentId, DateTime minTimeUtc, DateTime maxTimeUtc, CancellationToken cancellationToken = default)` — (inheritdoc)

#### class `HordeServer.Agents.Telemetry.AgentTelemetryCollection.AgentTelemetryDocument`  
`class AgentTelemetryDocument : IAgentTelemetry`  
_private*; L20-59_
- inherits: `IAgentTelemetry`
- L22 _public property_ `public ObjectId Id { get; set; }`
- L25 _public property_ `public DateTime TimeUtc { get; set; }` — attrs: `[BsonElement("tm")]`
- L28 _public property_ `public AgentId AgentId { get; set; }` — attrs: `[BsonElement("agt")]`
- L31 _public property_ `public float UserCpu { get; set; }` — attrs: `[BsonElement("cpu_usr")]`
- L34 _public property_ `public float SystemCpu { get; set; }` — attrs: `[BsonElement("cpu_sys")]`
- L37 _public property_ `public float IdleCpu { get; set; }` — attrs: `[BsonElement("cpu_idle")]`
- L40 _public property_ `public int TotalRam { get; set; }` — attrs: `[BsonElement("ram_tot")]`
- L43 _public property_ `public int FreeRam { get; set; }` — attrs: `[BsonElement("ram_free")]`
- L46 _public property_ `public int UsedRam { get; set; }` — attrs: `[BsonElement("ram_used")]`
- L49 _public property_ `public long WorkingTotalDisk { get; set; }` — attrs: `[BsonElement("hdd_tot")]`
- L52 _public property_ `public long WorkingFreeDisk { get; set; }` — attrs: `[BsonElement("hdd_free")]`
- L55 _public property_ `public long SystemTotalDisk { get; set; }` — attrs: `[BsonElement("sys_hdd_tot")]`
- L58 _public property_ `public long SystemFreeDisk { get; set; }` — attrs: `[BsonElement("sys_hdd_free")]`

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Telemetry/IAgentTelemetry.cs` (HordeServer.Compute)


#### interface `HordeServer.Agents.Telemetry.IAgentTelemetry`  
`public interface IAgentTelemetry`  
_public; L8-64_
- desc: Telemetry for an agent
- L13 _public* property_ `DateTime TimeUtc { get; set; }` — Time that the data was captured
- L18 _public* property_ `float UserCpu { get; set; }` — Percentage of time the CPU was busy executing code in user space
- L23 _public* property_ `float SystemCpu { get; set; }` — Percentage of time the CPU was busy executing code in kernel space
- L28 _public* property_ `float IdleCpu { get; set; }` — Percentage of time the CPU was idling
- L33 _public* property_ `int TotalRam { get; set; }` — Total memory installed (megabytes)
- L38 _public* property_ `int FreeRam { get; set; }` — Available memory (megabytes)
- L43 _public* property_ `int UsedRam { get; set; }` — Used memory (megabytes)
- L48 _public* property_ `long WorkingTotalDisk { get; set; }` — Total disk space (megabytes)
- L53 _public* property_ `long WorkingFreeDisk { get; set; }` — Free disk space (megabytes)
- L58 _public* property_ `long SystemTotalDisk { get; set; }` — Total disk space (megabytes)
- L63 _public* property_ `long SystemFreeDisk { get; set; }` — Free disk space (megabytes)

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Telemetry/IAgentTelemetryCollection.cs` (HordeServer.Compute)


#### interface `HordeServer.Agents.Telemetry.IAgentTelemetryCollection`  
`public interface IAgentTelemetryCollection`  
_public; L10-25_
- desc: Interface for a collection of agent telemetry documents
- L15 _public* method_ `void Add(AgentId agentId, NewAgentTelemetry telemetry)` — Adds a new telemetry event
- L24 _public* method_ `Task<IReadOnlyList<IAgentTelemetry>> FindAsync(AgentId agentId, DateTime minTimeUtc, DateTime maxTimeUtc, CancellationToken cancellationToken = default)` — Finds telemetry samples for an agent in a particular time range

#### record `HordeServer.Agents.Telemetry.NewAgentTelemetry`  
`public record class NewAgentTelemetry(float UserCpuPct, float IdleCpuPct, float SystemCpuPct, int FreeRamMb, int UsedRamMb, int TotalRamMb, long WorkingFreeDiskMb, long WorkingTotalDiskMb, long SystemFreeDiskMb, long SystemTotalDiskMb)`  
_public; L30-30_
- desc: New telemetry data

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Utilization/IUtilizationData.cs` (HordeServer.Compute)


#### interface `HordeServer.Agents.Utilization.IUtilizationData`  
`public interface IUtilizationData`  
_public; L11-42_
- desc: Information about the utilization of a pool
- L16 _public property_ `public DateTime StartTime { get; }` — Start time for the bucket
- L21 _public property_ `public DateTime FinishTime { get; }` — Finish time for this bucket
- L26 _public property_ `public int NumAgents { get; }` — Number of agents in total
- L31 _public property_ `public IReadOnlyList<IPoolUtilizationData> Pools { get; }` — Breakdown of utilization by pool
- L36 _public property_ `public double HibernatingTime { get; }` — Amount of time that agents were hibernating
- L41 _public property_ `public double AdminTime { get; }` — Total time spent running administrative tasks (conform, etc...)

#### class `HordeServer.Agents.Utilization.UtilizationData`  
`public sealed class UtilizationData : IUtilizationData`  
_public; L47-97_
- inherits: `IUtilizationData`
- desc: Concrete implementation of IUtilizationData
- L50 _public property_ `public DateTime StartTime { get; set; }` — (inheritdoc)
- L53 _public property_ `public DateTime FinishTime { get; set; }` — (inheritdoc)
- L56 _public property_ `public int NumAgents { get; set; }` — (inheritdoc)
- L59 _private* property_ `List<PoolUtilizationData> Pools { get; set; }` — (inheritdoc)
- L60 _private* property_ `IReadOnlyList<IPoolUtilizationData> IUtilizationData.Pools => ...`
- L62 _private* property_ `Dictionary<PoolId, PoolUtilizationData> PoolsLookup { get; set; }`
- L65 _public property_ `public double HibernatingTime { get; set; }` — (inheritdoc)
- L68 _public property_ `public double AdminTime { get; set; }` — (inheritdoc)
- L75-79 _public ctor_ `public UtilizationData(DateTime startTime, DateTime finishTime)` — Constructor
- L86-96 _public method_ `public PoolUtilizationData FindOrAddPool(PoolId poolId)` — Adds a new pool

#### interface `HordeServer.Agents.Utilization.IPoolUtilizationData`  
`public interface IPoolUtilizationData`  
_public; L102-133_
- desc: Information about the utilization of a pool
- L107 _public property_ `public PoolId PoolId { get; }` — Pool containing the work to execute
- L112 _public property_ `public int NumAgents { get; }` — Number of agents in this pool
- L117 _public property_ `public IReadOnlyList<IStreamUtilizationData> Streams { get; }` — The stream executing work. If this is null, the time accounts for the machine executing work in another pool.
- L122 _public property_ `public double AdminTime { get; }` — Amount of time spent running
- L127 _public property_ `public double HibernatingTime { get; }` — Amount of time that agents were hibernating
- L132 _public property_ `public double OtherTime { get; }` — Amount of time spent by agents in this pool servicing other pools

#### class `HordeServer.Agents.Utilization.PoolUtilizationData`  
`public sealed class PoolUtilizationData : IPoolUtilizationData`  
_public; L138-185_
- inherits: `IPoolUtilizationData`
- desc: Concrete implementation of IPoolUtilizationData
- L141 _public property_ `public PoolId PoolId { get; set; }` — (inheritdoc)
- L144 _public property_ `public int NumAgents { get; set; }` — (inheritdoc)
- L147 _private* property_ `List<StreamUtilizationData> Streams { get; set; }` — (inheritdoc)
- L148 _private* property_ `IReadOnlyList<IStreamUtilizationData> IPoolUtilizationData.Streams => ...`
- L150 _private* property_ `Dictionary<StreamId, StreamUtilizationData> StreamLookup { get; set; }`
- L153 _public property_ `public double AdminTime { get; set; }` — (inheritdoc)
- L156 _public property_ `public double HibernatingTime { get; set; }` — (inheritdoc)
- L159 _public property_ `public double OtherTime { get; set; }` — (inheritdoc)
- L165-168 _public ctor_ `public PoolUtilizationData(PoolId poolId)` — Constructor
- L174-184 _public method_ `public StreamUtilizationData FindOrAddStream(StreamId streamId)` — Adds a stream to the object

#### interface `HordeServer.Agents.Utilization.IStreamUtilizationData`  
`public interface IStreamUtilizationData`  
_public; L190-201_
- desc: Utilization of a pool for a particular stream
- L195 _public property_ `public StreamId StreamId { get; }` — The stream id
- L200 _public property_ `public double Time { get; }` — Number of machine hours spent executing work for this stream

#### class `HordeServer.Agents.Utilization.StreamUtilizationData`  
`public sealed class StreamUtilizationData : IStreamUtilizationData`  
_public; L206-222_
- inherits: `IStreamUtilizationData`
- desc: Concrete implementation of IStreamUtilizationData
- L209 _public property_ `public StreamId StreamId { get; set; }` — (inheritdoc)
- L212 _public property_ `public double Time { get; set; }` — (inheritdoc)
- L218-221 _public ctor_ `public StreamUtilizationData(StreamId streamId)` — Constructor

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Utilization/IUtilizationDataCollection.cs` (HordeServer.Compute)


#### interface `HordeServer.Agents.Utilization.IUtilizationDataCollection`  
`public interface IUtilizationDataCollection`  
_public; L8-33_
- desc: Collection of utilization collection
- L15 _public* method_ `Task AddUtilizationDataAsync(IUtilizationData data, CancellationToken cancellationToken = default)` — Adds entries for the given utilization
- L25 _public* method_ `Task<IReadOnlyList<IUtilizationData>> GetUtilizationDataAsync(DateTime? startTimeUtc = null, DateTime? finishTimeUtc = null, int? count = null, CancellationToken cancellationToken = default)` — Finds utilization data matching the given criteria
- L32 _public* method_ `Task<IUtilizationData?> GetLatestUtilizationDataAsync(CancellationToken cancellationToken = default)` — Finds utilization data matching the given criteria

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Utilization/UtilizationController.cs` (HordeServer.Compute)


#### class `HordeServer.Agents.Utilization.UtilizationController`  
`public sealed class UtilizationController : ControllerBase`  
_public; L14-93_
- attrs: `[ApiController] [Route("[controller]")]`
- inherits: `ControllerBase`
- desc: Controller for the /api/v1/utilization endpoint.
- L16 _private* field_ `readonly IUtilizationDataCollection _utilizationDataCollection`
- L21-24 _public ctor_ `public UtilizationController(IUtilizationDataCollection utilizationDataCollection)` — Constructor
- L35-39 _public method_ `public async Task<ActionResult<List<GetUtilizationDataResponse>>> GetUtilizationDataAsync([FromQuery] DateTime? after = null, [FromQuery] DateTime? before = null, [FromQuery] int? count = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/utilization")]` — Gets utilization data for a time range.
- L47-59 _public method_ `public async Task<ActionResult<List<GetUtilizationDataResponse>>> GetStreamUtilizationDataAsync(DateTime endDate, [FromQuery(Name = "Range")] int range, [FromQuery(Name = "TzOffset")] int? tzOffset, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Obsolete("Use the /api/v1/utilization endpoint instead.")] [Route("/api/v1/reports/utilization/{endDate}")]` — Gets a collection of utilization data including an endpoint and a range
- L61-72 _private* method_ `static GetUtilizationDataResponse CreateTelemetryResponse(IUtilizationData telemetry)`
- L74-84 _private* method_ `static GetUtilizationPoolDataResponse CreatePoolTelemetryResponse(IPoolUtilizationData pool)`
- L86-92 _private* method_ `static GetUtilizationStreamDataResponse CreateStreamTelemetryResponse(IStreamUtilizationData stream)`

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Utilization/UtilizationDataCollection.cs` (HordeServer.Compute)


#### class `HordeServer.Agents.Utilization.UtilizationDataCollection`  
`public class UtilizationDataCollection : IUtilizationDataCollection`  
_public; L15-137_
- inherits: `IUtilizationDataCollection`
- desc: Collection of utilization data
- L93 _private* field_ `readonly IMongoCollection<UtilizationDocument> _utilization`
- L99-102 _public ctor_ `public UtilizationDataCollection(IMongoService database)` — Constructor
- L105-108 _public method_ `public async Task AddUtilizationDataAsync(IUtilizationData newTelemetry, CancellationToken cancellationToken)` — (inheritdoc)
- L111-130 _public method_ `public async Task<IReadOnlyList<IUtilizationData>> GetUtilizationDataAsync(DateTime? startTimeUtc, DateTime? finishTimeUtc, int? count, CancellationToken cancellationToken)` — (inheritdoc)
- L133-136 _public method_ `public async Task<IUtilizationData?> GetLatestUtilizationDataAsync(CancellationToken cancellationToken)` — (inheritdoc)

#### class `HordeServer.Agents.Utilization.UtilizationDataCollection.UtilizationDocument`  
`class UtilizationDocument : IUtilizationData`  
_private*; L17-45_
- inherits: `IUtilizationData`
- L19 _public property_ `public DateTime StartTime { get; set; }`
- L20 _public property_ `public DateTime FinishTime { get; set; }`
- L22 _public property_ `public int NumAgents { get; set; }`
- L23 _public property_ `public List<PoolUtilizationDocument> Pools { get; set; }`
- L24 _private* property_ `IReadOnlyList<IPoolUtilizationData> IUtilizationData.Pools => ...`
- L26 _public property_ `public double AdminTime { get; set; }`
- L27 _public property_ `public double HibernatingTime { get; set; }`
- L28 _public property_ `public int UpdateIndex { get; set; }`
- L31-34 _private ctor_ `private UtilizationDocument()` — attrs: `[BsonConstructor]`
- L36-44 _public ctor_ `public UtilizationDocument(IUtilizationData other)`

#### class `HordeServer.Agents.Utilization.UtilizationDataCollection.PoolUtilizationDocument`  
`class PoolUtilizationDocument : IPoolUtilizationData`  
_private*; L47-74_
- inherits: `IPoolUtilizationData`
- L49 _public property_ `public PoolId PoolId { get; set; }`
- L50 _public property_ `public int NumAgents { get; set; }`
- L52 _public property_ `public List<StreamUtilizationDocument> Streams { get; set; }`
- L53 _private* property_ `IReadOnlyList<IStreamUtilizationData> IPoolUtilizationData.Streams => ...`
- L55 _public property_ `public double AdminTime { get; set; }`
- L56 _public property_ `public double HibernatingTime { get; set; }`
- L57 _public property_ `public double OtherTime { get; set; }`
- L60-63 _private ctor_ `private PoolUtilizationDocument()` — attrs: `[BsonConstructor]`
- L65-73 _public ctor_ `public PoolUtilizationDocument(IPoolUtilizationData other)`

#### class `HordeServer.Agents.Utilization.UtilizationDataCollection.StreamUtilizationDocument`  
`class StreamUtilizationDocument : IStreamUtilizationData`  
_private*; L76-91_
- inherits: `IStreamUtilizationData`
- L78 _public property_ `public StreamId StreamId { get; set; }`
- L79 _public property_ `public double Time { get; set; }`
- L82-84 _private ctor_ `private StreamUtilizationDocument()` — attrs: `[BsonConstructor]`
- L86-90 _public ctor_ `public StreamUtilizationDocument(IStreamUtilizationData other)`

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Agents/Utilization/UtilizationDataService.cs` (HordeServer.Compute)


#### class `HordeServer.Agents.Utilization.UtilizationDataService`  
`public sealed class UtilizationDataService : IHostedService, IAsyncDisposable`  
_public; L17-136_
- inherits: `IHostedService, IAsyncDisposable`
- desc: Service which updates telemetry periodically
- L19 _private* field_ `readonly IUtilizationDataCollection _utilizationDataCollection`
- L20 _private* field_ `readonly IAgentCollection _agentCollection`
- L21 _private* field_ `readonly ILeaseCollection _leaseCollection`
- L22 _private* field_ `readonly IPoolCollection _poolCollection`
- L23 _private* field_ `readonly IFleetManager _fleetManager`
- L24 _private* field_ `readonly IClock _clock`
- L25 _private* field_ `readonly ITicker _tick`
- L26 _private* field_ `readonly ILogger _logger`
- L31-41 _public ctor_ `public UtilizationDataService(IUtilizationDataCollection utilizationDataCollection, IAgentCollection agentCollection, ILeaseCollection leaseCollection, IPoolCollection poolCollection, IFleetManager fleetManager, IClock clock, ILogger<UtilizationDataService> logger)` — Constructor
- L44 _public method_ `public Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L47 _public method_ `public Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L50 _public method_ `public ValueTask DisposeAsync()` — (inheritdoc)
- L53-135 _private* method_ `async ValueTask TickLeaderAsync(CancellationToken cancellationToken)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Aws/AwsCloudWatchMetricExporter.cs` (HordeServer.Compute)


#### class `HordeServer.Aws.AwsCloudWatchMetricExporter`  
`public sealed class AwsCloudWatchMetricExporter : IHostedService, IAsyncDisposable`  
_public; L16-98_
- inherits: `IHostedService, IAsyncDisposable`
- desc: Exports metric inside Horde server to AWS CloudWatch
- L18 _private field_ `private readonly ComputeService _computeService`
- L19 _private field_ `private readonly IAmazonCloudWatch _cloudWatch`
- L20 _private field_ `private readonly AsyncTaskQueue _asyncTaskQueue`
- L21 _private field_ `private readonly ILogger<AwsCloudWatchMetricExporter> _logger`
- L29-35 _public ctor_ `public AwsCloudWatchMetricExporter(ComputeService computeService, IAmazonCloudWatch cloudWatch, ILogger<AwsCloudWatchMetricExporter> logger)` — Constructor
- L38-41 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L43-46 _private method_ `private void OnResourceNeedsUpdated(string clusterId, string poolId, string resourceName, int totalValue)`
- L48-83 _private method_ `private async Task OnResourceNeedsUpdatedAsync(string clusterId, string poolId, string resourceName, int totalValue, CancellationToken cancellationToken)`
- L86-90 _public method_ `public Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L93-97 _public method_ `public async Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Aws/AwsCloudWatchMultiplexer.cs` (HordeServer.Compute)


#### class `HordeServer.Aws.AwsCloudWatchMultiplexer`  
`public class AwsCloudWatchMultiplexer : IAmazonCloudWatch`  
_public; L16-119_
- inherits: `IAmazonCloudWatch`
- desc: Fan-out a single CloudWatch request to multiple clients (each AWS region requires a separate client) This is used for replicating metrics to more than one region while still implementing the same original interface. Granted, only PutMetricDataAsync is implemented as that is what Horde uses.
- L18 _private field_ `private readonly List<IAmazonCloudWatch> _clients`
- L24-32 _public ctor_ `public AwsCloudWatchMultiplexer(List<IAmazonCloudWatch> clients)` — Constructor
- L35-49 _public method_ `public async Task<PutMetricDataResponse> PutMetricDataAsync(PutMetricDataRequest request, CancellationToken cancellationToken = default)` — (inheritdoc)
- L52 _public property_ `public IClientConfig Config => ...` — (inheritdoc)
- L55-59 _public method_ `public void Dispose()` — (inheritdoc)
- L64-73 _protected method_ `protected virtual void Dispose(bool disposing)` — Overridable dispose method
- L76 _public method_ `public Task<DeleteAlarmsResponse> DeleteAlarmsAsync(DeleteAlarmsRequest request, CancellationToken cancellationToken = default)`
- L77 _public method_ `public Task<DeleteAnomalyDetectorResponse> DeleteAnomalyDetectorAsync(DeleteAnomalyDetectorRequest request, CancellationToken cancellationToken = default)`
- L78 _public method_ `public Task<DeleteDashboardsResponse> DeleteDashboardsAsync(DeleteDashboardsRequest request, CancellationToken cancellationToken = default)`
- L79 _public method_ `public Task<DeleteInsightRulesResponse> DeleteInsightRulesAsync(DeleteInsightRulesRequest request, CancellationToken cancellationToken = default)`
- L80 _public method_ `public Task<DeleteMetricStreamResponse> DeleteMetricStreamAsync(DeleteMetricStreamRequest request, CancellationToken cancellationToken = default)`
- L81 _public method_ `public Task<DescribeAlarmHistoryResponse> DescribeAlarmHistoryAsync(CancellationToken cancellationToken = default)`
- L82 _public method_ `public Task<DescribeAlarmHistoryResponse> DescribeAlarmHistoryAsync(DescribeAlarmHistoryRequest request, CancellationToken cancellationToken = default)`
- L83 _public method_ `public Task<DescribeAlarmsResponse> DescribeAlarmsAsync(CancellationToken cancellationToken = default)`
- L84 _public method_ `public Task<DescribeAlarmsResponse> DescribeAlarmsAsync(DescribeAlarmsRequest request, CancellationToken cancellationToken = default)`
- L85 _public method_ `public Task<DescribeAlarmsForMetricResponse> DescribeAlarmsForMetricAsync(DescribeAlarmsForMetricRequest request, CancellationToken cancellationToken = default)`
- L86 _public method_ `public Task<DescribeAnomalyDetectorsResponse> DescribeAnomalyDetectorsAsync(DescribeAnomalyDetectorsRequest request, CancellationToken cancellationToken = default)`
- L87 _public method_ `public Task<DescribeInsightRulesResponse> DescribeInsightRulesAsync(DescribeInsightRulesRequest request, CancellationToken cancellationToken = default)`
- L88 _public method_ `public Task<DisableAlarmActionsResponse> DisableAlarmActionsAsync(DisableAlarmActionsRequest request, CancellationToken cancellationToken = default)`
- L89 _public method_ `public Task<DisableInsightRulesResponse> DisableInsightRulesAsync(DisableInsightRulesRequest request, CancellationToken cancellationToken = default)`
- L90 _public method_ `public Task<EnableAlarmActionsResponse> EnableAlarmActionsAsync(EnableAlarmActionsRequest request, CancellationToken cancellationToken = default)`
- L91 _public method_ `public Task<EnableInsightRulesResponse> EnableInsightRulesAsync(EnableInsightRulesRequest request, CancellationToken cancellationToken = default)`
- L92 _public method_ `public Task<GetDashboardResponse> GetDashboardAsync(GetDashboardRequest request, CancellationToken cancellationToken = default)`
- L93 _public method_ `public Task<GetInsightRuleReportResponse> GetInsightRuleReportAsync(GetInsightRuleReportRequest request, CancellationToken cancellationToken = default)`
- L94 _public method_ `public Task<GetMetricDataResponse> GetMetricDataAsync(GetMetricDataRequest request, CancellationToken cancellationToken = default)`
- L95 _public method_ `public Task<GetMetricStatisticsResponse> GetMetricStatisticsAsync(GetMetricStatisticsRequest request, CancellationToken cancellationToken = default)`
- L96 _public method_ `public Task<GetMetricStreamResponse> GetMetricStreamAsync(GetMetricStreamRequest request, CancellationToken cancellationToken = default)`
- L97 _public method_ `public Task<GetMetricWidgetImageResponse> GetMetricWidgetImageAsync(GetMetricWidgetImageRequest request, CancellationToken cancellationToken = default)`
- L98 _public method_ `public Task<ListDashboardsResponse> ListDashboardsAsync(ListDashboardsRequest request, CancellationToken cancellationToken = default)`
- L99 _public method_ `public Task<ListManagedInsightRulesResponse> ListManagedInsightRulesAsync(ListManagedInsightRulesRequest request, CancellationToken cancellationToken = default)`
- L100 _public method_ `public Task<ListMetricsResponse> ListMetricsAsync(CancellationToken cancellationToken = default)`
- L101 _public method_ `public Task<ListMetricsResponse> ListMetricsAsync(ListMetricsRequest request, CancellationToken cancellationToken = default)`
- L102 _public method_ `public Task<ListMetricStreamsResponse> ListMetricStreamsAsync(ListMetricStreamsRequest request, CancellationToken cancellationToken = default)`
- L103 _public method_ `public Task<ListTagsForResourceResponse> ListTagsForResourceAsync(ListTagsForResourceRequest request, CancellationToken cancellationToken = default)`
- L104 _public method_ `public Task<PutAnomalyDetectorResponse> PutAnomalyDetectorAsync(PutAnomalyDetectorRequest request, CancellationToken cancellationToken = default)`
- L105 _public method_ `public Task<PutCompositeAlarmResponse> PutCompositeAlarmAsync(PutCompositeAlarmRequest request, CancellationToken cancellationToken = default)`
- L106 _public method_ `public Task<PutDashboardResponse> PutDashboardAsync(PutDashboardRequest request, CancellationToken cancellationToken = default)`
- L107 _public method_ `public Task<PutInsightRuleResponse> PutInsightRuleAsync(PutInsightRuleRequest request, CancellationToken cancellationToken = default)`
- L108 _public method_ `public Task<PutManagedInsightRulesResponse> PutManagedInsightRulesAsync(PutManagedInsightRulesRequest request, CancellationToken cancellationToken = default)`
- L109 _public method_ `public Task<PutMetricAlarmResponse> PutMetricAlarmAsync(PutMetricAlarmRequest request, CancellationToken cancellationToken = default)`
- L110 _public method_ `public Task<PutMetricStreamResponse> PutMetricStreamAsync(PutMetricStreamRequest request, CancellationToken cancellationToken = default)`
- L111 _public method_ `public Task<SetAlarmStateResponse> SetAlarmStateAsync(SetAlarmStateRequest request, CancellationToken cancellationToken = default)`
- L112 _public method_ `public Task<StartMetricStreamsResponse> StartMetricStreamsAsync(StartMetricStreamsRequest request, CancellationToken cancellationToken = default)`
- L113 _public method_ `public Task<StopMetricStreamsResponse> StopMetricStreamsAsync(StopMetricStreamsRequest request, CancellationToken cancellationToken = default)`
- L114 _public method_ `public Task<TagResourceResponse> TagResourceAsync(TagResourceRequest request, CancellationToken cancellationToken = default)`
- L115 _public method_ `public Task<UntagResourceResponse> UntagResourceAsync(UntagResourceRequest request, CancellationToken cancellationToken = default)`
- L116 _public method_ `public Endpoint DetermineServiceOperationEndpoint(AmazonWebServiceRequest request)`
- L117 _public property_ `public ICloudWatchPaginatorFactory Paginators => ...`

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Compute/ComputeAclAction.cs` (HordeServer.Compute)


#### class `HordeServer.Compute.ComputeAclAction`  
`public static class ComputeAclAction`  
_public; L10-31_
- desc: ACL actions for compute service
- L15 _public property_ `public static AclAction AddComputeTasks { get; }` — User can add tasks to the compute cluster
- L20 _public property_ `public static AclAction GetComputeTasks { get; }` — User can get and list tasks from the compute cluster
- L25 _public property_ `public static AclAction UbaCacheRead { get; }` — User can read from Unreal Build Accelerator cache
- L30 _public property_ `public static AclAction UbaCacheWrite { get; }` — User can write to Unreal Build Accelerator cache

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Compute/ComputeController.cs` (HordeServer.Compute)


#### class `HordeServer.Compute.ComputeController`  
`public class ComputeController : HordeControllerBase`  
_public; L23-249_
- attrs: `[ApiController] [Authorize] [Route("[controller]")]`
- inherits: `HordeControllerBase`
- desc: Controller for the /api/v2/compute endpoint
- L25 _private* field_ `readonly ComputeService _computeService`
- L26 _private* field_ `readonly IOptionsSnapshot<ComputeConfig> _computeConfig`
- L27 _private* field_ `readonly Tracer _tracer`
- L32-37 _public ctor_ `public ComputeController(ComputeService computeService, IOptionsSnapshot<ComputeConfig> computeConfig, Tracer tracer)` — Constructor
- L47-71 _public method_ `public ActionResult<GetClusterResponse> GetCluster([FromBody] AssignComputeRequest request)` — attrs: `[HttpPost] [Authorize] [Route("/api/v2/compute/_cluster")]` — Find the most suitable cluster given a compute assignment request
- L83-89 _public method_ `public async Task<ActionResult<AssignComputeResponse>> AssignComputeResourceAsync([FromBody] AssignComputeRequest request, CancellationToken cancellationToken)` — attrs: `[HttpPost] [Authorize] [Route("/api/v2/compute")] [Obsolete("Resolve cluster with get cluster endpoint instead")]` — Add tasks to be executed remotely and auto-select appropriate compute cluster to use
- L101-173 _public method_ `public async Task<ActionResult<AssignComputeResponse>> AssignComputeResourceInClusterAsync(ClusterId clusterId, [FromBody] AssignComputeRequest request, CancellationToken cancellationToken)` — attrs: `[HttpPost] [Authorize] [Route("/api/v2/compute/{clusterId}")]` — Add tasks to be executed remotely
- L183-192 _public method_ `public async Task<ActionResult<UbaConfig>> AllocateUbaCacheServerAsync(ClusterId clusterId, CancellationToken cancellationToken)` — attrs: `[HttpPost] [Authorize] [Route("/api/v2/compute/{clusterId}/uba-cache")]` — Request a UBA cache server session
- L202-222 _public method_ `public async Task<ActionResult<GetResourceNeedsResponse>> GetResourceNeedsAsync(ClusterId clusterId)` — attrs: `[HttpGet] [Authorize] [Route("/api/v2/compute/{clusterId}/resource-needs")]` — Get current resource needs for active sessions
- L234-248 _public method_ `public async Task<ActionResult<AssignComputeResponse>> SetResourceNeedsAsync(ClusterId clusterId, [FromBody] ResourceNeedsMessage request)` — attrs: `[HttpPost] [Authorize] [Route("/api/v2/compute/{clusterId}/resource-needs")]` — Declare resource needs for a session to help server calculate current demand KnownPropertyNames for resource name property names

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Compute/ComputeRequest.cs` (HordeServer.Compute)


#### class `HordeServer.Compute.ComputeRequest`  
`public class ComputeRequest`  
_public; L11-31_
- desc: Request for a compute resource
- L16 _public property_ `public Requirements Requirements { get; }` — Requirements for the agent to satisfy this request
- L21 _public property_ `public ComputeTask Task { get; }` — Connection settings for the channel
- L26-30 _public ctor_ `public ComputeRequest(Requirements requirements, ComputeTask task)` — Constructor

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Compute/ComputeService.cs` (HordeServer.Compute)


#### class `HordeServer.Compute.ComputeServiceException`  
`public class ComputeServiceException : Exception`  
_public; L40-52_
- inherits: `Exception`
- desc: Exceptions related to compute service
- L45 _public property_ `public bool ShowToUser { get; init; }` — Whether this exception message can be shown to user or client
- L48-51 _public ctor_ `public ComputeServiceException(string? message, Exception? innerException = null, bool showToUser = false) : base(message, innerException)` — (inheritdoc)

#### class `HordeServer.Compute.NoComputeResourcesException`  
`public class NoComputeResourcesException(string? message, Exception? innerException = null) : ComputeServiceException(message, innerException, true)`  
_public; L57-61_
- desc: Exception when no compute resources available
- L59 _internal const_ `internal const string AllResourcesInUse = "Matching resources available but all are in use"`
- L60 _internal const_ `internal const string NoMatchingResources = "No matching resources available (in use or not)"`

#### enum `HordeServer.Compute.AllocationOutcome`  
`public enum AllocationOutcome`  
_public; L66-77_
- desc: Outcome for a compute allocation request
- L71 _public* enumerator_ `Accepted` — A lease was allocated
- L76 _public* enumerator_ `Denied` — A lease was not allocated

#### class `HordeServer.Compute.AllocateResourceParams`  
`public class AllocateResourceParams`  
_public; L82-155_
- desc: Internal parameters for allocating a resource
- L87 _public property_ `public ClusterId ClusterId { get; }` — Cluster ID
- L92 _public property_ `public ClaimsPrincipal User { get; init; }` — User allocating the resource
- L97 _public property_ `public UserId? UserId { get; init; }` — User ID allocating the resource
- L102 _public property_ `public ComputeProtocol Protocol { get; }` — Desired protocol version
- L107 _public property_ `public Requirements Requirements { get; }` — Criteria for selecting an agent
- L112 _public property_ `public string? RequestId { get; init; }` — Unique ID of this allocation request. If the same allocation retried, the same request ID should be used
- L117 _public property_ `public LeaseId? ParentLeaseId { get; init; }` — Optional parent lease
- L122 _public property_ `public IPAddress? RequesterIp { get; init; }` — IP address of the requester
- L125 _public property_ `public string? RequesterPublicIp { get; init; }` — (inheritdoc)
- L128 _public property_ `public Dictionary<string, int> Ports { get; init; }` — (inheritdoc)
- L131 _public property_ `public ConnectionMode? ConnectionMode { get; init; }` — (inheritdoc)
- L134 _public property_ `public bool? UsePublicIp { get; init; }` — (inheritdoc)
- L137 _public property_ `public ComputeEncryption Encryption { get; init; }` — (inheritdoc)
- L140 _public property_ `public int? InactivityTimeoutMs { get; init; }` — (inheritdoc)
- L143 _public property_ `public bool? UseUbaCache { get; init; }` — (inheritdoc)
- L148-154 _public ctor_ `public AllocateResourceParams(ClusterId clusterId, ClaimsPrincipal user, ComputeProtocol protocol, Requirements? requirements = null)` — Constructor

#### class `HordeServer.Compute.ComputeService`  
`public sealed class ComputeService : IHostedService, IAsyncDisposable`  
_public; L160-1021_
- inherits: `IHostedService, IAsyncDisposable`
- desc: Assigns compute leases to agents
- L165 _private field_ `private readonly TimeSpan _requestLogTtl = TimeSpan.FromMinutes(5)` — Time-to-live for each bucket of request (currently grouped per minute)
- L170 _private field_ `private readonly TimeSpan _requestLogMetricInterval = TimeSpan.FromMinutes(1)` — How often the queue metric of allocation requests should be calculated
- L175 _private field_ `private readonly TimeSpan _relayPortCleanupInterval = TimeSpan.FromMinutes(1)` — How often to look for stale leases and relayed ports
- L180 _private field_ `private readonly TimeSpan _resourceNeedsMaxAge = TimeSpan.FromMinutes(2)` — Max age before discarding a reported resource need
- L185 _public delegate_ `public delegate void ResourceNeedEvent(string clusterId, string poolId, string resourceName, int total)` — Delegate for resource need events
- L190 _public event_ `public event ResourceNeedEvent? OnResourceNeedsUpdated` — Event triggered when resource needs have been calculated and updated
- L192 _private* field_ `readonly IAgentCollection _agentCollection`
- L193 _private* field_ `readonly IAgentScheduler _agentScheduler`
- L194 _private* field_ `readonly ILogCollection _logCollection`
- L195 _private* field_ `readonly AgentService _agentService`
- L196 _private* field_ `readonly AgentRelayService _agentRelayService`
- L197 _private* field_ `readonly IRedisService _redisService`
- L198 _private* field_ `readonly HttpClient _httpClient`
- L199 _private* field_ `readonly IOptionsMonitor<ComputeServerConfig> _staticComputeConfig`
- L200 _private* field_ `readonly IOptionsMonitor<ComputeConfig> _computeConfig`
- L201 _private* field_ `readonly IClock _clock`
- L202 _private* field_ `readonly Tracer _tracer`
- L203 _private* field_ `readonly Counter<int> _allocationsAcceptedCount`
- L204 _private* field_ `readonly Counter<int> _allocationsDeniedCount`
- L205 _private* field_ `readonly ITicker _requestLogMetricTicker`
- L206 _private* field_ `readonly ITicker _relayPortCleanupTicker`
- L207 _private* field_ `readonly ILogger<ComputeService> _logger`
- L209 _private* field_ `List<Measurement<int>> _unservedMeasurements = new()`
- L210 _private* field_ `List<Measurement<int>> _resourceNeedsMeasurements = new()`
- L215-265 _public ctor_ `public ComputeService( IAgentCollection agentCollection, IAgentScheduler agentScheduler, ILogCollection logCollection, AgentService agentService, AgentRelayService agentRelayService, IRedisService redisService, HttpClient httpClient, IOptionsMonitor<ComputeServerConfig> staticComputeConfig, IOptionsMonitor<ComputeConfig> computeConfig, IClock clock, Tracer tracer, Meter meter, ILogger<ComputeService> logger)` — Constructor
- L268-272 _public method_ `public async Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L275-279 _public method_ `public async Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L282-286 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L288-292 _private method_ `private async ValueTask RequestLogMetricTickAsync(CancellationToken stoppingToken)`
- L294-297 _private method_ `private async ValueTask RelayPortCleanupTickAsync(CancellationToken cancellationToken)`
- L302-325 _internal method_ `internal async Task CleanStaleRelayPortsAsync(CancellationToken cancellationToken)` — Check for port mappings that either have no registered lease or possess an expired lease
- L327-339 _private method_ `private async Task<List<Measurement<int>>> CalculateUnservedRequestsMetricAsync()`
- L342-371 _internal method_ `internal async Task<List<Measurement<int>>> CalculateResourceNeedsAsync()`
- L379-524 _public method_ `public async Task<ComputeResource> TryAllocateResourceAsync(AllocateResourceParams arp, CancellationToken cancellationToken)` — Allocates a compute resource
- L526-542 _internal method_ `internal static bool VerifyUbaCache(ClaimsPrincipal user, ComputeClusterConfig clusterConfig)`
- L544-557 _private method_ `private string? ResolvePoolId(string? poolId, IPAddress? ipAddress)`
- L567-571 _public method_ `public async Task SetResourceNeedsAsync(ClusterId clusterId, string sessionId, string pool, Dictionary<string, int> resourceNeeds)` — Declare resource needs for a session to help server calculate current demand Any previous declaration associated with the same session ID will be replaced.
- L573-608 _internal method_ `internal async Task<List<SessionResourceNeeds>> GetResourceNeedsAsync()`
- L610 _private method_ `private static string RedisKeyResourceNeeds()`
- L627-632 _private method_ `private static string RedisKeyComputeRequests(DateTimeOffset timestamp)`
- L686-709 _internal method_ `internal async Task LogRequestAsync(AllocationOutcome outcome, string? requestId, Requirements requirements, LeaseId? parentLeaseId, TelemetrySpan currentSpan, CancellationToken cancellationToken = default)`
- L711-747 _internal method_ `internal async Task<List<RequestInfo>> GetUnservedRequestsAsync()`
- L749-754 _internal method_ `internal static Dictionary<string, int> GroupByPoolAndCount(List<RequestInfo> requests)`
- L763-771 _private method_ `private async Task<int?> GetNumActiveLeasesAsync(LeaseId? parentLeaseId, CancellationToken cancellationToken)` — Get the number of currently active leases belonging to the given parent lease. Allows compute allocation requests metric to be broken down by lease.
- L773-848 _private method_ `private async Task<ComputeResource?> TryAssignAsync(AllocateResourceParams arp, IAgent agent, ComputeTask computeTask, ComputeProtocol protocol, LeaseId leaseId)`
- L858-874 _public method_ `public static IPAddress ResolveRequesterIp(IPAddress? requesterIp, bool? usePublicIp, string? requesterPublicIp)` — Resolve IP of the requester
- L883-896 _public method_ `public static ClusterId FindBestComputeClusterId(ComputeConfig computeConfig, IPAddress? requesterIp)` — Find best compute cluster for given parameters
- L898-901 _private method_ `private static IPAddress FindBestRelayIp(IPAddress? clientIp, IPAddress? publicClientIp, IEnumerable<string> relayIps)`
- L904-908 _private method_ `private static IPAddress FindBestRelayIp(IPAddress? clientIp, IPAddress? publicClientIp, List<IPAddress> relayIps)` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Style", "IDE0060:Remove unused parameter", Justification = "To be implemented")]`
- L919-969 _public method_ `public async Task<UbaComputeResource> AllocateUbaCacheServerAsync( ClaimsPrincipal user, ComputeClusterConfig clusterConfig, int ttl, CancellationToken cancellationToken, HttpClient? httpClient = null)` — Allocate a UBA cache server session
- L971-985 _private* method_ `static ComputeTask CreateComputeTask(Dictionary<string, int> assignedResources, LogId? logId, ComputeEncryption encryption, byte[] certificateData, LeaseId? parentLeaseId, ComputeProtocol protocol, int? inactivityTimeoutMs)`
- L987-995 _private* method_ `static byte[] GenerateCert(ComputeEncryption encryption)`
- L997-1008 _internal method_ `internal static Encryption ConvertEncryptionFromProto(ComputeEncryption proto)`
- L1010-1020 _internal method_ `internal static ComputeEncryption ConvertEncryptionToProto(Encryption? json)`

#### record struct `HordeServer.Compute.ComputeService.MetricKey`  
`private record struct MetricKey(string ClusterId, string PoolId, string ResourceName)`  
_private; L341-341_

#### record struct `HordeServer.Compute.ComputeService.SessionResourceNeeds`  
`internal record struct SessionResourceNeeds(DateTime Timestamp, string ClusterId, string SessionId, string Pool, Dictionary<string, int> ResourceNeeds)`  
_internal; L620-625_
- desc: Record describing the resource needs for a session at a particular point in time
- L622 _public method_ `public string GetRedisHashKey()`
- L623 _public method_ `public string Serialize()`
- L624 _public method_ `public static SessionResourceNeeds Deserialize(string value)`

#### record `HordeServer.Compute.ComputeService.RequestInfo`  
`internal record RequestInfo(DateTimeOffset Timestamp, AllocationOutcome Outcome, string RequestId, string Pool, string? ParentLeaseId)`  
_internal; L642-684_
- desc: Record to be stored in Redis for representing a compute allocation request
- L644 _private const_ `private const int Version = 1`
- L646-656 _public method_ `public string Serialize()`
- L658 _public method_ `public static RequestInfo? Deserialize(RedisValue value)`
- L659-683 _public method_ `public static RequestInfo? Deserialize(string value)`

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Compute/ComputeTaskSource.cs` (HordeServer.Compute)


#### class `HordeServer.Compute.UbaComputeResource`  
`public class UbaComputeResource(string cacheEndpoint, string cacheSessionKey, bool writeAccess)`  
_public; L19-29_
- desc: (inheritdoc)
- L22 _public property_ `public string CacheEndpoint { get; }` — (inheritdoc)
- L25 _public property_ `public string CacheSessionKey { get; }` — (inheritdoc)
- L28 _public property_ `public bool WriteAccess { get; }` — (inheritdoc)

#### class `HordeServer.Compute.ComputeResourcePort`  
`public class ComputeResourcePort`  
_public; L34-91_
- desc: A TCP/IP port used by a compute resource, and how it is mapped externally -> internally
- L40 _public property_ `public int Port { get; }` — Externally visible port that is mapped to agent port In direct connection mode, these two are identical.
- L45 _public property_ `public int AgentPort { get; }` — Port the local process on the agent is listening on
- L52-56 _public ctor_ `public ComputeResourcePort(int port, int agentPort)` — Constructor
- L59-62 _protected method_ `protected bool Equals(ComputeResourcePort other)` — (inheritdoc)
- L65-78 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L81-84 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L87-90 _public method_ `public override string ToString()` — (inheritdoc)

#### class `HordeServer.Compute.ComputeResource`  
`public class ComputeResource`  
_public; L96-171_
- desc: Information about a compute resource
- L99 _public property_ `public ConnectionMode ConnectionMode { get; }` — (inheritdoc)
- L104 _public property_ `public IPAddress Ip { get; }` — IP address of the agent
- L107 _public property_ `public string? ConnectionAddress { get; }` — (inheritdoc)
- L110 _public property_ `public IReadOnlyDictionary<string, ComputeResourcePort> Ports { get; }` — (inheritdoc)
- L113 _public property_ `public UbaComputeResource? Uba { get; set; }` — (inheritdoc)
- L118 _public property_ `public ComputeTask Task { get; }` — Information about the compute task
- L123 _public property_ `public IReadOnlyList<string> Properties { get; }` — Properties of the assigned agent
- L128 _public property_ `public AgentId AgentId { get; }` — Agent id on the remote machine
- L133 _public property_ `public string? AgentVersion { get; }` — Agent version on the remote machine
- L138 _public property_ `public ComputeProtocol Protocol { get; }` — Compute protocol this resource is using
- L143 _public property_ `public LeaseId LeaseId { get; }` — Lease id on the remote machine
- L148-170 _public ctor_ `public ComputeResource( ConnectionMode connectionMode, IPAddress ip, string? connectionAddress, IReadOnlyDictionary<string, ComputeResourcePort> ports, ComputeTask task, IReadOnlyList<string> properties, AgentId agentId, string? agentVersion, ComputeProtocol protocol, LeaseId leaseId)` — Constructor

#### class `HordeServer.Compute.ComputeTaskSource`  
`public class ComputeTaskSource : TaskSourceBase<ComputeTask>`  
_public; L176-317_
- inherits: `TaskSourceBase<ComputeTask>`
- desc: Dispatches requests for compute resources
- L194 _public property_ `public override string Type => ...` — (inheritdoc)
- L197 _public property_ `public override TaskSourceFlags Flags => ...` — (inheritdoc)
- L199 _private* field_ `readonly AgentRelayService _agentRelay`
- L200 _private* field_ `readonly ILeaseCollection _leaseCollection`
- L201 _private* field_ `readonly IOptionsMonitor<ComputeConfig> _computeConfig`
- L202 _private* field_ `readonly ILogger _logger`
- L204 _private* field_ `readonly object _lockObject = new object()`
- L205 _private* field_ `readonly Dictionary<ClusterId, LinkedList<Waiter>> _waiters = ...`
- L205 _private* field_ `readonly Dictionary< _waiters = new Dictionary<ClusterId, LinkedList<Waiter>>()`
- L210-216 _public ctor_ `public ComputeTaskSource(AgentRelayService agentRelay, ILeaseCollection leaseCollection, IOptionsMonitor<ComputeConfig> computeConfig, ILogger<ComputeTaskSource> logger)` — Constructor
- L219-222 _public method_ `public override Task<Task<CreateLeaseOptions?>> AssignLeaseAsync(IAgent agent, CancellationToken cancellationToken)` — (inheritdoc)
- L225-231 _public method_ `public override async Task OnLeaseFinishedAsync(IAgent agent, LeaseId leaseId, ComputeTask payload, LeaseOutcome outcome, ReadOnlyMemory<byte> output, ILogger logger, CancellationToken cancellationToken)` — (inheritdoc)
- L233-300 _private* method_ `async Task<CreateLeaseOptions?> WaitInternalAsync(IAgent agent, CancellationToken cancellationToken)`
- L303-316 _public method_ `public override async ValueTask GetLeaseDetailsAsync(Any payload, Dictionary<string, string> details, CancellationToken cancellationToken)` — (inheritdoc)

#### class `HordeServer.Compute.ComputeTaskSource.Waiter`  
`class Waiter`  
_private*; L178-191_
- L180 _public property_ `public IAgent Agent { get; }`
- L181 _public property_ `public IPAddress Ip { get; }`
- L182 _public property_ `public int Port { get; }`
- L183 _public property_ `public TaskCompletionSource<CreateLeaseOptions?> Lease { get; }`
- L185-190 _public ctor_ `public Waiter(IAgent agent, IPAddress ip, int port)`

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Compute/RedisMessageQueue.cs` (HordeServer.Compute)


#### interface `HordeServer.Compute.IMessageQueue`  
`interface IMessageQueue<T> where T : class`  
_internal*; L12-35_
- constraints: `where T : class`
- desc: Interface for a distributed message queue
- L19 _public* method_ `Task PostAsync(string channelId, T message)` — Adds messages to the queue
- L26 _public* method_ `Task<List<T>> ReadMessagesAsync(string channelId)` — Waits for a message to be available on the given channel
- L34 _public* method_ `Task<List<T>> WaitForMessagesAsync(string channelId, CancellationToken cancellationToken)` — Waits for a message to be available on the given channel

#### class `HordeServer.Compute.RedisMessageQueue`  
`class RedisMessageQueue<T> : IMessageQueue<T>, IDisposable where T : class`  
_internal*; L41-175_
- inherits: `IMessageQueue<T>, IDisposable`
- constraints: `where T : class`
- desc: Implementation of a message queue using Redis
- L43 _private* field_ `readonly IDatabase _redis`
- L44 _private* field_ `readonly RedisKey _keyPrefix`
- L45 _private* field_ `readonly RedisChannel _updateChannel`
- L46 _private* field_ `readonly Dictionary<string, TaskCompletionSource<bool>> _channelWakeEvents = ...`
- L46 _private* field_ `readonly Dictionary< _channelWakeEvents = new Dictionary<string, TaskCompletionSource<bool>>()`
- L49 _private* property_ `TimeSpan ExpireTime { get; set; }`
- L56-63 _public ctor_ `public RedisMessageQueue(IDatabase redis, RedisKey keyPrefix)` — Constructor
- L66-69 _public method_ `public void Dispose()` — (inheritdoc)
- L76-87 _private* method_ `void OnChannelUpdate(RedisChannel channel, RedisValue value)` — Callback for a message being posted to a channel
- L94-97 _private* method_ `RedisListKey<T> GetChannel(string channelId)` — Gets the set of messages for a channel
- L100-110 _public method_ `public async Task PostAsync(string channelId, T message)` — (inheritdoc)
- L112-121 _private* method_ `async Task<bool> ReadMessagesAsync(RedisListKey<T> list, List<T> messages)`
- L124-129 _public method_ `public async Task<List<T>> ReadMessagesAsync(string channelId)` — (inheritdoc)
- L132-174 _public method_ `public async Task<List<T>> WaitForMessagesAsync(string channelId, CancellationToken cancellationToken)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Compute/RedisTaskScheduler.cs` (HordeServer.Compute)


#### interface `HordeServer.Compute.ITaskScheduler`  
`interface ITaskScheduler<TQueueId, TTask> where TQueueId : notnull where TTask : class`  
_internal*; L18-59_
- constraints: `where TQueueId : notnull where TTask : class`
- desc: Interface for a queue of compute operations, each of which may have different requirements for the executing machines.
- L28 _public* method_ `Task EnqueueAsync(TQueueId queueId, TTask taskId, bool atFront)` — Adds a task to a queue
- L35 _public* method_ `Task<TTask?> DequeueAsync(TQueueId queueId)` — Dequeue any task from a particular queue
- L43 _public* method_ `Task<Task<(TQueueId, TTask)?>> DequeueAsync(Func<TQueueId, ValueTask<bool>> predicate, CancellationToken token = default)` — Dequeues a task that the given agent can execute
- L49 _public* method_ `Task<List<TQueueId>> GetInactiveQueuesAsync()` — Gets hashes of all the inactive task queues
- L58 _public* method_ `Task<int> GetNumQueuedTasksAsync(Func<TQueueId, ValueTask<bool>> predicate, CancellationToken token = default)` — Get number of tasks that a given pool/agent can execute A read-only operation and will not affect any queue.

#### class `HordeServer.Compute.RedisTaskScheduler`  
`public sealed class RedisTaskScheduler<TQueueId, TTask> : ITaskScheduler<TQueueId, TTask>, IAsyncDisposable where TQueueId : notnull where TTask : class`  
_public; L66-478_
- inherits: `ITaskScheduler<TQueueId, TTask>, IAsyncDisposable`
- constraints: `where TQueueId : notnull where TTask : class`
- desc: Implementation of ITaskScheduler{TQueue, TTask} using Redis for storage
- L82 _private* field_ `readonly RedisConnectionPool _redisConnectionPool`
- L83 _private* field_ `readonly RedisKey _baseKey`
- L84 _private* field_ `readonly RedisSetKey<TQueueId> _queueIndex`
- L85 _private* field_ `readonly RedisHashKey<TQueueId, DateTime> _activeQueues`
- L85 _private* field_ `readonly RedisHashKey< _activeQueues`
- L86 _private* field_ `IReadOnlySet<TQueueId> _localActiveQueues = new HashSet<TQueueId>()`
- L87 _private* field_ `readonly Stopwatch _resetActiveQueuesTimer = Stopwatch.StartNew()`
- L88 _private* field_ `readonly List<Listener> _listeners = new List<Listener>()`
- L89 _private* field_ `readonly RedisChannel<TQueueId> _newQueueChannel`
- L90 _private* field_ `readonly Task _queueUpdateTask`
- L91 _private* field_ `readonly CancellationTokenSource _cancellationSource = new CancellationTokenSource()`
- L92 _private* field_ `readonly ILogger _logger`
- L100-110 _public ctor_ `public RedisTaskScheduler(RedisConnectionPool redisConnectionPool, RedisKey baseKey, ILogger logger)` — Constructor
- L113-127 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L134-137 _private* method_ `RedisListKey<TTask> GetQueueKey(TQueueId queueId)` — Gets the key for a list of tasks for a particular queue
- L142-152 _private* method_ `static Task<long> PushTaskAsync(IDatabaseAsync database, RedisListKey<TTask> list, TTask task, When when, CommandFlags flags, bool atFront)` — Pushes a task onto either end of a queue
- L160-187 _public method_ `public async Task EnqueueAsync(TQueueId queueId, TTask task, bool atFront)` — Adds a task to a particular queue, creating and adding that queue to the index if necessary
- L195-209 _public method_ `public async Task<Task<(TQueueId, TTask)?>> DequeueAsync(Func<TQueueId, ValueTask<bool>> predicate, CancellationToken token = default)` — Dequeues an item for execution by the given agent
- L211-246 _private method_ `private async Task<(TQueueId, TTask)?> WaitToDequeueAsync(TQueueId[] queues, Func<TQueueId, ValueTask<bool>> predicate, CancellationToken token)`
- L254-268 _private* method_ `async Task<(TQueueId, TTask)?> TryAssignToLocalAgentAsync(TQueueId[] queueIds, Func<TQueueId, ValueTask<bool>> predicate)` — Attempts to dequeue a task from a set of queue
- L275-295 _public method_ `public async Task<TTask?> DequeueAsync(TQueueId queueId)` — Dequeues the item at the front of a queue
- L302-339 _private* method_ `async ValueTask AddActiveQueueAsync(TQueueId queueId)` — Marks a queue key as being actively monitored, preventing it being returned by GetInactiveQueuesAsync
- L345-371 _public method_ `public async Task<List<TQueueId>> GetInactiveQueuesAsync()` — Find any inactive keys
- L379-392 _public method_ `public async Task<int> GetNumQueuedTasksAsync(Func<TQueueId, ValueTask<bool>> predicate, CancellationToken token = default)`
- L394-412 _private* method_ `async Task UpdateQueuesAsync(CancellationToken cancellationToken)`
- L414-477 _private* method_ `async Task<bool> TryDispatchToNewQueueAsync(TQueueId queueId)`

#### class `HordeServer.Compute.RedisTaskScheduler.Listener`  
`class Listener`  
_private*; L70-80_
- L72 _public field_ `public Func<TQueueId, ValueTask<bool>> _predicate`
- L72 _public field_ `public Func< _predicate`
- L73 _public property_ `public TaskCompletionSource<(TQueueId, TTask)?> CompletionSource { get; }`
- L75-79 _public ctor_ `public Listener(Func<TQueueId, ValueTask<bool>> predicate)`

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Compute/TunnelService.cs` (HordeServer.Compute)


#### class `HordeServer.Compute.TunnelService`  
`public sealed class TunnelService : IHostedService, IDisposable`  
_public; L15-173_
- inherits: `IHostedService, IDisposable`
- desc: Tunnels connections between Horde agents and compute initiators
- L17 _private const_ `private const int BufferSize = 4096`
- L19 _private field_ `private readonly CancellationTokenSource _cancellationSource`
- L20 _private field_ `private readonly ComputeServerConfig _staticComputeConfig`
- L21 _private field_ `private readonly ILogger _logger`
- L22 _private field_ `private Task? _serverTask`
- L27 _internal property_ `internal Task? ServerTask => ...` — Accessor for the server task, for tests
- L32-37 _public ctor_ `public TunnelService(IOptions<ComputeServerConfig> staticComputeConfig, ILogger<TunnelService> logger)` — Constructor
- L40-43 _public method_ `public void Dispose()` — (inheritdoc)
- L46-50 _public method_ `public Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L57-60 _public method_ `public void Start(IPAddress address)` — Start the tunnel server
- L63-82 _public method_ `public async Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L84-119 _private* method_ `async Task HandleClientAsync(TcpClient client, CancellationToken cancellationToken)`
- L121-129 _private method_ `private static async Task RelayStreamsAsync(Stream input, Stream output, CancellationToken cancellationToken)`
- L131-156 _private* method_ `async Task RunTcpListenerAsync(IPAddress address, int port, Func<TcpClient, CancellationToken, Task> handleConnectionAsync, CancellationToken cancellationToken)`
- L158-172 _private* method_ `async Task HandleConnectionGuardedAsync(TcpClient tcpClient, Func<TcpClient, CancellationToken, Task> handleConnectionAsync, CancellationToken cancellationToken)`

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/ComputeAclModifier.cs` (HordeServer.Compute)


#### class `HordeServer.ComputeAclModifier`  
`class ComputeAclModifier : IDefaultAclModifier`  
_internal*; L15-32_
- inherits: `IDefaultAclModifier`
- L18-31 _public method_ `public void Apply(DefaultAclBuilder acl)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/ComputeConfig.cs` (HordeServer.Compute)


#### class `HordeServer.ComputeConfig`  
`public class ComputeConfig : IPluginConfig`  
_public; L34-186_
- attrs: `[ConfigIncludeRoot] [ConfigMacroScope]`
- inherits: `IPluginConfig`
- desc: Configuration for the compute system
- L39 _public property_ `public List<ConfigInclude> Include { get; set; }` — Includes for other configuration files
- L44 _public property_ `public List<ConfigMacro> Macros { get; set; }` — Macros within the compute config
- L49 _public property_ `public AclConfig Acl { get; set; }` — Inherited root acl
- L54 _public property_ `public ConfigVersion VersionEnum { get; set; }` — Config version number
- L59 _public property_ `public TelemetryStoreId TelemetryStoreId { get; set; }` — Telemetry store for lease and compute telemetry data
- L64 _public property_ `public List<AgentRateConfig> Rates { get; set; }` — List of costs of a particular agent type
- L69 _public property_ `public List<ComputeClusterConfig> Clusters { get; set; }` — List of compute profiles
- L74 _public property_ `public List<PoolConfig> Pools { get; set; }` — List of pools
- L79 _public property_ `public List<AgentSoftwareConfig> Software { get; set; }` — List of costs of a particular agent type
- L84 _public property_ `public List<NetworkConfig> Networks { get; set; }` — List of networks
- L86 _private field_ `private readonly Dictionary<ClusterId, ComputeClusterConfig> _computeClusterLookup = ...`
- L86 _private field_ `private readonly Dictionary< _computeClusterLookup = new Dictionary<ClusterId, ComputeClusterConfig>()`
- L87 _private field_ `private readonly Dictionary<PoolId, PoolConfig> _poolLookup = ...`
- L87 _private field_ `private readonly Dictionary< _poolLookup = new Dictionary<PoolId, PoolConfig>()`
- L90-108 _public method_ `public void PostLoad(PluginConfigOptions configOptions)` — (inheritdoc)
- L113 _public method_ `public bool Authorize(AclAction action, ClaimsPrincipal principal)` — Authorize a user to perform a specific action
- L122 _public method_ `public bool TryGetComputeCluster(ClusterId clusterId, [NotNullWhen(true)] out ComputeClusterConfig? config)` — Attempts to get compute cluster configuration from this object
- L131-144 _public method_ `public bool TryGetNetworkConfig(IPAddress ip, [NotNullWhen(true)] out NetworkConfig? networkConfig)` — Attempt to resolve an IP address to a network config
- L146-177 _private method_ `private static bool IsIpInBlock(IPAddress ip, string? cidrBlock)`
- L185 _public method_ `public bool TryGetPool(PoolId poolId, [NotNullWhen(true)] out PoolConfig? config)` — Attempts to get configuration for a pool from this object

#### class `HordeServer.AgentSoftwareConfig`  
`public class AgentSoftwareConfig`  
_public; L192-203_
- attrs: `[DebuggerDisplay("{ToolId}")]`
- desc: Selects different agent software versions by evaluating a condition
- L197 _public property_ `public ToolId ToolId { get; set; }` — Tool identifier
- L202 _public property_ `public Condition? Condition { get; set; }` — Condition for using this channel

#### class `HordeServer.AgentRateConfig`  
`public class AgentRateConfig`  
_public; L208-221_
- desc: Describes the monetary cost of agents matching a particular criteria
- L214 _public property_ `public Condition? Condition { get; set; }` — attrs: `[CbField("c")]` — Condition string
- L220 _public property_ `public double Rate { get; set; }` — attrs: `[CbField("r")]` — Rate for this agent

#### class `HordeServer.NetworkConfig`  
`public class NetworkConfig`  
_public; L227-252_
- desc: Describes a network The ID describes any logical grouping, such as region, availability zone, rack or office location.
- L233 _public property_ `public string? Id { get; set; }` — attrs: `[CbField("id")]` — ID for this network
- L239 _public property_ `public string? CidrBlock { get; set; }` — attrs: `[CbField("cb")]` — CIDR block
- L245 _public property_ `public string? Description { get; set; }` — attrs: `[CbField("d")]` — Human-readable description
- L251 _public property_ `public string? ComputeId { get; set; }` — attrs: `[CbField("cid")]` — Compute ID for this network (used when allocating compute resources)

#### class `HordeServer.UbaComputeClusterConfig`  
`public class UbaComputeClusterConfig`  
_public; L259-281_
- desc: Configuration settings for Unreal Build Accelerator (UBA) for a compute cluster Contains cache server connectivity and other UBA-related settings. Ensure all cache related fields are non-null to activate use of cache.
- L266 _public property_ `public string? CacheEndpoint { get; set; }` — Host and port for connecting to the UBA cache server (host:port format) As specified with `-port=[PORT]` to UBA cache process. Serves all cache requests and must be accessible to both agents and initiators running UBA / Unreal Build Tool.
- L274 _public property_ `public string? CacheHttpEndpoint { get; set; }` — Host and port for HTTP management of UBA cache server (host:port format) As specified with `-http=[PORT]` to UBA cache process. This port is used by Horde to manage the UBA cache, such as adding new cache session keys for initiators For improved security, only allow Horde server to access this port
- L280 _public property_ `public string? CacheHttpCrypto { get; set; }` — AES encryption key used for secure Horde-to-cache-server communication As specified with `-httpcrypto=[KEY]` to UBA cache process.

#### class `HordeServer.ComputeClusterConfig`  
`public class ComputeClusterConfig`  
_public; L287-350_
- attrs: `[DebuggerDisplay("{Id}")]`
- desc: Profile for executing compute requests
- L292 _public property_ `public ClusterId Id { get; set; }` — Name of the partition
- L297 _public property_ `public string NamespaceId { get; set; }` — Name of the namespace to use
- L302 _public property_ `public string RequestBucketId { get; set; }` — Name of the input bucket
- L307 _public property_ `public string ResponseBucketId { get; set; }` — Name of the output bucket
- L312 _public property_ `public Condition? Condition { get; set; }` — Filter for agents to include
- L317 _public property_ `public AclConfig Acl { get; set; }` — Access control list
- L322 _public property_ `public UbaComputeClusterConfig? Uba { get; set; }` — Configuration settings for Unreal Build Accelerator (UBA) for a compute cluster
- L328-341 _public method_ `public void PostLoad(AclConfig parentAcl)` — Callback post loading this config file
- L348 _public method_ `public bool Authorize(AclAction action, ClaimsPrincipal user)` — Authorizes a user to perform a given action

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/ComputePlugin.cs` (HordeServer.Compute)


#### class `HordeServer.ComputePlugin`  
`public class ComputePlugin : IPluginStartup`  
_public; L35-192_
- attrs: `[Plugin("Compute", GlobalConfigType = typeof(ComputeConfig), ServerConfigType = typeof(ComputeServerConfig))]`
- inherits: `IPluginStartup`
- desc: Entry point for the storage plugin
- L37 _private* field_ `readonly IServerInfo _serverInfo`
- L38 _private* field_ `readonly ComputeServerConfig _staticComputeConfig`
- L43-47 _public ctor_ `public ComputePlugin(IServerInfo serverInfo, ComputeServerConfig staticComputeConfig)` — Constructor
- L50-59 _public method_ `public void Configure(IApplicationBuilder app)` — (inheritdoc)
- L62-191 _public method_ `public void ConfigureServices(IServiceCollection services)` — (inheritdoc)

#### class `HordeServer.ComputePluginExtensions`  
`public static class ComputePluginExtensions`  
_public; L197-213_
- desc: Helper methods for compute config
- L202 _public method_ `public static void AddComputeConfig(this IDictionary<PluginName, IPluginConfig> dictionary, ComputeConfig computeConfig)` — Configures the compute plugin
- L208-212 _public method_ `public static ComputeConfig GetComputeConfig(this IDictionary<PluginName, IPluginConfig> plugins)` — Get the compute plugin config

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/ComputeResponseFilter.cs` (HordeServer.Compute)


#### class `HordeServer.ComputeResponseFilter`  
`class ComputeResponseFilter : IPluginResponseFilter`  
_internal*; L12-35_
- inherits: `IPluginResponseFilter`
- L14 _private* field_ `readonly IOptionsMonitor<ComputeConfig> _computeConfig`
- L16-19 _public ctor_ `public ComputeResponseFilter(IOptionsMonitor<ComputeConfig> computeConfig)`
- L21-34 _public method_ `public void Apply(HttpContext context, object response)`

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/ComputeServerConfig.cs` (HordeServer.Compute)


#### class `HordeServer.ComputeServerConfig`  
`public class ComputeServerConfig : PluginServerConfig`  
_public; L14-80_
- inherits: `PluginServerConfig`
- desc: Static configuration for the compute plugin
- L19 _public property_ `public bool EnableUpgradeTasks { get; set; }` — Whether to enable the upgrade task source, always upgrading agents to the latest version
- L24 _public property_ `public bool WithAws { get; set; }` — Whether to enable Amazon Web Services (AWS) specific features
- L31 _public property_ `public string[] AwsRegions { get; set; }` — List of AWS regions for Horde to be aware of (e.g. us-east-1 or eu-central-1) Right now, this is only used for replicating CloudWatch metrics to multiple regions Amazon.RegionEndpoint
- L37 _public property_ `public string[] AwsAutoScalingQueueUrls { get; set; }` — AWS SQS queue URLs where lifecycle events from EC2 auto-scaling are received AwsAutoScalingLifecycleService
- L42 _public property_ `public FleetManagerType FleetManagerV2 { get; set; }` — Default fleet manager to use (when not specified by pool)
- L48 _public property_ `public JsonObject? FleetManagerV2Config { get; set; }` — attrs: `[JsonConverter(typeof(JsonObjectOrStringConverter))]` — Config for the fleet manager (serialized JSON)
- L53 _public property_ `public bool AutoEnrollAgents { get; set; }` — Whether to automatically enroll agents in the farm
- L58 _public property_ `public PoolSizeStrategy DefaultAgentPoolSizeStrategy { get; set; }` — Default agent pool sizing strategy for pools that doesn't have one explicitly configured
- L63 _public property_ `public int AgentPoolScaleOutCooldownSeconds { get; set; }` — Scale-out cooldown for auto-scaling agent pools (in seconds). Can be overridden by per-pool settings.
- L68 _public property_ `public int AgentPoolScaleInCooldownSeconds { get; set; }` — Scale-in cooldown for auto-scaling agent pools (in seconds). Can be overridden by per-pool settings.
- L73 _public property_ `public int ComputeTunnelPort { get; set; }` — Port to listen on for tunneling compute sockets to agents
- L79 _public property_ `public string? ComputeTunnelAddress { get; set; }` — What address (host:port) clients should connect to for compute socket tunneling Port may differ from ComputeTunnelPort if Horde server is behind a reverse proxy/firewall

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Debug/ComputeDebugController.cs` (HordeServer.Compute)


#### class `HordeServer.Debug.ComputeDebugController`  
`class ComputeDebugController : HordeControllerBase`  
_internal*; L26-94_
- attrs: `[ApiController] [Authorize] [DebugEndpoint] [Tags("Debug")]`
- inherits: `HordeControllerBase`
- desc: Debug functionality for the compute system
- L28 _private* field_ `readonly AgentRelayService _agentRelayService`
- L29 _private* field_ `readonly IOptionsSnapshot<ComputeConfig> _computeConfig`
- L31-35 _public ctor_ `public ComputeDebugController(AgentRelayService agentRelayService, IOptionsSnapshot<ComputeConfig> computeConfig)`
- L42-72 _public method_ `public async Task<ActionResult<object>> AddPortMappingAsync([FromQuery] string? clientIpStr = null, [FromQuery] string? agentIpStr = null, [FromQuery] int? agentPort = null)` — attrs: `[HttpGet] [Route("/api/v1/debug/relay/add-port")]` — Add a port mapping for agent relay
- L79-93 _public method_ `public ActionResult<object> GetNetworkId([FromQuery] string? ipAddress = null)` — attrs: `[HttpGet] [Route("/api/v1/debug/network-id")]` — Get the network ID for a given IP address

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Logs/ILog.cs` (HordeServer.Compute)


#### interface `HordeServer.Logs.ILog`  
`public interface ILog`  
_public; L21-149_
- desc: Information about a log file
- L26 _public* property_ `LogId Id { get; }` — Identifier for the log. Randomly generated.
- L31 _public* property_ `JobId JobId { get; }` — Unique id of the job containing this log
- L36 _public* property_ `LeaseId? LeaseId { get; }` — The lease allowed to write to this log
- L41 _public* property_ `SessionId? SessionId { get; }` — The session allowed to write to this log
- L46 _public* property_ `LogType Type { get; }` — Type of data stored in this log
- L51 _public* property_ `NamespaceId NamespaceId { get; }` — Namespace containing the log data
- L56 _public* property_ `RefName RefName { get; }` — Name of the ref used to store data for this log
- L61 _public* property_ `AclScopeName AclScopeName { get; }` — Acl scope that owns this log
- L67 _public* method_ `Task DeleteAsync(CancellationToken cancellationToken = default)` — Delete this log
- L76 _public* method_ `Task<List<Utf8String>> ReadLinesAsync(int index, int count, CancellationToken cancellationToken = default)` — Read a set of lines from the given log file
- L83 _public* method_ `Task<LogMetadata> GetMetadataAsync(CancellationToken cancellationToken)` — Gets metadata about the log file
- L92 _public* method_ `Task<ILog> UpdateLineCountAsync(int lineCount, bool complete, CancellationToken cancellationToken = default)` — Updates the line count for a log file (v2 backend only)
- L99 _public* method_ `Task<Stream> OpenRawStreamAsync(CancellationToken cancellationToken = default)` — Gets lines from the given log
- L108 _public* method_ `Task<Stream> OpenRawStreamAsync(long offset, long length, CancellationToken cancellationToken)` — Gets lines from the given log
- L116 _public* method_ `Task CopyPlainTextStreamAsync(Stream outputStream, CancellationToken cancellationToken = default)` — Parses a stream of json text and outputs plain text
- L127 _public* method_ `Task<List<int>> SearchLogDataAsync(string text, int firstLine, int count, SearchStats stats, CancellationToken cancellationToken)` — Search for the specified text in a log file
- L136 _public* method_ `Task AddEventsAsync(List<NewLogEventData> newEvents, CancellationToken cancellationToken = default)` — Creates a new event
- L146 _public* method_ `Task<List<ILogAnchor>> GetAnchorsAsync(ObjectId? spanId = null, int? index = null, int? count = null, CancellationToken cancellationToken = default)` — Finds events within a log file

#### interface `HordeServer.Logs.ILogAnchor`  
`public interface ILogAnchor`  
_public; L154-186_
- desc: Anchor within a log files
- L159 _public property_ `public LogId LogId { get; }` — Unique id of the log containing this event
- L164 _public property_ `public LogEventSeverity Severity { get; }` — Severity of the event
- L169 _public property_ `public int LineIndex { get; }` — Index of the first line for this event
- L174 _public property_ `public int LineCount { get; }` — Number of lines in the event
- L179 _public property_ `public ObjectId? SpanId { get; }` — Span id for this log event
- L185 _public method_ `public Task<ILogEventData> GetDataAsync(CancellationToken cancellationToken = default)` — Gets the data for this log event

#### interface `HordeServer.Logs.ILogEventData`  
`public interface ILogEventData`  
_public; L191-212_
- desc: Interface for event data
- L196 _public* property_ `LogEventSeverity Severity { get; }` — The log level
- L201 _public* property_ `EventId? EventId { get; }` — The type of event
- L206 _public* property_ `string Message { get; }` — The complete rendered message, in plaintext
- L211 _public* property_ `IReadOnlyList<JsonLogEvent> Lines { get; }` — Gets this event data as a JSON objects

#### class `HordeServer.Logs.NewLogEventData`  
`public class NewLogEventData`  
_public; L217-238_
- desc: Represents a node in the graph
- L222 _public property_ `public LogEventSeverity Severity { get; set; }` — Severity of the event
- L227 _public property_ `public int LineIndex { get; set; }` — Index of the first line for this event
- L232 _public property_ `public int LineCount { get; set; }` — Number of lines in the event
- L237 _public property_ `public ObjectId? SpanId { get; set; }` — The span this this event belongs to

#### class `HordeServer.Logs.LogEventExtensions`  
`public static class LogEventExtensions`  
_public; L243-255_
- desc: Extensions for parsing log event properties
- L251-254 _public method_ `public static IEnumerable<JsonProperty> FindPropertiesOfType(this ILogEventData data, Utf8String type)` — Find all properties of the given type in a particular log line

#### class `HordeServer.Logs.LogMetadata`  
`public class LogMetadata`  
_public; L260-271_
- desc: Metadata about a log file
- L265 _public property_ `public long Length { get; set; }` — Length of the log file
- L270 _public property_ `public int MaxLineIndex { get; set; }` — Number of lines in the log file

#### class `HordeServer.Logs.LogExtensions`  
`public static class LogExtensions`  
_public; L276-320_
- desc: Extension methods for log files
- L284-287 _public method_ `public static Task AddEventAsync(this ILog log, NewLogEventData newEvent, CancellationToken cancellationToken = default)` — Creates a new event
- L295-306 _public method_ `public static bool AuthorizeForSession(this ILog log, ClaimsPrincipal user)` — Determines if the user is authorized to perform an action on a particular template
- L315-319 _public method_ `public static async Task CopyRawStreamAsync(this ILog log, Stream outputStream, CancellationToken cancellationToken)` — Parses a stream of json text and outputs plain text

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Logs/ILogCollection.cs` (HordeServer.Compute)


#### interface `HordeServer.Logs.ILogCollection`  
`public interface ILogCollection`  
_public; L15-61_
- desc: Wrapper around the jobs collection in a mongo DB
- L28 _public* method_ `Task<ILog> AddAsync(JobId jobId, LeaseId? leaseId, SessionId? sessionId, LogType type, LogId? logId = null, AclScopeName aclScopeName = default, CancellationToken cancellationToken = default)` — Adds a new log
- L36 _public* method_ `Task<ILog?> GetAsync(LogId logId, CancellationToken cancellationToken = default)` — Gets a log by ID
- L49 _public* method_ `Task<IReadOnlyList<ILogAnchor>> FindAnchorsForSpansAsync(IEnumerable<ObjectId> spanIds, LogId[]? logIds = null, int index = 0, int count = 10, CancellationToken cancellationToken = default)` — Finds a list of events for a set of spans
- L58 _public* method_ `Task AddSpanToEventsAsync(IEnumerable<ILogAnchor> events, ObjectId spanId, CancellationToken cancellationToken = default)` — Update the span for an event

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Logs/ILogExtAuthProvider.cs` (HordeServer.Compute)


#### interface `HordeServer.Logs.ILogExtAuthProvider`  
`public interface ILogExtAuthProvider`  
_public; L11-21_
- desc: Interface which allows
- L20 _public method_ `public ValueTask<bool> AuthorizeAsync(ILog log, AclAction action, ClaimsPrincipal principal, CancellationToken cancellationToken = default)` — Determine if the given principal can access a particular log

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Logs/ILogExtIssueProvider.cs` (HordeServer.Compute)


#### interface `HordeServer.Logs.ILogExtIssueProvider`  
`public interface ILogExtIssueProvider`  
_public; L10-19_
- desc: Interface which provides issue identifiers for event ids in log documents
- L18 _public method_ `public ValueTask<int?> GetIssueIdAsync(ObjectId spanId, CancellationToken cancellationToken = default)` — Gets an issue it for the given span

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Logs/LogAclAction.cs` (HordeServer.Compute)


#### class `HordeServer.Logs.LogAclAction`  
`public static class LogAclAction`  
_public; L10-41_
- desc: ACL actions for logs
- L15 _public property_ `public static AclAction CreateLog { get; }` — Ability to create a log. Implicitly granted to agents.
- L20 _public property_ `public static AclAction UpdateLog { get; }` — Ability to update log metadata
- L25 _public property_ `public static AclAction ViewLog { get; }` — Ability to view a log contents
- L30 _public property_ `public static AclAction WriteLogData { get; }` — Ability to write log data
- L35 _public property_ `public static AclAction CreateEvent { get; }` — Ability to create events
- L40 _public property_ `public static AclAction ViewEvent { get; }` — Ability to view events

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Logs/LogCollection.cs` (HordeServer.Compute)


#### class `HordeServer.Logs.LogCollection`  
`public sealed class LogCollection : ILogCollection, IDisposable`  
_public; L30-1033_
- inherits: `ILogCollection, IDisposable`
- desc: Wrapper around the jobs collection in a mongo DB
- L258 _private* field_ `readonly IMongoCollection<LogDocument> _logCollection`
- L259 _private* field_ `readonly IMongoCollection<LogAnchorDocument> _logEvents`
- L260 _private* field_ `readonly IMongoCollection<LegacyLogEventDocument> _legacyEvents`
- L261 _private* field_ `readonly LogTailService _logTailService`
- L262 _private* field_ `readonly StorageService _storageService`
- L263 _private* field_ `readonly Tracer _tracer`
- L264 _private* field_ `readonly ILogger _logger`
- L265 _private* field_ `readonly IMemoryCache _logCache`
- L270-285 _public ctor_ `public LogCollection(IMongoService mongoService, LogTailService logTailService, StorageService storageService, Tracer tracer, ILogger<LogCollection> logger)` — Constructor
- L288-291 _public method_ `public void Dispose()` — (inheritdoc)
- L294-299 _public method_ `public async Task<ILog> AddAsync(JobId jobId, LeaseId? leaseId, SessionId? sessionId, LogType type, LogId? logId, AclScopeName aclScopeName, CancellationToken cancellationToken)` — (inheritdoc)
- L302-313 _private* method_ `async Task DeleteAsync(LogDocument logDocument, CancellationToken cancellationToken)` — (inheritdoc)
- L316-324 _public method_ `public async Task<ILog?> GetAsync(LogId logId, CancellationToken cancellationToken)` — (inheritdoc)
- L327-368 _private* method_ `async Task<List<Utf8String>> ReadLinesAsync(LogDocument log, int index, int count, CancellationToken cancellationToken)` — (inheritdoc)
- L371-383 _private* method_ `async Task<LogMetadata> GetMetadataAsync(LogDocument log, CancellationToken cancellationToken)` — (inheritdoc)
- L385-390 _private* method_ `async Task<LogDocument> UpdateLineCountAsync(LogDocument log, int lineCount, bool complete, CancellationToken cancellationToken)`
- L393-420 _private* method_ `async Task<(int, long)> GetLineOffsetAsync(LogDocument log, int lineIdx, CancellationToken cancellationToken)` — attrs: `[SuppressMessage("CodeQuality", "IDE0051:Remove unused private members")]`
- L423-452 _private* method_ `async Task<Stream> OpenRawStreamAsync(LogDocument log, long offset, long length, CancellationToken cancellationToken)` — (inheritdoc)
- L455-478 _private* method_ `async Task<List<int>> SearchLogDataAsync(LogDocument log, string text, int firstLine, int count, SearchStats searchStats, CancellationToken cancellationToken)` — (inheritdoc)
- L480-526 _private* method_ `async IAsyncEnumerable<int> SearchLogDataInternalNewAsync(LogDocument log, string text, int firstLine, SearchStats searchStats, [EnumeratorCancellation] CancellationToken cancellationToken)`
- L528-568 _private* method_ `async Task<Utf8String[]> ReadTailAsync(LogDocument log, int index, CancellationToken cancellationToken)`
- L571-633 _private* method_ `async Task CopyPlainTextStreamAsync(ILog log, Stream outputStream, CancellationToken cancellationToken)` — (inheritdoc)
- L638-650 _public method_ `public static int GuardedConvertToPlainText(ReadOnlySpan<byte> input, byte[] output, int outputOffset, ILogger logger)` — Helper method for catching exceptions in ConvertToPlainText(ReadOnlySpan{Byte}, Byte[], Int32)
- L659-693 _public method_ `public static int ConvertToPlainText(ReadOnlySpan<byte> input, byte[] output, int outputOffset)` — Converts a JSON log line to plain text
- L700-711 _private* method_ `static bool IsEmptyOrWhitespace(ReadOnlySpan<byte> input)` — Determines if the given line is empty
- L719-768 _private* method_ `static int UnescapeUtf8(ReadOnlySpan<byte> source, Span<byte> target)` — Unescape a json utf8 string
- L773-776 _private* method_ `Task AddEventsAsync(LogId logId, List<NewLogEventData> newEvents, CancellationToken cancellationToken)` — (inheritdoc)
- L779-803 _private* method_ `async Task<List<ILogAnchor>> GetAnchorsAsync(ILog log, ObjectId? spanId = null, int? index = null, int? count = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L806-827 _public method_ `public async Task<IReadOnlyList<ILogAnchor>> FindAnchorsForSpansAsync(IEnumerable<ObjectId> spanIds, LogId[]? logIds, int index, int count, CancellationToken cancellationToken)` — (inheritdoc)
- L830-835 _public method_ `public async Task AddSpanToEventsAsync(IEnumerable<ILogAnchor> events, ObjectId spanId, CancellationToken cancellationToken)` — (inheritdoc)
- L860-883 _private* method_ `async Task<LogEventData> GetEventDataAsync(ILog log, int lineIndex, int lineCount, CancellationToken cancellationToken)`

#### class `HordeServer.Logs.LogCollection.Log`  
`class Log : ILog`  
_private*; L32-84_
- inherits: `ILog`
- L34 _private* field_ `readonly LogCollection _collection`
- L35 _private* field_ `readonly LogDocument _document`
- L37 _private* property_ `LogId ILog.Id => ...`
- L38 _private* property_ `JobId ILog.JobId => ...`
- L39 _private* property_ `LeaseId? ILog.LeaseId => ...`
- L40 _private* property_ `SessionId? ILog.SessionId => ...`
- L41 _private* property_ `LogType ILog.Type => ...`
- L42 _private* property_ `NamespaceId ILog.NamespaceId => ...`
- L43 _private* property_ `RefName ILog.RefName => ...`
- L44 _private* property_ `AclScopeName ILog.AclScopeName => ...`
- L46-50 _public ctor_ `public Log(LogCollection collection, LogDocument document)`
- L52 _public method_ `public Task DeleteAsync(CancellationToken cancellationToken = default)`
- L55-59 _public method_ `public async Task<ILog> UpdateLineCountAsync(int lineCount, bool complete, CancellationToken cancellationToken = default)`
- L61 _public method_ `public Task<List<Utf8String>> ReadLinesAsync(int index, int count, CancellationToken cancellationToken = default)`
- L64 _public method_ `public Task<LogMetadata> GetMetadataAsync(CancellationToken cancellationToken)`
- L67 _public method_ `public Task<Stream> OpenRawStreamAsync(CancellationToken cancellationToken = default)`
- L70 _public method_ `public Task<Stream> OpenRawStreamAsync(long offset, long length, CancellationToken cancellationToken)`
- L73 _public method_ `public Task CopyPlainTextStreamAsync(Stream outputStream, CancellationToken cancellationToken = default)`
- L76 _public method_ `public Task<List<int>> SearchLogDataAsync(string text, int firstLine, int count, SearchStats stats, CancellationToken cancellationToken)`
- L79 _public method_ `public Task AddEventsAsync(List<NewLogEventData> newEvents, CancellationToken cancellationToken = default)`
- L82 _public method_ `public Task<List<ILogAnchor>> GetAnchorsAsync(ObjectId? spanId = null, int? index = null, int? count = null, CancellationToken cancellationToken = default)`

#### class `HordeServer.Logs.LogCollection.LogDocument`  
`class LogDocument`  
_private*; L86-141_
- L89 _public property_ `public LogId Id { get; set; }` — attrs: `[BsonRequired, BsonId]`
- L92 _public property_ `public JobId JobId { get; set; }` — attrs: `[BsonRequired]`
- L95 _public property_ `public LeaseId? LeaseId { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L98 _public property_ `public SessionId? SessionId { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L100 _public property_ `public LogType Type { get; set; }`
- L101 _public property_ `public bool UseNewStorageBackend { get; set; }`
- L104 _public property_ `public int? MaxLineIndex { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L107 _public property_ `public long? IndexLength { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L109 _public property_ `public List<LogChunkDocument> Chunks { get; set; }`
- L111 _public property_ `public int LineCount { get; set; }`
- L113 _public property_ `public NamespaceId NamespaceId { get; set; }`
- L114 _public property_ `public RefName RefName { get; set; }`
- L115 _public property_ `public AclScopeName AclScopeName { get; set; }`
- L118 _public property_ `public bool Complete { get; set; }` — attrs: `[BsonIgnoreIfDefault]`
- L121 _public property_ `public int UpdateIndex { get; set; }` — attrs: `[BsonRequired]`
- L124-126 _private ctor_ `private LogDocument()` — attrs: `[BsonConstructor]`
- L128-140 _public ctor_ `public LogDocument(JobId jobId, LeaseId? leaseId, SessionId? sessionId, LogType type, LogId? logId, NamespaceId namespaceId, AclScopeName aclScopeName)`

#### class `HordeServer.Logs.LogCollection.LogChunkDocument`  
`class LogChunkDocument`  
_private*; L143-169_
- L145 _public property_ `public long Offset { get; set; }`
- L146 _public property_ `public int Length { get; set; }`
- L147 _public property_ `public int LineIndex { get; set; }`
- L150 _public property_ `public string? Server { get; set; }` — attrs: `[BsonIgnoreIfNull]`
- L153-155 _public ctor_ `public LogChunkDocument()` — attrs: `[BsonConstructor]`
- L157-163 _public ctor_ `public LogChunkDocument(LogChunkDocument other)`
- L165-168 _public method_ `public LogChunkDocument Clone()`

#### class `HordeServer.Logs.LogCollection.LogAnchor`  
`class LogAnchor : ILogAnchor`  
_private*; L171-194_
- inherits: `ILogAnchor`
- L173 _private* field_ `readonly ILog _log`
- L174 _private* field_ `readonly LogCollection _collection`
- L175 _private* field_ `readonly LogAnchorDocument _document`
- L177 _public property_ `public LogAnchorDocument Document => ...`
- L179 _private* property_ `LogId ILogAnchor.LogId => ...`
- L180 _private* property_ `LogEventSeverity ILogAnchor.Severity => ...`
- L181 _private* property_ `int ILogAnchor.LineIndex => ...`
- L182 _private* property_ `int ILogAnchor.LineCount => ...`
- L183 _private* property_ `ObjectId? ILogAnchor.SpanId => ...`
- L185-190 _public ctor_ `public LogAnchor(ILog log, LogCollection collection, LogAnchorDocument document)`
- L192 _public method_ `public async Task<ILogEventData> GetDataAsync(CancellationToken cancellationToken = default)`

#### class `HordeServer.Logs.LogCollection.LogAnchorId`  
`class LogAnchorId`  
_private*; L196-203_
- L199 _public property_ `public LogId LogId { get; set; }` — attrs: `[BsonElement("l")]`
- L202 _public property_ `public int LineIndex { get; set; }` — attrs: `[BsonElement("n")]`

#### class `HordeServer.Logs.LogCollection.LogAnchorDocument`  
`class LogAnchorDocument`  
_private*; L205-237_
- L208 _public property_ `public LogAnchorId Id { get; set; }` — attrs: `[BsonId]`
- L211 _public property_ `public bool IsWarning { get; set; }` — attrs: `[BsonElement("w"), BsonIgnoreIfDefault, BsonDefaultValue(false)]`
- L214 _public property_ `public int? LineCount { get; set; }` — attrs: `[BsonElement("c"), BsonIgnoreIfNull]`
- L217 _public property_ `public ObjectId? SpanId { get; set; }` — attrs: `[BsonElement("s")]`
- L220-223 _public ctor_ `public LogAnchorDocument()` — attrs: `[BsonConstructor]`
- L225-231 _public ctor_ `public LogAnchorDocument(LogId logId, LogEventSeverity severity, int lineIndex, int lineCount, ObjectId? spanId)`
- L233-236 _public ctor_ `public LogAnchorDocument(LogId logId, NewLogEventData data) : this(logId, data.Severity, data.LineIndex, data.LineCount, data.SpanId)`

#### class `HordeServer.Logs.LogCollection.LegacyLogEventDocument`  
`class LegacyLogEventDocument`  
_private*; L239-256_
- L241 _public property_ `public ObjectId Id { get; set; }`
- L242 _public property_ `public DateTime Time { get; set; }`
- L243 _public property_ `public LogEventSeverity Severity { get; set; }`
- L244 _public property_ `public LogId LogId { get; set; }`
- L245 _public property_ `public int LineIndex { get; set; }`
- L246 _public property_ `public int LineCount { get; set; }`
- L248 _public property_ `public string? Message { get; set; }`
- L251 _public property_ `public int? IssueId { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("IssueId2")]`
- L253 _public property_ `public BsonDocument? Data { get; set; }`
- L255 _public property_ `public int UpgradeVersion { get; set; }`

#### class `HordeServer.Logs.LogCollection.LogEventData`  
`class LogEventData : ILogEventData`  
_private*; L837-858_
- inherits: `ILogEventData`
- L839 _public field_ `public string? _message`
- L840 _public property_ `public IReadOnlyList<JsonLogEvent> Lines { get; }`
- L842 _private* property_ `EventId? ILogEventData.EventId => ...`
- L843 _private* property_ `LogEventSeverity ILogEventData.Severity => ...`
- L845-848 _public ctor_ `public LogEventData(IReadOnlyList<JsonLogEvent> lines)`
- L850-857 _private* property_ `string ILogEventData.Message { get; }`

#### class `HordeServer.Logs.LogCollection.ResponseStream`  
`class ResponseStream : Stream`  
_private*; L890-1032_
- inherits: `Stream`
- desc: Streams log data to a caller
- L892 _private* field_ `readonly LogNode _rootNode`
- L897 _private* field_ `readonly long _responseOffset` — Starting offset within the file of the data to return
- L902 _private* field_ `readonly long _responseLength` — Length of data to return
- L907 _private* field_ `long _currentOffset` — Current offset within the stream
- L912 _private* field_ `int _chunkIdx` — The current chunk index
- L917 _private* field_ `ReadOnlyMemory<byte> _sourceBuffer` — Buffer containing a message for missing data
- L922 _private* field_ `int _sourcePos` — Offset within the source buffer
- L927 _private* field_ `int _sourceEnd` — Length of the source buffer being copied from
- L932-943 _public ctor_ `public ResponseStream(LogNode rootNode, long offset, long length)` — Constructor
- L946 _public property_ `public override bool CanRead => ...` — (inheritdoc)
- L949 _public property_ `public override bool CanSeek => ...` — (inheritdoc)
- L952 _public property_ `public override bool CanWrite => ...` — (inheritdoc)
- L955 _public property_ `public override long Length => ...` — (inheritdoc)
- L958-962 _public property_ `public override long Position { get; set; }` — (inheritdoc)
- L965-967 _public method_ `public override void Flush()` — (inheritdoc)
- L970-975 _public method_ `public override int Read(byte[] buffer, int offset, int count)` — (inheritdoc)
- L978-981 _public method_ `public override async Task<int> ReadAsync(byte[] buffer, int offset, int length, CancellationToken cancellationToken)` — (inheritdoc)
- L984-1022 _public method_ `public override async ValueTask<int> ReadAsync(Memory<byte> buffer, CancellationToken cancellationToken)` — (inheritdoc)
- L1025 _public method_ `public override long Seek(long offset, SeekOrigin origin)` — (inheritdoc)
- L1028 _public method_ `public override void SetLength(long value)` — (inheritdoc)
- L1031 _public method_ `public override void Write(byte[] buffer, int offset, int count)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Logs/LogIdUtils.cs` (HordeServer.Compute)


#### class `HordeServer.Logs.LogIdUtils`  
`public static class LogIdUtils`  
_public; L11-17_
- desc: Server helper methods for LogId
- L16 _public method_ `public static LogId GenerateNewId()` — Creates a new LogId

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Logs/LogRpcService.cs` (HordeServer.Compute)


#### class `HordeServer.Logs.LogRpcService`  
`public class LogRpcService : LogRpc.LogRpcBase`  
_public; L21-196_
- attrs: `[Authorize]`
- inherits: `LogRpc.LogRpcBase`
- desc: Implements the Horde gRPC service for bots updating their status and dequeing work
- L26 _private* const_ `const string RequestCompleteMessage = "Request is complete"`
- L27 _private* const_ `const string WritingNotAllowedMessage = "Writing is not allowed"`
- L29 _private* field_ `readonly ILogCollection _logCollection`
- L30 _private* field_ `readonly LogTailService _logTailService`
- L31 _private* field_ `readonly StorageService _storageService`
- L32 _private* field_ `readonly IOptionsSnapshot<ComputeConfig> _computeConfig`
- L33 _private* field_ `readonly ILogger<LogRpcService> _logger`
- L38-45 _public ctor_ `public LogRpcService(ILogCollection logCollection, LogTailService logTailService, StorageService storageService, IOptionsSnapshot<ComputeConfig> computeConfig, ILogger<LogRpcService> logger)` — Constructor
- L48-78 _public method_ `public override async Task<RpcUpdateLogResponse> UpdateLog(RpcUpdateLogRequest request, ServerCallContext context)` — (inheritdoc)
- L81-141 _public method_ `public override async Task UpdateLogTail(IAsyncStreamReader<RpcUpdateLogTailRequest> requestStream, IServerStreamWriter<RpcUpdateLogTailResponse> responseStream, ServerCallContext context)` — (inheritdoc)
- L146-163 _private* method_ `static async Task<bool> TryWriteResponseAsync(IServerStreamWriter<RpcUpdateLogTailResponse> responseStream, RpcUpdateLogTailResponse response)` — Attempts to write a response to the stream, returning false if the stream is already closed
- L166-195 _public method_ `public override async Task<Empty> CreateLogEvents(RpcCreateLogEventsRequest request, ServerCallContext context)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Logs/LogTailService.cs` (HordeServer.Compute)


#### class `HordeServer.Logs.LogTailService`  
`public class LogTailService : IHostedService`  
_public; L32-432_
- inherits: `IHostedService`
- desc: Stores data for logs which has not yet been flushed to persistent storage. * Once a log is retrieved, server adds an entry with this log id to a sorted set in Redis (see s_expireQueue, scored by expiry time (defaulting to ExpireAfter from present) and broadcasts it to any other server instances. * If a log is being tailed, server keeps the total number of lines in a Redis key (TailNextKey, and appends chunks of log data to a sorted set for that log scored by index of the first line (see TailDataKey). * Chunks are split on fixed boundaries, in order to allow older entries to be purged by score without having to count the number of lines they contain first. * Agent polls for requests to provide tail data via LogRpcService.UpdateLogTail, which calls WaitForTailNextAsync. WaitForTailNextAsync returns the index of the total line count for this log if it is being tailed (indicating the index of the next line that the agent should send to the server), or blocks until the log is being tailed. 
- L37 _public property_ `public static TimeSpan TrimAfter { get; }` — Amount of time to keep tail data in the cache after it has been flushed to persistent storage. This gives some wiggle room with order of operations when sequencing persisted data with tail data.
- L42 _public property_ `public static TimeSpan ExpireAfter { get; }` — Amount of time to continue tailing a log after the last time it was updated.
- L44 _private* field_ `readonly IRedisService _redisService`
- L46 _private* field_ `readonly ConcurrentDictionary<LogId, AsyncEvent> _notifyLogEvents = ...`
- L46 _private* field_ `readonly ConcurrentDictionary< _notifyLogEvents = new ConcurrentDictionary<LogId, AsyncEvent>()`
- L47 _private* field_ `readonly RedisChannel<LogId> _tailStartChannel`
- L48 _private* field_ `static readonly RedisSortedSetKey<string> s_trimQueue = "logs:trim"`
- L49 _private* field_ `static readonly RedisSortedSetKey<LogId> s_expireQueue = "logs:expire"`
- L51 _private* field_ `readonly IClock _clock`
- L52 _private* field_ `readonly ITicker _expireTailsTicker`
- L54 _private* field_ `readonly ILogger _logger`
- L55 _private* field_ `readonly IServerInfo _serverInfo`
- L57 _private* field_ `IAsyncDisposable? _tailStartSubscription`
- L59 _internal method_ `internal static RedisStringKey<int> TailNextKey(LogId logId)`
- L60 _internal method_ `internal static RedisSortedSetKey<ReadOnlyMemory<byte>> TailDataKey(LogId logId)`
- L65 _public property_ `public int ChunkLineCount { get; }` — Boundary to split Redis chunks along.
- L70-73 _public ctor_ `public LogTailService(IRedisService redisService, IClock clock, IServerInfo serverInfo, ILogger<LogTailService> logger) : this(redisService, clock, 32, serverInfo, logger)` — Constructor
- L78-94 _public ctor_ `public LogTailService(IRedisService redisService, IClock clock, int chunkLineCount, IServerInfo serverInfo, ILogger<LogTailService> logger)` — Constructor
- L97-104 _public method_ `public async Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L107-117 _public method_ `public async Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L119-161 _private method_ `private async ValueTask ExpireTailsAsync(CancellationToken cancellationToken)`
- L163-170 _private method_ `private void OnTailStart(LogId logId)`
- L178-212 _public method_ `public async ValueTask EnableTailingAsync(LogId logId, int lineCount, CancellationToken cancellationToken = default)` — Enable tailing for the given log file
- L221-240 _public method_ `public async Task AppendAsync(LogId logId, int tailNext, ReadOnlyMemory<byte> tailData)` — Appends data to the log tail, starting at the given line index
- L249-254 _public method_ `public async Task<List<Utf8String>> ReadAsync(LogId logId, int lineIndex, int lineCount)` — Reads data for the given log file, starting at the requested line index
- L264-298 _public method_ `public async Task ReadAsync(LogId logId, int lineIndex, int lineCount, List<Utf8String> lines)` — Reads data for the given log file, starting at the requested line index
- L306-315 _public method_ `public async ValueTask FlushAsync(LogId logId, int lineCount)` — Flushes the given log file to the given number of lines
- L324-335 _public method_ `public async Task<int> GetFullLineCountAsync(LogId logId, int flushedLineCount, CancellationToken cancellationToken)` — Gets the total number of lines in a log
- L343-348 _public method_ `public async Task<int> GetTailNextAsync(LogId logId, CancellationToken cancellationToken)` — Gets the next requested tail line number, returning immediately if it is set
- L356-386 _public method_ `public async Task<int> WaitForTailNextAsync(LogId logId, CancellationToken cancellationToken)` — Waits for a request to read tail data
- L391-431 _private* method_ `static int SplitLogDataToChunks(int lineIdx, ReadOnlyMemory<byte> data, int chunkLineCount, List<SortedSetEntry<ReadOnlyMemory<byte>>> entries)` — Splits data into chunks aligned onto ChunkLineCount line boundaries.

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Logs/LogsController.cs` (HordeServer.Compute)


#### enum `HordeServer.Logs.LogOutputFormat`  
`public enum LogOutputFormat`  
_public; L25-36_
- desc: Format for the returned data
- L30 _public* enumerator_ `Text` — Plain text
- L35 _public* enumerator_ `Raw` — Raw output (text/json)

#### class `HordeServer.Logs.LogsController`  
`public class LogsController : ControllerBase`  
_public; L44-524_
- attrs: `[ApiController] [Authorize] [Route("[controller]")]`
- inherits: `ControllerBase`
- desc: Controller for the /api/logs endpoint
- L46 _private field_ `private readonly ILogCollection _logCollection`
- L47 _private field_ `private readonly StorageService _storageService`
- L48 _private field_ `private readonly IEnumerable<ILogExtAuthProvider> _authProviders`
- L49 _private field_ `private readonly IEnumerable<ILogExtIssueProvider> _issueProviders`
- L50 _private field_ `private readonly IOptionsSnapshot<ComputeConfig> _computeConfig`
- L51 _private field_ `private readonly ILogger _logger`
- L56-64 _public ctor_ `public LogsController(ILogCollection logCollection, StorageService storageService, IEnumerable<ILogExtAuthProvider> authProviders, IEnumerable<ILogExtIssueProvider> issueProviders, IOptionsSnapshot<ComputeConfig> computeConfig, ILogger<LogsController> logger)` — Constructor
- L76-90 _public method_ `public async Task<ActionResult<object>> GetLogAsync(LogId logId, [FromQuery] PropertyFilter? filter = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/logs/{logId}")] [ProducesResponseType(typeof(GetLogResponse), 200)]` — Retrieve metadata about a specific log file
- L92-102 _private* method_ `static GetLogResponse CreateGetLogResponse(ILog log, LogMetadata metadata)`
- L114-134 _public method_ `public async Task<ActionResult<WriteBlobResponse>> WriteLogBlobAsync(LogId logId, WriteBlobRequest request, CancellationToken cancellationToken = default)` — attrs: `[HttpPost] [Route("/api/v1/logs/{logId}/blobs")] [ProducesResponseType(typeof(WriteBlobResponse), 200)]` — Uploads a blob for a log file. See /api/v1/storage/XXX/blobs.
- L147-165 _public method_ `public async Task<ActionResult<WriteBlobResponse>> WriteLogBlobAsync(LogId logId, BlobLocator locator, WriteBlobRequest request, CancellationToken cancellationToken = default)` — attrs: `[HttpPut] [Route("/api/v1/logs/{logId}/blobs/{*locator}")] [ProducesResponseType(typeof(WriteBlobResponse), 200)]` — Uploads a blob for a log file. See /api/v1/storage/XXX/blobs.
- L178-206 _public method_ `public async Task<ActionResult> GetLogDataAsync( LogId logId, [FromQuery] LogOutputFormat format = LogOutputFormat.Raw, [FromQuery] string? fileName = null, [FromQuery] bool download = false, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/logs/{logId}/data")]` — Retrieve raw data for a log file
- L218-295 _public method_ `public async Task<ActionResult> GetLogLinesAsync(LogId logId, [FromQuery] int index = 0, [FromQuery] int count = 100, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/logs/{logId}/lines")]` — Retrieve line data for a log
- L308-329 _public method_ `public async Task<ActionResult<SearchLogResponse>> SearchLogAsync( LogId logId, [FromQuery] string text, [FromQuery] int firstLine = 0, [FromQuery] int count = 5, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/logs/{logId}/search")]` — Search log data
- L342-385 _public method_ `public async Task<ActionResult<List<GetLogEventResponse>>> GetEventsAsync(LogId logId, [FromQuery] int? index = null, [FromQuery] int? count = null, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/logs/{logId}/events")] [ProducesResponseType(typeof(List<GetLogEventResponse>), 200)]` — Retrieve events for a log
- L396-464 _public method_ `public async Task<ActionResult<GetBatchLogEventsResponse>> GetBatchEventsAsync([FromBody] GetBatchLogEventsRequest request, CancellationToken cancellationToken = default)` — attrs: `[HttpPost] [Route("/api/v1/logs/events")] [ProducesResponseType(typeof(GetBatchLogEventsResponse), 200)]` — Retrieve events for multiple logs in a single request
- L472-482 _public method_ `public static GetLogEventResponse CreateGetLogEventResponse(ILogAnchor anchor, ILogEventData eventData, int? issueId)` — Create a log event response message
- L492-523 _private* method_ `async Task<bool> AuthorizeAsync(ILog log, AclAction action, ClaimsPrincipal user, CancellationToken cancellationToken)` — Determines if the user is authorized to perform an action on a particular template

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Properties/AssemblyInfo.cs` (HordeServer.Compute)
_(no declarations)_


### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Protos/horde/messages/agent_capabilities.proto.cs` (HordeServer.Compute)


#### class `HordeCommon.Rpc.Messages.RpcAgentCapabilities`  
`partial class RpcAgentCapabilities`  
_internal*; L9-61_
- L11-14 _public ctor_ `public RpcAgentCapabilities(IEnumerable<string> properties)`
- L16-42 _public method_ `public RpcAgentCapabilities MergeDevices()`
- L44-60 _private* method_ `void CopyPropertyToResource(string name)`

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Protos/horde/messages/lease.proto.cs` (HordeServer.Compute)


#### class `HordeCommon.Rpc.Messages.RpcLease`  
`partial class RpcLease`  
_internal*; L10-47_
- desc: Additional methods for RpcLease
- L15-19 _public property_ `public LeaseId Id { get; set; }` — Typed accessor for the RpcLease.IdString field.
- L24-29 _public method_ `public LeaseOutcomeReason ToNativeOutcomeReason()` — Convert outcome reason(s) from Protobuf-format to C# enum
- L34-46 _public method_ `public static List<RpcLeaseOutcomeReason> ToProtobufOutcomeReasons(LeaseOutcomeReason reasons)` — Convert C# enum with outcome reason(s) to Protobuf-format

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Protos/horde/messages/session.proto.cs` (HordeServer.Compute)


#### class `HordeCommon.Rpc.Messages.RpcSession`  
`partial class RpcSession`  
_internal*; L13-37_
- L15 _public property_ `public static TimeSpan ExpireAfterTime { get; }`
- L17-21 _public property_ `public AgentId AgentId { get; set; }`
- L23-27 _public property_ `public SessionId SessionId { get; set; }`
- L29-33 _public property_ `public IoHash CapabilitiesHash { get; set; }`
- L35 _public property_ `public DateTime ExpiryTime => ...`

#### class `HordeCommon.Rpc.Messages.RpcSessionLease`  
`partial class RpcSessionLease : IAgentLease`  
_internal*; L39-56_
- inherits: `IAgentLease`
- L41-45 _public property_ `public LeaseId Id { get; set; }`
- L47-51 _public property_ `public LeaseId? ParentId { get; set; }`
- L53 _private* property_ `IReadOnlyDictionary<string, int>? IAgentLease.Resources => ...`
- L55 _private* property_ `LeaseState IAgentLease.State => ...`

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Protos/horde/tasks/job_task.cs` (HordeServer.Compute)


#### class `HordeCommon.Rpc.Tasks.RpcJobOptions`  
`partial class RpcJobOptions`  
_internal*; L5-7_

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Server/RpcService.cs` (HordeServer.Compute)


#### class `HordeServer.Server.RpcService`  
`public class RpcService : HordeRpc.HordeRpcBase`  
_public; L33-503_
- attrs: `[Authorize]`
- inherits: `HordeRpc.HordeRpcBase`
- desc: Implements the Horde gRPC service for bots updating their status and dequeing work
- L39 _internal const_ `internal const int MaxDetailedConflictErrors = 20` — Number of session mismatches per agent that generate detailed (Error-level) structured exceptions. Beyond this threshold, mismatches are logged at Debug level to suppress spam.
- L44 _internal field_ `internal TimeSpan _longPollTimeout = TimeSpan.FromMinutes(9)` — Timeout before closing a long-polling request (client will retry again)
- L46 _private* field_ `readonly AgentService _agentService`
- L47 _private* field_ `readonly ILifetimeService _lifetimeService`
- L48 _private* field_ `readonly IToolCollection _toolCollection`
- L49 _private* field_ `readonly IAgentTelemetryCollection _agentTelemetryCollection`
- L50 _private* field_ `readonly IAclService _aclService`
- L51 _private* field_ `readonly IOptionsSnapshot<ComputeConfig> _computeConfig`
- L52 _private* field_ `readonly SessionConflictService _sessionConflictService`
- L53 _private* field_ `readonly ILogger _logger`
- L54 _private* field_ `readonly ITelemetryWriter _telemetryWriter`
- L59-79 _public ctor_ `public RpcService( AgentService agentService, ILifetimeService lifetimeService, IToolCollection toolCollection, IAgentTelemetryCollection agentTelemetryCollection, IAclService aclService, IOptionsSnapshot<ComputeConfig> computeConfig, SessionConflictService sessionConflictService, ILogger<RpcService> logger, ITelemetryWriter telemetryWriter)` — Constructor
- L89-123 _public method_ `public override async Task QueryServerState(IAsyncStreamReader<RpcQueryServerStateRequest> reader, IServerStreamWriter<RpcQueryServerStateResponse> writer, ServerCallContext context)` — attrs: `[Obsolete("RPC connection management now done natively")]` — Waits until the server is terminating
- L133-170 _public method_ `public override async Task QueryServerStateV2(IAsyncStreamReader<RpcQueryServerStateRequest> reader, IServerStreamWriter<RpcQueryServerStateResponse> writer, ServerCallContext context)` — attrs: `[Obsolete("RPC connection management now done natively")]` — Waits until the server is terminating
- L179-207 _public method_ `public override async Task<RpcCreateAgentResponse> CreateAgent(RpcCreateAgentRequest request, ServerCallContext context)` — Creates a new agent The enrollment process is bypassed for all agent types created through this endpoint.
- L209-215 _private method_ `private void EnsurePermission(AclAction action, string errorMessage, ServerCallContext context)`
- L223-280 _public method_ `public override async Task<RpcCreateSessionResponse> CreateSession(RpcCreateSessionRequest request, ServerCallContext context)` — Creates a new session
- L289-401 _public method_ `public override async Task UpdateSession(IAsyncStreamReader<RpcUpdateSessionRequest> reader, IServerStreamWriter<RpcUpdateSessionResponse> writer, ServerCallContext context)` — Updates an agent session
- L410-458 _public method_ `public override async Task DownloadSoftware(RpcDownloadSoftwareRequest request, IServerStreamWriter<RpcDownloadSoftwareResponse> responseStream, ServerCallContext context)` — Downloads a new agent archive
- L461-492 _public method_ `public override Task<Empty> UploadTelemetry(RpcUploadTelemetryRequest request, ServerCallContext context)` — (inheritdoc)
- L494-502 _private method_ `private static bool IsCancellationException(Exception ex)`

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Tasks/ITaskSource.cs` (HordeServer.Compute)


#### enum `HordeServer.Tasks.TaskSourceFlags`  
`public enum TaskSourceFlags`  
_public; L23-44_
- attrs: `[Flags]`
- desc: Flags indicating when a task source is valid
- L28 _public* enumerator_ `None = 0` — Normal behavior
- L33 _public* enumerator_ `AllowDuringDowntime = 1` — Indicates that tasks from this source can run during downtime
- L38 _public* enumerator_ `AllowWhenDisabled = 2` — Allows this source to schedule tasks when the agent is disabled
- L43 _public* enumerator_ `AllowWhenBusy = 4` — Allows this source to schedule tasks when the agent is busy executing external work

#### interface `HordeServer.Tasks.ITaskSource`  
`public interface ITaskSource`  
_public; L49-122_
- desc: Handler for a certain lease type
- L54 _public* property_ `string Type { get; }` — The task type
- L59 _public* property_ `MessageDescriptor Descriptor { get; }` — Descriptor for this lease type
- L64 _public* property_ `TaskSourceFlags Flags { get; }` — Flags controlling behavior of this source
- L82 _public* method_ `Task<Task<CreateLeaseOptions?>> AssignLeaseAsync(IAgent agent, CancellationToken cancellationToken)` — Assigns a lease or waits for one to be available. This method returns a wrapped task object. Issuing of tasks is done in two phases; all task sources are queried sequentially for a lease with immediate availability, and if one isn't found we wait for leases to become available in parallel. Task sources are specificially ordered to allow one to take precedence over another. Performing the lease allocation in two steps allows for the following patterns: - A lease cannot be assigned immediately (due to dependencies on some limited external resource, or due to other leases already running on an agent), but we should not assign any other leases to the agent either. In this situation, the method can just block immediately until the lease criteria are satisfied. - The determination of a lease's availability requires some async setup, which can be done before the secondary task returns.
- L91 _public* method_ `Task CancelLeaseAsync(IAgent agent, LeaseId leaseId, Any payload, CancellationToken cancellationToken)` — Cancel a lease that was previously assigned to an agent, allowing it to be assigned out again
- L101 _public* method_ `Task OnLeaseStartedAsync(IAgent agent, LeaseId leaseId, Any payload, ILogger logger, CancellationToken cancellationToken)` — Notification that a lease has been started
- L113 _public* method_ `Task OnLeaseFinishedAsync(IAgent agent, LeaseId leaseId, Any payload, LeaseOutcome outcome, ReadOnlyMemory<byte> output, ILogger logger, CancellationToken cancellationToken)` — Notification that a task has completed
- L121 _public* method_ `ValueTask GetLeaseDetailsAsync(Any payload, Dictionary<string, string> details, CancellationToken cancellationToken)` — Gets information to include for a lease in a lease info response

#### class `HordeServer.Tasks.TaskSourceBase`  
`public abstract class TaskSourceBase<TMessage> : ITaskSource where TMessage : IMessage, new()`  
_public; L128-264_
- inherits: `ITaskSource`
- constraints: `where TMessage : IMessage, new()`
- desc: Base implementation of ITaskSource
- L164 _private* field_ `static readonly TMessage s_message = new TMessage()`
- L167 _public property_ `public abstract string Type { get; }` — (inheritdoc)
- L170 _public property_ `public abstract TaskSourceFlags Flags { get; }` — (inheritdoc)
- L173 _protected property_ `protected virtual PropertyList OnLeaseStartedProperties { get; }` — (inheritdoc)
- L176 _public property_ `public MessageDescriptor Descriptor => ...` — (inheritdoc)
- L179 _public method_ `public abstract Task<Task<CreateLeaseOptions?>> AssignLeaseAsync(IAgent agent, CancellationToken cancellationToken)` — (inheritdoc)
- L182 _public method_ `public Task CancelLeaseAsync(IAgent agent, LeaseId leaseId, Any payload, CancellationToken cancellationToken)` — (inheritdoc)
- L185 _public method_ `public Task OnLeaseStartedAsync(IAgent agent, LeaseId leaseId, Any payload, ILogger logger, CancellationToken cancellationToken)` — (inheritdoc)
- L188 _public method_ `public Task OnLeaseFinishedAsync(IAgent agent, LeaseId leaseId, Any payload, LeaseOutcome outcome, ReadOnlyMemory<byte> output, ILogger logger, CancellationToken cancellationToken)` — (inheritdoc)
- L191 _public method_ `public virtual Task CancelLeaseAsync(IAgent agent, LeaseId leaseId, TMessage payload, CancellationToken cancellationToken)` — (inheritdoc)
- L194-207 _public method_ `public virtual Task OnLeaseStartedAsync(IAgent agent, LeaseId leaseId, TMessage payload, ILogger logger, CancellationToken cancellationToken)` — (inheritdoc)
- L210-214 _public method_ `public virtual Task OnLeaseFinishedAsync(IAgent agent, LeaseId leaseId, TMessage payload, LeaseOutcome outcome, ReadOnlyMemory<byte> output, ILogger logger, CancellationToken cancellationToken)` — (inheritdoc)
- L217-231 _public method_ `public virtual ValueTask GetLeaseDetailsAsync(Any payload, Dictionary<string, string> details, CancellationToken cancellationToken)` — (inheritdoc)
- L238-242 _protected method_ `protected static Task<CreateLeaseOptions?> SkipAsync(CancellationToken token)` — Creates a lease task which will wait until the given cancellation token is signalled.
- L249-253 _protected method_ `protected static async Task<Task<CreateLeaseOptions?>> DrainAsync(CancellationToken token)` — Waits until the cancellation token is signalled, then return an cancelled lease task.
- L260-263 _protected method_ `protected static Task<CreateLeaseOptions?> LeaseAsync(CreateLeaseOptions lease)` — Creates a lease task from a given lease

#### class `HordeServer.Tasks.TaskSourceBase.PropertyList`  
`protected class PropertyList`  
_protected; L133-162_
- desc: List of properties that can be output as log messages
- L135 _internal field_ `internal StringBuilder _formatString = new StringBuilder()`
- L136 _internal field_ `internal List<Func<TMessage, object>> _accessors = ...`
- L136 _internal field_ `internal List<Func< _accessors = new List<Func<TMessage, object>>()`
- L137 _internal field_ `internal List<(string, Func<TMessage, object>)> _jsonAccessors = new List<(string, Func<TMessage, object>)>()`
- L143-147 _public method_ `public PropertyList Add(Expression<Func<TMessage, object>> expr)` — Adds a new property to the list
- L155-161 _public method_ `public PropertyList Add(string name, Func<TMessage, object> accessor)` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Globalization", "CA1308:Normalize strings to uppercase", Justification = "<Pending>")]` — Adds a new property to the list

#### class `HordeServer.Tasks.TaskSourceNotificationService`  
`class TaskSourceNotificationService : IHostedService, IAsyncDisposable`  
_internal*; L269-329_
- inherits: `IHostedService, IAsyncDisposable`
- desc: Service which dispatches lease complete notifications to task sources
- L271 _private* field_ `readonly IAgentCollection _agentCollection`
- L272 _private* field_ `readonly LeaseCollection _leaseCollection`
- L273 _private* field_ `readonly ITaskSource[] _taskSources`
- L274 _private* field_ `readonly AsyncQueue _asyncQueue`
- L275 _private* field_ `readonly ILogger _logger`
- L277-284 _public ctor_ `public TaskSourceNotificationService(IAgentCollection agentCollection, LeaseCollection leaseCollection, IEnumerable<ITaskSource> taskSources, ILogger<TaskSourceNotificationService> logger)`
- L287-291 _public method_ `public Task StartAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L294-298 _public method_ `public async Task StopAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L301 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L304-318 _private* method_ `void OnLeaseComplete(ILease lease)`
- L320-328 _private* method_ `async Task HandleCompleteLeaseAsync(ITaskSource taskSource, ILease lease, Any payload, CancellationToken cancellationToken)`

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Tasks/RestartTaskSource.cs` (HordeServer.Compute)


#### class `HordeServer.Tasks.RestartTaskSource`  
`class RestartTaskSource : TaskSourceBase<RestartTask>`  
_internal*; L13-55_
- inherits: `TaskSourceBase<RestartTask>`
- L15 _public property_ `public override string Type => ...`
- L17 _public property_ `public override TaskSourceFlags Flags => ...`
- L19 _private* field_ `readonly ILogCollection _logCollection`
- L21-26 _public ctor_ `public RestartTaskSource(ILogCollection logCollection)`
- L28-54 _public method_ `public override async Task<Task<CreateLeaseOptions?>> AssignLeaseAsync(IAgent agent, CancellationToken cancellationToken)`

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Tasks/ShutdownTaskSource.cs` (HordeServer.Compute)


#### class `HordeServer.Tasks.ShutdownTaskSource`  
`class ShutdownTaskSource : TaskSourceBase<ShutdownTask>`  
_internal*; L13-46_
- inherits: `TaskSourceBase<ShutdownTask>`
- L15 _public property_ `public override string Type => ...`
- L17 _public property_ `public override TaskSourceFlags Flags => ...`
- L19 _private* field_ `readonly ILogCollection _logCollection`
- L21-25 _public ctor_ `public ShutdownTaskSource(ILogCollection logCollection)`
- L27-45 _public method_ `public override async Task<Task<CreateLeaseOptions?>> AssignLeaseAsync(IAgent agent, CancellationToken cancellationToken)`

### `Source/Programs/Horde/Plugins/Compute/HordeServer.Compute/Tasks/UpgradeTaskSource.cs` (HordeServer.Compute)


#### class `HordeServer.Tasks.UpgradeTaskSource`  
`class UpgradeTaskSource : TaskSourceBase<UpgradeTask>`  
_internal*; L17-108_
- inherits: `TaskSourceBase<UpgradeTask>`
- L19 _public property_ `public override string Type => ...`
- L21 _public property_ `public override TaskSourceFlags Flags => ...`
- L23 _private* field_ `readonly IToolCollection _toolCollection`
- L24 _private* field_ `readonly ILogCollection _logCollection`
- L25 _private* field_ `readonly IOptionsMonitor<ComputeConfig> _computeConfig`
- L26 _private* field_ `readonly IOptions<ComputeServerConfig> _staticComputeConfig`
- L27 _private* field_ `readonly IClock _clock`
- L29-38 _public ctor_ `public UpgradeTaskSource(IToolCollection toolCollection, ILogCollection logCollection, IOptionsMonitor<ComputeConfig> computeConfig, IOptions<ComputeServerConfig> staticComputeConfig, IClock clock)`
- L40-77 _public method_ `public override async Task<Task<CreateLeaseOptions?>> AssignLeaseAsync(IAgent agent, CancellationToken cancellationToken)`
- L85-107 _public method_ `public async Task<(ITool, IToolDeployment)?> GetRequiredSoftwareVersionAsync(IAgent agent, CancellationToken cancellationToken)` — Determines the client software version that should be installed on an agent
