# Programs / LiveLinkHubLauncher

- module root: `Source/Programs/LiveLinkHub/Source/LiveLinkHubLauncher`
- headers: 2; symbols: 9
- symbol kinds: namespace=2, prototype=7
- PrivateDependencyModuleNames: AgilitySDK, ApplicationCore, AssetRegistry, AutomationController, AutomationTest, AutomationWorker, Core, CoreUObject, DerivedDataCache, DesktopPlatform, Engine, InputCore, InstallBundleManager, LiveLinkHub, MediaUtils, Messaging, MoviePlayer, MoviePlayerProxy, PluginBrowser, PreLoadScreen, ProfileVisualizer, Projects, PropertyEditor, RHI, RenderCore, Slate, SlateCore, StandaloneRenderer, ToolWidgets, TraceLog, UnixCommonStartup, UnrealEd
- PrivateIncludePathModuleNames: AutomationController, AutomationTest, AutomationWorker, DerivedDataCache, HeadMountedDisplay, Launch, MRMesh, SlateNullRenderer, SlateRHIRenderer

### `Source/Programs/LiveLinkHub/Source/LiveLinkHubLauncher/Private/LiveLinkHubPluginHelpers.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace LiveLinkHub`
- L7 _namespace_ `namespace PluginHelpers` (scope `LiveLinkHub`)
- L10 _prototype_ `FString GetPluginConfigPath();` (scope `LiveLinkHub::PluginHelpers`) — Returns the path to LiveLinkHubPlugins.ini.
- L13 _prototype_ `void ReadPluginDirectoriesFromConfig(TArray<FString>& OutDirectories);` (scope `LiveLinkHub::PluginHelpers`) — Returns the user plugin directories stored in LiveLinkHubPlugins.ini.
- L16 _prototype_ `void WritePluginDirectoriesToConfig(const TArray<FString>& InDirectories);` (scope `LiveLinkHub::PluginHelpers`) — Serializes the specified user plugin directories out to LiveLinkHubPlugins.ini.
- L19 _prototype_ `void RestoreSavedPluginDirectories();` (scope `LiveLinkHub::PluginHelpers`) — Reads the configured user plugin directories and adds them to the plugin manager search path.
- L22 _prototype_ `void HandlePluginDirectoriesChanged();` (scope `LiveLinkHub::PluginHelpers`) — Stores the latest plugin manager search paths to disk.
- L25 _prototype_ `void RegisterPluginDirectoriesChangedHandler();` (scope `LiveLinkHub::PluginHelpers`) — Connects the `HandlePluginDirectoriesChanged` handler to the plugin browser directories changed event.

### `Source/Programs/LiveLinkHub/Source/LiveLinkHubLauncher/Private/LiveLinkHubRun.h` (Private)


#### Free symbols / members of external scopes

- L7 _prototype_ `int32 RunLiveLinkHub(const TCHAR* CommandLine);`
