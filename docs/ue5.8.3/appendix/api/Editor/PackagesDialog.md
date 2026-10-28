# Editor / PackagesDialog

- module root: `Source/Editor/PackagesDialog`
- headers: 2; symbols: 143
- symbol kinds: class=5, enum=2, enumerator=10, function=32, member=45, prototype=49
- DynamicallyLoadedModuleNames: AssetTools
- PrivateDependencyModuleNames: ApplicationCore, AssetRegistry, Core, CoreUObject, InputCore, Slate, SlateCore, SourceControl, ToolWidgets, UnrealEd
- PrivateIncludePathModuleNames: AssetTools

### `Source/Editor/PackagesDialog/Private/SPackagesDialog.h` (Private)


#### class `FPackageButton`  
`class FPackageButton : public TSharedFromThis<FPackageButton>`  
_L51-148_
- inherits: `TSharedFromThis<FPackageButton>`
- desc: Represents a button that will dynamically be added to the package dialog window
- L54 _public function_ `FPackageButton(FPackagesDialogModule* InModule, EDialogReturnType InType, EDialogButtonStyle InStyle, const FText& InName, const FText& InToolTip, TAttribute<bool> InDisabled = false) : Module(InModule) , Name(InName) , ToolTip(InToolTip) , Type(InType) , Style(InStyle) , Clicked(false) , Disabled(InDisabled)`
- L67 _public function_ `FReply OnButtonClicked()` — Gets called when the button is clicked
- L82 _public function_ `bool IsEnabled() const` — Returns if the button should be enabled @return True if the button is not disabled, false otherwise
- L89 _public function_ `FText GetName() const` — Gets the name of the button @return the name of the button
- L96 _public function_ `FText GetToolTip() const` — Gets the tooltip for the button @return the tooltip for the button
- L103 _public function_ `bool IsClicked() const` — Returns if the button was clicked @return True if the button was clicked, false otherwise
- L110 _public function_ `EDialogReturnType GetType() const` — Gets the type of the button @return the type of the button
- L117 _public function_ `EDialogButtonStyle GetStyle() const` — Gets the style of the button @return the style of the button
- L124 _public function_ `void SetDisabled(bool InDisabled)` — Sets if the button should be disabled @param	InDisabled	New disabled value
- L135 _public function_ `void Reset()` — Resets this button state
- L141 _private member_ `FPackagesDialogModule* Module;` — Stores the module that contains this button
- L142 _private member_ `FText Name;` — Name of the button
- L143 _private member_ `FText ToolTip;` — Tool tip for this button
- L144 _private member_ `EDialogReturnType Type;` — Button type
- L145 _private member_ `EDialogButtonStyle Style;` — Button style
- L146 _private member_ `bool Clicked;` — Stores if the button was clicked to close the dialog
- L147 _private member_ `TAttribute<bool> Disabled;` — Stores if the button is disabled or not

