# CSharp / HordeServer.Tools

- project root: `Source/Programs/Horde/Plugins/Tools/HordeServer.Tools`
- files: 10; symbols: 169
- symbol kinds: class=16, ctor=12, field=22, method=49, property=70
- access marked `*` is implicit (not written in source)

### `Source/Programs/Horde/Plugins/Tools/HordeServer.Tools/Commands/Generate/ToolDataCommand.cs` (HordeServer.Tools)


#### class `HordeServer.Commands.Generate.ToolDataCommand`  
`class ToolDataCommand : Command`  
_internal*; L19-206_
- attrs: `[Command("generate", "tooldata", "Creates bundled tool data, and registers it with the server config file")]`
- inherits: `Command`
- L23 _public property_ `public string Id { get; set; }` — attrs: `[CommandLine(Required = true)] [Description("Identifier for the tool")]`
- L27 _public property_ `public string? Name { get; set; }` — attrs: `[CommandLine] [Description("Name of the tool")]`
- L31 _public property_ `public string? Description { get; set; }` — attrs: `[CommandLine] [Description("Description for the tool")]`
- L35 _public property_ `public string? Category { get; set; }` — attrs: `[CommandLine] [Description("Category for the tool")]`
- L39 _public property_ `public string? Group { get; set; }` — attrs: `[CommandLine] [Description("Group for the tool")]`
- L43 _public property_ `public List<string> Platforms { get; set; }` — attrs: `[CommandLine(ListSeparator = ';')] [Description("Semicolon delimited list of tool platforms")]`
- L47 _public property_ `public string? Version { get; set; }` — attrs: `[CommandLine] [Description("Version string for the tool")]`
- L51 _public property_ `public bool Public { get; set; }` — attrs: `[CommandLine] [Description("If true, the tool may be downloaded by any user without authentication")]`
- L55 _public property_ `public bool ShowInUgs { get; set; }` — attrs: `[CommandLine] [Description("Shows the tool for download in UGS")]`
- L59 _public property_ `public bool ShowInToolbox { get; set; }` — attrs: `[CommandLine] [Description("Shows the tool for download in the Unreal Toolbox")]`
- L63 _public property_ `public bool ShowInDashboard { get; set; }` — attrs: `[CommandLine("-ShowInDashboard=")] [Description("Shows the tool for download on the dashboard")]`
- L67 _public property_ `public List<string> Metadata { get; set; }` — attrs: `[CommandLine(ListSeparator = ';')] [Description("Semicolon delimited list of key=value metadata pairs")]`
- L71 _public property_ `public DirectoryReference InputDir { get; set; }` — attrs: `[CommandLine(Required = true)] [Description("Source directory for tool data")]`
- L75 _public property_ `public DirectoryReference ServerDir { get; set; }` — attrs: `[CommandLine] [Description("Directory containing the server to modify")]`
- L77-80 _public ctor_ `public ToolDataCommand(IServerInfo serverInfo)`
- L82-188 _public method_ `public override async Task<int> ExecuteAsync(ILogger logger)`
- L190-205 _private* method_ `static async Task PopulateCacheAsync(IStorageNamespace client, DedupeBlobWriter writer, DirectoryReference searchDir, CancellationToken cancellationToken)`

### `Source/Programs/Horde/Plugins/Tools/HordeServer.Tools/Properties/AssemblyInfo.cs` (HordeServer.Tools)
_(no declarations)_


### `Source/Programs/Horde/Plugins/Tools/HordeServer.Tools/Tools/ToolAclAction.cs` (HordeServer.Tools)


#### class `HordeServer.Tools.ToolAclAction`  
`public static class ToolAclAction`  
_public; L10-21_
- desc: ACL actions which apply to tools
- L15 _public property_ `public static AclAction DownloadTool { get; }` — Ability to download a tool
- L20 _public property_ `public static AclAction UploadTool { get; }` — Ability to upload new tool versions

### `Source/Programs/Horde/Plugins/Tools/HordeServer.Tools/Tools/ToolCollection.cs` (HordeServer.Tools)


