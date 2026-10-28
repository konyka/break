# Developer / MessageLog

- module root: `Source/Developer/MessageLog`
- headers: 12; symbols: 337
- symbol kinds: class=11, delegate=15, function=46, macro=5, member=68, prototype=186, struct=3, typedef=3
- PrivateDependencyModuleNames: ApplicationCore, Core, CoreUObject, InputCore, Slate, SlateCore
- PrivateIncludePathModuleNames: Documentation, MainFrame, WorkspaceMenuStructure

### `Source/Developer/MessageLog/Private/MessageFilter.h` (Private)


#### class `FMessageFilter`  
`class FMessageFilter : public TSharedFromThis<FMessageFilter>`  
_L14-55_
- inherits: `TSharedFromThis<FMessageFilter>`
- desc: Represents a message log attribute that can be filtered. Handles all callbacks for any slate checkboxes which wish to alter such filters.
- L17 _public function_ `FMessageFilter(const FText& InName, const FSlateIcon& InIcon) : Name(InName) , Icon(InIcon) , Display(true)`
- L23 _public prototype_ `virtual ~FMessageFilter() = default;`
- L26 _public prototype_ `FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);` — Fires a callback when the mouse is released on an option (not linked to states)
- L29 _public prototype_ `virtual ECheckBoxState OnGetDisplayCheckState() const;` — Gets the display state to send to a display filter check box
- L32 _public prototype_ `virtual void OnDisplayCheckStateChanged(ECheckBoxState InNewState);` — Sets the display state from a display filter check box
- L39 _public function_ `virtual FSimpleMulticastDelegate& OnFilterChanged( )` — Returns a delegate to be invoked when the filter state changes. @return The delegate.
- L45 _public function_ `const FText& GetName() const`
- L46 _public function_ `const FSlateIcon& GetIcon() const`
- L47 _public function_ `const bool GetDisplay() const`
- L50 _private member_ `FText Name;`
- L51 _private member_ `FSlateIcon Icon;`
- L52 _private member_ `bool Display;`
- L54 _private member_ `FSimpleMulticastDelegate RefreshCallback;`

### `Source/Developer/MessageLog/Private/Model/MessageLogModel.h` (Private)


#### class `FMessageLogModel`  
`class FMessageLogModel`  
_L11-50_
- desc: Holds a series of message log listings that can be written to.
- L16 _public prototype_ `virtual ~FMessageLogModel();` — Destructor
- L19 _public prototype_ `bool UnregisterLogListingModel( const FName& LogName );` — Unregisters a log listing with the message log system, true if successful
- L22 _public prototype_ `bool IsRegisteredLogListingModel( const FName& LogName ) const;` — Checks to see if a log listing is already registered with the system
- L25 _public prototype_ `TSharedRef< class FMessageLogListingModel > GetLogListingModel( const FName& LogName );` — Gets a log listing, if it does not exist it is created.
- L28 _public function_ `DECLARE_EVENT( FMessageLogModel, FChangedEvent ) FChangedEvent& OnChanged()` — Broadcasts whenever a message log listing is added or removed
- L33 _protected function_ `virtual void Notify()` — Will broadcast to all registered observers informing them of a change
- L38 _private prototype_ `TSharedRef< class FMessageLogListingModel > RegisterOrGetLogListingModel( const FName& LogName );` — Registers a log listing with the message log system, true if successful
- L41 _private prototype_ `TSharedPtr< class FMessageLogListingModel > FindLogListingModel( const FName& LogName ) const;` — Finds the LogListing Model, given its name.  Returns null if not found.
- L46 _private member_ `TMap< FName, TSharedPtr< class FMessageLogListingModel > > NameToModelMap;` — A map from a log listings' Name->Model
- L49 _private member_ `FChangedEvent ChangedEvent;` — The event that broadcasts whenever data is changed

#### Free symbols / members of external scopes

- L28 _delegate_ `DECLARE_EVENT( FMessageLogModel, FChangedEvent ) FChangedEvent& OnChanged() { return ChangedEvent; } protected: virtual void Notify() { ChangedEvent.Broadcast(); } private: TSharedRef< class FMessageLogListingModel > RegisterOrGetLogListingModel( const FName& LogName );` — Broadcasts whenever a message log listing is added or removed

### `Source/Developer/MessageLog/Private/Presentation/MessageLogViewModel.h` (Private)


