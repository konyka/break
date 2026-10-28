# Plugins / MessagingDebugger

- module root: `Plugins/Messaging/MessagingDebugger/Source/MessagingDebugger`
- headers: 27; symbols: 307
- symbol kinds: class=27, delegate=6, function=47, macro=6, member=90, namespace=4, prototype=127
- PrivateDependencyModuleNames: Core, CoreUObject, InputCore, PropertyEditor, Serialization, Slate, SlateCore, WorkspaceMenuStructure
- PrivateIncludePathModuleNames: Messaging

### `Plugins/Messaging/MessagingDebugger/Source/MessagingDebugger/Private/Models/MessagingDebuggerCommands.h` (Private)


#### class `FMessagingDebuggerCommands`  
`class FMessagingDebuggerCommands : public TCommands<FMessagingDebuggerCommands>`  
_L11-54_
- inherits: `TCommands<FMessagingDebuggerCommands>`
- L17 _public function_ `FMessagingDebuggerCommands() : TCommands<FMessagingDebuggerCommands>("MessagingDebugger", NSLOCTEXT("Contexts", "MessagingDebugger", "Messaging Debugger"), NAME_None, "MessagingDebuggerStyle")` — Default constructor.
- L25 _public function_ `virtual void RegisterCommands() override`
- L38 _public member_ `TSharedPtr<FUICommandInfo> BreakDebugger;` — Holds a command that breaks at the next message.
- L41 _public member_ `TSharedPtr<FUICommandInfo> ClearHistory;` — Holds a command that clears the message history.
- L44 _public member_ `TSharedPtr<FUICommandInfo> ContinueDebugger;` — Holds a command that continues debugging.
- L47 _public member_ `TSharedPtr<FUICommandInfo> StartDebugger;` — Holds a command that starts debugging.
- L50 _public member_ `TSharedPtr<FUICommandInfo> StepDebugger;` — Holds a command that continues debugging for one step.
- L53 _public member_ `TSharedPtr<FUICommandInfo> StopDebugger;` — Holds a command that stops debugging.

#### Free symbols / members of external scopes

- L8 _macro_ `#define LOCTEXT_NAMESPACE "FMessagingDebuggerCommands"`

### `Plugins/Messaging/MessagingDebugger/Source/MessagingDebugger/Private/Models/MessagingDebuggerEndpointFilter.h` (Private)


#### class `FMessagingDebuggerEndpointFilter`  
`class FMessagingDebuggerEndpointFilter`  
_L11-78_
- desc: Implements a filter for the message endpoints list.
- L21 _public function_ `bool FilterEndpoint(const TSharedPtr<FMessageTracerEndpointInfo>& EndpointInfo) const` — Filters the specified endpoint based on the current filter settings. @param EndpointInfo The endpoint to filter. @return true if the endpoint passed the filter, false otherwise.
- L50 _public function_ `void SetFilterString(const FString& InFilterString)` — Sets the filter string. @param InFilterString The filter string to set.
- L63 _public prototype_ `DECLARE_EVENT(FMessagingDebuggerEndpointFilter, FOnMessagingEndpointFilterChanged);` — Gets an event delegate that is invoked when the filter settings changed. @return The event delegate.
- L64 _public function_ `FOnMessagingEndpointFilterChanged& OnChanged()`
- L72 _private member_ `FString FilterString;` — Holds the filter string used to filter endpoints by their names.
- L77 _private member_ `FOnMessagingEndpointFilterChanged ChangedEvent;` — Holds an event delegate that is invoked when the filter settings changed.

#### Free symbols / members of external scopes

- L63 _delegate_ `DECLARE_EVENT(FMessagingDebuggerEndpointFilter, FOnMessagingEndpointFilterChanged);` — Gets an event delegate that is invoked when the filter settings changed. @return The event delegate.

### `Plugins/Messaging/MessagingDebugger/Source/MessagingDebugger/Private/Models/MessagingDebuggerMessageFilter.h` (Private)


#### class `FMessagingDebuggerMessageFilter`  
`class FMessagingDebuggerMessageFilter`  
_L13-52_
- desc: Implements a filter for the message history list.
- L23 _public function_ `bool FilterEndpoint(const TSharedPtr<FMessageTracerMessageInfo>& MessageInfo) const` — Filters the specified message based on the current filter settings. @param MessageInfo The message to filter. @return true if the message passed the filter, false otherwise.
- L42 _public prototype_ `DECLARE_EVENT(FMessagingDebuggerMessageFilter, FOnMessagingMessageFilterChanged);` — Gets an event delegate that is invoked when the filter settings changed. @return The event delegate.
- L43 _public function_ `FOnMessagingMessageFilterChanged& OnChanged()`
- L51 _private member_ `FOnMessagingMessageFilterChanged ChangedEvent;` — Holds an event delegate that is invoked when the filter settings changed.

#### Free symbols / members of external scopes

- L42 _delegate_ `DECLARE_EVENT(FMessagingDebuggerMessageFilter, FOnMessagingMessageFilterChanged);` — Gets an event delegate that is invoked when the filter settings changed. @return The event delegate.

### `Plugins/Messaging/MessagingDebugger/Source/MessagingDebugger/Private/Models/MessagingDebuggerModel.h` (Private)


