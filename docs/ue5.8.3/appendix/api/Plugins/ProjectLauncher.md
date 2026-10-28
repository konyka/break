# Plugins / ProjectLauncher

- module root: `Plugins/Developer/ProjectLauncher/Source/ProjectLauncher`
- headers: 33; symbols: 1251
- symbol kinds: class=50, delegate=19, enum=11, enumerator=44, externvar=6, function=112, macro=23, member=321, namespace=25, prototype=605, struct=15, typedef=20

### `Plugins/Developer/ProjectLauncher/Source/ProjectLauncher/Private/Styling/ProjectLauncherStyle.h` (Private)


#### class `FProjectLauncherStyle`  
`class FProjectLauncherStyle`  
_L15-40_
- L18 _public prototype_ `static void Initialize();`
- L19 _public prototype_ `static void Shutdown();`
- L21 _public prototype_ `static const ISlateStyle& Get();`
- L22 _public prototype_ `static const FName& GetStyleSetName();`
- L23 _public function_ `static const FSlateBrush* GetBrush(FName PropertyName, const ANSICHAR* Specifier = nullptr)`
- L28 _public prototype_ `static const FSlateBrush* GetBrushForTask(ILauncherTaskPtr Task);`
- L29 _public prototype_ `static const FSlateBrush* GetProfileBrushForPlatform(const PlatformInfo::FTargetPlatformInfo* PlatformInfo, EPlatformIconSize IconSize);`
- L30 _public prototype_ `static const FSlateBrush* GetProfileBrushForPlatforms(TArray<const PlatformInfo::FTargetPlatformInfo*> PlatformInfos, EPlatformIconSize IconSize);`
- L32 _public function_ `static const FSegmentedProgressBarStyle& GetProgressBarStyle()`
- L38 _private member_ `static TSharedPtr<FSlateStyleSet> StyleSet;`
- L39 _private member_ `static FSegmentedProgressBarStyle ProgressBarStyle;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace PlatformInfo`

### `Plugins/Developer/ProjectLauncher/Source/ProjectLauncher/Private/Widgets/Output/CustomLaunchOutputLogMarshaller.h` (Private)


#### enum `ProjectLauncher::ELogFilter`  
`enum class ELogFilter : uint8`  
_L19-24_
- L21 _public enumerator_ `All`
- L22 _public enumerator_ `WarningsAndErrors`
- L23 _public enumerator_ `Errors`

#### class `ProjectLauncher::FLaunchLogTextLayoutMarshaller`  
`class FLaunchLogTextLayoutMarshaller : public FBaseTextLayoutMarshaller`  
_L28-64_
- inherits: `FBaseTextLayoutMarshaller`
- desc: this class is responsible for marshalling the output log from FModel into an associated multiline text box
- L31 _public prototype_ `FLaunchLogTextLayoutMarshaller(const TSharedRef<ProjectLauncher::FModel>& InModel);`
- L32 _public prototype_ `virtual void SetText(const FString& SourceString, FTextLayout& TargetTextLayout) override;`
- L33 _public prototype_ `virtual void GetText(FString& TargetString, const FTextLayout& SourceTextLayout) override;`
- L34 _public prototype_ `virtual void MakeDirty() override;`
- L36 _public function_ `ELogFilter GetFilter() const`
- L37 _public prototype_ `void SetFilter( ELogFilter InLogFilter );`
- L39 _public function_ `FString GetFilterString() const`
- L40 _public prototype_ `void SetFilterString( const FString& InLogFilterString );`
- L42 _public prototype_ `void AddPendingLogMessage( TSharedPtr<FLaunchLogMessage> Message );`
- L43 _public prototype_ `bool FlushPendingLogMessages();`
- L45 _public prototype_ `void RefreshAllLogMessages();`
- L46 _public function_ `int32 GetNumFilteredMessages() const`
- L48 _protected prototype_ `TArray<TSharedRef<class IRun>> GetRun(TSharedPtr<FLaunchLogMessage> Message);`
- L49 _protected prototype_ `bool ParseUATCommand( const TCHAR*& CommandLinePtr, FTextRange& TextRange ) const;`
- L51 _protected member_ `FTextBlockStyle MessageStyle;`
- L52 _protected member_ `FTextBlockStyle WarningStyle;`
- L53 _protected member_ `FTextBlockStyle ErrorStyle;`
- L54 _protected member_ `TArray<FTextBlockStyle> DisplayStyles;`
- L56 _protected member_ `const TSharedRef<ProjectLauncher::FModel> Model;`
- L57 _protected member_ `TSpscQueue<TSharedPtr<FLaunchLogMessage>> PendingMessages;`
- L58 _protected member_ `ELogFilter LogFilter = ELogFilter::All;`
- L59 _protected member_ `FString LogFilterString;`
- L60 _protected member_ `FTextLayout* TextLayout;`
- L61 _protected member_ `int32 NumFilteredMessages = 0;`
- L62 _protected member_ `int32 DisplayStyleIndex = 0;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace ProjectLauncher`

### `Plugins/Developer/ProjectLauncher/Source/ProjectLauncher/Private/Widgets/Output/SCustomLaunchLaunchPanel.h` (Private)


#### class `SCustomLaunchLaunchPanel`  
`class SCustomLaunchLaunchPanel : public SCompoundWidget`  
_L20-71_
- inherits: `SCompoundWidget`
- L24 _public function_ `SLATE_BEGIN_ARGS(SCustomLaunchLaunchPanel)`
- L30 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<ProjectLauncher::FModel>& InModel);`
- L31 _public prototype_ `void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;`
- L34 _public prototype_ `void SetLauncherWorker( const ILauncherWorkerRef& Worker );`
- L35 _public prototype_ `void ClearLog();`
- L38 _private prototype_ `bool IsBuilding() const;`
- L39 _private prototype_ `bool IsIdle() const;`
- L40 _private prototype_ `const FSlateBrush* GetProfileImage() const;`
- L41 _private prototype_ `FText GetProfileName() const;`
- L42 _private prototype_ `FText GetProfileDescription() const;`
- L43 _private prototype_ `FText GetProfileProjectName() const;`
- L44 _private prototype_ `FText GetProfileConfigurationName() const;`
- L45 _private prototype_ `FText GetProfileTargetName() const;`
- L46 _private prototype_ `FText GetProfileContentSchemeName() const;`
- L47 _private prototype_ `FText GetCurrentTaskDescription() const;`
- L48 _private prototype_ `FText GetProgressDescription() const;`
- L49 _private prototype_ `FText GetTotalDurationDescription() const;`
- L50 _private prototype_ `TOptional<float> GetProgressPercent() const;`
- L51 _private prototype_ `SSegmentedProgressBar::EState GetSegmentedProgressBarState(ILauncherTaskPtr Task) const;`
- L52 _private prototype_ `FReply OnCancelButtonClicked();`
- L53 _private prototype_ `FReply OnRetryButtonClicked();`
- L54 _private prototype_ `FReply OnDoneButtonClicked();`
- L56 _private prototype_ `ILauncherProfilePtr GetLauncherProfile() const;`
- L58 _private prototype_ `void HandleOutputReceived(const FString& InMessage);`
- L60 _private member_ `FOnClicked OnCloseClicked;`
- L61 _private member_ `FOnClicked OnRerunClicked;`
- L63 _private member_ `TWeakPtr<ILauncherWorker> LauncherWorker;`
- L64 _private member_ `TArray<ILauncherTaskPtr> TaskList;`
- L66 _private member_ `TSharedPtr<ProjectLauncher::FLaunchLogTextLayoutMarshaller> LaunchLogTextMarshaller;`
- L67 _private member_ `TSharedPtr<SCustomLaunchOutputLog> OutputLog;`
- L68 _private member_ `TSharedPtr<SSegmentedProgressBar> SubwayProgressBar;`
- L70 _private member_ `TSharedPtr<ProjectLauncher::FModel> Model;`

### `Plugins/Developer/ProjectLauncher/Source/ProjectLauncher/Private/Widgets/Output/SCustomLaunchOutputLog.h` (Private)


#### class `SCustomLaunchOutputLog`  
`class SCustomLaunchOutputLog : public SCompoundWidget`  
_L15-62_
- inherits: `SCompoundWidget`
- L19 _public function_ `SLATE_BEGIN_ARGS(SCustomLaunchOutputLog)`
- L23 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<ProjectLauncher::FModel>& InModel, const TSharedRef<ProjectLauncher::FLaunchLogTextLayoutMarshaller>& InLaunchLogTextMarshaller);`
- L25 _public prototype_ `void CopyLog();`
- L26 _public prototype_ `void SaveLog();`
- L27 _public prototype_ `void ClearLog();`
- L28 _public prototype_ `FString GetLogAsString( bool bSelectedLinesOnly = false ) const;`
- L30 _public prototype_ `void RefreshLog();`
- L32 _public prototype_ `void RequestForceScroll( bool bIfUserHasNotScrolledUp = false );`
- L34 _public prototype_ `TSharedRef<SWidget> CreateFilterWidget();`
- L37 _private prototype_ `TSharedRef<SWidget> MakeFilterMenu();`
- L38 _private prototype_ `FReply OnSaveClicked();`
- L39 _private prototype_ `FReply OnClearClicked();`
- L40 _private prototype_ `FReply OnCopyClicked();`
- L42 _private prototype_ `void OnFilterTextChanged(const FText& FilterText);`
- L43 _private prototype_ `void OnFilterTextCommitted(const FText& InFilterText, ETextCommit::Type InCommitType);`
- L44 _private prototype_ `void OnFilterChanged(ProjectLauncher::ELogFilter Filter);`
- L45 _private prototype_ `void OnWordWrapToggle();`
- L46 _private prototype_ `void OnSearchBoxFiltersLogToggle();`
- L47 _private prototype_ `void OnUserScrolled(float ScrollOffset);`
- L48 _private prototype_ `void ExtendTextBoxMenu(class FMenuBuilder& Builder);`
- L50 _private member_ `TSharedPtr<SMultiLineEditableTextBox> LogMessageTextBox;`
- L51 _private member_ `TSharedPtr<SButton> SaveButton;`
- L52 _private member_ `TSharedPtr<SButton> ClearButton;`
- L53 _private member_ `TSharedPtr<SButton> CopyButton;`
- L56 _private member_ `bool bIsUserScrolled = false;`
- L57 _private member_ `bool bWordWrap = false;`
- L58 _private member_ `bool bSearchBoxFiltersLog = true;`
- L59 _private member_ `FText CurrentFilterText;`
- L60 _private member_ `TSharedPtr<ProjectLauncher::FLaunchLogTextLayoutMarshaller> LaunchLogTextMarshaller;`
- L61 _private member_ `TSharedPtr<ProjectLauncher::FModel> Model;`

### `Plugins/Developer/ProjectLauncher/Source/ProjectLauncher/Private/Widgets/Profiles/SCustomLaunchCustomProfileEditor.h` (Private)


#### class `SCustomLaunchCustomProfileEditor`  
`class SCustomLaunchCustomProfileEditor : public SCompoundWidget, public IScrollableWidget`  
_L28-96_
- inherits: `SCompoundWidget,IScrollableWidget`
- L31 _public function_ `SLATE_BEGIN_ARGS(SCustomLaunchCustomProfileEditor)`
- L35 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<ProjectLauncher::FModel>& InModel);`
- L37 _public prototype_ `void SetProfile( const ILauncherProfilePtr& Profile );`
- L38 _public function_ `ILauncherProfilePtr GetProfile() const`
- L40 _public prototype_ `TSharedRef<SWidget> MakeCommandsMenu();`
- L42 _public prototype_ `void RebuildTree();`
- L43 _public function_ `TSharedRef<SLaunchProfileTreeView> GetTreeView() const`
- L46 _public prototype_ `virtual FVector2D GetScrollDistance() override;` — IScrollableWidget interface
- L47 _public prototype_ `virtual FVector2D GetScrollDistanceRemaining() override;`
- L48 _public prototype_ `virtual TSharedRef<SWidget> GetScrollWidget() override;`
- L51 _private prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L53 _private prototype_ `TSharedRef<ITableRow> OnGenerateWidgetForTreeNode( ProjectLauncher::FLaunchProfileTreeNodePtr TreeNode, const TSharedRef<STableViewBase>& OwnerTable, bool bPinned );`
- L54 _private prototype_ `void OnGetChildren(ProjectLauncher::FLaunchProfileTreeNodePtr TreeNode, TArray<ProjectLauncher::FLaunchProfileTreeNodePtr>& OutChildren);`
- L56 _private prototype_ `void CacheCollapsedRecursive( TSet<FString>& Collapsed, const FString& NodeName, ProjectLauncher::FLaunchProfileTreeNodePtr Node) const;`
- L57 _private prototype_ `void ApplyCollapsedRecusive( const TSet<FString>& Collapsed, const FString& NodeName, ProjectLauncher::FLaunchProfileTreeNodePtr Node) const;`
- L58 _private prototype_ `void ReorderNodes(ProjectLauncher::FLaunchProfileTreeNodePtr SourceNode, ProjectLauncher::FLaunchProfileTreeNodePtr TargetNode, EItemDropZone DropZone);`
- L60 _private prototype_ `bool IsHierarchyVisible(ProjectLauncher::FLaunchProfileTreeNodePtr TreeNode) const;`
- L68 _private prototype_ `void MakeMenu( FMenuBuilder& MenuBuilder, EMenuType MenuType, ILauncherProfileBuildCookRunPtr BuildCookRun = nullptr );`
- L70 _private prototype_ `void MakeUATCommandSubMenu( FMenuBuilder& MenuBuilder, ILauncherProfileUATCommandRef UATCommand );`
- L71 _private prototype_ `void MakeExtensionMenu( FMenuBuilder& MenuBuilder, EMenuType MenuType, TSharedRef<ProjectLauncher::FLaunchExtension> Extension, ILauncherProfileBuildCookRunPtr BuildCookRun = nullptr );`
- L73 _private prototype_ `void MakeTreeNodeSubMenu( FMenuBuilder& MenuBuilder, ProjectLauncher::FLaunchProfileTreeNodePtr TreeNode);`
- L74 _private prototype_ `TSharedRef<SWidget> MakeTreeNodeSubMenuWidget(ProjectLauncher::FLaunchProfileTreeNodePtr TreeNode);`
- L76 _private prototype_ `TSharedPtr<ProjectLauncher::FLaunchExtensionInstance> GetExtensionForUATCommand(ILauncherProfileUATCommandRef UATCommand) const;`
- L77 _private prototype_ `FSlateIcon GetIconForUATCommand(ILauncherProfileUATCommandPtr UATCommand) const;`
- L79 _private member_ `ILauncherProfilePtr CurrentProfile;`
- L80 _private member_ `TSharedPtr<ProjectLauncher::FModel> Model;`
- L81 _private member_ `TSharedPtr<ProjectLauncher::ILaunchProfileTreeBuilder> TreeBuilder;`
- L82 _private member_ `TSharedPtr<SLaunchProfileTreeView> TreeView;`
- L83 _private member_ `TArray<TSharedRef<ProjectLauncher::FLaunchExtensionInstance>> PendingExtensionDeletes;`
- L84 _private member_ `TSet<FString> PendingCollapseHeadings;`
- L85 _private member_ `FString PendingNewHeadingAdded;`
- L87 _private member_ `float SplitterPos = 0.6f;`
- L90 _private prototype_ `void BeginRenameUATCommand( const ILauncherProfileUATCommandRef& UATCommand ) const;`
- L93 _private member_ `TMap<ILauncherProfilePtr,TSet<FString>> CachedCollapsedNodes;`
- L94 _private member_ `TMap<ILauncherProfileUATCommandPtr,TWeakPtr<class SInlineEditableTextBlock>> UATCommandNameFields;`

#### enum `SCustomLaunchCustomProfileEditor::EMenuType`  
`enum class EMenuType`  
_L62-67_
- L64 _public enumerator_ `ProfileExtensions`
- L65 _public enumerator_ `BuildCookRunExtensions`
- L66 _public enumerator_ `UATCommands`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace ProjectLauncher`
- L24 _typedef_ `typedef STreeView<ProjectLauncher::FLaunchProfileTreeNodePtr> SLaunchProfileTreeView;`
- L25 _typedef_ `typedef STableRow<ProjectLauncher::FLaunchProfileTreeNodePtr> SLaunchProfileTreeRow;`

### `Plugins/Developer/ProjectLauncher/Source/ProjectLauncher/Private/Widgets/Profiles/SCustomLaunchCustomProfileSelector.h` (Private)


