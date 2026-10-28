# CSharp / UnrealToolboxExampleApplication

- project root: `Source/Programs/UnrealToolboxExampleApplication`
- files: 11; symbols: 71
- symbol kinds: class=12, const=4, ctor=9, field=18, method=28
- access marked `*` is implicit (not written in source)

### `Source/Programs/UnrealToolboxExampleApplication/App.axaml.cs` (UnrealToolboxExampleApplication)


#### class `UnrealToolboxExampleApplication.App`  
`public partial class App : Application`  
_public; L11-148_
- inherits: `Application`
- L13-16 _public method_ `public override void Initialize()`
- L18-27 _public method_ `public override void OnFrameworkInitializationCompleted()`
- L29-43 _private* method_ `void StartUpdateListener(IClassicDesktopStyleApplicationLifetime desktop)`
- L45-79 _private* method_ `void ListenViaNamedEvent(IClassicDesktopStyleApplicationLifetime desktop)`
- L81-134 _private* method_ `void ListenViaMarkerFile(IClassicDesktopStyleApplicationLifetime desktop)`
- L136-147 _private* method_ `static async Task<bool> ShowUpdateDialog(IClassicDesktopStyleApplicationLifetime desktop)`

### `Source/Programs/UnrealToolboxExampleApplication/CodeSamples.cs` (UnrealToolboxExampleApplication)


#### class `UnrealToolboxExampleApplication.CodeSamples`  
`static class CodeSamples`  
_internal*; L5-296_
- L7 _public field_ `public static readonly string CsprojStructure = """ <Project Sdk="Microsoft.NET.Sdk"> <PropertyGroup> <OutputType>WinExe</OutputType> <TargetFramework>net10.0</TargetFramework> <Nullable>enable</Nullable> <AvaloniaUseCompiledBindingsByDefault>true< ...`
- L25 _public field_ `public static readonly string SingleInstanceLock = """ class SingleInstanceLock : IDisposable { readonly string _lockFilePath; FileStream? _lockFileStream; public SingleInstanceLock(string appName) { string lockDir = Path.Combine( Environment.GetFolde ...`
- L61 _public field_ `public static readonly string SingleInstanceUsage = """ using SingleInstanceLock instanceLock = new SingleInstanceLock("MyApp"); if (!instanceLock.TryAcquire()) { Console.Error.WriteLine("Already running."); return 1; } """`
- L71 _public field_ `public static readonly string PlatformRidConditions = """ <!-- Default to Windows for local build --> <ItemGroup Condition="'$(RuntimeIdentifier)' == '' Or $(RuntimeIdentifier.StartsWith('win'))"> <Content Include="Toolbox.win.json" Link="Toolbox.json">  ...`
- L96 _public field_ `public static readonly string ToolboxJsonFull = """ { "installCommand": { "fileName": "MyTool.exe", "arguments": [ "--install" ] }, "uninstallCommand": { "fileName": "MyTool.exe", "arguments": [ "--uninstall" ] }, "runCommand": { "fileName": "MyToo ...`
- L134 _public field_ `public static readonly string ToolboxJsonMinimal = """ { "installCommand": { "fileName": "MyTool.exe", "arguments": [ "--install" ] }, "uninstallCommand": { "fileName": "MyTool.exe", "arguments": [ "--uninstall" ] } } """`
- L147 _public field_ `public static readonly string InstallWindows = """ static void InstallWindows(string exePath) { string shortcutPath = GetWindowsShortcutPath(); Type shellType = Type.GetTypeFromProgID("WScript.Shell") ?? throw new InvalidOperationException( "WScri ...`
- L167 _public field_ `public static readonly string InstallMacOs = """ static void InstallMacOS(string exePath) { string applicationsDir = Path.Combine( Environment.GetFolderPath( Environment.SpecialFolder.UserProfile), "Applications"); Directory.CreateDirectory(appl ...`
- L185 _public field_ `public static readonly string InstallLinux = """ static void InstallLinux(string exePath) { string applicationsDir = Path.Combine( Environment.GetFolderPath( Environment.SpecialFolder.UserProfile), ".local", "share", "applications"); Directory.C ...`
- L207 _public field_ `public static readonly string NamedEventUpdate = """ // Installer sends update request using EventWaitHandle requestEvent = new EventWaitHandle(false, EventResetMode.AutoReset, "MyApp-UpdateRequest"); requestEvent.Set(); // Running app listens and s ...`
- L228 _public field_ `public static readonly string MarkerFileUpdate = """ // Installer writes marker file File.WriteAllText(requestFilePath, "update"); // Running app polls for the file while (true) { Thread.Sleep(1000); if (!File.Exists(requestFilePath)) continue; File ...`
- L248 _public field_ `public static readonly string ToolboxWinJson = """ { "installCommand": { "fileName": "UnrealToolboxExampleApplication.exe", "arguments": [ "--install" ] }, "uninstallCommand": { "fileName": "UnrealToolboxExampleApplication.exe", "arguments": [ "-- ...`
- L270 _public field_ `public static readonly string ToolboxUnixJson = """ { "installCommand": { "fileName": "UnrealToolboxExampleApplication", "arguments": [ "--install" ] }, "uninstallCommand": { "fileName": "UnrealToolboxExampleApplication", "arguments": [ "--uninstal ...`
- L292 _public field_ `public static readonly string LocalToolFlag = """ dotnet run --project UnrealToolbox.csproj -- \ -NoUpdate -LocalTool=C:\dev\MyTool\bin\publish """`

