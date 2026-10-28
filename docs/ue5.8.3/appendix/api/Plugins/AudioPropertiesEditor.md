# Plugins / AudioPropertiesEditor

- module root: `Plugins/Experimental/AudioProperties/Source/AudioPropertiesEditor`
- headers: 17; symbols: 221
- symbol kinds: class=18, delegate=1, enum=1, enumerator=2, function=27, macro=2, member=55, namespace=3, prototype=107, struct=1, typedef=1, variable=3
- PrivateDependencyModuleNames: AssetDefinition, AudioEditor
- PublicDependencyModuleNames: AssetDefinition, AudioExtensions, AudioProperties, ContentBrowser, Core, CoreUObject, Engine, InputCore, PropertyEditor, Slate, SlateCore, StructUtilsEditor, ToolMenus, UnrealEd

### `Plugins/Experimental/AudioProperties/Source/AudioPropertiesEditor/Private/AssetDefinition_AudioPropertiesBindings.h` (Private)


#### class `UAssetDefinition_AudioPropertiesBindings`  
`class UAssetDefinition_AudioPropertiesBindings : public UAssetDefinitionDefault_AudioDiffable`  
_L12-23_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault_AudioDiffable`
- L18 _public function_ `virtual FText GetAssetDisplayName() const override`
- L19 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L20 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L21 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`

### `Plugins/Experimental/AudioProperties/Source/AudioPropertiesEditor/Private/AudioPropertiesDetailsInjectorUtils.h` (Private)


#### Free symbols / members of external scopes

- L13 _macro_ `#define LOCTEXT_NAMESPACE "AudioPropertiesDetailsInjectorUtils"`
- L15 _namespace_ `namespace AudioPropertiesDetailsInjectorUtils`
- L17 _variable_ `static const FLazyName EditConditionPropertyMetadata = "Ed` (scope `AudioPropertiesDetailsInjectorUtils`)
- L18 _variable_ `static const FLazyName InlineEditConditionTogglePropertyMetadata = "In` (scope `AudioPropertiesDetailsInjectorUtils`)
- L20 _function_ `inline const UObject* GetUObjectFromPtrPropertyHandle(const TSharedPtr<IPropertyHandle> InPropertyHandle, const UObject* PropertyOwner)` (scope `AudioPropertiesDetailsInjectorUtils`)
- L46 _function_ `inline bool ShouldParseProperty(const UObject* PropertyOwner, const TSharedPtr<IPropertyHandle> InPropertyHandle)` (scope `AudioPropertiesDetailsInjectorUtils`)
- L70 _function_ `inline void HandleLocalPropertyOverrideChange(UObject* PropertyOwner, const bool bIsPropertyOverriden, const TSharedPtr<IPropertyHandle> TargetPropertyHandle, const TSharedPtr<IPropertyHandle> PropertySheetHandle)` (scope `AudioPropertiesDetailsInjectorUtils`)
- L113 _function_ `inline TSharedRef<SWidget> GetSingleEditPropertyNameWidget(TSharedPtr<IPropertyHandle> PropertyHandle, const TSharedPtr<IPropertyHandle> PropertySheetHandle, const TArray<TWeakObjectPtr<UObject>>& ObjectsBeingCustomized)` (scope `AudioPropertiesDetailsInjectorUtils`)
- L140 _function_ `` (scope `AudioPropertiesDetailsInjectorUtils::GetSingleEditPropertyNameWidget`)
- L173 _function_ `inline TSharedRef<SWidget> GetMultiEditPropertyNameWidget(TSharedPtr<IPropertyHandle> PropertyHandle, const TSharedPtr<IPropertyHandle> PropertySheetHandle, const TArray<TWeakObjectPtr<UObject>>& ObjectsBeingCustomized)` (scope `AudioPropertiesDetailsInjectorUtils`)
- L187 _function_ `` (scope `AudioPropertiesDetailsInjectorUtils::GetMultiEditPropertyNameWidget`)
- L209 _function_ `` (scope `AudioPropertiesDetailsInjectorUtils::GetMultiEditPropertyNameWidget::__anon691790fb0502`)
- L247 _function_ `inline TSharedRef<SWidget> CreateOverriddenPropertyNameWidget(TSharedPtr<IPropertyHandle> PropertyHandle, const TSharedPtr<IPropertyHandle> PropertySheetHandle, const TArray<TWeakObjectPtr<UObject>>& ObjectsBeingCustomized)` (scope `AudioPropertiesDetailsInjectorUtils`)

