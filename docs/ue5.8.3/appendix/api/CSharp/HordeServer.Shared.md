# CSharp / HordeServer.Shared

- project root: `Source/Programs/Horde/HordeServer.Shared`
- files: 81; symbols: 791
- symbol kinds: class=108, const=27, ctor=50, enum=3, enumerator=11, event=1, field=52, indexer=1, interface=39, method=310, operator=3, property=176, record=6, record struct=3, struct=1
- access marked `*` is implicit (not written in source)

### `Source/Programs/Horde/HordeServer.Shared/Acls/AclConfig.cs` (HordeServer.Shared)


#### class `HordeServer.Acls.AclConfig`  
`public class AclConfig`  
_public; L17-275_
- desc: Parameters to update an ACL
- L23 _public property_ `public AclConfig? Parent { get; set; }` — attrs: `[JsonIgnore]` — The parent scope object
- L29 _public property_ `public AclScopeName ScopeName { get; set; }` — attrs: `[JsonIgnore]` — Name of this scope
- L35 _public property_ `public AclScopeName[]? LegacyScopeNames { get; set; }` — attrs: `[JsonIgnore]` — Legacy aliases for this scope
- L41 _public property_ `public AclAction[]? Actions { get; set; }` — attrs: `[JsonIgnore]` — ACL actions associated with this config (for debugging purposes)
- L47 _public property_ `public List<AclConfig>? Children { get; set; }` — attrs: `[JsonIgnore]` — ACLs which are parented to this
- L52 _public property_ `public List<AclEntryConfig>? Entries { get; set; }` — Entries to replace the existing ACL
- L57 _public property_ `public List<AclProfileConfig>? Profiles { get; set; }` — Defines profiles which allow grouping sets of actions into named collections
- L62 _public property_ `public bool? Inherit { get; set; }` — Whether to inherit permissions from the parent ACL
- L67 _public property_ `public List<AclAction>? Exceptions { get; set; }` — List of exceptions to the inherited setting
- L69 _private* field_ `IReadOnlyDictionary<AclProfileId, AclProfileConfig> _profileLookup = ...`
- L69 _private* field_ `IReadOnlyDictionary< _profileLookup = null!`
- L77 _public method_ `public bool Authorize(AclAction action, ClaimsPrincipal user)` — Tests whether a user is authorized to perform the given actions
- L86-103 _public method_ `public bool? TryAuthorize(AclAction action, ClaimsPrincipal user)` — Tests whether a user is authorized to perform the given actions
- L111-164 _public method_ `public bool? AuthorizeSingleScope(AclAction action, ClaimsPrincipal user)` — Tests whether a user is authorized to perform the given actions in this specific scope
- L169-172 _public method_ `public void PostLoad(AclConfig parentScope, string scopeNameSuffix, AclAction[] actions)` — Called after the config file has been read
- L177-220 _public method_ `public void PostLoad(AclConfig? parentScope, AclScopeName scopeName, AclAction[] actions)` — Called after the config file has been read
- L225-230 _public method_ `public Dictionary<AclScopeName, HashSet<AclAction>> FindEntitlements(Predicate<AclClaimConfig> predicate)` — Find all entitlements for a user
- L235-260 _public method_ `public void FindEntitlements(Predicate<AclClaimConfig> predicate, Dictionary<AclScopeName, HashSet<AclAction>> scopeToActions)` — Find all entitlements for a user
- L267-274 _public method_ `public static AclAction[] GetActions(Type[] type)` — Get all AclActions declared for the types specified

#### class `HordeServer.Acls.AclEntryConfig`  
`public class AclEntryConfig`  
_public; L280-354_
- desc: Individual entry in an ACL
- L286 _public property_ `public AclClaimConfig Claim { get; set; }` — attrs: `[Required]` — Name of the user or group
- L291 _public property_ `public List<AclAction>? Actions { get; set; }` — Array of actions to allow
- L296 _public property_ `public List<AclProfileId>? Profiles { get; set; }` — List of profiles to grant
- L302 _public property_ `public HashSet<AclAction> ComputedActions { get; set; }` — attrs: `[JsonIgnore]` — List of all actions inherited from all profiles
- L307-310 _public ctor_ `public AclEntryConfig()` — Private constructor for serialization
- L318-329 _public ctor_ `public AclEntryConfig(AclClaimConfig claim, IEnumerable<AclAction>? actions, IEnumerable<AclProfileId>? profiles = null)` — Constructor
- L331-343 _internal method_ `internal void PostLoad(AclScopeName scopeName, IReadOnlyDictionary<AclProfileId, AclProfileConfig> profileLookup)`
- L345-353 _private* method_ `static IEnumerable<AclAction> GetActionsForProfile(AclScopeName scopeName, AclProfileId profileId, IReadOnlyDictionary<AclProfileId, AclProfileConfig> profileLookup)`

#### class `HordeServer.Acls.AclProfileConfig`  
`public class AclProfileConfig`  
_public; L359-424_
- desc: Configuration for an ACL profile. This defines a preset group of actions which can be given to a user via an ACL entry.
- L364 _public property_ `public AclProfileId Id { get; set; }` — Identifier for this profile
- L369 _public property_ `public List<AclAction>? Actions { get; set; }` — Actions to include
- L374 _public property_ `public List<AclAction>? ExcludeActions { get; set; }` — Actions to exclude from the inherited actions
- L379 _public property_ `public List<AclProfileId>? Extends { get; set; }` — Other profiles to extend from
- L385 _internal property_ `internal HashSet<AclAction> ComputedActions { get; set; }` — attrs: `[JsonIgnore]` — Computed list of actions after considering base profiles etc... Fixed up by calling PostLoad().
- L387-411 _internal method_ `internal void PostLoad(AclScopeName scopeName, Dictionary<AclProfileId, AclProfileConfig> profileLookup, HashSet<AclProfileId> visited)`
- L413-423 _private* method_ `static IEnumerable<AclAction> GetActionsForProfile(AclScopeName scopeName, AclProfileId profileId, Dictionary<AclProfileId, AclProfileConfig> profileLookup, HashSet<AclProfileId> visited)`

#### class `HordeServer.Acls.AclClaimConfig`  
`public class AclClaimConfig : IAclClaim`  
_public; L429-476_
- inherits: `IAclClaim`
- desc: New claim to create
- L435 _public property_ `public string Type { get; set; }` — attrs: `[Required]` — The claim type
- L441 _public property_ `public string Value { get; set; }` — attrs: `[Required]` — The claim value
- L446-450 _public ctor_ `public AclClaimConfig()` — Constructor
- L456-459 _public ctor_ `public AclClaimConfig(Claim claim) : this(claim.Type, claim.Value)` — Constructor
- L466-470 _public ctor_ `public AclClaimConfig(string type, string value)` — Constructor
- L475 _public method_ `public Claim ToClaim()` — Converts this object to a regular Claim object.

### `Source/Programs/Horde/HordeServer.Shared/Acls/AclProfileId.cs` (HordeServer.Shared)


#### record struct `HordeServer.Acls.AclProfileId`  
`public record struct AclProfileId(StringId Id)`  
_public; L17-31_
- attrs: `[LogValueType] [JsonSchemaString] [TypeConverter(typeof(StringIdTypeConverter<AclProfileId, AclProfileIdConverter>))] [StringIdConverter(typeof(AclProfileIdConverter))]`
- desc: Identifier for a profile; a group of actions which can be assigned to a user as a whole.
- L22-24 _public ctor_ `public AclProfileId(string id) : this(new StringId(id))` — Constructor
- L27 _public property_ `public bool IsEmpty => ...` — (inheritdoc)
- L30 _public method_ `public override string ToString()` — (inheritdoc)

#### class `HordeServer.Acls.AclProfileIdConverter`  
`class AclProfileIdConverter : StringIdConverter<AclProfileId>`  
_internal*; L36-43_
- inherits: `StringIdConverter<AclProfileId>`
- desc: Converter to and from StringId instances.
- L39 _public method_ `public override AclProfileId FromStringId(StringId id)` — (inheritdoc)
- L42 _public method_ `public override StringId ToStringId(AclProfileId value)` — (inheritdoc)

### `Source/Programs/Horde/HordeServer.Shared/Acls/IAclService.cs` (HordeServer.Shared)


#### interface `HordeServer.Acls.IAclService`  
`public interface IAclService`  
_public; L12-29_
- desc: Functionality for manipulating ACLs
- L21 _public* method_ `ValueTask<string> IssueBearerTokenAsync(IEnumerable<Claim> claims, TimeSpan? expiry, CancellationToken cancellationToken = default)` — Issues a bearer token with the given roles
- L28 _public* method_ `bool TryGetAclScope(AclScopeName scopeName, [NotNullWhen(true)] out AclConfig? scopeConfig)` — Finds an ACL scope by name

#### class `HordeServer.Acls.AclServiceExtensions`  
`public static class AclServiceExtensions`  
_public; L34-56_
- desc: Extension methods for IAclService
- L43 _public method_ `public static bool Authorize(this IAclService aclService, AclScopeName scopeName, AclAction action, ClaimsPrincipal user)` — Authorizes a user to perform a given action
- L54 _public method_ `public static async ValueTask<string> IssueBearerTokenAsync(this IAclService aclService, IEnumerable<AclClaimConfig> claims, TimeSpan? expiry, CancellationToken cancellationToken = default)` — Issues a bearer token with the given roles

### `Source/Programs/Horde/HordeServer.Shared/Acls/IDefaultAclModifier.cs` (HordeServer.Shared)


#### interface `HordeServer.Acls.IDefaultAclModifier`  
`public interface IDefaultAclModifier`  
_public; L10-16_
- desc: Interface which can be implemented by classes that mutate the default ACL
- L15 _public* method_ `void Apply(DefaultAclBuilder builder)` — Modifies the default ACL

### `Source/Programs/Horde/HordeServer.Shared/Auditing/IAuditLog.cs` (HordeServer.Shared)


#### interface `HordeServer.Auditing.IAuditLogMessage`  
`public interface IAuditLogMessage`  
_public; L12-28_
- desc: Message from an audit log
- L17 _public property_ `public DateTime TimeUtc { get; }` — Timestamp for the event
- L22 _public property_ `public LogLevel Level { get; }` — Severity of the message
- L27 _public property_ `public string Data { get; }` — The message payload. Should be an encoded JSON object, with format/properties fields.

#### interface `HordeServer.Auditing.IAuditLogChannel`  
`public interface IAuditLogChannel : ILogger`  
_public; L33-60_
- inherits: `ILogger`
- desc: Channel for a particular entity
- L44 _public* method_ `IAsyncEnumerable<IAuditLogMessage> FindAsync(DateTime? minTime = null, DateTime? maxTime = null, int? index = null, int? count = null, CancellationToken cancellationToken = default)` — Finds messages matching certain criteria
- L53 _public* method_ `Task<long> DeleteAsync(DateTime? minTime = null, DateTime? maxTime = null, CancellationToken cancellationToken = default)` — Deletes messages between a given time range for a particular object
- L59 _public* method_ `Task FlushAsync(CancellationToken cancellationToken = default)` — Flush all writes to this log

#### interface `HordeServer.Auditing.IAuditLogChannel`  
`public interface IAuditLogChannel<TSubject> : IAuditLogChannel`  
_public; L65-71_
- inherits: `IAuditLogChannel`
- desc: Channel for a particular entity
- L70 _public* property_ `TSubject Subject { get; }` — Identifier for the subject of this channel

#### interface `HordeServer.Auditing.IAuditLogMessage`  
`public interface IAuditLogMessage<TTargetId> : IAuditLogMessage`  
_public; L77-83_
- inherits: `IAuditLogMessage`
- desc: Message in an audit log
- L82 _public property_ `public TTargetId Subject { get; }` — Unique id for the entity

#### interface `HordeServer.Auditing.IAuditLog`  
`public interface IAuditLog<TSubject>`  
_public; L88-96_
- desc: Interface for a collection of log messages for a particular document type
- L95 _public* indexer_ `IAuditLogChannel<TSubject> this[TSubject subject] { get; }` — Get the channel for a particular subject

#### interface `HordeServer.Auditing.IAuditLogFactory`  
`public interface IAuditLogFactory<TSubject>`  
_public; L102-111_
- desc: Factory for instantiating audit log instances
- L110 _public* method_ `IAuditLog<TSubject> Create(string collectionName, string subjectProperty)` — Create a new audit log instance, with the given database name

#### class `HordeServer.Auditing.AuditLogExtensions`  
`public static class AuditLogExtensions`  
_public; L116-145_
- desc: Extension methods for audit log channels
- L129-144 _public method_ `public static async Task FindAsync(this IAuditLogChannel channel, PipeWriter bodyWriter, DateTime? minTime = null, DateTime? maxTime = null, int index = 0, int count = 50, CancellationToken cancellationToken = default)` — Retrieve historical information about a specific agent

### `Source/Programs/Horde/HordeServer.Shared/ConfigVersion.cs` (HordeServer.Shared)


#### enum `HordeServer.ConfigVersion`  
`public enum ConfigVersion`  
_public; L11-37_
- desc: Global version number for running the server. As new features are introduced that require data migrations, this version number indicates the backwards compatibility functionality that must be enabled. When adding a new version here, also add a message to ConfigService.CreateSnapshotAsync describing the steps that need to be taken to upgrade the deployment.
- L16 _public* enumerator_ `None` — Not specified
- L21 _public* enumerator_ `Initial` — Initial version number
- L26 _public* enumerator_ `PoolsInConfigFiles` — All pools are managed through config files. Database pool reads are disabled.
- L31 _public* enumerator_ `LatestPlusOne` — One after the last defined version number
- L36 _public* enumerator_ `Latest = LatestPlusOne - 1` — Latest version number

### `Source/Programs/Horde/HordeServer.Shared/Configuration/ConfigContext.cs` (HordeServer.Shared)


#### class `HordeServer.Configuration.ConfigContext`  
`public class ConfigContext`  
_public; L17-258_
- attrs: `[DebuggerDisplay("{CurrentFile}")]`
- desc: Context for reading a tree of config files
- L22 _public property_ `public JsonSerializerOptions JsonOptions { get; }` — Options for serializing config files
- L27 _public property_ `public Stack<IConfigFile> IncludeStack { get; }` — Stack of included files
- L32 _public property_ `public Stack<string> ScopeStack { get; }` — Stack of properties
- L37 _public property_ `public Dictionary<string, Uri> PropertyPathToFile { get; }` — Map of property path to the file declaring a value for it
- L42 _public property_ `public IReadOnlyDictionary<string, IConfigSource> Sources { get; }` — Sources to read config files from
- L47 _public property_ `public List<Dictionary<string, string>> MacroScopes { get; }` — Map of macro name to value
- L52 _public property_ `public Dictionary<Uri, IConfigFile> Files { get; }` — Tracks files read as part of the configuration
- L62 _public property_ `public Dictionary<Uri, Uri?> ProcessedIncludes { get; set; }` — Tracks files already processed as includes within the current include root scope, preventing diamond dependencies from causing the same file to be merged multiple times. Maps each included URI to the URI of the file that first included it. Each [ConfigIncludeRoot] entered from property/array traversal saves and restores this so sibling roots (e.g. two StreamConfigs in the same project) get independent scopes. Roots entered from include processing share the parent's scope for diamond detection.
- L67 _public property_ `public int IncludeRootDepth { get; set; }` — Depth counter for nested [ConfigIncludeRoot] processing.
- L75 _public property_ `public bool InIncludeScope { get; set; }` — When true, the current PreprocessAsync call is processing an included file (recursive from the include loop). [ConfigIncludeRoot] entries should share the parent's diamond dedup scope rather than creating a fresh one, so that diamonds within the same include tree are still detected.
- L80 _public property_ `public List<string> Warnings { get; }` — Warnings generated during config processing (e.g. diamond include dependencies)
- L85 _public property_ `public ILogger Logger { get; }` — Logger for config messages
- L90 _public property_ `public Uri CurrentFile => ...` — Uri of the current file
- L95 _public property_ `public string CurrentScope => ...` — Current property scope
- L97 _private* field_ `readonly Func<string, string?> _getMacroValue`
- L97 _private* field_ `readonly Func< _getMacroValue`
- L102-110 _public ctor_ `public ConfigContext(JsonSerializerOptions jsonOptions, IReadOnlyDictionary<string, IConfigSource> sources, ILogger logger)` — Constructor
- L116-122 _public method_ `public void AddProperty(string name)` — Marks a property as defined in the current file
- L129-144 _public method_ `public bool TryAddProperty(string name, [NotNullWhen(false)] out Uri? otherFile)` — Marks a property as defined in the current file
- L150-153 _public method_ `public void EnterScope(string name)` — Pushes a scope to the property stack
- L158-161 _public method_ `public void LeaveScope()` — Pops a scope from the property stack
- L166 _public method_ `public string ExpandMacros(string text)` — Expand macros in a string property
- L171-181 _private* method_ `string? GetMacroValue(string name)` — Gets the value of a named macro
- L189-205 _public method_ `public async ValueTask<IConfigFile> ReadFileAsync(Uri uri, CancellationToken cancellationToken)` — Reads the contents of a file using the appropriate source
- L213-224 _public method_ `public async ValueTask<JsonObject> ParseFileAsync(IConfigFile file, CancellationToken cancellationToken = default)` — Parses a config file as a json object
- L233-243 _public method_ `public async Task<JsonObject> PreprocessFileAsync(Uri uri, ObjectConfigNode rootNode, CancellationToken cancellationToken)` — Reads an object from a particular URL
- L252-257 _public method_ `public async Task<T> ReadAsync<T>(Uri uri, CancellationToken cancellationToken) where T : class, new()` — Reads an object from a particular URL

