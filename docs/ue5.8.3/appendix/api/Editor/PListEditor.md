# Editor / PListEditor

- module root: `Source/Editor/PListEditor`
- headers: 8; symbols: 266
- symbol kinds: class=9, enum=2, enumerator=8, function=13, macro=1, member=66, prototype=166, struct=1
- DynamicallyLoadedModuleNames: MainFrame
- PrivateDependencyModuleNames: Core, CoreUObject, DesktopPlatform, InputCore, Slate, SlateCore, XmlParser
- PrivateIncludePathModuleNames: WorkspaceMenuStructure

### `Source/Editor/PListEditor/Private/PListNode.h` (Private)


#### enum `EPLNTypes`  
`enum EPLNTypes`  
_L21-32_
- desc: Represents the types of data that are supported by plist files.
- L23 _public enumerator_ `PLN_String`
- L24 _public enumerator_ `PLN_Boolean`
- L29 _public enumerator_ `PLN_File` — PLN_Real, PLN_Integer, PLN_Date, PLN_Data,
- L30 _public enumerator_ `PLN_Dictionary`
- L31 _public enumerator_ `PLN_Array`

#### class `IPListNode`  
`class IPListNode : public TSharedFromThis<IPListNode>`  
_L42-131_
- inherits: `TSharedFromThis<IPListNode>`
- desc: An interface to a PListNode that can be stored in an STreeView
- L45 _public function_ `IPListNode(SPListEditorPanel* InEditorWidget) : EditorWidget(InEditorWidget), Depth(-1)`
- L52 _public prototype_ `virtual ~IPListNode() = default;` — No base class creations
- L55 _public prototype_ `virtual bool IsValid() = 0;` — Validation check
- L58 _public prototype_ `virtual TArray<TSharedPtr<IPListNode> >& GetChildren() = 0;` — Returns the array of children. Note: the returned array is modifyable
- L61 _public prototype_ `virtual void AddChild(TSharedPtr<IPListNode> InChild) = 0;` — Adds a child to the internal array of the class
- L64 _public prototype_ `virtual EPLNTypes GetType() = 0;` — Gets the type of the node via enum
- L67 _public prototype_ `virtual bool UsesColumns() = 0;` — Determines whether the node needs to generate widgets for columns, or just use the whole row without columns
- L71 _public prototype_ `virtual TSharedRef<ITableRow> GenerateWidget(const TSharedRef<STableViewBase>& OwnerTable) = 0;` — Note: Uses the default expansion button but we want our own since default doesn't work with columns
- L74 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName, int32 Depth, ITableRow* RowPtr) = 0;` — Generates a widget for the specified column name
- L77 _public prototype_ `virtual FString ToXML(const int32 indent = 0, bool bOutputKey = true) = 0;` — Gets an XML representation of the node's internals
- L80 _public prototype_ `virtual void Refresh() = 0;` — Refreshes anything necessary in the node, such as a text used in information displaying
- L83 _public prototype_ `virtual int32 GetNumPairs() = 0;` — Calculate how many key/value pairs exist for this node.
- L86 _public prototype_ `virtual void OnFilterTextChanged(FString NewFilter) = 0;` — Called when the filter changes
- L89 _public prototype_ `virtual void SetIndex(int32 NewIndex) = 0;` — When parents are refreshed, they can set the index of their children for proper displaying
- L94 _public prototype_ `virtual void SetKey(FString NewKey);` — Sets the KeyString of the node, needed for telling children to set their keys. Default do nothing.
- L96 _public prototype_ `virtual void SetValue(FString NewValue);` — Sets the value of the node. Default do nothing
- L98 _public prototype_ `virtual void SetValue(bool bNewValue);` — Sets the value of the node. Default do nothing
- L100 _public prototype_ `virtual void SetArrayMember(bool bArrayMember);` — Sets a flag denoting whether the element is in an array. Default do nothing
- L102 _public prototype_ `virtual const FSlateBrush* GetOverlayBrush();` — Gets the overlay brush dynamically
- L107 _public prototype_ `static bool IsKeyStringValid(FString ToCheck);` — Checks if a key string is valid
- L109 _public prototype_ `static bool IsValueStringValid(FString ToCheck);` — Checks if a value string is valid
- L114 _public prototype_ `static const FSlateBrush* GetOverlayBrushDelegate(const TSharedRef<class IPListNode> In);` — Delegate: Gets the overlay brush from derived children classes
- L119 _public prototype_ `void SetDepth(int32 InDepth);` — Sets the depth of the node
- L121 _public prototype_ `int32 GetDepth();` — Gets the depth of the node
- L126 _protected member_ `SPListEditorPanel* EditorWidget;` — Pointer to the main editor widget for certain functionality, like marking it as dirty
- L130 _private member_ `int32 Depth;`

#### Free symbols / members of external scopes

- L35 _prototype_ `TSharedRef<ITableRow> GenerateInvalidRow(const TSharedRef<STableViewBase>& OwnerTable, const FText& ErrorMessage);` — A default function to return an invalid row widget
- L37 _prototype_ `TSharedRef<SWidget> GenerateInvalidRow(const FText& ErrorMessage);` — A default function to return an invalid row widget with columns
- L39 _prototype_ `FString GenerateTabString(int32 NumTabs);` — Helper function to generate an FString with the specified number of tabs

### `Source/Editor/PListEditor/Private/PListNodeArray.h` (Private)


#### class `FPListNodeArray`  
`class FPListNodeArray : public IPListNode`  
_L26-121_
- inherits: `IPListNode`
- desc: A Node representing an array
- L29 _public function_ `FPListNodeArray(SPListEditorPanel* InEditorWidget) : IPListNode(InEditorWidget), TableRow(nullptr), ArrayIndex(-1), bFiltered(false), bArrayMember(false), bKeyValid(false)`
- L36 _public prototype_ `virtual bool IsValid() override;` — Validation check
- L39 _public prototype_ `virtual TArray<TSharedPtr<IPListNode> >& GetChildren() override;` — Returns the array of children
- L42 _public prototype_ `virtual void AddChild(TSharedPtr<IPListNode> InChild) override;` — Adds a child to the internal array of the class
- L45 _public prototype_ `virtual EPLNTypes GetType() override;` — Gets the type of the node via enum
- L48 _public prototype_ `virtual bool UsesColumns() override;` — Determines whether the node needs to generate widgets for columns, or just use the whole row without columns
- L51 _public prototype_ `virtual TSharedRef<ITableRow> GenerateWidget(const TSharedRef<STableViewBase>& OwnerTable) override;` — Generates a widget for a TableView row
- L54 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName, int32 Depth, ITableRow* RowPtr) override;` — Generate a widget for the specified column name
- L57 _public prototype_ `virtual FString ToXML(const int32 indent = 0, bool bOutputKey = true) override;` — Gets an XML representation of the node's internals
- L60 _public prototype_ `virtual void Refresh() override;` — Refreshes anything necessary in the node, such as a text used in information displaying
- L63 _public prototype_ `virtual int32 GetNumPairs() override;` — Calculate how many key/value pairs exist for this node.
- L66 _public prototype_ `virtual void OnFilterTextChanged(FString NewFilter) override;` — Called when the filter changes
- L69 _public prototype_ `virtual void SetIndex(int32 NewIndex) override;` — When parents are refreshed, they can set the index of their children for proper displaying
- L74 _public prototype_ `const FSlateBrush* GetOverlayBrush() override;` — Gets the overlay brush to use
- L76 _public prototype_ `virtual void SetKey(FString NewString) override;` — Sets the KeyString of the node, needed for telling children to set their keys
- L78 _public prototype_ `virtual void SetArrayMember(bool bArrayMember) override;` — Sets a flag denoting whether the element is in an array. Default do nothing
- L82 _private prototype_ `void OnKeyStringChanged(const FText& NewString);` — Delegate: When key string changes
- L84 _private prototype_ `const FSlateBrush* GetExpanderImage() const;` — Delegate: Gets the image for the expander button
- L86 _private prototype_ `EVisibility GetExpanderVisibility() const;` — Delegate: Gets the visibility of the expander arrow
- L88 _private prototype_ `FReply OnArrowClicked();` — Delegate: Handles when the arrow is clicked
- L90 _private prototype_ `FSlateColor GetKeyBackgroundColor() const;` — Delegate: Changes the color of the key string text box based on validity
- L92 _private prototype_ `FSlateColor GetKeyForegroundColor() const;` — Delegate: Changes the color of the key string text box based on validity
- L97 _private member_ `TArray<TSharedPtr<IPListNode> > Children;` — All children of the array
- L100 _private member_ `FString KeyString;` — The string for the key
- L102 _private member_ `TSharedPtr<SEditableTextBox> KeyStringTextBox;` — The editable text box for the key string
- L105 _private member_ `TSharedPtr<STextBlock> InfoTextWidget;` — Info text widget for displaying num children
- L108 _private member_ `TSharedPtr<SButton> ExpanderArrow;` — Widget for the expander arrow
- L110 _private member_ `ITableRow* TableRow;` — Reference to the Containing Row
- L113 _private member_ `int32 ArrayIndex;` — Index within parent array. Ignored if not an array member
- L115 _private member_ `bool bFiltered;` — Whether it's filtered or not
- L117 _private member_ `bool bArrayMember;` — Whether an array member or not
- L120 _private member_ `bool bKeyValid;` — Flag for valid key string

