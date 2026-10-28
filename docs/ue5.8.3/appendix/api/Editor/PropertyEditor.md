# Editor / PropertyEditor

- module root: `Source/Editor/PropertyEditor`
- headers: 180; symbols: 6041
- symbol kinds: class=231, delegate=122, enum=29, enumerator=109, externvar=1, function=972, macro=18, member=1243, namespace=41, prototype=3117, struct=76, typedef=33, variable=49
- DynamicallyLoadedModuleNames: AssetRegistry, AssetTools, ClassViewer, ContentBrowser, MainFrame, StructViewer
- PrivateDependencyModuleNames: AppFramework, ApplicationCore, AssetDefinition, CQTest, ConfigEditor, Core, CoreUObject, DesktopPlatform, Documentation, EditorStyle, EditorWidgets, Engine, InputCore, Json, Projects, PropertyPath, SceneOutliner, Slate, SlateCore, ToolMenus, ToolWidgets, WidgetRegistration
- PrivateIncludePathModuleNames: AssetRegistry, AssetTools, ClassViewer, ContentBrowser, MainFrame, StructViewer
- PublicDependencyModuleNames: ActorPickerMode, EditorConfig, EditorFramework, SceneDepthPickerMode, UnrealEd

### `Source/Editor/PropertyEditor/Private/CategoryPropertyNode.h` (Private)


#### class `FCategoryPropertyNode`  
`class FCategoryPropertyNode : public FPropertyNode`  
_L8-54_
- inherits: `FPropertyNode`
- L11 _public prototype_ `FCategoryPropertyNode();`
- L12 _public prototype_ `virtual ~FCategoryPropertyNode();`
- L17 _public function_ `virtual FCategoryPropertyNode* AsCategoryNode() override` — Overridden function to get the derived object node
- L18 _public function_ `virtual const FCategoryPropertyNode* AsCategoryNode() const override`
- L23 _public function_ `void SetCategoryName(const FName& InCategoryName)` — Accessor functions for getting a category name
- L24 _public function_ `const FName& GetCategoryName(void) const`
- L31 _public prototype_ `bool IsSubcategory() const;` — Checks to see if this category is a 'sub-category' @return	True if this category node is a sub-category, otherwise false
- L33 _public prototype_ `virtual FText GetDisplayName() const override;`
- L39 _protected prototype_ `virtual void InitBeforeNodeFlags() override;` — Overridden function for special setup
- L43 _protected prototype_ `virtual void InitChildNodes() override;` — Overridden function for Creating Child Nodes
- L48 _protected prototype_ `virtual bool GetQualifiedName( FString& PathPlusIndex, const bool bWithArrayIndex, const FPropertyNode* StopParent = nullptr, bool bIgnoreCategories = false ) const override;` — Appends my path, including an array index (where appropriate)
- L53 _protected member_ `FName CategoryName;` — Stored category name for the window

### `Source/Editor/PropertyEditor/Private/CustomChildBuilder.h` (Private)


#### class `FCustomChildrenBuilder`  
`class FCustomChildrenBuilder : public IDetailChildrenBuilder`  
_L15-59_
- inherits: `IDetailChildrenBuilder`
- L18 _public function_ `FCustomChildrenBuilder(TSharedRef<FDetailCategoryImpl> InParentCategory, TSharedPtr<IDetailGroup> InParentGroup = nullptr) : ParentCategory(InParentCategory) , ParentGroup(InParentGroup)`
- L23 _public prototype_ `virtual IDetailChildrenBuilder& AddCustomBuilder(TSharedRef<class IDetailCustomNodeBuilder> InCustomBuilder) override;`
- L24 _public prototype_ `virtual IDetailGroup& AddGroup(FName GroupName, const FText& LocalizedDisplayName, const bool bStartExpanded = false) override;`
- L25 _public prototype_ `virtual IDetailGroup* GetGroup(FName GroupName) override;`
- L26 _public prototype_ `virtual FDetailWidgetRow& AddCustomRow(const FText& SearchString) override;`
- L27 _public prototype_ `virtual IDetailPropertyRow& AddProperty(TSharedRef<IPropertyHandle> PropertyHandle) override;`
- L29 _public prototype_ `virtual IDetailPropertyRow* AddExternalObjects(const TArray<UObject*>& Objects, FName UniqueIdName) override;` — `UE_DEPRECATED(5.1, "Please use the overload that takes an FAddPropertyParams instead.")`
- L30 _public prototype_ `virtual IDetailPropertyRow* AddExternalObjects(const TArray<UObject*>& Objects, const FAddPropertyParams& Params) override;`
- L31 _public prototype_ `virtual IDetailPropertyRow* AddExternalObjectProperty(const TArray<UObject*>& Objects, FName PropertyName, const FAddPropertyParams& Params) override;`
- L32 _public prototype_ `virtual IDetailPropertyRow* AddExternalStructure(TSharedRef<FStructOnScope> ChildStructure, FName UniqueIdName) override;`
- L33 _public prototype_ `virtual IDetailPropertyRow* AddExternalStructure(TSharedPtr<IStructureDataProvider> ChildStructure, FName UniqueIdName) override;`
- L34 _public prototype_ `virtual IDetailPropertyRow* AddChildStructure(TSharedRef<IPropertyHandle> PropertyHandle, TSharedPtr<IStructureDataProvider> ChildStructure, FName UniqueIdName, const FText& DisplayNameOverride = FText()) override;`
- L35 _public prototype_ `virtual IDetailPropertyRow* AddExternalStructureProperty(TSharedRef<FStructOnScope> ChildStructure, FName PropertyName, const FAddPropertyParams& Params) override;`
- L36 _public prototype_ `virtual IDetailPropertyRow* AddExternalStructureProperty(TSharedPtr<IStructureDataProvider> ChildStructure, FName PropertyName, const FAddPropertyParams& Params) override;`
- L37 _public prototype_ `virtual IDetailPropertyRow* AddChildStructureProperty(TSharedRef<IPropertyHandle> PropertyHandle, TSharedPtr<IStructureDataProvider> ChildStructure, FName PropertyName, const FAddPropertyParams& Params = FAddPropertyParams(), const FText& DisplayNameOverride = FText()) override;`
- L38 _public prototype_ `virtual TArray<TSharedPtr<IPropertyHandle>> AddAllExternalStructureProperties(TSharedRef<FStructOnScope> ChildStructure) override;`
- L39 _public prototype_ `virtual TArray<TSharedPtr<IPropertyHandle>> AddAllExternalStructureProperties(TSharedPtr<IStructureDataProvider> ChildStructure) override;`
- L40 _public prototype_ `virtual TSharedRef<SWidget> GenerateStructValueWidget(TSharedRef<IPropertyHandle> StructPropertyHandle) override;`
- L41 _public prototype_ `virtual IDetailCategoryBuilder& GetParentCategory() const override;`
- L42 _public prototype_ `virtual IDetailGroup* GetParentGroup() const override;`
- L44 _public function_ `const TArray< FDetailLayoutCustomization >& GetChildCustomizations() const`
- L47 _public prototype_ `FCustomChildrenBuilder& OverrideResetChildrenToDefault(const FResetToDefaultOverride& ResetToDefault);` — Set the user customized reset to default for the children of this builder
- L50 _private member_ `TArray< FDetailLayoutCustomization > ChildCustomizations;`
- L51 _private member_ `TWeakPtr<FDetailCategoryImpl> ParentCategory;`
- L52 _private member_ `TWeakPtr<IDetailGroup> ParentGroup;`
- L55 _private member_ `TOptional<FResetToDefaultOverride> CustomResetChildToDefault;` — User customized reset to default on children
- L57 _private prototype_ `IDetailPropertyRow* AddStructureProperty(const FAddPropertyParams& Params, TFunctionRef<void(FDetailLayoutCustomization&)> MakePropertyRowCustomization);`
- L58 _private prototype_ `template<class T> IDetailPropertyRow* AddExternalStructureProperty(const T& ChildStructure, FName PropertyName, const FAddPropertyParams& Params);`

### `Source/Editor/PropertyEditor/Private/DetailAdvancedDropdownNode.h` (Private)


#### class `FAdvancedDropdownNode`  
`class FAdvancedDropdownNode : public FDetailTreeNode, public TSharedFromThis<FAdvancedDropdownNode>`  
_L14-51_
- inherits: `FDetailTreeNode,TSharedFromThis<FAdvancedDropdownNode>`
- L17 _public function_ `FAdvancedDropdownNode(TSharedRef<FDetailCategoryImpl> InParentCategory, const TAttribute<bool>& InExpanded, const TAttribute<bool>& InEnabled, TAttribute<bool> InVisible) : ParentCategory(InParentCategory.Get()) , IsEnabled(InEnabled) , IsExpanded(InExpanded) , IsVisible(InVisible)`
- L28 _private function_ `virtual TSharedPtr<IDetailsView> GetNodeDetailsViewSharedPtr() const override`
- L29 _private function_ `virtual TSharedPtr<IDetailsViewPrivate> GetDetailsViewSharedPtr() const override`
- L30 _private prototype_ `virtual TSharedRef< ITableRow > GenerateWidgetForTableView( const TSharedRef<STableViewBase>& OwnerTable, bool bAllowFavoriteSystem) override;`
- L31 _private prototype_ `virtual bool GenerateStandaloneWidget(FDetailWidgetRow& OutRow) const override;`
- L32 _private function_ `virtual void GetChildren(FDetailNodeList& OutChildren, const bool& bInIgnoreVisibility) override`
- L33 _private prototype_ `virtual void OnItemExpansionChanged( bool bIsExpanded, bool bShouldSaveState) override;`
- L34 _private function_ `virtual bool ShouldBeExpanded() const override`
- L35 _private prototype_ `virtual ENodeVisibility GetVisibility() const override;`
- L36 _private function_ `virtual void FilterNode( const FDetailFilter& InFilter ) override`
- L37 _private function_ `virtual void Tick( float DeltaTime ) override`
- L38 _private function_ `virtual bool ShouldShowOnlyChildren() const override`
- L39 _private function_ `virtual FName GetNodeName() const override`
- L40 _private function_ `virtual EDetailNodeType GetNodeType() const override`
- L41 _private function_ `virtual TSharedPtr<IPropertyHandle> CreatePropertyHandle() const override`
- L45 _private prototype_ `FReply OnAdvancedDropDownClicked();` — Called when the advanced drop down arrow is clicked
- L47 _private member_ `FDetailCategoryImpl& ParentCategory;`
- L48 _private member_ `TAttribute<bool> IsEnabled;`
- L49 _private member_ `TAttribute<bool> IsExpanded;`
- L50 _private member_ `TAttribute<bool> IsVisible;`

### `Source/Editor/PropertyEditor/Private/DetailCategoryBuilderImpl.h` (Private)


#### struct `FDetailLayoutCustomization`  
`struct FDetailLayoutCustomization`  
_L30-73_
- desc: Defines a customization for a specific detail
- L32 _public prototype_ `FDetailLayoutCustomization();`
- L34 _public member_ `TSharedPtr<FDetailPropertyRow> PropertyRow;` — The property node for the property detail
- L36 _public member_ `TSharedPtr<FDetailGroup> DetailGroup;` — A group of customizations
- L38 _public member_ `TSharedPtr<FDetailWidgetRow> WidgetDecl;` — Custom Widget for displaying the detail
- L40 _public member_ `TSharedPtr<FDetailCustomBuilderRow> CustomBuilderRow;` — Custom builder for more complicated widgets
- L42 _public function_ `bool HasPropertyNode() const` — @return true if this customization has a property node
- L44 _public function_ `bool HasCustomWidget() const` — @return true if this customization has a custom widget
- L46 _public function_ `bool HasCustomBuilder() const` — @return true if this customization has a custom builder (custom builders will set the custom widget)
- L48 _public function_ `bool HasGroup() const` — @return true if this customization has a group
- L50 _public prototype_ `bool HasExternalPropertyRow() const;` — @return true if this has a customization for an external property row
- L52 _public function_ `bool IsValidCustomization() const` — @return true if this customization is valid
- L54 _public prototype_ `bool IsHidden() const;` — @return true if the customized item is hidden
- L56 _public prototype_ `TSharedPtr<FPropertyNode> GetPropertyNode() const;` — @return the property node for this customization (if any )
- L58 _public prototype_ `FDetailWidgetRow GetWidgetRow() const;` — @return The row to display from this customization
- L60 _public prototype_ `TArrayView<TSharedPtr<IPropertyHandle>> GetPropertyHandles() const;` — @return properties being customized
- L62 _public prototype_ `FText GetFilterTextString() const;` — @return the filter text associated with this row, if any
- L64 _public member_ `bool bAdvanced { false };` — Whether or not this customization is considered an advanced property.
- L66 _public member_ `bool bCustom { false };` — Whether or not this customization is custom or a default one.
- L68 _public prototype_ `const IDetailLayoutRow* GetDetailLayoutRow() const;` — @return The current layout row that this customization represents. May be null if IsValidCustomization() is false.
- L70 _public prototype_ `FName GetName() const;` — @return The name of the row depending on which type of customization this is, then the name of the property node, then NAME_None.
- L72 _public prototype_ `TOptional<FResetToDefaultOverride> GetCustomResetToDefault() const;` — @return The custom reset to default if one is available.

#### class `FDetailLayout`  
`class FDetailLayout`  
_L75-104_
- L78 _public function_ `FDetailLayout(FName InInstanceName) : InstanceName(InInstanceName)`
- L82 _public prototype_ `void AddLayout(const FDetailLayoutCustomization& Layout);`
- L84 _public function_ `const TArray<FDetailLayoutCustomization>& GetSimpleLayouts() const`
- L85 _public function_ `const TArray<FDetailLayoutCustomization>& GetAdvancedLayouts() const`
- L87 _public prototype_ `FDetailLayoutCustomization* GetDefaultLayout(const TSharedRef<FPropertyNode>& PropertyNode);`
- L89 _public function_ `bool HasAdvancedLayouts() const`
- L95 _public function_ `FName GetInstanceName() const` — Get the instance name - this is usually the UObject's name when in a multi-selection. Used to display a group beneath the category if multiple objects share some of the same-named properties.
- L99 _private member_ `TArray<FDetailLayoutCustomization> SimpleLayouts;` — Layouts that appear in the simple (visible by default) area of a category
- L101 _private member_ `TArray<FDetailLayoutCustomization> AdvancedLayouts;` — Layouts that appear in the advanced (hidden by default) details area of a category
- L103 _private member_ `FName InstanceName;` — The sort order in which this layout is displayed (lower numbers are displayed first)

#### class `FDetailLayoutMap`  
`class FDetailLayoutMap`  
_L107-153_
- L110 _public function_ `FDetailLayoutMap() : bContainsBaseInstance(false)`
- L114 _public function_ `FDetailLayout& FindOrAdd(FName InstanceName)`
- L132 _public typedef_ `using RangedForIteratorType = TArray<FDetailLayout>::RangedForIteratorType;`
- L133 _public typedef_ `using RangedForConstIteratorType = TArray<FDetailLayout>::RangedForConstIteratorType;`
- L135 _public function_ `FORCEINLINE RangedForIteratorType begin()`
- L136 _public function_ `FORCEINLINE RangedForConstIteratorType begin() const`
- L137 _public function_ `FORCEINLINE RangedForIteratorType end()`
- L138 _public function_ `FORCEINLINE RangedForConstIteratorType end() const`
- L140 _public function_ `FDetailLayout& operator[](int32 Index)`
- L141 _public function_ `const FDetailLayout& operator[](int32 Index) const`
- L143 _public function_ `int32 Num() const`
- L148 _public prototype_ `bool ShouldShowGroup(FName RequiredGroupName) const;` — @return Whether or not we need to display a group border around a list of details.
- L151 _private member_ `TArray<FDetailLayout> Layouts;`
- L152 _private member_ `bool bContainsBaseInstance;`

#### class `FDetailCategoryImpl`  
`class FDetailCategoryImpl : public IDetailCategoryBuilder, public FDetailTreeNode, public TSharedFromThis<FDetailCategoryImpl>`  
_L159-502_
- inherits: `IDetailCategoryBuilder,FDetailTreeNode,TSharedFromThis<FDetailCategoryImpl>`
- desc: Detail category implementation
- L163 _public member_ `static FString DetailCategories;`
- L164 _public member_ `static FString TransientPerViewDetailCategories;`
- L165 _public member_ `static FString PersistentPerViewDetailCategories;`
- L168 _public prototype_ `FDetailCategoryImpl(FName InCategoryName, TSharedRef<FDetailLayoutBuilderImpl> InDetailLayout);`
- L169 _public prototype_ `~FDetailCategoryImpl();`
- L172 _public prototype_ `virtual IDetailCategoryBuilder& InitiallyCollapsed(bool bShouldBeInitiallyCollapsed) override;` — IDetailCategoryBuilder interface
- L173 _public prototype_ `virtual IDetailCategoryBuilder& OnExpansionChanged(FOnBooleanValueChanged InOnExpansionChanged) override;`
- L174 _public prototype_ `virtual IDetailCategoryBuilder& RestoreExpansionState(bool bRestore) override;`
- L175 _public prototype_ `virtual IDetailCategoryBuilder& HeaderContent(TSharedRef<SWidget> InHeaderContent, bool bWholeRowContent = false) override;`
- L176 _public prototype_ `virtual IDetailPropertyRow& AddProperty(FName PropertyPath, UClass* ClassOuter = nullptr, FName InstanceName = NAME_None, EPropertyLocation::Type Location = EPropertyLocation::Default) override;`
- L177 _public prototype_ `virtual IDetailPropertyRow& AddProperty(TSharedPtr<IPropertyHandle> PropertyHandle, EPropertyLocation::Type Location = EPropertyLocation::Default) override;`
- L178 _public prototype_ `virtual IDetailPropertyRow* AddExternalObjects(const TArray<UObject*>& Objects, EPropertyLocation::Type Location = EPropertyLocation::Default, const FAddPropertyParams& Params = FAddPropertyParams()) override;`
- L179 _public prototype_ `virtual IDetailPropertyRow* AddExternalObjectProperty(const TArray<UObject*>& Objects, FName PropertyName, EPropertyLocation::Type Location = EPropertyLocation::Default, const FAddPropertyParams& Params = FAddPropertyParams()) override;`
- L180 _public prototype_ `virtual IDetailPropertyRow* AddExternalStructure(TSharedPtr<FStructOnScope> StructData, EPropertyLocation::Type Location = EPropertyLocation::Default) override;`
- L181 _public prototype_ `virtual IDetailPropertyRow* AddExternalStructureProperty(TSharedPtr<FStructOnScope> StructData, FName PropertyName, EPropertyLocation::Type Location = EPropertyLocation::Default, const FAddPropertyParams& Params = FAddPropertyParams()) override;`
- L182 _public prototype_ `virtual IDetailPropertyRow* AddExternalStructureProperty(TSharedPtr<IStructureDataProvider> StructData, FName PropertyName, EPropertyLocation::Type Location = EPropertyLocation::Default, const FAddPropertyParams& Params = FAddPropertyParams()) override;`
- L183 _public prototype_ `virtual TArray<TSharedPtr<IPropertyHandle>> AddAllExternalStructureProperties(TSharedRef<FStructOnScope> StructData, EPropertyLocation::Type Location = EPropertyLocation::Default, TArray<IDetailPropertyRow*>* OutPropertiesRow = nullptr) override;`
- L184 _public prototype_ `virtual TArray<TSharedPtr<IPropertyHandle>> AddAllExternalStructureProperties(TSharedPtr<IStructureDataProvider> StructProvider, EPropertyLocation::Type Location = EPropertyLocation::Default, TArray<IDetailPropertyRow*>* OutPropertiesRow = nullptr) override;`
- L185 _public function_ `virtual bool IsParentLayoutValid() const override`
- L186 _public function_ `virtual IDetailLayoutBuilder& GetParentLayout() const override`
- L187 _public prototype_ `virtual FDetailWidgetRow& AddCustomRow(const FText& FilterString, bool bForAdvanced = false) override;`
- L188 _public prototype_ `virtual void AddCustomBuilder(TSharedRef<IDetailCustomNodeBuilder> InCustomBuilder, bool bForAdvanced = false) override;`
- L189 _public prototype_ `virtual IDetailGroup& AddGroup(FName GroupName, const FText& LocalizedDisplayName, bool bForAdvanced = false, bool bStartExpanded = false) override;`
- L190 _public prototype_ `virtual void GetDefaultProperties(TArray<TSharedRef<IPropertyHandle> >& OutAllProperties, bool bSimpleProperties = true, bool bAdvancedProperties = true) override;`
- L191 _public function_ `virtual const FText& GetDisplayName() const override`
- L192 _public prototype_ `virtual void SetDisplayName(const FText& InDisplayName) override;`
- L193 _public prototype_ `virtual const TOptional<FText>& GetToolTip() const override;`
- L194 _public prototype_ `virtual void SetToolTip(const FText& ToolTip) override;`
- L195 _public prototype_ `virtual void SetCategoryVisibility(bool bIsVisible) override;`
- L196 _public prototype_ `virtual void SetShowAdvanced(bool bShowAdvanced) override;`
- L197 _public prototype_ `virtual int32 GetSortOrder() const override;`
- L198 _public prototype_ `virtual void SetSortOrder(int32 InSortOrder) override;`
- L199 _public prototype_ `virtual void AddPropertyDisableInstancedReference(TSharedPtr<IPropertyHandle> PropertyHandle) override;`
- L202 _public function_ `virtual TSharedPtr<FOnPasteFromText> OnPasteFromText() const override` — Delegate handling pasting an optionally tagged text snippet
- L206 _public function_ `virtual TSharedPtr<FOnCopyToText> OnCopyToText() const override` — Delegate handling copying a property handle to text. The default property handle impl for copying will be used if the delegate is not bound or returns false for a property
- L209 _public function_ `virtual TSharedPtr<IDetailsView> GetNodeDetailsViewSharedPtr() const override` — FDetailTreeNode interface
- L210 _public prototype_ `virtual TSharedPtr<IDetailsViewPrivate> GetDetailsViewSharedPtr() const override;`
- L211 _public prototype_ `virtual TSharedRef< ITableRow > GenerateWidgetForTableView(const TSharedRef<STableViewBase>& OwnerTable, bool bAllowFavoriteSystem) override;`
- L212 _public prototype_ `virtual bool GenerateStandaloneWidget(FDetailWidgetRow& OutRow) const override;`
- L215 _public function_ `virtual EDetailNodeType GetNodeType() const override` — IDetailTreeNode interface
- L216 _public function_ `virtual TSharedPtr<IPropertyHandle> CreatePropertyHandle() const override`
- L217 _public prototype_ `virtual void GetFilterStrings(TArray<FString>& OutFilterStrings) const override;`
- L218 _public prototype_ `virtual bool GetInitiallyCollapsed() const override;`
- L220 _public prototype_ `virtual void GetChildren(FDetailNodeList& OutChildren, const bool& bInIgnoreVisibility = false) override;`
- L221 _public prototype_ `virtual bool ShouldBeExpanded() const override;`
- L222 _public prototype_ `virtual ENodeVisibility GetVisibility() const override;`
- L223 _public prototype_ `virtual void FilterNode(const FDetailFilter& DetailFilter) override;`
- L224 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L225 _public function_ `virtual bool ShouldShowOnlyChildren() const override`
- L226 _public function_ `virtual FName GetNodeName() const override`
- L231 _public prototype_ `void GetGeneratedChildren(FDetailNodeList& OutChildren, bool bIgnoreVisibility, bool bIgnoreAdvancedDropdown);` — Gets all generated children with options for ignoring current child visibility or advanced dropdowns
- L233 _public prototype_ `FCustomPropertyTypeLayoutMap GetCustomPropertyTypeLayoutMap() const;`
- L238 _public function_ `FName GetCategoryName() const` — @return The name of the category
- L243 _public function_ `TSharedPtr<FDetailLayoutBuilderImpl> GetParentLayoutImpl() const` — @return The parent detail layout builder for this category
- L248 _public prototype_ `void GenerateLayout();` — Generates the children for this category
- L256 _public prototype_ `void AddPropertyNode(TSharedRef<FPropertyNode> PropertyNode, FName InstanceName);` — Adds a property node to the default category layout @param PropertyNode			The property node to add @param InstanceName			The name of the property instance (for duplicate properties of the same type)
- L264 _public prototype_ `void SetDisplayName(FName CategoryName, const FText& LocalizedNameOverride);` — Sets the display name of the category string @param CategoryName			Base category name to use if no localized override is set @param LocalizedNameOverride	The localized name override to use (can be empty)
- L272 _public prototype_ `void RequestItemExpanded(TSharedRef<FDetailTreeNode> TreeNode, bool bShouldBeExpanded);` — Request that a child node of this category be expanded or collapsed @param TreeNode				The node to expand or collapse @param bShouldBeExpanded		True if the node should be expanded, false to collapse it
- L279 _public prototype_ `void RefreshTree(bool bRefilterCategory);` — Notifies the tree view that it needs to be refreshed @param bRefilterCategory True if the category should be refiltered
- L286 _public prototype_ `void AddTickableNode(FDetailTreeNode& TickableNode);` — Adds a node that needs to be ticked @param TickableNode	The node that needs to be ticked
- L293 _public prototype_ `void RemoveTickableNode(FDetailTreeNode& TickableNode);` — Removes a node that no longer needs to be ticked @param TickableNode	The node that no longer needs to be ticked
- L296 _public function_ `const FString& GetCategoryPathName() const` — @return The category path for this category
- L303 _public prototype_ `void SaveExpansionState(FDetailTreeNode& InTreeNode);` — Saves the expansion state of a tree node in this category @param InTreeNode	The node to save expansion state from
- L311 _public prototype_ `bool GetSavedExpansionState(FDetailTreeNode& InTreeNode) const;` — Gets the saved expansion state of a tree node in this category @param InTreeNode	The node to get expansion state for @return true if the node should be expanded, false otherwise
- L314 _public prototype_ `bool ContainsOnlyAdvanced() const;` — @return true if this category only contains advanced properties
- L319 _public prototype_ `int32 GetNumCustomizations() const;` — Get the number of customizations in this category.
- L324 _public prototype_ `void OnAdvancedDropdownClicked();` — Called when the advanced dropdown button is clicked
- L329 _public function_ `void SetCategoryAsSpecialFavorite()` — Call this function to make the category behave like favorite category
- L332 _public function_ `bool IsFavoriteCategory() const` — Is this the Favorites category?
- L335 _public function_ `bool GetShouldBeInitiallyCollapsed() const` — Is this category initially collapsed?
- L337 _public prototype_ `FDetailLayoutCustomization* GetDefaultCustomization(TSharedRef<FPropertyNode> PropertyNode);`
- L343 _public prototype_ `virtual bool IsEmpty() const override;` — If true, this Category should have no UProperty data associated with it, and will be shown as an empty stub with no expansion arrow
- L349 _public prototype_ `virtual void SetIsEmpty(bool bInIsEmpty) override;` — Sets whether this Category is "Empty" ~ that is, should have no UProperty data associated with it, and will be shown as an empty stub with no expansion arrow
- L351 _public prototype_ `virtual TOptional<FLinearColor> GetColor() const override;`
- L353 _public prototype_ `virtual void SetColor(FLinearColor InColor) override;`
- L355 _public prototype_ `virtual void ClearColor() override;`
- L359 _private prototype_ `virtual void OnItemExpansionChanged(bool bIsExpanded, bool bShouldSaveState) override;`
- L362 _private prototype_ `const FString& GetDetailCategoriesExpansionSection() const;` — Return string key for the given struct in config .ini for this details view's categories
- L365 _private prototype_ `FString GetCategoryPathConfigKey(const FString& InPath) const;` — Return string key for the given struct in config .ini for this details view
- L370 _private prototype_ `void GenerateChildrenForLayouts();` — Generates children for all layouts.
- L375 _private prototype_ `void GenerateChildrenForSingleLayout(const FDetailLayout& Layout, const TArray<FDetailLayoutCustomization>& Customizations, FDetailNodeList& OutChildren);` — Generate children for the single given layout and append them to OutChildren.
- L383 _private prototype_ `void GenerateNodesFromCustomizations(const TArray<FDetailLayoutCustomization>& InCustomizationList, FDetailNodeList& OutNodeList);` — Generates nodes from a list of customization in a single layout @param InCustomizationList	The list of customizations to generate nodes from @param OutNodeList			The generated nodes
- L388 _private prototype_ `bool IsAdvancedLayout(const FDetailLayoutCustomization& LayoutInfo);` — @return Whether or not a customization should appear in the advanced section of the category by default
- L396 _private prototype_ `void AddCustomLayout(const FDetailLayoutCustomization& LayoutInfo);` — Adds a custom layout to this category @param LayoutInfo	The custom layout information @param bForAdvanced	Whether or not the custom layout should appear in the advanced section of the category
- L404 _private prototype_ `void AddDefaultLayout(const FDetailLayoutCustomization& DefaultLayoutInfo, FName InstanceName);` — Adds a default layout to this category @param DefaultLayoutInfo		The layout information @param bForAdvanced			Whether or not the layout should appear in the advanced section of the category
- L411 _private prototype_ `FDetailLayout& GetLayoutForInstance(FName InstanceName);` — Returns the layout for a given object instance name @param InstanceName the name of the instance to get the layout for
- L416 _private prototype_ `bool ShouldAdvancedBeExpanded() const;` — @return True of we should show the advanced button
- L421 _private prototype_ `bool IsAdvancedDropdownEnabled() const;` — @return true if the advaned dropdown button is enabled
- L426 _private prototype_ `bool ShouldAdvancedBeVisible() const;` — @return the visibility of the advanced help text drop down (it is visible in a category if there are no simple properties)
- L431 _private prototype_ `bool IsParentEnabled() const;` — @return true if the parent that hosts us is enabled
- L438 _private prototype_ `void RefreshTreeInternal(bool bRefilterCategory);` — Does the work of refreshing the tree (this is triggered from RefreshTree) @param bRefilterCategory True if the category should be refiltered
- L442 _private member_ `FDetailLayoutMap LayoutMap;` — Layouts that appear in this category category
- L444 _private member_ `FDetailNodeList SimpleChildNodes;` — All Simple child nodes
- L446 _private member_ `FDetailNodeList AdvancedChildNodes;` — All Advanced child nodes
- L448 _private member_ `TSharedPtr<FDetailTreeNode> AdvancedDropdownNode;` — Advanced dropdown node.
- L450 _private member_ `FOnBooleanValueChanged OnExpansionChangedDelegate;` — Delegate called when expansion of the category changes
- L452 _private member_ `FText DisplayName;` — The display name of the category
- L454 _private member_ `TOptional<FText> ToolTip;` — ToolTip for this category
- L456 _private member_ `FString CategoryPathName;` — The path name of the category
- L458 _private member_ `TSharedPtr<SWidget> HeaderContentWidget;` — Custom header content displayed to the right of the category name
- L460 _private member_ `bool bHeaderContentWholeRowContent = false;` — True if the HeaderContentWidget should span the whole row (hides the category label)
- L462 _private member_ `TSharedPtr<FDetailTreeNode> InlinePropertyNode;` — A property node that is displayed in the header row to the right of the category name.
- L464 _private member_ `TWeakPtr<FDetailLayoutBuilderImpl> DetailLayoutBuilder;` — The parent detail builder
- L466 _private member_ `TSharedPtr<FOnPasteFromText> PasteFromTextDelegate;` — Delegate handling pasting an optionally tagged text snippet
- L468 _private member_ `TSharedPtr<FOnCopyToText> CopyToTextDelegate;` — Delegate handling copying a property to text. The default property handle copy will be used if not provided
- L471 _private member_ `FName CategoryName;` — The category identifier
- L473 _private member_ `int32 SortOrder;` — The sort order of this category (amongst all categories)
- L475 _private member_ `TOptional<FLinearColor> Color;` — The color that represents the category.
- L477 _private member_ `bool bRestoreExpansionState : 1;` — Whether or not to restore the expansion state between sessions
- L479 _private member_ `bool bShouldBeInitiallyCollapsed : 1;` — Whether or not the category should be initially collapsed
- L481 _private member_ `bool bUserShowAdvanced : 1;` — Whether or not advanced properties should be shown (as specified by the user)
- L483 _private member_ `bool bForceAdvanced : 1;` — Whether or not advanced properties are forced to be shown (this is an independent toggle from bShowAdvanced which is user driven)
- L485 _private member_ `bool bHasFilterStrings : 1;` — Whether or not the content in the category is being filtered
- L487 _private member_ `bool bHasVisibleDetails : 1;` — true if anything is visible in the category
- L489 _private member_ `bool bIsCategoryVisible : 1;` — true if the category is visible at all
- L491 _private member_ `bool bFavoriteCategory : 1;` — true if this category is the special favorite category, all property in the layout will be display when we generate the root tree
- L492 _private member_ `bool bShowOnlyChildren : 1;`
- L493 _private member_ `bool bHasVisibleAdvanced : 1;`
- L494 _private member_ `bool bPendingRefresh : 1;`
- L495 _private member_ `bool bPendingRefreshNeedsRefilter : 1;`
- L501 _private member_ `bool bIsEmpty : 1;` — If true, this Category should have no UProperty data associated with it, and will be shown as an empty stub with no expansion arrow

### `Source/Editor/PropertyEditor/Private/DetailCategoryGroupNode.h` (Private)


#### class `FDetailCategoryGroupNode`  
`class FDetailCategoryGroupNode : public FDetailTreeNode, public TSharedFromThis<FDetailCategoryGroupNode>`  
_L13-54_
- inherits: `FDetailTreeNode,TSharedFromThis<FDetailCategoryGroupNode>`
- L16 _public prototype_ `FDetailCategoryGroupNode(FName InGroupName, TSharedRef<FDetailCategoryImpl> InParentCategory);`
- L19 _public prototype_ `void SetChildren(const FDetailNodeList& InChildNodes);`
- L21 _public function_ `void SetShowBorder(bool bInShowBorder)`
- L22 _public function_ `bool GetShowBorder() const`
- L24 _public function_ `void SetHasSplitter(bool bInHasSplitter)`
- L25 _public function_ `bool GetHasSplitter() const`
- L28 _private function_ `virtual TSharedPtr<IDetailsView> GetNodeDetailsViewSharedPtr() const override`
- L29 _private function_ `virtual TSharedPtr<IDetailsViewPrivate> GetDetailsViewSharedPtr() const override`
- L30 _private function_ `virtual void OnItemExpansionChanged( bool bIsExpanded, bool bShouldSaveState) override`
- L31 _private function_ `virtual bool ShouldBeExpanded() const override`
- L32 _private function_ `virtual ENodeVisibility GetVisibility() const override`
- L33 _private prototype_ `virtual TSharedRef< ITableRow > GenerateWidgetForTableView( const TSharedRef<STableViewBase>& OwnerTable, bool bAllowFavoriteSystem) override;`
- L34 _private prototype_ `virtual bool GenerateStandaloneWidget(FDetailWidgetRow& OutRow) const override;`
- L36 _private function_ `virtual EDetailNodeType GetNodeType() const override`
- L37 _private function_ `virtual TSharedPtr<IPropertyHandle> CreatePropertyHandle() const override`
- L38 _private function_ `virtual void GetFilterStrings(TArray<FString>& OutFilterStrings) const override`
- L40 _private prototype_ `virtual void GetChildren(FDetailNodeList& OutChildren, const bool& bInIgnoreVisibility) override;`
- L41 _private prototype_ `virtual void FilterNode( const FDetailFilter& InFilter ) override;`
- L42 _private function_ `virtual void Tick( float DeltaTime ) override`
- L43 _private function_ `virtual bool ShouldShowOnlyChildren() const override`
- L44 _private function_ `virtual FName GetNodeName() const override`
- L47 _private member_ `FDetailNodeList ChildNodes;`
- L48 _private member_ `FDetailCategoryImpl& ParentCategory;`
- L49 _private member_ `FName GroupName;`
- L50 _private member_ `bool bShouldBeVisible;`
- L52 _private member_ `bool bShowBorder;`
- L53 _private member_ `bool bHasSplitter;`

### `Source/Editor/PropertyEditor/Private/DetailCustomBuilderRow.h` (Private)


#### class `FDetailCustomBuilderRow`  
`class FDetailCustomBuilderRow : public IDetailLayoutRow, public TSharedFromThis<FDetailCustomBuilderRow>`  
_L16-49_
- inherits: `IDetailLayoutRow,TSharedFromThis<FDetailCustomBuilderRow>`
- L19 _public prototype_ `FDetailCustomBuilderRow( TSharedRef<IDetailCustomNodeBuilder> CustomBuilder );`
- L20 _public prototype_ `virtual ~FDetailCustomBuilderRow() = default;`
- L23 _public function_ `virtual FName GetRowName() const override` — IDetailLayoutRow interface
- L24 _public prototype_ `virtual TOptional<FResetToDefaultOverride> GetCustomResetToDefault() const override;`
- L26 _public prototype_ `void Tick( float DeltaTime );`
- L27 _public prototype_ `bool RequiresTick() const;`
- L28 _public prototype_ `bool HasColumns() const;`
- L29 _public prototype_ `bool ShowOnlyChildren() const;`
- L30 _public prototype_ `void OnItemNodeInitialized( TSharedRef<FDetailItemNode> InTreeNode, TSharedRef<FDetailCategoryImpl> InParentCategory, const TAttribute<bool>& InIsParentEnabled );`
- L31 _public function_ `TSharedRef<IDetailCustomNodeBuilder> GetCustomBuilder() const`
- L32 _public prototype_ `FName GetCustomBuilderName() const;`
- L33 _public prototype_ `TSharedPtr<IPropertyHandle> GetPropertyHandle() const;`
- L34 _public prototype_ `void OnGenerateChildren( FDetailNodeList& OutChildren );`
- L35 _public prototype_ `bool IsInitiallyCollapsed() const;`
- L36 _public prototype_ `TSharedPtr<FDetailWidgetRow> GetWidgetRow() const;`
- L37 _public prototype_ `bool AreChildCustomizationsHidden() const;`
- L38 _public function_ `void SetOriginalPath(FStringView Path)`
- L39 _public function_ `const FString& GetOriginalPath() const`
- L43 _private member_ `TAttribute<bool> IsParentEnabled;` — Whether or not our parent is enabled
- L44 _private member_ `TSharedPtr<FDetailWidgetRow> HeaderRow;`
- L45 _private member_ `TSharedRef<class IDetailCustomNodeBuilder> CustomNodeBuilder;`
- L46 _private member_ `TSharedPtr<class FCustomChildrenBuilder> ChildrenBuilder;`
- L47 _private member_ `TWeakPtr<FDetailCategoryImpl> ParentCategory;`
- L48 _private member_ `FString OriginalPath;`

### `Source/Editor/PropertyEditor/Private/DetailFilter.h` (Private)


#### struct `FDetailFilter`  
`struct FDetailFilter`  
_L9-68_
- desc: Represents a filter which controls the visibility of items in the details view
- L11 _public function_ `FDetailFilter() : bShowOnlyModified(false) , bShowAllAdvanced(false) , bShowAllChildrenIfCategoryMatches(true) , bShowOnlyKeyable(false) , bShowOnlyAnimated(false) , bShowFavoritesCategory(false) , bShowOnlyAllowed(false) , bShowLooseProperties(false) , bShowHeaders(true)`
- L23 _public function_ `bool IsEmptyFilter() const`
- L39 _public member_ `TArray<FString> FilterStrings;` — Any user search terms that items must match
- L41 _public member_ `bool bShowOnlyModified;` — If we should only show modified properties
- L43 _public member_ `bool bShowAllAdvanced;` — If we should show all advanced properties
- L45 _public member_ `bool bShowAllChildrenIfCategoryMatches;` — If we should show all the children if their category name matches the search
- L47 _public member_ `bool bShowOnlyKeyable;` — If we should only show keyable properties
- L49 _public member_ `bool bShowOnlyAnimated;` — If we should only show animated properties
- L51 _public member_ `bool bShowFavoritesCategory;` — If we should show the favorites category.
- L53 _public member_ `bool bShowOnlyAllowed;` — If we should only show properties that match PropertyAllowList
- L55 _public member_ `bool bShowLooseProperties;` — If true, will also show loose properties
- L57 _public member_ `bool bShowHeaders;` — If true, category headers
- L59 _public member_ `TSet<FPropertyPath> PropertyAllowList;` — The set of allowed properties to show.
- L61 _public member_ `TSet<FName> VisibleSections;` — The set of selected sections to show. If empty, all sections are shown.
- L63 _public member_ `TSet<FName> VisibleCategories;` — The set of selected categories to show. If empty, all categories are shown.
- L66 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FShouldForceHideProperty, const TSharedRef<class IPropertyHandle>&);` — Delegate that determines whether a property should be forced hidden - evaluated on panel refresh
- L67 _public member_ `FShouldForceHideProperty ShouldForceHideProperty;`

#### Free symbols / members of external scopes

- L66 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FShouldForceHideProperty, const TSharedRef<class IPropertyHandle>&);` — Delegate that determines whether a property should be forced hidden - evaluated on panel refresh

### `Source/Editor/PropertyEditor/Private/DetailGroup.h` (Private)


#### class `FDetailGroup`  
`class FDetailGroup : public IDetailGroup, public TSharedFromThis<FDetailGroup>`  
_L18-163_
- inherits: `IDetailGroup,TSharedFromThis<FDetailGroup>`
- L21 _public prototype_ `FDetailGroup( const FName InGroupName, TSharedRef<FDetailCategoryImpl> InParentCategory, const FText& InLocalizedDisplayName, const bool bInStartExpanded = false );`
- L24 _public prototype_ `virtual FDetailWidgetRow& HeaderRow() override;` — IDetailGroup interface
- L25 _public prototype_ `virtual IDetailPropertyRow& HeaderProperty( TSharedRef<IPropertyHandle> PropertyHandle ) override;`
- L26 _public prototype_ `virtual FDetailWidgetRow& AddWidgetRow() override;`
- L27 _public prototype_ `virtual IDetailPropertyRow& AddPropertyRow( TSharedRef<IPropertyHandle> PropertyHandle ) override;`
- L28 _public prototype_ `virtual IDetailPropertyRow& AddExternalStructureProperty(TSharedPtr<IStructureDataProvider> StructDataProvider, FName PropertyName, EPropertyLocation::Type Location, const FAddPropertyParams& Params) override;`
- L29 _public prototype_ `virtual IDetailPropertyRow& AddExternalObjectProperty(const TArray<UObject*>& Objects, FName PropertyName, EPropertyLocation::Type Location, const FAddPropertyParams& Params) override;`
- L30 _public prototype_ `virtual IDetailGroup& AddGroup(FName NewGroupName, const FText& InLocalizedDisplayName, bool bInStartExpanded = false) override;`
- L31 _public prototype_ `virtual const TOptional<FText>& GetToolTip() const override;`
- L32 _public prototype_ `virtual void SetToolTip(const FText& ToolTip) override;`
- L33 _public prototype_ `virtual void ToggleExpansion( bool bExpand ) override;`
- L34 _public prototype_ `virtual bool GetExpansionState() const override;`
- L35 _public prototype_ `virtual void SetDisplayMode(EDetailGroupDisplayMode Mode) override;`
- L38 _public function_ `virtual FName GetRowName() const override` — IDetailLayoutRow interface
- L39 _public prototype_ `virtual TOptional<FResetToDefaultOverride> GetCustomResetToDefault() const override;`
- L41 _public prototype_ `TSharedPtr<FDetailPropertyRow> GetHeaderPropertyRow() const;`
- L42 _public prototype_ `TSharedPtr<FPropertyNode> GetHeaderPropertyNode() const;`
- L45 _public function_ `virtual FName GetGroupName() const override` — @return The name of the group
- L48 _public function_ `virtual int32 GetNumChildren() const override` — @return The number of child rows under this group
- L51 _public function_ `const FText& GetGroupDisplayName() const` — @return The localized display name of the group
- L54 _public prototype_ `bool HasColumns() const;` — Whether or not the group has columns
- L57 _public prototype_ `bool RequiresTick() const;` — @return true if this row should be ticked
- L60 _public function_ `bool ShouldStartExpanded() const` — @return true if this row should start expanded
- L63 _public function_ `EDetailGroupDisplayMode GetDisplayMode() const` — @return the display mode that this group should use
- L68 _public prototype_ `EVisibility GetGroupVisibility() const;` — @return The visibility of this group
- L77 _public prototype_ `void OnItemNodeInitialized( TSharedRef<class FDetailItemNode> InTreeNode, TSharedRef<FDetailCategoryImpl> InParentCategory, const TAttribute<bool>& InIsParentEnabled );` — Called by the owning item node when it has been initialized @param InTreeNode		The node that owns this group @param InParentCategory	The category this group is located in @param InIsParentEnabled	Whether or not the parent node is enabled
- L80 _public prototype_ `FDetailWidgetRow GetWidgetRow();` — @return the row which should be displayed for this group
- L87 _public prototype_ `void OnGenerateChildren( FDetailNodeList& OutChildren );` — Called to generate children of this group @param OutChildren	The list of children to add to
- L93 _public prototype_ `virtual void EnableReset(bool InValue);` — Permit resetting all the properties in the group
- L98 _public prototype_ `virtual TSharedPtr<IDetailPropertyRow> FindPropertyRow(TSharedRef<IPropertyHandle> PropertyHandle) const override;` — Return the property row associated with the specified property handle
- L103 _public function_ `virtual FDetailGroupReset& GetOnDetailGroupReset() override` — Return the delegate called when user press the Group Reset ui
- L108 _public function_ `virtual TSharedPtr<FOnPasteFromText> OnPasteFromText() const override` — Return an optional PasteFromText delegate
- L113 _public function_ `virtual TSharedPtr<FOnCopyToText> OnCopyToText() const override` — Return an optional PasteFromText delegate
- L120 _private prototype_ `FReply OnNameClicked();` — Called when the name of the group is clicked to expand the group
- L125 _private prototype_ `TSharedRef<SWidget> MakeNameWidget();` — Makes a name widget for this group
- L128 _private prototype_ `void OnResetClicked();` — Called when the "Reset to Default" button for the location has been clicked
- L129 _private prototype_ `bool IsResetVisible() const;`
- L130 _private prototype_ `bool GetAllChildrenPropertyHandles(TArray<TSharedPtr<IPropertyHandle>>& PropertyHandles) const;`
- L131 _private prototype_ `bool GetAllChildrenPropertyHandlesRecursive(const FDetailGroup* CurrentDetailGroup, TArray<TSharedPtr<IPropertyHandle>>& PropertyHandles) const;`
- L135 _private member_ `TArray<FDetailLayoutCustomization> GroupChildren;` — Customized group children
- L137 _private member_ `TSharedPtr<FDetailLayoutCustomization> HeaderCustomization;` — User customized header row
- L139 _private member_ `TWeakPtr<class FDetailItemNode> OwnerTreeNode;` — Owner node of this group
- L141 _private member_ `TWeakPtr<FDetailCategoryImpl> ParentCategory;` — Parent category of this group
- L143 _private member_ `TAttribute<bool> IsParentEnabled;` — Whether or not our parent is enabled
- L145 _private member_ `FText LocalizedDisplayName;` — Display name of this group
- L147 _private member_ `TOptional<FText> LocalizedToolTip;` — ToolTip for this group
- L149 _private member_ `FName GroupName;` — Name identifier of this group
- L151 _private member_ `bool bStartExpanded : 1;` — Whether the detail group should start expanded or not
- L153 _private member_ `bool bResetEnabled : 1;` — Permit resetting all the properties in the group
- L155 _private member_ `EDetailGroupDisplayMode DisplayMode;` — Whether the detail group should appear like it's a subcategory or not
- L157 _private member_ `FDetailGroupReset OnDetailGroupReset;` — Delegate called when user press the Group Reset ui
- L159 _private member_ `TSharedPtr<FOnPasteFromText> PasteFromTextDelegate;` — Delegate handling pasting an optionally tagged text snippet
- L161 _private member_ `TSharedPtr<FOnCopyToText> CopyToTextDelegate;` — Optional Delegate handling copying to a text snippet

### `Source/Editor/PropertyEditor/Private/DetailItemNode.h` (Private)


#### class `FDetailItemNode`  
`class FDetailItemNode : public FDetailTreeNode, public TSharedFromThis<FDetailItemNode>`  
_L18-138_
- inherits: `FDetailTreeNode,TSharedFromThis<FDetailItemNode>`
- desc: A single item in a detail tree
- L21 _public prototype_ `FDetailItemNode( const FDetailLayoutCustomization& InCustomization, TSharedRef<FDetailCategoryImpl> InParentCategory, TAttribute<bool> InIsParentEnabled, TSharedPtr<IDetailGroup> InParentGroup = nullptr);`
- L22 _public prototype_ `~FDetailItemNode();`
- L25 _public prototype_ `virtual EDetailNodeType GetNodeType() const override;` — IDetailTreeNode interface
- L26 _public prototype_ `virtual TSharedPtr<IPropertyHandle> CreatePropertyHandle() const override;`
- L27 _public prototype_ `virtual void GetFilterStrings(TArray<FString>& OutFilterStrings) const override;`
- L28 _public prototype_ `virtual bool GetInitiallyCollapsed() const override;`
- L29 _public prototype_ `virtual void RefreshVisibility() override;`
- L34 _public prototype_ `void Initialize();` — Initializes this node
- L36 _public prototype_ `void ToggleExpansion();`
- L38 _public prototype_ `void SetExpansionState(bool bWantsExpanded, bool bSaveState);`
- L39 _public prototype_ `void SetExpansionState(bool bWantsExpanded);`
- L45 _public prototype_ `void GenerateChildren( bool bUpdateFilteredNodes );` — Generates children for this node @param bUpdateFilteredNodes If true, details panel will re-filter to account for new nodes being added
- L50 _public prototype_ `bool HasMultiColumnWidget() const;` — @return TRUE if this node has a widget with multiple columns
- L55 _public function_ `bool HasGeneratedChildren() const` — @return true if this node has any children (regardless of child visibility)
- L60 _public prototype_ `EVisibility ComputeItemVisibility() const;` — @return The new, uncached visibility of this item.
- L65 _public prototype_ `void RefreshCachedVisibility(bool bCallChangeDelegate = false);` — updates the cached node visibility and optionally calls a tree refresh if it changed
- L68 _public function_ `virtual TSharedPtr<IDetailsView> GetNodeDetailsViewSharedPtr() const override` — FDetailTreeNode interface
- L69 _public function_ `virtual TSharedPtr<IDetailsViewPrivate> GetDetailsViewSharedPtr() const override`
- L70 _public prototype_ `virtual TSharedRef< ITableRow > GenerateWidgetForTableView( const TSharedRef<STableViewBase>& OwnerTable, bool bAllowFavoriteSystem) override;`
- L71 _public prototype_ `virtual bool GenerateStandaloneWidget(FDetailWidgetRow& OutRow) const override;`
- L72 _public prototype_ `virtual void GetChildren(FDetailNodeList& OutChildren, const bool& bInIgnoreVisibility = false) override;`
- L73 _public prototype_ `virtual void OnItemExpansionChanged( bool bInIsExpanded, bool bShouldSaveState) override;`
- L74 _public prototype_ `virtual bool ShouldBeExpanded() const override;`
- L75 _public prototype_ `virtual ENodeVisibility GetVisibility() const override;`
- L76 _public prototype_ `virtual void FilterNode( const FDetailFilter& InFilter ) override;`
- L77 _public prototype_ `virtual void Tick( float DeltaTime ) override;`
- L78 _public prototype_ `virtual bool ShouldShowOnlyChildren() const override;`
- L79 _public function_ `virtual FName GetNodeName() const override`
- L80 _public function_ `virtual TSharedPtr<FDetailCategoryImpl> GetParentCategory() const override`
- L81 _public prototype_ `virtual FPropertyPath GetPropertyPath() const override;`
- L82 _public function_ `virtual void SetIsHighlighted(bool bInIsHighlighted) override`
- L83 _public function_ `virtual bool IsHighlighted() const override`
- L84 _public function_ `virtual bool IsLeaf() override`
- L85 _public prototype_ `virtual TAttribute<bool> IsPropertyEditingEnabled() const override;`
- L86 _public prototype_ `virtual TSharedPtr<FPropertyNode> GetPropertyNode() const override;`
- L87 _public prototype_ `virtual void GetAllPropertyNodes(TArray<TSharedRef<FPropertyNode>>& OutNodes) const override;`
- L88 _public prototype_ `virtual TSharedPtr<FComplexPropertyNode> GetExternalRootPropertyNode() const override;`
- L89 _public prototype_ `virtual TSharedPtr<IDetailPropertyRow> GetRow() const override;`
- L96 _private prototype_ `void InitPropertyEditor();` — Initializes the property editor on this node
- L101 _private prototype_ `void InitCustomBuilder();` — Initializes the custom builder on this node
- L106 _private prototype_ `void InitGroup();` — Initializes the detail group on this node
- L111 _private prototype_ `bool IsPropertyEditingEnabledImpl() const;` — Implementation of IsPropertyEditingEnabled
- L115 _private member_ `FDetailLayoutCustomization Customization;` — Customization on this node
- L117 _private member_ `FDetailNodeList Children;` — Child nodes of this node
- L119 _private member_ `TWeakPtr<FDetailCategoryImpl> ParentCategory;` — Parent categories on this node
- L121 _private member_ `TWeakPtr<IDetailGroup> ParentGroup;` — Parent group on this node
- L123 _private member_ `TAttribute<bool> IsParentEnabled;` — Attribute for checking if our parent is enabled
- L125 _private member_ `EVisibility CachedItemVisibility;` — Cached visibility of this node
- L127 _private member_ `bool bForceHidden;` — If true, this node will be hidden regardless of if it's parent or children would've otherwise overridden the filter result
- L129 _private member_ `bool bShouldBeVisibleDueToFiltering;` — True if this node passes filtering
- L131 _private member_ `bool bShouldBeVisibleDueToChildFiltering;` — True if this node is visible because its children are filtered successfully
- L133 _private member_ `bool bTickable;` — True if this node should be ticked
- L135 _private member_ `bool bIsExpanded;` — True if this node is expanded
- L137 _private member_ `bool bIsHighlighted;` — True if this node is highlighted

### `Source/Editor/PropertyEditor/Private/DetailLayoutBuilderImpl.h` (Private)


#### class `FDetailLayoutBuilderImpl`  
`class FDetailLayoutBuilderImpl : public IDetailLayoutBuilder, public TSharedFromThis<FDetailLayoutBuilderImpl>`  
_L17-307_
- inherits: `IDetailLayoutBuilder,TSharedFromThis<FDetailLayoutBuilderImpl>`
- L20 _public prototype_ `FDetailLayoutBuilderImpl( TSharedPtr<FComplexPropertyNode>& InRootNode, FClassToPropertyMap& InPropertyMap, const TSharedRef<IPropertyUtilities>& InPropertyUtilities, const TSharedRef<IPropertyGenerationUtilities>& InPropertyGenerationUtilities, const TSharedPtr<IDetailsViewPrivate>& InDetailsView, bool bIsExternal);`
- L31 _public prototype_ `virtual TSharedPtr<const IDetailsView> GetDetailsViewSharedPtr() const override;` — IDetailLayoutBuilder Interface
- L32 _public prototype_ `virtual void GetObjectsBeingCustomized(TArray< TWeakObjectPtr<UObject> >& OutObjects) const override;`
- L33 _public prototype_ `virtual void GetStructsBeingCustomized(TArray< TSharedPtr<FStructOnScope> >& OutStructs) const override;`
- L34 _public prototype_ `virtual IDetailCategoryBuilder& EditCategory(FName CategoryName, const FText& NewLocalizedDisplayName = FText::GetEmpty(), ECategoryPriority::Type CategoryType = ECategoryPriority::Default) override;`
- L35 _public prototype_ `virtual IDetailCategoryBuilder& EditCategoryAllowNone(FName CategoryName, const FText& NewLocalizedDisplayName = FText::GetEmpty(), ECategoryPriority::Type CategoryType = ECategoryPriority::Default) override;`
- L36 _public prototype_ `virtual void GetCategoryNames(TArray<FName>& OutCategoryNames) const override;`
- L37 _public prototype_ `virtual IDetailPropertyRow& AddPropertyToCategory(TSharedPtr<IPropertyHandle> InPropertyHandle) override;`
- L38 _public prototype_ `virtual FDetailWidgetRow& AddCustomRowToCategory(TSharedPtr<IPropertyHandle> InPropertyHandle, const FText& InCustomSearchString, bool bForAdvanced = false) override;`
- L39 _public prototype_ `virtual TSharedPtr<IPropertyHandle> AddObjectPropertyData(TConstArrayView<UObject*> Objects, FName PropertyName) override;`
- L40 _public prototype_ `virtual TSharedPtr<IPropertyHandle> AddStructurePropertyData(const TSharedPtr<FStructOnScope>& StructData, FName PropertyName) override;`
- L41 _public prototype_ `virtual IDetailPropertyRow* EditDefaultProperty(TSharedPtr<IPropertyHandle> InPropertyHandle) override;`
- L42 _public prototype_ `virtual IDetailPropertyRow* EditPropertyFromRoot(TSharedPtr<IPropertyHandle> InPropertyHandle) override;`
- L43 _public prototype_ `virtual bool DoesCategoryHaveGeneratedChildren(FName CategoryName) override;`
- L44 _public prototype_ `virtual TSharedRef<IPropertyHandle> GetProperty(const FName PropertyPath, const UStruct* ClassOutermost, FName InInstanceName) const override;`
- L45 _public prototype_ `virtual FName GetTopLevelProperty() override;`
- L46 _public prototype_ `virtual void HideProperty(const TSharedPtr<IPropertyHandle> Property) override;`
- L47 _public prototype_ `virtual void HideProperty(FName PropertyPath, const UStruct* ClassOutermost = NULL, FName InstanceName = NAME_None) override;`
- L48 _public prototype_ `virtual void ForceRefreshDetails() override;`
- L49 _public prototype_ `virtual TSharedPtr<FAssetThumbnailPool> GetThumbnailPool() const override;`
- L50 _public prototype_ `virtual bool IsPropertyVisible(TSharedRef<IPropertyHandle> PropertyHandle) const override;`
- L51 _public prototype_ `virtual bool IsPropertyVisible(const struct FPropertyAndParent& PropertyAndParent) const override;`
- L52 _public prototype_ `virtual void HideCategory(FName CategoryName) override;`
- L53 _public prototype_ `virtual TSharedRef<IPropertyUtilities> GetPropertyUtilities() const override;`
- L54 _public prototype_ `virtual UClass* GetBaseClass() const override;`
- L55 _public prototype_ `virtual const TArray<TWeakObjectPtr<UObject>>& GetSelectedObjects() const override;`
- L56 _public prototype_ `virtual bool HasClassDefaultObject() const override;`
- L57 _public prototype_ `virtual void RegisterInstancedCustomPropertyTypeLayout(FName PropertyTypeName, FOnGetPropertyTypeCustomizationInstance PropertyTypeLayoutDelegate, TSharedPtr<IPropertyTypeIdentifier> Identifier = nullptr) override;`
- L58 _public prototype_ `virtual void SortCategories(const FOnCategorySortOrderFunction& SortFunction) override;`
- L59 _public prototype_ `virtual void SetPropertyGenerationAllowListPaths(const TSet<FString>& InPropertyGenerationAllowListPaths) override;`
- L60 _public prototype_ `virtual bool IsPropertyPathAllowed(const FString& InPath) const override;`
- L61 _public prototype_ `virtual void DisableInstancedReference(TSharedRef<IPropertyHandle> PropertyHandle) const override;`
- L71 _public prototype_ `bool AddEmptyCategoryIfNeeded(TSharedPtr<FComplexPropertyNode> Node);` — Creates an empty category row if there currently are no categories and one is required for the @code TSharedPtr<FComplexPropertyNode> @endcode Node @param Node The @code TSharedPtr<FComplexPropertyNode> @endcode that we will add an empty category for, if needed @return true if an empty/stub category was added, else it returns false
- L78 _public prototype_ `FDetailCategoryImpl& DefaultCategory(FName CategoryName);` — Creates a default category. The SDetails view will generate widgets in default categories @param CategoryName	The name of the category to create
- L83 _public prototype_ `TSharedPtr<FDetailCategoryImpl> GetSubCategoryImpl(FName CategoryName) const;` — Find a subcategory with the given name, if it exists
- L88 _public prototype_ `bool HasCategory(FName CategoryName) const;` — @returns true if a category with the given name exists
- L93 _public prototype_ `void GenerateDetailLayout();` — Generates the layout for this detail builder
- L98 _public prototype_ `void FilterDetailLayout(const FDetailFilter& InFilter);` — Filters the layout based on the passed in filter
- L107 _public prototype_ `void SetCurrentCustomizationClass(UStruct* CurrentClass, FName VariableName);` — Sets the current class being asked for customization Used for looking up properties if a class is not provided @param CurrentClass	The current class being customized @param VariableName The variable name of the class being customized (used for inner classes/structs where there can be multiple instances of them)
- L110 _public function_ `FName GetCurrentCustomizationVariableName() const` — @return The current class variable name being customized
- L119 _public prototype_ `TSharedPtr<FPropertyNode> GetPropertyNode(FName PropertyPath, const UStruct* ClassOutermost, FName InstanceName) const;` — Finds a property node for the current property @param PropertyPath	The path to the property @param ClassOutermost	The outer class of the property @return The found property node
- L126 _public prototype_ `TSharedPtr<FPropertyNode> GetPropertyNode(TSharedPtr<IPropertyHandle> PropertyHandle) const;` — Gets the property node from the provided handle @param PropertyHandle	The property handle to get the node from
- L133 _public prototype_ `void SetCustomProperty(const TSharedPtr<FPropertyNode>& PropertyNode);` — Marks a property as customized @param PropertyNode	The property node to mark as customized
- L138 _public function_ `FDetailNodeList& GetFilteredRootTreeNodes()` — @return All tree nodes that should be visible in the tree
- L143 _public function_ `FDetailNodeList& GetAllRootTreeNodes()` — @return All root tree nodes, regardless of visibility.
- L148 _public function_ `bool HasDetails() const` — @return true if the layout has any details
- L153 _public prototype_ `void Tick(float DeltaTime);` — Ticks tickable nodes (if any)
- L160 _public prototype_ `void AddTickableNode(FDetailTreeNode& TickableNode);` — Adds a node that should be ticked each frame @param TickableNode	The node to tick
- L167 _public prototype_ `void RemoveTickableNode(FDetailTreeNode& TickableNode);` — Removes a node that should no longer be ticked each frame @param TickableNode	The node to remove
- L172 _public function_ `const FDetailFilter& GetCurrentFilter() const` — @return The current filter that is being used to show or hide rows
- L180 _public prototype_ `void SaveExpansionState(const FString& NodePath, bool bIsExpanded);` — Saves the expansion state of a tree node @param NodePath	The path to the detail node to save @param bIsExpanded	true if the node is expanded, false otherwise
- L188 _public prototype_ `bool GetSavedExpansionState(const FString& NodePath) const;` — Gets the saved expansion state of a tree node in this category @param NodePath	The path to the detail node to get @return true if the node should be expanded, false otherwise
- L195 _public prototype_ `TSharedRef<IPropertyHandle> GetPropertyHandle(TSharedPtr<FPropertyNode> PropertyNodePtr) const;` — Makes a property handle from a property node @param PropertyNodePtr	The property node to make a handle for.
- L202 _public prototype_ `void AddExternalRootPropertyNode(TSharedRef<FComplexPropertyNode> InExternalRootNode);` — Adds an external property root node to the list of root nodes that the details new needs to manage @param InExternalRootNode		The node to add
- L209 _public prototype_ `void RemoveExternalRootPropertyNode(TSharedRef<FComplexPropertyNode> InExternalRootNode);` — Removes an external property root node to the list of root nodes that the details new needs to manage @param InExternalRootNode		The node to remove
- L211 _public prototype_ `void ClearExternalRootPropertyNodes();`
- L214 _public function_ `TSharedPtr<IDetailsView> GetDetailsViewSharedPtr() override` — @return The details view that owns this layout
- L216 _public function_ `TSharedPtr<FComplexPropertyNode> GetRootNode() const` — @return The root node for this customization
- L218 _public function_ `FRootPropertyNodeList& GetExternalRootPropertyNodes()`
- L221 _public function_ `bool IsLayoutForExternalRoot() const` — @return True if the layout is for an external root property node and not in the main set of objects the details panel is observing
- L224 _public prototype_ `FDelegateHandle AddNodeVisibilityChangedHandler(FSimpleMulticastDelegate::FDelegate InOnNodeVisibilityChanged);` — Adds a handler for when a node this builder owns has had a forced visibility change.
- L227 _public prototype_ `void RemoveNodeVisibilityChangedHandler(FDelegateHandle DelegateHandle);` — Removes a handler for when a node this builder owns has had a forced visibility change.
- L230 _public prototype_ `void NotifyNodeVisibilityChanged();` — Notifies this detail layout builder that a node it owns had it's visibility forcibly changed.
- L233 _public prototype_ `IPropertyGenerationUtilities& GetPropertyGenerationUtilities() const;` — Gets internal utilities for generating property layouts.
- L236 _public prototype_ `FCustomPropertyTypeLayoutMap GetInstancedPropertyTypeLayoutMap() const;` — Combines the type layout map from our PropertyGenerationUtilities object, with the local InstancePropertyTypeExtensions map - which provides instance based customizations/overrides.
- L238 _public prototype_ `void RefreshNodeVisbility();`
- L249 _private prototype_ `TSharedPtr<FPropertyNode> GetPropertyNodeInternal( FName PropertyPath, const UStruct* ClassOutermost, FName InstanceName ) const;` — Finds a property node for the current property by searching in a fast lookup map or a path search if required @param PropertyPath	The path to the property @param ClassOutermost	The outer class of the property @param bMarkPropertyAsCustomized	Whether or not to mark the property as customized so it does not appear in the default layout @return The found property node
- L254 _private prototype_ `void BuildCategories( const FCategoryMap& CategoryMap, TArray< TSharedRef<FDetailCategoryImpl> >& OutSimpleCategories, TArray< TSharedRef<FDetailCategoryImpl> >& OutAdvancedCategories );` — Builds a list of simple and advanced categories that should be displayed
- L258 _private member_ `TWeakPtr<FComplexPropertyNode> RootNode;` — The root property node for this customization
- L260 _private member_ `FRootPropertyNodeList ExternalRootPropertyNodes;` — External property nodes which need to validated each tick
- L262 _private member_ `FCategoryMap CustomCategoryMap;` — A mapping of category names to categories which have been customized
- L264 _private member_ `FCategoryMap DefaultCategoryMap;` — A mapping of category names to categories which have been not customized
- L266 _private member_ `FCategoryMap SubCategoryMap;` — Mapping of subcategory names to their subcategory builder
- L268 _private member_ `FClassToPropertyMap& PropertyMap;` — A mapping of classes to top level properties in that class
- L270 _private member_ `TSet<FName> ForceHiddenCategories;` — Force hidden categories set by the user
- L272 _private member_ `TSet<FString> PropertyGenerationAllowListPaths;` — If not empty only nodes for property specified paths will be generated
- L274 _private member_ `TSet<FDetailTreeNode*> TickableNodes;` — Nodes that require ticking
- L276 _private member_ `TSet<FDetailTreeNode*> TickableNodesToAdd;` — Nodes to add to being ticked, only used while iterating
- L278 _private member_ `TSet<FDetailTreeNode*> TickableNodesToRemove;` — Nodes to remove from being ticked, only used while iterating
- L280 _private member_ `FDetailFilter CurrentFilter;` — Current filter applied to the view
- L282 _private member_ `FDetailNodeList AllRootTreeNodes;` — All RootTreeNodes
- L284 _private member_ `FDetailNodeList FilteredRootTreeNodes;` — All generated category widgets for rebuilding them if needed
- L286 _private member_ `FName CurrentCustomizationVariableName;` — The current variable name of the class being customized (inner class instances)
- L288 _private member_ `const TWeakPtr<IPropertyUtilities> PropertyDetailsUtilities;` — The global property utilties.  This is weak to avoid circular ref but it should always be valid if this class exists
- L290 _private member_ `const TWeakPtr<IPropertyGenerationUtilities> PropertyGenerationUtilities;` — Internal utilities for generating property layouts.
- L292 _private member_ `TWeakPtr<IDetailsViewPrivate> DetailsView;` — The view where this detail customizer resides
- L294 _private member_ `UStruct* CurrentCustomizationClass;` — The current class being customized
- L296 _private member_ `bool bLayoutForExternalRoot;` — True if the layout is for an external root property node and not in the main set of objects the details panel is observing
- L298 _private member_ `bool bIsIteratingTickableNodes = false;` — True if the layout is for an external root property node and not in the main set of objects the details panel is observing
- L300 _private member_ `FSimpleMulticastDelegate OnNodeVisibilityChanged;` — A delegate which is called whenever a node owned by this layout builder has it's visibility forcibly changed.
- L303 _private member_ `TArray<FOnCategorySortOrderFunction> CategorySortOrderFunctions;` — Optionally provided functions to sort categories, which allow caller to reconfigure sort order.
- L306 _private member_ `FCustomPropertyTypeLayoutMap InstancePropertyTypeExtensions;` — Local customizations for this detail layout only. Provides a way for IDetailCustomizations to override type customizations without polluting customizations for other instances.

### `Source/Editor/PropertyEditor/Private/DetailLayoutHelpers.h` (Private)


#### struct `DetailLayoutHelpers::FUpdatePropertyMapArgs`  
`struct FUpdatePropertyMapArgs`  
_L13-19_
- L15 _public member_ `FDetailLayoutData* LayoutData;`
- L16 _public member_ `FCustomPropertyTypeLayoutMap* InstancedPropertyTypeToDetailLayoutMap;`
- L17 _public member_ `bool bEnableFavoriteSystem;`
- L18 _public member_ `bool bUpdateFavoriteSystemOnly;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace DetailLayoutHelpers`
- L28 _prototype_ `void UpdateSinglePropertyMapRecursive(FPropertyNode& InNode, FName CurCategory, FComplexPropertyNode* CurObjectNode, FUpdatePropertyMapArgs& InUpdateArgs);` (scope `DetailLayoutHelpers`) — Recursively updates children of property nodes. Generates default layout for properties @param InNode	The parent node to get children from @param The detail layout builder that will be used for customization of this property map @param CurCategory The current category name
- L33 _prototype_ `void QueryCustomDetailLayout(FDetailLayoutData& LayoutData, const FCustomDetailLayoutMap& InstancedDetailLayoutMap, const FOnGetDetailCustomizationInstance& GenericLayoutDelegate);` (scope `DetailLayoutHelpers`) — Calls a delegate for each registered class that has properties visible to get any custom detail layouts

### `Source/Editor/PropertyEditor/Private/DetailMultiTopLevelObjectRootNode.h` (Private)


#### class `SDetailMultiTopLevelObjectTableRow`  
`class SDetailMultiTopLevelObjectTableRow : public SDetailTableRowBase`  
_L20-43_
- inherits: `SDetailTableRowBase`
- L23 _public function_ `SLATE_BEGIN_ARGS(SDetailMultiTopLevelObjectTableRow) : _DisplayName() , _ExpansionArrowUsage(EExpansionArrowUsage::None)`
- L27 _public prototype_ `SLATE_ARGUMENT( FText, DisplayName ) SLATE_ARGUMENT(IDetailRootObjectCustomization::EExpansionArrowUsage, ExpansionArrowUsage) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FDetailTreeNode> InOwnerTreeNode, const TSharedRef<STableViewBase>& InOwnerTableView);`
- L32 _public prototype_ `void SetContent(TSharedRef<SWidget> InContent) override;`
- L35 _private prototype_ `const FSlateBrush* GetBackgroundImage() const;`
- L36 _private prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L37 _private prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L40 _private member_ `EExpansionArrowUsage ExpansionArrowUsage;`
- L41 _private member_ `SHorizontalBox::FSlot* ContentSlot = nullptr;`
- L42 _private member_ `TWeakPtr<STableViewBase> OwnerTableViewWeak;`

#### class `FDetailMultiTopLevelObjectRootNode`  
`class FDetailMultiTopLevelObjectRootNode : public FDetailTreeNode, public TSharedFromThis<FDetailMultiTopLevelObjectRootNode>`  
_L45-76_
- inherits: `FDetailTreeNode,TSharedFromThis<FDetailMultiTopLevelObjectRootNode>`
- L48 _public prototype_ `FDetailMultiTopLevelObjectRootNode(const TSharedPtr<IDetailRootObjectCustomization>& RootObjectCustomization, const TSharedPtr<IDetailsViewPrivate>& InDetailsView, const FObjectPropertyNode* RootNode);`
- L49 _public prototype_ `void SetChildren(const FDetailNodeList& InChildNodes);`
- L51 _private function_ `virtual TSharedPtr<IDetailsView> GetNodeDetailsViewSharedPtr() const override`
- L52 _private function_ `virtual TSharedPtr<IDetailsViewPrivate> GetDetailsViewSharedPtr() const override`
- L53 _private prototype_ `virtual void OnItemExpansionChanged(bool bIsExpanded, bool bShouldSaveState) override;`
- L54 _private prototype_ `virtual bool ShouldBeExpanded() const override;`
- L55 _private prototype_ `virtual ENodeVisibility GetVisibility() const override;`
- L56 _private prototype_ `virtual TSharedRef<ITableRow> GenerateWidgetForTableView(const TSharedRef<STableViewBase>& OwnerTable, bool bAllowFavoriteSystem) override;`
- L57 _private prototype_ `virtual bool GenerateStandaloneWidget(FDetailWidgetRow& OutRow) const override;`
- L58 _private prototype_ `virtual void GetChildren(FDetailNodeList& OutChildren, const bool& bInIgnoreVisibility) override;`
- L59 _private prototype_ `virtual void FilterNode(const FDetailFilter& InFilter) override;`
- L60 _private function_ `virtual void Tick(float DeltaTime) override`
- L61 _private prototype_ `virtual bool ShouldShowOnlyChildren() const override;`
- L62 _private function_ `virtual FName GetNodeName() const override`
- L63 _private function_ `virtual EDetailNodeType GetNodeType() const override`
- L64 _private function_ `virtual TSharedPtr<IPropertyHandle> CreatePropertyHandle() const override`
- L65 _private prototype_ `void GenerateWidget_Internal(FDetailWidgetRow& Row, TSharedPtr<SDetailMultiTopLevelObjectTableRow> TableRow) const;`
- L68 _private member_ `FDetailNodeList ChildNodes;`
- L69 _private member_ `TWeakPtr<IDetailsViewPrivate> DetailsView;`
- L70 _private member_ `TWeakPtr<IDetailRootObjectCustomization> RootObjectCustomization;`
- L71 _private member_ `FDetailsObjectSet RootObjectSet;`
- L72 _private member_ `const UClass* CommonBaseClass;`
- L73 _private member_ `FName NodeName;`
- L74 _private member_ `bool bShouldBeVisible;`
- L75 _private member_ `bool bHasFilterStrings;`

#### Free symbols / members of external scopes

- L18 _typedef_ `using EExpansionArrowUsage = IDetailRootObjectCustomization::EExpansionArrowUsage;`

### `Source/Editor/PropertyEditor/Private/DetailPropertyRow.h` (Private)


#### class `FDetailPropertyRow`  
`class FDetailPropertyRow : public IDetailPropertyRow, public IPropertyTypeCustomizationUtils, public IDetailLayoutRow, public TSharedFromThis<FDetailPropertyRow>`  
_L23-263_
- inherits: `IDetailPropertyRow,IPropertyTypeCustomizationUtils,IDetailLayoutRow,TSharedFromThis<FDetailPropertyRow>`
- L26 _public prototype_ `FDetailPropertyRow(TSharedPtr<FPropertyNode> InPropertyNode, TSharedRef<FDetailCategoryImpl> InParentCategory, TSharedPtr<FComplexPropertyNode> InExternalRootNode = nullptr);`
- L29 _public function_ `virtual TSharedPtr<IPropertyHandle> GetPropertyHandle() const override` — IDetailPropertyRow interface
- L30 _public prototype_ `virtual IDetailPropertyRow& DisplayName( const FText& InDisplayName ) override;`
- L31 _public prototype_ `virtual IDetailPropertyRow& ToolTip( const FText& InToolTip ) override;`
- L32 _public prototype_ `virtual IDetailPropertyRow& ShowPropertyButtons( bool bInShowPropertyButtons ) override;`
- L33 _public prototype_ `virtual IDetailPropertyRow& EditCondition( TAttribute<bool> EditConditionValue, FOnBooleanValueChanged OnEditConditionValueChanged, ECustomEditConditionMode EditConditionMode = ECustomEditConditionMode::Override ) override;`
- L34 _public prototype_ `virtual IDetailPropertyRow& EditConditionHides(bool bEditConditionHideValue) override;`
- L35 _public prototype_ `virtual IDetailPropertyRow& IsEnabled(TAttribute<bool> InIsEnabled) override;`
- L36 _public prototype_ `virtual IDetailPropertyRow& ShouldAutoExpand(bool bForceExpansion) override;`
- L37 _public prototype_ `virtual IDetailPropertyRow& Visibility( TAttribute<EVisibility> Visibility ) override;`
- L38 _public prototype_ `virtual IDetailPropertyRow& OverrideResetToDefault(const FResetToDefaultOverride& ResetToDefault) override;`
- L39 _public prototype_ `virtual IDetailPropertyRow& DragDropHandler(TSharedPtr<IDetailDragDropHandler> InDragDropHandler) override;`
- L40 _public prototype_ `virtual bool IsExpanded() const override;`
- L41 _public prototype_ `virtual FDetailWidgetRow& CustomWidget( bool bShowChildren = false ) override;`
- L42 _public prototype_ `virtual FDetailWidgetDecl* CustomNameWidget() override;`
- L43 _public prototype_ `virtual FDetailWidgetDecl* CustomValueWidget() override;`
- L44 _public prototype_ `virtual FDetailWidgetDecl* CustomResetToDefaultWidget() override;`
- L45 _public prototype_ `virtual void GetDefaultWidgets( TSharedPtr<SWidget>& OutNameWidget, TSharedPtr<SWidget>& OutValueWidget, bool bAddWidgetDecoration = false) override;`
- L46 _public prototype_ `virtual void GetDefaultWidgets( TSharedPtr<SWidget>& OutNameWidget, TSharedPtr<SWidget>& OutValueWidget, FDetailWidgetRow& Row, bool bAddWidgetDecoration = false) override;`
- L49 _public prototype_ `virtual TSharedPtr<class FAssetThumbnailPool> GetThumbnailPool() const override;` — IPropertyTypeCustomizationUtils interface
- L50 _public prototype_ `virtual TSharedPtr<class IPropertyUtilities> GetPropertyUtilities() const override;`
- L53 _public prototype_ `virtual FName GetRowName() const override;` — IDetailLayoutRow interface
- L54 _public function_ `virtual TOptional<FResetToDefaultOverride> GetCustomResetToDefault() const override`
- L58 _public prototype_ `bool HasColumns() const;` — @return true if this row has widgets with columns
- L61 _public prototype_ `bool ShowOnlyChildren() const;` — @return true if this row shows only children and is not visible itself
- L64 _public prototype_ `bool RequiresTick() const;` — @return true if this row should be ticked
- L67 _public function_ `bool HasExternalProperty() const` — @return true if this row has an external property
- L70 _public function_ `void SetCustomExpansionId(const FName ExpansionIdName)` — Sets the custom name that should be used to save and restore this nodes expansion state
- L73 _public function_ `FName GetCustomExpansionId() const` — @return Gets the custom name that should be used to save and restore this nodes expansion state
- L79 _public function_ `void SetForceShowOnlyChildren(bool bInForceShowOnlyChildren)` — Sets whether or not we force only children to be shown regardless of what the customization wants. Typically used when this row is only for organizational purposes and doesnt have anything valid to show (like external object nodes)
- L87 _public prototype_ `void OnItemNodeInitialized( TSharedRef<FDetailCategoryImpl> InParentCategory, const TAttribute<bool>& InIsParentEnabled, TSharedPtr<IDetailGroup> InParentGroup);` — Called when the owner node is initialized @param InParentCategory	The category that this property is in @param InIsParentEnabled	Whether or not our parent is enabled
- L90 _public prototype_ `FDetailWidgetRow GetWidgetRow();` — @return The widget row that should be displayed for this property row
- L93 _public prototype_ `TArrayView<TSharedPtr<IPropertyHandle>> GetPropertyHandles() const;` — @return properties being customized
- L96 _public prototype_ `FText GetFilterTextString() const;` — @return the filter text associated with this row, if any
- L101 _public function_ `TSharedPtr<FPropertyNode> GetPropertyNode() const` — @return The property node for this row
- L106 _public function_ `TSharedPtr<FComplexPropertyNode> GetExternalRootNode() const` — @return The external root node for this row if it has one.
- L111 _public function_ `TSharedPtr<FPropertyEditor> GetPropertyEditor()` — @return The property editor for this row
- L118 _public prototype_ `void OnGenerateChildren( FDetailNodeList& OutChildren );` — Called when children of this row should be generated @param OutChildren	The list of children created
- L123 _public prototype_ `bool GetForceAutoExpansion() const;` — @return Whether or not this row wants to force expansion
- L128 _public prototype_ `EVisibility GetPropertyVisibility() const;` — @return The visibility of this property
- L130 _public prototype_ `static void MakeExternalPropertyRowCustomization(TSharedPtr<FStructOnScope> StructData, FName PropertyName, TSharedRef<FDetailCategoryImpl> ParentCategory, struct FDetailLayoutCustomization& OutCustomization, const FAddPropertyParams& Parameters);`
- L131 _public prototype_ `static void MakeExternalPropertyRowCustomization(TSharedPtr<IStructureDataProvider> StructDataProvider, FName PropertyName, TSharedRef<FDetailCategoryImpl> ParentCategory, struct FDetailLayoutCustomization& OutCustomization, const FAddPropertyParams& Parameters);`
- L132 _public prototype_ `static void MakeExternalPropertyRowCustomization(const TArray<UObject*>& InObjects, FName PropertyName, TSharedRef<FDetailCategoryImpl> ParentCategory, struct FDetailLayoutCustomization& OutCustomization, const FAddPropertyParams& Parameters);`
- L133 _public prototype_ `static void MakeChildPropertyRowCustomization(TSharedRef<IPropertyHandle> PropertyHandle, TSharedPtr<IStructureDataProvider> StructDataProvider, FName PropertyName, TSharedRef<FDetailCategoryImpl> ParentCategory, struct FDetailLayoutCustomization& OutCustomization, const FAddPropertyParams& Parameters, const FText& DisplayNameOverride = FText());`
- L139 _private prototype_ `void MakeNameOrKeyWidget( FDetailWidgetRow& Row, const TSharedPtr<FDetailWidgetRow> InCustomRow ) const;` — Makes a name widget or key widget for the tree
- L144 _private prototype_ `void MakeValueWidget( FDetailWidgetRow& Row, const TSharedPtr<FDetailWidgetRow> InCustomRow, bool bAddWidgetDecoration = true ) const;` — Makes the value widget for the tree
- L149 _private prototype_ `void SetWidgetRowProperties( FDetailWidgetRow& Row ) const;` — Set the given widget row's custom properties. Note: Should be called before MakeNameOrKeyWidget and MakeValueWidget.
- L154 _private prototype_ `bool HasEditCondition() const;` — @return true if this row has an edit condition
- L159 _private prototype_ `bool GetEnabledState() const;` — @return Whether or not this row is enabled
- L164 _private prototype_ `bool IsEditConditionMet() const;` — @return true if this row's edit condition has been met
- L169 _private prototype_ `bool IsOnlyVisibleWhenEditConditionMet() const;` — @return true if this row should be shown/hidden based on the edit condition state
- L179 _private prototype_ `TSharedPtr<IPropertyTypeCustomization>& GetTypeInterface();` — Looks up and caches (if not already) the associated type interface, and then returns it. Could be null/invalid if no customization was specified for this row. Creating the CustomTypeInterface on demand, instead of at construction, allows for IDetailCustomization's to override custom property type layouts via a IDetailLayoutBuilder.
- L187 _private prototype_ `void GenerateChildrenForPropertyNode( TSharedPtr<FPropertyNode>& RootPropertyNode, FDetailNodeList& OutChildren );` — Generates children for the property node @param RootPropertyNode	The property node to generate children for (May be a child of the property node being stored) @param OutChildren	The list of children created
- L196 _private prototype_ `static TSharedRef<FPropertyEditor> MakePropertyEditor( const TSharedRef<FPropertyNode>& InPropertyNode, const TSharedRef<IPropertyUtilities>& PropertyUtilities, TSharedPtr<FPropertyEditor>& InEditor );` — Makes a property editor from the property node on this row @param InPropertyNode	The node to create the editor for @param PropertyUtilities	Utilities for the property editor @param InEditor			The editor we wish to create if it does not yet exist.
- L205 _private prototype_ `static TSharedPtr<IPropertyTypeCustomization> GetPropertyCustomization( const TSharedRef<FPropertyNode>& InPropertyNode, const TSharedRef<FDetailCategoryImpl>& InParentCategory );` — Gets the property customization for the specified node @param	InPropertyNode		The node to check for customizations @param	InParentCategory	The node's parent category @return	The property customization for the node, or null if one does not exist
- L208 _private prototype_ `static bool NeedsKeyNode(TSharedRef<FPropertyNode> InPropertyNode, TSharedRef<FDetailCategoryImpl> InParentCategory);` — Does the given property node require a key node to be created, or is a key property editor sufficient?
- L212 _private member_ `TAttribute<bool> CustomIsEnabledAttrib;` — User driven enabled state
- L214 _private member_ `TAttribute<bool> IsParentEnabled;` — Whether or not our parent is enabled
- L216 _private member_ `TAttribute<EVisibility> PropertyVisibility;` — Visibility of the property
- L218 _private member_ `TSharedPtr<IPropertyTypeCustomization> CachedCustomTypeInterface;` — If the property on this row is a customized property type, this is the interface to that customization
- L220 _private member_ `TSharedPtr<class FCustomChildrenBuilder> PropertyTypeLayoutBuilder;` — Builder for children of a customized property type
- L222 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;` — The property handle for this row
- L224 _private member_ `TSharedPtr<FPropertyNode> PropertyNode;` — The property node for this row
- L226 _private member_ `TSharedPtr<FPropertyEditor> PropertyEditor;` — The property editor for this row
- L228 _private member_ `TSharedPtr<FPropertyEditor> PropertyKeyEditor;` — The property editor for this row's key
- L230 _private member_ `TSharedPtr<IPropertyTypeCustomization> CachedKeyCustomTypeInterface;` — The property Type customization for this row's key
- L232 _private member_ `TSharedPtr<FDetailWidgetRow> CustomPropertyWidget;` — Custom widgets to use for this row instead of the default ones
- L234 _private member_ `TAttribute<bool> CustomEditConditionValue;` — User customized edit condition
- L236 _private member_ `FOnBooleanValueChanged CustomEditConditionValueChanged;` — User customized edit condition change handler.
- L238 _private member_ `ECustomEditConditionMode CustomEditConditionMode = ECustomEditConditionMode::Override;` — Should this custom edit condition override or merge with the existing edit condition of the property (if any)?
- L240 _private member_ `bool bCustomEditConditionHides = false;` — User customized edit condition hides specifier
- L242 _private member_ `TOptional<FResetToDefaultOverride> CustomResetToDefault;` — User customized reset to default
- L244 _private member_ `TSharedPtr<IDetailDragDropHandler> CustomDragDropHandler;` — User customized drag/drop handler
- L246 _private member_ `TWeakPtr<FDetailCategoryImpl> ParentCategory;` — The category this row resides in
- L248 _private member_ `TSharedPtr<FComplexPropertyNode> ExternalRootNode;` — Root of the property node if this node comes from an external tree
- L250 _private member_ `TSharedPtr<struct FDetailLayoutData> ExternalObjectLayout;`
- L252 _private member_ `FName CustomExpansionIdName;` — The custom expansion ID name used to save and restore expansion state on this node
- L254 _private member_ `bool bShowPropertyButtons;` — Whether or not to show standard property buttons
- L256 _private member_ `bool bShowCustomPropertyChildren;` — True to show custom property children
- L258 _private member_ `bool bForceAutoExpansion;` — True to force auto-expansion
- L260 _private member_ `bool bCachedCustomTypeInterface;` — True if we've already attempted to fill out our CustomTypeInterface (no need to rerun the query)
- L262 _private member_ `bool bForceShowOnlyChildren = false;` — True if this row is only for organizational purposes and doesnt have anything valid to show itself

### `Source/Editor/PropertyEditor/Private/DetailRowMenuContextPrivate.h` (Private)


#### class `UDetailRowMenuContextPrivate`  
`class UDetailRowMenuContextPrivate : public UObject`  
_L13-35_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: The private context provides the slate widget.
- L19 _public function_ `template <typename RowType> TSharedPtr<RowType> GetRowWidget() const`
- L34 _public member_ `TWeakPtr<SDetailTableRowBase> Row;`

### `Source/Editor/PropertyEditor/Private/DetailsViewConfig.h` (Private)


#### struct `FDetailsSectionSelection`  
`struct FDetailsSectionSelection`  
_L17-25_
- reflection: `USTRUCT()`
- L24 _public member_ `TSet<FName> SectionNames;` — `UPROPERTY()`

#### struct `FDetailsViewConfig`  
`struct FDetailsViewConfig`  
_L28-77_
- reflection: `USTRUCT()`
- L36 _public member_ `bool bShowFavoritesCategory { false };` — `UPROPERTY()` — If we should show the favorites category.
- L40 _public member_ `bool bShowAllAdvanced { false };` — `UPROPERTY()` — When enabled, the Advanced Details will always auto expand.
- L44 _public member_ `bool bShowHiddenPropertiesWhilePlaying { false };` — `UPROPERTY()` — When Playing or Simulating, shows all properties (even non-visible and non-editable properties), if the object belongs to a simulating world.  This is useful for debugging.
- L48 _public member_ `bool bShowAllChildrenIfCategoryMatches { false };` — `UPROPERTY()` — Show all category children if the category matches the filter.
- L52 _public member_ `bool bShowOnlyKeyable { false };` — `UPROPERTY()` — Show only keyable properties.
- L56 _public member_ `bool bShowOnlyAnimated { false };` — `UPROPERTY()` — Show only animated properties.
- L60 _public member_ `bool bShowOnlyModified { false };` — `UPROPERTY()` — Show only modified properties.
- L64 _public member_ `bool bShowSections { true };` — `UPROPERTY()` — Show sections.
- L68 _public member_ `float ValueColumnWidth { 0 };` — `UPROPERTY()` — Width of the value column in the details view (0.0-1.0).
- L72 _public member_ `TMap<FName, FDetailsSectionSelection> SelectedSections;` — `UPROPERTY()` — A map of class name to a set of selected sections for that class.
- L76 _public member_ `bool bShowHelperSections = false;` — `UPROPERTY()` — Show Favorites and Modified sections

#### class `UDetailsConfig`  
`class UDetailsConfig : public UEditorConfigBase`  
_L80-95_
- reflection: `UCLASS(EditorConfig="DetailsView")`
- inherits: `UEditorConfigBase`
- L87 _public member_ `TMap<FName, FDetailsViewConfig> Views;` — `UPROPERTY(meta=(EditorConfig))`
- L89 _public prototype_ `static void Initialize();`
- L90 _public prototype_ `static UDetailsConfig* Get();`
- L94 _private member_ `static TObjectPtr<UDetailsConfig> Instance;`

### `Source/Editor/PropertyEditor/Private/DetailsViewGenericObjectFilter.h` (Private)


#### class `FDetailsViewDefaultObjectFilter`  
`class FDetailsViewDefaultObjectFilter : public FDetailsViewObjectFilter`  
_L13-25_
- inherits: `FDetailsViewObjectFilter`
- desc: The default object set is just a pass through to the details panel.
- L16 _public prototype_ `FDetailsViewDefaultObjectFilter(bool bInAllowMultipleRoots);`
- L21 _public prototype_ `virtual TArray<FDetailsViewObjectRoot> FilterObjects(const TArray<UObject*>& SourceObjects);` — FDetailsViewObjectFilter interface
- L24 _private member_ `bool bAllowMultipleRoots;`

### `Source/Editor/PropertyEditor/Private/DetailsViewPropertyGenerationUtilities.h` (Private)


#### class `FDetailsViewPropertyGenerationUtilities`  
`class FDetailsViewPropertyGenerationUtilities : public IPropertyGenerationUtilities`  
_L9-19_
- inherits: `IPropertyGenerationUtilities`
- desc: Property generation utilities for widgets derived from SDetailsViewBase.
- L12 _public prototype_ `FDetailsViewPropertyGenerationUtilities(SDetailsViewBase& InDetailsView);`
- L14 _public prototype_ `virtual const FCustomPropertyTypeLayoutMap& GetInstancedPropertyTypeLayoutMap() const override;` — IPropertyGenerationUtilities interface
- L15 _public prototype_ `virtual void RebuildTreeNodes() override;`
- L18 _private member_ `TWeakPtr<SDetailsViewBase> DetailsViewPtr;`

### `Source/Editor/PropertyEditor/Private/DetailsViewStyle.h` (Private)


#### class `FOverridesWidgetStyleKey`  
`class FOverridesWidgetStyleKey : public TSharedFromThis< FOverridesWidgetStyleKey >`  
_L19-95_
- inherits: `TSharedFromThis<FOverridesWidgetStyleKey>`
- desc: A class which provides a key with the information to create the Overrides widget style (including the Icom)
- L28 _public prototype_ `FOverridesWidgetStyleKey(FName InName);` — The default constructor for the style key. @param InName the FName which is the name of the key
- L39 _public prototype_ `FOverridesWidgetStyleKey(FName InName, const TOptional<EOverriddenState>& InOverriddenState, const TOptional<bool>& bInStateInherited = TOptional<bool>(), const FText& InCategoryTooltip = FText::GetEmpty(), const FText& InPropertyTooltip = FText::GetEmpty());` — The constructor for the style key that initializes the Overridden state members @param InName the FName which is the name of the key @param InOverriddenState the overridden state for components for which this style is visible @param bInStateInherited take into account if the state was inherited or not, not set means anything @param InCategoryTooltip tooltip for this widget if it is a category @param InPropertyTooltip tooltip for this widget if it is a property
- L48 _public prototype_ `const FSlateBrush& GetConstStyleBrush() const;` — returns the const FSlateBrush& that creates the icon for this widget style
- L53 _public prototype_ `const FSlateBrush& GetConstStyleBrushHovered() const;` — returns the const FSlateBrush& that creates the hovered icon for this widget style
- L58 _public prototype_ `FText GetToolTipText(bool bIsCategory = false) const;` — returns the tooltip for this widget style
- L67 _public prototype_ `TAttribute<EVisibility> GetVisibilityAttribute(const TSharedPtr<FEditPropertyChain>& PropertyChain, TWeakObjectPtr<UObject>& OverriddenObjectWeakPtr) const;` — Creates a TAttribute<EVisibility> which indicates the EVisibility for this widget style @param PropertyChain points to the FEditPropertyChain for the Property, if this style is for a Property, else it is nullptr @param OverriddenObjectWeakPtr the UObject associated with this widget style @return
- L72 _public member_ `const FName Name;` — the name of the key
- L77 _public member_ `const TOptional<EOverriddenState> VisibleOverriddenState;` — The EOverriddenState for which this style is visible for a UObject
- L82 _public member_ `TOptional<bool> bStateInherited;` — Whether the state was inherited from a parent node or not
- L84 _public member_ `const bool bCanBeVisible = false;`
- L89 _public member_ `FText CategoryTooltip;` — Tooltip for this widget if it is a category
- L94 _public member_ `FText PropertyTooltip;` — tTooltip for this widget if it is a property

#### class `FOverridesWidgetStyleKeys`  
`class FOverridesWidgetStyleKeys`  
_L101-146_
- desc: s The FOverridesWidgetStyleKeys class provides style keys which can create the needed styles for overrides widgets
- L109 _public prototype_ `static const FOverridesWidgetStyleKey& Here();` — The style for an override widget when an item is completely overridden and has no nested properties which are not.
- L114 _public prototype_ `static const FOverridesWidgetStyleKey& Added();` — The style for the override widget when an item has been newly added
- L120 _public prototype_ `static const FOverridesWidgetStyleKey& None();` — The style for the override widget when the user hovers over it which shows that they have associated action no overrides to choose from
- L125 _public prototype_ `static const FOverridesWidgetStyleKey& Removed();` — The style for the override widget when an item has been removed
- L131 _public prototype_ `static const FOverridesWidgetStyleKey& Inside();` — The style for the override widget when it has some nested items inside that have been overridden, but not all of them
- L133 _public prototype_ `static const FOverridesWidgetStyleKey& HereInside();`
- L138 _public prototype_ `static const FOverridesWidgetStyleKey& Inherited();` — The override state was inherited from a parent node
- L140 _public prototype_ `static TArray< TSharedRef< const FOverridesWidgetStyleKey >> GetKeys();`
- L142 _public prototype_ `static void Initialize();`
- L145 _private member_ `static TArray< TSharedRef< const FOverridesWidgetStyleKey >> OverridesWidgetStyleKeys;`

#### class `FDetailsViewStyle`  
`class FDetailsViewStyle : public FSlateWidgetStyle`  
_L151-318_
- inherits: `FSlateWidgetStyle`
- desc: A Class which holds information regarding the style of a Details View
- L158 _public prototype_ `FDetailsViewStyle();` — The default constructor of this @code FDetailsViewStyle @endcode.
- L165 _public prototype_ `FDetailsViewStyle(FDetailsViewStyleKey& InKey);` — Constructs this @code FDetailsViewStyle @endcode with the specified parameters @param InKey the Key for  the @code FDetailsViewStyle @endcode
- L173 _public prototype_ `FDetailsViewStyle(FDetailsViewStyle& InStyle);` — Copy constructor for @code FDetailsViewStyle @endcode. @param InStyle the @code FDetailsViewStyle @endcode instance from which to initialize this @code FDetailsViewStyle @endcode.
- L181 _public prototype_ `FDetailsViewStyle(const FDetailsViewStyle& InStyle);` — Const copy constructor for @code FDetailsViewStyle @endcode. @param InStyle the @code FDetailsViewStyle @endcode instance from which to initialize this @code FDetailsViewStyle @endcode.
- L186 _public prototype_ `FMargin GetOuterCategoryRowPadding() const;` — Returns the padding for the outer Category row
- L191 _public prototype_ `FMargin GetRowPadding(bool bIsOuterCategory) const;` — Returns the padding for details panel rows which are not outer Category rows
- L196 _public prototype_ `bool operator==(FDetailsViewStyle& OtherLayoutType) const;` — The equality operator for @code FDetailsViewStyle @endcode
- L201 _public prototype_ `FDetailsViewStyle& operator=(FDetailsViewStyleKey& OtherLayoutTypeKey);` — The assignment operator for @code FDetailsViewStyle @endcode
- L206 _public prototype_ `virtual const FName GetTypeName() const override;` — Gets the @code FName @endcode Name of this style.
- L214 _public prototype_ `const FSlateBrush* GetBackgroundImageForCategoryRow( const bool bShowBorder, const bool bIsInnerCategory, const bool bIsCategoryExpanded) const;` — Returns the background image for the Category row, minus the scrollbar well @param bShowBorder a bool to indicate whether the border should be shown, at all @param bIsCategoryExpanded a bool that indicates whether this Category is expanded
- L227 _public prototype_ `const FSlateBrush* GetBackgroundImageForScrollBarWell( const bool bShowBorder, const bool bIsInnerCategory, const bool bIsCategoryExpanded, const bool bIsScrollBarVisible) const;` — Returns the background image for the scroll bar well @param bShowBorder a bool to indicate whether the border should be shown, at all @param bIsInnerCategory a bool that indicates whether this background is for an inner Category @param bIsCategoryExpanded a bool that indicates whether this Category is expanded @param bIsScrollBarVisible a bool that indicates whether the scrollbar for the details view is visible
- L236 _public prototype_ `static void InitializeDetailsViewStyles();` — Initializes all Details View Styles
- L245 _public prototype_ `FDetailsViewStyle( const FDetailsViewStyleKey& InKey, float InTopCategoryPadding = 0.f);` — Constructs this FDetailsViewStyle with the specified parameters @param InKey the name of the FDetailsViewStyle @param InTopCategoryPadding the top padding for the Category row
- L254 _public prototype_ `FMargin GetTablePadding(bool bIsScrollBarVisible) const;` — Returns the FMargin which provides the padding around the whole details view table @param bIsScrollBarVisible whether the scrollbar is visible
- L259 _public function_ `FMargin GetCategoryButtonsMargin() const` — Returns the FMargin which provides the padding around the Category buttons
- L269 _public prototype_ `static const FDetailsViewStyle* GetStyle(const FDetailsViewStyleKey& InKey);` — Returns the @code FDetailsViewStyle @endcode for which this is the @code FDetailsViewStyleKey @endcode . @param InKey the name of the FDetailsViewStyle
- L273 _private prototype_ `void Initialize( const FDetailsViewStyle* Style );`
- L281 _private prototype_ `void Initialize( FDetailsViewStyleKey& InKey, const float InTopCategoryPadding);` — Initializes this FDetailsViewStyle with the specified parameters @param InKey the name of the FDetailsViewStyle @param InTopCategoryPadding the top padding for the Category row
- L289 _private prototype_ `void Initialize(FDetailsViewStyleKey& InKey);` — Initializes this FDetailsViewStyle with the style specified by @code FDetailsViewStyleKey @endcode InKey @param InKey the name of the FDetailsViewStyle
- L292 _private member_ `FDetailsViewStyleKey Key;` — the Name of the Style
- L298 _private member_ `static inline TMap<FName, const FDetailsViewStyle*> StyleKeyToStyleTemplateMap;` — A map of @code FDetailsViewStyleKey @endcode instances to the @code const FDetailsViewStyle* @endcode instances for which they are the keys.
- L301 _private member_ `float TopCategoryPadding = 0.f;` — the Slate Units of the top padding for an outer Category row
- L306 _private member_ `FMargin TablePaddingWithScrollbar = FMargin(0, 0, 16, 1);` — The FMargin which provides the padding around the whole details view table with scrollbar
- L311 _private member_ `FMargin TablePaddingWithNoScrollbar = FMargin(0, 0, 0, 1);` — The FMargin which provides the padding around the whole details view table with no scrollbar
- L316 _private member_ `FMargin CategoryButtonsMargin = FMargin(0, 0, 0, 0);` — The FMargin which provides the padding around the Category buttons

### `Source/Editor/PropertyEditor/Private/EditConditionContext.h` (Private)


#### class `IEditConditionContext`  
`class IEditConditionContext`  
_L12-34_
- L15 _public prototype_ `virtual FName GetContextName() const = 0;`
- L17 _public prototype_ `virtual TOptional<bool> GetBoolValue(const FString& PropertyName, TWeakObjectPtr<UFunction> CachedFunction = nullptr) const = 0;`
- L18 _public prototype_ `virtual TOptional<int64> GetIntegerValue(const FString& PropertyName, TWeakObjectPtr<UFunction> CachedFunction = nullptr) const = 0;`
- L19 _public prototype_ `virtual TOptional<double> GetNumericValue(const FString& PropertyName, TWeakObjectPtr<UFunction> CachedFunction = nullptr) const = 0;`
- L20 _public prototype_ `virtual TOptional<FString> GetEnumValue(const FString& PropertyName, TWeakObjectPtr<UFunction> CachedFunction = nullptr) const = 0;`
- L21 _public prototype_ `virtual TOptional<UObject*> GetPointerValue(const FString& PropertyName, TWeakObjectPtr<UFunction> CachedFunction = nullptr) const = 0;`
- L22 _public prototype_ `virtual TOptional<FString> GetTypeName(const FString& PropertyName, TWeakObjectPtr<UFunction> CachedFunction = nullptr) const = 0;`
- L23 _public prototype_ `virtual TOptional<int64> GetIntegerValueOfEnum(const FString& EnumType, const FString& EnumValue) const = 0;`
- L33 _public prototype_ `virtual const TWeakObjectPtr<UFunction> GetFunction(const FString& FieldName) const = 0;` — Get field as a function, avoiding multiple function searches @TODO: Get property in general, not just for functions. See: UE-175891. @param FieldName Name of the field to try to interpret as a function @return Function if found or already cached, else

#### class `FEditConditionContext`  
`class FEditConditionContext : public IEditConditionContext`  
_L41-67_
- inherits: `IEditConditionContext`
- L44 _public prototype_ `FEditConditionContext(FPropertyNode& InPropertyNode);`
- L45 _public prototype_ `virtual ~FEditConditionContext() = default;`
- L47 _public prototype_ `virtual FName GetContextName() const override;`
- L49 _public prototype_ `virtual TOptional<bool> GetBoolValue(const FString& PropertyName, TWeakObjectPtr<UFunction> CachedFunction = nullptr) const override;`
- L50 _public prototype_ `virtual TOptional<int64> GetIntegerValue(const FString& PropertyName, TWeakObjectPtr<UFunction> CachedFunction = nullptr) const override;`
- L51 _public prototype_ `virtual TOptional<double> GetNumericValue(const FString& PropertyName, TWeakObjectPtr<UFunction> CachedFunction = nullptr) const override;`
- L52 _public prototype_ `virtual TOptional<FString> GetEnumValue(const FString& PropertyName, TWeakObjectPtr<UFunction> CachedFunction = nullptr) const override;`
- L53 _public prototype_ `virtual TOptional<UObject*> GetPointerValue(const FString& PropertyName, TWeakObjectPtr<UFunction> CachedFunction = nullptr) const override;`
- L54 _public prototype_ `virtual TOptional<FString> GetTypeName(const FString& PropertyName, TWeakObjectPtr<UFunction> CachedFunction = nullptr) const override;`
- L55 _public prototype_ `virtual TOptional<int64> GetIntegerValueOfEnum(const FString& EnumType, const FString& EnumValue) const override;`
- L57 _public prototype_ `virtual const TWeakObjectPtr<UFunction> GetFunction(const FString& FieldName) const override;`
- L63 _public prototype_ `const FBoolProperty* GetSingleBoolProperty(const TSharedPtr<FEditConditionExpression>& Expression) const;` — Fetch the single boolean property referenced. Returns nullptr if more than one property is referenced.
- L66 _private member_ `TWeakPtr<FPropertyNode> PropertyNode;`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogEditCondition, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogEditCondition, Log, All);`

### `Source/Editor/PropertyEditor/Private/EditConditionParser.h` (Private)


#### struct `EditConditionParserTokens::FPropertyToken`  
`struct FPropertyToken`  
_L17-32_
- L19 _public function_ `FPropertyToken(FString&& InProperty) : PropertyName(InProperty)`
- L22 _public function_ `FPropertyToken(const FPropertyToken& Other) : PropertyName(Other.PropertyName)`
- L25 _public function_ `FPropertyToken& operator=(const FPropertyToken& Other)`
- L31 _public member_ `FString PropertyName;`

#### struct `EditConditionParserTokens::FEnumToken`  
`struct FEnumToken`  
_L34-51_
- L36 _public function_ `FEnumToken(FString&& InType, FString&& InValue) : Type(InType), Value(InValue)`
- L39 _public function_ `FEnumToken(const FEnumToken& Other) : Type(Other.Type), Value(Other.Value)`
- L42 _public function_ `FEnumToken& operator=(const FEnumToken& Other)`
- L49 _public member_ `FString Type;`
- L50 _public member_ `FString Value;`

#### struct `EditConditionParserTokens::FNullPtrToken`  
`struct FNullPtrToken`  
_L53-58_
- L55 _public prototype_ `FNullPtrToken() = default;`
- L56 _public prototype_ `FNullPtrToken(const FNullPtrToken&) = default;`
- L57 _public prototype_ `FNullPtrToken& operator=(const FNullPtrToken&) = default;`

#### struct `EditConditionParserTokens::FIndexNoneToken`  
`struct FIndexNoneToken`  
_L60-65_
- L62 _public prototype_ `FIndexNoneToken() = default;`
- L63 _public prototype_ `FIndexNoneToken(const FIndexNoneToken&) = default;`
- L64 _public prototype_ `FIndexNoneToken& operator=(const FIndexNoneToken&) = default;`

#### class `FEditConditionExpression`  
`class FEditConditionExpression`  
_L98-106_
- L101 _public function_ `FEditConditionExpression(TArray<FCompiledToken>&& InTokens) : Tokens(MoveTemp(InTokens))`
- L105 _public member_ `TArray<FCompiledToken> Tokens;`

#### class `FEditConditionParser`  
`class FEditConditionParser`  
_L108-134_
- L111 _public prototype_ `FEditConditionParser();`
- L113 _public prototype_ `FEditConditionParser(const FEditConditionParser&) = delete;`
- L114 _public prototype_ `FEditConditionParser(FEditConditionParser&&) = default;`
- L115 _public prototype_ `FEditConditionParser& operator=(const FEditConditionParser&) = delete;`
- L116 _public prototype_ `FEditConditionParser& operator=(FEditConditionParser&&) = default;`
- L122 _public prototype_ `TSharedPtr<FEditConditionExpression> Parse(const FString& ExpressionString) const;` — Parse the given string into an expression. @returns The parsed expression if valid, invalid TSharedPtr if the string is not a valid expression string.
- L128 _public prototype_ `TValueOrError<bool, FText> Evaluate(const FEditConditionExpression& Expression, const IEditConditionContext& Context) const;` — Evaluate the given expression within the given context. @returns The result of the evaluated expression if valid, invalid TOptional if the evaluation failed or produced a non-bool result.
- L131 _private member_ `FTokenDefinitions TokenDefinitions;`
- L132 _private member_ `FExpressionGrammar ExpressionGrammar;`
- L133 _private member_ `TOperatorJumpTable<IEditConditionContext> OperatorJumpTable;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace EditConditionParserTokens`
- L68 _macro_ `#define DEFINE_EDIT_CONDITION_NODE(TYPE, ...) \`

### `Source/Editor/PropertyEditor/Private/EditConditionParserTests.h` (Private)


#### enum `EditConditionTestEnum`  
`enum class EditConditionTestEnum`  
_L16-20_
- reflection: `UENUM()`
- L18 _public enumerator_ `First = 15`
- L19 _public enumerator_ `Second = 31`

#### enum `EditConditionByteEnum`  
`enum EditConditionByteEnum : int`  
_L23-27_
- reflection: `UENUM()`
- L25 _public enumerator_ `First = 15`
- L26 _public enumerator_ `Second = 31`

#### class `UEditConditionTestObject`  
`class UEditConditionTestObject : public UObject`  
_L37-131_
- reflection: `UCLASS(transient)`
- inherits: `UObject`
- desc: Test object for edit condition property checks Note: Currently only bool functions are supported (Including static). remaining are not used because currently not supported by edit condition parser
- L42 _private member_ `bool BoolProperty;` — `UPROPERTY(EditAnywhere, Category=Test)`
- L45 _private member_ `EditConditionTestEnum EnumProperty;` — `UPROPERTY(EditAnywhere, Category=Test)`
- L48 _private member_ `TEnumAsByte<EditConditionByteEnum> ByteEnumProperty;` — `UPROPERTY(EditAnywhere, Category=Test)`
- L51 _private member_ `double DoubleProperty;` — `UPROPERTY(EditAnywhere, Category=Test)`
- L54 _private member_ `int32 IntegerProperty;` — `UPROPERTY(EditAnywhere, Category=Test)`
- L57 _private member_ `uint8 UintBitfieldProperty : 1;` — `UPROPERTY(EditAnywhere, Category=Test)`
- L60 _private member_ `TObjectPtr<UObject> UObjectPtr;` — `UPROPERTY(EditAnywhere, Category=Test)`
- L63 _private member_ `TSoftClassPtr<UObject> SoftClassPtr;` — `UPROPERTY(EditAnywhere, Category=Test)`
- L66 _private member_ `TWeakObjectPtr<UObject> WeakObjectPtr;` — `UPROPERTY(EditAnywhere, Category=Test)`
- L71 _public prototype_ `void VoidFunction() const;` — `UFUNCTION()` — Used in test cases that should fail, should not be able to execute a void function in edit condition
- L74 _public prototype_ `bool GetBoolFunction() const;` — `UFUNCTION()`
- L77 _public prototype_ `EditConditionTestEnum GetEnumFunction() const;` — `UFUNCTION()`
- L80 _public prototype_ `TEnumAsByte<EditConditionByteEnum> GetByteEnumFunction() const;` — `UFUNCTION()`
- L83 _public prototype_ `double GetDoubleFunction() const;` — `UFUNCTION()`
- L86 _public prototype_ `int32 GetIntegerFunction() const;` — `UFUNCTION()`
- L89 _public prototype_ `uint8 GetUintBitfieldFunction() const;` — `UFUNCTION()`
- L92 _public prototype_ `UObject* GetUObjectPtrFunction() const;` — `UFUNCTION()`
- L95 _public prototype_ `TSoftClassPtr<UObject> GetSoftClassPtrFunction() const;` — `UFUNCTION()`
- L98 _public prototype_ `TWeakObjectPtr<UObject> GetWeakObjectPtrFunction() const;` — `UFUNCTION()`
- L103 _public prototype_ `void StaticVoidFunction();` — `UFUNCTION()` — Used in test cases that should fail, should not be able to execute a void function in edit condition
- L106 _public prototype_ `static bool StaticGetBoolFunction();` — `UFUNCTION()`
- L109 _public prototype_ `static EditConditionTestEnum StaticGetEnumFunction();` — `UFUNCTION()`
- L112 _public prototype_ `static TEnumAsByte<EditConditionByteEnum> StaticGetByteEnumFunction();` — `UFUNCTION()`
- L115 _public prototype_ `static double StaticGetDoubleFunction();` — `UFUNCTION()`
- L118 _public prototype_ `static int32 StaticGetIntegerFunction();` — `UFUNCTION()`
- L121 _public prototype_ `static uint8 StaticGetUintBitfieldFunction();` — `UFUNCTION()`
- L124 _public prototype_ `static UObject* StaticGetUObjectPtrFunction();` — `UFUNCTION()`
- L127 _public prototype_ `static TSoftClassPtr<UObject> StaticGetSoftClassPtrFunction();` — `UFUNCTION()`
- L130 _public prototype_ `static TWeakObjectPtr<UObject> StaticGetWeakObjectPtrFunction();` — `UFUNCTION()`

### `Source/Editor/PropertyEditor/Private/IDetailsViewPrivate.h` (Private)


#### class `IDetailsViewPrivate`  
`class IDetailsViewPrivate : public IDetailsView`  
_L19-236_
- inherits: `IDetailsView`
- L29 _public prototype_ `virtual void SetNodeExpansionState(TSharedRef<FDetailTreeNode> InTreeNode, bool bIsItemExpanded, bool bRecursive) = 0;` — Sets the expansion state for a node and optionally all of its children @param InTreeNode		The node to change expansion state on @param bIsItemExpanded	The new expansion state @param bRecursive		Whether or not to apply the expansion change to any children
- L37 _public prototype_ `virtual void RequestItemExpanded(TSharedRef<FDetailTreeNode> TreeNode, bool bExpand) = 0;` — Requests that an item in the tree be expanded or collapsed @param TreeNode	The tree node to expand @param bExpand	true if the item should be expanded, false otherwise
- L42 _public prototype_ `virtual void RefreshTree() = 0;` — Refreshes the detail's treeview
- L45 _public prototype_ `virtual FNotifyHook* GetNotifyHook() const = 0;` — Returns the notify hook to use when properties change
- L50 _public prototype_ `virtual TSharedPtr<IPropertyUtilities> GetPropertyUtilities() = 0;` — Returns the property utilities for this view
- L55 _public prototype_ `virtual void MoveScrollOffset(int32 DeltaOffset) = 0;` — Causes the details view to move the scroll offset (by item) @param DeltaOffset	We add this value to the current scroll offset if the result is in the scrolling range
- L63 _public prototype_ `virtual void SaveCustomExpansionState(const FString& NodePath, bool bIsExpanded) = 0;` — Saves the expansion state of a tree node @param NodePath	The path to the detail node to save @param bIsExpanded	true if the node is expanded, false otherwise
- L71 _public prototype_ `virtual bool GetCustomSavedExpansionState(const FString& NodePath) const = 0;` — Gets the saved expansion state of a tree node in this category @param NodePath	The path to the detail node to get @return true if the node should be expanded, false otherwise
- L78 _public prototype_ `virtual FName GetViewIdentifier() const = 0;` — Gets the View Identifier for this details view. If any. @return Text set for view identifier for this details view on creation
- L85 _public prototype_ `virtual FDetailsViewArgs::EExpansionPersistenceMethod GetExpansionPersistenceMethod() const = 0;` — Gets expansion persistence method for this details view. See FDetailsViewArgs. @return Text set for view identifier for this details view on creation
- L90 _public prototype_ `virtual bool IsPropertyVisible( const struct FPropertyAndParent& PropertyAndParent ) const = 0;` — @return True if the property is visible
- L95 _public prototype_ `virtual bool IsPropertyReadOnly( const struct FPropertyAndParent& PropertyAndParent ) const = 0;` — @return True if the property is visible
- L100 _public prototype_ `virtual bool IsCustomRowVisible(FName InRowName, FName InParentName) const = 0;` — @return Whether a custom row with the specified name and parent name is visible.
- L105 _public prototype_ `virtual bool IsCustomRowReadOnly(FName InRowName, FName InParentName) const = 0;` — @return Whether a custom row with the specified name and parent name is read-only.
- L110 _public prototype_ `virtual TSharedPtr<class FAssetThumbnailPool> GetThumbnailPool() const = 0;` — @return The thumbnail pool that should be used for thumbnails being rendered in this view
- L115 _public prototype_ `virtual const TArray<TSharedRef<class IClassViewerFilter>>& GetClassViewerFilters() const = 0;` — @return The set of custom class viewer filters to use for class properties in this view
- L123 _public prototype_ `virtual void CreateColorPickerWindow(const TSharedRef< class FPropertyEditor >& PropertyEditor, bool bUseAlpha) = 0;` — Creates the color picker window for this property view. @param PropertyEditor				The slate property node to edit. @param bUseAlpha			Whether or not alpha is supported
- L128 _public prototype_ `virtual void EnqueueDeferredAction(FSimpleDelegate& DeferredAction) = 0;` — Adds an action to execute next tick
- L133 _public prototype_ `virtual void NotifyFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent) = 0;` — Called when properties have finished changing (after PostEditChange is called)
- L138 _public prototype_ `virtual void RerunCurrentFilter() = 0;` — Reruns the current search filter applied to the details panel to account for any new changes
- L141 _public prototype_ `virtual bool DontUpdateValueWhileEditing() const = 0;` — If a customization standalone widget is used, the value should be update only once, when its window is closed
- L144 _public prototype_ `virtual bool ContainsMultipleTopLevelObjects() const = 0;` — @return Whether or not the details panel was created with multiple unrelated objects visible at once in the details panel
- L147 _public prototype_ `virtual TSharedPtr<class IDetailRootObjectCustomization> GetRootObjectCustomization() const = 0;` — @return the customization instance that defines how the display for a root object looks
- L150 _public prototype_ `virtual void UpdateSinglePropertyMap(TSharedPtr<FComplexPropertyNode> InRootPropertyNode, struct FDetailLayoutData& LayoutData, bool bIsExternal) = 0;` — Runs the details customization update on a root property node
- L152 _public prototype_ `virtual const FCustomPropertyTypeLayoutMap& GetCustomPropertyTypeLayoutMap() const = 0;`
- L155 _public prototype_ `virtual void SaveExpandedItems(TSharedRef<FPropertyNode> StartNode) = 0;` — Saves the expansion state of property nodes for the selected object set
- L160 _public prototype_ `virtual void RestoreExpandedItems(TSharedRef<FPropertyNode> StartNode) = 0;` — Restores the expansion state of property nodes for the selected object set
- L165 _public prototype_ `virtual void RestoreExpandedItems(TSharedRef<FPropertyNode> StartNode, TMap<UStruct*, FStringPrefixTree>* OptionalExpansionStates) = 0;` — Restores the expansion state of property nodes for the selected object set, with optionally provided external expansion states.
- L173 _public prototype_ `virtual void MarkNodeAnimating(TSharedPtr<FPropertyNode> InNode, float InAnimationDuration, TOptional<FGuid> InAnimationBatchId = {}) = 0;` — Mark node as animating, useful if animating during behaviors that trigger widget reconstruction. @param InNode				The slate property node to animate. @param InAnimationDuration	The animation duration in seconds. @param InAnimationBatchId	(Optional) A batch id to enable simultaneous (and performant) animation of multiple rows.
- L176 _public prototype_ `virtual bool IsNodeAnimating(TSharedPtr<FPropertyNode> InNode) = 0;` — @return true if node is animating
- L179 _public prototype_ `virtual float GetNodeAnimationTime(TSharedPtr<FPropertyNode> InNode) = 0;` — @return the time/progress of the given node (time since creation/play), if it's animating. The time is in seconds.
- L182 _public prototype_ `virtual class FDetailColumnSizeData& GetColumnSizeData() = 0;` — Column width accessibility
- L185 _public prototype_ `virtual bool IsFavoritingEnabled() const = 0;` — Does this details view allow favoriting?
- L188 _public prototype_ `virtual bool IsGroupFavorite(FStringView GroupPath) const = 0;` — Is the given group a favorite?
- L191 _public prototype_ `virtual void SetGroupFavorite(FStringView GroupPath, bool IsFavorite) = 0;` — Set the given group's favorite status.
- L194 _public prototype_ `virtual bool IsCustomBuilderFavorite(FStringView Path) const = 0;` — Is the given custom builder a favorite?
- L197 _public prototype_ `virtual void SetCustomBuilderFavorite(FStringView GroupPath, bool IsFavorite) = 0;` — Set the given group's favorite status.
- L200 _public function_ `virtual void GetHeadNodes(TArray<TWeakPtr<FDetailTreeNode>>& OutNodes)` — Retrieve a list of top-most detail tree nodes.
- L206 _public function_ `virtual const FDetailsViewStyleKey& GetStyleKey() override` — Gets the @code FDetailsViewStyleKey& @endcode which provides a Key to the current style for a Details View
- L214 _public function_ `virtual void UpdateStyleKey() override` — Updates @code FDetailsViewStyleKey& StyleKey @endcode for the current @code IDetailsViewPrivate @endcode state
- L221 _public function_ `virtual bool IsDefaultStyle() const override` — Returns a bool indicating whether the given @code FDetailsViewStyleKey @endcode is the default Details View Style
- L230 _public prototype_ `virtual TSharedPtr<FDetailsDisplayManager> GetDisplayManager() = 0;` — Returns a @code TSharedPtr @endcode to the @code FDetailsDisplayManager @endcode for this details view
- L232 _public function_ `virtual TSharedPtr<FDetailsNameWidgetOverrideCustomization> GetDetailsNameWidgetOverrideCustomization()`

### `Source/Editor/PropertyEditor/Private/IPropertyGenerationUtilities.h` (Private)


#### class `IPropertyGenerationUtilities`  
`class IPropertyGenerationUtilities`  
_L8-18_
- desc: Defines internal utilities for generating property layouts.
- L11 _public prototype_ `virtual ~IPropertyGenerationUtilities() = default;`
- L14 _public prototype_ `virtual const FCustomPropertyTypeLayoutMap& GetInstancedPropertyTypeLayoutMap() const = 0;` — Gets the instance type customization map for the details implementation providing this utilities object.
- L17 _public prototype_ `virtual void RebuildTreeNodes() = 0;` — Rebuilds the details tree nodes for the details implementation providing this utilities object.

### `Source/Editor/PropertyEditor/Private/ItemPropertyNode.h` (Private)


#### class `FItemPropertyNode`  
`class FItemPropertyNode : public FPropertyNode`  
_L8-75_
- inherits: `FPropertyNode`
- L12 _public prototype_ `FItemPropertyNode();`
- L13 _public prototype_ `virtual ~FItemPropertyNode();`
- L15 _public prototype_ `virtual uint8* GetValueBaseAddress(uint8* StartAddress, bool bIsSparseData, bool bIsStruct) const override;`
- L16 _public prototype_ `virtual uint8* GetValueAddress(uint8* StartAddress, bool bIsSparseData, bool bIsStruct) const override;`
- L21 _public function_ `virtual FItemPropertyNode* AsItemPropertyNode() override` — Overridden function to get the derived object node
- L22 _public function_ `virtual const FItemPropertyNode* AsItemPropertyNode() const override`
- L25 _public prototype_ `void SetDisplayNameOverride( const FText& InDisplayNameOverride ) override;` — Display name override to use instead of the property name
- L30 _public prototype_ `virtual void SetFavorite(bool FavoriteValue) override;` — @return true if the property is mark as a favorite
- L35 _public prototype_ `virtual bool IsFavorite() const override;` — @return true if the property is mark as a favorite
- L40 _public prototype_ `virtual FText GetDisplayName() const override;` — @return The formatted display name for the property in this node
- L45 _public prototype_ `virtual void SetToolTipOverride( const FText& InToolTipOverride ) override;` — Sets the tooltip override to use instead of the property tooltip
- L50 _public prototype_ `virtual FText GetToolTipText() const override;` — @return The tooltip for the property in this node
- L53 _protected prototype_ `virtual void InitBeforeNodeFlags() override;`
- L58 _protected prototype_ `virtual void InitExpansionFlags() override;` — Overridden function for special setup
- L63 _protected prototype_ `virtual void InitChildNodes() override;` — Overridden function for Creating Child Nodes
- L67 _private member_ `FText DisplayNameOverride;` — Display name override to use instead of the property name
- L69 _private member_ `FText ToolTipOverride;` — Tooltip override to use instead of the property tooltip
- L74 _private member_ `bool bCanDisplayFavorite;` — Option to know if we can display the favorite icon in the property editor

### `Source/Editor/PropertyEditor/Private/ObjectPropertyNode.h` (Private)


#### class `FObjectPropertyNode`  
`class FObjectPropertyNode : public FComplexPropertyNode`  
_L18-199_
- inherits: `FComplexPropertyNode`
- L21 _public prototype_ `FObjectPropertyNode();`
- L22 _public prototype_ `virtual ~FObjectPropertyNode();`
- L25 _public function_ `virtual FObjectPropertyNode* AsObjectNode() override` — FPropertyNode Interface
- L26 _public function_ `virtual const FObjectPropertyNode* AsObjectNode() const override`
- L27 _public prototype_ `virtual bool GetReadAddressUncached(const FPropertyNode& InNode, bool InRequiresSingleSelection, FReadAddressListData* OutAddresses, bool bComparePropertyContents = true, bool bObjectForceCompare = false, bool bArrayPropertiesCanDifferInSize = false) const override;`
- L28 _public prototype_ `virtual bool GetReadAddressUncached(const FPropertyNode& InNode, FReadAddressListData& OutAddresses) const override;`
- L34 _public prototype_ `UObject* GetUObject(int32 InIndex);` — Returns the UObject at index "n" of the Objects Array @param InIndex - index to read out of the array
- L35 _public prototype_ `const UObject* GetUObject(int32 InIndex) const;`
- L41 _public prototype_ `UPackage* GetUPackage(int32 InIndex);` — Returns the UPackage at index "n" of the Objects Array @param InIndex - index to read out of the array
- L42 _public prototype_ `const UPackage* GetUPackage(int32 InIndex) const;`
- L45 _public function_ `int32 GetNumObjects() const` — Returns the number of objects for which properties are currently being edited.
- L50 _public prototype_ `void AddObject( UObject* InObject );` — Adds a new object to the list.
- L53 _public prototype_ `void AddObjects(const TArray<UObject*>& InObjects);` — Adds new objects to the list.
- L58 _public prototype_ `void RemoveObject(UObject* InObject);` — Removes an object from the list.
- L62 _public prototype_ `void RemoveAllObjects();` — Removes all objects from the list.
- L65 _public prototype_ `void SetObjectPackageOverrides(const TMap<TWeakObjectPtr<UObject>, TWeakObjectPtr<UPackage>>& InMapping);` — Set overrides that should be used when looking for packages that contain the given object
- L67 _public prototype_ `void ClearObjectPackageOverrides();` — Clear overrides that should be used when looking for packages that contain the given object
- L73 _public prototype_ `bool PurgeKilledObjects();` — Purges any objects marked pending kill from the object list @return True if any objects were purged, or false otherwise
- L76 _public prototype_ `void Finalize();` — Called when the object list is finalized, Finalize() finishes the property window setup.
- L79 _public function_ `UClass* GetObjectBaseClass()` — @return		The base-est baseclass for objects in this list.
- L81 _public function_ `const UClass* GetObjectBaseClass() const` — @return		The base-est baseclass for objects in this list.
- L85 _public function_ `virtual UStruct* GetBaseStructure() override` — FComplexPropertyNode implementation
- L86 _public function_ `virtual const UStruct* GetBaseStructure() const override`
- L88 _public prototype_ `virtual TArray<UStruct*> GetAllStructures() override;`
- L89 _public prototype_ `virtual TArray<const UStruct*> GetAllStructures() const override;`
- L91 _public function_ `virtual int32 GetInstancesNum() const override`
- L92 _public function_ `virtual uint8* GetMemoryOfInstance(int32 Index) const override`
- L96 _public function_ `virtual uint8* GetValuePtrOfInstance(int32 Index, const FProperty* InProperty, const FPropertyNode* InParentNode) const override`
- L117 _public function_ `virtual TWeakObjectPtr<UObject> GetInstanceAsUObject(int32 Index) const override`
- L122 _public function_ `virtual EPropertyType GetPropertyType() const override`
- L123 _public function_ `virtual void Disconnect() override`
- L130 _public function_ `virtual FProperty* GetStoredProperty()` — @return		The property stored at this node, to be passed to Pre/PostEditChange.
- L132 _public function_ `TPropObjectIterator ObjectIterator()`
- L133 _public function_ `TPropObjectConstIterator ObjectConstIterator() const`
- L137 _public prototype_ `virtual TSharedPtr<FPropertyNode> GenerateSingleChild( FName ChildPropertyName ) override;` — Generates a single child from the provided property name.  Any existing children are destroyed
- L142 _public function_ `const TSet<FName>& GetHiddenCategories() const` — @return The hidden categories
- L144 _public function_ `bool IsRootNode() const`
- L149 _public prototype_ `bool IsSparseDataStruct(const UScriptStruct* Struct) const;` — @return True if Struct is one of the sparse data structures used by this object
- L152 _protected prototype_ `virtual void InitBeforeNodeFlags() override;` — FPropertyNode interface
- L153 _protected prototype_ `virtual void InitChildNodes() override;`
- L154 _protected prototype_ `virtual bool GetQualifiedName( FString& PathPlusIndex, const bool bWithArrayIndex, const FPropertyNode* StopParent = nullptr, bool bIgnoreCategories = false ) const override;`
- L155 _protected prototype_ `virtual uint8* GetValueBaseAddress(uint8* Base, bool bIsSparseData, bool bIsStruct) const override;`
- L160 _protected prototype_ `void SetBestBaseClass();` — Looks at the Objects array and creates the best base class.  Called by Finalize(); that is, when the list of selected objects is being finalized.
- L168 _private prototype_ `void InternalInitChildNodes( FName SingleChildName = NAME_None );` — Creates child nodes @param SingleChildName	The property name of a single child to create instead of all childen
- L171 _private prototype_ `void GetCategoryProperties(const TSet<UClass*>& ClassesToConsider, const FProperty* CurrentProperty, bool bShouldShowDisableEditOnInstance, bool bShouldShowHiddenProperties, TSet<FName>& CategoriesFromProperties, TArray<FName>& SortedCategories, int32& NonBlueprintCategoryIndex);` — If CurrentProperty should show up in the ClassesToConsider make sure its category is in SortedCategories and CategoriesFromProperties.
- L175 _private member_ `TArray< TWeakObjectPtr<UObject> > Objects;` — The list of objects we are editing properties for.
- L178 _private member_ `TWeakObjectPtr<UClass> BaseClass;` — The lowest level base class for objects in this list.
- L183 _private member_ `TWeakFieldPtr<FProperty> StoredProperty;` — The property passed to Pre/PostEditChange calls.
- L188 _private member_ `TSet<FName> HiddenCategories;` — Set of all category names hidden by the objects in this node
- L195 _private member_ `TMap<UClass*, TTuple<UScriptStruct*, void*>> SparseClassDataInstances;` — Contains the structure and memory location for storing data of that type. Used to read and write to sidecar structs for the class
- L198 _private member_ `TMap<TWeakObjectPtr<UObject>, TWeakObjectPtr<UPackage>> ObjectToPackageMapping;` — Object -> Package re-mapping

#### Free symbols / members of external scopes

- L15 _typedef_ `typedef TArray< TWeakObjectPtr<UObject> >::TIterator TPropObjectIterator;` — Object iteration
- L16 _typedef_ `typedef TArray< TWeakObjectPtr<UObject> >::TConstIterator TPropObjectConstIterator;`

### `Source/Editor/PropertyEditor/Private/Presentation/PropertyEditor/PropertyEditor.h` (Private)


#### class `FPropertyEditor`  
`class FPropertyEditor : public TSharedFromThis<FPropertyEditor>`  
_L14-137_
- inherits: `TSharedFromThis<FPropertyEditor>`
- L17 _public prototype_ `static TSharedRef<FPropertyEditor> Create(const TSharedRef<FPropertyNode>& InPropertyNode, const TSharedRef<IPropertyUtilities>& InPropertyUtilities);`
- L20 _public prototype_ `FString GetValueAsString() const;` — @return The String containing the value of the property
- L23 _public prototype_ `FString GetValueAsDisplayString() const;` — @return The String containing the value of the property, possibly using an alternate form more suitable for display in the UI
- L26 _public prototype_ `FText GetValueAsText() const;` — @return The String containing the value of the property as Text
- L29 _public prototype_ `FText GetValueAsDisplayText() const;` — @return The String containing the value of the property as Text, possibly using an alternate form more suitable for display in the UI
- L31 _public prototype_ `bool PropertyIsA(const FFieldClass* InClass) const;`
- L33 _public prototype_ `bool IsFavorite() const;`
- L35 _public prototype_ `bool IsChildOfFavorite() const;`
- L37 _public prototype_ `void ToggleFavorite();`
- L39 _public prototype_ `bool IsPropertyEditingEnabled() const;`
- L41 _public prototype_ `void ForceRefresh();`
- L43 _public prototype_ `void RequestRefresh();`
- L47 _public prototype_ `bool IsEditConst(const bool bIncludeEditCondition = true) const;` — @return Whether the property is editconst. If bIncludeEditCondition is false, this will return true if the property is ever editable (as though it always passes any specified EditCondition).
- L50 _public prototype_ `bool SupportsEditConditionToggle() const;` — @return Whether this property should have an edit condition toggle.
- L53 _public prototype_ `void ToggleEditConditionState();` — Toggle the current state of the edit condition if this SupportsEditConditionToggle()
- L56 _public prototype_ `bool HasEditCondition() const;` — @return Whether the property has a condition which must be met before allowing editing of it's value
- L59 _public prototype_ `bool IsEditConditionMet() const;` — @return Whether the condition has been met to allow editing of this property's value
- L62 _public prototype_ `bool IsOnlyVisibleWhenEditConditionMet() const;` — @return Whether this property derives its visibility from its edit condition
- L65 _public prototype_ `FText GetToolTipText() const;` — @return The tooltip for this property editor
- L68 _public prototype_ `FString GetDocumentationLink() const;` — @return The documentation link for this property
- L71 _public prototype_ `FString GetDocumentationExcerptName() const;` — @return The documentation excerpt name to use from this properties documentation link
- L74 _public prototype_ `FText GetDisplayName() const;` — @return The display name to be used for the property
- L77 _public prototype_ `bool DoesPassFilterRestrictions() const;` — @return Whether the property passes the current filter restrictions. If no there are no filter restrictions false will be returned.
- L79 _public prototype_ `void UseSelected();`
- L80 _public prototype_ `void AddItem();`
- L81 _public prototype_ `void AddGivenItem(const FString& InGivenItem);`
- L82 _public prototype_ `void ClearItem();`
- L83 _public prototype_ `void InsertItem();`
- L84 _public prototype_ `void DeleteItem();`
- L85 _public prototype_ `void DuplicateItem();`
- L86 _public prototype_ `void MakeNewBlueprint();`
- L87 _public prototype_ `void BrowseTo();`
- L88 _public prototype_ `void EmptyArray();`
- L89 _public prototype_ `void OnGetClassesForAssetPicker( TArray<const UClass*>& OutClasses );`
- L90 _public prototype_ `void OnAssetSelected( const FAssetData& AssetData );`
- L91 _public prototype_ `void OnActorSelected( AActor* InActor );`
- L92 _public prototype_ `void OnGetActorFiltersForSceneOutliner( TSharedPtr<FSceneOutlinerFilters>& OutFilters );`
- L93 _public prototype_ `void EditConfigHierarchy();`
- L99 _public prototype_ `void SetOptionalItem(FProperty* NewProperty, const UClass* NewObjectClass);` — If this is an editor of an optional, set that optional to the passed in value. If nullptr is passed in, the optional is set and default-initialized.
- L102 _public prototype_ `void ClearOptionalItem();` — If this is an editor of an optional, unset that optional.
- L105 _public prototype_ `TSharedRef<FPropertyNode> GetPropertyNode() const;` — In an ideal world we wouldn't expose these
- L106 _public prototype_ `const FProperty* GetProperty() const;`
- L107 _public prototype_ `TSharedRef<IPropertyHandle> GetPropertyHandle() const;`
- L109 _public prototype_ `static void SyncToObjectsInNode( const TWeakPtr<FPropertyNode>& WeakPropertyNode );`
- L111 _public member_ `static const FString MultipleValuesDisplayName;`
- L113 _private prototype_ `FPropertyEditor( const TSharedRef<FPropertyNode>& InPropertyNode, const TSharedRef<IPropertyUtilities>& InPropertyUtilities );`
- L115 _private prototype_ `void OnUseSelected();`
- L116 _private prototype_ `void OnAddItem();`
- L117 _private prototype_ `void OnAddGivenItem(const FString InGivenItem);`
- L118 _private prototype_ `void OnClearItem();`
- L119 _private prototype_ `void OnInsertItem();`
- L120 _private prototype_ `void OnDeleteItem();`
- L121 _private prototype_ `void OnDuplicateItem();`
- L122 _private prototype_ `void OnBrowseTo();`
- L123 _private prototype_ `void OnEmptyArray();`
- L124 _private prototype_ `void OnSetOptionalValue(FProperty* NewProperty, const UClass* NewObjectClass);`
- L125 _private prototype_ `void OnClearOptionalValue();`
- L130 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;` — Property handle for actually reading/writing the value of a property
- L133 _private member_ `TSharedRef<FPropertyNode> PropertyNode;` — pointer to the property node.
- L136 _private member_ `TSharedRef<IPropertyUtilities> PropertyUtilities;` — The property view where this widget resides

### `Source/Editor/PropertyEditor/Private/Presentation/PropertyTable/DataSource.h` (Private)


#### class `UObjectDataSource`  
`class UObjectDataSource : public IDataSource`  
_L8-27_
- inherits: `IDataSource`
- L12 _public function_ `UObjectDataSource( const TWeakObjectPtr< UObject >& InObject ) : Object( InObject )`
- L17 _public prototype_ `virtual ~UObjectDataSource() = default;`
- L19 _public function_ `virtual TWeakObjectPtr< UObject > AsUObject() const override`
- L20 _public function_ `virtual TSharedPtr< FPropertyPath > AsPropertyPath() const override`
- L22 _public function_ `virtual bool IsValid() const override`
- L26 _private member_ `TWeakObjectPtr< UObject > Object;`

#### class `PropertyPathDataSource`  
`class PropertyPathDataSource : public IDataSource`  
_L29-48_
- inherits: `IDataSource`
- L33 _public function_ `PropertyPathDataSource( const TSharedRef< FPropertyPath >& InPath ) : Path( InPath )`
- L38 _public prototype_ `virtual ~PropertyPathDataSource() = default;`
- L40 _public function_ `virtual TWeakObjectPtr< UObject > AsUObject() const override`
- L41 _public function_ `virtual TSharedPtr< FPropertyPath > AsPropertyPath() const override`
- L43 _public function_ `virtual bool IsValid() const override`
- L47 _private member_ `TSharedRef< FPropertyPath > Path;`

#### class `NoDataSource`  
`class NoDataSource : public IDataSource`  
_L50-60_
- inherits: `IDataSource`
- L54 _public prototype_ `virtual ~NoDataSource() = default;`
- L56 _public function_ `virtual TWeakObjectPtr< UObject > AsUObject() const override`
- L57 _public function_ `virtual TSharedPtr< FPropertyPath > AsPropertyPath() const override`
- L59 _public function_ `virtual bool IsValid() const override`

### `Source/Editor/PropertyEditor/Private/Presentation/PropertyTable/PropertyTable.h` (Private)


#### class `FPropertyTable`  
`class FPropertyTable : public TSharedFromThis< FPropertyTable >, public IPropertyTable`  
_L13-232_
- inherits: `TSharedFromThis<FPropertyTable>,IPropertyTable`
- L17 _public prototype_ `FPropertyTable();`
- L18 _public prototype_ `virtual ~FPropertyTable();`
- L20 _public prototype_ `virtual void Tick() override;`
- L22 _public prototype_ `virtual void ForceRefresh() override;`
- L23 _public prototype_ `virtual void RequestRefresh() override;`
- L24 _public prototype_ `virtual void RequestForceRefresh() override;`
- L26 _public prototype_ `virtual class FNotifyHook* GetNotifyHook() const override;`
- L27 _public prototype_ `virtual bool AreFavoritesEnabled() const override;`
- L28 _public prototype_ `virtual void ToggleFavorite( const TSharedRef< class FPropertyEditor >& PropertyEditor ) const override;`
- L29 _public prototype_ `virtual void CreateColorPickerWindow( const TSharedRef< class FPropertyEditor >& PropertyEditor, bool bUseAlpha ) const override;`
- L30 _public prototype_ `virtual void EnqueueDeferredAction( FSimpleDelegate DeferredAction ) override;`
- L31 _public prototype_ `virtual TSharedPtr<class FAssetThumbnailPool> GetThumbnailPool() const override;`
- L32 _public function_ `virtual void NotifyStartedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent) override`
- L33 _public function_ `virtual void NotifyFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent) override`
- L34 _public prototype_ `virtual const TArray<TSharedRef<class IClassViewerFilter>>& GetClassViewerFilters() const override;`
- L36 _public prototype_ `virtual bool GetIsUserAllowedToChangeRoot() override;`
- L37 _public prototype_ `virtual void SetIsUserAllowedToChangeRoot( bool InAllowUserToChangeRoot ) override;`
- L39 _public prototype_ `virtual void AddColumn( const TWeakObjectPtr< UObject >& Object ) override;`
- L40 _public prototype_ `virtual void AddColumn( const TWeakFieldPtr< FProperty >& Property ) override;`
- L41 _public prototype_ `virtual void AddColumn( const TSharedRef< FPropertyPath >& PropertyPath ) override;`
- L42 _public prototype_ `virtual void AddColumn( const TSharedRef< class IPropertyTableColumn >& Column ) override;`
- L43 _public prototype_ `virtual void RemoveColumn( const TSharedRef< class IPropertyTableColumn >& Column ) override;`
- L45 _public prototype_ `virtual void AddRow( const TWeakObjectPtr< UObject >& Object ) override;`
- L46 _public prototype_ `virtual void AddRow( const TWeakFieldPtr< FProperty >& Property ) override;`
- L47 _public prototype_ `virtual void AddRow( const TSharedRef< FPropertyPath >& PropertyPath ) override;`
- L48 _public prototype_ `virtual void AddRow( const TSharedRef< class IPropertyTableRow >& Row ) override;`
- L49 _public prototype_ `virtual void RemoveRow( const TSharedRef< class IPropertyTableRow >& Row ) override;`
- L51 _public function_ `virtual const EPropertyTableOrientation::Type GetOrientation() const override`
- L52 _public prototype_ `virtual void SetOrientation( EPropertyTableOrientation::Type InOrientation ) override;`
- L54 _public prototype_ `virtual void SetRootPath( const TSharedPtr< FPropertyPath >& Path ) override;`
- L55 _public function_ `virtual TSharedRef< FPropertyPath > GetRootPath() const override`
- L56 _public prototype_ `virtual TArray< FPropertyInfo > GetPossibleExtensionsForPath( const TSharedRef< FPropertyPath >& Path ) const override;`
- L58 _public prototype_ `virtual void GetSelectedTableObjects( TArray< TWeakObjectPtr< UObject > >& OutSelectedObjects) const override;`
- L60 _public function_ `virtual const TArray<TWeakObjectPtr<UObject>>& GetSelectedObjects() const`
- L61 _public prototype_ `virtual void SetObjects( const TArray< TWeakObjectPtr< UObject > >& Objects ) override;`
- L62 _public prototype_ `virtual void SetObjects( const TArray< UObject* >& Objects ) override;`
- L64 _public prototype_ `virtual TSharedRef< class FObjectPropertyNode > GetObjectPropertyNode( const TSharedRef< IPropertyTableColumn >& Column, const TSharedRef< IPropertyTableRow >& Row ) override;`
- L65 _public prototype_ `virtual TSharedRef< class FObjectPropertyNode > GetObjectPropertyNode( const TWeakObjectPtr< UObject >& Object ) override;`
- L67 _public function_ `virtual bool GetShowRowHeader() const override`
- L68 _public prototype_ `virtual void SetShowRowHeader( const bool InShowRowHeader ) override;`
- L70 _public function_ `virtual bool GetShowObjectName() const override`
- L71 _public prototype_ `virtual void SetShowObjectName( const bool ShowObjectName ) override;`
- L73 _public function_ `virtual const TArray< TSharedRef< class IPropertyTableColumn > >& GetColumns() override`
- L74 _public function_ `virtual TArray< TSharedRef< class IPropertyTableRow > >& GetRows() override`
- L76 _public function_ `virtual const TSet< TSharedRef< class IPropertyTableRow > >& GetSelectedRows() override`
- L77 _public prototype_ `virtual void SetSelectedRows( const TSet< TSharedRef< IPropertyTableRow > >& InSelectedRows ) override;`
- L79 _public function_ `virtual const TSet< TSharedRef< class IPropertyTableCell > >& GetSelectedCells() override`
- L80 _public prototype_ `virtual void SetSelectedCells( const TSet< TSharedRef< class IPropertyTableCell > >& InSelectedCells ) override;`
- L82 _public prototype_ `virtual void SelectCellRange( const TSharedRef< class IPropertyTableCell >& StartingCell, const TSharedRef< class IPropertyTableCell >& EndingCell ) override;`
- L84 _public function_ `virtual float GetItemHeight() const override`
- L85 _public function_ `virtual void SetItemHeight( float NewItemHeight ) override`
- L87 _public function_ `virtual TSharedPtr< class IPropertyTableCell > GetLastClickedCell() const override`
- L88 _public function_ `virtual void SetLastClickedCell( const TSharedPtr< class IPropertyTableCell >& Cell ) override`
- L90 _public function_ `virtual TSharedPtr< class IPropertyTableCell > GetCurrentCell() const override`
- L91 _public prototype_ `virtual void SetCurrentCell( const TSharedPtr< class IPropertyTableCell >& Cell ) override;`
- L93 _public function_ `virtual TSharedPtr< class IPropertyTableColumn > GetCurrentColumn() const override`
- L94 _public prototype_ `virtual void SetCurrentColumn( const TSharedPtr< class IPropertyTableColumn >& Column ) override;`
- L96 _public function_ `virtual TSharedPtr< class IPropertyTableRow > GetCurrentRow() const override`
- L97 _public prototype_ `virtual void SetCurrentRow( const TSharedPtr< class IPropertyTableRow >& Row ) override;`
- L99 _public prototype_ `virtual TSharedPtr< class IPropertyTableCell > GetFirstCellInSelection() override;`
- L100 _public prototype_ `virtual TSharedPtr< class IPropertyTableCell > GetLastCellInSelection() override;`
- L102 _public prototype_ `virtual TSharedPtr< class IPropertyTableCell > GetNextCellInRow( const TSharedRef< class IPropertyTableCell >& Cell ) override;`
- L103 _public prototype_ `virtual TSharedPtr< class IPropertyTableCell > GetPreviousCellInRow( const TSharedRef< class IPropertyTableCell >& Cell ) override;`
- L105 _public prototype_ `virtual TSharedPtr< class IPropertyTableCell > GetNextCellInColumn( const TSharedRef< class IPropertyTableCell >& Cell ) override;`
- L106 _public prototype_ `virtual TSharedPtr< class IPropertyTableCell > GetPreviousCellInColumn( const TSharedRef< class IPropertyTableCell >& Cell ) override;`
- L108 _public prototype_ `virtual TSharedPtr< class IPropertyTableCell > GetFirstCellInRow( const TSharedRef< class IPropertyTableRow >& Row ) override;`
- L109 _public prototype_ `virtual TSharedPtr< class IPropertyTableCell > GetLastCellInRow( const TSharedRef< class IPropertyTableRow >& Row ) override;`
- L111 _public prototype_ `virtual TSharedPtr< class IPropertyTableCell > GetFirstCellInColumn( const TSharedRef< class IPropertyTableColumn >& Column ) override;`
- L112 _public prototype_ `virtual TSharedPtr< class IPropertyTableCell > GetLastCellInColumn( const TSharedRef< class IPropertyTableColumn >& Column ) override;`
- L114 _public prototype_ `virtual TSharedPtr< class IPropertyTableCell > GetFirstCellInTable() override;`
- L115 _public prototype_ `virtual TSharedPtr< class IPropertyTableCell > GetLastCellInTable() override;`
- L117 _public function_ `virtual EPropertyTableSelectionUnit::Type GetSelectionUnit() const override`
- L118 _public function_ `virtual void SetSelectionUnit( const EPropertyTableSelectionUnit::Type Unit ) override`
- L120 _public function_ `virtual ESelectionMode::Type GetSelectionMode() const override`
- L121 _public prototype_ `virtual void SetSelectionMode( const ESelectionMode::Type Mode ) override;`
- L123 _public prototype_ `virtual EColumnSortPriority::Type GetColumnSortPriority(const TSharedRef< class IPropertyTableColumn > Column) const override;`
- L124 _public prototype_ `virtual EColumnSortMode::Type GetColumnSortMode( const TSharedRef< class IPropertyTableColumn > Column ) const override;`
- L125 _public prototype_ `virtual void SortByColumnWithId( const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type SortMode) override;`
- L126 _public prototype_ `virtual void SortByColumn( const TSharedRef< class IPropertyTableColumn >& Column, EColumnSortMode::Type SortMode, const EColumnSortPriority::Type SortPriority ) override;`
- L128 _public prototype_ `virtual void PasteTextAtCell( const FString& Text, const TSharedRef< class IPropertyTableCell >& Cell ) override;`
- L130 _public prototype_ `DECLARE_DERIVED_EVENT( FPropertyTable, IPropertyTable::FSelectionChanged, FSelectionChanged );`
- L131 _public function_ `FSelectionChanged* OnSelectionChanged() override`
- L133 _public prototype_ `DECLARE_DERIVED_EVENT( FPropertyTable, IPropertyTable::FColumnsChanged, FColumnsChanged );`
- L134 _public function_ `FColumnsChanged* OnColumnsChanged() override`
- L136 _public prototype_ `DECLARE_DERIVED_EVENT( FPropertyTable, IPropertyTable::FRowsChanged, FRowsChanged );`
- L137 _public function_ `FRowsChanged* OnRowsChanged() override`
- L139 _public prototype_ `DECLARE_DERIVED_EVENT( FPropertyTable, IPropertyTable::FRootPathChanged, FRootPathChanged );`
- L140 _public function_ `virtual FRootPathChanged* OnRootPathChanged() override`
- L142 _public function_ `virtual bool IsPropertyEditingEnabled() const override`
- L144 _public function_ `virtual bool DontUpdateValueWhileEditing() const override`
- L149 _public function_ `virtual bool HasClassDefaultObject() const`
- L155 _private prototype_ `void UpdateColumns();`
- L156 _private prototype_ `void UpdateRows();`
- L158 _private prototype_ `bool CanSelectCells() const;`
- L159 _private prototype_ `bool CanSelectRows() const;`
- L161 _private prototype_ `TSharedPtr< IPropertyTableColumn > ScanForColumnWithSelectableCells( const int32 StartIndex, const int32 Step ) const;`
- L162 _private prototype_ `TSharedPtr< IPropertyTableRow > ScanForRowWithCells( const int32 StartIndex, const int32 Step ) const;`
- L164 _private prototype_ `TSharedRef< IPropertyTableRow > CreateRow( const TWeakObjectPtr< UObject >& Object );`
- L165 _private prototype_ `TSharedRef< IPropertyTableRow > CreateRow( const TWeakFieldPtr< FProperty >& Property );`
- L166 _private prototype_ `TSharedRef< IPropertyTableRow > CreateRow( const TSharedRef< FPropertyPath >& PropertyPath );`
- L168 _private prototype_ `TSharedRef< IPropertyTableColumn > CreateColumn( const TWeakObjectPtr< UObject >& Object );`
- L169 _private prototype_ `TSharedRef< IPropertyTableColumn > CreateColumn( const TWeakFieldPtr< FProperty >& Property );`
- L170 _private prototype_ `TSharedRef< IPropertyTableColumn > CreateColumn( const TSharedRef< FPropertyPath >& PropertyPath );`
- L172 _private prototype_ `void PurgeInvalidObjectNodes();`
- L174 _private prototype_ `void ResetTable();`
- L176 _private prototype_ `void OnObjectsReplaced(const TMap<UObject*, UObject*>& ReplacementMap);`
- L180 _private member_ `TArray< TWeakObjectPtr< UObject > > SourceObjects;`
- L181 _private member_ `TMap< TWeakObjectPtr< UObject >, TSharedRef< FObjectPropertyNode > > SourceObjectPropertyNodes;`
- L183 _private member_ `TArray< TSharedRef< class IPropertyTableColumn > > Columns;`
- L184 _private member_ `TArray< TSharedRef< class IPropertyTableRow > > Rows;`
- L186 _private member_ `TSet< TSharedRef< class IPropertyTableColumn > > SelectedColumns;`
- L187 _private member_ `TSet< TSharedRef< class IPropertyTableRow > > SelectedRows;`
- L188 _private member_ `TSet< TSharedRef< class IPropertyTableCell > > SelectedCells;`
- L189 _private member_ `TSharedPtr< class IPropertyTableCell > StartingCellSelectionRange;`
- L190 _private member_ `TSharedPtr< class IPropertyTableCell > EndingCellSelectionRange;`
- L192 _private member_ `TSharedPtr< class IPropertyTableRow > CurrentRow;`
- L193 _private member_ `TSharedPtr< class IPropertyTableCell > CurrentCell;`
- L194 _private member_ `TSharedPtr< class IPropertyTableColumn > CurrentColumn;`
- L196 _private member_ `TSharedRef< FPropertyPath > RootPath;`
- L198 _private member_ `EPropertyTableSelectionUnit::Type SelectionUnit;`
- L199 _private member_ `ESelectionMode::Type SelectionMode;`
- L201 _private member_ `bool ShowRowHeader;`
- L202 _private member_ `bool ShowObjectName;`
- L204 _private member_ `float ItemHeight;`
- L205 _private member_ `TSharedPtr< class IPropertyTableCell > LastClickedCell;`
- L208 _private member_ `TArray<FSimpleDelegate> DeferredActions;` — Actions that should be executed next tick
- L210 _private member_ `FSelectionChanged SelectionChanged;`
- L211 _private member_ `FColumnsChanged ColumnsChanged;`
- L212 _private member_ `FRowsChanged RowsChanged;`
- L213 _private member_ `FRootPathChanged RootPathChanged;`
- L215 _private member_ `TWeakPtr< class IPropertyTableColumn > PrimarySortedByColumn;`
- L216 _private member_ `TWeakPtr< class IPropertyTableColumn > SecondarySortedByColumn;`
- L218 _private member_ `EColumnSortMode::Type PrimarySortMode;`
- L219 _private member_ `EColumnSortMode::Type SecondarySortMode;`
- L221 _private member_ `bool AllowUserToChangeRoot;`
- L224 _private member_ `bool bRefreshRequested;` — Refresh the table contents?
- L227 _private member_ `EPropertyTableOrientation::Type Orientation;` — The Orientation of this table, I.e. do we swap columns and rows
- L229 _private member_ `FDelegateHandle ObjectsReplacedHandle;`
- L231 _private member_ `TSharedRef<FEditConditionParser> EditConditionParser;`

#### Free symbols / members of external scopes

- L130 _delegate_ `DECLARE_DERIVED_EVENT( FPropertyTable, IPropertyTable::FSelectionChanged, FSelectionChanged );`
- L133 _delegate_ `DECLARE_DERIVED_EVENT( FPropertyTable, IPropertyTable::FColumnsChanged, FColumnsChanged );`
- L136 _delegate_ `DECLARE_DERIVED_EVENT( FPropertyTable, IPropertyTable::FRowsChanged, FRowsChanged );`
- L139 _delegate_ `DECLARE_DERIVED_EVENT( FPropertyTable, IPropertyTable::FRootPathChanged, FRootPathChanged );`

### `Source/Editor/PropertyEditor/Private/Presentation/PropertyTable/PropertyTableCell.h` (Private)


#### class `FPropertyTableCell`  
`class FPropertyTableCell : public TSharedFromThis< FPropertyTableCell >, public IPropertyTableCell`  
_L16-72_
- inherits: `TSharedFromThis<FPropertyTableCell>,IPropertyTableCell`
- L20 _public prototype_ `FPropertyTableCell( const TSharedRef< class IPropertyTableColumn >& InColumn, const TSharedRef< class IPropertyTableRow >& InRow );`
- L22 _public prototype_ `virtual ~FPropertyTableCell() = default;`
- L24 _public prototype_ `virtual void Refresh() override;`
- L26 _public prototype_ `virtual bool IsReadOnly() const override;`
- L27 _public function_ `virtual bool IsBound() const override`
- L28 _public function_ `virtual bool InEditMode() const override`
- L29 _public prototype_ `virtual bool IsValid() const override;`
- L30 _public function_ `virtual bool PassesPermissionList() const override`
- L32 _public prototype_ `virtual FString GetValueAsString() const override;`
- L33 _public prototype_ `virtual FText GetValueAsText() const override;`
- L34 _public prototype_ `virtual void SetValueFromString( const FString& InString ) override;`
- L36 _public prototype_ `virtual TWeakObjectPtr< UObject > GetObject() const override;`
- L37 _public function_ `virtual TSharedPtr< class FPropertyNode > GetNode() const override`
- L38 _public function_ `virtual TSharedRef< class IPropertyTableColumn > GetColumn() const override`
- L39 _public function_ `virtual TSharedRef< class IPropertyTableRow > GetRow() const override`
- L40 _public prototype_ `virtual TSharedRef< class IPropertyTable > GetTable() const override;`
- L41 _public prototype_ `virtual TSharedPtr< class IPropertyHandle > GetPropertyHandle() const override;`
- L43 _public prototype_ `virtual void EnterEditMode() override;`
- L44 _public prototype_ `virtual void ExitEditMode() override;`
- L46 _public prototype_ `DECLARE_DERIVED_EVENT( FPropertyTableCell, IPropertyTableCell::FEnteredEditModeEvent, FEnteredEditModeEvent );`
- L47 _public function_ `virtual FEnteredEditModeEvent& OnEnteredEditMode() override`
- L49 _public prototype_ `DECLARE_DERIVED_EVENT( FPropertyTableCell, IPropertyTableCell::FExitedEditModeEvent, FExitedEditModeEvent );`
- L50 _public function_ `virtual FExitedEditModeEvent& OnExitedEditMode() override`
- L54 _private prototype_ `bool DoesPropertyPassPermissionList();` — Check if the property for this cell passes the permission list for the object we are viewing
- L58 _private member_ `bool bIsBound;`
- L59 _private member_ `bool bInEditMode;`
- L60 _private member_ `bool bIsPropertyAllowed;`
- L62 _private member_ `FEnteredEditModeEvent EnteredEditModeEvent;`
- L63 _private member_ `FExitedEditModeEvent ExitedEditModeEvent;`
- L65 _private member_ `TWeakPtr< class IPropertyTableColumn > Column;`
- L66 _private member_ `TWeakPtr< class IPropertyTableRow > Row;`
- L68 _private member_ `TSharedPtr< class FPropertyNode > PropertyNode;`
- L69 _private member_ `TSharedPtr< class FObjectPropertyNode > ObjectNode;`
- L71 _private member_ `TSharedPtr< FPropertyEditor > PropertyEditor;`

#### Free symbols / members of external scopes

- L46 _delegate_ `DECLARE_DERIVED_EVENT( FPropertyTableCell, IPropertyTableCell::FEnteredEditModeEvent, FEnteredEditModeEvent );`
- L49 _delegate_ `DECLARE_DERIVED_EVENT( FPropertyTableCell, IPropertyTableCell::FExitedEditModeEvent, FExitedEditModeEvent );`

### `Source/Editor/PropertyEditor/Private/Presentation/PropertyTable/PropertyTableColumn.h` (Private)


#### class `FPropertyTableColumn`  
`class FPropertyTableColumn : public TSharedFromThis< FPropertyTableColumn >, public IPropertyTableColumn`  
_L10-98_
- inherits: `TSharedFromThis<FPropertyTableColumn>,IPropertyTableColumn`
- L14 _public prototype_ `FPropertyTableColumn( const TSharedRef< IPropertyTable >& InTable, const TWeakObjectPtr< UObject >& InObject );`
- L16 _public prototype_ `FPropertyTableColumn( const TSharedRef< IPropertyTable >& InTable, const TSharedRef< FPropertyPath >& InPropertyPath );`
- L18 _public prototype_ `FPropertyTableColumn( const TSharedRef< IPropertyTable >& InTable, const TWeakObjectPtr< UObject >& InObject, const TSharedRef< FPropertyPath >& InPartialPropertyPath );`
- L20 _public prototype_ `virtual ~FPropertyTableColumn() = default;`
- L24 _public prototype_ `virtual FName GetId() const override;`
- L26 _public prototype_ `virtual FText GetDisplayName() const override;`
- L28 _public function_ `virtual TSharedRef< IDataSource > GetDataSource() const override`
- L30 _public function_ `virtual TSharedRef< class FPropertyPath > GetPartialPath() const override`
- L32 _public prototype_ `virtual TSharedRef< class IPropertyTableCell > GetCell( const TSharedRef< class IPropertyTableRow >& Row ) override;`
- L34 _public prototype_ `virtual void RemoveCellsForRow( const TSharedRef< class IPropertyTableRow >& Row ) override;`
- L36 _public prototype_ `virtual TSharedRef< class IPropertyTable > GetTable() const override;`
- L38 _public function_ `virtual bool CanSelectCells() const override`
- L40 _public function_ `virtual EPropertyTableColumnSizeMode::Type GetSizeMode() const override`
- L42 _public function_ `virtual void SetSizeMode(EPropertyTableColumnSizeMode::Type InSizeMode) override`
- L44 _public function_ `virtual float GetWidth() const override`
- L46 _public function_ `virtual void SetWidth( float InWidth ) override`
- L48 _public function_ `virtual bool IsHidden() const override`
- L50 _public function_ `virtual void SetHidden( bool InIsHidden ) override`
- L52 _public function_ `virtual bool IsFrozen() const override`
- L54 _public prototype_ `virtual void SetFrozen( bool InIsFrozen ) override;`
- L56 _public prototype_ `virtual bool CanSortBy() const override;`
- L58 _public prototype_ `virtual void Sort(TArray< TSharedRef< class IPropertyTableRow > >& Rows, const EColumnSortMode::Type PrimarySortMode, const TSharedPtr<IPropertyTableColumn>& SecondarySortColumn, const EColumnSortMode::Type SecondarySortMode) override;`
- L60 _public prototype_ `virtual void Tick() override;`
- L62 _public prototype_ `virtual TSharedPtr<struct FCompareRowByColumnBase> GetPropertySorter(const FProperty* Property, EColumnSortMode::Type SortMode) override;`
- L64 _public prototype_ `DECLARE_DERIVED_EVENT( FPropertyTableColumn, IPropertyTableColumn::FFrozenStateChanged, FFrozenStateChanged );`
- L65 _public function_ `FFrozenStateChanged* OnFrozenStateChanged() override`
- L69 _public prototype_ `static bool IsSupportedStructProperty(const FProperty* InProperty);`
- L73 _private prototype_ `void GenerateColumnId();`
- L75 _private prototype_ `void GenerateColumnDisplayName();`
- L80 _private member_ `TMap< TSharedRef< IPropertyTableRow >, TSharedRef< class IPropertyTableCell > > Cells;`
- L82 _private member_ `TSharedRef< IDataSource > DataSource;`
- L83 _private member_ `TWeakPtr< IPropertyTable > Table;`
- L85 _private member_ `FName Id;`
- L86 _private member_ `FText DisplayName;`
- L88 _private member_ `float Width;`
- L90 _private member_ `bool bIsHidden;`
- L91 _private member_ `bool bIsFrozen;`
- L93 _private member_ `FFrozenStateChanged FrozenStateChanged;`
- L95 _private member_ `TSharedRef< class FPropertyPath > PartialPath;`
- L97 _private member_ `EPropertyTableColumnSizeMode::Type SizeMode;`

#### Free symbols / members of external scopes

- L64 _delegate_ `DECLARE_DERIVED_EVENT( FPropertyTableColumn, IPropertyTableColumn::FFrozenStateChanged, FFrozenStateChanged );`

### `Source/Editor/PropertyEditor/Private/Presentation/PropertyTable/PropertyTableObjectNameCell.h` (Private)


#### class `FPropertyTableObjectNameCell`  
`class FPropertyTableObjectNameCell : public TSharedFromThis< FPropertyTableObjectNameCell >, public IPropertyTableCell`  
_L14-63_
- inherits: `TSharedFromThis<FPropertyTableObjectNameCell>,IPropertyTableCell`
- L18 _public prototype_ `FPropertyTableObjectNameCell( const TSharedRef< class FPropertyTableObjectNameColumn >& InColumn, const TSharedRef< class IPropertyTableRow >& InRow );`
- L19 _public prototype_ `virtual ~FPropertyTableObjectNameCell() = default;`
- L21 _public prototype_ `virtual void Refresh() override;`
- L23 _public prototype_ `virtual bool IsReadOnly() const override;`
- L24 _public function_ `virtual bool IsBound() const override`
- L25 _public function_ `virtual bool InEditMode() const override`
- L26 _public prototype_ `virtual bool IsValid() const override;`
- L28 _public prototype_ `virtual FString GetValueAsString() const override;`
- L29 _public prototype_ `virtual FText GetValueAsText() const override;`
- L30 _public function_ `virtual void SetValueFromString( const FString& InString ) override`
- L32 _public prototype_ `virtual TWeakObjectPtr< UObject > GetObject() const override;`
- L34 _public function_ `virtual TSharedPtr< class FPropertyNode > GetNode() const override`
- L35 _public prototype_ `virtual TSharedRef< class IPropertyTableColumn > GetColumn() const override;`
- L36 _public prototype_ `virtual TSharedRef< class IPropertyTableRow > GetRow() const override;`
- L37 _public prototype_ `virtual TSharedRef< class IPropertyTable > GetTable() const override;`
- L38 _public function_ `virtual TSharedPtr< class IPropertyHandle > GetPropertyHandle() const override`
- L40 _public prototype_ `virtual void EnterEditMode() override;`
- L41 _public prototype_ `virtual void ExitEditMode() override;`
- L43 _public prototype_ `DECLARE_DERIVED_EVENT( FPropertyTableObjectNameCell, IPropertyTableCell::FEnteredEditModeEvent, FEnteredEditModeEvent );`
- L44 _public function_ `virtual FEnteredEditModeEvent& OnEnteredEditMode() override`
- L46 _public prototype_ `DECLARE_DERIVED_EVENT( FPropertyTableObjectNameCell, IPropertyTableCell::FExitedEditModeEvent, FExitedEditModeEvent );`
- L47 _public function_ `virtual FExitedEditModeEvent& OnExitedEditMode() override`
- L52 _private member_ `FEnteredEditModeEvent EnteredEditModeEvent;`
- L53 _private member_ `FExitedEditModeEvent ExitedEditModeEvent;`
- L55 _private member_ `TWeakPtr< class FPropertyTableObjectNameColumn > Column;`
- L56 _private member_ `TWeakPtr< class IPropertyTableRow > Row;`
- L58 _private member_ `TSharedPtr< class FObjectPropertyNode > ObjectNode;`
- L59 _private member_ `FString ObjectName;`
- L61 _private member_ `bool bIsBound;`
- L62 _private member_ `bool bInEditMode;`

#### Free symbols / members of external scopes

- L43 _delegate_ `DECLARE_DERIVED_EVENT( FPropertyTableObjectNameCell, IPropertyTableCell::FEnteredEditModeEvent, FEnteredEditModeEvent );`
- L46 _delegate_ `DECLARE_DERIVED_EVENT( FPropertyTableObjectNameCell, IPropertyTableCell::FExitedEditModeEvent, FExitedEditModeEvent );`

### `Source/Editor/PropertyEditor/Private/Presentation/PropertyTable/PropertyTableObjectNameColumn.h` (Private)


#### class `FPropertyTableObjectNameColumn`  
`class FPropertyTableObjectNameColumn : public TSharedFromThis< FPropertyTableObjectNameColumn >, public IPropertyTableColumn`  
_L19-192_
- inherits: `TSharedFromThis<FPropertyTableObjectNameColumn>,IPropertyTableColumn`
- L23 _public function_ `FPropertyTableObjectNameColumn( const TSharedRef< IPropertyTable >& InTable ) : Table( InTable ) , Cells() , Width( 2.0f ) , bIsHidden( false )`
- L32 _public prototype_ `virtual ~FPropertyTableObjectNameColumn() = default;`
- L36 _public function_ `virtual FName GetId() const override`
- L38 _public function_ `virtual FText GetDisplayName() const override`
- L40 _public function_ `virtual TSharedRef< IDataSource > GetDataSource() const override`
- L42 _public function_ `virtual TSharedRef< class FPropertyPath > GetPartialPath() const override`
- L44 _public function_ `virtual TSharedRef< class IPropertyTableCell > GetCell( const TSharedRef< class IPropertyTableRow >& Row ) override`
- L60 _public function_ `virtual void RemoveCellsForRow( const TSharedRef< class IPropertyTableRow >& Row ) override`
- L65 _public function_ `virtual TSharedRef< class IPropertyTable > GetTable() const override`
- L67 _public function_ `virtual bool CanSelectCells() const override`
- L69 _public function_ `virtual EPropertyTableColumnSizeMode::Type GetSizeMode() const override`
- L71 _public function_ `virtual void SetSizeMode(EPropertyTableColumnSizeMode::Type InSizeMode) override`
- L73 _public function_ `virtual float GetWidth() const override`
- L75 _public function_ `virtual void SetWidth( float InWidth ) override`
- L77 _public function_ `virtual bool IsHidden() const override`
- L79 _public function_ `virtual void SetHidden( bool InIsHidden ) override`
- L81 _public function_ `virtual bool IsFrozen() const override`
- L83 _public function_ `virtual void SetFrozen( bool InIsFrozen ) override`
- L85 _public function_ `virtual bool CanSortBy() const override`
- L87 _public function_ `virtual void Sort( TArray< TSharedRef< class IPropertyTableRow > >& Rows, const EColumnSortMode::Type PrimarySortMode, const TSharedPtr<IPropertyTableColumn>& SecondarySortColumn, const EColumnSortMode::Type SecondarySortMode ) override`
- L136 _public function_ `virtual TSharedPtr<struct FCompareRowByColumnBase> GetPropertySorter(const FProperty* Property, EColumnSortMode::Type SortMode) override`
- L142 _public function_ `virtual void Tick() override`
- L144 _public prototype_ `DECLARE_DERIVED_EVENT( FPropertyTableColumn, IPropertyTableColumn::FFrozenStateChanged, FFrozenStateChanged );`
- L145 _public function_ `FFrozenStateChanged* OnFrozenStateChanged() override`
- L151 _public function_ `FString GetObjectNameAsString( const TSharedRef< IPropertyTableRow >& Row )`
- L186 _private member_ `TWeakPtr< IPropertyTable > Table;`
- L187 _private member_ `TMap< TSharedRef< IPropertyTableRow >, TSharedRef< class IPropertyTableCell > > Cells;`
- L188 _private member_ `float Width;`
- L189 _private member_ `bool bIsHidden;`
- L191 _private member_ `FFrozenStateChanged FrozenStateChanged;`

#### struct `FPropertyTableObjectNameColumn::Sort::FCompareRowByObjectNameAscending`  
`struct FCompareRowByObjectNameAscending`  
_L89-102_
- L92 _public function_ `FCompareRowByObjectNameAscending(const TSharedRef< FPropertyTableObjectNameColumn >& Column) : NameColumn(Column)`
- L96 _public function_ `FORCEINLINE bool operator()(const TSharedRef< IPropertyTableRow >& Lhs, const TSharedRef< IPropertyTableRow >& Rhs) const`
- L101 _public member_ `TSharedRef< FPropertyTableObjectNameColumn > NameColumn;`

#### struct `FPropertyTableObjectNameColumn::Sort::FCompareRowByObjectNameDescending`  
`struct FCompareRowByObjectNameDescending`  
_L104-119_
- L107 _public function_ `FCompareRowByObjectNameDescending(const TSharedRef< FPropertyTableObjectNameColumn >& Column) : Comparer(Column)`
- L111 _public function_ `FORCEINLINE bool operator()(const TSharedRef< IPropertyTableRow >& Lhs, const TSharedRef< IPropertyTableRow >& Rhs) const`
- L118 _private member_ `const FCompareRowByObjectNameAscending Comparer;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define LOCTEXT_NAMESPACE "ObjectNameColumnHeader"`
- L144 _delegate_ `DECLARE_DERIVED_EVENT( FPropertyTableColumn, IPropertyTableColumn::FFrozenStateChanged, FFrozenStateChanged );`

### `Source/Editor/PropertyEditor/Private/Presentation/PropertyTable/PropertyTablePropertyNameCell.h` (Private)


#### class `FPropertyTablePropertyNameCell`  
`class FPropertyTablePropertyNameCell : public TSharedFromThis< FPropertyTablePropertyNameCell >, public IPropertyTableCell`  
_L14-82_
- inherits: `TSharedFromThis<FPropertyTablePropertyNameCell>,IPropertyTableCell`
- L18 _public prototype_ `FPropertyTablePropertyNameCell( const TSharedRef< class FPropertyTablePropertyNameColumn >& InColumn, const TSharedRef< class IPropertyTableRow >& InRow );`
- L22 _public prototype_ `virtual void EnterEditMode() override;`
- L24 _public prototype_ `virtual void ExitEditMode() override;`
- L26 _public prototype_ `virtual TSharedRef< class IPropertyTableColumn > GetColumn() const override;`
- L28 _public function_ `virtual TSharedPtr< class FPropertyNode > GetNode() const override`
- L30 _public prototype_ `virtual TWeakObjectPtr< UObject > GetObject() const override;`
- L32 _public prototype_ `virtual TSharedRef< class IPropertyTableRow > GetRow() const override;`
- L34 _public prototype_ `virtual TSharedRef< class IPropertyTable > GetTable() const override;`
- L36 _public prototype_ `virtual FString GetValueAsString() const override;`
- L38 _public prototype_ `virtual FText GetValueAsText() const override;`
- L40 _public function_ `virtual bool InEditMode() const override`
- L42 _public function_ `virtual bool IsReadOnly() const override`
- L44 _public function_ `virtual bool IsBound() const override`
- L46 _public function_ `virtual bool IsValid() const override`
- L48 _public prototype_ `DECLARE_DERIVED_EVENT( FPropertyTablePropertyNameCell, IPropertyTableCell::FEnteredEditModeEvent, FEnteredEditModeEvent );`
- L49 _public function_ `virtual FEnteredEditModeEvent& OnEnteredEditMode() override`
- L51 _public prototype_ `DECLARE_DERIVED_EVENT( FPropertyTablePropertyNameCell, IPropertyTableCell::FExitedEditModeEvent, FExitedEditModeEvent );`
- L52 _public function_ `virtual FExitedEditModeEvent& OnExitedEditMode() override`
- L54 _public prototype_ `virtual void Refresh() override;`
- L56 _public function_ `virtual void SetValueFromString( const FString& InString ) override`
- L63 _private member_ `bool bInEditMode;` — Is this cell being edited?
- L66 _private member_ `bool bIsBound;` — Is this cell valid?
- L69 _private member_ `TWeakPtr< class FPropertyTablePropertyNameColumn > Column;` — The column this cell is in
- L72 _private member_ `FEnteredEditModeEvent EnteredEditModeEvent;` — Delegate to execute when we enter edit mode
- L75 _private member_ `FExitedEditModeEvent ExitedEditModeEvent;` — Delegate to execute when we exit edit mode
- L78 _private member_ `TSharedPtr< class FObjectPropertyNode > ObjectNode;` — The object node which is associated with this cell
- L81 _private member_ `TWeakPtr< class IPropertyTableRow > Row;` — The row this cell is in

#### Free symbols / members of external scopes

- L48 _delegate_ `DECLARE_DERIVED_EVENT( FPropertyTablePropertyNameCell, IPropertyTableCell::FEnteredEditModeEvent, FEnteredEditModeEvent );`
- L51 _delegate_ `DECLARE_DERIVED_EVENT( FPropertyTablePropertyNameCell, IPropertyTableCell::FExitedEditModeEvent, FExitedEditModeEvent );`

### `Source/Editor/PropertyEditor/Private/Presentation/PropertyTable/PropertyTablePropertyNameColumn.h` (Private)


#### class `FPropertyTablePropertyNameColumn`  
`class FPropertyTablePropertyNameColumn : public TSharedFromThis< FPropertyTablePropertyNameColumn >, public IPropertyTableColumn`  
_L13-93_
- inherits: `TSharedFromThis<FPropertyTablePropertyNameColumn>,IPropertyTableColumn`
- L17 _public prototype_ `FPropertyTablePropertyNameColumn( const TSharedRef< IPropertyTable >& InTable );`
- L19 _public prototype_ `virtual ~FPropertyTablePropertyNameColumn() = default;`
- L23 _public function_ `virtual bool CanSelectCells() const override`
- L25 _public function_ `virtual bool CanSortBy() const override`
- L27 _public prototype_ `virtual TSharedRef< class IPropertyTableCell > GetCell( const TSharedRef< class IPropertyTableRow >& Row ) override;`
- L29 _public function_ `virtual TSharedRef< IDataSource > GetDataSource() const override`
- L31 _public function_ `virtual TSharedRef< class FPropertyPath > GetPartialPath() const override`
- L33 _public function_ `virtual FText GetDisplayName() const override`
- L35 _public function_ `virtual FName GetId() const override`
- L37 _public function_ `virtual EPropertyTableColumnSizeMode::Type GetSizeMode() const override`
- L39 _public function_ `virtual void SetSizeMode(EPropertyTableColumnSizeMode::Type InSizeMode) override`
- L41 _public function_ `virtual TSharedRef< class IPropertyTable > GetTable() const override`
- L43 _public function_ `virtual float GetWidth() const override`
- L45 _public function_ `virtual bool IsFrozen() const override`
- L47 _public function_ `virtual bool IsHidden() const override`
- L49 _public function_ `virtual void RemoveCellsForRow( const TSharedRef< class IPropertyTableRow >& Row ) override`
- L54 _public function_ `virtual void SetFrozen( bool InIsFrozen ) override`
- L56 _public function_ `virtual void SetHidden( bool InIsHidden ) override`
- L58 _public function_ `virtual void SetWidth( float InWidth ) override`
- L60 _public prototype_ `virtual void Sort( TArray< TSharedRef< class IPropertyTableRow > >& Rows, const EColumnSortMode::Type PrimarySortMode, const TSharedPtr<IPropertyTableColumn>& SecondarySortColumn, const EColumnSortMode::Type SecondarySortMode ) override;`
- L62 _public prototype_ `virtual TSharedPtr<struct FCompareRowByColumnBase> GetPropertySorter(const FProperty* Property, EColumnSortMode::Type SortMode) override;`
- L64 _public function_ `virtual void Tick() override`
- L66 _public prototype_ `DECLARE_DERIVED_EVENT( FPropertyTableColumn, IPropertyTableColumn::FFrozenStateChanged, FFrozenStateChanged );`
- L67 _public function_ `FFrozenStateChanged* OnFrozenStateChanged() override`
- L73 _private prototype_ `FString GetPropertyNameAsString( const TSharedRef< IPropertyTableRow >& Row );`
- L78 _private member_ `bool bIsHidden;` — Has this column been hidden?
- L81 _private member_ `TMap< TSharedRef< IPropertyTableRow >, TSharedRef< class IPropertyTableCell > > Cells;` — A map of all cells in this column
- L84 _private member_ `TSharedRef< IDataSource > DataSource;` — The data source for this column
- L87 _private member_ `TWeakPtr< IPropertyTable > Table;` — A reference to the owner table
- L90 _private member_ `float Width;` — The width of the column
- L92 _private member_ `FFrozenStateChanged FrozenStateChanged;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define LOCTEXT_NAMESPACE "PropertyNameColumnHeader"`
- L66 _delegate_ `DECLARE_DERIVED_EVENT( FPropertyTableColumn, IPropertyTableColumn::FFrozenStateChanged, FFrozenStateChanged );`

### `Source/Editor/PropertyEditor/Private/Presentation/PropertyTable/PropertyTableRow.h` (Private)


#### class `FPropertyTableRow`  
`class FPropertyTableRow : public TSharedFromThis< FPropertyTableRow >, public IPropertyTableRow`  
_L13-63_
- inherits: `TSharedFromThis<FPropertyTableRow>,IPropertyTableRow`
- L17 _public prototype_ `FPropertyTableRow( const TSharedRef< class IPropertyTable >& InTable, const TWeakObjectPtr< UObject >& InObject );`
- L19 _public prototype_ `FPropertyTableRow( const TSharedRef< class IPropertyTable >& InTable, const TSharedRef< FPropertyPath >& InPropertyPath );`
- L21 _public prototype_ `FPropertyTableRow( const TSharedRef< class IPropertyTable >& InTable, const TWeakObjectPtr< UObject >& InObject, const TSharedRef< FPropertyPath >& InPartialPropertyPath );`
- L23 _public prototype_ `FPropertyTableRow( const TSharedRef< class IPropertyTable >& InTable, const TSharedRef< FPropertyPath >& InPropertyPath, const TSharedRef< FPropertyPath >& InPartialPropertyPath );`
- L25 _public prototype_ `virtual ~FPropertyTableRow() = default;`
- L27 _public function_ `virtual TSharedRef< class IDataSource > GetDataSource() const override`
- L29 _public prototype_ `virtual bool HasChildren() const override;`
- L31 _public prototype_ `virtual void GetChildRows( TArray< TSharedRef< class IPropertyTableRow > >& OutChildren ) const override;`
- L33 _public prototype_ `virtual TSharedRef< class IPropertyTable > GetTable() const override;`
- L35 _public function_ `virtual bool HasCells() const override`
- L37 _public function_ `virtual TSharedRef< class FPropertyPath > GetPartialPath() const override`
- L39 _public prototype_ `virtual void Tick() override;`
- L41 _public prototype_ `virtual void Refresh() override;`
- L43 _public prototype_ `DECLARE_DERIVED_EVENT( FPropertyTableRow, IPropertyTableRow::FRefreshed, FRefreshed );`
- L44 _public function_ `virtual FRefreshed* OnRefresh() override`
- L49 _private prototype_ `void GenerateChildren();`
- L54 _private member_ `TSharedRef< class IDataSource > DataSource;`
- L56 _private member_ `TWeakPtr< class IPropertyTable > Table;`
- L58 _private member_ `TArray< TSharedRef< class IPropertyTableRow > > Children;`
- L60 _private member_ `TSharedRef< class FPropertyPath > PartialPath;`
- L62 _private member_ `FRefreshed Refreshed;`

#### Free symbols / members of external scopes

- L43 _delegate_ `DECLARE_DERIVED_EVENT( FPropertyTableRow, IPropertyTableRow::FRefreshed, FRefreshed );`

### `Source/Editor/PropertyEditor/Private/Presentation/PropertyTable/PropertyTableRowHeaderColumn.h` (Private)


#### class `FPropertyTableRowHeaderColumn`  
`class FPropertyTableRowHeaderColumn : public TSharedFromThis< FPropertyTableRowHeaderColumn >, public IPropertyTableColumn`  
_L14-94_
- inherits: `TSharedFromThis<FPropertyTableRowHeaderColumn>,IPropertyTableColumn`
- L18 _public function_ `FPropertyTableRowHeaderColumn( const TSharedRef< IPropertyTable >& InTable ) : Table( InTable ) , Cells() , bIsHidden( false ) , DataSource( MakeShareable( new NoDataSource() ) )`
- L27 _public prototype_ `virtual ~FPropertyTableRowHeaderColumn() = default;`
- L29 _public function_ `virtual FName GetId() const override`
- L30 _public function_ `virtual FText GetDisplayName() const override`
- L31 _public function_ `virtual TSharedRef< IDataSource > GetDataSource() const override`
- L32 _public function_ `virtual TSharedRef< class FPropertyPath > GetPartialPath() const override`
- L34 _public function_ `virtual TSharedRef< class IPropertyTableCell > GetCell( const TSharedRef< class IPropertyTableRow >& Row ) override`
- L50 _public function_ `virtual void RemoveCellsForRow( const TSharedRef< class IPropertyTableRow >& Row ) override`
- L55 _public function_ `virtual TSharedRef< class IPropertyTable > GetTable() const override`
- L57 _public function_ `virtual bool CanSelectCells() const override`
- L59 _public function_ `virtual EPropertyTableColumnSizeMode::Type GetSizeMode() const override`
- L61 _public function_ `virtual void SetSizeMode(EPropertyTableColumnSizeMode::Type InSizeMode) override`
- L63 _public function_ `virtual float GetWidth() const override`
- L65 _public function_ `virtual void SetWidth( float InWidth ) override`
- L67 _public function_ `virtual bool IsHidden() const override`
- L69 _public function_ `virtual void SetHidden( bool InIsHidden ) override`
- L71 _public function_ `virtual bool IsFrozen() const override`
- L73 _public function_ `virtual void SetFrozen( bool InIsFrozen ) override`
- L75 _public function_ `virtual bool CanSortBy() const override`
- L77 _public function_ `virtual void Sort( TArray< TSharedRef< class IPropertyTableRow > >& Rows, const EColumnSortMode::Type PrimarySortMode, const TSharedPtr<IPropertyTableColumn>& SecondarySortColumn, const EColumnSortMode::Type SecondarySortMode ) override`
- L79 _public function_ `virtual TSharedPtr<struct FCompareRowByColumnBase> GetPropertySorter(const FProperty* Property, EColumnSortMode::Type SortMode) override`
- L81 _public function_ `virtual void Tick() override`
- L83 _public prototype_ `DECLARE_DERIVED_EVENT( FPropertyTableColumn, IPropertyTableColumn::FFrozenStateChanged, FFrozenStateChanged );`
- L84 _public function_ `FFrozenStateChanged* OnFrozenStateChanged() override`
- L88 _private member_ `TWeakPtr< IPropertyTable > Table;`
- L89 _private member_ `TMap< TSharedRef< IPropertyTableRow >, TSharedRef< class IPropertyTableCell > > Cells;`
- L90 _private member_ `bool bIsHidden;`
- L91 _private member_ `TSharedRef< IDataSource > DataSource;`
- L93 _private member_ `FFrozenStateChanged FrozenStateChanged;`

#### Free symbols / members of external scopes

- L83 _delegate_ `DECLARE_DERIVED_EVENT( FPropertyTableColumn, IPropertyTableColumn::FFrozenStateChanged, FFrozenStateChanged );`

### `Source/Editor/PropertyEditor/Private/PropertyChangeListener.h` (Private)


#### class `FPropertyChangeListener`  
`class FPropertyChangeListener : public IPropertyChangeListener`  
_L15-42_
- inherits: `IPropertyChangeListener`
- desc: Implementation of an IPropertyChangeListener
- L18 _public prototype_ `virtual ~FPropertyChangeListener() = default;`
- L20 _public prototype_ `virtual void SetObject( UObject& Object, const FPropertyListenerSettings& InPropertyListenerSettings ) override;` — IPropertyChangeListener interface
- L21 _public prototype_ `virtual bool ScanForChanges( bool bRecacheNewValues = true ) override;`
- L22 _public prototype_ `virtual void TriggerAllPropertiesChangedDelegate() override;`
- L23 _public function_ `virtual FOnPropertyChanged& GetOnPropertyChangedDelegate() override`
- L31 _private prototype_ `void CreatePropertyCaches( TSharedRef<FPropertyNode>& PropertyNode, UObject* ParentObject );` — Recursively creates a property value cache for each property node in the tree starting with the passed in property node @param PropertyNode	The starting propertynode @param ParentObject	The current parent object to the property in the property node
- L34 _private member_ `FPropertyListenerSettings PropertyListenerSettings;` — Settings for how to listen to properties
- L36 _private member_ `TSharedPtr<FObjectPropertyNode> RootPropertyNode;` — The root of the property tree
- L38 _private member_ `TArray< TSharedPtr<class FValueCache> > CachedValues;` — List of all cached values
- L40 _private member_ `FOnPropertyChanged OnPropertyChangedDelegate;` — Delegate to call when a property has changed

### `Source/Editor/PropertyEditor/Private/PropertyEditorClipboardPrivate.h` (Private)


#### struct `UE::PropertyEditor::Internal::FClipboardData`  
`struct FClipboardData`  
_L20-52_
- desc: Contains parsed clipboard data, used to cache subsequent validity checks.
- L23 _public member_ `TOptional<FString> Content;` — Clipboard content string.
- L26 _public member_ `bool bIsApplicable = false;` — Applicability of the clipboard content to this row.
- L29 _public member_ `int32 PreviousPropertyHandleNum = INDEX_NONE;` — Previous PropertyHandle count, used to validate applicability.
- L32 _public member_ `TMap<FName, FString> PropertyValues;` — Deserialized property values (as text).
- L35 _public member_ `TArray<FName> PropertyNames;` — List of unique property names being pasted.
- L38 _public function_ `void Reset()` — Resets/invalidates data.
- L47 _public function_ `void Reserve(const int32& InNum)`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace PropertyEditor` (scope `UE`)
- L13 _namespace_ `namespace Internal` (scope `UE::PropertyEditor`)
- L15 _prototype_ `bool IsJsonString(const FString& InStr);` (scope `UE::PropertyEditor::Internal`)
- L16 _prototype_ `bool TryWriteClipboard(const TMap<FName, FString>& InTaggedClipboardPairs, FString& OutClipboardStr);` (scope `UE::PropertyEditor::Internal`)
- L17 _prototype_ `bool TryParseClipboard(const FString& InClipboardStr, TMap<FName, FString>& OutTaggedClipboard);` (scope `UE::PropertyEditor::Internal`)

### `Source/Editor/PropertyEditor/Private/PropertyEditorCopyPastePrivate.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace PropertyEditor` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::PropertyEditor`)
- L13 _prototype_ `[[nodiscard]] FString GetPropertyPath( TUniqueFunction<const TSharedPtr<IPropertyHandle>()>&& GetPropertyHandle, TUniqueFunction<const TSharedPtr<FPropertyNode>()>&& GetPropertyNode);` (scope `UE::PropertyEditor::Private`) — Get property path from handle, or node if the handle isn't valid.

### `Source/Editor/PropertyEditor/Private/PropertyEditorHelpers.h` (Private)


#### enum `EPropertyButton::Type`  
`enum Type`  
_L40-61_
- L42 _public enumerator_ `Add`
- L43 _public enumerator_ `Empty`
- L44 _public enumerator_ `Insert_Delete_Duplicate`
- L45 _public enumerator_ `Insert_Delete`
- L46 _public enumerator_ `Insert`
- L47 _public enumerator_ `Delete`
- L48 _public enumerator_ `Duplicate`
- L49 _public enumerator_ `Browse`
- L50 _public enumerator_ `PickAsset`
- L51 _public enumerator_ `PickActor`
- L52 _public enumerator_ `PickActorInteractive`
- L53 _public enumerator_ `Clear`
- L54 _public enumerator_ `Use`
- L55 _public enumerator_ `NewBlueprint`
- L56 _public enumerator_ `EditConfigHierarchy`
- L57 _public enumerator_ `Documentation`
- L58 _public enumerator_ `OptionalSet`
- L59 _public enumerator_ `OptionalPick`
- L60 _public enumerator_ `OptionalClear`

#### class `SPropertyNameWidget`  
`class SPropertyNameWidget : public SCompoundWidget`  
_L64-76_
- inherits: `SCompoundWidget`
- L67 _public function_ `SLATE_BEGIN_ARGS( SPropertyNameWidget )`
- L69 _public prototype_ `SLATE_EVENT( FOnClicked, OnDoubleClicked ) SLATE_END_ARGS() void Construct( const FArguments& InArgs, TSharedPtr<FPropertyEditor> PropertyEditor );`
- L75 _private member_ `TSharedPtr< class FPropertyEditor > PropertyEditor;`

#### class `SPropertyValueWidget`  
`class SPropertyValueWidget : public SCompoundWidget`  
_L78-107_
- inherits: `SCompoundWidget`
- L81 _public function_ `SLATE_BEGIN_ARGS( SPropertyValueWidget ) : _ShowPropertyButtons( true )`
- L84 _public prototype_ `SLATE_ARGUMENT( bool, ShowPropertyButtons ) SLATE_ARGUMENT(TOptional<FDetailWidgetRow*>, InWidgetRow) SLATE_END_ARGS() void Construct( const FArguments& InArgs, TSharedPtr<FPropertyEditor> InPropertyEditor, TSharedPtr<IPropertyUtilities> InPropertyUtilities );`
- L91 _public function_ `float GetMinDesiredWidth() const` — @return The minimum desired with if this property value
- L94 _public function_ `float GetMaxDesiredWidth() const` — @return The maximum desired with if this property value
- L97 _private prototype_ `TSharedRef<SWidget> ConstructPropertyEditorWidget( TSharedPtr<FPropertyEditor>& PropertyEditor, TSharedPtr<IPropertyUtilities> InPropertyUtilities );`
- L99 _private member_ `TSharedPtr< SWidget > ValueEditorWidget;`
- L101 _private member_ `float MinDesiredWidth;` — The minimum desired with if this property value
- L103 _private member_ `float MaxDesiredWidth;` — The maximum desired with if this property value
- L105 _private member_ `TOptional<FDetailWidgetRow*> WidgetRow;` — The widget row this value widget is part of

#### class `SEditConditionWidget`  
`class SEditConditionWidget : public SCompoundWidget`  
_L109-128_
- inherits: `SCompoundWidget`
- L111 _private function_ `SLATE_BEGIN_ARGS( SEditConditionWidget )`
- L113 _private prototype_ `SLATE_ATTRIBUTE( bool, EditConditionValue ) SLATE_EVENT( FOnBooleanValueChanged, OnEditConditionValueChanged ) SLATE_END_ARGS() void Construct( const FArguments& Args );`
- L120 _private prototype_ `void OnEditConditionCheckChanged( ECheckBoxState CheckState );`
- L121 _private prototype_ `bool HasEditConditionToggle() const;`
- L122 _private prototype_ `ECheckBoxState OnGetEditConditionCheckState() const;`
- L123 _private prototype_ `EVisibility GetVisibility() const;`
- L126 _private member_ `TAttribute<bool> EditConditionValue;`
- L127 _private member_ `FOnBooleanValueChanged OnEditConditionValueChanged;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Editor` (scope `UE`)
- L19 _namespace_ `namespace ContentBrowser` (scope `UE::Editor`)
- L21 _function_ `static bool IsNewStyleEnabled()` (scope `UE::Editor::ContentBrowser`)
- L24 _function_ `` (scope `UE::Editor::ContentBrowser::IsNewStyleEnabled`)
- L38 _namespace_ `namespace EPropertyButton`
- L130 _namespace_ `namespace PropertyEditorHelpers`
- L136 _prototype_ `bool ShouldBeVisible(const FPropertyNode& InParentNode, const FProperty* Property);` (scope `PropertyEditorHelpers`) — Perform common checks from metadata to determine if a given Property should be visible when displayed underneath the given property node.
- L143 _prototype_ `bool IsBuiltInStructProperty( const FProperty* Property );` (scope `PropertyEditorHelpers`) — Returns whether or not a property is a built in struct property like a vector or color @return true if the property is built in type, false otherwise
- L150 _prototype_ `bool IsChildOfArray( const FPropertyNode& InPropertyNode );` (scope `PropertyEditorHelpers`) — Returns whether or not a property is a child of an array (static or dynamic) @return true if the property is in an array, false otherwise
- L155 _prototype_ `bool IsChildOfSet( const FPropertyNode& InPropertyNode );` (scope `PropertyEditorHelpers`) — @return true if the property is a child (within) a set, false otherwise
- L160 _prototype_ `bool IsChildOfMap( const FPropertyNode& InPropertyNode );` (scope `PropertyEditorHelpers`) — @return true if the property is a child (within) a map, false otherwise
- L165 _prototype_ `bool IsChildOfOption(const FPropertyNode& InPropertyNode);` (scope `PropertyEditorHelpers`) — @return true if the property is a child (within) a option, false otherwise
- L172 _prototype_ `bool IsStaticArray( const FPropertyNode& InPropertyNode );` (scope `PropertyEditorHelpers`) — Returns whether or not a property a static array @param InPropertyNode	The property node containing the property to check
- L179 _prototype_ `bool IsDynamicArray( const FPropertyNode& InPropertyNode );` (scope `PropertyEditorHelpers`) — Returns whether or not a property a static array @param InPropertyNode	The property node containing the property to check
- L186 _prototype_ `bool IsOptionalProperty(const FPropertyNode& InPropertyNode);` (scope `PropertyEditorHelpers`) — Returns whether or not a property is an optional wrapper @param InPropertyNode	The property node containing the property to check
- L191 _prototype_ `bool IsSoftObjectPath(const FProperty* Property);` (scope `PropertyEditorHelpers`) — Returns true if this is an FSoftObjectPath and should be treated like a TSoftObjectPtr
- L196 _prototype_ `bool IsSoftClassPath(const FProperty* Property);` (scope `PropertyEditorHelpers`) — Returns true if this is an FSoftClassPath and should be treated like a TSoftClassPtr
- L201 _prototype_ `const FProperty* GetArrayParent( const FPropertyNode& InPropertyNode );` (scope `PropertyEditorHelpers`) — Gets the array parent of a property if it is in a dynamic or static array
- L206 _prototype_ `const FProperty* GetSetParent( const FPropertyNode& InPropertyNode );` (scope `PropertyEditorHelpers`) — Gets the set parent of a property if it is in a set
- L211 _prototype_ `const FProperty* GetMapParent(const FPropertyNode& InPropertyNode);` (scope `PropertyEditorHelpers`) — Gets the map parent of a property if it is in a map
- L216 _prototype_ `const FProperty* GetOptionParent(const FPropertyNode& InPropertyNode);` (scope `PropertyEditorHelpers`) — Gets the option parent of a property if it is in an option
- L224 _prototype_ `bool IsEditInlineClassAllowed( UClass* CheckClass, bool bAllowAbstract );` (scope `PropertyEditorHelpers`) — Returns if a class is acceptable for edit inline @param CheckClass		The class to check @param bAllowAbstract	True if abstract classes are allowed
- L229 _prototype_ `FText GetToolTipText( const FProperty* const Property );` (scope `PropertyEditorHelpers`) — @return The text that represents the specified properties tooltip
- L234 _prototype_ `FString GetDocumentationLink( const FProperty* const Property );` (scope `PropertyEditorHelpers`) — @return The link to the documentation that describes this property in detail
- L239 _prototype_ `FString GetEnumDocumentationLink(const FProperty* const Property);` (scope `PropertyEditorHelpers`) — @return The link to the documentation that describes this enum property in detail
- L244 _prototype_ `FString GetDocumentationExcerptName( const FProperty* const Property );` (scope `PropertyEditorHelpers`) — @return The name of the excerpt that describes this property in detail in the documentation file linked to this property
- L252 _prototype_ `TSharedPtr<IPropertyHandle> GetPropertyHandle( TSharedRef<FPropertyNode> PropertyNode, FNotifyHook* NotifyHook, TSharedPtr<IPropertyUtilities> PropertyUtilities );` (scope `PropertyEditorHelpers`) — Gets a property handle for the specified property node @param PropertyNode		The property node to get the handle from @param NotifyHook		Optional notify hook for the handle to use
- L261 _prototype_ `void GetRequiredPropertyButtons( TSharedRef<FPropertyNode> PropertyNode, TArray<EPropertyButton::Type>& OutRequiredButtons, bool bUsingAssetPicker = true );` (scope `PropertyEditorHelpers`) — Generates a list of required button types for the property @param PropertyNode			The property node to get required buttons from @param OutRequiredbuttons	The list of required buttons @param bUsingAssetPicker		Whether or not the property editor is using the asset picker
- L272 _prototype_ `void MakeRequiredPropertyButtons( const TSharedRef<FPropertyNode>& PropertyNode, const TSharedRef<IPropertyUtilities>& PropertyUtilities, TArray< TSharedRef<SWidget> >& OutButtons, const TArray<EPropertyButton::Type>& ButtonsToIgnore = TArray<EPropertyButton::Type>(), bool bUsingAssetPicker = true );` (scope `PropertyEditorHelpers`) — Makes property buttons widgets that accompany a property @param PropertyNode				The property node to make buttons for @param ButtonTypeToDelegateMap	A mapping of button type to the delegate to call when the button is clicked @param OutButtons				The populated list of button widgets @param ButtonsToIgnore			Specify those buttons which should be ignored and not added @param bUsingAssetPicker			Whether or not the property editor is using the asset picker
- L273 _prototype_ `void MakeRequiredPropertyButtons( const TSharedRef< FPropertyEditor >& PropertyEditor, TArray< TSharedRef<SWidget> >& OutButtons, const TArray<EPropertyButton::Type>& ButtonsToIgnore = TArray<EPropertyButton::Type>(), bool bUsingAssetPicker = true );` (scope `PropertyEditorHelpers`)
- L275 _prototype_ `TSharedRef<SWidget> MakePropertyButton( const EPropertyButton::Type ButtonType, const TSharedRef< FPropertyEditor >& PropertyEditor );` (scope `PropertyEditorHelpers`)
- L276 _prototype_ `TSharedRef<SWidget> MakePropertyReorderHandle(TSharedPtr<SDetailSingleItemRow> InParentRow, TAttribute<bool> InEnabledAttr);` (scope `PropertyEditorHelpers`)
- L283 _prototype_ `void CollectObjectNodes( TSharedPtr<FPropertyNode> StartNode, TArray<FObjectPropertyNode*>& OutObjectNodes );` (scope `PropertyEditorHelpers`) — Recursively finds all object property nodes in a property tree @param StartNode	The node to start from @param OutObjectNodes	List of all object nodes found
- L292 _prototype_ `TArray<FName> GetValidEnumsFromPropertyOverride(const FProperty* Property, const UEnum* InEnum);` (scope `PropertyEditorHelpers`) — Returns any enums that are explicitly allowed by the "ValidEnumValues" metadata on FProperty using the specified enum. @param Property	The property which may contain the "ValidEnumValues" metadata @param InEnum	The enum to search @return The array of allowed enums.  NOTE: If an empty array is returned all enum values are allowed. It is an error for a property to hide all enum values so that state is undefined here.
- L301 _prototype_ `TArray<FName> GetInvalidEnumsFromPropertyOverride(const FProperty* Property, const UEnum* InEnum);` (scope `PropertyEditorHelpers`) — Returns any enums that are explicitly Disallowed by the "InvalidEnumValues" metadata on FProperty using the specified enum. @param Property	The property which may contain the "InvalidEnumValues" metadata @param InEnum	The enum to search @return The array of disallowed enums.
- L311 _prototype_ `TArray<FName> GetRestrictedEnumsFromPropertyOverride(TArrayView<UObject*> ObjectList, const FProperty* Property, const UEnum* InEnum);` (scope `PropertyEditorHelpers`) — Returns any enums that are explicitly restricted by the "GetRestrictedEnumValues" metadata on FProperty using the specified enum. @param ObjectList The list of objects currently edited @param Property	The property which may contain the "GetRestrictedEnumValues" metadata @param InEnum	The enum to search @return The array of restricted enums.
- L320 _prototype_ `TMap<FName, FText> GetEnumValueDisplayNamesFromPropertyOverride(const FProperty* Property, const UEnum* InEnum);` (scope `PropertyEditorHelpers`) — Returns any enums that are have an overridden display name from the "EnumValueDisplayNameOverrides" metadata on FProperty using the specified enum. @param Property	The property which may contain the "EnumValueDisplayNameOverrides" metadata @param InEnum	The enum to search @return The map of display name overrides.
- L328 _prototype_ `bool IsCategoryHiddenByClass(const TSharedPtr<FComplexPropertyNode>& InRootNode, FName CategoryName);` (scope `PropertyEditorHelpers`) — Whether or not a category is hidden by a given root object @param InRootNode	The root node that for the objects we are customizing @param CategoryName	The name of the category to check @return true if a category is hidden, false otherwise
- L337 _prototype_ `bool IsVisibleStandaloneProperty(const FPropertyNode& PropertyNode, const FPropertyNode& ParentNode);` (scope `PropertyEditorHelpers`) — Determines whether or not a property should be visible in the default generated detail layout @param PropertyNode	The property node to check @param ParentNode	The parent property node to check @return true if the property should be visible
- L339 _prototype_ `void OrderPropertiesFromMetadata(TArray<FProperty*>& Properties);` (scope `PropertyEditorHelpers`)
- L345 _prototype_ `FName GetPropertyOptionsMetaDataKey(const FProperty* Property);` (scope `PropertyEditorHelpers`) — For properties that support options lists, returns the metadata key which holds the name of the UFunction to call. Returns NAME_None if the property doesn't support, or doesn't have, options.
- L353 _prototype_ `const UClass* FindOrLoadClass(const FString& ClassPath);` (scope `PropertyEditorHelpers`) — Attempts to find the class with the given object path. @param ClassPath  The asset path of the class to find or load (eg: /Game/Blueprints/BP_Example.BP_Example_C) @return nullptr if the class could not be found, or if the path doesn't correspond to a class object
- L361 _prototype_ `FText GetNumElementsText(const FText& InContainerText, const FPropertyEditor& InPropertyEditor);` (scope `PropertyEditorHelpers`) — Returns the text to inform the users of the number of elements in a given container property @param InContainerText the name of the container to use in the text (e.g. "Map" for a TMap) @param InPropertyEditor container to use in the text (e.g. "Map" for a TMap) @return the localized text

### `Source/Editor/PropertyEditor/Private/PropertyEditorToolkit.h` (Private)


#### class `FPropertyEditorToolkit`  
`class FPropertyEditorToolkit : public FAssetEditorToolkit`  
_L19-122_
- inherits: `FAssetEditorToolkit`
- L23 _public prototype_ `FPropertyEditorToolkit();`
- L25 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L27 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L29 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L31 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L33 _public prototype_ `virtual FText GetToolkitName() const override;`
- L35 _public prototype_ `virtual FText GetToolkitToolTipText() const override;`
- L37 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L39 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L41 _public function_ `virtual bool IncludeAssetInRestoreOpenAssetsPrompt(UObject* Asset) const override`
- L43 _public prototype_ `bool IsExposedAsColumn( const TWeakPtr< IPropertyTreeRow >& Row ) const;`
- L45 _public prototype_ `void ToggleColumnForProperty( const TSharedPtr< class FPropertyPath >& PropertyPath );`
- L47 _public prototype_ `bool TableHasCustomColumns() const;`
- L49 _public function_ `virtual bool IsPrimaryEditor() const override`
- L51 _public prototype_ `virtual void OnAssetsSaved(const TArray<UObject*>& SavedObjects) override;`
- L55 _public prototype_ `static TSharedRef<FPropertyEditorToolkit> CreateEditor( const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UObject* ObjectToEdit );`
- L57 _public prototype_ `static TSharedRef<FPropertyEditorToolkit> CreateEditor( const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, const TArray<UObject*>& ObjectsToEdit );`
- L63 _protected function_ `virtual bool IsFindInContentBrowserButtonVisible() const override` — "Find in Content Browser" is not visible in the property matrix because it only works on assets (and not on actors)
- L66 _private prototype_ `static TSharedPtr<FPropertyEditorToolkit> FindExistingEditor( UObject* Object );`
- L68 _private prototype_ `void Initialize( const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, const TArray<UObject*>& ObjectsToEdit );`
- L70 _private prototype_ `void CreatePropertyTree();`
- L72 _private prototype_ `void CreatePropertyTable();`
- L74 _private prototype_ `void CreateGridView();`
- L76 _private prototype_ `void CreateDetailsPanel();`
- L78 _private prototype_ `TSharedRef<SDockTab> SpawnTab_PropertyTree( const FSpawnTabArgs& Args );`
- L80 _private prototype_ `TSharedRef<SDockTab> SpawnTab_PropertyTable( const FSpawnTabArgs& Args ) ;`
- L82 _private prototype_ `TSharedRef<SDockTab> SpawnTab_DetailsPanel(const FSpawnTabArgs& Args);`
- L84 _private prototype_ `void GridSelectionChanged();`
- L86 _private prototype_ `void GridRootPathChanged();`
- L88 _private prototype_ `void ConstructTreeColumns( const TSharedRef< class SHeaderRow >& HeaderRow );`
- L90 _private prototype_ `TSharedRef< SWidget > ConstructTreeCell( const FName& ColumnName, const TSharedRef< class IPropertyTreeRow >& Row );`
- L92 _private prototype_ `FReply OnToggleColumnClicked( const TWeakPtr< class IPropertyTreeRow > Row );`
- L94 _private prototype_ `const FSlateBrush* GetToggleColumnButtonImageBrush( const TWeakPtr< class IPropertyTreeRow > Row ) const;`
- L96 _private prototype_ `EVisibility GetToggleColumnButtonVisibility( const TSharedRef< class IPropertyTreeRow > Row ) const;`
- L98 _private prototype_ `void TableColumnsChanged();`
- L102 _private member_ `TSharedPtr< class SPropertyTreeViewImpl > PropertyTree;`
- L103 _private member_ `TSharedPtr< class IPropertyTable > PropertyTable;`
- L105 _private member_ `TSharedPtr< FPropertyPath > PathToRoot;`
- L108 _private member_ `TSharedPtr<class IDetailsView> DetailsView;` — Details panel
- L110 _private member_ `TArray< TSharedRef< FPropertyPath > > PropertyPathsAddedAsColumns;`
- L112 _private member_ `TArray< TWeakPtr<IPropertyTreeRow> > PinRows;`
- L114 _private member_ `static const FName ToolkitFName;`
- L116 _private member_ `static const FName ApplicationId;`
- L117 _private member_ `static const FName TreeTabId;`
- L118 _private member_ `static const FName GridTabId;`
- L119 _private member_ `static const FName DetailsTabId;`
- L120 _private member_ `static const FName TreePinAsColumnHeaderId;`

### `Source/Editor/PropertyEditor/Private/PropertyHandleImpl.h` (Private)


#### class `FObjectBaseAddress`  
`class FObjectBaseAddress`  
_L15-34_
- L18 _public prototype_ `FObjectBaseAddress() = default;`
- L19 _public function_ `FObjectBaseAddress(UObject* InObject, uint8* InStructAddress, uint8* InBaseAddress, bool bInIsStruct) : Object(InObject) , StructAddress(InStructAddress) , BaseAddress(InBaseAddress) , bIsStruct(bInIsStruct)`
- L27 _public member_ `UObject* Object = nullptr;` — Object associated with the value, or owner object when editing a struct.
- L29 _public member_ `uint8* StructAddress = nullptr;` — Pointer to the object/struct instance that actually owns the value (may be pointing to sidecar data).
- L31 _public member_ `uint8* BaseAddress = nullptr;` — Pointer to the base address of the value within StructAddress.
- L33 _public member_ `bool bIsStruct = false;` — Editing a struct

#### class `FPropertyValueImpl`  
`class FPropertyValueImpl`  
_L39-401_
- desc: Encapsulates a property node (and property) and provides functionality to read and write to that node
- L48 _public prototype_ `FPropertyValueImpl( TSharedPtr<FPropertyNode> InPropertyNode, FNotifyHook* InNotifyHook, TSharedPtr<IPropertyUtilities> InPropertyUtilities );` — Constructor @param InPropertyNode	The property node containing information about the property to be edited @param NotifyHook		Optional notify hook for pre/post edit change messages sent outside of objects being modified
- L55 _public prototype_ `static void GenerateArrayIndexMapToObjectNode( TMap<FString,int32>& OutArrayIndexMap, FPropertyNode* PropertyNode );` — Recurse up to the next object node, adding all array indices into a map according to their property name @param ArrayIndexMap - for the current object, what properties use which array offsets @param InNode - node to start adding array offsets for.  This function will move upward until it gets to an object node
- L60 _public prototype_ `FString GetPropertyValueArray() const;` — Gets the value as a string formatted for multiple values in an array
- L68 _public typedef_ `typedef TFunctionRef<bool(const FObjectBaseAddress& , const int32 , const int32 )> EnumerateObjectsToModifyFuncRef;` — Enumerate the objects that need to be modified from the passed in property node @param InPropertyNode			The property node to get objects from @param InObjectsToModifyCallback	The function to call for each object
- L69 _public prototype_ `void EnumerateObjectsToModify( FPropertyNode* InPropertyNode, const EnumerateObjectsToModifyFuncRef& InObjectsToModifyCallback ) const;` — typedef TFunctionRef<bool(const FObjectBaseAddress&  ObjectToModify , const int32  ObjectIndex , const int32  NumObjects )> EnumerateObjectsToModifyFuncRef;   Return true to continue enumeration
- L77 _public prototype_ `void GetObjectsToModify( TArray<FObjectBaseAddress>& ObjectsToModify, FPropertyNode* InPropertyNode ) const;` — Gets the objects that need to be modified from the passed in property node @param ObjectsToModify	The addresses of the objects to modify @param InPropertyNode	The property node to get objects from
- L85 _public prototype_ `FPropertyAccess::Result GetValueData( void*& OutAddress ) const;` — Gets the union of values with the appropriate type for the property set @param OutAddress	The location of the property value @return The result of the query
- L93 _public prototype_ `FPropertyAccess::Result GetValueEditStack(FPropertyNodeEditStack& OutStack) const;` — Gets edit stack for this property @param OutStack	Edit stack @return The result of the query
- L102 _public function_ `template<class TProperty> typename TProperty::TCppType GetPropertyValue(void const* Address) const` — Given an address and a property type, get the actual value out @param Address	The location of the property value @return The property value
- L115 _public function_ `UObject* GetObjectPropertyValue(void const* Address) const` — Given an address, get the actual UObject* value out @param Address	The location of the property value @return The object property value
- L129 _public prototype_ `FPropertyAccess::Result ImportText( const FString& InValue, EPropertyValueSetFlags::Type Flags );` — The core functionality for setting values on a property @param	The value formatted as a string @return	The result of attempting to set the value
- L130 _public prototype_ `FPropertyAccess::Result ImportText( const FString& InValue, FPropertyNode* PropertyNode, EPropertyValueSetFlags::Type Flags );`
- L131 _public prototype_ `FPropertyAccess::Result ImportText( const TArray<FObjectBaseAddress>& InObjects, const TArray<FString>& InValues, FPropertyNode* PropertyNode, EPropertyValueSetFlags::Type Flags );`
- L138 _public prototype_ `void EnumerateRawData( const IPropertyHandle::EnumerateRawDataFuncRef& InRawDataCallback );` — Enumerate the raw data of this property.  (Each pointer can be cast to the property data type) @param InRawDataCallback		The function to call for each data
- L139 _public prototype_ `void EnumerateConstRawData( const IPropertyHandle::EnumerateConstRawDataFuncRef& InRawDataCallback ) const;`
- L146 _public prototype_ `void AccessRawData( TArray<void*>& RawData );` — Accesses the raw data of this property. @param RawData	An array of raw data.
- L147 _public prototype_ `void AccessRawData( TArray<const void*>& RawData ) const;`
- L152 _public prototype_ `void SetOnPropertyValueChanged( const FSimpleDelegate& InOnPropertyValueChanged );` — Sets a delegate to call when the property value changes
- L153 _public prototype_ `void SetOnPropertyValueChangedWithData(const TDelegate<void(const FPropertyChangedEvent&)>& InOnPropertyValueChanged);`
- L157 _public prototype_ `void SetOnChildPropertyValueChanged( const FSimpleDelegate& InOnChildPropertyValueChanged );` — Sets a delegate to call when the property value of a child changes
- L158 _public prototype_ `void SetOnChildPropertyValueChangedWithData(const TDelegate<void(const FPropertyChangedEvent&)>& InOnChildPropertyValueChanged);`
- L162 _public prototype_ `void SetOnPropertyValuePreChange(const FSimpleDelegate& InOnPropertyValuePreChange);` — Sets a delegate to call when the property value is about to change
- L167 _public prototype_ `void SetOnChildPropertyValuePreChange(const FSimpleDelegate& InOnChildPropertyValuePreChange);` — Sets a delegate to call when the property value of a child is about to change
- L172 _public prototype_ `void SetOnPropertyResetToDefault(const FSimpleDelegate& InOnPropertyResetToDefault);` — Sets a delegate to call when a property is reset to default
- L177 _public prototype_ `void SetOnCanItemChange(const FCanPropertyItemChange& InDelegate);` — Sets a delegate to call before an item in a container is being mutated
- L178 _public prototype_ `bool CanItemChange(EPropertyChangeType::Type Type, int32 Index);`
- L183 _public prototype_ `FDelegateHandle SetOnChangeBlocked(const FPropertyChangeBlocked::FDelegate& InDelegate);` — Sets a delegate to call when a property change has been disallowed
- L188 _public prototype_ `void UnregisterOnChangeBlocked(FDelegateHandle Handle);` — Unregisters a delegate that's bound to OnChangeBlocked
- L193 _public prototype_ `FDelegateHandle SetOnRebuildChildren( const FSimpleDelegate& InOnRebuildChildren );` — Sets a delegate to call when children of the property node must be rebuilt
- L198 _public prototype_ `void UnregisterOnRebuildChildren(FDelegateHandle Handle);` — Unregisters a delegate called when children of the property node must be rebuilt
- L208 _public prototype_ `FPropertyAccess::Result GetValueAsString( FString& OutString, EPropertyPortFlags PortFlags = PPF_PropertyWindow ) const;` — Get the value of a property as a formatted string. Each FProperty has a specific string format that it sets @param OutValue	The formatted string value to set @param PortFlags	Determines how the property's value is accessed. Defaults to PPF_PropertyWindow @return The result of attempting to get the value
- L217 _public prototype_ `FPropertyAccess::Result GetValueAsDisplayString( FString& OutString, EPropertyPortFlags PortFlags ) const;` — Get the value of a property as a formatted string, possibly using an alternate form more suitable for display in the UI @param OutValue	The formatted string value to set @param PortFlags	Determines how the property's value is accessed. @return The result of attempting to get the value
- L225 _public prototype_ `FPropertyAccess::Result GetValueAsText( FText& OutText ) const;` — Get the value of a property as FText. @param OutValue The formatted text value to set @return The result of attempting to get the value
- L233 _public prototype_ `FPropertyAccess::Result GetValueAsDisplayText( FText& OutText ) const;` — Get the value of a property as FText, possibly using an alternate form more suitable for display in the UI @param OutValue The formatted text value to set @return The result of attempting to get the value
- L242 _public prototype_ `FPropertyAccess::Result SetValueAsString( const FString& InValue, EPropertyValueSetFlags::Type Flags );` — Sets the value of a property formatted from a string. Each FProperty has a specific string format it requires @param InValue The formatted string value to set @return The result of attempting to set the value
- L250 _public prototype_ `bool IsPropertyTypeOf( FFieldClass* ClassType ) const ;` — Returns whether or not a property is of a specific subclass of FProperty @param ClassType	The class type to check @param true if the property is a ClassType
- L255 _public prototype_ `TSharedPtr<FPropertyNode> GetPropertyNode() const;` — @return The property node used by this value
- L260 _public prototype_ `int32 GetNumChildren() const;` — @return The number of children the property node has
- L268 _public prototype_ `TSharedPtr<FPropertyNode> GetChildNode( FName ChildName, bool bRecurse = true ) const;` — Gets a child node of the property node @param ChildName	The name of the child to get @return The child property node or nullptr if it doesnt exist
- L276 _public prototype_ `TSharedPtr<FPropertyNode> GetChildNode( int32 ChildIndex ) const ;` — Gets a child node of the property node @param ChildIndex	The child index where the child is stored @return The child property node or nullptr if it doesnt exist
- L285 _public prototype_ `bool GetChildNode(const int32 ChildArrayIndex, TSharedPtr<FPropertyNode>& OutChildNode) const;` — Gets a child of the property node that has the given array index @param ChildArrayIndex	The array index we're searching for. This is not necessarily the same value as the index where the child is stored @param OutChildNode		The child property node whose array index matches ChildArrayIndex, or nullptr if it could not be found @return True if a matching child property node was found, false otherwise
- L290 _public prototype_ `void ResetToDefault() ;` — Rests the value to its default value
- L295 _public prototype_ `bool DiffersFromDefault() const ;` — @return true if the property value differs from its default value
- L300 _public prototype_ `bool IsEditConst() const;` — @return true if the property  is edit const and cannot be changed
- L305 _public prototype_ `bool IsExpanded() const;` — @return Whether or not the property is expanded
- L310 _public prototype_ `void SetExpanded(bool bExpanded);` — Set the expanded flag
- L315 _public prototype_ `FText GetResetToDefaultLabel() const;` — @return The label to use for displaying reset to default values
- L321 _public prototype_ `int32 AddChild();` — Adds a child to the property node (container properties only) @return The logical index of the added child.
- L326 _public prototype_ `void ClearChildren();` — Removes all children from the property node (container properties only)
- L331 _public prototype_ `void InsertChild( int32 Index );` — Inserts a child at Index (arrays only)
- L336 _public prototype_ `void InsertChild( TSharedPtr<FPropertyNode> ChildNodeToInsertAfter );` — Inserts a child at the index provided by the child node (arrays only)
- L341 _public prototype_ `void DuplicateChild( int32 Index );` — Duplicates the child at Index (containers only)
- L346 _public prototype_ `void DuplicateChild( TSharedPtr<FPropertyNode> ChildNodeToDuplicate );` — Duplicates the provided child (containers only)
- L351 _public prototype_ `void DeleteChild( int32 Index );` — Deletes the child at Index (containers only)
- L356 _public prototype_ `void DeleteChild( TSharedPtr<FPropertyNode> ChildNodeToDelete );` — Deletes the provided child (containers only)
- L361 _public prototype_ `void SwapChildren( int32 FirstIndex, int32 SecondIndex );` — Swaps the children at FirstIndex and SecondIndex
- L366 _public prototype_ `void SwapChildren( TSharedPtr<FPropertyNode> FirstChildNode, TSharedPtr<FPropertyNode> SecondChildNode );` — Swaps the children provided children (containers only)
- L371 _public prototype_ `void MoveElementTo(int32 OriginalIndex, int32 NewIndex);` — Moves the element at OriginalIndex to NewIndex
- L376 _public prototype_ `bool HasValidPropertyNode() const;` — @return true if the property node is valid
- L381 _public prototype_ `FText GetDisplayName() const;` — @return The display name of the property
- L384 _public function_ `FNotifyHook* GetNotifyHook() const` — @return The notify hook being used
- L386 _public function_ `TSharedPtr<IPropertyUtilities> GetPropertyUtilities() const`
- L388 _public prototype_ `void ShowInvalidOperationError(const FText& ErrorText);`
- L392 _protected member_ `TWeakPtr<FPropertyNode> PropertyNode;` — Property node used to access FProperty and address of object to change
- L393 _protected member_ `TWeakPtr<IPropertyUtilities> PropertyUtilities;`
- L395 _protected member_ `FNotifyHook* NotifyHook;` — Notify hook to call when properties change
- L397 _protected member_ `bool bInteractiveChangeInProgress;` — Set true if a change was made with bFinished=false
- L400 _private member_ `TWeakPtr<class SNotificationItem> InvalidOperationError;`

#### class `FPropertyHandleBase`  
`class FPropertyHandleBase : public IPropertyHandle`  
_L412-566_
- inherits: `IPropertyHandle`
- desc: The base implementation of a property handle
- L415 _public prototype_ `FPropertyHandleBase( TSharedPtr<FPropertyNode> PropertyNode, FNotifyHook* NotifyHook, TSharedPtr<IPropertyUtilities> PropertyUtilities );`
- L419 _public prototype_ `DECLARE_PROPERTY_ACCESSOR( int8 ) DECLARE_PROPERTY_ACCESSOR( int16) DECLARE_PROPERTY_ACCESSOR( int32 ) DECLARE_PROPERTY_ACCESSOR( int64 ) DECLARE_PROPERTY_ACCESSOR( uint8 ) DECLARE_PROPERTY_ACCESSOR( uint16 ) DECLARE_PROPERTY_ACCESSOR( uint32 ) DECLARE_PROPERTY_ACCESSOR( uint64 ) DECLARE_PROPERTY_ACCESSOR( float ) DECLARE_PROPERTY_ACCESSOR( double ) DECLARE_PROPERTY_ACCESSOR( FString ) DECLARE_PROPERTY_ACCESSOR( FText ) DECLARE_PROPERTY_ACCESSOR( FName ) DECLARE_PROPERTY_ACCESSOR( FVector ) DECLARE_PROPERTY_ACCESSOR( FVector2D ) DECLARE_PROPERTY_ACCESSOR( FVector4 ) DECLARE_PROPERTY_ACCESSOR( FQuat ) DECLARE_PROPERTY_ACCESSOR( FRotator ) DECLARE_PROPERTY_ACCESSOR( UObject* ) DECLARE_PROPERTY_ACCESSOR( const UObject* ) DECLARE_PROPERTY_ACCESSOR( FAssetData ) DECLARE_PROPERTY_ACCESSOR( FProperty* ) DECLARE_PROPERTY_ACCESSOR( const FProperty* ) virtual FPropertyAccess::Result GetValueData(void*& OutAddress) const override;`
- L444 _public prototype_ `virtual FPropertyAccess::Result SetValue( const TCHAR* InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags ) override;`
- L447 _public prototype_ `virtual bool IsValidHandle() const override;` — IPropertyHandle interface
- L448 _public prototype_ `virtual bool IsSamePropertyNode(TSharedPtr<IPropertyHandle> OtherHandle) const override;`
- L449 _public prototype_ `virtual FText GetPropertyDisplayName() const override;`
- L450 _public prototype_ `virtual void SetPropertyDisplayName(FText InDisplayName) override;`
- L451 _public prototype_ `virtual void ResetToDefault() override;`
- L452 _public prototype_ `virtual bool DiffersFromDefault() const override;`
- L453 _public prototype_ `virtual FText GetResetToDefaultLabel() const override;`
- L454 _public prototype_ `virtual void MarkHiddenByCustomization() override;`
- L455 _public prototype_ `virtual void MarkResetToDefaultCustomized(bool bCustomized = true) override;`
- L456 _public prototype_ `virtual void ClearResetToDefaultCustomized() override;`
- L457 _public prototype_ `virtual bool IsCustomized() const override;`
- L458 _public prototype_ `virtual bool IsResetToDefaultCustomized() const override;`
- L459 _public prototype_ `virtual FString GeneratePathToProperty() const override;`
- L460 _public prototype_ `virtual TSharedRef<SWidget> CreatePropertyNameWidget( const FText& NameOverride, const FText& ToolTipOverride, bool bDisplayResetToDefault, bool bDisplayText, bool bDisplayThumbnail ) const override;`
- L461 _public prototype_ `virtual TSharedRef<SWidget> CreatePropertyNameWidget(const FText& NameOverride, const FText& ToolTipOverride) const override;`
- L462 _public prototype_ `virtual TSharedRef<SWidget> CreatePropertyValueWidget( bool bDisplayDefaultPropertyButtons = true ) const override;`
- L463 _public prototype_ `virtual TSharedRef<SWidget> CreatePropertyValueWidgetWithCustomization( const IDetailsView* DetailsView ) override;`
- L464 _public prototype_ `virtual TSharedRef<SWidget> CreateDefaultPropertyButtonWidgets() const override;`
- L465 _public prototype_ `virtual void CreateDefaultPropertyCopyPasteActions(FUIAction& OutCopyAction, FUIAction& OutPasteAction) const override;`
- L466 _public prototype_ `virtual bool IsEditConst() const override;`
- L467 _public prototype_ `virtual bool IsEditable() const override;`
- L468 _public prototype_ `virtual bool IsExpanded() const override;`
- L469 _public prototype_ `virtual void SetExpanded(bool bExpanded) override;`
- L470 _public prototype_ `virtual void SetOnPropertyValueChanged( const FSimpleDelegate& InOnPropertyValueChanged ) override;`
- L471 _public prototype_ `virtual void SetOnPropertyValueChangedWithData(const TDelegate<void(const FPropertyChangedEvent&)>& InOnPropertyValueChanged) override;`
- L472 _public prototype_ `virtual void SetOnChildPropertyValueChanged( const FSimpleDelegate& InOnPropertyValueChanged ) override;`
- L473 _public prototype_ `virtual void SetOnChildPropertyValueChangedWithData( const TDelegate<void(const FPropertyChangedEvent&)>& InOnChildPropertyValueChanged ) override;`
- L474 _public prototype_ `virtual void SetOnPropertyValuePreChange(const FSimpleDelegate& InOnPropertyValuePreChange) override;`
- L475 _public prototype_ `virtual void SetOnChildPropertyValuePreChange(const FSimpleDelegate& InOnPropertyValuePreChange) override;`
- L476 _public prototype_ `virtual void SetOnPropertyResetToDefault(const FSimpleDelegate& InOnPropertyResetToDefault) override;`
- L478 _public prototype_ `virtual int32 GetIndexInArray() const override;`
- L479 _public prototype_ `virtual FPropertyAccess::Result GetValueAsFormattedString( FString& OutValue, EPropertyPortFlags PortFlags = PPF_PropertyWindow ) const override;`
- L480 _public prototype_ `virtual FPropertyAccess::Result GetValueAsDisplayString( FString& OutValue, EPropertyPortFlags PortFlags = PPF_PropertyWindow) const override;`
- L481 _public prototype_ `virtual FPropertyAccess::Result GetValueAsFormattedText( FText& OutValue ) const override;`
- L482 _public prototype_ `virtual FPropertyAccess::Result GetValueAsDisplayText( FText& OutValue ) const override;`
- L483 _public prototype_ `virtual FPropertyAccess::Result SetValueFromFormattedString( const FString& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags ) override;`
- L484 _public prototype_ `virtual TSharedPtr<IPropertyHandle> GetChildHandle( uint32 ChildIndex ) const override;`
- L485 _public prototype_ `virtual TSharedPtr<IPropertyHandle> GetChildHandle( FName ChildName, bool bRecurse = true ) const override;`
- L486 _public prototype_ `virtual TSharedPtr<IPropertyHandle> GetParentHandle() const override;`
- L487 _public prototype_ `virtual TSharedPtr<IPropertyHandle> GetKeyHandle() const override;`
- L488 _public prototype_ `virtual void EnumerateRawData( const EnumerateRawDataFuncRef& InRawDataCallback ) override;`
- L489 _public prototype_ `virtual void EnumerateConstRawData( const EnumerateConstRawDataFuncRef& InRawDataCallback ) const override;`
- L490 _public prototype_ `virtual void AccessRawData( TArray<void*>& RawData ) override;`
- L491 _public prototype_ `virtual void AccessRawData( TArray<const void*>& RawData ) const override;`
- L492 _public prototype_ `virtual uint32 GetNumOuterObjects() const override;`
- L493 _public prototype_ `virtual void GetOuterObjects(TArray<UObject*>& OuterObjects) const override;`
- L494 _public prototype_ `virtual void GetOuterStructs( TArray<TSharedPtr<FStructOnScope>>& OutStructs ) const override;`
- L495 _public prototype_ `virtual const UClass* GetOuterBaseClass() const override;`
- L496 _public prototype_ `virtual void ReplaceOuterObjects(const TArray<UObject*>& OuterObjects) override;`
- L497 _public prototype_ `virtual void GetOuterPackages(TArray<UPackage*>& OuterPackages) const override;`
- L498 _public prototype_ `virtual FPropertyAccess::Result GetNumChildren( uint32& OutNumChildren ) const override;`
- L499 _public function_ `virtual TSharedPtr<IPropertyHandleArray> AsArray() override`
- L500 _public function_ `virtual TSharedPtr<IPropertyHandleSet> AsSet() override`
- L501 _public function_ `virtual TSharedPtr<IPropertyHandleMap> AsMap() override`
- L502 _public function_ `virtual TSharedPtr<IPropertyHandleOptional> AsOptional() override`
- L503 _public function_ `virtual TSharedPtr<IPropertyHandleStruct> AsStruct() override`
- L504 _public prototype_ `virtual const FFieldClass* GetPropertyClass() const override;`
- L505 _public prototype_ `virtual FProperty* GetProperty() const override;`
- L506 _public prototype_ `virtual FProperty* GetMetaDataProperty() const override;`
- L507 _public prototype_ `virtual bool HasMetaData(const FName& Key) const override;`
- L508 _public prototype_ `virtual const FString& GetMetaData(const FName& Key) const override;`
- L509 _public prototype_ `virtual bool GetBoolMetaData(const FName& Key) const override;`
- L510 _public prototype_ `virtual int32 GetIntMetaData(const FName& Key) const override;`
- L511 _public prototype_ `virtual float GetFloatMetaData(const FName& Key) const override;`
- L512 _public prototype_ `virtual double GetDoubleMetaData(const FName& Key) const override;`
- L513 _public prototype_ `virtual UClass* GetClassMetaData(const FName& Key) const override;`
- L514 _public prototype_ `virtual void SetInstanceMetaData(const FName& Key, const FString& Value) override;`
- L515 _public prototype_ `virtual const FString* GetInstanceMetaData(const FName& Key) const override;`
- L516 _public prototype_ `virtual const TMap<FName, FString>* GetInstanceMetaDataMap() const override;`
- L517 _public prototype_ `virtual FText GetToolTipText() const override;`
- L518 _public prototype_ `virtual void SetToolTipText(const FText& ToolTip) override;`
- L519 _public function_ `virtual bool HasDocumentation() override`
- L520 _public function_ `virtual FString GetDocumentationLink() override`
- L521 _public function_ `virtual FString GetDocumentationExcerptName() override`
- L522 _public prototype_ `virtual uint8* GetValueBaseAddress( uint8* Base ) const override;`
- L523 _public prototype_ `virtual int32 GetNumPerObjectValues() const override;`
- L524 _public prototype_ `virtual FPropertyAccess::Result SetPerObjectValues( const TArray<FString>& InPerObjectValues, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags ) override;`
- L525 _public prototype_ `virtual FPropertyAccess::Result GetPerObjectValues( TArray<FString>& OutPerObjectValues ) const override;`
- L526 _public prototype_ `virtual FPropertyAccess::Result SetPerObjectValue( const int32 ObjectIndex, const FString& ObjectValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags ) override;`
- L527 _public prototype_ `virtual FPropertyAccess::Result GetPerObjectValue( const int32 ObjectIndex, FString& OutObjectValue ) const override;`
- L528 _public prototype_ `virtual bool GeneratePossibleValues(TArray< TSharedPtr<FString> >& OutOptionStrings, TArray< FText >& OutToolTips, TArray<bool>& OutRestrictedItems) override;`
- L529 _public prototype_ `virtual bool GeneratePossibleValues(TArray<FString>& OutOptionStrings, TArray< FText >& OutToolTips, TArray<bool>& OutRestrictedItems, TArray<FText>* OutDisplayNames) override;`
- L530 _public prototype_ `virtual FPropertyAccess::Result SetObjectValueFromSelection() override;`
- L531 _public prototype_ `virtual void NotifyPreChange() override;`
- L532 _public prototype_ `virtual void NotifyPostChange(EPropertyChangeType::Type ChangeType) override;`
- L533 _public prototype_ `virtual void NotifyFinishedChangingProperties() override;`
- L534 _public prototype_ `virtual void AddRestriction(TSharedRef<const FPropertyRestriction> Restriction) override;`
- L535 _public prototype_ `virtual bool IsHidden(const FString& Value) const override;`
- L536 _public prototype_ `virtual bool IsHidden(const FString& Value, TArray<FText>& OutReasons) const override;`
- L537 _public prototype_ `virtual bool IsDisabled(const FString& Value) const override;`
- L538 _public prototype_ `virtual bool IsDisabled(const FString& Value, TArray<FText>& OutReasons) const override;`
- L539 _public prototype_ `virtual bool IsRestricted(const FString& Value) const override;`
- L540 _public prototype_ `virtual bool IsRestricted(const FString& Value, TArray<FText>& OutReasons) const override;`
- L541 _public prototype_ `virtual bool GenerateRestrictionToolTip(const FString& Value, FText& OutTooltip) const override;`
- L542 _public prototype_ `virtual void SetIgnoreValidation(bool bInIgnore) override;`
- L543 _public prototype_ `virtual TArray<TSharedPtr<IPropertyHandle>> AddChildStructure(TSharedRef<FStructOnScope> ChildStructure) override;`
- L544 _public prototype_ `virtual TArray<TSharedPtr<IPropertyHandle>> AddChildStructure(TSharedRef<IStructureDataProvider> ChildStructProvider) override;`
- L545 _public prototype_ `virtual void RemoveChildren() override;`
- L546 _public prototype_ `virtual bool CanResetToDefault() const override;`
- L547 _public prototype_ `virtual void ExecuteCustomResetToDefault(const FResetToDefaultOverride& InOnCustomResetToDefault) override;`
- L548 _public prototype_ `virtual FName GetDefaultCategoryName() const override;`
- L549 _public prototype_ `virtual FText GetDefaultCategoryText() const override;`
- L550 _public prototype_ `virtual FStringView GetPropertyPath() const override;`
- L551 _public prototype_ `virtual TSharedPtr<FPropertyPath> CreateFPropertyPath() const override;`
- L552 _public prototype_ `virtual int32 GetArrayIndex() const override;`
- L553 _public prototype_ `virtual void RequestRebuildChildren() override;`
- L554 _public prototype_ `virtual bool IsFavorite() const override;`
- L555 _public prototype_ `virtual bool IsCategoryHandle() const override;`
- L557 _public prototype_ `TSharedPtr<FPropertyNode> GetPropertyNode() const;`
- L558 _public prototype_ `void OnCustomResetToDefault(const FResetToDefaultOverride& OnCustomResetToDefault);`
- L561 _private prototype_ `static void CopyValueToClipboard(TWeakPtr<FPropertyValueImpl> ImplementationWeak);`
- L562 _private prototype_ `static void PasteValueFromClipboard(TWeakPtr<FPropertyValueImpl> ImplementationWeak);`
- L565 _protected member_ `TSharedPtr<FPropertyValueImpl> Implementation;`

#### class `FPropertyHandleInt`  
`class FPropertyHandleInt : public FPropertyHandleBase`  
_L568-597_
- inherits: `FPropertyHandleBase`
- L571 _public prototype_ `FPropertyHandleInt( TSharedRef<FPropertyNode> PropertyNode, FNotifyHook* NotifyHook, TSharedPtr<IPropertyUtilities> PropertyUtilities );`
- L572 _public prototype_ `static bool Supports( TSharedRef<FPropertyNode> PropertyNode );`
- L574 _public prototype_ `virtual FPropertyAccess::Result GetValue(int8& OutValue ) const override;`
- L575 _public prototype_ `virtual FPropertyAccess::Result SetValue(const int8& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags ) override;`
- L577 _public prototype_ `virtual FPropertyAccess::Result GetValue(int16& OutValue) const override;`
- L578 _public prototype_ `virtual FPropertyAccess::Result SetValue(const int16& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags) override;`
- L580 _public prototype_ `virtual FPropertyAccess::Result GetValue(int32& OutValue) const override;`
- L581 _public prototype_ `virtual FPropertyAccess::Result SetValue(const int32& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags) override;`
- L583 _public prototype_ `virtual FPropertyAccess::Result GetValue(int64& OutValue) const override;`
- L584 _public prototype_ `virtual FPropertyAccess::Result SetValue(const int64& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags) override;`
- L586 _public prototype_ `virtual FPropertyAccess::Result GetValue(uint8& OutValue) const override;`
- L587 _public prototype_ `virtual FPropertyAccess::Result SetValue(const uint8& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags) override;`
- L589 _public prototype_ `virtual FPropertyAccess::Result GetValue(uint16& OutValue) const override;`
- L590 _public prototype_ `virtual FPropertyAccess::Result SetValue(const uint16& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags) override;`
- L592 _public prototype_ `virtual FPropertyAccess::Result GetValue(uint32& OutValue) const override;`
- L593 _public prototype_ `virtual FPropertyAccess::Result SetValue(const uint32& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags) override;`
- L595 _public prototype_ `virtual FPropertyAccess::Result GetValue(uint64& OutValue) const override;`
- L596 _public prototype_ `virtual FPropertyAccess::Result SetValue(const uint64& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags) override;`

#### class `FPropertyHandleFloat`  
`class FPropertyHandleFloat : public FPropertyHandleBase`  
_L599-606_
- inherits: `FPropertyHandleBase`
- L602 _public prototype_ `FPropertyHandleFloat( TSharedRef<FPropertyNode> PropertyNode, FNotifyHook* NotifyHook, TSharedPtr<IPropertyUtilities> PropertyUtilities );`
- L603 _public prototype_ `static bool Supports( TSharedRef<FPropertyNode> PropertyNode );`
- L604 _public prototype_ `virtual FPropertyAccess::Result GetValue( float& OutValue ) const override;`
- L605 _public prototype_ `virtual FPropertyAccess::Result SetValue( const float& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags ) override;`

#### class `FPropertyHandleDouble`  
`class FPropertyHandleDouble : public FPropertyHandleBase`  
_L608-615_
- inherits: `FPropertyHandleBase`
- L611 _public prototype_ `FPropertyHandleDouble( TSharedRef<FPropertyNode> PropertyNode, FNotifyHook* NotifyHook, TSharedPtr<IPropertyUtilities> PropertyUtilities );`
- L612 _public prototype_ `static bool Supports( TSharedRef<FPropertyNode> PropertyNode );`
- L613 _public prototype_ `virtual FPropertyAccess::Result GetValue( double& OutValue ) const override;`
- L614 _public prototype_ `virtual FPropertyAccess::Result SetValue( const double& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags ) override;`

#### class `FPropertyHandleBool`  
`class FPropertyHandleBool : public FPropertyHandleBase`  
_L617-624_
- inherits: `FPropertyHandleBase`
- L620 _public prototype_ `FPropertyHandleBool( TSharedRef<FPropertyNode> PropertyNode, FNotifyHook* NotifyHook, TSharedPtr<IPropertyUtilities> PropertyUtilities );`
- L621 _public prototype_ `static bool Supports( TSharedRef<FPropertyNode> PropertyNode );`
- L622 _public prototype_ `virtual FPropertyAccess::Result GetValue( bool& OutValue ) const override;`
- L623 _public prototype_ `virtual FPropertyAccess::Result SetValue( const bool& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags ) override;`

#### class `FPropertyHandleByte`  
`class FPropertyHandleByte : public FPropertyHandleBase`  
_L626-633_
- inherits: `FPropertyHandleBase`
- L629 _public prototype_ `FPropertyHandleByte( TSharedRef<FPropertyNode> PropertyNode, FNotifyHook* NotifyHook, TSharedPtr<IPropertyUtilities> PropertyUtilities );`
- L630 _public prototype_ `static bool Supports( TSharedRef<FPropertyNode> PropertyNode );`
- L631 _public prototype_ `virtual FPropertyAccess::Result GetValue( uint8& OutValue ) const override;`
- L632 _public prototype_ `virtual FPropertyAccess::Result SetValue( const uint8& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags ) override;`

#### class `FPropertyHandleString`  
`class FPropertyHandleString : public FPropertyHandleBase`  
_L635-646_
- inherits: `FPropertyHandleBase`
- L638 _public prototype_ `FPropertyHandleString( TSharedRef<FPropertyNode> PropertyNode, FNotifyHook* NotifyHook,TSharedPtr<IPropertyUtilities> PropertyUtilities );`
- L639 _public prototype_ `static bool Supports( TSharedRef<FPropertyNode> PropertyNode );`
- L640 _public prototype_ `virtual FPropertyAccess::Result GetValue( FString& OutValue ) const override;`
- L641 _public prototype_ `virtual FPropertyAccess::Result SetValue( const FString& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags ) override;`
- L642 _public prototype_ `virtual FPropertyAccess::Result SetValue( const TCHAR* InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags ) override;`
- L644 _public prototype_ `virtual FPropertyAccess::Result GetValue( FName& OutValue ) const override;`
- L645 _public prototype_ `virtual FPropertyAccess::Result SetValue( const FName& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags ) override;`

#### class `FPropertyHandleObject`  
`class FPropertyHandleObject : public FPropertyHandleBase`  
_L648-662_
- inherits: `FPropertyHandleBase`
- L651 _public prototype_ `FPropertyHandleObject( TSharedRef<FPropertyNode> PropertyNode, FNotifyHook* NotifyHook, TSharedPtr<IPropertyUtilities> PropertyUtilities );`
- L652 _public prototype_ `static bool Supports( TSharedRef<FPropertyNode> PropertyNode );`
- L653 _public prototype_ `virtual FPropertyAccess::Result GetValue( UObject*& OutValue ) const override;`
- L654 _public prototype_ `virtual FPropertyAccess::Result SetValue( UObject* const& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags ) override;`
- L655 _public prototype_ `virtual FPropertyAccess::Result GetValue( const UObject*& OutValue ) const override;`
- L656 _public prototype_ `virtual FPropertyAccess::Result SetValue( const UObject* const& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags ) override;`
- L657 _public prototype_ `virtual FPropertyAccess::Result GetValue( FAssetData& OutValue ) const override;`
- L658 _public prototype_ `virtual FPropertyAccess::Result SetValue( const FAssetData& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags ) override;`
- L659 _public prototype_ `virtual FPropertyAccess::Result SetValueFromFormattedString(const FString& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags) override;`
- L660 _public prototype_ `FPropertyAccess::Result SetValueFromFormattedString(const FString& InValue, EPropertyValueSetFlags::Type Flags, bool bSkipResolve);`
- L661 _public prototype_ `virtual FPropertyAccess::Result SetObjectValueFromSelection() override;`

#### class `FPropertyHandleMixed`  
`class FPropertyHandleMixed : public FPropertyHandleBase`  
_L665-674_
- inherits: `FPropertyHandleBase`
- desc: LWC_TODO: Replace with FPropertyHandleDouble once all types support it
- L668 _public prototype_ `FPropertyHandleMixed(TSharedRef<FPropertyNode> PropertyNode, FNotifyHook* NotifyHook, TSharedPtr<IPropertyUtilities> PropertyUtilities);`
- L669 _public prototype_ `static bool Supports(TSharedRef<FPropertyNode> PropertyNode);`
- L670 _public prototype_ `virtual FPropertyAccess::Result GetValue(float& OutValue) const override;`
- L671 _public prototype_ `virtual FPropertyAccess::Result GetValue(double& OutValue) const override;`
- L672 _public prototype_ `virtual FPropertyAccess::Result SetValue(const float& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags) override;`
- L673 _public prototype_ `virtual FPropertyAccess::Result SetValue(const double& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags) override;`

#### class `FPropertyHandleStruct`  
`class FPropertyHandleStruct : public FPropertyHandleBase, public IPropertyHandleStruct`  
_L676-683_
- inherits: `FPropertyHandleBase,IPropertyHandleStruct`
- L679 _public prototype_ `FPropertyHandleStruct(TSharedRef<FPropertyNode> PropertyNode, FNotifyHook* NotifyHook, TSharedPtr<IPropertyUtilities> PropertyUtilities);`
- L680 _public prototype_ `static bool Supports(TSharedRef<FPropertyNode> PropertyNode);`
- L681 _public prototype_ `virtual TSharedPtr<IPropertyHandleStruct> AsStruct() override;`
- L682 _public prototype_ `virtual TSharedPtr<FStructOnScope> GetStructData() const override;`

#### class `FPropertyHandleVector`  
`class FPropertyHandleVector : public FPropertyHandleStruct`  
_L685-708_
- inherits: `FPropertyHandleStruct`
- L688 _public prototype_ `FPropertyHandleVector( TSharedRef<FPropertyNode> PropertyNode, FNotifyHook* NotifyHook, TSharedPtr<IPropertyUtilities> PropertyUtilities );`
- L689 _public prototype_ `static bool Supports( TSharedRef<FPropertyNode> PropertyNode );`
- L690 _public prototype_ `virtual FPropertyAccess::Result GetValue( FVector& OutValue ) const override;`
- L691 _public prototype_ `virtual FPropertyAccess::Result SetValue( const FVector& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags ) override;`
- L693 _public prototype_ `virtual FPropertyAccess::Result GetValue( FVector2D& OutValue ) const override;`
- L694 _public prototype_ `virtual FPropertyAccess::Result SetValue( const FVector2D& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags ) override;`
- L696 _public prototype_ `virtual FPropertyAccess::Result GetValue( FVector4& OutValue ) const override;`
- L697 _public prototype_ `virtual FPropertyAccess::Result SetValue( const FVector4& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags ) override;`
- L699 _public prototype_ `virtual FPropertyAccess::Result GetValue( FQuat& OutValue ) const override;`
- L700 _public prototype_ `virtual FPropertyAccess::Result SetValue( const FQuat& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags ) override;`
- L702 _public prototype_ `virtual FPropertyAccess::Result SetX(double InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags);`
- L703 _public prototype_ `virtual FPropertyAccess::Result SetY(double InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags);`
- L704 _public prototype_ `virtual FPropertyAccess::Result SetZ(double InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags);`
- L705 _public prototype_ `virtual FPropertyAccess::Result SetW(double InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags);`
- L707 _private member_ `TArray< TSharedPtr<FPropertyHandleMixed> > VectorComponents;`

#### class `FPropertyHandleRotator`  
`class FPropertyHandleRotator : public FPropertyHandleStruct`  
_L710-727_
- inherits: `FPropertyHandleStruct`
- L713 _public prototype_ `FPropertyHandleRotator( TSharedRef<FPropertyNode> PropertyNode, FNotifyHook* NotifyHook, TSharedPtr<IPropertyUtilities> PropertyUtilities );`
- L714 _public prototype_ `static bool Supports( TSharedRef<FPropertyNode> PropertyNode );`
- L715 _public prototype_ `virtual FPropertyAccess::Result GetValue( FRotator& OutValue ) const override;`
- L716 _public prototype_ `virtual FPropertyAccess::Result SetValue( const FRotator& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags ) override;`
- L717 _public prototype_ `virtual FPropertyAccess::Result GetValue(FQuat& OutValue) const override;`
- L718 _public prototype_ `virtual FPropertyAccess::Result SetValue(const FQuat& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags) override;`
- L720 _public prototype_ `virtual FPropertyAccess::Result SetRoll( double InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags );`
- L721 _public prototype_ `virtual FPropertyAccess::Result SetPitch( double InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags );`
- L722 _public prototype_ `virtual FPropertyAccess::Result SetYaw( double InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags );`
- L724 _private member_ `TSharedPtr<FPropertyHandleMixed> RollValue;`
- L725 _private member_ `TSharedPtr<FPropertyHandleMixed> PitchValue;`
- L726 _private member_ `TSharedPtr<FPropertyHandleMixed> YawValue;`

#### class `FPropertyHandleColor`  
`class FPropertyHandleColor : public FPropertyHandleStruct`  
_L729-736_
- inherits: `FPropertyHandleStruct`
- L732 _public prototype_ `FPropertyHandleColor( TSharedRef<FPropertyNode> PropertyNode, FNotifyHook* NotifyHook, TSharedPtr<IPropertyUtilities> PropertyUtilities );`
- L733 _public prototype_ `static bool Supports( TSharedRef<FPropertyNode> PropertyNode );`
- L735 _public prototype_ `virtual FPropertyAccess::Result SetValueFromFormattedString(const FString& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags) override;`

#### class `FPropertyHandleArray`  
`class FPropertyHandleArray : public FPropertyHandleBase, public IPropertyHandleArray`  
_L738-761_
- inherits: `FPropertyHandleBase,IPropertyHandleArray`
- L741 _public prototype_ `FPropertyHandleArray( TSharedRef<FPropertyNode> PropertyNode, FNotifyHook* NotifyHook, TSharedPtr<IPropertyUtilities> PropertyUtilities );`
- L742 _public prototype_ `static bool Supports( TSharedRef<FPropertyNode> PropertyNode );`
- L744 _public prototype_ `virtual FPropertyHandleItemAddResult AddItem() override;` — IPropertyHandleArray interface
- L745 _public prototype_ `virtual FPropertyAccess::Result EmptyArray() override;`
- L746 _public prototype_ `virtual FPropertyAccess::Result Insert( int32 Index ) override;`
- L747 _public prototype_ `virtual FPropertyAccess::Result DuplicateItem( int32 Index ) override;`
- L748 _public prototype_ `virtual FPropertyAccess::Result DeleteItem( int32 Index ) override;`
- L749 _public prototype_ `virtual FPropertyAccess::Result SwapItems(int32 FirstIndex, int32 SecondIndex) override;`
- L750 _public prototype_ `virtual FPropertyAccess::Result GetNumElements( uint32& OutNumItems ) const override;`
- L751 _public prototype_ `virtual FDelegateHandle SetOnNumElementsChanged( const FSimpleDelegate& InOnNumElementsChanged ) override;`
- L752 _public prototype_ `virtual void UnregisterOnNumElementsChanged(FDelegateHandle Handle) override;`
- L753 _public prototype_ `virtual void SetOnCanItemChange(const FCanPropertyItemChange& InDelegate) override;`
- L754 _public prototype_ `virtual FDelegateHandle SetOnChangeBlocked(const FPropertyChangeBlocked::FDelegate& InDelegate) override;`
- L755 _public prototype_ `virtual void UnregisterOnChangeBlocked(FDelegateHandle Handle) override;`
- L756 _public prototype_ `virtual TSharedPtr<IPropertyHandleArray> AsArray() override;`
- L757 _public prototype_ `virtual TSharedRef<IPropertyHandle> GetElement( int32 Index ) const override;`
- L758 _public prototype_ `virtual FPropertyAccess::Result MoveElementTo(int32 OriginalIndex, int32 NewIndex) override;`
- L759 _public prototype_ `virtual FPropertyAccess::Result SetValueFromFormattedString(const FString& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags) override;`
- L760 _public prototype_ `virtual bool IsEditable() const override;`

#### class `FPropertyHandleOptional`  
`class FPropertyHandleOptional : public FPropertyHandleBase, public IPropertyHandleOptional`  
_L763-774_
- inherits: `FPropertyHandleBase,IPropertyHandleOptional`
- L766 _public prototype_ `FPropertyHandleOptional(TSharedRef<FPropertyNode> PropertyNode, FNotifyHook* NotifyHook, TSharedPtr<IPropertyUtilities> PropertyUtilities);`
- L767 _public prototype_ `static bool Supports(TSharedRef<FPropertyNode> PropertyNode);`
- L769 _public prototype_ `virtual FPropertyAccess::Result GetOptionalValue(FProperty*& OutValue) override;` — IPropertyHandleOptional interface
- L770 _public prototype_ `virtual FPropertyAccess::Result SetOptionalValue(FProperty* NewProperty, const UClass* NewObjectClass) override;`
- L771 _public prototype_ `virtual FPropertyAccess::Result ClearOptionalValue() override;`
- L772 _public prototype_ `virtual TSharedPtr<IPropertyHandleOptional> AsOptional() override;`
- L773 _public prototype_ `virtual bool IsEditable() const override;`

#### class `FPropertyHandleText`  
`class FPropertyHandleText : public FPropertyHandleBase`  
_L776-790_
- inherits: `FPropertyHandleBase`
- L779 _public prototype_ `FPropertyHandleText(TSharedRef<FPropertyNode> PropertyNode, FNotifyHook* NotifyHook,TSharedPtr<IPropertyUtilities> PropertyUtilities);`
- L780 _public prototype_ `static bool Supports(TSharedRef<FPropertyNode> PropertyNode);`
- L781 _public prototype_ `virtual FPropertyAccess::Result GetValue(FText& OutValue) const override;`
- L782 _public prototype_ `virtual FPropertyAccess::Result SetValue(const FText& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags) override;`
- L784 _public prototype_ `virtual FPropertyAccess::Result SetValue(const FString& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags) override;`
- L785 _public prototype_ `virtual FPropertyAccess::Result SetValue(const TCHAR* InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags) override;`
- L786 _public prototype_ `virtual FPropertyAccess::Result SetValueFromFormattedString(const FString& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags) override;`
- L789 _private prototype_ `FPropertyAccess::Result ImportFormattedTextString(const FString& InValue, EPropertyValueSetFlags::Type Flags);`

#### class `FPropertyHandleSet`  
`class FPropertyHandleSet : public FPropertyHandleBase, public IPropertyHandleSet`  
_L792-814_
- inherits: `FPropertyHandleBase,IPropertyHandleSet`
- L795 _public prototype_ `FPropertyHandleSet(TSharedRef<FPropertyNode> PropertyNode, FNotifyHook* NotifyHook, TSharedPtr<IPropertyUtilities> PropertyUtilities);`
- L796 _public prototype_ `static bool Supports(TSharedRef<FPropertyNode> PropertyNode);`
- L797 _public prototype_ `virtual TSharedPtr<IPropertyHandleSet> AsSet() override;`
- L800 _public prototype_ `virtual bool HasDefaultElement() override;` — IPropertyHandleSet Interface
- L801 _public prototype_ `virtual FPropertyHandleItemAddResult AddItem() override;`
- L802 _public prototype_ `virtual FPropertyAccess::Result Empty() override;`
- L803 _public prototype_ `virtual FPropertyAccess::Result DeleteItem(int32 Index) override;`
- L804 _public prototype_ `virtual FPropertyAccess::Result GetNumElements(uint32& OutNumElements) override;`
- L805 _public prototype_ `virtual TSharedRef<IPropertyHandle> GetElement(int32 Index) const override;`
- L806 _public prototype_ `virtual FPropertyAccess::Result SetValueFromFormattedString(const FString& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags) override;`
- L808 _public prototype_ `virtual FDelegateHandle SetOnNumElementsChanged( const FSimpleDelegate& InOnNumElementsChanged ) override;`
- L809 _public prototype_ `virtual void UnregisterOnNumElementsChanged(FDelegateHandle Handle) override;`
- L810 _public function_ `virtual bool HasDocumentation() override`
- L811 _public function_ `virtual FString GetDocumentationLink() override`
- L812 _public function_ `virtual FString GetDocumentationExcerptName() override`
- L813 _public prototype_ `virtual bool IsEditable() const override;`

#### class `FPropertyHandleMap`  
`class FPropertyHandleMap : public FPropertyHandleBase, public IPropertyHandleMap`  
_L816-839_
- inherits: `FPropertyHandleBase,IPropertyHandleMap`
- L819 _public prototype_ `FPropertyHandleMap(TSharedRef<FPropertyNode> PropertyNode, FNotifyHook* NotifyHook, TSharedPtr<IPropertyUtilities> PropertyUtilities);`
- L820 _public prototype_ `static bool Supports(TSharedRef<FPropertyNode> PropertyNode);`
- L821 _public prototype_ `virtual TSharedPtr<IPropertyHandleMap> AsMap() override;`
- L824 _public prototype_ `virtual bool HasDefaultKey() override;` — IPropertyHandleMap Interface
- L825 _public prototype_ `virtual FPropertyHandleItemAddResult AddItem() override;`
- L826 _public prototype_ `virtual FPropertyAccess::Result Empty() override;`
- L827 _public prototype_ `virtual FPropertyAccess::Result DeleteItem(int32 Index) override;`
- L828 _public prototype_ `virtual FPropertyAccess::Result GetNumElements(uint32& OutNumElements) override;`
- L829 _public prototype_ `virtual TSharedRef<IPropertyHandle> GetElement(int32 Index) const override;`
- L830 _public prototype_ `virtual FDelegateHandle SetOnNumElementsChanged( const FSimpleDelegate& InOnNumElementsChanged ) override;`
- L831 _public prototype_ `virtual void UnregisterOnNumElementsChanged(FDelegateHandle Handle) override;`
- L832 _public function_ `virtual bool HasDocumentation() override`
- L833 _public function_ `virtual FString GetDocumentationLink() override`
- L834 _public function_ `virtual FString GetDocumentationExcerptName() override`
- L835 _public prototype_ `virtual bool IsEditable() const override;`
- L838 _private prototype_ `int32 AddItemWithKey(const FString& Value);`

#### class `FPropertyHandleFieldPath`  
`class FPropertyHandleFieldPath : public FPropertyHandleBase`  
_L841-850_
- inherits: `FPropertyHandleBase`
- L844 _public prototype_ `FPropertyHandleFieldPath(TSharedRef<FPropertyNode> PropertyNode, FNotifyHook* NotifyHook, TSharedPtr<IPropertyUtilities> PropertyUtilities);`
- L845 _public prototype_ `static bool Supports(TSharedRef<FPropertyNode> PropertyNode);`
- L846 _public prototype_ `virtual FPropertyAccess::Result GetValue(FProperty*& OutValue) const override;`
- L847 _public prototype_ `virtual FPropertyAccess::Result SetValue(FProperty* const& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags) override;`
- L848 _public prototype_ `virtual FPropertyAccess::Result GetValue(const FProperty*& OutValue) const override;`
- L849 _public prototype_ `virtual FPropertyAccess::Result SetValue(const FProperty* const& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags) override;`

#### Free symbols / members of external scopes

- L403 _macro_ `#define DECLARE_PROPERTY_ACCESSOR( ValueType ) \`

### `Source/Editor/PropertyEditor/Private/PropertyNode.h` (Private)


#### class `FPropertySettings`  
`class FPropertySettings`  
_L100-113_
- L103 _public prototype_ `static FPropertySettings& Get();`
- L104 _public function_ `bool ShowFriendlyPropertyNames() const`
- L105 _public function_ `bool ShowHiddenProperties() const`
- L106 _public function_ `bool ExpandDistributions() const`
- L108 _private prototype_ `FPropertySettings();`
- L110 _private member_ `bool bShowFriendlyPropertyNames;`
- L111 _private member_ `bool bExpandDistributions;`
- L112 _private member_ `bool bShowHiddenProperties;`

#### struct `FAddressPair`  
`struct FAddressPair`  
_L115-125_
- L117 _public function_ `FAddressPair(const UObject* InObject, uint8* Address, bool bInIsStruct) : Object( InObject) , ReadAddress( Address ) , bIsStruct(bInIsStruct)`
- L122 _public member_ `TWeakObjectPtr<const UObject> Object;`
- L123 _public member_ `uint8* ReadAddress;`
- L124 _public member_ `bool bIsStruct;`

#### enum `TIsPODType::(anonymous)`  
`template<> struct TIsPODType<FAddressPair>`  
_L127-127_

#### struct `TIsPODType`  
`template<> struct TIsPODType<FAddressPair>`  
_L127-127_

#### struct `FReadAddressListData`  
`struct FReadAddressListData`  
_L129-175_
- L132 _public function_ `FReadAddressListData() : bAllValuesTheSame( false ) , bRequiresCache( true )`
- L137 _public function_ `void Add(const UObject* Object, uint8* Address, bool bIsStruct = false)`
- L142 _public function_ `int32 Num() const`
- L147 _public function_ `uint8* GetAddress( int32 Index )`
- L153 _public function_ `const UObject* GetObject(int32 Index)`
- L159 _public function_ `bool IsValidIndex( int32 Index ) const`
- L164 _public function_ `void Reset()`
- L171 _public member_ `bool bAllValuesTheSame;`
- L172 _public member_ `bool bRequiresCache;`
- L174 _private member_ `TArray<FAddressPair> ReadAddresses;`

#### class `FReadAddressList`  
`class FReadAddressList`  
_L180-218_
- desc: A list of read addresses for a property node which contains the address for the nodes FProperty on each object
- L184 _public function_ `FReadAddressList() : ReadAddressListData(nullptr)`
- L188 _public function_ `int32 Num() const`
- L193 _public function_ `uint8* GetAddress( int32 Index )`
- L198 _public function_ `const UObject* GetObject(int32 Index)`
- L203 _public function_ `bool IsValidIndex( int32 Index ) const`
- L208 _public function_ `void Reset()`
- L217 _private member_ `FReadAddressListData* ReadAddressListData;`

#### struct `FPropertyNodeInitParams`  
`struct FPropertyNodeInitParams`  
_L225-268_
- desc: Parameters for initializing a property node
- L235 _public member_ `TSharedPtr<FPropertyNode> ParentNode;` — The parent of the property node
- L237 _public member_ `FProperty* Property;` — The property that the node observes and modifies
- L239 _public member_ `int32 ArrayOffset;` — Offset to the property data within either a fixed array or a dynamic array
- L241 _public member_ `int32 ArrayIndex;` — Index of the property in its array parent
- L243 _public member_ `bool bAllowChildren;` — Whether or not to create any children
- L245 _public member_ `bool bForceHiddenPropertyVisibility;` — Whether or not to allow hidden properties (ones without CPF_Edit) to be visible
- L247 _public member_ `bool bCreateCategoryNodes;` — Whether or not to create category nodes (note: this setting is only valid for the root node of a property tree. The setting will propagate to children)
- L249 _public member_ `bool bCreateDisableEditOnInstanceNodes;` — Whether or not to create nodes for properties marked CPF_DisableEditOnInstance
- L251 _public member_ `bool bResolveInstanceDataObjects;` — Resolve Objects to their IDOs
- L254 _public member_ `EIsSparseDataProperty IsSparseProperty;` — Whether or not this property is sparse data
- L256 _public function_ `FPropertyNodeInitParams() : ParentNode(nullptr) , Property(nullptr) , ArrayOffset(0) , ArrayIndex( INDEX_NONE ) , bAllowChildren( true ) , bForceHiddenPropertyVisibility( false ) , bCreateCategoryNodes( true ) , bCreateDisableEditOnInstanceNodes( true ) , bResolveInstanceDataObjects(false) , IsSparseProperty( EIsSparseDataProperty::Inherit )`

#### enum `FPropertyNodeInitParams::EIsSparseDataProperty`  
`enum class EIsSparseDataProperty : uint8`  
_L227-232_
- L229 _public enumerator_ `False`
- L230 _public enumerator_ `True`
- L231 _public enumerator_ `Inherit`

#### struct `EPropertyArrayChangeType`  
`struct EPropertyArrayChangeType`  
_L272-289_
- desc: Describes in which way an array property change has happend. This is used for propagation of array property changes to the instances of archetype objects.

#### enum `EPropertyArrayChangeType::Type`  
`enum Type`  
_L274-288_
- L277 _public enumerator_ `Add` — A value was added to the array
- L279 _public enumerator_ `Clear` — The array was cleared
- L281 _public enumerator_ `Insert` — A new item has been inserted.
- L283 _public enumerator_ `Delete` — An item has been deleted
- L285 _public enumerator_ `Duplicate` — An item has been duplicated
- L287 _public enumerator_ `Swap` — Two items have been swapped

#### enum `EPropertyDataValidationResult`  
`enum EPropertyDataValidationResult : uint8`  
_L291-305_
- L294 _public enumerator_ `ObjectInvalid` — The object(s) being viewed are now invalid
- L296 _public enumerator_ `PropertiesChanged` — Non dynamic array property nodes were added or removed that would require a refresh
- L298 _public enumerator_ `EditInlineNewValueChanged` — An edit inline new value changed,  In the tree this rebuilds the nodes, in the details view we don't need to do this
- L300 _public enumerator_ `ArraySizeChanged` — The size of an array changed (delete,insert,add)
- L302 _public enumerator_ `ChildrenRebuilt` — An internal node's children were rebuilt for some reason
- L304 _public enumerator_ `DataValid` — All data is valid

#### class `FPropertyNodeEditStack`  
`class FPropertyNodeEditStack`  
_L308-370_
- desc: Helper class for modifying property values with setters and getters
- L330 _public prototype_ `FPropertyNodeEditStack(const FPropertyNode* InNode, const UObject* InObj = nullptr);` — Constructs property stack for the specified node InNode Property node to construct the stack for InObj Optional Object instance that contains the property being modified (if not provided the root container pointer will be acquired from the provided node hierarchy)
- L331 _public prototype_ `FPropertyNodeEditStack() = default;`
- L332 _public prototype_ `~FPropertyNodeEditStack();`
- L334 _public prototype_ `FPropertyNodeEditStack& operator = (const FPropertyNodeEditStack& Other) = delete;`
- L335 _public prototype_ `FPropertyNodeEditStack(const FPropertyNodeEditStack& Other) = delete;`
- L342 _public prototype_ `FPropertyAccess::Result Initialize(const FPropertyNode* InNode, const UObject* InObj);` — Initializes property stack for the specified node InNode Property node to construct the stack for InObj Object instance that contains the property being modified
- L348 _public function_ `uint8* GetDirectPropertyAddress()` — Returns the address of the property being modified. If anywhere in the property stack is a property with a setter or getter this will point to a temporarily allocated memory.
- L356 _public prototype_ `void CommitChanges();` — Commits all modifications to temporarily allocated property values back to the actual member variables using setters and getters where available
- L359 _public function_ `bool IsValid() const` — Checks if this edit stack is valid
- L366 _private prototype_ `FPropertyAccess::Result InitializeInternal(const FPropertyNode* InNode, const UObject* InObj);`
- L367 _private prototype_ `void Cleanup();`
- L369 _private member_ `TArray<FMemoryFrame> MemoryStack;`

#### struct `FPropertyNodeEditStack::FMemoryFrame`  
`struct FMemoryFrame`  
_L310-322_
- L312 _public prototype_ `FMemoryFrame() = default;`
- L313 _public function_ `FMemoryFrame(const FProperty* InProperty, uint8* InMemory) : Property(InProperty) , Memory(InMemory)`
- L319 _public member_ `const FProperty* Property = nullptr;` — Property that points to the memory in this frame
- L321 _public member_ `uint8* Memory = nullptr;` — Property address

#### class `FPropertyNode`  
`class FPropertyNode : public TSharedFromThis<FPropertyNode>`  
_L375-1348_
- inherits: `TSharedFromThis<FPropertyNode>`
- desc: The base class for all property nodes
- L379 _public prototype_ `FPropertyNode();`
- L380 _public prototype_ `virtual ~FPropertyNode();`
- L386 _public prototype_ `void InitNode(const FPropertyNodeInitParams& InitParams);` — Init Tree Node internally (used only derived classes to pass through variables that are common to all nodes @param InitParams	Parameters for how the node should be initialized
- L391 _public function_ `void RequestRebuildChildren()` — Indicates that children of this node should be rebuilt next tick.  Some topology changes will require this
- L396 _public prototype_ `void RebuildChildren();` — Used for rebuilding this nodes children
- L401 _public prototype_ `void MarkChildrenAsRebuilt();` — Mark this and all children as having been rebuilt.
- L406 _public prototype_ `void AddChildNode(TSharedPtr<FPropertyNode> InNode);` — For derived windows to be able to add their nodes to the child array
- L411 _public prototype_ `void RemoveAllChildNodes();` — Destroys all child nodes under this node
- L416 _public prototype_ `void ClearCachedReadAddresses(bool bRecursive = true);` — Clears cached read address data
- L421 _public function_ `virtual FObjectPropertyNode* AsObjectNode()` — Interface function to get at the derived FObjectPropertyNode class
- L422 _public function_ `virtual const FObjectPropertyNode* AsObjectNode() const`
- L427 _public function_ `virtual FComplexPropertyNode* AsComplexNode()` — Interface function to get at the derived FComplexPropertyNode class
- L428 _public function_ `virtual const FComplexPropertyNode* AsComplexNode() const`
- L433 _public function_ `virtual FCategoryPropertyNode* AsCategoryNode()` — Interface function to get at the derived FCategoryPropertyNode class
- L434 _public function_ `virtual const FCategoryPropertyNode* AsCategoryNode() const`
- L439 _public function_ `virtual FItemPropertyNode* AsItemPropertyNode()` — Interface function to get at the derived FItemPropertyNode class
- L440 _public function_ `virtual const FItemPropertyNode* AsItemPropertyNode() const`
- L445 _public prototype_ `FComplexPropertyNode* FindComplexParent();` — Follows the chain of items upwards until it finds the complex property that houses this item.
- L446 _public prototype_ `const FComplexPropertyNode* FindComplexParent() const;`
- L451 _public prototype_ `FObjectPropertyNode* FindObjectItemParent();` — Follows the chain of items upwards until it finds the object property that houses this item.
- L452 _public prototype_ `const FObjectPropertyNode* FindObjectItemParent() const;`
- L457 _public prototype_ `FStructurePropertyNode* FindStructureItemParent();` — Follows the chain of items upwards until it finds the structure property that houses this item.
- L458 _public prototype_ `const FStructurePropertyNode* FindStructureItemParent() const;`
- L463 _public prototype_ `FObjectPropertyNode* FindRootObjectItemParent();` — Follows the top-most object window that contains this property window item.
- L468 _public prototype_ `virtual EPropertyDataValidationResult EnsureDataIsValid();` — Used to see if any data has been destroyed from under the property tree.  Should only be called during Tick
- L479 _public prototype_ `FPropertyAccess::Result GetPropertyValueString(FString& OutString, const bool bAllowAlternateDisplayValue, EPropertyPortFlags PortFlags = PPF_PropertyWindow) const;` — @param OutText						The property formatted in a string @param bAllowAlternateDisplayValue	Allow the function to potentially use an alternate form more suitable for display in the UI @param PortFlags						Determines how the property's value is accessed. Defaults to PPF_PropertyWindow @return true if the value was retrieved successfully
- L486 _public prototype_ `FPropertyAccess::Result GetPropertyValueText(FText& OutText, const bool bAllowAlternateDisplayValue) const;` — @param OutText			The property formatted in text @param bAllowAlternateDisplayValue Allow the function to potentially use an alternate form more suitable for display in the UI @return true if the value was retrieved successfully
- L490 _public function_ `bool HasNodeFlags(const EPropertyNodeFlags::Type InTestFlags) const` — Flags
- L496 _public prototype_ `void SetNodeFlags(const EPropertyNodeFlags::Type InFlags, const bool InOnOff);` — Sets the flags used by the window and the root node @param InFlags - flags to turn on or off @param InOnOff - whether to toggle the bits on or off
- L504 _public prototype_ `TSharedPtr<FPropertyNode> FindChildPropertyNode(const FName InPropertyName, bool bRecurse = false);` — Finds a child of this property node @param InPropertyName	The name of the property to find @param bRecurse		true if we should recurse into children's children and so on.
- L509 _public function_ `FPropertyNode* GetParentNode()` — Returns the parent node in the hierarchy
- L510 _public function_ `const FPropertyNode* GetParentNode() const`
- L511 _public function_ `TSharedPtr<FPropertyNode> GetParentNodeSharedPtr()`
- L515 _public function_ `FProperty* GetProperty()` — Returns the Property this Node represents
- L516 _public function_ `const FProperty* GetProperty() const`
- L521 _public function_ `int32 GetArrayOffset() const` — Accessor functions for internals
- L522 _public function_ `int32 GetArrayIndex() const`
- L527 _public function_ `int32 GetNumChildNodes() const` — Return number of children that survived being filtered
- L532 _public function_ `TSharedPtr<FPropertyNode>& GetChildNode(const int32 ChildIndex)` — Returns the matching Child node
- L541 _public function_ `const TSharedPtr<FPropertyNode>& GetChildNode(const int32 ChildIndex) const` — Returns the matching Child node
- L550 _public prototype_ `bool GetChildNode(const int32 ChildArrayIndex, TSharedPtr<FPropertyNode>& OutChildNode);` — Returns the Child node whose ArrayIndex matches the supplied ChildIndex
- L555 _public prototype_ `bool GetChildNode(const int32 ChildArrayIndex, TSharedPtr<FPropertyNode>& OutChildNode) const;` — Returns the Child node whose ArrayIndex matches the supplied ChildIndex
- L560 _public prototype_ `bool IsPropertyConst() const;` — Returns whether this window's property is read only or has the CPF_EditConst flag.
- L563 _public prototype_ `bool IsEditConst(const bool bIncludeEditCondition = true) const;` — @return whether this window's property is constant (can't be edited by the user). If bIncludeEditCondition is false, the property is considered editable regardless of the EditCondition result.
- L568 _public prototype_ `bool ShouldSkipSerialization() const;` — Returns whether this window's property should not be serialized (determined by the CPF_SkipSerialization flag).
- L577 _public prototype_ `virtual bool GetQualifiedName(FString& PathPlusIndex, const bool bWithArrayIndex, const FPropertyNode* StopParent = nullptr, bool bIgnoreCategories = false) const;` — Gets the full name of this node @param PathPlusIndex - return value with full path of node @param bWithArrayIndex - If True, adds an array index (where appropriate) @param StopParent	- Stop at this parent (if any). Does NOT include it in the path @param bIgnoreCategories - Skip over categories
- L581 _public prototype_ `bool GetReadAddress( bool InRequiresSingleSelection, FReadAddressList& OutAddresses, bool bComparePropertyContents = true, bool bObjectForceCompare = false, bool bArrayPropertiesCanDifferInSize = false) const;` — The bArrayPropertiesCanDifferInSize flag is an override for array properties which want to display e.g. the "Clear" and "Empty" buttons, even though the array properties may differ in the number of elements.
- L592 _public prototype_ `bool GetReadAddress(FReadAddressList& OutAddresses) const;` — fills in the OutAddresses array with the addresses of all of the available objects. @param OutAddresses	Storage array for all of the objects' addresses.
- L599 _public prototype_ `FPropertyAccess::Result GetSingleReadAddress(uint8*& OutValueAddress) const;` — Fills in the OutValueAddress with the address of the value of all the available objects. If multiple items are selected, this will return a null address unless they are all the same value. @param OutValueAddress	The address of the item
- L606 _public prototype_ `FPropertyAccess::Result GetSingleObject(UObject*& OutObject) const;` — Fills in the OutObject with the address of the object of all the available objects. If multiple items are selected, this will return a null address unless they are all the same value. @param OutObject	The address of the Object
- L612 _public prototype_ `FPropertyAccess::Result GetSingleEditStack(FPropertyNodeEditStack& OutStack) const;` — Fills in the OutContainer with the address of the container (struct or UObject instance) that owns the property this node represents. @param OutContainer	The address of the container instance
- L617 _public prototype_ `virtual bool GetReadAddressUncached(const FPropertyNode& InNode, bool InRequiresSingleSelection, FReadAddressListData* OutAddresses, bool bComparePropertyContents = true, bool bObjectForceCompare = false, bool bArrayPropertiesCanDifferInSize = false) const;` — Gets read addresses without accessing cached data.  Is less efficient but gets the must up to date data
- L618 _public prototype_ `virtual bool GetReadAddressUncached(const FPropertyNode& InNode, FReadAddressListData& OutAddresses) const;`
- L628 _public prototype_ `virtual uint8* GetValueBaseAddress(uint8* StartAddress, bool bIsSparseData, bool bIsStruct = false) const;` — Calculates the memory address for the data associated with this item's property.  This is typically the value of a FProperty or a UObject address. @param	StartAddress	the location to use as the starting point for the calculation; typically the address of the object that contains this property. @param	bIsSparseData	True if StartAddress is pointing to a sidecar structure containing sparse class data, false otherwise @return	a pointer to a FProperty value or UObject.  (For dynamic arrays, you'd cast this value to an FArray*)
- L639 _public prototype_ `virtual uint8* GetValueAddress(uint8* StartAddress, bool bIsSparseData, bool bIsStruct = false) const;` — Calculates the memory address for the data associated with this item's value.  For most properties, identical to GetValueBaseAddress.  For items corresponding to dynamic array elements, the pointer returned will be the location for that element's data. @param	StartAddress	the location to use as the starting point for the calculation; typically the address of the object that contains this property. @param	bIsSparseData	True if StartAddress is pointing to a sidecar structure containing sparse class data, false otherwise @return	a pointer to a FProperty value or UObject.  (For dynamic arrays, you'd cast this value to whatever type is the Inner for the dynamic array)
- L645 _public prototype_ `uint8* GetStartAddressFromObject(const UObject* Obj) const;` — Caclulates the memory address for the starting point of the structure that contains the property this node uses. This will often be Obj but may also point to a sidecar data structure.
- L654 _public prototype_ `uint8* GetValueBaseAddressFromObject(const UObject* Obj) const;` — Calculates the memory address for the data associated with this item's property.  This is typically the value of a FProperty or a UObject address. @param	Obj	The object that contains this property; used as the starting point for the calculation @return	a pointer to a FProperty value or UObject.  (For dynamic arrays, you'd cast this value to an FArray*)
- L664 _public prototype_ `uint8* GetValueAddressFromObject(const UObject* Obj) const;` — Calculates the memory address for the data associated with this item's value.  For most properties, identical to GetValueBaseAddress.  For items corresponding to dynamic array elements, the pointer returned will be the location for that element's data. @param	Obj	The object that contains this property; used as the starting point for the calculation @return	a pointer to a FProperty value or UObject.  (For dynamic arrays, you'd cast this value to whatever type is the Inner for the dynamic array)
- L669 _public function_ `virtual void SetDisplayNameOverride(const FText& InDisplayNameOverride)` — Sets the display name override to use instead of the display name
- L674 _public function_ `virtual void SetFavorite(bool FavoriteValue)` — @return true if the property is mark as a favorite
- L679 _public function_ `virtual bool IsFavorite() const` — @return true if the property is mark as a favorite
- L684 _public function_ `virtual FText GetDisplayName() const` — @return The formatted display name for the property in this node
- L689 _public function_ `virtual void SetToolTipOverride(const FText& InToolTipOverride)` — Sets the tooltip override to use instead of the property tooltip
- L694 _public function_ `virtual FText GetToolTipText() const` — @return The tooltip for the property in this node
- L699 _public prototype_ `bool GetDiffersFromDefault();` — If there is a property, sees if it matches.  Otherwise sees if the entire parent structure matches
- L704 _public prototype_ `FText GetResetToDefaultLabel();` — @return The label for displaying a reset to default value
- L709 _public prototype_ `bool IsReorderable();` — @return If this property node is associated with a property that can be reordered within an array
- L712 _public prototype_ `bool IsChildOfFavorite() const;` — Walks up the hierarchy and return true if any parent node is a favorite
- L714 _public prototype_ `void NotifyPreChange(FProperty* PropertyAboutToChange, FNotifyHook* InNotifyHook);`
- L715 _public prototype_ `void NotifyPreChange(FProperty* PropertyAboutToChange, FNotifyHook* InNotifyHook, const TSet<UObject*>& AffectedInstances);`
- L716 _public prototype_ `void NotifyPreChange(FProperty* PropertyAboutToChange, FNotifyHook* InNotifyHook, TSet<UObject*>&& AffectedInstances);`
- L718 _public prototype_ `void NotifyPostChange(FPropertyChangedEvent& InPropertyChangedEvent, FNotifyHook* InNotifyHook);`
- L720 _public prototype_ `DECLARE_EVENT(FPropertyNode, FPropertyChildrenRebuiltEvent);`
- L721 _public prototype_ `FDelegateHandle SetOnRebuildChildren(const FSimpleDelegate& InOnRebuildChildren);`
- L722 _public function_ `FPropertyChildrenRebuiltEvent& OnRebuildChildren()`
- L731 _public prototype_ `void PropagatePropertyChange(UObject* ModifiedObject, const TCHAR* NewValue, const FString& PreviousValue);` — Propagates the property change to all instances of an archetype @param	ModifiedObject	Object which property has been modified @param	NewValue		New value of the property @param	PreviousValue	Value of the property before the modification
- L741 _public prototype_ `void PropagateContainerPropertyChange(UObject* ModifiedObject, const void* OriginalContainerAddr, EPropertyArrayChangeType::Type ChangeType, int32 Index, int32 SwapIndex = INDEX_NONE);` — Propagates the property change of a container property to all instances of an archetype @param	ModifiedObject				Object which property has been modified @param	OriginalContainerAddr		Original address holding the container value before the modification @param	ChangeType					In which way was the container modified @param	Index						Index of the modified item
- L747 _public prototype_ `static void DuplicateArrayEntry(UObject* ModifiedObject, FProperty* NodeProperty, FScriptArrayHelper& ArrayHelper, int32 Index);` — Helper function to centralize logic for duplcating an array entry and ensuring that instanced object references are correctly handled
- L757 _public prototype_ `void GatherInstancesAffectedByContainerPropertyChange(UObject* ModifiedObject, const void* OriginalContainerAddr, EPropertyArrayChangeType::Type ChangeType, TArray<UObject*>& OutAffectedInstances);` — Gather the list of all instances that will be affected by a container property change @param	ModifiedObject				Object which property has been modified @param	OriginalContainerAddr		Original address holding the container value before the modification @param	ChangeType					In which way is the container modified @param	OutAffectedInstances		Instances affected by the property change
- L768 _public prototype_ `void PropagateContainerPropertyChange(UObject* ModifiedObject, const void* OriginalContainerAddr, const TArray<UObject*>& AffectedInstances, EPropertyArrayChangeType::Type ChangeType, int32 Index, int32 SwapIndex = INDEX_NONE);` — Propagates the property change of a container property to the provided archetype instances @param	ModifiedObject				Object which property has been modified @param	OriginalContainerAddr		Original address holding the container value before the modification @param	AffectedInstances			Instances affected by the property change @param	ChangeType					In which way was the container modified @param	Index						Index of the modified item
- L772 _public prototype_ `DECLARE_EVENT(FPropertyNode, FPropertyValueChangedEvent);` — Broadcasts when a property value changes
- L774 _public function_ `DECLARE_MULTICAST_DELEGATE_OneParam(FPropertyValueChangedWithData, const FPropertyChangedEvent&) FPropertyValueChangedEvent& OnPropertyValueChanged()` — Broadcasts when a property value changes, but additionally includes the property changed event.
- L776 _public function_ `FPropertyValueChangedWithData& OnPropertyValueChangedWithData()`
- L779 _public function_ `FPropertyValueChangedEvent& OnChildPropertyValueChanged()` — Broadcasts when a child of this property changes
- L780 _public function_ `FPropertyValueChangedWithData& OnChildPropertyValueChangedWithData()`
- L783 _public prototype_ `DECLARE_EVENT(FPropertyNode, FPropertyValuePreChangeEvent);` — Broadcasts when a property value changes
- L784 _public function_ `FPropertyValuePreChangeEvent& OnPropertyValuePreChange()`
- L787 _public function_ `FPropertyValuePreChangeEvent& OnChildPropertyValuePreChange()` — Broadcasts when a child of this property changes
- L790 _public prototype_ `DECLARE_EVENT(FPropertyNode, FPropertyResetToDefaultEvent);` — Broadcasts when this property is reset to default
- L791 _public function_ `FPropertyResetToDefaultEvent& OnPropertyResetToDefault()`
- L797 _public function_ `FCanPropertyItemChange& OnCanItemChangeEvent()` — Broadcasts before an item in a container is being mutated, giving it a chance to back out. If an error occurs, it's sent by ChangeBlockedEvent.
- L800 _public function_ `FPropertyChangeBlocked& OnChangeBlockedEvent()` — Broadcasts before an item in a container is being mutated, giving it a chance to back out
- L809 _public prototype_ `void FilterNodes(const TArray<FString>& InFilterStrings, const bool bParentSeenDueToFiltering = false);` — Marks window's seem due to filtering flags @param InFilterStrings	- List of strings that must be in the property name in order to display Empty InFilterStrings means display as normal All strings must match in order to be accepted by the filter @param bParentAllowsVisible - is NOT true for an expander that is NOT expanded
- L816 _public prototype_ `void ProcessSeenFlags(const bool bParentAllowsVisible);` — Marks windows as visible based on the filter strings or standard visibility @param bParentAllowsVisible - is NOT true for an expander that is NOT expanded
- L821 _public prototype_ `void ProcessSeenFlagsForFavorites();` — Marks windows as visible based their favorites status
- L826 _public function_ `bool IsVisible() const` — @return true if this node should be visible in a tree
- L828 _public function_ `static TSharedRef< FPropertyPath > CreatePropertyPath(const TSharedRef< FPropertyNode >& PropertyNode)`
- L867 _public function_ `static TSharedPtr< FPropertyNode > FindPropertyNodeByPath(const TSharedPtr< FPropertyPath > Path, const TSharedRef< FPropertyNode >& StartingNode)`
- L916 _public function_ `static TArray< FPropertyInfo > GetPossibleExtensionsForPath(const TSharedPtr< FPropertyPath > Path, const TSharedRef< FPropertyNode >& StartingNode)`
- L956 _public prototype_ `static UObject* GetArchetype(const UObject* Object);`
- L958 _public prototype_ `static void RegisterArchetypePolicy(PropertyEditorPolicy::IArchetypePolicy* ArchetypePolicy);`
- L959 _public prototype_ `static void UnregisterArchetypePolicy(PropertyEditorPolicy::IArchetypePolicy* ArchetypePolicy);`
- L961 _public prototype_ `static void RegisterEditConstPolicy(PropertyEditorPolicy::IEditConstPolicy* EditConstPolicy);`
- L962 _public prototype_ `static void UnregisterEditConstPolicy(PropertyEditorPolicy::IEditConstPolicy* EditConstPolicy);`
- L964 _public prototype_ `static bool IsPropertyEditConst(const FEditPropertyChain& PropertyChain, UObject* Object);`
- L966 _public prototype_ `static bool IsPropertyEditConst(const FProperty* Property, UObject* Object);`
- L972 _public prototype_ `virtual void AddRestriction(TSharedRef<const FPropertyRestriction> Restriction);` — Adds a restriction to the possible values for this property. @param Restriction	The restriction being added to this property.
- L979 _public function_ `bool IsHidden(const FString& Value) const` — Tests if a value is hidden for this property @param Value			The value to test for being hidden. @return				True if this value is hidden.
- L989 _public function_ `bool IsDisabled(const FString& Value) const` — Tests if a value is disabled for this property @param Value			The value to test for being disabled. @return				True if this value is disabled.
- L994 _public function_ `bool IsRestricted(const FString& Value) const`
- L1005 _public prototype_ `virtual bool IsHidden(const FString& Value, TArray<FText>* OutReasons) const;` — Tests if a value is hidden for this property. @param Value			The value to test for being hidden. @param OutReasons		If hidden, the reasons why. @return				True if this value is hidden.
- L1013 _public prototype_ `virtual bool IsDisabled(const FString& Value, TArray<FText>* OutReasons) const;` — Tests if a value is disabled for this property. @param Value			The value to test for being disabled. @param OutReasons	If disabled, the reasons why. @return				True if this value is disabled.
- L1021 _public prototype_ `bool IsRestricted(const FString& Value, TArray<FText>& OutReasons) const;` — Tests if a value is restricted for this property. @param Value			The value to test for being restricted. @param OutReasons		If restricted, the reasons why. @return				True if this value is restricted.
- L1029 _public prototype_ `virtual bool GenerateRestrictionToolTip(const FString& Value, FText& OutTooltip)const;` — Generates a consistent tooltip describing this restriction for use in the editor. @param Value			The value to test for restriction and generate the tooltip from. @param OutTooltip	The tooltip describing why this value is restricted. @return				True if this value is restricted.
- L1031 _public function_ `const TArray<TSharedRef<const FPropertyRestriction>>& GetRestrictions() const`
- L1036 _public prototype_ `FPropertyChangedEvent& FixPropertiesInEvent(FPropertyChangedEvent& Event);`
- L1039 _public prototype_ `void SetInstanceMetaData(const FName& Key, const FString& Value);` — Set metadata value for 'Key' to 'Value' on this property instance (as opposed to the class)
- L1046 _public prototype_ `const FString* GetInstanceMetaData(const FName& Key) const;` — Get metadata value for 'Key' for this property instance (as opposed to the class) @return Pointer to metadata value; nullptr if Key not found
- L1053 _public prototype_ `const TMap<FName, FString>* GetInstanceMetaDataMap() const;` — Get metadata map for this property instance (as opposed to the class) @return Map ptr containing metadata pairs
- L1055 _public prototype_ `bool ParentOrSelfHasMetaData(const FName& MetaDataKey) const;`
- L1060 _public prototype_ `FProperty* GetMetaDataProperty();` — Gets the property we should use to read meta-data
- L1065 _public prototype_ `void InvalidateCachedState();` — Invalidates the cached state of this node in all children;
- L1067 _public function_ `static void SetupKeyValueNodePair( TSharedPtr<FPropertyNode>& KeyNode, TSharedPtr<FPropertyNode>& ValueNode )`
- L1075 _public function_ `TSharedPtr<FPropertyNode>& GetPropertyKeyNode()`
- L1077 _public function_ `const TSharedPtr<FPropertyNode>& GetPropertyKeyNode() const`
- L1082 _public prototype_ `FString GetDefaultValueAsString(bool bUseDisplayName = true);` — Gets the default value of the property as string.
- L1087 _public prototype_ `void BroadcastPropertyResetToDefault();` — Broadcasts reset to default property changes
- L1090 _public prototype_ `bool SupportsEditConditionToggle() const;` — @return Whether this property should have an edit condition toggle.
- L1093 _public prototype_ `void ToggleEditConditionState();` — Toggle the current state of the edit condition if this SupportsEditConditionToggle()
- L1096 _public prototype_ `bool HasEditCondition() const;` — @return Whether the property has a condition which must be met before allowing editing of it's value
- L1099 _public prototype_ `bool IsEditConditionMet() const;` — @return Whether the condition has been met to allow editing of this property's value
- L1102 _public prototype_ `bool IsOnlyVisibleWhenEditConditionMet() const;` — @return Whether this property derives its visibility from its edit condition
- L1108 _public prototype_ `void GetExpandedChildPropertyPaths(TSet<FString>& OutExpandedChildPropertyPaths) const;` — Helper to fetch a list of child property nodes that are expanded
- L1113 _public prototype_ `void SetExpandedChildPropertyNodes(const TSet<FString>& InNodesToExpand);` — Helper to set the expansion state of a list of child property nodes
- L1118 _public function_ `const FString& GetPropertyPath() const` — Helper to fetch a PropertyPath
- L1121 _public prototype_ `void SetIgnoreInstancedReference();` — Marks this property node as ignoring CPF_InstancedReference
- L1124 _public prototype_ `bool IsIgnoringInstancedReference() const;` — Queries whether the node would like to ignore CPF_InstancedReference semantics
- L1127 _public prototype_ `bool IsDestroyed() const;` — Return true if DestroyTree() has been called on this node.
- L1132 _public prototype_ `void MarkDestroyedRecursive();` — Sets bIsDestroyed on all nodes within the hierarchy
- L1134 _public prototype_ `TSharedRef<FEditPropertyChain> BuildPropertyChain( FProperty* PropertyAboutToChange ) const;`
- L1137 _protected prototype_ `TSharedRef<FEditPropertyChain> BuildPropertyChain( FProperty* PropertyAboutToChange, const TSet<UObject*>& InAffectedArchetypeInstances ) const;`
- L1138 _protected prototype_ `TSharedRef<FEditPropertyChain> BuildPropertyChain( FProperty* PropertyAboutToChange, TSet<UObject*>&& InAffectedArchetypeInstances ) const;`
- L1140 _protected prototype_ `void NotifyPreChangeInternal(TSharedRef<FEditPropertyChain> PropertyChain, FProperty* PropertyAboutToChange, FNotifyHook* InNotifyHook);`
- L1145 _protected prototype_ `void DestroyTree(const bool bInDestroySelf=true);` — Destroys all node within the hierarchy
- L1150 _protected function_ `virtual void InitBeforeNodeFlags()` — Interface function for Custom Setup of Node (prior to node flags being set)
- L1155 _protected function_ `virtual void InitExpansionFlags()` — Interface function for Custom expansion Flags.  Default is objects and categories which always expand
- L1160 _protected prototype_ `virtual void InitChildNodes() = 0;` — Interface function for Creating Child Nodes
- L1165 _protected prototype_ `bool IsFilterAcceptable(const TArray<FString>& InAcceptableNames, const TArray<FString>& InFilterStrings);` — Does the string compares to ensure this Name is acceptable to the filter that is passed in
- L1169 _protected prototype_ `void ExpandParent( bool bInRecursive );` — Make sure that parent nodes are expanded
- L1172 _protected function_ `FProperty* GetStoredProperty()` — @return		The property stored at this node, to be passed to Pre/PostEditChange.
- L1174 _protected prototype_ `bool GetDiffersFromDefault(const uint8* PropertyValueAddress, const uint8* PropertyDefaultAddress, const uint8* DefaultPropertyValueBaseAddress, const FProperty* InProperty, const UObject* TopLevelObject) const;`
- L1175 _protected prototype_ `bool GetDiffersFromDefaultForObject( FPropertyItemValueDataTrackerSlate& ValueTracker, FProperty* InProperty );`
- L1183 _protected prototype_ `FString GetDefaultValueAsString(const uint8* PropertyDefaultAddress, const FProperty* InProperty, EValueAsStringMode Mode, const UObject* TopLevelObject) const;`
- L1184 _protected prototype_ `FString GetDefaultValueAsStringForObject( FPropertyItemValueDataTrackerSlate& ValueTracker, UObject* InObject, FProperty* InProperty, EValueAsStringMode Mode);`
- L1193 _protected prototype_ `bool AdjustEnumPropDisplayName(UEnum* InEnum, FString& DisplayName) const;` — Helper function to obtain the display name for an enum property @param InEnum		The enum whose metadata to pull from @param DisplayName	The name of the enum value to adjust @return	true if the DisplayName has been changed
- L1199 _protected prototype_ `void BroadcastPropertyChangedDelegates();` — Helper function for derived members to be able to broadcast property changed notifications
- L1205 _protected prototype_ `void BroadcastPropertyChangedDelegates(const FPropertyChangedEvent& Event);` — Helper function for derived members to be able to broadcast property changed notifications including property changed event data
- L1212 _protected prototype_ `void BroadcastPropertyPreChangeDelegates();` — Helper function for derived members to be able to broadcast property pre-change notifications
- L1220 _protected prototype_ `TSharedPtr< FPropertyItemValueDataTrackerSlate > GetValueTracker( UObject* Object, uint32 ObjIndex );` — Gets a value tracker for the default of this property in the passed in object @param Object	The object to get the value for @param ObjIndex	The index of the object in the parent property node's object array (for caching)
- L1225 _protected prototype_ `void UpdateEditConstState();` — Updates and caches the current edit const state of this property
- L1232 _protected prototype_ `static bool DoesChildPropertyRequireValidation(FProperty* InChildProp);` — Checks to see if the supplied property of a child node requires validation @param	InChildProp		The property of the child node @return	True if the property requires validation, false otherwise
- L1236 _protected member_ `static FEditConditionParser EditConditionParser;`
- L1241 _protected member_ `TWeakPtr<FPropertyNode> ParentNodeWeakPtr;` — The node that is the parent of this node or nullptr for the root
- L1244 _protected member_ `TSharedPtr<FPropertyNode> PropertyKeyNode;` — The property node, if any, that serves as the key value for this node
- L1247 _protected member_ `mutable FReadAddressListData CachedReadAddresses;` — Cached read addresses for this property node
- L1250 _protected member_ `TArray< TSharedPtr<FPropertyItemValueDataTrackerSlate> > ObjectDefaultValueTrackers;` — List of per object default value trackers associated with this property node
- L1253 _protected member_ `TArray< TSharedPtr<FPropertyNode> > ChildNodes;` — List of all child nodes this node is responsible for
- L1256 _protected member_ `FPropertyChildrenRebuiltEvent OnRebuildChildrenEvent;` — Called when this node's children are rebuilt
- L1259 _protected member_ `FPropertyValuePreChangeEvent PropertyValuePreChangeEvent;` — Called when this node's property value is about to change (called during NotifyPreChange)
- L1262 _protected member_ `FPropertyValuePreChangeEvent ChildPropertyValuePreChangeEvent;` — Called when a child's property value is about to change
- L1265 _protected member_ `FPropertyValueChangedEvent PropertyValueChangedEvent;` — Called when this node's property value has changed (called during NotifyPostChange)
- L1267 _protected member_ `FPropertyValueChangedWithData PropertyValueChangedDelegate;` — Called when this node's property value has changed with the property changed event data as payload (called during NotifyPostChange)
- L1270 _protected member_ `FPropertyValueChangedEvent ChildPropertyValueChangedEvent;` — Called when a child's property value has changed
- L1272 _protected member_ `FPropertyValueChangedWithData ChildPropertyValueChangedDelegate;` — Called when a child's property value has changed with the property changed event data as payload
- L1275 _protected member_ `FPropertyResetToDefaultEvent PropertyResetToDefaultEvent;` — Called when the property is reset to default
- L1278 _protected member_ `FCanPropertyItemChange CanItemChangeEvent;` — Called before a container element is changed
- L1281 _protected member_ `FPropertyChangeBlocked ChangeBlockedEvent;` — Called when an attempted property change has been disallowed
- L1284 _protected member_ `TWeakFieldPtr<FProperty> Property;` — The property being displayed/edited.
- L1287 _protected member_ `int32 ArrayOffset;` — Offset to the property data within either a fixed array or a dynamic array
- L1290 _protected member_ `int32 ArrayIndex;` — The index of the property if it is inside an array, set, or map (internally, we'll use set/map helpers that store element indices in an array)
- L1297 _protected member_ `int32 MaxChildDepthAllowed;` — Safety Value representing Depth in the property tree used to stop diabolical topology cases -1 = No limit on children 0 = No more children are allowed.  Do not process child nodes >0 = A limit has been set by the property and will tick down for successive children
- L1302 _protected member_ `EPropertyNodeFlags::Type PropertyNodeFlags;` — Used for flags to determine if the node is seen (if not seen and never been created, don't create it on display)
- L1305 _protected member_ `bool bRebuildChildrenRequested;` — If true, children of this node will be rebuilt next tick.
- L1308 _protected member_ `bool bChildrenRebuilt;` — Set to true when RebuildChildren is called on the node
- L1311 _protected member_ `bool bIgnoreInstancedReference;` — Set to true when we want to ignore CPF_InstancedReference
- L1314 _protected member_ `bool bIsDestroyed = false;` — If true, DestroyTree() has been called on the node.
- L1317 _protected member_ `TArray<TSharedRef<const FPropertyRestriction>> Restrictions;` — An array of restrictions limiting this property's potential values in property editors.
- L1320 _protected member_ `TWeakPtr<FDetailTreeNode> TreeNode;` — Optional reference to a tree node that is displaying this property
- L1326 _protected member_ `TMap<FName, FString> InstanceMetaData;` — Stores metadata for this instance of the property (in contrast to regular metadata, which is stored per-class)
- L1331 _protected member_ `FString PropertyPath;` — The property path for this property
- L1334 _protected member_ `TSharedPtr<FEditConditionExpression> EditConditionExpression;` — Edit condition expression used to determine if this property editor can modify its property
- L1335 _protected member_ `TSharedPtr<FEditConditionContext> EditConditionContext;`
- L1341 _protected member_ `mutable bool bIsEditConst;` — Cached state of flags that are expensive to update These update when values are changed in the details panel
- L1342 _protected member_ `mutable bool bIsEditConstWithoutCondition;` — Ignores EditCondition state
- L1343 _protected member_ `mutable bool bUpdateEditConstState;`
- L1344 _protected member_ `mutable int32 UpdateEditConstStateEpoch;`
- L1345 _protected member_ `mutable bool bDiffersFromDefault;`
- L1346 _protected member_ `mutable bool bUpdateDiffersFromDefault;`
- L1347 _protected member_ `mutable int32 UpdateDiffersFromDefaultEpoch;`

#### enum `FPropertyNode::EValueAsStringMode`  
`enum class EValueAsStringMode`  
_L1177-1182_
- L1179 _public enumerator_ `None`
- L1180 _public enumerator_ `UseDisplayName`
- L1181 _public enumerator_ `ForDiff`

#### class `FComplexPropertyNode`  
`class FComplexPropertyNode : public FPropertyNode`  
_L1350-1397_
- inherits: `FPropertyNode`
- L1360 _public function_ `FComplexPropertyNode() : FPropertyNode()`
- L1361 _public prototype_ `virtual ~FComplexPropertyNode() = default;`
- L1363 _public function_ `virtual FComplexPropertyNode* AsComplexNode() override`
- L1364 _public function_ `virtual const FComplexPropertyNode* AsComplexNode() const override`
- L1366 _public function_ `virtual FStructurePropertyNode* AsStructureNode()`
- L1367 _public function_ `virtual const FStructurePropertyNode* AsStructureNode() const`
- L1369 _public prototype_ `virtual void SetDisplayNameOverride(const FText& InDisplayNameOverride) override;`
- L1370 _public prototype_ `virtual FText GetDisplayName() const override;`
- L1372 _public prototype_ `virtual UStruct* GetBaseStructure() = 0;`
- L1373 _public prototype_ `virtual const UStruct* GetBaseStructure() const = 0;`
- L1376 _public prototype_ `virtual TArray<UStruct*> GetAllStructures() = 0;` — Returns the base struct as well as any sidecar data structs
- L1377 _public prototype_ `virtual TArray<const UStruct*> GetAllStructures() const = 0;`
- L1379 _public prototype_ `virtual int32 GetInstancesNum() const = 0;`
- L1380 _public prototype_ `virtual uint8* GetMemoryOfInstance(int32 Index) const = 0;`
- L1385 _public prototype_ `virtual uint8* GetValuePtrOfInstance(int32 Index, const FProperty* InProperty, const FPropertyNode* InParentNode) const = 0;` — Returns a pointer to the stored value of InProperty on InParentNode's Index'th instance.
- L1386 _public prototype_ `virtual TWeakObjectPtr<UObject> GetInstanceAsUObject(int32 Index) const = 0;`
- L1387 _public prototype_ `virtual EPropertyType GetPropertyType() const = 0;`
- L1389 _public prototype_ `virtual void Disconnect() = 0;`
- L1392 _public prototype_ `virtual TSharedPtr<FPropertyNode> GenerateSingleChild(FName ChildPropertyName) = 0;` — Generates a single child from the provided property name.  Any existing children are destroyed
- L1396 _private member_ `FText DisplayNameOverride;` — Display name to use instead of the fully qualified name

#### enum `FComplexPropertyNode::EPropertyType`  
`enum EPropertyType`  
_L1354-1358_
- L1356 _public enumerator_ `EPT_Object`
- L1357 _public enumerator_ `EPT_StandaloneStructure`

#### Free symbols / members of external scopes

- L25 _namespace_ `namespace PropertyEditorPolicy`
- L31 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPropertyNode, Log, All);`
- L31 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPropertyNode, Log, All);`
- L33 _namespace_ `namespace EPropertyNodeFlags`
- L35 _typedef_ `typedef uint32 Type;` (scope `EPropertyNodeFlags`)
- L37 _variable_ `inline const Type IsSeen = 1 << 0;` (scope `EPropertyNodeFlags`)
- L38 _variable_ `inline const Type IsSeenDueToFiltering = 1 << 1;` (scope `EPropertyNodeFlags`) — inline const Type	IsSeen							= 1 << 0;	  true if this node can be seen based on current parent expansion.  Does not take into account clipping
- L39 _variable_ `inline const Type IsSeenDueToChildFiltering = 1 << 2;` (scope `EPropertyNodeFlags`) — inline const Type	IsSeenDueToFiltering			= 1 << 1;	  true if this node has been accepted by the filter
- L40 _variable_ `inline const Type IsParentSeenDueToFiltering = 1 << 3;` (scope `EPropertyNodeFlags`) — inline const Type	IsSeenDueToChildFiltering		= 1 << 2;	  true if this node or one of it's children is seen due to filtering.  It will then be forced on as well.
- L41 _variable_ `inline const Type IsSeenDueToChildFavorite = 1 << 4;` (scope `EPropertyNodeFlags`) — inline const Type	IsParentSeenDueToFiltering		= 1 << 3;	  True if the parent was visible due to filtering
- L43 _variable_ `inline const Type Expanded = 1 << 5;` (scope `EPropertyNodeFlags`)
- L44 _variable_ `inline const Type CanBeExpanded = 1 << 6;` (scope `EPropertyNodeFlags`) — inline const Type	Expanded						= 1 << 5;	  true if this node should display its children
- L46 _variable_ `inline const Type EditInlineNew = 1 << 7;` (scope `EPropertyNodeFlags`)
- L48 _variable_ `inline const Type SingleSelectOnly = 1 << 8;` (scope `EPropertyNodeFlags`)
- L49 _variable_ `inline const Type ShowCategories = 1 << 9;` (scope `EPropertyNodeFlags`) — inline const Type	SingleSelectOnly				= 1 << 8;	  true if only a single object is selected.
- L51 _variable_ `inline const Type HasEverBeenExpanded = 1 << 10;` (scope `EPropertyNodeFlags`)
- L53 _variable_ `inline const Type IsBeingFiltered = 1 << 11;` (scope `EPropertyNodeFlags`)
- L55 _variable_ `inline const Type IsFavorite = 1 << 12;` (scope `EPropertyNodeFlags`)
- L57 _variable_ `inline const Type NoChildrenDueToCircularReference= 1 << 13;` (scope `EPropertyNodeFlags`)
- L59 _variable_ `inline const Type AutoExpanded = 1 << 14;` (scope `EPropertyNodeFlags`)
- L60 _variable_ `inline const Type ShouldShowHiddenProperties = 1 << 15;` (scope `EPropertyNodeFlags`) — inline const Type	AutoExpanded					= 1 << 14;	  true if this node was autoexpanded due to being filtered
- L61 _variable_ `inline const Type IsAdvanced = 1 << 16;` (scope `EPropertyNodeFlags`) — inline const Type	ShouldShowHiddenProperties		= 1 << 15;	  true if this node should all properties not just those with the correct flag(s) to be shown in the editor
- L62 _variable_ `inline const Type IsCustomized = 1 << 17;` (scope `EPropertyNodeFlags`) — inline const Type	IsAdvanced						= 1 << 16;	  true if the property node is advanced (i.e it only shows up in advanced sections)
- L64 _variable_ `inline const Type RequiresValidation = 1 << 18;` (scope `EPropertyNodeFlags`)
- L66 _variable_ `inline const Type ShouldShowDisableEditOnInstance = 1 << 19;` (scope `EPropertyNodeFlags`)
- L68 _variable_ `inline const Type IsReadOnly = 1 << 20;` (scope `EPropertyNodeFlags`)
- L70 _variable_ `inline const Type SkipChildValidation = 1 << 21;` (scope `EPropertyNodeFlags`)
- L72 _variable_ `inline const Type ShowInnerObjectProperties = 1 << 22;` (scope `EPropertyNodeFlags`)
- L74 _variable_ `inline const Type HasCustomResetToDefault = 1 << 23;` (scope `EPropertyNodeFlags`)
- L76 _variable_ `inline const Type IsSparseClassData = 1 << 24;` (scope `EPropertyNodeFlags`)
- L78 _variable_ `inline const Type ShouldShowInViewport = 1 << 25;` (scope `EPropertyNodeFlags`)
- L80 _variable_ `inline const Type ResolveInstanceDataObjects = 1 << 26;` (scope `EPropertyNodeFlags`)
- L82 _variable_ `inline const Type SupportsDynamicInstancing = 1 << 27;` (scope `EPropertyNodeFlags`)
- L84 _variable_ `inline const Type DynamicInstance = 1 << 28;` (scope `EPropertyNodeFlags`)
- L88 _variable_ `inline const Type NoFlags = 0;` (scope `EPropertyNodeFlags`)
- L92 _namespace_ `namespace FPropertyNodeConstants`
- L94 _variable_ `inline const int32 NoDepthRestrictions = -1;` (scope `FPropertyNodeConstants`)
- L97 _variable_ `inline const TCHAR CategoryDelimiterChar = TCHAR( '|' );` (scope `FPropertyNodeConstants`) — Character used to deliminate sub-categories in category path names
- L127 _enumerator_ `template<> struct TIsPODType<FAddressPair> { enum { Value = true }; }; struct FReadAddressListData { public: FReadAddressListData() : bAllValuesTheSame( false ) , bRequiresCache( true )` (scope `TIsPODType::__anonaef2c6720103`)
- L720 _delegate_ `DECLARE_EVENT(FPropertyNode, FPropertyChildrenRebuiltEvent);`
- L772 _delegate_ `DECLARE_EVENT(FPropertyNode, FPropertyValueChangedEvent);` — Broadcasts when a property value changes
- L774 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FPropertyValueChangedWithData, const FPropertyChangedEvent&) FPropertyValueChangedEvent& OnPropertyValueChanged() { return PropertyValueChangedEvent; } FPropertyValueChangedWithData& OnPropertyValueChangedWithData() { return PropertyValueChangedDelegate; } FPropertyValueChangedEvent& OnChildPropertyValueChanged() { return ChildPropertyValueChangedEvent; } FPropertyValueChangedWithData& OnChildPropertyValueChangedWithData() { return ChildPropertyValueChangedDelegate; } DECLARE_EVENT(FPropertyNode, FPropertyValuePreChangeEvent);` — Broadcasts when a property value changes, but additionally includes the property changed event.
- L783 _delegate_ `DECLARE_EVENT(FPropertyNode, FPropertyValuePreChangeEvent);` — Broadcasts when a property value changes
- L790 _delegate_ `DECLARE_EVENT(FPropertyNode, FPropertyResetToDefaultEvent);` — Broadcasts when this property is reset to default

### `Source/Editor/PropertyEditor/Private/PropertyRowGenerator.h` (Private)


#### struct `FPropertyNodeMap`  
`struct FPropertyNodeMap`  
_L25-46_
- L27 _public function_ `FPropertyNodeMap() : ParentProperty(NULL)`
- L32 _public member_ `FPropertyNode* ParentProperty;` — Object property node which contains the properties in the node map
- L35 _public member_ `TMap<FName, TSharedPtr<FPropertyNode> > PropertyNameToNode;` — Property name to property node map
- L37 _public function_ `bool Contains(FName PropertyName) const`
- L42 _public function_ `void Add(FName PropertyName, TSharedPtr<FPropertyNode>& PropertyNode)`

#### struct `FDetailLayoutData`  
`struct FDetailLayoutData`  
_L58-69_
- L60 _public member_ `TSharedPtr<FDetailLayoutBuilderImpl> DetailLayout;`
- L62 _public member_ `FClassToPropertyMap ClassToPropertyMap;`
- L65 _public member_ `TSet<TWeakObjectPtr<UStruct>> ClassesWithProperties;` — A  unique classes being viewed
- L68 _public member_ `TArray<TSharedPtr<IDetailCustomization>> CustomizationClassInstances;` — Customization class instances currently active in this view

#### class `FPropertyRowGenerator`  
`class FPropertyRowGenerator : public IPropertyRowGenerator, public FTickableEditorObject, public TSharedFromThis<FPropertyRowGenerator>`  
_L71-173_
- inherits: `IPropertyRowGenerator,FTickableEditorObject,TSharedFromThis<FPropertyRowGenerator>`
- L74 _public prototype_ `FPropertyRowGenerator(const FPropertyRowGeneratorArgs& InArgs);`
- L77 _public prototype_ `FPropertyRowGenerator(const FPropertyRowGeneratorArgs& InArgs, TSharedPtr<FAssetThumbnailPool> InThumbnailPool);` — `UE_DEPRECATED(5.0, "FPropertyRowGenerator which takes in a thumbnail pool parameter is no longer necessary.")`
- L79 _public prototype_ `~FPropertyRowGenerator();`
- L81 _public prototype_ `DECLARE_DERIVED_EVENT(FPropertyRowGenerator, IPropertyRowGenerator::FOnRowsRefreshed, FOnRowsRefreshed);`
- L84 _public prototype_ `virtual void SetObjects(const TArray<UObject*>& InObjects) override;` — IPropertyRowGenerator interface
- L85 _public prototype_ `virtual void SetStructure(const TSharedPtr<FStructOnScope>& InStruct) override;`
- L86 _public prototype_ `virtual void SetStructure(const TSharedPtr<IStructureDataProvider>& InStructProvider) override;`
- L87 _public function_ `virtual const TArray<TWeakObjectPtr<UObject>>& GetSelectedObjects() const override`
- L88 _public prototype_ `virtual const TArray<TSharedRef<IDetailTreeNode>>& GetRootTreeNodes() const override;`
- L89 _public prototype_ `virtual TSharedPtr<IDetailTreeNode> FindTreeNode(TSharedPtr<IPropertyHandle> PropertyHandle) const override;`
- L90 _public prototype_ `virtual TArray<TSharedPtr<IDetailTreeNode>> FindTreeNodes(const TArray<TSharedPtr<IPropertyHandle>>& PropertyHandles) const override;`
- L91 _public function_ `virtual FOnRowsRefreshed& OnRowsRefreshed() override`
- L92 _public prototype_ `virtual void RegisterInstancedCustomPropertyLayout(UStruct* Class, FOnGetDetailCustomizationInstance DetailLayoutDelegate) override;`
- L93 _public prototype_ `virtual void RegisterInstancedCustomPropertyTypeLayout(FName PropertyTypeName, FOnGetPropertyTypeCustomizationInstance PropertyTypeLayoutDelegate, TSharedPtr<IPropertyTypeIdentifier> Identifier = nullptr) override;`
- L94 _public prototype_ `virtual void UnregisterInstancedCustomPropertyLayout(UStruct* Class) override;`
- L95 _public prototype_ `virtual void UnregisterInstancedCustomPropertyTypeLayout(FName PropertyTypeName, TSharedPtr<IPropertyTypeIdentifier> Identifier = nullptr) override;`
- L96 _public function_ `virtual void SetCustomValidatePropertyNodesFunction(FOnValidatePropertyRowGeneratorNodes InCustomValidatePropertyNodesFunction) override`
- L101 _public prototype_ `virtual void SetPropertyGenerationAllowListPaths(const TSet<FString>& InPropertyGenerationAllowListPaths) override;` — This function sets property paths to generate PropertyNodes.This improves the performance for cases where PropertyView is only showing a few properties of the object by not generating all other PropertyNodes
- L102 _public prototype_ `virtual void InvalidateCachedState() override;`
- L103 _public prototype_ `virtual void FilterNodes(const TArray<FString>& InFilterStrings) override;`
- L106 _public function_ `virtual ETickableTickType GetTickableTickType() const override` — FTickableEditorObject interface
- L107 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L108 _public prototype_ `virtual TStatId GetStatId() const override;`
- L111 _public function_ `virtual class FNotifyHook* GetNotifyHook() const` — IPropertyUtilities interface
- L112 _public prototype_ `virtual void EnqueueDeferredAction(FSimpleDelegate DeferredAction);`
- L113 _public prototype_ `virtual bool IsPropertyEditingEnabled() const;`
- L114 _public prototype_ `virtual void ForceRefresh();`
- L115 _public function_ `virtual void RequestRefresh()`
- L116 _public prototype_ `virtual TSharedPtr<class FAssetThumbnailPool> GetThumbnailPool() const;`
- L117 _public function_ `virtual bool HasClassDefaultObject() const`
- L118 _public prototype_ `virtual const TArray<TSharedRef<class IClassViewerFilter>>& GetClassViewerFilters() const;`
- L120 _public prototype_ `const FCustomPropertyTypeLayoutMap& GetInstancedPropertyTypeLayoutMap() const;`
- L121 _public prototype_ `void UpdateDetailRows();`
- L122 _public function_ `virtual FOnNotifyStartedChangingProperties& OnNotifyStartedChangingProperties() override`
- L123 _public function_ `virtual FOnFinishedChangingProperties& OnFinishedChangingProperties() override`
- L126 _private prototype_ `void PreSetObject(int32 NumNewObjects, bool bHasStructRoots);`
- L127 _private prototype_ `void PostSetObject();`
- L128 _private prototype_ `void UpdatePropertyMaps();`
- L129 _private prototype_ `void UpdateSinglePropertyMap(TSharedPtr<FComplexPropertyNode> InRootPropertyNode, FDetailLayoutData& LayoutData);`
- L130 _private prototype_ `bool ValidatePropertyNodes(const FRootPropertyNodeList& PropertyNodeList);`
- L131 _private prototype_ `TSharedPtr<IDetailTreeNode> FindTreeNodeRecursive(const TSharedPtr<IDetailTreeNode>& StartNode, TSharedPtr<IPropertyHandle> PropertyHandle) const;`
- L132 _private prototype_ `void LayoutNodeVisibilityChanged();`
- L135 _private member_ `const FPropertyRowGeneratorArgs Args;`
- L137 _private member_ `FRootPropertyNodeList RootPropertyNodes;` — The root property nodes of the property tree for a specific set of UObjects
- L139 _private member_ `FRootPropertyNodeList RootNodesPendingKill;` — Root tree nodes that needs to be destroyed when safe
- L141 _private member_ `TArray<TSharedRef<IDetailTreeNode>> RootTreeNodes;` — Root tree nodes visible in the tree
- L143 _private member_ `TArray<FDetailLayoutData> DetailLayouts;` — The current detail layout based on objects in this details panel.  There is one layout for each top level object node.
- L145 _private member_ `TArray<TSharedPtr<IDetailCustomization>> CustomizationClassInstancesPendingDelete;` — Customization instances that need to be destroyed when safe to do so
- L147 _private member_ `TArray<FSimpleDelegate> DeferredActions;` — Actions that should be executed next tick
- L149 _private member_ `TArray<TWeakObjectPtr<UObject>> SelectedObjects;` — Currently viewed objects
- L151 _private member_ `FOnRowsRefreshed RowsRefreshedDelegate;` — Delegate to call when the user of this generator needs to know the rows are invalid
- L153 _private member_ `FCustomPropertyTypeLayoutMap InstancedTypeToLayoutMap;` — A mapping of type names to detail layout delegates, called when querying for custom detail layouts in this instance of the details view only
- L155 _private member_ `FCustomDetailLayoutMap InstancedClassToDetailLayoutMap;` — A mapping of classes to detail layout delegates, called when querying for custom detail layouts in this instance of the details view only
- L157 _private member_ `TSharedRef<IPropertyUtilities> PropertyUtilities;` — Utility class for accessing commonly used helper methods from customizations
- L159 _private member_ `TSharedRef<IPropertyGenerationUtilities> PropertyGenerationUtilities;` — Utility class for accessing internal helper methods
- L161 _private member_ `FOnFinishedChangingProperties OnFinishedChangingPropertiesDelegate;` — Delegate called when the details panel finishes editing a property (after post edit change is called)
- L163 _private member_ `FOnNotifyStartedChangingProperties OnNotifyStartedChangingPropertiesDelegate;` — Delegate called before the details panel finishes editing a property (after pre edit change is called)
- L165 _private member_ `FOnValidatePropertyRowGeneratorNodes CustomValidatePropertyNodesFunction;` — The ValidatePropertyNodes function can be overridden with this member, if set. Useful if your implementation doesn't require this kind of validation each Tick.
- L167 _private member_ `TSet<FString> PropertyGenerationAllowListPaths;` — If specified only nodes for these properties will be generated
- L169 _private member_ `FDetailFilter CurrentFilter;` — Filter to apply on generated rows nodes
- L171 _private member_ `bool bViewingClassDefaultObject = false;`
- L172 _private member_ `bool bRefreshPending = false;`

#### Free symbols / members of external scopes

- L50 _typedef_ `typedef TMap<FName, TSharedPtr<FDetailCategoryImpl> > FCategoryMap;` — Mapping of categories to all top level item property nodes in that category
- L53 _typedef_ `typedef TMap<FName, FPropertyNodeMap> FClassInstanceToPropertyMap;` — Class to properties in that class
- L56 _typedef_ `typedef TMap<FName, FClassInstanceToPropertyMap> FClassToPropertyMap;` — Class to properties in that class
- L81 _delegate_ `DECLARE_DERIVED_EVENT(FPropertyRowGenerator, IPropertyRowGenerator::FOnRowsRefreshed, FOnRowsRefreshed);`

### `Source/Editor/PropertyEditor/Private/PropertyTextUtilities.h` (Private)


#### class `FPropertyTextUtilities`  
`class FPropertyTextUtilities`  
_L14-21_
- L17 _public prototype_ `static void PropertyToTextHelper(FString& OutString, const FPropertyNode* InPropertyNode, const FProperty* Property, const uint8* ValueAddress, UObject* Object, EPropertyPortFlags PortFlags);`
- L18 _public prototype_ `static void PropertyToTextHelper(FString& OutString, const FPropertyNode* InPropertyNode, const FProperty* Property, const FObjectBaseAddress& ObjectAddress, EPropertyPortFlags PortFlags);`
- L19 _public prototype_ `static void TextToPropertyHelper(const TCHAR* Buffer, const FPropertyNode* InPropertyNode, const FProperty* Property, uint8* ValueAddress, UObject* Object, EPropertyPortFlags PortFlags = PPF_None);`
- L20 _public prototype_ `static void TextToPropertyHelper(const TCHAR* Buffer, const FPropertyNode* InPropertyNode, const FProperty* Property, const FObjectBaseAddress& ObjectAddress, EPropertyPortFlags PortFlags = PPF_None);`

### `Source/Editor/PropertyEditor/Private/SConstrainedBox.h` (Private)


#### class `SConstrainedBox`  
`class SConstrainedBox : public SCompoundWidget`  
_L14-32_
- inherits: `SCompoundWidget`
- L17 _public function_ `SLATE_BEGIN_ARGS(SConstrainedBox) : _MinWidth() , _MaxWidth()`
- L21 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_ATTRIBUTE(TOptional<float>, MinWidth) SLATE_ATTRIBUTE(TOptional<float>, MaxWidth) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L27 _public prototype_ `virtual FVector2D ComputeDesiredSize(float LayoutScaleMultiplier) const override;`
- L30 _private member_ `TAttribute< TOptional<float> > MinWidth;`
- L31 _private member_ `TAttribute< TOptional<float> > MaxWidth;`

### `Source/Editor/PropertyEditor/Private/SDetailCategoryTableRow.h` (Private)


#### class `SDetailCategoryTableRow`  
`class SDetailCategoryTableRow : public SDetailTableRowBase`  
_L16-118_
- inherits: `SDetailTableRowBase`
- L19 _public function_ `SLATE_BEGIN_ARGS(SDetailCategoryTableRow) : _InnerCategory(false) , _WholeRowHeaderContent(false) , _ShowBorder(true) , _ShowHeader(true) , _IsEmpty(false) , _Objects(nullptr)`
- L27 _public prototype_ `SLATE_ARGUMENT(FText, DisplayName) SLATE_ARGUMENT(bool, InnerCategory) SLATE_ARGUMENT(TSharedPtr<SWidget>, HeaderContent) SLATE_ARGUMENT(bool, WholeRowHeaderContent) SLATE_ARGUMENT(bool, ShowBorder) SLATE_ARGUMENT(bool, ShowHeader) SLATE_ARGUMENT(bool, IsEmpty) SLATE_ARGUMENT(TSharedPtr<FOnPasteFromText>, PasteFromText) SLATE_ARGUMENT(TSharedPtr<FOnCopyToText>, CopyToText) SLATE_ARGUMENT(TArray<TWeakObjectPtr<UObject>>*, Objects) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FDetailTreeNode> InOwnerTreeNode, const TSharedRef<STableViewBase>& InOwnerTableView);`
- L45 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L50 _protected prototype_ `virtual void PopulateContextMenu(UToolMenu* ToolMenu) override;`
- L51 _protected prototype_ `virtual bool CanFavoriteRow(bool bInAddToFavorite) override;`
- L52 _protected prototype_ `virtual void OnFavoriteRow(bool bInAddToFavorite) override;`
- L57 _private prototype_ `void ForEachImmediateChildPropertyNode(TFunctionRef<bool(TSharedPtr<FPropertyNode>&)> InFunctor);` — Process immediate children property nodes of this category, return false to break
- L59 _private prototype_ `EVisibility IsSeparatorVisible() const;`
- L64 _private prototype_ `const FSlateBrush* GetBackgroundImage() const;` — Gets the @code const FSlateBrush* @endcode which holds the background image for the Category Row, minus the ScrollBar Well
- L69 _private prototype_ `const FSlateBrush* GetBackgroundImageForScrollBarWell() const;` — Gets the @code const FSlateBrush* @endcode which holds the background image for the ScrollBar Well
- L70 _private prototype_ `FSlateColor GetInnerBackgroundColor() const;`
- L71 _private prototype_ `FSlateColor GetOuterBackgroundColor() const;`
- L73 _private prototype_ `void OnCopyCategory();`
- L74 _private prototype_ `bool CanCopyCategory() const;`
- L75 _private prototype_ `void OnPasteCategory();`
- L76 _private prototype_ `bool CanPasteCategory();`
- L77 _private prototype_ `void OnResetToDefaultCategory();`
- L78 _private prototype_ `bool CanResetToDefaultCategory() const;`
- L80 _private prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L81 _private prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L85 _private member_ `FText DisplayName;` — Cached category name.
- L91 _private member_ `const FDetailsViewStyle* DetailsViewStyle = nullptr;` — The style of the details view. This holds information and methods to get things like the row border image, table padding, and so forth.
- L94 _private member_ `UE::PropertyEditor::Internal::FClipboardData PreviousClipboardData;` — Previously parsed clipboard data.
- L96 _private member_ `bool bIsInnerCategory = false;`
- L97 _private member_ `bool bShowBorder = false;`
- L98 _private member_ `bool bShowHeader = true;`
- L104 _private member_ `bool bIsEmpty = false;` — If true, this Category should have no UProperty data associated with it, and will be shown as an empty stub with no expansion arrow
- L106 _private member_ `FUIAction CopyAction;`
- L107 _private member_ `FUIAction PasteAction;`
- L108 _private member_ `FUIAction ResetToDefault;`
- L111 _private member_ `TSharedPtr<FOnPasteFromText> OnPasteFromTextDelegate;` — Delegate handling pasting an optionally tagged text snippet
- L114 _private member_ `TSharedPtr<FOnCopyToText> OnCopyToTextDelegate;` — Delegate handling pasting an optionally tagged text snippet
- L117 _private member_ `FCurveSequence PulseAnimation;` — Animation curve for displaying pulse

### `Source/Editor/PropertyEditor/Private/SDetailExpanderArrow.h` (Private)


#### class `SDetailExpanderArrow`  
`class SDetailExpanderArrow : public SCompoundWidget`  
_L11-28_
- inherits: `SCompoundWidget`
- L14 _public function_ `SLATE_BEGIN_ARGS(SDetailExpanderArrow)`
- L15 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<SDetailTableRowBase> DetailsRow);`
- L21 _private prototype_ `EVisibility GetExpanderVisibility() const;`
- L22 _private prototype_ `const FSlateBrush* GetExpanderImage() const;`
- L23 _private prototype_ `FReply OnExpanderClicked();`
- L26 _private member_ `TWeakPtr<SDetailTableRowBase> Row;`
- L27 _private member_ `TSharedPtr<SButton> ExpanderArrow;`

### `Source/Editor/PropertyEditor/Private/SDetailNameArea.h` (Private)


#### class `SDetailNameArea`  
`class SDetailNameArea : public SCompoundWidget`  
_L20-66_
- inherits: `SCompoundWidget`
- desc: Displays the name area which is not recreated when the detail view is refreshed
- L23 _public function_ `SLATE_BEGIN_ARGS( SDetailNameArea )`
- L24 _public prototype_ `SLATE_EVENT( FOnClicked, OnLockButtonClicked ) SLATE_ARGUMENT( bool, ShowLockButton ) SLATE_ARGUMENT( bool, ShowObjectLabel ) SLATE_ATTRIBUTE( bool, IsLocked ) SLATE_ATTRIBUTE( bool, SelectionTip ) SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TArray< TWeakObjectPtr<UObject> >* SelectedObjects );`
- L38 _public prototype_ `void Refresh( const TArray< TWeakObjectPtr<UObject> >& SelectedObjects, int32 NameAreaSettings );` — Refreshes the name area when selection changes @param SelectedObjects	the new list of selected objects
- L43 _public prototype_ `virtual void SetCustomContent(TSharedRef<SWidget>& InCustomContent);` — Inserts Custom Content (typically tool buttons) before the lock
- L47 _private prototype_ `const FSlateBrush* OnGetLockButtonImageResource() const;` — @return the Slate brush to use for the lock image
- L49 _private prototype_ `TSharedRef< SWidget > BuildObjectNameArea( const TArray< TWeakObjectPtr<UObject> >& SelectedObjects );`
- L51 _private prototype_ `void BuildObjectNameAreaSelectionLabel( TSharedRef< SHorizontalBox > SelectionLabelBox, const TWeakObjectPtr<UObject> ObjectWeakPtr, const int32 NumSelectedObjects );`
- L53 _private prototype_ `void OnEditBlueprintClicked( TWeakObjectPtr<UBlueprint> InBlueprint, TWeakObjectPtr<UObject> InAsset );`
- L55 _private member_ `FOnClicked OnLockButtonClicked;`
- L56 _private member_ `TAttribute<bool> IsLocked;`
- L57 _private member_ `TAttribute<bool> SelectionTip;`
- L59 _private member_ `TSharedPtr<SWidget> CustomContent;`
- L61 _private member_ `bool bShowLockButton;`
- L62 _private member_ `bool bShowObjectLabel;`
- L65 _private member_ `SHorizontalBox::FSlot* CustomContentSlot;` — Area where the customs content resides

### `Source/Editor/PropertyEditor/Private/SDetailRowIndent.h` (Private)


#### class `SDetailRowIndent`  
`class SDetailRowIndent : public SCompoundWidget`  
_L13-28_
- inherits: `SCompoundWidget`
- L16 _public function_ `SLATE_BEGIN_ARGS(SDetailRowIndent)`
- L17 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<SDetailTableRowBase> DetailsRow);`
- L22 _private prototype_ `int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const;`
- L23 _private prototype_ `FOptionalSize GetIndentWidth() const;`
- L24 _private prototype_ `FSlateColor GetRowBackgroundColor(int32 IndentLevel) const;`
- L27 _private member_ `TWeakPtr<SDetailTableRowBase> Row;`

### `Source/Editor/PropertyEditor/Private/SDetailSingleItemRow.h` (Private)


#### class `SArrayRowHandle`  
`class SArrayRowHandle : public SCompoundWidget`  
_L24-44_
- inherits: `SCompoundWidget`
- L27 _public function_ `SLATE_BEGIN_ARGS(SArrayRowHandle)`
- L29 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_ARGUMENT(TSharedPtr<SDetailSingleItemRow>, ParentRow) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L35 _public function_ `FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override`
- L40 _public prototype_ `FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L43 _private member_ `TWeakPtr<SDetailSingleItemRow> ParentRow;`

#### class `SDetailSingleItemRow`  
`class SDetailSingleItemRow : public SDetailTableRowBase`  
_L49-182_
- inherits: `SDetailTableRowBase`
- desc: A widget for details that span the entire tree row and have no columns
- L52 _public function_ `SLATE_BEGIN_ARGS( SDetailSingleItemRow ) : _ColumnSizeData()`
- L54 _public prototype_ `SLATE_ARGUMENT( FDetailColumnSizeData, ColumnSizeData ) SLATE_ARGUMENT( bool, AllowFavoriteSystem) SLATE_END_ARGS() void Construct( const FArguments& InArgs, FDetailLayoutCustomization* InCustomization, bool bHasMultipleColumns, TSharedRef<FDetailTreeNode> InOwnerTreeNode, const TSharedRef<STableViewBase>& InOwnerTableView );`
- L64 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L65 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L68 _public prototype_ `TSharedPtr<FDragDropOperation> CreateDragDropOperation();`
- L72 _protected prototype_ `virtual void PopulateContextMenu(UToolMenu* ToolMenu) override;`
- L73 _protected prototype_ `virtual TArray<TSharedPtr<IPropertyHandle>> GetPropertyHandles(const bool bRecursive = false) const override;`
- L74 _protected prototype_ `virtual TSharedPtr<IPropertyHandle> GetPrimaryPropertyHandle() const override;`
- L75 _protected prototype_ `virtual bool CanFavoriteRow(bool bInAddToFavorite) override;`
- L76 _protected prototype_ `virtual void OnFavoriteRow(bool bInAddToFavorite) override;`
- L80 _private prototype_ `void OnCopyProperty();`
- L81 _private prototype_ `void OnCopyPropertyDisplayName();`
- L82 _private prototype_ `bool CanCopyPropertyDisplayName();`
- L83 _private prototype_ `void OnCopyPropertyInternalName();`
- L84 _private prototype_ `bool CanCopyPropertyInternalName();`
- L85 _private prototype_ `bool CanSelectByProperty();`
- L86 _private prototype_ `void OnPasteProperty();`
- L87 _private prototype_ `bool CanPasteProperty() const;`
- L89 _private prototype_ `void OnCopyGroup();`
- L90 _private prototype_ `bool CanCopyGroup() const;`
- L91 _private prototype_ `void OnPasteGroup();`
- L92 _private prototype_ `bool CanPasteGroup();`
- L94 _private prototype_ `FString GetPropertyInternalName() const;`
- L95 _private prototype_ `FText GetPropertyDisplayName() const;`
- L104 _private prototype_ `TSharedRef<SWidget> GetNameWidget(TSharedRef<SWidget> NameWidget, const TSharedPtr<FPropertyNode>& Node) const;` — Returns the TSharedRef<SWidget> for the Name column widget @param NameWidget @param Node @return
- L109 _private prototype_ `bool CanPasteFromText(const FString& InTag, const FString& InText, const bool bIncludeEditCondition = true) const;` — @return True if the (optionally tagged) input contents can be pasted
- L114 _private prototype_ `void OnPasteFromText(const FString& InTag, const FString& InText, const TOptional<FGuid>& InOperationId, const bool bIncludeEditCondition);` — Delegate handling pasting an optionally tagged text snippet
- L119 _private prototype_ `bool PasteFromText(const FString& InTag, const FString& InText, const bool bIncludeEditCondition = true);` — Handle pasting an optionally tagged text snippet
- L121 _private prototype_ `FSlateColor GetOuterBackgroundColor() const;`
- L122 _private prototype_ `FSlateColor GetInnerBackgroundColor() const;`
- L124 _private prototype_ `void CreateGlobalExtensionWidgets(TArray<FPropertyRowExtensionButton>& ExtensionButtons) const;`
- L125 _private prototype_ `void PopulateExtensionWidget();`
- L127 _private prototype_ `void UpdateResetToDefault();`
- L128 _private prototype_ `void OnResetToDefaultClicked() const;`
- L129 _private prototype_ `bool IsResetToDefaultVisible() const;`
- L131 _private prototype_ `bool IsHighlighted() const;`
- L132 _private prototype_ `bool IsFavorite() const;`
- L135 _private prototype_ `FString GetRowNameText() const;` — UIActions to help populate the PropertyEditorPermissionList, which must first be turned on through FPropertyEditorPermissionList::Get().SetShouldShowMenuEntries
- L136 _private prototype_ `void CopyRowNameText() const;`
- L137 _private prototype_ `void OnToggleAllowList() const;`
- L138 _private prototype_ `bool IsAllowListChecked() const;`
- L139 _private prototype_ `void OnToggleDenyList() const;`
- L140 _private prototype_ `bool IsDenyListChecked() const;`
- L142 _private prototype_ `void OnArrayOrCustomDragLeave(const FDragDropEvent& DragDropEvent);`
- L143 _private prototype_ `FReply OnArrayAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, TSharedPtr<FDetailTreeNode> TargetItem);`
- L144 _private prototype_ `FReply OnArrayHeaderAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, TSharedPtr<FDetailTreeNode> TargetItem);`
- L146 _private prototype_ `TOptional<EItemDropZone> OnArrayCanAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, TSharedPtr< FDetailTreeNode > Type);`
- L148 _private prototype_ `FReply OnCustomAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, TSharedPtr<FDetailTreeNode> TargetItem);`
- L149 _private prototype_ `TOptional<EItemDropZone> OnCustomCanAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, TSharedPtr<FDetailTreeNode> Type);`
- L153 _private prototype_ `bool CheckValidDrop(const TSharedPtr<SDetailSingleItemRow> RowPtr, EItemDropZone DropZone) const;` — Checks if the current drop event is being dropped into a valid location
- L155 _private prototype_ `TSharedPtr<FPropertyNode> GetPropertyNode() const;`
- L156 _private prototype_ `TSharedPtr<IPropertyHandle> GetPropertyHandle() const;`
- L158 _private prototype_ `void SetPropertyColorationTarget(bool bSelectActors = false);`
- L161 _private member_ `FDetailLayoutCustomization* Customization = nullptr;` — Customization for this widget
- L162 _private member_ `FDetailWidgetRow WidgetRow;`
- L163 _private member_ `bool bAllowFavoriteSystem = false;`
- L164 _private member_ `bool bCachedResetToDefaultVisible = false;`
- L165 _private member_ `TSharedPtr<FPropertyNode> SwappablePropertyNode;`
- L166 _private member_ `TSharedPtr<SButton> ExpanderArrow;`
- L167 _private member_ `TWeakPtr<FDragDropOperation> DragOperation;` — last drag initiated by this widget
- L168 _private member_ `FUIAction CopyAction;`
- L169 _private member_ `FUIAction PasteAction;`
- L172 _private member_ `UE::PropertyEditor::Internal::FClipboardData PreviousClipboardData;` — Previously parsed clipboard data.
- L175 _private member_ `TSharedPtr<FOnPasteFromText> OnPasteFromTextDelegate;` — Delegate handling pasting an optionally tagged text snippet
- L178 _private member_ `TSharedPtr<FOnCopyToText> OnCopyToTextDelegate;` — Delegate handling copying to a text snippet
- L181 _private member_ `FCurveSequence PulseAnimation;` — Animation curve for displaying pulse

#### class `FArrayRowDragDropOp`  
`class FArrayRowDragDropOp : public FDecoratedDragDropOp`  
_L184-198_
- inherits: `FDecoratedDragDropOp`
- L187 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FArrayRowDragDropOp, FDecoratedDragDropOp) FArrayRowDragDropOp(TSharedPtr<SDetailSingleItemRow> InRow);`
- L192 _public prototype_ `void Init();` — Inits the tooltip, needs to be called after constructing
- L195 _public prototype_ `void SetValidTarget(bool IsValidTarget);` — Update the drag tool tip indicating whether the current drop target is valid
- L197 _public member_ `TWeakPtr<SDetailSingleItemRow> Row;`

### `Source/Editor/PropertyEditor/Private/SDetailTableRowBase.h` (Private)


#### class `SDetailTableRowBase`  
`class SDetailTableRowBase : public STableRow< TSharedPtr< FDetailTreeNode > >`  
_L22-104_
- inherits: `STableRow<TSharedPtr<FDetailTreeNode>>`
- L25 _public prototype_ `virtual FReply OnMouseButtonUp( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L27 _public prototype_ `int32 GetIndentLevelForBackgroundColor() const;`
- L29 _public prototype_ `static bool IsScrollBarVisible(TWeakPtr<STableViewBase> OwnerTableViewWeak);`
- L30 _public member_ `static const float ScrollBarPadding;`
- L33 _public prototype_ `virtual void PopulateContextMenu(UToolMenu* ToolMenu);` — Called to register/extend the row context menu.
- L41 _protected member_ `TSharedPtr<FPropertyUpdatedWidgetBuilder> PropertyUpdatedWidgetBuilder;` — The FPropertyUpdatedWidgetBuilder which builds a Property Updated widget which can be used in place of the reset to default button
- L44 _protected prototype_ `TArray<TSharedPtr<FPropertyNode>> GetPropertyNodes(const bool bRecursive = false) const;` — Retrieve all property nodes represented by this row, and it's children if Recursive specified.
- L47 _protected prototype_ `TArray<TSharedPtr<FPropertyNode>> GetPropertyNodesFromHandles(const TConstArrayView<TSharedPtr<IPropertyHandle>>& InPropertyHandles) const;` — Retrieve all property nodes represented by the given property handles.
- L55 _protected prototype_ `virtual TArray<TSharedPtr<IPropertyHandle>> GetPropertyHandles(const bool bRecursive = false) const;` — Retrieve all property handles represented by this row, and it's children if Recursive specified. @note: This only returns the visible property handles, not the "primary" one (although often these are the same), for example FVector will give you the X, Y and Z handles, not the FVector itself. For the "primary" property handle, use GetPrimaryPropertyHandle.
- L58 _protected prototype_ `virtual TSharedPtr<IPropertyHandle> GetPrimaryPropertyHandle() const;` — Retrieve the primary property handle for this row, ie. an FVector should return the Struct itself, not it's X, Y, Z properties.
- L61 _protected prototype_ `virtual void ForceRefresh();` — Refreshes widget and associated list views.
- L64 _protected prototype_ `virtual void OnFavoriteRow(bool bInAddToFavorite);` — Called when row favoriting is toggled
- L67 _protected prototype_ `virtual bool CanFavoriteRow(bool bInAddToFavorite);` — Is row favoriting allowed
- L70 _private function_ `void OnExpandAllClicked()`
- L81 _private function_ `void OnCollapseAllClicked()`
- L96 _protected member_ `TWeakPtr<STableViewBase> OwnerTableViewWeak;` — A weak pointer to the STableViewBase from which we can get information such as if the scrollbar is showing.
- L97 _protected member_ `TWeakPtr<FDetailTreeNode> OwnerTreeNode;`
- L103 _protected member_ `TSharedPtr<FDetailsDisplayManager> DisplayManager;` — The @code DetailsDisplayManager @endcode which provides an API to manage some of the characteristics of the details display

### `Source/Editor/PropertyEditor/Private/SDetailsView.h` (Private)


#### class `SDetailsView`  
`class SDetailsView : public SDetailsViewBase`  
_L19-301_
- inherits: `SDetailsViewBase`
- L24 _public function_ `SLATE_BEGIN_ARGS(SDetailsView)`
- L27 _public prototype_ `virtual ~SDetailsView();`
- L30 _public prototype_ `virtual void ForceRefresh() override;` — Causes the details view to be refreshed (new widgets generated) with the current set of objects
- L33 _public prototype_ `virtual void InvalidateCachedState() override;` — Invalidates cached state such as the "revert to default" arrow and edit conditions, without rebuilding the entire panel.
- L36 _public prototype_ `void MoveScrollOffset(int32 DeltaOffset) override;` — Move the scrolling offset (by item), but do not refresh the tree
- L41 _public prototype_ `void Construct(const FArguments& InArgs, const FDetailsViewArgs& InDetailsViewArgs);` — Constructs the property view widgets
- L44 _public prototype_ `virtual void SetObjects(const TArray<UObject*>& InObjects, bool bForceRefresh = false, bool bOverrideLock = false) override;` — IDetailsView interface
- L45 _public prototype_ `virtual void SetObjects(const TArray<TWeakObjectPtr<UObject>>& InObjects, bool bForceRefresh = false, bool bOverrideLock = false) override;`
- L46 _public prototype_ `virtual void SetObject(UObject* InObject, bool bForceRefresh = false) override;`
- L47 _public prototype_ `virtual bool IsGroupFavorite(FStringView GroupPath) const override;`
- L48 _public prototype_ `virtual void SetGroupFavorite(FStringView GroupPath, bool IsFavorite) override;`
- L49 _public prototype_ `virtual bool IsCustomBuilderFavorite(FStringView Path) const override;`
- L50 _public prototype_ `virtual void SetCustomBuilderFavorite(FStringView Path, bool IsFavorite) override;`
- L52 _public prototype_ `virtual void RemoveInvalidObjects() override;`
- L53 _public prototype_ `virtual void SetObjectPackageOverrides(const TMap<TWeakObjectPtr<UObject>, TWeakObjectPtr<UPackage>>& InMapping) override;`
- L54 _public prototype_ `virtual void SetRootObjectCustomizationInstance(TSharedPtr<IDetailRootObjectCustomization> InRootObjectCustomization) override;`
- L55 _public prototype_ `virtual void SetObjectFilter(TSharedPtr<FDetailsViewObjectFilter> InFilter) override;`
- L56 _public prototype_ `virtual void SetClassViewerFilters(const TArray<TSharedRef<class IClassViewerFilter>>& InFilters) override;`
- L63 _public prototype_ `void ReplaceObjects(const TMap<UObject*, UObject*>& OldToNewObjectMap);` — Replaces objects being observed by the view with new objects @param OldToNewObjectMap	Mapping from objects to replace to their replacement
- L70 _public prototype_ `void RemoveDeletedObjects(const TArray<UObject*>& DeletedObjects);` — Removes objects from the view because they are about to be deleted @param DeletedObjects	The objects to delete
- L73 _public prototype_ `virtual void SetOnObjectArrayChanged(FOnObjectArrayChanged OnObjectArrayChangedDelegate) override;` — Sets the callback for when the property view changes
- L76 _public function_ `virtual const TArray<TWeakObjectPtr<UObject>>& GetSelectedObjects() const override` — @return	Returns list of selected objects we're inspecting
- L82 _public function_ `virtual const TArray<TWeakObjectPtr<AActor>>& GetSelectedActors() const override` — @return	Returns list of selected actors we're inspecting
- L88 _public function_ `virtual const FSelectedActorInfo& GetSelectedActorInfo() const override` — @return Returns information about the selected set of actors
- L93 _public function_ `virtual bool HasClassDefaultObject() const override`
- L98 _public prototype_ `virtual bool IsConnected() const override;`
- L100 _public function_ `virtual FRootPropertyNodeList& GetRootNodes() override`
- L105 _public function_ `virtual bool DontUpdateValueWhileEditing() const override`
- L110 _public function_ `virtual bool ContainsMultipleTopLevelObjects() const override`
- L115 _public function_ `virtual TSharedPtr<IDetailRootObjectCustomization> GetRootObjectCustomization() const override`
- L127 _public prototype_ `static const FDetailsViewStyleKey& GetPrimaryDetailsViewStyleKey();` — Gets the Shared pointer which points to the @code const FDetailsViewStyleKey& @endcode which is used for @code SDetailsView @endcode instances for which no other @code FDetailsViewStyleKey @endcode has been provided, for example through @code FDetailsViewArgs @endcode or an @code FDetailsViewObjectFilter @endcode. @return the shared pointer for the Primary details style key
- L132 _public prototype_ `virtual bool IsDefaultStyle() const override;` — Returns a bool indicating whether the given @code FDetailsViewStyleKey @endcode is the default Details View Style
- L139 _public prototype_ `virtual bool ResetToDefaultSection() override;` — Resets the selected sections to the default 'All' section. @return whether the operation succeeded.
- L153 _private prototype_ `virtual TSharedPtr<FDetailsNameWidgetOverrideCustomization> GetDetailsNameWidgetOverrideCustomization() override;` — returns a pointer to a Customization that can be applied to all name widgets, if one exists
- L155 _private prototype_ `void SetObjectArrayPrivate(const TArray<UObject*>& InObjects);`
- L157 _private prototype_ `TSharedRef<SDetailTree> ConstructTreeView(const TSharedRef<SScrollBar>& ScrollBar );`
- L166 _private prototype_ `bool ShouldSetNewObjects(const TArray<UObject*>& InObjects) const;` — Returns whether or not new objects need to be set. If the new objects being set are identical to the objects already in the details panel, nothing needs to be set @param InObjects The potential new objects to set @return true if the new objects should be set
- L171 _private prototype_ `int32 GetNumObjects() const;` — Returns the number of objects being edited by this details panel.
- L174 _private prototype_ `void PreSetObject(int32 InNewNumObjects);` — Called before during SetObjectArray before we change the objects being observed
- L177 _private prototype_ `void PostSetObject(const TArray<FDetailsViewObjectRoot>& Roots);` — Called at the end of SetObjectArray after we change the objects being observed
- L180 _private prototype_ `EVisibility GetActorNameAreaVisibility() const;` — Called to get the visibility of the actor name area
- L183 _private prototype_ `const FSlateBrush* OnGetLockButtonImageResource() const;` — Returns the name of the image used for the icon on the locked button
- L186 _private prototype_ `bool CanOpenRawPropertyEditor() const;` — Whether the property matrix button should be enabled
- L189 _private prototype_ `EVisibility CanShowRawPropertyEditorButton(const bool bAllowedByDetailsViewArgs) const;` — Whether the property matrix button should be shown
- L194 _private prototype_ `FReply OnOpenRawPropertyEditorClicked();` — Called to open the raw property editor (property matrix)
- L197 _private prototype_ `bool IsShowHiddenPropertiesWhilePlayingChecked() const;` — @return Returns true if show hidden properties while playing is checked
- L200 _private prototype_ `void OnShowHiddenPropertiesWhilePlayingClicked();` — Called when show hidden properties while playing is clicked
- L203 _private function_ `bool IsShowSectionsChecked() const` — @return true if Show Sections is checked.
- L206 _private prototype_ `void OnShowSectionsClicked();` — Called when Show Sections is clicked
- L209 _private prototype_ `bool IsShowHelperSectionsChecked() const;` — @return true if Show Helper Sections is checked.
- L212 _private prototype_ `void OnShowHelperSectionsClicked();` — Called when Show Helper Sections is clicked
- L215 _private prototype_ `FSlateColor GetToggleFavoritesColor() const;` — Get the color of the toggle favorites button.
- L218 _private prototype_ `FReply OnToggleFavoritesClicked();` — Called when the toggle favorites button is clicked.
- L221 _private prototype_ `void OnPostUndoRedo();` — Called after an undo or redo operation occurs in the editor.
- L224 _private prototype_ `TMap<FName, FSection> GetAllSections() const;` — Get all sections, keyed by name for the objects currently selected in the view.
- L227 _private prototype_ `void RebuildSectionSelector();` — Rebuild the section selector widget after a selection has been changed.
- L230 _private prototype_ `void OnSectionCheckedChanged(ECheckBoxState State, FName NewSelection);` — Refilter the details view after the user has selected a new section.
- L233 _private prototype_ `ECheckBoxState IsSectionChecked(FName Section) const;` — Get the currently selected section.
- L236 _private prototype_ `const FSlateBrush* GetViewOptionsBadgeIcon() const;` — Get the badge for the view options icon (if there are any options active
- L241 _private prototype_ `virtual void UpdateStyleKey() override;` — Updates @code FDetailsViewStyleKey& StyleKey @endcode for the current @code SDetailsView @endcode state
- L246 _private prototype_ `virtual const FDetailsViewStyleKey& GetStyleKey() override;` — Gets the @code FDetailsViewStyleKey& @endcode which provides a Key to the current style for a Details View
- L251 _private prototype_ `virtual TSharedPtr<FDetailsDisplayManager> GetDisplayManager() override;` — Returns a @code TSharedPtr @endcode to the @code FDetailsDisplayManager @endcode
- L259 _private prototype_ `void RefreshDisplayManager();` — Refreshes the class member @code TSharedPtr<FDetailsDisplayManager> DisplayManager @endcode. This is required anytime the data in the display manager may have grown stale.
- L265 _private member_ `TSharedPtr<FDetailsViewStyleKey> StyleKeySP;` — The @code FDetailsViewStyle& @endcode shared pointer which provides style information for this details view.
- L268 _private member_ `TSharedPtr<FDetailsNameWidgetOverrideCustomization> DetailsNameWidgetOverrideCustomization;` — A Customization that can be applied to all name widgets
- L271 _private member_ `TSharedPtr<FDetailsViewObjectFilter> ObjectFilter;` — The filter for objects viewed by this details panel
- L274 _private member_ `FSelectedActorInfo SelectedActorInfo;` — Information about the current set of selected actors
- L277 _private member_ `TArray<TWeakObjectPtr<UObject>> UnfilteredSelectedObjects;` — Set of selected objects for this detail view that were passed in through SetObjects (before the object filter is applied).
- L280 _private member_ `TArray<TWeakObjectPtr<UObject>> SelectedObjects;` — Final set of selected objects for this detail view after applying the object filter. It may be different from the set passed in through SetObjects.
- L286 _private member_ `TArray< TWeakObjectPtr<AActor> > SelectedActors;` — Selected actors for this detail view.  Note that this is not necessarily the same editor selected actor set.  If this detail view is locked It will only contain actors from when it was locked
- L288 _private member_ `TArray<TSharedPtr<FComplexPropertyNode>> RootPropertyNodes;` — The root property nodes of the property tree for a specific set of UObjects
- L290 _private member_ `FOnObjectArrayChanged OnObjectArrayChanged;` — Callback to send when the property view changes
- L292 _private member_ `TSharedPtr<IDetailRootObjectCustomization> RootObjectCustomization;` — Customization instance used when there are multiple top level objects in this view
- L294 _private member_ `bool bViewingClassDefaultObject;` — True if at least one viewed object is a CDO (blueprint editing)
- L296 _private member_ `FDelegateHandle PostUndoRedoDelegateHandle;` — Delegate handle for unregistering from the PostUndoRedo event.
- L298 _private member_ `TSharedPtr<class SWrapBox> SectionSelectorBox;` — The section selector widget to show if DetailsViewArgs.bShowSectionSelector is true.
- L300 _private member_ `bool bIsRefreshing;` — True when currently in the middle of a refreshing the object array

#### struct `SDetailsView::FSection`  
`struct FSection`  
_L143-147_
- desc: Minimal struct to hold section information. Note that the Name is the key, so is not present here.
- L145 _public member_ `FText DisplayName;`
- L146 _public member_ `int32 Order = 0;`

### `Source/Editor/PropertyEditor/Private/SDetailsViewBase.h` (Private)


#### class `SDetailsViewBase`  
`class SDetailsViewBase : public IDetailsViewPrivate`  
_L48-630_
- inherits: `IDetailsViewPrivate`
- L53 _public prototype_ `static void ResetTransientPerViewDetailExpansion();` — Global method to remove saved transient detail expansions
- L56 _public prototype_ `static void ResetPersistentPerViewDetailExpansion();` — Global method to remove saved persistent detail expansions
- L59 _public prototype_ `SDetailsViewBase();`
- L60 _public prototype_ `virtual ~SDetailsViewBase();`
- L65 _public function_ `virtual bool IsUpdatable() const override` — @return true of the details view can be updated from editor selection
- L70 _public function_ `virtual bool HasActiveSearch() const override`
- L75 _public prototype_ `virtual void ClearSearch() override;`
- L76 _public prototype_ `virtual void SetSearchText(const FText& InSearch) override;`
- L78 _public function_ `virtual int32 GetNumVisibleTopLevelObjects() const override`
- L84 _public function_ `virtual FName GetIdentifier() const override` — @return The identifier for this details view, or NAME_None is this view is anonymous
- L92 _public prototype_ `virtual void HideFilterArea(bool bHide) override;` — Sets the visible state of the filter box/property grid area
- L97 _public prototype_ `virtual TArray< FPropertyPath > GetPropertiesInOrderDisplayed() const override;` — IDetailsView interface
- L98 _public prototype_ `virtual TArray<TPair<int32, FPropertyPath>> GetPropertyRowNumbers() const override;`
- L99 _public prototype_ `virtual int32 CountRows() const override;`
- L100 _public prototype_ `virtual void HighlightProperty(const FPropertyPath& Property) override;`
- L101 _public prototype_ `virtual void ScrollPropertyIntoView(const FPropertyPath& Property, bool bExpandProperty = false) override;`
- L102 _public prototype_ `virtual FSlateRect GetPaintSpacePropertyBounds(const TSharedRef<FDetailTreeNode>& InDetailTreeNode, bool bIncludeChildren = true) const override;`
- L103 _public prototype_ `virtual FSlateRect GetTickSpacePropertyBounds(const TSharedRef<FDetailTreeNode>& InDetailTreeNode, bool bIncludeChildren = true) const override;`
- L104 _public prototype_ `virtual bool IsAncestorCollapsed(const TSharedRef<IDetailTreeNode>& Node) const override;`
- L105 _public prototype_ `virtual void ShowAllAdvancedProperties() override;`
- L106 _public prototype_ `virtual void SetOnDisplayedPropertiesChanged(FOnDisplayedPropertiesChanged InOnDisplayedPropertiesChangedDelegate) override;`
- L107 _public function_ `virtual FOnDisplayedPropertiesChanged& GetOnDisplayedPropertiesChanged() override`
- L108 _public function_ `virtual void SetDisableCustomDetailLayouts( bool bInDisableCustomDetailLayouts ) override`
- L109 _public prototype_ `virtual void SetIsPropertyVisibleDelegate(FIsPropertyVisible InIsPropertyVisible) override;`
- L110 _public function_ `virtual FIsPropertyVisible& GetIsPropertyVisibleDelegate() override`
- L111 _public prototype_ `virtual void SetIsCustomRowVisibleDelegate(FIsCustomRowVisible InIsCustomRowVisible) override;`
- L112 _public function_ `virtual FIsCustomRowVisible& GetIsCustomRowVisibleDelegate() override`
- L113 _public prototype_ `virtual void SetIsPropertyReadOnlyDelegate(FIsPropertyReadOnly InIsPropertyReadOnly) override;`
- L114 _public function_ `virtual FIsCustomRowReadOnly& GetIsCustomRowReadOnlyDelegate() override`
- L115 _public prototype_ `virtual void SetIsCustomRowReadOnlyDelegate(FIsCustomRowReadOnly InIsCustomRowReadOnly) override;`
- L116 _public function_ `virtual FIsPropertyReadOnly& GetIsPropertyReadOnlyDelegate() override`
- L117 _public prototype_ `virtual void SetIsPropertyEditingEnabledDelegate(FIsPropertyEditingEnabled IsPropertyEditingEnabled) override;`
- L118 _public function_ `virtual FIsPropertyEditingEnabled& GetIsPropertyEditingEnabledDelegate() override`
- L119 _public prototype_ `virtual bool IsPropertyEditingEnabled() const override;`
- L120 _public prototype_ `virtual void SetKeyframeHandler(TSharedPtr<IDetailKeyframeHandler> InKeyframeHandler) override;`
- L121 _public function_ `virtual TSharedPtr<IDetailKeyframeHandler> GetKeyframeHandler() const override`
- L122 _public prototype_ `virtual void SetExtensionHandler(TSharedPtr<IDetailPropertyExtensionHandler> InExtensionHandler) override;`
- L123 _public function_ `virtual TSharedPtr<IDetailPropertyExtensionHandler> GetExtensionHandler() const override`
- L124 _public prototype_ `virtual void SetChildrenCustomizationHandler(TSharedPtr<IDetailPropertyChildrenCustomizationHandler> InChildrenHandler) override;`
- L125 _public function_ `virtual TSharedPtr<IDetailPropertyChildrenCustomizationHandler> GetChildrenCustomizationHandler() const override`
- L126 _public prototype_ `virtual bool IsPropertyVisible(const struct FPropertyAndParent& PropertyAndParent) const override;`
- L127 _public prototype_ `virtual bool IsPropertyReadOnly(const struct FPropertyAndParent& PropertyAndParent) const override;`
- L128 _public prototype_ `virtual bool IsCustomRowVisible(FName InRowName, FName InParentName) const override;`
- L129 _public prototype_ `virtual bool IsCustomRowReadOnly(FName InRowName, FName InParentName) const override;`
- L130 _public prototype_ `virtual void SetGenericLayoutDetailsDelegate(FOnGetDetailCustomizationInstance OnGetGenericDetails) override;`
- L131 _public function_ `virtual FOnGetDetailCustomizationInstance& GetGenericLayoutDetailsDelegate() override`
- L132 _public function_ `virtual bool IsLocked() const override`
- L133 _public prototype_ `virtual void RefreshRootObjectVisibility() override;`
- L134 _public function_ `virtual FOnFinishedChangingProperties& OnFinishedChangingProperties() const override`
- L135 _public prototype_ `virtual void RegisterInstancedCustomPropertyLayout(UStruct* Class, FOnGetDetailCustomizationInstance DetailLayoutDelegate) override;`
- L136 _public prototype_ `virtual void RegisterInstancedCustomPropertyTypeLayout(FName PropertyTypeName, FOnGetPropertyTypeCustomizationInstance PropertyTypeLayoutDelegate, TSharedPtr<IPropertyTypeIdentifier> Identifier = nullptr) override;`
- L137 _public prototype_ `virtual void UnregisterInstancedCustomPropertyLayout(UStruct* Class) override;`
- L138 _public prototype_ `virtual void UnregisterInstancedCustomPropertyTypeLayout(FName PropertyTypeName, TSharedPtr<IPropertyTypeIdentifier> Identifier = nullptr) override;`
- L139 _public function_ `virtual void SetCustomValidatePropertyNodesFunction(FOnValidatePropertyRowGeneratorNodes InCustomValidatePropertyNodesFunction) override`
- L143 _public prototype_ `virtual float GetRightColumnMinWidth() const override;`
- L144 _public prototype_ `virtual void SetRightColumnMinWidth(float InMinWidth) override;`
- L147 _public prototype_ `virtual void RerunCurrentFilter() override;` — IDetailsViewPrivate interface
- L148 _public prototype_ `void SetNodeExpansionState(TSharedRef<FDetailTreeNode> InTreeNode, bool bExpand, bool bRecursive) override;`
- L149 _public prototype_ `void SaveCustomExpansionState(const FString& NodePath, bool bIsExpanded) override;`
- L150 _public prototype_ `bool GetCustomSavedExpansionState(const FString& NodePath) const override;`
- L151 _public prototype_ `virtual FName GetViewIdentifier() const override;`
- L152 _public prototype_ `virtual FDetailsViewArgs::EExpansionPersistenceMethod GetExpansionPersistenceMethod() const override;`
- L153 _public prototype_ `virtual void NotifyFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent) override;`
- L154 _public prototype_ `void RefreshTree() override;`
- L155 _public prototype_ `virtual void RequestForceRefresh() override;`
- L156 _public prototype_ `TSharedPtr<FAssetThumbnailPool> GetThumbnailPool() const override;`
- L157 _public prototype_ `virtual const TArray<TSharedRef<IClassViewerFilter>>& GetClassViewerFilters() const override;`
- L158 _public prototype_ `TSharedPtr<IPropertyUtilities> GetPropertyUtilities() override;`
- L159 _public prototype_ `void CreateColorPickerWindow(const TSharedRef<FPropertyEditor>& PropertyEditor, bool bUseAlpha) override;`
- L160 _public prototype_ `virtual void UpdateSinglePropertyMap(TSharedPtr<FComplexPropertyNode> InRootPropertyNode, FDetailLayoutData& LayoutData, bool bIsExternal) override;`
- L161 _public function_ `virtual FNotifyHook* GetNotifyHook() const override`
- L162 _public function_ `virtual const FCustomPropertyTypeLayoutMap& GetCustomPropertyTypeLayoutMap() const`
- L163 _public prototype_ `virtual void SaveExpandedItems( TSharedRef<FPropertyNode> StartNode ) override;`
- L164 _public prototype_ `virtual void RestoreExpandedItems(TSharedRef<FPropertyNode> StartNode) override;`
- L165 _public prototype_ `virtual void RestoreExpandedItems(TSharedRef<FPropertyNode> StartNode, TMap<UStruct*, FStringPrefixTree>* OptionalExpansionStates);`
- L166 _public prototype_ `virtual void MarkNodeAnimating(TSharedPtr<FPropertyNode> InNode, float InAnimationDuration, TOptional<FGuid> InAnimationBatchId) override;`
- L167 _public prototype_ `virtual bool IsNodeAnimating(TSharedPtr<FPropertyNode> InNode) override;`
- L168 _public prototype_ `virtual float GetNodeAnimationTime(TSharedPtr<FPropertyNode> InNode) override;`
- L169 _public function_ `virtual FDetailColumnSizeData& GetColumnSizeData() override`
- L170 _public function_ `virtual bool IsFavoritingEnabled() const override`
- L171 _public prototype_ `virtual bool IsConnected() const = 0;`
- L172 _public prototype_ `virtual FRootPropertyNodeList& GetRootNodes() = 0;`
- L173 _public prototype_ `virtual void GetHeadNodes(TArray<TWeakPtr<FDetailTreeNode>>&) override;`
- L178 _public prototype_ `void OnColorPickerWindowClosed(const TSharedRef<SWindow>& Window);` — Called when the open color picker window associated with this details view is closed
- L186 _public prototype_ `void RequestItemExpanded(TSharedRef<FDetailTreeNode> TreeNode, bool bExpand) override;` — Requests that an item in the tree be expanded or collapsed @param TreeNode	The tree node to expand @param bExpand	true if the item should be expanded, false otherwise
- L194 _public prototype_ `virtual void SetRootExpansionStates(const bool bExpand, const bool bRecurse) override;` — Sets the expansion state all root nodes and optionally all of their children @param bExpand			The new expansion state @param bRecurse			Whether or not to apply the expansion change to any children
- L199 _public prototype_ `virtual void EnqueueDeferredAction(FSimpleDelegate& DeferredAction) override;` — Adds an action to execute next tick
- L202 _public prototype_ `void RestoreAllExpandedItems(TMap<UStruct*, FStringPrefixTree>* OptionalExpansionStates = nullptr);` — Restore all expanded items in root nodes and external root nodes.
- L208 _public prototype_ `virtual TSharedPtr<FDetailsDisplayManager> GetDisplayManager() override;` — Returns a @code TSharedPtr @endcode to the @code FDetailsDisplayManager @endcode for this details view
- L211 _public prototype_ `virtual bool SupportsKeyboardFocus() const override;`
- L212 _public prototype_ `virtual FReply OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent) override;`
- L213 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;`
- L214 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;`
- L218 _public prototype_ `virtual FVector2D GetScrollDistance() override;` — IScrollableWidget interface
- L219 _public prototype_ `virtual FVector2D GetScrollDistanceRemaining() override;`
- L220 _public prototype_ `virtual TSharedRef<SWidget> GetScrollWidget() override;`
- L229 _public function_ `virtual bool ResetToDefaultSection() override` — Resets the selected sections to the default 'All' section. Base class returns false as sections selection is not application to all detail views. @return whether the operation succeeded.
- L235 _protected prototype_ `void SetColorPropertyFromColorPicker(FLinearColor NewColor);` — Called when a color property is changed from a color picker
- L307 _protected prototype_ `const FString& GetDetailPropertyExpansionSection() const;` — Return string key for the given struct in config .ini for this details view's properties
- L310 _protected prototype_ `const FString& GetDetailCustomWidgetExpansionSection() const;` — Return string key for the given struct in config .ini for this details view's custom widgets
- L313 _protected prototype_ `FString GetStructExpansionConfigKey(UStruct* InStruct) const;` — Return string key for the given struct in config .ini for this details view
- L316 _protected prototype_ `void HandleNodeAnimationComplete(FAnimatingNodeCollection* InAnimatedNode);` — Called when a node collection animation completes
- L319 _protected prototype_ `FAnimatingNodeCollection* GetAnimatingNodeCollectionForPropertyNode(const TSharedPtr<FPropertyNode>& InNode);` — Returns the owning FAnimatingNodeCollection for the provided PropertyNode, if any.
- L322 _protected prototype_ `void UpdatePropertyMaps();` — Updates the property map for access when customizing the details view.  Generates default layout for properties
- L324 _protected function_ `virtual void CustomUpdatePropertyMap(TSharedPtr<FDetailLayoutBuilderImpl>& InDetailLayout)`
- L326 _protected prototype_ `void GetExpansionState(UStruct* BaseStruct, FStringPrefixTree& OutPrefixTree) const;`
- L327 _protected prototype_ `UStruct* GetExpansionStruct(const TSharedRef<FPropertyNode>& StartNode);`
- L330 _protected prototype_ `void UpdatePropertyMapsWithItemExpansions();` — Updates the property map while keeping the expansion state of all items
- L333 _protected prototype_ `EVisibility GetTreeVisibility() const;` — Called to get the visibility of the tree view
- L336 _protected prototype_ `EVisibility GetScrollBarVisibility() const;` — Called to get the visibility of the scrollbar based on options, needs to be dynamic to avoid layout changing on expansion
- L339 _protected prototype_ `const FSlateBrush* OnGetFilterButtonImageResource() const;` — Returns the name of the image used for the icon on the filter button
- L342 _protected prototype_ `FReply OnLockButtonClicked();` — Called when the locked button is clicked
- L350 _protected prototype_ `void SetNodeExpansionStateRecursive( TSharedRef<FDetailTreeNode> InTreeNode, bool bIsItemExpanded );` — Called to recursively expand/collapse the children of the given item @param InTreeNode		The node that was expanded or collapsed @param bIsItemExpanded	True if the item is expanded, false if it is collapsed
- L358 _protected prototype_ `void OnItemExpansionChanged( TSharedRef<FDetailTreeNode> InTreeNode, bool bIsItemExpanded );` — Called when an item is expanded or collapsed in the detail tree @param InTreeNode		The node that was expanded or collapsed @param bIsItemExpanded	True if the item is expanded, false if it is collapsed
- L366 _protected prototype_ `void OnGetChildrenForDetailTree( TSharedRef<FDetailTreeNode> InTreeNode, TArray< TSharedRef<FDetailTreeNode> >& OutChildren );` — Function called through a delegate on the TreeView to request children of a tree node @param InTreeNode		The tree node to get children from @param OutChildren		The list of children of InTreeNode that should be visible
- L371 _protected prototype_ `TSharedRef<ITableRow> OnGenerateRowForDetailTree( TSharedRef<FDetailTreeNode> InTreeNode, const TSharedRef<STableViewBase>& OwnerTable );` — Returns an SWidget used as the visual representation of a node in the treeview.
- L374 _protected prototype_ `void OnRowReleasedForDetailTree(const TSharedRef<ITableRow>& TableRow);` — Clear focus when the row is scrolled out of view.
- L377 _protected function_ `bool IsShowOnlyModifiedChecked() const` — @return true if show only modified is checked
- L380 _protected function_ `bool IsCustomFilterChecked() const` — @return true if custom filter is checked
- L383 _protected function_ `bool IsShowAllAdvancedChecked() const` — @return true if show all advanced is checked
- L386 _protected function_ `bool IsShowOnlyAllowedChecked() const` — @return true if show only differing is checked
- L389 _protected function_ `bool IsShowAllChildrenIfCategoryMatchesChecked() const` — @return true if show all advanced is checked
- L392 _protected function_ `bool IsShowKeyableChecked() const` — @return true if show keyable is checked
- L395 _protected function_ `bool IsShowAnimatedChecked() const` — @return true if show animated is checked
- L398 _protected prototype_ `void OnShowOnlyModifiedClicked();` — Called when show only modified is clicked
- L401 _protected prototype_ `void OnCustomFilterClicked();` — Called when custom filter is clicked
- L404 _protected prototype_ `void OnShowAllAdvancedClicked();` — Called when show all advanced is clicked
- L407 _protected prototype_ `void OnShowOnlyAllowedClicked();` — Called when show only differing is clicked
- L410 _protected prototype_ `void OnShowAllChildrenIfCategoryMatchesClicked();` — Called when show all children if category matches is clicked
- L413 _protected prototype_ `void OnShowKeyableClicked();` — Called when show keyable is clicked
- L416 _protected prototype_ `void OnShowAnimatedClicked();` — Called when show animated is clicked
- L419 _protected prototype_ `void FilterRootNode(const TSharedPtr<FComplexPropertyNode>& RootNode);` — Apply the CurrentFilter to the given root node.
- L422 _protected prototype_ `void UpdateFilteredDetails();` — Updates the details with the CurrentFilter
- L425 _protected prototype_ `void OnFilterTextChanged(const FText& InFilterText);` — Called when the filter text changes.  This filters specific property nodes out of view
- L428 _protected prototype_ `void OnFilterTextCommitted(const FText& InSearchText, ETextCommit::Type InCommitType);` — Called when the filter text is cleared. Resets the filters
- L431 _protected function_ `virtual void UpdatePropertyAllowList(const TSet<FPropertyPath>& InAllowedProperties) override` — Called when the list of currently differing properties changes
- L433 _protected prototype_ `virtual TSharedPtr<SWidget> GetNameAreaWidget() override;`
- L434 _protected prototype_ `virtual void SetNameAreaCustomContent(TSharedRef<SWidget>& InCustomContent) override;`
- L435 _protected prototype_ `virtual TSharedPtr<SWidget> GetFilterAreaWidget() override;`
- L436 _protected prototype_ `virtual TSharedPtr<FUICommandList> GetHostCommandList() const override;`
- L437 _protected prototype_ `virtual TSharedPtr<FTabManager> GetHostTabManager() const override;`
- L438 _protected prototype_ `virtual void SetHostTabManager(TSharedPtr<FTabManager> InTabManager) override;`
- L445 _protected prototype_ `void FilterView( const FString& InFilterText );` — Hides or shows properties based on the passed in filter text @param InFilterText	The filter text
- L448 _protected prototype_ `EVisibility GetFilterBoxVisibility() const;` — Called to get the visibility of the filter box
- L451 _protected function_ `virtual void SetCustomFilterDelegate(FSimpleDelegate InOverride) override`
- L456 _protected function_ `virtual void SetCustomFilterLabel(FText InText) override`
- L461 _protected function_ `FText GetCustomFilterLabel() const`
- L467 _protected prototype_ `void SetPendingCleanupTimer();` — Free memory that is pending delete next editor tick even when widget not visible or ticking
- L469 _protected prototype_ `void HandlePendingCleanupTimer();` — Free memory that is pending delete during editor tick
- L471 _protected prototype_ `void HandlePendingCleanup();` — Free memory that is pending delete
- L474 _protected prototype_ `void SetPendingRefreshTimer();` — Set timer to force refresh if one not already set
- L476 _protected prototype_ `void ClearPendingRefreshTimer();` — Clear timer to force refresh if set
- L478 _protected prototype_ `void HandlePendingRefreshTimer();` — Force refresh during editor tick
- L480 _protected prototype_ `void SavePreSearchExpandedItems();`
- L481 _protected prototype_ `void RestorePreSearchExpandedItems();`
- L488 _protected prototype_ `struct FDetailsViewConfig* GetMutableViewConfig();` — Get a mutable version of the view config for setting values. @returns		The view config for this view. @note		If DetailsViewArgs.ViewIdentifier is not set, it is not possible to store settings for this view.
- L495 _protected prototype_ `const FDetailsViewConfig* GetConstViewConfig() const;` — Get a const version of the view config for getting values. @returns		The view config for this view. @note		If DetailsViewArgs.ViewIdentifier is not set, it is not possible to retrieve settings for this view.
- L496 _protected prototype_ `void SaveViewConfig();`
- L499 _protected prototype_ `void ClearKeyboardFocusIfWithin(const TSharedRef<SWidget>& Widget) const;` — Clear the keyboard focus if it's inside the given widget.
- L502 _protected prototype_ `FDetailFilter CreateDetailFilter();` — Creates details filter before filtering nodes
- L504 _protected prototype_ `void BindCommands();`
- L508 _protected member_ `FDetailsViewArgs DetailsViewArgs;` — The user defined args for the details view
- L510 _protected member_ `FCustomDetailLayoutMap InstancedClassToDetailLayoutMap;` — A mapping of classes to detail layout delegates, called when querying for custom detail layouts in this instance of the details view only
- L512 _protected member_ `FCustomPropertyTypeLayoutMap InstancedTypeToLayoutMap;` — A mapping of type names to detail layout delegates, called when querying for custom detail layouts in this instance of the details view only
- L514 _protected member_ `TArray<FDetailLayoutData> DetailLayouts;` — The current detail layout based on objects in this details panel.  There is one layout for each top level object node.
- L516 _protected member_ `TSharedPtr<SWidget> FilterRow;` — Row for searching and view options
- L518 _protected member_ `TSharedPtr<SSearchBox> SearchBox;` — Search box
- L520 _protected member_ `TArray< TSharedPtr<IDetailCustomization> > CustomizationClassInstancesPendingDelete;` — Customization instances that need to be destroyed when safe to do so
- L522 _protected member_ `TArray< TSharedPtr<FDetailLayoutBuilderImpl> > DetailLayoutsPendingDelete;` — Detail layouts that need to be destroyed when safe to do so
- L524 _protected member_ `TMap< TWeakPtr<FDetailTreeNode>, bool > FilteredNodesRequestingExpansionState;` — Map of nodes that are requesting an automatic expansion/collapse due to being filtered
- L526 _protected member_ `TSharedPtr<SDetailTree> DetailTree;` — Tree view
- L528 _protected member_ `FDetailNodeList RootTreeNodes;` — Root tree nodes visible in the tree
- L530 _protected member_ `TSharedPtr<SBox> ExternalOverlayContainer;` — A container for external overlays provided by display managers.
- L532 _protected member_ `FIsPropertyVisible IsPropertyVisibleDelegate;` — Delegate executed to determine if a property should be visible
- L534 _protected member_ `FIsCustomRowVisible IsCustomRowVisibleDelegate;` — Delegate executed to determine if a custom row should be visible.
- L536 _protected member_ `FIsPropertyReadOnly IsPropertyReadOnlyDelegate;` — Delegate executed to determine if a property should be read-only
- L538 _protected member_ `FIsCustomRowReadOnly IsCustomRowReadOnlyDelegate;` — Delegate executed to determine if a custom row should be read-only.
- L540 _protected member_ `FIsPropertyEditingEnabled IsPropertyEditingEnabledDelegate;` — Delegate called to see if a property editing is enabled
- L542 _protected member_ `mutable FOnFinishedChangingProperties OnFinishedChangingPropertiesDelegate;` — Delegate called when the details panel finishes editing a property (after post edit change is called)
- L544 _protected member_ `FDetailColumnSizeData ColumnSizeData;` — Container for passing around column size data to rows in the tree (each row has a splitter which can affect the column size)
- L546 _protected member_ `TWeakPtr<FPropertyNode> ColorPropertyNode;` — The property node that the color picker is currently editing.
- L548 _protected member_ `TSharedPtr<IPropertyUtilities> PropertyUtilities;` — Settings for this view
- L550 _protected member_ `TSharedPtr<IPropertyGenerationUtilities> PropertyGenerationUtilities;` — Gets internal utilities for generating property layouts.
- L552 _protected member_ `TSharedPtr<SDetailNameArea> NameArea;` — The name area which is not recreated when selection changes
- L554 _protected member_ `FDetailFilter CurrentFilter;` — The current filter
- L556 _protected member_ `FOnGetDetailCustomizationInstance GenericLayoutDelegate;` — Delegate called to get generic details not specific to an object being viewed
- L558 _protected member_ `TArray<FSimpleDelegate> DeferredActions;` — Actions that should be executed next tick
- L560 _protected member_ `FRootPropertyNodeList RootNodesPendingKill;` — Root tree nodes that needs to be destroyed when safe
- L562 _protected member_ `TSharedPtr<IDetailKeyframeHandler> KeyframeHandler;` — The handler for the keyframe UI, determines if the key framing UI should be displayed.
- L564 _protected member_ `TSharedPtr<IDetailPropertyExtensionHandler> ExtensionHandler;` — Property extension handler returns additional UI to apply after the customization is applied to the property.
- L566 _protected member_ `TSharedPtr<IDetailPropertyChildrenCustomizationHandler> ChildrenCustomizationHandler;` — Property children customization handler allows to customize property's children.
- L568 _protected member_ `TWeakPtr<FDetailTreeNode> CurrentlyHighlightedNode;` — The tree node that is currently highlighted, may be none.
- L570 _protected member_ `TArray<FAnimatingNodeCollection> CurrentlyAnimatingNodeCollections;` — The list of nodes whose widgets should be animating.
- L576 _protected member_ `TSharedPtr<FDetailsDisplayManager> DisplayManager;` — The @code DetailsDisplayManager @endcode which provides an API to manage some of the characteristics of the details display
- L579 _protected member_ `FStringPrefixTree ExpandedDetailNodes;` — Current set of expanded detail nodes (by path) that should be saved when the details panel closes
- L580 _protected member_ `FStringPrefixTree PreSearchExpandedItems;`
- L581 _protected member_ `FStringPrefixTree PreSearchExpandedCategories;`
- L584 _protected member_ `FOnDisplayedPropertiesChanged OnDisplayedPropertiesChangedDelegate;` — Executed when the tree is refreshed
- L586 _protected member_ `int32 NumVisibleTopLevelObjectNodes;`
- L589 _protected member_ `FDelegateHandle PropertyPermissionListChangedDelegate;` — Used to refresh the tree when the allow list filter changes
- L590 _protected member_ `FDelegateHandle PropertyPermissionListEnabledDelegate;`
- L593 _protected member_ `FDelegateHandle OnCultureChangedDelegate;` — Used to refresh the tree when the language changes
- L596 _protected member_ `FSimpleDelegate CustomFilterDelegate;` — Delegate for overriding the show modified filter
- L597 _protected member_ `FText CustomFilterLabel;`
- L600 _protected member_ `bool bIsLocked : 1;` — True if this property view is currently locked (I.E The objects being observed are not changed automatically due to user selection)
- L603 _protected member_ `bool bHasOpenColorPicker : 1;` — Whether or not this instance of the details view opened a color picker and it is not closed yet
- L606 _protected member_ `bool bDisableCustomDetailLayouts : 1;` — True if we want to skip generation of custom layouts for displayed object
- L609 _protected member_ `bool bCustomFilterActive : 1;` — When overriding show modified, you can't use the filter state to determine what is overridden anymore. Use this variable instead.
- L612 _protected member_ `bool bPendingCleanupTimerSet : 1;` — Timer has already been set to be run next tick
- L615 _protected member_ `bool bRunningDeferredActions : 1;` — Are we currently running deferred actions?
- L618 _protected member_ `FTimerHandle PendingRefreshTimerHandle;` — Handle to the pending refresh request, if any
- L620 _protected member_ `mutable TSharedPtr<FEditConditionParser> EditConditionParser;`
- L623 _protected member_ `TArray<TSharedRef<IClassViewerFilter>> ClassViewerFilters;` — Optional custom filter(s) to be applied when selecting values for class properties
- L626 _protected member_ `FOnValidateDetailsViewPropertyNodes CustomValidatePropertyNodesFunction;` — The EnsureDataIsValid function can be skipped with this member, if set. Useful if your implementation doesn't require this kind of validation each Tick.
- L629 _protected member_ `TSharedPtr<FUICommandList> InternalCommands;` — Internal details commands

#### struct `SDetailsViewBase::FAnimatingNodeCollection`  
`struct FAnimatingNodeCollection`  
_L238-304_
- desc: Contains one or more nodes being animated by a single timer.
- L240 _public function_ `FAnimatingNodeCollection() : BatchId(FGuid::NewGuid()) , CreationTime(FPlatformTime::Seconds())`
- L247 _public prototype_ `explicit FAnimatingNodeCollection(const TConstArrayView<TSharedPtr<FPropertyPath>>& InNodePaths, const FGuid& InBatchId = FGuid());` — Creates a collection for the given node(s). If a BatchId is not specified, it's calculated based on the provided nodes.
- L249 _public member_ `TArray<TSharedPtr<FPropertyPath>> NodePaths;`
- L252 _public member_ `FGuid BatchId;` — Required id for tracking and removal (Property Nodes aren't reliable), which also allow multiple nodes to be part of the same animation.
- L254 _public member_ `FTimerHandle NodeTimer;`
- L257 _public prototype_ `static FGuid GetIdForNodePath(const TSharedPtr<FPropertyPath>& InNodePath);` — Utility function that provides a deterministic Id for the given NodePath.
- L260 _public prototype_ `bool IsValid() const;` — Get validity of this AnimatingNode, determined by it's node path.
- L262 _public function_ `bool operator==(const FAnimatingNodeCollection& Other) const`
- L291 _public function_ `bool operator!=(const FAnimatingNodeCollection& Other) const`
- L297 _public prototype_ `void ResetElapsedSeconds();` — Effectively resets the stored animation time.
- L299 _public prototype_ `float GetElapsedSeconds() const;`
- L303 _private member_ `double CreationTime = 0.0f;` — The time at which this FAnimatingNodeCollection was created, useful for resuming animation on widget reconstruction.

#### Free symbols / members of external scopes

- L46 _typedef_ `typedef STreeView< TSharedRef<FDetailTreeNode> > SDetailTree;`

### `Source/Editor/PropertyEditor/Private/SPropertyTreeViewImpl.h` (Private)


#### class `SPropertyTreeViewImpl`  
`class SPropertyTreeViewImpl : public SCompoundWidget`  
_L24-365_
- inherits: `SCompoundWidget`
- L27 _public function_ `SLATE_BEGIN_ARGS( SPropertyTreeViewImpl ) : _IsLockable(true) , _HiddenPropertyVis( false ) , _AllowFavorites(true) , _AllowSearch( true ) , _ShowTopLevelNodes( true ) , _NotifyHook( NULL ) , _NameColumnWidth( 0.20f ) , _OnPropertySelectionChanged() , _OnPropertyMiddleClicked() , _ConstructExternalColumnHeaders() , _ConstructExternalColumnCell()`
- L41 _public prototype_ `SLATE_ARGUMENT( bool, IsLockable ) SLATE_ARGUMENT( bool, HiddenPropertyVis );`
- L43 _public prototype_ `SLATE_ARGUMENT( bool, AllowFavorites ) SLATE_ARGUMENT( bool, AllowSearch ) SLATE_ARGUMENT( bool, ShowTopLevelNodes ) SLATE_ARGUMENT( FNotifyHook*, NotifyHook ) SLATE_ARGUMENT( float, NameColumnWidth ) SLATE_EVENT( FOnPropertySelectionChanged, OnPropertySelectionChanged ) SLATE_EVENT( FOnPropertyClicked, OnPropertyMiddleClicked ) SLATE_EVENT( FConstructExternalColumnHeaders, ConstructExternalColumnHeaders ) SLATE_EVENT( FConstructExternalColumnCell, ConstructExternalColumnCell ) SLATE_END_ARGS() SPropertyTreeViewImpl();`
- L59 _public prototype_ `void Construct(const FArguments& InArgs);` — Constructs the property view widgets
- L62 _public prototype_ `virtual void RequestRefresh();` — Tells the property treeview to refresh its elements during the next tick
- L69 _public prototype_ `virtual void SetObjectArray( const TArray<UObject*>& InObjects );` — Sets the objects that this property view will observe @param InObjects	The list of objects to observe
- L71 _public prototype_ `virtual TSharedRef< FPropertyPath > GetRootPath() const;`
- L73 _public prototype_ `virtual void SetRootPath( const TSharedPtr< FPropertyPath >& Path );`
- L80 _public prototype_ `virtual void ReplaceObjects( const TMap<UObject*, UObject*>& OldToNewObjectMap );` — Replaces objects being observed by the view with new objects @param OldToNewObjectMap	Mapping from objects to replace to their replacement
- L87 _public prototype_ `virtual void RemoveDeletedObjects( const TArray<UObject*>& DeletedObjects );` — Removes objects from the view because they are about to be deleted @param DeletedObjects	The objects to delete
- L94 _public prototype_ `virtual void RemoveInvalidActors( const TSet<AActor*>& ValidActors );` — Removes actors from the property nodes object array which are no longer available @param ValidActors	The list of actors which are still valid
- L101 _public prototype_ `virtual void ToggleFavorite( const TSharedRef< class FPropertyEditor >& PropertyEditor );` — Marks or unmarks a property node as a favorite. @param InPropertyNode	The node to toggle favorite on
- L106 _public function_ `virtual bool AreFavoritesEnabled() const` — Returns true if favorites are enabled for this property view
- L114 _public prototype_ `virtual void CreateColorPickerWindow( const TSharedRef< class FPropertyEditor >& PropertyEditor, bool bUseAlpha );` — Creates the color picker window for this property view. @param Node				The slate property node to edit. @param bUseAlpha			Whether or not alpha is supported
- L119 _public function_ `virtual bool IsLocked() const` — Returns true if the property window is locked and cant have its observed objects changed
- L122 _public function_ `virtual FNotifyHook* GetNotifyHook() const` — Returns the notify hook to use when properties change
- L125 _public prototype_ `virtual void SetIsPropertyVisible( FIsPropertyVisible IsPropertyVisibleDelegate );` — Allows setting a custom delegate for deciding property visibility
- L128 _public prototype_ `virtual void SetOnObjectArrayChanged(FOnObjectArrayChanged OnObjectArrayChangedDelegate);` — Sets the callback for when the property view changes
- L131 _public prototype_ `virtual void SaveExpandedItems();` — Saves the expansion state of the property tree
- L134 _public prototype_ `virtual void SaveColumnWidths();` — Saves the widths of the columns in the property view
- L137 _public function_ `virtual FString GetTitle() const` — Gets the title for this property view based on objects being observed
- L140 _public prototype_ `virtual void ExpandAllNodes();` — Expands all top level nodes
- L143 _public prototype_ `void EnqueueDeferredAction( FSimpleDelegate& DeferredAction );` — Enqueues an action to be executed next tick
- L152 _public prototype_ `void SetFromExistingTree( TSharedPtr<FObjectPropertyNode> RootNode, TSharedPtr<FPropertyNode> PropertyToView );` — Sets the property tree to display from a node tree that always exists. This puts the view into a mode where it does not refresh or rebuild the tree because it is managed externally @param RootNode			The root of the existing property tree @param PropertyToView	The root of the displayed tree
- L157 _public prototype_ `virtual void SetFilterText( const FText& InFilterText );` — Sets the filter text to the given value.
- L160 _public prototype_ `void OnFilterTextChanged( const FText& InFilterText );` — Called when the filter text changes.  This filters specific property nodes out of view
- L170 _public prototype_ `virtual bool IsPropertySelected( const FString& InName, const int32 InArrayIndex = INDEX_NONE);` — Checks if the property or a child property is selected. @param InName			The name of the property. @param InArrayIndex		The array index of the property. @return true if the Property is selected.
- L181 _public prototype_ `virtual bool IsPropertyOrChildrenSelected( const FString& InName, const int32 InArrayIndex = INDEX_NONE, const bool CheckChildren = true );` — Checks if the property or a child property is selected. @param InName			The name of the property. @param InArrayIndex		The array index of the property. @param CheckChildren		true if children should be checked. @return true if the Property or a child is selected.
- L186 _private prototype_ `void OnPermissionListUpdated(TSoftObjectPtr<const UStruct>, FName);` — Delegate called when the property editor permission list is updated
- L189 _private prototype_ `void RestoreExpandedItems();` — Restores the expansion state in the tree for a specific object set
- L192 _private prototype_ `void RestoreColumnWidths();` — Restores the widths of the columns in the property view
- L195 _private prototype_ `void UpdateTopLevelPropertyNodes( TSharedPtr<FPropertyNode> FirstVisibleNode );` — Updates the top level property nodes.  The root nodes for the treeview.
- L198 _private prototype_ `void PreSetObject();` — Called before during SetObjectArray before we change the objects being observed
- L201 _private prototype_ `void PostSetObject();` — Called at the end of SetObjectArray after we change the objects being observed
- L204 _private prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;` — SWidget interface
- L213 _private prototype_ `void OnGetChildrenForPropertyNode( TSharedPtr<FPropertyNode> InPropertyNode, TArray< TSharedPtr<FPropertyNode> >& OutChildren );` — Function called through a delegate on the property TreeView to request children of a property node @param InPropertyNode	The property node to get children from @param OutChildren		The list of children of InPropertyNode that should be visible
- L216 _private prototype_ `bool IsPropertyNodeVisible(TSharedPtr<FPropertyNode> InPropertyNode);` — Check if a Property Node should be shown in the property tree if we have any external IsPropertyVisible delegates or permission lists
- L224 _private prototype_ `void OnGetChildFavoritesForPropertyNode( TSharedPtr<FPropertyNode> InPropertyNode, TArray< TSharedPtr<FPropertyNode> >& OutChildren );` — Function called through a delegate on the favorites TreeView to request children of a property node @param InPropertyNode	The property node to get children from @param OutChildren		The list of children of InPropertyNode that should be visible
- L227 _private prototype_ `FReply OnToggleFavoritesClicked();` — Called when the toggle favorites button is clicked
- L230 _private prototype_ `FReply OnLockButtonClicked();` — Called when the locked button is clicked
- L237 _private prototype_ `void FilterView( const FString& InFilterText );` — Hides or shows properties based on the passed in filter text @param InFilterText	The filter text
- L240 _private prototype_ `EVisibility OnGetFavoritesVisibility() const;` — Called when the favorites tree requests its visibility state
- L243 _private prototype_ `const FSlateBrush* OnGetFilterButtonImageResource() const;` — Returns the name of the image used for the icon on the filter button
- L246 _private prototype_ `const FSlateBrush* OnGetFavoriteButtonImageResource() const;` — Returns the name of the image used for the icon on the favorites button
- L249 _private prototype_ `const FSlateBrush* OnGetLockButtonImageResource() const;` — Returns the name of the image used for the icon on the locked button
- L252 _private prototype_ `void ConstructPropertyTree();` — Reconstructs the entire property tree widgets
- L257 _private prototype_ `void MarkFavorites();` — Recursively marks nodes which should be favorite starting from the root
- L265 _private prototype_ `void MarkFavoritesInternal( TSharedPtr<FPropertyNode> InPropertyNode, bool bAnyParentIsFavorite );` — Recursively marks nodes which should be favorite @param InPropertyNode	The property node to start marking favorites from @param bAnyParentIsFavorite	true of any parent of InPropertyNode is already marked as a favorite
- L272 _private prototype_ `TSharedRef<ITableRow> CreatePropertyEditor( TSharedPtr<FPropertyNode> InPropertyNode, const TSharedPtr<STableViewBase>& OwnerTable );` — Creates a property editor (the visual portion of a PropertyNode), for a specific property node @param InPropertyNode	The property node to create the visual for
- L277 _private prototype_ `TSharedRef<ITableRow> OnGenerateRowForPropertyTree( TSharedPtr<FPropertyNode> InPropertyNode, const TSharedRef<STableViewBase>& OwnerTable );` — Returns an SWidget used as the visual representation of a node in the property treeview.
- L280 _private prototype_ `void OnSelectionChanged( TSharedPtr<FPropertyNode> InPropertyNode, ESelectInfo::Type SelectInfo );` — Callback when property selection changes.
- L285 _private prototype_ `void LoadFavorites();` — Loads favorites from INI
- L290 _private prototype_ `void SaveFavorites();` — Saves favorites to INI
- L298 _private prototype_ `void RequestItemExpanded( TSharedPtr<FPropertyNode> PropertyNode, bool bExpand, bool bRecursiveExpansion = false );` — Requests that a property node's expansion state be changed due to being filtered @param PropertyNode	The property node to change expansion state on @param bExpand		true to expand the node, false to collapse it
- L302 _private member_ `TSet<FString> FavoritesList;` — List of properties which are favorites
- L304 _private member_ `TSet< TSharedPtr<FPropertyNode> > PreFilterExpansionSet;` — Stored set of expanded nodes before a filter was set
- L306 _private member_ `TMap< TSharedPtr<FPropertyNode>, bool > FilteredNodesRequestingExpansionState;` — Map of nodes that are requesting an automatic expansion/collapse due to being filtered
- L308 _private member_ `TArray< TSharedPtr<FPropertyNode> > TopLevelPropertyNodes;` — Top level property nodes which are visible in the TreeView. These are always category nodes belonging to the RootPropertyNode
- L310 _private member_ `TArray< TSharedPtr<FPropertyNode> > TopLevelFavorites;` — Top level favorite property nodes. These are root nodes of the favorite tree view
- L312 _private member_ `TArray<FSimpleDelegate> DeferredActions;` — Actions that should be executed next tick
- L314 _private member_ `TSharedPtr<FObjectPropertyNode> RootPropertyNode;` — The root property node of the property tree for a specific set of UObjects
- L316 _private member_ `TSharedPtr<SPropertyTree> PropertyTree;` — Our property treeview
- L318 _private member_ `TSharedPtr<SPropertyTree> FavoritesTree;` — Our property favorites treeview
- L320 _private member_ `TSharedPtr<SSearchBox> FilterTextBox;` — The filter text box
- L322 _private member_ `TSharedPtr< SHeaderRow > ColumnHeaderRow;` — The header row for the primary trees columns
- L324 _private member_ `TSharedPtr<class IPropertyUtilities> PropertySettings;` — Settings for this property view
- L326 _private member_ `FString CurrentFilterText;` — The current filter text
- L328 _private member_ `FString Title;` — The title of the property view (for a window title)
- L330 _private member_ `FNotifyHook* NotifyHook;` — Notify hook to call when properties are changed
- L332 _private member_ `bool bHasActiveFilter;` — True if there is an active filter (text in the filter box)
- L334 _private member_ `bool bLockable;` — True if this property view can be locked
- L336 _private member_ `bool bIsLocked;` — True if this property view is currently locked (I.E The objects being observed are not changed automatically due to user selection)
- L338 _private member_ `bool bFavoritesAllowed;` — True if this property view allows favorites to visible and modified
- L340 _private member_ `bool bFavoritesEnabled;` — True if favorites are currently enabled
- L342 _private member_ `bool bAllowSearch;` — True if we allow searching
- L344 _private member_ `bool bForceHiddenPropertyVisibility;` — True if the property view shows all properties regardless of their flags
- L346 _private member_ `bool bNodeTreeExternallyManaged;` — Whether or not this tree view manages and creates property nodes or whether the nodes are externally managed
- L348 _private member_ `bool bShowTopLevelPropertyNodes;` — Whether or not this tree should ever display top level property nodes as categories
- L350 _private member_ `FOnObjectArrayChanged OnObjectArrayChanged;` — Callback to send when the property view changes
- L352 _private member_ `FOnPropertySelectionChanged OnPropertySelectionChanged;` — Callback when property selection changes.
- L354 _private member_ `FOnPropertyClicked OnPropertyMiddleClicked;` — Callback when a property is clicked with the middle mouse button by the user
- L356 _private member_ `FIsPropertyVisible IsPropertyVisible;` — Callback to see if a property is visible
- L358 _private member_ `float InitialNameColumnWidth;` — The initial width of the name column
- L360 _private member_ `TSharedRef< class FPropertyPath > RootPath;` — The path to the property node that should be treated as the root
- L362 _private member_ `FConstructExternalColumnHeaders ConstructExternalColumnHeaders;` — Called to construct any extra column headers external code wants to expose
- L364 _private member_ `FConstructExternalColumnCell ConstructExternalColumnCell;` — Called to construct any the cell contents for columns created by external code

#### Free symbols / members of external scopes

- L22 _typedef_ `typedef STreeView< TSharedPtr<FPropertyNode> > SPropertyTree;`

### `Source/Editor/PropertyEditor/Private/SSingleProperty.h` (Private)


#### class `SSingleProperty`  
`class SSingleProperty : public ISinglePropertyView`  
_L17-106_
- inherits: `ISinglePropertyView`
- L20 _public function_ `SLATE_BEGIN_ARGS( SSingleProperty ) : _Object(NULL) , _StructData(NULL) , _NotifyHook( NULL ) , _PropertyFont( FAppStyle::GetFontStyle( PropertyEditorConstants::PropertyFontStyle ) ) , _NamePlacement( EPropertyNamePlacement::Left ) , _NameOverride() , _bShouldHideAssetThumbnail(false) , _bShouldHideResetToDefault(false)`
- L31 _public prototype_ `SLATE_ARGUMENT( UObject*, Object ) SLATE_ARGUMENT(TSharedPtr<IStructureDataProvider>, StructData) SLATE_ARGUMENT( FName, PropertyName ) SLATE_ARGUMENT( FNotifyHook*, NotifyHook ) SLATE_ARGUMENT( FSlateFontInfo, PropertyFont ) SLATE_ARGUMENT( EPropertyNamePlacement::Type, NamePlacement ) SLATE_ARGUMENT( FText, NameOverride ) SLATE_ARGUMENT( bool, bShouldHideAssetThumbnail ) SLATE_ARGUMENT( bool, bShouldHideResetToDefault ) SLATE_END_ARGS() void Construct( const FArguments& InArgs );`
- L45 _public function_ `virtual bool HasValidProperty() const override` — ISinglePropertyView interface
- L46 _public prototype_ `virtual void SetObject( UObject* InObject ) override;`
- L47 _public prototype_ `virtual void SetStruct( const TSharedPtr<IStructureDataProvider>& InStruct ) override;`
- L48 _public prototype_ `virtual void SetOnPropertyValueChanged( const FSimpleDelegate& InOnPropertyValueChanged ) override;`
- L55 _public prototype_ `void ReplaceObjects( const TMap<UObject*, UObject*>& OldToNewObjectMap );` — Replaces objects being observed by the view with new objects @param OldToNewObjectMap	Mapping from objects to replace to their replacement
- L62 _public prototype_ `void RemoveDeletedObjects( const TArray<UObject*>& DeletedObjects );` — Removes objects from the view because they are about to be deleted @param DeletedObjects	The objects to delete
- L65 _public prototype_ `void CreateColorPickerWindow( const TSharedRef< class FPropertyEditor >& PropertyEditor, bool bUseAlpha );` — Creates a color picker window for a property node
- L68 _public function_ `FNotifyHook* GetNotifyHook() const` — @return The notify hook used by the property
- L70 _public function_ `virtual TSharedPtr<IPropertyHandle> GetPropertyHandle() const override`
- L77 _private prototype_ `void SetColorPropertyFromColorPicker(FLinearColor NewColor);` — Sets the color if this is a color property @param NewColor The color to set
- L84 _private prototype_ `bool GeneratePropertyCustomization();` — Generates the SingleProperty customization @return true if valid property and widget has been generated
- L88 _private member_ `TSharedPtr<FComplexPropertyNode> RootPropertyNode;` — The root property node for the value node (contains the root object
- L90 _private member_ `TSharedPtr<FPropertyNode> ValueNode;` — The node for the property being edited
- L92 _private member_ `TSharedPtr<class FSinglePropertyUtilities> PropertyUtilities;` — Property utilities for handling common functionality of property editors
- L94 _private member_ `FText NameOverride;` — Name override to display instead of the property name
- L96 _private member_ `FSlateFontInfo PropertyFont;` — Font to use
- L98 _private member_ `FNotifyHook* NotifyHook;` — Notify hook to use when editing values
- L100 _private member_ `FName PropertyName;` — Name of the property
- L102 _private member_ `EPropertyNamePlacement::Type NamePlacement;` — Location of the name in the view
- L103 _private member_ `TSharedPtr<class IPropertyHandle> PropertyHandle;`
- L105 _private member_ `bool bShouldHideResetToDefault;` — Whether the 'reset to default' button should be hidden

### `Source/Editor/PropertyEditor/Private/SStructureDetailsView.h` (Private)


#### class `SStructureDetailsView`  
`class SStructureDetailsView : public SDetailsViewBase, public IStructureDetailsView`  
_L18-131_
- inherits: `SDetailsViewBase,IStructureDetailsView`
- L23 _public function_ `SLATE_BEGIN_ARGS(SStructureDetailsView) : _DetailsViewArgs()`
- L27 _public prototype_ `SLATE_ARGUMENT(FDetailsViewArgs, DetailsViewArgs) SLATE_ARGUMENT(FText, CustomName) SLATE_END_ARGS() ~SStructureDetailsView();` — User defined arguments for the details view
- L37 _public prototype_ `void Construct(const FArguments& InArgs);` — Constructs the property view widgets.
- L39 _public prototype_ `UStruct* GetBaseScriptStruct() const;`
- L41 _public prototype_ `virtual bool IsConnected() const override;`
- L43 _public function_ `virtual bool DontUpdateValueWhileEditing() const override`
- L48 _public function_ `virtual bool ContainsMultipleTopLevelObjects() const override`
- L57 _public function_ `virtual IDetailsView* GetDetailsView() override`
- L62 _public function_ `virtual TSharedPtr<SWidget> GetWidget() override`
- L67 _public prototype_ `virtual void SetStructureData(TSharedPtr<FStructOnScope> InStructData) override;`
- L69 _public prototype_ `virtual void SetStructureProvider(TSharedPtr<IStructureDataProvider> StructProvider) override;`
- L71 _public function_ `virtual FOnFinishedChangingProperties& GetOnFinishedChangingPropertiesDelegate() override`
- L76 _public function_ `TSharedPtr<const IStructureDataProvider> GetStructureProvider() const override`
- L80 _public prototype_ `virtual void ForceRefresh() override;` — Causes the details view to be refreshed (new widgets generated) with the current set of objects
- L82 _public prototype_ `virtual void InvalidateCachedState() override;` — Invalidates cached state such as the "revert to default" arrow and edit conditions, without rebuilding the entire panel.
- L83 _public function_ `virtual void MoveScrollOffset(int32 DeltaOffset) override`
- L86 _public prototype_ `virtual const TArray< TWeakObjectPtr<UObject> >& GetSelectedObjects() const override;` — IDetailsView interface
- L87 _public prototype_ `virtual const TArray< TWeakObjectPtr<AActor> >& GetSelectedActors() const override;`
- L88 _public prototype_ `virtual const struct FSelectedActorInfo& GetSelectedActorInfo() const override;`
- L90 _public function_ `virtual bool HasClassDefaultObject() const override`
- L95 _public function_ `virtual void SetOnObjectArrayChanged(FOnObjectArrayChanged OnObjectArrayChangedDelegate) override`
- L96 _public function_ `virtual void SetObjects(const TArray<UObject*>& InObjects, bool bForceRefresh = false, bool bOverrideLock = false) override`
- L97 _public function_ `virtual void SetObjects(const TArray< TWeakObjectPtr< UObject > >& InObjects, bool bForceRefresh = false, bool bOverrideLock = false) override`
- L98 _public function_ `virtual void SetObject(UObject* InObject, bool bForceRefresh = false) override`
- L99 _public function_ `virtual void RemoveInvalidObjects() override`
- L100 _public function_ `virtual void SetObjectPackageOverrides(const TMap<TWeakObjectPtr<UObject>, TWeakObjectPtr<UPackage>>& InMapping) override`
- L101 _public function_ `virtual void SetRootObjectCustomizationInstance(TSharedPtr<IDetailRootObjectCustomization> InRootObjectCustomization) override`
- L102 _public function_ `virtual TSharedPtr<class IDetailRootObjectCustomization> GetRootObjectCustomization() const override`
- L103 _public function_ `virtual void SetObjectFilter(TSharedPtr<FDetailsViewObjectFilter> InFilter) override`
- L104 _public function_ `virtual void SetClassViewerFilters(const TArray<TSharedRef<class IClassViewerFilter>>& InFilters) override`
- L105 _public function_ `virtual bool IsGroupFavorite(FStringView GroupPath) const`
- L106 _public function_ `virtual void SetGroupFavorite(FStringView GroupPath, bool IsFavorite)`
- L107 _public function_ `virtual bool IsCustomBuilderFavorite(FStringView Path) const`
- L108 _public function_ `virtual void SetCustomBuilderFavorite(FStringView Path, bool IsFavorite)`
- L111 _public prototype_ `virtual FRootPropertyNodeList& GetRootNodes() override;` — This is required by the base class but there is only ever one root node in a structure details view
- L113 _public prototype_ `TSharedPtr<class FComplexPropertyNode> GetRootNode();`
- L114 _public prototype_ `const TSharedPtr<class FComplexPropertyNode> GetRootNode() const;`
- L116 _public prototype_ `virtual void SetCustomName(const FText& Text) override;`
- L120 _protected prototype_ `virtual void CustomUpdatePropertyMap(TSharedPtr<FDetailLayoutBuilderImpl>& InDetailLayout) override;`
- L122 _protected prototype_ `EVisibility GetPropertyEditingVisibility() const;`
- L125 _protected prototype_ `const FSlateBrush* GetViewOptionsBadgeIcon() const;` — Get the badge for the view options icon (if there are any options active
- L128 _private member_ `TSharedPtr<IStructureDataProvider> StructProvider;`
- L129 _private member_ `FRootPropertyNodeList RootNodes;`
- L130 _private member_ `FText CustomName;`

### `Source/Editor/PropertyEditor/Private/StringPrefixTree.h` (Private)


#### class `FStringPrefixTree`  
`class FStringPrefixTree`  
_L25-118_
- desc: A string prefix tree is conceptually similar to a trie. However, instead of adding a new nodes per single character, nodes encode a string prefix, and entries are built up by concatenating the path to the node. For example, if we add the entries "ABC", "AC", and "D" to the tree, we will have: <root> |- "A" | |- "B" | | |- "C" * | |- "C" * |- "D" * Where only the nodes marked with * are leaf nodes. An entry is considered to be in the list only if it is a leaf node. This tree structure allows for long strings that may have long similar sections to be searched far faster than storing them in eg. a set.
- L29 _public prototype_ `FStringPrefixTree() = default;`
- L30 _public prototype_ `~FStringPrefixTree();`
- L35 _public prototype_ `void Insert(FStringView ToAdd);` — Insert the given string into the tree.
- L40 _public prototype_ `void InsertAll(const TArray<FString>& Array);` — Insert all the strings in the array.
- L45 _public prototype_ `void InsertAll(const TArray<FStringView>& Array);` — Insert all the strings in the array.
- L50 _public prototype_ `void Remove(FStringView ToRemove);` — Remove an entry. This can fragment the tree and should be avoided.
- L55 _public prototype_ `void Clear();` — Clear the tree.
- L60 _public prototype_ `bool Contains(FStringView Entry) const;` — Does the tree contain the given entry?
- L66 _public prototype_ `bool AnyStartsWith(FStringView Prefix) const;` — Does any entry start with the given prefix. Eg. if the tree contains "Foobar", this would return true if given "Foo".
- L72 _public prototype_ `int32 Size() const;` — Returns the number of leaf entries in the tree. Equivalent to the number of items added via Insert() or InsertAll().
- L77 _public prototype_ `TArray<FString> GetAllEntries() const;` — Dump all leaf nodes into an array.
- L83 _public prototype_ `int32 NumNodes() const;` — For testing and debugging. The number of internal nodes. This is a different (usually larger) number than the number of entries.
- L89 _public prototype_ `FString DumpToString() const;` — For testing and debugging. Pretty prints the internal tree structure as a string.
- L117 _private member_ `FNode Root;`

#### struct `FStringPrefixTree::FNode`  
`struct FNode`  
_L93-115_
- L95 _public member_ `FString Prefix;`
- L96 _public member_ `TArray<FNode> Children;`
- L97 _public member_ `bool IsLeaf = false;`
- L99 _public prototype_ `FNode() = default;`
- L100 _public prototype_ `~FNode();`
- L102 _public prototype_ `void Insert(FStringView ToAdd);`
- L103 _public prototype_ `void Remove(FStringView ToRemove);`
- L104 _public prototype_ `bool Contains(FStringView ToFind) const;`
- L105 _public prototype_ `bool AnyStartsWith(FStringView ToFind) const;`
- L106 _public prototype_ `int32 Size() const;`
- L108 _public prototype_ `int32 NumNodes() const;`
- L109 _public prototype_ `void GetAllEntries(const FString& CurrentPrefix, TArray<FString>& OutEntries) const;`
- L110 _public prototype_ `void DumpToString(FStringBuilderBase& Builder, TArray<bool, TInlineAllocator<32>>& DrawLines, bool bLastChild) const;`
- L114 _private prototype_ `bool CanPrune() const;` — we can prune any node that is not a leaf and does not contain any children which are leaves anymore

### `Source/Editor/PropertyEditor/Private/StructurePropertyNode.h` (Private)


#### class `FStructurePropertyNode`  
`class FStructurePropertyNode : public FComplexPropertyNode`  
_L15-343_
- inherits: `FComplexPropertyNode`
- L18 _public function_ `FStructurePropertyNode() : FComplexPropertyNode()`
- L19 _public prototype_ `virtual ~FStructurePropertyNode() override = default;`
- L21 _public function_ `virtual FStructurePropertyNode* AsStructureNode() override`
- L22 _public function_ `virtual const FStructurePropertyNode* AsStructureNode() const override`
- L24 _public function_ `void RemoveStructure(bool bInDestroySelf = true)`
- L32 _public function_ `void SetStructure(TSharedPtr<FStructOnScope> InStructData)`
- L41 _public function_ `void SetStructure(TSharedPtr<IStructureDataProvider> InStructProvider)`
- L47 _public function_ `bool HasValidStructData() const`
- L53 _public function_ `TSharedPtr<FStructOnScope> GetStructData() const` — Returns just the first structure. Please use GetStructProvider() or GetAllStructureData() when dealing with multiple struct instances.
- L68 _public function_ `void GetAllStructureData(TArray<TSharedPtr<FStructOnScope>>& OutStructs) const`
- L76 _public function_ `TSharedPtr<IStructureDataProvider> GetStructProvider() const`
- L81 _public prototype_ `virtual bool GetReadAddressUncached(const FPropertyNode& InPropertyNode, FReadAddressListData& OutAddresses) const override;`
- L83 _public prototype_ `virtual bool GetReadAddressUncached(const FPropertyNode& InPropertyNode, bool InRequiresSingleSelection, FReadAddressListData* OutAddresses, bool bComparePropertyContents, bool bObjectForceCompare, bool bArrayPropertiesCanDifferInSize) const override;`
- L90 _public function_ `void GetOwnerPackages(TArray<UPackage*>& OutPackages) const`
- L153 _public function_ `virtual const UStruct* GetBaseStructure() const override` — FComplexPropertyNode Interface
- L161 _public function_ `virtual UStruct* GetBaseStructure() override`
- L169 _public function_ `virtual TArray<UStruct*> GetAllStructures() override`
- L189 _public function_ `virtual TArray<const UStruct*> GetAllStructures() const override`
- L208 _public function_ `virtual int32 GetInstancesNum() const override`
- L252 _public function_ `virtual uint8* GetMemoryOfInstance(int32 Index) const override`
- L265 _public function_ `virtual uint8* GetValuePtrOfInstance(int32 Index, const FProperty* InProperty, const FPropertyNode* InParentNode) const override`
- L287 _public function_ `virtual TWeakObjectPtr<UObject> GetInstanceAsUObject(int32 Index) const override`
- L291 _public function_ `virtual EPropertyType GetPropertyType() const override`
- L296 _public function_ `virtual void Disconnect() override`
- L304 _public prototype_ `virtual TSharedPtr<FPropertyNode> GenerateSingleChild(FName ChildPropertyName) override;` — Generates a single child from the provided property name.  Any existing children are destroyed
- L308 _protected prototype_ `virtual EPropertyDataValidationResult EnsureDataIsValid() override;`
- L311 _protected prototype_ `virtual void InitChildNodes() override;` — FPropertyNode interface
- L313 _protected prototype_ `virtual void InitBeforeNodeFlags() override;`
- L314 _protected prototype_ `void InternalInitChildNodes(FName SinglePropertyName);`
- L316 _protected prototype_ `virtual uint8* GetValueBaseAddress(uint8* Base, bool bIsSparseData, bool bIsStruct) const override;`
- L318 _protected function_ `virtual bool GetQualifiedName(FString& PathPlusIndex, const bool bWithArrayIndex, const FPropertyNode* StopParent = nullptr, bool bIgnoreCategories = false) const override`
- L339 _private member_ `TSharedPtr<IStructureDataProvider> StructProvider;`
- L342 _private member_ `TWeakObjectPtr<const UStruct> WeakCachedBaseStruct = nullptr;` — The base struct at the time InitChildNodes() was called.

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyDetails/PropertyDetailsUtilities.h` (Private)


#### class `FPropertyDetailsUtilities`  
`class FPropertyDetailsUtilities : public IPropertyUtilities`  
_L11-35_
- inherits: `IPropertyUtilities`
- L14 _public prototype_ `FPropertyDetailsUtilities(IDetailsViewPrivate& InDetailsView);`
- L16 _public prototype_ `virtual class FNotifyHook* GetNotifyHook() const override;` — IPropertyUtilities interface
- L17 _public prototype_ `virtual bool AreFavoritesEnabled() const override;`
- L18 _public prototype_ `virtual void ToggleFavorite( const TSharedRef< class FPropertyEditor >& PropertyEditor ) const override;`
- L19 _public prototype_ `virtual void CreateColorPickerWindow( const TSharedRef< class FPropertyEditor >& PropertyEditor, bool bUseAlpha ) const override;`
- L20 _public prototype_ `virtual void EnqueueDeferredAction( FSimpleDelegate DeferredAction ) override;`
- L21 _public prototype_ `virtual bool IsPropertyEditingEnabled() const override;`
- L22 _public prototype_ `virtual void ForceRefresh() override;`
- L23 _public prototype_ `virtual void RequestRefresh() override;`
- L24 _public prototype_ `virtual void RequestForceRefresh() override;`
- L25 _public prototype_ `virtual TSharedPtr<class FAssetThumbnailPool> GetThumbnailPool() const override;`
- L26 _public function_ `virtual void NotifyStartedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent) override`
- L27 _public prototype_ `virtual void NotifyFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent) override;`
- L28 _public prototype_ `virtual bool DontUpdateValueWhileEditing() const override;`
- L29 _public prototype_ `const TArray<TWeakObjectPtr<UObject>>& GetSelectedObjects() const override;`
- L30 _public prototype_ `virtual bool HasClassDefaultObject() const override;`
- L31 _public prototype_ `virtual const TArray<TSharedRef<class IClassViewerFilter>>& GetClassViewerFilters() const override;`
- L34 _private member_ `TWeakPtr<IDetailsViewPrivate> DetailsViewPtr;`

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyEditor/PropertyEditorAssetConstants.h` (Private)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace PropertyEditorAssetConstants`
- L8 _variable_ `static const FVector2D ContentBrowserWindowSize(300.0f, 300.0f);` (scope `PropertyEditorAssetConstants`)
- L9 _variable_ `static const FVector2D SceneOutlinerWindowSize(350.0f, 300.0f);` (scope `PropertyEditorAssetConstants`)

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyEditor/PropertyEditorConstants.h` (Private)


#### class `PropertyEditorConstants`  
`class PropertyEditorConstants`  
_L17-35_
- L21 _public member_ `static const FName PropertyFontStyle;`
- L22 _public member_ `static const FName CategoryFontStyle;`
- L24 _public member_ `static const FName MD_Bitmask;`
- L25 _public member_ `static const FName MD_BitmaskEnum;`
- L26 _public member_ `static const FName MD_UseEnumValuesAsMaskValuesInEditor;`
- L28 _public member_ `static constexpr float PropertyRowHeight = 26.0f;`
- L30 _public member_ `static const FText DefaultUndeterminedText;`
- L32 _public prototype_ `static const FSlateBrush* GetOverlayBrush(const TSharedRef<class FPropertyEditor> PropertyEditor);`
- L34 _public prototype_ `static FSlateColor GetRowBackgroundColor(int32 IndentLevel, bool IsHovered);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace PropertyEditor` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::PropertyEditor`)
- L14 _variable_ `constexpr float PulseAnimationLength = 0.5f;` (scope `UE::PropertyEditor::Private`)

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyEditor/PropertyEditorUIFactory.h` (Private)
_(no declarations extracted)_

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyEditor/SPropertyAssetPicker.h` (Private)


#### class `SPropertyAssetPicker`  
`class SPropertyAssetPicker : public SCompoundWidget`  
_L12-37_
- inherits: `SCompoundWidget`
- L15 _public function_ `SLATE_BEGIN_ARGS( SPropertyAssetPicker )`
- L16 _public prototype_ `SLATE_EVENT( FOnGetAllowedClasses, OnGetAllowedClasses ) SLATE_EVENT( FOnAssetSelected, OnAssetSelected ) SLATE_ARGUMENT( TSharedPtr<IPropertyHandle>, PropertyHandle ) SLATE_END_ARGS() void Construct( const FArguments& InArgs );`
- L24 _private prototype_ `FReply OnClicked();`
- L26 _private prototype_ `TSharedRef<SWidget> OnGenerateAssetPicker();`
- L28 _private prototype_ `void OnAssetSelectedFromPicker( const struct FAssetData& AssetData );`
- L29 _private prototype_ `void OnAssetEnterPressedFromPicker( const TArray<struct FAssetData>& AssetData );`
- L32 _private member_ `TSharedPtr< class SMenuAnchor > AssetPickerAnchor;` — Menu anchor for opening and closing the asset picker
- L34 _private member_ `FOnGetAllowedClasses OnGetAllowedClasses;`
- L35 _private member_ `FOnAssetSelected OnAssetSelected;`
- L36 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;`

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyEditor/SPropertyComboBox.h` (Private)


#### class `SPropertyComboBox`  
`class SPropertyComboBox : public SSearchableComboBox`  
_L24-82_
- inherits: `SSearchableComboBox`
- L28 _public function_ `SLATE_BEGIN_ARGS( SPropertyComboBox ) : _Font( FAppStyle::GetFontStyle( PropertyEditorConstants::PropertyFontStyle ) ) , _ShowSearchForItemCount(-1)`
- L32 _public prototype_ `SLATE_ATTRIBUTE( TArray< TSharedPtr< FString > >, ComboItemList ) SLATE_ATTRIBUTE( TArray< bool >, RestrictedList ) SLATE_ATTRIBUTE( FString, VisibleText ) SLATE_ARGUMENT( TArray< TSharedPtr< SToolTip > >, RichToolTipList) SLATE_EVENT( FOnSelectionChanged, OnSelectionChanged ) SLATE_EVENT( FOnComboBoxOpening, OnComboBoxOpening ) SLATE_ARGUMENT( FSlateFontInfo, Font ) SLATE_ARGUMENT( int32, ShowSearchForItemCount ) SLATE_END_ARGS() void Construct( const FArguments& InArgs );`
- L45 _public prototype_ `~SPropertyComboBox();`
- L51 _public prototype_ `DLLEXPORT void SetSelectedItem( const FString& InSelectedItem );` — Sets the currently selected item for the combo box. @param InSelectedItem			The name of the item to select.
- L59 _public prototype_ `void SetItemList(TArray< TSharedPtr< FString > >& InItemList, TArray< TSharedPtr< SToolTip > >& InRichTooltips, TArray<bool>& InRestrictedList);` — Sets the item list for the combo box. @param InItemList			The item list to use. @param InTooltipList		The list of tooltips to use. @param InRestrictedList		The list of restricted items.
- L64 _private prototype_ `void OnSelectionChangedInternal( TSharedPtr<FString> InSelectedItem, ESelectInfo::Type SelectInfo );`
- L66 _private prototype_ `TSharedRef<SWidget> OnGenerateComboWidget( TSharedPtr<FString> InComboString );`
- L68 _private prototype_ `EVisibility GetSearchVisibility() const;`
- L71 _private prototype_ `FReply OnKeyDown( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override;` — SWidget interface
- L76 _private member_ `TArray< TSharedPtr<FString> > ComboItemList;` — List of items in our combo box. Only generated once as combo items dont change at runtime
- L77 _private member_ `TArray< TSharedPtr< SToolTip > > RichToolTips;`
- L78 _private member_ `FOnSelectionChanged OnSelectionChanged;`
- L79 _private member_ `FSlateFontInfo Font;`
- L80 _private member_ `TArray< bool > RestrictedList;`
- L81 _private member_ `int32 ShowSearchForItemCount;`

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyEditor/SPropertyEditor.h` (Private)


#### class `SPropertyEditor`  
`class SPropertyEditor : public SCompoundWidget`  
_L12-29_
- inherits: `SCompoundWidget`
- L15 _public function_ `SLATE_BEGIN_ARGS(SPropertyEditor) : _Font(FAppStyle::GetFontStyle(PropertyEditorConstants::PropertyFontStyle))`
- L18 _public prototype_ `SLATE_ATTRIBUTE(FSlateFontInfo, Font) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FPropertyEditor>& InPropertyEditor);`
- L22 _public prototype_ `void GetDesiredWidth(float& OutMinDesiredWidth, float& OutMaxDesiredWidth) const;`
- L25 _private prototype_ `bool ShouldShowValue(const TSharedRef<FPropertyEditor>& InPropertyEditor) const;`
- L28 _private member_ `TSharedPtr<FPropertyEditor> PropertyEditor;`

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyEditor/SPropertyEditorArray.h` (Private)


#### class `SPropertyEditorArray`  
`class SPropertyEditorArray : public SCompoundWidget`  
_L15-42_
- inherits: `SCompoundWidget`
- L19 _public function_ `SLATE_BEGIN_ARGS(SPropertyEditorArray) : _Font(FAppStyle::GetFontStyle(PropertyEditorConstants::PropertyFontStyle))`
- L22 _public prototype_ `SLATE_ATTRIBUTE(FSlateFontInfo, Font) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FPropertyEditor>& InPropertyEditor);`
- L26 _public prototype_ `void GetDesiredWidth(float& OutMinDesiredWidth, float& OutMaxDesiredWidth) const;`
- L28 _public prototype_ `static bool Supports(const TSharedRef<FPropertyEditor>& InPropertyEditor);`
- L31 _private prototype_ `FText GetArrayTextValue() const;`
- L34 _private prototype_ `bool CanEdit() const;` — @return True if the property can be edited
- L36 _private prototype_ `FReply OnDragDropTarget(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent);`
- L37 _private prototype_ `bool IsValidAssetDropOp(TSharedPtr<FDragDropOperation> InOperation);`
- L38 _private prototype_ `bool WillAddValidElements(TSharedPtr<FDragDropOperation> InOperation);`
- L41 _private member_ `TSharedPtr<FPropertyEditor> PropertyEditor;`

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyEditor/SPropertyEditorArrayItem.h` (Private)


#### struct `FTitleMetadataFormatter`  
`struct FTitleMetadataFormatter`  
_L20-28_
- L22 _public member_ `FText Format;`
- L23 _public member_ `TArray<TSharedPtr<IPropertyHandle>> PropertyHandles;`
- L25 _public prototype_ `FPropertyAccess::Result GetDisplayText(FText& OutText) const;`
- L27 _public prototype_ `static TSharedPtr<FTitleMetadataFormatter> TryParse(TSharedPtr<IPropertyHandle> RootProperty, const FString& TitlePropertyRaw);`

#### class `SPropertyEditorArrayItem`  
`class SPropertyEditorArrayItem : public SCompoundWidget`  
_L30-54_
- inherits: `SCompoundWidget`
- L33 _public function_ `SLATE_BEGIN_ARGS( SPropertyEditorArrayItem ) : _Font( FAppStyle::GetFontStyle( PropertyEditorConstants::PropertyFontStyle ) )`
- L36 _public prototype_ `SLATE_ATTRIBUTE( FSlateFontInfo, Font ) SLATE_END_ARGS() static bool Supports( const TSharedRef< class FPropertyEditor >& PropertyEditor );`
- L41 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef< class FPropertyEditor>& InPropertyEditor );`
- L43 _public prototype_ `void GetDesiredWidth( float& OutMinDesiredWidth, float& OutMaxDesiredWidth );`
- L46 _private prototype_ `FText GetValueAsString() const;`
- L49 _private prototype_ `bool CanEdit() const;` — @return True if the property can be edited
- L52 _private member_ `TSharedPtr<FPropertyEditor> PropertyEditor;`
- L53 _private member_ `TSharedPtr<FTitleMetadataFormatter> TitlePropertyFormatter;`

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyEditor/SPropertyEditorAsset.h` (Private)


#### class `SPropertyEditorAsset`  
`class SPropertyEditorAsset : public SCompoundWidget`  
_L35-483_
- inherits: `SCompoundWidget`
- desc: A widget used to edit Asset-type properties (UObject-derived properties). Can also be used (with a NULL FPropertyEditor) to edit a raw weak object pointer.
- L55 _public function_ `SLATE_BEGIN_ARGS(SPropertyEditorAsset) : _DisplayThumbnail(true) , _DisplayUseSelected(true) , _DisplayTransient(true) , _DisplayBrowse(true) , _EnableContentPicker(true) , _DisplayCompactSize(true) , _ThumbnailPool(nullptr) , _ThumbnailSize(FIntPoint(48, 48)) , _ObjectPath() , _Class(nullptr) , _CustomContentSlot() , _CustomButtonSlot()`
- L69 _public prototype_ `SLATE_ARGUMENT(TOptional<bool>, AllowClear) SLATE_ARGUMENT(TOptional<bool>, AllowCreate) SLATE_ARGUMENT(bool, DisplayThumbnail) SLATE_ARGUMENT(bool, DisplayUseSelected) SLATE_ARGUMENT(bool, DisplayTransient) SLATE_ARGUMENT(bool, DisplayBrowse) SLATE_EVENT(FSimpleDelegate, OnBrowseOverride) SLATE_ATTRIBUTE(FText, OnBrowseToolTipOverride) SLATE_ATTRIBUTE(const FSlateBrush*, OnBrowseIconOverride) SLATE_ARGUMENT(bool, EnableContentPicker) SLATE_ARGUMENT(bool, DisplayCompactSize) SLATE_ARGUMENT(TSharedPtr<FAssetThumbnailPool>, ThumbnailPool) SLATE_ARGUMENT(FIntPoint, ThumbnailSize) SLATE_ATTRIBUTE(FString, ObjectPath) SLATE_ARGUMENT(const UClass*, Class) SLATE_ARGUMENT(TOptional<TArray<UFactory*>>, NewAssetFactories) SLATE_EVENT(FOnSetObject, OnSetObject) SLATE_EVENT(FOnShouldFilterAsset, OnShouldFilterAsset) SLATE_NAMED_SLOT(FArguments, CustomContentSlot) SLATE_NAMED_SLOT(FArguments, CustomButtonSlot) SLATE_ARGUMENT(TSharedPtr<IPropertyHandle>, PropertyHandle) SLATE_ARGUMENT(TArray<FAssetData>, OwnerAssetDataArray) SLATE_EVENT(FOnShouldFilterActor, OnShouldFilterActor) SLATE_ARGUMENT(TOptional<FDetailWidgetRow*>, InWidgetRow) SLATE_ATTRIBUTE(bool, bOnlyRecognizeOnDragEnter) SLATE_END_ARGS() static bool Supports( const TSharedRef<FPropertyEditor>& InPropertyEditor );`
- L99 _public prototype_ `static bool Supports( const FProperty* NodeProperty );`
- L106 _public prototype_ `static bool ParseAssetText(const FString& InText, FAssetData& OutAssetData);` — Parses the input text and finds the corrisponding asset in the asset registry. Supports various types of paths, such as export text, object and package paths. @returns True if OutAssetData contains a valid asset, or the input text was None.
- L115 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedPtr<FPropertyEditor>& InPropertyEditor = NULL );` — Construct the widget. @param	InArgs				Arguments for widget construction @param	InPropertyEditor	The property editor that this widget will operate on. If this is NULL, we expect the Class member of InArgs to be a valid UClass, so we know what objects this widget can accept.
- L117 _public prototype_ `void GetDesiredWidth( float& OutMinDesiredWidth, float &OutMaxDesiredWidth );`
- L119 _public prototype_ `void OpenComboButton();`
- L122 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;` — Override the tick method so we can check for thumbnail differences & update if necessary
- L167 _private prototype_ `bool ShouldDisplayThumbnail( const FArguments& InArgs, const UClass* ObjectClass ) const;` — Helper function for Construct - determines whether we should display a thumbnail or not @param	InArgs	The args passed into Construct() @returns true if we should display the thumbnail
- L170 _private prototype_ `const FSlateBrush* GetThumbnailBorder() const;` — Gets the border brush to show around the thumbnail, changes when the user hovers on it.
- L173 _private prototype_ `const FSlateBrush* GetStatusIcon() const;` — Returns the status icon, empty for non actors
- L176 _private prototype_ `EActorReferenceState GetActorReferenceState() const;` — Returns the state of this actor reference
- L182 _private prototype_ `TSharedRef<SWidget> OnGetMenuContent();` — Get the content to be displayed in the asset/actor picker menu @returns the widget for the menu content
- L188 _private prototype_ `void OnMenuOpenChanged(bool bOpen);` — Called when the asset menu is closed, we handle this to force the destruction of the asset menu to ensure any settings the user set are saved.
- L193 _private prototype_ `bool IsFilteredActor( const AActor* const Actor) const;` — Returns whether the actor should be filtered out from selection.
- L198 _private prototype_ `void CloseComboButton();` — Closes the combo button for the asset name.
- L204 _private prototype_ `FText OnGetAssetName() const;` — Get the name to be displayed for this asset @returns the name of the asset
- L210 _private prototype_ `FText OnGetAssetClassName() const;` — Get the class name to be displayed for this asset @returns the class name of this asset
- L216 _private prototype_ `FText OnGetToolTip() const;` — Get the tooltip to be displayed for this asset @returns the tooltip string
- L226 _private prototype_ `bool CanAssetBeAssigned(const FAssetData& AssetData) const;` — Determine whether the given asset is allowed to be assigned to the property. This is currently used to prevent non-engine assets being assigned to properties of engine assets. @param	AssetData	The asset to be assigned @return	false		if the asset cannot be assigned, true		if it can be assigned or if this is not known (e.g. because a delegate handles the reference assignment)
- L233 _private prototype_ `void SetValue( const FAssetData& AssetData );` — Set the value of the asset referenced by this property editor. Will set the underlying property handle if there is one. @param	AssetData	The asset data for the object to set the reference to
- L239 _private prototype_ `FPropertyAccess::Result GetValue( FObjectOrAssetData& OutValue, FObjectOrAssetData::EAssetDataOptions GetValueOptions ) const;` — Get the value referenced by this widget. @returns the referenced object
- L247 _private prototype_ `const UClass* GetDisplayedClass() const;` — Get the UClass we will display in the UI. This is the class of the object (if valid) or the property handles class (if any) or the Class value this widget was constructed with. @returns the UClass to display
- L253 _private prototype_ `void OnAssetSelected( const FAssetData& AssetData );` — Delegate for handling selection in the asset browser. @param	Object	The chosen asset
- L259 _private prototype_ `void OnActorSelected( AActor* InActor );` — Delegate for handling selection in the scene outliner. @param	InActor	The chosen actor
- L265 _private prototype_ `void OnGetAllowedClasses(TArray<const UClass*>& AllowedClasses);` — Delegate for handling classes of objects that can be picked. @param	AllowedClasses	The array of classes we allow
- L270 _private prototype_ `void OnOpenAssetEditor();` — Opens the asset editor for the viewed object
- L276 _private prototype_ `void OnBrowse();` — Browse for the object referenced by this widget, either in the Content Browser or the scene (for Actors)
- L281 _private prototype_ `FText GetOnBrowseToolTip() const;` — Get the tooltip text for the Browse button
- L286 _private prototype_ `const FSlateBrush* GetOnBrowseIcon() const;` — Get the icon for the Browse button
- L291 _private prototype_ `void OnUse();` — Use the selected object (replaces the referenced object if valid)
- L296 _private prototype_ `void OnClear();` — Clear the referenced object
- L302 _private prototype_ `FSlateColor GetAssetClassColor();` — Assets have an associated color, this is used to supply that color in the UI. @returns the color to display for this asset
- L310 _private prototype_ `bool OnAssetDraggedOver( TArrayView<FAssetData> InAssets, FText& OutReason ) const;` — Delegate used to check whether we can drop an object on this widget. @param	InObject	The object we are dragging @param	OutReason	When returning false, the reason it was not allowed @returns true if the object can be dropped
- L316 _private prototype_ `void OnAssetDropped( const FDragDropEvent&, TArrayView<FAssetData> InAssets );` — Delegate handling dropping an object on this widget @param	InObject	The object we are dropping
- L321 _private prototype_ `void OnCopy();` — Delegate handling ctrl+c
- L326 _private prototype_ `void OnPaste();` — Delegate handling ctrl+v
- L331 _private prototype_ `bool CanPasteFromText(const FString& InTag, const FString& InText, FAssetData& OutAssetData) const;` — @return True if the (optionally tagged) input contents can be pasted
- L336 _private prototype_ `void OnPasteFromText(const FString& InTag, const FString& InText, const TOptional<FGuid>& InOperationId);` — Delegate handling pasting an optionally tagged text snippet
- L341 _private prototype_ `void PasteFromText(const FString& InTag, const FAssetData& InAssetData);` — Handle pasting an optionally tagged text snippet
- L346 _private prototype_ `bool CanPaste();` — @return True of the current clipboard contents can be pasted
- L351 _private prototype_ `FReply OnAssetThumbnailDoubleClick( const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent );` — Handle double clicking the asset thumbnail. this 'Edits' the displayed asset
- L354 _private prototype_ `bool CanEdit() const;` — @return True if the property can be edited
- L357 _private prototype_ `bool CanSetBasedOnCustomClasses( const FAssetData& InAssetData ) const;` — @return true if the passed in AssetData can be used to set the property based on the list of custom classes
- L360 _private prototype_ `bool CanSetBasedOnAssetReferenceFilter( const FAssetData& InAssetData, FText* OutOptionalFailureReason = nullptr ) const;` — @return true if the passed in AssetData can be used to set the property based on the game specific asset reference filter
- L363 _private prototype_ `TSharedPtr<IPropertyHandle> GetMostSpecificPropertyHandle() const;` — @return Returns the property handle most relevant
- L372 _private prototype_ `static UClass* GetObjectPropertyClass(const FProperty* Property);` — Gets the class of the supplied property for use within the PropertyEditorAsset widget. Asserts if the property is not supported by the widget. @param	Property	The supplied property for the widget @return	The class of the property. Asserts if this tries to return null.
- L377 _private prototype_ `void InitializeClassFilters(const FProperty* Property);` — Initialize the AllowedClasses and DisallowedClasses arrays based on the property metadata.
- L380 _private prototype_ `bool IsClassAllowed(const UClass* InClass) const;` — Check if the given class is allowed by the AllowedClasses and DisallowedClasses as defined in the property metadata.
- L385 _private prototype_ `void InitializeAssetDataTags(const FProperty* Property);` — Initialize DisallowedAssetDataTags based on the property metadata.
- L388 _private prototype_ `bool IsAssetFiltered(const FAssetData& InAssetData);` — @return Returns true if the asset is excluded for this property
- L393 _private prototype_ `void GenerateCustomAssetPickerButtons(const FAssetData& InAssetData, const TArray<FAssetButtonActionExtension>& InExtensions);` — Generates custom Asset Picker Buttons using the provided AssetActionButtonExtensions data.
- L398 _private member_ `TSharedPtr<SComboButton> AssetComboButton;` — Main combobutton
- L401 _private member_ `TSharedPtr<SBorder> ThumbnailBorder;` — The border surrounding the thumbnail image.
- L404 _private member_ `TSharedPtr<FPropertyEditor> PropertyEditor;` — The property editor, if any
- L407 _private member_ `TSharedPtr<SHorizontalBox> CustomAssetPickerButtonBox;` — Optional Custom Asset Picker Buttons
- L410 _private member_ `TAttribute<FString> ObjectPath;` — Path to the object being edited instead of accessing the value directly with a property handle
- L413 _private member_ `mutable FAssetData CachedAssetData;` — Cached data
- L416 _private member_ `const UClass* ObjectClass;` — The class of the object we are editing
- L419 _private member_ `TArray<const UClass*> AllowedClassFilters;` — Classes that can be used with this property
- L422 _private member_ `TArray<const UClass*> DisallowedClassFilters;` — Classes that can NOT be used with this property
- L425 _private member_ `TOptional<TArray<UFactory*>> NewAssetFactoriesOverride;` — A list of the factories we can use to create new assets
- L428 _private member_ `TSharedPtr<FAssetDataTagMap> DisallowedAssetDataTags;` — Tags (and eventually values) that can NOT be used with this property
- L431 _private member_ `TSharedPtr<FAssetDataTagMap> RequiredAssetDataTags;` — Tags and values that must be present for an asset to be used with this property
- L434 _private member_ `bool bAllowClear;` — Whether the asset can be 'None' in this case
- L437 _private member_ `bool bAllowCreate;` — Whether the asset can be created from the asset picker
- L440 _private member_ `bool bIsActor;` — Whether the object we are editing is an Actor (i.e. requires a Scene Outliner to be displayed)
- L443 _private member_ `bool bExactClass;` — Whether the classes in the AllowedClassFilters list are exact or whether valid classes can be derived.
- L446 _private member_ `bool bIsSoftObjectPath;` — Wheter the property is a soft reference
- L449 _private member_ `UObject* EditorPathOwner;` — Editor Path context if any
- L452 _private member_ `int32 NumButtons;` — The number of additional buttons this picker has.
- L455 _private member_ `TAttribute<bool> OnIsEnabled;` — Base attribute passed to specify whether this editor is enabled
- L458 _private member_ `FOnSetObject OnSetObject;` — Delegate to call when our object value is set
- L461 _private member_ `FOnShouldFilterAsset OnShouldFilterAsset;` — Delegate for filtering valid assets
- L464 _private member_ `TSharedPtr<FAssetThumbnail> AssetThumbnail;` — Thumbnail for the asset
- L467 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;` — The property handle, if any
- L470 _private member_ `FOnShouldFilterActor OnShouldFilterActor;` — Delegate for filtering valid actors
- L476 _private member_ `TArray<FAssetData> OwnerAssetDataArray;` — The reference object on which the picker will assign the picked asset, if any. The system will test first the PropertyHandle follow by the PropertyEditor and if nothing this array of assets
- L479 _private member_ `bool bDisplayUseSelected;` — Whether to show the 'Use Selected' item
- L482 _private member_ `bool bDisplayTransient;` — Whether to show transient objects in the picker.

#### enum `SPropertyEditorAsset::EActorReferenceState`  
`enum class EActorReferenceState : uint8`  
_L39-53_
- L42 _public enumerator_ `NotAnActor` — This is not pointing to an actor
- L44 _public enumerator_ `Null` — This is specifically pointing at no actor
- L46 _public enumerator_ `Loaded` — The pointed to actor is fully loaded in memory
- L48 _public enumerator_ `Exists` — The pointed to actor exists because the pointed to map is loaded but not the actor
- L50 _public enumerator_ `Unknown` — The pointed to actor is unknown because the pointed to map is not loaded
- L52 _public enumerator_ `Error` — This is a known bad reference, the owning map is loaded but the actor does not exist

#### struct `SPropertyEditorAsset::FObjectOrAssetData`  
`struct FObjectOrAssetData`  
_L125-160_
- L134 _public member_ `UObject* Object = nullptr;`
- L135 _public member_ `FSoftObjectPath ObjectPath;`
- L136 _public member_ `FAssetData AssetData;`
- L137 _public member_ `UObject* EditorPathOwner = nullptr;`
- L139 _public prototype_ `FObjectOrAssetData() = default;`
- L141 _public prototype_ `FObjectOrAssetData(UObject* InObject, UObject* EditorPathOwner, EAssetDataOptions AssetDataOptions);`
- L143 _public function_ `FObjectOrAssetData( const FSoftObjectPath& InObjectPath ) : Object(nullptr) , ObjectPath(InObjectPath) , EditorPathOwner(nullptr)`
- L149 _public function_ `FObjectOrAssetData( const FAssetData& InAssetData ) : Object(nullptr) , ObjectPath( InAssetData.ToSoftObjectPath() ) , AssetData( InAssetData ) , EditorPathOwner(nullptr)`
- L156 _public function_ `bool IsValid() const`

#### enum `SPropertyEditorAsset::FObjectOrAssetData::EAssetDataOptions`  
`enum class EAssetDataOptions`  
_L127-132_
- L129 _public enumerator_ `None`
- L131 _public enumerator_ `SkipAssetRegistryTagsGathering` — Will not populate AssetRegistry Tags for an AssetData

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyEditor/SPropertyEditorBool.h` (Private)


#### class `SPropertyEditorBool`  
`class SPropertyEditorBool : public SCompoundWidget`  
_L14-47_
- inherits: `SCompoundWidget`
- L18 _public function_ `SLATE_BEGIN_ARGS( SPropertyEditorBool )`
- L19 _public prototype_ `SLATE_END_ARGS() static bool Supports( const TSharedRef< class FPropertyEditor >& PropertyEditor );`
- L23 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef< class FPropertyEditor >& PropertyEditor );`
- L25 _public prototype_ `void GetDesiredWidth( float& OutMinDesiredWidth, float& OutMaxDesiredWidth );`
- L28 _public prototype_ `virtual bool SupportsKeyboardFocus() const override;` — SWidget overrides
- L29 _public prototype_ `virtual bool HasKeyboardFocus() const override;`
- L30 _public prototype_ `virtual FReply OnFocusReceived( const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent ) override;`
- L34 _private prototype_ `virtual FReply OnMouseButtonDoubleClick( const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent ) override;`
- L36 _private prototype_ `ECheckBoxState OnGetCheckState() const;`
- L38 _private prototype_ `void OnCheckStateChanged( ECheckBoxState InNewState );`
- L41 _private prototype_ `bool CanEdit() const;` — @return True if the property can be edited
- L44 _private member_ `TSharedPtr< class FPropertyEditor > PropertyEditor;`
- L46 _private member_ `TSharedPtr< class SCheckBox> CheckBox;`

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyEditor/SPropertyEditorClass.h` (Private)


#### class `SPropertyEditorClass`  
`class SPropertyEditorClass : public SCompoundWidget`  
_L26-162_
- inherits: `SCompoundWidget`
- desc: A widget used to edit Class properties (UClass type properties). Can also be used (with a null FPropertyEditor) to edit a raw weak class pointer.
- L29 _public function_ `SLATE_BEGIN_ARGS(SPropertyEditorClass) : _Font(FAppStyle::GetFontStyle(PropertyEditorConstants::PropertyFontStyle)) , _MetaClass(UObject::StaticClass()) , _RequiredInterface(nullptr) , _AllowAbstract(false) , _IsBlueprintBaseOnly(false) , _AllowNone(true) , _ShowDisplayNames(false) , _InvalidObjectDisplayText("None") , _bIsMultiOptionalSetter(false)`
- L40 _public prototype_ `SLATE_ARGUMENT(FSlateFontInfo, Font) SLATE_ARGUMENT(const UClass*, MetaClass) SLATE_ARGUMENT(const UClass*, RequiredInterface) SLATE_ARGUMENT(TArray<const UClass*>, AllowedClasses) SLATE_ARGUMENT(TArray<const UClass*>, DisallowedClasses) SLATE_ARGUMENT(bool, AllowAbstract) SLATE_ARGUMENT(bool, IsBlueprintBaseOnly) SLATE_ARGUMENT(bool, AllowNone) SLATE_ATTRIBUTE(const UClass*, SelectedClass) SLATE_ARGUMENT(bool, ShowViewOptions) SLATE_ARGUMENT(bool, ShowTree) SLATE_ARGUMENT(bool, ShowDisplayNames) SLATE_EVENT(FOnSetClass, OnSetClass) SLATE_ARGUMENT(TArray<TSharedRef<class IClassViewerFilter>>, ClassViewerFilters) SLATE_ARGUMENT(FString, InvalidObjectDisplayText) SLATE_ARGUMENT(bool, bIsMultiOptionalSetter) SLATE_END_ARGS() static bool Supports(const TSharedRef< class FPropertyEditor >& InPropertyEditor);`
- L77 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedPtr< class FPropertyEditor >& InPropertyEditor = nullptr);`
- L79 _public prototype_ `void GetDesiredWidth(float& OutMinDesiredWidth, float& OutMaxDesiredWidth);`
- L82 _private prototype_ `void SendToObjects(const FString& NewValue);`
- L84 _private prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L85 _private prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L86 _private prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L88 _private prototype_ `TSharedRef<SWidget> ConstructClassViewer();`
- L95 _private prototype_ `TSharedRef<SWidget> GenerateClassPicker();` — Generates a class picker with a filter to show only classes allowed to be selected. @return The Class Picker widget.
- L102 _private prototype_ `void OnClassPicked(UClass* InClass);` — Callback function from the Class Picker for when a Class is picked. @param InClass			The class picked in the Class Picker
- L107 _private prototype_ `FText GetDisplayValueAsString() const;` — Gets the active display value as a string
- L109 _private prototype_ `bool CanEdit() const;`
- L113 _private member_ `TSharedPtr<class FPropertyEditor> PropertyEditor;` — The property editor we were constructed for, or null if we're editing using the construction arguments
- L116 _private member_ `TSharedPtr<class SComboButton> ComboButton;` — Used when the property deals with Classes and will display a Class Picker.
- L119 _private member_ `TSharedPtr<IClassViewerFilter> ClassFilter;` — Class filter that the class viewer is using.
- L122 _private member_ `TSharedPtr<FClassViewerFilterFuncs> ClassFilterFuncs;` — Filter functions for class viewer.
- L125 _private member_ `FClassViewerInitializationOptions ClassViewerOptions;` — Options used for creating the class viewer.
- L128 _private member_ `const UClass* MetaClass;` — The meta class that the selected class must be a child-of
- L130 _private member_ `const UClass* RequiredInterface;` — An interface that the selected class must implement
- L132 _private member_ `bool bAllowAbstract;` — Whether or not abstract classes are allowed
- L134 _private member_ `bool bIsBlueprintBaseOnly;` — Should only base blueprints be displayed?
- L136 _private member_ `bool bAllowNone;` — Should we be able to select "None" as a class?
- L138 _private member_ `bool bAllowOnlyPlaceable;` — Should only placeable classes be displayed?
- L140 _private member_ `bool bShowViewOptions;` — Should we show the view options button at the bottom of the class picker?
- L142 _private member_ `bool bShowTree;` — Should we show the class picker in tree mode or list mode?
- L144 _private member_ `bool bShowDisplayNames;` — Should we prettify class names on the class picker? (ie show their display name)
- L146 _private member_ `bool bShowObjectRootClass;` — Should we include /Script/CoreUObject.Object in the list?
- L148 _private member_ `TArray<const UClass*> AllowedClassFilters;` — Classes that can be picked with this property
- L150 _private member_ `TArray<const UClass*> DisallowedClassFilters;` — Classes that can NOT be picked with this property
- L152 _private member_ `FString InvalidObjectDisplayText;` — Text which is displayed instead of the normal class-text (used to show 'Set to Value' on optionals)
- L154 _private member_ `bool bIsMultiOptionalSetter;` — True if this class editor is for setting a multiple-value optional
- L157 _private member_ `TAttribute<const UClass*> SelectedClass;` — Attribute used to get the currently selected class (required if PropertyEditor == null)
- L159 _private member_ `FOnSetClass OnSetClass;` — Delegate used to set the currently selected class (required if PropertyEditor == null)
- L161 _private prototype_ `void CreateClassFilter(const TArray<TSharedRef<IClassViewerFilter>>& InClassFilters);`

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyEditor/SPropertyEditorColor.h` (Private)


#### class `SPropertyEditorColor`  
`class SPropertyEditorColor : public SCompoundWidget`  
_L14-87_
- inherits: `SCompoundWidget`
- L18 _public function_ `SLATE_BEGIN_ARGS( SPropertyEditorColor )`
- L19 _public prototype_ `SLATE_END_ARGS() static bool Supports( const TSharedRef< class FPropertyEditor >& PropertyEditor );`
- L23 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef< class FPropertyEditor >& InPropertyEditor, const TSharedRef< class IPropertyUtilities >& InPropertyUtilities );`
- L28 _protected prototype_ `TSharedRef< SColorBlock > ConstructColorBlock();` — @return A newly constructed SColorBlock
- L31 _protected prototype_ `TSharedRef< SColorBlock > ConstructAlphaColorBlock();` — @return A newly constructed SColorBlock setup specifically for handling alpha
- L39 _protected prototype_ `bool ShouldDisplayIgnoreAlpha() const;` — ShouldDisplayIgnoreAlpha determines whether or not to ignore the alpha value and just display the color as fully opaque (such as when associated with lights, for example). @return Whether to display the color as completely opaque regardless of its alpha value.
- L42 _protected prototype_ `FLinearColor OnGetColor() const;` — @return Gets the color for the color block to use for its TAttribute
- L53 _protected prototype_ `FReply ColorBlock_OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);` — The system calls this method to notify the widget that a mouse button was pressed within it. This event is bubbled. The color block will spawn a new color picker and destroy the old one if applicable. @param MyGeometry The Geometry of the widget receiving the event @param MouseEvent Information about the input event @return Whether the event was handled along with possible requests for the system to take action.
- L63 _protected prototype_ `EVisibility GetVisibilityForOpaqueDisplay() const;` — If the color has a non-opaque alpha, we want to display half of the box as opaque so you can always see the color even if it's mostly/entirely transparent.  But if the color is rendered as completely opaque, we might as well collapse the extra opaque display rather than drawing two separate boxes. @return Whether the always-opaque part of the display is visible or collapsed (the latter is if the main part of the display is already being rendered as opaque).
- L65 _protected prototype_ `void CreateColorPickerWindow(const TSharedRef< class FPropertyEditor >& PropertyEditor, bool bUseAlpha, bool bOnlyRefreshOnOk=false);`
- L67 _protected prototype_ `void SetColor(FLinearColor NewColor);`
- L72 _protected prototype_ `void OnColorPickerCancelled( FLinearColor OriginalColor );` — Called when the color picker is cancelled
- L75 _protected prototype_ `bool CanEdit() const;` — @return True if the property can be edited
- L79 _protected member_ `TArray< FLinearColor > OriginalColors;` — Original colors to set in the case that the user cancel's the color picker
- L81 _protected member_ `TSharedPtr< class FPropertyEditor > PropertyEditor;`
- L83 _protected member_ `TSharedPtr< class IPropertyUtilities > PropertyUtilities;`
- L86 _protected member_ `bool bIgnoreAlpha;` — Whether or not alpha should be displayed.  Some color properties (such as lights) do not use alpha.

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyEditor/SPropertyEditorCombo.h` (Private)


#### class `SPropertyEditorCombo`  
`class SPropertyEditorCombo : public SCompoundWidget`  
_L16-73_
- inherits: `SCompoundWidget`
- L20 _public function_ `SLATE_BEGIN_ARGS( SPropertyEditorCombo )`
- L22 _public prototype_ `SLATE_ARGUMENT( FPropertyComboBoxArgs, ComboArgs ) SLATE_END_ARGS() static bool Supports( const TSharedRef< class FPropertyEditor >& InPropertyEditor );`
- L28 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedPtr< class FPropertyEditor >& InPropertyEditor = nullptr);` — Constructs widget, if InPropertyEditor is null then PropertyHandle must be set
- L30 _public prototype_ `void GetDesiredWidth( float& OutMinDesiredWidth, float& OutMaxDesiredWidth );`
- L32 _private prototype_ `void GenerateComboBoxStrings( TArray< TSharedPtr<FString> >& OutComboBoxStrings, TArray<TSharedPtr<class SToolTip>>& OutToolTips, TArray<bool>& OutRestrictedItems );`
- L33 _private prototype_ `void OnComboSelectionChanged( TSharedPtr<FString> NewValue, ESelectInfo::Type SelectInfo );`
- L34 _private prototype_ `void OnSegmentedControlSelectionChanged( FString NewValue );`
- L35 _private prototype_ `void OnResetToDefault();`
- L36 _private prototype_ `void OnComboOpening();`
- L38 _private prototype_ `virtual void SendToObjects( const FString& NewValue );`
- L43 _private prototype_ `FString GetDisplayValueAsString() const;` — Gets the active display value as a string
- L48 _private prototype_ `FText GetValueToolTip() const;` — Get the active display value tooltip.
- L51 _private prototype_ `bool CanEdit() const;` — @return True if the property can be edited
- L55 _private member_ `TSharedPtr< class FPropertyEditor > PropertyEditor;` — Property editor this was created from, may be null
- L58 _private member_ `TSharedPtr<class SPropertyComboBox> ComboBox;` — Fills out with generated strings.
- L61 _private member_ `TSharedPtr<SSegmentedControl<FString>> SegmentControl;` — Alternative display widget.
- L62 _private member_ `FTextBlockStyle ParameterTextStyle;`
- L65 _private member_ `FPropertyComboBoxArgs ComboArgs;` — Arguments used to construct the combo box
- L70 _private member_ `bool bUsesAlternateDisplayValues;` — Indicates that this combo box's values are friendly names for the real values; currently only used for enum drop-downs.
- L71 _private member_ `TMap<FString, FString> AlternateDisplayValueToInternalValue;`
- L72 _private member_ `TMap<FString, FString> InternalValueToAlternateDisplayValue;`

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyEditor/SPropertyEditorDateTime.h` (Private)


#### class `SPropertyEditorDateTime`  
`class SPropertyEditorDateTime : public SCompoundWidget`  
_L16-43_
- inherits: `SCompoundWidget`
- L20 _public function_ `SLATE_BEGIN_ARGS( SPropertyEditorDateTime ) : _Font( FAppStyle::GetFontStyle( PropertyEditorConstants::PropertyFontStyle ) )`
- L23 _public prototype_ `SLATE_ATTRIBUTE( FSlateFontInfo, Font ) SLATE_END_ARGS() static bool Supports( const TSharedRef< class FPropertyEditor >& InPropertyEditor );`
- L28 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef< class FPropertyEditor >& InPropertyEditor );`
- L30 _public prototype_ `void GetDesiredWidth( float& OutMinDesiredWidth, float& OutMaxDesiredWidth );`
- L34 _private prototype_ `virtual void HandleTextCommitted( const FText& NewText, ETextCommit::Type CommitInfo );`
- L36 _private prototype_ `bool CanEdit() const;`
- L40 _private member_ `TSharedPtr< class FPropertyEditor > PropertyEditor;`
- L42 _private member_ `TSharedPtr< class SWidget > PrimaryWidget;`

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyEditor/SPropertyEditorEditInline.h` (Private)


#### class `SPropertyEditorEditInline`  
`class SPropertyEditorEditInline : public SCompoundWidget`  
_L15-81_
- inherits: `SCompoundWidget`
- L19 _public function_ `SLATE_BEGIN_ARGS( SPropertyEditorEditInline ) : _Font( FAppStyle::GetFontStyle( PropertyEditorConstants::PropertyFontStyle ) )`
- L22 _public prototype_ `SLATE_ARGUMENT( FSlateFontInfo, Font ) SLATE_END_ARGS() static bool Supports( const TSharedRef< class FPropertyEditor >& InPropertyEditor );`
- L26 _public prototype_ `static bool Supports( const FPropertyNode* InTreeNode, int32 InArrayIdx );`
- L28 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef< class FPropertyEditor >& InPropertyEditor );`
- L30 _public prototype_ `void GetDesiredWidth( float& OutMinDesiredWidth, float& OutMaxDesiredWidth );`
- L40 _public prototype_ `static TSharedRef<SWidget> GenerateClassPicker(TSharedRef<IPropertyHandle> PropertyHandle, FOnClassPicked OnPicked, TSharedPtr<IClassViewerFilter> AdditionalClassFilter);` — Generates a class picker with a filter to show only classes allowed to be selected. @param PropertyHandle			The Property Handle for the instanced UObject whose class is being picked @param OnPicked				The callback to fire when a class is picked. @return The Class Picker widget.
- L48 _public prototype_ `static void OnClassPicked(UClass* InClass, TSharedRef<IPropertyHandle> PropertyHandle, EPropertyValueSetFlags::Type Flags=EPropertyValueSetFlags::DefaultFlags);` — Callback function from the Class Picker for when a Class is picked. @param InClass			The class picked in the Class Picker @param PropertyHandle	The Property Handle for the instanced UObject whose class is being picked
- L58 _private prototype_ `bool IsValueEnabled(TWeakPtr<IPropertyHandle> WeakHandlePtr) const;` — Called to see if the value is enabled for editing @param WeakHandlePtr	Handle to the property that the new value is for @return	true if the property is enabled
- L63 _private prototype_ `FText GetDisplayValueAsString() const;` — @return The current display value for the combo box as a string
- L68 _private prototype_ `const FSlateBrush* GetDisplayValueIcon() const;` — @return The current display value's icon, if any. Returns nullptr if we have no valid value.
- L73 _private prototype_ `void OnClassPickedInternal(UClass* InClass, TSharedRef<IPropertyHandle> PropertyHandle);` — Internal delegate called when a class is picked, used to close the combo box after a class is picked
- L78 _private member_ `TSharedPtr<class FPropertyEditor > PropertyEditor;`
- L80 _private member_ `TSharedPtr<class SComboButton> ComboButton;`

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyEditor/SPropertyEditorInteractiveActorPicker.h` (Private)


#### class `SPropertyEditorInteractiveActorPicker`  
`class SPropertyEditorInteractiveActorPicker : public SButton`  
_L12-49_
- inherits: `SButton`
- L15 _public function_ `SLATE_BEGIN_ARGS( SPropertyEditorInteractiveActorPicker )`
- L18 _public prototype_ `SLATE_EVENT( FOnGetAllowedClasses, OnGetAllowedClasses ) SLATE_EVENT( FOnShouldFilterActor, OnShouldFilterActor ) SLATE_EVENT( FOnActorSelected, OnActorSelected ) SLATE_END_ARGS() ~SPropertyEditorInteractiveActorPicker();` — Delegate used to filter allowed actors
- L30 _public prototype_ `void Construct( const FArguments& InArgs );`
- L33 _public prototype_ `virtual FReply OnKeyDown( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override;` — Begin SWidget interface
- L34 _public prototype_ `virtual bool SupportsKeyboardFocus() const override;`
- L39 _private prototype_ `FReply OnClicked();` — Delegate for when the button is clicked
- L42 _private member_ `FOnGetAllowedClasses OnGetAllowedClasses;` — Delegate used to filter allowed actors
- L45 _private member_ `FOnShouldFilterActor OnShouldFilterActor;` — Delegate used to filter allowed actors
- L48 _private member_ `FOnActorSelected OnActorSelected;` — Delegate called when an actor is selected

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyEditor/SPropertyEditorMap.h` (Private)


#### class `SPropertyEditorMap`  
`class SPropertyEditorMap : public SCompoundWidget`  
_L16-41_
- inherits: `SCompoundWidget`
- L19 _public function_ `SLATE_BEGIN_ARGS(SPropertyEditorMap) : _Font(FAppStyle::GetFontStyle(PropertyEditorConstants::PropertyFontStyle))`
- L22 _public prototype_ `SLATE_ATTRIBUTE(FSlateFontInfo, Font) SLATE_END_ARGS() static bool Supports(const TSharedRef< class FPropertyEditor >& InPropertyEditor);`
- L27 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef< class FPropertyEditor >& InPropertyEditor);`
- L29 _public prototype_ `void GetDesiredWidth(float& OutMinDesiredWidth, float& OutMaxDesiredWidth);`
- L33 _private prototype_ `FText GetMapTextValue() const;`
- L34 _private prototype_ `FText GetMapTooltipText() const;`
- L37 _private prototype_ `bool CanEdit() const;` — @return True if the property can be edited
- L40 _private member_ `TSharedPtr< FPropertyEditor > PropertyEditor;`

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyEditor/SPropertyEditorNumeric.h` (Private)


#### class `SPropertyEditorNumeric`  
`template <typename NumericType> class SPropertyEditorNumeric : public SCompoundWidget`  
_L41-657_
- inherits: `SCompoundWidget`
- L45 _public function_ `SLATE_BEGIN_ARGS( SPropertyEditorNumeric<NumericType> ) : _Font( FAppStyle::GetFontStyle( PropertyEditorConstants::PropertyFontStyle ) )`
- L48 _public function_ `SLATE_ATTRIBUTE( FSlateFontInfo, Font ) SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TSharedRef<FPropertyEditor>& InPropertyEditor )`
- L365 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L370 _public function_ `virtual FReply OnFocusReceived( const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent ) override`
- L376 _public function_ `void GetDesiredWidth( float& OutMinDesiredWidth, float& OutMaxDesiredWidth )`
- L394 _public function_ `static bool Supports( const TSharedRef< FPropertyEditor >& PropertyEditor )`
- L478 _private function_ `TOptional<NumericType> OnGetValue() const` — @return The value or unset if properties with multiple values are viewed
- L492 _private function_ `void OnValueChanged( NumericType NewValue )`
- L519 _private function_ `void OnValueCommitted( NumericType NewValue, ETextCommit::Type CommitInfo )`
- L541 _private function_ `void OnUndeterminedValueCommitted( FText NewValue, ETextCommit::Type CommitType )`
- L569 _private function_ `void OnBeginSliderMovement()` — Called when the slider begins to move.  We create a transaction here to undo the property
- L583 _private function_ `void OnEndSliderMovement( NumericType NewValue )` — Called when the slider stops moving.  We end the previously created transaction
- L601 _private function_ `bool CanEdit() const` — @return True if the property can be edited
- L646 _private member_ `TSharedPtr<TNumericUnitTypeInterface<NumericType>> TypeInterface;`
- L648 _private member_ `TSharedPtr< class FPropertyEditor > PropertyEditor;`
- L650 _private member_ `TSharedPtr< class SWidget > PrimaryWidget;`
- L653 _private member_ `bool bIsUsingSlider;` — True if the slider is being used to change the value of the property
- L656 _private member_ `NumericType LastSliderCommittedValue;` — When using the slider, what was the last committed value

#### struct `SPropertyEditorNumeric::TTypeToProperty`  
`template<typename T, typename U = void> struct TTypeToProperty`  
_L411-414_
- desc: Helper to provide mapping for a given FProperty object to a property editor type
- L413 _public function_ `static bool Match(const FProperty* InProperty)`

#### struct `SPropertyEditorNumeric::TTypeToProperty`  
`template<typename U> struct TTypeToProperty<float, U>`  
_L417-420_
- L413 _public function_ `static bool Match(const FProperty* InProperty)`

#### struct `SPropertyEditorNumeric::TTypeToProperty`  
`template<typename U> struct TTypeToProperty<double, U>`  
_L423-426_
- L413 _public function_ `static bool Match(const FProperty* InProperty)`

#### struct `SPropertyEditorNumeric::TTypeToProperty`  
`template<typename U> struct TTypeToProperty<int8, U>`  
_L429-432_
- L413 _public function_ `static bool Match(const FProperty* InProperty)`

#### struct `SPropertyEditorNumeric::TTypeToProperty`  
`template<typename U> struct TTypeToProperty<int16, U>`  
_L435-438_
- L413 _public function_ `static bool Match(const FProperty* InProperty)`

#### struct `SPropertyEditorNumeric::TTypeToProperty`  
`template<typename U> struct TTypeToProperty<int32, U>`  
_L441-444_
- L413 _public function_ `static bool Match(const FProperty* InProperty)`

#### struct `SPropertyEditorNumeric::TTypeToProperty`  
`template<typename U> struct TTypeToProperty<int64, U>`  
_L447-450_
- L413 _public function_ `static bool Match(const FProperty* InProperty)`

#### struct `SPropertyEditorNumeric::TTypeToProperty`  
`template<typename U> struct TTypeToProperty<uint8, U>`  
_L453-456_
- L413 _public function_ `static bool Match(const FProperty* InProperty)`

#### struct `SPropertyEditorNumeric::TTypeToProperty`  
`template<typename U> struct TTypeToProperty<uint16, U>`  
_L459-462_
- L413 _public function_ `static bool Match(const FProperty* InProperty)`

#### struct `SPropertyEditorNumeric::TTypeToProperty`  
`template<typename U> struct TTypeToProperty<uint32, U>`  
_L465-468_
- L413 _public function_ `static bool Match(const FProperty* InProperty)`

#### struct `SPropertyEditorNumeric::TTypeToProperty`  
`template<typename U> struct TTypeToProperty<uint64, U>`  
_L471-474_
- L413 _public function_ `static bool Match(const FProperty* InProperty)`

#### struct `SPropertyEditorNumeric::FBitmaskFlagInfo`  
`struct FBitmaskFlagInfo`  
_L607-612_
- desc: Flag data for bitmasks.
- L609 _public member_ `NumericType Value;`
- L610 _public member_ `FText DisplayName;`
- L611 _public member_ `FText ToolTipText;`

#### struct `SPropertyEditorNumeric::TBitmaskValueHelpers`  
`template<typename T> struct TBitmaskValueHelpers`  
_L616-622_
- desc: Integral bitmask value helper methods.
- L618 _public function_ `static T BitwiseAND(T Base, T Mask)`
- L619 _public function_ `static T BitwiseXOR(T Base, T Mask)`
- L621 _public function_ `template <typename U> static T LeftShift(T Base, U Shift)`
- L628 _public function_ `static float BitwiseAND(float Base, float Mask)`
- L629 _public function_ `static float BitwiseXOR(float Base, float Mask)`
- L631 _public function_ `template <typename U> static float LeftShift(float Base, U Shift)`
- L638 _public function_ `static double BitwiseAND(double Base, double Mask)`
- L639 _public function_ `static double BitwiseXOR(double Base, double Mask)`
- L641 _public function_ `template <typename U> static double LeftShift(double Base, U Shift)`

#### struct `SPropertyEditorNumeric::TBitmaskValueHelpers`  
`template<> struct TBitmaskValueHelpers<float>`  
_L626-632_
- desc: Explicit specialization for numeric 'float' types (these will not be used).
- L618 _public function_ `static T BitwiseAND(T Base, T Mask)`
- L619 _public function_ `static T BitwiseXOR(T Base, T Mask)`
- L621 _public function_ `template <typename U> static T LeftShift(T Base, U Shift)`
- L628 _public function_ `static float BitwiseAND(float Base, float Mask)`
- L629 _public function_ `static float BitwiseXOR(float Base, float Mask)`
- L631 _public function_ `template <typename U> static float LeftShift(float Base, U Shift)`
- L638 _public function_ `static double BitwiseAND(double Base, double Mask)`
- L639 _public function_ `static double BitwiseXOR(double Base, double Mask)`
- L641 _public function_ `template <typename U> static double LeftShift(double Base, U Shift)`

#### struct `SPropertyEditorNumeric::TBitmaskValueHelpers`  
`template<> struct TBitmaskValueHelpers<double>`  
_L636-642_
- desc: Explicit specialization for numeric 'double' types (these will not be used).
- L618 _public function_ `static T BitwiseAND(T Base, T Mask)`
- L619 _public function_ `static T BitwiseXOR(T Base, T Mask)`
- L621 _public function_ `template <typename U> static T LeftShift(T Base, U Shift)`
- L628 _public function_ `static float BitwiseAND(float Base, float Mask)`
- L629 _public function_ `static float BitwiseXOR(float Base, float Mask)`
- L631 _public function_ `template <typename U> static float LeftShift(float Base, U Shift)`
- L638 _public function_ `static double BitwiseAND(double Base, double Mask)`
- L639 _public function_ `static double BitwiseXOR(double Base, double Mask)`
- L641 _public function_ `template <typename U> static double LeftShift(double Base, U Shift)`

#### Free symbols / members of external scopes

- L38 _macro_ `#define LOCTEXT_NAMESPACE "PropertyEditor"`
- L64 _function_ `` (scope `SPropertyEditorNumeric::SLATE_ATTRIBUTE`)
- L84 _function_ `` (scope `SPropertyEditorNumeric::SLATE_ATTRIBUTE::__anon91086f730102`)
- L240 _function_ `` (scope `SPropertyEditorNumeric::SLATE_ATTRIBUTE::__anon91086f730502`)

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyEditor/SPropertyEditorOptional.h` (Private)


#### class `SPropertyEditorOptional`  
`class SPropertyEditorOptional : public SCompoundWidget`  
_L33-62_
- inherits: `SCompoundWidget`
- desc: This class represents a `value editor widget` for optional types in the details panel. It has three possible states which it can display: 1. (Unset Single-Select) The optional has no set value. A button `Set to Value` is shown and pressing this button will set the optional's value to a default initialized state. 2. (Set Single-Select OR Multi-Select) The optional has a set value. The `value editor widget` for the set value is shown (example: SPropertyEditorArray) along with a `Clear Optional` button which un-sets the optional. 3. (Multi-Select with mix of set + unset) A combo-box with `Multiple States` is shown which when clicked displays a dropdown menu offering: `Set all to Value` (sets all values to default initialized) `Set all to None` (unsets all values)
- L36 _public function_ `SLATE_BEGIN_ARGS(SPropertyEditorOptional) : _Font(FAppStyle::GetFontStyle(PropertyEditorConstants::PropertyFontStyle))`
- L39 _public prototype_ `SLATE_ATTRIBUTE(FSlateFontInfo, Font) SLATE_END_ARGS() static bool Supports(const TSharedRef<FPropertyEditor>& InPropertyEditor);`
- L44 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FPropertyEditor>& InPropertyEditor, TSharedRef<IPropertyUtilities> InPropertyUtilities);`
- L46 _public prototype_ `void GetDesiredWidth(float& OutMinDesiredWidth, float& OutMaxDesiredWidth);`
- L49 _private prototype_ `FText GetOptionalTooltipText() const;`
- L52 _private prototype_ `bool CanEdit() const;` — @return True if the property can be edited
- L54 _private prototype_ `TSharedRef<SWidget> MakeWidgetForOption(TSharedPtr<FText> InOption);`
- L55 _private prototype_ `void OnOptionChanged(TSharedPtr<FText> NewOption, ESelectInfo::Type);`
- L57 _private member_ `TSharedPtr< FPropertyEditor > PropertyEditor;`
- L58 _private member_ `TSharedPtr<SWidget> ValueEditorWidget;`
- L59 _private member_ `TArray<TSharedPtr<FText>> MultiselectOptions;`
- L60 _private member_ `float MinDesiredWidth;`
- L61 _private member_ `float MaxDesiredWidth;`

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyEditor/SPropertyEditorSceneDepthPicker.h` (Private)


#### class `SPropertyEditorSceneDepthPicker`  
`class SPropertyEditorSceneDepthPicker : public SButton`  
_L12-36_
- inherits: `SButton`
- L15 _public function_ `SLATE_BEGIN_ARGS(SPropertyEditorSceneDepthPicker)`
- L17 _public prototype_ `SLATE_EVENT(FOnSceneDepthLocationSelected, OnSceneDepthLocationSelected) SLATE_END_ARGS() ~SPropertyEditorSceneDepthPicker();`
- L23 _public prototype_ `void Construct( const FArguments& InArgs );`
- L26 _public prototype_ `virtual FReply OnKeyDown( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override;` — Begin SWidget interface
- L27 _public prototype_ `virtual bool SupportsKeyboardFocus() const override;`
- L32 _private prototype_ `FReply OnClicked();` — Delegate for when the button is clicked
- L35 _private member_ `FOnSceneDepthLocationSelected OnSceneDepthLocationSelected;` — Called when scene depth location is picked

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyEditor/SPropertyEditorSet.h` (Private)


#### class `SPropertyEditorSet`  
`class SPropertyEditorSet : public SCompoundWidget`  
_L16-41_
- inherits: `SCompoundWidget`
- L19 _public function_ `SLATE_BEGIN_ARGS(SPropertyEditorSet) : _Font(FAppStyle::GetFontStyle(PropertyEditorConstants::PropertyFontStyle))`
- L22 _public prototype_ `SLATE_ATTRIBUTE(FSlateFontInfo, Font) SLATE_END_ARGS() static bool Supports(const TSharedRef< class FPropertyEditor >& InPropertyEditor);`
- L27 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef< class FPropertyEditor >& InPropertyEditor);`
- L29 _public prototype_ `void GetDesiredWidth(float& OutMinDesiredWidth, float& OutMaxDesiredWidth);`
- L33 _private prototype_ `FText GetSetTextValue() const;`
- L34 _private prototype_ `FText GetSetTooltipText() const;`
- L37 _private prototype_ `bool CanEdit() const;` — @return True if the property can be edited
- L40 _private member_ `TSharedPtr< FPropertyEditor > PropertyEditor;`

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyEditor/SPropertyEditorStruct.h` (Private)


#### class `SPropertyEditorStruct`  
`class SPropertyEditorStruct : public SCompoundWidget`  
_L22-112_
- inherits: `SCompoundWidget`
- desc: A widget used to edit struct type properties (UObject type properties, with a sub-type of UScriptStuct). Can also be used (with a null FPropertyEditor) to edit a raw weak struct pointer.
- L25 _public function_ `SLATE_BEGIN_ARGS(SPropertyEditorStruct) : _Font(FAppStyle::GetFontStyle(PropertyEditorConstants::PropertyFontStyle)) , _MetaStruct(nullptr) , _AllowNone(true) , _ShowDisplayNames(false) , _bExcludeBaseStruct(false)`
- L32 _public prototype_ `SLATE_ARGUMENT(FSlateFontInfo, Font) SLATE_ARGUMENT(const UScriptStruct*, MetaStruct) SLATE_ARGUMENT(bool, AllowNone) SLATE_ATTRIBUTE(const UScriptStruct*, SelectedStruct) SLATE_ARGUMENT(bool, ShowViewOptions) SLATE_ARGUMENT(bool, ShowTree) SLATE_ARGUMENT(bool, ShowDisplayNames) SLATE_ARGUMENT(bool, bExcludeBaseStruct) SLATE_EVENT(FOnSetStruct, OnSetStruct) SLATE_END_ARGS() static bool Supports(const TSharedRef< class FPropertyEditor >& InPropertyEditor);`
- L54 _public prototype_ `static bool Supports(const FProperty* InProperty);`
- L56 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedPtr< class FPropertyEditor >& InPropertyEditor = nullptr);`
- L58 _public prototype_ `void GetDesiredWidth(float& OutMinDesiredWidth, float& OutMaxDesiredWidth);`
- L61 _private prototype_ `void SendToObjects(const FString& NewValue);`
- L63 _private prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L64 _private prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L65 _private prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L72 _private prototype_ `TSharedRef<SWidget> GenerateStructPicker();` — Generates a struct picker with a filter to show only structs allowed to be selected. @return The Struct Picker widget.
- L79 _private prototype_ `void OnStructPicked(const UScriptStruct* InStruct);` — Callback function from the Struct Picker for when a struct is picked. @param InStruct		The struct picked in the Struct Picker
- L84 _private prototype_ `FText GetDisplayValue() const;` — Gets the active display value
- L86 _private prototype_ `bool CanEdit() const;`
- L90 _private member_ `TSharedPtr<class FPropertyEditor> PropertyEditor;` — The property editor we were constructed for, or null if we're editing using the construction arguments
- L93 _private member_ `TSharedPtr<class SComboButton> ComboButton;` — Used when the property deals with structs and will display a Struct Picker.
- L96 _private member_ `const UScriptStruct* MetaStruct;` — The meta struct that the selected class must be a child-of
- L98 _private member_ `bool bAllowNone;` — Should we be able to select "None" as a struct?
- L100 _private member_ `bool bShowViewOptions;` — Should we show the view options button at the bottom of the struct picker?
- L102 _private member_ `bool bShowTree;` — Should we show the struct picker in tree mode or list mode?
- L104 _private member_ `bool bShowDisplayNames;` — Should we prettify struct names on the struct picker? (ie show their display name)
- L106 _private member_ `bool bExcludeBaseStruct;` — Should we hide the specified MetaStruct from the selection list and only display its children?
- L109 _private member_ `TAttribute<const UScriptStruct*> SelectedStruct;` — Attribute used to get the currently selected struct (required if PropertyEditor == null)
- L111 _private member_ `FOnSetStruct OnSetStruct;` — Delegate used to set the currently selected struct (required if PropertyEditor == null)

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyEditor/SPropertyEditorTableRow.h` (Private)


#### class `SPropertyEditorTableRow`  
`class SPropertyEditorTableRow : public SPropertyRowBase, public IPropertyTreeRow`  
_L21-87_
- inherits: `SPropertyRowBase,IPropertyTreeRow`
- desc: A wrapper around property editor if its shown in a tree (I.E SPropertyTreeView)
- L25 _public function_ `SLATE_BEGIN_ARGS(SPropertyEditorTableRow) : _OnMiddleClicked()`
- L28 _public prototype_ `SLATE_EVENT( FOnPropertyClicked, OnMiddleClicked ) SLATE_EVENT( FConstructExternalColumnCell, ConstructExternalColumnCell ) SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TSharedRef< class FPropertyEditor >& InPropertyEditor, const TSharedRef< class IPropertyUtilities >& InPropertyUtilities, const TSharedRef<STableViewBase>& InOwnerTable );`
- L40 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn( const FName& ColumnName ) override;` — Called to generate a widget for a column in this row @param ColumnName The name of the column to generate a widget for
- L42 _public prototype_ `virtual FReply OnMouseButtonUp( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L44 _public prototype_ `virtual TSharedPtr< FPropertyPath > GetPropertyPath() const override;`
- L46 _public prototype_ `virtual bool IsCursorHovering() const override;`
- L51 _private prototype_ `EVisibility OnGetRowVisibility() const;`
- L53 _private prototype_ `EVisibility OnGetFavoritesVisibility() const;`
- L54 _private prototype_ `const FSlateBrush* OnGetFavoriteImage() const;`
- L55 _private prototype_ `FReply OnToggleFavoriteClicked();`
- L57 _private prototype_ `FReply OnNameDoubleClicked();`
- L59 _private prototype_ `TSharedRef< SWidget > ConstructNameColumnWidget();`
- L60 _private prototype_ `TSharedRef< SWidget > ConstructValueColumnWidget();`
- L62 _private prototype_ `TSharedRef<SWidget> ConstructPropertyEditorWidget();`
- L64 _private prototype_ `EVisibility GetDiffersFromDefaultAsVisibility() const;`
- L65 _private prototype_ `const FSlateBrush* GetImageBrush() const;`
- L66 _private prototype_ `FReply OnClickedTestButton();`
- L72 _private member_ `TSharedPtr< class FPropertyEditor > PropertyEditor;` — The property editor in this row
- L74 _private member_ `TSharedPtr< class IPropertyUtilities > PropertyUtilities;`
- L76 _private member_ `TSharedPtr< SWidget > ValueEditorWidget;`
- L78 _private member_ `TSharedPtr< FPropertyPath > PropertyPath;`
- L80 _private member_ `FOnPropertyClicked OnMiddleClicked;`
- L83 _private member_ `FConstructExternalColumnCell ConstructExternalColumnCell;` — Called to construct any the cell contents for columns created by external code
- L85 _private member_ `FOptionalSize MinWidth;`
- L86 _private member_ `FOptionalSize MaxWidth;`

#### Free symbols / members of external scopes

- L16 _typedef_ `typedef SMultiColumnTableRow< TSharedPtr<class FPropertyNode*> > SPropertyRowBase;`

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyEditor/SPropertyEditorText.h` (Private)


#### class `SPropertyEditorText`  
`class SPropertyEditorText : public SCompoundWidget`  
_L22-78_
- inherits: `SCompoundWidget`
- L26 _public function_ `SLATE_BEGIN_ARGS( SPropertyEditorText ) : _Font( FAppStyle::GetFontStyle( PropertyEditorConstants::PropertyFontStyle ) )`
- L29 _public prototype_ `SLATE_ATTRIBUTE( FSlateFontInfo, Font ) SLATE_END_ARGS() static bool Supports( const TSharedRef< class FPropertyEditor >& InPropertyEditor );`
- L34 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef< class FPropertyEditor >& InPropertyEditor );`
- L36 _public prototype_ `void GetDesiredWidth( float& OutMinDesiredWidth, float& OutMaxDesiredWidth );`
- L38 _public prototype_ `bool SupportsKeyboardFocus() const override;`
- L40 _public prototype_ `FReply OnFocusReceived( const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent ) override;`
- L44 _private prototype_ `void OnTextCommitted( const FText& NewText, ETextCommit::Type CommitInfo );`
- L46 _private prototype_ `bool OnVerifyTextChanged(const FText& Text, FText& OutError);`
- L49 _private prototype_ `bool CanEdit() const;` — @return True if the property can be edited
- L52 _private prototype_ `bool IsReadOnly() const;` — @return True if the property is Read Only
- L55 _private prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FPropertyValidatorFunc, const FString&);`
- L57 _private member_ `TSharedPtr< class FPropertyEditor > PropertyEditor;`
- L59 _private member_ `TSharedPtr< class SWidget > PrimaryWidget;`
- L62 _private member_ `TSharedPtr<SMultiLineEditableTextBox> MultiLineWidget;` — Widget used for the multiline version of the text property
- L65 _private member_ `TSharedPtr<SEditableTextBox> SingleLineWidget;` — Widget used for the single line version of the text property
- L68 _private member_ `bool bIsMultiLine;` — Cached flag as we would like multi-line text widgets to be slightly larger
- L71 _private member_ `int32 MaxLength = 0;` — The maximum length of the value that can be edited, or <=0 for unlimited
- L74 _private member_ `FCharRangeList AllowedCharacters;` — The characters that are allowed in the value. If empty, any character is allowed.
- L77 _private member_ `FPropertyValidatorFunc PropertyValidatorFunc;` — An optional validator function that will be called each time the text is changed

#### Free symbols / members of external scopes

- L55 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FPropertyValidatorFunc, const FString&);`

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyEditor/SPropertyEditorTitle.h` (Private)


#### class `SPropertyEditorTitle`  
`class SPropertyEditorTitle : public SCompoundWidget`  
_L16-141_
- inherits: `SCompoundWidget`
- L21 _public function_ `SLATE_BEGIN_ARGS( SPropertyEditorTitle ) : _PropertyFont( FAppStyle::GetFontStyle( PropertyEditorConstants::PropertyFontStyle ) ) , _CategoryFont( FAppStyle::GetFontStyle( PropertyEditorConstants::CategoryFontStyle ) )`
- L25 _public function_ `SLATE_ATTRIBUTE( FSlateFontInfo, PropertyFont ) SLATE_ATTRIBUTE( FSlateFontInfo, CategoryFont ) SLATE_EVENT( FOnClicked, OnDoubleClicked ) SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TSharedRef<FPropertyEditor>& InPropertyEditor )`
- L120 _private function_ `FReply OnMouseButtonDoubleClick( const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent )`
- L138 _private member_ `FOnClicked OnDoubleClicked;` — The delegate to execute when this text is double clicked
- L140 _private member_ `TSharedPtr<FPropertyEditor> PropertyEditor;`

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyEditor/SPropertyMenuActorPicker.h` (Private)


#### class `SPropertyMenuActorPicker`  
`class SPropertyMenuActorPicker : public SCompoundWidget`  
_L12-111_
- inherits: `SCompoundWidget`
- L15 _public function_ `SLATE_BEGIN_ARGS( SPropertyMenuActorPicker ) : _InitialActor(NULL) , _AllowClear(true) , _AllowPickingLevelInstanceContent(false) , _ActorFilter() , _DisplayUseSelected(true) , _ShowTransient(false)`
- L23 _public prototype_ `SLATE_ARGUMENT( AActor*, InitialActor ) SLATE_ARGUMENT( bool, AllowClear ) SLATE_ARGUMENT( bool, AllowPickingLevelInstanceContent ) SLATE_ARGUMENT( FOnShouldFilterActor, ActorFilter ) SLATE_ARGUMENT(bool, DisplayUseSelected) SLATE_EVENT( FOnActorSelected, OnSet ) SLATE_EVENT( FSimpleDelegate, OnClose ) SLATE_EVENT( FSimpleDelegate, OnUseSelected ) SLATE_ARGUMENT(bool, ShowTransient) SLATE_END_ARGS() void Construct( const FArguments& InArgs );`
- L45 _private prototype_ `void HandleUseSelected();` — Use the currently selected Actor
- L50 _private prototype_ `void OnEdit();` — Edit the object referenced by this widget
- L55 _private prototype_ `void OnCopy();` — Delegate handling ctrl+c
- L60 _private prototype_ `void OnPaste();` — Delegate handling ctrl+v
- L65 _private prototype_ `bool CanPaste();` — @return True of the current clipboard contents can be pasted
- L70 _private prototype_ `void OnClear();` — Clear the referenced object
- L76 _private prototype_ `void OnActorSelected( AActor* InActor );` — Delegate for handling selection in the scene outliner. @param	InActor	The chosen actor
- L83 _private prototype_ `void SetValue( AActor* InActor );` — Set the value of the asset referenced by this property editor. Will set the underlying property handle if there is one. @param	InObject	The object to set the reference to
- L86 _private member_ `AActor* CurrentActor;`
- L89 _private member_ `bool bAllowClear;` — Whether the asset can be 'None' in this case
- L92 _private member_ `bool bAllowPickingLevelInstanceContent;` — Whether we allow picking actors inside level instances
- L95 _private member_ `FOnShouldFilterActor ActorFilter;` — Delegate used to test whether an actor should be displayed or not
- L98 _private member_ `FOnActorSelected OnSet;` — Delegate to call when our object value should be set
- L101 _private member_ `FSimpleDelegate OnClose;` — Delegate for closing the containing menu
- L104 _private member_ `FSimpleDelegate OnUseSelected;` — Delegate for using the currently selected actor
- L107 _private member_ `bool bDisplayUseSelected;` — Whether to display the 'Use Selected' item
- L110 _private member_ `bool bShowTransient = false;` — Whether to show transient objects

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyEditor/SPropertyMenuAssetPicker.h` (Private)


#### class `SPropertyMenuAssetPicker`  
`class SPropertyMenuAssetPicker : public SCompoundWidget`  
_L13-139_
- inherits: `SCompoundWidget`
- L16 _public function_ `SLATE_BEGIN_ARGS( SPropertyMenuAssetPicker ) : _InitialObject(nullptr) , _AllowClear(true)`
- L20 _public prototype_ `SLATE_ARGUMENT( FAssetData, InitialObject ) SLATE_ARGUMENT( TSharedPtr<IPropertyHandle>, PropertyHandle ) SLATE_ARGUMENT( TArray<FAssetData>, OwnerAssetArray) SLATE_ARGUMENT( bool, AllowClear ) SLATE_ARGUMENT( bool, AllowCopyPaste ) SLATE_ARGUMENT( TArray<const UClass*>, AllowedClasses ) SLATE_ARGUMENT( TArray<const UClass*>, DisallowedClasses ) SLATE_ARGUMENT( TArray<UFactory*>, NewAssetFactories ) SLATE_EVENT( FOnShouldFilterAsset, OnShouldFilterAsset ) SLATE_EVENT( FOnAssetSelected, OnSet ) SLATE_EVENT( FSimpleDelegate, OnClose ) SLATE_END_ARGS() void Construct( const FArguments& InArgs );`
- L44 _private prototype_ `void OnEdit();` — Edit the object referenced by this widget
- L49 _private prototype_ `void OnCopy();` — Delegate handling ctrl+c
- L54 _private prototype_ `void OnPaste();` — Delegate handling ctrl+v
- L59 _private prototype_ `bool CanPasteFromText(const FString& InTag, const FString& InText, FAssetData& OutAssetData) const;` — @return True if the (optionally tagged) input contents can be pasted
- L64 _private prototype_ `void OnPasteFromText(const FString& InTag, const FString& InText, const TOptional<FGuid>& InOperationId);` — Delegate handling pasting an optionally tagged text snippet
- L69 _private prototype_ `void PasteFromText(const FString& InTag, const FAssetData& InAssetData);` — Handle pasting an optionally tagged text snippet
- L74 _private prototype_ `bool CanPaste();` — @return True of the current clipboard contents can be pasted
- L79 _private prototype_ `void OnClear();` — Clear the referenced object
- L85 _private prototype_ `void OnAssetSelected( const FAssetData& AssetData );` — Delegate for handling selection in the asset browser. @param	AssetData	The chosen asset data
- L91 _private prototype_ `void OnAssetEnterPressed( const TArray<FAssetData>& AssetData );` — Delegate for handling keyboard selection in the asset browser. @param	AssetData	The chosen asset data
- L97 _private prototype_ `void OnCreateNewAssetSelected(TWeakObjectPtr<UFactory> Factory);` — Delegate for handling creating new assets from the menu. @param	FactoryPtr		Factory which creates asset
- L104 _private prototype_ `void SetValue( const FAssetData& AssetData );` — Set the value of the asset referenced by this property editor. Will set the underlying property handle if there is one. @param	AssetData	The asset data for the object to set the reference to
- L106 _private prototype_ `virtual FReply OnPreviewKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L109 _private member_ `FAssetData CurrentObject;`
- L112 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;` — The property this asset picker will modify (if any)
- L114 _private member_ `TSharedPtr<SWidget> AssetPickerWidget;`
- L117 _private member_ `bool bAllowClear;` — Whether the asset can be 'None' in this case
- L120 _private member_ `bool bAllowCopyPaste;` — Whether the asset can be copied or pasted
- L123 _private member_ `TArray<const UClass*> AllowedClasses;` — Array of classes to Allow in filter
- L126 _private member_ `TArray<const UClass*> DisallowedClasses;` — Array of classes to Disallow in filter
- L129 _private member_ `TArray<UFactory*> NewAssetFactories;` — Array of factories which can create a new asset of suitable type
- L132 _private member_ `FOnShouldFilterAsset OnShouldFilterAsset;` — Delegate for filtering valid assets
- L135 _private member_ `FOnAssetSelected OnSet;` — Delegate to call when our object value should be set
- L138 _private member_ `FSimpleDelegate OnClose;` — Delegate for closing the containing menu

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyEditor/SPropertyMenuComponentPicker.h` (Private)


#### class `SPropertyMenuComponentPicker`  
`class SPropertyMenuComponentPicker : public SCompoundWidget`  
_L17-97_
- inherits: `SCompoundWidget`
- L20 _public function_ `SLATE_BEGIN_ARGS(SPropertyMenuComponentPicker) : _InitialComponent(nullptr) , _AllowClear(true) , _ShowTransient(false) , _ActorFilter()`
- L26 _public prototype_ `SLATE_ARGUMENT(UActorComponent*, InitialComponent) SLATE_ARGUMENT(bool, AllowClear) SLATE_ARGUMENT(bool, ShowTransient) SLATE_ARGUMENT(FOnShouldFilterActor, ActorFilter) SLATE_ARGUMENT(FOnShouldFilterComponent, ComponentFilter) SLATE_EVENT(FOnComponentSelected, OnSet) SLATE_EVENT(FSimpleDelegate, OnClose) SLATE_ARGUMENT(UWorld*, PickerWorld) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L47 _private prototype_ `void OnEdit();` — Edit the object referenced by this widget
- L52 _private prototype_ `void OnCopy();` — Delegate handling ctrl+c
- L57 _private prototype_ `void OnPaste();` — Delegate handling ctrl+v
- L62 _private prototype_ `bool CanPaste();` — @return True of the current clipboard contents can be pasted
- L67 _private prototype_ `void OnClear();` — Clear the referenced object
- L73 _private prototype_ `void OnItemSelected(UActorComponent* Component);` — Delegate for handling selection by the actor picker. @param	Component The chosen component
- L80 _private prototype_ `void SetValue(UActorComponent* InComponent);` — Set the value of the asset referenced by this property editor. Will set the underlying property handle if there is one. @param	InObject	The object to set the reference to
- L83 _private member_ `UActorComponent* InitialComponent;`
- L86 _private member_ `bool bAllowClear;` — Whether the asset can be 'None' in this case
- L89 _private member_ `FOnShouldFilterActor ActorFilter;` — Delegate used to test whether a item should be displayed or not
- L90 _private member_ `FOnShouldFilterComponent ComponentFilter;`
- L93 _private member_ `FOnComponentSelected OnSet;` — Delegate to call when our object value should be set
- L96 _private member_ `FSimpleDelegate OnClose;` — Delegate for closing the containing menu

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace SceneOutliner`

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyEditor/SPropertySceneOutliner.h` (Private)


#### class `SPropertySceneOutliner`  
`class SPropertySceneOutliner : public SCompoundWidget`  
_L14-37_
- inherits: `SCompoundWidget`
- L17 _public function_ `SLATE_BEGIN_ARGS( SPropertySceneOutliner )`
- L18 _public prototype_ `SLATE_EVENT( FOnGetActorFilters, OnGetActorFilters ) SLATE_EVENT( FOnActorSelected, OnActorSelected ) SLATE_END_ARGS() void Construct( const FArguments& InArgs );`
- L25 _private prototype_ `FReply OnClicked();`
- L27 _private prototype_ `TSharedRef<SWidget> OnGenerateSceneOutliner();`
- L29 _private prototype_ `void OnActorSelectedFromOutliner( AActor* InActor );`
- L33 _private member_ `TSharedPtr< class SMenuAnchor > SceneOutlinerAnchor;` — Menu anchor for opening and closing the scene outliner
- L35 _private member_ `FOnGetActorFilters OnGetActorFilters;`
- L36 _private member_ `FOnActorSelected OnActorSelected;`

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyTable/BooleanPropertyTableCellPresenter.h` (Private)


#### class `FBooleanPropertyTableCellPresenter`  
`class FBooleanPropertyTableCellPresenter : public TSharedFromThis< FBooleanPropertyTableCellPresenter >, public IPropertyTableCellPresenter`  
_L9-38_
- inherits: `TSharedFromThis<FBooleanPropertyTableCellPresenter>,IPropertyTableCellPresenter`
- L13 _public prototype_ `FBooleanPropertyTableCellPresenter( const TSharedRef< class FPropertyEditor >& InPropertyEditor );`
- L15 _public prototype_ `virtual ~FBooleanPropertyTableCellPresenter() = default;`
- L17 _public prototype_ `virtual TSharedRef< class SWidget > ConstructDisplayWidget() override;`
- L19 _public prototype_ `virtual bool RequiresDropDown() override;`
- L21 _public prototype_ `virtual TSharedRef< class SWidget > ConstructEditModeCellWidget() override;`
- L23 _public prototype_ `virtual TSharedRef< class SWidget > ConstructEditModeDropDownWidget() override;`
- L25 _public prototype_ `virtual TSharedRef< class SWidget > WidgetToFocusOnEdit() override;`
- L27 _public prototype_ `virtual FString GetValueAsString() override;`
- L29 _public prototype_ `virtual FText GetValueAsText() override;`
- L31 _public function_ `virtual bool HasReadOnlyEditMode() override`
- L36 _private member_ `TSharedPtr< class SWidget > FocusWidget;`
- L37 _private member_ `TSharedRef< class FPropertyEditor > PropertyEditor;`

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyTable/ColorPropertyTableCellPresenter.h` (Private)


#### class `FColorPropertyTableCellPresenter`  
`class FColorPropertyTableCellPresenter : public TSharedFromThis< FColorPropertyTableCellPresenter >, public IPropertyTableCellPresenter`  
_L9-39_
- inherits: `TSharedFromThis<FColorPropertyTableCellPresenter>,IPropertyTableCellPresenter`
- L13 _public prototype_ `FColorPropertyTableCellPresenter( const TSharedRef< class FPropertyEditor >& InPropertyEditor, const TSharedRef< class IPropertyTableUtilities >& InPropertyUtilities );`
- L15 _public prototype_ `virtual ~FColorPropertyTableCellPresenter() = default;`
- L17 _public prototype_ `virtual TSharedRef< class SWidget > ConstructDisplayWidget() override;`
- L19 _public prototype_ `virtual bool RequiresDropDown() override;`
- L21 _public prototype_ `virtual TSharedRef< class SWidget > ConstructEditModeCellWidget() override;`
- L23 _public prototype_ `virtual TSharedRef< class SWidget > ConstructEditModeDropDownWidget() override;`
- L25 _public prototype_ `virtual TSharedRef< class SWidget > WidgetToFocusOnEdit() override;`
- L27 _public prototype_ `virtual FString GetValueAsString() override;`
- L29 _public prototype_ `virtual FText GetValueAsText() override;`
- L31 _public function_ `virtual bool HasReadOnlyEditMode() override`
- L36 _private member_ `TSharedPtr< class SWidget > FocusWidget;`
- L37 _private member_ `TSharedRef< class FPropertyEditor > PropertyEditor;`
- L38 _private member_ `TSharedRef< class IPropertyTableUtilities > PropertyUtilities;`

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyTable/ColumnWidgetFactory.h` (Private)


#### class `ColumnWidgetFactory`  
`class ColumnWidgetFactory : public TSharedFromThis< ColumnWidgetFactory >`  
_L8-16_
- inherits: `TSharedFromThis<ColumnWidgetFactory>`
- L12 _public prototype_ `bool Supports( const TSharedRef < class IPropertyTableColumn >& Column );`
- L14 _public prototype_ `TSharedRef< class SColumnHeader > CreateColumnHeaderWidget( const TSharedRef < class IPropertyTableColumn >& Column, const TSharedRef< class IPropertyTableUtilities >& Utilities, const TSharedPtr< IPropertyTableCustomColumn >& Customization, const FName& Style );`

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyTable/ObjectNameTableCellPresenter.h` (Private)


#### class `FObjectNameTableCellPresenter`  
`class FObjectNameTableCellPresenter : public TSharedFromThis< FObjectNameTableCellPresenter >, public IPropertyTableCellPresenter`  
_L23-134_
- inherits: `TSharedFromThis<FObjectNameTableCellPresenter>,IPropertyTableCellPresenter`
- L27 _public function_ `FObjectNameTableCellPresenter( const TSharedRef< IPropertyTableCell >& InCell ) : FocusWidget( SNullWidget::NullWidget ) , Cell( InCell )`
- L34 _public prototype_ `virtual ~FObjectNameTableCellPresenter() = default;`
- L36 _public function_ `virtual TSharedRef< class SWidget > ConstructDisplayWidget() override`
- L50 _public function_ `virtual bool RequiresDropDown() override`
- L52 _public function_ `virtual TSharedRef< class SWidget > ConstructEditModeCellWidget() override`
- L71 _public function_ `virtual TSharedRef< class SWidget > ConstructEditModeDropDownWidget() override`
- L73 _public function_ `virtual TSharedRef< class SWidget > WidgetToFocusOnEdit() override`
- L75 _public function_ `virtual FString GetValueAsString() override`
- L77 _public function_ `virtual FText GetValueAsText() override`
- L79 _public function_ `virtual bool HasReadOnlyEditMode() override`
- L84 _private function_ `TSharedRef< SWidget > ConstructNameWidget( const FName& TextFontStyle )`
- L120 _private function_ `FSlateColor GetTextForegroundColor() const`
- L132 _private member_ `TWeakPtr< class SWidget > FocusWidget;`
- L133 _private member_ `TSharedRef< IPropertyTableCell > Cell;`

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyTable/PropertyTableWidgetHandle.h` (Private)


#### class `FPropertyTableWidgetHandle`  
`class FPropertyTableWidgetHandle: public IPropertyTableWidgetHandle`  
_L9-28_
- inherits: `IPropertyTableWidgetHandle`
- L11 _public function_ `FPropertyTableWidgetHandle(const TSharedRef<SPropertyTable>& InPropertyTableWidget) : PropertyTableWidget(InPropertyTableWidget)`
- L14 _public prototype_ `virtual ~FPropertyTableWidgetHandle() = default;`
- L16 _public function_ `virtual void RequestRefresh() override`
- L21 _public function_ `virtual TSharedRef<SWidget> GetWidget() override`
- L27 _private member_ `TSharedRef<SPropertyTable> PropertyTableWidget;`

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyTable/SBoolColumnHeader.h` (Private)


#### class `SBoolColumnHeader`  
`class SBoolColumnHeader : public SColumnHeader`  
_L13-62_
- inherits: `SColumnHeader`
- L17 _public function_ `SLATE_BEGIN_ARGS( SBoolColumnHeader ) : _Style( TEXT("PropertyTable") ) , _Customization()`
- L21 _public function_ `SLATE_ARGUMENT( FName, Style ) SLATE_ARGUMENT( TSharedPtr< IPropertyTableCustomColumn >, Customization ) SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TSharedRef< class IPropertyTableColumn >& InPropertyTableColumn, const TSharedRef< class IPropertyTableUtilities >& InPropertyUtilities )`
- L36 _public function_ `virtual TSharedRef< SWidget > GenerateCell( const TSharedRef< class IPropertyTableRow >& PropertyTableRow ) override`
- L61 _private member_ `FName Style;`

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyTable/SColorColumnHeader.h` (Private)


#### class `SColorColumnHeader`  
`class SColorColumnHeader : public SColumnHeader`  
_L13-62_
- inherits: `SColumnHeader`
- L17 _public function_ `SLATE_BEGIN_ARGS( SColorColumnHeader ) : _Style( TEXT("PropertyTable") ) , _Customization()`
- L21 _public function_ `SLATE_ARGUMENT( FName, Style ) SLATE_ARGUMENT( TSharedPtr< IPropertyTableCustomColumn >, Customization ) SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TSharedRef< class IPropertyTableColumn >& InPropertyTableColumn, const TSharedRef< class IPropertyTableUtilities >& InPropertyUtilities )`
- L36 _public function_ `virtual TSharedRef< SWidget > GenerateCell( const TSharedRef< class IPropertyTableRow >& PropertyTableRow ) override`
- L61 _private member_ `FName Style;`

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyTable/SColumnHeader.h` (Private)


#### class `SColumnHeader`  
`class SColumnHeader : public SCompoundWidget`  
_L24-130_
- inherits: `SCompoundWidget`
- L27 _public function_ `SLATE_BEGIN_ARGS( SColumnHeader ) : _Style( TEXT("PropertyTable") ) , _Customization()`
- L31 _public prototype_ `SLATE_ARGUMENT( FName, Style ) SLATE_ARGUMENT( TSharedPtr< IPropertyTableCustomColumn >, Customization ) SLATE_END_ARGS() virtual TSharedRef< class SWidget > GenerateCell( const TSharedRef< class IPropertyTableRow >& Row ) = 0;`
- L40 _protected function_ `void Construct( const FArguments& InArgs, const TSharedRef< class IPropertyTableColumn >& InPropertyTableColumn, const TSharedRef< class IPropertyTableUtilities >& InUtilities )`
- L85 _protected function_ `virtual FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override`
- L99 _protected function_ `TSharedRef< SWidget > ConstructNameWidget( const FName& Style, const FName& TextFontStyle )`
- L125 _protected member_ `TSharedPtr< IPropertyTableUtilities > Utilities;`
- L127 _protected member_ `TSharedPtr< IPropertyTableColumn > Column;`
- L129 _protected member_ `TSharedPtr< IPropertyTableCustomColumn > Customization;`

#### Free symbols / members of external scopes

- L21 _macro_ `#define LOCTEXT_NAMESPACE "SColumnHeader"`

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyTable/SObjectColumnHeader.h` (Private)


#### class `SObjectColumnHeader`  
`class SObjectColumnHeader : public SColumnHeader`  
_L17-80_
- inherits: `SColumnHeader`
- L21 _public function_ `SLATE_BEGIN_ARGS( SObjectColumnHeader ) : _Style( TEXT("PropertyTable") ) , _Customization()`
- L25 _public function_ `SLATE_ARGUMENT( FName, Style ) SLATE_ARGUMENT( TSharedPtr< IPropertyTableCustomColumn >, Customization ) SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TSharedRef< class IPropertyTableColumn >& InPropertyTableColumn, const TSharedRef< class IPropertyTableUtilities >& InPropertyUtilities )`
- L40 _public function_ `virtual TSharedRef< SWidget > GenerateCell( const TSharedRef< class IPropertyTableRow >& PropertyTableRow ) override`
- L79 _private member_ `FName Style;`

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyTable/SObjectNameColumnHeader.h` (Private)


#### class `SObjectNameColumnHeader`  
`class SObjectNameColumnHeader : public SColumnHeader`  
_L12-67_
- inherits: `SColumnHeader`
- L16 _public function_ `SLATE_BEGIN_ARGS( SObjectNameColumnHeader ) : _Style( TEXT("PropertyTable") ) , _Customization()`
- L20 _public function_ `SLATE_ARGUMENT( FName, Style ) SLATE_ARGUMENT( TSharedPtr< IPropertyTableCustomColumn >, Customization ) SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TSharedRef< class IPropertyTableColumn >& InPropertyTableColumn, const TSharedRef< class IPropertyTableUtilities >& InPropertyUtilities )`
- L42 _public function_ `virtual TSharedRef< SWidget > GenerateCell( const TSharedRef< class IPropertyTableRow >& PropertyTableRow ) override`
- L66 _private member_ `FName Style;`

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyTable/SPropertyNameColumnHeader.h` (Private)


#### class `SPropertyNameColumnHeader`  
`class SPropertyNameColumnHeader : public SColumnHeader`  
_L18-87_
- inherits: `SColumnHeader`
- L22 _public function_ `SLATE_BEGIN_ARGS( SPropertyNameColumnHeader ) : _Style( TEXT("PropertyTable") ) , _Customization()`
- L26 _public function_ `SLATE_ARGUMENT( FName, Style ) SLATE_ARGUMENT( TSharedPtr< IPropertyTableCustomColumn >, Customization ) SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TSharedRef< class IPropertyTableColumn >& InPropertyTableColumn, const TSharedRef< class IPropertyTableUtilities >& InPropertyUtilities )`
- L51 _public function_ `virtual TSharedRef< SWidget > GenerateCell( const TSharedRef< class IPropertyTableRow >& PropertyTableRow ) override`
- L78 _public function_ `FReply OnTitleClicked()` — Called when the column title has been clicked to change sorting mode
- L86 _private member_ `FName Style;`

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyTable/SPropertyTable.h` (Private)


#### class `SPropertyTable`  
`class SPropertyTable : public STreeView< TSharedRef< IPropertyTableRow > > , public IPropertyTableWidgetHandle`  
_L32-789_
- inherits: `STreeView<TSharedRef<IPropertyTableRow>>,IPropertyTableWidgetHandle`
- L36 _public function_ `SLATE_BEGIN_ARGS( SPropertyTable ) : _Style( "PropertyTable" ) , _ColumnCustomizations()`
- L40 _public function_ `SLATE_ARGUMENT( FName, Style ) SLATE_ARGUMENT( TArray< TSharedRef< class IPropertyTableCustomColumn > >, ColumnCustomizations ) SLATE_END_ARGS() SPropertyTable() : bUpdatingSelection( false )`
- L56 _public function_ `void Construct( const FArguments& InArgs, const TSharedRef< class IPropertyTable >& InPropertyTable )` — Construct this widget.  Called by the SNew() Slate macro. @param	InArgs				Declaration used by the SNew() macro to construct this widget @param	InViewModel			The UI logic not specific to slate
- L126 _public function_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override`
- L132 _public function_ `virtual void RequestRefresh() override`
- L138 _public function_ `virtual TSharedRef<SWidget> GetWidget() override`
- L143 _public function_ `virtual FReply OnKeyDown( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override`
- L473 _public function_ `virtual FReply OnPreviewKeyDown( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override`
- L488 _public function_ `FReply SelectRange( const TSharedPtr< IPropertyTableCell >& StartingCell, const TSharedPtr< IPropertyTableCell >& EndingCell, const TSharedPtr< IPropertyTableCell >& CellToFocus )`
- L529 _public function_ `FReply MoveToCell( const TSharedPtr< IPropertyTableCell >& CellToFocus )`
- L561 _public function_ `virtual FReply OnKeyUp( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override`
- L588 _protected function_ `TSharedRef< ITableRow > GenerateRow( const TSharedRef< IPropertyTableRow > PropertyTableRow, const TSharedRef< STableViewBase >& OwnerTable )`
- L594 _protected function_ `void OnSelectionChanged( const TSharedPtr< IPropertyTableRow > Row, const ESelectInfo::Type SelectionInfo )`
- L622 _protected function_ `void UpdateSelection()` — Called whenever the table selection changes
- L649 _protected function_ `void OnGetChildren( const TSharedRef< IPropertyTableRow > ParentPropertyTableRow, TArray< TSharedRef< IPropertyTableRow > >& OutChildren )`
- L657 _private function_ `void SyncBreadcrumbTrail()`
- L686 _private function_ `void OnCrumbClicked( const int32& Item )`
- L703 _private function_ `TSharedRef< SWidget > GetCrumbMenuContent( const int32& Item )`
- L752 _private function_ `void SetRootPath( const TSharedRef< FPropertyPath > Path )`
- L765 _public function_ `virtual bool Private_UsesSelectorFocus() const override`
- L770 _public function_ `virtual bool Private_HasSelectorFocus( const TSharedRef< IPropertyTableRow >& TheItem ) const override`
- L778 _private member_ `bool bUpdatingSelection;` — Whether the view is currently updating the viewmodel selection
- L780 _private member_ `FName Style;`
- L782 _private member_ `TSharedPtr< IPropertyTable > Table;`
- L784 _private member_ `TSharedPtr< IPropertyTableUtilities > Utilities;`
- L786 _private member_ `TSharedPtr< SPropertyTableHeaderRow > HeaderRow;`
- L788 _private member_ `TSharedPtr< class SBreadcrumbTrail< int32 > > BreadcrumbTrail;`

#### Free symbols / members of external scopes

- L30 _macro_ `#define LOCTEXT_NAMESPACE "PropertyTable"`

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyTable/SPropertyTableCell.h` (Private)


#### class `SPropertyTableCell`  
`class SPropertyTableCell : public SCompoundWidget`  
_L26-88_
- inherits: `SCompoundWidget`
- L30 _public function_ `SLATE_BEGIN_ARGS( SPropertyTableCell ) : _Presenter( NULL ) , _Style( TEXT("PropertyTable") )`
- L34 _public function_ `SLATE_ARGUMENT( TSharedPtr< IPropertyTableCellPresenter >, Presenter) SLATE_ARGUMENT( FName, Style ) SLATE_END_ARGS() SPropertyTableCell() : DropDownAnchor( NULL ) , Presenter( NULL ) , Cell( NULL ) , bEnterEditingMode( false ) , Style()`
- L46 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef< class IPropertyTableCell >& InCell );`
- L48 _public prototype_ `virtual FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L50 _public prototype_ `virtual FReply OnMouseButtonDoubleClick( const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent ) override;`
- L52 _public prototype_ `virtual int32 OnPaint( const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;`
- L57 _private prototype_ `TSharedRef< SWidget > ConstructCellContents();`
- L59 _private prototype_ `void SetContent( const TSharedRef< SWidget >& NewContents );`
- L61 _private prototype_ `TSharedRef< class SWidget > ConstructEditModeCellWidget();`
- L63 _private prototype_ `TSharedRef< class SWidget > ConstructEditModeDropDownWidget();`
- L65 _private prototype_ `TSharedRef< class SWidget > ConstructInvalidPropertyWidget();`
- L67 _private prototype_ `void OnAnchorWindowClosed( const TSharedRef< SWindow >& WindowClosing );`
- L69 _private prototype_ `void EnteredEditMode();`
- L71 _private prototype_ `void ExitedEditMode();`
- L73 _private prototype_ `void OnCellValueChanged( UObject* Object, FPropertyChangedEvent& PropertyChangedEvent );`
- L76 _private prototype_ `EActiveTimerReturnType TriggerEnterEditingMode(double InCurrentTime, float InDeltaTime);` — One-off active timer to trigger entering the editing mode
- L80 _private member_ `TSharedPtr< SMenuAnchor > DropDownAnchor;`
- L82 _private member_ `TSharedPtr< class IPropertyTableCellPresenter > Presenter;`
- L83 _private member_ `TSharedPtr< class IPropertyTableCell > Cell;`
- L84 _private member_ `bool bEnterEditingMode;`
- L85 _private member_ `FName Style;`
- L87 _private member_ `const FSlateBrush* CellBackground;`

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyTable/SPropertyTableHeaderRow.h` (Private)


#### class `SPropertyTableHeaderRow`  
`class SPropertyTableHeaderRow : public SHeaderRow`  
_L21-237_
- inherits: `SHeaderRow`
- L25 _public function_ `SLATE_BEGIN_ARGS( SPropertyTableHeaderRow ) : _Style( TEXT("PropertyTable") ) , _Customizations()`
- L29 _public function_ `SLATE_ARGUMENT( FName, Style ) SLATE_ARGUMENT( TArray< TSharedRef< class IPropertyTableCustomColumn > >, Customizations ) SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TSharedRef< class IPropertyTable >& InPropertyTable )`
- L57 _public function_ `void UpdateColumns()`
- L135 _public function_ `TSharedPtr< SColumnHeader > Find( const FName& ColumnId )`
- L150 _private function_ `TSharedRef< SColumnHeader > ConstructColumnHeader( const TSharedRef < class IPropertyTableColumn >& Column, const TSharedRef< class IPropertyTableUtilities >& Utilities, const FName& InStyle )`
- L167 _private function_ `TSharedRef< SWidget > GenerateColumnMenu( const TSharedRef< IPropertyTableColumn >& Column )`
- L200 _private function_ `void RegenerateColumnMenu( const TSharedRef< IPropertyTableColumn >& Column )`
- L207 _private function_ `void RemoveColumn( const TSharedRef< IPropertyTableColumn > Column )`
- L212 _private function_ `void RemoveAllButThisColumn(const TSharedRef<IPropertyTableColumn> ColumnToKeep)`
- L228 _private member_ `TSharedPtr< class IPropertyTable > PropertyTable;`
- L230 _private member_ `TSharedPtr< class ColumnWidgetFactory > ColumnFactory;`
- L232 _private member_ `TArray< TSharedRef< class IPropertyTableCustomColumn > > Customizations;`
- L234 _private member_ `TMap< FName, TSharedRef< class SColumnHeader > > ColumnHeaders;`
- L236 _private member_ `FName Style;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define LOCTEXT_NAMESPACE "PropertyTableHeaderRow"`

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyTable/SPropertyTableRow.h` (Private)


#### class `SPropertyTableRow`  
`class SPropertyTableRow : public SPropertyTableRowBase`  
_L21-192_
- inherits: `SPropertyTableRowBase`
- L25 _public function_ `SLATE_BEGIN_ARGS( SPropertyTableRow ) : _Style( "PropertyTable" )`
- L28 _public function_ `SLATE_ARGUMENT( FName, Style ) SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TSharedRef< class IPropertyTableRow >& InPropertyTableRow, const TSharedRef< class SPropertyTableHeaderRow > InPropertyTableHeaderRow, const TSharedRef< STableViewBase >& InOwnerTableView )`
- L54 _public function_ `FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override`
- L62 _public function_ `FReply OnMouseButtonUp( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override`
- L151 _public function_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override`
- L159 _protected function_ `void Refresh()`
- L165 _protected function_ `virtual TSharedRef< SWidget > GenerateWidgetForColumn( const FName& ColumnId ) override`
- L188 _private member_ `TSharedPtr< class IPropertyTableRow > Row;`
- L189 _private member_ `TSharedPtr< class IPropertyTableCell > PreviousCurrentCell;`
- L190 _private member_ `TWeakPtr< class SPropertyTableHeaderRow > HeaderRowWeakPtr;`
- L191 _private member_ `FName Style;`

#### Free symbols / members of external scopes

- L19 _typedef_ `typedef SMultiColumnTableRow< TSharedRef< class IPropertyTableRow > > SPropertyTableRowBase;`

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyTable/SRowHeaderCell.h` (Private)


#### class `SRowHeaderCell`  
`class SRowHeaderCell : public SCompoundWidget`  
_L19-146_
- inherits: `SCompoundWidget`
- L23 _public function_ `SLATE_BEGIN_ARGS( SRowHeaderCell ) : _Style( TEXT("PropertyTable") )`
- L26 _public function_ `SLATE_ARGUMENT( FName, Style ) SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TSharedRef< class IPropertyTableCell >& InCell, const TSharedPtr< FPropertyEditor >& PropertyEditor )`
- L84 _public function_ `virtual FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override`
- L92 _public function_ `virtual FReply OnMouseButtonDoubleClick( const FGeometry& InMyGeometry, const FPointerEvent& MouseEvent ) override`
- L100 _public function_ `virtual int32 OnPaint( const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override`
- L121 _private function_ `const FSlateBrush* GetBorder() const`
- L126 _private function_ `EVisibility GetDirtyImageVisibility() const`
- L142 _private member_ `TSharedPtr< IPropertyTableCell > Cell;`
- L143 _private member_ `TSharedPtr< FPropertyEditor > Editor;`
- L144 _private member_ `FName Style;`
- L145 _private member_ `const FSlateBrush* CellBackground = nullptr;`

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyTable/SRowHeaderColumnHeader.h` (Private)


#### class `SRowHeaderColumnHeader`  
`class SRowHeaderColumnHeader : public SColumnHeader`  
_L13-68_
- inherits: `SColumnHeader`
- L17 _public function_ `SLATE_BEGIN_ARGS( SRowHeaderColumnHeader ) : _Style( TEXT("PropertyTable") )`
- L20 _public prototype_ `SLATE_ARGUMENT( FName, Style ) SLATE_END_ARGS() ~SRowHeaderColumnHeader() = default;`
- L31 _public function_ `void Construct( const FArguments& InArgs, const TSharedRef< class IPropertyTableColumn >& InPropertyTableColumn, const TSharedRef< class IPropertyTableUtilities >& InPropertyUtilities )` — Construct this widget.  Called by the SNew() Slate macro. @param	InArgs				Declaration used by the SNew() macro to construct this widget @param	InViewModel			The UI logic not specific to slate
- L49 _public function_ `virtual TSharedRef< SWidget > GenerateCell( const TSharedRef< class IPropertyTableRow >& PropertyTableRow ) override`
- L67 _private member_ `FName Style;`

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyTable/STextColumnHeader.h` (Private)


#### class `STextColumnHeader`  
`class STextColumnHeader : public SColumnHeader`  
_L13-67_
- inherits: `SColumnHeader`
- L17 _public function_ `SLATE_BEGIN_ARGS( STextColumnHeader ) : _Style( TEXT("PropertyTable") )`
- L20 _public function_ `SLATE_ARGUMENT( FName, Style ) SLATE_ARGUMENT( TSharedPtr< IPropertyTableCustomColumn >, Customization ) SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TSharedRef< class IPropertyTableColumn >& InPropertyTableColumn, const TSharedRef< class IPropertyTableUtilities >& InPropertyUtilities )`
- L41 _public function_ `virtual TSharedRef< SWidget > GenerateCell( const TSharedRef< class IPropertyTableRow >& PropertyTableRow ) override`
- L66 _private member_ `FName Style;`

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyTable/TextPropertyTableCellPresenter.h` (Private)


#### class `FTextPropertyTableCellPresenter`  
`class FTextPropertyTableCellPresenter : public TSharedFromThis< FTextPropertyTableCellPresenter >, public IPropertyTableCellPresenter`  
_L13-57_
- inherits: `TSharedFromThis<FTextPropertyTableCellPresenter>,IPropertyTableCellPresenter`
- L17 _public prototype_ `FTextPropertyTableCellPresenter( const TSharedRef< class FPropertyEditor >& InPropertyEditor, const TSharedRef< class IPropertyTableUtilities >& InPropertyUtilities, FSlateFontInfo InFont = FAppStyle::GetFontStyle( PropertyTableConstants::NormalFontStyle ), const TSharedPtr< IPropertyTableCell >& InCell = nullptr );`
- L19 _public prototype_ `virtual ~FTextPropertyTableCellPresenter() = default;`
- L21 _public prototype_ `virtual TSharedRef< class SWidget > ConstructDisplayWidget() override;`
- L23 _public prototype_ `virtual bool RequiresDropDown() override;`
- L25 _public function_ `virtual const FSlateBrush* GetEditModeCellBrush() override`
- L27 _public prototype_ `virtual TSharedRef< class SWidget > ConstructEditModeCellWidget() override;`
- L29 _public prototype_ `virtual TSharedRef< class SWidget > ConstructEditModeDropDownWidget() override;`
- L31 _public prototype_ `virtual TSharedRef< class SWidget > WidgetToFocusOnEdit() override;`
- L33 _public prototype_ `virtual FString GetValueAsString() override;`
- L35 _public prototype_ `virtual FText GetValueAsText() override;`
- L37 _public function_ `virtual bool HasReadOnlyEditMode() override`
- L42 _private prototype_ `bool CalculateIfUsingReadOnlyEditingWidget() const;`
- L44 _private prototype_ `FSlateColor GetTextForegroundColor() const;`
- L48 _private member_ `TSharedPtr< class SWidget > PropertyWidget;`
- L50 _private member_ `TSharedRef< class FPropertyEditor > PropertyEditor;`
- L51 _private member_ `TSharedRef< class IPropertyTableUtilities > PropertyUtilities;`
- L53 _private member_ `TSharedPtr< IPropertyTableCell > Cell;`
- L55 _private member_ `bool HasReadOnlyEditingWidget;`
- L56 _private member_ `FSlateFontInfo Font;`

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyTree/PropertyTreeConstants.h` (Private)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace PropertyTreeConstants`
- L8 _variable_ `const FName ColumnId_Name( TEXT("Prope` (scope `PropertyTreeConstants`)
- L9 _variable_ `const FName ColumnId_Property( TEXT("Value` (scope `PropertyTreeConstants`)
- L11 _variable_ `const FText ColumnText_Name( NSLOCTEXT("PropertyEdito` (scope `PropertyTreeConstants`)
- L12 _variable_ `const FText ColumnText_Property( NSLOCTEXT("PropertyEdito` (scope `PropertyTreeConstants`)

### `Source/Editor/PropertyEditor/Private/UserInterface/PropertyTree/SPropertyTreeCategoryRow.h` (Private)


#### class `SPropertyTreeCategoryRow`  
`class SPropertyTreeCategoryRow : public STableRow< TSharedPtr< class FPropertyNode* > >`  
_L17-127_
- inherits: `STableRow<TSharedPtr<classFPropertyNode*>>`
- L21 _public function_ `SLATE_BEGIN_ARGS( SPropertyTreeCategoryRow ) : _DisplayName()`
- L24 _public function_ `SLATE_ARGUMENT( FText, DisplayName ) SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable )`
- L43 _public function_ `virtual void ConstructChildren( ETableViewMode::Type InOwnerTableMode, const TAttribute<FMargin>& InPadding, const TSharedRef<SWidget>& InContent ) override` — We override ConstructChildren because we want a border around the row to add some spacing between headers and have the expander spaced differently
- L97 _public function_ `virtual FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override`
- L109 _protected function_ `const FSlateBrush* GetInnerBackgroundImage() const`
- L120 _protected function_ `FMargin GetBorderPadding() const` — @return the margin corresponding to how far this item is indented

### `Source/Editor/PropertyEditor/Public/AsyncDetailViewDiff.h` (Public)


#### class `TTreeDiffSpecification`  
`template<> class TTreeDiffSpecification<TWeakPtr<FDetailTreeNode>>`  
_L10-53_
- L13 _public prototype_ `virtual ~TTreeDiffSpecification() = default;`
- L19 _public prototype_ `virtual bool AreValuesEqual(const TWeakPtr<FDetailTreeNode>& TreeNodeA, const TWeakPtr<FDetailTreeNode>& TreeNodeB) const;` — determine whether the values stored in two nodes are equal. @param TreeNodeA node from the first user provided tree (guaranteed not to be null) @param TreeNodeB node from the second user provided tree (guaranteed not to be null)
- L21 _public prototype_ `virtual bool AreValuesEqual(const TWeakPtr<FDetailTreeNode>& TreeNodeA, const TWeakPtr<FDetailTreeNode>& TreeNodeB, TArray<FPropertySoftPath>*) const final;` — `UE_DEPRECATED(5.6, "Output parameters wasn't generic and is no longer used.")`
- L30 _public prototype_ `virtual bool AreMatching(const TWeakPtr<FDetailTreeNode>& TreeNodeA, const TWeakPtr<FDetailTreeNode>& TreeNodeB) const;` — determine whether two nodes occupy the same space in their trees for example if you have a tree key/value pairs, AreMatching should compare the keys while AreValuesEqual should compare the values @param TreeNodeA node from the first user provided tree (guaranteed not to be null) @param TreeNodeB node from the second user provided tree (guaranteed not to be null)
- L32 _public prototype_ `virtual bool AreMatching(const TWeakPtr<FDetailTreeNode>& TreeNodeA, const TWeakPtr<FDetailTreeNode>& TreeNodeB, TArray<FPropertySoftPath>*) const final;` — `UE_DEPRECATED(5.6, "Output parameters wasn't generic and is no longer used.")`
- L39 _public prototype_ `virtual void GetChildren(const TWeakPtr<FDetailTreeNode>& InParent, TArray<TWeakPtr<FDetailTreeNode>>& OutChildren) const;` — retrieves an array of children nodes from the parent node @param InParent node from one of the two user provided trees (guaranteed not to be null) @param[out] OutChildren to be filled with the children of parent
- L46 _public prototype_ `virtual bool ShouldMatchByValue(const TWeakPtr<FDetailTreeNode>& TreeNode) const;` — return true for nodes that match using AreValuesEqual first, and pair up by position second this is useful for arrays since we often want to keep elements with the same data paired while diffing other elements in order @param TreeNode node from one of the two user provided trees (guaranteed not to be null)
- L52 _public prototype_ `virtual bool ShouldInheritEqualFromChildren(const TWeakPtr<FDetailTreeNode>& TreeNodeA, const TWeakPtr<FDetailTreeNode>& TreeNodeB) const;` — return true if TreeNode is considered equal when all it's children are equal. This avoids an unnecessary call to AreValuesEqual

#### class `FAsyncDetailViewDiff`  
`class FAsyncDetailViewDiff : public TAsyncTreeDifferences<TWeakPtr<FDetailTreeNode>>`  
_L57-78_
- inherits: `TAsyncTreeDifferences<TWeakPtr<FDetailTreeNode>>`
- desc: asynchronously update a difference tree with changes to details views note: users are expected to call TAsyncTreeDifferences::Tick or TAsyncTreeDifferences::FlushQueue to get accurate data
- L60 _public prototype_ `FAsyncDetailViewDiff(TSharedRef<IDetailsView> LeftView, TSharedRef<IDetailsView> RightView);`
- L64 _public prototype_ `void GetPropertyDifferences(TArray<FSingleObjectDiffEntry>& OutDiffEntries) const;` — Note: by default this list is not necessarily accurate or exhaustive. if you need a perfectly accurate list, call FlushQueue() first
- L69 _public prototype_ `TPair<int32, int32> ForEachRow(const TFunction<ETreeTraverseControl(const TUniquePtr<DiffNodeType>&, int32, int32)>& Method) const;` — execute a method for each node associated with a row in at least one details view method provides current left and right row number returns the number of rows in each details view
- L72 _public prototype_ `TArray<FVector2f> GenerateScrollSyncRate() const;` — generates scroll data used by LinkableScrollbar
- L75 _private prototype_ `static TAttribute<TArray<TWeakPtr<FDetailTreeNode>>> RootNodesAttribute(TWeakPtr<IDetailsView> DetailsView);`
- L76 _private member_ `TWeakPtr<IDetailsView> LeftView;`
- L77 _private member_ `TWeakPtr<IDetailsView> RightView;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API PROPERTYEDITOR_API`

### `Source/Editor/PropertyEditor/Public/DetailBuilderTypes.h` (Public)


#### struct `FAddPropertyParams`  
`struct FAddPropertyParams`  
_L12-129_
- desc: Parameters required for specifying behavior when adding external properties from detail customizations
- L14 _public function_ `FAddPropertyParams() : bForceShowProperty(false) , bHideRootObjectNode(false)`
- L23 _public function_ `FAddPropertyParams& ForceShowProperty()` — Forcibly show the property, even if it does not have CPF_Edit
- L33 _public function_ `FAddPropertyParams& AllowChildren(bool bAllowChildren)` — Override whether the property node should allow children or not. If not overridden the default is implementation defined.
- L43 _public function_ `FAddPropertyParams& CreateCategoryNodes(bool bCreateCategoryNodes)` — Override whether the property node should create category nodes or not. If not overridden the default is implementation defined.
- L53 _public function_ `FAddPropertyParams& UniqueId(FName InUniqueId)` — Set a unique name for this property, allowing it to correctly save expansion states and other persistent UI state
- L63 _public function_ `FAddPropertyParams& HideRootObjectNode(bool bInHideRootObjectNode)` — Override whether the root object node should be shown for external object properties. This only applies when adding an entire uobject's properties to the details panel rather than an individual row or struct
- L72 _public function_ `bool ShouldForcePropertyVisible() const` — Check whether to forcibly show the property, even if it does not have CPF_Edit
- L77 _public function_ `bool ShouldHideRootObjectNode() const`
- L83 _public function_ `void OverrideAllowChildren(bool& OutAllowChildren) const` — Conditionally overwrites the specified boolean with a value specifying whether to allow child properties or not. Only overrides the value if the calling code specified an override
- L96 _public function_ `void OverrideCreateCategoryNodes(bool& OutCreateCategoryNodes) const` — Conditionally overwrites the specified boolean with a value specifying whether to create category nodes or not Only overrides the value if the calling code specified an override
- L108 _public function_ `FName GetUniqueId() const` — Get this property's unique ID name
- L116 _private member_ `bool bForceShowProperty : 1;` — When true, the property will be forcefully shown, even if it does not have CPF_Edit. When false the property will only be created if it has CPF_Edit.
- L119 _private member_ `bool bHideRootObjectNode : 1;` — When true any root ObjectPropertyNode generated from an external UObject being added will be hidden from view and only its children are shown
- L122 _private member_ `TOptional<bool> bAllowChildrenOverride;` — Tristate override for allowing children - if value is true: Allow Children, false: Disallow Children, unset: no override
- L125 _private member_ `TOptional<bool> bCreateCategoryNodesOverride;` — Tristate override for allowing children - if value is true: create category nodes, false: do not create category nodes, unset: no override
- L128 _private member_ `FName UniqueIdName;` — Unique ID name that is used for saving persistent UI state such as expansion

### `Source/Editor/PropertyEditor/Public/DetailCategoryBuilder.h` (Public)


#### class `IDetailLayoutRow`  
`class IDetailLayoutRow`  
_L19-24_
- desc: Interface for the various types of rows that can be created through a detail layout customization
- L22 _public prototype_ `virtual FName GetRowName() const = 0;`
- L23 _public prototype_ `virtual TOptional<FResetToDefaultOverride> GetCustomResetToDefault() const = 0;`

#### enum `EPropertyLocation::Type`  
`enum Type`  
_L29-37_
- L32 _public enumerator_ `Common` — The property appears in the simple area of a category (displayed by default)
- L34 _public enumerator_ `Advanced` — The property appears in the advanced area of a category(collapsed by default)
- L36 _public enumerator_ `Default` — The property appears in the default way specified in the UPROPERTY class flag

#### class `IDetailCategoryBuilder`  
`class IDetailCategoryBuilder`  
_L43-261_
- desc: Represents a category for the a details view
- L46 _public prototype_ `virtual ~IDetailCategoryBuilder() = default;`
- L50 _public prototype_ `virtual IDetailCategoryBuilder& InitiallyCollapsed(bool bShouldBeInitiallyCollapsed) = 0;` — Whether or not the category should be initially collapsed
- L55 _public prototype_ `virtual IDetailCategoryBuilder& OnExpansionChanged(FOnBooleanValueChanged InOnExpansionChanged) = 0;` — Adds a delegate to the category which is called when the category expansion state changes
- L60 _public prototype_ `virtual IDetailCategoryBuilder& RestoreExpansionState(bool bRestore) = 0;` — Sets whether or not the expansion state should be restored between sessions
- L68 _public prototype_ `virtual IDetailCategoryBuilder& HeaderContent(TSharedRef<SWidget> InHeaderContent, bool bWholeRowContent = false) = 0;` — Adds header content to the category @param InHeaderContent	The header content widget @param bWholeRowContent	The header content should span the whole row (hides category name)
- L73 _public prototype_ `virtual int32 GetSortOrder() const = 0;` — Gets the current sort order of the category
- L78 _public prototype_ `virtual void SetSortOrder(int32 InSortOrder) = 0;` — Sets the sort order of the category
- L89 _public prototype_ `virtual IDetailPropertyRow& AddProperty(FName PropertyPath, UClass* ClassOutermost = nullptr, FName InstanceName = NAME_None, EPropertyLocation::Type Location = EPropertyLocation::Default) = 0;` — Adds a property, shown in the default way to the category @param Path						The path to the property.  Can be just a name of the property or a path in the format outer.outer.value[optional_index_for_static_arrays] @param ClassOutermost			Optional outer class if accessing a property outside of the current class being customized @param InstanceName				Optional instance name if multiple FProperty's of the same type exist. such as two identical structs, the instance name is one of the struct variable names) @param Location				The location within the category where the property is shown See IDetailCategoryBuilder::GetProperty for clarification of parameters
- L97 _public prototype_ `virtual IDetailPropertyRow& AddProperty(TSharedPtr<IPropertyHandle> PropertyHandle, EPropertyLocation::Type Location = EPropertyLocation::Default) = 0;` — Adds a property, shown in the default way to the category @param PropertyHandle		The handle to the property to add @param Location				The location within the category where the property is shown
- L106 _public prototype_ `virtual IDetailPropertyRow* AddExternalObjects(const TArray<UObject*>& Objects, EPropertyLocation::Type Location = EPropertyLocation::Default, const FAddPropertyParams& Params = FAddPropertyParams()) = 0;` — Adds an entire external object to this category.  The object should not be one of the objects already visible by this details panel @param Objects		List of objects that contain the property @param Location		The location within the category where the property is shown @return A property row for customizing the property or NULL if the property could not be found
- L116 _public prototype_ `virtual IDetailPropertyRow* AddExternalObjectProperty(const TArray<UObject*>& Objects, FName PropertyName, EPropertyLocation::Type Location = EPropertyLocation::Default, const FAddPropertyParams& Params = FAddPropertyParams()) = 0;` — Adds an external object property that is not a property on the object(s) being customized @param Objects		List of objects that contain the property @param PropertyName	Optional name of the property to view.  If this is empty, the entire set of properties on the objects are added @param Location		The location within the category where the property is shown @return A property row for customizing the property or NULL if the property could not be found
- L125 _public prototype_ `virtual IDetailPropertyRow* AddExternalStructure(TSharedPtr<FStructOnScope> StructData, EPropertyLocation::Type Location = EPropertyLocation::Default) = 0;` — Adds an external standalone structure to this details panel @param StructData		Struct data to find the property within @param Location			The location within the category where the property is shown @return A property row for customizing the property or NULL if the property could not be found
- L135 _public prototype_ `virtual IDetailPropertyRow* AddExternalStructureProperty(TSharedPtr<FStructOnScope> StructData, FName PropertyName, EPropertyLocation::Type Location = EPropertyLocation::Default, const FAddPropertyParams& Params = FAddPropertyParams()) = 0;` — Adds an external property, that is contained within a UStruct, that is not a property on the object(s) being customized @param StructData		Struct data to find the property within @param PropertyName		The name of the property to view.  If this is empty the entire structure is added @param Location			The location within the category where the property is shown @return A property row for customizing the property or NULL if the property could not be found
- L136 _public prototype_ `virtual IDetailPropertyRow* AddExternalStructureProperty(TSharedPtr<IStructureDataProvider> StructData, FName PropertyName, EPropertyLocation::Type Location = EPropertyLocation::Default, const FAddPropertyParams& Params = FAddPropertyParams()) = 0;`
- L146 _public prototype_ `virtual TArray<TSharedPtr<IPropertyHandle>> AddAllExternalStructureProperties(TSharedRef<FStructOnScope> StructData, EPropertyLocation::Type Location = EPropertyLocation::Default, TArray<IDetailPropertyRow*>* OutPropertiesRow = nullptr) = 0;` — Adds all properties for the specified external structure to this category @param StructData		External struct data to add to the root @param Location			The location within the category where the properties are to be shown @param PropertiesRow		Optional pointer to an array that will contains the IDetailPropertyRow of the properties added @return Array of all properties added to this category
- L147 _public prototype_ `virtual TArray<TSharedPtr<IPropertyHandle>> AddAllExternalStructureProperties(TSharedPtr<IStructureDataProvider> StructProvider, EPropertyLocation::Type Location = EPropertyLocation::Default, TArray<IDetailPropertyRow*>* OutPropertiesRow = nullptr) = 0;`
- L155 _public prototype_ `virtual FDetailWidgetRow& AddCustomRow(const FText& FilterString, bool bForAdvanced = false) = 0;` — Adds a custom widget row to the category @param FilterString	 A string which is used to filter this custom row when a user types into the details panel search box @param bForAdvanced	 Whether the widget should appear in the advanced section
- L163 _public prototype_ `virtual void AddCustomBuilder(TSharedRef<IDetailCustomNodeBuilder> InCustomBuilder, bool bForAdvanced = false) = 0;` — Adds a custom builder to the category (for more complicated layouts) @param InCustomBuilder				The custom builder to add @param bForAdvanced					true if this builder is for the advanced section of the category
- L173 _public prototype_ `virtual IDetailGroup& AddGroup(FName GroupName, const FText& LocalizedDisplayName, bool bForAdvanced = false, bool bStartExpanded = false) = 0;` — Adds a group to the category @param GroupName	The name of the group @param LocalizedDisplayName	The display name of the group @param true if the group should appear in the advanced section of the category @param true if the group should start expanded
- L182 _public prototype_ `virtual void GetDefaultProperties(TArray<TSharedRef<IPropertyHandle> >& OutAllProperties, bool bSimpleProperties = true, bool bAdvancedProperties = true) = 0;` — Gets the default properties of this category @param OutAllProperties		The list of property handles that will be populated @param bSimpleProperties		true to get simple properties @param bAdvancedProperties	true to get advanded properties
- L187 _public prototype_ `virtual class IDetailLayoutBuilder& GetParentLayout() const = 0;` — @return The parent layout builder of this class
- L192 _public prototype_ `virtual bool IsParentLayoutValid() const = 0;` — @return true if the parent layout is valid or has been destroyed by a refresh.
- L197 _public prototype_ `virtual const FText& GetDisplayName() const = 0;` — @return The localized display name of the category
- L202 _public prototype_ `virtual void SetDisplayName(const FText& DisplayName) = 0;` — Set a new display name for this category.
- L207 _public prototype_ `virtual const TOptional<FText>& GetToolTip() const = 0;` — Gets the localized tooltip for this category.
- L212 _public prototype_ `virtual void SetToolTip(const FText& ToolTip) = 0;` — Sets the localized tooltip for this category.
- L218 _public prototype_ `virtual void SetCategoryVisibility(bool bVisible) = 0;` — Sets whether or not this category is hidden or shown This is designed to be used for dynamic category visibility after construction of the category
- L224 _public prototype_ `virtual void SetShowAdvanced(bool bShowAdvanced) = 0;` — Sets whether or not this category should show its advanced properties. This is designed to be used for dynamic display of advanced properties.
- L227 _public prototype_ `virtual void AddPropertyDisableInstancedReference(TSharedPtr<IPropertyHandle> PropertyHandle) = 0;` — Add a property, but force it to behave as a normal, peer reference regardless of CPF_InstancedReference
- L230 _public function_ `virtual TSharedPtr<FOnPasteFromText> OnPasteFromText() const` — Optional PasteFromText delegate for this category
- L233 _public function_ `virtual TSharedPtr<FOnCopyToText> OnCopyToText() const` — Optional CopyToText delegate for this category
- L239 _public function_ `virtual bool IsEmpty() const` — If true, this Category should have no UProperty data associated with it, and will be shown as an empty stub with no expansion arrow
- L245 _public function_ `virtual void SetIsEmpty(bool bInIsEmpty)` — Sets whether this Category is "Empty" ~ that is, should have no UProperty data associated with it, and will be shown as an empty stub with no expansion arrow
- L250 _public prototype_ `virtual TOptional<FLinearColor> GetColor() const = 0;` — If valid, the color that represented the category. It can be used to visually identify the category quickly.
- L255 _public prototype_ `virtual void SetColor(FLinearColor InColor) = 0;` — Set the color that represents the category.
- L260 _public prototype_ `virtual void ClearColor() = 0;` — Clear the color that represents the category.

#### Free symbols / members of external scopes

- L27 _namespace_ `namespace EPropertyLocation`

### `Source/Editor/PropertyEditor/Public/DetailColumnSizeData.h` (Public)


#### class `FDetailColumnSizeData`  
`class FDetailColumnSizeData`  
_L9-90_
- L13 _public function_ `FDetailColumnSizeData()`
- L33 _public function_ `TAttribute<float> GetNameColumnWidth() const`
- L34 _public function_ `TAttribute<float> GetValueColumnWidth() const`
- L35 _public function_ `TAttribute<float> GetWholeRowColumnWidth() const`
- L36 _public function_ `TAttribute<float> GetRightColumnWidth() const`
- L37 _public function_ `TAttribute<float> GetRightColumnMinWidth() const`
- L38 _public function_ `TAttribute<int> GetHoveredSplitterIndex() const`
- L40 _public function_ `const SSplitter::FOnSlotResized& GetOnNameColumnResized() const`
- L41 _public function_ `const SSplitter::FOnSlotResized& GetOnValueColumnResized() const`
- L42 _public function_ `const SSplitter::FOnSlotResized& GetOnWholeRowColumnResized() const`
- L43 _public function_ `const SSplitter::FOnSlotResized& GetOnRightColumnResized() const`
- L44 _public function_ `const SSplitter::FOnHandleHovered& GetOnSplitterHandleHovered() const`
- L46 _public function_ `void SetValueColumnWidth(float NewWidth)`
- L52 _public function_ `void SetRightColumnMinWidth(float NewMinWidth)`
- L58 _private member_ `float ValueColumnWidthValue;`
- L59 _private member_ `float RightColumnWidthValue;`
- L60 _private member_ `int HoveredSplitterIndexValue;`
- L62 _private member_ `TAttribute<float> NameColumnWidth;`
- L63 _private member_ `TAttribute<float> ValueColumnWidth;`
- L64 _private member_ `TAttribute<float> WholeRowColumnWidth;`
- L65 _private member_ `TAttribute<float> RightColumnWidth;`
- L66 _private member_ `TAttribute<float> RightColumnMinWidth;`
- L67 _private member_ `TAttribute<int32> HoveredSplitterIndex;`
- L68 _private member_ `SSplitter::FOnSlotResized OnNameColumnResized;`
- L69 _private member_ `SSplitter::FOnSlotResized OnValueColumnResized;`
- L70 _private member_ `SSplitter::FOnSlotResized OnWholeRowColumnResized;`
- L71 _private member_ `SSplitter::FOnSlotResized OnRightColumnResized;`
- L72 _private member_ `SSplitter::FOnHandleHovered OnSplitterHandleHovered;`
- L74 _private function_ `float GetNameColumnWidthValue() const`
- L75 _private function_ `float GetValueColumnWidthValue() const`
- L76 _private function_ `float GetWholeRowColumnWidthValue() const`
- L77 _private function_ `int32 GetHoveredSplitterIndexValue() const`
- L78 _private function_ `float GetRightColumnWidthValue() const`
- L80 _private function_ `void OnSetRightColumnWidth(float NewWidth)`
- L86 _private function_ `void OnSetHoveredSplitterIndex(int32 HoveredIndex)`

#### Free symbols / members of external scopes

- L29 _function_ `OnWholeRowColumnResized.BindLambda([](float) {});` (scope `FDetailColumnSizeData::FDetailColumnSizeData`) — these are intentionally left no-op, since the widths are derived from the other column width
- L30 _function_ `OnNameColumnResized.BindLambda([](float) {});` (scope `FDetailColumnSizeData::FDetailColumnSizeData`)

### `Source/Editor/PropertyEditor/Public/DetailLayoutBuilder.h` (Public)


#### enum `ECategoryPriority::Type`  
`enum Type`  
_L18-29_
- L22 _public enumerator_ `Variable = 0` — Highest sort priority
- L23 _public enumerator_ `Transform`
- L24 _public enumerator_ `Important`
- L25 _public enumerator_ `TypeSpecific`
- L26 _public enumerator_ `Default`
- L28 _public enumerator_ `Uncommon` — Lowest sort priority

#### class `IDetailLayoutBuilder`  
`class IDetailLayoutBuilder`  
_L35-329_
- desc: The builder for laying custom details
- L39 _public typedef_ `using FOnCategorySortOrderFunction = TFunction<void(const TMap<FName, IDetailCategoryBuilder*>& )>;`
- L41 _public prototype_ `virtual ~IDetailLayoutBuilder()= default;`
- L46 _public function_ `static FSlateFontInfo GetDetailFont()` — @return the font used for properties and details
- L51 _public function_ `static FSlateFontInfo GetDetailFontBold()` — @return the bold font used for properties and details
- L56 _public function_ `static FSlateFontInfo GetDetailFontItalic()` — @return the italic font used for properties and details
- L61 _public prototype_ `virtual TSharedPtr<const IDetailsView> GetDetailsViewSharedPtr() const = 0;` — @return the parent detail view for this layout builder
- L64 _public function_ `const IDetailsView* GetDetailsView() const` — `UE_DEPRECATED(5.5, "Use GetDetailsViewSharedPtr() instead.")`
- L72 _public prototype_ `virtual TSharedPtr<IDetailsView> GetDetailsViewSharedPtr() = 0;` — @return the parent detail view for this layout builder
- L75 _public function_ `IDetailsView* GetDetailsView()` — `UE_DEPRECATED(5.5, "Use GetDetailsViewSharedPtr() instead.")`
- L83 _public prototype_ `virtual UClass* GetBaseClass() const = 0;` — @return The base class of the objects being customized in this detail layout
- L89 _public prototype_ `virtual const TArray< TWeakObjectPtr<UObject> >& GetSelectedObjects() const = 0;` — Get the root objects observed by this layout. This is not guaranteed to be the same as the objects customized by this builder.  See GetObjectsBeingCustomized for that.
- L96 _public prototype_ `template <typename ObjectType = UObject> TArray< TWeakObjectPtr<ObjectType> > GetSelectedObjectsOfType() const;` — Get the root objects (of ObjectType) observed by this layout. This is not guaranteed to be the same as the objects customized by this builder.  See GetObjectsBeingCustomized for that.
- L103 _public prototype_ `virtual void GetObjectsBeingCustomized( TArray< TWeakObjectPtr<UObject> >& OutObjects ) const = 0;` — Gets the current object(s) being customized by this builder If this is a sub-object customization it will return those sub objects.  Otherwise the root objects will be returned.
- L112 _public prototype_ `template <typename ObjectType = UObject> TArray< TWeakObjectPtr<ObjectType> > GetObjectsOfTypeBeingCustomized() const;` — Gets the current object(s) being customized by this builder of ObjectType If this is a sub-object customization it will return those sub objects.  Otherwise the root objects will be returned. @return true if one or more objects of ObjectType were found.
- L119 _public prototype_ `virtual void GetStructsBeingCustomized( TArray< TSharedPtr<FStructOnScope> >& OutStructs ) const = 0;` — Gets the current struct(s) being customized by this builder If this is a sub-struct customization it will return those sub struct.  Otherwise the root struct will be returned.
- L124 _public prototype_ `virtual TSharedRef<IPropertyUtilities> GetPropertyUtilities() const = 0;` — @return the utilities various widgets need access to certain features of PropertyDetails
- L134 _public prototype_ `virtual IDetailCategoryBuilder& EditCategory(FName CategoryName, const FText& NewLocalizedDisplayName = FText::GetEmpty(), ECategoryPriority::Type CategoryType = ECategoryPriority::Default) = 0;` — Edits an existing category or creates a new one @param CategoryName				The name of the category @param NewLocalizedDisplayName	The new display name of the category (optional) @param CategoryType				Category type to define sort order.  Category display order is sorted by this type (optional)
- L144 _public prototype_ `virtual IDetailCategoryBuilder& EditCategoryAllowNone(FName CategoryName, const FText& NewLocalizedDisplayName = FText::GetEmpty(), ECategoryPriority::Type CategoryType = ECategoryPriority::Default) = 0;` — Edits an existing category or creates a new one If CategoryName is NAME_None, will enable access to properties without categories @param CategoryName				The name of the category @param NewLocalizedDisplayName	The new display name of the category (optional) @param CategoryType				Category type to define sort order.  Category display order is sorted by this type (optional)
- L150 _public prototype_ `virtual void GetCategoryNames(TArray<FName>& OutCategoryNames) const = 0;` — Gets the current set of existing category names. This includes both categories derived from properties and categories added via EditCategory. @param	OutCategoryNames	 The array of category names
- L158 _public prototype_ `virtual void SortCategories(const FOnCategorySortOrderFunction& SortFunction) = 0;` — Adds sort algorythm which overrides standard algorythm with that provided by the caller. Function called on each category after all categories have been added, and provides caller with ability to override sort order. @param 	SortFunction Function called on final pass of detail panel build, which provides map of all categories to set final sort order on.
- L165 _public prototype_ `virtual IDetailPropertyRow& AddPropertyToCategory(TSharedPtr<IPropertyHandle> InPropertyHandle) = 0;` — Adds the property to its given category automatically. Useful in detail customizations which want to preserve categories. @param InPropertyHandle			The handle to the property that you want to add to its own category. @return the property row with which the property was added.
- L173 _public prototype_ `virtual FDetailWidgetRow& AddCustomRowToCategory(TSharedPtr<IPropertyHandle> InPropertyHandle, const FText& InCustomSearchString, bool bForAdvanced = false) = 0;` — Adds a custom row to the property's category automatically. Useful in detail customizations which want to preserve categories. @param InPropertyHandle			The handle to the property that you want to add to its own category. @param InCustomSearchString		A string which is used to filter this custom row when a user types into the details panel search box. @return the detail widget that can be further customized.
- L183 _public prototype_ `virtual TSharedPtr<IPropertyHandle> AddObjectPropertyData(TConstArrayView<UObject*> Objects, FName PropertyName) = 0;` — Adds an external object's property to this details panel's PropertyMap. Allows getting the property handle for the property without having to generate a row widget. @param Objects		List of objects that contain the property. @param PropertyName	Name of the property to generate a node from. @return The property handle created tied to generated property node.
- L193 _public prototype_ `virtual TSharedPtr<IPropertyHandle> AddStructurePropertyData(const TSharedPtr<FStructOnScope>& StructData, FName PropertyName) = 0;` — Adds an external structure's property data to this details panel's PropertyMap. Allows getting the property handle for the property without having to generate a row widget. @param StructData    Struct data to find the property within. @param PropertyName	Name of the property to generate a node from. @return			    The property handle tied to the generated property node.
- L203 _public prototype_ `virtual IDetailPropertyRow* EditDefaultProperty(TSharedPtr<IPropertyHandle> InPropertyHandle) = 0;` — Allows for the customization of a property row for a property that already exists on a class being edited in the details panel The property will remain in the default location but the widget or other attributes for the property can be changed Note This cannot be used to customize other customizations @param InPropertyHandle	The handle to the property that you want to edit @return					The property row to edit or nullptr if the property row does not exist
- L212 _public prototype_ `virtual IDetailPropertyRow* EditPropertyFromRoot(TSharedPtr<IPropertyHandle> InPropertyHandle) = 0;` — Get the property row from the root of the details panel after it's been constructed, so this will work with default or custom properties @param InPropertyHandle	The handle to the property that you want to edit @return					The property row to edit or nullptr if the property row does not exist, which may happen if not constructed yet
- L217 _public prototype_ `virtual bool DoesCategoryHaveGeneratedChildren(FName CategoryName) = 0;` — @return true if the category contains child rows.
- L224 _public prototype_ `virtual void HideCategory( FName CategoryName ) = 0;` — Hides an entire category @param CategoryName	The name of the category to hide
- L251 _public prototype_ `virtual TSharedRef<IPropertyHandle> GetProperty( const FName PropertyPath, const UStruct* ClassOutermost = NULL, FName InstanceName = NAME_None ) const = 0;` — Gets a handle to a property which can be used to read and write the property value and identify the property in other detail customization interfaces. Instructions @param Path	The path to the property.  Can be just a name of the property or a path in the format outer.outer.value[optional_index_for_static_arrays] @param ClassOutermost	Optional outer class if accessing a property outside of the current class being customized @param InstanceName		Optional instance name if multiple FProperty's of the same type exist. such as two identical structs, the instance name is one of the struct variable names) Examples: struct MyStruct { int32 StaticArray[3]; float FloatVar; } class MyActor { MyStruct Struct1; MyStruct Struct2; float MyFloat } To access StaticArray at index 2 from Struct2 in MyActor, your path would be MyStruct.StaticArray[2]" and your instance name is "Struct2" To access MyFloat in MyActor you can just pass in "MyFloat" because the name of the property is unambiguous
- L259 _public prototype_ `virtual FName GetTopLevelProperty() = 0;`
- L266 _public prototype_ `virtual void HideProperty( const TSharedPtr<IPropertyHandle> PropertyHandle ) = 0;` — Hides a property from view @param PropertyHandle	The handle of the property to hide from view
- L277 _public prototype_ `virtual void HideProperty( FName PropertyPath, const UStruct* ClassOutermost = NULL, FName InstanceName = NAME_None ) = 0;` — Hides a property from view @param Path						The path to the property.  Can be just a name of the property or a path in the format outer.outer.value[optional_index_for_static_arrays] @param NewLocalizedDisplayName	Optional display name to show instead of the default name @param ClassOutermost			Optional outer class if accessing a property outside of the current class being customized @param InstanceName				Optional instance name if multiple FProperty's of the same type exist. such as two identical structs, the instance name is one of the struct variable names) See IDetailCategoryBuilder::GetProperty for clarification of parameters
- L283 _public prototype_ `virtual void ForceRefreshDetails() = 0;` — Refreshes the details view and regenerates all the customized layouts Use only when you need to remove or add complicated dynamic items
- L288 _public prototype_ `virtual TSharedPtr<class FAssetThumbnailPool> GetThumbnailPool() const = 0;` — Gets the thumbnail pool that should be used for rendering thumbnails in the details view
- L293 _public prototype_ `virtual bool IsPropertyVisible( TSharedRef<IPropertyHandle> PropertyHandle ) const = 0;` — @return true if the property should be visible in the details panel or false if the specific details panel is not showing this property
- L298 _public prototype_ `virtual bool IsPropertyVisible( const struct FPropertyAndParent& PropertyAndParent ) const = 0;` — @return true if the property should be visible in the details panel or false if the specific details panel is not showing this property
- L303 _public prototype_ `virtual bool HasClassDefaultObject() const = 0;` — @return True if an object in the builder is a class default object
- L311 _public prototype_ `virtual void RegisterInstancedCustomPropertyTypeLayout(FName PropertyTypeName, FOnGetPropertyTypeCustomizationInstance PropertyTypeLayoutDelegate, TSharedPtr<IPropertyTypeIdentifier> Identifier = nullptr) = 0;` — Registers a custom detail layout delegate for a specific type in this layout only @param PropertyTypeName	The type the custom detail layout is for @param DetailLayoutDelegate	The delegate to call when querying for custom detail layouts for the classes properties
- L318 _public prototype_ `virtual void SetPropertyGenerationAllowListPaths(const TSet<FString>& InPropertyGenerationAllowListPaths) = 0;` — This function sets property paths to generate PropertyNodes.This improves the performance for cases where PropertyView is only showing a few properties of the object by not generating all other PropertyNodes @param InPropertyGenerationAllowListPaths Set of the property paths
- L323 _public prototype_ `virtual bool IsPropertyPathAllowed(const FString& InPath) const = 0;` — @return True if the property path is contained within our allowed paths
- L328 _public prototype_ `virtual void DisableInstancedReference(TSharedRef<IPropertyHandle> PropertyHandle) const = 0;` — Force a property to behave as a normal, peer reference regardless of CPF_InstancedReference
- L332 _function_ `template <typename ObjectType> TArray<TWeakObjectPtr<ObjectType>> IDetailLayoutBuilder::GetSelectedObjectsOfType() const`
- L352 _function_ `template <typename ObjectType> TArray<TWeakObjectPtr<ObjectType>> IDetailLayoutBuilder::GetObjectsOfTypeBeingCustomized() const`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace ECategoryPriority`
- L340 _function_ `` (scope `IDetailLayoutBuilder::GetSelectedObjectsOfType`)
- L363 _function_ `` (scope `IDetailLayoutBuilder::GetObjectsOfTypeBeingCustomized`)

### `Source/Editor/PropertyEditor/Public/DetailRowMenuContext.h` (Public)


#### class `UDetailRowMenuContext`  
`class UDetailRowMenuContext : public UObject`  
_L13-30_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L19 _public function_ `TMulticastDelegate<void()>& ForceRefreshWidget()` — Optionally invoke to refresh the widget.
- L22 _public member_ `TArray<TSharedPtr<IPropertyHandle>> PropertyHandles;` — PropertyHandles associated with the Row.
- L25 _public member_ `TWeakPtr<IDetailsView> DetailsView;` — Containing DetailsView.
- L29 _private member_ `TMulticastDelegate<void()> ForceRefreshWidgetDelegate;` — Optionally invoke to refresh the widget.

### `Source/Editor/PropertyEditor/Public/DetailTreeNode.h` (Public)


#### enum `ENodeVisibility`  
`enum class ENodeVisibility : uint8`  
_L25-33_
- L28 _public enumerator_ `HiddenDueToFiltering` — Hidden but can be visible if parent is visible due to filtering
- L30 _public enumerator_ `ForcedHidden` — Never visible no matter what
- L32 _public enumerator_ `Visible` — Always visible

#### class `FDetailTreeNode`  
`class FDetailTreeNode : public IDetailTreeNode`  
_L35-190_
- inherits: `IDetailTreeNode`
- L40 _public prototype_ `virtual FNodeWidgets CreateNodeWidgets() const;` — IDetailTreeNode interface
- L41 _public prototype_ `virtual void GetChildren(TArray<TSharedRef<IDetailTreeNode>>& OutChildren, const bool& bInIgnoreVisibility = false);`
- L42 _public function_ `virtual TSharedPtr<IDetailPropertyRow> GetRow() const override`
- L43 _public function_ `virtual void GetFilterStrings(TArray<FString>& OutFilterStrings) const override`
- L44 _public function_ `virtual bool GetInitiallyCollapsed() const override`
- L47 _public prototype_ `virtual TSharedPtr<IDetailsViewPrivate> GetDetailsViewSharedPtr() const = 0;` — @return The details view that this node is in
- L50 _public function_ `IDetailsViewPrivate* GetDetailsView() const` — `UE_DEPRECATED(5.5, "Use GetDetailsViewSharedPtr() instead.")`
- L61 _public prototype_ `virtual TSharedRef< ITableRow > GenerateWidgetForTableView(const TSharedRef<STableViewBase>& OwnerTable, bool bAllowFavoriteSystem) = 0;` — Generates the widget representing this node @param OwnerTable		The table owner of the widget being generated @param PropertyUtilities	Property utilities to help generate widgets
- L63 _public prototype_ `virtual bool GenerateStandaloneWidget(FDetailWidgetRow& OutRow) const = 0;`
- L68 _public prototype_ `virtual void FilterNode(const FDetailFilter& InFilter) = 0;` — Filters this nodes visibility based on the provided filter strings
- L76 _public prototype_ `virtual void GetChildren(FDetailNodeList& OutChildren, const bool& bInIgnoreVisibility = false) = 0;` — Gets child tree nodes @param OutChildren			The array to add children to @param bInIgnoreVisibility	Ignore the child node visibility
- L81 _public function_ `TWeakPtr<FDetailTreeNode> GetParentNode() const` — @ The parent DetailTreeNode of this node, or nullptr if this is a root node (or not yet added to a tree)
- L88 _public function_ `void SetParentNode(TWeakPtr<FDetailTreeNode> InParentNode)` — Sets the parent node. The parent node's GetChildren() call should include this node. @param The new parent for this node
- L99 _public prototype_ `const UStruct* GetParentBaseStructure() const;` — Finds the immediate UScriptStruct or UClass containing this node, which is found through a series of checks: 1. Get the corresponding property node and find the nearest object or struct property containing the property 2. If that fails, each parent node is checked with the same criteria as above 3. If that fails, the base structure of the detail layout containing this node is used 4. If that fails, the class of the first selected object in the details view is used @return The best matching UStruct that was responsible for creating this node
- L104 _public prototype_ `static const UStruct* GetPropertyNodeBaseStructure(const FPropertyNode* PropertyNode);` — A helper function for GetParentBaseStructure that gets the parent specifically for a property node instead of a detail node
- L109 _public prototype_ `virtual void OnItemExpansionChanged(bool bIsExpanded, bool bShouldSaveState) = 0;` — Called when the item is expanded in the tree
- L114 _public prototype_ `virtual bool ShouldBeExpanded() const = 0;` — @return Whether or not the tree node should be expanded
- L119 _public prototype_ `virtual ENodeVisibility GetVisibility() const = 0;` — @return the visibility of this node in the tree
- L124 _public function_ `virtual void RefreshVisibility()` — updates the visibility of this node if necessary
- L129 _public prototype_ `virtual void Tick(float DeltaTime) = 0;` — Called each frame if the node requests that it should be ticked
- L134 _public prototype_ `virtual bool ShouldShowOnlyChildren() const = 0;` — @return true to ignore this node for visibility in the tree and only examine children
- L139 _public prototype_ `virtual FName GetNodeName() const = 0;` — The identifier name of the node
- L144 _public function_ `virtual TSharedPtr<FDetailCategoryImpl> GetParentCategory() const` — @return The category node that this node is nested in, if any:
- L149 _public function_ `virtual FPropertyPath GetPropertyPath() const` — @return The property path that this node is associate with, if any:
- L154 _public function_ `virtual void SetIsHighlighted(bool bInIsHighlighted)` — Called when the node should appear 'highlighted' to draw the users attention to it
- L159 _public function_ `virtual bool IsHighlighted() const` — @return true if the node has been highlighted
- L164 _public function_ `virtual bool IsLeaf()` — @return true if this is a leaf node:
- L169 _public function_ `virtual TAttribute<bool> IsPropertyEditingEnabled() const` — @return TAttribute indicating whether editing is enabled or whether the property is readonly:
- L174 _public function_ `virtual TSharedPtr<FPropertyNode> GetPropertyNode() const` — Gets the property node associated with this node.  Not all nodes have properties so this will fail for anything other than a property row or for property rows that have complex customizations that ignore the property
- L179 _public function_ `virtual void GetAllPropertyNodes(TArray<TSharedRef<FPropertyNode>>& OutNodes) const` — In certain circumstances a single DetailTreeNode can have multiple property nodes. This will get all of them.
- L184 _public function_ `virtual TSharedPtr<FComplexPropertyNode> GetExternalRootPropertyNode() const` — Gets the external property node associated with this node.  This will return nullptr for all rows expect property rows which were generated from an external root.
- L189 _private member_ `TWeakPtr<FDetailTreeNode> ParentNode = nullptr;` — The parent whose GetChildren() call will return this node. This can be null for root nodes or nodes not added to the tree yet.

#### Free symbols / members of external scopes

- L23 _typedef_ `typedef TArray<TSharedRef<FDetailTreeNode>> FDetailNodeList;`

### `Source/Editor/PropertyEditor/Public/DetailWidgetRow.h` (Public)


#### class `FDetailWidgetDecl`  
`class FDetailWidgetDecl`  
_L22-97_
- desc: Widget declaration for custom widgets in a widget row
- L26 _public function_ `FDetailWidgetDecl( class FDetailWidgetRow& InParentDecl, float InMinWidth, float InMaxWidth, EHorizontalAlignment InHAlign, EVerticalAlignment InVAlign ) : Widget( SNew( SInvalidDetailWidget ) ) , HorizontalAlignment( InHAlign ) , VerticalAlignment( InVAlign ) , MinWidth( InMinWidth ) , MaxWidth( InMaxWidth ) , ParentDecl( &InParentDecl )`
- L36 _public function_ `FDetailWidgetDecl( class FDetailWidgetRow& InParentDecl, const FDetailWidgetDecl& Other ) : Widget( Other.Widget ) , HorizontalAlignment( Other.HorizontalAlignment ) , VerticalAlignment( Other.VerticalAlignment ) , MinWidth( Other.MinWidth ) , MaxWidth( Other.MaxWidth ) , ParentDecl( &InParentDecl )`
- L46 _public function_ `FDetailWidgetRow& operator[]( TSharedRef<SWidget> InWidget )`
- L52 _public function_ `FDetailWidgetDecl& VAlign( EVerticalAlignment InAlignment )`
- L58 _public function_ `FDetailWidgetDecl& HAlign( EHorizontalAlignment InAlignment )`
- L64 _public function_ `FDetailWidgetDecl& MinDesiredWidth( TOptional<float> InMinWidth )`
- L70 _public function_ `FDetailWidgetDecl& MaxDesiredWidth( TOptional<float> InMaxWidth )`
- L90 _public member_ `TSharedRef<SWidget> Widget;`
- L91 _public member_ `EHorizontalAlignment HorizontalAlignment;`
- L92 _public member_ `EVerticalAlignment VerticalAlignment;`
- L93 _public member_ `TOptional<float> MinWidth;`
- L94 _public member_ `TOptional<float> MaxWidth;`
- L96 _private member_ `class FDetailWidgetRow* ParentDecl;`

#### class `FDetailWidgetDecl::SInvalidDetailWidget`  
`class SInvalidDetailWidget : public SSpacer`  
_L77-88_
- inherits: `SSpacer`
- L79 _private function_ `SLATE_BEGIN_ARGS( SInvalidDetailWidget )`
- L81 _private function_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs )`

#### class `FDetailWidgetRow`  
`class FDetailWidgetRow : public IDetailLayoutRow`  
_L105-452_
- inherits: `IDetailLayoutRow`
- desc: Represents a single row of custom widgets in a details panel
- L108 _public member_ `const static float DefaultValueMinWidth;`
- L109 _public member_ `const static float DefaultValueMaxWidth;`
- L111 _public function_ `FDetailWidgetRow() : NameWidget( *this, 0.0f, 0.0f, HAlign_Left, VAlign_Center ) , ValueWidget( *this, DefaultValueMinWidth, DefaultValueMaxWidth, HAlign_Left, VAlign_Center ) , ExtensionWidget( *this, 0.0f, 0.0f, HAlign_Right, VAlign_Center) , ResetToDefaultWidget( *this, 0.0f, 0.0f, HAlign_Center, VAlign_Center) , WholeRowWidget( *this, 0.0f, 0.0f, HAlign_Fill, VAlign_Fill ) , VisibilityAttr( EVisibility::Visible ) , FilterTextString() , CopyMenuAction() , PasteMenuAction() , RowTagName()`
- L125 _public function_ `FDetailWidgetRow& operator=(const FDetailWidgetRow& Other)`
- L148 _public prototype_ `virtual ~FDetailWidgetRow() = default;`
- L151 _public function_ `virtual FName GetRowName() const override` — IDetailLayoutRow interface
- L152 _public function_ `virtual TOptional<FResetToDefaultOverride> GetCustomResetToDefault() const override`
- L157 _public function_ `FDetailWidgetRow& operator[]( TSharedRef<SWidget> InWidget )` — Assigns content to the entire row
- L166 _public function_ `FDetailWidgetDecl& WholeRowContent()` — Assigns content to the whole slot, this is an explicit alternative to using []
- L174 _public function_ `FDetailWidgetDecl& NameContent()` — Assigns content to just the name slot
- L182 _public function_ `FDetailWidgetDecl& ValueContent()` — Assigns content to the value slot
- L190 _public function_ `FDetailWidgetDecl& ExtensionContent()` — Assigns content to the extension (right) slot
- L198 _public function_ `FDetailWidgetDecl& ResetToDefaultContent()` — Assigns content to the reset to default (right-most) slot
- L206 _public function_ `FDetailWidgetRow& FilterString( const FText& InFilterString )` — Sets a string which should be used to filter the content when a user searches
- L215 _public function_ `FDetailWidgetRow& Visibility( const TAttribute<EVisibility>& InVisibility )` — Sets the visibility of the entire row
- L224 _public function_ `FDetailWidgetRow& IsEnabled( const TAttribute<bool>& InIsEnabled )` — Sets the enabled state of the entire row
- L233 _public function_ `FDetailWidgetRow& IsValueEnabled( const TAttribute<bool>& InIsEnabled )` — Sets the enabled state of the value widget only
- L242 _public function_ `FDetailWidgetRow& CopyAction( const FUIAction& InCopyAction )` — Sets a custom copy action to take when copying the data from this row
- L251 _public function_ `FDetailWidgetRow& PasteAction( const FUIAction& InPasteAction )` — Sets a custom paste action to take when copying the data from this row
- L260 _public function_ `FDetailWidgetRow& AddCustomContextMenuAction(const FUIAction& Action, const FText& Name, const FText& Tooltip = FText(), const FSlateIcon& SlateIcon = FSlateIcon())` — Add a custom action to the row context menu
- L266 _public function_ `bool HasNameContent() const`
- L271 _public function_ `bool HasValueContent() const`
- L276 _public function_ `bool HasExtensionContent() const`
- L281 _public function_ `bool HasResetToDefaultContent() const`
- L289 _public function_ `bool HasColumns() const` — @return true if the row has columns, false if it spans the entire row
- L297 _public function_ `bool HasAnyContent() const` — @return true of the row has any content
- L303 _public function_ `bool IsCopyPasteBound() const` — @return true if a custom copy/paste is bound on this row
- L309 _public function_ `bool IsPasteFromTextBound() const` — @return true if a custom paste text is bound on this row
- L315 _public function_ `bool IsCopyToTextBound() const` — @return true if a custom copy text is bound on this row
- L323 _public function_ `FDetailWidgetRow& RowTag(const FName& InRowTagName)` — Sets a tag which can be used to identify this row
- L332 _public function_ `FDetailWidgetRow& OverrideResetToDefault(const FResetToDefaultOverride& InResetToDefaultOverride)` — Sets flag to indicate if property value differs from the default
- L341 _public function_ `FDetailWidgetRow& EditCondition(TAttribute<bool> InEditConditionValue, FOnBooleanValueChanged InOnEditConditionValueChanged)` — Override the edit condition.
- L351 _public function_ `FDetailWidgetRow& DragDropHandler(TSharedPtr<IDetailDragDropHandler> InDragDropHandler)` — Sets a handler for the row to be a source or target of drag-and-drop operations.
- L360 _public function_ `FDetailWidgetRow& PropertyHandleList(const TArray<TSharedPtr<IPropertyHandle>>& InPropertyHandles)` — Used to provide all the property handles this WidgetRow represent
- L369 _public function_ `const TArray<TSharedPtr<IPropertyHandle>>& GetPropertyHandles() const` — Return all the property handles this WidgetRow represent
- L376 _public function_ `FDetailWidgetRow& ShouldAutoExpand(bool bForceExpansion = true)` — Sets whether or not this property should auto-expand @param bForceExpansion	true to force the property to be expanded
- L384 _public member_ `FDetailWidgetDecl NameWidget;` — Name column content
- L386 _public member_ `FDetailWidgetDecl ValueWidget;` — Value column content
- L388 _public member_ `FDetailWidgetDecl ExtensionWidget;` — Extension (right) column content
- L390 _public member_ `FDetailWidgetDecl ResetToDefaultWidget;` — Reset to default (right-most) column content
- L392 _public member_ `FDetailWidgetDecl WholeRowWidget;` — Whole row content
- L394 _public member_ `TAttribute<EVisibility> VisibilityAttr;` — Visibility of the row
- L396 _public member_ `TAttribute<bool> IsEnabledAttr;` — IsEnabled of the row
- L398 _public member_ `TAttribute<bool> IsValueEnabledAttr;` — IsEnabled of the value widget only
- L400 _public member_ `FText FilterTextString;` — String to filter with
- L402 _public member_ `FUIAction CopyMenuAction;` — Action for copying data on this row
- L404 _public member_ `FUIAction PasteMenuAction;` — Action for pasting data on this row
- L406 _public member_ `TWeakPtr<FOnPasteFromText> OnPasteFromTextDelegate;` — Delegate for pasting (optionally tagged) text on this row
- L408 _public member_ `TWeakPtr<FOnCopyToText> OnCopyToTextDelegate;` — Optional Delegate for copying text on this row (default property handle copy used if unbound)
- L437 _public member_ `TArray<FCustomMenuData> CustomMenuItems;` — Custom Action on this row
- L439 _public member_ `FName RowTagName;` — Tag to identify this row
- L441 _public member_ `TOptional<FResetToDefaultOverride> CustomResetToDefault;` — Custom reset to default handler
- L443 _public member_ `TAttribute<bool> EditConditionValue;` — Custom edit condition value.
- L445 _public member_ `FOnBooleanValueChanged OnEditConditionValueChanged;` — Custom edit condition value changed handler.
- L447 _public member_ `TSharedPtr<IDetailDragDropHandler> CustomDragDropHandler;` — Custom handler for drag-and-drop of the row
- L449 _public member_ `TArray<TSharedPtr<IPropertyHandle>> PropertyHandles;` — All property handle that this custom widget represent
- L451 _public member_ `TOptional<bool> ForceAutoExpansion;` — True to force auto-expansion

#### struct `FDetailWidgetRow::FCustomMenuData`  
`struct FCustomMenuData`  
_L410-435_
- L412 _public function_ `FCustomMenuData(const FUIAction& InAction, const FText& InName, const FText& InTooltip, const FSlateIcon& InSlateIcon) : Action(InAction) , Name(InName) , Tooltip(InTooltip) , SlateIcon(InSlateIcon)`
- L419 _public function_ `FCustomMenuData(const FName InEntryName, const FUIAction& InAction, const FText& InName, const FText& InTooltip, const FSlateIcon& InSlateIcon) : EntryName(InEntryName) , Action(InAction) , Name(InName) , Tooltip(InTooltip) , SlateIcon(InSlateIcon)`
- L427 _public member_ `const FName EntryName;`
- L428 _public member_ `const FUIAction Action;`
- L429 _public member_ `const FText Name;`
- L430 _public member_ `const FText Tooltip;`
- L431 _public member_ `const FSlateIcon SlateIcon;`
- L434 _public prototype_ `const FName GetEntryName() const;` — Returns the EntryName if specified, otherwise derive from Name.

#### Free symbols / members of external scopes

- L100 _variable_ `static FName InvalidDetailWidgetName = TEXT("SIn`

### `Source/Editor/PropertyEditor/Public/DetailsDisplayManager.h` (Public)


#### class `FDetailsDisplayManager`  
`class FDetailsDisplayManager : public TSharedFromThis<FDetailsDisplayManager>`  
_L21-187_
- inherits: `TSharedFromThis<FDetailsDisplayManager>`
- desc: An @code FDetailsDisplayManager @endcode provides an API to tweak various settings of your details view, and provides some utility methods to work with Details.
- L24 _public prototype_ `DECLARE_DELEGATE(FResetToDefault);`
- L26 _public member_ `FOnDetailsNeedsUpdate OnDetailsNeedsUpdate;`
- L28 _public prototype_ `FDetailsDisplayManager();`
- L30 _public prototype_ `virtual ~FDetailsDisplayManager();`
- L32 _public prototype_ `virtual TOptional<bool> OverrideCreateCategoryNodes() const;`
- L37 _public prototype_ `virtual bool ShouldHideComponentEditor();` — Returns a boolean indicating if the Component Editor should be hidden
- L43 _public prototype_ `static bool GetForceShowSubObjectEditor();` — Returns a boolean indicating whether the sub-object editor should show regardless of any object filter preference settings this would override any value retrieved from ShouldHideComponentEditor.
- L49 _public prototype_ `virtual bool ShouldShowCategoryMenu();` — Returns a @code bool @endcode indicating whether this @code DetailsViewObjectFilter @endcode instance should show a category menu
- L56 _public prototype_ `virtual TSharedPtr<SWidget> GetCategoryMenu(FName InCategoryObjectName);` — Gets the category menu SWidget and returns a shared pointer to it @param InCategoryObjectName the name of the category
- L61 _public prototype_ `void UpdateView() const;` — Updates the current details view
- L66 _public prototype_ `virtual const FDetailsViewStyleKey& GetDetailsViewStyleKey() const;` — Returns the @code FDetailsViewStyleKey @endcode that is the Key to the current FDetailsViewStyle style
- L69 _public prototype_ `void SetIsOuterCategory(bool bInIsOuterCategory);` — sets whether the currently active category is an Outer category
- L74 _public prototype_ `const FDetailsViewStyle* GetDetailsViewStyle() const;` — Returns the @code FDetailsViewStyle @endcode that is the current FDetailsViewStyle style
- L81 _public prototype_ `virtual bool GetIsScrollBarNeeded() const;` — Returns a bool indicating whether or not the scrollbar is needed on the details view. Note that the "needed" here means that in this value the work has been done to figure out if the scrollbar should show, and anything can query this to see if it needs to alter the display accordingly
- L90 _public prototype_ `virtual void SetIsScrollBarNeeded(bool bInIsScrollBarNeeded);` — Set a bool indicating whether or not the scrollbar is needed on the details view. Note that the "needed" here means that in this value the work has been done to figure out if the scrollbar should show, and anything can query this to see if it needs to alter the display accordingly @param bInIsScrollBarNeeded a bool indicating whether or not the scrollbar is Needed on the details view
- L95 _public prototype_ `FMargin GetTablePadding() const;` — Returns the FMargin which provides the padding around the whole details view table
- L100 _public function_ `virtual bool SupportsDetailTreeOverlay() const` — Returns whether or not this display manager provides a widget to overlay over the detail tree.  This can be used to facilitate interactions like drag and drop.
- L106 _public prototype_ `virtual TSharedRef<SWidget> ConstructDetailTreeOverlay();` — Returns a widget which will be put in an overlay slot which is over the detail tree portion of the widget. @note Implementations must manage hit test visibility of the supplied widget carefully to prevent blocking UI interactions with the detail tree widgets.
- L118 _public prototype_ `virtual bool AddEmptyCategoryToDetailLayoutIfNeeded(TSharedRef<FComplexPropertyNode> Node, TSharedRef<FDetailLayoutBuilderImpl> DetailLayoutBuilder);` — If TSharedRef<FComplexPropertyNode> Node has a valid UObject instance, add an empty properties Category to the DetailLayoutBuilder @param Node the FComplexPropertyNode that wil be added as a property to the new Category @param DetailLayoutBuilder The FDetailLayoutBuilderImpl that will have a stub category added to it @return true if the Category was successfully added to FDetailLayoutBuilderImpl& DetailLayoutBuilder, else it returns false
- L128 _public prototype_ `virtual TSharedPtr<FPropertyUpdatedWidgetBuilder> GetPropertyUpdatedWidget(FResetToDefault ResetToDefault, bool bIsCategoryUpdateWidget = false, FName InCategoryObjectName = NAME_None);` — `UE_DEPRECATED(5.5, "Use ConstructPropertyUpdatedWidgetBuilder")` — Returns a widget which will show in place of the reset to default button, or a nullptr if the default reset button should be used @param ResetToDefault the delegate which should be called to reset the row to default @param bIsCategoryUpdateWidget if true this widget builder is for a Category instead of a property within @param InCategoryObjectName  the name of the UObject associated with the Category for the widget builder, if one exists, else it is NAME_NONE
- L138 _public prototype_ `virtual TSharedPtr<FPropertyUpdatedWidgetBuilder> GetPropertyUpdatedWidget(FResetToDefault ResetToDefault, TSharedRef<FEditPropertyChain> InEditorPropertyChain, FName InCategoryObjectName);` — `UE_DEPRECATED(5.5, "Use ConstructPropertyUpdatedWidgetBuilder")` — Returns a widget which will show in place of the reset to default button, or a nullptr if the default reset button should be used @param ResetToDefault the delegate which should be called to reset the row to default @param InEditorPropertyChain the FEditorPropertyChain for the FPropertyNode whose state is visualized by this  property updated widget @param InCategoryObjectName the name of the UObject for which the Category is displayed, if one is associated with the Category
- L145 _public prototype_ `virtual bool CanConstructPropertyUpdatedWidgetBuilder() const;` — `UE_DEPRECATED(5.5, "Experimental API")` — If returning true, the row widgets (ie. SDetailSingleItemRow, SDetailCategoryTableRow) will call ConstructPropertyUpdatedWidgetBuilder. Enables potentially expensive setup to be elided
- L152 _public prototype_ `virtual TSharedPtr<FPropertyUpdatedWidgetBuilder> ConstructPropertyUpdatedWidgetBuilder(const FConstructPropertyUpdatedWidgetBuilderArgs& Args);` — `UE_DEPRECATED(5.5, "Experimental API")` — Returns a builder class which will generate a widget in place of the Extension widgets on an item row. For non-item rows (ie. category), a widget will be placed in the same location
- L154 _public prototype_ `void UpdatePropertyForCategory(FName InCategoryObjectName, FProperty* Property, bool bAddProperty);`
- L156 _public prototype_ `bool GetCategoryHasAnyUpdatedProperties(FName InCategoryObjectName) const;`
- L164 _public prototype_ `virtual bool ShowEmptyCategoryIfRootUObjectHasNoPropertyData(UObject* InNode) const;` — Returns true if the specified UObject is a Root Node Object and should show an empty Category stub even if it has no UProperty Data, else it returns false @param InNode the @code UObject* @endcode which will be tested to see if it needs an empty category stub
- L172 _protected member_ `FDetailsViewStyleKey PrimaryStyleKey;` — The primary style key for the details view.
- L177 _protected member_ `bool bIsOuterCategory;` — A bool indicating whether or not the currently active category is an outer category
- L183 _protected member_ `bool bIsScrollBarNeeded = false;` — a bool indicating whether or not the scrollbar is needed on the details view. Note that the "needed" here means that in this value the work has been done to figure out if the scrollbar should show
- L186 _protected member_ `TMap<FName, TSet<FProperty*>> CategoryNameToUpdatePropertySetMap;` — A map of category object name to a set of properties that has been updated for it

#### struct `FConstructPropertyUpdatedWidgetBuilderArgs`  
`struct FConstructPropertyUpdatedWidgetBuilderArgs`  
_L189-198_
- L191 _public prototype_ `~FConstructPropertyUpdatedWidgetBuilderArgs();`
- L193 _public member_ `FExecuteAction ResetToDefaultAction;`
- L194 _public member_ `TSharedPtr<FPropertyPath> PropertyPath;`
- L195 _public member_ `FName Category = NAME_None;`
- L196 _public member_ `FExecuteAction InvalidateCachedState;`
- L197 _public member_ `TArray<TWeakObjectPtr<UObject>>* Objects = nullptr;`

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_DELEGATE(FOnDetailsNeedsUpdate) class FDetailsViewStyle;`
- L24 _delegate_ `DECLARE_DELEGATE(FResetToDefault);`

### `Source/Editor/PropertyEditor/Public/DetailsNameWidgetOverrideCustomization.h` (Public)


#### class `FDetailsNameWidgetOverrideCustomization`  
`class FDetailsNameWidgetOverrideCustomization : public TSharedFromThis<FDetailsNameWidgetOverrideCustomization>`  
_L13-34_
- inherits: `TSharedFromThis<FDetailsNameWidgetOverrideCustomization>`
- desc: A customization applied to the whole details panel which can update any Name widget
- L19 _public prototype_ `explicit FDetailsNameWidgetOverrideCustomization();` — default constructor
- L24 _public prototype_ `virtual ~FDetailsNameWidgetOverrideCustomization() = default;` — destructor
- L33 _public prototype_ `virtual TSharedRef<SWidget> CustomizeName( TSharedRef<SWidget> InnerNameContent, FPropertyPath& Path);` — @param InnerNameContent the unaltered content of the Name widget. It shows what would be there normally with no modification by this customization @param Path the FPropertyPath for the current property @return the new TSharedRef<SWidget> for the Name widget if one is provided, else it returns the default Name widget for the current property path

### `Source/Editor/PropertyEditor/Public/DetailsViewArgs.h` (Public)


#### enum `EEditDefaultsOnlyNodeVisibility`  
`enum class EEditDefaultsOnlyNodeVisibility : uint8`  
_L20-28_
- L23 _public enumerator_ `Show` — Always show nodes that have the EditDefaultsOnly aka CPF_DisableEditOnInstance flag.
- L25 _public enumerator_ `Hide` — Always hide nodes that have the EditDefaultsOnly aka CPF_DisableEditOnInstance flag.
- L27 _public enumerator_ `Automatic` — Let the details panel control it. If the CDO is selected EditDefaultsOnly nodes will be visible, otherwise false.

#### struct `FDetailsViewArgs`  
`struct FDetailsViewArgs`  
_L33-217_
- desc: Init params for a details view widget
- L62 _public member_ `EEditDefaultsOnlyNodeVisibility DefaultsOnlyVisibility;` — Controls how CPF_DisableEditOnInstance nodes will be treated
- L64 _public member_ `TSharedPtr<FUICommandList> HostCommandList;` — The command list from the host of the details view, allowing child widgets to bind actions with a bound chord
- L66 _public member_ `TSharedPtr<FTabManager> HostTabManager;` — The tab manager from the host of the details view, allowing child widgets to spawn tabs
- L68 _public member_ `TSharedPtr<FDetailsViewObjectFilter> ObjectFilter;` — Optional object filter to use for more complex handling of what a details panel is viewing.
- L70 _public member_ `TArray<TSharedRef<IClassViewerFilter>> ClassViewerFilters;` — Optional custom filter(s) to apply to the class viewer widget for class object property values.
- L72 _public member_ `TSharedPtr<SScrollBar> ExternalScrollbar;` — Externally constructed Scrollbar (internally constructed if not provided)
- L74 _public member_ `EHorizontalAlignment ScrollbarAlignment;` — whether to display scrollbar on the left or the right of the panel
- L76 _public member_ `TSharedPtr<FDetailsViewStyleKey> StyleKey;` — A @code TSharedPtr<FDetailsViewStyleKey> @endcode which provides the key to the Details View's style
- L78 _public member_ `TSharedPtr<FDetailsNameWidgetOverrideCustomization> DetailsNameWidgetOverrideCustomization;` — A Customization that can be applied to all name widgets
- L80 _public member_ `TSharedPtr<FExtender> OptionsExtender;` — If bShowOptions menu is available, adds support for user defined menu options
- L82 _public member_ `FName ViewIdentifier;` — Identifier for this details view; NAME_None if this view is anonymous
- L84 _public member_ `EExpansionPersistenceMethod ExpansionPersistenceMethod;` — Persistence method for expansion in this details view
- L86 _public member_ `FNotifyHook* NotifyHook;` — Notify hook to call when properties are changed
- L88 _public member_ `int32 NameAreaSettings;` — Settings for displaying the name area (@see ENameAreaSettings)
- L90 _public member_ `float ColumnWidth;` — The default value column width, as a percentage, 0-1.
- L92 _public member_ `float RightColumnMinWidth;` — The minimum width of the right column in Slate units.
- L94 _public member_ `bool bUpdatesFromSelection : 1;` — True if the viewed objects updates from editor selection
- L96 _public member_ `bool bLockable : 1;` — True if this property view can be locked
- L98 _public member_ `bool bAllowSearch : 1;` — True if we allow searching
- L100 _public member_ `bool bHideSelectionTip : 1;` — True if you want to not show the tip when no objects are selected (should only be used if viewing actors properties or bObjectsUseNameArea is true )
- L102 _public member_ `bool bSearchInitialKeyFocus : 1;` — True if you want the search box to have initial keyboard focus
- L104 _public member_ `bool bShowPropertyMatrixButton : 1;` — True if the 'Open Selection in Property Matrix' button should be shown
- L106 _public member_ `bool bShowOptions : 1;` — Allow options to be changed
- L108 _public member_ `bool bShowHeaders : 1;` — Allow headers to be hidden
- L110 _public member_ `bool bShowObjectLabel : 1;` — True if you want to show the object label
- L112 _public member_ `bool bShowActorLabel : 1;` — `UE_DEPRECATED(5.0, "bShowActorLabel has been renamed bShowObjectLabel")`
- L114 _public member_ `bool bShowModifiedPropertiesOption : 1;` — True if you want to show the 'Show Only Modified Properties' option. Only valid in conjunction with bShowOptions
- L116 _public member_ `bool bShowDifferingPropertiesOption : 1;` — True if you want to show the 'Show Only Differing Properties' option. Only valid in conjunction with bShowOptions.
- L118 _public member_ `bool bShowHiddenPropertiesWhilePlayingOption : 1;` — True if you want to show the 'Show Hidden Properties While Playing' option. Only valid in conjunction with bShowOptions.
- L120 _public member_ `bool bCustomNameAreaLocation : 1;` — If true, the name area will be created but will not be displayed so it can be placed in a custom location.
- L122 _public member_ `bool bCustomFilterAreaLocation : 1;` — If true, the filter area will be created but will not be displayed so it can be placed in a custom location.
- L124 _public member_ `bool bAllowFavoriteSystem : 1;` — If false, the current properties editor will never display the favorite system
- L126 _public member_ `bool bAllowMultipleTopLevelObjects : 1;` — If true the details panel will assume each object passed in through SetObjects will be a unique object shown in the tree and not combined with other objects
- L128 _public member_ `bool bShowScrollBar : 1;` — If false, the details panel's scrollbar will always be hidden. Useful when embedding details panels in widgets that either grow to accommodate them, or with scrollbars of their own.
- L130 _public member_ `bool bForceHiddenPropertyVisibility : 1;` — If true, all properties will be visible, not just those with CPF_Edit
- L132 _public member_ `bool bShowKeyablePropertiesOption : 1;` — True if you want to show the 'Show Only Keyable Properties'. Only valid in conjunction with bShowOptions
- L134 _public member_ `bool bShowAnimatedPropertiesOption: 1;` — True if you want to show the 'Show Only Animated Properties'. Only valid in conjunction with bShowOptions
- L136 _public member_ `bool bShowCustomFilterOption : 1;` — True if you want to show a custom filter.
- L138 _public member_ `bool bShowSectionSelector : 1;` — True if the section selector should be shown.
- L140 _public member_ `bool bShowLooseProperties : 1;` — If true, loose properties should be shown.
- L143 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FShouldForceHideProperty, const TSharedRef<IPropertyHandle>&);` — Delegate that determines whether a property should be forced hidden - evaluated on panel refresh
- L144 _public member_ `FShouldForceHideProperty ShouldForceHideProperty;`
- L147 _public member_ `TOptional<bool> bResolveInstanceDataObjects;` — Resolve any UObject* to their IDO counterparts if they exist
- L150 _public member_ `TSet<FName> InitialSections;` — Initial sections to be shown enabled in the filter
- L153 _public member_ `TSet<FName> InitialCategories;` — Initial categories to be shown enabled in the filter
- L157 _public function_ `FDetailsViewArgs() : DefaultsOnlyVisibility(EEditDefaultsOnlyNodeVisibility::Show) , ScrollbarAlignment(HAlign_Right) , DetailsNameWidgetOverrideCustomization(nullptr) , ViewIdentifier(NAME_None) , ExpansionPersistenceMethod(EExpansionPersistenceMethod::Default) , NotifyHook(nullptr) , NameAreaSettings(ActorsUseNameArea) , ColumnWidth(.6f) , RightColumnMinWidth(22) , bUpdatesFromSelection(false) , bLockable(false) , bAllowSearch(true) , bHideSelectionTip(false) , bSearchInitialKeyFocus(false) , bShowPropertyMatrixButton(true) , bShowOptions(true) , bShowHeaders(true) , bShowObjectLabel(true) , bShowModifiedPropertiesOption(true) , bShowDifferingPropertiesOption(false) , bShowHiddenPropertiesWhilePlayingOption(true) , bCustomNameAreaLocation(false) , bCustomFilterAreaLocation(false) , bAllowFavoriteSystem(false) , bAllowMultipleTopLevelObjects(false) , bShowScrollBar(true) , bForceHiddenPropertyVisibility(false) , bShowKeyablePropertiesOption(true) , bShowAnimatedPropertiesOption(true) , bShowCustomFilterOption(false) , bShowSectionSelector(false) , bShowLooseProperties(false)`
- L195 _public function_ `FDetailsViewArgs( const bool InUpdateFromSelection , const bool InLockable = false , const bool InAllowSearch = true , const ENameAreaSettings InNameAreaSettings = ActorsUseNameArea , const bool InHideSelectionTip = false , FNotifyHook* InNotifyHook = NULL , const bool InSearchInitialKeyFocus = false , FName InViewIdentifier = NAME_None ) : FDetailsViewArgs()` — `UE_DEPRECATED(5.0, "This constructor is deprecated, please create an empty FDetailsViewArgs and explicitly set any values that you wish to change.")` — Default constructor
- L215 _public prototype_ `FDetailsViewArgs(const FDetailsViewArgs&);`
- L216 _public prototype_ `FDetailsViewArgs& operator=(const FDetailsViewArgs&);`
- L220 _prototype_ `inline FDetailsViewArgs::FDetailsViewArgs(const FDetailsViewArgs&) = default;`
- L221 _prototype_ `inline FDetailsViewArgs& FDetailsViewArgs::operator=(const FDetailsViewArgs&) = default;`

#### enum `FDetailsViewArgs::ENameAreaSettings`  
`enum ENameAreaSettings`  
_L35-45_
- L38 _public enumerator_ `HideNameArea = 0` — The name area should never be displayed
- L40 _public enumerator_ `ObjectsUseNameArea = 1<<0` — All object types use the name area
- L42 _public enumerator_ `ActorsUseNameArea = 1<<1` — Actors prioritize using the name area
- L44 _public enumerator_ `ComponentsAndActorsUseNameArea = 1<<2 | ActorsUseNameArea` — Components and actors prioritize using the name area. Components will display their actor owner as the name

#### enum `FDetailsViewArgs::EExpansionPersistenceMethod`  
`enum class EExpansionPersistenceMethod : uint8`  
_L48-59_
- desc: Enum to set expansion persistence. Used to support saving expansion per details view.
- L51 _public enumerator_ `Default = 0` — Expansion will use default persistence (Global shared per struct type)
- L56 _public enumerator_ `TransientPerViewIdentifier = 1` — Expansion will be stored transiently per details view identifier and persist in a single editor session. The Expansion will be written to EditorPerProjectUserSettings.ini, but will be cleared without read on editor startup.
- L58 _public enumerator_ `PersistentPerViewIdentifier = 2` — Expansion will be stored per details view identifier and persist on disk.

#### Free symbols / members of external scopes

- L143 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FShouldForceHideProperty, const TSharedRef<IPropertyHandle>&);` — Delegate that determines whether a property should be forced hidden - evaluated on panel refresh

### `Source/Editor/PropertyEditor/Public/DetailsViewObjectFilter.h` (Public)


#### struct `FDetailsViewObjectRoot`  
`struct FDetailsViewObjectRoot`  
_L19-34_
- desc: An object root is a collection of UObjects that represent a top level set of properties in a details panel When there are multiple objects in the root, the common base class for all those objects are found and the properties on that common base class are displayed When a user edits one of those properties, it will propagate the result to all objects in the root. If multiple differing values are found on a single property, the details panel UI displays "multiple values"
- L21 _public function_ `FDetailsViewObjectRoot()`
- L24 _public function_ `FDetailsViewObjectRoot(UObject* InObject)`
- L29 _public function_ `FDetailsViewObjectRoot(TArray<UObject*> InObjects) : Objects(MoveTemp(InObjects))`
- L33 _public member_ `TArray<UObject*> Objects;`

#### class `FDetailsViewObjectFilter`  
`class FDetailsViewObjectFilter`  
_L41-83_
- desc: An object filter determines the root objects that should be displayed from a set of given source objects passed to the details panel. It can also be used to convey characteristics of a details view which may alter depending upon the type of objects that have been filtered.
- L45 _public function_ `explicit FDetailsViewObjectFilter()`
- L50 _public prototype_ `virtual ~FDetailsViewObjectFilter() = default;`
- L60 _public prototype_ `virtual TArray<FDetailsViewObjectRoot> FilterObjects(const TArray<UObject*>& SourceObjects) = 0;` — Given a const TArray<UObject*>& SourceObjects, it fills a TArray<FDetailsViewObjectRoot> with the objects that we need as details objects roots. This may be the same as the original SourceObjects, or it may be some subset of them, or some of their Sub-objects @param SourceObjects the array of objects acting as the Source of the root objects for the details view @return the TArray<FDetailsViewObjectRoot> with the objects that will act as root objects for the details view
- L63 _public function_ `virtual void UpdateFilterView() const` — Updates the view of anything being filtered by this filter
- L70 _public function_ `virtual TSharedPtr<FDetailsDisplayManager> GetDisplayManager()` — Returns a @code TSharedPtr @endcode to the @code FDetailsDisplayManager @endcode
- L81 _protected member_ `TSharedPtr<FDetailsDisplayManager> DisplayManager;` — The @code DetailsDisplayManager @endcode which provides an API to manage some of the characteristics of the details display

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_DELEGATE(FOnUpdateFilteredObjects) struct FDetailsViewObjectRoot { FDetailsViewObjectRoot() {} FDetailsViewObjectRoot(UObject* InObject) { Objects.Add(InObject); } FDetailsViewObjectRoot(TArray<UObject*> InObjects) : Objects(MoveTemp(InObjects)) {} TArray<UObject*> Objects; };`

### `Source/Editor/PropertyEditor/Public/DetailsViewStyleKey.h` (Public)


#### class `FDetailsViewStyleKey`  
`class FDetailsViewStyleKey`  
_L11-58_
- desc: A class which provides a strongly typed Key object for @code FDetailsViewStyleKey @endcode instances
- L17 _public prototype_ `FDetailsViewStyleKey();` — Default constructor for @code FDetailsViewStyleKey @endcode instances
- L22 _public prototype_ `FDetailsViewStyleKey(FDetailsViewStyleKey& Key);` — Copy Constructor for @code FDetailsViewStyleKey @endcode instances
- L27 _public prototype_ `FDetailsViewStyleKey(const FDetailsViewStyleKey& Key);` — const Copy Constructor for @code FDetailsViewStyleKey @endcode instances
- L34 _public prototype_ `FDetailsViewStyleKey& operator=(FDetailsViewStyleKey& OtherStyleKey);` — Assignment operator for @code FDetailsViewStyleKey @endcode instances. @param OtherStyleKey the key for the @code FDetailsViewStyleKey @endcode with which to initialize this @code FDetailsViewStyleKey @endcode
- L41 _public prototype_ `FDetailsViewStyleKey& operator=(const FDetailsViewStyleKey& OtherStyleKey);` — const assignment operator @code FDetailsViewStyleKey @endcode instances. @param OtherStyleKey the key for the @code FDetailsViewStyleKey @endcode with which to initialize this @code FDetailsViewStyleKey @endcode
- L43 _public prototype_ `bool operator==(const FDetailsViewStyleKey& OtherStyleKey) const;`
- L48 _public prototype_ `FName GetName() const;` — Returns the FName Name of this @code FDetailsViewStyleKey @endcode
- L53 _public prototype_ `FDetailsViewStyleKey(FName InName);` — A constructor for @code FDetailsViewStyleKey @endcode instances which takes an FName InName to initialize the leu
- L56 _private member_ `FName Name;`

#### class `FDetailsViewStyleKeys`  
`class FDetailsViewStyleKeys`  
_L63-91_
- desc: A Class which provides keys for @code FDetailsViewStyleKey @endcode instances
- L71 _public prototype_ `static const FDetailsViewStyleKey& Classic();` — Returns The Classic Details View style used in Unreal Engine 5.0 and prior, which has Categories displayed with no padding between them and no built in horizontal space
- L77 _public prototype_ `static const FDetailsViewStyleKey& Card();` — Returns A Details View style which presents with the top level Categories in a card-like fashion, with space between and around them.
- L83 _public prototype_ `static const FDetailsViewStyleKey& Default();` — The @code Default @endcode Details View style should be used when an object has no interest in displaying its own custom Details View and wants to default to whatever is the Primary Details View.
- L90 _public prototype_ `static bool IsDefault(const FDetailsViewStyleKey& StyleKey);` — Returns true if the @code const FDetailsViewStyleKey& @endcode is the @code Default @endcode Key, else it returns false. @param StyleKey a FDetailsViewStyleKey& to check whether it is the default

### `Source/Editor/PropertyEditor/Public/EditConditionEvaluator.h` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace EditConditionEvaluator`

### `Source/Editor/PropertyEditor/Public/IDetailChildrenBuilder.h` (Public)


#### class `IDetailChildrenBuilder`  
`class IDetailChildrenBuilder`  
_L21-146_
- desc: Builder for adding children to a detail customization
- L24 _public prototype_ `virtual ~IDetailChildrenBuilder() = default;`
- L32 _public prototype_ `virtual IDetailChildrenBuilder& AddCustomBuilder(TSharedRef<IDetailCustomNodeBuilder> InCustomBuilder) = 0;` — Adds a custom builder as a child @param InCustomBuilder		The custom builder to add
- L42 _public prototype_ `virtual IDetailGroup& AddGroup(FName GroupName, const FText& LocalizedDisplayName, const bool bStartExpanded=false) = 0;` — Adds a group to the category @param GroupName	The name of the group @param LocalizedDisplayName	The display name of the group @param bStartExpanded Set to true to force the category to expand by default @param true if the group should appear in the advanced section of the category
- L50 _public prototype_ `virtual IDetailGroup* GetGroup(FName GroupName) = 0;` — Get an existing group in the category @param GroupName	The name of the group @return a pointer to the group if it exists, otherwise nullptr
- L59 _public prototype_ `virtual FDetailWidgetRow& AddCustomRow(const FText& SearchString) = 0;`
- L67 _public prototype_ `virtual IDetailPropertyRow& AddProperty(TSharedRef<IPropertyHandle> PropertyHandle) = 0;` — Adds a property to the struct @param PropertyHandle	The handle to the property to add @return An interface to the property row that can be used to customize the appearance of the property
- L76 _public prototype_ `virtual IDetailPropertyRow* AddExternalObjects(const TArray<UObject*>& Objects, FName UniqueIdName = NAME_None) = 0;` — Adds a set of objects to as a child.  Similar to details panels, all objects will be visible in the details panel as set of properties from the common base class from the list of objects @param  Objects			The objects to add @param  UniqueIdName		Optional identifier that uniquely identifies this object among other objects of the same type.  If this is empty, saving and restoring expansion state of this object may not work @return The header row generated for this set of objects by the details panel
- L85 _public prototype_ `virtual IDetailPropertyRow* AddExternalObjects(const TArray<UObject*>& Objects, const FAddPropertyParams& Params = FAddPropertyParams()) = 0;` — Adds a set of objects to as a child.  Similar to details panels, all objects will be visible in the details panel as set of properties from the common base class from the list of objects @param  Objects			The objects to add @param  Params			Optional parameters for customizing the display of the property rows. @return The header row generated for this set of objects by the details panel
- L95 _public prototype_ `virtual IDetailPropertyRow* AddExternalObjectProperty(const TArray<UObject*>& Objects, FName PropertyName, const FAddPropertyParams& Params = FAddPropertyParams()) = 0;` — Adds a set of objects to as a child.  Similar to details panels, all objects will be visible in the details panel as set of properties from the common base class from the list of objects @param  Objects			The objects to add @param  PropertyName		Name of a property inside the object(s) to add. @param  Params			Optional parameters for customizing the display of the property rows. @return The header row generated for this set of objects by the details panel
- L105 _public prototype_ `virtual IDetailPropertyRow* AddExternalStructureProperty(TSharedRef<FStructOnScope> ChildStructure, FName PropertyName, const FAddPropertyParams& Params = FAddPropertyParams()) = 0;` — Adds a property from a custom structure as a child @param ChildStructure	The structure to add @param PropertyName		Optional name of a property inside the Child structure to add.  If this is empty, the entire structure will be added @param Params		    Optional identifier that uniquely identifies this structure among other structures of the same type.  If this is empty, saving and restoring expansion state of this structure may not work
- L106 _public prototype_ `virtual IDetailPropertyRow* AddExternalStructureProperty(TSharedPtr<IStructureDataProvider> ChildStructure, FName PropertyName, const FAddPropertyParams& Params = FAddPropertyParams()) = 0;`
- L107 _public prototype_ `virtual IDetailPropertyRow* AddChildStructureProperty(TSharedRef<IPropertyHandle> PropertyHandle, TSharedPtr<IStructureDataProvider> ChildStructure, FName PropertyName, const FAddPropertyParams& Params = FAddPropertyParams(), const FText& DisplayNameOverride = FText()) = 0;`
- L115 _public prototype_ `virtual IDetailPropertyRow* AddExternalStructure(TSharedRef<FStructOnScope> ChildStructure, FName UniqueIdName = NAME_None) = 0;` — Adds a custom structure as a child @param ChildStructure	The structure to add @param UniqueIdName		Optional identifier that uniquely identifies this structure among other structures of the same type.  If this is empty, saving and restoring expansion state of this structure may not work
- L116 _public prototype_ `virtual IDetailPropertyRow* AddExternalStructure(TSharedPtr<IStructureDataProvider> ChildStructure, FName UniqueIdName = NAME_None) = 0;`
- L117 _public prototype_ `virtual IDetailPropertyRow* AddChildStructure(TSharedRef<IPropertyHandle> PropertyHandle, TSharedPtr<IStructureDataProvider> ChildStructure, FName UniqueIdName = NAME_None, const FText& DisplayNameOverride = FText()) = 0;`
- L125 _public prototype_ `virtual TArray<TSharedPtr<IPropertyHandle>> AddAllExternalStructureProperties(TSharedRef<FStructOnScope> ChildStructure) = 0;` — Adds all the properties of an external structure as a children @param ChildStructure	The structure containing the properties to add @return An array of interfaces to the properties that were added
- L127 _public prototype_ `virtual TArray<TSharedPtr<IPropertyHandle>> AddAllExternalStructureProperties(TSharedPtr<IStructureDataProvider> ChildStructure) = 0;`
- L135 _public prototype_ `virtual TSharedRef<SWidget> GenerateStructValueWidget(TSharedRef<IPropertyHandle> StructPropertyHandle) = 0;` — Generates a value widget from a customized struct If the customized struct has no value widget an empty widget will be returned @param StructPropertyHandle	The handle to the struct property to generate the value widget from
- L140 _public prototype_ `virtual IDetailCategoryBuilder& GetParentCategory() const = 0;` — @return the parent category on the customized object that this children is in.
- L145 _public prototype_ `virtual IDetailGroup* GetParentGroup() const = 0;` — @return the parent group on the customized object that this children is in (if there is one)

### `Source/Editor/PropertyEditor/Public/IDetailCustomNodeBuilder.h` (Public)


#### class `IDetailCustomNodeBuilder`  
`class IDetailCustomNodeBuilder`  
_L15-73_
- desc: A custom node that can be given to a details panel category to customize widgets
- L18 _public prototype_ `virtual ~IDetailCustomNodeBuilder()= default;`
- L25 _public function_ `virtual void SetOnRebuildChildren(FSimpleDelegate InOnRegenerateChildren)` — Sets a delegate that should be used when the custom node needs to rebuild children @param A delegate to invoke when the tree should rebuild this nodes children
- L32 _public function_ `virtual void SetOnToggleExpansion(FOnToggleNodeExpansion InOnToggleExpansion)` — Sets a delegate that should be used when the custom node wants to expand @param A delegate to invoke when the tree should expand
- L40 _public prototype_ `virtual void GenerateHeaderRowContent( FDetailWidgetRow& NodeRow ) = 0;` — Called to generate content in the header of this node ( the actual node content ). Only called if HasHeaderRow is true @param NodeRow The row to put content in
- L47 _public function_ `virtual void GenerateChildContent( IDetailChildrenBuilder& ChildrenBuilder )` — Called to generate child content of this node @param ChildrenBuilder The builder to add child rows to.
- L52 _public function_ `virtual void Tick(float DeltaTime)` — Called each tick if RequiresTick is true
- L57 _public function_ `virtual bool RequiresTick() const` — @return true if this node requires tick, false otherwise
- L62 _public function_ `virtual bool InitiallyCollapsed() const` — @return true if this node should be collapsed in the tree
- L67 _public prototype_ `virtual FName GetName() const = 0;` — @return The name of this custom builder.  This is used as an identifier to save expansion state if needed
- L72 _public function_ `virtual TSharedPtr<IPropertyHandle> GetPropertyHandle() const` — @return The property associated with this builder (if any).

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_DELEGATE_OneParam(FOnToggleNodeExpansion, bool) class IDetailCustomNodeBuilder { public: virtual ~IDetailCustomNodeBuilder()= default; virtual void SetOnRebuildChildren(FSimpleDelegate InOnRegenerateChildren) {} virtual void SetOnToggleExpansion(FOnToggleNodeExpansion InOnToggleExpansion) {} virtual void GenerateHeaderRowContent( FDetailWidgetRow& NodeRow ) = 0; virtual void GenerateChildContent( IDetailChildrenBuilder& ChildrenBuilder ) {} /** * Called each tick if RequiresTick is true`

### `Source/Editor/PropertyEditor/Public/IDetailCustomization.h` (Public)


#### class `IDetailCustomization`  
`class IDetailCustomization : public TSharedFromThis<IDetailCustomization>`  
_L11-28_
- inherits: `TSharedFromThis<IDetailCustomization>`
- desc: Interface for any class that lays out details for a specific class
- L14 _public prototype_ `virtual ~IDetailCustomization() = default;`
- L17 _public function_ `virtual void PendingDelete()` — Called when no longer used and will be deleted
- L20 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) = 0;` — Called when details should be customized
- L26 _public function_ `virtual void CustomizeDetails( const TSharedPtr<IDetailLayoutBuilder>& DetailBuilder )` — Called when details should be customized, this version allows the customization to store a weak ptr to the layout builder. This allows property changes to trigger a force refresh of the detail panel.

### `Source/Editor/PropertyEditor/Public/IDetailDragDropHandler.h` (Public)


#### class `IDetailDragDropHandler`  
`class IDetailDragDropHandler`  
_L12-31_
- desc: Specifies how a widget row can initiate a drag-and-drop (be dragged) and/or act as the target of a drag-and-drop (be dropped onto).
- L15 _public prototype_ `virtual ~IDetailDragDropHandler() = default;`
- L18 _public prototype_ `virtual TSharedPtr<FDragDropOperation> CreateDragDropOperation() const = 0;` — Create a drag operation with the current widget row as the source.
- L21 _public prototype_ `virtual bool AcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone) const = 0;` — Accepts an arbitrary drag-and-drop (doesn't need to be from another widget row) with the current widget row as the target.
- L27 _public prototype_ `virtual TOptional<EItemDropZone> CanAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone) const = 0;` — Determines whether the drag-and-drop event contains data that can be accepted by the current widget row as the target. The handler can return a different drop zone if desired, or no drop zone if it can't accept the drop.
- L30 _public function_ `virtual bool UseHandleWidget() const` — Determines whether the reorder handle widget is added automatically.

### `Source/Editor/PropertyEditor/Public/IDetailGroup.h` (Public)


#### enum `EDetailGroupDisplayMode`  
`enum class EDetailGroupDisplayMode`  
_L16-20_
- desc: How the group should be formatted - either as a minor group, or identically to a major subcategory.
- L18 _public enumerator_ `Group`
- L19 _public enumerator_ `Category`

#### class `IDetailGroup`  
`class IDetailGroup : public IDetailLayoutRow`  
_L25-140_
- inherits: `IDetailLayoutRow`
- desc: A group in the details panel that can have children
- L28 _public prototype_ `virtual ~IDetailGroup() = default;`
- L35 _public prototype_ `virtual FDetailWidgetRow& HeaderRow() = 0;` — Makes a custom row for the groups header @return a new row for customizing the header
- L40 _public prototype_ `virtual IDetailPropertyRow& HeaderProperty( TSharedRef<IPropertyHandle> PropertyHandle ) = 0;` — Adds a property as the groups header
- L47 _public prototype_ `virtual FDetailWidgetRow& AddWidgetRow() = 0;` — Adds a new row for custom widgets * @return a new row for adding widgets
- L54 _public prototype_ `virtual IDetailPropertyRow& AddPropertyRow(TSharedRef<IPropertyHandle> PropertyHandle) = 0;` — Adds a new row for a property @return an interface for customizing the appearance of the property row
- L61 _public prototype_ `virtual IDetailPropertyRow& AddExternalStructureProperty(TSharedPtr<IStructureDataProvider> StructDataProvider, FName PropertyName, EPropertyLocation::Type Location, const FAddPropertyParams& Params) = 0;` — Adds a new row for an external struct property @return an interface for customizing the appearance of the property row
- L68 _public prototype_ `virtual IDetailPropertyRow& AddExternalObjectProperty(const TArray<UObject*>& Objects, FName PropertyName, EPropertyLocation::Type Location, const FAddPropertyParams& Params) = 0;` — Adds a new row for an external property @return an interface for customizing the appearance of the property row
- L77 _public prototype_ `virtual IDetailGroup& AddGroup(FName NewGroupName, const FText& InLocalizedDisplayName, bool bInStartExpanded = false) = 0;` — Adds a group to the category @param NewGroupName	The name of the group @param LocalizedDisplayName	The display name of the group @param true if the group should start expanded
- L82 _public prototype_ `virtual const TOptional<FText>& GetToolTip() const = 0;` — Gets the localized tooltip for this group.
- L87 _public prototype_ `virtual void SetToolTip(const FText& ToolTip) = 0;` — Sets the localized tooltip for this group.
- L94 _public prototype_ `virtual void ToggleExpansion( bool bExpand ) = 0;` — Toggles expansion on the group @param bExpand	true to expand the group, false to collapse
- L99 _public prototype_ `virtual bool GetExpansionState() const = 0;` — Gets the current state of expansion for the group
- L104 _public prototype_ `virtual void EnableReset(bool InValue) = 0;` — Permit resetting the properties in this group
- L109 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FDetailGroupReset);` — Delegate called when user press the Group Reset ui
- L114 _public prototype_ `virtual FDetailGroupReset& GetOnDetailGroupReset() = 0;` — Return the delegate called when user press the Group Reset ui
- L119 _public prototype_ `virtual FName GetGroupName() const = 0;` — Return the name associated with this group
- L124 _public prototype_ `virtual int32 GetNumChildren() const = 0;` — Returns the number of child rows under this group
- L129 _public prototype_ `virtual TSharedPtr<IDetailPropertyRow> FindPropertyRow(TSharedRef<IPropertyHandle> PropertyHandle) const = 0;` — Return the property row associated with the specified property handle
- L132 _public prototype_ `virtual void SetDisplayMode(EDetailGroupDisplayMode Mode) = 0;` — Specify whether this group should be formatted to display like a subcategory
- L135 _public function_ `virtual TSharedPtr<FOnPasteFromText> OnPasteFromText() const` — Return an optional PasteFromText delegate
- L138 _public function_ `virtual TSharedPtr<FOnCopyToText> OnCopyToText() const` — Return an optional CopyToText delegate

#### Free symbols / members of external scopes

- L109 _delegate_ `DECLARE_MULTICAST_DELEGATE(FDetailGroupReset);` — Delegate called when user press the Group Reset ui

### `Source/Editor/PropertyEditor/Public/IDetailKeyframeHandler.h` (Public)


#### enum `EPropertyKeyedStatus`  
`enum class EPropertyKeyedStatus : uint8`  
_L13-26_
- desc: Keyed Status of a Property, ordered by their precedence E.g. if a property is keyed in current and another frame, Keyed In Frame should take precedence
- L16 _public enumerator_ `NotKeyed` — Property not keyed, or not animated in current time
- L19 _public enumerator_ `KeyedInOtherFrame` — Property is animated in the current time, but there's no key in current frame
- L22 _public enumerator_ `PartiallyKeyed` — For Top-level properties only -- some but not all the properties of the struct are keyed in Current Frame
- L25 _public enumerator_ `KeyedInFrame` — Property (and all its sub-properties) are keyed in current frame

#### class `IDetailKeyframeHandler`  
`class IDetailKeyframeHandler`  
_L28-42_
- L31 _public prototype_ `virtual ~IDetailKeyframeHandler()= default;`
- L33 _public prototype_ `virtual bool IsPropertyKeyable(const UClass* InObjectClass, const IPropertyHandle& PropertyHandle) const = 0;`
- L35 _public prototype_ `virtual bool IsPropertyKeyingEnabled() const = 0;`
- L37 _public prototype_ `virtual void OnKeyPropertyClicked(const IPropertyHandle& KeyedPropertyHandle) = 0;`
- L39 _public prototype_ `virtual bool IsPropertyAnimated(const IPropertyHandle& PropertyHandle, UObject* ParentObject) const = 0;`
- L41 _public function_ `virtual EPropertyKeyedStatus GetPropertyKeyedStatus(const IPropertyHandle& PropertyHandle) const`

### `Source/Editor/PropertyEditor/Public/IDetailPropertyChildrenCustomizationHandler.h` (Public)


#### class `IDetailPropertyChildrenCustomizationHandler`  
`class IDetailPropertyChildrenCustomizationHandler`  
_L11-21_
- desc: Customizes properties children in a detail view.
- L14 _public prototype_ `virtual ~IDetailPropertyChildrenCustomizationHandler() = default;`
- L17 _public prototype_ `virtual bool ShouldCustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle) = 0;` — Returns true if the handler should override provided property's children.
- L20 _public function_ `virtual void CustomizeChildren(IDetailChildrenBuilder& ChildrenBuilder, TSharedPtr<IPropertyHandle> PropertyHandle)` — Gives a chance to customize provided property's children.

### `Source/Editor/PropertyEditor/Public/IDetailPropertyExtensionHandler.h` (Public)


#### class `IDetailPropertyExtensionHandler`  
`class IDetailPropertyExtensionHandler`  
_L12-53_
- L15 _public prototype_ `virtual ~IDetailPropertyExtensionHandler()= default;`
- L17 _public prototype_ `virtual bool IsPropertyExtendable(const UClass* InObjectClass, const IPropertyHandle& PropertyHandle) const = 0;`
- L20 _public function_ `virtual TSharedRef<SWidget> GenerateExtensionWidget(const UClass* InObjectClass, TSharedPtr<IPropertyHandle> PropertyHandle)` — `UE_DEPRECATED(4.24, "Please use ExtendWidgetRow")`
- L26 _public function_ `virtual TSharedRef<SWidget> GenerateExtensionWidget(const IDetailLayoutBuilder& InDetailBuilder, const UClass* InObjectClass, TSharedPtr<IPropertyHandle> PropertyHandle)` — `UE_DEPRECATED(5.0, "Please use ExtendWidgetRow")`
- L39 _public function_ `virtual void ExtendWidgetRow(FDetailWidgetRow& InWidgetRow, const IDetailLayoutBuilder& InDetailBuilder, const UClass* InObjectClass, TSharedPtr<IPropertyHandle> PropertyHandle)` — Gives the extension handler a chance to add extension widgets to the widget row. Typically, an extension handler can do so by using InWidgetRow.ExtensionContent(), but it can also modify other aspects of the widget row as well.

### `Source/Editor/PropertyEditor/Public/IDetailPropertyRow.h` (Public)


#### enum `ECustomEditConditionMode`  
`enum class ECustomEditConditionMode : uint8`  
_L18-24_
- L21 _public enumerator_ `Override` — The custom edit condition overrides the edit condition set directly on the property (if any). Only the custom edit condition must evaluate to true for the property to be editable.
- L23 _public enumerator_ `Merge` — The custom edit condition merges with the existing edit condition set directly on the property (if any). Both edit conditions must evaluate to true for the property to be editable.

#### class `FResetToDefaultOverride`  
`class FResetToDefaultOverride`  
_L29-174_
- desc: Structure describing the delegates needed to override the behavior of reset to default in detail properties
- L33 _public function_ `static FResetToDefaultOverride Create(FResetToDefaultHandler InResetToDefaultClicked, const bool InPropagateToChildren = false)` — Creates a FResetToDefaultOverride in which the the reset to default is always visible
- L44 _public function_ `static FResetToDefaultOverride Create(FIsResetToDefaultVisible InIsResetToDefaultVisible, FResetToDefaultHandler InResetToDefaultClicked, const bool InPropagateToChildren = false)` — Creates a FResetToDefaultOverride from visibility and click handler callback delegates
- L56 _public function_ `static FResetToDefaultOverride Create(TAttribute<bool> InIsResetToDefaultVisible, const bool InPropagateToChildren = false)` — Create a FResetToDefaultOverride from a visibility attribute.
- L67 _public function_ `static FResetToDefaultOverride Create(TAttribute<bool> InIsResetToDefaultVisible, FSimpleDelegate InResetToDefaultClicked, const bool InPropagateToChildren = false)` — Create a FResetToDefaultOverride from a visibility attribute and a simple delegate.
- L79 _public function_ `static FResetToDefaultOverride Create(FSimpleDelegate InResetToDefaultClicked, const bool InPropagateToChildren = false)` — Create a FResetToDefaultOverride from a simple delegate.
- L90 _public function_ `static FResetToDefaultOverride Hide(const bool InPropagateToChildren = false)` — Creates a FResetToDefaultOverride in which reset to default is never visible
- L100 _public function_ `bool IsResetToDefaultVisible(TSharedPtr<IPropertyHandle> Property) const` — Called by the UI to show/hide the reset widgets
- L126 _public function_ `bool HasResetToDefaultHandler() const` — Does this have a custom reset to default handler?
- L132 _public function_ `void OnResetToDefaultClicked(TSharedPtr<IPropertyHandle> PropertyHandle) const` — Called by the property editor to actually reset the property to default
- L145 _public function_ `FResetToDefaultHandler GetPropertyResetToDefaultDelegate() const` — Get the actual delegate bound to this reset to default handler.
- L148 _public function_ `bool PropagatesToChildren() const` — Called by properties to determine whether this override should set on their children
- L155 _private member_ `FIsResetToDefaultVisible IsVisiblePropertyDelegate;` — Callback to indicate whether or not reset to default is visible
- L158 _private member_ `FResetToDefaultHandler OnClickedPropertyDelegate;` — Delegate called when reset to default is clicked
- L161 _private member_ `TAttribute<bool> IsVisibleAttribute;` — Attribute to determine whether or not reset to default is visible
- L164 _private member_ `FSimpleDelegate OnClickedDelegate;` — Delegate called when reset to default is clicked
- L167 _private member_ `bool bPropagateToChildren;` — Should properties pass this on to their children?
- L170 _private member_ `bool bForceShow;` — Ignore the visibility delegate and always show the reset to default widgets?
- L173 _private member_ `bool bForceHide;` — Ignore the visibility delegate and never show the reset to default widgets?

#### class `IDetailPropertyRow`  
`class IDetailPropertyRow`  
_L179-314_
- desc: A single row for a property in a details panel
- L182 _public prototype_ `virtual ~IDetailPropertyRow()= default;`
- L185 _public prototype_ `virtual TSharedPtr<IPropertyHandle> GetPropertyHandle() const = 0;` — @return the property handle for the property on this row
- L192 _public prototype_ `virtual IDetailPropertyRow& DisplayName( const FText& InDisplayName ) = 0;` — Sets the localized display name of the property @param InDisplayName	The name of the property
- L199 _public prototype_ `virtual IDetailPropertyRow& ToolTip( const FText& InToolTip ) = 0;` — Sets the localized tooltip of the property @param InToolTip	The tooltip of the property
- L206 _public prototype_ `virtual IDetailPropertyRow& ShowPropertyButtons( bool bShowPropertyButtons ) = 0;` — Sets whether or not we show the default property editing buttons for this property @param bShowPropertyButtons	if true property buttons for this property will be shown.
- L217 _public prototype_ `virtual IDetailPropertyRow& EditCondition( TAttribute<bool> EditConditionValue, FOnBooleanValueChanged OnEditConditionValueChanged, ECustomEditConditionMode EditConditionMode = ECustomEditConditionMode::Override ) = 0;` — Sets an edit condition for this property.  If the edit condition fails, the property is not editable This will add a checkbox before the name of the property that users can click to toggle the edit condition Properties with built in edit conditions will override this automatically.  If the @param EditConditionValue			Attribute for the value of the edit condition (true indicates that the edit condition passes) @param OnEditConditionValueChanged	Delegate called when the edit condition value changes @param EditConditionMode				Should this custom edit condition override or merge with the existing edit condition of the property (if any)?
- L224 _public prototype_ `virtual IDetailPropertyRow& EditConditionHides( bool bEditConditionHidesValue ) = 0;` — Sets whether or not the edit condition for this property should affect its visibility.  If the edit condition fails, the property will be hidden outright. @param bEditConditionHidesValue		if true the property be shown/hidden based on the edit condition
- L231 _public prototype_ `virtual IDetailPropertyRow& IsEnabled( TAttribute<bool> InIsEnabled ) = 0;` — Sets whether or not this property is enabled @param InIsEnabled	Attribute for the enabled state of the property (true to enable the property)
- L239 _public prototype_ `virtual IDetailPropertyRow& ShouldAutoExpand(bool bForceExpansion = true) = 0;` — Sets whether or not this property should auto-expand @param bForceExpansion	true to force the property to be expanded
- L246 _public prototype_ `virtual IDetailPropertyRow& Visibility( TAttribute<EVisibility> Visibility ) = 0;` — Sets the visibility of this property @param Visibility	Attribute for the visibility of this property
- L253 _public prototype_ `virtual IDetailPropertyRow& OverrideResetToDefault(const FResetToDefaultOverride& ResetToDefault) = 0;` — Overrides the behavior of reset to default @param ResetToDefault	Contains the delegates needed to override the behavior of reset to default
- L260 _public prototype_ `virtual IDetailPropertyRow& DragDropHandler(TSharedPtr<IDetailDragDropHandler> InDragDropHandler) = 0;` — Sets a handler for this property row to be a source or target of drag-and-drop operations @param InDragDropHandler	Handler used when starting a drag or accepting a drop operation
- L267 _public prototype_ `virtual bool IsExpanded() const = 0;` — Returns the property row expansion state @return Will return true if the row is expanded, false if not
- L275 _public prototype_ `virtual void GetDefaultWidgets( TSharedPtr<SWidget>& OutNameWidget, TSharedPtr<SWidget>& OutValueWidget, bool bAddWidgetDecoration = false ) = 0;` — Returns the name and value widget of this property row.  You can use this widget to apply further customization to existing widgets (by using this  with CustomWidget) @param OutNameWidget		The default name widget @param OutValueWidget	The default value widget
- L284 _public prototype_ `virtual void GetDefaultWidgets( TSharedPtr<SWidget>& OutNameWidget, TSharedPtr<SWidget>& OutValueWidget, FDetailWidgetRow& Row, bool bAddWidgetDecoration = false ) = 0;` — Returns the name and value widget of this property row.  You can use this widget to apply further customization to existing widgets (by using this  with CustomWidget) @param OutNameWidget		The default name widget @param OutValueWidget	The default value widget @param OutCustomRow		The default widget row
- L292 _public prototype_ `virtual FDetailWidgetRow& CustomWidget( bool bShowChildren = false ) = 0;` — Overrides the property widget. Destroys any existing custom property widgets. @param bShowChildren	Whether or not to still show any children of this property @return a row for the property that custom widgets can be added to
- L299 _public prototype_ `virtual FDetailWidgetDecl* CustomNameWidget() = 0;` — Gives a non-owning pointer to name widget on existing custom property widget if it exists. @return	Pointer to name widget if custom property widget already exists, nullptr otherwise
- L306 _public prototype_ `virtual FDetailWidgetDecl* CustomValueWidget() = 0;` — Gives a non-owning pointer to value widget on existing custom property widget if it exists. @return	Pointer to value widget if custom property widget already exists, nullptr otherwise
- L313 _public prototype_ `virtual FDetailWidgetDecl* CustomResetToDefaultWidget() = 0;` — Gives a non-owning pointer to reset to default widget on existing custom property widget if it exists. @return	Pointer to reset to default widget if custom property widget already exists, nullptr otherwise

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsResetToDefaultVisible, TSharedPtr<IPropertyHandle> );`
- L15 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsResetToDefaultVisible, TSharedPtr<IPropertyHandle> );`
- L16 _delegate_ `DECLARE_DELEGATE_OneParam(FResetToDefaultHandler, TSharedPtr<IPropertyHandle> );`
- L16 _prototype_ `DECLARE_DELEGATE_OneParam(FResetToDefaultHandler, TSharedPtr<IPropertyHandle> );`

### `Source/Editor/PropertyEditor/Public/IDetailRootObjectCustomization.h` (Public)


#### struct `FDetailsObjectSet`  
`struct FDetailsObjectSet`  
_L10-17_
- desc: Defines a set of objects and a common base class between them for a root object customization
- L13 _public member_ `TArray<const UObject*> RootObjects;` — List of objects that represent the root in the details panel
- L16 _public member_ `const UClass* CommonBaseClass;` — The most common base class between all root objects

#### class `IDetailRootObjectCustomization`  
`class IDetailRootObjectCustomization : public TSharedFromThis<IDetailRootObjectCustomization>`  
_L22-112_
- inherits: `TSharedFromThis<IDetailRootObjectCustomization>`
- desc: Interface for any class that lays out details for a specific class
- L32 _public prototype_ `virtual ~IDetailRootObjectCustomization() = default;`
- L39 _public function_ `virtual TSharedPtr<SWidget> CustomizeObjectHeader(const FDetailsObjectSet& InRootObjectSet)` — Called when the details panel wants to display an object header widget for a given object @param	InRootObjects	The object set whose header is being customized
- L52 _public function_ `virtual TSharedPtr<SWidget> CustomizeObjectHeader(const FDetailsObjectSet& InRootObjectSet, const TSharedPtr<ITableRow>& InTableRow)` — Called when the details panel wants to display an object header widget for a given object @param	InRootObjects	The object set whose header is being customized @param	InTableRow		The ITableRow object (table views to talk to their rows) that will use the current IDetailRootObjectCustomization element.  This may be null if the customization is not being shown in a table view
- L62 _public function_ `virtual bool AreObjectsVisible(const FDetailsObjectSet& InRootObjectSet) const` — Whether or not the objects and all of its children should be visible in the details panel
- L74 _public function_ `virtual bool ShouldDisplayHeader(const FDetailsObjectSet& InRootObjectSet) const` — Whether or not the object should have a header displayed or just show the children directly @return true if the this customization should be displayed or false to just show the children directly
- L82 _public function_ `virtual TSharedPtr<SWidget> CustomizeObjectHeader(const UObject* InRootObject)` — `UE_DEPRECATED(4.25, "Please use the CustomizeObjectHeader version which takes in an array of root objects")`
- L88 _public function_ `virtual TSharedPtr<SWidget> CustomizeObjectHeader(const UObject* InRootObject, const TSharedPtr<ITableRow>& InTableRow)` — `UE_DEPRECATED(4.25, "Please use the CustomizeObjectHeader version which takes in an array of root objects")`
- L96 _public function_ `virtual bool IsObjectVisible(const UObject* InRootObject) const` — `UE_DEPRECATED(4.25, "Please use the AreObjectsVisible instead")`
- L99 _public function_ `virtual bool ShouldDisplayHeader(const UObject* InRootObject) const` — `UE_DEPRECATED(4.25, "Please use the ShouldDisplayHeader version which takes in an array of objects instead")`
- L107 _public function_ `virtual EExpansionArrowUsage GetExpansionArrowUsage() const` — Gets the setup for expansion arrows in this customization

#### enum `IDetailRootObjectCustomization::EExpansionArrowUsage`  
`enum EExpansionArrowUsage`  
_L25-30_
- L27 _public enumerator_ `Custom`
- L28 _public enumerator_ `Default`
- L29 _public enumerator_ `None`

### `Source/Editor/PropertyEditor/Public/IDetailTreeNode.h` (Public)


#### enum `EDetailNodeType`  
`enum class EDetailNodeType`  
_L13-23_
- L16 _public enumerator_ `Category` — Node represents a category
- L18 _public enumerator_ `Item` — Node represents an item such as a property or widget
- L20 _public enumerator_ `Advanced` — Node represents an advanced dropdown
- L22 _public enumerator_ `Object` — Represents a top level object node if a view supports multiple root objects

#### struct `FNodeWidgetLayoutData`  
`struct FNodeWidgetLayoutData`  
_L26-51_
- desc: Layout data for node's content widgets.
- L28 _public function_ `FNodeWidgetLayoutData()`
- L32 _public function_ `FNodeWidgetLayoutData(EHorizontalAlignment InHorizontalAlignment, EVerticalAlignment InVerticalAlignment, TOptional<float> InMinWidth, TOptional<float> InMaxWidth) : HorizontalAlignment(InHorizontalAlignment) , VerticalAlignment(InVerticalAlignment) , MinWidth(InMinWidth) , MaxWidth(InMaxWidth)`
- L41 _public member_ `EHorizontalAlignment HorizontalAlignment;` — The horizontal alignment requested by the widget.
- L44 _public member_ `EVerticalAlignment VerticalAlignment;` — The vertical alignment requested by the widget.
- L47 _public member_ `TOptional<float> MinWidth;` — An optional minimum width requested by the widget.
- L50 _public member_ `TOptional<float> MaxWidth;` — An optional maximum width requested by the widget.

#### struct `FNodeWidgetActionsCustomMenuData`  
`struct FNodeWidgetActionsCustomMenuData`  
_L54-75_
- desc: Defines a custom menu action which can be performed on a detail tree node.
- L56 _public function_ `FNodeWidgetActionsCustomMenuData(const FUIAction& InAction, const FText& InName, const FText& InTooltip, const FSlateIcon& InSlateIcon) : Action(InAction) , Name(InName) , Tooltip(InTooltip) , SlateIcon(InSlateIcon)`
- L65 _public member_ `const FUIAction Action;` — The action to be performed.
- L68 _public member_ `const FText Name;` — The name to display for the menu item.
- L71 _public member_ `const FText Tooltip;` — The tooltip to the display for the menu item.
- L74 _public member_ `const FSlateIcon SlateIcon;` — The icon to display for the menu item.

#### struct `FNodeWidgetActions`  
`struct FNodeWidgetActions`  
_L78-88_
- desc: Defines actions which can be performed on node widgets.
- L81 _public member_ `FUIAction CopyMenuAction;` — Action for copying data on this node
- L84 _public member_ `FUIAction PasteMenuAction;` — Action for pasting data on this node
- L87 _public member_ `TArray<FNodeWidgetActionsCustomMenuData> CustomMenuItems;` — Custom Actions on this node

#### struct `FNodeWidgets`  
`struct FNodeWidgets`  
_L91-116_
- desc: The widget contents of the node.  Any of these can be null depending on how the row was generated
- L94 _public member_ `TSharedPtr<SWidget> NameWidget;` — Widget for the name column
- L97 _public member_ `FNodeWidgetLayoutData NameWidgetLayoutData;` — Layout data for the widget in the name column.
- L100 _public member_ `TSharedPtr<SWidget> ValueWidget;` — Widget for the value column
- L103 _public member_ `FNodeWidgetLayoutData ValueWidgetLayoutData;` — Layout data for the widget in the value column.
- L106 _public member_ `TSharedPtr<SWidget> WholeRowWidget;` — Widget that spans the entire row.  Mutually exclusive with name/value widget
- L109 _public member_ `FNodeWidgetLayoutData WholeRowWidgetLayoutData;` — Layout data for the whole row widget.
- L112 _public member_ `TSharedPtr<SWidget> EditConditionWidget;` — Edit condition widget.
- L115 _public member_ `FNodeWidgetActions Actions;` — The actions which can be performed on the node widgets.

#### class `IDetailTreeNode`  
`class IDetailTreeNode`  
_L118-182_
- L121 _public prototype_ `virtual ~IDetailTreeNode() = default;`
- L126 _public prototype_ `virtual TSharedPtr<class IDetailsView> GetNodeDetailsViewSharedPtr() const = 0;` — @return Get the details view that this node is contained in.
- L129 _public function_ `class IDetailsView* GetNodeDetailsView() const` — `UE_DEPRECATED(5.5, "Use GetNodeDetailsViewSharedPtr() instead.")`
- L137 _public prototype_ `virtual EDetailNodeType GetNodeType() const = 0;` — @return The type of this node.  Should be used to determine any external styling to apply to the generated r ow
- L144 _public prototype_ `virtual TSharedPtr<IPropertyHandle> CreatePropertyHandle() const = 0;` — Creates a handle to the property on this row if the row represents a property. Only compatible with item node types that are properties @return The property handle for the row or null if the node doesn't have a property
- L151 _public prototype_ `virtual FNodeWidgets CreateNodeWidgets() const = 0;` — Creates the slate widgets for this row. @return the node widget structure with either name/value pair or a whole row widget
- L160 _public prototype_ `virtual void GetChildren(TArray<TSharedRef<IDetailTreeNode>>& OutChildren, const bool& bInIgnoreVisibility = false) = 0;` — Gets the children of this tree node Note: Customizations can determine the visibility of children.  This will only return visible children if bInIgnoreVisibility if false @param OutChildren			The generated children @param bInIgnoreVisibility	Whether to return children regardless of visibility
- L166 _public prototype_ `virtual FName GetNodeName() const = 0;` — Gets an identifier name for this node.  This is not a name formatted for display purposes, but can be useful for storing UI state like if this row is expanded.
- L171 _public prototype_ `virtual TSharedPtr<class IDetailPropertyRow> GetRow() const = 0;` — Get the property row that this node is represented by.
- L176 _public prototype_ `virtual void GetFilterStrings(TArray<FString>& OutFilterStrings) const = 0;` — Gets the filter strings for this node in the tree.
- L181 _public prototype_ `virtual bool GetInitiallyCollapsed() const = 0;` — Gets if this node should be initially collapsed by default.

### `Source/Editor/PropertyEditor/Public/IDetailsView.h` (Public)


#### class `IDetailsView`  
`class IDetailsView : public SCompoundWidget, public IScrollableWidget`  
_L35-353_
- inherits: `SCompoundWidget,IScrollableWidget`
- desc: Interface class for all detail views
- L39 _public prototype_ `virtual void SetOnObjectArrayChanged(FOnObjectArrayChanged OnObjectArrayChangedDelegate) = 0;` — Sets the callback for when the property view changes
- L42 _public prototype_ `virtual const TArray< TWeakObjectPtr<UObject> >& GetSelectedObjects() const = 0;` — List of all selected objects we are inspecting
- L45 _public prototype_ `virtual const TArray< TWeakObjectPtr<AActor> >& GetSelectedActors() const = 0;` — @return	Returns list of selected actors we are inspecting
- L48 _public prototype_ `virtual const struct FSelectedActorInfo& GetSelectedActorInfo() const = 0;` — @return Returns information about the selected set of actors
- L51 _public prototype_ `virtual bool HasClassDefaultObject() const = 0;` — @return Whether or not the details view is viewing a CDO
- L59 _public prototype_ `virtual void RegisterInstancedCustomPropertyLayout(UStruct* Class, FOnGetDetailCustomizationInstance DetailLayoutDelegate) = 0;` — Registers a custom detail layout delegate for a specific class in this instance of the details view only @param Class	The class the custom detail layout is for @param DetailLayoutDelegate	The delegate to call when querying for custom detail layouts for the classes properties
- L60 _public prototype_ `virtual void RegisterInstancedCustomPropertyTypeLayout(FName PropertyTypeName, FOnGetPropertyTypeCustomizationInstance PropertyTypeLayoutDelegate, TSharedPtr<IPropertyTypeIdentifier> Identifier = nullptr) = 0;`
- L67 _public prototype_ `virtual void UnregisterInstancedCustomPropertyLayout(UStruct* Class) = 0;` — Unregisters a custom detail layout delegate for a specific class in this instance of the details view only @param Class	The class with the custom detail layout delegate to remove
- L68 _public prototype_ `virtual void UnregisterInstancedCustomPropertyTypeLayout(FName PropertyTypeName, TSharedPtr<IPropertyTypeIdentifier> Identifier = nullptr) = 0;`
- L76 _public prototype_ `virtual void SetRootObjectCustomizationInstance(TSharedPtr<IDetailRootObjectCustomization> InRootObjectCustomization) = 0;` — Registers a customization that will be used only if this details panel contains multiple top level objects. I.E it was created with bAllowMultipleTopLevelObjects = true.	This interface will be used to customize the header for each top level object in the details panel @param InRootObjectCustomization	If null is passed in, the customization will be removed
- L85 _public prototype_ `virtual void SetObjects( const TArray<UObject*>& InObjects, bool bForceRefresh = false, bool bOverrideLock = false ) = 0;` — Sets the objects this details view is viewing @param InObjects		The list of objects to observe @param bForceRefresh	If true, doesn't check if new objects are being set @param bOverrideLock	If true, will set the objects even if the details view is locked
- L86 _public prototype_ `virtual void SetObjects( const TArray< TWeakObjectPtr< UObject > >& InObjects, bool bForceRefresh = false, bool bOverrideLock = false ) = 0;`
- L94 _public prototype_ `virtual void SetObject( UObject* InObject, bool bForceRefresh = false ) = 0;` — Sets a single object that details view is viewing @param InObject		The object to view @param bForceRefresh	If true, doesn't check if new objects are being set
- L97 _public prototype_ `virtual void RemoveInvalidObjects() = 0;` — Removes all invalid objects being observed by this details panel
- L100 _public prototype_ `virtual void SetObjectPackageOverrides(const TMap<TWeakObjectPtr<UObject>, TWeakObjectPtr<UPackage>>& InMapping) = 0;` — Set overrides that should be used when looking for packages that contain the given object (used when editing a transient copy of an object, but you need access to th real package)
- L105 _public prototype_ `virtual bool IsLocked() const = 0;` — Returns true if the details view is locked and cant have its observed objects changed
- L110 _public prototype_ `virtual bool IsUpdatable() const = 0;` — @return true if the details view can be updated from editor selection
- L115 _public prototype_ `virtual bool HasActiveSearch() const = 0;` — @return True if there is any filter of properties active in this details panel
- L120 _public prototype_ `virtual void ClearSearch() = 0;` — Clears any search terms in the current filter
- L125 _public prototype_ `virtual void SetSearchText(const FText& InSearch) = 0;` — Sets the active search for the current filter
- L131 _public prototype_ `virtual int32 GetNumVisibleTopLevelObjects() const = 0;` — @return The number of visible top level objects. This value is affected by filtering. Note: this value will always be 1 if this details panel was not created with bAllowMultipleTopLevelObjects=true
- L134 _public prototype_ `virtual FName GetIdentifier() const = 0;` — @return The identifier for this details view, or NAME_None is this view is anonymous
- L139 _public prototype_ `virtual void SetIsPropertyVisibleDelegate( FIsPropertyVisible InIsPropertyVisible ) = 0;` — Sets a delegate to call to determine if a specific property should be visible in this instance of the details view
- L140 _public prototype_ `virtual FIsPropertyVisible& GetIsPropertyVisibleDelegate() = 0;`
- L145 _public prototype_ `virtual void SetIsPropertyReadOnlyDelegate( FIsPropertyReadOnly InIsPropertyReadOnly ) = 0;` — Sets a delegate to call to determine if a specific property should be read-only in this instance of the details view
- L146 _public prototype_ `virtual FIsPropertyReadOnly& GetIsPropertyReadOnlyDelegate() = 0;`
- L151 _public prototype_ `virtual void SetIsCustomRowVisibleDelegate(FIsCustomRowVisible InIsCustomRowVisible) = 0;` — Sets a delegate to call to determine if a specific custom row should be visible in this instance of the details view
- L152 _public prototype_ `virtual FIsCustomRowVisible& GetIsCustomRowVisibleDelegate() = 0;`
- L157 _public prototype_ `virtual void SetIsCustomRowReadOnlyDelegate(FIsCustomRowReadOnly InIsCustomRowVisible) = 0;` — Sets a delegate to call to determine if a specific custom row should be visible in this instance of the details view
- L158 _public prototype_ `virtual FIsCustomRowReadOnly& GetIsCustomRowReadOnlyDelegate() = 0;`
- L163 _public prototype_ `virtual void SetGenericLayoutDetailsDelegate( FOnGetDetailCustomizationInstance OnGetGenericDetails ) = 0;` — Sets a delegate to call to layout generic details not specific to an object being viewed
- L164 _public prototype_ `virtual FOnGetDetailCustomizationInstance& GetGenericLayoutDetailsDelegate() = 0;`
- L169 _public prototype_ `virtual void SetIsPropertyEditingEnabledDelegate( FIsPropertyEditingEnabled IsPropertyEditingEnabled ) = 0;` — Sets a delegate to call to determine if the properties  editing is enabled
- L170 _public prototype_ `virtual FIsPropertyEditingEnabled& GetIsPropertyEditingEnabledDelegate() = 0;`
- L172 _public prototype_ `virtual void SetKeyframeHandler( TSharedPtr<IDetailKeyframeHandler> InKeyframeHandler ) = 0;`
- L173 _public prototype_ `virtual TSharedPtr<IDetailKeyframeHandler> GetKeyframeHandler() const = 0;`
- L175 _public prototype_ `virtual void SetExtensionHandler(TSharedPtr<IDetailPropertyExtensionHandler> InExtensionHandler) = 0;`
- L176 _public prototype_ `virtual TSharedPtr<IDetailPropertyExtensionHandler> GetExtensionHandler() const = 0;`
- L178 _public prototype_ `virtual void SetChildrenCustomizationHandler(TSharedPtr<IDetailPropertyChildrenCustomizationHandler> InExtensionHandler) = 0;`
- L179 _public prototype_ `virtual TSharedPtr<IDetailPropertyChildrenCustomizationHandler> GetChildrenCustomizationHandler() const = 0;`
- L184 _public prototype_ `virtual bool IsPropertyEditingEnabled() const = 0;` — @return true if property editing is enabled (based on the FIsPropertyEditingEnabled delegate)
- L191 _public prototype_ `virtual FOnFinishedChangingProperties& OnFinishedChangingProperties() const = 0;` — A delegate which is called after properties have been edited and PostEditChange has been called on all objects. This can be used to safely make changes to data that the details panel is observing instead of during PostEditChange (which is unsafe)
- L196 _public prototype_ `virtual void HideFilterArea(bool bIsVisible) = 0;` — Sets the visible state of the filter box/property grid area
- L201 _public prototype_ `virtual TArray< FPropertyPath > GetPropertiesInOrderDisplayed() const = 0;` — Returns a list of all the properties displayed (via full path), order in list corresponds to draw order:
- L208 _public prototype_ `virtual TArray<TPair<int32, FPropertyPath>> GetPropertyRowNumbers() const = 0;` — Returns the row number in the underlying TableView for each property being displayed. Note this won't include any properties that are apart of a collapsed section of the property tree because those properties don't have row numbers. If you need a list of all properties independent of expansion state, use GetPropertiesInOrderDisplayed
- L213 _public function_ `virtual FSlateRect GetPaintSpacePropertyBounds(const TSharedRef<FDetailTreeNode>& InDetailTreeNode, bool IncludeChildren = true) const` — Returns the boundary (in paint space) of a detail tree node if it's currently visible Otherwise return an invalid boundary
- L218 _public function_ `virtual FSlateRect GetTickSpacePropertyBounds(const TSharedRef<FDetailTreeNode>& InDetailTreeNode, bool IncludeChildren = true) const` — Returns the boundary (in tick space) of a detail tree node if it's currently visible Otherwise return an invalid boundary
- L223 _public function_ `virtual bool IsAncestorCollapsed(const TSharedRef<IDetailTreeNode>& Node) const` — Returns true if the provided detail tree node is part of a collapsed/hidden subsection of the details panel
- L228 _public prototype_ `virtual int32 CountRows() const = 0;` — returns the number of rows in the underlying TableView
- L233 _public prototype_ `virtual void HighlightProperty(const FPropertyPath& Property) = 0;` — Creates a box around the treenode corresponding to Property and scrolls the treenode into view
- L238 _public prototype_ `virtual void ScrollPropertyIntoView(const FPropertyPath& Property, bool bExpandProperty = false) = 0;` — Scrolls the treenode for the specific property into view
- L243 _public prototype_ `virtual void ShowAllAdvancedProperties() = 0;` — Forces all advanced property sections to be in expanded state:
- L251 _public prototype_ `virtual void SetRootExpansionStates(const bool bExpand, const bool bRecurse) = 0;` — Sets the expansion state all root nodes and optionally all of their children @param bExpand			The new expansion state @param bRecurse			Whether or not to apply the expansion change to any children
- L257 _public prototype_ `virtual void RefreshRootObjectVisibility() = 0;` — Refreshes the visibility of root objects in this details view. Note: This method has no effect if the details panel is viewing a single top-level object set only
- L261 _public prototype_ `virtual void SetOnDisplayedPropertiesChanged(FOnDisplayedPropertiesChanged InOnDisplayedPropertiesChangedDelegate) = 0;` — Assigns delegate called when view is filtered, useful for updating external control logic:
- L262 _public prototype_ `virtual FOnDisplayedPropertiesChanged& GetOnDisplayedPropertiesChanged() = 0;`
- L267 _public prototype_ `virtual void SetDisableCustomDetailLayouts(bool bInDisableCustomDetailLayouts) = 0;` — Disables or enables customization of the details view:
- L272 _public prototype_ `virtual void UpdatePropertyAllowList(const TSet<FPropertyPath>& InAllowedProperties) = 0;` — Sets the set of properties that are considered differing, used when filtering out identical properties
- L275 _public prototype_ `virtual TSharedPtr<SWidget> GetNameAreaWidget() = 0;` — Returns the name area widget used to display object naming functionality so it can be placed in a custom location.  Note FDetailsViewArgs.bCustomNameAreaLocation must be true
- L278 _public prototype_ `virtual void SetNameAreaCustomContent(TSharedRef<SWidget>& InCustomContent) = 0;` — Optionally add custom tools into the NameArea
- L281 _public prototype_ `virtual TSharedPtr<SWidget> GetFilterAreaWidget() = 0;` — Returns the search area widget used to display search and view options so it can be placed in a custom location.  Note FDetailsViewArgs.bCustomFilterAreaLocation must be true
- L284 _public prototype_ `virtual TSharedPtr<FUICommandList> GetHostCommandList() const = 0;` — Returns the command list of the hosting toolkit (can be nullptr if the widget that contains the details panel didn't route a command list in)
- L287 _public prototype_ `virtual TSharedPtr<FTabManager> GetHostTabManager() const = 0;` — Returns the tab manager of the hosting toolkit (can be nullptr if the details panel is not hosted within a tab)
- L290 _public prototype_ `virtual void SetHostTabManager(TSharedPtr<FTabManager> InTabManager) = 0;` — Sets the tab manager of the hosting toolkit (can be nullptr if the details panel is not hosted within a tab)
- L293 _public prototype_ `virtual void RequestForceRefresh() = 0;` — Request the details view to be refreshed (new widgets generated) with the current set of objects on the next Tick
- L296 _public prototype_ `virtual void ForceRefresh() = 0;` — Causes the details view to be refreshed (new widgets generated) with the current set of objects
- L299 _public function_ `virtual void InvalidateCachedState()` — Invalidates any cached state without necessarily doing a complete rebuild.
- L305 _public prototype_ `virtual void SetObjectFilter(TSharedPtr<FDetailsViewObjectFilter> InFilter) = 0;` — Sets an optional object filter to use for more complex handling of what a details panel is viewing.
- L308 _public prototype_ `virtual void SetClassViewerFilters(const TArray<TSharedRef<IClassViewerFilter>>& InFilters) = 0;` — Sets the custom filter(s) to be used when selecting values for class properties in this view.
- L311 _public prototype_ `virtual void SetCustomFilterDelegate(FSimpleDelegate InDelegate) = 0;` — Allows other systems to add a custom filter in the details panel
- L313 _public prototype_ `virtual void SetCustomFilterLabel(FText InText) = 0;`
- L317 _public prototype_ `virtual void SetCustomValidatePropertyNodesFunction(FOnValidateDetailsViewPropertyNodes InCustomValidatePropertyNodesFunction) = 0;` — Use this function to set a callback for SDetailsView that will skip the EnsureDataIsValid call in Tick. This is useful if your implementation doesn't need to validate nodes every tick or needs to perform some other form of validation.
- L320 _public prototype_ `virtual float GetRightColumnMinWidth() const = 0;` — Gets the minimum width of the detail panel's right column.
- L322 _public prototype_ `virtual void SetRightColumnMinWidth(float InMinWidth) = 0;` — Sets the minimum width of the detail panel's right column.
- L327 _public prototype_ `virtual void UpdateStyleKey() = 0;` — Updates @code FDetailsViewStyleKey& StyleKey @endcode for the current IDetailsView state
- L332 _public prototype_ `virtual const FDetailsViewStyleKey& GetStyleKey() = 0;` — Gets the @code FDetailsViewStyleKey& @endcode which provides a Key to the current style for a Details View
- L337 _public prototype_ `virtual bool IsDefaultStyle() const = 0;` — Returns a bool indicating whether the given @code FDetailsViewStyleKey @endcode is the default Details View Style
- L341 _public prototype_ `virtual FVector2D GetScrollDistance() = 0;` — IScrollableWidget interface
- L342 _public prototype_ `virtual FVector2D GetScrollDistanceRemaining() = 0;`
- L343 _public prototype_ `virtual TSharedRef<SWidget> GetScrollWidget() = 0;`
- L351 _public prototype_ `virtual bool ResetToDefaultSection() = 0;` — Resets the selected sections to the default 'All' section. @return whether the operation succeeded.

#### Free symbols / members of external scopes

- L28 _typedef_ `typedef TArray<TSharedPtr<FComplexPropertyNode>> FRootPropertyNodeList;`
- L30 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnValidateDetailsViewPropertyNodes, const FRootPropertyNodeList&) class IDetailsView : public SCompoundWidget, public IScrollableWidget { public: virtual void SetOnObjectArrayChanged(FOnObjectArrayChanged OnObjectArrayChangedDelegate) = 0; virtual const TArray< TWeakObjectPtr<UObject> >& GetSelectedObjects() const = 0; virtual const TArray< TWeakObjectPtr<AActor> >& GetSelectedActors() const = 0; virtual const struct FSelectedActorInfo& GetSelectedActorInfo() const = 0; virtual bool HasClassDefaultObject() const = 0; virtual void RegisterInstancedCustomPropertyLayout(UStruct* Class, FOnGetDetailCustomizationInstance DetailLayoutDelegate) = 0; virtual void RegisterInstancedCustomPropertyTypeLayout(FName PropertyTypeName, FOnGetPropertyTypeCustomizationInstance PropertyTypeLayoutDelegate, TSharedPtr<IPropertyTypeIdentifier> Identifier = nullptr) = 0; virtual void UnregisterInstancedCustomPropertyLayout(UStruct* Class) = 0; virtual void UnregisterInstancedCustomPropertyTypeLayout(FName PropertyTypeName, TSharedPtr<IPropertyTypeIdentifier> Identifier = nullptr) = 0;`

### `Source/Editor/PropertyEditor/Public/IPropertyChangeListener.h` (Public)


#### struct `FPropertyListenerSettings`  
`struct FPropertyListenerSettings`  
_L7-20_
- L10 _public member_ `uint64 RequiredPropertyFlags;` — Flags a property must have to be observed for changes
- L13 _public member_ `uint64 DisallowedPropertyFlags;` — Flags that a property must not have to be observed for changes
- L16 _public member_ `bool bIgnoreObjectProperties;` — Whether or not to ignore object properties
- L19 _public member_ `bool bIgnoreArrayProperties;` — Whether or not to ignore arrays (not the array elements but the array property itself

#### class `IPropertyChangeListener`  
`class IPropertyChangeListener`  
_L25-56_
- desc: Interface to a property change listener that broadcasts notifications when a property changes
- L29 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams( FOnPropertyChanged, const TArray<UObject*>&, const class IPropertyHandle& );` — Delegate called when a property changes
- L37 _public prototype_ `virtual void SetObject( UObject& Object, const FPropertyListenerSettings& InPropertyListenerSettings ) = 0;` — Sets the object that should be listened to for changes @param Object						The object to listen to @param InPropertyListenerSettings	Settings for which properties should be listened to
- L45 _public prototype_ `virtual bool ScanForChanges( bool bRecacheNewValues = true ) = 0;` — Scans properties for changes @param bRecacheNewValues	If true recaches new values found for the next scan @return true if any changes were found
- L50 _public prototype_ `virtual void TriggerAllPropertiesChangedDelegate() = 0;` — Triggers all property changed delegates to fire
- L55 _public prototype_ `virtual FOnPropertyChanged& GetOnPropertyChangedDelegate() = 0;` — @return A delegate to call when a property changes

#### Free symbols / members of external scopes

- L29 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams( FOnPropertyChanged, const TArray<UObject*>&, const class IPropertyHandle& );` — Delegate called when a property changes

### `Source/Editor/PropertyEditor/Public/IPropertyDetailsUtilities.h` (Public)
_(no declarations extracted)_

### `Source/Editor/PropertyEditor/Public/IPropertyRowGenerator.h` (Public)


#### struct `FPropertyRowGeneratorArgs`  
`struct FPropertyRowGeneratorArgs`  
_L16-40_
- L18 _public function_ `FPropertyRowGeneratorArgs() : NotifyHook(nullptr) , DefaultsOnlyVisibility(EEditDefaultsOnlyNodeVisibility::Show) , bAllowMultipleTopLevelObjects(false) , bShouldShowHiddenProperties(false) , bAllowEditingClassDefaultObjects(true)`
- L27 _public member_ `FNotifyHook* NotifyHook;` — Notify hook to call when properties are changed
- L30 _public member_ `EEditDefaultsOnlyNodeVisibility DefaultsOnlyVisibility;` — Controls how CPF_DisableEditOnInstance nodes will be treated
- L33 _public member_ `bool bAllowMultipleTopLevelObjects;` — Whether the root node should contain multiple objects.
- L36 _public member_ `bool bShouldShowHiddenProperties;` — Whether the generator should generate hidden properties.
- L39 _public member_ `bool bAllowEditingClassDefaultObjects;` — Whether the generator should allow editing CDOs.

#### class `IPropertyRowGenerator`  
`class IPropertyRowGenerator`  
_L42-127_
- L45 _public prototype_ `virtual ~IPropertyRowGenerator() = default;`
- L52 _public prototype_ `virtual void SetObjects(const TArray<UObject*>& InObjects) = 0;` — Sets the objects that should be used to generate rows @param InObjects	The list of objects to generate rows from.  Note unless FPropertyRowGeneratorArgs.bAllowMultipleTopLevelObjects is set to true, the properties used will be the common base class of all passed in objects
- L59 _public prototype_ `virtual void SetStructure(const TSharedPtr<FStructOnScope>& InStruct) = 0;` — Sets the structure that should be used to generate rows @param InStruct The structure used to generate rows from.
- L60 _public prototype_ `virtual void SetStructure(const TSharedPtr<IStructureDataProvider>& InStruct) = 0;`
- L66 _public prototype_ `virtual const TArray<TWeakObjectPtr<UObject>>& GetSelectedObjects() const = 0;` — Get the list of objects that were used to generate detail tree nodes @return A list of weak pointers to this generator's objects.
- L71 _public prototype_ `DECLARE_EVENT(IPropertyRowGenerator, FOnRowsRefreshed);` — Delegate called when rows have been refreshed.  This delegate should always be bound to something because once this is called, none of the rows previously generated can be trusted
- L72 _public prototype_ `virtual FOnRowsRefreshed& OnRowsRefreshed() = 0;`
- L77 _public prototype_ `virtual const TArray<TSharedRef<IDetailTreeNode>>& GetRootTreeNodes() const = 0;` — @return The list of root tree nodes that have been generated.  Note: There will only be one root node unless  FPropertyRowGeneratorArgs.bAllowMultipleTopLevelObjects was set to true when the generator was created
- L84 _public prototype_ `virtual TSharedPtr<IDetailTreeNode> FindTreeNode(TSharedPtr<IPropertyHandle> PropertyHandle) const = 0;` — Finds a tree node by property handle. @return The found tree node or null if the node cannot be found
- L91 _public prototype_ `virtual TArray<TSharedPtr<IDetailTreeNode>> FindTreeNodes(const TArray<TSharedPtr<IPropertyHandle>>& PropertyHandles) const = 0;` — Finds tree nodes by property handles. @return The found tree nodes (in the same order, a pointer will be null if the node cannot be found)
- L99 _public prototype_ `virtual void RegisterInstancedCustomPropertyLayout(UStruct* Class, FOnGetDetailCustomizationInstance DetailLayoutDelegate) = 0;` — Registers a custom detail layout delegate for a specific class in this instance of the generator only @param Class	The class the custom detail layout is for @param DetailLayoutDelegate	The delegate to call when querying for custom detail layouts for the classes properties
- L100 _public prototype_ `virtual void RegisterInstancedCustomPropertyTypeLayout(FName PropertyTypeName, FOnGetPropertyTypeCustomizationInstance PropertyTypeLayoutDelegate, TSharedPtr<IPropertyTypeIdentifier> Identifier = nullptr) = 0;`
- L107 _public prototype_ `virtual void UnregisterInstancedCustomPropertyLayout(UStruct* Class) = 0;` — Unregisters a custom detail layout delegate for a specific class in this instance of the generator only @param Class	The class with the custom detail layout delegate to remove
- L108 _public prototype_ `virtual void UnregisterInstancedCustomPropertyTypeLayout(FName PropertyTypeName, TSharedPtr<IPropertyTypeIdentifier> Identifier = nullptr) = 0;`
- L110 _public prototype_ `virtual FOnFinishedChangingProperties& OnFinishedChangingProperties() = 0;`
- L111 _public prototype_ `virtual FOnNotifyStartedChangingProperties& OnNotifyStartedChangingProperties() = 0;`
- L115 _public prototype_ `virtual void SetCustomValidatePropertyNodesFunction(FOnValidatePropertyRowGeneratorNodes InCustomValidatePropertyNodesFunction) = 0;` — Use this function to set a callback on FPropertyRowGenerator that will override the ValidatePropertyNodes function. This is useful if your implementation doesn't need to validate nodes every tick or needs to perform some other form of validation.
- L120 _public prototype_ `virtual void SetPropertyGenerationAllowListPaths(const TSet<FString>& InPropertyGenerationAllowListPaths) = 0;` — Use this function to set property paths to generate FPropertyNodes. This improves the performance for cases where UPropertyView is only showing a few properties of the object by not generating all other FPropertyNodes An example of a nested property path: RootPropertyName[0]->NestedPropertyName[0]->PropertyName
- L123 _public prototype_ `virtual void InvalidateCachedState() = 0;` — Invalidates internal cached state.  Common use of this API is to synchronize the viewed object with changes made by external code.
- L126 _public prototype_ `virtual void FilterNodes(const TArray<FString>& InFilterStrings) = 0;` — Apply filters to generated row tree nodes

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnValidatePropertyRowGeneratorNodes, const FRootPropertyNodeList&) struct FPropertyRowGeneratorArgs { FPropertyRowGeneratorArgs() : NotifyHook(nullptr) , DefaultsOnlyVisibility(EEditDefaultsOnlyNodeVisibility::Show) , bAllowMultipleTopLevelObjects(false) , bShouldShowHiddenProperties(false) , bAllowEditingClassDefaultObjects(true) {} FNotifyHook* NotifyHook; EEditDefaultsOnlyNodeVisibility DefaultsOnlyVisibility; bool bAllowMultipleTopLevelObjects; bool bShouldShowHiddenProperties; bool bAllowEditingClassDefaultObjects; };`
- L71 _delegate_ `DECLARE_EVENT(IPropertyRowGenerator, FOnRowsRefreshed);` — Delegate called when rows have been refreshed.  This delegate should always be bound to something because once this is called, none of the rows previously generated can be trusted

### `Source/Editor/PropertyEditor/Public/IPropertyTable.h` (Public)


#### enum `EPropertyTableSelectionUnit::Type`  
`enum Type`  
_L19-24_
- L21 _public enumerator_ `None = 0x00`
- L22 _public enumerator_ `Row = 0x01`
- L23 _public enumerator_ `Cell = 0x03`

#### enum `EPropertyTableOrientation::Type`  
`enum Type`  
_L30-34_
- L32 _public enumerator_ `AlignPropertiesInColumns` — Items and all their properties are in rows
- L33 _public enumerator_ `AlignPropertiesInRows` — Items and all their properties are in columns

#### class `IDataSource`  
`class IDataSource`  
_L37-45_
- L41 _public prototype_ `virtual TWeakObjectPtr< UObject > AsUObject() const = 0;`
- L42 _public prototype_ `virtual TSharedPtr< class FPropertyPath > AsPropertyPath() const = 0;`
- L44 _public prototype_ `virtual bool IsValid() const = 0;`

#### class `IPropertyTable`  
`class IPropertyTable : public IPropertyTableUtilities`  
_L47-160_
- inherits: `IPropertyTableUtilities`
- L51 _public prototype_ `virtual void Tick() = 0;`
- L53 _public prototype_ `virtual void ForceRefresh() = 0;`
- L54 _public prototype_ `virtual void RequestRefresh() = 0;`
- L56 _public prototype_ `virtual void AddColumn( const TWeakObjectPtr< class UObject >& Object ) = 0;`
- L57 _public prototype_ `virtual void AddColumn( const TWeakFieldPtr< class FProperty >& Property ) = 0;`
- L58 _public prototype_ `virtual void AddColumn( const TSharedRef< class FPropertyPath >& PropertyPath ) = 0;`
- L59 _public prototype_ `virtual void AddColumn( const TSharedRef< class IPropertyTableColumn >& Column ) = 0;`
- L60 _public prototype_ `virtual void RemoveColumn( const TSharedRef< class IPropertyTableColumn >& Column ) = 0;`
- L62 _public prototype_ `virtual void AddRow( const TWeakObjectPtr< UObject >& Object ) = 0;`
- L63 _public prototype_ `virtual void AddRow( const TWeakFieldPtr< FProperty >& Property ) = 0;`
- L64 _public prototype_ `virtual void AddRow( const TSharedRef< FPropertyPath >& PropertyPath ) = 0;`
- L65 _public prototype_ `virtual void AddRow( const TSharedRef< class IPropertyTableRow >& Row ) = 0;`
- L66 _public prototype_ `virtual void RemoveRow( const TSharedRef< class IPropertyTableRow >& Row ) = 0;`
- L68 _public prototype_ `virtual const EPropertyTableOrientation::Type GetOrientation() const = 0;`
- L69 _public prototype_ `virtual void SetOrientation( EPropertyTableOrientation::Type InOrientation ) = 0;`
- L71 _public prototype_ `virtual bool GetIsUserAllowedToChangeRoot() = 0;`
- L72 _public prototype_ `virtual void SetIsUserAllowedToChangeRoot( bool InAllowUserToChangeRoot ) = 0;`
- L74 _public prototype_ `virtual void SetRootPath( const TSharedPtr< FPropertyPath >& Path ) = 0;`
- L75 _public prototype_ `virtual TSharedRef< FPropertyPath> GetRootPath() const = 0;`
- L76 _public prototype_ `virtual TArray< struct FPropertyInfo > GetPossibleExtensionsForPath( const TSharedRef< FPropertyPath >& Path ) const = 0;`
- L78 _public prototype_ `virtual void GetSelectedTableObjects( TArray< TWeakObjectPtr< UObject > >& OutSelectedObjects) const = 0;`
- L80 _public prototype_ `virtual void SetObjects( const TArray< TWeakObjectPtr< UObject > >& Objects ) = 0;`
- L81 _public prototype_ `virtual void SetObjects( const TArray< UObject* >& Objects ) = 0;`
- L83 _public prototype_ `virtual TSharedRef< class FObjectPropertyNode > GetObjectPropertyNode( const TSharedRef< class IPropertyTableColumn >& Column, const TSharedRef< class IPropertyTableRow >& Row ) = 0;`
- L84 _public prototype_ `virtual TSharedRef< class FObjectPropertyNode > GetObjectPropertyNode( const TWeakObjectPtr< UObject >& Object ) = 0;`
- L86 _public prototype_ `virtual bool GetShowRowHeader() const = 0;`
- L87 _public prototype_ `virtual void SetShowRowHeader( const bool ShowRowHeader ) = 0;`
- L89 _public prototype_ `virtual bool GetShowObjectName() const = 0;`
- L90 _public prototype_ `virtual void SetShowObjectName( const bool ShowObjectName ) = 0;`
- L92 _public prototype_ `virtual const TArray< TSharedRef< class IPropertyTableColumn > >& GetColumns() = 0;`
- L94 _public prototype_ `virtual void SelectCellRange( const TSharedRef< class IPropertyTableCell >& StartingCell, const TSharedRef< class IPropertyTableCell >& EndingCell ) = 0;`
- L96 _public prototype_ `virtual TArray< TSharedRef< class IPropertyTableRow > >& GetRows() = 0;`
- L97 _public prototype_ `virtual const TSet< TSharedRef< class IPropertyTableRow > >& GetSelectedRows() = 0;`
- L98 _public prototype_ `virtual void SetSelectedRows( const TSet< TSharedRef< class IPropertyTableRow > >& InSelectedRows ) = 0;`
- L100 _public prototype_ `virtual const TSet< TSharedRef< class IPropertyTableCell > >& GetSelectedCells() = 0;`
- L101 _public prototype_ `virtual void SetSelectedCells( const TSet< TSharedRef< class IPropertyTableCell > >& InSelectedCells ) = 0;`
- L103 _public prototype_ `virtual float GetItemHeight() const = 0;`
- L104 _public prototype_ `virtual void SetItemHeight( float NewItemHeight ) = 0;`
- L106 _public prototype_ `virtual TSharedPtr< class IPropertyTableCell > GetLastClickedCell() const = 0;`
- L107 _public prototype_ `virtual void SetLastClickedCell( const TSharedPtr< class IPropertyTableCell >& Cell ) = 0;`
- L109 _public prototype_ `virtual TSharedPtr< class IPropertyTableCell > GetCurrentCell() const = 0;`
- L110 _public prototype_ `virtual void SetCurrentCell( const TSharedPtr< class IPropertyTableCell >& Cell ) = 0;`
- L112 _public prototype_ `virtual TSharedPtr< class IPropertyTableColumn > GetCurrentColumn() const = 0;`
- L113 _public prototype_ `virtual void SetCurrentColumn( const TSharedPtr< class IPropertyTableColumn >& Column ) = 0;`
- L115 _public prototype_ `virtual TSharedPtr< class IPropertyTableRow > GetCurrentRow() const = 0;`
- L116 _public prototype_ `virtual void SetCurrentRow( const TSharedPtr< class IPropertyTableRow >& Row ) = 0;`
- L118 _public prototype_ `virtual TSharedPtr< class IPropertyTableCell > GetFirstCellInSelection() = 0;`
- L119 _public prototype_ `virtual TSharedPtr< class IPropertyTableCell > GetLastCellInSelection() = 0;`
- L121 _public prototype_ `virtual TSharedPtr< class IPropertyTableCell > GetNextCellInRow( const TSharedRef< class IPropertyTableCell >& Cell ) = 0;`
- L122 _public prototype_ `virtual TSharedPtr< class IPropertyTableCell > GetPreviousCellInRow( const TSharedRef< class IPropertyTableCell >& Cell ) = 0;`
- L124 _public prototype_ `virtual TSharedPtr< class IPropertyTableCell > GetNextCellInColumn( const TSharedRef< class IPropertyTableCell >& Cell ) = 0;`
- L125 _public prototype_ `virtual TSharedPtr< class IPropertyTableCell > GetPreviousCellInColumn( const TSharedRef< class IPropertyTableCell >& Cell ) = 0;`
- L127 _public prototype_ `virtual TSharedPtr< class IPropertyTableCell > GetFirstCellInRow( const TSharedRef< class IPropertyTableRow >& Row ) = 0;`
- L128 _public prototype_ `virtual TSharedPtr< class IPropertyTableCell > GetLastCellInRow( const TSharedRef< class IPropertyTableRow >& Row ) = 0;`
- L130 _public prototype_ `virtual TSharedPtr< class IPropertyTableCell > GetFirstCellInColumn( const TSharedRef< class IPropertyTableColumn >& Column ) = 0;`
- L131 _public prototype_ `virtual TSharedPtr< class IPropertyTableCell > GetLastCellInColumn( const TSharedRef< class IPropertyTableColumn >& Column ) = 0;`
- L133 _public prototype_ `virtual TSharedPtr< class IPropertyTableCell > GetFirstCellInTable() = 0;`
- L134 _public prototype_ `virtual TSharedPtr< class IPropertyTableCell > GetLastCellInTable() = 0;`
- L136 _public prototype_ `virtual EPropertyTableSelectionUnit::Type GetSelectionUnit() const = 0;`
- L137 _public prototype_ `virtual void SetSelectionUnit( const EPropertyTableSelectionUnit::Type Unit ) = 0;`
- L139 _public prototype_ `virtual ESelectionMode::Type GetSelectionMode() const = 0;`
- L140 _public prototype_ `virtual void SetSelectionMode( const ESelectionMode::Type Mode ) = 0;`
- L142 _public prototype_ `virtual EColumnSortPriority::Type GetColumnSortPriority(const TSharedRef< class IPropertyTableColumn > Column) const = 0;`
- L143 _public prototype_ `virtual EColumnSortMode::Type GetColumnSortMode( const TSharedRef< class IPropertyTableColumn > Column ) const = 0;`
- L144 _public prototype_ `virtual void SortByColumnWithId( const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type SortMode ) = 0;`
- L145 _public prototype_ `virtual void SortByColumn( const TSharedRef< class IPropertyTableColumn >& Column, EColumnSortMode::Type SortMode, const EColumnSortPriority::Type SortPriority) = 0;`
- L147 _public prototype_ `virtual void PasteTextAtCell( const FString& Text, const TSharedRef< class IPropertyTableCell >& Cell ) = 0;`
- L149 _public prototype_ `DECLARE_EVENT( IPropertyTable, FSelectionChanged );`
- L150 _public prototype_ `virtual FSelectionChanged* OnSelectionChanged() = 0;`
- L152 _public prototype_ `DECLARE_EVENT( IPropertyTable, FColumnsChanged );`
- L153 _public prototype_ `virtual FColumnsChanged* OnColumnsChanged() = 0;`
- L155 _public prototype_ `DECLARE_EVENT( IPropertyTable, FRowsChanged );`
- L156 _public prototype_ `virtual FRowsChanged* OnRowsChanged() = 0;`
- L158 _public prototype_ `DECLARE_EVENT( IPropertyTable, FRootPathChanged );`
- L159 _public prototype_ `virtual FRootPathChanged* OnRootPathChanged() = 0;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace EPropertyTableSelectionUnit`
- L28 _namespace_ `namespace EPropertyTableOrientation`
- L149 _delegate_ `DECLARE_EVENT( IPropertyTable, FSelectionChanged );`
- L152 _delegate_ `DECLARE_EVENT( IPropertyTable, FColumnsChanged );`
- L155 _delegate_ `DECLARE_EVENT( IPropertyTable, FRowsChanged );`
- L158 _delegate_ `DECLARE_EVENT( IPropertyTable, FRootPathChanged );`

### `Source/Editor/PropertyEditor/Public/IPropertyTableCell.h` (Public)


#### class `IPropertyTableCell`  
`class IPropertyTableCell`  
_L7-39_
- L10 _public prototype_ `virtual ~IPropertyTableCell() = default;`
- L12 _public prototype_ `virtual void Refresh() = 0;`
- L14 _public prototype_ `virtual bool IsReadOnly() const = 0;`
- L15 _public prototype_ `virtual bool IsBound() const = 0;`
- L16 _public prototype_ `virtual bool InEditMode() const = 0;`
- L17 _public prototype_ `virtual bool IsValid() const = 0;`
- L18 _public function_ `virtual bool PassesPermissionList() const`
- L20 _public prototype_ `virtual FString GetValueAsString() const = 0;`
- L21 _public prototype_ `virtual FText GetValueAsText() const = 0;`
- L22 _public prototype_ `virtual void SetValueFromString( const FString& InString ) = 0;`
- L24 _public prototype_ `virtual TWeakObjectPtr< UObject > GetObject() const = 0;`
- L25 _public prototype_ `virtual TSharedPtr< class FPropertyNode > GetNode() const = 0;`
- L26 _public prototype_ `virtual TSharedRef< class IPropertyTableColumn > GetColumn() const = 0;`
- L27 _public prototype_ `virtual TSharedRef< class IPropertyTableRow > GetRow() const = 0;`
- L28 _public prototype_ `virtual TSharedRef< class IPropertyTable > GetTable() const = 0;`
- L29 _public prototype_ `virtual TSharedPtr< class IPropertyHandle > GetPropertyHandle() const = 0;`
- L31 _public prototype_ `virtual void EnterEditMode() = 0;`
- L32 _public prototype_ `virtual void ExitEditMode() = 0;`
- L34 _public prototype_ `DECLARE_EVENT( IPropertyTableCell, FEnteredEditModeEvent );`
- L35 _public prototype_ `virtual FEnteredEditModeEvent& OnEnteredEditMode() = 0;`
- L37 _public prototype_ `DECLARE_EVENT( IPropertyTableCell, FExitedEditModeEvent );`
- L38 _public prototype_ `virtual FExitedEditModeEvent& OnExitedEditMode() = 0;`

#### Free symbols / members of external scopes

- L34 _delegate_ `DECLARE_EVENT( IPropertyTableCell, FEnteredEditModeEvent );`
- L37 _delegate_ `DECLARE_EVENT( IPropertyTableCell, FExitedEditModeEvent );`

### `Source/Editor/PropertyEditor/Public/IPropertyTableCellPresenter.h` (Public)


#### class `IPropertyTableCellPresenter`  
`class IPropertyTableCellPresenter`  
_L7-29_
- L10 _public prototype_ `virtual ~IPropertyTableCellPresenter() = default;`
- L12 _public prototype_ `virtual TSharedRef< class SWidget > ConstructDisplayWidget() = 0;`
- L14 _public function_ `virtual const FSlateBrush* GetEditModeCellBrush()`
- L16 _public prototype_ `virtual bool RequiresDropDown() = 0;`
- L18 _public prototype_ `virtual TSharedRef< class SWidget > ConstructEditModeCellWidget() = 0;`
- L20 _public prototype_ `virtual TSharedRef< class SWidget > ConstructEditModeDropDownWidget() = 0;`
- L22 _public prototype_ `virtual TSharedRef< class SWidget > WidgetToFocusOnEdit() = 0;`
- L24 _public prototype_ `virtual FString GetValueAsString() = 0;`
- L26 _public prototype_ `virtual FText GetValueAsText() = 0;`
- L28 _public prototype_ `virtual bool HasReadOnlyEditMode() = 0;`

### `Source/Editor/PropertyEditor/Public/IPropertyTableColumn.h` (Public)


#### enum `EPropertyTableColumnSizeMode::Type`  
`enum Type`  
_L9-13_
- L11 _public enumerator_ `Fill`
- L12 _public enumerator_ `Fixed`

#### class `IPropertyTableColumn`  
`class IPropertyTableColumn`  
_L16-61_
- L20 _public prototype_ `virtual FName GetId() const = 0;`
- L22 _public prototype_ `virtual FText GetDisplayName() const = 0;`
- L24 _public prototype_ `virtual TSharedRef< class IDataSource > GetDataSource() const = 0;`
- L26 _public prototype_ `virtual TSharedRef< class FPropertyPath > GetPartialPath() const = 0;`
- L28 _public prototype_ `virtual TSharedRef< class IPropertyTableCell > GetCell( const TSharedRef< class IPropertyTableRow >& Row ) = 0;`
- L30 _public prototype_ `virtual void RemoveCellsForRow( const TSharedRef< class IPropertyTableRow >& Row ) = 0;`
- L32 _public prototype_ `virtual TSharedRef< class IPropertyTable > GetTable() const = 0;`
- L34 _public prototype_ `virtual bool CanSelectCells() const = 0;`
- L36 _public prototype_ `virtual EPropertyTableColumnSizeMode::Type GetSizeMode() const = 0;`
- L38 _public prototype_ `virtual void SetSizeMode(EPropertyTableColumnSizeMode::Type InSizeMode) = 0;`
- L40 _public prototype_ `virtual float GetWidth() const = 0;`
- L41 _public prototype_ `virtual void SetWidth( float InWidth ) = 0;`
- L43 _public prototype_ `virtual bool IsHidden() const = 0;`
- L44 _public prototype_ `virtual void SetHidden( bool IsHidden ) = 0;`
- L46 _public prototype_ `virtual bool IsFrozen() const = 0;`
- L47 _public prototype_ `virtual void SetFrozen( bool IsFrozen ) = 0;`
- L49 _public prototype_ `virtual bool CanSortBy() const = 0;`
- L50 _public prototype_ `virtual void Sort( TArray< TSharedRef< class IPropertyTableRow > >& Rows, const EColumnSortMode::Type PrimarySortMode, const TSharedPtr<IPropertyTableColumn>& SecondarySortColumn, const EColumnSortMode::Type SecondarySortMode ) = 0;`
- L52 _public prototype_ `virtual TSharedPtr<struct FCompareRowByColumnBase> GetPropertySorter(const FProperty* Property, EColumnSortMode::Type SortMode) = 0;`
- L57 _public prototype_ `virtual void Tick() = 0;` — Tick the property column each frame
- L59 _public prototype_ `DECLARE_EVENT_OneParam( IPropertyTableColumn, FFrozenStateChanged, const TSharedRef< IPropertyTableColumn >& );`
- L60 _public prototype_ `virtual FFrozenStateChanged* OnFrozenStateChanged() = 0;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace EPropertyTableColumnSizeMode`
- L59 _delegate_ `DECLARE_EVENT_OneParam( IPropertyTableColumn, FFrozenStateChanged, const TSharedRef< IPropertyTableColumn >& );`

### `Source/Editor/PropertyEditor/Public/IPropertyTableCustomColumn.h` (Public)


#### class `IPropertyTableCustomColumn`  
`class IPropertyTableCustomColumn`  
_L11-21_
- L14 _public prototype_ `virtual ~IPropertyTableCustomColumn() = default;`
- L16 _public prototype_ `virtual bool Supports( const TSharedRef< IPropertyTableColumn >& Column, const TSharedRef< IPropertyTableUtilities >& Utilities ) const = 0;`
- L18 _public prototype_ `virtual TSharedPtr< SWidget > CreateColumnLabel( const TSharedRef< IPropertyTableColumn >& Column, const TSharedRef< IPropertyTableUtilities >& Utilities, const FName& Style ) const = 0;`
- L20 _public prototype_ `virtual TSharedPtr< IPropertyTableCellPresenter > CreateCellPresenter( const TSharedRef< IPropertyTableCell >& Cell, const TSharedRef< IPropertyTableUtilities >& Utilities, const FName& Style ) const = 0;`

### `Source/Editor/PropertyEditor/Public/IPropertyTableRow.h` (Public)


#### class `IPropertyTableRow`  
`class IPropertyTableRow`  
_L6-28_
- L10 _public prototype_ `virtual TSharedRef< class IDataSource > GetDataSource() const = 0;`
- L12 _public prototype_ `virtual bool HasChildren() const = 0;`
- L14 _public prototype_ `virtual void GetChildRows( TArray< TSharedRef< class IPropertyTableRow > >& OutChildren ) const = 0;`
- L16 _public prototype_ `virtual TSharedRef< class IPropertyTable > GetTable() const = 0;`
- L18 _public prototype_ `virtual bool HasCells() const = 0;`
- L20 _public prototype_ `virtual TSharedRef< class FPropertyPath > GetPartialPath() const = 0;`
- L22 _public prototype_ `virtual void Tick() = 0;`
- L24 _public prototype_ `virtual void Refresh() = 0;`
- L26 _public prototype_ `DECLARE_EVENT( IPropertyTableRow, FRefreshed );`
- L27 _public prototype_ `virtual FRefreshed* OnRefresh() = 0;`

#### Free symbols / members of external scopes

- L26 _delegate_ `DECLARE_EVENT( IPropertyTableRow, FRefreshed );`

### `Source/Editor/PropertyEditor/Public/IPropertyTableUtilities.h` (Public)


#### class `IPropertyTableUtilities`  
`class IPropertyTableUtilities : public IPropertyUtilities`  
_L7-13_
- inherits: `IPropertyUtilities`
- L11 _public prototype_ `virtual void RemoveColumn( const TSharedRef< class IPropertyTableColumn >& Column ) = 0;`

### `Source/Editor/PropertyEditor/Public/IPropertyTableWidgetHandle.h` (Public)


#### class `IPropertyTableWidgetHandle`  
`class IPropertyTableWidgetHandle`  
_L6-13_
- L10 _public prototype_ `virtual void RequestRefresh() = 0;`
- L11 _public prototype_ `virtual TSharedRef<class SWidget> GetWidget() = 0;`

### `Source/Editor/PropertyEditor/Public/IPropertyTreeRow.h` (Public)


#### class `IPropertyTreeRow`  
`class IPropertyTreeRow`  
_L8-15_
- L12 _public prototype_ `virtual TSharedPtr< FPropertyPath > GetPropertyPath() const = 0;`
- L14 _public prototype_ `virtual bool IsCursorHovering() const = 0;`

### `Source/Editor/PropertyEditor/Public/IPropertyTypeCustomization.h` (Public)


#### class `IPropertyTypeCustomization`  
`class IPropertyTypeCustomization : public TSharedFromThis<IPropertyTypeCustomization>`  
_L27-60_
- inherits: `TSharedFromThis<IPropertyTypeCustomization>`
- desc: Base class for property type customizations. The property type customizations are used for Struct and instanced Object properties. The CustomizeHeader() is used to customize the property row, and the CustomizeChildren() is called to add property rows under the header row. If CustomizeHeader() does not populate the row, the child rows will be added inline at the level where the header row would have gone. Note for Object properties: - The customization is looked up based on the instanced Object type, or if multiple objects are edited, the common base class. - The PropertyHandle points to the property value (object pointer), the first child of PropertyHandle is the instanced object, and the instanced object properties are child of that.
- L31 _public prototype_ `virtual ~IPropertyTypeCustomization() = default;`
- L41 _public prototype_ `virtual void CustomizeHeader( TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils ) = 0;` — Called when the header of the property (the row in the details panel where the property is shown) If nothing is added to the row, the header is not displayed @param PropertyHandle			Handle to the property being customized @param HeaderRow					A row that widgets can be added to @param StructCustomizationUtils	Utilities for customization
- L50 _public prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils ) = 0;` — Called when the children of the property should be customized or extra rows added @param PropertyHandle			Handle to the property being customized @param StructBuilder				A builder for adding children @param StructCustomizationUtils	Utilities for customization
- L56 _public function_ `virtual bool ShouldInlineKey() const` — @return whether or not this customisation should be inlined when used as a key within a row

#### class `IPropertyTypeCustomizationUtils`  
`class IPropertyTypeCustomizationUtils`  
_L66-90_
- desc: Utilities for property type customization
- L69 _public prototype_ `virtual ~IPropertyTypeCustomizationUtils()= default;`
- L74 _public function_ `static FSlateFontInfo GetRegularFont()` — @return the font used for properties and details
- L79 _public function_ `static FSlateFontInfo GetBoldFont()` — @return the bold font used for properties and details
- L84 _public prototype_ `virtual TSharedPtr<FAssetThumbnailPool> GetThumbnailPool() const = 0;` — Gets the thumbnail pool that should be used for rendering thumbnails in the struct
- L89 _public function_ `virtual TSharedPtr<IPropertyUtilities> GetPropertyUtilities() const` — @return the utilities various widgets need access to certain features of PropertyDetails

#### class `IStructCustomization`  
`class IStructCustomization : public IPropertyTypeCustomization`  
_L97-128_
- inherits: `IPropertyTypeCustomization`
- desc: Deprecated IStructCustomization interface
- L100 _public function_ `virtual void CustomizeHeader( TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils )`
- L105 _public function_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils )`
- L118 _public prototype_ `virtual void CustomizeStructHeader( TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IStructCustomizationUtils& StructCustomizationUtils ) = 0;` — Called when the header of the struct (usually where the name of the struct and information about the struct as a whole is added) If nothing is added to the row, the header is not displayed @param StructPropertyHandle		Handle to the struct property @param HeaderRow					A row that widgets can be added to @param StructCustomizationUtils	Utilities for struct customization
- L127 _public prototype_ `virtual void CustomizeStructChildren( TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IStructCustomizationUtils& StructCustomizationUtils ) = 0;` — Called when the children of the struct should be customized @param StructPropertyHandle		Handle to the struct property @param StructBuilder				A builder for customizing the struct children @param StructCustomizationUtils	Utilities for struct customization

#### Free symbols / members of external scopes

- L94 _typedef_ `typedef IPropertyTypeCustomizationUtils IStructCustomizationUtils;` — Deprecated IStructCustomizationUtils interface

### `Source/Editor/PropertyEditor/Public/IPropertyUtilities.h` (Public)


#### class `IPropertyUtilities`  
`class IPropertyUtilities`  
_L14-51_
- desc: Settings for property editor widgets that call up to the base container for the widgets without knowing information about that container
- L17 _public prototype_ `virtual ~IPropertyUtilities()= default;`
- L18 _public prototype_ `virtual class FNotifyHook* GetNotifyHook() const = 0;`
- L19 _public prototype_ `virtual bool AreFavoritesEnabled() const = 0;`
- L20 _public prototype_ `virtual void ToggleFavorite( const TSharedRef< class FPropertyEditor >& PropertyEditor ) const = 0;`
- L21 _public prototype_ `virtual void CreateColorPickerWindow( const TSharedRef< class FPropertyEditor >& PropertyEditor, bool bUseAlpha ) const = 0;`
- L22 _public prototype_ `virtual void EnqueueDeferredAction( FSimpleDelegate DeferredAction ) = 0;`
- L23 _public prototype_ `virtual bool IsPropertyEditingEnabled() const = 0;`
- L29 _public prototype_ `virtual void ForceRefresh() = 0;` — Force a rebuild of the view, recreating and updating all widgets. @note This may run immediately; consider RequestForceRefresh unless you need to ensure invalid references (eg, to deleted objects) are removed.
- L35 _public prototype_ `virtual void RequestRefresh() = 0;` — Request a refresh of the view on the next tick, ideally without triggering a full rebuild of all widgets. @note This may run immediately or perform a rebuild depending on the implementation.
- L41 _public prototype_ `virtual void RequestForceRefresh() = 0;` — Request a rebuild of the view on the next tick, recreating and updating all widgets. @note This may run immediately depending on the implementation.
- L43 _public prototype_ `virtual TSharedPtr<class FAssetThumbnailPool> GetThumbnailPool() const = 0;`
- L44 _public prototype_ `virtual void NotifyStartedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent) = 0;`
- L45 _public prototype_ `virtual void NotifyFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent) = 0;`
- L46 _public prototype_ `virtual bool HasClassDefaultObject() const = 0;`
- L47 _public prototype_ `virtual const TArray<TWeakObjectPtr<UObject>>& GetSelectedObjects() const = 0;`
- L49 _public prototype_ `virtual bool DontUpdateValueWhileEditing() const = 0;` — If a customization standalone widget is used, the value should be update only once, when its window is closed
- L50 _public prototype_ `virtual const TArray<TSharedRef<class IClassViewerFilter>>& GetClassViewerFilters() const = 0;`

### `Source/Editor/PropertyEditor/Public/ISinglePropertyView.h` (Public)


#### struct `FSinglePropertyParams`  
`struct FSinglePropertyParams`  
_L15-44_
- desc: Init params for a single property
- L18 _public member_ `FText NameOverride;` — Override for the property name that will be displayed instead of the property name
- L21 _public member_ `FSlateFontInfo Font;` — Font to use instead of the default property font
- L24 _public member_ `FNotifyHook* NotifyHook;` — Notify hook interface to use for some property change events
- L27 _public member_ `EPropertyNamePlacement::Type NamePlacement;` — Whether or not to show the name
- L30 _public member_ `bool bHideAssetThumbnail;` — Whether to hide an asset thumbnail, if available
- L33 _public member_ `bool bHideResetToDefault;` — Whether to hide the 'reset to default' button
- L35 _public function_ `FSinglePropertyParams() : NameOverride(FText::GetEmpty()) , Font() , NotifyHook( NULL ) , NamePlacement( EPropertyNamePlacement::Left ) , bHideAssetThumbnail( false ) , bHideResetToDefault( false )`

#### class `ISinglePropertyView`  
`class ISinglePropertyView : public SCompoundWidget`  
_L51-67_
- inherits: `SCompoundWidget`
- desc: Represents a single property not in a property tree or details view for a single object Structs and Array properties cannot be used with this method
- L55 _public prototype_ `virtual void SetObject( UObject* InObject ) = 0;` — Sets the object to view/edit on the widget
- L58 _public prototype_ `virtual void SetStruct( const TSharedPtr<class IStructureDataProvider>& InStruct) = 0;` — Sets the struct to view/edit on the widget
- L61 _public prototype_ `virtual void SetOnPropertyValueChanged( const FSimpleDelegate& InOnPropertyValueChanged ) = 0;` — Sets a delegate called when the property value changes
- L64 _public prototype_ `virtual bool HasValidProperty() const = 0;` — Whether or not this widget has a valid property
- L66 _public prototype_ `virtual TSharedPtr<class IPropertyHandle> GetPropertyHandle() const = 0;`

### `Source/Editor/PropertyEditor/Public/IStructureDataProvider.h` (Public)


#### class `IStructureDataProvider`  
`class IStructureDataProvider`  
_L57-92_
- L60 _public prototype_ `virtual ~IStructureDataProvider() = default;`
- L63 _public prototype_ `virtual bool IsValid() const = 0;` — @return true if we have any data instances.
- L66 _public prototype_ `virtual const UStruct* GetBaseStructure() const = 0;` — @return the most common struct of the instance data. This struct will be used to build the UI for the instances.
- L74 _public prototype_ `virtual void GetInstances(TArray<TSharedPtr<FStructOnScope>>& OutInstances, const UStruct* ExpectedBaseStructure) const = 0;` — Returns instances to edit. Each provided struct should be compatible with ExpectedType. @param OutInstances returned instances @param ExpectedBaseStructure the base type of struct that is expected to be returned (see the documentation above about ExpectedType)
- L77 _public function_ `virtual bool IsPropertyIndirection() const` — @return true, if the provider supports handling indirections using GetValueBaseAddress().
- L85 _public function_ `virtual uint8* GetValueBaseAddress(uint8* ParentValueAddress, const UStruct* ExpectedBaseStructure) const` — Returns base address of provided struct based on parent property nodes value. @param ParentValueAddress Value of the parent @param ExpectedBaseStructure the base type of struct that is expected to be returned (see the documentation above about ExpectedType) @return value base address based on parent base address.
- L88 _public function_ `virtual void GetInstances(TArray<TSharedPtr<FStructOnScope>>& OutInstances) const final` — `UE_DEPRECATED(5.4, "Please use and override GetInstances() with ExpectedType instead.")`

#### class `FStructOnScopeStructureDataProvider`  
`class FStructOnScopeStructureDataProvider : public IStructureDataProvider`  
_L99-211_
- inherits: `IStructureDataProvider`
- L102 _public prototype_ `FStructOnScopeStructureDataProvider() = default;`
- L103 _public function_ `explicit FStructOnScopeStructureDataProvider(const TSharedPtr<FStructOnScope>& InStructData) : StructDataInstances( {InStructData} )`
- L108 _public function_ `explicit FStructOnScopeStructureDataProvider(const TArray<TSharedPtr<FStructOnScope>>& InStructDataInstances) : StructDataInstances(InStructDataInstances)`
- L113 _public function_ `void SetStructData(const TSharedPtr<FStructOnScope>& InStructData)`
- L118 _public function_ `void SetStructData(const TArray<TSharedPtr<FStructOnScope>>& InStructData)`
- L125 _public function_ `virtual bool IsValid() const override`
- L143 _public function_ `virtual const UStruct* GetBaseStructure() const override`
- L148 _public function_ `virtual void GetInstances(TArray<TSharedPtr<FStructOnScope>>& OutInstances, const UStruct* ExpectedBaseStructure) const override`
- L167 _public function_ `template<typename ContainerType> static const UStruct* FindBaseStructure(const TArray<TSharedPtr<ContainerType>>& StructDataInstances)`
- L210 _protected member_ `TArray<TSharedPtr<FStructOnScope>> StructDataInstances;`

### `Source/Editor/PropertyEditor/Public/IStructureDetailsView.h` (Public)


#### class `IStructureDetailsView`  
`class IStructureDetailsView`  
_L15-71_
- desc: Interface class for all detail views
- L24 _public prototype_ `virtual IDetailsView* GetDetailsView() = 0;` — Get an interface the underlying details view. @return Details view interface.
- L31 _public prototype_ `virtual TSharedPtr<class SWidget> GetWidget() = 0;` — Get this view's Slate widget. @return The widget for this view.
- L38 _public prototype_ `virtual void SetStructureData(TSharedPtr<class FStructOnScope> StructData) = 0;` — Set the structure data to be displayed in this view. @param StructData The structure data to display.
- L45 _public prototype_ `virtual void SetStructureProvider(TSharedPtr<class IStructureDataProvider> StructProvider) = 0;` — Set the structure data to be displayed in this view. @param StructProvider Provider of the the structure data to display.
- L52 _public prototype_ `virtual void SetCustomName(const FText& Text) = 0;` — Set the CustomName used for display purposes. @param Text The FText to use for setting the Name
- L58 _public function_ `virtual TSharedPtr<const class IStructureDataProvider> GetStructureProvider() const` — Get Const access to the StructureProvider. Not pure virtual for backwards compatibility reasons.
- L70 _public prototype_ `virtual FOnFinishedChangingProperties& GetOnFinishedChangingPropertiesDelegate() = 0;` — Get a delegate that is executed when the view has finished changing properties. @return The delegate.

### `Source/Editor/PropertyEditor/Public/MaterialList.h` (Public)


#### struct `FMaterialListDelegates`  
`struct FMaterialListDelegates`  
_L43-84_
- L45 _public function_ `FMaterialListDelegates() : OnGetMaterials() , OnMaterialChanged() , OnGenerateCustomNameWidgets() , OnGenerateCustomMaterialWidgets() , OnResetMaterialToDefaultClicked() , OnGenerateExtraBottomWidget()`
- L55 _public member_ `FOnGetMaterials OnGetMaterials;` — Delegate called to populate the list with materials
- L57 _public member_ `FOnMaterialChanged OnMaterialChanged;` — Delegate called when a user changes the material
- L59 _public member_ `FOnGenerateWidgetsForMaterial OnGenerateCustomNameWidgets;` — Delegate called to generate custom widgets under the name of in the left column of a details panel
- L61 _public member_ `FOnGenerateWidgetsForMaterial OnGenerateCustomMaterialWidgets;` — Delegate called to generate custom widgets under each material
- L63 _public member_ `FOnResetMaterialToDefaultClicked OnResetMaterialToDefaultClicked;` — Delegate called when a material list item should be reset to default
- L65 _public member_ `FOnGenerateWidgetsForMaterial OnGenerateExtraBottomWidget;` — Delegate called to generate extra widget under the material row
- L67 _public member_ `FOnMaterialListDirty OnMaterialListDirty;` — Delegate called when we tick the material list to know if the list is dirty
- L70 _public member_ `FOnCopyMaterialList OnCopyMaterialList;` — Delegate called Copying a material list
- L72 _public member_ `FOnCanCopyMaterialList OnCanCopyMaterialList;` — Delegate called to know if we can copy a material list
- L74 _public member_ `FOnPasteMaterialList OnPasteMaterialList;` — Delegate called Pasting a material list
- L76 _public member_ `TWeakPtr<FOnPasteFromText> OnPasteFromText;` — Delegate called Pasting an optionally tagged text snippet
- L79 _public member_ `FOnCopyMaterialItem OnCopyMaterialItem;` — Delegate called Copying a material item
- L81 _public member_ `FOnCanCopyMaterialItem OnCanCopyMaterialItem;` — Delegate called to know if we can copy a material item
- L83 _public member_ `FOnPasteMaterialItem OnPasteMaterialItem;` — Delegate called Pasting a material item

#### class `IMaterialListBuilder`  
`class IMaterialListBuilder`  
_L89-105_
- desc: Builds up a list of unique materials while creating some information about the materials
- L94 _public prototype_ `virtual ~IMaterialListBuilder()= default;` — Virtual destructor.
- L104 _public prototype_ `virtual void AddMaterial( uint32 SlotIndex, UMaterialInterface* Material, bool bCanBeReplaced, UActorComponent* InCurrentComponent = nullptr, FName SlotName = FName()) = 0;` — Adds a new material to the list @param SlotIndex The slot (usually mesh element index) where the material is located on the component. @param Material The material being used. @param bCanBeReplced Whether or not the material can be replaced by a user. @param InCurrentComponent The current component using the current material

#### struct `FMaterialListItem`  
`struct FMaterialListItem`  
_L110-149_
- desc: A Material item in a material list slot
- L113 _public member_ `TWeakObjectPtr<UMaterialInterface> Material;` — Material being used
- L116 _public member_ `int32 SlotIndex;` — Slot on a component where this material is at (mesh element)
- L119 _public member_ `bool bCanBeReplaced;` — Whether or not this material can be replaced by a new material
- L122 _public member_ `TWeakObjectPtr<UActorComponent> CurrentComponent;` — The current component using the current material
- L125 _public member_ `FName SlotName;` — User-specified name for the slot on a component where this material is at (mesh element). May be empty.
- L127 _public function_ `FMaterialListItem( UMaterialInterface* InMaterial = NULL, uint32 InSlotIndex = 0, bool bInCanBeReplaced = false, UActorComponent* InCurrentComponent = nullptr, FName InSlotName = FName()) : Material( InMaterial ) , SlotIndex( InSlotIndex ) , bCanBeReplaced( bInCanBeReplaced ) , CurrentComponent(InCurrentComponent) , SlotName(InSlotName)`
- L140 _public function_ `bool operator==( const FMaterialListItem& Other ) const`
- L145 _public function_ `bool operator!=( const FMaterialListItem& Other ) const`

#### class `FMaterialItemView`  
`class FMaterialItemView : public TSharedFromThis<FMaterialItemView>`  
_L154-297_
- inherits: `TSharedFromThis<FMaterialItemView>`
- desc: A view of a single item in an FMaterialList
- L158 _public prototype_ `virtual ~FMaterialItemView() = default;` — Virtual destructor
- L166 _public prototype_ `static TSharedRef<FMaterialItemView> Create( const FMaterialListItem& Material, FOnMaterialChanged InOnMaterialChanged, FOnGenerateWidgetsForMaterial InOnGenerateNameWidgetsForMaterial, FOnGenerateWidgetsForMaterial InOnGenerateWidgetsForMaterial, FOnResetMaterialToDefaultClicked InOnResetToDefaultClicked, FOnGenerateWidgetsForMaterial InOnGenerateExtraBottomWidget, int32 InMultipleMaterialCount, bool bShowUsedTextures);` — Creates a new instance of this class @param Material				The material to view @param InOnMaterialChanged	Delegate for when the material changes
- L179 _public prototype_ `virtual TSharedRef<SWidget> CreateNameContent();` — Create a Name Content for Material Item Widget
- L184 _public prototype_ `virtual TSharedRef<SWidget> CreateValueContent(IDetailLayoutBuilder& InDetailBuilder, const TArray<FAssetData>& OwnerAssetDataArray, UActorComponent* InActorComponent);` — Create a Value Content for Material Item Widget
- L189 _public function_ `const FMaterialListItem& GetMaterialListItem() const` — Get Material item in a material list slot
- L197 _public prototype_ `void ReplaceMaterial( UMaterialInterface* NewMaterial, bool bReplaceAll = false );` — Replace material in slot @param NewMaterial			The new material apply to slot @param bReplaceAll			Whether it should be applied to all slots
- L202 _public prototype_ `bool GetResetToBaseVisibility() const;` — Called to get the visibility of the reset to base button
- L207 _public prototype_ `void OnResetToBaseClicked();` — Called when reset to base is clicked
- L210 _private prototype_ `FMaterialItemView(const FMaterialListItem& InMaterial, FOnMaterialChanged& InOnMaterialChanged, FOnGenerateWidgetsForMaterial& InOnGenerateNameWidgets, FOnGenerateWidgetsForMaterial& InOnGenerateMaterialWidgets, FOnResetMaterialToDefaultClicked& InOnResetToDefaultClicked, FOnGenerateWidgetsForMaterial& OnGenerateExtraBottomWidget, int32 InMultipleMaterialCount, bool bInShowUsedTextures);`
- L222 _private prototype_ `void OnSetObject( const FAssetData& AssetData );` — Handler when the material asset has been changed
- L227 _private prototype_ `bool IsTexturesMenuEnabled() const;` — @return Whether or not the textures menu is enabled
- L232 _private prototype_ `TSharedRef<SWidget> OnGetTexturesMenuForMaterial();` — Generate list of the textures for material selection list
- L237 _private prototype_ `TSharedRef<SWidget> MakeBrowseNaniteOverrideMaterialButton() const;` — Create button for browse to nanite override material
- L242 _private prototype_ `FText GetTexturesMenuToolTipText() const;` — @return The tool tip for the textures menuuuuu
- L247 _private prototype_ `FString OnGetObjectPath() const;` — On Get object path handler
- L252 _private prototype_ `void GoToAssetInContentBrowser( TWeakObjectPtr<UObject> Object );` — Finds the asset in the content browser
- L262 _private prototype_ `struct FOnGenerateGlobalRowExtensionArgs GetGlobalRowExtensionArgs(IDetailLayoutBuilder& InDetailBuilder, UActorComponent* InCurrentComponent) const;` — Get Property Row Extenssion Arguments. The extension arguments is needed to add button or custom widget to property row. @param InDetailBuilder The builder for laying custom details. @param InCurrentComponent The current component using the current material. @return Generate Global Row Extension Args
- L271 _private prototype_ `TSharedPtr<SWidget> GetGlobalRowExtensionWidget(IDetailLayoutBuilder& InDetailBuilder, UActorComponent* InCurrentComponent) const;` — Get row extension widget @param InDetailBuilder The builder for laying custom details. @param InCurrentComponent The current component using the current material. @return Pointer to widget
- L275 _private member_ `FMaterialListItem MaterialItem;` — The Material item in a material list slot
- L278 _private member_ `FOnMaterialChanged OnMaterialChanged;` — Material Changed delegate
- L281 _private member_ `FOnGenerateWidgetsForMaterial OnGenerateCustomNameWidgets;` — Generate custom name delegate
- L284 _private member_ `FOnGenerateWidgetsForMaterial OnGenerateCustomMaterialWidgets;` — Generate custom material widget delegate
- L287 _private member_ `FOnResetMaterialToDefaultClicked OnResetToDefaultClicked;` — Reset to default delegate
- L290 _private member_ `FOnGenerateWidgetsForMaterial OnGenerateExtraBottomWidget;` — Generate custom widget under the material row delegate
- L293 _private member_ `int32 MultipleMaterialCount;` — Number of material count
- L296 _private member_ `bool bShowUsedTextures;` — Whether it should show textures

#### class `FMaterialList`  
`class FMaterialList : public IDetailCustomNodeBuilder , public TSharedFromThis<FMaterialList>`  
_L302-391_
- inherits: `IDetailCustomNodeBuilder,TSharedFromThis<FMaterialList>`
- desc: Custom Node Builder for Material List
- L308 _public prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnAddMaterialItemViewExtraBottomWidget, const TSharedRef<FMaterialItemView>& , UActorComponent* , IDetailLayoutBuilder& , TArray<TSharedPtr<SWidget>>& );` — Add Extra widgets for bottom material value field.
- L313 _public member_ `static FOnAddMaterialItemViewExtraBottomWidget OnAddMaterialItemViewExtraBottomWidget;`
- L315 _public prototype_ `FMaterialList( IDetailLayoutBuilder& InDetailLayoutBuilder, FMaterialListDelegates& MaterialListDelegates, const TArray<FAssetData>& InOwnerAssetDataArray, bool bInAllowCollapse = false, bool bInShowUsedTextures = true);`
- L323 _private prototype_ `void OnDisplayMaterialsForElement( int32 SlotIndex );` — Called when a user expands all materials in a slot. @param SlotIndex The index of the slot being expanded.
- L330 _private prototype_ `void OnHideMaterialsForElement( int32 SlotIndex );` — Called when a user hides all materials in a slot. @param SlotIndex The index of the slot being hidden.
- L333 _private function_ `virtual void SetOnRebuildChildren( FSimpleDelegate InOnRebuildChildren ) override` — IDetailCustomNodeBuilder interface
- L334 _private function_ `virtual bool RequiresTick() const override`
- L335 _private prototype_ `virtual void Tick( float DeltaTime ) override;`
- L336 _private prototype_ `virtual void GenerateHeaderRowContent( FDetailWidgetRow& NodeRow ) override;`
- L337 _private prototype_ `virtual void GenerateChildContent( IDetailChildrenBuilder& ChildrenBuilder ) override;`
- L338 _private function_ `virtual FName GetName() const override`
- L339 _private function_ `virtual bool InitiallyCollapsed() const override`
- L350 _private prototype_ `void AddMaterialItem(FDetailWidgetRow& Row, int32 CurrentSlot, const FMaterialListItem& Item, bool bDisplayLink, UActorComponent* InCurrentComponent = nullptr);` — Adds a new material item to the list @param Row					The row to add the item to @param CurrentSlot			The slot id of the material @param Item					The material item to add @param bDisplayLink			If a link to the material should be displayed instead of the actual item (for multiple materials) @param InCurrentComponent	The current component using the current material
- L353 _private prototype_ `bool OnCanCopyMaterialList() const;`
- L354 _private prototype_ `void OnCopyMaterialList();`
- L355 _private prototype_ `void OnPasteMaterialList();`
- L358 _private prototype_ `void OnPasteMaterialListFromText(const FString& InTag, const FString& InText, const TOptional<FGuid>& InOperationId);` — Handle pasting an optionally tagged text snippet
- L360 _private prototype_ `bool OnCanCopyMaterialItem(int32 CurrentSlot) const;`
- L361 _private prototype_ `void OnCopyMaterialItem(int32 CurrentSlot);`
- L362 _private prototype_ `void OnPasteMaterialItem(int32 CurrentSlot);`
- L365 _private member_ `FMaterialListDelegates MaterialListDelegates;` — Delegates for the material list
- L368 _private member_ `FSimpleDelegate OnRebuildChildren;` — Called to rebuild the children of the detail tree
- L371 _private member_ `IDetailLayoutBuilder& DetailLayoutBuilder;` — Parent detail layout this list is in
- L374 _private member_ `TArray< FMaterialListItem > DisplayedMaterials;` — Set of all unique displayed materials
- L377 _private member_ `TArray< TSharedRef<FMaterialItemView> > ViewedMaterials;` — Set of all materials currently in view (may be less than DisplayedMaterials)
- L380 _private member_ `TSet<uint32> ExpandedSlots;` — Set of all expanded slots
- L383 _private member_ `TSharedRef<FMaterialListBuilder> MaterialListBuilder;` — Material list builder used to generate materials
- L386 _private member_ `bool bAllowCollpase;` — Allow Collapse of material header row. Right now if you allow collapse, it will initially collapse.
- L388 _private member_ `bool bShowUsedTextures;` — Whether or not to use the used textures menu for each material entry
- L390 _private member_ `TArray<FAssetData> OwnerAssetDataArray;` — The mesh asset that owns these materials

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API PROPERTYEDITOR_API`
- L22 _delegate_ `DECLARE_DELEGATE_OneParam(FOnGetMaterials, IMaterialListBuilder&);` — Delegate called when we need to get new materials for the list
- L22 _prototype_ `DECLARE_DELEGATE_OneParam(FOnGetMaterials, IMaterialListBuilder&);` — Delegate called when we need to get new materials for the list
- L27 _delegate_ `DECLARE_DELEGATE_FourParams( FOnMaterialChanged, UMaterialInterface*, UMaterialInterface*, int32, bool );` — Delegate called when a user changes the material
- L27 _prototype_ `DECLARE_DELEGATE_FourParams( FOnMaterialChanged, UMaterialInterface*, UMaterialInterface*, int32, bool );` — Delegate called when a user changes the material
- L29 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams( TSharedRef<SWidget>, FOnGenerateWidgetsForMaterial, UMaterialInterface*, int32 );`
- L29 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams( TSharedRef<SWidget>, FOnGenerateWidgetsForMaterial, UMaterialInterface*, int32 );`
- L31 _delegate_ `DECLARE_DELEGATE_TwoParams( FOnResetMaterialToDefaultClicked, UMaterialInterface*, int32 );`
- L31 _prototype_ `DECLARE_DELEGATE_TwoParams( FOnResetMaterialToDefaultClicked, UMaterialInterface*, int32 );`
- L33 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FOnMaterialListDirty);`
- L33 _prototype_ `DECLARE_DELEGATE_RetVal(bool, FOnMaterialListDirty);`
- L35 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FOnCanCopyMaterialList);`
- L35 _prototype_ `DECLARE_DELEGATE_RetVal(bool, FOnCanCopyMaterialList);`
- L36 _delegate_ `DECLARE_DELEGATE(FOnCopyMaterialList);`
- L36 _prototype_ `DECLARE_DELEGATE(FOnCopyMaterialList);`
- L37 _delegate_ `DECLARE_DELEGATE(FOnPasteMaterialList);`
- L37 _prototype_ `DECLARE_DELEGATE(FOnPasteMaterialList);`
- L39 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnCanCopyMaterialItem, int32);`
- L39 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnCanCopyMaterialItem, int32);`
- L40 _delegate_ `DECLARE_DELEGATE_OneParam(FOnCopyMaterialItem, int32);`
- L40 _prototype_ `DECLARE_DELEGATE_OneParam(FOnCopyMaterialItem, int32);`
- L41 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPasteMaterialItem, int32);`
- L41 _prototype_ `DECLARE_DELEGATE_OneParam(FOnPasteMaterialItem, int32);`
- L135 _function_ `friend uint32 GetTypeHash( const FMaterialListItem& InItem )`
- L308 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnAddMaterialItemViewExtraBottomWidget, const TSharedRef<FMaterialItemView>& , UActorComponent* , IDetailLayoutBuilder& , TArray<TSharedPtr<SWidget>>& );` — Add Extra widgets for bottom material value field.

### `Source/Editor/PropertyEditor/Public/NumericPropertyParams.h` (Public)


#### struct `TNumericPropertyParams`  
`template<typename NumericType> struct TNumericPropertyParams`  
_L10-130_
- L13 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FString, FMetaDataGetter, FName);`
- L15 _public function_ `TNumericPropertyParams(const FProperty* Property, FMetaDataGetter MetaDataGetter)`
- L117 _public function_ `TAttribute<int32> GetLinearDeltaSensitivityAttribute() const`
- L122 _public member_ `TOptional<NumericType> MinValue;`
- L123 _public member_ `TOptional<NumericType> MaxValue;`
- L124 _public member_ `TOptional<NumericType> MinSliderValue;`
- L125 _public member_ `TOptional<NumericType> MaxSliderValue;`
- L126 _public member_ `NumericType SliderExponent;`
- L127 _public member_ `NumericType Delta;`
- L128 _public member_ `int32 LinearDeltaSensitivity;`
- L129 _public member_ `TOptional<NumericType> WheelStep;`

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FString, FMetaDataGetter, FName);`
- L30 _function_ `` (scope `TNumericPropertyParams::TNumericPropertyParams`)

### `Source/Editor/PropertyEditor/Public/PropertyCustomizationHelpers.h` (Public)


#### struct `FPropertyComboBoxArgs`  
`struct FPropertyComboBoxArgs`  
_L59-93_
- desc: Collects advanced arguments for MakePropertyComboBox
- L62 _public member_ `TSharedPtr<IPropertyHandle> PropertyHandle;` — If set, the combo box will bind to a specific property. If this is null, the following 3 delegates must be set
- L65 _public member_ `FOnGetPropertyComboBoxStrings OnGetStrings;` — Delegate that is called to generate the list of possible strings inside the combo box list. If not set it will generate using the property handle
- L68 _public member_ `FOnGetPropertyComboBoxValue OnGetValue;` — Delegate that is called to get the current string value to display as the combo box label. If not set it will generate using the property handle
- L71 _public member_ `FOnPropertyComboBoxValueSelected OnValueSelected;` — Delegate called when a string is selected. If not set it will modify what is bound to the property handle
- L74 _public member_ `int32 ShowSearchForItemCount = 20;` — If number of items in combo box is >= this, it will show a search box to allow filtering. -1 means to never show it
- L77 _public member_ `FSlateFontInfo Font;` — Font to use for text display. If not set it will use the default property editor font
- L80 _public function_ `FPropertyComboBoxArgs()` — Default constructor, the caller will need to fill in values manually
- L84 _public function_ `FPropertyComboBoxArgs(const TSharedPtr<IPropertyHandle>& InPropertyHandle, FOnGetPropertyComboBoxStrings InOnGetStrings = FOnGetPropertyComboBoxStrings(), FOnGetPropertyComboBoxValue InOnGetValue = FOnGetPropertyComboBoxValue(), FOnPropertyComboBoxValueSelected InOnValueSelected = FOnPropertyComboBoxValueSelected()) : PropertyHandle(InPropertyHandle) , OnGetStrings(InOnGetStrings) , OnGetValue(InOnGetValue) , OnValueSelected(InOnValueSelected)` — Constructor using original function arguments

#### struct `FPropertyFunctionCallArgs`  
`struct FPropertyFunctionCallArgs`  
_L95-126_
- L97 _public member_ `TWeakObjectPtr<UFunction> Function;`
- L99 _public member_ `TOptional<FText> LabelOverride;`
- L101 _public member_ `TOptional<FText> ToolTipTextOverride;`
- L103 _public typedef_ `using FOnExecute = TDelegate<FReply(TWeakObjectPtr<UFunction>)>;`
- L104 _public member_ `FOnExecute OnExecute;`
- L106 _public typedef_ `using FOnCanExecute = TDelegate<bool(TWeakObjectPtr<UFunction>)>;`
- L107 _public member_ `FOnCanExecute OnCanExecute;`
- L109 _public member_ `FTextBuilder* SearchText = nullptr;`
- L111 _public function_ `FPropertyFunctionCallArgs( UFunction* InFunction, const FOnExecute& InOnExecute, const FOnCanExecute& InOnCanExecute = {}, const TOptional<FText>& InLabelOverride = {}, const TOptional<FText>& InToolTipTextOverride = {}, FTextBuilder* InSearchText = nullptr) : Function(InFunction) , LabelOverride(InLabelOverride) , ToolTipTextOverride(InToolTipTextOverride) , OnExecute(InOnExecute) , OnCanExecute(InOnCanExecute) , SearchText(InSearchText)`

#### struct `FPropertyFunctionCallDelegates`  
`struct FPropertyFunctionCallDelegates`  
_L129-152_
- desc: The callbacks, if specified, are used when invoking function calls.
- L131 _public typedef_ `using FOnGetExecutionContext = TDelegate<TArray<TWeakObjectPtr<UObject>>(TWeakObjectPtr<UFunction>)>;`
- L132 _public member_ `FOnGetExecutionContext OnGetExecutionContext;`
- L134 _public typedef_ `using FOnExecute = TDelegate<FReply(TWeakObjectPtr<UFunction>)>;`
- L135 _public member_ `FOnExecute OnExecute;`
- L137 _public typedef_ `using FOnCanExecute = TDelegate<bool(TWeakObjectPtr<UFunction>)>;`
- L138 _public member_ `FOnCanExecute OnCanExecute;`
- L140 _public function_ `FPropertyFunctionCallDelegates( const FOnExecute& InOnExecute, const FOnCanExecute& InOnCanExecute = {}) : OnExecute(InOnExecute) , OnCanExecute(InOnCanExecute)`
- L148 _public function_ `FPropertyFunctionCallDelegates(const FOnGetExecutionContext& InOnGetExecutionContext) : OnGetExecutionContext(InOnGetExecutionContext)`

#### class `SObjectPropertyEntryBox`  
`class SObjectPropertyEntryBox : public SCompoundWidget`  
_L274-369_
- inherits: `SCompoundWidget`
- desc: Simulates an object property field Can be used when a property should act like a FObjectProperty but it isn't one
- L277 _public function_ `SLATE_BEGIN_ARGS( SObjectPropertyEntryBox ) : _AllowedClass( UObject::StaticClass() ) , _AllowClear( true ) , _DisplayUseSelected( true ) , _DisplayBrowse( true ) , _EnableContentPicker(true) , _DisplayCompactSize(false) , _DisplayThumbnail(true)`
- L287 _public prototype_ `SLATE_ATTRIBUTE( FString, ObjectPath ) SLATE_ARGUMENT( TSharedPtr<IPropertyHandle>, PropertyHandle ) SLATE_ARGUMENT(TArray<FAssetData>, OwnerAssetDataArray) SLATE_ARGUMENT( TSharedPtr<FAssetThumbnailPool>, ThumbnailPool ) SLATE_ARGUMENT( const UClass*, AllowedClass ) SLATE_ARGUMENT( TOptional<TArray<UFactory*>>, NewAssetFactories ) SLATE_EVENT(FOnShouldSetAsset, OnShouldSetAsset) SLATE_EVENT(FOnSetObject, OnObjectChanged) SLATE_EVENT(FOnShouldFilterAsset, OnShouldFilterAsset) SLATE_EVENT(FOnIsEnabled, OnIsEnabled) SLATE_ARGUMENT(bool, AllowClear) SLATE_ARGUMENT(bool, AllowCreate) SLATE_ARGUMENT(bool, DisplayUseSelected) SLATE_ARGUMENT(bool, DisplayBrowse) SLATE_EVENT(FSimpleDelegate, OnBrowseOverride) SLATE_ATTRIBUTE(FText, OnBrowseToolTipOverride) SLATE_ATTRIBUTE(const FSlateBrush*, OnBrowseIconOverride) SLATE_ARGUMENT(bool, EnableContentPicker) SLATE_ARGUMENT(bool, DisplayCompactSize) SLATE_ARGUMENT(bool, DisplayThumbnail)` — The path to the object
- L339 _public prototype_ `void GetDesiredWidth(float& OutMinDesiredWidth, float &OutMaxDesiredWidth);`
- L341 _public prototype_ `void OpenEntryBox();`
- L347 _private prototype_ `void OnSetObject(const FAssetData& InObject);` — Delegate function called when an object is changed
- L350 _private prototype_ `FString OnGetObjectPath() const;` — @return the object path for the object we are viewing
- L352 _private prototype_ `bool IsEnabled() const;`
- L356 _private member_ `FOnShouldSetAsset OnShouldSetAsset;` — Delegate to call to determine whether the asset should be set
- L358 _private member_ `FOnShouldFilterActor OnShouldFilterActor;` — Delegate to call to determine whether the actor should be allowed
- L360 _private member_ `FOnSetObject OnObjectChanged;` — Delegate to call when the object changes
- L362 _private member_ `FOnIsEnabled OnIsEnabled;` — Delegate to call to check if this widget should be enabled.
- L364 _private member_ `TAttribute<FString> ObjectPath;` — Path to the object
- L366 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;` — Handle to a property we modify (if any)
- L368 _private member_ `TSharedPtr<SPropertyEditorAsset> PropertyEditorAsset;` — The widget used to edit the object 'property'

#### class `SClassPropertyEntryBox`  
`class SClassPropertyEntryBox : public SCompoundWidget`  
_L380-426_
- inherits: `SCompoundWidget`
- desc: Simulates a class property field Can be used when a property should act like a FClassProperty but it isn't one
- L383 _public function_ `SLATE_BEGIN_ARGS(SClassPropertyEntryBox) : _MetaClass(UObject::StaticClass()) , _RequiredInterface(nullptr) , _AllowAbstract(false) , _IsBlueprintBaseOnly(false) , _AllowNone(true) , _HideViewOptions(false) , _ShowDisplayNames(false) , _ShowTreeView(false)`
- L394 _public prototype_ `SLATE_ARGUMENT(const UClass*, MetaClass) SLATE_ARGUMENT(const UClass*, RequiredInterface) SLATE_ARGUMENT(TArray<const UClass*>, AllowedClasses) SLATE_ARGUMENT(TArray<const UClass*>, DisallowedClasses) SLATE_ARGUMENT(bool, AllowAbstract) SLATE_ARGUMENT(bool, IsBlueprintBaseOnly) SLATE_ARGUMENT(bool, AllowNone) SLATE_ARGUMENT(bool, HideViewOptions) SLATE_ARGUMENT(bool, ShowDisplayNames) SLATE_ARGUMENT(bool, ShowTreeView) SLATE_ATTRIBUTE(const UClass*, SelectedClass) SLATE_EVENT(FOnSetClass, OnSetClass) SLATE_ARGUMENT(TArray<TSharedRef<IClassViewerFilter>>, ClassViewerFilters) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The meta class that the selected class must be a child-of (required)
- L425 _private member_ `TSharedPtr<SPropertyEditorClass> PropertyEditorClass;` — The widget used to edit the class 'property'

#### class `SStructPropertyEntryBox`  
`class SStructPropertyEntryBox : public SCompoundWidget`  
_L437-468_
- inherits: `SCompoundWidget`
- desc: Simulates a struct type property field Can be used when a property should act like a struct type but it isn't one
- L440 _public function_ `SLATE_BEGIN_ARGS(SStructPropertyEntryBox) : _MetaStruct(nullptr) , _AllowNone(true) , _HideViewOptions(false) , _ShowDisplayNames(false) , _ShowTreeView(false)`
- L448 _public prototype_ `SLATE_ARGUMENT(const UScriptStruct*, MetaStruct) SLATE_ARGUMENT(bool, AllowNone) SLATE_ARGUMENT(bool, HideViewOptions) SLATE_ARGUMENT(bool, ShowDisplayNames) SLATE_ARGUMENT(bool, ShowTreeView) SLATE_ATTRIBUTE(const UScriptStruct*, SelectedStruct) SLATE_EVENT(FOnSetStruct, OnSetStruct) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The meta class that the selected struct must be a child-of (optional)
- L467 _private member_ `TSharedPtr<SPropertyEditorStruct> PropertyEditorStruct;` — The widget used to edit the struct 'property'

#### class `SProperty`  
`class SProperty : public SCompoundWidget`  
_L475-523_
- inherits: `SCompoundWidget`
- desc: Represents a widget that can display a FProperty With the ability to customize the look of the property
- L479 _public prototype_ `DECLARE_DELEGATE( FOnPropertyValueChanged );`
- L481 _public function_ `SLATE_BEGIN_ARGS( SProperty ) : _ShouldDisplayName( true ) , _DisplayResetToDefault( true )`
- L486 _public prototype_ `SLATE_ATTRIBUTE( FText, DisplayName ) SLATE_ARGUMENT( bool, ShouldDisplayName ) SLATE_DEFAULT_SLOT( FArguments, CustomWidget ) SLATE_ARGUMENT( bool, DisplayResetToDefault ) SLATE_END_ARGS() virtual ~SProperty()= default;` — The display name to use in the default property widget
- L496 _public prototype_ `void Construct( const FArguments& InArgs, TSharedPtr<IPropertyHandle> InPropertyHandle );`
- L501 _public prototype_ `virtual void ResetToDefault();` — Resets the property to default
- L506 _public prototype_ `virtual bool ShouldShowResetToDefault() const;` — @return Whether or not the reset to default option should be visible
- L511 _public prototype_ `virtual FText GetResetToDefaultLabel() const;` — @return a label suitable for displaying in a reset to default menu
- L518 _public prototype_ `virtual bool IsValidProperty() const;` — Returns whether or not this property is valid.  Sometimes property widgets are created even when their FProperty is not exposed to the user.  In that case the property is invalid Properties can also become invalid if selection changes in the detail view and this value is stored somewhere. @return Whether or not the property is valid.
- L522 _protected member_ `TSharedPtr<IPropertyHandle> PropertyHandle;` — The handle being accessed by this widget

#### class `FDetailArrayBuilder`  
`class FDetailArrayBuilder : public IDetailCustomNodeBuilder`  
_L528-667_
- inherits: `IDetailCustomNodeBuilder`
- L533 _public function_ `FDetailArrayBuilder(TSharedRef<IPropertyHandle> InBaseProperty, bool InGenerateHeader = true, bool InDisplayResetToDefault = true, bool InDisplayElementNum = true) : ArrayProperty( InBaseProperty->AsArray() ) , BaseProperty( InBaseProperty ) , bGenerateHeader( InGenerateHeader) , bDisplayResetToDefault(InDisplayResetToDefault) , bDisplayElementNum(InDisplayElementNum)`
- L549 _public function_ `~FDetailArrayBuilder()`
- L554 _public function_ `void SetDisplayName( const FText& InDisplayName )`
- L559 _public function_ `void OnGenerateArrayElementWidget( FOnGenerateArrayElementWidget InOnGenerateArrayElementWidget )`
- L564 _public function_ `virtual bool RequiresTick() const override`
- L566 _public function_ `virtual void Tick( float DeltaTime ) override`
- L568 _public function_ `virtual FName GetName() const override`
- L573 _public function_ `virtual bool InitiallyCollapsed() const override`
- L575 _public function_ `virtual void GenerateHeaderRowContent( FDetailWidgetRow& NodeRow ) override`
- L620 _public function_ `virtual void GenerateChildContent( IDetailChildrenBuilder& ChildrenBuilder ) override`
- L633 _public function_ `virtual void RefreshChildren()`
- L638 _public function_ `virtual TSharedPtr<IPropertyHandle> GetPropertyHandle() const`
- L645 _protected function_ `virtual void SetOnRebuildChildren( FSimpleDelegate InOnRebuildChildren ) override`
- L647 _protected function_ `void OnNumChildrenChanged()`
- L652 _protected function_ `bool GetShouldGenerateHeader() const`
- L653 _protected function_ `bool GetShouldDisplayResetToDefault() const`
- L654 _protected function_ `bool GetShouldDisplayElementNum() const`
- L658 _private member_ `FText DisplayName;`
- L659 _private member_ `FOnGenerateArrayElementWidget OnGenerateArrayElementWidgetDelegate;`
- L660 _private member_ `TSharedPtr<IPropertyHandleArray> ArrayProperty;`
- L661 _private member_ `TSharedRef<IPropertyHandle> BaseProperty;`
- L662 _private member_ `FSimpleDelegate OnRebuildChildren;`
- L663 _private member_ `bool bGenerateHeader;`
- L664 _private member_ `bool bDisplayResetToDefault;`
- L665 _private member_ `bool bDisplayElementNum;`
- L666 _private member_ `FDelegateHandle OnNumElementsChangedHandle;`

#### class `SMaterialSlotWidget`  
`class SMaterialSlotWidget : public SCompoundWidget`  
_L672-687_
- inherits: `SCompoundWidget`
- desc: Helper class to create a material slot name widget for material lists
- L674 _private function_ `SLATE_BEGIN_ARGS(SMaterialSlotWidget) : _DeleteMaterialSlotVisibility(EVisibility::Visible)`
- L677 _private prototype_ `SLATE_ATTRIBUTE(FText, MaterialName) SLATE_ATTRIBUTE(bool, IsMaterialSlotNameReadOnly) SLATE_EVENT(FOnTextChanged, OnMaterialNameChanged) SLATE_EVENT(FOnTextCommitted, OnMaterialNameCommitted) SLATE_ATTRIBUTE(bool, CanDeleteMaterialSlot) SLATE_EVENT(FSimpleDelegate, OnDeleteMaterialSlot) SLATE_ATTRIBUTE(EVisibility, DeleteMaterialSlotVisibility) SLATE_END_ARGS() void Construct(const FArguments& InArgs, int32 SlotIndex, bool bIsMaterialUsed);`

#### struct `FSectionListDelegates`  
`struct FSectionListDelegates`  
_L718-754_
- L720 _public function_ `FSectionListDelegates() : OnGetSections() , OnSectionChanged() , OnGenerateCustomNameWidgets() , OnGenerateCustomSectionWidgets() , OnResetSectionToDefaultClicked()`
- L729 _public member_ `FOnGetSections OnGetSections;` — Delegate called to populate the list with Sections
- L731 _public member_ `FOnSectionChanged OnSectionChanged;` — Delegate called when a user changes the Section
- L733 _public member_ `FOnGenerateWidgetsForSection OnGenerateCustomNameWidgets;` — Delegate called to generate custom widgets under the name of in the left column of a details panel
- L735 _public member_ `FOnGenerateWidgetsForSection OnGenerateCustomSectionWidgets;` — Delegate called to generate custom widgets under each Section
- L737 _public member_ `FOnResetSectionToDefaultClicked OnResetSectionToDefaultClicked;` — Delegate called when a Section list item should be reset to default
- L740 _public member_ `FOnCopySectionList OnCopySectionList;` — Delegate called Copying a section list
- L742 _public member_ `FOnCanCopySectionList OnCanCopySectionList;` — Delegate called to know if we can copy a section list
- L744 _public member_ `FOnPasteSectionList OnPasteSectionList;` — Delegate called Pasting a section list
- L747 _public member_ `FOnCopySectionItem OnCopySectionItem;` — Delegate called Copying a section item
- L749 _public member_ `FOnCanCopySectionItem OnCanCopySectionItem;` — Delegate called To know if we can copy a section item
- L751 _public member_ `FOnPasteSectionItem OnPasteSectionItem;` — Delegate called Pasting a section item
- L753 _public member_ `FOnEnableSectionItem OnEnableSectionItem;` — Delegate called when enabling/disabling a section item

#### class `ISectionListBuilder`  
`class ISectionListBuilder`  
_L759-771_
- desc: Builds up a list of unique Sections while creating some information about the Sections
- L762 _public prototype_ `virtual ~ISectionListBuilder() = default;`
- L770 _public prototype_ `virtual void AddSection(int32 LodIndex, int32 SectionIndex, FName InMaterialSlotName, int32 InMaterialSlotIndex, FName InOriginalMaterialSlotName, const TMap<int32, FName> &InAvailableMaterialSlotName, const UMaterialInterface* Material, bool IsSectionUsingCloth, bool bIsChunkSection, int32 DefaultMaterialIndex) = 0;` — Adds a new Section to the list @param SlotIndex		The slot (usually mesh element index) where the Section is located on the component @param Section		The Section being used @param bCanBeReplced	Whether or not the Section can be replaced by a user

#### struct `FSectionListItem`  
`struct FSectionListItem`  
_L777-854_
- desc: A Section item in a Section list slot
- L780 _public member_ `int32 LodIndex;` — LodIndex of the Section
- L782 _public member_ `int32 SectionIndex;` — Section index
- L785 _public member_ `bool IsSectionUsingCloth;` — Is this section is using cloth
- L788 _public member_ `int32 ThumbnailSize;` — Size of the preview material thumbnail
- L791 _public member_ `TWeakObjectPtr<UMaterialInterface> Material;` — Material being readonly view in the list
- L794 _public member_ `FName MaterialSlotName;` — Material Slot Name
- L795 _public member_ `int32 MaterialSlotIndex;`
- L796 _public member_ `FName OriginalMaterialSlotName;`
- L799 _public member_ `TMap<int32, FName> AvailableMaterialSlotName;` — Available material slot name
- L801 _public member_ `bool bIsChunkSection;`
- L802 _public member_ `int32 DefaultMaterialIndex;`
- L805 _public function_ `FSectionListItem(int32 InLodIndex, int32 InSectionIndex, FName InMaterialSlotName, int32 InMaterialSlotIndex, FName InOriginalMaterialSlotName, const TMap<int32, FName> &InAvailableMaterialSlotName, const UMaterialInterface* InMaterial, bool InIsSectionUsingCloth, int32 InThumbnailSize, bool InIsChunkSection, int32 InDefaultMaterialIndex) : LodIndex(InLodIndex) , SectionIndex(InSectionIndex) , IsSectionUsingCloth(InIsSectionUsingCloth) , ThumbnailSize(InThumbnailSize) , Material(const_cast<UMaterialInterface*>(InMaterial)) , MaterialSlotName(InMaterialSlotName) , MaterialSlotIndex(InMaterialSlotIndex) , OriginalMaterialSlotName(InOriginalMaterialSlotName) , AvailableMaterialSlotName(InAvailableMaterialSlotName) , bIsChunkSection(InIsChunkSection) , DefaultMaterialIndex(InDefaultMaterialIndex)`
- L819 _public function_ `bool operator==(const FSectionListItem& Other) const`
- L850 _public function_ `bool operator!=(const FSectionListItem& Other) const`

#### class `FSectionList`  
`class FSectionList : public IDetailCustomNodeBuilder, public TSharedFromThis<FSectionList>`  
_L857-931_
- inherits: `IDetailCustomNodeBuilder,TSharedFromThis<FSectionList>`
- L860 _public prototype_ `FSectionList(IDetailLayoutBuilder& InDetailLayoutBuilder, FSectionListDelegates& SectionListDelegates, bool bInInitiallyCollapsed, int32 InThumbnailSize, int32 InSectionsLodIndex, FName InSectionListName);`
- L865 _public function_ `bool IsDisplayingSections() const` — @return true if Sections are being displayed
- L870 _private prototype_ `void OnDisplaySectionsForLod(int32 LodIndex);` — Called when a user expands all materials in a slot
- L875 _private prototype_ `void OnHideSectionsForLod(int32 LodIndex);` — Called when a user hides all materials in a slot
- L878 _private function_ `virtual void SetOnRebuildChildren(FSimpleDelegate InOnRebuildChildren) override` — IDetailCustomNodeBuilder interface
- L879 _private function_ `virtual bool RequiresTick() const override`
- L880 _private prototype_ `virtual void Tick(float DeltaTime) override;`
- L881 _private prototype_ `virtual void GenerateHeaderRowContent(FDetailWidgetRow& NodeRow) override;`
- L882 _private prototype_ `virtual void GenerateChildContent(IDetailChildrenBuilder& ChildrenBuilder) override;`
- L883 _private function_ `virtual FName GetName() const override`
- L884 _private function_ `virtual bool InitiallyCollapsed() const override`
- L897 _private prototype_ `void AddSectionItem(class FDetailWidgetRow& Row, int32 LodIndex, const struct FSectionListItem& Item, bool bDisplayLink);` — Adds a new Section item to the list @param Row			The row to add the item to @param LodIndex		The Lod of the section @param Item			The Section item to add @param bDisplayLink	If a link to the Section should be displayed instead of the actual item (for multiple Sections)
- L900 _private prototype_ `bool OnCanCopySectionList() const;`
- L901 _private prototype_ `void OnCopySectionList();`
- L902 _private prototype_ `void OnPasteSectionList();`
- L904 _private prototype_ `bool OnCanCopySectionItem(int32 LODIndex, int32 SectionIndex) const;`
- L905 _private prototype_ `void OnCopySectionItem(int32 LODIndex, int32 SectionIndex);`
- L906 _private prototype_ `void OnPasteSectionItem(int32 LODIndex, int32 SectionIndex);`
- L907 _private prototype_ `void OnEnableSectionItem(int32 LodIndex, int32 SectionIndex, bool bEnable);`
- L910 _private member_ `FSectionListDelegates SectionListDelegates;` — Delegates for the Section list
- L912 _private member_ `FSimpleDelegate OnRebuildChildren;` — Called to rebuild the children of the detail tree
- L914 _private member_ `IDetailLayoutBuilder& DetailLayoutBuilder;` — Parent detail layout this list is in
- L916 _private member_ `TArray< FSectionListItem > DisplayedSections;` — Set of all unique displayed Sections
- L918 _private member_ `TArray< TSharedRef<class FSectionItemView> > ViewedSections;` — Set of all Sections currently in view (may be less than DisplayedSections)
- L920 _private member_ `TSet<uint32> ExpandedSlots;` — Set of all expanded slots
- L922 _private member_ `TSharedRef<class FSectionListBuilder> SectionListBuilder;` — Section list builder used to generate Sections
- L925 _private member_ `bool bInitiallyCollapsed;` — Set the initial state of the collapse.
- L927 _private member_ `FName SectionListName;`
- L929 _private member_ `int32 ThumbnailSize;`
- L930 _private member_ `int32 SectionsLodIndex;`

#### Free symbols / members of external scopes

- L45 _delegate_ `DECLARE_DELEGATE_OneParam(FOnAssetSelected, const FAssetData& );`
- L45 _prototype_ `DECLARE_DELEGATE_OneParam(FOnAssetSelected, const FAssetData& );`
- L46 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnShouldSetAsset, const FAssetData& );`
- L46 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnShouldSetAsset, const FAssetData& );`
- L47 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnShouldFilterAsset, const FAssetData& );`
- L47 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnShouldFilterAsset, const FAssetData& );`
- L48 _delegate_ `DECLARE_DELEGATE_OneParam(FOnComponentSelected, const UActorComponent* );`
- L48 _prototype_ `DECLARE_DELEGATE_OneParam(FOnComponentSelected, const UActorComponent* );`
- L49 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnShouldFilterComponent, const UActorComponent* );`
- L49 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnShouldFilterComponent, const UActorComponent* );`
- L50 _delegate_ `DECLARE_DELEGATE_OneParam( FOnGetActorFilters, TSharedPtr<FSceneOutlinerFilters>& );`
- L50 _prototype_ `DECLARE_DELEGATE_OneParam( FOnGetActorFilters, TSharedPtr<FSceneOutlinerFilters>& );`
- L51 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnGetPropertyComboBoxStrings, TArray< TSharedPtr<FString> >&, TArray<TSharedPtr<SToolTip>>&, TArray<bool>&);`
- L51 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnGetPropertyComboBoxStrings, TArray< TSharedPtr<FString> >&, TArray<TSharedPtr<SToolTip>>&, TArray<bool>&);`
- L52 _delegate_ `DECLARE_DELEGATE_RetVal(FString, FOnGetPropertyComboBoxValue);`
- L52 _prototype_ `DECLARE_DELEGATE_RetVal(FString, FOnGetPropertyComboBoxValue);`
- L53 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPropertyComboBoxValueSelected, const FString&);`
- L53 _prototype_ `DECLARE_DELEGATE_OneParam(FOnPropertyComboBoxValueSelected, const FString&);`
- L54 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnInstancedPropertyIteration, IDetailCategoryBuilder&, IDetailGroup*, TSharedRef<IPropertyHandle>&);`
- L54 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnInstancedPropertyIteration, IDetailCategoryBuilder&, IDetailGroup*, TSharedRef<IPropertyHandle>&);`
- L55 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FOnIsEnabled);`
- L55 _prototype_ `DECLARE_DELEGATE_RetVal(bool, FOnIsEnabled);`
- L56 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnSetOptional, FProperty*, const UClass*);`
- L56 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnSetOptional, FProperty*, const UClass*);`
- L154 _namespace_ `namespace PropertyCustomizationHelpers`
- L156 _prototype_ `TSharedRef<SWidget> MakeCustomButton(const FSlateBrush* IconBrush, FSimpleDelegate OnClicked, TAttribute<FText> ToolTipText = FText(), TAttribute<bool> IsEnabled = true, TAttribute<EVisibility> IsVisible = EVisibility::Visible);` (scope `PropertyCustomizationHelpers`)
- L157 _prototype_ `TSharedRef<SWidget> MakeResetButton(FSimpleDelegate OnResetClicked, TAttribute<FText> OptionalToolTipText = FText(), TAttribute<bool> IsEnabled = true);` (scope `PropertyCustomizationHelpers`)
- L158 _prototype_ `TSharedRef<SWidget> MakeAddButton( FSimpleDelegate OnAddClicked, TAttribute<FText> OptionalToolTipText = FText(), TAttribute<bool> IsEnabled = true );` (scope `PropertyCustomizationHelpers`)
- L159 _prototype_ `TSharedRef<SWidget> MakeRemoveButton( FSimpleDelegate OnRemoveClicked, TAttribute<FText> OptionalToolTipText = FText(), TAttribute<bool> IsEnabled = true );` (scope `PropertyCustomizationHelpers`)
- L160 _prototype_ `TSharedRef<SWidget> MakeEditButton( FSimpleDelegate OnEditClicked, TAttribute<FText> OptionalToolTipText = FText(), TAttribute<bool> IsEnabled = true );` (scope `PropertyCustomizationHelpers`)
- L161 _prototype_ `TSharedRef<SWidget> MakeEmptyButton( FSimpleDelegate OnEmptyClicked, TAttribute<FText> OptionalToolTipText = FText(), TAttribute<bool> IsEnabled = true );` (scope `PropertyCustomizationHelpers`)
- L162 _prototype_ `TSharedRef<SWidget> MakeInsertDeleteDuplicateButton( FExecuteAction OnInsertClicked, FExecuteAction OnDeleteClicked, FExecuteAction OnDuplicateClicked );` (scope `PropertyCustomizationHelpers`)
- L163 _prototype_ `TSharedRef<SWidget> MakeDeleteButton( FSimpleDelegate OnDeleteClicked, TAttribute<FText> OptionalToolTipText = FText(), TAttribute<bool> IsEnabled = true );` (scope `PropertyCustomizationHelpers`)
- L164 _prototype_ `TSharedRef<SWidget> MakeClearButton( FSimpleDelegate OnClearClicked, TAttribute<FText> OptionalToolTipText = FText(), TAttribute<bool> IsEnabled = true );` (scope `PropertyCustomizationHelpers`)
- L165 _prototype_ `TSharedRef<SWidget> MakeVisibilityButton(FOnClicked OnVisibilityClicked, TAttribute<FText> OptionalToolTipText = FText(), TAttribute<bool> VisibilityDelegate = true);` (scope `PropertyCustomizationHelpers`)
- L166 _prototype_ `TSharedRef<SWidget> MakeNewBlueprintButton( FSimpleDelegate OnNewBlueprintClicked, TAttribute<FText> OptionalToolTipText = FText(), TAttribute<bool> IsEnabled = true );` (scope `PropertyCustomizationHelpers`)
- L167 _prototype_ `TSharedRef<SWidget> MakeUseSelectedButton( FSimpleDelegate OnUseSelectedClicked, TAttribute<FText> OptionalToolTipText = FText(), TAttribute<bool> IsEnabled = true, const bool IsActor = false );` (scope `PropertyCustomizationHelpers`)
- L168 _prototype_ `TSharedRef<SWidget> MakeBrowseButton( FSimpleDelegate OnFindClicked, TAttribute<FText> OptionalToolTipText = FText(), TAttribute<bool> IsEnabled = true, const bool IsActor = false, const TAttribute<const FSlateBrush*>& InIconOverride = TAttribute<const FSlateBrush*>());` (scope `PropertyCustomizationHelpers`)
- L169 _prototype_ `TSharedRef<SWidget> MakeAssetPickerAnchorButton( FOnGetAllowedClasses OnGetAllowedClasses, FOnAssetSelected OnAssetSelectedFromPicker, const TSharedPtr<IPropertyHandle>& PropertyHandle = TSharedPtr<IPropertyHandle>());` (scope `PropertyCustomizationHelpers`)
- L170 _prototype_ `TSharedRef<SWidget> MakeAssetPickerWithMenu( const FAssetData& InitialObject, const bool AllowClear, const TArray<const UClass*>& AllowedClasses, const TArray<UFactory*>& NewAssetFactories, FOnShouldFilterAsset OnShouldFilterAsset, FOnAssetSelected OnSet, FSimpleDelegate OnClose, const TSharedPtr<IPropertyHandle>& PropertyHandle = TSharedPtr<IPropertyHandle>(), const TArray<FAssetData>& OwnerAssetArray = TArray<FAssetData>());` (scope `PropertyCustomizationHelpers`)
- L171 _prototype_ `TSharedRef<SWidget> MakeAssetPickerWithMenu( const FAssetData& InitialObject, const bool AllowClear, const TArray<const UClass*>& AllowedClasses, const TArray<const UClass*>& DisallowedClasses, const TArray<UFactory*>& NewAssetFactories, FOnShouldFilterAsset OnShouldFilterAsset, FOnAssetSelected OnSet, FSimpleDelegate OnClose, const TSharedPtr<IPropertyHandle>& PropertyHandle = TSharedPtr<IPropertyHandle>(), const TArray<FAssetData>& OwnerAssetArray = TArray<FAssetData>());` (scope `PropertyCustomizationHelpers`)
- L172 _prototype_ `TSharedRef<SWidget> MakeAssetPickerWithMenu( const FAssetData& InitialObject, const bool AllowClear, const bool AllowCopyPaste, const TArray<const UClass*>& AllowedClasses, const TArray<UFactory*>& NewAssetFactories, FOnShouldFilterAsset OnShouldFilterAsset, FOnAssetSelected OnSet, FSimpleDelegate OnClose, const TSharedPtr<IPropertyHandle>& PropertyHandle = TSharedPtr<IPropertyHandle>(), const TArray<FAssetData>& OwnerAssetArray = TArray<FAssetData>());` (scope `PropertyCustomizationHelpers`)
- L173 _prototype_ `TSharedRef<SWidget> MakeAssetPickerWithMenu( const FAssetData& InitialObject, const bool AllowClear, const bool AllowCopyPaste, const TArray<const UClass*>& AllowedClasses, const TArray<const UClass*>& DisallowedClasses, const TArray<UFactory*>& NewAssetFactories, FOnShouldFilterAsset OnShouldFilterAsset, FOnAssetSelected OnSet, FSimpleDelegate OnClose, const TSharedPtr<IPropertyHandle>& PropertyHandle = TSharedPtr<IPropertyHandle>(), const TArray<FAssetData>& OwnerAssetArray = TArray<FAssetData>());` (scope `PropertyCustomizationHelpers`)
- L174 _prototype_ `TSharedRef<SWidget> MakeActorPickerAnchorButton( FOnGetActorFilters OnGetActorFilters, FOnActorSelected OnActorSelectedFromPicker );` (scope `PropertyCustomizationHelpers`)
- L175 _prototype_ `TSharedRef<SWidget> MakeActorPickerWithMenu( AActor* const InitialActor, const bool AllowClear, FOnShouldFilterActor ActorFilter, FOnActorSelected OnSet, FSimpleDelegate OnClose, FSimpleDelegate OnUseSelected );` (scope `PropertyCustomizationHelpers`)
- L176 _prototype_ `TSharedRef<SWidget> MakeActorPickerWithMenu(AActor* const InitialActor, const bool AllowClear, const bool AllowPickingLevelInstanceContent, FOnShouldFilterActor ActorFilter, FOnActorSelected OnSet, FSimpleDelegate OnClose, FSimpleDelegate OnUseSelected, bool bDisplayUseSelected=true, bool bShowTransient=false);` (scope `PropertyCustomizationHelpers`)
- L177 _prototype_ `TSharedRef<SWidget> MakeComponentPickerWithMenu( UActorComponent* const InitialComponent, const bool AllowClear, FOnShouldFilterActor ActorFilter, FOnShouldFilterComponent ComponentFilter, FOnComponentSelected OnSet, FSimpleDelegate OnClose, UWorld* PickerWorld = nullptr, bool bShowTransient = false);` (scope `PropertyCustomizationHelpers`)
- L178 _prototype_ `TSharedRef<SWidget> MakeInteractiveActorPicker(FOnGetAllowedClasses OnGetAllowedClasses, FOnShouldFilterActor OnShouldFilterActor, FOnActorSelected OnActorSelectedFromPicker);` (scope `PropertyCustomizationHelpers`)
- L179 _prototype_ `TSharedRef<SWidget> MakeSceneDepthPicker(FOnSceneDepthLocationSelected OnSceneDepthLocationSelected);` (scope `PropertyCustomizationHelpers`)
- L180 _prototype_ `TSharedRef<SWidget> MakeEditConfigHierarchyButton(FSimpleDelegate OnEditConfigClicked, TAttribute<FText> OptionalToolTipText = FText(), TAttribute<bool> IsEnabled = true);` (scope `PropertyCustomizationHelpers`)
- L181 _prototype_ `TSharedRef<SWidget> MakeDocumentationButton(const TSharedRef<FPropertyEditor>& InPropertyEditor);` (scope `PropertyCustomizationHelpers`)
- L182 _prototype_ `TSharedRef<SWidget> MakeSaveButton(FSimpleDelegate OnSaveClicked, TAttribute<FText> OptionalToolTipText = FText(), TAttribute<bool> IsEnabled = true);` (scope `PropertyCustomizationHelpers`)
- L183 _prototype_ `TSharedRef<SWidget> MakeSetOptionalButton(FOnSetOptional OnSetOptional, TAttribute<FText> OptionalToolTipText = FText(), TAttribute<bool> IsEnabled = true);` (scope `PropertyCustomizationHelpers`)
- L184 _prototype_ `TSharedRef<SWidget> MakePickOptionalButton(FOnSetOptional OnSetOptional, FSimpleDelegate OnClearOptional, const TSharedRef<FPropertyNode>& PropertyNode, TAttribute<FText> OptionalToolTipText = FText(), TAttribute<bool> IsEnabled = true);` (scope `PropertyCustomizationHelpers`)
- L185 _prototype_ `TSharedRef<SWidget> MakeClearOptionalButton(FSimpleDelegate OnClearOptional, TAttribute<FText> OptionalToolTipText = FText(), TAttribute<bool> IsEnabled = true);` (scope `PropertyCustomizationHelpers`)
- L186 _prototype_ `TSharedRef<SWidget> MakeFunctionCallButton(const FPropertyFunctionCallArgs& InArgs);` (scope `PropertyCustomizationHelpers`)
- L187 _prototype_ `void AddFunctionCallWidgets(IDetailGroup& RootGroup, const TArrayView<UFunction*>& InCallInEditorFunctions, const FPropertyFunctionCallDelegates& InArgs);` (scope `PropertyCustomizationHelpers`)
- L188 _prototype_ `void AddFunctionCallWidgets(IDetailLayoutBuilder& DetailBuilder, const TArrayView<UFunction*>& InCallInEditorFunctions, const FPropertyFunctionCallDelegates& InArgs);` (scope `PropertyCustomizationHelpers`)
- L189 _prototype_ `void AddCallInEditorFunctionCallWidgetsForClass(IDetailGroup& RootGroup, const UClass* Class, const FPropertyFunctionCallDelegates& InArgs);` (scope `PropertyCustomizationHelpers`)
- L190 _prototype_ `void AddCallInEditorFunctionCallWidgetsForClass(IDetailLayoutBuilder& DetailBuilder, const UClass* Class, const FPropertyFunctionCallDelegates& InArgs);` (scope `PropertyCustomizationHelpers`)
- L193 _prototype_ `FBoolProperty* GetEditConditionProperty(const FProperty* InProperty, bool& bNegate);` (scope `PropertyCustomizationHelpers`) — @return the FBoolProperty edit condition property if one exists.
- L196 _prototype_ `TArray<UFactory*> GetNewAssetFactoriesForClasses(const TArray<const UClass*>& Classes);` (scope `PropertyCustomizationHelpers`) — Returns a list of factories which can be used to create new assets, based on the supplied class
- L199 _prototype_ `TArray<UFactory*> GetNewAssetFactoriesForClasses(const TArray<const UClass*>& Classes, const TArray<const UClass*>& DisallowedClasses);` (scope `PropertyCustomizationHelpers`) — Returns a list of factories which can be used to create new assets, based on the supplied classes and respecting the disallowed set
- L206 _prototype_ `TSharedRef<SWidget> MakePropertyComboBox(const FPropertyComboBoxArgs& InArgs);` (scope `PropertyCustomizationHelpers`) — Build a combo button that you bind to a Name/String/Enum property or display using general delegates, using an arguments structure @param InArgs Options used to create combo box
- L216 _prototype_ `TSharedRef<SWidget> MakePropertyComboBox(const TSharedPtr<IPropertyHandle>& InPropertyHandle, FOnGetPropertyComboBoxStrings OnGetStrings = FOnGetPropertyComboBoxStrings(), FOnGetPropertyComboBoxValue OnGetValue = FOnGetPropertyComboBoxValue(), FOnPropertyComboBoxValueSelected OnValueSelected = FOnPropertyComboBoxValueSelected());` (scope `PropertyCustomizationHelpers`) — Build a combo button that you bind to a Name/String/Enum property or display using general delegates @param InPropertyHandle	If set, will bind to a specific property. If this is null, all 3 delegates must be set @param OnGetStrings		Delegate that will generate the list of possible strings. If not set will generate using property handle @param OnGetValue		Delegate that is called to get the current string value to display. If not set will generate using property handle @param OnValueSelected	Delegate called when a string is selected. If not set will set the property handle
- L226 _prototype_ `void MakeInstancedPropertyCustomUI(TMap<FName, IDetailGroup*>& ExistingGroup, IDetailCategoryBuilder& BaseCategory, TSharedRef<IPropertyHandle>& BaseProperty, FOnInstancedPropertyIteration AddRowDelegate);` (scope `PropertyCustomizationHelpers`) — Loops through all of an instanced object property's child properties and call AddRowDelegate on properties that needs to be added to the UI to let us customize it. @param ExistingGroup  A map used internally to determine the existing group categories. Should be empty. @param BaseCategory   The category that will be used as the root of the instanced object properties. @param BaseProperty   The instanced class property. @param AddRowDelegate The delegate that will be called on each child property.
- L232 _prototype_ `TArray<const UClass*> GetClassesFromMetadataString(const FString& MetadataString);` (scope `PropertyCustomizationHelpers`) — Parse and load the given metadata string into a list of allowed classes. The metadata string is likely from something like AllowedClasses or DisallowedClasses.
- L238 _prototype_ `TArray<const UScriptStruct*> GetStructsFromMetadataString(const FString& MetadataString);` (scope `PropertyCustomizationHelpers`) — Parse and load the given metadata string into a list of allowed structs. The metadata string is likely from something like AllowedClasses or DisallowedClasses.
- L243 _prototype_ `void GetCallInEditorFunctionsForClass(const UClass* InClass, TArray<UFunction*>& OutCallInEditorFunctions, EFieldIterationFlags InIterationFlags = EFieldIterationFlags::IncludeSuper);` (scope `PropertyCustomizationHelpers`)
- L248 _prototype_ `void GetCallInEditorFunctionsForClass(const UClass* InClass, const TFunctionRef<bool(const UFunction*)>& InFunctionFilter, TArray<UFunction*>& OutCallInEditorFunctions, EFieldIterationFlags InIterationFlags = EFieldIterationFlags::IncludeSuper);` (scope `PropertyCustomizationHelpers`) — @param InFunctionFilter	A filter to select candidate UFunctions
- L253 _prototype_ `TSharedRef<SWidget> MakeEditInlineObjectClassPicker(TSharedRef<IPropertyHandle> PropertyHandle, FOnClassPicked OnClassPicked, TSharedPtr<IClassViewerFilter> AdditionalClassFilter=nullptr);` (scope `PropertyCustomizationHelpers`) — Makes a class picker widget for the given instanced editinline UObject property handle. Shares code with SPropertyEditorInline, but doesn't create a combo button, just the class picker.
- L258 _prototype_ `void CreateNewInstanceOfEditInlineObjectClass(TSharedRef<IPropertyHandle> PropertyHandle, UClass* Class, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags);` (scope `PropertyCustomizationHelpers`) — Creates a new instance of the given object class inside the given property handle, mimicking what the SPropertyEditorEditInline widget does on class selection
- L264 _delegate_ `DECLARE_DELEGATE_RetVal( const UObject*, FOnGetObject );` — Delegate used to get a generic object
- L264 _prototype_ `DECLARE_DELEGATE_RetVal( const UObject*, FOnGetObject );` — Delegate used to get a generic object
- L267 _delegate_ `DECLARE_DELEGATE_OneParam( FOnSetObject, const FAssetData& );` — Delegate used to set a generic object
- L267 _prototype_ `DECLARE_DELEGATE_OneParam( FOnSetObject, const FAssetData& );` — Delegate used to set a generic object
- L373 _delegate_ `DECLARE_DELEGATE_OneParam( FOnSetClass, const UClass* );` — Delegate used to set a class
- L373 _prototype_ `DECLARE_DELEGATE_OneParam( FOnSetClass, const UClass* );` — Delegate used to set a class
- L430 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSetStruct, const UScriptStruct*);` — Delegate used to set a struct
- L430 _prototype_ `DECLARE_DELEGATE_OneParam(FOnSetStruct, const UScriptStruct*);` — Delegate used to set a struct
- L479 _delegate_ `DECLARE_DELEGATE( FOnPropertyValueChanged );`
- L526 _delegate_ `DECLARE_DELEGATE_ThreeParams( FOnGenerateArrayElementWidget, TSharedRef<IPropertyHandle>, int32, IDetailChildrenBuilder& );`
- L526 _prototype_ `DECLARE_DELEGATE_ThreeParams( FOnGenerateArrayElementWidget, TSharedRef<IPropertyHandle>, int32, IDetailChildrenBuilder& );`
- L696 _delegate_ `DECLARE_DELEGATE_OneParam(FOnGetSections, class ISectionListBuilder&);` — Delegate called when we need to get new sections for the list
- L696 _prototype_ `DECLARE_DELEGATE_OneParam(FOnGetSections, class ISectionListBuilder&);` — Delegate called when we need to get new sections for the list
- L701 _delegate_ `DECLARE_DELEGATE_FourParams(FOnSectionChanged, int32, int32, int32, FName);` — Delegate called when a user changes the Section
- L701 _prototype_ `DECLARE_DELEGATE_FourParams(FOnSectionChanged, int32, int32, int32, FName);` — Delegate called when a user changes the Section
- L703 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef<SWidget>, FOnGenerateWidgetsForSection, int32, int32);`
- L703 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef<SWidget>, FOnGenerateWidgetsForSection, int32, int32);`
- L705 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnResetSectionToDefaultClicked, int32, int32);`
- L705 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnResetSectionToDefaultClicked, int32, int32);`
- L707 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SWidget>, FOnGenerateLODComboBox, int32);`
- L707 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SWidget>, FOnGenerateLODComboBox, int32);`
- L709 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FOnCanCopySectionList);`
- L709 _prototype_ `DECLARE_DELEGATE_RetVal(bool, FOnCanCopySectionList);`
- L710 _delegate_ `DECLARE_DELEGATE(FOnCopySectionList);`
- L710 _prototype_ `DECLARE_DELEGATE(FOnCopySectionList);`
- L711 _delegate_ `DECLARE_DELEGATE(FOnPasteSectionList);`
- L711 _prototype_ `DECLARE_DELEGATE(FOnPasteSectionList);`
- L713 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnCanCopySectionItem, int32, int32);`
- L713 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnCanCopySectionItem, int32, int32);`
- L714 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnCopySectionItem, int32, int32);`
- L714 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnCopySectionItem, int32, int32);`
- L715 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnPasteSectionItem, int32, int32);`
- L715 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnPasteSectionItem, int32, int32);`
- L716 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnEnableSectionItem, int32, int32, bool);`
- L716 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnEnableSectionItem, int32, int32, bool);`

### `Source/Editor/PropertyEditor/Public/PropertyEditing.h` (Public)
_(no declarations extracted)_

### `Source/Editor/PropertyEditor/Public/PropertyEditorArchetypePolicy.h` (Public)


#### class `PropertyEditorPolicy::IArchetypePolicy`  
`class IArchetypePolicy`  
_L9-13_
- L12 _public prototype_ `virtual UObject* GetArchetypeForObject(const UObject* Object) const = 0;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace PropertyEditorPolicy`
- L15 _prototype_ `UObject* GetArchetype(const UObject* Object);` (scope `PropertyEditorPolicy`)
- L16 _prototype_ `void RegisterArchetypePolicy(IArchetypePolicy* Policy);` (scope `PropertyEditorPolicy`)
- L17 _prototype_ `void UnregisterArchetypePolicy(IArchetypePolicy* Policy);` (scope `PropertyEditorPolicy`)

### `Source/Editor/PropertyEditor/Public/PropertyEditorClipboard.h` (Public)


#### class `FPropertyEditorClipboard`  
`class FPropertyEditorClipboard`  
_L19-48_
- desc: Specializes clipboard handling to allow tagged entries, where you can partition the clipboard contents and look them up by tag (name). The clipboard is persisted using both the Platform implementation, and as a stored virtual clipboard.
- L23 _public prototype_ `static void ClipboardCopy(const TCHAR* Str);` — Perform a copy.
- L26 _public prototype_ `static void ClipboardCopy(const TCHAR* Str, FName Tag);` — Perform a copy, optionally specifying the tag.
- L29 _public prototype_ `static void ClipboardCopy(TUniqueFunction<void(TMap<FName, FString>&)>&& TagMappingFunc);` — Perform a copy, supplying a function that maps the result to multiple tags.
- L32 _public prototype_ `static void ClipboardAppend(TUniqueFunction<void(TMap<FName, FString>&)>&& TagMappingFunc);` — Append the given values to the current clipboard entry. If none exists, it will create it.
- L35 _public prototype_ `static bool ClipboardPaste(FString& Dest);` — Gets the clipboard contents.
- L41 _public prototype_ `static bool ClipboardPaste(FString& Dest, FName Tag);` — Will return true if the tag is specified and exists. If the tag doesn't exist, Dest will be populated with the untagged clipboard contents.
- L44 _private prototype_ `static TSharedRef<FPropertyEditorClipboard> Get();`
- L47 _private member_ `TMap<FName, FString> ClipboardContents;` — Item per-tag, cleared when a new copy operation occurs.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API PROPERTYEDITOR_API`

### `Source/Editor/PropertyEditor/Public/PropertyEditorCommands.h` (Public)


#### class `FPropertyEditorCommands`  
`class FPropertyEditorCommands : public TCommands<FPropertyEditorCommands>`  
_L10-21_
- inherits: `TCommands<FPropertyEditorCommands>`
- L13 _public prototype_ `FPropertyEditorCommands();`
- L16 _public prototype_ `virtual void RegisterCommands() override;`
- L19 _public member_ `TSharedPtr<FUICommandInfo> CollapseAll;`
- L20 _public member_ `TSharedPtr<FUICommandInfo> ExpandAll;`

### `Source/Editor/PropertyEditor/Public/PropertyEditorCopyPaste.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace PropertyEditor` (scope `UE`)
- L12 _prototype_ `[[nodiscard]] FString GetPropertyPath(const TSharedPtr<IPropertyHandle>& InPropertyHandle);` (scope `UE::PropertyEditor`) — Gets the property path from the provided PropertyHandle (if valid).
- L15 _prototype_ `[[nodiscard]] bool TagMatchesProperty(const FString& InTag, const TSharedPtr<IPropertyHandle>& InPropertyHandle);` (scope `UE::PropertyEditor`) — Returns true if the Tag is empty, or the specified property matches it.
- L20 _typedef_ `typedef TMulticastDelegate<void(const FString& InTag, const FString& InText, const TOptional<FGuid>& InOperationId)> FOnPasteFromText;` — Subscribe to and parse the string contents. Note that the caller is responsible for providing valid UE text, and the subscriber is responsible for applying it if applicable.
- L27 _typedef_ `typedef TMulticastDelegate<void(TSharedPtr<IPropertyHandle> InPropertyHandle, FString& OutPropertyText, const TOptional<FGuid>& InOperationId)> FOnCopyToText;` — Subscribe to and copy the property value to text. Optionally required when there is custom behavior needed on copy to match FOnPasteFromText, otherwise the default property handle copy will be used. Note that the caller is responsible for providing a valid property handle, and the subscriber is responsible for copying it to text if applicable. OutPropertyText should be left empty if the subscriber does not handle the given property.

### `Source/Editor/PropertyEditor/Public/PropertyEditorDelegates.h` (Public)


#### struct `FPropertyAndParent`  
`struct FPropertyAndParent`  
_L34-59_
- L36 _public prototype_ `explicit FPropertyAndParent(const TSharedRef<IPropertyHandle>& InPropertyHandle);`
- L37 _public prototype_ `explicit FPropertyAndParent(const TSharedRef<FPropertyNode>& InPropertyNode);`
- L40 _public member_ `const FProperty& Property;` — The property always exists
- L43 _public member_ `int32 ArrayIndex;` — The array index of this property if applicable, otherwise INDEX_NONE.
- L46 _public member_ `TArray< const FProperty* > ParentProperties;` — The entire chain of parent properties, all the way to the property root. ParentProperties[0] is the immediate parent.
- L52 _public member_ `TArray<int32> ParentArrayIndices;` — Array indices in parent properties where applicable, otherwise INDEX_NONE. The size of this array is always equal to the size of ParentProperties.
- L55 _public member_ `TArray< TWeakObjectPtr< UObject > > Objects;` — The objects for these properties
- L58 _private prototype_ `void Initialize(const TSharedRef<FPropertyNode>& InPropertyNode);`

#### struct `FOnGenerateGlobalRowExtensionArgs`  
`struct FOnGenerateGlobalRowExtensionArgs`  
_L131-147_
- desc: A property row extension arguments is displayed at the end of a property row, either inline or as a button.
- L134 _public member_ `TSharedPtr<IPropertyHandle> PropertyHandle;` — The detail row's property handle.
- L137 _public member_ `TWeakPtr<IDetailTreeNode> OwnerTreeNode;` — The detail row's owner tree node.
- L140 _public member_ `UObject* OwnerObject = nullptr;` — Owner object for the property extension
- L143 _public member_ `FString PropertyPath = TEXT("");` — Path of the exposed property
- L146 _public member_ `FProperty* Property = nullptr;` — Exposed property

#### struct `FPropertyRowExtensionButton`  
`struct FPropertyRowExtensionButton`  
_L153-163_
- desc: A property row extension button is displayed at the end of a property row, either inline as a button, or in a dropdown when not all buttons can fit.
- L156 _public member_ `TAttribute<FSlateIcon> Icon;` — The icon to display for the button.
- L158 _public member_ `TAttribute<FText> Label;` — The label to display for the button when shown in the dropdown.
- L160 _public member_ `TAttribute<FText> ToolTip;` — The tooltip to display for the button.
- L162 _public member_ `FUIAction UIAction;` — The UIAction to use for the button - this includes on execute, can execute and visibility handlers.

#### struct `FDetailLayoutCallback`  
`struct FDetailLayoutCallback`  
_L176-182_
- desc: Callback executed to query the custom layout of details
- L179 _public member_ `FOnGetDetailCustomizationInstance DetailLayoutDelegate;` — Delegate to call to query custom layout of details
- L181 _public member_ `int32 Order;` — The order of this class in the map of callbacks to send (callbacks sent in the order they are received)

#### struct `FPropertyTypeLayoutCallback`  
`struct FPropertyTypeLayoutCallback`  
_L184-193_
- L186 _public member_ `FOnGetPropertyTypeCustomizationInstance PropertyTypeLayoutDelegate;`
- L188 _public member_ `TSharedPtr<IPropertyTypeIdentifier> PropertyTypeIdentifier;`
- L190 _public function_ `bool IsValid() const`
- L192 _public prototype_ `TSharedRef<IPropertyTypeCustomization> GetCustomizationInstance() const;`

#### struct `FPropertyTypeLayoutCallbackList`  
`struct FPropertyTypeLayoutCallbackList`  
_L196-209_
- L199 _public member_ `FPropertyTypeLayoutCallback BaseCallback;` — The base callback is a registered callback with a null identifier
- L202 _public member_ `TArray< FPropertyTypeLayoutCallback > IdentifierList;` — List of registered callbacks with a non null identifier
- L204 _public prototype_ `void Add(const FPropertyTypeLayoutCallback& NewCallback);`
- L206 _public prototype_ `void Remove(const TSharedPtr<IPropertyTypeIdentifier>& InIdentifier);`
- L208 _public prototype_ `const FPropertyTypeLayoutCallback& Find(const IPropertyHandle& PropertyHandle) const;`

#### Free symbols / members of external scopes

- L62 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsPropertyVisible, const FPropertyAndParent&);` — Delegate called to see if a property should be visible
- L62 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsPropertyVisible, const FPropertyAndParent&);` — Delegate called to see if a property should be visible
- L65 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsPropertyReadOnly, const FPropertyAndParent&);` — Delegate called to see if a property should be read-only
- L65 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsPropertyReadOnly, const FPropertyAndParent&);` — Delegate called to see if a property should be read-only
- L68 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FIsCustomRowVisible, FName , FName );` — Delegate called to determine if a custom row should be visible.
- L68 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FIsCustomRowVisible, FName , FName );` — Delegate called to determine if a custom row should be visible.
- L71 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FIsCustomRowReadOnly, FName , FName );` — Delegate called to determine if a custom row should be read-only.
- L71 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FIsCustomRowReadOnly, FName , FName );` — Delegate called to determine if a custom row should be read-only.
- L74 _delegate_ `DECLARE_DELEGATE_RetVal(TSharedRef<IDetailCustomization>, FOnGetDetailCustomizationInstance);` — Delegate called to get a detail layout for a specific object class
- L74 _prototype_ `DECLARE_DELEGATE_RetVal(TSharedRef<IDetailCustomization>, FOnGetDetailCustomizationInstance);` — Delegate called to get a detail layout for a specific object class
- L77 _delegate_ `DECLARE_DELEGATE_RetVal(TSharedRef<IPropertyTypeCustomization>, FOnGetPropertyTypeCustomizationInstance);` — Delegate called to get a property layout for a specific property type
- L77 _prototype_ `DECLARE_DELEGATE_RetVal(TSharedRef<IPropertyTypeCustomization>, FOnGetPropertyTypeCustomizationInstance);` — Delegate called to get a property layout for a specific property type
- L80 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnObjectArrayChanged, const FString&, const TArray<UObject*>&);` — Notification for when a property view changes
- L80 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnObjectArrayChanged, const FString&, const TArray<UObject*>&);` — Notification for when a property view changes
- L83 _delegate_ `DECLARE_DELEGATE(FOnDisplayedPropertiesChanged);` — Notification for when displayed properties changes (for instance, because the user has filtered some properties
- L83 _prototype_ `DECLARE_DELEGATE(FOnDisplayedPropertiesChanged);` — Notification for when displayed properties changes (for instance, because the user has filtered some properties
- L86 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPropertySelectionChanged, FProperty*) DECLARE_DELEGATE_OneParam(FOnPropertyDoubleClicked, FProperty*) DECLARE_DELEGATE_OneParam(FOnPropertyClicked, const TSharedPtr<FPropertyPath >&) DECLARE_DELEGATE_OneParam(FConstructExternalColumnHeaders, const TSharedRef< SHeaderRow >&) DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef< SWidget >, FConstructExternalColumnCell, const FName& , const TSharedRef< IPropertyTreeRow >& ) DECLARE_DELEGATE_RetVal(bool, FIsPropertyEditingEnabled);` — Notification for when a property selection changes.
- L86 _prototype_ `DECLARE_DELEGATE_OneParam(FOnPropertySelectionChanged, FProperty*) DECLARE_DELEGATE_OneParam(FOnPropertyDoubleClicked, FProperty*) DECLARE_DELEGATE_OneParam(FOnPropertyClicked, const TSharedPtr<FPropertyPath >&) DECLARE_DELEGATE_OneParam(FConstructExternalColumnHeaders, const TSharedRef< SHeaderRow >&) DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef< SWidget >, FConstructExternalColumnCell, const FName& , const TSharedRef< IPropertyTreeRow >& ) DECLARE_DELEGATE_RetVal(bool, FIsPropertyEditingEnabled);` — Notification for when a property selection changes.
- L89 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPropertyDoubleClicked, FProperty*) DECLARE_DELEGATE_OneParam(FOnPropertyClicked, const TSharedPtr<FPropertyPath >&) DECLARE_DELEGATE_OneParam(FConstructExternalColumnHeaders, const TSharedRef< SHeaderRow >&) DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef< SWidget >, FConstructExternalColumnCell, const FName& , const TSharedRef< IPropertyTreeRow >& ) DECLARE_DELEGATE_RetVal(bool, FIsPropertyEditingEnabled);` — Notification for when a property is double clicked by the user
- L92 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPropertyClicked, const TSharedPtr<FPropertyPath >&) DECLARE_DELEGATE_OneParam(FConstructExternalColumnHeaders, const TSharedRef< SHeaderRow >&) DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef< SWidget >, FConstructExternalColumnCell, const FName& , const TSharedRef< IPropertyTreeRow >& ) DECLARE_DELEGATE_RetVal(bool, FIsPropertyEditingEnabled);` — Notification for when a property is clicked by the user
- L95 _delegate_ `DECLARE_DELEGATE_OneParam(FConstructExternalColumnHeaders, const TSharedRef< SHeaderRow >&) DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef< SWidget >, FConstructExternalColumnCell, const FName& , const TSharedRef< IPropertyTreeRow >& ) DECLARE_DELEGATE_RetVal(bool, FIsPropertyEditingEnabled);`
- L97 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef< SWidget >, FConstructExternalColumnCell, const FName& , const TSharedRef< IPropertyTreeRow >& ) DECLARE_DELEGATE_RetVal(bool, FIsPropertyEditingEnabled);`
- L100 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FIsPropertyEditingEnabled);` — Delegate called to see if a property editing is enabled
- L103 _typedef_ `using FCanPropertyItemChangeRetType = TValueOrError<bool, FText>;` — Delegate to be called before a container item changes
- L104 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(FCanPropertyItemChangeRetType, FCanPropertyItemChange, EPropertyChangeType::Type, int32 );`
- L104 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(FCanPropertyItemChangeRetType, FCanPropertyItemChange, EPropertyChangeType::Type, int32 );`
- L107 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FPropertyChangeBlocked, const FProperty*, FText );` — Delegate to be called when a change is blocked on a property
- L107 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FPropertyChangeBlocked, const FProperty*, FText );` — Delegate to be called when a change is blocked on a property
- L113 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FName, FPropertyHandleLayoutOverride, const IPropertyHandle& Handle) DECLARE_MULTICAST_DELEGATE_OneParam(FOnFinishedChangingProperties, const FPropertyChangedEvent&);` — A delegate that returns the name of a type that is to be used to look up the layout callback instead of the property's type. Return None to not provide an override.
- L113 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FName, FPropertyHandleLayoutOverride, const IPropertyHandle& Handle) DECLARE_MULTICAST_DELEGATE_OneParam(FOnFinishedChangingProperties, const FPropertyChangedEvent&);` — A delegate that returns the name of a type that is to be used to look up the layout callback instead of the property's type. Return None to not provide an override.
- L120 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnFinishedChangingProperties, const FPropertyChangedEvent&);` — A delegate which is called after properties have been edited and PostEditChange has been called on all objects. This can be used to safely make changes to data that the details panel is observing instead of during PostEditChange (which is unsafe)
- L126 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnNotifyStartedChangingProperties, const FPropertyChangedEvent&);` — A delegate which is called before properties have been edited and PreEditChange has been called on all objects. This can be used to identify what precisely changed.
- L126 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnNotifyStartedChangingProperties, const FPropertyChangedEvent&);` — A delegate which is called before properties have been edited and PreEditChange has been called on all objects. This can be used to identify what precisely changed.
- L171 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGenerateGlobalRowExtension, const FOnGenerateGlobalRowExtensionArgs& , TArray<FPropertyRowExtensionButton>& );` — Delegate called to get add an extension to a property row's name column. To use, bind an handler to the delegate that adds an extension to the out array parameter. When called, EWidgetPosition indicates the position for which the delegate is gathering extensions. ie. The favorite system is implemented by adding the star widget when the delegate is called with the left position.
- L171 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGenerateGlobalRowExtension, const FOnGenerateGlobalRowExtensionArgs& , TArray<FPropertyRowExtensionButton>& );` — Delegate called to get add an extension to a property row's name column. To use, bind an handler to the delegate that adds an extension to the out array parameter. When called, EWidgetPosition indicates the position for which the delegate is gathering extensions. ie. The favorite system is implemented by adding the star widget when the delegate is called with the left position.
- L212 _typedef_ `typedef TMap< FName, FPropertyTypeLayoutCallbackList > FCustomPropertyTypeLayoutMap;` — This is a multimap as there many be more than one customization per property type

### `Source/Editor/PropertyEditor/Public/PropertyEditorEditConstPolicy.h` (Public)


#### class `PropertyEditorPolicy::IEditConstPolicy`  
`class IEditConstPolicy`  
_L12-17_
- L15 _public prototype_ `virtual bool CanEditProperty(const FEditPropertyChain& PropertyChain, const UObject* Object) const = 0;`
- L16 _public prototype_ `virtual bool CanEditProperty(const FProperty* Property, const UObject* Object) const = 0;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace PropertyEditorPolicy`
- L19 _prototype_ `bool IsPropertyEditConst(const FEditPropertyChain& PropertyChain, UObject* Object);` (scope `PropertyEditorPolicy`)
- L20 _prototype_ `bool IsPropertyEditConst(const FProperty* Property, UObject* Object);` (scope `PropertyEditorPolicy`)
- L21 _prototype_ `void RegisterEditConstPolicy(IEditConstPolicy* Policy);` (scope `PropertyEditorPolicy`)
- L22 _prototype_ `void UnregisterEditConstPolicy(IEditConstPolicy* Policy);` (scope `PropertyEditorPolicy`)

### `Source/Editor/PropertyEditor/Public/PropertyEditorModule.h` (Public)


#### enum `EPropertyNamePlacement::Type`  
`enum Type`  
_L38-48_
- L41 _public enumerator_ `Hidden` — Do not show the property name
- L43 _public enumerator_ `Left` — Show the property name to the left of the widget
- L45 _public enumerator_ `Right` — Show the property name to the right of the widget
- L47 _public enumerator_ `Inside` — Inside the property editor edit box (unused for properties that dont have edit boxes )

#### enum `FPropertyAccess::Result`  
`enum Result`  
_L57-65_
- L60 _public enumerator_ `MultipleValues` — Multiple values were found so the value could not be read
- L62 _public enumerator_ `Fail` — Failed to set or get the value
- L64 _public enumerator_ `Success` — Successfully set the got the value

#### class `IPropertyTypeIdentifier`  
`class IPropertyTypeIdentifier`  
_L83-94_
- desc: Base class for adding an extra data to identify a custom property type
- L86 _public prototype_ `virtual ~IPropertyTypeIdentifier() = default;`
- L93 _public prototype_ `virtual bool IsPropertyTypeCustomized( const IPropertyHandle& PropertyHandle ) const = 0;` — Called to identify if a property type is customized @param IPropertyHandle	Handle to the property being tested

#### struct `FStructureDetailsViewArgs`  
`struct FStructureDetailsViewArgs`  
_L102-123_
- desc: Struct used to control the visibility of properties in a Structure Detail View
- L104 _public function_ `FStructureDetailsViewArgs() : bShowObjects(false) , bShowAssets(true) , bShowClasses(true) , bShowInterfaces(false)`
- L113 _public member_ `bool bShowObjects : 1;` — True if we should show general object properties in the details view
- L116 _public member_ `bool bShowAssets : 1;` — True if we should show asset properties in the details view
- L119 _public member_ `bool bShowClasses : 1;` — True if we should show class properties in the details view
- L122 _public member_ `bool bShowInterfaces : 1;` — True if we should show interface properties in the details view

#### class `FPropertySection`  
`class FPropertySection`  
_L129-188_
- desc: A property section is a group of categories with a name, eg. "Rendering" might contain "Materials" and "Lighting". Categories may belong to zero or more sections.
- L138 _public function_ `FPropertySection(FName InName, FText InDisplayName, const int32 InOrder = 0) : Name(InName), DisplayName(InDisplayName), Order(InOrder)` — @param InName		The internal name of this section. @param InDisplayName	The localizable display name to show to the user. @param InOrder		The order in which this section should be displayed. Lower values are displayed first.
- L145 _public prototype_ `FPropertySection(const FPropertySection&) = default;`
- L146 _public prototype_ `virtual ~FPropertySection() = default;`
- L149 _public prototype_ `virtual void AddCategory(FName CategoryName);` — Add a category to this section.
- L152 _public prototype_ `virtual void RemoveCategory(FName CategoryName);` — Remove a category from this section.
- L155 _public prototype_ `virtual bool HasAddedCategory(FName CategoryName) const;` — Does this section add the given category?
- L158 _public prototype_ `virtual bool HasRemovedCategory(FName CategoryName) const;` — Does this section remove the given category?
- L161 _public function_ `virtual FName GetName() const` — Get the internal name of this property section.
- L164 _public function_ `virtual FText GetDisplayName() const` — Get the display name of this section.
- L167 _public function_ `virtual int32 GetOrder() const` — Get the (sort) order of this section, where the default is 0.
- L172 _private member_ `FName Name;` — The internal name to use for this section.
- L175 _private member_ `FText DisplayName;` — The display name to use for this section.
- L178 _private member_ `int32 Order = 0;` — The order in which this section should be displayed. Lower values are displayed first.
- L181 _private member_ `TSet<FName> AddedCategories;` — The set of categories that are added to this section.
- L187 _private member_ `TSet<FName> RemovedCategories;` — The set of categories that are removed from this section. This exists to allow users to prevent sections from being crowded when inheriting.

#### class `FClassSectionMapping`  
`class FClassSectionMapping`  
_L191-230_
- desc: A mapping of categories to section names for a given class.
- L194 _public prototype_ `FClassSectionMapping(FName ClassName);`
- L195 _public prototype_ `FClassSectionMapping(const FClassSectionMapping&) = default;`
- L200 _public prototype_ `TSharedPtr<FPropertySection> FindSection(FName SectionName) const;` — Find or add a section of the given name.
- L207 _public prototype_ `TSharedRef<FPropertySection> FindOrAddSection(FName SectionName, FText DisplayName, const int32 Order = 0);` — Find or add a section of the given name. Optionally, you can specify an order for the section to be displayed in. Lower values are displayed first. Note that the default "All" section will always be displayed last.
- L212 _public prototype_ `void RemoveSection(FName SectionName);` — Remove a section of the given name.
- L220 _public prototype_ `bool GetSectionsForCategory(FName CategoryName, TArray<TSharedPtr<FPropertySection>>& OutSections) const;` — Get the sections that the given category belongs to and append them to OutSections. @param CategoryName	The category name to search for. @param OutSections	The array to append any found sections. The array will not be cleared. @return				true if any sections were found, false otherwise.
- L226 _private member_ `FName ClassName;`
- L229 _private member_ `TMap<FName, TSharedPtr<FPropertySection>> DefinedSections;` — The sections defined for this class.

#### struct `FRegisterCustomClassLayoutParams`  
`struct FRegisterCustomClassLayoutParams`  
_L233-237_
- L236 _public member_ `TOptional<int32> OptionalOrder;` — Optional order to register this class layout with. Registration order is used when not specified. Lower values are added first

#### class `FPropertyEditorModule`  
`class FPropertyEditorModule : public IModuleInterface`  
_L239-532_
- inherits: `IModuleInterface`
- L245 _public prototype_ `virtual void StartupModule();` — Called right after the module has been loaded
- L250 _public prototype_ `virtual void ShutdownModule();` — Called by the module manager right before this module is unloaded
- L257 _public prototype_ `virtual void UpdatePropertyViews( const TArray<UObject*>& NewObjectList );` — Refreshes property windows with a new list of objects to view @param NewObjectList	The list of objects each property window should view
- L264 _public prototype_ `virtual void ReplaceViewedObjects( const TMap<UObject*, UObject*>& OldToNewObjectMap );` — Replaces objects being viewed by open property views with new objects @param OldToNewObjectMap	A mapping between object to replace and its replacement
- L271 _public prototype_ `virtual void RemoveDeletedObjects( TArray<UObject*>& DeletedObjects );` — Removes deleted objects from property views that are observing them @param DeletedObjects	The objects to delete
- L276 _public prototype_ `virtual bool HasUnlockedDetailViews() const;` — Returns true if there is an unlocked detail view
- L284 _public prototype_ `virtual void RegisterCustomClassLayout( FName ClassName, FOnGetDetailCustomizationInstance DetailLayoutDelegate, FRegisterCustomClassLayoutParams Params = FRegisterCustomClassLayoutParams());` — Registers a custom detail layout delegate for a specific class @param ClassName	The name of the class that the custom detail layout is for @param DetailLayoutDelegate	The delegate to call when querying for custom detail layouts for the classes properties
- L291 _public prototype_ `virtual void UnregisterCustomClassLayout( FName ClassName );` — Unregisters a custom detail layout delegate for a specific class name @param ClassName	The class name with the custom detail layout delegate to remove
- L301 _public prototype_ `virtual void RegisterCustomPropertyTypeLayout( FName PropertyTypeName, FOnGetPropertyTypeCustomizationInstance PropertyTypeLayoutDelegate, TSharedPtr<IPropertyTypeIdentifier> Identifier = nullptr);` — Registers a property type customization A property type is a specific FProperty type, a struct, instanced Object property, or enum type @param PropertyTypeName		The name of the property type to customize.  For structs and enums this is the name of the struct class or enum	(not StructProperty or ByteProperty) @param PropertyTypeLayoutDelegate	The delegate to call when querying for a custom layout of the property type @param Identifier			An identifier to use to differentiate between two customizations on the same type
- L309 _public prototype_ `virtual void UnregisterCustomPropertyTypeLayout( FName PropertyTypeName, TSharedPtr<IPropertyTypeIdentifier> InIdentifier = nullptr);` — Unregisters a custom detail layout for a property type @param PropertyTypeName 	The name of the property type that was registered @param Identifier 		An identifier to use to differentiate between two customizations on the same type
- L317 _public prototype_ `virtual FDelegateHandle RegisterPropertyHandleLayoutOverride(FName PropertyTypeName, const FPropertyHandleLayoutOverride& Delegate);` — Registers a property layout override callback @param PropertyTypeName Name of the property type (e.g. struct FName) to override @param Delegate The delegate to call when we're looking for a property handle's layout override
- L324 _public prototype_ `virtual void UnregisterPropertyHandleLayoutOverride(FDelegateHandle DelegateHandle);` — Unregisters a property layout override callback @param DelegateHandle The handle returned by RegisterPropertyHandleLayoutOverride
- L335 _public prototype_ `virtual TSharedRef<FPropertySection> FindOrCreateSection(FName ClassName, FName SectionName, FText DisplayName, const int32 Order = 0);` — Find an existing section or create a section for a class. @param ClassName		The class to add a section mapping for. @param SectionName	The section to find or create. @param DisplayName	The display name to use for the section. If the section already exists for this class, the display name will not be replaced. @param Order			The order in which this section should be displayed. Lower values are displayed first. The default "All" section will always be displayed last. @return				A new section, or the existing one.
- L342 _public prototype_ `virtual TArray<TSharedPtr<FPropertySection>> FindSectionsForCategory(const UStruct* Struct, FName CategoryName) const;` — Find the section that the given category in the given struct should be a part of. @param Struct		The struct to start searching from. Note: all super-structs of the given struct will also be searched. @param CategoryName	The category to search for.
- L349 _public prototype_ `virtual void GetAllSections(const UStruct* Struct, TArray<TSharedPtr<FPropertySection>>& OutSections) const;` — Get all registered sections for the given struct (including the default section). @param Struct		The struct to fetch sections for. @param OutSections	Sections will be appended to this parameter. The array will not be cleared beforehand.
- L356 _public prototype_ `virtual void RemoveSection(FName ClassName, FName SectionName);` — Remove a given section from the given class. @param ClassName		The class to remove the section from. @param SectionName	The section to remove.
- L362 _public prototype_ `virtual void NotifyCustomizationModuleChanged();` — Customization modules should call this when that module has been unloaded, loaded, etc... so the property module can clean up its data.  Needed to support dynamic reloading of modules
- L373 _public prototype_ `virtual TSharedRef<class IDetailsView> CreateDetailView( const struct FDetailsViewArgs& DetailsViewArgs );` — Creates a new detail view @param DetailsViewArgs		The struct containing all the user definable details view arguments @return The new detail view
- L381 _public prototype_ `virtual TSharedPtr<class IDetailsView> FindDetailView( const FName ViewIdentifier ) const;` — Find an existing detail view @param ViewIdentifier	The name of the details view to find @return The existing detail view, or null if it wasn't found
- L390 _public prototype_ `virtual TSharedRef<SWindow> CreateFloatingDetailsView( const TArray< UObject* >& InObjects, bool bIsLockable );` — Convenience method for creating a new floating details window (a details view with its own top level window) @param InObjects			The objects to create the detail view for. @param bIsLockable		True if the property view can be locked. @return The new details view window.
- L400 _public prototype_ `virtual TSharedPtr<class ISinglePropertyView> CreateSingleProperty( UObject* InObject, FName InPropertyName, const struct FSinglePropertyParams& InitParams );` — Creates a standalone widget for a single object property @param InObject			The object to view @param InPropertyName	The name of the property to display @param InitParams		Optional init params for a single property @return The new property if valid or null
- L410 _public prototype_ `virtual TSharedPtr<class ISinglePropertyView> CreateSingleProperty(const TSharedPtr<class IStructureDataProvider>& InStruct, FName InPropertyName, const struct FSinglePropertyParams& InitParams);` — Creates a standalone widget for a single struct property @param InStruct			The struct containing the property to view @param InPropertyName	The name of the property to display @param InitParams		Optional init params for a single property @return The new property if valid or null
- L412 _public prototype_ `virtual TSharedRef<class IStructureDetailsView> CreateStructureDetailView(const struct FDetailsViewArgs& DetailsViewArgs, const FStructureDetailsViewArgs& StructureDetailsViewArgs, TSharedPtr<class FStructOnScope> StructData, const FText& CustomName = FText::GetEmpty());`
- L413 _public prototype_ `virtual TSharedRef<class IStructureDetailsView> CreateStructureProviderDetailView(const FDetailsViewArgs& DetailsViewArgs, const FStructureDetailsViewArgs& StructureDetailsViewArgs, TSharedPtr<IStructureDataProvider> StructProvider, const FText& CustomName = FText::GetEmpty());`
- L415 _public prototype_ `virtual TSharedRef<class IPropertyRowGenerator> CreatePropertyRowGenerator(const struct FPropertyRowGeneratorArgs& InArgs);`
- L422 _public prototype_ `virtual TSharedRef<class IPropertyChangeListener> CreatePropertyChangeListener();` — Creates a property change listener that notifies users via a  delegate when a property on an object changes @return The new property change listener
- L424 _public prototype_ `virtual TSharedRef< class IPropertyTable > CreatePropertyTable();`
- L426 _public prototype_ `virtual TSharedRef< SWidget > CreatePropertyTableWidget( const TSharedRef< class IPropertyTable >& PropertyTable );`
- L428 _public prototype_ `virtual TSharedRef< SWidget > CreatePropertyTableWidget( const TSharedRef< class IPropertyTable >& PropertyTable, const TArray< TSharedRef< class IPropertyTableCustomColumn > >& Customizations );`
- L429 _public prototype_ `virtual TSharedRef< class IPropertyTableWidgetHandle > CreatePropertyTableWidgetHandle( const TSharedRef< IPropertyTable >& PropertyTable );`
- L430 _public prototype_ `virtual TSharedRef< class IPropertyTableWidgetHandle > CreatePropertyTableWidgetHandle( const TSharedRef< IPropertyTable >& PropertyTable, const TArray< TSharedRef< class IPropertyTableCustomColumn > >& Customizations );`
- L432 _public prototype_ `virtual TSharedRef< IPropertyTableCellPresenter > CreateTextPropertyCellPresenter( const TSharedRef< class FPropertyNode >& InPropertyNode, const TSharedRef< class IPropertyTableUtilities >& InPropertyUtilities, const FSlateFontInfo* InFontPtr = NULL, const TSharedPtr< IPropertyTableCell >& InCell = nullptr);`
- L441 _public prototype_ `virtual FStructProperty* RegisterStructProperty(const UStruct* StructClass);` — Register a floating struct so that the details panel may use it as a property @param StructClass		The struct to register @return The struct property that may may be associated with the details panel
- L446 _public prototype_ `virtual TSharedRef< FAssetEditorToolkit > CreatePropertyEditorToolkit(const TSharedPtr< class IToolkitHost >& InitToolkitHost, UObject* ObjectToEdit );`
- L447 _public prototype_ `virtual TSharedRef< FAssetEditorToolkit > CreatePropertyEditorToolkit(const TSharedPtr< IToolkitHost >& InitToolkitHost, const TArray< UObject* >& ObjectsToEdit );`
- L448 _public prototype_ `virtual TSharedRef< FAssetEditorToolkit > CreatePropertyEditorToolkit(const TSharedPtr< IToolkitHost >& InitToolkitHost, const TArray< TWeakObjectPtr< UObject > >& ObjectsToEdit );`
- L450 _public prototype_ `FPropertyTypeLayoutCallback GetPropertyTypeCustomization(const FProperty* InProperty,const IPropertyHandle& PropertyHandle, const FCustomPropertyTypeLayoutMap& InstancedPropertyTypeLayoutMap);`
- L451 _public prototype_ `FPropertyTypeLayoutCallback FindPropertyTypeLayoutCallback(FName PropertyTypeName, const IPropertyHandle& PropertyHandle, const FCustomPropertyTypeLayoutMap& InstancedPropertyTypeLayoutMapp);`
- L452 _public prototype_ `bool IsCustomizedStruct(const UStruct* Struct, const FCustomPropertyTypeLayoutMap& InstancePropertyTypeLayoutMap) const;`
- L454 _public prototype_ `DECLARE_EVENT(PropertyEditorModule, FPropertyEditorOpenedEvent);`
- L455 _public function_ `virtual FPropertyEditorOpenedEvent& OnPropertyEditorOpened()`
- L457 _public prototype_ `DECLARE_EVENT_OneParam(PropertyEditorModule, FOnPropertyMatrixAssetsSaved, const TArray<UObject*>&);`
- L458 _public function_ `virtual FOnPropertyMatrixAssetsSaved& OnPropertyMatrixAssetsSaved()`
- L460 _public function_ `const FCustomDetailLayoutNameMap& GetClassNameToDetailLayoutNameMap() const`
- L463 _public function_ `FOnGenerateGlobalRowExtension& GetGlobalRowExtensionDelegate()` — Get the global row extension generators.
- L465 _public function_ `const bool GetCanUsePropertyMatrix() const`
- L466 _public function_ `void SetCanUsePropertyMatrix(const bool bInCanUsePropertyMatrix)`
- L488 _private prototype_ `virtual TSharedRef<SPropertyTreeViewImpl> CreatePropertyView( UObject* InObject, bool bAllowFavorites, bool bIsLockable, bool bHiddenPropertyVisibility, bool bAllowSearch, bool ShowTopLevelNodes, FNotifyHook* InNotifyHook, float InNameColumnWidth, FOnPropertySelectionChanged OnPropertySelectionChanged, FOnPropertyClicked OnPropertyMiddleClicked, FConstructExternalColumnHeaders ConstructExternalColumnHeaders, FConstructExternalColumnCell ConstructExternalColumnCell );` — Creates and returns a property view widget for embedding property views in other widgets NOTE: At this time these MUST not be referenced by the caller of CreatePropertyView when the property module unloads @param	InObject						The UObject that the property view should observe(Optional) @param	bAllowFavorites					Whether the property view should save favorites @param	bIsLockable						Whether or not the property view is lockable @param	bAllowSearch					Whether or not the property window allows searching it @param	InNotifyHook					Notify hook to call on some property change events @param	ColumnWidth						The width of the name column @param	OnPropertySelectionChanged		Delegate for notifying when the property selection has changed. @return	The newly created SPropertyTreeViewImpl widget
- L490 _private prototype_ `virtual TSharedRef<class IStructureDetailsView> CreateStructureDetailView(const struct FDetailsViewArgs& DetailsViewArgs, const FStructureDetailsViewArgs& StructureDetailsViewArgs, const FText& CustomName = FText::GetEmpty());`
- L492 _private prototype_ `TSharedPtr<FAssetThumbnailPool> GetThumbnailPool();`
- L494 _private prototype_ `void GetAllSectionsHelper(const UStruct* Struct, TArray<TSharedPtr<FPropertySection>>& OutSections, TSet<const UStruct*>& ProcessedStructs) const;`
- L495 _private prototype_ `void FindSectionsForCategoryHelper(const UStruct* Struct, FName CategoryName, TArray<TSharedPtr<FPropertySection>>& OutSections, TSet<const UStruct*>& SearchedStructs) const;`
- L497 _private prototype_ `TSharedPtr<class ISinglePropertyView> CreateSinglePropertyImpl(UObject* InObject, const TSharedPtr<IStructureDataProvider>& InStruct, FName InPropertyName, const struct FSinglePropertyParams& InitParams);`
- L498 _private prototype_ `void CompactSinglePropertyViewArray();`
- L501 _private prototype_ `void RegisterMenus();` — Register Menu extension points
- L503 _private prototype_ `static void PopulateRowContextMenu(UToolMenu* InToolMenu);`
- L507 _private member_ `TArray< TWeakPtr<class SDetailsView> > AllDetailViews;` — All created detail views
- L509 _private member_ `TArray< TWeakPtr<class SSingleProperty> > AllSinglePropertyViews;` — All created single property views
- L511 _private member_ `FCustomDetailLayoutNameMap ClassNameToDetailLayoutNameMap;` — A mapping of class names to detail layout delegates, called when querying for custom detail layouts
- L513 _private member_ `FCustomPropertyTypeLayoutMap GlobalPropertyTypeToLayoutMap;` — A mapping of property names to property type layout delegates, called when querying for custom property layouts
- L515 _private member_ `TMultiMap<FName, FPropertyHandleLayoutOverride> PropertyHandleLayoutOverrides;` — Registered list of override callbacks. First one returning non-None is going to be applied (if any).
- L517 _private member_ `TMap<FName, TSharedPtr<FClassSectionMapping>> ClassSectionMappings;` — A mapping of class names to section mappings.
- L519 _private member_ `FPropertyEditorOpenedEvent PropertyEditorOpened;` — Event to be called when a property editor is opened
- L521 _private member_ `FOnPropertyMatrixAssetsSaved PropertyMatrixAssetsSaved;` — Event to be called when assets are saved in bulk from the property matrix editor.
- L523 _private member_ `TMap<FName, FStructProperty*> RegisteredStructToProxyMap;` — Mapping of registered floating UStructs to their struct proxy so they show correctly in the details panel
- L525 _private member_ `TSharedPtr<class FAssetThumbnailPool> GlobalThumbnailPool;` — Shared thumbnail pool used by property row generators
- L527 _private member_ `UStruct* StructOnScopePropertyOwner;` — Container for ScopeOnStruct FStructProperty objects
- L529 _private member_ `FOnGenerateGlobalRowExtension OnGenerateGlobalRowExtension;` — Delegate called to extend the name column widget on a property row.
- L531 _private member_ `bool bCanUsePropertyMatrixOverride = true;` — Override for if the Property Matrix is availabe

#### Free symbols / members of external scopes

- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace PropertyEditor` (scope `UE`)
- L30 _variable_ `inline const FName RowContextMenuName = TEXT("Pro` (scope `UE::PropertyEditor`)
- L36 _namespace_ `namespace EPropertyNamePlacement`
- L55 _namespace_ `namespace FPropertyAccess`
- L96 _typedef_ `typedef TMap< TWeakObjectPtr<UStruct>, FDetailLayoutCallback > FCustomDetailLayoutMap;`
- L97 _typedef_ `typedef TMap< FName, FDetailLayoutCallback > FCustomDetailLayoutNameMap;`
- L454 _delegate_ `DECLARE_EVENT(PropertyEditorModule, FPropertyEditorOpenedEvent);`
- L457 _delegate_ `DECLARE_EVENT_OneParam(PropertyEditorModule, FOnPropertyMatrixAssetsSaved, const TArray<UObject*>&);`

### `Source/Editor/PropertyEditor/Public/PropertyEditorPermissionList.h` (Public)
_(no declarations extracted)_

### `Source/Editor/PropertyEditor/Public/PropertyEditorUtils.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace PropertyEditorUtils`
- L15 _prototype_ `void GetPropertyOptions(TArray<UObject*>& InOutContainers, FString& InOutPropertyPath, TArray<TSharedPtr<FString>>& InOutOptions);` (scope `PropertyEditorUtils`) — Calculates the possible drop-down options for the specified property path @param	InOutContainers		The container objects to resolve the property path against @param	InOutPropertyPath	The property path @param	InOutOptions		The resulting options
- L24 _prototype_ `void GetPropertyOptions( TArray<UObject*>& InOutContainers, FString& InOutPropertyPath, TArray<FString>& OutOptions, TArray<FText>* OutDisplayNames);` (scope `PropertyEditorUtils`) — Calculates the possible drop-down options for the specified property path The resulting option @param	InOutContainers		The container objects to resolve the property path against @param	InOutPropertyPath	The property path @param	InOutOptions		The resulting options
- L39 _prototype_ `void GetAllowedAndDisallowedClasses(const TArray<UObject*>& ObjectList, const FProperty& Property, TArray<const UClass*>& AllowedClasses, TArray<const UClass*>& DisallowedClasses, bool bExactClass, const UClass* ObjectClass = UObject::StaticClass());` (scope `PropertyEditorUtils`) — Get all allowed and disallowed classes according to meta data @param	ObjectList			The list of object that owns the property @param	Property			The FProperty that contains the meta data @param	AllowedClasses		The list of allowed classes @param	DisallowedClasses	The list of disallowed classes @param	bExactClass			Whether subclasses allowed or not @param	ObjectClass			The class to add to the disallowed classes if there is no allowed classes
- L49 _externvar_ `extern const FLazyName ShowObjectRootClassKey;` (scope `PropertyEditorUtils`) — Metadata key for specifying that the property editor's class picker should include the root Object type (/Script/CoreUObject.Object) in the displayed list of classes. By default Object is filtered out. This metadata key has no value, behavior is determined by its presence or absence, e.g.: UPROPERTY(meta=(ShowObjectRootClass)) TSoftClassPtr<UObject> Value;

### `Source/Editor/PropertyEditor/Public/PropertyHandle.h` (Public)


#### class `IPropertyHandle`  
`class IPropertyHandle : public TSharedFromThis<IPropertyHandle>`  
_L42-785_
- inherits: `TSharedFromThis<IPropertyHandle>`
- desc: A handle to a property which is used to read and write the value without needing to handle Pre/PostEditChange, transactions, package modification A handle also is used to identify the property in detail customization interfaces
- L45 _public prototype_ `virtual ~IPropertyHandle()= default;`
- L50 _public prototype_ `virtual bool IsValidHandle() const = 0;` — @return Whether or not the handle points to a valid property node. This can be true but GetProperty may still return null
- L55 _public prototype_ `virtual bool IsSamePropertyNode(TSharedPtr<IPropertyHandle> OtherHandle) const = 0;` — @return Whether or not the handle points to the same property node. Will return true if both point to an invalid node.
- L60 _public prototype_ `virtual bool IsEditConst() const = 0;` — @return Whether or not the property is edit const (can't be changed)
- L65 _public prototype_ `virtual bool IsEditable() const = 0;` — @return The opposite of IsEditConst
- L70 _public prototype_ `virtual bool IsExpanded() const = 0;` — @return Whether or not the property is expanded
- L75 _public prototype_ `virtual void SetExpanded(bool bExpanded) = 0;` — Sets the expanded flag for this property.
- L80 _public prototype_ `virtual const FFieldClass* GetPropertyClass() const = 0;` — Gets the class of the property being edited
- L85 _public prototype_ `virtual FProperty* GetProperty() const = 0;` — Gets the property being edited
- L90 _public prototype_ `virtual FStringView GetPropertyPath() const = 0;` — Helper to fetch a PropertyPath
- L95 _public prototype_ `virtual TSharedPtr<FPropertyPath> CreateFPropertyPath() const = 0;` — Helper to fetch a PropertyPath
- L100 _public prototype_ `virtual int32 GetArrayIndex() const = 0;` — Helper to fetch the ArrayIndex
- L105 _public prototype_ `virtual void RequestRebuildChildren() = 0;` — Indicates that children of this node should be rebuilt next tick.  Some topology changes will require this
- L110 _public prototype_ `virtual FProperty* GetMetaDataProperty() const = 0;` — Gets the property we should use to read meta-data
- L118 _public prototype_ `virtual bool HasMetaData(const FName& Key) const = 0;` — Determines if the property has any metadata associated with the key @param Key The key to lookup in the metadata @return true if there is a (possibly blank) value associated with this key
- L126 _public prototype_ `virtual const FString& GetMetaData(const FName& Key) const = 0;` — Find the metadata value associated with the key @param Key The key to lookup in the metadata @return The value associated with the key
- L134 _public prototype_ `virtual bool GetBoolMetaData(const FName& Key) const = 0;` — Find the metadata value associated with the key and return bool @param Key The key to lookup in the metadata @return return true if the value was true (case insensitive)
- L142 _public prototype_ `virtual int32 GetIntMetaData(const FName& Key) const = 0;` — Find the metadata value associated with the key and return int32 @param Key The key to lookup in the metadata @return the int value stored in the metadata.
- L150 _public prototype_ `virtual float GetFloatMetaData(const FName& Key) const = 0;` — Find the metadata value associated with the key and return float @param Key The key to lookup in the metadata @return the float value stored in the metadata.
- L158 _public prototype_ `virtual double GetDoubleMetaData(const FName& Key) const = 0;` — Find the metadata value associated with the key and return double @param Key The key to lookup in the metadata @return the double value stored in the metadata.
- L166 _public prototype_ `virtual UClass* GetClassMetaData(const FName& Key) const = 0;` — Find the metadata value associated with the key and return UClass* @param Key The key to lookup in the metadata @return the UClass value stored in the metadata.
- L169 _public prototype_ `virtual void SetInstanceMetaData(const FName& Key, const FString& Value) = 0;` — Set metadata value for 'Key' to 'Value' on this property instance (as opposed to the class)
- L176 _public prototype_ `virtual const FString* GetInstanceMetaData(const FName& Key) const = 0;` — Get metadata value for 'Key' for this property instance (as opposed to the class) @return Pointer to metadata value; nullptr if Key not found
- L183 _public prototype_ `virtual const TMap<FName, FString>* GetInstanceMetaDataMap() const = 0;` — Get metadata map for this property instance (as opposed to the class) @return Map ptr containing metadata pairs; nullptr if property node is invalid
- L188 _public prototype_ `virtual FText GetToolTipText() const = 0;` — Gets the property tool tip text.
- L195 _public prototype_ `virtual void SetToolTipText(const FText& ToolTip) = 0;` — Sets the tooltip shown for this property @param ToolTip	The tool tip to show
- L200 _public prototype_ `virtual bool HasDocumentation() = 0;` — @return True if this property has custom documentation, false otherwise
- L205 _public prototype_ `virtual FString GetDocumentationLink() = 0;` — @return The custom documentation link for this property
- L210 _public prototype_ `virtual FString GetDocumentationExcerptName() = 0;` — @return The custom documentation except name for this property
- L219 _public prototype_ `virtual uint8* GetValueBaseAddress( uint8* Base ) const = 0;` — Calculates the memory address for the data associated with this item's value. @param Base The location to use as the starting point for the calculation; typically the address of an object. @return A pointer to a FProperty value or UObject.
- L228 _public prototype_ `virtual FPropertyAccess::Result GetValueAsFormattedString( FString& OutValue, EPropertyPortFlags PortFlags = PPF_PropertyWindow ) const = 0;` — Gets the value formatted as a string. @param OutValue		String where the value is stored.  Remains unchanged if the value could not be set @param PortFlags		Property flags to determine how the string is retrieved. Defaults to PPF_PropertyWindow @return The result of attempting to get the value
- L237 _public prototype_ `virtual FPropertyAccess::Result GetValueAsDisplayString( FString& OutValue, EPropertyPortFlags PortFlags = PPF_PropertyWindow ) const = 0;` — Gets the value formatted as a string, possibly using an alternate form more suitable for display in the UI @param OutValue		String where the value is stored.  Remains unchanged if the value could not be set @param PortFlags		Property flags to determine how the string is retrieved. Defaults to PPF_PropertyWindow @return The result of attempting to get the value
- L245 _public prototype_ `virtual FPropertyAccess::Result GetValueAsFormattedText( FText& OutValue ) const = 0;` — Gets the value formatted as a string, as Text. @param OutValue	Text where the value is stored.  Remains unchanged if the value could not be set @return The result of attempting to get the value
- L253 _public prototype_ `virtual FPropertyAccess::Result GetValueAsDisplayText( FText& OutValue ) const = 0;` — Gets the value formatted as a string, as Text, possibly using an alternate form more suitable for display in the UI @param OutValue	Text where the value is stored.  Remains unchanged if the value could not be set @return The result of attempting to get the value
- L261 _public prototype_ `virtual FPropertyAccess::Result SetValueFromFormattedString( const FString& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags ) = 0;` — Sets the value formatted as a string. @param OutValue	String where the value is stored.  Is unchanged if the value could not be set @return The result of attempting to set the value
- L268 _public prototype_ `virtual void SetOnPropertyValueChanged( const FSimpleDelegate& InOnPropertyValueChanged ) = 0;` — Sets a delegate to call when the value of the property is changed @param InOnPropertyValueChanged	The delegate to call
- L275 _public prototype_ `virtual void SetOnPropertyValueChangedWithData( const TDelegate<void(const FPropertyChangedEvent&)>& InOnPropertyValueChanged ) = 0;` — Sets a delegate to call when the value of the property is changed including the property changed event as parameter @param InOnPropertyValueChanged The delegate to call. Needs to be of type void with a const FPropertyChangedEvent& parameter
- L282 _public prototype_ `virtual void SetOnChildPropertyValueChanged( const FSimpleDelegate& InOnChildPropertyValueChanged ) = 0;` — Sets a delegate to call when the value of the property of a child is changed @param InOnChildPropertyValueChanged	The delegate to call
- L289 _public prototype_ `virtual void SetOnChildPropertyValueChangedWithData( const TDelegate<void(const FPropertyChangedEvent&)>& InOnPropertyValueChanged ) = 0;` — Sets a delegate to call when the value of the property of a child is changed including the property changed event as parameter @param InOnPropertyValueChanged The delegate to call. Needs to be of type void with a const FPropertyChangedEvent& parameter
- L296 _public prototype_ `virtual void SetOnPropertyValuePreChange(const FSimpleDelegate& InOnPropertyValuePreChange) = 0;` — Sets a delegate to call when the value of the property is about to be changed @param InOnPropertyValuePreChange	The delegate to call
- L303 _public prototype_ `virtual void SetOnChildPropertyValuePreChange(const FSimpleDelegate& InOnChildPropertyValuePreChange) = 0;` — Sets a delegate to call when the value of the property of a child is about to be changed @param InOnChildPropertyValuePreChange	The delegate to call
- L310 _public prototype_ `virtual void SetOnPropertyResetToDefault(const FSimpleDelegate& InOnPropertyResetToDefault) = 0;` — Sets a delegate to call when the property is reset to default @param InOnPropertyResetToDefault	The delegate to call
- L319 _public prototype_ `virtual FPropertyAccess::Result GetValue( float& OutValue ) const = 0;` — Gets the typed value of a property. If the property does not support the value type FPropertyAccess::Fail is returned @param OutValue	The value that will be set if successful @return The result of attempting to get the value
- L320 _public prototype_ `virtual FPropertyAccess::Result GetValue( double& OutValue ) const = 0;`
- L321 _public prototype_ `virtual FPropertyAccess::Result GetValue( bool& OutValue ) const = 0;`
- L322 _public prototype_ `virtual FPropertyAccess::Result GetValue( int8& OutValue ) const = 0;`
- L323 _public prototype_ `virtual FPropertyAccess::Result GetValue( int16& OutValue ) const = 0;`
- L324 _public prototype_ `virtual FPropertyAccess::Result GetValue( int32& OutValue ) const = 0;`
- L325 _public prototype_ `virtual FPropertyAccess::Result GetValue( int64& OutValue ) const = 0;`
- L326 _public prototype_ `virtual FPropertyAccess::Result GetValue( uint8& OutValue ) const = 0;`
- L327 _public prototype_ `virtual FPropertyAccess::Result GetValue( uint16& OutValue ) const = 0;`
- L328 _public prototype_ `virtual FPropertyAccess::Result GetValue( uint32& OutValue ) const = 0;`
- L329 _public prototype_ `virtual FPropertyAccess::Result GetValue( uint64& OutValue ) const = 0;`
- L330 _public prototype_ `virtual FPropertyAccess::Result GetValue( FString& OutValue ) const = 0;`
- L331 _public prototype_ `virtual FPropertyAccess::Result GetValue( FText& OutValue ) const = 0;`
- L332 _public prototype_ `virtual FPropertyAccess::Result GetValue( FName& OutValue ) const = 0;`
- L333 _public prototype_ `virtual FPropertyAccess::Result GetValue( FVector& OutValue ) const = 0;`
- L334 _public prototype_ `virtual FPropertyAccess::Result GetValue( FVector2D& OutValue ) const = 0;`
- L335 _public prototype_ `virtual FPropertyAccess::Result GetValue( FVector4& OutValue ) const = 0;`
- L336 _public prototype_ `virtual FPropertyAccess::Result GetValue( FQuat& OutValue ) const = 0;`
- L337 _public prototype_ `virtual FPropertyAccess::Result GetValue( FRotator& OutValue ) const = 0;`
- L338 _public prototype_ `virtual FPropertyAccess::Result GetValue( UObject*& OutValue ) const = 0;`
- L339 _public prototype_ `virtual FPropertyAccess::Result GetValue( const UObject*& OutValue ) const = 0;`
- L340 _public prototype_ `virtual FPropertyAccess::Result GetValue( FAssetData& OutValue ) const = 0;`
- L341 _public prototype_ `virtual FPropertyAccess::Result GetValueData( void*& OutAddress ) const = 0;`
- L342 _public prototype_ `virtual FPropertyAccess::Result GetValue(FProperty*& OutValue) const = 0;`
- L343 _public prototype_ `virtual FPropertyAccess::Result GetValue(const FProperty*& OutValue) const = 0;`
- L351 _public prototype_ `virtual FPropertyAccess::Result SetValue( const float& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags ) = 0;` — Sets the typed value of a property. If the property does not support the value type FPropertyAccess::Fail is returned @param InValue	The value to set @return The result of attempting to set the value
- L352 _public prototype_ `virtual FPropertyAccess::Result SetValue( const double& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags ) = 0;`
- L353 _public prototype_ `virtual FPropertyAccess::Result SetValue( const bool& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags ) = 0;`
- L354 _public prototype_ `virtual FPropertyAccess::Result SetValue( const int8& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags ) = 0;`
- L355 _public prototype_ `virtual FPropertyAccess::Result SetValue( const int16& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags ) = 0;`
- L356 _public prototype_ `virtual FPropertyAccess::Result SetValue( const int32& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags ) = 0;`
- L357 _public prototype_ `virtual FPropertyAccess::Result SetValue( const int64& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags ) = 0;`
- L358 _public prototype_ `virtual FPropertyAccess::Result SetValue( const uint8& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags ) = 0;`
- L359 _public prototype_ `virtual FPropertyAccess::Result SetValue( const uint16& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags ) = 0;`
- L360 _public prototype_ `virtual FPropertyAccess::Result SetValue( const uint32& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags ) = 0;`
- L361 _public prototype_ `virtual FPropertyAccess::Result SetValue( const uint64& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags ) = 0;`
- L362 _public prototype_ `virtual FPropertyAccess::Result SetValue( const FString& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags ) = 0;`
- L363 _public prototype_ `virtual FPropertyAccess::Result SetValue( const FText& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags ) = 0;`
- L364 _public prototype_ `virtual FPropertyAccess::Result SetValue( const FName& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags ) = 0;`
- L365 _public prototype_ `virtual FPropertyAccess::Result SetValue( const FVector& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags ) = 0;`
- L366 _public prototype_ `virtual FPropertyAccess::Result SetValue( const FVector2D& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags ) = 0;`
- L367 _public prototype_ `virtual FPropertyAccess::Result SetValue( const FVector4& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags ) = 0;`
- L368 _public prototype_ `virtual FPropertyAccess::Result SetValue( const FQuat& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags ) = 0;`
- L369 _public prototype_ `virtual FPropertyAccess::Result SetValue( const FRotator& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags ) = 0;`
- L370 _public prototype_ `virtual FPropertyAccess::Result SetValue( UObject* const& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags ) = 0;`
- L371 _public prototype_ `virtual FPropertyAccess::Result SetValue( const UObject* const& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags ) = 0;`
- L372 _public prototype_ `virtual FPropertyAccess::Result SetValue( const FAssetData& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags ) = 0;`
- L373 _public prototype_ `virtual FPropertyAccess::Result SetValue( const TCHAR* InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags ) = 0;`
- L374 _public prototype_ `virtual FPropertyAccess::Result SetValue( FProperty* const& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags) = 0;`
- L375 _public prototype_ `virtual FPropertyAccess::Result SetValue( const FProperty* const& InValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags) = 0;`
- L381 _public prototype_ `virtual void NotifyPreChange() = 0;` — Called to manually notify root objects that this property is about to change This does not need to be called when SetValue functions are used since it will be called automatically
- L387 _public prototype_ `virtual void NotifyPostChange(EPropertyChangeType::Type ChangeType) = 0;` — Called to manually notify root objects that this property has changed This does not need to be called when SetValue functions are used since it will be called automatically
- L393 _public prototype_ `virtual void NotifyFinishedChangingProperties() = 0;` — Called to manually notify root objects that this property has finished changing This does not need to be called when SetValue functions are used since it will be called automatically
- L399 _public prototype_ `virtual FPropertyAccess::Result SetObjectValueFromSelection() = 0;` — Sets the object value from the current editor selection Will fail if this handle isn't an object property
- L404 _public prototype_ `virtual int32 GetNumPerObjectValues() const = 0;` — Gets the number of objects that this handle is editing
- L411 _public prototype_ `virtual FPropertyAccess::Result SetPerObjectValues( const TArray<FString>& PerObjectValues, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags ) = 0;` — Sets a unique value for each object this handle is editing @param PerObjectValues	The per object values as a formatted string.  There must be one entry per object or the return value is FPropertyAccess::Fail
- L416 _public prototype_ `virtual FPropertyAccess::Result GetPerObjectValues( TArray<FString>& OutPerObjectValues ) const = 0;` — Gets a unique value for each object this handle is editing
- L424 _public prototype_ `virtual FPropertyAccess::Result SetPerObjectValue( const int32 ObjectIndex, const FString& ObjectValue, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags ) = 0;` — Sets a value on the specified object that this handle is editing @param ObjectIndex		The index of the object to set the value of @param ObjectValue		The value to set on the given object
- L432 _public prototype_ `virtual FPropertyAccess::Result GetPerObjectValue( const int32 ObjectIndex, FString& OutObjectValue ) const = 0;` — Gets a value for the specified object that this handle is editing @param ObjectIndex		The index of the object to get the value of @param OutObjectValue	Filled with the value for this object
- L437 _public prototype_ `virtual int32 GetIndexInArray() const = 0;` — @return The index of this element in an array if it is in one.  INDEX_NONE otherwise
- L447 _public prototype_ `virtual TSharedPtr<IPropertyHandle> GetChildHandle( FName ChildName, bool bRecurse = true ) const = 0;` — Gets a child handle of this handle.  Useful for accessing properties in structs. Array elements cannot be accessed in this way @param ChildName The name of the child @param bRecurse	Whether or not to recurse into children of children and so on. If false will only search all immediate children @return The property handle for the child if it exists
- L455 _public prototype_ `virtual TSharedPtr<IPropertyHandle> GetChildHandle( uint32 Index ) const = 0;` — Gets a child handle of this handle.  Useful for accessing properties in structs. @param The index of the child @return The property handle for the child if it exists
- L461 _public prototype_ `virtual TSharedPtr<IPropertyHandle> GetParentHandle() const = 0;` — @return a handle to the parent property This parent handle may not contain a valid FProperty if the parent is the uobject.
- L466 _public prototype_ `virtual TSharedPtr<IPropertyHandle> GetKeyHandle() const = 0;` — @return The property handle to the key element for this value if this is a map element
- L471 _public prototype_ `virtual FPropertyAccess::Result GetNumChildren( uint32& OutNumChildren ) const = 0;` — @return The number of children the property handle has
- L476 _public prototype_ `virtual uint32 GetNumOuterObjects() const = 0;` — @return Get the number objects that contain this property and are being observed in the property editor
- L483 _public prototype_ `virtual void GetOuterObjects( TArray<UObject*>& OuterObjects ) const = 0;` — Get the objects that contain this property @param OuterObjects	An array that will be populated with the outer objects
- L490 _public prototype_ `virtual void GetOuterStructs( TArray<TSharedPtr<FStructOnScope>>& OutStructs ) const = 0;` — Get the structures that contain this property @param OutStructs	An array that will be populated with the outer structures
- L497 _public prototype_ `virtual const UClass* GetOuterBaseClass() const = 0;` — Get the shared base class of the objects that contain this property. @return The shared base class of the outer objects, or null if none are selected.
- L504 _public prototype_ `virtual void ReplaceOuterObjects( const TArray<UObject*>& OuterObjects ) = 0;` — Set the outer objects for this property @param OuterObjects An array that contains the new outer objects
- L512 _public prototype_ `virtual void GetOuterPackages(TArray<UPackage*>& OuterPackages) const = 0;` — Get the packages that contain this property @param OuterPackages	An array that will be populated with the outer packages
- L519 _public typedef_ `typedef TFunctionRef<bool(void* , const int32 , const int32 )> EnumerateRawDataFuncRef;` — Enumerate the raw data of this property.  (Each pointer can be cast to the property data type) @param InRawDataCallback		The function to call for each data
- L520 _public typedef_ `typedef TFunctionRef<bool(const void* , const int32 , const int32 )> EnumerateConstRawDataFuncRef;` — typedef TFunctionRef<bool(void*  RawData , const int32  DataIndex , const int32  NumDatas )> EnumerateRawDataFuncRef;   Return true to continue enumeration
- L521 _public prototype_ `virtual void EnumerateRawData( const EnumerateRawDataFuncRef& InRawDataCallback ) = 0;` — typedef TFunctionRef<bool(const void*  RawData , const int32  DataIndex , const int32  NumDatas )> EnumerateConstRawDataFuncRef;   Return true to continue enumeration
- L522 _public prototype_ `virtual void EnumerateConstRawData( const EnumerateConstRawDataFuncRef& InRawDataCallback ) const = 0;`
- L529 _public prototype_ `virtual void AccessRawData( TArray<void*>& RawData ) = 0;` — Accesses the raw data of this property.  (Each pointer can be cast to the property data type) @param RawData	An array of raw data.  The elements in this array are the raw data for this property on each of the objects in the  property editor
- L530 _public prototype_ `virtual void AccessRawData( TArray<const void*>& RawData ) const = 0;`
- L537 _public prototype_ `virtual TSharedPtr<IPropertyHandleArray> AsArray() = 0;` — Returns this handle as an array if possible @return the handle as an array if it is an array (static or dynamic)
- L542 _public prototype_ `virtual TSharedPtr<IPropertyHandleSet> AsSet() = 0;` — @return This handle as a set if possible
- L547 _public prototype_ `virtual TSharedPtr<IPropertyHandleMap> AsMap() = 0;` — @return This handle as a map if possible
- L552 _public prototype_ `virtual TSharedPtr<IPropertyHandleOptional> AsOptional() = 0;` — @return This handle as an optional if possible
- L557 _public prototype_ `virtual TSharedPtr<IPropertyHandleStruct> AsStruct() = 0;` — @return This handle as struct if possible
- L562 _public prototype_ `virtual FText GetPropertyDisplayName() const = 0;` — @return The display name of the property
- L567 _public prototype_ `virtual void SetPropertyDisplayName(FText InDisplayName) = 0;` — Allows the handle to override the node's display name
- L572 _public prototype_ `virtual void ResetToDefault() = 0;` — Resets the value to its default
- L577 _public prototype_ `virtual bool DiffersFromDefault() const = 0;` — @return Whether or not the value differs from its default
- L582 _public prototype_ `virtual FText GetResetToDefaultLabel() const = 0;` — @return A label suitable for displaying the reset to default value
- L587 _public prototype_ `virtual bool GeneratePossibleValues(TArray< TSharedPtr<FString> >& OutOptionStrings, TArray< FText >& OutToolTips, TArray<bool>& OutRestrictedItems) = 0;` — Generates a list of possible enum/class options for the property
- L593 _public prototype_ `virtual bool GeneratePossibleValues(TArray<FString>& OutOptionStrings, TArray< FText >& OutToolTips, TArray<bool>& OutRestrictedItems, TArray<FText>* OutDisplayNames) = 0;` — Generates a list of possible enum/class options for the property DisplayNames is optional
- L598 _public prototype_ `virtual void MarkHiddenByCustomization() = 0;` — Marks this property has hidden by customizaton (will not show up in the default place)
- L603 _public prototype_ `virtual void MarkResetToDefaultCustomized(bool bCustomized = true) = 0;` — Marks this property has having a custom reset to default (reset to default will not show up in the default place)
- L608 _public prototype_ `virtual void ClearResetToDefaultCustomized() = 0;` — Marks this property as not having a custom reset to default (useful when a widget customizing reset to default goes away)
- L613 _public prototype_ `virtual bool IsFavorite() const = 0;` — @return true if the property is mark as a favorite
- L618 _public prototype_ `virtual bool IsCustomized() const = 0;` — @return True if this property's UI is customized
- L623 _public prototype_ `virtual bool IsResetToDefaultCustomized() const = 0;` — @return True if this property's reset to default UI is customized (but not necessarialy the property UI itself)
- L630 _public prototype_ `virtual FString GeneratePathToProperty() const = 0;` — Generates a path from the parent UObject class to this property @return The path to this property
- L642 _public prototype_ `virtual TSharedRef<SWidget> CreatePropertyNameWidget( const FText& NameOverride, const FText& ToolTipOverride, bool bDisplayResetToDefault, bool bDisplayText = true, bool bDisplayThumbnail = true ) const = 0;` — `UE_DEPRECATED(5.0, "CreatePropertyNameWidget no longer supports bDisplayResetToDefault, bDisplayText or bDisplayThumbnail.")` — Creates a name widget for this property @param NameOverride				The name override to use instead of the property name @param ToolTipOverride			The tooltip override to use instead of the property name @param bDisplayResetToDefault	Whether or not to display the reset to default button @param bDisplayText				Whether or not to display the text name of the property @param bDisplayThumbnail			Whether or not to display the thumbnail for the property (if any) @return the name widget for this property
- L649 _public prototype_ `virtual TSharedRef<SWidget> CreatePropertyNameWidget(const FText& NameOverride = FText::GetEmpty(), const FText& ToolTipOverride = FText::GetEmpty()) const = 0;` — Creates a name widget for this property @param NameOverride				The name override to use instead of the property name @param ToolTipOverride			The tooltip override to use instead of the property name
- L658 _public prototype_ `virtual TSharedRef<SWidget> CreatePropertyValueWidget( bool bDisplayDefaultPropertyButtons = true ) const = 0;` — Creates a value widget for this property @param bDisplayDefaultPropertyButtons	If the value widget should include the property buttons. @return the value widget for this property
- L668 _public prototype_ `virtual TSharedRef<SWidget> CreatePropertyValueWidgetWithCustomization( const IDetailsView* DetailsView ) = 0;` — Creates a value widget for this property using customization, if available. Note that this is only the value widget for the header/main row for properties with child rows (ie: structs) @param DetailsView						The details view to create the value widget for. Used to retrieve per details view customizations. @return the value widget for this property
- L674 _public prototype_ `virtual TSharedRef<SWidget> CreateDefaultPropertyButtonWidgets() const = 0;` — Creates the default buttons which appear next to value widgets.  This is useful when creating customizations which don't use CreatePropertyValueWidget but you still want array item behaviors and reset to default capabilities.
- L681 _public prototype_ `virtual void CreateDefaultPropertyCopyPasteActions(FUIAction& OutCopyAction, FUIAction& OutPasteAction) const = 0;` — Creates the default copy and paste actions for a single property.  This is useful when creating customizations which use custom node builders since they can't implement copy/paste by default because the contents of the rows is not known, but frequently you're using the handles on each row to generate this UI.
- L687 _public prototype_ `virtual void AddRestriction( TSharedRef<const FPropertyRestriction> Restriction ) = 0;` — Adds a restriction to the possible values for this property. @param Restriction	The restriction being added to this property.
- L694 _public prototype_ `virtual bool IsRestricted(const FString& Value) const = 0;` — Tests if a value is restricted for this property @param Value			The value to test for restriction. @return				True if this value is restricted.
- L702 _public prototype_ `virtual bool IsRestricted(const FString& Value, TArray<FText>& OutReasons) const = 0;` — Tests if a value is restricted for this property. @param Value			The value to test for restriction. @param OutReasons	Outputs an array of the reasons why this value is restricted. @return				True if this value is restricted.
- L710 _public prototype_ `virtual bool GenerateRestrictionToolTip(const FString& Value, FText& OutTooltip) const = 0;` — Generates a consistent tooltip describing this restriction for use in the editor. @param Value			The value to test for restriction and generate the tooltip from. @param OutTooltip	The tooltip describing why this value is restricted. @return				True if this value is restricted.
- L717 _public prototype_ `virtual bool IsDisabled(const FString& Value) const = 0;` — Tests if a value is disabled for this property @param Value			The value to test whether it is disabled. @return				True if this value is disabled.
- L725 _public prototype_ `virtual bool IsDisabled(const FString& Value, TArray<FText>& OutReasons) const = 0;` — Tests if a value is disabled for this property. @param Value			The value to test whether it is disabled. @param OutReasons	Outputs an array of the reasons why this value is disabled. @return				True if this value is disabled.
- L732 _public prototype_ `virtual bool IsHidden(const FString& Value) const = 0;` — Tests if a value is hidden for this property @param Value			The value to test whether it is hidden. @return				True if this value is hidden.
- L740 _public prototype_ `virtual bool IsHidden(const FString& Value, TArray<FText>& OutReasons) const = 0;` — Tests if a value is hidden for this property. @param Value			The value to test whether it is hidden. @param OutReasons	Outputs an array of the reasons why this value is hidden. @return				True if this value is hidden.
- L746 _public prototype_ `virtual void SetIgnoreValidation(bool bInIgnore) = 0;` — Sets whether or not data validation should occur for this property and all of its children. It is generally unsafe to set this value unless you know what you are doing.  Data validation done by the details panel ensures changes to properties out from under the details panel are known This should only ever be set for extremely large arrays or other costly validation checks where validation is handled by the customizer
- L754 _public prototype_ `virtual TArray<TSharedPtr<IPropertyHandle>> AddChildStructure( TSharedRef<FStructOnScope> ChildStructure ) = 0;` — Adds a child structure @param ChildStructure	The structure to add @return An array of interfaces to the properties that were added
- L755 _public prototype_ `virtual TArray<TSharedPtr<IPropertyHandle>> AddChildStructure( TSharedRef<IStructureDataProvider> ChildStructure ) = 0;`
- L758 _public prototype_ `virtual void RemoveChildren() = 0;` — Removes all children of this handle
- L765 _public prototype_ `virtual bool CanResetToDefault() const = 0;` — Returns whether or not the property can be set to default @return If this property can be reset to default
- L770 _public prototype_ `virtual void ExecuteCustomResetToDefault(const FResetToDefaultOverride& OnCustomResetToDefault) = 0;` — Sets an override for this property's reset to default behavior
- L776 _public prototype_ `virtual FName GetDefaultCategoryName() const = 0;` — Gets the category FName that a property is in at the default location defined by the class the property is in It does not handle the property being moved to another category during customization
- L782 _public prototype_ `virtual FText GetDefaultCategoryText() const = 0;` — Gets the category display name that a property is in at the default location defined by the class the property is in It does not handle the property being moved to another category during customization
- L784 _public prototype_ `virtual bool IsCategoryHandle() const = 0;`

#### class `FPropertyHandleItemAddResult`  
`class FPropertyHandleItemAddResult`  
_L787-804_
- L790 _public prototype_ `FPropertyHandleItemAddResult() = default;`
- L791 _public function_ `FPropertyHandleItemAddResult(int32 InIndex, FPropertyAccess::Result InResult) : Index(InIndex) , PropertyAccessResult(InResult)`
- L796 _public function_ `int32 GetIndex() const`
- L797 _public function_ `FPropertyAccess::Result GetAccessResult() const`
- L799 _public function_ `operator FPropertyAccess::Result() const`
- L802 _private member_ `int32 Index = INDEX_NONE;`
- L803 _private member_ `FPropertyAccess::Result PropertyAccessResult = FPropertyAccess::Fail;`

#### class `IPropertyHandleArray`  
`class IPropertyHandleArray`  
_L809-890_
- desc: A handle to an array property which allows you to manipulate the array
- L812 _public prototype_ `virtual ~IPropertyHandleArray()= default;`
- L818 _public prototype_ `virtual FPropertyHandleItemAddResult AddItem() = 0;` — Adds an item to the end of the array @return Whether or not this was successful
- L824 _public prototype_ `virtual FPropertyAccess::Result EmptyArray() = 0;` — Empty the array @return Whether or not this was successful
- L830 _public prototype_ `virtual FPropertyAccess::Result Insert( int32 Index ) = 0;` — Inserts an item into the array at the specified index @return Whether or not this was successful
- L836 _public prototype_ `virtual FPropertyAccess::Result DuplicateItem( int32 Index ) = 0;` — Duplicates the item at the specified index in the array. @return Whether or not this was successful
- L842 _public prototype_ `virtual FPropertyAccess::Result DeleteItem( int32 Index ) = 0;` — Deletes the item at the specified index of the array @return Whether or not this was successful
- L848 _public prototype_ `virtual FPropertyAccess::Result SwapItems( int32 FirstIndex, int32 SecondIndex ) = 0;` — Swaps two items @return Whether or not this was successful
- L853 _public prototype_ `virtual FPropertyAccess::Result GetNumElements( uint32& OutNumItems ) const = 0;` — @return The number of elements in the array
- L858 _public prototype_ `virtual TSharedRef<IPropertyHandle> GetElement( int32 Index ) const = 0;` — @return a handle to the element at the specified index
- L864 _public prototype_ `virtual FPropertyAccess::Result MoveElementTo(int32 OriginalIndex, int32 NewIndex) = 0;` — Moves an element from OriginalIndex to NewIndex @return Whether or not this was successful
- L869 _public prototype_ `virtual void SetOnCanItemChange(const FCanPropertyItemChange& InDelegate) = 0;` — Sets a delegate to call before an item in a container is being mutated
- L874 _public prototype_ `virtual FDelegateHandle SetOnChangeBlocked(const FPropertyChangeBlocked::FDelegate& InDelegate) = 0;` — Sets a delegate to call when a property change has been disallowed
- L879 _public prototype_ `virtual void UnregisterOnChangeBlocked(FDelegateHandle Handle) = 0;` — Unregisters a delegate that is bound to OnChangeBlocked
- L884 _public prototype_ `virtual FDelegateHandle SetOnNumElementsChanged( const FSimpleDelegate& InOnNumElementsChanged ) = 0;` — Sets a delegate to call when the number of elements changes
- L889 _public prototype_ `virtual void UnregisterOnNumElementsChanged(FDelegateHandle Handle) = 0;` — Unregisters a delegate that is called when the number of elements changes

#### class `IPropertyHandleSet`  
`class IPropertyHandleSet`  
_L895-943_
- desc: A handle to a property which allows you to manipulate a Set
- L898 _public prototype_ `virtual ~IPropertyHandleSet()= default;`
- L903 _public prototype_ `virtual bool HasDefaultElement() = 0;` — @return True if the set contains an element with a default value, false otherwise
- L909 _public prototype_ `virtual FPropertyHandleItemAddResult AddItem() = 0;` — Adds an item to the set. @return Whether or not this was successful
- L915 _public prototype_ `virtual FPropertyAccess::Result Empty() = 0;` — Empties the set @return Whether or not this was successful
- L921 _public prototype_ `virtual FPropertyAccess::Result DeleteItem(int32 Index) = 0;` — Deletes the item in the set with the specified internal index @return Whether or not this was successful
- L926 _public prototype_ `virtual FPropertyAccess::Result GetNumElements(uint32& OutNumElements) = 0;` — @return The number of elements in the set
- L931 _public prototype_ `virtual TSharedRef<IPropertyHandle> GetElement(int32 Index) const = 0;` — @return a handle to the element at the specified index
- L937 _public prototype_ `virtual FDelegateHandle SetOnNumElementsChanged(const FSimpleDelegate& InOnNumElementsChanged) = 0;` — Sets a delegate to call when the number of elements changes
- L942 _public prototype_ `virtual void UnregisterOnNumElementsChanged(FDelegateHandle Handle) = 0;` — Unregisters a delegate that is called when the number of elements changes

#### class `IPropertyHandleMap`  
`class IPropertyHandleMap`  
_L948-995_
- desc: A handle to a property which allows you to manipulate a Map
- L951 _public prototype_ `virtual ~IPropertyHandleMap() = default;`
- L956 _public prototype_ `virtual bool HasDefaultKey() = 0;` — @return True if the map contains a key with a default value, false otherwise
- L962 _public prototype_ `virtual FPropertyHandleItemAddResult AddItem() = 0;` — Adds an item to the map. @return Whether or not this was successful
- L968 _public prototype_ `virtual FPropertyAccess::Result Empty() = 0;` — Empties the map @return Whether or not this was successful
- L974 _public prototype_ `virtual FPropertyAccess::Result DeleteItem(int32 Index) = 0;` — Deletes the item in the map with the specified internal index @return Whether or not this was successful
- L979 _public prototype_ `virtual FPropertyAccess::Result GetNumElements(uint32& OutNumElements) = 0;` — @return The number of elements in the map
- L984 _public prototype_ `virtual TSharedRef<IPropertyHandle> GetElement(int32 Index) const = 0;` — @return a handle to the element at the specified index
- L989 _public prototype_ `virtual FDelegateHandle SetOnNumElementsChanged(const FSimpleDelegate& InOnNumElementsChanged) = 0;` — Sets a delegate to call when the number of elements changes
- L994 _public prototype_ `virtual void UnregisterOnNumElementsChanged(FDelegateHandle Handle) = 0;` — Unregisters a delegate that is called when the number of elements changes

#### class `IPropertyHandleStruct`  
`class IPropertyHandleStruct`  
_L1000-1006_
- desc: A handle to a property which allows you to access a Struct's Data
- L1003 _public prototype_ `virtual ~IPropertyHandleStruct() = default;`
- L1005 _public prototype_ `virtual TSharedPtr<FStructOnScope> GetStructData() const = 0;`

#### class `IPropertyHandleOptional`  
`class IPropertyHandleOptional`  
_L1011-1034_
- desc: A handle to an optional property which allows you to manipulate the optional
- L1014 _public prototype_ `virtual ~IPropertyHandleOptional() = default;`
- L1020 _public prototype_ `virtual FPropertyAccess::Result GetOptionalValue(FProperty*& OutValue) = 0;` — Get the item @param OutValue	The value of the optional if it is set.
- L1027 _public prototype_ `virtual FPropertyAccess::Result SetOptionalValue(FProperty* NewProperty, const UClass* NewObjectClass) = 0;` — Set the item @param NewValue	The value to set the optional to. Pass in nullptr to default-initialize the value. @return			Whether or not this was successful
- L1033 _public prototype_ `virtual FPropertyAccess::Result ClearOptionalValue() = 0;` — Clear the item @return Whether or not this was successful

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace EPropertyValueSetFlags`
- L23 _typedef_ `typedef uint32 Type;` (scope `EPropertyValueSetFlags`)
- L26 _variable_ `inline const Type DefaultFlags = 0;` (scope `EPropertyValueSetFlags`) — Normal way to call set value (make a transaction, call posteditchange)
- L28 _variable_ `inline const Type NotTransactable = 1 << 0;` (scope `EPropertyValueSetFlags`) — No transaction will be created when setting this value (no undo/redo)
- L30 _variable_ `inline const Type InteractiveChange = 1 << 1;` (scope `EPropertyValueSetFlags`) — When PostEditChange is called mark the change as interactive (e.g, user is spinning a value in a spin box)
- L32 _variable_ `inline const Type InstanceObjects = 1 << 2;` (scope `EPropertyValueSetFlags`) — If the property being imported to is an instanced object, create a new object rather than simply setting the value literally
- L34 _variable_ `inline const Type ResetToDefault = 1 << 3;` (scope `EPropertyValueSetFlags`) — If the property is being set due to being reset to default

### `Source/Editor/PropertyEditor/Public/PropertyPath.h` (Public)


#### struct `FPropertyInfo`  
`struct FPropertyInfo`  
_L10-36_
- L14 _public function_ `FPropertyInfo() : Property() , ArrayIndex(INDEX_NONE)`
- L19 _public function_ `FPropertyInfo(TWeakFieldPtr< FProperty > InProperty, int32 InArrayIndex = INDEX_NONE) : Property(InProperty) , ArrayIndex(InArrayIndex)`
- L24 _public function_ `bool operator==( const FPropertyInfo& Other ) const`
- L29 _public function_ `bool operator!=( const FPropertyInfo& Other ) const`
- L34 _public member_ `TWeakFieldPtr<FProperty> Property;`
- L35 _public member_ `int32 ArrayIndex;`

#### class `FPropertyPath`  
`class FPropertyPath`  
_L39-213_
- L43 _public function_ `static TSharedRef< FPropertyPath > CreateEmpty()`
- L48 _public function_ `static TSharedRef< FPropertyPath > Create( const TWeakFieldPtr<FProperty> Property )`
- L61 _public function_ `bool IsValid() const`
- L66 _public function_ `int32 GetNumProperties() const`
- L71 _public function_ `const FPropertyInfo& GetPropertyInfo( int32 index ) const`
- L76 _public function_ `FPropertyInfo& GetPropertyInfoRef( int32 index )`
- L81 _public function_ `const FPropertyInfo& GetLeafMostProperty() const`
- L86 _public function_ `const FPropertyInfo& GetRootProperty() const`
- L91 _public function_ `TSharedRef< FPropertyPath > ExtendPath( const FPropertyInfo& NewLeaf ) const`
- L101 _public function_ `TSharedRef< FPropertyPath > ExtendPath( const TSharedRef< FPropertyPath >& Extension ) const`
- L115 _public function_ `TSharedRef< FPropertyPath > TrimPath( const int32 AmountToTrim ) const`
- L129 _public function_ `TSharedRef< FPropertyPath > TrimRoot( const int32 AmountToTrim ) const`
- L141 _public function_ `FString ToString(const TCHAR* Separator = TEXT("->")) const`
- L172 _public function_ `void AddProperty( const FPropertyInfo& InProperty )` — Add another property to be associated with this path
- L178 _public function_ `static bool AreEqual( const TSharedRef< FPropertyPath >& PathLhs, const TSharedRef< FPropertyPath >& PathRhs )`
- L208 _public prototype_ `TArray< UE::FPropertyPathName > ToPropertyPathName() const;` — Converts this to an array of property path names that are split between objects in the path.
- L212 _private member_ `TArray< FPropertyInfo > Properties;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L215 _function_ `FORCEINLINE bool operator==( const FPropertyPath& LHS, const FPropertyPath& RHS )`
- L233 _function_ `FORCEINLINE bool operator!=(const FPropertyPath& LHS, const FPropertyPath& RHS)`
- L238 _function_ `FORCEINLINE uint32 GetTypeHash(FPropertyPath const& Path)`

### `Source/Editor/PropertyEditor/Public/PropertyPermissionList.h` (Public)


#### enum `EPropertyPermissionListRules`  
`enum class EPropertyPermissionListRules : uint8`  
_L36-45_
- desc: A hierarchical set of rules that can be used to PermissionList all properties of specific Structs without having to manually add every single property in those Structs. These rules are applied in order from the base Struct to the leaf Struct. UseExistingPermissionList has dual-functionality to alternatively inherit the parent Struct's rule if no PermissionList is manually defined. For example, if you have: class A - (UseExistingPermissionList "MyProp")						PermissionList = "MyProp" class B : public class A - (AllowListAllProperties)					PermissionList = "MyProp","PropA1","PropA2" class C : public class B - (UseExistingPermissionList "AnotherProp")	PermissionList = "MyProp","PropA1","PropA2","AnotherProp" class D : public class B - (UseExistingPermissionList)				PermissionList = "MyProp","PropA1","PropA2","PropD1","PropD2" Note that because class C manually defines a PermissionList, it does not inherit the AllowListAllProperties rule from class B, while class D does not define a PermissionList, so it does inherit the rule, causing all of class D's properties to also get added to the AllowList.
- L39 _public enumerator_ `AllowListAllProperties` — If no PermissionList is manually defined for this Struct, AllowList all properties from this Struct and its subclasses
- L42 _public enumerator_ `AllowListAllSubclassProperties` — If a PermissionList is manually defined for this Struct, AllowList all properties from this Struct's subclasses. If this functionality is needed without any properties to AllowList, a fake property must be added to AllowList instead.
- L44 _public enumerator_ `UseExistingPermissionList` — If a PermissionList is manually defined for this struct, PermissionList those properties. Otherwise, use the parent Struct's rule.

#### struct `FPropertyPermissionListEntry`  
`struct FPropertyPermissionListEntry`  
_L47-53_
- L49 _public member_ `FNamePermissionList PermissionList;`
- L51 _public member_ `TArray<FName> AdditionalOwnerNames;` — When the permission list does not contain any AllowList, DenyList or DenyListAll it needs an AdditionalOwnerName to be tracked here so stays alive without being removed
- L52 _public member_ `EPropertyPermissionListRules Rules = EPropertyPermissionListRules::UseExistingPermissionList;`

#### class `FPropertyPermissionList`  
`class FPropertyPermissionList`  
_L55-190_
- L60 _public prototype_ `void AddPermissionList(TSoftObjectPtr<const UStruct> Struct, const FNamePermissionList& PermissionList, const EPropertyPermissionListRules Rules = EPropertyPermissionListRules::UseExistingPermissionList);` — `UE_DEPRECATED(5.5, "Call AddPermissionList with additional required arguments instead.")` — Add a set of rules for a specific base UStruct to determine which properties are visible in all details panels
- L62 _public prototype_ `void AddPermissionList(TSoftObjectPtr<const UStruct> Struct, const FNamePermissionList& PermissionList, const EPropertyPermissionListRules Rules, const TConstArrayView<FName> InAdditionalOwnerNames);` — Add a set of rules for a specific base UStruct to determine which properties are visible in all details panels
- L64 _public prototype_ `void RemovePermissionList(TSoftObjectPtr<const UStruct> Struct);` — Remove a set of rules for a specific base UStruct to determine which properties are visible in all details panels
- L66 _public prototype_ `void ClearPermissionList();` — Remove all rules
- L69 _public prototype_ `void UnregisterOwner(const FName Owner);` — Unregister an owner from all permission lists currently stored
- L72 _public prototype_ `void AddToAllowList(TSoftObjectPtr<const UStruct> Struct, const FName PropertyName, const FName Owner);` — Add a specific property to a UStruct's AllowList
- L74 _public prototype_ `void AddToAllowList(TSoftObjectPtr<const UStruct> Struct, const TArray<FName>& PropertyNames, const FName Owner);` — Add a list of properties to a UStruct's AllowList
- L76 _public prototype_ `void RemoveFromAllowList(TSoftObjectPtr<const UStruct> Struct, const FName PropertyName, const FName Owner);` — Remove a specific property from a UStruct's AllowList
- L78 _public prototype_ `void AddToDenyList(TSoftObjectPtr<const UStruct> Struct, const FName PropertyName, const FName Owner);` — Add a specific property to a UStruct's DenyList
- L80 _public prototype_ `void RemoveFromDenyList(TSoftObjectPtr<const UStruct> Struct, const FName PropertyName, const FName Owner);` — Remove a specific property from a UStruct's DenyList
- L82 _public prototype_ `void RegisterCustomDetailsTreeNodePermissionDelegate(TSoftObjectPtr<const UStruct> Struct, FCustomDetailTreeNodePermissionDelegate InDelegate);` — Registers a delegate that is capable of handling more advanced use cases, such as details panel rows whose identifiers are created dynamically.
- L83 _public prototype_ `void UnregisterCustomDetailsTreeNodePermissionDelegate(TSoftObjectPtr<const UStruct> Struct);`
- L86 _public member_ `FPermissionListUpdated PermissionListUpdatedDelegate;` — When the PermissionList or DenyList for any struct was added to or removed from.
- L89 _public member_ `FSimpleMulticastDelegate PermissionListEnabledDelegate;` — When the entire PermissionList is enabled or disabled
- L92 _public function_ `bool IsEnabled() const` — Controls whether DoesPropertyPassFilter always returns true or performs property-based filtering.
- L101 _public prototype_ `void SetEnabled(bool bEnable, bool bAnnounce = true);` — Turn on or off the property PermissionList. DoesPropertyPassFilter will always return true if disabled. Optionally the change can be announced through a broadcast, which is typically recommended, but may not be needed if the permission list is only temporary enabled, e.g. during saving. Under the hood, it will be a delegate that will always return bEnabled. If a delegate is passed in instead, that delegate is called to return dynamically whether the filter is enabled or not.
- L102 _public prototype_ `void SetEnabled(const FDelegateEnablePathFilter& bEnable, bool bAnnounce = true);`
- L105 _public prototype_ `bool HasFiltering(const UStruct* ObjectStruct) const;` — Checks if the provided struct has any entries in the allow, deny and deny all lists and returns true in that case.
- L111 _public prototype_ `bool DoesPropertyPassFilter(const UStruct* ObjectStruct, FName PropertyName) const;` — Checks if a property passes the PermissionList/DenyList filtering specified by PropertyPermissionLists This should be relatively fast as it maintains a flattened cache of all inherited PermissionLists for every UStruct (which is generated lazily).
- L114 _public prototype_ `bool DoesDetailTreeNodePassFilter(const UStruct* ObjectStruct, TSharedRef<FDetailTreeNode> DetailTreeNode);` — Checks if a given detail tree node passes the filters. This is more flexible than the above function but should only be considered for advanced use cases, such as dynamically generated rows from customizations that don't fit the structure of simply checking against an FName.
- L117 _public prototype_ `bool HasSpecificList(const UStruct* ObjectStruct) const;`
- L120 _public prototype_ `bool IsSpecificPropertyAllowListed(const UStruct* ObjectStruct, FName PropertyName) const;` — Check whether a property exists on the PermissionList for a specific Struct - this will return false if the property is AllowListed on a parent Struct
- L122 _public prototype_ `bool IsSpecificPropertyDenyListed(const UStruct* ObjectStruct, FName PropertyName) const;` — Check whether a property exists on the DenyList for a specific Struct - this will return false if the property is DenyListed on a parent Struct
- L125 _public function_ `const TMap<TSoftObjectPtr<const UStruct>, FPropertyPermissionListEntry>& GetRawPermissionList() const` — Gets a read-only reference to the original, un-flattened PermissionList.
- L128 _public prototype_ `void ClearCache();` — Clear CachedPropertyPermissionList to cause the PermissionListed property list to be regenerated next time it's queried
- L131 _public prototype_ `TSharedPtr<const FNamePermissionList> GetCachedPermissionListForStructIfEnabled(const UStruct* Struct) const;` — Gets a read-only reference to the cached permission list for the given struct, or null if the filtering is disabled. A non-null value will remain valid to read, but the info in it may become stale if this struct is re-cached because its raw rules change.
- L134 _public member_ `bool bSuppressUpdateDelegate = false;` — If true, PermissionListUpdatedDelegate will not broadcast when modifying the permission lists
- L136 _public function_ `const FDelegateEnablePathFilter& DelegateEnablePathFilter()`
- L139 _protected prototype_ `FPropertyPermissionList();`
- L140 _protected prototype_ `~FPropertyPermissionList();`
- L143 _private prototype_ `bool Tick(float DeltaTime);`
- L144 _private prototype_ `void OnObjectPostCDOCompiled(UObject* CDO, const FObjectPostCDOCompiledContext& Context);`
- L147 _private prototype_ `void ClearCacheAndQueueBroadcast_NoLock(TSoftObjectPtr<const UStruct> ObjectStruct = nullptr, FName OwnerName = NAME_None);` — Reset the cache and queue a broadcast. You must hold a write lock on PermissionListRW before calling this function!
- L150 _private prototype_ `void ClearCacheForClass_NoLock(const UClass* Class);` — Clear the given class (and any derived classes) from the cache. You must hold a write lock on PermissionListRW before calling this function!
- L153 _private member_ `FDelegateEnablePathFilter EnablePermissionList;` — Delegate to return whether DoesPropertyPassFilter should perform its PermissionList check or always return true
- L156 _private member_ `TMap<TSoftObjectPtr<const UStruct>, FPropertyPermissionListEntry> RawPropertyPermissionList;` — Stores assigned PermissionLists from AddPermissionList(), which are later flattened and stored in CachedPropertyPermissionList.
- L157 _private member_ `TMap<TSoftObjectPtr<const UStruct>, FCustomDetailTreeNodePermissionDelegate> CustomDetailTreeNodePermissionDelegates;`
- L160 _private member_ `FTSTicker::FDelegateHandle OnTickHandle;` — Handle for our tick function
- L169 _private member_ `TSet< FPermissionListUpdate > PendingUpdates;`
- L183 _private member_ `mutable TMap<TWeakObjectPtr<const UStruct>, TSharedRef<const FCachedPermissionList>> CachedPropertyPermissionList;` — Lazily-constructed combined cache of both the flattened class PermissionList and struct PermissionList
- L186 _private member_ `mutable FRWLock PermissionListRW;` — Protects RawPropertyPermissionList, CachedPropertyPermissionList, and PendingUpdates
- L189 _private prototype_ `TSharedRef<const FCachedPermissionList> GetCachedPermissionListEntryForStruct(const UStruct* Struct) const;` — Get or create the cached PermissionList for a specific UStruct

#### struct `FPropertyPermissionList::FPermissionListUpdate`  
`struct FPermissionListUpdate`  
_L162-166_
- L164 _public member_ `TSoftObjectPtr<const UStruct> ObjectStruct;`
- L165 _public member_ `FName OwnerName;`

#### struct `FPropertyPermissionList::FCachedPermissionList`  
`struct FCachedPermissionList`  
_L171-181_
- L173 _public function_ `FCachedPermissionList(FNamePermissionList&& InPermissionList, EPropertyPermissionListRules InRules) : PermissionList(MakeShared<FNamePermissionList>(MoveTemp(InPermissionList))) , Rules(InRules)`
- L179 _public member_ `TSharedRef<const FNamePermissionList> PermissionList;`
- L180 _public member_ `EPropertyPermissionListRules Rules = EPropertyPermissionListRules::UseExistingPermissionList;`

#### class `FPropertyEditorPermissionList`  
`class FPropertyEditorPermissionList : public FPropertyPermissionList`  
_L192-214_
- inherits: `FPropertyPermissionList`
- L195 _public prototype_ `static FPropertyEditorPermissionList& Get();`
- L198 _public function_ `bool ShouldShowMenuEntries() const` — Whether the Details View should show special menu entries to add/remove items in the PermissionList
- L200 _public function_ `void SetShouldShowMenuEntries(bool bShow)` — Turn on or off menu entries to modify the PermissionList from a Details View
- L202 _public function_ `void SetIsEnabledForPackageDelegate(const FIsEnabledForPackage& InIsEnabledForPackage )` — Set the delegate that is called in IsEnabledForPackage
- L204 _public prototype_ `bool IsEnabledForPackage(const UPackage* Package) const;` — A special call to disable the filter for a specific blueprint, if the IsEnabledForPackageDelegate is set and returns false
- L207 _private prototype_ `FPropertyEditorPermissionList() = default;`
- L208 _private prototype_ `~FPropertyEditorPermissionList() = default;`
- L210 _private member_ `FIsEnabledForPackage IsEnabledForPackageDelegate;`
- L213 _private member_ `bool bShouldShowMenuEntries = false;` — Whether SDetailSingleItemRow should add menu items to add/remove properties to/from the PermissionList

#### class `FHiddenPropertyPermissionList`  
`class FHiddenPropertyPermissionList : public FPropertyPermissionList`  
_L216-223_
- inherits: `FPropertyPermissionList`
- L219 _public prototype_ `static FHiddenPropertyPermissionList& Get();`
- L221 _private prototype_ `FHiddenPropertyPermissionList() = default;`
- L222 _private prototype_ `~FHiddenPropertyPermissionList() = default;`

#### class `FEnumValuePermissionList`  
`class FEnumValuePermissionList`  
_L225-255_
- L229 _public prototype_ `void AddPermissionList(TSoftObjectPtr<const UEnum> Enum, const FNamePermissionList& PermissionList);` — Add a set of rules for a specific UEnum to determine which values are visible in all details panels
- L231 _public prototype_ `void RemovePermissionList(TSoftObjectPtr<const UEnum> Enum);` — Remove a set of rules for a specific UEnum to determine which values are visible in all details panels
- L233 _public prototype_ `void ClearPermissionList();` — Remove all rules
- L236 _public prototype_ `bool DoesEnumValuePassFilter(const UEnum* Enum, FName ValueName) const;` — Check whether the specified value is permitted for the provided UEnum
- L239 _public prototype_ `bool HasFiltering(const UEnum* Enum) const;` — Checks if the provided enum has any entries in the permission list and returns true in that case.
- L242 _public function_ `bool IsEnabled() const` — When false, DoesEnumValuePassFilter will always return true.
- L244 _public function_ `void SetEnabled(bool bEnable)` — Turn on or off the enum PermissionList. When off, DoesEnumValuePassFilter will always return true.
- L247 _public function_ `const TMap<TSoftObjectPtr<const UEnum>, FNamePermissionList>& GetRawPermissionList() const` — Gets a read-only copy of the original, un-flattened PermissionList.
- L249 _public prototype_ `static FEnumValuePermissionList& Get();`
- L252 _private member_ `TMap<TSoftObjectPtr<const UEnum>, FNamePermissionList> PermissionList;`
- L254 _private member_ `bool bEnablePermissionList = false;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API PROPERTYEDITOR_API`
- L15 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPropertyEditorPermissionList, Log, All);`
- L15 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPropertyEditorPermissionList, Log, All);`
- L18 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FPermissionListUpdated, TSoftObjectPtr<const UStruct>, FName);` — Struct, OwnerName
- L18 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FPermissionListUpdated, TSoftObjectPtr<const UStruct>, FName);` — Struct, OwnerName
- L19 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsEnabledForPackage, const UPackage*);`
- L19 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsEnabledForPackage, const UPackage*);`
- L20 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TOptional<bool>, FCustomDetailTreeNodePermissionDelegate, TSharedRef<FDetailTreeNode> DetailTreeNode);`
- L20 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TOptional<bool>, FCustomDetailTreeNodePermissionDelegate, TSharedRef<FDetailTreeNode> DetailTreeNode);`

### `Source/Editor/PropertyEditor/Public/PropertyRestriction.h` (Public)


#### class `FPropertyRestriction`  
`class FPropertyRestriction`  
_L14-56_
- L18 _public function_ `FPropertyRestriction(const FText& InReason) : Reason(InReason)`
- L23 _public function_ `const FText& GetReason() const`
- L25 _public prototype_ `bool IsValueHidden(const FString& Value) const;`
- L26 _public prototype_ `bool IsValueDisabled(const FString& Value) const;`
- L27 _public prototype_ `void AddHiddenValue(FString Value);`
- L28 _public prototype_ `void AddDisabledValue(FString Value);`
- L29 _public prototype_ `void AddClassFilter(TSharedRef<IClassViewerFilter> ClassFilter);`
- L31 _public prototype_ `void RemoveHiddenValue(FString Value);`
- L32 _public prototype_ `void RemoveDisabledValue(FString Value);`
- L33 _public prototype_ `void RemoveClassFilter(TSharedRef<IClassViewerFilter> ClassFilter);`
- L34 _public prototype_ `void RemoveAll();`
- L36 _public function_ `TArray<FString>::TConstIterator GetHiddenValuesIterator() const`
- L41 _public function_ `TArray<FString>::TConstIterator GetDisabledValuesIterator() const`
- L46 _public function_ `TArray<TSharedRef<IClassViewerFilter>>::TConstIterator GeClassViewFilterIterator() const`
- L52 _private member_ `TArray<FString> HiddenValues;`
- L53 _private member_ `TArray<FString> DisabledValues;`
- L54 _private member_ `TArray<TSharedRef<IClassViewerFilter>> ClassViewFilter;`
- L55 _private member_ `FText Reason;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API PROPERTYEDITOR_API`

### `Source/Editor/PropertyEditor/Public/SDetailsSplitter.h` (Public)


#### class `SDetailsSplitter`  
`class SDetailsSplitter : public SCompoundWidget`  
_L11-94_
- inherits: `SCompoundWidget`
- desc: Splitter that allows you to provide an FAsyncDetailViewDiff to connect like-properties between two or more details panels
- L40 _public prototype_ `static FSlot::FSlotArguments Slot();`
- L42 _public function_ `SLATE_BEGIN_ARGS(SDetailsSplitter)`
- L44 _public prototype_ `SLATE_EVENT(FRowHighlightColor, RowHighlightColor)` — default cyan: FLinearColor(0.f, 1.f, 1.f, .7f)
- L51 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L55 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L56 _public prototype_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;`
- L57 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L59 _public prototype_ `void AddSlot(const FSlot::FSlotArguments& SlotArgs, int32 Index = INDEX_NONE);`
- L60 _public prototype_ `FPanel& GetPanel(int32 Index);`
- L62 _public prototype_ `void SetRowHighlightColorDelegate(const FRowHighlightColor& Delegate);`
- L64 _public prototype_ `void HighlightFromMergeResults(const TMap<FString, TMap<FPropertySoftPath, ETreeDiffResult>>& Highlights);` — generate a highlight color delegate that utilizes the merge results to determine the color
- L83 _private prototype_ `void PaintPropertyConnector(FSlateWindowElementList& OutDrawElements, int32 LayerId, const FSlateRect& LeftPropertyRect, const FSlateRect& RightPropertyRect, const FLinearColor& FillColor, const FLinearColor& OutlineColor) const;`
- L86 _private prototype_ `void PaintCopyPropertyButton(FSlateWindowElementList& OutDrawElements, int32 LayerId, const TUniquePtr<FAsyncDetailViewDiff::DiffNodeType>& DiffNode, const FSlateRect& LeftPropertyRect, const FSlateRect& RightPropertyRect, EPropertyCopyDirection CopyDirection) const;`
- L89 _private member_ `TSharedPtr<SSplitter> Splitter;`
- L90 _private member_ `TArray<FPanel> Panels;`
- L91 _private member_ `FCopyPropertyButton HoveredCopyButton;`
- L92 _private member_ `FRowHighlightColor GetRowHighlightColor;`
- L93 _private member_ `FShouldHighlightRow GetShouldHighlightRow;`

#### class `SDetailsSplitter::FSlot`  
`class FSlot : public TSlotBase<FSlot>`  
_L19-32_
- inherits: `TSlotBase<FSlot>`
- L22 _public prototype_ `FSlot() = default;`

#### struct `SDetailsSplitter::FPanel`  
`struct FPanel`  
_L33-39_
- L35 _public member_ `TSharedPtr<IDetailsView> DetailsView;`
- L36 _public member_ `TAttribute<bool> IsReadonly;`
- L37 _public member_ `TAttribute<TSharedPtr<FAsyncDetailViewDiff>> DiffRight;`
- L38 _public member_ `FShouldIgnoreRow ShouldIgnoreRow;`

#### enum `SDetailsSplitter::EPropertyCopyDirection`  
`enum class EPropertyCopyDirection`  
_L68-73_
- L70 _public enumerator_ `Copy_None`
- L71 _public enumerator_ `CopyLeftToRight`
- L72 _public enumerator_ `CopyRightToLeft`

#### struct `SDetailsSplitter::FCopyPropertyButton`  
`struct FCopyPropertyButton`  
_L75-81_
- L77 _public member_ `TWeakPtr<FDetailTreeNode> SourceDetailsNode;`
- L78 _public member_ `TWeakPtr<FDetailTreeNode> DestinationDetailsNode;`
- L79 _public member_ `ETreeDiffResult DiffResult = ETreeDiffResult::Invalid;`
- L80 _public member_ `EPropertyCopyDirection CopyDirection = EPropertyCopyDirection::Copy_None;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PROPERTYEDITOR_API`
- L15 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FShouldIgnoreRow, const TWeakPtr<FDetailTreeNode>&) DECLARE_DELEGATE_RetVal_OneParam(FLinearColor, FRowHighlightColor, const TUniquePtr<FAsyncDetailViewDiff::DiffNodeType>&) DECLARE_DELEGATE_RetVal_OneParam(bool, FShouldHighlightRow, const TUniquePtr<FAsyncDetailViewDiff::DiffNodeType>&) class FSlot : public TSlotBase<FSlot> { public: FSlot() = default; SLATE_SLOT_BEGIN_ARGS(FSlot, TSlotBase<FSlot>) SLATE_ATTRIBUTE(float, Value) SLATE_ARGUMENT(TSharedPtr<IDetailsView>, DetailsView) SLATE_ATTRIBUTE(bool, IsReadonly)` — Callback that's called before highlighting a row. If true, the row is skipped.
- L16 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FLinearColor, FRowHighlightColor, const TUniquePtr<FAsyncDetailViewDiff::DiffNodeType>&) DECLARE_DELEGATE_RetVal_OneParam(bool, FShouldHighlightRow, const TUniquePtr<FAsyncDetailViewDiff::DiffNodeType>&) class FSlot : public TSlotBase<FSlot> { public: FSlot() = default; SLATE_SLOT_BEGIN_ARGS(FSlot, TSlotBase<FSlot>) SLATE_ATTRIBUTE(float, Value) SLATE_ARGUMENT(TSharedPtr<IDetailsView>, DetailsView) SLATE_ATTRIBUTE(bool, IsReadonly)`
- L17 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FShouldHighlightRow, const TUniquePtr<FAsyncDetailViewDiff::DiffNodeType>&) class FSlot : public TSlotBase<FSlot> { public: FSlot() = default; SLATE_SLOT_BEGIN_ARGS(FSlot, TSlotBase<FSlot>) SLATE_ATTRIBUTE(float, Value) SLATE_ARGUMENT(TSharedPtr<IDetailsView>, DetailsView) SLATE_ATTRIBUTE(bool, IsReadonly)`

### `Source/Editor/PropertyEditor/Public/SPerQualityLevelPropertiesWidget.h` (Public)


#### class `SOverridePropertiesWidget`  
`class SOverridePropertiesWidget : public SCompoundWidget`  
_L15-60_
- inherits: `SCompoundWidget`
- L18 _public typedef_ `typedef typename TSlateDelegates<FName>::FOnGenerateWidget FOnGenerateWidget;`
- L20 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnOverrideAction, FName);`
- L22 _public function_ `SLATE_BEGIN_ARGS(SOverridePropertiesWidget) : _OnGenerateWidget()`
- L26 _public prototype_ `SLATE_EVENT(FOnGenerateWidget, OnGenerateWidget) SLATE_EVENT(FOnOverrideAction, OnAddEntry) SLATE_EVENT(FOnOverrideAction, OnRemoveEntry) SLATE_ATTRIBUTE(TArray<FName>, EntryNames) SLATE_END_ARGS() virtual void Construct(const typename SOverridePropertiesWidget::FArguments& InArgs);`
- L42 _protected prototype_ `virtual void ConstructChildren() = 0;`
- L44 _protected prototype_ `TSharedRef<SWidget> MakeOverrideWidget(FName InName, FText InDisplayText, const TArray<FName>& InEntries, FMenuBuilder& InAddMenuBuilder);`
- L46 _protected prototype_ `void AddEntry(FName EntryName);`
- L48 _protected prototype_ `FReply RemoveEntry(FName EntryName);`
- L50 _protected prototype_ `void AddEntryToMenu(const FName& EntryName, const FTextFormat Format, FMenuBuilder& AddEntryMenuBuilder);`
- L52 _protected member_ `FOnGenerateWidget OnGenerateWidget;`
- L53 _protected member_ `FOnOverrideAction OnAddEntry;`
- L54 _protected member_ `FOnOverrideAction OnRemoveEntry;`
- L55 _protected member_ `TAttribute<TArray<FName>> EntryNames;`
- L56 _protected member_ `int32 LastEntryNames;`
- L57 _protected member_ `bool bAddedMenuItem;`
- L59 _protected member_ `FString ToolTip;`

#### class `SPerQualityLevelPropertiesWidget`  
`class SPerQualityLevelPropertiesWidget : public SOverridePropertiesWidget`  
_L65-74_
- inherits: `SOverridePropertiesWidget`
- desc: SPerQualityLevelPropertiesWidget
- L69 _public prototype_ `virtual void Construct(const typename SPerQualityLevelPropertiesWidget::FArguments& InArgs);`
- L72 _protected prototype_ `virtual void ConstructChildren() override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API PROPERTYEDITOR_API`
- L20 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnOverrideAction, FName);`

### `Source/Editor/PropertyEditor/Public/SResetToDefaultMenu.h` (Public)


#### class `SResetToDefaultMenu`  
`class SResetToDefaultMenu : public SCompoundWidget`  
_L29-106_
- inherits: `SCompoundWidget`
- desc: Displays a reset to default menu for a set of properties Will hide itself automatically when all of the properties being observed are already at their default values
- L33 _public function_ `SLATE_BEGIN_ARGS( SResetToDefaultMenu ) : _VisibilityWhenDefault( EVisibility::Hidden ) , _DiffersFromDefault( false )`
- L41 _public prototype_ `SLATE_ARGUMENT( EVisibility, VisibilityWhenDefault ) SLATE_ATTRIBUTE( bool, DiffersFromDefault ) SLATE_ARGUMENT(FSimpleDelegate, OnResetToDefault) SLATE_ARGUMENT(FOnGetResetToDefaultText, OnGetResetToDefaultText) SLATE_END_ARGS() void Construct( const FArguments& InArgs );` — The visibility of this widget when the value is default and the reset to default option does need to be shown
- L63 _public prototype_ `void AddProperty( TSharedRef<class IPropertyHandle> InProperty );` — Adds a new property to the menu that is displayed when a user clicks the reset to default button @param InProperty	The property handle to display
- L66 _private prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;`
- L71 _private prototype_ `EVisibility GetResetToDefaultVisibility() const;` — @return The visibility of the reset to default widget
- L76 _private prototype_ `TSharedRef<class SWidget> OnGenerateResetToDefaultMenuContent();` — Called when the menu is open to regenerate the default menu content
- L81 _private prototype_ `void ResetToDefault();` — Resets property to default, only used when our property handle is not valid.
- L86 _private prototype_ `void ResetAllToDefault();` — Resets all properties to default
- L90 _private member_ `TArray< TSharedRef<class IPropertyHandle> > Properties;` — Properties that should be displayed in the menu
- L93 _private member_ `EVisibility VisibilityWhenDefault;` — The visibility to use when the properties are already the default
- L96 _private member_ `bool bShouldBeVisible;` — Whether or this menu should be visible
- L99 _private member_ `TAttribute<bool> DiffersFromDefault;` — Attribute used to determine whether we are different from the default
- L102 _private member_ `FSimpleDelegate OnResetToDefault;` — Delegate fired when we reset to default - only used when we don't have a property handle
- L105 _private member_ `FOnGetResetToDefaultText OnGetResetToDefaultText;` — Delegate used to get the text to display when resetting our value - only used when we don't have a property handle

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API PROPERTYEDITOR_API`
- L23 _delegate_ `DECLARE_DELEGATE_RetVal(FText, FOnGetResetToDefaultText);` — Delegate used to get the text to display when resetting our value This will only be used when we are not using a property handle.
- L23 _prototype_ `DECLARE_DELEGATE_RetVal(FText, FOnGetResetToDefaultText);` — Delegate used to get the text to display when resetting our value This will only be used when we are not using a property handle.

### `Source/Editor/PropertyEditor/Public/SResetToDefaultPropertyEditor.h` (Public)


#### class `SResetToDefaultPropertyEditor`  
`class SResetToDefaultPropertyEditor : public SCompoundWidget`  
_L21-55_
- inherits: `SCompoundWidget`
- desc: Widget showing the reset to default value button
- L25 _public function_ `SLATE_BEGIN_ARGS( SResetToDefaultPropertyEditor ) : _NonVisibleState( EVisibility::Hidden )`
- L28 _public prototype_ `SLATE_ARGUMENT( EVisibility, NonVisibleState ) SLATE_ARGUMENT( TOptional<FResetToDefaultOverride>, CustomResetToDefault ) SLATE_END_ARGS() ~SResetToDefaultPropertyEditor();`
- L34 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedPtr< class IPropertyHandle>& InPropertyHandle );`
- L37 _private prototype_ `FText GetResetToolTip() const;`
- L39 _private prototype_ `EVisibility GetDiffersFromDefaultAsVisibility() const;`
- L41 _private prototype_ `void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime );`
- L43 _private prototype_ `FReply OnResetClicked();`
- L45 _private prototype_ `void UpdateDiffersFromDefaultState();`
- L48 _private member_ `TOptional<FResetToDefaultOverride> OptionalCustomResetToDefault;`
- L50 _private member_ `TSharedPtr< class IPropertyHandle > PropertyHandle;`
- L52 _private member_ `EVisibility NonVisibleState;`
- L54 _private member_ `bool bValueDiffersFromDefault;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API PROPERTYEDITOR_API`

### `Source/Editor/PropertyEditor/Public/SStandaloneCustomizedValueWidget.h` (Public)


#### class `SStandaloneCustomizedValueWidget`  
`class SStandaloneCustomizedValueWidget : public SCompoundWidget, public IPropertyTypeCustomizationUtils`  
_L19-38_
- inherits: `SCompoundWidget,IPropertyTypeCustomizationUtils`
- desc: Generates the header widget for a customized struct or other type. This widget is generally used in the property editor to display a struct as a single row, like with an FColor. Properties passed in that do not have a header customization will return a null widget.
- L22 _public function_ `SLATE_BEGIN_ARGS( SStandaloneCustomizedValueWidget )`
- L25 _public prototype_ `SLATE_ARGUMENT( TSharedPtr<FDetailCategoryImpl>, ParentCategory) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<IPropertyTypeCustomization> InCustomizationInterface, TSharedRef<IPropertyHandle> InPropertyHandle);` — Optional Parent Detail Category, useful to access Thumbnail Pool.
- L31 _public prototype_ `virtual TSharedPtr<FAssetThumbnailPool> GetThumbnailPool() const override;`
- L34 _private member_ `TWeakPtr<FDetailCategoryImpl> ParentCategory;`
- L35 _private member_ `TSharedPtr<IPropertyTypeCustomization> CustomizationInterface;`
- L36 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;`
- L37 _private member_ `TSharedPtr<FDetailWidgetRow> CustomPropertyWidget;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API PROPERTYEDITOR_API`

### `Source/Editor/PropertyEditor/Public/UserInterface/Categories/CategoryMenuComboButtonBuilder.h` (Public)


#### class `FCategoryMenuComboButtonBuilder`  
`class FCategoryMenuComboButtonBuilder : public FToolElementRegistrationArgs`  
_L14-68_
- inherits: `FToolElementRegistrationArgs`
- L21 _public member_ `FOnGetContent OnGetContent;` — the delegate to get the menu content
- L27 _public prototype_ `FCategoryMenuComboButtonBuilder( TSharedRef<FDetailsDisplayManager> InDetailsDisplayManager );` — The constructor, which takes a @code TSharedRef<FDetailsDisplayManager> @endcode to initialize the Details Display Manager
- L32 _public prototype_ `FCategoryMenuComboButtonBuilder& Set_OnGetContent(FOnGetContent InOnGetContent);` — Set the OnGetContent for the menu that this button is responsible for
- L37 _public prototype_ `FCategoryMenuComboButtonBuilder& Bind_IsVisible(TAttribute<EVisibility> InIsVisible);` — Set the IsVisible delegate for the menu that this button is responsible for
- L40 _public prototype_ `virtual TSharedPtr<SWidget> GenerateWidget() override;` — Implements the generation of the Category Menu button SWidget
- L50 _public prototype_ `TSharedRef<SWidget> operator*();` — Converts this into the SWidget it builds
- L57 _private member_ `TSharedRef<FDetailsDisplayManager> DisplayManager;` — The @code DetailsDisplayManager @endcode which provides an API to manage some of the characteristics of the details display
- L62 _private member_ `TAttribute<EVisibility> IsRowHoveredOver;` — An attribute indicating whether the current row is hovered over
- L67 _private member_ `TAttribute<EVisibility> IsVisible;` — the attribute which tells whether this menu button is visible

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_DELEGATE_OneParam(FGetIsRowHoveredOver, bool) class FCategoryMenuComboButtonBuilder : public FToolElementRegistrationArgs { public: FOnGetContent OnGetContent; FCategoryMenuComboButtonBuilder( TSharedRef<FDetailsDisplayManager> InDetailsDisplayManager ); FCategoryMenuComboButtonBuilder& Set_OnGetContent(FOnGetContent InOnGetContent); FCategoryMenuComboButtonBuilder& Bind_IsVisible(TAttribute<EVisibility> InIsVisible); virtual TSharedPtr<SWidget> GenerateWidget() override; virtual ~FCategoryMenuComboButtonBuilder() override; TSharedRef<SWidget> operator*();`

### `Source/Editor/PropertyEditor/Public/UserInterface/PropertyTable/PropertyTableConstants.h` (Public)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace PropertyTableConstants`
- L8 _variable_ `static const FName NormalFontStyle( TEXT("Prope` (scope `PropertyTableConstants`)
- L9 _variable_ `static const FName BoldFontStyle( TEXT("Prope` (scope `PropertyTableConstants`)
- L10 _variable_ `static const FName FilterFontStyle( TEXT("Prope` (scope `PropertyTableConstants`)

### `Source/Editor/PropertyEditor/Public/UserInterface/Widgets/OverridesComboButtonBuilder.h` (Public)


#### class `FOverridesComboButtonBuilder`  
`class FOverridesComboButtonBuilder : public FPropertyUpdatedWidgetBuilder`  
_L19-101_
- inherits: `FPropertyUpdatedWidgetBuilder`
- desc: A Display builder for the overrides combo button
- L26 _public member_ `FOnGetContent OnGetContent;` — the delegate to get the menu content
- L36 _public prototype_ `FOverridesComboButtonBuilder( TSharedRef<FDetailsDisplayManager> InDetailsDisplayManager, bool bInIsCategoryOverridesComboButton, TWeakObjectPtr<UObject> InObject );` — The constructor, which takes a @code TSharedRef<FDetailsDisplayManager> @endcode to initialize the Details Display Manager @param InDetailsDisplayManager the FDetailsDisplayManager which manages the details display @param bInIsCategoryOverridesComboButton if true, this FOverridesComboButtonBuilder is for a Category rather than a property row
- L44 _public prototype_ `FOverridesComboButtonBuilder& Set_OnGetContent(FOnGetContent InOnGetContent);` — Set the OnGetContent for the menu that this button is responsible for
- L49 _public prototype_ `void SetEditPropertyChain(TSharedRef<FEditPropertyChain>& InEditPropertyChain);` — Sets the FEditPropertyChain for this FOverridesComboButtonBuilder
- L54 _public prototype_ `TSharedPtr<FEditPropertyChain> GetEditPropertyChain() const;` — Gets the FEditPropertyChain for this FOverridesComboButtonBuilder
- L59 _public prototype_ `virtual TSharedPtr<SWidget> GenerateWidget() override;` — Implements the generation of the Category Menu button SWidget
- L69 _public prototype_ `TSharedRef<SWidget> operator*();` — Converts this into the SWidget it builds
- L77 _private member_ `TSharedRef<FDetailsDisplayManager> DisplayManager;` — The @code DetailsDisplayManager @endcode which provides an API to manage some of the characteristics of the details display
- L82 _private member_ `bool bIsCategoryOverridesComboButton;` — if true, this is an overrides combo button for a Category
- L87 _private member_ `TWeakObjectPtr<UObject> Object;` — The UObject that will be queried for its override state
- L93 _private member_ `TSharedPtr<FEditPropertyChain> EditPropertyChain;` — If this is a ComboButton builder for a Property, this will point to the FEditPropertyChain for that Property, else it will be nullptr
- L99 _private member_ `bool bIsCategory = true;` — if true this is a builder for an Overrides combo button for a Category, else it is a builder for Properties within a Category

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_DELEGATE_OneParam(FGetIsRowHoveredOver, bool) class FOverridesComboButtonBuilder : public FPropertyUpdatedWidgetBuilder { public: FOnGetContent OnGetContent; FOverridesComboButtonBuilder( TSharedRef<FDetailsDisplayManager> InDetailsDisplayManager, bool bInIsCategoryOverridesComboButton, TWeakObjectPtr<UObject> InObject ); FOverridesComboButtonBuilder& Set_OnGetContent(FOnGetContent InOnGetContent); void SetEditPropertyChain(TSharedRef<FEditPropertyChain>& InEditPropertyChain);`

### `Source/Editor/PropertyEditor/Public/UserInterface/Widgets/PropertyUpdatedWidgetBuilder.h` (Public)


#### class `FPropertyUpdatedWidgetBuilder`  
`class FPropertyUpdatedWidgetBuilder : public FToolElementRegistrationArgs`  
_L9-60_
- inherits: `FToolElementRegistrationArgs`
- L13 _public prototype_ `DECLARE_DELEGATE(FResetToDefault);`
- L18 _public prototype_ `FPropertyUpdatedWidgetBuilder();` — default constructor
- L23 _public prototype_ `FPropertyUpdatedWidgetBuilder& Bind_IsVisible(TAttribute<EVisibility> InIsVisible);` — Set the IsVisible delegate for the menu that this button is responsible for
- L30 _public prototype_ `FPropertyUpdatedWidgetBuilder& Set_ResetToDefault(FResetToDefault InResetToDefault);` — Sets the ResetToDefault delegate @param InResetToDefault the FResetToDefault delegate to set for this widget builder
- L35 _public prototype_ `FResetToDefault Get_ResetToDefault();` — returns the ResetToDefault delegate
- L42 _public prototype_ `void Bind_IsRowHovered(TAttribute<bool> InIsRowHoveredAttr);` — binds the IsRowHovered Attribute @param bInIsRowHoveredAttr the attribute which will determine if the row for this property is hovered
- L47 _public member_ `TAttribute<bool> IsRowHoveredAttr;` — If true, the row that this is associated with is currently hovered over
- L53 _protected member_ `TAttribute<EVisibility> IsVisible;` — the attribute which tells whether this menu button is visible
- L58 _protected member_ `FResetToDefault ResetToDefault;` — A delegate for resetting the active property row

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_DELEGATE(FResetToDefault);`

### `Source/Editor/PropertyEditor/Public/VariablePrecisionNumericInterface.h` (Public)


#### struct `FVariablePrecisionNumericInterface`  
`struct FVariablePrecisionNumericInterface : public TDefaultNumericTypeInterface<float>`  
_L12-38_
- inherits: `TDefaultNumericTypeInterface<float>`
- desc: FVariablePrecisionNumericInterface allow more precision as the numbers get closer to zero
- L14 _public function_ `FVariablePrecisionNumericInterface()`
- L17 _public function_ `virtual FString ToString(const float& Value) const override` — Convert the type to/from a string
