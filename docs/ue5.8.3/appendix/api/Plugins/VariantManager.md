# Plugins / VariantManager

- module root: `Plugins/Enterprise/VariantManager/Source/VariantManager`
- headers: 38; symbols: 953
- symbol kinds: class=38, delegate=5, enum=4, enumerator=18, function=89, macro=1, member=226, namespace=2, prototype=561, struct=5, typedef=4
- PrivateDependencyModuleNames: AppFramework, AssetTools, BlueprintGraph, CinematicCamera, ContentBrowser, DesktopPlatform, EditorStyle, EditorWidgets, GraphEditor, InputCore, Projects, PropertyEditor, SceneOutliner, Slate, SlateCore, ToolMenus, ToolWidgets, VariantManagerContentEditor, WorkspaceMenuStructure
- PublicDependencyModuleNames: Core, CoreUObject, EditorFramework, Engine, PropertyPath, UnrealEd, VariantManagerContent

### `Plugins/Enterprise/VariantManager/Source/VariantManager/Private/ConsoleVariables.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace VariantManager` (scope `UE`)
- L10 _prototype_ `TAutoConsoleVariable<int32>& Get_CVar_VariantManager_CapturePropertyDialog();` (scope `UE::VariantManager`) — Controls which Capture Property Dialog UI is used (0=default, 1=updated with last used, two columns)
- L12 _prototype_ `TAutoConsoleVariable<bool>& Get_CVar_VariantManager_FunctionArgumentsUI();` (scope `UE::VariantManager`) — Enables UI for editing function caller arguments
- L14 _prototype_ `TAutoConsoleVariable<bool>& Get_CVar_VariantManager_AssetPicker();` (scope `UE::VariantManager`) — Improves the layout and adds asset picker to switch between Level Variant Sets.

### `Plugins/Enterprise/VariantManager/Source/VariantManager/Private/Dialogs/SCaptureDialog.h` (Private)


#### enum `ECaptureDialogType`  
`enum class ECaptureDialogType : uint8`  
_L14-18_
- L16 _public enumerator_ `Property`
- L17 _public enumerator_ `ActorAndProperty`

