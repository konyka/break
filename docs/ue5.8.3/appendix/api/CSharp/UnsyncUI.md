# CSharp / UnsyncUI

- project root: `Source/Programs/UnsyncUI/UnsyncUI`
- files: 11; symbols: 537
- symbol kinds: class=53, ctor=25, enum=3, enumerator=4, event=2, field=129, interface=1, method=133, property=181, struct=6
- access marked `*` is implicit (not written in source)

### `Source/Programs/UnsyncUI/UnsyncUI/App.xaml.cs` (UnsyncUI)


#### class `UnsyncUI.App`  
`public partial class App : Application`  
_public; L17-250_
- inherits: `Application`
- desc: Interaction logic for App.xaml
- L19-23 _public ctor_ `public App() : base()`
- L25 _public property_ `public new static App Current => ...`
- L27 _public property_ `public Config Config { get; set; }`
- L28 _public property_ `public string UnsyncPath { get; set; }`
- L29 _public property_ `public UserPreferences UserConfig { get; set; }`
- L30 _public property_ `public string DefaultSearchTerms { get; set; }`
- L32 _internal field_ `internal bool EnableExperimentalFeatures = false`
- L33 _internal field_ `internal bool EnableUserAuthentication = false`
- L34 _internal field_ `internal bool UnsyncSupportsStdout = false`
- L36 _internal field_ `internal Dictionary<string, string> Variables = ...`
- L36 _internal field_ `internal Dictionary< Variables = new Dictionary<string, string>()`
- L38 _internal property_ `internal string ApplicationLog { get; set; }`
- L40-51 _internal method_ `internal void ClearApplicationLog()`
- L53-56 _internal method_ `internal void LogError(string message)`
- L58-71 _internal method_ `internal void LogMessage(string message)`
- L73-76 _internal method_ `internal void LogDebug(string message)`
- L78-234 _protected method_ `protected override void OnStartup(StartupEventArgs e)`
- L236-243 _protected method_ `protected override void OnExit(ExitEventArgs e)`
- L245-249 _private* method_ `static void UnhandledException(object sender, string e)`

#### class `UnsyncUI.UserPreferences`  
`public sealed class UserPreferences`  
_public; L252-296_
- L255 _private field_ `private static readonly Guid version = Guid.Parse("1386020B-374C-43CE-8FBF-74AAE69EEFD3")`
- L256 _private field_ `private static readonly string userDir = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData), "UnsyncUI")`
- L257 _private field_ `private static readonly string userFile = Path.Combine(userDir, $"user_{version}.json")`
- L259 _public property_ `public string Proxy { get; set; }`
- L260 _public property_ `public Dictionary<string, string> ProjectDestinationMap { get; set; }`
- L261 _public property_ `public string CustomSrcPath { get; set; }`
- L262 _public property_ `public string CustomDstPath { get; set; }`
- L263 _public property_ `public string CustomInclude { get; set; }`
- L264 _public property_ `public string AdditionalArgs { get; set; }`
- L265 _public property_ `public bool AppendBuildName { get; set; }`
- L266 _public property_ `public bool LogInOnStartup { get; set; }`
- L268-283 _public method_ `public static UserPreferences Load()`
- L285-295 _public method_ `public void Save()`

### `Source/Programs/UnsyncUI/UnsyncUI/AssemblyInfo.cs` (UnsyncUI)
_(no declarations)_


### `Source/Programs/UnsyncUI/UnsyncUI/BuildSelectorControl.xaml.cs` (UnsyncUI)


#### class `UnsyncUI.BuildSelectorControl`  
`public partial class BuildSelectorControl : UserControl`  
_public; L23-82_
- inherits: `UserControl`
- desc: Interaction logic for BuildSelectorControl.xaml
- L25 _private* field_ `GridViewColumnHeader lastHeaderClicked = null`
- L26 _private* field_ `ListSortDirection lastDirection = ListSortDirection.Ascending`
- L28-31 _public ctor_ `public BuildSelectorControl()`
- L33-36 _private method_ `private void SyncHyperlink_Click(object sender, RoutedEventArgs e)`
- L38-70 _private method_ `private void BuildsHeader_Click(object sender, RoutedEventArgs e)`
- L72-81 _private method_ `private void Sort(params (string field, ListSortDirection direction)[] args)`

#### class `UnsyncUI.BuildPlatformModel`  
`public sealed class BuildPlatformModel`  
_public; L84-112_
- L87 _public property_ `public BuildModel Build { get; }`
- L88 _public property_ `public string Platform { get; }`
- L89 _public property_ `public string Flavor { get; }`
- L90 _public property_ `public string Description { get; }`
- L91 _public property_ `public string FullPath { get; }`
- L92 _public property_ `public string DestPathRelative { get; }`
- L93 _public property_ `public string Include { get; }`
- L95 _public property_ `public string Name => ...`
- L99 _public property_ `public string SafeName => ...`
- L101-111 _public ctor_ `public BuildPlatformModel(BuildModel build, string platform, string fullPath, string flavor, string include)`

#### class `UnsyncUI.BuildModel`  
`public sealed class BuildModel : BaseModel`  
_public; L114-227_
- inherits: `BaseModel`
- L116 _private field_ `private CancellationTokenSource cts`
- L117 _public property_ `public string Stream => ...`
- L118 _public property_ `public UInt64 CL => ...`
- L119 _public property_ `public string Suffix => ...`
- L121 _public property_ `public string Timestamp => ...`
- L123 _public property_ `public Config.Directory RootDir { get; }`
- L124 _public property_ `public string Path => ...`
- L126 _internal property_ `internal Config.BuildTemplate Template { get; }`
- L128 _public property_ `public Command OnRefreshPlatformsClicked { get; }`
- L129 _public property_ `public Command OnStopRefreshPlatformsClicked { get; }`
- L131 _public property_ `public ObservableCollection<BuildPlatformModel> Platforms { get; }`
- L133 _private field_ `private Config AppConfig`
- L135 _private field_ `private DirectoryEntry DirEntry`
- L137-149 _internal ctor_ `internal BuildModel(DirectoryEntry dirEntry, Config.Directory rootDir, Config.BuildTemplate template, Config config)`
- L151 _public method_ `public bool HasPlatform(string platform)`
- L153-201 _private method_ `private async Task EnumeratePlatforms(IDirectoryEnumerator dirEnum, Config.Directory currentDir, string path, Config.BuildTemplate template, CancellationTokenSource cancellationToken)`
- L203-226 _public method_ `public async void PopulatePlatforms()`

