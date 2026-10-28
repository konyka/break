# CSharp / HordeServer.Tests.Shared

- project root: `Source/Programs/Horde/HordeServer.Tests.Shared`
- files: 9; symbols: 152
- symbol kinds: class=12, const=1, ctor=14, field=19, method=48, property=58
- access marked `*` is implicit (not written in source)

### `Source/Programs/Horde/HordeServer.Tests.Shared/AppHostStub.cs` (HordeServer.Tests.Shared)


#### class `HordeServer.Tests.AppLifetimeStub`  
`public class AppLifetimeStub : IHostApplicationLifetime`  
_public; L7-24_
- inherits: `IHostApplicationLifetime`
- L9 _public property_ `public CancellationToken ApplicationStarted { get; }`
- L10 _public property_ `public CancellationToken ApplicationStopping { get; }`
- L11 _public property_ `public CancellationToken ApplicationStopped { get; }`
- L13-18 _public ctor_ `public AppLifetimeStub()`
- L20-23 _public method_ `public void StopApplication()`

### `Source/Programs/Horde/HordeServer.Tests.Shared/DatabaseRunner.cs` (HordeServer.Tests.Shared)


#### class `HordeServer.Tests.DatabaseRunner`  
`public abstract class DatabaseRunner : IDisposable`  
_public; L13-192_
- inherits: `IDisposable`
- L15 _private field_ `private readonly string _binName`
- L16 _private field_ `private readonly int _defaultPort`
- L17 _private field_ `private readonly string _name`
- L18 _private field_ `private readonly bool _reuseProcess`
- L19 _protected property_ `protected string TempDir { get; }`
- L21 _private field_ `private ManagedProcessGroup? _processGroup`
- L22 _private field_ `private ManagedProcess? _process`
- L24-31 _protected ctor_ `protected DatabaseRunner(string name, string binName, int defaultPort, bool reuseProcess)`
- L34-38 _public method_ `public void Dispose()` — (inheritdoc)
- L40-43 _protected method_ `protected virtual void Dispose(bool disposing)`
- L45 _protected property_ `protected int Port { get; set; }`
- L47 _protected method_ `protected abstract string GetArguments()`
- L49-83 _public method_ `public void Start()`
- L85-96 _private* method_ `static async Task RelayOutputAsync(ManagedProcess process)`
- L98-111 _public method_ `public void Stop()`
- L113-116 _public method_ `public (string Host, int Port) GetListenAddress()`
- L118-123 _private method_ `private string GetBinaryPath()`
- L125-130 _private method_ `private string GetTemporaryDirectory()`
- L132-141 _private method_ `private static int GetAvailablePort(int timeoutMs = 5000)`
- L143-175 _public method_ `public static bool IsPortAvailable(int port, int timeoutMs = 5000)`
- L177-191 _private method_ `private static void DeleteDirectory(string path)`

#### class `HordeServer.Tests.MongoDbRunnerLocal`  
`public class MongoDbRunnerLocal : DatabaseRunner`  
_public; L194-210_
- inherits: `DatabaseRunner`
- L196-198 _public ctor_ `public MongoDbRunnerLocal() : base("mongodb", "ThirdParty/Mongo/mongod.exe", 27017, true)`
- L200-203 _protected method_ `protected override string GetArguments()`
- L205-209 _public method_ `public string GetConnectionString()`

### `Source/Programs/Horde/HordeServer.Tests.Shared/DowntimeServiceStub.cs` (HordeServer.Tests.Shared)


#### class `HordeServer.Tests.DowntimeServiceStub`  
`public class DowntimeServiceStub : IDowntimeService`  
_public; L7-15_
- inherits: `IDowntimeService`
- L9-12 _public ctor_ `public DowntimeServiceStub(bool isDowntimeActive = false)`
- L14 _public property_ `public bool IsDowntimeActive { get; set; }`

### `Source/Programs/Horde/HordeServer.Tests.Shared/GrpcTestHelpers.cs` (HordeServer.Tests.Shared)