### `Source/Programs/UnrealToolboxExampleApplication/MainWindow.axaml.cs` (UnrealToolboxExampleApplication)


#### class `UnrealToolboxExampleApplication.MainWindow`  
`public partial class MainWindow : Window`  
_public; L9-58_
- inherits: `Window`
- L11 _private* field_ `readonly Dictionary<string, UserControl> _pageCache = ...`
- L11 _private* field_ `readonly Dictionary< _pageCache = new Dictionary<string, UserControl>()`
- L13-26 _public ctor_ `public MainWindow()`
- L28-38 _private* method_ `void NavView_SelectionChanged(object? sender, NavigationViewSelectionChangedEventArgs e)`
- L40-57 _private* method_ `UserControl GetOrCreatePage(string tag)`

### `Source/Programs/UnrealToolboxExampleApplication/Pages/InstallUninstallPage.axaml.cs` (UnrealToolboxExampleApplication)


#### class `UnrealToolboxExampleApplication.Pages.InstallUninstallPage`  
`public partial class InstallUninstallPage : UserControl`  
_public; L7-13_
- inherits: `UserControl`
- L9-12 _public ctor_ `public InstallUninstallPage()`

### `Source/Programs/UnrealToolboxExampleApplication/Pages/ProjectSetupPage.axaml.cs` (UnrealToolboxExampleApplication)


#### class `UnrealToolboxExampleApplication.Pages.ProjectSetupPage`  
`public partial class ProjectSetupPage : UserControl`  
_public; L7-13_
- inherits: `UserControl`
- L9-12 _public ctor_ `public ProjectSetupPage()`

### `Source/Programs/UnrealToolboxExampleApplication/Pages/PublishingPage.axaml.cs` (UnrealToolboxExampleApplication)


#### class `UnrealToolboxExampleApplication.Pages.PublishingPage`  
`public partial class PublishingPage : UserControl`  
_public; L7-13_
- inherits: `UserControl`
- L9-12 _public ctor_ `public PublishingPage()`

### `Source/Programs/UnrealToolboxExampleApplication/Pages/ThisExamplePage.axaml.cs` (UnrealToolboxExampleApplication)


#### class `UnrealToolboxExampleApplication.Pages.ThisExamplePage`  
`public partial class ThisExamplePage : UserControl`  
_public; L7-13_
- inherits: `UserControl`
- L9-12 _public ctor_ `public ThisExamplePage()`

### `Source/Programs/UnrealToolboxExampleApplication/Pages/ToolboxJsonPage.axaml.cs` (UnrealToolboxExampleApplication)


