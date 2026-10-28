# Developer / AutomationWindow

- module root: `Source/Developer/AutomationWindow`
- headers: 12; symbols: 426
- symbol kinds: class=17, delegate=4, enum=2, enumerator=5, function=65, macro=4, member=104, namespace=4, prototype=205, struct=2, typedef=3, variable=11
- PrivateDependencyModuleNames: ApplicationCore, AutomationTest, CoreUObject, DesktopPlatform, EditorFramework, Engine, InputCore, Json, JsonUtilities, Kismet, Slate, SlateCore, SourceControl, ToolWidgets, UnrealEd
- PrivateIncludePathModuleNames: SessionServices
- PublicDependencyModuleNames: AutomationController, Core

### `Source/Developer/AutomationWindow/Private/AutomationPresetManager.h` (Private)


#### struct `FAutomationTestPreset`  
`struct FAutomationTestPreset`  
_L22-107_
- reflection: `USTRUCT()`
- desc: Class that holds preset data for the automation window
- L29 _public function_ `FAutomationTestPreset()` — Default constructor.
- L34 _public function_ `FAutomationTestPreset(FName NewPresetId) : Id(NewPresetId)` — New Preset constructor.
- L40 _public prototype_ `virtual ~FAutomationTestPreset( ) = default;` — Destructor.
- L45 _public function_ `FName GetID() const` — Gets the unique preset id for this preset.
- L56 _public function_ `const FText& GetName() const` — Gets the name for this preset. @return The preset's name. @see GetID, SetPresetName
- L67 _public function_ `void SetName(const FText& InPresetName)` — Sets the name for this preset. @param InPresetName The name to set. @see GetPresetName
- L78 _public function_ `const TArray<FString>& GetEnabledTests() const` — Returns the list of enabled tests. @return Collection of tests. @see SetEnabledTests
- L89 _public function_ `void SetEnabledTests(TArray<FString> NewEnabledTests)` — Sets the list of enabled tests. @param NewEnableDtests The collection of tests to enable. @see GetEnabledTests
- L98 _private member_ `FName Id;` — `UPROPERTY()` — The unique name for this preset.
- L102 _private member_ `FText Name;` — `UPROPERTY()` — The name of this preset.
- L106 _private member_ `TArray<FString> EnabledTests;` — `UPROPERTY()` — The list of enabled test names.

#### class `FAutomationTestPresetManager`  
`class FAutomationTestPresetManager`  
_L110-178_
- L115 _public prototype_ `FAutomationTestPresetManager();` — Default constructor.
- L118 _public prototype_ `virtual ~FAutomationTestPresetManager() = default;` — Virtual destructor.
- L125 _public prototype_ `virtual AutomationPresetPtr AddNewPreset( const FText& PresetName, const TArray<FString>& SelectedTests );` — Creates a new preset with the given name and enabled tests. @param PresetName The name of the new preset. @param SelectedTests The list of enabled tests.
- L130 _public prototype_ `virtual TArray<AutomationPresetPtr>& GetAllPresets( );` — Returns a reference to the list that holds the presets.
- L138 _public prototype_ `void RemovePreset( const AutomationPresetRef Preset );` — Removes the selected preset from the preset list and deletes the file on disk. @param Preset The preset to remove. @see LoadPresets, SavePreset
- L146 _public prototype_ `bool SavePreset( const AutomationPresetRef Preset);` — Saves the passed in preset to disk. @param Preset The preset to save. @see RemovePreset, LoadPresets
- L153 _public prototype_ `void LoadPresets( );` — Load all Presets from disk. @see RemovePreset, SavePreset
- L162 _protected prototype_ `AutomationPresetPtr LoadPreset( FArchive& Archive );` — Creates a new preset and loads it with data from the archive. @param Archive The stream to read the preset data from.
- L169 _protected function_ `static FString GetPresetFolder()` — Gets the folder in which preset files are stored. @return The folder path.
- L177 _private member_ `TArray<AutomationPresetPtr> Presets;` — Holds the collection of automation presets.

#### Free symbols / members of external scopes

- L13 _typedef_ `typedef TSharedPtr<struct FAutomationTestPreset> AutomationPresetPtr;` — Type definition for shared pointers to instances of FAutomationTestPreset.
- L16 _typedef_ `typedef TSharedRef<struct FAutomationTestPreset> AutomationPresetRef;` — Type definition for shared references to instances of FAutomationTestPreset.

### `Source/Developer/AutomationWindow/Private/AutomationWindowStyle.h` (Private)


#### class `FAutomationWindowStyle`  
`class FAutomationWindowStyle : public FSlateStyleSet`  
_L10-26_
- inherits: `FSlateStyleSet`
- L14 _public prototype_ `virtual const FName& GetStyleSetName() const override;`
- L16 _public prototype_ `static const FAutomationWindowStyle& Get();`
- L17 _public prototype_ `static void Shutdown();`
- L19 _public prototype_ `~FAutomationWindowStyle();`
- L22 _private prototype_ `FAutomationWindowStyle();`
- L24 _private member_ `static FName StyleName;`
- L25 _private member_ `static TUniquePtr<FAutomationWindowStyle> Inst;`

### `Source/Developer/AutomationWindow/Private/SAutomationExportMenu.h` (Private)