#### class `FMessagingDebuggerModel`  
`class FMessagingDebuggerModel`  
_L15-151_
- desc: Implements a view model for the messaging debugger.
- L22 _public prototype_ `void ClearVisibilities();` — Clears all visibility filters (to show all messages).
- L29 _public prototype_ `TSharedPtr<FMessageTracerEndpointInfo> GetSelectedEndpoint() const;` — Gets the endpoint that is currently selected in the endpoint list. @return The selected endpoint.
- L36 _public prototype_ `TSharedPtr<FMessageTracerMessageInfo> GetSelectedMessage() const;` — Gets the message that is currently selected in the message history. @return The selected message.
- L44 _public prototype_ `bool IsEndpointVisible(const TSharedRef<FMessageTracerEndpointInfo>& EndpointInfo) const;` — Checks whether messages of the given message endpoint should be visible. @param Endpoint The information of the endpoint to check. @return true if the endpoint's messages should be visible, false otherwise.
- L52 _public prototype_ `bool IsMessageVisible(const TSharedRef<FMessageTracerMessageInfo>& MessageInfo) const;` — Checks whether the given message should be visible. @param MessageInfo The information of the message to check. @return true if the message should be visible, false otherwise.
- L60 _public prototype_ `bool IsTypeVisible(const TSharedRef<FMessageTracerTypeInfo>& TypeInfo) const;` — Checks whether messages of the given type should be visible. @param TypeInfo The information of the message type to check. @return true if messages of the given type should be visible, false otherwise.
- L67 _public prototype_ `void SelectEndpoint(const TSharedPtr<FMessageTracerEndpointInfo>& EndpointInfo);` — Selects the specified endpoint (or none if nullptr). @param EndpointInfo The information of the endpoint to select.
- L74 _public prototype_ `void SelectMessage(const TSharedPtr<FMessageTracerMessageInfo>& MessageInfo);` — Selects the specified message (or none if nullptr). @param MessageInfo The information of the message to select.
- L82 _public prototype_ `void SetEndpointVisibility(const TSharedRef<FMessageTracerEndpointInfo>& EndpointInfo, bool Visible);` — Sets whether messages for the given endpoint should be visible. @param Endpoint The information for the endpoint. @param Visible Whether the endpoint's messages should be visible or not.
- L90 _public prototype_ `void SetTypeVisibility(const TSharedRef<FMessageTracerTypeInfo>& TypeInfo, bool Visible);` — Sets whether messages for the given message type should be visible. @param Endpoint The information for the message type. @param Visible Whether messages of the given type should be visible or not.
- L99 _public prototype_ `DECLARE_EVENT(FMessagingDebuggerModel, FOnMessageVisibilityChanged);` — Gets an event delegate that is invoked when the filter settings changed. @return The event delegate.
- L100 _public function_ `FOnMessageVisibilityChanged& OnMessageVisibilityChanged()`
- L110 _public prototype_ `DECLARE_EVENT(FMessagingDebuggerModel, FOnSelectedEndpointChanged);` — Gets an event delegate that is invoked when the selected endpoint has changed. @return The event delegate.
- L111 _public function_ `FOnSelectedEndpointChanged& OnSelectedEndpointChanged()`
- L121 _public prototype_ `DECLARE_EVENT(FMessagingDebuggerModel, FOnSelectedMessageChanged);` — Gets an event delegate that is invoked when the selected message has changed. @return The event delegate.
- L122 _public function_ `FOnSelectedMessageChanged& OnSelectedMessageChanged()`
- L130 _private member_ `TArray<TSharedPtr<FMessageTracerEndpointInfo>> InvisibleEndpoints;` — Holds the collection of invisible message endpoints.
- L133 _private member_ `TArray<TSharedPtr<FMessageTracerTypeInfo>> InvisibleTypes;` — Holds the collection of invisible message types.
- L136 _private member_ `TSharedPtr<FMessageTracerEndpointInfo> SelectedEndpoint;` — Holds a pointer to the sole endpoint that is currently selected in the endpoint list.
- L139 _private member_ `TSharedPtr<FMessageTracerMessageInfo> SelectedMessage;` — Holds a pointer to the message that is currently selected in the message history.
- L144 _private member_ `FOnMessageVisibilityChanged MessageVisibilityChangedEvent;` — Holds an event delegate that is invoked when the visibility of messages has changed.
- L147 _private member_ `FOnSelectedEndpointChanged SelectedEndpointChangedEvent;` — Holds an event delegate that is invoked when the selected endpoint has changed.
- L150 _private member_ `FOnSelectedMessageChanged SelectedMessageChangedEvent;` — Holds an event delegate that is invoked when the selected message has changed.

#### Free symbols / members of external scopes

- L99 _delegate_ `DECLARE_EVENT(FMessagingDebuggerModel, FOnMessageVisibilityChanged);` — Gets an event delegate that is invoked when the filter settings changed. @return The event delegate.
- L110 _delegate_ `DECLARE_EVENT(FMessagingDebuggerModel, FOnSelectedEndpointChanged);` — Gets an event delegate that is invoked when the selected endpoint has changed. @return The event delegate.
- L121 _delegate_ `DECLARE_EVENT(FMessagingDebuggerModel, FOnSelectedMessageChanged);` — Gets an event delegate that is invoked when the selected message has changed. @return The event delegate.

### `Plugins/Messaging/MessagingDebugger/Source/MessagingDebugger/Private/Models/MessagingDebuggerTypeFilter.h` (Private)


#### class `FMessagingDebuggerTypeFilter`  
`class FMessagingDebuggerTypeFilter`  
_L11-80_
- desc: Implements a filter for the message endpoints list.
- L21 _public function_ `bool FilterType(const TSharedPtr<FMessageTracerTypeInfo>& TypeInfo) const` — Filters the specified message type based on the current filter settings. @param TypeInfo The message type to filter. @return true if the endpoint passed the filter, false otherwise.
- L52 _public function_ `void SetFilterString(const FString& InFilterString)` — Sets the filter string. @param InFilterString The filter string to set.
- L65 _public prototype_ `DECLARE_EVENT(FMessagingDebuggerTypeFilter, FOnMessagingEndpointFilterChanged);` — Gets an event delegate that is invoked when the filter settings changed. @return The event delegate.
- L66 _public function_ `FOnMessagingEndpointFilterChanged& OnChanged()`
- L74 _private member_ `FString FilterString;` — Holds the filter string used to filter message types by their names.
- L79 _private member_ `FOnMessagingEndpointFilterChanged ChangedEvent;` — Holds an event delegate that is invoked when the filter settings changed.

#### Free symbols / members of external scopes

- L65 _delegate_ `DECLARE_EVENT(FMessagingDebuggerTypeFilter, FOnMessagingEndpointFilterChanged);` — Gets an event delegate that is invoked when the filter settings changed. @return The event delegate.

### `Plugins/Messaging/MessagingDebugger/Source/MessagingDebugger/Private/Styles/MessagingDebuggerStyle.h` (Private)


#### class `FMessagingDebuggerStyle`  
`class FMessagingDebuggerStyle final : public FSlateStyleSet`  
_L21-108_
- inherits: `FSlateStyleSet`
- desc: Implements the visual style of the messaging debugger UI.
- L27 _public function_ `FMessagingDebuggerStyle() : FSlateStyleSet("MessagingDebuggerStyle")` — Default constructor.
- L104 _public function_ `virtual ~FMessagingDebuggerStyle()` — Virtual destructor.

#### Free symbols / members of external scopes

- L13 _macro_ `#define IMAGE_BRUSH(RelativePath, ...) FSlateImageBrush(RootToContentDir(RelativePath, TEXT(".png")), __VA_ARGS__)`
- L14 _macro_ `#define BOX_BRUSH(RelativePath, ...) FSlateBoxBrush(RootToContentDir(RelativePath, TEXT(".png")), __VA_ARGS__)`
- L15 _macro_ `#define BORDER_BRUSH(RelativePath, ...) FSlateBorderBrush(RootToContentDir(RelativePath, TEXT(".png")), __VA_ARGS__)`