#### class `FPackageItem`  
`class FPackageItem : public TSharedFromThis<FPackageItem>`  
_L153-400_
- inherits: `TSharedFromThis<FPackageItem>`
- desc: Represents package item that is displayed as a checkbox inside the package dialog
- L156 _public function_ `FPackageItem(UPackage* InPackage, FString&& InAssetDisplayName, FString&& InFileName, UE::Core::FVersePath&& InVersePath, FString&& InOwnerName, ECheckBoxState InState, bool InDisabled, FString&& InIconName, FString&& InIconToolTip) : Package(InPackage) , AssetDisplayName(MoveTemp(InAssetDisplayName)) , PackageName(FPackageName::ObjectPathToPackageName(InPackage->GetName())) , FileName(MoveTemp(InFileName)) , VersePath(MoveTemp(InVersePath)) , OwnerName(MoveTemp(InOwnerName)) , State(InState) , Disabled(InDisabled) , IconName(MoveTemp(InIconName)) , IconToolTip(MoveTemp(InIconToolTip))`
- L190 _public function_ `const FSlateIcon& GetAssetIcon() const` — @return FSlateIcon the icon for the underlying asset object class or default object icon
- L197 _public function_ `ECheckBoxState OnGetDisplayCheckState() const` — Gets the display state of the item @return the item state
- L208 _public function_ `void OnDisplayCheckStateChanged(ECheckBoxState InNewState)` — Sets the item state @param InNewState the new state to set the item to
- L224 _public function_ `void SetRefreshCallback(FSimpleDelegate InRefreshButtonCallback)` — Sets refresh callback that should be called when the item's state change @param InRefreshButtonCallback the new callback
- L234 _public function_ `ECheckBoxState GetState() const` — Gets the state of the checkbox item @return the state of the checkbox item
- L241 _public function_ `UPackage* GetPackage() const` — Gets the package represented by this checkbox item @return the package represented by this checkbox item
- L248 _public prototype_ `UObject* GetPackageObject() const;` — Get the object belonging to the package, if any @return the object which is in the package, if any
- L256 _public prototype_ `bool HasMultipleAssets() const;` — Get whether the package contains multiple assets @return whether the package contains multiple assets
- L263 _public function_ `bool IsDisabled() const` — Checks to see if the checkbox item is disabled @return True if the checkbox item is disabled, false otherwise
- L270 _public function_ `const FString& GetAssetDisplayName() const` — Gets the display name of the primary asset item @return the display name of the asset item
- L277 _public function_ `const FString& GetPackageName() const` — Gets the name of the package item @return the name of the package item
- L284 _public function_ `const FString& GetFileName() const` — Gets the name of the file item @return the name of the file item
- L291 _public function_ `const UE::Core::FVersePath& GetVersePath() const` — Gets the Verse path of the primary asset item @return the Verse path of the primary asset item
- L298 _public function_ `const FString& GetOwnerName() const` — Gets the name of the file owner item @return the name of the file owner item
- L305 _public function_ `const FString& GetIconName() const` — Gets the icon name of the checkbox item @return the icon name of the checkbox item
- L312 _public function_ `FString GetCheckedOutByString() const` — Get a string containing the name(s) of other users who have the file checked out @return names of other users who have the file checked out
- L355 _public prototype_ `bool GetTypeNameAndColor(FText& OutName, FColor& OutColor) const;` — Gets the type name and color of the package item @param OutName	FText into which the type name will be placed, or an empty string if type cannot be obtained @param OutColor	FColor into which the type color will be placed @return Whether the details were successfully fetched.
- L362 _public function_ `FText GetTypeName() const` — Gets just the type name of the package item @return Type name of the package item, or an empty string
- L375 _public function_ `FString GetToolTip() const` — Gets the tool tip of the checkbox item @return the tool tip of the checkbox item
- L382 _public function_ `void SetState(ECheckBoxState NewState)` — Sets the new checkbox item state @param	NewState	New state
- L385 _private member_ `UPackage* Package;` — The package associated with this entry
- L386 _private member_ `FString AssetDisplayName;` — Name of the asset to display
- L387 _private member_ `FString PackageName;` — Name of the package to display
- L388 _private member_ `FString FileName;` — Name of the file
- L389 _private member_ `UE::Core::FVersePath VersePath;` — Verse path to display
- L390 _private member_ `FString OwnerName;` — Name of the owner of the file
- L391 _private member_ `ECheckBoxState State;` — The state of the checkbox
- L392 _private member_ `bool Disabled;` — if the entry is disabled
- L393 _private member_ `FString IconName;` — Name of an icon to show next to the checkbox
- L394 _private member_ `FString IconToolTip;` — ToolTip to display for the icon
- L395 _private member_ `FSimpleDelegate RefreshButtonCallback;` — ToolTip to display for the icon
- L396 _private member_ `mutable TWeakObjectPtr<UObject> Object;` — Cached object associated with this entry.
- L399 _private member_ `FSlateIcon AssetIcon;` — Icon for the asset class

