# Plugins / SandboxedEditing

- module root: `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing`
- headers: 103; symbols: 1267
- symbol kinds: class=82, delegate=20, enum=11, enumerator=33, function=108, member=288, namespace=219, prototype=475, struct=18, typedef=4, variable=9
- PrivateDependencyModuleNames: AssetTools, ContentBrowser, DesktopPlatform, Engine, FileSandboxCore, FileSandboxUI, FileUtilities, InputCore, NamingTokens, Slate, SlateCore, SourceControl, ToolMenus, ToolWidgets, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/BrowserFeature.h` (Private)


#### class `UE::SandboxedEditing::FBrowserFeature`  
`class FBrowserFeature : public FNoncopyable`  
_L25-71_
- inherits: `FNoncopyable`
- desc: Summons a nomad tab through which the user can browse sandboxes.
- L33 _public prototype_ `explicit FBrowserFeature( const TSharedRef<FSandboxSystemModel>& InSandboxModel, const TSharedRef<FileSandboxUI::IExternalSandboxActiveViewModel>& InExternalSandboxViewModel );` — @param InSandboxModel Model that interacts with the core sandbox system. @param InExternalSandboxViewModel View model to let us know when an external sandbox is active.
- L37 _public prototype_ `~FBrowserFeature();`
- L40 _public prototype_ `void SummonUI() const;` — Summons the browser tab.
- L45 _private member_ `const TSharedRef<FSandboxSystemModel> SandboxModel;` — The shared sandbox model.
- L48 _private member_ `const FSandboxColumnRegistry SandboxColumns;` — The columns that are displayed in the browser.
- L50 _private member_ `const FFileStateColumnRegistry BrowserFileActionColumns;` — The columns displayed for the file actions in the browser UI.
- L52 _private member_ `const FFileStateColumnRegistry ActiveFileActionColumns;` — The columns displayed for the file actions in the active sandbox UI.
- L55 _private member_ `const FBrowserViewModels ViewModels;` — Holds all view models relevant for the browser.
- L57 _private member_ `const FBrowserViews Views;` — Holds all explicit views.
- L60 _private member_ `const TSharedRef<FBrowserCommandBindings> CommandBindings;` — Binds user commands to models.
- L62 _private prototype_ `explicit FBrowserFeature( const TSharedRef<FSandboxSystemModel>& InSandboxModel, const TSharedRef<FileSandboxUI::IExternalSandboxActiveViewModel>& InExternalSandboxViewModel, const TSharedRef<FSandboxControlsViewModel>& InControlsViewModel );`
- L68 _private prototype_ `void RegisterTabSpawner();`
- L69 _private prototype_ `void UnregisterTabSpawner();`
- L70 _private prototype_ `TSharedRef<SDockTab> SpawnBrowserTab(const FSpawnTabArgs& InArgs);`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/Commands/BrowserCommandBindings.h` (Private)


#### class `UE::SandboxedEditing::FBrowserCommandBindings`  
`class FBrowserCommandBindings : public FNoncopyable`  
_L18-49_
- inherits: `FNoncopyable`
- desc: Binds the commands relevant for the browser feature
- L22 _public prototype_ `explicit FBrowserCommandBindings(const FBrowserViewModels& InViewModels);`
- L24 _public function_ `const TSharedRef<FUICommandList>& GetCommandList() const`
- L29 _private member_ `const TSharedRef<FSandboxControlsViewModel> ControlsViewModel;` — Used for editing sandbox info.
- L31 _private member_ `const TSharedRef<FLeaveSandboxViewModel> LeaveSandboxViewModel;` — Used to interact with the active sandbox.
- L33 _private member_ `const TSharedRef<FPersistSandboxViewModel> PersistViewModel;` — Used to persist the sandbox.
- L36 _private member_ `const TSharedRef<FUICommandList> CommandList;` — Holds our command bindings
- L39 _private member_ `FSimpleMulticastDelegate OnDeleteSelection;` — Invoked when the delete command is issued.
- L42 _private prototype_ `void HandleCancel() const;` — Cancels any active operation, such as renaming or creating a sandbox.
- L44 _private prototype_ `void HandleLeaveSandbox();`
- L45 _private prototype_ `bool CanLeaveSandbox();`
- L47 _private prototype_ `void HandlePersistSandbox();`
- L48 _private prototype_ `bool CanPersistSandbox();`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/Commands/BrowserCommands.h` (Private)


#### class `UE::SandboxedEditing::FBrowserCommands`  
`class FBrowserCommands : public TCommands<FBrowserCommands>`  
_L10-35_
- inherits: `TCommands<FBrowserCommands>`
- desc: Commands used in the browser feature.
- L14 _public prototype_ `FBrowserCommands();`
- L17 _public prototype_ `virtual void RegisterCommands() override;`
- L21 _public member_ `TSharedPtr<FUICommandInfo> CreateNewSandbox;` — Starts the workflow for creating a new sandbox.
- L24 _public member_ `TSharedPtr<FUICommandInfo> Cancel;` — Cancel the current operation, such as renaming or creating a sandbox.
- L27 _public member_ `TSharedPtr<FUICommandInfo> LeaveSandbox;` — Leaves the current sandbox.
- L29 _public member_ `TSharedPtr<FUICommandInfo> PersistSandbox;` — Persists the current sandbox (without leaving).
- L32 _public member_ `TSharedPtr<FUICommandInfo> ExportSandboxes;` — Exports the sandboxes selected in the browser.
- L34 _public member_ `TSharedPtr<FUICommandInfo> ImportSandboxes;` — Imports sandboxes selected from the system explorer.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/Commands/FileStateActions/FileStateCommandBindings.h` (Private)


#### class `UE::SandboxedEditing::FFileStateCommandBindings`  
`class FFileStateCommandBindings : public FNoncopyable`  
_L22-53_
- inherits: `FNoncopyable`
- desc: Builds the right-click menu items displayed in all instances of SFileStateListView. Binds & unbinds the relevant commands required for that menu.
- L26 _public prototype_ `explicit FFileStateCommandBindings( TAttribute<TOptional<FString>> InSelectedSandboxRootAttr, TAttribute<TArray<FString>> InSelectedFilePathsAttr );`
- L31 _public prototype_ `void AppendMenu(FMenuBuilder& InMenuBuilder);` — Utility to append the commands to a menu builder.
- L36 _private member_ `const TSharedRef<FUICommandList> CommandList = MakeShared<FUICommandList>();` — The command list that our commands are bound to.
- L39 _private member_ `const TAttribute<TOptional<FString>> SelectedSandboxRootAttr;` — The sandbox root path on which the commands should be run.
- L41 _private member_ `const TAttribute<TArray<FString>> SelectedFilePathsAttr;` — Gets the items selected in the UI.
- L44 _private prototype_ `void BindCommands();` — Binds the commands needed for the menu.
- L46 _private prototype_ `void HandleBrowseToAsset() const;`
- L47 _private prototype_ `bool CanBrowseToAsset() const;`
- L49 _private prototype_ `void HandleShowRootInExplorer() const;`
- L51 _private prototype_ `void HandleShowFileInExplorer() const;`
- L52 _private prototype_ `bool CanShowFileInExplorer() const;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/Commands/FileStateActions/FileStateCommands.h` (Private)


#### class `UE::SandboxedEditing::FFileStateCommands`  
`class FFileStateCommands : public TCommands<FFileStateCommands>`  
_L10-29_
- inherits: `TCommands<FFileStateCommands>`
- desc: Commands used for actions performed on sandboxed files (usually on selected items in SFileStateListView).
- L14 _public prototype_ `FFileStateCommands();`
- L17 _public prototype_ `virtual void RegisterCommands() override;`
- L21 _public member_ `TSharedPtr<FUICommandInfo> BrowseToAsset;` — Opens the content browser to this file
- L23 _public member_ `TSharedPtr<FUICommandInfo> ShowRootInExplorer;` — Shows sandbox root directory in the system file explorer.
- L25 _public member_ `TSharedPtr<FUICommandInfo> ShowFileInExplorer;` — Shows the file's sandboxed counterpart in the system file explorer.
- L28 _public member_ `TSharedPtr<FUICommandInfo> PersistSelected;` — Persists the selected files.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/ViewModels/Active/ActiveSandboxDetailsViewModel.h` (Private)


#### class `UE::SandboxedEditing::FActiveSandboxDetailsViewModel`  
`class FActiveSandboxDetailsViewModel : public FNoncopyable`  
_L15-41_
- inherits: `FNoncopyable`
- desc: Information about the active sandbox.
- L19 _public prototype_ `explicit FActiveSandboxDetailsViewModel( const TSharedRef<FSandboxSystemModel>& InModel, const TSharedRef<FLeaveSandboxViewModel>& InLeaveSandboxViewModel );`
- L25 _public prototype_ `void LeaveSandbox();` — Leaves the active sandbox.
- L27 _public prototype_ `bool CanLeaveSandbox(FText* OutReason = nullptr) const;` — @return Whether the sandbox can be left
- L30 _public prototype_ `FString GetSandboxName() const;` — @return Name of the active sandbox.
- L32 _public prototype_ `FString GetSandboxPath() const;` — @return Path to active sandbox root.
- L37 _private member_ `const TSharedRef<FSandboxSystemModel> Model;` — The model used to interact with the sandbox system.
- L40 _private member_ `const TSharedRef<FLeaveSandboxViewModel> LeaveSandboxViewModel;` — Handles leave logic.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/ViewModels/Active/ActiveSandboxTrackerViewModel.h` (Private)


