# Programs / SlateUGS

- module root: `Source/Programs/SlateUGS`
- headers: 20; symbols: 296
- symbol kinds: class=19, delegate=1, enum=2, enumerator=7, function=15, member=99, namespace=5, prototype=147, struct=1
- PrivateDependencyModuleNames: AppFramework, ApplicationCore, Core, DesktopPlatform, PakFile, Projects, Slate, SlateCore, StandaloneRenderer, ToolWidgets, UGSCore, UnixCommonStartup
- PublicIncludePathModuleNames: Launch

### `Source/Programs/SlateUGS/Private/ChangeInfo.h` (Private)


#### struct `FChangeInfo`  
`struct FChangeInfo`  
_L8-23_
- L10 _public member_ `FDateTime Time;`
- L11 _public member_ `bool bHeaderRow = false;`
- L13 _public member_ `UGSCore::EReviewVerdict ReviewStatus = UGSCore::EReviewVerdict::Unknown;`
- L14 _public member_ `int Changelist = 0;`
- L15 _public member_ `bool bCurrentlySynced = false;`
- L16 _public member_ `bool bSyncingPrecompiled = false;`
- L17 _public member_ `bool bHasZippedBinaries = false;`
- L18 _public member_ `UGSCore::FChangeType ChangeType;`
- L19 _public member_ `FText Author;`
- L20 _public member_ `FString Description;`

### `Source/Programs/SlateUGS/Private/ScheduledSyncTimer.h` (Private)


#### class `ScheduledSyncTimer`  
`class ScheduledSyncTimer : FRunnable`  
_L10-26_
- inherits: `FRunnable`
- L13 _public prototype_ `~ScheduledSyncTimer();`
- L15 _public prototype_ `void Start(const FDateTime& InScheduledTime, const TFunction<void()>& InTimerElapsedCallback);`
- L16 _public prototype_ `void Stop();`
- L19 _private prototype_ `virtual uint32 Run() override;`
- L21 _private member_ `bool bFinished = false;`
- L23 _private member_ `FDateTime ScheduledTime;`
- L24 _private member_ `FRunnableThread* WorkerThread = nullptr;`
- L25 _private member_ `TFunction<void()> TimerElapsedCallback;`

### `Source/Programs/SlateUGS/Private/SlateUGSStyle.h` (Private)


#### class `FSlateUGSStyle`  
`class FSlateUGSStyle : public FSlateStyleSet`  
_L8-23_
- inherits: `FSlateStyleSet`
- L11 _public prototype_ `virtual const FName& GetStyleSetName() const override;`
- L13 _public prototype_ `static const FSlateUGSStyle& Get();`
- L14 _public prototype_ `static void Shutdown();`
- L16 _public prototype_ `~FSlateUGSStyle();`
- L19 _private prototype_ `FSlateUGSStyle();`
- L21 _private member_ `static FName StyleName;`
- L22 _private member_ `static TUniquePtr<FSlateUGSStyle> Inst;`

### `Source/Programs/SlateUGS/Private/UGSLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSlateUGS, Verbose, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSlateUGS, Verbose, All);`

### `Source/Programs/SlateUGS/Private/UGSTab.h` (Private)


#### enum `SyncCategoryType`  
`enum SyncCategoryType`  
_L25-29_
- L27 _public enumerator_ `CurrentWorkspace`
- L28 _public enumerator_ `AllWorkspaces`