#### class `SCaptureDialog`  
`class SCaptureDialog : public SWindow`  
_L20-55_
- inherits: `SWindow`
- L23 _public function_ `SLATE_BEGIN_ARGS(SCaptureDialog)`
- L24 _public prototype_ `SLATE_ARGUMENT(ECaptureDialogType, DialogType) SLATE_ARGUMENT(const TArray<UObject*>*, ObjectsToCapture) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L30 _public prototype_ `TArray<UObject*> GetCurrentCheckedActors();`
- L31 _public prototype_ `TArray<TSharedPtr<FCapturableProperty>> GetCurrentCheckedProperties();`
- L32 _public function_ `bool GetUserAccepted()`
- L34 _public prototype_ `static TSharedPtr<SCaptureDialog> OpenCaptureDialogAsModalWindow(ECaptureDialogType DialogType, const TArray<UObject*>& ObjectsToCapture);`
- L38 _private prototype_ `FReply OnDialogConfirmed();`
- L39 _private prototype_ `FReply OnDialogCanceled();`
- L42 _private prototype_ `virtual FReply OnKeyDown( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override;` — Overloaded from SWidget
- L44 _private member_ `TSharedPtr<SCapturedActorsWidget> ActorWidget;`
- L45 _private member_ `TSharedPtr<SCapturedPropertiesWidgetBase> PropertiesWidget;`
- L46 _private member_ `TSharedPtr<SSearchBox> SearchBox;`
- L48 _private member_ `TSharedPtr<SSplitter> Splitter;`
- L50 _private member_ `TArray<TSharedPtr<FCapturableProperty>> CapturedProperties;`
- L51 _private member_ `bool bUserAccepted = false;`
- L53 _private member_ `TWeakPtr<SWindow> WeakWindow;`
- L54 _private member_ `int DialogVersion = 0;`

### `Plugins/Enterprise/VariantManager/Source/VariantManager/Private/Dialogs/SCapturedActorsWidget.h` (Private)


#### class `SCapturedActorsWidget`  
`class SCapturedActorsWidget : public SCompoundWidget`  
_L11-33_
- inherits: `SCompoundWidget`
- L14 _public function_ `SLATE_BEGIN_ARGS(SCapturedActorsWidget)`
- L15 _public function_ `SLATE_ARGUMENT(const TArray<UObject*>*, Actors) SLATE_END_ARGS() SCapturedActorsWidget()`
- L22 _public prototype_ `~SCapturedActorsWidget() = default;`
- L24 _public prototype_ `void Construct(const FArguments& InArgs);`
- L25 _public prototype_ `TArray<UObject*> GetCurrentCheckedActors();`
- L29 _protected prototype_ `TSharedRef<ITableRow> MakeRow(UObject* Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L31 _protected member_ `TArray<UObject*> AllActors;`
- L32 _protected member_ `TMap<UObject*, bool> ActorChecked;`

### `Plugins/Enterprise/VariantManager/Source/VariantManager/Private/Dialogs/SCapturedActorsWidgetTwo.h` (Private)


#### class `SCapturedActorsWidgetTwo`  
`class SCapturedActorsWidgetTwo : public SCapturedActorsWidget`  
_L13-28_
- inherits: `SCapturedActorsWidget`
- L16 _public function_ `SLATE_BEGIN_ARGS(SCapturedActorsWidgetTwo)`
- L17 _public prototype_ `SLATE_ARGUMENT(const TArray<UObject*>*, Actors) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L24 _private prototype_ `TSharedRef<ITableRow> MakeRow(UObject* Item, const TSharedRef<STableViewBase>& OwnerTable) const;`
- L25 _private prototype_ `void OnSelectionChanged(UObject* Object, ESelectInfo::Type SelectType);`
- L27 _private member_ `TSharedPtr<SListView<UObject*>> ActorListView;`

### `Plugins/Enterprise/VariantManager/Source/VariantManager/Private/Dialogs/SCapturedPropertiesWidget.h` (Private)


#### class `SCapturedPropertiesWidgetBase`  
`class SCapturedPropertiesWidgetBase : public SCompoundWidget`  
_L13-18_
- inherits: `SCompoundWidget`
- L16 _public prototype_ `virtual TArray<TSharedPtr<FCapturableProperty>> GetCurrentCheckedProperties() = 0;`
- L17 _public prototype_ `virtual void FilterPropertyPaths(const FText& Filter) = 0;`

#### class `SCapturedPropertiesWidget`  
`class SCapturedPropertiesWidget : public SCapturedPropertiesWidgetBase`  
_L20-45_
- inherits: `SCapturedPropertiesWidgetBase`
- L23 _public function_ `SLATE_BEGIN_ARGS(SCapturedPropertiesWidget)`
- L24 _public function_ `SLATE_ARGUMENT(TArray<TSharedPtr<FCapturableProperty>>*, PropertyPaths) SLATE_END_ARGS() SCapturedPropertiesWidget()`
- L31 _public prototype_ `~SCapturedPropertiesWidget() = default;`
- L33 _public prototype_ `void Construct(const FArguments& InArgs);`
- L34 _public prototype_ `virtual TArray<TSharedPtr<FCapturableProperty>> GetCurrentCheckedProperties() override;`
- L35 _public prototype_ `virtual void FilterPropertyPaths(const FText& Filter) override;`
- L39 _private prototype_ `TSharedRef<ITableRow> MakeCapturedPropertyWidget(TSharedPtr<FCapturableProperty> Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L41 _private member_ `TArray<TSharedPtr<FCapturableProperty>> CapturedProperties;`
- L43 _private member_ `TSharedPtr<SListView<TSharedPtr<FCapturableProperty>>> PropListView;`
- L44 _private member_ `TArray<TSharedPtr<FCapturableProperty>> FilteredCapturedProperties;`

### `Plugins/Enterprise/VariantManager/Source/VariantManager/Private/Dialogs/SCapturedPropertiesWidgetTwo.h` (Private)


#### class `SCapturedPropertiesWidgetTwo`  
`class SCapturedPropertiesWidgetTwo : public SCapturedPropertiesWidgetBase`  
_L17-65_
- inherits: `SCapturedPropertiesWidgetBase`
- L20 _public function_ `SLATE_BEGIN_ARGS(SCapturedPropertiesWidgetTwo)`
- L21 _public prototype_ `SLATE_ARGUMENT(TArray<TSharedPtr<FCapturableProperty>>*, PropertyPaths) SLATE_END_ARGS() virtual ~SCapturedPropertiesWidgetTwo() override;`
- L27 _public prototype_ `void Construct(const FArguments& InArgs);` — Constructs this widget with InArgs
- L30 _public prototype_ `virtual TArray<TSharedPtr<FCapturableProperty>> GetCurrentCheckedProperties() override;`
- L31 _public prototype_ `virtual void FilterPropertyPaths(const FText& Filter) override;`
- L33 _public prototype_ `void SetFavorite(const TSharedPtr<FCapturableProperty>& Property, bool bFavorite);`
- L34 _public prototype_ `void SaveFavorites() const;`
- L37 _private prototype_ `EColumnSortMode::Type GetSortMode(const FName ColumnName) const;`
- L38 _private prototype_ `EColumnSortPriority::Type GetSortPriority(FName ColumnName) const;`
- L39 _private prototype_ `void HandleSort(const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type NewSortMode);`
- L40 _private prototype_ `void SortItems();`
- L42 _private prototype_ `void AddFilters();`
- L43 _private prototype_ `void OnFilterChanged();`
- L45 _private prototype_ `void LoadAndMarkFavorites();`
- L48 _private prototype_ `TSharedRef<ITableRow> MakeCapturedPropertyWidget(TSharedPtr<FCapturableProperty> Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L50 _private member_ `TArray<TSharedPtr<FCapturableProperty>> CapturedProperties;`
- L52 _private member_ `TSharedPtr<SListView<TSharedPtr<FCapturableProperty>>> PropListView;`
- L53 _private member_ `TSharedPtr<SBasicFilterBar<TSharedPtr<FCapturableProperty>>> FilterBar;`
- L55 _private member_ `TArray<TSharedPtr<FCapturableProperty>> FilteredCapturedProperties;`
- L56 _private member_ `TArray<TSharedRef<FFilterBase<TSharedPtr<FCapturableProperty>>>> Filters;`
- L58 _private member_ `TSet<FName> FavoriteProperties;`
- L60 _private member_ `TAttribute<FText> HighlightText;`
- L62 _private member_ `EColumnSortMode::Type SortMode = EColumnSortMode::Ascending;`
- L63 _private member_ `EColumnSortPriority::Type SortPriority = EColumnSortPriority::Primary;`
- L64 _private member_ `FName SortColumn;`

### `Plugins/Enterprise/VariantManager/Source/VariantManager/Private/Dialogs/SEditFunctionCallerArgumentsDialog.h` (Private)


#### class `UEditFunctionCallerArguments`  
`class UEditFunctionCallerArguments : public UObject`  
_L14-24_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Object representation for function caller arguments editing (with IDetailsView)
- L20 _public member_ `FName FunctionName;` — `UPROPERTY(VisibleAnywhere, Category="Function Caller")`
- L23 _public member_ `TMap<FName, FString> Arguments;` — `UPROPERTY(EditAnywhere, Category="Function Caller")`

#### class `SEditFunctionCallerArgumentsDialog`  
`class SEditFunctionCallerArgumentsDialog : public SWindow`  
_L29-58_
- inherits: `SWindow`
- desc: Dialog for editing function caller arguments
- L32 _public function_ `SLATE_BEGIN_ARGS(SEditFunctionCallerArgumentsDialog)`
- L36 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FName& InFunctionName, const TMap<FName, FString>& InFunctionArguments);`
- L42 _public prototype_ `static TSharedPtr<SEditFunctionCallerArgumentsDialog> OpenDialogAsModalWindow(const FName& FunctionName, const TMap<FName, FString>& Arguments);`
- L45 _public function_ `bool GetUserAccepted() const`
- L47 _public prototype_ `TMap<FName, FString> GetFunctionArguments() const;`
- L50 _private prototype_ `FReply OnDialogConfirmed();`
- L51 _private prototype_ `FReply OnDialogCanceled();`
- L54 _private member_ `TSharedPtr<class IDetailsView> PropertyView;`
- L55 _private member_ `TStrongObjectPtr<UEditFunctionCallerArguments> CallerArguments;`
- L57 _private member_ `bool bUserAccepted = false;`

### `Plugins/Enterprise/VariantManager/Source/VariantManager/Private/DisplayNodes/VariantManagerActorNode.h` (Private)


#### class `FVariantManagerActorNode`  
`class FVariantManagerActorNode : public FVariantManagerDisplayNode`  
_L18-57_
- inherits: `FVariantManagerDisplayNode`
- desc: A node for displaying an object binding
- L21 _public prototype_ `FVariantManagerActorNode(UVariantObjectBinding* InObjectBinding, TSharedPtr<FVariantManagerDisplayNode> InParentNode, TWeakPtr<FVariantManager> InVariantManager);`
- L24 _public prototype_ `TWeakObjectPtr<UVariantObjectBinding> GetObjectBinding() const;` — Gets the UVariantObjectBinding held by this actor node
- L27 _public prototype_ `virtual void BuildContextMenu(FMenuBuilder& MenuBuilder) override;`
- L28 _public prototype_ `virtual FText GetDisplayNameToolTipText() const override;`
- L29 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L30 _public prototype_ `virtual const FSlateBrush* GetIconOverlayBrush() const override;`
- L31 _public prototype_ `virtual EVariantManagerNodeType GetType() const override;`
- L32 _public prototype_ `virtual FText GetDisplayName() const override;`
- L33 _public prototype_ `virtual FSlateColor GetDisplayNameColor() const override;`
- L34 _public prototype_ `virtual void SetDisplayName(const FText& NewDisplayName) override;`
- L35 _public prototype_ `virtual bool IsSelectable() const override;`
- L36 _public prototype_ `virtual bool CanDrag() const override;`
- L37 _public prototype_ `virtual TWeakPtr<FVariantManager> GetVariantManager() const override;`
- L38 _public prototype_ `virtual TOptional<EItemDropZone> CanDrop(const FDragDropEvent& DragDropEvent, EItemDropZone ItemDropZone) const override;`
- L39 _public prototype_ `virtual void Drop(const FDragDropEvent& DragDropEvent, EItemDropZone ItemDropZone) override;`
- L40 _public prototype_ `virtual TSharedRef<SWidget> GetCustomOutlinerContent(TSharedPtr<SVariantManagerTableRow> InTableRow) override;`
- L45 _private prototype_ `FText GetRebindToSelectedTooltip() const;` — Gets the tooltip to show on the 'RebindToSelected' button
- L48 _private prototype_ `const UClass* GetClassForObjectBinding() const;` — Gets the class of the UObject that is bound to our ObjectBinding, or nullptr
- L51 _private prototype_ `void AddAssignActorSubMenu(FMenuBuilder& MenuBuilder);` — Creates the floating submenu that is shown when mousing over the "Rebind to other actor" right-click option
- L53 _private member_ `TWeakObjectPtr<UVariantObjectBinding> ObjectBinding;`
- L54 _private member_ `mutable FText OldDisplayText;`
- L55 _private member_ `FText DefaultDisplayName;`
- L56 _private member_ `TWeakPtr<FVariantManager> VariantManager;`

### `Plugins/Enterprise/VariantManager/Source/VariantManager/Private/DisplayNodes/VariantManagerColorPropertyNode.h` (Private)


#### class `FVariantManagerColorPropertyNode`  
`class FVariantManagerColorPropertyNode : public FVariantManagerPropertyNode`  
_L10-25_
- inherits: `FVariantManagerPropertyNode`
- L13 _public prototype_ `FVariantManagerColorPropertyNode(TArray<UPropertyValue*> InPropertyValues, TWeakPtr<FVariantManager> InVariantManager);`
- L16 _protected prototype_ `virtual TSharedPtr<SWidget> GetPropertyValueWidget() override;`
- L19 _private prototype_ `FReply OnClickColorBlock(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L20 _private prototype_ `void OnSetColorFromColorPicker(FLinearColor NewColor);`
- L24 _private member_ `FLinearColor CachedColor = FLinearColor::Black;` — Keep a local cache as applying/recording from UPropertyValues is not free and the SColorBlock reads from this every frame

### `Plugins/Enterprise/VariantManager/Source/VariantManager/Private/DisplayNodes/VariantManagerDisplayNode.h` (Private)


#### enum `EVariantManagerNodeType`  
`enum class EVariantManagerNodeType : uint8`  
_L22-30_
- reflection: `UENUM()`
- L24 _public enumerator_ `VariantSet`
- L25 _public enumerator_ `Variant`
- L26 _public enumerator_ `Actor`
- L27 _public enumerator_ `Property`
- L28 _public enumerator_ `Function`
- L29 _public enumerator_ `Spacer`

#### class `FVariantManagerDisplayNode`  
`class FVariantManagerDisplayNode : public TSharedFromThis<FVariantManagerDisplayNode>`  
_L35-212_
- inherits: `TSharedFromThis<FVariantManagerDisplayNode>`
- desc: Base VariantManager layout node.
- L40 _public prototype_ `FVariantManagerDisplayNode(TSharedPtr<FVariantManagerDisplayNode> InParentNode, TWeakPtr<FVariantManagerNodeTree> InParentTree );`
- L42 _public prototype_ `virtual ~FVariantManagerDisplayNode()= default;`
- L44 _public function_ `virtual EVariantManagerNodeType GetType() const`
- L49 _public function_ `virtual bool IsSelectable() const`
- L54 _public function_ `virtual bool IsReadOnly() const`
- L58 _public function_ `virtual void StartRenaming() const`
- L62 _public function_ `virtual FText GetDisplayName() const`
- L67 _public prototype_ `virtual const FTableRowStyle* GetRowStyle() const;`
- L68 _public prototype_ `virtual FSlateColor GetDisplayNameColor() const;`
- L69 _public prototype_ `virtual FText GetDisplayNameToolTipText() const;`
- L70 _public function_ `virtual void SetDisplayName(const FText& NewDisplayName)`
- L71 _public prototype_ `virtual void HandleNodeLabelTextChanged(const FText& NewLabel, ETextCommit::Type CommitType);`
- L73 _public function_ `virtual bool IsResizable() const`
- L77 _public function_ `virtual void Resize(float NewSize)`
- L82 _public prototype_ `virtual FReply OnDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent);`
- L84 _public prototype_ `virtual TSharedRef<SWidget> GetCustomOutlinerContent(TSharedPtr<SVariantManagerTableRow> InTableRow);`
- L86 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const;`
- L87 _public prototype_ `virtual const FSlateBrush* GetIconOverlayBrush() const;`
- L88 _public prototype_ `virtual FSlateColor GetIconColor() const;`
- L89 _public prototype_ `virtual FText GetIconToolTipText() const;`
- L90 _public prototype_ `virtual const FSlateBrush* GetNodeBorderImage() const;`
- L91 _public prototype_ `virtual void BuildContextMenu(FMenuBuilder& MenuBuilder);`
- L93 _public function_ `uint32 GetNumChildren() const`
- L97 _public function_ `const TArray<TSharedRef<FVariantManagerDisplayNode>>& GetChildNodes() const`
- L101 _public function_ `void AddChild(TSharedRef<FVariantManagerDisplayNode> NewChild)`
- L107 _public function_ `template <class PREDICATE_CLASS> void SortChildNodes(const PREDICATE_CLASS& Predicate)`
- L116 _public function_ `TSharedPtr<FVariantManagerDisplayNode> GetParent() const`
- L120 _public function_ `void SetParent(TSharedPtr<FVariantManagerDisplayNode> NewParent)`
- L124 _public function_ `TSharedRef<FVariantManagerDisplayNode> GetOutermostParent()`
- L130 _public prototype_ `virtual TWeakPtr<FVariantManager> GetVariantManager() const;`
- L132 _public function_ `TWeakPtr<FVariantManagerNodeTree> GetParentTree() const`
- L137 _public prototype_ `virtual void SetExpansionState(bool bInExpanded);`
- L138 _public prototype_ `bool IsExpanded() const;`
- L139 _public prototype_ `bool IsHidden() const;`
- L140 _public prototype_ `bool IsHovered() const;`
- L141 _public function_ `bool IsSelected() const`
- L146 _public function_ `void SetSelected(bool bShouldBeSelected)`
- L151 _public function_ `float GetVirtualTop() const`
- L155 _public function_ `float GetVirtualBottom() const`
- L160 _public prototype_ `DECLARE_EVENT(FVariantManagerDisplayNode, FRequestRenameEvent);`
- L161 _public function_ `FRequestRenameEvent& OnRenameRequested()`
- L163 _public function_ `virtual bool CanDrag() const`
- L167 _public function_ `virtual TOptional<EItemDropZone> CanDrop(const FDragDropEvent& DragDropEvent, EItemDropZone ItemDropZone) const`
- L171 _public function_ `virtual void Drop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone)`
- L178 _private prototype_ `void HandleContextMenuRenameNodeExecute();` — Callback for executing a "Rename Node" context menu action.
- L181 _private prototype_ `bool HandleContextMenuRenameNodeCanExecute() const;` — Callback for determining whether a "Rename Node" context menu action can execute.
- L185 _protected member_ `float VirtualTop;` — The virtual offset of this item from the top of the tree, irrespective of expansion states.
- L188 _protected member_ `float VirtualBottom;` — The virtual offset + virtual height of this item, irrespective of expansion states.
- L191 _protected member_ `TWeakPtr<FVariantManagerDisplayNode> ParentNode;` — The parent of this node
- L194 _protected member_ `TArray<TSharedRef<FVariantManagerDisplayNode>> ChildNodes;` — List of children belonging to this node
- L197 _protected member_ `TWeakPtr<FVariantManagerNodeTree> ParentTree;` — Parent tree that this node is in
- L200 _protected member_ `TSharedPtr<SInlineEditableTextBlock> EditableLabel;` — Holds the editable text label widget.
- L203 _protected member_ `bool bExpanded;` — Whether or not the node is expanded
- L205 _protected member_ `bool bSelected;`
- L208 _protected member_ `FRequestRenameEvent RenameRequestedEvent;` — Event that is triggered when rename is requested
- L211 _protected member_ `const FSlateBrush* BackgroundBrush;` — Default background brush for this node when expanded

#### Free symbols / members of external scopes

- L160 _delegate_ `DECLARE_EVENT(FVariantManagerDisplayNode, FRequestRenameEvent);`

### `Plugins/Enterprise/VariantManager/Source/VariantManager/Private/DisplayNodes/VariantManagerEnumPropertyNode.h` (Private)


#### class `FVariantManagerEnumPropertyNode`  
`class FVariantManagerEnumPropertyNode : public FVariantManagerPropertyNode`  
_L11-29_
- inherits: `FVariantManagerPropertyNode`
- L14 _public prototype_ `FVariantManagerEnumPropertyNode(TArray<UPropertyValue*> InPropertyValues, TWeakPtr<FVariantManager> InVariantManager);`
- L17 _protected prototype_ `virtual TSharedPtr<SWidget> GetPropertyValueWidget() override;`
- L20 _private prototype_ `void OnComboboxSelectionChanged(TSharedPtr<FString> NewItem, ESelectInfo::Type SelectType);`
- L21 _private prototype_ `FText GetRecordedEnumDisplayText(bool bSameValue) const;`
- L22 _private prototype_ `void UpdateComboboxStrings();`
- L24 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> Combobox;`
- L26 _private member_ `TArray<TSharedPtr<FString>> EnumDisplayTexts;`
- L27 _private member_ `TArray<TSharedPtr<SToolTip>> EnumRichToolTips;`
- L28 _private member_ `TArray<int32> EnumIndices;`

### `Plugins/Enterprise/VariantManager/Source/VariantManager/Private/DisplayNodes/VariantManagerFunctionPropertyNode.h` (Private)


#### class `FVariantManagerFunctionPropertyNode`  
`class FVariantManagerFunctionPropertyNode : public FVariantManagerPropertyNode`  
_L16-93_
- inherits: `FVariantManagerPropertyNode`
- L21 _public prototype_ `FVariantManagerFunctionPropertyNode(TWeakObjectPtr<UVariantObjectBinding> InObjectBinding, FFunctionCaller& InCaller, TWeakPtr<FVariantManager> InVariantManager);`
- L24 _public prototype_ `virtual EVariantManagerNodeType GetType() const override;` — FVariantManagerDisplayNode interface
- L25 _public prototype_ `virtual void BuildContextMenu(FMenuBuilder& MenuBuilder) override;`
- L26 _public prototype_ `virtual FText GetDisplayName() const override;`
- L27 _public prototype_ `virtual FText GetDisplayNameToolTipText() const override;`
- L30 _public prototype_ `TWeakObjectPtr<UVariantObjectBinding> GetObjectBinding() const;`
- L31 _public prototype_ `FFunctionCaller& GetFunctionCaller() const;`
- L36 _public prototype_ `virtual uint32 GetDisplayOrder() const override;` — Get the order with which the VariantManager should display this in a property list. Lower values will be shown higher up
- L41 _public prototype_ `virtual void SetDisplayOrder(uint32 InDisplayOrder) override;` — Set the order with which the VariantManager should display this in a property list. Lower values will be shown higher up
- L46 _private prototype_ `void SetBindingTargetFunction(UK2Node_FunctionEntry* NewFunctionEntry);` — Set the target function as the selected option both for this node as well as for the underlying binding
- L49 _private prototype_ `void CreateDirectorFunction(ULevelVariantSets* InLevelVariantSets, UClass* PinClassType);` — Create a new blank director function
- L51 _private prototype_ `void CreateDirectorFunctionFromFunction(UFunction* QuickBindFunction, UClass* PinClassType);`
- L54 _private prototype_ `void NavigateToDefinition();` — Navigate to the function whose name is FunctionName
- L57 _private prototype_ `TSharedRef<SWidget> GetMenuContent();` — Generate the drop down menu
- L60 _private prototype_ `void PopulateQuickBindSubMenu(FMenuBuilder& MenuBuilder, UClass* TemplateClass);` — Populate the menu builder with entries according to UClass' functions
- L63 _private prototype_ `const FSlateBrush* GetFunctionIcon() const;` — Get the icon to display on the main combo button
- L68 _protected prototype_ `virtual FReply ResetMultipleValuesToDefault() override;` — Reset recorded data of all property values to nullptr
- L71 _protected function_ `virtual FReply RecordMultipleValues() override` — Disable this function as we don't have any properties to record with
- L74 _protected prototype_ `virtual bool PropertiesHaveSameValue() const override;` — Returns true if all properties have the exact same value bytes
- L77 _protected prototype_ `virtual bool PropertiesHaveDefaultValue() const override;` — Returns true if all properties have the exact same value bytes as the CDO
- L80 _protected function_ `virtual bool PropertiesHaveCurrentValue() const override` — Disable this function as we don't have any properties
- L83 _protected prototype_ `virtual TSharedPtr<SWidget> GetPropertyValueWidget() override;` — Generate the widget for the entire row
- L86 _protected prototype_ `void OnEditArguments();` — Opens Edit Arguments dialog
- L89 _protected prototype_ `FText GetFunctionArgumentsTooltipText() const;` — Formats supplied function arguments into tooltip text
- L91 _protected member_ `TWeakObjectPtr<UVariantObjectBinding> ObjectBinding;`
- L92 _protected member_ `FFunctionCaller& FunctionCaller;`

### `Plugins/Enterprise/VariantManager/Source/VariantManager/Private/DisplayNodes/VariantManagerOptionPropertyNode.h` (Private)


#### class `FVariantManagerOptionPropertyNode`  
`class FVariantManagerOptionPropertyNode : public FVariantManagerPropertyNode`  
_L11-29_
- inherits: `FVariantManagerPropertyNode`
- desc: Display node made to interact with SwitchActor and UPropertyValueOption
- L14 _public prototype_ `FVariantManagerOptionPropertyNode(TArray<UPropertyValue*> InPropertyValues, TWeakPtr<FVariantManager> InVariantManager);`
- L15 _public prototype_ `virtual FText GetDisplayNameToolTipText() const override;`
- L18 _protected prototype_ `virtual TSharedPtr<SWidget> GetPropertyValueWidget() override;`
- L21 _private prototype_ `ASwitchActor* GetSwitchActor();`
- L23 _private prototype_ `void OnComboBoxOpening();`
- L24 _private prototype_ `void OnComboBoxOptionChanged(TSharedPtr<FString> NewOption, ESelectInfo::Type SelectType);`
- L25 _private prototype_ `FText GetComboBoxSelectedOptionText() const;`
- L27 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> ComboBox;`
- L28 _private member_ `TArray<TSharedPtr<FString>> Options;`

### `Plugins/Enterprise/VariantManager/Source/VariantManager/Private/DisplayNodes/VariantManagerPropertyNode.h` (Private)


#### class `FVariantManagerPropertyNode`  
`class FVariantManagerPropertyNode : public FVariantManagerDisplayNode`  
_L19-131_
- inherits: `FVariantManagerDisplayNode`
- L24 _public prototype_ `FVariantManagerPropertyNode(TArray<UPropertyValue*> InPropertyValues, TWeakPtr<FVariantManager> InVariantManager);`
- L26 _public function_ `const TArray<TWeakObjectPtr<UPropertyValue>>& GetPropertyValues() const`
- L32 _public prototype_ `virtual void BuildContextMenu(FMenuBuilder& MenuBuilder) override;` — FVariantManagerDisplayNode interface
- L33 _public prototype_ `virtual FText GetDisplayNameToolTipText() const override;`
- L34 _public prototype_ `virtual const FSlateBrush* GetIconOverlayBrush() const override;`
- L35 _public prototype_ `virtual FText GetIconToolTipText() const override;`
- L36 _public prototype_ `virtual EVariantManagerNodeType GetType() const override;`
- L37 _public prototype_ `virtual bool IsReadOnly() const override;`
- L38 _public prototype_ `virtual FText GetDisplayName() const override;`
- L39 _public prototype_ `virtual void SetDisplayName(const FText& NewDisplayName) override;`
- L40 _public prototype_ `virtual bool IsSelectable() const override;`
- L41 _public function_ `virtual bool CanDrag() const override`
- L42 _public prototype_ `virtual TOptional<EItemDropZone> CanDrop(const FDragDropEvent& DragDropEvent, EItemDropZone ItemDropZone) const override;`
- L43 _public prototype_ `virtual void Drop(const FDragDropEvent& DragDropEvent, EItemDropZone ItemDropZone) override;`
- L44 _public function_ `virtual TWeakPtr<FVariantManager> GetVariantManager() const override`
- L53 _public prototype_ `virtual TSharedRef<SWidget> GetCustomOutlinerContent(TSharedPtr<SVariantManagerTableRow> InTableRow) override;` — Full outliner content for this property node. This includes name, splitter and value content.
- L58 _public prototype_ `virtual TSharedRef<SWidget> GetCustomValueContent();` — Just value content for this property node.
- L63 _public prototype_ `virtual uint32 GetDisplayOrder() const;` — Get the order with which the VariantManager should display this in a property list. Lower values will be shown higher up
- L68 _public prototype_ `virtual void SetDisplayOrder(uint32 InDisplayOrder);` — Set the order with which the VariantManager should display this in a property list. Lower values will be shown higher up
- L73 _public prototype_ `bool IsActorProperty() const;` — Flag if this is an Actor or Actor Component property.
- L78 _public prototype_ `FString GetSubPath() const;` — Path without the property name
- L83 _public prototype_ `FString GetPropertyName() const;` — Name of the property (last part of the path)
- L88 _protected prototype_ `virtual void UpdateRecordedDataFromSinglePropView(TSharedPtr<ISinglePropertyView> SinglePropView);` — Callback for when user updates the property widget
- L91 _protected prototype_ `virtual FReply ResetMultipleValuesToDefault();` — Reset recorded data of all property values to the CDO value
- L94 _protected prototype_ `virtual FReply RecordMultipleValues();` — Reset recorded data from all property values
- L97 _protected prototype_ `virtual bool PropertiesHaveSameValue() const;` — Returns true if all properties have the exact same value bytes
- L100 _protected prototype_ `virtual bool PropertiesHaveDefaultValue() const;` — Returns true if all properties have the exact same value bytes as the CDO
- L104 _protected prototype_ `virtual bool PropertiesHaveCurrentValue() const;` — Returns true if all UPropertyValues have recorded data that matches the current value of the properties they are tracking
- L107 _protected prototype_ `TSharedRef<SWidget> GetMultipleValuesWidget();` — Returns a widget that is displayed when PropertyValues have different recorded data
- L110 _protected prototype_ `TSharedRef<SWidget> GetFailedToResolveWidget(const UPropertyValue* Property);` — Returns a widget that is displayed when we fail to resolve PropertyValues
- L112 _protected prototype_ `bool RecursiveDisableOldResetButton(TSharedPtr<SWidget> Widget);`
- L114 _protected prototype_ `EVisibility GetResetButtonVisibility() const;`
- L115 _protected prototype_ `EVisibility GetRecordButtonVisibility() const;`
- L117 _protected prototype_ `virtual TSharedPtr<SWidget> GetPropertyValueWidget();`
- L119 _protected member_ `TSharedPtr<SButton> ResetButton;`
- L120 _protected member_ `TSharedPtr<SButton> RecordButton;`
- L122 _protected member_ `TStrongObjectPtr<UPropertyTemplateObject> SinglePropertyViewTemplate;`
- L124 _protected member_ `TMap<TWeakObjectPtr<UPropertyValue>, FDelegateHandle> PropertyValueOnRecordedSubscriptions;`
- L126 _protected member_ `TArray<TWeakObjectPtr<UPropertyValue>> PropertyValues;`
- L128 _protected member_ `FText DefaultDisplayName;`
- L130 _protected member_ `TWeakPtr<FVariantManager> VariantManager;`

### `Plugins/Enterprise/VariantManager/Source/VariantManager/Private/DisplayNodes/VariantManagerStringPropertyNode.h` (Private)


#### class `FVariantManagerStringPropertyNode`  
`class FVariantManagerStringPropertyNode : public FVariantManagerPropertyNode`  
_L20-33_
- inherits: `FVariantManagerPropertyNode`
- desc: Accesses FString, FText and FName UPropertyValues in a different way by actually taking copies to their objects and using SetValue on property handles. This is necessary for safety and to decouple the variant's stored object from the displayed object (and details view). This happens for these types only because they are the only base types that are reference types and basically handles to heap data stored elsewhere. Because of that we can't just blindly copy their bytes around, but *must* use the actual objects so that we trigger the copy constructors and serialization functions, properly caring for the data they handle
- L25 _public prototype_ `FVariantManagerStringPropertyNode(TArray<UPropertyValue*> InPropertyValues, TWeakPtr<FVariantManager> InVariantManager);`
- L29 _protected prototype_ `virtual TSharedPtr<SWidget> GetPropertyValueWidget() override;`
- L32 _protected prototype_ `virtual void UpdateRecordedDataFromSinglePropView(TSharedPtr<ISinglePropertyView> SinglePropView) override;` — Callback for when user updates the property widget

### `Plugins/Enterprise/VariantManager/Source/VariantManager/Private/DisplayNodes/VariantManagerStructPropertyNode.h` (Private)


#### class `FVariantManagerStructPropertyNode`  
`class FVariantManagerStructPropertyNode : public FVariantManagerPropertyNode`  
_L11-59_
- inherits: `FVariantManagerPropertyNode`
- L16 _public prototype_ `FVariantManagerStructPropertyNode(TArray<UPropertyValue*> InPropertyValues, TWeakPtr<FVariantManager> InVariantManager);`
- L20 _protected prototype_ `virtual TSharedPtr<SWidget> GetPropertyValueWidget() override;`
- L24 _private prototype_ `void OnFloatPropCommitted(double InValue, ETextCommit::Type InCommitType, FNumericProperty* Prop, int32 RecordedElementSize, int32 Offset);`
- L25 _private prototype_ `void OnSignedPropCommitted(int64 InValue, ETextCommit::Type InCommitType, FNumericProperty* Prop, int32 Offset);`
- L26 _private prototype_ `void OnUnsignedPropCommitted(uint64 InValue, ETextCommit::Type InCommitType, FNumericProperty* Prop, int32 Offset);`
- L28 _private prototype_ `TOptional<double> GetFloatValueFromPropertyValue(FNumericProperty* Prop, int32 RecordedElementSize, int32 Offset) const;`
- L29 _private prototype_ `TOptional<int64> GetSignedValueFromPropertyValue(FNumericProperty* Prop, int32 Offset) const;`
- L30 _private prototype_ `TOptional<uint64> GetUnsignedValueFromPropertyValue(FNumericProperty* Prop, int32 Offset) const;`
- L32 _private prototype_ `TOptional<double> GetFloatValueFromCache(FNumericProperty* Prop) const;`
- L33 _private prototype_ `TOptional<int64> GetSignedValueFromCache(FNumericProperty* Prop) const;`
- L34 _private prototype_ `TOptional<uint64> GetUnsignedValueFromCache(FNumericProperty* Prop) const;`
- L36 _private prototype_ `void OnBeginSliderMovement(FNumericProperty* Prop);`
- L38 _private prototype_ `void OnFloatEndSliderMovement(double LastValue, FNumericProperty* Prop, int32 RecordedElementSize, int32 Offset);`
- L39 _private prototype_ `void OnSignedEndSliderMovement(int64 LastValue, FNumericProperty* Prop, int32 Offset);`
- L40 _private prototype_ `void OnUnsignedEndSliderMovement(uint64 LastValue, FNumericProperty* Prop, int32 Offset);`
- L42 _private prototype_ `void OnFloatValueChanged(double NewValue, FNumericProperty* Prop);`
- L43 _private prototype_ `void OnSignedValueChanged(int64 NewValue, FNumericProperty* Prop);`
- L44 _private prototype_ `void OnUnsignedValueChanged(uint64 NewValue, FNumericProperty* Prop);`
- L47 _private prototype_ `template <typename F> TSharedRef<SWidget> GenerateFloatEntryBox(FNumericProperty* Prop, int32 RecordedElementSize, int32 Offset);`
- L49 _private prototype_ `template <typename S> TSharedRef<SWidget> GenerateSignedEntryBox(FNumericProperty* Prop, int32 Offset);`
- L51 _private prototype_ `template <typename U> TSharedRef<SWidget> GenerateUnsignedEntryBox(FNumericProperty* Prop, int32 Offset);`
- L53 _private member_ `bool bIsUsingSlider = false;`
- L56 _private member_ `TMap<FNumericProperty*, TOptional<double>> FloatValues;` — Cached values to be used for GetXValue and OnXValueChanged
- L57 _private member_ `TMap<FNumericProperty*, TOptional<int64>> SignedValues;`
- L58 _private member_ `TMap<FNumericProperty*, TOptional<uint64>> UnsignedValues;`

### `Plugins/Enterprise/VariantManager/Source/VariantManager/Private/DisplayNodes/VariantManagerVariantNode.h` (Private)


#### class `FVariantManagerVariantNode`  
`class FVariantManagerVariantNode : public FVariantManagerDisplayNode`  
_L19-58_
- inherits: `FVariantManagerDisplayNode`
- desc: A variant manager display node representing a variant in the outliner.
- L22 _public prototype_ `FVariantManagerVariantNode( UVariant& InVariant, TSharedPtr<FVariantManagerDisplayNode> InParentNode, TWeakPtr<FVariantManagerNodeTree> InParentTree );`
- L25 _public prototype_ `virtual FReply OnDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;` — FVariantManagerDisplayNode interface
- L26 _public prototype_ `virtual TSharedRef<SWidget> GetCustomOutlinerContent(TSharedPtr<SVariantManagerTableRow> InTableRow) override;`
- L27 _public prototype_ `virtual EVariantManagerNodeType GetType() const override;`
- L28 _public prototype_ `virtual bool IsReadOnly() const override;`
- L29 _public prototype_ `virtual FText GetDisplayName() const override;`
- L30 _public prototype_ `virtual void SetDisplayName( const FText& NewDisplayName ) override;`
- L31 _public prototype_ `virtual void HandleNodeLabelTextChanged(const FText& NewLabel, ETextCommit::Type CommitType) override;`
- L32 _public prototype_ `virtual bool IsSelectable() const override;`
- L33 _public prototype_ `virtual bool CanDrag() const override;`
- L34 _public prototype_ `virtual TOptional<EItemDropZone> CanDrop(const FDragDropEvent& DragDropEvent, EItemDropZone ItemDropZone) const override;`
- L35 _public prototype_ `virtual void Drop(const FDragDropEvent& DragDropEvent, EItemDropZone ItemDropZone) override;`
- L36 _public prototype_ `virtual void BuildContextMenu(FMenuBuilder& MenuBuilder) override;`
- L40 _public prototype_ `UVariant& GetVariant() const;` — Gets the folder data for this display node.
- L41 _public prototype_ `TSharedRef<SWidget> GetThumbnailWidget();`
- L44 _private prototype_ `bool AreAssetsAcceptableForDrop(TArrayView<FAssetData> AssetDatas) const;`
- L45 _private prototype_ `void HandleAssetsDropped(const FDragDropEvent& DragDropEvent, TArrayView<FAssetData> AssetDatas);`
- L49 _private prototype_ `ECheckBoxState IsRadioButtonChecked() const;`
- L50 _private prototype_ `void OnRadioButtonStateChanged(ECheckBoxState NewState);`
- L52 _private member_ `UVariant& Variant;`
- L54 _private member_ `TSharedPtr<SCheckBox> RadioButton;`
- L57 _private member_ `TSharedPtr<FSlateImageBrush> ImageBrush;` — We need to keep the brush alive while the thumbnail is rendered

### `Plugins/Enterprise/VariantManager/Source/VariantManager/Private/DisplayNodes/VariantManagerVariantSetNode.h` (Private)


#### class `FVariantManagerVariantSetNode`  
`class FVariantManagerVariantSetNode : public FVariantManagerDisplayNode`  
_L17-61_
- inherits: `FVariantManagerDisplayNode`
- desc: A variant manager display node representing a variant set in the outliner.
- L20 _public prototype_ `FVariantManagerVariantSetNode( UVariantSet& InVariantSet, TSharedPtr<FVariantManagerDisplayNode> InParentNode, TWeakPtr<FVariantManagerNodeTree> InParentTree );`
- L23 _public prototype_ `virtual const FTableRowStyle* GetRowStyle() const override;` — FVariantManagerDisplayNode interface
- L24 _public prototype_ `virtual EVariantManagerNodeType GetType() const override;`
- L25 _public prototype_ `virtual bool IsReadOnly() const override;`
- L26 _public prototype_ `virtual FText GetDisplayName() const override;`
- L27 _public prototype_ `virtual void SetDisplayName( const FText& NewDisplayName ) override;`
- L28 _public prototype_ `virtual void HandleNodeLabelTextChanged(const FText& NewLabel, ETextCommit::Type CommitType) override;`
- L29 _public prototype_ `virtual bool IsSelectable() const override;`
- L30 _public prototype_ `virtual bool CanDrag() const override;`
- L31 _public prototype_ `virtual TOptional<EItemDropZone> CanDrop(const FDragDropEvent& DragDropEvent, EItemDropZone ItemDropZone) const override;`
- L32 _public prototype_ `virtual void Drop(const FDragDropEvent& DragDropEvent, EItemDropZone ItemDropZone) override;`
- L33 _public prototype_ `virtual void BuildContextMenu(FMenuBuilder& MenuBuilder) override;`
- L34 _public prototype_ `virtual const FSlateBrush* GetNodeBorderImage() const override;`
- L35 _public prototype_ `virtual TSharedRef<SWidget> GetCustomOutlinerContent(TSharedPtr<SVariantManagerTableRow> InTableRow) override;`
- L36 _public prototype_ `TSharedRef<SWidget> GetThumbnailWidget();`
- L37 _public prototype_ `virtual void SetExpansionState(bool bInExpanded) override;`
- L40 _public prototype_ `UVariantSet& GetVariantSet() const;` — Gets the folder data for this display node.
- L43 _private prototype_ `bool AreAssetsAcceptableForDrop(TArrayView<FAssetData> AssetDatas) const;`
- L44 _private prototype_ `void HandleAssetsDropped(const FDragDropEvent& DragDropEvent, TArrayView<FAssetData> AssetDatas);`
- L49 _private member_ `UVariantSet& VariantSet;` — The movie scene folder data which this node represents.
- L51 _private member_ `FTableRowStyle RowStyle;`
- L54 _private member_ `const FSlateBrush* ExpandedBackgroundBrush;` — Different brushes so that the edges look good when expanded and collapsed
- L55 _private member_ `const FSlateBrush* CollapsedBackgroundBrush;`
- L57 _private member_ `TSharedPtr<FAssetThumbnailPool> ThumbnailPool;`
- L60 _private member_ `TSharedPtr<FSlateBrush> ImageBrush;` — We need to keep the brush alive while the thumbnail is rendered

### `Plugins/Enterprise/VariantManager/Source/VariantManager/Private/LevelVariantSetsEditorToolkit.h` (Private)


#### class `FLevelVariantSetsEditorToolkit`  
`class FLevelVariantSetsEditorToolkit : public FAssetEditorToolkit , public FGCObject`  
_L16-63_
- inherits: `FAssetEditorToolkit,FGCObject`
- L22 _public prototype_ `FLevelVariantSetsEditorToolkit();`
- L23 _public prototype_ `virtual ~FLevelVariantSetsEditorToolkit();`
- L25 _public prototype_ `void Initialize(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, ULevelVariantSets* LevelVariantSets);`
- L28 _public function_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override`
- L32 _public function_ `virtual FString GetReferencerName() const override`
- L36 _public prototype_ `virtual bool OnRequestClose(EAssetEditorCloseReason InCloseReason) override;`
- L37 _public prototype_ `virtual bool CanFindInContentBrowser() const override;`
- L38 _public prototype_ `virtual void FocusWindow(UObject* ObjectToFocusOn = nullptr) override;`
- L41 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L42 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L43 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L44 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L48 _public prototype_ `static FName GetVariantManagerTabID();` — Static methods that can be used by the VariantManagerModule to spawn an empty tab when doing Window > Variant Manager. Our regular methods also end up calling these
- L49 _public prototype_ `static FLinearColor GetWorldCentricTabColorScaleStatic();`
- L53 _private prototype_ `static TSharedRef<SDockTab> HandleTabManagerSpawnTab(const FSpawnTabArgs& Args);` — Callback for spawning tabs.
- L56 _private member_ `TObjectPtr<ULevelVariantSets> LevelVariantSets;` — Level sequence for our edit operation.
- L59 _private member_ `TSharedPtr<FVariantManager> VariantManager;` — The VariantManager used by this editor.
- L62 _private member_ `TWeakPtr<SDockTab> CreatedTab;` — Keep track of the tab we create so that we can close it when the asset closes

### `Plugins/Enterprise/VariantManager/Source/VariantManager/Private/PropertyTemplateObject.h` (Private)


#### class `UPropertyTemplateObject`  
`class UPropertyTemplateObject : public UObject`  
_L28-111_
- reflection: `UCLASS(Transient)`
- inherits: `UObject`
- L33 _public function_ `static FName GetPropertyNameFromClass(const FFieldClass* PropertyType)`
- L53 _public member_ `uint8 CapturedByteProperty;` — `UPROPERTY(Transient, EditAnywhere, Category="Template", meta=(ToolTip="Captured byte property"))`
- L56 _public member_ `uint16 CapturedUInt16Property;` — `UPROPERTY(Transient, EditAnywhere, Category="Template", meta=(ToolTip="Captured uint16 property"))`
- L59 _public member_ `uint32 CapturedUInt32Property;` — `UPROPERTY(Transient, EditAnywhere, Category="Template", meta=(ToolTip="Captured uint32 property"))`
- L62 _public member_ `uint64 CapturedUInt64Property;` — `UPROPERTY(Transient, EditAnywhere, Category="Template", meta=(ToolTip="Captured uint16 property"))`
- L65 _public member_ `int8 CapturedInt8Property;` — `UPROPERTY(Transient, EditAnywhere, Category="Template", meta=(ToolTip="Captured int8 property"))`
- L68 _public member_ `int16 CapturedInt16Property;` — `UPROPERTY(Transient, EditAnywhere, Category="Template", meta=(ToolTip="Captured int16 property"))`
- L71 _public member_ `int32 CapturedIntProperty;` — `UPROPERTY(Transient, EditAnywhere, Category="Template", meta=(ToolTip="Captured int32 property"))`
- L74 _public member_ `int64 CapturedInt64Property;` — `UPROPERTY(Transient, EditAnywhere, Category="Template", meta=(ToolTip="Captured int64 property"))`
- L77 _public member_ `float CapturedFloatProperty;` — `UPROPERTY(Transient, EditAnywhere, Category="Template", meta=(ToolTip="Captured float property"))`
- L80 _public member_ `double CapturedDoubleProperty;` — `UPROPERTY(Transient, EditAnywhere, Category="Template", meta=(ToolTip="Captured double property"))`
- L83 _public member_ `bool bCapturedBoolProperty;` — `UPROPERTY(Transient, EditAnywhere, Category="Template", meta=(ToolTip="Captured boolean property"))`
- L86 _public member_ `TObjectPtr<UObject> CapturedObjectProperty;` — `UPROPERTY(Transient, EditAnywhere, Category="Template", meta=(ToolTip="Captured UObject property"))`
- L95 _public member_ `TSoftObjectPtr<UObject> CapturedSoftObjectProperty;` — `UPROPERTY(Transient, EditAnywhere, Category="Template", meta=(ToolTip="Captured Soft UObject property"))`
- L98 _public member_ `FScriptInterface CapturedInterfaceProperty;` — `UPROPERTY(Transient, EditAnywhere, Category="Template", meta=(ToolTip="Captured UInterface property"))`
- L101 _public member_ `FName CapturedNameProperty;` — `UPROPERTY(Transient, EditAnywhere, Category="Template", meta=(ToolTip="Captured FName property"))`
- L104 _public member_ `FString CapturedStrProperty;` — `UPROPERTY(Transient, EditAnywhere, Category="Template", meta=(ToolTip="Captured FString property"))`
- L107 _public member_ `FText CapturedTextProperty;` — `UPROPERTY(Transient, EditAnywhere, Category="Template", meta=(ToolTip="Captured FText property"))`
- L110 _public member_ `FVector CapturedVectorProperty;` — `UPROPERTY(Transient, EditAnywhere, Category="Template", meta=(ToolTip="Captured FVector property"))`

### `Plugins/Enterprise/VariantManager/Source/VariantManager/Private/SDependencyRow.h` (Private)


#### struct `FVariantDependencyModel`  
`struct FVariantDependencyModel : TSharedFromThis<FVariantDependencyModel>`  
_L17-34_
- inherits: `TSharedFromThis<FVariantDependencyModel>`
- desc: Adapter so that we can use arrays of these objects on SListViews and still reference the original Dependency
- L19 _public function_ `FVariantDependencyModel( TWeakObjectPtr<UVariant> InParentVariant, FVariantDependency* InDependency, bool bInIsDependent, bool bInIsDivider) : ParentVariant(InParentVariant) , Dependency(InDependency) , bIsDependent(bInIsDependent) , bIsDivider(bInIsDivider)`
- L30 _public member_ `TWeakObjectPtr<UVariant> ParentVariant;`
- L31 _public member_ `FVariantDependency* Dependency = nullptr;`
- L32 _public member_ `bool bIsDependent = false;`
- L33 _public member_ `bool bIsDivider = false;`

#### class `SDependencyRow`  
`class SDependencyRow : public SMultiColumnTableRow<FVariantDependencyModelPtr>`  
_L38-77_
- inherits: `SMultiColumnTableRow<FVariantDependencyModelPtr>`
- L41 _public function_ `SLATE_BEGIN_ARGS(SDependencyRow)`
- L42 _public prototype_ `SLATE_END_ARGS() static const FName VisibilityColumn;`
- L45 _public member_ `static const FName VariantSetColumn;`
- L46 _public member_ `static const FName VariantColumn;`
- L48 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, FVariantDependencyModelPtr InDependencyModel, bool bInteractionEnabled);`
- L50 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& InColumnName) override;`
- L53 _private prototype_ `void OnSelectedVariantSetChanged(TSharedPtr<FText> NewItem, ESelectInfo::Type SelectType);`
- L54 _private prototype_ `void OnSelectedVariantChanged(TSharedPtr<FText> NewItem, ESelectInfo::Type SelectType);`
- L56 _private prototype_ `FText GetSelectedVariantSetOption() const;`
- L57 _private prototype_ `FText GetSelectedVariantOption() const;`
- L59 _private prototype_ `FText GetDependentVariantSetText() const;`
- L60 _private prototype_ `FText GetDependentVariantText() const;`
- L62 _private prototype_ `void RebuildVariantSetOptions();`
- L63 _private prototype_ `void RebuildVariantOptions();`
- L65 _private prototype_ `FReply OnEnableRowToggled();`
- L66 _private prototype_ `EVisibility OnGetEyeIconVisibility() const;`
- L69 _private member_ `TArray<TSharedPtr<FText>> VariantSetOptions;`
- L70 _private member_ `TArray<TSharedPtr<FText>> VariantOptions;`
- L72 _private member_ `TWeakObjectPtr<UVariant> ParentVariantPtr;`
- L73 _private member_ `FVariantDependency* Dependency = nullptr;`
- L75 _private member_ `bool bIsDivider = false;`
- L76 _private member_ `bool bIsDependent = false;`

#### Free symbols / members of external scopes

- L36 _typedef_ `using FVariantDependencyModelPtr = TSharedPtr<FVariantDependencyModel>;`

### `Plugins/Enterprise/VariantManager/Source/VariantManager/Private/SVariantManager.h` (Private)


#### struct `FSplitterValues`  
`struct FSplitterValues`  
_L40-49_
- desc: Convenience struct to save/load how the user configured the main splitters
- L42 _public member_ `float PropertyNameColumn = 0.5f;`
- L43 _public member_ `float PropertyValueColumn = 0.5f;`
- L44 _public member_ `float VariantColumn = 0.25f;`
- L46 _public function_ `FSplitterValues()`
- L47 _public prototype_ `FSplitterValues(FString& InSerialized);`
- L48 _public prototype_ `FString ToString();`

#### struct `FVariantManagerPropertiesColumnSizeData`  
`struct FVariantManagerPropertiesColumnSizeData`  
_L51-57_
- L53 _public member_ `TAttribute<float> NameColumnWidth;`
- L54 _public member_ `TAttribute<float> ValueColumnWidth;`
- L55 _public member_ `SSplitter::FOnSlotResized OnSplitterNameColumnChanged;`
- L56 _public member_ `SSplitter::FOnSlotResized OnSplitterValueColumnChanged;`

#### class `SVariantManager`  
`class SVariantManager : public SCompoundWidget , public FNotifyHook`  
_L59-339_
- inherits: `SCompoundWidget,FNotifyHook`
- L65 _public function_ `DECLARE_DELEGATE_OneParam(FOnToggleBoolOption, bool) SLATE_BEGIN_ARGS(SVariantManager)`
- L69 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FExtender>, AddMenuExtender) SLATE_ARGUMENT(TSharedPtr<FExtender>, ToolbarExtender) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FVariantManager> InVariantManager);` — Extender to use for the add menu.
- L76 _public prototype_ `~SVariantManager();`
- L78 _public prototype_ `void CreateCommandBindings();`
- L80 _public function_ `TSharedPtr<FUICommandList> GetVariantTreeCommandBindings() const`
- L85 _public function_ `TSharedPtr<FUICommandList> GetActorListCommandBindings() const`
- L90 _public function_ `TSharedPtr<FUICommandList> GetPropertyListCommandBindings() const`
- L96 _public prototype_ `void AddEditorSelectedActorsToVariant();` — Commands
- L97 _public prototype_ `bool CanAddEditorSelectedActorsToVariant();`
- L99 _public prototype_ `void CreateNewVariantSet();`
- L100 _public prototype_ `bool CanCreateNewVariantSet();`
- L102 _public prototype_ `void CutSelectionVariantTree();`
- L103 _public prototype_ `void CopySelectionVariantTree();`
- L104 _public prototype_ `void PasteSelectionVariantTree();`
- L105 _public prototype_ `void DeleteSelectionVariantTree();`
- L106 _public prototype_ `void DuplicateSelectionVariantTree();`
- L107 _public prototype_ `void RenameSelectionVariantTree();`
- L109 _public prototype_ `bool CanCutVariantTree();`
- L110 _public prototype_ `bool CanCopyVariantTree();`
- L111 _public prototype_ `bool CanPasteVariantTree();`
- L112 _public prototype_ `bool CanDeleteVariantTree();`
- L113 _public prototype_ `bool CanDuplicateVariantTree();`
- L114 _public prototype_ `bool CanRenameVariantTree();`
- L116 _public prototype_ `void CutSelectionActorList();`
- L117 _public prototype_ `void CopySelectionActorList();`
- L118 _public prototype_ `void PasteSelectionActorList();`
- L119 _public prototype_ `void DeleteSelectionActorList();`
- L120 _public prototype_ `void DuplicateSelectionActorList();`
- L121 _public prototype_ `void RenameSelectionActorList();`
- L123 _public prototype_ `bool CanCutActorList();`
- L124 _public prototype_ `bool CanCopyActorList();`
- L125 _public prototype_ `bool CanPasteActorList();`
- L126 _public prototype_ `bool CanDeleteActorList();`
- L127 _public prototype_ `bool CanDuplicateActorList();`
- L128 _public prototype_ `bool CanRenameActorList();`
- L130 _public prototype_ `void SwitchOnSelectedVariant();`
- L131 _public prototype_ `void CreateThumbnail();`
- L132 _public prototype_ `void SelectThumbnailAsset();`
- L133 _public prototype_ `void LoadThumbnail();`
- L134 _public prototype_ `void ClearThumbnail();`
- L136 _public prototype_ `bool CanSwitchOnVariant();`
- L137 _public prototype_ `bool CanCreateThumbnail();`
- L138 _public prototype_ `bool CanLoadThumbnail();`
- L139 _public prototype_ `bool CanClearThumbnail();`
- L141 _public prototype_ `void CaptureNewPropertiesFromSelectedActors();`
- L142 _public prototype_ `bool CanCaptureNewPropertiesFromSelectedActors();`
- L144 _public prototype_ `void AddFunctionCaller();`
- L145 _public prototype_ `bool CanAddFunctionCaller();`
- L147 _public prototype_ `void RebindToSelectedActor();`
- L148 _public prototype_ `bool CanRebindToSelectedActor();`
- L150 _public prototype_ `void RemoveActorBindings();`
- L151 _public prototype_ `bool CanRemoveActorBindings();`
- L153 _public prototype_ `void ApplyProperty();`
- L154 _public prototype_ `void RecordProperty();`
- L155 _public prototype_ `void RemoveCapture();`
- L156 _public prototype_ `void CallDirectorFunction();`
- L157 _public prototype_ `void RemoveDirectorFunctionCaller();`
- L159 _public prototype_ `bool CanApplyProperty();`
- L160 _public prototype_ `bool CanRecordProperty();`
- L161 _public prototype_ `bool CanRemoveCapture();`
- L162 _public prototype_ `bool CanCallDirectorFunction();`
- L163 _public prototype_ `bool CanRemoveDirectorFunctionCaller();`
- L165 _public prototype_ `void SwitchOnVariant(UVariant* Variant);`
- L167 _public prototype_ `void GetSelectedBindingAndEditorActor(UVariantObjectBinding*& OutSelectedBinding, UObject*& OutSelectedObject);`
- L171 _public prototype_ `void SortDisplayNodes(TArray<TSharedRef<FVariantManagerDisplayNode>>& DisplayNodes);` — Sorts display nodes based on their order on the screen Can be used to sort selected nodes
- L173 _public prototype_ `TSharedRef<SWidget> MakeAddButton();`
- L174 _public prototype_ `TSharedRef<SWidget> GetMenuContextForLevelVariantSets();`
- L175 _public prototype_ `TSharedRef<SWidget> MakeLevelVariantSetsComboButton();`
- L177 _public function_ `FVariantManagerPropertiesColumnSizeData& GetPropertiesColumnSizeData()`
- L182 _public prototype_ `static TSharedRef<ITableRow> MakeCapturedPropertyRow(TSharedPtr<FVariantManagerPropertyNode> Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L183 _public prototype_ `static TSharedRef<ITableRow> MakeCapturedPropertyRowWithColumns(TSharedPtr<FVariantManagerPropertyNode> Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L184 _public prototype_ `TSharedPtr<SWidget> OnPropertyListContextMenuOpening() const;`
- L186 _public prototype_ `void OnOutlinerNodeSelectionChanged();`
- L187 _public prototype_ `void OnActorNodeSelectionChanged();`
- L188 _public prototype_ `void OnVariantDependenciesUpdated(UVariant* ParentVariant);`
- L191 _public prototype_ `void RefreshVariantTree();` — These completely refresh the data and the view for each display
- L192 _public prototype_ `void RefreshActorList();`
- L193 _public prototype_ `void RefreshPropertyList();`
- L194 _public prototype_ `void RefreshDependencyLists();`
- L195 _public prototype_ `void UpdatePropertyDefaults();`
- L197 _public prototype_ `void OnBlueprintCompiled();`
- L198 _public prototype_ `void OnMapChanged(UWorld* World, EMapChangeType MapChangeType);`
- L200 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L205 _public prototype_ `void OnOutlinerSearchChanged(const FText& Filter);`
- L207 _public prototype_ `virtual void OnDragEnter( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;`
- L208 _public prototype_ `virtual void OnDragLeave( const FDragDropEvent& DragDropEvent ) override;`
- L209 _public prototype_ `virtual FReply OnDragOver( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;`
- L210 _public prototype_ `virtual FReply OnDrop( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;`
- L211 _public prototype_ `virtual FReply OnKeyDown( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override;`
- L212 _public prototype_ `virtual void OnFocusChanging( const FWeakWidgetPath& PreviousFocusPath, const FWidgetPath& NewWidgetPath, const FFocusEvent& InFocusEvent ) override;`
- L214 _public prototype_ `FReply OnAddVariantSetClicked();`
- L215 _public prototype_ `FReply OnSummonAddActorMenu();`
- L216 _public prototype_ `FReply OnAddDependencyClicked();`
- L218 _public prototype_ `FReply OnDeleteSelectedDependencies();`
- L221 _public function_ `float OnGetPropertiesNameColumnWidth() const` — Callbacks for property ColumnSizeData
- L222 _public function_ `float OnGetPropertiesValueColumnWidth() const`
- L224 _public prototype_ `void OnObjectTransacted(UObject* Object, const class FTransactionObjectEvent& Event);`
- L225 _public prototype_ `void OnObjectPropertyChanged(UObject* Object, struct FPropertyChangedEvent& Event);`
- L226 _public prototype_ `void OnPreObjectPropertyChanged(UObject* Object, const class FEditPropertyChain& PropChain);`
- L227 _public prototype_ `void OnPieEvent(bool bIsSimulating);`
- L228 _public prototype_ `void OnEditorSelectionChanged(UObject* NewSelection);`
- L230 _public prototype_ `void OnThumbnailChanged(UObject* VariantOrVariantSet);`
- L232 _public prototype_ `void ReorderPropertyNodes(const TArray<TSharedPtr<FVariantManagerPropertyNode>>& TheseNodes, TSharedPtr<FVariantManagerPropertyNode> Pivot, EItemDropZone RelativePosition);`
- L243 _private prototype_ `TSharedRef<ITableRow> GenerateRightTreeRow( TSharedRef<ERightTreeRowType> RowType, const TSharedRef<STableViewBase>& OwnerTable );`
- L244 _private prototype_ `TSharedRef<SWidget> GenerateRightTreeHeaderRowContent( ERightTreeRowType RowType, TSharedRef<STableRow<TSharedRef<ERightTreeRowType>>> InTableRow );`
- L245 _private prototype_ `TSharedRef<SWidget> GenerateRightTreePropertiesRowContent();`
- L246 _private prototype_ `TSharedRef<SWidget> GenerateRightTreeDependenciesRowContent();`
- L247 _private prototype_ `TSharedRef<ITableRow> GenerateDependencyRow( FVariantDependencyModelPtr Dependency, const TSharedRef<STableViewBase>& OwnerTable, bool bInteractionEnabled );`
- L251 _private prototype_ `void UpdateVariantSetThumbnail(UVariantSet* InVariantSet);` — Set thumbnail of variant set, if it does not have one, to be the same as first found variant thumbnail
- L253 _private prototype_ `void OnAssetDroppedForVariantManager(const FDragDropEvent& DragDropEvent, TArrayView<FAssetData> AssetDatas);`
- L254 _private prototype_ `static bool OnAreAssetsAcceptableForVariantManager(TArrayView<FAssetData> Assets, FText& OutReason);`
- L256 _private prototype_ `static FReply OnUseSelectedAssetFromContentBrowserForCurrentLevelVariantSet();`
- L257 _private prototype_ `FReply OnBrowseToCurrentLevelVariantSet() const;`
- L259 _private prototype_ `EColumnSortMode::Type GetSortMode(const FName ColumnName) const;`
- L260 _private prototype_ `EColumnSortPriority::Type GetSortPriority(const FName ColumnName) const;`
- L261 _private prototype_ `void HandleSort(const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type NewSortMode);`
- L262 _private prototype_ `void SortItems();`
- L265 _private member_ `TWeakPtr<FVariantManager> VariantManagerPtr;`
- L267 _private member_ `TSharedPtr<SVariantManagerNodeTreeView> NodeTreeView;`
- L269 _private member_ `TSharedPtr<SVariantManagerActorListView> ActorListView;`
- L270 _private member_ `TArray<TSharedRef<FVariantManagerDisplayNode>> DisplayedActors;`
- L272 _private member_ `TSharedPtr<SListView<TSharedPtr<FVariantManagerPropertyNode>>> CapturedPropertyListView;`
- L273 _private member_ `TArray<TSharedPtr<FVariantManagerPropertyNode>> DisplayedPropertyNodes;`
- L275 _private member_ `TSharedPtr<SListView<FVariantDependencyModelPtr>> DependenciesList;`
- L276 _private member_ `TArray<FVariantDependencyModelPtr> DisplayedDependencies;`
- L279 _private member_ `TSet<FString> CachedSelectedActorPaths;` — We use paths here to avoid having to check if the bindings are resolved
- L280 _private member_ `TSet<FString> CachedDisplayedActorPaths;`
- L281 _private member_ `TSet<FString> CachedAllActorPaths;`
- L283 _private member_ `TSharedPtr<SScrollBar> ScrollBar;`
- L285 _private member_ `TArray<TSharedPtr<class IPropertyChangeListener>> PropertyChangeListeners;`
- L287 _private member_ `TSharedPtr<FUICommandList> VariantTreeCommandBindings;`
- L288 _private member_ `TSharedPtr<FUICommandList> ActorListCommandBindings;`
- L289 _private member_ `TSharedPtr<FUICommandList> PropertyListCommandBindings;`
- L291 _private member_ `bool bAutoCaptureProperties = false;`
- L293 _private member_ `FVariantManagerPropertiesColumnSizeData PropertiesColumnSizeData;`
- L294 _private member_ `float PropertiesNameColumnWidth = 0;`
- L295 _private member_ `float PropertiesValueColumnWidth = 0;`
- L297 _private member_ `FSplitterValues SplitterValues;`
- L299 _private member_ `FDelegateHandle OnObjectTransactedHandle;`
- L300 _private member_ `FDelegateHandle OnBlueprintCompiledHandle;`
- L301 _private member_ `FDelegateHandle OnMapChangedHandle;`
- L302 _private member_ `FDelegateHandle OnObjectPropertyChangedHandle;`
- L303 _private member_ `FDelegateHandle OnPreObjectPropertyChangedHandle;`
- L304 _private member_ `FDelegateHandle OnBeginPieHandle;`
- L305 _private member_ `FDelegateHandle OnEndPieHandle;`
- L306 _private member_ `FDelegateHandle OnEditorSelectionChangedHandle;`
- L307 _private member_ `FDelegateHandle OnVariantThumbnailUpdatedHandle;`
- L308 _private member_ `FDelegateHandle OnVariantSetThumbnailUpdatedHandle;`
- L311 _private member_ `TSharedPtr<SSplitter> MainSplitter;` — We keep track of this to remember splitter values between loads
- L312 _private member_ `TSharedPtr<SSplitter> PropertiesSplitter;`
- L313 _private member_ `TSharedPtr<SSplitter> DependenciesSplitter;`
- L315 _private member_ `TArray<TSharedRef<ERightTreeRowType>> RightTreeRootItems;`
- L328 _private member_ `TMap<int32, SVariantManager::FCachedPropertyPath> CachedPropertyPaths;` — Structures used to optimize construction and usage of property paths related to auto-expose, as we must use the pre- and post-property-changed events in combination
- L329 _private member_ `TArray<SVariantManager::FCachedPropertyPath> CachedPropertyPathStack;`
- L331 _private member_ `bool bRespondToEditorSelectionEvents = true;`
- L333 _private member_ `const FTableColumnHeaderStyle* HeaderStyle = nullptr;`
- L334 _private member_ `const FSplitterStyle* SplitterStyle = nullptr;`
- L336 _private member_ `EColumnSortMode::Type SortMode = EColumnSortMode::Ascending;`
- L337 _private member_ `EColumnSortPriority::Type SortPriority = EColumnSortPriority::Primary;`
- L338 _private member_ `FName SortColumn;`

#### enum `SVariantManager::ERightTreeRowType`  
`enum class ERightTreeRowType`  
_L235-241_
- L237 _public enumerator_ `PropertiesHeader`
- L238 _public enumerator_ `PropertiesContent`
- L239 _public enumerator_ `DependenciesHeader`
- L240 _public enumerator_ `DependenciesContent`

#### struct `SVariantManager::FCachedPropertyPath`  
`struct FCachedPropertyPath`  
_L317-324_
- L319 _public member_ `UObject* Object;`
- L320 _public member_ `FProperty* ParentProperty;`
- L321 _public member_ `FProperty* ChildProperty;`
- L322 _public member_ `AActor* TargetActor;`
- L323 _public member_ `FString Path;`

#### Free symbols / members of external scopes

- L37 _typedef_ `using FVariantDependencyModelPtr = TSharedPtr<FVariantDependencyModel>;`
- L65 _delegate_ `DECLARE_DELEGATE_OneParam(FOnToggleBoolOption, bool) SLATE_BEGIN_ARGS(SVariantManager) { } SLATE_ARGUMENT(TSharedPtr<FExtender>, AddMenuExtender) SLATE_ARGUMENT(TSharedPtr<FExtender>, ToolbarExtender) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FVariantManager> InVariantManager);`

### `Plugins/Enterprise/VariantManager/Source/VariantManager/Private/SVariantManagerActorListView.h` (Private)


#### class `SVariantManagerActorListView`  
`class SVariantManagerActorListView : public SListView<TSharedRef<FVariantManagerDisplayNode>>`  
_L13-45_
- inherits: `SListView<TSharedRef<FVariantManagerDisplayNode>>`
- L16 _public function_ `SLATE_BEGIN_ARGS(SVariantManagerActorListView)`
- L17 _public prototype_ `SLATE_ARGUMENT( const TArray<TSharedRef<FVariantManagerDisplayNode>>* , ListItemsSource) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TWeakPtr<FVariantManager> InVariantManagerPtr);`
- L22 _public prototype_ `virtual void OnDragLeave( const FDragDropEvent& DragDropEvent ) override;`
- L23 _public prototype_ `virtual FReply OnDragOver( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;`
- L24 _public prototype_ `virtual FReply OnDrop( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;`
- L30 _public prototype_ `virtual void Private_SetItemSelection( TSharedRef<FVariantManagerDisplayNode> TheItem, bool bShouldBeSelected, bool bWasUserDirected = false ) override;` — We override all of these because we want to behave like the rest of the engine: Highlight on mouse down, but only select on release/mouse up. Besides, some of these fire one after the other like clear + setItemSelection, which would break things in SVariantManager or cause unecessary updates. The first three fire on mouse down and highlight, the last one fires on mouse up/key down/touch up and selects
- L31 _public prototype_ `virtual void Private_ClearSelection() override;`
- L32 _public prototype_ `virtual void Private_SelectRangeFromCurrentTo(TSharedRef<FVariantManagerDisplayNode> InRangeSelectionEnd) override;`
- L33 _public prototype_ `virtual void Private_SignalSelectionChanged(ESelectInfo::Type SelectInfo) override;`
- L35 _public prototype_ `void UpdateSelectionFromListView();`
- L36 _public prototype_ `void UpdateListViewFromSelection();`
- L40 _private prototype_ `TSharedRef<ITableRow> OnGenerateActorRow(TSharedRef<FVariantManagerDisplayNode> Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L41 _private prototype_ `TSharedPtr<SWidget> OnActorListContextMenuOpening();`
- L43 _private member_ `TWeakPtr<FVariantManager> VariantManagerPtr;`
- L44 _private member_ `bool bCanDrop = false;`

### `Plugins/Enterprise/VariantManager/Source/VariantManager/Private/SVariantManagerNodeTreeView.h` (Private)


#### class `SVariantManagerNodeTreeView`  
`class SVariantManagerNodeTreeView : public STreeView<FDisplayNodeRef>`  
_L13-61_
- inherits: `STreeView<FDisplayNodeRef>`
- L17 _public function_ `SLATE_BEGIN_ARGS(SVariantManagerNodeTreeView)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FVariantManagerNodeTree>& InNodeTree);`
- L22 _public prototype_ `int32 GetDisplayIndexOfNode(FDisplayNodeRef InNode);`
- L25 _public prototype_ `void Refresh();` — Caches the nodes the VariantManagerNodeTree is using and refreshes the display
- L29 _public prototype_ `void SortAsDisplayed(TArray<FDisplayNodeRef>& Nodes);` — Sorts the given nodes so that they are in the same order as they appear on the screen This compares the given nodes with the STreeView's LinearizedItems
- L35 _public prototype_ `virtual void Private_SetItemSelection(FDisplayNodeRef TheItem, bool bShouldBeSelected, bool bWasUserDirected = false) override;` — We override all of these because we want to behave like the rest of the engine: Highlight on mouse down, but only select on release/mouse up. Besides, some of these fire one after the other like clear + setItemSelection, which would break things in SVariantManager or cause unecessary updates. The first three fire on mouse down and highlight, the last one fires on mouse up/key down/touch up and selects
- L36 _public prototype_ `virtual void Private_ClearSelection() override;`
- L37 _public prototype_ `virtual void Private_SelectRangeFromCurrentTo(FDisplayNodeRef InRangeSelectionEnd) override;`
- L38 _public prototype_ `virtual void Private_SignalSelectionChanged(ESelectInfo::Type SelectInfo) override;`
- L42 _public prototype_ `void UpdateSelectionFromTreeView();` — Sets FVariantManagerSelection to whatever our STreeView has selected Does not broadcast anything
- L43 _public prototype_ `void UpdateTreeViewFromSelection();`
- L47 _protected prototype_ `void OnExpansionChanged(FDisplayNodeRef InItem, bool bIsExpanded);`
- L48 _protected prototype_ `TSharedRef<ITableRow> OnGenerateRow(FDisplayNodeRef InDisplayNode, const TSharedRef<STableViewBase>& OwnerTable);`
- L49 _protected prototype_ `void OnGetChildren(FDisplayNodeRef InParent, TArray<FDisplayNodeRef>& OutChildren) const;`
- L50 _protected prototype_ `TSharedPtr<SWidget> OnContextMenuOpening();`
- L52 _protected function_ `TSharedPtr<FVariantManagerNodeTree> GetNodeTree()`
- L59 _private member_ `TSharedPtr<FVariantManagerNodeTree> VariantManagerNodeTree;`
- L60 _private member_ `TArray<FDisplayNodeRef> RootNodes;`

#### Free symbols / members of external scopes

- L10 _typedef_ `typedef TSharedRef<FVariantManagerDisplayNode> FDisplayNodeRef;`

### `Plugins/Enterprise/VariantManager/Source/VariantManager/Private/SVariantManagerTableRow.h` (Private)


#### class `SVariantManagerTableRow`  
`class SVariantManagerTableRow : public STableRow<FDisplayNodeRef>`  
_L14-41_
- inherits: `STableRow<FDisplayNodeRef>`
- desc: Represents a row in the VariantManager's tree views and list views
- L17 _public function_ `SLATE_BEGIN_ARGS(SVariantManagerTableRow)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTableView, const TSharedRef<FVariantManagerDisplayNode>& InNode);`
- L22 _public function_ `TSharedPtr<FVariantManagerDisplayNode> GetDisplayNode() const`
- L28 _public prototype_ `FReply DragDetected(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent);` — We subscribe these to base class STableRow's events
- L29 _public prototype_ `void DragLeave(const FDragDropEvent& DragDropEvent);`
- L30 _public prototype_ `TOptional<EItemDropZone> CanAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone ItemDropZone, FDisplayNodeRef DisplayNode);`
- L31 _public prototype_ `FReply AcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone ItemDropZone, FDisplayNodeRef DisplayNode);`
- L34 _public prototype_ `virtual FReply OnMouseButtonDoubleClick( const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent ) override;` — STableRow interface
- L35 _public prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L40 _private member_ `mutable TWeakPtr<FVariantManagerDisplayNode> Node;`

#### class `SVariantManagerMultiColumnPropertyTableRow`  
`class SVariantManagerMultiColumnPropertyTableRow : public SMultiColumnTableRow<TSharedPtr<FVariantManagerPropertyNode>>`  
_L45-78_
- inherits: `SMultiColumnTableRow<TSharedPtr<FVariantManagerPropertyNode>>`
- desc: Represents a multi-column row in the VariantManager's list views for displaying properties (and function callers)
- L48 _public member_ `static const FName ColumnPath;`
- L49 _public member_ `static const FName ColumnProperty;`
- L50 _public member_ `static const FName ColumnValue;`
- L52 _public function_ `SLATE_BEGIN_ARGS(SVariantManagerMultiColumnPropertyTableRow)`
- L53 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTableView, const TSharedRef<FVariantManagerPropertyNode>& InNode);`
- L57 _public function_ `TSharedPtr<FVariantManagerDisplayNode> GetDisplayNode() const`
- L63 _public prototype_ `FReply DragDetected(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent);` — We subscribe these to base class STableRow's events
- L64 _public prototype_ `void DragLeave(const FDragDropEvent& DragDropEvent);`
- L65 _public prototype_ `TOptional<EItemDropZone> CanAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone ItemDropZone, TSharedPtr<FVariantManagerPropertyNode> DisplayNode);`
- L66 _public prototype_ `FReply AcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone ItemDropZone, TSharedPtr<FVariantManagerPropertyNode> DisplayNode);`
- L69 _public prototype_ `virtual FReply OnMouseButtonDoubleClick( const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent ) override;` — STableRow interface
- L70 _public prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L73 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& InColumnName) override;`
- L77 _private member_ `mutable TWeakPtr<FVariantManagerPropertyNode> Node;`

#### Free symbols / members of external scopes

- L11 _typedef_ `typedef TSharedRef<FVariantManagerDisplayNode> FDisplayNodeRef;`

### `Plugins/Enterprise/VariantManager/Source/VariantManager/Private/VariantManagerClipboard.h` (Private)


#### class `FVariantManagerClipboard`  
`class FVariantManagerClipboard`  
_L11-89_
- L15 _public function_ `static void Push(UVariant* Variant)`
- L19 _public function_ `static void Push(UVariantSet* VariantSet)`
- L23 _public function_ `static void Push(UVariantObjectBinding* ObjectBinding)`
- L27 _public function_ `static void Push(const TArray<UVariant*>& Variants)`
- L35 _public function_ `static void Push(const TArray<UVariantSet*>& VariantSets)`
- L43 _public function_ `static void Push(const TArray<UVariantObjectBinding*>& ObjectBindings)`
- L51 _public function_ `static const TArray<TStrongObjectPtr<UVariant>>& GetVariants()`
- L55 _public function_ `static const TArray<TStrongObjectPtr<UVariantSet>>& GetVariantSets()`
- L59 _public function_ `static const TArray<TStrongObjectPtr<UVariantObjectBinding>>& GetObjectBindings()`
- L63 _public function_ `static void EmptyVariants()`
- L67 _public function_ `static void EmptyVariantSets()`
- L71 _public function_ `static void EmptyObjectBindings()`
- L75 _public function_ `static void Empty()`
- L86 _private member_ `static TArray<TStrongObjectPtr<UVariant>> StoredVariants;` — These should be TStrongObjectPtr because if we're cutting and pasting, we might temporarily be the only objects pointing at these items
- L87 _private member_ `static TArray<TStrongObjectPtr<UVariantSet>> StoredVariantSets;`
- L88 _private member_ `static TArray<TStrongObjectPtr<UVariantObjectBinding>> StoredObjectBindings;`

### `Plugins/Enterprise/VariantManager/Source/VariantManager/Private/VariantManagerDragDropOp.h` (Private)


#### class `FVariantManagerDragDropOp`  
`class FVariantManagerDragDropOp : public FDecoratedDragDropOp`  
_L10-28_
- inherits: `FDecoratedDragDropOp`
- L14 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FVariantManagerDragDropOp, FDecoratedDragDropOp) static TSharedRef<FVariantManagerDragDropOp> New(TArray<TSharedRef<FVariantManagerDisplayNode>>& InDraggedNodes);`
- L18 _public prototype_ `TArray<TSharedRef<FVariantManagerDisplayNode>>& GetDraggedNodes();`
- L23 _private function_ `FVariantManagerDragDropOp()` — Force usage of factory method
- L27 _private member_ `TArray<TSharedRef<FVariantManagerDisplayNode>> DraggedNodes;`