### `Plugins/Messaging/MessagingDebugger/Source/MessagingDebugger/Private/Widgets/Breakpoints/SMessagingBreakpoints.h` (Private)


#### class `SMessagingBreakpoints`  
`class SMessagingBreakpoints : public SCompoundWidget`  
_L20-60_
- inherits: `SCompoundWidget`
- desc: Implements the message breakpoints panel.
- L25 _public function_ `SLATE_BEGIN_ARGS(SMessagingBreakpoints)`
- L37 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<ISlateStyle>& InStyle, const TSharedRef<IMessageTracer, ESPMode::ThreadSafe>& InTracer);` — Construct this widget. @param InArgs The declaration data for this widget. @param InStyle The visual style to use for this widget. @param InTracer The message tracer.
- L42 _private prototype_ `TSharedRef<ITableRow> HandleBreakpointListGenerateRow(TSharedPtr<IMessageTracerBreakpoint, ESPMode::ThreadSafe> EndpointInfo, const TSharedRef<STableViewBase>& OwnerTable);` — Handles generating a row widget for the endpoint list view.
- L45 _private prototype_ `void HandleBreakpointListSelectionChanged(TSharedPtr<IMessageTracerBreakpoint, ESPMode::ThreadSafe> InItem, ESelectInfo::Type SelectInfo);` — Handles the selection of endpoints.
- L50 _private member_ `TArray<TSharedPtr<IMessageTracerBreakpoint, ESPMode::ThreadSafe>> BreakpointList;` — Holds the filtered list of historic messages.
- L53 _private member_ `TSharedPtr<SListView<TSharedPtr<IMessageTracerBreakpoint, ESPMode::ThreadSafe>>> BreakpointListView;` — Holds the message list view.
- L56 _private member_ `TSharedPtr<ISlateStyle> Style;` — Holds the widget's visual style.
- L59 _private member_ `TSharedPtr<IMessageTracer, ESPMode::ThreadSafe> Tracer;` — Holds a pointer to the message bus tracer.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ESelectInfo`

### `Plugins/Messaging/MessagingDebugger/Source/MessagingDebugger/Private/Widgets/Breakpoints/SMessagingBreakpointsTableRow.h` (Private)


#### class `SMessagingBreakpointsTableRow`  
`class SMessagingBreakpointsTableRow : public SMultiColumnTableRow<TSharedPtr<IMessageTracerBreakpoint, ESPMode::ThreadSafe>>`  
_L17-49_
- inherits: `SMultiColumnTableRow<TSharedPtr<IMessageTracerBreakpoint,ESPMode::ThreadSafe>>`
- desc: Implements a row widget for the session console log.
- L22 _public function_ `SLATE_BEGIN_ARGS(SMessagingBreakpointsTableRow)`
- L34 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, const TSharedRef<IMessageTracerBreakpoint, ESPMode::ThreadSafe> InBreakpoint);` — Constructs the widget. @param InArgs The construction arguments. @param InOwnerTableView The table view that owns this row.
- L40 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L45 _private member_ `TSharedPtr<IMessageTracerBreakpoint, ESPMode::ThreadSafe> Breakpoint;` — Holds a pointer to the breakpoint that is shown in this row.
- L48 _private member_ `TSharedPtr<ISlateStyle> Style;` — Holds the widget's visual style.

### `Plugins/Messaging/MessagingDebugger/Source/MessagingDebugger/Private/Widgets/EndpointDetails/SMessagingAddressTableRow.h` (Private)


#### class `SMessagingAddressTableRow`  
`class SMessagingAddressTableRow : public SMultiColumnTableRow<TSharedPtr<FMessageTracerAddressInfo>>`  
_L20-61_
- inherits: `SMultiColumnTableRow<TSharedPtr<FMessageTracerAddressInfo>>`
- desc: Implements a row widget for the dispatch state list.
- L25 _public function_ `SLATE_BEGIN_ARGS(SMessagingAddressTableRow)`
- L38 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, const TSharedRef<FMessagingDebuggerModel>& InModel);` — Constructs the widget. @param InArgs The construction arguments. @param InOwnerTableView The table view that owns this row.
- L44 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L49 _private prototype_ `FText HandleTimeUnregisteredText() const;` — Callback for getting the timestamp at which the address was unregistered.
- L54 _private member_ `TSharedPtr<FMessageTracerAddressInfo> AddressInfo;` — Holds the address information.
- L57 _private member_ `TSharedPtr<FMessagingDebuggerModel> Model;` — Holds a pointer to the view model.
- L60 _private member_ `TSharedPtr<ISlateStyle> Style;` — Holds the widget's visual style.

### `Plugins/Messaging/MessagingDebugger/Source/MessagingDebugger/Private/Widgets/EndpointDetails/SMessagingEndpointDetails.h` (Private)