#### class `UGSTab`  
`class UGSTab`  
_L31-134_
- L34 _public prototype_ `UGSTab();`
- L35 _public prototype_ `~UGSTab();`
- L37 _public prototype_ `void Initialize(TSharedPtr<UGSCore::FUserSettings> UserSettings);`
- L39 _public prototype_ `const TSharedRef<SDockTab> GetTabWidget();`
- L40 _public prototype_ `FSpawnTabArgs GetTabArgs() const;`
- L42 _public prototype_ `void SetTabManager(UGSTabManager* InTabManager);`
- L43 _public prototype_ `void SetTabArgs(FSpawnTabArgs InTabArgs);`
- L45 _public prototype_ `void Tick();`
- L47 _public prototype_ `bool IsProjectLoaded() const;`
- L50 _public prototype_ `bool OnWorkspaceChosen(const FString& Project);` — Slate callbacks
- L51 _public prototype_ `void OnSyncChangelist(int Changelist);`
- L52 _public prototype_ `void OnViewInSwarmClicked(int Changelist) const;`
- L53 _public prototype_ `void OnCopyChangeListClicked(int Changelist) const;`
- L54 _public prototype_ `void OnMoreInfoClicked(int Changelist) const;`
- L55 _public prototype_ `void OnOpenPerforceClicked() const;`
- L56 _public prototype_ `void OnSyncLatest();`
- L57 _public prototype_ `void OnSyncFilterWindowSaved( const TArray<FString>& SyncViewCurrent, const TArray<FGuid>& SyncIncludedCategoriesCurrent, const TArray<FGuid>& SyncExcludedCategoriesCurrent, const TArray<FString>& SyncViewAll, const TArray<FGuid>& SyncIncludedCategoriesAll, const TArray<FGuid>& SyncExcludedCategoriesAll);`
- L64 _public prototype_ `void OnBuildWorkspace();`
- L65 _public prototype_ `void OnOpenExplorer();`
- L66 _public prototype_ `void OnOpenEditor();`
- L67 _public prototype_ `void OnCreateWorkspace(const FString& WorkspaceName, const FString& Stream, const FString& RootDirectory) const;`
- L70 _public prototype_ `bool IsSyncing() const;` — Accessors
- L71 _public prototype_ `FString GetSyncProgress() const;`
- L72 _public prototype_ `const TArray<FString>& GetCombinedSyncFilter() const;`
- L73 _public prototype_ `TArray<UGSCore::FWorkspaceSyncCategory> GetSyncCategories(SyncCategoryType CategoryType) const;`
- L74 _public prototype_ `TArray<FString> GetSyncViews(SyncCategoryType CategoryType) const;`
- L75 _public prototype_ `UGSTabManager* GetTabManager() const;`
- L76 _public prototype_ `TSharedPtr<UGSCore::FUserSettings> GetUserSettings() const;`
- L77 _public prototype_ `bool ShouldSyncPrecompiledEditor() const;`
- L78 _public prototype_ `TArray<FString> GetAllStreamNames() const;`
- L80 _public prototype_ `void UpdateGameTabBuildList();`
- L81 _public prototype_ `void RefreshBuildList();`
- L82 _public prototype_ `void CancelSync();`
- L85 _private prototype_ `void OnWorkspaceSyncComplete( TSharedRef<UGSCore::FWorkspaceUpdateContext, ESPMode::ThreadSafe> WorkspaceContext, UGSCore::EWorkspaceUpdateResult SyncResult, const FString& StatusMessage);`
- L90 _private prototype_ `TMap<FString, FString> GetWorkspaceVariables() const;`
- L91 _private prototype_ `UGSCore::EBuildConfig GetEditorBuildConfig() const;`
- L92 _private prototype_ `TMap<FGuid, UGSCore::FCustomConfigObject> GetDefaultBuildStepObjects(const FString& EditorTargetName);`
- L95 _private prototype_ `void QueueMessageForMainThread(TFunction<void()> Function);` — Allows the queuing of functions from threads to be run on the main thread
- L97 _private prototype_ `bool ShouldIncludeInReviewedList(const TSet<int>& PromotedChangeNumbers, int ChangeNumber) const;`
- L100 _private prototype_ `bool SetupWorkspace();` — Core functions
- L102 _private member_ `FCriticalSection CriticalSection;`
- L105 _private member_ `FSpawnTabArgs TabArgs;` — Slate Data
- L106 _private member_ `TSharedRef<SDockTab> TabWidget;`
- L107 _private member_ `TSharedRef<SEmptyTab> EmptyTabView;`
- L108 _private member_ `TSharedRef<SGameSyncTab> GameSyncTabView;`
- L111 _private member_ `UGSTabManager* TabManager = nullptr;` — Core data
- L112 _private member_ `FString ProjectFileName;`
- L113 _private member_ `TSharedPtr<UGSCore::FWorkspace> Workspace;`
- L114 _private member_ `TSharedPtr<UGSCore::FPerforceConnection> PerforceClient;`
- L115 _private member_ `TSharedPtr<UGSCore::FUserWorkspaceSettings> WorkspaceSettings;`
- L116 _private member_ `TSharedPtr<UGSCore::FUserProjectSettings> ProjectSettings;`
- L117 _private member_ `TSharedPtr<UGSCore::FDetectProjectSettingsTask> DetectSettings;`
- L118 _private member_ `TArray<FString> CombinedSyncFilter;`
- L119 _private member_ `TSharedPtr<UGSCore::FUserSettings> UserSettings;`
- L120 _private member_ `TSharedPtr<FLogWidgetTextWriter> Log;`
- L123 _private member_ `TSharedPtr<UGSCore::FPerforceMonitor> PerforceMonitor;` — Monitoring threads
- L124 _private member_ `TSharedPtr<UGSCore::FEventMonitor> EventMonitor;`
- L127 _private member_ `TArray<TFunction<void()>> MessageQueue;` — Queue for handling callbacks from multiple threads that need to be called on the main thread
- L128 _private member_ `std::atomic<bool> bHasQueuedMessages;`
- L130 _private member_ `std::atomic<bool> bNeedUpdateGameTabBuildList;`
- L133 _private member_ `FProcHandle EditorProcessHandle;` — If we launch the editor, keep track of it to reap when its exited

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UGSCore`

### `Source/Programs/SlateUGS/Private/UGSTabManager.h` (Private)


#### class `UGSTabManager`  
`class UGSTabManager`  
_L14-41_
- L17 _public prototype_ `UGSTabManager();`
- L18 _public prototype_ `void ConstructTabs();`
- L20 _public prototype_ `void Tick();`
- L22 _public prototype_ `TSharedRef<SDockTab> SpawnTab(int Index, const FSpawnTabArgs& Args);`
- L23 _public prototype_ `void ActivateTab();`
- L24 _public prototype_ `FName GetTabId(int TabIndex) const;`
- L27 _public prototype_ `void SetupScheduledSync();` — Will setup a schedule sync, as well as tear down an existing one and make a new one
- L28 _public prototype_ `void StopScheduledSyncTimer();`
- L31 _private prototype_ `void StartScheduledSyncTimer();`
- L32 _private prototype_ `void ScheduleTimerElapsed();`
- L34 _private member_ `static constexpr int MaxTabs = 10;`
- L35 _private member_ `TStaticArray<UGSTab, MaxTabs> Tabs;`
- L37 _private member_ `TSharedPtr<UGSCore::FUserSettings> UserSettings;`
- L39 _private member_ `std::atomic<bool> bScheduledTimerElapsed;`
- L40 _private member_ `ScheduledSyncTimer SyncTimer;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UGSCore`

### `Source/Programs/SlateUGS/Private/Widgets/SEmptyTab.h` (Private)


#### class `SEmptyTab`  
`class SEmptyTab final : public SCompoundWidget`  
_L9-21_
- inherits: `SCompoundWidget`
- L12 _public function_ `SLATE_BEGIN_ARGS(SEmptyTab)`
- L13 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UGSTab* InTab);`
- L18 _private prototype_ `FReply OnOpenProjectClicked();`
- L20 _private member_ `UGSTab* Tab = nullptr;`

