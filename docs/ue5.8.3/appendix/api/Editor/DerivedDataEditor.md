# Editor / DerivedDataEditor

- module root: `Source/Editor/DerivedDataEditor`
- headers: 2; symbols: 42
- symbol kinds: class=3, function=1, macro=1, member=14, prototype=23
- DynamicallyLoadedModuleNames: MainFrame
- PrivateDependencyModuleNames: Core, CoreUObject, DerivedDataCache, DerivedDataWidgets, EditorFramework, EditorSubsystem, Engine, InputCore, MessageLog, OutputLog, Slate, SlateCore, ToolMenus, ToolWidgets, UnrealEd, WorkspaceMenuStructure
- PrivateIncludePathModuleNames: 

### `Source/Editor/DerivedDataEditor/Private/SDerivedDataStatusBar.h` (Private)


#### class `FDerivedDataEditorMenuCommands`  
`class FDerivedDataEditorMenuCommands : public TCommands<FDerivedDataEditorMenuCommands>`  
_L18-40_
- inherits: `TCommands<FDerivedDataEditorMenuCommands>`
- L22 _public prototype_ `FDerivedDataEditorMenuCommands();`
- L24 _public prototype_ `virtual void RegisterCommands() override;`
- L28 _private prototype_ `static void ChangeSettings_Clicked();`
- L29 _private prototype_ `static void ViewCacheStatistics_Clicked();`
- L30 _private prototype_ `static void ViewResourceUsage_Clicked();`
- L34 _public member_ `TSharedPtr< FUICommandInfo > ChangeSettings;`
- L35 _public member_ `TSharedPtr< FUICommandInfo > ViewResourceUsage;`
- L36 _public member_ `TSharedPtr< FUICommandInfo > ViewCacheStatistics;`
- L37 _public member_ `TSharedPtr< FUICommandInfo > LaunchZenDashboard;`
- L39 _public member_ `static TSharedRef<FUICommandList> ActionList;`

#### class `SDerivedDataStatusBarWidget`  
`class SDerivedDataStatusBarWidget : public SCompoundWidget`  
_L43-68_
- inherits: `SCompoundWidget`
- L45 _private function_ `SLATE_BEGIN_ARGS(SDerivedDataStatusBarWidget)`
- L46 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L52 _private prototype_ `FText GetTitleToolTipText() const;`
- L53 _private prototype_ `FText GetRemoteCacheToolTipText() const;`
- L54 _private prototype_ `FText GetTitleText() const;`
- L55 _private prototype_ `const FSlateBrush* GetRemoteCacheStateBackgroundIcon() const;`
- L56 _private prototype_ `const FSlateBrush* GetRemoteCacheStateBadgeIcon() const;`
- L57 _private prototype_ `TSharedRef<SWidget> CreateStatusBarMenu();`
- L58 _private prototype_ `EActiveTimerReturnType UpdateBusyIndicator(double InCurrentTime, float InDeltaTime);`
- L59 _private prototype_ `EActiveTimerReturnType UpdateWarnings(double InCurrentTime, float InDeltaTime);`
- L61 _private member_ `double ElapsedDownloadTime = 0;`
- L62 _private member_ `double ElapsedUploadTime = 0;`
- L63 _private member_ `double ElapsedBusyTime = 0;`
- L65 _private member_ `bool bBusy = false;`
- L67 _private member_ `TSharedPtr<SNotificationItem> NotificationItem;`

### `Source/Editor/DerivedDataEditor/Public/DerivedDataEditor.h` (Public)


#### class `FDerivedDataEditor`  
`class FDerivedDataEditor : public IModuleInterface`  
_L23-55_
- inherits: `IModuleInterface`
- desc: The module holding all of the UI related pieces for DerivedData
- L30 _public prototype_ `virtual void StartupModule() override;` — Called right after the module DLL has been loaded and the module object has been created
- L35 _public prototype_ `virtual void ShutdownModule() override;` — Called before the module is unloaded, right before the module object is destroyed.
- L37 _public prototype_ `TSharedRef<SWidget> CreateStatusBarWidget();`
- L39 _public prototype_ `void ShowResourceUsageTab();`
- L40 _public prototype_ `void ShowCacheStatisticsTab();`
- L44 _private prototype_ `TSharedPtr<SWidget> CreateResourceUsageDialog();`
- L45 _private prototype_ `TSharedPtr<SWidget> CreateCacheStatisticsDialog();`
- L47 _private prototype_ `TSharedRef<SDockTab> CreateResourceUsageTab(const FSpawnTabArgs& Args);`
- L48 _private prototype_ `TSharedRef<SDockTab> CreateCacheStatisticsTab(const FSpawnTabArgs& Args);`
- L50 _private member_ `TWeakPtr<SDockTab> ResourceUsageTab;`
- L51 _private member_ `TWeakPtr<SDockTab> CacheStatisticsTab;`
- L53 _private member_ `TSharedPtr<SWindow> SettingsWindow;`
- L54 _private member_ `TSharedPtr<SDerivedDataCacheSettingsDialog> SettingsDialog;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API DERIVEDDATAEDITOR_API`
