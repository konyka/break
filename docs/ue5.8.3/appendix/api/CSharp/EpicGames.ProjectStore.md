# CSharp / EpicGames.ProjectStore

- project root: `Source/Programs/Shared/EpicGames.ProjectStore`
- files: 5; symbols: 266
- symbol kinds: class=21, ctor=13, delegate=1, enum=4, enumerator=29, field=19, interface=1, method=88, property=82, record=5, record struct=3
- access marked `*` is implicit (not written in source)

### `Source/Programs/Shared/EpicGames.ProjectStore/CloudStorage/CloudStorage.cs` (EpicGames.ProjectStore)


#### class `EpicGames.ProjectStore.CloudStorage`  
`public class CloudStorage : ICloudStorage`  
_public; L27-782_
- inherits: `ICloudStorage`
- desc: (inheritdoc)
- L29 _private field_ `private readonly IOptionsSnapshot<CloudStorageOptions> _options`
- L30 _private field_ `private readonly ILogger<CloudStorage> _logger`
- L31 _private field_ `private readonly IServiceProvider _provider`
- L60 _private* field_ `static readonly Regex s_logLinePattern = new(@"\[.*\]\s?\[(?<severity>warning|error|info)\]\s?(\[(?<file>\S+)\:(?<line>\d+)\])?(?<message>.*)")`
- L64-69 _public ctor_ `public CloudStorage(IOptionsSnapshot<CloudStorageOptions> options, ILogger<CloudStorage> logger, IServiceProvider provider)` — CTOR
- L72-94 _public method_ `public async Task<ICloudStorage.LoggedInStatus> LoginAsync(bool unattended = true, CloudBuildOptionsOverride? optionsOverride = null)` — (inheritdoc)
- L96-145 _private method_ `private async Task<string?> GetAccessTokenAsync(bool unattended = true, CloudBuildOptionsOverride? optionsOverride = null)`
- L148-152 _public method_ `public Task DownloadBuildAsync(StringId bucketId, CbObjectId buildId, DirectoryReference outputDir, List<FilePattern>? includeFiles = null, List<FilePattern>? excludeFiles = null, CloudBuildDownloadOptions? downloadOptions = null, IProgress<(float, string)>? progress = null, CloudBuildOptionsOverride? optionsOverride = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L155-159 _public method_ `public Task DownloadBuildAsyncEx(StringId bucketId, CbObjectId buildId, DirectoryReference outputDir, List<string>? includeFiles = null, List<string>? excludeFiles = null, CloudBuildDownloadOptions? downloadOptions = null, IProgress<(float, string)>? progress = null, CloudBuildOptionsOverride? optionsOverride = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L162-165 _public method_ `public void DownloadBuild(StringId bucketId, CbObjectId buildId, DirectoryReference outputDir, List<FilePattern>? includeFiles = null, List<FilePattern>? excludeFiles = null, CloudBuildDownloadOptions? downloadOptions = null, IProgress<(float, string)>? progress = null, CloudBuildOptionsOverride? optionsOverride = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L168-171 _public method_ `public void DownloadBuildEx(StringId bucketId, CbObjectId buildId, DirectoryReference outputDir, List<string>? includeFiles = null, List<string>? excludeFiles = null, CloudBuildDownloadOptions? downloadOptions = null, IProgress<(float, string)>? progress = null, CloudBuildOptionsOverride? optionsOverride = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L174-193 _public method_ `public Task DownloadBuildFromUriAsync(Uri uri, DirectoryReference outputDir, List<FilePattern>? includeFiles = null, List<FilePattern>? excludeFiles = null, CloudBuildDownloadOptions? downloadOptions = null, IProgress<(float, string)>? progress = null, CloudBuildOptionsOverride? optionsOverride = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L195-202 _private method_ `private async Task DownloadBuildAsync(NamespaceId? namespaceId, StringId bucketId, CbObjectId buildId, DirectoryReference outputDir, List<FilePattern>? includeFiles, List<FilePattern>? excludeFiles, CloudBuildDownloadOptions? downloadOptions = null, IProgress<(float, string)>? progress = null, CloudBuildOptionsOverride? optionsOverride = null, CancellationToken cancellationToken = default)`
- L204-228 _private method_ `private async Task DownloadBuildAsync(NamespaceId? namespaceId, StringId bucketId, CbObjectId buildId, DirectoryReference outputDir, IEnumerable<string>? includeFiles, IEnumerable<string>? excludeFiles, CloudBuildDownloadOptions? downloadOptions = null, IProgress<(float, string)>? progress = null, CloudBuildOptionsOverride? optionsOverride = null, CancellationToken cancellationToken = default)`
- L230-248 _private method_ `private static string ToZenWildcard(DirectoryReference outputDirectory, FilePattern filePattern)`
- L251-363 _public method_ `public IEnumerable<FindBuildResponse> FindBuilds(Regex bucketRegex, CbObject query, CloudBuildSearchOptions? searchOptions = null, CloudBuildOptionsOverride? optionsOverride = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L366-374 _public method_ `public async IAsyncEnumerable<FindBuildResponse> FindBuildsAsync(Regex bucketRegex, CbObject query, CloudBuildSearchOptions? searchOptions = null, CloudBuildOptionsOverride? optionsOverride = null, [EnumeratorCancellation] CancellationToken cancellationToken = default)` — (inheritdoc)
- L376-390 _private method_ `private static Regex BuildRegex(string project, string? type, string? branch)`
- L393-398 _public method_ `public IAsyncEnumerable<FindBuildResponse> FindBuildsAsync(string project, string? type, string? branch, CbObject query, CloudBuildSearchOptions? searchOptions = null, CloudBuildOptionsOverride? optionsOverride = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L401-406 _public method_ `public IEnumerable<FindBuildResponse> FindBuilds(string project, string? type, string? branch, CbObject query, CloudBuildSearchOptions? searchOptions = null, CloudBuildOptionsOverride? optionsOverride = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L408-416 _private method_ `private static ZenExitCodes AsZenExitCodeValue(int exitCode)`
- L419-516 _public method_ `public async Task<BuildContents> ListBuildContentsAsync(StringId bucketId, CbObjectId buildId, CloudBuildOptionsOverride? optionsOverride = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L518-526 _private method_ `private void EnsureZenExitCodeSuccess(int exitCode)`
- L529-537 _public method_ `public Task Reconfigure(Action<CloudStorageOptions> action)` — (inheritdoc)
- L540-543 _public method_ `public string? GetCurrentNamespace(CloudBuildOptionsOverride? optionsOverride)` — (inheritdoc)
- L546-583 _public method_ `public async Task ImportSnapshotAsync(string localFileName, string localRootPath, string engineDir, string cookedPlatformDir, bool forceImport = false, bool asyncImport = false, CancellationToken cancellationToken = default)` — (inheritdoc)
- L585-708 _private method_ `private async Task<int> RunZenCliAsync(string cmdline, IProgress<(float, string)>? progress = null, CloudBuildOptionsOverride? optionsOverride = null, CancellationToken cancellationToken = default)`
- L710-750 _private method_ `private async Task<int> RunProcessAsync(string cmd, string arguments, string? workingDirectory = null, Dictionary<string, string>? env = null, IProgress<(float, string)>? progress = null, bool echoStdout = false, ILogger? echoLogger = null, CancellationToken cancellationToken = default)`
- L752-781 _private method_ `private static void EchoToLogger(ILogger zenLogger, string line)`

#### enum `EpicGames.ProjectStore.CloudStorage.ZenExitCodes`  
`private enum ZenExitCodes`  
_private; L36-58_
- desc: Zens documented exit codes
- L38 _public* enumerator_ `Success = 0`
- L39 _public* enumerator_ `OtherError = 1`
- L40 _public* enumerator_ `BadInput = 2`
- L41 _public* enumerator_ `OutOfMemory = 16`
- L42 _public* enumerator_ `OutOfDisk = 17`
- L43 _public* enumerator_ `AssertError = 70`
- L44 _public* enumerator_ `HttpOtherClientError = 80`
- L45 _public* enumerator_ `HttpCantConnectError = 81`
- L46 _public* enumerator_ `HttpNotFound = 66`
- L47 _public* enumerator_ `HttpUnauthorized = 77`
- L48 _public* enumerator_ `HttpSLLError = 82`
- L49 _public* enumerator_ `HttpForbidden = 83`
- L50 _public* enumerator_ `HttpTimeout = 84`
- L51 _public* enumerator_ `HttpConflict = 85`
- L52 _public* enumerator_ `HttpNoHost = 86`
- L53 _public* enumerator_ `HttpOtherServerError = 90`
- L54 _public* enumerator_ `HttpInternalServerError = 91`
- L55 _public* enumerator_ `HttpServiceUnavailable = 69`
- L56 _public* enumerator_ `HttpBadGateway = 92`
- L57 _public* enumerator_ `HttpGatewayTimeout = 93`

### `Source/Programs/Shared/EpicGames.ProjectStore/CloudStorage/CloudStorageExtensions.cs` (EpicGames.ProjectStore)


#### class `EpicGames.ProjectStore.CloudStorageExtensions`  
`public static class CloudStorageExtensions`  
_public; L11-37_
- desc: Extension methods for Cloud Storage
- L17-25 _public method_ `public static void AddCloudStorage(this IServiceCollection serviceCollection)` — Adds Cloud Storage-related services with the default settings
- L32-36 _public method_ `public static void AddCloudStorage(this IServiceCollection serviceCollection, Action<CloudStorageOptions> configureCloudStorage)` — Adds Cloud Storage-related services with configuration

### `Source/Programs/Shared/EpicGames.ProjectStore/CloudStorage/CloudStorageQueryBuilder.cs` (EpicGames.ProjectStore)


#### class `EpicGames.ProjectStore.CloudStorageQueryBuilder`  
`public class CloudStorageQueryBuilder`  
_public; L12-199_
- desc: Helper class to build a query for finding builds using cloud storage
- L14 _private field_ `private readonly CbWriter _writer = new()`
- L15 _private field_ `private CbObject? _generatedObject = null`
- L20-24 _public ctor_ `public CloudStorageQueryBuilder()` — CTOR
- L32-39 _public method_ `public void Equals<T>(string fieldName, T value)` — Search for exact value in a field
- L47-54 _public method_ `public void NotEquals<T>(string fieldName, T value)` — Search for any value except value in a field
- L62-69 _public method_ `public void LessThen<T>(string fieldName, T value)` — Search for any value less than, type must be able to be compared
- L77-84 _public method_ `public void LessThenOrEqual<T>(string fieldName, T value)` — Search for any value less than or equal, type must be able to be compared
- L92-99 _public method_ `public void GreaterThen<T>(string fieldName, T value)` — Search for any value greater than, type must be able to be compared
- L107-114 _public method_ `public void GreaterThenOrEqual<T>(string fieldName, T value)` — Search for any value greater than or equal, type must be able to be compared
- L122-134 _public method_ `public void In<T>(string fieldName, IEnumerable<T> values)` — Search for any of the exact values in a list
- L142-154 _public method_ `public void NotIn<T>(string fieldName, IEnumerable<T> values)` — Search for any of the exact values to not be in this list
- L160-171 _public method_ `public CbObject Done()` — Returns the built query and locks the builder to prevent further appended filters
- L173-190 _private method_ `private void WriteValue<T>(string? fieldName, T value)`
- L192-198 _private method_ `private void ThrowOnLocked()`

### `Source/Programs/Shared/EpicGames.ProjectStore/CloudStorage/ICloudStorage.cs` (EpicGames.ProjectStore)


#### record `EpicGames.ProjectStore.FindBuildResponse`  
`public record FindBuildResponse( string Name, CbObjectId BuildId, StringId BucketId, string? Commit, DateTime CreatedAt, CbObject Metadata)`  
_public; L28-65_
- desc: A build found during search
- L39 _public property_ `public CbObjectId BuildId { get; init; }` — The globally unique id of the build
- L44 _public property_ `public StringId BucketId { get; init; }` — Which bucket the build is in
- L49 _public property_ `public string? Commit { get; init; }` — The commit identifier as defined in source control typically an incrementing number (changelist) or hash (git commit), can be null if missing
- L54 _public property_ `public string Name { get; init; }` — The name of the build
- L59 _public property_ `public DateTime CreatedAt { get; init; }` — When the build was created
- L64 _public property_ `public CbObject Metadata { get; init; }` — The metadata of the build

#### record struct `EpicGames.ProjectStore.PartContents`  
`public readonly record struct PartContents(string PartName, CbObjectId PartId, ulong TotalSize, Dictionary<string, FileDescription> Files)`  
_public; L70-91_
- desc: The contents available for a part
- L75 _public property_ `public required string PartName { get; init; }` — The name of the part
- L80 _public property_ `public CbObjectId PartId { get; init; }` — The id of the part, usually used in apis to uniquely identify this part
- L85 _public property_ `public required ulong TotalSize { get; init; }` — The total uncompressed size of the part
- L90 _public property_ `public required Dictionary<string, FileDescription> Files { get; init; }` — All the files in the part

#### record struct `EpicGames.ProjectStore.FileDescription`  
`public readonly record struct FileDescription(IoHash RawHash, ulong RawSize, int Attributes, int Mode)`  
_public; L96-117_
- desc: Description of an individual file
- L101 _public property_ `public required IoHash RawHash { get; init; }` — Hash of uncompressed content
- L106 _public property_ `public required ulong RawSize { get; init; }` — Size of the file before compression
- L111 _public property_ `public required int Attributes { get; init; }` — Windows file attributes applied to the file
- L116 _public property_ `public required int Mode { get; init; }` — Linux/Mac attributes applied to the file

#### record struct `EpicGames.ProjectStore.BuildContents`  
`public record struct BuildContents`  
_public; L122-128_
- desc: The contents available for a build
- L127 _public property_ `public required Dictionary<string, PartContents> Parts { get; init; }` — Each part of the build

#### record `EpicGames.ProjectStore.CloudBuildSearchOptions`  
`public record CloudBuildSearchOptions`  
_public; L133-154_
- desc: Options passed to the search
- L138 _public property_ `public int? Limit { get; set; }` — Max number of builds returned
- L143 _public property_ `public int? Skip { get; set; }` — Number of builds to skip before returning result, useful to paginate results
- L148 _public property_ `public int? Max { get; set; }` — Max number of builds considered in the search request, you will usually want Limit rather then Max
- L153 _public property_ `public bool? IncludeTTL { get; set; }` — Set to true to include how long the build will live, makes the search slower

#### record `EpicGames.ProjectStore.CloudBuildOptionsOverride`  
`public record CloudBuildOptionsOverride`  
_public; L159-185_
- desc: Per command overrides of common options
- L164 _public property_ `public string? DefaultHost { get; set; }` — Override which host is being used by default for this command, this host is used with service discovery to determine optimal host for this invocation
- L169 _public property_ `public string? OverrideHost { get; set; }` — Explicitly define which host to use ignoring any service discovery, only use this is you explicitly want to hit a specific host
- L174 _public property_ `public NamespaceId? NamespaceId { get; set; }` — Override which namespace is being used
- L179 _public property_ `public string? AccessToken { get; set; }` — Override the access token used for auth
- L184 _public property_ `public ILogger? EchoLogger { get; set; }` — Logger to echo output to, echo log to output option must also be set. If this logger is not provided but that option is set a global ZenCli logger is used instead

#### record `EpicGames.ProjectStore.CloudBuildDownloadOptions`  
`public record CloudBuildDownloadOptions`  
_public; L190-232_
- desc: Advanced options for downloading builds
- L195 _public property_ `public bool? AllowMultipart { get; set; }` — Set to override if we allow usage of multipart downloads
- L200 _public property_ `public bool AssumeHttp2 { get; set; }` — Set to opt out of http upgrade - needed if using http2 without TLS
- L205 _public property_ `public bool BoostWorkers { get; set; }` — Set to boost the number of worker threads used by zen. Will usually speed up downloads if there is CPU capacity available but can cause you machine to become unresponsive
- L210 _public property_ `public bool BoostWorkerMemory { get; set; }` — Set to increase memory used by workers when BoostWorkers is enabled to reduce disk pressure by buffering more in memory
- L215 _public property_ `public FileReference? TraceFile { get; set; }` — Optional path to an utrace file, if specified Zen will output its utrace file here
- L220 _public property_ `public DirectoryReference? ZenStateFolder { get; set; }` — Override directory location for the zen state folder
- L226 _public property_ `public bool Append { get; set; }` — Whether to append downloads to an existing directory (true) or to clear the directory before download (false) Set this to true if you want to download an artifact to a directory, then download an additional artifact from another without wiping state between
- L231 _public property_ `public bool Clean { get; set; }` — Delete all data in target folder that is not part of the downloaded content

#### class `EpicGames.ProjectStore.CloudStorageException`  
`public class CloudStorageException(string msg) : Exception(msg)`  
_public; L238-238_
- desc: General exception thrown from Cloud Storage

#### interface `EpicGames.ProjectStore.ICloudStorage`  
`public interface ICloudStorage`  
_public; L243-446_
- desc: Interface for interacting with UE Cloud Storage
- L271 _public* method_ `Task<LoggedInStatus> LoginAsync(bool unattended = true, CloudBuildOptionsOverride? optionsOverride = null)` — Login against cloud storage, will trigger an interactive login unless set to unattended
- L286 _public* method_ `Task DownloadBuildAsync(StringId bucketId, CbObjectId buildId, DirectoryReference outputDir, List<FilePattern>? includeFiles = null, List<FilePattern>? excludeFiles = null, CloudBuildDownloadOptions? downloadOptions = null, IProgress<(float, string)>? progress = null, CloudBuildOptionsOverride? optionsOverride = null, CancellationToken cancellationToken = default)` — Download a build using all the required fields
- L300 _public* method_ `Task DownloadBuildAsyncEx(StringId bucketId, CbObjectId buildId, DirectoryReference outputDir, List<string>? includeFiles = null, List<string>? excludeFiles = null, CloudBuildDownloadOptions? downloadOptions = null, IProgress<(float, string)>? progress = null, CloudBuildOptionsOverride? optionsOverride = null, CancellationToken cancellationToken = default)` — Download a build using all the required fields. Ex: Pass file patterns as strings directly to includeFiles and excludeFiles params.
- L315 _public* method_ `void DownloadBuild(StringId bucketId, CbObjectId buildId, DirectoryReference outputDir, List<FilePattern>? includeFiles = null, List<FilePattern>? excludeFiles = null, CloudBuildDownloadOptions? downloadOptions = null, IProgress<(float, string)>? progress = null, CloudBuildOptionsOverride? optionsOverride = null, CancellationToken cancellationToken = default)` — Download a build using all the required fields
- L330 _public* method_ `void DownloadBuildEx(StringId bucketId, CbObjectId buildId, DirectoryReference outputDir, List<string>? includeFiles = null, List<string>? excludeFiles = null, CloudBuildDownloadOptions? downloadOptions = null, IProgress<(float, string)>? progress = null, CloudBuildOptionsOverride? optionsOverride = null, CancellationToken cancellationToken = default)` — Download a build using all the required fields. Ex: Pass file patterns as strings directly to includeFiles and excludeFiles params.
- L344 _public* method_ `Task DownloadBuildFromUriAsync(Uri uri, DirectoryReference outputDir, List<FilePattern>? includeFiles = null, List<FilePattern>? excludeFiles = null, CloudBuildDownloadOptions? downloadOptions = null, IProgress<(float, string)>? progress = null, CloudBuildOptionsOverride? optionsOverride = null, CancellationToken cancellationToken = default)` — Download a build using a single uri value that encodes everything needed to locate the build
- L355 _public* method_ `IAsyncEnumerable<FindBuildResponse> FindBuildsAsync(Regex bucketRegex, CbObject query, CloudBuildSearchOptions? searchOptions = null, CloudBuildOptionsOverride? optionsOverride = null, CancellationToken cancellationToken = default)` — Search for builds in UE Cloud Storage using a regular expression to describe which buckets the build might be in
- L366 _public* method_ `IEnumerable<FindBuildResponse> FindBuilds(Regex bucketRegex, CbObject query, CloudBuildSearchOptions? searchOptions = null, CloudBuildOptionsOverride? optionsOverride = null, CancellationToken cancellationToken = default)` — Search for builds in UE Cloud Storage using a regular expression to describe which buckets the build might be in
- L379 _public* method_ `IAsyncEnumerable<FindBuildResponse> FindBuildsAsync(string project, string? type, string? branch, CbObject query, CloudBuildSearchOptions? searchOptions = null, CloudBuildOptionsOverride? optionsOverride = null, CancellationToken cancellationToken = default)` — Search for builds in UE Cloud Storage using common components
- L392 _public* method_ `IEnumerable<FindBuildResponse> FindBuilds(string project, string? type, string? branch, CbObject query, CloudBuildSearchOptions? searchOptions = null, CloudBuildOptionsOverride? optionsOverride = null, CancellationToken cancellationToken = default)` — Search for builds in UE Cloud Storage using common components
- L402 _public* method_ `Task<BuildContents> ListBuildContentsAsync(StringId bucketId, CbObjectId buildId, CloudBuildOptionsOverride? optionsOverride = null, CancellationToken cancellationToken = default)` — List the contents of a build
- L409 _public* method_ `Task Reconfigure(Action<CloudStorageOptions> action)` — Override the configuration of this instance of cloud storage, mostly useful if you get configuration from another source then the default inis / environment variables
- L416-425 _public* method_ `static string SanitizeBucketValue(string s)` — Helper method to turn a bucket component into a value that is compatible with cloud storage bucket names
- L432 _public* method_ `string? GetCurrentNamespace(CloudBuildOptionsOverride? optionsOverride)` — Returns the current namespace used
- L445 _public* method_ `Task ImportSnapshotAsync(string localFileName, string localRootPath, string engineDir, string cookedPlatformDir, bool forceImport = false, bool asyncImport = false, CancellationToken cancellationToken = default)` — Import a snapshot to the local zen

#### enum `EpicGames.ProjectStore.ICloudStorage.LoggedInStatus`  
`enum LoggedInStatus`  
_public*; L248-263_
- desc: The possible login states
- L253 _public* enumerator_ `LoggedIn` — Has an active access token
- L257 _public* enumerator_ `InteractiveLoginRequired` — No access token found, will require interactive login
- L262 _public* enumerator_ `LoginNotConfigured` — Unattended login specified but no login configuration given

#### record `EpicGames.ProjectStore.CloudStorageOptions`  
`public record CloudStorageOptions : IValidatableObject`  
_public; L451-606_
- inherits: `IValidatableObject`
- desc: Options for cloud storage
- L456 _public property_ `public bool AllowAuthPrompt { get; set; }` — Set too true to allow auth prompts, recommended to set to false for un-interactive scenarios
- L463 _public property_ `public string? Host { get; set; }` — attrs: `[Url] [Required]` — The host name to use to connect to cloud storage
- L469 _public property_ `public string? NamespaceId { get; set; }` — attrs: `[Required]` — The namespace to use when connecting to cloud storage
- L475 _public property_ `public string? BaselineBranch { get; set; }` — attrs: `[Required]` — The Baseline branch to use for builds within cloud storage
- L481 _public property_ `public FileReference? ZenExePath { get; set; }` — attrs: `[Required]` — The path to the zen cli executable
- L486 _public property_ `public FileReference? OidcTokenExePath { get; set; }` — The path to the OidcToken executable
- L491 _public property_ `public string? AccessToken { get; set; }` — The explicit access token to use when communicating with Cloud Storage, it's usually best to not set this and specify the OidcTokenExePath instead to allow for refreshing of tokens if the background task end up long-running
- L496 _public property_ `public bool FetchAccessTokenInProcess { get; set; }` — Set to fetch access token via EpicGames.Oidc instead of using the OidcToken executable. This lets you build a tool that doesn't need to ship the token executable but prevents zen from refreshing the access token as needed so long-running operations can fail
- L501 _public property_ `public Action<ManagedProcess>? OnProcessCreated { get; set; }` — Callback when a process has been created
- L506 _public property_ `public Action<ManagedProcess>? OnProcessExited { get; set; }` — Callback when a process we created has exited
- L511 _public property_ `public bool EchoZenCliToStdout { get; set; }` — Set to true to echo all zencli output to stdout
- L516 _public property_ `public bool EchoZenCliToLog { get; set; }` — Set to true to echo all zen cli logs to a Microsoft.Extensions.Logger called "ZenCli"
- L521 _public property_ `public bool WriteLogEventStatements { get; set; }` — Used to control if log event directives are written into sources that it will consume
- L528-547 _public method_ `public IEnumerable<ValidationResult> Validate(ValidationContext validationContext)` — Implements verification of the settings object for IValidatableObject
- L552-582 _public method_ `public void FindExecutablesFromUnrealRoot()` — Finds paths for executables based on unreal root directory
- L589-605 _internal method_ `internal string GetHostCliArgs(CloudBuildOptionsOverride? optionsOverride)` — Returns the zen cli arguments to use for this set of host arguments

### `Source/Programs/Shared/EpicGames.ProjectStore/ProjectStoreTypes.cs` (EpicGames.ProjectStore)


#### enum `EpicGames.ProjectStore.ZenOperatingMode`  
`public enum ZenOperatingMode`  
_public; L30-40_
- attrs: `[JsonConverter(typeof(JsonStringEnumConverter))]`
- desc: How the client should operate. Whether it should stream from zenserver or use the local filesystem
- L35 _public* enumerator_ `Stream` — Use Zen streaming
- L39 _public* enumerator_ `Filesystem` — Access data from local filesystem

#### class `EpicGames.ProjectStore.ZenServerStoreData`  
`public class ZenServerStoreData`  
_public; L45-88_
- desc: A specification of storage details with zenserver
- L50 _public property_ `public bool IsLocalHost { get; set; }` — Whether zenserver is running locally
- L54 _public property_ `public string? HostName { get; set; }` — The primary or local host name for zenserver
- L58 _public property_ `public List<string> RemoteHostNames { get; }` — The list of remote host names for zenserver
- L62 _public property_ `public int HostPort { get; set; }` — The port for zenserver on the host
- L67 _public property_ `public JsonElement? HostAuth { get; set; }` — Authentication details for connecting to zenserver. Null if no authentication is required. Stored as an opaque JSON object that is passed through from the platform storage.
- L71 _public property_ `public string? ProjectId { get; set; }` — The project identifier for the stored data in zenserver
- L75 _public property_ `public string? OplogId { get; set; }` — The oplog identifier for the stored data in zenserver
- L79 _public property_ `public string? WorkspaceId { get; set; }` — The zen workspace the build's share is available from
- L83 _public property_ `public string? ShareId { get; set; }` — The zen workspace share pointing to the build
- L87 _public property_ `public ZenOperatingMode? OperatingMode { get; set; }` — Selected mode of operation. If missing, assume ZenOperatingMode.Stream

#### class `EpicGames.ProjectStore.ProjectStoreData`  
`public class ProjectStoreData`  
_public; L92-98_
- desc: A desctiptor of a project store
- L97 _public property_ `public ZenServerStoreData? ZenServer { get; set; }` — The details for zenserver for this project store

#### class `EpicGames.ProjectStore.BuildIndexException`  
`public class BuildIndexException : Exception`  
_public; L103-119_
- inherits: `Exception`
- desc: Exception indicating errors when finding or importing snapshots.
- L108 _public ctor_ `public BuildIndexException()` — Default constructor
- L113 _public ctor_ `public BuildIndexException(string message) : base(message)` — Constructor with message
- L118 _public ctor_ `public BuildIndexException(string message, Exception innerException) : base(message, innerException)` — Constructor with message and innerException

#### class `EpicGames.ProjectStore.Build`  
`public abstract class Build`  
_public; L137-408_
- desc: Base class for all builds we could want to import, whether discovered via looking them up in the P:/ drive or discovered via the Unreal Cloud DDC builds API.
- L144 _protected field_ `protected readonly RunAppDelegate RunApp` — Delegate used to run command-line applications
- L151-154 _protected ctor_ `protected Build(RunAppDelegate runApp)` — Constructor.
- L163 _public method_ `public abstract void Import(FileReference projectFile, DirectoryReference platformCookedDirectory, bool forceImport, bool asyncImport)` — Performs snapshot import for the discovered descriptors into a specified project and cooked output directory.
- L175 _public method_ `public abstract void Import(FileReference projectFile, DirectoryReference rootDirectory, DirectoryReference engineDirectory, DirectoryReference platformCookedDirectory, bool forceImport, bool asyncImport)` — Performs snapshot import for the discovered descriptors into a specified project and cooked output directory, using a specified Unreal root/engine directory.
- L180 _public method_ `public abstract int GetChangelist()` — Returns the changelist associated with this snapshot.
- L182-185 _private method_ `private static string[] GetHostAddresses()`
- L190-200 _public method_ `public static JsonSerializerOptions GetDefaultJsonSerializerOptions()` — JSON serialization options for writing to ue.projectstore and reading data from Unreal Cloud.
- L216-224 _protected method_ `protected static string GetProjectID(FileReference projectFile)` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA5351", Justification = "Not using MD5 for cryptographically secure use case")] [System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA1308", Justification = "We know the has` — Returns a project ID of the form {project}.{hash} where {hash} is the first eight bytes of the MD5 hash of the full project filename, lowercased. This matches conventions used by other tooling such as ushell.
- L230-233 _protected method_ `protected void CreateProject(FileReference projectFile)` — Creates a new project in zenserver if it doesn't exist, using the default Unreal root and engine directories.
- L241-248 _protected method_ `protected void CreateProject(FileReference projectFile, DirectoryReference rootDirectory, DirectoryReference engineDirectory)` — Creates a new project in zenserver if it doesn't exist.
- L253-259 _protected method_ `protected static FileReference GetZenExecutable(DirectoryReference engineDirectory)` — Returns a FileReference to the published Zen executable in Engine/Binaries/...
- L266-313 _private method_ `private static JsonElement? GetZenHostAuth()` — Retrieves the Zen host auth data from the platform credential store as an opaque JSON element, matching the storage used by FPlatformMisc::GetStoredValue(TEXT("Epic Games"), TEXT("Zen"), TEXT("HostAuth")). Returns null if no auth data is stored or if reading/parsing fails.
- L321-348 _private method_ `private static string? ReadIniValue(string iniPath, string sectionName, string keyName)` — Reads a value from a UE-style INI file given a section name and key name. Handles UE's quoted-string format: if the value is wrapped in double quotes, the quotes are stripped and escape sequences are processed to match the behavior of FParse::QuotedString / FConfigFile::ShouldExportQuotedString.
- L353-376 _private method_ `private static string UnescapeIniQuotedString(ReadOnlySpan<char> value)` — Unescapes a UE INI quoted string value, matching FParse::QuotedString.
- L384-407 _protected method_ `protected static FileReference WriteProjectStoreFile(string projectId, string platform, DirectoryReference platformCookDirectory)` — Writes a ue.projectstore file for the given project and platform to the platform cooked data directory.

#### class `EpicGames.ProjectStore.Build.LowerCaseNamingPolicy`  
`private class LowerCaseNamingPolicy : JsonNamingPolicy`  
_private; L202-205_
- inherits: `JsonNamingPolicy`
- L204 _public method_ `public override string ConvertName(string name)`

#### class `EpicGames.ProjectStore.FileshareBuild`  
`public class FileshareBuild : Build`  
_public; L413-624_
- inherits: `Build`
- desc: Implementation of Build for builds discovered from snapshot descriptors on the network fileshare.
- L510 _private field_ `private readonly SnapshotDescriptorCollection _snapshotDescriptors = new()`
- L511 _private field_ `private readonly int _changelist`
- L513-522 _private method_ `private void LoadSnapshotDescriptors(string snapshotDescriptorJSON)`
- L530-535 _public ctor_ `public FileshareBuild(string snapshotDescriptorJSON, int changelist, RunAppDelegate runApp) : base(runApp)` — Constructs a fileshare build using a JSON string
- L543-549 _public ctor_ `public FileshareBuild(FileReference snapshotDescriptor, int changelist, RunAppDelegate runApp) : base(runApp)` — Constructs a fileshare build using a snapshot descriptor from a network fileshare.
- L552-555 _public method_ `public override void Import(FileReference projectFile, DirectoryReference platformCookedDirectory, bool forceImport, bool asyncImport)` — (inheritdoc)
- L558-617 _public method_ `public override void Import(FileReference projectFile, DirectoryReference rootDirectory, DirectoryReference engineDirectory, DirectoryReference platformCookedDirectory, bool forceImport, bool asyncImport)` — (inheritdoc)
- L620-623 _public method_ `public override int GetChangelist()` — (inheritdoc)

#### enum `EpicGames.ProjectStore.FileshareBuild.SnapshotStorageType`  
`public enum SnapshotStorageType`  
_public; L418-436_
- desc: Enumeration of different storage options for snapshots.
- L423 _public* enumerator_ `Invalid` — A reserved non-valid storage type for snapshots.
- L427 _public* enumerator_ `Cloud` — Snapshot stored in cloud repositories such as Unreal Cloud DDC.
- L431 _public* enumerator_ `Zen` — Snapshot stored in a zenserver.
- L435 _public* enumerator_ `File` — Snapshot stored as a file on disk.

#### class `EpicGames.ProjectStore.FileshareBuild.SnapshotDescriptor`  
`class SnapshotDescriptor`  
_private*; L441-497_
- desc: Metadata about a snapshot
- L446 _public property_ `public string Name { get; set; }` — Name of the snapshot
- L451 _public property_ `public SnapshotStorageType Type { get; set; }` — Storage type used for the snapshot
- L456 _public property_ `public string TargetPlatform { get; set; }` — Target platform for this snapshot
- L461 _public property_ `public string Host { get; set; }` — For cloud or Zen snapshots, the host they are stored on.
- L466 _public property_ `public string ProjectId { get; set; }` — For Zen snapshots, the project ID to import from.
- L471 _public property_ `public string OplogId { get; set; }` — For Zen snapshots, the oplog ID to import from.
- L476 _public property_ `public string Namespace { get; set; }` — For cloud snapshots, the namespace they are stored in.
- L481 _public property_ `public string Bucket { get; set; }` — For cloud snapshots, the bucket they are stored in.
- L486 _public property_ `public string Key { get; set; }` — For cloud snapshots, the key they are stored in.
- L491 _public property_ `public string Directory { get; set; }` — For file snapshots, the directory it is stored in.
- L496 _public property_ `public string Filename { get; set; }` — For file snapshots, the filename (not including path) that they are stored in.

#### class `EpicGames.ProjectStore.FileshareBuild.SnapshotDescriptorCollection`  
`class SnapshotDescriptorCollection`  
_private*; L502-508_
- desc: A collection of one or more snapshot descriptors
- L507 _public property_ `public List<SnapshotDescriptor> Snapshots { get; set; }` — The list of snapshots contained within this collection.

#### class `EpicGames.ProjectStore.UnrealCloudDDCBuild`  
`public class UnrealCloudDDCBuild : Build`  
_public; L629-705_
- inherits: `Build`
- desc: Implementation of Build for snapshots discovered via the Unreal Cloud DDC builds API.
- L631 _private field_ `private readonly UnrealCloudDDCBuildData _buildData`
- L632 _private field_ `private readonly string _host`
- L633 _private field_ `private readonly string _namespace`
- L634 _private field_ `private readonly string _bucket`
- L635 _private field_ `private readonly string _accessToken`
- L646-654 _public ctor_ `public UnrealCloudDDCBuild(UnrealCloudDDCBuildData buildData, string host, string ns, string bucket, string accessToken, RunAppDelegate runApp) : base(runApp)` — Creates a build that can be used to import the given buildData from an Unreal Cloud host, namespace and bucket.
- L657-660 _public method_ `public override void Import(FileReference projectFile, DirectoryReference platformCookedDirectory, bool forceImport, bool asyncImport)` — (inheritdoc)
- L663-698 _public method_ `public override void Import(FileReference projectFile, DirectoryReference rootDirectory, DirectoryReference engineDirectory, DirectoryReference platformCookedDirectory, bool forceImport, bool asyncImport)` — (inheritdoc)
- L701-704 _public method_ `public override int GetChangelist()` — (inheritdoc)

#### class `EpicGames.ProjectStore.BuildIndex`  
`public abstract class BuildIndex`  
_public; L711-750_
- desc: Base class representing a location we can discover builds from, whether from the P:/ drive or from an Unreal Cloud DDC host's builds API.
- L716-719 _protected ctor_ `protected BuildIndex(RunAppDelegate runApp)`
- L725 _protected field_ `protected readonly RunAppDelegate RunApp` — A delegate used to run command-line apps. See documentation of RunAppDelegate for details.
- L737 _public method_ `public abstract List<int> GetAvailableChangelists(string branch, string project, string platform, string runtime)` — Retrieves a list of changelists for a given branch/project/platform/runtime that can be imported from this build index.
- L749 _public method_ `public abstract Build GetBuild(string branch, string project, string platform, string runtime, int changelist, bool getClosestPreceding)` — Returns a Build which can be used to import the referenced snapshot into zen.

#### class `EpicGames.ProjectStore.FileshareBuildIndex`  
`public class FileshareBuildIndex : BuildIndex`  
_public; L755-854_
- inherits: `BuildIndex`
- desc: Implementation of BuildIndex for builds discovered from a network drive.
- L757 _private field_ `private readonly DirectoryReference _buildRoot`
- L765-781 _public ctor_ `public FileshareBuildIndex(DirectoryReference buildRoot, RunAppDelegate runApp) : base(runApp)`
- L783-813 _private method_ `private DirectoryReference GetBuildsDir(string branch, string project, string platform, string runtime)`
- L816-831 _public method_ `public override List<int> GetAvailableChangelists(string branch, string project, string platform, string runtime)` — (inheritdoc)
- L834-853 _public method_ `public override Build GetBuild(string branch, string project, string platform, string runtime, int changelist, bool getClosestPreceding)` — (inheritdoc)

#### class `EpicGames.ProjectStore.UnrealCloudDDCBuildMetadata`  
`public class UnrealCloudDDCBuildMetadata`  
_public; L859-895_
- desc: Metadata associated with an Unreal Cloud DDC snapshot discovered via the builds API.
- L864 _public property_ `public string Name { get; set; }` — The name of the published snapshot.
- L869 _public property_ `public string Branch { get; set; }` — The branch of the published snapshot.
- L874 _public property_ `public string BaselineBranch { get; set; }` — The baseline branch of the published snapshot.
- L879 _public property_ `public string Platform { get; set; }` — The platform the snapshot is cooked for.
- L884 _public property_ `public string CookPlatform { get; set; }` — The cookPlatform the snapshot is cooked for (includes details such as cook flavor).
- L889 _public property_ `public string Project { get; set; }` — The name of the project the snapshot includes.
- L894 _public property_ `public int Changelist { get; set; }` — The changelist the snapshot was cooked at.

#### class `EpicGames.ProjectStore.UnrealCloudDDCBuildData`  
`public class UnrealCloudDDCBuildData`  
_public; L900-911_
- desc: Data associated with an Unreal Cloud DDC snapshot discovered via the builds API.
- L905 _public property_ `public string BuildId { get; set; }` — The builds ID used to retrieve the snapshot's data.
- L910 _public property_ `public UnrealCloudDDCBuildMetadata Metadata { get; set; }` — The build metadata retrieved from Unreal Cloud.

#### class `EpicGames.ProjectStore.UnrealCloudDDCBuildIndex`  
`public class UnrealCloudDDCBuildIndex : BuildIndex`  
_public; L916-1197_
- inherits: `BuildIndex`
- desc: Implementation of BuildIndex for builds discovered from the Unreal Cloud DDC builds API.
- L918 _private field_ `private readonly string _host`
- L919 _private field_ `private readonly string _namespace`
- L920 _private field_ `private readonly string _accessToken`
- L930-936 _public ctor_ `public UnrealCloudDDCBuildIndex(string host, string ns, string cloudAuthServiceName, RunAppDelegate runApp) : base(runApp)` — Constructs an Unreal Cloud build index that will search the given Unreal Cloud host and namespace. Uses OidcToken.exe to perform authorization with the host.
- L946-952 _public ctor_ `public UnrealCloudDDCBuildIndex(string host, string ns, IOidcTokenInfo accessTokenInfo, RunAppDelegate runApp) : base(runApp)` — Creates an Unreal Cloud build index that will search the given Unreal Cloud host and namespace, using an existing OidcTokenInfo from OidcTokenManager.
- L964-993 _public method_ `public static async Task<UnrealCloudDDCBuildIndex> CreateBuildIndexAsync(string host, string ns, RunAppDelegate runApp, bool allowInteractiveLogin = false)` — Creates an Unreal Cloud build index asynchronously using remote auth configuration provided by a given host.
- L1001-1030 _private method_ `private string GetAccessToken(string cloudAuthServiceName)`
- L1044-1067 _private method_ `private static string GetBucket(string project, string branch, string platform, string runtime)` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA1308", Justification = "We know the provided strings are safe to lowercase using ToLowerInvariant()")]`
- L1076-1122 _public method_ `public List<string> GetAvailablePlatforms(string branch, string project)` — Gets a list of the available platforms this build index can find for a given branch and project.
- L1124-1170 _private method_ `private List<UnrealCloudDDCBuildData> QueryBuilds(string branch, string project, string platform, string runtime, int changelist = 0)`
- L1173-1176 _public method_ `public override List<int> GetAvailableChangelists(string branch, string project, string platform, string runtime)` — (inheritdoc)
- L1179-1196 _public method_ `public override Build GetBuild(string branch, string project, string platform, string runtime, int changelist, bool getClosestPreceding)` — (inheritdoc)

#### class `EpicGames.ProjectStore.UnrealCloudDDCBuildIndex.AccessTokenOutput`  
`class AccessTokenOutput`  
_private*; L995-999_
- L997 _public property_ `public string? Token { get; set; }`
- L998 _public property_ `public string? ExpiresAt { get; set; }`

#### class `EpicGames.ProjectStore.UnrealCloudDDCBuildIndex.QueryBuildsResponse`  
`class QueryBuildsResponse`  
_private*; L1032-1036_
- L1034 _public property_ `public List<UnrealCloudDDCBuildData> Results { get; set; }`
- L1035 _public property_ `public bool PartialResult { get; set; }`

#### class `EpicGames.ProjectStore.UnrealCloudDDCBuildIndex.QueryBucketsResponse`  
`class QueryBucketsResponse`  
_private*; L1038-1041_
- L1040 _public property_ `public List<string> Buckets { get; set; }`

#### Namespace-level symbols

- L130 _public delegate_ `public delegate void RunAppDelegate(string app, string commandLine)` — This is a bit of a hack to avoid depending on CommandUtils, etc from AutomationTool. Calling apps (specifically UAT) may want to control process lifetimes for spawned processes in a way we can't know about here. So we allow them to run any commands we need to run using whatever process-creation function they want, by passing a delegate to the build index.
