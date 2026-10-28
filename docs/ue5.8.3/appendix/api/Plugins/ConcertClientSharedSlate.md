# Plugins / ConcertClientSharedSlate

- module root: `Plugins/Developer/Concert/ConcertUI/ConcertClientSharedSlate/Source/ConcertClientSharedSlate`
- headers: 28; symbols: 255
- symbol kinds: class=19, delegate=4, enum=1, enumerator=3, function=60, macro=1, member=38, namespace=58, prototype=58, struct=9, typedef=1, variable=3
- PrivateDependencyModuleNames: AssetDefinition, AssetRegistry, Concert, ConcertClient, ConcertSyncCore, ConcertTransport, EditorWidgets, InputCore, Projects, Slate, SlateCore, SubobjectDataInterface, ToolMenus, ToolWidgets, UnrealEd
- PublicDependencyModuleNames: ConcertSharedSlate, ConcertSyncClient, Core, CoreUObject, EditorStyle, Engine, Slate, SlateCore

### `Plugins/Developer/Concert/ConcertUI/ConcertClientSharedSlate/Source/ConcertClientSharedSlate/Private/Replication/Editor/Model/Object/EditorObjectHierarchyModel.h` (Private)


#### class `UE::ConcertClientSharedSlate::FEditorObjectHierarchyModel`  
`class FEditorObjectHierarchyModel : public ConcertSharedSlate::IObjectHierarchyModel`  
_L20-32_
- inherits: `ConcertSharedSlate::IObjectHierarchyModel`
- desc: Builds a similar tree hierarchy as SSubobjectEditor with the addition of non-component subobjects. An example for a hierarchy in an editor build is: - Actor returns its root component, non-scene components (UActorComponents), and all other direct subobjects - Scene components return their children, and all other direct subobjects - All other subobjects report all direct subobjects
- L25 _public prototype_ `virtual void ForEachDirectChild( const TSoftObjectPtr<>& Parent, TFunctionRef<EBreakBehavior(const TSoftObjectPtr<>& Object, ConcertSharedSlate::EChildRelationship Relationship)> Callback, ConcertSharedSlate::EChildRelationshipFlags InclusionFlags ) const override;`
- L30 _public prototype_ `virtual TOptional<FParentInfo> GetParentInfo(const TSoftObjectPtr<const UObject>& ChildObject) const override;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ConcertClientSharedSlate` (scope `UE`)

### `Plugins/Developer/Concert/ConcertUI/ConcertClientSharedSlate/Source/ConcertClientSharedSlate/Private/Replication/Editor/Model/Object/EditorObjectNameModel.h` (Private)


#### class `UE::ConcertClientSharedSlate::FEditorObjectNameModel`  
`class FEditorObjectNameModel : public ConcertSharedSlate::IObjectNameModel`  
_L11-18_
- inherits: `ConcertSharedSlate::IObjectNameModel`
- desc: Name model that uses editor data for determining display names: actors use their labels, components ask USubobjectDataSubsystem.
- L16 _public function_ `virtual FText GetObjectDisplayName(const TSoftObjectPtr<>& ObjectPath) const override`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ConcertClientSharedSlate` (scope `UE`)

### `Plugins/Developer/Concert/ConcertUI/ConcertClientSharedSlate/Source/ConcertClientSharedSlate/Private/Replication/Editor/Model/ReplicationStreamObject.h` (Private)


#### class `UReplicationStreamObject`  
`class UReplicationStreamObject : public UObject`  
_L11-18_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: UObject wrapper to allow transactions on FConcertObjectReplicationMap.
- L17 _public member_ `FConcertObjectReplicationMap ReplicationMap;` — `UPROPERTY()`

### `Plugins/Developer/Concert/ConcertUI/ConcertClientSharedSlate/Source/ConcertClientSharedSlate/Private/Replication/Editor/Model/TransactionalReplicationStreamModel.h` (Private)


#### class `UE::ConcertSharedSlate::FTransactionalReplicationStreamModel`  
`class FTransactionalReplicationStreamModel : public FEditableStreamModelProxy , public FSelfRegisteringEditorUndoClient , public FGCObject`  
_L17-51_
- inherits: `FEditableStreamModelProxy,FSelfRegisteringEditorUndoClient,FGCObject`
- desc: Special case of FGenericPropertySelectionModel where the edited FConcertObjectReplicationMap lives in an UObject that is RF_Transactional.
- L24 _public prototype_ `FTransactionalReplicationStreamModel( const TSharedRef<IEditableReplicationStreamModel>& WrappedModel, UObject& OwningObject );`
- L30 _public prototype_ `virtual void AddObjects(TConstArrayView<UObject*> Objects) override;`
- L31 _public prototype_ `virtual void RemoveObjects(TConstArrayView<FSoftObjectPath> Objects) override;`
- L32 _public prototype_ `virtual void AddProperties(const FSoftObjectPath&, TConstArrayView<FConcertPropertyChain> Properties) override;`
- L33 _public prototype_ `virtual void RemoveProperties(const FSoftObjectPath&, TConstArrayView<FConcertPropertyChain> Properties) override;`
- L37 _public prototype_ `virtual bool MatchesContext(const FTransactionContext& InContext, const TArray<TPair<UObject*, FTransactionObjectEvent>>& TransactionObjectContexts) const override;`
- L38 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L39 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L43 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L44 _public function_ `virtual FString GetReferencerName() const override`
- L50 _private member_ `TWeakObjectPtr<UObject> OwningObject;` — User of FTransactionalPropertySelectionModel is responsible for keeping OwningObject alive, e.g. via an asset editor.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)

### `Plugins/Developer/Concert/ConcertUI/ConcertClientSharedSlate/Source/ConcertClientSharedSlate/Private/Replication/Editor/View/PropertyTree/PropertyFilterBase.h` (Private)


#### class `UE::ConcertClientSharedSlate::FPropertyFilterBase`  
`class FPropertyFilterBase : public IFilter<const ConcertSharedSlate::FPropertyData&>`  
_L21-40_
- inherits: `IFilter<constConcertSharedSlate::FPropertyData&>`
- desc: Base class for property filters. This filter inverts the results: all filters are supposed to be inverse filters, i.e. they should be run when they are greyed out in the UI. When they are run, they should remove specific properties. Subclasses simply implement Matches, which figures out whether the property is contained in some FPropertyData.
- L26 _public function_ `virtual bool PassesFilter(const ConcertSharedSlate::FPropertyData& InItem) const final override`
- L30 _public function_ `virtual FChangedEvent& OnChanged() final override`
- L36 _private member_ `FChangedEvent ChangedEventDelegate;` — Dummy delegate to fulfill IFilter interface: this filter will never change so this delegate will never trigger.
- L39 _private prototype_ `virtual bool MatchesFilteredForProperty(const ConcertSharedSlate::FPropertyData& InItem) const = 0;` — @return Whether this item contains the property this filter is looking for.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ConcertClientSharedSlate` (scope `UE`)