### `Source/Programs/SlateUGS/Private/Widgets/SGameSyncTab.h` (Private)


#### class `SBuildDataRow`  
`class SBuildDataRow final : public SMultiColumnTableRow<TSharedPtr<FChangeInfo>>`  
_L14-24_
- inherits: `SMultiColumnTableRow<TSharedPtr<FChangeInfo>>`
- L16 _private function_ `SLATE_BEGIN_ARGS(SBuildDataRow)`
- L17 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, const TSharedPtr<FChangeInfo>& Item);`
- L20 _private prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnId) override;`
- L23 _protected member_ `TSharedPtr<FChangeInfo> CurrentItem;`

#### class `SGameSyncTab`  
`class SGameSyncTab final : public SCompoundWidget`  
_L26-67_
- inherits: `SCompoundWidget`
- L29 _public function_ `SLATE_BEGIN_ARGS(SGameSyncTab)`
- L30 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UGSTab* InTab);`
- L36 _public prototype_ `TSharedPtr<SLogWidget> GetSyncLog() const;` — We need access to the SyncLog when creating the Workspace TODO: think of a better way to do this
- L37 _public prototype_ `bool SetSyncLogLocation(const FString& LogFileName);`
- L39 _public prototype_ `void SetStreamPathText(FText StreamPath);`
- L40 _public prototype_ `void SetChangelistText(int Changelist);`
- L41 _public prototype_ `void SetProjectPathText(FText ProjectPath);`
- L43 _public prototype_ `void AddHordeBuilds(const TArray<TSharedPtr<FChangeInfo>>& Builds);`
- L46 _private prototype_ `TSharedRef<ITableRow> GenerateHordeBuildTableRow(TSharedPtr<FChangeInfo> InItem, const TSharedRef<STableViewBase>& InOwnerTable);`
- L47 _private prototype_ `TSharedRef<SWidget> MakeSyncButtonDropdown();`
- L50 _private prototype_ `TSharedPtr<SWidget> OnRightClickedBuild();` — Widget callbacks
- L52 _private member_ `TSharedPtr<SListView<TSharedPtr<FChangeInfo>>> HordeBuildsView;`
- L53 _private member_ `TArray<TSharedPtr<FChangeInfo>> HordeBuilds;`
- L55 _private member_ `TSharedPtr<SLogWidget> SyncLog;`
- L57 _private member_ `TSharedPtr<STextBlock> StreamPathText;`
- L58 _private member_ `TSharedPtr<STextBlock> ChangelistText;`
- L59 _private member_ `TSharedPtr<STextBlock> ProjectPathText;`
- L60 _private member_ `TSharedPtr<STextBlock> SyncProgressText;`
- L62 _private member_ `static constexpr float HordeBuildRowHorizontalPadding = 10.0f;`
- L63 _private member_ `static constexpr float HordeBuildRowVerticalPadding = 2.5f;`
- L64 _private member_ `static constexpr float HordeBuildRowExtraIconPadding = 10.0f;`
- L66 _private member_ `UGSTab* Tab = nullptr;`

### `Source/Programs/SlateUGS/Private/Widgets/SHordeBadge.h` (Private)


#### enum `EBadgeState`  
`enum class EBadgeState`  
_L8-16_
- L10 _public enumerator_ `Unknown`
- L12 _public enumerator_ `Error`
- L13 _public enumerator_ `Warning`
- L14 _public enumerator_ `Success`
- L15 _public enumerator_ `Pending`

#### class `SHordeBadge`  
`class SHordeBadge : public SButton`  
_L18-39_
- inherits: `SButton`
- L21 _public function_ `SLATE_BEGIN_ARGS(SHordeBadge) : _BadgeState(EBadgeState::Unknown)`
- L26 _public prototype_ `SLATE_ATTRIBUTE(FText, Text) SLATE_ATTRIBUTE(EBadgeState, BadgeState) SLATE_EVENT(FOnClicked, OnClicked) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The text to display in the button.