#### class `UE::SandboxedEditing::FActiveSandboxTrackerViewModel`  
`class FActiveSandboxTrackerViewModel : public FNoncopyable`  
_L15-44_
- inherits: `FNoncopyable`
- desc: Knows when the active sandbox changes.
- L19 _public prototype_ `explicit FActiveSandboxTrackerViewModel(const TSharedRef<FSandboxSystemModel>& InModel);`
- L20 _public prototype_ `~FActiveSandboxTrackerViewModel();`
- L23 _public prototype_ `bool HasActiveSandbox() const;` — @return Whether there is an active sandbox
- L26 _public function_ `FSimpleMulticastDelegate& OnLoadSandbox()` — Invoked when the engine has entered an active sandbox.
- L28 _public function_ `FSimpleMulticastDelegate& OnLeaveSandbox()` — Invoked when the active has stopped being in an active sandbox.
- L33 _private member_ `const TSharedRef<FSandboxSystemModel> Model;` — The model used to interact with the sandbox system.
- L36 _private member_ `FSimpleMulticastDelegate OnLoadSandboxDelegate;` — Invoked when a new sandbox is loaded.
- L38 _private member_ `FSimpleMulticastDelegate OnLeaveSandboxDelegate;` — Invoked when the current sandbox is left.
- L41 _private prototype_ `void HandleSandboxedLoaded();` — Creates the view model and invokes OnLoadSandboxDelegate.
- L43 _private prototype_ `void HandleSandboxLeft();` — Cleans up the view model and invokes OnLeaveSandboxDelegate.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/ViewModels/BrowserViewModels.h` (Private)


#### struct `UE::SandboxedEditing::FBrowserViewModels`  
`struct FBrowserViewModels`  
_L27-88_
- desc: Holds all view models used by the root UI. Make sharing view models easier.
- L30 _public member_ `const TSharedRef<FFilterSandboxViewModel> FilterSandboxViewModel;` — Knows how to filter sandbox items.
- L32 _public member_ `const TSharedRef<FSandboxListViewModel> ListViewModel;` — Knows about the items that are displayed in the browser.
- L36 _public member_ `const TSharedRef<FFilterFileStateViewModel> FilterUnloadedSandboxFileStateViewModel;` — The filters for UnloadedSandboxFileStateViewModel
- L38 _public member_ `const TSharedRef<FUnloadedSandboxFileStateViewModel> UnloadedSandboxFileStateViewModel;` — Knows the file action of the currently selected sandbox.
- L41 _public member_ `const TSharedRef<FFilterFileStateViewModel> FilterActiveSandboxFileStateViewModel;` — The filters for ActiveSandboxFileStateViewModel
- L43 _public member_ `const TSharedRef<FActiveSandboxFileStateViewModel> ActiveSandboxFileStateViewModel;` — Knows the file actions of the active sandbox.
- L47 _public member_ `const TSharedRef<FSandboxControlsViewModel> ControlsViewModel;` — Handles actions that the user performs on the sandboxes via the UI.
- L49 _public member_ `const TSharedRef<FSandboxMetaDataViewModel> MetaDataViewModel;` — Handles changing metadata of a sandbox.
- L53 _public member_ `const TSharedRef<FPersistSandboxViewModel> PersistViewModel;` — Handles persisting the active sandbox.
- L55 _public member_ `const TSharedRef<FLeaveSandboxViewModel> LeaveViewModel;` — Handles leaving an active sandbox.
- L59 _public member_ `const TSharedRef<FActiveSandboxTrackerViewModel> ActiveSandboxTrackerViewModel;` — Used for widgets to switch states when the active sandbox changes.
- L61 _public member_ `const TSharedRef<FActiveSandboxDetailsViewModel> ActiveSandboxDetailsViewModel;` — Used for widgets that display info about the currently active sandbox.
- L63 _public member_ `const TSharedRef<FileSandboxUI::IExternalSandboxActiveViewModel> ExternalSandboxViewModel;` — Knows about when an extern sandbox is being displayed.
- L66 _public function_ `explicit FBrowserViewModels( const FSandboxColumnRegistry& InSandboxColumns, const FFileStateColumnRegistry& InBrowserFileActionColumns, const FFileStateColumnRegistry& InActiveFileActionColumns, const TSharedRef<FSandboxSystemModel>& InModel, const TSharedRef<FileSandboxUI::IExternalSandboxActiveViewModel>& InExternalSandboxViewModel, const TSharedRef<FSandboxControlsViewModel>& InControlsViewModel ) : FilterSandboxViewModel(MakeShared<FFilterSandboxViewModel>(InSandboxColumns.GetBehaviorArray())) , ListViewModel(MakeShared<FSandboxListViewModel>(InModel, FilterSandboxViewModel, InSandboxColumns.ColumnBehaviors)) , FilterUnloadedSandboxFileStateViewModel(MakeShared<FFilterFileStateViewModel>(InBrowserFileActionColumns.ToBehaviorArray())) , UnloadedSandboxFileStateViewModel(MakeShared<FUnloadedSandboxFileStateViewModel>(InModel, FilterUnloadedSandboxFileStateViewModel, InBrowserFileActionColumns.ColumnBehaviors)) , FilterActiveSandboxFileStateViewModel(MakeShared<FFilterFileStateViewModel>(InActiveFileActionColumns.ToBehaviorArray())) , ActiveSandboxFileStateViewModel(MakeShared<FActiveSandboxFileStateViewModel>(InModel, FilterActiveSandboxFileStateViewModel, InActiveFileActionColumns.ColumnBehaviors)) , ControlsViewModel(InControlsViewModel) , MetaDataViewModel(MakeShared<FSandboxMetaDataViewModel>(InModel)) , PersistViewModel(MakeShared<FPersistSandboxViewModel>(InModel)) , LeaveViewModel(MakeShared<FLeaveSandboxViewModel>(InModel, PersistViewModel)) , ActiveSandboxTrackerV ...`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace FileSandboxUI` (scope `UE`)
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/ViewModels/Columns/ISearchableColumnBehavior.h` (Private)


#### class `UE::SandboxedEditing::ISearchableColumnBehavior`  
`template<typename TRowData> class ISearchableColumnBehavior`  
_L11-19_
- desc: Interface for a column that can be searched
- L16 _public prototype_ `virtual void PopulateSearchTerms(const TRowData& InRowData, TArray<FString>& OutSearchTerms) const = 0;` — Search terms for this column
- L18 _public prototype_ `virtual ~ISearchableColumnBehavior() = default;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/ViewModels/Columns/ISortableColumnBehavior.h` (Private)


#### class `UE::SandboxedEditing::ISortableColumnBehavior`  
`template<typename TRowData> class ISortableColumnBehavior`  
_L11-28_
- desc: Interface for a column that can be sorted
- L16 _public prototype_ `virtual bool CanSort() const = 0;` — @return Whether this column supports sorting
- L25 _public prototype_ `virtual bool SortBy(const TRowData& Lhs, const TRowData& Rhs, EColumnSortMode::Type SortMode) const = 0;` — Compares two row items for sorting. @param Lhs The left-hand side item @param Rhs The right-hand side item @param SortMode The sort mode (Ascending or Descending) @return true if Lhs should come before Rhs, false otherwise
- L27 _public prototype_ `virtual ~ISortableColumnBehavior() = default;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/ViewModels/FileState/FileStateColumnRegistry.h` (Private)


#### struct `UE::SandboxedEditing::FFileStateColumnRegistry`  
`struct FFileStateColumnRegistry`  
_L14-28_
- L17 _public member_ `TMap<FName, TSharedRef<IFileStateColumnBehavior>> ColumnBehaviors;` — The behavior of the columns for view models.
- L20 _public member_ `TMap<FName, TSharedRef<IFileStateColumnWidgetFactory>> ColumnFactories;` — Creates the widgets for the columns.
- L22 _public function_ `TArray<TSharedRef<IFileStateColumnBehavior>> ToBehaviorArray() const`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SandboxedEditing` (scope `UE`)
- L31 _prototype_ `FFileStateColumnRegistry GetColumnsForBrowser();` (scope `UE::SandboxedEditing`) — @return Columns to show in the browser view.
- L34 _prototype_ `FFileStateColumnRegistry GetColumnsForActiveSandbox();` (scope `UE::SandboxedEditing`) — @return Columns to show in the active sandbox view.
- L37 _prototype_ `FFileStateColumnRegistry GetColumnsForPersist(const TSharedRef<FPersistOperationViewModel>& InViewModel);` (scope `UE::SandboxedEditing`) — @return Columns to show in the persist view.

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/ViewModels/FileState/FileStateColumns.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SandboxedEditing` (scope `UE`)
- L15 _typedef_ `using FFileStateColumnFactoryMap = TMap<FName, TSharedRef<IFileStateColumnWidgetFactory>>;` (scope `UE::SandboxedEditing`) — Needed for SLATE_ARGUMENT (the macro is written in such a way that TMap is not parsed correctly).
- L17 _variable_ `constexpr FLazyName PersistCheckboxColumn(TEXT("Pers` (scope `UE::SandboxedEditing`)
- L18 _variable_ `constexpr FLazyName FileActionColumn(TEXT("File` (scope `UE::SandboxedEditing`)
- L19 _variable_ `constexpr FLazyName FilePathColumn(TEXT("File` (scope `UE::SandboxedEditing`)
- L20 _variable_ `constexpr FLazyName FileTimestampColumn(TEXT("File` (scope `UE::SandboxedEditing`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/ViewModels/FileState/FileStateItem.h` (Private)


#### struct `UE::SandboxedEditing::FFileStateItem`  
`struct FFileStateItem`  
_L12-31_
- desc: Represents an item displayed in IFileStateViewModel.
- L15 _public member_ `FString NonSandboxFile;` — Path to the non-sandboxed file.
- L18 _public member_ `FileSandboxCore::ESandboxFileChange Action;` — The operation performed on the file.
- L21 _public member_ `FDateTime Timestamp;` — The time of the edit
- L23 _public function_ `explicit FFileStateItem(FString InNonSandboxFile, FileSandboxCore::ESandboxFileChange InAction, const FDateTime& InTimestamp) : NonSandboxFile(MoveTemp(InNonSandboxFile)) , Action(InAction) , Timestamp(InTimestamp)`
- L30 _public function_ `bool HasValidTimestamp() const` — @return Whether the timestamp is valid. FileSandboxCore API returns FDateTime::MinValue for invalid timestamps.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/ViewModels/FileState/FileStateItemUtils.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace FileSandboxCore` (scope `UE`)
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SandboxedEditing` (scope `UE`)
- L15 _prototype_ `TArray<TSharedPtr<FFileStateItem>> MakeItemsFromFileChanges(const FileSandboxCore::FGatheredFileChanges& InChanges);` (scope `UE::SandboxedEditing`) — @return An item array transformed from FGatheredFileChanges

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/ViewModels/FileState/FilterFileStateViewModel.h` (Private)


#### class `UE::SandboxedEditing::FFilterFileStateViewModel`  
`class FFilterFileStateViewModel : public FNoncopyable`  
_L16-50_
- inherits: `FNoncopyable`
- desc: Knows of all filters for filtering file state items.
- L18 _private typedef_ `using FFileActionTextFilter = TTextFilter<const TSharedRef<FFileStateItem>&>;`
- L21 _public prototype_ `explicit FFilterFileStateViewModel(TAttribute<TArray<TSharedRef<IFileStateColumnBehavior>>> InVisibleColumns);`
- L24 _public prototype_ `FText GetSearchText() const;` — @return Current search text
- L26 _public prototype_ `void SetSearchText(const FText& InSearchText);` — Sets the search text. Will trigger a refilter.
- L29 _public prototype_ `bool PassesFilter(const TSharedRef<FFileStateItem>& InItem) const;` — @return Whether the item can be displayed.
- L32 _public prototype_ `bool AreAnyFiltersActive() const;` — @return Whether any filters are active.
- L35 _public function_ `FSimpleMulticastDelegate& OnFilterChanged()` — @return Delegate invoked when any of the filters changes
- L40 _private member_ `const TAttribute<TArray<TSharedRef<IFileStateColumnBehavior>>> VisibleColumns;` — Visible columns. Used for filtering visible columns by text.
- L43 _private member_ `FFileActionTextFilter TextFilter;` — Does text filltering on items
- L46 _private member_ `FSimpleMulticastDelegate OnFilterChangedDelegate;` — Invoked when any of the filters changes
- L49 _private prototype_ `void ItemToString(const TSharedRef<FFileStateItem>& InItem, TArray<FString>& OutSearchTerms);` — Converts an item to string.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/ViewModels/FileState/IFileStateColumnBehavior.h` (Private)


#### class `UE::SandboxedEditing::IFileStateColumnBehavior`  
`class IFileStateColumnBehavior : public ISearchableColumnBehavior<TSharedPtr<FFileStateItem>> , public ISortableColumnBehavior<TSharedPtr<FFileStateItem>>`  
_L17-20_
- inherits: `ISearchableColumnBehavior<TSharedPtr<FFileStateItem>>,ISortableColumnBehavior<TSharedPtr<FFileStateItem>>`
- desc: View-model logic that is implemented by columns. Supports both searching and sorting.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/ViewModels/FileState/IFileStateColumnWidgetFactory.h` (Private)


#### struct `UE::SandboxedEditing::FMakeFileStateColumnWidgetArgs`  
`struct FMakeFileStateColumnWidgetArgs`  
_L12-24_
- desc: Args for making a column widget in a row.
- L15 _public member_ `TSharedPtr<FFileStateItem> RowData;` — The row data for this column widget
- L18 _public member_ `TAttribute<FText> HighlightText;` — The (search) text to highlight in widgets.
- L20 _public function_ `explicit FMakeFileStateColumnWidgetArgs(TSharedPtr<FFileStateItem> InRowData, TAttribute<FText> InHighlightText) : RowData(MoveTemp(InRowData)) , HighlightText(MoveTemp(InHighlightText))`

#### class `UE::SandboxedEditing::IFileStateColumnWidgetFactory`  
`class IFileStateColumnWidgetFactory`  
_L27-38_
- desc: Interface for creating Slate widgets for a column.
- L32 _public prototype_ `virtual SHeaderRow::FColumn::FArguments MakeColumnArguments() = 0;` — @return Info required to construct the column.
- L35 _public prototype_ `virtual TSharedRef<SWidget> MakeColumnWidget(const FMakeFileStateColumnWidgetArgs& InArgs) = 0;` — @return Widget that should be put into the row for this column
- L37 _public prototype_ `virtual ~IFileStateColumnWidgetFactory() = default;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/ViewModels/FileState/IFileStateViewModel.h` (Private)


#### class `UE::SandboxedEditing::IFileStateViewModel`  
`class IFileStateViewModel`  
_L19-60_
- desc: View model for UI that shows the files added / removed / edited in the sandbox. The implementation can vary based on where the UI is displayed, e.g. - Persist files (part of workflow for leaving sandbox) - Sandbox changed files (part of UI for displaying current sandbox details)
- L24 _public prototype_ `virtual const TArray<TSharedPtr<FFileStateItem>>& GetItems() const = 0;` — @return The items to display
- L27 _public prototype_ `virtual TArray<FName> GetDisplayedColumns() const = 0;` — @return The columns that should be displayed.
- L30 _public prototype_ `virtual FSimpleMulticastDelegate& OnItemsChanged() = 0;` — Invoked when the items change.
- L39 _public prototype_ `virtual EColumnSortMode::Type GetColumnSortMode(const FName ColumnId) const = 0;` — Returns the current column sort mode (ascending or descending) if the ColumnId parameter matches the current column to be sorted by, otherwise returns EColumnSortMode::None. @param ColumnId Column ID to query sort mode for. @return The sort mode for the column, or EColumnSortMode::None if it is not known.
- L48 _public prototype_ `virtual EColumnSortPriority::Type GetColumnSortPriority(const FName ColumnId) const = 0;` — Returns the current column sort priority (primary or secondary) if the ColumnId parameter matches a sorted column, otherwise returns EColumnSortPriority::Max. @param ColumnId Column ID to query sort priority for. @return The sort priority for the column, or EColumnSortPriority::Max if it is not sorted.
- L57 _public prototype_ `virtual void OnColumnSortModeChanged(const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type InSortMode) = 0;` — Callback for SHeaderRow::Column::OnSort, called when the column to sort by is changed. @param SortPriority The sort priority (Primary or Secondary) @param ColumnId The column to sort by @param InSortMode The sort mode (ascending or descending)
- L59 _public prototype_ `virtual ~IFileStateViewModel() = default;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/ViewModels/FileState/Models/ActiveSandboxFileStateViewModel.h` (Private)


#### class `UE::SandboxedEditing::FActiveSandboxFileStateViewModel`  
`class FActiveSandboxFileStateViewModel : public FStaticFileStateViewModel`  
_L12-33_
- inherits: `FStaticFileStateViewModel`
- desc: Refreshes the file states of the active sandbox.
- L16 _public prototype_ `explicit FActiveSandboxFileStateViewModel( const TSharedRef<FSandboxSystemModel>& InModel, const TSharedRef<FFilterFileStateViewModel>& InFilterViewModel, TMap<FName, TSharedRef<IFileStateColumnBehavior>> InColumns );`
- L21 _public prototype_ `~FActiveSandboxFileStateViewModel();`
- L26 _private member_ `TSharedPtr<FSandboxSystemModel> Model;` — Used to get the file states from the active sandbox.
- L29 _private prototype_ `void RefreshItems();` — Refreshes the items from the active sandbox.
- L31 _private prototype_ `void OnSandboxLoaded();`
- L32 _private prototype_ `void OnSandboxLeft();`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/ViewModels/FileState/Models/StaticFileStateViewModel.h` (Private)


#### class `UE::SandboxedEditing::FStaticFileStateViewModel`  
`class FStaticFileStateViewModel : public IFileStateViewModel`  
_L20-79_
- inherits: `IFileStateViewModel`
- desc: Initialized with items at construction. The item array is not directly mutated by this class (TODO except for sorting columns). Subclasses may mutate the item array. This can serve as a base implementation for more dynamic models.
- L24 _public prototype_ `explicit FStaticFileStateViewModel( TMap<FName, TSharedRef<IFileStateColumnBehavior>> InColumns, TArray<TSharedPtr<FFileStateItem>> InItems = {}, TSharedPtr<FFilterFileStateViewModel> InFilterViewModel = nullptr );`
- L32 _public function_ `virtual const TArray<TSharedPtr<FFileStateItem>>& GetItems() const override`
- L33 _public prototype_ `virtual TArray<FName> GetDisplayedColumns() const override;`
- L34 _public function_ `virtual FSimpleMulticastDelegate& OnItemsChanged() override`
- L35 _public prototype_ `virtual EColumnSortMode::Type GetColumnSortMode(const FName ColumnId) const override;`
- L36 _public prototype_ `virtual EColumnSortPriority::Type GetColumnSortPriority(const FName ColumnId) const override;`
- L37 _public prototype_ `virtual void OnColumnSortModeChanged(const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type InSortMode) override;`
- L43 _protected member_ `const TMap<FName, TSharedRef<IFileStateColumnBehavior>> Columns;` — All columns that can ever be displayed.
- L46 _protected member_ `const TSharedPtr<FFilterFileStateViewModel> FilterViewModel;` — Optional filter model.
- L49 _protected member_ `TArray<TSharedPtr<FFileStateItem>> AllUnfilteredItems;` — The items to display.
- L52 _protected prototype_ `void NotifyItemsChanged();` — Called by subclasses when they have changed AllUnfilteredItems.
- L57 _private member_ `FSimpleMulticastDelegate OnItemsChangedDelegate;` — Invoked when items or sorting changes.
- L60 _private member_ `TArray<TSharedPtr<FFileStateItem>> FilteredItems;` — A filtered version of AllUnfilteredItems.
- L63 _private member_ `FName PrimarySortedColumn;` — Sorting state
- L64 _private member_ `EColumnSortMode::Type PrimarySortMode = EColumnSortMode::None;`
- L65 _private member_ `FName SecondarySortedColumn;`
- L66 _private member_ `EColumnSortMode::Type SecondarySortMode = EColumnSortMode::None;`
- L69 _private prototype_ `void FilterItems();` — Refilters the items.
- L75 _private prototype_ `void RequestSort();` — Requests that the items be sorted according to the current sort column and mode. Refreshes the list after sorting.
- L78 _private prototype_ `void SortItems();` — Sorts the items according to the current sort column and mode.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/ViewModels/FileState/Models/UnloadedSandboxFileStateViewModel.h` (Private)


#### class `UE::SandboxedEditing::FUnloadedSandboxFileStateViewModel`  
`class FUnloadedSandboxFileStateViewModel : public FStaticFileStateViewModel`  
_L14-41_
- inherits: `FStaticFileStateViewModel`
- desc: View model for displaying the file changes of an unloaded sandbox, i.e. when the engine is not sandboxed. Used to display info about a sandbox in the browser.
- L18 _public prototype_ `explicit FUnloadedSandboxFileStateViewModel( const TSharedRef<FSandboxSystemModel>& InModel, const TSharedRef<FFilterFileStateViewModel>& InFilterViewModel, const TMap<FName, TSharedRef<IFileStateColumnBehavior>>& InColumns );`
- L23 _public prototype_ `~FUnloadedSandboxFileStateViewModel();`
- L26 _public prototype_ `void SetContent(const FString& InSandboxRoot);` — Sets the content to be that of the specified sandbox.
- L29 _public prototype_ `void ClearContent();` — Clears the content.
- L34 _private member_ `const TSharedRef<FSandboxSystemModel> Model;` — The model through which we interact with the sandbox system.
- L37 _private member_ `TOptional<FString> SelectedSandbox;` — The sandbox being viewed.
- L40 _private prototype_ `void OnSandboxLeft();` — Refreshes the content, in case the active sandbox changed files.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/ViewModels/Leaving/AskUserAboutDirtyPackagesWorkflow.h` (Private)


#### class `UE::SandboxedEditing::FAskUserAboutDirtyPackagesWorkflow`  
`class FAskUserAboutDirtyPackagesWorkflow : public FNoncopyable`  
_L13-46_
- inherits: `FNoncopyable`
- desc: Workflow for asking the user what to do about dirty packages, i.e. when leaving the sandbox.
- L18 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnCleanupWorkflow, EWorkflowResult) DECLARE_MULTICAST_DELEGATE_OneParam(FOnEndWorkflow, EWorkflowResult) explicit FAskUserAboutDirtyPackagesWorkflow(const TSharedRef<FSandboxSystemModel>& InSandboxModel, FOnCleanupWorkflow InCleanupWorkflowDelegate);`
- L24 _public prototype_ `void RevertDirtyPackages();` — Discards all dirty packages, and reloads them.
- L27 _public prototype_ `void SaveDirtyPackages();` — Saves all dirty packages.
- L30 _public prototype_ `void Cancel();` — Cancels this workflow
- L33 _public function_ `FOnEndWorkflow& OnWorkflowEnded()` — Invoked when this workflow ends.
- L38 _private member_ `const TSharedRef<FSandboxSystemModel> SandboxModel;` — The shared sandbox model.
- L41 _private member_ `const FOnCleanupWorkflow CleanupWorkflowDelegate;` — Cleanup delegate invoked after OnWorkflowEndedDelegate.
- L43 _private member_ `FOnEndWorkflow OnWorkflowEndedDelegate;` — Invoked when this workflow ends.
- L45 _private prototype_ `void BroadcastEndWorkflowDelegates(EWorkflowResult InResult);`

#### enum `UE::SandboxedEditing::FAskUserAboutDirtyPackagesWorkflow::EWorkflowResult`  
`enum class EWorkflowResult`  
_L17-17_
- L17 _public enumerator_ `enum class EWorkflowResult { Success, Error, Cancelled }; DECLARE_DELEGATE_OneParam(FOnCleanupWorkflow, EWorkflowResult) DECLARE_MULTICAST_DELEGATE_OneParam(FOnEndWorkflow, EWorkflowResult) explicit FAskUserAboutDirtyPackagesWorkflow(const TSharedRef<FSandboxSystemModel>& InSandboxModel, FOnCleanupWorkflow InCleanupWorkflowDelegate); void RevertDirtyPackages();`
- L17 _public enumerator_ `enum class EWorkflowResult { Success, Error, Cancelled }; DECLARE_DELEGATE_OneParam(FOnCleanupWorkflow, EWorkflowResult) DECLARE_MULTICAST_DELEGATE_OneParam(FOnEndWorkflow, EWorkflowResult) explicit FAskUserAboutDirtyPackagesWorkflow(const TSharedRef<FSandboxSystemModel>& InSandboxModel, FOnCleanupWorkflow InCleanupWorkflowDelegate); void RevertDirtyPackages();`
- L17 _public enumerator_ `enum class EWorkflowResult { Success, Error, Cancelled }; DECLARE_DELEGATE_OneParam(FOnCleanupWorkflow, EWorkflowResult) DECLARE_MULTICAST_DELEGATE_OneParam(FOnEndWorkflow, EWorkflowResult) explicit FAskUserAboutDirtyPackagesWorkflow(const TSharedRef<FSandboxSystemModel>& InSandboxModel, FOnCleanupWorkflow InCleanupWorkflowDelegate); void RevertDirtyPackages();`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SandboxedEditing` (scope `UE`)
- L18 _delegate_ `DECLARE_DELEGATE_OneParam(FOnCleanupWorkflow, EWorkflowResult) DECLARE_MULTICAST_DELEGATE_OneParam(FOnEndWorkflow, EWorkflowResult) explicit FAskUserAboutDirtyPackagesWorkflow(const TSharedRef<FSandboxSystemModel>& InSandboxModel, FOnCleanupWorkflow InCleanupWorkflowDelegate);`
- L19 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnEndWorkflow, EWorkflowResult) explicit FAskUserAboutDirtyPackagesWorkflow(const TSharedRef<FSandboxSystemModel>& InSandboxModel, FOnCleanupWorkflow InCleanupWorkflowDelegate);`

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/ViewModels/Leaving/AskUserToPersistWorkflow.h` (Private)


#### enum `UE::SandboxedEditing::EAskUserToPersistResult`  
`enum class EAskUserToPersistResult : uint8`  
_L10-18_
- L13 _public enumerator_ `ProceedToPersist` — The user wants to select files to persist.
- L15 _public enumerator_ `LeaveWithoutPersist` — The users wants to leave without persisting.
- L17 _public enumerator_ `Cancelled` — User decided to cancel the operation.

#### class `UE::SandboxedEditing::FAskUserToPersistWorkflow`  
`class FAskUserToPersistWorkflow : public FNoncopyable`  
_L21-44_
- inherits: `FNoncopyable`
- desc: Upon leaving the sandbox, asks the user whether they want to persist changes
- L25 _public prototype_ `DECLARE_DELEGATE_OneParam(FCleanupWorkflow, EAskUserToPersistResult);`
- L27 _public function_ `explicit FAskUserToPersistWorkflow(FCleanupWorkflow InCleanupWorkflow) : CleanupWorkflow(MoveTemp(InCleanupWorkflow))`
- L32 _public function_ `void ProceedToPersist()` — Proceed to present the dialogue for persisting files. Called by view.
- L35 _public function_ `void LeaveWithoutPersist()` — Leave the sandbox without persisting files. Called by view.
- L38 _public function_ `void CancelLeave()` — The user decided to cancel the operation. Called by view.
- L43 _private member_ `FCleanupWorkflow CleanupWorkflow;` — Invoked when the workflow ends.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SandboxedEditing` (scope `UE`)
- L25 _delegate_ `DECLARE_DELEGATE_OneParam(FCleanupWorkflow, EAskUserToPersistResult);`

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/ViewModels/Leaving/LeaveSandboxViewModel.h` (Private)


#### class `UE::SandboxedEditing::FLeaveSandboxViewModel`  
`class FLeaveSandboxViewModel : public FNoncopyable`  
_L30-79_
- inherits: `FNoncopyable`
- desc: Handles the userflow of leaving a sandbox. All steps that may be performed are: 1. Handle any in-memory changes to packages: either save all, or discard all. 2. Ask the user to persist files changes, if any have been made. 3. Persist files the user has selected. 4. Leave the sandbox.
- L34 _public prototype_ `explicit FLeaveSandboxViewModel( const TSharedRef<FSandboxSystemModel> InModel, const TSharedRef<FPersistSandboxViewModel> InPersistViewModel );`
- L38 _public prototype_ `~FLeaveSandboxViewModel();`
- L41 _public prototype_ `void LeaveSandbox();` — Leaves the active sandbox.
- L43 _public prototype_ `bool CanLeaveSandbox(FText* OutReason = nullptr) const;` — @return Whether the sandbox can be left
- L46 _public function_ `FAskUserAboutDirtyPackagesWorkflow* GetLeaveWithDirtyPackageWorkflow() const` — @return Gets the current workflow
- L48 _public function_ `FAskUserToPersistWorkflow* GetAskUserToPersistWorkflow() const` — @return Gets the current workflow
- L51 _public function_ `FLeaveWithDirtyPackagesWorkflowDelegate& OnCreateLeaveWithDirtyPackageWorkflow()` — Invoked when the user should be asked about what to do with dirty packages.
- L53 _public function_ `FAskUserToPersistWorkflowDelegate& OnAskUserToPersistWorkflow()` — Invoked when the user should be asked whether they want to persist any files.
- L58 _private member_ `const TSharedRef<FSandboxSystemModel> Model;` — The model used to interact with the sandbox system.
- L61 _private member_ `const TSharedRef<FPersistSandboxViewModel> PersistViewModel;` — Used to go through the persist workflow.
- L64 _private member_ `TUniquePtr<FAskUserAboutDirtyPackagesWorkflow> LeaveWithDirtyPackagesWorkflow;` — Handles dirty packages when leaving.
- L66 _private member_ `TUniquePtr<FAskUserToPersistWorkflow> AskUserToPersistWorkflow;` — Asks the user whether they want to persist, leave without persisting, or cancel.
- L69 _private member_ `FLeaveWithDirtyPackagesWorkflowDelegate OnCreateLeaveWithDirtyPackageWorkflowDelegate;` — Invoked when the user should be asked about what to do with dirty packages.
- L71 _private member_ `FAskUserToPersistWorkflowDelegate AskUserToPersistWorkflowDelegate;` — Invoked when the user should be asked whether they want to persist any files.
- L74 _private prototype_ `void OnDirtyPackagesHandled(FAskUserAboutDirtyPackagesWorkflow::EWorkflowResult InResult);` — Invoked when LeaveWithDirtyPackagesWorkflow finishes.
- L76 _private prototype_ `void OnUserDecidedWhetherToPersist(EAskUserToPersistResult InResult);` — Invoked when the FAskUserToPersistWorkflow ends.
- L78 _private prototype_ `void OnPersistOperationEnded(EPersistWorkflowAction InAction) const;` — Invoked when the FPersistSandboxWorkflow has ended.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace SandboxedEditing` (scope `UE`)
- L18 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FLeaveWithDirtyPackagesWorkflowDelegate, FAskUserAboutDirtyPackagesWorkflow&);`
- L18 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FLeaveWithDirtyPackagesWorkflowDelegate, FAskUserAboutDirtyPackagesWorkflow&);` (scope `UE::SandboxedEditing`)
- L19 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FAskUserToPersistWorkflowDelegate, FAskUserToPersistWorkflow&);`
- L19 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FAskUserToPersistWorkflowDelegate, FAskUserToPersistWorkflow&);` (scope `UE::SandboxedEditing`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/ViewModels/List/FilterSandboxViewModel.h` (Private)


#### class `UE::SandboxedEditing::FFilterSandboxViewModel`  
`class FFilterSandboxViewModel : public FNoncopyable`  
_L16-47_
- inherits: `FNoncopyable`
- desc: Knows of all filters for filtering sandbox items.
- L18 _private typedef_ `using FSandboxTextFilter = TTextFilter<const TSharedRef<FSandboxListItem>&>;`
- L21 _public prototype_ `explicit FFilterSandboxViewModel(TAttribute<TArray<TSharedRef<ISandboxColumnBehavior>>> InVisibleColumns);`
- L24 _public prototype_ `FText GetSearchText() const;` — @return Current search text
- L26 _public prototype_ `void SetSearchText(const FText& InSearchText);` — Sets the search text. Will trigger a refilter.
- L29 _public prototype_ `bool PassesFilter(const TSharedRef<FSandboxListItem>& InItem) const;` — @return Whether the item can be displayed.
- L32 _public function_ `FSimpleMulticastDelegate& OnFilterChanged()` — @return Delegate invoked when any of the filters changes
- L37 _private member_ `const TAttribute<TArray<TSharedRef<ISandboxColumnBehavior>>> VisibleColumns;` — Visible columns. Used for filtering visible columns by text.
- L40 _private member_ `FSandboxTextFilter TextFilter;` — Does text filltering on items
- L43 _private member_ `FSimpleMulticastDelegate OnFilterChangedDelegate;` — Invoked when any of the filters changes
- L46 _private prototype_ `void ItemToString(const TSharedRef<FSandboxListItem>& InItem, TArray<FString>& OutSearchTerms);` — Converts an item to string.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/ViewModels/List/ISandboxColumnBehavior.h` (Private)


#### class `UE::SandboxedEditing::ISandboxColumnBehavior`  
`class ISandboxColumnBehavior : public ISearchableColumnBehavior<TSharedPtr<FSandboxListItem>>`  
_L13-14_
- inherits: `ISearchableColumnBehavior<TSharedPtr<FSandboxListItem>>`
- desc: Operations for columns that display sandboxes in the sandbox list view.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/ViewModels/List/ISandboxColumnWidgetFactory.h` (Private)


#### struct `UE::SandboxedEditing::FMakeSandboxColumnWidgetArgs`  
`struct FMakeSandboxColumnWidgetArgs`  
_L15-31_
- desc: Args for making a column widget in a row.
- L18 _public member_ `TSharedPtr<FSandboxListItem> RowData;` — The row data for this column widget
- L21 _public member_ `TAttribute<FText> HighlightText;` — Text that is being searched
- L24 _public member_ `FIsSelected IsSelectedDelegate;` — Whether the row is currently selected in the SListView. Required for some widgets, e.g. SInlineEditableTextBlock.
- L26 _public function_ `explicit FMakeSandboxColumnWidgetArgs(TSharedPtr<FSandboxListItem> InRowData, TAttribute<FText> InHighlightText, FIsSelected InIsSelectedDelegate) : RowData(MoveTemp(InRowData)) , HighlightText(MoveTemp(InHighlightText)) , IsSelectedDelegate(MoveTemp(InIsSelectedDelegate))`

#### class `UE::SandboxedEditing::ISandboxColumnWidgetFactory`  
`class ISandboxColumnWidgetFactory`  
_L34-45_
- desc: Interface for creating Slate widgets for a column.
- L39 _public prototype_ `virtual SHeaderRow::FColumn::FArguments MakeColumnArguments() = 0;` — @return Info required to construct the column.
- L42 _public prototype_ `virtual TSharedRef<SWidget> MakeColumnWidget(const FMakeSandboxColumnWidgetArgs& InArgs) = 0;` — @return Widget that should be put into the row for this column
- L44 _public prototype_ `virtual ~ISandboxColumnWidgetFactory() = default;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/ViewModels/List/SandboxColumnRegistry.h` (Private)


#### struct `UE::SandboxedEditing::FSandboxColumnRegistry`  
`struct FSandboxColumnRegistry`  
_L13-27_
- L16 _public member_ `TMap<FName, TSharedRef<ISandboxColumnBehavior>> ColumnBehaviors;` — The behavior of the columns for view models.
- L19 _public member_ `TMap<FName, TSharedRef<ISandboxColumnWidgetFactory>> ColumnFactories;` — Creates the widgets for the columns.
- L21 _public function_ `TArray<TSharedRef<ISandboxColumnBehavior>> GetBehaviorArray() const`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/ViewModels/List/SandboxColumns.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SandboxedEditing` (scope `UE`)
- L15 _typedef_ `using FSandboxColumnFactoryMap = TMap<FName, TSharedRef<ISandboxColumnWidgetFactory>>;` (scope `UE::SandboxedEditing`) — Needed for SLATE_ARGUMENT (the macro is written in such a way that TMap is not parsed correctly).
- L17 _variable_ `constexpr FLazyName NameSandboxColumn(TEXT("Name` (scope `UE::SandboxedEditing`)
- L18 _variable_ `constexpr FLazyName DescriptionSandboxColumn(TEXT("Desc` (scope `UE::SandboxedEditing`)
- L19 _variable_ `constexpr FLazyName VersionSandboxNameColumn(TEXT("Vers` (scope `UE::SandboxedEditing`)
- L20 _variable_ `constexpr FLazyName LastModifiedSandboxColumn(TEXT("Last` (scope `UE::SandboxedEditing`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/ViewModels/List/SandboxListItem.h` (Private)


#### class `UE::SandboxedEditing::FSandboxListItem`  
`class FSandboxListItem`  
_L10-20_
- desc: A single item displayed in the SSandboxListView.
- L15 _public member_ `FSandboxInfo SandboxInfo;` — Basic info about the sandbox
- L17 _public function_ `explicit FSandboxListItem(FSandboxInfo SandboxInfo) : SandboxInfo(MoveTemp(SandboxInfo))`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/ViewModels/List/SandboxListViewModel.h` (Private)


#### class `UE::SandboxedEditing::FSandboxListViewModel`  
`class FSandboxListViewModel : public FNoncopyable`  
_L17-78_
- inherits: `FNoncopyable`
- desc: Decides what is displayed in SSandboxListView.
- L21 _public prototype_ `explicit FSandboxListViewModel( const TSharedRef<FSandboxSystemModel>& InSandboxModel, const TSharedRef<FFilterSandboxViewModel>& InFilterViewModel, TMap<FName, TSharedRef<ISandboxColumnBehavior>> InColumns );`
- L25 _public prototype_ `~FSandboxListViewModel();`
- L28 _public function_ `const TArray<TSharedPtr<FSandboxListItem>>& GetItems() const` — @return The items to display
- L31 _public prototype_ `TArray<FName> GetDisplayedColumns() const;` — @return The columns that should be displayed (taking visibility into account).
- L34 _public prototype_ `bool IsColumnVisible(FName InColumnName) const;` — @return Whether a column is visible. Name column is always visible.
- L37 _public prototype_ `void SetColumnVisibility(FName InColumnName, bool bIsVisible);` — Sets whether a column is visible. Name column cannot be hidden.
- L40 _public prototype_ `EColumnSortPriority::Type GetSortPriority(FName InColumnName) const;` — @return The priority with which the column is sorted.
- L42 _public prototype_ `EColumnSortMode::Type GetSortMode(FName InColumnName) const;` — @return How the column is sorted
- L44 _public prototype_ `void SetSortMode(const EColumnSortPriority::Type InSortPriority, const FName& ColumnId, const EColumnSortMode::Type InSortMode);` — Changes the sort mode for the given column
- L47 _public function_ `FSimpleMulticastDelegate& OnItemsChanged()` — Invoked when the displayed items changes (added / removed / sorted).
- L52 _private member_ `const TSharedRef<FSandboxSystemModel> SandboxModel;` — The shared sandbox model.
- L54 _private member_ `const TSharedRef<FFilterSandboxViewModel> FilterViewModel;` — Used to filter the items.
- L57 _private member_ `const TMap<FName, TSharedRef<ISandboxColumnBehavior>> Columns;` — All columns that can ever be displayed.
- L60 _private member_ `TSet<FName> HiddenColumns;` — Tracks which columns are visible. Name column is always visible.
- L63 _private member_ `TArray<TSharedPtr<FSandboxListItem>> AllUnfilteredItems;` — Contains all items.
- L65 _private member_ `TArray<TSharedPtr<FSandboxListItem>> FilteredItems;` — A filtered version of AllUnfilteredItems.
- L68 _private member_ `FSimpleMulticastDelegate OnItemsChangedDelegate;` — Invoked when the displayed items changes (added / removed / sorted).
- L71 _private prototype_ `void RefreshItems();` — Updates AllUnfilteredItems from the model. Tries to retain preexisting items.
- L74 _private prototype_ `void FilterItems();`
- L77 _private prototype_ `void SortItems();` — Sorts the items.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/ViewModels/Persist/PersistOperationViewModel.h` (Private)


#### class `UE::SandboxedEditing::FPersistOperationViewModel`  
`class FPersistOperationViewModel : public FNoncopyable`  
_L14-55_
- inherits: `FNoncopyable`
- desc: View model for UI that lets the user click items they want to persist.
- L18 _public prototype_ `explicit FPersistOperationViewModel(FPersistSandboxWorkflow& InWorkflow UE_LIFETIMEBOUND);`
- L21 _public prototype_ `void ConfirmPersist() const;` — Persists the files selected so far. Any follow-up operation, such as leaving the sandbox, will be performed.
- L24 _public prototype_ `void CancelPersist() const;` — Cancels the workflow. No follow-up operation, such as leaving the sandbox, will be performed.
- L30 _public prototype_ `void SetFilePersisted(int32 InIndex, bool bShouldPersist);` — @param InIndex Index to GetPersistableFiles().NonSandboxPaths @param bShouldPersist Whether the files should be persisted
- L35 _public prototype_ `bool IsFileMarkedForPersist(int32 InIndex) const;` — @param InIndex Index to GetPersistableFiles().NonSandboxPaths @return Whether the file is marked to be persisted
- L38 _public prototype_ `void SetAllFilesPersisted(bool bAllFiles);` — Marks all files to be persisted.
- L41 _public prototype_ `bool AreAllFilesMarkedForPersist() const;` — @return Whether all files are marked to be persisted.
- L43 _public prototype_ `bool AreAnyFilesMarkedForPersist() const;` — @return Whether any files are marked for persist.
- L46 _public prototype_ `const FileSandboxCore::FGatheredFileChanges& GetPersistableFiles() const;` — @return The modified files
- L51 _private member_ `FPersistSandboxWorkflow& Workflow;` — The workflow to forward the persist and cancel events to.
- L54 _private member_ `TBitArray<> FilesMarkedForPersist;` — The files the user has selected to persist. Each index corresponds to PersistableFiles.NonSandboxPaths.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/ViewModels/Persist/PersistSandboxViewModel.h` (Private)


#### class `UE::SandboxedEditing::FPersistSandboxViewModel`  
`class FPersistSandboxViewModel : public FNoncopyable`  
_L19-67_
- inherits: `FNoncopyable`
- desc: Handles the logic of persisting a sandbox.
- L23 _public prototype_ `explicit FPersistSandboxViewModel(const TSharedRef<FSandboxSystemModel>& InModel);`
- L26 _public prototype_ `bool StartPersistWorkflow(FileSandboxCore::FGatheredFileChanges InFileChanges, TConstArrayView<FString> InPreSelected = {});` — Starts the persist workflow.
- L31 _public prototype_ `bool StartPersistWorkflowForActiveSandbox(TConstArrayView<FString> InPreSelected = {});` — Starts a persist workflow by using the changes of the active sandbox. @param
- L34 _public prototype_ `bool CanStartPersistWorkflow() const;` — @return Whether a persist workflow can be started
- L36 _public prototype_ `bool CanStartPersistWorkflowForActiveSandbox() const;` — @return Whether a persist workflow can be started for the active sandbox
- L39 _public function_ `FPersistSandboxWorkflow* GetPersistWorkflow() const` — @return The current persist workflow
- L42 _public function_ `FPersistSandboxWorkflowDelegate& OnStartPersistWorkflow()` — Invoked when the persist workflow is started.
- L44 _public function_ `FPersistWorkflowActionDelegate& OnEndPersistWorkflow()` — Invoked when the persist workflow has ended.
- L47 _public function_ `FRequestPersistSummaryNotificationDelegate& OnRequestPersistSummaryNotification()` — Invoked when a persist operation is performed to show a notification for the result.
- L52 _private member_ `const TSharedRef<FSandboxSystemModel> Model;` — Used to persist changes via the sandbox system.
- L55 _private member_ `TUniquePtr<FPersistSandboxWorkflow> ActivePersistWorkflow;` — The active persist workflow.
- L58 _private member_ `FPersistSandboxWorkflowDelegate OnStartPersistWorkflowDelegate;` — Invoked when the persist workflow is started.
- L60 _private member_ `FPersistWorkflowActionDelegate OnEndPersistWorkflowDelegate;` — Invoked when the persist workflow has ended.
- L63 _private member_ `FRequestPersistSummaryNotificationDelegate OnRequestPersistSummaryNotificationDelegate;` — Invoked when a persist operation is performed to show a notification for the result.
- L66 _private prototype_ `void OnCleanupPersistWorkflow(const FPersistWorkflowUserChoice& InPersistResult);` — Handles the workflow ending, possibly persisting InFilesToPersist.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace FileSandboxUI` (scope `UE`)
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SandboxedEditing` (scope `UE`)
- L14 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FPersistSandboxWorkflowDelegate, FPersistSandboxWorkflow&, TConstArrayView<FString> ) DECLARE_MULTICAST_DELEGATE_OneParam(FPersistWorkflowActionDelegate, EPersistWorkflowAction);`
- L14 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FPersistSandboxWorkflowDelegate, FPersistSandboxWorkflow&, TConstArrayView<FString> ) DECLARE_MULTICAST_DELEGATE_OneParam(FPersistWorkflowActionDelegate, EPersistWorkflowAction);` (scope `UE::SandboxedEditing`)
- L15 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FPersistWorkflowActionDelegate, EPersistWorkflowAction);`
- L16 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FRequestPersistSummaryNotificationDelegate, const FileSandboxUI::FPersistSummary&) class FPersistSandboxViewModel : public FNoncopyable { public: explicit FPersistSandboxViewModel(const TSharedRef<FSandboxSystemModel>& InModel); bool StartPersistWorkflow(FileSandboxCore::FGatheredFileChanges InFileChanges, TConstArrayView<FString> InPreSelected = {}); bool StartPersistWorkflowForActiveSandbox(TConstArrayView<FString> InPreSelected = {}); bool CanStartPersistWorkflow() const; bool CanStartPersistWorkflowForActiveSandbox() const; FPersistSandboxWorkflow* GetPersistWorkflow() const { return ActivePersistWorkflow.Get(); } FPersistSandboxWorkflowDelegate& OnStartPersistWorkflow() { return OnStartPersistWorkflowDelegate; } FPersistWorkflowActionDelegate& OnEndPersistWorkflow() { return OnEndPersistWorkflowDelegate; } FRequestPersistSummaryNotificationDelegate& OnRequestPersistSummaryNotification() { return OnRequestPersistSummaryNotificationDelegate; } private: const TSharedRef<FSandboxSystemModel> Model; TUniquePtr<FPersistSandboxWorkflow> ActivePersistWorkflow;`

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/ViewModels/Persist/PersistSandboxWorkflow.h` (Private)


#### enum `UE::SandboxedEditing::EPersistWorkflowResult`  
`enum class EPersistWorkflowResult : uint8`  
_L16-22_
- L19 _public enumerator_ `Persisted` — Files were persisted, or the user decided to confirm without any files to persist.
- L21 _public enumerator_ `Cancelled` — User decided to cancel the operation. Do not continue with follow-up operations, such as leaving the sandbox.

#### class `UE::SandboxedEditing::FPersistSandboxWorkflow`  
`class FPersistSandboxWorkflow : public FNoncopyable`  
_L28-66_
- inherits: `FNoncopyable`
- desc: Represents a temporary application state in which user operation is choosing files to persist. Effectively, this is a view-model representation of the pop-up dialogue, in which files to persist are chosen.
- L33 _public prototype_ `DECLARE_DELEGATE_OneParam(FCleanupWorkflow, const FPersistWorkflowUserChoice&);` — @param FilesToPersist The files the user selected to persist. Unset if the operation is cancelled. Can be set but empty.
- L35 _public prototype_ `explicit FPersistSandboxWorkflow( const TSharedRef<FSandboxSystemModel>& InModel, FileSandboxCore::FGatheredFileChanges InChanges, FCleanupWorkflow InOnWorkflowEnded );`
- L41 _public prototype_ `void ConfirmPersist(TArray<FString> InFilesToPersist) const;` — Persists the files selected so far. Any follow-up operation, such as leaving the sandbox, will be performed.
- L44 _public prototype_ `void CancelPersist() const;` — Cancels the workflow. No follow-up operation, such as leaving the sandbox, will be performed.
- L47 _public function_ `const FileSandboxCore::FGatheredFileChanges& GetPersistableFiles() const` — @return The modified files
- L50 _public function_ `FSimpleMulticastDelegate& OnWorkflowEnded()` — Invoked when the workflow ends.
- L55 _private member_ `const TSharedRef<FSandboxSystemModel> Model;` — The model used to interact with the sandbox system.
- L58 _private member_ `FSimpleMulticastDelegate OnWorkflowEndedDelegate;` — Invoked when the workflow ends.
- L60 _private member_ `const FCleanupWorkflow OnCleanupWorkflowDelegate;` — Invoked when the workflow ends.
- L63 _private member_ `const FileSandboxCore::FGatheredFileChanges PersistableFiles;` — The files that can be persisted.
- L65 _private prototype_ `void EndWorkflow(const FPersistWorkflowUserChoice& InResult) const;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SandboxedEditing` (scope `UE`)
- L33 _delegate_ `DECLARE_DELEGATE_OneParam(FCleanupWorkflow, const FPersistWorkflowUserChoice&);` — @param FilesToPersist The files the user selected to persist. Unset if the operation is cancelled. Can be set but empty.

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/ViewModels/Persist/PersistWorkflowUserChoice.h` (Private)


#### enum `UE::SandboxedEditing::EPersistWorkflowAction`  
`enum class EPersistWorkflowAction : uint8`  
_L12-22_
- desc: Action to take when FPersistSandboxWorkflow completes.
- L15 _public enumerator_ `Persist` — Files were selected for persist. Any follow-up operation, such as leaving, should be performed.
- L18 _public enumerator_ `PersistNone` — User explicitly choose not to persist any of the files. Any follow-up operation, such as leaving, should be performed.
- L21 _public enumerator_ `Cancelled` — User decided to cancel the operation. Do not continue with follow-up operations, such as leaving the sandbox.

#### struct `UE::SandboxedEditing::FPersistWorkflowUserChoice`  
`struct FPersistWorkflowUserChoice`  
_L25-39_
- desc: Describes the user decision for FPersistSandboxWorkflow.
- L28 _public member_ `EPersistWorkflowAction UserAction;` — Determines what action the user chose to take.
- L31 _public member_ `TOptional<TArray<FString>> FilesToPersist;` — Only set if UserAction == EPersistWorkflowAction::Persist.
- L33 _public function_ `static FPersistWorkflowUserChoice MakePersist(TArray<FString> InFileToPersist)`
- L37 _public function_ `static FPersistWorkflowUserChoice MakePersistNone()`
- L38 _public function_ `static FPersistWorkflowUserChoice MakeCancelled()`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/ViewModels/RenameSandboxWorkflow.h` (Private)


#### class `UE::SandboxedEditing::FRenameSandboxWorkflow`  
`class FRenameSandboxWorkflow : public FNoncopyable`  
_L16-65_
- inherits: `FNoncopyable`
- desc: Workflow for renaming a sandbox.
- L20 _public prototype_ `explicit FRenameSandboxWorkflow( FString InRenamedRoot, const TSharedRef<FSandboxSystemModel>& InModel, FSimpleDelegate InOnWorkflowEndedDelegate );`
- L26 _public prototype_ `void Confirm();` — Renames the sandbox if the name is valid, and stops the operation if successful.
- L28 _public prototype_ `void Cancel();` — Cancels the operation.
- L31 _public function_ `void SetName(FString InName)` — Sets the that the sandbox should be renamed to.
- L38 _public prototype_ `bool IsNameValid(FText* OutErrorText = nullptr) const;` — @return Whether the current name is valid, and an optional error message if this function returns false.
- L41 _public function_ `const FString& GetRenamedSandboxRoot() const` — @return The root directory of the sandbox being renamed
- L44 _public function_ `FOnSandboxRenamed& OnSandboxRenamed()` — Invoked after the sandbox has been successfully renamed.
- L49 _private member_ `const TSharedRef<FSandboxSystemModel> Model;` — The model used to interact with the sandbox system.
- L52 _private member_ `const FString RenamedSandboxRoot;` — The root directory of the sandbox being renamed
- L54 _private member_ `const FString InitialName;` — The name the sandbox had at the beginning.
- L57 _private member_ `FOnSandboxRenamed OnSandboxRenamedDelegate;` — Invoked after the sandbox has been successfully renamed.
- L59 _private member_ `const FSimpleDelegate OnWorkflowEndedDelegate;` — Invoked when the workflow ends.
- L62 _private member_ `FString NewName;` — The name to give the sandbox.
- L64 _private member_ `bool bHasChangedName = false;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace SandboxedEditing` (scope `UE`)
- L11 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSandboxRenamed, const FString& , const FString& );`
- L11 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSandboxRenamed, const FString& , const FString& );` (scope `UE::SandboxedEditing`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/ViewModels/SandboxControlsViewModel.h` (Private)