#### class `UnsyncUI.ProjectModel`  
`public sealed class ProjectModel : TabModel`  
_public; L229-585_
- inherits: `TabModel`
- L231 _private field_ `private bool firstRefresh = true`
- L232 _private field_ `private Action<IEnumerable<(SyncStartConfig Config, BuildPlatformModel Model)>> onBuildsSelected`
- L234 _private field_ `private string statusString = null`
- L235-242 _public property_ `public string StatusString { get; set; }`
- L244 _public property_ `public Config.Project Definition { get; }`
- L245 _public property_ `public string Name => ...`
- L247 _public property_ `public Command OnRefreshBuildsClicked { get; }`
- L248 _public property_ `public Command OnStopRefreshBuildsClicked { get; }`
- L249 _public property_ `public Command<IList> OnStartSync { get; }`
- L250 _public property_ `public Command CopyBuildCLClicked { get; }`
- L251 _public property_ `public Command CopyBuildNameClicked { get; }`
- L252 _public property_ `public Command OpenBuildLocationClicked { get; }`
- L253 _public property_ `public Command ResetDestinationClicked { get; }`
- L254 _public property_ `public Command OpenDestinationClicked { get; }`
- L256 _public property_ `public ObservableCollection<BuildModel> Builds { get; }`
- L257 _public property_ `public ICollectionView BuildsView { get; }`
- L259-274 _public method_ `public bool BuildsViewFilter(object item)`
- L276 _private field_ `private BuildModel selectedBuild = null`
- L277-291 _public property_ `public BuildModel SelectedBuild { get; set; }`
- L293 _private field_ `private string searchTerms = ""`
- L294-302 _public property_ `public string SearchTerms { get; set; }`
- L304 _private field_ `private CancellationTokenSource cts = null`
- L307 _private field_ `private string defaultDstPath = null` — Default download directory (either auto-detected or loaded from project config)
- L312 _private field_ `private string dstPath = null` — Current download path selected by user or loaded from user preferences. This value persists between application sessions (saved per project). It can be reset to default by pressing "Reset" button in the UI.
- L314-325 _public property_ `public string DstPath { get; set; }`
- L327-343 _private* method_ `void UpdateFinalDstPath()`
- L345 _private field_ `private string finalDstPath = null`
- L346-353 _public property_ `public string FinalDstPath { get; set; }`
- L355 _public property_ `public bool DryRun { get; set; }`
- L357 _private field_ `private bool appendBuildName = true`
- L358-369 _public property_ `public bool AppendBuildName { get; set; }`
- L371-430 _public ctor_ `public ProjectModel(Config.Project definition, Action<IEnumerable<(SyncStartConfig Config, BuildPlatformModel Model)>> onBuildsSelected)`
- L431 _private property_ `private bool CanResetDestinationToDefault => ...`
- L433-437 _private method_ `private void ResetDestinationToDefault()`
- L439-446 _private method_ `private void StopRefreshBuilds()`
- L448-493 _public method_ `public async void RefreshBuildsAsync()`
- L495-508 _public method_ `public void StartSync(IEnumerable<BuildPlatformModel> selectedBuilds)`
- L510-517 _public method_ `public override void OnSelected()`
- L519-544 _private method_ `private void CopyStringToClipboard(string str)`
- L546-552 _private method_ `private void CopyBuildCL()`
- L554-561 _private method_ `private void CopyBuildName()`
- L563-569 _private method_ `private void OpenBuildLocation()`
- L571-584 _private method_ `private void OpenDestinationLocation()`

### `Source/Programs/UnsyncUI/UnsyncUI/Config.cs` (UnsyncUI)


#### class `UnsyncUI.Config`  
`public sealed class Config`  
_public; L17-439_
- L218 _public property_ `public List<Proxy> Proxies { get; set; }`
- L219 _public property_ `public Proxy RootProxy { get; }`
- L220 _public property_ `public List<Project> Projects { get; set; }`
- L222 _public property_ `public string UnsyncPath { get; set; }`
- L224 _public property_ `public bool EnableExperimentalFeatures { get; set; }`
- L226 _public property_ `public bool EnableUserAuthentication { get; set; }`
- L228 _internal field_ `internal string loggedInUser`
- L230-248 _internal method_ `internal void ApplyVariables(XElement rootNode, Dictionary<string, string> Variables)`
- L250-338 _public ctor_ `public Config(string filename, string DefaultUnsyncPath = null, Dictionary<string, string> Variables = null)`
- L341-386 _private method_ `private (List<Proxy>, Proxy) DiscoverProxies(List<Proxy> SeedServers)`
- L388-394 _private method_ `private UnsyncQueryConfig CreateUnsyncQueryConfig()`
- L396-402 _private method_ `private bool CanUseUnsyncDirectoryEnumerator()`
- L404-414 _public method_ `public IDirectoryEnumerator CreateDirectoryEnumerator(Config.Project ProjectSchema)`
- L416-426 _public method_ `public IDirectoryEnumerator CreateDirectoryEnumerator(String Path, Config.Directory DirectorySchema)`
- L428-432 _public method_ `public BuildModel CreateBuildModel(string path, DateTime timestamp, Config.Directory rootDir)`
- L434-437 _public method_ `public BuildModel CreateBuildModel(string path, Config.Directory rootDir)`

#### class `UnsyncUI.Config.Proxy`  
`public sealed class Proxy`  
_public; L19-30_
- L21 _public property_ `public string Name { get; set; }`
- L22 _public property_ `public string Path { get; set; }`
- L23 _public property_ `public string Protocol { get; set; }`
- L25-28 _public method_ `public UnsyncServerConfig GetServerConfig()`

#### struct `UnsyncUI.Config.BuildTemplate`  
`internal struct BuildTemplate`  
_internal; L32-43_
- L34 _public field_ `public string Stream`
- L35 _public field_ `public UInt64? CL`
- L36 _public field_ `public string Suffix`
- L37 _public field_ `public string Platform`
- L38 _public field_ `public string Flavor`
- L39 _public field_ `public string Include`
- L41 _public property_ `public bool IsStreamClFound => ...`

