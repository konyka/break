# Developer / SessionFrontend

- module root: `Source/Developer/SessionFrontend`
- headers: 20; symbols: 316
- symbol kinds: class=22, delegate=4, enum=1, enumerator=3, function=76, macro=6, member=94, prototype=102, struct=2, typedef=6
- PrivateDependencyModuleNames: ApplicationCore, AutomationWindow, DesktopPlatform, InputCore, Json, ScreenShotComparison, ScreenShotComparisonTools, SessionServices, SlateCore, TargetPlatform, TraceTools, WorkspaceMenuStructure
- PrivateIncludePathModuleNames: Messaging, TargetDeviceServices
- PublicDependencyModuleNames: Core, CoreUObject, Slate

### `Source/Developer/SessionFrontend/Private/Models/SessionBrowserOwnerFilter.h` (Private)


#### class `FSessionBrowserOwnerFilter`  
`class FSessionBrowserOwnerFilter : public TSharedFromThis<FSessionBrowserOwnerFilter>`  
_L22-96_
- inherits: `TSharedFromThis<FSessionBrowserOwnerFilter>`
- desc: Implements a view model for a session owner filter.
- L34 _public function_ `FSessionBrowserOwnerFilter( const FString& InOwnerName, bool InEnabled, FOnSessionBrowserOwnerFilterStateChanged InOnStateChanged ) : Enabled(InEnabled) , OwnerName(InOwnerName) , OnStateChanged(InOnStateChanged)` — Creates and initializes a new instance. @param InOwnerName The user name of the session owner. @param InEnabled Whether this filter is enabled. @param InOnStateChanged A delegate that is executed when the filter's enabled state changed.
- L47 _public function_ `void EnableFromCheckState( ECheckBoxState CheckState )` — Enables or disables the filter based on the specified check box state. @param CheckState The check box state.
- L59 _public function_ `const FString& GetOwnerName()` — Gets the filter's owner name. @return The user name of the session owner.
- L69 _public function_ `ECheckBoxState GetCheckStateFromIsEnabled() const` — Gets the check box state from the filter's enabled state. @return Checked if the filter is enabled, Unchecked otherwise.
- L79 _public function_ `bool IsEnabled() const` — Checks whether this filter is enabled. @return true if the filter is enabled, false otherwise.
- L87 _private member_ `bool Enabled;` — Holds a flag indicating whether this filter is enabled.
- L90 _private member_ `FString OwnerName;` — Holds the name of the session owner.
- L95 _private member_ `FOnSessionBrowserOwnerFilterStateChanged OnStateChanged;` — Holds a delegate that is executed when the filter's enabled state changed.

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnSessionBrowserOwnerFilterStateChanged, const FString&, bool);` — Delegate type for session owner filter state changes. The first parameter is the name of the owner that changed its enabled state. The second parameter is the new enabled state.
- L16 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnSessionBrowserOwnerFilterStateChanged, const FString&, bool);` — Delegate type for session owner filter state changes. The first parameter is the name of the owner that changed its enabled state. The second parameter is the new enabled state.
- L100 _typedef_ `typedef TSharedPtr<FSessionBrowserOwnerFilter> FSessionBrowserOwnerFilterPtr;` — Type definition for shared pointers to instances of FSessionBrowserOwnerFilter.
- L103 _typedef_ `typedef TSharedRef<FSessionBrowserOwnerFilter> FSessionBrowserOwnerFilterRef;` — Type definition for shared references to instances of FSessionBrowserOwnerFilter.

### `Source/Developer/SessionFrontend/Private/Models/SessionBrowserTreeItems.h` (Private)


#### enum `ESessionBrowserTreeNodeType`  
`enum class ESessionBrowserTreeNodeType`  
_L9-14_
- L11 _public enumerator_ `Group`
- L12 _public enumerator_ `Instance`
- L13 _public enumerator_ `Session`

#### class `FSessionBrowserTreeItem`  
`class FSessionBrowserTreeItem`  
_L20-94_
- desc: Base class for items in the session tree view.
- L25 _public prototype_ `virtual ~FSessionBrowserTreeItem() = default;` — Virtual destructor.
- L35 _public function_ `void AddChild(const TSharedRef<FSessionBrowserTreeItem>& Child)` — Adds a child process item to this item. @param The child item to add. @see ClearChildren, GetChildren
- L45 _public function_ `void ClearChildren()` — Clears the collection of child items. @see AddChild, GetChildren
- L56 _public function_ `const TArray<TSharedPtr<FSessionBrowserTreeItem>>& GetChildren()` — Gets the child items. @return Child items. @see AddChild, ClearChildren, GetParent
- L67 _public function_ `const TSharedPtr<FSessionBrowserTreeItem>& GetParent()` — Gets the parent item. @return Parent item. @see GetChildren, SetParent
- L78 _public function_ `void SetParent(const TSharedPtr<FSessionBrowserTreeItem>& Node)` — Sets the parent item. @param Node The parent item to set. @see GetParent
- L85 _public prototype_ `virtual ESessionBrowserTreeNodeType GetType() = 0;`
- L90 _private member_ `TArray<TSharedPtr<FSessionBrowserTreeItem>> Children;` — Holds the child process items.
- L93 _private member_ `TSharedPtr<FSessionBrowserTreeItem> Parent;` — Holds a pointer to the parent item.

#### class `FSessionBrowserGroupTreeItem`  
`class FSessionBrowserGroupTreeItem : public FSessionBrowserTreeItem`  
_L100-152_
- inherits: `FSessionBrowserTreeItem`
- desc: Implements a group item in the session tree view.
- L106 _public function_ `FSessionBrowserGroupTreeItem(const FText& InGroupName, const FText& InToolTipText) : GroupName(InGroupName) , ToolTipText(InToolTipText)` — Creates and initializes a new instance.
- L112 _public prototype_ `virtual ~FSessionBrowserGroupTreeItem() = default;` — Virtual destructor.
- L121 _public function_ `FText GetGroupName() const` — Gets the name of the group associated with this item. @return Group name.
- L131 _public function_ `FText GetToolTipText() const` — Gets the tool tip text of the group associated with this item. @return Tool tip text.
- L140 _public function_ `virtual ESessionBrowserTreeNodeType GetType() override`
- L148 _private member_ `FText GroupName;` — The name of the group associated with this item.
- L151 _private member_ `FText ToolTipText;` — The tool tip text.