#### class `UE::SandboxedEditing::FSandboxControlsViewModel`  
`class FSandboxControlsViewModel : public FNoncopyable`  
_L30-148_
- inherits: `FNoncopyable`
- desc: Handles actions that can be performed with FSandboxListItems, such as deleting, renaming, loading. These actions are primarily present on the controls widget in the form of buttons. Some of them can be performed in the list view, such as deleting or renaming.
- L34 _public prototype_ `explicit FSandboxControlsViewModel(const TSharedRef<FSandboxSystemModel>& InModel);`
- L37 _public prototype_ `void CancelWorkflows();` — Cancels any workflows that may be active.
- L40 _public prototype_ `void StartCreationWorkflow();` — Starts a workflow for creating a new sandbox.
- L42 _public prototype_ `bool CanStartCreationWorkflow() const;` — @return Whether a new sandbox creation workflow can currently be started.
- L44 _public function_ `FSandboxCreationWorkflow* GetCurrentCreationWorkflow() const` — @return The currently active creation workflow.
- L47 _public prototype_ `bool CanLoadSandbox(const FString& InSandboxRoot, FText* OutReason = nullptr) const;` — @return Whether the sandbox can be loaded.
- L49 _public prototype_ `void LoadSandbox(const FString& InSandboxRoot);` — Loads the sandbox.
- L52 _public prototype_ `bool CanDeleteSandbox(const FString& InSandboxRoot, FText* OutReason = nullptr) const;` — @return Whether the sandbox can be deleted.
- L54 _public prototype_ `void DeleteSandbox(const FString& InSandboxRoot);` — Deletes the sandbox.
- L57 _public prototype_ `bool CanRenameSandbox(const FString& InSandboxRoot, FText* OutError = nullptr) const;` — @return Whether a rename operation can be started for the sandbox.
- L59 _public prototype_ `void StartRenameWorkflow(const FString& InSandboxRoot);` — Starts a rename operation for the sandbox.
- L61 _public function_ `FRenameSandboxWorkflow* GetCurrentRenameWorkflow() const` — @return The currently active rename workflow.
- L64 _public prototype_ `bool CanStartExportWorkflow() const;` — @return Whether an export operation can be performed.
- L66 _public prototype_ `void StartExportWorkflow(const TArray<FString>& InSandboxRoots);` — Starts an export workflow
- L68 _public function_ `FExportWorkflow* GetCurrentExportWorkflow() const` — @return The currently active export workflow.
- L71 _public prototype_ `bool CanStartImportWorkflow() const;` — @return Whether an import operation can be performed.
- L73 _public prototype_ `void StartImportWorkflow();` — Starts an import workflow.
- L75 _public function_ `FImportWorkflow* GetCurrentImportWorkflow() const` — @return The currently active import workflow.
- L78 _public function_ `FCreationWorkflowDelegate& OnCreationWorkflowStarted()` — @return Delegate that is invoked when the creation workflow starts.
- L80 _public function_ `FSimpleMulticastDelegate& OnCreationWorkflowEnded()` — @return Delegate that is invoked when the creation workflow ends.
- L83 _public function_ `FRenameWorkflowDelegate& OnRenameWorkflowStarted()` — @return Delegate that is invoked when the rename workflow starts.
- L85 _public function_ `FSimpleMulticastDelegate& OnRenameWorkflowEnded()` — @return Delegate that is invoked when the rename workflow ends.
- L88 _public function_ `FExportWorkflowDelegate& OnExportWorkflowStarted()` — @return Delegate that is invoked when the export workflow starts.
- L90 _public function_ `FSimpleMulticastDelegate& OnExportWorkflowEnded()` — @return Delegate that is invoked when the export workflow ends.
- L93 _public function_ `FImportWorkflowDelegate& OnImportWorkflowStarted()` — @return Delegate that is invoked when the import workflow starts.
- L95 _public function_ `FSimpleMulticastDelegate& OnImportWorkflowEnded()` — @return Delegate that is invoked when the import workflow ends.
- L100 _private prototype_ `void LoadSandboxInternal(const FString& InSandboxRoot);` — Loads the sandbox without checking for in-memory changes.
- L103 _private member_ `const TSharedRef<FSandboxSystemModel> Model;` — The underlying model that performs the mutations.
- L106 _private member_ `TWeakPtr<SNotificationItem> InMemoryChangesNotification;` — Active notification for in-memory changes warning. Lifetime is not bound to this class and only used to make sure we do not have multiple notification to the user.
- L109 _private member_ `TUniquePtr<FSandboxCreationWorkflow> CurrentCreationWorkflow;` — Set if the user is currently in the process of creating a sandbox.
- L111 _private member_ `TUniquePtr<FRenameSandboxWorkflow> CurrentRenameWorkflow;` — Set if the user is currently in the process of renaming a sandbox.
- L113 _private member_ `TUniquePtr<FExportWorkflow> CurrentExportWorkflow;` — Set if the user is currently in the process of exporting sandboxes.
- L115 _private member_ `TUniquePtr<FImportWorkflow> CurrentImportWorkflow;` — Set if the user is currently in the process of importing sandboxes.
- L118 _private member_ `FCreationWorkflowDelegate OnCreationWorkflowStartedDelegate;` — Invoked when the creation workflow starts.
- L120 _private member_ `FSimpleMulticastDelegate OnCreationWorkflowEndedDelegate;` — Invoked when the creation workflow ends.
- L123 _private member_ `FRenameWorkflowDelegate OnRenameWorkflowStartedDelegate;` — Invoked when the rename workflow starts.
- L125 _private member_ `FSimpleMulticastDelegate OnRenameWorkflowEndedDelegate;` — Invoked when the rename workflow ends.
- L128 _private member_ `FExportWorkflowDelegate OnExportWorkflowStartedDelegate;` — Invoked when the export workflow starts.
- L130 _private member_ `FSimpleMulticastDelegate OnExportWorkflowEndedDelegate;` — Invoked when the export workflow ends.
- L133 _private member_ `FImportWorkflowDelegate OnImportWorkflowStartedDelegate;` — Invoked when the import workflow starts.
- L135 _private member_ `FSimpleMulticastDelegate OnImportWorkflowEndedDelegate;` — Invoked when the import workflow ends.
- L138 _private prototype_ `void HandleCreationWorkflowEnded();` — Called by CurrentCreationWorkflow when the workflow ends.
- L140 _private prototype_ `void HandleRenameWorkflowEnded();` — Called by CurrentRenameWorkflow when the workflow ends.
- L142 _private prototype_ `void HandleExportWorkflowEnded();` — Called by CurrentExportWorkflow when the workflow ends.
- L144 _private prototype_ `void HandleImportWorkflowEnded();` — Called by CurrentImportWorkflow when the workflow ends.
- L147 _private function_ `bool HasActiveWorkflow() const` — @return Whether a workflow is active

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace SandboxedEditing` (scope `UE`)
- L19 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FCreationWorkflowDelegate, FSandboxCreationWorkflow&);`
- L19 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FCreationWorkflowDelegate, FSandboxCreationWorkflow&);` (scope `UE::SandboxedEditing`)
- L20 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FRenameWorkflowDelegate, FRenameSandboxWorkflow&);`
- L20 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FRenameWorkflowDelegate, FRenameSandboxWorkflow&);` (scope `UE::SandboxedEditing`)
- L21 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FExportWorkflowDelegate, FExportWorkflow&);`
- L21 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FExportWorkflowDelegate, FExportWorkflow&);` (scope `UE::SandboxedEditing`)
- L22 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FImportWorkflowDelegate, FImportWorkflow&);`
- L22 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FImportWorkflowDelegate, FImportWorkflow&);` (scope `UE::SandboxedEditing`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/ViewModels/SandboxCreationWorkflow.h` (Private)


