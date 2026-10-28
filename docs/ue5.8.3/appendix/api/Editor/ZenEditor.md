# Editor / ZenEditor

- module root: `Source/Editor/ZenEditor`
- headers: 3; symbols: 89
- symbol kinds: class=4, enum=1, enumerator=3, function=2, macro=2, member=29, namespace=4, prototype=43, typedef=1
- DynamicallyLoadedModuleNames: MainFrame
- PrivateDependencyModuleNames: Core, CoreUObject, DerivedDataCache, DerivedDataWidgets, EditorFramework, EditorSubsystem, Engine, InputCore, MessageLog, OutputLog, Slate, SlateCore, StorageServerWidgets, ToolMenus, ToolWidgets, UATHelper, UnrealEd, WorkspaceMenuStructure, Zen
- PrivateIncludePathModuleNames: 

### `Source/Editor/ZenEditor/Private/SZenStatusBar.h` (Private)


#### class `FZenStausBarCommands`  
`class FZenStausBarCommands : public TCommands<FZenStausBarCommands>`  
_L21-55_
- inherits: `TCommands<FZenStausBarCommands>`
- L25 _public prototype_ `FZenStausBarCommands();`
- L27 _public prototype_ `virtual void RegisterCommands() override;`
- L31 _private prototype_ `static void ChangeCacheSettings_Clicked();`
- L32 _private prototype_ `static void ViewCacheStatistics_Clicked();`
- L33 _private prototype_ `static void ViewResourceUsage_Clicked();`
- L34 _private prototype_ `static void ViewServerStatus_Clicked();`
- L35 _private prototype_ `static void ViewZenStore_Clicked();`
- L36 _private prototype_ `static void LaunchZenDashboard_Clicked();`
- L37 _private prototype_ `static void StartZenServer_Clicked();`
- L38 _private prototype_ `static void StopZenServer_Clicked();`
- L39 _private prototype_ `static void RestartZenServer_Clicked();`
- L43 _public member_ `TSharedPtr< FUICommandInfo > ChangeCacheSettings;`
- L44 _public member_ `TSharedPtr< FUICommandInfo > ViewResourceUsage;`
- L45 _public member_ `TSharedPtr< FUICommandInfo > ViewCacheStatistics;`
- L46 _public member_ `TSharedPtr< FUICommandInfo > ViewServerStatus;`
- L47 _public member_ `TSharedPtr< FUICommandInfo > ViewZenStore;`
- L48 _public member_ `TSharedPtr< FUICommandInfo > LaunchZenDashboard;`
- L49 _public member_ `TSharedPtr< FUICommandInfo > StartZenServer;`
- L50 _public member_ `TSharedPtr< FUICommandInfo > StopZenServer;`
- L51 _public member_ `TSharedPtr< FUICommandInfo > RestartZenServer;`
- L53 _public member_ `static TSharedRef<FUICommandList> ActionList;`
- L54 _public member_ `static TSharedPtr<UE::Zen::FServiceInstanceManager> ServiceInstanceManager;`

#### class `SZenStatusBarWidget`  
`class SZenStatusBarWidget : public SCompoundWidget`  
_L58-91_
- inherits: `SCompoundWidget`
- L60 _private function_ `SLATE_BEGIN_ARGS(SZenStatusBarWidget)`
- L61 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L67 _private prototype_ `FText GetTitleToolTipText() const;`
- L68 _private prototype_ `FText GetTitleText() const;`
- L70 _private prototype_ `FText GetServerStateToolTipText() const;`
- L71 _private prototype_ `const FSlateBrush* GetServerStateBadgeIcon() const;`
- L72 _private prototype_ `const FSlateBrush* GetServerStateBackgroundIcon() const;`
- L74 _private prototype_ `TSharedRef<SWidget> CreateStatusBarMenu();`
- L75 _private prototype_ `EActiveTimerReturnType UpdateBusyIndicator(double InCurrentTime, float InDeltaTime);`
- L76 _private prototype_ `EActiveTimerReturnType UpdateWarnings(double InCurrentTime, float InDeltaTime);`
- L78 _private member_ `double ElapsedDownloadTime = 0;`
- L79 _private member_ `double ElapsedUploadTime = 0;`
- L80 _private member_ `double ElapsedBusyTime = 0;`
- L82 _private member_ `bool IsRunning = false;`
- L83 _private member_ `bool IsDownloading = false;`
- L84 _private member_ `bool IsUploading = false;`
- L85 _private member_ `bool IsReading = false;`
- L86 _private member_ `bool IsWriting = false;`
- L87 _private member_ `bool IsBusy = false;`
- L89 _private member_ `TSharedPtr<SNotificationItem> NotificationItem;`
- L90 _private member_ `TSharedPtr<UE::Zen::FServiceInstanceManager> ServiceInstanceManager;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Zen` (scope `UE`)