#### class `SMessagingEndpointDetails`  
`class SMessagingEndpointDetails : public SCompoundWidget`  
_L20-74_
- inherits: `SCompoundWidget`
- desc: Implements the message types panel.
- L25 _public function_ `SLATE_BEGIN_ARGS(SMessagingEndpointDetails)`
- L37 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FMessagingDebuggerModel>& InModel, const TSharedRef<ISlateStyle>& InStyle);` — Construct this widget. @param InArgs The declaration data for this widget. @param InModel The view model to use. @param InStyle The visual style to use for this widget.
- L43 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L48 _protected prototype_ `void RefreshAddressInfo();` — Refreshes the endpoint's address information.
- L53 _private prototype_ `TSharedRef<ITableRow> HandleAddressListGenerateRow(TSharedPtr<FMessageTracerAddressInfo> AddressInfo, const TSharedRef<STableViewBase>& OwnerTable);` — Callback for generating a row widget for the address list view.
- L56 _private prototype_ `FText HandleEndpointDetailsReceivedMessagesText() const;` — Callback for getting the number of received messages.
- L59 _private prototype_ `FText HandleEndpointDetailsSentMessagesText() const;` — Callback for getting the number of sent messages.
- L64 _private member_ `TArray<TSharedPtr<FMessageTracerAddressInfo>> AddressList;` — Holds the list of address information.
- L67 _private member_ `TSharedPtr<SListView<TSharedPtr<FMessageTracerAddressInfo>> > AddressListView;` — Holds the address information list view.
- L70 _private member_ `TSharedPtr<FMessagingDebuggerModel> Model;` — Holds a pointer to the view model.
- L73 _private member_ `TSharedPtr<ISlateStyle> Style;` — Holds the widget's visual style.

### `Plugins/Messaging/MessagingDebugger/Source/MessagingDebugger/Private/Widgets/Endpoints/SMessagingEndpoints.h` (Private)


#### class `SMessagingEndpoints`  
`class SMessagingEndpoints : public SCompoundWidget`  
_L23-98_
- inherits: `SCompoundWidget`
- desc: Implements the message endpoints panel.
- L28 _public function_ `SLATE_BEGIN_ARGS(SMessagingEndpoints)`
- L34 _public prototype_ `~SMessagingEndpoints();` — Destructor.
- L46 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FMessagingDebuggerModel>& InModel, const TSharedRef<ISlateStyle>& InStyle, const TSharedRef<IMessageTracer, ESPMode::ThreadSafe>& InTracer);` — Construct this widget. @param InArgs The declaration data for this widget. @param InModel The view model to use. @param InStyle The visual style to use for this widget. @param InTracer The message tracer.
- L52 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L57 _protected prototype_ `void ReloadEndpointList();` — Reloads the list of endpoints.
- L62 _private prototype_ `TSharedRef<ITableRow> HandleEndpointListGenerateRow(TSharedPtr<FMessageTracerEndpointInfo> EndpointInfo, const TSharedRef<STableViewBase>& OwnerTable);` — Handles generating a row widget for the endpoint list view.
- L65 _private prototype_ `FText HandleEndpointListGetHighlightText() const;` — Handles getting the highlight string for endpoints.
- L68 _private prototype_ `void HandleEndpointListSelectionChanged(TSharedPtr<FMessageTracerEndpointInfo> InItem, ESelectInfo::Type SelectInfo);` — Handles the selection of endpoints.
- L71 _private prototype_ `void HandleFilterChanged();` — Handles endpoint filter changes.
- L74 _private prototype_ `void HandleModelSelectedMessageChanged();` — Callback for handling message selection changes.
- L82 _private member_ `TArray<TSharedPtr<FMessageTracerEndpointInfo>> EndpointList;` — Holds the filtered list of historic messages.
- L85 _private member_ `TSharedPtr<SListView<TSharedPtr<FMessageTracerEndpointInfo>>> EndpointListView;` — Holds the message list view.
- L88 _private member_ `TSharedPtr<FMessagingDebuggerEndpointFilter> Filter;` — Holds the endpoint filter model.
- L91 _private member_ `TSharedPtr<FMessagingDebuggerModel> Model;` — Holds a pointer to the view model.
- L94 _private member_ `TSharedPtr<ISlateStyle> Style;` — Holds the widget's visual style.
- L97 _private member_ `TSharedPtr<IMessageTracer, ESPMode::ThreadSafe> Tracer;` — Holds a pointer to the message bus tracer.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ESelectInfo`

### `Plugins/Messaging/MessagingDebugger/Source/MessagingDebugger/Private/Widgets/Endpoints/SMessagingEndpointsFilterBar.h` (Private)


#### class `SMessagingEndpointsFilterBar`  
`class SMessagingEndpointsFilterBar : public SCompoundWidget`  
_L13-35_
- inherits: `SCompoundWidget`
- desc: Implements the endpoints list filter bar widget.
- L18 _public function_ `SLATE_BEGIN_ARGS(SMessagingEndpointsFilterBar)`
- L29 _public prototype_ `void Construct(const FArguments& InArgs, TSharedRef<FMessagingDebuggerEndpointFilter> InFilter);` — Construct this widget. @param InArgs The declaration data for this widget. @param InFilter The filter model.
- L34 _private member_ `TSharedPtr<FMessagingDebuggerEndpointFilter> Filter;` — Holds a pointer to the filter model.

### `Plugins/Messaging/MessagingDebugger/Source/MessagingDebugger/Private/Widgets/Endpoints/SMessagingEndpointsTableRow.h` (Private)


#### class `SMessagingEndpointsTableRow`  
`class SMessagingEndpointsTableRow : public SMultiColumnTableRow<TSharedPtr<FMessageTracerEndpointInfo>>`  
_L20-60_
- inherits: `SMultiColumnTableRow<TSharedPtr<FMessageTracerEndpointInfo>>`
- desc: Implements a row widget for the session console log.
- L25 _public function_ `SLATE_BEGIN_ARGS(SMessagingEndpointsTableRow)`
- L39 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, const TSharedRef<FMessagingDebuggerModel>& InModel);` — Constructs the widget. @param InArgs The construction arguments. @param InOwnerTableView The table view that owns this row.
- L45 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L50 _private member_ `TSharedPtr<FMessageTracerEndpointInfo> EndpointInfo;` — Holds the endpoint's debug information.
- L53 _private member_ `TAttribute<FText> HighlightText;` — Holds the highlight string for the message.
- L56 _private member_ `TSharedPtr<FMessagingDebuggerModel> Model;` — Holds a pointer to the view model.
- L59 _private member_ `TSharedPtr<ISlateStyle> Style;` — Holds the widget's visual style.

### `Plugins/Messaging/MessagingDebugger/Source/MessagingDebugger/Private/Widgets/Graph/SMessagingGraph.h` (Private)