#### class `UE::SandboxedEditing::FSandboxCreationWorkflow`  
`class FSandboxCreationWorkflow : public FNoncopyable`  
_L18-52_
- inherits: `FNoncopyable`
- desc: View-model managing the workflow for creating a new sandbox. The user can type the name, edit other data, etc. At any point they can confirm or cancel the workflow.
- L22 _public prototype_ `explicit FSandboxCreationWorkflow(const TSharedRef<FSandboxSystemModel>& InModel, FSimpleDelegate InOnWorkflowEndedDelegate);`
- L25 _public prototype_ `void Confirm();` — Finishes the workflow, if possible, resulting in the creation of the sandbox.
- L27 _public prototype_ `void Cancel();` — Stops the workflow.
- L30 _public prototype_ `bool CanConfirm(FText* OutReason = nullptr) const;` — @return Whether the workflow can be confirmed, i.e. whether the sandbox can be created.
- L33 _public prototype_ `void SetName(const FString& InNewName);` — Sets the name the user wants to give the sandbox. The name needn't be valid, however, it will prevent CanConfirm from returning true.
- L35 _public prototype_ `bool IsValidName(const FString& InName, FText* OutReason = nullptr) const;` — @return Whether this name is a valid name to set.
- L38 _public prototype_ `void SetDescription(const FString& InNewDescription);` — Sets the description. There are no restrictions on the description.
- L43 _private member_ `const TSharedRef<FSandboxSystemModel> Model;` — The model used to interact with the sandbox system.
- L46 _private member_ `const FSimpleDelegate OnWorkflowEndedDelegate;` — Invoked when the workflow ends.
- L49 _private member_ `FString Name;` — The name the user wants to give.
- L51 _private member_ `FString Description;` — The description the user wants to give.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/ViewModels/SandboxMetaDataViewModel.h` (Private)


#### class `UE::SandboxedEditing::FSandboxMetaDataViewModel`  
`class FSandboxMetaDataViewModel : public FNoncopyable`  
_L13-29_
- inherits: `FNoncopyable`
- desc: Handles editing metadata about sandboxes, such as name and description.
- L17 _public prototype_ `explicit FSandboxMetaDataViewModel(const TSharedRef<FSandboxSystemModel>& InModel);`
- L20 _public prototype_ `TOptional<FString> GetDescription(const FString& InSandboxRoot) const;` — @return The description of the given sandbox. Unset if the sandbox root does not exist.
- L23 _public prototype_ `void SetDescription(const FString& InSandboxRoot, const FString& InNewDescription);` — Sets the description of the sandbox
- L28 _private member_ `const TSharedRef<FSandboxSystemModel> Model;` — The model used to query the sandboxes.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/ViewModels/Transfer/ExportWorkflow.h` (Private)


#### enum `UE::SandboxedEditing::EExportPathType`  
`enum class EExportPathType : uint8`  
_L16-24_
- desc: What type of path the user should select.
- L19 _public enumerator_ `Directory` — Select a directory to export multiple sandboxes to.
- L21 _public enumerator_ `Zip` — Select a file name for a single sandbox to be exported.
- L23 _public enumerator_ `Count`

#### class `UE::SandboxedEditing::FExportWorkflow`  
`class FExportWorkflow : public FNoncopyable`  
_L27-83_
- inherits: `FNoncopyable`
- desc: Workflow for exporting sandboxes from Unreal.
- L31 _public prototype_ `explicit FExportWorkflow(TArray<FString> InSandboxPaths, FSimpleDelegate InOnWorkflowEndedDelegate);`
- L34 _public prototype_ `bool CanExport();` — @return Whether the sandbox selection can be exported.
- L36 _public prototype_ `void TryExportOrCancel();` — Exports the sandbox selection.
- L39 _public prototype_ `void Cancel();` — Cancels the operation.
- L42 _public prototype_ `TArray<FString> GetFilesOverridenByExportDirectory(const FString& InNewExportRoot) const;` — @return List of files that would be overriden if this path is chosen.
- L45 _public prototype_ `void SetExportPath(FString InNewExportRoot);` — Sets the export path.
- L47 _public prototype_ `const FString& GetExportPath() const;` — @return The export path
- L50 _public prototype_ `EExportPathType GetExportType() const;` — @return What type of path the user should select.
- L53 _public prototype_ `FString GetDefaultExportDirectory() const;` — @return Default path to suggest to the user.
- L55 _public prototype_ `FString GetDefaultSandboxFileName() const;` — @return Default filename to suggest to the user.
- L58 _public function_ `TConstArrayView<FString> GetExportedSandboxRootPaths() const` — @return The sandboxes that are being exported.
- L61 _public function_ `FExportEndedDelegate& OnExportEnded()` — Invoked when the operation ends.
- L66 _private member_ `const TArray<FString> ExportedSandboxPaths;` — The sandboxes that are being exported.
- L69 _private member_ `const FSimpleDelegate OnWorkflowEndedDelegate;` — Invoked when the workflow ends.
- L72 _private member_ `FExportEndedDelegate ExportEndedDelegate;` — Invoked when the operation ends.
- L79 _private member_ `FString ExportPath;` — This has a different meaning depending on ExportedSandboxPaths.Num: - Num() == 1: This is a file path to a .zip to export to, or a directory path (in which case the repository name is used as suggested name). - Num() > 1: This is a directory path to place the .zips in.
- L81 _private prototype_ `bool CanSingleExport() const;`
- L82 _private prototype_ `bool CanMultiExport() const;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SandboxedEditing` (scope `UE`)
- L12 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FSandboxExportPathDelegate, const FString& InDefaultName);`
- L12 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FSandboxExportPathDelegate, const FString& InDefaultName);` (scope `UE::SandboxedEditing`)
- L13 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FExportEndedDelegate, const FExportWorkflowResult& InExportResult);`
- L13 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FExportEndedDelegate, const FExportWorkflowResult& InExportResult);` (scope `UE::SandboxedEditing`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/ViewModels/Transfer/ExportWorkflowResult.h` (Private)


#### enum `UE::SandboxedEditing::EExportWorkflowResult`  
`enum class EExportWorkflowResult : uint8`  
_L11-18_
- desc: Gives an indication of the workflow's result.
- L13 _public enumerator_ `Success`
- L14 _public enumerator_ `SomeErrors`
- L15 _public enumerator_ `Cancelled`
- L17 _public enumerator_ `Count`

#### struct `UE::SandboxedEditing::FExportWorkflowResult`  
`struct FExportWorkflowResult`  
_L21-28_
- desc: Describes the result of a finished export workflow.
- L24 _public member_ `EExportWorkflowResult ExportResult;` — Gives an indication of the workflow's result.
- L27 _public member_ `TArray<FString> SandboxesWithErrors;` — Sandboxes that failed to be exported.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/ViewModels/Transfer/ImportValidationResult.h` (Private)


#### struct `UE::SandboxedEditing::FImportValidationResult`  
`struct FImportValidationResult`  
_L11-21_
- desc: Result of validating user selected files before import.
- L17 _public member_ `TArray<FString> AskForOverwrite;` — The root paths of sandboxes that already exist and would be overwritten by the import operation. Ask the user to confirm overwrite.
- L20 _public member_ `TArray<FString> InvalidZips;` — Paths to zips that the user selected but that do not contain any valid sandboxes.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/ViewModels/Transfer/ImportWorkflow.h` (Private)


#### class `UE::SandboxedEditing::FImportWorkflow`  
`class FImportWorkflow : public FNoncopyable`  
_L22-55_
- inherits: `FNoncopyable`
- desc: Workflow for importing sandboxes into Unreal.
- L26 _public prototype_ `explicit FImportWorkflow(FSimpleDelegate InOnWorkflowEndedDelegate);`
- L28 _public prototype_ `void TryImportOrCancel();`
- L30 _public prototype_ `void Cancel();`
- L33 _public prototype_ `FImportValidationResult SetFilesToImport(TArray<FString> InFiles);` — Sets the files that are supposed
- L35 _public function_ `const TArray<FString>& GetFilesToImport() const` — @return The files that will be imported.
- L38 _public prototype_ `FString GetDefaultImportDirectory() const;` — @return Default path to suggest to the user.
- L41 _public function_ `FImportEndedDelegate& OnImportEnded()` — Invoked when the operation ends.
- L46 _private member_ `const FSimpleDelegate OnWorkflowEndedDelegate;` — Invoked when the workflow ends.
- L49 _private member_ `TArray<FString> FilesToImport;` — Paths to the files the user has selected for import.
- L51 _private member_ `TArray<FileSandboxCore::ZipUtils::FImportInspectionResult> FileInspections;` — Validation result for each selected file.
- L54 _private member_ `FImportEndedDelegate ImportEndedDelegate;` — Invoked when the operation ends.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace FileSandboxCore` (scope `UE`)
- L11 _namespace_ `namespace ZipUtils` (scope `UE::FileSandboxCore`)
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace SandboxedEditing` (scope `UE`)
- L19 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FImportEndedDelegate, const FImportWorkflowResult& InImportResult);`
- L19 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FImportEndedDelegate, const FImportWorkflowResult& InImportResult);` (scope `UE::SandboxedEditing`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/ViewModels/Transfer/ImportWorkflowResult.h` (Private)


#### enum `UE::SandboxedEditing::EImportWorkflowResult`  
`enum class EImportWorkflowResult : uint8`  
_L11-18_
- desc: Gives an indication of the workflow's result.
- L13 _public enumerator_ `Success`
- L14 _public enumerator_ `SomeErrors`
- L15 _public enumerator_ `Cancelled`
- L17 _public enumerator_ `Count`

#### struct `UE::SandboxedEditing::FImportWorkflowResult`  
`struct FImportWorkflowResult`  
_L21-28_
- desc: Describes the result of the entire import operation (multiple sandboxes can be imported at the same time).
- L24 _public member_ `EImportWorkflowResult ResultCode;` — Gives an indication of the workflow's result.
- L27 _public member_ `TArray<FString> Errors;` — The errors that occured. If empty, the operation was successful.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/Views/AskUserAboutDirtyPackagesView.h` (Private)


#### class `UE::SandboxedEditing::FAskUserAboutDirtyPackagesView`  
`class FAskUserAboutDirtyPackagesView : public FNoncopyable`  
_L17-46_
- inherits: `FNoncopyable`
- desc: Visualizes the notification for leaving the sandbox with dirty packages.
- L21 _public prototype_ `explicit FAskUserAboutDirtyPackagesView(const TSharedRef<FLeaveSandboxViewModel>& InLeaveViewModel);`
- L22 _public prototype_ `~FAskUserAboutDirtyPackagesView();`
- L27 _private member_ `const TSharedRef<FLeaveSandboxViewModel> LeaveViewModel;` — Notifies us when a FLeaveSandboxViewModel starts.
- L30 _private member_ `TSharedPtr<SNotificationItem> Notification;` — Whether currently showing the notification for when the user is trying to leave the sandbox even though there are modified assets.
- L32 _private member_ `FDelegateHandle HandleWorkflowEndHandle;`
- L35 _private prototype_ `void ShowNotification(FAskUserAboutDirtyPackagesWorkflow& InWorkflow);` — Show the notification for when the user is trying to leave the sandbox even though there are modified assets.
- L38 _private prototype_ `void HandleSaveAll() const;` — Saves all dirty assets, hides the notification, and proceeds with the leave operation.
- L40 _private prototype_ `void HandleRevert() const;` — Discards all dirty assets, hides the notification, and proceeds with the leave operation.
- L42 _private prototype_ `void HandleCancel() const;` — Cancels the workflow.
- L45 _private prototype_ `void HideNotification();` — Hides the notification.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/Views/AskUserToPersistView.h` (Private)


#### class `UE::SandboxedEditing::FAskUserToPersistView`  
`class FAskUserToPersistView`  
_L13-26_
- desc: Visualizes FAskUserToPersistWorkflow by displaying a dialogue.
- L17 _public prototype_ `explicit FAskUserToPersistView(const TSharedRef<FLeaveSandboxViewModel>& InLeaveViewModel);`
- L18 _public prototype_ `~FAskUserToPersistView();`
- L23 _private member_ `const TSharedRef<FLeaveSandboxViewModel> LeaveViewModel;` — Notifies when FAskUserToPersistWorkflow starts.
- L25 _private prototype_ `void ShowNotification(FAskUserToPersistWorkflow& InWorkflow) const;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/Views/BrowserViews.h` (Private)


#### struct `UE::SandboxedEditing::FBrowserViews`  
`struct FBrowserViews`  
_L21-52_
- desc: Holds the views for Sandboxed Editing. This is mostly for handling displaying notifications, spawning dialogues, etc. requested by view models. @note Only contains "explicit" views. Of course, widgets, e.g. SSandboxedEditingRoot, implicitly classify as views. Those are not held here though.
- L24 _public member_ `const TSharedRef<FAskUserAboutDirtyPackagesView> AskUserAboutDirtyPackagesView;` — When leaving with in-memory changes, this displays a toaster.
- L27 _public member_ `const TSharedRef<FAskUserToPersistView> AskUserToPersistView;` — When leaving, this asks the user whether they want to persist files.
- L30 _public member_ `const TSharedRef<FPersistSandboxView> PersistSandboxView;` — Visualizes FPersistSandboxWorkflow.
- L33 _public member_ `const TSharedRef<FRenameWorkflowView> RenameWorkflowView;` — Displays a notification when a sandbox is renamed.
- L36 _public member_ `const TSharedRef<FExportView> ExportView;` — Presents the UI for exporting sandboxes.
- L38 _public member_ `const TSharedRef<FImportView> ImportView;` — Presents the UI for importing sandboxes.
- L40 _public function_ `explicit FBrowserViews( const TSharedRef<FSandboxControlsViewModel>& InControlsViewModel, const TSharedRef<FPersistSandboxViewModel>& InPersistViewModel, const TSharedRef<FLeaveSandboxViewModel>& InLeaveViewModel ) : AskUserAboutDirtyPackagesView(MakeShared<FAskUserAboutDirtyPackagesView>(InLeaveViewModel)) , AskUserToPersistView(MakeShared<FAskUserToPersistView>(InLeaveViewModel)) , PersistSandboxView(MakeShared<FPersistSandboxView>(InPersistViewModel)) , RenameWorkflowView(MakeShared<FRenameWorkflowView>(InControlsViewModel)) , ExportView(MakeShared<FExportView>(InControlsViewModel)) , ImportView(MakeShared<FImportView>(InControlsViewModel))`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/Views/Menu/FileStateMenuUtils.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SandboxedEditing` (scope `UE`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace SandboxedEditing` (scope `UE`)
- L13 _namespace_ `namespace FileStateMenu` (scope `UE::SandboxedEditing`)
- L16 _prototype_ `TArray<FString> TransformSelectedItems(const TSharedRef<SFileStateListView>& InListView);` (scope `UE::SandboxedEditing::FileStateMenu`) — @return Gets the non-sandbox file paths selected in InListView.
- L18 _prototype_ `TAttribute<TArray<FString>> MakeSelectedFilesAttribute(const TSharedRef<SFileStateListView>& InListView);` (scope `UE::SandboxedEditing::FileStateMenu`) — @return Attribute returning result of TransformSelectedItems.
- L21 _prototype_ `void AppendMenu(FMenuBuilder& InMenuBuilder);` (scope `UE::SandboxedEditing::FileStateMenu`) — Appends entries that are shared across all menus.

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/Views/PersistSandboxView.h` (Private)


#### class `UE::SandboxedEditing::FPersistSandboxView`  
`class FPersistSandboxView : public FNoncopyable`  
_L15-30_
- inherits: `FNoncopyable`
- desc: Visualizes FPersistSandboxWorkflow.
- L18 _public prototype_ `explicit FPersistSandboxView(const TSharedRef<FPersistSandboxViewModel>& InPersistViewModel);`
- L19 _public prototype_ `~FPersistSandboxView();`
- L24 _private member_ `const TSharedRef<FPersistSandboxViewModel> PersistViewModel;` — Notifies when FPersistSandboxWorkflow starts.
- L27 _private prototype_ `void ShowPersistWorkflow(FPersistSandboxWorkflow& InWorkflow, TConstArrayView<FString> InPreSelectedFiles) const;` — Shows a modal in which the user can select the files to persist.
- L29 _private prototype_ `void ShowPersistSummary(const FileSandboxUI::FPersistSummary& InSummary) const;` — Shows a notification summarizing the result of the operation.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/Views/RenameWorkflowView.h` (Private)