### `Source/Editor/PListEditor/Private/PListNodeBoolean.h` (Private)


#### class `FPListNodeBoolean`  
`class FPListNodeBoolean : public IPListNode`  
_L25-113_
- inherits: `IPListNode`
- desc: A Node representing a boolean value
- L28 _public function_ `FPListNodeBoolean(SPListEditorPanel* InEditorWidget) : IPListNode(InEditorWidget), bValue(false), ArrayIndex(-1), bFiltered(false), bArrayMember(false), bKeyValid(false)`
- L35 _public prototype_ `virtual bool IsValid() override;` — Validation check
- L38 _public prototype_ `virtual TArray<TSharedPtr<IPListNode> >& GetChildren() override;` — Returns the array of children
- L41 _public prototype_ `virtual void AddChild(TSharedPtr<IPListNode> InChild) override;` — Adds a child to the internal array of the class
- L44 _public prototype_ `virtual EPLNTypes GetType() override;` — Gets the type of the node via enum
- L47 _public prototype_ `virtual bool UsesColumns() override;` — Determines whether the node needs to generate widgets for columns, or just use the whole row without columns
- L50 _public prototype_ `virtual TSharedRef<ITableRow> GenerateWidget(const TSharedRef<STableViewBase>& OwnerTable) override;` — Generates a widget for a TableView row
- L53 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName, int32 Depth, ITableRow* RowPtr) override;` — Generate a widget for the specified column name
- L56 _public prototype_ `virtual FString ToXML(const int32 indent = 0, bool bOutputKey = true) override;` — Gets an XML representation of the node's internals
- L59 _public prototype_ `virtual void Refresh() override;` — Refreshes anything necessary in the node, such as a text used in information displaying
- L62 _public prototype_ `virtual int32 GetNumPairs() override;` — Calculate how many key/value pairs exist for this node.
- L65 _public prototype_ `virtual void OnFilterTextChanged(FString NewFilter) override;` — Called when the filter changes
- L68 _public prototype_ `virtual void SetIndex(int32 NewIndex) override;` — When parents are refreshed, they can set the index of their children for proper displaying
- L73 _public prototype_ `const FSlateBrush* GetOverlayBrush() override;` — Gets the brush to use based on filter status
- L75 _public prototype_ `virtual void SetKey(FString NewString) override;` — Sets the KeyString of the node, needed for telling children to set their keys
- L77 _public prototype_ `virtual void SetValue(bool bNewValue) override;` — Sets the value of the boolean
- L79 _public prototype_ `virtual void SetArrayMember(bool bArrayMember) override;` — Sets a flag denoting whether the element is in an array
- L84 _private prototype_ `void OnKeyStringChanged(const FText& NewString);` — Delegate: When key string changes
- L86 _private prototype_ `void OnValueChanged(ECheckBoxState NewValue);` — Delegate: When the checkbox changes
- L88 _private prototype_ `FSlateColor GetKeyBackgroundColor() const;` — Delegate: Changes the color of the key string text box based on validity
- L90 _private prototype_ `FSlateColor GetKeyForegroundColor() const;` — Delegate: Changes the color of the key string text box based on validity
- L95 _private member_ `FString KeyString;` — The string for the key
- L97 _private member_ `TSharedPtr<SEditableTextBox> KeyStringTextBox;` — The editable text box for the key string
- L100 _private member_ `bool bValue;` — The value
- L102 _private member_ `TSharedPtr<SCheckBox> ValueCheckBox;` — The editable text box for the value string
- L105 _private member_ `int32 ArrayIndex;` — Index within parent array. Ignore if not an array member
- L107 _private member_ `bool bFiltered;` — Filtered flag
- L109 _private member_ `bool bArrayMember;` — Array flag
- L112 _private member_ `bool bKeyValid;` — Flag for valid key string

### `Source/Editor/PListEditor/Private/PListNodeDictionary.h` (Private)


#### class `FPListNodeDictionary`  
`class FPListNodeDictionary : public IPListNode`  
_L24-106_
- inherits: `IPListNode`
- desc: A Node representing a dictionary
- L27 _public function_ `FPListNodeDictionary(SPListEditorPanel* InEditorWidget) : IPListNode(InEditorWidget), TableRow(nullptr), ArrayIndex(-1), bArrayMember(false), bFiltered(false)`
- L34 _public prototype_ `virtual bool IsValid() override;` — Validation check
- L37 _public prototype_ `virtual TArray<TSharedPtr<IPListNode> >& GetChildren() override;` — Returns the array of children
- L40 _public prototype_ `virtual void AddChild(TSharedPtr<IPListNode> InChild) override;` — Adds a child to the internal array of the class
- L43 _public prototype_ `virtual EPLNTypes GetType() override;` — Gets the type of the node via enum
- L46 _public prototype_ `virtual bool UsesColumns() override;` — Determines whether the node needs to generate widgets for columns, or just use the whole row without columns
- L49 _public prototype_ `virtual TSharedRef<ITableRow> GenerateWidget(const TSharedRef<STableViewBase>& OwnerTable) override;` — Generates a widget for a TableView row
- L52 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName, int32 Depth, ITableRow* RowPtr) override;` — Generate a widget for the specified column name
- L55 _public prototype_ `virtual FString ToXML(const int32 indent = 0, bool bOutputKey = true) override;` — Gets an XML representation of the node's internals
- L58 _public prototype_ `virtual void Refresh() override;` — Refreshes anything necessary in the node, such as a text used in information displaying
- L61 _public prototype_ `virtual int32 GetNumPairs() override;` — Calculate how many key/value pairs exist for this node.
- L64 _public prototype_ `virtual void OnFilterTextChanged(FString NewFilter) override;` — Called when the filter changes
- L67 _public prototype_ `virtual void SetIndex(int32 NewIndex) override;` — When parents are refreshed, they can set the index of their children for proper displaying
- L72 _public prototype_ `virtual void SetArrayMember(bool bArrayMember) override;` — Sets a flag denoting whether the element is in an array. Default do nothing
- L74 _public prototype_ `virtual const FSlateBrush* GetOverlayBrush() override;` — Gets the overlay brush dynamically
- L79 _private prototype_ `const FSlateBrush* GetExpanderImage() const;` — Delegate: Gets the image for the expander button
- L81 _private prototype_ `EVisibility GetExpanderVisibility() const;` — Delegate: Gets the visibility of the expander arrow
- L83 _private prototype_ `FReply OnArrowClicked();` — Delegate: Handles when the arrow is clicked
- L88 _private member_ `TArray<TSharedPtr<IPListNode> > Children;` — All children of the dictionary
- L91 _private member_ `TSharedPtr<SEditableTextBox> KeyStringTextBox;` — The editable text box for the key string
- L93 _private member_ `TSharedPtr<STextBlock> InfoTextWidget;` — Info text widget for displaying num children
- L96 _private member_ `TSharedPtr<SButton> ExpanderArrow;` — Widget for the expander arrow
- L98 _private member_ `ITableRow* TableRow;` — Reference to the Containing Row
- L101 _private member_ `int32 ArrayIndex;` — Index within parent array. Ignore if not an array member
- L103 _private member_ `bool bArrayMember;` — Array Member Status
- L105 _private member_ `bool bFiltered;` — Filtered Status