#### class `FMessageLogViewModel`  
`class FMessageLogViewModel : public TSharedFromThis< FMessageLogViewModel >`  
_L10-110_
- inherits: `TSharedFromThis<FMessageLogViewModel>`
- desc: Presentation logic for the message log
- L16 _public function_ `DECLARE_EVENT( FMessageLogViewModel, FChangedEvent ) FChangedEvent& OnChanged()` — Broadcasts whenever we are informed of a change in the MessageLogModel
- L20 _public function_ `DECLARE_EVENT( FMessageLogViewModel, FOnSelectionChangedEvent ) FOnSelectionChangedEvent& OnSelectionChanged()` — Broadcasts whenever selection state changes
- L26 _public prototype_ `FMessageLogViewModel( const TSharedPtr< class FMessageLogModel >& InMessageLogModel );` — Constructor
- L29 _public prototype_ `virtual ~FMessageLogViewModel();` — Destructor
- L32 _public prototype_ `virtual void Initialize();` — Initializes the FMessageLogViewModel for use
- L35 _public prototype_ `virtual void Update();` — Called when data is changed changed/updated in the model
- L46 _public prototype_ `TSharedRef<class FMessageLogListingViewModel> RegisterLogListingViewModel( const FName& LogName, const FText& LogLabel, const struct FMessageLogInitializationOptions& InitializationOptions );` — Registers a log listing view model. It is not necessary to call this function before outputting to a log via AddMessage etc. This call simply registers a UI to view the log data. @param	LogName					The name of the log to register @param	LogLabel				The label to display for the log @param	InitializationOptions	Initialization options for this message log
- L54 _public prototype_ `bool UnregisterLogListingViewModel( const FName& LogName );` — Unregisters a log listing view model. @param	LogName		The name of the log to unregister. @returns true if successful.
- L62 _public prototype_ `bool IsRegisteredLogListingViewModel( const FName& LogName ) const;` — Checks to see if a log listing view model is already registered @param	LogName		The name of the log to check. @returns true if the log listing is already registered.
- L65 _public prototype_ `TSharedPtr< class FMessageLogListingViewModel > FindLogListingViewModel( const FName& LogName ) const;` — Finds the LogListing ViewModel, given its name. Returns null if not found.
- L68 _public prototype_ `TSharedRef< class FMessageLogListingViewModel > GetLogListingViewModel( const FName& LogName );` — Gets a log listing ViewModel, if it does not exist it is created.
- L71 _public prototype_ `void ChangeCurrentListingViewModel( const FName& LogName );` — Changes the currently selected log listing
- L74 _public prototype_ `TSharedPtr<class FMessageLogListingViewModel> GetCurrentListingViewModel() const;` — Gets the currently selected log listing
- L77 _public prototype_ `FName GetCurrentListingName() const;` — Gets the currently selected log listing's name
- L80 _public prototype_ `FString GetCurrentListingLabel() const;` — Gets the currently selected log listing's label
- L83 _public function_ `const TArray<IMessageLogListingPtr>& GetLogListingViewModels() const` — Get the linearized array of ViewModels
- L88 _private prototype_ `void UpdateListingViewModelArray();` — Updates the linearized array of ViewModels
- L93 _private member_ `TSharedPtr< class FMessageLogModel > MessageLogModel;` — The model we are getting display info from
- L96 _private member_ `TMap< FName, TSharedPtr< class FMessageLogListingViewModel > > NameToViewModelMap;` — A map from a log listings' Name->ViewModel
- L99 _private member_ `TArray<IMessageLogListingPtr> ViewModelArray;` — A linearized array of the ViewModels - we need this for the data to display in a SComboBox
- L102 _private member_ `TSharedPtr< class FMessageLogListingViewModel > SelectedLogListingViewModel;` — The currently selected log listing
- L105 _private member_ `FChangedEvent ChangedEvent;` — The event that broadcasts whenever a change occurs to the data
- L108 _private member_ `FOnSelectionChangedEvent SelectionChangedEvent;` — The event that broadcasts whenever selection state is changed

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_EVENT( FMessageLogViewModel, FChangedEvent ) FChangedEvent& OnChanged() { return ChangedEvent; } DECLARE_EVENT( FMessageLogViewModel, FOnSelectionChangedEvent ) FOnSelectionChangedEvent& OnSelectionChanged() { return SelectionChangedEvent; } public: FMessageLogViewModel( const TSharedPtr< class FMessageLogModel >& InMessageLogModel );` — Broadcasts whenever we are informed of a change in the MessageLogModel
- L20 _delegate_ `DECLARE_EVENT( FMessageLogViewModel, FOnSelectionChangedEvent ) FOnSelectionChangedEvent& OnSelectionChanged() { return SelectionChangedEvent; } public: FMessageLogViewModel( const TSharedPtr< class FMessageLogModel >& InMessageLogModel );` — Broadcasts whenever selection state changes

### `Source/Developer/MessageLog/Private/UserInterface/SMessageLog.h` (Private)


#### class `SMessageLog`  
`class SMessageLog : public SCompoundWidget`  
_L21-75_
- inherits: `SCompoundWidget`
- desc: An implementation for the message log widget. It holds a series of message log listings which it can switch between.
- L26 _public function_ `SLATE_BEGIN_ARGS(SMessageLog)`
- L27 _public prototype_ `SLATE_END_ARGS() static FName AppName;`
- L32 _public prototype_ `~SMessageLog();` — Destructor.
- L40 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef<class FMessageLogViewModel>& InViewModel );` — Constructs the widget. @param InArgs The construction arguments. @param InModel The view model to use.
- L46 _public prototype_ `FReply OnKeyDown( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override;`
- L51 _private prototype_ `TSharedRef<ITableRow> HandleCategoriesListGenerateRow( IMessageLogListingPtr Item, const TSharedRef<STableViewBase>& OwnerTable );` — Callback for generating a row in the categories list.
- L54 _private prototype_ `void HandleCategoriesListSelectionChanged( IMessageLogListingPtr Selection, ESelectInfo::Type SelectInfo );` — Callback for changing the selected item in the categories list.
- L57 _private prototype_ `void HandleSelectionUpdated();` — Handles the broadcast message sent when the current log listing selection is changed
- L60 _private prototype_ `void RefreshCategoryList();` — Handles the broadcast message sent when the current log listing is updated
- L65 _private member_ `TSharedPtr<SListView<IMessageLogListingPtr>> CategoriesListView;` — Holds the log categories list view widget.
- L68 _private member_ `TSharedPtr<SBorder> CurrentListingDisplay;` — The widget for displaying the current listing.
- L71 _private member_ `TSharedPtr<class SMessageLogListing> LogListing;` — The current log listing widget, if any.
- L74 _private member_ `TSharedPtr<class FMessageLogViewModel> ViewModel;` — The message log view model

### `Source/Developer/MessageLog/Private/UserInterface/SMessageLogCategoryListRow.h` (Private)


#### class `SMessageLogCategoryListRow`  
`class SMessageLogCategoryListRow : public SMultiColumnTableRow<IMessageLogListingPtr>`  
_L24-103_
- inherits: `SMultiColumnTableRow<IMessageLogListingPtr>`
- desc: Implements a row widget for the log categories list view.
- L29 _public function_ `SLATE_BEGIN_ARGS(SMessageLogCategoryListRow)`
- L39 _public function_ `void Construct( const FArguments& InArgs, const IMessageLogListingRef& InLogListing, const TSharedRef<STableViewBase>& InOwnerTableView )` — Constructs the widget. @param InArgs The arguments.
- L55 _public function_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn( const FName& ColumnName ) override`
- L76 _private function_ `FText HandleNameColumnText( ) const` — Callback for getting the text in the 'Entries' column.
- L89 _private function_ `FSlateColor HandleTextColorAndOpacity( ) const` — Callback for getting the text color.
- L102 _private member_ `IMessageLogListingPtr LogListing;` — Holds the log listing used to populate this row.

#### Free symbols / members of external scopes

- L19 _macro_ `#define LOCTEXT_NAMESPACE "SMessageLogCategoryListRow"`

### `Source/Developer/MessageLog/Private/UserInterface/SMessageLogMessageListRow.h` (Private)


