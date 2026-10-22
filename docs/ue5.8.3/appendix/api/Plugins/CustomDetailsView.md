# Plugins / CustomDetailsView

- module root: `Plugins/VirtualProduction/CustomDetailsView/Source/CustomDetailsView`
- headers: 19; symbols: 369
- symbol kinds: class=18, delegate=5, enum=6, enumerator=20, function=30, macro=1, member=67, namespace=10, prototype=208, struct=3, typedef=1
- PrivateDependencyModuleNames: Engine, PropertyEditor, ToolMenus, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, InputCore, Slate, SlateCore

### `Plugins/VirtualProduction/CustomDetailsView/Source/CustomDetailsView/Private/CustomDetailsViewRowExtensions.h` (Private)


#### class `FCustomDetailsViewRowExtensions`  
`class FCustomDetailsViewRowExtensions`  
_L12-29_
- L15 _public prototype_ `static FCustomDetailsViewRowExtensions& Get();`
- L17 _public prototype_ `~FCustomDetailsViewRowExtensions();`
- L19 _public prototype_ `void RegisterRowExtensions();`
- L21 _public prototype_ `void UnregisterRowExtensions();`
- L24 _private member_ `FDelegateHandle RowExtensionHandle;`
- L26 _private prototype_ `static void HandleCreatePropertyRowExtension(const FOnGenerateGlobalRowExtensionArgs& InArgs, TArray<FPropertyRowExtensionButton>& OutExtensions);`
- L28 _private prototype_ `static void FillPropertyRightClickMenu(UToolMenu* InToolMenu);`

### `Plugins/VirtualProduction/CustomDetailsView/Source/CustomDetailsView/Private/Items/CustomDetailsViewCustomCategoryItem.h` (Private)


#### class `FCustomDetailsViewCustomCategoryItem`  
`class FCustomDetailsViewCustomCategoryItem : public FCustomDetailsViewItemBase, public ICustomDetailsViewCustomCategoryItem`  
_L10-43_
- inherits: `FCustomDetailsViewItemBase,ICustomDetailsViewCustomCategoryItem`
- L13 _public prototype_ `explicit FCustomDetailsViewCustomCategoryItem(const TSharedRef<SCustomDetailsView>& InCustomDetailsView , const TSharedPtr<ICustomDetailsViewItem>& InParentItem, FName InCategoryName , const FText& InLabel, const FText& InToolTip);`
- L17 _public prototype_ `virtual ~FCustomDetailsViewCustomCategoryItem() override = default;`
- L19 _public function_ `FName GetCategoryName() const`
- L22 _public prototype_ `virtual void RefreshItemId() override;`
- L26 _public prototype_ `virtual void SetLabel(const FText& InLabel) override;`
- L27 _public prototype_ `virtual void SetToolTip(const FText& InToolTip) override;`
- L28 _public prototype_ `virtual TSharedRef<ICustomDetailsViewItem> AsItem() override;`
- L33 _protected prototype_ `virtual void InitWidget_Internal() override;`
- L36 _protected prototype_ `void CreateNameWidget();`
- L38 _protected member_ `FName CategoryName;`
- L40 _protected member_ `FText Label;`
- L42 _protected member_ `FText ToolTip;`

### `Plugins/VirtualProduction/CustomDetailsView/Source/CustomDetailsView/Private/Items/CustomDetailsViewCustomItem.h` (Private)


#### class `FCustomDetailsViewCustomItem`  
`class FCustomDetailsViewCustomItem : public FCustomDetailsViewItemBase, public ICustomDetailsViewCustomItem`  
_L10-47_
- inherits: `FCustomDetailsViewItemBase,ICustomDetailsViewCustomItem`
- L13 _public prototype_ `explicit FCustomDetailsViewCustomItem(const TSharedRef<SCustomDetailsView>& InCustomDetailsView , const TSharedPtr<ICustomDetailsViewItem>& InParentItem, FName InItemName , const FText& InLabel, const FText& InToolTip);`
- L17 _public prototype_ `virtual ~FCustomDetailsViewCustomItem() override = default;`
- L19 _public function_ `FName GetItemName() const`
- L22 _public prototype_ `virtual void RefreshItemId() override;`
- L26 _public prototype_ `virtual void SetNodeType(TOptional<EDetailNodeType> InNodeType) override;`
- L27 _public prototype_ `virtual void SetLabel(const FText& InLabel) override;`
- L28 _public prototype_ `virtual void SetToolTip(const FText& InToolTip) override;`
- L29 _public prototype_ `virtual void SetValueWidget(const TSharedRef<SWidget>& InValueWidget) override;`
- L30 _public prototype_ `virtual void SetExpansionWidget(const TSharedRef<SWidget>& InExpansionWidget) override;`
- L31 _public prototype_ `virtual void SetWholeRowWidget(const TSharedRef<SWidget>& InWholeRowWidget) override;`
- L32 _public prototype_ `virtual TSharedRef<ICustomDetailsViewItem> AsItem() override;`
- L37 _protected prototype_ `virtual void InitWidget_Internal() override;`
- L40 _protected prototype_ `void CreateNameWidget();`
- L42 _protected member_ `FName ItemName;`
- L44 _protected member_ `FText Label;`
- L46 _protected member_ `FText ToolTip;`

### `Plugins/VirtualProduction/CustomDetailsView/Source/CustomDetailsView/Private/Items/CustomDetailsViewDetailTreeNodeItem.h` (Private)