### `Plugins/Experimental/AudioProperties/Source/AudioPropertiesEditor/Private/AudioPropertiesEditorLogCategory.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAudioPropertiesEditor, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAudioPropertiesEditor, Log, All);`

### `Plugins/Experimental/AudioProperties/Source/AudioPropertiesEditor/Private/AudioPropertiesSheetAssetBuilder.h` (Private)


#### struct `AudioPropertiesSheetAssetBuilder::FPropertyRequest`  
`struct FPropertyRequest`  
_L13-26_
- L15 _public member_ `const FProperty* CachedProperty;`
- L16 _public member_ `bool bInheritProperty;`
- L17 _public member_ `bool bInheritValue;`
- L19 _public function_ `FPropertyRequest(const FProperty* InCachedProperty, bool bInInheritProperty = false, bool bInInheritValue = false) : CachedProperty(InCachedProperty) , bInheritProperty(bInInheritProperty) , bInheritValue(bInInheritValue)`

#### enum `AudioPropertiesSheetAssetBuilder::ESourceObjectParsingType`  
`enum class ESourceObjectParsingType :uint8`  
_L28-32_
- L30 _public enumerator_ `UObject` — To parse UProperties found on the source UObject
- L31 _public enumerator_ `PropertySheet` — To parse from the property sheet contained on a source UAudioPropertiesSheetAsset