#### class `FSessionBrowserInstanceTreeItem`  
`class FSessionBrowserInstanceTreeItem : public FSessionBrowserTreeItem`  
_L158-196_
- inherits: `FSessionBrowserTreeItem`
- desc: Implements a instance item in the session tree view.
- L164 _public function_ `FSessionBrowserInstanceTreeItem(const TSharedRef<ISessionInstanceInfo>& InInstanceInfo) : InstanceInfo(InInstanceInfo)` — Creates and initializes a new instance.
- L169 _public prototype_ `virtual ~FSessionBrowserInstanceTreeItem() = default;` — Virtual destructor.
- L178 _public function_ `TSharedPtr<ISessionInstanceInfo> GetInstanceInfo() const` — Gets the instance info associated with this item. @return Instance info.
- L187 _public function_ `virtual ESessionBrowserTreeNodeType GetType() override`
- L195 _private member_ `TWeakPtr<ISessionInstanceInfo> InstanceInfo;` — Weak pointer to the instance info associated with this item.

#### class `FSessionBrowserSessionTreeItem`  
`class FSessionBrowserSessionTreeItem : public FSessionBrowserTreeItem`  
_L202-240_
- inherits: `FSessionBrowserTreeItem`
- desc: Implements a session item in the session tree view.
- L208 _public function_ `FSessionBrowserSessionTreeItem(const TSharedRef<ISessionInfo>& InSessionInfo) : SessionInfo(InSessionInfo)` — Creates and initializes a new instance.
- L213 _public prototype_ `virtual ~FSessionBrowserSessionTreeItem() = default;` — Virtual destructor.
- L222 _public function_ `TSharedPtr<ISessionInfo> GetSessionInfo() const` — Gets the session info associated with this item. @return Session info.
- L231 _public function_ `virtual ESessionBrowserTreeNodeType GetType() override`
- L239 _private member_ `TWeakPtr<ISessionInfo> SessionInfo;` — Weak pointer to the session info associated with this item.

### `Source/Developer/SessionFrontend/Private/Models/SessionConsoleCategoryFilter.h` (Private)


#### class `FSessionConsoleCategoryFilter`  
`class FSessionConsoleCategoryFilter : public TSharedFromThis<FSessionConsoleCategoryFilter>`  
_L20-94_
- inherits: `TSharedFromThis<FSessionConsoleCategoryFilter>`
- desc: Implements a view model for a console log category filter.
- L32 _public function_ `FSessionConsoleCategoryFilter( const FName& InCategory, bool InEnabled, FOnSessionConsoleCategoryFilterStateChanged InOnStateChanged ) : Category(InCategory) , Enabled(InEnabled) , OnStateChanged(InOnStateChanged)` — Creates and initializes a new instance. @param InCategory The filter category. @param InEnabled Whether this filter is enabled. @param InOnStateChanged A delegate that is executed when the filter's enabled state changed.
- L45 _public function_ `void EnableFromCheckState( ECheckBoxState CheckState )` — Enables or disables the filter based on the specified check box state. @param CheckState The check box state.
- L57 _public function_ `FName GetCategory()` — Gets the filter's category. @return The category name.
- L67 _public function_ `ECheckBoxState GetCheckStateFromIsEnabled() const` — Gets the check box state from the filter's enabled state. @return Checked if the filter is enabled, Unchecked otherwise.
- L77 _public function_ `bool IsEnabled() const` — Checks whether this filter is enabled. @return true if the filter is enabled, false otherwise.
- L85 _private member_ `FName Category;` — Holds the filter's category.
- L88 _private member_ `bool Enabled;` — Holds a flag indicating whether this filter is enabled.
- L93 _private member_ `FOnSessionConsoleCategoryFilterStateChanged OnStateChanged;` — Holds a delegate that is executed when the filter's enabled state changed.

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnSessionConsoleCategoryFilterStateChanged, const FName&, bool);` — Delegate type for category filter state changes. The first parameter is the name of the category that changed its enabled state. The second parameter is the new enabled state.
- L14 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnSessionConsoleCategoryFilterStateChanged, const FName&, bool);` — Delegate type for category filter state changes. The first parameter is the name of the category that changed its enabled state. The second parameter is the new enabled state.
- L98 _typedef_ `typedef TSharedPtr<FSessionConsoleCategoryFilter> FSessionConsoleCategoryFilterPtr;` — Type definition for shared pointers to instances of FSessionConsoleCategoryFilter.
- L101 _typedef_ `typedef TSharedRef<FSessionConsoleCategoryFilter> FSessionConsoleCategoryFilterRef;` — Type definition for shared references to instances of FSessionConsoleCategoryFilter.

### `Source/Developer/SessionFrontend/Private/Models/SessionConsoleCommands.h` (Private)


#### class `FSessionConsoleCommands`  
`class FSessionConsoleCommands : public TCommands<FSessionConsoleCommands>`  
_L16-46_
- inherits: `TCommands<FSessionConsoleCommands>`
- desc: The device details commands.
- L22 _public function_ `FSessionConsoleCommands() : TCommands<FSessionConsoleCommands>( "SessionConsole", NSLOCTEXT("Contexts", "SessionConsole", "Session Console"), NAME_None, FSessionFrontendStyle::GetStyleSetName() )` — Default constructor.
- L34 _public function_ `virtual void RegisterCommands() override`
- L43 _public member_ `TSharedPtr<FUICommandInfo> Clear;`
- L44 _public member_ `TSharedPtr<FUICommandInfo> SessionCopy;`
- L45 _public member_ `TSharedPtr<FUICommandInfo> SessionSave;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define LOCTEXT_NAMESPACE "SessionConsoleCommands"`

### `Source/Developer/SessionFrontend/Private/Models/SessionConsoleLogMessage.h` (Private)


#### struct `FSessionConsoleLogMessage`  
`struct FSessionConsoleLogMessage`  
_L14-51_
- desc: Structure for log messages that are displayed in the session console panel.
- L17 _public member_ `FName Category;` — Holds the log category.
- L20 _public member_ `FString InstanceName;` — Holds the name of the sender's engine instance.
- L23 _public member_ `FMessageAddress Sender;` — Holds the sender's address.
- L26 _public member_ `FString Text;` — Holds the message text.
- L29 _public member_ `FDateTime Time;` — Holds the time at which the message was generated.
- L32 _public member_ `double TimeSeconds;` — Holds the number of seconds from the start of the instance at which the message was generated.
- L35 _public member_ `ELogVerbosity::Type Verbosity;` — Holds the verbosity type.
- L42 _public function_ `FSessionConsoleLogMessage(const FMessageAddress& InSender, const FString& InInstanceName, float InTimeSeconds, const FString& InText, ELogVerbosity::Type InVerbosity, const FName& InCategory) : Category(InCategory) , InstanceName(InInstanceName) , Sender(InSender) , Text((InCategory != NAME_None) ? InCategory.ToString() + TEXT(": ") + InText : InText) , Time(FDateTime::Now()) , TimeSeconds(InTimeSeconds) , Verbosity(InVerbosity)` — Creates and initializes a new instance.