### `Plugins/Developer/Concert/ConcertUI/ConcertClientSharedSlate/Source/ConcertClientSharedSlate/Private/Replication/Editor/View/PropertyTree/PropertyFilter_ByPropertyType.h` (Private)


#### class `UE::ConcertClientSharedSlate::FPropertyFilter_ByPropertyType`  
`class FPropertyFilter_ByPropertyType : public FPropertyFilterBase`  
_L16-34_
- inherits: `FPropertyFilterBase`
- desc: Filters a property based on the FFieldClass it has.
- L20 _public function_ `FPropertyFilter_ByPropertyType(TSet<FFieldClass*> AllowedClasses) : AllowedClasses(MoveTemp(AllowedClasses))`
- L26 _private member_ `TSet<FFieldClass*> AllowedClasses;`
- L29 _private member_ `FChangedEvent ChangedEventDelegate;` — Dummy delegate to fulfill IFilter interface: this filter will never change so this delegate will never trigger.
- L32 _private prototype_ `virtual bool MatchesFilteredForProperty(const ConcertSharedSlate::FPropertyData& InItem) const override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace ConcertClientSharedSlate` (scope `UE`)

### `Plugins/Developer/Concert/ConcertUI/ConcertClientSharedSlate/Source/ConcertClientSharedSlate/Private/Replication/Editor/View/PropertyTree/PropertyFrontendFilter.h` (Private)


#### class `UE::ConcertClientSharedSlate::FPropertyFrontendFilter`  
`class FPropertyFrontendFilter : public FFilterBase<const ConcertSharedSlate::FPropertyData&>`  
_L13-40_
- inherits: `FFilterBase<constConcertSharedSlate::FPropertyData&>`
- desc: Base UI filter for filtering properties. Gets rid of all the extra functionality in FFilterBase we do not need.
- L17 _public function_ `FPropertyFrontendFilter(TSharedRef<FFilterCategory> InCategory, FText DisplayName, FText Tooltip = FText::GetEmpty()) : FFilterBase(MoveTemp(InCategory)) , DisplayName(MoveTemp(DisplayName)) , Tooltip(MoveTemp(Tooltip))`
- L24 _public function_ `virtual FString GetName() const override`
- L25 _public function_ `virtual FText GetDisplayName() const override`
- L26 _public function_ `virtual FText GetToolTipText() const override`
- L27 _public function_ `virtual FLinearColor GetColor() const override`
- L28 _public function_ `virtual FName GetIconName() const override`
- L29 _public function_ `virtual bool IsInverseFilter() const override`
- L30 _public function_ `virtual void ActiveStateChanged(bool bActive) override`
- L31 _public function_ `virtual void ModifyContextMenu(FMenuBuilder& MenuBuilder) override`
- L32 _public function_ `virtual void SaveSettings(const FString& IniFilename, const FString& IniSection, const FString& SettingsString) const override`
- L33 _public function_ `virtual void LoadSettings(const FString& IniFilename, const FString& IniSection, const FString& SettingsString) override`
- L38 _private member_ `FText DisplayName;`
- L39 _private member_ `FText Tooltip;`

#### class `UE::ConcertClientSharedSlate::TPropertyFrontendFilter`  
`template<typename TFilterType> class TPropertyFrontendFilter : public FPropertyFrontendFilter`  
_L44-78_
- inherits: `FPropertyFrontendFilter`
- desc: Inlines a IFilter<const FPropertyData&> at compile time to avoid an additional TSharedPtr<IFilter<const FPropertyData&>>.
- L49 _public function_ `template<typename... TArg> TPropertyFrontendFilter(TSharedRef<FFilterCategory> InCategory, FText DisplayName, TArg&&... Arg) : FPropertyFrontendFilter(MoveTemp(InCategory), MoveTemp(DisplayName)) , FilterImplementation(Forward<TArg>(Arg)...)`
- L60 _public function_ `template<typename... TArg> TPropertyFrontendFilter(TSharedRef<FFilterCategory> InCategory, FText DisplayName, FText Tooltip, TArg&&... Arg) : FPropertyFrontendFilter(MoveTemp(InCategory), MoveTemp(DisplayName), MoveTemp(Tooltip)) , FilterImplementation(Forward<TArg>(Arg)...)`
- L70 _public function_ `virtual bool PassesFilter(const ConcertSharedSlate::FPropertyData& InItem) const override`
- L77 _private member_ `TFilterType FilterImplementation;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ConcertClientSharedSlate` (scope `UE`)
- L54 _function_ `` (scope `UE::ConcertClientSharedSlate::TPropertyFrontendFilter::TPropertyFrontendFilter`)

### `Plugins/Developer/Concert/ConcertUI/ConcertClientSharedSlate/Source/ConcertClientSharedSlate/Private/Replication/Editor/View/PropertyTree/SFilteredPropertyTreeView.h` (Private)