#### class `UE::SandboxedEditing::FRenameWorkflowView`  
`class FRenameWorkflowView : public FNoncopyable`  
_L14-29_
- inherits: `FNoncopyable`
- desc: Displays a notification when a sandbox is renamed.
- L18 _public prototype_ `explicit FRenameWorkflowView(const TSharedRef<FSandboxControlsViewModel>& InControlsViewModel);`
- L19 _public prototype_ `~FRenameWorkflowView();`
- L23 _private member_ `const TSharedRef<FSandboxControlsViewModel> ControlsViewModel;`
- L26 _private prototype_ `void OnStartRenameOperation(FRenameSandboxWorkflow& InWorkflow) const;` — Subscribes OnSandboxRenamed.
- L28 _private prototype_ `void OnSandboxRenamed(const FString& InOldName, const FString& InNewName) const;` — Shows a slate notification that the sandbox was renamed.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/Views/Transfer/ExportView.h` (Private)


#### class `UE::SandboxedEditing::FExportView`  
`class FExportView : public FNoncopyable`  
_L14-28_
- inherits: `FNoncopyable`
- desc: Presents dialogues for exporting sandboxes.
- L18 _public prototype_ `explicit FExportView(const TSharedRef<FSandboxControlsViewModel>& InViewModel);`
- L19 _public prototype_ `~FExportView();`
- L24 _private member_ `const TSharedRef<FSandboxControlsViewModel> ViewModel;` — Produces the export workflow that the view binds to.
- L26 _private prototype_ `void OnExportWorkflowStarted(FExportWorkflow& InWorkflow);`
- L27 _private prototype_ `void OnExportEnded(const FExportWorkflowResult& InResult);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/Views/Transfer/ImportView.h` (Private)


#### class `UE::SandboxedEditing::FImportView`  
`class FImportView : public FNoncopyable`  
_L16-30_
- inherits: `FNoncopyable`
- desc: Presents dialogues for importing sandboxes.
- L20 _public prototype_ `explicit FImportView(const TSharedRef<FSandboxControlsViewModel>& InViewModel);`
- L21 _public prototype_ `~FImportView();`
- L26 _private member_ `const TSharedRef<FSandboxControlsViewModel> ViewModel;` — Produces the import workflow that the view binds to.
- L28 _private prototype_ `void OnImportWorkflowStarted(FImportWorkflow& InWorkflow);`
- L29 _private prototype_ `void OnImportEnded(const FImportWorkflowResult& InImportResult);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/Widgets/SSandboxedEditingRoot.h` (Private)


#### class `UE::SandboxedEditing::SSandboxedEditingRoot`  
`class SSandboxedEditingRoot : public SCompoundWidget`  
_L25-71_
- inherits: `SCompoundWidget`
- desc: Root widget for Sandboxed Editing. It updates it content depending on whether the engine is sandboxed.
- L29 _public function_ `SLATE_BEGIN_ARGS(SSandboxedEditingRoot)`
- L31 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FUICommandList>, CommandList) SLATE_ARGUMENT(FSandboxColumnFactoryMap, SandboxColumnFactories) SLATE_ARGUMENT(FFileStateColumnFactoryMap, BrowserFileActionsColumnFactories) SLATE_ARGUMENT(FFileStateColumnFactoryMap, ActiveFileStateColumnsFactories) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FBrowserViewModels& InViewModels);` — The command list to bind selection-based commands to.
- L45 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L51 _private member_ `TSharedPtr<SSandboxedEditingBrowser> Browser;` — The sandbox editing browser. Shown as long as not in any sandbox.
- L54 _private member_ `TSharedPtr<FActiveSandboxTrackerViewModel> ActiveSandboxTrackerViewModel;` — Knows when the active sandbox changes.
- L56 _private member_ `TSharedPtr<FileSandboxUI::IExternalSandboxActiveViewModel> ExternalSandboxViewModel;` — Knows when an external sandbox is active.
- L59 _private member_ `TOptional<SActiveSandbox::FViewModels> ActiveSandboxViewModels;` — The view models required to construct the active sandbox widget. Set once Construct has been called.
- L61 _private member_ `TAttribute<FFileStateColumnFactoryMap> ActiveFileStateColumnsAttr;` — Used to build the columns for the file actions list for the active sandbox.
- L64 _private member_ `TSharedPtr<FUICommandList> CommandBindings;` — Command bindings for the browser UI.
- L67 _private prototype_ `void UpdateWidgetContent();` — Sets the widget content to the browser or active session widget depending on whether we're in a sandbox.
- L69 _private prototype_ `void ShowActiveSandbox();`
- L70 _private prototype_ `void ShowBrowser();`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace FileSandboxUI` (scope `UE`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/Widgets/Sandboxed/SActiveSandbox.h` (Private)


#### class `UE::SandboxedEditing::SActiveSandbox`  
`class SActiveSandbox : public SCompoundWidget`  
_L21-68_
- inherits: `SCompoundWidget`
- desc: Widget displayed while in a sandbox
- L48 _public function_ `SLATE_BEGIN_ARGS(SActiveSandbox)`
- L50 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FUICommandList>, CommandList) SLATE_ARGUMENT(FFileStateColumnFactoryMap, ColumnFactories) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FViewModels& InViewModels);` — The command list to bind commands to.
- L61 _private member_ `TSharedPtr<FActiveSandboxDetailsViewModel> ActiveSandboxViewModel;` — Details about the active sandbox.
- L64 _private prototype_ `TSharedRef<SWidget> MakeDescription(const FViewModels& InViewModels);` — Make the description widget.
- L67 _private prototype_ `TSharedRef<SWidget> MakeFileChangesContent(const FArguments& InArgs, const FViewModels& InViewModels);` — Makes the widget that displays the files changed by the current sandbox.

#### struct `UE::SandboxedEditing::SActiveSandbox::FViewModels`  
`struct FViewModels`  
_L25-46_
- L27 _public member_ `TSharedRef<FActiveSandboxDetailsViewModel> ActiveSandboxViewModel;`
- L28 _public member_ `TSharedRef<FSandboxMetaDataViewModel> MetaDataViewModel;`
- L29 _public member_ `TSharedRef<FActiveSandboxFileStateViewModel> ActiveSandboxFileStateModel;`
- L30 _public member_ `TSharedRef<FFilterFileStateViewModel> FilterActiveSandboxFileStateModel;`
- L31 _public member_ `TSharedRef<FPersistSandboxViewModel> PersistViewModel;`
- L33 _public function_ `explicit FViewModels( const TSharedRef<FActiveSandboxDetailsViewModel>& InActiveSandboxViewModel, const TSharedRef<FSandboxMetaDataViewModel>& InMetaDataViewModel, const TSharedRef<FActiveSandboxFileStateViewModel>& InActiveSandboxFileStateModel, const TSharedRef<FFilterFileStateViewModel>& InFilterActiveSandboxFileStateModel, const TSharedRef<FPersistSandboxViewModel>& InPersistViewModel ) : ActiveSandboxViewModel(InActiveSandboxViewModel) , MetaDataViewModel(InMetaDataViewModel) , ActiveSandboxFileStateModel(InActiveSandboxFileStateModel) , FilterActiveSandboxFileStateModel(InFilterActiveSandboxFileStateModel) , PersistViewModel(InPersistViewModel)`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/Widgets/Sandboxed/SActiveSandboxFileChanges.h` (Private)


#### class `UE::SandboxedEditing::SActiveSandboxFileChanges`  
`class SActiveSandboxFileChanges : public SCompoundWidget`  
_L21-83_
- inherits: `SCompoundWidget`
- desc: Displays the file changes of the active sandbox.
- L45 _public function_ `SLATE_BEGIN_ARGS(SActiveSandboxFileChanges)`
- L47 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FUICommandList>, CommandList) SLATE_ARGUMENT(FFileStateColumnFactoryMap, ColumnFactories) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FViewModels& InViewModels);` — The command list to bind commands to.
- L58 _private member_ `TSharedPtr<FUICommandList> CommandList;` — Used for building the right-click menu.
- L60 _private member_ `TSharedPtr<FPersistSandboxViewModel> PersistViewModel;` — Used for binding right-click persist commands.
- L63 _private member_ `TSharedPtr<SFilterableFileStateListView> FileActionWidget;` — Displays the file changes made in this sandbox.
- L66 _private member_ `TUniquePtr<FFileStateCommandBindings> FileStateCommandBindings;` — Common entries for FileActionWidget.
- L69 _private prototype_ `TSharedPtr<SWidget> MakeFileChangeContextMenu();` — @return The context menu for FileActionWidget.
- L72 _private prototype_ `void BindCommands(const FViewModels& InViewModels);` — Binds the commands that this widget introduces.
- L75 _private prototype_ `void HandlePersistSelected() const;` — Brings up the persist dialogue with the current selection pre-selected.
- L77 _private prototype_ `bool CanPersistSelected() const;` — @return Whether the persist dialogue can be created at this time
- L80 _private prototype_ `void RevertSelection() const;` — Handles command for reverting current selection.
- L82 _private prototype_ `bool CanRevertSelection() const;` — Whether there is a selection, and it can be reverted.

#### struct `UE::SandboxedEditing::SActiveSandboxFileChanges::FViewModels`  
`struct FViewModels`  
_L25-43_
- L27 _public member_ `TSharedRef<FActiveSandboxDetailsViewModel> ActiveSandboxViewModel;`
- L28 _public member_ `TSharedRef<IFileStateViewModel> FileActionsViewModel;`
- L29 _public member_ `TSharedRef<FFilterFileStateViewModel> FilterViewModel;`
- L30 _public member_ `TSharedRef<FPersistSandboxViewModel> PersistViewModel;`
- L32 _public function_ `explicit FViewModels( const TSharedRef<FActiveSandboxDetailsViewModel>& InActiveSandboxViewModel, const TSharedRef<IFileStateViewModel>& InFileActionsViewModel, const TSharedRef<FFilterFileStateViewModel>& InFilterViewModel, const TSharedRef<FPersistSandboxViewModel>& InPersistViewModel ) : ActiveSandboxViewModel(InActiveSandboxViewModel) , FileActionsViewModel(InFileActionsViewModel) , FilterViewModel(InFilterViewModel) , PersistViewModel(InPersistViewModel)`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/Widgets/Sandboxed/SActiveSandboxToolbar.h` (Private)


#### class `UE::SandboxedEditing::SActiveSandboxToolbar`  
`class SActiveSandboxToolbar : public SCompoundWidget`  
_L15-36_
- inherits: `SCompoundWidget`
- desc: Widget displayed on the top while in an active sandbox.
- L19 _public function_ `SLATE_BEGIN_ARGS(SActiveSandboxToolbar)`
- L21 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FUICommandList>, CommandList) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FActiveSandboxDetailsViewModel>& InActiveSandboxViewModel);` — The command list to bind commands to.
- L29 _private member_ `TSharedPtr<FActiveSandboxDetailsViewModel> ActiveSandboxViewModel;` — Details about the active sandbox.
- L32 _private prototype_ `TSharedRef<SWidget> MakeNameWidget() const;` — @return Widget displaying the active sandbox name.
- L35 _private prototype_ `FText GetLeaveButtonToolTipText() const;` — @return Tooltip text to display for the leave button

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/Widgets/Sandboxed/SPersistOperationWidget.h` (Private)


#### class `UE::SandboxedEditing::SPersistOperationWidget`  
`class SPersistOperationWidget : public SCompoundWidget`  
_L14-33_
- inherits: `SCompoundWidget`
- desc: Displays all UI for persisting a sandbox
- L18 _public function_ `SLATE_BEGIN_ARGS(SPersistOperationWidget)`
- L19 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FPersistOperationViewModel>& InViewModel);`
- L26 _private member_ `TSharedPtr<FPersistOperationViewModel> ViewModel;` — Gets the view model being visualized.
- L28 _private prototype_ `bool IsPersistButtonEnabled() const;`
- L29 _private prototype_ `TSharedRef<SWidget> MakeButtonArea();`
- L31 _private prototype_ `FReply OnClickPersist() const;`
- L32 _private prototype_ `FReply OnClickCancel() const;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/Widgets/Shared/FileState/Columns/ActionFileStateColumn.h` (Private)


#### class `UE::SandboxedEditing::FActionFileStateColumn`  
`class FActionFileStateColumn : public IFileStateColumnBehavior, public IFileStateColumnWidgetFactory`  
_L10-24_
- inherits: `IFileStateColumnBehavior,IFileStateColumnWidgetFactory`
- L15 _public prototype_ `virtual void PopulateSearchTerms(const TSharedPtr<FFileStateItem>& InRowData, TArray<FString>& OutSearchTerms) const override;`
- L16 _public function_ `virtual bool CanSort() const override`
- L17 _public prototype_ `virtual bool SortBy(const TSharedPtr<FFileStateItem>& Lhs, const TSharedPtr<FFileStateItem>& Rhs, EColumnSortMode::Type SortMode) const override;`
- L21 _public prototype_ `virtual SHeaderRow::FColumn::FArguments MakeColumnArguments() override;`
- L22 _public prototype_ `virtual TSharedRef<SWidget> MakeColumnWidget(const FMakeFileStateColumnWidgetArgs& InArgs) override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/Widgets/Shared/FileState/Columns/PathFileStateColumn.h` (Private)


#### class `UE::SandboxedEditing::FPathFileStateColumn`  
`class FPathFileStateColumn : public IFileStateColumnBehavior, public IFileStateColumnWidgetFactory`  
_L11-25_
- inherits: `IFileStateColumnBehavior,IFileStateColumnWidgetFactory`
- desc: Displays the file path to the file.
- L16 _public prototype_ `virtual void PopulateSearchTerms(const TSharedPtr<FFileStateItem>& InRowData, TArray<FString>& OutSearchTerms) const override;`
- L17 _public function_ `virtual bool CanSort() const override`
- L18 _public prototype_ `virtual bool SortBy(const TSharedPtr<FFileStateItem>& Lhs, const TSharedPtr<FFileStateItem>& Rhs, EColumnSortMode::Type SortMode) const override;`
- L22 _public prototype_ `virtual SHeaderRow::FColumn::FArguments MakeColumnArguments() override;`
- L23 _public prototype_ `virtual TSharedRef<SWidget> MakeColumnWidget(const FMakeFileStateColumnWidgetArgs& InArgs) override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/Widgets/Shared/FileState/Columns/PersistFileStateColumn.h` (Private)


#### class `UE::SandboxedEditing::FPersistFileStateColumn`  
`class FPersistFileStateColumn : public IFileStateColumnBehavior, public IFileStateColumnWidgetFactory`  
_L12-39_
- inherits: `IFileStateColumnBehavior,IFileStateColumnWidgetFactory`
- L16 _public prototype_ `explicit FPersistFileStateColumn(const TSharedRef<FPersistOperationViewModel>& InPersistViewModel);`
- L19 _public function_ `virtual void PopulateSearchTerms(const TSharedPtr<FFileStateItem>& InRowData, TArray<FString>& OutSearchTerms) const override`
- L20 _public function_ `virtual bool CanSort() const override`
- L21 _public function_ `virtual bool SortBy(const TSharedPtr<FFileStateItem>& Lhs, const TSharedPtr<FFileStateItem>& Rhs, EColumnSortMode::Type SortMode) const override`
- L25 _public prototype_ `virtual SHeaderRow::FColumn::FArguments MakeColumnArguments() override;`
- L26 _public prototype_ `virtual TSharedRef<SWidget> MakeColumnWidget(const FMakeFileStateColumnWidgetArgs& InArgs) override;`
- L32 _private member_ `const TSharedRef<FPersistOperationViewModel> PersistViewModel;` — Used to set whether an item should be persisted
- L34 _private prototype_ `ECheckBoxState GetToggleRootSelectedState() const;`
- L35 _private prototype_ `void OnToggleRootSelectedCheckBox(ECheckBoxState InNewState) const;`
- L37 _private prototype_ `ECheckBoxState GetItemCheckBoxState(int32 InIndex) const;`
- L38 _private prototype_ `void SetItemCheckBoxState(ECheckBoxState InNewState, int32 InIndex) const;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/Widgets/Shared/FileState/Columns/TimestampFileStateColumn.h` (Private)


#### class `UE::SandboxedEditing::FTimestampFileStateColumn`  
`class FTimestampFileStateColumn : public IFileStateColumnBehavior, public IFileStateColumnWidgetFactory`  
_L11-25_
- inherits: `IFileStateColumnBehavior,IFileStateColumnWidgetFactory`
- desc: Displays the timestamp of the sandboxed file change.
- L16 _public prototype_ `virtual void PopulateSearchTerms(const TSharedPtr<FFileStateItem>& InRowData, TArray<FString>& OutSearchTerms) const override;`
- L17 _public function_ `virtual bool CanSort() const override`
- L18 _public prototype_ `virtual bool SortBy(const TSharedPtr<FFileStateItem>& Lhs, const TSharedPtr<FFileStateItem>& Rhs, EColumnSortMode::Type SortMode) const override;`
- L22 _public prototype_ `virtual SHeaderRow::FColumn::FArguments MakeColumnArguments() override;`
- L23 _public prototype_ `virtual TSharedRef<SWidget> MakeColumnWidget(const FMakeFileStateColumnWidgetArgs& InArgs) override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/Widgets/Shared/FileState/SFileStateFilters.h` (Private)


#### class `UE::SandboxedEditing::SFileStateFilters`  
`class SFileStateFilters : public SCompoundWidget`  
_L13-29_
- inherits: `SCompoundWidget`
- desc: Displays the widgets required to filter file actions, i.e. FFilterFileStateViewModel.
- L17 _public function_ `SLATE_BEGIN_ARGS(SFileStateFilters)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FFilterFileStateViewModel>& InFilterModel);`
- L25 _private member_ `TSharedPtr<FFilterFileStateViewModel> FilterViewModel;` — Knows how to filter file state items.
- L27 _private prototype_ `void OnSearchTextChanged(const FText& Text) const;`
- L28 _private prototype_ `void OnSearchTextCommitted(const FText& InFilterText, ETextCommit::Type Arg);`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/Widgets/Shared/FileState/SFileStateListRow.h` (Private)


#### class `UE::SandboxedEditing::SFileStateListRow`  
`class SFileStateListRow : public SMultiColumnTableRow<TSharedPtr<FFileStateItem>>`  
_L15-45_
- inherits: `SMultiColumnTableRow<TSharedPtr<FFileStateItem>>`
- L19 _public function_ `SLATE_BEGIN_ARGS(SFileStateListRow)`
- L21 _public prototype_ `SLATE_ARGUMENT(FFileStateColumnFactoryMap, ColumnFactories) SLATE_ARGUMENT(FMargin, Padding) SLATE_ATTRIBUTE(FText, HighlightText) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FFileStateItem>& InItem, const TSharedRef<STableViewBase>& InOwnerTable);` — Used to build the columns.
- L32 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& InColumnName) override;`
- L38 _private member_ `TSharedPtr<FFileStateItem> Item;` — The item that is being displayed by this row.
- L41 _private member_ `FFileStateColumnFactoryMap ColumnFactoryMap;` — Used to build the columns.
- L44 _private member_ `TAttribute<FText> HighlightText;` — The text to highlight in the columns.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/Widgets/Shared/FileState/SFileStateListView.h` (Private)


#### class `UE::SandboxedEditing::SFileStateListView`  
`class SFileStateListView : public SCompoundWidget`  
_L20-77_
- inherits: `SCompoundWidget`
- desc: Displays a list view FFileStateItem provided by IFileStateViewModel.
- L24 _public function_ `SLATE_BEGIN_ARGS(SFileStateListView)`
- L27 _public prototype_ `SLATE_ARGUMENT(FFileStateColumnFactoryMap, ColumnFactories) SLATE_ATTRIBUTE(FText, HighlightText) SLATE_ATTRIBUTE(FText, OverrideOverlayText) SLATE_ARGUMENT(FText, NoChangesText) SLATE_EVENT(FOnContextMenuOpening, OnContextMenuOpening) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<IFileStateViewModel>& InViewModel);` — Used to build the columns.
- L47 _public prototype_ `TArray<TSharedPtr<FFileStateItem>> GetSelectedFiles() const;` — @return Selected items.
- L52 _private member_ `TSharedPtr<IFileStateViewModel> ViewModel;` — The view model being displayed
- L55 _private member_ `TSharedPtr<SListView<TSharedPtr<FFileStateItem>>> ListView;` — The list view displaying the items.
- L58 _private member_ `TMap<FName, TSharedRef<IFileStateColumnWidgetFactory>> ColumnFactories;` — Used to build the columns.
- L61 _private member_ `TAttribute<FText> HighlightText;` — The text to highlight in the columns.
- L63 _private member_ `TAttribute<FText> OverrideOverlayText;` — Text to display in the content, e.g. when all items are filtered out. Overrides the text when the attribute returns non-empty.
- L65 _private member_ `FText NoChangesText;` — The text to display when there are no changes to display.
- L68 _private prototype_ `TSharedRef<SHeaderRow> MakeHeaderRow();` — @return The header row to display at the top of the table
- L71 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FFileStateItem> InItem, const TSharedRef<STableViewBase>& InOwnerTable) const;` — @return Widget for the items
- L74 _private prototype_ `FText GetOverlayText() const;` — @return Text to display in the content, e.g. when there's no items.
- L76 _private prototype_ `EVisibility GetOverlayTextVisibility() const;` — @return The visibility of the overlay text

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/Widgets/Shared/FileState/SFilterableFileStateListView.h` (Private)