#### class `HordeServer.Tests.TestServerStreamWriter`  
`public class TestServerStreamWriter<T> : IServerStreamWriter<T> where T : class`  
_public; L26-77_
- inherits: `IServerStreamWriter<T>`
- constraints: `where T : class`
- L28 _private field_ `private readonly ServerCallContext _serverCallContext`
- L29 _private field_ `private readonly Channel<T> _channel`
- L31 _public property_ `public WriteOptions? WriteOptions { get; set; }`
- L33-38 _public ctor_ `public TestServerStreamWriter(ServerCallContext serverCallContext)`
- L40-43 _public method_ `public void Complete()`
- L45-48 _public method_ `public IAsyncEnumerable<T> ReadAllAsync()`
- L50-61 _public method_ `public async Task<T?> ReadNextAsync()`
- L63-76 _public method_ `public Task WriteAsync(T message)`

#### class `HordeServer.Tests.TestAsyncStreamReader`  
`public class TestAsyncStreamReader<T> : IAsyncStreamReader<T> where T : class`  
_public; L79-121_
- inherits: `IAsyncStreamReader<T>`
- constraints: `where T : class`
- L81 _private field_ `private readonly Channel<T> _channel`
- L82 _private field_ `private readonly ServerCallContext _serverCallContext`
- L84 _public property_ `public T Current { get; set; }`
- L86-90 _public ctor_ `public TestAsyncStreamReader(ServerCallContext serverCallContext)`
- L92-98 _public method_ `public void AddMessage(T message)`
- L100-103 _public method_ `public void Complete()`
- L105-120 _public method_ `public async Task<bool> MoveNext(CancellationToken cancellationToken)`

### `Source/Programs/Horde/HordeServer.Tests.Shared/HttpContextStub.cs` (HordeServer.Tests.Shared)


#### class `HordeServer.Tests.ConnectionInfoStub`  
`public sealed class ConnectionInfoStub : ConnectionInfo`  
_public; L16-41_
- inherits: `ConnectionInfo`
- desc: Stub implementation of ConnectionInfo for testing
- L19 _public property_ `public override string Id { get; set; }` — (inheritdoc)
- L22 _public property_ `public override IPAddress? RemoteIpAddress { get; set; }` — (inheritdoc)
- L25 _public property_ `public override int RemotePort { get; set; }` — (inheritdoc)
- L28 _public property_ `public override IPAddress? LocalIpAddress { get; set; }` — (inheritdoc)
- L31 _public property_ `public override int LocalPort { get; set; }` — (inheritdoc)
- L34 _public property_ `public override X509Certificate2? ClientCertificate { get; set; }` — (inheritdoc)
- L37-40 _public method_ `public override Task<X509Certificate2?> GetClientCertificateAsync(CancellationToken cancellationToken = default)` — (inheritdoc)

#### class `HordeServer.Tests.HttpContextStub`  
`sealed class HttpContextStub : HttpContext`  
_internal*; L43-73_
- inherits: `HttpContext`
- L45 _public property_ `public override ConnectionInfo Connection { get; }`
- L46 _public property_ `public override IFeatureCollection Features { get; }`
- L47 _public property_ `public override IDictionary<object, object?> Items { get; set; }`
- L48 _public property_ `public override HttpRequest Request { get; }`
- L49 _public property_ `public override CancellationToken RequestAborted { get; set; }`
- L50 _public property_ `public override IServiceProvider RequestServices { get; set; }`
- L51 _public property_ `public override HttpResponse Response { get; }`
- L52 _public property_ `public override ISession Session { get; set; }`
- L53 _public property_ `public override string TraceIdentifier { get; set; }`
- L54 _public property_ `public override ClaimsPrincipal User { get; set; }`
- L55 _public property_ `public override WebSocketManager WebSockets { get; }`
- L57-61 _public ctor_ `public HttpContextStub(Claim? roleClaimType, IPAddress? remoteIpAddress = null)`
- L63-67 _public ctor_ `public HttpContextStub(ClaimsPrincipal user, IPAddress? remoteIpAddress = null)`
- L69-72 _public method_ `public override void Abort()`

### `Source/Programs/Horde/HordeServer.Tests.Shared/ServerCallContextStub.cs` (HordeServer.Tests.Shared)