#### class `UE::ConcertClientSharedSlate::SFilteredPropertyTreeView`  
`class SFilteredPropertyTreeView : public SCompoundWidget , public ConcertSharedSlate::IPropertyTreeView`  
_L24-67_
- inherits: `SCompoundWidget,ConcertSharedSlate::IPropertyTreeView`
- desc: This widget extends SPropertyTreeView with filtering functionality.
- L30 _public typedef_ `using FFilterRef = TSharedRef<FFilterBase<const ConcertSharedSlate::FPropertyData&>>;`
- L32 _public function_ `SLATE_BEGIN_ARGS(SFilteredPropertyTreeView)`
- L34 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, FFilterablePropertyTreeViewParams Params);`
- L39 _public function_ `virtual void RefreshPropertyData(const TArray<ConcertSharedSlate::FPropertyAssignmentEntry>& Entries, bool bCanReuseExistingRowItems) override`
- L43 _public function_ `virtual void RequestRefilter() const override`
- L44 _public function_ `virtual void RequestResortForColumn(const FName& ColumnId) override`
- L45 _public function_ `virtual void RequestScrollIntoView(const FConcertPropertyChain& PropertyChain) override`
- L46 _public function_ `virtual TSharedRef<SWidget> GetWidget() override`
- L52 _private member_ `TSharedPtr<IPropertyTreeView> ExtendedTreeView;` — The tree view displaying the replicated properties
- L54 _private member_ `TSharedPtr<SReplicationFilterBar> FilterBar;` — Displays the active filters
- L62 _private prototype_ `FBuildFilterBarResult BuildFilterBar();` — Build the filter bar and returns the filters that should be active by default.
- L65 _private prototype_ `ConcertSharedSlate::EFilterResult PassesFilters(const ConcertSharedSlate::FPropertyData& ReplicatedPropertyData) const;` — Runs all filters through this item
- L66 _private prototype_ `bool PassesAnyFilters(const ConcertSharedSlate::FPropertyData& ReplicatedPropertyData) const;`

#### struct `UE::ConcertClientSharedSlate::SFilteredPropertyTreeView::FBuildFilterBarResult`  
`struct FBuildFilterBarResult`  
_L56-60_
- L58 _public member_ `TArray<FFilterRef> EnabledByDefault;`
- L59 _public member_ `TArray<FFilterRef> DisabledByDefault;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace ConcertClientSharedSlate` (scope `UE`)

### `Plugins/Developer/Concert/ConcertUI/ConcertClientSharedSlate/Source/ConcertClientSharedSlate/Private/Replication/Editor/View/SReplicationDropArea.h` (Private)


#### class `UE::ConcertClientSharedSlate::SReplicationDropArea`  
`class SReplicationDropArea : public SCompoundWidget`  
_L13-40_
- inherits: `SCompoundWidget`
- desc: Handles drag-drop operations for the replication UI.
- L17 _public function_ `SLATE_BEGIN_ARGS(SReplicationDropArea)`
- L19 _public prototype_ `SLATE_EVENT(FDragDropReplicatableObject, HandleDroppedObjects) SLATE_EVENT(FCanDragDropObject, CanDropObject) SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — Required. Responds to objects being dropped into the replication outliner.
- L31 _private member_ `FDragDropReplicatableObject HandleDroppedObjectsDelegate;` — Responds to objects being dropped into the replication outliner.
- L33 _private member_ `FCanDragDropObject CanDropObjectDelegate;` — Decides whether a dragged object can be dropped.
- L35 _private prototype_ `FReply OnDragDropTarget(const FGeometry& Geometry, const FDragDropEvent& DragDropEvent) const;`
- L36 _private prototype_ `bool CanDragDropTarget(TSharedPtr<FDragDropOperation> InOperation) const;`
- L39 _private prototype_ `bool CanDrop(UObject* Object) const;` — @return Whether Object can be dropped.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ConcertClientSharedSlate` (scope `UE`)

### `Plugins/Developer/Concert/ConcertUI/ConcertClientSharedSlate/Source/ConcertClientSharedSlate/Public/ConcertClientFrontendUtils.h` (Public)


#### Free symbols / members of external scopes

- L17 _macro_ `#define LOCTEXT_NAMESPACE "ConcertClientFrontendUtils"`
- L19 _namespace_ `namespace ConcertClientFrontendUtils`
- L21 _variable_ `static const FName ButtonIconSyle = TEXT("Fon` (scope `ConcertClientFrontendUtils`)
- L22 _variable_ `static const float MinDesiredWidthForBtnAndIcon = 29.f;` (scope `ConcertClientFrontendUtils`)
- L23 _variable_ `static const FName ButtonStyleNames[(int32)EConcertActionType::NUM] = { TEXT("SimpleButton"), TEXT("FlatButton.Primary"), TEXT("FlatButton.Info"), TEXT("FlatButton.Success"), TEXT("FlatButton.Warning"), TEXT("FlatButton.Danger"), };` (scope `ConcertClientFrontendUtils`)
- L32 _function_ `inline TSharedRef<SButton> CreateTextButton(const FConcertActionDefinition& InDef)` (scope `ConcertClientFrontendUtils`)
- L44 _function_ `.Visibility_Lambda([IsVisible = InDef.IsVisible]() { return IsVisible.Get() ? EVisibility::Visible : EVisibility::Collapsed; }) .OnClicked_Lambda([OnExecute = InDef.OnExecute]() { OnExecute.ExecuteIfBound(); return FReply::Handled(); }) [ SNew(SBox) .MinDesiredWidth(MinDesiredWidthForBtnAndIcon - PaddingCompensation) .HAlign(HAlign_Center) [ SNew(STextBlock) .Font(FAppStyle::Get().GetFontStyle(ButtonIconSyle)) .Text(InDef.Text) .Justification(ETextJustify::Center) ] ];` (scope `ConcertClientFrontendUtils::CreateTextButton`)
- L45 _function_ `.OnClicked_Lambda([OnExecute = InDef.OnExecute]() { OnExecute.ExecuteIfBound(); return FReply::Handled(); }) [ SNew(SBox) .MinDesiredWidth(MinDesiredWidthForBtnAndIcon - PaddingCompensation) .HAlign(HAlign_Center) [ SNew(STextBlock) .Font(FAppStyle::Get().GetFontStyle(ButtonIconSyle)) .Text(InDef.Text) .Justification(ETextJustify::Center) ] ];` (scope `ConcertClientFrontendUtils::CreateTextButton`)
- L59 _function_ `inline TSharedRef<SButton> CreateIconButton(const FConcertActionDefinition& InDef)` (scope `ConcertClientFrontendUtils`)
- L66 _function_ `.Visibility_Lambda([IsVisible = InDef.IsVisible]() { return IsVisible.Get() ? EVisibility::Visible : EVisibility::Collapsed; }) .OnClicked_Lambda([OnExecute = InDef.OnExecute]() { OnExecute.ExecuteIfBound(); return FReply::Handled(); }) .VAlign(VAlign_Center) .HAlign(HAlign_Center) [ SNew(SImage) .Image(TAttribute<const FSlateBrush*>::Create([IconStyleAttr = InDef.IconStyle]() { return FConcertFrontendStyle::Get()->GetBrush(IconStyleAttr.Get()); })) .ColorAndOpacity(FSlateColor::UseForeground()) ];` (scope `ConcertClientFrontendUtils::CreateIconButton`)
- L67 _function_ `.OnClicked_Lambda([OnExecute = InDef.OnExecute]() { OnExecute.ExecuteIfBound(); return FReply::Handled(); }) .VAlign(VAlign_Center) .HAlign(HAlign_Center) [ SNew(SImage) .Image(TAttribute<const FSlateBrush*>::Create([IconStyleAttr = InDef.IconStyle]() { return FConcertFrontendStyle::Get()->GetBrush(IconStyleAttr.Get()); })) .ColorAndOpacity(FSlateColor::UseForeground()) ];` (scope `ConcertClientFrontendUtils::CreateIconButton`)
- L72 _function_ `.Image(TAttribute<const FSlateBrush*>::Create([IconStyleAttr = InDef.IconStyle]() { return FConcertFrontendStyle::Get()->GetBrush(IconStyleAttr.Get()); })) .ColorAndOpacity(FSlateColor::UseForeground()) ];` (scope `ConcertClientFrontendUtils::CreateIconButton`)
- L77 _function_ `inline void AppendButtons(TSharedRef<SHorizontalBox> InHorizBox, TArrayView<const FConcertActionDefinition> InDefs)` (scope `ConcertClientFrontendUtils`)

