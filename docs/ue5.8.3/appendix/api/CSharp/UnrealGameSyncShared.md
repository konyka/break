# CSharp / UnrealGameSyncShared

- project root: `Source/Programs/UnrealGameSync/UnrealGameSyncShared`
- files: 26; symbols: 1164
- symbol kinds: class=81, const=21, ctor=64, dtor=1, enum=12, enumerator=65, event=3, field=116, indexer=1, interface=6, method=420, property=374
- access marked `*` is implicit (not written in source)

### `Source/Programs/UnrealGameSync/UnrealGameSyncShared/ApplicationTheme.cs` (UnrealGameSyncShared)


#### class `UnrealGameSync.ThemeAttribute`  
`sealed class ThemeAttribute : System.Attribute`  
_internal*; L12-15_
- attrs: `[AttributeUsage(System.AttributeTargets.Property)]`
- inherits: `System.Attribute`

#### class `UnrealGameSync.ApplicationTheme`  
`public class ApplicationTheme`  
_public; L17-363_
- L19 _public const_ `public const string LightThemeId = "Light"`
- L20 _public const_ `public const string DarkThemeId = "Dark"`
- L22 _public property_ `public static string DefaultThemeId { get; set; }`
- L24 _private* field_ `static readonly ReadOnlyCollection<Func<ApplicationTheme>> s_defaultThemeConstructors = new ReadOnlyCollection<Func<ApplicationTheme>>(new List<Func<ApplicationTheme>>() { CreateLightTheme, CreateDarkTheme })`
- L26 _public property_ `public string ThemeId { get; init; }`
- L29 _public property_ `public string ThemeName { get; init; }` — attrs: `[Theme]`
- L32 _public property_ `public bool UseDarkMode { get; init; }` — attrs: `[Theme]`
- L34 _public property_ `public bool UseFlatControls { get; init; }` — attrs: `[Theme]`
- L37 _public property_ `public Color ForegroundColor { get; init; }` — attrs: `[Theme]`
- L39 _public property_ `public Color BackgroundColor { get; init; }` — attrs: `[Theme]`
- L42 _public property_ `public Color ActiveCaption { get; init; }` — attrs: `[Theme]`
- L44 _public property_ `public Color ActiveCaptionText { get; init; }` — attrs: `[Theme]`
- L46 _public property_ `public Color InactiveCaption { get; init; }` — attrs: `[Theme]`
- L48 _public property_ `public Color InactiveCaptionText { get; init; }` — attrs: `[Theme]`
- L51 _public property_ `public Color MenuHighlightBGColor { get; init; }` — attrs: `[Theme]`
- L53 _public property_ `public Color MenuHighlightBorderColor { get; init; }` — attrs: `[Theme]`
- L56 _public property_ `public Color TextColor { get; init; }` — attrs: `[Theme]`
- L58 _public property_ `public Color DimmedText { get; init; }` — attrs: `[Theme]`
- L60 _public property_ `public Color LinkColor { get; init; }` — attrs: `[Theme]`
- L62 _public property_ `public Color LinkColorHover { get; init; }` — attrs: `[Theme]`
- L64 _public property_ `public Color LinkColorActive { get; init; }` — attrs: `[Theme]`
- L66 _public property_ `public Color SuccessColor { get; init; }` — attrs: `[Theme]`
- L68 _public property_ `public Color WarningColor { get; init; }` — attrs: `[Theme]`
- L70 _public property_ `public Color ErrorColor { get; init; }` — attrs: `[Theme]`
- L72 _public property_ `public Color StandardNotificationBGTint { get; init; }` — attrs: `[Theme]`
- L74 _public property_ `public Color SuccessNotificationBGTint { get; init; }` — attrs: `[Theme]`
- L76 _public property_ `public Color WarningNotificationBGTint { get; init; }` — attrs: `[Theme]`
- L78 _public property_ `public Color ErrorNotificationBGTint { get; init; }` — attrs: `[Theme]`
- L81 _public property_ `public Color InputBackgroundColor { get; init; }` — attrs: `[Theme]`
- L83 _public property_ `public Color InputBorderColor { get; init; }` — attrs: `[Theme]`
- L86 _public property_ `public Color CodeBadgeColor { get; init; }` — attrs: `[Theme]`
- L88 _public property_ `public Color ContentBadgeColor { get; init; }` — attrs: `[Theme]`
- L91 _public property_ `public Color UEFNBadgeColor { get; init; }` — attrs: `[Theme]`
- L94 _public property_ `public Color SyncBadgeColor { get; init; }` — attrs: `[Theme]`
- L96 _public property_ `public Color SyncHoverBadgeColor { get; init; }` — attrs: `[Theme]`
- L99 _public property_ `public bool ShouldInvertColorBrightness { get; init; }` — attrs: `[Theme]`
- L101 _public method_ `public static string GetThemeConfigSectionName(string themeId)`
- L102-109 _private* method_ `static ApplicationTheme CreateLightTheme()`
- L111-156 _private* method_ `static ApplicationTheme CreateDarkTheme()`
- L158-175 _public method_ `public static Dictionary<string, string> GetThemeList(ConfigFile configFile)`
- L177-196 _public method_ `public static void AddDefaultThemesToConfig(ConfigFile configFile)`
- L198-201 _public method_ `public static bool IsColorLight(Color color)`
- L203-230 _public method_ `public static Color InvertColorBrightness(Color color)`
- L232-241 _public method_ `public static ApplicationTheme? LoadThemeFromConfig(string themeId, ConfigFile configFile)`
- L244-247 _public method_ `public static ApplicationTheme ConstructDefaultTheme()`
- L249-314 _private* ctor_ `ApplicationTheme(string inThemeId, ConfigSection? themeSection = null)`
- L316-352 _public method_ `public void AddThemeToConfig(ConfigFile configFile)`
- L354-362 _public method_ `public Color? CheckInvertColor(Color? color)`

### `Source/Programs/UnrealGameSync/UnrealGameSyncShared/ArchiveInfo.cs` (UnrealGameSyncShared)


#### interface `UnrealGameSync.IArchive`  
`public interface IArchive`  
_public; L22-28_
- L24 _public property_ `public string Key { get; }`
- L25 _public* property_ `bool? RemoveOldBinaries { get; }`
- L27 _public* method_ `Task<bool> DownloadAsync(IPerforceConnection perforce, DirectoryReference localRootPath, FileReference manifestFileName, ILogger logger, ProgressValue progress, CancellationToken cancellationToken)`

#### interface `UnrealGameSync.IArchiveChannel`  
`public interface IArchiveChannel`  
_public; L30-48_
- L32 _public const_ `public const string EditorArchiveType = "Editor"`
- L35 _public* property_ `string Name { get; }`
- L38 _public* property_ `string Type { get; }`
- L41 _public* property_ `string ToolTip { get; }`
- L44 _public* property_ `bool IgnoreRequiredBadges { get; }`
- L46 _public* method_ `bool HasAny()`
- L47 _public* method_ `IArchive? TryGetArchiveForChangeNumber(int changeNumber, int maxChangeNumber)`

#### class `UnrealGameSync.BaseArchiveChannel`  
`public abstract class BaseArchiveChannel : IArchiveChannel`  
_public; L50-95_
- inherits: `IArchiveChannel`
- L52 _public property_ `public string Name { get; }`
- L53 _public property_ `public string Type { get; }`
- L55 _public property_ `public virtual string ToolTip { get; }`
- L57 _public property_ `public bool IgnoreRequiredBadges { get; }`
- L60 _public property_ `public SortedList<int, IArchive> ChangeNumberToArchive { get; }`
- L62-67 _protected ctor_ `protected BaseArchiveChannel(string name, string type, bool bIgnoreRequiredBadges = false)`
- L69-72 _public method_ `public bool HasAny()`
- L74-89 _public method_ `public IArchive? TryGetArchiveForChangeNumber(int changeNumber, int maxChangeNumber)`
- L91-94 _public method_ `public override string ToString()`

#### class `UnrealGameSync.PerforceArchiveChannel`  
`public class PerforceArchiveChannel : BaseArchiveChannel`  
_public; L97-249_
- inherits: `BaseArchiveChannel`
- L99 _public property_ `public string DepotPath { get; set; }`
- L100 _public property_ `public string? Target { get; }`
- L102 _public property_ `public override string ToolTip => ...`
- L105-111 _public ctor_ `public PerforceArchiveChannel(string name, string type, string depotPath, string? target, bool bIgnoreRequiredBadges = false) : base(name, type, bIgnoreRequiredBadges)`
- L113-118 _public method_ `public override bool Equals(object? other)`
- L120-123 _public method_ `public override int GetHashCode()`
- L159-187 _public method_ `public static bool TryParseConfigEntryAsync(string text, [NotNullWhen(true)] out PerforceArchiveChannel? channel)`
- L189-215 _public method_ `public async Task FindArtifactsAsync(IPerforceConnection perforce, CancellationToken cancellationToken)`
- L217-248 _public method_ `public static async Task<List<PerforceArchiveChannel>> GetChannelsAsync(IPerforceConnection perforce, ConfigFile latestProjectConfigFile, string projectIdentifier, CancellationToken cancellationToken)`

#### class `UnrealGameSync.PerforceArchiveChannel.PerforceArchive`  
`class PerforceArchive : IArchive`  
_private*; L125-157_
- inherits: `IArchive`
- L127 _public property_ `public string Key { get; }`
- L128 _public property_ `public bool? RemoveOldBinaries { get; }`
- L130 _public ctor_ `public PerforceArchive(string key)`
- L133-156 _public method_ `public async Task<bool> DownloadAsync(IPerforceConnection perforce, DirectoryReference localRootPath, FileReference manifestFileName, ILogger logger, ProgressValue progress, CancellationToken cancellationToken)`

#### class `UnrealGameSync.HordeArchiveChannel`  
`public class HordeArchiveChannel : BaseArchiveChannel`  
_public; L251-369_
- inherits: `BaseArchiveChannel`
- L253-256 _public ctor_ `public HordeArchiveChannel(string name, string type, bool bIgnoreRequiredBadges = false) : base(name, type, bIgnoreRequiredBadges)`
- L258-263 _public method_ `public override bool Equals(object? other)`
- L265-268 _public method_ `public override int GetHashCode()`
- L325-368 _public method_ `public static async Task<List<HordeArchiveChannel>> GetChannelsAsync(IHordeClient hordeClient, string projectIdentifier, CancellationToken cancellationToken)`

#### class `UnrealGameSync.HordeArchiveChannel.HordeArchive`  
`class HordeArchive : IArchive`  
_private*; L270-323_
- inherits: `IArchive`
- L272 _private* field_ `readonly IHordeClient _hordeClient`
- L273 _private* field_ `readonly ArtifactId _artifactId`
- L275 _public property_ `public string Key { get; }`
- L276 _public property_ `public bool? RemoveOldBinaries { get; }`
- L278-283 _public ctor_ `public HordeArchive(IHordeClient hordeClient, ArtifactId artifactId)`
- L285-307 _public method_ `public async Task<bool> DownloadAsync(IPerforceConnection perforce, DirectoryReference localRootPath, FileReference manifestFileName, ILogger logger, ProgressValue progress, CancellationToken cancellationToken)`
- L309-322 _private method_ `private static async Task GatherFilesForManifestAsync(string directoryPath, IBlobRef<DirectoryNode> directoryRef, ArchiveManifest manifest, DateTime timeStamp, CancellationToken cancellationToken)`

#### class `UnrealGameSync.CloudArchiveChannel`  
`public class CloudArchiveChannel : BaseArchiveChannel`  
_public; L371-554_
- inherits: `BaseArchiveChannel`
- L373 _private field_ `private readonly string _archiveType`
- L374 _private field_ `private readonly string _streamName`
- L376-381 _public ctor_ `public CloudArchiveChannel(string name, string type, string archiveType, string streamName, bool bIgnoreRequiredBadges = false) : base(name, type, bIgnoreRequiredBadges)`
- L383-388 _public method_ `public override bool Equals(object? other)`
- L390-393 _public method_ `public override int GetHashCode()`
- L447-490 _public method_ `public static async Task<List<CloudArchiveChannel>> GetChannelsAsync(ICloudStorage cloudStorage, ConfigFile latestProjectConfigFile, string projectIdentifier, CancellationToken cancellationToken)`
- L492-527 _private method_ `private async Task FindArtifactsAsync(ICloudStorage cloudStorage, string projectIdentifier, string host, string namespaceId, CancellationToken cancellationToken)`
- L529-553 _public method_ `public static bool TryParseConfigEntryAsync(string text, [NotNullWhen(true)] out CloudArchiveChannel? channel)`

#### class `UnrealGameSync.CloudArchiveChannel.CloudArchive`  
`class CloudArchive : IArchive`  
_private*; L395-445_
- inherits: `IArchive`
- L397 _private* field_ `readonly ICloudStorage _cloudStorageClient`
- L398 _private field_ `private readonly string _host`
- L399 _private field_ `private readonly string _namespaceId`
- L400 _private field_ `private readonly string _bucketId`
- L402 _public property_ `public string Key { get; }`
- L403 _public property_ `public bool? RemoveOldBinaries { get; }`
- L405-412 _public ctor_ `public CloudArchive(ICloudStorage cloudStorageClient, string host, string namespaceId, string bucketId, string buildId)`
- L414-444 _public method_ `public async Task<bool> DownloadAsync(IPerforceConnection perforce, DirectoryReference localRootPath, FileReference manifestFileName, ILogger logger, ProgressValue progress, CancellationToken cancellationToken)`

#### class `UnrealGameSync.BaseArchive`  
`public static class BaseArchive`  
_public; L556-595_
- L558 _public field_ `public static readonly HashSet<string> DefaultArchiveSources = new HashSet<string>(StringComparer.OrdinalIgnoreCase) { "perforce", "cloud", "horde" }`
- L560-594 _public method_ `public static async Task<List<BaseArchiveChannel>> EnumerateChannelsAsync( IPerforceConnection perforce, IHordeClient? hordeClient, ICloudStorage? cloudStorage, ConfigFile latestProjectConfigFile, string projectIdentifier, HashSet<string> archiveSources, CancellationToken cancellationToken)`

### `Source/Programs/UnrealGameSync/UnrealGameSyncShared/ArchiveManifest.cs` (UnrealGameSyncShared)


#### class `UnrealGameSync.ArchiveManifestFile`  
`public class ArchiveManifestFile`  
_public; L15-41_
- attrs: `[DebuggerDisplay("{FileName}")]`
- L17 _public property_ `public string FileName { get; }`
- L18 _public property_ `public long Length { get; }`
- L19 _public property_ `public DateTime LastWriteTimeUtc { get; }`
- L21-26 _public ctor_ `public ArchiveManifestFile(BinaryReader reader)`
- L28-33 _public ctor_ `public ArchiveManifestFile(string fileName, long length, DateTime lastWriteTimeUtc)`
- L35-40 _public method_ `public void Write(BinaryWriter writer)`

#### class `UnrealGameSync.ArchiveManifest`  
`public class ArchiveManifest`  
_public; L43-78_
- L45 _private* const_ `const int Signature = ((int)'U' << 24) | ((int)'A' << 16) | ((int)'M' << 8) | 1`
- L47 _public property_ `public List<ArchiveManifestFile> Files { get; }`
- L49-51 _public ctor_ `public ArchiveManifest()`
- L53-66 _public ctor_ `public ArchiveManifest(FileStream inputStream)`
- L68-77 _public method_ `public void Write(FileStream outputStream)`

#### class `UnrealGameSync.ArchiveUtils`  
`public static class ArchiveUtils`  
_public; L80-160_
- L82-126 _public method_ `public static void ExtractFiles(FileReference archiveFileName, DirectoryReference baseDirectoryName, FileReference? manifestFileName, ProgressValue progress, ILogger logger)`
- L128-159 _public method_ `public static void RemoveExtractedFiles(DirectoryReference baseDirectoryName, FileReference manifestFileName, ProgressValue progress, ILogger logWriter)`