### `Source/Editor/PListEditor/Private/PListNodeFile.h` (Private)


#### class `FPListNodeFile`  
`class FPListNodeFile : public IPListNode`  
_L19-70_
- inherits: `IPListNode`
- desc: A Node representing the plist as a whole
- L22 _public function_ `FPListNodeFile(SPListEditorPanel* InEditorWidget) : IPListNode(InEditorWidget)`
- L29 _public prototype_ `virtual bool IsValid() override;` — Validation check
- L32 _public prototype_ `virtual TArray<TSharedPtr<IPListNode> >& GetChildren() override;` — Returns the array of children
- L35 _public prototype_ `virtual void AddChild(TSharedPtr<IPListNode> InChild) override;` — Adds a child to the internal array of the class
- L38 _public prototype_ `virtual EPLNTypes GetType() override;` — Gets the type of the node via enum
- L41 _public prototype_ `virtual bool UsesColumns() override;` — Determines whether the node needs to generate widgets for columns, or just use the whole row without columns
- L44 _public prototype_ `virtual TSharedRef<ITableRow> GenerateWidget(const TSharedRef<STableViewBase>& OwnerTable) override;` — Generates a widget for a TableView row
- L47 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName, int32 Depth, ITableRow* RowPtr) override;` — Generate a widget for the specified column name
- L50 _public prototype_ `virtual FString ToXML(const int32 indent = 0, bool bOutputKey = true) override;` — Gets an XML representation of the node's internals
- L53 _public prototype_ `virtual void Refresh() override;` — Refreshes anything necessary in the node, such as a text used in information displaying
- L56 _public prototype_ `virtual int32 GetNumPairs() override;` — Calculate how many key/value pairs exist for this node.
- L59 _public prototype_ `virtual void OnFilterTextChanged(FString NewFilter) override;` — Called when the filter changes
- L62 _public prototype_ `virtual void SetIndex(int32 NewIndex) override;` — When parents are refreshed, they can set the index of their children for proper displaying
- L67 _private member_ `TArray<TSharedPtr<IPListNode> > Children;` — All children of the file (everything)
- L69 _private member_ `TSharedPtr<STextBlock> TextWidget;` — Widget for displaying text on this row

### `Source/Editor/PListEditor/Private/PListNodeString.h` (Private)


#### class `FPListNodeString`  
`class FPListNodeString : public IPListNode`  
_L22-116_
- inherits: `IPListNode`
- desc: A Node representing a string value
- L25 _public function_ `FPListNodeString(SPListEditorPanel* InEditorWidget) : IPListNode(InEditorWidget), ArrayIndex(-1), bFiltered(false), bArrayMember(false), bKeyValid(false), bValueValid(false)`
- L32 _public prototype_ `virtual bool IsValid() override;` — Validation check
- L35 _public prototype_ `virtual TArray<TSharedPtr<IPListNode> >& GetChildren() override;` — Returns the array of children
- L38 _public prototype_ `virtual void AddChild(TSharedPtr<IPListNode> InChild) override;` — Adds a child to the internal array of the class
- L41 _public prototype_ `virtual EPLNTypes GetType() override;` — Gets the type of the node via enum
- L44 _public prototype_ `virtual bool UsesColumns() override;` — Determines whether the node needs to generate widgets for columns, or just use the whole row without columns
- L47 _public prototype_ `virtual TSharedRef<ITableRow> GenerateWidget(const TSharedRef<STableViewBase>& OwnerTable) override;` — Generates a widget for a TableView row
- L50 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName, int32 Depth, ITableRow* RowPtr) override;` — Generate a widget for the specified column name
- L53 _public prototype_ `virtual FString ToXML(const int32 indent = 0, bool bOutputKey = true) override;` — Gets an XML representation of the node's internals
- L56 _public prototype_ `virtual void Refresh() override;` — Refreshes anything necessary in the node, such as a text used in information displaying
- L59 _public prototype_ `virtual int32 GetNumPairs() override;` — Calculate how many key/value pairs exist for this node.
- L62 _public prototype_ `virtual void OnFilterTextChanged(FString NewFilter) override;` — Called when the filter changes
- L65 _public prototype_ `virtual void SetIndex(int32 NewIndex) override;` — When parents are refreshed, they can set the index of their children for proper displaying
- L70 _public prototype_ `const FSlateBrush* GetOverlayBrush() override;` — Gets the brush to use based on filter status
- L72 _public prototype_ `virtual void SetKey(FString NewString) override;` — Sets the KeyString of the node, needed for telling children to set their keys
- L74 _public prototype_ `virtual void SetValue(FString NewValue) override;` — Sets the value of the boolean
- L76 _public prototype_ `virtual void SetArrayMember(bool bArrayMember) override;` — Sets a flag denoting whether the element is in an array
- L81 _private prototype_ `void OnKeyStringChanged(const FText& NewString);` — Delegate: When key string changes
- L83 _private prototype_ `void OnValueStringChanged(const FText& NewString);` — Delegate: When the value changes
- L85 _private prototype_ `FSlateColor GetKeyBackgroundColor() const;` — Delegate: Changes the color of the key string text box based on validity
- L87 _private prototype_ `FSlateColor GetKeyForegroundColor() const;` — Delegate: Changes the color of the key string text box based on validity
- L89 _private prototype_ `FSlateColor GetValueBackgroundColor() const;` — Delegate: Changes the color of the value string text box based on validity
- L91 _private prototype_ `FSlateColor GetValueForegroundColor() const;` — Delegate: Changes the color of the value string text box based on validity
- L96 _private member_ `FString KeyString;` — The string for the key
- L98 _private member_ `TSharedPtr<SEditableTextBox> KeyStringTextBox;` — The editable text box for the key string
- L101 _private member_ `FString ValueString;` — The value
- L103 _private member_ `TSharedPtr<SEditableTextBox> ValueStringTextBox;` — The editable text box for the value string
- L106 _private member_ `int32 ArrayIndex;` — Index withing parent array. Ignore if not an array member
- L108 _private member_ `bool bFiltered;` — Filtered flag
- L110 _private member_ `bool bArrayMember;` — Array flag
- L113 _private member_ `bool bKeyValid;` — Flag for valid key string
- L115 _private member_ `bool bValueValid;` — Flag for valid value string