#### class `SCustomLaunchCustomProfileSelector`  
`class SCustomLaunchCustomProfileSelector : public SCompoundWidget`  
_L18-94_
- inherits: `SCompoundWidget`
- L22 _public function_ `DECLARE_DELEGATE_OneParam(FSetProfileEditorVisible, bool) SLATE_BEGIN_ARGS(SCustomLaunchCustomProfileSelector)`
- L37 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<ProjectLauncher::FModel>& InModel);`
- L38 _public prototype_ `~SCustomLaunchCustomProfileSelector();`
- L40 _public prototype_ `void StartEditProfileName(ILauncherProfilePtr Profile);`
- L41 _public prototype_ `void StartEditProfileDescription(ILauncherProfilePtr Profile);`
- L44 _private typedef_ `typedef STableRow<TSharedPtr<ILauncherProfilePtr>> SLauncherTableRow;`
- L46 _private member_ `FOnClicked OnProfileAdd;`
- L47 _private member_ `ProjectLauncher::FOnProfileClicked OnProfileEdit;`
- L48 _private member_ `ProjectLauncher::FOnProfileClicked OnProfileDelete;`
- L49 _private member_ `ProjectLauncher::FOnProfileClicked OnProfileDuplicate;`
- L50 _private member_ `ProjectLauncher::FOnProfileClicked OnProfileRename;`
- L51 _private member_ `ProjectLauncher::FOnProfileClicked OnProfileEditDescription;`
- L52 _private member_ `ProjectLauncher::FOnProfileClicked OnProfileModified;`
- L53 _private member_ `FSetProfileEditorVisible ChangeProfileEditorVisibility;`
- L54 _private member_ `TAttribute<bool> EditPanelVisible;`
- L56 _private prototype_ `TSharedRef<ITableRow> GenerateCustomProfileRow(ILauncherProfilePtr Profile, const TSharedRef<STableViewBase>& OwnerTable);`
- L57 _private prototype_ `const FSlateBrush* GetProfileImage(ILauncherProfilePtr Profile) const;`
- L58 _private prototype_ `FSlateColor GetRowColor(TSharedRef<SLauncherTableRow> TableRow) const;`
- L60 _private prototype_ `void OnSelectionChanged( ILauncherProfilePtr Profile, ESelectInfo::Type SelectionMode );`
- L61 _private prototype_ `void OnProfileSelected( const ILauncherProfilePtr& NewProfile, const ILauncherProfilePtr& OldProfile);`
- L62 _private prototype_ `void OnCustomProfileAdded(const ILauncherProfileRef& AddedProfile);`
- L63 _private prototype_ `void OnCustomProfileRemoved(const ILauncherProfileRef& RemovedProfile);`
- L64 _private prototype_ `void OnCustomProfileEditClicked(ILauncherProfilePtr Profile);`
- L65 _private prototype_ `void OnCustomProfileDuplicateClicked(ILauncherProfilePtr Profile);`
- L66 _private prototype_ `void OnCustomProfileDeleteClicked(ILauncherProfilePtr Profile);`
- L67 _private prototype_ `void OnCustomProfileRenameClicked(ILauncherProfilePtr Profile);`
- L68 _private prototype_ `void OnCustomProfileEditDescriptionClicked(ILauncherProfilePtr Profile);`
- L69 _private prototype_ `FReply OnOpenDeviceManagerClicked();`
- L70 _private prototype_ `FReply OnEditProfileClicked(ILauncherProfilePtr Profile);`
- L71 _private prototype_ `FReply OnCloseEditorClicked();`
- L72 _private prototype_ `EVisibility GetInlineEditButtonVisibility(TSharedRef<SWidget> RowWidget, ILauncherProfilePtr Profile) const;`
- L73 _private prototype_ `EVisibility GetCloseEditorButtonVisibility(ILauncherProfilePtr Profile) const;`
- L74 _private prototype_ `ECheckBoxState GetCustomProfileEditCheckState(ILauncherProfilePtr Profile) const;`
- L76 _private prototype_ `void RefreshCustomProfileList();`
- L78 _private prototype_ `void SetSelectedDevices(const TArray<FString> DeviceIDs, ILauncherProfilePtr Profile );`
- L79 _private prototype_ `TArray<FString> GetSelectedDevices(const ILauncherProfilePtr Profile) const;`
- L81 _private prototype_ `TSharedPtr<SWidget> MakeContextMenu();`
- L82 _private prototype_ `void EditProfile(ILauncherProfilePtr Profile);`
- L84 _private prototype_ `void SetProfileName(const FText& NewText, ETextCommit::Type InTextCommit, ILauncherProfilePtr Profile);`
- L85 _private prototype_ `void SetProfileDescription(const FText& NewText, ETextCommit::Type InTextCommit, ILauncherProfilePtr Profile);`
- L87 _private member_ `TSharedPtr<SListView<ILauncherProfilePtr>> CustomProfileListView;`
- L89 _private member_ `TMap<ILauncherProfilePtr, TSharedPtr<SInlineEditableTextBlock>> NameEditTextBoxes;`
- L90 _private member_ `TMap<ILauncherProfilePtr, TSharedPtr<SInlineEditableTextBlock>> DescriptionEditTextBoxes;`
- L93 _private member_ `TSharedPtr<ProjectLauncher::FModel> Model;`

#### Free symbols / members of external scopes

- L22 _delegate_ `DECLARE_DELEGATE_OneParam(FSetProfileEditorVisible, bool) SLATE_BEGIN_ARGS(SCustomLaunchCustomProfileSelector) {} SLATE_EVENT(FOnClicked, OnProfileAdd) SLATE_EVENT(ProjectLauncher::FOnProfileClicked, OnProfileEdit) SLATE_EVENT(ProjectLauncher::FOnProfileClicked, OnProfileDuplicate) SLATE_EVENT(ProjectLauncher::FOnProfileClicked, OnProfileDelete) SLATE_EVENT(ProjectLauncher::FOnProfileClicked, OnProfileRename) SLATE_EVENT(ProjectLauncher::FOnProfileClicked, OnProfileEditDescription) SLATE_EVENT(ProjectLauncher::FOnProfileClicked, OnProfileModified) SLATE_EVENT(FSetProfileEditorVisible, ChangeProfileEditorVisibility) SLATE_ATTRIBUTE(bool, EditPanelVisible) SLATE_END_ARGS() public: void Construct(const FArguments& InArgs, const TSharedRef<ProjectLauncher::FModel>& InModel);`

### `Plugins/Developer/ProjectLauncher/Source/ProjectLauncher/Private/Widgets/Profiles/SCustomLaunchProfilesPanel.h` (Private)


#### class `SCustomLaunchProfilesPanel`  
`class SCustomLaunchProfilesPanel : public SCompoundWidget`  
_L15-90_
- inherits: `SCompoundWidget`
- L18 _public function_ `SLATE_BEGIN_ARGS(SCustomLaunchProfilesPanel)`
- L23 _public prototype_ `SCustomLaunchProfilesPanel();`
- L24 _public prototype_ `~SCustomLaunchProfilesPanel();`
- L27 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<ProjectLauncher::FModel>& InModel);`
- L29 _public prototype_ `void OnProfileLaunchComplete();`
- L32 _private prototype_ `TSharedRef<SWidget> CreateProfilesPanel();`
- L34 _private prototype_ `TSharedRef<SWidget> CreateProfileSelectorWidget();`
- L35 _private prototype_ `TSharedRef<SWidget> CreateProfileEditorWidget();`
- L36 _private prototype_ `TSharedRef<SWidget> CreateAdvancedProfileWarningWidget();`
- L37 _private prototype_ `TSharedRef<SWidget> CreateProfileEditorToolbarWidget();`
- L39 _private prototype_ `EVisibility GetExtensionsBarVisibility() const;`
- L41 _private prototype_ `void OnProfileEdit(const ILauncherProfilePtr& Profile);`
- L42 _private prototype_ `void OnProfileDelete(const ILauncherProfilePtr& Profile);`
- L43 _private prototype_ `void OnProfileSave(const ILauncherProfilePtr& Profile);`
- L44 _private prototype_ `void OnProfileDuplicate(const ILauncherProfilePtr& Profile);`
- L45 _private prototype_ `void OnProfileRename(const ILauncherProfilePtr& Profile);`
- L46 _private prototype_ `void OnProfileEditDescription(const ILauncherProfilePtr& Profile);`
- L47 _private prototype_ `void OnProfileSelected(const ILauncherProfilePtr& NewProfile, const ILauncherProfilePtr& OldProfile);`
- L48 _private prototype_ `void OnProfileModified(const ILauncherProfilePtr& Profile);`
- L50 _private prototype_ `void OnLogAreaExpansionChanged( bool bExpanded );`
- L52 _private prototype_ `FReply OnLaunchButtonClicked();`
- L53 _private prototype_ `bool IsLaunchButtonEnabled() const;`
- L54 _private prototype_ `FText GetLaunchButtonToolTipText() const;`
- L55 _private prototype_ `const FSlateBrush* GetLaunchButtonImage() const;`
- L57 _private prototype_ `FReply OnCreateNewCustomProfileClicked();`
- L59 _private prototype_ `FReply OnOpenDeviceManagerClicked();`
- L61 _private prototype_ `const FSlateBrush* GetSelectedProfileImage() const;`
- L62 _private prototype_ `bool IsSelectedProfileReadOnly() const;`
- L64 _private prototype_ `FText GetSelectedProfileName() const;`
- L65 _private prototype_ `FText GetSelectedProfileDescription() const;`
- L67 _private prototype_ `void SetProfileEditorVisibleCheckState(const ECheckBoxState NewCheckState);`
- L68 _private prototype_ `ECheckBoxState GetProfileEditorVisibleCheckState() const;`
- L70 _private prototype_ `void SetProfileEditorVisible(bool bVisible);`
- L71 _private prototype_ `bool IsProfileEditorVisible() const;`
- L73 _private prototype_ `void SetDefaultProjectPath(FString ProjectPath);`
- L74 _private prototype_ `FString GetDefaultProjectPath() const;`
- L76 _private prototype_ `void SetDefaultBuildTarget(TArray<FString> BuildTarget);`
- L77 _private prototype_ `TArray<FString> GetDefaultBuildTarget() const;`
- L79 _private member_ `ProjectLauncher::FOnProfileClicked OnProfileLaunchClicked;`
- L80 _private member_ `TSharedPtr<ProjectLauncher::FModel> Model;`
- L82 _private member_ `TSharedPtr<SSplitter> LogAreaSplitter;`
- L83 _private member_ `TSharedPtr<SExpandableArea> LogExpandableArea;`
- L84 _private member_ `TSharedPtr<SSplitter> ProfileEditorSplitter;`
- L85 _private member_ `TSharedPtr<SCustomLaunchCustomProfileSelector> ProfileSelector;`
- L86 _private member_ `TSharedPtr<class SCustomLaunchCustomProfileEditor> PropertyEditor;`
- L87 _private member_ `TSharedPtr<class SCustomLaunchOutputLog> OutputLog;`

### `Plugins/Developer/ProjectLauncher/Source/ProjectLauncher/Private/Widgets/SProjectLauncher.h` (Private)


#### class `SProjectLauncher`  
`class SProjectLauncher : public SCompoundWidget`  
_L14-45_
- inherits: `SCompoundWidget`
- L17 _public function_ `SLATE_BEGIN_ARGS(SProjectLauncher)`
- L21 _public prototype_ `SProjectLauncher();`
- L22 _public prototype_ `~SProjectLauncher();`
- L25 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<ProjectLauncher::FModel>& InModel);`
- L28 _private prototype_ `void OnProfileRun(const ILauncherProfilePtr& Profile);`
- L29 _private prototype_ `FReply OnProgressClose();`
- L30 _private prototype_ `FReply OnRerunClicked();`
- L32 _private member_ `ILauncherWorkerPtr LauncherWorker;`
- L33 _private member_ `ILauncherProfilePtr LauncherProfile;`
- L34 _private member_ `TSharedPtr<ProjectLauncher::FModel> Model;`
- L42 _private member_ `TSharedPtr<SWidgetSwitcher> LauncherPanelWidgetSwitcher;`
- L43 _private member_ `TSharedPtr<SCustomLaunchProfilesPanel> ProfileSelectorPanel;`
- L44 _private member_ `TSharedPtr<SCustomLaunchLaunchPanel> LaunchProgressPanel;`

#### enum `SProjectLauncher::EPanel`  
`enum EPanel`  
_L36-40_
- L38 _public enumerator_ `Panel_Profiles = 0`
- L39 _public enumerator_ `Panel_Progress = 1`

### `Plugins/Developer/ProjectLauncher/Source/ProjectLauncher/Public/Extension/AutomatedTestLaunchExtension.h` (Public)


#### class `ProjectLauncher::FAutomatedTestLaunchExtensionInstance`  
`class FAutomatedTestLaunchExtensionInstance : public FUATCommandLaunchExtensionInstanceBase`  
_L16-39_
- inherits: `FUATCommandLaunchExtensionInstanceBase`
- desc: Helper base class for an automated test launch extension Creates an item in the extension menu that will toggle the test on and off note: It is not necessary for an automated test extensions to use this class
- L19 _public prototype_ `FAutomatedTestLaunchExtensionInstance( FArgs& InArgs );`
- L22 _protected prototype_ `virtual void OnAdded() override;`
- L23 _protected prototype_ `virtual void OnRemoved() override;`
- L28 _protected prototype_ `virtual void OnTestAdded( ILauncherProfileAutomatedTestRef InAutomatedTest ) = 0;` — Hook to allow any modification of the automated test & profile once it has been created. At least the test name should be specified
- L33 _protected function_ `virtual void OnTestRemoved( ILauncherProfileAutomatedTestRef InAutomatedTest )` — Advanced hook to allow any modification of the profile just before the automated test is removed
- L38 _protected prototype_ `ILauncherProfileAutomatedTestPtr GetTest() const;` — Access this extension's automated test if it has been created

#### class `ProjectLauncher::FAutomatedTestLaunchExtension`  
`class FAutomatedTestLaunchExtension : public FUATCommandLaunchExtensionBase`  
_L42-50_
- inherits: `FUATCommandLaunchExtensionBase`
- L45 _public prototype_ `virtual void GetExtensionsMenuEntry( FExtensionsMenuEntry& MenuEntry ) const override;`
- L46 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L49 _protected prototype_ `virtual ILauncherProfileUATCommandRef CreateUATCommand(ILauncherProfileRef InProfile, TSharedRef<FModel> InModel) const override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API PROJECTLAUNCHER_API`
- L9 _namespace_ `namespace ProjectLauncher`

### `Plugins/Developer/ProjectLauncher/Source/ProjectLauncher/Public/Extension/BuildCookRunCommandExtension.h` (Public)


#### class `ProjectLauncher::FBuildCookRunExtension`  
`class FBuildCookRunExtension : public TSharedFromThis<FBuildCookRunExtension>`  
_L14-188_
- inherits: `TSharedFromThis<FBuildCookRunExtension>`
- desc: Base for a launch extension for an ILauncherProfileBuildCookRun
- L17 _public typedef_ `typedef FLaunchExtensionInstance::EConfig EConfig;`
- L30 _public prototype_ `FBuildCookRunExtension( const FArgs& InArgs );`
- L31 _public prototype_ `virtual ~FBuildCookRunExtension();`
- L37 _public function_ `virtual void CustomizeTree( FLaunchProfileTreeNode& ProfileTreeNode )` — Hook to allow the extension to add extra fields to the property editing tree, if the tree builder allows it Property tree items should be hidden until the user has selected something to make it relevent, to avoid cluttering the UI.
- L42 _public prototype_ `FLaunchProfileTreeNode& AddDefaultHeading(FLaunchProfileTreeNode& ProfileTreeNode) const;` — Create the default heading for this extension
- L49 _public function_ `virtual void CustomizeUATCommandLine( FString& InOutCommandLine )` — Advanced hook to allow any advanced modification of the command line when a UAT command test is launched
- L54 _public function_ `void OnPropertyChanged()` — Notification callback when a property has been changed in our profile
- L59 _public function_ `virtual void OnProjectChanged()` — Notification callback when the project has been changed in our profile
- L64 _public function_ `virtual void OnValidate()` — Notification callback when the profile is validated
- L69 _public function_ `inline TSharedRef<FLaunchExtension> GetExtension() const` — Get the extension we belong to
- L74 _public function_ `inline TSharedRef<FLaunchExtensionInstance> GetExtensionInstance() const` — Get the extension instance that instantiated us
- L80 _protected function_ `inline ILauncherProfileRef GetProfile() const` — Get the profile we were instantiated for
- L85 _protected function_ `inline ILauncherProfileBuildCookRunRef GetBuildCookRun() const` — Get the BuildCookRun we were instantiated for
- L90 _protected function_ `inline ILauncherProfileBuildCookRunRef GetDefaultBuildCookRun() const` — Get the reference default BuildCookRun
- L95 _protected function_ `inline TSharedRef<FModel> GetModel() const` — Get the model, for general purpose helper functions
- L106 _protected prototype_ `FString GetConfigString(EConfig Config, const TCHAR* Name, const TCHAR* DefaultValue = TEXT("")) const;` — Read a configuration string value @param Config where the value is stored @param Name name of the value to read @param DefaultValue value to return if the value isn't found @returns the value of the property, or DefaultValue if it isn't found
- L116 _protected prototype_ `bool GetConfigBool(EConfig Config, const TCHAR* Name, bool DefaultValue = false) const;` — Read a configuration bool value @param Config where the value is stored @param Name name of the value to read @param DefaultValue value to return if the value isn't found @returns the value of the property, or DefaultValue if it isn't found
- L126 _protected prototype_ `int32 GetConfigInteger(EConfig Config, const TCHAR* Name, int32 DefaultValue = 0) const;` — Read a configuration int value @param Config where the value is stored @param Name name of the value to read @param DefaultValue value to return if the value isn't found @returns the value of the property, or DefaultValue if it isn't found
- L136 _protected prototype_ `float GetConfigFloat(EConfig Config, const TCHAR* Name, float DefaultValue = 0.0f) const;` — Read a configuration float value @param Config where the value is stored @param Name name of the value to read @param DefaultValue value to return if the value isn't found @returns the value of the property, or DefaultValue if it isn't found
- L145 _protected prototype_ `void SetConfigString(EConfig Config, const TCHAR* Name, const FString& Value) const;` — Write a configuration string value @param Config where the value is stored @param Name name of the value to write @param Value value to write
- L154 _protected prototype_ `void SetConfigBool(EConfig Config, const TCHAR* Name, const bool& Value) const;` — Write a configuration bool value @param Config where the value is stored @param Name name of the value to write @param Value value to write
- L163 _protected prototype_ `void SetConfigInteger(EConfig Config, const TCHAR* Name, const int32& Value) const;` — Write a configuration int value @param Config where the value is stored @param Name name of the value to write @param Value value to write
- L172 _protected prototype_ `void SetConfigFloat(EConfig Config, const TCHAR* Name, const float& Value) const;` — Write a configuration float value @param Config where the value is stored @param Name name of the value to write @param Value value to write
- L175 _private prototype_ `void OnUATCommandValidation( ILauncherProfileUATCommandRef UATCommand );`
- L176 _private prototype_ `FString GetConfigKeyName(const TCHAR* Name) const;`
- L178 _private member_ `ILauncherProfileRef Profile;`
- L179 _private member_ `ILauncherProfileBuildCookRunRef BuildCookRun;`
- L180 _private member_ `ILauncherProfileBuildCookRunRef DefaultBuildCookRun;`
- L181 _private member_ `TSharedRef<FModel> Model;`
- L182 _private member_ `TSharedRef<FLaunchExtension> Extension;`
- L183 _private member_ `TSharedRef<FLaunchExtensionInstance> ExtensionInstance;`
- L184 _private member_ `FLaunchProfileTreeData& OwnerTreeData;`
- L185 _private member_ `FPropertyChangedDelegate PropertyChangedDelegate;`

#### struct `ProjectLauncher::FBuildCookRunExtension::FArgs`  
`struct FArgs`  
_L19-28_
- L21 _public member_ `ILauncherProfileRef Profile;`
- L22 _public member_ `ILauncherProfileBuildCookRunRef BuildCookRun;`
- L23 _public member_ `ILauncherProfileBuildCookRunRef DefaultBuildCookRun;`
- L24 _public member_ `TSharedRef<FModel> Model;`
- L25 _public member_ `TSharedRef<FLaunchExtension> Extension;`
- L26 _public member_ `TSharedRef<FLaunchExtensionInstance> ExtensionInstance;`
- L27 _public member_ `FLaunchProfileTreeData& OwnerTreeData;`

#### class `ProjectLauncher::IBuildCookRunExtensionFactory`  
`class IBuildCookRunExtensionFactory`  
_L194-223_
- desc: Interface for creating & maintaining build cook run extensions
- L201 _public prototype_ `virtual TSharedRef<FBuildCookRunExtension> CreateBuildCookRunExtension( const FBuildCookRunExtension::FArgs& InArgs ) = 0;` — A launch extension must override this to create a new build cook run extension
- L206 _public prototype_ `virtual bool HasActiveBuildCookRunExtension() const = 0;` — Returns whether there are any active build cook run extensions from this launch extension
- L211 _public prototype_ `virtual void CustomizeBuildCookRunExtensionMenu( FMenuBuilder& InMenuBuilder, const ILauncherProfileBuildCookRunRef& InBuildCookRun ) = 0;` — Customizes the build cook run extensions menu to allow extenions to be enabled & disabled
- L217 _protected prototype_ `virtual bool IsBuildCookRunExtensionEnabledByDefault( const ILauncherProfileBuildCookRunRef& InBuildCookRun ) const = 0;` — Returns whether build cook run extensions should be enabled by default. Typically false
- L222 _protected prototype_ `virtual bool CanToggleBuildCookRunExtension( const ILauncherProfileBuildCookRunRef& InBuildCookRun, bool bWantToEnable ) const = 0;` — Returns whether our build cook run extensions can be toggled on or off. Typically true

#### class `ProjectLauncher::FBuildCookRunCommandExtensionInstance`  
`class FBuildCookRunCommandExtensionInstance : public FLaunchExtensionInstance, public IBuildCookRunExtensionFactory`  
_L228-275_
- inherits: `FLaunchExtensionInstance,IBuildCookRunExtensionFactory`
- L232 _public prototype_ `FBuildCookRunCommandExtensionInstance( FArgs& InArgs);`
- L233 _public prototype_ `virtual ~FBuildCookRunCommandExtensionInstance();`
- L235 _public prototype_ `virtual void InternalInitialize() override;`
- L238 _public function_ `virtual IBuildCookRunExtensionFactory* AsBuildCookRunFactory() override`
- L240 _public prototype_ `bool HasActiveBuildCookRunExtension() const override;`
- L242 _public prototype_ `void CustomizeBuildCookRunExtensionMenu( FMenuBuilder& InMenuBuilder, const ILauncherProfileBuildCookRunRef& InBuildCookRun ) override;`
- L244 _public prototype_ `virtual TSharedRef<FBuildCookRunExtension> CreateBuildCookRunExtension( const FBuildCookRunExtension::FArgs& InArgs ) = 0;`
- L246 _public prototype_ `virtual void CustomizeTree( FLaunchProfileTreeData& ProfileTreeData );`
- L247 _public prototype_ `virtual void OnPropertyChanged() override;`
- L250 _public function_ `virtual bool CanBeRemoved() const override final` — fixme: ideally enumerate FLaunchExtension to find those that are BCR
- L262 _protected prototype_ `FString GetConfigKeyName( const TCHAR* Name, const ILauncherProfileBuildCookRunRef& BuildCookRun) const;` — Get the key name to use for reading & writing a configuration value for the given BuildCookRun, expected to be passed as Name to the GetConfigXXX/SetConfigXXX functions @param Config where the value is stored @param Name name of the value @param BuildCookRun the build cook run command @returns namespaced version of Name
- L264 _protected prototype_ `virtual bool IsBuildCookRunExtensionEnabledByDefault( const ILauncherProfileBuildCookRunRef& InBuildCookRun ) const override;`
- L265 _protected prototype_ `virtual bool CanToggleBuildCookRunExtension( const ILauncherProfileBuildCookRunRef& InBuildCookRun, bool bWantToEnable ) const override;`
- L266 _protected prototype_ `virtual bool CustomizeUATCommandLine( const ILauncherProfileUATCommandRef& InUATCommand, FString& InOutCommandLine ) override;`
- L268 _protected prototype_ `void OnUATCommandAdded(const ILauncherProfileUATCommandRef& UATCommand);`
- L269 _protected prototype_ `void OnUATCommandRemoved(const ILauncherProfileUATCommandRef& UATCommand);`
- L270 _protected prototype_ `TSharedRef<FBuildCookRunExtension> CreateBuildCookRunExtensionInternal( const ILauncherProfileBuildCookRunRef& InBuildCookRun );`
- L272 _protected member_ `TMap<ILauncherProfileUATCommandPtr,TSharedRef<FBuildCookRunExtension>> BuildCookRunExtensions;`

#### class `ProjectLauncher::FBuildCookRunCommandExtension`  
`class FBuildCookRunCommandExtension : public FLaunchExtension`  
_L279-283_
- inherits: `FLaunchExtension`
- L282 _public function_ `virtual bool IsAlwaysCreated( ILauncherProfileRef InProfile, TSharedRef<FModel> InModel ) const override`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API PROJECTLAUNCHER_API`
- L9 _namespace_ `namespace ProjectLauncher`