### `Source/Programs/UnrealGameSync/UnrealGameSyncShared/ArchiveOverride.cs` (UnrealGameSyncShared)


#### interface `UnrealGameSync.IArchiveOverride`  
`public interface IArchiveOverride`  
_public; L19-22_
- desc: Defines a contract for retrieving an archive changelist number that may override the provided changelist.
- L21 _public* method_ `Task<int> GetChangelistAsync(int changelist)`

#### class `UnrealGameSync.DefaultArchiveOverride`  
`public class DefaultArchiveOverride : IArchiveOverride`  
_public; L28-34_
- inherits: `IArchiveOverride`
- desc: Provides a default implementation of the IArchiveOverride interface that returns the specified changelist without modification.
- L30-33 _public method_ `public Task<int> GetChangelistAsync(int changelist)`

#### class `UnrealGameSync.ArchiveOverrideFromStreamDescription`  
`public partial class ArchiveOverrideFromStreamDescription : IArchiveOverride`  
_public; L44-104_
- inherits: `IArchiveOverride`
- desc: Provides an implementation of the IArchiveOverride interface that determines the changelist override by parsing the Perforce stream description.
- L46 _private field_ `private readonly IPerforceSettings _perforceSettings`
- L47 _private field_ `private readonly ILogger _logger`
- L50 _private method_ `private static partial Regex ImportRegex()` — attrs: `[GeneratedRegex("^\\s*import\\s+\\.\\.\\.")]`
- L53 _private method_ `private static partial Regex ImportCaptureRegex()` — attrs: `[GeneratedRegex("(//[^@]+)@(\\d+)")]`
- L55-59 _public ctor_ `public ArchiveOverrideFromStreamDescription(IPerforceSettings perforceSettings, ILogger logger)`
- L61-103 _public method_ `public async Task<int> GetChangelistAsync(int changelist)`

#### class `UnrealGameSync.ArchiveOverrideFactory`  
`public static class ArchiveOverrideFactory`  
_public; L109-122_
- desc: Provides factory methods for creating instances of archive override implementations.
- L111-121 _public method_ `public static IArchiveOverride Create(string archiveOverride, IPerforceSettings perforceSettings, Microsoft.Extensions.Logging.ILogger logger)`

### `Source/Programs/UnrealGameSync/UnrealGameSyncShared/AsyncDisposer.cs` (UnrealGameSyncShared)


#### interface `UnrealGameSync.IAsyncDisposer`  
`public interface IAsyncDisposer`  
_public; L10-13_
- L12 _public* method_ `void Add(Task task)`

#### class `UnrealGameSync.AsyncDisposer`  
`public class AsyncDisposer : IAsyncDisposer, IAsyncDisposable`  
_public; L15-60_
- inherits: `IAsyncDisposer, IAsyncDisposable`
- L17 _private* field_ `readonly object _lockObject = new object()`
- L18 _private* field_ `readonly List<Task> _tasks = new List<Task>()`
- L19 _private* field_ `readonly ILogger _logger`
- L21-24 _public ctor_ `public AsyncDisposer(ILogger<AsyncDisposer> logger)`
- L26-33 _public method_ `public void Add(Task task)`
- L35-41 _private method_ `private void Remove(Task task)`
- L43-59 _public method_ `public async ValueTask DisposeAsync()`

### `Source/Programs/UnrealGameSync/UnrealGameSyncShared/BuildStep.cs` (UnrealGameSyncShared)


#### enum `UnrealGameSync.BuildStepType`  
`public enum BuildStepType`  
_public; L9-14_
- L11 _public* enumerator_ `Compile`
- L12 _public* enumerator_ `Cook`
- L13 _public* enumerator_ `Other`

#### class `UnrealGameSync.BuildStep`  
`public class BuildStep`  
_public; L17-210_
- attrs: `[DebuggerDisplay("{Description}")]`
- L19 _public const_ `public const string UniqueIdKey = "UniqueId"`
- L21 _public property_ `public Guid UniqueId { get; set; }`
- L22 _public property_ `public int OrderIndex { get; set; }`
- L23 _public property_ `public string? Description { get; set; }`
- L24 _public property_ `public string? StatusText { get; set; }`
- L25 _public property_ `public int EstimatedDuration { get; set; }`
- L26 _public property_ `public BuildStepType Type { get; set; }`
- L27 _public property_ `public string? Target { get; set; }`
- L28 _public property_ `public string? Platform { get; set; }`
- L29 _public property_ `public string? Configuration { get; set; }`
- L30 _public property_ `public string? FileName { get; set; }`
- L31 _public property_ `public string? WorkingDir { get; set; }`
- L32 _public property_ `public string? Arguments { get; set; }`
- L33 _public property_ `public bool UseLogWindow { get; set; }`
- L34 _public property_ `public bool NormalSync { get; set; }`
- L35 _public property_ `public bool ScheduledSync { get; set; }`
- L36 _public property_ `public string? StatusPanelLink { get; set; }`
- L37 _public property_ `public List<Guid> Requires { get; }`
- L38 _public property_ `public List<Guid> LocalCompileRequires { get; }`
- L39 _public property_ `public Guid ToolId { get; set; }`
- L41-53 _public ctor_ `public BuildStep(Guid inUniqueId, int inOrderIndex, string? inDescription, string? inStatusText, int inEstimatedDuration, string? inFileName, string? inArguments, string? inWorkingDir, bool inUseLogWindow)`
- L55-70 _public ctor_ `public BuildStep(Guid inUniqueId, int inOrderIndex, string? inDescription, string? inStatusText, int inEstimatedDuration, string? inTarget, string? inPlatform, string? inConfiguration, string? inArguments, bool inSyncDefault)`
- L72-129 _public ctor_ `public BuildStep(ConfigObject obj)`
- L131-144 _public method_ `public bool IsValid()`
- L146-161 _public method_ `public static void MergeBuildStepObjects(Dictionary<Guid, ConfigObject> buildStepObjects, IEnumerable<ConfigObject> modifyObjects)`
- L163-201 _public method_ `public ConfigObject ToConfigObject()`
- L203-209 _public method_ `public ConfigObject? ToConfigObject(ConfigObject? defaultObject)`

### `Source/Programs/UnrealGameSync/UnrealGameSyncShared/CloudStorage.cs` (UnrealGameSyncShared)


#### class `UnrealGameSync.FoundBuildResponse`  
`public class FoundBuildResponse(string buildName, string buildId, string bucketId, string commit)`  
_public; L28-35_
- desc: A build found during search
- L30 _public property_ `public string BuildId { get; init; }`
- L31 _public property_ `public string BucketId { get; init; }`
- L33 _public property_ `public string Commit { get; init; }`
- L34 _public property_ `public string Name { get; set; }`

#### interface `UnrealGameSync.ICloudStorage`  
`public interface ICloudStorage`  
_public; L40-83_
- desc: Interface for interacting with UE Cloud Storage
- L47 _public* method_ `bool IsEnabled(ConfigFile configFile)` — True if the config file enables cloud storage
- L57 _public* method_ `Task<bool> DownloadBuildFromUriAsync(Uri uri, DirectoryReference outputDir, IProgress<string> progress, CancellationToken cancellationToken)` — Download a build from UE Cloud Storage based on an uri
- L71 _public* method_ `Task<bool> DownloadBuildAsync(string host, string namespaceId, string bucketId, string buildId, DirectoryReference outputDir, DirectoryReference? zenStateDirectory, IProgress<string> progress, CancellationToken cancellationToken)` — Download a build using all the required fields
- L82 _public* method_ `IAsyncEnumerable<FoundBuildResponse> FindBuildAsync(string host, string namespaceId, Regex bucketRegex, CbObject query, CancellationToken cancellationToken)` — Search for builds in UE Cloud Storage using a regular expression to describe which buckets the build might be in

#### class `UnrealGameSync.CloudStorage`  
`class CloudStorage(ILogger<CloudStorage> logger, ITokenStore tokenStore) : ICloudStorage, IDisposable`  
_internal*; L85-367_
- L87 _private field_ `private OidcTokenManager? _tokenManager`
- L88 _private field_ `private string? _providerName`
- L90 _private field_ `private readonly SemaphoreSlim _createOidcTokenSemaphore = new SemaphoreSlim(1, 1)`
- L91-100 _public method_ `public bool IsEnabled(ConfigFile configFile)`
- L102-114 _public method_ `public async Task CreateOidcTokenManagerAsync(Uri uri)`
- L116-134 _public method_ `public async Task<bool> DownloadBuildFromUriAsync(Uri uri, DirectoryReference outputDir, IProgress<string> progress, CancellationToken cancellationToken)`
- L136-150 _public method_ `public async Task<bool> DownloadBuildAsync(string host, string namespaceId, string bucketId, string buildId, DirectoryReference outputDir, DirectoryReference? zenStateDirectory, IProgress<string> progress, CancellationToken cancellationToken)`
- L152-213 _public method_ `public async Task<bool> RunZenCli(string cmdline, string accessToken, IProgress<string> progress, CancellationToken cancellationToken)`
- L215-306 _public method_ `public async IAsyncEnumerable<FoundBuildResponse> FindBuildAsync(string host, string namespaceId, Regex bucketRegex, CbObject query, [EnumeratorCancellation] CancellationToken cancellationToken)`
- L308-347 _private method_ `private async Task<string?> GetAccessToken(Uri uri, bool allowInteractiveLogin = true)`
- L349-355 _private method_ `private void Dispose(bool disposing)`
- L357-361 _public method_ `public void Dispose()`
- L363-366 _private* dtor_ `~CloudStorage()`

#### class `UnrealGameSync.CloudStorageExtensions`  
`public static class CloudStorageExtensions`  
_public; L372-396_
- desc: Extension methods for Cloud Storage
- L378-384 _public method_ `public static void AddCloudStorage(this IServiceCollection serviceCollection)` — Adds Horde-related services with the default settings
- L391-395 _public method_ `public static void AddCloudStorage(this IServiceCollection serviceCollection, Action<CloudStorageOptions> configureHorde)` — Adds Horde-related services

#### class `UnrealGameSync.CloudStorageOptions`  
`public class CloudStorageOptions`  
_public; L398-401_

### `Source/Programs/UnrealGameSync/UnrealGameSyncShared/ConfigFile.cs` (UnrealGameSyncShared)


#### class `UnrealGameSync.ConfigObject`  
`public class ConfigObject`  
_public; L19-310_
- attrs: `[JsonConverter(typeof(ConfigObjectJsonConverter))]`
- L21 _private* const_ `const string ConfigSeparatorCharacters = "(),= \t\""`
- L23 _public property_ `public List<KeyValuePair<string, string>> Pairs { get; }`
- L25-28 _public ctor_ `public ConfigObject()`
- L30-33 _public ctor_ `public ConfigObject(ConfigObject other)`
- L35-39 _public ctor_ `public ConfigObject(string text)`
- L41-45 _public ctor_ `public ConfigObject(ConfigObject baseObject, string text)`
- L47-85 _private* method_ `void ParseConfigString(string text)`
- L87-131 _private* method_ `static string? ParseConfigToken(string text, ref int idx)`
- L133-150 _private* method_ `static string? ParseConfigValueToken(string text, ref int idx)`
- L152-158 _public method_ `public IEnumerable<string> GetKeys()`
- L161-171 _public method_ `public string? GetValue(string key, string? defaultValue = null)` — attrs: `[return: NotNullIfNotNull("defaultValue")]`
- L173-185 _public method_ `public Guid GetValue(string key, Guid defaultValue)`
- L187-199 _public method_ `public int GetValue(string key, int defaultValue)`
- L201-213 _public method_ `public bool GetValue(string key, bool defaultValue)`
- L215-233 _public method_ `public void SetValue(string key, string? value)`
- L235-238 _public method_ `public void SetValue(string key, Guid value)`
- L240-243 _public method_ `public void SetValue(string key, int value)`
- L245-248 _public method_ `public void SetValue(string key, bool value)`
- L250-254 _public indexer_ `public string? this[string key] { get; set; }`
- L256-265 _public method_ `public void SetDefaults(ConfigObject other)`
- L267-276 _public method_ `public void AddOverrides(ConfigObject obj, ConfigObject? defaultObject)`
- L278-304 _public method_ `public string ToString(ConfigObject? baseObject)`
- L306-309 _public method_ `public override string ToString()`

#### class `UnrealGameSync.ConfigObjectJsonConverter`  
`public class ConfigObjectJsonConverter : JsonConverter<ConfigObject>`  
_public; L312-343_
- inherits: `JsonConverter<ConfigObject>`
- L314-332 _public method_ `public override ConfigObject Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)`
- L334-342 _public method_ `public override void Write(Utf8JsonWriter writer, ConfigObject value, JsonSerializerOptions options)`

#### class `UnrealGameSync.ConfigSection`  
`public class ConfigSection`  
_public; L346-538_
- attrs: `[DebuggerDisplay("{Name}")]`
- L348 _public property_ `public string Name { get; set; }`
- L349 _public property_ `public Dictionary<string, string> Pairs { get; }`
- L351 _private field_ `private readonly HashSet<string> _wildCardKeys = new HashSet<string>()`
- L353-356 _public ctor_ `public ConfigSection(string inName)`
- L358-362 _public method_ `public void Clear()`
- L364-367 _public method_ `public void SetValue(string key, int value)`
- L369-372 _public method_ `public void SetValue(string key, long value)`
- L374-377 _public method_ `public void SetValue(string key, bool value)`
- L379-398 _public method_ `public void SetValue(string key, string value, bool fromWildCard = false)`
- L400-403 _public method_ `public bool HasWildCardValue(string key)`
- L405-415 _public method_ `public void SetValues(string key, string[] values)`
- L417-427 _public method_ `public void SetValues(string key, Guid[] values)`
- L429-440 _public method_ `public void AppendValue(string key, string value)`
- L442-445 _public method_ `public void RemoveValue(string key)`
- L447 _public method_ `public int GetValue(string key, int defaultValue)`
- L449-461 _public method_ `public int? GetOptionalIntValue(string key, int? defaultValue)`
- L463-475 _public method_ `public long GetValue(string key, long defaultValue)`
- L477-480 _public method_ `public bool GetValue(string key, bool defaultValue)`
- L483-491 _public method_ `public string? GetValue(string key, string? defaultValue = null)` — attrs: `[return: NotNullIfNotNull("defaultValue")]`
- L493-501 _public method_ `public TEnum GetEnumValue<TEnum>(string key, TEnum defaultValue) where TEnum : struct`
- L504-515 _public method_ `public string[]? GetValues(string key, string[]? defaultValue = null)` — attrs: `[return: NotNullIfNotNull("defaultValue")]`
- L518-537 _public method_ `public Guid[]? GetValues(string key, Guid[]? defaultValue = null)` — attrs: `[return: NotNullIfNotNull("defaultValue")]`

