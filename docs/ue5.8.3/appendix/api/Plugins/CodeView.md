# Plugins / CodeView

- module root: `Plugins/Experimental/CodeView/Source/CodeView`
- headers: 1; symbols: 69
- symbol kinds: class=4, enum=2, enumerator=5, function=9, member=15, namespace=5, prototype=25, typedef=4
- PrivateDependencyModuleNames: DetailCustomizations, SlateCore, SourceCodeAccess
- PublicDependencyModuleNames: Core, CoreUObject, DesktopPlatform, EditorFramework, Engine, InputCore, PropertyEditor, Slate, UnrealEd

### `Plugins/Experimental/CodeView/Source/CodeView/Private/SCodeView.h` (Private)


#### enum `CodeView::ETreeItemType::Type`  
`enum Type`  
_L23-30_
- L26 _public enumerator_ `Class` — C++ class
- L29 _public enumerator_ `Function` — C++ method

#### class `CodeView::FTreeItem`  
`class FTreeItem`  
_L35-52_
- desc: Base tree item abstract class for our code view.
- L38 _public function_ `FTreeItem()`
- L42 _public function_ `virtual ~FTreeItem()`
- L46 _public prototype_ `virtual ETreeItemType::Type GetType() const = 0;`
- L48 _public prototype_ `virtual const FString& GetAsString() const = 0;`
- L51 _public member_ `FString ModuleName;` — Module name

#### class `CodeView::FClassTreeItem`  
`class FClassTreeItem : public FTreeItem`  
_L56-80_
- inherits: `FTreeItem`
- desc: Represents a C++ class in the tree view
- L60 _public function_ `virtual ETreeItemType::Type GetType() const override`
- L65 _public function_ `virtual const FString& GetAsString() const override`
- L70 _public function_ `virtual ~FClassTreeItem()`
- L73 _public member_ `FString ClassName;` — Class name
- L76 _public member_ `bool bIsCompleteList;` — True unless if we're still gathering data and this class' list of functions is incomplete
- L79 _public member_ `FString AnyFunctionSymbolName;` — Symbol name for a function in this class that will navigate us to the class' source file (ideally header file)

#### class `CodeView::FFunctionTreeItem`  
`class FFunctionTreeItem : public FTreeItem`  
_L84-105_
- inherits: `FTreeItem`
- desc: Represents a C++ function in the tree view
- L88 _public function_ `virtual ETreeItemType::Type GetType() const override`
- L93 _public function_ `virtual const FString& GetAsString() const override`
- L98 _public function_ `virtual ~FFunctionTreeItem()`
- L101 _public member_ `FString FunctionName;` — Only the function name (sanitized)
- L104 _public member_ `FString FunctionSymbolName;` — Full symbol name

#### enum `CodeView::ECustomColumnMode::Type`  
`enum Type`  
_L118-130_
- L121 _public enumerator_ `None = 0` — Empty column -- doesn't display anything
- L124 _public enumerator_ `ModuleName` — Module name
- L129 _public enumerator_ `Count` — Number of options