### `Plugins/Developer/Concert/ConcertUI/ConcertClientSharedSlate/Source/ConcertClientSharedSlate/Public/Replication/ClientReplicationWidgetDelegates.h` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ConcertClientSharedSlate` (scope `UE`)
- L13 _delegate_ `DECLARE_DELEGATE_OneParam(FDragDropReplicatableObject, TConstArrayView<UObject*> DroppedObjects);` — Responds to objects being dropped into the replication outliner.
- L13 _prototype_ `DECLARE_DELEGATE_OneParam(FDragDropReplicatableObject, TConstArrayView<UObject*> DroppedObjects);` (scope `UE::ConcertClientSharedSlate`) — Responds to objects being dropped into the replication outliner.
- L15 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FCanDragDropObject, UObject& Object);` — Decides whether a dragged object can be dropped.
- L15 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FCanDragDropObject, UObject& Object);` (scope `UE::ConcertClientSharedSlate`) — Decides whether a dragged object can be dropped.

### `Plugins/Developer/Concert/ConcertUI/ConcertClientSharedSlate/Source/ConcertClientSharedSlate/Public/Replication/ClientReplicationWidgetFactories.h` (Public)


#### struct `UE::ConcertClientSharedSlate::FFilterablePropertyTreeViewParams`  
`struct FFilterablePropertyTreeViewParams`  
_L48-69_
- desc: Params for creating a filterable property tree view.
- L51 _public member_ `TArray<ConcertSharedSlate::FPropertyColumnEntry> AdditionalPropertyColumns { ConcertSharedSlate::ReplicationColumns::Property::LabelColumn() };` — The columns the property view should have. The label column is always included.
- L57 _public member_ `ConcertSharedSlate::FColumnSortInfo PrimaryPropertySort { ConcertSharedSlate::ReplicationColumns::Property::LabelColumnId, EColumnSortMode::Ascending };` — Optional initial primary sort mode for object rows
- L59 _public member_ `ConcertSharedSlate::FColumnSortInfo SecondaryPropertySort { ConcertSharedSlate::ReplicationColumns::Property::LabelColumnId, EColumnSortMode::Ascending };` — Optional initial secondary sort mode for object rows
- L68 _public member_ `ConcertSharedSlate::FCreateCategoryRow CreateCategoryRow;` — Optional delegate for grouping objects under a category. If unset, no category are generated. When the user clicks an object in the top view, this delegate will be called for the clicked object, its components (if an actor), and its (nested) subobjects. ContextObjects is a single object if a single object is clicked or multiple object in the case of multi-edit.