#### class `SAutomationExportMenu`  
`class SAutomationExportMenu : public SCompoundWidget`  
_L17-145_
- inherits: `SCompoundWidget`
- L22 _public prototype_ `SAutomationExportMenu();` — Default constructor.
- L24 _public function_ `SLATE_BEGIN_ARGS( SAutomationExportMenu )`
- L25 _public prototype_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TSharedRef<SNotificationList>& InNotificationList );`
- L41 _private prototype_ `bool AreReportsGenerated() const;` — Have the reports been generated @return true if the reports have been generated
- L49 _private prototype_ `void BuildMenuItems( const FText& InName, EFileExportType::Type InType );` — Build the menu items. @param InName The menu item name. @param InType The menu item type.
- L52 _private prototype_ `void CreateMenu( );` — Create the menu widgets.
- L57 _private prototype_ `void EnableAvailableReports();` — Set all the available export options to checked.
- L64 _private prototype_ `FText GetExportButtonTooltip() const;` — Get the export button tooltip. @return true export report is ready.
- L71 _private prototype_ `FText GetExportComboButtonTooltip() const;` — Get the export combo button tooltip. @return true export report is ready.
- L74 _private prototype_ `void GetResults( );` — Get the test result summary from the manager.
- L81 _private prototype_ `FReply HandleExportDataClicked();` — Export the report data when clicked. @return handled if the report has been handled.
- L86 _private prototype_ `void HandleMenuOpen();` — Called when the menu button is opened. Gets the results, and generates the widgets.
- L94 _private prototype_ `bool IsCheckBoxEnabled( EFileExportType::Type CheckType ) const;` — Should the export checkboxes be enabled. @param CheckType The menu item type. @return true if the checkbox is enabled .
- L101 _private prototype_ `bool IsExportReady() const;` — Is an export report ready. @return true export report is ready.
- L109 _private prototype_ `void OnDisplayCheckStateChanged( ECheckBoxState InNewState, EFileExportType::Type CheckType );` — Check box has changed, update the export data mask . @param The new state, checked or unchecked. @param The type of checkbox set.
- L117 _private prototype_ `ECheckBoxState OnGetDisplayCheckState( EFileExportType::Type CheckType ) const;` — Gets the display state to send to a display filter check box @param The type of checkbox. @return The desired checkbox state.
- L124 _private prototype_ `FReply SpawnNotification();` — Add a notification when the file is exported. @return true export report is ready.
- L129 _private member_ `TSharedPtr< SButton > ExportButton;` — The export button
- L132 _private member_ `TSharedPtr< SComboButton > ExportMenuComboButton;` — The combo button
- L135 _private member_ `uint32 FileExportTypeMask;` — Holds the file export mask for deciding which reports to output e.g. only errors
- L138 _private member_ `TSharedPtr< SVerticalBox > MenuHolderBox;` — Box to hold the menu items
- L141 _private member_ `TSharedPtr< SNotificationList > NotificationListPtr;` — The list of active system messages
- L144 _private member_ `uint32 ResultMask;` — Holds the result mask generated by the report manager

### `Source/Developer/AutomationWindow/Private/SAutomationGraphicalResultBox.h` (Private)


#### enum `EAutomationGrapicalDisplayType::Type`  
`enum Type`  
_L18-22_
- L20 _public enumerator_ `DisplayName`
- L21 _public enumerator_ `DisplayTime`

#### class `SAutomationGraphicalResultBox`  
`class SAutomationGraphicalResultBox : public SCompoundWidget`  
_L29-213_
- inherits: `SCompoundWidget`
- desc: Implements the automation graphical results box widget.
- L34 _public function_ `SLATE_BEGIN_ARGS(SAutomationGraphicalResultBox)`
- L36 _public prototype_ `SLATE_ARGUMENT(FString, Text) SLATE_END_ARGS() virtual ~SAutomationGraphicalResultBox();`
- L50 _public prototype_ `void Construct( const FArguments& InArgs, const IAutomationControllerManagerRef& InAutomationController);` — Construct this widget. @param InArgs The declaration data for this widget. @param InAutomationController Reference to the automation controller.
- L53 _public prototype_ `void ClearResults();` — Clears the current results and any widgets that were created
- L56 _public prototype_ `bool HasResults() const;` — Returns if there are any results available to display.
- L59 _public prototype_ `EAutomationGrapicalDisplayType::Type GetDisplayType() const;` — Returns the current display type.
- L66 _public prototype_ `void SetDisplayType(EAutomationGrapicalDisplayType::Type NewDisplayType);` — Sets the current display type @param NewDisplayType The display type to set.
- L172 _private prototype_ `void GetEnabledReports(TSharedPtr<IAutomationReport> InReport, TArray< TSharedPtr< IAutomationReport > >& OutReports);` — Returns if there are any results available to display. @param InReport The report to recursively check for enabled tests. @param OutReports The list of enabled test reports.
- L175 _private prototype_ `void PopulateData();` — Populates the ClusterResults with test data pulled from the automation controller
- L178 _private prototype_ `void CreateWidgets();` — Creates all the slate widgets to display the test results
- L181 _private prototype_ `void OnFillResults();` — This is called when the tests are complete so we can update the widget
- L189 _private prototype_ `FSlateColor GetColorForTestState(const EAutomationState TestState, const bool bHasWarnings) const;` — Gets the color for a test based off the test state and if it has any warnings. @param TestState The test state from the automation report (Success, Fail, NotRun, etc.) @param bHasWarnings If the test had any warning logs.
- L197 _private prototype_ `FText GetTestDisplayText(const FString TestName, const float TestTime) const;` — Gets the text to display for this test item based off the current DisplayType. @param TestName The name of the test. @param TestTime The duration of the test.
- L200 _private member_ `EAutomationGrapicalDisplayType::Type DisplayType;` — Stores what information should be displayed on the test widgets.
- L203 _private member_ `TArray<FClusterResults> ClusterResults;` — The test results grouped by cluster.
- L206 _private member_ `float TotalTestDuration;` — The time of the longest cluster.
- L209 _private member_ `TSharedPtr< SVerticalBox > RootBox;` — Pointer to the root widget that contains all the result widgets.
- L212 _private member_ `IAutomationControllerManagerPtr AutomationController;` — Pointer to the automation controller so we can get the test results.

#### class `SAutomationGraphicalResultBox::FTestResults`  
`class FTestResults`  
_L71-94_
- desc: Holds information on a single test result
- L75 _public function_ `FTestResults(const FString& InName)` — Constructor
- L84 _public member_ `FString TestName;` — Name of the test
- L87 _public member_ `float Duration;` — Duration of the test
- L90 _public member_ `EAutomationState TestState;` — State of the test
- L93 _public member_ `bool bHasWarnings;` — If the test had any warnings

#### class `SAutomationGraphicalResultBox::FDeviceResults`  
`class FDeviceResults`  
_L97-127_
- desc: Holds all the test results for a single device
- L101 _public function_ `FDeviceResults(const FGuid& InGameInstanceId, const FString& InGameInstanceName)` — Constructor
- L111 _public member_ `FString GameInstanceName;` — The game instance Name running on the Device
- L114 _public member_ `FString GameInstanceId;` — The game instance Id running on the Device
- L117 _public member_ `float TotalTime;` — Total time of all the tests
- L120 _public member_ `uint32 TotalTestSkips;` — How many of the tests were skipped
- L123 _public member_ `uint32 TotalTestSuccesses;` — How many of the tests were successful
- L126 _public member_ `TArray<FTestResults> Tests;` — The list of tests

#### class `SAutomationGraphicalResultBox::FClusterResults`  
`class FClusterResults`  
_L130-164_
- desc: Holds all the results for a single cluster
- L134 _public function_ `FClusterResults(const FString& InName)` — Constructor
- L145 _public member_ `FString ClusterName;` — Name of the Cluster
- L148 _public member_ `uint32 TotalNumTests;` — Total number of tests
- L151 _public member_ `uint32 TotalTestSkips;` — How many of the tests were skipped
- L154 _public member_ `uint32 TotalTestSuccesses;` — How many of the tests were successful
- L157 _public member_ `float TotalTime;` — Total time of all the tests
- L160 _public member_ `float ParallelTime;` — Longest time a device took to finish its tests
- L163 _public member_ `TArray <FDeviceResults> Devices;` — The list of devices in this cluster

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace EAutomationGrapicalDisplayType`

### `Source/Developer/AutomationWindow/Private/SAutomationTestItem.h` (Private)


