# Plugins / SlateIM

- module root: `Plugins/Experimental/SlateIM/Source/SlateIM`
- headers: 35; symbols: 1054
- symbol kinds: class=41, delegate=2, enum=4, enumerator=15, function=141, macro=7, member=309, namespace=11, prototype=433, struct=63, typedef=19, variable=9
- PrivateDependencyModuleNames: ApplicationCore, CoreUObject, Engine, InputCore, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: Core, SlateIMEngine

### `Plugins/Experimental/SlateIM/Source/SlateIM/Private/Containers/ISlateIMContainer.h` (Private)


#### class `ISlateIMContainer`  
`class ISlateIMContainer : public ISlateIMTypeChecking`  
_L15-27_
- inherits: `ISlateIMTypeChecking`
- L18 _public function_ `virtual FString GetDebugName()`
- L20 _public prototype_ `virtual int32 GetNumChildren() = 0;`
- L21 _public prototype_ `virtual FSlateIMChild GetChild(int32 Index) = 0;`
- L22 _public prototype_ `virtual void UpdateChild(FSlateIMChild Child, int32 Index, const FSlateIMSlotData& AlignmentData) = 0;`
- L24 _public prototype_ `virtual FSlateIMChild GetContainer() = 0;`
- L26 _public prototype_ `virtual void RemoveUnusedChildren(int32 LastUsedChildIndex) = 0;`

### `Plugins/Experimental/SlateIM/Source/SlateIM/Private/Containers/SImCompoundWidget.h` (Private)


#### class `SImCompoundWidget`  
`class SImCompoundWidget : public SBorder, public ISlateIMContainer`  
_L10-73_
- inherits: `SBorder,ISlateIMContainer`
- L16 _public prototype_ `virtual int32 GetNumChildren() override;`
- L17 _public prototype_ `virtual FSlateIMChild GetChild(int32 Index) override;`
- L19 _public function_ `virtual FSlateIMChild GetContainer() override`
- L24 _public prototype_ `virtual void RemoveUnusedChildren(int32 LastUsedChildIndex) override;`
- L26 _public prototype_ `virtual void UpdateChild(FSlateIMChild Child, int32 Index, const FSlateIMSlotData& AlignmentData) override;`
- L28 _public function_ `void SetBackgroundImage(const FSlateBrush* BorderBrush)`
- L33 _public function_ `void SetContentPadding(const FMargin ContentPadding)`
- L38 _public function_ `void SetAbsorbMouse(bool bInAbsorb)`
- L43 _public prototype_ `void SetOrientation(EOrientation InOrientation);`
- L45 _public function_ `virtual FReply OnMouseButtonDown(const FGeometry&, const FPointerEvent&) override`
- L50 _public function_ `virtual FReply OnMouseButtonUp(const FGeometry&, const FPointerEvent&) override`
- L55 _public function_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry&, const FPointerEvent&) override`
- L60 _public function_ `virtual FReply OnMouseMove(const FGeometry&, const FPointerEvent&) override`
- L65 _public function_ `virtual FReply OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override`
- L71 _private member_ `TSharedPtr<SImStackBox> Container;`
- L72 _private member_ `bool bAbsorbMouse = true;`

### `Plugins/Experimental/SlateIM/Source/SlateIM/Private/Containers/SImContextMenuAnchor.h` (Private)


#### enum `EMenuType`  
`enum class EMenuType : uint8`  
_L11-19_
- L13 _public enumerator_ `Button`
- L14 _public enumerator_ `Check`
- L15 _public enumerator_ `Toggle`
- L16 _public enumerator_ `Separator`
- L17 _public enumerator_ `Section`
- L18 _public enumerator_ `SubMenu`

#### class `SImContextMenuAnchor`  
`class SImContextMenuAnchor : public SCompoundWidget, public ISlateIMContainer`  
_L21-91_
- inherits: `SCompoundWidget,ISlateIMContainer`
- L27 _public function_ `SLATE_BEGIN_ARGS(SImContextMenuAnchor)`
- L28 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L32 _public prototype_ `virtual int32 GetNumChildren() override;`
- L33 _public prototype_ `virtual FSlateIMChild GetChild(int32 Index) override;`
- L35 _public function_ `virtual FSlateIMChild GetContainer() override`
- L40 _public prototype_ `virtual void RemoveUnusedChildren(int32 LastUsedChildIndex) override;`
- L42 _public prototype_ `virtual void UpdateChild(FSlateIMChild Child, int32 Index, const FSlateIMSlotData& AlignmentData) override;`
- L44 _public prototype_ `void Begin();`
- L45 _public prototype_ `void End();`
- L47 _public prototype_ `bool AddMenuButton(const FStringView& RowText, const FStringView& ToolTipText);`
- L48 _public prototype_ `bool AddMenuCheckButton(const FStringView& RowText, bool& InOutCurrentState, const FStringView& ToolTipText);`
- L49 _public prototype_ `bool AddMenuToggleButton(const FStringView& RowText, bool& InOutCurrentState, const FStringView& ToolTipText);`
- L50 _public prototype_ `void AddMenuSeparator();`
- L51 _public prototype_ `void AddMenuSection(const FStringView& SectionText);`
- L52 _public prototype_ `void BeginSubMenu(const FStringView& SectionText);`
- L53 _public prototype_ `void EndSubMenu();`
- L54 _public prototype_ `void OpenMenu(const FVector2D& InScreenPosition, const FWidgetPath* InWidgetPath = nullptr);`
- L55 _public function_ `bool IsMenuOpen() const`
- L56 _public prototype_ `TSharedRef<SWidget> GetMenuContent() const;`
- L58 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L61 _private prototype_ `bool AddMenuInternal(const FStringView& RowText, const FStringView& ToolTipText, bool& InOutCurrentState, EMenuType MenuType);`
- L62 _private prototype_ `void OnMenuItemExecuted(int32 MenuIndex, bool bIsCheck);`
- L63 _private prototype_ `ECheckBoxState OnGetMenuItemCheckState(int32 MenuIndex);`
- L65 _private prototype_ `TSharedRef<SWidget> OnGetSubMenuContent(int32 SubMenuIndex);` — void OnGetSubMenuContent(FMenuBuilder& MenuBuilder, int32 SubMenuIndex);
- L66 _private prototype_ `TSharedRef<SWidget> BuildMenu_Recursive(int32& InOutMenuIndex, int32 MenuLevel);`
- L79 _private member_ `TWeakPtr<IMenu> OpenedMenu;`
- L80 _private member_ `TSharedPtr<SWidget> MenuWidget;`
- L81 _private member_ `TArray<FMenuItemData, TMemStackAllocator<>> MenuDataList;`
- L82 _private member_ `TArray<TCHAR, TMemStackAllocator<>> MenuStringList;`
- L84 _private member_ `TArray<int32, TInlineAllocator<1>> ActivatedIndices;`
- L85 _private member_ `TBitArray<> CheckStates;`
- L86 _private member_ `TArray<TSharedRef<SWidget>> SubMenuWidgets;`
- L87 _private member_ `TArray<uint64> MenuHashes;`
- L88 _private member_ `int32 CurrentMenuIndex = 0;`
- L89 _private member_ `int32 CurrentSubMenuLevel = 0;`
- L90 _private member_ `bool bIsDirty = false;`

#### struct `SImContextMenuAnchor::FMenuItemData`  
`struct FMenuItemData`  
_L68-77_
- L70 _public member_ `int32 TextOffset;`
- L71 _public member_ `int32 TextSize;`
- L72 _public member_ `int32 ToolTipOffset;`
- L73 _public member_ `int32 ToolTipSize;`
- L74 _public member_ `int32 SubMenuLevel;`
- L75 _public member_ `EMenuType Type;`

### `Plugins/Experimental/SlateIM/Source/SlateIM/Private/Containers/SImPopUp.h` (Private)


#### class `SImPopUp`  
`class SImPopUp : public SMenuAnchor, public ISlateIMContainer`  
_L12-35_
- inherits: `SMenuAnchor,ISlateIMContainer`
- L18 _public prototype_ `void Construct(const FArguments& InArgs);`
- L20 _public prototype_ `virtual int32 GetNumChildren() override;`
- L21 _public prototype_ `virtual FSlateIMChild GetChild(int32 Index) override;`
- L22 _public prototype_ `virtual void UpdateChild(FSlateIMChild Child, int32 Index, const FSlateIMSlotData& AlignmentData) override;`
- L24 _public function_ `virtual FSlateIMChild GetContainer() override`
- L29 _public prototype_ `virtual void RemoveUnusedChildren(int32 LastUsedChildIndex) override;`
- L31 _public prototype_ `virtual FVector2D ComputeDesiredSize(float LayoutScaleMultiplier) const override;`
- L34 _private member_ `TSharedPtr<SBox> ChildBox;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SLATEIM_API`

### `Plugins/Experimental/SlateIM/Source/SlateIM/Private/Containers/SImScrollBox.h` (Private)


#### class `SImScrollBox`  
`class SImScrollBox : public SScrollBox, public ISlateIMContainer`  
_L8-41_
- inherits: `SScrollBox,ISlateIMContainer`
- L14 _public function_ `bool IsValidSlotIndex(int32 Index) const`
- L19 _public function_ `void SetOnUserScrolled(const FOnUserScrolled& InHandler)`
- L24 _public prototype_ `virtual int32 GetNumChildren() override;`
- L25 _public prototype_ `virtual FSlateIMChild GetChild(int32 Index) override;`
- L27 _public function_ `virtual FSlateIMChild GetContainer() override`
- L32 _public function_ `virtual void RemoveUnusedChildren(int32 LastUsedChildIndex) override`
- L40 _public prototype_ `virtual void UpdateChild(FSlateIMChild Child, int32 Index, const FSlateIMSlotData& AlignmentData) override;`

### `Plugins/Experimental/SlateIM/Source/SlateIM/Private/Containers/SImStackBox.h` (Private)


#### class `SImStackBox`  
`class SImStackBox : public SStackBox, public ISlateIMContainer`  
_L8-25_
- inherits: `SStackBox,ISlateIMContainer`
- L14 _public prototype_ `virtual int32 GetNumChildren() override;`
- L15 _public prototype_ `virtual FSlateIMChild GetChild(int32 Index) override;`
- L17 _public function_ `virtual FSlateIMChild GetContainer() override`
- L22 _public prototype_ `virtual void RemoveUnusedChildren(int32 LastUsedChildIndex) override;`
- L24 _public prototype_ `virtual void UpdateChild(FSlateIMChild Child, int32 Index, const FSlateIMSlotData& AlignmentData) override;`

### `Plugins/Experimental/SlateIM/Source/SlateIM/Private/Containers/SImTab.h` (Private)


#### class `SImTab`  
`class SImTab : public SDockTab, public ISlateIMContainer`  
_L12-52_
- inherits: `SDockTab,ISlateIMContainer`
- L18 _public prototype_ `virtual int32 GetNumChildren() override;`
- L19 _public prototype_ `virtual FSlateIMChild GetChild(int32 Index) override;`
- L20 _public prototype_ `virtual void UpdateChild(FSlateIMChild Child, int32 Index, const FSlateIMSlotData& AlignmentData) override;`
- L21 _public prototype_ `virtual void RemoveUnusedChildren(int32 LastUsedChildIndex) override;`
- L23 _public function_ `virtual FSlateIMChild GetContainer() override`
- L28 _public prototype_ `void ForceCloseTab();`
- L30 _public function_ `bool IsDrawerOpen() const`
- L35 _public function_ `void OnDrawerOpened()`
- L40 _public function_ `void OnDrawerClosed()`
- L45 _public member_ `FName TabId = NAME_None;`
- L46 _public member_ `FSlateIcon TabIcon;`
- L47 _public member_ `FText TabTitle = FText::GetEmpty();`
- L50 _private member_ `TSharedPtr<SImStackBox> Container;`
- L51 _private member_ `bool bDrawerOpen = false;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SLATEIM_API`

### `Plugins/Experimental/SlateIM/Source/SlateIM/Private/Containers/SImTabGroup.h` (Private)


#### class `SImTabGroup`  
`class SImTabGroup : public SCompoundWidget, public ISlateIMContainer`  
_L13-70_
- inherits: `SCompoundWidget,ISlateIMContainer`
- L19 _public function_ `SLATE_BEGIN_ARGS(SImTabGroup)`
- L21 _public prototype_ `SLATE_ARGUMENT(FName, TabGroupId) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L27 _public prototype_ `void BeginTabGroupUpdates();`
- L28 _public prototype_ `void FinalizeTabGroup();`
- L30 _public prototype_ `virtual int32 GetNumChildren() override;`
- L31 _public prototype_ `virtual FSlateIMChild GetChild(int32 Index) override;`
- L32 _public prototype_ `virtual void UpdateChild(FSlateIMChild Child, int32 Index, const FSlateIMSlotData& AlignmentData) override;`
- L33 _public prototype_ `virtual void RemoveUnusedChildren(int32 LastUsedChildIndex) override;`
- L35 _public function_ `virtual FSlateIMChild GetContainer() override`
- L40 _public prototype_ `FName GetTabGroupId() const;`
- L41 _public prototype_ `bool IsTabForegrounded(const FName& TabId) const;`
- L43 _public prototype_ `void SetSizeCoefficient(float SizeCoefficient);`
- L45 _public prototype_ `void BeginTabSplitter(EOrientation Orientation);`
- L46 _public prototype_ `void BeginTabStack();`
- L47 _public prototype_ `void EndTabLayoutNode();`
- L49 _public prototype_ `TSharedRef<SDockTab> SpawnTab(const FSpawnTabArgs& Args);`
- L50 _public prototype_ `TSharedPtr<SDockTab> ReuseTab(const FTabId& TabId) const;`
- L63 _private member_ `TSharedPtr<FTabManager> TabManager;`
- L64 _private member_ `TSharedPtr<FTabManager::FLayout> TabLayout;`
- L65 _private member_ `TArray<FImTabLayoutNode> WorkingLayoutNodeStack;`
- L66 _private member_ `TArray<FImTab> Tabs;`
- L67 _private member_ `FName TabGroupId = NAME_None;`
- L68 _private member_ `float CurrentSizeCoefficient = 1.f;`
- L69 _private member_ `bool bIsLayoutUpToDate = false;`

#### struct `SImTabGroup::FImTab`  
`struct FImTab`  
_L53-57_
- L55 _public member_ `FName TabId = NAME_None;`
- L56 _public member_ `TSharedPtr<SImTab> TabWidget;`

#### struct `SImTabGroup::FImTabLayoutNode`  
`struct FImTabLayoutNode`  
_L58-62_
- L60 _public member_ `TSharedRef<FTabManager::FLayoutNode> Node;`
- L61 _public member_ `int32 CurrentChildIndex = 0;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SLATEIM_API`

### `Plugins/Experimental/SlateIM/Source/SlateIM/Private/Containers/SImTableView.h` (Private)


#### class `FSlateIMTableHeader`  
`class FSlateIMTableHeader : public ISlateIMContainer, public ISlateIMChild, public TSharedFromThis<FSlateIMTableHeader>`  
_L17-39_
- inherits: `ISlateIMContainer,ISlateIMChild,TSharedFromThis<FSlateIMTableHeader>`
- desc: Header
- L24 _public function_ `virtual FString GetDebugName() override`
- L25 _public function_ `virtual int32 GetNumChildren() override`
- L26 _public function_ `virtual FSlateIMChild GetChild(int32 Index) override`
- L27 _public function_ `virtual FSlateIMChild GetContainer() override`
- L28 _public prototype_ `virtual void RemoveUnusedChildren(int32 LastUsedChildIndex) override;`
- L29 _public prototype_ `virtual void UpdateChild(FSlateIMChild Child, int32 Index, const FSlateIMSlotData& AlignmentData) override;`
- L31 _public prototype_ `virtual TSharedPtr<SWidget> GetAsWidget() override;`
- L33 _public prototype_ `TSharedPtr<SImTableView> GetOwningTable() const;`
- L34 _public prototype_ `void SetOwningTable(const TSharedPtr<SImTableView>& InOwningTable);`
- L37 _private member_ `TArray<FSlateIMChild> Children;`
- L38 _private member_ `TSharedPtr<SImTableView> OwningTable;`

#### class `SImTableHeader`  
`class SImTableHeader : public SHeaderRow`  
_L41-52_
- inherits: `SHeaderRow`
- L46 _public prototype_ `void Construct(const SHeaderRow::FArguments& InArgs, const TSharedRef<FSlateIMTableHeader> InHeader);`
- L48 _public prototype_ `TSharedPtr<FSlateIMTableHeader> GetHeader() const;`
- L51 _private member_ `TSharedPtr<FSlateIMTableHeader> Header;`

#### class `FSlateIMRowExpansionStateData`  
`class FSlateIMRowExpansionStateData`  
_L55-64_
- L58 _public prototype_ `bool HasSavedExpansionState(uint32 InRowId) const;`
- L59 _public prototype_ `bool GetSavedExpansionState(uint32 InRowId, bool bDefaultState = true) const;`
- L60 _public prototype_ `void SetSavedExpansionState(uint32 InRowId, bool bState);`
- L63 _private member_ `TMap<uint32, bool> ExpansionStates;`

#### class `FSlateIMTableRow`  
`class FSlateIMTableRow : public ISlateIMContainer, public ISlateIMChild, public FSlateIMRowExpansionStateData, public TSharedFromThis<FSlateIMTableRow>`  
_L69-114_
- inherits: `ISlateIMContainer,ISlateIMChild,FSlateIMRowExpansionStateData,TSharedFromThis<FSlateIMTableRow>`
- desc: Row
- L76 _public function_ `virtual FString GetDebugName() override`
- L77 _public function_ `virtual int32 GetNumChildren() override`
- L78 _public function_ `virtual FSlateIMChild GetChild(int32 Index) override`
- L79 _public function_ `virtual FSlateIMChild GetContainer() override`
- L80 _public prototype_ `virtual void RemoveUnusedChildren(int32 LastUsedChildIndex) override;`
- L81 _public prototype_ `virtual void UpdateChild(FSlateIMChild Child, int32 Index, const FSlateIMSlotData& AlignmentData) override;`
- L82 _public prototype_ `virtual TSharedPtr<SWidget> GetAsWidget() override;`
- L84 _public function_ `uint32 GetRowId() const`
- L85 _public function_ `void SetRowId(uint32 InRowId)`
- L87 _public prototype_ `void GetChildRows(TArray<TSharedRef<FSlateIMTableRow>>& OutRows) const;`
- L89 _public prototype_ `TSharedPtr<ISlateIMContainer> GetParent() const;`
- L90 _public prototype_ `void SetParent(TSharedPtr<ISlateIMContainer> InParent);`
- L92 _public prototype_ `int32 CountCellWidgetsUpToIndex(int32 Index) const;`
- L93 _public prototype_ `int32 FindColumnIndex(const FName& ColumnName) const;`
- L95 _public prototype_ `TSharedRef<SWidget> GetCellWidget(int32 CellIndex) const;`
- L97 _public function_ `int32 GetColumnCount() const`
- L98 _public prototype_ `void UpdateColumnCount(int32 NewColumnCount);`
- L100 _public prototype_ `TSharedPtr<SImTableView> GetOwningTable() const;`
- L101 _public prototype_ `void SetOwningTable(const TSharedPtr<SImTableView>& InOwningTable);`
- L103 _public prototype_ `bool IsExpanded();`
- L104 _public prototype_ `bool HasChildRows() const;`
- L105 _public prototype_ `bool ShouldDisplayExpander() const;`
- L106 _public prototype_ `bool AreTableRowContentsRequired();`
- L109 _private member_ `TWeakPtr<ISlateIMContainer> Parent;`
- L110 _private member_ `uint32 RowId = 0;`
- L111 _private member_ `TArray<FSlateIMChild> Children;`
- L112 _private member_ `int32 ColumnCount = 0;`
- L113 _private member_ `TSharedPtr<SImTableView> OwningTable;`