#### class `HordeServer.Tests.ServerCallContextStub`  
`public class ServerCallContextStub : ServerCallContext`  
_public; L10-73_
- inherits: `ServerCallContext`
- L13 _private* const_ `const string HttpContextKey = "__HttpContext"`
- L15 _protected property_ `protected override string MethodCore { get; }`
- L16 _protected property_ `protected override string HostCore { get; }`
- L17 _protected property_ `protected override string PeerCore { get; }`
- L18 _protected property_ `protected override DateTime DeadlineCore { get; }`
- L19 _protected property_ `protected override Metadata RequestHeadersCore { get; }`
- L20 _protected property_ `protected override CancellationToken CancellationTokenCore => ...`
- L21 _protected property_ `protected override Metadata ResponseTrailersCore { get; }`
- L22 _protected property_ `protected override Status StatusCore { get; set; }`
- L23 _protected property_ `protected override WriteOptions? WriteOptionsCore { get; set; }`
- L24 _protected property_ `protected override AuthContext AuthContextCore { get; }`
- L26 _private field_ `private CancellationToken _cancellationToken`
- L28-35 _public method_ `public static ServerCallContext ForAdminWithAgentSessionId(string agentSessionId)`
- L37-43 _public method_ `public static ServerCallContext ForAdmin(IPAddress? remoteIpAddress = null)`
- L45-50 _public ctor_ `public ServerCallContextStub(Claim? roleClaimType, IPAddress? remoteIpAddress = null)`
- L52-57 _public ctor_ `public ServerCallContextStub(ClaimsPrincipal user, IPAddress? remoteIpAddress = null)`
- L59-62 _public method_ `public void SetCancellationToken(CancellationToken cancellationToken)`
- L64-67 _protected method_ `protected override Task WriteResponseHeadersAsyncCore(Metadata responseHeaders)`
- L69-72 _protected method_ `protected override ContextPropagationToken CreatePropagationTokenCore(ContextPropagationOptions? options)`

### `Source/Programs/Horde/HordeServer.Tests.Shared/ServerTestSetup.cs` (HordeServer.Tests.Shared)


#### class `HordeServer.Tests.ServerTestSetup`  
`public class ServerTestSetup : DatabaseIntegrationTest`  
_public; L30-236_
- inherits: `DatabaseIntegrationTest`
- L32 _public property_ `public FakeClock Clock => ...`
- L33 _public property_ `public IMemoryCache Cache => ...`
- L35 _public property_ `public IAclService AclService => ...`
- L36 _public property_ `public IMongoService MongoService => ...`
- L37 _public property_ `public IDowntimeService DowntimeService => ...`
- L38 _public property_ `public LifetimeService LifetimeService => ...`
- L39 _public property_ `public ServerStatusService ServerStatusService => ...`
- L41 _public property_ `public ServerSettings ServerSettings => ...`
- L42 _public property_ `public IOptionsMonitor<ServerSettings> ServerSettingsMon => ...`
- L44 _public property_ `public OpenTelemetry.Trace.Tracer Tracer => ...`
- L45 _public property_ `public Meter Meter => ...`
- L46 _public property_ `public ConfigService ConfigService => ...`
- L47 _public property_ `public ILogger<ConfigService> ConfigServiceLogger => ...`
- L48 _public property_ `public IOptionsMonitor<GlobalConfig> GlobalConfig => ...`
- L49 _public property_ `public IOptionsSnapshot<GlobalConfig> GlobalConfigSnapshot => ...`
- L51 _public property_ `public IPluginCollection PluginCollection => ...`
- L52 _public property_ `public IEnumerable<IDefaultAclModifier> DefaultAclModifiers => ...`
- L54 _private field_ `private static bool s_datadogWriterPatched`
- L56 _private* field_ `readonly PluginCollection _pluginCollection`
- L58-63 _public ctor_ `public ServerTestSetup()`
- L65-75 _private* ctor_ `static ServerTestSetup()`
- L77-83 _protected method_ `protected async Task SetConfigAsync(GlobalConfig globalConfig)`
- L85-93 _protected method_ `protected async Task UpdateConfigAsync(Action<GlobalConfig> action)`
- L95-107 _protected method_ `protected override void ConfigureSettings(ServerSettings settings)`
- L109-165 _protected method_ `protected override void ConfigureServices(IServiceCollection services)`
- L167-170 _protected method_ `protected void AddPlugin<T>() where T : class, IPluginStartup`
- L177-186 _public method_ `public static ILogger<T> CreateConsoleLogger<T>()` — Create a console logger for tests
- L194-235 _private method_ `private static void PatchDatadogWriter()` — Hack the Datadog tracing library to not block during shutdown of tests. Without this fix, the lib will try to send traces to a host that isn't running and block for +20 secs Since so many of the interfaces and classes in the lib are internal it was difficult to replace Tracer.Instance