#### class `SMessageLogMessageListRow`  
`class SMessageLogMessageListRow : public STableRow<TSharedPtr<FTokenizedMessage>>`  
_L24-127_
- inherits: `STableRow<TSharedPtr<FTokenizedMessage>>`
- L29 _public prototype_ `DECLARE_DELEGATE_TwoParams( FOnTokenClicked, TSharedPtr<FTokenizedMessage>, const TSharedRef<class IMessageToken>& );`
- L30 _public prototype_ `DECLARE_DELEGATE_OneParam( FOnMessageClicked, TSharedPtr<FTokenizedMessage> );`
- L34 _public function_ `SLATE_BEGIN_ARGS(SMessageLogMessageListRow) : _Message() , _OnTokenClicked() , _OnMessageDoubleClicked()`
- L39 _public prototype_ `SLATE_ATTRIBUTE(TSharedPtr<FTokenizedMessage>, Message) SLATE_EVENT(FOnTokenClicked, OnTokenClicked) SLATE_EVENT(FOnMessageClicked, OnMessageDoubleClicked) SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TSharedRef< STableViewBase >& InOwnerTableView );`
- L54 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidget();` — @return Widget for this log listing item
- L56 _public function_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override`
- L70 _protected prototype_ `TSharedRef<SWidget> CreateHyperlink( const TSharedRef<IMessageToken>& InMessageToken, const FText& InToolTip = FText() );`
- L72 _protected prototype_ `void CreateMessage( const TSharedRef<SHorizontalBox>& InHorzBox, const TSharedRef<IMessageToken>& InMessageToken, float Padding );`
- L76 _private function_ `EVisibility GetActionLinkVisibility(TSharedRef<FActionToken> ActionToken) const`
- L81 _private function_ `bool GetActionLinkEnable(TSharedRef<FActionToken> ActionToken) const`
- L86 _private function_ `void HandleActionHyperlinkNavigate( TSharedRef<FActionToken> ActionToken )`
- L91 _private function_ `void HandleHyperlinkNavigate( TSharedRef<IMessageToken> InMessageToken )`
- L97 _private function_ `FReply HandleTokenButtonClicked( TSharedRef<IMessageToken> InMessageToken )`
- L105 _private function_ `void HandleDocsHyperlinkNavigate( FString DocumentationLink )`
- L110 _private function_ `void HandleTutorialHyperlinkNavigate( FString TutorialAssetName )`
- L120 _protected member_ `TSharedPtr<FTokenizedMessage> Message;` — The message used to create this widget.
- L123 _protected member_ `FOnTokenClicked OnTokenClicked;` — Delegate to execute when the token is clicked.
- L126 _protected member_ `FOnMessageClicked OnMessageDoubleClicked;` — Delegate to execute when the message is double-clicked.

#### Free symbols / members of external scopes

- L22 _macro_ `#define LOCTEXT_NAMESPACE "SMessageLogMessageListRow"`
- L29 _delegate_ `DECLARE_DELEGATE_TwoParams( FOnTokenClicked, TSharedPtr<FTokenizedMessage>, const TSharedRef<class IMessageToken>& );`
- L30 _delegate_ `DECLARE_DELEGATE_OneParam( FOnMessageClicked, TSharedPtr<FTokenizedMessage> );`

### `Source/Developer/MessageLog/Public/IMessageLogListing.h` (Public)


#### class `IMessageLogListing`  
`class IMessageLogListing : public IMessageLog`  
_L21-135_
- inherits: `IMessageLog`
- desc: A message log listing, such as the Compiler Log, or the Map Check Log.
- L26 _public prototype_ `virtual void ClearMessages() = 0;` — Clears messages (if paged, in the current page)
- L33 _public prototype_ `virtual const TArray< TSharedRef<class FTokenizedMessage> >& GetSelectedMessages() const = 0;` — Gets a list of the selected messages for the specific log listing @returns an array of selected messages.
- L40 _public prototype_ `virtual void SelectMessages( const TArray< TSharedRef<class FTokenizedMessage> >& InSelectedMessages ) = 0;` — Sets multiple selected messages @param	InSelectedMessages	The messages to select.
- L47 _public prototype_ `virtual const TArray< TSharedRef<class FTokenizedMessage> >& GetFilteredMessages() const = 0;` — Gets a list of the filtered messages for the specific log listing @returns an array of filtered messages.
- L55 _public prototype_ `virtual void SelectMessage(const TSharedRef<class FTokenizedMessage>& Message, bool bSelected) = 0;` — Set the message selection state @param	Message		The message to select/deselect. @param	bSelected	Whether to select or deselect the message.
- L63 _public prototype_ `virtual bool IsMessageSelected(const TSharedRef<class FTokenizedMessage>& Message) const = 0;` — Get the message selection state @param	Message		The message to check. @returns true if the message is selected.
- L66 _public prototype_ `virtual void ClearSelectedMessages() = 0;` — Clears the message selection
- L69 _public prototype_ `virtual void InvertSelectedMessages() = 0;` — Inverts the message selection
- L76 _public prototype_ `virtual FString GetSelectedMessagesAsString() const = 0;` — Gets all the unfiltered selected messages as a single piece of text @returns the selected messages as a string
- L83 _public prototype_ `virtual FString GetAllMessagesAsString() const = 0;` — Gets all the unfiltered messages as a single piece of text @returns all the messages as a string
- L90 _public prototype_ `virtual const FName& GetName() const = 0;` — Gets the message log listing unique name @returns the name of the listing.
- L97 _public prototype_ `virtual void SetLabel( const FText& InLogLabel ) = 0;` — Sets the message log listing label @param	InLogLabel	The label to display for this listing.
- L104 _public prototype_ `virtual const FText& GetLabel() const = 0;` — Gets the message log listing label @returns the label for this listing.
- L111 _public prototype_ `virtual const TArray< TSharedRef< class FMessageFilter> >& GetMessageFilters() const = 0;` — Gets the set of message filters used when displaying messages @returns the array of message filters.
- L118 _public prototype_ `virtual void ExecuteToken( const TSharedRef<class IMessageToken>& Token ) const = 0;` — Performs an operation depending on the token (execute hyperlink etc.) @param	Token	The token to execute.
- L121 _public prototype_ `DECLARE_EVENT_OneParam( IMessageLogListing, IMessageTokenClickedEvent, const TSharedRef<class IMessageToken>& );` — Broadcasts when a token is clicked/executed
- L122 _public prototype_ `virtual IMessageTokenClickedEvent& OnMessageTokenClicked() = 0;`
- L125 _public prototype_ `DECLARE_EVENT( IMessageLogListing, FChangedEvent ) virtual FChangedEvent& OnDataChanged() = 0;` — Broadcasts whenever we are informed of a change in the IMessageLogListing
- L129 _public prototype_ `DECLARE_EVENT( IMessageLogListing, FOnSelectionChangedEvent ) virtual FOnSelectionChangedEvent& OnSelectionChanged() = 0;` — Broadcasts whenever selection state is changed
- L133 _public prototype_ `DECLARE_EVENT( IMessageLogListing, FOnPageSelectionChangedEvent ) virtual FOnPageSelectionChangedEvent& OnPageSelectionChanged() = 0;` — Broadcasts whenever page selection state is changed

#### Free symbols / members of external scopes

- L12 _typedef_ `typedef TSharedPtr<class IMessageLogListing> IMessageLogListingPtr;` — Type definition for shared pointers to instances of IMessageLogListing.
- L15 _typedef_ `typedef TSharedRef<class IMessageLogListing> IMessageLogListingRef;` — Type definition for shared references to instances of IMessageLogListing.
- L121 _delegate_ `DECLARE_EVENT_OneParam( IMessageLogListing, IMessageTokenClickedEvent, const TSharedRef<class IMessageToken>& );` — Broadcasts when a token is clicked/executed
- L125 _delegate_ `DECLARE_EVENT( IMessageLogListing, FChangedEvent ) virtual FChangedEvent& OnDataChanged() = 0;` — Broadcasts whenever we are informed of a change in the IMessageLogListing
- L129 _delegate_ `DECLARE_EVENT( IMessageLogListing, FOnSelectionChangedEvent ) virtual FOnSelectionChangedEvent& OnSelectionChanged() = 0;` — Broadcasts whenever selection state is changed
- L133 _delegate_ `DECLARE_EVENT( IMessageLogListing, FOnPageSelectionChangedEvent ) virtual FOnPageSelectionChangedEvent& OnPageSelectionChanged() = 0;` — Broadcasts whenever page selection state is changed

