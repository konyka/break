# CSharp / UnrealToolbox

- project root: `Source/Programs/UnrealToolbox`
- files: 34; symbols: 662
- symbol kinds: class=49, const=6, ctor=44, enum=3, enumerator=9, event=10, field=171, interface=6, method=225, property=127, record=8, record struct=1, struct=3
- access marked `*` is implicit (not written in source)

### `Source/Programs/UnrealToolbox/AboutPage.axaml.cs` (UnrealToolbox)


#### class `UnrealToolbox.AboutPage`  
`partial class AboutPage : UserControl`  
_internal*; L9-61_
- inherits: `UserControl`
- L11-28 _public ctor_ `public AboutPage()`
- L30-44 _private method_ `private static void OpenFolder(string path)`
- L46-60 _private method_ `private static void OpenFile(string path)`

### `Source/Programs/UnrealToolbox/App.axaml.cs` (UnrealToolbox)


#### class `UnrealToolbox.App`  
`public sealed partial class App : Application, IToolboxPluginHost, IAsyncDisposable`  
_public; L23-414_
- inherits: `Application, IToolboxPluginHost, IAsyncDisposable`
- desc: Main application class
- L25 _private* field_ `readonly ServiceProvider _serviceProvider`
- L26 _private* field_ `readonly ILogger _logger`
- L28 _private* field_ `WindowIcon? _normalIcon`
- L29 _private* field_ `WindowIcon? _busyIcon`
- L30 _private* field_ `WindowIcon? _pausedIcon`
- L31 _private* field_ `WindowIcon? _errorIcon`
- L32 _private* field_ `DispatcherTimer? _retryUpdateTimer`
- L34 _private* field_ `SettingsWindow? _settingsWindow`
- L36 _private* field_ `Thread? _settingsThread`
- L37 _private* field_ `ManualResetEvent? _settingsThreadStop`
- L42-60 _public ctor_ `public App()` — Constructor
- L63-73 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L76-104 _public method_ `public override void Initialize()` — (inheritdoc)
- L106-136 _private* method_ `void RegisterProtocolHandlers()`
- L138-173 _private method_ `private void WaitForEvents()`
- L175-178 _private* method_ `void CloseMainThread()`
- L180-194 _private* method_ `void ExecuteCommands()`
- L196-209 _private* method_ `void ExecuteCommand(Command command)`
- L211-214 _private method_ `private void UpdateReady()`
- L216-228 _private* method_ `void UpdateReadyMainThread()`
- L230-241 _private* method_ `bool AllWindowsClosed()`
- L243-288 _private method_ `private void UpdateMenu()`
- L290-313 _private* method_ `static void AddMenuItems(IToolCatalogItem item, ToolMenuItem toolMenuItem, NativeMenu menu)`
- L315-327 _private* method_ `static void TrayIcon_RunCommand(IToolCatalogItem item, ToolCommand command)`
- L329-341 _private method_ `private void RefreshPlugins()`
- L343-347 _private method_ `private void TrayIcon_Click(object? sender, EventArgs e)`
- L349-352 _private method_ `private void TrayIcon_Settings(object? sender, EventArgs e)`
- L354-363 _private method_ `private void OpenSettings()`
- L365-368 _private method_ `private void SettingsWindow_Closed(object? sender, EventArgs e)`
- L370-373 _private method_ `private void TrayIcon_Exit(object? sender, EventArgs e)`
- L376-379 _public method_ `public void UpdateStatus()` — (inheritdoc)
- L381-413 _private method_ `private void UpdateStatusMainThread()`

### `Source/Programs/UnrealToolbox/Command.cs` (UnrealToolbox)


#### enum `UnrealToolbox.CommandType`  
`enum CommandType`  
_internal*; L10-13_
- attrs: `[JsonConverter(typeof(JsonStringEnumConverter))]`
- L12 _public* enumerator_ `OpenUrl`

#### class `UnrealToolbox.Command`  
`class Command`  
_internal*; L15-19_
- L17 _public property_ `public CommandType Type { get; set; }`
- L18 _public property_ `public string? Argument { get; set; }`

#### class `UnrealToolbox.CommandList`  
`class CommandList`  
_internal*; L21-24_
- L23 _public property_ `public List<Command> Commands { get; set; }`

#### class `UnrealToolbox.CommandHelper`  
`class CommandHelper`  
_internal*; L26-116_
- L28 _private* const_ `const string MutexName = "UnrealToolbox-CommandMutex"`
- L30 _private* field_ `static readonly FileReference s_commandFile = FileReference.Combine(Program.DataDir, "Commands.json")`
- L32 _private* field_ `static readonly JsonSerializerOptions s_jsonOptions = new JsonSerializerOptions { AllowTrailingCommas = true, DefaultIgnoreCondition = JsonIgnoreCondition.WhenWritingNull, PropertyNameCaseInsensitive = true, PropertyNamingPolicy = JsonNamingPolicy.CamelC ...`
- L41-49 _public method_ `public static void Enqueue(Command command)`
- L51-60 _public method_ `public static List<Command> DequeueAll()`
- L62-82 _private* method_ `static void RunUnderMutex(Action action)`
- L84-106 _private* method_ `static CommandList ReadCommandList()`
- L108-115 _private* method_ `static void WriteCommandList(CommandList commandList)`

### `Source/Programs/UnrealToolbox/GeneralSettingsPage.axaml.cs` (UnrealToolbox)


#### class `UnrealToolbox.GeneralSettingsPage`  
`partial class GeneralSettingsPage : UserControl, IDisposable`  
_internal*; L7-29_
- inherits: `UserControl, IDisposable`
- L9 _private* field_ `readonly GeneralSettingsViewModel _viewModel`
- L11-14 _public ctor_ `public GeneralSettingsPage() : this(SettingsContext.Default)`
- L16-23 _public ctor_ `public GeneralSettingsPage(SettingsContext context)`
- L25-28 _public method_ `public void Dispose()`

### `Source/Programs/UnrealToolbox/GeneralSettingsViewModel.cs` (UnrealToolbox)


#### class `UnrealToolbox.GeneralSettingsViewModel`  
`partial class GeneralSettingsViewModel : ObservableObject, IDisposable`  
_internal*; L14-257_
- inherits: `ObservableObject, IDisposable`
- L21 _private* field_ `readonly SettingsContext _context`
- L22 _private* field_ `readonly IHordeClientProvider _hordeClientProvider`
- L23 _private* field_ `readonly IToolCatalog? _toolCatalog`
- L26 _private* field_ `string _serverUrl = String.Empty` — attrs: `[ObservableProperty]`
- L29 _private* field_ `string _serverStatus = String.Empty` — attrs: `[ObservableProperty]`
- L32 _private* field_ `bool _isConnecting` — attrs: `[ObservableProperty]`
- L34 _private* field_ `bool _requestRefresh`
- L35 _private* field_ `BackgroundTask<ConnectionState>? _connectTask`
- L37 _public property_ `public ToolCatalogViewModel ToolCatalog { get; }`
- L39-42 _public ctor_ `public GeneralSettingsViewModel() : this(SettingsContext.Default)`
- L44-59 _public ctor_ `public GeneralSettingsViewModel(SettingsContext context)`
- L61-71 _public method_ `public async void Dispose()`
- L73-97 _private* method_ `void RunConnectionTask(Func<CancellationToken, Task<ConnectionState>> innerTask)`
- L99-127 _private* method_ `void UpdateConnectionState()`
- L129 _public method_ `public void OpenServer()`
- L132-139 _public method_ `public void StartRefresh()`
- L141 _public method_ `public void CancelRefresh()`
- L144-151 _private* method_ `void UpdateRefresh()`
- L153-197 _private* method_ `async Task<ConnectionState> HandleRefreshAsync(CancellationToken cancellationToken)`
- L199-239 _public method_ `public async Task ConfigureServerAsync()`
- L241-256 _private* method_ `static void OpenBrowser(string url)`

#### record `UnrealToolbox.GeneralSettingsViewModel.ConnectionState`  
`record class ConnectionState(string ServerUrl, string ServerStatus)`  
_private*; L16-19_
- L18 _public property_ `public static ConnectionState NoServerConfigured { get; }`

### `Source/Programs/UnrealToolbox/HordeClientProvider.cs` (UnrealToolbox)