#### class `SMessagingGraph`  
`class SMessagingGraph : public SCompoundWidget`  
_L13-35_
- inherits: `SCompoundWidget`
- desc: Implements the message interaction graph panel.
- L18 _public function_ `SLATE_BEGIN_ARGS(SMessagingGraph)`
- L29 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<ISlateStyle>& InStyle);` — Construct this widget. @param InArgs The declaration data for this widget. @param InStyle The visual style to use for this widget.

### `Plugins/Messaging/MessagingDebugger/Source/MessagingDebugger/Private/Widgets/History/SMessagingHistory.h` (Private)


#### class `SMessagingHistory`  
`class SMessagingHistory : public SCompoundWidget`  
_L23-127_
- inherits: `SCompoundWidget`
- desc: Implements the message history panel.
- L28 _public function_ `SLATE_BEGIN_ARGS(SMessagingHistory)`
- L34 _public prototype_ `~SMessagingHistory();` — Destructor.
- L46 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef<FMessagingDebuggerModel>& InModel, const TSharedRef<ISlateStyle>& InStyle, const TSharedRef<IMessageTracer, ESPMode::ThreadSafe>& InTracer);` — Construct this widget. @param InArgs The construction arguments. @param InModel The view model to use. @param InStyle The visual style to use for this widget. @param InTracer The message tracer.
- L59 _protected prototype_ `void AddMessage(const TSharedRef<FMessageTracerMessageInfo>& MessageInfo);` — Adds the given message to the history. @param MessageInfo The information about the message to add.
- L62 _protected prototype_ `void ReloadMessages();` — Reloads the message history.
- L67 _private prototype_ `void HandleFilterChanged();` — Callback for message filter changes.
- L70 _private prototype_ `TSharedRef<ITableRow> HandleMessageListGenerateRow(TSharedPtr<FMessageTracerMessageInfo> MessageInfo, const TSharedRef<STableViewBase>& OwnerTable);` — Callback for generating a row widget for the message list view.
- L73 _private prototype_ `FText HandleMessageListGetHighlightText() const;` — Callback for getting the message list's highlight string.
- L76 _private prototype_ `void HandleMessageListItemDoubleClick(TSharedPtr<FMessageTracerMessageInfo> Item);` — Callback for double-clicking a message item.
- L79 _private prototype_ `void HandleMessageListItemScrolledIntoView(TSharedPtr<FMessageTracerMessageInfo> Item, const TSharedPtr<ITableRow>& TableRow);` — Callback for scrolling a message item into view.
- L82 _private prototype_ `void HandleMessageListSelectionChanged(TSharedPtr<FMessageTracerMessageInfo> InItem, ESelectInfo::Type SelectInfo);` — Callback for selecting a message in the message list view.
- L85 _private prototype_ `void HandleModelMessageVisibilityChanged();` — Callback for changes in message visibility.
- L88 _private prototype_ `void HandleShowHiddenHyperlinkNavigate();` — Callback for clicking the 'Show hidden' hyperlink.
- L91 _private prototype_ `EVisibility HandleShowHiddenHyperlinkVisibility() const;` — Callback for getting the visibility of the 'Show hidden' hyperlink.
- L94 _private prototype_ `FText HandleStatusBarText() const;` — Callback for getting the status bar text.
- L97 _private prototype_ `void HandleTracerMessageAdded(TSharedRef<FMessageTracerMessageInfo> MessageInfo);` — Callback for when a message has been added to the message tracer.
- L100 _private prototype_ `void HandleTracerMessagesReset();` — Callback for when the tracer's message history has been reset.
- L105 _private member_ `TSharedPtr<FMessagingDebuggerMessageFilter> Filter;` — Holds the message filter model.
- L108 _private member_ `TArray<TSharedPtr<FMessageTracerMessageInfo>> MessageList;` — Holds the filtered list of historic messages.
- L111 _private member_ `TSharedPtr<SListView<TSharedPtr<FMessageTracerMessageInfo>>> MessageListView;` — Holds the message list view.
- L114 _private member_ `TSharedPtr<FMessagingDebuggerModel> Model;` — Holds a pointer to the view model.
- L117 _private member_ `bool ShouldScrollToLast;` — Holds a flag indicating whether the message list should auto-scroll to the last item.
- L120 _private member_ `TSharedPtr<ISlateStyle> Style;` — Holds the widget's visual style.
- L123 _private member_ `int32 TotalMessages;` — Holds the total number of messages (including invisible ones).
- L126 _private member_ `TSharedPtr<IMessageTracer, ESPMode::ThreadSafe> Tracer;` — Holds a pointer to the message bus tracer.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ESelectInfo`

### `Plugins/Messaging/MessagingDebugger/Source/MessagingDebugger/Private/Widgets/History/SMessagingHistoryFilterBar.h` (Private)


#### class `SMessagingHistoryFilterBar`  
`class SMessagingHistoryFilterBar : public SCompoundWidget`  
_L17-45_
- inherits: `SCompoundWidget`
- desc: Implements the messaging history command bar widget.
- L22 _public function_ `SLATE_BEGIN_ARGS(SMessagingHistoryFilterBar)`
- L33 _public function_ `void Construct(const FArguments& InArgs, TSharedRef<FMessagingDebuggerMessageFilter> InFilter)` — Construct this widget @param InArgs The declaration data for this widget. @param InFilter The filter model.
- L44 _private member_ `TSharedPtr<FMessagingDebuggerMessageFilter> Filter;` — Holds the filter model.

#### Free symbols / members of external scopes

- L11 _macro_ `#define LOCTEXT_NAMESPACE "SMessagingHistoryFilterBar"`

### `Plugins/Messaging/MessagingDebugger/Source/MessagingDebugger/Private/Widgets/History/SMessagingHistoryTableRow.h` (Private)


#### class `SMessagingHistoryTableRow`  
`class SMessagingHistoryTableRow : public SMultiColumnTableRow<TSharedPtr<FMessageTracerMessageInfo>>`  
_L22-109_
- inherits: `SMultiColumnTableRow<TSharedPtr<FMessageTracerMessageInfo>>`
- desc: Implements a row widget for the message history list.
- L27 _public function_ `SLATE_BEGIN_ARGS(SMessagingHistoryTableRow)`
- L41 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView);` — Constructs the widget. @param InArgs The construction arguments. @param InOwnerTableView The table view that owns this row.
- L47 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L53 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L62 _protected prototype_ `FText ScopeToText(EMessageScope Scope) const;` — Converts the given message scope to a human readable string. @return The string representation.
- L72 _protected prototype_ `FText TimespanToReadableText(double Seconds) const;` — Converts the given time span in seconds to a human readable string. @param Seconds The time span to convert. @return The string representation. @todo gmp: refactor this into FText::AsTimespan or something like that
- L77 _private prototype_ `FSlateColor HandleDispatchLatencyColorAndOpacity() const;` — Callback for getting the text color of the DispatchLatency column.
- L79 _private prototype_ `const FSlateBrush* HandleFlagImage() const;`
- L82 _private prototype_ `FText HandleRecipientsText() const;` — Callback for getting the text in the Recipients column.
- L85 _private prototype_ `FSlateColor HandleRouteLatencyColorAndOpacity() const;` — Callback for getting the text color of the RouteLatency column.
- L88 _private prototype_ `FText HandleRouteLatencyText() const;` — Callback for getting the text in the RouteLatency column.
- L91 _private prototype_ `FSlateColor HandleTextColorAndOpacity() const;` — Callback for getting the text color of various columns.
- L96 _private member_ `TAttribute<FText> HighlightText;` — Holds the highlight string for the message.
- L99 _private member_ `TSharedPtr<FMessageTracerMessageInfo> MessageInfo;` — Holds message's debug information.
- L102 _private member_ `double MaxDispatchLatency;` — Holds the maximum dispatch latency.
- L105 _private member_ `double MaxHandlingTime;` — Holds the maximum time that was needed to handle the message.
- L108 _private member_ `TSharedPtr<ISlateStyle> Style;` — Holds the widget's visual style.

### `Plugins/Messaging/MessagingDebugger/Source/MessagingDebugger/Private/Widgets/Interceptors/SMessagingInterceptors.h` (Private)


#### class `SMessagingInterceptors`  
`class SMessagingInterceptors : public SCompoundWidget`  
_L18-68_
- inherits: `SCompoundWidget`
- desc: Implements the message interceptors panel.
- L23 _public function_ `SLATE_BEGIN_ARGS(SMessagingInterceptors)`
- L36 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef<FMessagingDebuggerModel>& InModel, const TSharedRef<ISlateStyle>& InStyle, const TSharedRef<IMessageTracer, ESPMode::ThreadSafe>& InTracer);` — Construct this widget @param InArgs The declaration data for this widget. @param InModel The view model to use. @param InStyle The visual style to use for this widget. @param InTracer The message tracer.
- L45 _protected prototype_ `void ReloadInterceptorList();` — Reloads the list of interceptors.
- L50 _private prototype_ `TSharedRef<ITableRow> HandleInterceptorListGenerateRow(TSharedPtr<FMessageTracerInterceptorInfo> InterceptorInfo, const TSharedRef<STableViewBase>& OwnerTable);` — Handles generating a row widget for the interceptor list view.
- L55 _private member_ `TArray<TSharedPtr<FMessageTracerInterceptorInfo>> InterceptorList;` — Holds the filtered list of interceptors.
- L58 _private member_ `TSharedPtr<SListView<TSharedPtr<FMessageTracerInterceptorInfo>>> InterceptorListView;` — Holds the interceptor list view.
- L61 _private member_ `TSharedPtr<FMessagingDebuggerModel> Model;` — Holds a pointer to the view model.
- L64 _private member_ `TSharedPtr<ISlateStyle> Style;` — Holds the widget's visual style.
- L67 _private member_ `TSharedPtr<IMessageTracer, ESPMode::ThreadSafe> Tracer;` — Holds a pointer to the message bus tracer.