### `Source/Programs/SlateUGS/Private/Widgets/SLogWidget.h` (Private)


#### class `FLogWidgetTextLayoutMarshaller`  
`class FLogWidgetTextLayoutMarshaller : public FBaseTextLayoutMarshaller`  
_L11-28_
- inherits: `FBaseTextLayoutMarshaller`
- L14 _public prototype_ `FLogWidgetTextLayoutMarshaller();`
- L15 _public prototype_ `virtual ~FLogWidgetTextLayoutMarshaller();`
- L18 _public prototype_ `virtual void SetText(const FString& SourceString, FTextLayout& TargetTextLayout) override;` — ITextLayoutMarshaller
- L19 _public prototype_ `virtual void GetText(FString& TargetString, const FTextLayout& SourceTextLayout) override;`
- L21 _public prototype_ `void Clear();`
- L22 _public prototype_ `void AppendLine(const FString& Line);`
- L23 _public prototype_ `int32 GetNumLines() const;`
- L26 _private member_ `TArray<TSharedRef<FString>> Lines;`
- L27 _private member_ `FTextLayout* TextLayout;`

#### class `SLogWidget`  
`class SLogWidget : public SCompoundWidget`  
_L30-59_
- inherits: `SCompoundWidget`
- L33 _public function_ `SLATE_BEGIN_ARGS(SLogWidget)`
- L36 _public prototype_ `SLogWidget();`
- L37 _public prototype_ `~SLogWidget();`
- L39 _public prototype_ `void Construct( const FArguments& InArgs );`
- L41 _public prototype_ `bool OpenFile(const TCHAR* NewLogFileName);`
- L42 _public prototype_ `void CloseFile();`
- L44 _public prototype_ `void Clear();`
- L45 _public prototype_ `void ScrollToEnd();`
- L46 _public prototype_ `void AppendLine(const FString& Line);`
- L49 _protected member_ `FString LogFileName;`
- L50 _protected member_ `FCriticalSection CriticalSection;`
- L51 _protected member_ `TArray<FString> QueuedLines;`
- L52 _protected member_ `TSharedPtr<FLogWidgetTextLayoutMarshaller> MessagesTextMarshaller;`
- L53 _protected member_ `TSharedPtr<SMultiLineEditableTextBox> MessagesTextBox;`
- L54 _protected member_ `bool bIsUserScrolled;`
- L55 _protected member_ `FArchive* LogWriter;`
- L57 _protected prototype_ `void OnScroll(float ScrollOffset);`
- L58 _protected prototype_ `EActiveTimerReturnType OnTimerElapsed(double CurrentTime, float DeltaTime);`