#### class `UnrealToolbox.HordeClientProvider`  
`class HordeClientProvider : IHordeClientProvider, IAsyncDisposable`  
_internal*; L14-185_
- inherits: `IHordeClientProvider, IAsyncDisposable`
- desc: Implements a mechanism for creating scoped HordeClient instances, and modifying configuration settings
- L87 _private* field_ `readonly object _lockObject = new object()`
- L88 _private* field_ `readonly ILogger _logger`
- L89 _private* field_ `readonly ILoggerFactory _loggerFactory`
- L90 _private* field_ `readonly List<Task> _disposeTasks = new List<Task>()`
- L92 _private* field_ `HordeClientLifetime? _lifetime`
- L97 _public event_ `public event Action? OnStateChanged` — Event signalled whenever the connection state changes
- L102 _public event_ `public event Action? OnAccessTokenStateChanged` — Event signalled whenever the access token state changes
- L107-113 _public ctor_ `public HordeClientProvider(ILoggerFactory loggerFactory)` — Constructor
- L116-123 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L126-139 _public method_ `public IHordeClientRef? GetClientRef()` — (inheritdoc)
- L142-151 _public method_ `public void Reset()` — (inheritdoc)
- L153-156 _private* method_ `void OnAccessTokenStateChangedInternal()`
- L158-172 _private* method_ `void CreateLifetime()`
- L174-184 _private* method_ `void DestroyLifetime()`

#### class `UnrealToolbox.HordeClientProvider.HordeClientLifetime`  
`class HordeClientLifetime : IAsyncDisposable`  
_private*; L16-65_
- inherits: `IAsyncDisposable`
- L18 _private* field_ `readonly TaskCompletionSource _refZeroTcs = new TaskCompletionSource(TaskCreationOptions.RunContinuationsAsynchronously)`
- L20 _private* field_ `int _refCount`
- L21 _private* field_ `ServiceProvider _serviceProvider`
- L22 _private* field_ `IHordeClient _hordeClient`
- L24 _public property_ `public IHordeClient Client => ...`
- L26-37 _public ctor_ `public HordeClientLifetime(ILoggerFactory loggerFactory)`
- L39-50 _public method_ `public async ValueTask DisposeAsync()`
- L52-56 _public method_ `public void AddRef()`
- L58-64 _public method_ `public void Release()`

#### class `UnrealToolbox.HordeClientProvider.HordeClientRef`  
`class HordeClientRef : IHordeClientRef`  
_private*; L67-85_
- inherits: `IHordeClientRef`
- L69 _private* field_ `HordeClientLifetime? _lifetime`
- L71 _public property_ `public IHordeClient Client => ...`
- L74-78 _public ctor_ `public HordeClientRef(HordeClientLifetime lifetime)`
- L80-84 _public method_ `public void Dispose()`

### `Source/Programs/UnrealToolbox/IHordeClientProvider.cs` (UnrealToolbox)


#### interface `UnrealToolbox.IHordeClientRef`  
`interface IHordeClientRef : IDisposable`  
_internal*; L10-16_
- inherits: `IDisposable`
- desc: Reference to a Horde client instance. Should be disposed of when done.
- L15 _public* property_ `IHordeClient Client { get; }` — The client instance

#### interface `UnrealToolbox.IHordeClientProvider`  
`interface IHordeClientProvider`  
_internal*; L21-42_
- desc: Accessor for a IHordeClient instance which can be recreated in response to config changes.
- L26 _public* event_ `event Action? OnStateChanged` — Event signalled whenever the connection state changes
- L31 _public* event_ `event Action? OnAccessTokenStateChanged` — Event signalled whenever the access token state changes
- L36 _public* method_ `void Reset()` — Resets the current client and creates a new one with the latest settings.
- L41 _public* method_ `IHordeClientRef? GetClientRef()` — Gets a reference to the current client instance. These references should be kept as short as possible.

### `Source/Programs/UnrealToolbox/IToolCatalog.cs` (UnrealToolbox)


#### interface `UnrealToolbox.IToolCatalog`  
`public interface IToolCatalog`  
_public; L8-30_
- desc: Interface for the tool catalog
- L13 _public* property_ `bool AutoUpdate { get; set; }` — Whether to auto-update tools to latest
- L19 _public* method_ `void RequestUpdate()` — Asynchronously request an update of tool catalog Listen on OnItemsChanged for when items actually update.
- L24 _public* property_ `IReadOnlyList<IToolCatalogItem> Items { get; }` — List of available tools
- L29 _public* event_ `event Action? OnItemsChanged` — Notification that some property of the items list has changed

### `Source/Programs/UnrealToolbox/IToolCatalogItem.cs` (UnrealToolbox)


#### interface `UnrealToolbox.IToolCatalogItem`  
`public interface IToolCatalogItem`  
_public; L11-62_
- desc: Describes a tool available to be installed
- L16 _public* property_ `ToolId Id { get; }` — Identifier for the tool
- L21 _public* property_ `string Name { get; }` — Name of the tool
- L26 _public* property_ `string Description { get; }` — Description for the tool
- L31 _public* property_ `ToolDeploymentInfo? Latest { get; }` — Latest available version of the tool
- L36 _public* property_ `CurrentToolDeploymentInfo? Current { get; }` — The current tool deployment
- L41 _public* property_ `PendingToolDeploymentInfo? Pending { get; }` — Pending tool deployment, if an install or uninstall operation
- L46 _public* event_ `event Action? OnItemChanged` — Callback for the item state changing
- L51 _public* method_ `void Cancel()` — Cancel any pending installation
- L56 _public* method_ `void Install()` — Start installing this tool or updating it to the latest version
- L61 _public* method_ `void Uninstall()` — Start uninstalling this tool

#### record `UnrealToolbox.ToolDeploymentInfo`  
`public record class ToolDeploymentInfo(ToolDeploymentId Id, string Version)`  
_public; L69-69_
- desc: Information about a particular tool deployment

#### record `UnrealToolbox.CurrentToolDeploymentInfo`  
`public record class CurrentToolDeploymentInfo(ToolDeploymentId Id, string Version, DirectoryReference Dir, ToolConfig Config) : ToolDeploymentInfo(Id, Version)`  
_public; L78-78_
- inherits: `ToolDeploymentInfo(Id, Version)`
- desc: Information about an installed tool deployment

#### record `UnrealToolbox.PendingToolDeploymentInfo`  
`public record class PendingToolDeploymentInfo(bool Failed, string? Message, ToolDeploymentInfo? Deployment, bool ShowLogLink = false)`  
_public; L87-87_
- desc: Information about a pending tool installation

### `Source/Programs/UnrealToolbox/IToolboxPlugin.cs` (UnrealToolbox)


#### enum `UnrealToolbox.TrayAppPluginState`  
`enum TrayAppPluginState`  
_internal*; L8-15_
- L10 _public* enumerator_ `Undefined`
- L11 _public* enumerator_ `Ok`
- L12 _public* enumerator_ `Busy`
- L13 _public* enumerator_ `Paused`
- L14 _public* enumerator_ `Error`

#### record `UnrealToolbox.ToolboxPluginStatus`  
`record class ToolboxPluginStatus(TrayAppPluginState State, string? Message = null)`  
_internal*; L20-23_
- desc: Reported status of a plugin
- L22 _public property_ `public static ToolboxPluginStatus Default { get; }`

#### interface `UnrealToolbox.IToolboxPlugin`  
`interface IToolboxPlugin : IAsyncDisposable`  
_internal*; L28-75_
- inherits: `IAsyncDisposable`
- desc: Plugin for the tray app
- L33 _public* property_ `string Name { get; }` — Name of the plugin to show in the settings page
- L38 _public* property_ `IconSource Icon { get; }` — Icon to show on the settings page
- L43 _public* property_ `IReadOnlyList<string> UrlProtocols { get; }` — Url protocol handlers that this plugin supports
- L49 _public* method_ `bool Refresh()` — Refresh the state of this plugin. Called when the application is activated or focussed.
- L54 _public* method_ `bool HandleUrl(Uri url)` — Handles a url passed on the commandline
- L59 _public* method_ `ToolboxPluginStatus GetStatus()` — Get the current status of this plugin
- L64 _public* method_ `bool HasSettingsPage()` — Determines if the plugin should be shown in the settings page
- L69 _public* method_ `Control CreateSettingsPage(SettingsContext context)` — Create a settings page for this plugin
- L74 _public* method_ `void PopulateContextMenu(NativeMenu contextMenu)` — Allow the plugin to customize the tray icon context menu