### `Plugins/Messaging/MessagingDebugger/Source/MessagingDebugger/Private/Widgets/Interceptors/SMessagingInterceptorsTableRow.h` (Private)


#### class `SMessagingInterceptorsTableRow`  
`class SMessagingInterceptorsTableRow : public SMultiColumnTableRow<TSharedPtr<FMessageTracerInterceptorInfo>>`  
_L19-60_
- inherits: `SMultiColumnTableRow<TSharedPtr<FMessageTracerInterceptorInfo>>`
- desc: Implements a row widget for the interceptors list.
- L24 _public function_ `SLATE_BEGIN_ARGS(SMessagingInterceptorsTableRow)`
- L37 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, const TSharedRef<FMessagingDebuggerModel>& InModel);` — Constructs the widget. @param InArgs The construction arguments. @param InOwnerTableView The table view that owns this row.
- L43 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L48 _private prototype_ `FText HandleTimeUnregisteredText() const;` — Callback for getting the timestamp at which the address was unregistered.
- L53 _private member_ `TSharedPtr<FMessageTracerInterceptorInfo> InterceptorInfo;` — Holds the interceptor information.
- L56 _private member_ `TSharedPtr<FMessagingDebuggerModel> Model;` — Holds a pointer to the view model.
- L59 _private member_ `TSharedPtr<ISlateStyle> Style;` — Holds the widget's visual style.

### `Plugins/Messaging/MessagingDebugger/Source/MessagingDebugger/Private/Widgets/MessageData/SMessagingMessageData.h` (Private)


#### class `SMessagingMessageData`  
`class SMessagingMessageData : public SCompoundWidget , public FNotifyHook`  
_L19-76_
- inherits: `SCompoundWidget,FNotifyHook`
- desc: Implements the message data panel.
- L25 _public function_ `SLATE_BEGIN_ARGS(SMessagingMessageData)`
- L31 _public prototype_ `~SMessagingMessageData();` — Destructor.
- L42 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FMessagingDebuggerModel>& InModel, const TSharedRef<ISlateStyle>& InStyle);` — Construct this widget. @param InArgs The declaration data for this widget. @param InModel The view model to use. @param InStyle The visual style to use for this widget.
- L48 _public prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, class FEditPropertyChain* PropertyThatChanged) override;`
- L53 _private prototype_ `bool HandleDetailsViewIsPropertyEditable() const;` — Handles checking whether the details view is editable.
- L56 _private prototype_ `EVisibility HandleDetailsViewVisibility() const;` — Handles determining the visibility of the details view.
- L59 _private prototype_ `void HandleModelSelectedMessageChanged();` — Callback for handling message selection changes.
- L65 _private member_ `TSharedPtr<IStructureDetailsView> StructureDetailsView;` — Holds the structure details view.
- L72 _private member_ `TSharedPtr<FMessagingDebuggerModel> Model;` — Holds a pointer to the view model.
- L75 _private member_ `TSharedPtr<ISlateStyle> Style;` — Holds the widget's visual style.

### `Plugins/Messaging/MessagingDebugger/Source/MessagingDebugger/Private/Widgets/MessageDetails/SMessagingDispatchStateTableRow.h` (Private)


#### class `SMessagingDispatchStateTableRow`  
`class SMessagingDispatchStateTableRow : public SMultiColumnTableRow<TSharedPtr<FMessageTracerDispatchState>>`  
_L18-306_
- inherits: `SMultiColumnTableRow<TSharedPtr<FMessageTracerDispatchState>>`
- desc: Implements a row widget for the dispatch state list.
- L23 _public function_ `SLATE_BEGIN_ARGS(SMessagingDispatchStateTableRow)`
- L36 _public function_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, const TSharedRef<FMessagingDebuggerModel>& InModel)` — Constructs the widget. @param InArgs The construction arguments. @param InOwnerTableView The table view that owns this row.
- L53 _public function_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override`
- L134 _protected function_ `FSlateColor TimespanToColor(double Timespan) const` — Converts a time span a color value. @param Latency The time span to convert. @return The corresponding color value.
- L160 _protected function_ `FText NamedThreadToReadableText(ENamedThreads::Type NamedThread)` — Converts a named thread to a human readable string. @param NamedThread The named thread. @return The text representation.
- L192 _protected function_ `FText TimespanToReadableText(double Seconds) const` — Converts the given time span in seconds to a human readable string. @param Seconds The time span to convert. @return The text representation. @todo gmp: refactor this into FText::AsTimespan or something like that
- L224 _private function_ `FText HandleDispatchTypeText() const` — Callback for getting the dispatch type.
- L243 _private function_ `FText HandleDispatchTypeTooltip() const` — Callback for getting the dispatch type tool tip text.
- L259 _private function_ `FText HandleHandlingTimeText() const` — Callback for getting the handling time text.
- L270 _private function_ `FSlateColor HandleHandlingTimeColorAndOpacity() const` — Callback for getting the color of a time span text.
- L281 _private function_ `const FSlateBrush* HandleTypeImage() const` — Callback for getting the dispatch type image.
- L299 _private member_ `TSharedPtr<FMessageTracerDispatchState> DispatchState;` — Holds the message dispatch state.
- L302 _private member_ `TSharedPtr<FMessagingDebuggerModel> Model;` — Holds a pointer to the view model.
- L305 _private member_ `TSharedPtr<ISlateStyle> Style;` — Holds the widget's visual style.

#### Free symbols / members of external scopes

- L12 _macro_ `#define LOCTEXT_NAMESPACE "SMessagingDispatchStateTableRow"`