### `Source/Programs/Horde/HordeServer.Shared/Configuration/ConfigException.cs` (HordeServer.Shared)


#### class `HordeServer.Configuration.ConfigException`  
`public sealed class ConfigException : Exception`  
_public; L8-33_
- inherits: `Exception`
- desc: Exception thrown when reading config files
- L10 _private* field_ `readonly ConfigContext _context`
- L15 _public property_ `public IEnumerable<string> ScopeStack => ...` — Stack of properties
- L23-27 _public ctor_ `public ConfigException(ConfigContext context, string message, Exception? innerException = null) : base(message, innerException)` — Constructor
- L32 _public method_ `public ConfigContext GetContext()` — Gets the parser context when this exception was thrown. This is not exposed as a public property to avoid serializing the whole thing to Serilog.

### `Source/Programs/Horde/HordeServer.Shared/Configuration/ConfigInclude.cs` (HordeServer.Shared)


#### class `HordeServer.Configuration.ConfigInclude`  
`public class ConfigInclude`  
_public; L10-17_
- desc: Directive to merge config data from another source
- L16 _public property_ `public string Path { get; set; }` — attrs: `[Required, ConfigInclude, ConfigRelativePath]` — Path to the config data to be included. May be relative to the including file's location.

### `Source/Programs/Horde/HordeServer.Shared/Configuration/ConfigMacro.cs` (HordeServer.Shared)


#### class `HordeServer.Configuration.ConfigMacro`  
`public class ConfigMacro`  
_public; L8-19_
- desc: Declares a config macro
- L13 _public property_ `public string Name { get; set; }` — Name of the macro property
- L18 _public property_ `public string Value { get; set; }` — Value for the macro property

### `Source/Programs/Horde/HordeServer.Shared/Configuration/ConfigNode.cs` (HordeServer.Shared)


#### class `HordeServer.Configuration.ConfigIncludeAttribute`  
`public sealed class ConfigIncludeAttribute : Attribute`  
_public; L15-17_
- attrs: `[AttributeUsage(AttributeTargets.Property)]`
- inherits: `Attribute`
- desc: Attribute used to mark Uri properties that include other config files

#### class `HordeServer.Configuration.ConfigIncludeRootAttribute`  
`public sealed class ConfigIncludeRootAttribute : Attribute`  
_public; L23-25_
- attrs: `[AttributeUsage(AttributeTargets.Class)]`
- inherits: `Attribute`
- desc: Specifies that a class is the root for including other files

#### class `HordeServer.Configuration.ConfigRelativePathAttribute`  
`public sealed class ConfigRelativePathAttribute : Attribute`  
_public; L31-33_
- attrs: `[AttributeUsage(AttributeTargets.Property)]`
- inherits: `Attribute`
- desc: Attribute used to mark Uri properties that are relative to their containing file

#### class `HordeServer.Configuration.ConfigMacroScopeAttribute`  
`public sealed class ConfigMacroScopeAttribute : Attribute`  
_public; L39-41_
- attrs: `[AttributeUsage(AttributeTargets.Class)]`
- inherits: `Attribute`
- desc: Attribute used to mark Uri properties that are relative to their containing file

#### class `HordeServer.Configuration.ConfigNode`  
`public abstract class ConfigNode`  
_public; L46-152_
- desc: Node in the preprocessor parse tree
- L51 _protected property_ `protected static JsonNodeOptions DefaultJsonNodeOptions { get; }` — Default options for new json node objects
- L59 _public method_ `public abstract void ParseMacros(JsonNode? node, ConfigContext context, Dictionary<string, string> macros)` — Parses macro definitions from this object
- L68 _public method_ `public Task<JsonNode?> PreprocessAsync(JsonNode? node, ConfigContext context, CancellationToken cancellationToken)` — Preprocesses a json document
- L79 _public method_ `public abstract Task<JsonNode?> PreprocessAsync(JsonNode? node, JsonNode? existingNode, ConfigContext context, CancellationToken cancellationToken)` — Preprocesses a json document (possibly merging with an existing property)
- L89 _public method_ `public abstract Task ParseIncludesAsync(JsonNode? node, List<IConfigFile> includes, ConfigContext context, CancellationToken cancellationToken)` — Traverse the property tree starting with 'node' and process any include directives, merging the results into the given target object.
- L97-112 _public method_ `public static Uri CombinePaths(Uri baseUri, string path)` — Combine a relative path with a base URI to produce a new URI
- L117-151 _protected method_ `protected static JsonNode? ExpandMacros(JsonNode? node, ConfigContext context)` — Helper method to expand all macros within a node without performing any other processing on it

#### class `HordeServer.Configuration.ScalarConfigNode`  
`public class ScalarConfigNode : ConfigNode`  
_public; L157-215_
- inherits: `ConfigNode`
- desc: Implementation of ConfigNode for scalar types
- L162 _public property_ `public bool Include { get; set; }` — Whether this node represents an include directive
- L167 _public property_ `public bool RelativeToContainingFile { get; set; }` — Specifies that this node is a string which should be made into an absolute path using the path of the current file.
- L172-176 _public ctor_ `public ScalarConfigNode(bool include = false, bool relativePath = false)` — Constructor
- L179-180 _public method_ `public override void ParseMacros(JsonNode? jsonNode, ConfigContext context, Dictionary<string, string> macros)` — (inheritdoc)
- L183-200 _public method_ `public override Task<JsonNode?> PreprocessAsync(JsonNode? node, JsonNode? existingNode, ConfigContext context, CancellationToken cancellationToken)` — (inheritdoc)
- L203-214 _public method_ `public override async Task ParseIncludesAsync(JsonNode? node, List<IConfigFile> includes, ConfigContext context, CancellationToken cancellationToken)` — (inheritdoc)

#### class `HordeServer.Configuration.ResourceConfigNode`  
`public class ResourceConfigNode : ConfigNode`  
_public; L220-242_
- inherits: `ConfigNode`
- desc: Property containing a binary resource
- L223 _public method_ `public override Task ParseIncludesAsync(JsonNode? node, List<IConfigFile> includes, ConfigContext context, CancellationToken cancellationToken)` — (inheritdoc)
- L227-228 _public method_ `public override void ParseMacros(JsonNode? node, ConfigContext context, Dictionary<string, string> macros)` — (inheritdoc)
- L231-241 _public method_ `public override async Task<JsonNode?> PreprocessAsync(JsonNode? node, JsonNode? existingNode, ConfigContext context, CancellationToken cancellationToken)` — (inheritdoc)

#### class `HordeServer.Configuration.ArrayConfigNode`  
`public class ArrayConfigNode : ConfigNode`  
_public; L247-301_
- inherits: `ConfigNode`
- desc: Array of Json values
- L252 _public property_ `public ConfigNode ElementType { get; }` — Type of each element of the array
- L257-260 _public ctor_ `public ArrayConfigNode(ConfigNode elementType)` — Constructor
- L263-272 _public method_ `public override void ParseMacros(JsonNode? node, ConfigContext context, Dictionary<string, string> macros)` — (inheritdoc)
- L275-288 _public method_ `public override async Task<JsonNode?> PreprocessAsync(JsonNode? node, JsonNode? existingNode, ConfigContext context, CancellationToken cancellationToken)` — (inheritdoc)
- L291-300 _public method_ `public override async Task ParseIncludesAsync(JsonNode? node, List<IConfigFile> includes, ConfigContext context, CancellationToken cancellationToken)` — (inheritdoc)

#### class `HordeServer.Configuration.DictionaryConfigNode`  
`public class DictionaryConfigNode : ConfigNode`  
_public; L306-350_
- inherits: `ConfigNode`
- desc: Arbitary mapping of string values to keys
- L311 _public property_ `public ConfigNode ValueType { get; }` — Type of values in the dictionary
- L316 _public ctor_ `public DictionaryConfigNode(ConfigNode valueType)` — Constructor
- L320-321 _public method_ `public override void ParseMacros(JsonNode? jsonNode, ConfigContext context, Dictionary<string, string> macros)` — (inheritdoc)
- L324-337 _public method_ `public override async Task<JsonNode?> PreprocessAsync(JsonNode? node, JsonNode? existingNode, ConfigContext context, CancellationToken cancellationToken)` — (inheritdoc)
- L340-349 _public method_ `public override async Task ParseIncludesAsync(JsonNode? node, List<IConfigFile> includes, ConfigContext context, CancellationToken cancellationToken)` — (inheritdoc)

#### class `HordeServer.Configuration.MacroConfigNode`  
`public class MacroConfigNode : ConfigNode`  
_public; L355-374_
- inherits: `ConfigNode`
- desc: Handles macro objects
- L358 _public method_ `public override Task ParseIncludesAsync(JsonNode? node, List<IConfigFile> includes, ConfigContext context, CancellationToken cancellationToken)` — (inheritdoc)
- L362-369 _public method_ `public override void ParseMacros(JsonNode? node, ConfigContext context, Dictionary<string, string> macros)` — (inheritdoc)
- L372 _public method_ `public override Task<JsonNode?> PreprocessAsync(JsonNode? node, JsonNode? existingNode, ConfigContext context, CancellationToken cancellationToken)` — (inheritdoc)

#### class `HordeServer.Configuration.ObjectConfigNode`  
`public class ObjectConfigNode : ConfigNode`  
_public; L379-741_
- inherits: `ConfigNode`
- desc: Implementation of ConfigNode to handle class types
- L384 _public property_ `public bool IncludeRoot { get; set; }` — Whether this object should be treated as a root for nested include directies
- L389 _public property_ `public bool MacroScope { get; set; }` — Declares a new macro scope
- L394 _public property_ `public Dictionary<string, ConfigNode> Properties { get; }` — Properties within this object
- L399-402 _public ctor_ `public ObjectConfigNode(bool isIncludeRoot, bool isMacroScope) : this(isIncludeRoot, isMacroScope, Array.Empty<KeyValuePair<string, ConfigNode>>())` — Constructor
- L407-412 _public ctor_ `public ObjectConfigNode(bool isIncludeRoot, bool isMacroScope, IEnumerable<KeyValuePair<string, ConfigNode>> properties)` — Constructor
- L418-420 _public ctor_ `public ObjectConfigNode(Type type) : this(type, new Dictionary<Type, ConfigNode>())` — Constructor
- L422-444 _private* ctor_ `ObjectConfigNode(Type type, Dictionary<Type, ConfigNode> recursiveTypes)`
- L446 _private* method_ `bool IsDefault()`
- L449-466 _private* method_ `static ConfigNode? CreateTypeForProperty(PropertyInfo propertyInfo, Dictionary<Type, ConfigNode> recursiveTypes)`
- L468-499 _private* method_ `static ConfigNode? CreateType(Type type, Dictionary<Type, ConfigNode> recursiveTypes)`
- L507 _public method_ `public async Task<JsonObject> PreprocessAsync(JsonObject obj, ConfigContext context, CancellationToken cancellationToken)` — Preprocesses an object
- L511-526 _public method_ `public override void ParseMacros(JsonNode? jsonNode, ConfigContext context, Dictionary<string, string> macros)` — (inheritdoc)
- L529-632 _public method_ `public override async Task<JsonNode?> PreprocessAsync(JsonNode? node, JsonNode? existingNode, ConfigContext context, CancellationToken cancellationToken)` — (inheritdoc)
- L634-670 _private* method_ `static JsonNode? Merge(JsonNode? source, JsonNode? target)`
- L673-679 _public method_ `public override async Task ParseIncludesAsync(JsonNode? node, List<IConfigFile> includes, ConfigContext context, CancellationToken cancellationToken)` — (inheritdoc)
- L681-690 _private* method_ `async Task ParseIncludesInternalAsync(JsonObject obj, List<IConfigFile> includes, ConfigContext context, CancellationToken cancellationToken)`
- L697-718 _public method_ `public void AddChildNode(string path, ConfigNode node)` — Adds a new node at a given path
- L725-740 _public method_ `public bool TryGetChildNode(string path, [NotNullWhen(true)] out ConfigNode? node)` — Tries to get a node by path

### `Source/Programs/Horde/HordeServer.Shared/Configuration/ConfigObject.cs` (HordeServer.Shared)


#### enum `HordeServer.Configuration.ConfigMergeStrategy`  
`public enum ConfigMergeStrategy`  
_public; L13-29_
- desc: Possible methods for merging config values
- L18 _public* enumerator_ `Default` — Default strategy; replace with the base value if the current value is null
- L23 _public* enumerator_ `Append` — Append the contents of this list to the base list
- L28 _public* enumerator_ `Recursive` — Recursively merge object properties

#### class `HordeServer.Configuration.ConfigMergeStrategyAttribute`  
`public sealed class ConfigMergeStrategyAttribute : Attribute`  
_public; L35-46_
- attrs: `[AttributeUsage(AttributeTargets.Property)]`
- inherits: `Attribute`
- desc: Attribute used to mark object properties whose child properties should be merged individually
- L40 _public property_ `public ConfigMergeStrategy Strategy { get; }` — Strategy for merging this property
- L45 _public ctor_ `public ConfigMergeStrategyAttribute(ConfigMergeStrategy strategy)` — Constructor

#### class `HordeServer.Configuration.ConfigObject`  
`public static class ConfigObject`  
_public; L51-209_
- desc: Helper methods for merging default values
- L58-147 _public method_ `public static void MergeDefaults<TKey, TValue>(IEnumerable<(TKey Key, TKey? BaseKey, TValue Value)> objects, ILogger? logger = null) where TKey : notnull where TValue : class` — Merges any unassigned properties from the source object to the target
- L154-157 _public method_ `public static void MergeDefaults<T>(T target, T source) where T : class` — Merges any unassigned properties from the source object to the target
- L165-208 _public method_ `public static void MergeDefaults(Type type, object target, object source)` — Merges any unassigned properties from the source object to the target

### `Source/Programs/Horde/HordeServer.Shared/Configuration/ConfigResource.cs` (HordeServer.Shared)


#### class `HordeServer.Configuration.ConfigResource`  
`public sealed class ConfigResource`  
_public; L14-26_
- attrs: `[JsonSchemaString] [JsonConverter(typeof(ConfigResourceSerializer))]`
- desc: Special resource type in configuration files which stores data from an external source
- L20 _public property_ `public string? Path { get; set; }` — attrs: `[ConfigRelativePath]` — Path to the resource
- L25 _public property_ `public ReadOnlyMemory<byte> Data { get; set; }` — Data for the resource. This will be stored externally to the config data.