#### class `FAudioPropertiesSheetAssetBuilder`  
`class FAudioPropertiesSheetAssetBuilder`  
_L37-41_
- L40 _public prototype_ `static void BuildPropertySheetFromPropertyDataArray(const UObject* SourceObject, const UAudioPropertiesSheetAsset* ParentSheet, TArrayView<AudioPropertiesSheetAssetBuilder::FPropertyRequestPtr> InPropertyData, AudioPropertiesSheetAssetBuilder::ESourceObjectParsingType ParsingType = AudioPropertiesSheetAssetBuilder::ESourceObjectParsingType::UObject);`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace AudioPropertiesSheetAssetBuilder`
- L34 _typedef_ `using FPropertyRequestPtr = TSharedPtr<FPropertyRequest>;` (scope `AudioPropertiesSheetAssetBuilder`)

### `Plugins/Experimental/AudioProperties/Source/AudioPropertiesEditor/Private/AudioPropertiesSheetAssetDetails.h` (Private)


#### class `FAudioPropertiesSheetAssetDetails`  
`class FAudioPropertiesSheetAssetDetails : public IDetailCustomization`  
_L8-20_
- inherits: `IDetailCustomization`
- L12 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L16 _private prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L19 _private prototype_ `void BuildPropertiesParserRow(IDetailLayoutBuilder& DetailBuilder);` — Allows to select the local parser and shows the inherited one in case local is null

### `Plugins/Experimental/AudioProperties/Source/AudioPropertiesEditor/Private/AudioPropertiesSheetBuilderInstantiator.h` (Private)


#### class `FAudioPropertiesSheetBuilderInstantiator`  
`class FAudioPropertiesSheetBuilderInstantiator : public TSharedFromThis<FAudioPropertiesSheetBuilderInstantiator>`  
_L11-20_
- inherits: `TSharedFromThis<FAudioPropertiesSheetBuilderInstantiator>`
- L14 _public prototype_ `void ExtendContentBrowserSelectionMenu();`
- L17 _private prototype_ `void ExecuteCreateBuilderWidget(const FToolMenuContext& MenuContext);`
- L18 _private prototype_ `void CreateBuilderWidget(TArrayView<TSoftObjectPtr<UObject>> SourceObjects);`
- L19 _private prototype_ `void SourceObjectAsyncLoadComplete(TSoftObjectPtr<UObject> LoadedObject);`

### `Plugins/Experimental/AudioProperties/Source/AudioPropertiesEditor/Private/AudioPropertiesSheetDetails.h` (Private)


#### class `FAudioPropertiesSheetDetails`  
`class FAudioPropertiesSheetDetails : public IPropertyTypeCustomization`  
_L13-23_
- inherits: `IPropertyTypeCustomization`
- desc: Details Customization of an AudioPropertiesSheetAsset
- L17 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L20 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;` — ~Begin IPropertyTypeCustomization interface
- L21 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildrenBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`

#### class `FAudioPropertiesSheetBagNodeBuilder`  
`class FAudioPropertiesSheetBagNodeBuilder : public IDetailCustomNodeBuilder, public TSharedFromThis<FAudioPropertiesSheetBagNodeBuilder>`  
_L26-57_
- inherits: `IDetailCustomNodeBuilder,TSharedFromThis<FAudioPropertiesSheetBagNodeBuilder>`
- desc: Creates a property node showing the local property bag + any properties inherited from the parent tree
- L29 _public prototype_ `FAudioPropertiesSheetBagNodeBuilder( TSharedPtr<IPropertyHandle> InPropertySheetStructHandle, TSharedPtr<IPropertyUtilities> InPropertyUtils, FAudioPropertiesSheet* InLeafMostSheet = nullptr );`
- L35 _public prototype_ `void GenerateChildContent( IDetailChildrenBuilder& ChildrenBuilder )override;`
- L36 _public prototype_ `void GenerateHeaderRowContent(FDetailWidgetRow& NodeRow) override;`
- L38 _public prototype_ `FName GetName() const override;`
- L40 _public prototype_ `void OnParentAssetPropertyOverrideChange(const FProperty& TargetProperty, bool bIsOverridden);`
- L44 _private prototype_ `void AddParentTreePropertyBags(IDetailChildrenBuilder& ChildrenBuilder);`
- L46 _private prototype_ `TSharedRef<SWidget> BuildHeaderRowName() const;`
- L47 _private prototype_ `TSharedRef<SWidget> BuildHeaderRowValue();`
- L49 _private member_ `TSharedPtr<IPropertyHandle> CachedSheetStructHandle;`
- L50 _private member_ `TSharedPtr<IPropertyHandle> ParentPropertyHandle;`
- L52 _private member_ `TSharedPtr<IPropertyUtilities> CachedPropertyUtils;`
- L53 _private member_ `FAudioPropertiesSheet* LeafMostSheet;`
- L55 _private member_ `TSharedPtr<class IPropertyChangeListener> PropertyChangeListener;`

#### class `FAudioPropertiesSheetAssetTreeNodeBuilder`  
`class FAudioPropertiesSheetAssetTreeNodeBuilder : public IDetailCustomNodeBuilder, public TSharedFromThis<FAudioPropertiesSheetAssetTreeNodeBuilder>`  
_L60-105_
- inherits: `IDetailCustomNodeBuilder,TSharedFromThis<FAudioPropertiesSheetAssetTreeNodeBuilder>`
- desc: Creates a property node showing the property sheet inheritance tree
- L63 _public prototype_ `FAudioPropertiesSheetAssetTreeNodeBuilder( TSharedPtr<IPropertyHandle> InPropertySheetStructHandle, TSharedPtr<IPropertyHandle> InChildPtrToThisContainer, FAudioPropertiesSheet* InLeafMostSheet = nullptr, bool InIsLeaf = false);`
- L69 _public prototype_ `void GenerateHeaderRowContent(FDetailWidgetRow& NodeRow) override;`
- L70 _public prototype_ `void GenerateChildContent(IDetailChildrenBuilder& ChildrenBuilder) override;`
- L72 _public function_ `virtual void SetOnRebuildChildren(FSimpleDelegate InOnRegenerateChildren) override`
- L74 _public prototype_ `FName GetName() const override;`
- L76 _public member_ `FSimpleDelegate OnRebuildChildren;`
- L79 _private prototype_ `TSharedRef<SWidget> BuildParentPickerWidget();`
- L80 _private prototype_ `TSharedRef<SWidget> BuildHeaderRowName() const;`
- L81 _private prototype_ `TSharedRef<SWidget> BuildHeaderRowValue(const UObject* PropertyOwner, const bool InBuildAssetPicker);`
- L82 _private prototype_ `TSharedRef<SToolTip> CreatePathTooltip(const UObject* TargetObject);`
- L84 _private prototype_ `void AddParentNode(IDetailChildrenBuilder& ChildrenBuilder);`
- L86 _private member_ `TSharedPtr<IPropertyHandle> CachedSheetStructHandle;`
- L87 _private member_ `TSharedPtr<IPropertyHandle> ParentPropertyHandle;`
- L88 _private member_ `TSharedPtr<IPropertyHandle> ChildPtrToThisContainer;`
- L90 _private member_ `const IPropertyTypeCustomizationUtils* CustomizationUtils;`
- L93 _private prototype_ `bool FilterParentAssetForPicking(const FAssetData& InAssetData);` — asset browsing/picking delegates
- L94 _private prototype_ `void OnParentAssetSelected(const FAssetData& AssetData);`
- L95 _private prototype_ `void OnParentCleared();`
- L96 _private prototype_ `void OnAssetPickerClosed();`
- L97 _private prototype_ `void OnUseSelected();`
- L98 _private prototype_ `void OnBrowseTo(UObject* AssetToBrowseTo);`
- L100 _private member_ `TArray<UObject*> PropertyOwners;`
- L102 _private member_ `FAudioPropertiesSheet* LeafMostSheet;`
- L104 _private member_ `bool bIsLeaf;`

### `Plugins/Experimental/AudioProperties/Source/AudioPropertiesEditor/Private/CustomNodeBuilders/AudioPropertiesDetailArrayBuilder.h` (Private)


#### class `FAudioPropertiesDetailArrayBuilder`  
`class FAudioPropertiesDetailArrayBuilder : public FDetailArrayBuilder, public TSharedFromThis<FAudioPropertiesDetailArrayBuilder>`  
_L7-24_
- inherits: `FDetailArrayBuilder,TSharedFromThis<FAudioPropertiesDetailArrayBuilder>`
- L10 _public prototype_ `FAudioPropertiesDetailArrayBuilder(const TSharedRef<IPropertyHandle>& InBaseProperty, const TSharedRef<IPropertyHandle>& InPropertySheetHandle, TWeakObjectPtr<UObject> InPropertyOwner, bool InGenerateHeader = true, bool InDisplayResetToDefault = true, bool InDisplayElementNum = true);`
- L12 _public prototype_ `virtual void GenerateHeaderRowContent(FDetailWidgetRow& NodeRow) override;`
- L15 _private prototype_ `virtual void GenerateChildContent(IDetailChildrenBuilder& ChildrenBuilder) override;`
- L17 _private prototype_ `bool IsEnabled() const;`
- L18 _private prototype_ `bool GetHeaderRowEditConditionValue() const;`
- L19 _private prototype_ `void OnHeaderRowEditConditionValueChanged(bool bValue) const;`
- L20 _private prototype_ `void SetUpEditCondition(FDetailWidgetRow& NodeRow) const;`
- L22 _private member_ `TSharedRef<IPropertyHandle> PropertySheetPropertyHandle;`
- L23 _private member_ `TWeakObjectPtr<UObject> PropertyOwnerObject;`

### `Plugins/Experimental/AudioProperties/Source/AudioPropertiesEditor/Private/CustomNodeBuilders/AudioPropertiesDetailNestedNodesBuilder.h` (Private)


#### class `FAudioPropertiesDetailNestedNodesBuilder`  
`class FAudioPropertiesDetailNestedNodesBuilder : public IDetailCustomNodeBuilder , public TSharedFromThis<FAudioPropertiesDetailNestedNodesBuilder>`  
_L8-40_
- inherits: `IDetailCustomNodeBuilder,TSharedFromThis<FAudioPropertiesDetailNestedNodesBuilder>`
- L11 _public prototype_ `FAudioPropertiesDetailNestedNodesBuilder(TSharedRef<IPropertyHandle> InBaseProperty, const TSharedRef<IPropertyHandle>& InPropertySheetHandle, TWeakObjectPtr<UObject> InPropertyOwner, bool InGenerateHeader = true, bool InDisplayResetToDefault = true);`
- L13 _public function_ `virtual bool RequiresTick() const override`
- L14 _public function_ `virtual void Tick( float DeltaTime ) override`
- L16 _public prototype_ `void SetDisplayName( const FText& InDisplayName );`
- L17 _public prototype_ `virtual FName GetName() const override;`
- L19 _public function_ `virtual bool InitiallyCollapsed() const override`
- L21 _public prototype_ `virtual void GenerateHeaderRowContent(FDetailWidgetRow& NodeRow) override;`
- L22 _public prototype_ `virtual void GenerateChildContent(IDetailChildrenBuilder& ChildrenBuilder) override;`
- L24 _public prototype_ `virtual TSharedPtr<IPropertyHandle> GetPropertyHandle() const override;`
- L27 _private prototype_ `bool IsEnabled() const;`
- L28 _private prototype_ `bool GetHeaderRowEditConditionValue() const;`
- L29 _private prototype_ `void OnHeaderRowEditConditionValueChanged(bool bValue) const;`
- L30 _private prototype_ `void SetUpEditCondition(FDetailWidgetRow& NodeRow) const;`
- L32 _private member_ `FText DisplayName;`
- L33 _private member_ `TSharedRef<IPropertyHandle> BasePropertyHandle;`
- L34 _private member_ `TSharedRef<IPropertyHandle> PropertySheetPropertyHandle;`
- L35 _private member_ `TWeakObjectPtr<UObject> PropertyOwnerObject;`
- L37 _private member_ `bool bGenerateHeader;`
- L38 _private member_ `bool bDisplayResetToDefault;`

### `Plugins/Experimental/AudioProperties/Source/AudioPropertiesEditor/Private/CustomNodeBuilders/AudioPropertiesDetailSetBuilder.h` (Private)


#### class `FAudioPropertiesDetailSetBuilder`  
`class FAudioPropertiesDetailSetBuilder : public IDetailCustomNodeBuilder , public TSharedFromThis<FAudioPropertiesDetailSetBuilder>`  
_L8-49_
- inherits: `IDetailCustomNodeBuilder,TSharedFromThis<FAudioPropertiesDetailSetBuilder>`
- L11 _public prototype_ `FAudioPropertiesDetailSetBuilder(TSharedRef<IPropertyHandle> InBaseProperty, const TSharedRef<IPropertyHandle>& InPropertySheetHandle, TWeakObjectPtr<UObject> InPropertyOwner, bool InGenerateHeader = true, bool InDisplayResetToDefault = true, bool InDisplayElementNum = true);`
- L12 _public prototype_ `virtual ~FAudioPropertiesDetailSetBuilder();`
- L14 _public function_ `virtual bool RequiresTick() const override`
- L15 _public function_ `virtual void Tick( float DeltaTime ) override`
- L17 _public prototype_ `void SetDisplayName( const FText& InDisplayName );`
- L18 _public prototype_ `virtual FName GetName() const override;`
- L20 _public function_ `virtual bool InitiallyCollapsed() const override`
- L22 _public prototype_ `virtual void GenerateHeaderRowContent(FDetailWidgetRow& NodeRow) override;`
- L23 _public prototype_ `virtual void GenerateChildContent(IDetailChildrenBuilder& ChildrenBuilder) override;`
- L25 _public prototype_ `virtual TSharedPtr<IPropertyHandle> GetPropertyHandle() const override;`
- L28 _protected function_ `virtual void SetOnRebuildChildren(FSimpleDelegate InOnRebuildChildren) override`
- L29 _protected prototype_ `void OnNumChildrenChanged() const;`
- L32 _private prototype_ `bool IsEnabled() const;`
- L33 _private prototype_ `bool GetHeaderRowEditConditionValue() const;`
- L34 _private prototype_ `void OnHeaderRowEditConditionValueChanged(bool bValue) const;`
- L35 _private prototype_ `void SetUpEditCondition(FDetailWidgetRow& NodeRow) const;`
- L37 _private member_ `FText DisplayName;`
- L38 _private member_ `TSharedPtr<IPropertyHandleSet> SetPropertyHandle;`
- L39 _private member_ `TSharedRef<IPropertyHandle> BasePropertyHandle;`
- L40 _private member_ `TSharedRef<IPropertyHandle> PropertySheetPropertyHandle;`
- L41 _private member_ `TWeakObjectPtr<UObject> PropertyOwnerObject;`
- L43 _private member_ `FSimpleDelegate OnRebuildChildren;`
- L44 _private member_ `FDelegateHandle OnNumElementsChangedHandle;`
- L46 _private member_ `bool bGenerateHeader;`
- L47 _private member_ `bool bDisplayResetToDefault;`
- L48 _private member_ `bool bDisplayElementNum;`

### `Plugins/Experimental/AudioProperties/Source/AudioPropertiesEditor/Private/SAudioPropertiesSheetBuilderWidget.h` (Private)


#### class `SAudioPropertiesSheetBuilderWidget`  
`class SAudioPropertiesSheetBuilderWidget : public SCompoundWidget`  
_L18-82_
- inherits: `SCompoundWidget`
- L21 _public function_ `SLATE_BEGIN_ARGS(SAudioPropertiesSheetBuilderWidget)`
- L24 _public prototype_ `SLATE_ARGUMENT(TObjectPtr<const UObject>, SourceObject)` — The object to inherit properties from
- L33 _private prototype_ `TSharedRef<SWidget> GenerateSourceObjectWidget();`
- L34 _private prototype_ `TSharedRef<SWidget> GeneratePropertyListWidget();`
- L35 _private prototype_ `TSharedRef<SWidget> GenerateParentPickerWidget();`
- L36 _private prototype_ `void UpdateSourcePickerComboText() const;`
- L37 _private prototype_ `void UpdateParentPickerComboText() const;`
- L39 _private prototype_ `void SetSourceObject(TObjectPtr<const UObject> NewSourceObject);`
- L40 _private prototype_ `void SetSourceAsset(const FAssetData& InSelectedSource);`
- L41 _private prototype_ `void SetParentAsset(const FAssetData& InSelectedParent);`
- L42 _private prototype_ `void UpdatePropertyRequests();`
- L44 _private prototype_ `FAssetData GetSourceAssetData();`
- L47 _private prototype_ `TSharedRef<ITableRow> OnGenerateRowForList(AudioPropertiesSheetAssetBuilder::FPropertyRequestPtr InItem, const TSharedRef<STableViewBase>& OwnerTable);` — Widgets callbacks
- L48 _private prototype_ `FReply OnMakePropertySheetClicked();`
- L49 _private prototype_ `void OnSearchTextChanged(const FText& SearchText);`
- L52 _private prototype_ `void OnSourceBrowseToButtonClicked() const;` — Asset browsing delegates - source
- L53 _private prototype_ `void OnSourceEditButtonClicked() const;`
- L54 _private prototype_ `void OnSourceUseSelectedButtonClicked();`
- L57 _private prototype_ `void OnParentBrowseToButtonClicked() const;` — Asset browsing delegates - parent
- L58 _private prototype_ `void OnParentEditButtonClicked() const;`
- L59 _private prototype_ `void OnParentUseSelectedButtonClicked();`
- L62 _private prototype_ `EColumnSortMode::Type GetColumnSortMode(FName InColumnName) const;` — Sorting methods
- L63 _private prototype_ `void OnColumnSortModeChanged(EColumnSortPriority::Type SortPriority, const FName& ColumnName, EColumnSortMode::Type InSortMode);`
- L64 _private prototype_ `void SortProperties();`
- L66 _private member_ `TObjectPtr<const UObject> SourceObject;`
- L67 _private member_ `FAssetData GeneratedSheetParent;`
- L68 _private member_ `bool bSourceIsPropertySheet = false;`
- L70 _private member_ `TSharedPtr<SListView<AudioPropertiesSheetAssetBuilder::FPropertyRequestPtr>> PropertyRequestsView;`
- L71 _private member_ `TArray<AudioPropertiesSheetAssetBuilder::FPropertyRequestPtr> PropertyRequests;`
- L72 _private member_ `TArray<AudioPropertiesSheetAssetBuilder::FPropertyRequestPtr> FilteredPropertyRequests;`
- L74 _private member_ `FName SortedColumn;`
- L75 _private member_ `EColumnSortMode::Type SortMode;`
- L77 _private member_ `TSharedPtr<SComboButton> SourcePickerComboButton;`
- L78 _private member_ `TSharedPtr<STextBlock> SourcePickerComboText;`
- L80 _private member_ `TSharedPtr<SComboButton> ParentPickerComboButton;`
- L81 _private member_ `TSharedPtr<STextBlock> ParentPickerComboText;`

### `Plugins/Experimental/AudioProperties/Source/AudioPropertiesEditor/Public/AssetDefinition_AudioPropertiesSheetAsset.h` (Public)


#### class `UAssetDefinition_AudioPropertiesSheetAsset`  
`class UAssetDefinition_AudioPropertiesSheetAsset : public UAssetDefinitionDefault_AudioDiffable`  
_L14-32_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetDefinitionDefault_AudioDiffable`
- L20 _public function_ `virtual FText GetAssetDisplayName() const override`
- L21 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L22 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L23 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L24 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L27 _public prototype_ `FToolMenuSection* FindContextMenuSection(FName SectionName) const;`
- L30 _private prototype_ `virtual TArray<FToolMenuSection*> RebuildContextMenuSections() const;`