#### class `HordeServer.Tools.ToolCollection`  
`public class ToolCollection : IToolCollection`  
_public; L28-528_
- inherits: `IToolCollection`
- desc: Collection of tool documents
- L198 _private field_ `private readonly IServerInfo _serverInfo`
- L199 _private field_ `private readonly IMongoCollection<ToolDocument> _tools`
- L200 _private field_ `private readonly StorageService _storageService`
- L201 _private field_ `private readonly FileObjectStoreFactory _fileObjectStoreFactory`
- L202 _private field_ `private readonly IClock _clock`
- L203 _private field_ `private readonly BundleCache _bundleCache`
- L204 _private field_ `private readonly MemoryMappedFileCache _memoryMappedFileCache`
- L205 _private field_ `private readonly IOptionsMonitor<ToolsConfig> _toolsConfig`
- L206 _private field_ `private readonly IOptions<ToolsServerConfig> _toolsServerConfig`
- L207 _private field_ `private readonly ILogger _logger`
- L212-224 _public ctor_ `public ToolCollection(IMongoService mongoService, IServerInfo serverInfo, StorageService storageService, BundleCache bundleCache, MemoryMappedFileCache memoryMappedFileCache, FileObjectStoreFactory fileObjectStoreFactory, IClock clock, IOptionsMonitor<ToolsConfig> toolsConfig, IOptions<ToolsServerConfig> toolsServerConfig, ILogger<ToolCollection> logger)` — Constructor
- L226-240 _private* method_ `Tool? CreateToolObject(ToolDocument? document)`
- L243-262 _public method_ `public async Task<ITool?> GetAsync(ToolId id, CancellationToken cancellationToken)` — (inheritdoc)
- L265-283 _public method_ `public async Task<IReadOnlyList<ITool>> GetAllAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L285-303 _private* method_ `async Task<ToolDocument> FindOrAddDocumentAsync(ToolConfig toolConfig, CancellationToken cancellationToken)`
- L305-318 _private* method_ `static ToolDocument CreateBundledToolDocument(BundledToolConfig bundledToolConfig)`
- L320-331 _private* method_ `static ToolDeploymentId GetDeploymentId(BundledToolConfig bundledToolConfig)`
- L333-348 _private* method_ `async Task<ToolDocument?> CreateDeploymentAsync(ToolDocument tool, ToolConfig toolConfig, ToolDeploymentConfig options, Stream stream, CancellationToken cancellationToken)`
- L350-356 _private* method_ `async Task<ToolDocument?> CreateDeploymentAsync(ToolDocument tool, ToolConfig toolConfig, ToolDeploymentConfig options, HashedBlobRefValue target, CancellationToken cancellationToken)`
- L358-395 _private* method_ `async Task<ToolDocument?> CreateDeploymentInternalAsync(ToolDocument tool, ToolConfig toolConfig, ToolDeploymentId deploymentId, ToolDeploymentConfig options, IStorageNamespace storageNamespace, IHashedBlobRef content, CancellationToken cancellationToken)`
- L397-419 _private* method_ `async ValueTask<ToolDocument?> TryAddDeploymentAsync(ToolDocument tool, ToolDeploymentDocument deployment, int maxDeploymentCount, CancellationToken cancellationToken)`
- L421-462 _private* method_ `async Task<ToolDocument?> UpdateDeploymentAsync(ToolDocument tool, ToolDeploymentId deploymentId, ToolDeploymentState action, double currentProgress, CancellationToken cancellationToken)`
- L469-479 _private* method_ `IStorageNamespace GetStorageNamespace(ToolConfig toolConfig)` — Gets the storage namespace containing data for a particular tool
- L486-496 _private* method_ `IStorageBackend CreateStorageBackend(ToolConfig toolConfig)` — Gets the storage backend containing data for a particular tool
- L498-502 _private* method_ `IBlobRef<DirectoryNode> Open(ToolConfig tool, ToolDeploymentDocument deployment)`
- L511-519 _private* method_ `async Task<Stream> GetDeploymentZipAsync(ToolConfig tool, ToolDeploymentDocument deployment, CancellationToken cancellationToken)` — Opens a stream to the data for a particular deployment
- L521-527 _private* method_ `async Task<ToolDocument> UpdateAsync(ToolDocument tool, UpdateDefinition<ToolDocument> update, CancellationToken cancellationToken)`

#### class `HordeServer.Tools.ToolCollection.ToolDocument`  
`class ToolDocument`  
_private*; L30-46_
- L32 _public property_ `public ToolId Id { get; set; }`
- L35 _public property_ `public List<ToolDeploymentDocument> Deployments { get; set; }` — attrs: `[BsonElement("dep")]`
- L39 _public property_ `public DateTime LastUpdateTime { get; set; }` — attrs: `[BsonElement("_u")]`
- L42-45 _public ctor_ `public ToolDocument(ToolId id)` — attrs: `[BsonConstructor]`

#### class `HordeServer.Tools.ToolCollection.ToolDeploymentDocument`  
`class ToolDeploymentDocument`  
_private*; L48-85_
- L50 _public property_ `public ToolDeploymentId Id { get; set; }`
- L53 _public property_ `public string Version { get; set; }` — attrs: `[BsonElement("ver")]`
- L56 _public property_ `public double BaseProgress { get; set; }` — attrs: `[BsonElement("bpr")]`
- L59 _public property_ `public DateTime? StartedAt { get; set; }` — attrs: `[BsonElement("stm")]`
- L62 _public property_ `public TimeSpan Duration { get; set; }` — attrs: `[BsonElement("dur")]`
- L65 _public property_ `public NamespaceId NamespaceId { get; set; }` — attrs: `[BsonElement("ns")]`
- L68 _public property_ `public RefName RefName { get; set; }` — attrs: `[BsonElement("ref")]`
- L71-75 _public ctor_ `public ToolDeploymentDocument(ToolDeploymentId id)` — attrs: `[BsonConstructor]`
- L77-84 _public ctor_ `public ToolDeploymentDocument(ToolDeploymentId id, ToolDeploymentConfig options, NamespaceId namespaceId, RefName refName)`

#### class `HordeServer.Tools.ToolCollection.Tool`  
`class Tool : ITool`  
_private*; L87-139_
- inherits: `ITool`
- L89 _private* field_ `readonly ToolCollection _collection`
- L90 _private* field_ `readonly ToolDocument _document`
- L91 _private* field_ `readonly ToolConfig _config`
- L92 _private* field_ `readonly List<ToolDeployment> _deployments`
- L94 _public property_ `public ToolConfig Config => ...`
- L95 _public property_ `public ToolDocument Document => ...`
- L97 _public property_ `public ToolId Id => ...`
- L98 _public property_ `public string Name => ...`
- L99 _public property_ `public string Description => ...`
- L100 _public property_ `public string? Category => ...`
- L101 _public property_ `public string? Group => ...`
- L102 _public property_ `public IReadOnlyList<string>? Platforms => ...`
- L103 _public property_ `public bool Public => ...`
- L104 _public property_ `public bool Bundled => ...`
- L105 _public property_ `public bool ShowInUgs => ...`
- L106 _public property_ `public bool ShowInDashboard => ...`
- L107 _public property_ `public bool ShowInToolbox => ...`
- L108 _public property_ `public IReadOnlyDictionary<string, string> Metadata => ...`
- L109 _public property_ `public IReadOnlyList<IToolDeployment> Deployments => ...`
- L111-117 _public ctor_ `public Tool(ToolCollection collection, ToolDocument document, ToolConfig config, DateTime utcNow)`
- L119 _public method_ `public bool Authorize(AclAction action, ClaimsPrincipal principal)`
- L122-126 _public method_ `public async Task<ITool?> CreateDeploymentAsync(ToolDeploymentConfig options, Stream stream, CancellationToken cancellationToken = default)`
- L128-132 _public method_ `public async Task<ITool?> CreateDeploymentAsync(ToolDeploymentConfig options, HashedBlobRefValue target, CancellationToken cancellationToken = default)`
- L134 _public method_ `public IStorageBackend GetStorageBackend()`
- L137 _public method_ `public IStorageNamespace GetStorageNamespace()`

#### class `HordeServer.Tools.ToolCollection.ToolDeployment`  
`class ToolDeployment : IToolDeployment`  
_private*; L141-196_
- inherits: `IToolDeployment`
- L143 _private* field_ `readonly Tool _tool`
- L144 _private* field_ `readonly ToolCollection _collection`
- L145 _private* field_ `readonly ToolDeploymentDocument _document`
- L147 _public property_ `public ToolDeploymentId Id => ...`
- L148 _public property_ `public string Version => ...`
- L149 _public property_ `public ToolDeploymentState State { get; }`
- L150 _public property_ `public double Progress { get; }`
- L151 _public property_ `public DateTime? StartedAt => ...`
- L152 _public property_ `public TimeSpan Duration => ...`
- L153 _public property_ `public NamespaceId NamespaceId => ...`
- L154 _public property_ `public RefName RefName => ...`
- L156 _public property_ `public IBlobRef<DirectoryNode> Content => ...`
- L159-185 _public ctor_ `public ToolDeployment(Tool tool, ToolCollection collection, ToolDeploymentDocument document, DateTime utcNow)`
- L187 _public method_ `public Task<Stream> OpenZipStreamAsync(CancellationToken cancellationToken = default)`
- L190-195 _public method_ `public async Task<IToolDeployment?> UpdateAsync(ToolDeploymentState action, CancellationToken cancellationToken = default)`

### `Source/Programs/Horde/Plugins/Tools/HordeServer.Tools/Tools/ToolConfig.cs` (HordeServer.Tools)


#### class `HordeServer.Tools.ToolConfig`  
`public class ToolConfig`  
_public; L20-130_
- attrs: `[DebuggerDisplay("{Id}")]`
- desc: Options for configuring a tool
- L25 _public property_ `public static NamespaceId DefaultNamespaceId { get; }` — The default namespace for tool data
- L31 _public property_ `public ToolId Id { get; set; }` — attrs: `[Required]` — Unique identifier for the tool
- L37 _public property_ `public string Name { get; set; }` — attrs: `[Required]` — Name of the tool
- L42 _public property_ `public string Description { get; set; }` — Description for the tool
- L47 _public property_ `public string? Category { get; set; }` — Category for the tool. Will cause the tool to be shown in a different tab in the dashboard.
- L52 _public property_ `public string? Group { get; set; }` — Grouping key for different variations of the same tool. The dashboard will show these together.
- L57 _public property_ `public List<string>? Platforms { get; set; }` — Platforms for this tool. Takes the form of a NET RID (https://learn.microsoft.com/en-us/dotnet/core/rid-catalog).
- L62 _public property_ `public bool Public { get; set; }` — Whether this tool should be exposed for download on a public endpoint without authentication
- L67 _public property_ `public bool ShowInUgs { get; set; }` — Whether to show this tool for download in the UGS tools menu
- L72 _public property_ `public bool ShowInDashboard { get; set; }` — Whether to show this tool for download in the dashboard
- L77 _public property_ `public bool ShowInToolbox { get; set; }` — Whether to show this tool for download in Unreal Toolbox
- L82 _public property_ `public CaseInsensitiveDictionary<string> Metadata { get; set; }` — Metadata for this tool
- L87 _public property_ `public NamespaceId NamespaceId { get; set; }` — Default namespace for new deployments of this tool
- L92 _public property_ `public int MaxDeployments { get; set; }` — Maximum number of deployments to retain for this tool. When exceeded, the oldest deployments are removed.
- L97 _public property_ `public AclConfig Acl { get; set; }` — Permissions for the tool
- L102-106 _public ctor_ `public ToolConfig()` — Default constructor for serialization
- L111-116 _public ctor_ `public ToolConfig(ToolId id)` — Constructor
- L122-125 _public method_ `public void PostLoad(AclConfig parentAcl)` — Called after the config has been read
- L128 _public method_ `public bool Authorize(AclAction action, ClaimsPrincipal user)` — (inheritdoc)

#### class `HordeServer.Tools.BundledToolConfig`  
`public class BundledToolConfig : ToolConfig`  
_public; L135-159_
- inherits: `ToolConfig`
- desc: Configuration for a tool bundled alongsize the server
- L140 _public property_ `public string Version { get; set; }` — Version string for the current tool data
- L145 _public property_ `public RefName RefName { get; set; }` — Ref name in the tools directory
- L150 _public property_ `public string? DataDir { get; set; }` — Directory containing blob data for this tool. If empty, the tools/{id} folder next to the server will be used.
- L155-158 _public ctor_ `public BundledToolConfig()` — Constructor

### `Source/Programs/Horde/Plugins/Tools/HordeServer.Tools/Tools/ToolsController.cs` (HordeServer.Tools)


#### class `HordeServer.Tools.ToolsController`  
`public class ToolsController : HordeControllerBase`  
_public; L23-189_
- attrs: `[ApiController] [Authorize] [Route("[controller]")]`
- inherits: `HordeControllerBase`
- desc: Controller for the /api/v1/tools endpoint
- L25 _private* field_ `readonly IToolCollection _toolCollection`
- L30-33 _public ctor_ `public ToolsController(IToolCollection toolCollection)` — Constructor
- L43-66 _public method_ `public async Task<ActionResult<WriteBlobResponse>> WriteBlobAsync(ToolId id, WriteBlobRequest request, CancellationToken cancellationToken = default)` — attrs: `[HttpPost] [Route("/api/v1/tools/{id}/blobs")]` — Uploads blob data for a new tool deployment.
- L77-95 _public method_ `public async Task<ActionResult<WriteBlobResponse>> WriteBlobAsync(ToolId id, BlobLocator locator, WriteBlobRequest request, CancellationToken cancellationToken = default)` — attrs: `[HttpPut] [Route("/api/v1/tools/{id}/blobs/{*locator}")]` — Uploads blob data for a new tool deployment.
- L103-125 _public method_ `public async Task<ActionResult<CreateToolDeploymentResponse>> CreateDeploymentAsync(ToolId id, [FromForm] ToolDeploymentConfig options, [FromForm] IFormFile file, CancellationToken cancellationToken)` — attrs: `[HttpPost] [Route("/api/v1/tools/{id}/deployments")]` — Create a new deployment of the given tool.
- L132-154 _public method_ `public async Task<ActionResult<CreateToolDeploymentResponse>> CreateDeploymentAsync(ToolId id, CreateToolDeploymentRequest request, CancellationToken cancellationToken)` — attrs: `[HttpPost] [Route("/api/v2/tools/{id}/deployments")]` — Create a new deployment of the given tool.
- L161-188 _public method_ `public async Task<ActionResult> UpdateDeploymentAsync(ToolId id, ToolDeploymentId deploymentId, [FromBody] UpdateDeploymentRequest request)` — attrs: `[HttpPatch] [Route("/api/v1/tools/{id}/deployments/{deploymentId}")]` — Updates the state of an active deployment.

#### class `HordeServer.Tools.PublicToolsController`  
`public class PublicToolsController : HordeControllerBase`  
_public; L197-430_
- attrs: `[ApiController] [TryAuthorize] [Tags("Tools")]`
- inherits: `HordeControllerBase`
- desc: Public methods available without authorization (or with very custom authorization)
- L199 _private* field_ `readonly IToolCollection _toolCollection`
- L200 _private* field_ `readonly IClock _clock`
- L205-209 _public ctor_ `public PublicToolsController(IToolCollection toolCollection, IClock clock)` — Constructor
- L217-231 _public method_ `public async Task<ActionResult<GetToolsSummaryResponse>> GetToolsAsync()` — attrs: `[HttpGet] [TryAuthorize] [Route("/api/v1/tools")]` — Enumerates all the available tools.
- L233-237 _private* method_ `static GetToolSummaryResponse CreateGetToolSummaryResponse(ITool tool)`
- L245-276 _public method_ `public async Task<ActionResult> GetToolAsync(ToolId id, GetToolAction action = GetToolAction.Info, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/tools/{id}")]` — Gets information about a particular tool
- L278-281 _private* method_ `static GetToolResponse CreateGetToolResponse(ITool tool, List<GetToolDeploymentResponse> deployments)`
- L293-312 _public method_ `public async Task<ActionResult> FindDeploymentAsync(ToolId id, [FromQuery] double phase = 0.0, [FromQuery] GetToolAction action = GetToolAction.Info, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/tools/{id}/deployments")]` — Finds deployments of a particular tool.
- L320-339 _public method_ `public async Task<ActionResult> GetDeploymentAsync(ToolId id, ToolDeploymentId deploymentId, [FromQuery] GetToolAction action = GetToolAction.Info, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/tools/{id}/deployments/{deploymentId}")]` — Gets information about a specific tool deployment.
- L341-375 _private method_ `private async Task<ActionResult> GetDeploymentResponseAsync(ITool tool, IToolDeployment deployment, GetToolAction action, CancellationToken cancellationToken)`
- L377-383 _private* method_ `static async Task<GetToolDeploymentResponse> GetDeploymentInfoResponseAsync(ITool tool, IToolDeployment deployment, CancellationToken cancellationToken)`
- L394-413 _public method_ `public async Task<ActionResult> ReadToolBlobAsync(ToolId id, BlobLocator locator, CancellationToken cancellationToken = default)` — attrs: `[HttpGet] [Route("/api/v1/tools/{id}/blobs/{*locator}")]` — Retrieves blobs for a particular tool
- L415-429 _private* method_ `bool AuthorizeDownload(ITool tool)`

### `Source/Programs/Horde/Plugins/Tools/HordeServer.Tools/ToolsAclModifier.cs` (HordeServer.Tools)


#### class `HordeServer.ToolsAclModifier`  
`class ToolsAclModifier : IDefaultAclModifier`  
_internal*; L9-16_
- inherits: `IDefaultAclModifier`
- L12-15 _public method_ `public void Apply(DefaultAclBuilder acl)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Tools/HordeServer.Tools/ToolsConfig.cs` (HordeServer.Tools)


#### class `HordeServer.Tools.ToolsConfig`  
`public class ToolsConfig : IPluginConfig`  
_public; L14-41_
- inherits: `IPluginConfig`
- desc: Configuration for the tools system
- L19 _public property_ `public List<ToolConfig> Tools { get; set; }` — Tool configurations
- L21 _private field_ `private readonly Dictionary<ToolId, ToolConfig> _toolLookup = ...`
- L21 _private field_ `private readonly Dictionary< _toolLookup = new Dictionary<ToolId, ToolConfig>()`
- L24-32 _public method_ `public void PostLoad(PluginConfigOptions configOptions)` — (inheritdoc)
- L40 _public method_ `public bool TryGetTool(ToolId toolId, [NotNullWhen(true)] out ToolConfig? config)` — Attempts to get configuration for a tool from this object

### `Source/Programs/Horde/Plugins/Tools/HordeServer.Tools/ToolsPlugin.cs` (HordeServer.Tools)


#### class `HordeServer.ToolsPlugin`  
`public class ToolsPlugin : IPluginStartup`  
_public; L18-32_
- attrs: `[Plugin("Tools", GlobalConfigType = typeof(ToolsConfig), ServerConfigType = typeof(ToolsServerConfig))]`
- inherits: `IPluginStartup`
- desc: Entry point for the storage plugin
- L21-22 _public method_ `public void Configure(IApplicationBuilder app)` — (inheritdoc)
- L25-31 _public method_ `public void ConfigureServices(IServiceCollection services)` — (inheritdoc)

#### class `HordeServer.ToolsPluginExtensions`  
`public static class ToolsPluginExtensions`  
_public; L37-44_
- desc: Helper methods for tools config
- L42 _public method_ `public static void AddToolsConfig(this IDictionary<PluginName, IPluginConfig> dictionary, ToolsConfig toolsConfig)` — Configures the tools plugin

### `Source/Programs/Horde/Plugins/Tools/HordeServer.Tools/ToolsServerConfig.cs` (HordeServer.Tools)


#### class `HordeServer.ToolsServerConfig`  
`public class ToolsServerConfig : PluginServerConfig`  
_public; L15-33_
- inherits: `PluginServerConfig`
- desc: Server configuration for bundled tools
- L20 _public property_ `public List<BundledToolConfig> BundledTools { get; set; }` — Tools bundled along with the server. Data for each tool can be produced using the 'bundle create' command, and should be stored in the Tools directory.
- L28-32 _public method_ `public bool TryGetBundledTool(ToolId toolId, [NotNullWhen(true)] out BundledToolConfig? bundledToolConfig)` — Attempts to get a bundled tool with the given id