#### class `HordeServer.Configuration.ConfigResourceSerializer`  
`public class ConfigResourceSerializer : JsonConverter<ConfigResource>`  
_public; L31-97_
- inherits: `JsonConverter<ConfigResource>`
- desc: Serializer for ConfigResource objects
- L33 _private* field_ `readonly bool _withData`
- L38-39 _public ctor_ `public ConfigResourceSerializer() : this(true)` — Explicit default constructor (cannot use default argument with JsonSerializer)
- L45 _public ctor_ `public ConfigResourceSerializer(bool withData)` — Constructor
- L49-80 _public method_ `public override ConfigResource Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — (inheritdoc)
- L83-96 _public method_ `public override void Write(Utf8JsonWriter writer, ConfigResource resource, JsonSerializerOptions options)` — (inheritdoc)

### `Source/Programs/Horde/HordeServer.Shared/Configuration/IChangelistFileReader.cs` (HordeServer.Shared)


#### interface `HordeServer.Configuration.IChangelistFileReader`  
`public interface IChangelistFileReader`  
_public; L8-18_
- desc: Reads files from a shelved Perforce changelist for config validation and diffing.
- L17 _public* method_ `Task<Dictionary<Uri, byte[]>> ReadChangelistFilesAsync(int changelist, string? cluster, CancellationToken cancellationToken)` — Reads all config-like files from a shelved changelist.

#### class `HordeServer.Configuration.ChangelistNotFoundException`  
`public class ChangelistNotFoundException : Exception`  
_public; L23-31_
- inherits: `Exception`
- desc: Exception thrown when a changelist cannot be found or described.
- L28-30 _public ctor_ `public ChangelistNotFoundException(string message) : base(message)` — Constructor

### `Source/Programs/Horde/HordeServer.Shared/Configuration/IConfigFile.cs` (HordeServer.Shared)


#### interface `HordeServer.Configuration.IConfigFile`  
`public interface IConfigFile`  
_public; L10-33_
- desc: Accessor for a specific revision of a config file. Provides metadata about the current revision, and allows reading its data.
- L15 _public* property_ `Uri Uri { get; }` — URI of the config file
- L20 _public* property_ `string Revision { get; }` — String used to identify a specific version of the config data. Used for ordinal comparisons, otherwise opaque.
- L25 _public* property_ `IUser? Author { get; }` — Author of this revision, if known
- L32 _public* method_ `ValueTask<ReadOnlyMemory<byte>> ReadAsync(CancellationToken cancellationToken)` — Reads data for the config file

#### class `HordeServer.Configuration.ConfigFileExtensions`  
`public static class ConfigFileExtensions`  
_public; L38-59_
- desc: Extension methods for config files
- L44-58 _public method_ `public static string GetUserFormattedPath(this IConfigFile file)` — Formats a the URI for a config file in a format that is more readable for users

### `Source/Programs/Horde/HordeServer.Shared/Configuration/IConfigService.cs` (HordeServer.Shared)


#### interface `HordeServer.Configuration.IConfigService`  
`public interface IConfigService`  
_public; L10-30_
- desc: Interface for the config service
- L15 _public* event_ `event Action<ConfigUpdateInfo>? OnConfigUpdate` — Event for notifications that the config has been updated
- L20 _public* method_ `Task<ConfigValidationResult> ValidateAsync(Dictionary<Uri, byte[]> files, CancellationToken cancellationToken)` — Validate a new set of config files. Parses and runs PostLoad methods on them.
- L29 _public* method_ `Task<ConfigResolveResult> ResolveWithOverridesAsync(Dictionary<Uri, byte[]> files, CancellationToken cancellationToken)` — Resolve a set of config file overrides through the full pipeline (includes, macros, inheritance) and return the resulting GlobalConfig. Unread files are returned as warnings, not errors.

#### class `HordeServer.Configuration.ConfigValidationResult`  
`public class ConfigValidationResult`  
_public; L35-51_
- desc: Result from validating config files
- L40 _public property_ `public bool Success => ...` — Whether validation succeeded
- L45 _public property_ `public string? Error { get; set; }` — Error message if validation failed (null on success)
- L50 _public property_ `public List<string> Warnings { get; set; }` — Warnings generated during config processing (e.g. diamond include dependencies)

#### class `HordeServer.Configuration.ConfigResolveResult`  
`public class ConfigResolveResult`  
_public; L56-83_
- desc: Result from resolving config with overrides
- L61 _public property_ `public object? Config { get; set; }` — The resolved global config (null if validation failed)
- L67 _public property_ `public IDictionary<PluginName, IPluginConfig>? Plugins { get; set; }` — The resolved plugin configs (null if validation failed). Plugins can use their GetXxxConfig() extension methods on this.
- L72 _public property_ `public string? Error { get; set; }` — Error message if config parsing failed (null on success)
- L77 _public property_ `public List<Uri> UnreadFiles { get; set; }` — Config file URIs from the overrides that were not consumed by the pipeline
- L82 _public property_ `public List<string> Warnings { get; set; }` — Warnings generated during config processing (e.g. diamond include dependencies)

### `Source/Programs/Horde/HordeServer.Shared/Configuration/IConfigSource.cs` (HordeServer.Shared)


#### record `HordeServer.Configuration.ConfigUpdateInfo`  
`public record class ConfigUpdateInfo(List<string> Status, HashSet<UserId> Authors, Exception? Exception)`  
_public; L13-13_
- desc: Information about the updated config

#### interface `HordeServer.Configuration.IConfigSource`  
`public interface IConfigSource`  
_public; L18-46_
- desc: Source for reading config files
- L23 _public* property_ `string Scheme { get; }` — URI scheme for this config source
- L28 _public* property_ `TimeSpan UpdateInterval { get; }` — Update interval for this source
- L36 _public* method_ `Task<IConfigFile[]> GetFilesAsync(Uri[] uris, CancellationToken cancellationToken)` — Reads a config file from this source
- L45 _public* method_ `Task GetUpdateInfoAsync(IReadOnlyDictionary<Uri, string> files, IReadOnlyDictionary<Uri, string>? prevFiles, ConfigUpdateInfo updateInfo, CancellationToken cancellationToken)` — Gets summary infomration for sending notifications

#### class `HordeServer.Configuration.ConfigSource`  
`public static class ConfigSource`  
_public; L51-65_
- desc: Extension methods for IConfigSource
- L60-64 _public method_ `public static async Task<IConfigFile> GetAsync(this IConfigSource source, Uri uri, CancellationToken cancellationToken)` — Gets a single config file from a source

#### class `HordeServer.Configuration.InMemoryConfigSource`  
`public sealed class InMemoryConfigSource : IConfigSource`  
_public; L70-131_
- inherits: `IConfigSource`
- desc: In-memory config file source
- L89 _private* field_ `readonly Dictionary<Uri, ConfigFileRevisionImpl> _files = ...`
- L89 _private* field_ `readonly Dictionary< _files = new Dictionary<Uri, ConfigFileRevisionImpl>()`
- L94 _public const_ `public const string Scheme = "memory"` — Name of the scheme for this source
- L97 _private* property_ `string IConfigSource.Scheme => ...` — (inheritdoc)
- L100 _public property_ `public TimeSpan UpdateInterval => ...` — (inheritdoc)
- L107-110 _public method_ `public void Add(Uri path, ReadOnlyMemory<byte> data)` — Manually adds a new config file
- L113-126 _public method_ `public Task<IConfigFile[]> GetFilesAsync(Uri[] uris, CancellationToken cancellationToken)` — (inheritdoc)
- L129 _public method_ `public Task GetUpdateInfoAsync(IReadOnlyDictionary<Uri, string> files, IReadOnlyDictionary<Uri, string>? prevFiles, ConfigUpdateInfo updateInfo, CancellationToken cancellationToken)` — (inheritdoc)

#### class `HordeServer.Configuration.InMemoryConfigSource.ConfigFileRevisionImpl`  
`class ConfigFileRevisionImpl : IConfigFile`  
_private*; L72-87_
- inherits: `IConfigFile`
- L74 _public property_ `public Uri Uri { get; }`
- L75 _public property_ `public string Revision { get; }`
- L76 _public property_ `public ReadOnlyMemory<byte> Data { get; }`
- L77 _public property_ `public IUser? Author => ...`
- L79-84 _public ctor_ `public ConfigFileRevisionImpl(Uri uri, string version, ReadOnlyMemory<byte> data)`
- L86 _public method_ `public ValueTask<ReadOnlyMemory<byte>> ReadAsync(CancellationToken cancellationToken)`

#### class `HordeServer.Configuration.FileConfigSource`  
`public sealed class FileConfigSource : IConfigSource`  
_public; L136-234_
- inherits: `IConfigSource`
- desc: Config file source which reads from the filesystem
- L160 _public const_ `public const string Scheme = "file"` — Name of the scheme for this source
- L163 _private* property_ `string IConfigSource.Scheme => ...` — (inheritdoc)
- L166 _public property_ `public TimeSpan UpdateInterval => ...` — (inheritdoc)
- L168 _private* field_ `readonly DirectoryReference _baseDir`
- L169 _private* field_ `readonly ConcurrentDictionary<FileReference, ConfigFileImpl> _files = ...`
- L169 _private* field_ `readonly ConcurrentDictionary< _files = new ConcurrentDictionary<FileReference, ConfigFileImpl>()`
- L174-177 _public ctor_ `public FileConfigSource() : this(DirectoryReference.GetCurrentDirectory())` — Constructor
- L183-186 _public ctor_ `public FileConfigSource(DirectoryReference baseDir)` — Constructor
- L189-229 _public method_ `public async Task<IConfigFile[]> GetFilesAsync(Uri[] uris, CancellationToken cancellationToken)` — (inheritdoc)
- L232 _public method_ `public Task GetUpdateInfoAsync(IReadOnlyDictionary<Uri, string> files, IReadOnlyDictionary<Uri, string>? prevFiles, ConfigUpdateInfo updateInfo, CancellationToken cancellationToken)` — (inheritdoc)

#### class `HordeServer.Configuration.FileConfigSource.ConfigFileImpl`  
`class ConfigFileImpl : IConfigFile`  
_private*; L138-155_
- inherits: `IConfigFile`
- L140 _public property_ `public Uri Uri { get; }`
- L141 _public property_ `public string Revision { get; }`
- L142 _public property_ `public DateTime LastWriteTimeUtc { get; }`
- L143 _public property_ `public ReadOnlyMemory<byte> Data { get; }`
- L144 _public property_ `public IUser? Author => ...`
- L146-152 _public ctor_ `public ConfigFileImpl(Uri uri, DateTime lastWriteTimeUtc, ReadOnlyMemory<byte> data)`
- L154 _public method_ `public ValueTask<ReadOnlyMemory<byte>> ReadAsync(CancellationToken cancellationToken)`

### `Source/Programs/Horde/HordeServer.Shared/Configuration/ResolveSecretAttribute.cs` (HordeServer.Shared)


#### class `HordeServer.Configuration.ResolveSecretAttribute`  
`public sealed class ResolveSecretAttribute : Attribute`  
_public; L9-9_
- attrs: `[AttributeUsage(AttributeTargets.Property)]`
- inherits: `Attribute`
- desc: Convert a string representation of a secret to a concrete value during config updates

### `Source/Programs/Horde/HordeServer.Shared/IServerInfo.cs` (HordeServer.Shared)


#### enum `HordeServer.RunMode`  
`public enum RunMode`  
_public; L13-34_
- desc: Type of run mode this process should use. Each carry different types of workloads. More than one mode can be active. But not all modes are not guaranteed to be compatible with each other and will raise an error if combined in such a way.
- L18 _public* enumerator_ `None` — Default no-op value (ASP.NET config will default to this for enums that cannot be parsed)
- L25 _public* enumerator_ `Server` — Handle and respond to incoming external requests, such as HTTP REST and gRPC calls. These requests are time-sensitive and short-lived, typically less than 5 secs. If processes handling requests are unavailable, it will be very visible for users.
- L33 _public* enumerator_ `Worker` — Run non-request facing workloads. Such as background services, processing queues, running work based on timers etc. Short periods of downtime or high CPU usage due to bursts are fine for this mode. No user requests will be impacted directly. If auto-scaling is used, a much more aggressive policy can be applied (tighter process packing, higher avg CPU usage).

#### interface `HordeServer.IServerInfo`  
`public interface IServerInfo`  
_public; L39-97_
- desc: Provides access to server deployment information
- L44 _public* property_ `SemVer Version { get; }` — Current version of the server
- L49 _public* property_ `string Environment { get; }` — Environment that the server is deployed to
- L54 _public* property_ `string SessionId { get; }` — Unique session id
- L59 _public* property_ `DirectoryReference AppDir { get; }` — Directory containing the server executable
- L64 _public* property_ `DirectoryReference DataDir { get; }` — Directory to store server data files
- L69 _public* property_ `IConfiguration Configuration { get; }` — Global configuration settings
- L74 _public* property_ `bool ReadOnlyMode { get; }` — Whether the server is running in read-only mode
- L79 _public* property_ `bool EnableDebugEndpoints { get; }` — Whether to enable endpoints which are for debugging purposes
- L84 _public* property_ `Uri ServerUrl { get; }` — Url to use for generating links back to the server
- L89 _public* property_ `Uri DashboardUrl { get; }` — Url to use for generating links back to the dashboard.
- L96 _public* method_ `bool IsRunModeActive(RunMode mode)` — Helper method to check if this process has activated the given mode

### `Source/Programs/Horde/HordeServer.Shared/IServerStartup.cs` (HordeServer.Shared)


#### interface `HordeServer.IServerStartup`  
`public interface IServerStartup`  
_public; L10-16_
- desc: Interface for the main server startup class. Can be used by commands that want to instantiate server services.
- L15 _public* method_ `void ConfigureServices(IServiceCollection services)` — Configure services for the server

### `Source/Programs/Horde/HordeServer.Shared/Plugins/IPluginConfig.cs` (HordeServer.Shared)


#### interface `HordeServer.Plugins.IPluginConfig`  
`public interface IPluginConfig`  
_public; L11-18_
- desc: Interface for plugin extensions to the global config object
- L17 _public* method_ `void PostLoad(PluginConfigOptions configOptions)` — Called to fixup a plugin's configuration after deserialization

#### record `HordeServer.Plugins.PluginConfigOptions`  
`public record class PluginConfigOptions(ConfigVersion Version, IEnumerable<IPluginConfig> Plugins, AclConfig ParentAcl, ILogger? Logger = null)`  
_public; L23-23_
- desc: Options passed to IPluginConfig.PostLoad(PluginConfigOptions)

#### class `HordeServer.Plugins.EmptyPluginConfig`  
`public sealed class EmptyPluginConfig : IPluginConfig`  
_public; L28-33_
- inherits: `IPluginConfig`
- desc: Empty implementation of IPluginConfig
- L31-32 _public method_ `public void PostLoad(PluginConfigOptions configOptions)` — (inheritdoc)

### `Source/Programs/Horde/HordeServer.Shared/Plugins/IPluginDashboardAcls.cs` (HordeServer.Shared)


#### interface `HordeServer.Plugins.IPluginDashboardAcls`  
`public interface IPluginDashboardAcls`  
_public; L14-31_
- desc: Interface for plugins to declare ACL actions relevant to dashboard visibility. Plugins implementing this interface can specify what ACL actions control access to their dashboard features, and the server will return which actions the current user has when returning plugin information.
- L22 _public* method_ `AclAction[] GetDashboardAclActions()` — Gets the ACL actions that are relevant for dashboard visibility for this plugin. These actions will be checked against the current user and returned in the server info response so the dashboard can filter plugins and mount points.
- L30 _public* method_ `bool AuthorizeDashboardAction(AclAction action, ClaimsPrincipal user)` — Checks if the given user has the specified ACL action for this plugin

### `Source/Programs/Horde/HordeServer.Shared/Plugins/IPluginResponseFilter.cs` (HordeServer.Shared)


#### interface `HordeServer.Plugins.IPluginResponseFilter`  
`public interface IPluginResponseFilter`  
_public; L10-16_
- desc: Interface allowing plugins to modify API responses
- L15 _public method_ `public void Apply(HttpContext context, object response)` — Apply any changes to the given response

### `Source/Programs/Horde/HordeServer.Shared/Plugins/IPluginStartup.cs` (HordeServer.Shared)


#### interface `HordeServer.Plugins.IPluginStartup`  
`public interface IPluginStartup`  
_public; L11-24_
- desc: Interface for modules that can extend the services known by Horde
- L17 _public* method_ `void Configure(IApplicationBuilder app)` — Configure the application
- L23 _public* method_ `void ConfigureServices(IServiceCollection serviceCollection)` — Configure the services provided by the plugin

### `Source/Programs/Horde/HordeServer.Shared/Plugins/PluginAttribute.cs` (HordeServer.Shared)


#### class `HordeServer.Plugins.PluginAttribute`  
`public sealed class PluginAttribute : Attribute`  
_public; L10-47_
- attrs: `[AttributeUsage(AttributeTargets.Class)]`
- inherits: `Attribute`
- desc: Attribute used to identify types that should be constructed for the given plugin name. Should be attached to a public class implementing IPluginStartup.
- L15 _public property_ `public string Name { get; }` — Name of the plugin
- L20 _public property_ `public bool EnabledByDefault { get; set; }` — Whether the plugin should be enabled by default
- L25 _public property_ `public string[] DependsOn { get; set; }` — Other plugins that this plugin depends on
- L31 _public property_ `public Type? ServerConfigType { get; set; }` — Type containing server settings for this plugin. Will be injected into a Microsoft.Extensions.Options.IOptions{TOptions} object in the service container, as well as (optionally) the constructor for the the concrete plugin startup object.
- L40 _public property_ `public Type? GlobalConfigType { get; set; }` — Type containing global settings for this plugin. Must implement the IPluginConfig interface. Standard Microsoft.Extensions.Options.IOptions{TOptions} and Microsoft.Extensions.Options.IOptionsMonitor{TOptions} objects will be registered for this type in the service container.
- L45 _public ctor_ `public PluginAttribute(string name)` — Constructor

### `Source/Programs/Horde/HordeServer.Shared/Plugins/PluginName.cs` (HordeServer.Shared)


#### record struct `HordeServer.Plugins.PluginName`  
`public record struct PluginName(StringId Id)`  
_public; L17-29_
- attrs: `[LogValueType] [JsonSchemaString] [TypeConverter(typeof(StringIdTypeConverter<PluginName, PluginNameStringIdConverter>))] [StringIdConverter(typeof(PluginNameStringIdConverter))]`
- desc: Name of a plugin
- L23-25 _public ctor_ `public PluginName(string name) : this(new StringId(name))` — Constructor
- L28 _public method_ `public override string ToString()` — (inheritdoc)

#### class `HordeServer.Plugins.PluginNameStringIdConverter`  
`class PluginNameStringIdConverter : StringIdConverter<PluginName>`  
_internal*; L34-43_
- inherits: `StringIdConverter<PluginName>`
- desc: Converter from PluginName objects to regular StringId types
- L37 _public method_ `public override PluginName FromStringId(StringId id)` — (inheritdoc)
- L41 _public method_ `public override StringId ToStringId(PluginName value)` — (inheritdoc)

### `Source/Programs/Horde/HordeServer.Shared/Plugins/PluginServerConfig.cs` (HordeServer.Shared)


#### class `HordeServer.Plugins.PluginServerConfig`  
`public class PluginServerConfig`  
_public; L8-14_
- desc: Base class for plugin server config objects
- L13 _public property_ `public bool? Enabled { get; set; }` — Whether the plugin should be enabled or not

### `Source/Programs/Horde/HordeServer.Shared/RCA/IRcaEnqueuer.cs` (HordeServer.Shared)


#### interface `HordeServer.RCA.IRcaEnqueuer`  
`public interface IRcaEnqueuer`  
_public; L12-22_
- desc: Interface for enqueuing RCA processing requests. Implementations persist the request and process it asynchronously.
- L21 _public* method_ `Task EnqueueAsync(int issueId, StreamId streamId, WorkflowId? workflowId, CancellationToken cancellationToken)` — Enqueue an RCA processing request for the given issue.

### `Source/Programs/Horde/HordeServer.Shared/RCA/IRcaNotifier.cs` (HordeServer.Shared)


#### record `HordeServer.RCA.RcaRunnerUp`  
`public record RcaRunnerUp(CommitId Commit, string? BriefReason)`  
_public; L10-10_
- desc: A runner-up suspect from an RCA analysis

#### record `HordeServer.RCA.RcaResult`  
`public record RcaResult(CommitId? CulpritCommitId, string? Reason, double Confidence, string? Summary, string? Category, IReadOnlyList<RcaRunnerUp>? RunnerUps)`  
_public; L15-15_
- desc: Result of an auto-RCA analysis

#### interface `HordeServer.RCA.IRcaNotifier`  
`public interface IRcaNotifier`  
_public; L20-29_
- desc: Interface for notifying about completed RCA results (e.g., posting to Slack threads).
- L28 _public* method_ `Task NotifyRcaCompleteAsync(int issueId, RcaResult result, CancellationToken cancellationToken)` — Notify that RCA analysis has completed for an issue

### `Source/Programs/Horde/HordeServer.Shared/RCA/IRcaProcessor.cs` (HordeServer.Shared)


#### interface `HordeServer.RCA.IRcaProcessor`  
`public interface IRcaProcessor`  
_public; L12-23_
- desc: Interface for processing Root Cause Analysis on issues. Implementations may use LLMs, ML models, or other techniques.
- L22 _public* method_ `Task ProcessRcaAsync(int issueId, StreamId streamId, WorkflowId? workflowId, CancellationToken cancellationToken)` — Process RCA for the given issue if eligible. Implementations should check workflow eligibility internally and return early if not eligible.

### `Source/Programs/Horde/HordeServer.Shared/Server/AdminAclAction.cs` (HordeServer.Shared)


#### class `HordeServer.Server.AdminAclAction`  
`public static class AdminAclAction`  
_public; L10-21_
- desc: ACL actions for admin operations
- L15 _public property_ `public static AclAction AdminRead { get; }` — Ability to read any data from the server. Always inherited.
- L20 _public property_ `public static AclAction AdminWrite { get; }` — Ability to write any data to the server.

### `Source/Programs/Horde/HordeServer.Shared/Server/IAgentVersionProvider.cs` (HordeServer.Shared)


#### interface `HordeServer.Server.IAgentVersionProvider`  
`public interface IAgentVersionProvider`  
_public; L8-14_
- desc: Allows subsystems to advertise the version of bundled tools via the /server/info endpoint
- L13 _public* method_ `Task<string?> GetAsync(CancellationToken cancellationToken = default)` — Returns the version number of the Horde agent

### `Source/Programs/Horde/HordeServer.Shared/Server/IDowntimeService.cs` (HordeServer.Shared)


#### interface `HordeServer.Server.IDowntimeService`  
`public interface IDowntimeService`  
_public; L8-17_
- desc: Interface for a service which keeps track of whether we're during downtime
- L13-16 _public property_ `public bool IsDowntimeActive { get; }` — Returns true if downtime is currently active

### `Source/Programs/Horde/HordeServer.Shared/Server/IHealthMonitor.cs` (HordeServer.Shared)


#### interface `HordeServer.Server.IHealthMonitor`  
`public interface IHealthMonitor`  
_public; L10-21_
- desc: Allows reporting the health of a subsystem
- L15 _public* method_ `void SetName(string name)` — Sets the name used for reporting status of this service
- L20 _public* method_ `Task UpdateAsync(HealthStatus result, string? message = null, DateTimeOffset? timestamp = null)` — Updates the current health of a system

#### interface `HordeServer.Server.IHealthMonitor`  
`public interface IHealthMonitor<T> : IHealthMonitor`  
_public; L27-29_
- inherits: `IHealthMonitor`
- desc: Typed implementation of IHealthMonitor

### `Source/Programs/Horde/HordeServer.Shared/Server/ILifetimeService.cs` (HordeServer.Shared)


#### interface `HordeServer.Server.ILifetimeService`  
`public interface ILifetimeService`  
_public; L8-19_
- desc: Interface for the server lifetime service
- L13 _public* property_ `bool IsStopping { get; }` — Returns true if the server is stopping
- L18 _public* property_ `Task StoppingTask { get; }` — Gets an awaitable task for the server stopping

### `Source/Programs/Horde/HordeServer.Shared/Server/IMongoService.cs` (HordeServer.Shared)


#### interface `HordeServer.Server.IMongoService`  
`public interface IMongoService : IHealthCheck`  
_public; L12-96_
- inherits: `IHealthCheck`
- desc: Interface for the Horde MongoDB instance
- L17 _public* property_ `IMongoDatabase Database { get; }` — The database instance
- L22 _public property_ `public bool ReadOnlyMode { get; }` — Access the database in a read-only mode (don't create indices or modify content)
- L28 _public* method_ `MongoClient GetClient()` — Get the MongoDB client
- L36 _public* method_ `IMongoCollection<T> GetCollection<T>(string name)` — Get a MongoDB collection from database
- L46 _public* method_ `IMongoCollection<T> GetCollection<T>(string name, Func<IndexKeysDefinitionBuilder<T>, IndexKeysDefinition<T>> keysFunc, bool unique = false)` — Get a MongoDB collection from database with a single index
- L55 _public* method_ `IMongoCollection<T> GetCollection<T>(string name, IEnumerable<MongoIndex<T>> indexes)` — Get a MongoDB collection from database
- L61 _public* method_ `Task<T> GetSingletonAsync<T>(CancellationToken cancellationToken) where T : SingletonBase, new()` — Gets a singleton document by id
- L69 _public* method_ `Task<T> GetSingletonAsync<T>(Func<T> constructor, CancellationToken cancellationToken) where T : SingletonBase, new()` — Gets a singleton document by id
- L78 _public* method_ `Task UpdateSingletonAsync<T>(Action<T> updater, CancellationToken cancellationToken) where T : SingletonBase, new()` — Updates a singleton
- L87 _public* method_ `Task UpdateSingletonAsync<T>(Func<T, bool> updater, CancellationToken cancellationToken) where T : SingletonBase, new()` — Updates a singleton
- L95 _public* method_ `Task<bool> TryUpdateSingletonAsync<T>(T singletonObject, CancellationToken cancellationToken) where T : SingletonBase` — Attempts to update a singleton object

### `Source/Programs/Horde/HordeServer.Shared/Server/IRedisService.cs` (HordeServer.Shared)


#### interface `HordeServer.Server.IRedisService`  
`public interface IRedisService : IHealthCheck`  
_public; L12-23_
- inherits: `IHealthCheck`
- desc: Provides access to a Redis database
- L17 _public* property_ `bool ReadOnlyMode { get; }` — Flag for whether the connection is read-only
- L22 _public property_ `public RedisConnectionPool ConnectionPool { get; }` — Connection pool

#### class `HordeServer.Server.RedisServiceExtensions`  
`public static class RedisServiceExtensions`  
_public; L28-101_
- desc: Extension methods for IRedisService
- L35 _public method_ `public static IConnectionMultiplexer GetConnection(this IRedisService redisService)` — Get the least-loaded Redis connection from the pool Don't store the returned object and try to resolve this as late as possible to ensure load is balanced.
- L43 _public method_ `public static IDatabase GetDatabase(this IRedisService redisService)` — Get the least-loaded Redis database from the connection pool Don't store the returned object and try to resolve this as late as possible to ensure load is balanced.
- L53 _public method_ `public static Task PublishAsync(this IRedisService redisService, RedisChannel channel, RedisValue message, CommandFlags flags = CommandFlags.None)` — Publish a message to a channel
- L64 _public method_ `public static Task PublishAsync<T>(this IRedisService redisService, RedisChannel<T> channel, T message, CommandFlags flags = CommandFlags.None)` — Publish a message to a channel
- L68 _public method_ `public static Task<RedisSubscription> SubscribeAsync(this IRedisService redisService, RedisChannel channel, Action<RedisValue> callback)` — (inheritdoc)
- L72 _public method_ `public static Task<RedisSubscription> SubscribeAsync<T>(this IRedisService redisService, RedisChannel<T> channel, Action<T> callback)` — (inheritdoc)
- L82-86 _public method_ `public static async Task<RedisSubscription> SubscribeAsync(this IRedisService redisService, RedisChannel channel, Action<RedisChannel, RedisValue> callback)` — Subscribe to notifications on a channel
- L96-100 _public method_ `public static async Task<RedisSubscription> SubscribeAsync<T>(this IRedisService redisService, RedisChannel<T> channel, Action<RedisChannel<T>, T> callback)` — Subscribe to notifications on a channel

### `Source/Programs/Horde/HordeServer.Shared/Server/MongoIndex.cs` (HordeServer.Shared)


#### class `HordeServer.Server.MongoIndex`  
`public class MongoIndex : IEquatable<MongoIndex>`  
_public; L16-119_
- attrs: `[DebuggerDisplay("{Name}")]`
- inherits: `IEquatable<MongoIndex>`
- desc: Constrained set of parameters for building a mongo index
- L22 _public property_ `public string Name { get; set; }` — attrs: `[BsonElement("name"), BsonRequired]` — Name of the index
- L28 _public property_ `public BsonDocument KeysDocument { get; set; }` — attrs: `[BsonElement("key"), BsonRequired]` — Keys for the index
- L34 _public property_ `public bool Unique { get; set; }` — attrs: `[BsonElement("unique")]` — The index should be unique
- L40 _public property_ `public bool Sparse { get; set; }` — attrs: `[BsonElement("sparse")]` — Whether to create a sparse index
- L46-50 _private ctor_ `private MongoIndex()` — attrs: `[BsonConstructor]` — Constructor
- L59-65 _public ctor_ `public MongoIndex(string? name, BsonDocument keysDocument, bool unique, bool sparse)` — Constructor
- L73-76 _public method_ `public static MongoIndex<T> Create<T>(Func<IndexKeysDefinitionBuilder<T>, IndexKeysDefinition<T>> keysFunc, bool unique = false, bool sparse = false)` — Constructor
- L85-88 _public method_ `public static MongoIndex<T> Create<T>(string name, Func<IndexKeysDefinitionBuilder<T>, IndexKeysDefinition<T>> keysFunc, bool unique = false, bool sparse = false)` — Constructor
- L91 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L94 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L97 _public method_ `public bool Equals(MongoIndex? other)` — (inheritdoc)
- L104-118 _protected method_ `protected static string GetDefaultName(BsonDocument keys)` — Gets the default name for an index based on its keys

#### class `HordeServer.Server.MongoIndex`  
`public class MongoIndex<T> : MongoIndex`  
_public; L125-145_
- inherits: `MongoIndex`
- desc: Strongly typed index document
- L131 _public property_ `public IndexKeysDefinition<T> Keys { get; }` — attrs: `[BsonIgnore]` — Keys for the index
- L140-144 _public ctor_ `public MongoIndex(string? name, IndexKeysDefinition<T> keys, bool unique, bool sparse) : base(name, keys.Render(BsonSerializer.LookupSerializer<T>(), BsonSerializer.SerializerRegistry), unique, sparse)` — Constructor

#### class `HordeServer.Server.MongoIndexExtensions`  
`public static class MongoIndexExtensions`  
_public; L150-167_
- desc: Extension methods for MongoIndex{T}
- L155-158 _public method_ `public static void Add<T>(this List<MongoIndex<T>> list, Func<IndexKeysDefinitionBuilder<T>, IndexKeysDefinition<T>> keyFunc, bool unique = false, bool sparse = false)` — Adds a new index to the collection
- L163-166 _public method_ `public static void Add<T>(this List<MongoIndex<T>> list, string name, Func<IndexKeysDefinitionBuilder<T>, IndexKeysDefinition<T>> keyFunc, bool unique = false, bool sparse = false)` — Adds a new index to the collection

### `Source/Programs/Horde/HordeServer.Shared/Server/MongoMigration.cs` (HordeServer.Shared)


#### class `HordeServer.Server.MongoMigrationAttribute`  
`public sealed class MongoMigrationAttribute(string plugin, int version, string name, bool autoLoad = true) : Attribute`  
_public; L12-35_
- attrs: `[AttributeUsage(AttributeTargets.Class)]`
- desc: Attribute to decorate MongoDB migration classes with metadata
- L17 _public property_ `public string Plugin { get; }` — Plugin identifier for this migration.
- L23 _public property_ `public int Version { get; }` — Gets the version number for this migration and plugin Must be monotonically increasing and unique within in plugin namespace
- L28 _public property_ `public string Name { get; }` — Descriptive name of the change this migration performs
- L34 _public property_ `public bool AutoLoad { get; }` — Whether migration should be detected and loaded during full reflection scans of available migrations If set to false, the migration must manually be registered with a migrator

#### record `HordeServer.Server.MigrationContext`  
`public record MigrationContext(IMongoService MongoService, ILogger Logger)`  
_public; L40-46_
- desc: Provides context and services needed for executing migrations
- L45 _public property_ `public IMongoDatabase Database => ...` — Shorthand for accessing the MongoDB database object

#### interface `HordeServer.Server.IMongoMigration`  
`public interface IMongoMigration`  
_public; L52-63_
- desc: Defines operations for upgrading and downgrading database schemas Implemented by classes providing a migration
- L57 _public method_ `public Task UpAsync(MigrationContext context, CancellationToken token)` — Upgrade the database schema version
- L62 _public method_ `public Task DownAsync(MigrationContext context, CancellationToken token)` — Downgrade the database schema version

### `Source/Programs/Horde/HordeServer.Shared/Server/ServerAclAction.cs` (HordeServer.Shared)


#### class `HordeServer.Server.ServerAclAction`  
`public static class ServerAclAction`  
_public; L10-37_
- desc: General server ACL actions
- L15 _public property_ `public static AclAction Debug { get; }` — Access to the debug endpoints
- L20 _public property_ `public static AclAction Impersonate { get; }` — Ability to impersonate another user
- L25 _public property_ `public static AclAction ViewCosts { get; }` — View estimated costs for particular operations
- L30 _public property_ `public static AclAction IssueBearerToken { get; }` — Issue bearer token for the current user
- L35 _public property_ `public static AclAction IssueExtendedBearerToken { get; }` — Issue bearer token for the current user

### `Source/Programs/Horde/HordeServer.Shared/Telemetry/ITelemetryWriter.cs` (HordeServer.Shared)


#### interface `HordeServer.Telemetry.ITelemetryWriter`  
`public interface ITelemetryWriter`  
_public; L10-31_
- desc: Interface for writing telemetry events from the server
- L15 _public* property_ `bool Enabled { get; }` — Whether the writer is enabled. Can be used to shortcut construction of event data.
- L22 _public* method_ `void WriteEvent(TelemetryStoreId telemetryStoreId, object payload)` — Writes a telemetry event using the server's metadata
- L30 _public* method_ `void WriteEvent(TelemetryStoreId telemetryStoreId, TelemetryRecordMeta metadata, object payload)` — Writes a telemetry event

#### record `HordeServer.Telemetry.TelemetryRecordMeta`  
`public record class TelemetryRecordMeta(string? AppId = null, string? AppVersion = null, string? AppEnvironment = null, string? SessionId = null)`  
_public; L40-46_
- desc: Additional metadata associated with a telemetry event
- L45 _public const_ `public const string HordeAppId = "Horde"` — App id for events originating from Horde itself

#### class `HordeServer.Telemetry.NullTelemetryWriter`  
`public class NullTelemetryWriter : ITelemetryWriter`  
_public; L51-63_
- inherits: `ITelemetryWriter`
- desc: Inactive implementation of ITelemetryWriter
- L54 _public property_ `public bool Enabled { get; }` — (inheritdoc)
- L57-58 _public method_ `public void WriteEvent(TelemetryStoreId telemetryStoreId, object payload)` — (inheritdoc)
- L61-62 _public method_ `public void WriteEvent(TelemetryStoreId telemetryStoreId, TelemetryRecordMeta metadata, object payload)` — (inheritdoc)

### `Source/Programs/Horde/HordeServer.Shared/Telemetry/TelemetryAclAction.cs` (HordeServer.Shared)


#### class `HordeServer.Telemetry.TelemetryAclAction`  
`public static class TelemetryAclAction`  
_public; L10-16_
- desc: ACL actions for telemetry operations
- L15 _public property_ `public static AclAction QueryMetrics { get; }` — Ability to search for various metrics

### `Source/Programs/Horde/HordeServer.Shared/Users/IAvatar.cs` (HordeServer.Shared)


#### interface `HordeServer.Users.IAvatar`  
`public interface IAvatar`  
_public; L8-29_
- desc: Avatar for the user
- L13 _public property_ `public string? Image24 { get; set; }` — Url for a 24x24 pixel image
- L18 _public property_ `public string? Image32 { get; set; }` — Url for a 32x32 pixel image
- L23 _public property_ `public string? Image48 { get; set; }` — Url for a 48x48 pixel image
- L28 _public property_ `public string? Image72 { get; set; }` — Url for a 72x72 pixel image

### `Source/Programs/Horde/HordeServer.Shared/Users/IAvatarService.cs` (HordeServer.Shared)


#### interface `HordeServer.Users.IAvatarService`  
`public interface IAvatarService`  
_public; L8-17_
- desc: Provides avatar images
- L16 _public* method_ `Task<IAvatar?> GetAvatarAsync(IUser user, CancellationToken cancellationToken)` — Gets a users's avatar

#### class `HordeServer.Users.NullAvatarService`  
`public class NullAvatarService : IAvatarService`  
_public; L22-26_
- inherits: `IAvatarService`
- desc: Default implementation of IAvatarService
- L25 _public method_ `public Task<IAvatar?> GetAvatarAsync(IUser user, CancellationToken cancellationToken)` — (inheritdoc)

### `Source/Programs/Horde/HordeServer.Shared/Users/IUser.cs` (HordeServer.Shared)


#### class `HordeServer.Users.KnownUsers`  
`public static class KnownUsers`  
_public; L16-22_
- desc: Known user ids
- L21 _public property_ `public static UserId System { get; }` — The system user. Used for automated processes.

#### interface `HordeServer.Users.IUser`  
`public interface IUser`  
_public; L27-48_
- desc: Document which collates information about a user, and their personal settings
- L32 _public property_ `public UserId Id { get; }` — The user id
- L37 _public property_ `public string Name { get; }` — Full name of the user
- L42 _public property_ `public string Login { get; }` — The user's login id
- L47 _public property_ `public string? Email { get; }` — The user's email

#### interface `HordeServer.Users.IUserClaims`  
`public interface IUserClaims`  
_public; L53-64_
- desc: Claims for a particular user
- L58 _public property_ `public UserId UserId { get; }` — The user id
- L63 _public property_ `public IReadOnlyList<IUserClaim> Claims { get; }` — Claims for this user (on last login)

#### interface `HordeServer.Users.IUserJobTemplateSettings`  
`public interface IUserJobTemplateSettings`  
_public; L69-95_
- L74 _public property_ `public StreamId StreamId { get; }` — The stream the job was run in
- L79 _public property_ `public TemplateId TemplateId { get; }` — The template id of the job
- L84 _public property_ `public string TemplateHash { get; }` — The hash of the template definition
- L89 _public property_ `public IReadOnlyList<string> Arguments { get; }` — The arguments defined when creating the job
- L94 _public property_ `public DateTime UpdateTimeUtc { get; }` — The last time the job template was used

#### class `HordeServer.Users.UpdateUserJobTemplateOptions`  
`public class UpdateUserJobTemplateOptions`  
_public; L100-121_
- desc: Settings for updating job template user preference
- L105 _public property_ `public StreamId StreamId { get; set; }` — The stream the job was run in
- L110 _public property_ `public TemplateId TemplateId { get; set; }` — The template id of the job
- L115 _public property_ `public string TemplateHash { get; set; }` — The hash of the template definition
- L120 _public property_ `public IReadOnlyList<string> Arguments { get; set; }` — The arguments defined when creating the job

#### interface `HordeServer.Users.IUserSettings`  
`public interface IUserSettings`  
_public; L126-162_
- desc: User settings document
- L131 _public property_ `public UserId UserId { get; }` — The user id
- L136 _public property_ `public bool EnableExperimentalFeatures { get; }` — Whether to enable experimental features
- L141 _public property_ `public bool AlwaysTagPreflightCL { get; }` — Whether to always tag CL descriptions for preflights
- L146 _public property_ `public BsonValue DashboardSettings { get; }` — Opaque settings dictionary for the dashboard
- L151 _public property_ `public IReadOnlyList<JobId> PinnedJobIds { get; }` — List of pinned jobs
- L156 _public property_ `public IReadOnlyList<BisectTaskId> PinnedBisectTaskIds { get; }` — List of pinned bisection tasks
- L161 _public property_ `public IReadOnlyList<IUserJobTemplateSettings>? JobTemplateSettings { get; }` — List of job template preferences

#### class `HordeServer.Users.UserExtensions`  
`public static class UserExtensions`  
_public; L167-220_
- desc: Extension methods
- L172-203 _public method_ `public static GetUserResponse ToApiResponse(this IUser user, IAvatar? avatar, IUserClaims? claims, IUserSettings? settings)` — Creates an API response object
- L208-211 _public method_ `public static GetThinUserInfoResponse ToThinApiResponse(this IUser user)` — Creates an API thin user response
- L216-219 _public method_ `public static GetJobTemplateSettingsResponse ToApiResponse(this IUserJobTemplateSettings settings)` — Creates an API settings response

### `Source/Programs/Horde/HordeServer.Shared/Users/IUserClaim.cs` (HordeServer.Shared)


#### interface `HordeServer.Users.IUserClaim`  
`public interface IUserClaim`  
_public; L10-21_
- desc: Claim for a user
- L15 _public property_ `public string Type { get; }` — Name of the claim
- L20 _public property_ `public string Value { get; }` — Value of the claim

#### class `HordeServer.Users.UserClaim`  
`public class UserClaim : IUserClaim`  
_public; L26-69_
- inherits: `IUserClaim`
- desc: New claim document
- L29 _public property_ `public string Type { get; set; }` — (inheritdoc)
- L32 _public property_ `public string Value { get; set; }` — (inheritdoc)
- L39-43 _public ctor_ `public UserClaim(string type, string value)` — Constructor
- L49-52 _public ctor_ `public UserClaim(IUserClaim other) : this(other.Type, other.Value)` — Constructor
- L59-62 _public method_ `public static UserClaim FromClaim(Claim claim)` — Constructs a UserClaim from a Claim object
- L68 _public operator_ `public static implicit operator UserClaim(Claim claim)` — Conversion operator from NET claims

### `Source/Programs/Horde/HordeServer.Shared/Users/IUserCollection.cs` (HordeServer.Shared)


#### interface `HordeServer.Users.IUserCollection`  
`public interface IUserCollection`  
_public; L15-110_
- desc: Manages user documents
- L23 _public* method_ `Task<IUser?> GetUserAsync(UserId id, CancellationToken cancellationToken = default)` — Gets a user by unique id
- L31 _public* method_ `ValueTask<IUser?> GetCachedUserAsync(UserId? id, CancellationToken cancellationToken = default)` — Gets a cached user by unique id
- L42 _public* method_ `Task<IReadOnlyList<IUser>> FindUsersAsync(IEnumerable<UserId>? ids = null, string? nameRegex = null, int? index = null, int? count = null, CancellationToken cancellationToken = default)` — Gets a user by unique id
- L50 _public* method_ `Task<IUser?> FindUserByLoginAsync(string login, CancellationToken cancellationToken = default)` — Gets a user by login
- L58 _public* method_ `Task<IUser?> FindUserByEmailAsync(string email, CancellationToken cancellationToken = default)` — Gets a user by email address
- L68 _public* method_ `Task<IUser> FindOrAddUserByLoginAsync(string login, string? name = null, string? email = null, CancellationToken cancellationToken = default)` — Find or add a user with the given claims. Claims will be updated if the user exists.
- L76 _public* method_ `Task<IUserClaims> GetClaimsAsync(UserId userId, CancellationToken cancellationToken = default)` — Gets the claims for a user
- L85 _public* method_ `Task UpdateClaimsAsync(UserId userId, IEnumerable<IUserClaim> claims, CancellationToken cancellationToken = default)` — Update the claims for a user
- L93 _public* method_ `Task<IUserSettings> GetSettingsAsync(UserId userId, CancellationToken cancellationToken = default)` — Get settings for a user
- L109 _public* method_ `Task UpdateSettingsAsync(UserId userId, bool? enableExperimentalFeatures = null, bool? alwaysTagPreflightCL = null, BsonValue? dashboardSettings = null, IEnumerable<JobId>? addPinnedJobIds = null, IEnumerable<JobId>? removePinnedJobIds = null, UpdateUserJobTemplateOptions? templateOptions = null, IEnumerable<BisectTaskId>? addBisectTaskIds = null, IEnumerable<BisectTaskId>? removeBisectTaskIds = null, CancellationToken cancellationToken = default)` — Update a user

#### class `HordeServer.Users.UserCollectionExtensions`  
`public static class UserCollectionExtensions`  
_public; L115-136_
- desc: Extension methods for the user collect
- L124-135 _public method_ `public static Task<IUser?> GetUserAsync(this IUserCollection userCollection, ClaimsPrincipal principal, CancellationToken cancellationToken = default)` — Gets a particular user info from the collection

### `Source/Programs/Horde/HordeServer.Shared/Utilities/AsyncCachedValue.cs` (HordeServer.Shared)


#### class `HordeServer.Utilities.AsyncCachedValue`  
`public sealed class AsyncCachedValue<T> : IAsyncDisposable`  
_public; L12-170_
- inherits: `IAsyncDisposable`
- desc: Caches a value and asynchronously updates it after a period of time
- L29 _private* field_ `CancellationTokenSource _cancellationTokenSource = new CancellationTokenSource()`
- L34 _private* field_ `Task<State>? _current = null` — The current state
- L39 _private* field_ `readonly Func<CancellationToken, Task<T>> _generator` — Generator for the new value
- L39 _private* field_ `readonly Func< _generator` — Generator for the new value
- L44 _private* field_ `readonly TimeSpan _minRefreshTime` — Time at which to start to refresh the value
- L49 _private* field_ `readonly TimeSpan _maxRefreshTime` — Time at which to wait for the value to refresh
- L54-57 _public ctor_ `public AsyncCachedValue(Func<CancellationToken, Task<T>> generator, TimeSpan refreshTime) : this(generator, refreshTime * 0.75, refreshTime)` — Default constructor
- L62-67 _public ctor_ `public AsyncCachedValue(Func<CancellationToken, Task<T>> generator, TimeSpan minRefreshTime, TimeSpan maxRefreshTime)` — Default constructor
- L70-84 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L89-92 _public method_ `public void Invalidate()` — Invalidates the current value
- L99-102 _public method_ `public Task<T> GetAsync(CancellationToken cancellationToken = default)` — Tries to get the current value
- L108-117 _public method_ `public Task<T> GetAsync(TimeSpan maxAge, CancellationToken cancellationToken = default)` — Tries to get the current value
- L119-124 _private* method_ `static async Task<T> WrapCancellationAsync(Task<T> task, CancellationToken cancellationToken)`
- L126-146 _private* method_ `async Task<T> GetInternalAsync(TimeSpan maxAge)`
- L148-164 _private* method_ `Task<State> CreateOrGetStateTaskAsync(ref Task<State>? stateTask)`
- L166-169 _private* method_ `async Task<State> CreateStateAsync()`

#### class `HordeServer.Utilities.AsyncCachedValue.State`  
`class State`  
_private*; L14-27_
- L16 _public field_ `public readonly T Value`
- L17 _private* field_ `readonly Stopwatch _timer`
- L18 _public field_ `public Task<State>? _next`
- L20 _public property_ `public TimeSpan Elapsed => ...`
- L22-26 _public ctor_ `public State(T value)`

### `Source/Programs/Horde/HordeServer.Shared/Utilities/AsyncTaskQueue.cs` (HordeServer.Shared)


#### class `HordeServer.Utilities.AsyncTaskQueue`  
`public sealed class AsyncTaskQueue : IAsyncDisposable`  
_public; L10-73_
- inherits: `IAsyncDisposable`
- desc: Allows spawning async tasks that will run sequentially, and allows waiting for them to complete
- L12 _private* field_ `readonly object _lockObject = new object()`
- L13 _private* field_ `Task _task`
- L14 _private* field_ `readonly ILogger _logger`
- L15 _private* field_ `CancellationTokenSource _cancellationSource`
- L21-26 _public ctor_ `public AsyncTaskQueue(ILogger logger)` — Constructor
- L29-39 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L45-52 _public method_ `public void Enqueue(Func<CancellationToken, Task> func)` — Adds a new task to the queue
- L57 _public method_ `public Task FlushAsync(CancellationToken cancellationToken = default)` — Waits for any queued tasks to complete
- L60-72 _private* method_ `async Task RunAsync(Task prevTask, Func<CancellationToken, Task> func)`

### `Source/Programs/Horde/HordeServer.Shared/Utilities/Aws.cs` (HordeServer.Shared)


#### class `HordeServer.Utilities.AwsHelper`  
`public static class AwsHelper`  
_public; L8-48_
- desc: Helper functions for interacting with Amazon Web Services (AWS)
- L19-47 _public method_ `public static (string AccessKey, string SecretAccessKey, string SecretToken) ReadAwsCredentials(string profileName, string? credentialsFilePath = null)` — Reads AWS credentials from 'credentials' file The AWS SDK provided functionality was proven too much work, so this is a simplified version.

### `Source/Programs/Horde/HordeServer.Shared/Utilities/BinaryIdConverter.cs` (HordeServer.Shared)


#### class `HordeServer.Utilities.BinaryIdBsonSerializer`  
`public sealed class BinaryIdBsonSerializer<TValue, TConverter> : SerializerBase<TValue> where TValue : struct where TConverter : BinaryIdConverter<TValue>, new()`  
_public; L13-22_
- inherits: `SerializerBase<TValue>`
- constraints: `where TValue : struct where TConverter : BinaryIdConverter<TValue>, new()`
- desc: Class which serializes object id types to BSON
- L15 _private* field_ `readonly TConverter _converter = new TConverter()`
- L18 _public method_ `public override TValue Deserialize(BsonDeserializationContext context, BsonDeserializationArgs args)` — (inheritdoc)
- L21 _public method_ `public override void Serialize(BsonSerializationContext context, BsonSerializationArgs args, TValue value)` — (inheritdoc)

#### class `HordeServer.Utilities.BinaryIdBsonSerializationProvider`  
`public sealed class BinaryIdBsonSerializationProvider : BsonSerializationProviderBase`  
_public; L27-39_
- inherits: `BsonSerializationProviderBase`
- desc: Class which serializes object id types to BSON
- L30-38 _public method_ `public override IBsonSerializer? GetSerializer(Type type, IBsonSerializerRegistry serializerRegistry)` — (inheritdoc)

### `Source/Programs/Horde/HordeServer.Shared/Utilities/BinaryIdUtils.cs` (HordeServer.Shared)


#### class `HordeServer.Utilities.BinaryIdUtils`  
`public static class BinaryIdUtils`  
_public; L11-37_
- desc: Utility methods for BinaryId
- L16-20 _public method_ `public static BinaryId CreateNew()` — Creates a new BinaryId
- L25-28 _public method_ `public static BinaryId FromObjectId(ObjectId objectId)` — Creates a BinaryId from an ObjectId
- L33-36 _public method_ `public static ObjectId ToObjectId(BinaryId binaryId)` — Creates an ObjectId from a BinaryId

### `Source/Programs/Horde/HordeServer.Shared/Utilities/BsonDocumentExtensions.cs` (HordeServer.Shared)


#### class `HordeServer.Utilities.BsonDocumentExtensions`  
`public static class BsonDocumentExtensions`  
_public; L11-105_
- desc: Extension methods for BsonDocument
- L21-37 _public method_ `public static bool TryGetPropertyValue(this BsonDocument document, string name, BsonType type, [NotNullWhen(true)] out BsonValue? outValue)` — Gets a property value from a document or subdocument, indicated with dotted notation
- L47-60 _private method_ `private static bool TryGetDirectPropertyValue(this BsonDocument document, string name, BsonType type, [NotNullWhen(true)] out BsonValue? outValue)` — Gets a property value that's an immediate child of the document
- L69-82 _public method_ `public static bool TryGetInt32(this BsonDocument document, string name, out int outValue)` — Gets an int32 value from the document
- L91-104 _public method_ `public static bool TryGetString(this BsonDocument document, string name, [NotNullWhen(true)] out string? outValue)` — Gets a string value from the document

### `Source/Programs/Horde/HordeServer.Shared/Utilities/CaseInsensitiveDictionary.cs` (HordeServer.Shared)


#### class `HordeServer.Utilities.CaseInsensitiveDictionary`  
`public class CaseInsensitiveDictionary<TValue> : Dictionary<string, TValue>`  
_public; L8-33_
- inherits: `Dictionary<string, TValue>`
- desc: Case insensitive set of strings
- L13-16 _public ctor_ `public CaseInsensitiveDictionary() : base(StringComparer.OrdinalIgnoreCase)` — Constructor
- L21-24 _public ctor_ `public CaseInsensitiveDictionary(IDictionary<string, TValue> items) : base(items, StringComparer.OrdinalIgnoreCase)` — Constructor
- L29-32 _public ctor_ `public CaseInsensitiveDictionary(IEnumerable<KeyValuePair<string, TValue>> items) : base(items, StringComparer.OrdinalIgnoreCase)` — Constructor

### `Source/Programs/Horde/HordeServer.Shared/Utilities/CaseInsensitiveStringSet.cs` (HordeServer.Shared)


#### class `HordeServer.Utilities.CaseInsensitiveStringSet`  
`public class CaseInsensitiveStringSet : HashSet<string>`  
_public; L8-25_
- inherits: `HashSet<string>`
- desc: Case insensitive set of strings
- L13-16 _public ctor_ `public CaseInsensitiveStringSet() : base(StringComparer.OrdinalIgnoreCase)` — Constructor
- L21-24 _public ctor_ `public CaseInsensitiveStringSet(IEnumerable<string> items) : base(items, StringComparer.OrdinalIgnoreCase)` — Constructor

### `Source/Programs/Horde/HordeServer.Shared/Utilities/CollectionExtensions.cs` (HordeServer.Shared)


#### class `HordeServer.Utilities.CollectionExtensions`  
`public static class CollectionExtensions`  
_public; L8-24_
- desc: Extension methods for collections
- L17-23 _public method_ `public static void Add<TKey, TValue>(this Google.Protobuf.Collections.MapField<TKey, TValue> map, IEnumerable<KeyValuePair<TKey, TValue>> sequence)` — Adds an arbitrary sequence of items to a protobuf map field

### `Source/Programs/Horde/HordeServer.Shared/Utilities/CppApiAttribute.cs` (HordeServer.Shared)


#### class `HordeServer.Utilities.CppApiAttribute`  
`public sealed class CppApiAttribute : Attribute`  
_public; L9-11_
- attrs: `[AttributeUsage(AttributeTargets.Class)]`
- inherits: `Attribute`
- desc: Indicates that requests and responses should be included in the exported C++ API

### `Source/Programs/Horde/HordeServer.Shared/Utilities/CustomFileCallbackResult.cs` (HordeServer.Shared)


#### class `HordeServer.Utilities.CustomFileCallbackResult`  
`public class CustomFileCallbackResult : FileResult`  
_public; L14-77_
- inherits: `FileResult`
- desc: Class deriving from a FileResult that allows custom file types (used for zip file creation)
- L16 _private field_ `private readonly Func<Stream, ActionContext, Task> _callback`
- L16 _private field_ `private readonly Func< ActionContext`
- L16 _private field_ `private readonly Func< _callback`
- L17 _private* field_ `readonly string _fileName`
- L18 _private* field_ `readonly bool _inline`
- L27-33 _public ctor_ `public CustomFileCallbackResult(string fileName, string mimeType, bool inline, Func<Stream, ActionContext, Task> callback) : base(mimeType)` — Constructor
- L40-49 _public method_ `public override Task ExecuteResultAsync(ActionContext context)` — Executes the action result

#### class `HordeServer.Utilities.CustomFileCallbackResult.CustomFileCallbackResultExecutor`  
`private sealed class CustomFileCallbackResultExecutor : FileResultExecutorBase`  
_private; L54-76_
- inherits: `FileResultExecutorBase`
- desc: Exectutor for the custom FileResult
- L60-63 _public ctor_ `public CustomFileCallbackResultExecutor(ILoggerFactory loggerFactory) : base(CreateLogger<CustomFileCallbackResultExecutor>(loggerFactory))` — Constructor
- L71-75 _public method_ `public Task ExecuteAsync(ActionContext context, CustomFileCallbackResult result)` — Executes a CustomFileResult callback

#### class `HordeServer.Utilities.CustomBufferStream`  
`public class CustomBufferStream : MemoryStream`  
_public; L82-88_
- inherits: `MemoryStream`
- desc: Stream overriding CanSeek to false so the zip file plays nice with it.
- L87 _public property_ `public override bool CanSeek => ...` — Always report unseekable.

### `Source/Programs/Horde/HordeServer.Shared/Utilities/DateTimeJsonConverter.cs` (HordeServer.Shared)


#### class `HordeServer.Utilities.DateTimeJsonConverter`  
`public class DateTimeJsonConverter : JsonConverter<DateTime>`  
_public; L13-33_
- inherits: `JsonConverter<DateTime>`
- desc: Converter for DateTime values to JSON
- L16-26 _public method_ `public override DateTime Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — (inheritdoc)
- L29-32 _public method_ `public override void Write(Utf8JsonWriter writer, DateTime dateTime, JsonSerializerOptions options)` — (inheritdoc)