### `Source/Editor/PListEditor/Public/PListEditor.h` (Public)


#### class `FPListEditor`  
`class FPListEditor : public IModuleInterface`  
_L11-28_
- inherits: `IModuleInterface`
- desc: Key binding editor module
- L18 _public prototype_ `virtual void StartupModule();` — Called right after the module DLL has been loaded and the module object has been created
- L23 _public prototype_ `virtual void ShutdownModule();` — Called before the module is unloaded, right before the module object is destroyed.

### `Source/Editor/PListEditor/Public/SPlistEditor.h` (Public)


#### enum `ENTF_Types`  
`enum ENTF_Types`  
_L55-60_
- desc: Type of notification to spawn
- L57 _public enumerator_ `NTF_Normal`
- L58 _public enumerator_ `NTF_Success`
- L59 _public enumerator_ `NTF_Fail`

#### struct `FQueuedNotification`  
`struct FQueuedNotification`  
_L63-92_
- desc: A queued notification for handling
- L68 _public function_ `FQueuedNotification(const FText& InNotif, const ENTF_Types InNotifType) : Notif(InNotif), NotifType(InNotifType)` — Constructs the queued notification
- L76 _public function_ `const FText Notification() const` — Retrieves the notification
- L81 _public function_ `const ENTF_Types NotificationType() const` — Retrieves the notification type
- L89 _private member_ `FText Notif;` — The stored notification
- L91 _private member_ `ENTF_Types NotifType;` — The stored notificaiton type