#### struct `UE::ConcertClientSharedSlate::FCreateDropTargetOutlinerWrapperParams`  
`struct FCreateDropTargetOutlinerWrapperParams`  
_L79-85_
- L82 _public member_ `FDragDropReplicatableObject HandleDroppedObjectsDelegate;` — Required. Handles objects that were dropped.
- L84 _public member_ `FCanDragDropObject CanDropObjectDelegate;` — Optional. Decides whether a dragged object can be dropped.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace ConcertClientSharedSlate` (scope `UE`)
- L29 _prototype_ `TSharedRef<ConcertSharedSlate::IObjectHierarchyModel> CreateObjectHierarchyForComponentHierarchy();` (scope `UE::ConcertClientSharedSlate`) — Builds a similar tree hierarchy as SSubobjectEditor. Reports only components as subobjects.
- L32 _prototype_ `TSharedRef<ConcertSharedSlate::IObjectNameModel> CreateEditorObjectNameModel();` (scope `UE::ConcertClientSharedSlate`) — Name model that uses editor data for determining display names: actors use their labels, components ask USubobjectDataSubsystem.
- L40 _prototype_ `TSharedRef<ConcertSharedSlate::IEditableReplicationStreamModel> CreateTransactionalStreamModel( const TSharedRef<ConcertSharedSlate::IEditableReplicationStreamModel>& BaseModel, UObject& OwnerObject );` (scope `UE::ConcertClientSharedSlate`) — Wraps the passed in BaseModel and makes it transactional. All calls that modify the underlying model was wrapped with scoped transactions. @param OwnerObject The object containing the FConcertObjectReplicationMap - used for transactions.
- L45 _prototype_ `TSharedRef<ConcertSharedSlate::IEditableReplicationStreamModel> CreateTransactionalStreamModel();` (scope `UE::ConcertClientSharedSlate`) — Simpler CreateTransactionalStreamModel overload that internally creates an UObject and sets it up automatically.
- L77 _prototype_ `TSharedRef<ConcertSharedSlate::IPropertyTreeView> CreateFilterablePropertyTreeView(FFilterablePropertyTreeViewParams Params);` (scope `UE::ConcertClientSharedSlate`) — Creates a tree view that allows filtering of properties based on their type. There is a combo box to the left of the search bar for managing the used filters. The user can toggle used filters on and off under the search bar.
- L88 _prototype_ `ConcertSharedSlate::FWrapOutlinerWidget CreateDropTargetOutlinerWrapper( FCreateDropTargetOutlinerWrapperParams Params );` (scope `UE::ConcertClientSharedSlate`) — Returns a delegate that wraps the replication outliner with a SDropTarget: it allows users to drag-drop actors.

### `Plugins/Developer/Concert/ConcertUI/ConcertClientSharedSlate/Source/ConcertClientSharedSlate/Public/Replication/Editor/Model/Extension/StreamExtenderBySettings.h` (Public)


#### class `UE::ConcertClientSharedSlate::FStreamExtenderBySettings`  
`class FStreamExtenderBySettings : public ConcertSharedSlate::IStreamExtender`  
_L14-28_
- inherits: `ConcertSharedSlate::IStreamExtender`
- desc: Automatically adds objects and properties according to settings specified in some FConcertReplicationEditorSettings.
- L18 _public prototype_ `FStreamExtenderBySettings(TAttribute<const FConcertStreamObjectAutoBindingRules*> InReplicationSettingsAttribute);`
- L21 _public prototype_ `virtual void ExtendStream(UObject& ExtendedObject, ConcertSharedSlate::IStreamExtensionContext& Context) override;`
- L27 _private member_ `TAttribute<const FConcertStreamObjectAutoBindingRules*> ReplicationSettingsAttribute;` — Optional settings for auto adding common properties and objects.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ConcertClientSharedSlate` (scope `UE`)

### `Plugins/Developer/Concert/ConcertUI/ConcertClientSharedSlate/Source/ConcertClientSharedSlate/Public/Replication/Editor/Model/ObjectSource/ActorSelectionSourceModel.h` (Public)