### `Source/Programs/Horde/HordeServer.Shared/Utilities/DateTimeOffsetJsonConverter.cs` (HordeServer.Shared)


#### class `HordeServer.Utilities.DateTimeOffsetJsonConverter`  
`public class DateTimeOffsetJsonConverter : JsonConverter<DateTimeOffset>`  
_public; L13-33_
- inherits: `JsonConverter<DateTimeOffset>`
- desc: Converter for DateTimeOffset values to JSON
- L16-26 _public method_ `public override DateTimeOffset Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — (inheritdoc)
- L29-32 _public method_ `public override void Write(Utf8JsonWriter writer, DateTimeOffset dateTimeOffset, JsonSerializerOptions options)` — (inheritdoc)

### `Source/Programs/Horde/HordeServer.Shared/Utilities/DebugEndpointAttribute.cs` (HordeServer.Shared)


#### class `HordeServer.Utilities.DebugEndpointAttribute`  
`public sealed class DebugEndpointAttribute : Attribute, IActionFilter`  
_public; L14-30_
- attrs: `[AttributeUsage(AttributeTargets.Class)]`
- inherits: `Attribute, IActionFilter`
- desc: Only requests to attached controller to pass if debug endpoint is enabled in settings Adds extra security for not enabling these admin endpoints by accident.
- L17-24 _public method_ `public void OnActionExecuting(ActionExecutingContext context)` — (inheritdoc)
- L27-29 _public method_ `public void OnActionExecuted(ActionExecutedContext context)` — (inheritdoc)

### `Source/Programs/Horde/HordeServer.Shared/Utilities/DefaultAclBuilder.cs` (HordeServer.Shared)


#### class `HordeServer.Utilities.DefaultAclBuilder`  
`public class DefaultAclBuilder`  
_public; L11-63_
- desc: Utility class for allowing plugins to modify the default ACL used by the server
- L13 _private* field_ `readonly List<AclEntryConfig> _roles = new List<AclEntryConfig>()`
- L14 _private* field_ `readonly HashSet<AclAction> _readActions = new HashSet<AclAction>()`
- L15 _private* field_ `readonly HashSet<AclAction> _writeActions = new HashSet<AclAction>()`
- L22 _public method_ `public void AddCustomRole(AclClaimConfig claim, AclAction[] actions)` — Adds a custom role with a certain set of entitlements
- L28 _public method_ `public void AddDefaultReadAction(AclAction action)` — Adds a default read operation that users can perform
- L34 _public method_ `public void AddDefaultWriteAction(AclAction action)` — Adds a default write operation that users can perform
- L40-62 _public method_ `public AclConfig Build()` — Create the new acl config

### `Source/Programs/Horde/HordeServer.Shared/Utilities/HordeClaimTypes.cs` (HordeServer.Shared)


#### class `HordeServer.Utilities.HordeClaimTypes`  
`public static class HordeClaimTypes`  
_public; L15-116_
- desc: Claim types that are specific to horde
- L20 _public const_ `public const string CurrentVersion = "1"` — Version number for auth claims. Can be updated to force a re-login.
- L25 _private* const_ `const string Prefix = "http://epicgames.com/ue/horde/"` — Base URI for all Horde claims.
- L30 _public const_ `public const string Version = Prefix + "version"` — Version number for the auth header
- L35 _public const_ `public const string Role = Prefix + "role"` — Claim for a particular role. This is reserved for well-known roles defined by Horde itself.
- L40 _public const_ `public const string Group = Prefix + "group"` — Claim type reserved for a particular group within the Horde account system. Values are user defined.
- L45 _public const_ `public const string Agent = Prefix + "agent"` — Claim for a particular agent
- L50 _public const_ `public const string AgentEnrollmentKey = Prefix + "agent-enrollment-key"` — Claim for an agent's enrollment key
- L55 _public const_ `public const string AccountId = Prefix + "account-id"` — Claim for a particular account id
- L60 _public const_ `public const string AgentSessionId = Prefix + "session"` — Claim for a particular session
- L65 _public const_ `public const string User = Prefix + "user"` — User name for horde
- L70 _public const_ `public const string UserId = Prefix + "user-id-v3"` — Unique id of the horde user (see IUserCollection)
- L75 _public const_ `public const string JobArtifacts = Prefix + "job-artifacts"` — Claim for downloading artifacts from a particular job
- L80 _public const_ `public const string PerforceUser = Prefix + "perforce-user"` — Claim for the Perforce username
- L85 _public const_ `public const string ExternalIssueUser = Prefix + "external-issue-user"` — Claim for the external issue username
- L90 _public const_ `public const string Lease = Prefix + "lease"` — Claim identifying an agent as executing a particular lease
- L95 _public const_ `public const string LeaseStream = Prefix + "lease-stream"` — Claim identifying an agent as executing a lease in a particular stream
- L100 _public const_ `public const string LeaseProject = Prefix + "lease-project"` — Claim identifying an agent as executing a lease in a particular project
- L105 _public const_ `public const string LeaseTemplate = Prefix + "lease-template"` — Claim identifying an agent as executing a lease in a particular job template
- L110 _public const_ `public const string ReadNamespace = Prefix + "read-namespace"` — Claim allowing a certain namespace and/or path to be read from. See WriteNamespace.
- L115 _public const_ `public const string WriteNamespace = Prefix + "write-namespace"` — Claim allowing a certain namespace and/or path to be written to. Value may be a namespace name, or a subpath (eg. ns:a/b will only allow blobs and refs with an a/b prefix to be written).

#### class `HordeServer.Utilities.HordeClaimExtensions`  
`public static class HordeClaimExtensions`  
_public; L121-190_
- desc: Extension methods for getting Horde claims from a principal
- L128-132 _public method_ `public static AccountId? GetAccountId(this ClaimsPrincipal principal)` — Gets the Horde account id from a principal
- L139-143 _public method_ `public static UserId? GetUserId(this ClaimsPrincipal principal)` — Gets the Horde user ID from a principal
- L148-159 _public method_ `public static bool AuthorizeAsUser(this AclConfig aclConfig, ClaimsPrincipal user, UserId userId)` — Determines whether the given user can masquerade as a given user
- L166-169 _public method_ `public static string? GetUser(this ClaimsPrincipal principal)` — Gets the Horde username from a principal
- L176-180 _public method_ `public static string? GetExternalIssueUser(this ClaimsPrincipal user)` — Gets the external issue username for the given principal
- L186-189 _public method_ `public static bool HasAdminClaim(this ClaimsPrincipal user)` — Determine if a user has the administrator claim

### `Source/Programs/Horde/HordeServer.Shared/Utilities/HordeClaims.cs` (HordeServer.Shared)


#### class `HordeServer.Utilities.HordeClaims`  
`public static class HordeClaims`  
_public; L12-73_
- desc: Predetermined claim values
- L17 _public property_ `public static AclClaimConfig AdminClaim { get; }` — Claim which gives unfettered access to all Horde endpoints
- L22 _public property_ `public static AclClaimConfig AgentRegistrationClaim { get; }` — Name of the role that can be used to administer agents
- L27 _public property_ `public static AclClaimConfig DownloadSoftwareClaim { get; }` — Name of the role used to upload software
- L32 _public property_ `public static AclClaimConfig UploadToolsClaim { get; }` — Name of the role used to upload tools
- L37 _public property_ `public static AclClaimConfig ConfigureProjectsClaim { get; }` — Name of the role used to upload software
- L42 _public property_ `public static AclClaimConfig StartChainedJobClaim { get; }` — Name of the role used to upload software
- L47 _public property_ `public static AclClaimConfig AgentDedicatedRoleClaim { get; }` — Role for dedicated agents
- L52 _public property_ `public static AclClaimConfig AgentWorkstationRoleClaim { get; }` — Role for workstation agents
- L59-62 _public method_ `public static AclClaimConfig GetAgentClaim(AgentId agentId)` — Gets the role for a specific agent
- L69-72 _public method_ `public static AclClaimConfig GetSessionClaim(SessionId sessionId)` — Gets the role for a specific agent session

### `Source/Programs/Horde/HordeServer.Shared/Utilities/HordeControllerBase.cs` (HordeServer.Shared)


#### class `HordeServer.Utilities.HordeControllerBase`  
`public abstract class HordeControllerBase : ControllerBase`  
_public; L29-359_
- inherits: `ControllerBase`
- desc: Base class for Horde controllers
- L37-40 _protected method_ `protected ActionResult BadRequest(string message, params object[] args)` — attrs: `[NonAction]` — Create a response indicating a problem with the request
- L49-52 _protected method_ `protected ActionResult BadRequest(EventId eventId, string message, params object[] args)` — attrs: `[NonAction]` — Create a response indicating a problem with the request
- L58-61 _protected method_ `protected ActionResult Forbid(AclAction action)` — attrs: `[NonAction]` — Returns a 403 (forbidden) response with the given action
- L67-70 _protected method_ `protected ActionResult Forbid(AclAction action, AgentId agentId)` — attrs: `[NonAction]` — Returns a 403 (forbidden) response with the given action and object
- L76-79 _protected method_ `protected ActionResult Forbid(AclAction action, AclScopeName scopeName)` — attrs: `[NonAction]` — Returns a 403 (forbidden) response with the given action and object
- L85-88 _protected method_ `protected ActionResult Forbid(AclAction action, ClusterId clusterId)` — attrs: `[NonAction]` — Returns a 403 (forbidden) response with the given action and object
- L94-97 _protected method_ `protected ActionResult Forbid(AclAction action, JobId jobId)` — attrs: `[NonAction]` — Returns a 403 (forbidden) response with the given action and object
- L103-106 _protected method_ `protected ActionResult Forbid(AclAction action, NamespaceId namespaceId)` — attrs: `[NonAction]` — Returns a 403 (forbidden) response with the given action and object
- L112-115 _protected method_ `protected ActionResult Forbid(AclAction action, ProjectId projectId)` — attrs: `[NonAction]` — Returns a 403 (forbidden) response with the given action and object
- L121-124 _protected method_ `protected ActionResult Forbid(AclAction action, SecretId secretId)` — attrs: `[NonAction]` — Returns a 403 (forbidden) response with the given action and object
- L130-133 _protected method_ `protected ActionResult Forbid(AclAction action, StreamId streamId)` — attrs: `[NonAction]` — Returns a 403 (forbidden) response with the given action and object
- L139-142 _protected method_ `protected ActionResult Forbid(AclAction action, SymbolStoreId storeId)` — attrs: `[NonAction]` — Returns a 403 (forbidden) response with the given action and object
- L148-151 _protected method_ `protected ActionResult Forbid(AclAction action, ToolId toolId)` — attrs: `[NonAction]` — Returns a 403 (forbidden) response with the given action and object
- L157-160 _protected method_ `protected ActionResult Forbid(AclAction action, TemplateId templateId)` — attrs: `[NonAction]` — Returns a 403 (forbidden) response with the given action and object
- L166-169 _private method_ `private ActionResult Forbid(AclAction action, string objectMessage, object obj)` — attrs: `[NonAction]` — Returns a 403 (forbidden) response with the given action and object
- L175-178 _protected method_ `protected ActionResult Forbid(string message, params object[] args)` — attrs: `[NonAction]` — Returns a 403 response with the given log event
- L184-187 _protected method_ `protected ActionResult NotFound(AccountId accountId)` — attrs: `[NonAction]` — Returns a 404 response for the given object
- L193-196 _protected method_ `protected ActionResult NotFound(AgentId agentId)` — attrs: `[NonAction]` — Returns a 404 response for the given object
- L202-205 _protected method_ `protected ActionResult NotFound(AgentId agentId, LeaseId leaseId)` — attrs: `[NonAction]` — Returns a 404 response for the given object
- L211-214 _protected method_ `protected ActionResult NotFound(ArtifactId artifactId)` — attrs: `[NonAction]` — Returns a 404 response for the given object
- L220-223 _protected method_ `protected ActionResult NotFound(ClusterId clusterId)` — attrs: `[NonAction]` — Returns a 404 response for the given object
- L229-232 _protected method_ `protected ActionResult NotFound(JobId jobId)` — attrs: `[NonAction]` — Returns a 404 response for the given object
- L238-241 _protected method_ `protected ActionResult NotFound(JobId jobId, int groupIdx)` — attrs: `[NonAction]` — Returns a 404 response for the given object
- L247-250 _protected method_ `protected ActionResult NotFound(JobId jobId, int groupIdx, int nodeIdx)` — attrs: `[NonAction]` — Returns a 404 response for the given object
- L256-259 _protected method_ `protected ActionResult NotFound(JobId jobId, JobStepBatchId batchId)` — attrs: `[NonAction]` — Returns a 404 response for the given object
- L265-268 _protected method_ `protected ActionResult NotFound(JobId jobId, JobStepBatchId batchId, JobStepId stepId)` — attrs: `[NonAction]` — Returns a 404 response for the given object
- L274-277 _protected method_ `protected ActionResult NotFound(NamespaceId namespaceId)` — attrs: `[NonAction]` — Returns a 404 response for the given object
- L283-286 _protected method_ `protected ActionResult NotFound(NamespaceId namespaceId, RefName refName)` — attrs: `[NonAction]` — Returns a 404 response for the given object
- L292-295 _protected method_ `protected ActionResult NotFound(BisectTaskId bisectTaskId)` — attrs: `[NonAction]` — Returns a 404 response for the given object
- L301-304 _protected method_ `protected ActionResult NotFound(SecretId secretId)` — attrs: `[NonAction]` — Returns a 404 response for the given object
- L310-313 _protected method_ `protected ActionResult NotFound(StreamId streamId)` — attrs: `[NonAction]` — Returns a 404 response for the given object
- L319-322 _protected method_ `protected ActionResult NotFound(StreamId streamId, TemplateId templateId)` — attrs: `[NonAction]` — Returns a 404 response for the given object
- L328-331 _protected method_ `protected ActionResult NotFound(TelemetryStoreId telemetryStoreId)` — attrs: `[NonAction]` — Returns a 404 response for the given object
- L337-340 _protected method_ `protected ActionResult NotFound(ToolId toolId)` — attrs: `[NonAction]` — Returns a 404 response for the given object
- L346-349 _protected method_ `protected ActionResult NotFound(ToolId toolId, ToolDeploymentId deploymentId)` — attrs: `[NonAction]` — Returns a 404 response for the given object
- L355-358 _protected method_ `protected ActionResult NotFound(string message, params object[] args)` — attrs: `[NonAction]` — Returns a 404 response for the given object

### `Source/Programs/Horde/HordeServer.Shared/Utilities/InlineFileStreamResult.cs` (HordeServer.Shared)


#### class `HordeServer.Utilities.InlineFileStreamResult`  
`public class InlineFileStreamResult : FileStreamResult`  
_public; L11-37_
- inherits: `FileStreamResult`
- desc: Class to return a file stream without the "content-disposition: attachment" header
- L16 _private* field_ `readonly string _fileName` — The suggested download filename
- L21-25 _public ctor_ `public InlineFileStreamResult(System.IO.Stream stream, string mimeType, string fileName) : base(stream, mimeType)` — Constructor
- L28-36 _public method_ `public override Task ExecuteResultAsync(ActionContext context)` — (inheritdoc)

### `Source/Programs/Horde/HordeServer.Shared/Utilities/JsonConfigFile.cs` (HordeServer.Shared)


#### class `HordeServer.Utilities.JsonConfigFile`  
`public class JsonConfigFile`  
_public; L15-98_
- desc: Allows manipulating JSON config files without fully deserializing them
- L20 _public property_ `public JsonObject Root { get; }` — The root of the config file
- L25-28 _public ctor_ `public JsonConfigFile(JsonObject root)` — Constructor
- L33-38 _public method_ `public static async Task<JsonConfigFile> ReadAsync(FileReference file, CancellationToken cancellationToken = default)` — Reads a json config file from a file on disk
- L43-51 _public method_ `public async Task WriteAsync(FileReference file, CancellationToken cancellationToken = default)` — Writes the config file back out to a file
- L56-74 _public method_ `public static T FindOrAddNode<T>(JsonObject obj, string name, Func<T> factory) where T : JsonNode` — Adds a node with the given name to an object
- L79-97 _public method_ `public static JsonObject FindOrAddElementByKey(JsonArray array, string key, string name)` — Finds an existing element, or adds a new element to an array, with the given name.

### `Source/Programs/Horde/HordeServer.Shared/Utilities/JsonUtils.cs` (HordeServer.Shared)


#### class `HordeServer.Utilities.JsonUtils`  
`public static class JsonUtils`  
_public; L13-42_
- desc: Helper methods for json serialization
- L18 _public property_ `public static JsonSerializerOptions DefaultSerializerOptions { get; }` — Default JSON serialization options
- L20-26 _private* method_ `static JsonSerializerOptions CreateDefaultJsonSerializerOptions()`
- L31-41 _public method_ `public static void ConfigureJsonSerializer(JsonSerializerOptions options)` — Configure a json serializer with all standard Horde converters

### `Source/Programs/Horde/HordeServer.Shared/Utilities/MongoBufferedWriter.cs` (HordeServer.Shared)


#### class `HordeServer.Utilities.MongoBufferedWriter`  
`public sealed class MongoBufferedWriter<TDocument> : IAsyncDisposable where TDocument : class`  
_public; L13-128_
- inherits: `IAsyncDisposable`
- constraints: `where TDocument : class`
- desc: Utility class for buffering document writes to a Mongo collection
- L16 _private* field_ `readonly IMongoCollection<TDocument> _collection`
- L17 _private* field_ `readonly int _flushCount`
- L18 _private* field_ `readonly TimeSpan _flushTime`
- L19 _private* field_ `readonly ConcurrentQueue<TDocument> _queue = new ConcurrentQueue<TDocument>()`
- L20 _private* field_ `readonly BackgroundTask _backgroundTask`
- L21 _private* field_ `readonly AsyncEvent _newDataEvent = new AsyncEvent()`
- L22 _private* field_ `readonly AsyncEvent _flushEvent = new AsyncEvent()`
- L23 _private* field_ `readonly ILogger _logger`
- L28-31 _public ctor_ `public MongoBufferedWriter(IMongoCollection<TDocument> collection, ILogger logger) : this(collection, 50, TimeSpan.FromSeconds(5.0), logger)` — Constructor
- L36-43 _public ctor_ `public MongoBufferedWriter(IMongoCollection<TDocument> collection, int flushCount, TimeSpan flushTime, ILogger logger)` — Constructor
- L46-49 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L54-58 _public method_ `public ValueTask StartAsync()` — Start the background task to periodically flush data to the DB
- L63-67 _public method_ `public async ValueTask StopAsync(CancellationToken cancellationToken)` — Stops the background task
- L70-97 _private* method_ `async Task BackgroundFlushAsync(CancellationToken cancellationToken)`
- L100-115 _public method_ `public async ValueTask FlushAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L118-127 _public method_ `public void Write(TDocument document)` — (inheritdoc)