#### class `UE::SandboxedEditing::SFilterableFileStateListView`  
`class SFilterableFileStateListView : public SCompoundWidget`  
_L20-60_
- inherits: `SCompoundWidget`
- desc: Vertical arrangement of a filter section (search bar) and SFileStateListView.
- L24 _public function_ `SLATE_BEGIN_ARGS(SFilterableFileStateListView)`
- L27 _public prototype_ `SLATE_ARGUMENT(FFileStateColumnFactoryMap, ColumnFactories) SLATE_ARGUMENT(FText, NoChangesText) SLATE_EVENT(FOnContextMenuOpening, OnContextMenuOpening) SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TSharedRef<IFileStateViewModel>& InFileActionsViewModel, const TSharedRef<FFilterFileStateViewModel>& InFilterViewModel );` — Used to build the columns.
- L46 _public function_ `const TSharedPtr<SFileStateListView>& GetListView() const` — @return List view displaying the items
- L51 _private member_ `TSharedPtr<IFileStateViewModel> FileActionViewModel;` — Used to generate the override overlay text.
- L53 _private member_ `TSharedPtr<FFilterFileStateViewModel> FilterViewModel;` — Used to generate the override overlay text.
- L56 _private member_ `TSharedPtr<SFileStateListView> FileStateWidget;` — Displays the items.
- L59 _private prototype_ `FText GetOverrideOverlayText() const;` — @return Text indicating that all items are filtered out, or empty.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/Widgets/Shared/SSandboxDescription.h` (Private)


#### class `UE::SandboxedEditing::SSandboxDescription`  
`class SSandboxDescription : public SCompoundWidget`  
_L17-41_
- inherits: `SCompoundWidget`
- desc: Allows editing a description. The description is displayed in an expandable area to save space.
- L21 _public function_ `SLATE_BEGIN_ARGS(SSandboxDescription)`
- L23 _public prototype_ `SLATE_ATTRIBUTE(TOptional<FString>, SandboxPath) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FSandboxMetaDataViewModel>& InMetaDataViewModel);` — Path to the sandbox for which the description is being edited. Returning unset disables the edit box.
- L31 _private member_ `TSharedPtr<FSandboxMetaDataViewModel> MetaDataViewModel;` — Used to edit the description.
- L34 _private member_ `TAttribute<TOptional<FString>> SandboxPathAttr;` — Path to the sandbox for which the description is being edited.
- L37 _private member_ `TSharedPtr<SMultiLineEditableTextBox> DescriptionTextCtrl;` — Contains the description text
- L39 _private prototype_ `FText GetDescription() const;`
- L40 _private prototype_ `void OnDescriptionCommitted(const FText& InNewDescription, ETextCommit::Type InType) const;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/Widgets/Unsandboxed/GenericBrowser/SSessionBrowserFrame.h` (Private)


#### class `UE::SandboxedEditing::SSessionBrowserFrame`  
`class SSessionBrowserFrame : public SCompoundWidget`  
_L26-50_
- inherits: `SCompoundWidget`
- desc: Generic widget that lays out widgets related for session management. The concept of a session is kept abstract and depends on the code that uses this widget. For now only used for Sandboxed Editing. In the future, it should be used across Multi-User, Multi-User Server, and Sandboxed editing. The purpose is to have a central place that organizes the layout of the specific widgets, and avoid code duplication. The follow elements are laid out: - Controls: buttons to control the sessions - Search box: filtering the sessions - Tree / List view: displays the sessions - Extra info: displays more info about the session
- L30 _public function_ `SLATE_BEGIN_ARGS(SSessionBrowserFrame)`
- L31 _public prototype_ `SLATE_NAMED_SLOT(FArguments, ControlContent) SLATE_NAMED_SLOT(FArguments, SearchContent) SLATE_NAMED_SLOT(FArguments, SessionContent) SLATE_NAMED_SLOT(FArguments, DetailsContent) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L42 _private prototype_ `TSharedRef<SVerticalBox> CreateContent(const FArguments& InArgs);` — Creates the layout
- L45 _private prototype_ `void AppendControlWidget(const FArguments& InArgs, const TSharedRef<SVerticalBox>& Content);` — Optionally adds the controls (above search), if specified by args.
- L47 _private prototype_ `void AppendSearchWidget(const FArguments& InArgs, const TSharedRef<SVerticalBox>& Content);` — Optionally adds the search widget (above session content), if specified by args.
- L49 _private prototype_ `void AppendDetailsWidget(const FArguments& InArgs, const TSharedRef<SSplitter>& Content);` — Optionally adds the controls (below session content), if specified by args.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/Widgets/Unsandboxed/List/Columns/DescriptionSandboxColumn.h` (Private)


#### class `UE::SandboxedEditing::FDescriptionSandboxColumn`  
`class FDescriptionSandboxColumn : public ISandboxColumnBehavior, public ISandboxColumnWidgetFactory`  
_L11-23_
- inherits: `ISandboxColumnBehavior,ISandboxColumnWidgetFactory`
- desc: Displays the sandbox description.
- L16 _public prototype_ `virtual void PopulateSearchTerms(const TSharedPtr<FSandboxListItem>& InRowData, TArray<FString>& OutSearchTerms) const override;`
- L20 _public prototype_ `virtual SHeaderRow::FColumn::FArguments MakeColumnArguments() override;`
- L21 _public prototype_ `virtual TSharedRef<SWidget> MakeColumnWidget(const FMakeSandboxColumnWidgetArgs& InArgs) override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/Widgets/Unsandboxed/List/Columns/LastModifiedSandboxColumn.h` (Private)


#### class `UE::SandboxedEditing::FLastModifiedSandboxColumn`  
`class FLastModifiedSandboxColumn : public ISandboxColumnBehavior, public ISandboxColumnWidgetFactory`  
_L11-23_
- inherits: `ISandboxColumnBehavior,ISandboxColumnWidgetFactory`
- desc: Displays when the sandbox was last modified.
- L16 _public prototype_ `virtual void PopulateSearchTerms(const TSharedPtr<FSandboxListItem>& InRowData, TArray<FString>& OutSearchTerms) const override;`
- L20 _public prototype_ `virtual SHeaderRow::FColumn::FArguments MakeColumnArguments() override;`
- L21 _public prototype_ `virtual TSharedRef<SWidget> MakeColumnWidget(const FMakeSandboxColumnWidgetArgs& InArgs) override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/Widgets/Unsandboxed/List/Columns/NameSandboxColumn.h` (Private)


#### class `UE::SandboxedEditing::FNameSandboxColumn`  
`class FNameSandboxColumn : public ISandboxColumnBehavior, public ISandboxColumnWidgetFactory`  
_L13-32_
- inherits: `ISandboxColumnBehavior,ISandboxColumnWidgetFactory`
- desc: Displays the sandbox name.
- L17 _public prototype_ `explicit FNameSandboxColumn(const TSharedRef<FSandboxControlsViewModel>& InRenameViewModel);`
- L20 _public prototype_ `virtual void PopulateSearchTerms(const TSharedPtr<FSandboxListItem>& InRowData, TArray<FString>& OutSearchTerms) const override;`
- L24 _public prototype_ `virtual SHeaderRow::FColumn::FArguments MakeColumnArguments() override;`
- L25 _public prototype_ `virtual TSharedRef<SWidget> MakeColumnWidget(const FMakeSandboxColumnWidgetArgs& InArgs) override;`
- L31 _private member_ `const TSharedRef<FSandboxControlsViewModel> RenameViewModel;` — View model used to rename sandboxes.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/Widgets/Unsandboxed/List/Columns/VersionSandboxColumn.h` (Private)


#### class `UE::SandboxedEditing::FVersionSandboxColumn`  
`class FVersionSandboxColumn : public ISandboxColumnBehavior, public ISandboxColumnWidgetFactory`  
_L11-23_
- inherits: `ISandboxColumnBehavior,ISandboxColumnWidgetFactory`
- desc: Displays the engine version this sandbox was last used in.
- L16 _public prototype_ `virtual void PopulateSearchTerms(const TSharedPtr<FSandboxListItem>& InRowData, TArray<FString>& OutSearchTerms) const override;`
- L20 _public prototype_ `virtual SHeaderRow::FColumn::FArguments MakeColumnArguments() override;`
- L21 _public prototype_ `virtual TSharedRef<SWidget> MakeColumnWidget(const FMakeSandboxColumnWidgetArgs& InArgs) override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/Widgets/Unsandboxed/List/DummySandboxItem.h` (Private)


#### enum `UE::SandboxedEditing::EDummySandboxItemType`  
`enum class EDummySandboxItemType : uint8`  
_L13-16_
- desc: The intent of the dummy sandbox item.
- L15 _public enumerator_ `CreateSandbox`

#### struct `UE::SandboxedEditing::FDummySandboxItemInfo`  
`struct FDummySandboxItemInfo`  
_L22-31_
- desc: Holds info about a FSandboxListItem added to the SListView but does not really represent a real sandbox. It's a way to get the SListView to display row widget.
- L24 _public member_ `const TSharedRef<FSandboxListItem> Item;`
- L25 _public member_ `const EDummySandboxItemType Type;`
- L27 _public function_ `explicit FDummySandboxItemInfo(const TSharedRef<FSandboxListItem>& InItem, EDummySandboxItemType InType) : Item(InItem) , Type(InType)`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/Widgets/Unsandboxed/List/SCreateSandboxListRow.h` (Private)


#### class `UE::SandboxedEditing::SCreateSandboxListRow`  
`class SCreateSandboxListRow : public SMultiColumnTableRow<TSharedPtr<FSandboxListItem>>`  
_L17-62_
- inherits: `SMultiColumnTableRow<TSharedPtr<FSandboxListItem>>`
- desc: A row in the SSandboxListView for creating a new sandbox.
- L21 _public function_ `SLATE_BEGIN_ARGS(SCreateSandboxListRow)`
- L23 _public prototype_ `SLATE_ATTRIBUTE(FSandboxCreationWorkflow*, Workflow) SLATE_ARGUMENT(FMargin, Padding) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable);` — Gets the creation workflow this widget displays.
- L31 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L34 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& InColumnName) override;`
- L40 _private member_ `TAttribute<FSandboxCreationWorkflow*> WorkflowAttr;` — Gets the creation workflow this widget displays.
- L43 _private member_ `TSharedPtr<SEditableTextBox> NameWidget;` — Name widget
- L46 _private member_ `bool bHasTakenInitialFocus = false;` — Whether keyboard focus has been set to the editable text already.
- L49 _private prototype_ `TSharedRef<SWidget> CreateNameWidget();` — @return The widget for editing the name.
- L51 _private prototype_ `TSharedRef<SWidget> CreateButtons();` — @return Confirm and cancel buttons.
- L54 _private prototype_ `void OnSandboxNameCommitted(const FText& InNewText, ETextCommit::Type InCommitType);` — Creates the sandbox if enter is pressed.
- L56 _private prototype_ `FReply OnKeyDownHandler(const FGeometry& Geometry, const FKeyEvent& InKeyEvent);` — Handles cancelling when esc is pressed.
- L58 _private prototype_ `void OnSandboxNameChanged(const FText& InNewText);` — Handles displaying an error.
- L61 _private function_ `FSandboxCreationWorkflow* GetWorkflow() const` — @return Gets the workflow being displayed.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/Widgets/Unsandboxed/List/SSandboxListRow.h` (Private)


#### class `UE::SandboxedEditing::SSandboxListRow`  
`class SSandboxListRow : public SMultiColumnTableRow<TSharedPtr<FSandboxListItem>>`  
_L16-51_
- inherits: `SMultiColumnTableRow<TSharedPtr<FSandboxListItem>>`
- desc: A row in the SSandboxListView displaying a single sandbox.
- L20 _public function_ `SLATE_BEGIN_ARGS(SSandboxListRow)`
- L22 _public prototype_ `SLATE_ARGUMENT(FSandboxColumnFactoryMap, ColumnFactories) SLATE_ATTRIBUTE(FText, HighlightText) SLATE_ATTRIBUTE(bool, IsSelected) SLATE_ARGUMENT(FMargin, Padding) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FSandboxListItem>& InItem, const TSharedRef<STableViewBase>& InOwnerTable);` — The columns we know about
- L36 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& InColumnName) override;`
- L42 _private member_ `FSandboxColumnFactoryMap ColumnFactoryMap;` — Used to build the columns.
- L45 _private member_ `TSharedPtr<FSandboxListItem> Item;` — The displayed item.
- L48 _private member_ `TAttribute<FText> HighlightTextAttr;` — Which text should be highlighted (text search).
- L50 _private member_ `TAttribute<bool> IsSelectedAttr;` — Whether the item is selected.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/Widgets/Unsandboxed/List/SSandboxListView.h` (Private)


#### class `UE::SandboxedEditing::SSandboxListView`  
`class SSandboxListView : public SCompoundWidget`  
_L27-114_
- inherits: `SCompoundWidget`
- desc: A list view containing all the sandboxes.
- L37 _public function_ `SLATE_BEGIN_ARGS(SSandboxListView)`
- L39 _public prototype_ `SLATE_ATTRIBUTE(FText, HighlightText) SLATE_ARGUMENT(FSandboxColumnFactoryMap, ColumnFactories) SLATE_ARGUMENT(TSharedPtr<FUICommandList>, ContextMenuCommandList) SLATE_EVENT(FSandboxDelegate, OnSelectedSandboxChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FViewModels& InViewModels);` — The text to highlight in the columns.
- L54 _public prototype_ `void ForEachSelectedItem(TFunctionRef<EBreakBehavior(const FString& InRootPath)> InCallback) const;` — Enumerates every selected sandbox.
- L56 _public prototype_ `TArray<FString> GetSelectedSandboxRootPaths() const;` — @return Array containing the root path of every sandboxed selected in the list view.
- L59 _public prototype_ `TOptional<FString> GetSelectedItem() const;` — @return The sandbox that is selected if exactly one item is selected.
- L62 _public prototype_ `int32 NumSelected() const;` — @return Number of items selected
- L67 _private member_ `TSharedPtr<FSandboxListViewModel> ListViewModel;` — Knows about the items that are displayed in the browser.
- L69 _private member_ `TSharedPtr<FSandboxControlsViewModel> ControlsViewModel;` — Responds to creation of FSandboxCreationWorkflow by adding a dummy row into the table view.
- L72 _private member_ `FSandboxColumnFactoryMap ColumnFactoryMap;` — Used to build the columns.
- L74 _private member_ `TAttribute<FText> HighlightTextAttr;` — The text to highlight in the columns.
- L76 _private member_ `TSharedPtr<FUICommandList> ContextMenuCommandList;` — The command list to use in the context menu
- L79 _private member_ `TSharedPtr<SListView<TSharedPtr<FSandboxListItem>>> ListView;` — Displays the items.
- L81 _private member_ `TArray<TSharedPtr<FSandboxListItem>> Items;` — The items displayed in the ListView. A copy of the items in ListViewModel plus any dummy row.
- L87 _private member_ `TOptional<FDummySandboxItemInfo> DummyItem;` — Dummy item used to make the ListView display an additional row, e.g. for creating a new sandbox. Usually inserted at the beginning of items while in a creation workflow. It is inserted first so it's displayed on the top.
- L90 _private member_ `FSandboxDelegate OnSelectedSandboxChangedDelegate;` — Invoked when the selected sandbox changes.
- L93 _private prototype_ `TSharedRef<SHeaderRow> MakeHeaderRow();` — @return The header row to display at the top of the table
- L96 _private prototype_ `TSharedRef<SWidget> MakeColumnVisibilityMenu();` — @return Column visibility menu content
- L99 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FSandboxListItem> InItem, const TSharedRef<STableViewBase>& InOwnerTable);` — @return Widget for the items
- L101 _private prototype_ `void OnItemDoubleClicked(TSharedPtr<FSandboxListItem> InItem);` — Loads the clicked sandbox
- L103 _private prototype_ `TSharedPtr<SWidget> OnContextMenuOpening();` — @return Context menu to show
- L106 _private prototype_ `void OnItemsChanged();` — Invoked when the list needs to be regenerated.
- L108 _private prototype_ `void OnCreationWorkflowStarted(FSandboxCreationWorkflow& InWorkflow);`
- L109 _private prototype_ `void OnCreationWorkflowEnded();`
- L111 _private prototype_ `void OnSelectionChanged(TSharedPtr<FSandboxListItem> InItem, ESelectInfo::Type) const;`
- L113 _private prototype_ `EVisibility GetOverlayTextVisibility() const;`

#### struct `UE::SandboxedEditing::SSandboxListView::FViewModels`  
`struct FViewModels`  
_L31-35_
- L33 _public member_ `TSharedRef<FSandboxListViewModel> ListViewModel;`
- L34 _public member_ `TSharedRef<FSandboxControlsViewModel> ControlsViewModel;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace SandboxedEditing` (scope `UE`)
- L24 _delegate_ `DECLARE_DELEGATE_OneParam(FSandboxDelegate, TOptional<FString> );`
- L24 _prototype_ `DECLARE_DELEGATE_OneParam(FSandboxDelegate, TOptional<FString> );` (scope `UE::SandboxedEditing`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/Widgets/Unsandboxed/SBrowserControls.h` (Private)


#### class `UE::SandboxedEditing::SBrowserControls`  
`class SBrowserControls : public SCompoundWidget`  
_L18-36_
- inherits: `SCompoundWidget`
- desc: Controls widget to place on the top section of the browser.
- L22 _public function_ `SLATE_BEGIN_ARGS(SBrowserControls)`
- L24 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FUICommandList>, CommandList) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FSandboxControlsViewModel>& InControlsViewModel);` — The command list to bind selection-based commands to.
- L32 _private member_ `TSharedPtr<FSandboxControlsViewModel> ControlsViewModel;` — View model for mutating
- L35 _private prototype_ `TSharedRef<SWidget> BuildButtonBar(const FArguments& InArgs);` — Builds the button bar

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/Widgets/Unsandboxed/SBrowserFilters.h` (Private)


#### class `UE::SandboxedEditing::SBrowserFilters`  
`class SBrowserFilters : public SCompoundWidget`  
_L12-28_
- inherits: `SCompoundWidget`
- L16 _public function_ `SLATE_BEGIN_ARGS(SBrowserFilters)`
- L17 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FFilterSandboxViewModel>& InFilterSandboxViewModel);`
- L24 _private member_ `TSharedPtr<FFilterSandboxViewModel> FilterSandboxViewModel;` — Knows how to filter sandbox items.
- L26 _private prototype_ `void OnSearchTextChanged(const FText& Text) const;`
- L27 _private prototype_ `void OnSearchTextCommitted(const FText& InFilterText, ETextCommit::Type Arg);`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/Widgets/Unsandboxed/SBrowserSandboxDetails.h` (Private)


#### class `UE::SandboxedEditing::SBrowserSandboxDetails`  
`class SBrowserSandboxDetails : public SCompoundWidget`  
_L18-68_
- inherits: `SCompoundWidget`
- desc: Shows details for a sandbox in the browser widget. Handles showing text such as "select sandbox to view details", etc.
- L22 _public function_ `SLATE_BEGIN_ARGS(SBrowserSandboxDetails)`
- L24 _public prototype_ `SLATE_ATTRIBUTE(TOptional<FString>, SandboxPath) SLATE_ATTRIBUTE(int32, NumSelected) SLATE_ARGUMENT(FFileStateColumnFactoryMap, ColumnFactories) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FSandboxMetaDataViewModel>& InMetaDataViewModel, const TSharedRef<FUnloadedSandboxFileStateViewModel>& InFileActionsViewModel, const TSharedRef<FFilterFileStateViewModel>& InFilterViewModel );` — Path to the selected sandbox.
- L41 _private member_ `TAttribute<int32> NumSelectedAttr;` — Gets the number of selected items. Determines the content displayed.
- L44 _private member_ `TSharedPtr<SFilterableFileStateListView> FileActionsView;` — List of file actions being displayed.
- L47 _private member_ `TUniquePtr<FFileStateCommandBindings> FileStateCommandBindings;` — Common entries for FileActionWidget.
- L50 _private prototype_ `TSharedRef<SWidget> MakeWidgetSwitcherContent( const FArguments& InArgs, const TSharedRef<FSandboxMetaDataViewModel>& InMetaDataViewModel, const TSharedRef<FUnloadedSandboxFileStateViewModel>& InFileActionsViewModel, const TSharedRef<FFilterFileStateViewModel>& InFilterViewModel );` — @return The widget switcher that switches between the different messages and actual details content.
- L57 _private prototype_ `TSharedRef<SWidget> MakeDetailContent( const FArguments& InArgs, const TSharedRef<FSandboxMetaDataViewModel>& InMetaDataViewModel, const TSharedRef<FUnloadedSandboxFileStateViewModel>& InFileActionsViewModel, const TSharedRef<FFilterFileStateViewModel>& InFilterViewModel );` — @return Content to display in the widget switcher
- L65 _private prototype_ `int32 GetWidgetIndex() const;` — @return Index for widget switcher to display. Determined by how many items are selected.
- L67 _private prototype_ `TSharedPtr<SWidget> MakeFileChangeContextMenu();`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/Browser/Widgets/Unsandboxed/SSandboxedEditingBrowser.h` (Private)