#### class `UE::ConcertClientSharedSlate::FActorSelectionSourceModel`  
`class FActorSelectionSourceModel : public ConcertSharedSlate::IObjectSelectionSourceModel`  
_L10-25_
- inherits: `ConcertSharedSlate::IObjectSelectionSourceModel`
- desc: Logic for selecting actors from the current editor world.
- L14 _public prototype_ `FActorSelectionSourceModel();`
- L17 _public prototype_ `virtual TArray<ConcertSharedSlate::FObjectSourceCategory> GetRootSources() const override;`
- L18 _public prototype_ `virtual TArray<TSharedRef<ConcertSharedSlate::IObjectSourceModel>> GetContextMenuOptions(const FSoftObjectPath& Item) override;`
- L24 _private member_ `ConcertSharedSlate::FObjectSourceCategory BaseActorCategory;` — Contains actions around adding actor related objects. Displayed next to the search bar. Refined with dynamic options in GetRootSources.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ConcertClientSharedSlate` (scope `UE`)

### `Plugins/Developer/Concert/ConcertUI/ConcertClientSharedSlate/Source/ConcertClientSharedSlate/Public/Replication/Editor/Model/ObjectSource/SelectedActorsSource.h` (Public)


#### class `UE::ConcertClientSharedSlate::FSelectedActorsSource`  
`class FSelectedActorsSource : public ConcertSharedSlate::IObjectSourceModel`  
_L10-19_
- inherits: `ConcertSharedSlate::IObjectSourceModel`
- desc: Gets the actors currently selected in the editor.
- L15 _public prototype_ `virtual ConcertSharedSlate::FSourceDisplayInfo GetDisplayInfo() const override;`
- L16 _public prototype_ `virtual uint32 GetNumSelectableItems() const override;`
- L17 _public prototype_ `virtual void EnumerateSelectableItems(TFunctionRef<EBreakBehavior(const ConcertSharedSlate::FSelectableObjectInfo& SelectableOption)> Delegate) const override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ConcertClientSharedSlate` (scope `UE`)

### `Plugins/Developer/Concert/ConcertUI/ConcertClientSharedSlate/Source/ConcertClientSharedSlate/Public/Replication/Editor/Model/ObjectSource/WorldActorSource.h` (Public)


#### class `UE::ConcertClientSharedSlate::FWorldActorSource`  
`class FWorldActorSource : public ConcertSharedSlate::IObjectSourceModel`  
_L11-20_
- inherits: `ConcertSharedSlate::IObjectSourceModel`
- desc: Gets all the actors in the current GWorld
- L16 _public prototype_ `virtual ConcertSharedSlate::FSourceDisplayInfo GetDisplayInfo() const override;`
- L17 _public prototype_ `virtual uint32 GetNumSelectableItems() const override;`
- L18 _public prototype_ `virtual void EnumerateSelectableItems(TFunctionRef<EBreakBehavior(const ConcertSharedSlate::FSelectableObjectInfo& SelectableOption)> Delegate) const override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ConcertClientSharedSlate` (scope `UE`)

### `Plugins/Developer/Concert/ConcertUI/ConcertClientSharedSlate/Source/ConcertClientSharedSlate/Public/Replication/Editor/Model/PropertySource/ConcertSyncCoreReplicatedPropertySource.h` (Public)


#### class `UE::ConcertClientSharedSlate::PRAGMA_DISABLE_DEPRECATION_WARNINGS`  
`PRAGMA_DISABLE_DEPRECATION_WARNINGS : public ConcertSharedSlate::IPropertySourceModel PRAGMA_ENABLE_DEPRECATION_WARNINGS`  
_L18-40_
- reflection: `UE_DEPRECATED(5.5, "No longer in use")`
- inherits: `ConcertSharedSlate::IPropertySourceModelPRAGMA_ENABLE_DEPRECATION_WARNINGS`
- desc: The allowed properties are those returned by UE::ConcertSyncCore::ForEachReplicatableProperty.
- L24 _public prototype_ `void SetClass(UClass* InClass);`
- L27 _public prototype_ `virtual ConcertSharedSlate::FSourceDisplayInfo GetDisplayInfo() const override;`
- L28 _public function_ `virtual uint32 GetNumSelectableItems() const override`
- L30 _public prototype_ `virtual void EnumerateSelectableItems(TFunctionRef<EBreakBehavior(const ConcertSharedSlate::FSelectablePropertyInfo& SelectableOption)> Delegate) const override;`
- L37 _private member_ `TWeakObjectPtr<UClass> Class;` — Weak ptr because it could be a Blueprint class that can be destroyed at any time.
- L39 _private member_ `int32 NumProperties = 0;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace ConcertClientSharedSlate` (scope `UE`)

### `Plugins/Developer/Concert/ConcertUI/ConcertClientSharedSlate/Source/ConcertClientSharedSlate/Public/Replication/Editor/Model/PropertySource/ReplicatablePropertySource.h` (Public)


#### class `UE::ConcertClientSharedSlate::FReplicatablePropertySource`  
`class FReplicatablePropertySource : public ConcertSharedSlate::IPropertySource`  
_L11-37_
- inherits: `ConcertSharedSlate::IPropertySource`
- desc: Lists all properties that can be replicated.
- L15 _public function_ `explicit FReplicatablePropertySource(UClass* Class) : Class(Class)`
- L20 _public function_ `virtual void EnumerateProperties(TFunctionRef<EBreakBehavior(const ConcertSharedSlate::FPropertyInfo& Property)> Delegate) const override`
- L36 _private member_ `TWeakObjectPtr<UClass> Class;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ConcertClientSharedSlate` (scope `UE`)
- L28 _function_ `` (scope `UE::ConcertClientSharedSlate::FReplicatablePropertySource::EnumerateProperties`)

### `Plugins/Developer/Concert/ConcertUI/ConcertClientSharedSlate/Source/ConcertClientSharedSlate/Public/Replication/Editor/Model/PropertySource/SelectPropertyFromUClassModel.h` (Public)


#### class `UE::ConcertClientSharedSlate::FSelectPropertyFromUClassModel`  
`class FSelectPropertyFromUClassModel : public ConcertSharedSlate::IPropertySourceProcessor`  
_L17-27_
- inherits: `ConcertSharedSlate::IPropertySourceProcessor`
- desc: Decides which properties can be added to IEditableReplicationStreamModel. The allowed properties are those returned by UE::ConcertSyncCore::ForEachReplicatableProperty.
- L22 _public prototype_ `virtual void ProcessPropertySource( const ConcertSharedSlate::FPropertySourceContext& Context, TFunctionRef<void(const ConcertSharedSlate::IPropertySource& Model)> Processor ) const override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ConcertClientSharedSlate` (scope `UE`)

### `Plugins/Developer/Concert/ConcertUI/ConcertClientSharedSlate/Source/ConcertClientSharedSlate/Public/Replication/Editor/Model/PropertyUtils.h` (Public)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ConcertClientSharedSlate` (scope `UE`)
- L12 _namespace_ `namespace PropertyUtils` (scope `UE::ConcertClientSharedSlate`)
- L26 _prototype_ `void EnumerateAdditionalPropertiesToAdd( const UClass& ObjectClass, TConstArrayView<FConcertPropertyChain> PropertiesToAdd, TFunctionRef<void(FConcertPropertyChain&& AdditionalProperty)> Callback );` (scope `UE::ConcertClientSharedSlate::PropertyUtils`) — Called when the user adds a property in the property tree view. This finds additional properties that should also be added. Examples: - User adds a struct property: Add all child properties automatically - User adds a container property: All all child properties automatically if it is a struct @param ObjectClass The class the properties belong to @param PropertiesToAdd The properties about to be added a replication stream model @param Callback Callback to receive the additional properties
- L33 _function_ `inline void AppendAdditionalPropertiesToAdd(const UClass& ObjectClass, TArray<FConcertPropertyChain>& InOutPropertiesToAdd)` (scope `UE::ConcertClientSharedSlate::PropertyUtils`) — Special version of EnumerateAdditionalPropertiesToAdd that appends any additional properties to the same array.
- L37 _function_ `EnumerateAdditionalPropertiesToAdd(ObjectClass, InOutPropertiesToAdd, [&AdditionalProperties](FConcertPropertyChain&& Chain){ AdditionalProperties.Emplace(MoveTemp(Chain)); });` (scope `UE::ConcertClientSharedSlate::PropertyUtils::AppendAdditionalPropertiesToAdd`)
- L41 _function_ `inline void AppendAdditionalPropertiesToAdd(const FSoftClassPath& ObjectClass, TArray<FConcertPropertyChain>& InOutPropertiesToAdd)` (scope `UE::ConcertClientSharedSlate::PropertyUtils`)

### `Plugins/Developer/Concert/ConcertUI/ConcertClientSharedSlate/Source/ConcertClientSharedSlate/Public/Replication/Editor/UnrealEditor/HideObjectsNotInWorldLogic.h` (Public)