### `Source/Programs/Horde/HordeServer.Shared/Utilities/MongoExtensions.cs` (HordeServer.Shared)


#### class `HordeServer.Utilities.MongoExtensions`  
`public static class MongoExtensions`  
_public; L15-349_
- desc: Extension methods for MongoDB
- L20-24 _public method_ `public static void MapConstructor<T>(this BsonClassMap classMap, Expression<Func<T>> generator, params string[] argumentNames)` — Maps a constructor for a type into a classmap
- L31-34 _public method_ `public static DateTime RoundToBsonDateTime(DateTime time)` — Rounds a time value to its BSON equivalent (ie. milliseconds since Unix Epoch).
- L39-44 _public method_ `public static BsonDocument Render<T>(this FilterDefinition<T> filter)` — Renders a filter definition to a document using the default serializer registry
- L49-54 _public method_ `public static BsonValue Render<T>(this UpdateDefinition<T> update)` — Renders a filter definition to a document using the default serializer registry
- L66-81 _public method_ `public static async Task<TResult> FindWithHintAsync<TDoc, TResult>(this IMongoCollection<TDoc> collection, FilterDefinition<TDoc> filter, string? indexHint, Func<IFindFluent<TDoc, TDoc>, Task<TResult>> processAsync)` — Executes a query with a particular index hint
- L90-101 _public method_ `public static IFindFluent<TDocument, TProjection> Range<TDocument, TProjection>(this IFindFluent<TDocument, TProjection> query, int? index, int? count)` — Filters the documents returned from a search
- L110-121 _public method_ `public static IAggregateFluent<TDocument> Range<TDocument>(this IAggregateFluent<TDocument> query, int? index, int? count)` — Filters the documents returned from a search
- L131-149 _public method_ `public static async Task<bool> InsertOneIgnoreDuplicatesAsync<TDocument>(this IMongoCollection<TDocument> collection, TDocument newDocument, CancellationToken cancellationToken = default)` — Attempts to insert a document into a collection, handling the error case that a document with the given key already exists
- L158-181 _public method_ `public static async Task InsertManyIgnoreDuplicatesAsync<TDocument>(this IMongoCollection<TDocument> collection, List<TDocument> newDocuments, CancellationToken cancellationToken = default)` — Attempts to insert a document into a collection, handling the error case that a document with the given key already exists
- L192-202 _public method_ `public static UpdateDefinition<TDocument> SetOrUnsetNull<TDocument, TField>(this UpdateDefinitionBuilder<TDocument> updateBuilder, Expression<Func<TDocument, TField?>> field, TField? value) where TField : struct` — Sets a field to a value, or unsets it if the value is null
- L213-223 _public method_ `public static UpdateDefinition<TDocument> SetOrUnsetNull<TDocument, TField>(this UpdateDefinition<TDocument> update, Expression<Func<TDocument, TField?>> field, TField? value) where TField : struct` — Sets a field to a value, or unsets it if the value is null
- L233-243 _public method_ `public static UpdateDefinition<TDocument> SetOrUnsetBool<TDocument>(this UpdateDefinition<TDocument> update, Expression<Func<TDocument, bool>> field, bool value)` — Sets a field to a value, or unsets it if the value is null
- L253-263 _public method_ `public static UpdateDefinition<TDocument> SetOrUnsetBool<TDocument>(this UpdateDefinitionBuilder<TDocument> updateBuilder, Expression<Func<TDocument, bool>> field, bool value)` — Sets a field to a value, or unsets it if the value is null
- L274-284 _public method_ `public static UpdateDefinition<TDocument> SetOrUnsetNullRef<TDocument, TField>(this UpdateDefinitionBuilder<TDocument> updateBuilder, Expression<Func<TDocument, TField?>> field, TField? value) where TField : class` — Sets a field to a value, or unsets it if the value is null
- L294-297 _public method_ `public static FilterDefinition<TDocument> Expr<TDocument>(this FilterDefinitionBuilder<TDocument> filter, Expression<Func<TDocument, bool>> expression)` — Creates a filter definition from a linq expression. This is not generally explicitly castable, so expose it as a FilterDefinitionBuilder method.
- L309-324 _public method_ `public static async IAsyncEnumerable<T> ToAsyncEnumerable<T>(this IAsyncCursorSource<T> source, [EnumeratorCancellation] CancellationToken cancellationToken)` — Creates an async enumerator from the given query
- L331-348 _public method_ `public static BsonValue ToBsonValue(this JsonElement element)` — Converts a JsonElement to a BsonValue

