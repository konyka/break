# Plugins / EditorTraceUtilities

- module root: `Plugins/TraceUtilities/Source/EditorTraceUtilities`
- headers: 6; symbols: 179
- symbol kinds: class=7, delegate=1, enum=3, enumerator=8, function=10, macro=1, member=49, namespace=10, prototype=84, struct=4, typedef=2
- PrivateDependencyModuleNames: Engine, InputCore, Slate, SlateCore, ToolMenus, TraceAnalysis, TraceInsightsFrontend, TraceLog, TraceTools, UATHelper
- PrivateIncludePathModuleNames: MessageLog
- PublicDependencyModuleNames: Core

### `Plugins/TraceUtilities/Source/EditorTraceUtilities/Private/EditorTraceUtilities.h` (Private)


#### class `UE::EditorTraceUtilities::FEditorTraceUtilitiesModule`  
`class FEditorTraceUtilitiesModule : public IEditorTraceUtilitiesModule`  
_L13-28_
- inherits: `IEditorTraceUtilitiesModule`
- L18 _public prototype_ `virtual void StartupModule() override;`
- L19 _public prototype_ `virtual void ShutdownModule() override;`
- L20 _public prototype_ `virtual const FStatusBarTraceSettings& GetTraceSettings() const override;`
- L23 _public function_ `static const FString& GetTraceUtilitiesIni()`
- L26 _private member_ `FDelegateHandle RegisterStartupCallbackHandle;`
- L27 _private member_ `static FString EditorTraceUtilitiesIni;`

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTraceUtilities, Log, All) namespace UE::EditorTraceUtilities { class FEditorTraceUtilitiesModule : public IEditorTraceUtilitiesModule { public:`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace EditorTraceUtilities` (scope `UE`)

### `Plugins/TraceUtilities/Source/EditorTraceUtilities/Private/InsightsStatusBar/EditorTraceUtilitiesStyle.h` (Private)


#### class `FEditorTraceUtilitiesStyle`  
`class FEditorTraceUtilitiesStyle final : public FSlateStyleSet`  
_L10-68_
- inherits: `FSlateStyleSet`
- L14 _public function_ `FEditorTraceUtilitiesStyle() : FSlateStyleSet("EditorTraceUtilitiesStyle")`
- L58 _public function_ `static FEditorTraceUtilitiesStyle& Get()`
- L64 _public function_ `~FEditorTraceUtilitiesStyle()`

### `Plugins/TraceUtilities/Source/EditorTraceUtilities/Private/InsightsStatusBar/SInsightsStatusBar.h` (Private)


#### struct `UE::EditorTraceUtilities::FTraceFileInfo`  
`struct FTraceFileInfo`  
_L20-30_
- L22 _public member_ `FString FilePath;`
- L23 _public member_ `FDateTime ModifiedTime;`
- L24 _public member_ `bool bIsFromTraceStore;`
- L26 _public function_ `bool operator <(const FTraceFileInfo& rhs)`

#### class `UE::EditorTraceUtilities::SInsightsStatusBarWidget`  
`class SInsightsStatusBarWidget : public SCompoundWidget`  
_L36-180_
- inherits: `SCompoundWidget`
- desc: Status bar widget for Unreal Insights. Shows buttons to start tracing either to a file or to the trace store and allows saving a snapshot to file.
- L56 _public member_ `static FStatusBarTraceSettings StatusBarTraceSettings;` — Settings this widget uses.
- L58 _public function_ `SLATE_BEGIN_ARGS(SInsightsStatusBarWidget)`
- L59 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L63 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L66 _private prototype_ `FText GetTitleToolTipText() const;`
- L68 _private prototype_ `void LaunchUnrealInsights_OnClicked();`
- L70 _private prototype_ `void OpenLiveSession_OnClicked();`
- L71 _private prototype_ `void OpenLiveSession(const FString& InTraceDestination);`
- L73 _private prototype_ `void OpenProfilingDirectory_OnClicked();`
- L74 _private prototype_ `void OpenProfilingDirectory();`
- L76 _private prototype_ `void OpenTraceStoreDirectory_OnClicked();`
- L77 _private prototype_ `void OpenTraceStoreDirectory(ESelectLatestTraceCriteria Criteria);`
- L79 _private prototype_ `void OpenLatestTraceFromFolder(const FString& InFolder, ESelectLatestTraceCriteria InCriteria);`
- L80 _private prototype_ `FString GetLatestTraceFileFromFolder(const FString& InFolder, ESelectLatestTraceCriteria InCriteria);`
- L82 _private prototype_ `void SetTraceDestination_Execute(ETraceDestination InDestination);`
- L83 _private prototype_ `bool SetTraceDestination_CanExecute();`
- L84 _private prototype_ `bool SetTraceDestination_IsChecked(ETraceDestination InDestination);`
- L86 _private prototype_ `void SaveSnapshot();`
- L87 _private prototype_ `bool SaveSnapshot_CanExecute() const;`
- L89 _private prototype_ `FText GetTraceMenuItemText() const;`
- L90 _private prototype_ `FText GetTraceMenuItemTooltipText() const;`
- L92 _private prototype_ `void ToggleTrace_OnClicked();`
- L93 _private prototype_ `bool ToggleTrace_CanExecute() const;`
- L95 _private prototype_ `bool PauseTrace_CanExecute();`
- L96 _private prototype_ `FText GetPauseTraceMenuItemTooltipText() const;`
- L97 _private prototype_ `void TogglePauseTrace_OnClicked();`
- L99 _private prototype_ `bool StartTracing();`
- L101 _private prototype_ `TSharedRef<SWidget> MakeTraceMenu();`
- L102 _private prototype_ `void Channels_BuildMenu(FMenuBuilder& MenuBuilder);`
- L103 _private prototype_ `void Traces_BuildMenu(FMenuBuilder& MenuBuilder);`
- L105 _private prototype_ `void LogMessage(const FText& Text);`
- L106 _private prototype_ `void ShowNotification(const FText& Text, const FText& SubText);`
- L108 _private prototype_ `bool GetBooleanSettingValue(const TCHAR* InSettingName);`
- L109 _private prototype_ `void ToggleBooleanSettingValue(const TCHAR* InSettingName);`
- L111 _private prototype_ `void OnTraceStarted(FTraceAuxiliary::EConnectionType TraceType, const FString& TraceDestination);`
- L112 _private prototype_ `void OnTraceStopped(FTraceAuxiliary::EConnectionType TraceType, const FString& TraceDestination);`
- L113 _private prototype_ `void OnSnapshotSaved(FTraceAuxiliary::EConnectionType TraceType, const FString& TraceDestination);`
- L115 _private prototype_ `void CacheTraceStorePath();`
- L117 _private prototype_ `void ToggleChannel_Execute(int32 Index);`
- L118 _private prototype_ `bool ToggleChannel_IsChecked(int32 Index);`
- L120 _private prototype_ `void CreateChannelsInfo();`
- L121 _private prototype_ `void UpdateChannelsInfo();`
- L123 _private prototype_ `void InitCommandList();`
- L125 _private prototype_ `bool TraceScreenshot_CanExecute() const;`
- L126 _private prototype_ `void TraceScreenshot_Execute();`
- L127 _private prototype_ `FText GetTraceScreenshotTooltipText() const;`
- L129 _private prototype_ `bool TraceBookmark_CanExecute() const;`
- L130 _private prototype_ `void TraceBookmark_Execute();`
- L131 _private prototype_ `FText GetTraceBookmarkTooltipText() const;`
- L133 _private prototype_ `FText GetTraceRegionName();`
- L134 _private member_ `FText TraceRegionName = FText();`
- L135 _private prototype_ `FText GetTraceRegionNameDesc();`
- L137 _private prototype_ `void ToggleRegion_Execute();`
- L138 _private prototype_ `bool ToggleRegion_CanExecute() const;`
- L139 _private prototype_ `bool RegionIsActive() const;`
- L140 _private prototype_ `FText GetRegionSwitchLabelText() const;`
- L141 _private prototype_ `FText GetRegionSwitchDescText() const;`
- L143 _private prototype_ `void PopulateRecentTracesList();`
- L145 _private prototype_ `void OpenTrace(int32 Index);`
- L148 _private member_ `static const TCHAR* DefaultPreset;`
- L149 _private member_ `static const TCHAR* MemoryPreset;`
- L150 _private member_ `static const TCHAR* TaskGraphPreset;`
- L151 _private member_ `static const TCHAR* ContextSwitchesPreset;`
- L153 _private member_ `static const TCHAR* SettingsCategory;`
- L154 _private member_ `static const TCHAR* OpenLiveSessionOnTraceStartSettingName;`
- L155 _private member_ `static const TCHAR* OpenInsightsAfterTraceSettingName;`
- L156 _private member_ `static const TCHAR* TraceRegionSettingName;`
- L157 _private member_ `static const TCHAR* ShowInExplorerAfterTraceSettingName;`
- L159 _private member_ `bool bIsTraceRecordButtonHovered = false;`
- L160 _private member_ `mutable double ConnectionStartTime = 0.0f;`
- L162 _private member_ `FString TraceStorePath;`
- L164 _private member_ `TArray<FChannelData> ChannelsInfo;`
- L165 _private member_ `bool bShouldUpdateChannels = false;`
- L167 _private member_ `TSharedPtr<FLiveSessionTracker> LiveSessionTracker;`
- L169 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L171 _private member_ `TArray<UE::Insights::FTraceServerControl> ServerControls;`
- L173 _private member_ `TArray<TSharedPtr<FTraceFileInfo>> Traces;`
- L174 _private member_ `FName LogListingName;`
- L176 _private member_ `uint64 RegionId = 0;`
- L178 _private member_ `bool bShouldTryOpenLiveSession = false;`
- L179 _private member_ `double OpenLiveSessionScheduledTime = 0.0f;`

#### struct `UE::EditorTraceUtilities::SInsightsStatusBarWidget::FChannelData`  
`struct FChannelData`  
_L38-44_
- L40 _public member_ `FString Name;`
- L41 _public member_ `FString Desc;`
- L42 _public member_ `bool bIsEnabled = false;`
- L43 _public member_ `bool bIsReadOnly = false;`

#### enum `UE::EditorTraceUtilities::SInsightsStatusBarWidget::ESelectLatestTraceCriteria`  
`enum class ESelectLatestTraceCriteria : uint32`  
_L46-51_
- L48 _public enumerator_ `None`
- L49 _public enumerator_ `CreatedTime`
- L50 _public enumerator_ `ModifiedTime`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Insights` (scope `UE`)
- L16 _prototype_ `TSharedRef<SWidget> CreateInsightsStatusBarWidget();`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace EditorTraceUtilities` (scope `UE`)

### `Plugins/TraceUtilities/Source/EditorTraceUtilities/Private/InsightsStatusBar/SRecentTracesList.h` (Private)


#### class `UE::EditorTraceUtilities::SRecentTracesListEntry`  
`class SRecentTracesListEntry : public SCompoundWidget`  
_L17-34_
- inherits: `SCompoundWidget`
- desc: A widget that shows an entry in the recent traces submenu.
- L19 _private function_ `SLATE_BEGIN_ARGS(SRecentTracesListEntry)`
- L20 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FTraceFileInfo> InTrace, const FString& InStorePath, TSharedPtr<FLiveSessionTracker> InLiveSessionTracker);`
- L25 _private prototype_ `FReply OpenContainingFolder();`
- L27 _private prototype_ `EVisibility GetLiveLabelVisibility() const;`
- L30 _private member_ `FString StorePath;`
- L31 _private member_ `TSharedPtr<FTraceFileInfo> TraceInfo;`
- L32 _private member_ `FString TraceName;`
- L33 _private member_ `TSharedPtr<FLiveSessionTracker> LiveSessionTracker;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace EditorTraceUtilities` (scope `UE`)

### `Plugins/TraceUtilities/Source/EditorTraceUtilities/Public/IEditorTraceUtilitiesModule.h` (Public)


#### enum `UE::EditorTraceUtilities::ETraceDestination`  
`enum class ETraceDestination : uint32`  
_L9-13_
- L11 _public enumerator_ `TraceStore = 0`
- L12 _public enumerator_ `File = 1`

#### struct `UE::EditorTraceUtilities::FStatusBarTraceSettings`  
`struct FStatusBarTraceSettings`  
_L16-19_
- desc: The tracing settings the status bar extension manages.
- L18 _public member_ `ETraceDestination TraceDestination = ETraceDestination::TraceStore;`

#### class `UE::EditorTraceUtilities::IEditorTraceUtilitiesModule`  
`class IEditorTraceUtilitiesModule : public IModuleInterface`  
_L21-50_
- inherits: `IModuleInterface`
- L31 _public function_ `static inline IEditorTraceUtilitiesModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L42 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() during shutdown if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L49 _public prototype_ `virtual const FStatusBarTraceSettings& GetTraceSettings() const = 0;` — Gets the tracing settings the status bar extension manages.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace EditorTraceUtilities` (scope `UE`)

### `Plugins/TraceUtilities/Source/EditorTraceUtilities/Public/UnrealInsightsLauncher.h` (Public)


#### class `FUnrealInsightsLauncher`  
`class FUnrealInsightsLauncher : public TSharedFromThis<FUnrealInsightsLauncher>`  
_L11-115_
- inherits: `TSharedFromThis<FUnrealInsightsLauncher>`
- L23 _public typedef_ `typedef TFunction<void(const EStartInsightsResult )> StartUnrealInsightsCallback;`
- L25 _public prototype_ `FUnrealInsightsLauncher();`
- L26 _public prototype_ `~FUnrealInsightsLauncher();`
- L28 _public member_ `static TSharedPtr<FUnrealInsightsLauncher> Instance;`
- L30 _public function_ `static const TSharedPtr<FUnrealInsightsLauncher>& Get()`
- L42 _public prototype_ `FString GetInsightsApplicationPath();` — Returns the full path to UnrealInsights.exe for the current engine installation
- L50 _public prototype_ `void StartUnrealInsights(const FString& Path, const FString& Parameters = TEXT(""));` — Launches the UnrealInsights executable from the given Path, displays an editor message if it fails. If the executable is not found, a build process is started. @param Path The full filename of UnrealInsights.exe to launch @param Parameters The command line parameters to use when launching the exe
- L59 _public prototype_ `void StartUnrealInsights(const FString& Path, const FString& Parameters, StartUnrealInsightsCallback Callback);` — Launches the UnrealInsights executable from the given Path, displays an editor message if it fails. If the executable is not found, a build process is started. @param Path The full filename of UnrealInsights.exe to launch @param Parameters The command line parameters to use when launching the exe @param Callback A Callback that will be called when the launch process is completed.
- L64 _public prototype_ `void CloseUnrealInsights();` — Closes UnrealInsights.exe.
- L72 _public prototype_ `bool TryOpenTraceFromDestination(const FString& Destination );` — Try to open a trace file from the trace target returned by UE::Trace::GetTraceDestination(). Destination may contain a file name or IP address of a trace server. In the latter case we try to query the file name of the active/live trace through the storebrowser API and open the remote trace in Insights. @param Destination The trace destination of the currently running trace session.
- L79 _public prototype_ `bool OpenTraceFile(const FString& FilePath);` — Launches UnrealInsights.exe with FilePath as the only parameter @param  FilePath Full file name and path to a .utrace file on the local machine @return
- L88 _public prototype_ `bool OpenRemoteTrace(const FString& TraceHostAddress, const uint16 TraceHostPort, uint32 TraceID);` — Launches UnrealInsights.exe with the -Store and -OpenTraceID parameters @param  TraceHostAddress hostname or ip address of the trace host @param  TraceHostPort Port the Trace Host is running on @param  TraceID ID of the Trace to open, can be obtained through the UE::Trace::FStoreBrowser interface @return
- L94 _public prototype_ `bool OpenActiveTraceFromStore(const FString& TraceHostAddress);` — This function tries to query the file name of the active/live trace through the storebrowser API @param Hostname hostname or ip of the target UnrealTraceServerX
- L101 _private prototype_ `void BuildUnrealInsights(const FString& Path, const FString& LaunchParameters, StartUnrealInsightsCallback Callback);` — Attempts building UnrealInsights via UAT, will launch with forwarded parameters if successful. Assumes that the Insights Executable in path belongs to this engine.
- L104 _private prototype_ `void LogMessage(const FText& Message);` — Logs an error message to the MessageLog window
- L107 _private prototype_ `void LogMessageOnGameThread(const FText& Message);` — Logs an error message to the MessageLog window using a task that is ran on the Game Thread.
- L111 _private member_ `FName LogListingName;` — The name of the Unreal Insights log listing.
- L114 _private member_ `FProcHandle UnrealInsightsHandle;` — The proccess handler of the Unreal Insights.

#### enum `FUnrealInsightsLauncher::EStartInsightsResult`  
`enum class EStartInsightsResult : uint32`  
_L16-21_
- L18 _public enumerator_ `Completed = 0`
- L19 _public enumerator_ `BuildFailed = 1`
- L20 _public enumerator_ `LaunchFailed = 2`

#### struct `FLiveSessionTaskData`  
`struct FLiveSessionTaskData`  
_L119-123_
- L121 _public member_ `FLiveSessionsMap TaskLiveSessionData;`
- L122 _public member_ `uint32 StorePort;`

#### class `FLiveSessionTracker`  
`class FLiveSessionTracker`  
_L125-147_
- L128 _public prototype_ `FLiveSessionTracker();`
- L129 _public prototype_ `~FLiveSessionTracker() = default;`
- L131 _public prototype_ `void Update();`
- L132 _public prototype_ `void StartQuery();`
- L134 _public prototype_ `bool HasData();`
- L135 _public prototype_ `const FLiveSessionsMap& GetLiveSessions();`
- L136 _public prototype_ `uint32 GetStorePort();`
- L139 _private member_ `bool bHasData = false;`
- L140 _private member_ `bool bIsQueryInProgress = false;`
- L141 _private member_ `uint32 StorePort;`
- L143 _private member_ `FLiveSessionsMap LiveSessionMap;`
- L144 _private member_ `TSharedPtr<FLiveSessionTaskData> TaskLiveSessionData;`
- L146 _private member_ `FGraphEventRef Event;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API EDITORTRACEUTILITIES_API`
- L117 _typedef_ `typedef TMap<FString, uint32> FLiveSessionsMap;`