#### class `UnrealToolbox.ToolboxPluginBase`  
`abstract class ToolboxPluginBase : IToolboxPlugin`  
_internal*; L80-123_
- inherits: `IToolboxPlugin`
- desc: Base implementation of IToolboxPlugin
- L83 _public property_ `public abstract string Name { get; }` — (inheritdoc)
- L86 _public property_ `public virtual IconSource Icon => ...` — (inheritdoc)
- L90 _public property_ `public virtual IReadOnlyList<string> UrlProtocols => ...` — (inheritdoc)
- L94 _public method_ `public virtual bool Refresh()` — (inheritdoc)
- L98 _public method_ `public virtual bool HandleUrl(Uri url)` — (inheritdoc)
- L102 _public method_ `public virtual Control CreateSettingsPage(SettingsContext context)` — (inheritdoc)
- L106-110 _public method_ `public virtual ValueTask DisposeAsync()` — (inheritdoc)
- L113 _public method_ `public virtual ToolboxPluginStatus GetStatus()` — (inheritdoc)
- L117 _public method_ `public virtual bool HasSettingsPage()` — (inheritdoc)
- L121-122 _public method_ `public virtual void PopulateContextMenu(NativeMenu contextMenu)` — (inheritdoc)

### `Source/Programs/UnrealToolbox/IToolboxPluginHost.cs` (UnrealToolbox)


#### interface `UnrealToolbox.IToolboxPluginHost`  
`interface IToolboxPluginHost`  
_internal*; L8-14_
- desc: Interface for the tray app host application
- L13 _public* method_ `void UpdateStatus()` — Notifies the host that a status change has ocurred

### `Source/Programs/UnrealToolbox/JsonConfig.cs` (UnrealToolbox)


#### class `UnrealToolbox.JsonConfig`  
`class JsonConfig<T> where T : class, new()`  
_internal*; L9-73_
- constraints: `where T : class, new()`
- L11 _private* field_ `readonly FileReference _file`
- L12 _private* field_ `static readonly JsonSerializerOptions s_jsonSerializerOptions = GetJsonSerializerOptions()`
- L13 _private* field_ `T _current`
- L14 _private* field_ `byte[] _data`
- L16 _public property_ `public T Current => ...`
- L18-23 _public ctor_ `public JsonConfig(FileReference file)`
- L25-35 _private* method_ `static JsonSerializerOptions GetJsonSerializerOptions()`
- L37-56 _public method_ `public bool LoadSettings()`
- L58-72 _public method_ `public bool UpdateSettings(T settings)`

### `Source/Programs/UnrealToolbox/Notifications/Notifications.cs` (UnrealToolbox)


#### class `UnrealToolbox.ToolboxNotification`  
`class ToolboxNotification`  
_internal*; L14-43_
- desc: A tool notification
- L19 _public property_ `public string Title { get; }` — The title to display
- L24 _public property_ `public string Body { get; }` — The body of the notification
- L29 _public property_ `public bool Force { get; }` — Whether to force the notification regardless of delta time
- L37-42 _public ctor_ `public ToolboxNotification(string title, string body, bool force = false)` — Constructor

#### class `UnrealToolbox.ToolboxNotificationManager`  
`class ToolboxNotificationManager : IAsyncDisposable`  
_internal*; L48-191_
- inherits: `IAsyncDisposable`
- desc: Toolbox notification manager implementation
- L50 _private field_ `private INotificationManager? _platformManager`
- L52 _private field_ `private static readonly object s_lock = new object()`
- L54 _private field_ `private static List<ToolboxNotification> s_notifications = new List<ToolboxNotification>()`
- L55 _private* field_ `readonly BackgroundTask _backgroundTask`
- L58 _private* field_ `DateTime? _lastNotificationTime`
- L59 _private* field_ `string? _lastTitle`
- L60 _private* field_ `string? _lastBody`
- L63 _private method_ `private static extern void SetCurrentProcessExplicitAppUserModelID([MarshalAs(UnmanagedType.LPWStr)] string appId)` — attrs: `[DllImport("shell32.dll", SetLastError = true)]`
- L65-68 _public ctor_ `public ToolboxNotificationManager()`
- L70-103 _private* method_ `async Task PostNotificationsAsync(CancellationToken cancellationToken)`
- L105-126 _public method_ `public void Start()`
- L128-132 _public method_ `public async ValueTask DisposeAsync()`
- L140-146 _public method_ `public static void PostNotification(string title, string body, bool force = false)` — Threead safe notification posting
- L154-190 _private method_ `private void ShowNotification(string title, string body, bool force = false)` — Show a notification,

### `Source/Programs/UnrealToolbox/Plugins/Artifacts/ArtifactsPlugin.cs` (UnrealToolbox)


#### class `UnrealToolbox.Plugins.Artifacts.ArtifactsPlugin`  
`class ArtifactsPlugin : ToolboxPluginBase`  
_internal*; L15-175_
- inherits: `ToolboxPluginBase`
- L17 _private* field_ `readonly IHordeClientProvider _hordeClientProvider`
- L18 _private* field_ `readonly JsonConfig<DownloadSettings> _settings`
- L19 _private* field_ `readonly ILogger _logger`
- L21 _public property_ `public override string Name => ...`
- L24 _public property_ `public override IconSource Icon => ...`
- L27 _public property_ `public override IReadOnlyList<string> UrlProtocols => ...`
- L30-36 _public ctor_ `public ArtifactsPlugin(IHordeClientProvider hordeClientProvider, ILogger<ArtifactsPlugin> logger)`
- L38-47 _public method_ `public override bool HandleUrl(Uri url)`
- L49-54 _public method_ `public override void PopulateContextMenu(NativeMenu contextMenu)`
- L56-59 _private method_ `private void MenuItem_Click(object? sender, EventArgs e)`
- L61-73 _public method_ `public async Task DownloadAsync(Uri? artifactUrl, CancellationToken cancellationToken)`
- L75-141 _public method_ `public async Task DownloadDataAsync(DownloadOptions options, CancellationToken cancellationToken)`
- L144-174 _public method_ `public static void RegisterFileAssociations(string application)` — attrs: `[SupportedOSPlatform("windows")]`

### `Source/Programs/UnrealToolbox/Plugins/Artifacts/DownloadOptions.cs` (UnrealToolbox)


#### class `UnrealToolbox.Plugins.Artifacts.DownloadOptions`  
`class DownloadOptions`  
_internal*; L8-22_
- L10 _public property_ `public Uri BaseUrl { get; set; }`
- L11 _public property_ `public RefName RefName { get; set; }`
- L12 _public property_ `public DirectoryReference OutputDir { get; set; }`
- L13 _public property_ `public bool PatchExistingData { get; set; }`
- L15-21 _public ctor_ `public DownloadOptions(Uri baseUrl, RefName refName, DirectoryReference outputDir, bool patchExistingData)`

### `Source/Programs/UnrealToolbox/Plugins/Artifacts/DownloadOptionsViewModel.cs` (UnrealToolbox)


#### record `UnrealToolbox.Plugins.Artifacts.ArtifactInfo`  
`record class ArtifactInfo(ArtifactId? Id, string? Name, string? Type, StreamId? Stream, CommitId? Commit, string? Description, Uri? JobUrl, IReadOnlyList<string>? Keys, IReadOnlyList<string>? Metadata, Uri BaseUrl, RefName RefName)`  
_internal*; L18-18_