### `Source/Editor/ZenEditor/Private/ZenDashboardLauncher.h` (Private)


#### class `UE::Zen::FZenDashboardLauncher`  
`class FZenDashboardLauncher : public TSharedFromThis<FZenDashboardLauncher>`  
_L13-76_
- inherits: `TSharedFromThis<FZenDashboardLauncher>`
- L23 _public typedef_ `typedef TFunction<void(const EStartZenDashboardResult )> StartZenDashboardCallback;`
- L25 _public prototype_ `FZenDashboardLauncher();`
- L26 _public prototype_ `~FZenDashboardLauncher();`
- L28 _public function_ `static const TSharedPtr<FZenDashboardLauncher>& Get()`
- L40 _public prototype_ `FString GetZenDashboardApplicationPath();` — Returns the full path to ZenDashboard.exe for the current engine installation
- L48 _public prototype_ `void StartZenDashboard(const FString& Path, const FString& Parameters = TEXT(""));` — Launches the ZenDashboard executable from the given Path, displays an editor message if it fails. If the executable is not found, a build process is started. @param Path The full filename of ZenDashboard.exe to launch @param Parameters The command line parameters to use when launching the exe
- L57 _public prototype_ `void StartZenDashboard(const FString& Path, const FString& Parameters, StartZenDashboardCallback Callback);` — Launches the ZenDashboard executable from the given Path, displays an editor message if it fails. If the executable is not found, a build process is started. @param Path The full filename of ZenDashboard.exe to launch @param Parameters The command line parameters to use when launching the exe @param Callback A Callback that will be called when the launch process is completed.
- L62 _public prototype_ `void CloseZenDashboard();` — Closes ZenDashboard.exe.
- L69 _private prototype_ `void BuildZenDashboard(const FString& Path, const FString& LaunchParameters, StartZenDashboardCallback Callback);` — Attempts building ZenDashboard via UAT, will launch with forwarded parameters if successful. Assumes that the ZenDashboard Executable in path belongs to this engine.
- L73 _private member_ `FProcHandle ZenDashboardHandle;` — The process handler of ZenDashboard.
- L75 _private member_ `static TSharedPtr<FZenDashboardLauncher> Instance;`

#### enum `UE::Zen::FZenDashboardLauncher::EStartZenDashboardResult`  
`enum class EStartZenDashboardResult : uint32`  
_L16-21_
- L18 _public enumerator_ `Completed = 0`
- L19 _public enumerator_ `BuildFailed = 1`
- L20 _public enumerator_ `LaunchFailed = 2`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Zen` (scope `UE`)

### `Source/Editor/ZenEditor/Public/ZenEditor.h` (Public)


#### class `FZenEditor`  
`class FZenEditor : public IModuleInterface`  
_L23-63_
- inherits: `IModuleInterface`
- desc: The module holding all of the UI related pieces for DerivedData
- L30 _public prototype_ `virtual void StartupModule() override;` — Called right after the module DLL has been loaded and the module object has been created
- L35 _public prototype_ `virtual void ShutdownModule() override;` — Called before the module is unloaded, right before the module object is destroyed.
- L37 _public prototype_ `bool IsZenEnabled() const;`
- L38 _public prototype_ `TSharedRef<SWidget> CreateStatusBarWidget();`
- L40 _public prototype_ `void ShowResourceUsageTab();`
- L41 _public prototype_ `void ShowCacheStatisticsTab();`
- L42 _public prototype_ `void ShowZenServerStatusTab();`
- L43 _public prototype_ `void StartZenServer();`
- L44 _public prototype_ `void StopZenServer();`
- L45 _public prototype_ `void RestartZenServer();`
- L49 _private prototype_ `TSharedPtr<SWidget> CreateResourceUsageDialog();`
- L50 _private prototype_ `TSharedPtr<SWidget> CreateCacheStatisticsDialog();`
- L51 _private prototype_ `TSharedPtr<SWidget> CreateZenStoreDialog();`
- L53 _private prototype_ `TSharedRef<SDockTab> CreateResourceUsageTab(const FSpawnTabArgs& Args);`
- L54 _private prototype_ `TSharedRef<SDockTab> CreateCacheStatisticsTab(const FSpawnTabArgs& Args);`
- L55 _private prototype_ `TSharedRef<SDockTab> CreateZenServerStatusTab(const FSpawnTabArgs& Args);`
- L57 _private member_ `TWeakPtr<SDockTab> ResourceUsageTab;`
- L58 _private member_ `TWeakPtr<SDockTab> CacheStatisticsTab;`
- L59 _private member_ `TWeakPtr<SDockTab> ZenServerStatusTab;`
- L61 _private member_ `TSharedPtr<SWindow> SettingsWindow;`
- L62 _private member_ `TSharedPtr<SDerivedDataCacheSettingsDialog> SettingsDialog;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API ZENEDITOR_API`