### `Source/Developer/MessageLog/Public/MessageLogInitializationOptions.h` (Public)


#### struct `FMessageLogInitializationOptions`  
`struct FMessageLogInitializationOptions`  
_L10-49_
- desc: Options for setting up a message log's UI
- L12 _public function_ `FMessageLogInitializationOptions() : bShowFilters(true) , bShowPages(false) , bAllowClear(true) , bDiscardDuplicates(false) , MaxPageCount(20) , bShowInLogWindow(true) , bScrollToBottom(false)`
- L23 _public member_ `bool bShowFilters;` — Whether to show the filters menu
- L29 _public member_ `bool bShowPages;` — Whether to initially  show the pages widget. Setting this to false will allow the user to manually clear the log. If this is not set & NewPage() is called on the log, the pages widget will show itself
- L34 _public member_ `bool bAllowClear;` — Whether to allow the user to clear this log.
- L39 _public member_ `bool bDiscardDuplicates;` — Whether to check for duplicate messages & discard them
- L42 _public member_ `uint32 MaxPageCount;` — The maximum number of pages this log can hold. Pages are managed in a first in, last out manner
- L45 _public member_ `bool bShowInLogWindow;` — Whether to show this log in the main log window
- L48 _public member_ `bool bScrollToBottom;` — Whether to scroll to the bottom of the window when messages are added

### `Source/Developer/MessageLog/Public/MessageLogModule.h` (Public)