#### class `SImTableRow`  
`class SImTableRow : public SMultiColumnTableRow<TSharedRef<FSlateIMTableRow>>`  
_L116-127_
- inherits: `SMultiColumnTableRow<TSharedRef<FSlateIMTableRow>>`
- L121 _public prototype_ `void Construct(const FSuperRowType::FArguments& InArgs, const TSharedRef<SImTableView>& InOwnerTableView, const TSharedRef<FSlateIMTableRow>& InTableRow);`
- L123 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L126 _private member_ `TSharedPtr<FSlateIMTableRow> TableRow;`

#### class `FSlateIMTableBody`  
`class FSlateIMTableBody : public ISlateIMContainer, public ISlateIMChild, public FSlateIMRowExpansionStateData, public TSharedFromThis<FSlateIMTableBody>`  
_L134-161_
- inherits: `ISlateIMContainer,ISlateIMChild,FSlateIMRowExpansionStateData,TSharedFromThis<FSlateIMTableBody>`
- desc: Body
- L141 _public function_ `virtual FString GetDebugName() override`
- L142 _public function_ `virtual int32 GetNumChildren() override`
- L143 _public function_ `virtual FSlateIMChild GetChild(int32 Index) override`
- L144 _public function_ `virtual FSlateIMChild GetContainer() override`
- L145 _public prototype_ `virtual void RemoveUnusedChildren(int32 LastUsedChildIndex) override;`
- L146 _public prototype_ `virtual void UpdateChild(FSlateIMChild Child, int32 Index, const FSlateIMSlotData& AlignmentData) override;`
- L147 _public function_ `virtual TSharedPtr<SWidget> GetAsWidget() override`
- L149 _public prototype_ `TSharedPtr<SImTableView> GetOwningTable() const;`
- L150 _public prototype_ `void SetOwningTable(const TSharedPtr<SImTableView>& InOwningTable);`
- L152 _public prototype_ `TSharedPtr<FSlateIMTableRow> GetRow(int32 Index);`
- L154 _public prototype_ `bool IsTree() const;`
- L156 _public prototype_ `const TArray<TSharedRef<FSlateIMTableRow>>& GetTableRows() const;`
- L159 _private member_ `TArray<TSharedRef<FSlateIMTableRow>> Children;`
- L160 _private member_ `TSharedPtr<SImTableView> OwningTable;`

#### class `SImTableView`  
`class SImTableView : public ISlateIMContainer, public STreeView<TSharedRef<FSlateIMTableRow>>`  
_L170-269_
- inherits: `ISlateIMContainer,STreeView<TSharedRef<FSlateIMTableRow>>`
- desc: Table
- L176 _public prototype_ `void Construct(const FArguments& InArgs);`
- L178 _public function_ `virtual int32 GetNumChildren() override`
- L179 _public prototype_ `virtual FSlateIMChild GetChild(int32 Index) override;`
- L180 _public function_ `virtual FSlateIMChild GetContainer() override`
- L181 _public prototype_ `virtual void RemoveUnusedChildren(int32 LastUsedChildIndex) override;`
- L182 _public prototype_ `virtual void UpdateChild(FSlateIMChild Child, int32 Index, const FSlateIMSlotData& AlignmentData) override;`
- L184 _public prototype_ `virtual float GetNumLiveWidgets() const override;`
- L186 _public prototype_ `TSharedPtr<FSlateIMTableHeader> GetHeader() const;`
- L187 _public prototype_ `TSharedPtr<FSlateIMTableBody> GetBody() const;`
- L189 _public prototype_ `void AddColumn(const FName& ColumnID, const FStringView& ColumnToolTip, const FSlateIMSlotData& SlotData);`
- L191 _public function_ `int32 GetColumnCount() const`
- L193 _public prototype_ `void EndColumnUpdates();`
- L195 _public prototype_ `void BeginTableUpdates();`
- L196 _public prototype_ `void EndTableUpdates();`
- L198 _public prototype_ `void BeginTableContent();`
- L200 _public prototype_ `void UpdateColumns();`
- L202 _public prototype_ `void SetTableRowStyle(const FTableRowStyle* InRowStyle);`
- L205 _public prototype_ `bool IsTree() const;` — A table is a tree if any of its rows has children
- L207 _public prototype_ `void RequestRefresh();`
- L208 _public prototype_ `void RequestRebuild();`
- L210 _public prototype_ `TSharedRef<ITableRow> GenerateRow(TSharedRef<FSlateIMTableRow> InTableRow, const TSharedRef<STableViewBase>& OwnerTable);`
- L212 _public prototype_ `void GatherChildren(TSharedRef<FSlateIMTableRow> Row, TArray<TSharedRef<FSlateIMTableRow>>& OutChildren) const;`
- L214 _public prototype_ `TSharedPtr<FSlateIMTableRow> GetRow(int32 Index);`
- L216 _public prototype_ `int32 GetRowLinearizedIndex(const TSharedRef<FSlateIMTableRow>& Row) const;`
- L218 _public prototype_ `bool IsSameColumnCount(const TSharedRef<FSlateIMTableRow>& Row) const;`
- L219 _public prototype_ `int32 FindColumnIndex(const FName& ColumnName) const;`
- L221 _public prototype_ `void OnRowAdded();`
- L222 _public prototype_ `int32 GetRowCount() const;`
- L225 _private prototype_ `void AddColumn_Internal(const FName& ColumnId, const FStringView& ColumnToolTip, const FSlateIMSlotData& SlotData);`
- L227 _private prototype_ `void HandleOnExpansionChanged(TSharedRef<FSlateIMTableRow> InItem, bool bInExpanded);`
- L255 _private member_ `TSharedPtr<FSlateIMTableHeader> Header;`
- L256 _private member_ `TSharedPtr<FSlateIMTableBody> Body;`
- L257 _private member_ `const FTableRowStyle* RowStyle = nullptr;`
- L258 _private member_ `int32 ColumnCount = 0;`
- L259 _private member_ `int32 RowCount = 0;`
- L261 _private member_ `mutable int32 CachedNumLiveWidgets = 0;`
- L268 _private member_ `} DirtyState = NeedsRebuild;`

#### struct `SImTableView::FRowSource`  
`struct FRowSource : public UE::Slate::ItemsSource::IItemsSource<TSharedRef<FSlateIMTableRow>>`  
_L231-253_
- inherits: `UE::Slate::ItemsSource::IItemsSource<TSharedRef<FSlateIMTableRow>>`
- desc: Because the row source is now in a different object which can change, use this intermediary object to avoid issues updating the source.
- L233 _public member_ `SImTableView& OwningTable;`
- L235 _public function_ `FRowSource(SImTableView& InOwningTable) : OwningTable(InOwningTable)`
- L239 _public function_ `virtual const TArrayView<const TSharedRef<FSlateIMTableRow>> GetItems() const override`
- L249 _public function_ `virtual bool IsSame(const void* RawPointer) const override`

#### enum `SImTableView::(anonymous)`  
``  
_L264-268_

#### Free symbols / members of external scopes

- L265 _enumerator_ `Clean` (scope `SImTableView::__anonecb566710103`)
- L266 _enumerator_ `NeedsRefresh` (scope `SImTableView::__anonecb566710103`)
- L267 _enumerator_ `NeedsRebuild` (scope `SImTableView::__anonecb566710103`)

### `Plugins/Experimental/SlateIM/Source/SlateIM/Private/Containers/SImWrapBox.h` (Private)


#### class `SImWrapBox`  
`class SImWrapBox : public SWrapBox, public ISlateIMContainer`  
_L9-26_
- inherits: `SWrapBox,ISlateIMContainer`
- L15 _public prototype_ `virtual int32 GetNumChildren() override;`
- L16 _public prototype_ `virtual FSlateIMChild GetChild(int32 Index) override;`
- L18 _public function_ `virtual FSlateIMChild GetContainer() override`
- L23 _public prototype_ `virtual void RemoveUnusedChildren(int32 LastUsedChildIndex) override;`
- L25 _public prototype_ `virtual void UpdateChild(FSlateIMChild Child, int32 Index, const FSlateIMSlotData& AlignmentData) override;`

### `Plugins/Experimental/SlateIM/Source/SlateIM/Private/Misc/ISlateIMChild.h` (Private)


#### class `ISlateIMChild`  
`class ISlateIMChild : public ISlateIMTypeChecking`  
_L14-18_
- inherits: `ISlateIMTypeChecking`
- desc: Interface for non-widget children in the SlateIM hierarchy (eg. for virtualized listview entries)
- L17 _public prototype_ `virtual TSharedPtr<SWidget> GetAsWidget() = 0;`

#### struct `FSlateIMChild`  
`struct FSlateIMChild : private TUnion<TYPE_OF_NULLPTR, TSharedRef<SWidget>, TSharedRef<ISlateIMChild>>`  
_L20-78_
- inherits: `TUnion<TYPE_OF_NULLPTR,TSharedRef<SWidget>,TSharedRef<ISlateIMChild>>`
- L22 _public function_ `FSlateIMChild(TYPE_OF_NULLPTR = nullptr) : TUnion(nullptr)`
- L24 _public function_ `FSlateIMChild(const TSharedRef<SWidget>& Widget) : TUnion(Widget)`
- L26 _public function_ `FSlateIMChild(const TSharedRef<ISlateIMChild>& Entry) : TUnion(Entry)`
- L29 _public function_ `TSharedPtr<SWidget> GetWidget() const`
- L39 _public function_ `TSharedRef<SWidget> GetWidgetRef() const`
- L46 _public function_ `template<typename WidgetType> TSharedPtr<WidgetType> GetWidget() const`
- L57 _public function_ `TSharedPtr<ISlateIMChild> GetChild() const`
- L68 _public function_ `template<typename ChildType> TSharedPtr<ChildType> GetChild() const`

### `Plugins/Experimental/SlateIM/Source/SlateIM/Private/Misc/SlateIMExamples.h` (Private)


#### class `FSlateIMTestWidget`  
`class FSlateIMTestWidget`  
_L14-74_
- L17 _public prototype_ `void Draw();`
- L18 _public prototype_ `void DrawBasics();`
- L19 _public prototype_ `void DrawTables();`
- L20 _public prototype_ `void DrawGraphs();`
- L21 _public prototype_ `void DrawInputs();`
- L22 _public prototype_ `void DrawTabs();`
- L23 _public prototype_ `void DrawFilter();`
- L26 _private member_ `double CurrentTime = 0;`
- L27 _private member_ `double TimeSinceLastUpdate = 0;`
- L28 _private member_ `FString TimeText;`
- L29 _private member_ `FString ComboItemToAdd;`
- L30 _private member_ `bool CheckState = false;`
- L31 _private member_ `ECheckBoxState CheckStateEnum = ECheckBoxState::Undetermined;`
- L32 _private member_ `int32 SelectedItemIndex = 0;`
- L33 _private member_ `int32 SearchableComboBoxSelectedItemIndex = 0;`
- L34 _private member_ `float SliderVal = 5.0f;`
- L35 _private member_ `float SliderMax = 20.f;`
- L36 _private member_ `int32 SelectedItem = INDEX_NONE;`
- L37 _private member_ `int32 IntValue = 50;`
- L38 _private member_ `int32 IntMax = 100;`
- L39 _private member_ `bool bShouldBeDisabled = false;`
- L40 _private member_ `bool MenuCheckState = true;`
- L41 _private member_ `bool MenuToggleState = true;`
- L42 _private member_ `TOptional<EAppReturnType::Type> DialogResult;`
- L43 _private member_ `int32 NumItems = 10;`
- L44 _private member_ `int32 LiveNumItems = NumItems;`
- L45 _private member_ `FString NumItemsText = FString::FromInt(NumItems);`
- L46 _private member_ `bool bShouldLiveUpdateTable = false;`
- L47 _private member_ `bool bShouldAddCanada = true;`
- L48 _private member_ `bool bShouldAddChildRow = false;`
- L49 _private member_ `TArray<FString> ComboBoxItems = { TEXT("Option 1"), TEXT("Option 2"), TEXT(`
- L50 _private member_ `bool bRefreshComboItems = false;`
- L51 _private member_ `bool bIsButtonEnabled = true;`
- L52 _private member_ `int32 DynamicTabCount = 3;`
- L53 _private member_ `FSlateIMStringFilter FruitFilter;`
- L54 _private member_ `TOptional<TArray<FString>> FilteredFruitList;`
- L55 _private member_ `int32 SelectedKitchenInstrument = INDEX_NONE;`
- L56 _private member_ `TRingBuffer<double> SquareGraphValues;`
- L57 _private member_ `TRingBuffer<FVector2D> SinGraphValues = { FVector2D(0, FMath::Sin(0.0)) };`
- L58 _private member_ `TRingBuffer<FVector2D> CosGraphValues = { FVector2D(0, FMath::Cos(0.0)) };`
- L59 _private member_ `TRingBuffer<FVector2D> TanGraphValues = { FVector2D(0, FMath::Tan(0.0)) };`
- L61 _private member_ `FSlateBrush WBrush;`
- L62 _private member_ `FSlateBrush ABrush;`
- L63 _private member_ `FSlateBrush SBrush;`
- L64 _private member_ `FSlateBrush DBrush;`
- L66 _private member_ `FSlateBrush LMBBrush;`
- L67 _private member_ `FSlateBrush RMBBrush;`
- L70 _private member_ `TSoftObjectPtr<UTexture2D> RedIcon = TSoftObjectPtr<UTexture2D>(FSoftObjectPath(TEXT("/Engi`
- L71 _private member_ `TSoftObjectPtr<UTexture2D> GreenIcon = TSoftObjectPtr<UTexture2D>(FSoftObjectPath(TEXT("/Engi`
- L72 _private member_ `int32 CanvasRenderCount = 0;`

#### class `FSlateStyleBrowser`  
`class FSlateStyleBrowser : public FSlateIMWindowBase`  
_L76-92_
- inherits: `FSlateIMWindowBase`
- L79 _public function_ `FSlateStyleBrowser() : FSlateIMWindowBase(TEXT("SlateIM Style Browser"), FVector2f(1000, 500), false, TEXT("SlateIM.ToggleSlateStyleBrowser"), TEXT("Opens a window that previews available slate styles"))`
- L83 _public prototype_ `virtual void DrawWindow(float DeltaTime) override;`
- L86 _private member_ `FString SearchString;`
- L87 _private member_ `FString PreviewText;`
- L88 _private member_ `float SpinBoxValue = 66.7f;`
- L89 _private member_ `float SliderValue = 66.7f;`
- L90 _private member_ `int32 SelectedComboIndex = INDEX_NONE;`
- L91 _private member_ `int32 SelectedListIndex = INDEX_NONE;`

#### class `FSlateIMTestWindowWidget`  
`class FSlateIMTestWindowWidget : public FSlateIMWindowBase`  
_L94-105_
- inherits: `FSlateIMWindowBase`
- L97 _public function_ `FSlateIMTestWindowWidget(const TCHAR* Command, const TCHAR* CommandHelp) : FSlateIMWindowBase(TEXT("SlateIM Test Suite"), FVector2f(700, 900), false, Command, CommandHelp)`
- L101 _public prototype_ `virtual void DrawWindow(float DeltaTime) override;`
- L104 _private member_ `FSlateIMTestWidget TestWidget;`

#### class `FSlateIMTestNomadTabWidget`  
`class FSlateIMTestNomadTabWidget : public FSlateIMNomadTabBase`  
_L107-118_
- inherits: `FSlateIMNomadTabBase`
- L110 _public function_ `FSlateIMTestNomadTabWidget(const TCHAR* Command, const TCHAR* CommandHelp) : FSlateIMNomadTabBase(TEXT("SlateIM Test Suite"), Command, CommandHelp)`
- L114 _public prototype_ `virtual void DrawContent(float DeltaTime) override;`
- L117 _private member_ `FSlateIMTestWidget TestWidget;`

#### class `FSlateIMTestViewportWidget`  
`class FSlateIMTestViewportWidget : public FSlateIMWidgetWithCommandBase`  
_L121-137_
- inherits: `FSlateIMWidgetWithCommandBase`
- L124 _public function_ `FSlateIMTestViewportWidget(const TCHAR* Command, const TCHAR* CommandHelp) : FSlateIMWidgetWithCommandBase(Command, CommandHelp)`
- L132 _public prototype_ `virtual void DrawWidget(float DeltaTime) override;`
- L135 _private member_ `FSlateIMTestWidget TestWidget;`
- L136 _private member_ `SlateIM::FViewportRootLayout Layout;`

### `Plugins/Experimental/SlateIM/Source/SlateIM/Private/Misc/SlateIMInputState.h` (Private)


#### enum `ESlateIMKeyState`  
`enum class ESlateIMKeyState : uint8`  
_L7-13_
- L9 _public enumerator_ `Idle`
- L10 _public enumerator_ `Pressed`
- L11 _public enumerator_ `Held`
- L12 _public enumerator_ `Released`

#### struct `FSlateIMInputState`  
`struct FSlateIMInputState`  
_L15-19_
- L17 _public member_ `TMap<FKey, ESlateIMKeyState> KeyStateMap;`
- L18 _public member_ `TMap<FKey, float> AnalogValueMap;`

### `Plugins/Experimental/SlateIM/Source/SlateIM/Private/Misc/SlateIMLogging.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSlateIM, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSlateIM, Log, All);`

### `Plugins/Experimental/SlateIM/Source/SlateIM/Private/Misc/SlateIMManager.h` (Private)


#### struct `SlateIM::FContainerNode`  
`struct FContainerNode`  
_L33-44_
- L35 _public function_ `FContainerNode(TSharedPtr<ISlateIMContainer> InWidget) : Widget(InWidget)`
- L39 _public function_ `bool IsValid() const`
- L42 _public member_ `TSharedPtr<ISlateIMContainer> Widget;` — Current State
- L43 _public member_ `int32 LastUsedChildIndex = INDEX_NONE;`

#### struct `SlateIM::FWidgetHash`  
`struct FWidgetHash`  
_L46-63_
- L48 _public member_ `FXxHash64 AlignmentHash;`
- L49 _public member_ `FXxHash64 DataHash;`
- L51 _public function_ `FWidgetHash()`
- L54 _public function_ `FWidgetHash(FXxHash64 InAlignmentHash, FXxHash64 InDataHash) : AlignmentHash(InAlignmentHash) , DataHash(InDataHash)`
- L59 _public function_ `bool IsValid() const`