### `Plugins/Developer/ProjectLauncher/Source/ProjectLauncher/Public/Extension/BuildCookRunLaunchExtension.h` (Public)


#### class `ProjectLauncher::FBuildCookRunLaunchExtensionInstance`  
`class FBuildCookRunLaunchExtensionInstance : public FUATCommandLaunchExtensionInstanceBase`  
_L11-15_
- inherits: `FUATCommandLaunchExtensionInstanceBase`
- L14 _public prototype_ `FBuildCookRunLaunchExtensionInstance( FArgs& InArgs );`

#### class `ProjectLauncher::FBuildCookRunLaunchExtension`  
`class FBuildCookRunLaunchExtension : public FUATCommandLaunchExtensionBase`  
_L17-30_
- inherits: `FUATCommandLaunchExtensionBase`
- L20 _public prototype_ `virtual void GetExtensionsMenuEntry( FExtensionsMenuEntry& MenuEntry ) const override;`
- L21 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L22 _public prototype_ `virtual const TCHAR* GetInternalName() const override;`
- L23 _public prototype_ `virtual FText GetDisplayName() const override;`
- L25 _public prototype_ `virtual TSharedPtr<ProjectLauncher::FLaunchExtensionInstance> CreateInstanceForProfile( ProjectLauncher::FLaunchExtensionInstance::FArgs& InArgs ) override;`
- L26 _public prototype_ `virtual bool CanBeCreated( ILauncherProfileRef InProfile, TSharedRef<FModel> InModel ) const override;`
- L29 _protected prototype_ `virtual ILauncherProfileUATCommandRef CreateUATCommand(ILauncherProfileRef InProfile, TSharedRef<FModel> InModel) const override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API PROJECTLAUNCHER_API`
- L9 _namespace_ `namespace ProjectLauncher`

### `Plugins/Developer/ProjectLauncher/Source/ProjectLauncher/Public/Extension/CmdLineParametersExtension.h` (Public)


#### class `ProjectLauncher::FCmdLineParametersExtension`  
`class FCmdLineParametersExtension : public TSharedFromThis<FCmdLineParametersExtension>`  
_L23-89_
- inherits: `TSharedFromThis<FCmdLineParametersExtension>`
- desc: Base for a command line extension
- L35 _public prototype_ `FCmdLineParametersExtension( const FArgs& InArgs );`
- L36 _public prototype_ `virtual ~FCmdLineParametersExtension();`
- L41 _public function_ `inline TSharedRef<FLaunchExtension> GetExtension() const` — Get the extension we belong to
- L46 _public function_ `inline TSharedRef<FLaunchExtensionInstance> GetExtensionInstance() const` — Get the extension instance that instantiated us
- L52 _protected function_ `virtual void CustomizeParametersSubmenu( FMenuBuilder& MenuBuilder )` — Hook to allow the extension to extend the extension parameters menu
- L57 _protected function_ `virtual void OnProjectChanged()` — Notification callback when the project has been changed in our profile
- L62 _protected function_ `inline ILauncherProfileRef GetProfile() const` — Get the profile we were instantiated for
- L67 _protected function_ `inline TSharedRef<FModel> GetModel() const` — Get the model, for general purpose helper functions
- L72 _protected prototype_ `void SetCommandLine( const FString& InCommandLine );` — Update the command line
- L77 _protected prototype_ `FString GetCommandLine() const;` — Get the current command line
- L80 _private member_ `ILauncherProfileRef Profile;`
- L81 _private member_ `TSharedRef<FModel> Model;`
- L82 _private member_ `TSharedRef<FLaunchExtension> Extension;`
- L83 _private member_ `TSharedRef<FLaunchExtensionInstance> ExtensionInstance;`
- L84 _private member_ `FLaunchProfileTreeNode::FSetString SetCommandLineDelegate;`
- L85 _private member_ `FLaunchProfileTreeNode::FGetString GetCommandLineDelegate;`
- L86 _private member_ `FString TypeName;`

#### struct `ProjectLauncher::FCmdLineParametersExtension::FArgs`  
`struct FArgs`  
_L26-33_
- L28 _public member_ `TSharedRef<FModel> Model;`
- L29 _public member_ `TSharedRef<FLaunchExtensionInstance> ExtensionInstance;`
- L30 _public member_ `FLaunchProfileTreeNode::FSetString SetCommandLine;`
- L31 _public member_ `FLaunchProfileTreeNode::FGetString GetCommandLine;`
- L32 _public member_ `FString TypeName;`

#### class `ProjectLauncher::ICmdLineParametersExtensionFactory`  
`class ICmdLineParametersExtensionFactory`  
_L95-138_
- desc: Interface for creating & maintaining command line extensions
- L98 _public prototype_ `virtual ~ICmdLineParametersExtensionFactory() = default;`
- L103 _public prototype_ `virtual TSharedRef<FCmdLineParametersExtension> Create( const FCmdLineParametersExtension::FArgs& InArgs );` — Create an instance of a command line extension. A launch extension can override this to customize the command line menu
- L108 _public function_ `virtual FString GetCmdLineType() const` — Which commandline type the extension supports. Either a custom string or one of ProjectLauncher::CmdLineType::
- L113 _public prototype_ `virtual FText GetCmdLineParameterDisplayName( const FString& InParameter ) const;` — Returns the user-facing name for the given parameter. It will default to the parameter itself.
- L118 _public prototype_ `virtual void GetCmdLineParameters( TArray<FString>& OutParameters ) const = 0;` — Returns the parameters that this extension provides. They will be added to the submenu.
- L124 _public function_ `virtual void GetDefaultCmdLineParameters( TArray<FString>& OutParameters ) const` — Returns the parameters that will be automatically added to the command line when this extension is enabled. Not available for 'always created' extensions
- L131 _public prototype_ `static void MakeCmdLineParametersSubmenu(FMenuBuilder& MenuBuilder, uint64 InstanceID, const FString& TypeName, TSharedRef<FModel> Model, TSharedRef<FLaunchExtensionInstance> Instance, const FLaunchProfileTreeNode::FSetString& SetValue, const FLaunchProfileTreeNode::FGetString& GetValue );` — Create the command line parameters menu for the given extension
- L136 _public prototype_ `static void DestroyCmdLineParametersExtensions(TSharedPtr<FLaunchExtensionInstance> Instance);` — Remove any command line extensions from the given launch extension

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PROJECTLAUNCHER_API`
- L10 _namespace_ `namespace ProjectLauncher`
- L13 _namespace_ `namespace CmdLineType` (scope `ProjectLauncher`)
- L15 _externvar_ `extern const TCHAR* Launch;` (scope `ProjectLauncher::CmdLineType`)
- L16 _externvar_ `extern const TCHAR* UAT;` (scope `ProjectLauncher::CmdLineType`)

### `Plugins/Developer/ProjectLauncher/Source/ProjectLauncher/Public/Extension/CustomUATCommandLaunchExtension.h` (Public)


#### class `ProjectLauncher::FCustomUATCommandLaunchExtensionInstance`  
`class FCustomUATCommandLaunchExtensionInstance : public FUATCommandLaunchExtensionInstanceBase`  
_L14-32_
- inherits: `FUATCommandLaunchExtensionInstanceBase`
- desc: Base class for an custom UAT command launch extension
- L17 _public prototype_ `FCustomUATCommandLaunchExtensionInstance( FArgs& InArgs );`
- L20 _protected prototype_ `virtual void OnAdded() override;`
- L21 _protected prototype_ `virtual void OnRemoved() override;`
- L26 _protected prototype_ `virtual void OnUATCommandAdded( ILauncherProfileUATCommandRef InUATCommand ) = 0;` — Hook to allow any modification of the UAT Command & profile once it has been created. At least the UAT Command name should be specified
- L31 _protected function_ `virtual void OnUATCommandRemoved( ILauncherProfileUATCommandRef InUATCommand )` — Advanced hook to allow any modification of the profile just before the UAT Command is removed

#### class `ProjectLauncher::FCustomUATCommandLaunchExtension`  
`class FCustomUATCommandLaunchExtension : public FUATCommandLaunchExtensionBase`  
_L36-43_
- inherits: `FUATCommandLaunchExtensionBase`
- L39 _public prototype_ `virtual void GetExtensionsMenuEntry( FExtensionsMenuEntry& MenuEntry ) const override;`
- L42 _protected prototype_ `virtual ILauncherProfileUATCommandRef CreateUATCommand(ILauncherProfileRef InProfile, TSharedRef<FModel> InModel) const override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API PROJECTLAUNCHER_API`
- L9 _namespace_ `namespace ProjectLauncher`

### `Plugins/Developer/ProjectLauncher/Source/ProjectLauncher/Public/Extension/LaunchExtension.h` (Public)


#### class `ProjectLauncher::FLaunchExtensionInstance`  
`class FLaunchExtensionInstance : public TSharedFromThis<FLaunchExtensionInstance>`  
_L31-378_
- inherits: `TSharedFromThis<FLaunchExtensionInstance>`
- desc: Base class for a launch extension instance. Used while editing a specific profile, and when finalizing the command line arguments during profile launch. Created by a specialization of FLaunchExtension as follows: TSharedPtr<ProjectLauncher:FLaunchExtensinInstance> FMyLaunchExtension::CreateInstanceForProfile( ProjectLauncher::FLaunchExtensionInstance::FArgs& InArgs ) { return MakeShared<FMyLaunchExtensionInstance>(InArgs); }
- L44 _public prototype_ `FLaunchExtensionInstance( FArgs& InArgs );`
- L45 _public prototype_ `virtual ~FLaunchExtensionInstance();`
- L51 _public prototype_ `virtual bool GetExtensionParameters( TArray<FString>& OutParameters ) const;` — `UE_DEPRECATED(5.8, "refactor code to use ICmdLineParametersExtension")` — Returns the parameters that this extension provides. They will be added to the submenu.
- L57 _public prototype_ `virtual FText GetExtensionParameterDisplayName( const FString& InParameter ) const;` — `UE_DEPRECATED(5.8, "refactor code to use ICmdLineParametersExtension")` — Returns the user-facing name for the given parameter. It will default to the parameter itself.
- L62 _public prototype_ `virtual bool GetExtensionVariables( TArray<FString>& OutVariables ) const;` — Returns the user facing variables that this extension provides, in "$(name)" format
- L67 _public prototype_ `virtual bool GetExtensionVariableValue( const FString& InParameter, FString& OutValue ) const;` — Returns the current value for the given variable
- L73 _public function_ `virtual void CustomizeParametersSubmenu( FMenuBuilder& MenuBuilder )` — `UE_DEPRECATED(5.8, "refactor code to use ICmdLineParametersExtension")` — Hook to allow the extension to extend the extension parameters menu
- L79 _public prototype_ `virtual void CustomizeTree( FLaunchProfileTreeData& ProfileTreeData );` — Hook to allow the extension to add extra fields to the property editing tree, if the tree builder allows it Property tree items should be hidden until the user has selected something to make it relevent, to avoid cluttering the UI.
- L84 _public function_ `virtual void CustomizeLaunchCommandLine( FString& InOutCommandLine )` — Advanced hook to allow any advanced modification of the command line when our profile is launched
- L89 _public function_ `virtual void CustomizeTargetLaunchCommandLine( FString& InOutCommandLine, EBuildTargetType InBuildTargetType )` — Advanced hook to allow any advanced modification of the command line when our profile is launched for the given build target type
- L94 _public prototype_ `virtual bool CustomizeUATCommandLine( const ILauncherProfileUATCommandRef& InUATCommand, FString& InOutCommandLine );` — Advanced hook to allow any advanced modification of the command line when a UAT command test is launched
- L99 _public prototype_ `virtual void OnPropertyChanged();` — Notification callback when a property has been changed in our profile
- L104 _public function_ `virtual void OnProjectChanged()` — Notification callback when the project has been changed in our profile
- L109 _public function_ `virtual void OnValidateProfile()` — Notification callback when the profile is validated
- L114 _public prototype_ `virtual FLaunchProfileTreeNode& AddDefaultHeading(ProjectLauncher::FLaunchProfileTreeData& ProfileTreeData) const;` — Create the default heading for this extension
- L120 _public function_ `virtual void MakeCustomExtensionSubmenu(FMenuBuilder& MenuBuilder)` — Populate the custom extension menu for this extension. This menu would typically contain items that might enable bespoke tree customization options for example.
- L125 _public function_ `virtual bool CanBeRemoved() const` — Whether the given extension can be removed or not
- L130 _public function_ `inline TSharedRef<FLaunchExtension> GetExtension() const` — Get the extension that instantiated us
- L135 _public function_ `inline ILauncherProfileRef GetProfile() const` — Get the profile we were instantiated for
- L140 _public function_ `inline ILauncherProfileRef GetDefaultProfile() const` — Get the reference default profile
- L145 _public function_ `inline TSharedRef<FModel> GetModel() const` — Get the model, for general purpose helper functions
- L150 _public function_ `inline FPropertyChangedDelegate& GetPropertyChangedDelegate()` — Get the property changed delegate that will be called when an extension changes the profile
- L155 _public function_ `virtual class IBuildCookRunExtensionFactory* AsBuildCookRunFactory()` — Attempt to cast this launch extension instance to a build cook run factory
- L160 _public function_ `virtual class ICmdLineParametersExtensionFactory* AsCmdLineParametersFactory()` — Attempt to cast this launch extension instance to a launch command line factory
- L165 _public function_ `virtual bool ManagesUATCommand( const ILauncherProfileUATCommandRef& UATCommand ) const` — Determine if this launch extension instance manages the given UAT command
- L170 _public function_ `virtual ILauncherProfileUATCommandPtr GetUATCommand() const` — Get the associated UAT command, if any
- L175 _public prototype_ `virtual void InternalInitialize();` — Internal intitialization function, called immediately after construction - don't call directly
- L181 _public prototype_ `void CustomizeTree();` — Internal property tree customization function - don't call directly
- L183 _public function_ `virtual void OnAdded()`
- L184 _public function_ `virtual void OnRemoved()`
- L189 _public prototype_ `virtual void BroadcastEvent(const FString& EventName, void* EventData = nullptr);` — Broadcast an event to all other extension instances associated to the same profile.
- L194 _public function_ `virtual void HandleEventCallback(const FString& EventName, void* EventData)` — The listener checks the incoming event name and chooses to handle the event accordingly.
- L199 _public prototype_ `static TArray<TSharedPtr<FLaunchExtensionInstance>> GetProfileExtensionInstancesByName(const FString& ExtensionName, ILauncherProfileRef InProfile);` — Search for the extension instances associated with the given profile by name
- L204 _protected prototype_ `bool IsParameterUsed( const FString& InParameter ) const;` — `UE_DEPRECATED(5.8, "Use ProjectLauncher::CmdLineUtils version")`
- L207 _protected prototype_ `void SetParameterUsed( const FString& InParameter, bool bUsed );` — `UE_DEPRECATED(5.8, "Use ProjectLauncher::CmdLineUtils version")`
- L210 _protected prototype_ `void AddParameter( const FString& InParameter );` — `UE_DEPRECATED(5.8, "Use ProjectLauncher::CmdLineUtils version")`
- L213 _protected prototype_ `void RemoveParameter( const FString& InParameter );` — `UE_DEPRECATED(5.8, "Use ProjectLauncher::CmdLineUtils version")`
- L216 _protected prototype_ `FString GetParameterValue( const FString& InParameter ) const;` — `UE_DEPRECATED(5.8, "Use ProjectLauncher::CmdLineUtils version")`
- L219 _protected prototype_ `bool UpdateParameterValue( const FString& InParameter, const FString& InNewValue );` — `UE_DEPRECATED(5.8, "Use ProjectLauncher::CmdLineUtils version")`
- L222 _protected prototype_ `FString GetFinalParameter( const FString& InParameter ) const;` — `UE_DEPRECATED(5.8, "Use ProjectLauncher::CmdLineUtils version")`
- L230 _protected prototype_ `FString GetCommandLine() const;` — `UE_DEPRECATED(5.8, "access the appropriate field from a BuildCookRun instance, or use ICmdLineParametersExtension")` — Get the current command line @returns the current command line string
- L238 _protected prototype_ `void SetCommandLine( const FString& CommandLine );` — `UE_DEPRECATED(5.8, "access the appropriate field from a BuildCookRun instance, or use ICmdLineParametersExtension")` — Update the current command line @param CommandLine the new command line
- L243 _protected function_ `inline FLaunchProfileTreeData& GetOwnerTreeData() const` — Get the owner tree data
- L250 _public prototype_ `FName GetLaunchPlatformName() const;` — Get the name of the platform to launch on. this is the highest priority platform/target in the list of platforms
- L270 _public prototype_ `FString GetConfigString( EConfig Config, const TCHAR* Name, const TCHAR* DefaultValue = TEXT("") ) const;` — Read a configuration string value @param Config where the value is stored @param Name name of the value to read @param DefaultValue value to return if the value isn't found @returns the value of the string, or DefaultValue if it isn't found
- L280 _public prototype_ `bool GetConfigBool( EConfig Config, const TCHAR* Name, bool DefaultValue = false ) const;` — Read a configuration bool value @param Config where the value is stored @param Name name of the value to read @param DefaultValue value to return if the value isn't found @returns the value of the bool, or DefaultValue if it isn't found
- L290 _public prototype_ `int32 GetConfigInteger( EConfig Config, const TCHAR* Name, int32 DefaultValue = 0 ) const;` — Read a configuration int value @param Config where the value is stored @param Name name of the value to read @param DefaultValue value to return if the value isn't found @returns the value of the bool, or DefaultValue if it isn't found
- L300 _public prototype_ `float GetConfigFloat( EConfig Config, const TCHAR* Name, float DefaultValue = 0.0f ) const;` — Read a configuration float value @param Config where the value is stored @param Name name of the value to read @param DefaultValue value to return if the value isn't found @returns the value of the bool, or DefaultValue if it isn't found
- L309 _public prototype_ `void SetConfigString( EConfig Config, const TCHAR* Name, const FString& Value ) const;` — Write a configuration string value @param Config where the value is stored @param Name name of the value to write @param Value value to write
- L318 _public prototype_ `void SetConfigBool( EConfig Config, const TCHAR* Name, const bool& Value ) const;` — Write a configuration bool value @param Config where the value is stored @param Name name of the value to write @param Value value to write
- L327 _public prototype_ `void SetConfigInteger( EConfig Config, const TCHAR* Name, const int32& Value ) const;` — Write a configuration int value @param Config where the value is stored @param Name name of the value to write @param Value value to write
- L336 _public prototype_ `void SetConfigFloat( EConfig Config, const TCHAR* Name, const float& Value ) const;` — Write a configuration float value @param Config where the value is stored @param Name name of the value to write @param Value value to write
- L348 _public prototype_ `FString GetConfigKeyName( EConfig Config, const TCHAR* Name ) const;` — Get the final key name to use for reading & writing a configuration value @param Config where the value is stored @param Name name of the value @returns namespaced version of Name
- L353 _public prototype_ `void BroadcastPropertyChanged() const;` — Signal to any listeners that a property in the profile has changed
- L359 _public prototype_ `void RequestTreeRefresh();` — Request that the property tree should be refreshed - such as when a widget has changed size
- L364 _public prototype_ `void RequestFullTreeRebuild();` — Request that the enture property tree is rebuilt - such as when adding or removing top-level sections
- L368 _private prototype_ `virtual void OnCustomValidation();`
- L370 _private prototype_ `virtual const TCHAR* GetInternalName() const;`
- L372 _private member_ `ILauncherProfileRef Profile;`
- L373 _private member_ `ILauncherProfileRef DefaultProfile;`
- L374 _private member_ `TSharedRef<FModel> Model;`
- L375 _private member_ `TSharedRef<FLaunchExtension> Extension;`
- L376 _private member_ `FLaunchProfileTreeData& OwnerTreeData;`
- L377 _private member_ `FPropertyChangedDelegate PropertyChangedDelegate;`

#### struct `ProjectLauncher::FLaunchExtensionInstance::FArgs`  
`struct FArgs`  
_L34-42_
- L36 _public member_ `ILauncherProfileRef Profile;`
- L37 _public member_ `ILauncherProfileRef DefaultProfile;`
- L38 _public member_ `TSharedRef<FModel> Model;`
- L39 _public member_ `TSharedRef<FLaunchExtension> Extension;`
- L40 _public member_ `FLaunchProfileTreeData& OwnerTreeData;`
- L41 _public member_ `ILauncherProfileUATCommandPtr UATCommand;`

#### enum `ProjectLauncher::FLaunchExtensionInstance::EConfig`  
`enum class EConfig : uint8`  
_L255-260_
- desc: Enumeration to choose where a value should be stored
- L257 _public enumerator_ `User_Common` — value is shared between all instances of this extension
- L258 _public enumerator_ `User_PerProfile` — value is specific to this profile & extension
- L259 _public enumerator_ `PerProfile` — value is saved with the profile

#### class `ProjectLauncher::FLaunchExtension`  
`class FLaunchExtension : public TSharedFromThis<FLaunchExtension>`  
_L393-513_
- inherits: `TSharedFromThis<FLaunchExtension>`
- desc: Base class for a launch extension. Singleton instance is registered with this plugin during initialization as follows: TSharedPtr<FMyLaunchExtension> MyExtension = MakeShared<FMyLaunchExtension>(); IProjectLauncherModule::Get().RegisterExtension( MyExtension.ToSharedRef() );
- L396 _public prototype_ `virtual ~FLaunchExtension() = default;`
- L401 _public prototype_ `virtual const TCHAR* GetInternalName() const = 0;` — Returns the debug name for this extension
- L406 _public prototype_ `virtual FText GetDisplayName() const = 0;` — Returns the user-facing name for this extension
- L411 _public prototype_ `virtual FSlateIcon GetIcon() const;` — Returns the icon to use for this extension in menus etc
- L416 _public function_ `virtual bool IsAlwaysCreated( ILauncherProfileRef InProfile, TSharedRef<FModel> InModel ) const` — Whether this extension is always created. the user cannot remove it
- L421 _public function_ `virtual bool IsCreatedByDefault( ILauncherProfileRef InProfile, TSharedRef<FModel> InModel ) const` — Whether this extension will be created by default. the user can still remove it
- L426 _public function_ `virtual bool IsUATCommandManager() const` — Whether this extension manages a UAT command
- L431 _public function_ `virtual bool CanBeCreated( ILauncherProfileRef InProfile, TSharedRef<FModel> InModel ) const` — Whether this extension can be created at this time
- L437 _public function_ `virtual class FBuildCookRunLaunchExtension* AsBuildCookRunLaunchExtension()` — Attempt to cast this launch extension to an BuildCookRun launch extension (this is an extension for a build cook run UAT command)
- L442 _public function_ `virtual class IUATCommandExtensionFactory* AsUATCommandFactory()` — Attempt to cast this launch extension instance to a UAT command factory
- L452 _public prototype_ `static TArray<TSharedPtr<FLaunchExtensionInstance>> CreateExtensionInstancesForProfile( ILauncherProfileRef InProfile, TSharedRef<FModel> InModel, FLaunchProfileTreeData& InOwnerTreeData );` — Instantiate all compatible extensions @param InProfile the current profile @param InModel helper class @param InOwnerTreeData the property tree data associated with the profile @returns array of all compatible extensions
- L454 _public prototype_ `static TSharedPtr<FLaunchExtensionInstance> CreateExtensionInstance( TSharedRef<FLaunchExtension> InExtension, ILauncherProfileRef InProfile, TSharedRef<FModel> InModel, FLaunchProfileTreeData& InOwnerTreeData, ILauncherProfileUATCommandPtr InUATCommand = nullptr );`
- L455 _public prototype_ `static void DestroyExtensionInstance(TSharedRef<FLaunchExtensionInstance> InExtensionInstance, ILauncherProfileRef InProfile, TSharedRef<FModel> InModel);`
- L457 _public prototype_ `static TSharedPtr<FLaunchExtensionInstance> GetExtensionInstance(TSharedRef<FLaunchExtension> InExtension, ILauncherProfileRef InProfile);`
- L458 _public prototype_ `static TArray<TSharedRef<FLaunchExtensionInstance>> GetExtensionInstances(TSharedRef<FLaunchExtension> InExtension, ILauncherProfileRef InProfile);`
- L460 _public prototype_ `static TArray<TSharedRef<FLaunchExtension>> GetExtensions();`
- L495 _public prototype_ `virtual void GetExtensionsMenuEntry( FExtensionsMenuEntry& MenuEntry ) const;`
- L497 _public function_ `virtual void MakeCustomExtensionSubmenu(FMenuBuilder& MenuBuilder, ILauncherProfileRef InProfile, TSharedRef<FModel> InModel)`
- L504 _public prototype_ `static void DestroyExtensionInstancesForProfile(ILauncherProfilePtr InProfile);` — Destroy all extension instances for the given profile @param InProfile the profile who's extension instances to return
- L512 _private prototype_ `virtual TSharedPtr<FLaunchExtensionInstance> CreateInstanceForProfile( FLaunchExtensionInstance::FArgs& InArgs ) = 0;` — Create an instance of the launch extension for the given profile - called internally by CreateExtensionInstancesForProfile @returns: new instance, or null if it isn't appropriate

#### struct `ProjectLauncher::FLaunchExtension::FExtensionsMenuEntry`  
`struct FExtensionsMenuEntry`  
_L466-494_
- desc: Describes how this extension is represented in the extensions menu
- L469 _public member_ `static const FExtensionsMenuEntry None;` — common menu locations
- L470 _public member_ `static const FExtensionsMenuEntry Default;`
- L471 _public member_ `static const FExtensionsMenuEntry OwnSection;`
- L472 _public member_ `static const FExtensionsMenuEntry Deprecated;`
- L473 _public member_ `static const FExtensionsMenuEntry AutomatedTests;`
- L474 _public member_ `static const FExtensionsMenuEntry UATCommands;`
- L477 _public member_ `FString SectionName;` — internal names
- L478 _public member_ `FString SubmenuName;`
- L481 _public member_ `FText SectionDisplayName;` — friendly names
- L482 _public member_ `FText SubmenuDisplayName;`
- L491 _public member_ `EType Type = Type_None;`
- L493 _public member_ `bool bIsDefault = false;` — default sections should be kept at the top

#### enum `ProjectLauncher::FLaunchExtension::FExtensionsMenuEntry::EType`  
`enum EType`  
_L485-490_
- desc: type of menu entry
- L487 _public enumerator_ `Type_None` — does not appear in the extensions menu
- L488 _public enumerator_ `Type_Section` — appears in the extensions menu in the common section.
- L489 _public enumerator_ `Type_SubMenu` — appears in the extensions menu in a submenu of the SectionName section

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API PROJECTLAUNCHER_API`
- L13 _namespace_ `namespace ProjectLauncher`
- L18 _typedef_ `typedef TMulticastDelegate<void()> FPropertyChangedDelegate;` (scope `ProjectLauncher`)