#### class `UnrealToolbox.Plugins.Artifacts.DownloadOptionsViewModel`  
`partial class DownloadOptionsViewModel : ObservableObject`  
_internal*; L20-362_
- inherits: `ObservableObject`
- L22 _private* field_ `readonly Window _window`
- L26 _private* field_ `Uri? _artifactUrl` — attrs: `[ObservableProperty] [NotifyPropertyChangedFor(nameof(InputText))]`
- L29 _private* field_ `bool _showUrlSpinner` — attrs: `[ObservableProperty]`
- L46 _private* field_ `ArtifactInfo? _artifact` — attrs: `[ObservableProperty] [NotifyPropertyChangedFor(nameof(AllowStart))] [NotifyPropertyChangedFor(nameof(BuildName))] [NotifyPropertyChangedFor(nameof(ShowArtifactInfo))] [NotifyPropertyChangedFor(nameof(HasArtifactName))] [NotifyPropertyChange`
- L48-65 _public property_ `public string InputText { get; }`
- L67 _public property_ `public bool ShowBrowse => ...`
- L70 _public property_ `public string OutputDir => ...`
- L75 _public field_ `public string _baseOutputDir` — attrs: `[ObservableProperty] [NotifyPropertyChangedFor(nameof(OutputDir))]`
- L79 _public field_ `public bool _appendBuildName` — attrs: `[ObservableProperty] [NotifyPropertyChangedFor(nameof(OutputDir))]`
- L82 _public field_ `public bool _patchExistingData` — attrs: `[ObservableProperty]`
- L86 _private* field_ `string _errorMessage = String.Empty` — attrs: `[ObservableProperty] [NotifyPropertyChangedFor(nameof(ShowErrorMessage))]`
- L88 _public property_ `public bool ShowArtifactInfo => ...`
- L91 _public property_ `public bool HasArtifactName => ...`
- L93 _public property_ `public string ArtifactName => ...`
- L96 _public property_ `public bool HasArtifactType => ...`
- L98 _public property_ `public string ArtifactType => ...`
- L101 _public property_ `public bool HasArtifactDescription => ...`
- L104 _public property_ `public string ArtifactDescription => ...`
- L107 _public property_ `public bool HasArtifactJobUrl => ...`
- L110 _public property_ `public string ArtifactJobUrl => ...`
- L113-120 _public property_ `public string ArtifactKeys { get; }`
- L122 _public property_ `public string ArtifactMetadata => ...`
- L125 _public property_ `public bool ShowErrorMessage => ...`
- L128 _public property_ `public bool AllowStart => ...`
- L131-144 _public property_ `public string BuildName { get; }`
- L146 _private* field_ `readonly IHordeClientProvider? _hordeClientProvider`
- L148-158 _public ctor_ `public DownloadOptionsViewModel(Window window, DownloadSettings? settings, IHordeClientProvider? hordeClientProvider)`
- L160-164 _private* method_ `static string? GetDefaultDownloadFolder(Window window)`
- L166-178 _public method_ `public DownloadOptions? GetDownloadOptions()`
- L180-254 _public method_ `public async Task<bool> RefreshArtifactAsync()`
- L256-281 _public method_ `public async Task<bool> SelectUrlAsync()`
- L283-303 _public method_ `public async Task<bool> SelectInputFileAsync()`
- L305-327 _public method_ `public void OpenJobUrl()`
- L329-339 _public method_ `public void OpenOutputDir()`
- L341-361 _public method_ `public async Task<bool> SelectOutputDirAsync()`

### `Source/Programs/UnrealToolbox/Plugins/Artifacts/DownloadOptionsWindow.axaml.cs` (UnrealToolbox)


#### class `UnrealToolbox.Plugins.Artifacts.DownloadOptionsWindow`  
`partial class DownloadOptionsWindow : Window`  
_internal*; L8-71_
- inherits: `Window`
- L10 _private* field_ `readonly DownloadOptionsViewModel _viewModel`
- L11 _private* field_ `readonly JsonConfig<DownloadSettings>? _settings`
- L12 _private* field_ `readonly TaskCompletionSource<DownloadOptions?> _result = new TaskCompletionSource<DownloadOptions?>()`
- L14 _public property_ `public Task<DownloadOptions?> Result => ...`
- L16-18 _public ctor_ `public DownloadOptionsWindow() : this(null, null, null)`
- L20-30 _public ctor_ `public DownloadOptionsWindow(Uri? artifactUrl, JsonConfig<DownloadSettings>? settings, IHordeClientProvider? hordeClientProvider)`
- L32-40 _protected method_ `protected override void OnOpened(EventArgs e)`
- L42-45 _public method_ `public async Task SelectInputFileAsync()`
- L47-64 _private* method_ `void Start_Click(object? sender, RoutedEventArgs args)`
- L66-70 _private* method_ `void Cancel_Click(object? sender, RoutedEventArgs args)`

### `Source/Programs/UnrealToolbox/Plugins/Artifacts/DownloadProgressViewModel.cs` (UnrealToolbox)


#### class `UnrealToolbox.Plugins.Artifacts.DownloadProgressViewModel`  
`partial class DownloadProgressViewModel : ObservableObject, IProgress<IExtractStats>`  
_internal*; L9-78_
- inherits: `ObservableObject, IProgress<IExtractStats>`
- L11 _private* field_ `long _size`
- L12 _private* field_ `long _totalSize`
- L15 _private* field_ `string _status = "Starting..."` — attrs: `[ObservableProperty]`
- L18 _private* field_ `bool _isRunning = true` — attrs: `[ObservableProperty]`
- L21 _private* field_ `int _progress` — attrs: `[ObservableProperty]`
- L24 _private* field_ `bool _isProgressBarVisible` — attrs: `[ObservableProperty]`
- L29 _private* field_ `string _errorMessage = String.Empty` — attrs: `[ObservableProperty] [NotifyPropertyChangedFor(nameof(ShowErrorMessage))] [NotifyPropertyChangedFor(nameof(CloseText))]`
- L33 _private* field_ `string? _openFolderPath` — attrs: `[ObservableProperty] [NotifyPropertyChangedFor(nameof(ShowOpenFolder))]`
- L35 _public property_ `public bool ShowErrorMessage => ...`
- L38 _public property_ `public bool ShowOpenFolder => ...`
- L41 _public property_ `public string CloseText => ...`
- L44-49 _public method_ `public void Report(IExtractStats value)`
- L51-55 _public method_ `public void MarkComplete()`
- L57-62 _private* method_ `void ReportOnMainThread(string status, long size)`
- L64-68 _public method_ `public void SetTotalSize(long totalSize)`
- L70-77 _private* method_ `void UpdateProgress()`

### `Source/Programs/UnrealToolbox/Plugins/Artifacts/DownloadProgressWindow.axaml.cs` (UnrealToolbox)


#### class `UnrealToolbox.Plugins.Artifacts.DownloadProgressWindow`  
`partial class DownloadProgressWindow : Window`  
_internal*; L9-39_
- inherits: `Window`
- L11 _private* field_ `readonly DownloadProgressViewModel _viewModel`
- L13-16 _public ctor_ `public DownloadProgressWindow() : this(new DownloadProgressViewModel())`
- L18-24 _public ctor_ `public DownloadProgressWindow(DownloadProgressViewModel viewModel)`
- L26-33 _public method_ `public void OpenFolder(object? sender, RoutedEventArgs args)`
- L35-38 _public method_ `public void Cancel(object? sender, RoutedEventArgs args)`

### `Source/Programs/UnrealToolbox/Plugins/Artifacts/DownloadSettings.cs` (UnrealToolbox)


#### class `UnrealToolbox.Plugins.Artifacts.DownloadSettings`  
`public class DownloadSettings`  
_public; L9-41_
- attrs: `[Serializable]`
- desc: Settings for the artifacts plugin
- L14 _public property_ `public string? OutputDir { get; set; }` — Output directory for the download
- L19 _public property_ `public bool AppendBuildName { get; set; }` — Whether to append the build name to the output directory
- L24 _public property_ `public bool PatchExistingData { get; set; }` — Whether to patch existing data when writing the new build
- L29-30 _public ctor_ `public DownloadSettings()` — Default constructor
- L35-40 _public ctor_ `public DownloadSettings(DownloadSettings other)` — Copy constructor

### `Source/Programs/UnrealToolbox/Plugins/HordeAgent/HordeAgentPlugin.cs` (UnrealToolbox)