#### class `UE::ConcertClientSharedSlate::FHideObjectsNotInWorldLogic`  
`class FHideObjectsNotInWorldLogic : public FNoncopyable`  
_L17-37_
- inherits: `FNoncopyable`
- desc: This logic is used to show only those replicated objects that are in the world the user has opened in the editor. Its functions are injected into the FCreateViewerParams.
- L21 _public prototype_ `FHideObjectsNotInWorldLogic();`
- L22 _public prototype_ `~FHideObjectsNotInWorldLogic();`
- L25 _public prototype_ `bool ShouldShowObject(const FSoftObjectPath& ObjectPath) const;` — @return Whether this object should be shown to the user.
- L27 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnRefreshObjects);`
- L28 _public function_ `FOnRefreshObjects& OnRefreshObjects()`
- L33 _private member_ `FOnRefreshObjects OnRefreshObjectsDelegate;` — Broadcasts when the set of displayed objects has changed, e.g. when switching worlds.
- L35 _private function_ `void OnWorldAdded(UWorld* World) const`
- L36 _private function_ `void OnWorldDestroyed(UWorld* World) const`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ConcertClientSharedSlate` (scope `UE`)
- L27 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnRefreshObjects);`

### `Plugins/Developer/Concert/ConcertUI/ConcertClientSharedSlate/Source/ConcertClientSharedSlate/Public/Replication/Editor/UnrealEditor/ModifyObjectInLevelHandler.h` (Public)


#### class `UE::ConcertClientSharedSlate::FModifyObjectInLevelHandler`  
`class FModifyObjectInLevelHandler : public FNoncopyable`  
_L26-52_
- inherits: `FNoncopyable`
- desc: Handles updating the passed in model in the following cases: - Actor removed: Remove from model - Component or subobject added / removed: refresh hierarchy
- L33 _public prototype_ `FModifyObjectInLevelHandler( ConcertSharedSlate::IEditableReplicationStreamModel& UpdatedModel UE_LIFETIMEBOUND );` — @param UpdatedModel The model to modified when an object is modified. The caller ensures it outlives the constructed object.
- L36 _public prototype_ `~FModifyObjectInLevelHandler();`
- L38 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnHierarchyNeedsRefresh);`
- L40 _public function_ `FOnHierarchyNeedsRefresh& OnHierarchyNeedsRefresh()` — Broadcasts when the hierarchy may have changed.
- L45 _private member_ `ConcertSharedSlate::IEditableReplicationStreamModel& UpdatedModel;` — The model that is updated when an object is modified.
- L48 _private member_ `FOnHierarchyNeedsRefresh OnHierarchyNeedsRefreshDelegate;` — Broadcasts when the hierarchy may have changed.
- L50 _private prototype_ `void OnActorDeleted(AActor* Actor) const;`
- L51 _private prototype_ `void OnObjectTransacted(UObject* Object, const FTransactionObjectEvent& TransactionObjectEvent) const;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace ConcertClientSharedSlate` (scope `UE`)
- L38 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnHierarchyNeedsRefresh);`

### `Plugins/Developer/Concert/ConcertUI/ConcertClientSharedSlate/Source/ConcertClientSharedSlate/Public/Replication/ObjectNameUtils.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ConcertClientSharedSlate` (scope `UE`)
- L12 _prototype_ `FText GetObjectDisplayName(const TSoftObjectPtr<>& ObjectPath);` (scope `UE::ConcertClientSharedSlate`) — @return The display name of ObjectPath to use for Concert replication UI.

### `Plugins/Developer/Concert/ConcertUI/ConcertClientSharedSlate/Source/ConcertClientSharedSlate/Public/Replication/Settings/ConcertInheritableClassOption.h` (Public)


#### struct `FConcertInheritableClassOption`  
`struct FConcertInheritableClassOption`  
_L9-16_
- reflection: `USTRUCT()`
- desc: Base struct for settings intended for classes
- L15 _public member_ `bool bInheritFromBase = true;` — `UPROPERTY(EditAnywhere, Category = "Config")` — Whether to inherit the settings from the base class.

### `Plugins/Developer/Concert/ConcertUI/ConcertClientSharedSlate/Source/ConcertClientSharedSlate/Public/Replication/Settings/ConcertPerClassSubobjectMatchingRules.h` (Public)


#### struct `FConcertInheritableSubobjectMatchingRules`  
`struct FConcertInheritableSubobjectMatchingRules : public FConcertSubobjectMatchingRules`  
_L9-16_
- reflection: `USTRUCT()`
- inherits: `FConcertSubobjectMatchingRules`
- L15 _public member_ `bool bInheritFromBase = true;` — `UPROPERTY(EditAnywhere, Category = "Config")` — Whether to inherit the settings from the base class.

#### struct `FConcertPerClassSubobjectMatchingRules`  
`struct FConcertPerClassSubobjectMatchingRules`  
_L26-50_
- reflection: `USTRUCT()`
- desc: Binds subobject matching rules to classes. The matching rules can then be applied recursively, if FConcertSubobjectDefaultSelectionRules::bInheritFromBase is set to true. For example, suppose you have set up two sets of rules: one for matching subobjects of an UStaticMeshComponent and one for USkeletalMeshComponent. If the bInheritFromBase is set true for USkeletalMeshComponent's rules, then UStaticMeshComponent will also be applied when searching a skeletal mesh component.
- L38 _public member_ `TMap<FSoftClassPath, FConcertInheritableSubobjectMatchingRules> SubobjectMatchingRules;` — `UPROPERTY(EditAnywhere, Config, Category = "Replication|Editor")` — Maps matching rules to actor and component classes. Examples: - Whenever you add a StaticMeshActor actor, you its static mesh component to be added automatically, too (set IncludeSubobjectRegex to the components name). - Whenever you add a component, you want to add its child components, too (set IncludeAllOption = AllComponents) .
- L41 _public prototype_ `void MatchSubobjectsRecursivelyBreakable(const UObject& Object, TFunctionRef<EBreakBehavior(UObject&)> OnSubobjectMatched) const;` — Recursively walks up Object class hierarchy and tries to find subobjects
- L42 _public function_ `void MatchSubobjectsRecursively(const UObject& Object, TFunctionRef<void(UObject&)> OnSubobjectMatched) const`

#### Free symbols / members of external scopes

- L45 _function_ `` (scope `FConcertPerClassSubobjectMatchingRules::MatchSubobjectsRecursively`)

### `Plugins/Developer/Concert/ConcertUI/ConcertClientSharedSlate/Source/ConcertClientSharedSlate/Public/Replication/Settings/ConcertStreamObjectAutoBindingRules.h` (Public)


#### struct `FConcertDefaultPropertySelection`  
`struct FConcertDefaultPropertySelection : public FConcertInheritableClassOption`  
_L15-26_
- reflection: `USTRUCT()`
- inherits: `FConcertInheritableClassOption`
- L25 _public member_ `TArray<FString> DefaultSelectedProperties;` — `UPROPERTY(EditAnywhere, Category = "Config")` — A list of properties that should be selected by default when you add a new object type. Specify properties by using the names as the appear in the replication editor and each property with ".". Example: "RelativeLocation.X"

#### struct `FConcertStreamObjectAutoBindingRules`  
`struct FConcertStreamObjectAutoBindingRules`  
_L33-54_
- reflection: `USTRUCT()`
- desc: When a user adds an object via the stream editor, you may want to automatically bind properties and add additional subobjects This structure contains rules to achieve this.
- L39 _public member_ `TMap<FSoftClassPath, FConcertDefaultPropertySelection> DefaultPropertySelection;` — `UPROPERTY(EditAnywhere, Category = "Replication|Editor")` — Properties you want selected by default when you add a new replicated object in the editor
- L50 _public member_ `FConcertPerClassSubobjectMatchingRules DefaultAddedSubobjectRules;` — `UPROPERTY(EditAnywhere, Category = "Replication|Editor")` — Rules for auto adding additional subobjects. For example, you can set this up so when you add a static mesh actor, its static mesh component is automatically added, too. The simplest way to achieve this is to bind AStaticMeshActor class to a setting with IncludeAllOption set to AllComponents. Matched subobjects will be auto added, too.
- L53 _public prototype_ `void AddDefaultPropertiesFromSettings(UClass& Class, TFunctionRef<void(FConcertPropertyChain&& Chain)> Callback) const;` — Reads DefaultPropertySelection and calls Callback for any default property selections based on the Class just added.

### `Plugins/Developer/Concert/ConcertUI/ConcertClientSharedSlate/Source/ConcertClientSharedSlate/Public/Replication/Settings/ConcertSubobjectMatchingRules.h` (Public)


#### enum `EConcertIncludeAllSubobjectsType`  
`enum class EConcertIncludeAllSubobjectsType : uint8`  
_L11-19_
- reflection: `UENUM()`
- L14 _public enumerator_ `None` — Include nothing by default
- L16 _public enumerator_ `AllComponents` — Include all components
- L18 _public enumerator_ `AllSubobjects` — Include all subobjects recursively (includes components, their subobjects, etc. )

#### struct `FConcertSubobjectMatchingRules`  
`struct FConcertSubobjectMatchingRules`  
_L23-71_
- reflection: `USTRUCT()`
- desc: Defines rules for finding subobjects of an object.
- L32 _public member_ `TSet<FSoftClassPath> IncludeClasses;` — `UPROPERTY(EditAnywhere, Category = "Config")` — A list of subobject classes to add by default. For example, when you add an actor, you want to also add certain component classes.
- L42 _public member_ `TSet<FString> ExcludeSubobjectRegex;` — `UPROPERTY(EditAnywhere, Category = "Config")` — Components that match any of this regex will be excluded from IncludeClasses. Tips: - If you want to include "Component" but not "ComponentName" you can use boundaries "\bComponent\b". . ".*" matches any sequence of characters.
- L52 _public member_ `TSet<FString> IncludeSubobjectRegex;` — `UPROPERTY(EditAnywhere, Category = "Config")` — Components that match any of this regex will be included as well. Tips: - If you want to include "Component" but not "ComponentName" you can use boundaries "\bComponent\b". . ".*" matches any sequence of characters.
- L56 _public member_ `EConcertIncludeAllSubobjectsType IncludeAllOption = EConcertIncludeAllSubobjectsType::None;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Config")` — Behaviour to configure for including all of a certain type of subobject.
- L62 _public prototype_ `void MatchToSubobjectsBreakable(const UObject& AddedObject, TFunctionRef<EBreakBehavior(UObject&)> OnSubobjectMatched) const;` — Looks for subobjects in AddedObject that match these rules. This looks for direct subobjects only though you can call MatchToSubobjectsIn recursively on what you received through OnSubobjectMatched.
- L63 _public function_ `void MatchToSubobjects(const UObject& AddedObject, TFunctionRef<void(UObject&)> OnSubobjectMatched) const`