### `Source/Programs/Horde/HordeServer.Shared/Utilities/ObjectIdConverter.cs` (HordeServer.Shared)


#### class `HordeServer.Utilities.ObjectIdConverter`  
`public abstract class ObjectIdConverter<T> where T : struct`  
_public; L18-29_
- constraints: `where T : struct`
- desc: Base class for converting to and from types containing an object id. Useful pattern for reducing boilerplate with strongly typed records.
- L23 _public method_ `public abstract ObjectId ToObjectId(T value)` — Converts a type to a ObjectId
- L28 _public method_ `public abstract T FromObjectId(ObjectId id)` — Constructs a type from an object id

#### class `HordeServer.Utilities.ObjectIdConverterAttribute`  
`public sealed class ObjectIdConverterAttribute : Attribute`  
_public; L35-46_
- attrs: `[AttributeUsage(AttributeTargets.Struct)]`
- inherits: `Attribute`
- desc: Attribute declaring an object id converter for a particular type
- L40 _public property_ `public Type ConverterType { get; }` — The converter type
- L45 _public ctor_ `public ObjectIdConverterAttribute(Type converterType)` — Constructor

#### class `HordeServer.Utilities.ObjectIdTypeConverter`  
`public sealed class ObjectIdTypeConverter<TValue, TConverter> : TypeConverter where TValue : struct where TConverter : ObjectIdConverter<TValue>, new()`  
_public; L51-83_
- inherits: `TypeConverter`
- constraints: `where TValue : struct where TConverter : ObjectIdConverter<TValue>, new()`
- desc: Class which serializes types with a ObjectIdConverter{T} to Json
- L53 _private* field_ `readonly TConverter _converter = new TConverter()`
- L56-59 _public method_ `public override bool CanConvertFrom(ITypeDescriptorContext? context, Type sourceType)` — (inheritdoc)
- L62-69 _public method_ `public override object? ConvertFrom(ITypeDescriptorContext? context, CultureInfo? culture, object value)` — (inheritdoc)
- L72 _public method_ `public override bool CanConvertTo(ITypeDescriptorContext? context, Type? destinationType)` — (inheritdoc)
- L75-82 _public method_ `public override object? ConvertTo(ITypeDescriptorContext? context, CultureInfo? culture, object? value, Type destinationType)` — (inheritdoc)