### `Plugins/Developer/ProjectLauncher/Source/ProjectLauncher/Public/Extension/UATCommandLaunchExtension.h` (Public)


#### class `ProjectLauncher::FUATCommandLaunchExtensionInstanceBase`  
`class FUATCommandLaunchExtensionInstanceBase : public FLaunchExtensionInstance`  
_L14-34_
- inherits: `FLaunchExtensionInstance`
- desc: Helper base class for an extension that is tied to a UAT command in the profile
- L17 _public prototype_ `FUATCommandLaunchExtensionInstanceBase( FArgs& InArgs );`
- L19 _public prototype_ `virtual bool ManagesUATCommand( const ILauncherProfileUATCommandRef& InUATCommand ) const override;`
- L20 _public prototype_ `virtual ILauncherProfileUATCommandPtr GetUATCommand() const override;`
- L25 _public function_ `virtual void CustomizeUATCommandLine( FString& InOutCommandLine )` — Advanced hook to allow any advanced modification of the command line when this extension's UAT Command is launched
- L28 _protected member_ `const ILauncherProfileUATCommandRef UATCommand;`
- L30 _protected prototype_ `virtual bool CustomizeUATCommandLine( const ILauncherProfileUATCommandRef& InUATCommand, FString& InOutCommandLine ) override;`
- L31 _protected prototype_ `virtual void OnCustomValidation() override;`
- L32 _protected prototype_ `virtual FLaunchProfileTreeNode& AddDefaultHeading(FLaunchProfileTreeData& ProfileTreeData) const override;`
- L33 _protected prototype_ `virtual const TCHAR* GetInternalName() const override;`

#### class `ProjectLauncher::IUATCommandExtensionFactory`  
`class IUATCommandExtensionFactory`  
_L39-47_
- desc: Interface for creating & maintaining UAT command extensions
- L42 _public prototype_ `virtual TSharedPtr<ProjectLauncher::FLaunchExtensionInstance> CreateUATCommandExtensionInstance(ILauncherProfileRef InProfile, TSharedRef<FModel> InModel, FLaunchProfileTreeData& InOwnerTreeData) = 0;`
- L45 _protected prototype_ `virtual ILauncherProfileUATCommandRef CreateUATCommand(ILauncherProfileRef InProfile, TSharedRef<FModel> InModel) const = 0;`

#### class `ProjectLauncher::FUATCommandLaunchExtensionBase`  
`class FUATCommandLaunchExtensionBase : public FLaunchExtension, public IUATCommandExtensionFactory`  
_L50-60_
- inherits: `FLaunchExtension,IUATCommandExtensionFactory`
- L53 _public function_ `virtual bool IsUATCommandManager() const`
- L55 _public function_ `virtual IUATCommandExtensionFactory* AsUATCommandFactory() override`
- L58 _protected prototype_ `virtual TSharedPtr<ProjectLauncher::FLaunchExtensionInstance> CreateUATCommandExtensionInstance(ILauncherProfileRef InProfile, TSharedRef<FModel> InModel, FLaunchProfileTreeData& InOwnerTreeData) override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API PROJECTLAUNCHER_API`
- L9 _namespace_ `namespace ProjectLauncher`

### `Plugins/Developer/ProjectLauncher/Source/ProjectLauncher/Public/Model/ProjectLauncherModel.h` (Public)


#### enum `ProjectLauncher::EContentScheme`  
`enum class EContentScheme : uint8`  
_L34-45_
- desc: Defines how content is stored and deployed for a profile
- L36 _public enumerator_ `PakFiles`
- L37 _public enumerator_ `ZenStreaming`
- L38 _public enumerator_ `ZenPakStreaming`
- L39 _public enumerator_ `DevelopmentPackage`
- L40 _public enumerator_ `SubmissionPackage`
- L41 _public enumerator_ `LooseFiles`
- L42 _public enumerator_ `CookOnTheFly`
- L43 _public enumerator_ `PreStagedBuild`
- L44 _public enumerator_ `MAX`

#### enum `ProjectLauncher::EProfileType`  
`enum class EProfileType : uint8`  
_L69-75_
- desc: Defines the type of a profile (basic, custom, or advanced)
- L71 _public enumerator_ `Invalid`
- L72 _public enumerator_ `Basic`
- L73 _public enumerator_ `Custom`
- L74 _public enumerator_ `Advanced`

#### struct `ProjectLauncher::FLaunchLogMessage`  
`struct FLaunchLogMessage`  
_L78-87_
- desc: Holds a single log message emitted during launch
- L80 _public member_ `TSharedRef<FString> Message;`
- L81 _public member_ `ELogVerbosity::Type Verbosity;`
- L83 _public function_ `FLaunchLogMessage(const FString& InMessage, ELogVerbosity::Type InVerbosity) : Message(MakeShared<FString>(InMessage)) , Verbosity(InVerbosity)`

#### struct `ProjectLauncher::FProjectSettings`  
`struct FProjectSettings`  
_L90-122_
- desc: Cache of project settings relevant for launch profiles
- L93 _public member_ `bool bIsCurrentEditorProject = false;` — whether this project is the one that is currently open in the editor
- L96 _public member_ `bool bUseZenStore = false;` — whether Zen Store is enabled via the project settings - in this case, we can't use Loose Files
- L99 _public member_ `bool bUseIoStore = false;` — whether Io Store is enabled via the project settings - we can only use zen workflows when this is enabled
- L102 _public member_ `bool bHasAutomaticZenPakStreamingWorkspaceCreation = false;` — whether a workspace will be created automatically when using Zen Pak streaming
- L105 _public member_ `bool bAllowRemoteNetworkService = false;` — whether Zen Server is allowed to accept connections from remote machines (i.e. console devkits, phones etc)
- L108 _public member_ `FString DefaultBuildTargetName;` — default build target names
- L109 _public member_ `FString DefaultServerTargetName;`
- L110 _public member_ `FString DefaultClientTargetName;`
- L111 _public member_ `FString DefaultEditorTargetName;`
- L114 _public member_ `FString FallbackDefaultBuildTarget;` — fallback "default" build target to use if none is specified
- L117 _public member_ `FConfigCacheIni* Config = nullptr;` — cached project config ini
- L120 _public member_ `FEvent* Pending = nullptr;` — whether this is still being initialized
- L121 _public member_ `bool bIsReady = false;`

#### class `ProjectLauncher::FModel`  
`class FModel : public TSharedFromThis<FModel>`  
_L149-390_
- inherits: `TSharedFromThis<FModel>`
- desc: This class contains a selection of helper functions and the current profile state
- L153 _public prototype_ `FModel(const TSharedRef<ITargetDeviceProxyManager>& InDeviceProxyManager, const TSharedRef<ILauncher>& InLauncher, const TSharedRef<ILauncherProfileManager>& InProfileManager);` — Constructor/destructor/one-time init
- L154 _public prototype_ `~FModel();`
- L155 _public prototype_ `void Init();`
- L158 _public function_ `const TSharedRef<ITargetDeviceProxyManager>& GetDeviceProxyManager() const` — Get the target device proxy manager
- L164 _public function_ `const TSharedRef<ILauncher>& GetLauncher() const` — Get the launcher instance
- L170 _public function_ `const TSharedRef<ILauncherProfileManager>& GetProfileManager() const` — Get the launcher profile manager
- L176 _public function_ `const TArray<ILauncherProfilePtr>& GetAllProfiles() const` — Get all known launcher profiles
- L182 _public function_ `ILauncherProfilePtr GetBasicLaunchProfile() const` — Get the basic launch profile
- L188 _public function_ `const ILauncherProfilePtr& GetSelectedProfile() const` — Get the currently selected profile
- L194 _public function_ `FOnSelectedProfileChanged& OnProfileSelected()` — Delegate fired when a profile is selected
- L200 _public prototype_ `void SelectProfile(const ILauncherProfilePtr& Profile);` — Change the selected profile
- L203 _public prototype_ `void SortProfiles();` — Sort all profiles alphabetically, keeping the basic profile first in the list
- L206 _public prototype_ `EProfileType GetProfileType(const ILauncherProfileRef& Profile) const;` — Get the type of a profile (basic, custom, advanced)
- L209 _public prototype_ `bool IsAdvancedProfile(const ILauncherProfileRef& Profile) const;` — Returns true if the given profile is advanced (multiple platforms/cultures, DLC, patches, etc)
- L212 _public prototype_ `bool IsBasicLaunchProfile(const ILauncherProfilePtr& Profile) const;` — Returns true if the given profile is the basic launch profile
- L215 _public prototype_ `ILauncherProfileRef CreateCustomProfile(const TCHAR* Name);` — Create a new custom profile with the given name
- L218 _public prototype_ `ILauncherProfileRef CreateBasicLaunchProfile();` — Create a new basic launch profile
- L221 _public prototype_ `ILauncherProfilePtr CloneCustomProfile(const ILauncherProfileRef& Profile);` — Clone an existing custom profile
- L224 _public prototype_ `const ILauncherProfileRef GetDefaultBasicLaunchProfile() const;` — Get the default basic launch profile - used for "reset to default"
- L227 _public prototype_ `const ILauncherProfileRef GetDefaultCustomLaunchProfile() const;` — Get the default custom launch profile - used for "reset to default"
- L230 _public prototype_ `const ILauncherProfileBuildCookRunRef GetBasicDefaultBuildCookRun() const;` — Get the default build cook run for the basic profile - used for "reset to default"
- L233 _public prototype_ `const ILauncherProfileBuildCookRunRef GetCustomDefaultBuildCookRun() const;` — Get the default build cook run for the custom profile - used for "reset to default"
- L237 _public prototype_ `EContentScheme DetermineProfileContentScheme(const ILauncherProfileBuildCookRunRef& BuildCookRun) const;` — Determine the content scheme for a profile
- L240 _public prototype_ `void SetProfileContentScheme(EContentScheme ContentScheme, const FProjectSettings& ProjectSettings, const ILauncherProfileBuildCookRunRef& BuildCookRun, bool bWantToCook = true, ELauncherProfileDeploymentModes::Type DefaultDeploymentMode = ELauncherProfileDeploymentModes::CopyToDevice);` — Apply a content scheme to a profile, setting cook/deploy/packaging options etc
- L245 _public prototype_ `TSharedPtr<FLaunchLogMessage> AddLogMessage(const FString& InMessage, ELogVerbosity::Type InVerbosity = ELogVerbosity::Log);` — Record a new log message from launching
- L248 _public prototype_ `void ClearLogMessages();` — Clear all log messages
- L251 _public function_ `int32 GetNumLogMessages() const` — Get number of log messages
- L258 _public prototype_ `static const PlatformInfo::FTargetPlatformInfo* GetPlatformInfo(const ILauncherProfilePtr& Profile);` — `UE_DEPRECATED(5.8, "Use GetPlatformInfos")` — Get platform info for a profile or platform name
- L259 _public prototype_ `static const PlatformInfo::FTargetPlatformInfo* GetPlatformInfo(FName PlatformName, const FTargetInfo& BuildTargetInfo);`
- L260 _public prototype_ `static TArray<const PlatformInfo::FTargetPlatformInfo*> GetPlatformInfos(const ILauncherProfileBuildCookRunRef& BuildCookRun);`
- L261 _public prototype_ `static TArray<const PlatformInfo::FTargetPlatformInfo*> GetPlatformInfosForAllCommands(const ILauncherProfilePtr& Profile);`
- L265 _public prototype_ `static bool IsHostPlatform(const ILauncherProfilePtr& Profile);` — `UE_DEPRECATED(5.8, "No longer in use. IsUsingRemotePlatform may be of use")` — Returns true if profile or platform name refers to host platform
- L266 _public prototype_ `static bool IsHostPlatform(FName PlatformName);`
- L267 _public prototype_ `static bool IsUsingRemotePlatform(const ILauncherProfileBuildCookRunRef& BuildCookRun);`
- L270 _public prototype_ `FTargetInfo GetBuildTargetInfo(FString BuildTargetName, const FString& ProjectPath);` — Get build target info for a project path or profile
- L272 _public prototype_ `FTargetInfo GetBuildTargetInfo(const ILauncherProfileRef& Profile);` — `UE_DEPRECATED(5.8, "Use GetBuildTargetInfos")`
- L273 _public prototype_ `TArray<FTargetInfo> GetBuildTargetInfos(const ILauncherProfileRef& Profile, const ILauncherProfileBuildCookRunRef& BuildCookRun);`
- L276 _public prototype_ `static TSharedPtr<ITargetDeviceProxy> GetDeviceProxy(const ILauncherProfileBuildCookRunRef& BuildCookRun);` — Get a device proxy for a profile
- L279 _public prototype_ `void UpdateDeployDeviceProxyFromCookedPlatforms(const ILauncherProfileRef& Profile);` — Update device proxies based on the current cook platforms
- L282 _public prototype_ `void UpdatedCookedPlatformsFromDeployDeviceProxy(const ILauncherProfileRef& Profile, const ILauncherProfileBuildCookRunRef& BuildCookRun, TSharedPtr<ITargetDeviceProxy> DeviceProxy = nullptr);` — Update cooked platforms based on selected device proxy
- L285 _public prototype_ `void UpdateCookedPlatformsFromBuildTarget(const ILauncherProfileRef& Profile, const ILauncherProfileBuildCookRunRef& BuildCookRun);` — Update cooked platforms based on build target
- L288 _public prototype_ `void EnsureValidBuildTarget(const ILauncherProfileRef& Profile, const ILauncherProfileBuildCookRunRef& BuildCookRun);` — Attempts to set a valid build target if one has not been specified
- L291 _public prototype_ `static FString GetVanillaPlatformName(const FString& PlatformName);` — Utility functions for resolving platform names
- L292 _public prototype_ `static FString GetPlatformNameWithFlavor(const FString& PlatformName);`
- L293 _public prototype_ `static FString GetBuildTargetPlatformName(const FString& PlatformName, const FTargetInfo& BuildTargetInfo);`
- L296 _public prototype_ `const FProjectSettings GetProjectSettings(const FString& ProjectPath, bool bWait = true);` — Retrieve project settings from a project path or profile
- L297 _public prototype_ `const FProjectSettings GetProjectSettings(const ILauncherProfileRef& Profile, bool bWait = true);`
- L298 _public prototype_ `bool AreProjectSettingsReady(const FString& ProjectPath);`
- L299 _public prototype_ `bool AreProjectSettingsReady(const ILauncherProfileRef& Profile);`
- L300 _public prototype_ `FString GetProjectPath(const ILauncherProfileRef& Profile) const;`
- L303 _public function_ `FOnProjectSettingsReady& OnProjectSettingsReady()` — Delegate fired when a project's settings have been loaded
- L310 _public prototype_ `const TCHAR* GetConfigSection() const;` — Get config section and ini file used for storing project launcher state
- L311 _public prototype_ `const FString& GetConfigIni() const;`
- L314 _public prototype_ `bool AreExtensionsEnabled() const;` — Returns true if extensions are enabled for project launcher
- L317 _public prototype_ `bool CanUseSimplifiedLayout(const ILauncherProfileRef& Profile);` — Returns true if we can use a simplified layout for this profile
- L320 _public prototype_ `TArray<FString> GetAvailableProjectMapNames(const FString& InProjectPath, bool bIncludeNonContentDirMaps = false);` — Get available maps for a project, engine, or plugin
- L321 _public prototype_ `TArray<FString> GetAvailableProjectMapPaths(const FString& InProjectPath, bool bIncludeNonContentDirMaps = false);`
- L322 _public prototype_ `TArray<FString> GetAvailableEngineMapNames();`
- L323 _public prototype_ `TArray<FString> GetAvailableEngineMapPaths();`
- L324 _public prototype_ `TArray<FString> GetAvailablePluginMapNames(const FString& PluginContentDir);`
- L325 _public prototype_ `TArray<FString> GetAvailablePluginMapPaths(const FString& PluginContentDir);`
- L334 _public prototype_ `void GetUATCommandsDetail( const ILauncherProfileRef& Profile, FUATCommandsDetail& OutUATCommandsDetail);`
- L337 _public prototype_ `void SetDefaults(const ILauncherProfileRef& Profile, const ILauncherProfileBuildCookRunRef& BuildCookRun);` — Set the defaults for this BuildCookRun
- L341 _private prototype_ `void LoadConfig();` — Load and save config state
- L342 _private prototype_ `void SaveConfig();`
- L345 _private prototype_ `void HandleProfileManagerProfileAdded(const ILauncherProfileRef& Profile);` — Handlers for profile manager and device proxy events
- L346 _private prototype_ `void HandleProfileManagerProfileRemoved(const ILauncherProfileRef& Profile);`
- L347 _private prototype_ `void HandleProfileManagerFallbackProjectChanged();`
- L348 _private prototype_ `void HandleDeviceProxyAdded(const TSharedRef<ITargetDeviceProxy>& DeviceProxy);`
- L349 _private prototype_ `void HandleDeviceProxyRemoved(const TSharedRef<ITargetDeviceProxy>& DeviceProxy);`
- L352 _private prototype_ `void HandleProfileProjectChanged( ILauncherProfilePtr InProfile );` — Handler for profile properties changing
- L353 _private prototype_ `void HandleProjectSettingsReady( const FString& ProjectPath );`
- L356 _private prototype_ `void ReadProjectSettingsFromConfig(FConfigCacheIni& InConfig, const FString& InProjectPath, FProjectSettings& OutResult);` — Helper for reading project settings from config
- L359 _private prototype_ `void OnModifyLaunchCommandLine( const ILauncherProfileRef& InProfile, EBuildTargetType InBuildTargetType, FString& InOutCommandLine );` — Modify launch command lines to inject extension variables
- L360 _private prototype_ `void OnModifyUATCommandLine( FUATCommandPostProcessParameters& PostProcessParameters );`
- L363 _private prototype_ `TArray<FString> GetAndCacheMapPaths(const FString& InContentDir, bool bIncludeNonContentDirMaps = false);` — Get map paths under a content directory, caching results
- L366 _private member_ `FString ConfigFileName;`
- L368 _private member_ `TSharedRef<ITargetDeviceProxyManager> DeviceProxyManager;`
- L369 _private member_ `TSharedRef<ILauncher> Launcher;`
- L370 _private member_ `TSharedRef<ILauncherProfileManager> ProfileManager;`
- L372 _private member_ `ILauncherProfilePtr SelectedProfile;`
- L373 _private member_ `TArray<ILauncherProfilePtr> AllProfiles;`
- L374 _private member_ `ILauncherProfilePtr BasicLaunchProfile;`
- L375 _private member_ `bool bHasSetBasicLaunchProfilePlatform = false;`
- L378 _private member_ `TArray<TSharedPtr<FLaunchLogMessage>> LaunchLogMessages;`
- L380 _private member_ `FCriticalSection CachedProjectSettingsCS;`
- L381 _private member_ `TMap<FString,FProjectSettings> CachedProjectSettings;`
- L382 _private member_ `TMap<FString,TArray<FString>> CachedMapPaths;`
- L384 _private member_ `FOnSelectedProfileChanged ProfileSelectedDelegate;`
- L385 _private member_ `FOnSelectedPlatformChanged PlatformChangedDelegate;`
- L386 _private member_ `FOnProjectSettingsReady ProjectSettingsReady;`
- L388 _private member_ `ILauncherProfilePtr DefaultBasicLaunchProfile;`
- L389 _private member_ `ILauncherProfilePtr DefaultCustomLaunchProfile;`

