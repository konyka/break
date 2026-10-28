# Developer / OutputLog

- module root: `Source/Developer/OutputLog`
- headers: 9; symbols: 381
- symbol kinds: class=10, delegate=6, enum=4, enumerator=14, function=30, member=119, namespace=3, prototype=180, struct=11, typedef=4
- PrivateDependencyModuleNames: Core, CoreUObject, DesktopPlatform, EditorFramework, Engine, EngineSettings, InputCore, Slate, SlateCore, StatusBar, TargetPlatform, ToolMenus, ToolWidgets, UnrealEd
- PrivateIncludePathModuleNames: WorkspaceMenuStructure

### `Source/Developer/OutputLog/Private/OutputLogMenuContext.h` (Private)


#### class `UConsoleInputBoxMenuContext`  
`class UConsoleInputBoxMenuContext : public UObject`  
_L16-33_
- reflection: `UCLASS()`
- inherits: `UObject`
- L21 _public function_ `void Init(const TSharedRef<SConsoleInputBox>& InConsoleInputBox)`
- L26 _public function_ `TSharedPtr<SConsoleInputBox> GetConsoleInputBox() const`
- L32 _private member_ `TWeakPtr<SConsoleInputBox> WeakConsoleInputBox;`

#### class `UOutputLogMenuContext`  
`class UOutputLogMenuContext : public UObject`  
_L37-54_
- reflection: `UCLASS()`
- inherits: `UObject`
- L42 _public function_ `void Init(const TSharedRef<SOutputLog>& InOutputLog)`
- L47 _public function_ `TSharedPtr<SOutputLog> GetOutputLog() const`
- L53 _private member_ `TWeakPtr<SOutputLog> WeakOutputLog;`

### `Source/Developer/OutputLog/Private/OutputLogStyle.h` (Private)


#### class `FOutputLogStyle`  
`class FOutputLogStyle : public FSlateStyleSet`  
_L10-29_
- inherits: `FSlateStyleSet`
- L14 _public prototype_ `virtual const FName& GetStyleSetName() const override;`
- L16 _public prototype_ `static const FOutputLogStyle& Get();`
- L17 _public prototype_ `static void Shutdown();`
- L19 _public prototype_ `~FOutputLogStyle();`
- L22 _private prototype_ `FOutputLogStyle();`
- L24 _private prototype_ `void OnSettingsChanged(FName PropertyName);`
- L25 _private prototype_ `void UpdateLogTextSize();`
- L27 _private member_ `static FName StyleName;`
- L28 _private member_ `static TUniquePtr<FOutputLogStyle> Inst;`

### `Source/Developer/OutputLog/Private/SDebugConsole.h` (Private)