#### class `SAutomationTestItem`  
`class SAutomationTestItem : public SMultiColumnTableRow< TSharedPtr<FString> >`  
_L24-250_
- inherits: `SMultiColumnTableRow<TSharedPtr<FString>>`
- desc: Implements a row widget for the automation list.
- L27 _public function_ `SLATE_BEGIN_ARGS(SAutomationTestItem)`
- L45 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView );` — Construct this widget.  Called by the SNew() Slate macro. @param	InArgs	          Declaration used by the SNew() macro to construct this widget. @param   InOwnerTableView  The owner table into which this row is being placed.
- L53 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn( const FName& ColumnName ) override;` — Generates the widget for the specified column. @param ColumnName The name of the column to generate the widget for. @return The widget.
- L62 _protected prototype_ `FSlateColor GetFilterStatusTextColor( ) const;` — Returns filter status color. @return filter color.
- L69 _protected prototype_ `const FSlateBrush* GetSmokeTestImage( ) const;` — Returns icon for "fast" tests, parents of fast tests, or empty for a slow test. @return the smoke test image.
- L77 _protected prototype_ `FText GetTestToolTip( int32 ClusterIndex ) const;` — Returns the tool tip for the automation test result. @param ClusterIndex The cluster index. @return The tooltip text.
- L84 _protected prototype_ `ECheckBoxState IsTestEnabled() const;` — Is the test enabled. @return true if the test is enabled.
- L91 _protected prototype_ `EVisibility IsToBeSkipped_GetVisibility() const;` — Is the test inside exclude list. This info is taken from Config/DefaultEngine.ini, section [AutomationTestExcludelist]. Return the visibility state based on skipped state.
- L98 _protected prototype_ `FSlateColor IsToBeSkipped_GetColorAndOpacity() const;` — Change opacity of skipped button if it is hovered. Return the Linear Color with different opacity based on hovered status.
- L105 _protected prototype_ `bool IsDirectlyExcluded() const;` — Is the test inside exclude list through direct exclusion (not through propagation). @return true if the test is inside the exclude list by direct exclusion.
- L110 _protected prototype_ `EVisibility IsDirectlyExcluded_GetVisibility() const;` — Return the visibility state based on exclude state.
- L117 _protected prototype_ `FText GetExcludeReason() const;` — Reason for the exclusion @return the exclusion reason
- L124 _protected prototype_ `FReply SetSkipFlag();` — Add or remove test from exclude list. It will change Config/DefaultEngine.ini, section [AutomationTestExcludelist]. @return respond of dialog
- L131 _protected prototype_ `bool CanSkipFlagBeChanged() const;` — Can the test skip flag be changed. @return true if the test skip flag can be changed.
- L138 _protected prototype_ `FReply OnEditExcludeOptionsClicked();` — Open Exclude test options editor @return respond of dialog
- L143 _protected prototype_ `EVisibility CanEditTags_GetVisibility() const;` — Returns whether of not test tags can be edited on test.
- L150 _protected prototype_ `FReply OnEditTestTagsClicked();` — Open Test Tags editor. @return Editor reply result.
- L158 _protected prototype_ `FSlateColor ItemStatus_BackgroundColor( const int32 ClusterIndex ) const;` — Returns color that indicates test status per cluster. @param ClusterIndex The cluster index. @return The background Color.
- L165 _protected prototype_ `FText ItemStatus_DurationText( ) const;` — Returns color the duration the test ran for. @return The duration the test took as text.
- L174 _protected prototype_ `EVisibility ItemStatus_GetStatusVisibility( const int32 ClusterIndex, const bool bForInProcessThrobber ) const;` — Helper to ensure throbber is visible when in process and icon is visible otherwise. @param ClusterIndex The cluster index. @param bForInProcessThrobber If throbbing is in process. @return The visibility state.
- L183 _protected prototype_ `EVisibility ItemStatus_GetChildrenStatusVisibility( const int32 ClusterIndex, const bool bForInProcessThrobber ) const;` — Helper for internal nodes to ensure throbber is visible when children are in process and icon is visible when children completed. @param ClusterIndex The cluster index. @param bForInProcessThrobber If throbbing is in process. @return The visibility state.
- L191 _protected prototype_ `FSlateColor ItemStatus_ProgressColor( const int32 ClusterIndex ) const;` — Color of progress bar for internal tree test nodes. @param ClusterIndex The cluster index. @return The progress bar color.
- L199 _protected prototype_ `TOptional<float> ItemStatus_ProgressFraction( const int32 ClusterIndex ) const;` — Returns percent completion for an internal tree node for all enabled child tests. @param ClusterIndex The cluster index. @return The percent complete.
- L207 _protected prototype_ `const FSlateBrush* ItemStatus_StatusImage( const int32 ClusterIndex ) const;` — Returns image that denotes the status of a particular test on the given platform cluster. @param ClusterIndex The cluster index. @return the status image.
- L215 _protected prototype_ `const FSlateBrush* ItemChildrenStatus_StatusImage(const int32 ClusterIndex) const;` — Returns image that denotes the status of a test category as implied by its children, on the given platform cluster. @param ClusterIndex The cluster index. @return the status image.
- L222 _protected prototype_ `FText ItemStatus_NumParticipantsRequiredText( ) const;` — The number of participants required for this test item in string form. @return The number of participants needed.
- L227 _private prototype_ `void HandleTestingCheckbox_Click( ECheckBoxState );` — Handle the testing checkbox click.
- L232 _private member_ `float ColumnWidth;` — The column width.
- L235 _private member_ `bool IsLocalSession;` — Is Session local.
- L238 _private member_ `bool bIsToBeSkippedButtonHovered = false;` — Is Skip button hovered.
- L241 _private member_ `TAttribute<FText> HighlightText;` — Holds the highlight string for the automation test.
- L244 _private member_ `TSharedPtr<IAutomationReport> TestStatus;` — Holds the automation report.
- L247 _private member_ `FOnItemCheckedStateChanged OnCheckedStateChangedDelegate;` — Holds a delegate to be invoked when the check box state changed.
- L249 _private member_ `SHorizontalBox::FSlot* TagsSlot;`

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_DELEGATE_OneParam(FOnItemCheckedStateChanged, TSharedPtr<IAutomationReport> );`
- L19 _prototype_ `DECLARE_DELEGATE_OneParam(FOnItemCheckedStateChanged, TSharedPtr<IAutomationReport> );`

### `Source/Developer/AutomationWindow/Private/SAutomationTestItemContextMenu.h` (Private)


#### class `SAutomationTestItemContextMenu`  
`class SAutomationTestItemContextMenu : public SCompoundWidget`  
_L23-106_
- inherits: `SCompoundWidget`
- L28 _public function_ `SLATE_BEGIN_ARGS(SAutomationTestItemContextMenu)`
- L39 _public function_ `void Construct( const FArguments& InArgs, const TArray<FString>& InAssetNames, const TArray<FString>& InTestNames )` — Construct this widget. @param InArgs The declaration data for this widget. @param InSessionManager The session to use.
- L62 _protected function_ `TSharedRef<SWidget> MakeContextMenu( )` — Builds the context menu widget. @return The context menu.
- L85 _private function_ `void HandleContextItemTerminate( )` — Handle the context menu closing down. If an asset is selected, request that it gets loaded
- L94 _private function_ `void HandleContextItemCopyName()` — Handle the context menu closing down. Copy the test names to clipboard
- L102 _private member_ `TArray<FString> AssetNames;` — Holds the selected asset name.
- L105 _private member_ `TArray<FString> TestNames;` — /  Holds the test names.

#### Free symbols / members of external scopes

- L21 _macro_ `#define LOCTEXT_NAMESPACE "SAutomationTestItemContextMenu"`

### `Source/Developer/AutomationWindow/Private/SAutomationTestTagEditor.h` (Private)