#### struct `SlateIM::FRootNode`  
`struct FRootNode`  
_L65-103_
- L67 _public prototype_ `FRootNode(FName InRootName, TSharedPtr<ISlateIMRoot> InRootWidget, bool InRootState);`
- L69 _public prototype_ `FWidgetHash GetWidgetHash() const;`
- L71 _public prototype_ `void SetDataHash(FXxHash64 InDataHash);`
- L73 _public prototype_ `void SetAlignmentHash(FXxHash64 AlignmentHash);`
- L75 _public function_ `void SetDisabledState()`
- L76 _public function_ `void SetEnabledState()`
- L78 _public prototype_ `void SetNextToolTip(const FStringView& InNextToolTip);`
- L80 _public prototype_ `void ActivateTab();`
- L82 _public member_ `FContainerNode RootContainer;`
- L84 _public member_ `TArray<FContainerNode> CurrentContainerStack;`
- L85 _public member_ `TArray<TSharedPtr<SImContextMenuAnchor>> CurrentMenuAnchorStack;`
- L87 _public member_ `TArray<FWidgetHash> WidgetTreeDataHash;`
- L89 _public member_ `TSharedPtr<ISlateIMRoot> RootWidget;`
- L92 _public member_ `TMap<FName, TWeakPtr<SImTab>> Tabs;` — Store a list of tabs so that when ActivateTab is called at the end of layout, any registered tab can be activated.
- L93 _public member_ `TSet<FName> TabsToActivate;`
- L95 _public member_ `FString CurrentToolTip;`
- L96 _public member_ `uint64 DataHash = 0;`
- L97 _public member_ `FName RootName = NAME_None;`
- L98 _public member_ `int32 CurrentWidgetIndex = 0;`
- L99 _public member_ `double LastAccessTime = 0;`
- L100 _public member_ `bool RootState = false;`
- L101 _public member_ `bool bCurrentEnabledState = true;`
- L102 _public member_ `bool bActivatedThisFrame = false;`

#### struct `SlateIM::FWidgetActivation`  
`struct FWidgetActivation`  
_L105-115_
- L107 _public member_ `FName RootName = NAME_None;`
- L108 _public member_ `int32 ContainerIndex = INDEX_NONE;`
- L109 _public member_ `int32 WidgetIndex = INDEX_NONE;`
- L111 _public function_ `bool operator==(const FWidgetActivation& Other) const`

#### struct `SlateIM::FSlateIMAlignmentState`  
`struct FSlateIMAlignmentState`  
_L117-127_
- L119 _public member_ `TOptional<FMargin> Padding;`
- L120 _public member_ `TOptional<EHorizontalAlignment> HAlign;`
- L121 _public member_ `TOptional<EVerticalAlignment> VAlign;`
- L122 _public member_ `TOptional<bool> AutoSize;`
- L123 _public member_ `TOptional<float> MinWidth;`
- L124 _public member_ `TOptional<float> MinHeight;`
- L125 _public member_ `TOptional<float> MaxWidth;`
- L126 _public member_ `TOptional<float> MaxHeight;`

#### class `SlateIM::FSlateIMManager`  
`class FSlateIMManager`  
_L129-270_
- L132 _public prototype_ `static void Initialize();`
- L133 _public prototype_ `static FSlateIMManager& Get();`
- L135 _public prototype_ `FSlateIMManager();`
- L136 _public prototype_ `~FSlateIMManager();`
- L139 _public prototype_ `template<typename RootType> FRootNode* FindRoot(const FName WindowId);`
- L140 _public prototype_ `FRootNode& AddRoot(const FName WindowId, TSharedPtr<ISlateIMRoot> NewRoot);`
- L142 _public prototype_ `void BeginRoot(FName RootName);`
- L143 _public prototype_ `void EndRoot();`
- L145 _public prototype_ `void PushContainer(FContainerNode&& Node);`
- L147 _public prototype_ `template<typename ContainerType> void PopContainer();`
- L149 _public prototype_ `template<typename ContainerType> TSharedPtr<ContainerType> GetCurrentContainer() const;`
- L151 _public prototype_ `template<typename ContainerType> TSharedPtr<ContainerType> FindMostRecentContainer() const;`
- L152 _public prototype_ `const FContainerNode* GetCurrentContainerNode() const;`
- L154 _public prototype_ `void PushMenuRoot(TSharedPtr<SImContextMenuAnchor>& MenuRoot);`
- L155 _public prototype_ `void PopMenuRoot();`
- L156 _public prototype_ `TSharedPtr<SImContextMenuAnchor> GetCurrentMenuRoot() const;`
- L159 _public prototype_ `template<typename WidgetType> TSharedPtr<WidgetType> BeginIMWidget();`
- L160 _public prototype_ `TSharedPtr<SWidget> BeginCustomWidget(TSharedPtr<SWidget> ExpectedWidget);`
- L161 _public prototype_ `void EndWidget(bool bResetAlignmentData);`
- L163 _public prototype_ `void EnsureCurrentContainerNode();`
- L166 _public prototype_ `FSlateIMChild GetCurrentChild() const;` — Gets the widget which should be at the current spot in the hierarchy or null if it doesn't exist
- L167 _public prototype_ `TSharedPtr<SWidget> GetCurrentChildAsWidget() const;`
- L168 _public prototype_ `const FRootNode& GetCurrentRoot() const;`
- L169 _public prototype_ `FRootNode& GetMutableCurrentRoot();`
- L170 _public function_ `bool HasCurrentRoot() const`
- L172 _public prototype_ `void UpdateCurrentChild(FSlateIMChild Child, const FSlateIMSlotData& AlignmentData);`
- L173 _public prototype_ `void AdvanceToNextWidget();`
- L175 _public prototype_ `void ActivateWidget(const TSharedPtr<FSlateIMWidgetActivationMetadata>& ActivationData);`
- L176 _public prototype_ `bool IsWidgetActivatedThisFrame(const TSharedPtr<FSlateIMWidgetActivationMetadata>& ActivationData) const;`
- L178 _public function_ `FSlateIMSlotData GetCurrentAlignmentData( const FMargin& DefaultPadding, const EHorizontalAlignment DefaultHAlign, const EVerticalAlignment DefaultVAlign, const bool bDefaultAutoSize, const float DefaultMinWidth, const float DefaultMinHeight, const float DefaultMaxWidth, const float DefaultMaxHeight) const`
- L199 _public prototype_ `void ResetAlignmentData();`
- L201 _public function_ `FSlateIMAlignmentState SaveAlignmentState() const`
- L215 _public function_ `void RestoreAlignmentState(const FSlateIMAlignmentState& AlignmentState)`
- L227 _public prototype_ `void OnSlateIMModalOpened();`
- L228 _public prototype_ `void OnSlateIMModalClosed();`
- L229 _public prototype_ `bool CanUpdateSlateIM() const;`
- L231 _public member_ `TOptional<FMargin> NextPadding;`
- L232 _public member_ `TOptional<EHorizontalAlignment> NextHAlign;`
- L233 _public member_ `TOptional<EVerticalAlignment> NextVAlign;`
- L234 _public member_ `TOptional<bool> NextAutoSize;`
- L235 _public member_ `TOptional<float> NextMinWidth;`
- L236 _public member_ `TOptional<float> NextMinHeight;`
- L237 _public member_ `TOptional<float> NextMaxWidth;`
- L238 _public member_ `TOptional<float> NextMaxHeight;`
- L241 _private prototype_ `void ValidateRootName(FName RootName) const;`
- L243 _private prototype_ `void Tick(float DeltaTime);`
- L245 _private prototype_ `void OnSlateShutdown();`
- L247 _private prototype_ `void RemoveUnusedChildren(FContainerNode& Container);`
- L249 _private prototype_ `void PopContainer_Internal();`
- L251 _private member_ `static TUniquePtr<FSlateIMManager> Instance;`
- L253 _private member_ `TMap<FName, FRootNode> RootMap;`
- L254 _private member_ `TArray<FWidgetActivation, TInlineAllocator<4>> ActivatedWidgets;`
- L255 _private member_ `FRootNode* CurrentRoot = nullptr;`
- L257 _private member_ `TUniquePtr<FMemMark> MemMark;`
- L259 _private member_ `bool bBuildingImmediateModeWidgets = false;`
- L260 _private member_ `bool bIsSlateIMModalOpen = false;`
- L263 _private member_ `FSlateStyleBrowser SlateStyleBrowser;`
- L264 _private member_ `FSlateIMTestWindowWidget TestWindowWidget;`
- L265 _private member_ `FSlateIMTestNomadTabWidget TestNomadTabWidget;`
- L267 _private member_ `FSlateIMTestViewportWidget TestViewportWidget;`
- L273 _function_ `template <typename RootType> FRootNode* FSlateIMManager::FindRoot(const FName WindowId)`
- L287 _function_ `template <typename ContainerType> void FSlateIMManager::PopContainer()`
- L294 _function_ `template <typename ContainerType> TSharedPtr<ContainerType> FSlateIMManager::GetCurrentContainer() const`
- L307 _function_ `template <typename ContainerType> TSharedPtr<ContainerType> FSlateIMManager::FindMostRecentContainer() const`
- L324 _function_ `template <typename WidgetType> TSharedPtr<WidgetType> FSlateIMManager::BeginIMWidget()`

#### Free symbols / members of external scopes

- L31 _namespace_ `namespace SlateIM`

### `Plugins/Experimental/SlateIM/Source/SlateIM/Private/Misc/SlateIMSlateResources.h` (Private)


#### struct `SlateIM::FSlateIMDataStore`  
`template<typename DataType> struct FSlateIMDataStore : ISlateMetaData`  
_L13-28_
- inherits: `ISlateMetaData`
- L15 _public prototype_ `SLATE_METADATA_TYPE(FSlateIMDataStore, ISlateMetaData);`
- L17 _public function_ `FSlateIMDataStore(DataType&& InData) : Data(MoveTemp(InData))`
- L22 _public function_ `FSlateIMDataStore(const DataType& InData) : Data(InData)`
- L27 _public member_ `DataType Data;`

#### struct `SlateIM::FPinnedObjectResource`  
`struct FPinnedObjectResource`  
_L33-36_
- desc: Object Resource
- L35 _public member_ `TStrongObjectPtr<UObject> PinnedResource;`

#### struct `SlateIM::FSlateIMPinnedObjectResourceDataStore`  
`struct FSlateIMPinnedObjectResourceDataStore : FSlateIMDataStore<FPinnedObjectResource>`  
_L40-56_
- inherits: `FSlateIMDataStore<FPinnedObjectResource>`
- L42 _public typedef_ `using Super = FSlateIMDataStore<FPinnedObjectResource>;`
- L44 _public function_ `FSlateIMPinnedObjectResourceDataStore(FPinnedObjectResource&& InData) : Super(MoveTemp(InData))`
- L49 _public function_ `FSlateIMPinnedObjectResourceDataStore(const FPinnedObjectResource& InData) : Super(InData)`
- L54 _public function_ `static const FName& GetTypeId()`
- L55 _public function_ `virtual bool IsOfTypeImpl(const FName& Type) const override`

#### struct `SlateIM::FPinnedImageResource`  
`struct FPinnedImageResource`  
_L61-65_
- desc: Image Resource
- L63 _public member_ `FSlateBrush Brush;`
- L64 _public member_ `TStrongObjectPtr<UObject> PinnedResource;`

#### struct `SlateIM::FSlateIMPinnedImageResourceDataStore`  
`struct FSlateIMPinnedImageResourceDataStore : FSlateIMDataStore<FPinnedImageResource>`  
_L69-85_
- inherits: `FSlateIMDataStore<FPinnedImageResource>`
- L71 _public typedef_ `using Super = FSlateIMDataStore<FPinnedImageResource>;`
- L73 _public function_ `FSlateIMPinnedImageResourceDataStore(FPinnedImageResource&& InData) : Super(MoveTemp(InData))`
- L78 _public function_ `FSlateIMPinnedImageResourceDataStore(const FPinnedImageResource& InData) : Super(InData)`
- L83 _public function_ `static const FName& GetTypeId()`
- L84 _public function_ `virtual bool IsOfTypeImpl(const FName& Type) const override`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace SlateIM`
- L38 _typedef_ `using FUObjectObjectResource = FSlateIMDataStore<FPinnedObjectResource>;` (scope `SlateIM`)
- L67 _typedef_ `using FUObjectImageResource = FSlateIMDataStore<FPinnedImageResource>;` (scope `SlateIM`)

### `Plugins/Experimental/SlateIM/Source/SlateIM/Private/Misc/SlateIMSlotData.h` (Private)


#### struct `FSlateIMSlotData`  
`struct FSlateIMSlotData`  
_L24-67_
- L26 _public function_ `FSlateIMSlotData(const FMargin& InPadding, const EHorizontalAlignment InHAlign, const EVerticalAlignment InVAlign, bool bInAutoSize, float InMinWidth, float InMinHeight, float InMaxWidth, float InMaxHeight) : Padding(InPadding) , HorizontalAlignment(InHAlign) , VerticalAlignment(InVAlign) , bAutoSize(bInAutoSize) , MinWidth(InMinWidth) , MinHeight(InMinHeight) , MaxWidth(InMaxWidth) , MaxHeight(InMaxHeight) , Hash(GetAlignmentHash())`
- L39 _public member_ `const FMargin Padding = SlateIM::Defaults::Padding;`
- L40 _public member_ `const EHorizontalAlignment HorizontalAlignment = SlateIM::Defaults::HAlign;`
- L41 _public member_ `const EVerticalAlignment VerticalAlignment = SlateIM::Defaults::VAlign;`
- L42 _public member_ `const bool bAutoSize = SlateIM::Defaults::bAutoSize;`
- L43 _public member_ `const float MinWidth = SlateIM::Defaults::MinWidth;`
- L44 _public member_ `const float MinHeight = SlateIM::Defaults::MinHeight;`
- L45 _public member_ `const float MaxWidth = SlateIM::Defaults::MaxWidth;`
- L46 _public member_ `const float MaxHeight = SlateIM::Defaults::MaxHeight;`
- L47 _public member_ `const FXxHash64 Hash;`
- L50 _private function_ `FXxHash64 GetAlignmentHash() const`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace SlateIM`
- L10 _namespace_ `namespace Defaults` (scope `SlateIM`)
- L12 _variable_ `const FMargin Padding(3.0f, 3.0f, 3.0f, 3.0f);` (scope `SlateIM::Defaults`)
- L13 _variable_ `constexpr EHorizontalAlignment HAlign = HAlign_Left;` (scope `SlateIM::Defaults`)
- L14 _variable_ `constexpr EVerticalAlignment VAlign = VAlign_Fill;` (scope `SlateIM::Defaults`)
- L15 _variable_ `constexpr bool bAutoSize = true;` (scope `SlateIM::Defaults`)
- L16 _variable_ `constexpr float MinWidth = 0.0f;` (scope `SlateIM::Defaults`)
- L17 _variable_ `constexpr float MinHeight = 0.0f;` (scope `SlateIM::Defaults`)
- L18 _variable_ `constexpr float MaxWidth = 0.0f;` (scope `SlateIM::Defaults`)
- L19 _variable_ `constexpr float MaxHeight = 0.0f;` (scope `SlateIM::Defaults`)
- L20 _variable_ `constexpr float InputWidgetWidth = 200.f;` (scope `SlateIM::Defaults`)

### `Plugins/Experimental/SlateIM/Source/SlateIM/Private/Misc/SlateIMTypeChecking.h` (Private)


#### class `ISlateIMTypeChecking`  
`class ISlateIMTypeChecking`  
_L7-23_
- L11 _public function_ `template<class TType> bool IsA() const`
- L16 _public prototype_ `virtual ~ISlateIMTypeChecking() = default;`
- L19 _protected function_ `virtual bool IsAImpl(const FName&) const`

#### Free symbols / members of external scopes