#### Free symbols / members of external scopes

- L66 _function_ `` (scope `FConcertSubobjectMatchingRules::MatchToSubobjects`)

### `Plugins/Developer/Concert/ConcertUI/ConcertClientSharedSlate/Source/ConcertClientSharedSlate/Public/Widgets/Client/ClientInfoHelpers.h` (Public)


#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace ConcertClientSharedSlate` (scope `UE`)
- L17 _function_ `inline ConcertSharedSlate::FGetOptionalClientInfo MakeClientInfoGetter(const TSharedRef<IConcertClient>& Client)` (scope `UE::ConcertClientSharedSlate`)
- L20 _function_ `` (scope `UE::ConcertClientSharedSlate::MakeClientInfoGetter`)
- L45 _function_ `inline ConcertSharedSlate::FIsLocalClient MakeIsLocalClientGetter(const TSharedRef<IConcertClient>& Client)` (scope `UE::ConcertClientSharedSlate`)
- L48 _function_ `` (scope `UE::ConcertClientSharedSlate::MakeIsLocalClientGetter`)
- L55 _function_ `inline ConcertSharedSlate::FGetClientParenthesesContent MakeGetLocalClientParenthesesContent(const TSharedRef<IConcertClient>& Client)` (scope `UE::ConcertClientSharedSlate`) — @return A parentheses delegate that returns "You" if the endpoint ID is that of Client and returns FText::GetEmpty() otherwise.
- L58 _function_ `` (scope `UE::ConcertClientSharedSlate::MakeGetLocalClientParenthesesContent`)
- L67 _function_ `inline TAttribute<TOptional<FConcertClientInfo>> MakeLocalClientInfoAttribute(const TSharedRef<IConcertClient>& Client)` (scope `UE::ConcertClientSharedSlate`)
- L70 _function_ `` (scope `UE::ConcertClientSharedSlate::MakeLocalClientInfoAttribute`)
- L76 _function_ `inline TAttribute<TOptional<FConcertClientInfo>> MakeClientInfoAttribute(const TSharedRef<IConcertClient>& Client, const FGuid& ClientId)` (scope `UE::ConcertClientSharedSlate`)
- L79 _function_ `` (scope `UE::ConcertClientSharedSlate::MakeClientInfoAttribute`)