### `Plugins/Enterprise/VariantManager/Source/VariantManager/Private/VariantManagerEditorCommands.h` (Private)


#### class `FVariantManagerEditorCommands`  
`class FVariantManagerEditorCommands : public TCommands<FVariantManagerEditorCommands>`  
_L8-37_
- inherits: `TCommands<FVariantManagerEditorCommands>`
- L14 _public prototype_ `FVariantManagerEditorCommands();` — Default constructor.
- L17 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands
- L19 _public member_ `TSharedPtr<FUICommandInfo> CreateVariantManagerCommand;`
- L20 _public member_ `TSharedPtr<FUICommandInfo> AddVariantSetCommand;`
- L21 _public member_ `TSharedPtr<FUICommandInfo> AddSelectedActorsCommand;`
- L22 _public member_ `TSharedPtr<FUICommandInfo> SwitchOnSelectedVariantCommand;`
- L23 _public member_ `TSharedPtr<FUICommandInfo> CreateThumbnailCommand;`
- L24 _public member_ `TSharedPtr<FUICommandInfo> SelectThumbnailAssetCommand;`
- L25 _public member_ `TSharedPtr<FUICommandInfo> LoadThumbnailCommand;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> ClearThumbnailCommand;`
- L27 _public member_ `TSharedPtr<FUICommandInfo> AddPropertyCaptures;`
- L28 _public member_ `TSharedPtr<FUICommandInfo> AddFunction;`
- L29 _public member_ `TSharedPtr<FUICommandInfo> RebindActorDisabled;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> RebindToSelected;`
- L31 _public member_ `TSharedPtr<FUICommandInfo> RemoveActorBindings;`
- L32 _public member_ `TSharedPtr<FUICommandInfo> ApplyProperty;`
- L33 _public member_ `TSharedPtr<FUICommandInfo> RecordProperty;`
- L34 _public member_ `TSharedPtr<FUICommandInfo> RemoveCapture;`
- L35 _public member_ `TSharedPtr<FUICommandInfo> CallFunction;`
- L36 _public member_ `TSharedPtr<FUICommandInfo> RemoveFunction;`