#### class `UE::SandboxedEditing::SSandboxedEditingBrowser`  
`class SSandboxedEditingBrowser : public SCompoundWidget`  
_L24-84_
- inherits: `SCompoundWidget`
- desc: Displays a list of sandboxes. Shows content only
- L38 _public function_ `SLATE_BEGIN_ARGS(SSandboxedEditingBrowser)`
- L40 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FUICommandList>, CommandList) SLATE_ARGUMENT(FSandboxColumnFactoryMap, SandboxColumnFactories) SLATE_ARGUMENT(FFileStateColumnFactoryMap, FileActionsColumnFactories) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FViewModels& InViewModels);` — The command list to bind selection-based commands to.
- L52 _private member_ `TSharedPtr<FSandboxControlsViewModel> ControlsViewModel;` — Used for implementing the commands we bind to.
- L54 _private member_ `TSharedPtr<FUnloadedSandboxFileStateViewModel> UnloadedSandboxFileStateViewModel;` — When the selected sandbox changes, we notify this model.
- L57 _private member_ `TSharedPtr<FUICommandList> CommandList;` — Optional command list for selection based commands, such as delete.
- L60 _private member_ `TSharedPtr<SSandboxListView> ListView;` — List view displaying the sandboxes.
- L64 _private prototype_ `void BindCommands();` — Binds the commands only possible with UI, e.g. those that perform an action on the selection.
- L67 _private prototype_ `void HandleDeleteSelection() const;` — Handles deleting the selection.
- L69 _private prototype_ `bool CanDeleteSelection() const;` — @return Whether the current selection can be deleted.
- L72 _private prototype_ `void HandleRenameSelection() const;` — Renames the currently selected. Only does anything if exactly one item is selected. No-op, otherwise.
- L75 _private prototype_ `void HandleExportSandboxes();` — Handles the command for exporting sandboxes.
- L77 _private prototype_ `bool CanExportSandboxes();` — @return Whether any sandboxes are selected in the browser.
- L80 _private prototype_ `void HandleImportSandboxes();` — Handles the command for importing sandboxes.
- L83 _private prototype_ `void OnSelectedSandboxChanged(TOptional<FString> InSandbox) const;` — Notify the UnloadedSandboxFileStateViewModel when the selected sandbox changes.

#### struct `UE::SandboxedEditing::SSandboxedEditingBrowser::FViewModels`  
`struct FViewModels`  
_L28-36_
- L30 _public member_ `TSharedRef<FFilterSandboxViewModel> FilterSandboxViewModel;`
- L31 _public member_ `TSharedRef<FSandboxListViewModel> ListViewModel;`
- L32 _public member_ `TSharedRef<FSandboxControlsViewModel> ControlsViewModel;`
- L33 _public member_ `TSharedRef<FSandboxMetaDataViewModel> MetaDataViewModel;`
- L34 _public member_ `TSharedRef<FUnloadedSandboxFileStateViewModel> UnloadedSandboxFileStateViewModel;`
- L35 _public member_ `TSharedRef<FFilterFileStateViewModel> FilterUnloadedSandboxFileStateViewModel;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/ContentBrowserBadge/ContentBrowserBadgeFeature.h` (Private)


#### class `UE::SandboxedEditing::FContentBrowserBadgeFeature`  
`class FContentBrowserBadgeFeature : public FNoncopyable`  
_L24-69_
- inherits: `FNoncopyable`
- desc: Feature that displays badges on Content Browser items for files modified in the active sandbox. Registers badge generators with the Content Browser to show visual indicators for: - Added files (new files created in sandbox) - Modified files (existing files changed in sandbox) - Deleted files (files removed in sandbox)
- L27 _public prototype_ `explicit FContentBrowserBadgeFeature(TSharedRef<FSandboxSystemModel> InSandboxModel);`
- L28 _public prototype_ `~FContentBrowserBadgeFeature();`
- L32 _private prototype_ `void RegisterBadgeGenerators();` — Registers the badge generators with Content Browser
- L35 _private prototype_ `void UnregisterBadgeGenerators();` — Unregisters the badge generators from Content Browser
- L38 _private prototype_ `void OnSandboxLoaded();` — Called when a sandbox is loaded - registers badge generators
- L41 _private prototype_ `void OnSandboxLeft();` — Called when a sandbox is left - unregisters badge generators
- L44 _private prototype_ `TSharedRef<SWidget> GenerateBadgeIcon(const FAssetData& AssetData);` — Generates the badge icon widget for an asset
- L47 _private prototype_ `TSharedRef<SWidget> GenerateBadgeTooltip(const FAssetData& AssetData);` — Generates the badge tooltip widget for an asset
- L57 _private prototype_ `ESandboxChangeType GetAssetChangeType(const FAssetData& AssetData) const;`
- L61 _private member_ `TSharedRef<FSandboxSystemModel> SandboxModel;` — Model for interacting with the sandbox system
- L64 _private member_ `FDelegateHandle BadgeGeneratorHandle;` — Handle to the registered badge generator
- L67 _private member_ `FDelegateHandle OnLoadSandboxHandle;` — Delegate handles for sandbox lifecycle events
- L68 _private member_ `FDelegateHandle OnLeaveSandboxHandle;`

#### enum `UE::SandboxedEditing::FContentBrowserBadgeFeature::ESandboxChangeType`  
`enum class ESandboxChangeType : uint8`  
_L50-56_
- desc: Checks if the given asset is modified in the active sandbox and returns the change type
- L52 _public enumerator_ `None`
- L53 _public enumerator_ `Added`
- L54 _public enumerator_ `Modified`
- L55 _public enumerator_ `Deleted`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/StatusBar/Commands/StatusBarCommandMappings.h` (Private)


#### class `UE::SandboxedEditing::FStatusBarCommandMappings`  
`class FStatusBarCommandMappings : public FNoncopyable`  
_L15-35_
- inherits: `FNoncopyable`
- desc: Handles all commands for our app. Has the FUICommandList and binds all commands.
- L19 _public prototype_ `explicit FStatusBarCommandMappings(const TSharedRef<FSandboxSystemModel>& InSandboxViewModel);`
- L20 _public prototype_ `~FStatusBarCommandMappings();`
- L22 _public function_ `const TSharedRef<FUICommandList>& GetCommandList() const`
- L27 _private member_ `const TSharedRef<FSandboxSystemModel> SandboxViewModel;` — Required to handle the commands.
- L30 _private member_ `const TSharedRef<FUICommandList> CommandList;` — Holds our command bindings
- L32 _private prototype_ `void HandleLeaveSandbox();`
- L33 _private prototype_ `void HandlePersistAll();`
- L34 _private prototype_ `void HandleDiscardAll();`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/StatusBar/Commands/StatusBarCommands.h` (Private)


#### class `UE::SandboxedEditing::FStatusBarCommands`  
`class FStatusBarCommands : public TCommands<FStatusBarCommands>`  
_L9-32_
- inherits: `TCommands<FStatusBarCommands>`
- L13 _public prototype_ `FStatusBarCommands();`
- L16 _public prototype_ `virtual void RegisterCommands() override;`
- L23 _public member_ `TSharedPtr<FUICommandInfo> OpenCreateNewSandboxDialog;` — Opens a dialog for creating a new sandbox. @note This is temporary UX - this will be removed when we implement the final UX.
- L26 _public member_ `TSharedPtr<FUICommandInfo> LeaveSandbox;` — Leaves the active sandbox without persisting.
- L29 _public member_ `TSharedPtr<FUICommandInfo> PersistAll;` — Persists all changes.
- L31 _public member_ `TSharedPtr<FUICommandInfo> DiscardAll;` — Discards all changes.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/StatusBar/StatusBarFeature.h` (Private)


#### class `UE::SandboxedEditing::FStatusBarFeature`  
`class FStatusBarFeature : public FNoncopyable`  
_L11-24_
- inherits: `FNoncopyable`
- desc: Manages extending the status bar for Sandboxed Editing.
- L15 _public prototype_ `explicit FStatusBarFeature(const TSharedRef<FSandboxSystemModel>& InSandboxModel);`
- L20 _private member_ `const TSharedRef<FSandboxSystemModel> SandboxModel;` — The shared sandbox model.
- L23 _private member_ `const FStatusBarCommandMappings CommandMappings;` — Handles all the input commands to this app.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/StatusBar/Widgets/SCreateNewSandbox.h` (Private)


#### class `UE::SandboxedEditing::SCreateNewSandbox`  
`class SCreateNewSandbox : public SCompoundWidget`  
_L20-68_
- inherits: `SCompoundWidget`
- L24 _public function_ `SLATE_BEGIN_ARGS(SCreateNewSandbox)`
- L26 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<SWindow>, ParentWindow) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FSandboxSystemModel>& InModel);` — The parent window this widget is hosted in.
- L31 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L34 _public function_ `bool IsDialogConfirmed() const` — Get dialog result
- L37 _public prototype_ `FCreateSandboxArgs GetArgs() const;` — Get the new sandbox command from the dialog result.
- L42 _private member_ `TWeakPtr<SWindow> ParentWindow;` — Pointer to the parent modal window
- L45 _private member_ `TSharedPtr<FSandboxSystemModel> Model;` — Model use to determine whether a name is available.
- L47 _private member_ `TSharedPtr<SMultiLineEditableTextBox> DescriptionTextCtrl;`
- L48 _private member_ `TSharedPtr<SEditableTextBox> NameTextCtrl;`
- L51 _private member_ `bool bDialogConfirmed = false;` — Result confirmation
- L53 _private prototype_ `TSharedRef<SWidget> CreateDescriptionInput();`
- L54 _private prototype_ `TSharedRef<SWidget> CreateButtonArea();`
- L57 _private prototype_ `FReply OnCreateClicked();` — Called when the settings of the dialog are to be accepted
- L59 _private prototype_ `bool IsCreateButtonEnabled() const;` — Called to check if create button is enabled or not.
- L61 _private prototype_ `FText GetCreateButtonToolTipText() const;` — @return Tooltip text to show on create button
- L64 _private prototype_ `void OnNameChanged(const FText& InNewName);` — Updates the error state when the name changes.
- L67 _private prototype_ `FReply OnCancelClicked();` — Called when the sandbox creation is abandoned.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace SandboxedEditing` (scope `UE`)
- L18 _prototype_ `void ShowNewSandboxModal(TSharedPtr<FSandboxSystemModel> InViewModel);` (scope `UE::SandboxedEditing`) — Shows a modal dialogue to the user for starting a new sandbox.

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Features/StatusBar/Widgets/SSandboxStatusBarWidget.h` (Private)


#### class `UE::SandboxedEditing::SSandboxStatusBarWidget`  
`class SSandboxStatusBarWidget : public SCompoundWidget`  
_L14-37_
- inherits: `SCompoundWidget`
- desc: Root widget that is placed in the status bar.
- L18 _public function_ `SLATE_BEGIN_ARGS(SSandboxStatusBarWidget)`
- L19 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FSandboxSystemModel>& InViewModel, const TSharedRef<FUICommandList>& InCommandList);`
- L26 _private member_ `TSharedPtr<FSandboxSystemModel> ViewModel;` — The model we're bound to.
- L28 _private member_ `TSharedPtr<FUICommandList> CommandList;` — The commands needed to create the menu.
- L31 _private prototype_ `FText GetTitleText() const;` — @return Text to display in the combo button content
- L33 _private prototype_ `TSharedRef<SWidget> CreateStatusBarMenu();` — @return Content to show when combo button is opened
- L36 _private prototype_ `void BuildSandboxesMenu(UToolMenu* InMenuBuilder);` — Fills the submenu showing the available sandboxes.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Framework/Cleanup/ShutdownCleanupHandler.h` (Private)


#### class `UE::SandboxedEditing::FShutdownCleanupHandler`  
`class FShutdownCleanupHandler : public FNoncopyable`  
_L16-44_
- inherits: `FNoncopyable`
- desc: Handles cleanup of empty sandboxes on editor shutdown. Checks all known sandboxes and deletes those with no file changes.
- L23 _public prototype_ `explicit FShutdownCleanupHandler(const TSharedRef<FSandboxSystemModel>& InModel);` — Constructor - registers for engine shutdown event @param InModel The sandbox system model to use for operations
- L26 _public prototype_ `~FShutdownCleanupHandler();` — Destructor - unregisters delegates
- L30 _private prototype_ `void OnEnginePreExit();` — Called when engine is about to shut down
- L37 _private prototype_ `bool HasFileChanges(const FString& SandboxRoot);` — Checks if a sandbox has any file changes @param SandboxRoot The root directory of the sandbox @return True if the sandbox has created/modified/deleted files
- L40 _private member_ `TSharedRef<FSandboxSystemModel> SandboxModel;` — The sandbox system model for all sandbox operations
- L43 _private member_ `FDelegateHandle ShutdownHandle;` — Delegate handle for cleanup

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Framework/EntryPoint/SandboxedEditingEntryPoint.h` (Private)


#### class `UE::SandboxedEditing::FSandboxedEditingEntryPoint`  
`class FSandboxedEditingEntryPoint : public FileSandboxUI::ISandboxEntryPoint`  
_L13-30_
- inherits: `FileSandboxUI::ISandboxEntryPoint`
- desc: Represents entry point for sandboxed in Sandboxed Editing.
- L18 _public prototype_ `virtual void SummonProviderUI() override;`
- L19 _public prototype_ `virtual FText GetEntryPointLabel() const override;`
- L20 _public prototype_ `virtual bool OwnsSandbox(const FileSandboxCore::ISandboxInstance& InSandbox) const override;`
- L24 _public function_ `FSimpleMulticastDelegate& OnRequestSummonUI()` — Event invoked when the UI is supposed to be summoned.
- L29 _private member_ `FSimpleMulticastDelegate OnRequestSummonUIDelegate;` — Event invoked when the UI is supposed to be summoned.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Framework/EntryPoint/SandboxedEditingSandboxIntegration.h` (Private)


#### class `UE::SandboxedEditing::FSandboxedEditingSandboxIntegration`  
`class FSandboxedEditingSandboxIntegration : public FNoncopyable`  
_L15-32_
- inherits: `FNoncopyable`
- desc: Responsible for registering Sandboxed Editing with the sandbox system.
- L19 _public prototype_ `FSandboxedEditingSandboxIntegration();`
- L20 _public prototype_ `~FSandboxedEditingSandboxIntegration();`
- L22 _public function_ `const TSharedRef<FSandboxedEditingEntryPoint>& GetEntryPoint() const`
- L23 _public function_ `const TSharedRef<FileSandboxUI::IExternalSandboxActiveViewModel>& GetExternalSandboxViewModel() const`
- L28 _private member_ `const TSharedRef<FSandboxedEditingEntryPoint> EntryPoint;` — Represents Sandboxed Editing as entry point so it becomes discoverable by other editor systems.
- L31 _private member_ `const TSharedRef<FileSandboxUI::IExternalSandboxActiveViewModel> ExternalSandboxViewModel;` — This view model is used to overlay a widget onto the browser when the engine is already sandboxed.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace FileSandboxUI` (scope `UE`)
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Framework/Models/CreateSandboxArgs.h` (Private)


#### struct `UE::SandboxedEditing::FCreateSandboxArgs`  
`struct FCreateSandboxArgs`  
_L9-13_
- L11 _public member_ `FString Name;`
- L12 _public member_ `FString Description;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Framework/Models/SandboxInfo.h` (Private)


#### struct `UE::SandboxedEditing::FSandboxInfo`  
`struct FSandboxInfo`  
_L12-45_
- desc: Describes a sandbox.
- L15 _public member_ `FString Name;` — Name the user has given the sandbox. May not be unique (but usually is).
- L18 _public member_ `FString Description;` — Description the user has given the sandbox.
- L21 _public member_ `FString SandboxRoot;` — Path to the root of the sandbox directory. Unique for every sandbox item.
- L24 _public member_ `FDateTime LastModified;` — Info about when the sandbox was last modified in local time.
- L27 _public member_ `FFileSandboxCore_EngineVersionInfo EngineVersion;` — The version of the engine when this sandbox was created in.
- L29 _public prototype_ `FSandboxInfo() = default;`
- L30 _public function_ `explicit FSandboxInfo( FString InName, FString InDescription, FString InDirectoryPath, const FDateTime& InLastModified, FFileSandboxCore_EngineVersionInfo InEngineVersion ) : Name(MoveTemp(InName)) , Description(MoveTemp(InDescription)) , SandboxRoot(MoveTemp(InDirectoryPath)) , LastModified(InLastModified) , EngineVersion(MoveTemp(InEngineVersion))`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace SandboxedEditing` (scope `UE`)
- L41 _function_ `friend bool operator<(const FSandboxInfo& Left, const FSandboxInfo& Right)` (scope `UE::SandboxedEditing`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Framework/Models/SandboxSystemModel.h` (Private)