#### struct `ProjectLauncher::FModel::FUATCommandsDetail`  
`struct FUATCommandsDetail`  
_L328-333_
- desc: Get the current UAT command information for the given profile
- L330 _public member_ `int32 MinOrder = 0;`
- L331 _public member_ `int32 MaxOrder = 0;`
- L332 _public member_ `uint32 NumUATCommands = 0;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API PROJECTLAUNCHER_API`
- L18 _namespace_ `namespace PlatformInfo`
- L28 _namespace_ `namespace ProjectLauncher`
- L30 _externvar_ `extern const FText ProjectLauncherText;` (scope `ProjectLauncher`)
- L31 _externvar_ `extern bool bUseClassicView;` (scope `ProjectLauncher`)
- L48 _prototype_ `TArray<EContentScheme> GetAllContentSchemes();` (scope `ProjectLauncher`) — Returns all possible content schemes
- L51 _prototype_ `FText GetContentSchemeDisplayName(EContentScheme ContentScheme);` (scope `ProjectLauncher`) — Get user-visible display name for a content scheme
- L54 _prototype_ `FText GetContentSchemeToolTip(EContentScheme ContentScheme);` (scope `ProjectLauncher`) — Get tooltip text describing a content scheme
- L57 _prototype_ `FText GetProfileLaunchErrorMessage(ILauncherProfilePtr Profile, bool bWithAnnotations = false );` (scope `ProjectLauncher`) — Returns a launch error message for a given profile, optionally with annotations
- L60 _prototype_ `const TCHAR* LexToString( const ProjectLauncher::EContentScheme& ContentScheme);` (scope `ProjectLauncher`) — Convert a content scheme to string
- L63 _prototype_ `bool LexTryParseString( ProjectLauncher::EContentScheme& OutContentScheme, const TCHAR* String );` (scope `ProjectLauncher`) — Try to parse a string into a content scheme enum value
- L66 _prototype_ `bool GetUserConfirmation( const FText& Message, const FText& Title = ProjectLauncherText, bool bDefaultValue = true );` (scope `ProjectLauncher`) — Message box helper
- L126 _delegate_ `DECLARE_DELEGATE_OneParam(FOnProfileClicked, const ILauncherProfilePtr&) DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSelectedProfileChanged, const ILauncherProfilePtr& , const ILauncherProfilePtr& ) DECLARE_MULTICAST_DELEGATE_OneParam(FOnProjectSettingsReady, const FString& ) DECLARE_MULTICAST_DELEGATE(FOnSelectedPlatformChanged) namespace CmdLineType { extern const TCHAR* Launch; extern const TCHAR* UAT; } class FModel : public TSharedFromThis<FModel> { public: FModel(const TSharedRef<ITargetDeviceProxyManager>& InDeviceProxyManager, const TSharedRef<ILauncher>& InLauncher, const TSharedRef<ILauncherProfileManager>& InProfileManager); ~FModel(); void Init(); const TSharedRef<ITargetDeviceProxyManager>& GetDeviceProxyManager() const { return DeviceProxyManager; } const TSharedRef<ILauncher>& GetLauncher() const {` — Delegate fired when a profile is clicked in the UI
- L129 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSelectedProfileChanged, const ILauncherProfilePtr& , const ILauncherProfilePtr& ) DECLARE_MULTICAST_DELEGATE_OneParam(FOnProjectSettingsReady, const FString& ) DECLARE_MULTICAST_DELEGATE(FOnSelectedPlatformChanged) namespace CmdLineType { extern const TCHAR* Launch; extern const TCHAR* UAT; } class FModel : public TSharedFromThis<FModel> { public: FModel(const TSharedRef<ITargetDeviceProxyManager>& InDeviceProxyManager, const TSharedRef<ILauncher>& InLauncher, const TSharedRef<ILauncherProfileManager>& InProfileManager); ~FModel(); void Init(); const TSharedRef<ITargetDeviceProxyManager>& GetDeviceProxyManager() const { return DeviceProxyManager; } const TSharedRef<ILauncher>& GetLauncher() const { return Launcher; }` — Delegate fired when the selected profile changes
- L132 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnProjectSettingsReady, const FString& ) DECLARE_MULTICAST_DELEGATE(FOnSelectedPlatformChanged) namespace CmdLineType { extern const TCHAR* Launch; extern const TCHAR* UAT; } class FModel : public TSharedFromThis<FModel> { public: FModel(const TSharedRef<ITargetDeviceProxyManager>& InDeviceProxyManager, const TSharedRef<ILauncher>& InLauncher, const TSharedRef<ILauncherProfileManager>& InProfileManager); ~FModel(); void Init(); const TSharedRef<ITargetDeviceProxyManager>& GetDeviceProxyManager() const { return DeviceProxyManager; } const TSharedRef<ILauncher>& GetLauncher() const { return Launcher; } const TSharedRef<ILauncherProfileManager>& GetProfileManager() const {` — Delegate fired when project settings have been loaded
- L135 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnSelectedPlatformChanged) namespace CmdLineType { extern const TCHAR* Launch; extern const TCHAR* UAT; } class FModel : public TSharedFromThis<FModel> { public: FModel(const TSharedRef<ITargetDeviceProxyManager>& InDeviceProxyManager, const TSharedRef<ILauncher>& InLauncher, const TSharedRef<ILauncherProfileManager>& InProfileManager); ~FModel(); void Init(); const TSharedRef<ITargetDeviceProxyManager>& GetDeviceProxyManager() const { return DeviceProxyManager; } const TSharedRef<ILauncher>& GetLauncher() const { return Launcher; } const TSharedRef<ILauncherProfileManager>& GetProfileManager() const { return ProfileManager; }` — Delegate fired when the selected platform changes
- L139 _namespace_ `namespace CmdLineType` (scope `ProjectLauncher`)
- L141 _externvar_ `extern const TCHAR* Launch;` (scope `ProjectLauncher::CmdLineType`)
- L142 _externvar_ `extern const TCHAR* UAT;` (scope `ProjectLauncher::CmdLineType`)

### `Plugins/Developer/ProjectLauncher/Source/ProjectLauncher/Public/ProfileTree/BasicProfileTreeBuilder.h` (Public)


#### class `ProjectLauncher::FBasicProfileTreeBuilder`  
`class FBasicProfileTreeBuilder : public FGenericProfileTreeBuilder`  
_L12-24_
- inherits: `FGenericProfileTreeBuilder`
- L15 _public prototype_ `FBasicProfileTreeBuilder( const ILauncherProfileRef& Profile, const TSharedRef<FModel>& InModel );`
- L16 _public prototype_ `virtual ~FBasicProfileTreeBuilder() = default;`
- L18 _public prototype_ `virtual void Construct() override;`
- L20 _public function_ `virtual FString GetName() const override`

#### class `ProjectLauncher::FBasicProfileTreeBuilderFactory`  
`class FBasicProfileTreeBuilderFactory : public ILaunchProfileTreeBuilderFactory`  
_L29-36_
- inherits: `ILaunchProfileTreeBuilderFactory`
- L32 _public prototype_ `virtual TSharedPtr<ILaunchProfileTreeBuilder> TryCreateTreeBuilder( const ILauncherProfileRef& InProfile, const TSharedRef<FModel>& InModel ) override;`
- L34 _public function_ `virtual bool IsProfileTypeSupported(EProfileType ProfileType ) const override`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API PROJECTLAUNCHER_API`
- L9 _namespace_ `namespace ProjectLauncher`

### `Plugins/Developer/ProjectLauncher/Source/ProjectLauncher/Public/ProfileTree/CustomProfileTreeBuilder.h` (Public)


#### class `ProjectLauncher::FCustomProfileTreeBuilder`  
`class FCustomProfileTreeBuilder : public FGenericProfileTreeBuilder`  
_L11-23_
- inherits: `FGenericProfileTreeBuilder`
- L14 _public prototype_ `FCustomProfileTreeBuilder( const ILauncherProfileRef& Profile, const TSharedRef<FModel>& InModel );`
- L15 _public prototype_ `virtual ~FCustomProfileTreeBuilder() = default;`
- L17 _public prototype_ `virtual void Construct() override;`
- L19 _public function_ `virtual FString GetName() const override`

#### class `ProjectLauncher::FCustomProfileTreeBuilderFactory`  
`class FCustomProfileTreeBuilderFactory : public ILaunchProfileTreeBuilderFactory`  
_L26-33_
- inherits: `ILaunchProfileTreeBuilderFactory`
- L29 _public prototype_ `virtual TSharedPtr<ILaunchProfileTreeBuilder> TryCreateTreeBuilder( const ILauncherProfileRef& Profile, const TSharedRef<FModel>& InModel ) override;`
- L31 _public function_ `virtual bool IsProfileTypeSupported(EProfileType ProfileType ) const override`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API PROJECTLAUNCHER_API`
- L9 _namespace_ `namespace ProjectLauncher`

### `Plugins/Developer/ProjectLauncher/Source/ProjectLauncher/Public/ProfileTree/GenericProfileTreeBuilder.h` (Public)


#### class `ProjectLauncher::FGenericProfileTreeBuilder`  
`class FGenericProfileTreeBuilder : public ILaunchProfileTreeBuilder, public TSharedFromThis<FGenericProfileTreeBuilder>`  
_L31-219_
- inherits: `ILaunchProfileTreeBuilder,TSharedFromThis<FGenericProfileTreeBuilder>`
- desc: Base class for a profile tree builder that creates FLaunchProfileTreeData from a given ILauncherProfile. Expected to be created by an instance of ILaunchProfileTreeBuilderFactory, for example: TSharedPtr<ILaunchProfileTreeBuilder> FMyProfileTreeBuilderFactory::TryCreateTreeBuilder( const ILauncherProfileRef& InProfile, const TSharedRef<FModel>& InModel ) { return MakeShared<FMyProfileTreeBuilder>(InProfile, InModel); }
- L34 _public prototype_ `FGenericProfileTreeBuilder( const ILauncherProfileRef& Profile, const ILauncherProfileRef& InDefaultProfile, const TSharedRef<FModel>& InModel );`
- L35 _public prototype_ `virtual ~FGenericProfileTreeBuilder();`
- L37 _public prototype_ `virtual void Construct() override;`
- L39 _public function_ `virtual FLaunchProfileTreeDataRef GetProfileTree() override`
- L44 _public function_ `virtual bool AllowExtensionsUI() const override`
- L51 _protected prototype_ `void AddProjectProperty( FLaunchProfileTreeNode& HeadingNode );` — default property creation functions
- L53 _protected prototype_ `FString GetProjectPath() const;`
- L54 _protected prototype_ `void SetProjectName(FString ProjectPath);`
- L55 _protected prototype_ `bool HasProject() const;`
- L56 _protected prototype_ `void ValidateBuildTargets(const FString& ProjectPath);`
- L195 _protected prototype_ `void OnUATCommandAdded(const ILauncherProfileUATCommandRef& UATCommand);`
- L196 _protected prototype_ `void OnUATCommandRemoved(const ILauncherProfileUATCommandRef& UATCommand);`
- L197 _protected prototype_ `virtual void OnPropertyChanged() override;`
- L198 _protected prototype_ `void CacheStartupMapList() const;`
- L199 _protected prototype_ `TSharedRef<SWidget> OnGenerateComboWidget( TSharedPtr<FString> InComboString );`
- L202 _protected member_ `mutable bool bStartupMapCacheDirty = true;`
- L203 _protected member_ `mutable TArray<TSharedPtr<FString>> CachedStartupMaps;`
- L205 _protected member_ `FLaunchProfileTreeDataRef TreeData;`
- L206 _protected member_ `const ILauncherProfileRef Profile;`
- L207 _protected member_ `const ILauncherProfileRef DefaultProfile;`
- L208 _protected member_ `ILauncherProfileBuildCookRunPtr DefaultBuildCookRun;`
- L209 _protected member_ `EProfileType ProfileType;`
- L211 _protected member_ `const TSharedRef<FModel> Model;`
- L213 _protected prototype_ `FBuildCookRun& Get(const ILauncherProfileBuildCookRunRef& BuildCookRun);`
- L218 _protected member_ `TMap<ILauncherProfileBuildCookRunRef,TSharedRef<FBuildCookRun>> BuildCookRunData;`

#### class `ProjectLauncher::FGenericProfileTreeBuilder::FBuildCookRun`  
`class FBuildCookRun : public TSharedFromThis<FBuildCookRun>`  
_L58-190_
- inherits: `TSharedFromThis<FBuildCookRun>`
- L61 _public prototype_ `FBuildCookRun( FGenericProfileTreeBuilder& InOwner, ILauncherProfileBuildCookRunRef InBuildCookRun, const TSharedRef<FModel>& InModel );`
- L62 _public prototype_ `~FBuildCookRun();`
- L64 _public prototype_ `void AddTargetProperty( FLaunchProfileTreeNode& HeadingNode );`
- L65 _public prototype_ `void AddPlatformProperty( FLaunchProfileTreeNode& HeadingNode );`
- L66 _public prototype_ `void AddConfigurationProperty( FLaunchProfileTreeNode& HeadingNode );`
- L67 _public prototype_ `void AddContentSchemeProperty( FLaunchProfileTreeNode& HeadingNode );`
- L68 _public prototype_ `void AddCompressPakFilesProperty( FLaunchProfileTreeNode& HeadingNode );`
- L69 _public prototype_ `void AddGenerateChunksProperty( FLaunchProfileTreeNode& HeadingNode );`
- L70 _public prototype_ `void AddZenSnapshotProperty(FLaunchProfileTreeNode& HeadingNode);`
- L71 _public prototype_ `void AddImportZenSnapshotProperty( FLaunchProfileTreeNode& HeadingNode );`
- L72 _public prototype_ `void AddZenPakStreamingPathProperty( FLaunchProfileTreeNode& HeadingNode );`
- L73 _public prototype_ `void AddSubmissionPackageProperty( FLaunchProfileTreeNode& HeadingNode );`
- L74 _public prototype_ `void AddIncrementalCookProperty( FLaunchProfileTreeNode& HeadingNode );`
- L75 _public prototype_ `void AddCookProperty( FLaunchProfileTreeNode& HeadingNode );`
- L76 _public prototype_ `void AddBuildProperty( FLaunchProfileTreeNode& HeadingNode );`
- L77 _public prototype_ `void AddForceBuildProperty( FLaunchProfileTreeNode& HeadingNode );`
- L78 _public prototype_ `void AddArchitectureProperty( FLaunchProfileTreeNode& HeadingNode );`
- L79 _public prototype_ `void AddStagingDirectoryProperty( FLaunchProfileTreeNode& HeadingNode );`
- L80 _public prototype_ `void AddArchiveBuildProperty( FLaunchProfileTreeNode& HeadingNode );`
- L81 _public prototype_ `void AddArchiveBuildDirectoryProperty( FLaunchProfileTreeNode& HeadingNode );`
- L82 _public prototype_ `void AddDeployProperty( FLaunchProfileTreeNode& HeadingNode );`
- L83 _public prototype_ `void AddIncrementalDeployProperty( FLaunchProfileTreeNode& HeadingNode );`
- L84 _public prototype_ `void AddTargetDeviceProperty( FLaunchProfileTreeNode& HeadingNode );`
- L85 _public prototype_ `void AddRunProperty( FLaunchProfileTreeNode& HeadingNode );`
- L86 _public prototype_ `void AddInitialMapProperty( FLaunchProfileTreeNode& HeadingNode );`
- L87 _public prototype_ `void AddCommandLineProperty( FLaunchProfileTreeNode& HeadingNode );`
- L96 _public prototype_ `void Construct();`
- L99 _public prototype_ `TArray<FString> GetBuildTargets() const;`
- L100 _public prototype_ `void SetBuildTargets( TArray<FString> BuildTargets);`
- L102 _public prototype_ `void SetBuildConfiguration(EBuildConfiguration BuildConfiguration);`
- L103 _public prototype_ `EBuildConfiguration GetBuildConfiguration() const;`
- L105 _public prototype_ `void SetContentScheme(EContentScheme ContentScheme);`
- L106 _public prototype_ `bool IsContentSchemeAvailable(EContentScheme, FText& OutReason) const;`
- L108 _public prototype_ `FString GetCommandLine(EBuildTargetType BuildTarget) const;`
- L109 _public prototype_ `void SetCommandLine( const FString& NewCommandLine, EBuildTargetType BuildTarget );`
- L111 _public prototype_ `void SetSelectedPlatforms( TArray<FString> SelectedPlatforms );`
- L112 _public prototype_ `TArray<FString> GetSelectedPlatforms() const;`
- L114 _public prototype_ `void SetCook( bool bCook );`
- L115 _public prototype_ `bool GetCook( ILauncherProfileBuildCookRunPtr InBuildCookRun = nullptr ) const;`
- L117 _public prototype_ `void SetDeployDeviceIDs(TArray<FString> DeployDeviceIDs);`
- L118 _public prototype_ `TArray<FString> GetDeployDeviceIDs() const;`
- L119 _public prototype_ `EDeployDeviceOption GetDeployDeviceOption() const;`
- L120 _public prototype_ `void SetDeployDeviceOption( EDeployDeviceOption DeployDeviceOption );`
- L121 _public prototype_ `float GetDeployDeviceListHeight() const;`
- L122 _public prototype_ `void SetDeployDeviceListHeight( float NewHeight );`
- L123 _public prototype_ `void OnDeviceRemoved(FString DeviceID);`
- L124 _public prototype_ `TSharedRef<SWidget> CreateDeployDeviceWidget();`
- L126 _public prototype_ `void SetBuild( bool bBuild );`
- L127 _public prototype_ `bool GetBuild( ILauncherProfileBuildCookRunPtr InBuildCookRun = nullptr ) const;`
- L129 _public prototype_ `void SetForceBuild( bool bForceBuild );`
- L130 _public prototype_ `bool GetForceBuild( ILauncherProfileBuildCookRunPtr InBuildCookRun = nullptr ) const;`
- L132 _public prototype_ `void SetArchitecture( FString Architecture, EBuildTargetType TargetType );`
- L133 _public prototype_ `FString GetArchitecture(EBuildTargetType TargetType) const;`
- L134 _public prototype_ `FText GetArchitectureDisplayName( FString Architecture );`
- L136 _public prototype_ `void SetDeployToDevice( bool bDeployToDevice );`
- L137 _public prototype_ `bool GetDeployToDevice( ILauncherProfileBuildCookRunPtr InBuildCookRun = nullptr ) const;`
- L139 _public prototype_ `void SetIsRunning( bool bRun );`
- L140 _public prototype_ `bool GetIsRunning( ILauncherProfileBuildCookRunPtr InBuildCookRun = nullptr ) const;`
- L142 _public prototype_ `void OnInitialMapChanged( TSharedPtr<FString> InitialMap, ESelectInfo::Type );`
- L143 _public prototype_ `TSharedPtr<FString> GetInitialMap() const;`
- L146 _public prototype_ `void SetHasAdvancedPlatformTargets( bool bEnable );`
- L147 _public prototype_ `bool HasAdvancedPlatformTargets() const;`
- L149 _public prototype_ `void RefreshContentScheme();`
- L150 _public prototype_ `void ValidateArchitectures();`
- L151 _public prototype_ `void OnValidateProfile(ILauncherProfileUATCommandRef UATCommand);`
- L152 _public prototype_ `void OnProjectSettingsReady(const FString& ProjectPath);`
- L154 _public prototype_ `void CacheArchitectures();`
- L155 _public prototype_ `void CacheBuildTargets();`
- L157 _public prototype_ `FText GetZenSnapshotText() const;`
- L160 _public member_ `FLaunchProfileTreeNode::FGetBool ForPak;` — helper callbacks to simplify control enable/visibility
- L161 _public member_ `FLaunchProfileTreeNode::FGetBool ForZen;`
- L162 _public member_ `FLaunchProfileTreeNode::FGetBool ForZenWS;`
- L163 _public member_ `FLaunchProfileTreeNode::FGetBool ForCooked;`
- L164 _public member_ `FLaunchProfileTreeNode::FGetBool ForEnabledCooked;`
- L165 _public member_ `FLaunchProfileTreeNode::FGetBool ForContent;`
- L166 _public member_ `FLaunchProfileTreeNode::FGetBool ForCode;`
- L167 _public member_ `FLaunchProfileTreeNode::FGetBool ForCodeBuild;`
- L168 _public member_ `FLaunchProfileTreeNode::FGetBool ForDeployment;`
- L169 _public member_ `FLaunchProfileTreeNode::FGetBool ForRun;`
- L170 _public member_ `FLaunchProfileTreeNode::FGetBool ForSubmissionPackage;`
- L171 _public member_ `FLaunchProfileTreeNode::FGetString EmptyString;`
- L173 _public member_ `TArray<FString> CachedDeployDeviceIDs;`
- L175 _public member_ `float DeployDeviceListHeight = 150.0f;`
- L177 _public member_ `EContentScheme ContentScheme;`
- L178 _public member_ `bool bHasAdvancedPlatformTargets;`
- L179 _public member_ `bool bShouldCook;`
- L180 _public member_ `TSharedPtr<SCustomLaunchPlatformCombo> PlatformCombo;`
- L181 _public member_ `TSharedPtr<SCustomLaunchBuildTargetCombo> BuildTargetCombo;`
- L182 _public member_ `TSharedPtr<SSearchableComboBox> InitalMapCombo;`
- L183 _public member_ `TSharedPtr<SCustomLaunchDeviceListView> DeployDeviceListView;`
- L184 _public member_ `TMap<EBuildTargetType, TArray<FString>> CachedBuildTargetArchitectures;`
- L185 _public member_ `TSet<EBuildTargetType> CachedBuildTargetTypes;`
- L187 _public member_ `FGenericProfileTreeBuilder& Owner;`
- L188 _public member_ `ILauncherProfileBuildCookRunRef BuildCookRun;`
- L189 _public member_ `const TSharedRef<FModel> Model;`

#### enum `ProjectLauncher::FGenericProfileTreeBuilder::FBuildCookRun::EDeployDeviceOption`  
`enum class EDeployDeviceOption : uint8`  
_L90-94_
- L92 _public enumerator_ `Default`
- L93 _public enumerator_ `Selected`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API PROJECTLAUNCHER_API`
- L17 _namespace_ `namespace ESelectInfo`
- L19 _namespace_ `namespace ProjectLauncher`

### `Plugins/Developer/ProjectLauncher/Source/ProjectLauncher/Public/ProfileTree/ILaunchProfileTreeBuilder.h` (Public)


#### class `ProjectLauncher::ILaunchProfileTreeBuilder`  
`class ILaunchProfileTreeBuilder`  
_L22-54_
- desc: Interface for a profile tree builder that creates FLaunchProfileTreeData from a given ILauncherProfile. Expected to be created by an instance of ILaunchProfileTreeBuilderFactory, for example: TSharedPtr<ILaunchProfileTreeBuilder> FMyProfileTreeBuilderFactory::TryCreateTreeBuilder( const ILauncherProfileRef& InProfile, const TSharedRef<FModel>& InModel ) { return MakeShared<FMyProfileTreeBuilder>(InProfile, InModel); }
- L28 _public prototype_ `virtual void Construct() = 0;` — Construct the launch profile tree
- L35 _public prototype_ `virtual FLaunchProfileTreeDataRef GetProfileTree() = 0;` — Provide access to the launch profile tree @returns profile UI tree
- L42 _public prototype_ `virtual FString GetName() const = 0;` — Debug name for this tree builder @returns debug name of the tree builder
- L48 _public prototype_ `virtual void OnPropertyChanged() = 0;` — Callback when the property tree editor has modified the profile. NOTE: Custom widgets will need to call this manually.
- L53 _public prototype_ `virtual bool AllowExtensionsUI() const = 0;` — Whether this tree builder allows extensions to add UI elements. Typically would be true without good reason.

#### class `ProjectLauncher::ILaunchProfileTreeBuilderFactory`  
`class ILaunchProfileTreeBuilderFactory`  
_L65-92_
- desc: Interface for a factory that can create specializations of ILaunchProfileTreeBuilder for a given ILauncherProfile Singleton instance is registered with this plugin during initialization as follows: TSharedPtr<FMyTreeBuilderFactory> MyTreeBuilder = MakeShared<FMyTreeBuilderFactory>(); IProjectLauncherModule::Get().RegisterTreeBuilder( MyTreeBuilder.ToSharedRef() );
- L75 _public prototype_ `virtual TSharedPtr<ILaunchProfileTreeBuilder> TryCreateTreeBuilder( const ILauncherProfileRef& Profile, const TSharedRef<ProjectLauncher::FModel>& Model ) = 0;` — Create a profile tree builder class for the given profile @param Profile the profile being edited @param Model helper class @returns new instance of a profile tree builder for the given profile, or null if it is not supported by this tree builder factory
- L83 _public function_ `virtual int GetPriority() const` — Get the priority for this tree builder factory. Higher priority tree builders are evaluated first. Specializations should return non-zero values @returns priority for this tree builder factory
- L91 _public prototype_ `virtual bool IsProfileTypeSupported(ProjectLauncher::EProfileType ProfileType ) const = 0;` — Determines whether this tree builder can support profiles of the given type @param ProfileType the type of profile @returns true if the profile type is supported

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace ProjectLauncher`

### `Plugins/Developer/ProjectLauncher/Source/ProjectLauncher/Public/ProfileTree/LaunchProfileTreeData.h` (Public)


#### class `ProjectLauncher::FValidation`  
`class FValidation`  
_L44-65_
- desc: Validation object representing errors and warnings tied to profile settings. If the given validation errors are present in the profile a warning icon will be displayed next to this property in the UI Use with the Validation callback in FLaunchProfileTreeNode: .Validation = FValidation( {ELauncherProfileValidationErrors::NoProjectSelected, ...} ), or .Validation = FValidation( {TEXT("Validation_SomeCustomValidation"), ...} ),
- L47 _public function_ `FValidation()`
- L48 _public prototype_ `FValidation( std::initializer_list<ELauncherProfileValidationErrors::Type> InAssociatedErrors );`
- L49 _public prototype_ `FValidation( std::initializer_list<ELauncherProfileValidationErrors::Type> InAssociatedErrors, std::initializer_list<FString> InAssociatedCustomErrors );`
- L50 _public prototype_ `FValidation( std::initializer_list<FString> InAssociatedCustomErrors );`
- L53 _public prototype_ `bool IsSet() const;` — Returns true if any validation rules are set.
- L56 _public prototype_ `bool HasError( ILauncherProfileRef Profile, ILauncherProfileUATCommandPtr UATCommand ) const;` — Returns true if the given profile has one of the associated errors.
- L59 _public prototype_ `void GetErrorText( ILauncherProfileRef Profile, ILauncherProfileUATCommandPtr UATCommand, TArray<FString>& ErrorLines ) const;` — Collects error text from the profile for display.
- L62 _private member_ `bool bIsSet = false;` — whether this validation has been configured
- L63 _private member_ `TArray<ELauncherProfileValidationErrors::Type> AssociatedErrors;` — engine-defined errors
- L64 _private member_ `TArray<FString> AssociatedCustomErrors;` — custom errors specific to this profile

#### class `ProjectLauncher::FLaunchProfileTreeNode`  
`class FLaunchProfileTreeNode : public TSharedFromThis<FLaunchProfileTreeNode>`  
_L70-173_
- inherits: `TSharedFromThis<FLaunchProfileTreeNode>`
- desc: Represents a single editable node (field, checkbox, widget, etc.) in the profile tree UI.
- L74 _public prototype_ `FLaunchProfileTreeNode(FLaunchProfileTreeData* InTreeData);` — Construct a node bound to a tree.
- L76 _public typedef_ `typedef TFunction<void()> FFunction;`
- L77 _public typedef_ `typedef TFunction<bool()> FGetBool;`
- L78 _public typedef_ `typedef TFunction<void(bool)> FSetBool;`
- L79 _public typedef_ `typedef TFunction<int32()> FGetInt;`
- L80 _public typedef_ `typedef TFunction<void(int32)> FSetInt;`
- L81 _public typedef_ `typedef TFunction<float()> FGetFloat;`
- L82 _public typedef_ `typedef TFunction<void(float)> FSetFloat;`
- L83 _public typedef_ `typedef TFunction<FString(void)> FGetString;`
- L84 _public typedef_ `typedef TFunction<void(FString)> FSetString;`
- L97 _public prototype_ `FLaunchProfileTreeNode& AddWidget( FText InName, FCallbacks&& InWidgetCallbacks, TSharedRef<SWidget> InValueWidget );` — Add a generic widget with callbacks.
- L100 _public prototype_ `FLaunchProfileTreeNode& AddWidget( FText InName, TSharedRef<SWidget> InValueWidget );` — Add a generic widget without callbacks.
- L112 _public prototype_ `FLaunchProfileTreeNode& AddBoolean( FText InName, FBooleanCallbacks&& BooleanCallbacks, FText ToolTipText = FText::FromString(""));`
- L124 _public prototype_ `FLaunchProfileTreeNode& AddString( FText InName, FStringCallbacks&& StringCallbacks, FText ToolTipText = FText::FromString(""), FText HintText = FText::FromString(""));`
- L125 _public prototype_ `FLaunchProfileTreeNode& AddDirectoryString(FText InName, FStringCallbacks&& StringCallbacks, bool InMakeRelative = true, FText ToolTipText = FText::FromString(""));`
- L126 _public prototype_ `FLaunchProfileTreeNode& AddFileString(FText InName, FStringCallbacks&& StringCallbacks, FString FileFilter = TEXT("All`
- L127 _public prototype_ `FLaunchProfileTreeNode& AddCommandLineString( FText InName, FStringCallbacks&& StringCallbacks, const TCHAR* InType = nullptr );` — defaults to "Launch" cmdline extensions
- L143 _public prototype_ `template<typename T> FLaunchProfileTreeNode& AddValue( FText InName, TTypeCallbacks<T>&& TypeCallbacks, TInterval<T> Range = TInterval<T>(), bool bShowSpinner = false );` — Add a typed value widget, e.g. spinner for int or float.
- L145 _public prototype_ `FLaunchProfileTreeNode& AddInteger( FText InName, TTypeCallbacks<int32>&& TypeCallbacks, FInt32Interval Range = FInt32Interval(), bool bShowSpinner = false );`
- L146 _public prototype_ `FLaunchProfileTreeNode& AddFloat( FText InName, TTypeCallbacks<float>&& TypeCallbacks, FFloatInterval Range = FFloatInterval(), bool bShowSpinner = false );`
- L148 _public prototype_ `FLaunchProfileTreeNode& AddSubHeading(const TCHAR* InName, FText InDisplayName, int32 SortOrder = 0);`
- L149 _public prototype_ `FLaunchProfileTreeNode& GetSubHeading(const TCHAR* InName) const;`
- L151 _public prototype_ `FLaunchProfileTreeNode& FindOrAddSubHeading(ILauncherProfileUATCommandRef UATCommand);`
- L153 _public prototype_ `bool ContainsNodeRecursive( const FLaunchProfileTreeNodePtr& TargetNode ) const;`
- L156 _public member_ `FText Name;` — Node details
- L157 _public member_ `int32 SortOrder;` — sort order for headings
- L158 _public member_ `int32 Depth = 0;` — tree depth
- L159 _public member_ `TSharedPtr<SWidget> Widget;` — UI widget
- L160 _public member_ `ILauncherProfileUATCommandPtr UATCommand;` — option UAT command associated with this node
- L161 _public member_ `FCallbacks Callbacks;` — generic callbacks
- L162 _public member_ `TArray<FLaunchProfileTreeNodePtr> Children;` — child nodes
- L163 _public member_ `TMap<FString,FLaunchProfileTreeNodePtr> SubHeadingNodes;` — named subheadings
- L165 _public function_ `const FLaunchProfileTreeData* GetTreeData() const`
- L166 _public function_ `FLaunchProfileTreeData* GetTreeData()`
- L170 _protected prototype_ `void OnPropertyChanged();` — Notify parent tree that a property has changed.
- L172 _protected member_ `FLaunchProfileTreeData* TreeData;`
- L234 _function_ `template<typename T> FLaunchProfileTreeNode& FLaunchProfileTreeNode::AddValue( FText InName, TTypeCallbacks<T>&& TypeCallbacks, TInterval<T> Range, bool bShowSpinner )`

#### struct `ProjectLauncher::FLaunchProfileTreeNode::FCallbacks`  
`struct FCallbacks`  
_L87-94_
- desc: Callbacks common to all widgets.
- L89 _public member_ `FGetBool IsDefault = nullptr;` — check if current value is default
- L90 _public member_ `FFunction SetToDefault = nullptr;` — reset to default
- L91 _public member_ `FGetBool IsVisible = nullptr;` — visibility logic
- L92 _public member_ `FGetBool IsEnabled = nullptr;` — enabled/disabled logic
- L93 _public member_ `FValidation Validation;` — validation rules

#### struct `ProjectLauncher::FLaunchProfileTreeNode::FBooleanCallbacks`  
`struct FBooleanCallbacks`  
_L103-111_
- desc: Boolean-specific callbacks.
- L105 _public member_ `FGetBool GetValue = nullptr;`
- L106 _public member_ `FSetBool SetValue = nullptr;`
- L107 _public member_ `FGetBool GetDefaultValue = nullptr;`
- L108 _public member_ `FGetBool IsVisible = nullptr;`
- L109 _public member_ `FGetBool IsEnabled = nullptr;`
- L110 _public member_ `FValidation Validation;`

#### struct `ProjectLauncher::FLaunchProfileTreeNode::FStringCallbacks`  
`struct FStringCallbacks`  
_L115-123_
- desc: String-specific callbacks.
- L117 _public member_ `FGetString GetValue = nullptr;`
- L118 _public member_ `FSetString SetValue = nullptr;`
- L119 _public member_ `FGetString GetDefaultValue = nullptr;`
- L120 _public member_ `FGetBool IsVisible = nullptr;`
- L121 _public member_ `FGetBool IsEnabled = nullptr;`
- L122 _public member_ `FValidation Validation;`

#### struct `ProjectLauncher::FLaunchProfileTreeNode::TTypeCallbacks`  
`template<typename T> struct TTypeCallbacks`  
_L131-139_
- desc: Generic value callbacks.
- L133 _public member_ `TFunction<T()> GetValue = nullptr;`
- L134 _public member_ `TFunction<void(T)> SetValue = nullptr;`
- L135 _public member_ `TFunction<T()> GetDefaultValue = nullptr;`
- L136 _public member_ `FGetBool IsVisible = nullptr;`
- L137 _public member_ `FGetBool IsEnabled = nullptr;`
- L138 _public member_ `FValidation Validation;`

#### class `ProjectLauncher::FLaunchProfileTreeData`  
`class FLaunchProfileTreeData : public TSharedFromThis<FLaunchProfileTreeData>`  
_L179-228_
- inherits: `TSharedFromThis<FLaunchProfileTreeData>`
- desc: Represents the full profile tree of editable UI nodes for a launcher profile. Integrates extensions and manages node headings.
- L183 _public prototype_ `FLaunchProfileTreeData(ILauncherProfilePtr InProfile, TSharedRef<FModel> InModel, ILaunchProfileTreeBuilder* InTreeBuilder);` — Construct with a profile, model, and tree builder.
- L184 _public prototype_ `~FLaunchProfileTreeData();`
- L187 _public prototype_ `FLaunchProfileTreeNode& AddHeading(const TCHAR* InName, FText InDisplayName, int32 SortOrder = 0);` — Add or retrieve top-level headings.
- L188 _public prototype_ `FLaunchProfileTreeNode& GetHeading(const TCHAR* InName) const;`
- L190 _public prototype_ `FLaunchProfileTreeNode& FindOrAddHeading(ILauncherProfileUATCommandRef UATCommand, bool bIsPrimaryHeading);`
- L191 _public prototype_ `void SortNodes();`
- L194 _public prototype_ `void CreateExtensionsUI();` — Invoke extension instances to build their UI.
- L197 _public prototype_ `void OnPropertyChanged();` — Notify of property changes and refresh requests.
- L198 _public prototype_ `void RequestTreeRefresh();`
- L199 _public prototype_ `void RequestFullTreeRebuild();`
- L200 _public prototype_ `void OnCommandLineFieldCreated( FLaunchProfileTreeNode& InNode, const FLaunchProfileTreeNode::FStringCallbacks& InStringCallbacks, const FString& InTypeName );`
- L201 _public prototype_ `void OnLaunchExtensionToggle( const TSharedRef<class FLaunchExtensionInstance>& ExtensionInstance, bool bAdded );`
- L204 _public member_ `ILauncherProfilePtr Profile;` — Member variables
- L205 _public member_ `TSharedRef<FModel> Model;` — owning model
- L206 _public member_ `TArray<FLaunchProfileTreeNodePtr> Nodes;` — all nodes
- L207 _public member_ `TMap<FString,FLaunchProfileTreeNodePtr> HeadingNodes;` — named top-level headings
- L208 _public member_ `ILaunchProfileTreeBuilder* TreeBuilder;` — UI builder interface
- L209 _public member_ `TArray<TSharedPtr<FLaunchExtensionInstance>> ExtensionInstances;` — extension instances attached
- L210 _public member_ `TSet<FLaunchProfileTreeNodePtr> RequestExpandHeadings;` — headings to expand
- L211 _public member_ `TSet<FLaunchProfileTreeNodePtr> UATCommandHeadings;` — headings that have additional controls for modifying the command
- L212 _public member_ `bool bRequestTreeRefresh = false;` — request to refresh tree UI
- L213 _public member_ `bool bRequestTreeFullRebuild = false;` — request to fully recreate the profile tree
- L216 _public member_ `static const TCHAR* GeneralSettingsSectionName;` — Constants
- L217 _public member_ `static const int32 GeneralSettingsSortOrder;`
- L218 _public member_ `static const int32 DefaultSortOrder;`
- L227 _private member_ `TArray<FCommandLineField> AllCommandLineFields;`

#### struct `ProjectLauncher::FLaunchProfileTreeData::FCommandLineField`  
`struct FCommandLineField`  
_L221-226_
- L223 _public member_ `FLaunchProfileTreeNode::FGetString GetValue = nullptr;`
- L224 _public member_ `FLaunchProfileTreeNode::FSetString SetValue = nullptr;`
- L225 _public member_ `FString TypeName;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API PROJECTLAUNCHER_API`
- L19 _namespace_ `namespace ProjectLauncher`
- L27 _typedef_ `typedef TSharedPtr<FLaunchProfileTreeData> FLaunchProfileTreeDataPtr;` (scope `ProjectLauncher`)
- L28 _typedef_ `typedef TSharedRef<FLaunchProfileTreeData> FLaunchProfileTreeDataRef;` (scope `ProjectLauncher`)
- L30 _typedef_ `typedef TSharedPtr<FLaunchProfileTreeNode> FLaunchProfileTreeNodePtr;` (scope `ProjectLauncher`)
- L31 _typedef_ `typedef TSharedRef<FLaunchProfileTreeNode> FLaunchProfileTreeNodeRef;` (scope `ProjectLauncher`)
- L247 _function_ `` (scope `ProjectLauncher::FLaunchProfileTreeNode::AddValue`)

### `Plugins/Developer/ProjectLauncher/Source/ProjectLauncher/Public/ProjectLauncherModule.h` (Public)


#### class `IProjectLauncherModule`  
`class IProjectLauncherModule : public IModuleInterface`  
_L17-61_
- inherits: `IModuleInterface`
- desc: Interface for ProjectLauncher module
- L24 _public function_ `static inline IProjectLauncherModule& Get()` — Singleton-like access to the Custom Launch UI module instance @return Returns IProjectLauncherModule singleton instance, loading the module on demand if needed
- L33 _public function_ `static inline IProjectLauncherModule* TryGet()` — Singleton-like access to the Custom Launch UI module instance @return Returns IProjectLauncherModule singleton instance if it is loaded
- L43 _public prototype_ `virtual void RegisterTreeBuilder( TSharedRef<ProjectLauncher::ILaunchProfileTreeBuilderFactory> TreeBuilderFactory ) = 0;` — Registers a marhaller factory, for defining the layout & fields for editing an ILauncherProfile
- L48 _public prototype_ `virtual void UnregisterTreeBuilder( TSharedRef<ProjectLauncher::ILaunchProfileTreeBuilderFactory> TreeBuilderFactory ) = 0;` — Unregisters a previously-registered tree builder factory
- L55 _public prototype_ `virtual void RegisterExtension( TSharedRef<ProjectLauncher::FLaunchExtension> Extension ) = 0;` — Registers an extension
- L60 _public prototype_ `virtual void UnregisterExtension( TSharedRef<ProjectLauncher::FLaunchExtension> Extension ) = 0;` — Unregisters a previously-registered extension

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ProjectLauncher`

### `Plugins/Developer/ProjectLauncher/Source/ProjectLauncher/Public/Utils/LauncherCmdLineUtils.h` (Public)


#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PROJECTLAUNCHER_API`
- L10 _namespace_ `namespace ProjectLauncher`
- L12 _namespace_ `namespace CmdLineUtils` (scope `ProjectLauncher`)
- L20 _prototype_ `bool IsParameterUsed( const FString& InCmdLine, const FString& InParameter );` (scope `ProjectLauncher::CmdLineUtils`) — Determine if the given parameter is on the command line @param InParameter the parameter to test, e.g. -key=value or -param @returns whether the parameter is being used
- L28 _prototype_ `void SetParameterUsed( FString& InOutCmdLine, const FString& InParameter, bool bUsed );` (scope `ProjectLauncher::CmdLineUtils`) — Add or remove the given parameter on the command line @param InParameter the parameter to add or remove, e.g. -key=value or -param @param bUsed whether to add or remove the parameter
- L35 _prototype_ `void AddParameter( FString& InOutCmdLine, const FString& InParameter );` (scope `ProjectLauncher::CmdLineUtils`) — Add the given parameter to the command line @param InParameter the parameter to add, e.g. -key=value or -param
- L43 _prototype_ `bool RemoveParameter( FString& InOutCmdLine, const FString& InParameter );` (scope `ProjectLauncher::CmdLineUtils`) — Remove the given parameter from the command line @param InParameter the parameter to remove, e.g. -key=value or -param @returns true if the parameter was removed
- L51 _prototype_ `FString GetParameterValue( const FString& InCmdLine, const FString& InParameter );` (scope `ProjectLauncher::CmdLineUtils`) — Retrieve the current value for the given command line parameter @param InParameter the parameter to query, e.g. -key=value @returns the value of the parameter
- L60 _prototype_ `bool UpdateParameterValue( FString& InOutCmdLine, const FString& InParameter, const FString& InNewValue );` (scope `ProjectLauncher::CmdLineUtils`) — Update the value of the given command line parameter @param InParameter the parameter to modify, e.g. -key=value or -key= @param InNewValue the new value to use @returns true unless InParameter is not a key/value property
- L68 _prototype_ `FString GetFinalParameter( const FString& InCmdLine, const FString& InParameter );` (scope `ProjectLauncher::CmdLineUtils`) — Get the current state of the given command line parameter, allowing for user-changed values @param InParameter the parameter to test, e.g. -key=value @returns The parameter as it is now, allowing for user modifications, e.g. -key=value or -key=some_new_value

### `Plugins/Developer/ProjectLauncher/Source/ProjectLauncher/Public/Widgets/Shared/SCustomLaunchBuildTargetCombo.h` (Public)


#### class `SCustomLaunchBuildTargetCombo`  
`class SCustomLaunchBuildTargetCombo : public SCompoundWidget`  
_L16-57_
- inherits: `SCompoundWidget`
- L20 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnSelectionChanged, TArray<FString> );`
- L22 _public function_ `SLATE_BEGIN_ARGS(SCustomLaunchBuildTargetCombo) : _TextStyle( &FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>( "NormalText" ) )`
- L25 _public prototype_ `SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged);`
- L26 _public prototype_ `SLATE_ATTRIBUTE(FString, SelectedProject);`
- L27 _public prototype_ `SLATE_ATTRIBUTE(TArray<FString>, SelectedBuildTargets);`
- L35 _public prototype_ `void Construct( const FArguments& InArgs, TSharedRef<ProjectLauncher::FModel> InModel);`
- L38 _protected prototype_ `FString GetDefaultBuildTargetName() const;`
- L39 _protected prototype_ `ECheckBoxState GetBuildTargetCheckState( FString BuildTargetName ) const;`
- L41 _protected member_ `TAttribute<FString> SelectedProject;`
- L42 _protected member_ `TAttribute<TArray<FString>> SelectedBuildTargets;`
- L43 _protected member_ `FOnSelectionChanged OnSelectionChanged;`
- L44 _protected member_ `bool bShowAnyProjectOption;`
- L45 _protected member_ `TAttribute<bool> GetAdvancedPlatformsOption;`
- L46 _protected member_ `FOnBooleanValueChanged SetAdvancedPlatformsOption;`
- L48 _protected member_ `TSharedPtr<ProjectLauncher::FModel> Model;`
- L49 _protected member_ `TSharedPtr<class SComboButton> ComboButton;`
- L51 _protected prototype_ `TSharedRef<SWidget> MakeBuildTargetSelectionWidget();`
- L53 _protected prototype_ `FText GetBuildTargetName() const;`
- L54 _protected prototype_ `void SetBuildTargetName(FString BuildTargetName);`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API PROJECTLAUNCHER_API`
- L20 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSelectionChanged, TArray<FString> );`

### `Plugins/Developer/ProjectLauncher/Source/ProjectLauncher/Public/Widgets/Shared/SCustomLaunchCombo.h` (Public)


#### class `SCustomLaunchCombo`  
`template<typename T> class SCustomLaunchCombo : public SCompoundWidget`  
_L18-211_
- inherits: `SCompoundWidget`
- desc: helper class to create a combo box that can select an item or collection of items
- L22 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnSelectionChanged, T );`
- L23 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnSelectedItemsChanged, TArray<T> );`
- L24 _public function_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FGetItemText, T) DECLARE_DELEGATE_RetVal_OneParam(bool, FIsItemEnabled, T) DECLARE_DELEGATE_RetVal_OneParam(FSlateIcon, FGetItemIcon, T) SLATE_BEGIN_ARGS(SCustomLaunchCombo<T>) : _ActionType(EUserInterfaceActionType::RadioButton)`
- L45 _public function_ `void Construct( const FArguments& InArgs)`
- L86 _protected member_ `TAttribute<T> SelectedItem;`
- L87 _protected member_ `TAttribute<TArray<T>> SelectedItems;`
- L88 _protected member_ `TAttribute<TArray<T>> Items;`
- L89 _protected member_ `FOnSelectionChanged OnSelectionChanged;`
- L90 _protected member_ `FGetItemText GetDisplayName;`
- L91 _protected member_ `FGetItemText GetItemToolTip;`
- L92 _protected member_ `FIsItemEnabled IsItemEnabled;`
- L93 _protected member_ `FGetItemIcon GetItemIcon;`
- L94 _protected member_ `FOnSelectedItemsChanged OnSelectedItemsChanged;`
- L96 _protected member_ `bool bIsMultiselect;`
- L97 _protected member_ `EUserInterfaceActionType ActionType;`
- L99 _protected function_ `FText GetSelectedItemDisplayName() const`
- L119 _protected function_ `void SetSelectedItem(T Value)`
- L142 _protected function_ `ECheckBoxState GetItemCheckState(T Value)`
- L157 _protected function_ `bool GetItemIsEnabled(T Value) const`
- L162 _protected function_ `FText ToText(T Value) const`
- L173 _protected function_ `virtual FText ToTextOverride(T Value) const`
- L179 _protected function_ `TSharedRef<SWidget> MakeWidget()`