- L25 _macro_ `#define SLATE_IM_TYPE_DATA(TYPE, BASE) \`

### `Plugins/Experimental/SlateIM/Source/SlateIM/Private/Misc/SlateIMWidgetActivationMetadata.h` (Private)


#### struct `FSlateIMWidgetActivationMetadata`  
`struct FSlateIMWidgetActivationMetadata : ISlateMetaData`  
_L7-20_
- inherits: `ISlateMetaData`
- L9 _public prototype_ `SLATE_METADATA_TYPE(FSlateIMWidgetActivationMetadata, ISlateMetaData);`
- L11 _public function_ `FSlateIMWidgetActivationMetadata(const FName& RootName, int32 ContainerIndex, int32 WidgetIndex) : RootName(RootName) , ContainerIndex(ContainerIndex) , WidgetIndex(WidgetIndex)`
- L17 _public member_ `FName RootName = NAME_None;`
- L18 _public member_ `int32 ContainerIndex = INDEX_NONE;`
- L19 _public member_ `int32 WidgetIndex = INDEX_NONE;`

### `Plugins/Experimental/SlateIM/Source/SlateIM/Private/Misc/SlateIMWidgetScope.h` (Private)


#### struct `SlateIM::FWidgetScope`  
`template<typename WidgetType, bool CanHaveMetadata = TIsDerivedFrom<WidgetType, SWidget>::Value> struct FWidgetScope`  
_L11-213_
- L13 _public function_ `FWidgetScope(const FMargin DefaultPadding = Defaults::Padding, const EHorizontalAlignment DefaultHAlign = Defaults::HAlign, const EVerticalAlignment DefaultVAlign = Defaults::VAlign, const bool bDefaultAutoSize = Defaults::bAutoSize, const float DefaultMinWidth = Defaults::MinWidth, const float DefaultMinHeight = Defaults::MinHeight, const float DefaultMaxWidth = Defaults::MaxWidth, const float DefaultMaxHeight = Defaults::MaxHeight) : Widget(FSlateIMManager::Get().BeginIMWidget<WidgetType>()) , AlignmentData(FSlateIMManager::Get().GetCurrentAlignmentData(DefaultPadding, DefaultHAlign, DefaultVAlign, bDefaultAutoSize, DefaultMinWidth, DefaultMinHeight, DefaultMaxWidth, DefaultMaxHeight)) , DataHash() , bIsSlotDirty(false)`
- L37 _public function_ `FWidgetScope(const bool bAutoSize) : FWidgetScope(Defaults::Padding, Defaults::HAlign, Defaults::VAlign, bAutoSize)`
- L42 _public function_ `FWidgetScope(const TSharedPtr<SWidget> ExpectedWidget, const FMargin DefaultPadding = Defaults::Padding, const EHorizontalAlignment DefaultHAlign = Defaults::HAlign, const EVerticalAlignment DefaultVAlign = Defaults::VAlign, const bool bDefaultAutoSize = Defaults::bAutoSize, const float DefaultMinWidth = Defaults::MinWidth, const float DefaultMinHeight = Defaults::MinHeight, const float DefaultMaxWidth = Defaults::MaxWidth, const float DefaultMaxHeight = Defaults::MaxHeight) : Widget(FSlateIMManager::Get().BeginCustomWidget(ExpectedWidget)) , AlignmentData(FSlateIMManager::Get().GetCurrentAlignmentData(DefaultPadding, DefaultHAlign, DefaultVAlign, bDefaultAutoSize, DefaultMinWidth, DefaultMinHeight, DefaultMaxWidth, DefaultMaxHeight)) , DataHash() , bIsSlotDirty(false)`
- L67 _public function_ `~FWidgetScope()`
- L127 _public function_ `TSharedPtr<WidgetType> GetWidget()`
- L129 _public function_ `void UpdateWidget(TSharedPtr<WidgetType> NewWidget)`
- L143 _public function_ `TSharedPtr<WidgetType> GetOrCreate(const TFunction<TSharedPtr<WidgetType>(void)>& WidgetCreationFunction)`
- L156 _public function_ `template<typename T> void HashData(const T& Data)`
- L161 _public function_ `void HashStringView(const FStringView& String)`
- L166 _public function_ `bool IsDataHashDirty() const`
- L172 _public function_ `bool IsActivatedThisFrame() const`
- L177 _public function_ `TSharedPtr<FSlateIMWidgetActivationMetadata> GetOrCreateActivationMetadata()`
- L207 _private member_ `TSharedPtr<WidgetType> Widget;`
- L208 _private member_ `TSharedPtr<FSlateIMWidgetActivationMetadata> ActivationMetadata;`
- L209 _private member_ `FSlateIMSlotData AlignmentData;`
- L210 _private member_ `FXxHash64Builder HashBuilder;`
- L211 _private member_ `mutable FXxHash64 DataHash;`
- L212 _private member_ `bool bIsSlotDirty = false;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace SlateIM`

### `Plugins/Experimental/SlateIM/Source/SlateIM/Private/Roots/ISlateIMRoot.h` (Private)


#### class `ISlateIMRoot`  
`class ISlateIMRoot : public ISlateIMTypeChecking`  
_L15-24_
- inherits: `ISlateIMTypeChecking`
- L18 _public prototype_ `virtual void UpdateChild(TSharedRef<SWidget> Child, const FSlateIMSlotData& AlignmentData) = 0;`
- L19 _public prototype_ `virtual bool IsVisible() const = 0;`
- L21 _public prototype_ `virtual FSlateIMInputState& GetInputState() = 0;`
- L23 _public prototype_ `virtual TSharedRef<SDockTab> GetRootTab() const = 0;`

### `Plugins/Experimental/SlateIM/Source/SlateIM/Private/Roots/SlateIMExposedRoot.h` (Private)


#### class `FSlateIMExposedRoot`  
`class FSlateIMExposedRoot : public ISlateIMRoot`  
_L9-27_
- inherits: `ISlateIMRoot`
- L14 _public prototype_ `FSlateIMExposedRoot();`
- L17 _public prototype_ `virtual void UpdateChild(TSharedRef<SWidget> Child, const FSlateIMSlotData& AlignmentData) override;`
- L18 _public function_ `virtual bool IsVisible() const override`
- L19 _public prototype_ `virtual FSlateIMInputState& GetInputState() override;`
- L20 _public prototype_ `virtual TSharedRef<SDockTab> GetRootTab() const override;`
- L22 _public prototype_ `TSharedRef<SWidget> GetExposedWidget() const;`
- L25 _private member_ `TSharedRef<SImWrapper> ExposedWidget;`
- L26 _private member_ `TSharedRef<SDockTab> RootTab;`

### `Plugins/Experimental/SlateIM/Source/SlateIM/Private/Roots/SlateIMViewportRoot.h` (Private)


#### class `FSlateIMViewportRoot`  
`class FSlateIMViewportRoot : public ISlateIMRoot`  
_L21-55_
- inherits: `ISlateIMRoot`
- L26 _public prototype_ `FSlateIMViewportRoot(UGameViewportClient* InGameViewport);`
- L27 _public prototype_ `FSlateIMViewportRoot(ULocalPlayer* InLocalPlayer);`
- L29 _public prototype_ `FSlateIMViewportRoot(TSharedPtr<IAssetViewport> InLevelViewport);`
- L33 _public prototype_ `virtual void UpdateChild(TSharedRef<SWidget> Child, const FSlateIMSlotData& AlignmentData) override;`
- L34 _public function_ `virtual bool IsVisible() const override`
- L38 _public prototype_ `virtual FSlateIMInputState& GetInputState() override;`
- L39 _public prototype_ `virtual TSharedRef<SDockTab> GetRootTab() const override;`
- L41 _public prototype_ `void UpdateViewport(const SlateIM::FViewportRootLayout& Layout);`
- L43 _public member_ `TWeakObjectPtr<UGameViewportClient> GameViewport;`
- L44 _public member_ `TWeakObjectPtr<ULocalPlayer> LocalPlayer;`
- L46 _public member_ `TWeakPtr<IAssetViewport> AssetViewport;`
- L50 _private member_ `TSharedPtr<SScaleBox> ScaleBox;`
- L51 _private member_ `TSharedPtr<SImWrapper> Wrapper;`
- L52 _private member_ `TSharedPtr<SWidget> ViewportRoot;`
- L53 _private member_ `SConstraintCanvas::FSlot* Slot = nullptr;`
- L54 _private member_ `TSharedRef<SDockTab> RootTab;`

### `Plugins/Experimental/SlateIM/Source/SlateIM/Private/Roots/SlateIMWindowRoot.h` (Private)


#### class `FSlateIMWindowRoot`  
`class FSlateIMWindowRoot : public ISlateIMRoot`  
_L11-32_
- inherits: `ISlateIMRoot`
- L16 _public prototype_ `FSlateIMWindowRoot(TSharedRef<SWindow> Window);`
- L19 _public prototype_ `virtual void UpdateChild(TSharedRef<SWidget> Child, const FSlateIMSlotData& AlignmentData) override;`
- L20 _public prototype_ `virtual bool IsVisible() const override;`
- L21 _public prototype_ `virtual FSlateIMInputState& GetInputState() override;`
- L22 _public prototype_ `virtual TSharedRef<SDockTab> GetRootTab() const override;`
- L24 _public prototype_ `void UpdateWindow(const FStringView& Title);`
- L26 _public prototype_ `TSharedPtr<SWindow> GetWindow() const;`
- L29 _private member_ `TWeakPtr<SWindow> RootWindow;`
- L30 _private member_ `TSharedPtr<SImWrapper> WindowRootWidget;`
- L31 _private member_ `TSharedRef<SDockTab> RootTab;`

### `Plugins/Experimental/SlateIM/Source/SlateIM/Private/SlateIMStyle.h` (Private)


#### class `FSlateIMStyle`  
`class FSlateIMStyle final : public FSlateStyleSet`  
_L7-18_
- inherits: `FSlateStyleSet`
- L10 _public function_ `static FSlateIMStyle& Get()`
- L16 _public prototype_ `FSlateIMStyle();`

### `Plugins/Experimental/SlateIM/Source/SlateIM/Private/SlateIM_Internal.h` (Private)


#### Free symbols / members of external scopes

- L15 _namespace_ `namespace SlateIM`
- L17 _prototype_ `void BeginContainer();` (scope `SlateIM`)
- L18 _prototype_ `void EndContainer();` (scope `SlateIM`)
- L20 _prototype_ `void BeginStack(EOrientation Orientation);` (scope `SlateIM`)
- L21 _prototype_ `void EndStack();` (scope `SlateIM`)
- L23 _prototype_ `void BeginWrap(EOrientation Orientation);` (scope `SlateIM`)
- L24 _prototype_ `void EndWrap();` (scope `SlateIM`)
- L26 _prototype_ `void Image_Internal(const FImageParams& Params, TFunctionRef<const FSlateBrush* (const TSharedRef<SImage>&)> GetBrush);` (scope `SlateIM`)

### `Plugins/Experimental/SlateIM/Source/SlateIM/Private/Widgets/SImButton.h` (Private)


#### class `SImButton`  
`class SImButton : public SButton`  
_L10-25_
- inherits: `SButton`
- L15 _public function_ `SLATE_BEGIN_ARGS(SImButton)`
- L16 _public prototype_ `SLATE_EVENT(FOnClicked, OnClicked) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L21 _public prototype_ `void SetText(const FStringView& InText);`
- L24 _private member_ `TSharedPtr<STextBlock> TextBox;`

### `Plugins/Experimental/SlateIM/Source/SlateIM/Private/Widgets/SImCheckBox.h` (Private)


#### class `SImCheckBox`  
`class SImCheckBox : public SCheckBox`  
_L9-25_
- inherits: `SCheckBox`
- L14 _public function_ `SLATE_BEGIN_ARGS(SImCheckBox)`
- L15 _public prototype_ `SLATE_ATTRIBUTE(ECheckBoxState, IsChecked) SLATE_EVENT(FOnCheckStateChanged, OnCheckStateChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L21 _public prototype_ `void SetText(const FText& InText);`
- L24 _private member_ `TSharedPtr<STextBlock> TextBox;`

### `Plugins/Experimental/SlateIM/Source/SlateIM/Private/Widgets/SImGraph.h` (Private)


#### struct `FSlateIMLineGraphData`  
`struct FSlateIMLineGraphData`  
_L10-18_
- L12 _public member_ `TArray<FVector2D> NormalizedPoints;`
- L13 _public member_ `FLinearColor Color = FLinearColor::White;`
- L14 _public member_ `float LineThickness = 1.0f;`
- L15 _public member_ `FDoubleRange XViewRange;`
- L16 _public member_ `FDoubleRange YViewRange;`
- L17 _public member_ `bool bIsStale = false;`

#### class `SImGraph`  
`class SImGraph : public SLeafWidget`  
_L20-43_
- inherits: `SLeafWidget`
- L25 _public function_ `SLATE_BEGIN_ARGS(SImGraph)`
- L26 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L30 _public prototype_ `void BeginGraph();`
- L31 _public prototype_ `void EndGraph();`
- L33 _public prototype_ `void AddLineGraph(const TArrayView<FVector2D>& Points, const SlateIM::FGraphLinePointsParams& Params);`
- L34 _public prototype_ `void AddLineGraph(const TArrayView<double>& Values, const SlateIM::FGraphLineValuesParams& Params);`
- L37 _private prototype_ `virtual int32 OnPaint( const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;`
- L38 _private prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L40 _private prototype_ `FSlateIMLineGraphData& GetNextLineGraph(const FLinearColor& LineColor, float LineThickness, const FDoubleRange& XViewRange, const FDoubleRange& YViewRange);`
- L42 _private member_ `TArray<FSlateIMLineGraphData> LineGraphs;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SLATEIM_API`

### `Plugins/Experimental/SlateIM/Source/SlateIM/Private/Widgets/SImWrapper.h` (Private)


#### class `SImWrapper`  
`class SImWrapper : public SCompoundWidget`  
_L10-41_
- inherits: `SCompoundWidget`
- L13 _public function_ `SLATE_BEGIN_ARGS(SImWrapper)`
- L15 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_END_ARGS() virtual ~SImWrapper() override;`
- L20 _public prototype_ `void Construct(const FArguments& InArgs);`
- L22 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L24 _public prototype_ `virtual bool SupportsKeyboardFocus() const override;`
- L26 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& KeyEvent) override;`
- L27 _public prototype_ `virtual FReply OnKeyUp(const FGeometry& MyGeometry, const FKeyEvent& KeyEvent) override;`
- L28 _public prototype_ `virtual FReply OnAnalogValueChanged(const FGeometry& MyGeometry, const FAnalogInputEvent& AnalogInputEvent) override;`
- L29 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L30 _public prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L31 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L32 _public prototype_ `virtual FReply OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L33 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L35 _public prototype_ `void SetContent(const TSharedRef< SWidget >& InContent);`
- L36 _public prototype_ `void SetHAlign(EHorizontalAlignment HAlign);`
- L37 _public prototype_ `void SetVAlign(EVerticalAlignment VAlign);`
- L38 _public prototype_ `void SetPadding(TAttribute<FMargin> InPadding);`
- L40 _public member_ `FSlateIMInputState InputState;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SLATEIM_API`

### `Plugins/Experimental/SlateIM/Source/SlateIM/Public/Misc/SlateIMStringFilter.h` (Public)


#### class `FSlateImTextFilter`  
`template<typename ItemType> class FSlateImTextFilter`  
_L15-44_
- desc: Base template class for SlateIM text filters. Provides a common interface for filtering items using TTextFilter.
- L18 _public prototype_ `FSlateImTextFilter() = default;`
- L20 _public prototype_ `virtual ~FSlateImTextFilter() = default;`
- L27 _public typedef_ `using ArrayItemType = std::remove_const_t<typename TRemoveReference<ItemType>::Type>;` — Filters an array of items, returning a new array with only matching entries. @param InArray The source array to filter @return A new array containing only the items that pass the filter
- L28 _public function_ `TArray<ArrayItemType> Filter(const TArray<ArrayItemType>& InArray) const`
- L41 _public member_ `FString InputText;`
- L43 _public member_ `TSharedPtr<TTextFilter<ItemType>> TextFilter;`

#### class `FSlateIMStringFilter`  
`class FSlateIMStringFilter : public FSlateImTextFilter<const FString&>`  
_L58-72_
- inherits: `FSlateImTextFilter<constFString&>`
- desc: SlateIM filter utility class for filtering FStrings in immediate-mode menus. Usage: // As a member variable in your SlateIM menu class FSlateIMStringFilter MyFilter; // In your immediate-mode drawing code SlateIM::TextFilter(MyFilter, TEXT("Filter")); // Filter an array of items TArray<FString> FilteredItems = MyFilter.Filter(Items);
- L61 _public function_ `FSlateIMStringFilter()`

#### Free symbols / members of external scopes

- L36 _function_ `` (scope `FSlateImTextFilter::Filter`)
- L67 _function_ `` (scope `FSlateIMStringFilter::FSlateIMStringFilter`)

### `Plugins/Experimental/SlateIM/Source/SlateIM/Public/SlateIM.h` (Public)