#### class `UnrealToolboxExampleApplication.Pages.ToolboxJsonPage`  
`public partial class ToolboxJsonPage : UserControl`  
_public; L7-13_
- inherits: `UserControl`
- L9-12 _public ctor_ `public ToolboxJsonPage()`

### `Source/Programs/UnrealToolboxExampleApplication/Pages/WelcomePage.axaml.cs` (UnrealToolboxExampleApplication)


#### class `UnrealToolboxExampleApplication.Pages.WelcomePage`  
`public partial class WelcomePage : UserControl`  
_public; L7-13_
- inherits: `UserControl`
- L9-12 _public ctor_ `public WelcomePage()`

### `Source/Programs/UnrealToolboxExampleApplication/Program.cs` (UnrealToolboxExampleApplication)


#### class `UnrealToolboxExampleApplication.Program`  
`static class Program`  
_internal*; L12-383_
- L14 _public const_ `public const string UpdateRequestEventName = "UnrealToolboxExampleApp-UpdateRequest"`
- L15 _public const_ `public const string UpdateDeclinedEventName = "UnrealToolboxExampleApp-UpdateDeclined"`
- L17 _private* const_ `const string ProcessName = "UnrealToolboxExampleApplication"`
- L18 _private* const_ `const string AppDisplayName = "Unreal Toolbox Example Application"`
- L21-41 _public method_ `public static int Main(string[] args)` — attrs: `[STAThread]`
- L43-48 _public method_ `public static AppBuilder BuildAvaloniaApp()`
- L50-76 _private* method_ `static int Install()`
- L78-107 _private* method_ `static int Uninstall()`
- L111-130 _private* method_ `static bool RequestRunningInstanceShutdown()`
- L132-172 _private* method_ `static bool RequestShutdownViaNamedEvent(Process[] instances)`
- L174-253 _private* method_ `static bool RequestShutdownViaMarkerFile(Process[] instances)`
- L255-258 _public method_ `public static string GetRequestFilePath()`
- L260-263 _public method_ `public static string GetDeclinedFilePath()`
- L273-290 _private* method_ `static void InstallWindows(string exePath)` — attrs: `[SupportedOSPlatform("windows")] [UnconditionalSuppressMessage("Trimming", "IL2057", Justification = "COM type WScript.Shell is resolved at runtime by the OS, not subject to trimming.")] [UnconditionalSuppressMessage("Trimming", "IL2072", J`
- L293-301 _private* method_ `static void UninstallWindows()` — attrs: `[SupportedOSPlatform("windows")]`
- L303-307 _private* method_ `static string GetWindowsShortcutPath()`
- L313-328 _private* method_ `static void InstallMacOS(string exePath)`
- L330-342 _private* method_ `static void UninstallMacOS()`
- L348-366 _private* method_ `static void InstallLinux(string exePath)`
- L368-380 _private* method_ `static void UninstallLinux()`

#### class `UnrealToolboxExampleApplication.SingleInstanceLock`  
`class SingleInstanceLock : IDisposable`  
_internal*; L385-415_
- inherits: `IDisposable`
- L387 _private* field_ `readonly string _lockFilePath`
- L388 _private* field_ `FileStream? _lockFileStream`
- L390-395 _public ctor_ `public SingleInstanceLock(string appName)`
- L397-408 _public method_ `public bool TryAcquire()`
- L410-414 _public method_ `public void Dispose()`

### `Source/Programs/UnrealToolboxExampleApplication/UpdateDialog.axaml.cs` (UnrealToolboxExampleApplication)


#### class `UnrealToolboxExampleApplication.UpdateDialog`  
`public partial class UpdateDialog : Window`  
_public; L8-24_
- inherits: `Window`
- L10-13 _public ctor_ `public UpdateDialog()`
- L15-18 _private* method_ `void OnYesClicked(object? sender, RoutedEventArgs e)`
- L20-23 _private* method_ `void OnNoClicked(object? sender, RoutedEventArgs e)`