#### class `SCustomLaunchLexToStringCombo`  
`template<typename T> class SCustomLaunchLexToStringCombo : public SCustomLaunchCombo<T>`  
_L216-223_
- inherits: `SCustomLaunchCombo<T>`
- desc: helper class that can display a list of items, if those items have a LexToString function available
- L219 _public function_ `virtual FText ToTextOverride(T Value) const override`

#### class `SCustomLaunchStringCombo`  
`class SCustomLaunchStringCombo : public SCustomLaunchCombo<FString>`  
_L226-233_
- inherits: `SCustomLaunchCombo<FString>`
- desc: helper class that can display a list of strings
- L229 _public function_ `virtual FText ToTextOverride(FString Value) const override`

#### Free symbols / members of external scopes

- L13 _macro_ `#define LOCTEXT_NAMESPACE "SCustomLaunchCombo"`
- L22 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSelectionChanged, T );`
- L23 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSelectedItemsChanged, TArray<T> );`
- L24 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FGetItemText, T) DECLARE_DELEGATE_RetVal_OneParam(bool, FIsItemEnabled, T) DECLARE_DELEGATE_RetVal_OneParam(FSlateIcon, FGetItemIcon, T) SLATE_BEGIN_ARGS(SCustomLaunchCombo<T>) : _ActionType(EUserInterfaceActionType::RadioButton) {} SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged) SLATE_EVENT(FGetItemText, GetDisplayName) SLATE_EVENT(FGetItemText, GetItemToolTip) SLATE_EVENT(FIsItemEnabled, IsItemEnabled) SLATE_EVENT(FGetItemIcon, GetItemIcon) SLATE_EVENT(FOnSelectedItemsChanged, OnSelectedItemsChanged) SLATE_EVENT(FOnIsOpenChanged, OnMenuOpenChanged) SLATE_ATTRIBUTE(TArray<T>, Items) SLATE_ATTRIBUTE(T, SelectedItem) SLATE_ATTRIBUTE(TArray<T>, SelectedItems) SLATE_ARGUMENT(EUserInterfaceActionType, ActionType) SLATE_END_ARGS() public: void Construct( const FArguments& InArgs) { OnSelectionChanged = InArgs._OnSelectionChanged; OnSelectedItemsChanged = InArgs._OnSelectedItemsChanged; GetDisplayName = InArgs._GetDisplayName; GetItemToolTip = InArgs._GetItemToolTip; IsItemEnabled = InArgs._IsItemEnabled; GetItemIcon = InArgs._GetItemIcon; ActionType = InArgs._ActionType; Items = InArgs._Items; SelectedItem = InArgs._SelectedItem; SelectedItems = InArgs._SelectedItems; bIsMultiselect = (ActionType == EUserInterfaceActionType::Check || ActionType == EUserInterfaceActionType::ToggleButton); if (bIsMultiselect) { check(!OnSelectionChanged.IsBound()); check(!SelectedItem.IsBound());`
- L25 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsItemEnabled, T) DECLARE_DELEGATE_RetVal_OneParam(FSlateIcon, FGetItemIcon, T) SLATE_BEGIN_ARGS(SCustomLaunchCombo<T>) : _ActionType(EUserInterfaceActionType::RadioButton) {} SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged) SLATE_EVENT(FGetItemText, GetDisplayName) SLATE_EVENT(FGetItemText, GetItemToolTip) SLATE_EVENT(FIsItemEnabled, IsItemEnabled) SLATE_EVENT(FGetItemIcon, GetItemIcon) SLATE_EVENT(FOnSelectedItemsChanged, OnSelectedItemsChanged) SLATE_EVENT(FOnIsOpenChanged, OnMenuOpenChanged) SLATE_ATTRIBUTE(TArray<T>, Items) SLATE_ATTRIBUTE(T, SelectedItem) SLATE_ATTRIBUTE(TArray<T>, SelectedItems) SLATE_ARGUMENT(EUserInterfaceActionType, ActionType) SLATE_END_ARGS() public: void Construct( const FArguments& InArgs) { OnSelectionChanged = InArgs._OnSelectionChanged; OnSelectedItemsChanged = InArgs._OnSelectedItemsChanged; GetDisplayName = InArgs._GetDisplayName; GetItemToolTip = InArgs._GetItemToolTip; IsItemEnabled = InArgs._IsItemEnabled; GetItemIcon = InArgs._GetItemIcon; ActionType = InArgs._ActionType; Items = InArgs._Items; SelectedItem = InArgs._SelectedItem; SelectedItems = InArgs._SelectedItems; bIsMultiselect = (ActionType == EUserInterfaceActionType::Check || ActionType == EUserInterfaceActionType::ToggleButton); if (bIsMultiselect) { check(!OnSelectionChanged.IsBound()); check(!SelectedItem.IsBound()); }`
- L26 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FSlateIcon, FGetItemIcon, T) SLATE_BEGIN_ARGS(SCustomLaunchCombo<T>) : _ActionType(EUserInterfaceActionType::RadioButton) {} SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged) SLATE_EVENT(FGetItemText, GetDisplayName) SLATE_EVENT(FGetItemText, GetItemToolTip) SLATE_EVENT(FIsItemEnabled, IsItemEnabled) SLATE_EVENT(FGetItemIcon, GetItemIcon) SLATE_EVENT(FOnSelectedItemsChanged, OnSelectedItemsChanged) SLATE_EVENT(FOnIsOpenChanged, OnMenuOpenChanged) SLATE_ATTRIBUTE(TArray<T>, Items) SLATE_ATTRIBUTE(T, SelectedItem) SLATE_ATTRIBUTE(TArray<T>, SelectedItems) SLATE_ARGUMENT(EUserInterfaceActionType, ActionType) SLATE_END_ARGS() public: void Construct( const FArguments& InArgs) { OnSelectionChanged = InArgs._OnSelectionChanged; OnSelectedItemsChanged = InArgs._OnSelectedItemsChanged; GetDisplayName = InArgs._GetDisplayName; GetItemToolTip = InArgs._GetItemToolTip; IsItemEnabled = InArgs._IsItemEnabled; GetItemIcon = InArgs._GetItemIcon; ActionType = InArgs._ActionType; Items = InArgs._Items; SelectedItem = InArgs._SelectedItem; SelectedItems = InArgs._SelectedItems; bIsMultiselect = (ActionType == EUserInterfaceActionType::Check || ActionType == EUserInterfaceActionType::ToggleButton); if (bIsMultiselect) { check(!OnSelectionChanged.IsBound()); check(!SelectedItem.IsBound()); } else`

### `Plugins/Developer/ProjectLauncher/Source/ProjectLauncher/Public/Widgets/Shared/SCustomLaunchContentSchemeCombo.h` (Public)


#### class `SCustomLaunchContentSchemeCombo`  
`class SCustomLaunchContentSchemeCombo : public SCompoundWidget`  
_L15-44_
- inherits: `SCompoundWidget`
- L19 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnSelectionChanged, ProjectLauncher::EContentScheme );`
- L20 _public function_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FGetContentSchemeAvailability, ProjectLauncher::EContentScheme, FText& ) SLATE_BEGIN_ARGS(SCustomLaunchContentSchemeCombo) : _TextStyle( &FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>( "NormalText" ) )`
- L25 _public prototype_ `SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged);`
- L26 _public prototype_ `SLATE_EVENT(FGetContentSchemeAvailability, IsContentSchemeAvailable) SLATE_ATTRIBUTE(ProjectLauncher::EContentScheme, SelectedContentScheme);`
- L33 _public prototype_ `void Construct( const FArguments& InArgs);`
- L36 _protected member_ `TAttribute<ProjectLauncher::EContentScheme> SelectedContentScheme;`
- L37 _protected member_ `FOnSelectionChanged OnSelectionChanged;`
- L38 _protected member_ `FGetContentSchemeAvailability IsContentSchemeAvailable;`
- L40 _protected prototype_ `TSharedRef<SWidget> MakeContentSchemeSelectionWidget();`
- L42 _protected prototype_ `FText GetContentSchemeName() const;`
- L43 _protected prototype_ `void SetContentScheme(ProjectLauncher::EContentScheme ContentScheme);`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API PROJECTLAUNCHER_API`
- L19 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSelectionChanged, ProjectLauncher::EContentScheme );`
- L20 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FGetContentSchemeAvailability, ProjectLauncher::EContentScheme, FText& ) SLATE_BEGIN_ARGS(SCustomLaunchContentSchemeCombo) : _TextStyle( &FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>( "NormalText" ) ) {} SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged);`