#### class `UE::SandboxedEditing::FSandboxSystemModel`  
`class FSandboxSystemModel : public FNoncopyable`  
_L32-161_
- inherits: `FNoncopyable`
- desc: Model for creating, loading, and querying the active sandbox. Bridges the sandbox system without exposing it directly. Members added here should have direct corresponding UI elements.
- L36 _public prototype_ `FSandboxSystemModel();`
- L37 _public prototype_ `~FSandboxSystemModel();`
- L40 _public prototype_ `bool CreateNewSandbox(const FCreateSandboxArgs& InArgs);` — Creates a new sandbox with the given name.
- L42 _public prototype_ `bool CanCreateNewSandbox(const FString& InName, FText* Reason = nullptr);` — @return Whether it is valid to call CreateNewSandbox.
- L44 _public prototype_ `bool CanCreateNewSandbox() const;` — @return Whether we can create a new sandbox. This is allowed as long as there is no leave lock.
- L47 _public prototype_ `bool LoadSandbox(const FString& InRootDirectory);` — Loads the specified sandbox.
- L49 _public prototype_ `bool CanLoadSandbox(const FString& InRootDirectory);` — @return Whether the user can join this sandbox (i.e. not yet in this sandbox)
- L51 _public prototype_ `bool IsActiveSandbox(const FString& InRootDirectory) const;` — @return Whether this is the active sandbox.
- L54 _public prototype_ `void LeaveSandbox() const;` — Leaves the current sandbox.
- L56 _public function_ `bool IsAllowedToLeaveSandbox() const` — @return Whether the sandbox can be left (false if there is no active one).
- L58 _public prototype_ `bool IsAllowedToLeaveSandbox(FText* OutReason) const;` — @return Whether the sandbox can be left (false if there is no active one).
- L60 _public prototype_ `bool CanLeaveSandboxWithoutFurtherActions() const;` — @return Whether the engine is in a valid state to leave the sandbox, i.e. no other clean up actions need to be performed.
- L63 _public prototype_ `TArray<UPackage*> GetInMemoryChanges() const;` — @return The in-memory changes preventing the sandbox from being left.
- L65 _public prototype_ `bool RevertDirtyPackages();` — Reverts in-memory changes on the given packages, and performs related actions, such as reloading the underlying asset editors, etc.
- L67 _public prototype_ `bool SaveDirtyPackages();` — Saves the in-memory changes of the given packages, so the packages are no longer dirty.
- L70 _public prototype_ `void DeleteSandbox(const FString& InSandboxRoot) const;` — Deletes the sandbox.
- L72 _public prototype_ `bool CanDeleteSandbox(const FString& InSandboxRoot, FText* OutReason = nullptr) const;` — @return Whether the sandbox can be deleted.
- L75 _public prototype_ `void PersistAllChanges() const;` — Persists all changes
- L77 _public prototype_ `void PersistFiles(TConstArrayView<FString> InFiles, FileSandboxCore::IPersistFeedback* InFeedback = nullptr) const;` — Persists given files.
- L79 _public prototype_ `bool CanPersistAllChanges() const;` — @return Whether all changes can be persisted
- L82 _public prototype_ `FileSandboxCore::FGatheredFileChanges GatherActiveFileChanges() const;` — @return The file changes that were performed by the sandbox.
- L84 _public prototype_ `FileSandboxCore::FGatheredFileChanges GatherFileChanges(const FString& InSandbox) const;` — @return The file changes of the specified sandbox.
- L87 _public prototype_ `void EnumerateFileChanges( const FString& InSandbox, TFunctionRef<FileSandboxCore::EBreakBehavior(const FileSandboxCore::FSandboxedFileChangeInfo& InChange)> InCallback );` — Invokes InCallback for each file change.
- L93 _public prototype_ `void RevertAllChanges() const;` — Reverts all changes
- L95 _public prototype_ `bool CanRevertAllChanges() const;` — @return Whether all changes can be reverted
- L98 _public prototype_ `FString GetActiveSandboxPath() const;` — @return Path to the root directory of the active sandbox. Empty if none is active.
- L100 _public prototype_ `FString GetActiveSandboxName() const;` — @return Name of the currently active sandbox. Empty if none active.
- L102 _public prototype_ `bool HasActiveSandbox() const;` — @return Whether there is an active sandbox
- L105 _public prototype_ `void ForEachSandbox(TFunctionRef<void(const FSandboxInfo& InRoot)> InProcess) const;` — Enumerates all known sandboxes.
- L107 _public prototype_ `TArray<FSandboxInfo> GetKnownSandboxes() const;` — @return The sandboxes we know of.
- L110 _public prototype_ `TOptional<FSandboxInfo> GetSandboxInfo(const FString& InSandboxRoot) const;` — @return Info about the sandbox. Unset if sandbox does not exist.
- L112 _public prototype_ `void SetDescription(const FString& InSandboxRoot, const FString& InDescription) const;` — Sets the sandbox description.
- L115 _public prototype_ `bool RenameSandbox(const FString& InSandboxRoot, const FString& InNewName) const;` — Tries to rename InSandboxRoot to InNewName.
- L117 _public prototype_ `bool CanRenameSandbox(const FString& InSandboxRoot, const FString& InNewName, FText* OutError = nullptr) const;` — @returnWhether the sandbox at InSandboxRoot can be renamed to InNewName.
- L119 _public prototype_ `bool IsAllowedToRenameSandbox(const FString& InSandboxRoot, FText* OutError = nullptr) const;` — @return Whether it is allowd to rename the InSandboxRoot, i.e. it is not active.
- L122 _public function_ `FSimpleMulticastDelegate& OnKnownSandboxesChanged()` — Invoked when the result of GetKnownSandboxes may have changed.
- L125 _public function_ `FSimpleMulticastDelegate& OnLoadSandbox()` — Invoked when the a new sandbox is loaded.
- L127 _public function_ `FSimpleMulticastDelegate& OnLeaveSandbox()` — Invoked when the current sandbox is left.
- L130 _public function_ `FSimpleMulticastDelegate& OnSandboxFilesChanged()` — Invoked when the files in the active sandbox have changed.
- L134 _private prototype_ `bool HasLeaveLock(FText* OutReason = nullptr) const;` — @return true if a leave lock is currently registered.
- L137 _private prototype_ `bool IsUsingDefaultRepository() const;` — @return true if using the default repository (not a custom directory).
- L140 _private prototype_ `void NotifyIfBypassingRepository() const;` — Fires OnKnownSandboxesChanged event if using a custom directory (bypassing repository's directory watching).
- L143 _private member_ `FSimpleMulticastDelegate OnKnownSandboxesChangedDelegate;` — Invoked when the result of GetKnownSandboxes may have changed.
- L146 _private member_ `FSimpleMulticastDelegate OnLoadSandboxDelegate;` — Invoked when the a new sandbox is loaded.
- L148 _private member_ `FSimpleMulticastDelegate OnLeaveSandboxDelegate;` — Invoked when the current sandbox is left.
- L151 _private member_ `FSimpleMulticastDelegate OnSandboxFilesChangedDelegate;` — Invoked when the files in the active sandbox have changed.
- L153 _private function_ `void HandleSandboxesChanged(const FileSandboxCore::FRepositoryChangedEvent&) const`
- L154 _private function_ `void HandleMetaDataChanged(const FString&) const`
- L155 _private function_ `void HandleCustomDirectoryChanged() const`
- L157 _private prototype_ `void HandleLoadSandbox(FileSandboxCore::ISandboxInstance& InInstance);`
- L158 _private prototype_ `void HandleLeaveSandbox();`
- L160 _private prototype_ `void HandleActiveSandboxFilesChanged();` — Invoked when the set of files touched by the active sandbox changes.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace FileSandboxCore` (scope `UE`)
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace SandboxedEditing` (scope `UE`)
- L168 _namespace_ `namespace SandboxModel` (scope `UE::SandboxedEditing`)
- L171 _prototype_ `TOptional<FString> GetSandboxPathFor(const FString& InSandbox, const FString& InNonSandboxPath);` (scope `UE::SandboxedEditing::SandboxModel`) — @return Gets the sandbox path for InNonSandboxPath.
- L174 _prototype_ `TOptional<FString> GetSandboxName(const FString& InSandboxDirectory);` (scope `UE::SandboxedEditing::SandboxModel`) — @return Name of the sandbox if the directory is the root of a sandbox. Unset otherwise.
- L177 _prototype_ `FString GetBaseSandboxDirectory();` (scope `UE::SandboxedEditing::SandboxModel`) — @return The base directory in which sandboxes are placed.
- L180 _prototype_ `bool HasActiveSandbox();` (scope `UE::SandboxedEditing::SandboxModel`) — @return Whether there is an active sandbox
- L183 _prototype_ `void RevertSpecifiedChanges(TConstArrayView<FString> InFiles);` (scope `UE::SandboxedEditing::SandboxModel`) — Reverts the changes of the specified files.
- L185 _prototype_ `bool CanRevertSpecifiedChanges(TConstArrayView<FString> InFiles);` (scope `UE::SandboxedEditing::SandboxModel`) — @return Whether the specified files can be reverted.

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Framework/Models/SandboxTagging.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace SandboxedEditing` (scope `UE`)
- L12 _variable_ `constexpr FLazyName SandboxedEditingTag("San` (scope `UE::SandboxedEditing`) — Tag added to sandboxes created by the Sandboxed Editing plugin.
- L15 _prototype_ `bool IsOwnedBySandboxedEditing(const FFileSandboxCore_SandboxMetaData& InMetaData);` (scope `UE::SandboxedEditing`) — @return Whether the metadata is marked to belong to the Sandboxed Editing application.
- L18 _prototype_ `bool CanBeShownBySandboxedEditing(const FFileSandboxCore_SandboxMetaData& InMetaData);` (scope `UE::SandboxedEditing`) — @return Whether the metadata indicates that Sandboxed Editing can interact with this sandbox.
- L21 _prototype_ `void MarkOwnedBySandboxedEditing(FFileSandboxCore_SandboxMetaData& InMetaData);` (scope `UE::SandboxedEditing`) — Modifies the metadata such that we know it belongs to Sandboxed Editing application.

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Framework/Notifications.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SandboxedEditing` (scope `UE`)
- L14 _prototype_ `void ShowCreatedSandbox(const FString& InSandboxName);` (scope `UE::SandboxedEditing`) — Shows a notification that the user joined a sandbox.
- L17 _prototype_ `void ShowLoadedSandbox(const FString& InSandboxName);` (scope `UE::SandboxedEditing`) — Shows the sandbox was loaded successfully.
- L19 _prototype_ `void ShowFailedToLoadSandbox(const FString& InSandboxName);` (scope `UE::SandboxedEditing`) — Show that the sandbox could not be loaded.
- L21 _prototype_ `void ShowIncompatibleVersionError(const FString& InSandboxName, const FString& InSandboxVersion, const FString& InCurrentVersion);` (scope `UE::SandboxedEditing`) — Show that the sandbox could not be loaded due to incompatible version.
- L24 _prototype_ `void ShowLeftSandbox(const FString& InSandboxName);` (scope `UE::SandboxedEditing`) — Shows notification that the user left a sandbox.
- L27 _prototype_ `void ShowCannotLeaveDuringPlayMode();` (scope `UE::SandboxedEditing`) — Shows notification that the user cannot leave the sandbox while a play session is active.
- L36 _prototype_ `TSharedPtr<SNotificationItem> ShowInMemoryChangesWarning(const FString& InSandboxName, TFunction<void()> OnDiscard, TFunction<void()> OnCancel);` (scope `UE::SandboxedEditing`) — Shows a notification warning the user about in-memory changes before loading a sandbox. @param InSandboxName The name of the sandbox being loaded @param OnDiscard Callback invoked when user chooses to discard changes @param OnCancel Callback invoked when user chooses to cancel @return The notification item.

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Framework/SandboxedEditingApp.h` (Private)


#### class `UE::SandboxedEditing::FSandboxedEditingApp`  
`class FSandboxedEditingApp : public FNoncopyable`  
_L23-49_
- inherits: `FNoncopyable`
- desc: Creates all relevant systems to deliver the sandboxed editing experience in the editor. This is a coordinator: It sets up features, which are isolated areas in the editor that interact with sandboxing.
- L26 _public prototype_ `FSandboxedEditingApp();`
- L34 _private member_ `const TSharedRef<FSandboxSystemModel> SandboxModel;` — View model for interacting with sandbox system. Shared pointer in case the UI to avoid crash in case that though some bug the UI outlives this app for whatever reason.
- L37 _private member_ `const TSharedRef<FSandboxedEditingSandboxIntegration> SandboxIntegration;` — Responsible for registering Sandboxed Editing with the sandbox system.
- L40 _private member_ `const FStatusBarFeature StatusBarFeature;` — Extends the status bar for Sandboxed Editing.
- L42 _private member_ `const FBrowserFeature BrowserFeature;` — Extends the editor with a nomad tab containing a browser for sandboxes.
- L44 _private member_ `const FContentBrowserBadgeFeature ContentBrowserBadgeFeature;` — Displays badges on Content Browser items for files modified in the active sandbox.
- L46 _private member_ `const FStartupBehaviorHandler StartupBehaviorHandler;` — Handles startup behavior (creating/loading sandboxes on editor startup).
- L48 _private member_ `const FShutdownCleanupHandler ShutdownCleanupHandler;` — Handles cleanup of empty sandboxes on editor shutdown.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Framework/StartupBehavior/StartupBehaviorHandler.h` (Private)


#### class `UE::SandboxedEditing::FStartupBehaviorHandler`  
`class FStartupBehaviorHandler : public FNoncopyable`  
_L20-117_
- inherits: `FNoncopyable`
- desc: Handles sandbox startup behavior based on user settings. Automatically creates, loads, or prompts for sandboxes when the editor starts. Also tracks the last used sandbox for the "Join Previous" workflow.
- L27 _public prototype_ `explicit FStartupBehaviorHandler(const TSharedRef<FSandboxSystemModel>& InModel);` — Constructor - registers for editor initialization and sandbox load events @param InModel The sandbox system model to use for operations
- L30 _public prototype_ `~FStartupBehaviorHandler();` — Destructor - unregisters all delegates
- L35 _private prototype_ `void OnEditorInitialized(double Duration);` — Called when the editor has fully initialized and is ready
- L38 _private prototype_ `void ExecuteStartupBehavior();` — Reads settings and executes the appropriate startup behavior
- L42 _private prototype_ `void HandleDoNothing();` — Does nothing - default behavior
- L45 _private prototype_ `void HandlePromptToJoin();` — Shows a prompt with options to create new, join previous, or skip
- L48 _private prototype_ `void HandleCreateNewSandbox();` — Automatically creates a new sandbox using the template name
- L51 _private prototype_ `void HandleJoinPreviousSandbox();` — Automatically loads the most recently used sandbox
- L59 _private prototype_ `bool TryGetStartupBehaviorFromCommandLine(ESandboxStartupBehavior& OutBehavior) const;` — Parses command line override for startup behavior @param OutBehavior If command line override is present, this will be set @return True if command line override was found, false otherwise
- L66 _private prototype_ `bool TryGetNameTemplateFromCommandLine(FString& OutTemplate) const;` — Parses command line override for sandbox name template @param OutTemplate If command line override is present, this will be set @return True if command line override was found, false otherwise
- L74 _private prototype_ `FString ResolveNamingTokens(const FString& Template);` — Resolves naming tokens in a template string using the NamingTokens plugin @param Template The template string with tokens like {yyyy}, {mm}, {dd}, {user} @return The resolved string with tokens replaced, or a fallback if resolution fails
- L80 _private prototype_ `FString FallbackToTimestamp();` — Generates a fallback sandbox name using timestamp when NamingTokens fails @return A timestamp-based sandbox name like "Sandbox_2026_03_27_1435"
- L87 _private prototype_ `FString GenerateUniqueSandboxName(const FString& BaseName);` — Generates a unique sandbox name by auto-incrementing if the base name exists @param BaseName The desired base name @return A unique name (BaseName, BaseName_1, BaseName_2, etc.)
- L93 _private prototype_ `void ShowSuccessNotification(const FText& Message);` — Shows a success notification @param Message The message to display
- L99 _private prototype_ `void ShowErrorNotification(const FText& Message);` — Shows an error notification @param Message The error message to display
- L106 _private prototype_ `void OnSandboxLoaded();` — Called whenever a sandbox is loaded (manual or automatic) Updates LastUsedSandboxPath in settings
- L110 _private member_ `TSharedRef<FSandboxSystemModel> SandboxModel;` — The sandbox system model for all sandbox operations
- L113 _private member_ `TSharedPtr<SNotificationItem> CurrentNotification;` — Current notification being displayed (for prompt workflow)
- L116 _private member_ `FDelegateHandle LoadSandboxHandle;` — Delegate handle for sandbox load tracking

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/GlobalSandboxedEditingEditorSettings.h` (Private)


#### class `UGlobalSandboxedEditingEditorSettings`  
`class UGlobalSandboxedEditingEditorSettings : public UObject`  
_L10-36_
- reflection: `UCLASS(Config=EditorSettings, DefaultConfig)`
- inherits: `UObject`
- desc: Settings shared with all editor instances.
- L15 _public function_ `static UGlobalSandboxedEditingEditorSettings* Get()`
- L18 _public function_ `const FString& GetDefaultExportDirectory() const` — @return The default path that sandboxes are exported to.
- L20 _public prototype_ `void SetDefaultExportDirectory(const FString& InPath);` — @param InPath Path to directory or file. In case of file, the directory will be extracted and set.
- L23 _public function_ `const FString& GetDefaultImportDirectory() const` — @return The default path that sandboxes are imported from.
- L25 _public prototype_ `void SetDefaultImportDirectory(const FString& InPath);` — @param InPath Path to directory or file. In case of file, the directory will be extracted and set.
- L31 _private member_ `FString DefaultExportDirectory;` — `UPROPERTY(EditAnywhere, Config, Category = "General")` — Default directory to export to.
- L35 _private member_ `FString DefaultImportDirectory;` — `UPROPERTY(EditAnywhere, Config, Category = "General")` — Default directory to import from.

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/LogSandboxedEditing.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSandboxedEditing, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSandboxedEditing, Log, All);`

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/SandboxEditingModule.h` (Private)


#### class `UE::SandboxedEditing::FSandboxEditingModule`  
`class FSandboxEditingModule : public ISandboxedEditingModule`  
_L10-23_
- inherits: `ISandboxedEditingModule`
- L15 _public prototype_ `virtual void StartupModule() override;`
- L16 _public prototype_ `virtual void ShutdownModule() override;`
- L22 _private member_ `TUniquePtr<FSandboxedEditingApp> EditingApp;` — Manages all the business logic and creates the editor workflows.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/SandboxedEditingSettings.h` (Private)


#### enum `ESandboxStartupBehavior`  
`enum class ESandboxStartupBehavior : uint8`  
_L18-31_
- reflection: `UENUM()`
- desc: Determines how the editor should behave on startup with regards to sandboxes. Command Line Overrides: -SANDBOXSTARTUP=DoNothing|PromptToJoin|CreateNewSandbox|JoinPreviousSandbox -SANDBOXNAMETEMPLATE="Sandbox_{yyyy}_{mm}_{dd}" Command line overrides take precedence over these settings and are not saved to config.
- L21 _public enumerator_ `DoNothing UMETA(DisplayName = "Do Nothing")` — Do not automatically create or join a sandbox on startup (default)
- L24 _public enumerator_ `PromptToJoin UMETA(DisplayName = "Prompt to Join")` — Show a prompt asking the user if they want to create or join a sandbox
- L27 _public enumerator_ `CreateNewSandbox UMETA(DisplayName = "Create New Sandbox")` — Automatically create a new sandbox using the default template name
- L30 _public enumerator_ `JoinPreviousSandbox UMETA(DisplayName = "Join Previous Sandbox")` — Automatically join the most recently used sandbox

#### class `USandboxedEditingSettings`  
`class USandboxedEditingSettings : public UObject`  
_L34-71_
- reflection: `UCLASS(MinimalAPI, config=Engine)`
- inherits: `UObject`
- L39 _public function_ `static USandboxedEditingSettings* Get()`
- L41 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnCustomDirectoryChanged);`
- L42 _public member_ `static FOnCustomDirectoryChanged OnCustomDirectoryChanged;`
- L45 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L50 _public member_ `bool bAskToPersistWhenLeavingSandbox = true;` — `UPROPERTY(config, EditAnywhere, Category = "Actions", meta = (DisplayName="Ask to persist when leaving the sandbox"))` — Should we always ask the user to persist sandbox contents when leaving a sandbox?
- L54 _public member_ `ESandboxStartupBehavior StartupBehavior = ESandboxStartupBehavior::DoNothing;` — `UPROPERTY(config, EditAnywhere, Category = "Startup", meta = (DisplayName = "Startup Behavior", ToolTip = "Controls what happens on editor startup. Can be overridden with -SANDBOXSTARTUP command line argument."))` — Controls what happens on editor startup with regards to sandboxes. Can be overridden with -SANDBOXSTARTUP=DoNothing|PromptToJoin|CreateNewSandbox|JoinPreviousSandbox
- L58 _public member_ `FString DefaultSandboxNameTemplate = TEXT("San` — `UPROPERTY(config, EditAnywhere, Category = "Startup", meta = (DisplayName = "Default Sandbox Name Template", EditCondition = "StartupBehavior != ESandboxStartupBehavior::DoNothing", EditConditionHides, ToolTip = "Template for sandbox names. Supports {yyyy}, {mm}, {dd}, {24h}, {min}, {sec}, {user}, etc. Example: Sandbox_{yyyy}_{mm}_{dd}_{user}. Can be overridden with -SANDBOXNAMETEMPLATE command line argument."))` — Template for sandbox names when creating new sandboxes on startup. Supports {yyyy}, {mm}, {dd}, {24h}, {min}, {sec}, {user}, etc. Can be overridden with -SANDBOXNAMETEMPLATE
- L62 _public member_ `FString LastUsedSandboxPath;` — `UPROPERTY(config)` — Internal tracking of the last used sandbox path (auto-updated, not user-editable)
- L66 _public member_ `bool bDeleteEmptySandboxesOnExit = false;` — `UPROPERTY(config, EditAnywhere, Category = "Cleanup", meta = (DisplayName = "Delete Empty Sandboxes on Exit", ToolTip = "Automatically delete sandboxes with no file changes when the editor shuts down"))` — Automatically delete sandboxes with no file changes when the editor shuts down
- L70 _public member_ `FDirectoryPath CustomSandboxStorageDirectory;` — `UPROPERTY(config, EditAnywhere, Category = "Storage", meta = (DisplayName = "Custom Sandbox Storage Directory", ToolTip = "Optional custom directory where sandboxes are stored. Leave empty to use default location: {Project}/Intermediate/Sandboxes/. Can be overridden with -DEFAULTSANDBOXDIRECTORY command line argument."))` — Optional custom directory where sandboxes are stored. Leave empty to use default location: {Project}/Intermediate/Sandboxes/. Can be overridden with -DEFAULTSANDBOXDIRECTORY command line argument.

#### Free symbols / members of external scopes

- L41 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnCustomDirectoryChanged);`

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/SandboxedEditingStyle.h` (Private)


#### class `UE::SandboxedEditing::FSandboxedEditingStyle`  
`class FSandboxedEditingStyle final : public FSlateStyleSet`  
_L13-26_
- inherits: `FSlateStyleSet`
- L17 _public prototype_ `static FSandboxedEditingStyle& Get();`
- L19 _public prototype_ `FSandboxedEditingStyle();`
- L24 _private prototype_ `void RegisterBrowserStyle();`
- L25 _private prototype_ `void RegisterSharedStyle();`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Utils/BreakBehavior.h` (Private)


#### enum `UE::SandboxedEditing::EBreakBehavior`  
`enum class EBreakBehavior : uint8`  
_L9-13_
- L11 _public enumerator_ `Break`
- L12 _public enumerator_ `Continue`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SandboxedEditing` (scope `UE`)

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/Utils/WidgetUtils.h` (Private)


#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace SandboxedEditing` (scope `UE`)
- L19 _prototype_ `TSharedRef<SWidget> MakeIconButton( const TAttribute<const FSlateBrush*>& Icon, const TAttribute<FText>& Tooltip, const TAttribute<bool>& EnabledAttribute, const FOnClicked& OnClicked, const TAttribute<EVisibility>& Visibility = EVisibility::Visible );` (scope `UE::SandboxedEditing`) — Makes an action button that only contains an icon.
- L28 _prototype_ `TSharedRef<SWidget> MakePrimaryButton( const TAttribute<FText>& Label, const TAttribute<FText>& Tooltip, const TAttribute<const FSlateBrush*>& Icon, const TAttribute<bool>& EnabledAttribute, const FOnClicked& OnClicked, const TAttribute<EVisibility>& Visibility = EVisibility::Visible );` (scope `UE::SandboxedEditing`) — Makes primary action button with a label.
- L39 _prototype_ `TSharedRef<SWidget> MakeIconButtonByCommand( const TAttribute<const FSlateBrush*>& Icon, const TSharedPtr<FUICommandList>& InCommandList, const TSharedPtr<FUICommandInfo>& InCommand, const TAttribute<FText>& OverrideTooltip = {}, const TAttribute<EVisibility>& Visibility = EVisibility::Visible );` (scope `UE::SandboxedEditing`) — Overload that determines the IsEnabled and OnClicked parameters from the command list.
- L48 _prototype_ `TSharedRef<SWidget> MakePrimaryButtonByCommand( const TSharedPtr<FUICommandList>& InCommandList, const TSharedPtr<FUICommandInfo>& InCommand, const TAttribute<FText>& InLabel, const TAttribute<FText>& InOverrideTooltip = {}, const TAttribute<const FSlateBrush*>& InIcon = {}, const TAttribute<EVisibility>& Visibility = EVisibility::Visible );` (scope `UE::SandboxedEditing`) — Overload that determines the IsEnabled and OnClicked parameters from the command list.
- L58 _prototype_ `TSharedRef<SWidget> MakePositiveActionButton( const TAttribute<const FSlateBrush*>& Icon, const TAttribute<FText>& Tooltip, const TAttribute<bool>& EnabledAttribute, const FOnClicked& OnClicked, const TAttribute<EVisibility>& Visibility = EVisibility::Visible );` (scope `UE::SandboxedEditing`) — Makes a positive action button that only contains an icon
- L67 _prototype_ `TSharedRef<SWidget> MakeNegativeActionButton( const TAttribute<const FSlateBrush*>& Icon, const TAttribute<FText>& Tooltip, const TAttribute<bool>& EnabledAttribute, const FOnClicked& OnClicked, const TAttribute<EVisibility>& Visibility = EVisibility::Visible );` (scope `UE::SandboxedEditing`) — Makes a negative action button that only contains an icon
- L76 _prototype_ `TSharedRef<SWidget> CreateOpenSettingsButton();` (scope `UE::SandboxedEditing`) — @return A gear button that opens the plugin settings for Sandboxed Editing.

### `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Public/ISandboxEditingModule.h` (Public)


#### class `UE::SandboxedEditing::ISandboxedEditingModule`  
`class ISandboxedEditingModule : public IModuleInterface`  
_L10-28_
- inherits: `IModuleInterface`
- L20 _public function_ `static ISandboxedEditingModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L27 _public function_ `static bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() during shutdown if IsAvailable() returns true. @return True if the module is loaded and ready to use

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SandboxedEditing` (scope `UE`)