### `Plugins/Messaging/MessagingDebugger/Source/MessagingDebugger/Private/Widgets/MessageDetails/SMessagingMessageDetails.h` (Private)


#### class `SMessagingMessageDetails`  
`class SMessagingMessageDetails : public SCompoundWidget`  
_L20-79_
- inherits: `SCompoundWidget`
- desc: Implements the message details panel.
- L25 _public function_ `SLATE_BEGIN_ARGS(SMessagingMessageDetails)`
- L31 _public prototype_ `~SMessagingMessageDetails();` — Destructor.
- L42 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FMessagingDebuggerModel>& InModel, const TSharedRef<ISlateStyle>& InStyle);` — Construct this widget. @param InArgs The declaration data for this widget. @param InModel The view model to use. @param InStyle The visual style to use for this widget.
- L47 _protected prototype_ `void RefreshDetails();` — Refreshes the details widget.
- L52 _private prototype_ `TSharedRef<ITableRow> HandleDispatchStateListGenerateRow(TSharedPtr<FMessageTracerDispatchState> DispatchState, const TSharedRef<STableViewBase>& OwnerTable);` — Callback for generating a row widget for the dispatch state list view.
- L55 _private prototype_ `FText HandleExpirationText() const;` — Callback for getting the text of the 'Expiration' field.
- L58 _private prototype_ `void HandleModelSelectedMessageChanged();` — Callback for handling message selection changes.
- L61 _private prototype_ `FText HandleSenderThreadText() const;` — Callback for getting the text of the 'Sender Thread' field.
- L64 _private prototype_ `FText HandleTimestampText() const;` — Callback for getting the text of the 'Timestamp' field.
- L69 _private member_ `TArray<TSharedPtr<FMessageTracerDispatchState>> DispatchStateList;` — Holds the list of dispatch states.
- L72 _private member_ `TSharedPtr<SListView<TSharedPtr<FMessageTracerDispatchState>> > DispatchStateListView;` — Holds the dispatch state list view.
- L75 _private member_ `TSharedPtr<FMessagingDebuggerModel> Model;` — Holds a pointer to the view model.
- L78 _private member_ `TSharedPtr<ISlateStyle> Style;` — Holds the widget's visual style.

### `Plugins/Messaging/MessagingDebugger/Source/MessagingDebugger/Private/Widgets/SMessagingDebugger.h` (Private)


#### class `SMessagingDebugger`  
`class SMessagingDebugger : public SCompoundWidget`  
_L22-136_
- inherits: `SCompoundWidget`
- desc: Implements the messaging system debugger application.
- L27 _public function_ `SLATE_BEGIN_ARGS(SMessagingDebugger)`
- L33 _public prototype_ `SMessagingDebugger();` — Default constructor.
- L46 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef<SDockTab>& ConstructUnderMajorTab, const TSharedPtr<SWindow>& ConstructUnderWindow, const TSharedRef<IMessageTracer, ESPMode::ThreadSafe>& InMessageTracer, const TSharedRef<ISlateStyle>& InStyle);` — Constructs the application. @param InArgs The Slate argument list. @param ConstructUnderMajorTab The major tab which will contain the session front-end. @param ConstructUnderWindow The window in which this widget is being constructed. @param InMessageTracer The message tracer to use for the debugger. @param InStyleSet The style set to use.
- L61 _protected prototype_ `static void FillWindowMenu(FMenuBuilder& MenuBuilder, const TSharedPtr<FTabManager> TabManager);` — Fills the Window menu with menu items. @param MenuBuilder The multi-box builder that should be filled with content for this pull-down menu. @param TabManager A Tab Manager from which to populate tab spawner menu items.
- L67 _protected prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L68 _protected prototype_ `virtual bool SupportsKeyboardFocus() const override;`
- L73 _private prototype_ `bool HandleBreakDebuggerCommandCanExecute() const;` — Callback for checking whether the BreakDebugger command can be executed.
- L76 _private prototype_ `void HandleBreakDebuggerCommandExecute();` — Callback for clicking the BreakDebugger command.
- L79 _private prototype_ `bool HandleClearHistoryCommandCanExecute() const;` — Callback for checking whether the ClearHistory command can be executed.
- L82 _private prototype_ `void HandleClearHistoryCommandExecute();` — Callback for clicking the ClearHistory command.
- L85 _private prototype_ `bool HandleContinueDebuggerCommandCanExecute() const;` — Callback for checking whether the ContinueDebugger command can be executed.
- L88 _private prototype_ `void HandleContinueDebuggerCommandExecute();` — Callback for clicking the ContinueDebugger command.
- L91 _private prototype_ `bool HandleContinueDebuggerCommandIsVisible() const;` — Callback for checking whether the ContinueDebugger command is visible.
- L94 _private prototype_ `void HandleMajorTabPersistVisualState();` — Callback for for when the owner tab's visual state is being persisted.
- L97 _private prototype_ `bool HandleStartDebuggerCommandCanExecute() const;` — Callback for checking whether the StartDebugger command can be executed.
- L100 _private prototype_ `void HandleStartDebuggerCommandExecute();` — Callback for clicking the StartDebugger command.
- L103 _private prototype_ `bool HandleStartDebuggerCommandIsVisible() const;` — Callback for checking whether the StartDebugger command is visible.
- L106 _private prototype_ `bool HandleStepDebuggerCommandCanExecute() const;` — Callback for checking whether the StepDebugger command can be executed.
- L109 _private prototype_ `void HandleStepDebuggerCommandExecute();` — Callback for clicking the StepDebugger command.
- L112 _private prototype_ `bool HandleStopDebuggerCommandCanExecute() const;` — Callback for checking whether the StopDebugger command can be executed.
- L115 _private prototype_ `void HandleStopDebuggerCommandExecute();` — Callback for clicking the StopDebugger command.
- L118 _private prototype_ `TSharedRef<SDockTab> HandleTabManagerSpawnTab(const FSpawnTabArgs& Args, FName TabIdentifier) const;` — Callback for spawning tabs.
- L123 _private member_ `TSharedRef<FUICommandList> CommandList;` — Holds the list of UI commands.
- L126 _private member_ `TSharedPtr<IMessageTracer, ESPMode::ThreadSafe> MessageTracer;` — Holds a pointer to the message bus tracer.
- L129 _private member_ `TSharedRef<FMessagingDebuggerModel> Model;` — Holds the messaging debugger's view model.
- L132 _private member_ `TSharedPtr<ISlateStyle> Style;` — Holds the widget's visual style.
- L135 _private member_ `TSharedPtr<FTabManager> TabManager;` — Holds the tab manager that manages the front-end's tabs.