### `Plugins/Developer/ProjectLauncher/Source/ProjectLauncher/Public/Widgets/Shared/SCustomLaunchCultureListView.h` (Public)


#### class `SCustomLaunchCultureListView`  
`class SCustomLaunchCultureListView : public SCompoundWidget`  
_L16-104_
- inherits: `SCompoundWidget`
- L20 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnSelectionChanged, TArray<FString> );`
- L22 _public function_ `SLATE_BEGIN_ARGS(SCustomLaunchCultureListView)`
- L23 _public prototype_ `SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged);`
- L24 _public prototype_ `SLATE_ATTRIBUTE(TArray<FString>, SelectedCultures);`
- L29 _public prototype_ `void Construct( const FArguments& InArgs, TSharedRef<ProjectLauncher::FModel> InModel );`
- L31 _public prototype_ `void RefreshCultureList();`
- L32 _public prototype_ `TSharedRef<SWidget> MakeControlsWidget();`
- L35 _protected member_ `TSharedPtr<ProjectLauncher::FModel> Model;`
- L36 _protected member_ `TAttribute<TArray<FString>> SelectedCultures;`
- L37 _protected member_ `TAttribute<FString> ProjectPath;`
- L38 _protected member_ `FOnSelectionChanged OnSelectionChanged;`
- L47 _private typedef_ `typedef TSharedPtr<FCultureTreeNode> FCultureTreeNodePtr;`
- L49 _private member_ `FCultureTreeNodePtr CultureTreeRoot;`
- L51 _private prototype_ `void OnProjectChanged();`
- L53 _private prototype_ `void OnSearchFilterTextCommitted(const FText& SearchText, ETextCommit::Type InCommitType);`
- L54 _private prototype_ `void OnSearchFilterTextChanged(const FText& SearchText);`
- L56 _private member_ `FString CurrentFilterText;`
- L68 _private member_ `ELocalizationGroupFilter LocalizationGroupFilter;`
- L81 _private member_ `TMap<ELocalizationGroupFilter,FLocalizationGroup> LocalizationGroupDetails;`
- L85 _private member_ `static const TCHAR** LocalizationGroupPrefixes[(int32)ELocalizationGroupFilter::MAX];`
- L86 _private member_ `static const FText LocalizationGroupDisplayName[(int32)ELocalizationGroupFilter::MAX];`
- L89 _private member_ `TSharedPtr<STreeView<FCultureTreeNodePtr>> CultureListView;`
- L90 _private member_ `TArray<FCultureTreeNodePtr> CultureListViewItemsSource;`
- L92 _private prototype_ `void GetCultureTreeNodeChildren(FCultureTreeNodePtr Item, TArray<FCultureTreeNodePtr>& OutChildren);`
- L93 _private prototype_ `TSharedRef<ITableRow> GenerateCultureTreeNodeRow(FCultureTreeNodePtr Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L94 _private prototype_ `ECheckBoxState GetCultureTreeNodeCheckState(FCultureTreeNodePtr Item) const;`
- L95 _private prototype_ `void SetCultureTreeNodeCheckState(ECheckBoxState CheckBoxState, FCultureTreeNodePtr Item);`
- L96 _private prototype_ `FText GetCultureDisplayName(FCultureTreeNodePtr Item) const;`
- L98 _private member_ `mutable bool bHasPaintedThisFrame = false;`
- L99 _private prototype_ `virtual int32 OnPaint( const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L101 _private member_ `bool bCultureListDirty = false;`
- L102 _private prototype_ `void RefreshCultureListInternal();`
- L103 _private prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`

#### struct `SCustomLaunchCultureListView::FCultureTreeNode`  
`struct FCultureTreeNode`  
_L42-46_
- L44 _public member_ `FString Name;`
- L45 _public member_ `TArray<TSharedPtr<FCultureTreeNode>> Children;`

#### enum `SCustomLaunchCultureListView::ELocalizationGroupFilter`  
`enum class ELocalizationGroupFilter : int32`  
_L58-67_
- L60 _public enumerator_ `All`
- L61 _public enumerator_ `Selected`
- L62 _public enumerator_ `EFIGS`
- L63 _public enumerator_ `CJK`
- L64 _public enumerator_ `Nordics`
- L66 _public enumerator_ `MAX`

#### struct `SCustomLaunchCultureListView::FLocalizationGroup`  
`struct FLocalizationGroup`  
_L70-80_
- L72 _public function_ `FLocalizationGroup( FText InDisplayName, const TArray<FString>& InLanguages ) : DisplayName(InDisplayName) , Languages(InLanguages)`
- L78 _public member_ `FText DisplayName;`
- L79 _public member_ `const TArray<FString>& Languages;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API PROJECTLAUNCHER_API`
- L20 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSelectionChanged, TArray<FString> );`

### `Plugins/Developer/ProjectLauncher/Source/ProjectLauncher/Public/Widgets/Shared/SCustomLaunchDeviceCombo.h` (Public)


#### class `SCustomLaunchDeviceCombo`  
`class SCustomLaunchDeviceCombo : public SCustomLaunchDeviceWidgetBase`  
_L12-38_
- inherits: `SCustomLaunchDeviceWidgetBase`
- L16 _public function_ `SLATE_BEGIN_ARGS(SCustomLaunchDeviceCombo) : _AllPlatforms(false)`
- L19 _public prototype_ `SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged);`
- L20 _public prototype_ `SLATE_ATTRIBUTE(TArray<FString>, SelectedDevices);`
- L21 _public prototype_ `SLATE_ATTRIBUTE(TArray<FString>, Platforms);`
- L26 _public prototype_ `void Construct( const FArguments& InArgs );`
- L30 _protected prototype_ `TSharedRef<SWidget> GenerateDeviceListWidget(TSharedPtr<FString> DeviceID) const;`
- L31 _protected prototype_ `void OnDeviceSelectionChanged(TSharedPtr<FString> DeviceID, ESelectInfo::Type InSelectInfo);`
- L32 _protected prototype_ `const FSlateBrush* GetSelectedDeviceBrush() const;`
- L33 _protected prototype_ `FText GetSelectedDeviceName() const;`
- L36 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FString>> > DeviceComboBox;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PROJECTLAUNCHER_API`

