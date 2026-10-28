# Editor / PinnedCommandList

- module root: `Source/Editor/PinnedCommandList`
- headers: 5; symbols: 97
- symbol kinds: class=5, delegate=5, enum=1, enumerator=2, function=3, macro=1, member=27, prototype=50, struct=3
- PrivateDependencyModuleNames: ApplicationCore, Core, CoreUObject, InputCore, Slate, SlateCore

### `Source/Editor/PinnedCommandList/Private/PinnedCommandListSettings.h` (Private)


#### enum `EPinnedCommandListType`  
`enum class EPinnedCommandListType : uint8`  
_L9-16_
- reflection: `UENUM()`
- L12 _public enumerator_ `Command` — A simple command
- L15 _public enumerator_ `CustomWidget` — A registered custom widget

#### struct `FPinnedCommandListCommand`  
`struct FPinnedCommandListCommand`  
_L20-35_
- reflection: `USTRUCT()`
- desc: A command and its context
- L26 _public member_ `FName Name;` — `UPROPERTY(config)` — The name of the command
- L30 _public member_ `FName Binding;` — `UPROPERTY(config)` — The name of the command binding if this is a command
- L34 _public member_ `EPinnedCommandListType Type = EPinnedCommandListType::Command;` — `UPROPERTY(config)` — What type of command this is

#### struct `FPinnedCommandListContext`  
`struct FPinnedCommandListContext`  
_L39-50_
- reflection: `USTRUCT()`
- desc: A pinned command list context, allowing us to persist a set of pinned commands
- L45 _public member_ `FName Name;` — `UPROPERTY(config)` — The name of the context that this command list is displayed within
- L49 _public member_ `TArray<FPinnedCommandListCommand> Commands;` — `UPROPERTY(config)` — The commands to display

#### class `UPinnedCommandListSettings`  
`class UPinnedCommandListSettings : public UObject`  
_L54-62_
- reflection: `UCLASS(config=EditorPerProjectUserSettings)`
- inherits: `UObject`
- desc: A persistent set of pinned commands
- L61 _public member_ `TArray<FPinnedCommandListContext> Contexts;` — `UPROPERTY(config)` — Persistent pinned command contexts

### `Source/Editor/PinnedCommandList/Private/SPinnedCommandList.h` (Private)


#### struct `FRegisteredCustomWidget`  
`struct FRegisteredCustomWidget`  
_L27-43_
- desc: Tracks a registered custom widget, so it can be persisted
- L30 _public member_ `FName CustomWidgetIdentifier;` — Identifier for this custom widget
- L33 _public member_ `IPinnedCommandList::FOnGenerateCustomWidget OnGenerateCustomWidget;` — Widget creation delegate
- L36 _public member_ `TAttribute<FText> CustomWidgetDisplayName;` — Display name for this custom widget, used in context menus and tooltips
- L39 _public member_ `FMargin CustomWidgetPadding;` — Padding to use for this custom widget
- L42 _public member_ `bool bShowLabel;` — Whether to show the label for this custom widget