### `Plugins/Experimental/AudioProperties/Source/AudioPropertiesEditor/Public/AudioPropertiesBindingsFactory.h` (Public)


#### class `UAudioPropertiesBindingsFactory`  
`class UAudioPropertiesBindingsFactory : public UFactory`  
_L11-16_
- reflection: `UCLASS(hidecategories = Object, MinimalAPI)`
- inherits: `UFactory`
- L15 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

### `Plugins/Experimental/AudioProperties/Source/AudioPropertiesEditor/Public/AudioPropertiesDetailsInjector.h` (Public)


#### class `FAudioPropertiesDetailsInjector`  
`class FAudioPropertiesDetailsInjector : public IAudioPropertiesDetailsInjector`  
_L17-43_
- inherits: `IAudioPropertiesDetailsInjector`
- desc: Helper to customize the IDetailCustomization of a class receiving properties from an AudioPropertySheetAsset
- L24 _public prototype_ `void CustomizeInjectedPropertiesDetails(IDetailLayoutBuilder& DetailBuilder, TSharedRef<IPropertyHandle> PropertySheetPropertyHandle) override;` — To be called from IDetailCustomization::CustomizeDetails to customize widgets of injected properties @param DetailBuilder					DetailBuilder from CustomizeDetails. @param PropertySheetPropertyHandle		Property Handle of the property sheet injecting properties on the target UObject.
- L30 _public prototype_ `void BindDetailCustomizationToPropertySheetChanges(IDetailLayoutBuilder& DetailBuilder, TSharedRef<IPropertyHandle> PropertySheetPropertyHandle) override;` — To be called from IDetailCustomization::CustomizeDetails to bind the detail view to changes on the property sheet @param DetailBuilder					DetailBuilder from CustomizeDetails. @param PropertySheetPropertyHandle		Property Handle of the property sheet injecting properties on the target UObject.
- L33 _public prototype_ `void UnbindFromPropertySheetChanges() override;` — Call this on destruction/pending delete of the details customization to unbind the detail view to changes on the property sheet
- L36 _private prototype_ `void BindDetailsRefreshToPropertySheetSwaps(const IDetailLayoutBuilder& DetailBuilder, TArray<TWeakObjectPtr<UObject>>& ObjectsBeingCustomized, TSharedRef<IPropertyHandle> PropertySheetPropertyHandle);`
- L37 _private prototype_ `void BindDetailsRefreshToPropertySheetChanges(IDetailLayoutBuilder& DetailBuilder, TArray<TWeakObjectPtr<UObject>>& ObjectsBeingCustomized, TSharedRef<IPropertyHandle> PropertySheetPropertyHandle);`
- L39 _private prototype_ `void CreateOverriddenPropertiesWidgets(IDetailLayoutBuilder& DetailBuilder, TArray<TWeakObjectPtr<UObject>> ObjectsBeingCustomized, TSharedRef<IPropertyHandle> PropertySheetPropertyHandle);`
- L41 _private member_ `TArray<FDelegateHandle> OnTargetObjectPropertyChangeDelegateHandles;`
- L42 _private member_ `TMultiMap<FObjectKey, FDelegateHandle> InjectedPropertiesBindings;`