### `Plugins/Developer/ProjectLauncher/Source/ProjectLauncher/Public/Widgets/Shared/SCustomLaunchDeviceListView.h` (Public)


#### class `SCustomLaunchDeviceListView`  
`class SCustomLaunchDeviceListView : public SCustomLaunchDeviceWidgetBase`  
_L14-43_
- inherits: `SCustomLaunchDeviceWidgetBase`
- L18 _public function_ `SLATE_BEGIN_ARGS(SCustomLaunchDeviceListView) : _AllPlatforms(false) , _SingleSelect(false)`
- L22 _public prototype_ `SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged);`
- L23 _public prototype_ `SLATE_ATTRIBUTE(TArray<FString>, SelectedDevices);`
- L24 _public prototype_ `SLATE_ATTRIBUTE(TArray<FString>, Platforms);`
- L30 _public prototype_ `void Construct( const FArguments& InArgs );`
- L33 _protected member_ `bool bSingleSelect;`
- L35 _protected prototype_ `TSharedRef<ITableRow> GenerateDeviceRow(TSharedPtr<FString> DeviceID, const TSharedRef<STableViewBase>& OwnerTable);`
- L36 _protected prototype_ `ECheckBoxState IsDeviceChecked(TSharedPtr<FString> DeviceID) const;`
- L37 _protected prototype_ `void OnDeviceCheckStateChanged(ECheckBoxState NewState, TSharedPtr<FString> DeviceID);`
- L38 _protected prototype_ `virtual void OnDeviceListRefreshed() override;`
- L41 _private member_ `TSharedPtr<SListView<TSharedPtr<FString>>> DeviceListView;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PROJECTLAUNCHER_API`

### `Plugins/Developer/ProjectLauncher/Source/ProjectLauncher/Public/Widgets/Shared/SCustomLaunchDeviceWidgetBase.h` (Public)


#### class `SCustomLaunchDeviceWidgetBase`  
`class SCustomLaunchDeviceWidgetBase : public SCompoundWidget`  
_L18-50_
- inherits: `SCompoundWidget`
- L22 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnSelectionChanged, TArray<FString> );`
- L25 _public prototype_ `void Construct();`
- L26 _public prototype_ `~SCustomLaunchDeviceWidgetBase();`
- L28 _public prototype_ `void RefreshDeviceList();`
- L29 _public prototype_ `void OnSelectedPlatformChanged();`
- L32 _protected function_ `virtual void OnDeviceListRefreshed()`
- L34 _protected member_ `TAttribute<TArray<FString>> Platforms;`
- L35 _protected member_ `TAttribute<TArray<FString>> SelectedDevices;`
- L36 _protected member_ `FOnSelectionChanged OnSelectionChanged;`
- L37 _protected member_ `bool bAllPlatforms = false;`
- L39 _protected prototype_ `void OnDeviceProxyAdded(const TSharedRef<ITargetDeviceProxy>& DeviceProxy);`
- L40 _protected prototype_ `void OnDeviceProxyRemoved(const TSharedRef<ITargetDeviceProxy>& DeviceProxy);`
- L42 _protected prototype_ `const TSharedRef<ITargetDeviceProxyManager> GetDeviceProxyManager() const;`
- L44 _protected prototype_ `const PlatformInfo::FTargetPlatformInfo* GetPlatformInfoForDeviceID( const FString& DeviceID ) const;`
- L45 _protected prototype_ `FText GetDisplayNameForDevice( const TSharedPtr<FString>& DeviceID ) const;`
- L47 _protected member_ `TSet<FString> KnownDeviceIDs;`
- L48 _protected member_ `TArray<TSharedPtr<FString>> AllDeviceIDs;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PROJECTLAUNCHER_API`
- L13 _namespace_ `namespace PlatformInfo`
- L22 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSelectionChanged, TArray<FString> );`

### `Plugins/Developer/ProjectLauncher/Source/ProjectLauncher/Public/Widgets/Shared/SCustomLaunchMapListView.h` (Public)


#### enum `EMapSourceFlags`  
`enum class EMapSourceFlags : uint8`  
_L9-17_
- L11 _public enumerator_ `None = 0`
- L12 _public enumerator_ `MyDeveloperContent = 1 << 0`
- L13 _public enumerator_ `OtherDeveloperContent = 1 << 1`
- L14 _public enumerator_ `ProjectPlugins = 1 << 2`
- L15 _public enumerator_ `EngineContent = 1 << 3`
- L16 _public enumerator_ `EnginePlugins = 1 << 4`

#### class `SCustomLaunchMapListView`  
`class SCustomLaunchMapListView : public SCompoundWidget`  
_L26-102_
- inherits: `SCompoundWidget`
- L30 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnSelectionChanged, TArray<FString> );`
- L31 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnMapFilterChanged, EMapSourceFlags);`
- L33 _public function_ `SLATE_BEGIN_ARGS(SCustomLaunchMapListView)`
- L34 _public prototype_ `SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged);`
- L35 _public prototype_ `SLATE_ATTRIBUTE(TArray<FString>, SelectedMaps);`
- L42 _public prototype_ `void Construct( const FArguments& InArgs, TSharedRef<ProjectLauncher::FModel> InModel );`
- L44 _public prototype_ `void RefreshMapList();`
- L45 _public prototype_ `TSharedRef<SWidget> MakeControlsWidget();`
- L48 _protected member_ `TSharedPtr<ProjectLauncher::FModel> Model;`
- L49 _protected member_ `TAttribute<TArray<FString>> SelectedMaps;`
- L50 _protected member_ `TAttribute<FString> ProjectPath;`
- L51 _protected member_ `FOnSelectionChanged OnSelectionChanged;`
- L52 _protected member_ `FOnMapFilterChanged OnMapFilterChanged;`
- L55 _private member_ `bool bShowFolders = true;` — whether to display the available maps in a hierarchy or flat list
- L58 _private member_ `EMapSourceFlags MapSourceFlags = EMapSourceFlags::None;` — Content visibility flags (toggled via filter menu)
- L60 _private prototype_ `TSharedRef<SWidget> MakeFilterMenuContent();`
- L61 _private prototype_ `bool HasAnyFilterEnabled() const;`
- L70 _private typedef_ `typedef TSharedPtr<FMapTreeNode> FMapTreeNodePtr;`
- L72 _private member_ `FMapTreeNodePtr MapTreeRoot;`
- L74 _private prototype_ `void OnProjectChanged();`
- L77 _private prototype_ `void RefreshCheckBoxState( bool bExpand = false);`
- L78 _private prototype_ `ECheckBoxState RefreshCheckBoxStateRecursive(FMapTreeNodePtr Node, bool bExpand);`
- L79 _private prototype_ `void SetCheckBoxStateRecursive(FMapTreeNodePtr Node, ECheckBoxState CheckBoxState, TArray<FString>& CheckedMaps);`
- L81 _private prototype_ `void OnSearchFilterTextCommitted(const FText& SearchText, ETextCommit::Type InCommitType);`
- L82 _private prototype_ `void OnSearchFilterTextChanged(const FText& SearchText);`
- L84 _private member_ `FString CurrentFilterText;`
- L86 _private member_ `TSharedPtr<STreeView<FMapTreeNodePtr>> MapTreeView;`
- L87 _private member_ `TArray<FMapTreeNodePtr> MapTreeViewItemsSource;`
- L89 _private prototype_ `void GetMapTreeNodeChildren(FMapTreeNodePtr Item, TArray<FMapTreeNodePtr>& OutChildren);`
- L90 _private prototype_ `TSharedRef<ITableRow> GenerateMapTreeNodeRow(FMapTreeNodePtr Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L91 _private prototype_ `ECheckBoxState GetMapTreeNodeCheckState(FMapTreeNodePtr Item) const;`
- L92 _private prototype_ `void SetMapTreeNodeCheckState(ECheckBoxState CheckBoxState, FMapTreeNodePtr Item);`
- L93 _private prototype_ `const FSlateBrush* GetMapTreeNodeIcon(FMapTreeNodePtr Node) const;`
- L94 _private prototype_ `FSlateColor GetMapTreeNodeColor(FMapTreeNodePtr Node) const;`
- L96 _private member_ `mutable bool bHasPaintedThisFrame = false;`
- L97 _private prototype_ `virtual int32 OnPaint( const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L99 _private member_ `bool bMapListDirty = false;`
- L100 _private prototype_ `void RefreshMapListInternal();`
- L101 _private prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`

#### struct `SCustomLaunchMapListView::FMapTreeNode`  
`struct FMapTreeNode`  
_L63-69_
- L65 _public member_ `FString Name;`
- L66 _public member_ `ECheckBoxState CheckBoxState = ECheckBoxState::Unchecked;`
- L67 _public member_ `bool bFiltered = false;`
- L68 _public member_ `TArray<TSharedPtr<FMapTreeNode>> Children;`

#### Free symbols / members of external scopes

- L18 _prototype_ `ENUM_CLASS_FLAGS(EMapSourceFlags);`
- L20 _macro_ `#define UE_API PROJECTLAUNCHER_API`
- L30 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSelectionChanged, TArray<FString> );`
- L31 _delegate_ `DECLARE_DELEGATE_OneParam(FOnMapFilterChanged, EMapSourceFlags);`

### `Plugins/Developer/ProjectLauncher/Source/ProjectLauncher/Public/Widgets/Shared/SCustomLaunchPlatformCombo.h` (Public)


#### class `SCustomLaunchPlatformCombo`  
`class SCustomLaunchPlatformCombo : public SCompoundWidget`  
_L23-62_
- inherits: `SCompoundWidget`
- L27 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnSelectionChanged, TArray<FString> );`
- L29 _public function_ `SLATE_BEGIN_ARGS(SCustomLaunchPlatformCombo) : _TextStyle( &FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>( "NormalText" ) )`
- L32 _public prototype_ `SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged);`
- L33 _public prototype_ `SLATE_ATTRIBUTE(TArray<FString>, SelectedPlatforms);`
- L41 _public prototype_ `void Construct( const FArguments& InArgs);`
- L42 _public prototype_ `void RefreshPlatformsList();`
- L45 _protected member_ `TAttribute<TArray<FString>> SelectedPlatforms;`
- L46 _protected member_ `FOnSelectionChanged OnSelectionChanged;`
- L47 _protected member_ `TAttribute<bool> GetAdvancedPlatformsOption;`
- L48 _protected member_ `TAttribute<TSet<EBuildTargetType>> SupportedBuildTargets;`
- L49 _protected member_ `TSet<FString> BuildTargetGroupStarts;`
- L51 _protected prototype_ `TSharedRef<SWidget> OnGeneratePlatformListWidget( TSharedPtr<FString> Platform );`
- L52 _protected prototype_ `void OnPlatformSelectionChanged( TSharedPtr<FString> Platform, ESelectInfo::Type InSelectInfo );`
- L53 _protected prototype_ `const FSlateBrush* GetSelectedPlatformBrush() const;`
- L54 _protected prototype_ `FText GetSelectedPlatformName() const;`
- L55 _protected prototype_ `ECheckBoxState GetPlatformCheckState( const TSharedPtr<FString> Platform ) const;`
- L56 _protected prototype_ `void SetPlatformCheckState( ECheckBoxState CheckState, TSharedPtr<FString> Platform );`
- L57 _protected prototype_ `FSlateColor GetPlatformTextColor( const PlatformInfo::FTargetPlatformInfo* PlatformInfo );`
- L60 _protected member_ `TArray<TSharedPtr<FString>> PlatformsList;`
- L61 _protected member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> PlatformsComboBox;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API PROJECTLAUNCHER_API`
- L17 _namespace_ `namespace PlatformInfo`
- L27 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSelectionChanged, TArray<FString> );`

### `Plugins/Developer/ProjectLauncher/Source/ProjectLauncher/Public/Widgets/Shared/SCustomLaunchProjectCombo.h` (Public)


#### class `SCustomLaunchProjectCombo`  
`class SCustomLaunchProjectCombo : public SCompoundWidget`  
_L14-59_
- inherits: `SCompoundWidget`
- L18 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnSelectionChanged, FString );`
- L28 _public function_ `SLATE_BEGIN_ARGS(SCustomLaunchProjectCombo) : _ShowAnyProjectOption(false) , _CurrentProjectOption(ECurrentProjectOption::None) , _TextStyle( &FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>( "NormalText" ) )`
- L33 _public prototype_ `SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged);`
- L34 _public prototype_ `SLATE_ATTRIBUTE(FString, SelectedProject);`
- L35 _public prototype_ `SLATE_ATTRIBUTE(bool, HasProject);`
- L43 _public prototype_ `void Construct( const FArguments& InArgs);`
- L46 _protected member_ `TAttribute<FString> SelectedProject;`
- L47 _protected member_ `TAttribute<bool> HasProject;`
- L48 _protected member_ `FOnSelectionChanged OnSelectionChanged;`
- L49 _protected member_ `bool bShowAnyProjectOption;`
- L50 _protected member_ `ECurrentProjectOption CurrentProjectOption;`
- L52 _protected prototype_ `TSharedRef<SWidget> MakeProjectSelectionWidget();`
- L53 _protected prototype_ `void OnBrowseForProject();`
- L55 _protected prototype_ `FText GetProjectName() const;`
- L56 _protected prototype_ `void SetProjectPath(FString ProjectPath);`

#### enum `SCustomLaunchProjectCombo::ECurrentProjectOption`  
`enum class ECurrentProjectOption`  
_L20-25_
- L22 _public enumerator_ `None`
- L23 _public enumerator_ `ActualProject`
- L24 _public enumerator_ `Empty`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API PROJECTLAUNCHER_API`
- L18 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSelectionChanged, FString );`
