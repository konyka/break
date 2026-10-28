# Plugins / OperatorStackEditor

- module root: `Plugins/VirtualProduction/OperatorStack/Source/OperatorStack`
- headers: 22; symbols: 419
- symbol kinds: class=10, delegate=2, enum=2, enumerator=9, function=129, member=108, prototype=141, struct=12, typedef=6
- PrivateDependencyModuleNames: ApplicationCore, CoreUObject, CustomDetailsView, EditorSubsystem, Engine, InputCore, LevelEditor, Projects, PropertyEditor, Slate, SlateCore, ToolMenus, ToolWidgets, TypedElementRuntime, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/VirtualProduction/OperatorStack/Source/OperatorStack/Private/Styles/OperatorStackEditorStyle.h` (Private)


#### class `FOperatorStackEditorStyle`  
`class FOperatorStackEditorStyle : public FSlateStyleSet`  
_L7-19_
- inherits: `FSlateStyleSet`
- L10 _public prototype_ `FOperatorStackEditorStyle();`
- L14 _public function_ `static FOperatorStackEditorStyle& Get()`

### `Plugins/VirtualProduction/OperatorStack/Source/OperatorStack/Private/Widgets/DragDropOps/OperatorStackEditorDragDropOp.h` (Private)


#### class `FOperatorStackEditorDragDropOp`  
`class FOperatorStackEditorDragDropOp : public FDecoratedDragDropOp`  
_L13-50_
- inherits: `FDecoratedDragDropOp`
- desc: A custom drag operation for operator stack items
- L16 _public function_ `DRAG_DROP_OPERATOR_TYPE(FOperatorStackEditorDragDropOp, FDecoratedDragDropOp) static TSharedRef<FOperatorStackEditorDragDropOp> New(const TArray<TSharedPtr<FOperatorStackEditorItem>>& InItems)`
- L31 _public function_ `const TArray<TSharedPtr<FOperatorStackEditorItem>>& GetDraggedItems() const`
- L36 _public function_ `void SetDropZone(const TOptional<EItemDropZone>& InDropZone)`
- L41 _public function_ `TOptional<EItemDropZone> GetDropZone() const`
- L47 _protected member_ `TArray<TSharedPtr<FOperatorStackEditorItem>> DraggedItems;` — Dragged items
- L49 _protected member_ `TOptional<EItemDropZone> DropZone;`

### `Plugins/VirtualProduction/OperatorStack/Source/OperatorStack/Private/Widgets/SOperatorStackEditorPanel.h` (Private)


#### class `SOperatorStackEditorPanel`  
`class SOperatorStackEditorPanel : public SOperatorStackEditorWidget`  
_L20-138_
- inherits: `SOperatorStackEditorWidget`
- desc: This is the main panel that contains the stacks and switcher for them
- L23 _public function_ `SLATE_BEGIN_ARGS(SOperatorStackEditorPanel)`
- L24 _public prototype_ `SLATE_ARGUMENT(int32, PanelId) SLATE_END_ARGS() virtual ~SOperatorStackEditorPanel() override;`
- L29 _public prototype_ `void Construct(const FArguments& InArgs);`
- L32 _public prototype_ `virtual void SetContext(const FOperatorStackEditorContext& InContext) override;`
- L33 _public prototype_ `virtual void SetActiveCustomization(const FName& InCustomization) override;`
- L34 _public prototype_ `virtual void SetToolbarCustomizations(const TArray<FName>& InCustomizations) override;`
- L35 _public prototype_ `virtual void GetToolbarCustomizations(TArray<UOperatorStackEditorStackCustomization*>& OutCustomizations) override;`
- L36 _public prototype_ `virtual void ShowToolbarCustomization(FName InCustomization) override;`
- L37 _public prototype_ `virtual void HideToolbarCustomization(FName InCustomization) override;`
- L38 _public prototype_ `virtual void SetToolbarVisibility(bool bInVisible) override;`
- L39 _public prototype_ `virtual void SetKeyframeHandler(TSharedPtr<IDetailKeyframeHandler> InKeyframeHandler) override;`
- L40 _public prototype_ `virtual void SetDetailColumnSize(TSharedPtr<FDetailColumnSizeData> InDetailColumnSize) override;`
- L41 _public prototype_ `virtual void SetPanelTag(FName InTag) override;`
- L42 _public prototype_ `virtual void RefreshContext() override;`
- L43 _public function_ `virtual FOperatorStackEditorContextPtr GetContext() const override`
- L47 _public function_ `virtual int32 GetPanelId() const override`
- L51 _public function_ `virtual FName GetPanelTag() const override`
- L57 _public prototype_ `const FOperatorStackEditorTree& GetItemTree(UOperatorStackEditorStackCustomization* InCustomization);`
- L59 _public prototype_ `void SaveItemExpansionState(uint32 InItem, bool bInExpanded);`
- L61 _public prototype_ `bool GetItemExpansionState(uint32 InItem, bool& bOutExpanded);`
- L63 _public function_ `TSharedPtr<IDetailKeyframeHandler> GetKeyframeHandler() const`
- L68 _public function_ `TSharedPtr<FDetailColumnSizeData> GetDetailColumnSize() const`
- L73 _public function_ `const FText& GetLastSearch() const`
- L78 _public prototype_ `void FilterItemsAsync(const FText& InNewSearch, float InDelay = 0.f);`
- L82 _protected prototype_ `EVisibility GetToolbarButtonVisibility(int32 InIdx) const;` — Is the toolbar button active
- L85 _protected prototype_ `void AddSlot(const UOperatorStackEditorStackCustomization* InCustomizationStack);` — Adds a new widget slot for toolbar and switcher
- L88 _protected prototype_ `void UpdateSlots();` — Update the slots content with actual widget
- L91 _protected prototype_ `void OnToolbarButtonClicked(ECheckBoxState InState, int32 InWidgetIdx);` — Switch view when toolbar button is clicked
- L94 _protected prototype_ `ECheckBoxState IsToolbarButtonActive(int32 InWidgetIdx) const;` — Highlight active selection
- L98 _private member_ `TSharedPtr<SScrollBox> WidgetToolbar;` — Contains the named stack views
- L101 _private member_ `TSharedPtr<SWidgetSwitcher> WidgetSwitcher;` — Contains the different stack views
- L104 _private member_ `TMap<FName, int32> NamedStackIndexes;` — Stack index with their identifier for updates
- L107 _private member_ `TSet<int32> VisibleCustomizations;` — Customization visible to switch in toolbar
- L110 _private member_ `FOperatorStackEditorContextPtr Context;` — Current context, could be null
- L113 _private member_ `TSharedPtr<IDetailKeyframeHandler> KeyframeHandler;` — Keyframe handler to be able to keyframe properties in items
- L116 _private member_ `TSharedPtr<FDetailColumnSizeData> DetailColumnSize;` — Detail column size to have matching size across items
- L119 _private member_ `int32 PanelId = INDEX_NONE;` — The panel id to identify this widget
- L122 _private member_ `FName PanelTag = NAME_None;` — The panel tag to identify this widget
- L125 _private member_ `TMap<TWeakObjectPtr<UOperatorStackEditorStackCustomization>, FOperatorStackEditorTree> CustomizationTrees;` — Item trees containing items supported for each customization
- L128 _private member_ `TMap<uint32, bool> ItemExpansionState;` — To check whether an item was expanded and restore it
- L131 _private member_ `TArray<TSharedRef<SOperatorStackEditorStack>> CustomizationStacks;` — Contains the customization stacks
- L134 _private member_ `FText LastSearch = FText::GetEmpty();` — Last search done within the stack
- L137 _private member_ `FTSTicker::FDelegateHandle LastSearchHandle;` — Last search request triggered

### `Plugins/VirtualProduction/OperatorStack/Source/OperatorStack/Private/Widgets/SOperatorStackEditorStack.h` (Private)


#### class `SOperatorStackEditorStack`  
`class SOperatorStackEditorStack : public SCompoundWidget`  
_L24-164_
- inherits: `SCompoundWidget`
- desc: Represent a stack customization widget
- L29 _public member_ `static constexpr float Padding = 2.f;`
- L30 _public member_ `static const TMap<EOperatorStackEditorMessageType, FLinearColor> MessageBoxColors;`
- L31 _public member_ `static const TMap<EOperatorStackEditorMessageType, const FSlateBrush*> MessageBoxIcons;`
- L33 _public function_ `SLATE_BEGIN_ARGS(SOperatorStackEditorStack)`
- L34 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs , const TSharedPtr<SOperatorStackEditorPanel> InMainPanel , TObjectPtr<UOperatorStackEditorStackCustomization> InCustomization , const FOperatorStackEditorItemPtr& InCustomizeItem);`
- L41 _public function_ `UOperatorStackEditorStackCustomization* GetStackCustomization() const`
- L46 _public function_ `TSharedPtr<SOperatorStackEditorPanel> GetMainPanel() const`
- L51 _public prototype_ `FOperatorStackEditorContextPtr GetContext() const;`
- L54 _public prototype_ `void FilterItems(const FText& InText);` — Apply a filter on all items
- L57 _protected prototype_ `TSharedRef<ITableRow> OnGenerateRow(FOperatorStackEditorItemPtr InItem, const TSharedRef<STableViewBase>& InOwnerTable);`
- L60 _protected prototype_ `FReply OnKeyDownHandler(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent);` — Key down handler for list
- L63 _protected prototype_ `FReply OnHeaderMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);` — Mouse event for header
- L66 _protected prototype_ `void OnHeaderExpansionChanged(bool bInExpansion);` — Header expansion state changed
- L69 _protected prototype_ `void OnSelectionChanged(FOperatorStackEditorItemPtr InItem, ESelectInfo::Type InSelect) const;` — List selection changed
- L72 _protected prototype_ `bool IsSelectableRow(FOperatorStackEditorItemPtr InItem) const;` — Is this item selectable in the list view
- L75 _protected prototype_ `TSharedRef<SWidget> GenerateStackWidget();` — A stack widget consists of a header, body and footer
- L77 _protected prototype_ `TSharedPtr<SWidget> GenerateHeaderWidget();`
- L78 _protected prototype_ `TSharedPtr<SWidget> GenerateBodyWidget();`
- L79 _protected prototype_ `TSharedPtr<SWidget> GenerateFooterWidget();`
- L82 _protected prototype_ `TSharedRef<SWidget> GenerateMenuWidget(FName InMenuName) const;` — Generate this named menu widget for this context
- L84 _protected prototype_ `EVisibility GetHeaderVisibility() const;`
- L85 _protected prototype_ `EVisibility GetBodyVisibility() const;`
- L86 _protected prototype_ `EVisibility GetFooterVisibility() const;`
- L88 _protected prototype_ `EVisibility GetMessageBoxVisibility() const;`
- L89 _protected prototype_ `FLinearColor GetMessageBoxBackgroundColor() const;`
- L90 _protected prototype_ `const FSlateBrush* GetMessageBoxIcon() const;`
- L91 _protected prototype_ `EVisibility GetMessageBoxIconVisibility() const;`
- L94 _protected member_ `TWeakObjectPtr<UOperatorStackEditorStackCustomization> StackCustomizationWeak;` — The customization to use
- L97 _protected member_ `TWeakPtr<SOperatorStackEditorPanel> MainPanelWeak;` — The main panel we are in
- L100 _protected member_ `FOperatorStackEditorItemPtr CustomizeItem;` — Customization item for this stack
- L103 _protected member_ `TArray<FOperatorStackEditorItemPtr> Items;` — Children items of this item
- L106 _protected member_ `TSharedPtr<SListView<FOperatorStackEditorItemPtr>> ItemsListView;` — The list view if we contain any children
- L109 _protected member_ `TSharedPtr<ICustomDetailsView> HeaderDetailsView;` — Header custom view for properties in header
- L112 _protected member_ `TSharedPtr<ICustomDetailsView> BodyDetailsView;` — Body custom view for properties in body
- L115 _protected member_ `TSharedPtr<ICustomDetailsView> FooterDetailsView;` — Footer custom view for properties in footer
- L118 _protected member_ `TArray<TSharedPtr<SOperatorStackEditorStack>> ItemsWidgets;` — Children items widget created from this, used for search propagation
- L121 _protected member_ `TSharedPtr<SSearchBox> SearchBox;` — The search bar if any, only for root operator stack
- L124 _protected member_ `TSet<FString> SearchedKeywords;` — Contains pinned searched keywords, only for root operator stack
- L127 _protected member_ `TSet<FString> SearchableKeywords;` — Contains searchable keywords for this item
- L130 _protected member_ `bool bHeaderExpanded = true;` — Is header expanded to show body and footer
- L133 _protected member_ `FLinearColor BorderColor = FLinearColor::Transparent;` — Color of the border around this stack
- L136 _protected member_ `TSharedPtr<FUICommandList> CommandList;` — List of command available for this item
- L139 _protected member_ `FName ContextMenuName;` — Name of the context menu
- L142 _protected member_ `TAttribute<FText> MessageBoxText;` — When set will display an alert message in the header
- L145 _protected member_ `TAttribute<EOperatorStackEditorMessageType> MessageBoxType;` — When set will display an alert message in the header
- L147 _protected member_ `bool bHiddenByFilter = false;`
- L150 _private prototype_ `static TSharedRef<ICustomDetailsView> CreateDetailsView(const FCustomDetailsViewArgs& InArgs, const FOperatorStackEditorItem& InItem);`
- L152 _private prototype_ `void OnSearchTextChanged(const FText& InSearchText);`
- L153 _private prototype_ `void OnSearchTextCommitted(const FText& InFilterText, ETextCommit::Type InCommitType);`
- L154 _private prototype_ `void OnSearchPinnedKeyword(ECheckBoxState InCheckState, FString InPinnedKeyword);`
- L157 _private prototype_ `void RequestSearchAsync() const;` — Request an async search on the main panel
- L160 _private prototype_ `bool HandleRecursiveSearch(const TSet<FString>& InSearchedKeywords_OR, const TSet<FString>& InSearchedKeywords_AND);` — Handles search in a recursive way, hiding items that do not match keywords
- L163 _private prototype_ `bool MatchSearch(const TSet<FString>& InSearchedKeywordsOR, const TSet<FString>& InSearchedKeywordsAND) const;` — Returns true when this item matches the keywords