#### class `SPinnedCommandList`  
`class SPinnedCommandList : public IPinnedCommandList`  
_L48-155_
- inherits: `IPinnedCommandList`
- desc: A list of commands that were 'pinned' by the user, for easy re-use
- L52 _public prototype_ `DECLARE_DELEGATE( FOnCommandsChanged );` — Delegate for when commands have changed
- L54 _public prototype_ `DECLARE_DELEGATE_RetVal( TSharedPtr<SWidget>, FOnGetContextMenu );`
- L56 _public function_ `SLATE_BEGIN_ARGS( SPinnedCommandList )`
- L59 _public prototype_ `SLATE_EVENT( FOnGetContextMenu, OnGetContextMenu ) SLATE_EVENT( FOnCommandsChanged, OnCommandsChanged ) SLATE_END_ARGS() SPinnedCommandList();` — Called when a command is right clicked
- L67 _public prototype_ `~SPinnedCommandList();`
- L70 _public prototype_ `void Construct(const FArguments& InArgs, const FName& InContextName);` — Constructs this widget with InArgs
- L73 _public prototype_ `virtual void BindCommandList(const TSharedRef<const FUICommandList>& InUICommandList) override;` — IPinnedCommandList interface
- L74 _public prototype_ `virtual void BindCommandList(const TSharedRef<FUICommandList_Pinnable>& InUICommandList_Pinnable) override;`
- L75 _public prototype_ `virtual void RegisterCustomWidget(IPinnedCommandList::FOnGenerateCustomWidget InOnGenerateCustomWidget, FName InCustomWidgetIdentifier, TAttribute<FText> InCustomWidgetDisplayName, FMargin InCustomWidgetPadding = FMargin(2.0f, 1.0f), bool bShowLabel = true) override;`
- L76 _public prototype_ `virtual void AddCommand(const TSharedRef<const FUICommandInfo>& InCommandInfo, const TSharedRef<const FUICommandList>& InUICommandList) override;`
- L77 _public prototype_ `virtual void AddCustomWidget(FName InCustomWidgetIdentifier) override;`
- L78 _public prototype_ `virtual void RemoveCommand(const TSharedRef<const FUICommandInfo>& InCommandInfo) override;`
- L79 _public prototype_ `virtual void RemoveCustomWidget(FName InCustomWidgetIdentifier) override;`
- L80 _public prototype_ `virtual bool HasAnyCommands() const override;`
- L81 _public prototype_ `virtual void RemoveAllCommands() override;`
- L82 _public prototype_ `virtual void SetStyle(const ISlateStyle* InStyleSet, const FName& InStyleName) override;`
- L85 _public prototype_ `void SaveSettings() const;` — Saves any settings to config that should be persistent between editor sessions
- L88 _public prototype_ `void LoadSettings();` — Loads any settings to config that should be persistent between editor sessions
- L91 _public prototype_ `virtual FReply OnMouseButtonUp( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent );` — SWidget interface
- L96 _private prototype_ `TSharedRef<SCommand> AddCommand_Internal(const TSharedRef<const FUICommandInfo>& InCommandInfo, const TSharedRef<const FUICommandList>& InUICommandList, const TSharedPtr<const FUICommandList_Pinnable>& InUICommandListPinnable = nullptr);` — Adds a command and returns its widget. Creates a new widget if one does not already exist
- L99 _private prototype_ `TSharedPtr<SCommand> AddCustomWidget_Internal(FName InCustomWidgetIdentifier, const TSharedPtr<const FUICommandList_Pinnable>& InUICommandListPinnable = nullptr);` — Adds a custom widget and returns its widget. Creates a new widget if one does not already exist
- L102 _private prototype_ `void AddCommandWidget(const TSharedRef<SCommand>& CommandToAdd);` — Adds a command to the end of the pinned commands box.
- L105 _private prototype_ `void RemoveCommandWidget(const TSharedRef<SCommand>& CommandToRemove);` — Removes a command from the pinned commands box.
- L108 _private prototype_ `void OnResetCommands();` — Called when reset commands option is pressed
- L111 _private prototype_ `void RemoveAllCommandsButThis(const TSharedRef<SCommand>& CommandToRemove);` — Remove all commands but the one specified
- L114 _private prototype_ `void HandleExecuteAction(const TSharedRef<const FUICommandInfo>& InCommandInfo, const TSharedRef<const FUICommandList_Pinnable>& InUICommandList);` — Filter action execution
- L117 _private prototype_ `void HandleCustomWidgetInteraction(FName InCustomWidgetIdentifier, const TSharedRef<const FUICommandList_Pinnable>& InUICommandList);` — Filter custom widget interactions
- L120 _private prototype_ `void SortCommands();` — Sort commands
- L123 _private prototype_ `void RefreshCommandWidgets();` — Clear and re-add all widgets to slots
- L127 _private member_ `FName ContextName;` — Context name used to persist this widget's settings
- L130 _private member_ `TSharedPtr<SWrapBox> CommandBox;` — The horizontal box which contains all the commands
- L133 _private member_ `TArray<TSharedRef<SCommand>> Commands;` — All commands in the list
- L136 _private member_ `TArray<TWeakPtr<const FUICommandList>> BoundCommandLists;` — UI command lists that we can execute commands to (used to re-bind the UI on reload)
- L139 _private member_ `TArray<TWeakPtr<const FUICommandList_Pinnable>> BoundPinnableCommandLists;` — UI command lists that we can execute commands to (used to re-bind the UI on reload)
- L142 _private member_ `TArray<FRegisteredCustomWidget> CustomWidgets;` — Registered custom widgets
- L145 _private member_ `FOnGetContextMenu OnGetContextMenu;` — Delegate for getting the context menu.
- L148 _private member_ `FOnCommandsChanged OnCommandsChanged;` — Delegate for when commands have changed
- L151 _private member_ `const ISlateStyle* StyleSet;` — The slate style to use when constructing command widgets
- L154 _private member_ `FName StyleName;` — The menu style name to use when constructing command widgets