### `Source/Developer/SessionFrontend/Private/Models/SessionConsoleVerbosityFilter.h` (Private)


#### class `FSessionConsoleVerbosityFilter`  
`class FSessionConsoleVerbosityFilter : public TSharedFromThis<FSessionConsoleVerbosityFilter>`  
_L20-124_
- inherits: `TSharedFromThis<FSessionConsoleVerbosityFilter>`
- desc: Implements a view model for a console log category filter.
- L34 _public function_ `FSessionConsoleVerbosityFilter( ELogVerbosity::Type InVerbosity, const FSlateBrush* InIcon, bool InEnabled, const FString& InName, FOnSessionConsoleVerbosityFilterStateChanged InOnStateChanged) : Enabled(InEnabled) , Icon(InIcon) , Name(InName) , Verbosity(InVerbosity) , OnStateChanged(InOnStateChanged)` — Creates and initializes a new instance. @param InVerbosity The log verbosity level to filter. @param InIcon The filter's icon. @param InEnabled Whether this filter is enabled. @param InName The filter's name. @param InOnStateChanged A delegate that is executed when the filter's enabled state changed.
- L49 _public function_ `void EnableFromCheckState( ECheckBoxState CheckState )` — Enables or disables the filter based on the specified check box state. @param CheckState The check box state.
- L61 _public function_ `ECheckBoxState GetCheckStateFromIsEnabled() const` — Gets the check box state from the filter's enabled state. @return Checked if the filter is enabled, Unchecked otherwise.
- L71 _public function_ `const FSlateBrush* GetIcon() const` — Gets the filter's icon. @return Filter icon image.
- L81 _public function_ `const FString& GetName() const` — Gets the filter's name. @return The name string.
- L91 _public function_ `ELogVerbosity::Type GetVerbosity() const` — Gets the filter verbosity level. @return Verbosity level.
- L101 _public function_ `bool IsEnabled() const` — Checks whether this filter is enabled. @return true if the filter is enabled, false otherwise.
- L109 _private member_ `bool Enabled;` — Holds a flag indicating whether this filter is enabled.
- L112 _private member_ `const FSlateBrush* Icon;` — Holds the icon image.
- L115 _private member_ `FString Name;` — Holds the filter's name.
- L118 _private member_ `ELogVerbosity::Type Verbosity;` — Holds the filter's verbosity level.
- L123 _private member_ `FOnSessionConsoleVerbosityFilterStateChanged OnStateChanged;` — Holds a delegate that is executed when the filter's enabled state changed.

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnSessionConsoleVerbosityFilterStateChanged, ELogVerbosity::Type, bool);` — Delegate type for verbosity filter state changes. The first parameter is the verbosity level that changed its enabled state. The second parameter is the new enabled state.
- L14 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnSessionConsoleVerbosityFilterStateChanged, ELogVerbosity::Type, bool);` — Delegate type for verbosity filter state changes. The first parameter is the verbosity level that changed its enabled state. The second parameter is the new enabled state.
- L128 _typedef_ `typedef TSharedPtr<FSessionConsoleVerbosityFilter> FSessionConsoleVerbosityFilterPtr;` — Type definition for shared pointers to instances of FSessionConsoleVerbosityFilter.
- L131 _typedef_ `typedef TSharedRef<FSessionConsoleVerbosityFilter> FSessionConsoleVerbosityFilterRef;` — Type definition for shared references to instances of FSessionConsoleVerbosityFilter.

### `Source/Developer/SessionFrontend/Private/SessionFrontendStyle.h` (Private)


#### class `FSessionFrontendStyle`  
`class FSessionFrontendStyle`  
_L7-23_
- L10 _public prototype_ `static void Initialize();`
- L11 _public prototype_ `static void Shutdown();`
- L13 _public prototype_ `static const ISlateStyle& Get();`
- L14 _public prototype_ `static const FName& GetStyleSetName();`
- L15 _public function_ `static const FSlateBrush* GetBrush(FName PropertyName, const ANSICHAR* Specifier = NULL)`
- L22 _private member_ `static TSharedPtr<class FSlateStyleSet> StyleSet;` — Singleton instances of this style.

### `Source/Developer/SessionFrontend/Private/Widgets/Browser/SSessionBrowserCommandBar.h` (Private)


#### class `SSessionBrowserCommandBar`  
`class SSessionBrowserCommandBar : public SCompoundWidget`  
_L12-28_
- inherits: `SCompoundWidget`
- desc: Implements the session browser's command bar widget.
- L17 _public function_ `SLATE_BEGIN_ARGS(SSessionBrowserCommandBar)`
- L27 _public prototype_ `void Construct( const FArguments& InArgs );` — Construct this widget @param InArgs The declaration data for this widget.

### `Source/Developer/SessionFrontend/Private/Widgets/Browser/SSessionBrowserTreeGroupRow.h` (Private)


#### class `SSessionBrowserTreeGroupRow`  
`class SSessionBrowserTreeGroupRow : public STableRow<TSharedPtr<FSessionBrowserGroupTreeItem>>`  
_L28-163_
- inherits: `STableRow<TSharedPtr<FSessionBrowserGroupTreeItem>>`
- desc: Implements a row widget for the session browser tree.
- L33 _public function_ `SLATE_BEGIN_ARGS(SSessionBrowserTreeGroupRow)`
- L47 _public function_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView)`
- L98 _protected function_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override`
- L115 _private function_ `const FSlateBrush* HandleBorderBackgroundImage() const` — Callback for getting the background image of the row's border.
- L128 _private function_ `FSlateColor HandleGroupNameColorAndOpacity() const` — Callback for getting the group name text's color.
- L136 _private function_ `FText HandleGroupNameText() const` — Callback for getting the group name text.
- L149 _private function_ `const FSlateBrush* HandlePullDownImage() const` — Gets the image for the pull-down icon.
- L159 _private member_ `TAttribute<FText> HighlightText;` — The highlight string for this row.
- L162 _private member_ `TSharedPtr<FSessionBrowserGroupTreeItem> Item;` — A reference to the tree item that is displayed in this row.