### `Plugins/VirtualProduction/OperatorStack/Source/OperatorStack/Private/Widgets/SOperatorStackExpanderButton.h` (Private)


#### class `SOperatorStackExpanderButton`  
`class SOperatorStackExpanderButton : public SCompoundWidget`  
_L16-56_
- inherits: `SCompoundWidget`
- desc: A simple expander button with image, fires an event everytime state changes
- L19 _public function_ `SLATE_BEGIN_ARGS(SOperatorStackExpanderButton) : _StartsExpanded(true) , _CollapsedButtonIcon(FAppStyle::Get().GetBrush(TEXT("TreeArrow_Collapsed"))) , _ExpandedButtonIcon(FAppStyle::Get().GetBrush(TEXT("TreeArrow_Expanded"))) , _CollapsedHoveredButtonIcon(FAppStyle::Get().GetBrush(TEXT("TreeArrow_Collapsed_Hovered"))) , _ExpandedHoveredButtonIcon(FAppStyle::Get().GetBrush(TEXT("TreeArrow_Expanded_Hovered")))`
- L27 _public prototype_ `SLATE_ARGUMENT(bool, StartsExpanded) SLATE_ARGUMENT(const FSlateBrush*, CollapsedButtonIcon) SLATE_ARGUMENT(const FSlateBrush*, ExpandedButtonIcon) SLATE_ARGUMENT(const FSlateBrush*, CollapsedHoveredButtonIcon) SLATE_ARGUMENT(const FSlateBrush*, ExpandedHoveredButtonIcon) SLATE_EVENT(FOperatorStackExpanderButtonStateChanged, OnExpansionStateChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — Are we expanded by default
- L40 _private prototype_ `const FSlateBrush* GetExpanderIcon() const;`
- L41 _private prototype_ `FReply OnExpanderButtonClicked();`
- L43 _private prototype_ `void BroadcastExpansion() const;`
- L44 _private prototype_ `void ToggleExpansion();`
- L46 _private member_ `FOperatorStackExpanderButtonStateChanged OnExpansionStateChangedEvent;`
- L48 _private member_ `TSharedPtr<SButton> ExpanderButton;`
- L50 _private member_ `const FSlateBrush* CollapsedButtonIcon = nullptr;`
- L51 _private member_ `const FSlateBrush* ExpandedButtonIcon = nullptr;`
- L52 _private member_ `const FSlateBrush* CollapsedHoveredButtonIcon = nullptr;`
- L53 _private member_ `const FSlateBrush* ExpandedHoveredButtonIcon = nullptr;`
- L55 _private member_ `bool bIsItemExpanded = true;`

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_DELEGATE_OneParam(FOperatorStackExpanderButtonStateChanged, bool) class SOperatorStackExpanderButton : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SOperatorStackExpanderButton) : _StartsExpanded(true) , _CollapsedButtonIcon(FAppStyle::Get().GetBrush(TEXT("TreeArrow_Collapsed"))) , _ExpandedButtonIcon(FAppStyle::Get().GetBrush(TEXT("TreeArrow_Expanded"))) , _CollapsedHoveredButtonIcon(FAppStyle::Get().GetBrush(TEXT("TreeArrow_Collapsed_Hovered"))) , _ExpandedHoveredButtonIcon(FAppStyle::Get().GetBrush(TEXT("TreeArrow_Expanded_Hovered"))) {} SLATE_ARGUMENT(bool, StartsExpanded) SLATE_ARGUMENT(const FSlateBrush*, CollapsedButtonIcon) SLATE_ARGUMENT(const FSlateBrush*, ExpandedButtonIcon) SLATE_ARGUMENT(const FSlateBrush*, CollapsedHoveredButtonIcon) SLATE_ARGUMENT(const FSlateBrush*, ExpandedHoveredButtonIcon) SLATE_EVENT(FOperatorStackExpanderButtonStateChanged, OnExpansionStateChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs); private: const FSlateBrush* GetExpanderIcon() const; FReply OnExpanderButtonClicked(); void BroadcastExpansion() const; void ToggleExpansion(); FOperatorStackExpanderButtonStateChanged OnExpansionStateChangedEvent; TSharedPtr<SButton> ExpanderButton; const FSlateBrush* CollapsedButtonIcon = nullptr; const FSlateBrush* ExpandedButtonIcon = nullptr; const FSlateBrush* CollapsedHoveredButtonIcon = nullptr;`