#### class `FAudioPropertiesDetailsInjectorBuilder`  
`class FAudioPropertiesDetailsInjectorBuilder : public IAudioPropertiesDetailsInjectorBuilder`  
_L48-52_
- inherits: `IAudioPropertiesDetailsInjectorBuilder`
- desc: Modular feature builder to instantiate an FAudioPropertiesDetailsInjector
- L51 _public function_ `virtual IAudioPropertiesDetailsInjector* CreateAudioPropertiesDetailsInjector() override`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AUDIOPROPERTIESEDITOR_API`

### `Plugins/Experimental/AudioProperties/Source/AudioPropertiesEditor/Public/AudioPropertiesEditorModule.h` (Public)


#### class `FAudioPropertiesEditorModule`  
`class FAudioPropertiesEditorModule : public IModuleInterface`  
_L18-28_
- inherits: `IModuleInterface`
- L21 _public prototype_ `virtual void StartupModule() override;`
- L22 _public prototype_ `virtual void ShutdownModule() override;`
- L25 _private member_ `TSharedPtr<FAudioPropertiesSheetBuilderInstantiator> PropertiesSheetBuilder = nullptr;`
- L27 _private member_ `TSharedPtr<FAudioPropertiesDetailsInjectorBuilder> DetailsInjectorBuilder = nullptr;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace AudioPropertiesEditorModule`
- L15 _variable_ `inline constexpr FColor AssetColor = FColor(201, 29, 85);` (scope `AudioPropertiesEditorModule`)

### `Plugins/Experimental/AudioProperties/Source/AudioPropertiesEditor/Public/AudioPropertiesSheetAssetFactory.h` (Public)


#### class `UAudioPropertiesSheetAssetFactory`  
`class UAudioPropertiesSheetAssetFactory : public UFactory`  
_L11-16_
- reflection: `UCLASS(hidecategories = Object, MinimalAPI)`
- inherits: `UFactory`
- L15 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

### `Plugins/Experimental/AudioProperties/Source/AudioPropertiesEditor/Public/InstancedAudioPropertyBagDetails.h` (Public)


#### class `FInstancedAudioPropertyBagDetails`  
`class FInstancedAudioPropertyBagDetails : public FPropertyBagInstanceDataDetails`  
_L13-39_
- inherits: `FPropertyBagInstanceDataDetails`
- L17 _public prototype_ `FInstancedAudioPropertyBagDetails( TSharedPtr<IPropertyHandle> InInstancedPropertyBagHandle, const TSharedPtr<IPropertyUtilities>& InPropUtils, const UAudioPropertiesSheetAsset* InOwningAudioPropertiesSheetAsset, FAudioPropertiesSheet* InLeafMostPropertySheet, bool bInIsLeafBag = false);`
- L24 _public prototype_ `virtual void OnChildRowAdded(IDetailPropertyRow& ChildRow)override;`
- L26 _public function_ `virtual void GenerateHeaderRowContent(FDetailWidgetRow& NodeRow) override`
- L29 _private prototype_ `void DrawLeafBagChildRow(IDetailPropertyRow& ChildRow);`
- L30 _private prototype_ `void DrawInheritedBagChildRow(IDetailPropertyRow& ChildRow);`
- L32 _private prototype_ `void HandlePropertyOverrideChanged(TSharedPtr<IPropertyHandle> PropertyThatChanged, const bool bOverrideState);`
- L34 _private member_ `TSharedPtr<IPropertyHandle> InstancedPropertyBagHandle = nullptr;`
- L35 _private member_ `const UAudioPropertiesSheetAsset* OwningAudioPropertiesSheetAsset = nullptr;`
- L36 _private member_ `FAudioPropertiesSheet* LeafMostPropertySheet = nullptr;`
- L37 _private member_ `TSharedPtr<IPropertyUtilities> CachedPropUtils;`
- L38 _private member_ `bool bIsLeafBag = false;`