#### class `FCustomDetailsViewDetailTreeNodeItem`  
`class FCustomDetailsViewDetailTreeNodeItem : public FCustomDetailsViewItemBase`  
_L21-110_
- inherits: `FCustomDetailsViewItemBase`
- L24 _public prototype_ `explicit FCustomDetailsViewDetailTreeNodeItem(const TSharedRef<SCustomDetailsView>& InCustomDetailsView , const TSharedPtr<ICustomDetailsViewItem>& InParentItem , const TSharedPtr<IDetailTreeNode>& InDetailTreeNode);`
- L32 _public prototype_ `virtual TSharedPtr<IDetailsView> GetDetailsView() const override;`
- L33 _public prototype_ `virtual void RefreshItemId() override;`
- L34 _public function_ `virtual const TArray<TSharedPtr<ICustomDetailsViewItem>>& GetChildren() const override final`
- L35 _public prototype_ `virtual void SetResetToDefaultOverride(const FResetToDefaultOverride& InOverride) override;`
- L36 _public prototype_ `virtual void CreateGlobalExtensionButtons(TArray<FPropertyRowExtensionButton>& OutExtensionButtons) override;`
- L37 _public prototype_ `virtual bool CreateResetToDefaultButton(FPropertyRowExtensionButton& OutButton) override;`
- L38 _public prototype_ `virtual void SetCreateChildItemDelegate(FOnCustomDetailsViewGenerateChildItem InDelegate) override;`
- L39 _public prototype_ `virtual void SetCustomizeItemMenuContext(FOnCustomDetailsViewCustomizeItemMenuContext InDelegate) override;`
- L43 _public prototype_ `virtual void AddExtensionWidget(const TSharedRef<SSplitter>& InSplitter , const FDetailColumnSizeData& InColumnSizeData , const FCustomDetailsViewArgs& InViewArgs) override;`
- L47 _public prototype_ `virtual TSharedRef<SWidget> MakeEditConditionWidget() override;`
- L50 _public prototype_ `bool HasEditConditionToggle() const;`
- L51 _public prototype_ `EVisibility GetEditConditionVisibility() const;`
- L52 _public prototype_ `ECheckBoxState GetEditConditionCheckState() const;`
- L53 _public prototype_ `void OnEditConditionCheckChanged(ECheckBoxState InCheckState);`
- L55 _public prototype_ `void OnKeyframeClicked();`
- L56 _public prototype_ `bool IsKeyframeVisible() const;`
- L58 _public prototype_ `bool IsResetToDefaultVisible() const;`
- L59 _public prototype_ `void UpdateResetToDefault(float InDeltaTime);`
- L61 _public prototype_ `void OnResetToDefaultClicked();`
- L62 _public prototype_ `bool CanResetToDefault() const;`
- L64 _public prototype_ `FText GetResetToDefaultToolTip() const;`
- L65 _public prototype_ `FSlateIcon GetResetToDefaultIcon() const;`
- L67 _public function_ `TSharedPtr<IDetailTreeNode> GetRowTreeNode() const`
- L72 _public function_ `TSharedPtr<IPropertyHandle> GetRowPropertyHandle() const`
- L78 _protected prototype_ `void AddChildDetailsTreeNodes(const TSharedRef<ICustomDetailsViewItem>& InParentItem, ECustomDetailsViewNodePropertyFlag InNodeChildPropertyFlag, const TArray<TSharedRef<IDetailTreeNode>>& InNodeChildren, TArray<TSharedPtr<ICustomDetailsViewItem>>& OutChildren);`
- L81 _protected prototype_ `bool IsStruct() const;`
- L83 _protected prototype_ `bool HasParentStruct() const;`
- L87 _protected prototype_ `virtual void InitWidget_Internal() override;` — Generate details context menu based on property handle
- L88 _protected prototype_ `virtual void UpdateVisibility() override;`
- L89 _protected prototype_ `virtual TSharedPtr<SWidget> GenerateContextMenuWidget() override;`
- L90 _protected prototype_ `virtual void GenerateCustomChildren(const TSharedRef<ICustomDetailsViewItem>& InParentItem, TArray<TSharedPtr<ICustomDetailsViewItem>>& OutChildren) override;`
- L94 _protected member_ `TSharedPtr<IPropertyHandle> PropertyHandle;` — The Property Handle of this Detail Tree Node. Can be null
- L97 _protected member_ `TWeakPtr<IDetailTreeNode> DetailTreeNodeWeak;` — Weak pointer to the Detail Tree Node this Item represents
- L100 _protected member_ `FDelegateHandle UpdateResetToDefaultHandle;` — Handle to the delegate handling Updating Reset To Default Visibility State Post Slate App Tick
- L103 _protected member_ `bool bResetToDefaultVisible = false;` — Cached value of the visibility state of the ResetToDefault Widget
- L106 _protected member_ `FOnCustomDetailsViewGenerateChildItem ChildItemDelegate;` — Used for custom child property rows.
- L109 _protected member_ `FOnCustomDetailsViewCustomizeItemMenuContext ContextMenuDelegate;` — Used to customize the context menu

### `Plugins/VirtualProduction/CustomDetailsView/Source/CustomDetailsView/Private/Items/CustomDetailsViewItemBase.h` (Private)