#### class `FSlateIMModule`  
`class FSlateIMModule : public IModuleInterface`  
_L53-58_
- inherits: `IModuleInterface`
- L56 _public prototype_ `virtual void StartupModule() override;`
- L57 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L63 _namespace_ `namespace SlateIM`
- L80 _prototype_ `bool BeginWindowRoot(FName UniqueName, const FStringView& WindowTitle, FVector2f WindowSize, bool bShouldReopen = false);` (scope `SlateIM`) — Begins a new floating window root Please use the method below with the struct parameter. @param UniqueName a unique name to identify this window @param WindowTitle The name of the window. This will also be displayed in the windows title bar @param WindowSize The size to open the window at (does not update the size of an existing window) @param bShouldReopen (optional) If this window was created with a previous call to BeginWindow and then closed, passing in true will reopen the window and false will leave it closed. If the window has never been seen this parameter does nothing and the window will open @return the current window state. True if open, false if closed or not updating @note Consider using FSlateIMWindowBase to handle creating and updating your Slate IM Window
- L92 _prototype_ `bool BeginWindowRoot(FName UniqueName, const FWindowParams& Params = {});` (scope `SlateIM`) — Begins a new floating window root @param UniqueName a unique name to identify this window @param Params (optional) Additional parameters to create the window. @return the current window state. True if open, false if closed or not updating @note Consider using FSlateIMWindowBase to handle creating and updating your Slate IM Window
- L108 _prototype_ `bool BeginViewportRoot(FName UniqueName, UGameViewportClient* ViewportClient, const FViewportRootLayout& Layout);` (scope `SlateIM`) — Begins a new root in the game viewport Please use the method below with the struct-parameter. @param UniqueName a globally unique name to identify this root @param ViewportClient the viewport client to add the widget to @param Layout How to lay out the root within the viewport @return Whether the root is valid and updating
- L119 _prototype_ `bool BeginViewportRoot(FName UniqueName, UGameViewportClient* ViewportClient, const FViewportParams& Params = FViewportParams());` (scope `SlateIM`) — Begins a new root in the game viewport @param UniqueName a globally unique name to identify this root @param ViewportClient the viewport client to add the widget to @param Params (optional) Additional parameters to create the root. @return Whether the root is valid and updating
- L132 _prototype_ `bool BeginViewportRoot(FName UniqueName, ULocalPlayer* LocalPlayer, const FViewportRootLayout& Layout);` (scope `SlateIM`) — Begins a new root in the provided player's viewport Please use the method below with the struct-parameter. @param UniqueName a globally unique name to identify this root @param LocalPlayer the player whose viewport to add the widget to @param Layout How to lay out the root within the viewport @return Whether the root is valid and updating
- L143 _prototype_ `bool BeginViewportRoot(FName UniqueName, ULocalPlayer* LocalPlayer, const FViewportParams& Params = FViewportParams());` (scope `SlateIM`) — Begins a new root in the provided player's viewport @param UniqueName a globally unique name to identify this root @param LocalPlayer the player whose viewport to add the widget to @param Params (optional) Additional parameters to create the root. @return Whether the root is valid and updating
- L160 _prototype_ `bool BeginViewportRoot(FName UniqueName, TSharedPtr<IAssetViewport> AssetViewport, const FViewportRootLayout& Layout);` (scope `SlateIM`) — Begins a SlateIM root in the provided in editor viewport Please use the method below with the struct-parameter. @param UniqueName Unique identifier for this root. Must be globally unique within the same editor session @param AssetViewport The editor viewpor to add the SlateIM content to @param Layout How to lay out the root within the viewport @return Whether the root is valid and updating @note Not available in BPFL: TSharedPtr<IAssetViewport> is not Blueprint-compatible
- L173 _prototype_ `bool BeginViewportRoot(FName UniqueName, TSharedPtr<IAssetViewport> AssetViewport, const FViewportParams& Params = FViewportParams());` (scope `SlateIM`) — Begins a SlateIM root in the provided in editor viewport @param UniqueName Unique identifier for this root. Must be globally unique within the same editor session @param AssetViewport The editor viewpor to add the SlateIM content to @param Params (optional) Additional parameters to create the root. @return Whether the root is valid and updating @note Not available in BPFL: TSharedPtr<IAssetViewport> is not Blueprint-compatible
- L187 _prototype_ `bool BeginExposedRoot(FName UniqueName, TSharedPtr<SWidget>& OutSlateIMWidget);` (scope `SlateIM`) — Begins a SlateIM root that exposes a slate widget for embedding in other Slate hierarchies @param UniqueName a globally unique name to identify this root @param OutSlateIMWidget where to output the resulting SlateIM widget to @return Whether the root is valid and updating @note Consider using FSlateIMExposedBase to handle creating and updating your Slate IM exposed widget @note Not available in BPFL: TSharedPtr<SWidget> is not Blueprint-compatible
- L192 _prototype_ `void EndRoot();` (scope `SlateIM`) — Ends any Root type, must always be called regardless of the result of the Begin function
- L201 _prototype_ `void BeginHorizontalStack(bool bMaximizeContent = false);` (scope `SlateIM`) — Begins a horizontally stacked container. All widgets created within the Horizontal Stack container will be placed in-order left-to-right @param bMaximizeContent (optional) Maximize() the contents of the stack
- L203 _prototype_ `void EndHorizontalStack();` (scope `SlateIM`)
- L210 _prototype_ `void BeginVerticalStack(bool bMaximizeContent = false);` (scope `SlateIM`) — Begins a vertically stacked container. All widgets created within the Vertical Stack container will be placed in-order top-to-bottom @param bMaximizeContent (optional) Maximize() the contents of the stack
- L211 _prototype_ `void EndVerticalStack();` (scope `SlateIM`)
- L221 _prototype_ `void BeginHorizontalWrap(bool bMaximizeContent = false);` (scope `SlateIM`) — Begins a horizontally wrapped container. All widgets created within the Horizontal Wrap container will be placed in-order left-to-right until the allotted width is filled, then the content will begin a new line and so-on. @param bMaximizeContent (optional) Maximize() the contents of the wrap @note Wrap box children are always AutoSize and do not support Fill
- L223 _prototype_ `void EndHorizontalWrap();` (scope `SlateIM`)
- L233 _prototype_ `void BeginVerticalWrap(bool bMaximizeContent = false);` (scope `SlateIM`) — Begins a vertically wrapped container. All widgets created within the Vertical Wrap container will be placed in-order top-to-bottom until the allotted height is filled, then the content will begin a new column and so-on. @param bMaximizeContent (optional) Maximize() the contents of the wrap @note Wrap container children are always AutoSize and do not support Fill
- L235 _prototype_ `void EndVerticalWrap();` (scope `SlateIM`)
- L246 _prototype_ `void BeginTable(const FTableViewStyle* InStyle, const FTableRowStyle* InRowStyle = nullptr);` (scope `SlateIM`) — Begin a Table container. The contents are automatically scrollable if the table is sized smaller than all its content. Please use the method below with the struct-parameter. @param InStyle A Table View Style to override the default style. Changes to the style after the first invocation are not reflected, provide a new style object to update the visuals at runtime @param InRowStyle (optional) A Table Row Style to override the default table row style. Changing the style only affects new table rows.
- L253 _prototype_ `void BeginTable(const FTableParams& Params = FTableParams());` (scope `SlateIM`) — Begin a Table container. The contents are automatically scrollable if the table is sized smaller than all its content. @param Params (optional) Additional parameters to create the table.
- L258 _prototype_ `void EndTable();` (scope `SlateIM`) — End the current Table container.
- L263 _prototype_ `void BeginTableHeader();` (scope `SlateIM`) — Starts the header. Call this before adding any content to the table.
- L268 _prototype_ `void EndTableHeader();` (scope `SlateIM`) — Ends the table header.
- L277 _prototype_ `void NextTableColumn(const FName& ColumnID);` (scope `SlateIM`) — Moves to the next column. Allows fine control of the column body. @param ColumnID The name to use as ID for the column @note Table columns support SetToolTip, HAlign, and VAlign. See FixedTableColumnWidth() and InitialTableColumnWidth() for size options.
- L287 _prototype_ `void AddTableColumn(const FName& ColumnID, const FStringView& ColumnLabel);` (scope `SlateIM`) — Adds a column and immediately ends it with the given label as its body. Please use the method below with the struct-parameter. @param ColumnID The name to use as ID for the column @param ColumnLabel Added a default label to the column
- L295 _prototype_ `void AddTableColumn(const FName& ColumnID, const FTableColumnParams& Params = FTableColumnParams());` (scope `SlateIM`) — Adds a column and immediately ends it with the given label as its body. @param ColumnID The name to use as ID for the column @param Params (optional) Additional parameters to create the column
- L302 _prototype_ `void FixedTableColumnWidth(float Width);` (scope `SlateIM`) — Set the column to a fixed width, not resizable by users. Call this before calling AddTableColumn(). @param Width The fixed width of the column
- L309 _prototype_ `void InitialTableColumnWidth(float Width);` (scope `SlateIM`) — Set the column to an initial width, which can then be resized by users. Call this before calling AddTableColumn(). @param Width The initial width of the column
- L314 _prototype_ `void BeginTableBody();` (scope `SlateIM`) — Starts a table body.
- L319 _prototype_ `void EndTableBody();` (scope `SlateIM`) — Ends a table body.
- L330 _prototype_ `bool NextTableCell(bool* bOutRowSelected = nullptr);` (scope `SlateIM`) — Begin the content for the next table cell. The column and row are tracked internally based on the number of columns. @param bOutRowSelected (optional) If supplied, will return true if the row this cell belongs to is selected. @return Whether the contents of this table cell are visible. When false, the content can be skipped to save cycles. @note There is no "End" function counterpart to this call. This function supports the various slot functions (Padding, HAlign, VAlign, Min/Max Width/Height, etc).
- L346 _prototype_ `bool BeginTableRowChildren(uint32 ParentRowId, bool bDefaultExpanded = false);` (scope `SlateIM`) — Begin adding content as a child to the current table row. NextTableCell() must still be called after this function. If the table is a tree, a unique row id must be provided when starting a new set of child rows so that the expansion state of the parent row is saved. Not providing a row id will cause the parent row to revert to the default expansion state if its grandparent row is closed. Please use the method below with the struct-parameter. @param ParentRowId Id of the parent row. 0 to disable state saving. Row ids must be unique to its parent. @param bDefaultExpanded (optional) Set the default expansion state of the parent (whether the children following are visible.) Only applies to rows with a parent id. @return Whether the parent row is expanded or not. When false, the child content can be skipped to save cycles.
- L358 _prototype_ `bool BeginTableRowChildren(const FTableRowChildrenParams& Params = FTableRowChildrenParams());` (scope `SlateIM`) — Begin adding content as a child to the current table row. NextTableCell() must still be called after this function. If the table is a tree, a unique row id must be provided when starting a new set of child rows so that the expansion state of the parent row is saved. Not providing a row id will cause the parent row to revert to the default expansion state if its grandparent row is closed. @param Params (optional) Additional parameters to create the table children. @return Whether the parent row is expanded or not. When false, the child content can be skipped to save cycles.
- L363 _prototype_ `void EndTableRowChildren();` (scope `SlateIM`) — Stop adding child content to the parent row. This must be called no matter the result of BeginTableRowChildren()
- L375 _prototype_ `void BeginBorder(const FSlateBrush* BorderBrush, EOrientation Orientation, bool bAbsorbMouse = true, FMargin ContentPadding = FMargin(2.0f));` (scope `SlateIM`) — Begin a container with a background image. Please use the method below with the struct-parameter. @param BorderBrush The brush to use as the background for this container @param Orientation Which direction the contents of the container should flow @param bAbsorbMouse (optional) Whether the container should handle all mouse inputs @param ContentPadding (optional) How much to pad the contents of the container
- L383 _prototype_ `void BeginBorder(const FSlateBrush* BorderBrush, const FBorderParams& Params = FBorderParams());` (scope `SlateIM`) — Begin a container with a background image. @param BorderBrush The brush to use as the background for this container @param Params (optional) Additional params to create the border
- L395 _prototype_ `void BeginBorder(const FName BorderStyleName, EOrientation Orientation, bool bAbsorbMouse = true, FMargin ContentPadding = FMargin(2.0f));` (scope `SlateIM`) — Begin a container with a background image. Please use the method below with the struct-parameter. @param BorderStyleName The name of the brush in FAppStyle to use as the background for this container @param Orientation Which direction the contents of the container should flow @param bAbsorbMouse (optional) Whether the container should handle all mouse inputs @param ContentPadding (optional) How much to pad the contents of the container
- L403 _prototype_ `void BeginBorder(const FName BorderStyleName, const FBorderParams& Params = FBorderParams());` (scope `SlateIM`) — Begin a container with a background image. @param BorderStyleName The name of the brush in FAppStyle to use as the background for this container @param Params (optional) Additional params to create the border
- L405 _prototype_ `void EndBorder();` (scope `SlateIM`)
- L416 _prototype_ `bool BeginScrollBox(EOrientation Orientation);` (scope `SlateIM`) — Begins a container that will allow the user to scroll when its content is larger than the allotted space. Please use the method below with the struct-parameter. @param Orientation Which direction content should flow and scroll @return Whether the user scroll the content this frame
- L425 _prototype_ `bool BeginScrollBox(const FScrollBoxParams& Params = FScrollBoxParams());` (scope `SlateIM`) — Begins a container that will allow the user to scroll when its content is larger than the allotted space. @param Params (optional) Additional parameters to create the scroll box @return Whether the user scroll the content this frame
- L427 _prototype_ `void EndScrollBox();` (scope `SlateIM`)
- L439 _prototype_ `void BeginPopUp(const FName BorderStyleName, EOrientation Orientation, bool bAbsorbMouse = true, FMargin ContentPadding = FMargin(2.0f));` (scope `SlateIM`) — Begin a container with a background image. Please use the method below with the struct-parameter. @param BorderStyleName The name of the brush in FAppStyle to use as the background for this container @param Orientation Which direction the contents of the container should flow @param bAbsorbMouse (optional) Whether the container should handle all mouse inputs @param ContentPadding (optional) How much to pad the contents of the container
- L447 _prototype_ `void BeginPopUp(const FName BorderStyleName = TEXT("ToolPanel.GroupBorder"), const FPopUpParams& Para` (scope `SlateIM`) — Begin a container with a background image. @param BorderStyleName The name of the brush in FAppStyle to use as the background for this container @param Params (optional) Additional parameters to create the border
- L459 _prototype_ `void BeginPopUp(const FSlateBrush* BorderBrush, EOrientation Orientation, bool bAbsorbMouse = true, FMargin ContentPadding = FMargin(2.0f));` (scope `SlateIM`) — Begin a container with a background image. Please use the method below with the struct-parameter. @param BorderBrush The brush to use as the background for this container @param Orientation Which direction the contents of the container should flow @param bAbsorbMouse (optional) Whether the container should handle all mouse inputs @param ContentPadding (optional) How much to pad the contents of the container
- L467 _prototype_ `void BeginPopUp(const FSlateBrush* BorderBrush, const FPopUpParams& Params = FPopUpParams());` (scope `SlateIM`) — Begin a container with a background image. @param BorderBrush The brush to use as the background for this container @param Params (optional) Additional params to create the border
- L469 _prototype_ `void EndPopUp();` (scope `SlateIM`)
- L478 _prototype_ `void Padding(const FMargin NextPadding);` (scope `SlateIM`) — Sets the padding for the next widget @param NextPadding The padding to apply to the next widget
- L485 _prototype_ `void HAlign(EHorizontalAlignment NextAlignment);` (scope `SlateIM`) — Sets the horizontal alignment for the next widget @param NextAlignment The alignment to apply to the next widget
- L491 _prototype_ `void VAlign(EVerticalAlignment NextAlignment);` (scope `SlateIM`) — Sets the vertical alignment for the next widget @param NextAlignment The alignment to apply to the next widget
- L496 _prototype_ `void AutoSize();` (scope `SlateIM`) — Set the next slot to AutoSize to its content
- L503 _prototype_ `void Fill();` (scope `SlateIM`) — Sets the next slot to Fill the remaining space in its container @note The filled space is shared equally with any other slots set to Fill the same container
- L510 _prototype_ `void MinWidth(float InMinWidth);` (scope `SlateIM`) — Set the minimum width the next slot can have. @param InMinWidth The minimum width for the next slot
- L518 _prototype_ `void MinHeight(float InMinHeight);` (scope `SlateIM`)
- L525 _prototype_ `void MaxWidth(float InMaxWidth);` (scope `SlateIM`)
- L531 _prototype_ `void MaxHeight(float InMaxHeight);` (scope `SlateIM`) — Set the maximum height the next slot can have. @param InMaxHeight The maximum height for the next slot
- L536 _prototype_ `void Maximize();` (scope `SlateIM`) — Set the alignments to Fill and removes autosize.
- L549 _prototype_ `void Text(const FStringView& InText, const FTextBlockStyle* TextStyle);` (scope `SlateIM`) — Display a string of text Please use the method below with the struct-parameter. @param InText The text string to display @param TextStyle A Text Block Style to override the default style. Changes to the style after the first invocation are not reflected, provide a new style object to update the visuals at runtime
- L561 _prototype_ `void Text(const FStringView& InText, FSlateColor Color, const FTextBlockStyle* TextStyle = nullptr);` (scope `SlateIM`) — Display a colored string of text Please use the method below with the struct-parameter. @param InText The text string to display @param Color The color to display the text as @param TextStyle (optional) A Text Block Style to override the default style. Changes to the style after the first invocation are not reflected, provide a new style object to update the visuals at runtime
- L569 _prototype_ `void Text(const FStringView& InText, const FTextParams& Params = FTextParams());` (scope `SlateIM`) — Display a string of text @param InText The text string to display @param Params (optional) Additional parameters to create the text.
- L581 _prototype_ `bool EditableText(FString& InOutText, const FStringView& HintText, const FEditableTextBoxStyle* TextStyle = nullptr);` (scope `SlateIM`) — Create a text input field @param InOutText The text that is in the input field. Can have a default value @param HintText The hint text to display when the input field is empty @param TextStyle (optional) An Editable Text Box Style to override the default style. Changes to the style after the first invocation are not reflected, provide a new style object to update the visuals at runtime @return Whether the user changed or committed text this frame
- L591 _prototype_ `bool EditableText(FString& InOutText, const FEditableTextParams& Params = FEditableTextParams());` (scope `SlateIM`) — Create a text input field @param InOutText The text that is in the input field. Can have a default value @param Params (optional) Additional parameters to create the widget @return Whether the user changed or committed text this frame
- L600 _prototype_ `void Image(const FSlateBrush* ImageBrush, const FSlateColor& ColorAndOpacity, FVector2D DesiredSize = FVector2D::ZeroVector);` (scope `SlateIM`) — Display a brush @param ImageBrush The brush to display @param ColorAndOpacity The color to tint the brush @param DesiredSize (optional) Override the desired size to display the brush at
- L608 _prototype_ `void Image(const FSlateBrush* ImageBrush, const FImageParams& Params = FImageParams());` (scope `SlateIM`) — Display a brush @param ImageBrush The brush to display @param Params (optional) Additional parameters to display the image
- L619 _prototype_ `void Image(const FName ImageStyleName, const FSlateColor& ColorAndOpacity, FVector2D DesiredSize = FVector2D::ZeroVector);` (scope `SlateIM`) — Display a slate style brush Please use the method below with the struct-parameter. @param ImageStyleName The named of the brush to display from FAppStyle @param ColorAndOpacity The color to tint the brush @param DesiredSize (optional) Override the desired size to display the brush at
- L627 _prototype_ `void Image(const FName ImageStyleName, const FImageParams& Params = FImageParams());` (scope `SlateIM`) — Display a slate style brush @param ImageStyleName The named of the brush to display from FAppStyle @param Params (optional) Additional parameters to display the image
- L637 _prototype_ `void Image(const FSlateColor& ColorAndOpacity, FVector2D DesiredSize = FVector2D::ZeroVector);` (scope `SlateIM`) — Display a colored box Please use the method below with the struct-parameter. @param ColorAndOpacity The color to display @param DesiredSize (optional) Override the desired size to display the box at
- L644 _prototype_ `void Image(const FImageParams& Params = FImageParams());` (scope `SlateIM`) — Display a colored box @param Params (optional) Additional parameters to display the block (including the color)
- L657 _prototype_ `void Image(UTexture2D* ImageTexture, const FSlateColor& ColorAndOpacity, FVector2D DesiredSize = FVector2D::ZeroVector);` (scope `SlateIM`)
- L665 _prototype_ `void Image(UTexture2D* ImageTexture, const FImageParams& Params = FImageParams());` (scope `SlateIM`) — Display a texture @param ImageTexture The texture to display @param Params (optional) Additional parameters to display the image
- L677 _prototype_ `void Image(UTextureRenderTarget2D* ImageRenderTarget, const FSlateColor& ColorAndOpacity, FVector2D DesiredSize = FVector2D::ZeroVector);` (scope `SlateIM`)
- L685 _prototype_ `void Image(UTextureRenderTarget2D* ImageRenderTarget, const FImageParams& Params = FImageParams());` (scope `SlateIM`) — Display a render target texture @param ImageRenderTarget The render target texture to display @param Params (optional) Additional parameters to display the image
- L697 _prototype_ `void Image(UMaterialInterface* ImageMaterial, FVector2D BrushSize, const FSlateColor& ColorAndOpacity, FVector2D DesiredSize = FVector2D::ZeroVector);` (scope `SlateIM`) — Display a material Please use the method below with the struct-parameter. @param ImageMaterial The material to display @param BrushSize The size to create the internal brush with @param ColorAndOpacity The color to tint the brush @param DesiredSize (optional) Override the desired size to display the brush at
- L706 _prototype_ `void Image(UMaterialInterface* ImageMaterial, FVector2D BrushSize, const FImageParams& Params = FImageParams());` (scope `SlateIM`) — Display a material @param ImageMaterial The material to display @param BrushSize The size to create the internal brush with @param Params (optional) Additional parameters to display the image
- L721 _prototype_ `bool Button(const FStringView& InText, const bool bEnabled, const FButtonStyle* InStyle = nullptr);` (scope `SlateIM`) — Display a button with text Please use the method below with the struct-parameter. @param InText The text to display on the button @param bEnabled Indicate if the button is enabled or not (grayed) @param InStyle (optional) A Button Style to override the default style. Changes to the style after the first invocation are not reflected, provide a new style object to update the visuals at runtime @return Whether the user clicked the button this frame
- L730 _prototype_ `bool Button(const FStringView& InText, const FButtonParams& Params = FButtonParams());` (scope `SlateIM`) — @param InText The text to display on the button @param Params (optional) Additional parameters to create the button @return Whether the user clicked the button this frame
- L744 _prototype_ `bool CheckBox(const FStringView& InLabel, bool& InOutCurrentState, const FCheckBoxStyle* CheckBoxStyle = nullptr);` (scope `SlateIM`) — Display a two-state checkbox Please use the method below with the struct-parameter. @param InLabel The label for the checkbox @param InOutCurrentState The current state of the checkbox. Can provide a default value. @param CheckBoxStyle (optional) A Checkbox Style to override the default style. Changes to the style after the first invocation are not reflected, provide a new style object to update the visuals at runtime @return Whether the user changed the state of the checkbox this frame
- L754 _prototype_ `bool CheckBox(bool& InOutCurrentState, const FCheckBoxParams& Params = FCheckBoxParams());` (scope `SlateIM`) — Display a two-state checkbox @param InOutCurrentState The current state of the checkbox. Can provide a default value. @param Params (optional) Additional parameters to create the checkbox @return Whether the user changed the state of the checkbox this frame
- L768 _prototype_ `bool CheckBox(const FStringView& InText, ECheckBoxState& InOutCurrentState, const FCheckBoxStyle* CheckBoxStyle = nullptr);` (scope `SlateIM`) — Display a three-state checkbox Please use the method below with the struct-parameter. @param InText The label for the checkbox @param InOutCurrentState The current state of the checkbox. Can provide a default value. @param CheckBoxStyle (optional) A Checkbox Style to override the default style. Changes to the style after the first invocation are not reflected, provide a new style object to update the visuals at runtime @return Whether the user changed the state of the checkbox this frame
- L778 _prototype_ `bool CheckBox(ECheckBoxState& InOutCurrentState, const FCheckBoxParams& Params = FCheckBoxParams());` (scope `SlateIM`) — Display a three-state checkbox @param InOutCurrentState The current state of the checkbox. Can provide a default value. @param Params (optional) Additional parameters to create the checkbox @return Whether the user changed the state of the checkbox this frame
- L793 _prototype_ `bool SpinBox(float& InOutValue, TOptional<float> Min, TOptional<float> Max, const FSpinBoxStyle* SpinBoxStyle = nullptr);` (scope `SlateIM`) — Display a float-based spin box Please use the method below with the struct-parameter. @param InOutValue The current value of the spin box. Can provide a default value. @param Min The minimum value of the spin box (or unset for no limit). @param Max The maximum value of the spin box (or unset for no limit). @param SpinBoxStyle (optional) A Spin Box Style to override the default style. Changes to the style after the first invocation are not reflected, provide a new style object to update the visuals at runtime @return Whether the user changed or committed the spin box value this frame
- L808 _prototype_ `bool SpinBox(double& InOutValue, TOptional<double> Min, TOptional<double> Max, const FSpinBoxStyle* SpinBoxStyle = nullptr);` (scope `SlateIM`) — Display a double-based spin box Please use the method below with the struct-parameter. @param InOutValue The current value of the spin box. Can provide a default value. @param Min The minimum value of the spin box (or unset for no limit). @param Max The maximum value of the spin box (or unset for no limit). @param SpinBoxStyle (optional) A Spin Box Style to override the default style. Changes to the style after the first invocation are not reflected, provide a new style object to update the visuals at runtime @return Whether the user changed or committed the spin box value this frame
- L823 _prototype_ `bool SpinBox(int32& InOutValue, TOptional<int32> Min, TOptional<int32> Max, const FSpinBoxStyle* SpinBoxStyle = nullptr);` (scope `SlateIM`) — Display an integer-based spin box Please use the method below with the struct-parameter. @param InOutValue The current value of the spin box. Can provide a default value. @param Min The minimum value of the spin box (or unset for no limit). @param Max The maximum value of the spin box (or unset for no limit). @param SpinBoxStyle (optional) A Spin Box Style to override the default style. Changes to the style after the first invocation are not reflected, provide a new style object to update the visuals at runtime @return Whether the user committed the spin box value this frame
- L834 _prototype_ `template<typename InNumericType> bool SpinBox(InNumericType& InOutValue, const FSpinBoxParams<InNumericType>& Params = FSpinBoxParams<InNumericType>());` (scope `SlateIM`) — Display a spin box @param InOutValue The current value of the spin box. Can provide a default value. @param Params (optional) Additional parameters to create the spinbox @return Whether the user committed the spin box value this frame
- L845 _prototype_ `template<> bool SpinBox(float& InOutValue, const FSpinBoxParams<float>& Params);` (scope `SlateIM`) — Display a float-based spin box @param InOutValue The current value of the spin box. Can provide a default value. @param Params Additional parameters to create the spinbox @return Whether the user changed or committed the spin box value this frame
- L856 _prototype_ `template<> bool SpinBox(double& InOutValue, const FSpinBoxParams<double>& Params);` (scope `SlateIM`) — Display a double-based spin box @param InOutValue The current value of the spin box. Can provide a default value. @param Params Additional parameters to create the spinbox @return Whether the user changed or committed the spin box value this frame
- L867 _prototype_ `template<> bool SpinBox(int32& InOutValue, const FSpinBoxParams<int32>& Params);` (scope `SlateIM`) — Display an int32-based spin box @param InOutValue The current value of the spin box. Can provide a default value. @param Params Additional parameters to create the spinbox @return Whether the user changed or committed the spin box value this frame
- L883 _prototype_ `bool Slider(float& InOutValue, float Min, float Max, float Step, const FSliderStyle* SliderStyle = nullptr);` (scope `SlateIM`) — Display a float-based slider Please use the method below with the struct-parameter. @param InOutValue The current value of the slider. Can provide a default value. @param Min The minimum value of the slider @param Max The maximum value of the slider @param Step The smallest incremental change that can be made to the slider's value @param SliderStyle (optional) A Slider Style to override the default style. Changes to the style after the first invocation are not reflected, provide a new style object to update the visuals at runtime @return Whether the user changed the value of the slider this frame
- L893 _prototype_ `bool Slider(float& InOutValue, const FSliderParams& Params = FSliderParams());` (scope `SlateIM`) — Display a float-based slider @param InOutValue The current value of the slider. Can provide a default value. @param Params (optional) Additional parameters to create the slider @return Whether the user changed the value of the slider this frame
- L902 _prototype_ `void ProgressBar(TOptional<float> Percent, const FProgressBarStyle* ProgressBarStyle);` (scope `SlateIM`) — Display a progress bar @param Percent The value of the progress bar (0.0 to 1.0) @param ProgressBarStyle A Progress Bar Style to override the default style. Changes to the style after the first invocation are not reflected, provide a new style object to update the visuals at runtime
- L910 _prototype_ `void ProgressBar(TOptional<float> Percent, const FProgressBarParams& Params = FProgressBarParams());` (scope `SlateIM`) — Display a progress bar @param Percent The value of the progress bar (0.0 to 1.0) @param Params (optional) Additional parameters to create the progress bar
- L925 _prototype_ `bool ComboBox(const TArray<FString>& ComboItems, int32& InOutSelectedItemIndex, bool bForceRefresh, const FComboBoxStyle* InComboStyle = nullptr);` (scope `SlateIM`) — Display a dropdown of text options Please use the method below with the struct-parameter. @param ComboItems The options the user can choose from @param InOutSelectedItemIndex The index of the currently selected option @param bForceRefresh (optional) Whether to force a refresh of the available options or the selected option (set to true for a frame when changing the list of options or manually setting the selected index) @param InComboStyle (optional) A Combo Box Style to override the default style. Changes to the style after the first invocation are not reflected, provide a new style object to update the visuals at runtime @return Whether the user changed the selected option this frame
- L939 _prototype_ `bool SearchableComboBox(const TArray<FString>& ComboItems, int32& InOutSelectedItemIndex, bool bForceRefresh = false, const FComboBoxStyle* InComboStyle = nullptr);` (scope `SlateIM`) — Display a searchable dropdown of text options Please use the method below with the struct-parameter. @param ComboItems The options the user can choose from @param InOutSelectedItemIndex The index of the currently selected option @param bForceRefresh (optional) Whether to force a refresh of the available options or the selected option (set to true for a frame when changing the list of options or manually setting the selected index) @param InComboStyle (optional) A Combo Box Style to override the default style. Only the initial style is applied @return Whether the user changed the selected option this frame
- L950 _prototype_ `bool ComboBox(const TArray<FString>& ComboItems, int32& InOutSelectedItemIndex, const FComboBoxParams& Params = FComboBoxParams());` (scope `SlateIM`) — Display a dropdown of text options @param ComboItems The options the user can choose from @param InOutSelectedItemIndex The index of the currently selected option @param Params (optional) Additional parameter to create the combo box @return Whether the user changed the selected option this frame
- L965 _prototype_ `bool SelectionList(const TArray<FString>& ListItems, int32& InOutSelectedItemIndex, bool bForceRefresh, const FTableViewStyle* InStyle = nullptr);` (scope `SlateIM`) — Display a list of text options Please use the method below with the struct-parameter. @param ListItems The list of options the user can choose from @param InOutSelectedItemIndex The index of the currently selected option @param bForceRefresh (optional) Whether to force a refresh of the available options or the selected option (set to true for a frame when changing the list of options or manually setting the selected index) @param InStyle (optional) A Table View Style to override the default style. Changes to the style after the first invocation are not reflected, provide a new style object to update the visuals at runtime @return Whether the user changed the selected option this frame
- L976 _prototype_ `bool SelectionList(const TArray<FString>& ListItems, int32& InOutSelectedItemIndex, const FSelectionListParams& Params = FSelectionListParams());` (scope `SlateIM`) — Display a list of text options @param ListItems The list of options the user can choose from @param InOutSelectedItemIndex The index of the currently selected option @param Params (optional) Additional parameters to create the selection list @return Whether the user changed the selected option this frame
- L983 _prototype_ `void Spacer(const FVector2D& Size);` (scope `SlateIM`) — Create a block of empty space @param Size The size of whitespace to create
- L991 _prototype_ `void Widget(TSharedRef<SWidget> InWidget);` (scope `SlateIM`) — Add an already created slate widget to the IM hierarchy @note Do not create the widget you are passing in here every frame. This is meant to be used to add already created widgets @note Not available in BPFL: TSharedRef<SWidget> is not Blueprint-compatible
- L1000 _prototype_ `bool BeginContextMenuAnchor();` (scope `SlateIM`) — Begin an area where a menu appears with a right click @return Whether the menu is open
- L1002 _prototype_ `void EndContextMenuAnchor();` (scope `SlateIM`)
- L1009 _prototype_ `void BeginMenuBar();` (scope `SlateIM`) — Begin a menu bar, similar to those shown at the top of windows. Can be placed anywhere. @see AddMenuSeparator AddMenuButton AddMenuToggleButton AddMenuCheckButton BeginSubMenu
- L1014 _prototype_ `void EndMenuBar();` (scope `SlateIM`) — End the menu bar.
- L1019 _prototype_ `void AddMenuBarEntry(const FStringView& InMenuName);` (scope `SlateIM`) — Adds a menu to the menu entry with the given name.
- L1024 _prototype_ `void EndMenuBarEntry();` (scope `SlateIM`) — Ends a menu bar entry
- L1031 _prototype_ `void AddMenuSection(const FStringView& SectionText);` (scope `SlateIM`) — Add a new section to the current context menu @param SectionText The label of the section to add
- L1036 _prototype_ `void AddMenuSeparator();` (scope `SlateIM`) — Add a separator to the current context menu
- L1048 _prototype_ `bool AddMenuButton(const FStringView& RowText, const FStringView& ToolTipText);` (scope `SlateIM`) — Add a menu item button to the current context menu Please use the method below with the struct-parameter. @param RowText Label for the menu item @param ToolTipText The tooltip to display for the menu item @return Whether the user clicked the menu item this frame
- L1058 _prototype_ `bool AddMenuButton(const FStringView& RowText, const FMenuButtonParams& Params = FMenuButtonParams());` (scope `SlateIM`) — Add a menu item button to the current context menu @param RowText Label for the menu item @param Params (optional) Additional parameters to create the menu button @return Whether the user clicked the menu item this frame
- L1071 _prototype_ `bool AddMenuToggleButton(const FStringView& RowText, bool& InOutCurrentState, const FStringView& ToolTipText);` (scope `SlateIM`) — Display a menu item button with a checkbox Please use the method below with the struct-parameter. @param RowText Label for the menu item @param InOutCurrentState The current state of the toggle @param ToolTipText The tooltip to display for the menu item @return Whether the user toggled the checkbox this frame
- L1082 _prototype_ `bool AddMenuToggleButton(const FStringView& RowText, bool& InOutCurrentState, const FMenuButtonParams& Params = FMenuButtonParams());` (scope `SlateIM`) — Display a menu item button with a checkbox @param RowText Label for the menu item @param InOutCurrentState The current state of the toggle @param Params (optional) Additional parameters to create the menu button @return Whether the user toggled the checkbox this frame
- L1095 _prototype_ `bool AddMenuCheckButton(const FStringView& RowText, bool& InOutCurrentState, const FStringView& ToolTipText);` (scope `SlateIM`) — Display a menu item button with a checkmark Please use the method below with the struct-parameter. @param RowText Label for the menu item @param InOutCurrentState The current state of the checkmark @param ToolTipText The tooltip to display for the menu item @return Whether the user clicked the menu item this frame
- L1106 _prototype_ `bool AddMenuCheckButton(const FStringView& RowText, bool& InOutCurrentState, const FMenuButtonParams& Params = FMenuButtonParams());` (scope `SlateIM`) — Display a menu item button with a checkmark @param RowText Label for the menu item @param InOutCurrentState The current state of the checkmark @param Params (optional) Additional parameters to create the menu button @return Whether the user clicked the menu item this frame
- L1113 _prototype_ `void BeginSubMenu(const FStringView& SubMenuText);` (scope `SlateIM`) — Add a submenu item to the current menu @param SubMenuText The label for the menu item
- L1115 _prototype_ `void EndSubMenu();` (scope `SlateIM`)
- L1124 _prototype_ `void BeginTabGroup(const FName& TabGroupId);` (scope `SlateIM`) — Begin a tab group, can contain TabStacks and TabSplitters @param TabGroupId Provide a unique identifier for this tab group
- L1129 _prototype_ `void EndTabGroup();` (scope `SlateIM`) — Ends the current Tab Group
- L1134 _prototype_ `void BeginTabStack();` (scope `SlateIM`) — Begin a tab stack, can only contain Tabs
- L1139 _prototype_ `void EndTabStack();` (scope `SlateIM`) — Ends the current Tab Stack
- L1146 _prototype_ `void BeginTabSplitter(EOrientation Orientation);` (scope `SlateIM`) — Begin a tab splitter, displays child TabSplitters and TabStacks side-by-side @param Orientation The direction to layout child TabSplitters and TabStacks
- L1151 _prototype_ `void EndTabSplitter();` (scope `SlateIM`) — Ends the current Tab Splitter
- L1158 _prototype_ `void TabSplitterSizeCoefficient(float SizeCoefficient);` (scope `SlateIM`) — Assigns the Size Coefficient for the next child of a TabSplitter @param SizeCoefficient The weight to assign to the next child of the parent TabSplitter
- L1171 _prototype_ `bool BeginTab(const FName& TabId, const FSlateIcon& TabIcon, const FText& TabTitle = FText::GetEmpty());` (scope `SlateIM`) — Begins a Tab to contain any other content Please use the method below with the struct-parameter. @param TabId Provide a tab id that is unique within the Tab Group @param TabIcon An icon to display on the tab next to the title. This cannot be updated after the initial creation of the tab. @param TabTitle (optional) The title to display for the tab if it should differ from the TabId. This cannot be updated after the initial creation of the tab. @return Returns true if the tab is active, false otherwise. Logic to draw the contents of the tab can be skipped when this is false.
- L1181 _prototype_ `bool BeginTab(const FName& TabId, const FTabParams& Params = FTabParams());` (scope `SlateIM`) — Begins a Tab to contain any other content @param TabId Provide a tab id that is unique within the Tab Group @param Params (optional) Additional parameters used to create the tab @return Returns true if the tab is active, false otherwise. Logic to draw the contents of the tab can be skipped when this is false.
- L1186 _prototype_ `void EndTab();` (scope `SlateIM`) — Ends the current Tab. This must be called even when BeginTab returns false.
- L1197 _prototype_ `void ActivateTab(const FName& TabId);` (scope `SlateIM`) — Causes a one-time activation of a tab in its parent tab well. Can be used at any point during layout. To use this effectively, all tab ids should be unique. Only the first tab registered with the given id will be activated. Can be called multiple times to activate multiple tabs in the same update. @see ActivateInParent(ETabActivationCause). @param TabId The tab id to activate.
- L1206 _prototype_ `bool CanUpdateSlateIM();` (scope `SlateIM`) — SlateIM updates are disabled in specific scenarios (like when a SlateIM::ModalDialog is open), use this function to react accordingly @return Whether SlateIM can update currently
- L1213 _prototype_ `void BeginDisabledState();` (scope `SlateIM`) — Disables all widgets until EndDisabledState is called. @note It is not possible to enable a widget inside a disabled parent widget by calling EndDisabledState before a child is created inside a disabled Widget.
- L1215 _prototype_ `void EndDisabledState();` (scope `SlateIM`)
- L1222 _prototype_ `void SetToolTip(const FStringView& NextToolTip);` (scope `SlateIM`) — Sets the tooltip to be used for the next widget created. Resets after tooltip is used @param NextToolTip The tooltip to display
- L1239 _prototype_ `EAppReturnType::Type ModalDialog(EAppMsgType::Type MessageType, const FStringView& DialogText, EAppMsgCategory Category, const FStringView& DialogTitle = FStringView());` (scope `SlateIM`) — Opens a modal dialog of the specified type. This function will not return until the user closes the modal dialog Please use the method below with the struct-parameter. @param MessageType The type of options the user can respond to the dialog with @param DialogText The message to display to the user @param Category The type of dialog to display @param DialogTitle (optional) The title to display in the dialog window @return The option the user selected @note SlateIM updates are disable while a SlateIM modal is open @see CanUpdateSlateIM()
- L1253 _prototype_ `EAppReturnType::Type ModalDialog(EAppMsgType::Type MessageType, const FStringView& DialogText, const FModalDialogParams& Params = FModalDialogParams());` (scope `SlateIM`) — Opens a modal dialog of the specified type. This function will not return until the user closes the modal dialog @param MessageType The type of options the user can respond to the dialog with @param DialogText The message to display to the user @param Params (optional) Additional parameters used to create the dialog @return The option the user selected @note SlateIM updates are disable while a SlateIM modal is open @see CanUpdateSlateIM()
- L1266 _function_ `template<typename ItemType> bool TextFilter(FSlateImTextFilter<ItemType>& InFilter, const FEditableTextParams& Params = FEditableTextParams())` (scope `SlateIM`) — Text filter input box that updates the filter when text changes. @param InFilter The text filter to display and update @param Params (optional) Additional parameters to create the text filter @return Whether the user changed or committed text this frame @note Not available in BPFL: template function
- L1289 _function_ `template<typename ItemType> bool TextFilter(FSlateImTextFilter<ItemType>& InFilter, const FStringView& HintText)` (scope `SlateIM`) — Text filter input box that updates the filter when text changes. Please use the method above with the struct-parameter. @param InFilter The text filter to display and update @param HintText hint text to display when the input is empty @return Whether the user changed or committed text this frame @note Not available in BPFL: template function
- L1301 _prototype_ `bool IsHovered();` (scope `SlateIM`) — Query whether the last widget is hovered or not @return true if the cursor is hovering the last rendered widget, false otherwise
- L1309 _prototype_ `bool IsFocused(EFocusDepth Depth = EFocusDepth::IncludingDescendants);` (scope `SlateIM`) — Query whether the previous widget is focused @param Depth (optional) How far to check for focus. Includes child widgets by default. @return true if the previous widget has focus (for the specified depth), false otherwise
- L1316 _prototype_ `void BeginGraph();` (scope `SlateIM`) — Begin a graph widget, call graphing functions between this and EndGraph to include multiple graphs in a single chart
- L1321 _prototype_ `void EndGraph();` (scope `SlateIM`) — Call when finished calling graphing functions for the widget
- L1334 _prototype_ `void GraphLine(const TArrayView<FVector2D>& Points, const FLinearColor& LineColor, float LineThickness, const FDoubleRange& XViewRange, const FDoubleRange& YViewRange);` (scope `SlateIM`) — Add a line graph of 2D vectors to the graph widget Please use the method below with the struct-parameter. @param Points The X,Y points to plot on the graph @param LineColor The color of the line to draw for this graph @param LineThickness How thick to draw the line @param XViewRange The min and max X values to horizontally scale the graph to @param YViewRange The min and max Y values to vertically scale the graph to
- L1342 _prototype_ `void GraphLine(const TArrayView<FVector2D>& Points, const FGraphLinePointsParams& Params = FGraphLinePointsParams());` (scope `SlateIM`) — Add a line graph of 2D vectors to the graph widget @param Points The X,Y points to plot on the graph @param Params Additional parameters to draw the line
- L1355 _prototype_ `void GraphLine(const TArrayView<double>& Values, const FLinearColor& LineColor, float LineThickness, const FDoubleRange& ViewRange);` (scope `SlateIM`) — Add a line graph of values to the graph widget. The value index is used as the X-value when plotting, the graph will scale horizontally to fit all values in the array. Please use the method below with the struct-parameter. @param Values The Y values to plot on the graph @param LineColor The color of the line to draw for this graph @param LineThickness How thick to draw the line @param ViewRange The min and max Y values to vertically scale the graph to
- L1364 _prototype_ `void GraphLine(const TArrayView<double>& Values, const FGraphLineValuesParams& Params = FGraphLineValuesParams());` (scope `SlateIM`) — Add a line graph of values to the graph widget. The value index is used as the X-value when plotting, the graph will scale horizontally to fit all values in the array. @param Values The Y values to plot on the graph @param Params Additional parameters to draw the line
- L1376 _prototype_ `bool IsKeyPressed(const FKey& InKey);` (scope `SlateIM`) — Query whether a key was pressed this frame. Only considers input events that make it to the SlateIM root. Input events handled by child widgets will not be considered. @param InKey The key to query the state of @return true if the key was just pressed this frame
- L1386 _prototype_ `bool IsKeyHeld(const FKey& InKey);` (scope `SlateIM`) — Query whether a key is being held this frame. Only considers input events that make it to the SlateIM root. Input events handled by child widgets will not be considered. @param InKey The key to query the state of @return true if the key was pressed or held this frame
- L1396 _prototype_ `bool IsKeyReleased(const FKey& InKey);` (scope `SlateIM`) — Query whether a key was released this frame. Only considers input events that make it to the SlateIM root. Input events handled by child widgets will not be considered. @param InKey The key to query the state of @return true if the key was just released this frame
- L1406 _prototype_ `float GetKeyAnalogValue(const FKey& InKey);` (scope `SlateIM`) — Retrieve the analog value for a key Only considers input events that make it to the SlateIM root. Input events handled by child widgets will not be considered. @param InKey The key to query the state of @return the last analog value the SlateIM root received for the specified key
- L1411 _namespace_ `namespace Canvas` (scope `SlateIM`)
- L1420 _prototype_ `void BeginCanvas(int32 Width, int32 Height, const FCanvasParams& CanvasParams = FCanvasParams());` (scope `SlateIM::Canvas`) — Begin queueing commands to draw to a canvas render target. @param Width The width of the canvas in pixels. @param Height The height of the canvas in pixels. @param Params Additional parameters to create the canvas.
- L1425 _prototype_ `void EndCanvas();` (scope `SlateIM::Canvas`) — Ends the currently drawn canvas and executes all queued commands.
- L1430 _prototype_ `void Invalidate();` (scope `SlateIM::Canvas`) — Invalidate the current canvas, forcing a redraw if its UpdateType is set to Invalidation.
- L1433 _prototype_ `void SetClip(const FVector2f& ClipPosition);` (scope `SlateIM::Canvas`) — Sets the position of the lower-right corner of the clipping region of the canvas
- L1436 _prototype_ `void SetDrawColor(const FLinearColor& Color);` (scope `SlateIM::Canvas`) — Sets the draw color of the canvas.
- L1437 _prototype_ `void SetDrawColor(const FColor& Color);` (scope `SlateIM::Canvas`)
- L1447 _prototype_ `void DrawItem(TSharedRef<FCanvasItem> ItemPtr, const FVector2f& CanvasPosition = FVector2f::ZeroVector);` (scope `SlateIM::Canvas`) — Queue drawing a canvas item to the canvas. @param Item The canvas item to draw. The item *must* stay in scope until EndCanvas(). @param CanvasPosition (optional) The position to draw the item on the canvas. @note Not available in BPFL: TSharedRef<FCanvasItem> is not Blueprint-compatible
- L1456 _prototype_ `void DrawIcon(const FCanvasIcon& Icon, const FVector2f& CanvasPosition = FVector2f::ZeroVector, const FVector2f& Scale = FVector2f::UnitVector);` (scope `SlateIM::Canvas`) — Queue drawing a canvas icon (texture) to the canvas. @param Icon The icon to draw. The texture draw area is in pixels. @param CanvasPosition (optional) The position of the icon on the canvas, in pixels. @param Scale (optional) The scale of the icon.
- L1466 _prototype_ `void DrawLine(const FVector2D& CanvasPositionA, const FVector2D& CanvasPositionB, float Thickness = 1.0f, const FLinearColor& RenderColor = FLinearColor::White);` (scope `SlateIM::Canvas`) — Queue drawing a line to the canvas. @param CanvasPositionA One end of the line on the canvas, in pixels. @param CanvasPositionB The other end of the line on the canvas, in pixels. @param Thickness (optional) The thickness of the line in pixels. @param RenderColor (optional) The color of the line.
- L1476 _prototype_ `void DrawTexture(UTexture* RenderTexture, const FVector2D& CanvasPosition, const FVector2D& CanvasSize, const FTileRenderParams& RenderParams = FTileRenderParams());` (scope `SlateIM::Canvas`) — Queue drawing a texture to the canvas. @param RenderTexture The texture to draw. @param CanvasPosition The position of the texture on the canvas, in pixels. @param CanvasSize The size of the texture on the canvas, in pixels. @param RenderParams (optional) Additional parameters to draw the tile.
- L1486 _prototype_ `void DrawMaterial(UMaterialInterface* RenderMaterial, const FVector2D& CanvasPosition, const FVector2D& CanvasSize, const FTileRenderParams& RenderParams = FTileRenderParams());` (scope `SlateIM::Canvas`) — Queue drawing a material to the canvas. @param RenderMaterial The material to draw. @param CanvasPosition The position of the material on the canvas, in pixels. @param CanvasSize The size of the material on the canvas, in pixels. @param RenderParams (optional) Additional parameters to draw the tile. RenderColor and BlendMode are not used.
- L1496 _prototype_ `void DrawText(UFont* RenderFont, const FString& RenderText, const FVector2D& CanvasPosition, const FTextRenderParams& RenderParams);` (scope `SlateIM::Canvas`) — Queue drawing text to the canvas. @param RenderFont The font used to render the text. @param RenderText The string to render. @param CanvasPosition The position of the text on the canvas, in pixels. @param RenderParams (optional) Additional parameters to draw the text.
- L1509 _prototype_ `void DrawText(UFont* RenderFont, const FString& RenderText, const FVector2f& CanvasPosition, const FVector2f& Scale = FVector2f::UnitVector, const FFontRenderInfo& RenderInfo = FFontRenderInfo());` (scope `SlateIM::Canvas`) — Queue drawing text to the canvas. Alternate method allowing the use of FFontRenderInfo. @param RenderFont The font used to render the text. @param RenderText The string to render. @param CanvasPosition The position of the text on the canvas, in pixels. @param Scale (optional) The scale of the text on the canvas. @param RenderInfo (optional) Extra optional parameters for rendering the text.
- L1527 _prototype_ `void DrawWrappedText(const UFont* RenderFont, const FString& RenderText, const FVector2f& CanvasPosition, bool bCenterTextX, bool bCenterTextY, const FVector2f& Scale = FVector2f::UnitVector, const FFontRenderInfo& RenderInfo = FFontRenderInfo());` (scope `SlateIM::Canvas`) — Queue drawing wrapped text to canvas. Uses FFontRenderInfo for text effets. Text size / wrapping is automatically computed based on the position of the text and the @see SetCanvasClip. The default clipping position is the entire canvas. It does not reset between queued calls. @param RenderFont The font used to render the text. @param RenderText The text to render. @param CanvasPosition The position of the text on the canvas, in pixels. @param bCenterTextX If true, the text is centered on the given draw position on the X axis. @param bCenterTextY If true, the text is centered on the given draw position on the Y axis. @param Scale (optional) The scale of the text on the canvas. @param RenderInfo (optional) Extra optional parameters for rendering the text.
- L1542 _prototype_ `void DrawBorder(UTexture* BorderTexture, UTexture* BackgroundTexture, UTexture* LeftBorderTexture, UTexture* RightBorderTexture, UTexture* TopBorderTexture, UTexture* BottomBorderTexture, const FVector2D& CanvasPosition, const FVector2D& CanvasSize, const FBorderRenderParams& RenderParams = FBorderRenderParams());` (scope `SlateIM::Canvas`) — Queue drawing a border to the canvas. @param BorderTexture The texture for the center of the border. @param BackgroundTexture The texture for the background of the border. @param LeftBorderTexture The texture for the left of the border. @param RightBorderTexture The texture for the right of the border. @param TopBorderTexture The texture for the top of the border. @param BottomBorderTexture The texture for the bottom of the border. @param CanvasPosition The position of the border on the canvas, in pixels. @param CanvasSize The size of the border on the canvas, in pixels. @param RenderParams (optional) Additional parameters to draw the border.
- L1552 _prototype_ `void DrawBox(const FVector2D& CanvasPosition, const FVector2D& CanvasSize, float Thickness = 1.0f, FLinearColor RenderColor = FLinearColor::White);` (scope `SlateIM::Canvas`) — Queue drawing an unfilled box to the canvas. @param CanvasPosition The position of the box on the canvas, in pixels. @param CanvasSize The size of the box on the canvas, in pixels. @param Thickness (optional) The thicknses of the lines to draw. @param RenderColor (optional) The color of the lines to draw.
- L1562 _prototype_ `void DrawTriangles(UTexture* RenderTexture, TSharedRef<TArray<FCanvasUVTri>> Triangles);` (scope `SlateIM::Canvas`) — Queue drawing a series of texture-filled triangles to the canvas. @param RenderTexture The texture to draw with. @param Triangles The list of triangles to draw. @note Not available in BPFL: TSharedRef<TArray<FCanvasUVTri>> is not Blueprint-compatible
- L1572 _prototype_ `void DrawMaterialTriangles(UMaterialInterface* RenderMaterial, TSharedRef<TArray<FCanvasUVTri>> Triangles);` (scope `SlateIM::Canvas`) — Queue drawing a series of material-filled triangles to the canvas. @param RenderTexture The texture to draw with. @param Triangles The list of triangles to draw. @note Not available in BPFL: TSharedRef<TArray<FCanvasUVTri>> is not Blueprint-compatible
- L1583 _prototype_ `void DrawPolygon(UTexture* RenderTexture, const FVector2D& CanvasPosition, const FVector2D& Radius, int32 NumberOfSides, FLinearColor RenderColor = FLinearColor::White);` (scope `SlateIM::Canvas`) — Queue drawing a filled polygon to the canvas. @param RenderTexture The texture to draw with. @param CanvasPosition The position of the center of the polygon on the canvas, in pixels. @param Radius The radius of the polygon, in pixels. @param NumberOfSides The number of sides of the polygon. @param RenderColor (optional) The color of the polygon.