#### class `UnrealToolbox.Plugins.HordeAgent.HordeAgentPlugin`  
`class HordeAgentPlugin : ToolboxPluginBase`  
_internal*; L18-575_
- inherits: `ToolboxPluginBase`
- L22 _private* field_ `readonly IToolboxPluginHost _host`
- L23 _private* field_ `readonly IToolCatalog _toolCatalog`
- L24 _private* field_ `readonly ILogger _logger`
- L26 _private* field_ `readonly BackgroundTask _clientTask`
- L27 _private* field_ `readonly BackgroundTask _tickPauseStateTask`
- L29 _private* field_ `readonly FileReference _settingsFile`
- L31 _private* field_ `byte[] _settingsData = Array.Empty<byte>()`
- L32 _private* field_ `HordeAgentSettings _settings = new HordeAgentSettings()`
- L33 _private* field_ `bool _pipeConnected`
- L35 _public property_ `public HordeAgentSettings Settings => ...`
- L37 _private* field_ `AgentSettingsMessage? _agentSettings`
- L39 _private* field_ `ToolboxPluginStatus? _status`
- L40 _private* field_ `ToolboxPluginStatus? _reportStatus`
- L42 _public property_ `public override string Name => ...`
- L44 _public property_ `public override IconSource Icon => ...`
- L46 _public property_ `public bool IsEnabled { get; set; }`
- L48 _public method_ `public override bool HasSettingsPage()`
- L51 _public method_ `public override Control CreateSettingsPage(SettingsContext context)`
- L54-67 _public method_ `public void UpdateSettings(HordeAgentSettings settings)`
- L69-76 _private* method_ `void EnrollWithServer()`
- L78-90 _public ctor_ `public HordeAgentPlugin(IToolboxPluginHost host, ToolCatalog toolCatalog, ILogger<HordeAgentPlugin> logger)`
- L92-104 _public method_ `public override bool Refresh()`
- L106-116 _private* method_ `static JsonSerializerOptions GetJsonSerializerOptions()`
- L118-169 _private* method_ `void LoadSettings()`
- L171-194 _private* method_ `static AgentMode? ReadLegacyMode()`
- L196-204 _public method_ `public override void PopulateContextMenu(NativeMenu contextMenu)`
- L206-212 _public method_ `public override async ValueTask DisposeAsync()`
- L214-225 _private method_ `private void OnOpenLogs(object? sender, EventArgs e)`
- L227-270 _private* method_ `void SetStatus(AgentStatusMessage status)`
- L272-284 _public method_ `public override ToolboxPluginStatus GetStatus()`
- L286-312 _private* method_ `async Task StatusTaskAsync(CancellationToken cancellationToken)`
- L323 _private* method_ `static extern bool GetLastInputInfo(ref LASTINPUTINFO plii)` — attrs: `[DllImport("user32.dll")]`
- L326 _private* method_ `static extern uint GetTickCount()` — attrs: `[DllImport("kernel32.dll")]`
- L352 _private* method_ `static extern bool GlobalMemoryStatusEx(ref MEMORYSTATUSEX lpBuffer)` — attrs: `[DllImport("kernel32.dll", CharSet = CharSet.Auto, SetLastError = true)]`
- L355 _private* method_ `static extern bool GetSystemTimes(out FILETIME lpIdleTime, out FILETIME lpKernelTime, out FILETIME lpUserTime)` — attrs: `[DllImport("kernel32.dll", SetLastError = true)]`
- L358 _private* field_ `bool _enabled`
- L359 _private* field_ `readonly AsyncEvent _statusChangedEvent = new AsyncEvent()`
- L360 _private* field_ `readonly AsyncEvent _enabledChangedEvent = new AsyncEvent()`
- L362-416 _private* method_ `async Task TickPauseStateAsync(CancellationToken cancellationToken)`
- L418-450 _private* method_ `IEnumerable<IdleStat> GetIdleStats()`
- L452 _private* field_ `int _idleCpuPct = 0`
- L453 _private* field_ `int _idleCriticalProcessCount = 0`
- L455-479 _private* method_ `async Task TickCpuStatsAsync(CancellationToken cancellationToken)`
- L481-516 _private* method_ `async Task TickCriticalProcessAsync(CancellationToken cancellationToken)`
- L518-574 _private* method_ `async Task PollForStatusUpdatesAsync(CancellationToken cancellationToken)`

#### record struct `UnrealToolbox.Plugins.HordeAgent.HordeAgentPlugin.IdleStat`  
`record struct IdleStat(string Name, long Value, long MinValue)`  
_private*; L20-20_

#### struct `UnrealToolbox.Plugins.HordeAgent.HordeAgentPlugin.LASTINPUTINFO`  
`struct LASTINPUTINFO`  
_private*; L316-320_
- attrs: `[StructLayout(LayoutKind.Sequential)]`
- L318 _public field_ `public int cbSize`
- L319 _public field_ `public uint dwTime`

#### struct `UnrealToolbox.Plugins.HordeAgent.HordeAgentPlugin.FILETIME`  
`struct FILETIME`  
_private*; L329-335_
- attrs: `[StructLayout(LayoutKind.Sequential)]`
- L331 _public field_ `public uint dwLowDateTime`
- L332 _public field_ `public uint dwHighDateTime`
- L334 _public property_ `public readonly ulong Total => ...`

#### struct `UnrealToolbox.Plugins.HordeAgent.HordeAgentPlugin.MEMORYSTATUSEX`  
`struct MEMORYSTATUSEX`  
_private*; L338-349_
- attrs: `[StructLayout(LayoutKind.Sequential)]`
- L340 _public field_ `public int dwLength`
- L341 _public field_ `public uint dwMemoryLoad`
- L342 _public field_ `public ulong ullTotalPhys`
- L343 _public field_ `public ulong ullAvailPhys`
- L344 _public field_ `public ulong ullTotalPageFile`
- L345 _public field_ `public ulong ullAvailPageFile`
- L346 _public field_ `public ulong ullTotalVirtual`
- L347 _public field_ `public ulong ullAvailVirtual`
- L348 _public field_ `public ulong ullAvailExtendedVirtual`

### `Source/Programs/UnrealToolbox/Plugins/HordeAgent/HordeAgentSettings.cs` (UnrealToolbox)


#### enum `UnrealToolbox.Plugins.HordeAgent.AgentMode`  
`public enum AgentMode`  
_public; L7-12_
- L9 _public* enumerator_ `Workstation = 0`
- L10 _public* enumerator_ `Dedicated = 1`
- L11 _public* enumerator_ `Disabled = 2`

#### class `UnrealToolbox.Plugins.HordeAgent.HordeAgentSettings`  
`public class HordeAgentSettings`  
_public; L15-20_
- attrs: `[Serializable]`
- L17 _public property_ `public AgentMode? Mode { get; set; }`
- L18 _public property_ `public IdleSettings Idle { get; set; }`
- L19 _public property_ `public CpuUtilizationSettings Cpu { get; set; }`

#### class `UnrealToolbox.Plugins.HordeAgent.IdleSettings`  
`public class IdleSettings`  
_public; L23-30_
- attrs: `[Serializable]`
- L25 _public property_ `public int MinIdleTimeSecs { get; set; }`
- L26 _public property_ `public int MinIdleCpuPct { get; set; }`
- L27 _public property_ `public int MinFreeVirtualMemMb { get; set; }`
- L29 _public property_ `public string[] CriticalProcesses { get; set; }`

#### class `UnrealToolbox.Plugins.HordeAgent.CpuUtilizationSettings`  
`public class CpuUtilizationSettings`  
_public; L33-37_
- attrs: `[Serializable]`
- L35 _public property_ `public int CpuCount { get; set; }`
- L36 _public property_ `public double CpuMultiplier { get; set; }`

### `Source/Programs/UnrealToolbox/Plugins/HordeAgent/HordeAgentSettingsPage.axaml.cs` (UnrealToolbox)


#### class `UnrealToolbox.Plugins.HordeAgent.HordeAgentSettingsPage`  
`partial class HordeAgentSettingsPage : UserControl`  
_internal*; L7-24_
- inherits: `UserControl`
- L9-12 _public ctor_ `public HordeAgentSettingsPage() : this(SettingsContext.Default, null)`
- L14-23 _public ctor_ `public HordeAgentSettingsPage(SettingsContext context, HordeAgentPlugin? plugin)`

### `Source/Programs/UnrealToolbox/Plugins/HordeAgent/HordeAgentSettingsViewModel.cs` (UnrealToolbox)


#### class `UnrealToolbox.Plugins.HordeAgent.HordeAgentSettingsViewModel`  
`partial class HordeAgentSettingsViewModel : ObservableObject`  
_internal*; L10-139_
- inherits: `ObservableObject`
- L12 _private* field_ `readonly SettingsContext _context`
- L13 _private* field_ `readonly HordeAgentPlugin? _plugin`
- L15 _private* field_ `AgentMode _mode`
- L17 _private* method_ `static string GetPropertyName(AgentMode mode)`
- L25-40 _private* method_ `void SetModeIfTrue(AgentMode mode, bool value)`
- L42-46 _public property_ `public bool IsDedicatedMode { get; set; }`
- L48-52 _public property_ `public bool IsWorkstationMode { get; set; }`
- L54-58 _public property_ `public bool IsDisabled { get; set; }`
- L61 _private* field_ `int _minIdleTimeSecs` — attrs: `[ObservableProperty]`
- L64 _private* field_ `int _minFreeMemoryMb` — attrs: `[ObservableProperty]`
- L67 _private* field_ `int _minFreeCpuPct` — attrs: `[ObservableProperty]`
- L70 _private* field_ `int _cpuCount` — attrs: `[ObservableProperty]`
- L73 _private* field_ `double _cpuMultiplier` — attrs: `[ObservableProperty]`
- L76 _private* field_ `string _sandboxDir = "C:\\Dump"` — attrs: `[ObservableProperty]`
- L78-90 _public ctor_ `public HordeAgentSettingsViewModel(SettingsContext context, HordeAgentPlugin? plugin)`
- L92-109 _protected method_ `protected override void OnPropertyChanged(PropertyChangedEventArgs e)`
- L111-116 _public method_ `public void OpenSandbox()`
- L118-138 _public method_ `public async Task MoveSandboxAsync()`

### `Source/Programs/UnrealToolbox/Plugins/HordeProxy/HordeProxyPlugin.cs` (UnrealToolbox)