#### class `SPackagesDialog`  
`class SPackagesDialog : public SCompoundWidget`  
_L405-654_
- inherits: `SCompoundWidget`
- desc: Represents a package dialog comprised of packages and checkboxes and buttons
- L408 _public function_ `SLATE_BEGIN_ARGS(SPackagesDialog) : _ReadOnly(false) , _AllowSourceControlConnection(false) , _Message() , _Warning()`
- L416 _public prototype_ `SLATE_ATTRIBUTE(bool, ReadOnly) SLATE_ATTRIBUTE(bool, AllowSourceControlConnection) SLATE_ARGUMENT(FText, Message) SLATE_ARGUMENT(FText, Warning) SLATE_EVENT(FSimpleDelegate, OnSourceControlStateChanged) SLATE_END_ARGS() void Construct( const FArguments& InArgs );` — When true, this dialog only shows a list of packages without the ability to filter
- L447 _public prototype_ `TSharedRef<SWidget> GenerateWidgetForItemAndColumn( TSharedPtr<FPackageItem> Item, const FName ColumnID ) const;` — Create and return a widget for the given item and column ID @param	Item		The item being queried @param	ColumnID	The column ID being queried @return	The widget which was created
- L452 _public prototype_ `void RemoveAll();` — Removes all checkbox items from the dialog
- L459 _public prototype_ `void Add(TSharedPtr<FPackageItem> Item);` — Adds a new checkbox item to the dialog @param	Item	The item to be added
- L466 _public prototype_ `void AddButton(TSharedPtr<FPackageButton> Button);` — Adds a new button to the dialog @param	Button	The button to be added
- L473 _public prototype_ `void SetMessage(const FText& InMessage);` — Sets the message of the widget @param	InMessage	The string that the message should be set to
- L480 _public prototype_ `void SetWarning(const FText& InMessage);` — Sets the warning message of the widget @param	InMessage	The string that the warning message should be set to
- L491 _public prototype_ `EDialogReturnType GetReturnType(OUT TArray<UPackage*>& OutCheckedPackages, OUT TArray<UPackage*>& OutUncheckedPackages, OUT TArray<UPackage*>& OutUndeterminedPackages);` — Gets the return type of the dialog and it populates the package array results @param	OutCheckedPackages		Will be populated with the checked packages @param	OutUncheckedPackages	Will be populated with the unchecked packages @param	OutUndeterminedPackages	Will be populated with the undetermined packages @return	returns the button that was pressed to remove the dialog
- L498 _public prototype_ `TSharedPtr< SWidget > GetWidgetToFocusOnActivate() const;` — Gets the widget which is to have keyboard focus on activating the dialog @return	returns the widget
- L503 _public prototype_ `EVisibility GetConnectToSourceControlVisibility() const;` — Get the visibility of the 'Connect to Source Control' button
- L508 _public prototype_ `FReply OnConnectToSourceControlClicked() const;` — Delegate used when the 'Connect to Source Control' button is clicked
- L514 _public prototype_ `void PopulateIgnoreForSaveItems( const TSet<FString>& InIgnorePackages );` — Populate the items with their current ignore status @param	InIgnorePackages	Container to populate the items from.
- L520 _public prototype_ `void PopulateIgnoreForSaveArray( OUT TSet<FString>& InOutIgnorePackages ) const;` — Populate current ignore status array with the item status @param	InOutIgnorePackages	Container to populate with the current ignore status of the items.
- L525 _public prototype_ `void Reset();` — Reset the state of this dialogs buttons
- L530 _public function_ `bool IsSourceControlConnectionAllowed() const` — Whether the dialog allows a source control connection
- L535 _private prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L536 _private prototype_ `virtual FReply OnKeyDown( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override;`
- L542 _private prototype_ `void RefreshButtons();` — Called when the checkbox items have changed state
- L547 _private prototype_ `TSharedRef<ITableRow> MakePackageListItemWidget(TSharedPtr<FPackageItem> Item, const TSharedRef<STableViewBase>& OwnerTable);` — Makes the widget for the checkbox items in the list view
- L552 _private prototype_ `TSharedPtr<SWidget> MakePackageListContextMenu() const;` — Makes the widget for the context menu in the list view
- L557 _private prototype_ `bool CanExecuteSCCDiffAgainstDepot() const;` — Handler to check to see if "Diff Against Depot" can be executed
- L562 _private prototype_ `void ExecuteSCCDiffAgainstDepot() const;` — Handler for when "Diff Against Depot" is selected
- L570 _private prototype_ `TArray< TSharedPtr<FPackageItem> > GetSelectedItems( bool bAllIfNone ) const;` — Get all the selected items in the dialog. @param bAllIfNone - if true, returns all items when none are selected @return the array of selected packages
- L573 _private prototype_ `FText GetMessage() const;` — Delegate used to supply message text to the widget
- L576 _private prototype_ `FText GetWarning() const;` — Delegate used to supply warning text to the widget
- L579 _private prototype_ `EVisibility GetWarningVisibility() const;` — Delegate used to determine visibility of the warning
- L589 _private prototype_ `EColumnSortMode::Type GetColumnSortMode( const FName ColumnId ) const;` — Returns the current column sort mode (ascending or descending) if the ColumnId parameter matches the current column to be sorted by, otherwise returns EColumnSortMode_None. @param	ColumnId	Column ID to query sort mode for. @return	The sort mode for the column, or EColumnSortMode_None if it is not known.
- L597 _private prototype_ `void OnColumnSortModeChanged( const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type InSortMode );` — Callback for SHeaderRow::Column::OnSort, called when the column to sort by is changed. @param	ColumnId	The new column to sort by @param	InSortMode	The sort mode (ascending or descending)
- L603 _private prototype_ `void RequestSort();` — Requests that the source list data be sorted according to the current sort column and mode, and refreshes the list view.
- L608 _private prototype_ `void SortTree();` — Sorts the source list data according to the current sort column and mode.
- L611 _private member_ `TArray< TSharedPtr<FPackageItem> > Items;` — All checkbox items stored in this widget for the list view
- L614 _private member_ `TSharedPtr< SListView< TSharedPtr<FPackageItem> > >ItemListView;` — The list view for showing all checkboxes
- L617 _private member_ `TArray< TSharedPtr<FPackageButton> > Buttons;` — All buttons stored in this widget
- L620 _private member_ `TSharedPtr< SHorizontalBox > ButtonsBox;` — A horizontal box that will contain all of the buttons
- L623 _private member_ `FSimpleDelegate RefreshButtonsCallback;` — Refresh callback that should be called when a checkbox item state change
- L626 _private member_ `TSharedPtr< SHorizontalBox > MessageBox;` — A horizontal box that will represent the message of the widget
- L629 _private member_ `bool bReadOnly;` — When true, this dialog only shows a list of packages without the ability to filter
- L632 _private member_ `bool bAllowSourceControlConnection;` — When true, this dialog displays a 'connect to source control' button
- L635 _private member_ `bool bShowWarning;` — When true, the warning message is displayed in the widget
- L638 _private member_ `bool bSortDirty;` — When true, items will be sorted on the next tick
- L641 _private member_ `FText Message;` — The message to display
- L644 _private member_ `FText Warning;` — The warning to display
- L647 _private member_ `FName SortByColumn;` — Specify which column to sort with
- L650 _private member_ `EColumnSortMode::Type SortMode;` — Currently selected sorting mode
- L653 _private member_ `FSimpleDelegate OnSourceControlStateChanged;` — Called when source control state changes