### `Plugins/VirtualProduction/OperatorStack/Source/OperatorStack/Private/Widgets/TableRows/SOperatorStackEditorStackRow.h` (Private)


#### class `SOperatorStackEditorStackRow`  
`class SOperatorStackEditorStackRow : public STableRow<FOperatorStackEditorItemPtr>`  
_L12-44_
- inherits: `STableRow<FOperatorStackEditorItemPtr>`
- desc: A single row item in the stack listview that contains a stack, get it it's recursive :)
- L16 _public function_ `SLATE_BEGIN_ARGS(SOperatorStackEditorStackRow)`
- L17 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs , const TSharedRef<STableViewBase>& InOwnerTableView , const TSharedPtr<SOperatorStackEditorStack>& InOuterStack , const FOperatorStackEditorItemPtr& InCustomizeItem);`
- L24 _public function_ `TSharedPtr<SOperatorStackEditorStack> GetInnerStack() const`
- L31 _protected prototype_ `FReply OnStackDragDetected(const FGeometry& InGeometry, const FPointerEvent& InPointer) const;` — When starting a stack drag operation
- L34 _protected prototype_ `TOptional<EItemDropZone> OnStackCanAcceptDrop(const FDragDropEvent& InDropEvent, EItemDropZone InZone, FOperatorStackEditorItemPtr InZoneItem) const;` — Whether we allow or disallow drop
- L37 _protected prototype_ `FReply OnStackDrop(FDragDropEvent const& InEvent) const;` — When a drop event happens on an item
- L40 _protected prototype_ `virtual int32 OnPaintDropIndicator(EItemDropZone InZone, const FPaintArgs& InPaintArgs, const FGeometry& InGeometry, const FSlateRect& InSlateRect, FSlateWindowElementList& OutDrawElements, int32 InLayerId, const FWidgetStyle& InWidgetStyle, bool bInParentEnabled) const override;` — Draw indicator for drop
- L42 _protected member_ `TWeakPtr<SOperatorStackEditorStack> OuterStackWeak;`
- L43 _protected member_ `TSharedPtr<SOperatorStackEditorStack> InnerStack;`

### `Plugins/VirtualProduction/OperatorStack/Source/OperatorStack/Private/Widgets/Tabs/OperatorStackEditorTabInstance.h` (Private)


#### struct `FOperatorStackEditorTabInstance`  
`struct FOperatorStackEditorTabInstance : TSharedFromThis<FOperatorStackEditorTabInstance>`  
_L16-48_
- inherits: `TSharedFromThis<FOperatorStackEditorTabInstance>`
- L18 _public prototype_ `explicit FOperatorStackEditorTabInstance(const TSharedRef<ILevelEditor>& InLevelEditor);`
- L19 _public prototype_ `virtual ~FOperatorStackEditorTabInstance();`
- L21 _public prototype_ `TSharedPtr<SDockTab> InvokeTab();`
- L22 _public prototype_ `bool CloseTab();`
- L23 _public prototype_ `bool RefreshTab(UObject* InContext, bool bInForce);`
- L24 _public prototype_ `bool FocusTab(const UObject* InContext, FName InIdentifier);`
- L26 _public prototype_ `TSharedPtr<SOperatorStackEditorWidget> GetOperatorStackEditorWidget() const;`
- L27 _public prototype_ `bool RegisterTab();`
- L28 _public prototype_ `bool UnregisterTab();`
- L30 _public function_ `TSharedPtr<ILevelEditor> GetLevelEditor() const`
- L36 _private prototype_ `void BindDelegates();`
- L37 _private prototype_ `void UnbindDelegates();`
- L39 _private prototype_ `TSharedRef<SDockTab> OnSpawnTab(const FSpawnTabArgs& InArgs);`
- L40 _private prototype_ `void OnSelectionSetChanged(const UTypedElementSelectionSet* InSelection, bool bInForce);`
- L41 _private prototype_ `void OnSelectionChanged(UObject* InSelectionObject);`
- L43 _private prototype_ `bool CheckActiveSelection(float, TWeakObjectPtr<const UTypedElementSelectionSet> InSelectionWeak, bool bInForce);`
- L45 _private member_ `TWeakPtr<ILevelEditor> LevelEditorWeak;`
- L46 _private member_ `int32 WidgetIdentifier = INDEX_NONE;`
- L47 _private member_ `FTSTicker::FDelegateHandle SelectionDelegateHandle;`

### `Plugins/VirtualProduction/OperatorStack/Source/OperatorStack/Public/Builders/OperatorStackEditorBodyBuilder.h` (Public)


#### struct `FOperatorStackEditorBodyBuilder`  
`struct FOperatorStackEditorBodyBuilder`  
_L13-109_
- desc: Body builder for item
- L16 _public prototype_ `FOperatorStackEditorBodyBuilder& SetCustomWidget(TSharedPtr<SWidget> InWidget);` — Override the stack generated widget with a custom one
- L19 _public prototype_ `FOperatorStackEditorBodyBuilder& SetShowDetailsView(bool bInShowDetailsView);` — Show a details view for the current item
- L22 _public prototype_ `FOperatorStackEditorBodyBuilder& SetDetailsViewItem(TSharedPtr<FOperatorStackEditorItem> InItem);` — Set the item that needs to be displayed by the details view overriding current item
- L25 _public prototype_ `FOperatorStackEditorBodyBuilder& DisallowProperty(FProperty* InProperty);` — Disallow specific property in the details view
- L28 _public prototype_ `FOperatorStackEditorBodyBuilder& DisallowCategory(const FName& InCategory);` — Disallow specific category in the details view
- L31 _public prototype_ `FOperatorStackEditorBodyBuilder& AllowProperty(FProperty* InProperty);` — Allow specific property in the details view
- L34 _public prototype_ `FOperatorStackEditorBodyBuilder& AllowCategory(const FName& InCategory);` — Allow specific category in the details view
- L37 _public prototype_ `FOperatorStackEditorBodyBuilder& ExpandProperty(FProperty* InProperty);` — Expand property state in the details view
- L40 _public prototype_ `FOperatorStackEditorBodyBuilder& CollapseProperty(FProperty* InProperty);` — Collapse property state in the details view
- L43 _public prototype_ `FOperatorStackEditorBodyBuilder& SetEmptyBodyText(const FText& InText);` — Set a text that will be displayed when it is empty
- L45 _public function_ `TSharedPtr<SWidget> GetCustomWidget() const`
- L50 _public function_ `bool GetShowDetailsView() const`
- L55 _public function_ `TSharedPtr<FOperatorStackEditorItem> GetDetailsViewItem() const`
- L60 _public function_ `const TArray<TSharedRef<FCustomDetailsViewItemId>>& GetDisallowedDetailsViewItems() const`
- L65 _public function_ `const TArray<TSharedRef<FCustomDetailsViewItemId>>& GetAllowedDetailsViewItems() const`
- L70 _public function_ `const TArray<TSharedRef<FCustomDetailsViewItemId>>& GetCollapsedDetailsViewItems() const`
- L75 _public function_ `const TArray<TSharedRef<FCustomDetailsViewItemId>>& GetExpandedDetailsViewItems() const`
- L80 _public function_ `const FText& GetEmptyBodyText() const`
- L87 _protected member_ `TSharedPtr<SWidget> CustomWidget = nullptr;` — Custom widget to replace content
- L90 _protected member_ `bool bShowDetailsView = false;` — Does this body contains a details view
- L93 _protected member_ `TSharedPtr<FOperatorStackEditorItem> DetailsViewItem = nullptr;` — Override actual item to display detail view
- L96 _protected member_ `FText EmptyBodyText;` — When the body is empty, this will be displayed
- L99 _protected member_ `TArray<TSharedRef<FCustomDetailsViewItemId>> DisallowedDetailsViewItems;` — Disallowed items inside details view
- L102 _protected member_ `TArray<TSharedRef<FCustomDetailsViewItemId>> AllowedDetailsViewItems;` — Allowed items inside details view
- L105 _protected member_ `TArray<TSharedRef<FCustomDetailsViewItemId>> CollapsedDetailsViewItems;` — Collapsed items inside details view
- L108 _protected member_ `TArray<TSharedRef<FCustomDetailsViewItemId>> ExpandedDetailsViewItems;` — Expanded items inside details view

### `Plugins/VirtualProduction/OperatorStack/Source/OperatorStack/Public/Builders/OperatorStackEditorFooterBuilder.h` (Public)


#### Free symbols / members of external scopes

- L8 _typedef_ `typedef FOperatorStackEditorBodyBuilder FOperatorStackEditorFooterBuilder;` — Body and Footer are the same at the moment, we may add additional behaviour here

### `Plugins/VirtualProduction/OperatorStack/Source/OperatorStack/Public/Builders/OperatorStackEditorHeaderBuilder.h` (Public)


#### enum `EOperatorStackEditorMessageType`  
`enum class EOperatorStackEditorMessageType`  
_L15-26_
- L17 _public enumerator_ `None`
- L19 _public enumerator_ `Info` — Blue message for information message
- L21 _public enumerator_ `Success` — Green message for success message
- L23 _public enumerator_ `Warning` — Yellow message for warning message
- L25 _public enumerator_ `Error` — Red message for error message

#### struct `FOperatorStackEditorHeaderBuilder`  
`struct FOperatorStackEditorHeaderBuilder`  
_L29-242_
- desc: Header builder for item
- L32 _public prototype_ `FOperatorStackEditorHeaderBuilder& SetIcon(const FSlateBrush* InIcon);` — Set the icon to display for this item header
- L35 _public prototype_ `FOperatorStackEditorHeaderBuilder& SetLabel(const FText& InLabel);` — Set the label to display for this item header
- L38 _public prototype_ `FOperatorStackEditorHeaderBuilder& SetTooltip(const FText& InTooltip);` — Set the tooltip to display for this item header
- L41 _public prototype_ `FOperatorStackEditorHeaderBuilder& SetBorderColor(const FLinearColor& InColor);` — Sets the border color surrounding the item
- L44 _public prototype_ `FOperatorStackEditorHeaderBuilder& SetProperty(FProperty* InProperty);` — Set a single property to expose in the header, like a boolean
- L47 _public prototype_ `FOperatorStackEditorHeaderBuilder& SetToolbarMenu(const FName& InActionMenuName);` — Set a small menu that contains icon entries on the right
- L50 _public prototype_ `FOperatorStackEditorHeaderBuilder& SetToolMenu(const FName& InToolMenuName, const FText& InToolMenuLabel, const FSlateBrush* InToolMenuIcon);` — Set a menu that appears when we press a button with a label and icon in the header
- L53 _public prototype_ `FOperatorStackEditorHeaderBuilder& SetSearchAllowed(bool bInSearchable);` — Allow search on this item, if the stack header is searchable a search box will appear
- L56 _public prototype_ `FOperatorStackEditorHeaderBuilder& SetSearchKeywords(const TSet<FString>& InKeywords);` — Sets keywords for this item, if the keyword is contained inside this item will show
- L59 _public prototype_ `FOperatorStackEditorHeaderBuilder& SetSearchPinnedKeywords(const TSet<FString>& InKeywords);` — Sets pinned keywords on root item, they will appear on top of the search bar
- L62 _public prototype_ `FOperatorStackEditorHeaderBuilder& SetExpandable(bool bInExpandable);` — Whether the item is expandable
- L65 _public prototype_ `FOperatorStackEditorHeaderBuilder& SetStartsExpanded(bool bInExpanded);` — Whether the item starts expanded or collapsed
- L68 _public prototype_ `FOperatorStackEditorHeaderBuilder& SetDraggable(bool bInDraggable);` — Whether the item is draggable
- L71 _public prototype_ `FOperatorStackEditorHeaderBuilder& SetCommandList(TSharedPtr<FUICommandList> InCommands);` — Sets available commands on this item
- L74 _public prototype_ `FOperatorStackEditorHeaderBuilder& SetContextMenu(const FName& InToolMenuName);` — Sets context menu name on this item
- L77 _public prototype_ `FOperatorStackEditorHeaderBuilder& SetCustomWidget(TSharedPtr<SWidget> InWidget);` — Sets the custom widget replacing the stack generated widget
- L80 _public prototype_ `FOperatorStackEditorHeaderBuilder& SetMessageBox(const TAttribute<EOperatorStackEditorMessageType>& InType, const TAttribute<FText>& InText);` — Sets whether to show a message box in the header for warning, error, success operations
- L82 _public function_ `const FSlateBrush* GetIcon() const`
- L87 _public function_ `const FText& GetLabel() const`
- L92 _public function_ `const FText& GetTooltip() const`
- L97 _public function_ `const FLinearColor& GetBorderColor() const`
- L102 _public function_ `const FName& GetToolbarMenuName() const`
- L107 _public function_ `const TSharedPtr<FCustomDetailsViewItemId>& GetProperty() const`
- L112 _public function_ `const FName& GetToolMenuName() const`
- L117 _public function_ `const FSlateBrush* GetToolMenuIcon() const`
- L122 _public function_ `const FText& GetToolMenuLabel() const`
- L127 _public function_ `bool GetSearchAllowed() const`
- L132 _public function_ `const TSet<FString>& GetSearchKeywords() const`
- L137 _public function_ `const TSet<FString>& GetSearchPinnedKeywords() const`
- L142 _public function_ `bool GetExpandable() const`
- L147 _public function_ `bool GetStartsExpanded() const`
- L152 _public function_ `bool GetDraggable() const`
- L157 _public function_ `const TSharedPtr<FUICommandList>& GetCommandList() const`
- L162 _public function_ `const FName& GetContextMenuName() const`
- L167 _public function_ `TSharedPtr<SWidget> GetCustomWidget() const`
- L172 _public function_ `const TAttribute<EOperatorStackEditorMessageType>& GetMessageBoxType() const`
- L177 _public function_ `const TAttribute<FText>& GetMessageBoxText() const`
- L184 _protected member_ `const FSlateBrush* Icon = nullptr;` — On the left
- L187 _protected member_ `FText Label;` — On the left, after to icon
- L190 _protected member_ `FText Tooltip;` — Shown on the header
- L193 _protected member_ `FLinearColor BorderColor = FLinearColor::Transparent;` — The border color surrounding the item
- L196 _protected member_ `FName ToolbarMenuName;` — Menu on the right before property, should not contain a lot of entries and only icons
- L199 _protected member_ `TSharedPtr<FCustomDetailsViewItemId> Property = nullptr;` — On the right, property id to expose in the header
- L202 _protected member_ `FName ToolMenuName;` — Menu present in the header for additional actions
- L205 _protected member_ `const FSlateBrush* ToolMenuIcon = nullptr;` — Menu icon in the header
- L208 _protected member_ `FText ToolMenuLabel;` — Menu label in the header as a tooltip and label
- L211 _protected member_ `bool bSearchAllowed = false;` — Allow use of search bar to filter content
- L214 _protected member_ `TSet<FString> SearchKeywords;` — Keywords to test against search input
- L217 _protected member_ `TSet<FString> SearchPinnedKeywords;` — Pinned keywords for search, will appear below search box, only for root stack
- L220 _protected member_ `bool bExpandable = false;` — Allow expandable header to show the body and footer
- L223 _protected member_ `bool bStartsExpanded = true;` — Starts expanded or not
- L226 _protected member_ `bool bDraggable = false;` — Allow drag operation on this item
- L229 _protected member_ `TSharedPtr<FUICommandList> CommandList;` — Commands executable for this item
- L232 _protected member_ `FName ContextMenuName;` — Context menu available on this item
- L235 _protected member_ `TSharedPtr<SWidget> CustomWidget;` — Widget that overrides the whole stack generated widget
- L238 _protected member_ `TAttribute<EOperatorStackEditorMessageType> MessageBoxType;` — The type of message box we want to show
- L241 _protected member_ `TAttribute<FText> MessageBoxText;` — The text content of the message box

### `Plugins/VirtualProduction/OperatorStack/Source/OperatorStack/Public/Contexts/OperatorStackEditorContext.h` (Public)


#### struct `FOperatorStackEditorContext`  
`struct FOperatorStackEditorContext final`  
_L9-57_
- desc: Represent the current context we customize for the whole operator stack
- L11 _public prototype_ `FOperatorStackEditorContext() = default;`
- L12 _public function_ `explicit FOperatorStackEditorContext(const TArray<TSharedPtr<FOperatorStackEditorItem>>& InItems) : Items(InItems)`
- L36 _public function_ `TConstArrayView<TSharedPtr<FOperatorStackEditorItem>> GetItems() const` — Items we want to customize
- L46 _public function_ `bool operator==(const FOperatorStackEditorContext& InOther) const`
- L53 _protected member_ `TArray<TSharedPtr<FOperatorStackEditorItem>> Items;` — Context items being customized
- L56 _protected member_ `uint32 CachedHash = 0;` — Context items hash to compare contexts

#### Free symbols / members of external scopes

- L41 _function_ `friend uint32 GetTypeHash(const FOperatorStackEditorContext& InItem)`
- L59 _typedef_ `typedef TSharedPtr<FOperatorStackEditorContext> FOperatorStackEditorContextPtr;`
- L60 _typedef_ `typedef TWeakPtr<FOperatorStackEditorContext> FOperatorStackEditorContextPtrWeak;`

### `Plugins/VirtualProduction/OperatorStack/Source/OperatorStack/Public/Contexts/OperatorStackEditorMenuContext.h` (Public)


#### class `UOperatorStackEditorMenuContext`  
`class UOperatorStackEditorMenuContext : public UObject`  
_L14-45_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Context passed in UToolMenu when generating entries with selected items
- L19 _public function_ `TSharedPtr<FOperatorStackEditorContext> GetContext() const`
- L24 _public function_ `void SetContext(TSharedPtr<FOperatorStackEditorContext> InContext)`
- L29 _public function_ `TSharedPtr<FOperatorStackEditorItem> GetItem() const`
- L34 _public function_ `void SetItem(TSharedPtr<FOperatorStackEditorItem> InItem)`
- L41 _protected member_ `TWeakPtr<FOperatorStackEditorContext> ContextWeak;` — The current context this menu is extending
- L44 _protected member_ `TWeakPtr<FOperatorStackEditorItem> ItemWeak;` — The item this menu should apply to

### `Plugins/VirtualProduction/OperatorStack/Source/OperatorStack/Public/Customizations/OperatorStackEditorStackCustomization.h` (Public)


#### class `UOperatorStackEditorStackCustomization`  
`class UOperatorStackEditorStackCustomization : public UObject`  
_L26-155_
- reflection: `UCLASS(MinimalAPI, Abstract, Transient)`
- inherits: `UObject`
- desc: Abstract class to represent an operator stack containing items, an item is represented by a header-body-footer, An item can contain multiple items (recursive), Children class extending this class are automatically registered
- L34 _public function_ `UOperatorStackEditorStackCustomization() : UOperatorStackEditorStackCustomization(NAME_None, FText::GetEmpty())`
- L38 _public function_ `UOperatorStackEditorStackCustomization(const FName& InIdentifier, const FText& InLabel, int32 InPriority = INDEX_NONE) : Identifier(InIdentifier) , Label(InLabel) , Priority(InPriority)`
- L45 _public prototype_ `bool RegisterCustomizationFor(const UStruct* InItemDefinition);` — Registers items with this definition that can use this customization
- L46 _public prototype_ `bool RegisterCustomizationFor(const FFieldClass* InItemDefinition);`
- L49 _public prototype_ `bool UnregisterCustomizationFor(const UStruct* InItemDefinition);` — Unregisters item definition for this customization
- L50 _public prototype_ `bool UnregisterCustomizationFor(const FFieldClass* InItemDefinition);`
- L53 _public prototype_ `bool IsCustomizationSupportedFor(const FOperatorStackEditorItemPtr& InItem) const;` — Checks if this customization is supported for this item
- L56 _public function_ `virtual bool GetRootItem(const FOperatorStackEditorContext& InContext, FOperatorStackEditorItemPtr& OutRootItem) const` — Retrieves root supported item out of the provided context, Children classes must implement this
- L62 _public function_ `virtual bool GetChildrenItem(const FOperatorStackEditorItemPtr& InItem, TArray<FOperatorStackEditorItemPtr>& OutChildrenItems) const` — Retrieves the supported children items based out of a parent item, Children classes must implement this
- L68 _public function_ `virtual void CustomizeStackHeader(const FOperatorStackEditorTree& InItemTree, FOperatorStackEditorHeaderBuilder& InStackHeaderBuilder)` — Customize the header for a context
- L71 _public function_ `virtual void CustomizeStackBody(const FOperatorStackEditorTree& InItemTree, FOperatorStackEditorBodyBuilder& InStackBodyBuilder)` — Customize the full stack body
- L74 _public function_ `virtual void CustomizeItemHeader(const FOperatorStackEditorItemPtr& InItem, const FOperatorStackEditorTree& InItemTree, FOperatorStackEditorHeaderBuilder& InHeaderBuilder)` — Customize the header for a supported item
- L77 _public function_ `virtual void CustomizeItemBody(const FOperatorStackEditorItemPtr& InItem, const FOperatorStackEditorTree& InItemTree, FOperatorStackEditorBodyBuilder& InBodyBuilder)` — Customize the body for a supported item
- L80 _public function_ `virtual void CustomizeItemFooter(const FOperatorStackEditorItemPtr& InItem, const FOperatorStackEditorTree& InItemTree, FOperatorStackEditorFooterBuilder& InFooterBuilder)` — Customize the body for a supported item
- L83 _public function_ `virtual bool OnIsItemSelectable(const FOperatorStackEditorItemPtr& InItem)` — Can an item be selected
- L89 _public function_ `virtual bool OnIsItemDraggable(const FOperatorStackEditorItemPtr& InItem)` — Can an item be dragged
- L95 _public function_ `virtual TOptional<EItemDropZone> OnItemCanAcceptDrop(const TArray<FOperatorStackEditorItemPtr>& InDraggedItems, const FOperatorStackEditorItemPtr& InTargetItem, EItemDropZone InTargetZone)` — Get the valid drop zone of draggable items onto a zone item
- L101 _public function_ `virtual void OnDropItem(const TArray<FOperatorStackEditorItemPtr>& InDraggedItems, const FOperatorStackEditorItemPtr& InTargetItem, EItemDropZone InTargetZone)` — Handle dropped items onto target zone
- L104 _public function_ `const FName& GetIdentifier() const` — Get identifier of this customization
- L110 _public function_ `const FText& GetLabel() const` — Get display label of this customization
- L116 _public function_ `int32 GetPriority() const` — Get stack priority in the toolbar
- L122 _public prototype_ `virtual const FSlateBrush* GetIcon() const;` — Get the displayed icon of this customization
- L125 _public prototype_ `void RefreshActiveSelection(UObject* InContext, bool bInForce) const;` — Refresh the selection linked to this context
- L128 _public prototype_ `void FocusCustomization(const UObject* InContext) const;` — Switches section of operator stack and select this customization for this context
- L131 _public function_ `virtual bool ShouldFocusCustomization(const FOperatorStackEditorContext& InContext) const` — Whether new context should focus on this customization in the widget
- L139 _private member_ `FName Identifier;` — `UPROPERTY()` — Unique identifier of this customization
- L143 _private member_ `FText Label;` — `UPROPERTY()` — Label displayed at the top to switch between customizations
- L147 _private member_ `int32 Priority;` — `UPROPERTY()` — Priority for this stack in toolbar, highest numbers will result in placement before lowest number
- L151 _private member_ `TSet<TObjectPtr<const UStruct>> SupportedDefinitions;` — `UPROPERTY()` — Supported definition for this customization stack
- L154 _private member_ `TSet<const FFieldClass*> SupportedFieldClasses;` — Supported definition for this customization stack

### `Plugins/VirtualProduction/OperatorStack/Source/OperatorStack/Public/Items/OperatorStackEditorGroupItem.h` (Public)


#### struct `FOperatorStackEditorGroupItem`  
`struct FOperatorStackEditorGroupItem : FOperatorStackEditorItem`  
_L8-74_
- inherits: `FOperatorStackEditorItem`
- desc: Groups item of the same type together
- L10 _public function_ `explicit FOperatorStackEditorGroupItem(const TArray<FOperatorStackEditorItemPtr>& InItems, const FOperatorStackEditorItemType& InType) : FOperatorStackEditorItem( InType )`
- L40 _public function_ `virtual uint32 GetValueCount() const override`
- L45 _public function_ `virtual bool HasValue(uint32 InIndex) const override`
- L56 _public function_ `virtual uint32 GetHash() const override`
- L61 _public function_ `virtual void* GetValuePtr(uint32 InIndex) const override`
- L73 _protected member_ `TArray<FOperatorStackEditorItemPtr> Items;`

### `Plugins/VirtualProduction/OperatorStack/Source/OperatorStack/Public/Items/OperatorStackEditorItem.h` (Public)


#### struct `FOperatorStackEditorItem`  
`struct FOperatorStackEditorItem`  
_L16-191_
- desc: Abstract base parent item
- L18 _public function_ `explicit FOperatorStackEditorItem(const FOperatorStackEditorItemType& InType) : ItemType(InType)`
- L22 _public prototype_ `virtual ~FOperatorStackEditorItem() = default;`
- L28 _public function_ `template<typename InValueType> bool IsA() const` — You can use this to check if Item.IsA<UObject>() or Item.IsA<FMyStruct>() or Item.IsA<FIntProperty>()
- L74 _public function_ `template <typename InValueType> InValueType* Get(uint32 InIndex) const` — You can use this to get the item Item.Get<UObject>() or Item.Get<FMyStruct>() or Item.Get<int32>()
- L112 _public function_ `template <typename InValueType> TArray<InValueType*> GetAsArray() const` — You can use this to get all the underlying items as an array of a specific type
- L131 _public function_ `const FOperatorStackEditorItemType& GetValueType() const` — Get the value type of this item
- L137 _public function_ `virtual uint32 GetValueCount() const` — Get the amount of value stored within this item
- L143 _public function_ `bool HasValue() const` — Checks if this item has at least one value and that it is usable
- L156 _public function_ `virtual bool HasValue(uint32 InIndex) const` — Checks if this item has a value and that it is usable
- L162 _public function_ `virtual void* GetValuePtr(uint32 InIndex) const` — Get raw ptr to value, prefer using Get<>() instead
- L168 _public function_ `virtual uint32 GetHash() const` — Override in child to be able to compare item
- L178 _public function_ `bool operator==(const FOperatorStackEditorItem& InOtherItem) const`
- L189 _protected member_ `uint32 CachedHash = 0;`
- L190 _protected member_ `FOperatorStackEditorItemType ItemType;`

#### Free symbols / members of external scopes

- L173 _function_ `friend uint32 GetTypeHash(const FOperatorStackEditorItem& InItem)`
- L193 _typedef_ `typedef TSharedPtr<FOperatorStackEditorItem> FOperatorStackEditorItemPtr;`
- L194 _typedef_ `typedef TWeakPtr<FOperatorStackEditorItem> FOperatorStackEditorItemPtrWeak;`

### `Plugins/VirtualProduction/OperatorStack/Source/OperatorStack/Public/Items/OperatorStackEditorItemType.h` (Public)


#### enum `EOperatorStackEditorItemType`  
`enum class EOperatorStackEditorItemType : uint8`  
_L15-21_
- desc: Used to quickly get the general type of an item without casting
- L17 _public enumerator_ `None`
- L18 _public enumerator_ `Object`
- L19 _public enumerator_ `Struct`
- L20 _public enumerator_ `Primitive`

#### struct `FOperatorStackEditorItemType`  
`struct FOperatorStackEditorItemType`  
_L24-111_
- desc: Item type
- L28 _public function_ `explicit FOperatorStackEditorItemType(const InTypeClass* InType, EOperatorStackEditorItemType InTypeEnum) : TypeClass(InType) , TypeEnum(InTypeEnum)`
- L36 _public function_ `bool IsChildOf(const InTypeClass* InOtherType) const`
- L46 _public function_ `bool IsChildOf(const FOperatorStackEditorItemType* InOtherType) const`
- L73 _public function_ `const InTypeClass* Get() const`
- L78 _public function_ `EOperatorStackEditorItemType GetTypeEnum() const`
- L100 _public function_ `bool operator==(const FOperatorStackEditorItemType& InOtherItem) const`
- L109 _private member_ `TUnion<const UStruct*, const FFieldClass*> TypeClass;`
- L110 _private member_ `EOperatorStackEditorItemType TypeEnum = EOperatorStackEditorItemType::None;`

#### Free symbols / members of external scopes

- L83 _function_ `friend uint32 GetTypeHash(const FOperatorStackEditorItemType& InItem)`

### `Plugins/VirtualProduction/OperatorStack/Source/OperatorStack/Public/Items/OperatorStackEditorObjectItem.h` (Public)


#### struct `FOperatorStackEditorObjectItem`  
`struct FOperatorStackEditorObjectItem : FOperatorStackEditorItem`  
_L14-50_
- inherits: `FOperatorStackEditorItem`
- desc: Object version of item
- L19 _public function_ `explicit FOperatorStackEditorObjectItem(InValueType* InItem) : FOperatorStackEditorItem( FOperatorStackEditorItemType(InItem ? InItem->GetClass() : nullptr, EOperatorStackEditorItemType::Object) )`
- L28 _public function_ `virtual uint32 GetValueCount() const override`
- L33 _public function_ `virtual bool HasValue(uint32 InIndex) const override`
- L38 _public function_ `virtual uint32 GetHash() const override`
- L43 _public function_ `virtual void* GetValuePtr(uint32 InIndex) const override`
- L49 _protected member_ `TWeakObjectPtr<UObject> ObjectWeak;`

### `Plugins/VirtualProduction/OperatorStack/Source/OperatorStack/Public/Items/OperatorStackEditorPrimitiveItem.h` (Public)


#### struct `FOperatorStackEditorPrimitiveItem`  
`struct FOperatorStackEditorPrimitiveItem : FOperatorStackEditorItem`  
_L14-50_
- inherits: `FOperatorStackEditorItem`
- desc: Primitive version of item
- L19 _public function_ `explicit FOperatorStackEditorPrimitiveItem(FFieldClass* InFieldClass, InItemDefinition& InValue) : FOperatorStackEditorItem( FOperatorStackEditorItemType(InFieldClass, EOperatorStackEditorItemType::Primitive) )`
- L28 _public function_ `virtual uint32 GetValueCount() const override`
- L33 _public function_ `virtual bool HasValue(uint32 InIndex) const override`
- L38 _public function_ `virtual uint32 GetHash() const override`
- L43 _public function_ `virtual void* GetValuePtr(uint32 InIndex) const override`
- L49 _protected member_ `uint8* MemoryPtr = nullptr;`

### `Plugins/VirtualProduction/OperatorStack/Source/OperatorStack/Public/Items/OperatorStackEditorStructItem.h` (Public)


#### struct `FOperatorStackEditorStructItem`  
`struct FOperatorStackEditorStructItem : FOperatorStackEditorItem`  
_L15-100_
- inherits: `FOperatorStackEditorItem`
- desc: Struct version of item
- L20 _public function_ `explicit FOperatorStackEditorStructItem(InValueType& InStruct) : FOperatorStackEditorItem( FOperatorStackEditorItemType(InValueType::StaticStruct(), EOperatorStackEditorItemType::Struct) )`
- L36 _public function_ `explicit FOperatorStackEditorStructItem(InValueType& InStruct) : FOperatorStackEditorItem( FOperatorStackEditorItemType(TBaseStructure<InValueType>::Get(), EOperatorStackEditorItemType::Struct) )`
- L50 _public function_ `explicit FOperatorStackEditorStructItem(const TSharedPtr<FStructOnScope>& InStruct) : FOperatorStackEditorItem( FOperatorStackEditorItemType(InStruct.IsValid() ? InStruct->GetStruct() : nullptr, EOperatorStackEditorItemType::Struct) )` — Version for struct on scope
- L63 _public function_ `TSharedPtr<FStructOnScope> GetStructOnScope() const`
- L68 _public function_ `virtual uint32 GetValueCount() const override`
- L73 _public function_ `virtual bool HasValue(uint32 InIndex) const override`
- L83 _public function_ `virtual uint32 GetHash() const override`
- L88 _public function_ `virtual void* GetValuePtr(uint32 InIndex) const override`
- L99 _protected member_ `TWeakPtr<FStructOnScope> StructWeak;`

### `Plugins/VirtualProduction/OperatorStack/Source/OperatorStack/Public/Items/OperatorStackEditorTree.h` (Public)


#### struct `FOperatorStackEditorTree`  
`struct FOperatorStackEditorTree`  
_L11-69_
- desc: Customization tree used to find all supported items by a customization object
- L13 _public prototype_ `explicit FOperatorStackEditorTree(UOperatorStackEditorStackCustomization* InCustomization, FOperatorStackEditorContextPtr InContext);`
- L16 _public prototype_ `FOperatorStackEditorItemPtr GetRootItem() const;` — Get all top items supported by this customization
- L19 _public prototype_ `TArray<FOperatorStackEditorItemPtr> GetChildrenItems(FOperatorStackEditorItemPtr InItem) const;` — Get supported children items from a supported item
- L22 _public prototype_ `FOperatorStackEditorItemPtr GetParentItem(FOperatorStackEditorItemPtr InItem) const;` — Get supported parent item from a supported child item
- L25 _public prototype_ `TArray<FOperatorStackEditorItemPtr> GetLeafItems() const;` — Get all leaf supported item
- L28 _public prototype_ `TConstArrayView<FOperatorStackEditorItemPtr> GetAllItems() const;` — Get all supported items by this customization
- L31 _public prototype_ `const FOperatorStackEditorContext& GetContext() const;` — Get source context used to build this tree
- L34 _public prototype_ `UOperatorStackEditorStackCustomization* GetCustomization() const;` — Get the customization used to build this tree
- L37 _public prototype_ `bool Contains(FOperatorStackEditorItemPtr InItem) const;` — Checks if an item is already contained in the tree
- L50 _private typedef_ `using FOperatorStackEditorTreeNodePtr = TSharedPtr<FOperatorStackEditorTreeNode>;`
- L52 _private prototype_ `TArray<FOperatorStackEditorItemPtr> GetSupportedChildrenItems(const FOperatorStackEditorItemPtr& InParentItem) const;`
- L53 _private prototype_ `void BuildTreeInternal(const TArray<FOperatorStackEditorItemPtr>& InItems, int32 InParent);`
- L56 _private member_ `TArray<FOperatorStackEditorItemPtr> Items;` — All items in this tree
- L59 _private member_ `TArray<FOperatorStackEditorTreeNodePtr> Nodes;` — All nodes in this tree
- L62 _private member_ `FOperatorStackEditorTreeNodePtr RootNode;` — Root items in the tree
- L65 _private member_ `TWeakObjectPtr<UOperatorStackEditorStackCustomization> CustomizationWeak;` — Customization used to build this tree
- L68 _private member_ `TWeakPtr<FOperatorStackEditorContext> ContextWeak;` — Source context used to build this tree

#### struct `FOperatorStackEditorTree::FOperatorStackEditorTreeNode`  
`struct FOperatorStackEditorTreeNode`  
_L41-48_
- desc: Customization tree node used only internally by the tree
- L43 _public prototype_ `explicit FOperatorStackEditorTreeNode(int32 InItemIndex, int32 InParentIndex);`
- L45 _public member_ `int32 ItemIndex = INDEX_NONE;`
- L46 _public member_ `int32 ParentIndex = INDEX_NONE;`
- L47 _public member_ `TArray<int32> ChildrenIndices;`

### `Plugins/VirtualProduction/OperatorStack/Source/OperatorStack/Public/Subsystems/OperatorStackEditorSubsystem.h` (Public)


#### class `UOperatorStackEditorSubsystem`  
`class UOperatorStackEditorSubsystem : public UEditorSubsystem`  
_L18-86_
- reflection: `UCLASS()`
- inherits: `UEditorSubsystem`
- desc: Subsystem that handles operator stack customization
- L26 _public member_ `static const FName TabId;`
- L27 _public prototype_ `static UOperatorStackEditorSubsystem* Get();`
- L29 _public function_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnOperatorStackSpawned, TSharedRef<SOperatorStackEditorWidget> ) static FOnOperatorStackSpawned::RegistrationType& OnOperatorStackSpawned()`
- L37 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L38 _public prototype_ `virtual void Deinitialize() override;`
- L41 _public prototype_ `bool RegisterStackCustomization(TSubclassOf<UOperatorStackEditorStackCustomization> InStackCustomizationClass);`
- L42 _public prototype_ `bool UnregisterStackCustomization(TSubclassOf<UOperatorStackEditorStackCustomization> InStackCustomizationClass);`
- L45 _public prototype_ `bool ForEachCustomization(TFunctionRef<bool(UOperatorStackEditorStackCustomization*)> InFunction) const;` — Loops through each customization stack in priority order, stops if false returned within function
- L48 _public prototype_ `UOperatorStackEditorStackCustomization* GetCustomization(const FName& InName) const;` — Get customization with identifier
- L51 _public prototype_ `TSharedRef<SOperatorStackEditorWidget> GenerateWidget();` — Generate an operator stack widget
- L54 _public prototype_ `TSharedPtr<SOperatorStackEditorWidget> FindWidget(int32 InId);` — Finds an existing operator stack widget
- L57 _public prototype_ `TArray<TSharedPtr<SOperatorStackEditorWidget>> FindWidgets(const UWorld* InContext);` — Finds existing operator stack widgets within a provided context
- L60 _public prototype_ `bool ForEachCustomizationWidget(TFunctionRef<bool(TSharedRef<SOperatorStackEditorWidget>)> InFunction) const;` — Loops through each operator stack widgets available
- L63 _public prototype_ `void RefreshCustomizationWidget(UObject* InContext, bool bInForce);` — Refresh only selection of widget with specific context
- L66 _public prototype_ `void FocusCustomizationWidget(const UObject* InContext, FName InIdentifier);` — Focus customization widget with specific context
- L69 _protected member_ `static FOnOperatorStackSpawned OnOperatorStackSpawnedDelegate;`
- L71 _protected prototype_ `void ScanForStackCustomizations();`
- L73 _protected prototype_ `void OnWidgetDestroyed(int32 InPanelId);`
- L75 _protected prototype_ `void OnLevelEditorCreated(TSharedPtr<ILevelEditor> InLevelEditor);`
- L79 _protected member_ `TMap<FName, TObjectPtr<UOperatorStackEditorStackCustomization>> CustomizationStacks;` — `UPROPERTY()` — Map of identifier and stack customization models
- L82 _protected member_ `TMap<int32, TWeakPtr<SOperatorStackEditorWidget>> CustomizationWidgets;` — Current widget created associated to an identifier
- L85 _protected member_ `TArray<TSharedPtr<FOperatorStackEditorTabInstance>> TabInstances;` — Current tab within editor