#### class `STestNameAndTagTableRow`  
`class STestNameAndTagTableRow : public SMultiColumnTableRow<TSharedPtr<FString>>`  
_L46-94_
- inherits: `SMultiColumnTableRow<TSharedPtr<FString>>`
- L49 _public function_ `SLATE_BEGIN_ARGS(STestNameAndTagTableRow)`
- L50 _public function_ `SLATE_ARGUMENT(TSharedPtr<IAutomationReport>, TestReport) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView)`
- L61 _public function_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override`
- L93 _private member_ `IAutomationReportPtr TestReport;`

#### class `SAutomationTestTagEditor`  
`class SAutomationTestTagEditor : public SCompoundWidget`  
_L98-454_
- inherits: `SCompoundWidget`
- L103 _public function_ `SLATE_BEGIN_ARGS(SAutomationTestTagEditor)`
- L113 _public function_ `void Construct(const FArguments& InArgs, const TArray<IAutomationReportPtr>& InTestReports)` — Construct this widget. @param InArgs The declaration data for this widget.
- L252 _public function_ `static void ShowInWindow(const TSharedRef<const SWidget> InParentWindow, const TArray<TSharedPtr<IAutomationReport>>& InTestReports, const FOnTestTagsSavedEvent& OnTestTagsSaved)`
- L279 _public function_ `void SetOnTestTagsSavedEvent(const FOnTestTagsSavedEvent& Event)`
- L285 _private function_ `void AddTagToListBox(const FString& InTag)`
- L291 _private function_ `FReply OnAddButtonClicked()`
- L301 _private function_ `void TagSuggestionBox_SetText(const FText& NewText, ETextCommit::Type CommitInfo)`
- L309 _private function_ `void TagSuggestionBox_TextChanged(const FText& NewText)`
- L314 _private function_ `void TagSuggestionBox_GetSuggestions(const FString& CurrText, TArray<FString>& OutSuggestions)`
- L319 _private function_ `FReply OnDiscardButtonClicked()`
- L339 _private function_ `bool SaveButonEnabled() const`
- L345 _private function_ `FReply OnSaveButtonClicked()`
- L439 _private function_ `TSharedRef<ITableRow> OnGenerateTestNameAndTagRow(TSharedPtr<IAutomationReport> InTestReport, const TSharedRef<STableViewBase>& OwnerTable)`
- L444 _private function_ `void OnGetTestNameAndTagChildren(TSharedPtr<IAutomationReport> InItem, TArray<TSharedPtr<IAutomationReport>>& OutItems)`
- L449 _private member_ `TSharedPtr<SSuggestionTextBox> TagSuggestionBox;`
- L450 _private member_ `TSharedPtr<SAutomationTestTagListBox> TagListBox;`
- L451 _private member_ `TSharedPtr<SButton> AddButton;`
- L452 _private member_ `TArray<IAutomationReportPtr> TestReports;`
- L453 _private member_ `FOnTestTagsSavedEvent OnTestTagsSavedEvent;`

#### Free symbols / members of external scopes

- L36 _macro_ `#define LOCTEXT_NAMESPACE "SAutomationTestTagEditor"`
- L38 _prototype_ `DEFINE_LOG_CATEGORY_STATIC(LogAutomationTestTagEditor, Log, All);`
- L40 _namespace_ `namespace TestNameAndTagTableConstants`
- L42 _variable_ `const FName Name(TEXT("Name` (scope `TestNameAndTagTableConstants`)
- L43 _variable_ `const FName Tags(TEXT("Tags` (scope `TestNameAndTagTableConstants`)
- L70 _function_ `` (scope `STestNameAndTagTableRow::GenerateWidgetForColumn`)
- L96 _delegate_ `DECLARE_DELEGATE(FOnTestTagsSavedEvent);`
- L96 _prototype_ `DECLARE_DELEGATE(FOnTestTagsSavedEvent);`
- L316 _function_ `OutSuggestions = FAutomationTestFramework::Get().GetAllExistingTags().Array().FilterByPredicate([&CurrText](const FString& CurrentTag) { return CurrentTag.Contains(CurrText); });` (scope `SAutomationTestTagEditor::TagSuggestionBox_GetSuggestions`)
- L406 _function_ `` (scope `SAutomationTestTagEditor::OnSaveButtonClicked`)

### `Source/Developer/AutomationWindow/Private/SAutomationTestTagFilter.h` (Private)


#### class `SAutomationTestTagFilter`  
`class SAutomationTestTagFilter : public SCompoundWidget`  
_L35-164_
- inherits: `SCompoundWidget`
- L40 _public function_ `SLATE_BEGIN_ARGS(SAutomationTestTagFilter)`
- L50 _public function_ `void Construct(const FArguments& InArgs, TSharedPtr<FAutomationGroupFilter> InAutomationTagFilter)` — Construct this widget. @param InArgs The declaration data for this widget.
- L120 _public function_ `FReply OnApplyTagFilterButtonClicked()`
- L132 _public function_ `FReply OnRemoveTagFilterButtonClicked()`
- L138 _public function_ `void ApplyTagFilter(const FString& TagFilter)`
- L145 _public function_ `void SetOnTestFilterAppliedEvent(const FOnTestFilterAppliedEvent& OnTestFilterAppliedEvent)`
- L150 _public function_ `void ClearFilter()`
- L159 _protected member_ `TSharedPtr<FAutomationGroupFilter> AutomationTagFilter;`
- L160 _protected member_ `FOnTestFilterAppliedEvent OnTestFilterApplied;`
- L161 _protected member_ `TSharedPtr<SEditableTextBox> FilterText;`
- L162 _protected member_ `TSharedPtr<SLayeredImage> FilterButtonImage;`
- L163 _protected member_ `bool IsFilterApplied;`

#### Free symbols / members of external scopes

- L31 _macro_ `#define LOCTEXT_NAMESPACE "SAutomationTestTagFilter"`
- L33 _delegate_ `DECLARE_DELEGATE(FOnTestFilterAppliedEvent);`
- L33 _prototype_ `DECLARE_DELEGATE(FOnTestFilterAppliedEvent);`
- L79 _function_ `` (scope `SAutomationTestTagFilter::Construct`)

### `Source/Developer/AutomationWindow/Private/SAutomationTestTagListBox.h` (Private)


#### class `SAutomationTestTagItem`  
`class SAutomationTestTagItem : public SCompoundWidget`  
_L25-106_
- inherits: `SCompoundWidget`
- L30 _public function_ `SLATE_BEGIN_ARGS(SAutomationTestTagItem)`
- L40 _public function_ `void Construct(const FArguments& InArgs, const FString& InTag, const bool InIsNew, const bool InImmutable)` — Construct this widget. @param InArgs The declaration data for this widget.
- L89 _public function_ `bool IsMarkedForDeletion()`
- L94 _public function_ `FString GetTagValue()`
- L100 _protected prototype_ `FReply ToggleTagDeletion();`
- L102 _protected member_ `TSharedPtr<SBorder> MainBorder;`
- L103 _protected member_ `bool IsNew;`
- L104 _protected member_ `bool MarkedForDeletion;`
- L105 _protected member_ `FString TagValue;`
- L210 _function_ `inline FReply SAutomationTestTagItem::ToggleTagDeletion()`

#### class `SAutomationTestTagListBox`  
`class SAutomationTestTagListBox : public SCompoundWidget`  
_L108-207_
- inherits: `SCompoundWidget`
- L113 _public function_ `SLATE_BEGIN_ARGS(SAutomationTestTagListBox)`
- L124 _public function_ `void Construct( const FArguments& InArgs, TArray<FString>& InExistingTags, TSet<FString> InImmutableTags )` — Construct this widget. @param InArgs The declaration data for this widget. @param InCurrentTestStatus The current test report pointer.
- L147 _public function_ `void AddTag(const FString& TestTag, bool IsNew, bool IsImmutable)`
- L177 _public function_ `TArray<FString> GetNewTags()`
- L182 _public function_ `int32 RemoveNewTagsItem(const FString &ItemToRemove)`
- L187 _public function_ `TArray<FString> GetMarkForDeleteTags()`
- L204 _private member_ `TArray<FString> ExistingTags;`
- L205 _private member_ `TArray<FString> NewTags;`
- L206 _private member_ `TSharedPtr<SWrapBox> TagBox;`

#### Free symbols / members of external scopes