#### Free symbols / members of external scopes

- L52 _delegate_ `DECLARE_DELEGATE( FOnCommandsChanged );` — Delegate for when commands have changed
- L54 _delegate_ `DECLARE_DELEGATE_RetVal( TSharedPtr<SWidget>, FOnGetContextMenu );`

### `Source/Editor/PinnedCommandList/Public/IPinnedCommandList.h` (Public)


#### class `IPinnedCommandList`  
`class IPinnedCommandList : public SCompoundWidget`  
_L35-101_
- inherits: `SCompoundWidget`
- desc: A list of commands that were 'pinned' by the user, for easy re-use To use the a command list: 1. Construct it using CreatePinnedCommandList (using a valid context if you want to persist settings). Optionally call SetStyle after construction to style your widget for its context. Styles are the same concatenated named styles given to menu button items. 2. Bind one or more command lists to the widget via BindCommandList. This should be done *after* commands are registered to the FUICommandlist to allow commands to be correctly re-created from persistent settings. 3. Register one or more custom widgets via RegisterCustomWidget. 4. If using the FUICommandList_Pinnable, commands should be automatically forwarded to the pinned commands list widget when executed. If not, then the user needs to manually add commands via AddCommand. 5. If using FUICommandList_Pinnable custom widget interactions will be automatically forwarded to the pinned commands list, but FUICommandList_Pinnable::OnCustomWidgetInteraction *does* need to be called when widgets are interacted with to automatically add the custom widget to the pinned commands list.
- L39 _public prototype_ `DECLARE_DELEGATE_RetVal(TSharedRef<SWidget>, FOnGenerateCustomWidget);` — Delegate used to generate custom widgets
- L45 _public prototype_ `virtual void BindCommandList(const TSharedRef<const FUICommandList>& InUICommandList) = 0;` — Bind a command list to this widget. To persist the UI between sessions, register your command lists when this widget is constructed. @param	InUICommandList		The command list to bind
- L52 _public prototype_ `virtual void BindCommandList(const TSharedRef<FUICommandList_Pinnable>& InUICommandList) = 0;` — Bind a pinnable command list to this widget. As well as calling BindCommandList(), this also sets up delegates to forward commands and widget interactions to this command list. @param	InUICommandList		The command list to bind
- L62 _public prototype_ `virtual void RegisterCustomWidget(FOnGenerateCustomWidget InOnGenerateCustomWidget, FName InCustomWidgetIdentifier, TAttribute<FText> InCustomWidgetDisplayName, FMargin InCustomWidgetPadding = FMargin(2.0f, 1.0f), bool bInShowLabel = true) = 0;` — Register a custom widget. This allows the widget to be dynamically reconstructed according to the persisted commands. @param	InOnGenerateCustomWidget	Delegate used to regenerate the custom widget when created or loaded. @param	InCustomWidgetIdentifier	Unique identifier used to persist the widget. Matched to the parameter when calling AddCustomWidget. @param	InCustomWidgetDisplayName	Text to display next to the custom widget, and to generate tooltips for the widget. @param	InCustomWidgetPadding		Custom padding around the widget. @param	bInShowLabel				Whether to display the label in the pinned widget (it will still be used in the context menus)
- L69 _public prototype_ `virtual void AddCommand(const TSharedRef<const FUICommandInfo>& InUICommandInfo, const TSharedRef<const FUICommandList>& InUICommandList) = 0;` — Add a command to the pinned list. @param	InUICommandInfo		The command to add @param	InUICommandList		The command list that handles the command
- L75 _public prototype_ `virtual void AddCustomWidget(FName InCustomWidgetIdentifier) = 0;` — Add a previously registered custom widget to the pinned list. @see RegisterCustomWidget. @param	InCustomWidgetIdentifier	Unique identifier used to persist the widget.
- L81 _public prototype_ `virtual void RemoveCommand(const TSharedRef<const FUICommandInfo>& InUICommandInfo) = 0;` — Remove a command from the pinned list. @param	InUICommandInfo		The command to remove
- L87 _public prototype_ `virtual void RemoveCustomWidget(FName InCustomWidgetIdentifier) = 0;` — Remove a custom widget from the pinned list @param	InCustomWidgetIdentifier	Unique identifier used to persist the widget.
- L90 _public prototype_ `virtual bool HasAnyCommands() const = 0;` — @return true if any commands are assigned
- L93 _public prototype_ `virtual void RemoveAllCommands() = 0;` — Removes all commands in the list
- L100 _public prototype_ `virtual void SetStyle(const ISlateStyle* InStyleSet, const FName& InStyleName) = 0;` — Set a menu style to use when building command widgets. @param	InStyleSet		The style set to use, e.g. &FAppStyle::Get() @param	InStyleName		The name of the menu button style to use, e.g. "Menu"