#### Free symbols / members of external scopes

- L29 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnOperatorStackSpawned, TSharedRef<SOperatorStackEditorWidget> ) static FOnOperatorStackSpawned::RegistrationType& OnOperatorStackSpawned() { return OnOperatorStackSpawnedDelegate; }`

### `Plugins/VirtualProduction/OperatorStack/Source/OperatorStack/Public/Widgets/SOperatorStackEditorWidget.h` (Public)


#### class `SOperatorStackEditorWidget`  
`class SOperatorStackEditorWidget : public SCompoundWidget`  
_L14-67_
- inherits: `SCompoundWidget`
- desc: Main operator stack widget created, only exposed function
- L18 _public function_ `virtual void SetActiveCustomization(const FName& InCustomization)` — Set the active customization in the panel
- L21 _public function_ `virtual void SetToolbarCustomizations(const TArray<FName>& InCustomizations)` — Sets the customization to show in the toolbar, overrides order
- L24 _public function_ `virtual void GetToolbarCustomizations(TArray<UOperatorStackEditorStackCustomization*>& OutCustomizations)` — Get all the customizations object active on this widget
- L27 _public function_ `virtual void ShowToolbarCustomization(FName InCustomization)` — Show the customization in the panel
- L30 _public function_ `virtual void HideToolbarCustomization(FName InCustomization)` — Hide the customization from the panel
- L33 _public function_ `virtual void SetToolbarVisibility(bool bInVisible)` — Sets the visibility of the toolbar to switch between customizations
- L36 _public function_ `virtual void SetContext(const FOperatorStackEditorContext& InNewContext)` — Update the context of the widget panel
- L39 _public function_ `virtual void SetKeyframeHandler(TSharedPtr<IDetailKeyframeHandler> InKeyframeHandler)` — Sets the keyframe handler to keyframe items properties
- L42 _public function_ `virtual void SetDetailColumnSize(TSharedPtr<FDetailColumnSizeData> InDetailColumnSize)` — Sets the detail column sizes to have same column sizes across items
- L45 _public function_ `virtual void SetPanelTag(FName InTag)` — Sets the panel tag to identify this panel
- L48 _public function_ `virtual void RefreshContext()` — Forces a refresh of the current context if any
- L51 _public function_ `virtual TSharedPtr<FOperatorStackEditorContext> GetContext() const` — Get the current context of this operator stack widget
- L57 _public function_ `virtual int32 GetPanelId() const` — Get the panel identifier, unique per widget
- L63 _public function_ `virtual FName GetPanelTag() const` — Get the panel tag