### `Plugins/Messaging/MessagingDebugger/Source/MessagingDebugger/Private/Widgets/Toolbar/SMessagingDebuggerToolbar.h` (Private)


#### class `SMessagingDebuggerToolbar`  
`class SMessagingDebuggerToolbar : public SCompoundWidget`  
_L15-43_
- inherits: `SCompoundWidget`
- desc: Implements the messaging debugger toolbar widget.
- L20 _public function_ `SLATE_BEGIN_ARGS(SMessagingDebuggerToolbar)`
- L32 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<ISlateStyle>& InStyle, const TSharedRef<FUICommandList>& InCommandList);` — Construct this widget. @param InArgs The declaration data for this widget. @param InStyle The visual style to use for this widget. @param InCommandList The command list to bind to.
- L42 _protected prototype_ `TSharedRef<SWidget> MakeToolbar(const TSharedRef<FUICommandList>& CommandList);` — Creates the toolbar widget. @param CommandList The command list to use for the toolbar buttons. @return The toolbar widget.

### `Plugins/Messaging/MessagingDebugger/Source/MessagingDebugger/Private/Widgets/Types/SMessagingTypes.h` (Private)


#### class `SMessagingTypes`  
`class SMessagingTypes : public SCompoundWidget`  
_L23-106_
- inherits: `SCompoundWidget`
- desc: Implements the message types panel.
- L28 _public function_ `SLATE_BEGIN_ARGS(SMessagingTypes)`
- L34 _public prototype_ `~SMessagingTypes();` — Destructor.
- L46 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef<FMessagingDebuggerModel>& InModel, const TSharedRef<ISlateStyle>& InStyle, const TSharedRef<IMessageTracer, ESPMode::ThreadSafe>& InTracer);` — Construct this widget. @param InArgs The declaration data for this widget. @param InModel The view model to use. @param InStyle The visual style to use for this widget. @param InTracer The message tracer.
- L59 _protected prototype_ `void AddType(const TSharedRef<FMessageTracerTypeInfo>& TypeInfo);` — Adds the given message to the history. @param TypeInfo The information about the message type to add.
- L62 _protected prototype_ `void ReloadTypes();` — Reloads the message history.
- L67 _private prototype_ `void HandleFilterChanged();` — Callback for message type filter changes.
- L70 _private prototype_ `void HandleModelSelectedMessageChanged();` — Callback for handling message selection changes.
- L73 _private prototype_ `void HandleTracerMessagesReset();` — Callback for when the tracer's message history has been reset.
- L76 _private prototype_ `void HandleTracerTypeAdded(TSharedRef<FMessageTracerTypeInfo> TypeInfo);` — Callback for when a message type has been added to the message tracer.
- L79 _private prototype_ `TSharedRef<ITableRow> HandleTypeListGenerateRow(TSharedPtr<FMessageTracerTypeInfo> TypeInfo, const TSharedRef<STableViewBase>& OwnerTable);` — Callback for generating a row widget for the message type list view.
- L82 _private prototype_ `FText HandleTypeListGetHighlightText() const;` — Callback for getting the highlight string for message types.
- L85 _private prototype_ `void HandleTypeListSelectionChanged(TSharedPtr<FMessageTracerTypeInfo> InItem, ESelectInfo::Type SelectInfo);` — Callback for selecting message types.
- L90 _private member_ `TSharedPtr<FMessagingDebuggerTypeFilter> Filter;` — Holds the message type filter model.
- L93 _private member_ `TSharedPtr<FMessagingDebuggerModel> Model;` — Holds a pointer to the view model.
- L96 _private member_ `TSharedPtr<ISlateStyle> Style;` — Holds the widget's visual style.
- L99 _private member_ `TSharedPtr<IMessageTracer, ESPMode::ThreadSafe> Tracer;` — Holds a pointer to the message bus tracer.
- L102 _private member_ `TArray<TSharedPtr<FMessageTracerTypeInfo>> TypeList;` — Holds the filtered list of message types.
- L105 _private member_ `TSharedPtr<SListView<TSharedPtr<FMessageTracerTypeInfo>>> TypeListView;` — Holds the message type list view.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace ESelectInfo`

### `Plugins/Messaging/MessagingDebugger/Source/MessagingDebugger/Private/Widgets/Types/SMessagingTypesFilterBar.h` (Private)


#### class `SMessagingTypesFilterBar`  
`class SMessagingTypesFilterBar : public SCompoundWidget`  
_L13-39_
- inherits: `SCompoundWidget`
- desc: Implements the message type list filter bar widget.
- L18 _public function_ `SLATE_BEGIN_ARGS(SMessagingTypesFilterBar)`
- L33 _public prototype_ `void Construct(const FArguments& InArgs, TSharedRef<FMessagingDebuggerTypeFilter> InFilter);` — Construct this widget. @param InArgs The declaration data for this widget. @param InFilter The filter model.
- L38 _private member_ `TSharedPtr<FMessagingDebuggerTypeFilter> Filter;` — Holds the filter model.

### `Plugins/Messaging/MessagingDebugger/Source/MessagingDebugger/Private/Widgets/Types/SMessagingTypesTableRow.h` (Private)


#### class `SMessagingTypesTableRow`  
`class SMessagingTypesTableRow : public SMultiColumnTableRow<TSharedPtr<FMessageTracerTypeInfo>>`  
_L19-59_
- inherits: `SMultiColumnTableRow<TSharedPtr<FMessageTracerTypeInfo>>`
- desc: Implements a row widget for the message type list.
- L24 _public function_ `SLATE_BEGIN_ARGS(SMessagingTypesTableRow)`
- L38 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, const TSharedRef<FMessagingDebuggerModel>& InModel);` — Constructs the widget. @param InArgs The construction arguments. @param InOwnerTableView The table view that owns this row.
- L44 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L49 _private member_ `TAttribute<FText> HighlightText;` — Holds the highlight string for the message.
- L52 _private member_ `TSharedPtr<FMessagingDebuggerModel> Model;` — Holds a pointer to the view model.
- L55 _private member_ `TSharedPtr<ISlateStyle> Style;` — Holds the widget's visual style.
- L58 _private member_ `TSharedPtr<FMessageTracerTypeInfo> TypeInfo;` — Holds message type's debug information.