- L21 _macro_ `#define LOCTEXT_NAMESPACE "SAutomationTestTagListBox"`
- L23 _prototype_ `DEFINE_LOG_CATEGORY_STATIC(LogAutomationTestTagListBox, Log, All);`
- L151 _function_ `` (scope `SAutomationTestTagListBox::AddTag`)
- L191 _function_ `` (scope `SAutomationTestTagListBox::GetMarkForDeleteTags`)

### `Source/Developer/AutomationWindow/Private/SAutomationWindow.h` (Private)


#### enum `EAutomationTestBackgroundStyle::Type`  
`enum Type`  
_L54-59_
- L56 _public enumerator_ `Unknown`
- L57 _public enumerator_ `Editor`
- L58 _public enumerator_ `Game`

#### class `SAutomationWindow`  
`class SAutomationWindow : public SCompoundWidget`  
_L66-700_
- inherits: `SCompoundWidget`
- desc: Implements the main UI Window for hosting all automation tests.
- L71 _private typedef_ `typedef TTextFilter< const TSharedPtr< class IAutomationReport >& > AutomationReportTextFilter;` — The automation text filter - used for updating the automation report list
- L92 _public function_ `SLATE_BEGIN_ARGS( SAutomationWindow )`
- L98 _public prototype_ `SAutomationWindow();` — Default constructor.
- L101 _public prototype_ `virtual ~SAutomationWindow();` — Destructor.
- L108 _public prototype_ `void Construct(const FArguments& InArgs, const IAutomationControllerManagerRef& AutomationController, const TSharedRef<ISessionManager>& InSessionManager);` — Constructs the widget.
- L115 _public prototype_ `bool IsAutomationControllerIdle() const;` — Check tests aren't running. @return true if the tests aren't running.
- L118 _public prototype_ `static TArray<FString> SaveExpandedTestNames(TSet<TSharedPtr<IAutomationReport>> ExpandedItems);` — Save the currently selected tests and expanded items so they can be reapplied later
- L121 _public prototype_ `static void ExpandItemsInList(TSharedPtr<STreeView<TSharedPtr<IAutomationReport>>> InTestTable, TSharedPtr<IAutomationReport> InReport, TArray<FString> ItemsToExpand);` — Expanded the given item if its name is in the array of strings given.
- L124 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — Override base class Tick
- L133 _protected function_ `bool AreMultipleRowsSelected()` — Checks the list of selected rows to see if multiple rows are selected. @return true if multiple rows are selected.
- L140 _protected prototype_ `void ChangeTheSelectionToThisRow(TSharedPtr< IAutomationReport > ThisRow);` — Change the selection to a given row @param ThisRow a Report in the list of all reports
- L148 _protected prototype_ `bool IsRowSelected(TSharedPtr< IAutomationReport > ThisRow);` — Tests if the given row is in the list of selected rows. @param ThisRow a Report in the list of all report. @return true if the report passed in is in the list of selected rows.
- L155 _protected prototype_ `void SetAllSelectedTestsChecked( bool InChecked );` — Sets the enabled value of the selected rows to given value. @param InChecked Set all the selected rows to the enabled state to this value.
- L162 _protected prototype_ `bool IsAnySelectedRowEnabled();` — Checks the list of selected rows to see if any are enabled. @return true if any of the selected rows are enabled.
- L165 _protected prototype_ `virtual FReply OnKeyDown( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override;` — Overridden from SWidget: Called when a key is pressed down - capturing copy.
- L168 _protected prototype_ `virtual FReply OnKeyUp( const FGeometry& InGeometry, const FKeyEvent& InKeyEvent ) override;` — Overridden from SWidget: Called after a key is released.
- L177 _private prototype_ `void HandleItemCheckBoxCheckedStateChanged( TSharedPtr< IAutomationReport > TestStatus );` — Handle for a test item's check box being clicked. @param TestStatus The test row details.
- L180 _private prototype_ `bool HandleItemCheckBoxIsEnabled( ) const;` — Callback for getting the enabled state of a test item.
- L183 _private prototype_ `bool HandleMainContentIsEnabled() const;` — Callback for getting the enabled state of the main content overlay.
- L186 _private prototype_ `void CreateCommands();` — Create the UI commands for the toolbar
- L193 _private prototype_ `static TSharedRef< SWidget > MakeAutomationWindowToolBar( const TSharedRef<FUICommandList>& InCommandList, TSharedPtr<class SAutomationWindow> InLevelEditor );` — Static: Creates a toolbar widget for the main automation window. @return The new widget.
- L194 _private prototype_ `TSharedRef< SWidget > MakeAutomationWindowToolBar( const TSharedRef<FUICommandList>& InCommandList );`
- L201 _private prototype_ `static TSharedRef< SWidget > MakeAutomationFilterToolBar(const TSharedRef<FUICommandList>& InCommandList, TSharedPtr<class SAutomationWindow> InLevelEditor);` — Static: Creates a filter toolbar widget for the automation window. @return The new widget.
- L202 _private prototype_ `TSharedRef< SWidget > MakeAutomationFilterToolBar(const TSharedRef<FUICommandList>& InCommandList);`
- L209 _private prototype_ `static TSharedRef< SWidget >GenerateTestsOptionsMenuContent( TWeakPtr<class SAutomationWindow> InAutomationWindow );` — Static: Creates the test options menu widget. @return	The new widget.
- L210 _private prototype_ `TSharedRef< SWidget > GenerateTestsOptionsMenuContent( );`
- L217 _private prototype_ `static TSharedRef< SWidget >GenerateGroupOptionsMenuContent( TWeakPtr<class SAutomationWindow> InAutomationWindow );` — Static: Creates the group flag options menu widget. @return The new widget.
- L218 _private prototype_ `TSharedRef< SWidget > GenerateGroupOptionsMenuContent( );`
- L225 _private prototype_ `static TSharedRef< SWidget >GeneratePresetsMenuContent( TWeakPtr<class SAutomationWindow> InAutomationWindow );` — Static: Creates the Presets menu widget. @return The new widget.
- L226 _private prototype_ `TSharedRef< SWidget > GeneratePresetsMenuContent();`
- L233 _private prototype_ `static TSharedRef< SWidget > GenerateTestHistoryMenuContent(TWeakPtr<class SAutomationWindow> InAutomationWindow);` — Static: Creates the test history options menu widget. @return The new widget.
- L234 _private prototype_ `TSharedRef< SWidget > GenerateTestHistoryMenuContent();`
- L241 _private prototype_ `TSharedRef<SWidget> GenerateRequestedFilterComboItem(TSharedPtr<FString> InItem);` — Creates a combo item for the requested filter. @return New combo item widget.
- L248 _private prototype_ `TSharedRef<SWidget> GenerateGroupComboItem(TSharedPtr<FString> InItem);` — Creates a combo item for a test group. @return New combo item widget.
- L256 _private prototype_ `void PopulateReportSearchStrings( const TSharedPtr< IAutomationReport >& Report, OUT TArray< FString >& OutSearchStrings ) const;` — Populates OutSearchStrings with the strings that should be used in searching. @param Report The automation report to get a text description from. @param OutSearchStrings An array of stings to use.
- L259 _private prototype_ `void OnExpansionChanged(TSharedPtr<IAutomationReport> InItem, bool bExpanded);` — Callback for a test expansion changing
- L262 _private prototype_ `void ExpandSingleItemSubgroups(TSharedPtr<IAutomationReport> InItem, bool bExpanded);` — Recursively expands subgroups as a reaction on expansion change (expands single-item subgroups without leafs recursively)
- L265 _private prototype_ `void OnGetChildren(TSharedPtr<IAutomationReport> InItem, TArray<TSharedPtr<IAutomationReport> >& OutItems);` — Gets children tests for a node in the hierarchy
- L268 _private prototype_ `void OnTestExpansionRecursive(TSharedPtr<IAutomationReport> InTreeNode, bool bInIsItemExpanded);` — Callback for a test expansion changing recursively
- L271 _private prototype_ `void OnTestSelectionChanged(TSharedPtr<IAutomationReport> Selection, ESelectInfo::Type SelectInfo);` — Callback for a new test being selected
- L274 _private prototype_ `void UpdateTestLog(TSharedPtr<IAutomationReport> Selection);` — Update the test log.
- L277 _private prototype_ `void HeaderCheckboxStateChange(ECheckBoxState InCheckboxState);` — Called when the header checkbox's state is changed. Will go through all the Unit Tests available and change the state of their checkbox.
- L280 _private prototype_ `void RebuildPlatformIcons();` — Rebuilds the platform icon header
- L283 _private prototype_ `FText CreateDeviceTooltip(int32 ClusterIndex);` — Generate the device tooltip
- L286 _private prototype_ `void ClearAutomationUI ();` — Clear the UI and icon header
- L289 _private prototype_ `TSharedRef<ITableRow> OnGenerateWidgetForTest(TSharedPtr<IAutomationReport> InItem, const TSharedRef<STableViewBase>& OwnerTable );` — Generates a row widget for a automation test
- L292 _private prototype_ `TSharedRef<ITableRow> OnGenerateWidgetForLog(TSharedPtr<FAutomationOutputMessage> Message, const TSharedRef<STableViewBase>& OwnerTable);` — Generates a row widget for the log list view.
- L295 _private prototype_ `FText OnGetNumEnabledTestsString() const;` — Returns number of enabled tests (regardless of visibility)
- L298 _private prototype_ `FText OnGetNumDevicesInClusterString(const int32 ClusterIndex) const;` — Returns number of workers in a device cluster
- L301 _private prototype_ `void OnRefreshTestCallback();` — Callback when the list has been refreshed by the Automation Controller
- L304 _private prototype_ `void FindWorkers();` — Finds available workers
- L308 _private prototype_ `void ListTests();` — Updates list of all the tests
- L311 _private prototype_ `FReply RunTests();` — Goes through all selected tests and runs them.
- L314 _private prototype_ `void OnFilterTextChanged( const FText& InFilterText );` — Filter text has been updated
- L317 _private prototype_ `bool IsDeveloperDirectoryIncluded() const;` — Returns if we're considering tests on content within the developer folders
- L320 _private prototype_ `void OnToggleDeveloperDirectoryIncluded();` — Toggles the consideration of tests within developer folders
- L323 _private prototype_ `bool IsExcludedTestsFilterOn() const;` — Returns if we're considering tests from exclude list only
- L326 _private prototype_ `void OnToggleExcludedTestsFilter();` — Toggles the consideration of tests from exclude list only
- L329 _private prototype_ `bool IsSmokeTestFilterOn() const;` — Returns if we're filtering based on if the test is a "smoke" test
- L332 _private prototype_ `void OnToggleSmokeTestFilter();` — Toggles filtering of tests based on smoke test status
- L335 _private prototype_ `bool IsWarningFilterOn() const;` — Returns if we're filtering based on if the test returned any warnings
- L338 _private prototype_ `void OnToggleWarningFilter();` — Toggles filtering of tests based on warning condition
- L341 _private prototype_ `bool IsErrorFilterOn() const;` — Returns if we're filtering based on if the test returned any errors
- L344 _private prototype_ `void OnToggleErrorFilter();` — Toggles filtering of tests based on error condition
- L347 _private prototype_ `ECheckBoxState IsSendAnalyticsCheckBoxChecked() const;` — Returns if analytics should be sent to the back end
- L350 _private prototype_ `void HandleSendAnalyticsBoxCheckStateChanged(ECheckBoxState CheckBoxState);` — Toggles if we are sending analytics results from the tests
- L353 _private prototype_ `ECheckBoxState KeepPIEOpenCheckBoxChecked() const;` — Returns if PIE should be kept open when test pass end
- L356 _private prototype_ `void HandleKeepPIEOpenBoxCheckStateChanged(ECheckBoxState CheckBoxState);` — Toggles if PIE should be kept open when test pass end
- L359 _private prototype_ `ECheckBoxState AutoExpandSingleItemSubgroupsCheckBoxChecked() const;` — Returns if we should automatically expand single-item test subgroups
- L362 _private prototype_ `void HandleAutoExpandSingleItemSubgroupsCheckStateChanged(ECheckBoxState CheckBoxState);` — Toggles if automatic expansion of single-item subgroups is enabled
- L365 _private prototype_ `ECheckBoxState IsDeviceGroupCheckBoxIsChecked(const int32 DeviceGroupFlag) const;` — Returns if a device group is enabled
- L368 _private prototype_ `void HandleDeviceGroupCheckStateChanged(ECheckBoxState CheckBoxState, const int32 DeviceGroupFlag);` — Toggles a device group flag
- L371 _private prototype_ `void HandlePresetCheckStateChanged(ECheckBoxState CheckBoxState, const int32 EntryIndex, TSharedPtr<TArray<TSharedPtr<SCheckBox>>> CheckBoxes);` — Sitches presets in the Presets Menu of Preset ComboButton
- L374 _private prototype_ `void OnChangeRepeatCount(int32 InNewValue);` — Sets the number of times to repeat the tests
- L377 _private prototype_ `int32 GetRepeatCount() const;` — Returns the number of times to repeat the tests
- L380 _private prototype_ `void UpdateTestListBackgroundStyle();` — Update the test list background style (Editor vs Game)
- L387 _private prototype_ `FString GetSmallIconExtension() const;` — Gets the extention for the small brush, if enabled. @return The string to append to the brush path.
- L394 _private prototype_ `EVisibility GetLargeToolBarVisibility() const;` — Gets whether we should show large tool bar button details. @return The visibility setting for large tool bar details.
- L401 _private prototype_ `const FSlateBrush* GetRunAutomationIcon() const;` — Gets a brush for the automation start / stop state. @return - A start or stop icon - depending on state.
- L408 _private prototype_ `FText GetRunAutomationLabel() const;` — Gets a label for the automation start / stop state. @return A start or stop tests label Depending on state.
- L415 _private prototype_ `const FSlateBrush* GetTestBackgroundBorderImage() const;` — Gets the brush to use for the test list background. @return The brush to use depending on the value of TestBackgroundType.
- L423 _private prototype_ `void ExpandTreeView( TSharedPtr< IAutomationReport > InReport, const bool ShouldExpand );` — Recursively expand the tree nodes. @param InReport The current report. @param ShouldExpand Should we expand the item.
- L426 _private prototype_ `FText HandleAutomationHighlightText( ) const;` — Update the highlight string in the automation reports.
- L429 _private prototype_ `EVisibility HandleSelectSessionOverlayVisibility( ) const;` — Callback for determining the visibility of the 'Select a session' overlay.
- L432 _private prototype_ `void HandleSessionManagerCanSelectSession( const TSharedPtr<ISessionInfo>& Session, bool& CanSelect );` — Callback for determining whether a session can be selected in the session manager.
- L439 _private prototype_ `void HandleSessionManagerSelectionChanged( const TSharedPtr<ISessionInfo>& SelectedSession );` — Session selection has changed in the session manager @param SelectedSession The session that was selected.
- L442 _private prototype_ `void HandleSessionManagerInstanceChanged();` — Called when the session manager updates an instances.
- L449 _private prototype_ `bool IsAutomationRunButtonEnabled() const;` — Should the automation run button be enabled. @return true if it should be enabled.
- L456 _private prototype_ `void OnTestAvailableCallback( EAutomationControllerModuleState::Type InAutomationControllerState );` — Set whether tests are available to run. @param The Automation controller state.
- L461 _private prototype_ `void OnTestsCompleteCallback();` — Called when tests complete.
- L464 _private prototype_ `void CopyLog();` — Copies the selected log messages to the clipboard.
- L472 _private prototype_ `TSharedPtr<SWidget> HandleAutomationListContextMenuOpening( );` — Handle the context menu opening for automation reports. @return the context window.
- L475 _private prototype_ `void RunSelectedTests();` — Added button for running the currently open level test.
- L477 _private prototype_ `void FindTestReportsForCurrentEditorLevel(TArray<TSharedPtr<IAutomationReport>>& OutLevelReports);`
- L479 _private prototype_ `bool CanExecuteRunLevelTest();`
- L481 _private prototype_ `void OnRunLevelTest();`
- L483 _private prototype_ `void ScrollToTest(TSharedPtr<IAutomationReport> InReport);`
- L485 _private prototype_ `bool ExpandToTest(TSharedPtr<IAutomationReport> InRoot, TSharedPtr<IAutomationReport> InReport);`
- L489 _private prototype_ `FReply HandleSavePresetClicked();` — Handles the save preset button being clicked.
- L492 _private prototype_ `void OnNewPresetClicked();` — Handles the create new preset menu item being clicked.
- L495 _private prototype_ `void OnRemovePresetClicked();` — Handles the remove preset menu item being clicked.
- L498 _private prototype_ `void OnRenamePresetClicked();` — Handles the rename preset menu item being clicked.
- L501 _private prototype_ `bool IsSaveButtonEnabled() const;` — Should the save preset button be enabled.
- L504 _private prototype_ `EVisibility HandlePresetComboVisibility( ) const;` — Handles if the preset combo box should be visible.
- L507 _private prototype_ `EVisibility HandlePresetTextVisibility( ) const;` — Handles if the add preset text box should be visible.
- L510 _private prototype_ `EVisibility HandleGroupsVisibility() const;` — Handles if the groups combo box should be visible.
- L513 _private prototype_ `void HandlePresetTextCommited( const FText& CommittedText, ETextCommit::Type CommitType );` — Called when the user commits the text in the add preset text box.
- L516 _private prototype_ `void HandleRequesteFilterChanged(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo);` — Called when the user changes the requested test filter
- L518 _private prototype_ `void HandleGroupChanged(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo);` — Called when the user changes the test group
- L521 _private prototype_ `void ExpandEnabledTests( TSharedPtr< IAutomationReport > InReport );` — Expands the test tree to show all enabled tests.
- L524 _private prototype_ `FText GetPresetComboText() const;` — Gets the text to display for the preset combo box.
- L526 _private prototype_ `FText GetRequestedFilterComboText() const;` — Gets the text to display for the requested filter combo box.
- L528 _private prototype_ `FText GetGroupComboText() const;` — Gets the combo box text to display for the selected group.
- L531 _private prototype_ `void HandleEditTagsButtonClicked() const;` — Handle selected tests tag editing.
- L533 _private prototype_ `bool IsEditTagsButtonEnabled() const;` — Whether the edit tags button is enabled.
- L540 _private prototype_ `FReply HandleCommandBarCopyLogClicked();` — Handle the copy button clicked in the command bar. @return If the command was handled or not.
- L548 _private prototype_ `void HandleLogListSelectionChanged( TSharedPtr<FAutomationOutputMessage> InItem, ESelectInfo::Type SelectInfo );` — Handle the log selection changed. @param The selected item. @param SelectInfo Provides context on how the selection changed.
- L556 _private prototype_ `EVisibility GetTestLogVisibility( ) const;` — Gets the visibility of the test log window. @return The window's visibility. @see GetTestGraphVisibility
- L564 _private prototype_ `EVisibility GetTestGraphVisibility( ) const;` — Gets the visibility of the graphical test result window. @return The window's visibility. @see GetTestLogVisibility
- L567 _private prototype_ `void HandleResultDisplayTypeStateChanged( ECheckBoxState NewRadioState, EAutomationGrapicalDisplayType::Type NewDisplayType );` — Handles changing the display type for the graphical results window.
- L570 _private prototype_ `ECheckBoxState HandleResultDisplayTypeIsChecked( EAutomationGrapicalDisplayType::Type InDisplayType ) const;` — Handles checking if a display type is active for the graphical results window.
- L577 _private function_ `EVisibility GetTestsUpdatingThrobberVisibility() const` — Gets the visibility for the throbber. @return Whether we should show the throbber or not.
- L583 _private prototype_ `void OnAssetRegistryFilesLoaded();`
- L589 _private member_ `TSharedPtr<FUICommandList> AutomationWindowActions;` — The automation window actions list.
- L592 _private member_ `TSharedPtr<ISessionInfo> ActiveSession;` — Holds a pointer to the active session.
- L595 _private member_ `IAutomationControllerManagerPtr AutomationController;` — Holds the AutomationController.
- L598 _private member_ `TSharedPtr< SSearchBox > AutomationSearchBox;` — Holds the search box widget.
- L601 _private member_ `const float ColumnWidth;` — Must maintain a widget size so the header and row icons can line up.
- L604 _private member_ `TSharedPtr< STreeView< TSharedPtr< IAutomationReport > > > TestTable;` — The list of all valid tests.
- L607 _private member_ `TSharedPtr< SHorizontalBox > PlatformsHBox;` — Widget for header platform icons.
- L610 _private member_ `TSharedPtr< SAutomationWindowCommandBar > CommandBar;` — Widget for the command bar.
- L613 _private member_ `TSharedPtr< SVerticalBox > MenuBar;` — Widget for the menu bar - run automation etc.
- L616 _private member_ `TSharedPtr<SListView<TSharedPtr<FAutomationOutputMessage> > > LogListView;` — Holds the widget to display log messages.
- L619 _private member_ `TSharedPtr< SAutomationGraphicalResultBox > GraphicalResultBox;` — Holds the widget to display a graph of the results.
- L622 _private member_ `TArray<TSharedPtr<FAutomationOutputMessage> > LogMessages;` — Holds the collection of log messages.
- L625 _private member_ `TSharedPtr< AutomationReportTextFilter > AutomationTextFilter;` — The automation report text filter.
- L628 _private member_ `TSharedPtr< FAutomationFilter > AutomationGeneralFilter;` — The automation general filter - for smoke tests / warnings and Errors.
- L631 _private member_ `TSharedPtr< FAutomationGroupFilter > AutomationGroupFilter;` — The automation group filter - filters tests based on selected group filter.
- L634 _private member_ `TSharedPtr< FAutomationGroupFilter > AutomationTagFilter;` — The automation tag filter - filters tests based on tag expression.
- L637 _private member_ `TSharedPtr< AutomationFilterCollection > AutomationFilters;` — The automation filter collection - contains the automation filters.
- L640 _private member_ `TSharedPtr<ISessionManager> SessionManager;` — Holds the session manager.
- L646 _private member_ `EAutomationControllerModuleState::Type AutomationControllerState;` — Holds the automation controller module state. This is set by the automation controller callback. We may go back to querying the module directly.
- L649 _private member_ `bool bIsRequestingTests;` — Flag to acknowledge if the window is awaiting tests to display.
- L652 _private member_ `bool bHasChildTestSelected;` — Flag to tell if we have a child test selected in the test tree.
- L655 _private member_ `EAutomationTestBackgroundStyle::Type TestBackgroundType;` — Which type of window style to use for the test background.
- L658 _private member_ `bool bAddingTestPreset;` — True if we are creating a new preset (The add/rename preset text box is visible).
- L661 _private member_ `bool bRenamingTestPreset;` — True if we are renaming a new preset (The add/rename preset text box is visible).
- L664 _private member_ `bool bIsLabelVisibilityEnabled;` — Flag to enable display of the text labels in the toolbar.
- L667 _private member_ `bool bAutoExpandSingleItemSubgroups;` — Flag to enable auto expand of subgroups that have single-item groups without children.
- L670 _private member_ `TSharedPtr<FAutomationTestPresetManager> TestPresetManager;` — Holds a pointer to the preset manager.
- L673 _private member_ `TSharedPtr<FAutomationTestPreset> SelectedPreset;` — Holds the currently selected preset.
- L676 _private member_ `TSharedPtr< STextBlock > PresetComboButtonText;` — Holds a pointer to the preset combo button widget.
- L679 _private member_ `TSharedPtr< SComboBox< TSharedPtr<FString> > > RequestedFilterComboBox;` — Holds a pointer to the preset combo box widget.
- L680 _private member_ `TArray< TSharedPtr< FString > > RequestedFilterComboList;`
- L683 _private member_ `TSharedPtr< SComboBox< TSharedPtr<FString> > > GroupComboBox;` — Holds a pointer to the groups combo box widget.
- L684 _private member_ `TArray< TSharedPtr< FString > > GroupComboList;`
- L687 _private member_ `TMap< FString, TArray<FAutomatedTestFilter> > GroupFiltersMap;` — Map for fast access of test group filters by name.
- L690 _private member_ `TSharedPtr<SEditableTextBox> PresetTextBox;` — Holds a pointer to the preset text box.
- L693 _private member_ `TArray<FString> SavedExpandedItems;` — List of expanded test items to preserve during a refresh
- L696 _private member_ `TWeakPtr<IAutomationReport> PreviousSelection;` — Saves the last selected test so that it can be unbinded from refreshing the log
- L699 _private member_ `TSharedPtr<SAutomationTestTagFilter> TagFilter;` — Holds a pointer to the tag filter widget.