#### class `FLogWidgetTextWriter`  
`class FLogWidgetTextWriter : public UGSCore::FLineBasedTextWriter`  
_L61-76_
- inherits: `UGSCore::FLineBasedTextWriter`
- L64 _public function_ `FLogWidgetTextWriter(const TSharedRef<SLogWidget>& InLogWidget) : LogWidget(InLogWidget)`
- L69 _public function_ `virtual void FlushLine(const FString& Line) override`
- L75 _private member_ `TSharedRef<SLogWidget> LogWidget;`

### `Source/Programs/SlateUGS/Private/Widgets/SModalTaskWindow.h` (Private)


#### class `SModalTaskWindow`  
`class SModalTaskWindow : public SWindow, private FRunnable`  
_L16-40_
- inherits: `SWindow,FRunnable`
- L19 _public function_ `SLATE_BEGIN_ARGS(SModalTaskWindow)`
- L20 _public prototype_ `SLATE_ARGUMENT(FText, Title) SLATE_ARGUMENT(FText, Message) SLATE_ARGUMENT(TSharedPtr<UGSCore::IModalTask>, Task) SLATE_END_ARGS() TSharedPtr<UGSCore::FModalTaskResult> Result;`
- L27 _public prototype_ `SModalTaskWindow();`
- L28 _public prototype_ `~SModalTaskWindow();`
- L30 _public prototype_ `void Construct(const FArguments& InArgs);`
- L31 _public prototype_ `EActiveTimerReturnType OnTickTimer(double CurrentTime, float DeltaTime);`
- L34 _private member_ `FEvent* AbortEvent;`
- L35 _private member_ `FEvent* CloseEvent;`
- L36 _private member_ `FRunnableThread* Thread;`
- L37 _private member_ `TSharedPtr<UGSCore::IModalTask> Task;`
- L39 _private prototype_ `virtual uint32 Run() override;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UGSCore`
- L42 _prototype_ `TSharedRef<UGSCore::FModalTaskResult> ExecuteModalTask(TSharedPtr<SWidget> Parent, TSharedRef<UGSCore::IModalTask> Task, const FText& InTitle, const FText& InMessage);`

### `Source/Programs/SlateUGS/Private/Widgets/SNewWorkspaceWindow.h` (Private)