#### class `UnrealToolbox.Plugins.HordeProxy.HordeProxyPlugin`  
`class HordeProxyPlugin : ToolboxPluginBase`  
_internal*; L16-163_
- inherits: `ToolboxPluginBase`
- L18 _private* field_ `readonly BackgroundTask _serverTask`
- L19 _private* field_ `readonly IHordeClientProvider _hordeClientProvider`
- L20 _private* field_ `readonly AsyncEvent _restartServerEvent = new AsyncEvent()`
- L21 _private* field_ `readonly SynchronizationContext? _synchronizationContext`
- L22 _private* field_ `readonly JsonConfig<HordeProxySettings> _settings`
- L24 _private* field_ `string _status = "Starting..."`
- L26 _public property_ `public HordeProxySettings Settings => ...`
- L28 _public event_ `public event Action? OnStatusChanged`
- L30 _public property_ `public override string Name => ...`
- L32 _public property_ `public string Status => ...`
- L34 _public property_ `public override IconSource Icon => ...`
- L36-48 _public ctor_ `public HordeProxyPlugin(IHordeClientProvider hordeClientProvider)`
- L50 _public method_ `public override bool HasSettingsPage()`
- L53 _public method_ `public override Control CreateSettingsPage(SettingsContext context)`
- L56-68 _private* method_ `void SetStatus(string status)`
- L70-76 _public method_ `public void UpdateSettings(HordeProxySettings settings)`
- L78-84 _public method_ `public override async ValueTask DisposeAsync()`
- L86 _public method_ `public override bool Refresh()`
- L89-92 _private* method_ `void OnStateChanged()`
- L94-137 _private* method_ `async Task RunServerAsync(CancellationToken cancellationToken)`
- L139-162 _private* method_ `static async Task ForwardRequestAsync(HttpContext context)`

### `Source/Programs/UnrealToolbox/Plugins/HordeProxy/HordeProxySettings.cs` (UnrealToolbox)


#### class `UnrealToolbox.Plugins.HordeProxy.HordeProxySettings`  
`public class HordeProxySettings`  
_public; L8-12_
- attrs: `[Serializable]`
- L10 _public property_ `public bool Enabled { get; set; }`
- L11 _public property_ `public int Port { get; set; }`

### `Source/Programs/UnrealToolbox/Plugins/HordeProxy/HordeProxySettingsPage.axaml.cs` (UnrealToolbox)


#### class `UnrealToolbox.Plugins.HordeProxy.HordeProxySettingsPage`  
`partial class HordeProxySettingsPage : UserControl`  
_internal*; L7-20_
- inherits: `UserControl`
- L9-12 _public ctor_ `public HordeProxySettingsPage() : this(null)`
- L14-19 _public ctor_ `public HordeProxySettingsPage(HordeProxyPlugin? plugin)`

### `Source/Programs/UnrealToolbox/Plugins/HordeProxy/HordeProxySettingsViewModel.cs` (UnrealToolbox)


#### class `UnrealToolbox.Plugins.HordeProxy.HordeProxySettingsViewModel`  
`partial class HordeProxySettingsViewModel : ObservableObject`  
_internal*; L8-72_
- inherits: `ObservableObject`
- L10 _private* field_ `readonly HordeProxyPlugin? _plugin`
- L12 _private* field_ `int _pendingUpdate`
- L15 _private* field_ `bool _enabled` — attrs: `[ObservableProperty]`
- L18 _private* field_ `int _port` — attrs: `[ObservableProperty]`
- L21 _private* field_ `string _status = String.Empty` — attrs: `[ObservableProperty]`
- L23-36 _public ctor_ `public HordeProxySettingsViewModel(HordeProxyPlugin? plugin)`
- L38 _private* method_ `void OnStatusChanged()`
- L41-50 _protected method_ `protected override void OnPropertyChanged(PropertyChangedEventArgs e)`
- L52-60 _private* method_ `async void ApplySettingsAsync(int currentUpdate)`
- L62-71 _private* method_ `void ApplySettings()`

### `Source/Programs/UnrealToolbox/Program.cs` (UnrealToolbox)


#### class `UnrealToolbox.Program`  
`static class Program`  
_internal*; L10-160_
- L12 _private* const_ `const string MutexName = "UnrealToolbox-Mutex"`
- L13 _public const_ `public const string CloseEventName = "UnrealToolbox-Close"`
- L14 _public const_ `public const string RefreshEventName = "UnrealToolbox-Refresh"`
- L15 _public const_ `public const string SettingsEventName = "UnrealToolbox-Settings"`
- L16 _public const_ `public const string CommandEventName = "UnrealToolbox-Command"`
- L18 _public property_ `public static SelfUpdateState? Update { get; set; }`
- L20 _public property_ `public static DirectoryReference DataDir { get; }`
- L22 _public property_ `public static FileReference LogFile { get; }`
- L25-45 _public method_ `public static int Main(string[] args)` — attrs: `[STAThread]`
- L47-102 _private* method_ `static int RealMain(string[] args)`
- L105-110 _public method_ `public static AppBuilder BuildAvaloniaApp()`
- L112-123 _private* method_ `static DirectoryReference GetDataDir()`
- L125-135 _private* method_ `static EventWaitHandle? CreateNamedEvent(string name)`
- L138 _private* method_ `static extern uint SetForegroundWindow(nint hWnd)` — attrs: `[DllImport("user32.dll")]`
- L140-159 _public method_ `public static void BringWindowToFront(Window window)`

#### class `UnrealToolbox.SingleInstanceMutex`  
`class SingleInstanceMutex : IDisposable`  
_internal*; L162-202_
- inherits: `IDisposable`
- L164 _private* field_ `readonly Mutex _mutex`
- L165 _private* field_ `bool _locked`
- L167-170 _public ctor_ `public SingleInstanceMutex(string name)`
- L172-179 _public method_ `public void Release()`
- L181-195 _public method_ `public bool Wait(int timeout)`
- L197-201 _public method_ `public void Dispose()`

### `Source/Programs/UnrealToolbox/SelfUpdateService.cs` (UnrealToolbox)


#### class `UnrealToolbox.SelfUpdateState`  
`class SelfUpdateState`  
_internal*; L14-238_
- L23 _private* field_ `readonly string? _currentVersion`
- L24 _private* field_ `readonly DirectoryReference _baseDir`
- L25 _private* field_ `readonly JsonConfig<JsonState> _config`
- L26 _private* field_ `readonly string[] _args`
- L27 _private* field_ `readonly bool _isLaunchApp`
- L29 _public property_ `public string? CurrentVersionString => ...`
- L32 _public property_ `public string? LatestVersion => ...`
- L35 _public property_ `public DirectoryReference LatestDir => ...`
- L38 _public property_ `public DirectoryReference UpdateDir => ...`
- L41-45 _public property_ `public string? UpdateVersion { get; set; }`
- L47-62 _public ctor_ `public SelfUpdateState(DirectoryReference baseDir, string[] args)`
- L64 _public method_ `public bool IsUpdatePending()`
- L67-78 _private* method_ `void UpdateState(Action<JsonState> update)`
- L80-90 _public method_ `public static SelfUpdateState? TryCreate(string appName, string[] args)`
- L92-135 _public method_ `public bool TryLaunchLatest()`
- L137-149 _private* method_ `static bool TryParseVersion(string? version, [NotNullWhen(true)] out VersionNumber? versionNumber)`
- L151 _private* method_ `bool ShouldLaunchLatest(DirectoryReference latestDir)`
- L157-175 _public method_ `public bool ShouldUpdateTo(string? version)` — Test whether the current instance should update to the given version
- L182-203 _private* method_ `static string? ReadVersion(DirectoryReference dir)`
- L205-237 _private* method_ `static bool Launch(string executable, string[] args)`

#### class `UnrealToolbox.SelfUpdateState.JsonState`  
`class JsonState`  
_private*; L16-21_
- L18 _public property_ `public string? LaunchApp { get; set; }`
- L19 _public property_ `public string? LatestVersion { get; set; }`
- L20 _public property_ `public string? UpdateVersion { get; set; }`

#### class `UnrealToolbox.SelfUpdateState.VersionFile`  
`class VersionFile`  
_private*; L177-180_
- L179 _public property_ `public string? Version { get; set; }`