#### class `UnsyncUI.Config.FileGroup`  
`public sealed class FileGroup`  
_public; L45-57_
- L47 _public property_ `public Regex Regex { get; }`
- L48 _public property_ `public string Include { get; }`
- L49 _public property_ `public string Flavor { get; }`
- L51-56 _public ctor_ `public FileGroup(XElement node)`

#### class `UnsyncUI.Config.Directory`  
`public sealed class Directory`  
_public; L59-155_
- L61 _public property_ `public Regex Regex { get; }`
- L62 _public property_ `public string Stream { get; }`
- L63 _public property_ `public string Suffix { get; }`
- L64 _public property_ `public string CL { get; }`
- L65 _public property_ `public string Platform { get; }`
- L66 _public property_ `public string Flavor { get; }`
- L67 _public property_ `public List<Directory> SubDirectories { get; }`
- L68 _public property_ `public List<FileGroup> FileGroups { get; }`
- L70-80 _public ctor_ `public Directory(XElement node)`
- L82-119 _internal method_ `internal bool Parse(string path, ref BuildTemplate template)`
- L121-154 _internal method_ `internal void ParseFileGroups(List<String> filePaths, BuildTemplate template, out List<BuildTemplate> groupTemplates)`

#### class `UnsyncUI.Config.Project`  
`public sealed class Project`  
_public; L157-216_
- L159 _internal field_ `internal Config AppConfig`
- L161 _public property_ `public string Name { get; set; }`
- L162 _public property_ `public string Root { get; set; }`
- L163 _public property_ `public string Destination { get; set; }`
- L164 _public property_ `public List<string> Exclusions { get; set; }`
- L165 _public property_ `public List<Directory> Children { get; set; }`
- L167-189 _private method_ `private Task EnumerateBuilds(IDirectoryEnumerator dirEnum, ITargetBlock<BuildModel> pipe, Directory d, DirectoryEntry dirEntry, BuildTemplate template, CancellationToken cancelToken)`
- L191-215 _public method_ `public (Task, ISourceBlock<BuildModel>) EnumerateBuilds(CancellationToken cancelToken)`

### `Source/Programs/UnsyncUI/UnsyncUI/Converters.cs` (UnsyncUI)


#### class `UnsyncUI.BaseConverter`  
`public abstract class BaseConverter`  
_public; L13-31_
- L15-30 _protected method_ `protected static bool AsBool(object value)`

#### class `UnsyncUI.VisibilityConverter`  
`public sealed class VisibilityConverter : IValueConverter`  
_public; L32-69_
- inherits: `IValueConverter`
- L34 _public property_ `public Visibility TrueState { get; set; }`
- L35 _public property_ `public Visibility FalseState { get; set; }`
- L37-65 _public method_ `public object Convert(object value, Type targetType, object parameter, CultureInfo culture)`
- L67 _public method_ `public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)`

#### class `UnsyncUI.NotConverter`  
`public sealed class NotConverter : BaseConverter, IValueConverter`  
_public; L71-78_
- inherits: `BaseConverter, IValueConverter`
- L73 _public method_ `public object Convert(object value, Type targetType, object parameter, CultureInfo culture)`
- L76 _public method_ `public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)`

#### class `UnsyncUI.AllConverter`  
`public sealed class AllConverter : BaseConverter, IMultiValueConverter`  
_public; L80-90_
- inherits: `BaseConverter, IMultiValueConverter`
- L82 _public property_ `public object TrueValue { get; set; }`
- L83 _public property_ `public object FalseValue { get; set; }`
- L85 _public method_ `public object Convert(object[] values, Type targetType, object parameter, CultureInfo culture)`
- L88 _public method_ `public object[] ConvertBack(object value, Type[] targetTypes, object parameter, CultureInfo culture)`

#### class `UnsyncUI.ObjectConverter`  
`public sealed class ObjectConverter : BaseConverter, IValueConverter`  
_public; L92-102_
- inherits: `BaseConverter, IValueConverter`
- L94 _public property_ `public object TrueValue { get; set; }`
- L95 _public property_ `public object FalseValue { get; set; }`
- L97 _public method_ `public object Convert(object value, Type targetType, object parameter, CultureInfo culture)`
- L100 _public method_ `public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)`

#### class `UnsyncUI.ConsoleColorConverter`  
`public sealed class ConsoleColorConverter : IValueConverter`  
_public; L104-136_
- inherits: `IValueConverter`
- L106 _private field_ `private Dictionary<ConsoleColor, SolidColorBrush> brushes = ...`
- L106 _private field_ `private Dictionary< brushes = new Dictionary<ConsoleColor, SolidColorBrush>() { [ConsoleColor.Black] = new SolidColorBrush(Color.FromRgb(0, 0, 0)), [ConsoleColor.DarkBlue] = new SolidColorBrush(Color.FromRgb(0, 0, 128)), [ConsoleC ...`
- L126-132 _public method_ `public object Convert(object value, Type targetType, object parameter, CultureInfo culture)`
- L134 _public method_ `public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)`

#### class `UnsyncUI.ObjectToBoolConverter`  
`public class ObjectToBoolConverter : IValueConverter`  
_public; L138-154_
- inherits: `IValueConverter`
- L140-148 _public method_ `public object Convert(object value, Type targetType, object parameter, CultureInfo culture)`
- L150-153 _public method_ `public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)`

### `Source/Programs/UnsyncUI/UnsyncUI/JobControl.xaml.cs` (UnsyncUI)