#### class `SNewWorkspaceWindow`  
`class SNewWorkspaceWindow final : public SWindow`  
_L11-36_
- inherits: `SWindow`
- L14 _public function_ `SLATE_BEGIN_ARGS(SNewWorkspaceWindow)`
- L15 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<SWorkspaceWindow> InParent, UGSTab* InTab);`
- L20 _private prototype_ `FReply OnBrowseStreamClicked();`
- L21 _private prototype_ `FReply OnBrowseRootDirectoryClicked();`
- L23 _private prototype_ `FReply OnCreateClicked();`
- L24 _private prototype_ `FReply OnCancelClicked();`
- L26 _private prototype_ `bool IsCreateButtonEnabled() const;`
- L28 _private member_ `TSharedPtr<SEditableTextBox> StreamTextBox = nullptr;`
- L29 _private member_ `TSharedPtr<SEditableTextBox> RootDirTextBox = nullptr;`
- L30 _private member_ `TSharedPtr<SEditableTextBox> WorkspaceNameTextBox = nullptr;`
- L31 _private member_ `FString RootDirPreviousFolder;`
- L33 _private member_ `TSharedPtr<SWorkspaceWindow> Parent = nullptr;`
- L35 _private member_ `UGSTab* Tab = nullptr;`

### `Source/Programs/SlateUGS/Private/Widgets/SPopupTextWindow.h` (Private)


#### class `SPopupTextWindow`  
`class SPopupTextWindow : public SWindow`  
_L8-22_
- inherits: `SWindow`
- L11 _public function_ `SLATE_BEGIN_ARGS(SPopupTextWindow) : _BodyTextJustification(ETextJustify::Center) , _ShowScrollBars(false)`
- L15 _public prototype_ `SLATE_ARGUMENT(FText, TitleText) SLATE_ARGUMENT(FText, BodyText) SLATE_ARGUMENT(ETextJustify::Type, BodyTextJustification) SLATE_ARGUMENT(bool, ShowScrollBars) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`

### `Source/Programs/SlateUGS/Private/Widgets/SScheduledSyncWindow.h` (Private)


#### class `SScheduledSyncWindow`  
`class SScheduledSyncWindow final : public SWindow`  
_L15-45_
- inherits: `SWindow`
- L18 _public function_ `SLATE_BEGIN_ARGS(SScheduledSyncWindow)`
- L19 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UGSTab* InTab);`
- L25 _private prototype_ `FSlateColor HandleTextBoxForegroundColor() const;` — Handles getting the text color of the editable text box.
- L28 _private prototype_ `FText HandleTextBoxText() const;` — Handles getting the text to be displayed in the editable text box.
- L31 _private prototype_ `void HandleTextBoxTextCommited(const FText& NewText, ETextCommit::Type CommitInfo);` — Handles committing the text in the editable text box.
- L34 _private prototype_ `void HandleScheduleSyncChanged(ECheckBoxState InCheck);` — Handle the check box enable or disabling Schedule Sync
- L35 _private prototype_ `ECheckBoxState HandleGetScheduleSyncChecked() const;`
- L37 _private prototype_ `FReply OnOkClicked();`
- L38 _private prototype_ `FReply OnCancelClicked();`
- L40 _private member_ `bool bInputValid = false;`
- L41 _private member_ `FString Input;`
- L43 _private member_ `UGSTab* Tab = nullptr;`
- L44 _private member_ `TSharedPtr<UGSCore::FUserSettings> UserSettings;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UGSCore`

### `Source/Programs/SlateUGS/Private/Widgets/SSelectStreamWindow.h` (Private)


#### class `SSelectStreamWindow`  
`class SSelectStreamWindow final : public SWindow`  
_L11-36_
- inherits: `SWindow`
- L14 _public function_ `SLATE_BEGIN_ARGS(SSelectStreamWindow)`
- L15 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UGSTab* InTab, FString* OutSelectedStreamPath);`
- L20 _private member_ `TSharedPtr<SEditableTextBox> FilterText;`
- L21 _private member_ `TSharedPtr<FStreamNode> SelectedStream;`
- L22 _private member_ `FString* SelectedStreamPath = nullptr;`
- L24 _private member_ `TArray<TSharedRef<FStreamNode>> StreamsTree;`
- L25 _private prototype_ `void PopulateStreamsTree();`
- L26 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedRef<FStreamNode> InItem, const TSharedRef<STableViewBase>& InOwnerTable);`
- L27 _private prototype_ `void OnGetChildren(TSharedRef<FStreamNode> InItem, TArray<TSharedRef<FStreamNode>>& OutChildren);`
- L28 _private prototype_ `void OnSelectionChanged(TSharedPtr<FStreamNode> NewSelection, ESelectInfo::Type SelectInfo);`
- L30 _private prototype_ `FReply OnOkClicked();`
- L31 _private prototype_ `FReply OnCancelClicked();`
- L33 _private prototype_ `bool IsOkButtonEnabled() const;`
- L35 _private member_ `UGSTab* Tab = nullptr;`

### `Source/Programs/SlateUGS/Private/Widgets/SSettingsWindow.h` (Private)