#### Free symbols / members of external scopes

- L23 _macro_ `#define LOCTEXT_NAMESPACE "SSessionBrowserTreeRow"`

### `Source/Developer/SessionFrontend/Private/Widgets/Browser/SSessionBrowserTreeInstanceRow.h` (Private)


#### class `SSessionBrowserTreeInstanceRow`  
`class SSessionBrowserTreeInstanceRow : public SMultiColumnTableRow<TSharedPtr<FSessionBrowserTreeItem>>`  
_L33-329_
- inherits: `SMultiColumnTableRow<TSharedPtr<FSessionBrowserTreeItem>>`
- desc: Implements a row widget for the session browser tree.
- L38 _public function_ `SLATE_BEGIN_ARGS(SSessionBrowserTreeInstanceRow)`
- L52 _public function_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView)` — Constructs the widget. @param InArgs The construction arguments.
- L69 _public function_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn( const FName& ColumnName ) override`
- L193 _private function_ `const FSlateBrush* HandleAuthorizedImage() const` — Callback for getting the image of the Authorized icon.
- L206 _private function_ `FText HandleDeviceColumnText() const` — Callback for getting the text in the 'Device' column.
- L219 _private function_ `FSlateColor GetNameImageColor() const` — Callback for getting the image color for the name column.
- L232 _private function_ `FSlateColor GetNameTextColor() const` — Callback for getting the text color for the name column.
- L245 _private function_ `const FSlateBrush* HandleInstanceBorderBrush() const` — Callback for getting the border brush for this row.
- L263 _private function_ `FText HandleInstanceTypeText() const` — Callback for getting the type of the session instance.
- L276 _private function_ `FText HandleLevelColumnText() const` — Callback for getting the instance's current level.
- L289 _private function_ `FSlateColor HandleStatusImageColor() const` — Callback for getting the image of the Status icon.
- L307 _private function_ `FSlateColor HandleTextColorAndOpacity() const` — Callback for getting the foreground text color.
- L325 _private member_ `TAttribute<FText> HighlightText;` — The highlight string for this row.
- L328 _private member_ `TSharedPtr<FSessionBrowserInstanceTreeItem> Item;` — A reference to the tree item that is displayed in this row.

#### Free symbols / members of external scopes

- L28 _macro_ `#define LOCTEXT_NAMESPACE "SSessionBrowserTreeRow"`

### `Source/Developer/SessionFrontend/Private/Widgets/Browser/SSessionBrowserTreeSessionRow.h` (Private)


#### class `SSessionBrowserTreeSessionRow`  
`class SSessionBrowserTreeSessionRow : public STableRow<TSharedPtr<FSessionBrowserSessionTreeItem>>`  
_L29-199_
- inherits: `STableRow<TSharedPtr<FSessionBrowserSessionTreeItem>>`
- desc: Implements a row widget for the session browser tree.
- L34 _public function_ `SLATE_BEGIN_ARGS(SSessionBrowserTreeSessionRow)`
- L48 _public function_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView)`
- L93 _protected function_ `FText SanitizeSessionName(const TSharedPtr<ISessionInfo>& SessionInfo) const`
- L135 _protected function_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override`
- L152 _private function_ `const FSlateBrush* HandleBorderBackgroundImage() const` — Callback for getting the background image of the row's border.
- L165 _private function_ `FText HandleBorderToolTipText() const` — Callback for getting the text of the row border's tool tip.
- L187 _private function_ `FText HandleSessionNameText() const` — Callback for getting the name of the session.
- L195 _private member_ `TAttribute<FText> HighlightText;` — The highlight string for this row.
- L198 _private member_ `TSharedPtr<FSessionBrowserSessionTreeItem> Item;` — A reference to the tree item that is displayed in this row.

#### Free symbols / members of external scopes

- L24 _macro_ `#define LOCTEXT_NAMESPACE "SSessionBrowserTreeRow"`

### `Source/Developer/SessionFrontend/Private/Widgets/Console/SSessionConsole.h` (Private)