#### class `FPListEditorCommands`  
`class FPListEditorCommands : public TCommands<FPListEditorCommands>`  
_L95-143_
- inherits: `TCommands<FPListEditorCommands>`
- desc: Class for keybindings for the editor
- L100 _public function_ `FPListEditorCommands() : TCommands<FPListEditorCommands>("PListEditor", NSLOCTEXT("PListEditor", "PListEditor", "PList Editor"), NAME_None, FAppStyle::GetAppStyleSetName())` — Register Command group
- L106 _public member_ `TSharedPtr<FUICommandInfo> NewCommand;` — New Command
- L108 _public member_ `TSharedPtr<FUICommandInfo> OpenCommand;` — Open Command
- L110 _public member_ `TSharedPtr<FUICommandInfo> SaveCommand;` — Save Command
- L112 _public member_ `TSharedPtr<FUICommandInfo> SaveAsCommand;` — SaveAs Command
- L114 _public member_ `TSharedPtr<FUICommandInfo> DeleteSelectedCommand;` — DeleteSelected Command
- L116 _public member_ `TSharedPtr<FUICommandInfo> MoveUpCommand;` — Move Entry up in list command
- L118 _public member_ `TSharedPtr<FUICommandInfo> MoveDownCommand;` — Move Entry down in list command
- L120 _public member_ `TSharedPtr<FUICommandInfo> AddDictionaryCommand;` — Add Dictionary Command
- L122 _public member_ `TSharedPtr<FUICommandInfo> AddArrayCommand;` — Add Array Command
- L124 _public member_ `TSharedPtr<FUICommandInfo> AddStringCommand;` — Add String Command
- L126 _public member_ `TSharedPtr<FUICommandInfo> AddBooleanCommand;` — Add Boolean Command
- L129 _public function_ `virtual void RegisterCommands() override` — Initialize Commands