#### class `UnsyncUI.JobControl`  
`public partial class JobControl : UserControl`  
_public; L26-178_
- inherits: `UserControl`
- desc: Interaction logic for ActiveJobControl.xaml
- L28 _private field_ `private static readonly ConsoleColorConverter _colorConverter = new ConsoleColorConverter()`
- L30 _private field_ `private ScrollViewer _scrollViewer`
- L31 _private field_ `private bool _autoScroll = true`
- L32 _private field_ `private bool _isProgrammaticScroll = false`
- L34 _private field_ `private FlowDocument _logDocument`
- L35 _private field_ `private LogModel _currentLogModel`
- L36 _private field_ `private Run _currentRun`
- L38-45 _public ctor_ `public JobControl()`
- L47-55 _private method_ `private void OnLogRichTextBoxLoaded(object sender, RoutedEventArgs e)`
- L57-69 _private method_ `private static ScrollViewer FindScrollViewer(DependencyObject obj)`
- L71 _private method_ `private static Brush GetBrush(ConsoleColor color)`
- L74-97 _private method_ `private void OnDataContextChanged(object sender, DependencyPropertyChangedEventArgs e)`
- L99-112 _private method_ `private void AppendLogLine(LogModel model)`
- L114-124 _private method_ `private void OnCurrentLogModelChanged(object sender, PropertyChangedEventArgs e)`
- L126-140 _private method_ `private void OnLogLinesChanged(object sender, NotifyCollectionChangedEventArgs e)`
- L142-153 _private method_ `private void OnScrollChanged(object sender, ScrollChangedEventArgs e)`
- L155-161 _private method_ `private bool IsAtBottom()`
- L163-168 _private method_ `private void UpdateFollowLink()`
- L170-177 _private method_ `private void FollowLink_Click(object sender, RoutedEventArgs e)`

#### class `UnsyncUI.LogModel`  
`public sealed class LogModel : BaseModel`  
_public; L180-195_
- inherits: `BaseModel`
- L182 _private field_ `private string text = null`
- L183-187 _public property_ `public string Text { get; set; }`
- L189 _private field_ `private ConsoleColor color = ConsoleColor.Black`
- L190-194 _public property_ `public ConsoleColor Color { get; set; }`

#### class `UnsyncUI.FileModel`  
`public sealed class FileModel : BaseModel`  
_public; L197-212_
- inherits: `BaseModel`
- L199 _private field_ `private string name = null`
- L200-204 _public property_ `public string Name { get; set; }`
- L206 _private field_ `private string status = null`
- L207-211 _public property_ `public string Status { get; set; }`

#### class `UnsyncUI.JobModel`  
`public sealed class JobModel : BaseModel`  
_public; L214-651_
- inherits: `BaseModel`
- L216 _public property_ `public BuildPlatformModel Build { get; }`
- L217 _public property_ `public string DstPath { get; }`
- L218 _public property_ `public string ScavengePath { get; }`
- L219 _public property_ `public string DstPathBase => ...`
- L220 _public property_ `public bool DryRun { get; }`
- L221 _public property_ `public UnsyncServerConfig Server { get; }`
- L222 _public property_ `public string AdditionalArgs { get; }`
- L223 _public property_ `public string[] IncludeFilter { get; }`
- L224 _public property_ `public string[] Exclusions { get; }`
- L226 _public property_ `public string ProxyStr => ...`
- L228 _public property_ `public string Name => ...`
- L230 _private field_ `private double totalProgress = 0`
- L231-235 _public property_ `public double TotalProgress { get; set; }`
- L237 _private field_ `private bool isIndeterminate = true`
- L238-242 _public property_ `public bool IsIndeterminate { get; set; }`
- L244 _private field_ `private bool showProgressBar = false`
- L245-249 _public property_ `public bool ShowProgressBar { get; set; }`
- L251 _private field_ `private bool showCancelHyperlink = true`
- L252-256 _public property_ `public bool ShowCancelHyperlink { get; set; }`
- L258 _private field_ `private bool showClearHyperlink = false`
- L259-263 _public property_ `public bool ShowClearHyperlink { get; set; }`
- L265 _private field_ `private string statusMessage = null`
- L266-270 _public property_ `public string StatusMessage { get; set; }`
- L272 _private field_ `private ConsoleColor statusColor = ConsoleColor.Black`
- L273-277 _public property_ `public ConsoleColor StatusColor { get; set; }`
- L279 _private field_ `private string progressMessage = null`
- L280-284 _public property_ `public string ProgressMessage { get; set; }`
- L287 _private field_ `private bool detailsExpanded = false`
- L288-292 _public property_ `public bool DetailsExpanded { get; set; }`
- L294 _public property_ `public Command OnCancelClicked { get; }`
- L295 _public property_ `public Command OnClearClicked { get; }`
- L296 _public property_ `public Command OnSourcePathClicked { get; }`
- L297 _public property_ `public Command OnDestPathClicked { get; }`
- L298 _public property_ `public Command CopyLogClicked { get; }`
- L299 _public property_ `public Command SaveLogClicked { get; }`
- L301 _private field_ `private TaskCompletionSource<bool> startTcs = new TaskCompletionSource<bool>()`
- L302 _private field_ `private CancellationTokenSource cts = new CancellationTokenSource()`
- L303 _public property_ `public bool IsCancelled => ...`
- L304 _public property_ `public bool Succeeded { get; set; }`
- L306 _private field_ `private double maxLogScrollViewHeight = Double.PositiveInfinity`
- L307-311 _public property_ `public double MaxLogScrollViewHeight { get; set; }`
- L313 _private field_ `private Action<JobModel> onCompletion`
- L314 _private field_ `private Action<JobModel> onProgress`
- L316 _public property_ `public ObservableCollection<LogModel> LogLines { get; }`
- L317 _public property_ `public ObservableCollection<FileModel> Files { get; }`
- L318 _private field_ `private Dictionary<string, FileModel> filesMap = ...`
- L318 _private field_ `private Dictionary< filesMap = new Dictionary<string, FileModel>()`
- L320-358 _public ctor_ `public JobModel( BuildPlatformModel build, string dstPath, string scavengePath, bool dryRun, UnsyncServerConfig server, string additionalArgs, string[] exclusions, Action<JobModel> onCompletion, Action<JobModel> onClear, Action<JobModel> onProgress)`
- L360-368 _private method_ `private string GetLogText()`
- L370-377 _private method_ `private void CopyLog()`
- L379-399 _private method_ `private void SaveLog()`
- L401 _public method_ `public void StartJob()`
- L403-411 _public method_ `public void CancelJob()`
- L413-419 _public method_ `public bool IsDuplicate(JobModel otherJob)`
- L421-650 _private method_ `private async void RunAsync()`