### `Plugins/Enterprise/VariantManager/Source/VariantManager/Private/VariantManagerLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogVariantManager, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogVariantManager, Log, All);`

### `Plugins/Enterprise/VariantManager/Source/VariantManager/Private/VariantManagerNodeTree.h` (Private)


#### class `FVariantManagerNodeTree`  
`class FVariantManagerNodeTree : public TSharedFromThis<FVariantManagerNodeTree>`  
_L15-50_
- inherits: `TSharedFromThis<FVariantManagerNodeTree>`
- L19 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnUpdated);`
- L21 _public function_ `FVariantManagerNodeTree( class FVariantManager& InVariantManager ) : VariantManager( InVariantManager )`
- L25 _public prototype_ `void Empty();`
- L29 _public prototype_ `void Update();` — Creates display nodes for all variant sets and variants that pass the filter and adds them to RootNodes. Doesn't update anything else
- L30 _public prototype_ `const TArray< TSharedRef<FVariantManagerDisplayNode> >& GetRootNodes() const;`
- L32 _public function_ `bool HasActiveFilter() const`
- L33 _public prototype_ `bool IsNodeFiltered( const TSharedRef<const FVariantManagerDisplayNode> Node ) const;`
- L34 _public prototype_ `void FilterNodes( const FString& InFilter );`
- L36 _public function_ `FVariantManager& GetVariantManager()`
- L38 _public prototype_ `void SetHoveredNode(const TSharedPtr<FVariantManagerDisplayNode>& InHoveredNode);`
- L39 _public prototype_ `const TSharedPtr<FVariantManagerDisplayNode>& GetHoveredNode() const;`
- L43 _private member_ `TArray< TSharedRef<FVariantManagerDisplayNode> > RootNodes;`
- L44 _private member_ `TSet<TSharedRef<const FVariantManagerDisplayNode>> FilteredNodes;`
- L45 _private member_ `TSharedPtr<FVariantManagerDisplayNode> HoveredNode;`
- L47 _private member_ `FString FilterString;`
- L49 _private member_ `FVariantManager& VariantManager;`

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnUpdated);`