### `Plugins/Experimental/SlateIM/Source/SlateIM/Public/SlateIMParameters.h` (Public)


#### struct `SlateIM::FWindowParams`  
`struct FWindowParams`  
_L28-41_
- desc: Sync with FSlateIMWindowParams
- L31 _public member_ `FStringView WindowTitle;` — The name of the window. This will also be displayed in the windows title bar
- L34 _public member_ `FVector2f WindowSize = FVector2f::ZeroVector;` — The size to open the window at (does not update the size of an existing window)
- L37 _public member_ `bool bShouldReopen = false;` — If this window was created with a previous call to BeginWindow and then closed, passing in true will reopen the window and false will leave it closed. If the window has never been seen this parameter does nothing and the window will open
- L40 _public member_ `bool bAlwaysOnTop = false;` — Window will be create always on top.

#### struct `SlateIM::FTableParams`  
`struct FTableParams`  
_L44-55_
- desc: Sync with FSlateIMTableParams
- L48 _public member_ `const FTableViewStyle* Style = nullptr;` — A Table View Style to override the default style. Changes to the style after the first invocation are not reflected, provide a new style object to update the visuals at runtime
- L51 _public member_ `const FTableRowStyle* RowStyle = nullptr;` — A Table Row Style to override the default table row style. Changing the style only affects new table rows.
- L54 _public member_ `ESelectionMode::Type SelectionMode = ESelectionMode::None;` — Select mode for the table.