#### class `HordeServer.Utilities.ObjectIdJsonConverter`  
`public class ObjectIdJsonConverter : JsonConverter<ObjectId>`  
_public; L88-110_
- inherits: `JsonConverter<ObjectId>`
- desc: Class which serializes ObjectId types to Json
- L91-103 _public method_ `public override ObjectId Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — (inheritdoc)
- L106-109 _public method_ `public override void Write(Utf8JsonWriter writer, ObjectId objectId, JsonSerializerOptions options)` — (inheritdoc)

#### class `HordeServer.Utilities.ObjectIdJsonConverter`  
`public sealed class ObjectIdJsonConverter<TValue, TConverter> : JsonConverter<TValue> where TValue : struct where TConverter : ObjectIdConverter<TValue>, new()`  
_public; L115-126_
- inherits: `JsonConverter<TValue>`
- constraints: `where TValue : struct where TConverter : ObjectIdConverter<TValue>, new()`
- desc: Class which serializes types with a ObjectIdConverter{T} to Json
- L117 _private* field_ `readonly TConverter _converter = new TConverter()`
- L120 _public method_ `public override TValue Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — (inheritdoc)
- L124 _public method_ `public override void Write(Utf8JsonWriter writer, TValue value, JsonSerializerOptions options)` — (inheritdoc)