### `Source/Programs/UnsyncUI/UnsyncUI/MainWindow.xaml.cs` (UnsyncUI)


#### class `UnsyncUI.MainWindow`  
`public partial class MainWindow : Window`  
_public; L18-51_
- inherits: `Window`
- desc: Interaction logic for MainWindow.xaml
- L20-31 _public ctor_ `public MainWindow()`
- L33-50 _private method_ `private void Window_Closing(object sender, CancelEventArgs e)`

#### class `UnsyncUI.AutoScrollTextBox`  
`public class AutoScrollTextBox : TextBox`  
_public; L53-60_
- inherits: `TextBox`
- L55-59 _protected method_ `protected override void OnTextChanged(TextChangedEventArgs e)`

#### class `UnsyncUI.MainTabTemplateSelector`  
`public sealed class MainTabTemplateSelector : DataTemplateSelector`  
_public; L62-71_
- inherits: `DataTemplateSelector`
- L64 _public property_ `public DataTemplate ProjectTemplate { get; set; }`
- L65 _public property_ `public DataTemplate CustomTemplate { get; set; }`
- L67 _public method_ `public override DataTemplate SelectTemplate(object item, DependencyObject container)`

#### class `UnsyncUI.AnnouncementItem`  
`public sealed class AnnouncementItem : BaseModel`  
_public; L73-88_
- inherits: `BaseModel`
- L75 _public property_ `public string Message { get; }`
- L76 _public property_ `public ConsoleColor Color { get; }`
- L78-87 _public ctor_ `public AnnouncementItem(string message, string level)`

#### class `UnsyncUI.AnnouncementBannerModel`  
`public sealed class AnnouncementBannerModel : BaseModel`  
_public; L90-127_
- inherits: `BaseModel`
- L92 _private field_ `private HashSet<string> seenIds = new HashSet<string>()`
- L94 _public property_ `public ObservableCollection<AnnouncementItem> Announcements { get; }`
- L96 _private field_ `private bool isVisible = false`
- L97-101 _public property_ `public bool IsVisible { get; set; }`
- L103 _public property_ `public Command OnDismissClicked { get; }`
- L105-108 _public ctor_ `public AnnouncementBannerModel()`
- L110-126 _public method_ `public void AddAnnouncements(IEnumerable<HelloAnnouncement> announcements)`

#### class `UnsyncUI.TabModel`  
`public abstract class TabModel : BaseModel`  
_public; L129-132_
- inherits: `BaseModel`
- L131 _public method_ `public virtual void OnSelected()`

#### class `UnsyncUI.CustomModel`  
`public sealed class CustomModel : TabModel`  
_public; L134-201_
- inherits: `TabModel`
- L136 _private field_ `private Action<IEnumerable<(SyncStartConfig Config, BuildPlatformModel Model)>> onBuildsSelected`
- L138 _public property_ `public string Name => ...`
- L140 _private field_ `private string srcPath = App.Current.UserConfig.CustomSrcPath`
- L141-151 _public property_ `public string SrcPath { get; set; }`
- L153 _public property_ `public bool DryRun { get; set; }`
- L155 _private field_ `private string dstPath = App.Current.UserConfig.CustomDstPath`
- L156-166 _public property_ `public string DstPath { get; set; }`
- L168 _private field_ `private string include = App.Current.UserConfig.CustomInclude`
- L169-177 _public property_ `public string Include { get; set; }`
- L179 _public property_ `public Command OnSyncClicked { get; }`
- L181 _private method_ `private void UpdateSyncCommand()`
- L184-200 _public ctor_ `public CustomModel(Action<IEnumerable<(SyncStartConfig Config, BuildPlatformModel Model)>> onBuildsSelected)`

#### class `UnsyncUI.SyncStartConfig`  
`public class SyncStartConfig`  
_public; L203-209_
- L205 _public field_ `public bool DryRun`
- L206 _public field_ `public string DstPath`
- L207 _public field_ `public string ScavengePath`
- L208 _public field_ `public string[] Exclusions`

#### class `UnsyncUI.MainWindowModel`  
`public sealed class MainWindowModel : BaseModel`  
_public; L211-564_
- inherits: `BaseModel`
- L213 _public property_ `public AnnouncementBannerModel AnnouncementBanner { get; }`
- L215 _private field_ `private Config.Proxy selectedProxy = App.Current.Config?.Proxies?.Where(p => p.Name.Equals(App.Current.UserConfig.Proxy, StringComparison.InvariantCultureIgnoreCase))?.FirstOrDefault() ?? App.Current.Config?.Proxies?.Where(p => p.Path != ...`
- L219-227 _public property_ `public Config.Proxy SelectedProxy { get; set; }`
- L229 _private field_ `private bool logExpanded = true`
- L230-234 _public property_ `public bool LogExpanded { get; set; }`
- L236-239 _public property_ `public string ApplicationLog { get; }`
- L241-244 _public method_ `public void OnLogUpdated()`
- L246 _private field_ `private bool showHelp = true`
- L247-251 _public property_ `public bool ShowHelp { get; set; }`
- L253 _private field_ `private string additionalArgs = App.Current.UserConfig.AdditionalArgs`
- L254-262 _public property_ `public string AdditionalArgs { get; set; }`
- L264 _public property_ `public bool ShouldShowLoginInfo { get; }`
- L266-274 _public property_ `public string LoggedInUser { get; set; }`
- L276 _public property_ `public Command OnLogInClicked { get; }`
- L277 _public property_ `public Command OnLogOutClicked { get; }`
- L279-299 _private method_ `private void LogIn()`
- L301-304 _private method_ `private void LogOut()`
- L307 _private field_ `private TaskbarItemProgressState progressState = TaskbarItemProgressState.None`
- L308-312 _public property_ `public TaskbarItemProgressState ProgressState { get; set; }`
- L314 _private field_ `private float progressValue = 0.0f`
- L315-319 _public property_ `public float ProgressValue { get; set; }`
- L321 _private field_ `private int batchJobCount = 0`
- L323 _public property_ `public Config Config => ...`
- L325 _public property_ `public Command OnClearQueueClicked { get; }`
- L326 _public property_ `public Command OnClearCompletedClicked { get; }`
- L328 _public property_ `public Command OnClearApplicationLogClicked { get; }`
- L330 _public property_ `public ObservableCollection<TabModel> Tabs { get; }`
- L331 _public property_ `public ObservableCollection<JobModel> QueuedJobs { get; }`
- L333 _private field_ `private JobModel activeJob = null`
- L334-338 _public property_ `public JobModel ActiveJob { get; set; }`
- L340 _public property_ `public ObservableCollection<JobModel> CompletedJobs { get; }`
- L342 _private field_ `private TabModel selectedTab = null`
- L343-351 _public property_ `public TabModel SelectedTab { get; set; }`
- L353-380 _public ctor_ `public MainWindowModel()`
- L382-409 _private method_ `private void FetchAnnouncements()`
- L411-415 _private method_ `private void ClearQueue()`
- L417-421 _private method_ `private void ClearCompleted()`
- L423-426 _private method_ `private void ClearApplicationLog()`
- L428-445 _public method_ `public void OnBuildsSelected(IEnumerable<(SyncStartConfig Config, BuildPlatformModel Model)> selectedBuilds)`
- L447-471 _private method_ `private void AddJob(JobModel job)`
- L473-476 _private method_ `private void OnJobProgress(JobModel job)`
- L478-515 _private method_ `private void OnJobCompleted(JobModel job)`
- L517-521 _private method_ `private void OnClearJob(JobModel job)`
- L523-545 _private method_ `private void UpdateProgressState()`
- L546-563 _private method_ `private void UpdateProgressValue()`