#### class `SSessionConsole`  
`class SSessionConsole : public SCompoundWidget`  
_L29-192_
- inherits: `SCompoundWidget`
- desc: Implements the session console panel. This panel receives console log messages from a remote engine session and can also send console commands to it.
- L34 _public function_ `SLATE_BEGIN_ARGS(SSessionConsole)`
- L40 _public prototype_ `~SSessionConsole();` — Destructor.
- L50 _public prototype_ `void Construct(const FArguments& InArgs, TSharedRef<ISessionManager> InSessionManager);` — Construct this widget @param InArgs The declaration data for this widget. @param InSessionManager The session manager to use.
- L55 _protected prototype_ `void BindCommands();` — Binds the device commands on our toolbar.
- L62 _protected prototype_ `void ClearLog();` — Clears the log list view. @see CopyLog, ReloadLog, SaveLog
- L69 _protected prototype_ `void CopyLog();` — Copies the selected log messages to the clipboard. @see ClearLog, ReloadLog, SaveLog
- L77 _protected prototype_ `void ReloadLog(bool FullyReload);` — Reloads the log messages for the currently selected engine instances. @param FullyReload Whether to fully reload the log entries or only re-apply filtering. @see ClearLog, CopyLog, SaveLog
- L84 _protected prototype_ `void SaveLog();` — Saves all log messages to a file. @see ClearLog, CopyLog, ReloadLog
- L91 _protected prototype_ `void SendCommand(const FString& CommandString);` — Sends the command entered into the input field. @param CommandString The command string to send.
- L97 _protected prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L102 _private prototype_ `void HandleClearActionExecute();` — Callback for executing the 'Clear' action.
- L105 _private prototype_ `bool HandleClearActionCanExecute();` — Callback for determining the 'Clear' action can execute.
- L108 _private prototype_ `void HandleCopyActionExecute();` — Callback for executing the 'Copy' action.
- L111 _private prototype_ `bool HandleCopyActionCanExecute();` — Callback for determining the 'Copy' action can execute.
- L114 _private prototype_ `void HandleSaveActionExecute();` — Callback for executing the 'Save' action.
- L117 _private prototype_ `bool HandleSaveActionCanExecute();` — Callback for determining the 'Save' action can execute.
- L120 _private prototype_ `void HandleCommandBarPromoteToShortcutClicked(const FString& CommandString);` — Callback for promoting console command to shortcuts.
- L123 _private prototype_ `void HandleCommandSubmitted(const FString& CommandString);` — Callback for submitting console commands.
- L126 _private prototype_ `void HandleFilterChanged();` — Callback for changing the filter settings.
- L129 _private prototype_ `void HandleLogListItemScrolledIntoView(TSharedPtr<FSessionLogMessage> Item, const TSharedPtr<ITableRow>& TableRow);` — Callback for scrolling a log item into view.
- L132 _private prototype_ `TSharedRef<ITableRow> HandleLogListGenerateRow(TSharedPtr<FSessionLogMessage> Message, const TSharedRef<STableViewBase>& OwnerTable);` — Callback for generating a row widget for the log list view.
- L135 _private prototype_ `FText HandleLogListGetHighlightText() const;` — Callback for getting the highlight string for log messages.
- L138 _private prototype_ `void HandleLogListSelectionChanged(TSharedPtr<FSessionLogMessage> InItem, ESelectInfo::Type SelectInfo);` — Callback for selecting log messages.
- L141 _private prototype_ `bool HandleMainContentIsEnabled() const;` — Callback for getting the enabled state of the console box.
- L144 _private prototype_ `EVisibility HandleSelectSessionOverlayVisibility() const;` — Callback for determining the visibility of the 'Select a session' overlay.
- L147 _private prototype_ `void HandleSessionManagerInstanceSelectionChanged(const TSharedPtr<ISessionInstanceInfo>& Instance, bool Selected);` — Callback for changing the engine instance selection.
- L150 _private prototype_ `void HandleSessionManagerLogReceived(const TSharedRef<ISessionInfo>& Session, const TSharedRef<ISessionInstanceInfo>& Instance, const TSharedRef<FSessionLogMessage>& Message);` — Callback for received log entries.
- L153 _private prototype_ `void HandleSessionManagerSelectedSessionChanged(const TSharedPtr<ISessionInfo>& SelectedSession);` — Callback for changing the selected session.
- L158 _private member_ `TArray<TSharedPtr<FSessionLogMessage>> AvailableLogs;` — Holds an unfiltered list of available log messages.
- L161 _private member_ `TSharedPtr<SSessionConsoleCommandBar> CommandBar;` — Holds the command bar.
- L164 _private member_ `TSharedPtr<SSessionConsoleFilterBar> FilterBar;` — Holds the filter bar.
- L167 _private member_ `TSharedPtr<SSearchBox> FindBar;` — Holds the find bar.
- L170 _private member_ `FString HighlightText;` — Holds the highlight text.
- L173 _private member_ `FString LastLogFileSaveDirectory;` — Holds the directory where the log file was last saved to.
- L176 _private member_ `TSharedPtr<SListView<TSharedPtr<FSessionLogMessage>>> LogListView;` — Holds the log list view.
- L179 _private member_ `TArray<TSharedPtr<FSessionLogMessage>> LogMessages;` — Holds the filtered list of log messages.
- L182 _private member_ `TSharedPtr<ISessionManager> SessionManager;` — Holds the session manager.
- L185 _private member_ `TSharedPtr<SSessionConsoleShortcutWindow> ShortcutWindow;` — Holds the shortcut window.
- L188 _private member_ `bool ShouldScrollToLast;` — Holds a flag indicating whether the log list should auto-scroll to the last item.
- L191 _private member_ `TSharedPtr<FUICommandList> UICommandList;` — The command list for controlling the device

### `Source/Developer/SessionFrontend/Private/Widgets/Console/SSessionConsoleCommandBar.h` (Private)