#### struct `SlateIM::FTableColumnParams`  
`struct FTableColumnParams`  
_L58-62_
- desc: Sync with FSlateIMTableColumnParams
- L61 _public member_ `FStringView Label = FStringView();` — Added a default label to the column

#### struct `SlateIM::FTableRowChildrenParams`  
`struct FTableRowChildrenParams`  
_L65-72_
- desc: Sync with FSlateIMTableRowChildrenParams
- L68 _public member_ `uint32 ParentRowId = 0;` — Id of the parent row. 0 to disable state saving. Row ids must be unique to its parent.
- L71 _public member_ `bool bDefaultExpanded = false;` — Set the default expansion state of the parent (whether the children following are visible.) Only applies to rows with a parent id.

#### struct `SlateIM::FTextParams`  
`struct FTextParams`  
_L75-83_
- desc: Sync with FSlateIMTextParams
- L78 _public member_ `FSlateColor Color = FSlateColor::UseForeground();` — The color to display the text as
- L82 _public member_ `const FTextBlockStyle* Style = nullptr;` — A Text Block Style to override the default style. Changes to the style after the first invocation are not reflected, provide a new style object to update the visuals at runtime

#### struct `SlateIM::FEditableTextParams`  
`struct FEditableTextParams`  
_L86-94_
- desc: Sync with FSlateIMEditableTextParams
- L89 _public member_ `const FStringView HintText = FStringView();` — HintText The hint text to display when the input field is empty
- L93 _public member_ `const FEditableTextBoxStyle* Style = nullptr;` — An Editable Text Box Style to override the default style. Changes to the style after the first invocation are not reflected, provide a new style object to update the visuals at runtime

#### struct `SlateIM::FButtonParams`  
`struct FButtonParams`  
_L97-105_
- desc: Sync with FSlateIMButtonParams
- L100 _public member_ `bool bEnabled = true;` — Indicate if the button is enabled or not (grayed)
- L104 _public member_ `const FButtonStyle* Style = nullptr;` — A Button Style to override the default style. Changes to the style after the first invocation are not reflected, provide a new style object to update the visuals at runtime

#### struct `SlateIM::FCheckBoxParams`  
`struct FCheckBoxParams`  
_L108-116_
- desc: Sync with FSlateIMCheckBoxParams
- L111 _public member_ `const FStringView Label;` — The label for the checkbox
- L115 _public member_ `const FCheckBoxStyle* CheckBoxStyle = nullptr;` — A Checkbox Style to override the default style. Changes to the style after the first invocation are not reflected, provide a new style object to update the visuals at runtime

#### struct `SlateIM::FSpinBoxParams`  
`template<typename InNumericType> struct FSpinBoxParams`  
_L119-130_
- L122 _public member_ `TOptional<InNumericType> Min;` — The minimum value of the spin box (or unset for no limit).
- L125 _public member_ `TOptional<InNumericType> Max;` — The maximum value of the spin box (or unset for no limit).
- L129 _public member_ `const FSpinBoxStyle* Style = nullptr;` — A Spin Box Style to override the default style. Changes to the style after the first invocation are not reflected, provide a new style object to update the visuals at runtime

#### struct `SlateIM::FSliderParams`  
`struct FSliderParams`  
_L133-147_
- desc: Sync with FSlateIMSliderParams
- L136 _public member_ `float Min = 0.f;` — The minimum value of the slider
- L139 _public member_ `float Max = 100.f;` — The maximum value of the slider
- L142 _public member_ `float Step = 1.f;` — The smallest incremental change that can be made to the slider's value
- L146 _public member_ `const FSliderStyle* Style = nullptr;` — A Slider Style to override the default style. Changes to the style after the first invocation are not reflected, provide a new style object to update the visuals at runtime

#### struct `SlateIM::FProgressBarParams`  
`struct FProgressBarParams`  
_L150-155_
- desc: Sync with FSlateIMProgressBarParams
- L154 _public member_ `const FProgressBarStyle* Style = nullptr;` — A Progress Bar Style to override the default style. Changes to the style after the first invocation are not reflected, provide a new style object to update the visuals at runtime

#### struct `SlateIM::FComboBoxParams`  
`struct FComboBoxParams`  
_L158-170_
- desc: Sync with FSlateIMComboBoxParams
- L162 _public member_ `bool bForceRefresh = false;` — Whether to force a refresh of the available options or the selected option (set to true for a frame when changing the list of options or manually setting the selected index)
- L165 _public member_ `bool bSearchable = false;` — Adds a search bar to the combo box
- L169 _public member_ `const FComboBoxStyle* Style = nullptr;` — A Combo Box Style to override the default style. Changes to the style after the first invocation are not reflected, provide a new style object to update the visuals at runtime

#### struct `SlateIM::FSelectionListParams`  
`struct FSelectionListParams`  
_L173-182_
- desc: Sync with FSlateIMSelectionListParams
- L177 _public member_ `bool bForceRefresh = false;` — Whether to force a refresh of the available options or the selected option (set to true for a frame when changing the list of options or manually setting the selected index)
- L181 _public member_ `const FTableViewStyle* Style = nullptr;` — A Table View Style to override the default style. Changes to the style after the first invocation are not reflected, provide a new style object to update the visuals at runtime

#### struct `SlateIM::FMenuButtonParams`  
`struct FMenuButtonParams`  
_L185-189_
- desc: Sync with FSlateIMMenuButtonParams
- L188 _public member_ `FStringView ToolTipText = FStringView();` — The tooltip to display for the menu item

#### struct `SlateIM::FTabParams`  
`struct FTabParams`  
_L192-199_
- desc: Sync with FSlateIMTabParams
- L195 _public member_ `const FSlateIcon TabIcon = FSlateIcon();` — An icon to display on the tab next to the title. This cannot be updated after the initial creation of the tab.
- L198 _public member_ `const FText TabTitle;` — The title to display for the tab if it should differ from the TabId. This cannot be updated after the initial creation of the tab.

#### struct `SlateIM::FModalDialogParams`  
`struct FModalDialogParams`  
_L202-209_
- desc: Sync with FSlateIMModalDialogParams
- L205 _public member_ `EAppMsgCategory Category = EAppMsgCategory::Warning;` — The type of dialog to display
- L208 _public member_ `const FStringView Title = FStringView();` — The title to display in the dialog window