#### class `FCustomDetailsViewItemBase`  
`class FCustomDetailsViewItemBase : public ICustomDetailsViewItem`  
_L27-147_
- inherits: `ICustomDetailsViewItem`
- L30 _public prototype_ `explicit FCustomDetailsViewItemBase(const TSharedRef<SCustomDetailsView>& InCustomDetailsView, const TSharedPtr<ICustomDetailsViewItem>& InParentItem = nullptr);`
- L33 _public prototype_ `virtual ~FCustomDetailsViewItemBase() override = default;`
- L35 _public prototype_ `void UpdateIndentLevel();`
- L38 _public prototype_ `virtual void InitWidget() override;`
- L39 _public prototype_ `virtual TSharedPtr<ICustomDetailsView> GetCustomDetailsView() const override;`
- L40 _public function_ `virtual TSharedPtr<IDetailsView> GetDetailsView() const override`
- L41 _public prototype_ `virtual const FCustomDetailsViewItemId& GetItemId() const override final;`
- L42 _public prototype_ `virtual TSharedPtr<ICustomDetailsViewItem> GetRoot() const override;`
- L43 _public prototype_ `virtual TSharedPtr<ICustomDetailsViewItem> GetParent() const override;`
- L44 _public prototype_ `virtual void SetParent(TSharedPtr<ICustomDetailsViewItem> InParent) override;`
- L45 _public prototype_ `virtual const TArray<TSharedPtr<ICustomDetailsViewItem>>& GetChildren() const override;`
- L46 _public prototype_ `virtual void RefreshChildren(TSharedPtr<ICustomDetailsViewItem> InParentOverride = nullptr) override;`
- L47 _public prototype_ `virtual TOptional<EDetailNodeType> GetNodeType() const override;`
- L48 _public prototype_ `virtual void AddAsChild(const TSharedRef<ICustomDetailsViewItem>& InParentItem, TArray<TSharedPtr<ICustomDetailsViewItem>>& OutChildren) override;`
- L49 _public prototype_ `virtual TSharedRef<SWidget> MakeWidget(const TSharedPtr<SWidget>& InPrependWidget, const TSharedPtr<SWidget>& InOwningWidget) override;`
- L50 _public prototype_ `virtual TSharedPtr<SWidget> GetWidget(ECustomDetailsViewWidgetType InWidgetType) const override;`
- L51 _public prototype_ `virtual TSharedPtr<SWidget> GetOverrideWidget(ECustomDetailsViewWidgetType InWidgetType) const override;`
- L52 _public prototype_ `virtual void SetOverrideWidget(ECustomDetailsViewWidgetType InWidgetType, TSharedPtr<SWidget> InWidget) override;`
- L53 _public prototype_ `virtual void SetKeyframeEnabled(bool bInKeyframeEnabled) override;`
- L54 _public function_ `virtual void SetResetToDefaultOverride(const FResetToDefaultOverride& InOverride) override`
- L55 _public prototype_ `virtual bool IsWidgetVisible() const override;`
- L56 _public prototype_ `virtual void SetValueWidgetWidthOverride(TOptional<float> InWidth) override;`
- L57 _public prototype_ `virtual void SetEnabledOverride(TAttribute<bool> InOverride) override;`
- L58 _public prototype_ `virtual const FDetailWidgetRow& GetDetailWidgetRow() const override;`
- L59 _public prototype_ `virtual bool CreateResetToDefaultButton(FPropertyRowExtensionButton& OutButton) override;`
- L60 _public prototype_ `virtual void CreateGlobalExtensionButtons(TArray<FPropertyRowExtensionButton>& OutExtensionButtons) override;`
- L61 _public prototype_ `virtual TSharedRef<SWidget> CreateExtensionButtonWidget(const TArray<FPropertyRowExtensionButton>& InExtensionButtons) override;`
- L62 _public function_ `virtual void SetCreateChildItemDelegate(FOnCustomDetailsViewGenerateChildItem InDelegate) override` — No default implementation
- L63 _public function_ `virtual void SetCustomizeItemMenuContext(FOnCustomDetailsViewCustomizeItemMenuContext InDelegate) override` — No default implementation
- L66 _public prototype_ `virtual void AddWholeRowWidget(const TSharedRef<SSplitter>& InSplitter , const TSharedPtr<SWidget>& InPrependWidget , const FDetailColumnSizeData& InColumnSizeData , const FMargin& InPadding);`
- L71 _public prototype_ `virtual void AddNameWidget(const TSharedRef<SSplitter>& InSplitter , const TSharedPtr<SWidget>& InPrependWidget , const FDetailColumnSizeData& InColumnSizeData , const FMargin& InPadding);`
- L76 _public prototype_ `virtual void AddValueWidget(const TSharedRef<SSplitter>& InSplitter , const FDetailColumnSizeData& InColumnSizeData , const FMargin& InPadding);`
- L80 _public prototype_ `virtual void AddExtensionWidget(const TSharedRef<SSplitter>& InSplitter , const FDetailColumnSizeData& InColumnSizeData , const FCustomDetailsViewArgs& InViewArgs);`
- L84 _public prototype_ `TSharedPtr<IDetailKeyframeHandler> GetKeyframeHandler() const;`
- L86 _public prototype_ `bool CanKeyframe() const;`
- L88 _public prototype_ `virtual TSharedRef<SWidget> MakeEditConditionWidget();`
- L91 _protected prototype_ `FReply OnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent);`
- L93 _protected prototype_ `TArray<TSharedPtr<ICustomDetailsViewItem>> GenerateChildren(const TSharedRef<ICustomDetailsViewItem>& InParentItem);`
- L95 _protected function_ `virtual void InitWidget_Internal()`
- L97 _protected prototype_ `virtual void UpdateVisibility();`
- L101 _protected function_ `virtual TSharedPtr<SWidget> GenerateContextMenuWidget()` — Generate optional context menu on row right click
- L106 _protected function_ `virtual void GenerateCustomChildren(const TSharedRef<ICustomDetailsViewItem>& InParentItem, TArray<TSharedPtr<ICustomDetailsViewItem>>& OutChildren)`
- L108 _protected prototype_ `virtual void GatherChildren(const TSharedRef<ICustomDetailsViewItem>& InParentItem, const UE::CustomDetailsView::FTreeExtensionType& InTreeExtensions, ECustomDetailsTreeInsertPosition InPosition, TArray<TSharedPtr<ICustomDetailsViewItem>>& OutChildren) override;`
- L113 _protected member_ `TWeakPtr<SCustomDetailsView> CustomDetailsViewWeak;` — Weak pointer to the Entity View holding this Item
- L116 _protected member_ `TWeakPtr<ICustomDetailsViewItem> ParentWeak;` — Weak pointer to the Parent Item
- L119 _protected member_ `FCustomDetailsViewItemId ItemId;` — The Identifier for this Item
- L122 _protected member_ `TArray<TSharedPtr<ICustomDetailsViewItem>> Children;` — Cached list of Children gotten since this Item was last refreshed/generated
- L125 _protected member_ `TMap<ECustomDetailsViewWidgetType, TSharedPtr<SWidget>> Widgets;` — The Widgets generated for each Widget Type
- L128 _protected member_ `TMap<ECustomDetailsViewWidgetType, TSharedRef<SWidget>> OverrideWidgets;` — Widgets set by the user to override automatically generated widgets
- L131 _protected member_ `TOptional<EDetailNodeType> NodeType;` — The Node Type of the Detail Tree Node. Can be unset if Detail Tree Node was never valid
- L134 _protected member_ `FDetailWidgetRow DetailWidgetRow;` — The Widget Row information Retrieved from the Detail Tree Node
- L137 _protected member_ `int32 IndentLevel = -1;` — Calculated Indent Level based on Hierarchy
- L140 _protected member_ `bool bKeyframeEnabled = true;` — If false, the keyframe button for this widget will never display.
- L143 _protected member_ `TOptional<float> ValueWidthOverride;` — Overrides the create value widget's maximum width, if set.
- L146 _protected member_ `TAttribute<bool> EnabledOverride;` — Set to give custom enabled override.

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace CustomDetailsView` (scope `UE`)
- L22 _namespace_ `namespace Private` (scope `UE::CustomDetailsView`)
- L24 _prototype_ `TAttribute<FOptionalSize> GetOptionalSize(const TOptional<float>& InOptional);` (scope `UE::CustomDetailsView::Private`)

### `Plugins/VirtualProduction/CustomDetailsView/Source/CustomDetailsView/Private/Items/CustomDetailsViewRootItem.h` (Private)


#### class `FCustomDetailsViewRootItem`  
`class FCustomDetailsViewRootItem : public FCustomDetailsViewDetailTreeNodeItem, public ICustomDetailsViewBase`  
_L10-42_
- inherits: `FCustomDetailsViewDetailTreeNodeItem,ICustomDetailsViewBase`
- L13 _public prototype_ `explicit FCustomDetailsViewRootItem(const TSharedRef<SCustomDetailsView>& InCustomDetailsView);`
- L18 _public prototype_ `virtual void RefreshItemId() override;`
- L19 _public prototype_ `virtual void RefreshChildren(TSharedPtr<ICustomDetailsViewItem> InParentOverride = nullptr) override;`
- L20 _public prototype_ `virtual TSharedRef<SWidget> MakeWidget(const TSharedPtr<SWidget>& InPrependWidget, const TSharedPtr<SWidget>& InOwningWidget) override;`
- L21 _public prototype_ `virtual TSharedPtr<SWidget> GetWidget(ECustomDetailsViewWidgetType InWidgetType) const override;`
- L25 _public prototype_ `virtual void SetObject(UObject* InObject) override;`
- L26 _public prototype_ `virtual void SetObjects(const TArray<UObject*>& InObjects) override;`
- L27 _public prototype_ `virtual void SetStruct(const TSharedPtr<FStructOnScope>& InStruct) override;`
- L28 _public prototype_ `virtual bool FilterItems(const TArray<FString>& InFilterStrings) override;`
- L33 _private prototype_ `virtual void InitWidget_Internal() override;`
- L34 _private prototype_ `virtual void GenerateCustomChildren(const TSharedRef<ICustomDetailsViewItem>& InParentItem, TArray<TSharedPtr<ICustomDetailsViewItem>>& OutChildren) override;`
- L37 _private member_ `TSharedPtr<IPropertyRowGenerator> PropertyRowGenerator;`
- L39 _private member_ `FDelegateHandle OnRowsRefreshedHandle;`
- L41 _private member_ `FDelegateHandle OnFinishedChangeHandle;`

### `Plugins/VirtualProduction/CustomDetailsView/Source/CustomDetailsView/Private/SCustomDetailsView.h` (Private)


#### enum `UE::CustomDetailsView::Private::EAllowType`  
`enum class EAllowType : uint8`  
_L21-26_
- L23 _public enumerator_ `Allowed`
- L24 _public enumerator_ `DisallowSelf`
- L25 _public enumerator_ `DisallowSelfAndChildren`

#### class `SCustomDetailsView`  
`class SCustomDetailsView : public ICustomDetailsView`  
_L29-109_
- inherits: `ICustomDetailsView`
- L32 _public function_ `SLATE_BEGIN_ARGS(SCustomDetailsView)`
- L33 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FCustomDetailsViewArgs& InCustomDetailsViewArgs);`
- L39 _public function_ `TSharedRef<InItemType> CreateItem(InArgTypes&&... InArgs)`
- L47 _public prototype_ `void Refresh();`
- L49 _public prototype_ `void OnTreeViewRegenerated();`
- L51 _public prototype_ `void OnFinishedChangingProperties(const FPropertyChangedEvent& InPropertyChangedEvent);`
- L53 _public prototype_ `UE::CustomDetailsView::Private::EAllowType GetAllowType(const TSharedRef<ICustomDetailsViewItem>& InParentItem, const TSharedRef<IDetailTreeNode>& InDetailTreeNode, ECustomDetailsViewNodePropertyFlag InNodePropertyFlags) const;`
- L56 _public prototype_ `void OnGetChildren(TSharedPtr<ICustomDetailsViewItem> InItem, TArray<TSharedPtr<ICustomDetailsViewItem>>& OutChildren) const;`
- L58 _public prototype_ `void OnExpansionChanged(TSharedPtr<ICustomDetailsViewItem> InItem, bool bInExpanded);`
- L60 _public prototype_ `DLLEXPORT void SetExpansionRecursive(TSharedPtr<ICustomDetailsViewItem> InItem, bool bInExpand);`
- L62 _public prototype_ `bool ShouldItemExpand(const TSharedPtr<ICustomDetailsViewItem>& InItem) const;`
- L64 _public prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<ICustomDetailsViewItem> InItem, const TSharedRef<STableViewBase>& InOwnerTable) const;`
- L66 _public function_ `const FCustomDetailsViewArgs& GetViewArgs() const`
- L69 _public prototype_ `virtual void SetObject(UObject* InObject) override;`
- L70 _public prototype_ `virtual void SetObjects(const TArray<UObject*>& InObjects) override;`
- L71 _public prototype_ `virtual void SetStruct(const TSharedPtr<FStructOnScope>& InStruct) override;`
- L75 _public prototype_ `virtual TSharedRef<ICustomDetailsViewItem> GetRootItem() const override;`
- L76 _public prototype_ `virtual TSharedPtr<ICustomDetailsViewItem> FindItem(const FCustomDetailsViewItemId& InItemId) const override;`
- L77 _public prototype_ `virtual TSharedRef<STreeView<TSharedPtr<ICustomDetailsViewItem>>> MakeSubTree(const TArray<TSharedPtr<ICustomDetailsViewItem>>* InSourceItems) const override;`
- L78 _public prototype_ `virtual void RebuildTree(ECustomDetailsViewBuildType InBuildType) override;`
- L79 _public prototype_ `virtual void ExtendTree(FCustomDetailsViewItemId InHook, ECustomDetailsTreeInsertPosition InPosition, TSharedRef<ICustomDetailsViewItem> InItem) override;`
- L80 _public prototype_ `virtual const UE::CustomDetailsView::FTreeExtensionType& GetTreeExtensions(FCustomDetailsViewItemId InHook) const override;`
- L81 _public prototype_ `virtual TSharedRef<ICustomDetailsViewItem> CreateDetailTreeItem(TSharedRef<ICustomDetailsViewItem> InParent, TSharedRef<IDetailTreeNode> InDetailTreeNode) override;`
- L82 _public prototype_ `virtual TSharedPtr<ICustomDetailsViewCustomItem> CreateCustomItem(TSharedRef<ICustomDetailsViewItem> InParent, FName InItemName, const FText& InLabel = FText::GetEmpty(), const FText& InToolTip = FText::GetEmpty()) override;`
- L83 _public prototype_ `virtual TSharedPtr<ICustomDetailsViewCustomCategoryItem> CreateCustomCategoryItem(TSharedRef<ICustomDetailsViewItem> InParent, FName InItemName, const FText& InLabel = FText::GetEmpty(), const FText& InToolTip = FText::GetEmpty()) override;`
- L84 _public prototype_ `virtual TSharedPtr<ICustomDetailsViewItem> FindCustomItem(const FName& InItemName) const override;`
- L85 _public prototype_ `virtual bool FilterItems(const TArray<FString>& InFilterStrings) override;`
- L86 _public prototype_ `virtual bool GetItemExpansionState(const FCustomDetailsViewItemId& InItemId, ECustomDetailsViewExpansion& OutExpansion) const override;`
- L87 _public prototype_ `virtual void SetItemExpansionState(const FCustomDetailsViewItemId& InItemId, ECustomDetailsViewExpansion InExpansion) override;`
- L91 _private prototype_ `bool ShouldRebuildImmediately(ECustomDetailsViewBuildType InBuildType) const;`
- L94 _private member_ `TSharedPtr<FCustomDetailsViewRootItem> RootItem;` — Single Root of Tree, not part of the visual part Tree Widget, but provides things like the Root Items (i.e. its Children)
- L96 _private member_ `TMap<FName, TSharedRef<ICustomDetailsViewItem>> AddedCustomItems;`
- L98 _private member_ `TMap<FCustomDetailsViewItemId, TSharedRef<ICustomDetailsViewItem>> ItemMap;`
- L100 _private member_ `TSharedPtr<SCustomDetailsTreeView> ViewTree;`
- L102 _private member_ `FCustomDetailsViewArgs ViewArgs;`
- L104 _private member_ `bool bPendingRebuild = true;`
- L106 _private member_ `TMap<FCustomDetailsViewItemId, UE::CustomDetailsView::FTreeExtensionType> ExtensionMap;`
- L108 _private member_ `TSharedPtr<FSlateBrush> BackgroundBrush;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace CustomDetailsView` (scope `UE`)
- L19 _namespace_ `namespace Private` (scope `UE::CustomDetailsView`)

### `Plugins/VirtualProduction/CustomDetailsView/Source/CustomDetailsView/Private/Slate/SCustomDetailsTreeView.h` (Private)


#### class `SCustomDetailsTreeView`  
`class SCustomDetailsTreeView : public STreeView<TSharedPtr<ICustomDetailsViewItem>>`  
_L11-22_
- inherits: `STreeView<TSharedPtr<ICustomDetailsViewItem>>`
- L14 _public prototype_ `void SetCustomDetailsView(const TSharedRef<SCustomDetailsView>& InCustomDetailsView);`
- L17 _public prototype_ `virtual FReGenerateResults ReGenerateItems(const FGeometry& MyGeometry) override;`
- L21 _private member_ `TWeakPtr<SCustomDetailsView> CustomDetailsViewWeak;`

### `Plugins/VirtualProduction/CustomDetailsView/Source/CustomDetailsView/Private/Slate/SCustomDetailsViewItemRow.h` (Private)


#### class `SCustomDetailsViewItemRow`  
`class SCustomDetailsViewItemRow : public STableRow<TSharedPtr<ICustomDetailsViewItem>>`  
_L12-29_
- inherits: `STableRow<TSharedPtr<ICustomDetailsViewItem>>`
- L15 _public function_ `SLATE_BEGIN_ARGS(SCustomDetailsViewItemRow)`
- L16 _public prototype_ `SLATE_ARGUMENT(STableRow<TSharedPtr<ICustomDetailsViewItem>>::FArguments, TableRowArgs) SLATE_END_ARGS() void Construct(const FArguments& InArgs , const TSharedRef<STableViewBase>& InOwnerTable , const TSharedPtr<ICustomDetailsViewItem>& InItem , const FCustomDetailsViewArgs& InViewArgs);`
- L25 _public prototype_ `virtual void ConstructChildren(ETableViewMode::Type InOwnerTableMode , const TAttribute<FMargin>& InPadding , const TSharedRef<SWidget>& InContent) override;`

### `Plugins/VirtualProduction/CustomDetailsView/Source/CustomDetailsView/Public/CustomDetailsViewArgs.h` (Public)


#### struct `UE::CustomDetailsView::CContainerKeyable`  
`struct CContainerKeyable`  
_L30-37_
- desc: Describes a type that can be used as a Key in a Container (Set/Map). Requires a GetTypeHash overload and be Equality Comparable NOTE: Equality Comparable is required so for A and B both of type T, not only does A==B need to be implemented, but also A!=B, even though Containers like Sets/Maps only require operator==
- L33 _public prototype_ `template <typename T> auto Requires() -> decltype( Refines<CEqualityComparable, T>(), Refines<CGetTypeHashable, T>() );`

#### class `UE::CustomDetailsView::TAllowList`  
`template<typename InItemType, typename = typename TEnableIf<TModels<CContainerKeyable, InItemType>::Value>::Type> class TAllowList`  
_L45-80_
- desc: Has similar approach to FSceneView's Show / Hidden Primitives list, in that there's: Allowed Items: Anything not in this list is not allowed. This only applies if this is set (set via calling Allow(...)) Disallowed Items: Anything in this list will not be allowed, even if it is on the Allowed Item List
- L48 _public function_ `void Allow(const InItemType& InItem)`
- L57 _public function_ `void ResetAllowedItems()`
- L62 _public function_ `void Disallow(const InItemType& InItem)`
- L67 _public function_ `void ResetDisallowedList()`
- L72 _public function_ `bool IsAllowed(const InItemType& InItem) const`
- L78 _private member_ `TOptional<TSet<InItemType>> AllowedItems;`
- L79 _private member_ `TSet<InItemType> DisallowedItems;`

#### enum `ECustomDetailsViewWidgetType`  
`enum class ECustomDetailsViewWidgetType`  
_L84-90_
- desc: The types of Widget this Custom Details View deals with
- L86 _public enumerator_ `Name`
- L87 _public enumerator_ `Value`
- L88 _public enumerator_ `WholeRow`
- L89 _public enumerator_ `Extensions`

#### enum `ECustomDetailsViewExpansion`  
`enum class ECustomDetailsViewExpansion : uint8`  
_L93-98_
- desc: Expansion state allowed for an item
- L95 _public enumerator_ `Collapsed`
- L96 _public enumerator_ `SelfExpanded`
- L97 _public enumerator_ `SelfAndChildrenExpanded`

#### struct `FCustomDetailsViewArgs`  
`struct FCustomDetailsViewArgs`  
_L100-174_
- L103 _public member_ `UE::CustomDetailsView::TAllowList<FName> CategoryAllowList;` — List of Allowed and Disallowed Categories
- L106 _public member_ `UE::CustomDetailsView::TAllowList<FCustomDetailsViewItemId> ItemAllowList;` — List of Allowed and Disallowed Items based on their Id
- L109 _public member_ `UE::CustomDetailsView::TAllowList<ECustomDetailsViewWidgetType> WidgetTypeAllowList;` — List of Allowed Widget Types
- L112 _public member_ `bool bDefaultItemsExpanded = false;` — The default expansion state if not overriden by the Expansion State map below
- L115 _public member_ `TMap<FCustomDetailsViewItemId, ECustomDetailsViewExpansion> ExpansionState;` — Map of the Node Name to their Expanded State
- L117 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnExpansionStateChanged, const TSharedRef<ICustomDetailsViewItem>&, bool) FOnExpansionStateChanged OnExpansionStateChanged;`
- L121 _public member_ `float ValueColumnWidth = 0.6f;` — Default value column width, as a percentage, 0-1.
- L124 _public member_ `float RightColumnMinWidth = 40.f;` — Minimum width of the right column in Slate units.
- L130 _public member_ `TSharedPtr<FDetailColumnSizeData> ColumnSizeData;` — Optional: Set a Column Size Data to use. If null, Custom Details will instantiate one separately. This is recommended when dealing with multiple Custom Details Views that want to synchronize Column Sizes
- L133 _public member_ `TSharedPtr<SScrollBar> ExternalScrollBar;` — Optional external Scroll bar to use for the Tree
- L136 _public member_ `FPropertyRowGeneratorArgs RowGeneratorArgs;` — Arguments used for the Property Row Generator
- L139 _public member_ `TSharedPtr<IDetailKeyframeHandler> KeyframeHandler;` — The Keyframe Handler to use. bAllowGlobalExtensions must be set to true
- L142 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnItemWidgetGenerated, TSharedPtr<ICustomDetailsViewItem>);` — Delegate called everytime a Widget has been generated for a given Item
- L143 _public member_ `FOnItemWidgetGenerated OnItemWidgetGenerated;`
- L146 _public member_ `FSimpleMulticastDelegate OnTreeViewRegenerated;` — Delegate called when all the widgets in the Main Tree View has been regenerated
- L149 _public member_ `FOnFinishedChangingProperties OnFinishedChangingProperties;` — Delegate called when Properties have finished changing
- L152 _public member_ `FMargin DefaultPadding = FMargin(5.f, 2.f);` — The Padding to use for each Widget (Name, Value, etc)
- L155 _public member_ `float IndentAmount = 10.f;` — Amount of indentation to make per level in the Details View Tree
- L158 _public member_ `float TableBackgroundOpacity = 1.f;` — Opacity for the Table Background Panel
- L161 _public member_ `float RowBackgroundOpacity = 1.f;` — Opacity for the Row Background Panel
- L164 _public member_ `bool bShowCategories = true;` — Whether to show Categories
- L167 _public member_ `bool bAllowResetToDefault = true;` — Whether to allow Reset to Default to be added in
- L170 _public member_ `bool bAllowGlobalExtensions = false;` — Whether to allow Global Extensions to be added
- L173 _public member_ `bool bExcludeStructChildPropertiesFromFilters = true;` — Whether to exclude struct child properties, and their children, from filters.

#### enum `ECustomDetailsViewNodePropertyFlag`  
`enum class ECustomDetailsViewNodePropertyFlag : uint8`  
_L176-182_
- L178 _public enumerator_ `None = 0`
- L181 _public enumerator_ `HasParentStruct = 1 << 0` — A parent node of this property is a struct property.

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace CustomDetailsView` (scope `UE`)
- L117 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnExpansionStateChanged, const TSharedRef<ICustomDetailsViewItem>&, bool) FOnExpansionStateChanged OnExpansionStateChanged;`
- L142 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnItemWidgetGenerated, TSharedPtr<ICustomDetailsViewItem>);` — Delegate called everytime a Widget has been generated for a given Item
- L183 _prototype_ `ENUM_CLASS_FLAGS(ECustomDetailsViewNodePropertyFlag);`