#### class `UnrealGameSync.ConfigFile`  
`public class ConfigFile`  
_public; L540-951_
- L542 _private field_ `private readonly List<ConfigSection> _sections = new List<ConfigSection>()`
- L544-546 _public ctor_ `public ConfigFile()`
- L548-551 _private* method_ `static FileReference GetTempFileName(FileReference fileName)`
- L553-556 _public method_ `public void Load(FileReference fileName)`
- L558-580 _public method_ `public bool TryLoad(FileReference fileName, ILogger logger)`
- L582-634 _public method_ `public void Parse(string[] lines, string? project = null)`
- L636-669 _public method_ `public void Save(FileReference fileName)`
- L671-674 _public method_ `public ConfigSection? FindSection(string name)`
- L676-685 _public method_ `public ConfigSection FindOrAddSection(string name)`
- L687-694 _public method_ `public void RemoveSection(string name)`
- L696-701 _public method_ `public void SetValue(string key, int value)`
- L703-708 _public method_ `public void SetValue(string key, bool value)`
- L710-715 _public method_ `public void SetValue(string key, string value)`
- L717-722 _public method_ `public void SetValues(string key, string[] values)`
- L724-729 _public method_ `public bool GetValue(string key, bool defaultValue)`
- L731-751 _public method_ `public bool GetValue(string key, bool defaultValue, string? projectIdentifier)`
- L753-759 _public method_ `public int GetValue(string key, int defaultValue)`
- L761-781 _public method_ `public int GetValue(string key, int defaultValue, string? projectIdentifier)`
- L783-789 _public method_ `public int? GetOptionalIntValue(string key, int? defaultValue)`
- L791-811 _public method_ `public int? GetOptionalIntValue(string key, int? defaultValue, string? projectIdentifier)`
- L815-820 _public method_ `public string? GetValue(string key, string? defaultValue)` — attrs: `[return: NotNullIfNotNull("defaultValue")]`
- L823-843 _public method_ `public string? GetValue(string key, string? defaultValue, string? projectIdentifier)` — attrs: `[return: NotNullIfNotNull("defaultValue")]`
- L845-850 _public method_ `public TEnum GetEnumValue<TEnum>(string key, TEnum defaultValue) where TEnum : struct`
- L852-872 _public method_ `public TEnum GetEnumValue<TEnum>(string key, TEnum defaultValue, string? projectIdentifier) where TEnum : struct`
- L875-880 _public method_ `public string[]? GetValues(string key, string[]? defaultValue)` — attrs: `[return: NotNullIfNotNull("defaultValue")]`
- L883-911 _public method_ `public string[]? GetValues(string key, string[]? defaultValue, string? projectIdentifier)` — attrs: `[return: NotNullIfNotNull("defaultValue")]`
- L914-919 _public method_ `public Guid[]? GetGuidValues(string key, Guid[]? defaultValue)` — attrs: `[return: NotNullIfNotNull("defaultValue")]`
- L922-950 _public method_ `public Guid[]? GetGuidValues(string key, Guid[]? defaultValue, string? projectIdentifier)` — attrs: `[return: NotNullIfNotNull("defaultValue")]`

### `Source/Programs/UnrealGameSync/UnrealGameSyncShared/ConfigUtils.cs` (UnrealGameSyncShared)


#### class `UnrealGameSync.TargetReceipt`  
`public class TargetReceipt`  
_public; L18-52_
- L20 _public property_ `public string? Configuration { get; set; }`
- L21 _public property_ `public string? Launch { get; set; }`
- L22 _public property_ `public string? LaunchCmd { get; set; }`
- L24-33 _public method_ `public static bool TryRead(FileReference location, DirectoryReference? engineDir, DirectoryReference? projectDir, [NotNullWhen(true)] out TargetReceipt? receipt)`
- L36-51 _private method_ `private static string? ExpandReceiptVariables(string? line, DirectoryReference? engineDir, DirectoryReference? projectDir)` — attrs: `[return: NotNullIfNotNull("line")]`

#### class `UnrealGameSync.ConfigUtils`  
`public static class ConfigUtils`  
_public; L54-1358_
- L56 _public property_ `public static string HostPlatform { get; }`
- L58 _public property_ `public static string HostArchitectureSuffix { get; }`
- L60-74 _private* method_ `static string GetHostPlatform()`
- L76-79 _public method_ `public static Task<ConfigFile> ReadProjectConfigFileAsync(IPerforceConnection perforce, ProjectInfo projectInfo, ILogger logger, CancellationToken cancellationToken)`
- L81-84 _public method_ `public static async Task<ConfigFile> ReadProjectConfigFileAsync(IPerforceConnection perforce, ProjectInfo projectInfo, List<KeyValuePair<FileReference, DateTime>> localConfigFiles, ILogger logger, CancellationToken cancellationToken)`
- L86-148 _public method_ `public static async Task<ConfigFile> ReadProjectConfigFileAsync(IPerforceConnection perforce, string branchClientPath, string selectedClientFileName, string projectIdentifier, DirectoryReference cacheFolder, List<KeyValuePair<FileReference, DateTime>> localConfigFiles, ILogger logger, CancellationToken cancellationToken)`
- L150-199 _public method_ `public static async Task<List<string[]>> ReadConfigFiles(IPerforceConnection perforce, IEnumerable<string> depotPaths, List<KeyValuePair<FileReference, DateTime>> localFiles, DirectoryReference cacheFolder, ILogger logger, CancellationToken cancellationToken)`
- L201-216 _public method_ `public static FileReference GetEditorTargetFile(ProjectInfo projectInfo, ConfigFile projectConfig)`
- L218-222 _public method_ `public static FileReference GetEditorReceiptFile(ProjectInfo projectInfo, ConfigFile projectConfig, BuildConfig config)`
- L224-242 _private method_ `private static List<FileReference> FindTargets(DirectoryReference engineOrProjectDir)`
- L244-259 _public method_ `public static string GetDefaultEditorTargetName(ProjectInfo projectInfo, ConfigFile projectConfigFile)`
- L261-274 _public method_ `public static bool TryReadEditorReceipt(ProjectInfo projectInfo, FileReference receiptFile, [NotNullWhen(true)] out TargetReceipt? receipt)`
- L276-298 _public method_ `public static TargetReceipt CreateDefaultEditorReceipt(ProjectInfo projectInfo, ConfigFile projectConfigFile, BuildConfig configuration)`
- L300-312 _private method_ `private static bool UseSharedEditorReceipt(ProjectInfo projectInfo, ConfigFile projectConfig)`
- L314-327 _public method_ `public static FileReference GetReceiptFile(ProjectInfo projectInfo, ConfigFile projectConfig, FileReference targetFile, string configuration)`
- L329-332 _public method_ `public static FileReference GetReceiptFile(DirectoryReference baseDir, string targetName, string configuration)`
- L334-344 _public method_ `public static FileReference GetReceiptFile(DirectoryReference baseDir, string targetName, string platform, string configuration, string architectureSuffix)`
- L346-382 _public method_ `public static Dictionary<Guid, ConfigObject> GetDefaultBuildStepObjects(ProjectInfo projectInfo, string editorTarget, BuildConfig editorConfig, ConfigFile latestProjectConfigFile, bool shouldSyncPrecompiledEditor)`
- L384-433 _public method_ `public static Dictionary<string, string> GetWorkspaceVariables(ProjectInfo projectInfo, int changeNumber, int codeChangeNumber, TargetReceipt? editorTarget, ConfigFile? projectConfigFile, IPerforceSettings perforceSettings)`
- L435-443 _public method_ `public static Dictionary<string, string> GetWorkspaceVariables(ProjectInfo projectInfo, int changeNumber, int codeChangeNumber, TargetReceipt? editorTarget, ConfigFile? projectConfigFile, IPerforceSettings perforceSettings, IEnumerable<KeyValuePair<string, string>> additionalVariables)`
- L445-483 _public method_ `public static bool TryGetProjectSetting(ConfigFile projectConfigFile, string selectedProjectIdentifier, string name, [NotNullWhen(true)] out string? value)`
- L485-510 _public method_ `public static void GetProjectSettings(ConfigFile projectConfigFile, string selectedProjectIdentifier, string name, List<string> values)`
- L512-554 _public method_ `public static Dictionary<Guid, WorkspaceSyncCategory> GetSyncCategories(ConfigFile projectConfigFile)`
- L556-566 _public method_ `public static bool IsPresetAvailable(ConfigFile? projectConfigFile, string projectIdentifier, string preset)`
- L568-603 _public method_ `public static bool GetDefaultPreset(ConfigFile? projectConfigFile, string projectIdentifier, out string preset)`
- L605-634 _public method_ `public static bool GetForceDefaultPreset(ConfigFile? projectConfigFile, string projectIdentifier, out bool forceDefaultPreset)`
- L636-655 _public method_ `public static bool GetForceSyncBaseContent(ConfigFile? projectConfigFile, string projectIdentifier, out bool forceSyncBaseContent)`
- L657-757 _public method_ `public static IDictionary<string, Preset> GetPresets(ConfigFile? projectConfigFile, string projectIdentifier)`
- L759-771 _public method_ `public static ISet<string> GetAdditionalPathsToSync(ConfigFile latestProjectConfigFile)`
- L773-796 _public method_ `public static ISet<string> GetBaseContentPaths(ConfigFile? projectConfigFile, string projectIdentifier)`
- L798-808 _private* method_ `static IEnumerable<Guid> ParseGuids(IEnumerable<string> values)`
- L810-835 _private method_ `private static async Task<DirectoryReference?> GetLocalRootPathAsync(IPerforceConnection perforce, ILogger logger, CancellationToken cancellationToken)`
- L837-897 _public method_ `public static async Task ExecuteConfigInjectionScriptsAsync( IPerforceConnection perforce, string branchClientPath, string selectedClientFileName, string projectIdentifier, DirectoryReference cacheFolder, ConfigFile configFile, List<KeyValuePair<FileReference, DateTime>> localConfigFiles, ILogger logger, CancellationToken cancellationToken = default)`
- L899-952 _public method_ `public static IDictionary<string, FeatureFlag> GetFeatureFlags(ConfigFile? projectConfigFile, string projectIdentifier)`
- L954-962 _public method_ `public static bool IsFeatureEnabled(IDictionary<string, FeatureFlag> features, string featureName)`
- L964-1195 _private method_ `private static async Task ExecuteSingleInjectionScriptAsync( IPerforceConnection perforce, string branchClientPath, DirectoryReference localRootPath, string selectedClientFileName, string projectIdentifier, DirectoryReference cacheFolder, ConfigFile configFile, List<KeyValuePair<FileReference, DateTime>> localConfigFiles, string relativePath, string scriptArgs, ILogger logger, CancellationToken cancellationToken)`
- L1197-1281 _private method_ `private static (string? interpreter, string? interpreterArgs) GetInterpreterForScript(string scriptPath, ILogger logger)`
- L1283-1316 _private method_ `private static bool IsCommandAvailable(string command)`
- L1318-1357 _private method_ `private static void MakeScriptExecutable(string scriptPath, ILogger logger)`

### `Source/Programs/UnrealGameSync/UnrealGameSyncShared/DeploymentSettings.cs` (UnrealGameSyncShared)