#### struct `FSlateIMViewportRootLayout`  
`struct FSlateIMViewportRootLayout`  
_L213-240_
- reflection: `USTRUCT(BlueprintType)`
- L219 _public member_ `FAnchors Anchors = FAnchors(0);` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — How to anchor the root within the viewport (normalized units)
- L223 _public member_ `FVector2f Offset = FVector2f::ZeroVector;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — Offset the root from the anchored position in the viewport (in slate units)
- L227 _public member_ `FVector2f Alignment = FVector2f::ZeroVector;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — How the root is aligned to its anchor (normalized units)
- L231 _public member_ `TOptional<FVector2f> Size;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — Optional set the size (in slate units) of the root in the viewport. When unset, the root will auto-size for its content.
- L235 _public member_ `int32 ZOrder = 10000;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — The ZOrder of the SlateIM widget in the viewport
- L239 _public member_ `float Scale = 1.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — Global scale to apply within the viewport

#### struct `FSlateIMWindowParams`  
`struct FSlateIMWindowParams`  
_L243-272_
- reflection: `USTRUCT(BlueprintType)`
- L249 _public member_ `FString WindowTitle;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — The name of the window. This will also be displayed in the windows title bar
- L253 _public member_ `FVector2f WindowSize = FVector2f::ZeroVector;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — The size to open the window at (does not update the size of an existing window)
- L257 _public member_ `bool bShouldReopen = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — If this window was created with a previous call to BeginWindow and then closed, passing in true will reopen the window and false will leave it closed. If the window has never been seen this parameter does nothing and the window will open
- L261 _public member_ `bool bAlwaysOnTop = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — Window will be create always on top.
- L263 _public function_ `operator SlateIM::FWindowParams() const`

#### struct `FSlateIMViewportParams`  
`struct FSlateIMViewportParams`  
_L275-282_
- reflection: `USTRUCT(BlueprintType)`
- L281 _public member_ `FSlateIMViewportRootLayout Layout;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — How to lay out the root within the viewport

#### struct `FSlateIMTableParams`  
`struct FSlateIMTableParams`  
_L285-301_
- reflection: `USTRUCT(BlueprintType)`
- L291 _public member_ `TEnumAsByte<ESelectionMode::Type> SelectionMode = ESelectionMode::None;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — Select mode for the table.
- L293 _public function_ `operator SlateIM::FTableParams() const`

#### struct `FSlateIMTableColumnParams`  
`struct FSlateIMTableColumnParams`  
_L304-316_
- reflection: `USTRUCT(BlueprintType)`
- L310 _public member_ `FString Label;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — Added a default label to the column.
- L312 _public function_ `operator SlateIM::FTableColumnParams() const`

#### struct `FSlateIMTableRowChildrenParams`  
`struct FSlateIMTableRowChildrenParams`  
_L319-338_
- reflection: `USTRUCT(BlueprintType)`
- L325 _public member_ `int32 ParentRowId = 0;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — Id of the parent row. 0 to disable state saving. Row ids must be unique to its parent.
- L329 _public member_ `bool bDefaultExpanded = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — Set the default expansion state of the parent (whether the children following are visible.) Only applies to rows with a parent id.
- L331 _public function_ `operator SlateIM::FTableRowChildrenParams() const`

#### struct `FSlateIMBorderParams`  
`struct FSlateIMBorderParams`  
_L341-356_
- reflection: `USTRUCT(BlueprintType)`
- L347 _public member_ `TEnumAsByte<EOrientation> Orientation = EOrientation::Orient_Vertical;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — Which direction the contents of the container should flow
- L351 _public member_ `bool bAbsorbMouse = true;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — Whether the container should handle all mouse inputs
- L355 _public member_ `FMargin ContentPadding = FMargin(2.0f);` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — How much to pad the contents of the container

#### struct `FSlateIMScrollBoxParams`  
`struct FSlateIMScrollBoxParams`  
_L359-366_
- reflection: `USTRUCT(BlueprintType)`
- L365 _public member_ `TEnumAsByte<EOrientation> Orientation = EOrientation::Orient_Vertical;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — Which direction content should flow and scroll

#### struct `FSlateIMPopUpParams`  
`struct FSlateIMPopUpParams`  
_L369-384_
- reflection: `USTRUCT(BlueprintType)`
- L375 _public member_ `TEnumAsByte<EOrientation> Orientation = EOrientation::Orient_Vertical;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — Which direction the contents of the container should flow
- L379 _public member_ `bool bAbsorbMouse = true;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — Whether the container should handle all mouse inputs
- L383 _public member_ `FMargin ContentPadding = FMargin(2.0f);` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — How much to pad the contents of the container

#### struct `FSlateIMTextParams`  
`struct FSlateIMTextParams`  
_L387-402_
- reflection: `USTRUCT(BlueprintType)`
- L393 _public member_ `FSlateColor Color = FSlateColor::UseForeground();` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — The color to display the text as
- L395 _public function_ `operator SlateIM::FTextParams() const`

#### struct `FSlateIMEditableTextParams`  
`struct FSlateIMEditableTextParams`  
_L405-420_
- reflection: `USTRUCT(BlueprintType)`
- L411 _public member_ `FString HintText;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — HintText The hint text to display when the input field is empty
- L413 _public function_ `operator SlateIM::FEditableTextParams() const`

#### struct `FSlateIMImageParams`  
`struct FSlateIMImageParams`  
_L423-434_
- reflection: `USTRUCT(BlueprintType)`
- L429 _public member_ `FSlateColor ColorAndOpacity = FLinearColor::White;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — The color to tint the brush
- L433 _public member_ `FVector2D DesiredSize = FVector2D::ZeroVector;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — Override the desired size to display the brush at

#### struct `FSlateIMButtonParams`  
`struct FSlateIMButtonParams`  
_L437-452_
- reflection: `USTRUCT(BlueprintType)`
- L443 _public member_ `bool bEnabled = true;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — Indicate if the button is enabled or not (grayed)
- L445 _public function_ `operator SlateIM::FButtonParams() const`

#### struct `FSlateIMCheckBoxParams`  
`struct FSlateIMCheckBoxParams`  
_L455-470_
- reflection: `USTRUCT(BlueprintType)`
- L461 _public member_ `FString Label;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — The label for the checkbox
- L463 _public function_ `operator SlateIM::FCheckBoxParams() const`

#### struct `FSlateIMSpinBoxFloatParams`  
`struct FSlateIMSpinBoxFloatParams`  
_L473-493_
- reflection: `USTRUCT(BlueprintType)`
- L479 _public member_ `TOptional<float> Min;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — The minimum value of the spin box(or unset for no limit).
- L483 _public member_ `TOptional<float> Max;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — The maximum value of the spin box(or unset for no limit).
- L485 _public function_ `operator SlateIM::FSpinBoxParams<float>() const`

#### struct `FSlateIMSpinBoxDoubleParams`  
`struct FSlateIMSpinBoxDoubleParams`  
_L496-516_
- reflection: `USTRUCT(BlueprintType)`
- L502 _public member_ `TOptional<double> Min;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — The minimum value of the spin box(or unset for no limit).
- L506 _public member_ `TOptional<double> Max;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — The maximum value of the spin box(or unset for no limit).
- L508 _public function_ `operator SlateIM::FSpinBoxParams<double>() const`

#### struct `FSlateIMSpinBoxInt32Params`  
`struct FSlateIMSpinBoxInt32Params`  
_L519-539_
- reflection: `USTRUCT(BlueprintType)`
- L525 _public member_ `TOptional<int32> Min;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — The minimum value of the spin box(or unset for no limit).
- L529 _public member_ `TOptional<int32> Max;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — The maximum value of the spin box(or unset for no limit).
- L531 _public function_ `operator SlateIM::FSpinBoxParams<int32>() const`

#### struct `FSlateIMSliderParams`  
`struct FSlateIMSliderParams`  
_L542-567_
- reflection: `USTRUCT(BlueprintType)`
- L548 _public member_ `float Min = 0.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — The minimum value of the slider
- L552 _public member_ `float Max = 100.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — The maximum value of the slider
- L556 _public member_ `float Step = 1.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — The smallest incremental change that can be made to the slider's value
- L558 _public function_ `operator SlateIM::FSliderParams() const`

#### struct `FSlateIMProgressBarParams`  
`struct FSlateIMProgressBarParams`  
_L570-578_
- reflection: `USTRUCT(BlueprintType)`
- L574 _public function_ `operator SlateIM::FProgressBarParams() const`

#### struct `FSlateIMComboBoxParams`  
`struct FSlateIMComboBoxParams`  
_L581-602_
- reflection: `USTRUCT(BlueprintType)`
- L588 _public member_ `bool bForceRefresh = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — Whether to force a refresh of the available options or the selected option (set to true for a frame when changing the list of options or manually setting the selected index)
- L592 _public member_ `bool bSearchable = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — Adds a search bar to the combo box
- L594 _public function_ `operator SlateIM::FComboBoxParams() const`

#### struct `FSlateIMSelectionListParams`  
`struct FSlateIMSelectionListParams`  
_L605-621_
- reflection: `USTRUCT(BlueprintType)`
- L612 _public member_ `bool bForceRefresh = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — Whether to force a refresh of the available options or the selected option (set to true for a frame when changing the list of options or manually setting the selected index)
- L614 _public function_ `operator SlateIM::FSelectionListParams() const`

#### struct `FSlateIMMenuButtonParams`  
`struct FSlateIMMenuButtonParams`  
_L624-636_
- reflection: `USTRUCT(BlueprintType)`
- L630 _public member_ `FString ToolTipText;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — The tooltip to display for the menu item
- L632 _public function_ `operator SlateIM::FMenuButtonParams() const`

#### struct `FSlateIMIcon`  
`struct FSlateIMIcon`  
_L639-658_
- reflection: `USTRUCT(BlueprintType)`
- L645 _public member_ `FName StyleSetName = NAME_None;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — The name of the style set the icon can be found in.
- L649 _public member_ `FName StyleName = NAME_None;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — The name of the style for the icon.
- L653 _public member_ `FName SmallStyleName = NAME_None;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — The name of the style for the small icon.
- L657 _public member_ `FName StatusOverlayStyleName = NAME_None;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — Name of the style for the status overlay icon

#### struct `FSlateIMTabParams`  
`struct FSlateIMTabParams`  
_L661-680_
- reflection: `USTRUCT(BlueprintType)`
- L667 _public member_ `FSlateIMIcon TabIcon;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — An icon to display on the tab next to the title. This cannot be updated after the initial creation of the tab.
- L671 _public member_ `FText TabTitle;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — The title to display for the tab if it should differ from the TabId. This cannot be updated after the initial creation of the tab.
- L673 _public function_ `operator SlateIM::FTabParams() const`

#### struct `FSlateIMModalDialogParams`  
`struct FSlateIMModalDialogParams`  
_L683-702_
- reflection: `USTRUCT(BlueprintType)`
- L689 _public member_ `EAppMsgCategory Category = EAppMsgCategory::Warning;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — The type of dialog to display
- L693 _public member_ `FString Title;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — The title to display in the dialog window
- L695 _public function_ `operator SlateIM::FModalDialogParams() const`

#### enum `ESlateIMFocusDepth`  
`enum class ESlateIMFocusDepth : uint8`  
_L705-712_
- reflection: `UENUM(BlueprintType)`
- L708 _public enumerator_ `SelfOnly` — Only check if the previous widget is focused
- L711 _public enumerator_ `IncludingDescendants` — Check if the previous widget or any of its childs widgets are focused (recursively)

#### struct `FSlateIMGraphLinePointsParams`  
`struct FSlateIMGraphLinePointsParams`  
_L715-734_
- reflection: `USTRUCT(BlueprintType)`
- L721 _public member_ `FDoubleRange XViewRange = FDoubleRange(0.0, 1.0);` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — The min and max X values to horizontally scale the graph to
- L725 _public member_ `FDoubleRange YViewRange = FDoubleRange(0.0, 1.0);` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — The min and max Y values to vertically scale the graph to
- L729 _public member_ `FLinearColor LineColor = FLinearColor::White;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — The color of the line to draw for this graph
- L733 _public member_ `float LineThickness = 1.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — How thick to draw the line

#### struct `FSlateIMGraphLineValuesParams`  
`struct FSlateIMGraphLineValuesParams`  
_L737-752_
- reflection: `USTRUCT(BlueprintType)`
- L743 _public member_ `FDoubleRange ViewRange = FDoubleRange(0.0, 1.0);` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — The min and max Y values to vertically scale the graph to
- L747 _public member_ `FLinearColor LineColor = FLinearColor::White;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — The color of the line to draw for this graph
- L751 _public member_ `float LineThickness = 1.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SlateIM")` — How thick to draw the line

#### Free symbols / members of external scopes

- L25 _namespace_ `namespace SlateIM`

### `Plugins/Experimental/SlateIM/Source/SlateIM/Public/SlateIMParametersFwd.h` (Public)


#### Free symbols / members of external scopes

- L55 _namespace_ `namespace SlateIM`
- L57 _typedef_ `using FViewportRootLayout = FSlateIMViewportRootLayout;` (scope `SlateIM`)
- L58 _typedef_ `using FViewportParams = FSlateIMViewportParams;` (scope `SlateIM`)
- L59 _typedef_ `using FBorderParams = FSlateIMBorderParams;` (scope `SlateIM`)
- L60 _typedef_ `using FScrollBoxParams = FSlateIMScrollBoxParams;` (scope `SlateIM`)
- L61 _typedef_ `using FPopUpParams = FSlateIMPopUpParams;` (scope `SlateIM`)
- L62 _typedef_ `using FImageParams = FSlateIMImageParams;` (scope `SlateIM`)
- L63 _typedef_ `using EFocusDepth = ESlateIMFocusDepth;` (scope `SlateIM`)
- L64 _typedef_ `using FGraphLinePointsParams = FSlateIMGraphLinePointsParams;` (scope `SlateIM`)
- L65 _typedef_ `using FGraphLineValuesParams = FSlateIMGraphLineValuesParams;` (scope `SlateIM`)
- L68 _namespace_ `namespace Canvas` (scope `SlateIM`)
- L70 _typedef_ `using ECanvasUpdateType = ESlateIMEngineCanvasUpdateType;` (scope `SlateIM::Canvas`)
- L71 _typedef_ `using FCanvasParams = FSlateIMEngineCanvasParams;` (scope `SlateIM::Canvas`)
- L72 _typedef_ `using FTileRenderParams = FSlateIMEngineTileRenderParams;` (scope `SlateIM::Canvas`)
- L73 _typedef_ `using FTextRenderParams = FSlateIMEngineTextRenderParams;` (scope `SlateIM::Canvas`)
- L74 _typedef_ `using FBorderRenderParams = FSlateIMEngineBorderRenderParams;` (scope `SlateIM::Canvas`)

### `Plugins/Experimental/SlateIM/Source/SlateIM/Public/SlateIMWidgetBase.h` (Public)


#### class `FSlateIMWidgetBase`  
`class FSlateIMWidgetBase`  
_L23-43_
- desc: A utility base class for creating SlateIM-based tools. Handles setting up a tick for drawing the tool. Note: this class is not required for using SlateIM but provides common functionality for SlateIM tools The test widgets (FSlateIMTestViewportWidget/FSlateIMTestWindowWidget in SlateIMManager) are examples of using this class.
- L26 _public prototype_ `explicit FSlateIMWidgetBase(const FStringView& Name);`
- L27 _public prototype_ `virtual ~FSlateIMWidgetBase();`
- L29 _public function_ `void ToggleWidget()`
- L30 _public prototype_ `virtual void EnableWidget();`
- L31 _public prototype_ `virtual void DisableWidget();`
- L33 _public function_ `bool IsWidgetEnabled() const`
- L35 _public function_ `const FName& GetWidgetName() const`
- L38 _protected prototype_ `virtual void DrawWidget(float DeltaTime) = 0;`
- L41 _private member_ `FDelegateHandle TickHandle;`
- L42 _private member_ `FName WidgetName;`

#### class `FSlateIMWidgetWithCommandBase`  
`class FSlateIMWidgetWithCommandBase : public FSlateIMWidgetBase`  
_L48-56_
- inherits: `FSlateIMWidgetBase`
- desc: Specialized version of FSlateIMWidgetBase that auto registers a command to toggle this widget
- L51 _public prototype_ `FSlateIMWidgetWithCommandBase(const TCHAR* Command, const TCHAR* CommandHelp);`
- L52 _public prototype_ `FSlateIMWidgetWithCommandBase(const FStringView& WidgetName, const TCHAR* Command, const TCHAR* CommandHelp);`
- L55 _private member_ `FAutoConsoleCommand WidgetCommand;`

#### class `FSlateIMWindowBase`  
`class FSlateIMWindowBase : public FSlateIMWidgetWithCommandBase`  
_L61-84_
- inherits: `FSlateIMWidgetWithCommandBase`
- desc: Specialized version of FSlateIMWidgetBase that draws in a window and disables itself when the user closes the window
- L64 _public function_ `FSlateIMWindowBase(FStringView WindowTitle, FVector2f WindowSize, const TCHAR* Command, const TCHAR* CommandHelp) : FSlateIMWindowBase(WindowTitle, WindowSize, false, Command, CommandHelp)`
- L68 _public function_ `FSlateIMWindowBase(FStringView WindowTitle, FVector2f WindowSize, bool bAlwaysOnTop, const TCHAR* Command, const TCHAR* CommandHelp) : FSlateIMWidgetWithCommandBase(Command, CommandHelp) , WindowTitle(WindowTitle) , WindowSize(WindowSize) , bAlwaysOnTop(bAlwaysOnTop)`
- L76 _protected prototype_ `virtual void DrawWindow(float DeltaTime) = 0;`
- L79 _private prototype_ `virtual void DrawWidget(float DeltaTime) final override;`
- L81 _private member_ `FString WindowTitle;`
- L82 _private member_ `FVector2f WindowSize;`
- L83 _private member_ `bool bAlwaysOnTop;`

#### class `FSlateIMNomadTabBase`  
`class FSlateIMNomadTabBase : public FSlateIMWidgetWithCommandBase`  
_L89-105_
- inherits: `FSlateIMWidgetWithCommandBase`
- desc: Specialized version of FSlateIMWidgetBase that draws in a nomad (dockable) tab and disables itself when the user closes the window
- L92 _public prototype_ `FSlateIMNomadTabBase(FStringView TabTitle, const TCHAR* Command, const TCHAR* CommandHelp, FSlateIcon TabIcon = FSlateIcon());`
- L93 _public prototype_ `virtual ~FSlateIMNomadTabBase();`
- L95 _public prototype_ `virtual void DisableWidget() override;`
- L98 _protected prototype_ `virtual void DrawContent(float DeltaTime) = 0;`
- L101 _private prototype_ `virtual void DrawWidget(float DeltaTime) final override;`
- L103 _private member_ `TWeakPtr<SDockTab> RootTab;`
- L104 _private member_ `TWeakPtr<SWidget> TabContent;`

#### class `FSlateIMExposedBase`  
`class FSlateIMExposedBase : public FSlateIMWidgetBase`  
_L112-134_
- inherits: `FSlateIMWidgetBase`
- desc: Specialized version of FSlateIMWidgetBase that exposes the resulting widget for embedding in other slate widgets @note EnableWidget() must be called to get a valid ExposedWidget
- L115 _public function_ `explicit FSlateIMExposedBase(const FStringView& Name) : FSlateIMWidgetBase(Name)`
- L121 _public prototype_ `TSharedRef<SWidget> GetExposedWidget() const;` — Get the widget to embed in your existing slate hierarchy
- L123 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnExposedWidgetChanged, TSharedRef<SWidget>);`
- L124 _public member_ `FOnExposedWidgetChanged OnExposedWidgetChanged;`
- L127 _protected prototype_ `virtual void DrawContent(float DeltaTime) = 0;`
- L130 _private prototype_ `virtual void DrawWidget(float DeltaTime) final override;`
- L132 _private member_ `TSharedPtr<SWidget> ExposedWidget;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SLATEIM_API`
- L123 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnExposedWidgetChanged, TSharedRef<SWidget>);`