#### class `FMessageLogModule`  
`class FMessageLogModule : public IModuleInterface`  
_L14-104_
- inherits: `IModuleInterface`
- L17 _public prototype_ `FMessageLogModule();`
- L20 _public prototype_ `virtual void StartupModule();` — Begin IModuleInterface interface
- L21 _public prototype_ `virtual void ShutdownModule();`
- L33 _public prototype_ `virtual void RegisterLogListing(const FName& LogName, const FText& LogLabel, const FMessageLogInitializationOptions& InitializationOptions = FMessageLogInitializationOptions() );` — Registers a log listing with the message log widget. This log is displayed in the global Message Log window by default, but this can be disabled in InitializationOptions. It is not necessary to call this function before outputting to a log via AddMessage etc. This call simply registers a UI to view the log data. @param	LogName					The name of the log to register @param	LogLabel				The label to display for the log @param	InitializationOptions	Initialization options for this message log
- L41 _public prototype_ `virtual bool UnregisterLogListing(const FName& LogName);` — Unregisters a log listing with the message log widget. @param	LogName		The name of the log to unregister. @returns true if successful.
- L49 _public prototype_ `virtual bool IsRegisteredLogListing(const FName& LogName) const;` — Checks to see if a log listing is already registered with the system @param	LogName		The name of the log to check. @returns true if the log listing is already registered.
- L57 _public prototype_ `virtual TSharedRef<class IMessageLogListing> GetLogListing(const FName& LogName);` — Get a message log listing registered with the message log. If it does not exist it will created. @param	LogName		The name of the log to retrieve @returns the log listing.
- L64 _public prototype_ `virtual void OpenMessageLog(const FName& LogName);` — Opens up the message log to a certain log listing @param	LogName		The name of the log to open
- L73 _public prototype_ `virtual TSharedRef<class IMessageLogListing> CreateLogListing(const FName& InLogName, const FMessageLogInitializationOptions& InitializationOptions = FMessageLogInitializationOptions());` — Creates a new log listing for use outside of the global MessageLog window. @param	LogName					The name of the log to create @param	InitializationOptions	Initialization options for this message log @returns a new log listing.
- L81 _public prototype_ `virtual TSharedRef< class SWidget > CreateLogListingWidget(const TSharedRef<class IMessageLogListing>& InMessageLogListing);` — Creates a log listing widget to view data from the passed-in listing. @param	InMessageLogListing	The log listing created via CreateLogListing(). @returns the log listing widget.
- L86 _public prototype_ `virtual void EnableMessageLogDisplay(bool bInCanDisplayMessageLog);` — Setting this to true will allow the message log to be displayed when OpenMessageLog is called.
- L92 _public prototype_ `virtual void RegisterMessageLogSpawner(const TSharedRef<FWorkspaceItem>& InGroup);` — Registers the Message Log spawner. @param InGroup The Workspace group used to register the MessageLogSpawner.
- L97 _private member_ `TSharedPtr<class FMessageLogViewModel> MessageLogViewModel;` — The one and only message log view model
- L100 _private member_ `bool bCanDisplayMessageLog;` — Delegate used to determine whether the message log can be displayed
- L103 _private member_ `FDelegateHandle ModulesChangedHandle;` — Handle to delegate called when module state changes

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FCanShowMessageLog);`
- L12 _prototype_ `DECLARE_DELEGATE_RetVal(bool, FCanShowMessageLog);`

### `Source/Developer/MessageLog/Public/Model/MessageLogListingModel.h` (Public)


#### class `FMessageLogListingModel`  
`class FMessageLogListingModel : public TSharedFromThis< FMessageLogListingModel >`  
_L15-182_
- inherits: `TSharedFromThis<FMessageLogListingModel>`
- desc: This class represents a set of rich tokenized messages for a particular system
- L36 _public prototype_ `virtual ~FMessageLogListingModel() = default;`
- L43 _public function_ `static TSharedRef< FMessageLogListingModel > Create( const FName& InLogName )` — Factory method which creates a new FMessageLogListingModel object @param	InLogName		The name of the log
- L50 _public function_ `DECLARE_EVENT( FMessageLogListingModel, FChangedEvent ) FChangedEvent& OnChanged()` — Broadcasts whenever the message log listing changes
- L54 _public function_ `const FName& GetName() const` — Retrieves the name identifier for this log listing
- L57 _public prototype_ `const TSharedPtr<FTokenizedMessage> GetMessageAtIndex( const uint32 PageIndex, const int32 MessageIndex ) const;` — Returns the message at the specified index
- L60 _public prototype_ `FString GetAllMessagesAsString(const uint32 PageIndex) const;` — Gets all messages as a string
- L63 _public prototype_ `MessageContainer::TConstIterator GetMessageIterator(uint32 PageIndex) const;` — Obtains a const iterator to the message data structure
- L66 _public prototype_ `int32 ReplaceMessage( const TSharedRef< FTokenizedMessage >& NewMessage, const uint32 PageIndex, const int32 MessageIndex );` — Replaces the message at the given index
- L69 _public prototype_ `void AddMessage( const TSharedRef< FTokenizedMessage >& NewMessage, bool bMirrorToOutputLog = true, bool bDiscardDuplicates = false );` — Appends a message
- L72 _public prototype_ `void AddMessages( const TArray< TSharedRef< FTokenizedMessage > >& NewMessages, bool bMirrorToOutputLog = true, bool bDiscardDuplicates = false );` — Appends multiple messages
- L75 _public prototype_ `void ClearMessages();` — Clears all messages
- L84 _public prototype_ `void NewPage( const FText& InTitle, uint32 InMaxPages );` — Add a new page. Old pages are only kept around if they contain messages, so if the current page is empty, this call does nothing. @param	InTitle		The title that will be displayed for this page. @param	InMaxPages	The maximum number of pages we keep around. If the count is exceeded, we discard the oldest page.
- L93 _public prototype_ `bool SetCurrentPage( const FText& InTitle, uint32 InMaxPages );` — Sets the current page to the one specified by the title. If the page does not exist, creates a new page. @param	InTitle		The title of the page to search for, or create @param	InMaxPages	The maximum number of pages we keep around. If the count is exceeded, we discard the oldest page. @returns true if the page has changed (either switched or created a new one).
- L103 _public prototype_ `bool SetCurrentPage( const uint32 InOldPageIndex );` — Sets the current page to the one specified by the index. If the page does not exist, creates a new page. The page will move to index 0. @param	InTitle		The title of the page to search for, or create @param	InMaxPages	The maximum number of pages we keep around. If the count is exceeded, we discard the oldest page. @returns true if the page has changed (either switched or created a new one).
- L106 _public prototype_ `uint32 NumPages() const;` — Get the number of pages contained in this log
- L109 _public prototype_ `uint32 NumMessages( uint32 PageIndex ) const;` — Get the number of messages on the passed-in page
- L115 _public prototype_ `const FText& GetPageTitle( const uint32 PageIndex ) const;` — Get the title of the page at the specified index @param	PageIndex	The index of the page
- L118 _public prototype_ `static bool AreMessagesEqual(const TSharedRef< FTokenizedMessage >& Message0, const TSharedRef< FTokenizedMessage >& Message1);` — Helper function for RemoveDuplicates(), exposed so the ViewModel can use it too
- L121 _public prototype_ `void RemoveDuplicates(uint32 PageIndex);` — Remove any messages that are duplicates of one another - O(n)
- L126 _protected function_ `virtual void Notify()` — Will broadcast to all registered observers informing them of a change
- L129 _protected prototype_ `FPage& CurrentPage() const;` — Access the current page (we only add messages to this page
- L132 _protected prototype_ `FPage* PageAtIndex(const uint32 PageIndex) const;` — Get a page by index - uses cache to speed up linked list access
- L135 _protected prototype_ `void CreateNewPageIfRequired();` — Create a new page if we have one pending
- L143 _private function_ `FMessageLogListingModel( const FName& InLogName ) : LogName( InLogName ) , bIsPrintingToOutputLog( false )` — FMessageLogListingModel Constructor @param	InLogName		The name of the log
- L156 _private prototype_ `void AddMessageInternal( const TSharedRef<FTokenizedMessage>& NewMessage, bool bMirrorToOutputLog, bool bDiscardDuplicates );` — Helper function for AddMessage and AddMessages
- L160 _private member_ `FText PendingPageName;` — The name of a pending page
- L163 _private member_ `uint32 MaxPages;` — The cap on the number of pages we have
- L166 _private member_ `TDoubleLinkedList<FPage> Pages;` — The list of pages in this log listing
- L169 _private member_ `FName LogName;` — Name of the listing, for identification
- L172 _private member_ `FChangedEvent ChangedEvent;` — Delegate to call when data is changed
- L175 _private member_ `bool bIsPrintingToOutputLog;` — Are we currently processing the output log mirror?  If so, we drop any additional messages we receive, as they are duplicates
- L178 _private member_ `mutable uint32 CachedPageIndex;` — Cached page index
- L181 _private member_ `mutable FPage* CachedPage;` — Cached page

#### struct `FMessageLogListingModel::FPage`  
`struct FPage`  
_L18-32_
- L20 _public function_ `FPage( const FText& InTitle ) : Title( InTitle )`
- L26 _public member_ `FText Title;` — The title of this page
- L29 _public member_ `MessageContainer Messages;` — The list of messages in this log listing
- L31 _public member_ `TSet<uint32> MessagesHashes;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MESSAGELOG_API`
- L12 _typedef_ `typedef TArray< TSharedRef<FTokenizedMessage> > MessageContainer;` — Define the container type for all the messages
- L50 _delegate_ `DECLARE_EVENT( FMessageLogListingModel, FChangedEvent ) FChangedEvent& OnChanged() { return ChangedEvent; } const FName& GetName() const { return LogName; } const TSharedPtr<FTokenizedMessage> GetMessageAtIndex( const uint32 PageIndex, const int32 MessageIndex ) const;` — Broadcasts whenever the message log listing changes

### `Source/Developer/MessageLog/Public/Presentation/MessageLogListingViewModel.h` (Public)


#### class `FMessageLogListingViewModel`  
`class FMessageLogListingViewModel : public TSharedFromThis<FMessageLogListingViewModel> , public IMessageLogListing`  
_L18-273_
- inherits: `TSharedFromThis<FMessageLogListingViewModel>,IMessageLogListing`
- desc: The non-UI solution specific presentation logic for a collection of messages for a particular system.
- L31 _public function_ `static TSharedRef< FMessageLogListingViewModel > Create( const TSharedRef< FMessageLogListingModel >& InMessageLogListingModel, const FText& InLogLabel, const FMessageLogInitializationOptions& InitializationOptions = FMessageLogInitializationOptions() )` — Factory method which creates a new FMessageLogListingViewModel object @param	InMessageLogListingModel		The MessageLogListing data to view @param	InLogLabel						The label that will be displayed in the UI for this log listing @param	InMessageLogListingModel		If true, a filters list will be displayed for this log listing
- L40 _public prototype_ `FMessageLogListingViewModel();`
- L41 _public prototype_ `~FMessageLogListingViewModel();`
- L44 _public prototype_ `virtual void AddMessage( const TSharedRef< class FTokenizedMessage >& NewMessage, bool bMirrorToOutputLog ) override;` — Begin IMessageLogListing interface
- L45 _public prototype_ `virtual void AddMessages( const TArray< TSharedRef< class FTokenizedMessage > >& NewMessages, bool bMirrorToOutputLog ) override;`
- L46 _public prototype_ `virtual void ClearMessages() override;`
- L47 _public prototype_ `virtual const TArray< TSharedRef<class FTokenizedMessage> >& GetSelectedMessages() const override;`
- L48 _public prototype_ `virtual void SelectMessages( const TArray< TSharedRef<class FTokenizedMessage> >& InSelectedMessages ) override;`
- L49 _public prototype_ `virtual const TArray< TSharedRef<class FTokenizedMessage> >& GetFilteredMessages() const override;`
- L50 _public prototype_ `virtual void SelectMessage(const TSharedRef<class FTokenizedMessage>& Message, bool bSelected) override;`
- L51 _public prototype_ `virtual bool IsMessageSelected(const TSharedRef<class FTokenizedMessage>& Message) const override;`
- L52 _public prototype_ `virtual void ClearSelectedMessages() override;`
- L53 _public prototype_ `virtual void InvertSelectedMessages() override;`
- L54 _public prototype_ `virtual FString GetSelectedMessagesAsString() const override;`
- L55 _public prototype_ `virtual FString GetAllMessagesAsString() const override;`
- L56 _public prototype_ `virtual const FName& GetName() const override;`
- L57 _public prototype_ `virtual void SetLabel( const FText& InLogLabel ) override;`
- L58 _public prototype_ `virtual const FText& GetLabel() const override;`
- L59 _public prototype_ `virtual const TArray< TSharedRef<FMessageFilter> >& GetMessageFilters() const override;`
- L60 _public prototype_ `virtual void ExecuteToken( const TSharedRef<class IMessageToken>& Token ) const override;`
- L61 _public prototype_ `virtual void NewPage( const FText& Title ) override;`
- L62 _public prototype_ `virtual void SetCurrentPage( const FText& Title ) override;`
- L63 _public prototype_ `virtual void SetCurrentPage( const uint32 InOldPageIndex ) override;`
- L64 _public prototype_ `virtual void NotifyIfAnyMessages( const FText& Message, EMessageSeverity::Type SeverityFilter = EMessageSeverity::Info, bool bForce = false ) override;`
- L65 _public prototype_ `virtual void Open() override;`
- L66 _public prototype_ `virtual int32 NumMessages( EMessageSeverity::Type SeverityFilter ) override;`
- L68 _public function_ `DECLARE_DERIVED_EVENT(FMessageLogListingViewModel, IMessageLogListing::IMessageTokenClickedEvent, IMessageTokenClickedEvent) virtual IMessageLogListing::IMessageTokenClickedEvent& OnMessageTokenClicked() override`
- L71 _public function_ `DECLARE_DERIVED_EVENT(FMessageLogListingViewModel, IMessageLogListing::FChangedEvent, FChangedEvent) virtual IMessageLogListing::FChangedEvent& OnDataChanged() override`
- L74 _public function_ `DECLARE_DERIVED_EVENT(FMessageLogListingViewModel, IMessageLogListing::FOnSelectionChangedEvent, FOnSelectionChangedEvent) virtual IMessageLogListing::FOnSelectionChangedEvent& OnSelectionChanged() override`
- L77 _public function_ `DECLARE_DERIVED_EVENT(FMessageLogListingViewModel, IMessageLogListing::FOnPageSelectionChangedEvent, FOnPageSelectionChangedEvent ) virtual IMessageLogListing::FOnPageSelectionChangedEvent& OnPageSelectionChanged() override`
- L82 _public prototype_ `virtual void Initialize();` — Initializes the FMessageLogListingViewModel for use
- L85 _public prototype_ `void OnFilterChanged();` — Handles updating the viewmodel when one of its filters changes
- L88 _public prototype_ `virtual void OnChanged();` — Called when data is changed changed/updated in the model
- L91 _public function_ `const TArray< TSharedRef< FTokenizedMessage > >& GetFilteredMessages()` — Returns the filtered message list
- L94 _public prototype_ `MessageContainer::TConstIterator GetFilteredMessageIterator() const;` — Obtains a const iterator to the filtered messages
- L97 _public prototype_ `MessageContainer::TConstIterator GetSelectedMessageIterator() const;` — Obtains a const iterator to the selected filtered messages list
- L100 _public prototype_ `const TSharedPtr<FTokenizedMessage> GetMessageAtIndex( const int32 MessageIndex ) const;` — Returns the message at the specified index in the filtered list
- L103 _public prototype_ `void SetShowFilters(bool bInShowFilters);` — Set whether we should show filters or not
- L106 _public prototype_ `bool GetShowFilters() const;` — Get whether we should show filters or not
- L109 _public prototype_ `void SetShowPages(bool bInShowPages);` — Set whether we should show pages or not
- L112 _public prototype_ `bool GetShowPages() const;` — Get whether we should show pages or not
- L115 _public prototype_ `void SetScrollToBottom(bool bInScrollToBottom);` — Set whether we should scroll to the bottom when messages are added
- L118 _public prototype_ `bool GetScrollToBottom() const;` — Get whether we should scroll to the bottom when messages are added
- L121 _public prototype_ `void SetAllowClear(bool bInAllowClear);` — Set whether we should show allow the user to clear the log.
- L124 _public prototype_ `bool GetAllowClear() const;` — Get whether we should show allow the user to clear the log.
- L127 _public prototype_ `void SetDiscardDuplicates(bool bInDiscardDuplicates);` — Set whether we should discard duplicates or not
- L130 _public prototype_ `bool GetDiscardDuplicates() const;` — Get whether we should discard duplicates or not
- L133 _public prototype_ `void SetMaxPageCount(uint32 InMaxPageCount);` — Set the maximum page count this log can hold
- L136 _public prototype_ `uint32 GetMaxPageCount() const;` — Get the maximum page count this log can hold
- L139 _public prototype_ `uint32 GetPageCount() const;` — Get the number of pages we can view
- L142 _public prototype_ `uint32 GetCurrentPageIndex() const;` — Get the current page index we are viewing
- L145 _public prototype_ `void SetCurrentPageIndex( uint32 InCurrentPageIndex );` — Set the current page index we are viewing
- L148 _public prototype_ `void NextPage();` — Go to the page at the index after the current
- L151 _public prototype_ `void PrevPage();` — Go to the page at the index before the current
- L157 _public prototype_ `const FText& GetPageTitle( const uint32 PageIndex ) const;` — Get the title of the page at the specified index @param	PageIndex	The index of the page
- L160 _public prototype_ `uint32 NumMessages() const;` — Gets the number of messages in the current log page
- L163 _public function_ `bool ShouldShowInLogWindow() const` — Get whether to show this log in the main log window
- L166 _private function_ `FMessageLogListingViewModel( TSharedPtr< FMessageLogListingModel > InMessageLogListingModel, const FText& InLogLabel, const FMessageLogInitializationOptions& InitializationOptions ) : bShowFilters( InitializationOptions.bShowFilters ) , bShowPages( InitializationOptions.bShowPages ) , bAllowClear( InitializationOptions.bAllowClear ) , bDiscardDuplicates( InitializationOptions.bDiscardDuplicates ) , bScrollToBottom( InitializationOptions.bScrollToBottom ) , MaxPageCount( InitializationOptions.MaxPageCount ) , bShowInLogWindow( InitializationOptions.bShowInLogWindow ) , CurrentPageIndex( 0 ) , bIsRefreshing( false ) , LogLabel( InLogLabel ) , MessageLogListingModel( InMessageLogListingModel )`
- L181 _private prototype_ `void RefreshFilteredMessages();` — Rebuilds the list of filtered messages
- L184 _private prototype_ `void DismissNotification(int32 NotificationId);` — Dismisses a notification that was previously shown.
- L187 _private prototype_ `void OpenMessageLogFromNotification(int32 NotificationId);` — Opens the message log from a notification that was previously shown.
- L190 _private prototype_ `void OpenMessageLog();` — Helper function for opening this message log from a notification
- L193 _private prototype_ `int32 NumMessagesPresent( uint32 PageIndex, EMessageSeverity::Type InSeverity ) const;` — Helper function to check if this log contains messages above a certain severity
- L196 _private prototype_ `EMessageSeverity::Type HighestSeverityPresent( uint32 PageIndex ) const;` — Helper function to check the worst severity contained in this log page
- L201 _private member_ `bool bShowFilters;` — Whether filters should be shown for this listing
- L204 _private member_ `bool bShowPages;` — Whether pages should be used/shown for this listing
- L207 _private member_ `bool bAllowClear;` — Whether we allow the user to clear the log.
- L210 _private member_ `bool bDiscardDuplicates;` — Whether to check for duplicate messages & discard them
- L213 _private member_ `bool bScrollToBottom;` — Whether to scroll to the bottom when messages are added
- L216 _private member_ `uint32 MaxPageCount;` — The limit on the number of displayed pages for this listing
- L219 _private member_ `bool bShowInLogWindow;` — Whether to show this log in the main log window
- L222 _private member_ `uint32 CurrentPageIndex;` — The currently displayed page index
- L225 _private member_ `bool bIsRefreshing;` — Tracks if the viewmodel is in the middle of refreshing
- L228 _private member_ `FText LogLabel;` — Label of the listing, displayed to users
- L231 _private member_ `TSharedPtr< FMessageLogListingModel > MessageLogListingModel;` — The model we are getting display info from
- L234 _private member_ `MessageContainer FilteredMessages;` — The same list of messages in the model after filtering is applied
- L237 _private member_ `MessageContainer SelectedFilteredMessages;` — The list of selected messages
- L240 _private member_ `TArray< TSharedRef< FMessageFilter > > MessageFilters;` — The array of message filters used on this listing
- L243 _private member_ `IMessageTokenClickedEvent TokenClickedEvent;` — Delegate to call when a token is clicked
- L246 _private member_ `FChangedEvent ChangedEvent;` — Delegate to call when model data is changed
- L249 _private member_ `FOnSelectionChangedEvent SelectionChangedEvent;` — Delegate to call when selection state is changed
- L252 _private member_ `FOnPageSelectionChangedEvent PageSelectionChangedEvent;` — Delegate to call when page selection state is changed
- L271 _private member_ `TArray<FOpenNotification> OpenNotifications;`
- L272 _private member_ `static int32 NextNotificationId;`

#### struct `FMessageLogListingViewModel::FOpenNotification`  
`struct FOpenNotification`  
_L255-270_
- desc: All open notifications
- L257 _public member_ `int32 NotificationId;`
- L258 _public member_ `TWeakPtr<class SNotificationItem> NotificationItem;`
- L259 _public member_ `const FText NotificationMessage;`
- L261 _public function_ `FOpenNotification(int32 InNotificationId, const TWeakPtr<class SNotificationItem>& InNotificationItem, const FText InNotificationMessage) : NotificationId(InNotificationId) , NotificationItem(InNotificationItem) , NotificationMessage( InNotificationMessage)`
- L269 _public function_ `FOpenNotification() : NotificationId(INDEX_NONE)`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MESSAGELOG_API`
- L68 _delegate_ `DECLARE_DERIVED_EVENT(FMessageLogListingViewModel, IMessageLogListing::IMessageTokenClickedEvent, IMessageTokenClickedEvent) virtual IMessageLogListing::IMessageTokenClickedEvent& OnMessageTokenClicked() override { return TokenClickedEvent; } DECLARE_DERIVED_EVENT(FMessageLogListingViewModel, IMessageLogListing::FChangedEvent, FChangedEvent) virtual IMessageLogListing::FChangedEvent& OnDataChanged() override { return ChangedEvent; } DECLARE_DERIVED_EVENT(FMessageLogListingViewModel, IMessageLogListing::FOnSelectionChangedEvent, FOnSelectionChangedEvent) virtual IMessageLogListing::FOnSelectionChangedEvent& OnSelectionChanged() override { return SelectionChangedEvent; } DECLARE_DERIVED_EVENT(FMessageLogListingViewModel, IMessageLogListing::FOnPageSelectionChangedEvent, FOnPageSelectionChangedEvent ) virtual IMessageLogListing::FOnPageSelectionChangedEvent& OnPageSelectionChanged() override { return PageSelectionChangedEvent; } virtual void Initialize();`
- L71 _delegate_ `DECLARE_DERIVED_EVENT(FMessageLogListingViewModel, IMessageLogListing::FChangedEvent, FChangedEvent) virtual IMessageLogListing::FChangedEvent& OnDataChanged() override { return ChangedEvent; } DECLARE_DERIVED_EVENT(FMessageLogListingViewModel, IMessageLogListing::FOnSelectionChangedEvent, FOnSelectionChangedEvent) virtual IMessageLogListing::FOnSelectionChangedEvent& OnSelectionChanged() override { return SelectionChangedEvent; } DECLARE_DERIVED_EVENT(FMessageLogListingViewModel, IMessageLogListing::FOnPageSelectionChangedEvent, FOnPageSelectionChangedEvent ) virtual IMessageLogListing::FOnPageSelectionChangedEvent& OnPageSelectionChanged() override { return PageSelectionChangedEvent; } virtual void Initialize();`
- L74 _delegate_ `DECLARE_DERIVED_EVENT(FMessageLogListingViewModel, IMessageLogListing::FOnSelectionChangedEvent, FOnSelectionChangedEvent) virtual IMessageLogListing::FOnSelectionChangedEvent& OnSelectionChanged() override { return SelectionChangedEvent; } DECLARE_DERIVED_EVENT(FMessageLogListingViewModel, IMessageLogListing::FOnPageSelectionChangedEvent, FOnPageSelectionChangedEvent ) virtual IMessageLogListing::FOnPageSelectionChangedEvent& OnPageSelectionChanged() override { return PageSelectionChangedEvent; } virtual void Initialize();`
- L77 _delegate_ `DECLARE_DERIVED_EVENT(FMessageLogListingViewModel, IMessageLogListing::FOnPageSelectionChangedEvent, FOnPageSelectionChangedEvent ) virtual IMessageLogListing::FOnPageSelectionChangedEvent& OnPageSelectionChanged() override { return PageSelectionChangedEvent; } virtual void Initialize();`