#### class `SPListEditorPanel`  
`class SPListEditorPanel : public SCompoundWidget`  
_L145-302_
- inherits: `SCompoundWidget`
- L148 _public function_ `SLATE_BEGIN_ARGS( SPListEditorPanel )`
- L153 _public function_ `SPListEditorPanel() : UICommandList(new FUICommandList())` — Constructor
- L159 _public prototype_ `virtual FReply OnKeyDown( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override;` — SWidget interface
- L160 _public prototype_ `virtual FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L164 _public prototype_ `void Construct( const FArguments& InArgs );` — Construct the widget when opened
- L167 _public prototype_ `bool OnTabClose();` — Handles when the tab is trying to be closed (prompt saving if necessary)
- L172 _private member_ `TArray<TSharedPtr<IPListNode> > PListNodes;` — An internal array holding parsed data from a loaded plist file
- L174 _private member_ `TSharedPtr<STreeView<TSharedPtr<IPListNode> > > InternalTree;` — The list widget, needed so we can request refreshes when we change the list's contents
- L177 _private member_ `TSharedPtr<SSearchBox> SearchBox;` — The search bar widget
- L180 _private member_ `TSharedPtr<SNotificationList> NotificationListPtr;` — The list of active system messages
- L182 _private member_ `TArray<FQueuedNotification> QueuedNotifications;` — A queue of notifications to display on subsequent frames
- L184 _private member_ `int32 FramesToSkip;` — How many frames to skip before trying to display a notification
- L187 _private member_ `TSharedPtr<SEditableText> FileNameWidget;` — The widget that shows the filename
- L189 _private member_ `FString InOutLastPath;` — The last loaded file
- L191 _private member_ `bool bFileLoaded;` — Whether or not a file is currently loaded. Also encompasses when a new file is created
- L193 _private member_ `bool bPromptSave;` — Whether or not to prompt a save before going through
- L195 _private member_ `bool bNewFile;` — Whether a new file is created that needs a save location
- L197 _private member_ `bool bDirty;` — Dirty flag: Anything has been touched in PListNodes
- L199 _private member_ `bool bPromptDelete;` — Flag on whether to prompt for deletions of not
- L202 _private member_ `TSharedRef<FUICommandList> UICommandList;` — The list of UI Commands executable
- L207 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow( TSharedPtr<IPListNode> InItem, const TSharedRef<STableViewBase>& OwnerTable );` — Delegate to generate a row for each member of the internal SList
- L209 _private prototype_ `void OnGetChildren(TSharedPtr<IPListNode> InItem, TArray<TSharedPtr<IPListNode> >& OutItems);` — Delegate to get the children of the stored items
- L214 _public prototype_ `void OnAddArray();` — Delegate to add a new array to the plist as a child of the selected node
- L216 _public prototype_ `void OnNew();` — Delegate for New ui command
- L218 _public prototype_ `FReply OnNewClicked();` — Delegate to create a new plist when the button is clicked
- L220 _public prototype_ `void OnOpen();` — Delegate for Open ui command
- L222 _public prototype_ `FReply OnOpenClicked();` — Delegate to open an existing plist when the button is clicked
- L224 _public prototype_ `void OnSave();` — Delegate for Save ui command
- L226 _public prototype_ `FReply OnSaveClicked();` — Delegate to save the working plist when the button is clicked
- L228 _public prototype_ `void OnSaveAs();` — Delegate for SaveAs ui command
- L230 _public prototype_ `FReply OnSaveAsClicked();` — Delegate to save the working plist with a specified name when the button is clicked
- L232 _public prototype_ `void OnDeleteSelected();` — Delegate for DeleteSelected ui command
- L234 _public prototype_ `void OnMoveUp();` — Delegate for MoveUp command
- L236 _public prototype_ `void OnMoveDown();` — Delegate for MoveDown command
- L238 _public prototype_ `void OnAddDictionary();` — Delegate for adding a dictionary
- L240 _public prototype_ `void OnAddString();` — Delegate for adding a string
- L242 _public prototype_ `void OnAddBoolean();` — Delegate for adding a boolean
- L244 _public prototype_ `void OnPopupTextChosen(const FString& ChosenText);` — Delegate to handle when a text option is chosen from right-click menu
- L247 _public prototype_ `TSharedPtr<SWidget> OnContextMenuOpen();` — Delegate to generate the context menu for the ListView
- L249 _public prototype_ `bool DetermineDeleteSelectedContext() const;` — Delegate that determines when the delete selected context button can be clicked
- L251 _public prototype_ `bool DetermineAddArrayContext() const;` — Delegate that determines when the AddArray button can be clicked in the context menu
- L253 _public prototype_ `bool DetermineMoveUpContext() const;` — Delegate for determining when MoveUp can be used
- L255 _public prototype_ `bool DetermineMoveDownContext() const;` — Delegate for determining when MoveDown can be used
- L257 _public prototype_ `bool DetermineAddDictionaryContext() const;` — Delegate for determining when AddDictionary can be used
- L259 _public prototype_ `bool DetermineAddStringContext() const;` — Delegate for determining when AddString can be used
- L261 _public prototype_ `bool DetermineAddBooleanContext() const;` — Delegate for determining when AddBoolean can be used
- L264 _public prototype_ `bool IsSearchBarEnabled() const;` — Delegate to check if the SearchBar is/should be enabled
- L266 _public prototype_ `void OnFilterTextChanged( const FText& InFilterText );` — Delegate to handle when the user changes filter text
- L271 _public prototype_ `void MarkDirty();` — Marks the widget as being dirty, forcing a prompt on saving before some actions
- L275 _private prototype_ `EActiveTimerReturnType DisplayDeferredNotifications( double InCurrentTime, float InDeltaTime );` — Displays queued notifications
- L277 _private prototype_ `void PerformDisplayNotifications();` — Helper method to display queued notifications
- L281 _private prototype_ `bool ParseXmlTree(FXmlFile& Doc, FString& OutError);` — Helper method to parse through and load an Xml tree into an internal intermediate format for Slate
- L283 _private prototype_ `void SerializePListNodes(FArchive* Writer);` — Helper method to write out the contents of PListNodes using a valid FileWriter
- L285 _private prototype_ `bool ValidatePListNodes();` — Helper function to check if PListNodes is valid (every element being valid)
- L287 _private prototype_ `void DisplayNotification(const FText& ToDisplay, const ENTF_Types NotificationType = NTF_Normal);` — Helper function to display notifications in the current tab
- L289 _private prototype_ `void ClearDirty();` — Clears the dirty flag, internal use only
- L291 _private prototype_ `bool PromptSave();` — Helper method to perform a save prompt. Returns true if the caller can pass the prompt and false if the caller should not continue its routine
- L293 _private prototype_ `bool PromptDelete();` — Helper method to prompt the user to delete element(s)
- L295 _private prototype_ `bool CheckFileExists(FString Path);` — Helper method to check if a file exists
- L297 _private prototype_ `bool OpenFile(FString FilePath);` — Helper function to open a file. Does not perform any checks before performing operation (such as bDirty)!!
- L299 _private prototype_ `void BindCommands();` — Helper method to bind commands
- L301 _private prototype_ `bool FindParent(const TSharedPtr<IPListNode>& InChildNode, TSharedPtr<IPListNode>& OutFoundNode) const;` — Helper function to search through nodes to find a specific node's parent

#### Free symbols / members of external scopes

- L48 _macro_ `#define LOCTEXT_NAMESPACE "PListEditorCommands"`