#### class `HordeServer.Utilities.ObjectIdJsonConverterFactory`  
`public sealed class ObjectIdJsonConverterFactory : JsonConverterFactory`  
_public; L131-146_
- inherits: `JsonConverterFactory`
- desc: Creates constructors for types with a ObjectIdConverter{T} to Json
- L134 _public method_ `public override bool CanConvert(Type typeToConvert)` — (inheritdoc)
- L137-145 _public method_ `public override JsonConverter? CreateConverter(Type type, JsonSerializerOptions options)` — (inheritdoc)

#### class `HordeServer.Utilities.ObjectIdBsonSerializer`  
`public sealed class ObjectIdBsonSerializer<TValue, TConverter> : SerializerBase<TValue> where TValue : struct where TConverter : ObjectIdConverter<TValue>, new()`  
_public; L151-161_
- inherits: `SerializerBase<TValue>`
- constraints: `where TValue : struct where TConverter : ObjectIdConverter<TValue>, new()`
- desc: Class which serializes object id types to BSON
- L153 _private* field_ `readonly TConverter _converter = new TConverter()`
- L156 _public method_ `public override TValue Deserialize(BsonDeserializationContext context, BsonDeserializationArgs args)` — (inheritdoc)
- L160 _public method_ `public override void Serialize(BsonSerializationContext context, BsonSerializationArgs args, TValue value)` — (inheritdoc)

#### class `HordeServer.Utilities.ObjectIdBsonSerializationProvider`  
`public sealed class ObjectIdBsonSerializationProvider : BsonSerializationProviderBase`  
_public; L166-178_
- inherits: `BsonSerializationProviderBase`
- desc: Class which serializes object id types to BSON
- L169-177 _public method_ `public override IBsonSerializer? GetSerializer(Type type, IBsonSerializerRegistry serializerRegistry)` — (inheritdoc)

### `Source/Programs/Horde/HordeServer.Shared/Utilities/OpenTelemetryExtensions.cs` (HordeServer.Shared)


#### class `HordeServer.Utilities.OpenTelemetryExtensions`  
`public static class OpenTelemetryExtensions`  
_public; L10-33_
- desc: Extensions to handle Horde specific data types in the OpenTelemetry library
- L14-21 _public method_ `public static TelemetrySpan SetAttribute(this TelemetrySpan span, string key, int? value)` — Set a key:value tag on the span
- L25-32 _public method_ `public static TelemetrySpan SetAttribute(this TelemetrySpan span, string key, DateTimeOffset? value)` — Set a key:value tag on the span

### `Source/Programs/Horde/HordeServer.Shared/Utilities/OpenTelemetryTracers.cs` (HordeServer.Shared)


#### class `HordeServer.Utilities.OpenTelemetryTracers`  
`public static class OpenTelemetryTracers`  
_public; L10-51_
- desc: Static initialization of all available OpenTelemetry tracers
- L16 _public const_ `public const string DatadogResourceAttribute = "resource.name"` — Name of resource name attribute in Datadog Some traces use this for prettier display inside their UI
- L21 _public const_ `public const string HordeName = "Horde"` — Name of default Horde tracer (aka activity source)
- L26 _public const_ `public const string MongoDbName = "MongoDB"` — Name of MongoDB tracer (aka activity source)
- L32 _public const_ `public const string PerforceName = "Perforce"` — Name of Perforce client tracer (aka activity source) By default, tracer is declared inside EpicGames.Perforce.
- L38 _public property_ `public static string[] SourceNames => ...` — List of all source names configured in this class. They are needed at startup when initializing OpenTelemetry
- L44 _public field_ `public static readonly Tracer Horde = TracerProvider.Default.GetTracer(HordeName)` — Default tracer used in Horde Prefer dependency-injected tracer over this static member.
- L50 _public field_ `public static readonly Tracer MongoDb = TracerProvider.Default.GetTracer(MongoDbName)` — Tracer specific to MongoDB Prefer StartMongoDbSpan static extension for Tracer.

### `Source/Programs/Horde/HordeServer.Shared/Utilities/PropertyFilter.cs` (HordeServer.Shared)


#### class `HordeServer.Utilities.PropertyFilter`  
`public class PropertyFilter`  
_public; L15-218_
- attrs: `[TypeConverter(typeof(PropertyFilterTypeConverter))]`
- desc: Utility class to filter a response to include a subset of fields
- L20 _private* field_ `readonly Dictionary<string, PropertyFilter?> _nameToFilter = ...` — Specific filters for properties of this object. A key of '*' will match any property not matched by anything else, and a value of null will include the whole object.
- L20 _private* field_ `readonly Dictionary< _nameToFilter = new Dictionary<string, PropertyFilter?>(StringComparer.OrdinalIgnoreCase)` — Specific filters for properties of this object. A key of '*' will match any property not matched by anything else, and a value of null will include the whole object.
- L27-57 _public method_ `public static PropertyFilter Parse(string? fields)` — Parse a list of fields as a property filter
- L65-68 _public method_ `public static bool Includes(PropertyFilter? filter, string field)` — Checks whether the filter contains the given field
- L76-79 _public method_ `public static object Apply(object response, PropertyFilter? filter)` — Attempts to apply a property filter to a response object, where the property filter may be null.
- L86-89 _public method_ `public bool Includes(string field)` — Checks whether the filter contains the given field
- L96-200 _public method_ `public object ApplyTo(object response)` — Extract the given fields from the response
- L207-217 _private* method_ `static string ConvertPascalToCamelCase(string name)` — Convert a property name to camel case

#### class `HordeServer.Utilities.PropertyFilterTypeConverter`  
`public class PropertyFilterTypeConverter : TypeConverter`  
_public; L223-236_
- inherits: `TypeConverter`
- desc: Type converter from strings to PropertyFilter objects
- L226-229 _public method_ `public override bool CanConvertFrom(ITypeDescriptorContext? context, Type sourceType)` — (inheritdoc)
- L232-235 _public method_ `public override object ConvertFrom(ITypeDescriptorContext? context, CultureInfo? culture, object value)` — (inheritdoc)

#### class `HordeServer.Utilities.PropertyFilterExtensions`  
`public static class PropertyFilterExtensions`  
_public; L241-260_
- desc: Extension methods for property filters
- L249-259 _public method_ `public static object ApplyFilter(this object obj, PropertyFilter? filter)` — Apply a filter to a response object

### `Source/Programs/Horde/HordeServer.Shared/Utilities/RedisExtensions.cs` (HordeServer.Shared)


#### class `HordeServer.Utilities.RedisExtensions`  
`public static class RedisExtensions`  
_public; L10-30_
- desc: Extensions for Redis classes
- L18-29 _public method_ `public static async Task WaitAndIgnoreCancellationsAsync(this ITransaction transaction, params Task[] tasks)` — Await given tasks and swallow any task cancellation exceptions. Useful to do after (failing) transaction to ensure no trailing tasks are left unawaited

### `Source/Programs/Horde/HordeServer.Shared/Utilities/SingletonDocument.cs` (HordeServer.Shared)


#### record struct `HordeServer.Utilities.SingletonId`  
`public record struct SingletonId(StringId Id)`  
_public; L14-23_
- attrs: `[StringIdConverter(typeof(SingletonIdConverter))]`
- desc: Identifier for a pool
- L19 _public ctor_ `public SingletonId(string id) : this(new StringId(id))` — Constructor
- L22 _public method_ `public override string ToString()` — (inheritdoc)

#### class `HordeServer.Utilities.SingletonIdConverter`  
`class SingletonIdConverter : StringIdConverter<SingletonId>`  
_internal*; L28-35_
- inherits: `StringIdConverter<SingletonId>`
- desc: Converter to and from StringId instances.
- L31 _public method_ `public override SingletonId FromStringId(StringId id)` — (inheritdoc)
- L34 _public method_ `public override StringId ToStringId(SingletonId value)` — (inheritdoc)

#### class `HordeServer.Utilities.SingletonBase`  
`public abstract class SingletonBase`  
_public; L40-59_
- desc: Base class for singleton documents
- L46 _public property_ `public SingletonId Id { get; set; }` — attrs: `[BsonId]` — Unique id for this singleton
- L51 _public property_ `public int Revision { get; set; }` — The revision index of this document
- L56-58 _public method_ `public virtual void PostLoad()` — Callback to allow the singleton to fix up itself after being read

#### class `HordeServer.Utilities.SingletonDocumentAttribute`  
`public sealed class SingletonDocumentAttribute : Attribute`  
_public; L65-87_
- attrs: `[AttributeUsage(AttributeTargets.Class)]`
- inherits: `Attribute`
- desc: Attribute specifying the unique id for a singleton document
- L70 _public property_ `public string Id { get; }` — Unique id for the singleton document
- L75 _public property_ `public string? LegacyId { get; }` — ObjectId for the legacy document
- L82-86 _public ctor_ `public SingletonDocumentAttribute(string id, string? legacyId = null)` — Constructor

#### interface `HordeServer.Utilities.ISingletonDocument`  
`public interface ISingletonDocument<T>`  
_public; L93-109_
- desc: Interface for the getting and setting the singleton
- L100 _public* method_ `Task<T> GetAsync(CancellationToken cancellationToken)` — Gets the current document
- L108 _public* method_ `Task<bool> TryUpdateAsync(T value, CancellationToken cancellationToken)` — Attempts to update the document

#### class `HordeServer.Utilities.SingletonDocument`  
`public class SingletonDocument<T> : ISingletonDocument<T> where T : SingletonBase, new()`  
_public; L115-142_
- inherits: `ISingletonDocument<T>`
- constraints: `where T : SingletonBase, new()`
- desc: Concrete implementation of ISingletonDocument{T}
- L120 _private* field_ `readonly IMongoService _mongoService` — The database service instance
- L126-129 _public ctor_ `public SingletonDocument(IMongoService mongoService)` — Constructor
- L132-135 _public method_ `public async Task<T> GetAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L138-141 _public method_ `public Task<bool> TryUpdateAsync(T value, CancellationToken cancellationToken)` — (inheritdoc)

#### class `HordeServer.Utilities.SingletonDocumentExtensions`  
`public static class SingletonDocumentExtensions`  
_public; L147-170_
- desc: Extension methods for singletons
- L157-169 _public method_ `public static async Task<T> UpdateAsync<T>(this ISingletonDocument<T> singleton, Action<T> updateAction, CancellationToken cancellationToken) where T : SingletonBase, new()` — Update a singleton

### `Source/Programs/Horde/HordeServer.Shared/Utilities/StringIdConverter.cs` (HordeServer.Shared)


#### class `HordeServer.Utilities.StringIdBsonSerializer`  
`public sealed class StringIdBsonSerializer<TValue, TConverter> : SerializerBase<TValue> where TValue : struct where TConverter : StringIdConverter<TValue>, new()`  
_public; L15-24_
- inherits: `SerializerBase<TValue>`
- constraints: `where TValue : struct where TConverter : StringIdConverter<TValue>, new()`
- desc: Class which serializes object id types to BSON
- L17 _private* field_ `readonly TConverter _converter = new TConverter()`
- L20 _public method_ `public override TValue Deserialize(BsonDeserializationContext context, BsonDeserializationArgs args)` — (inheritdoc)
- L23 _public method_ `public override void Serialize(BsonSerializationContext context, BsonSerializationArgs args, TValue value)` — (inheritdoc)

#### class `HordeServer.Utilities.StringIdBsonSerializationProvider`  
`public sealed class StringIdBsonSerializationProvider : BsonSerializationProviderBase`  
_public; L29-41_
- inherits: `BsonSerializationProviderBase`
- desc: Class which serializes object id types to BSON
- L32-40 _public method_ `public override IBsonSerializer? GetSerializer(Type type, IBsonSerializerRegistry serializerRegistry)` — (inheritdoc)

#### struct `HordeServer.Utilities.StringIdProto`  
`public struct StringIdProto<TValue, TConverter> where TValue : struct where TConverter : StringIdConverter<TValue>, new()`  
_public; L48-57_
- attrs: `[ProtoContract]`
- constraints: `where TValue : struct where TConverter : StringIdConverter<TValue>, new()`
- desc: Surrogate type for serializing StringId types to ProtoBuf
- L50 _private* field_ `static readonly TConverter s_converter = new TConverter()`
- L53 _public property_ `public string? Id { get; set; }` — attrs: `[ProtoMember(1)]`
- L55 _public operator_ `public static implicit operator TValue(StringIdProto<TValue, TConverter> source)`
- L56 _public operator_ `public static implicit operator StringIdProto<TValue, TConverter>(TValue source)`

### `Source/Programs/Horde/HordeServer.Shared/Utilities/StructuredRpcException.cs` (HordeServer.Shared)


#### class `HordeServer.Utilities.StructuredRpcException`  
`public class StructuredRpcException : RpcException`  
_public; L12-84_
- inherits: `RpcException`
- desc: Exception class designed to allow logging structured log messages
- L17 _public property_ `public string Format { get; }` — The format string with named parameters
- L22 _public property_ `public object[] Args { get; }` — The argument list
- L30-35 _public ctor_ `public StructuredRpcException(StatusCode statusCode, string format, params object[] args) : base(new Status(statusCode, FormatMessage(format, args)))` — Constructor
- L43-47 _private* method_ `static string FormatMessage(string format, params object[] args)` — Replace named arguments in the format message with their values
- L54-83 _private* method_ `static string ConvertToFormatString(string format)` — Converts a named parameter format string to a String.Format style string

### `Source/Programs/Horde/HordeServer.Shared/Utilities/TimeSpanJsonConverter.cs` (HordeServer.Shared)


#### class `HordeServer.Utilities.TimeSpanJsonConverter`  
`public class TimeSpanJsonConverter : JsonConverter<TimeSpan>`  
_public; L12-30_
- inherits: `JsonConverter<TimeSpan>`
- desc: Converter for TimeSpan types to Json
- L15-23 _public method_ `public override TimeSpan Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — (inheritdoc)
- L26-29 _public method_ `public override void Write(Utf8JsonWriter writer, TimeSpan timeSpan, JsonSerializerOptions options)` — (inheritdoc)

### `Source/Programs/Horde/HordeServer.Shared/Utilities/TimeZoneInfoExtensions.cs` (HordeServer.Shared)


#### class `HordeServer.Utilities.TimeZoneInfoExtensions`  
`public static class TimeZoneInfoExtensions`  
_public; L8-22_
- desc: Extension methods for TimeZoneInfo
- L16-21 _public method_ `public static DateTime GetStartOfDayUtc(this TimeZoneInfo timeZone, DateTime time)` — Gets the start of the day for the given datetime in UTC, respecting the configured timezone.

### `Source/Programs/Horde/HordeServer.Shared/Utilities/TryAuthorizeAttribute.cs` (HordeServer.Shared)


#### class `HordeServer.Utilities.TryAuthorizeAttribute`  
`public sealed class TryAuthorizeAttribute : Attribute, IAsyncAuthorizationFilter`  
_public; L14-25_
- attrs: `[AttributeUsage(AttributeTargets.Method | AttributeTargets.Class)]`
- inherits: `Attribute, IAsyncAuthorizationFilter`
- desc: Attempts to authorize the user, but does not challenge or forbid access if authorization fails.
- L17-24 _public method_ `public async Task OnAuthorizationAsync(AuthorizationFilterContext context)` — (inheritdoc)