#### class `SPackageItemsListRow`  
`class SPackageItemsListRow : public SMultiColumnTableRow< TSharedPtr< FPackageItem > >`  
_L657-688_
- inherits: `SMultiColumnTableRow<TSharedPtr<FPackageItem>>`
- desc: Widget that represents a row in the PackagesDialog's list view.  Generates widgets for each column on demand.
- L663 _public function_ `SLATE_BEGIN_ARGS( SPackageItemsListRow )`
- L666 _public prototype_ `SLATE_ARGUMENT( TSharedPtr< SPackagesDialog >, PackagesDialog ) SLATE_ARGUMENT( TSharedPtr< FPackageItem >, Item ) SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView );` — The Packages Dialog that owns the tree.  We'll only keep a weak reference to it.
- L678 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn( const FName& ColumnName ) override;` — Overridden from SMultiColumnTableRow.  Generates a widget for this column of the list row.
- L684 _private member_ `TWeakPtr< SPackagesDialog > PackagesDialogWeak;` — Weak reference to the PackagesDialog widget that owns our list
- L687 _private member_ `TSharedPtr< FPackageItem > Item;` — The item associated with this row of data

### `Source/Editor/PackagesDialog/Public/PackagesDialog.h` (Public)


#### enum `EDialogReturnType`  
`enum EDialogReturnType`  
_L13-23_
- L15 _public enumerator_ `DRT_Save = 0`
- L16 _public enumerator_ `DRT_DontSave`
- L17 _public enumerator_ `DRT_CheckOut`
- L18 _public enumerator_ `DRT_MakeWritable`
- L19 _public enumerator_ `DRT_Cancel`
- L20 _public enumerator_ `DRT_Skip`
- L21 _public enumerator_ `DRT_Revert`
- L22 _public enumerator_ `DRT_None`

#### enum `EDialogButtonStyle`  
`enum EDialogButtonStyle`  
_L25-29_
- L27 _public enumerator_ `DBS_Normal = 0`
- L28 _public enumerator_ `DBS_Primary`

#### class `FPackagesDialogModule`  
`class FPackagesDialogModule : public IModuleInterface`  
_L31-168_
- inherits: `IModuleInterface`
- L38 _public prototype_ `virtual void StartupModule() override;` — Called right after the module DLL has been loaded and the module object has been created
- L43 _public prototype_ `virtual void ShutdownModule() override;` — Called before the module is unloaded, right before the module object is destroyed.
- L54 _public prototype_ `virtual void CreatePackagesDialog(const FText& Title, const FText& Message, bool InReadOnly = false, bool InAllowSourceControlConnection = false, const FSimpleDelegate& InOnSourceControlStateChanged = FSimpleDelegate());` — Used to create the package dialog window @param	Title							The title of the package dialog window @param	Message							The message that gets displayed in the package dialog window @param	InReadOnly						When true, this dialog only shows a list of packages without the ability to filter @param	InAllowSourceControlConnection	When true, this dialog displays a 'connect to source control' button when needed @param	InOnSourceControlStateChanged	Delegate called when the source control state changes
- L61 _public prototype_ `virtual EDialogReturnType ShowPackagesDialog();` — Shows the package dialog window as a modal window @return	Which button was pressed to terminate the window
- L70 _public prototype_ `virtual EDialogReturnType ShowPackagesDialog(OUT TSet<FString>& InOutIgnoredPackages);` — Shows the package dialog window as a modal window @param	InPackagedToIgnore	The Set of packages to ignore when saving. @return	Which button was pressed to terminate the window
- L75 _public prototype_ `virtual void RemovePackagesDialog();` — Removes the package dialog window
- L81 _public prototype_ `virtual void SetMessage(const FText& InMessage);` — Sets the message displayed in the package dialog @param InMessage		The message to display
- L87 _public prototype_ `virtual void SetWarning(const FText& InMessage);` — Sets the warning message displayed in the package dialog @param InMessage		The warning to display
- L95 _public prototype_ `virtual void GetResults(TArray<UPackage*>& OutPackages, ECheckBoxState InChecked);` — Populates the passed in array with the desired packages @param	OutPackages		The array that should be populated with the desired packages @param	InChecked		The type of packages that we want to retrieve
- L100 _public prototype_ `virtual void RemoveAllPackageItems();` — Removes all package items from the dialog
- L111 _public prototype_ `virtual void AddPackageItem(UPackage* InPackage, ECheckBoxState InChecked, bool InDisabled = false, FString InIconName=TEXT(""), FString InIconToolTip=TEXT(""));` — Adds a new item to the checkbox that represents a package @param	InPackage		The package that will be represented as a checkbox @param	InChecked		The state of the checkbox @param	InDisabled		If the item should be disabled @param	InIconName		The name of the icon to display @param	InIconToolTip	The tooltip to display
- L122 _public prototype_ `virtual void AddButton(EDialogReturnType Type, const FText& Name, const FText& ToolTip = FText(), TAttribute<bool> Disabled = false);` — Adds a new button to the package dialog window @param	Type		The type of this button @param	ButtonStyle	The style of this button @param	Name		The name to display @param	ToolTip		The tooltip to display @param	Disabled	If the button should be disabled
- L123 _public prototype_ `virtual void AddButton(EDialogReturnType Type, EDialogButtonStyle ButtonStyle, const FText& Name, const FText& ToolTip = FText(), TAttribute<bool> Disabled = false);`
- L130 _public function_ `virtual bool SupportsDynamicReloading() override` — Override this to set whether your module is allowed to be unloaded on the fly @return	Whether the module supports shutdown separate from the rest of the engine.
- L140 _public prototype_ `virtual bool IsWindowInitialized() const;` — Checks to see if the package dialog window is currently initialized @return	True if initialized, otherwise false
- L146 _protected prototype_ `void OnModulesChanged( FName ModuleThatChanged, EModuleChangeReason ReasonForChange );` — Called when a module has been changed (unloaded, loaded, etc)
- L150 _private member_ `static const FVector2D DEFAULT_WINDOW_SIZE;` — A default window size for the package dialog
- L153 _private member_ `static const FVector2D EXTRA_WINDOW_WIDTH;` — Extra window width if source control connection is allowed
- L156 _private member_ `TWeakPtr<SWindow> EditorPackagesDialogWindow;` — Editor package dialog window
- L159 _private member_ `TSharedPtr<class SPackagesDialog> PackagesDialogWidget;` — Packages Dialog Widget to use in the package dialog
- L162 _private member_ `TAttribute<FText> PackageDialogTitle;` — The title of the dialog window
- L165 _private member_ `TArray<UPackage*> CheckedPackages;` — The results of the dialog will be stored in these arrays
- L166 _private member_ `TArray<UPackage*> UncheckedPackages;`
- L167 _private member_ `TArray<UPackage*> UndeterminedPackages;`