#### class `CodeView::SCodeView`  
`class SCodeView : public SCompoundWidget`  
_L139-265_
- inherits: `SCompoundWidget`
- desc: Code View widget.  Displays a hierarchical view of C++ functions in one or more classes.
- L144 _public function_ `SLATE_BEGIN_ARGS( SCodeView )`
- L146 _public prototype_ `SLATE_EVENT( FGetSelectedActors, GetSelectedActors ) SLATE_END_ARGS() void Construct( const FArguments& InArgs );`
- L158 _public prototype_ `~SCodeView();` — SCodeView destructor
- L161 _public prototype_ `TSharedRef< SWidget > GenerateWidgetForItemAndColumn( FTreeItemPtr Item, const FName ColumnID ) const;` — Called by our list to generate a widget that represents the specified item at the specified column in the tree
- L164 _public prototype_ `void OnDetailSectionExpansionChanged( bool bIsExpanded );` — Hooked up to the SDetailSection, so that it can notify the CodeView when it has been expanded
- L167 _public prototype_ `bool IsReadyToPopulate() const;` — Returns true we're ready to populate the list.  This is used to set whether we should be initially expanded.
- L173 _private prototype_ `void Populate();` — Populates our data set
- L176 _private prototype_ `FText GetCustomColumnTextForTreeItem( FTreeItemPtr TreeItem ) const;` — Gets text for the specified item to display in the custom column for the tree
- L179 _private prototype_ `TSharedRef< ITableRow > OnGenerateRowForTree( FTreeItemPtr Item, const TSharedRef< STableViewBase >& OwnerTable );` — Called by STreeView to generate a table row for the specified item
- L182 _private prototype_ `void OnGetChildrenForTree( FTreeItemPtr Parent, TArray< FTreeItemPtr >& OutChildren );` — Called by STreeView to get child items for the specified parent item
- L185 _private prototype_ `void OnTreeSelectionChanged( FTreeItemPtr TreeItem, ESelectInfo::Type SelectInfo );` — Called by STreeView when the tree's selection has changed
- L188 _private prototype_ `void OnTreeDoubleClick( FTreeItemPtr TreeItem );` — Called by STreeView when the user double-clicks on an item in the tree
- L193 _private prototype_ `FText GetFilterText() const;` — @return Returns the current filter text
- L200 _private prototype_ `void OnFilterTextChanged( const FText& InFilterText );` — Called by the editable text control when the filter text is changed by the user @param	InFilterText	The new text
- L203 _private prototype_ `void OnFilterTextCommitted( const FText& InFilterText, ETextCommit::Type CommitInfo );` — Called by the editable text control when a user presses enter or commits their text change
- L210 _private prototype_ `const FSlateBrush* GetFilterButtonGlyph() const;` — Called by the filter button to get the image to display in the button @return	Slate brush for the button to display
- L213 _private prototype_ `FText GetFilterButtonToolTip() const;` — @return	The filter button tool-tip text
- L216 _private prototype_ `EVisibility GetFilterStatusVisibility() const;` — @return	Returns whether the filter status line should be drawn
- L219 _private prototype_ `FText GetFilterStatusText() const;` — @return	Returns the filter status text
- L222 _private prototype_ `FSlateColor GetFilterStatusTextColor() const;` — @return Returns color for the filter status text message, based on success of search filter
- L225 _private prototype_ `bool IsFilterActive() const;` — @return	Returns true if the filter is currently active
- L228 _private prototype_ `void OnCustomColumnModeChanged( TSharedPtr< ECustomColumnMode::Type > NewSelection, ESelectInfo::Type SelectInfo );` — Called by our custom column mode combo box when a new mode is selected
- L231 _private prototype_ `void OnSymbolQueryFinished();` — Called by FSourceCodeNavigation after a symbol query finishes
- L234 _private prototype_ `FText GetSelectedModeText() const;` — Helper method to set the displayed text for the mode combo box
- L239 _private member_ `TSharedPtr< SCodeTreeView > CodeTreeView;` — Our tree view
- L242 _private member_ `TMap< FString, FTreeItemPtr > SignatureToTreeItemMap;` — Map of function signatures to list items in our data.  Used to quickly find the item for a function.
- L245 _private member_ `int32 TotalClassesAndFunctions;` — Total number of displayable tree items we've seen, before applying a search filter
- L248 _private member_ `FCodeTreeItems RootTreeItems;` — Root level tree items
- L251 _private member_ `TMap< FString, TArray< FTreeItemPtr > > ClassNameToTreeItemMap;` — Map of class names to functions in that class
- L255 _private member_ `mutable ECustomColumnMode::Type CurrentCustomColumnMode;` — Current custom column mode.  This is used for displaying a bit of extra data about the items, as well as allowing the user to search by additional criteria
- L258 _private member_ `TSharedPtr< SSearchBox > FilterTextBoxWidget;` — Widget containing the filtering text box
- L261 _private member_ `FGetSelectedActors GetSelectedActorsDelegate;` — Gets the list of actors that we're viewing code for
- L264 _private member_ `TSharedPtr< SCustomColumnModeComboBoxType > CustomColumnModeComboBox;` — The mode selection combo box

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace ESelectInfo`
- L13 _namespace_ `namespace ETextCommit`
- L19 _namespace_ `namespace CodeView`
- L21 _namespace_ `namespace ETreeItemType` (scope `CodeView`)
- L109 _typedef_ `typedef TSharedPtr< FTreeItem > FTreeItemPtr;` (scope `CodeView`)
- L112 _typedef_ `typedef STreeView< FTreeItemPtr > SCodeTreeView;` (scope `CodeView`)
- L113 _typedef_ `typedef TArray< FTreeItemPtr > FCodeTreeItems;` (scope `CodeView`)
- L116 _namespace_ `namespace ECustomColumnMode` (scope `CodeView`)
- L134 _typedef_ `typedef SComboBox< TSharedPtr< ECustomColumnMode::Type > > SCustomColumnModeComboBoxType;` (scope `CodeView`) — Slate combo box type that allows users to pick a custom column mode