### `Source/Programs/UnsyncUI/UnsyncUI/Query.cs` (UnsyncUI)


#### class `UnsyncUI.UnsyncServerConfig`  
`public class UnsyncServerConfig`  
_public; L16-37_
- L18 _public field_ `public String address`
- L19 _public field_ `public String protocol`
- L21-36 _public method_ `public String GetCommandLineArgs()`

#### class `UnsyncUI.UnsyncQueryConfig`  
`public class UnsyncQueryConfig`  
_public; L39-43_
- L41 _public field_ `public String unsyncPath`
- L42 _public field_ `public UnsyncServerConfig server`

#### class `UnsyncUI.SearchQueryResultEntry`  
`class SearchQueryResultEntry`  
_internal*; L45-52_
- L47 _public property_ `public String path { get; set; }`
- L49 _public property_ `public bool is_directory { get; set; }`
- L50 _public property_ `public UInt64 size { get; set; }`
- L51 _public property_ `public UInt64 mtime { get; set; }`

#### class `UnsyncUI.SearchQueryResult`  
`class SearchQueryResult`  
_internal*; L54-58_
- L56 _public property_ `public String root { get; set; }`
- L57 _public property_ `public List<SearchQueryResultEntry> entries { get; set; }`

#### class `UnsyncUI.HelloAnnouncement`  
`public class HelloAnnouncement`  
_public; L60-65_
- L62 _public property_ `public string id { get; set; }`
- L63 _public property_ `public string level { get; set; }`
- L64 _public property_ `public string message { get; set; }`

#### class `UnsyncUI.HelloResponse`  
`class HelloResponse`  
_internal*; L67-70_
- L69 _public property_ `public List<HelloAnnouncement> announcements { get; set; }`

#### class `UnsyncUI.LoginQueryResult`  
`public class LoginQueryResult`  
_public; L73-83_
- L76 _public property_ `public List<String> aud { get; set; }` — attrs: `[JsonConverter(typeof(SingleOrArrayConverter))]`
- L77 _public property_ `public String sub { get; set; }`
- L78 _public property_ `public String iss { get; set; }`
- L79 _public property_ `public List<String> scp { get; set; }`
- L80 _public property_ `public UInt64 iat { get; set; }`
- L81 _public property_ `public UInt64 exp { get; set; }`
- L82 _public property_ `public List<String> groups { get; set; }`

#### class `UnsyncUI.UnsyncMirrorDesc`  
`public class UnsyncMirrorDesc`  
_public; L85-93_
- L87 _public property_ `public String name { get; set; }`
- L88 _public property_ `public String description { get; set; }`
- L89 _public property_ `public String address { get; set; }`
- L90 _public property_ `public uint port { get; set; }`
- L91 _public property_ `public uint ping { get; set; }`
- L92 _public property_ `public bool ok { get; set; }`

#### class `UnsyncUI.UnsyncQueryUtil`  
`public class UnsyncQueryUtil`  
_public; L95-180_
- L97 _private* field_ `UnsyncQueryConfig Config`
- L98-101 _public ctor_ `public UnsyncQueryUtil(UnsyncQueryConfig InConfig)`
- L103-106 _public ctor_ `public UnsyncQueryUtil(string unsyncPath, string serverAddress, string serverProtocol) : this(unsyncPath, new UnsyncServerConfig { address = serverAddress, protocol = serverProtocol } )`
- L108-113 _public ctor_ `public UnsyncQueryUtil(string unsyncPath, UnsyncServerConfig server)`
- L115-147 _private method_ `private string RunCommand(string argsStr)`
- L149-153 _public method_ `public List<UnsyncMirrorDesc> Mirrors()`
- L155-159 _public method_ `public LoginQueryResult Login()`
- L161-179 _public method_ `public List<HelloAnnouncement> Hello()`