#### class `SSettingsWindow`  
`class SSettingsWindow final: public SWindow`  
_L16-43_
- inherits: `SWindow`
- L19 _public function_ `SLATE_BEGIN_ARGS(SSettingsWindow)`
- L20 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UGSTab* InTab);`
- L26 _private prototype_ `void HandleBuildChanged(ECheckBoxState InCheck);` — Handle the check box enable or disabling for AfterSync settings
- L27 _private prototype_ `ECheckBoxState HandleGetBuildChecked() const;`
- L29 _private prototype_ `void HandleRunChanged(ECheckBoxState InCheck);`
- L30 _private prototype_ `ECheckBoxState HandleGetRunChecked() const;`
- L32 _private prototype_ `void HandleOpenSolutionChanged(ECheckBoxState InCheck);`
- L33 _private prototype_ `ECheckBoxState HandleGetOpenSolutionChecked() const;`
- L35 _private prototype_ `void HandleSyncCompiledEditor(ECheckBoxState InCheck);`
- L36 _private prototype_ `ECheckBoxState HandleGetSyncCompiledEditor() const;`
- L38 _private prototype_ `FReply OnOkClicked();`
- L39 _private prototype_ `FReply OnCancelClicked();`
- L41 _private member_ `UGSTab* Tab = nullptr;`
- L42 _private member_ `TSharedPtr<UGSCore::FUserSettings> UserSettings;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UGSCore`

### `Source/Programs/SlateUGS/Private/Widgets/SSyncFilterWindow.h` (Private)


#### class `SSyncFilterWindow`  
`class SSyncFilterWindow final : public SWindow`  
_L14-40_
- inherits: `SWindow`
- L17 _public function_ `SLATE_BEGIN_ARGS(SSyncFilterWindow)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UGSTab* InTab);`
- L23 _private prototype_ `FReply OnShowCombinedFilterClicked();`
- L24 _private prototype_ `FReply OnCustomViewSyntaxClicked();`
- L25 _private prototype_ `FReply OnSaveClicked();`
- L26 _private prototype_ `FReply OnCancelClicked();`
- L28 _private prototype_ `void ConstructSyncFilters();`
- L29 _private prototype_ `void ConstructCustomSyncViewTextBoxes();`
- L31 _private member_ `UGSTab* Tab = nullptr;`
- L32 _private member_ `TArray<UGSCore::FWorkspaceSyncCategory> WorkspaceCategoriesCurrent;`
- L33 _private member_ `TArray<UGSCore::FWorkspaceSyncCategory> WorkspaceCategoriesAll;`
- L35 _private member_ `TSharedPtr<SCheckBoxList> SyncFiltersCurrent;`
- L36 _private member_ `TSharedPtr<SCheckBoxList> SyncFiltersAll;`
- L37 _private member_ `TSharedPtr<SMultiLineEditableTextBox> CustomSyncViewCurrent;`
- L38 _private member_ `TSharedPtr<SMultiLineEditableTextBox> CustomSyncViewAll;`

### `Source/Programs/SlateUGS/Private/Widgets/SWorkspaceWindow.h` (Private)


#### class `SWorkspaceWindow`  
`class SWorkspaceWindow final : public SWindow`  
_L10-36_
- inherits: `SWindow`
- L13 _public function_ `SLATE_BEGIN_ARGS(SWorkspaceWindow)`
- L14 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UGSTab* InTab);`
- L18 _public prototype_ `void SetWorkspaceTextBox(FText Text) const;`
- L21 _private prototype_ `FReply OnOkClicked();`
- L22 _private prototype_ `FReply OnCancelClicked();`
- L24 _private prototype_ `FReply OnBrowseClicked();`
- L25 _private member_ `FString PreviousProjectPath;`
- L27 _private prototype_ `FReply OnNewClicked();`
- L29 _private member_ `bool bIsLocalFileSelected = true;`
- L30 _private member_ `TSharedPtr<SEditableTextBox> LocalFileTextBox = nullptr;`
- L31 _private member_ `FString WorkspacePathText;`
- L33 _private member_ `TSharedPtr<SEditableTextBox> WorkspaceNameTextBox = nullptr;`
- L35 _private member_ `UGSTab* Tab = nullptr;`

### `Source/Programs/SlateUGS/Public/SlateUGS.h` (Public)
_(no declarations extracted)_

### `Source/Programs/SlateUGS/Public/SlateUGSApp.h` (Public)


#### Free symbols / members of external scopes

- L11 _prototype_ `int RunSlateUGS(const TCHAR* Commandline);` — Run the SlateUGS .