### `Plugins/Enterprise/VariantManager/Source/VariantManager/Private/VariantManagerPropertyCapturer.h` (Private)


#### class `FVariantManagerPropertyCapturer`  
`class FVariantManagerPropertyCapturer`  
_L15-47_
- desc: Utility for capturing useful properties of a given UObject, as well as building a small UI listing them and allowing each to be picked
- L25 _public prototype_ `static void CaptureProperties(const TArray<UObject*>& InObjectsToCapture, TArray<TSharedPtr<FCapturableProperty>>& OutCapturedProps, FString TargetPropertyPath = FString(), bool bCaptureAllArrayIndices = false);` — Returns in OutCaptureProps a FCapturableProperty struct for the union of each and any viable property we can find on all InObjectsToCapture. TargetPropertyPath: When this is given it will only capture properties that have this *exact* property path bCaptureAllArrayIndices: If true and if we have a TargetPropertyPath, a path like 'Tags[2]' will lead to the capturing of all array indices of 'Tags', so 'Tags[0]', 'Tags[1]', 'Tags[2]', etc. If false, only 'Tags[2]' will be captured.
- L31 _public prototype_ `static void CaptureVisibility(const TArray<UObject*>& InObjectsToCapture, TArray<TSharedPtr<FCapturableProperty>>& OutCapturedProps);` — Returns in OutCaptureProps the FCapturableProperty corresponding to the Visibility property of all USceneComponents that we find in InObjectsToCapture
- L37 _public prototype_ `static void CaptureTransform(const TArray<UObject*>& InObjectsToCapture, TArray<TSharedPtr<FCapturableProperty>>& OutCapturedProps);` — Returns in OutCaptureProps the FCapturablePropertys corresponding to the transform properties of all USceneComponents that we find in InObjectsToCapture
- L38 _public prototype_ `static void CaptureLocation(const TArray<UObject*>& InObjectsToCapture, TArray<TSharedPtr<FCapturableProperty>>& OutCapturedProps);`
- L39 _public prototype_ `static void CaptureRotation(const TArray<UObject*>& InObjectsToCapture, TArray<TSharedPtr<FCapturableProperty>>& OutCapturedProps);`
- L40 _public prototype_ `static void CaptureScale3D(const TArray<UObject*>& InObjectsToCapture, TArray<TSharedPtr<FCapturableProperty>>& OutCapturedProps);`
- L46 _public prototype_ `static void CaptureMaterial(const TArray<UObject*>& InObjectsToCapture, TArray<TSharedPtr<FCapturableProperty>>& OutCapturedProps);` — Returns in OutCaptureProps the FCapturablePropertys corresponding to the material properties of all UMeshComponents that we find in InObjectsToCapture