#### class `UnsyncUI.UnsyncDirectoryEnumerator`  
`public class UnsyncDirectoryEnumerator : IDirectoryEnumerator`  
_public; L184-475_
- inherits: `IDirectoryEnumerator`
- L186 _private field_ `private UnsyncQueryConfig Config`
- L188 _private field_ `private Config.Project ProjectSchema`
- L190 _private field_ `private String DirectoryRoot`
- L191 _private field_ `private Config.Directory DirectorySchema`
- L193 _private field_ `private bool Initialized = false`
- L204 _private* field_ `List<Entry> Entries`
- L206-210 _public ctor_ `public UnsyncDirectoryEnumerator(Config.Project ProjectSchema, UnsyncQueryConfig Config)`
- L211-216 _public ctor_ `public UnsyncDirectoryEnumerator(String Path, Config.Directory DirectorySchema, UnsyncQueryConfig Config)`
- L218-231 _public method_ `public string FormatArtifactPath(string virtualPath)`
- L233-252 _private method_ `private async Task LazyInit(CancellationToken cancellationToken)`
- L259-271 _private method_ `private void ProcessQueryResult(SearchQueryResult queryResult)`
- L273-300 _private method_ `private async Task RunQueries(List<String> queryStrings, CancellationToken cancellationToken)`
- L302-317 _private method_ `private async Task InitProject(CancellationToken cancellationToken)`
- L319-359 _private method_ `private void GenerateQueries(ref BuildTraversalState traversalState, Config.Directory dir, String query, ref List<String> output)`
- L361-376 _private method_ `private async Task InitDirectory(CancellationToken cancellationToken)`
- L378-389 _private method_ `private int GetDirectoryDepth(string path)`
- L412-459 _private method_ `private Task<IEnumerable<DirectoryEntry>> EnumerateEntries(string path, CancellationToken token, EntryFilter filter)`
- L461-467 _public method_ `public Task<IEnumerable<DirectoryEntry>> EnumerateDirectories(string path, CancellationToken token)`
- L468-474 _public method_ `public Task<IEnumerable<DirectoryEntry>> EnumerateFiles(string path, CancellationToken token)`

#### class `UnsyncUI.UnsyncDirectoryEnumerator.Entry`  
`private class Entry`  
_private; L195-202_
- L197 _public field_ `public String FullPath`
- L198 _public field_ `public int Depth`
- L199 _public field_ `public UInt64 Size`
- L200 _public field_ `public UInt64 MTime`
- L201 _public field_ `public bool IsDirectory`

#### class `UnsyncUI.UnsyncDirectoryEnumerator.BuildTraversalState`  
`class BuildTraversalState`  
_private*; L253-257_
- L255 _public field_ `public bool FoundCL = false`
- L256 _public field_ `public bool FoundStream = false`

#### struct `UnsyncUI.UnsyncDirectoryEnumerator.EntryFilter`  
`private struct EntryFilter`  
_private; L391-410_
- L393 _public field_ `public bool IncludeFiles`
- L394 _public field_ `public bool IncludeDirectories`
- L396-409 _public method_ `public bool ShouldInclude(Entry entry)`

#### class `UnsyncUI.SingleOrArrayConverter`  
`public class SingleOrArrayConverter : JsonConverter<List<String>>`  
_public; L477-500_
- inherits: `JsonConverter<List<String>>`
- L479-487 _public method_ `public override List<String> Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)`
- L489-499 _public method_ `public override void Write(Utf8JsonWriter writer, List<String> value, JsonSerializerOptions options)`

### `Source/Programs/UnsyncUI/UnsyncUI/SelectFolderControl.xaml.cs` (UnsyncUI)


#### class `UnsyncUI.SelectFolderControl`  
`public partial class SelectFolderControl : UserControl`  
_public; L12-42_
- inherits: `UserControl`
- desc: Interaction logic for SelectFolderControl.xaml
- L14 _public field_ `public static readonly DependencyProperty DescriptionProperty = DependencyProperty.Register(nameof(Description), typeof(string), typeof(SelectFolderControl))`
- L15 _public field_ `public static readonly DependencyProperty SelectedPathProperty = DependencyProperty.Register(nameof(SelectedPath), typeof(string), typeof(SelectFolderControl), new FrameworkPropertyMetadata() { BindsTwoWayByDefault = true, DefaultUpdateSourceTrigger = UpdateSourceT ...`
- L21-25 _public property_ `public string Description { get; set; }`
- L27-31 _public property_ `public string SelectedPath { get; set; }`
- L33-36 _public ctor_ `public SelectFolderControl()`
- L38-41 _public method_ `public void OnBrowseClicked(object sender, RoutedEventArgs e)`

### `Source/Programs/UnsyncUI/UnsyncUI/Shell.cs` (UnsyncUI)


#### class `UnsyncUI.Shell`  
`public static class Shell`  
_public; L10-53_
- L12-15 _public method_ `public static void LaunchExplorer(string path)`
- L17-35 _public method_ `public static string SelectFolder(string root, string desc)`
- L37-52 _public method_ `public static string SelectSaveFile(string title, string filter, string defaultExt, string defaultFilename)`

### `Source/Programs/UnsyncUI/UnsyncUI/Utils.cs` (UnsyncUI)


#### class `UnsyncUI.BaseModel`  
`public abstract class BaseModel : INotifyPropertyChanged`  
_public; L19-34_
- inherits: `INotifyPropertyChanged`
- L21 _public event_ `public event PropertyChangedEventHandler PropertyChanged`
- L23 _protected method_ `protected void OnPropertyChanged(string name)`
- L26-33 _protected method_ `protected void SetProperty<T>(ref T property, T newValue, [CallerMemberName] string name = null)`

#### class `UnsyncUI.Command`  
`public class Command<T> : BaseModel, ICommand`  
_public; L36-63_
- inherits: `BaseModel, ICommand`
- L38 _public event_ `public event EventHandler CanExecuteChanged`
- L39 _private field_ `private Action<T> action`
- L40 _private field_ `private bool enabled = false`
- L42-54 _public property_ `public bool Enabled { get; set; }`
- L56-59 _public ctor_ `public Command(Action<T> action)`
- L61 _public method_ `public bool CanExecute(object parameter)`
- L62 _public method_ `public void Execute(object parameter)`

#### class `UnsyncUI.Command`  
`public sealed class Command : Command<object>`  
_public; L65-70_
- inherits: `Command<object>`
- L67-69 _public ctor_ `public Command(Action action) : base(o => action())`

#### struct `UnsyncUI.DirectoryEntry`  
`public struct DirectoryEntry`  
_public; L72-81_
- L74 _public field_ `public string Path`
- L75 _public field_ `public DateTime MTime`
- L77-80 _public method_ `public static IEnumerable<string> ToPaths(IEnumerable<DirectoryEntry> dirEntries)`

#### interface `UnsyncUI.IDirectoryEnumerator`  
`public interface IDirectoryEnumerator`  
_public; L83-88_
- L85 _public method_ `public Task<IEnumerable<DirectoryEntry>> EnumerateDirectories(string path, CancellationToken token)`
- L86 _public method_ `public Task<IEnumerable<DirectoryEntry>> EnumerateFiles(string path, CancellationToken token)`
- L87 _public method_ `public string FormatArtifactPath(string virtualPath)`