#### struct `SAutomationWindow::FAutomationOutputMessage`  
`struct FAutomationOutputMessage`  
_L75-88_
- desc: Single line in the automation output
- L78 _public member_ `FName Style;` — Holds the message style.
- L81 _public member_ `FString Text;` — Holds the message text.
- L84 _public function_ `FAutomationOutputMessage (const FString& InText, const FName& InStyle) : Style(InStyle) , Text(InText)` — Creates and initializes a new instance.

#### Free symbols / members of external scopes

- L37 _namespace_ `namespace AutomationTestWindowConstants`
- L39 _variable_ `const FName Checked( TEXT("Check` (scope `AutomationTestWindowConstants`)
- L40 _variable_ `const FName Skipped( TEXT("Skipp` (scope `AutomationTestWindowConstants`)
- L41 _variable_ `const FName SkippedOptions( TEXT("Skipp` (scope `AutomationTestWindowConstants`)
- L42 _variable_ `const FName Tags(TEXT("Tags` (scope `AutomationTestWindowConstants`)
- L43 _variable_ `const FName Title( TEXT("Name"` (scope `AutomationTestWindowConstants`)
- L44 _variable_ `const FName SmokeTest( TEXT("Smoke` (scope `AutomationTestWindowConstants`)
- L45 _variable_ `const FName RequiredDeviceCount( TEXT("Requi` (scope `AutomationTestWindowConstants`)
- L46 _variable_ `const FName Status( TEXT("Statu` (scope `AutomationTestWindowConstants`)
- L47 _variable_ `const FName Timing( TEXT("Timin` (scope `AutomationTestWindowConstants`)
- L52 _namespace_ `namespace EAutomationTestBackgroundStyle`