#### class `UnrealToolbox.SelfUpdateService`  
`class SelfUpdateService : IAsyncDisposable`  
_internal*; L240-334_
- inherits: `IAsyncDisposable`
- L242 _private* property_ `static ToolId ToolId { get; }`
- L244 _private* field_ `readonly IHordeClientProvider _hordeClientProvider`
- L245 _private* field_ `readonly BackgroundTask _backgroundTask`
- L246 _private* field_ `readonly ILogger _logger`
- L248 _public event_ `public event Action? OnUpdateReady`
- L250-255 _public ctor_ `public SelfUpdateService(IHordeClientProvider hordeClientProvider, ILogger<SelfUpdateService> logger)`
- L257-260 _public method_ `public void Start()`
- L262-265 _public method_ `public async ValueTask DisposeAsync()`
- L267-285 _private* method_ `async Task CheckForUpdatesAsync(CancellationToken cancellationToken)`
- L287-333 _private* method_ `async Task CheckForUpdateAsync(CancellationToken cancellationToken)`

### `Source/Programs/UnrealToolbox/SettingsWindow.axaml.cs` (UnrealToolbox)


#### record `UnrealToolbox.SettingsContext`  
`record class SettingsContext(Window? SettingsWindow, IServiceProvider ServiceProvider)`  
_internal*; L9-12_
- L11 _public property_ `public static SettingsContext Default { get; }`

#### class `UnrealToolbox.SettingsWindow`  
`partial class SettingsWindow : Window`  
_internal*; L14-131_
- inherits: `Window`
- L16 _private* field_ `readonly IServiceProvider? _serviceProvider`
- L17 _private* field_ `readonly Dictionary<string, IToolboxPlugin> _typeToPlugin = ...`
- L17 _private* field_ `readonly Dictionary< _typeToPlugin = new Dictionary<string, IToolboxPlugin>()`
- L18 _private* field_ `readonly Dictionary<IToolboxPlugin, Control> _pluginPages = ...`
- L18 _private* field_ `readonly Dictionary< _pluginPages = new Dictionary<IToolboxPlugin, Control>()`
- L20 _private* field_ `AboutPage? _aboutPage`
- L21 _private* field_ `GeneralSettingsPage? _generalSettingsPage`
- L23-25 _public ctor_ `public SettingsWindow() : this(null!)`
- L27-37 _public ctor_ `public SettingsWindow(IServiceProvider serviceProvider)`
- L39-70 _public method_ `public void Refresh()`
- L72-86 _private* method_ `void OnActivated(object? sender, EventArgs e)`
- L88-94 _private method_ `private void NavView_SelectionChanged(object? sender, NavigationViewSelectionChangedEventArgs e)`
- L96-119 _private method_ `private void NavView_UpdateContent()`
- L121-130 _private method_ `private Control CreatePluginPage(IToolboxPlugin plugin, SettingsContext context)`

### `Source/Programs/UnrealToolbox/ToolCatalog.cs` (UnrealToolbox)


#### class `UnrealToolbox.ToolCatalog`  
`class ToolCatalog : IToolCatalog, IAsyncDisposable`  
_internal*; L18-1129_
- inherits: `IToolCatalog, IAsyncDisposable`
- L196 _private* field_ `readonly IHordeClientProvider _hordeClientProvider`
- L197 _private* field_ `readonly ILogger _logger`
- L198 _private* field_ `readonly object _workerThreadLockObject = new object()`
- L199 _private* field_ `readonly AsyncEvent _updateEvent`
- L200 _private* field_ `readonly BackgroundTask _updateTask`
- L201 _private* field_ `readonly AsyncEvent _cleanupEvent`
- L202 _private* field_ `readonly BackgroundTask _cleanupTask`
- L203 _private* field_ `readonly SemaphoreSlim _msiSemaphore`
- L205 _private* field_ `readonly SynchronizationContext? _mainThreadSynchronizationContext`
- L207 _private* field_ `IReadOnlyDictionary<ToolId, Item> _mainThreadItems`
- L207 _private* field_ `IReadOnlyDictionary< _mainThreadItems`
- L208 _private* field_ `IReadOnlyList<IToolCatalogItem> _mainThreadItemList`
- L209 _private* property_ `IReadOnlyList<IToolCatalogItem> IToolCatalog.Items => ...`
- L211 _private* field_ `IReadOnlyDictionary<ToolId, Item> _items`
- L211 _private* field_ `IReadOnlyDictionary< _items`
- L213 _private* field_ `Uri? _serverUri`
- L214 _private* field_ `bool _autoUpdate = true`
- L216 _public event_ `public event Action? OnItemsChanged`
- L218 _private* field_ `static readonly JsonSerializerOptions s_jsonSerializerOptions = new JsonSerializerOptions { AllowTrailingCommas = true, PropertyNameCaseInsensitive = true, PropertyNamingPolicy = JsonNamingPolicy.CamelCase, WriteIndented = true }`
- L220-231 _public property_ `public bool AutoUpdate { get; set; }`
- L234-237 _public method_ `public void RequestUpdate()` — (inheritdoc)
- L239-255 _public ctor_ `public ToolCatalog(IHordeClientProvider hordeClientProvider, ILogger<ToolCatalog> logger)`
- L257 _public method_ `public static DirectoryReference GetToolsDir()`
- L258 _public method_ `public static FileReference GetConfigFile()`
- L260-270 _private* method_ `void PostMainThreadUpdate()`
- L272-303 _private* method_ `void UpdateMainThread()`
- L305-309 _private* method_ `void UpdateMainThreadItemsState()`
- L311-317 _public method_ `public void Start()`
- L319-335 _public method_ `public async Task StopAsync(CancellationToken cancellationToken)`
- L337-343 _public method_ `public async ValueTask DisposeAsync()`
- L345-348 _private* method_ `void OnServerChange()`
- L350-353 _private* method_ `static DirectoryReference GetToolDir(ToolId toolId, ToolDeploymentId deploymentId)`
- L355-376 _private* method_ `ToolConfig LoadToolConfig(DirectoryReference toolDir)`
- L378-406 _private* method_ `IReadOnlyDictionary<ToolId, Item> LoadState()`
- L408-428 _private* method_ `async Task SaveStateAsync(CancellationToken cancellationToken)`
- L430-442 _private* method_ `void CancelDeployment(Item item, ToolDeploymentInfo? deployment)`
- L444-460 _private* method_ `void UpdateDeployment(Item item, IToolDeployment? deployment)`
- L462-494 _private* method_ `async Task UpdateCurrentDeploymentAsync(Item item, IToolDeployment? deployment, ToolDeploymentInfo deploymentInfo, CancellationToken cancellationToken)`
- L496-563 _private* method_ `async Task InstallAsync(Item item, DirectoryReference toolDir, ToolDeploymentInfo deploymentInfo, CancellationToken cancellationToken)`
- L565-577 _private* method_ `static bool IsMsiInstalled(string msiProductId)`
- L579-588 _private* method_ `async Task<bool> UninstallAsync(Item item, CancellationToken cancellationToken)`
- L590-647 _private* method_ `async Task<bool> UninstallInternalAsync(Item item, CancellationToken cancellationToken)`
- L649-720 _private* method_ `async Task<int> RunCommandAsync(string toolName, ToolCommand command, string workingDir, bool elevateProcess, bool hidden, CancellationToken cancellationToken)`
- L722-736 _private* method_ `void UpdateStateAndNotify(Item item, Func<ItemState, ItemState> update)`
- L738-765 _private* method_ `static string GetItemStateMessage(ItemState state)`
- L769-797 _private* method_ `async Task CleanupAsync(CancellationToken cancellationToken)`
- L799-884 _private* method_ `bool CleanupOnce()`
- L886-898 _private* method_ `bool TryRenameDir(DirectoryInfo dirInfo, string newName)`
- L900-912 _private* method_ `bool ForceDeleteDir(DirectoryInfo dirInfo)`
- L914-926 _private* method_ `bool TryDeleteDir(DirectoryInfo dirInfo)`
- L932-980 _private* method_ `async Task UpdateAsync(CancellationToken cancellationToken)`
- L982-1003 _private* method_ `async Task PollForUpdatesOnceAsync(CancellationToken cancellationToken)`
- L1005-1062 _private* method_ `void SetTools(IEnumerable<ITool> tools)`
- L1064 _private* property_ `static IReadOnlySet<string> HostPlatformRids { get; }`
- L1066-1077 _private* method_ `static bool ShouldIncludeTool(ITool tool)`
- L1079-1126 _private* method_ `static HashSet<string> GetHostPlatformRids()`

#### record `UnrealToolbox.ToolCatalog.ItemState`  
`record class ItemState(string Name, string Description, string? MsiProductId, CurrentToolDeploymentInfo? Current, PendingToolDeploymentInfo? Pending, IToolDeployment? Latest)`  
_private*; L20-20_