#### class `UnsyncUI.NativeDirectoryEnumerator`  
`public class NativeDirectoryEnumerator : IDirectoryEnumerator`  
_public; L91-101_
- inherits: `IDirectoryEnumerator`
- L93-96 _public method_ `public Task<IEnumerable<DirectoryEntry>> EnumerateDirectories(string path, CancellationToken token)`
- L97-100 _public method_ `public Task<IEnumerable<DirectoryEntry>> EnumerateFiles(string path, CancellationToken token)`

#### class `UnsyncUI.AsyncIO`  
`static class AsyncIO`  
_internal*; L103-192_
- L105 _private field_ `private static SemaphoreSlim mutex = new SemaphoreSlim(4)`
- L107-145 _public method_ `public static Task<IEnumerable<DirectoryEntry>> EnumerateDirectoriesAsync(string path, CancellationToken token)`
- L146-191 _public method_ `public static Task<IEnumerable<DirectoryEntry>> EnumerateFilesAsync(string path, CancellationToken token)`

#### class `UnsyncUI.AsyncProcess`  
`public sealed class AsyncProcess`  
_public; L194-403_
- L293 _private field_ `private Process proc = new Process()`
- L294 _public property_ `public int? ExitCode { get; set; }`
- L296-306 _public ctor_ `public AsyncProcess(string path, string args)`
- L314-323 _public method_ `public async IAsyncEnumerable<string> RunAsync([EnumeratorCancellation] CancellationToken cancelToken, bool ReadStdErr = true)`
- L325-391 _public method_ `public async IAsyncEnumerable<(string, StreamKind)> RunAsyncStreams([EnumeratorCancellation] CancellationToken cancelToken)`
- L393-402 _public method_ `public async Task<string> RunAndGetOutput(bool ReadStdErr = true)`

#### class `UnsyncUI.AsyncProcess.ProcessTracker`  
`public static class ProcessTracker`  
_public; L196-291_
- L246 _private method_ `private extern static IntPtr CreateJobObject(IntPtr lpJobAttributes, string name)` — attrs: `[DllImport("kernel32.dll", CharSet = CharSet.Unicode)]`
- L249 _private method_ `private extern static bool SetInformationJobObject(IntPtr job, JobObjectInfoType infoType, IntPtr lpJobObjectInfo, uint cbJobObjectInfoLength)` — attrs: `[DllImport("kernel32.dll")]`
- L252 _private method_ `private extern static bool AssignProcessToJobObject(IntPtr job, IntPtr process)` — attrs: `[DllImport("kernel32.dll", SetLastError = true)]`
- L254 _private field_ `private static readonly IntPtr hJob = CreateJobObject(IntPtr.Zero, $"ProcessTracker_{Process.GetCurrentProcess().Id}")`
- L256-284 _private* ctor_ `static ProcessTracker()`
- L286-290 _public method_ `public static void Attach(Process proc)`

#### enum `UnsyncUI.AsyncProcess.ProcessTracker.JOBOBJECTLIMIT`  
`public enum JOBOBJECTLIMIT : uint`  
_public; L199-202_
- attrs: `[Flags]`
- inherits: `uint`
- L201 _public* enumerator_ `JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE = 0x2000`

#### struct `UnsyncUI.AsyncProcess.ProcessTracker.JOBOBJECT_BASIC_LIMIT_INFORMATION`  
`public struct JOBOBJECT_BASIC_LIMIT_INFORMATION`  
_public; L205-216_
- attrs: `[StructLayout(LayoutKind.Sequential)]`
- L207 _public field_ `public long PerProcessUserTimeLimit`
- L208 _public field_ `public long PerJobUserTimeLimit`
- L209 _public field_ `public JOBOBJECTLIMIT LimitFlags`
- L210 _public field_ `public UIntPtr MinimumWorkingSetSize`
- L211 _public field_ `public UIntPtr MaximumWorkingSetSize`
- L212 _public field_ `public uint ActiveProcessLimit`
- L213 _public field_ `public long Affinity`
- L214 _public field_ `public uint PriorityClass`
- L215 _public field_ `public uint SchedulingClass`

#### struct `UnsyncUI.AsyncProcess.ProcessTracker.IO_COUNTERS`  
`public struct IO_COUNTERS`  
_public; L219-227_
- attrs: `[StructLayout(LayoutKind.Sequential)]`
- L221 _public field_ `public ulong ReadOperationCount`
- L222 _public field_ `public ulong WriteOperationCount`
- L223 _public field_ `public ulong OtherOperationCount`
- L224 _public field_ `public ulong ReadTransferCount`
- L225 _public field_ `public ulong WriteTransferCount`
- L226 _public field_ `public ulong OtherTransferCount`

#### struct `UnsyncUI.AsyncProcess.ProcessTracker.JOBOBJECT_EXTENDED_LIMIT_INFORMATION`  
`public struct JOBOBJECT_EXTENDED_LIMIT_INFORMATION`  
_public; L230-238_
- attrs: `[StructLayout(LayoutKind.Sequential)]`
- L232 _public field_ `public JOBOBJECT_BASIC_LIMIT_INFORMATION BasicLimitInformation`
- L233 _public field_ `public IO_COUNTERS IoInfo`
- L234 _public field_ `public UIntPtr ProcessMemoryLimit`
- L235 _public field_ `public UIntPtr JobMemoryLimit`
- L236 _public field_ `public UIntPtr PeakProcessMemoryUsed`
- L237 _public field_ `public UIntPtr PeakJobMemoryUsed`

#### enum `UnsyncUI.AsyncProcess.ProcessTracker.JobObjectInfoType`  
`public enum JobObjectInfoType`  
_public; L240-243_
- L242 _public* enumerator_ `ExtendedLimitInformation = 9`

#### enum `UnsyncUI.AsyncProcess.StreamKind`  
`public enum StreamKind`  
_public; L308-312_
- L310 _public* enumerator_ `StdOut`
- L311 _public* enumerator_ `StdErr`