### `Source/Programs/Horde/HordeServer.Tests.Shared/TestScopedMongoService.cs` (HordeServer.Tests.Shared)


#### class `HordeServer.Tests.TestScopedMongoService`  
`public sealed class TestScopedMongoService : IMongoService, IDisposable`  
_public; L14-142_
- inherits: `IMongoService, IDisposable`
- desc: Implementation instantiated per test with a unique database name to sandbox and isolate reads/writes during a test
- L16 _public property_ `public IMongoDatabase Database { get; }`
- L17 _public property_ `public bool ReadOnlyMode { get; }`
- L19 _private field_ `private readonly string _dbName = $"HordeTest-{Guid.NewGuid()}"`
- L20 _private field_ `private readonly MongoClient _mongoClient`
- L21 _private field_ `private readonly IMongoCollection<BsonDocument> _singletonsV1`
- L22 _private field_ `private readonly IMongoCollection<BsonDocument> _singletonsV2`
- L23 _private field_ `private readonly ISet<string> _indexesCreated = new HashSet<string>()`
- L24 _private field_ `private readonly object _indexLock = new()`
- L26-32 _public ctor_ `public TestScopedMongoService(MongoClient mongoClient)`
- L35-38 _public method_ `public void Dispose()` — (inheritdoc)
- L41-44 _public method_ `public MongoClient GetClient()` — (inheritdoc)
- L47-50 _public method_ `public IMongoCollection<T> GetCollection<T>(string name)` — (inheritdoc)
- L53-56 _public method_ `public IMongoCollection<T> GetCollection<T>(string name, Func<IndexKeysDefinitionBuilder<T>, IndexKeysDefinition<T>> keysFunc, bool unique = false)` — (inheritdoc)
- L59-64 _public method_ `public IMongoCollection<T> GetCollection<T>(string name, IEnumerable<MongoIndex<T>> indexes)` — (inheritdoc)
- L66-89 _private method_ `private void AddIndexes<T>(string collectionName, IMongoCollection<T> collection, MongoIndex<T>[] indexes)`
- L92-95 _public method_ `public Task<T> GetSingletonAsync<T>(CancellationToken cancellationToken) where T : SingletonBase, new()` — (inheritdoc)
- L98-101 _public method_ `public Task<T> GetSingletonAsync<T>(Func<T> constructor, CancellationToken cancellationToken) where T : SingletonBase, new()` — (inheritdoc)
- L104-112 _public method_ `public Task UpdateSingletonAsync<T>(Action<T> updater, CancellationToken cancellationToken) where T : SingletonBase, new()` — (inheritdoc)
- L115-129 _public method_ `public async Task UpdateSingletonAsync<T>(Func<T, bool> updater, CancellationToken cancellationToken) where T : SingletonBase, new()` — (inheritdoc)
- L132-135 _public method_ `public Task<bool> TryUpdateSingletonAsync<T>(T singletonObject, CancellationToken cancellationToken) where T : SingletonBase` — (inheritdoc)
- L138-141 _public method_ `public Task<HealthCheckResult> CheckHealthAsync(HealthCheckContext context, CancellationToken cancellationToken = new CancellationToken())` — (inheritdoc)

### `Source/Programs/Horde/HordeServer.Tests.Shared/WebHostEnvironmentStub.cs` (HordeServer.Tests.Shared)


#### class `HordeServer.Tests.WebHostEnvironmentStub`  
`public class WebHostEnvironmentStub : IHostEnvironment`  
_public; L8-20_
- inherits: `IHostEnvironment`
- L10 _public property_ `public string ApplicationName { get; set; }`
- L11 _public property_ `public IFileProvider ContentRootFileProvider { get; set; }`
- L12 _public property_ `public string ContentRootPath { get; set; }`
- L13 _public property_ `public string EnvironmentName { get; set; }`
- L15-19 _public ctor_ `public WebHostEnvironmentStub()`