#### Free symbols / members of external scopes

- L39 _delegate_ `DECLARE_DELEGATE_RetVal(TSharedRef<SWidget>, FOnGenerateCustomWidget);` — Delegate used to generate custom widgets

### `Source/Editor/PinnedCommandList/Public/IPinnedCommandListModule.h` (Public)


#### class `IPinnedCommandListModule`  
`class IPinnedCommandListModule : public IModuleInterface`  
_L10-19_
- inherits: `IModuleInterface`
- L18 _public prototype_ `virtual TSharedRef<IPinnedCommandList> CreatePinnedCommandList(const FName& InContextName) = 0;` — Create a pinned commands list widget @param	InContextName	The context name used to persist the widget's settings @return a new pinned commands widget

### `Source/Editor/PinnedCommandList/Public/UICommandList_Pinnable.h` (Public)


#### class `FUICommandList_Pinnable`  
`class FUICommandList_Pinnable : public FUICommandList`  
_L23-90_
- inherits: `FUICommandList`
- desc: Extended version of FUICommandList that allows: - Hooks into action dispatch, to allow commands to be forwarded for pinning - Indexing when mapping to provide a sort key - Optional grouping of actions
- L26 _public prototype_ `FUICommandList_Pinnable();`
- L31 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnExecuteAction, const TSharedRef<const FUICommandInfo>& , const TSharedRef<const FUICommandList_Pinnable>& );` — Delegate called when an action is executed
- L34 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCustomWidgetInteraction, FName , const TSharedRef<const FUICommandList_Pinnable>& );` — Delegate called when a custom widget is interacted with
- L37 _public prototype_ `virtual bool ExecuteAction(const TSharedRef< const FUICommandInfo > InUICommandInfo) const override;` — FUICommandList interface
- L38 _public prototype_ `virtual void MapAction( const TSharedPtr< const FUICommandInfo > InUICommandInfo, const FUIAction& InUIAction ) override;`
- L41 _public prototype_ `void WidgetInteraction(FName InCustomWidgetIdentifier) const;` — Mark that a custom widget was interacted with
- L44 _public function_ `FOnExecuteAction& OnExecuteAction()` — Delegate called when an action is executed
- L47 _public function_ `FOnCustomWidgetInteraction& OnCustomWidgetInteraction()` — Delegate called when an custom widget is interacted with
- L54 _public prototype_ `int32 GetMappedCommandIndex( FName InCommandName ) const;` — Get the index this command was mapped to. @param	InCommandName		The command name to check @return the mapped index, or INDEX_NONE if the command is not mapped to this command list
- L61 _public prototype_ `FName GetMappedCommandGroup( FName InCommandName ) const;` — Get the group this command was mapped into. @param	InUICommandInfo		The command to check @return the command's group, or NAME_None if the command is not grouped
- L67 _public prototype_ `void BeginGroup(FName InGroupName);` — Start a group scope. All calls to MapAction will be grouped into the specified group. Should be paired with EndGroup()
- L70 _public prototype_ `void EndGroup();` — End a group scope. Should be paired with BeginGroup().
- L74 _protected member_ `int32 CurrentActionIndex;` — Index used to provide a sort key for actions when mapped
- L77 _protected member_ `FName CurrentGroupName;` — Current group name
- L80 _protected member_ `FOnExecuteAction OnExecuteActionDelegate;` — Delegate called when an action is executed
- L83 _protected member_ `FOnCustomWidgetInteraction OnCustomWidgetInteractionDelegate;` — Delegate called when a custom widget is interacted with
- L86 _protected member_ `TMap<FName, int32> CommandIndexMap;` — Map providing an index for each command that was mapped via this command list
- L89 _protected member_ `TMap<FName, FName> CommandGroupMap;` — Map providing a group for each command that was mapped via this command list

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API PINNEDCOMMANDLIST_API`
- L31 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnExecuteAction, const TSharedRef<const FUICommandInfo>& , const TSharedRef<const FUICommandList_Pinnable>& );` — Delegate called when an action is executed
- L34 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCustomWidgetInteraction, FName , const TSharedRef<const FUICommandList_Pinnable>& );` — Delegate called when a custom widget is interacted with