#### class `SDebugConsole`  
`class SDebugConsole : public SCompoundWidget`  
_L19-62_
- inherits: `SCompoundWidget`
- desc: Debug console widget, designed to be summoned on top of a viewport or window
- L23 _public function_ `SLATE_BEGIN_ARGS( SDebugConsole )`
- L27 _public prototype_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs, const EDebugConsoleStyle::Type InStyle, FOutputLogModule* OutputLogModule, const FDebugConsoleDelegates* DebugConsoleDelegates );`
- L33 _public prototype_ `void SetFocusToEditableText();` — Call to set focus to this debug console's editable text box
- L36 _public prototype_ `SDebugConsole();` — Default constructor
- L41 _protected prototype_ `EVisibility MakeVisibleIfLogIsShown() const;` — Returns EVisibility::Visible if style has log being shown, otherwise VIS_COLLAPSED
- L44 _protected prototype_ `FLinearColor GetAnimatedColorAndOpacity() const;` — Returns a color and opacity value to use based on any current animation
- L47 _protected prototype_ `FSlateColor GetAnimatedSlateColor() const;` — Returns a Slate color based on any current animation (same color as GetAnimatedColorAndOpacity)
- L49 _protected prototype_ `FSlateColor GetFlashColor() const;`
- L53 _private member_ `TSharedPtr< SMultiLineEditableTextBox > EditableTextBox;` — Editable text box for this debug console's input line
- L56 _private member_ `EDebugConsoleStyle::Type CurrentStyle;` — Current style of the debug console.  Can be changed on the fly.
- L59 _private member_ `FCurveSequence AnimCurveSequence;` — Intro/outro animation curve
- L60 _private member_ `FCurveHandle AnimCurve;`
- L61 _private member_ `FCurveHandle FlashCurve;`

### `Source/Developer/OutputLog/Private/SDeviceOutputLog.h` (Private)


#### struct `FTargetDeviceEntry`  
`struct FTargetDeviceEntry`  
_L21-26_
- L23 _public member_ `FTargetDeviceId DeviceId;`
- L24 _public member_ `const FSlateBrush* DeviceIconBrush;`
- L25 _public member_ `ITargetDeviceWeakPtr DeviceWeakPtr;`

#### class `SDeviceOutputLog`  
`class SDeviceOutputLog : public SOutputLog`  
_L33-104_
- inherits: `SOutputLog`
- L36 _public function_ `SLATE_BEGIN_ARGS(SDeviceOutputLog) : _AutoSelectDevice(false)`
- L39 _public prototype_ `SLATE_ARGUMENT(bool, AutoSelectDevice)` — If the first device found should be automatically selected.
- L50 _public prototype_ `void Construct( const FArguments& InArgs );` — Construct this widget.  Called by the SNew() Slate macro. @param	InArgs	Declaration used by the SNew() macro to construct this widget
- L53 _public function_ `FSelectedTargetDeviceChangedDelegate& OnSelectedDeviceChanged()`
- L54 _public prototype_ `ITargetDevicePtr GetSelectedTargetDevice() const;`
- L59 _protected prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SWidget interface
- L62 _protected prototype_ `virtual void Serialize( const TCHAR* V, ELogVerbosity::Type Verbosity, const class FName& Category ) override;` — FOutputDevice interface
- L63 _protected prototype_ `virtual bool CanBeUsedOnAnyThread() const;`
- L65 _protected prototype_ `void ExecuteConsoleCommand(const FString& ExecCommand);`
- L69 _protected prototype_ `void HandleTargetPlatformDeviceLost(ITargetDeviceRef LostDevice);` — Callback for lost target devices.
- L71 _protected prototype_ `void HandleTargetPlatformDeviceDiscovered(ITargetDeviceRef DiscoveredDevice);` — Callback for discovered target devices.
- L73 _protected prototype_ `void AddDeviceEntry(ITargetDeviceRef TargetDevice);`
- L74 _protected prototype_ `bool FindDeviceEntry(FTargetDeviceId InDeviceId);`
- L76 _protected prototype_ `void OnDeviceSelectionChanged(FTargetDeviceEntryPtr DeviceEntry);`
- L77 _protected prototype_ `TSharedRef<SWidget> MakeDeviceComboButtonMenu();`
- L78 _protected prototype_ `TSharedRef<SWidget> GenerateWidgetForDeviceComboBox(const FTargetDeviceEntryPtr& DeviceEntry) const;`
- L80 _protected prototype_ `FText GetTargetDeviceText(FTargetDeviceEntryPtr DeviceEntry) const;`
- L81 _protected prototype_ `FText GetSelectedTargetDeviceText() const;`
- L83 _protected prototype_ `const FSlateBrush* GetTargetDeviceBrush(FTargetDeviceEntryPtr DeviceEntry) const;`
- L84 _protected prototype_ `const FSlateBrush* GetSelectedTargetDeviceBrush() const;`
- L89 _private member_ `TArray<FTargetDeviceEntryPtr> DeviceList;`
- L90 _private member_ `FTargetDeviceEntryPtr CurrentDevicePtr;`
- L91 _private member_ `ITargetDeviceOutputPtr CurrentDeviceOutputPtr;`
- L93 _private member_ `TSharedPtr<SComboButton> TargetDeviceComboButton;`
- L96 _private member_ `FCriticalSection BufferedLinesSynch;` — Synchronization object for access to buffered lines
- L97 _private member_ `TArray<FBufferedLine> BufferedLines;`
- L100 _private member_ `FSelectedTargetDeviceChangedDelegate OnSelectedDeviceChangedDelegate;`
- L102 _private member_ `bool bAutoSelectDevice;`

#### Free symbols / members of external scopes

- L28 _typedef_ `typedef TSharedPtr<FTargetDeviceEntry> FTargetDeviceEntryPtr;`
- L30 _delegate_ `DECLARE_DELEGATE_OneParam(FSelectedTargetDeviceChangedDelegate, ITargetDevicePtr);`
- L30 _prototype_ `DECLARE_DELEGATE_OneParam(FSelectedTargetDeviceChangedDelegate, ITargetDevicePtr);`

### `Source/Developer/OutputLog/Private/SOutputLog.h` (Private)


#### struct `FOutputLogMessage`  
`struct FOutputLogMessage`  
_L33-49_
- desc: A single log message for the output log, holding a message and a style, for color and bolding of the message.
- L35 _public member_ `TSharedRef<FString> Message;`
- L36 _public member_ `ELogVerbosity::Type Verbosity;`
- L37 _public member_ `int8 CategoryStartIndex;`
- L38 _public member_ `FName Category;`
- L39 _public member_ `FName Style;`
- L41 _public function_ `FOutputLogMessage(const TSharedRef<FString>& NewMessage, ELogVerbosity::Type NewVerbosity, FName NewCategory, FName NewStyle, int32 InCategoryStartIndex) : Message(NewMessage) , Verbosity(NewVerbosity) , CategoryStartIndex((int8)InCategoryStartIndex) , Category(NewCategory) , Style(NewStyle)`

#### class `SConsoleInputBox`  
`class SConsoleInputBox : public SCompoundWidget`  
_L54-258_
- inherits: `SCompoundWidget`
- desc: Console input box with command-completion support
- L57 _private typedef_ `using FInterceptConsoleCommandDelegate = UE::OutputLog::FInterceptConsoleCommandDelegate;`
- L58 _private typedef_ `using FHistoryOverrideDelegate = UE::OutputLog::FHistoryOverrideDelegate;`
- L61 _public function_ `DECLARE_DELEGATE_OneParam(FExecuteConsoleCommand, const FString& ) SLATE_BEGIN_ARGS( SConsoleInputBox ) : _SuggestionListPlacement( MenuPlacement_BelowAnchor )`
- L68 _public prototype_ `SLATE_ARGUMENT( EMenuPlacement, SuggestionListPlacement ) /** Called before executing a command;` — Where to place the suggestion list
- L94 _public prototype_ `void Construct( const FArguments& InArgs );` — Construct this widget.  Called by the SNew() Slate macro. @param	InArgs	Declaration used by the SNew() macro to construct this widget
- L97 _public function_ `TSharedRef< SMultiLineEditableTextBox > GetEditableTextBox()` — Returns the editable text box associated with this widget.  Used to set focus directly.
- L103 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;` — SWidget interface
- L107 _protected function_ `virtual bool SupportsKeyboardFocus() const override`
- L110 _protected prototype_ `virtual FReply OnPreviewKeyDown( const FGeometry& MyGeometry, const FKeyEvent& KeyEvent ) override;` — e.g. Tab or Key_Up
- L112 _protected prototype_ `void OnFocusLost( const FFocusEvent& InFocusEvent ) override;`
- L115 _protected prototype_ `void OnTextCommitted(const FText& InText, ETextCommit::Type CommitInfo);` — Handles entering in a command
- L117 _protected prototype_ `void OnTextChanged(const FText& InText);`
- L120 _protected prototype_ `FOptionalSize GetSelectionListMaxWidth() const;` — Get the maximum width of the selection list
- L123 _protected prototype_ `TSharedRef<ITableRow> MakeSuggestionListItemWidget(TSharedPtr<FConsoleSuggestion> Message, const TSharedRef<STableViewBase>& OwnerTable);` — Makes the widget for the suggestions messages in the list view
- L125 _protected prototype_ `void SuggestionSelectionChanged(TSharedPtr<FConsoleSuggestion> NewValue, ESelectInfo::Type SelectInfo);`
- L128 _protected prototype_ `TArray<FConsoleSuggestion> GenerateSuggestions() const;` — Genearates suggestions for the console
- L130 _protected prototype_ `void SetSuggestions(TArray<FConsoleSuggestion>& Elements, FText Highlight);`
- L132 _protected prototype_ `void MarkActiveSuggestion();`
- L134 _protected prototype_ `void ClearSuggestions();`
- L136 _protected prototype_ `void OnCommandExecutorRegistered(const FName& Type, class IModularFeature* ModularFeature);`
- L138 _protected prototype_ `void OnCommandExecutorUnregistered(const FName& Type, class IModularFeature* ModularFeature);`
- L140 _protected prototype_ `void SyncActiveCommandExecutor();`
- L142 _protected prototype_ `void SetActiveCommandExecutor(const FName InExecName);`
- L144 _protected prototype_ `void MakeNextCommandExecutorActive();`
- L146 _protected prototype_ `FText GetActiveCommandExecutorDisplayName() const;`
- L148 _protected prototype_ `FText GetActiveCommandExecutorHintText() const;`
- L150 _protected prototype_ `bool GetActiveCommandExecutorAllowMultiLine() const;`
- L152 _protected prototype_ `FText GetInputHelpText() const;`
- L154 _protected prototype_ `bool IsCommandExecutorMenuEnabled() const;`
- L156 _protected prototype_ `TSharedRef<SWidget> GetCommandExecutorMenuContent();`
- L158 _protected prototype_ `FReply OnKeyDownHandler(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);`
- L160 _protected prototype_ `FReply OnKeyCharHandler(const FGeometry& MyGeometry, const FCharacterEvent& InCharacterEvent);`
- L217 _private member_ `TSharedPtr< SMultiLineEditableTextBox > InputText;` — Editable text widget
- L220 _private member_ `TSharedPtr< SMenuAnchor > SuggestionBox;` — history / auto completion elements
- L223 _private member_ `TSharedPtr< SListView< TSharedPtr<FConsoleSuggestion> > > SuggestionListView;` — The list view for showing all log messages. Should be replaced by a full text editor
- L226 _private member_ `FSuggestions Suggestions;` — Active list of suggestions
- L229 _private member_ `FSimpleDelegate OnConsoleCommandExecuted;` — Delegate to call when a console command is executed
- L232 _private member_ `FInterceptConsoleCommandDelegate InterceptConsoleCommand;` — Delegate used to intercept console commands.
- L235 _private member_ `FHistoryOverrideDelegate HistoryOverride;` — Delegate used to override the command history of the specified executors.
- L238 _private member_ `FExecuteConsoleCommand ConsoleCommandCustomExec;` — Delegate to call to execute console command
- L241 _private member_ `FSimpleDelegate OnCloseConsole;` — Delegate to call to close the console
- L244 _private member_ `FName PreferredCommandExecutorName;` — Name of the preferred command executor (may not always be the active executor)
- L247 _private member_ `IConsoleCommandExecutor* ActiveCommandExecutor;` — The currently active command executor
- L250 _private member_ `bool bIgnoreUIUpdate;` — to prevent recursive calls in UI callback
- L253 _private member_ `bool bHasTicked;` — true if this widget has been Ticked at least once
- L256 _private member_ `bool bConsumeTab;` — True if we consumed a tab key in OnPreviewKeyDown, so we can ignore it in OnKeyCharHandler as well

#### struct `SConsoleInputBox::FSuggestions`  
`struct FSuggestions`  
_L164-214_
- L166 _public function_ `FSuggestions() : SelectedSuggestion(INDEX_NONE)`
- L171 _public function_ `void Reset()`
- L178 _public function_ `bool HasSuggestions() const`
- L183 _public function_ `bool HasSelectedSuggestion() const`
- L188 _public function_ `void StepSelectedSuggestion(const int32 Step)`
- L201 _public function_ `TSharedPtr<FConsoleSuggestion> GetSelectedSuggestion() const`
- L207 _public member_ `int32 SelectedSuggestion;` — INDEX_NONE if not set, otherwise index into SuggestionsList
- L210 _public member_ `TArray<TSharedPtr<FConsoleSuggestion>> SuggestionsList;` — All log messages stored in this widget for the list view
- L213 _public member_ `FText SuggestionsHighlight;` — Highlight text to use for the suggestions list

#### struct `FOutputLogFilter`  
`struct FOutputLogFilter`  
_L263-338_
- desc: Holds information about filters_
- L266 _public member_ `TSet<ELogVerbosity::Type> IgnoreFilterVerbosities;` — Set of Verbosity levels that will show all regardless of category filter
- L269 _public member_ `FAllowLogCategoryCallback AllowLogCategoryCallback;` — If set, checks if a category is allowed to log or not
- L271 _public member_ `ELogLevelFilter MessagesFilter = ELogLevelFilter::Enabled;`
- L272 _public member_ `ELogLevelFilter WarningsFilter = ELogLevelFilter::Enabled;`
- L273 _public member_ `ELogLevelFilter ErrorsFilter = ELogLevelFilter::Enabled;`
- L276 _public member_ `bool bSelectNewCategories = true;` — Whether newly added categories should begin as selected.
- L279 _public function_ `FOutputLogFilter() : TextFilterExpressionEvaluator(ETextFilterExpressionEvaluatorMode::BasicString)` — Enable all filters by default
- L283 _public prototype_ `ECheckBoxState AreAllCategoriesSelected() const;`
- L285 _public prototype_ `void ApplySettings(const FOutputLogFilterSettings& InSettings);`
- L286 _public prototype_ `void ExportSettings(FOutputLogFilterSettings& OutSettings) const;`
- L289 _public prototype_ `bool IsMessageAllowed(const TSharedPtr<FOutputLogMessage>& Message) const;` — Checks the given message against set filters
- L292 _public function_ `void SetFilterText(const FText& InFilterText)` — Set the Text to be used as the Filter's restrictions
- L295 _public function_ `FText GetFilterText() const` — Get the Text currently being used as the Filter's restrictions
- L298 _public function_ `FText GetSyntaxErrors() const` — Returns Evaluator syntax errors (if any)
- L301 _public prototype_ `TArray<FOutputLogCategorySettings> GetCategoryFilters() const;` — Returns the list of category settings sorted by Name. Ends up sorting the Categories Map if needed
- L304 _public function_ `const TMap<FName, FOutputLogCategorySettings>& GetCategories() const` — Returns the map of categories
- L310 _public prototype_ `void AddAvailableLogCategory(const FName& LogCategory, const TOptional<bool>& InitiallySelected = TOptional<bool>());` — Adds a Log Category to the list of available categories, if it isn't already present
- L313 _public prototype_ `bool IsLogCategoryAvailable(const FName& LogCategory) const;` — Returns true if the specified log category is in the list of available categories
- L316 _public prototype_ `bool IsLogCategoryEnabled(const FName& LogCategory) const;` — Returns true if the specified log category is enabled
- L319 _public prototype_ `void SetLogCategoryEnabled(const FName& LogCategory, bool bEnabled);` — Enables or disables a log category if it is not already in that state.
- L321 _public prototype_ `void SetAllCategoriesEnabled(bool bEnabled);`
- L324 _public prototype_ `void ToggleLogCategory(const FName& LogCategory);` — Enables or disables a Log Category in the filter
- L327 _public prototype_ `void ClearSelectedLogCategories();` — Empties the list of selected log categories
- L330 _private prototype_ `ELogLevelFilter GetMessageLevelFilter(const TSharedPtr<FOutputLogMessage>& Message) const;`
- L332 _private member_ `mutable bool bCategoriesNeedSorting = false;`
- L334 _private member_ `TMap<FName, FOutputLogCategorySettings> Categories;` — All categories the filter is aware of
- L337 _private member_ `FTextFilterExpressionEvaluator TextFilterExpressionEvaluator;` — Expression evaluator that can be used to perform complex text filter queries

#### class `SOutputLog`  
`class SOutputLog : public SCompoundWidget, public FOutputDevice`  
_L344-566_
- inherits: `SCompoundWidget,FOutputDevice`
- desc: Widget which holds a list view of logs of the program output as well as a combo box for entering in new commands
- L350 _public function_ `SLATE_BEGIN_ARGS( SOutputLog )`
- L352 _public prototype_ `SLATE_EVENT(FSimpleDelegate, OnCloseConsole) SLATE_EVENT(FSimpleDelegate, OnClearLog) SLATE_ARGUMENT_DEFAULT( const TArray< TSharedPtr<FOutputLogMessage> >*, Messages) = nullptr;`
- L360 _public prototype_ `SLATE_ARGUMENT_DEFAULT( const FOutputLogFilter*, InitialLogFilter ) = nullptr;` — The default Filter to apply to the OutputLog
- L363 _public prototype_ `SLATE_ARGUMENT_DEFAULT( const FOutputLogFilterSettings*, InitialLogFilterSettings ) = nullptr;` — The default FilterSettings to apply to the OutputLog
- L366 _public prototype_ `SLATE_ARGUMENT_DEFAULT( EOutputLogSettingsMenuFlags, SettingsMenuFlags ) = EOutputLogSettingsMenuFlags::None;`
- L369 _public prototype_ `SLATE_ARGUMENT_DEFAULT( bool, EnableLoggingLimitMenu ) = false;` — Should this output log enable support for limiting the number of logged lines.
- L372 _public prototype_ `SLATE_ARGUMENT_DEFAULT( TOptional<int32>, LoggingLineLimit ) =` — The limit to the number of lines we output to the logging widget.
- L374 _public prototype_ `SLATE_ARGUMENT( FDefaultCategorySelectionMap, DefaultCategorySelection ) SLATE_EVENT( FAllowLogCategoryCallback, AllowInitialLogCategory ) SLATE_END_ARGS() virtual ~SOutputLog();`
- L389 _public prototype_ `void Construct( const FArguments& InArgs, bool bCreateDrawerDockButton );` — Construct this widget.  Called by the SNew() Slate macro. @param	InArgs	Declaration used by the SNew() macro to construct this widget
- L392 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SWidget interface
- L405 _public prototype_ `static bool CreateLogMessages(const TCHAR* V, ELogVerbosity::Type Verbosity, const class FName& Category, TArray< TSharedPtr<FOutputLogMessage> >& OutMessages);` — Creates FOutputLogMessage objects from FOutputDevice log callback @param	V Message text @param Verbosity Message verbosity @param Category Message category @param OutMessages Array to receive created FOutputLogMessage messages @param Filters [Optional] Filters to apply to Messages @return true if any messages have been created, false otherwise
- L408 _public prototype_ `static void RegisterSettingsMenu();` — Registers settings dropdown tool menu for extensibility.
- L413 _public prototype_ `void OnClearLog();` — Called when delete all is selected
- L416 _public prototype_ `void OnHighlightCategory(FName NewCategoryToHighlight);` — Called when a category is selected to be highlighted
- L419 _public prototype_ `void HandleSettingChanged(FName ChangedSettingName);` — Called when the editor style settings are modified
- L421 _public prototype_ `void RefreshAllPreservingLocation();`
- L426 _public prototype_ `bool CanClearLog() const;` — Called to determine whether delete all is currently a valid command
- L429 _public prototype_ `void FocusConsoleCommandBox();` — Focuses the edit box where you type in console commands
- L432 _public prototype_ `void UpdateOutputLogFilter(const FOutputLogFilter& InFilter);` — Change the output log's filter. If CategoriesToShow is empty, all categories will be shown.
- L433 _public prototype_ `void UpdateOutputLogFilter(const FOutputLogFilterSettings& InSettings);`
- L435 _public function_ `const FOutputLogFilter& GetOutputLogFilter()`
- L438 _protected prototype_ `virtual void Serialize( const TCHAR* V, ELogVerbosity::Type Verbosity, const class FName& Category ) override;`
- L444 _protected prototype_ `void ExtendTextBoxMenu(FMenuBuilder& Builder);` — Extends the context menu used by the text box
- L449 _protected prototype_ `void OnUserScrolled(float ScrollOffset);` — Called when the user scrolls the log window vertically
- L453 _public prototype_ `void OnConsoleCommandExecuted();` — Called when a console command is entered for this output log
- L457 _protected prototype_ `void RequestForceScroll(bool bIfUserHasNotScrolledUp = false);` — Request we immediately force scroll to the bottom of the log
- L460 _protected member_ `TSharedPtr< FOutputLogTextLayoutMarshaller > MessagesTextMarshaller;` — Converts the array of messages into something the text box understands
- L463 _protected member_ `TSharedPtr< SMultiLineEditableTextBox > MessagesTextBox;` — The editable text showing all log messages
- L466 _protected member_ `TSharedPtr< SSearchBox > FilterTextBox;` — The editable text showing all log messages
- L468 _protected member_ `FSimpleDelegate OnClearLogDelegate;`
- L469 _protected member_ `FSimpleDelegate OnCloseConsole;`
- L474 _private prototype_ `TSharedRef<SWidget> MakeLogLimitMenuItem();` — The log limit menu entry to prevent logs from consuming the output log widget.
- L476 _private prototype_ `void BuildInitialLogCategoryFilter(const FArguments& InArgs);`
- L479 _private prototype_ `void OnFilterTextChanged(const FText& InFilterText);` — Called by Slate when the filter box changes text.
- L482 _private prototype_ `void OnFilterTextCommitted(const FText& InFilterText, ETextCommit::Type InCommitType);` — Called by Slate when the filter text box is confirmed.
- L485 _private prototype_ `TSharedRef<SWidget> MakeAddFilterMenu();` — Make the "Filters" menu.
- L488 _private prototype_ `void MakeSelectCategoriesSubMenu(FMenuBuilder& MenuBuilder);` — Make the "Categories" sub-menu.
- L490 _private prototype_ `ELogLevelFilter GetMessagesFilter() const;`
- L491 _private prototype_ `void OnMessagesFilterChanged(ELogLevelFilter NewFilter);`
- L493 _private prototype_ `ELogLevelFilter GetWarningsFilter() const;`
- L494 _private prototype_ `void OnWarningsFilterChanged(ELogLevelFilter NewFilter);`
- L496 _private prototype_ `ELogLevelFilter GetErrorsFilter() const;`
- L497 _private prototype_ `void OnErrorsFilterChanged(ELogLevelFilter NewFilter);`
- L500 _private prototype_ `void CategoriesShowAll_Execute();` — Toggles All Categories true/false.
- L503 _private prototype_ `ECheckBoxState CategoriesShowAll_IsChecked() const;` — Returns the state of "Show All"
- L506 _private prototype_ `void CategoriesSingle_Execute(FName InName);` — Toggles the given category true/false.
- L509 _private prototype_ `bool CategoriesSingle_IsChecked(FName InName) const;` — Returns the state of the given category
- L512 _private prototype_ `void Refresh();` — Forces re-population of the messages list
- L514 _private prototype_ `bool IsWordWrapEnabled() const;`
- L516 _private prototype_ `void SetWordWrapEnabled(ECheckBoxState InValue);`
- L518 _private prototype_ `void SetTimestampMode(ELogTimes::Type InValue);`
- L520 _private prototype_ `bool IsSelectedTimestampMode(ELogTimes::Type NewType);`
- L522 _private prototype_ `void AddTimestampMenuSection(FMenuBuilder& Menu);`
- L524 _private prototype_ `ELogTimes::Type GetSelectedTimestampMode();`
- L527 _private prototype_ `bool IsClearOnPIEEnabled() const;`
- L529 _private prototype_ `void SetClearOnPIE(ECheckBoxState InValue);`
- L532 _private prototype_ `static void RegisterSettingsMenu_WordWrap(FToolMenuSection& InSection);`
- L533 _private prototype_ `static void RegisterSettingsMenu_TimestampMode(FToolMenuSection& InSection);`
- L534 _private prototype_ `static void RegisterSettingsMenu_ClearOnPIE(FToolMenuSection& InSection);`
- L535 _private prototype_ `static void RegisterSettingsMenu_BrowseLogs(FToolMenuSection& InSection);`
- L536 _private prototype_ `static void RegisterSettingsMenu_OpenLogExternal(FToolMenuSection& InSection);`
- L537 _private prototype_ `FName GetSettingsMenuProfileForFlags(EOutputLogSettingsMenuFlags InFlags);`
- L538 _private prototype_ `TSharedRef<SWidget> GetSettingsMenuContent(FName InMenuProfileName);`
- L540 _private prototype_ `TSharedRef<SWidget> CreateDrawerDockButton();`
- L542 _private prototype_ `void OpenLogFileInExplorer();`
- L544 _private prototype_ `void OpenLogFileInExternalEditor();`
- L546 _private prototype_ `FReply OnDockInLayoutClicked();`
- L549 _protected member_ `TSharedPtr<SConsoleInputBox> ConsoleInputBox;`
- L552 _protected member_ `FOutputLogFilter Filter;` — Visible messages filter
- L554 _protected member_ `FDelegateHandle SettingsWatchHandle;`
- L556 _protected member_ `int32 LoggingLineLimit = 10000;`
- L559 _protected member_ `bool bIsUserScrolled = false;` — True if the user has scrolled the window upwards
- L561 _protected member_ `bool bShouldCreateDrawerDockButton = false;`
- L563 _protected member_ `bool bShouldShowLoggingLimitMenu = false;`
- L565 _protected member_ `bool bEnableLoggingLimit = false;`

#### class `FOutputLogTextLayoutMarshaller`  
`class FOutputLogTextLayoutMarshaller : public FBaseTextLayoutMarshaller`  
_L569-635_
- inherits: `FBaseTextLayoutMarshaller`
- desc: Output log text marshaller to convert an array of FOutputLogMessages into styled lines to be consumed by an FTextLayout
- L573 _public prototype_ `static TSharedRef< FOutputLogTextLayoutMarshaller > Create(TArray< TSharedPtr<FOutputLogMessage> > InMessages, FOutputLogFilter* InFilter);`
- L575 _public prototype_ `virtual ~FOutputLogTextLayoutMarshaller();`
- L578 _public prototype_ `virtual void SetText(const FString& SourceString, FTextLayout& TargetTextLayout) override;` — ITextLayoutMarshaller
- L579 _public prototype_ `virtual void GetText(FString& TargetString, const FTextLayout& SourceTextLayout) override;`
- L581 _public prototype_ `bool AppendPendingMessage(const TCHAR* InText, const ELogVerbosity::Type InVerbosity, const FName& InCategory);`
- L582 _public prototype_ `bool SubmitPendingMessages();`
- L583 _public prototype_ `void ClearMessages();`
- L585 _public prototype_ `void CountMessages();`
- L587 _public prototype_ `int32 GetNumMessages() const;`
- L588 _public prototype_ `int32 GetNumFilteredMessages();`
- L589 _public prototype_ `int32 GetNumCachedMessages();`
- L591 _public prototype_ `void MarkMessagesCacheAsDirty();`
- L593 _public prototype_ `FName GetCategoryForLocation(const FTextLocation Location) const;`
- L595 _public prototype_ `FTextLocation GetTextLocationAt(const FVector2D& Relative) const;`
- L597 _public function_ `FName GetCategoryToHighlight() const`
- L599 _public function_ `void SetCategoryToHighlight(FName InCategory)`
- L603 _protected prototype_ `FOutputLogTextLayoutMarshaller(TArray< TSharedPtr<FOutputLogMessage> > InMessages, FOutputLogFilter* InFilter);`
- L605 _protected prototype_ `void AppendPendingMessagesToTextLayout();`
- L607 _protected member_ `TMap<FName, float> CategoryHueMap;`
- L609 _protected prototype_ `float GetCategoryHue(FName CategoryName);`
- L612 _protected member_ `TArray< TSharedPtr<FOutputLogMessage> > Messages;` — All log messages to show in the text box
- L615 _protected member_ `TArray< TSharedPtr<FOutputLogMessage> > PendingMessages;` — Messages pending add, kept separate to avoid a race condition when reading Messages
- L618 _protected member_ `int32 NextPendingMessageIndex;` — Index of the next entry in the Messages array that is pending submission to the text layout
- L621 _protected member_ `int32 CachedNumMessages;` — Holds cached numbers of messages to avoid unnecessary re-filtering
- L624 _protected member_ `bool bNumMessagesCacheDirty;` — Flag indicating the messages count cache needs rebuilding
- L627 _protected member_ `FOutputLogFilter* Filter;` — Visible messages filter
- L629 _protected member_ `FName CategoryToHighlight;`
- L631 _protected member_ `FTextLayout* TextLayout;`
- L634 _protected member_ `FCriticalSection PendingMessagesCriticalSection;` — Output log runs own its own "OutputDeviceRedirector" thread, lock against messages to prevent race conditions

#### Free symbols / members of external scopes

- L61 _delegate_ `DECLARE_DELEGATE_OneParam(FExecuteConsoleCommand, const FString& ) SLATE_BEGIN_ARGS( SConsoleInputBox ) : _SuggestionListPlacement( MenuPlacement_BelowAnchor ) {} SLATE_ARGUMENT( EMenuPlacement, SuggestionListPlacement ) /** Called before executing a command;`

### `Source/Developer/OutputLog/Public/ConsoleInputBoxParameters.h` (Public)


#### struct `UE::OutputLog::FConsoleInputBoxCreationParams`  
`struct FConsoleInputBoxCreationParams`  
_L36-49_
- desc: Parameters used to create a console input box widget
- L39 _public member_ `FSimpleDelegate OnCloseConsole;` — Called when the console requests to be closed.
- L42 _public member_ `FSimpleDelegate OnConsoleCommandExecuted;` — Called after a console command has been executed.
- L45 _public member_ `FInterceptConsoleCommandDelegate OnInterceptConsoleCommand;` — Called to intercept console commands before execution.
- L48 _public member_ `FHistoryOverrideDelegate OnHistoryOverride;` — Called to provide custom command history for a specific executor.

#### struct `UE::OutputLog::FConsoleInputBoxCreationResult`  
`struct FConsoleInputBoxCreationResult`  
_L54-64_
- desc: Result of creating a console input box widget.
- L57 _public member_ `TSharedPtr<SWidget> ConsoleInputBox;` — Root widget representing the console input box.
- L63 _public member_ `TSharedPtr<SMultiLineEditableTextBox> ExposedEditableTextBox;` — Exposed editable text box used for command input. Can be used to control focus, text, or bind additional behavior.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace OutputLog` (scope `UE`)
- L21 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FInterceptConsoleCommandDelegate, const FName& , const FString& );` — Delegate that allows intercepting console commands and optionally handling them. @param ExecutorName Name of the active command executor @param ExecCommand  Command string to evaluate @return True if the command was intercepted (handled) and should not be executed further; false to allow normal execution.
- L21 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FInterceptConsoleCommandDelegate, const FName& , const FString& );` (scope `UE::OutputLog`) — Delegate that allows intercepting console commands and optionally handling them. @param ExecutorName Name of the active command executor @param ExecCommand  Command string to evaluate @return True if the command was intercepted (handled) and should not be executed further; false to allow normal execution.
- L30 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FHistoryOverrideDelegate, const FName& , TArray<FString>& );` — Delegate that allows overriding the command history for a specific executor @param ExecutorName Name of the active command executor @param OutCmdHistory Command history for the executor @return True if the history was overridden; false to use the executor's default history.
- L30 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FHistoryOverrideDelegate, const FName& , TArray<FString>& );` (scope `UE::OutputLog`) — Delegate that allows overriding the command history for a specific executor @param ExecutorName Name of the active command executor @param OutCmdHistory Command history for the executor @return True if the history was overridden; false to use the executor's default history.

### `Source/Developer/OutputLog/Public/OutputLogCreationParams.h` (Public)


#### enum `EOutputLogSettingsMenuFlags`  
`enum class EOutputLogSettingsMenuFlags`  
_L7-22_
- L9 _public enumerator_ `None = 0x00`
- L12 _public enumerator_ `SkipClearOnPie = 0x01` — The clear on Pie button should not be created
- L15 _public enumerator_ `SkipEnableWordWrapping = 0x02` — The Enable world wrapping button should not be created
- L18 _public enumerator_ `SkipOpenSourceButton = 0x04` — Skip the button that opens the source folder of the output log module
- L21 _public enumerator_ `SkipOpenInExternalEditorButton = 0x08` — Skip the button which opens the log in a text editor

#### struct `FOutputLogCreationParams`  
`struct FOutputLogCreationParams`  
_L28-47_
- L31 _public member_ `bool bCreateDockInLayoutButton = false;` — Whether to create the button for docking the log
- L34 _public member_ `EOutputLogSettingsMenuFlags SettingsMenuCreationFlags = EOutputLogSettingsMenuFlags::None;` — Determines what entries the Settings drop-down will ignore
- L37 _public member_ `FAllowLogCategoryCallback AllowAsInitialLogCategory;` — Called when building the initial set of selected log categories
- L40 _public member_ `FDefaultCategorySelectionMap DefaultCategorySelection;` — Maps each log category to whether it should be selected or deselected by default. The caller is responsible to enter valid category names.
- L43 _public member_ `FSimpleDelegate OnCloseConsole;` — Called when the console tab is closed.
- L46 _public member_ `TOptional<int32> LoggingLimit;` — Do we want to support limited console output with a predefined limit.

#### Free symbols / members of external scopes

- L25 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FAllowLogCategoryCallback, const FName);`
- L25 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FAllowLogCategoryCallback, const FName);`
- L26 _typedef_ `using FDefaultCategorySelectionMap = TMap<FName, bool>;`

### `Source/Developer/OutputLog/Public/OutputLogModule.h` (Public)


#### enum `EDebugConsoleStyle::Type`  
`enum Type`  
_L24-31_
- L27 _public enumerator_ `Compact` — Shows the debug console input line with tab completion only
- L30 _public enumerator_ `WithLog` — Shows a scrollable log window with the input line on the bottom

#### struct `FDebugConsoleDelegates`  
`struct FDebugConsoleDelegates`  
_L34-39_
- L36 _public member_ `FSimpleDelegate OnFocusLost;`
- L37 _public member_ `FSimpleDelegate OnConsoleCommandExecuted;`
- L38 _public member_ `FSimpleDelegate OnCloseConsole;`

#### class `FOutputLogModule`  
`class FOutputLogModule : public IModuleInterface`  
_L41-156_
- inherits: `IModuleInterface`
- L44 _public prototype_ `virtual void StartupModule();`
- L45 _public prototype_ `virtual void ShutdownModule();`
- L47 _public member_ `static const FName ModuleName;`
- L48 _public prototype_ `static FOutputLogModule& Get();`
- L49 _public prototype_ `static FOutputLogModule* TryGet();`
- L52 _public prototype_ `virtual bool ShouldHideConsole() const;` — Returns whether debug console widgets should be hidden
- L56 _public prototype_ `virtual TSharedRef<SWidget> MakeConsoleInputBox(TSharedPtr<SMultiLineEditableTextBox>& OutExposedEditableTextBox, const FSimpleDelegate& OnCloseConsole, const FSimpleDelegate& OnConsoleCommandExecuted) const;` — Generates a console input box widget.  Remember, this widget will become invalid if the output log DLL is unloaded on the fly.
- L66 _public prototype_ `virtual UE::OutputLog::FConsoleInputBoxCreationResult MakeConsoleInputBox(const UE::OutputLog::FConsoleInputBoxCreationParams& InCreationParams) const;` — Creates a console input box widget @note The widget becomes invalid if the OutputLog module is unloaded at runtime @param InCreationParams Input box creation parameters @return Result structure that contains the requested widget and additional data
- L68 _public prototype_ `virtual TSharedRef<SWidget> MakeOutputLogDrawerWidget(const FSimpleDelegate& OnCloseConsole);`
- L70 _public prototype_ `virtual TSharedRef<SWidget> MakeOutputLogWidget(const FOutputLogCreationParams& Params);`
- L73 _public prototype_ `virtual void ToggleDebugConsoleForWindow(const TSharedRef<SWindow>& Window, const EDebugConsoleStyle::Type InStyle, const FDebugConsoleDelegates& DebugConsoleDelegates);` — Opens a debug console in the specified window, if not already open
- L76 _public prototype_ `virtual void CloseDebugConsole();` — Closes the debug console for the specified window
- L78 _public prototype_ `virtual void ClearOnPIE(const bool bIsSimulating);`
- L80 _public prototype_ `virtual void FocusOutputLogConsoleBox(const TSharedRef<SWidget> OutputLogToFocus);`
- L82 _public prototype_ `virtual const TSharedPtr<SWidget> GetOutputLog() const;`
- L87 _public prototype_ `virtual void SuspendGlobalLog();` — Suspend the collection of global log data that is used for constructing output log widgets.  This global log will perpetually collect logging information perpetually and may exhaust memory.
- L92 _public prototype_ `virtual void ResumeGlobalLog();` — Resume global log collection. Note this has a memory impact as log entries are stored for the life of the running edit.
- L95 _public prototype_ `void FocusOutputLog();` — Opens and focuses on the Output Log Drawer if the status bar exists, otherwise opens and focuses on the Output Log Tab.
- L98 _public prototype_ `virtual void FocusOutputLogAndScrollToEnd();` — Same as FocusOutputLog(), but also scrolls the output log window to the end.
- L100 _public function_ `const TSharedPtr<SDockTab> GetOutputLogTab() const`
- L111 _public prototype_ `void UpdateOutputLogFilter(const TArray<FName>& CategoriesToShow, TOptional<bool> bShowErrors = TOptional<bool>(), TOptional<bool> bShowWarnings = TOptional<bool>(), TOptional<bool> bShowLogs = TOptional<bool>());` — Change the output log's filter. If CategoriesToShow is empty, all categories will be shown.
- L112 _public prototype_ `void UpdateOutputLogFilter(const TArray<FName>& CategoriesToShow, const FOutputFilterParams& InParams);`
- L115 _public prototype_ `void OpenOutputLog() const;` — Opens the output log tab, or brings it to front if it's already open
- L119 _public prototype_ `virtual bool ShouldCycleToOutputLogDrawer() const;` — Returns the value of bCycleToOutputLogDrawer from the module OutputLogSettings. This function helps StatusBar to access properties in OutputLogSetting through OutputLogModule to avoid dependencies.
- L121 _public member_ `TMulticastDelegate<void()> OnOutputLogDrawerCleared;`
- L124 _public prototype_ `virtual const TUniquePtr<FNamePermissionList>& GetConsoleCommandExecutorPermissionList() const;` — Returns list used to filter which command executors are allowed
- L127 _private prototype_ `TSharedRef<SDockTab> SpawnOutputLogTab(const FSpawnTabArgs& Args);`
- L128 _private prototype_ `void SaveDockedTabSettings();`
- L130 _private prototype_ `TSharedRef<SDockTab> SpawnDeviceOutputLogTab(const FSpawnTabArgs& Args);`
- L134 _private member_ `TSharedPtr<FOutputLogHistory> OutputLogHistory;` — Our global output log app spawner
- L137 _private member_ `TUniquePtr<FOutputLogFilter> OutputLogFilterCache;` — Caches the user selected Filters as the OutputLog tab can be closed and remade multiple times
- L140 _private member_ `TWeakPtr<SOutputLog> OutputLog;` — Our global active output log that belongs to a tab
- L143 _private member_ `TWeakPtr<SDockTab> OutputLogTab;` — Global tab that the output log resides in
- L146 _private member_ `TWeakPtr<SOutputLog> OutputLogDrawer;` — The output log that lives in a status bar drawer
- L149 _private member_ `TWeakPtr<SWidget> DebugConsole;` — Weak pointer to a debug console that's currently open, if any
- L152 _private member_ `TWeakPtr<SWidget> PreviousKeyboardFocusedWidget;` — Weak pointer to the widget to focus once they console window closes
- L155 _private member_ `TUniquePtr<FNamePermissionList> ConsoleCommandExecutorPermissionList;` — List used to filter which command executors are allowed

#### struct `FOutputLogModule::FOutputFilterParams`  
`struct FOutputFilterParams`  
_L102-108_
- L104 _public member_ `TOptional<bool> bShowErrors;`
- L105 _public member_ `TOptional<bool> bShowWarnings;`
- L106 _public member_ `TOptional<bool> bShowLogs;`
- L107 _public member_ `TOptional<TSet<ELogVerbosity::Type>> IgnoreFilterVerbosities;`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace EDebugConsoleStyle`

### `Source/Developer/OutputLog/Public/OutputLogSettings.h` (Public)


#### enum `ELogCategoryColorizationMode`  
`enum class ELogCategoryColorizationMode : uint8`  
_L14-27_
- reflection: `UENUM()`
- L17 _public enumerator_ `None` — Do not colorize based on log categories
- L20 _public enumerator_ `ColorizeWholeLine` — Colorize the entire log line, but not warnings or errors
- L23 _public enumerator_ `ColorizeCategoryOnly` — Colorize only the category name (including on warnings and errors)
- L26 _public enumerator_ `ColorizeCategoryAsBadge` — Colorize the background of the category name (including on warnings and errors)

#### enum `ELogLevelFilter`  
`enum class ELogLevelFilter : uint8`  
_L30-38_
- reflection: `UENUM()`
- L33 _public enumerator_ `None` — Show none of the logs at this level.
- L35 _public enumerator_ `Enabled` — Show only the enabled logs at this level.
- L37 _public enumerator_ `All` — Show all logs at this level.

#### struct `FOutputLogCategorySettings`  
`struct FOutputLogCategorySettings`  
_L41-50_
- reflection: `USTRUCT()`
- L46 _public member_ `FName Name;` — `UPROPERTY()`
- L49 _public member_ `bool bEnabled = true;` — `UPROPERTY()`

#### struct `FOutputLogFilterSettings`  
`struct FOutputLogFilterSettings`  
_L53-79_
- reflection: `USTRUCT()`
- L58 _public member_ `ELogLevelFilter MessagesFilter = ELogLevelFilter::Enabled;` — `UPROPERTY()`
- L61 _public member_ `ELogLevelFilter WarningsFilter = ELogLevelFilter::Enabled;` — `UPROPERTY()`
- L64 _public member_ `ELogLevelFilter ErrorsFilter = ELogLevelFilter::Enabled;` — `UPROPERTY()`
- L67 _public member_ `FText FilterText;` — `UPROPERTY()`
- L75 _public member_ `TArray<FOutputLogCategorySettings> Categories;` — `UPROPERTY()` — Note that an empty list in settings implicitly means "all" categories. This will invert state if a user explicitly disables all categories, but that is acceptable. An empty log simply looks broken.
- L78 _public member_ `bool bSelectNewCategories = true;` — `UPROPERTY()`

#### class `UOutputLogSettings`  
`class UOutputLogSettings : public UObject`  
_L85-155_
- reflection: `UCLASS(MinimalAPI, config=EditorPerProjectUserSettings)`
- inherits: `UObject`
- desc: Implements the Editor style settings.
- L90 _public function_ `UOutputLogSettings()`
- L99 _public member_ `int32 LogFontSize;` — `UPROPERTY(EditAnywhere, config, Category="Output Log", meta=(DisplayName="Log Font Size", ConfigRestartRequired=true))` — The font size used in the output log
- L103 _public member_ `TEnumAsByte<ELogTimes::Type> LogTimestampMode;` — `UPROPERTY(EditAnywhere, config, Category="Output Log", meta=(DisplayName = "Output Log Window Timestamp Mode"))` — The display mode for timestamps in the output log window
- L107 _public member_ `ELogCategoryColorizationMode CategoryColorizationMode;` — `UPROPERTY(EditAnywhere, config, Category = "Output Log")` — How should categories be colorized in the output log?
- L114 _public member_ `bool bCycleToOutputLogDrawer;` — `UPROPERTY(EditAnywhere, config, Category = "Output Log", meta = (DisplayName = "Open Output Log Drawer with Console Command Shortcut"))` — If checked pressing the console command shortcut will cycle between focusing the status bar console, opening the output log drawer, and back to the previous focus target. If unchecked, the console command shortcut will only focus the status bar console
- L117 _public member_ `bool bEnableOutputLogWordWrap;` — `UPROPERTY(EditAnywhere, config, Category = "Output Log")`
- L121 _public member_ `bool bEnableOutputLogClearOnPIE;` — `UPROPERTY(config)`
- L126 _public member_ `FOutputLogFilterSettings OutputLogTabFilter;` — `UPROPERTY(config)` — The most recently used filter settings.
- L135 _public prototype_ `DECLARE_EVENT_OneParam(UOutputLogSettings, FSettingChangedEvent, FName );` — Returns an event delegate that is executed when a setting has changed. @return The delegate.
- L136 _public function_ `FSettingChangedEvent& OnSettingChanged()`
- L141 _protected function_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override` — UObject overrides
- L154 _private member_ `FSettingChangedEvent SettingChangedEvent;` — Holds an event delegate that is executed when a setting has changed.

#### Free symbols / members of external scopes

- L135 _delegate_ `DECLARE_EVENT_OneParam(UOutputLogSettings, FSettingChangedEvent, FName );` — Returns an event delegate that is executed when a setting has changed. @return The delegate.