### `Source/Developer/AutomationWindow/Private/SAutomationWindowCommandBar.h` (Private)


#### class `SAutomationWindowCommandBar`  
`class SAutomationWindowCommandBar : public SCompoundWidget`  
_L17-66_
- inherits: `SCompoundWidget`
- desc: Implements the automation console command bar widget.
- L22 _public function_ `SLATE_BEGIN_ARGS(SAutomationWindowCommandBar)`
- L36 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef< SNotificationList >& InNotificationList );` — Construct this widget @param InArgs The declaration data for this widget.
- L43 _public prototype_ `void SetNumLogMessages( int Count );` — Sets the number of messages selected in the log window. @param Count Number of selected messages.
- L46 _public prototype_ `void SetCopyButtonVisibility(EVisibility InVisibility);` — Sets visibility status for Copy button
- L51 _private prototype_ `FReply HandleCopyButtonClicked( );` — Handles clicking the copy log button.
- L53 _private prototype_ `EVisibility GetCopyButtonVisibility() const;`
- L54 _private prototype_ `EVisibility GetExportMenuVisibility() const;`
- L59 _private member_ `TSharedPtr<SButton> CopyButton;` — Holds the copy log button.
- L62 _private member_ `FOnClicked OnCopyLogClicked;` — Holds a delegate that is executed when the copy log button is clicked.
- L65 _private member_ `EVisibility CopyButtonVisibility = EVisibility::Collapsed;` — Holds visibility status for Copy button

### `Source/Developer/AutomationWindow/Public/IAutomationWindowModule.h` (Public)


#### class `IAutomationWindowModule`  
`class IAutomationWindowModule : public IModuleInterface`  
_L19-60_
- inherits: `IModuleInterface`
- desc: Automation Window module
- L31 _public prototype_ `virtual TSharedRef<class SWidget> CreateAutomationWindow( const IAutomationControllerManagerRef& AutomationController, const TSharedRef<ISessionManager>& SessionManager ) = 0;` — Creates a Automation Window widget. @param AutomationController The automation controller to use. @param SessionManager The session manager to use. @return	New Automation Test window widget
- L38 _public prototype_ `virtual TWeakPtr<class SDockTab> GetAutomationWindowTab() = 0;` — Store a pointer to the AutomationWindowTab. @return a weak pointer to the automation tab.
- L45 _public prototype_ `virtual void SetAutomationWindowTab(TWeakPtr<class SDockTab> AutomationWindowTab) = 0;` — Store a pointer to the AutomationWindowTab. @param AutomationWindowTab a weak pointer to the automation tab.
- L54 _public prototype_ `virtual FOnAutomationWindowModuleShutdown& OnShutdown( ) = 0;` — Gets a delegate that is invoked when the automation window module shuts down. @return The delegate.
- L59 _protected prototype_ `~IAutomationWindowModule( ) = default;` — Virtual destructor.

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_DELEGATE(FOnAutomationWindowModuleShutdown);` — Delegate to call when the automation window module is shutdown.
- L13 _prototype_ `DECLARE_DELEGATE(FOnAutomationWindowModuleShutdown);` — Delegate to call when the automation window module is shutdown.