#### class `UnrealToolbox.ToolCatalog.Item`  
`class Item : IToolCatalogItem`  
_private*; L23-83_
- attrs: `[DebuggerDisplay("{Id}")]`
- inherits: `IToolCatalogItem`
- L25 _public property_ `public ToolId Id { get; }`
- L27 _private* field_ `readonly ToolCatalog _catalog`
- L30 _public field_ `public ItemState _mainThreadState`
- L31 _public field_ `public ToolDeploymentInfo? _mainThreadLatest`
- L34 _private* property_ `string IToolCatalogItem.Name => ...`
- L35 _private* property_ `string IToolCatalogItem.Description => ...`
- L36 _private* property_ `ToolDeploymentInfo? IToolCatalogItem.Latest => ...`
- L37 _private* property_ `CurrentToolDeploymentInfo? IToolCatalogItem.Current => ...`
- L38 _private* property_ `PendingToolDeploymentInfo? IToolCatalogItem.Pending => ...`
- L40 _public field_ `public ItemState _state`
- L41 _public field_ `public DeploymentTask? _deploymentTask`
- L42 _public event_ `public event Action? OnItemChanged`
- L44-52 _public ctor_ `public Item(ToolCatalog catalog, ToolId id, ItemState state)`
- L54-58 _public method_ `public void UpdateMainThreadState()`
- L60-63 _public method_ `public void NotifyChanged()`
- L65-69 _public method_ `public void SetState(ItemState state)`
- L71 _public method_ `public void Cancel()`
- L78 _public method_ `public void Install()`
- L81 _public method_ `public void Uninstall()`

#### class `UnrealToolbox.ToolCatalog.DeploymentTask`  
`class DeploymentTask`  
_private*; L86-140_
- L89 _public property_ `public ToolDeploymentInfo Deployment { get; }`
- L91 _private* field_ `CancellationTokenSource? _cancellationSource`
- L92 _private* field_ `readonly Task _task`
- L94-102 _public ctor_ `public DeploymentTask(ToolDeploymentInfo deployment, Func<CancellationToken, Task> func, DeploymentTask? lastDeploymentTask)`
- L104-127 _private* method_ `async Task RunAsync(Func<CancellationToken, Task> func, DeploymentTask? lastDeploymentTask, CancellationTokenSource cancellationSource)`
- L129 _public method_ `public Task WaitAsync(CancellationToken cancellationToken)`
- L132-139 _public method_ `public void Cancel()`

#### class `UnrealToolbox.ToolCatalog.JsonState`  
`class JsonState`  
_private*; L144-148_
- L146 _public property_ `public bool AutoUpdate { get; set; }`
- L147 _public property_ `public List<JsonItemState> Items { get; set; }`

#### class `UnrealToolbox.ToolCatalog.JsonItemState`  
`class JsonItemState`  
_private*; L150-172_
- L152 _public property_ `public ToolId Id { get; set; }`
- L153 _public property_ `public string Name { get; set; }`
- L154 _public property_ `public string Description { get; set; }`
- L155 _public property_ `public string? MsiProductId { get; set; }`
- L156 _public property_ `public JsonDeploymentState? Current { get; set; }`
- L158-162 _public ctor_ `public JsonItemState()`
- L164-171 _public ctor_ `public JsonItemState(ToolId id, ItemState state)`

#### class `UnrealToolbox.ToolCatalog.JsonDeploymentState`  
`class JsonDeploymentState`  
_private*; L174-192_
- L176 _public property_ `public ToolDeploymentId Id { get; set; }`
- L177 _public property_ `public string Version { get; set; }`
- L179-182 _public ctor_ `public JsonDeploymentState()`
- L184-188 _public ctor_ `public JsonDeploymentState(ToolDeploymentInfo current)`
- L190 _public method_ `public ToolDeploymentInfo ToToolDeploymentInfo()`

### `Source/Programs/UnrealToolbox/ToolCatalogViewModel.cs` (UnrealToolbox)


#### class `UnrealToolbox.ToolCatalogViewModel`  
`partial class ToolCatalogViewModel : ObservableObject, IDisposable`  
_internal*; L11-92_
- inherits: `ObservableObject, IDisposable`
- L13 _private* field_ `readonly IToolCatalog? _catalog`
- L14 _private* field_ `readonly Dictionary<IToolCatalogItem, ToolCatalogItemViewModel> _items = ...`
- L14 _private* field_ `readonly Dictionary< _items = new Dictionary<IToolCatalogItem, ToolCatalogItemViewModel>()`
- L16 _public property_ `public ObservableCollection<ToolCatalogItemViewModel> Items { get; }`
- L18 _public property_ `public bool ShowTools => ...`
- L21 _private* field_ `bool _autoUpdate = true` — attrs: `[ObservableProperty]`
- L23-25 _public ctor_ `public ToolCatalogViewModel() : this(null)`
- L27-40 _public ctor_ `public ToolCatalogViewModel(IToolCatalog? catalog)`
- L42-50 _protected method_ `protected override void OnPropertyChanged(PropertyChangedEventArgs e)`
- L52-62 _public method_ `public void Dispose()`
- L64-91 _private* method_ `void RefreshItems()`

#### class `UnrealToolbox.ToolCatalogItemViewModel`  
`partial class ToolCatalogItemViewModel : ObservableObject, IDisposable`  
_internal*; L94-197_
- inherits: `ObservableObject, IDisposable`
- L96 _private* field_ `readonly IToolCatalogItem _item`
- L98-103 _public ctor_ `public ToolCatalogItemViewModel(IToolCatalogItem item)`
- L105-108 _public method_ `public void Dispose()`
- L111 _private* field_ `string _name = String.Empty` — attrs: `[ObservableProperty]`
- L114 _private* field_ `string _description = String.Empty` — attrs: `[ObservableProperty]`
- L117 _private* field_ `string _status = String.Empty` — attrs: `[ObservableProperty]`
- L120 _private* field_ `bool _showStatusLink` — attrs: `[ObservableProperty]`
- L123 _private* field_ `bool _showStatusText` — attrs: `[ObservableProperty]`
- L126 _private* field_ `bool _showAdd` — attrs: `[ObservableProperty]`
- L129 _private* field_ `bool _showUpdate` — attrs: `[ObservableProperty]`
- L132 _private* field_ `bool _showRemove` — attrs: `[ObservableProperty]`
- L135 _private* field_ `bool _isBusy` — attrs: `[ObservableProperty]`
- L137-178 _internal method_ `internal void UpdateFromModel()`
- L181-187 _public method_ `public void ShowLog()` — attrs: `[SuppressMessage("Performance", "CA1822:Mark members as static", Justification = "Avalonia cannot call static methods as a binding")]`
- L189 _public method_ `public void Add()`
- L192 _public method_ `public void Remove()`
- L195 _public method_ `public void Update()`

### `Source/Programs/UnrealToolbox/ToolConfig.cs` (UnrealToolbox)


#### class `UnrealToolbox.ToolConfig`  
`public class ToolConfig`  
_public; L8-39_
- desc: Configuration for a tool that can be shown in the launcher
- L13 _public property_ `public ToolMenuItem? PopupMenu { get; set; }` — Popup menu item for the tool
- L18 _public property_ `public bool ManualInstall { get; set; }` — Whether the install/uninstall for this tool needs to be triggered manually
- L23 _public property_ `public bool RequiresElevation { get; set; }` — Whether the install/uninstall for this tool needs administrator or root privileges
- L28 _public property_ `public bool Hidden { get; set; }` — Whether the install/uninstall process window should be hidden
- L33 _public property_ `public ToolCommand? InstallCommand { get; set; }` — Command to run when installing
- L38 _public property_ `public ToolCommand? UninstallCommand { get; set; }` — Command to run when uninstalling

#### class `UnrealToolbox.ToolMenuItem`  
`public class ToolMenuItem`  
_public; L44-60_
- desc: Menu item for the tool
- L49 _public property_ `public string? Label { get; set; }` — Text to display for the menu item. If null, or a sequence of hyphens, will create a menu separator.
- L54 _public property_ `public ToolCommand? Command { get; set; }` — Command to run when the menu item is clicked. Will be executed in the root directory of the downloaded tool.
- L59 _public property_ `public List<ToolMenuItem>? Children { get; set; }` — Child menu items. Cannot be specified at the same time as a tool.

#### class `UnrealToolbox.ToolCommand`  
`public class ToolCommand`  
_public; L65-76_
- desc: Command to run for a menu item.
- L70 _public property_ `public string FileName { get; set; }` — Executable to run
- L75 _public property_ `public List<string>? Arguments { get; set; }` — Command line arguments for the tool