#### class `SSessionConsoleCommandBar`  
`class SSessionConsoleCommandBar : public SCompoundWidget`  
_L20-101_
- inherits: `SCompoundWidget`
- desc: Implements the session console's command bar widget.
- L25 _public function_ `SLATE_BEGIN_ARGS(SSessionConsoleCommandBar)`
- L42 _public prototype_ `void Construct(const FArguments& InArgs);` — Construct this widget @param InArgs The declaration data for this widget.
- L49 _public prototype_ `void SetNumSelectedInstances(int Count);` — Sets the number of selected engine instances. @param Count Number of selected instances.
- L58 _protected prototype_ `void SubmitCommand(const FString& Command);` — Submits the entered command. @param Command the command to submit.
- L63 _private prototype_ `void HandleInputTextChanged(const FText& InText);` — Handles changing the input text box's content.
- L66 _private prototype_ `void HandleInputTextCommitted(const FText& InText, ETextCommit::Type CommitInfo);` — Handles committing the input text box's content.
- L69 _private prototype_ `void HandleInputTextShowingHistory(TArray<FString>& OutHistory);` — Handles showing a history in the input text box.
- L72 _private prototype_ `void HandleInputTextShowingSuggestions(const FString& Text, TArray<FString>& OutSuggestions);` — Handles showing suggestions in the input text box.
- L75 _private prototype_ `FReply HandlePromoteToShortcutButtonClicked();` — Handles clicking the promote to shortcut button.
- L78 _private prototype_ `FReply HandleSendButtonClicked();` — Handles clicking the send button.
- L83 _private member_ `TArray<FString> CommandHistory;` — Holds the command history.
- L86 _private member_ `TSharedPtr<SSuggestionTextBox> InputTextBox;` — Holds the input text box.
- L89 _private member_ `TSharedPtr<SButton> SendButton;` — Holds the send button.
- L92 _private member_ `TSharedPtr<SButton> PromoteToShortcutButton;` — Holds the promote to shortcut button.
- L97 _private member_ `FOnSessionConsoleCommandSubmitted OnCommandSubmitted;` — Holds a delegate that is executed when a command is submitted.
- L100 _private member_ `FOnSessionConsoleCommandSubmitted OnPromoteToShortcutClicked;` — Holds a delegate that is executed when the Promote To Shortcut button is clicked.

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSessionConsoleCommandSubmitted, const FString& ) class SSessionConsoleCommandBar : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SSessionConsoleCommandBar) { } SLATE_EVENT(FOnSessionConsoleCommandSubmitted, OnCommandSubmitted) SLATE_EVENT(FOnSessionConsoleCommandSubmitted, OnPromoteToShortcutClicked) SLATE_END_ARGS() public: void Construct(const FArguments& InArgs); void SetNumSelectedInstances(int Count); protected: /**` — Delegate type for submitting console commands.

### `Source/Developer/SessionFrontend/Private/Widgets/Console/SSessionConsoleFilterBar.h` (Private)


#### class `SSessionConsoleFilterBar`  
`class SSessionConsoleFilterBar : public SCompoundWidget`  
_L20-141_
- inherits: `SCompoundWidget`
- desc: Implements the console filter bar widget.
- L25 _public function_ `SLATE_BEGIN_ARGS(SSessionConsoleFilterBar)`
- L39 _public prototype_ `void Construct(const FArguments& InArgs);` — Construct this widget @param InArgs The declaration data for this widget.
- L47 _public prototype_ `bool FilterLogMessage(const TSharedRef<FSessionLogMessage>& LogMessage);` — Filters the specified log message based on the current filter settings. @param LogMessage The log message to filter. @return true if the log message passed the filter, false otherwise.
- L54 _public prototype_ `FText GetFilterText() const;` — Gets the current filter string. @return Filter string.
- L57 _public prototype_ `void ResetFilter();` — Resets the categories and filter counters.
- L67 _protected prototype_ `void AddCategoryFilter(const FName& Category);` — Adds a category filter. @param Category The filter's category. @see AddVerbosityFilter
- L77 _protected prototype_ `void AddVerbosityFilter(ELogVerbosity::Type Verbosity, const FString& Name, const FName& Icon);` — Adds a verbosity filter. @param Verbosity The filters verbosity level. @param Name The name of the filter. @param Icon The name of the filter's icon. @see AddVerbosityFilter
- L82 _private prototype_ `TSharedRef<ITableRow> HandleCategoryFilterGenerateRow(FSessionConsoleCategoryFilterPtr Filter, const TSharedRef<STableViewBase>& OwnerTable);` — Callback for generating a row widget for the category filter list.
- L85 _private prototype_ `FText HandleCategoryFilterGetRowText(FSessionConsoleCategoryFilterPtr Filter) const;` — Callback for getting the text for a row in the category filter drop-down.
- L88 _private prototype_ `void HandleCategoryFilterStateChanged(const FName& ChangedCategory, bool Enabled);` — Callback for changing the enabled state of a category filter.
- L91 _private prototype_ `void HandleFilterStringTextChanged(const FText& NewText);` — Callback for changing the filter string text box text.
- L94 _private prototype_ `void HandleHighlightOnlyCheckBoxCheckStateChanged(ECheckBoxState CheckedState);` — Callback for changing the checked state of the 'Filter' check box.
- L97 _private prototype_ `TSharedRef<ITableRow> HandleVerbosityFilterGenerateRow(FSessionConsoleVerbosityFilterPtr Filter, const TSharedRef<STableViewBase>& OwnerTable);` — Callback for generating a row widget for the verbosity filter list.
- L100 _private prototype_ `FText HandleVerbosityFilterGetRowText(FSessionConsoleVerbosityFilterPtr Filter) const;` — Callback for getting the text for a row in the verbosity filter drop-down.
- L103 _private prototype_ `void HandleVerbosityFilterStateChanged(ELogVerbosity::Type Verbosity, bool Enabled);` — Callback for changing the check state of a filter button.
- L108 _private member_ `TArray<FSessionConsoleCategoryFilterPtr> CategoriesList;` — Holds the list of category filters.
- L111 _private member_ `TSharedPtr<SListView<FSessionConsoleCategoryFilterPtr>> CategoriesListView;` — Holds the category filters list view.
- L114 _private member_ `TMap<FName, int32> CategoryCounters;` — Holds the log message counters for category filters.
- L117 _private member_ `TArray<FName> DisabledCategories;` — Holds the list of disabled log categories.
- L120 _private member_ `TArray<ELogVerbosity::Type> DisabledVerbosities;` — Holds the list of disabled log verbosities.
- L123 _private member_ `TSharedPtr<SCheckBox> HighlightOnlyCheckBox;` — Holds the filter check box.
- L126 _private member_ `TSharedPtr<SSearchBox> FilterStringTextBox;` — Holds the filter string text box.
- L129 _private member_ `TArray<FSessionConsoleVerbosityFilterPtr> VerbositiesList;` — Holds the verbosity filters.
- L132 _private member_ `TSharedPtr< SListView<FSessionConsoleVerbosityFilterPtr>> VerbositiesListView;` — Holds the verbosity filters list view.
- L135 _private member_ `TMap<ELogVerbosity::Type, int32> VerbosityCounters;` — Holds the log message counters for verbosity filters.
- L140 _private member_ `FSimpleDelegate OnFilterChanged;` — Holds a delegate that is executed when the filter settings changed.

### `Source/Developer/SessionFrontend/Private/Widgets/Console/SSessionConsoleLogTableRow.h` (Private)


#### class `SSessionConsoleLogTableRow`  
`class SSessionConsoleLogTableRow : public SMultiColumnTableRow<TSharedPtr<FSessionLogMessage>>`  
_L28-171_
- inherits: `SMultiColumnTableRow<TSharedPtr<FSessionLogMessage>>`
- desc: Implements a row widget for the session console log.
- L33 _public function_ `SLATE_BEGIN_ARGS(SSessionConsoleLogTableRow)`
- L45 _public function_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView)` — Constructs the widget. @param InArgs The construction arguments.
- L58 _public function_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override`
- L141 _private function_ `FSlateColor HandleGetBorderColor() const` — Gets the border color for this row.
- L147 _private function_ `FSlateColor HandleGetTextColor() const` — Gets the text color for this log entry.
- L167 _private member_ `TAttribute<FText> HighlightText;` — Holds the highlight string for the log message.
- L170 _private member_ `TSharedPtr<FSessionLogMessage> LogMessage;` — Holds a reference to the log message that is displayed in this row.

### `Source/Developer/SessionFrontend/Private/Widgets/Console/SSessionConsoleShortcutWindow.h` (Private)


#### struct `FConsoleShortcutData`  
`struct FConsoleShortcutData`  
_L14-21_
- L17 _public member_ `FString Name;` — Name of the shortcut
- L20 _public member_ `FString Command;` — Command line for the shortcut

#### class `SSessionConsoleShortcutWindow`  
`class SSessionConsoleShortcutWindow : public SCompoundWidget`  
_L27-126_
- inherits: `SCompoundWidget`
- desc: Implements the console filter bar widget.
- L32 _public function_ `SLATE_BEGIN_ARGS(SSessionConsoleShortcutWindow)`
- L47 _public prototype_ `void AddShortcut(const FString& InName, const FString& InCommandString);` — Adds a new shortcut to the list of commands and saves the list. @param InName The name of the shortcut to add. @param InCommandString The command associated with the shortcut.
- L54 _public prototype_ `void Construct(const FArguments& InArgs);` — Constructs this widget. @param InArgs The construction arguments.
- L64 _protected prototype_ `void AddShortcutInternal(const FString& InName, const FString& InCommandString);` — Adds a new shortcut to the list of commands. @param InName The name of the shortcut. @param InCommandString The command string.
- L71 _protected prototype_ `FString GetShortcutFilename() const;` — Gets the name of the file that stores the shortcuts. @return The file name.
- L78 _protected prototype_ `void LoadShortcuts();` — Loads commands from save file. @see SaveShortcuts
- L81 _protected prototype_ `void RebuildUI();` — Rebuild UI or hide of there are no entries.
- L88 _protected prototype_ `void SaveShortcuts() const;` — Saves commands to save file. @see LoadShortcuts
- L93 _private prototype_ `void HandleDeleteCommandActionExecute(TSharedPtr<FConsoleShortcutData> InShortcut);` — Callback for when a shortcut should be removed.
- L96 _private prototype_ `FReply HandleExecuteButtonClicked(TSharedPtr<FConsoleShortcutData> InShortcut);` — Callback for when a shortcut is executed.
- L99 _private prototype_ `void HandleEditCommandActionExecute(TSharedPtr<FConsoleShortcutData> InShortcut, bool bInEditCommand, FText InPromptTitle);` — Callback for when a shortcut name or command is being edited.
- L102 _private prototype_ `TSharedRef<ITableRow> HandleShortcutListViewGenerateRow(TSharedPtr<FConsoleShortcutData> InItem, const TSharedRef<STableViewBase>& OwnerTable);` — Generates a row widget for a shortcut.
- L105 _private prototype_ `void HandleShortcutTextEntryCommitted(const FText& CommandText, ETextCommit::Type CommitInfo);` — Callback for committing changes to command.
- L110 _private member_ `bool bEditCommand;` — Whether to edit the name or command.
- L113 _private member_ `TSharedPtr<FConsoleShortcutData> EditedShortcut;` — Reference to owner of the current pop-up.
- L116 _private member_ `TWeakPtr<class IMenu> NameEntryMenu;` — Reference to owner of the current pop-up.
- L119 _private member_ `FOnSessionConsoleCommandSubmitted OnCommandSubmitted;` — Holds a delegate that is executed when a command is submitted.
- L122 _private member_ `TArray<TSharedPtr<FConsoleShortcutData>> Shortcuts;` — List of all commands that are currently supported by shortcuts.
- L125 _private member_ `TSharedPtr<SListView<TSharedPtr<FConsoleShortcutData>>> ShortcutListView;` — The list view for showing all commands.

### `Source/Developer/SessionFrontend/Private/Widgets/Console/SSessionConsoleToolbar.h` (Private)


#### class `SSessionConsoleToolbar`  
`class SSessionConsoleToolbar : public SCompoundWidget`  
_L15-32_
- inherits: `SCompoundWidget`
- desc: Implements the device toolbar widget.
- L20 _public function_ `SLATE_BEGIN_ARGS(SSessionConsoleToolbar)`
- L31 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef<FUICommandList>& CommandList );` — Constructs the widget. @param InArgs The construction arguments. @param CommandList The command list to use.

#### Free symbols / members of external scopes

- L10 _macro_ `#define LOCTEXT_NAMESPACE "SSessionConsoleToolbar"`

### `Source/Developer/SessionFrontend/Private/Widgets/SSessionFrontend.h` (Private)


#### class `SSessionFrontend`  
`class SSessionFrontend : public SCompoundWidget`  
_L22-86_
- inherits: `SCompoundWidget`
- desc: Implements the launcher application
- L27 _public function_ `SLATE_BEGIN_ARGS(SSessionFrontend)`
- L39 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef<SDockTab>& ConstructUnderMajorTab, const TSharedPtr<SWindow>& ConstructUnderWindow );` — Constructs the application. @param InArgs The Slate argument list. @param ConstructUnderMajorTab The major tab which will contain the session front-end. @param ConstructUnderWindow The window in which this widget is being constructed.
- L41 _public function_ `TSharedPtr<FTabManager> GetTabManager() const`
- L51 _protected prototype_ `static void FillWindowMenu( FMenuBuilder& MenuBuilder, const TSharedPtr<FTabManager> TabManager );` — Fills the Window menu with menu items. @param MenuBuilder The multi-box builder that should be filled with content for this pull-down menu. @param TabManager A Tab Manager from which to populate tab spawner menu items.
- L54 _protected prototype_ `void InitializeControllers();` — Creates and initializes the controller classes.
- L59 _private prototype_ `void HandleAutomationModuleShutdown();` — Callback for handling automation module shutdowns.
- L62 _private prototype_ `TSharedRef<SDockTab> HandleTabManagerSpawnTab( const FSpawnTabArgs& Args, FName TabIdentifier ) const;` — Callback for spawning tabs.
- L67 _private member_ `TSharedPtr<ITargetDeviceProxyManager> DeviceProxyManager;` — Holds the target device proxy manager.
- L70 _private member_ `bool LauncherOverlayVisible;` — Holds a flag indicating whether the launcher overlay is visible.
- L73 _private member_ `TSharedPtr<SButton> NewSessionButton;` — Holds the 'new session' button.
- L76 _private member_ `TSharedPtr<ISessionManager> SessionManager;` — Holds a pointer to the session manager.
- L79 _private member_ `IScreenShotManagerPtr ScreenShotManager;` — Holds a pointer to the session manager.
- L82 _private member_ `TSharedPtr<FTabManager> TabManager;` — Holds the tab manager that manages the front-end's tabs.
- L85 _private member_ `TSharedPtr<class ITraceController> TraceController;` — Trace controller

### `Source/Developer/SessionFrontend/Public/ISessionFrontendModule.h` (Public)


#### class `ISessionFrontendModule`  
`class ISessionFrontendModule : public IModuleInterface`  
_L14-43_
- inherits: `IModuleInterface`
- desc: Interface for launcher UI modules.
- L25 _public prototype_ `virtual TSharedRef<SWidget> CreateSessionBrowser( const TSharedRef<ISessionManager>& SessionManager ) = 0;` — Creates a session browser widget. @param SessionManager The session manager to use. @return The new session browser widget.
- L32 _public prototype_ `virtual TSharedRef<SWidget> CreateSessionConsole( const TSharedRef<ISessionManager>& SessionManager ) = 0;` — Creates a session console widget. @param SessionManager The session manager to use.
- L37 _public prototype_ `virtual void InvokeSessionFrontend(FName SubTabToActivate = NAME_None) = 0;` — Show the session frontend tab.
- L42 _public prototype_ `virtual ~ISessionFrontendModule() = default;` — Virtual destructor.

### `Source/Developer/SessionFrontend/Public/Widgets/Browser/SSessionBrowser.h` (Public)


#### class `SSessionBrowser`  
`class SSessionBrowser : public SCompoundWidget`  
_L26-147_
- inherits: `SCompoundWidget`
- desc: Implements a Slate widget for browsing active game sessions.
- L31 _public function_ `SLATE_BEGIN_ARGS(SSessionBrowser)`
- L37 _public prototype_ `~SSessionBrowser();` — Destructor.
- L47 _public prototype_ `void Construct( const FArguments& InArgs, TSharedRef<ISessionManager> InSessionManager );` — Construct this widget. @param InArgs The declaration data for this widget. @param InSessionManager The session manager to use.
- L56 _protected prototype_ `void ExpandItem(const TSharedPtr<FSessionBrowserTreeItem>& Item);` — Fully expands the specified tree view item. @param Item The tree view item to expand.
- L59 _protected prototype_ `void FilterSessions();` — Filters the session tree.
- L62 _protected prototype_ `void AddInstanceItemToTree(TSharedPtr<FSessionBrowserTreeItem>& SessionItem, const TSharedPtr<FSessionBrowserTreeItem>& InstanceItem, const TSharedPtr<ISessionInstanceInfo>& InstanceInfo);` — Adds items for this session in the tree.
- L65 _protected prototype_ `void ReloadSessions();` — Reloads the sessions list.
- L70 _private prototype_ `void HandleSessionManagerInstanceSelectionChanged(const TSharedPtr<ISessionInstanceInfo>& Instance, bool Selected);` — Callback for changing the selection state of an instance.
- L73 _private prototype_ `void HandleSessionManagerSelectedSessionChanged(const TSharedPtr<ISessionInfo>& SelectedSession);` — Callback for changing the selected session in the session manager.
- L76 _private prototype_ `void HandleSessionManagerSessionsUpdated();` — Callback for updating the session list in the session manager.
- L79 _private prototype_ `void HandleSessionManagerInstanceDiscovered(const TSharedRef<ISessionInfo>& OwnerSession, const TSharedRef<ISessionInstanceInfo>& DiscoveredInstance);` — Callback from the session manager to notify there's a new session instance.
- L82 _private prototype_ `FText HandleSessionTreeRowGetToolTipText(TSharedPtr<FSessionBrowserTreeItem> Item) const;` — Callback for getting the tool tip text of a session tree row.
- L85 _private prototype_ `void HandleSessionTreeViewExpansionChanged(TSharedPtr<FSessionBrowserTreeItem> TreeItem, bool bIsExpanded);` — Callback for session tree view selection changes.
- L88 _private prototype_ `TSharedRef<ITableRow> HandleSessionTreeViewGenerateRow(TSharedPtr<FSessionBrowserTreeItem> Item, const TSharedRef<STableViewBase>& OwnerTable);` — Callback for generating a row widget in the session tree view.
- L91 _private prototype_ `void HandleSessionTreeViewGetChildren(TSharedPtr<FSessionBrowserTreeItem> Item, TArray<TSharedPtr<FSessionBrowserTreeItem>>& OutChildren);` — Callback for getting the children of a node in the session tree view.
- L94 _private prototype_ `void HandleSessionTreeViewSelectionChanged(const TSharedPtr<FSessionBrowserTreeItem> Item, ESelectInfo::Type SelectInfo);` — Callback for session tree view selection changes.
- L97 _private prototype_ `FReply HandleTerminateSessionButtonClicked();` — Callback for clicking the 'Terminate Session' button.
- L100 _private prototype_ `bool HandleTerminateSessionButtonIsEnabled() const;` — Callback for getting the enabled state of the 'Terminate Session' button.
- L105 _private member_ `TArray<TSharedPtr<ISessionInfo>> AvailableSessions;` — Holds an unfiltered list of available sessions.
- L108 _private member_ `TSharedPtr<SSessionBrowserCommandBar> CommandBar;` — Holds the command bar.
- L111 _private member_ `bool IgnoreSessionManagerEvents;` — Whether to ignore events from the session manager.
- L114 _private member_ `bool updatingTreeExpansion;` — Whether to ignore events from the session tree view.
- L117 _private member_ `TMap<FGuid, TSharedPtr<FSessionBrowserTreeItem>> ItemMap;` — Maps session and instance GUIDs to existing tree items.
- L120 _private member_ `TSharedPtr<ISessionManager> SessionManager;` — Holds a reference to the session manager.
- L123 _private member_ `TArray<TSharedPtr<FSessionBrowserTreeItem>> SessionTreeItems;` — Holds the filtered list of tree items.
- L126 _private member_ `TSharedPtr<STreeView<TSharedPtr<FSessionBrowserTreeItem>>> SessionTreeView;` — Holds the session tree view.
- L131 _private member_ `TSharedPtr<FSessionBrowserGroupTreeItem> AppGroupItem;` — The session tree item that holds this application's session.
- L134 _private member_ `TSharedPtr<FSessionBrowserGroupTreeItem> OtherGroupItem;` — The session tree item that holds other user's sessions.
- L137 _private member_ `TSharedPtr<FSessionBrowserGroupTreeItem> OwnerGroupItem;` — The session tree item that holds the owner's remote sessions.
- L140 _private member_ `TSharedPtr<FSessionBrowserGroupTreeItem> StandaloneGroupItem;` — The session tree item that holds other user's standalone instances.
- L143 _private member_ `TWeakPtr<FSessionBrowserTreeItem> ThisAppInstance;` — This app's instance session
- L146 _private member_ `bool bCanSetDefaultSelection;` — True if we should set the default selection the next time the tree view if refreshed.

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API SESSIONFRONTEND_API`