### `Plugins/VirtualProduction/CustomDetailsView/Source/CustomDetailsView/Public/CustomDetailsViewFwd.h` (Public)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace CustomDetailsView` (scope `UE`)
- L15 _typedef_ `using FTreeExtensionType = TMap<ECustomDetailsTreeInsertPosition, TArray<TSharedPtr<ICustomDetailsViewItem>>>;` (scope `UE::CustomDetailsView`)

### `Plugins/VirtualProduction/CustomDetailsView/Source/CustomDetailsView/Public/CustomDetailsViewMenuContext.h` (Public)


#### class `UCustomDetailsViewMenuContext`  
`class UCustomDetailsViewMenuContext : public UObject`  
_L10-13_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`

### `Plugins/VirtualProduction/CustomDetailsView/Source/CustomDetailsView/Public/CustomDetailsViewModule.h` (Public)


#### class `ICustomDetailsViewModule`  
`class ICustomDetailsViewModule : public IModuleInterface`  
_L11-25_
- inherits: `IModuleInterface`
- L14 _public function_ `static ICustomDetailsViewModule& Get()`
- L19 _public function_ `static bool IsLoaded()`
- L24 _public prototype_ `virtual TSharedRef<ICustomDetailsView> CreateCustomDetailsView(const FCustomDetailsViewArgs& InArgs) = 0;`

### `Plugins/VirtualProduction/CustomDetailsView/Source/CustomDetailsView/Public/CustomDetailsViewSequencer.h` (Public)


#### struct `FCustomDetailsViewSequencerUtils`  
`struct FCustomDetailsViewSequencerUtils`  
_L16-25_
- L18 _public prototype_ `DECLARE_DELEGATE_RetVal(TSharedPtr<IDetailKeyframeHandler>, FGetKeyframeHandlerDelegate);`
- L20 _public prototype_ `static void CreateSequencerExtensionButton(const FGetKeyframeHandlerDelegate& InKeyframeHandlerDelegate, TSharedPtr<IPropertyHandle> InPropertyHandle, TArray<FPropertyRowExtensionButton>& OutExtensionButtons);`
- L23 _public prototype_ `static void CreateSequencerExtensionButton(TWeakPtr<IDetailKeyframeHandler> InKeyframeHandlerWeak, TSharedPtr<IPropertyHandle> InPropertyHandle, TArray<FPropertyRowExtensionButton>& OutExtensionButtons);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CUSTOMDETAILSVIEW_API`
- L18 _delegate_ `DECLARE_DELEGATE_RetVal(TSharedPtr<IDetailKeyframeHandler>, FGetKeyframeHandlerDelegate);`

### `Plugins/VirtualProduction/CustomDetailsView/Source/CustomDetailsView/Public/ICustomDetailsView.h` (Public)


#### enum `ECustomDetailsViewBuildType`  
`enum class ECustomDetailsViewBuildType : uint8`  
_L18-26_
- L21 _public enumerator_ `Auto` — Custom Details View determines whether it should Build Instantly or Deferred
- L23 _public enumerator_ `InstantBuild` — Force an Instant Build. Useful for when you want to see the results of the Build right after
- L25 _public enumerator_ `DeferredBuild` — Defer the Build to a later point in time. Useful to avoid having to rebuild multiple times (e.g. when resizing the widget containing the tree view)

#### enum `ECustomDetailsTreeInsertPosition`  
`enum class ECustomDetailsTreeInsertPosition : uint8`  
_L28-40_
- L31 _public enumerator_ `Before` — Adds an item into the hierarchy on the same level as the current item but before it in the order.
- L33 _public enumerator_ `After` — Adds an item into the hierarchy on the same level as the current item but after it in the order.
- L35 _public enumerator_ `FirstChild` — Prepends an item to the current item's child items.
- L37 _public enumerator_ `Child` — Appends an item to the current item's child items.
- L39 _public enumerator_ `LastChild` — Appends an item to the current item's child items, but after the list above.

#### class `ICustomDetailsViewBase`  
`class ICustomDetailsViewBase`  
_L42-59_
- L45 _public prototype_ `virtual ~ICustomDetailsViewBase() = default;`
- L47 _public prototype_ `virtual void SetObject(UObject* InObject) = 0;`
- L49 _public prototype_ `virtual void SetObjects(const TArray<UObject*>& InObjects) = 0;`
- L51 _public prototype_ `virtual void SetStruct(const TSharedPtr<FStructOnScope>& InStruct) = 0;`
- L58 _public prototype_ `virtual bool FilterItems(const TArray<FString>& InFilterStrings) = 0;` — Applies a row filter on this tree items, returns true when filter found something returns false when no rows passed filters

#### class `ICustomDetailsView`  
`class ICustomDetailsView : public SCompoundWidget, public ICustomDetailsViewBase`  
_L61-110_
- inherits: `SCompoundWidget,ICustomDetailsViewBase`
- L68 _public prototype_ `virtual TSharedRef<ICustomDetailsViewItem> GetRootItem() const = 0;` — Get the Root Item of the Main Tree. WARNING: This Item is not meant to make Widgets or have an Item Id. It's purely for having one source to house the entire tree
- L75 _public prototype_ `virtual TSharedPtr<ICustomDetailsViewItem> FindItem(const FCustomDetailsViewItemId& InItemId) const = 0;` — Quickly find an Item with the given Item Id without iterating the tree @param InItemId the id of the item to look for @return pointer to the item, or null if it was not found
- L82 _public prototype_ `virtual TSharedRef<STreeView<TSharedPtr<ICustomDetailsViewItem>>> MakeSubTree(const TArray<TSharedPtr<ICustomDetailsViewItem>>* InSourceItems) const = 0;` — Make a Sub Tree View for the Given Root Item Id @param InSourceItems pointer to the array of items that will be the top level items of the tree, these need to be valid for the duration of the Tree View lifetime @return the tree widget if the Root Item Id was found
- L85 _public prototype_ `virtual void RebuildTree(ECustomDetailsViewBuildType InBuildType) = 0;` — Request the Tree to be rebuilt with the given Build Type
- L88 _public prototype_ `virtual void ExtendTree(FCustomDetailsViewItemId InHook, ECustomDetailsTreeInsertPosition InPosition, TSharedRef<ICustomDetailsViewItem> InItem) = 0;` — Adds a custom node into the hierarchy at the given position.
- L91 _public prototype_ `virtual const UE::CustomDetailsView::FTreeExtensionType& GetTreeExtensions(FCustomDetailsViewItemId InHook) const = 0;` — Retrieves all the extensions for the given item.
- L94 _public prototype_ `virtual TSharedRef<ICustomDetailsViewItem> CreateDetailTreeItem(TSharedRef<ICustomDetailsViewItem> InParent, TSharedRef<IDetailTreeNode> InDetailTreeNode) = 0;` — Creates a custom details view item based on a property handle.
- L97 _public prototype_ `virtual TSharedPtr<ICustomDetailsViewCustomItem> CreateCustomItem(TSharedRef<ICustomDetailsViewItem> InParent, FName InItemName, const FText& InLabel = FText::GetEmpty(), const FText& InToolTip = FText::GetEmpty()) = 0;` — Creates a custom details view item that has a customisable name and value widget.
- L100 _public prototype_ `virtual TSharedPtr<ICustomDetailsViewCustomCategoryItem> CreateCustomCategoryItem(TSharedRef<ICustomDetailsViewItem> InParent, FName InItemName, const FText& InLabel = FText::GetEmpty(), const FText& InToolTip = FText::GetEmpty()) = 0;` — Creates a custom details view item that acts as a category.
- L103 _public prototype_ `virtual TSharedPtr<ICustomDetailsViewItem> FindCustomItem(const FName& InItemName) const = 0;` — Find a previously added custom item.
- L106 _public prototype_ `virtual bool GetItemExpansionState(const FCustomDetailsViewItemId& InItemId, ECustomDetailsViewExpansion& OutExpansion) const = 0;` — Returns the current expansion state of an item. Returns true if the item state was found.
- L109 _public prototype_ `virtual void SetItemExpansionState(const FCustomDetailsViewItemId& InItemId, ECustomDetailsViewExpansion InExpansion) = 0;` — Sets the current expansion state of an item.

### `Plugins/VirtualProduction/CustomDetailsView/Source/CustomDetailsView/Public/Items/CustomDetailsViewItemId.h` (Public)


#### class `FCustomDetailsViewItemId`  
`class FCustomDetailsViewItemId`  
_L7-84_
- L10 _private member_ `template<typename T> static constexpr bool TFindPropertyCondition_V = TModels_V<CStaticClassProvider, T> || TModels_V<CStaticStructProvider, T>;`
- L14 _public member_ `static constexpr uint32 CustomItemType = static_cast<uint32>(-1);` — This protects it from being taken by other new items added to EDetailNodeType.
- L15 _public member_ `static constexpr uint32 NullItemType = static_cast<uint32>(-2);`
- L17 _public prototype_ `FCustomDetailsViewItemId() = default;`
- L19 _public prototype_ `static FCustomDetailsViewItemId MakeCategoryId(FName InCategoryName, const FCustomDetailsViewItemId* InParentId = nullptr);`
- L21 _public prototype_ `static FCustomDetailsViewItemId MakePropertyId(FProperty* Property);`
- L22 _public prototype_ `static FCustomDetailsViewItemId MakePropertyId(const TSharedPtr<IPropertyHandle>& InPropertyHandle);`
- L23 _public prototype_ `static FCustomDetailsViewItemId MakeCustomId(FName InItemName, const FCustomDetailsViewItemId* InParentId = nullptr);`
- L30 _public function_ `static FCustomDetailsViewItemId MakePropertyId(FName InPropertyName)`
- L46 _public prototype_ `static FCustomDetailsViewItemId MakeFromDetailTreeNode(const TSharedRef<IDetailTreeNode>& InDetailTreeNode, const FCustomDetailsViewItemId* InParentId = nullptr);`
- L54 _public function_ `bool operator==(const FCustomDetailsViewItemId& InOtherItemId) const`
- L61 _public function_ `bool operator!=(const FCustomDetailsViewItemId& InOtherItemId) const`
- L66 _public function_ `const FString& GetItemName() const`
- L68 _public function_ `uint32 GetItemType() const`
- L70 _public prototype_ `bool IsType(EDetailNodeType InType) const;`
- L73 _private prototype_ `FCustomDetailsViewItemId(uint32 InItemType, const FString& InItemName, const FCustomDetailsViewItemId* InParentId = nullptr);`
- L75 _private function_ `void CalculateTypeHash()`
- L81 _private member_ `FString ItemName;`
- L82 _private member_ `uint32 ItemType = NullItemType;`
- L83 _private member_ `uint32 CachedHash = 0;`

#### Free symbols / members of external scopes

- L49 _function_ `friend uint32 GetTypeHash(const FCustomDetailsViewItemId& InItemId)`

### `Plugins/VirtualProduction/CustomDetailsView/Source/CustomDetailsView/Public/Items/ICustomDetailsViewCustomCategoryItem.h` (Public)


#### class `ICustomDetailsViewCustomCategoryItem`  
`class ICustomDetailsViewCustomCategoryItem`  
_L12-24_
- L15 _public prototype_ `virtual ~ICustomDetailsViewCustomCategoryItem() = default;`
- L18 _public prototype_ `virtual void SetLabel(const FText& InLabel) = 0;` — Sets the text that will appear in the name column.
- L21 _public prototype_ `virtual void SetToolTip(const FText& InToolTip) = 0;` — Sets the tooltip that will appear in the name column.
- L23 _public prototype_ `virtual TSharedRef<ICustomDetailsViewItem> AsItem() = 0;`

### `Plugins/VirtualProduction/CustomDetailsView/Source/CustomDetailsView/Public/Items/ICustomDetailsViewCustomItem.h` (Public)


#### class `ICustomDetailsViewCustomItem`  
`class ICustomDetailsViewCustomItem`  
_L13-36_
- L16 _public prototype_ `virtual ~ICustomDetailsViewCustomItem() = default;`
- L18 _public prototype_ `virtual void SetNodeType(TOptional<EDetailNodeType> InNodeType) = 0;`
- L21 _public prototype_ `virtual void SetLabel(const FText& InLabel) = 0;` — Sets the text that will appear in the name column. Removes whole row widget override.
- L24 _public prototype_ `virtual void SetToolTip(const FText& InToolTip) = 0;` — Sets the tooltip that will appear in the name column. Removes whole row widget override.
- L27 _public prototype_ `virtual void SetValueWidget(const TSharedRef<SWidget>& InValueWidget) = 0;` — Sets the widget that will appear in the value column. Removes whole row widget override.
- L30 _public prototype_ `virtual void SetExpansionWidget(const TSharedRef<SWidget>& InExpansionWidget) = 0;` — Sets the expansion widget override which where return to default, etc. are. Removes whole row widget override.
- L33 _public prototype_ `virtual void SetWholeRowWidget(const TSharedRef<SWidget>& InWholeRowWidget) = 0;` — Sets the whole row widget override and removes the other overrides.
- L35 _public prototype_ `virtual TSharedRef<ICustomDetailsViewItem> AsItem() = 0;`

### `Plugins/VirtualProduction/CustomDetailsView/Source/CustomDetailsView/Public/Items/ICustomDetailsViewItem.h` (Public)


#### class `ICustomDetailsViewItem`  
`class ICustomDetailsViewItem : public TSharedFromThis<ICustomDetailsViewItem>`  
_L32-136_
- inherits: `TSharedFromThis<ICustomDetailsViewItem>`
- L35 _public prototype_ `virtual ~ICustomDetailsViewItem() = default;`
- L38 _public prototype_ `virtual void InitWidget() = 0;` — Called to initialise the widget.
- L40 _public prototype_ `virtual TSharedPtr<ICustomDetailsView> GetCustomDetailsView() const = 0;`
- L43 _public prototype_ `virtual TSharedPtr<IDetailsView> GetDetailsView() const = 0;` — Details view containing this item
- L46 _public prototype_ `virtual void RefreshItemId() = 0;` — Called to update the Item's Id
- L49 _public prototype_ `virtual const FCustomDetailsViewItemId& GetItemId() const = 0;` — Retrieves the Item Id last updated from RefreshItemId, to avoid having to recalculate it every time
- L52 _public prototype_ `virtual void RefreshChildren(TSharedPtr<ICustomDetailsViewItem> InParentOverride = nullptr) = 0;` — Regenerates the Children
- L54 _public prototype_ `virtual TSharedPtr<ICustomDetailsViewItem> GetRoot() const = 0;`
- L56 _public prototype_ `virtual TSharedPtr<ICustomDetailsViewItem> GetParent() const = 0;`
- L58 _public prototype_ `virtual void SetParent(TSharedPtr<ICustomDetailsViewItem> InParent) = 0;`
- L60 _public prototype_ `virtual const TArray<TSharedPtr<ICustomDetailsViewItem>>& GetChildren() const = 0;`
- L62 _public prototype_ `virtual TOptional<EDetailNodeType> GetNodeType() const = 0;`
- L65 _public prototype_ `virtual void AddAsChild(const TSharedRef<ICustomDetailsViewItem>& InParentItem, TArray<TSharedPtr<ICustomDetailsViewItem>>& OutChildren) = 0;` — Adds this node as a child.
- L72 _public prototype_ `virtual TSharedRef<SWidget> MakeWidget(const TSharedPtr<SWidget>& InPrependWidget = nullptr , const TSharedPtr<SWidget>& InOwningWidget = nullptr) = 0;` — Instantiates a Widget for the Given Item @param InPrependWidget: Optional to prepend a Widget to the Name or Whole Row Widget @param InOwningWidget: Optional Widget to check for attributes like IsHovered()
- L80 _public prototype_ `virtual TSharedPtr<SWidget> GetWidget(ECustomDetailsViewWidgetType InWidgetType) const = 0;` — Get the one of the widgets that was generated in the MakeWidget Listen to the OnItemWidgetGenerated Delegate to have this Widget up to date with latest tree view @param InWidgetType: The type of widget to retrieve
- L85 _public prototype_ `virtual TSharedPtr<SWidget> GetOverrideWidget(ECustomDetailsViewWidgetType InWidgetType) const = 0;` — Gets the widget set to override the widget automatically generated in the given slot.
- L91 _public prototype_ `virtual void SetOverrideWidget(ECustomDetailsViewWidgetType InWidgetType, TSharedPtr<SWidget> InWidget) = 0;` — Adds a widget to override an automatically generated widget for the given slot. @param InWidget The widget to override with, or a nullptr or SNullWidget::NullWidget to remove it.
- L94 _public prototype_ `virtual void SetKeyframeEnabled(bool bInKeyframeEnabled) = 0;` — Override the keyframeability of this item.
- L97 _public prototype_ `virtual void SetResetToDefaultOverride(const FResetToDefaultOverride& InOverride) = 0;` — Override the reset to the default information for this item.
- L100 _public prototype_ `virtual bool IsWidgetVisible() const = 0;` — Checks to see if widget is visible
- L103 _public prototype_ `virtual void SetValueWidgetWidthOverride(TOptional<float> InWidth) = 0;` — Overrides the created value widget's maximum width.
- L106 _public prototype_ `virtual void SetEnabledOverride(TAttribute<bool> InOverride) = 0;` — Overrides the created widget's enabled status.
- L109 _public prototype_ `virtual const FDetailWidgetRow& GetDetailWidgetRow() const = 0;` — Returns the widget row that stores the default of this widget.
- L112 _public prototype_ `virtual bool CreateResetToDefaultButton(FPropertyRowExtensionButton& OutButton) = 0;` — Creates the reset to default button based on this item's settings, if it can.
- L115 _public prototype_ `virtual void CreateGlobalExtensionButtons(TArray<FPropertyRowExtensionButton>& OutExtensionButtons) = 0;` — Creates the other global extension buttons.
- L118 _public prototype_ `virtual TSharedRef<SWidget> CreateExtensionButtonWidget(const TArray<FPropertyRowExtensionButton>& InExtensionButtons) = 0;` — Takes a list of buttons and creates an extension button widget.
- L124 _public prototype_ `virtual void SetCreateChildItemDelegate(FOnCustomDetailsViewGenerateChildItem InDelegate) = 0;` — When the property based on a property row generator is expanded and child properties are generated, use this delegate to create the row, if set and it returns a non-null row.
- L129 _public prototype_ `virtual void SetCustomizeItemMenuContext(FOnCustomDetailsViewCustomizeItemMenuContext InDelegate) = 0;` — Allows to customize the context menu of this item
- L133 _protected prototype_ `virtual void GatherChildren(const TSharedRef<ICustomDetailsViewItem>& InParentItem, const UE::CustomDetailsView::FTreeExtensionType& InTreeExtensions, ECustomDetailsTreeInsertPosition InPosition, TArray<TSharedPtr<ICustomDetailsViewItem>>& OutChildren) = 0;` — Adds the children of this node.

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams( TSharedPtr<ICustomDetailsViewItem>, FOnCustomDetailsViewGenerateChildItem, const TSharedRef<ICustomDetailsView>& InCustomDetailsView, const TSharedPtr<ICustomDetailsViewItem>& InParentItem, const TSharedRef<IDetailTreeNode>& InChildNode ) DECLARE_DELEGATE_FourParams( FOnCustomDetailsViewCustomizeItemMenuContext, const TSharedRef<ICustomDetailsView>& InCustomDetailsView, const TSharedPtr<ICustomDetailsViewItem>& InItem, UObject* InMenuContext, TArray<TSharedPtr<IPropertyHandle>>& InPropertyHandles ) class ICustomDetailsViewItem : public TSharedFromThis<ICustomDetailsViewItem> { public: virtual ~ICustomDetailsViewItem() = default; virtual void InitWidget() = 0; virtual TSharedPtr<ICustomDetailsView> GetCustomDetailsView() const = 0; virtual TSharedPtr<IDetailsView> GetDetailsView() const = 0; virtual void RefreshItemId() = 0; virtual const FCustomDetailsViewItemId& GetItemId() const = 0; virtual void RefreshChildren(TSharedPtr<ICustomDetailsViewItem> InParentOverride = nullptr) = 0; virtual TSharedPtr<ICustomDetailsViewItem> GetRoot() const = 0;`
- L24 _delegate_ `DECLARE_DELEGATE_FourParams( FOnCustomDetailsViewCustomizeItemMenuContext, const TSharedRef<ICustomDetailsView>& InCustomDetailsView, const TSharedPtr<ICustomDetailsViewItem>& InItem, UObject* InMenuContext, TArray<TSharedPtr<IPropertyHandle>>& InPropertyHandles ) class ICustomDetailsViewItem : public TSharedFromThis<ICustomDetailsViewItem> { public: virtual ~ICustomDetailsViewItem() = default; virtual void InitWidget() = 0; virtual TSharedPtr<ICustomDetailsView> GetCustomDetailsView() const = 0; virtual TSharedPtr<IDetailsView> GetDetailsView() const = 0; virtual void RefreshItemId() = 0; virtual const FCustomDetailsViewItemId& GetItemId() const = 0; virtual void RefreshChildren(TSharedPtr<ICustomDetailsViewItem> InParentOverride = nullptr) = 0; virtual TSharedPtr<ICustomDetailsViewItem> GetRoot() const = 0; virtual TSharedPtr<ICustomDetailsViewItem> GetParent() const = 0; virtual void SetParent(TSharedPtr<ICustomDetailsViewItem> InParent) = 0; virtual const TArray<TSharedPtr<ICustomDetailsViewItem>>& GetChildren() const = 0; virtual TOptional<EDetailNodeType> GetNodeType() const = 0;`