### `Source/Developer/MessageLog/Public/UserInterface/SMessageLogListing.h` (Public)


#### class `SMessageLogListing`  
`class SMessageLogListing : public SCompoundWidget`  
_L25-173_
- inherits: `SCompoundWidget`
- desc: A message log listing, such as the Compiler Log, or the Map Check Log. Holds the log lines, and any extra widgets necessary.
- L28 _public function_ `SLATE_BEGIN_ARGS(SMessageLogListing)`
- L33 _public prototype_ `SMessageLogListing();`
- L35 _public prototype_ `~SMessageLogListing();`
- L37 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef< class IMessageLogListing >& InModelView );`
- L40 _public prototype_ `void RefreshVisibility();` — Refreshes the log messages, reapplying any filtering
- L43 _public prototype_ `void BroadcastMessageTokenClicked( TSharedPtr< class FTokenizedMessage > Message, const TSharedRef<class IMessageToken>& Token );` — Used to execute the 'on clicked token' delegate
- L45 _public prototype_ `void BroadcastMessageDoubleClicked(TSharedPtr< class FTokenizedMessage > Message);` — Used to execute a message's featured action (a token associated with the entire message)
- L48 _public prototype_ `const TArray< TSharedRef< class FTokenizedMessage > > GetSelectedMessages() const;` — Gets a list of the selected messages
- L51 _public prototype_ `void SelectMessage( const TSharedRef< class FTokenizedMessage >& Message, bool bSelected ) const;` — Set the message selection state
- L54 _public prototype_ `bool IsMessageSelected( const TSharedRef< class FTokenizedMessage >& Message ) const;` — Get the message selection state
- L57 _public prototype_ `void ScrollToMessage( const TSharedRef< class FTokenizedMessage >& Message ) const;` — Scrolls the message into view
- L60 _public prototype_ `void ClearSelectedMessages() const;` — Clears the message selection
- L63 _public prototype_ `void InvertSelectedMessages() const;` — Inverts the message selection
- L66 _public prototype_ `FString GetSelectedMessagesAsString() const;` — Compiles the selected messages into a single string.
- L69 _public prototype_ `FString GetAllMessagesAsString() const;` — Compiles all the messages into a single string.
- L72 _public function_ `const FName& GetName() const` — Gets the message log listing unique name
- L75 _public function_ `const FText& GetLabel() const` — Gets the message log listing label
- L78 _public function_ `const TArray< TSharedRef< class FMessageFilter > >& GetMessageFilters() const` — Gets the set of message filters used when displaying messages
- L81 _public prototype_ `void OnChanged();` — Called when data is changed changed/updated in the model
- L84 _public prototype_ `void OnSelectionChanged();` — Called whenever the viewmodel selection changes
- L89 _public prototype_ `void CopySelectedToClipboard() const;` — Copies the selected messages to the clipboard
- L94 _public prototype_ `FString CopyLogOutput( bool bSelected, bool bClipboard ) const;` — Copies log output (selected/all), optionally to the clipboard
- L97 _public prototype_ `const TSharedRef< const FUICommandList > GetCommandList() const;` — @return	The UICommandList supported by the MessageLogView
- L106 _public prototype_ `FReply OnKeyDown( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override;` — Called after a key is pressed when this widget has focus @param  InKeyEvent  Key event @return  Returns whether the event was handled, along with other possible actions
- L109 _public prototype_ `FString GetPageText() const;` — Delegate supplying a label for the page-flipper widget
- L112 _public prototype_ `FReply OnClickedPrevPage();` — Delegate to display the previous page
- L115 _public prototype_ `FReply OnClickedNextPage();` — Delegate to display the next page
- L118 _public prototype_ `EVisibility GetFilterMenuVisibility();` — Delegate to get the display visibility of the show filter combobox
- L121 _public prototype_ `TSharedRef<ITableRow> MakeShowWidget(TSharedRef<FMessageFilter> Selection, const TSharedRef<STableViewBase>& OwnerTable);` — Generates the widgets for show filtering
- L124 _public prototype_ `TSharedRef<SWidget> OnGetFilterMenuContent();` — Generates the menu content for filtering log content
- L127 _public prototype_ `bool IsPageWidgetEnabled() const;` — Delegate for enabling & disabling the page widget depending on the number of pages
- L130 _public prototype_ `EVisibility GetPageWidgetVisibility() const;` — Delegate for showing & hiding the page widget depending on whether this log uses pages or not
- L133 _public prototype_ `bool IsClearWidgetEnabled() const;` — Delegate for enabling & disabling the clear button depending on the number of messages
- L136 _public prototype_ `EVisibility GetClearWidgetVisibility() const;` — Delegate for showing & hiding the clear button depending on whether this log uses pages or not
- L139 _public prototype_ `FText OnGetPageMenuLabel() const;` — Delegate to generate the label for the page combobox
- L142 _public prototype_ `TSharedRef<SWidget> OnGetPageMenuContent() const;` — Delegate to generate the menu content for the page combobox
- L145 _public prototype_ `void OnPageSelected(uint32 PageIndex);` — Delegate called when a page is selected from the page menu
- L148 _public prototype_ `FReply OnClear();` — Delegate for Clear button
- L152 _private prototype_ `TSharedRef<ITableRow> MakeMessageLogListItemWidget( TSharedRef< class FTokenizedMessage > Message, const TSharedRef< STableViewBase >& OwnerTable );` — Makes the message log line widgets for populating the listing
- L155 _private prototype_ `void OnLineSelectionChanged( TSharedPtr< class FTokenizedMessage > Selection, ESelectInfo::Type SelectInfo );` — Called when map check message line selection has changed
- L157 _private prototype_ `void ContextMenuSelect() const;`
- L158 _private prototype_ `void ContextMenuSelectByMessage(const TCHAR* FormatKey) const;`
- L159 _private prototype_ `TSharedPtr<SWidget> ContextMenuOpening();`
- L163 _private member_ `const TSharedRef< FUICommandList > UICommandList;` — The list of commands with bound delegates for the message log
- L166 _private member_ `TSharedPtr<class FMessageLogListingViewModel> MessageLogListingViewModel;` — Reference to the ViewModel which holds state info and has access to data
- L169 _private member_ `bool bUpdatingSelection;` — Whether the view is currently updating the viewmodel selection
- L172 _private member_ `TSharedPtr< SListView< TSharedRef< class FTokenizedMessage > > > MessageListView;` — The list view for showing all the message log lines

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API MESSAGELOG_API`