### `Plugins/Enterprise/VariantManager/Source/VariantManager/Private/VariantManagerSelection.h` (Private)


#### class `FVariantManagerSelection`  
`class FVariantManagerSelection`  
_L14-98_
- L22 _public prototype_ `FVariantManagerSelection();`
- L25 _public prototype_ `TSet<TSharedRef<FVariantManagerDisplayNode>>& GetSelectedOutlinerNodes();` — Gets a set of the selected outliner nodes.
- L26 _public prototype_ `TSet<TSharedRef<FVariantManagerActorNode>>& GetSelectedActorNodes();`
- L28 _public prototype_ `void GetSelectedVariantsAndVariantSets(TArray<UVariant*>& OutVariants, TArray<UVariantSet*>& OutVariantSets);`
- L30 _public prototype_ `void AddToSelection(TSharedRef<FVariantManagerDisplayNode> OutlinerNode);`
- L31 _public prototype_ `void AddToSelection(const TArray<TSharedRef<FVariantManagerDisplayNode>>& OutlinerNodes);`
- L33 _public prototype_ `void AddActorNodeToSelection(TSharedRef<FVariantManagerActorNode> ActorNode);`
- L34 _public prototype_ `void AddActorNodeToSelection(const TArray<TSharedRef<FVariantManagerActorNode>>& ActorNodes);`
- L36 _public prototype_ `void RemoveFromSelection(TSharedRef<FVariantManagerDisplayNode> OutlinerNode);`
- L37 _public prototype_ `void RemoveActorNodeFromSelection(TSharedRef<FVariantManagerActorNode> ActorNode);`
- L39 _public prototype_ `void SetSelectionTo(const TArray<TSharedRef<FVariantManagerDisplayNode>>& OutlinerNodes, bool bFireBroadcast = true);`
- L40 _public prototype_ `void SetActorNodeSelectionTo(const TArray<TSharedRef<FVariantManagerActorNode>>& ActorNodes, bool bFireBroadcast = true);`
- L47 _public prototype_ `TSet<FString>& GetSelectedNodePaths();` — These manage paths to selected objects using ObjectNames (e.g. ULevelVariantSets_2/UVariantSets_5/UVariant_1/UVariantObjectBinding_7) Used to preserve selection during tree/list updates (e.g. add a new object binding, add it to this, then refresh tree to have it immediately selected)
- L50 _public prototype_ `bool IsSelected(const TSharedRef<FVariantManagerDisplayNode> OutlinerNode) const;` — Returns whether or not the outliner node is selected.
- L53 _public prototype_ `void Empty();` — Empties all selections.
- L56 _public prototype_ `void EmptySelectedOutlinerNodes();` — Empties the outliner node selection.
- L57 _public prototype_ `void EmptySelectedActorNodes();`
- L60 _public prototype_ `FOnSelectionChanged& GetOnOutlinerNodeSelectionChanged();` — Gets a multicast delegate which is called when the outliner node selection changes.
- L61 _public prototype_ `FOnSelectionChanged& GetOnActorNodeSelectionChanged();`
- L64 _public prototype_ `TArray<FGuid> GetBoundObjectsGuids();` — Helper function to get an array of FGuid of bound objects on return
- L67 _public prototype_ `void SuspendBroadcast();` — Suspend the broadcast of selection change notifications.
- L70 _public prototype_ `void ResumeBroadcast();` — Resume the broadcast of selection change notifications.
- L72 _public prototype_ `void RequestOutlinerNodeSelectionChangedBroadcast();`
- L73 _public prototype_ `void RequestActorNodeSelectionChangedBroadcast();`
- L77 _private prototype_ `bool IsBroadcasting();` — When true, selection change notifications should be broadcasted.
- L85 _private member_ `TSet<FString> SelectedNodePaths;` — We load/store these to preserve selections when updating node trees/list views objects can also manually set these so that the nodes built for these paths will be selected when the tree is refreshed (e.g. add a new object binding, add it to this, then refresh tree to have it immediately selected)
- L87 _private member_ `TSet<TSharedRef<FVariantManagerDisplayNode>> SelectedOutlinerNodes;`
- L88 _private member_ `TSet<TSharedRef<FVariantManagerActorNode>> SelectedActorNodes;`
- L90 _private member_ `FOnSelectionChanged OnOutlinerNodeSelectionChanged;`
- L91 _private member_ `FOnSelectionChanged OnActorNodeSelectionChanged;`
- L94 _private member_ `int32 SuspendBroadcastCount;` — The number of times the broadcasting of selection change notifications has been suspended.
- L97 _private member_ `bool bOutlinerNodeSelectionChangedBroadcastPending;` — When true there is a pending outliner node selection change which will be broadcast next tick.

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnSelectionChanged) public: FVariantManagerSelection();`

### `Plugins/Enterprise/VariantManager/Source/VariantManager/Private/VariantManagerStyle.h` (Private)


#### class `FVariantManagerStyle`  
`class FVariantManagerStyle final : public FSlateStyleSet`  
_L8-25_
- inherits: `FSlateStyleSet`
- L11 _public prototype_ `FVariantManagerStyle();`
- L13 _public function_ `~FVariantManagerStyle()`
- L18 _public prototype_ `static const FName GetAppStyleSetName();`
- L20 _public function_ `static FVariantManagerStyle& Get()`

### `Plugins/Enterprise/VariantManager/Source/VariantManager/Private/VariantManagerUtils.h` (Private)


#### class `FVariantManagerUtils`  
`class FVariantManagerUtils`  
_L14-61_
- L19 _public prototype_ `static void RegisterForHotReload();` — Invalidate our cached pointers whenever a hot reload happens, as the classes that own those UPropertys might be reinstanced
- L20 _public prototype_ `static void UnregisterForHotReload();`
- L24 _public prototype_ `static bool IsBuiltInStructProperty(const FProperty* Property);` — Returns true if Property is a FStructProperty with a Struct of type FVector, FColor, FRotator, FQuat, etc
- L28 _public prototype_ `static bool IsWalkableStructProperty(const FProperty* Property);` — Returns true if Property is a FStructProperty with a Struct that the Variant Manager is allowed to capture specific properties from
- L31 _public prototype_ `static FArrayProperty* GetOverrideMaterialsProperty();` — Returns the OverrideMaterials property of the UMeshComponent class
- L34 _public prototype_ `static FStructProperty* GetRelativeLocationProperty();` — Returns the RelativeLocation property of the USceneComponent class
- L37 _public prototype_ `static FStructProperty* GetRelativeRotationProperty();` — Returns the RelativeRotation property of the USceneComponent class
- L40 _public prototype_ `static FStructProperty* GetRelativeScale3DProperty();` — Returns the RelativeScale3D property of the USceneComponent class
- L43 _public prototype_ `static FBoolProperty* GetVisibilityProperty();` — Returns the bVisible property of the USceneComponent class
- L46 _public prototype_ `static FStructProperty* GetLightColorProperty();` — Returns the LightColor property of the ULightComponent class
- L50 _private prototype_ `static void InvalidateCache();` — Invalidates all of our cached FProperty pointers
- L52 _private member_ `static FArrayProperty* OverrideMaterialsProperty;`
- L53 _private member_ `static FStructProperty* RelativeLocationProperty;`
- L54 _private member_ `static FStructProperty* RelativeRotationProperty;`
- L55 _private member_ `static FStructProperty* RelativeScale3DProperty;`
- L56 _private member_ `static FBoolProperty* VisiblityProperty;`
- L57 _private member_ `static FStructProperty* LightColorProperty;`
- L58 _private member_ `static FStructProperty* DefaultLightColorProperty;`
- L60 _private member_ `static FDelegateHandle OnHotReloadHandle;`

### `Plugins/Enterprise/VariantManager/Source/VariantManager/Public/CapturableProperty.h` (Public)


#### struct `FCapturableProperty`  
`struct FCapturableProperty`  
_L15-92_
- reflection: `USTRUCT(BlueprintType)`
- desc: Describes a property path that can be captured. It just exposes a display name but uses internal data in order to be able to capture exception properties, like materials
- L19 _public function_ `FCapturableProperty() : Checked(false) , Favorite(false) , CaptureType(EPropertyValueCategory::Undefined)`
- L25 _public function_ `FCapturableProperty(const FString& InDisplayName, const FPropertyPath& InPropPath, const TArray<FString>& InComponentNames, bool InChecked, FName InPropertySetterName, EPropertyValueCategory InCaptureType) : DisplayName(InDisplayName) , Prop(InPropPath) , Checked(InChecked) , Favorite(false) , CaptureType(InCaptureType) , ComponentNames(InComponentNames) , PropertySetterName(InPropertySetterName)`
- L54 _public member_ `FString DisplayName;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="VariantManager")`
- L56 _public member_ `FPropertyPath Prop;`
- L57 _public member_ `bool Checked;`
- L58 _public member_ `bool Favorite;`
- L59 _public member_ `bool bIsActor = false;`
- L60 _public member_ `EPropertyValueCategory CaptureType;`
- L61 _public member_ `TArray<FString> ComponentNames;` — Same length as Prop, but will be empty for non-component ObjectProperties
- L62 _public member_ `FName PropertySetterName;`
- L64 _public member_ `FString SubPath;` — Path without property name
- L65 _public member_ `FString PropertyName;` — Just property name
- L67 _public function_ `TArray<FCapturedPropSegment> ToCapturedPropSegmentArray()`

### `Plugins/Enterprise/VariantManager/Source/VariantManager/Public/VariantManager.h` (Public)


#### class `FVariantManager`  
`class FVariantManager final : public FGCObject , public FEditorUndoClient , public TSharedFromThis<FVariantManager>`  
_L24-149_
- inherits: `FGCObject,FEditorUndoClient,TSharedFromThis<FVariantManager>`
- L31 _public prototype_ `FVariantManager();`
- L33 _public prototype_ `virtual ~FVariantManager();`
- L35 _public prototype_ `void Close();`
- L37 _public prototype_ `void InitVariantManager(ULevelVariantSets* InLevelVariantSets);`
- L39 _public prototype_ `void CaptureNewProperties(const TArray<UVariantObjectBinding*>& Bindings);`
- L40 _public prototype_ `void GetCapturableProperties(const TArray<AActor*>& Actors, TArray<TSharedPtr<FCapturableProperty>>& OutProperties, FString TargetPropertyPath = FString(), bool bCaptureAllArrayIndices = true);`
- L41 _public prototype_ `void GetCapturableProperties(const TArray<UClass*>& Classes, TArray<TSharedPtr<FCapturableProperty>>& OutProperties, FString TargetPropertyPath = FString(), bool bCaptureAllArrayIndices = true);`
- L45 _public prototype_ `UBlueprint* GetOrCreateDirectorBlueprint(ULevelVariantSets* InLevelVariantSets);` — Sets up the blueprint class deriving from the function director that we'll use. Do this here as it uses editor-only code
- L46 _public prototype_ `UK2Node_FunctionEntry* CreateDirectorFunction(ULevelVariantSets* InLevelVariantSets, FName InFunctionName, UClass* PinClassType, bool bCreateWithArguments);`
- L47 _public prototype_ `UK2Node_FunctionEntry* CreateDirectorFunctionFromFunction(UFunction* QuickBindFunction, UClass* PinClassType, bool bCreateWithArguments);`
- L48 _public prototype_ `void CreateFunctionCaller(const TArray<UVariantObjectBinding*>& Bindings);`
- L51 _public prototype_ `void AddPropertyCaptures(const TArray<UPropertyValue*>& OfThisProperty, UVariantObjectBinding* ToThisBinding);` — Adds existing items to existing containers
- L52 _public prototype_ `void AddObjectBindings(const TArray<UVariantObjectBinding*>& TheseBindings, UVariant* ToThisVariant, int32 InsertionIndex = INDEX_NONE, bool bReplaceOld = false);`
- L53 _public prototype_ `void AddVariants(const TArray<UVariant*>& TheseVariants, UVariantSet* ToThisVariantSet, int32 InsertionIndex = INDEX_NONE);`
- L54 _public prototype_ `void AddVariantSets(const TArray<UVariantSet*>& TheseVariantSets, ULevelVariantSets* ToThisLevelVarSets, int32 InsertionIndex = INDEX_NONE);`
- L55 _public prototype_ `void AddFunctionCallers(const TArray<FFunctionCaller>& Functions, UVariantObjectBinding* Binding);`
- L58 _public prototype_ `void RemovePropertyCapturesFromParent(const TArray<UPropertyValue*>& ThisProp);` — Removes existing items from existing containers
- L59 _public prototype_ `void RemoveObjectBindingsFromParent(const TArray<UVariantObjectBinding*>& ThisBinding);`
- L60 _public prototype_ `void RemoveVariantsFromParent(const TArray<UVariant*>& ThisVariant);`
- L61 _public prototype_ `void RemoveVariantSetsFromParent(const TArray<UVariantSet*>& ThisVariantSet);`
- L62 _public prototype_ `void RemoveFunctionCallers(const TArray<FFunctionCaller*>& TheseCallers, UVariantObjectBinding* FromThisBinding);`
- L65 _public prototype_ `void MoveObjectBindings(const TArray<UVariantObjectBinding*>& TheseBindings, UVariant* ToThisVariant);` — Remove existing items from their parents and add them to existing containers
- L66 _public prototype_ `void MoveVariants(const TArray<UVariant*>& TheseVariants, UVariantSet* ToThisVariantSet, int32 InsertionIndex = INDEX_NONE);`
- L67 _public prototype_ `void MoveVariantSets(const TArray<UVariantSet*>& TheseVariantSets, ULevelVariantSets* ToThisLevelVariantSets, int32 InsertionIndex = INDEX_NONE);`
- L70 _public prototype_ `void DuplicateObjectBindings(const TArray<UVariantObjectBinding*>& TheseBindings, UVariant* ToThisVariant, int32 InsertionIndex = INDEX_NONE);` — Duplicate existing items to existing containers
- L71 _public prototype_ `void DuplicateVariants(const TArray<UVariant*>& TheseVariants, UVariantSet* ToThisVariantSet, int32 InsertionIndex = INDEX_NONE);`
- L72 _public prototype_ `void DuplicateVariantSets(const TArray<UVariantSet*>& TheseVariantSets, ULevelVariantSets* ToThisLevelVarSets, int32 InsertionIndex = INDEX_NONE);`
- L75 _public prototype_ `void MergeObjectBindings(const UVariantObjectBinding* ThisBinding, UVariantObjectBinding* IntoThisBinding);` — Adds all children from one container to the other container, if it doesn't already have them
- L76 _public prototype_ `void MergeVariants(const UVariant* ThisVar, UVariant* IntoThisVar);`
- L79 _public prototype_ `TArray<UPropertyValue*> CreatePropertyCaptures(const TArray<TSharedPtr<FCapturableProperty>>& OfTheseProperties, const TArray<UVariantObjectBinding*>& InTheseBindings, bool bSilenceWarnings = false);` — Creates new items and add them to existing containers
- L80 _public prototype_ `TArray<UPropertyValue*> CreateTransformPropertyCaptures(const TArray<UVariantObjectBinding*>& InTheseBindings);`
- L81 _public prototype_ `TArray<UPropertyValue*> CreateLocationPropertyCaptures(const TArray<UVariantObjectBinding*>& InTheseBindings);`
- L82 _public prototype_ `TArray<UPropertyValue*> CreateRotationPropertyCaptures(const TArray<UVariantObjectBinding*>& InTheseBindings);`
- L83 _public prototype_ `TArray<UPropertyValue*> CreateScale3DPropertyCaptures(const TArray<UVariantObjectBinding*>& InTheseBindings);`
- L84 _public prototype_ `TArray<UPropertyValue*> CreateVisibilityPropertyCaptures(const TArray<UVariantObjectBinding*>& InTheseBindings);`
- L85 _public prototype_ `TArray<UPropertyValue*> CreateMaterialPropertyCaptures(const TArray<UVariantObjectBinding*>& InTheseBindings);`
- L86 _public prototype_ `TArray<UVariantObjectBinding*> CreateObjectBindings(const TArray<AActor*>& OfTheseActors, const TArray<UVariant*>& InTheseVariants, int32 InsertionIndex = INDEX_NONE);`
- L87 _public prototype_ `TArray<UVariantObjectBinding*> CreateObjectBindingsAndCaptures(const TArray<AActor*>& OfTheseActors, const TArray<UVariant*>& InTheseVariants, int32 InsertionIndex = INDEX_NONE);`
- L88 _public prototype_ `UVariant* CreateVariant(UVariantSet* InThisVariantSet);`
- L89 _public prototype_ `UVariantSet* CreateVariantSet(ULevelVariantSets* InThisLevelVariantSets);`
- L93 _public prototype_ `TArray<FObjectThumbnail*> GetVariantThumbnails(const TArray<UVariant*> SrcArray);` — Thumbnail operations Returns one for each variant. These can be nullptr
- L95 _public prototype_ `void SetVariantThumbnails(const TArray<FObjectThumbnail*> Thumbnails, const TArray<UVariant*> Variants);` — Expects one for each variant. Accepts nullptr (will clear any previous thumbnail when setting)
- L96 _public prototype_ `void CopyVariantThumbnails(TArray<UVariant*> DstArray, const TArray<UVariant*> SrcArray);`
- L99 _public prototype_ `void RecordProperty(UPropertyValue* Prop) const;` — Captured property handling
- L100 _public prototype_ `void ApplyProperty(UPropertyValue* Prop) const;`
- L103 _public prototype_ `void CallDirectorFunction(FName FunctionName, UVariantObjectBinding* TargetObject) const;` — Function handling
- L106 _public prototype_ `virtual void PostUndo(bool bSuccess) override;` — FEditorUndoClient Interface
- L107 _public function_ `virtual void PostRedo(bool bSuccess) override`
- L113 _public prototype_ `void CanAddActorsToVariant(const TArray<TWeakObjectPtr<AActor>>& InActors, const UVariant* InVariant, TArray<TWeakObjectPtr<AActor>>& OutActorsWeCanAdd);` — Returns which actors we can add to an existing UVariant, since we only allow one per actor per variant We can force add/replace with AddObjectBindings, but this allows us to check how many will be added, which is used for tooltips and feedback
- L114 _public prototype_ `void CanAddActorsToVariant(const TArray<UObject*>& InActors, const UVariant* InVariant, TArray<UObject*>& OutActorsWeCanAdd);`
- L116 _public prototype_ `TSharedPtr<SVariantManager> GetVariantManagerWidget();`
- L118 _public function_ `ULevelVariantSets* GetCurrentLevelVariantSets()`
- L124 _public function_ `TSharedRef<FVariantManagerNodeTree> GetNodeTree()` — Gets the tree of nodes which is used to populate the animation outliner.
- L129 _public function_ `FVariantManagerSelection& GetSelection()`
- L135 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L136 _public function_ `virtual FString GetReferencerName() const override`
- L142 _private member_ `TSharedPtr<FVariantManagerSelection> Selection;`
- L144 _private member_ `TWeakObjectPtr<ULevelVariantSets> CurrentLevelVariantSets;`
- L146 _private member_ `TSharedPtr<SVariantManager> VariantManagerWidget;`
- L148 _private member_ `TSharedRef<FVariantManagerNodeTree> NodeTree;`

### `Plugins/Enterprise/VariantManager/Source/VariantManager/Public/VariantManagerBlueprintLibrary.h` (Public)


#### enum `EVariantFunctionCallerSignature`  
`enum class EVariantFunctionCallerSignature : uint8`  
_L21-29_
- reflection: `UENUM(BlueprintType)`
- L23 _public enumerator_ `Static`
- L24 _public enumerator_ `NoParameters`
- L25 _public enumerator_ `OneParameter`
- L26 _public enumerator_ `OneParameterWithArgs`
- L27 _public enumerator_ `FourParameters`
- L28 _public enumerator_ `FourParametersWithArgs`

#### class `UVariantManagerBlueprintLibrary`  
`class UVariantManagerBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L35-257_
- reflection: `UCLASS(meta=(ScriptName="VariantManagerLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- desc: Library of functions that can be used by the Python API to trigger VariantManager operations
- L40 _private prototype_ `static FVariantManager& GetVariantManager();` — Gets or initializes and returns Variant Manager
- L46 _public prototype_ `static ULevelVariantSets* CreateLevelVariantSetsAsset(const FString& AssetName, const FString& AssetPath);` — `UFUNCTION(BlueprintCallable, Category = "VariantManager")` — Creates a new LevelVariantSetsAsset named AssetName (e.g. 'MyLevelVariantSets') in the content path AssetPath (e.g. '/Game')
- L50 _public prototype_ `static ALevelVariantSetsActor* CreateLevelVariantSetsActor(ULevelVariantSets* LevelVariantSetsAsset);` — `UFUNCTION(BlueprintCallable, Category = "VariantManager")` — Creates a new ALevelVariantSetsActor in the current scene and assigns LevelVariantSetsAsset to it
- L55 _public prototype_ `static TArray<FString> GetCapturableProperties(UObject* ActorOrClass);` — `UFUNCTION(BlueprintCallable, Category = "VariantManager")` — Returns a property path for all the properties we can capture for an actor. Will also handle receiving the actor's class instead.
- L62 _public prototype_ `static void AddVariantSet(ULevelVariantSets* LevelVariantSets, UVariantSet* VariantSet);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager")` — Adds VariantSet to the LevelVariantSets' list of VariantSets
- L66 _public prototype_ `static void AddVariant(UVariantSet* VariantSet, UVariant* Variant);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager")` — Adds Variant to the VariantSet's list of Variants
- L70 _public prototype_ `static void AddActorBinding(UVariant* Variant, AActor* Actor);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager")` — Binds the Actor to the Variant, internally creating a VariantObjectBinding
- L75 _public prototype_ `static UPropertyValue* CaptureProperty(UVariant* Variant, AActor* Actor, FString PropertyPath);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager")` — Finds the actor binding to Actor within Variant and tries capturing a property with PropertyPath Returns the captured UPropertyValue if succeeded or nullptr if it failed.
- L80 _public prototype_ `static int32 AddDependency(UVariant* Variant, UPARAM(ref) FVariantDependency& Dependency);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category="VariantManager")`
- L83 _public prototype_ `static void SetDependency(UVariant* Variant, int32 Index, UPARAM(ref) FVariantDependency& Dependency);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category="VariantManager")`
- L86 _public prototype_ `static void DeleteDependency(UVariant* Variant, int32 Index);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category="VariantManager")`
- L89 _public prototype_ `static TArray<FVariantDependency> GetDependencies(UVariant* Variant);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category="VariantManager")`
- L96 _public prototype_ `static TArray<UPropertyValue*> GetCapturedProperties(UVariant* Variant, AActor* Actor);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager")` — Returns which properties have been captured for this actor in Variant
- L103 _public prototype_ `static void RemoveVariantSet(ULevelVariantSets* LevelVariantSets, UVariantSet* VariantSet);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager")` — Removes VariantSet from LevelVariantSets, if that is its parent
- L107 _public prototype_ `static void RemoveVariant(UVariantSet* VariantSet, UVariant* Variant);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager")` — Removes Variant from VariantSet, if that is its parent
- L111 _public prototype_ `static void RemoveActorBinding(UVariant* Variant, AActor* Actor);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager")` — Removes an actor binding to Actor from Variant, if it exists
- L115 _public prototype_ `static void RemoveCapturedProperty(UVariant* Variant, AActor* Actor, UPropertyValue* Property);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager")` — Removes a property capture from an actor binding within Variant, if it exists
- L122 _public prototype_ `static void RemoveVariantSetByName(ULevelVariantSets* LevelVariantSets, const FString& VariantSetName);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager")` — Looks for a variant set with VariantSetName within LevelVariantSets and removes it, if it exists
- L126 _public prototype_ `static void RemoveVariantByName(UVariantSet* VariantSet, const FString& VariantName);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager")` — Looks for a variant with VariantName within VariantSet and removes it, if it exists
- L130 _public prototype_ `static void RemoveActorBindingByName(UVariant* Variant, const FString& ActorName);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager")` — Looks for an actor binding to an actor with ActorLabel within Variant and removes it, if it exists
- L134 _public prototype_ `static void RemoveCapturedPropertyByName(UVariant* Variant, AActor* Actor, FString PropertyPath);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager")` — Removes property capture with PropertyPath from Actor's binding within Variant, if it exists
- L141 _public prototype_ `static void Record(UPropertyValue* PropVal);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager")` — Records new data for PropVal from the actor from which it was captured
- L145 _public prototype_ `static void Apply(UPropertyValue* PropVal);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager")` — Applies the recorded data from PropVal to the actor from which it was captured
- L149 _public prototype_ `static FString GetPropertyTypeString(UPropertyValue* PropVal);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager")` — This allows the scripting language to get the type of the C++ property its dealing with
- L154 _public prototype_ `static void SetValueBool(UPropertyValue* Property, bool InValue);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager|PropertyAccessors")`
- L157 _public prototype_ `static bool GetValueBool(UPropertyValue* Property);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager|PropertyAccessors")`
- L160 _public prototype_ `static void SetValueInt(UPropertyValue* Property, int32 InValue);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager|PropertyAccessors")`
- L163 _public prototype_ `static int32 GetValueInt(UPropertyValue* Property);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager|PropertyAccessors")`
- L166 _public prototype_ `static void SetValueFloat(UPropertyValue* Property, float InValue);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager|PropertyAccessors")`
- L169 _public prototype_ `static float GetValueFloat(UPropertyValue* Property);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager|PropertyAccessors")`
- L172 _public prototype_ `static void SetValueObject(UPropertyValue* Property, UObject* InValue);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager|PropertyAccessors")`
- L175 _public prototype_ `static UObject* GetValueObject(UPropertyValue* Property);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager|PropertyAccessors")`
- L178 _public prototype_ `static void SetValueString(UPropertyValue* Property, const FString& InValue);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager|PropertyAccessors")`
- L181 _public prototype_ `static FString GetValueString(UPropertyValue* Property);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager|PropertyAccessors")`
- L184 _public prototype_ `static void SetValueRotator(UPropertyValue* Property, FRotator InValue);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager|PropertyAccessors")`
- L187 _public prototype_ `static FRotator GetValueRotator(UPropertyValue* Property);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager|PropertyAccessors")`
- L190 _public prototype_ `static void SetValueColor(UPropertyValue* Property, FColor InValue);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager|PropertyAccessors")`
- L193 _public prototype_ `static FColor GetValueColor(UPropertyValue* Property);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager|PropertyAccessors")`
- L196 _public prototype_ `static void SetValueLinearColor(UPropertyValue* Property, FLinearColor InValue);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager|PropertyAccessors")`
- L199 _public prototype_ `static FLinearColor GetValueLinearColor(UPropertyValue* Property);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager|PropertyAccessors")`
- L202 _public prototype_ `static void SetValueVector(UPropertyValue* Property, FVector InValue);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager|PropertyAccessors")`
- L205 _public prototype_ `static FVector GetValueVector(UPropertyValue* Property);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager|PropertyAccessors")`
- L208 _public prototype_ `static void SetValueQuat(UPropertyValue* Property, FQuat InValue);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager|PropertyAccessors")`
- L211 _public prototype_ `static FQuat GetValueQuat(UPropertyValue* Property);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager|PropertyAccessors")`
- L214 _public prototype_ `static void SetValueVector4(UPropertyValue* Property, FVector4 InValue);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager|PropertyAccessors")`
- L217 _public prototype_ `static FVector4 GetValueVector4(UPropertyValue* Property);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager|PropertyAccessors")`
- L220 _public prototype_ `static void SetValueVector2D(UPropertyValue* Property, FVector2D InValue);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager|PropertyAccessors")`
- L223 _public prototype_ `static FVector2D GetValueVector2D(UPropertyValue* Property);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager|PropertyAccessors")`
- L226 _public prototype_ `static void SetValueIntPoint(UPropertyValue* Property, FIntPoint InValue);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager|PropertyAccessors")`
- L229 _public prototype_ `static FIntPoint GetValueIntPoint(UPropertyValue* Property);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager|PropertyAccessors")`
- L232 _public prototype_ `static UBlueprint* GetOrCreateDirectorBlueprint(UVariant* Variant);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager|FunctionCallers")`
- L235 _public prototype_ `static TArray<FName> GetFunctionCallerNames(UVariant* Variant, AActor* Actor);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager|FunctionCallers")`
- L238 _public prototype_ `static bool GetFunctionCallerArguments(UVariant* Variant, AActor* Actor, FName FunctionName, TMap<FName, FString>& Arguments);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager|FunctionCallers")`
- L241 _public prototype_ `static bool CreateFunctionCaller(UVariant* Variant, AActor* Actor, FName FunctionName, EVariantFunctionCallerSignature Signature);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager|FunctionCallers")`
- L244 _public prototype_ `static bool AddFunctionCaller(UVariant* Variant, AActor* Actor, FName FunctionName);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager|FunctionCallers")`
- L247 _public prototype_ `static bool UpdateFunctionCallerArguments(UVariant* Variant, AActor* Actor, FName FunctionName, const TMap<FName, FString>& Arguments);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager|FunctionCallers")`
- L250 _public prototype_ `static bool RemoveFunctionCaller(UVariant* Variant, AActor* Actor, FName FunctionName);` — `UFUNCTION(BlueprintCallable, meta=(ScriptMethod), Category = "VariantManager|FunctionCallers")`
- L253 _private prototype_ `static bool CheckTheFunctionSignature(UVariant* Variant, AActor* BoundActor, FName FunctionName, EVariantFunctionCallerSignature Signature);`
- L256 _private member_ `static TUniquePtr<FVariantManager> VariantManager;`

### `Plugins/Enterprise/VariantManager/Source/VariantManager/Public/VariantManagerModule.h` (Public)


#### class `IVariantManagerModule`  
`class IVariantManagerModule : public IModuleInterface`  
_L12-26_
- inherits: `IModuleInterface`
- L15 _public function_ `static inline IVariantManagerModule& Get()`
- L20 _public function_ `static inline bool IsAvailable()`
- L25 _public prototype_ `virtual TSharedRef<FVariantManager> CreateVariantManager(ULevelVariantSets* InLevelVariantSets) = 0;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define VARIANTMANAGERMODULE_MODULE_NAME TEXT("VariantManager")`