#### class `UnrealGameSync.DeploymentSettings`  
`public partial class DeploymentSettings`  
_public; L18-104_
- desc: This class contains settings for a site-specific deployment of UGS, and is read from the Deployment.json file in the application directory.
- L23 _public property_ `public LauncherUpdateSource UpdateSource { get; set; }` — Default update source for UGS
- L28 _public property_ `public string? HordeUrl { get; set; }` — Url for the Horde server
- L33 _public property_ `public ToolId HordeToolId { get; set; }` — Identifier for the tool to sync from UGS
- L38 _public property_ `public string? ApiUrl { get; set; }` — SQL connection string used to connect to the database for telemetry and review data.
- L43 _public property_ `public string? DefaultPerforceServer { get; set; }` — Default Perforce server to connect to
- L49 _public property_ `public List<string> DefaultIssueApiUrls { get; set; }` — Servers to connect to for issue details by default
- L55 _public property_ `public string? UrlHandleIssueApi { get; set; }` — The issue api to use for URL handler events
- L61 _public property_ `public string? DefaultDepotPath { get; set; }` — Specifies the depot path to sync down the stable version of UGS from, without a trailing slash (eg. //depot/UnrealGameSync/bin). This is a site-specific setting. The UnrealGameSync executable should be located at Release/UnrealGameSync.exe under this path, with any dependent DLLs.
- L66 _public property_ `public string? ToolsDepotPath { get; set; }` — Depot path to sync additional tools from
- L71 _public property_ `public string? SentryDsn { get; set; }` — DSN for sending crash reports to Sentry.
- L76 _public property_ `public bool EnableAlerts { get; set; }` — Whether to allow notifications about build failures
- L78 _public property_ `public bool AllowUEFNProjects { get; set; }`
- L80 _private* field_ `static DeploymentSettings? s_instance`
- L82-103 _public property_ `public static DeploymentSettings Instance { get; }`

### `Source/Programs/UnrealGameSync/UnrealGameSyncShared/FeatureFlag.cs` (UnrealGameSyncShared)


#### class `UnrealGameSync.FeatureFlag`  
`public class FeatureFlag`  
_public; L8-18_
- L10 _public property_ `public string Name { get; set; }`
- L11 _public property_ `public bool Enabled { get; set; }`
- L13-17 _public method_ `public void Import(FeatureFlag ff)`

#### class `UnrealGameSync.FeatureFlagCache`  
`public class FeatureFlagCache`  
_public; L20-38_
- L22 _private property_ `private IDictionary<string, FeatureFlag> Features { get; }`
- L24-27 _public ctor_ `public FeatureFlagCache(IDictionary<string, FeatureFlag> features)`
- L29-37 _public method_ `public bool IsFeatureEnabled(string featureName)`

### `Source/Programs/UnrealGameSync/UnrealGameSyncShared/FileFilter.cs` (UnrealGameSyncShared)


#### enum `UnrealGameSync.FileFilterType`  
`public enum FileFilterType`  
_public; L13-17_
- desc: Indicates whether files which match a pattern should be included or excluded
- L15 _public* enumerator_ `Include`
- L16 _public* enumerator_ `Exclude`

#### class `UnrealGameSync.FileFilter`  
`public class FileFilter`  
_public; L24-424_
- desc: Stores a set of rules, similar to p4 path specifications, which can be used to efficiently filter files in or out of a set. The rules are merged into a tree with nodes for each path fragments and rule numbers in each leaf, allowing tree traversal in an arbitrary order to how they are applied.
- L29 _private* field_ `readonly FileFilterNode _rootNode` — Root node for the tree.
- L34 _private* field_ `readonly FileFilterNode _defaultNode` — The default node, which will match any path
- L39 _private* field_ `readonly List<FileFilterNode> _rules = new List<FileFilterNode>()` — Terminating nodes for each rule added to the filter
- L44-50 _public ctor_ `public FileFilter(FileFilterType defaultType = FileFilterType.Exclude)` — Default constructor
- L56-63 _public ctor_ `public FileFilter(FileFilter other) : this(other._defaultNode.Type)` — Copy constructor
- L69-76 _public ctor_ `public FileFilter(IEnumerable<string> lines) : this()` — Constructs a file filter from a p4-style filespec. Exclude lines are prefixed with a - character.
- L82-92 _public method_ `public void AddRule(string rule)` — Adds an include or exclude rule to the filter
- L99-122 _public method_ `public void AddRule(string rule, params string[] allowTags)` — Adds an include or exclude rule to the filter. The rule may be
- L128-134 _public method_ `public void AddRules(IEnumerable<string> rules)` — Adds several rules to the filter
- L140-146 _public method_ `public void AddRules(IEnumerable<string> rules, params string[] tags)` — Adds several rules in the given lines. Rules may be prefixed with conditions of the syntax {Key=Value, Key2=Value2}, which will be evaluated using variables in the given dictionary before being added.
- L151-169 _public method_ `public void ReadRulesFromFile(string fileName, string sectionName, params string[] allowTags)` — Reads a configuration file split into sections
- L175-178 _public method_ `public void Include(string pattern)` — Adds an include rule to the filter
- L184-190 _public method_ `public void Include(IEnumerable<string> patterns)` — Adds several exclude rules to the filter
- L196-199 _public method_ `public void Exclude(string pattern)` — Adds an exclude rule to the filter
- L205-211 _public method_ `public void Exclude(IEnumerable<string> patterns)` — Adds several exclude rules to the filter
- L218-289 _public method_ `public void AddRule(string pattern, FileFilterType type)` — Adds an include or exclude rule to the filter
- L294-300 _public method_ `public void ExcludeConfidentialFolders()` — Excludes all confidential folders from the filter
- L307-314 _public method_ `public bool Matches(string fileName)` — Determines whether the given file matches the filter
- L321-328 _public method_ `public bool PossiblyMatches(string folderName)` — Determines whether it's possible for anything within the given folder name to match the filter. Useful to early out of recursive file searches.
- L335-338 _public method_ `public IEnumerable<string> ApplyTo(IEnumerable<string> fileNames)` — Applies the filter to each element in a sequence, and returns the list of files that match
- L348-382 _private* method_ `static FileFilterNode FindMatchingNode(FileFilterNode currentNode, string[] tokens, int tokenIdx, FileFilterNode currentBestNode)` — Finds the node which matches a given list of tokens.
- L392-423 _private* method_ `static int HighestPossibleIncludeMatch(FileFilterNode currentNode, string[] tokens, int tokenIdx, int currentBestRuleNumber)` — Returns the highest possible rule number which can match the given list of input tokens, assuming that the list of input tokens is incomplete.

#### class `UnrealGameSync.FileFilterNode`  
`class FileFilterNode`  
_internal*; L429-534_
- desc: Node within a filter tree. Each node matches a single path fragment - a folder or file name, with an include or exclude rule consisting of a sequence of nodes.
- L434 _public field_ `public readonly FileFilterNode? Parent` — Node which this is parented to. Null for the root node.
- L439 _public field_ `public readonly string Pattern` — Pattern to match for this node. May contain * or ? wildcards.
- L444 _public field_ `public int MaxIncludeRuleNumber = -1` — Highest include rule number matched by this node or any child nodes.
- L449 _public field_ `public int MaxExcludeRuleNumber = -1` — Highest exclude rule number matched by this node or any child nodes.
- L454 _public field_ `public List<FileFilterNode> Branches = new List<FileFilterNode>()` — Child branches of this node, distinct by the the pattern for each.
- L459 _public field_ `public int RuleNumber` — If a path matches the sequence of nodes ending in this node, the number of the rule which added it. -1 if this was not the last node in a rule.
- L464 _public field_ `public FileFilterType Type` — Whether a rule terminating in this node should include files or exclude files.
- L469-475 _public ctor_ `public FileFilterNode(FileFilterNode? inParent, string inPattern)` — Default constructor.
- L480-490 _public method_ `public bool IsMatch(string token)` — Determine if the given token matches the pattern in this node
- L495-524 _private* method_ `static bool IsMatch(string token, int tokenIdx, string pattern, int patternIdx)` — Determine if a given token matches a pattern, starting from the given positions within each string.
- L530-533 _public method_ `public override string ToString()` — Debugger visualization

### `Source/Programs/UnrealGameSync/UnrealGameSyncShared/GlobalSettings.cs` (UnrealGameSyncShared)


#### class `UnrealGameSync.FilterSettings`  
`public class FilterSettings`  
_public; L11-54_
- L13 _public property_ `public List<Guid> IncludeCategories { get; init; }`
- L14 _public property_ `public List<Guid> ExcludeCategories { get; init; }`
- L15 _public property_ `public List<string> View { get; init; }`
- L16 _public property_ `public bool? AllProjects { get; set; }`
- L17 _public property_ `public bool? LocalProjects { get; set; }`
- L18 _public property_ `public bool? AllProjectsInSln { get; set; }`
- L19 _public property_ `public bool? UprojectSpecificSln { get; set; }`
- L21-30 _public method_ `public void Reset()`
- L32-39 _public method_ `public void SetCategories(Dictionary<Guid, bool> categories)`
- L41-53 _public method_ `public Dictionary<Guid, bool> GetCategories()`

#### class `UnrealGameSync.GlobalSettings`  
`public class GlobalSettings`  
_public; L56-65_
- L58 _public property_ `public string? LatestVersion { get; set; }`
- L59 _public property_ `public DateTime LastVersionCheck { get; set; }`
- L60 _public property_ `public PerforceSyncOptions Perforce { get; set; }`
- L61 _public property_ `public FilterSettings Filter { get; set; }`
- L62 _public property_ `public bool AutoResolveConflicts { get; set; }`
- L63 _public property_ `public bool AlwaysClobberFiles { get; set; }`
- L64 _public property_ `public bool AlwaysDeleteFiles { get; set; }`

#### class `UnrealGameSync.GlobalSettingsFile`  
`public class GlobalSettingsFile`  
_public; L67-282_
- L69 _public property_ `public FileReference File { get; }`
- L70 _public property_ `public GlobalSettings Global { get; }`
- L72-94 _public method_ `public UserProjectSettings FindOrAddProjectSettings(ProjectInfo projectInfo, UserWorkspaceSettings settings, ILogger logger)`
- L96-98 _protected method_ `protected virtual void ImportProjectSettings(ProjectInfo projectInfo, UserProjectSettings projectSettings)`
- L100-102 _protected method_ `protected virtual void ImportWorkspaceSettings(DirectoryReference rootDir, string clientName, string branchPath, UserWorkspaceSettings workspaceSettings)`
- L104-106 _protected method_ `protected virtual void ImportWorkspaceState(DirectoryReference rootDir, string clientName, string branchPath, WorkspaceState workspaceState)`
- L108-112 _public ctor_ `public GlobalSettingsFile(FileReference file, GlobalSettings global)`
- L114-122 _public method_ `public static GlobalSettingsFile Create(FileReference file)`
- L124-136 _public method_ `public virtual bool Save(ILogger logger)`
- L138-150 _public method_ `public bool Save(ILogger logger, FileReference globalSettingsJsonFile)`
- L152-155 _public method_ `public WorkspaceStateWrapper FindOrAddWorkspaceState(UserWorkspaceSettings settings)`
- L157-165 _public method_ `public WorkspaceStateWrapper FindOrAddWorkspaceState(DirectoryReference rootDir, string clientName, string branchPath)`
- L167-172 _public method_ `public WorkspaceStateWrapper FindOrAddWorkspaceState(ProjectInfo projectInfo, UserWorkspaceSettings settings)`
- L174-191 _public method_ `public UserWorkspaceSettings FindOrAddWorkspaceSettings(DirectoryReference rootDir, string? serverAndPort, string? userName, string clientName, string branchPath, string projectPath, string localPath, ILogger logger)`
- L193-266 _public method_ `public static string[] GetCombinedSyncFilter( Dictionary<Guid, WorkspaceSyncCategory> uniqueIdToFilter, string roleName, IDictionary<string, Preset> roles, FilterSettings globalFilter, FilterSettings workspaceFilter, ConfigSection? perforceSection)`
- L268-281 _private* method_ `static void EnableFilter(Guid uniqueId, HashSet<Guid> enabled, Dictionary<Guid, WorkspaceSyncCategory> uniqueIdToFilter)`

### `Source/Programs/UnrealGameSync/UnrealGameSyncShared/LauncherSettings.cs` (UnrealGameSyncShared)


#### enum `UnrealGameSync.LauncherUpdateSource`  
`public enum LauncherUpdateSource`  
_public; L12-18_
- L14 _public* enumerator_ `Unknown = 0`
- L15 _public* enumerator_ `Perforce = 1`
- L16 _public* enumerator_ `Horde = 2`
- L17 _public* enumerator_ `None = 3`

#### class `UnrealGameSync.LauncherSettings`  
`public class LauncherSettings`  
_public; L20-154_
- L22 _public property_ `public LauncherUpdateSource UpdateSource { get; set; }`
- L24 _public property_ `public string? HordeServer { get; set; }`
- L26 _public property_ `public string? PerforceServerAndPort { get; set; }`
- L27 _public property_ `public string? PerforceUserName { get; set; }`
- L28 _public property_ `public string? PerforceDepotPath { get; set; }`
- L30 _public property_ `public bool PreviewBuild { get; set; }`
- L32-38 _public ctor_ `public LauncherSettings()`
- L40-49 _public ctor_ `public LauncherSettings(LauncherSettings other)`
- L51-57 _public method_ `public void Read()`
- L60-95 _private* method_ `void ReadFromRegistry()` — attrs: `[SupportedOSPlatform("windows")]`
- L97-111 _public method_ `public bool Save()`
- L114-140 _private* method_ `void SaveToRegistry()` — attrs: `[SupportedOSPlatform("windows")]`
- L143-153 _private* method_ `static void SaveRegistryValue(RegistryKey key, string name, string? value, string? defaultValue)` — attrs: `[SupportedOSPlatform("windows")]`

### `Source/Programs/UnrealGameSync/UnrealGameSyncShared/OpenProjectInfo.cs` (UnrealGameSyncShared)


#### class `UnrealGameSync.OpenProjectInfo`  
`public class OpenProjectInfo`  
_public; L15-353_
- L17 _public property_ `public UserSelectedProjectSettings SelectedProject { get; }`
- L19 _public property_ `public IPerforceSettings PerforceSettings { get; }`
- L20 _public property_ `public ProjectInfo ProjectInfo { get; }`
- L21 _public property_ `public UserWorkspaceSettings WorkspaceSettings { get; }`
- L22 _public property_ `public WorkspaceStateWrapper WorkspaceStateWrapper { get; }`
- L23 _public property_ `public ConfigFile LatestProjectConfigFile { get; }`
- L24 _public property_ `public ConfigFile WorkspaceProjectConfigFile { get; }`
- L25 _public property_ `public IReadOnlyList<string>? WorkspaceProjectStreamFilter { get; }`
- L26 _public property_ `public List<KeyValuePair<FileReference, DateTime>> LocalConfigFiles { get; }`
- L27 _public property_ `public bool GenerateP4Config { get; }`
- L29-42 _public ctor_ `public OpenProjectInfo(UserSelectedProjectSettings selectedProject, IPerforceSettings perforceSettings, ProjectInfo projectInfo, UserWorkspaceSettings workspaceSettings, WorkspaceStateWrapper workspaceStateWrapper, ConfigFile latestProjectConfigFile, ConfigFile workspaceProjectConfigFile, IReadOnlyList<string>? workspaceProjectStreamFilter, List<KeyValuePair<FileReference, DateTime>> localConfigFiles, bool generateP4Config)`
- L44-58 _public method_ `public static async Task<OpenProjectInfo> CreateAsync(IPerforceSettings defaultPerforceSettings, UserSelectedProjectSettings selectedProject, UserSettings userSettings, bool generateP4Config, ILogger<OpenProjectInfo> logger, CancellationToken cancellationToken)`
- L60-258 _public method_ `public static async Task<OpenProjectInfo> CreateAsync(IPerforceConnection defaultConnection, UserSelectedProjectSettings selectedProject, UserSettings userSettings, bool generateP4Config, ILogger<OpenProjectInfo> logger, CancellationToken cancellationToken)`
- L260-307 _private* method_ `static async Task<List<IPerforceSettings>> FilterClients(List<ClientsRecord> clients, FileReference newSelectedFileName, IPerforceSettings defaultPerforceSettings, string? hostName, ILogger logger, CancellationToken cancellationToken)`
- L309-352 _private* method_ `static void GenerateP4ConfigFile(IPerforceSettings perforceSettings, ProjectInfo projectInfo, ILogger<OpenProjectInfo> logger)`

### `Source/Programs/UnrealGameSync/UnrealGameSyncShared/OutputAdapters.cs` (UnrealGameSyncShared)


#### class `UnrealGameSync.PrefixedTextWriter`  
`class PrefixedTextWriter : ILogger`  
_internal*; L10-29_
- inherits: `ILogger`
- L12 _private* field_ `readonly string _prefix`
- L13 _private* field_ `readonly ILogger _inner`
- L15-19 _public ctor_ `public PrefixedTextWriter(string inPrefix, ILogger inInner)`
- L21 _public method_ `public IDisposable? BeginScope<TState>(TState state) where TState : notnull`
- L23 _public method_ `public bool IsEnabled(LogLevel logLevel)`
- L25-28 _public method_ `public void Log<TState>(LogLevel logLevel, EventId eventId, TState state, Exception? exception, Func<TState, Exception?, string> formatter)`

### `Source/Programs/UnrealGameSync/UnrealGameSyncShared/PostSyncExtension.cs` (UnrealGameSyncShared)


#### class `UnrealGameSync.PostSyncExtension`  
`internal class PostSyncExtension : IDisposable`  
_internal; L14-119_
- inherits: `IDisposable`
- L16 _private field_ `private readonly WorkspaceUpdateContext Context`
- L18 _private field_ `private readonly IPerforceConnection Perforce`
- L20 _private field_ `private readonly ProjectInfo Project`
- L22 _private field_ `private readonly FileReference ConfigTempFile`
- L23 _private field_ `private readonly FileReference GlobalSettingsJsonFile`
- L24 _private field_ `private readonly FileReference GlobalSettingsIniFile`
- L25 _private field_ `private readonly FileReference WorkspaceSettingsFile`
- L26 _private field_ `private readonly FileReference ProjectSettingsFile`
- L28 _private field_ `private readonly List<FileReference> TempFiles = new List<FileReference>()`
- L30-55 _public ctor_ `public PostSyncExtension(ILogger logger, WorkspaceUpdateContext context, IPerforceConnection perforce, ProjectInfo project)`
- L57-103 _public method_ `public async Task<Dictionary<string, string>> ExpandAsync(string step, Dictionary<string, string> postSyncVariables, CancellationToken cancellationToken)`
- L105-118 _public method_ `public void Dispose()`

### `Source/Programs/UnrealGameSync/UnrealGameSyncShared/Preset.cs` (UnrealGameSyncShared)


#### class `UnrealGameSync.RoleCategory`  
`public class RoleCategory`  
_public; L8-12_
- L10 _public property_ `public Guid Id { get; set; }`
- L11 _public property_ `public bool Enabled { get; set; }`

#### class `UnrealGameSync.Preset`  
`public class Preset`  
_public; L14-40_
- L16 _public property_ `public string Name { get; set; }`
- L17 _public property_ `public IDictionary<Guid, RoleCategory> Categories { get; }`
- L18 _public property_ `public ISet<string> Views { get; }`
- L20-39 _public method_ `public void Import(Preset preset)`

### `Source/Programs/UnrealGameSync/UnrealGameSyncShared/Telemetry.cs` (UnrealGameSyncShared)


#### interface `UnrealGameSync.ITelemetrySink`  
`public interface ITelemetrySink : IDisposable`  
_public; L21-29_
- inherits: `IDisposable`
- desc: Interface for a telemetry sink
- L28 _public* method_ `void SendEvent(string eventName, object attributes)` — Sends a telemetry event with the given information

#### class `UnrealGameSync.NullTelemetrySink`  
`public sealed class NullTelemetrySink : ITelemetrySink`  
_public; L34-45_
- inherits: `ITelemetrySink`
- desc: Telemetry sink that discards all events
- L37-39 _public method_ `public void Dispose()` — (inheritdoc)
- L42-44 _public method_ `public void SendEvent(string eventName, object attributes)` — (inheritdoc)

#### class `UnrealGameSync.EpicTelemetrySink`  
`public sealed class EpicTelemetrySink : ITelemetrySink`  
_public; L50-152_
- inherits: `ITelemetrySink`
- desc: Epic internal telemetry sink using the data router
- L52 _private* field_ `readonly string _url`
- L53 _private* field_ `readonly ILogger _logger`
- L54 _private* field_ `readonly HttpClient _httpClient = new HttpClient()`
- L55 _private* field_ `readonly Channel<string> _channel = Channel.CreateUnbounded<string>(new UnboundedChannelOptions())`
- L56 _private* field_ `readonly Task _backgroundTask`
- L61-69 _public ctor_ `public EpicTelemetrySink(string url, ILogger logger)` — Constructor
- L72-83 _public method_ `public void Dispose()` — (inheritdoc)
- L86-96 _public method_ `public void SendEvent(string eventName, object attributes)` — (inheritdoc)
- L101-151 _private* method_ `async Task WriteEventsAsync()` — Synchronously sends a telemetry event

#### class `UnrealGameSync.UgsTelemetry`  
`public static class UgsTelemetry`  
_public; L157-176_
- desc: Global telemetry static class
- L162-165 _public property_ `public static ITelemetrySink? ActiveSink { get; set; }` — The current telemetry provider
- L172-175 _public method_ `public static void SendEvent(string eventName, object attributes)` — Sends a telemetry event with the given information

### `Source/Programs/UnrealGameSync/UnrealGameSyncShared/TelemetryStopwatch.cs` (UnrealGameSyncShared)


#### class `UnrealGameSync.TelemetryStopwatch`  
`class TelemetryStopwatch : IDisposable`  
_internal*; L10-57_
- inherits: `IDisposable`
- L12 _private* field_ `readonly string _eventName`
- L13 _private* field_ `readonly Dictionary<string, object?> _eventData`
- L13 _private* field_ `readonly Dictionary< _eventData`
- L14 _private* field_ `readonly Stopwatch _timer`
- L16-24 _public ctor_ `public TelemetryStopwatch(string eventName, string project)`
- L26-32 _public method_ `public void AddData(object data)`
- L34-45 _public method_ `public TimeSpan Stop(string inResult)`
- L47-54 _public method_ `public void Dispose()`
- L56 _public property_ `public TimeSpan Elapsed => ...`

### `Source/Programs/UnrealGameSync/UnrealGameSyncShared/ToolUpdateMonitor.cs` (UnrealGameSyncShared)


#### class `UnrealGameSync.ToolLink`  
`public class ToolLink`  
_public; L25-37_
- attrs: `[DebuggerDisplay("{Label}")]`
- L27 _public property_ `public string Label { get; set; }`
- L28 _public property_ `public string FileName { get; set; }`
- L29 _public property_ `public string? Arguments { get; set; }`
- L30 _public property_ `public string? WorkingDir { get; set; }`
- L32-36 _public ctor_ `public ToolLink(string label, string fileName)`

#### class `UnrealGameSync.ToolSettings`  
`public class ToolSettings`  
_public; L40-50_
- L42 _public property_ `public string? InstallCommand { get; set; }`
- L43 _public property_ `public string? UninstallCommand { get; set; }`
- L47 _public property_ `public List<ToolLink> StatusPanelLinks { get; set; }` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Set property accessed through reflection")]`
- L49 _public property_ `public bool SafeWhenBusy { get; set; }`

#### class `UnrealGameSync.ToolInfo`  
`public class ToolInfo`  
_public; L53-78_
- attrs: `[DebuggerDisplay("{Name}")]`
- L55 _public property_ `public Guid Id { get; set; }`
- L56 _public property_ `public string Name { get; set; }`
- L57 _public property_ `public string Description { get; set; }`
- L61 _public property_ `public HashSet<Guid> DependsOnToolIds { get; set; }` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Set property accessed through reflection")]`
- L63 _public property_ `public ToolSettings Settings { get; set; }`
- L64 _public property_ `public string Revision { get; set; }`
- L66-72 _public ctor_ `public ToolInfo(Guid id, string name, string description, string revision)`
- L74-77 _public method_ `public ToolInfo Clone()`

#### class `UnrealGameSync.ToolUpdateMonitor`  
`public sealed class ToolUpdateMonitor : IDisposable`  
_public; L80-748_
- inherits: `IDisposable`
- L83 _private* field_ `readonly CancellationTokenSource _cancellationSource`
- L85 _private* field_ `readonly SynchronizationContext _synchronizationContext`
- L86 _private* field_ `Task? _workerTask`
- L87 _private* field_ `readonly AsyncEvent _wakeEvent`
- L88 _private* field_ `readonly ILogger _logger`
- L89 _private* field_ `readonly IAsyncDisposer _asyncDisposer`
- L90 _private* field_ `readonly FileReference _enabledToolsFile`
- L91 _private* field_ `readonly IServiceProvider _serviceProvider`
- L93 _private* field_ `bool _readLegacyConfig`
- L95 _private* field_ `IReadOnlyDictionary<string, ToolInfo> _perforceTools = ...`
- L95 _private* field_ `IReadOnlyDictionary< _perforceTools = new Dictionary<string, ToolInfo>(StringComparer.Ordinal)`
- L96 _private* field_ `int _perforceToolsChange = -1`
- L98 _private* field_ `IReadOnlyList<ToolInfo> _tools = Array.Empty<ToolInfo>()`
- L99 _private* field_ `IReadOnlyList<ToolInfo> _enabledTools = Array.Empty<ToolInfo>()`
- L101 _private* property_ `IPerforceSettings PerforceSettings { get; }`
- L102 _private* property_ `DirectoryReference ToolsDir { get; }`
- L103 _private* property_ `UserSettings Settings { get; }`
- L105 _public property_ `public Action? OnChange { get; set; }`
- L107 _public property_ `public Tuple<bool, string> LastStatus { get; set; }`
- L109-140 _public ctor_ `public ToolUpdateMonitor(IPerforceSettings perforceSettings, DirectoryReference dataDir, UserSettings settings, ILogger logger, IServiceProvider serviceProvider)`
- L142-145 _public method_ `public void Start()`
- L147-150 _public method_ `public Task GetDataFromBackendAsync()`
- L152-155 _public method_ `public Task UpdateToolsAsync()`
- L157-168 _public method_ `public void Dispose()`
- L170 _public method_ `public IReadOnlyList<ToolInfo> GetTools()`
- L173 _public method_ `public IReadOnlyList<ToolInfo> GetEnabledTools()`
- L176-179 _private* method_ `DirectoryReference GetToolPathInternal(string toolName)`
- L181-191 _public method_ `public string? GetToolName(Guid toolId)`
- L193-204 _public method_ `public DirectoryReference? GetToolPath(string toolName)`
- L206-209 _public method_ `public void UpdateNow()`
- L211-230 _private* method_ `async Task PollForUpdatesAsync(CancellationToken cancellationToken)`
- L232-331 _private* method_ `async Task PollForUpdatesOnce(CancellationToken cancellationToken, bool update = true)`
- L333-345 _private* method_ `static void FindEnabledTools(HashSet<Guid> inputToolIds, List<ToolInfo> tools, HashSet<Guid> enabledToolIds)`
- L347-383 _private* method_ `async Task ReadPerforceToolsAsync(IPerforceConnection perforce, List<ToolInfo> tools, CancellationToken cancellationToken)`
- L385-398 _private* method_ `static async Task ReadHordeToolsAsync(HordeHttpClient hordeHttpClient, List<ToolInfo> tools, CancellationToken cancellationToken)`
- L400-413 _private* method_ `static async Task<ToolInfo?> ReadToolDefinitionAsync(IPerforceConnection perforce, string iniRevision, string toolRevision, CancellationToken cancellationToken)`
- L415-461 _private* method_ `static ToolInfo? ParseToolInfo(string[] contents, string defaultToolName, string revision)`
- L463-479 _public method_ `public async Task RunCommandAsync(string toolName, string command, CancellationToken cancellationToken)`
- L481-508 _private* method_ `async Task RemoveToolAsync(ToolInfo tool, CancellationToken cancellationToken)`
- L510-521 _private* method_ `static void ForceDeleteDirectory(DirectoryReference directoryName)`
- L523-535 _private* method_ `bool TryDeleteDirectory(DirectoryReference directoryName)`
- L537-630 _private* method_ `async Task<bool> UpdateToolAsync(IPerforceConnection? perforce, ToolInfo tool, CancellationToken cancellationToken)`
- L632-635 _private* method_ `FileReference GetConfigFilePath(string toolName)`
- L637-672 _private* method_ `async Task ReadLegacyConfigAsync(IReadOnlyList<ToolInfo> tools, CancellationToken cancellationToken)`
- L674-690 _private* method_ `int GetToolChange(string toolName)`
- L692-714 _private* method_ `async Task SetToolRevisionAsync(string toolName, ToolInfo? toolInfo, CancellationToken cancellationToken)`
- L721-735 _private* method_ `void Load()`
- L737-747 _private* method_ `async Task SaveAsync(List<ToolInfo> enabledTools, CancellationToken cancellationToken)`

#### class `UnrealGameSync.ToolUpdateMonitor.State`  
`class State`  
_private*; L716-719_
- L718 _public property_ `public List<ToolInfo> Tools { get; set; }`

### `Source/Programs/UnrealGameSync/UnrealGameSyncShared/UserSettings.cs` (UnrealGameSyncShared)


#### enum `UnrealGameSync.BuildConfig`  
`public enum BuildConfig`  
_public; L20-25_
- L22 _public* enumerator_ `Debug`
- L23 _public* enumerator_ `DebugGame`
- L24 _public* enumerator_ `Development`

#### enum `UnrealGameSync.TabLabels`  
`public enum TabLabels`  
_public; L27-33_
- L29 _public* enumerator_ `Stream`
- L30 _public* enumerator_ `WorkspaceName`
- L31 _public* enumerator_ `WorkspaceRoot`
- L32 _public* enumerator_ `ProjectFile`

#### enum `UnrealGameSync.BisectState`  
`public enum BisectState`  
_public; L35-41_
- L37 _public* enumerator_ `Include`
- L38 _public* enumerator_ `Exclude`
- L39 _public* enumerator_ `Pass`
- L40 _public* enumerator_ `Fail`

#### enum `UnrealGameSync.UserSelectedProjectType`  
`public enum UserSelectedProjectType`  
_public; L43-47_
- L45 _public* enumerator_ `Client`
- L46 _public* enumerator_ `Local`

#### enum `UnrealGameSync.FilterType`  
`public enum FilterType`  
_public; L49-55_
- L51 _public* enumerator_ `None`
- L52 _public* enumerator_ `Code`
- L53 _public* enumerator_ `Content`
- L54 _public* enumerator_ `UEFN`

#### class `UnrealGameSync.LockableEditorArgument`  
`public class LockableEditorArgument`  
_public; L60-101_
- desc: Config specified class to add a lockable editor argument to a project
- L62 _public property_ `public string Name { get; set; }`
- L63 _public property_ `public bool Enabled { get; set; }`
- L64 _public property_ `public bool Locked { get; set; }`
- L66-71 _public ctor_ `public LockableEditorArgument( string name, bool enabled, bool locked = false )`
- L73-78 _public ctor_ `public LockableEditorArgument(LockableEditorArgument lockableEditorArgument)`
- L80-100 _public method_ `public static bool TryParseConfigEntry(string text, [NotNullWhen(true)] out LockableEditorArgument? editorArgument)`

#### class `UnrealGameSync.LatestChangeType`  
`public class LatestChangeType`  
_public; L107-188_
- desc: Config specified class to determine what is the Latest Change to Sync Can be configured using badges, good and starred CLs
- L110 _public property_ `public string Name { get; set; }`
- L111 _public property_ `public string Description { get; set; }`
- L112 _public property_ `public int OrderIndex { get; set; }`
- L115 _public property_ `public bool Good { get; set; }`
- L116 _public property_ `public bool Starred { get; set; }`
- L117 _public property_ `public bool FindNewestGoodContent { get; set; }`
- L118 _public property_ `public List<string> RequiredBadges { get; init; }`
- L121 _public property_ `public string? ReadFrom { get; set; }`
- L123-149 _public method_ `public static bool TryParseConfigEntry(string text, [NotNullWhen(true)] out LatestChangeType? changeType)`
- L152-161 _public method_ `public static LatestChangeType LatestChange()`
- L164-174 _public method_ `public static LatestChangeType LatestGoodChange()`
- L177-187 _public method_ `public static LatestChangeType LatestStarredChange()`

#### enum `UnrealGameSync.UserSettingsVersion`  
`public enum UserSettingsVersion`  
_public; L191-198_
- L193 _public* enumerator_ `Initial = 0`
- L194 _public* enumerator_ `DefaultServerSettings = 1`
- L195 _public* enumerator_ `XgeShaderCompilation = 2`
- L196 _public* enumerator_ `DefaultNumberOfThreads = 3`
- L197 _public* enumerator_ `Latest = DefaultNumberOfThreads`

#### class `UnrealGameSync.ArchiveSettings`  
`public class ArchiveSettings`  
_public; L201-259_
- L204 _public property_ `public bool Enabled { get; set; }` — attrs: `[JsonPropertyName("Enabled")]`
- L207 _public property_ `public string Type { get; set; }` — attrs: `[JsonPropertyName("Type")]`
- L210 _public property_ `public List<string> Order { get; init; }` — attrs: `[JsonPropertyName("Order")]`
- L212-215 _public ctor_ `public ArchiveSettings()`
- L217-222 _public ctor_ `public ArchiveSettings(bool enabled, string type, IEnumerable<string> order)`
- L224-242 _public method_ `public static bool TryParseConfigEntry(string text, [NotNullWhen(true)] out ArchiveSettings? settings)`
- L244-253 _public method_ `public string ToConfigEntry()`
- L255-258 _public method_ `public override string ToString()`

#### class `UnrealGameSync.SnapshotSettings`  
`public class SnapshotSettings`  
_public; L261-265_
- L263 _public property_ `public string Runtime { get; set; }`
- L264 _public property_ `public string Platform { get; set; }`

#### class `UnrealGameSync.UserSelectedProjectSettings`  
`public class UserSelectedProjectSettings`  
_public; L267-375_
- L269 _public property_ `public string? ServerAndPort { get; set; }`
- L270 _public property_ `public string? UserName { get; set; }`
- L271 _public property_ `public UserSelectedProjectType Type { get; set; }`
- L272 _public property_ `public string? ClientPath { get; set; }`
- L273 _public property_ `public string? LocalPath { get; set; }`
- L274 _public property_ `public string? ScheduledSyncTypeId { get; set; }`
- L276-283 _public ctor_ `public UserSelectedProjectSettings(string? serverAndPort, string? userName, UserSelectedProjectType type, string? clientPath, string? localPath)`
- L285-338 _public method_ `public static bool TryParseConfigEntry(string text, [NotNullWhen(true)] out UserSelectedProjectSettings? project)`
- L340-369 _public method_ `public string ToConfigEntry()`
- L371-374 _public method_ `public override string? ToString()`

#### class `UnrealGameSync.SyncCategory`  
`public class SyncCategory`  
_public; L377-381_
- L379 _public property_ `public Guid Id { get; set; }`
- L380 _public property_ `public bool Enable { get; set; }`

#### class `UnrealGameSync.BisectEntry`  
`public class BisectEntry`  
_public; L383-387_
- L385 _public property_ `public int Change { get; set; }`
- L386 _public property_ `public BisectState State { get; set; }`

#### class `UnrealGameSync.UserWorkspaceSettings`  
`public class UserWorkspaceSettings`  
_public; L389-488_
- L392 _public property_ `public DirectoryReference RootDir { get; set; }` — attrs: `[JsonIgnore]`
- L395 _public property_ `public long LastModifiedTimeUtc { get; set; }` — attrs: `[JsonIgnore]`
- L398 _public property_ `public string? ServerAndPort { get; set; }`
- L399 _public property_ `public string? UserName { get; set; }`
- L400 _public property_ `public string ClientName { get; set; }`
- L403 _public property_ `public string BranchPath { get; set; }`
- L406 _public property_ `public string ProjectPath { get; set; }`
- L408 _public property_ `public string Preset { get; set; }`
- L411 _public property_ `public FilterSettings Filter { get; set; }`
- L413 _public property_ `public bool SyncBaseContent { get; set; }`
- L416 _public property_ `public FileReference ConfigFile => ...` — attrs: `[JsonIgnore]`
- L419 _public property_ `public string ClientProjectPath => ...` — attrs: `[JsonIgnore]`
- L422 _public property_ `public FileReference? LocalProjectPath { get; set; }` — attrs: `[JsonIgnore]`
- L424-435 _public method_ `public void Init(string? serverAndPort, string? userName, string clientName, string branchPath, string projectPath, string localPath)`
- L437-451 _public method_ `public static bool TryLoad(DirectoryReference rootDir, [NotNullWhen(true)] out UserWorkspaceSettings? settings)`
- L453 _private* field_ `static readonly object _syncRoot = new object()`
- L455-458 _public method_ `public bool Save(ILogger logger)`
- L460-472 _public method_ `public bool Save(ILogger logger, FileReference workspaceSettingsFile)`
- L474-482 _private method_ `private void SaveInternal(FileReference fileReference)`
- L484-487 _public method_ `public static FileReference GetConfigFile(DirectoryReference rootDir)`

#### class `UnrealGameSync.UserProjectSettings`  
`public class UserProjectSettings`  
_public; L490-603_
- L493 _public property_ `public FileReference ConfigFile { get; set; }` — attrs: `[JsonIgnore]`
- L496 _public property_ `public List<string> RequiredBadges { get; init; }` — attrs: `[JsonIgnore]`
- L499 _public property_ `public List<ConfigObject> BuildSteps { get; init; }` — attrs: `[JsonPropertyName("BuildSteps")]`
- L502 _public property_ `public FilterType FilterType { get; set; }` — attrs: `[JsonPropertyName("FilterType")]`
- L505 _public property_ `public HashSet<string> FilterBadges { get; init; }` — attrs: `[JsonPropertyName("FilterBadges")]`
- L508 _public property_ `public string Preset { get; set; }` — attrs: `[JsonPropertyName("Preset")]`
- L511 _public property_ `public bool PresetSetByUser { get; set; }` — attrs: `[JsonPropertyName("PresetSetByUser")]`
- L514 _public property_ `public List<ArchiveSettings> Archives { get; init; }` — attrs: `[JsonPropertyName("Archives")]`
- L517 _public property_ `public bool ArchivesDeactivated { get; set; }` — attrs: `[JsonPropertyName("ArchivesDeactivated")]`
- L520 _public property_ `public string Version { get; set; }` — attrs: `[JsonPropertyName("Version")]`
- L522 _private field_ `private static readonly object s_syncRoot = new object()`
- L524 _private field_ `private static string s_currentVersion = String.Empty`
- L525-550 _public method_ `public static string CurrentVersion()`
- L552-554 _private ctor_ `private UserProjectSettings()`
- L556-559 _public ctor_ `public UserProjectSettings(FileReference configFile)`
- L561-573 _public method_ `public static bool TryLoad(FileReference configFile, [NotNullWhen(true)] out UserProjectSettings? settings)`
- L575-578 _public method_ `public bool Save(ILogger logger)`
- L580-592 _public method_ `public bool Save(ILogger logger, FileReference projectSettingsFile)`
- L594-602 _private method_ `private void SaveInternal(FileReference fileReference)`

#### class `UnrealGameSync.UserSettings`  
`public class UserSettings : GlobalSettingsFile`  
_public; L605-1358_
- inherits: `GlobalSettingsFile`
- L617 _private* field_ `readonly FileReference _fileName`
- L618 _private* field_ `readonly ConfigFile _configFile`
- L621 _public property_ `public UserSettingsVersion Version { get; set; }`
- L622 _public property_ `public bool GenerateProjectAfterSync { get; set; }`
- L623 _public property_ `public bool BuildAfterSync { get; set; }`
- L624 _public property_ `public bool RunAfterSync { get; set; }`
- L625 _public property_ `public bool OpenSolutionAfterSync { get; set; }`
- L626 _public property_ `public bool ShowLogWindow { get; set; }`
- L627 _public property_ `public bool ShowUnreviewedChanges { get; set; }`
- L628 _public property_ `public bool ShowAutomatedChanges { get; set; }`
- L629 _public property_ `public RobomergeShowChangesOption ShowRobomerge { get; set; }`
- L630 _public property_ `public bool AnnotateRobmergeChanges { get; set; }`
- L631 _public property_ `public bool ShowLocalTimes { get; set; }`
- L632 _public property_ `public bool KeepInTray { get; set; }`
- L633 _public property_ `public HashSet<Guid> EnabledTools { get; init; }`
- L634 _public property_ `public int FilterIndex { get; set; }`
- L635 _public property_ `public UserSelectedProjectSettings? LastProject { get; set; }`
- L636 _public property_ `public List<UserSelectedProjectSettings> OpenProjects { get; init; }`
- L637 _public property_ `public List<UserSelectedProjectSettings> RecentProjects { get; init; }`
- L638 _public property_ `public string SyncTypeId { get; set; }`
- L639 _public property_ `public BuildConfig CompiledEditorBuildConfig { get; set; }`
- L640 _public property_ `public TabLabels TabLabels { get; set; }`
- L641 _public property_ `public long NextLauncherVersionCheck { get; set; }`
- L642 _public property_ `public ApplicationTheme? Theme { get; set; }`
- L643 _public property_ `public Dictionary<string, string> ThemeList { get; init; }`
- L646 _public property_ `public List<ArchiveSettings> Archives { get; init; }`
- L648 _public property_ `public List<SnapshotSettings> Snapshots { get; init; }`
- L649 _public property_ `public string SnapshotHost { get; set; }`
- L650 _public property_ `public string SnapshotNamespace { get; set; }`
- L653 _public property_ `public Dictionary<string, string> ProviderToRefreshTokens { get; init; }`
- L656 _public property_ `public bool WindowVisible { get; set; }`
- L657 _public property_ `public string WindowState { get; set; }`
- L658 _public property_ `public Rectangle? WindowBounds { get; set; }`
- L661 _public property_ `public bool ScheduleEnabled { get; set; }`
- L662 _public property_ `public TimeSpan ScheduleTime { get; set; }`
- L663 _public property_ `public bool ScheduleAnyOpenProject { get; set; }`
- L664 _public property_ `public List<UserSelectedProjectSettings> ScheduleProjects { get; init; }`
- L667 _public property_ `public List<LockableEditorArgument> EditorArguments { get; init; }`
- L668 _public property_ `public bool EditorArgumentsPrompt { get; set; }`
- L671 _public property_ `public List<string> NotifyProjects { get; init; }`
- L672 _public property_ `public int NotifyUnassignedMinutes { get; set; }`
- L673 _public property_ `public int NotifyUnacknowledgedMinutes { get; set; }`
- L674 _public property_ `public int NotifyUnresolvedMinutes { get; set; }`
- L677 _private* field_ `readonly Dictionary<DirectoryReference, UserWorkspaceSettings> _workspaceDirToSettings = ...`
- L677 _private* field_ `readonly Dictionary< _workspaceDirToSettings = new Dictionary<DirectoryReference, UserWorkspaceSettings>()`
- L678 _private* field_ `readonly Dictionary<FileReference, UserProjectSettings> _projectKeyToSettings = ...`
- L678 _private* field_ `readonly Dictionary< _projectKeyToSettings = new Dictionary<FileReference, UserProjectSettings>()`
- L681 _public property_ `public PerforceSyncOptions SyncOptions => ...`
- L682 _public property_ `public ClientSubmitOptions ClientSubmitOptions { get; set; }`
- L684-716 _private method_ `private List<UserSelectedProjectSettings> ReadProjectList(string settingName, string legacySettingName)`
- L718-721 _public method_ `public static UserSettings Create(DirectoryReference settingsDir, ILogger logger)`
- L723-762 _public method_ `public static UserSettings Create(FileReference fileName, FileReference legacyFileName, FileReference coreFileName, ILogger logger)`
- L764-950 _public ctor_ `public UserSettings(FileReference inFileName, ConfigFile inConfigFile, FileReference inCoreFileName, GlobalSettings inCoreSettingsData) : base(inCoreFileName, inCoreSettingsData)`
- L952-967 _private* method_ `static Dictionary<Guid, bool> GetCategorySettings(ConfigSection? section, string includedKey, string excludedKey)`
- L969-986 _private* method_ `static Rectangle? ParseRectangleValue(string text)`
- L988-998 _private* method_ `static string FormatRectangleValue(Rectangle value)`
- L1000-1004 _public method_ `public static DirectoryReference GetConfigDir(DirectoryReference workspaceDir)`
- L1006-1017 _public method_ `public static void CreateConfigDir(DirectoryReference configDir)`
- L1019-1022 _public method_ `public ApplicationTheme? LoadTheme(string themeId)`
- L1024-1123 _protected method_ `protected override void ImportWorkspaceState(DirectoryReference rootDir, string clientName, string branchPath, WorkspaceState currentWorkspace)`
- L1125-1147 _protected method_ `protected override void ImportWorkspaceSettings(DirectoryReference rootDir, string clientName, string branchPath, UserWorkspaceSettings currentWorkspace)`
- L1149-1159 _protected method_ `protected override void ImportProjectSettings(ProjectInfo projectInfo, UserProjectSettings currentProject)`
- L1161-1181 _public method_ `public bool Save(ILogger logger, FileReference globalSettingsJsonFile, FileReference globalSettingsIniFile)`
- L1183-1203 _public method_ `public override bool Save(ILogger logger)`
- L1205-1306 _private method_ `private void PrepareConfigFileforSave()`
- L1309-1349 _private* method_ `static string? UnescapeText(string? text)` — attrs: `[return: NotNullIfNotNull("text")]`
- L1351-1357 _public method_ `public IEnumerable<FileReference> GetCachedFilePaths()`

#### enum `UnrealGameSync.UserSettings.RobomergeShowChangesOption`  
`public enum RobomergeShowChangesOption`  
_public; L610-615_
- desc: Enum that decribes which robomerge changes to show
- L612 _public* enumerator_ `All`
- L613 _public* enumerator_ `Badged`
- L614 _public* enumerator_ `None`

### `Source/Programs/UnrealGameSync/UnrealGameSyncShared/Utility.cs` (UnrealGameSyncShared)


#### class `UnrealGameSync.UserErrorException`  
`public sealed class UserErrorException : Exception`  
_public; L25-33_
- inherits: `Exception`
- L27 _public property_ `public int Code { get; }`
- L29-32 _public ctor_ `public UserErrorException(string message, int code = 1) : base(message)`

#### class `UnrealGameSync.PerforceChangeDetails`  
`public class PerforceChangeDetails`  
_public; L35-87_
- L37 _public property_ `public int Number { get; }`
- L38 _public property_ `public string Description { get; }`
- L39 _public property_ `public bool ContainsCode { get; }`
- L40 _public property_ `public bool ContainsContent { get; }`
- L42 _public property_ `public bool ContainsUEFN { get; }`
- L44 _public property_ `public bool ContainsUgsConfig { get; }`
- L46-76 _public ctor_ `public PerforceChangeDetails(DescribeRecord describeRecord, Func<string, bool>? isCodeFile = null, Func<string, bool>? isUEFNFile = null)`
- L78-81 _public method_ `public static bool IsCodeFile(string depotFile)`
- L83-86 _public method_ `public static bool IsUEFNFile(string depotFile)`

#### class `UnrealGameSync.Utility`  
`public static class Utility`  
_public; L89-1015_
- L91 _private* field_ `static readonly MemoryCache s_changeCache = new MemoryCache(new MemoryCacheOptions { SizeLimit = 4096 })`
- L101 _private* method_ `static string GetChangeCacheKey(int number, Sha1Hash config)`
- L103 _private* method_ `static string GetChangeDetailsCacheKey(int number, Sha1Hash config)`
- L105-125 _private* method_ `static Sha1Hash GetConfigHash(IPerforceConnection perforce, IEnumerable<string> syncPaths, IEnumerable<string> codeRules, IEnumerable<string> uefnRules)`
- L130-134 _public method_ `public static string[] GetCodeFilter(ConfigFile projectConfigFile)` — Gets the code filter from the project config file
- L139-143 _public method_ `public static string[] GetUEFNFilter(ConfigFile projectConfigFile)` — Gets the code filter from the project config file
- L148-265 _public method_ `public static async IAsyncEnumerable<ChangesRecord> EnumerateChanges(IPerforceConnection perforce, IEnumerable<string> syncPaths, int? minChangeNumber, int? maxChangeNumber, int? maxChanges, [EnumeratorCancellation] CancellationToken cancellationToken)` — Creates or returns cached PerforceChangeDetails objects describing the requested chagnes
- L270-274 _public method_ `public static IAsyncEnumerable<PerforceChangeDetails> EnumerateChangeDetails(IPerforceConnection perforce, int? minChangeNumber, int? maxChangeNumber, IEnumerable<string> syncPaths, IEnumerable<string> codeRules, IEnumerable<string> uefnRules, CancellationToken cancellationToken)` — Creates or returns cached PerforceChangeDetails objects describing the requested chagnes
- L279-379 _public method_ `public static async IAsyncEnumerable<PerforceChangeDetails> EnumerateChangeDetails(IPerforceConnection perforce, IAsyncEnumerable<int> changeNumbers, IEnumerable<string> codeRules, IEnumerable<string> uefnRules, [EnumeratorCancellation] CancellationToken cancellationToken)` — Creates or returns cached PerforceChangeDetails objects describing the requested chagnes
- L381 _public event_ `public static event Action<Exception>? TraceException`
- L383-391 _private* method_ `static JsonSerializerOptions GetDefaultJsonSerializerOptions()`
- L393 _public property_ `public static JsonSerializerOptions DefaultJsonSerializerOptions { get; }`
- L395-414 _public method_ `public static bool TryLoadJson<T>(FileReference file, [NotNullWhen(true)] out T? obj) where T : class`
- L416-427 _public method_ `public static T? TryDeserializeJson<T>(byte[] data) where T : class`
- L429-433 _public method_ `public static T LoadJson<T>(FileReference file)`
- L435-451 _public method_ `public static byte[] SerializeJson<T>(T obj)`
- L453-457 _public method_ `public static void SaveJson<T>(FileReference file, T obj)`
- L459-470 _public method_ `public static string GetPathWithCorrectCase(FileInfo info)`
- L472-487 _public method_ `public static string GetPathWithCorrectCase(DirectoryInfo info)`
- L489-496 _public method_ `public static void ForceDeleteFile(string fileName)`
- L498-507 _public method_ `public static bool SpawnProcess(string fileName, string commandLine)`
- L509-528 _public method_ `public static bool SpawnHiddenProcess(string fileName, string commandLine)`
- L530-546 _public method_ `public static async Task<int> ExecuteProcessAsync(string fileName, string? workingDir, string commandLine, Action<string> outputLine, IReadOnlyDictionary<string, string>? env = null, CancellationToken cancellationToken = default)`
- L548-564 _public method_ `public static async Task<int> ExecuteProcessAsync(string fileName, string? workingDir, string commandLine, Action<string> outputLine, CancellationToken cancellationToken)`
- L566-578 _public method_ `public static bool SafeIsFileUnderDirectory(string fileName, string directoryName)`
- L587-636 _public method_ `public static string ExpandVariables(string inputString, Dictionary<string, string>? additionalVariables = null)` — Expands variables in $(VarName) format in the given string. Variables are retrieved from the given dictionary, or through the environment of the current process. Any unknown variables are ignored.
- L646-662 _public method_ `public static bool IsEnterpriseProjectFromText(string text)` — Determines if a project is an enterprise project
- L666-685 _private method_ `private static void AddLocalConfigPaths_WithSubFolders(DirectoryInfo baseDir, string fileName, List<FileInfo> files)`
- L687-711 _private method_ `private static void AddLocalConfigPaths_WithExtensionDirs(DirectoryInfo? baseDir, string relativePath, string fileName, List<FileInfo> files)`
- L713-747 _public method_ `public static List<FileInfo> GetLocalConfigPaths(DirectoryInfo engineDir, FileInfo projectFile)`
- L749-753 _private method_ `private static void AddDepotConfigPaths_PlatformFolders(string basePath, string fileName, List<string> searchPaths)`
- L755-760 _private method_ `private static void AddDepotConfigPaths_PlatformExtensions(string basePath, string relativePath, string fileName, List<string> searchPaths)`
- L762-794 _public method_ `public static List<string> GetDepotConfigPaths(string enginePath, string projectPath, string branchClientPath)`
- L798-865 _public method_ `public static async Task<string[]?> TryPrintFileUsingCacheAsync(IPerforceConnection perforce, string depotPath, DirectoryReference cacheFolder, string? digest, ILogger logger, CancellationToken cancellationToken)`
- L867-888 _public method_ `public static void ClearPrintCache(DirectoryReference cacheFolder)`
- L890-893 _public method_ `public static Color Blend(Color first, Color second, float t)`
- L895-907 _public method_ `public static PerforceSettings OverridePerforceSettings(IPerforceSettings defaultConnection, string? serverAndPort, string? userName)`
- L909-936 _public method_ `public static string FormatRecentDateTime(DateTime date)`
- L938-941 _public method_ `public static string FormatDurationMinutes(TimeSpan duration)`
- L943-957 _public method_ `public static string FormatDurationMinutes(int totalMinutes)`
- L959-978 _public method_ `public static string FormatUserName(string userName)`
- L980-986 _public method_ `public static void OpenUrl(string url)`
- L989-998 _public method_ `public static void DeleteRegistryKey(RegistryKey rootKey, string keyName, string valueName)` — attrs: `[SupportedOSPlatform("windows")]`
- L1001-1014 _public method_ `public static void DeleteRegistryKey(RegistryKey key, string name)` — attrs: `[SupportedOSPlatform("windows")]`

#### class `UnrealGameSync.Utility.CachedChangeRecord`  
`class CachedChangeRecord`  
_private*; L93-99_
- L95 _public property_ `public ChangesRecord ChangesRecord { get; }`
- L96 _public property_ `public int? PrevNumber { get; set; }`
- L98 _public ctor_ `public CachedChangeRecord(ChangesRecord changesRecord)`

#### class `UnrealGameSync.Utility.ProjectJson`  
`class ProjectJson`  
_private*; L638-641_
- L640 _public property_ `public bool Enterprise { get; set; }`

### `Source/Programs/UnrealGameSync/UnrealGameSyncShared/WorkspaceLock.cs` (UnrealGameSyncShared)


#### class `UnrealGameSync.WorkspaceLock`  
`public sealed class WorkspaceLock : IDisposable`  
_public; L16-237_
- inherits: `IDisposable`
- desc: Encapsulates the state of cross-process workspace lock
- L18 _private* const_ `const string Prefix = @"Global\ugs-workspace"`
- L20 _private* field_ `readonly Mutex _mutex`
- L22 _private* field_ `readonly object _lockObject = new object()`
- L23 _private* field_ `readonly string _objectName`
- L24 _private* field_ `int _acquireCount`
- L26 _private* field_ `bool _locked`
- L27 _private* field_ `EventWaitHandle? _lockedEvent`
- L29 _private* field_ `Thread? _acquireThread`
- L30 _private* field_ `readonly BlockingCollection<Action> _acquireActions = new BlockingCollection<Action>()`
- L31 _private* field_ `readonly CancellationTokenSource _acquireCancellationSource = new CancellationTokenSource()`
- L33 _private* field_ `Thread? _monitorThread`
- L34 _private* field_ `readonly ManualResetEvent _cancelMonitorEvent = new ManualResetEvent(false)`
- L39 _public event_ `public event Action<bool>? OnChange` — Callback for the lock state changing
- L45-66 _public ctor_ `public WorkspaceLock(DirectoryReference rootDir)` — Constructor
- L69-93 _public method_ `public void Dispose()` — (inheritdoc)
- L99 _public method_ `public bool IsLocked()` — Determines if the lock is held by any
- L105 _public method_ `public bool IsLockedByOtherProcess()` — Determines if the lock is held by another process
- L111-116 _public method_ `public async Task<bool> TryAcquireAsync()` — Attempt to acquire the mutext
- L118-139 _private* method_ `void TryAcquireInternal(TaskCompletionSource<bool> resultTcs)`
- L144-149 _public method_ `public async Task ReleaseAsync()` — Release the current mutext
- L151-165 _private method_ `private void ReleaseInternal(TaskCompletionSource<bool> resultTcs)`
- L167-175 _private method_ `private void ReleaseLockedEvent()`
- L177-197 _private* method_ `void AcquireThread()`
- L199-234 _private* method_ `void MonitorThread()`
- L236 _private* method_ `EventWaitHandle CreateLockedEvent()`

### `Source/Programs/UnrealGameSync/UnrealGameSyncShared/WorkspaceState.cs` (UnrealGameSyncShared)


#### class `UnrealGameSync.WorkspaceState`  
`public class WorkspaceState`  
_public; L15-142_
- desc: The current workspace state. Use WorkspaceStateWrapper to access state for a workspace.
- L24 _public property_ `public long SettingsTimeUtc { get; set; }`
- L25 _public property_ `public string ClientName { get; set; }`
- L26 _public property_ `public string BranchPath { get; set; }`
- L27 _public property_ `public string ProjectPath { get; set; }`
- L28 _public property_ `public string? StreamName { get; set; }`
- L30 _public property_ `public bool StreamSwitched { get; set; }`
- L32 _public property_ `public string ProjectIdentifier { get; set; }`
- L33 _public property_ `public bool IsEnterpriseProject { get; set; }`
- L36 _public property_ `public int CurrentChangeNumber { get; set; }`
- L37 _public property_ `public int CurrentCodeChangeNumber { get; set; }`
- L38 _public property_ `public string? CurrentSyncFilterHash { get; set; }`
- L39 _public property_ `public List<int> AdditionalChangeNumbers { get; init; }`
- L42 _public property_ `public int LastSyncChangeNumber { get; set; }`
- L43 _public property_ `public WorkspaceUpdateResult LastSyncResult { get; set; }`
- L44 _public property_ `public string? LastSyncResultMessage { get; set; }`
- L45 _public property_ `public DateTime? LastSyncTime { get; set; }`
- L46 _public property_ `public int LastSyncDurationSeconds { get; set; }`
- L49 _public property_ `public int LastBuiltChangeNumber { get; set; }`
- L52 _public property_ `public string LastSyncEditorArchive { get; set; }`
- L55 _public property_ `public HashSet<string> ExpandedArchiveTypes { get; init; }`
- L58 _public property_ `public List<BisectEntry> BisectChanges { get; init; }`
- L60-70 _public method_ `public void UpdateCachedProjectInfo(ProjectInfo projectInfo, long settingsTimeUtc)`
- L72-75 _public method_ `public bool IsValid(ProjectInfo projectInfo)`
- L77-84 _public method_ `public void ResetForProject(ProjectInfo projectInfo)`
- L86-120 _public method_ `public void CopyFrom(WorkspaceState other)`
- L122-132 _public method_ `public void SetBisectState(int change, BisectState state)`
- L134-141 _public method_ `public void SetLastSyncState(WorkspaceUpdateResult result, WorkspaceUpdateContext context, string statusMessage)`

#### class `UnrealGameSync.ReadOnlyWorkspaceState`  
`public class ReadOnlyWorkspaceState`  
_public; L147-211_
- desc: Read-only wrapper around WorkspaceState. To modify state, use WorkspaceStateWrapper.Modify(Action{WorkspaceState}).
- L149 _private* field_ `readonly WorkspaceState _inner`
- L151 _public property_ `public long SettingsTimeUtc => ...`
- L152 _public property_ `public string ClientName => ...`
- L153 _public property_ `public string BranchPath => ...`
- L154 _public property_ `public string ProjectPath => ...`
- L155 _public property_ `public string? StreamName => ...`
- L156 _public property_ `public bool StreamSwitched => ...`
- L157 _public property_ `public string ProjectIdentifier => ...`
- L158 _public property_ `public bool IsEnterpriseProject => ...`
- L161 _public property_ `public int CurrentChangeNumber => ...`
- L162 _public property_ `public int CurrentCodeChangeNumber => ...`
- L163 _public property_ `public string? CurrentSyncFilterHash => ...`
- L164 _public property_ `public IReadOnlyList<int> AdditionalChangeNumbers => ...`
- L167 _public property_ `public int LastSyncChangeNumber => ...`
- L168 _public property_ `public WorkspaceUpdateResult LastSyncResult => ...`
- L169 _public property_ `public string? LastSyncResultMessage => ...`
- L170 _public property_ `public DateTime? LastSyncTime => ...`
- L171 _public property_ `public int LastSyncDurationSeconds => ...`
- L174 _public property_ `public int LastBuiltChangeNumber => ...`
- L177 _public property_ `public string LastSyncEditorArchive => ...`
- L180 _public property_ `public IReadOnlySet<string> ExpandedArchiveTypes { get; }`
- L183 _public property_ `public IReadOnlyList<BisectEntry> BisectChanges => ...`
- L185-189 _internal ctor_ `internal ReadOnlyWorkspaceState(WorkspaceState inner)`
- L191-203 _public method_ `public ReadOnlyWorkspaceState ResetForProject(ProjectInfo projectInfo)`
- L205-210 _public method_ `public WorkspaceState MutableCopy()`

#### class `UnrealGameSync.WorkspaceStateWrapper`  
`public sealed class WorkspaceStateWrapper : IDisposable`  
_public; L216-348_
- inherits: `IDisposable`
- desc: Monitors state of a workspace state file.
- L221 _public property_ `public DirectoryReference RootDir { get; }` — Directory containing the config file
- L226 _public property_ `public FileReference File { get; }` — Path to the modified file
- L231 _public property_ `public ReadOnlyWorkspaceState Current { get; set; }` — Current workspace state
- L236 _public event_ `public event Action<ReadOnlyWorkspaceState>? OnModified` — Callback for modifications to the workspace state
- L238 _private* field_ `readonly FileSystemWatcher _watcher`
- L239 _private* field_ `readonly Func<WorkspaceState> _createNew`
- L244-263 _public ctor_ `public WorkspaceStateWrapper(DirectoryReference rootDir, Func<WorkspaceState> createNew)` — Constructor
- L266-269 _public method_ `public void Dispose()` — (inheritdoc)
- L275-301 _public method_ `public ReadOnlyWorkspaceState Modify(Action<WorkspaceState> action)` — Modify the current workspace state
- L303-307 _private* method_ `void OnModifiedInternal(object sender, FileSystemEventArgs e)`
- L309 _private* const_ `const int ERROR_SHARING_VIOLATION = 32`
- L311-328 _private method_ `private ReadOnlyWorkspaceState GetSnapshot()`
- L330-347 _private* method_ `WorkspaceState ReadState(FileStream stream)`

### `Source/Programs/UnrealGameSync/UnrealGameSyncShared/WorkspaceUpdate.cs` (UnrealGameSyncShared)


#### enum `UnrealGameSync.WorkspaceUpdateOptions`  
`public enum WorkspaceUpdateOptions`  
_public; L26-50_
- attrs: `[Flags]`
- L28 _public* enumerator_ `Sync = 0x01`
- L29 _public* enumerator_ `SyncSingleChange = 0x02`
- L30 _public* enumerator_ `AutoResolveChanges = 0x04`
- L31 _public* enumerator_ `GenerateProjectFiles = 0x08`
- L32 _public* enumerator_ `SyncArchives = 0x10`
- L33 _public* enumerator_ `Build = 0x20`
- L34 _public* enumerator_ `Clean = 0x40`
- L35 _public* enumerator_ `ScheduledBuild = 0x80`
- L36 _public* enumerator_ `RunAfterSync = 0x100`
- L37 _public* enumerator_ `OpenSolutionAfterSync = 0x200`
- L38 _public* enumerator_ `ContentOnly = 0x400`
- L39 _public* enumerator_ `UpdateFilter = 0x800`
- L40 _public* enumerator_ `SyncAllProjects = 0x1000`
- L41 _public* enumerator_ `IncludeAllProjectsInSolution = 0x2000`
- L42 _public* enumerator_ `RemoveFilteredFiles = 0x4000`
- L43 _public* enumerator_ `Clobber = 0x8000`
- L44 _public* enumerator_ `Refilter = 0x10000`
- L45 _public* enumerator_ `UprojectSpecificSolution = 0x20000`
- L46 _public* enumerator_ `FastSync = 0x40000`
- L47 _public* enumerator_ `ImportSnapshots = 0x80000`
- L48 _public* enumerator_ `SyncLocalProjects = 0x100000`
- L49 _public* enumerator_ `SyncBaseContent = 0x200000`

#### enum `UnrealGameSync.WorkspaceUpdateResult`  
`public enum WorkspaceUpdateResult`  
_public; L52-63_
- L54 _public* enumerator_ `Canceled`
- L55 _public* enumerator_ `FailedToSync`
- L56 _public* enumerator_ `FailedToSyncLoginExpired`
- L57 _public* enumerator_ `FilesToDelete`
- L58 _public* enumerator_ `FilesToResolve`
- L59 _public* enumerator_ `FilesToClobber`
- L60 _public* enumerator_ `FailedToCompile`
- L61 _public* enumerator_ `FailedToCompileWithCleanWorkspace`
- L62 _public* enumerator_ `Success`

#### class `UnrealGameSync.PerforceSyncOptions`  
`public class PerforceSyncOptions`  
_public; L65-96_
- L67 _public const_ `public const int DefaultNumRetries = 0`
- L68 _public const_ `public const int DefaultNumThreads = 4`
- L69 _public const_ `public const int DefaultTcpBufferSize = 0`
- L70 _public const_ `public const int DefaultFileBufferSize = 0`
- L72 _public const_ `public const int DefaultMaxCommandsPerBatch = 200`
- L73 _public const_ `public const int DefaultMaxSizePerBatch = 128 * 1024 * 1024`
- L74 _public const_ `public const int DefaultNumSyncErrorRetries = 0`
- L75 _public const_ `public const int DefaultSyncErrorRetryDelay = 0`
- L77 _public const_ `public const bool DefaultUseFastSync = false`
- L78 _public const_ `public const bool DefaultUseNativeLibrary = true`
- L80 _public property_ `public int? NumThreads { get; set; }`
- L82 _public property_ `public int? MaxCommandsPerBatch { get; set; }`
- L83 _public property_ `public int? MaxSizePerBatch { get; set; }`
- L85 _public property_ `public int? NumSyncErrorRetries { get; set; }`
- L86 _public property_ `public int? SyncErrorRetryDelay { get; set; }`
- L88 _public property_ `public bool? UseFastSync { get; set; }`
- L90 _public property_ `public bool? UseNativeClient { get; set; }`
- L92-95 _public method_ `public PerforceSyncOptions Clone()`

#### class `UnrealGameSync.WorkspaceUpdateContext`  
`public class WorkspaceUpdateContext`  
_public; L98-192_
- L100 _public property_ `public DateTime StartTime { get; set; }`
- L101 _public property_ `public int ChangeNumber { get; set; }`
- L102 _public property_ `public int? CodeChangeNumber { get; set; }`
- L103 _public property_ `public WorkspaceUpdateOptions Options { get; set; }`
- L104 _public property_ `public BuildConfig EditorConfig { get; set; }`
- L105 _public property_ `public List<string> SyncFilter { get; }`
- L106 _public property_ `public Dictionary<string, IArchive?> ArchiveTypeToArchive { get; }`
- L107 _public property_ `public Dictionary<string, bool> DeleteFiles { get; }`
- L108 _public property_ `public Dictionary<string, bool> ClobberFiles { get; }`
- L109 _public property_ `public List<ConfigObject> UserBuildStepObjects { get; }`
- L110 _public property_ `public HashSet<Guid> CustomBuildSteps { get; }`
- L111 _public property_ `public Dictionary<string, string> AdditionalVariables { get; }`
- L112 _public property_ `public PerforceSyncOptions? PerforceSyncOptions { get; set; }`
- L113 _public property_ `public List<HaveRecord> HaveFiles { get; }`
- L114 _public property_ `public List<SnapshotSettings> Snapshots { get; }`
- L115 _public property_ `public string SnapshotHost { get; set; }`
- L116 _public property_ `public string SnapshotNamespace { get; set; }`
- L117 _public property_ `public IServiceProvider ServiceProvider { get; init; }`
- L119 _public property_ `public UserSettings? Usersettings { get; init; }`
- L121 _public property_ `public UserWorkspaceSettings? UserWorkspaceSettings { get; init; }`
- L123 _public property_ `public UserProjectSettings? UserProjectSettings { get; init; }`
- L127 _public property_ `public ConfigFile? ProjectConfigFile { get; set; }`
- L128 _public property_ `public IReadOnlyList<string>? ProjectStreamFilter { get; set; }`
- L129 _public property_ `public ISet<string> BaseContentPaths { get; set; }`
- L130 _public property_ `public ISet<string> AdditionalPathsToSync { get; set; }`
- L133-161 _public ctor_ `public WorkspaceUpdateContext( IServiceProvider serviceProvider, UserSettings? usersettings, UserWorkspaceSettings? userWorkspaceSettings, UserProjectSettings? userProjectSettings, int changeNumber, WorkspaceUpdateOptions options, BuildConfig editorConfig, string[]? syncFilter, List<ConfigObject> userBuildSteps, HashSet<Guid>? customBuildSteps)`
- L163-191 _public method_ `public static WorkspaceUpdateOptions GetOptionsFromConfig(GlobalSettings globalSettings, UserWorkspaceSettings workspaceSettings)`

#### class `UnrealGameSync.WorkspaceSyncCategory`  
`public class WorkspaceSyncCategory`  
_public; L194-246_
- L196 _public property_ `public Guid UniqueId { get; set; }`
- L197 _public property_ `public bool Enable { get; set; }`
- L198 _public property_ `public string Name { get; set; }`
- L199 _public property_ `public List<string> Paths { get; }`
- L200 _public property_ `public bool Hidden { get; set; }`
- L201 _public property_ `public List<Guid> Requires { get; }`
- L203-205 _public ctor_ `public WorkspaceSyncCategory(Guid uniqueId) : this(uniqueId, "Unnamed")`
- L207-213 _public ctor_ `public WorkspaceSyncCategory(Guid uniqueId, string name, params string[] paths)`
- L215-218 _public method_ `public static Dictionary<Guid, bool> GetDefault(IEnumerable<WorkspaceSyncCategory> categories)`
- L220-232 _public method_ `public static Dictionary<Guid, bool> GetDelta(Dictionary<Guid, bool> source, Dictionary<Guid, bool> target)`
- L234-240 _public method_ `public static void ApplyDelta(Dictionary<Guid, bool> categories, Dictionary<Guid, bool> delta)`
- L242-245 _public method_ `public override string ToString()`

#### class `UnrealGameSync.ProjectInfo`  
`public class ProjectInfo`  
_public; L248-405_
- L250 _public property_ `public DirectoryReference LocalRootPath { get; }`
- L252 _public property_ `public string ClientName { get; }`
- L253 _public property_ `public string BranchPath { get; }`
- L254 _public property_ `public string ProjectPath { get; }`
- L256 _public property_ `public string? StreamName { get; }`
- L258 _public property_ `public string ProjectIdentifier { get; }`
- L259 _public property_ `public bool IsEnterpriseProject { get; }`
- L262 _public property_ `public FileReference LocalFileName { get; }`
- L264 _public property_ `public string ClientRootPath => ...`
- L265 _public property_ `public string ClientFileName => ...`
- L267 _public property_ `public string TelemetryProjectIdentifier => ...`
- L268 _public property_ `public DirectoryReference EngineDir => ...`
- L269 _public property_ `public DirectoryReference? ProjectDir => ...`
- L270 _public property_ `public DirectoryReference DataFolder => ...`
- L271 _public property_ `public DirectoryReference CacheFolder => ...`
- L272 _public property_ `public bool IsUEFNProject => ...`
- L274 _public method_ `public static DirectoryReference GetDataFolder(DirectoryReference workspaceDir)`
- L275 _public method_ `public static DirectoryReference GetCacheFolder(DirectoryReference workspaceDir)`
- L277-290 _public ctor_ `public ProjectInfo(DirectoryReference localRootPath, string clientName, string branchPath, string projectPath, string localProjectPath, string? streamName, string projectIdentifier, bool isEnterpriseProject)`
- L292-355 _public method_ `public static async Task<ProjectInfo> CreateAsync(IPerforceConnection perforceClient, UserWorkspaceSettings settings, CancellationToken cancellationToken)`
- L357-377 _public method_ `public static async Task<string?> TryGetStreamPrefixAsync(IPerforceConnection perforce, string streamName, CancellationToken cancellationToken)`
- L379-385 _public method_ `public static void ValidateBranchPath(string branchPath)`
- L387-399 _public method_ `public static void ValidateProjectPath(string projectPath)`
- L401-404 _public method_ `public ProjectInfo ShallowCopy()`

#### class `UnrealGameSync.WorkspaceUpdate`  
`public class WorkspaceUpdate`  
_public; L407-2556_
- L409 _private* const_ `const string BuildVersionFileName = "/Engine/Build/Build.version"`
- L410 _private* const_ `const string VersionHeaderFileName = "/Engine/Source/Runtime/Launch/Resources/Version.h"`
- L411 _private* const_ `const string ObjectVersionFileName = "/Engine/Source/Runtime/Core/Private/UObject/ObjectVersion.cpp"`
- L413 _private* field_ `static readonly string LocalVersionHeaderFileName = VersionHeaderFileName.Replace('/', Path.DirectorySeparatorChar)`
- L414 _private* field_ `static readonly string LocalObjectVersionFileName = ObjectVersionFileName.Replace('/', Path.DirectorySeparatorChar)`
- L416 _private* field_ `static readonly SemaphoreSlim _updateSemaphore = new SemaphoreSlim(1)`
- L608 _public property_ `public WorkspaceUpdateContext Context { get; }`
- L609 _public property_ `public ProgressValue Progress { get; }`
- L611-614 _public ctor_ `public WorkspaceUpdate(WorkspaceUpdateContext context)`
- L664 _public property_ `public static string ShellScriptExt { get; }`
- L666-678 _public method_ `public static Task<int> ExecuteShellCommandAsync(string commandLine, Action<string> processOutput, CancellationToken cancellationToken)`
- L680-1853 _public method_ `public async Task<(WorkspaceUpdateResult, string)> ExecuteAsync(IPerforceSettings perforceSettings, ProjectInfo project, WorkspaceStateWrapper stateMgr, ILogger logger, CancellationToken cancellationToken)`
- L1855-1862 _private* method_ `static void ProcessOutput(string line, string prefix, ProgressValue progress, ILogger logger)`
- L1864-1874 _private* method_ `static async Task<bool> IsLicenseeVersion(IPerforceConnection perforce, ProjectInfo project, CancellationToken cancellationToken)`
- L1876-1880 _public method_ `public static List<string> GetSyncPaths(ProjectInfo project, WorkspaceUpdateOptions options, string[] syncFilter, ISet<string> additionalPathsToSync, ISet<string> baseContentPaths)`
- L1883-2001 _public method_ `public static List<string> GetRelativeSyncPaths(ProjectInfo project, WorkspaceUpdateOptions options, IReadOnlyList<string>? syncFilter, ISet<string> additionalPathsToSync, ISet<string> baseContentPaths)`
- L2003-2015 _public method_ `public static bool MatchFilter(ProjectInfo project, FileReference fileName, FileFilter filter)`
- L2034-2045 _private* method_ `static void applySyncPath(List<string> syncPaths, string syncPath)`
- L2047-2055 _private* method_ `static Task<(WorkspaceUpdateResult, string)> SyncFileRevisions(IPerforceConnection perforce, string prefix, WorkspaceUpdateContext context, List<string> syncCommands, HashSet<string> remainingDepotPaths, ProgressValue progress, ILogger logger, CancellationToken cancellationToken)`
- L2057-2116 _private* method_ `static async Task<(WorkspaceUpdateResult, string)> SyncFileRevisions(IPerforceConnection perforce, string prefix, WorkspaceUpdateContext context, Queue<List<string>> syncCommandLists, HashSet<string> remainingDepotPaths, ProgressValue progress, ILogger logger, CancellationToken cancellationToken)`
- L2118-2126 _private* method_ `static void UpdateSyncState(string prefix, SyncState state, ProgressValue progress)`
- L2128-2140 _private* method_ `static void UpdateSyncState(string prefix, SyncRecord record, SyncState state, ProgressValue progress, ILogger logger)`
- L2142-2199 _private* method_ `static async Task StaticSyncWorker(int threadNumber, IPerforceConnection perforce, WorkspaceUpdateContext context, SyncState state, Action<SyncRecord, ILogger> syncOutput, ILogger globalLog, CancellationToken cancellationToken)`
- L2201-2268 _private* method_ `static async Task<(WorkspaceUpdateResult, string, string?)> StaticSyncFileRevisions(IPerforceConnection perforce, WorkspaceUpdateContext context, List<string> syncCommands, Action<SyncRecord> syncOutput, CancellationToken cancellationToken)`
- L2270-2304 _public method_ `public static async Task<ConfigFile> ReadProjectConfigFile(IPerforceConnection perforce, ProjectInfo projectInfo, ILogger logger)`
- L2306-2321 _public method_ `public static async Task<IReadOnlyList<string>?> ReadProjectStreamFilter(IPerforceConnection perforce, ConfigFile projectConfigFile, CancellationToken cancellationToken)`
- L2323-2333 _private* method_ `static string FormatTime(long seconds)`
- L2335-2343 _private* method_ `static async Task<bool> HasModifiedSourceFiles(IPerforceConnection perforce, ProjectInfo project, CancellationToken cancellationToken)`
- L2345-2354 _private* method_ `static async Task<List<FStatRecord>> FindUnresolvedFiles(IPerforceConnection perforce, IEnumerable<string> syncPaths, CancellationToken cancellationToken)`
- L2356-2359 _private* method_ `static Task<bool> UpdateVersionFile(IPerforceConnection perforce, string clientPath, Dictionary<string, string> versionStrings, int changeNumber, ILogger logger, CancellationToken cancellationToken)`
- L2361-2419 _private* method_ `static async Task<bool> UpdateVersionFile(IPerforceConnection perforce, string clientPath, int changeNumber, Func<string, string> update, ILogger logger, CancellationToken cancellationToken)`
- L2421-2437 _private* method_ `static string UpdateVersionStrings(string text, Dictionary<string, string> versionStrings)`
- L2439-2477 _private* method_ `static string UpdateBuildVersion(string text, int changelist, int codeChangelist, string branchOrStreamName, bool isLicenseeVersion)`
- L2479-2505 _private* method_ `static async Task<bool> WriteVersionFile(IPerforceConnection perforce, string localPath, string depotPath, string newText, ILogger logger, CancellationToken cancellationToken)`
- L2507-2527 _private* method_ `static bool UpdateVersionLine(ref string line, string prefix, string suffix)`
- L2529-2553 _private* method_ `static string? ReadToken(string line, ref int lineIdx)`
- L2555 _public property_ `public Tuple<string, float> CurrentProgress => ...`

#### class `UnrealGameSync.WorkspaceUpdate.RecordCounter`  
`class RecordCounter : IDisposable`  
_private*; L418-452_
- inherits: `IDisposable`
- L420 _private* field_ `readonly ProgressValue _progress`
- L421 _private* field_ `readonly string _message`
- L422 _private* field_ `int _count`
- L423 _private* field_ `readonly Stopwatch _timer = Stopwatch.StartNew()`
- L425-431 _public ctor_ `public RecordCounter(ProgressValue progress, string message)`
- L433-436 _public method_ `public void Dispose()`
- L438-445 _public method_ `public void Increment()`
- L447-451 _public method_ `public void UpdateMessage()`

#### class `UnrealGameSync.WorkspaceUpdate.SyncBatchBuilder`  
`class SyncBatchBuilder`  
_private*; L454-496_
- L456 _public property_ `public int MaxCommandsPerList { get; }`
- L457 _public property_ `public long MaxSizePerList { get; }`
- L458 _public property_ `public Queue<List<string>> Batches { get; }`
- L460 _private* field_ `List<string>? _commands`
- L461 _private* field_ `List<string>? _deleteCommands`
- L462 _private* field_ `long _size`
- L464-469 _public ctor_ `public SyncBatchBuilder(int? maxCommandsPerList, long? maxSizePerList)`
- L471-495 _public method_ `public void Add(string newCommand, long newSize)`

#### class `UnrealGameSync.WorkspaceUpdate.SyncTree`  
`class SyncTree`  
_private*; L498-606_
- L500 _public field_ `public bool CanUseWildcard`
- L501 _public property_ `public bool CanContainExcludedFiles { get; set; }`
- L502 _public field_ `public int TotalIncludedFiles`
- L503 _public field_ `public long TotalSize`
- L504 _public field_ `public int TotalExcludedFiles`
- L505 _public field_ `public Dictionary<string, long> IncludedFiles = ...`
- L505 _public field_ `public Dictionary< IncludedFiles = new Dictionary<string, long>()`
- L506 _public field_ `public Dictionary<string, SyncTree> NameToSubTree = ...`
- L506 _public field_ `public Dictionary< NameToSubTree = new Dictionary<string, SyncTree>(StringComparer.OrdinalIgnoreCase)`
- L508-512 _public ctor_ `public SyncTree(bool canUseWildcard, bool canContainExcludedFiles)`
- L514-523 _public method_ `public SyncTree FindOrAddSubTree(string name)`
- L525 _public method_ `public void IncludeFile(string path, long size, ILogger logger)`
- L527-544 _private method_ `private void IncludeFile(string fullPath, string path, long size, ILogger logger)`
- L546-560 _public method_ `public void ExcludeFile(string path)`
- L562-572 _public method_ `public void GetOptimizedSyncCommands(string prefix, int changeNumber, SyncBatchBuilder builder)`
- L574-593 _private method_ `private void GetOptimizedSyncCommandsWithExcludedFiles(string prefix, int changeNumber, SyncBatchBuilder builder)`
- L595-605 _private method_ `private void GetOptimizedSyncCommandsWithoutExcludedFiles(string prefix, int changeNumber, SyncBatchBuilder builder)`

#### class `UnrealGameSync.WorkspaceUpdate.SyncFile`  
`class SyncFile`  
_private*; L616-628_
- L618 _public field_ `public string DepotFile`
- L619 _public field_ `public string RelativePath`
- L620 _public field_ `public long Size`
- L622-627 _public ctor_ `public SyncFile(string depotFile, string relativePath, long size)`

#### class `UnrealGameSync.WorkspaceUpdate.SemaphoreScope`  
`class SemaphoreScope : IDisposable`  
_private*; L630-662_
- inherits: `IDisposable`
- L632 _private* field_ `readonly SemaphoreSlim _semaphore`
- L633 _public property_ `public bool HasLock { get; set; }`
- L635-638 _public ctor_ `public SemaphoreScope(SemaphoreSlim semaphore)`
- L640-644 _public method_ `public bool TryAcquire()`
- L646-650 _public method_ `public async Task AcquireAsync(CancellationToken cancellationToken)`
- L652-659 _public method_ `public void Release()`
- L661 _public method_ `public void Dispose()`

#### class `UnrealGameSync.WorkspaceUpdate.SyncState`  
`class SyncState`  
_private*; L2017-2032_
- L2019 _public field_ `public int TotalDepotPaths`
- L2020 _public field_ `public HashSet<string> RemainingDepotPaths`
- L2021 _public field_ `public Queue<List<string>> SyncCommandLists`
- L2022 _public field_ `public string StatusMessage`
- L2023 _public field_ `public WorkspaceUpdateResult Result = WorkspaceUpdateResult.Success`
- L2025-2031 _public ctor_ `public SyncState(HashSet<string> remainingDepotPaths, Queue<List<string>> syncCommandLists)`
