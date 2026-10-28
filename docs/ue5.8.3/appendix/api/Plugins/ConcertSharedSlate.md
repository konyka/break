# Plugins / ConcertSharedSlate

- module root: `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate`
- headers: 96; symbols: 1767
- symbol kinds: class=76, delegate=60, enum=22, enumerator=66, externvar=13, function=310, macro=21, member=400, namespace=180, prototype=537, struct=39, typedef=33, variable=10
- PrivateDependencyModuleNames: ConcertSyncCore, ConcertTransport, Engine, InputCore, Json, Projects, SlateCore, ToolMenus, ToolWidgets
- PublicDependencyModuleNames: Concert, ConcertSyncCore, Core, CoreUObject, Slate, UndoHistory

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Private/Replication/Editor/Model/Data/PropertyNodeData.h` (Private)


#### class `UE::ConcertSharedSlate::FCategoryData`  
`class FCategoryData`  
_L14-26_
- desc: A node in the tree view which groups a subobject.
- L18 _public function_ `FCategoryData(TArray<TSoftObjectPtr<>> InContextObjects) : ContextObjects(MoveTemp(InContextObjects))`
- L20 _public function_ `const TArray<TSoftObjectPtr<>>& GetContextObjects() const`
- L25 _private member_ `const TArray<TSoftObjectPtr<>> ContextObjects;` — The objects this category represents; all the objects are releated, i.e. ActorA's StaticMeshComponent0 and ActorB's StaticMeshComponent0.

#### class `UE::ConcertSharedSlate::FPropertyNodeData`  
`class FPropertyNodeData`  
_L29-49_
- desc: Instanced for each property row in IPropertyTreeView.
- L33 _public function_ `FPropertyNodeData(FPropertyData PropertyData) : PropertyData(MoveTemp(PropertyData))`
- L36 _public function_ `FPropertyNodeData(FCategoryData CategoryData) : CategoryData(MoveTemp(CategoryData))`
- L40 _public function_ `bool IsCategoryNode() const`
- L42 _public function_ `const TOptional<FPropertyData>& GetPropertyData() const`
- L43 _public function_ `const TOptional<FCategoryData>& GetCategoryData() const`
- L47 _private member_ `const TOptional<FPropertyData> PropertyData;`
- L48 _private member_ `const TOptional<FCategoryData> CategoryData;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Private/Replication/Editor/Model/GenericReplicationStreamModel.h` (Private)


#### class `UE::ConcertSharedSlate::FGenericReplicationStreamModel`  
`class FGenericReplicationStreamModel : public IEditableReplicationStreamModel`  
_L17-58_
- inherits: `IEditableReplicationStreamModel`
- desc: Implements logic for editing a FConcertObjectReplicationMap.
- L22 _public prototype_ `FGenericReplicationStreamModel( TAttribute<FConcertObjectReplicationMap*> InReplicationMapAttribute, TSharedPtr<IStreamExtender> InExtender = nullptr );`
- L28 _public prototype_ `virtual FSoftClassPath GetObjectClass(const FSoftObjectPath& Object) const override;`
- L29 _public prototype_ `virtual bool ContainsObjects(const TSet<FSoftObjectPath>& Objects) const override;`
- L30 _public prototype_ `virtual bool ContainsProperties(const FSoftObjectPath& Object, const TSet<FConcertPropertyChain>& Properties) const override;`
- L31 _public prototype_ `virtual bool ForEachReplicatedObject(TFunctionRef<EBreakBehavior(const FSoftObjectPath& Object)> Delegate) const override;`
- L32 _public prototype_ `virtual bool ForEachProperty(const FSoftObjectPath& Object, TFunctionRef<EBreakBehavior(const FConcertPropertyChain& Parent)> Delegate) const override;`
- L33 _public prototype_ `virtual uint32 GetNumProperties(const FSoftObjectPath& Object) const override;`
- L37 _public prototype_ `virtual void AddObjects(TConstArrayView<UObject*> Objects) override;`
- L38 _public prototype_ `virtual void RemoveObjects(TConstArrayView<FSoftObjectPath> Objects) override;`
- L39 _public prototype_ `virtual void AddProperties(const FSoftObjectPath&, TConstArrayView<FConcertPropertyChain> Properties) override;`
- L40 _public prototype_ `virtual void RemoveProperties(const FSoftObjectPath&, TConstArrayView<FConcertPropertyChain> Properties) override;`
- L41 _public function_ `virtual FOnObjectsChanged& OnObjectsChanged() override`
- L42 _public function_ `virtual FOnPropertiesChanged& OnPropertiesChanged() override`
- L48 _private member_ `const TAttribute<FConcertObjectReplicationMap*> ReplicationMapAttribute;` — Returns the replication map that is supposed to be edited.
- L51 _private member_ `TSharedPtr<IStreamExtender> Extender;` — Adds properties and objects when an object is added. Can be null.
- L53 _private member_ `FOnObjectsChanged OnObjectsChangedDelegate;`
- L54 _private member_ `FOnPropertiesChanged OnPropertiesChangedDelegate;`
- L57 _private prototype_ `void ExtendObjects(FConcertObjectReplicationMap& ReplicationMap, UObject& AddedObject, TArray<UObject*>& ObjectsAddedSoFar);` — Applies Extender to AddedObject whilst adding any additionally added UObjects to ObjectsAddedSoFar and avoiding adding objects already added to ObjectsAddedSoFar.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Private/Replication/Editor/Model/ReadableReplicationStreamModel.h` (Private)


#### class `UE::ConcertSharedSlate::FReadableReplicationStreamModel`  
`class FReadableReplicationStreamModel : public IReplicationStreamModel`  
_L17-37_
- inherits: `IReplicationStreamModel`
- desc: Implements logic for reading a FConcertObjectReplicationMap.
- L22 _public prototype_ `FReadableReplicationStreamModel(TAttribute<const FConcertObjectReplicationMap*> InReplicationMapAttribute);`
- L25 _public prototype_ `virtual FSoftClassPath GetObjectClass(const FSoftObjectPath& Object) const override;`
- L26 _public prototype_ `virtual bool ContainsObjects(const TSet<FSoftObjectPath>& Objects) const override;`
- L27 _public prototype_ `virtual bool ContainsProperties(const FSoftObjectPath& Object, const TSet<FConcertPropertyChain>& Properties) const override;`
- L28 _public prototype_ `virtual bool ForEachReplicatedObject(TFunctionRef<EBreakBehavior(const FSoftObjectPath& Object)> Delegate) const override;`
- L29 _public prototype_ `virtual bool ForEachProperty(const FSoftObjectPath& Object, TFunctionRef<EBreakBehavior(const FConcertPropertyChain& Parent)> Delegate) const override;`
- L30 _public prototype_ `virtual uint32 GetNumProperties(const FSoftObjectPath& Object) const override;`
- L36 _private member_ `const TAttribute<const FConcertObjectReplicationMap*> ReplicationMapAttribute;` — Returns the replication map that is supposed to be edited.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Private/Replication/Editor/Model/SharedReplicationStreamModelGetters.h` (Private)


#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L17 _namespace_ `namespace SharedStreamGetters` (scope `UE::ConcertSharedSlate`)
- L20 _prototype_ `FSoftClassPath GetObjectClass(const FConcertObjectReplicationMap* ReplicationMap, const FSoftObjectPath& Object);` (scope `UE::ConcertSharedSlate::SharedStreamGetters`) — @return Gets the object class from ReplicationMap for Object.
- L22 _prototype_ `bool ContainsObjects(const FConcertObjectReplicationMap* ReplicationMap, const TSet<FSoftObjectPath>& Objects);` (scope `UE::ConcertSharedSlate::SharedStreamGetters`) — @return Whether all the objects are contained in ReplicationMap.
- L24 _prototype_ `bool ContainsProperties(const FConcertObjectReplicationMap* ReplicationMap, const FSoftObjectPath& Object, const TSet<FConcertPropertyChain>& Properties);` (scope `UE::ConcertSharedSlate::SharedStreamGetters`) — @return Whether Object has the given properties assigned.
- L26 _prototype_ `bool ForEachReplicatedObject(const FConcertObjectReplicationMap* ReplicationMap, TFunctionRef<EBreakBehavior(const FSoftObjectPath& Object)> Delegate);` (scope `UE::ConcertSharedSlate::SharedStreamGetters`) — @return Whether Delegate was invokes at least once.
- L28 _prototype_ `bool ForEachProperty(const FConcertObjectReplicationMap* ReplicationMap, const FSoftObjectPath& Object, TFunctionRef<EBreakBehavior(const FConcertPropertyChain& Parent)> Delegate);` (scope `UE::ConcertSharedSlate::SharedStreamGetters`) — @return Whether Delegate was invokes at least once.
- L30 _prototype_ `uint32 GetNumProperties(const FConcertObjectReplicationMap* ReplicationMap, const FSoftObjectPath& Object);` (scope `UE::ConcertSharedSlate::SharedStreamGetters`) — @return Number of properties assigned to Object

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Private/Replication/Editor/Utils/DisplayUtils.h` (Private)


#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L23 _namespace_ `namespace PropertyChain` (scope `UE::ConcertSyncCore`)
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L25 _namespace_ `namespace DisplayUtils` (scope `UE::ConcertSharedSlate`)
- L28 _prototype_ `FText GetObjectDisplayText(const TSoftObjectPtr<>& Object, IObjectNameModel* Model = nullptr);` (scope `UE::ConcertSharedSlate::DisplayUtils`) — Unified version that reads from IObjectNameModel or defaults to extracting the name from the path.
- L29 _function_ `inline FText GetObjectDisplayText(const TSoftObjectPtr<>& Object, const TSharedPtr<IObjectNameModel>& Model = nullptr)` (scope `UE::ConcertSharedSlate::DisplayUtils`)
- L32 _prototype_ `FText ExtractObjectDisplayTextFromPath(const FSoftObjectPath& Object);` (scope `UE::ConcertSharedSlate::DisplayUtils`) — @return The text to use for displaying this object's name
- L35 _prototype_ `FString GetObjectDisplayString(const UObject& Object);` (scope `UE::ConcertSharedSlate::DisplayUtils`) — @return More lightweight version of GetObjectDisplayText which does not construct any FText.
- L38 _prototype_ `FText GetObjectTypeText(const FSoftClassPath& ClassPath);` (scope `UE::ConcertSharedSlate::DisplayUtils`) — @return The text to use for displaying this object's type
- L41 _prototype_ `FSlateIcon GetObjectIcon(const FSoftClassPath& ClassPath);` (scope `UE::ConcertSharedSlate::DisplayUtils`) — @return The icon to use for this object
- L43 _prototype_ `FSlateIcon GetObjectIcon(UObject& Object);` (scope `UE::ConcertSharedSlate::DisplayUtils`) — @return The icon to use for this object
- L46 _prototype_ `FText GetPropertyDisplayText(ConcertSyncCore::PropertyChain::FPropertyResolutionCache& Cache, const FConcertPropertyChain& Property, UStruct* Class = nullptr);` (scope `UE::ConcertSharedSlate::DisplayUtils`) — @return The text to use for displaying this property's name. Uses Class to determine class name if available.
- L48 _prototype_ `FString GetPropertyDisplayString(ConcertSyncCore::PropertyChain::FPropertyResolutionCache& Cache, const FConcertPropertyChain& Property, UStruct* Class = nullptr);` (scope `UE::ConcertSharedSlate::DisplayUtils`) — @return More lightweight version of GetPropertyDisplayString which does not construct any FText. Uses Class to determine class name if available.

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Private/Replication/Editor/Utils/PropertyEnumerationUtils.h` (Private)


#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L19 _typedef_ `using FEnumerateProperties = TFunctionRef<EBreakBehavior(const FSoftClassPath&, const FConcertPropertyChain&)>;` (scope `UE::ConcertSharedSlate`)
- L22 _prototype_ `FSoftClassPath GetObjectClassFromModelOrLoad(const TSoftObjectPtr<>& Object, const IReplicationStreamModel& Model);` (scope `UE::ConcertSharedSlate`) — Gets the class from the model or loads it. This function is designed to be used without assuming that it is run in editor-builds.
- L25 _prototype_ `void EnumerateProperties(TConstArrayView<TSoftObjectPtr<>> Objects, const IReplicationStreamModel& Model, const IPropertySourceProcessor* OptionalSource, FEnumerateProperties Callback);` (scope `UE::ConcertSharedSlate`) — Calls EnumerateRegisteredPropertiesOnly or EnumerateAllProperties depending on whether OptionalSource is nullptr.
- L27 _prototype_ `void EnumerateRegisteredPropertiesOnly(TConstArrayView<TSoftObjectPtr<>> Objects, const IReplicationStreamModel& Model, FEnumerateProperties Callback);` (scope `UE::ConcertSharedSlate`) — Enumerates the properties that are assigned to the object in Model
- L29 _prototype_ `void EnumerateAllProperties(TConstArrayView<TSoftObjectPtr<>> Objects, const IPropertySourceProcessor& Source, const IReplicationStreamModel& Model, FEnumerateProperties Callback);` (scope `UE::ConcertSharedSlate`) — Enumerate the properties that are selectable in Source (e.g. all properties in that class, @see FSelectPropertyFromUClassModel).

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Private/Replication/Editor/View/Column/ObjectColumnAdapter.h` (Private)


#### class `UE::ConcertSharedSlate::FObjectColumnAdapter`  
`class FObjectColumnAdapter : public IReplicationTreeColumn<FReplicatedObjectData>`  
_L12-58_
- inherits: `IReplicationTreeColumn<FReplicatedObjectData>`
- desc: Adapts an IObjectTreeColumn to IReplicationTreeColumn<FPropertyData>. It simply passes additional info down to IPropertyTreeColumn.
- L16 _public function_ `static TArray<TReplicationColumnEntry<FReplicatedObjectData>> Transform(const TArray<FObjectColumnEntry>& Entries)`
- L33 _public function_ `FObjectColumnAdapter(TSharedRef<IObjectTreeColumn> InAdaptedColumn) : AdaptedColumn(MoveTemp(InAdaptedColumn))`
- L37 _public function_ `virtual SHeaderRow::FColumn::FArguments CreateHeaderRowArgs() const override`
- L38 _public function_ `virtual TSharedRef<SWidget> GenerateColumnWidget(const FBuildArgs& InArgs) override`
- L42 _public function_ `virtual void PopulateSearchString(const FReplicatedObjectData& InItem, TArray<FString>& InOutSearchStrings) const override`
- L47 _public function_ `virtual bool CanBeSorted() const override`
- L48 _public function_ `virtual bool IsLessThan(const FReplicatedObjectData& Left, const FReplicatedObjectData& Right) const override`
- L52 _private member_ `TSharedRef<IObjectTreeColumn> AdaptedColumn;`
- L54 _private function_ `static FObjectTreeRowContext Transform(FReplicatedObjectData Data)`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L20 _function_ `` (scope `UE::ConcertSharedSlate::FObjectColumnAdapter::Transform`)
- L23 _function_ `` (scope `UE::ConcertSharedSlate::FObjectColumnAdapter::Transform::__anon1385c31a0102`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Private/Replication/Editor/View/Column/PropertyColumnAdapter.h` (Private)


#### class `UE::ConcertSharedSlate::FPropertyColumnAdapter`  
`class FPropertyColumnAdapter : public IReplicationTreeColumn<FPropertyNodeData>`  
_L13-61_
- inherits: `IReplicationTreeColumn<FPropertyNodeData>`
- desc: Adapts an IPropertyTreeColumn to IReplicationTreeColumn<FPropertyData>. It simply passes additional info down to IPropertyTreeColumn.
- L17 _public function_ `static TArray<TReplicationColumnEntry<FPropertyNodeData>> Transform(const TArray<FPropertyColumnEntry>& Entries)`
- L34 _public function_ `FPropertyColumnAdapter(TSharedRef<IPropertyTreeColumn> InAdaptedColumn) : AdaptedColumn(MoveTemp(InAdaptedColumn))`
- L38 _public function_ `virtual SHeaderRow::FColumn::FArguments CreateHeaderRowArgs() const override`
- L39 _public function_ `virtual TSharedRef<SWidget> GenerateColumnWidget(const FBuildArgs& InArgs) override`
- L43 _public function_ `virtual void PopulateSearchString(const FPropertyNodeData& InItem, TArray<FString>& InOutSearchStrings) const override`
- L48 _public function_ `virtual bool CanBeSorted() const override`
- L49 _public function_ `virtual bool IsLessThan(const FPropertyNodeData& Left, const FPropertyNodeData& Right) const override`
- L53 _private member_ `TSharedRef<IPropertyTreeColumn> AdaptedColumn;`
- L55 _private function_ `static FPropertyTreeRowContext Transform(const FPropertyNodeData& Data)`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L21 _function_ `` (scope `UE::ConcertSharedSlate::FPropertyColumnAdapter::Transform`)
- L24 _function_ `` (scope `UE::ConcertSharedSlate::FPropertyColumnAdapter::Transform::__anonc7a177e80102`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Private/Replication/Editor/View/MultiEditor/ConsolidatedMultiStreamModel.h` (Private)


#### class `UE::ConcertSharedSlate::FConsolidatedMultiStreamModel`  
`class FConsolidatedMultiStreamModel : public IEditableReplicationStreamModel`  
_L29-90_
- inherits: `IEditableReplicationStreamModel`
- desc: Combines multiple streams into one and allows you to query whether an object is contained by any of them Does not NOT support property queries. Implements functions in a specific way to allow editing of multiple streams in a single SBaseReplicationStreamEditor UI. Coupled to SMultiReplicationStreamEditor. How this works: - AddObject & RemoveObject calls are forwarded to ConsolidatedStreamModel - Object getters, like ForEachReplicatedObject, query ConsolidatedStreamModel AND the multiple streams in MultiStreamModel - Property editing is not supported SMultiReplicationStreamEditor's responsibility is to consolidate all replicated objects in a single UI and display all properties in the class. The creator of SMultiReplicationStreamEditor is supposed to inject custom columns into the property section for assigning specific properties to the streams in the IEditableReplicationStreamModel.
- L34 _public prototype_ `FConsolidatedMultiStreamModel( TSharedRef<IEditableReplicationStreamModel> InConsolidatedModel, TSharedRef<IEditableMultiReplicationStreamModel> InMultiStreamModel, FGetAutoAssignTarget InGetAutoAssignTargetDelegate );`
- L42 _public prototype_ `virtual FSoftClassPath GetObjectClass(const FSoftObjectPath& Object) const override;`
- L43 _public prototype_ `virtual bool ContainsObjects(const TSet<FSoftObjectPath>& Objects) const override;`
- L44 _public prototype_ `virtual bool ContainsProperties(const FSoftObjectPath& Object, const TSet<FConcertPropertyChain>& Properties) const override;`
- L45 _public prototype_ `virtual bool ForEachReplicatedObject(TFunctionRef<EBreakBehavior(const FSoftObjectPath& Object)> Delegate) const override;`
- L46 _public prototype_ `virtual bool ForEachProperty(const FSoftObjectPath& Object, TFunctionRef<EBreakBehavior(const FConcertPropertyChain& Property)> Delegate) const override;`
- L47 _public prototype_ `virtual uint32 GetNumProperties(const FSoftObjectPath& Object) const override;`
- L51 _public prototype_ `virtual void AddObjects(TConstArrayView<UObject*> Objects) override;`
- L52 _public prototype_ `virtual void RemoveObjects(TConstArrayView<FSoftObjectPath> Objects) override;`
- L53 _public function_ `virtual void AddProperties(const FSoftObjectPath& Object, TConstArrayView<FConcertPropertyChain> Properties) override`
- L54 _public function_ `virtual void RemoveProperties(const FSoftObjectPath& Object, TConstArrayView<FConcertPropertyChain> Properties) override`
- L55 _public function_ `virtual FOnObjectsChanged& OnObjectsChanged() override`
- L56 _public function_ `virtual FOnPropertiesChanged& OnPropertiesChanged() override`
- L67 _private member_ `TSharedRef<IEditableReplicationStreamModel> ConsolidatedStreamModel;` — AddObjects calls are redirected to this model. That allows objects added via the add button to show up in the UI regardless of what the real streams contain. RemoveObjects are applied to both StreamForAdding and to the editable streams in MultiStreamModel.
- L70 _private member_ `TSharedRef<IEditableMultiReplicationStreamModel> MultiStreamModel;` — Contains all the streams that are being displayed
- L73 _private member_ `FOnObjectsChanged OnObjectsChangedDelegate;` — Called the equivalent event of ConsolidatedStreamModel or any of the streams in MultiStreamModel is broadcast.
- L75 _private member_ `FOnPropertiesChanged OnPropertiesChangedDelegate;` — Never actually called, just to implement OnPropertiesChanged.
- L77 _private member_ `FGetAutoAssignTarget GetAutoAssignTargetDelegate;` — If set, also adds newly added objects to the target stream.
- L80 _private member_ `TArray<TWeakPtr<IEditableReplicationStreamModel>> SubscribedToViewers;` — All streams we've subscribed to for changes. Used so we can unsubscribe when MultiStreamModel->OnStreamsChanged triggers.
- L83 _private prototype_ `void OnObjectsChanged_StreamForAdding(TConstArrayView<UObject*> AddedObjects, TConstArrayView<FSoftObjectPath> RemovedObjects, EReplicatedObjectChangeReason ChangeReason);` — Trigger our delegates when any of the substreams change.
- L84 _private prototype_ `void OnObjectsChanged_ClientStream(TConstArrayView<UObject*> AddedObjects, TConstArrayView<FSoftObjectPath> RemovedObjects, EReplicatedObjectChangeReason ChangeReason);`
- L87 _private prototype_ `void OnStreamExternallyChanged(TSharedRef<IReplicationStreamModel> Stream);` — Trigger subscription rebuild when streams are added / removed.
- L88 _private prototype_ `void RebuildStreamSubscriptions();`
- L89 _private prototype_ `void ClearStreamSubscriptions();`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Private/Replication/Editor/View/MultiEditor/SMultiReplicationStreamEditor.h` (Private)


#### class `UE::ConcertSharedSlate::SMultiReplicationStreamEditor`  
`class SMultiReplicationStreamEditor : public IMultiReplicationStreamEditor`  
_L31-56_
- inherits: `IMultiReplicationStreamEditor`
- desc: Displays multiple streams in a single widget. SMultiReplicationStreamEditor's responsibility is to consolidate all replicated objects in a single UI and display all properties in the class. The creator of SMultiReplicationStreamEditor is supposed to inject custom columns into the property section for assigning specific properties to the streams in the IEditableReplicationStreamModel.
- L33 _private typedef_ `using Super = IMultiReplicationStreamEditor;`
- L36 _public function_ `SLATE_BEGIN_ARGS(SMultiReplicationStreamEditor)`
- L38 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, FCreateMultiStreamEditorParams EditorParams, FCreateViewerParams ViewerParams);`
- L42 _public function_ `virtual IReplicationStreamEditor& GetEditorBase() const override`
- L43 _public function_ `virtual IEditableMultiReplicationStreamModel& GetMultiStreamModel() const override`
- L44 _public function_ `virtual IEditableReplicationStreamModel& GetConsolidatedModel() const override`
- L49 _private member_ `TSharedPtr<FConsolidatedMultiStreamModel> ConsolidatedModel;` — This model combines all of the user provided ones so they are all displayed in one view.
- L52 _private member_ `TSharedPtr<IEditableMultiReplicationStreamModel> MultiStreamModel;` — Tells us which streams there are.
- L55 _private member_ `TSharedPtr<IReplicationStreamEditor> EditorView;` — The main view, which is displaying ConsolidatedModel.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Private/Replication/Editor/View/ObjectEditor/SBaseReplicationStreamEditor.h` (Private)


#### class `UE::ConcertSharedSlate::SBaseReplicationStreamEditor`  
`class SBaseReplicationStreamEditor : public IReplicationStreamEditor`  
_L50-168_
- inherits: `IReplicationStreamEditor`
- desc: Extends SObjectToPropertyView with common functionality for editing (with an IEditableReplicationStreamModel): - Pressing delete calls IEditableReplicationStreamModel::RemoveObjects - A combo box to left of the object search bar for adding new top level objects - Default context menu items for top-level objects, such as deleting or adding more based right-clicked object - Wraps the IEditableReplicationStreamModel with FFakeObjectToPropertiesEditorModel so the SObjectToPropertyView: - displays only top-level objects in the outliner (i.e. excludes components) - displays all properties in the property view instead of just those registered in the model This is a base widget and is not fully functional, yet. You must inject additional UI to support adding objects. @see SDefaultReplicationStreamEditor for an example: it adds a Replicates? checkbox to the property rows. This widget assumes that the IReplicationSubobjectView::GetSelectedObjects reports subobjects that are not in the model yet. Such objects are added to the model.
- L54 _public function_ `SLATE_BEGIN_ARGS(SBaseReplicationStreamEditor)`
- L57 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<IPropertyAssignmentView>, PropertyAssignmentView) SLATE_ARGUMENT(TArray<FObjectColumnEntry>, ObjectColumns) SLATE_ARGUMENT(FColumnSortInfo, PrimaryObjectSort) SLATE_ARGUMENT(FColumnSortInfo, SecondaryObjectSort) SLATE_ARGUMENT(TSharedPtr<IObjectHierarchyModel>, ObjectHierarchy) SLATE_ARGUMENT(TSharedPtr<IObjectNameModel>, NameModel) SLATE_EVENT(FExtendObjectMenu, OnExtendObjectsContextMenu) SLATE_EVENT(FSelectObjectsFromComboButton, OnPreAddSelectedObjectsDelegate) SLATE_EVENT(FSelectObjectsFromComboButton, OnPostAddSelectedObjectsDelegate) SLATE_EVENT(FShouldDisplayObject, ShouldDisplayObject) SLATE_EVENT(FMakeObjectRowOverlayWidget, MakeObjectRowOverlayWidget) SLATE_ARGUMENT(EHorizontalAlignment, ObjectOverlayAlignment) SLATE_NAMED_SLOT(FArguments, LeftOfObjectSearchBar) SLATE_NAMED_SLOT(FArguments, RightOfObjectSearchBar) SLATE_ATTRIBUTE(bool, IsEditingEnabled) SLATE_ATTRIBUTE(FText, EditingDisabledToolTipText)` — In the lower half of the editor, this view presents the properties associated with the object that is currently selected in the upper part of the view.
- L109 _public prototype_ `virtual void Refresh() override;`
- L110 _public prototype_ `virtual void RequestObjectColumnResort(const FName& ColumnId) override;`
- L111 _public prototype_ `virtual void RequestPropertyColumnResort(const FName& ColumnId) override;`
- L112 _public prototype_ `virtual void SetSelectedObjects(TConstArrayView<TSoftObjectPtr<>> Objects) override;`
- L113 _public prototype_ `virtual TArray<TSoftObjectPtr<>> GetSelectedObjects() const override;`
- L119 _private member_ `TSharedPtr<SReplicationStreamViewer> ReplicationViewer;` — Displays the objects and properties
- L122 _private member_ `TSharedPtr<IEditableReplicationStreamModel> EditablePropertiesModel;` — For reading and writting to the edited asset
- L124 _private member_ `TSharedPtr<IObjectHierarchyModel> ObjectHierarchy;` — Can be null. If set, adds all subobjects to the top level view.
- L127 _private member_ `TSharedPtr<IObjectSelectionSourceModel> ObjectSelectionSource;` — For deciding which objects can be added to EditablePropertiesModel.
- L129 _private member_ `TSharedPtr<IPropertySourceProcessor> PropertySelectionSource;` — For deciding which properties can be added to EditablePropertiesModel.
- L132 _private member_ `TAttribute<bool> IsEditingEnabledAttribute;` — Optional. Determines whether all UI for changing the model should be disabled.
- L134 _private member_ `TAttribute<FText> EditingDisabledToolTipTextAttribute;` — Optional. Whenever IsEditingEnabled returns true, this tooltip is displayed for relevant, disabled UI.
- L137 _private member_ `FExtendObjectMenu OnExtendObjectsContextMenuDelegate;` — Generates additional entries
- L139 _private member_ `FSelectObjectsFromComboButton OnPreAddSelectedObjectsDelegate;` — Called just before the passed objects are added to the stream model. Called in response to the user selecting these objects from the combo button.
- L141 _private member_ `FSelectObjectsFromComboButton OnPostAddSelectedObjectsDelegate;` — Called just after the passed objects have been added to the stream model. Called in response to the user selecting these objects from the combo button.
- L148 _private member_ `bool bIsAddingFromSelection = false;` — Set when the combo button is adding an object. This is so AutoAddObjectsAndPropertiesFromSettings only adds when an object is added via the combo button. Note that AutoAddObjectsAndPropertiesFromSettings must be called in OnObjectsChanged so it becomes part of the transaction.
- L150 _private prototype_ `bool IsEditingDisabled() const;`
- L151 _private prototype_ `FText GetEditingDisabledText() const;`
- L153 _private prototype_ `void OnObjectsChanged(TConstArrayView<UObject*> AddedObjects, TConstArrayView<FSoftObjectPath> RemovedObjects, EReplicatedObjectChangeReason ChangeReason);`
- L154 _private prototype_ `void OnPropertiesChanged();`
- L157 _private prototype_ `TSharedRef<SWidget> BuildRootAddObjectWidgets();` — Customizing left objects search bar
- L158 _private prototype_ `void OnObjectsSelectedForAdding(TArray<FSelectableObjectInfo> ObjectsToAdd);`
- L161 _private function_ `void OnDeleteObjects_PassByValue(TArray<TSharedPtr<FReplicatedObjectData>> CopiedObjectsToDelete) const` — Respond to object editing events
- L162 _private prototype_ `void OnDeleteObjects(const TArray<TSharedPtr<FReplicatedObjectData>>& ObjectsToDelete) const;`
- L163 _private prototype_ `TSharedPtr<SWidget> OnObjectsContextMenuOpening();`
- L164 _private prototype_ `void AddObjectSourceContextMenuOptions(FMenuBuilder& MenuBuilder);`
- L167 _private prototype_ `FSourceModelBuilders<FSelectableObjectInfo>::FItemPickerArgs MakeObjectSourceBuilderArgs();` — Utils for building item source widgets

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Private/Replication/Editor/View/ObjectViewer/SReplicatedPropertyView.h` (Private)


#### class `UE::ConcertSharedSlate::SReplicatedPropertyView`  
`class SReplicatedPropertyView : public SCompoundWidget`  
_L21-72_
- inherits: `SCompoundWidget`
- desc: Determines which properties are to be displayed based on an IReplicationStreamModel. Uses a property tree for displaying. If no properties are displayed, this widget displays a message instead, e.g. to select an object.
- L25 _public function_ `SLATE_BEGIN_ARGS(SReplicatedPropertyView)`
- L28 _public prototype_ `SLATE_EVENT(FGetObjectClass, GetObjectClass) SLATE_ARGUMENT(TSharedPtr<IObjectNameModel>, NameModel) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<IPropertyAssignmentView> InPropertyAssignmentView, TSharedRef<IReplicationStreamModel> InPropertiesModel);` — Gets the class for the object since the object may not be in the model.
- L37 _public prototype_ `void RefreshPropertyData(const TArray<TSoftObjectPtr<>>& SelectedObjects);` — Updates the displayed properties
- L39 _public function_ `void RequestResortForColumn(const FName& ColumnId) const` — Requests that the given column be resorted, if it currently affects the row sorting.
- L44 _private member_ `TSharedPtr<IPropertyAssignmentView> PropertyAssignmentView;` — In the lower half of the editor, this view presents the properties associated with the object that is currently selected in the upper part of the view.
- L47 _private member_ `TSharedPtr<IReplicationStreamModel> PropertiesModel;` — The model this view is visualizing.
- L59 _private member_ `TSharedPtr<SWidgetSwitcher> PropertyContent;` — Determines the content displayed for PropertyArea.
- L62 _private member_ `FGetObjectClass GetObjectClassDelegate;` — Gets the class for the object since the object may not be in the model.
- L64 _private prototype_ `TSharedRef<SWidget> CreatePropertiesView(const FArguments& InArgs);`
- L67 _private prototype_ `TOptional<FSoftClassPath> GetClassForPropertiesFromSelection(const TArray<TSoftObjectPtr<>>& Objects) const;` — Given the selected objects, determines whether they all have the same class and returns it if so.
- L69 _private prototype_ `void SetPropertyContent(EReplicatedPropertyContent Content) const;` — Sets how to display this widget
- L71 _private function_ `FSoftClassPath GetObjectClass(const TSoftObjectPtr<>& Object) const`

#### enum `UE::ConcertSharedSlate::SReplicatedPropertyView::EReplicatedPropertyContent`  
`enum class EReplicatedPropertyContent`  
_L49-57_
- L52 _public enumerator_ `Properties` — Shows the properties
- L54 _public enumerator_ `NoSelection` — Prompts: "Select an object to see selected properties"
- L56 _public enumerator_ `SelectionTooBig` — Prompts: "Select objects of the same type type to see selected properties"

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Private/Replication/Editor/View/ObjectViewer/SReplicationStreamViewer.h` (Private)


#### class `UE::ConcertSharedSlate::SReplicationStreamViewer`  
`class SReplicationStreamViewer : public IReplicationStreamViewer`  
_L48-195_
- inherits: `IReplicationStreamViewer`
- desc: Root widget for viewing UMultiUserPropertyReplicationSelection. This widget knows how to display IReplicationStreamModel. The underlying data is modified by SObjectToPropertyEditor, which uses this widget's extension points to call functions on IEditableReplicationStreamModel. Important: this view should be possible to be built in programs, so it should not reference things like AActor, UActorComponent, ResolveObject, etc. directly.
- L52 _public function_ `SLATE_BEGIN_ARGS(SReplicationStreamViewer)`
- L55 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<IPropertyAssignmentView>, PropertyAssignmentView) SLATE_ARGUMENT(TArray<FObjectColumnEntry>, ObjectColumns) SLATE_ARGUMENT(FColumnSortInfo, PrimaryObjectSort) SLATE_ARGUMENT(FColumnSortInfo, SecondaryObjectSort) SLATE_ARGUMENT(TSharedPtr<IObjectHierarchyModel>, ObjectHierarchy) SLATE_ARGUMENT(TSharedPtr<IObjectNameModel>, NameModel) SLATE_EVENT(SReplicationTreeView<FReplicatedObjectData>::FDeleteItems, OnDeleteObjects) SLATE_EVENT(FOnContextMenuOpening, OnObjectsContextMenuOpening) SLATE_EVENT(FShouldDisplayObject, ShouldDisplayObject) /** Optional. Gets the content to overlay on hovered rows;` — In the lower half of the editor, this view presents the properties associated with the object that is currently selected in the upper part of the view.
- L98 _public prototype_ `virtual void Refresh() override;`
- L99 _public prototype_ `virtual void RequestObjectColumnResort(const FName& ColumnId) override;`
- L100 _public prototype_ `virtual void RequestPropertyColumnResort(const FName& ColumnId) override;`
- L101 _public prototype_ `virtual void SetSelectedObjects(TConstArrayView<TSoftObjectPtr<>> Objects) override;`
- L102 _public prototype_ `virtual TArray<TSoftObjectPtr<>> GetSelectedObjects() const override;`
- L105 _public function_ `void RequestObjectDataRefresh()`
- L106 _public function_ `void RequestPropertyDataRefresh()`
- L109 _public prototype_ `void SelectObjects(TConstArrayView<TSoftObjectPtr<>> Objects, bool bAtEndOfTick = false);` — Selects the given objects.
- L111 _public prototype_ `void ExpandObjects(TConstArrayView<TSoftObjectPtr<>> Objects, bool bRecursive, bool bAtEndOfTick = false);` — Expands the given objects, recursively if desired.
- L114 _public prototype_ `bool IsDisplayedInTopView(const FSoftObjectPath& Object) const;` — @return Whether Object is being displayed in the top object panel.
- L117 _public prototype_ `TArray<TSharedPtr<FReplicatedObjectData>> GetSelectedObjectItems() const;` — @return Gets the root objects selected in the outliner; the subobject view chooses which of these objects (or their subobjects) end up in GetSelectedObjectShowingProperties.
- L120 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L126 _private member_ `TSharedPtr<IReplicationStreamModel> PropertiesModel;` — The model this view is visualizing.
- L128 _private member_ `TSharedPtr<IObjectHierarchyModel> ObjectHierarchy;` — Can be null. If set, this determines the children nested under the root objects. Editor builds have access to e.g. to USubobjectDataSubsystem but programs do not.
- L130 _private member_ `TSharedPtr<IObjectNameModel> NameModel;` — Can be null. If set, this determines the display text for objects. Editor builds have access to e.g. to USubobjectDataSubsystem but programs do not.
- L133 _private member_ `TSharedPtr<SExpandableArea> PropertyArea;` — Lists the properties of the selected actor
- L135 _private member_ `TSharedPtr<SReplicatedPropertyView> PropertySection;` — Edits the property list and (optionally) exposes subobjects of the selected root object.
- L138 _private member_ `TSharedPtr<SReplicationTreeView<FReplicatedObjectData>> ReplicatedObjects;` — Tree view for replicated objects.
- L141 _private member_ `TArray<TSharedPtr<FReplicatedObjectData>> AllObjectRowData;` — All object row data
- L143 _private member_ `TArray<TSharedPtr<FReplicatedObjectData>> RootObjectRowData;` — The instances of ObjectRowData which do not have any parents. This acts as the item source for the tree view.
- L145 _private member_ `TMap<FSoftObjectPath, TSharedPtr<FReplicatedObjectData>> PathToObjectDataCache;` — Inverse map of ObjectRowData using FReplicatedObjectData::GetObjectPath as key. Contains all elements of ObjectRowData.
- L147 _private member_ `bool bIsPropertyAreaExpanded = false;`
- L149 _private member_ `FStreamViewerObjectViewOptions ObjectViewOptions;` — View options for the object outliner.
- L151 _private member_ `bool bHasRequestedObjectRefresh = false;`
- L152 _private member_ `bool bHasRequestedPropertyRefresh = false;`
- L153 _private member_ `TArray<TSoftObjectPtr<>> PendingToSelect;`
- L154 _private member_ `TArray<TSoftObjectPtr<>> PendingToExpand;`
- L155 _private member_ `bool bPendingExpandRecursively = false;`
- L158 _private member_ `FShouldDisplayObject ShouldDisplayObjectDelegate;` — Optional. Whether a given object should be displayed. If this returns false on an object, none of its children will be shown either.
- L161 _private prototype_ `TSharedRef<SWidget> CreateContentWidget(const FArguments& InArgs);` — Widget creation helpers
- L162 _private prototype_ `TSharedRef<SWidget> CreateOutlinerSection(const FArguments& InArgs);`
- L163 _private prototype_ `TSharedRef<SWidget> CreatePropertiesSection(const FArguments& InArgs);`
- L166 _private prototype_ `void RefreshObjectData();` — Regenerates object row data in the top view
- L168 _private prototype_ `void IterateDisplayableObjects(TFunctionRef<void(const FSoftObjectPath& Object)> Delegate) const;` — Lists all objects that need an object in the top-view.
- L171 _private prototype_ `void BuildRootObjectRowData();` — Sets RootObjectRowData to all non-root nodes from ObjectRowData.
- L174 _private prototype_ `void BuildObjectHierarchyIfNeeded(TSharedPtr<FReplicatedObjectData> ReplicatedObjectData, TMap<FSoftObjectPath, TSharedPtr<FReplicatedObjectData>>& NewPathToObjectDataCache);` — Creates an item for every object in the hierarchy of ReplicatedObjectData
- L175 _private prototype_ `void GetObjectRowChildren(TSharedPtr<FReplicatedObjectData> ReplicatedObjectData, TFunctionRef<void(TSharedPtr<FReplicatedObjectData>)> ProcessChild);`
- L178 _private function_ `SSplitter::ESizeRule GetPropertyAreaSizeRule() const` — Handles how much space the 'Clients' area uses with respect to its expansion state.
- L179 _private function_ `void OnPropertyAreaExpansionChanged(bool bExpanded)`
- L182 _private function_ `void OnSubobjectViewOptionToggled()` — Called in response to subobject display view option being changed. Rebuilds the entire hierarchy.
- L189 _private prototype_ `bool CanDisplayObject(const TSoftObjectPtr<>& Object) const;` — Invokes the ShouldDisplayObjectDelegate to determine whether ObjectPath should be displayed.
- L190 _private function_ `bool CanDisplayObject(const FSoftObjectPath& ObjectPath) const`
- L192 _private prototype_ `bool ShouldDisplayObjectRelation(EChildRelationship Relationship) const;` — Whether the view options allow this type of relationship to be shown.
- L194 _private prototype_ `FSoftClassPath GetObjectClass(const TSoftObjectPtr<>& Object) const;`

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Private/Replication/Editor/View/ObjectViewer/StreamViewerObjectViewOptions.h` (Private)


#### class `UE::ConcertSharedSlate::FStreamViewerObjectViewOptions`  
`class FStreamViewerObjectViewOptions`  
_L13-36_
- desc: View options for the outliner displayed by SReplicationStreamViewer.
- L18 _public prototype_ `TSharedRef<SWidget> MakeViewOptionsComboButton();` — Makes a standard View Options widget, displaying the eye ball icon and showing the possible options.
- L20 _public prototype_ `TSharedRef<SWidget> MakeMenuWidget();` — Returns a Menu widgets containing the available options.
- L23 _public function_ `bool ShouldDisplaySubobjects() const` — Whether to display subobjects (with the exception of components, which are continued to be displayed).
- L25 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnDisplaySubobjectsToggled);`
- L27 _public function_ `FOnDisplaySubobjectsToggled& OnDisplaySubobjectsToggled()` — Called when the option for displaying subobjects has been changed.
- L32 _private member_ `FOnDisplaySubobjectsToggled OnDisplaySubobjectsToggledDelegate;` — Called when the option for displaying subobjects has been changed.
- L35 _private member_ `bool bDisplaySubobjects = false;` — Whether to display subobjects (with the exception of components, which are continued to be displayed).

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L25 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnDisplaySubobjectsToggled);`

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Private/Replication/Editor/View/Property/SCategoryColumnRow.h` (Private)


#### class `UE::ConcertSharedSlate::SCategoryColumnRow`  
`class SCategoryColumnRow : public STableRow<TSharedPtr<FPropertyNodeData>>`  
_L27-47_
- inherits: `STableRow<TSharedPtr<FPropertyNodeData>>`
- desc: A row that generates its columns generically via IReplicationTreeColumn.
- L29 _private typedef_ `using Super = STableRow;`
- L32 _public function_ `SLATE_BEGIN_ARGS(SCategoryColumnRow)`
- L34 _public prototype_ `SLATE_NAMED_SLOT(FArguments, Content) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<STableViewBase> InOwner);`
- L39 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L40 _public prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L44 _private member_ `TSharedPtr<SWidget> Content;`
- L46 _private prototype_ `const FSlateBrush* GetBackgroundImage() const;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Private/Replication/Editor/View/Property/SMultiObjectAssignment.h` (Private)


#### class `UE::ConcertSharedSlate::SMultiObjectAssignment`  
`class SMultiObjectAssignment : public SCompoundWidget , public IMultiObjectPropertyAssignmentView`  
_L22-79_
- inherits: `SCompoundWidget,IMultiObjectPropertyAssignmentView`
- desc: SMultiObjectAssignment shows the properties of the displayed object and all of its subobjects.
- L28 _public function_ `SLATE_BEGIN_ARGS(SMultiObjectAssignment)`
- L30 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<IPropertySourceProcessor>, PropertySource) SLATE_ARGUMENT(TSharedPtr<IObjectHierarchyModel>, ObjectHierarchy) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<IPropertyTreeView> InTreeView);` — Optional. If specified, displays the properties of this model instead of those assigned in the stream.
- L39 _public prototype_ `virtual void RefreshData(const TArray<TSoftObjectPtr<>>& Objects, const IReplicationStreamModel& Model) override;`
- L40 _public function_ `virtual void RequestRefilter() const override`
- L41 _public function_ `virtual void RequestResortForColumn(const FName& ColumnId) override`
- L42 _public function_ `virtual TSharedRef<SWidget> GetWidget() override`
- L43 _public function_ `virtual TArray<FObjectGroup> GetDisplayedGroups() const override`
- L44 _public function_ `virtual FOnSelectionChanged& OnObjectGroupsChanged() override`
- L48 _public prototype_ `virtual void SetShouldShowSubobjects(bool bShowSubobjects) override;`
- L49 _public function_ `virtual bool GetShouldShowSubobjects() const override`
- L55 _private member_ `TSharedPtr<IPropertyTreeView> TreeView;` — The tree view that is being wrapped.
- L57 _private member_ `TArray<TSoftObjectPtr<>> PreviousSelectedObjects;` — Used to determine whether to rebuild the entire property data.
- L59 _private member_ `TArray<FObjectGroup> DisplayedGroups;` — Cached value for GetDisplayedGroups.
- L62 _private member_ `TSharedPtr<IObjectHierarchyModel> ObjectHierarchy;` — Used to get subobjects of selected objects.
- L64 _private member_ `TSharedPtr<IPropertySourceProcessor> OptionalPropertySource;` — Optional. If specified, displays the properties of this model instead of those assigned in the stream.
- L67 _private member_ `bool bShouldShowSubobjects = false;` — Whether EChildRelationshipFlags::Subobject objects should be shown.
- L70 _private member_ `FOnSelectionChanged OnObjectGroupsChangedDelegate;` — Broadcasts when the result of GetDisplayedGroups() has changed.
- L78 _private prototype_ `FBuildAssignmentEntryResult BuildAssignmentEntry(const TArray<TSoftObjectPtr<>>& Objects, const IReplicationStreamModel& Model);` — Builds a property section grouped by Objects (usually has 1 object - contains similar objects, like StaticMeshComponent0, for multi-edit purposes).

#### struct `UE::ConcertSharedSlate::SMultiObjectAssignment::FBuildAssignmentEntryResult`  
`struct FBuildAssignmentEntryResult`  
_L72-76_
- L74 _public member_ `FPropertyAssignmentEntry Entry;`
- L75 _public member_ `bool bHaveSharedClass = false;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Private/Replication/Editor/View/Property/SPerObjectPropertyAssignment.h` (Private)


#### class `UE::ConcertSharedSlate::SPerObjectPropertyAssignment`  
`class SPerObjectPropertyAssignment : public SCompoundWidget , public IPropertyAssignmentView`  
_L17-53_
- inherits: `SCompoundWidget,IPropertyAssignmentView`
- desc: SPerObjectPropertyAssignment shows only the properties of the displayed object, which is achieved by wrapping SPropertyTreeView.
- L23 _public function_ `SLATE_BEGIN_ARGS(SPerObjectPropertyAssignment)`
- L25 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<IPropertySourceProcessor>, PropertySource) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<IPropertyTreeView> InTreeView);` — Optional. If specified, displays the properties of this model instead of those assigned in the stream.
- L31 _public prototype_ `virtual void RefreshData(const TArray<TSoftObjectPtr<>>& Objects, const IReplicationStreamModel& Model) override;`
- L32 _public function_ `virtual void RequestRefilter() const override`
- L33 _public function_ `virtual void RequestResortForColumn(const FName& ColumnId) override`
- L34 _public function_ `virtual TSharedRef<SWidget> GetWidget() override`
- L35 _public function_ `virtual TArray<FObjectGroup> GetDisplayedGroups() const override`
- L36 _public function_ `virtual FOnSelectionChanged& OnObjectGroupsChanged() override`
- L42 _private member_ `TSharedPtr<IPropertyTreeView> TreeView;` — The tree view that is being wrapped.
- L44 _private member_ `TArray<TSoftObjectPtr<>> PreviousSelectedObjects;` — Used to determine whether to rebuild the entire property data.
- L46 _private member_ `TArray<FObjectGroup> DisplayedGroups;` — Cached value for GetDisplayedGroups.
- L49 _private member_ `TSharedPtr<IPropertySourceProcessor> OptionalPropertySource;` — Optional. If specified, displays the properties of this model instead of those assigned in the stream.
- L52 _private member_ `FOnSelectionChanged OnObjectGroupsChangedDelegate;` — Broadcasts when the result of GetDisplayedGroups() has changed.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Private/Replication/Editor/View/Property/SPropertyTreeView.h` (Private)


#### class `UE::ConcertSharedSlate::SPropertyTreeView`  
`class SPropertyTreeView : public SCompoundWidget , public IPropertyTreeView`  
_L29-159_
- inherits: `SCompoundWidget,IPropertyTreeView`
- desc: This widget knows how to display a list of properties in a tree view. It generates the items and exposes extension points for more advanced UI, such as filtering.
- L35 _public function_ `SLATE_BEGIN_ARGS(SPropertyTreeView)`
- L40 _public prototype_ `SLATE_EVENT(SReplicationTreeView<FPropertyData>::FCustomFilter, FilterItem) SLATE_EVENT(FCreateCategoryRow, CreateCategoryRow) SLATE_ARGUMENT(TArray<FPropertyColumnEntry>, Columns) SLATE_ARGUMENT(FName, ExpandableColumnLabel) SLATE_ARGUMENT(FColumnSortInfo, PrimarySort) SLATE_ARGUMENT(FColumnSortInfo, SecondarySort) SLATE_ARGUMENT(ESelectionMode::Type, SelectionMode) SLATE_NAMED_SLOT(FArguments, LeftOfSearchBar) SLATE_NAMED_SLOT(FArguments, RightOfSearchBar) SLATE_NAMED_SLOT(FArguments, RowBelowSearchBar) SLATE_NAMED_SLOT(FArguments, NoItemsContent) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — Optional callback to do more filtering of items on top of the search bar.
- L73 _public prototype_ `virtual void RefreshPropertyData(const TArray<FPropertyAssignmentEntry>& Entries, bool bCanReuseExistingRowItems) override;`
- L74 _public function_ `virtual void RequestRefilter() const override`
- L75 _public function_ `virtual void RequestResortForColumn(const FName& ColumnId) override`
- L76 _public prototype_ `virtual void RequestScrollIntoView(const FConcertPropertyChain& PropertyChain) override;`
- L77 _public function_ `virtual TSharedRef<SWidget> GetWidget() override`
- L83 _private member_ `TSharedPtr<SReplicationTreeView<FPropertyNodeData>> TreeView;` — The tree view displaying the replicated properties
- L86 _private member_ `TArray<TSharedPtr<FPropertyNodeData>> PropertyRowData;` — Contains all data.
- L88 _private member_ `TArray<TSharedPtr<FPropertyNodeData>> RootPropertyNodes;` — The instances which do not have any parents. This acts as the item source for the tree view.
- L112 _private member_ `TMap<TSoftObjectPtr<>, FCategoryMetaData> CategoryNodes;` — Inverse map of object to its owning category. Contains all elements of PropertyRowData which are category nodes. The main purpose is to allow reuse of items when refreshing hierarchy (to retain selection state, etc.) Important: when multi-editing, this only maps the context object at index 0. Use FindCategoryMetaData to retrieve. Empty if ShouldBuildCategories() == false.
- L119 _private member_ `TMap<FConcertPropertyChain, TArray<TSharedPtr<FPropertyNodeData>>> ChainToPropertyDataCache;` — Inverse map of PropertyRowData using FPropertyData::GetProperty as key. Contains all elements of PropertyRowData which are property nodes The main purpose is to allow reuse of items when refreshing hierarchy (to retain selection state, etc.)
- L122 _private member_ `TArray<TArray<TSoftObjectPtr<>>> SourceEntriesForSorting;` — Equal to FPropertyAssignmentEntry::ContextObjects from the last RefreshPropertyData call. This is used during sorting to determine the relative ordering of categories.
- L125 _private member_ `SReplicationTreeView<FPropertyData>::FCustomFilter FilterDelegate;` — Optional callback for filtering items.
- L127 _private member_ `FCreateCategoryRow CreateCategoryRowDelegate;` — Optional callback for creating category rows. If unset, no category rows are generated.
- L130 _private function_ `bool ShouldBuildCategories() const` — @return Whether this UI was configured to show category nodes.
- L132 _private prototype_ `void RefreshCategoryNodes(const TArray<FPropertyAssignmentEntry>& Entries, TMap<TSoftObjectPtr<>, FCategoryMetaData>& NewCategoryNodes);`
- L133 _private prototype_ `void RefreshPropertyNodes(const TArray<FPropertyAssignmentEntry>& Entries, TMap<FConcertPropertyChain, TArray<TSharedPtr<FPropertyNodeData>>>& NewChainToPropertyDataCache);`
- L136 _private prototype_ `TSharedPtr<FPropertyNodeData> FindPropertyNode(const FConcertPropertyChain& PropertyChain, TConstArrayView<TSoftObjectPtr<>> ContextObjects);` — Looks in ChainToPropertyDataCache for any a node that is referencing PropertyChain and any of ContextObjects.
- L138 _private function_ `FCategoryMetaData* FindCategoryMetaData(const FPropertyNodeData& Item)` — Find the meta data for this item.
- L139 _private function_ `const FCategoryMetaData* FindCategoryMetaData(const FPropertyNodeData& Item) const`
- L142 _private prototype_ `void BuildRootPropertyRowData();` — Inits RootPropertyRowData from PropertyRowData.
- L143 _private prototype_ `void GetPropertyRowChildren(TSharedPtr<FPropertyNodeData> ParentNodeData, TFunctionRef<void(TSharedPtr<FPropertyNodeData>)> ProcessChild) const;`
- L144 _private prototype_ `void EnumerateRootProperties(const FCategoryData& ParentCategoryData, TFunctionRef<void(TSharedPtr<FPropertyNodeData>)> ProcessChild) const;`
- L145 _private prototype_ `void EnumerateChildProperties(const FPropertyNodeData& ParentNode, TFunctionRef<void(TSharedPtr<FPropertyNodeData>)> ProcessChild) const;`
- L148 _private prototype_ `EItemFilterResult FilterItem(const FPropertyNodeData& PropertyNodeData) const;` — Filters the item according to FilterDelegate.
- L150 _private prototype_ `TSharedPtr<ITableRow> OverrideRowWidget( TSharedPtr<FPropertyNodeData> NodeData, const TSharedRef<STableViewBase>& TableViewBase, const TReplicationTreeData<FPropertyNodeData>::FGenerateRowArgs& Args );` — Generates a category row if NodeData is a category.
- L156 _private prototype_ `EComparisonOverride OverrideIsLessThan(const TSharedPtr<FPropertyNodeData>& Left, const TSharedPtr<FPropertyNodeData>& Right) const;` — Overrides the sort if one of the nodes is a category
- L158 _private prototype_ `ESearchTermResult OverrideGetSearchTerms(const TSharedPtr<FPropertyNodeData>& NodeData, TArray<FString>& InOutSearchStrings) const;` — Overrides the search terms for category nodes.

#### struct `UE::ConcertSharedSlate::SPropertyTreeView::FCategoryMetaData`  
`struct FCategoryMetaData`  
_L90-100_
- L92 _public member_ `TSharedRef<FPropertyNodeData> Node;`
- L94 _public member_ `TSharedRef<ICategoryRow> RowWidgetContent;` — The widget displayed in the category widget.
- L96 _public function_ `FCategoryMetaData(TSharedRef<FPropertyNodeData> Node, TSharedRef<ICategoryRow> RowWidgetContent) : Node(Node) , RowWidgetContent(RowWidgetContent)`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Private/Replication/Editor/View/Tree/SReplicationColumnRow.h` (Private)


#### class `UE::ConcertSharedSlate::SReplicationColumnRow`  
`template<typename TListItemType> class SReplicationColumnRow : public SMultiColumnTableRow<TSharedPtr<TListItemType>>`  
_L24-177_
- inherits: `SMultiColumnTableRow<TSharedPtr<TListItemType>>`
- desc: A row that generates its columns generically via IReplicationTreeColumn.
- L26 _private typedef_ `using Super = SMultiColumnTableRow<TSharedPtr<TListItemType>>;`
- L29 _public typedef_ `using FGetColumn = typename TReplicationTreeData<TListItemType>::FGetColumn;`
- L30 _public typedef_ `using FOverrideColumnWidget = typename TReplicationTreeData<TListItemType>::FOverrideColumnWidget;`
- L31 _public typedef_ `using FGetHoveredRowContent = typename TReplicationTreeData<TListItemType>::FGetHoveredRowContent;`
- L33 _public function_ `SLATE_BEGIN_ARGS(SReplicationColumnRow) : _Style(&FCoreStyle::Get().GetWidgetStyle<FTableRowStyle>("TableView.Row"))`
- L37 _public function_ `SLATE_ARGUMENT(TSharedPtr<FText>, HighlightText) SLATE_EVENT(FGetColumn, ColumnGetter) SLATE_EVENT(FOverrideColumnWidget, OverrideColumnWidget) /** Optional. Gets the content to overlay on hovered rows;` — Used for highlighting the text being searched.
- L80 _public function_ `virtual void ConstructChildren(ETableViewMode::Type InOwnerTableMode, const TAttribute<FMargin>& InPadding, const TSharedRef<SWidget>& InContent) override`
- L117 _public function_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override` — Generates the widget representing this row.
- L171 _private member_ `FGetColumn ColumnGetterDelegate;`
- L172 _private member_ `FOverrideColumnWidget OverrideColumnWidgetDelegate;`
- L173 _private member_ `FGetHoveredRowContent GetHoveredRowContent;`
- L174 _private member_ `TSharedPtr<FText> HighlightText;`
- L175 _private member_ `TSharedPtr<TListItemType> RowData;`
- L176 _private member_ `FName ExpandableColumnLabel;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L72 _typedef_ `using FTableRowArgs = typename STableRow<TSharedPtr<TListItemType>>::FArguments;` (scope `UE::ConcertSharedSlate::SReplicationColumnRow::SLATE_ARGUMENT`)
- L106 _function_ `.Visibility_Lambda([this](){ return this->IsHovered() ? EVisibility::Visible : EVisibility::Hidden; }) [ HoverContent ] ] ] ];` (scope `UE::ConcertSharedSlate::SReplicationColumnRow::ConstructChildren`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Private/Replication/Editor/View/Tree/SReplicationTreeView.h` (Private)


#### enum `UE::ConcertSharedSlate::EItemFilterResult`  
`enum class EItemFilterResult : uint8`  
_L26-34_
- L29 _public enumerator_ `Include` — The item passes the filter and should be displayed
- L31 _public enumerator_ `Exclude` — The item does not pass the filter and not should be displayed
- L33 _public enumerator_ `IncludeOnlyIfChildIsIncluded` — The item is only displayed if the filter passes on one of its children. If no child is included, the item is not displayed.

#### enum `UE::ConcertSharedSlate::EComparisonOverride`  
`enum class EComparisonOverride : uint8`  
_L37-45_
- desc: Result for the IsLessThan override delegate in SReplicationTreeView.
- L40 _public enumerator_ `Less` — Left < Right is to be treated as true
- L42 _public enumerator_ `NotLess` — Left < Right is to be treated as false
- L44 _public enumerator_ `UseDefault` — Use the standard column comparision delegates to find out.

#### enum `UE::ConcertSharedSlate::ESearchTermResult`  
`enum class ESearchTermResult : uint8`  
_L48-54_
- desc: Result for the GetSearchString override delegate in SReplicationTreeView.
- L51 _public enumerator_ `UseDefault` — The delegate wants the passed in item to go through normal text search as well.
- L53 _public enumerator_ `UseOverrideOnly` — The delegate does not want the passed in item to go through the rest of the text search process.

#### class `UE::ConcertSharedSlate::SReplicationTreeView`  
`template<typename TItemType> class SReplicationTreeView : public SCompoundWidget`  
_L64-438_
- inherits: `SCompoundWidget`
- desc: Shared code for the tree view for replicated actors and properties. It is a tree view that is searchable with a search box and exposes slots to add more filter widgets, such as SBasicFilterBar. The columns are modular and are abstracted by IReplicationTreeColumn. You can customize row content by specializing TReplicationTreeItemTraits; the default implementation creates a SReplicationColumnRow, which uses IReplicationTreeColumn to draw the columns.
- L68 _public typedef_ `using FOverrideColumnWidget = typename TReplicationTreeData<TItemType>::FOverrideColumnWidget;`
- L69 _public prototype_ `DECLARE_DELEGATE_OneParam(FDeleteItems, const TArray<TSharedPtr<TItemType>>& SelectedItems);`
- L70 _public prototype_ `DECLARE_DELEGATE(FOnSelectionChanged);`
- L73 _public typedef_ `using FOverrideRowWidget = typename TReplicationTreeData<TItemType>::FOverrideRowWidget;` — TODO UE-216456: The following callbacks could be extracted to a IReplicationItem<TItemType> to simplify SReplicationTreeView implementation
- L74 _public typedef_ `using FGetHoveredRowContent = typename TReplicationTreeData<TItemType>::FGetHoveredRowContent;`
- L75 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(EItemFilterResult, FCustomFilter, const TItemType& Item);`
- L76 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(EComparisonOverride, FIsLessThanOverride, const TSharedPtr<TItemType>& Left, const TSharedPtr<TItemType>& Right);`
- L77 _public prototype_ `DECLARE_DELEGATE_TwoParams(FGetItemChildren, TSharedPtr<TItemType> Item, TFunctionRef<void(TSharedPtr<TItemType>)> ProcessChild);`
- L78 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(ESearchTermResult, FGetSearchTermsOverride, const TSharedPtr<TItemType>& Item, TArray<FString>& InOutSearchTerms);`
- L86 _public function_ `SLATE_BEGIN_ARGS(SReplicationTreeView<TItemType>) : _HeaderRowVisibility(EVisibility::Visible) , _SelectionMode(ESelectionMode::Single) , _RowStyle(&FCoreStyle::Get().GetWidgetStyle<FTableRowStyle>("TableView.Row"))`
- L92 _public function_ `SLATE_ARGUMENT(TArray<TSharedPtr<TItemType>>*, RootItemsSource) SLATE_EVENT(FGetItemChildren, OnGetChildren) SLATE_EVENT(FDeleteItems, OnDeleteItems) SLATE_EVENT(FOnContextMenuOpening, OnContextMenuOpening) SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged) SLATE_EVENT(FCustomFilter, FilterItem) /** Optional. Gets the content to overlay on hovered rows;` — The items to display
- L249 _public function_ `void RequestRefilter()`
- L254 _public function_ `void RequestResort()`
- L260 _public function_ `void RequestResortForColumn(const FName& ColumnId)` — Requests that the given column be resorted, if it currently affects the row sorting.
- L268 _public function_ `void SetPrimarySortMode(FName SortedColumnId, EColumnSortMode::Type SortMode)`
- L282 _public function_ `void SetSecondarySortMode(FName SortedColumnId, EColumnSortMode::Type SortMode)`
- L302 _public function_ `void SetSelectedItems(const TArray<TSharedPtr<TItemType>>& ObjectsToSelect, bool bIsSelected)`
- L307 _public function_ `void SetExpandedItems(const TArray<TSharedPtr<TItemType>>& ObjectsToSelect, bool bIsExpanded)`
- L315 _public function_ `void RequestScrollIntoView(const TSharedPtr<TItemType>& Item)`
- L320 _public function_ `TArray<TSharedPtr<TItemType>> GetSelectedItems() const`
- L321 _public function_ `const TArray<TSharedPtr<TItemType>>& GetFilteredRootItems() const`
- L322 _public function_ `const FText& GetHighlightText() const`
- L324 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L325 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L330 _private member_ `TSharedPtr<SSearchBox> SearchBox;` — The widget being used for search.
- L332 _private member_ `TSharedPtr<FText> SearchText;` — Used to highlight text in text widgets
- L334 _private member_ `TSharedPtr<TTextFilter<const TSharedPtr<TItemType>&>> SearchTextFilter;` — Performs text search
- L337 _private member_ `TSharedPtr<SHeaderRow> HeaderRow;` — ListView's header row
- L339 _private member_ `TSharedPtr<STreeView<TSharedPtr<TItemType>>> TreeView;` — Displays the contents
- L341 _private member_ `FName ExpandableColumnId;` — The name of the column which will have the SExpandableArrow widget for the tree view.
- L344 _private member_ `TMap<FName, TReplicationColumnEntry<TItemType>> ColumnInfos;` — Binds column names to their infos.
- L350 _private member_ `TMap<FName, TSharedRef<IReplicationTreeColumn<TItemType>>> ColumnInstances;` — Columns currently being displayed. Currently columns are created statically on widget construction but in the future we could add dynamic column registration. Hence for now every entry in ColumnInfos will have a corresponding entry here.
- L353 _private member_ `TArray<TSharedPtr<TItemType>>* AllRootItems = nullptr;` — Item source passed to the STreeView.
- L355 _private member_ `TArray<TSharedPtr<TItemType>> FilteredRootItems;` — Contains only the root items that passed the filters.
- L357 _private member_ `TSet<TSharedPtr<TItemType>> AllFilteredItems;` — Includes ALL items in the hierarchy that have itself passed the filter or one of its children has passed the filter.
- L365 _private member_ `TMap<TSharedPtr<TItemType>, FItemMetaData> ItemMetaData;` — Additional data about items needed for misc operations, like expansion.
- L368 _private member_ `bool bForceParentItemsExpanded = false;` — Whether all items should be expanded. True while searching and false otherwise.
- L371 _private member_ `bool bFilterChanged = false;` — Whether to call ReapplyFilters next Tick().
- L373 _private member_ `bool bRequestedSort = false;` — Whether to call Resort next Tick().
- L375 _private member_ `FColumnSortInfo PrimarySortInfo;`
- L376 _private member_ `FColumnSortInfo SecondarySortInfo;`
- L379 _private member_ `FGetItemChildren OnGetChildrenDelegate;` — Callback for getting an item's children.
- L381 _private member_ `FDeleteItems OnDeleteItemsDelegate;` — Optional delegate for responding to pressing the delete button
- L383 _private member_ `FCustomFilter CustomFilterDelegate;` — Optional delegate for filtering the items even more.
- L385 _private member_ `FGetHoveredRowContent GetHoveredRowContentDelegate;` — Optional. The content to overlay on hovered rows; it covers the entire row.
- L387 _private member_ `FOverrideColumnWidget OverrideColumnWidgetDelegate;` — Optional delegate for overriding the column widgets.
- L389 _private member_ `FOverrideRowWidget OverrideRowWidgetDelegate;` — Optional. The widget returned by this delegate ends up overriding the default row widget.
- L391 _private member_ `FIsLessThanOverride OverrideIsLessThanDelegate;` — Optional. This delegate is used during sorting and can override the default sorting behaviour for some items.
- L393 _private member_ `FGetSearchTermsOverride OverrideGetSearchTerms;` — Optional. Can generate custom terms for an item type. This can be used e.g. for category nodes.
- L396 _private member_ `const FTableRowStyle* RowStyle = nullptr;` — Style to use for rows
- L399 _private prototype_ `TSharedRef<SWidget> CreateTreeView(const FArguments& InArgs);` — STreeView creation
- L400 _private prototype_ `TSharedRef<SHeaderRow> CreateHeaderRow(const FArguments& InArgs);`
- L401 _private prototype_ `TSharedRef<ITableRow> OnGenerateRowWidget(TSharedPtr<TItemType> Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L402 _private prototype_ `void GetRowChildren(TSharedPtr<TItemType> Item, TArray<TSharedPtr<TItemType>>& OutChildren);`
- L405 _private prototype_ `EColumnSortPriority::Type GetColumnSortPriority(const FName ColumnId) const;` — Sorting callbacks
- L406 _private prototype_ `EColumnSortMode::Type GetColumnSortMode(const FName ColumnId) const;`
- L407 _private prototype_ `void OnColumnSortModeChanged(const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type InSortMode);`
- L410 _private prototype_ `void OnSearchTextCommitted(const FText& InFilterText, ETextCommit::Type CommitType);` — Searching callbacks
- L411 _private prototype_ `void OnSearchTextChanged(const FText& InSearchText);`
- L419 _private prototype_ `void PopulateSearchStrings(const TSharedPtr<TItemType>& Item, TArray<FString>& OutSearchStrings);`
- L420 _private prototype_ `void ReapplyFilters();`
- L421 _private prototype_ `EFilterResult ApplyFiltersRecursive(const TSharedPtr<TItemType>& Item, TSet<TSharedPtr<TItemType>>& FilteredItemsToShow);`
- L422 _private prototype_ `EItemFilterResult PassesFilters(const TSharedPtr<TItemType>& Item);`
- L425 _private prototype_ `void CleanseItemMetaData();` — Called after RootItems has changed. Removes all invalidated ItemMetaData entries
- L427 _private prototype_ `void ReapplyExpansionStates();` — Applies the cached expansion states to all items
- L429 _private prototype_ `void OnItemExpansionChanged(TSharedPtr<TItemType> Item, bool bIsExpanded);` — Callback into tree view when expansion state is changed.
- L432 _private function_ `bool IsSearching() const` — @return Whether currently searching.
- L435 _private prototype_ `void Resort();` — Sorting
- L436 _private prototype_ `void Sort(TArray<TSharedPtr<TItemType>>& Items);`
- L437 _private prototype_ `TSharedPtr<IReplicationTreeColumn<TItemType>> FindColumnByName(const FName& ColumnId) const;`
- L441 _function_ `template <typename TItemType> FReply SReplicationTreeView<TItemType>::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)`
- L453 _function_ `template <typename TItemType> void SReplicationTreeView<TItemType>::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)`
- L471 _function_ `template <typename TItemType> TSharedRef<SWidget> SReplicationTreeView<TItemType>::CreateTreeView(const FArguments& InArgs)`
- L524 _function_ `template <typename TItemType> TSharedRef<SHeaderRow> SReplicationTreeView<TItemType>::CreateHeaderRow(const FArguments& InArgs)`
- L554 _function_ `template <typename TItemType> TSharedRef<ITableRow> SReplicationTreeView<TItemType>::OnGenerateRowWidget(TSharedPtr<TItemType> Item, const TSharedRef<STableViewBase>& OwnerTable)`
- L580 _function_ `template <typename TItemType> void SReplicationTreeView<TItemType>::GetRowChildren(TSharedPtr<TItemType> Item, TArray<TSharedPtr<TItemType>>& OutChildren)`
- L602 _function_ `template <typename TItemType> EColumnSortPriority::Type SReplicationTreeView<TItemType>::GetColumnSortPriority(const FName ColumnId) const`
- L617 _function_ `template <typename TItemType> EColumnSortMode::Type SReplicationTreeView<TItemType>::GetColumnSortMode(const FName ColumnId) const`
- L631 _function_ `template <typename TItemType> void SReplicationTreeView<TItemType>::OnColumnSortModeChanged( const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type InSortMode )`
- L658 _function_ `template <typename TItemType> void SReplicationTreeView<TItemType>::OnSearchTextCommitted(const FText& InFilterText, ETextCommit::Type CommitType)`
- L667 _function_ `template <typename TItemType> void SReplicationTreeView<TItemType>::OnSearchTextChanged(const FText& InSearchText)`
- L675 _function_ `template <typename TItemType> void SReplicationTreeView<TItemType>::PopulateSearchStrings(const TSharedPtr<TItemType>& Item, TArray<FString>& OutSearchStrings)`
- L690 _function_ `template <typename TItemType> void SReplicationTreeView<TItemType>::ReapplyFilters()`
- L728 _function_ `template <typename TItemType> typename SReplicationTreeView<TItemType>::EFilterResult SReplicationTreeView<TItemType>::ApplyFiltersRecursive(const TSharedPtr<TItemType>& Item, TSet<TSharedPtr<TItemType>>& FilteredItemsToShow)`
- L754 _function_ `template <typename TItemType> EItemFilterResult SReplicationTreeView<TItemType>::PassesFilters(const TSharedPtr<TItemType>& Item)`
- L766 _function_ `template <typename TItemType> void SReplicationTreeView<TItemType>::CleanseItemMetaData()`
- L784 _function_ `template <typename TItemType> void SReplicationTreeView<TItemType>::ReapplyExpansionStates()`
- L803 _function_ `template <typename TItemType> void SReplicationTreeView<TItemType>::OnItemExpansionChanged(TSharedPtr<TItemType> Item, bool bIsExpanded)`
- L828 _function_ `template <typename TItemType> void SReplicationTreeView<TItemType>::Resort()`
- L838 _function_ `template <typename TItemType> void SReplicationTreeView<TItemType>::Sort(TArray<TSharedPtr<TItemType>>& Items)`
- L887 _function_ `template <typename TItemType> TSharedPtr<IReplicationTreeColumn<TItemType>> SReplicationTreeView<TItemType>::FindColumnByName(const FName& ColumnId) const`

#### enum `UE::ConcertSharedSlate::SReplicationTreeView::EContent`  
`enum class EContent`  
_L80-84_
- L82 _public enumerator_ `TreeView`
- L83 _public enumerator_ `Custom`

#### struct `UE::ConcertSharedSlate::SReplicationTreeView::FItemMetaData`  
`struct FItemMetaData`  
_L359-363_
- L362 _public member_ `bool bIsExpanded = false;` — Whether the item is expanded

#### enum `UE::ConcertSharedSlate::SReplicationTreeView::EFilterResult`  
`enum class EFilterResult : uint8`  
_L414-418_
- desc: Filtering
- L416 _public enumerator_ `ItemOrChildrenPassFilter`
- L417 _public enumerator_ `NoneInHierarchyPassFilter`

#### Free symbols / members of external scopes

- L22 _macro_ `#define LOCTEXT_NAMESPACE "SReplicationListView"`
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L69 _delegate_ `DECLARE_DELEGATE_OneParam(FDeleteItems, const TArray<TSharedPtr<TItemType>>& SelectedItems);`
- L70 _delegate_ `DECLARE_DELEGATE(FOnSelectionChanged);`
- L75 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(EItemFilterResult, FCustomFilter, const TItemType& Item);`
- L76 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(EComparisonOverride, FIsLessThanOverride, const TSharedPtr<TItemType>& Left, const TSharedPtr<TItemType>& Right);`
- L77 _delegate_ `DECLARE_DELEGATE_TwoParams(FGetItemChildren, TSharedPtr<TItemType> Item, TFunctionRef<void(TSharedPtr<TItemType>)> ProcessChild);`
- L78 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(ESearchTermResult, FGetSearchTermsOverride, const TSharedPtr<TItemType>& Item, TArray<FString>& InOutSearchTerms);`
- L475 _function_ `const auto GetTreeVisibility = [this]()` (scope `UE::ConcertSharedSlate::SReplicationTreeView::CreateTreeView`)
- L476 _function_ `const auto GetWarningVisibility = [this]()` (scope `UE::ConcertSharedSlate::SReplicationTreeView::CreateTreeView`)
- L494 _function_ `.OnSelectionChanged_Lambda([OnSelectionChanged = InArgs._OnSelectionChanged](auto, auto){ OnSelectionChanged.ExecuteIfBound(); }) .OnExpansionChanged(this, &SReplicationTreeView::OnItemExpansionChanged) .SelectionMode(InArgs._SelectionMode) .AllowOverscroll(EAllowOverscroll::No) .HeaderRow(CreateHeaderRow(InArgs))` (scope `UE::ConcertSharedSlate::SReplicationTreeView::CreateTreeView`)
- L510 _function_ `.WidgetIndex_Lambda([this](){ return AllRootItems->IsEmpty() ? 1 : 0; }) .Visibility_Lambda(GetWarningVisibility) +SWidgetSwitcher::Slot() [ SNew(STextBlock).Text(LOCTEXT("AllFiltered", "All items are filtered.")) ] +SWidgetSwitcher::Slot() [ InArgs._NoItemsContent.Widget ] ] ];` (scope `UE::ConcertSharedSlate::SReplicationTreeView::CreateTreeView`)
- L535 _function_ `ColumnNames.Sort([this](const FName& Left, const FName& Right) { return ColumnInfos[Left].ColumnInfo.SortOrder < ColumnInfos[Right].ColumnInfo.SortOrder; });` (scope `UE::ConcertSharedSlate::SReplicationTreeView::CreateHeaderRow`)
- L585 _function_ `` (scope `UE::ConcertSharedSlate::SReplicationTreeView::GetRowChildren`)
- L711 _function_ `SelectedItems.SetNum(Algo::RemoveIf(SelectedItems, [this](const TSharedPtr<TItemType>& Item){ return !FilteredRootItems.Contains(Item); }));` (scope `UE::ConcertSharedSlate::SReplicationTreeView::ReapplyFilters`) — Restore/reset the selected activity.
- L737 _function_ `` (scope `UE::ConcertSharedSlate::SReplicationTreeView::ApplyFiltersRecursive`)
- L819 _function_ `` (scope `UE::ConcertSharedSlate::SReplicationTreeView::OnItemExpansionChanged`)
- L843 _function_ `` (scope `UE::ConcertSharedSlate::SReplicationTreeView::Sort`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Private/Replication/Editor/View/Tree/TreeItemTraits.h` (Private)


#### class `UE::ConcertSharedSlate::TReplicationTreeItemTraits`  
`template<typename TItemType> class TReplicationTreeItemTraits`  
_L38-53_
- desc: Allows type-specific overriding of SReplicationColumnRow behavior. This effectively implements the Strategy design pattern.
- L43 _public function_ `static TSharedRef<ITableRow> GenerateRowWidget(TSharedPtr<TItemType> Item, const TSharedRef<STableViewBase>& OwnerTable, const typename TReplicationTreeData<TItemType>::FGenerateRowArgs& AdditionalArgs)` — Called by SReplicationColumnRow to generate an item's row.
- L49 _public function_ `static bool IsLessThan(const TItemType& Left, const TItemType& Right, const IReplicationTreeColumn<TItemType>& SortByColumn)` — Called by SReplicationColumnRow when sorting items by a column (this is the primary or secondary). Implement this to account for custom row types, if any. You usually want to implement this if you implement GenerateRowWidget.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L14 _function_ `template<typename TItemType> TSharedRef<ITableRow> GenerateRowWidget_Default(TSharedPtr<TItemType> Item, const TSharedRef<STableViewBase>& OwnerTable, const typename TReplicationTreeData<TItemType>::FGenerateRowArgs& AdditionalArgs)` (scope `UE::ConcertSharedSlate`) — Re-usable default behavior for implementing TReplicationTreeItemTraits::GenerateRowWidget. Simply generates a SReplicationColumnRow.
- L28 _function_ `template<typename TItemType> bool IsLessThan_Default(const TItemType& Left, const TItemType& Right, const IReplicationTreeColumn<TItemType>& SortByColumn)` (scope `UE::ConcertSharedSlate`) — Re-usable default behaviour for implementing sorting items by column.

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Private/Replication/Editor/View/Tree/TreeItemTraitsInput.h` (Private)


#### struct `UE::ConcertSharedSlate::FHoverRowContent`  
`struct FHoverRowContent`  
_L21-25_
- L23 _public member_ `TSharedRef<SWidget> Widget;`
- L24 _public member_ `EHorizontalAlignment Alignment = HAlign_Right;`

#### class `UE::ConcertSharedSlate::TReplicationTreeData`  
`template<typename TItemType> class TReplicationTreeData`  
_L29-57_
- desc: Holds type definitions that server as input to TReplicationTreeItemTraits (and thus should not be template specialized).
- L33 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<IReplicationTreeColumn<TItemType>>, FGetColumn, const FName& ColumnId);`
- L34 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedPtr<SWidget>, FOverrideColumnWidget, const FName& ColumnName, const TItemType& RowData);`
- L35 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FHoverRowContent, FGetHoveredRowContent, const TSharedPtr<TItemType>& Item);`
- L56 _public prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(TSharedPtr<ITableRow>, FOverrideRowWidget, TSharedPtr<TItemType> Item, const TSharedRef<STableViewBase>& OwnerTable, const FGenerateRowArgs& AdditionalArgs);` — Overrides the widget for the row if the delegate returns non-nullptr.

#### struct `UE::ConcertSharedSlate::TReplicationTreeData::FGenerateRowArgs`  
`struct FGenerateRowArgs`  
_L37-53_
- L40 _public member_ `FGetColumn GetColumnDelegate;` — Gets info about a replication column.
- L42 _public member_ `FOverrideColumnWidget OverrideColumnWidgetDelegate;` — Overrides a column's content widget.
- L45 _public member_ `FGetHoveredRowContent GetHoveredRowContent;` — Optional. Gets the content to overlay on hovered rows; it covers the entire row.
- L48 _public member_ `TSharedPtr<FText> HighlightText;` — The text to highlight - equal to search text.
- L50 _public member_ `FName ExpandableColumnId;` — The name of the column which will have the SExpandableArrow widget for the tree view.
- L52 _public member_ `const FTableRowStyle* RowStyle = nullptr;` — Style to use for rows

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L33 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<IReplicationTreeColumn<TItemType>>, FGetColumn, const FName& ColumnId);`
- L34 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedPtr<SWidget>, FOverrideColumnWidget, const FName& ColumnName, const TItemType& RowData);`
- L35 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FHoverRowContent, FGetHoveredRowContent, const TSharedPtr<TItemType>& Item);`
- L56 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(TSharedPtr<ITableRow>, FOverrideRowWidget, TSharedPtr<TItemType> Item, const TSharedRef<STableViewBase>& OwnerTable, const FGenerateRowArgs& AdditionalArgs);` — Overrides the widget for the row if the delegate returns non-nullptr.

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Private/Session/Activity/SessionActivityUtils.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::ConcertSharedSlate`)
- L12 _prototype_ `FText GetOperationName(const FConcertSessionActivity& Activity);` (scope `UE::ConcertSharedSlate::Private`)
- L13 _prototype_ `FText GetPackageName(const FConcertSessionActivity& Activity);` (scope `UE::ConcertSharedSlate::Private`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Private/Session/Browser/SNewSessionRow.h` (Private)


#### class `SNewSessionRow`  
`class SNewSessionRow : public SMultiColumnTableRow<TSharedPtr<FConcertSessionTreeItem>>`  
_L22-91_
- inherits: `SMultiColumnTableRow<TSharedPtr<FConcertSessionTreeItem>>`
- desc: The type of row used in the session list view to edit a new session (the session name + server).
- L25 _public typedef_ `using FGetServersFunc = TFunction<TArray<FConcertServerInfo>()>;`
- L27 _public typedef_ `using FAcceptFunc = TFunction<void(const TSharedPtr<FConcertSessionTreeItem>&)>;` — Should remove the editable 'new' row and creates the sessions.
- L29 _public typedef_ `using FDeclineFunc = TFunction<void(const TSharedPtr<FConcertSessionTreeItem>&)>;` — Should just remove the editable 'new' row.
- L31 _public function_ `SLATE_BEGIN_ARGS(SNewSessionRow)` — Needed to use Args because Construct() is limited to 5 arguments and 6 were required.
- L37 _public prototype_ `SLATE_ARGUMENT(FGetServersFunc, GetServerFunc) SLATE_ARGUMENT(FAcceptFunc, OnAcceptFunc) SLATE_ARGUMENT(FDeclineFunc, OnDeclineFunc) SLATE_ATTRIBUTE(FText, HighlightText) SLATE_ATTRIBUTE(FString, DefaultServerURL) SLATE_ATTRIBUTE(FMargin, Padding) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FConcertSessionTreeItem> InItem, const TSharedRef<STableViewBase>& InOwnerTableView);`
- L50 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L51 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L55 _private prototype_ `TSharedRef<SWidget> OnGenerateServersComboOptionWidget(TSharedPtr<FConcertServerInfo> Item);`
- L56 _private prototype_ `TSharedRef<SWidget> MakeSelectedServerWidget();`
- L57 _private prototype_ `FText GetSelectedServerText() const;`
- L58 _private prototype_ `const FSlateBrush* GetSelectedServerIgnoreVersionImage() const;`
- L59 _private prototype_ `FText GetSelectedServerIgnoreVersionTooltip() const;`
- L60 _private prototype_ `FText GetServerDisplayName(const FString& ServerName) const;`
- L62 _private prototype_ `void OnSessionNameChanged(const FText& NewName);`
- L63 _private prototype_ `void OnSessionNameCommitted(const FText& NewText, ETextCommit::Type CommitType);`
- L64 _private prototype_ `void OnProjectNameCommitted(const FText& NewProjectName, ETextCommit::Type CommitType);`
- L66 _private prototype_ `FReply OnAccept();`
- L67 _private prototype_ `FReply OnDecline();`
- L68 _private prototype_ `FReply OnKeyDownHandler(const FGeometry&, const FKeyEvent&);` — Registered as handler to the editable text (vs. OnKeyDown() virtual method).
- L70 _private prototype_ `void UpdateServerList();`
- L73 _private member_ `UE::ConcertSharedSlate::FColumnVisibilityTransaction TemporaryColumnShower;` — Helper for temporarily showing all columns required for this column
- L76 _private member_ `TWeakPtr<FConcertSessionTreeItem> Item;` — Holds the new item to fill with session name and server.
- L78 _private member_ `TArray<TSharedPtr<FConcertServerInfo>> Servers;` — Servers displayed in the server combo box.
- L80 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FConcertServerInfo>>> ServersComboBox;`
- L81 _private member_ `TSharedPtr<SEditableTextBox> EditableSessionName;`
- L82 _private member_ `TSharedPtr<SEditableTextBox> ProjectNameTextBox;`
- L84 _private member_ `FGetServersFunc GetServersFunc;`
- L85 _private member_ `FAcceptFunc AcceptFunc;`
- L86 _private member_ `FDeclineFunc DeclineFunc;`
- L88 _private member_ `TAttribute<FText> HighlightText;`
- L89 _private member_ `TAttribute<FString> DefaultServerURL;`
- L90 _private member_ `bool bInitialFocusTaken = false;`

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Private/Session/Browser/SSaveRestoreSessionRow.h` (Private)


#### class `SSaveRestoreSessionRow`  
`class SSaveRestoreSessionRow : public SMultiColumnTableRow<TSharedPtr<FConcertSessionTreeItem>>`  
_L20-73_
- inherits: `SMultiColumnTableRow<TSharedPtr<FConcertSessionTreeItem>>`
- desc: The type of row used in the session list view to create and archive or restore a session (edit the information required for the operation).
- L24 _public typedef_ `using FAcceptFunc = TFunction<void(TSharedPtr<FConcertSessionTreeItem>, const FString&)>;` — Should remove the editable row and save or restore the session.
- L26 _public typedef_ `using FDeclineFunc = TFunction<void(TSharedPtr<FConcertSessionTreeItem>)>;` — Should only remove the editable row from the table.
- L28 _public function_ `SLATE_BEGIN_ARGS(SSaveRestoreSessionRow) : _OnAcceptFunc() , _OnDeclineFunc() , _HighlightText()`
- L33 _public prototype_ `SLATE_ARGUMENT(FAcceptFunc, OnAcceptFunc) SLATE_ARGUMENT(FDeclineFunc, OnDeclineFunc) SLATE_ATTRIBUTE(FText, HighlightText) SLATE_ATTRIBUTE(FMargin, Padding) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FConcertSessionTreeItem> Node, const TSharedRef<STableViewBase>& InOwnerTableView);`
- L42 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L43 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L45 _public prototype_ `void OnSessionNameChanged(const FText& NewName);`
- L46 _public prototype_ `void OnSessionNameCommitted(const FText& NewText, ETextCommit::Type CommitType);`
- L47 _public prototype_ `FReply OnAccept();`
- L48 _public prototype_ `FReply OnDecline();`
- L49 _public prototype_ `FReply OnKeyDownHandler(const FGeometry&, const FKeyEvent&);` — Registered as handler to the editable text (vs. OnKeyDown() virtual method for this widget).
- L52 _public prototype_ `virtual TBitArray<> GetWiresNeededByDepth() const override;` — Override SMultiColumnTableRow functions to ensure a wire is drawn between the item to restore and the editable row to link them together.
- L53 _public function_ `virtual bool IsLastChild() const override`
- L54 _public function_ `virtual int32 DoesItemHaveChildren() const override`
- L55 _public function_ `virtual bool IsItemExpanded() const override`
- L58 _public prototype_ `FText GetDefaultName(const FConcertSessionTreeItem& Item) const;` — Generates a default name for an archive or a restored session.
- L63 _private member_ `UE::ConcertSharedSlate::FColumnVisibilityTransaction TemporaryColumnShower;` — Helper for temporarily showing all columns required for this column
- L65 _private member_ `TWeakPtr<FConcertSessionTreeItem> Item;`
- L66 _private member_ `TSharedPtr<SEditableTextBox> EditableSessionName;`
- L68 _private member_ `FAcceptFunc AcceptFunc;`
- L69 _private member_ `FDeclineFunc DeclineFunc;`
- L71 _private member_ `TAttribute<FText> HighlightText;`
- L72 _private member_ `bool bInitialFocusTaken = false;`

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Private/Session/Browser/SSessionGroupRow.h` (Private)


#### class `SSessionGroupRow`  
`class SSessionGroupRow : public SMultiColumnTableRow<TSharedPtr<FConcertSessionTreeItem>>`  
_L20-43_
- inherits: `SMultiColumnTableRow<TSharedPtr<FConcertSessionTreeItem>>`
- desc: The type of row used in the session list view to edit a new session (the session name + server).
- L30 _public function_ `SLATE_BEGIN_ARGS(SSessionGroupRow)`
- L32 _public prototype_ `SLATE_ARGUMENT(EGroupType, GroupType) SLATE_ATTRIBUTE(FMargin, Padding) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView);`
- L38 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L42 _private member_ `EGroupType GroupType{};`

#### enum `SSessionGroupRow::EGroupType`  
`enum class EGroupType`  
_L24-28_
- L26 _public enumerator_ `Active`
- L27 _public enumerator_ `Archived`

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Private/Session/Browser/SSessionRow.h` (Private)


#### class `SSessionRow`  
`class SSessionRow : public SMultiColumnTableRow<TSharedPtr<FConcertSessionTreeItem>>`  
_L16-73_
- inherits: `SMultiColumnTableRow<TSharedPtr<FConcertSessionTreeItem>>`
- L19 _public typedef_ `using FDoubleClickFunc = TFunction<void(TSharedPtr<FConcertSessionTreeItem>)>;`
- L20 _public typedef_ `using FRenameFunc = TFunction<void(TSharedPtr<FConcertSessionTreeItem>, const FString&)>;`
- L21 _public typedef_ `using FIsDefaultSession = TFunction<bool(TSharedPtr<FConcertSessionTreeItem>)>;`
- L23 _public function_ `SLATE_BEGIN_ARGS(SSessionRow) : _OnDoubleClickFunc() , _OnRenameFunc() , _HighlightText() , _IsSelected(false)`
- L30 _public prototype_ `SLATE_ARGUMENT(FDoubleClickFunc, OnDoubleClickFunc) SLATE_ARGUMENT(FRenameFunc, OnRenameFunc) SLATE_ARGUMENT(FIsDefaultSession, IsDefaultSession) SLATE_ATTRIBUTE(FText, HighlightText) SLATE_ATTRIBUTE(FMargin, Padding) SLATE_ATTRIBUTE(bool, IsSelected) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FConcertSessionTreeItem> InItem, const TSharedRef<STableViewBase>& InOwnerTableView);`
- L42 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L43 _public prototype_ `virtual FReply OnMouseButtonDoubleClick( const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L45 _public prototype_ `void OnSessionNameCommitted(const FText& NewSessionName, ETextCommit::Type CommitType);`
- L48 _private prototype_ `FSlateFontInfo GetFontInfo(bool bIsActiveSession, bool bIsDefault);`
- L49 _private prototype_ `FSlateColor GetFontColor(bool bIsActiveSession, bool bIsDefault);`
- L51 _private prototype_ `TSharedRef<SWidget> GenerateSessionColumn(const FSlateFontInfo& FontInfo, const FSlateColor& FontColor);`
- L52 _private prototype_ `TSharedRef<SWidget> GenerateServerColumn(const FSlateFontInfo& FontInfo, const FSlateColor& FontColor);`
- L53 _private prototype_ `TSharedRef<SWidget> GenerateServerDefaultColumn(const FSlateFontInfo& FontInfo, const FSlateColor& FontColor);`
- L54 _private prototype_ `TSharedRef<SWidget> GenerateProjectColumn(const FSlateFontInfo& FontInfo, const FSlateColor& FontColor);`
- L55 _private prototype_ `TSharedRef<SWidget> GenerateVersionColumn(const FSlateFontInfo& FontInfo, const FSlateColor& FontColor);`
- L56 _private prototype_ `TSharedRef<SWidget> GenerateLastModifiedColumn(const FSlateFontInfo& FontInfo, const FSlateColor& FontColor);`
- L58 _private function_ `void OnBeginEditingSessionName()`
- L59 _private prototype_ `bool OnValidatingSessionName(const FText& NewSessionName, FText& OutError);`
- L61 _private member_ `TWeakPtr<FConcertSessionTreeItem> Item;`
- L64 _private member_ `FDoubleClickFunc DoubleClickFunc;` — Invoked when the user double click on the row
- L66 _private member_ `FRenameFunc RenameFunc;` — Invoked when the user commit the session rename. (This will send the request to server)
- L68 _private member_ `FIsDefaultSession IsDefaultSession;` — Given a session checks whether it is the default session the client is supposed to join
- L70 _private member_ `TAttribute<FText> HighlightText;`
- L71 _private member_ `TAttribute<bool> IsSelected;`
- L72 _private member_ `TSharedPtr<SInlineEditableTextBlock> SessionNameText;`

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/ConcertFrontendStyle.h` (Public)


#### class `FConcertFrontendStyle`  
`class FConcertFrontendStyle`  
_L11-26_
- L15 _public prototype_ `static void Initialize();`
- L16 _public prototype_ `static void Shutdown();`
- L18 _public prototype_ `static TSharedPtr< class ISlateStyle > Get();`
- L20 _public prototype_ `static FName GetStyleSetName();`
- L24 _private prototype_ `static FString InContent(const FString& RelativePath, const ANSICHAR* Extension);`
- L25 _private member_ `static TSharedPtr< class FSlateStyleSet > StyleSet;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CONCERTSHAREDSLATE_API`

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/ConcertFrontendUtils.h` (Public)


#### enum `ETimeFormat`  
`enum class ETimeFormat`  
_L19-23_
- reflection: `UENUM()`
- desc: Defines how the time should be displayed in the date/time column.
- L21 _public enumerator_ `Relative` — Display relative time (23 seconds ago)
- L22 _public enumerator_ `Absolute` — Display absolute time (April 7, 2019 - 10:33:52)

#### Free symbols / members of external scopes

- L15 _macro_ `#define LOCTEXT_NAMESPACE "ConcertFrontendUtils"`
- L25 _namespace_ `namespace ConcertFrontendUtils`
- L28 _function_ `template <typename ItemType, typename PredFactoryType> inline void SyncArraysByPredicate(TArray<TSharedPtr<ItemType>>& InOutArray, TArray<TSharedPtr<ItemType>>&& InNewArray, const PredFactoryType& InPredFactory)` (scope `ConcertFrontendUtils`)
- L64 _function_ `template <typename ItemType> inline TArray<TSharedPtr<ItemType>> DeepCopyArray(const TArray<TSharedPtr<ItemType>>& InArray)` (scope `ConcertFrontendUtils`)
- L78 _function_ `template <typename ItemType> inline TArray<TSharedPtr<ItemType>> DeepCopyArrayAndClearSource(TArray<TSharedPtr<ItemType>>& InOutArray)` (scope `ConcertFrontendUtils`)
- L86 _function_ `inline const FSlateBrush* GetExpandableAreaBorderImage(const SExpandableArea& Area)` (scope `ConcertFrontendUtils`) — Returns the image used to render the expandable area title bar with respect to its hover/expand state.
- L95 _function_ `static FText FormatRelativeTime(const FDateTime& EventTime, const FDateTime* CurrTime = nullptr)` (scope `ConcertFrontendUtils`)
- L131 _function_ `static FText FormatTime(const FDateTime& Time, ETimeFormat TimeFormat, const FDateTime* CurrTime = nullptr)` (scope `ConcertFrontendUtils`)
- L138 _function_ `static TSharedRef<SComboButton> CreateViewOptionsComboButton(FOnGetContent GetMenuContentDelegate)` (scope `ConcertFrontendUtils`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/ConcertHeaderRowUtils.h` (Public)


#### struct `FColumnVisibilitySnapshot`  
`struct FColumnVisibilitySnapshot`  
_L13-19_
- reflection: `USTRUCT()`
- L18 _public member_ `FString Snapshot;` — `UPROPERTY()`

#### class `UE::ConcertSharedSlate::FColumnVisibilityTransaction`  
`class FColumnVisibilityTransaction`  
_L46-59_
- desc: Helper for temporarily setting column visibilities to a certain setting.
- L48 _private member_ `TMap<FName, bool> SavedColumnVisibilities;`
- L49 _private member_ `TMap<FName, bool> OverridenColumnVisibilities;`
- L50 _private member_ `TWeakPtr<SHeaderRow> HeaderRow;`
- L53 _public prototype_ `FColumnVisibilityTransaction(TWeakPtr<SHeaderRow> HeaderRow = nullptr);`
- L54 _public prototype_ `FColumnVisibilityTransaction& SetHeaderRow(TWeakPtr<SHeaderRow> InHeaderRow);`
- L56 _public prototype_ `FColumnVisibilityTransaction& SaveVisibilityAndSet(FName ColumnId, bool bShouldBeVisible);`
- L58 _public prototype_ `void ResetToSavedVisibilities(bool bOnlyResetIfNotOverriden = true);` — @param bOnlyResetIfNotOverriden Only reset to the old visibilities if none has changed from the saved state (i.e. user changed it during the operation)

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L23 _delegate_ `DECLARE_DELEGATE_OneParam(FSaveColumnVisibilitySnapshot, const FColumnVisibilitySnapshot& );`
- L23 _prototype_ `DECLARE_DELEGATE_OneParam(FSaveColumnVisibilitySnapshot, const FColumnVisibilitySnapshot& );` (scope `UE::ConcertSharedSlate`)
- L26 _prototype_ `TSharedRef<SWidget> MakeTableContextMenu(const TSharedRef<SHeaderRow>& HeaderRow, TMap<FName, bool> ColumnsVisibleByDefault = {}, bool bDefaultVisibility = true);` (scope `UE::ConcertSharedSlate`) — Util function that can be directly fed into SListView::OnContextMenuOpening
- L31 _prototype_ `void AddDefaultControlEntries(const TSharedRef<SHeaderRow>& HeaderRow, FMenuBuilder& MenuBuilder, TMap<FName, bool> ColumnsVisibleByDefault, bool bDefaultVisibility = true);` (scope `UE::ConcertSharedSlate`) — Adds an entry for "Show all", "Hide all", and "Restore column visibility".
- L38 _prototype_ `void AddEntriesForShowingHiddenRows(const TSharedRef<SHeaderRow>& HeaderRow, FMenuBuilder& MenuBuilder);` (scope `UE::ConcertSharedSlate`) — Inspects the hidden rows on the header row and an entry for showing each hidden column. @param HeaderRow To retrieve column information @param MenuBuilder Where to add the menu entries
- L41 _prototype_ `FColumnVisibilitySnapshot SnapshotColumnVisibilityState(const TSharedRef<SHeaderRow>& HeaderRow);` (scope `UE::ConcertSharedSlate`) — Exports the visibility state of each column so it can be restore later
- L43 _prototype_ `void RestoreColumnVisibilityState(const TSharedRef<SHeaderRow>& HeaderRow, const FColumnVisibilitySnapshot& Snapshot);` (scope `UE::ConcertSharedSlate`) — Restores the column visibilities from an exported state

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/IConcertSharedSlateModule.h` (Public)


#### class `IConcertSharedSlateModule`  
`class IConcertSharedSlateModule : public IModuleInterface`  
_L12-21_
- inherits: `IModuleInterface`
- desc: Interface for the Concert Sync UI module.
- L16 _public function_ `static IConcertSharedSlateModule& Get()` — Get the ConcertSyncUI module

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Model/Item/IItemSourceModel.h` (Public)


#### enum `UE::ConcertSharedSlate::ESourceType`  
`enum class ESourceType : uint8`  
_L15-37_
- L21 _public enumerator_ `ShowAsList` — Display EnumerateSelectableItems in a drop-down or menu list. Each entry is a button that closes the menu. Example: User wants to search from a list of actors.
- L26 _public enumerator_ `AddOnClick` — When this option is clicked, instantly add all of EnumerateSelectableItems. Example: User wants to add all actors selected in the world outliner.
- L36 _public enumerator_ `ShowAsToggleButtonList` — Display EnumerateSelectableItems in a drop-down or menu list. Each entry contains a checkbox: - FSourceModelBuilders::OnItemsSelected is called when the checkbox is toggled (since you provide IsItemSelected, you can determine whether to add or remove the items). - FSourceModelBuilders::IsItemSelected determines whether the checkbox is checked Example: User wants to search from a list of actors.

#### struct `UE::ConcertSharedSlate::FBaseDisplayInfo`  
`struct FBaseDisplayInfo`  
_L39-48_
- L42 _public member_ `FText Label;` — What the model should be displayed as in UI.
- L44 _public member_ `FText ToolTip;` — Optional tooltip when the model is hovered.
- L47 _public member_ `FSlateIcon Icon;` — Optional icon to display entry as.

#### struct `UE::ConcertSharedSlate::FSourceDisplayInfo`  
`struct FSourceDisplayInfo : FBaseDisplayInfo`  
_L50-54_
- inherits: `FBaseDisplayInfo`
- L53 _public member_ `ESourceType SourceType;` — Determines what happens when the option is clicked / hovered.

#### class `UE::ConcertSharedSlate::IItemSourceModel`  
`template<typename TItemType> class IItemSourceModel : public TSharedFromThis<IItemSourceModel<TItemType>>`  
_L71-108_
- inherits: `TSharedFromThis<IItemSourceModel<TItemType>>`
- desc: Defines the source for of item, e.g. objects. Imagine you have a list view displaying a list of objects. Over it is a "Add Object" combo button. In the button's menu, you'd find e.g. "Add from World", "Add from Selection", "Import from File", etc. Each of of these sub-menu entries is an item source and corresponds to an IItemSourceModel. @see IObjectSelectionSourceModel and FEditorObjectSelectionSourceModel for an example how sources may be used. Models may also be useful for building context menus entries. When you right-click an item, you may want to add more items based on the object clicked, e.g. add the components of a right-clicked actor. @see FEditorObjectSelectionSourceModel::FContextMenuSources and FEditorObjectSelectionSourceModel::GetContextMenuOptions @see FSourceModelBuilders for building UI from models, e.g. the above mentioned combo button or context menus.
- L76 _public prototype_ `virtual FSourceDisplayInfo GetDisplayInfo() const = 0;` — Some data for displaying this source in UI.
- L80 _public function_ `virtual uint32 GetNumSelectableItems() const` — `UE_DEPRECATED(5.5, "No longer in use")` — @return The number of selectable objects.
- L83 _public prototype_ `virtual void EnumerateSelectableItems(TFunctionRef<EBreakBehavior(const TItemType& SelectableOption)> Delegate) const = 0;` — Enumerates ALL objects from this source. This can be a LOT of objects (e.g. 2000 actors). Intended to be placed in a searchable drop-down menu.
- L86 _public function_ `virtual bool HasOptions() const` — @return Whether there are any options.
- L95 _public function_ `TArray<TItemType> GetSelectableItems()` — Util that converts EnumerateSelectableItems into an array.
- L107 _public prototype_ `virtual ~IItemSourceModel() = default;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L89 _function_ `EnumerateSelectableItems([&bHasAnItem](const auto&){ bHasAnItem = true; return EBreakBehavior::Break; });` (scope `UE::ConcertSharedSlate::IItemSourceModel::HasOptions`)
- L99 _function_ `` (scope `UE::ConcertSharedSlate::IItemSourceModel::GetSelectableItems`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Model/Item/SourceModelBuilders.h` (Public)


#### enum `UE::ConcertSharedSlate::EItemPickerFlags`  
`enum class EItemPickerFlags`  
_L27-32_
- L29 _public enumerator_ `None`
- L31 _public enumerator_ `DisplayOptionListInline = 1 << 0` — If the source type is ESourceType::ShowAsList, instead of creating a menu entry that spawns a submenu (default behavior) just place the source's items in the same menu.

#### struct `UE::ConcertSharedSlate::FSourceModelBuilders`  
`template<typename TItemType> struct FSourceModelBuilders`  
_L39-111_
- desc: Utility for creating widgets of IItemSourceModel and categories thereof (TSourceSelectionCategory).
- L41 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnItemsSelected, TArray<TItemType>);`
- L42 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsItemSelected, const TItemType& Item);`
- L43 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FString, FGetItemDisplayString, const TItemType& Item);`
- L44 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FSlateIcon, FGetItemIcon, const TItemType& Item);`
- L90 _public prototype_ `static TSharedRef<SWidget> BuildCategory(const TSourceSelectionCategory<TItemType>& Category, const FItemPickerArgs& Args);` — Builds a combo button where each entry corresponds to one IItemSourceModel. If there is only one option, the option is inlined by calling MakeStandaloneWidget.
- L98 _public prototype_ `static TSharedRef<SWidget> MakeStandaloneWidget(TSharedRef<IItemSourceModel<TItemType>> Source, FItemPickerArgs Args, FSlateIcon Icon);` — Creates a combo button inlining the source model. This is the inlined case of when a category only contains one item source. Used by BuildCategory.
- L101 _public prototype_ `static void AddOptionToMenu(TSharedRef<IItemSourceModel<TItemType>> Option, FItemPickerArgs Args, FBaseMenuBuilder& MenuBuilder);` — Adds the option to a context-menu
- L105 _private prototype_ `static void FillSearchableSubmenu(const TSharedRef<IItemSourceModel<TItemType>>& Source, const FItemPickerArgs& Args, FBaseMenuBuilder& MenuBuilder);`
- L107 _private prototype_ `static TSharedRef<SWidget> BuildMenu(const TArray<TAttribute<TSharedPtr<IItemSourceModel<TItemType>>>>& Options, TArray<TSourceSelectionCategory<TItemType>> SubCategories, const FItemPickerArgs& Args);`
- L108 _private prototype_ `static bool NeedsSeparationFromOtherItems(const TSharedRef<IItemSourceModel<TItemType>>& Option, const FItemPickerArgs& Args);`
- L110 _private prototype_ `static void AddSubCategoryToMenu(const TSourceSelectionCategory<TItemType>& Category, const FItemPickerArgs& Args, FBaseMenuBuilder& MenuBuilder);`
- L120 _function_ `template<typename TItemType> TSharedRef<SWidget> FSourceModelBuilders<TItemType>::BuildCategory(const TSourceSelectionCategory<TItemType>& Category, const FItemPickerArgs& Args)` — Builds a combo button where each entry corresponds to one IItemSourceModel. If there is only one option, the option is inlined by calling MakeStandaloneWidget.
- L153 _function_ `template<typename TItemType> TSharedRef<SWidget> FSourceModelBuilders<TItemType>::MakeStandaloneWidget(TSharedRef<IItemSourceModel<TItemType>> Source, FItemPickerArgs Args, FSlateIcon Icon)` — Creates a widget that displays the IItemSourceModel according to its specifications. Mainly to be used by BuildCategory.
- L201 _function_ `template<typename TItemType> void FSourceModelBuilders<TItemType>::AddOptionToMenu(TSharedRef<IItemSourceModel<TItemType>> Option, FItemPickerArgs Args, FBaseMenuBuilder& MenuBuilder)` — Adds the option to a context-menu
- L258 _function_ `template<typename TItemType> void FSourceModelBuilders<TItemType>::FillSearchableSubmenu(const TSharedRef<IItemSourceModel<TItemType>>& Source, const FItemPickerArgs& Args, FBaseMenuBuilder& MenuBuilder)`
- L298 _function_ `template<typename TItemType> TSharedRef<SWidget> FSourceModelBuilders<TItemType>::BuildMenu(const TArray<TAttribute<TSharedPtr<IItemSourceModel<TItemType>>>>& Options, TArray<TSourceSelectionCategory<TItemType>> SubCategories, const FItemPickerArgs& Args)`
- L349 _function_ `template <typename TItemType> bool FSourceModelBuilders<TItemType>::NeedsSeparationFromOtherItems(const TSharedRef<IItemSourceModel<TItemType>>& Option, const FItemPickerArgs& Args)`
- L357 _function_ `template<typename TItemType> void FSourceModelBuilders<TItemType>::AddSubCategoryToMenu(const TSourceSelectionCategory<TItemType>& Category, const FItemPickerArgs& Args, FBaseMenuBuilder& MenuBuilder)`

#### struct `UE::ConcertSharedSlate::FSourceModelBuilders::FItemPickerArgs`  
`struct FItemPickerArgs`  
_L46-87_
- L49 _public member_ `FOnItemsSelected OnItemsSelected;` — Required. Called when items are picked by the widget.
- L52 _public member_ `FGetItemDisplayString GetItemDisplayString;` — Required. Gets the display string for the item.
- L55 _public member_ `FGetItemIcon GetItemIcon;` — Optional. Gets the icon to display for the item.
- L58 _public member_ `FIsItemSelected IsItemSelected;` — Optional. Used primarily to filter out objects that are already selected.
- L61 _public member_ `TAttribute<bool> IsEnabledAttribute;` — Optional. Whether the UI is enabled.
- L63 _public member_ `TAttribute<FText> DisabledToolTipAttribute;` — Optional. If IsEnabled returns true, this tooltip is displayed on the relevant UI.
- L66 _public member_ `EItemPickerFlags Flags;` — Special flags for altering default behavior.
- L68 _public function_ `FItemPickerArgs( FOnItemsSelected OnObjectsSelected, FGetItemDisplayString GetItemDisplayString, FGetItemIcon GetItemIcon = {}, FIsItemSelected IsItemSelected = {}, TAttribute<bool> IsEnabledAttribute = {}, TAttribute<FText> DisabledToolTipAttribute = {}, EItemPickerFlags Flags = EItemPickerFlags::None ) : OnItemsSelected(MoveTemp(OnObjectsSelected)) , GetItemDisplayString(MoveTemp(GetItemDisplayString)) , GetItemIcon(MoveTemp(GetItemIcon)) , IsItemSelected(MoveTemp(IsItemSelected)) , IsEnabledAttribute(MoveTemp(IsEnabledAttribute)) , DisabledToolTipAttribute(MoveTemp(DisabledToolTipAttribute)) , Flags(Flags)`

#### Free symbols / members of external scopes

- L18 _macro_ `#define LOCTEXT_NAMESPACE "FSourceModelBuilders"`
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L33 _prototype_ `ENUM_CLASS_FLAGS(EItemPickerFlags);` (scope `UE::ConcertSharedSlate`)
- L41 _delegate_ `DECLARE_DELEGATE_OneParam(FOnItemsSelected, TArray<TItemType>);`
- L42 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsItemSelected, const TItemType& Item);`
- L43 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FString, FGetItemDisplayString, const TItemType& Item);`
- L44 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FSlateIcon, FGetItemIcon, const TItemType& Item);`
- L116 _namespace_ `namespace UE`
- L116 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L136 _function_ `` (scope `UE::ConcertSharedSlate::FSourceModelBuilders::BuildCategory`)
- L144 _function_ `.IsEnabled_Lambda([IsEnabled = Args.IsEnabledAttribute](){ return !(IsEnabled.IsBound() || IsEnabled.IsSet()) || IsEnabled.Get(); }) .OnGetMenuContent_Lambda([Options = Category.Options, SubCategories = Category.SubCategories, Args]() { return BuildMenu(Options, SubCategories, Args); });` (scope `UE::ConcertSharedSlate::FSourceModelBuilders::BuildCategory`)
- L159 _function_ `` (scope `UE::ConcertSharedSlate::FSourceModelBuilders::MakeStandaloneWidget`)
- L175 _function_ `.IsEnabled_Lambda([IsEnabled = Args.IsEnabledAttribute](){ return !(IsEnabled.IsBound() || IsEnabled.IsSet()) || IsEnabled.Get(); }) .OnGetMenuContent_Lambda([Source = MoveTemp(Source), Args = MoveTemp(Args)]() { FMenuBuilder MenuBuilder(true, nullptr); FillSearchableSubmenu(Source, Args, MenuBuilder); return MenuBuilder.MakeWidget(); });` (scope `UE::ConcertSharedSlate::FSourceModelBuilders::MakeStandaloneWidget`)
- L187 _function_ `.IsEnabled_Lambda([IsEnabled = Args.IsEnabledAttribute](){ return !(IsEnabled.IsBound() || IsEnabled.IsSet()) || IsEnabled.Get(); }) .OnClicked_Lambda([Source = MoveTemp(Source), AddObjectsDelegate = Args.OnItemsSelected]() { AddObjectsDelegate.Execute(Source->GetSelectableItems()); return FReply::Handled(); });` (scope `UE::ConcertSharedSlate::FSourceModelBuilders::MakeStandaloneWidget`)
- L222 _function_ `FExecuteAction::CreateLambda([](){}) };` (scope `UE::ConcertSharedSlate::FSourceModelBuilders::AddOptionToMenu`)
- L225 _function_ `` (scope `UE::ConcertSharedSlate::FSourceModelBuilders::AddOptionToMenu`)
- L244 _function_ `FExecuteAction::CreateLambda([Option, Args = MoveTemp(Args)](){ Args.OnItemsSelected.Execute(Option->GetSelectableItems()); }), FCanExecuteAction::CreateLambda([Option](){ return Option->HasOptions(); }) };` (scope `UE::ConcertSharedSlate::FSourceModelBuilders::AddOptionToMenu`)
- L262 _function_ `` (scope `UE::ConcertSharedSlate::FSourceModelBuilders::FillSearchableSubmenu`)
- L274 _function_ `? FCanExecuteAction::CreateLambda([Item, IsItemSelected = Args.IsItemSelected](){ return !IsItemSelected.IsBound() || !IsItemSelected.Execute(Item); }) : FCanExecuteAction::CreateLambda([](){ return true; });` (scope `UE::ConcertSharedSlate::FSourceModelBuilders::FillSearchableSubmenu`)
- L275 _function_ `: FCanExecuteAction::CreateLambda([](){ return true; });` (scope `UE::ConcertSharedSlate::FSourceModelBuilders::FillSearchableSubmenu`)
- L278 _function_ `: FIsActionChecked::CreateLambda([Item, IsItemSelected = Args.IsItemSelected](){ return IsItemSelected.IsBound() && IsItemSelected.Execute(Item); });` (scope `UE::ConcertSharedSlate::FSourceModelBuilders::FillSearchableSubmenu`)
- L281 _function_ `FText::FromString(Args.GetItemDisplayString.Execute(Item)), TAttribute<FText>(TAttribute<FText>::CreateLambda([CanExecuteAction](){ return CanExecuteAction.Execute() ? LOCTEXT("ItemSelected", "Item is already selected") : FText::GetEmpty(); })), Args.GetItemIcon.IsBound() ? Args.GetItemIcon.Execute(Item) : FSlateIcon(), FUIAction( FExecuteAction::CreateLambda([Item, SelectItemDelegate = Args.OnItemsSelected]() { SelectItemDelegate.Execute({ Item }); }), CanExecuteAction, IsActionChecked ), NAME_None, bUseButton ? EUserInterfaceActionType::Button : EUserInterfaceActionType::ToggleButton );` (scope `UE::ConcertSharedSlate::FSourceModelBuilders::FillSearchableSubmenu`)
- L332 _function_ `` (scope `UE::ConcertSharedSlate::FSourceModelBuilders::BuildMenu`)
- L365 _function_ `FExecuteAction::CreateLambda([](){}) };` (scope `UE::ConcertSharedSlate::FSourceModelBuilders::AddSubCategoryToMenu`)
- L369 _function_ `` (scope `UE::ConcertSharedSlate::FSourceModelBuilders::AddSubCategoryToMenu`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Model/Item/SourceSelectionCategory.h` (Public)


#### struct `UE::ConcertSharedSlate::TSourceSelectionCategory`  
`template<typename TSelectionType> struct TSourceSelectionCategory`  
_L22-32_
- desc: A category groups IItemSourceModel together, e.g. a category "Add actor" could have options like - selected in outliner - drop-down list of actors in the world Usually a category is displayed by a combo button with DisplayInfo being applied to it. However, if Options.Num() == 1, then for better UX the button can be "inlined" with a widget visualizing that option, e.g. a button that just invokes the single option and its IObjectSourceModel::GetDisplayInfo is applied to the button.
- L25 _public member_ `FBaseDisplayInfo DisplayInfo;` — Data to display about this category.
- L28 _public member_ `TArray<TAttribute<TSharedPtr<IItemSourceModel<TSelectionType>>>> Options;` — The options of this category. TAttribute to allow lazy instantiation (e.g. only when sub-menu is opened by user).
- L31 _public member_ `TArray<TSourceSelectionCategory> SubCategories;` — Sub-categories to show in the context menu. Example: "Add component" is subcategory with the items being FComponentFromActorSource_Root.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Replication/Editor/Model/Data/PropertyData.h` (Public)


#### class `UE::ConcertSharedSlate::FPropertyData`  
`class FPropertyData`  
_L13-48_
- desc: Instanced for each property row in IPropertyTreeView.
- L17 _public function_ `FPropertyData(TArray<TSoftObjectPtr<>> ContextObjects, FSoftClassPath OwningClass, FConcertPropertyChain Object) : ContextObjects(MoveTemp(ContextObjects)) , OwningClassPtr(MoveTemp(OwningClass)) , Property(MoveTemp(Object))`
- L23 _public function_ `const TArray<TSoftObjectPtr<>>& GetContextObjects() const`
- L24 _public function_ `const FConcertPropertyChain& GetProperty() const`
- L25 _public function_ `const TSoftClassPtr<>& GetOwningClassPtr() const`
- L36 _private member_ `TArray<TSoftObjectPtr<>> ContextObjects;` — The objects for which the properties are being displayed. This usually has only 1 entry. This has multiple elements in the case of multi-edit (i.e. when the user clicks multiple, compatible actors in the top-view). For example, for multi-edit this could contain ActorA->StaticMeshComponent0 and ActorB->StaticMeshComponent0.
- L39 _private member_ `TSoftClassPtr<> OwningClassPtr;` — The class with which the FProperty can be determined.
- L47 _private member_ `FConcertPropertyChain Property;` — The property to be replicated. On the servers, this will usually not resolve to anything. This was promoted to be TSoftObjectPtr so that any UI that resolves this object path automatically caches it. In certain operations this can improve performance: e.g. when fully rebuilding the property tree, this saved 35% performance.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Replication/Editor/Model/Data/ReplicatedObjectData.h` (Public)


#### class `UE::ConcertSharedSlate::FReplicatedObjectData`  
`class FReplicatedObjectData`  
_L11-35_
- desc: Instanced for each object row in stream viewer / editor UI.
- L15 _public function_ `FReplicatedObjectData(FSoftObjectPath ObjectPath) : ObjectPtr(MoveTemp(ObjectPath))`
- L18 _public function_ `FReplicatedObjectData(TSoftObjectPtr<> Object) : ObjectPtr(MoveTemp(Object))`
- L22 _public function_ `const FSoftObjectPath& GetObjectPath() const`
- L23 _public function_ `const TSoftObjectPtr<>& GetObjectPtr() const`
- L34 _private member_ `TSoftObjectPtr<> ObjectPtr;` — The replicated object. On the servers, this will usually not resolve to anything. This was promoted to be TSoftObjectPtr so that any UI that resolves this object path automatically caches it. In certain operations this can improve performance: e.g. when fully rebuilding the property tree, this saved 35% performance.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Replication/Editor/Model/Extension/IStreamExtender.h` (Public)


#### class `UE::ConcertSharedSlate::IStreamExtender`  
`class IStreamExtender`  
_L15-29_
- desc: When an object is added to IEditableReplicationStreamModel, these functions are called to allow adding additional objects and properties.
- L26 _public prototype_ `virtual void ExtendStream(UObject& ExtendedObject, IStreamExtensionContext& Context) = 0;` — Allows extending the stream when objects are added. This function is called recursively for any additional objects you add. @param ExtendedObject Object that was added @param Context Use for adding properties to ExtendedObject or to additional objects.
- L28 _public prototype_ `virtual ~IStreamExtender() = default;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Replication/Editor/Model/Extension/IStreamExtensionContext.h` (Public)


#### class `UE::ConcertSharedSlate::IStreamExtensionContext`  
`class IStreamExtensionContext`  
_L13-36_
- desc: Allows IStreamExtender to add default replication settings like properties and adding additional objects.
- L24 _public prototype_ `virtual void AddPropertyTo(UObject& Object, FConcertPropertyChain PropertyChain) = 0;` — Extends the stream with the given object, if not yet added, and adds the property to it. If Object was not yet in the stream, IStreamExtender::ExtendStream will be called for Object. @param Object Object to add, if not yet present, and assign a property to @param PropertyChain Property chain to associate with the object
- L33 _public prototype_ `virtual void AddAdditionalObject(UObject& Object) = 0;` — Adds an additional object. If Object was not yet in the stream, IStreamExtender::ExtendStream will be called for Object. @param Object The additional object to add
- L35 _public prototype_ `virtual ~IStreamExtensionContext() = default;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Replication/Editor/Model/IEditableMultiReplicationStreamModel.h` (Public)


#### class `UE::ConcertSharedSlate::IEditableMultiReplicationStreamModel`  
`class IEditableMultiReplicationStreamModel : public IMultiReplicationStreamModel`  
_L23-57_
- inherits: `IMultiReplicationStreamModel`
- desc: Model for UI editing multiple streams at the same time. Some streams can be read but not edited: - the set of readable streams includes the set of editable streams, but - the number of editable streams can be less than or equal to the number of read-only streams.
- L33 _public prototype_ `virtual TSet<TSharedRef<IEditableReplicationStreamModel>> GetEditableStreams() const = 0;` — @return Gets the streams that can be written to. @note There may be streams that are readable but not editable. Formally, the constraint is GetReadableStreams().Includes(GetEditableStreams()) and GetEditableStreams().Num() <= GetReadOnlyStreams().Num().
- L36 _public function_ `void ForEachStream(TFunctionRef<EBreakBehavior(const TSharedRef<IReplicationStreamModel>& Model)> Callback) const` — Util for iterating through both read-only and editable streams.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Replication/Editor/Model/IEditableReplicationStreamModel.h` (Public)


#### enum `UE::ConcertSharedSlate::EReplicatedObjectChangeReason`  
`enum class EReplicatedObjectChangeReason : uint8`  
_L17-27_
- L20 _public enumerator_ `ChangedDirectly` — A function call on the model changed the data.
- L26 _public enumerator_ `ExternalChange` — An external change, such as transaction, changed the data out from under us. The AddedObjects and RemovedObjects fields are empty because we don't know exactly what changed, if anything.

#### class `UE::ConcertSharedSlate::IEditableReplicationStreamModel`  
`class IEditableReplicationStreamModel : public IReplicationStreamModel`  
_L35-59_
- inherits: `IReplicationStreamModel`
- desc: Abstracts the concept of mapping objects to properties. This allows writing. Models may not always be writable. When editing a UAsset, it will be writable. However, if we join a multi-user session we do not want to edit the objects nor properties - only read.
- L40 _public prototype_ `virtual void AddObjects(TConstArrayView<UObject*> Objects) = 0;` — Adds the objects to the mapping
- L42 _public prototype_ `virtual void RemoveObjects(TConstArrayView<FSoftObjectPath> Objects) = 0;` — Removes the objects from the mapping
- L45 _public prototype_ `virtual void AddProperties(const FSoftObjectPath& Object, TConstArrayView<FConcertPropertyChain> Properties) = 0;` — Adds these properties to the object's list of selected properties.
- L47 _public prototype_ `virtual void RemoveProperties(const FSoftObjectPath& Object, TConstArrayView<FConcertPropertyChain> Properties) = 0;` — Removes these properties from the object's list of selected properties.
- L50 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnObjectsChanged, TConstArrayView<UObject*> AddedObjects, TConstArrayView<FSoftObjectPath> RemovedObjects, EReplicatedObjectChangeReason ChangeReason);` — Called when the object list changes. AddedObjects and RemovedObjects are empty if and only if ChangeReason == EReplicatedObjectChangeReason::Transacted.
- L51 _public prototype_ `virtual FOnObjectsChanged& OnObjectsChanged() = 0;`
- L54 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnPropertiesChanged);` — Called when the property list of some object changes. If the properties are removed because the object is removed outright, FOnObjectsChanged is called instead.
- L55 _public prototype_ `virtual FOnPropertiesChanged& OnPropertiesChanged() = 0;`
- L58 _public function_ `void Clear()` — Clear all objects in the model

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L50 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnObjectsChanged, TConstArrayView<UObject*> AddedObjects, TConstArrayView<FSoftObjectPath> RemovedObjects, EReplicatedObjectChangeReason ChangeReason);` — Called when the object list changes. AddedObjects and RemovedObjects are empty if and only if ChangeReason == EReplicatedObjectChangeReason::Transacted.
- L54 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnPropertiesChanged);` — Called when the property list of some object changes. If the properties are removed because the object is removed outright, FOnObjectsChanged is called instead.

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Replication/Editor/Model/IMultiReplicationStreamModel.h` (Public)


#### class `UE::ConcertSharedSlate::IMultiReplicationStreamModel`  
`class IMultiReplicationStreamModel : public TSharedFromThis<IMultiReplicationStreamModel>`  
_L13-29_
- inherits: `TSharedFromThis<IMultiReplicationStreamModel>`
- desc: Model for UI displaying multiple streams at the same time.
- L18 _public prototype_ `virtual TSet<TSharedRef<IReplicationStreamModel>> GetReadOnlyStreams() const = 0;` — @return Streams in this model that can only be read from.
- L20 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnStreamExternallyChanged, TSharedRef<IReplicationStreamModel> );`
- L22 _public prototype_ `virtual FOnStreamExternallyChanged& OnStreamExternallyChanged() = 0;` — Called when a read-only stream has changed.
- L24 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnStreamSetChanged);`
- L26 _public prototype_ `virtual FOnStreamSetChanged& OnStreamSetChanged() = 0;` — Broadcasts when the result of GetStreams has changed.
- L28 _public prototype_ `virtual ~IMultiReplicationStreamModel() = default;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L20 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnStreamExternallyChanged, TSharedRef<IReplicationStreamModel> );`
- L24 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnStreamSetChanged);`

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Replication/Editor/Model/IReplicationStreamModel.h` (Public)


#### class `UE::ConcertSharedSlate::IReplicationStreamModel`  
`class IReplicationStreamModel : public TSharedFromThis<IReplicationStreamModel>`  
_L20-179_
- inherits: `TSharedFromThis<IReplicationStreamModel>`
- desc: Abstracts the concept of mapping objects to properties. This is a read-only interface. Objects are allowed to be bound to no properties. @see IEditableReplicationStreamModel
- L25 _public prototype_ `virtual FSoftClassPath GetObjectClass(const FSoftObjectPath& Object) const = 0;` — @return Gets the class of the replication object
- L28 _public prototype_ `virtual bool ContainsObjects(const TSet<FSoftObjectPath>& Objects) const = 0;` — @return Whether the objects are selected
- L30 _public prototype_ `virtual bool ContainsProperties(const FSoftObjectPath& Object, const TSet<FConcertPropertyChain>& Properties) const = 0;` — @return Whether the properties are selected
- L36 _public prototype_ `virtual bool ForEachReplicatedObject(TFunctionRef<EBreakBehavior(const FSoftObjectPath& Object)> Delegate) const = 0;` — Iterates all objects in the mapping. @return Whether there were any mapped objects
- L43 _public prototype_ `virtual bool ForEachProperty(const FSoftObjectPath& Object, TFunctionRef<EBreakBehavior(const FConcertPropertyChain& Property)> Delegate) const = 0;` — Iterates all the properties of the given object in the mapping. @param Object The object of which to get the properties @param Delegate The callback
- L46 _public prototype_ `virtual uint32 GetNumProperties(const FSoftObjectPath& Object) const = 0;` — Gets the number of properties assigned to Object.
- L49 _public function_ `TSet<FSoftObjectPath> GetReplicatedObjects() const` — @return Gets all replicated objects
- L69 _public function_ `bool ForEachDirectChildProperty(const FSoftObjectPath& Object, TFunctionRef<EBreakBehavior(const FConcertPropertyChain& Property)> Delegate, const FConcertPropertyChain& OptionalParent = {}) const` — Iterates all the direct child properties of a given property in the mapping. @param Object The object of which to get the properties @param Delegate The callback @param OptionalParent Defines of which properties to get the child properties. If the property chain is empty, gets the object's root properties. @return Whether any properties were mapped
- L84 _public function_ `bool HasProperty(const FSoftObjectPath& ObjectPath, const FConcertPropertyChain& SearchedProperty) const` — @return Whether the given SearchedProperty is assigned to ObjectPath.
- L96 _public function_ `bool HasAnyPropertyAssigned(const FSoftObjectPath& ObjectPath) const` — @return Whether there is at least one property assigned to ObjectPath.
- L108 _public function_ `TSet<FConcertPropertyChain> GetAllProperties(const FSoftObjectPath& Object) const` — Util for getting properties as array
- L127 _public function_ `TSet<FName> GetChildProperties(const FSoftObjectPath& Object, const FConcertPropertyChain& OptionalParent = {}) const` — Util for getting child properties as array
- L139 _public function_ `void ForEachSubobject(const FSoftObjectPath& Parent, TFunctionRef<EBreakBehavior(const FSoftObjectPath& Child)> Callback) const` — Iterates every subobject of Parent.
- L152 _public function_ `template<typename TAllocator = FDefaultAllocator> TArray<FSoftObjectPath, TAllocator> GetSubobjects(const FSoftObjectPath& Parent) const` — @return Gets the subobjects as an array
- L165 _public function_ `template<typename TLambda> requires std::is_invocable_r_v<bool, TLambda, const FSoftObjectPath&> bool AnyOfSubobjects(const FSoftObjectPath& Root, TLambda&& Lambda)` — @return Whether the predicate holds true for any of Root's subobjects.
- L178 _public prototype_ `virtual ~IReplicationStreamModel() = default;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L53 _function_ `` (scope `UE::ConcertSharedSlate::IReplicationStreamModel::GetReplicatedObjects`)
- L73 _function_ `` (scope `UE::ConcertSharedSlate::IReplicationStreamModel::ForEachDirectChildProperty`)
- L88 _function_ `` (scope `UE::ConcertSharedSlate::IReplicationStreamModel::HasProperty`)
- L100 _function_ `` (scope `UE::ConcertSharedSlate::IReplicationStreamModel::HasAnyPropertyAssigned`)
- L119 _function_ `` (scope `UE::ConcertSharedSlate::IReplicationStreamModel::GetAllProperties`)
- L131 _function_ `` (scope `UE::ConcertSharedSlate::IReplicationStreamModel::GetChildProperties`)
- L143 _function_ `` (scope `UE::ConcertSharedSlate::IReplicationStreamModel::ForEachSubobject`)
- L156 _function_ `` (scope `UE::ConcertSharedSlate::IReplicationStreamModel::GetSubobjects`)
- L171 _function_ `` (scope `UE::ConcertSharedSlate::IReplicationStreamModel::AnyOfSubobjects`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Replication/Editor/Model/Object/IObjectHierarchyModel.h` (Public)


#### enum `UE::ConcertSharedSlate::EChildRelationship`  
`enum class EChildRelationship : uint8`  
_L19-30_
- desc: Describes the kind of relationship a child object can have to its parent object
- L22 _public enumerator_ `Component` — The child is a child component
- L24 _public enumerator_ `Subobject` — The child is subobject but not a component
- L27 _public enumerator_ `Unknown` — The relationship is not further specified / unknown (for example in non-editor builds you may need to use this due to missing runtime info)

#### enum `UE::ConcertSharedSlate::EChildRelationshipFlags`  
`enum class EChildRelationshipFlags : uint8`  
_L33-46_
- desc: Similar to EChildRelationship. Used for filtering using bit flags.
- L35 _public enumerator_ `None = 0`
- L38 _public enumerator_ `Component = 1 << 0` — The child is a component of the parent.
- L40 _public enumerator_ `Subobject = 1 << 1` — The child is a subobject of the parent but no component.
- L43 _public enumerator_ `Unknown = 1 << 2` — The relationship is not further specified / unknown (for example in non-editor builds you may need to use this due to missing runtime info)
- L45 _public enumerator_ `All = Component | Subobject | Unknown`

#### class `UE::ConcertSharedSlate::IObjectHierarchyModel`  
`class IObjectHierarchyModel`  
_L56-111_
- desc: Determines the parent-child relationship between objects. The model can be given an object and it will list all child objects, usually subobjects or child components. In editor builds, an implementation could resolve object paths to AActors, USceneComponent, etc. In programs, an implementation could be to compare all known object path strings.
- L73 _public prototype_ `virtual void ForEachDirectChild( const TSoftObjectPtr<>& Root, TFunctionRef<EBreakBehavior(const TSoftObjectPtr<>& Object, EChildRelationship Relationship)> Callback, EChildRelationshipFlags InclusionFlags = EChildRelationshipFlags::All ) const = 0;` — Gets all direct children in the hierarchy. An example for what ForEachDirectChild could return in an editor build: - Actor returns its root component, non-scene components (UActorComponents), and all other direct subobjects - Scene components return their children, and all other direct subobjects - All other subobjects report all direct subobjects The hierarchy is implementation defined: the above is just an example for describing how ForEachDirectChild should operate. @param Root @param Callback @param InclusionFlags Specifies the relationships that should be included
- L87 _public prototype_ `virtual TOptional<FParentInfo> GetParentInfo(const TSoftObjectPtr<const UObject>& ChildObject) const = 0;` — Gets parent info for ChildObject, if it has a child.
- L90 _public prototype_ `void ForEachChildRecursive( const TSoftObjectPtr<>& Root, TFunctionRef<EBreakBehavior(const TSoftObjectPtr<>& Parent, const TSoftObjectPtr<>& ChildObject, EChildRelationship Relationship)> Callback, EChildRelationshipFlags InclusionFlags = EChildRelationshipFlags::All ) const;` — Util for iterating all subobjects.
- L98 _public function_ `template<typename TAllocator = FDefaultAllocator> TArray<TSoftObjectPtr<>, TAllocator> GetChildrenRecursive(const TSoftObjectPtr<>& Root, EChildRelationshipFlags InclusionFlags = EChildRelationshipFlags::All) const` — Builds a TArray containing all children, recursively.
- L110 _public prototype_ `virtual ~IObjectHierarchyModel() = default;`

#### struct `UE::ConcertSharedSlate::IObjectHierarchyModel::FParentInfo`  
`struct FParentInfo`  
_L79-85_
- L82 _public member_ `TSoftObjectPtr<const UObject> Parent;` — The parent of the child object in the hierarchy.
- L84 _public member_ `EChildRelationship Relationship;` — Relationship that the child has to Parent, e.g. the child could be a component of Parent.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API CONCERTSHAREDSLATE_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L47 _prototype_ `ENUM_CLASS_FLAGS(EChildRelationshipFlags);` (scope `UE::ConcertSharedSlate`)
- L103 _function_ `` (scope `UE::ConcertSharedSlate::IObjectHierarchyModel::GetChildrenRecursive`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Replication/Editor/Model/Object/IObjectNameModel.h` (Public)


#### class `UE::ConcertSharedSlate::IObjectNameModel`  
`class IObjectNameModel`  
_L19-29_
- desc: Abstracts the concept of getting an object's display name. In editor builds, this could use the USubobjectDataSubsystem to look up subobject names on an actor. In programs, it could just default to what it says in the object path.
- L24 _public prototype_ `virtual FText GetObjectDisplayName(const TSoftObjectPtr<>& ObjectPath) const = 0;` — @return Gets the display name for an object
- L28 _public prototype_ `virtual ~IObjectNameModel() = default;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Replication/Editor/Model/ObjectSource/IObjectSelectionSourceModel.h` (Public)


#### enum `UE::ConcertSharedSlate::EObjectItemValidity`  
`enum class EObjectItemValidity : uint8`  
_L14-22_
- L17 _public enumerator_ `Valid` — The item is allowed
- L19 _public enumerator_ `DoesNotExist` — The referenced object no longer exists. E.g. the actor was removed.
- L21 _public enumerator_ `Invalid` — Any other reason, e.g. the object was allowed in a previous version but no longer is allowed now.

#### class `UE::ConcertSharedSlate::IObjectSelectionSourceModel`  
`class IObjectSelectionSourceModel : public TSharedFromThis<IObjectSelectionSourceModel>`  
_L25-36_
- inherits: `TSharedFromThis<IObjectSelectionSourceModel>`
- desc: Decides which objects can be added to a IEditableReplicationStreamModel.
- L30 _public prototype_ `virtual TArray<FObjectSourceCategory> GetRootSources() const = 0;` — Gets the "root set" of sources. Each one should be a button next to the search bar, e.g. "Add actor".
- L33 _public prototype_ `virtual TArray<TSharedRef<IObjectSourceModel>> GetContextMenuOptions(const FSoftObjectPath& Items) = 0;` — @return The sources that should be displayed in the right-click context menu when clicked in the menu.
- L35 _public prototype_ `virtual ~IObjectSelectionSourceModel() = default;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L12 _typedef_ `using FObjectSourceCategory = ConcertSharedSlate::TSourceSelectionCategory<FSelectableObjectInfo>;` (scope `UE::ConcertSharedSlate`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Replication/Editor/Model/ObjectSource/IObjectSourceModel.h` (Public)


#### struct `UE::ConcertSharedSlate::FSelectableObjectInfo`  
`struct FSelectableObjectInfo`  
_L14-19_
- desc: Info about a selectable object
- L16 _public function_ `FSelectableObjectInfo(UObject& Object) : Object(&Object)`
- L18 _public member_ `TWeakObjectPtr<UObject> Object;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L25 _typedef_ `using IObjectSourceModel = ConcertSharedSlate::IItemSourceModel<FSelectableObjectInfo>;` (scope `UE::ConcertSharedSlate`) — A specific object source, e.g. like actors, components from an actor (right-click), etc. @see IObjectSelectionSourceModel.

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Replication/Editor/Model/Property/IPropertySelectionSourceModel.h` (Public)


#### class `UE::ConcertSharedSlate::PRAGMA_DISABLE_DEPRECATION_WARNINGS`  
`PRAGMA_DISABLE_DEPRECATION_WARNINGS : public TSharedFromThis<IPropertySelectionSourceModel> PRAGMA_ENABLE_DEPRECATION_WARNINGS`  
_L22-34_
- reflection: `UE_DEPRECATED(5.5, "Use IPropertySourceProcessor instead.")`
- inherits: `TSharedFromThis<IPropertySelectionSourceModel>PRAGMA_ENABLE_DEPRECATION_WARNINGS`
- desc: Decides which properties can be added to a IReplicationStreamModel.
- L30 _public prototype_ `virtual TSharedRef<IPropertySourceModel> GetPropertySource(const FSoftClassPath& Class) const = 0;` — Gets the single source determining which properties can be selected.
- L33 _public prototype_ `virtual ~IPropertySelectionSourceModel() = default;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L15 _typedef_ `using FPropertySourceCategory UE_DEPRECATED(5.5, "No longer in use.") = PRAGMA_DISABLE_DEPRECATION_WARNINGS ConcertSharedSlate::TSourceSelectionCategory<FSelectablePropertyInfo>;` (scope `UE::ConcertSharedSlate`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Replication/Editor/Model/Property/IPropertySource.h` (Public)


#### struct `UE::ConcertSharedSlate::FPropertyInfo`  
`struct FPropertyInfo`  
_L16-20_
- desc: Wraps FConcertPropertyChain so it is easier to potentially change what IPropertySource lists in the future.
- L18 _public member_ `const FConcertPropertyChain& Property;`
- L19 _public function_ `explicit FPropertyInfo(const FConcertPropertyChain& Property) : Property(Property)`

#### class `UE::ConcertSharedSlate::IPropertySource`  
`class IPropertySource`  
_L23-31_
- desc: Lists out a bunch of properties.
- L28 _public prototype_ `virtual void EnumerateProperties(TFunctionRef<EBreakBehavior(const FPropertyInfo& Property)> Delegate) const = 0;` — Lists a bunch of properties.
- L30 _public prototype_ `virtual ~IPropertySource() = default;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Replication/Editor/Model/Property/IPropertySourceModel.h` (Public)


#### struct `UE::ConcertSharedSlate::FSelectablePropertyInfo`  
`struct UE_DEPRECATED(5.5, "No longer in use.") FSelectablePropertyInfo`  
_L13-16_
- desc: Info about a selectable property
- L15 _public member_ `FConcertPropertyChain Property;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L22 _typedef_ `using IPropertySourceModel UE_DEPRECATED(5.5, "No longer in use.") = PRAGMA_DISABLE_DEPRECATION_WARNINGS ConcertSharedSlate::IItemSourceModel<FSelectablePropertyInfo>;` (scope `UE::ConcertSharedSlate`) — A specific object source, e.g. like actors, components from an actor (right-click), etc. @see IPropertySelectionProcessor.

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Replication/Editor/Model/Property/IPropertySourceProcessor.h` (Public)


#### struct `UE::ConcertSharedSlate::FPropertySourceContext`  
`struct FPropertySourceContext`  
_L14-25_
- desc: Arguments for getting properties associated with an object / class.
- L17 _public member_ `TSoftObjectPtr<> Object;` — The object for which the properties are supposed to be displayed
- L19 _public member_ `FSoftClassPath Class;` — The class of Object
- L21 _public function_ `FPropertySourceContext(const TSoftObjectPtr<>& Object, const FSoftClassPath& Class) : Object(Object) , Class(Class)`

#### class `UE::ConcertSharedSlate::IPropertySourceProcessor`  
`class IPropertySourceProcessor`  
_L33-41_
- desc: Determines the properties that should be displayed for an Object / Class. The most simple implementation is to iterate the UClass properties but there can be more advanced implementations, such as only returning properties from a user defined list.
- L38 _public prototype_ `virtual void ProcessPropertySource(const FPropertySourceContext& Context, TFunctionRef<void(const IPropertySource& Model)> Processor) const = 0;` — Allows you to get the properties that are associated with the passed in object / class context. You are not allowed to keep a reference to Processor.
- L40 _public prototype_ `virtual ~IPropertySourceProcessor() = default;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Replication/Editor/Model/Util/EditableStreamModelProxy.h` (Public)


#### class `UE::ConcertSharedSlate::FEditableStreamModelProxy`  
`class FEditableStreamModelProxy : public IEditableReplicationStreamModel`  
_L13-47_
- inherits: `IEditableReplicationStreamModel`
- desc: Base util class for implementations that alter or extend the behavior of another IEditableReplicationStreamModel. This pattern allows chaining of behaviors.
- L17 _public function_ `FEditableStreamModelProxy(const TSharedRef<IEditableReplicationStreamModel>& InModel) : WrappedModel(InModel)`
- L22 _public function_ `virtual FSoftClassPath GetObjectClass(const FSoftObjectPath& Object) const override`
- L23 _public function_ `virtual bool ContainsObjects(const TSet<FSoftObjectPath>& Objects) const override`
- L24 _public function_ `virtual bool ContainsProperties(const FSoftObjectPath& Object, const TSet<FConcertPropertyChain>& Properties) const override`
- L25 _public function_ `virtual bool ForEachReplicatedObject(TFunctionRef<EBreakBehavior(const FSoftObjectPath& Object)> Delegate) const override`
- L26 _public function_ `virtual bool ForEachProperty(const FSoftObjectPath& Object, TFunctionRef<EBreakBehavior(const FConcertPropertyChain& Property)> Delegate) const override`
- L27 _public function_ `virtual uint32 GetNumProperties(const FSoftObjectPath& Object) const override`
- L28 _public function_ `virtual FOnObjectsChanged& OnObjectsChanged() override`
- L29 _public function_ `virtual FOnPropertiesChanged& OnPropertiesChanged() override`
- L33 _public function_ `virtual void AddObjects(TConstArrayView<UObject*> Objects) override`
- L34 _public function_ `virtual void RemoveObjects(TConstArrayView<FSoftObjectPath> Objects) override`
- L35 _public function_ `virtual void AddProperties(const FSoftObjectPath& Object, TConstArrayView<FConcertPropertyChain> Properties) override`
- L36 _public function_ `virtual void RemoveProperties(const FSoftObjectPath& Object, TConstArrayView<FConcertPropertyChain> Properties) override`
- L41 _protected function_ `const TSharedRef<IEditableReplicationStreamModel>& GetWrappedModel() const`
- L46 _private member_ `TSharedRef<IEditableReplicationStreamModel> WrappedModel;` — The model to be transacted

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Replication/Editor/View/Column/IObjectTreeColumn.h` (Public)


#### struct `UE::ConcertSharedSlate::FObjectTreeRowContext`  
`struct FObjectTreeRowContext`  
_L12-16_
- desc: Holds information relevant to a row.
- L15 _public member_ `FReplicatedObjectData RowData;` — The data that is stored in the row

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L18 _typedef_ `using IObjectTreeColumn = IReplicationTreeColumn<FObjectTreeRowContext>;` (scope `UE::ConcertSharedSlate`)
- L19 _typedef_ `using FObjectColumnEntry = TReplicationColumnEntry<FObjectTreeRowContext>;` (scope `UE::ConcertSharedSlate`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Replication/Editor/View/Column/IPropertyTreeColumn.h` (Public)


#### struct `UE::ConcertSharedSlate::FPropertyTreeRowContext`  
`struct FPropertyTreeRowContext`  
_L12-16_
- desc: Holds information relevant to a row.
- L15 _public member_ `FPropertyData RowData;` — The data that is stored in the row

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L18 _typedef_ `using IPropertyTreeColumn = IReplicationTreeColumn<FPropertyTreeRowContext>;` (scope `UE::ConcertSharedSlate`)
- L19 _typedef_ `using FPropertyColumnEntry = TReplicationColumnEntry<FPropertyTreeRowContext>;` (scope `UE::ConcertSharedSlate`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Replication/Editor/View/Column/IReplicationTreeColumn.h` (Public)


#### class `UE::ConcertSharedSlate::IReplicationTreeColumn`  
`template<typename TTreeItemType> class IReplicationTreeColumn`  
_L15-34_
- L25 _public prototype_ `virtual SHeaderRow::FColumn::FArguments CreateHeaderRowArgs() const = 0;`
- L27 _public prototype_ `virtual TSharedRef<SWidget> GenerateColumnWidget(const FBuildArgs& InArgs) = 0;`
- L28 _public function_ `virtual void PopulateSearchString(const TTreeItemType& InItem, TArray<FString>& InOutSearchStrings) const`
- L30 _public function_ `virtual bool CanBeSorted() const`
- L31 _public function_ `virtual bool IsLessThan(const TTreeItemType& Left, const TTreeItemType& Right) const`
- L33 _public prototype_ `virtual ~IReplicationTreeColumn() = default;`

#### struct `UE::ConcertSharedSlate::IReplicationTreeColumn::FBuildArgs`  
`struct FBuildArgs`  
_L19-23_
- L21 _public member_ `TSharedPtr<FText> HighlightText;`
- L22 _public member_ `const TTreeItemType& RowItem;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Replication/Editor/View/Column/ReplicationColumnDelegates.h` (Public)


#### struct `UE::ConcertSharedSlate::TReplicationColumnDelegates`  
`template<typename TTreeItemType> struct TReplicationColumnDelegates`  
_L10-13_
- L12 _public prototype_ `DECLARE_DELEGATE_RetVal(TSharedRef<IReplicationTreeColumn<TTreeItemType>>, FCreateColumn);`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L12 _delegate_ `DECLARE_DELEGATE_RetVal(TSharedRef<IReplicationTreeColumn<TTreeItemType>>, FCreateColumn);`

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Replication/Editor/View/Column/ReplicationColumnInfo.h` (Public)


#### struct `UE::ConcertSharedSlate::FReplicationColumnInfo`  
`struct FReplicationColumnInfo`  
_L15-19_
- desc: Meta information about a column that can change independent of the IReplicationTreeColumn implementation. For example, IReplicationTreeColumn does not need to know about sort order.
- L18 _public member_ `int32 SortOrder = 0;` — Determines whether this column is the first, etc.

#### struct `UE::ConcertSharedSlate::TReplicationColumnEntry`  
`template<typename TTreeItemType> struct TReplicationColumnEntry`  
_L22-30_
- L25 _public member_ `typename TReplicationColumnDelegates<TTreeItemType>::FCreateColumn CreateColumn;` — Factory function for creating the column instance.
- L27 _public member_ `FName ColumnId;` — The ID of the created column. Must be equal to what IReplicationTreeColumn::CreateHeaderRowArgs would return.
- L29 _public member_ `FReplicationColumnInfo ColumnInfo;` — Additional info about the column that is not directly controlled by IReplicationTreeColumn.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Replication/Editor/View/Column/ReplicationColumnsUtils.h` (Public)


#### struct `UE::ConcertSharedSlate::FColumnSortInfo`  
`struct FColumnSortInfo`  
_L23-29_
- desc: Info about a column that is being sorted.
- L25 _public member_ `FName SortedColumnId;`
- L26 _public member_ `EColumnSortMode::Type SortMode = EColumnSortMode::None;`
- L28 _public function_ `bool IsValid() const`

#### struct `UE::ConcertSharedSlate::TCheckboxColumnDelegates`  
`template<typename TListItemType> struct TCheckboxColumnDelegates`  
_L32-70_
- L34 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(ECheckBoxState, FGetColumnCheckboxState, const TListItemType& );`
- L35 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnColumnCheckboxChanged, bool , const TListItemType& );`
- L36 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsEnabled, const TListItemType& );`
- L37 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FGetToolTipText, const TListItemType& );`
- L39 _public function_ `TCheckboxColumnDelegates( FGetColumnCheckboxState InGetCheckboxStateDelegate, FOnColumnCheckboxChanged InOnCheckboxChangedDelegate, FGetToolTipText InGetToolTipTextDelegate = {}, FIsEnabled InIsEnabledDelegate = {} ) : GetCheckboxStateDelegate(MoveTemp(InGetCheckboxStateDelegate)) , OnCheckboxChangedDelegate(MoveTemp(InOnCheckboxChangedDelegate)) , GetToolTipTextDelegate(MoveTemp(InGetToolTipTextDelegate)) , IsEnabledDelegate(MoveTemp(InIsEnabledDelegate))`
- L51 _public function_ `TCheckboxColumnDelegates( FGetColumnCheckboxState InGetCheckboxStateDelegate, FOnColumnCheckboxChanged InOnCheckboxChangedDelegate, TAttribute<FText> InToolTipTextAttribute, FIsEnabled InIsEnabledDelegate = {} ) : GetCheckboxStateDelegate(MoveTemp(InGetCheckboxStateDelegate)) , OnCheckboxChangedDelegate(MoveTemp(InOnCheckboxChangedDelegate)) , GetToolTipTextDelegate(FGetToolTipText::CreateLambda([GetToolTipText = MoveTemp(InToolTipTextAttribute)](const TListItemType&){ return GetToolTipText.Get(); })) , IsEnabledDelegate(MoveTemp(InIsEnabledDelegate))`
- L59 _public function_ `, GetToolTipTextDelegate(FGetToolTipText::CreateLambda([GetToolTipText = MoveTemp(InToolTipTextAttribute)](const TListItemType&){ return GetToolTipText.Get(); })) , IsEnabledDelegate(MoveTemp(InIsEnabledDelegate))`
- L63 _public member_ `FGetColumnCheckboxState GetCheckboxStateDelegate;`
- L64 _public member_ `FOnColumnCheckboxChanged OnCheckboxChangedDelegate;`
- L67 _public member_ `FGetToolTipText GetToolTipTextDelegate;` — Optional. Defaults to FText::GetEmpty()
- L69 _public member_ `FIsEnabled IsEnabledDelegate;` — Optional. Default to true.

#### class `UE::ConcertSharedSlate::MakeCheckboxColumn::TCheckboxColumn`  
`class TCheckboxColumn : public UE::ConcertSharedSlate::template IReplicationTreeColumn<TListItemType>`  
_L82-143_
- inherits: `UE::ConcertSharedSlate::templateIReplicationTreeColumn<TListItemType>`
- L86 _public function_ `TCheckboxColumn( FName ColumnId, FText DefaultLabel, const float ColumnWidth, TCheckboxColumnDelegates<TListItemType> Delegates ) : ColumnId(ColumnId) , DefaultLabel(MoveTemp(DefaultLabel)) , ColumnWidth(ColumnWidth) , Delegates(MoveTemp(Delegates))`
- L98 _public function_ `virtual SHeaderRow::FColumn::FArguments CreateHeaderRowArgs() const override`
- L104 _public function_ `virtual TSharedRef<SWidget> GenerateColumnWidget(const typename IReplicationTreeColumn<TListItemType>::FBuildArgs& InArgs) override`
- L126 _public function_ `virtual void PopulateSearchString(const TListItemType& InItem, TArray<FString>& InOutSearchStrings) const override`
- L128 _public function_ `virtual bool CanBeSorted() const override`
- L129 _public function_ `virtual bool IsLessThan(const TListItemType& Left, const TListItemType& Right) const override`
- L139 _private member_ `const FName ColumnId;`
- L140 _private member_ `const FText DefaultLabel;`
- L141 _private member_ `const float ColumnWidth;`
- L142 _private member_ `const TCheckboxColumnDelegates<TListItemType> Delegates;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L34 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(ECheckBoxState, FGetColumnCheckboxState, const TListItemType& );`
- L35 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnColumnCheckboxChanged, bool , const TListItemType& );`
- L36 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsEnabled, const TListItemType& );`
- L37 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FGetToolTipText, const TListItemType& );`
- L74 _function_ `template<typename TListItemType> UE::ConcertSharedSlate::template TReplicationColumnEntry<TListItemType> MakeCheckboxColumn( FName ColumnId, TCheckboxColumnDelegates<TListItemType> Delegates, FText DefaultLabel, const int32 Priority, const float ColumnWidth = 20.f )` (scope `UE::ConcertSharedSlate`) — Util for making a checkbox column
- L108 _function_ `` (scope `UE::ConcertSharedSlate::MakeCheckboxColumn::TCheckboxColumn::GenerateColumnWidget`)
- L149 _function_ `` (scope `UE::ConcertSharedSlate::MakeCheckboxColumn`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Replication/Editor/View/Column/SelectionViewerColumns.h` (Public)


#### enum `UE::ConcertSharedSlate::ReplicationColumns::TopLevel::ETopLevelColumnOrder`  
`enum class ETopLevelColumnOrder : int32`  
_L30-38_
- L33 _public enumerator_ `Label = 20` — Label of the object
- L35 _public enumerator_ `Type = 30` — Class of the object
- L37 _public enumerator_ `NumProperties = 40` — Displays the number of properties assigned to the object

#### enum `UE::ConcertSharedSlate::ReplicationColumns::TopLevel::ENumPropertiesFlags`  
`enum class ENumPropertiesFlags : uint8`  
_L40-45_
- L42 _public enumerator_ `None`
- L44 _public enumerator_ `IncludeSubobjectCounts` — Also add up the number of properties that child objects have assigned.

#### enum `UE::ConcertSharedSlate::ReplicationColumns::Property::EReplicationPropertyColumnOrder`  
`enum class EReplicationPropertyColumnOrder : int32`  
_L64-70_
- L67 _public enumerator_ `Label = 10` — Label of the property
- L69 _public enumerator_ `Type = 20` — Type of the property

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L24 _namespace_ `namespace ReplicationColumns` (scope `UE::ConcertSharedSlate`)
- L24 _namespace_ `namespace TopLevel` (scope `UE::ConcertSharedSlate::ReplicationColumns`)
- L26 _externvar_ `extern const FName LabelColumnId;` (scope `UE::ConcertSharedSlate::ReplicationColumns::TopLevel`)
- L27 _externvar_ `extern const FName TypeColumnId;` (scope `UE::ConcertSharedSlate::ReplicationColumns::TopLevel`)
- L28 _externvar_ `extern const FName NumPropertiesColumnId;` (scope `UE::ConcertSharedSlate::ReplicationColumns::TopLevel`)
- L46 _prototype_ `ENUM_CLASS_FLAGS(ENumPropertiesFlags);` (scope `UE::ConcertSharedSlate::ReplicationColumns::TopLevel`)
- L52 _prototype_ `FObjectColumnEntry LabelColumn(IObjectNameModel* OptionalNameModel = nullptr, FGetObjectClass GetObjectClassDelegate = {});` (scope `UE::ConcertSharedSlate::ReplicationColumns::TopLevel`) — @param OptionalNameModel Used to look object name. Defaults to name displayed in object path if unset. @param GetObjectClassDelegate Used to display class icon. No icon is displayed if unset.
- L54 _prototype_ `FObjectColumnEntry TypeColumn(FGetObjectClass GetObjectClassDelegate);` (scope `UE::ConcertSharedSlate::ReplicationColumns::TopLevel`) — Shows the object's type.
- L56 _prototype_ `FObjectColumnEntry NumPropertiesColumn(const IReplicationStreamModel& Model UE_LIFETIMEBOUND, ENumPropertiesFlags Flags = ENumPropertiesFlags::IncludeSubobjectCounts);` (scope `UE::ConcertSharedSlate::ReplicationColumns::TopLevel`) — Shows the number of widgets assigned to the object.
- L59 _namespace_ `namespace UE`
- L59 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L59 _namespace_ `namespace ReplicationColumns` (scope `UE::ConcertSharedSlate`)
- L59 _namespace_ `namespace Property` (scope `UE::ConcertSharedSlate::ReplicationColumns`)
- L61 _externvar_ `extern const FName LabelColumnId;` (scope `UE::ConcertSharedSlate::ReplicationColumns::Property`)
- L62 _externvar_ `extern const FName TypeColumnId;` (scope `UE::ConcertSharedSlate::ReplicationColumns::Property`)
- L72 _prototype_ `FPropertyColumnEntry LabelColumn();` (scope `UE::ConcertSharedSlate::ReplicationColumns::Property`)
- L73 _prototype_ `FPropertyColumnEntry TypeColumn();` (scope `UE::ConcertSharedSlate::ReplicationColumns::Property`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Replication/Editor/View/Extension/CategoryRowGeneration.h` (Public)


#### struct `UE::ConcertSharedSlate::FCategoryRowGenerationArgs`  
`struct FCategoryRowGenerationArgs`  
_L19-30_
- L22 _public member_ `TArray<TSoftObjectPtr<>> ContextObjects;` — The objects for which this is being generated
- L24 _public member_ `TAttribute<FText> HighlightText;` — The highlight text which contains the search terms
- L26 _public function_ `FCategoryRowGenerationArgs(TArray<TSoftObjectPtr<>> ContextObjects, TAttribute<FText> HighlightText) : ContextObjects(MoveTemp(ContextObjects)) , HighlightText(MoveTemp(HighlightText))`

#### class `UE::ConcertSharedSlate::ICategoryRow`  
`class ICategoryRow`  
_L33-44_
- desc: A special reassignment view which shows the display object and all its children.
- L38 _public prototype_ `virtual void GenerateSearchTerms(const TArray<TSoftObjectPtr<>>& ContextObjects, TArray<FString>& InOutSearchTerms) const = 0;` — Generates search terms
- L41 _public prototype_ `virtual TSharedRef<SWidget> GetWidget() = 0;` — Gets the row as widget
- L43 _public prototype_ `virtual ~ICategoryRow() = default;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L46 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<ICategoryRow>, FCreateCategoryRow, const FCategoryRowGenerationArgs& Args);`
- L46 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<ICategoryRow>, FCreateCategoryRow, const FCategoryRowGenerationArgs& Args);` (scope `UE::ConcertSharedSlate`)
- L49 _prototype_ `FCreateCategoryRow CreateDefaultCategoryGenerator(TSharedRef<IObjectNameModel> NameModel);` (scope `UE::ConcertSharedSlate`) — Creates a delegate that generates a row displaying the name of the first context object.

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Replication/Editor/View/IMultiObjectPropertyAssignmentView.h` (Public)


#### class `UE::ConcertSharedSlate::IMultiObjectPropertyAssignmentView`  
`class IMultiObjectPropertyAssignmentView : public IPropertyAssignmentView`  
_L10-18_
- inherits: `IPropertyAssignmentView`
- desc: A special reassignment view which shows the display object and all its children.
- L15 _public prototype_ `virtual void SetShouldShowSubobjects(bool bShowSubobjects) = 0;` — Sets whether subobjects should be shown in the view (applies only to subobjects other than UActorComponents, which are always shown).
- L17 _public prototype_ `virtual bool GetShouldShowSubobjects() const = 0;` — @return Whether subobjects should be shown

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Replication/Editor/View/IMultiReplicationStreamEditor.h` (Public)


#### class `UE::ConcertSharedSlate::IMultiReplicationStreamEditor`  
`class IMultiReplicationStreamEditor : public SCompoundWidget`  
_L18-30_
- inherits: `SCompoundWidget`
- desc: Widget which edits multiple replication stream. @see ReplicationWidgetFactories.h
- L23 _public prototype_ `virtual IReplicationStreamEditor& GetEditorBase() const = 0;` — @return The widget drawing the consolidated model.
- L26 _public prototype_ `virtual IEditableMultiReplicationStreamModel& GetMultiStreamModel() const = 0;` — @return The source of the sub-streams
- L29 _public prototype_ `virtual IEditableReplicationStreamModel& GetConsolidatedModel() const = 0;` — @return Gets a model that combines all streams into one.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Replication/Editor/View/IPropertyAssignmentView.h` (Public)


#### struct `UE::ConcertSharedSlate::FObjectGroup`  
`struct FObjectGroup`  
_L25-28_
- desc: An object group is a bunch of related objects. This relates to multi-editing. Example: You click 2 ACineCameraActor in the IReplicationStreamViewer: - A group is the 2 actors you clicked - A group is the two cine camera components of the actor
- L27 _public member_ `TArray<TSoftObjectPtr<>> Group;`

#### class `UE::ConcertSharedSlate::IPropertyAssignmentView`  
`class IPropertyAssignmentView`  
_L43-75_
- desc: A replication assignment view displays an object's properties. It is the piece of UI that is displayed on the bottom part of the replication viewer. The replication stream viewer / editor looks like this (@see CreateBaseStreamEditor): - Object tree view: User can click on an object. - IPropertyAssignmentView: The clicked object's properties are displayed (the "root objects"). Right now there are 2 implementation: - SPerObjectPropertyAssignment, which displays the root object's properties only - SMultiObjectAssignment, which displays the root object and its subobjects. Generally, you can imagine the view as a tree view which has columns that can be injected (e.g. @see CreateBaseStreamEditor).
- L53 _public prototype_ `virtual void RefreshData(const TArray<TSoftObjectPtr<>>& Objects, const IReplicationStreamModel& Model) = 0;` — Rebuilds all displayed data immediately. @param Objects The objects that are supposed to be displayed. @param Model The model that can be queried for object info.
- L56 _public prototype_ `virtual void RequestRefilter() const = 0;` — Reapply the filter function to all items at the end of the frame. Call e.g. when the filters have changed.
- L62 _public prototype_ `virtual void RequestResortForColumn(const FName& ColumnId) = 0;` — Requests that the given column be resorted, if it currently affects the row sorting (primary or secondary). Call e.g. when a sortable attribute of the column has changed.
- L65 _public prototype_ `virtual TSharedRef<SWidget> GetWidget() = 0;` — Gets the tree view's widget
- L68 _public prototype_ `virtual TArray<FObjectGroup> GetDisplayedGroups() const = 0;` — @return The groups of objects being displayed in this view right now.
- L70 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnSelectionChanged);`
- L72 _public prototype_ `virtual FOnSelectionChanged& OnObjectGroupsChanged() = 0;` — @return Event that broadcasts when the result of GetDisplayedGroups() has changed.
- L74 _public prototype_ `virtual ~IPropertyAssignmentView() = default;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L70 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnSelectionChanged);`

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Replication/Editor/View/IPropertyTreeView.h` (Public)


#### struct `UE::ConcertSharedSlate::FPropertyAssignmentEntry`  
`struct FPropertyAssignmentEntry`  
_L16-31_
- L25 _public member_ `TArray<TSoftObjectPtr<>> ContextObjects;` — The objects for which the properties are being displayed. This usually has only 1 entry. This has multiple elements in the case of multi-edit (i.e. when the user clicks multiple, compatible actors in the top-view). For example, for multi-edit this could contain ActorA->StaticMeshComponent0 and ActorB->StaticMeshComponent0.
- L28 _public member_ `TSet<FConcertPropertyChain> PropertiesToDisplay;` — The properties to display
- L30 _public member_ `FSoftClassPath Class;` — The class of the properties

#### class `UE::ConcertSharedSlate::IPropertyTreeView`  
`class IPropertyTreeView`  
_L34-76_
- desc: Represents a tree view displaying properties from a single class.
- L48 _public function_ `void RefreshPropertyData(const TSet<FConcertPropertyChain>& PropertiesToDisplay, const FSoftClassPath& Class, bool bCanReuseExistingRowItems = true)` — `UE_DEPRECATED(5.5, "Use the version that takes FPropertyAssignmentEntry instead")` — Rebuilds all property data from the property source. @param PropertiesToDisplay The properties to display @param Class The class from which the PropertiesToDisplay come @param bCanReuseExistingRowItems True, will try to reuse rows for properties in the tree already (retains selected rows). Set this to false, if all rows should be regenerated (clears selection). In general, always set this to false if you've changed the object for which you're displaying the class.
- L58 _public prototype_ `virtual void RefreshPropertyData(const TArray<FPropertyAssignmentEntry>& Entries, bool bCanReuseExistingRowItems = true) = 0;` — Rebuilds all property data from the property source. @param Entries Defines the property content to display @param bCanReuseExistingRowItems True, will try to reuse rows for properties in the tree already (retains selected rows). Set this to false, if all rows should be regenerated (clears selection). In general, always set this to false if you've changed the object for which you're displaying the class.
- L61 _public prototype_ `virtual void RequestRefilter() const = 0;` — Reapply the filter function to all items at the end of the frame. Call e.g. when the filters have changed.
- L67 _public prototype_ `virtual void RequestResortForColumn(const FName& ColumnId) = 0;` — Requests that the given column be resorted, if it currently affects the row sorting (primary or secondary). Call e.g. when a sortable attribute of the column has changed.
- L70 _public prototype_ `virtual void RequestScrollIntoView(const FConcertPropertyChain& PropertyChain) = 0;` — Scroll the given property into view, if it is contained.
- L73 _public prototype_ `virtual TSharedRef<SWidget> GetWidget() = 0;` — Gets the tree view's widget
- L75 _public prototype_ `virtual ~IPropertyTreeView() = default;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Replication/Editor/View/IReplicationStreamEditor.h` (Public)


#### class `UE::ConcertSharedSlate::IReplicationStreamEditor`  
`class IReplicationStreamEditor : public IReplicationStreamViewer`  
_L14-15_
- inherits: `IReplicationStreamViewer`
- desc: Widget which edits replication stream. @see ReplicationWidgetFactories.h

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Replication/Editor/View/IReplicationStreamViewer.h` (Public)


#### class `UE::ConcertSharedSlate::IReplicationStreamViewer`  
`class IReplicationStreamViewer : public SCompoundWidget`  
_L16-44_
- inherits: `SCompoundWidget`
- desc: Widget which views a replication stream. @see ReplicationWidgetFactories.h
- L21 _public prototype_ `virtual void Refresh() = 0;` — Call after the data underlying the model was externally changed and needs to be redisplayed in the UI.
- L27 _public prototype_ `virtual void RequestObjectColumnResort(const FName& ColumnId) = 0;` — Requests that column be resorted; the column is in the top object view. This is to be called in response to a column's content changing. The rows will be resorted if the given column has a sort priority assigned.
- L32 _public prototype_ `virtual void RequestPropertyColumnResort(const FName& ColumnId) = 0;` — Requests that column be resorted; the column is in the bottom property view. This is to be called in response to a column's content changing. The rows will be resorted if the given column has a sort priority assigned.
- L36 _public prototype_ `virtual TArray<FSoftObjectPath> GetObjectsBeingPropertyEdited() const;` — `UE_DEPRECATED(5.5, "Use GetSelectedObjects instead.")` — @return The objects for which the properties are being edited / displayed.
- L39 _public prototype_ `virtual void SetSelectedObjects(TConstArrayView<TSoftObjectPtr<>> Objects) = 0;` — Selects the objects in the outliner and deselects all others. Only actors can be selected. Invalid entries are filtered out.
- L41 _public prototype_ `virtual TArray<TSoftObjectPtr<>> GetSelectedObjects() const = 0;` — @return The objects for which the properties are being edited / displayed.
- L43 _public prototype_ `virtual ~IReplicationStreamViewer() = default;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CONCERTSHAREDSLATE_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Replication/PropertyAssignmentViewFactory.h` (Public)


#### struct `UE::ConcertSharedSlate::FCreatePerObjectAssignmentViewParams`  
`struct FCreatePerObjectAssignmentViewParams`  
_L24-35_
- L27 _public member_ `TSharedRef<IPropertyTreeView> PropertyTreeView = CreateSearchablePropertyTreeView();` — Required. Displays the properties in a tree view. You can pass in e.g. custom UI with advanced filtering.
- L34 _public member_ `TSharedPtr<IPropertySourceProcessor> PropertySource;` — Optional. If specified, the view will display all properties reported by the model (useful for editor UI which edits streams, not useful for server where property info is not available). If unspecified, only display the properties assigned to the object in the stream.

#### struct `UE::ConcertSharedSlate::FCreateMultiObjectAssignmentViewParams`  
`struct FCreateMultiObjectAssignmentViewParams : FCreatePerObjectAssignmentViewParams`  
_L45-63_
- inherits: `FCreatePerObjectAssignmentViewParams`
- L48 _public member_ `TSharedRef<IPropertyTreeView> PropertyTreeView = CreateSearchablePropertyTreeView();` — Required. Displays the properties in a tree view. You can pass in e.g. custom UI with advanced filtering.
- L55 _public member_ `TSharedPtr<IObjectHierarchyModel> ObjectHierarchy;` — Optional. Gets components and subobjects of the displayed object. If this is unspecified, the created IMultiObjectPropertyAssignmentView will behave exactly as the per object view (IPropertyAssignmentView).
- L62 _public member_ `TSharedPtr<IPropertySourceProcessor> PropertySource;` — Optional. If specified, the view will display all properties reported by the model (useful for editor UI which edits streams, not useful for server where property info is not available). If unspecified, only display the properties assigned to the object in the stream.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L22 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(EFilterResult, FFilterPropertyData, const FPropertyData&);`
- L22 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(EFilterResult, FFilterPropertyData, const FPropertyData&);` (scope `UE::ConcertSharedSlate`)
- L43 _prototype_ `TSharedRef<IPropertyAssignmentView> CreatePerObjectAssignmentView(FCreatePerObjectAssignmentViewParams Params = {});` (scope `UE::ConcertSharedSlate`) — Creates a view that shows the properties of the object the user clicks. This basically just wraps IPropertyTreeView. You can customize the tree view by injecting columns (@see CreateSearchablePropertyTreeView).
- L69 _prototype_ `TSharedRef<IMultiObjectPropertyAssignmentView> CreateMultiObjectAssignmentView(FCreateMultiObjectAssignmentViewParams Params = {});` (scope `UE::ConcertSharedSlate`) — Creates a view that shows the properties of the object the user clicks and its subobjects. You can customize the tree view by injecting columns (@see CreateSearchablePropertyTreeView).

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Replication/PropertyTreeFactory.h` (Public)


#### struct `UE::ConcertSharedSlate::FCreatePropertyTreeViewParams`  
`struct FCreatePropertyTreeViewParams`  
_L27-60_
- L30 _public member_ `TArray<FPropertyColumnEntry> PropertyColumns { ReplicationColumns::Property::LabelColumn() };` — Optional. Additional property columns you want added.
- L36 _public member_ `FFilterPropertyData FilterItem;` — Optional filter function.
- L45 _public member_ `FCreateCategoryRow CreateCategoryRow;` — Optional delegate for grouping objects under a category. If unset, no category are generated. When the user clicks an object in the top view, this delegate will be called for the clicked object, its components (if an actor), and its (nested) subobjects. ContextObjects is a single object if a single object is clicked or multiple object in the case of multi-edit.
- L48 _public member_ `FColumnSortInfo PrimaryPropertySort { ReplicationColumns::Property::LabelColumnId, EColumnSortMode::Ascending };` — Optional initial primary sort mode for object rows
- L50 _public member_ `FColumnSortInfo SecondaryPropertySort { ReplicationColumns::Property::LabelColumnId, EColumnSortMode::Ascending };` — Optional initial secondary sort mode for object rows
- L53 _public member_ `TAlwaysValidWidget LeftOfPropertySearchBar;` — Optional widget to add to the left of the property list search bar.
- L55 _public member_ `TAlwaysValidWidget RightOfPropertySearchBar;` — Optional widget to add to the right of the property list search bar.
- L57 _public member_ `TAlwaysValidWidget RowBelowSearchBar;` — Optional widget to add between the search bar and the table view (e.g. a SBasicFilterBar).
- L59 _public member_ `TAlwaysValidWidget NoItemsContent;` — Optional, alternate content to show instead of the tree view when there are no rows.

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L25 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(EFilterResult, FFilterPropertyData, const FPropertyData&);`
- L25 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(EFilterResult, FFilterPropertyData, const FPropertyData&);` (scope `UE::ConcertSharedSlate`)
- L66 _prototype_ `TSharedRef<IPropertyTreeView> CreateSearchablePropertyTreeView(FCreatePropertyTreeViewParams Params = {});` (scope `UE::ConcertSharedSlate`) — Creates a tree view that uses a search box for filtering items. You can customize this tree view by adding custom widgets and columns into the property view.

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Replication/ReplicationWidgetFactories.h` (Public)


#### struct `UE::ConcertSharedSlate::FCreateViewerParams`  
`struct FCreateViewerParams`  
_L57-106_
- desc: Params for creating a IReplicationStreamViewer.
- L60 _public member_ `TSharedRef<IPropertyAssignmentView> PropertyAssignmentView = CreatePerObjectAssignmentView();` — Required. In the lower half of the editor, this view presents the properties associated with the object that is currently selected in the upper part of the view.
- L67 _public member_ `TSharedPtr<IObjectHierarchyModel> ObjectHierarchy;` — Optional. Determines the objects displayed as children to the top-level objects in the top section. If left unspecified, the top will only display actors. @note The created view will keep a strong reference to this.
- L70 _public member_ `TSharedPtr<IObjectNameModel> NameModel;` — Optional. Determines the display name of objects.
- L73 _public member_ `FExtendObjectMenu OnExtendObjectsContextMenu;` — Called to generate the context menu for objects. This extends the options already generated by this widget and is called at the end.
- L76 _public member_ `TArray<FObjectColumnEntry> ObjectColumns;` — Optional. Additional object columns you want added.
- L79 _public member_ `FColumnSortInfo PrimaryObjectSort;` — Optional initial primary sort mode for object rows
- L81 _public member_ `FColumnSortInfo SecondaryObjectSort;` — Optional initial secondary sort mode for object rows
- L84 _public member_ `TAlwaysValidWidget LeftOfObjectSearchBar;` — Optional widget to add to the left of the object list search bar.
- L86 _public member_ `TAlwaysValidWidget RightOfObjectSearchBar;` — Optional widget to add to the right of the object list search bar.
- L97 _public member_ `FShouldDisplayObject ShouldDisplayObjectDelegate;` — Optional. Whether a given object should be displayed. This is useful e.g. for hiding objects that are not in the local editor's opened world (for that purpuse couple this delegate with @see FHideObjectsNotInWorldLogic). If the list of displayed objects changes, call IReplicationStreamViewer::Refresh. If this returns false on an object, none of its children will be shown either Child objects are determined using ObjectHierarchy.
- L100 _public member_ `FMakeObjectRowOverlayWidget MakeObjectRowOverlayWidgetDelegate;` — Optional. Delegate executed to create a widget that overlays an object row.
- L102 _public member_ `EHorizontalAlignment OverlayWidgetAlignment = HAlign_Right;` — Optional. If MakeRowOverlayWidgetDelegate is specified, this controls how the widget is aligned in the column.
- L105 _public member_ `FWrapOutlinerWidget WrapOutlinerWidgetDelegate;` — Optional. Returns a new widget that wraps the outliner widget, which displays the replicated objects. Could return e.g. an SOverlay or SDropTarget.

#### struct `UE::ConcertSharedSlate::FCreateEditorParams`  
`struct FCreateEditorParams`  
_L109-137_
- desc: Params for creating an IReplicationStreamEditor
- L115 _public member_ `TSharedRef<IEditableReplicationStreamModel> DataModel;` — Required. The model that the editor is displaying. @note The view will keep a strong reference to this.
- L121 _public member_ `TSharedRef<IObjectSelectionSourceModel> ObjectSource;` — Required. Determines the objects that can be added to the object list. @note The view will keep a strong reference to this.
- L126 _public member_ `TSharedRef<IPropertySourceProcessor> PropertySource;` — Required. Determines the properties that are displayed in the property list. @note The view will keep a strong reference to this.
- L129 _public member_ `TAttribute<bool> IsEditingEnabled;` — Optional. Determines whether all UI for changing the model should be disabled.
- L131 _public member_ `TAttribute<FText> EditingDisabledToolTipText;` — Optional. Whenever IsEditingEnabled returns true, this tooltip is displayed for relevant, disabled UI.
- L134 _public member_ `FSelectObjectsFromComboButton OnPreAddSelectedObjectsDelegate;` — Called just before the passed objects are added to the stream model. Called in response to the user selecting these objects from the combo button.
- L136 _public member_ `FSelectObjectsFromComboButton OnPostAddSelectedObjectsDelegate;` — Called just after the passed objects have been added to the stream model. Called in response to the user selecting these objects from the combo button.

#### struct `UE::ConcertSharedSlate::FCreateMultiStreamEditorParams`  
`struct FCreateMultiStreamEditorParams`  
_L156-198_
- desc: Params for creating an IMultiReplicationStreamEditor
- L162 _public member_ `TSharedRef<IEditableMultiReplicationStreamModel> MultiStreamModel;` — The source of underlying streams that should be edited. @note The view will keep a strong reference to this.
- L178 _public member_ `TSharedRef<IEditableReplicationStreamModel> ConsolidatedObjectModel;` — This model consolidates all objects in all streams. When an object is added (i.e. IEditableReplicationStreamModel::OnObjectsChanged broadcasts), e.g. when - to an object is added to one of the managed streams (e.g. stream is remotely changed), - via the "Add" button, it is added here, too. This is needed for the internal operation of the multi view. You can make this model internally transact (@see ConcertClientSharedSlate::CreateTransactionalStreamModel). Doing so causes the objects added via "add" button to be transacted meaning the user can undo adding objects. @note The view will keep a strong reference to this
- L184 _public member_ `TSharedRef<IObjectSelectionSourceModel> ObjectSource;` — Determines the objects that are displayed in the property list. @note The view will keep a strong reference to this.
- L189 _public member_ `TSharedRef<IPropertySourceProcessor> PropertySource;` — Determines the properties that can be added to the property list. @note The view will keep a strong reference to this.
- L192 _public member_ `FGetAutoAssignTarget GetAutoAssignToStreamDelegate;` — Optional. If set, the Add button should automatically assign the added object to stream returned by this callback.
- L195 _public member_ `FSelectObjectsFromComboButton OnPreAddSelectedObjectsDelegate;` — Called just before the passed objects are added to the stream model. Called in response to the user selecting these objects from the combo button.
- L197 _public member_ `FSelectObjectsFromComboButton OnPostAddSelectedObjectsDelegate;` — Called just after the passed objects have been added to the stream model. Called in response to the user selecting these objects from the combo button.

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L39 _prototype_ `TSharedRef<IReplicationStreamModel> CreateReadOnlyStreamModel( TAttribute<const FConcertObjectReplicationMap*> ReplicationMapAttribute );` (scope `UE::ConcertSharedSlate`) — Creates a stream model that will only read from ReplicationMapAttribute.
- L51 _prototype_ `TSharedRef<IEditableReplicationStreamModel> CreateBaseStreamModel( TAttribute<FConcertObjectReplicationMap*> ReplicationMapAttribute, TSharedPtr<IStreamExtender> Extender = nullptr );` (scope `UE::ConcertSharedSlate`) — Creates a model that can be passed to CreateEditor. @param ReplicationMapAttribute Getter for extracting the FConcertObjectReplicationMap to edit @param Extender Optional callbacks for adding additional properties and objects when an object is added to the model @return A model that will edit the FConcertObjectReplicationMap.
- L152 _prototype_ `TSharedRef<IReplicationStreamEditor> CreateBaseStreamEditor(FCreateEditorParams EditorParams, FCreateViewerParams ViewerParams);` (scope `UE::ConcertSharedSlate`) — Creates a base replication stream editor. This editor implements base functionality for adding objects but has NO logic for editing properties. You are expected to inject widgets or columns, which implement editing properties. @see ConcertClientSharedSlate::CreateDefaultStreamEditor, which adds a checkbox to the start of every property row. The editor consists of two or three areas (depending whether on whether SubobjectView was specified), which share similar workflows the level editor: 1. Root objects, similar to world outliner: - Similar to World Outliner: Displays top-level objects, i.e. actors, are added here. - FCreateEditorParams::ObjectSource is used to build a combo button through which new objects can be added. 2. Properties: Shows properties of the selected root object and / or subobjects.
- L154 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<IEditableReplicationStreamModel>, FGetAutoAssignTarget, TConstArrayView<UObject*>);`
- L154 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<IEditableReplicationStreamModel>, FGetAutoAssignTarget, TConstArrayView<UObject*>);` (scope `UE::ConcertSharedSlate`)
- L209 _prototype_ `TSharedRef<IMultiReplicationStreamEditor> CreateBaseMultiStreamEditor(FCreateMultiStreamEditorParams EditorParams, FCreateViewerParams ViewerParams);` (scope `UE::ConcertSharedSlate`) — Creates an editor that displays multiple streams in a single widget. This editor consolidates all replicated objects into a single UI and display all properties in the class. You are supposed to inject custom columns into the property section for assigning specific properties to the streams in the IEditableReplicationStreamModel. @note This editor does NOT create any UI for changing the assigned properties. You are supposed to inject column widgets to the property rows for this.

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Replication/Utils/FilterResult.h` (Public)


#### enum `UE::ConcertSharedSlate::EFilterResult`  
`enum class EFilterResult : uint8`  
_L9-13_
- L11 _public enumerator_ `PassesFilter`
- L12 _public enumerator_ `DoesNotPassFilter`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Replication/Utils/ReplicationWidgetDelegates.h` (Public)


#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L28 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FSortPropertyPredicate, const FPropertyData& Left, const FPropertyData& Right);` — A predicate for determining Left < Right.
- L28 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FSortPropertyPredicate, const FPropertyData& Left, const FPropertyData& Right);` (scope `UE::ConcertSharedSlate`) — A predicate for determining Left < Right.
- L31 _delegate_ `DECLARE_DELEGATE_TwoParams(FExtendObjectMenu, FMenuBuilder&, TConstArrayView<TSoftObjectPtr<>> ContextObjects);` — Extends a context menu that is being built for a selection of objects.
- L31 _prototype_ `DECLARE_DELEGATE_TwoParams(FExtendObjectMenu, FMenuBuilder&, TConstArrayView<TSoftObjectPtr<>> ContextObjects);` (scope `UE::ConcertSharedSlate`) — Extends a context menu that is being built for a selection of objects.
- L34 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FSoftClassPath, FGetObjectClass, const TSoftObjectPtr<>&);` — Delegate for getting an object's class.
- L34 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FSoftClassPath, FGetObjectClass, const TSoftObjectPtr<>&);` (scope `UE::ConcertSharedSlate`) — Delegate for getting an object's class.
- L37 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FShouldDisplayObject, const FSoftObjectPath& ObjectPath);` — Delegate for deciding whether an object should be displayed.
- L37 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FShouldDisplayObject, const FSoftObjectPath& ObjectPath);` (scope `UE::ConcertSharedSlate`) — Delegate for deciding whether an object should be displayed.
- L40 _delegate_ `DECLARE_DELEGATE_OneParam(FSelectObjectsFromComboButton, TConstArrayView<FSelectableObjectInfo>);` — Delegate executed when object options are selected from the Add button to the left of the search bar in the top view of the replication panel.
- L40 _prototype_ `DECLARE_DELEGATE_OneParam(FSelectObjectsFromComboButton, TConstArrayView<FSelectableObjectInfo>);` (scope `UE::ConcertSharedSlate`) — Delegate executed when object options are selected from the Add button to the left of the search bar in the top view of the replication panel.
- L43 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SWidget>, FMakeObjectRowOverlayWidget, const FReplicatedObjectData& ObjectData);` — Delegate executed to create a widget that overlays an object row.
- L43 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SWidget>, FMakeObjectRowOverlayWidget, const FReplicatedObjectData& ObjectData);` (scope `UE::ConcertSharedSlate`) — Delegate executed to create a widget that overlays an object row.
- L49 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SWidget>, FWrapOutlinerWidget, const TSharedRef<SWidget>& OutlinerWidget);` — Delegate executed during construction of UI. It receives the SReplicationTreeView showing the replicated objects. The returned widget is intended to wrap the tree in some way, e.g. by it into an SOverlay or SDropTarget.
- L49 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SWidget>, FWrapOutlinerWidget, const TSharedRef<SWidget>& OutlinerWidget);` (scope `UE::ConcertSharedSlate`) — Delegate executed during construction of UI. It receives the SReplicationTreeView showing the replicated objects. The returned widget is intended to wrap the tree in some way, e.g. by it into an SOverlay or SDropTarget.

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/SConcertScrollBox.h` (Public)


#### class `SConcertScrollBox`  
`class SConcertScrollBox : public SCompoundWidget`  
_L17-84_
- inherits: `SCompoundWidget`
- L30 _public function_ `SLATE_BEGIN_ARGS(SConcertScrollBox)`
- L31 _public prototype_ `SLATE_SLOT_ARGUMENT(FSlot, Slots) SLATE_END_ARGS();`
- L40 _public prototype_ `void Construct(const FArguments& InArgs);` — Construct a custom ScrollBox that automatically scrolls to the bottom if the user is not currently scrolling. @param InArgs The Slate argument list. @param ConstructUnderMajorTab The major tab which will contain the Session History widget.
- L43 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SWidget interface.
- L49 _public prototype_ `static FSlot::FSlotArguments Slot();` — @return a new slot. Slots contain children for SScrollBox
- L54 _private prototype_ `void HandleUserScrolled(float);` — Delegate called to handle a user scrolling.
- L57 _private prototype_ `bool IsAtBottom();` — Checks if the scrollbar is currently at the bottom of its track.
- L60 _private prototype_ `FReply HandleScrollToStart();` — Callback for scrolling to the start of the list.
- L63 _private prototype_ `FReply HandleScrollToEnd();` — Callback for scrolling to the end of the list.
- L66 _private prototype_ `EVisibility HandleScrollButtonsVisibility() const;` — Callback for getting the ScrollBar buttons visibility.
- L69 _private prototype_ `TSharedRef<SButton> CreateScrollBarButton(const FText& InToolTip, const FString& InIcon, FOnClicked OnClickedDelegate) const;` — Creates a button with the FontAwesome font.
- L74 _private member_ `bool bIsLocked;` — Whether the scrollbar is locked to the bottom.
- L77 _private member_ `bool bPreventLock;` — Whether locking should be prevented.
- L80 _private member_ `TSharedPtr<SScrollBar> ScrollBar;` — Holds the ScrollBar.
- L83 _private member_ `TSharedPtr<SScrollBox> ScrollBox;` — Holds the inner ScrollBox.

#### class `SConcertScrollBox::FSlot`  
`class FSlot : public TSlotBase<FSlot>`  
_L21-28_
- inherits: `TSlotBase<FSlot>`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CONCERTSHAREDSLATE_API`

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/SConcertSessionRecovery.h` (Public)


#### class `SConcertSessionRecovery`  
`class SConcertSessionRecovery : public SCompoundWidget`  
_L20-169_
- inherits: `SCompoundWidget`
- desc: Displays the list of activities available for recovery and let the user select what should or shouldn't be recovered.
- L23 _public function_ `SLATE_BEGIN_ARGS(SConcertSessionRecovery) : _WithClientAvatarColorColumn(false) , _WithClientNameColumn(false) , _WithOperationColumn(true) , _WithPackageColumn(false) , _DetailsAreaVisibility(EVisibility::Collapsed) , _IsConnectionActivityFilteringEnabled(false) , _IsLockActivityFilteringEnabled(false) , _IsPackageActivityFilteringEnabled(true) , _IsTransactionActivityFilteringEnabled(true) , _IsReplicationActivityFilteringEnabled(true) , _IsIgnoredActivityFilteringEnabled(false) , _AreRecoverAllAndCancelButtonsVisible(true) , _IsRecoverThroughButtonsVisible(true)`
- L39 _public prototype_ `SLATE_ARGUMENT(FText, IntroductionText) SLATE_ARGUMENT(TSharedPtr<SWindow>, ParentWindow) SLATE_EVENT(SConcertSessionActivities::FFetchActivitiesFunc, OnFetchActivities) SLATE_EVENT(SConcertSessionActivities::FGetActivityClientInfoFunc, OnMapActivityToClient) SLATE_ARGUMENT(TFunction<bool(TSharedPtr<FConcertSessionActivity>)>, OnRestore) SLATE_ARGUMENT(TFunction<void()>, OnCancel) SLATE_ARGUMENT(bool, WithClientAvatarColorColumn) SLATE_ARGUMENT(bool, WithClientNameColumn) SLATE_ARGUMENT(bool, WithOperationColumn) SLATE_ARGUMENT(bool, WithPackageColumn) SLATE_ARGUMENT(EVisibility, DetailsAreaVisibility) SLATE_ARGUMENT(bool, IsConnectionActivityFilteringEnabled) SLATE_ARGUMENT(bool, IsLockActivityFilteringEnabled) SLATE_ARGUMENT(bool, IsPackageActivityFilteringEnabled)` — An introduction text to put the user in context.
- L103 _public prototype_ `void Construct(const FArguments& InArgs);` — Construct the recovery widget. @param InArgs The widgets arguments and attributes.
- L106 _public function_ `TSharedPtr<FConcertSessionActivity> GetRecoverThroughItem()` — Returns the activity, selected by the user, through which the session should be (or was) recovered or null to prevent recovery.
- L109 _public prototype_ `void Reset();` — Removes all activities from the view and reset the activity stream.
- L112 _public prototype_ `int32 GetTotalActivityNum() const;` — Returns the total number of activities currently stored (no filter applied).
- L115 _public prototype_ `FText GetRecoverAllButtonTooltip() const;` — Returns the tooltip shown for the 'Recovery All' button.
- L118 _public prototype_ `TSharedPtr<FConcertSessionActivity> GetMostRecentActivity() const;` — Returns the most recent activity available, ignoring the current filter.
- L122 _private prototype_ `TArray<FActivityColumn> MakeColumns(const FArguments& InArgs) const;`
- L124 _private prototype_ `void OnSearchTextChanged(const FText& InFilterText);`
- L125 _private prototype_ `void OnSearchTextCommitted(const FText& InFilterText, ETextCommit::Type CommitType);`
- L126 _private prototype_ `FText HighlightSearchText() const;`
- L128 _private prototype_ `FReply OnCancelRecoveryClicked();`
- L129 _private prototype_ `FReply OnRecoverAllClicked();`
- L131 _private prototype_ `EVisibility GetRecoverThroughButtonVisibility(TSharedPtr<FConcertSessionActivity> Activity);`
- L132 _private prototype_ `FText GetRecoverThroughButtonTooltip() const;`
- L133 _private prototype_ `TSharedPtr<SWidget> MakeRecoverThroughWidget(TWeakPtr<FConcertSessionActivity>, const FName&);`
- L134 _private prototype_ `void RecoverThrough(TSharedPtr<FConcertSessionActivity> Item);`
- L137 _private prototype_ `void DismissWindow();` — Close the windows hosting this recovery widget.
- L141 _private member_ `TSharedPtr<SConcertSessionActivities> ActivityView;` — Display the session activities.
- L144 _private member_ `TSharedPtr<FConcertSessionActivitiesOptions> ActivityViewOptions;` — Controls the various display options of the view.
- L147 _private member_ `TSharedPtr<FConcertSessionActivity> RecoveryThroughItem;` — The activity selected when the user click 'Recover' or 'Recover Through' buttons.
- L150 _private member_ `TWeakPtr<SWindow> ParentWindow;` — The parent window hosting this widget.
- L153 _private member_ `TSharedPtr<SSearchBox> SearchBox;` — The widget used to enter the text to search.
- L156 _private member_ `FText SearchText;` — The search text entered in the search box.
- L159 _private member_ `FText IntroductionText;` — The text displayed at the top to summarize the purpose of the window.
- L162 _private member_ `TAttribute<bool> IsRecoverThroughButtonVisible;` — Externally control the 'recovery through' button visibility. The internal logic to show it is run first, if it is still visible, this is evaluated.
- L165 _private member_ `TFunction<bool(TSharedPtr<FConcertSessionActivity>)> OnRestoreFn;` — The function invoked when the user clicks the restore button. Might not be bound.
- L168 _private member_ `TFunction<void()> OnCancelFn;` — The function invoked when the user clicks the cancel button. Might not be bound.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CONCERTSHAREDSLATE_API`

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/SPackageDetails.h` (Public)


#### class `SPackageDetails`  
`class SPackageDetails : public SCompoundWidget`  
_L14-59_
- inherits: `SCompoundWidget`
- L17 _public function_ `SLATE_BEGIN_ARGS(SPackageDetails)`
- L19 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L34 _public prototype_ `void SetPackageInfo(const FConcertPackageInfo& InPackageInfo, const int64 InRevision, const FString& InModifiedBy);` — Set the current package to have its details displayed. @param InPackageInfo The current package to have its info displayed. @param InRevision The target package's revision. @param InModifiedBy The username of the user who modified the package.
- L47 _private typedef_ `using FListItemPtr = TSharedPtr<FPackageDetailsRow>;`
- L50 _private prototype_ `TSharedRef<ITableRow> HandleGenerateRow(FListItemPtr InItem, const TSharedRef<STableViewBase>& OwnerTable) const;` — Callback for generating package info rows.
- L55 _private member_ `TSharedPtr<SListView<FListItemPtr>> DetailListView;` — Holds the ListView of package details rows.
- L58 _private member_ `TArray<FListItemPtr> DetailItems;` — Holds the package details rows.

#### struct `SPackageDetails::FPackageDetailsRow`  
`struct FPackageDetailsRow`  
_L39-45_
- desc: Holds basic information about a given package.
- L41 _public member_ `FText PackageName;`
- L42 _public member_ `FText Revision;`
- L43 _public member_ `FText ModifiedBy;`
- L44 _public member_ `FText Action;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CONCERTSHAREDSLATE_API`

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Session/Activity/ActivityColumn.h` (Public)


#### class `FActivityColumn`  
`class FActivityColumn final : public SHeaderRow::FColumn`  
_L15-56_
- inherits: `SHeaderRow::FColumn`
- desc: A column in SConcertSessionActivities
- L20 _public function_ `DECLARE_DELEGATE_ThreeParams(FGenerateColumnWidget, const TSharedRef<SConcertSessionActivities>& Owner, const TSharedRef<FConcertSessionActivity>&, SOverlay::FScopedWidgetSlotArguments& Slot ) DECLARE_DELEGATE_ThreeParams(FPopulateSearchString, const TSharedRef<SConcertSessionActivities>& Owner, const FConcertSessionActivity& Activity, TArray<FString>& ExistingSearchStrings ) FActivityColumn(const FArguments& InArgs) : FColumn(InArgs)` — Generates the widget content for a column in a row
- L38 _public function_ `FActivityColumn& GenerateColumnWidget(FGenerateColumnWidget Callback)` — Called to generate the column's widget for a row
- L40 _public function_ `FActivityColumn& PopulateSearchString(FPopulateSearchString Callback)` — Called to populate the search terms when rows are search
- L43 _public function_ `FActivityColumn& ColumnSortOrder(int32 NewValue)` — Determines whether this column is the first, etc.
- L45 _public prototype_ `void BuildColumnWidget(const TSharedRef<SConcertSessionActivities>& Owner, const TSharedRef<FConcertSessionActivity>& Activity, SOverlay::FScopedWidgetSlotArguments& Slot) const;`
- L46 _public prototype_ `void ExecutePopulateSearchString(const TSharedRef<SConcertSessionActivities>& Owner, const FConcertSessionActivity& Activity, TArray<FString>& ExistingSearchStrings) const;`
- L47 _public function_ `int32 GetColumnSortOrderValue() const`
- L51 _private member_ `FGenerateColumnWidget GenerateColumnWidgetCallback;`
- L52 _private member_ `FPopulateSearchString PopulateSearchStringCallback;`
- L55 _private member_ `int32 ColumnSortOrderValue = 0;` — Determines whether this column is the first, etc.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CONCERTSHAREDSLATE_API`
- L20 _delegate_ `DECLARE_DELEGATE_ThreeParams(FGenerateColumnWidget, const TSharedRef<SConcertSessionActivities>& Owner, const TSharedRef<FConcertSessionActivity>&, SOverlay::FScopedWidgetSlotArguments& Slot ) DECLARE_DELEGATE_ThreeParams(FPopulateSearchString, const TSharedRef<SConcertSessionActivities>& Owner, const FConcertSessionActivity& Activity, TArray<FString>& ExistingSearchStrings ) FActivityColumn(const FArguments& InArgs) : FColumn(InArgs) {} FActivityColumn& GenerateColumnWidget(FGenerateColumnWidget Callback) { GenerateColumnWidgetCallback = MoveTemp(Callback); return *this; } FActivityColumn& PopulateSearchString(FPopulateSearchString Callback) { PopulateSearchStringCallback = MoveTemp(Callback); return *this; } FActivityColumn& ColumnSortOrder(int32 NewValue) { ColumnSortOrderValue = NewValue; return *this; } void BuildColumnWidget(const TSharedRef<SConcertSessionActivities>& Owner, const TSharedRef<FConcertSessionActivity>& Activity, SOverlay::FScopedWidgetSlotArguments& Slot) const;` — Generates the widget content for a column in a row
- L27 _delegate_ `DECLARE_DELEGATE_ThreeParams(FPopulateSearchString, const TSharedRef<SConcertSessionActivities>& Owner, const FConcertSessionActivity& Activity, TArray<FString>& ExistingSearchStrings ) FActivityColumn(const FArguments& InArgs) : FColumn(InArgs) {} FActivityColumn& GenerateColumnWidget(FGenerateColumnWidget Callback) { GenerateColumnWidgetCallback = MoveTemp(Callback); return *this; } FActivityColumn& PopulateSearchString(FPopulateSearchString Callback) { PopulateSearchStringCallback = MoveTemp(Callback); return *this; } FActivityColumn& ColumnSortOrder(int32 NewValue) { ColumnSortOrderValue = NewValue; return *this; } void BuildColumnWidget(const TSharedRef<SConcertSessionActivities>& Owner, const TSharedRef<FConcertSessionActivity>& Activity, SOverlay::FScopedWidgetSlotArguments& Slot) const;` — Appends search terms to ExistingSearchStrings.

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Session/Activity/IConcertReflectionDataProvider.h` (Public)


#### class `UE::ConcertSharedSlate::IConcertReflectionDataProvider`  
`class IConcertReflectionDataProvider : public UndoHistory::IReflectionDataProvider`  
_L13-19_
- inherits: `UndoHistory::IReflectionDataProvider`
- desc: Passed on to SUndoHistoryDetails to display reflection data in non-editor builds. Used e.g. by the server.
- L18 _public prototype_ `virtual void SetTransactionContext(const FConcertTransactionEventBase& InTransaction) = 0;` — Called just before SUndoHistoryDetails::SetSelectedTransaction. Injects the related property data saved in the activity.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Session/Activity/PredefinedActivityColumns.h` (Public)


#### enum `UE::ConcertSharedSlate::ActivityColumn::EPredefinedColumnOrder`  
`enum class EPredefinedColumnOrder : int32`  
_L13-21_
- L15 _public enumerator_ `AvatarColor = -20`
- L16 _public enumerator_ `DateTime = -10`
- L17 _public enumerator_ `ClientName = 10`
- L18 _public enumerator_ `Operation = 20`
- L19 _public enumerator_ `Package = 30`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L11 _namespace_ `namespace ActivityColumn` (scope `UE::ConcertSharedSlate`)
- L23 _externvar_ `extern const FName DateTimeColumnId;` (scope `UE::ConcertSharedSlate::ActivityColumn`)
- L24 _externvar_ `extern const FName OperationColumnId;` (scope `UE::ConcertSharedSlate::ActivityColumn`)
- L25 _externvar_ `extern const FName AvatarColorColumnId;` (scope `UE::ConcertSharedSlate::ActivityColumn`)
- L26 _externvar_ `extern const FName ClientNameColumnId;` (scope `UE::ConcertSharedSlate::ActivityColumn`)
- L27 _externvar_ `extern const FName PackageColumnId;` (scope `UE::ConcertSharedSlate::ActivityColumn`)
- L28 _externvar_ `extern const FName SummaryColumnId;` (scope `UE::ConcertSharedSlate::ActivityColumn`)
- L31 _prototype_ `FActivityColumn DateTime();` (scope `UE::ConcertSharedSlate::ActivityColumn`) — Required
- L32 _prototype_ `FActivityColumn Summary();` (scope `UE::ConcertSharedSlate::ActivityColumn`)
- L35 _prototype_ `FActivityColumn AvatarColor();` (scope `UE::ConcertSharedSlate::ActivityColumn`) — Optional
- L36 _prototype_ `FActivityColumn ClientName();` (scope `UE::ConcertSharedSlate::ActivityColumn`)
- L37 _prototype_ `FActivityColumn Operation();` (scope `UE::ConcertSharedSlate::ActivityColumn`)
- L38 _prototype_ `FActivityColumn Package();` (scope `UE::ConcertSharedSlate::ActivityColumn`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Session/Activity/SConcertSessionActivities.h` (Public)


#### enum `EConcertActivityFilterFlags`  
`enum class EConcertActivityFilterFlags`  
_L37-46_
- desc: Filters for the concert session activity view.
- L39 _public enumerator_ `ShowAll = 0x00`
- L40 _public enumerator_ `HideConnectionActivities = 1<<0`
- L41 _public enumerator_ `HideLockActivities = 1<<1`
- L42 _public enumerator_ `HidePackageActivities = 1<<2`
- L43 _public enumerator_ `HideTransactionActivities= 1<<3`
- L44 _public enumerator_ `HideIgnoredActivities = 1<<4`
- L45 _public enumerator_ `HideReplicationActivities= 1<<5`

#### class `SConcertSessionActivities`  
`class SConcertSessionActivities : public SCompoundWidget`  
_L50-370_
- inherits: `SCompoundWidget`
- desc: Displays session activities in a table view.
- L85 _public function_ `SLATE_BEGIN_ARGS(SConcertSessionActivities) : _OnFetchActivities() , _OnMapActivityToClient() , _OnMakeColumnOverlayWidget() , _TimeFormat(ETimeFormat::Relative) , _ConnectionActivitiesVisibility(EVisibility::Hidden) , _LockActivitiesVisibility(EVisibility::Hidden) , _PackageActivitiesVisibility(EVisibility::Visible) , _TransactionActivitiesVisibility(EVisibility::Visible) , _ReplicationActivitiesVisibility(EVisibility::Hidden) , _IgnoredActivitiesVisibility(EVisibility::Hidden) , _DetailsAreaVisibility(EVisibility::Hidden) , _IsAutoScrollEnabled(false) , _DarkenMutedActivities(true)`
- L102 _public prototype_ `SLATE_EVENT(FFetchActivitiesFunc, OnFetchActivities) SLATE_EVENT(FGetActivityClientInfoFunc, OnMapActivityToClient) SLATE_EVENT(FGetPackageEvent, OnGetPackageEvent) SLATE_EVENT(FGetTransactionEvent, OnGetTransactionEvent) SLATE_EVENT(FMakeColumnOverlayWidgetFunc, OnMakeColumnOverlayWidget) SLATE_EVENT(FOnContextMenuOpening, OnContextMenuOpening) /** The columns to show for each activity;` — If bound, invoked to populate the view.
- L175 _public prototype_ `void Construct(const FArguments& InArgs);` — Construct the recovery widget. @param InArgs The widgets arguments and attributes.
- L178 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — Requests and consumes more activities if needed and/or possible.
- L181 _public prototype_ `TSharedPtr<FConcertSessionActivity> GetSelectedActivity() const;` — Returns the activity selected or null if none is selected.
- L183 _public prototype_ `TArray<TSharedPtr<FConcertSessionActivity>> GetSelectedActivities() const;` — Returns all selected activities
- L186 _public function_ `int32 GetTotalActivityNum() const` — Returns the total number of activities currently stored (no filter applied).
- L189 _public function_ `int32 GetDisplayedActivityNum() const` — Returns the number of activities shown.
- L192 _public function_ `int32 GetIgnoredActivityNum() const` — Returns the number of activities marked as 'ignored'.
- L195 _public prototype_ `TSharedPtr<FConcertSessionActivity> GetMostRecentActivity() const;` — Returns the most recent activity available, ignoring the current filter.
- L198 _public prototype_ `bool IsLastColumn(const FName& ColumnId) const;` — Returns true if the column names is the last one (most right one).
- L201 _public prototype_ `void ResetActivityList();` — Clears all activities displayed.
- L204 _public prototype_ `void Append(TSharedPtr<FConcertSessionActivity> Activity);` — Append an activity to the view. Used to populate the view from a live session.
- L207 _public prototype_ `void RequestRefresh();` — Request the view to refresh.
- L210 _public prototype_ `FText UpdateTextFilter(const FText& InFilterText);` — Asks the view to update the text search filter.
- L212 _public prototype_ `void OnColumnVisibilitySettingsChanged(const FColumnVisibilitySnapshot& ColumnSnapshot);`
- L214 _public function_ `const TAttribute<FText>& GetHighlightText() const`
- L215 _public function_ `const TAttribute<ETimeFormat>& GetTimeFormat() const`
- L216 _public function_ `TOptional<FConcertClientInfo> GetClientInfo(const FGuid& Guid) const`
- L217 _public function_ `TSharedPtr<SHeaderRow> GetHeaderRow() const`
- L219 _public function_ `const TArray<TSharedPtr<FConcertSessionActivity>>& GetActivities() const`
- L220 _public function_ `void SetSelectedActivities(const TArray<TSharedPtr<FConcertSessionActivity>>& ActivitiesToSelect)`
- L229 _private prototype_ `TSharedRef<SHeaderRow> CreateHeaderRow(const FArguments& InArgs);` — Widget creation
- L230 _private prototype_ `TSharedRef<ITableRow> OnGenerateActivityRowWidget(TSharedPtr<FConcertSessionActivity> Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L231 _private prototype_ `void FetchActivities();`
- L234 _private prototype_ `EConcertActivityFilterFlags QueryActiveActivityFilters() const;` — Filtering
- L235 _private prototype_ `void OnActivityFilterUpdated();`
- L236 _private prototype_ `bool PassesFilters(const FConcertSessionActivity& Activity);`
- L239 _private prototype_ `void OnListViewScrolled(double InScrollOffset);` — List view
- L240 _private prototype_ `void OnListViewSelectionChanged(TSharedPtr<FConcertSessionActivity> InActivity, ESelectInfo::Type SelectInfo);`
- L243 _private prototype_ `void PopulateSearchStrings(const FConcertSessionActivity& Item, TArray<FString>& OutSearchStrings);` — Search
- L246 _private prototype_ `void OnDetailsAreaExpansionChanged(bool bExpanded);` — Details
- L247 _private prototype_ `void UpdateDetailArea(TSharedPtr<FConcertSessionActivity> InSelectedActivity);`
- L248 _private prototype_ `void UpdateDetailsByEventPayload(TSharedPtr<FConcertSessionActivity> InSelectedActivity);`
- L249 _private prototype_ `void UpdateDetailsByRequest(TSharedPtr<FConcertSessionActivity> InSelectedActivity);`
- L251 _private prototype_ `void SetDetailsPanelVisibility(const SWidget* VisiblePanel);`
- L252 _private prototype_ `void DisplayTransactionDetails(const FConcertSessionActivity& Activity, const FConcertTransactionEventBase& InTransaction);`
- L253 _private prototype_ `void DisplayPackageDetails(const FConcertSessionActivity& Activity, int64 PackageRevision, const FConcertPackageInfo& PackageInfo);`
- L255 _private prototype_ `FText GetNoDetailsText() const;`
- L256 _private function_ `EVisibility GetDetailAreaVisibility() const`
- L257 _private function_ `SSplitter::ESizeRule GetDetailsAreaSizeRule() const`
- L260 _private prototype_ `void OnPostTick(float);` — Invoked after all widget ticks get processed. Used to check if the user scrolled or not.
- L265 _private member_ `TArray<TSharedPtr<FConcertSessionActivity>> AllActivities;` — List of all activities (including the filtered out ones).
- L268 _private member_ `TArray<TSharedPtr<FConcertSessionActivity>> Activities;` — List of currently displayed activities.
- L271 _private member_ `TSharedPtr<SListView<TSharedPtr<FConcertSessionActivity>>> ActivityView;` — The list view widget displaying the activities.
- L274 _private member_ `TOptional<TSharedPtr<UE::ConcertSharedSlate::IConcertReflectionDataProvider>> ConcertReflectionDataProvider;` — Provides reflection data for SUndoHistoryDetails for non-editor builds.
- L277 _private member_ `FMakeColumnOverlayWidgetFunc MakeColumnOverlayWidgetFn;` — Used to overlay a widget over a column widget (add an extra layer above the normal one)
- L280 _private member_ `FOnContextMenuOpening OnContextMenuOpening;` — If bound, invoked when an item in the table is right-click and we are supposed to show a menu of actions.
- L283 _private member_ `bool bDarkenMutedActivities = true;` — Whether to darken muted activities
- L286 _private member_ `TAttribute<FText> HighlightText;` — Returns which text should be highlighted.
- L289 _private member_ `TAttribute<ETimeFormat> TimeFormat;` — Whether the time should be displayed as relative (9 seconds ago) or as absolute (July 10, 2019 - 10:20:10)
- L292 _private member_ `TAttribute<EVisibility> ConnectionActivitiesVisibility;` — Whether the join/leave session activities are displayed.
- L295 _private member_ `TAttribute<EVisibility> LockActivitiesVisibility;` — Whether the lock/unlock activities are displayed.
- L298 _private member_ `TAttribute<EVisibility> PackageActivitiesVisibility;` — Whether the package activities are displayed.
- L301 _private member_ `TAttribute<EVisibility> TransactionActivitiesVisibility;` — Whether the transaction activities are displayed.
- L304 _private member_ `TAttribute<EVisibility> ReplicationActivitiesVisibility;` — Whether the replication activities are displayed.
- L307 _private member_ `TAttribute<EVisibility> IgnoredActivitiesVisibility;` — Whether the ignored activities are displayed.
- L310 _private member_ `int32 IgnoredActivityNum = 0;` — The number of activities flagged as 'ignored' within AllActivities array.
- L313 _private member_ `bool bAutoScrollDesired = false;` — Whether the auto-scrolling is desired (scroll to bottom automatically unless the user scrolls somewhere else).
- L316 _private member_ `bool bUserScrolling = false;` — Whether the user is scrolling (deactivate auto-scrolling).
- L319 _private member_ `EConcertActivityFilterFlags ActiveFilterFlags = EConcertActivityFilterFlags::ShowAll;` — Defines which activity types are currently filtered out from the view.
- L322 _private member_ `FFetchActivitiesFunc FetchActivitiesFn;` — Used to fetch more activities from an abstract source. Usually mutually exclusive with Append() function. May not be bound.
- L324 _private member_ `FGetActivityClientInfoFunc GetActivityUserFn;` — Used to map an activity endpoint ID to a client. May not be bound.
- L326 _private member_ `FGetTransactionEvent GetTransactionEventFn;` — Used to get the transaction event to display the selected transaction activity details. May not be bound.
- L328 _private member_ `FGetPackageEvent GetPackageEventFn;` — Used to get the package event to display the selected package activity details. May not be bound.
- L331 _private member_ `static constexpr int32 ActivitiesPerRequest = 128;` — The number of activities to request when scrolling down to request activities on demand. Used with FetchActivitiesFn() for paging.
- L334 _private member_ `int32 DesiredActivitiesCount = ActivitiesPerRequest;` — The current desired amount of activities to display. Used for paging with FetchActivitiesFn(). It will grow when the user scrolls down.
- L337 _private member_ `bool bAllActivitiesFetched = false;` — True once the activity provider function (FetchActivitiesFn) returns true.
- L340 _private member_ `TSharedPtr<TTextFilter<const FConcertSessionActivity&>> SearchTextFilter;` — Utility class used to tokenize and match text displayed in the list view.
- L342 _private member_ `TSharedPtr<SHeaderRow> HeaderRow;`
- L345 _private member_ `bool bIsUpdatingColumnVisibility = false;` — Flag used to suspend saving of the column visibility while OnColumnVisibilitySettingsChanged is active to prevent infinite event recursion.
- L348 _private member_ `TSharedPtr<SExpandableArea> ExpandableDetails;` — The expandable area under which the activity details are displayed.
- L351 _private member_ `TSharedPtr<SUndoHistoryDetails> TransactionDetailsPanel;` — The widget displaying transaction details (if detail area is expanded) when a transaction activity is selected.
- L354 _private member_ `TSharedPtr<SPackageDetails> PackageDetailsPanel;` — The widget displaying package details (if detail area is expanded) when a package activity is selected.
- L357 _private member_ `TSharedPtr<SBox> NoDetailsPanel;` — The widget saying they are no detail available (if detail area is expanded) when the activity has no details or no activity is selected.
- L360 _private member_ `TSharedPtr<SWidget> LoadingDetailsPanel;` — The widget displayed when details of a partially sync activity (if detail area is expanded) are being fetched from the server.
- L363 _private member_ `EVisibility DetailsAreaVisibility = EVisibility::Collapsed;` — Indicate if the details area should be displayed or not.
- L366 _private member_ `bool bDetailsAreaExpanded = false;` — Keeps the expanded status of the details area.
- L369 _private member_ `bool bActivityViewScrolled = false;` — Indicate whether the activity list view was scrolled during a frame. Used to correctly detect auto-scrolling in special cases.

#### class `FConcertSessionActivitiesOptions`  
`class FConcertSessionActivitiesOptions : public TSharedFromThis<FConcertSessionActivitiesOptions>`  
_L376-434_
- inherits: `TSharedFromThis<FConcertSessionActivitiesOptions>`
- desc: Manages the various options exposed by SConcertSessionActivities widget such as enabling/disabling filtering, changing the time format, etc.
- L380 _public prototype_ `DECLARE_DELEGATE_OneParam(FExtendContextMenu, FMenuBuilder&) TSharedRef<SWidget> MakeStatusBar(TAttribute<int32> Total, TAttribute<int32> Displayed);`
- L386 _public prototype_ `TSharedRef<SWidget> MakeViewOptionsComboButton(TOptional<FExtendContextMenu> ExtendMenu = {});` — Makes a standard View Options widget, displaying the eye ball icon and showing the possible options.
- L388 _public prototype_ `TSharedRef<SWidget> MakeMenuWidget(TOptional<FExtendContextMenu> ExtendMenu = {});` — Returns a Menu widgets containing the available options.
- L391 _public function_ `ETimeFormat GetTimeFormat() const` — Returns the time format option.
- L393 _public function_ `EVisibility GetConnectionActivitiesVisibility() const` — Returns whether the connection activities are listed in SConcertSessionActivities.
- L395 _public function_ `EVisibility GetLockActivitiesVisibility() const` — Returns whether the lock activities are listed in SConcertSessionActivities.
- L397 _public function_ `EVisibility GetPackageActivitiesVisibility() const` — Returns whether the package activities are listed in SConcertSessionActivities.
- L399 _public function_ `EVisibility GetTransactionActivitiesVisibility() const` — Returns whether the transaction activities are listed in SConcertSessionActivities.
- L401 _public function_ `EVisibility GetReplicationActivitiesVisibility() const` — Returns whether the ignored activities are listed in SConcertSessionActivities.
- L403 _public function_ `EVisibility GetIgnoredActivitiesVisibility() const` — Returns whether the ignored activities are listed in SConcertSessionActivities.
- L406 _public prototype_ `void OnOptionToggled(const FName CheckBoxId);` — Invoked when an options is togged from the displayed menu widget.
- L409 _public member_ `bool bEnableConnectionActivityFiltering = true;` — Enables the 'connection activity' filter check box. (Show Connection Activities).
- L411 _public member_ `bool bEnableLockActivityFiltering = true;` — Enables the 'lock activity' filter check box. (Show Lock Activities).
- L413 _public member_ `bool bEnablePackageActivityFiltering = true;` — Enables the 'package activity' filter check box (Show Package Activities).
- L415 _public member_ `bool bEnableTransactionActivityFiltering = true;` — Enables the 'transaction activity' filter check box (Show Transaction Activities).
- L417 _public member_ `bool bEnableReplicationActivityFiltering = true;` — Enables the 'replication activity' filter check box (Show Replication Activities).
- L419 _public member_ `bool bEnableIgnoredActivityFiltering = false;` — Enables the 'ignored activity' filter check box (Show Unrecoverable Activities).
- L421 _public member_ `bool bDisplayRelativeTime = true;` — Controls whether the time is displayed as absolute or relative. (Display Relative Time).
- L423 _public member_ `bool bDisplayConnectionActivities = false;` — If connection filtering is enabled, controls whether connection activities are filtered out.
- L425 _public member_ `bool bDisplayLockActivities = false;` — If lock filtering is enabled, controls whether lock activities are filtered out.
- L427 _public member_ `bool bDisplayPackageActivities = true;` — If package filtering is enabled, controls whether package activities are filtered out.
- L429 _public member_ `bool bDisplayTransactionActivities = true;` — If transaction filtering is enabled, controls whether transaction activities are filtered out.
- L431 _public member_ `bool bDisplayReplicationActivities = false;` — If replication filtering is enabled, controls whether replication activities are filtered out.
- L433 _public member_ `bool bDisplayIgnoredActivities = false;` — If ignored activity filtering is enabled, controls whether ignored activities are filtered out.

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API CONCERTSHAREDSLATE_API`
- L31 _namespace_ `namespace UE`
- L31 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L47 _prototype_ `ENUM_CLASS_FLAGS(EConcertActivityFilterFlags);`
- L55 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FFetchActivitiesFunc, TArray<TSharedPtr<FConcertSessionActivity>>& , int32& , FText& ) DECLARE_DELEGATE_RetVal_OneParam(TOptional<FConcertClientInfo>, FGetActivityClientInfoFunc, FGuid ) DECLARE_DELEGATE_RetVal_OneParam(TFuture<TOptional<FConcertSyncTransactionEvent>>, FGetTransactionEvent, const FConcertSessionActivity& ) DECLARE_DELEGATE_RetVal_TwoParams(bool, FGetPackageEvent, const FConcertSessionActivity& , FConcertSyncPackageEventMetaData& ) DECLARE_DELEGATE_RetVal_ThreeParams(TSharedPtr<SWidget>, FMakeColumnOverlayWidgetFunc, TWeakPtr<SMultiColumnTableRow<TSharedPtr<FConcertSessionActivity>>> , TWeakPtr<FConcertSessionActivity> , const FName& ) public: SLATE_BEGIN_ARGS(SConcertSessionActivities) : _OnFetchActivities() , _OnMapActivityToClient() , _OnMakeColumnOverlayWidget() , _TimeFormat(ETimeFormat::Relative) , _ConnectionActivitiesVisibility(EVisibility::Hidden) , _LockActivitiesVisibility(EVisibility::Hidden) , _PackageActivitiesVisibility(EVisibility::Visible) , _TransactionActivitiesVisibility(EVisibility::Visible) , _ReplicationActivitiesVisibility(EVisibility::Hidden)` — Used to pull activities from a session. Used to fetch and display the activities of an archived session.
- L62 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TOptional<FConcertClientInfo>, FGetActivityClientInfoFunc, FGuid ) DECLARE_DELEGATE_RetVal_OneParam(TFuture<TOptional<FConcertSyncTransactionEvent>>, FGetTransactionEvent, const FConcertSessionActivity& ) DECLARE_DELEGATE_RetVal_TwoParams(bool, FGetPackageEvent, const FConcertSessionActivity& , FConcertSyncPackageEventMetaData& ) DECLARE_DELEGATE_RetVal_ThreeParams(TSharedPtr<SWidget>, FMakeColumnOverlayWidgetFunc, TWeakPtr<SMultiColumnTableRow<TSharedPtr<FConcertSessionActivity>>> , TWeakPtr<FConcertSessionActivity> , const FName& ) public: SLATE_BEGIN_ARGS(SConcertSessionActivities) : _OnFetchActivities() , _OnMapActivityToClient() , _OnMakeColumnOverlayWidget() , _TimeFormat(ETimeFormat::Relative) , _ConnectionActivitiesVisibility(EVisibility::Hidden) , _LockActivitiesVisibility(EVisibility::Hidden) , _PackageActivitiesVisibility(EVisibility::Visible) , _TransactionActivitiesVisibility(EVisibility::Visible) , _ReplicationActivitiesVisibility(EVisibility::Hidden) , _IgnoredActivitiesVisibility(EVisibility::Hidden) , _DetailsAreaVisibility(EVisibility::Hidden) , _IsAutoScrollEnabled(false) , _DarkenMutedActivities(true) { }` — Used to map an activity to its client.
- L67 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TFuture<TOptional<FConcertSyncTransactionEvent>>, FGetTransactionEvent, const FConcertSessionActivity& ) DECLARE_DELEGATE_RetVal_TwoParams(bool, FGetPackageEvent, const FConcertSessionActivity& , FConcertSyncPackageEventMetaData& ) DECLARE_DELEGATE_RetVal_ThreeParams(TSharedPtr<SWidget>, FMakeColumnOverlayWidgetFunc, TWeakPtr<SMultiColumnTableRow<TSharedPtr<FConcertSessionActivity>>> , TWeakPtr<FConcertSessionActivity> , const FName& ) public: SLATE_BEGIN_ARGS(SConcertSessionActivities) : _OnFetchActivities() , _OnMapActivityToClient() , _OnMakeColumnOverlayWidget() , _TimeFormat(ETimeFormat::Relative) , _ConnectionActivitiesVisibility(EVisibility::Hidden) , _LockActivitiesVisibility(EVisibility::Hidden) , _PackageActivitiesVisibility(EVisibility::Visible) , _TransactionActivitiesVisibility(EVisibility::Visible) , _ReplicationActivitiesVisibility(EVisibility::Hidden) , _IgnoredActivitiesVisibility(EVisibility::Hidden) , _DetailsAreaVisibility(EVisibility::Hidden) , _IsAutoScrollEnabled(false) , _DarkenMutedActivities(true) { } SLATE_EVENT(FFetchActivitiesFunc, OnFetchActivities) SLATE_EVENT(FGetActivityClientInfoFunc, OnMapActivityToClient)` — Returns the transaction event corresponding the specified activity.
- L72 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FGetPackageEvent, const FConcertSessionActivity& , FConcertSyncPackageEventMetaData& ) DECLARE_DELEGATE_RetVal_ThreeParams(TSharedPtr<SWidget>, FMakeColumnOverlayWidgetFunc, TWeakPtr<SMultiColumnTableRow<TSharedPtr<FConcertSessionActivity>>> , TWeakPtr<FConcertSessionActivity> , const FName& ) public: SLATE_BEGIN_ARGS(SConcertSessionActivities) : _OnFetchActivities() , _OnMapActivityToClient() , _OnMakeColumnOverlayWidget() , _TimeFormat(ETimeFormat::Relative) , _ConnectionActivitiesVisibility(EVisibility::Hidden) , _LockActivitiesVisibility(EVisibility::Hidden) , _PackageActivitiesVisibility(EVisibility::Visible) , _TransactionActivitiesVisibility(EVisibility::Visible) , _ReplicationActivitiesVisibility(EVisibility::Hidden) , _IgnoredActivitiesVisibility(EVisibility::Hidden) , _DetailsAreaVisibility(EVisibility::Hidden) , _IsAutoScrollEnabled(false) , _DarkenMutedActivities(true) { } SLATE_EVENT(FFetchActivitiesFunc, OnFetchActivities) SLATE_EVENT(FGetActivityClientInfoFunc, OnMapActivityToClient) SLATE_EVENT(FGetPackageEvent, OnGetPackageEvent) SLATE_EVENT(FGetTransactionEvent, OnGetTransactionEvent)` — Returns the package event corresponding to the package activity.
- L78 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(TSharedPtr<SWidget>, FMakeColumnOverlayWidgetFunc, TWeakPtr<SMultiColumnTableRow<TSharedPtr<FConcertSessionActivity>>> , TWeakPtr<FConcertSessionActivity> , const FName& ) public: SLATE_BEGIN_ARGS(SConcertSessionActivities) : _OnFetchActivities() , _OnMapActivityToClient() , _OnMakeColumnOverlayWidget() , _TimeFormat(ETimeFormat::Relative) , _ConnectionActivitiesVisibility(EVisibility::Hidden) , _LockActivitiesVisibility(EVisibility::Hidden) , _PackageActivitiesVisibility(EVisibility::Visible) , _TransactionActivitiesVisibility(EVisibility::Visible) , _ReplicationActivitiesVisibility(EVisibility::Hidden) , _IgnoredActivitiesVisibility(EVisibility::Hidden) , _DetailsAreaVisibility(EVisibility::Hidden) , _IsAutoScrollEnabled(false) , _DarkenMutedActivities(true) { } SLATE_EVENT(FFetchActivitiesFunc, OnFetchActivities) SLATE_EVENT(FGetActivityClientInfoFunc, OnMapActivityToClient) SLATE_EVENT(FGetPackageEvent, OnGetPackageEvent) SLATE_EVENT(FGetTransactionEvent, OnGetTransactionEvent) SLATE_EVENT(FMakeColumnOverlayWidgetFunc, OnMakeColumnOverlayWidget) SLATE_EVENT(FOnContextMenuOpening, OnContextMenuOpening)` — Used to overlay a widget over a column widget to add custom functionalities to a row.
- L380 _delegate_ `DECLARE_DELEGATE_OneParam(FExtendContextMenu, FMenuBuilder&) TSharedRef<SWidget> MakeStatusBar(TAttribute<int32> Total, TAttribute<int32> Displayed);`

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Session/Browser/ConcertBrowserUtils.h` (Public)


#### Free symbols / members of external scopes

- L23 _namespace_ `namespace ConcertBrowserUtils`
- L26 _variable_ `static const FName SessionColName(TEXT("Sess` (scope `ConcertBrowserUtils`) — Defines the sessions list view column tag names.
- L27 _variable_ `static const FName ServerColName(TEXT("Serv` (scope `ConcertBrowserUtils`)
- L28 _variable_ `static const FName ProjectColName(TEXT("Proj` (scope `ConcertBrowserUtils`)
- L29 _variable_ `static const FName VersionColName(TEXT("Vers` (scope `ConcertBrowserUtils`)
- L30 _variable_ `static const FName LastModifiedColName(TEXT("Last` (scope `ConcertBrowserUtils`)
- L33 _variable_ `static const FName LastModifiedCheckBoxMenuName(TEXT("Last` (scope `ConcertBrowserUtils`) — Name of the filter box in the View option.
- L34 _variable_ `static const FName ActiveSessionsCheckBoxMenuName(TEXT("Acti` (scope `ConcertBrowserUtils`)
- L35 _variable_ `static const FName ArchivedSessionsCheckBoxMenuName(TEXT("Arch` (scope `ConcertBrowserUtils`)
- L36 _variable_ `static const FName DefaultServerCheckBoxMenuName(TEXT("Defa` (scope `ConcertBrowserUtils`)
- L39 _variable_ `static const FName IconColumnFontName(TEXT("Font` (scope `ConcertBrowserUtils`) — The awesome font used to pick the icon displayed in the session list view 'Icon' column.
- L42 _function_ `inline TSharedRef<SWidget> MakeIconButton(const TAttribute<const FSlateBrush*>& Icon, const TAttribute<FText>& Tooltip, const TAttribute<bool>& EnabledAttribute, const FOnClicked& OnClicked, const TAttribute<EVisibility>& Visibility = EVisibility::Visible)` (scope `ConcertBrowserUtils`) — Utility function used to create buttons displaying only an icon (using a brush)
- L60 _function_ `inline TSharedRef<SWidget> MakePositiveActionButton(const TAttribute<const FSlateBrush*>& Icon, const TAttribute<FText>& Tooltip, const TAttribute<bool>& EnabledAttribute, const FOnClicked& OnClicked, const TAttribute<EVisibility>& Visibility = EVisibility::Visible)` (scope `ConcertBrowserUtils`) — Utility function used to create buttons displaying a positive action
- L71 _function_ `inline TSharedRef<SWidget> MakeNegativeActionButton(const TAttribute<const FSlateBrush*>& Icon, const TAttribute<FText>& Tooltip, const TAttribute<bool>& EnabledAttribute, const FOnClicked& OnClicked, const TAttribute<EVisibility>& Visibility = EVisibility::Visible)` (scope `ConcertBrowserUtils`) — Utility function used to create buttons displaying a negative action
- L82 _function_ `inline FText GetServerVersionIgnoredTooltip()` (scope `ConcertBrowserUtils`) — Returns the tooltip shown when hovering the triangle with an exclamation icon when a server doesn't validate the version requirements.
- L84 _macro_ `#define LOCTEXT_NAMESPACE "SConcertBrowser"`
- L90 _function_ `inline TSharedRef<SWidget> MakeServerVersionIgnoredWidget(EConcertServerFlags InServerFlags)` (scope `ConcertBrowserUtils`) — Create a widget displaying the triangle with an exclamation icon in case the server flags include IgnoreSessionRequirement.
- L104 _function_ `inline void RequestItemDeletion(IConcertSessionBrowserController& Controller, const TArray<TSharedPtr<FConcertSessionTreeItem>>& SessionItems)` (scope `ConcertBrowserUtils`) — Helper function to split an array of FConcertSessionItems into multiple requests and execute
- L106 _typedef_ `using FServerAdminEndpointId = FGuid;` (scope `ConcertBrowserUtils::RequestItemDeletion`)
- L107 _typedef_ `using FSessionId = FGuid;` (scope `ConcertBrowserUtils::RequestItemDeletion`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Session/Browser/ConcertSessionBrowserSettings.h` (Public)


#### class `UConcertSessionBrowserSettings`  
`class UConcertSessionBrowserSettings : public UObject`  
_L12-30_
- reflection: `UCLASS(MinimalAPI, config=Editor)`
- inherits: `UObject`
- desc: Serializes the multi-user session browser settings like the active filters.
- L17 _public function_ `UConcertSessionBrowserSettings()`
- L20 _public member_ `ETimeFormat LastModifiedTimeFormat = ETimeFormat::Absolute;` — `UPROPERTY(config, EditAnywhere, Category="Multi-User Session Browser")`
- L23 _public member_ `bool bShowActiveSessions = true;` — `UPROPERTY(config, EditAnywhere, Category="Multi-User Session Browser")`
- L26 _public member_ `bool bShowArchivedSessions = true;` — `UPROPERTY(config, EditAnywhere, Category="Multi-User Session Browser")`
- L29 _public member_ `bool bShowDefaultServerSessionsOnly = false;` — `UPROPERTY(config, EditAnywhere, Category="Multi-User Session Browser")`

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Session/Browser/IConcertSessionBrowserController.h` (Public)


#### class `IConcertSessionBrowserController`  
`class IConcertSessionBrowserController`  
_L13-70_
- desc: Runs and cache network queries for the UI. In the model-view-controller pattern, this class acts like the controller. Its purpose is to keep the UI code as decoupled as possible from the API used to query it. It encapsulate the asynchronous code and provide a simpler API to the UI.
- L43 _public prototype_ `virtual TArray<FConcertServerInfo> GetServers() const = 0;` — Returns the latest list of server known to this controller.
- L46 _public prototype_ `virtual TArray<FActiveSessionInfo> GetActiveSessions() const = 0;` — Returns the latest list of active sessions known to this controller.
- L49 _public prototype_ `virtual TArray<FArchivedSessionInfo> GetArchivedSessions() const = 0;` — Returns the latest list of archived sessions known to this controller.
- L52 _public prototype_ `virtual TOptional<FConcertSessionInfo> GetActiveSessionInfo(const FGuid& AdminEndpoint, const FGuid& SessionId) const = 0;` — Returns the active sessions info corresponding to the specified parameters. Used to display the sessions details.
- L55 _public prototype_ `virtual TOptional<FConcertSessionInfo> GetArchivedSessionInfo(const FGuid& AdminEndpoint, const FGuid& SessionId) const = 0;` — Returns the archived sessions info corresponding to the specified parameters. Used to display the sessions details.
- L57 _public prototype_ `virtual void CreateSession(const FGuid& ServerAdminEndpointId, const FString& SessionName, const FString& ProjectName) = 0;`
- L58 _public prototype_ `virtual void ArchiveSession(const FGuid& ServerAdminEndpointId, const FGuid& SessionId, const FString& ArchiveName, const FConcertSessionFilter& SessionFilter) = 0;`
- L59 _public prototype_ `virtual void RestoreSession(const FGuid& ServerAdminEndpointId, const FGuid& SessionId, const FString& RestoredName, const FConcertSessionFilter& SessionFilter) = 0;`
- L60 _public prototype_ `virtual void RenameActiveSession(const FGuid& ServerAdminEndpointId, const FGuid& SessionId, const FString& NewName) = 0;`
- L61 _public prototype_ `virtual void RenameArchivedSession(const FGuid& ServerAdminEndpointId, const FGuid& SessionId, const FString& NewName) = 0;`
- L62 _public prototype_ `virtual bool CanRenameActiveSession(const FGuid& ServerAdminEndpointId, const FGuid& SessionId) const = 0;`
- L63 _public prototype_ `virtual bool CanRenameArchivedSession(const FGuid& ServerAdminEndpointId, const FGuid& SessionId) const = 0;`
- L64 _public prototype_ `virtual void DeleteSessions(const FGuid& ServerAdminEndpointId, const TArray<FGuid>& SessionIds) = 0;`
- L65 _public prototype_ `virtual bool CanDeleteActiveSession(const FGuid& ServerAdminEndpointId, const FGuid& SessionId) const = 0;`
- L66 _public prototype_ `virtual bool CanDeleteArchivedSession(const FGuid& ServerAdminEndpointId, const FGuid& SessionId) const = 0;`
- L67 _public prototype_ `virtual bool CanEverCreateSessions() const = 0;`
- L69 _public prototype_ `virtual ~IConcertSessionBrowserController() = default;`

#### struct `IConcertSessionBrowserController::FActiveSessionInfo`  
`struct FActiveSessionInfo`  
_L17-28_
- L19 _public member_ `FConcertServerInfo ServerInfo;`
- L20 _public member_ `FConcertSessionInfo SessionInfo;`
- L21 _public member_ `TArray<FConcertSessionClientInfo> Clients;`
- L23 _public function_ `FActiveSessionInfo(FConcertServerInfo ServerInfo, FConcertSessionInfo SessionInfo, TArray<FConcertSessionClientInfo> Clients = {}) : ServerInfo(MoveTemp(ServerInfo)) , SessionInfo(MoveTemp(SessionInfo)) , Clients(MoveTemp(Clients))`

#### struct `IConcertSessionBrowserController::FArchivedSessionInfo`  
`struct FArchivedSessionInfo`  
_L30-39_
- L32 _public member_ `FConcertServerInfo ServerInfo;`
- L33 _public member_ `FConcertSessionInfo SessionInfo;`
- L35 _public function_ `FArchivedSessionInfo(FConcertServerInfo ServerInfo, FConcertSessionInfo SessionInfo) : ServerInfo(MoveTemp(ServerInfo)) , SessionInfo(MoveTemp(SessionInfo))`

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Session/Browser/Items/ConcertActiveGroupTreeItem.h` (Public)


#### class `FConcertActiveGroupTreeItem`  
`class FConcertActiveGroupTreeItem : public FConcertGroupTreeItem`  
_L10-18_
- inherits: `FConcertGroupTreeItem`
- desc: Groups several active sessions
- L12 _private typedef_ `using Super = FConcertGroupTreeItem;`
- L15 _public function_ `FConcertActiveGroupTreeItem(FGetSessions GetSessionsFunc) : Super(MoveTemp(GetSessionsFunc), { FConcertSessionTreeItem::EType::ActiveSession, FConcertSessionTreeItem::EType::NewSession, FConcertSessionTreeItem::EType::SaveSession })`

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Session/Browser/Items/ConcertArchivedGroupTreeItem.h` (Public)


#### class `FConcertArchivedGroupTreeItem`  
`class FConcertArchivedGroupTreeItem : public FConcertGroupTreeItem`  
_L9-17_
- inherits: `FConcertGroupTreeItem`
- desc: Groups archived sessions
- L11 _private typedef_ `using Super = FConcertGroupTreeItem;`
- L14 _public function_ `FConcertArchivedGroupTreeItem(FGetSessions GetSessionsFunc) : Super(MoveTemp(GetSessionsFunc), { FConcertSessionTreeItem::EType::ArchivedSession, FConcertSessionTreeItem::EType::RestoreSession })`

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Session/Browser/Items/ConcertGroupTreeItem.h` (Public)


#### class `FConcertGroupTreeItem`  
`class FConcertGroupTreeItem : public FConcertTreeItem`  
_L10-37_
- inherits: `FConcertTreeItem`
- desc: Groups several FConcertSessionTreeItem
- L14 _public typedef_ `using FGetSessions = TFunction<TArray<TSharedPtr<FConcertSessionTreeItem>>()>;`
- L16 _public function_ `FConcertGroupTreeItem(FGetSessions GetSessionsFunc, TSet<FConcertSessionTreeItem::EType> AllowedTypes) : GetSessionsFunc(MoveTemp(GetSessionsFunc)) , AllowedTypes(MoveTemp(AllowedTypes))`
- L21 _public function_ `virtual void GetChildren(TArray<TSharedPtr<FConcertTreeItem>>& OutChildren) const override`
- L35 _protected member_ `const FGetSessions GetSessionsFunc;`
- L36 _protected member_ `const TSet<FConcertSessionTreeItem::EType> AllowedTypes;`

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Session/Browser/Items/ConcertSessionTreeItem.h` (Public)


#### class `FConcertSessionTreeItem`  
`class FConcertSessionTreeItem : public FConcertTreeItem`  
_L13-75_
- inherits: `FConcertTreeItem`
- desc: An item that represents a session, i.e. has session info.
- L26 _public function_ `FConcertSessionTreeItem(EType Type = EType::None, const FGuid& ServerAdminEndpointId = {}, const FGuid& SessionId = {}, const FString& SessionName = {}, const FString& ServerName = {}, const FString& ProjectName = {}, const FString& ProjectVersion = {}, EConcertServerFlags ServerFlags = {}, const FDateTime& LastModified = {}, const FOnBeginEditConcertSessionNameRequest& OnBeginEditSessionNameRequest = {} ) : Type(Type) , ServerAdminEndpointId(ServerAdminEndpointId) , SessionId(SessionId) , SessionName(SessionName) , ServerName(ServerName) , ProjectName(ProjectName) , ProjectVersion(ProjectVersion) , ServerFlags(ServerFlags) , LastModified(LastModified) , OnBeginEditSessionNameRequest(OnBeginEditSessionNameRequest)`
- L49 _public function_ `bool operator==(const FConcertSessionTreeItem& Other) const`
- L54 _public function_ `FConcertSessionTreeItem MakeCopyAsType(EType NewType) const`
- L61 _public function_ `virtual void GetChildren(TArray<TSharedPtr<FConcertTreeItem>>& OutChildren) const override`
- L63 _public member_ `EType Type = EType::None;`
- L64 _public member_ `FGuid ServerAdminEndpointId;`
- L65 _public member_ `FGuid SessionId;`
- L66 _public member_ `FString SessionName;`
- L67 _public member_ `FString ServerName;`
- L68 _public member_ `FString ProjectName;`
- L69 _public member_ `FString ProjectVersion;`
- L70 _public member_ `EConcertServerFlags ServerFlags = EConcertServerFlags::None;`
- L72 _public member_ `FDateTime LastModified;`
- L74 _public member_ `FOnBeginEditConcertSessionNameRequest OnBeginEditSessionNameRequest;` — Emitted when user press 'F2' or select 'Rename' from context menu.

#### enum `FConcertSessionTreeItem::EType`  
`enum class EType`  
_L16-24_
- L18 _public enumerator_ `None`
- L19 _public enumerator_ `NewSession` — Editable item to enter a session name and a pick a server.
- L20 _public enumerator_ `RestoreSession` — Editable item to name the restored session.
- L21 _public enumerator_ `SaveSession` — Editable item to name the archive.
- L22 _public enumerator_ `ActiveSession` — Read-only item representing an active session.
- L23 _public enumerator_ `ArchivedSession` — Read-only item representing an archived session.

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnBeginEditConcertSessionNameRequest) class FConcertSessionTreeItem : public FConcertTreeItem { public: enum class EType { None, NewSession,` — Signal emitted when a session name text field should enter in edit mode.

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Session/Browser/Items/ConcertTreeItem.h` (Public)


#### class `FConcertTreeItem`  
`class FConcertTreeItem`  
_L8-15_
- desc: Base class for everything displayed in session view
- L12 _public prototype_ `virtual void GetChildren(TArray<TSharedPtr<FConcertTreeItem>>& OutChildren) const = 0;`
- L14 _public prototype_ `virtual ~FConcertTreeItem() = default;`

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Session/Browser/SConcertSessionBrowser.h` (Public)


#### class `SConcertSessionBrowser`  
`class SConcertSessionBrowser : public SCompoundWidget`  
_L42-270_
- inherits: `SCompoundWidget`
- desc: Enables the user to browse/search/filter/sort active and archived sessions, create new session, archive active sessions, restore archived sessions, join a session and open the settings dialog.
- L62 _public function_ `SLATE_BEGIN_ARGS(SConcertSessionBrowser)`
- L65 _public prototype_ `SLATE_ATTRIBUTE(FString, DefaultSessionName) SLATE_ATTRIBUTE(FString, DefaultServerURL) SLATE_EVENT(FExtendSessionTable, ExtendSessionTable) SLATE_EVENT(FExtenderDelegate, ExtendControllButtons) SLATE_EVENT(FExtendSessionContextMenu, ExtendSessionContextMenu) SLATE_NAMED_SLOT(FArguments, RightOfControlButtons) SLATE_EVENT(FSessionDelegate, OnSessionClicked) SLATE_EVENT(FSessionDelegate, OnLiveSessionDoubleClicked) SLATE_EVENT(FSessionDelegate, OnArchivedSessionDoubleClicked) SLATE_EVENT(FSessionListDelegate, PostRequestedDeleteSession) SLATE_EVENT(FCanRemoveSessions, AskUserToDeleteSessions) SLATE_ARGUMENT(FColumnVisibilitySnapshot, ColumnVisibilitySnapshot) SLATE_EVENT(UE::ConcertSharedSlate::FSaveColumnVisibilitySnapshot, SaveColumnVisibilitySnapshot) SLATE_END_ARGS();` — Optional name of the default session - relevant for highlighting
- L103 _public prototype_ `void Construct(const FArguments& InArgs, TSharedRef<IConcertSessionBrowserController> InController, TSharedPtr<FText> InSearchText);` — Constructs the Browser. @param InArgs The Slate argument list. @param InController The controller used to send queries from the UI - represents controller in mode-view-controller pattern. @param[in,out] InSearchText The text to set in the search box and to remember (as output). Cannot be null.
- L106 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L107 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L110 _public prototype_ `void RefreshSessionList();`
- L111 _public function_ `bool HasAnySessions() const`
- L112 _public prototype_ `TArray<TSharedPtr<FConcertSessionTreeItem>> GetSelectedItems() const;`
- L114 _public function_ `bool IsNewButtonEnabled() const`
- L115 _public function_ `bool IsRestoreButtonEnabled() const`
- L116 _public function_ `bool IsArchiveButtonEnabled() const`
- L117 _public function_ `bool IsRenameButtonEnabled() const`
- L118 _public function_ `bool IsDeleteButtonEnabled() const`
- L121 _public function_ `void InsertNewSessionEditableRow()` — Adds row for creating new session. Exposed for other widgets, e.g. discovery overlay to create a new session.
- L123 _public function_ `void InsertRestoreSessionAsEditableRow(const TSharedPtr<FConcertSessionTreeItem>& ArchivedItem)` — Creates row under the given (archived) session with which session can be restored.
- L134 _private prototype_ `TSharedRef<SWidget> MakeBrowserContent(const FArguments& InArgs);` — Layout the 'session|details' split view.
- L136 _private prototype_ `void OnGetChildren(TSharedPtr<FConcertTreeItem> InItem, TArray<TSharedPtr<FConcertTreeItem>>& OutChildren);`
- L139 _private prototype_ `TSharedRef<SWidget> MakeControlBar(const FArguments& InArgs);` — Layout the sessions view and controls.
- L140 _private prototype_ `TSharedRef<SWidget> MakeButtonBar(const FArguments& InArgs);`
- L141 _private prototype_ `TSharedRef<SWidget> MakeSessionTableView(const FArguments& InArgs);`
- L142 _private prototype_ `TSharedRef<SWidget> MakeSessionTableFooter();`
- L143 _private prototype_ `TSharedRef<ITableRow> OnGenerateSessionRowWidget(TSharedPtr<FConcertTreeItem> Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L146 _private prototype_ `TSharedRef<ITableRow> MakeActiveSessionRowWidget(const TSharedPtr<FConcertSessionTreeItem>& ActiveItem, const TSharedRef<STableViewBase>& OwnerTable);` — Creates row widgets for session list view, validates user inputs and forward user requests for processing to a delegate function implemented by this class.
- L147 _private prototype_ `TSharedRef<ITableRow> MakeArchivedSessionRowWidget(const TSharedPtr<FConcertSessionTreeItem>& ArchivedItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L148 _private prototype_ `TSharedRef<ITableRow> MakeNewSessionRowWidget(const TSharedPtr<FConcertSessionTreeItem>& NewItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L149 _private prototype_ `TSharedRef<ITableRow> MakeRestoreSessionRowWidget(const TSharedPtr<FConcertSessionTreeItem>& RestoreItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L150 _private prototype_ `TSharedRef<ITableRow> MakeSaveSessionRowWidget(const TSharedPtr<FConcertSessionTreeItem>& ArchivedItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L151 _private prototype_ `TSharedRef<ITableRow> MakeGroupRowWidget(const TSharedPtr<FConcertTreeItem>& GroupItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L154 _private prototype_ `TSharedPtr<SWidget> MakeTableContextualMenu();` — Creates the contextual menu when right clicking a session list view row.
- L155 _private prototype_ `TSharedRef<SWidget> MakeViewOptionsComboButtonMenu();`
- L158 _private prototype_ `bool IsNewButtonEnabledInternal() const;` — The buttons above the session view.
- L159 _private prototype_ `bool IsRestoreButtonEnabledInternal() const;`
- L160 _private prototype_ `bool IsArchiveButtonEnabledInternal() const;`
- L161 _private prototype_ `bool IsRenameButtonEnabledInternal() const;`
- L162 _private prototype_ `bool IsDeleteButtonEnabledInternal() const;`
- L163 _private prototype_ `FReply OnNewButtonClicked();`
- L164 _private prototype_ `FReply OnRestoreButtonClicked();`
- L165 _private prototype_ `FReply OnArchiveButtonClicked();`
- L166 _private prototype_ `FReply OnDeleteButtonClicked();`
- L167 _private prototype_ `void OnBeginEditingSessionName(TSharedPtr<FConcertSessionTreeItem> Item);`
- L170 _private prototype_ `void OnSessionSelectionChanged(TSharedPtr<FConcertTreeItem> SelectedSession, ESelectInfo::Type SelectInfo);` — Manipulates the sessions view (the array and the UI).
- L171 _private prototype_ `void OnSessionSelectionChanged(TSharedPtr<FConcertSessionTreeItem> SelectedSession, ESelectInfo::Type SelectInfo);`
- L172 _private prototype_ `void InsertNewSessionEditableRowInternal();`
- L173 _private prototype_ `void InsertRestoreSessionAsEditableRowInternal(const TSharedPtr<FConcertSessionTreeItem>& ArchivedItem);`
- L174 _private prototype_ `void InsertArchiveSessionAsEditableRow(const TSharedPtr<FConcertSessionTreeItem>& ActiveItem);`
- L175 _private prototype_ `void InsertEditableSessionRow(TSharedPtr<FConcertSessionTreeItem> EditableItem, TSharedPtr<FConcertSessionTreeItem> ParentItem);`
- L176 _private prototype_ `void RemoveSessionRow(const TSharedPtr<FConcertSessionTreeItem>& Item);`
- L179 _private prototype_ `EColumnSortMode::Type GetColumnSortMode(const FName ColumnId) const;` — Sessions sorting. (Sorts the session view)
- L180 _private prototype_ `EColumnSortPriority::Type GetColumnSortPriority(const FName ColumnId) const;`
- L181 _private prototype_ `void OnColumnSortModeChanged(const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type InSortMode);`
- L182 _private prototype_ `void EnsureEditableParentChildOrder();`
- L185 _private prototype_ `void OnSearchTextChanged(const FText& InFilterText);` — Sessions filtering. (Filters the session view)
- L186 _private prototype_ `void OnSearchTextCommitted(const FText& InFilterText, ETextCommit::Type CommitType);`
- L187 _private prototype_ `void OnFilterMenuChecked(const FName MenuName);`
- L188 _private prototype_ `void PopulateSearchStrings(const FConcertSessionTreeItem& Item, TArray<FString>& OutSearchStrings) const;`
- L189 _private prototype_ `bool IsFilteredOut(const FConcertSessionTreeItem& Item) const;`
- L190 _private prototype_ `FText HighlightSearchText() const;`
- L193 _private prototype_ `void RequestCreateSession(const TSharedPtr<FConcertSessionTreeItem>& NewItem);` — Passes the user requests to FConcertBrowserController.
- L194 _private prototype_ `void RequestArchiveSession(const TSharedPtr<FConcertSessionTreeItem>& ActiveItem, const FString& ArchiveName);`
- L195 _private prototype_ `void RequestRestoreSession(const TSharedPtr<FConcertSessionTreeItem>& RestoreItem, const FString& SessionName);`
- L196 _private prototype_ `void RequestRenameSession(const TSharedPtr<FConcertSessionTreeItem>& RenamedItem, const FString& NewName);`
- L197 _private prototype_ `void RequestDeleteSessions(const TArray<TSharedPtr<FConcertSessionTreeItem>>& ItemsToDelete);`
- L199 _private prototype_ `TSharedPtr<IConcertSessionBrowserController> GetController() const;`
- L201 _private prototype_ `bool IsGroupItem(const TSharedPtr<FConcertTreeItem>& TreeItem) const;`
- L204 _private prototype_ `void ResetSessions();` — Modifying sessions arrays
- L205 _private prototype_ `void AddSession(TSharedPtr<FConcertSessionTreeItem> Session);`
- L206 _private prototype_ `void InsertSessionAtBeginning(TSharedPtr<FConcertSessionTreeItem> NewSession);`
- L207 _private prototype_ `void InsertSessionAfterParent(TSharedPtr<FConcertSessionTreeItem> NewSession, TSharedPtr<FConcertSessionTreeItem> Parent);`
- L208 _private prototype_ `EInsertPosition InsertSessionAfterParentIfAvailableOrAtBeginning(TSharedPtr<FConcertSessionTreeItem> NewSession, TSharedPtr<FConcertSessionTreeItem> Parent);`
- L209 _private prototype_ `void RemoveSession(TSharedPtr<FConcertSessionTreeItem> Session);`
- L210 _private prototype_ `void SortSessionList();`
- L215 _private member_ `TWeakPtr<IConcertSessionBrowserController> Controller;` — Gives access to the concert data (servers, sessions, clients, etc).
- L218 _private member_ `UConcertSessionBrowserSettings* PersistentSettings = nullptr;` — Keeps persistent user preferences, like the filters.
- L221 _private member_ `TAttribute<FString> DefaultSessionName;` — Optional default session name - relevant for highlighting
- L223 _private member_ `TAttribute<FString> DefaultServerUrl;` — Optional default server url - relevant for highlighting
- L225 _private member_ `FExtendSessionContextMenu ExtendSessionContextMenu;`
- L227 _private member_ `FSessionDelegate OnSessionClicked;` — Called when a live or archived session is clicked
- L228 _private member_ `FSessionDelegate OnLiveSessionDoubleClicked;`
- L230 _private member_ `FSessionDelegate OnArchivedSessionDoubleClicked;` — If unset, the default behaviour is to rename the session.
- L232 _private member_ `FSessionListDelegate PostRequestedDeleteSession;` — Called after a live or archived session was requested to be deleted (it may or may not have been deleted).
- L233 _private member_ `FCanRemoveSessions AskUserToDeleteSessions;`
- L236 _private member_ `TArray<TSharedPtr<FConcertSessionTreeItem>> Sessions;` — The items displayed in the session list view. It might be filtered and sorted compared to the full list hold by the controller.
- L238 _private member_ `TSharedPtr<FConcertActiveGroupTreeItem> ActiveSessionsGroupItem;` — Groups all active sessions under it
- L240 _private member_ `TSharedPtr<FConcertArchivedGroupTreeItem> ArchivedSessionsGroupItem;` — Groups all archived sessions under it
- L242 _private member_ `TArray<TSharedPtr<FConcertTreeItem>> TreeItemSource;` — ItemSource for SessionsView containing Sessions, ActiveGroup, and ArchivedGroup
- L245 _private member_ `TSharedPtr<STreeView<TSharedPtr<FConcertTreeItem>>> SessionsView;` — The session list view.
- L246 _private member_ `TSharedPtr<SHeaderRow> SessionHeaderRow;`
- L249 _private member_ `TSharedPtr<FConcertSessionTreeItem> EditableSessionRow;` — The item corresponding to a row used to create/archive/restore a session. There is only one at the time
- L250 _private member_ `TSharedPtr<FConcertSessionTreeItem> EditableSessionRowParent;` — For archive/restore, indicate which element is archived or restored.
- L253 _private member_ `EColumnSortMode::Type PrimarySortMode = EColumnSortMode::None;` — Sorting.
- L254 _private member_ `EColumnSortMode::Type SecondarySortMode = EColumnSortMode::None;`
- L255 _private member_ `FName PrimarySortedColumn;`
- L256 _private member_ `FName SecondarySortedColumn;`
- L259 _private member_ `TSharedPtr<SSearchBox> SearchBox;` — Filtering.
- L260 _private member_ `TSharedPtr<TTextFilter<const FConcertSessionTreeItem&>> SearchTextFilter;`
- L261 _private member_ `TSharedPtr<FText> SearchedText;`
- L262 _private member_ `bool bRefreshSessionFilter = true;`
- L263 _private member_ `FString LastDefaultServerUrl;`
- L266 _private member_ `TSharedPtr<SBorder> SessionDetailsView;` — Selected Session Details.
- L267 _private member_ `TSharedPtr<SExpandableArea> DetailsArea;`
- L268 _private member_ `TArray<TSharedPtr<FConcertSessionClientInfo>> Clients;`
- L269 _private member_ `TSharedPtr<SExpandableArea> ClientsArea;`

#### struct `SConcertSessionBrowser::ControlButtonExtensionHooks`  
`struct ControlButtonExtensionHooks`  
_L46-54_
- L49 _public member_ `static const FName BeforeSeparator;` — Contains: Create Session
- L51 _public member_ `static const FName Separator;` — Just separates the two
- L53 _public member_ `static const FName AfterSeparator;` — Contains: Restore, Archive, Delete

#### struct `SConcertSessionBrowser::SessionContextMenuExtensionHooks`  
`struct SessionContextMenuExtensionHooks`  
_L56-60_
- L59 _public member_ `static const FName ManageSession;` — Contains: Archive (ActiveSession), Restore (ArchivedSession), Rename, Delete

#### enum `SConcertSessionBrowser::EInsertPosition`  
`enum class EInsertPosition`  
_L127-131_
- L129 _public enumerator_ `AtBeginning`
- L130 _public enumerator_ `AfterParent`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API CONCERTSHAREDSLATE_API`
- L31 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SWidget>, FExtendSessionTable, const TSharedRef<SWidget>& );`
- L31 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SWidget>, FExtendSessionTable, const TSharedRef<SWidget>& );`
- L32 _delegate_ `DECLARE_DELEGATE_OneParam(FExtenderDelegate, FExtender&);`
- L32 _prototype_ `DECLARE_DELEGATE_OneParam(FExtenderDelegate, FExtender&);`
- L33 _delegate_ `DECLARE_DELEGATE_TwoParams(FExtendSessionContextMenu, const TSharedPtr<FConcertSessionTreeItem>&, FExtender&) DECLARE_DELEGATE_OneParam(FSessionDelegate, const TSharedPtr<FConcertSessionTreeItem>& );`
- L33 _prototype_ `DECLARE_DELEGATE_TwoParams(FExtendSessionContextMenu, const TSharedPtr<FConcertSessionTreeItem>&, FExtender&) DECLARE_DELEGATE_OneParam(FSessionDelegate, const TSharedPtr<FConcertSessionTreeItem>& );`
- L34 _delegate_ `DECLARE_DELEGATE_OneParam(FSessionDelegate, const TSharedPtr<FConcertSessionTreeItem>& );`
- L35 _delegate_ `DECLARE_DELEGATE_OneParam(FSessionListDelegate, const TArray<TSharedPtr<FConcertSessionTreeItem>>& );`
- L35 _prototype_ `DECLARE_DELEGATE_OneParam(FSessionListDelegate, const TArray<TSharedPtr<FConcertSessionTreeItem>>& );`
- L36 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FCanRemoveSessions, const TArray<TSharedPtr<FConcertSessionTreeItem>>& );`
- L36 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FCanRemoveSessions, const TArray<TSharedPtr<FConcertSessionTreeItem>>& );`

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Session/History/AbstractSessionHistoryController.h` (Public)


#### class `FAbstractSessionHistoryController`  
`class FAbstractSessionHistoryController : public TSharedFromThis<FAbstractSessionHistoryController>`  
_L19-48_
- inherits: `TSharedFromThis<FAbstractSessionHistoryController>`
- desc: Acts as controller of SSessionHistory in model-view-component pattern.
- L23 _public prototype_ `FAbstractSessionHistoryController(SSessionHistory::FArguments Arguments = SSessionHistory::FArguments());`
- L24 _public prototype_ `virtual ~FAbstractSessionHistoryController() = default;`
- L27 _public prototype_ `void ReloadActivities();` — Fetches activities from the server and updates the list view.
- L29 _public function_ `const TSharedRef<SSessionHistory>& GetSessionHistory() const`
- L34 _protected prototype_ `virtual void GetActivities(int64 MaximumNumberOfActivities, TMap<FGuid, FConcertClientInfo>& EndpointClientInfoMap, TArray<FConcertSessionActivity>& FetchedActivities) const = 0;` — Gets the latest activities
- L37 _protected prototype_ `virtual bool GetPackageEvent(const FConcertSessionActivity& Activity, FConcertSyncPackageEventMetaData& OutPackageEvent) const = 0;` — Returns the specified package event (without the package data itself) if available.
- L40 _protected prototype_ `virtual TFuture<TOptional<FConcertSyncTransactionEvent>> GetTransactionEvent(const FConcertSessionActivity& Activity) const = 0;` — Returns the specified package event if available.
- L45 _private member_ `TSharedRef<SSessionHistory> SessionHistory;` — The widget being managed
- L47 _private prototype_ `TSharedRef<SSessionHistory> MakeSessionHistory(SSessionHistory::FArguments Arguments) const;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CONCERTSHAREDSLATE_API`

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Session/History/SEditableSessionHistory.h` (Public)


#### struct `FCanPerformActionResult`  
`struct FCanPerformActionResult`  
_L15-27_
- L17 _public member_ `TOptional<FText> DeletionReason;`
- L19 _public function_ `static FCanPerformActionResult Yes()`
- L20 _public function_ `static FCanPerformActionResult No(FText Reason)`
- L22 _public function_ `bool CanPerformAction() const`
- L24 _public function_ `explicit FCanPerformActionResult(TOptional<FText> DeletionReason = {}) : DeletionReason(DeletionReason)`

#### class `SEditableSessionHistory`  
`class SEditableSessionHistory : public SCompoundWidget`  
_L30-90_
- inherits: `SCompoundWidget`
- desc: Allows activities in the session history to be deleted.
- L34 _public function_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SSessionHistory>, FMakeSessionHistory, SSessionHistory::FArguments) DECLARE_DELEGATE_RetVal_OneParam(FCanPerformActionResult, FCanPerformActionOnActivities, const TSet<TSharedRef<FConcertSessionActivity>>& ) DECLARE_DELEGATE_OneParam(FRequestActivitiesAction, const TSet<TSharedRef<FConcertSessionActivity>>&) SLATE_BEGIN_ARGS(SEditableSessionHistory)`
- L40 _public prototype_ `SLATE_EVENT(FMakeSessionHistory, MakeSessionHistory) SLATE_EVENT(FCanPerformActionOnActivities, CanDeleteActivities) SLATE_EVENT(FRequestActivitiesAction, DeleteActivities) SLATE_EVENT(FCanPerformActionOnActivities, CanMuteActivities) SLATE_EVENT(FRequestActivitiesAction, MuteActivities) SLATE_EVENT(FCanPerformActionOnActivities, CanUnmuteActivities) SLATE_EVENT(FRequestActivitiesAction, UnmuteActivities) SLATE_NAMED_SLOT(FArguments, StatusBar) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L61 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L66 _private member_ `TSharedPtr<SSessionHistory> SessionHistory;`
- L68 _private member_ `FCanPerformActionOnActivities CanDeleteActivitiesFunc;`
- L69 _private member_ `FRequestActivitiesAction DeleteActivitiesFunc;`
- L70 _private member_ `FCanPerformActionOnActivities CanMuteActivitiesFunc;`
- L71 _private member_ `FRequestActivitiesAction MuteActivitiesFunc;`
- L72 _private member_ `FCanPerformActionOnActivities CanUnmuteActivitiesFunc;`
- L73 _private member_ `FRequestActivitiesAction UnmuteActivitiesFunc;`
- L75 _private prototype_ `TSharedPtr<SWidget> OnContextMenuOpening();`
- L77 _private prototype_ `FReply OnClickDeleteActivitiesButton() const;`
- L78 _private prototype_ `FText GetDeleteActivitiesToolTip() const;`
- L79 _private prototype_ `bool IsDeleteButtonEnabled() const;`
- L81 _private prototype_ `FReply OnClickMuteActivitesButton() const;`
- L82 _private prototype_ `FText GetMuteActivitiesToolTip() const;`
- L83 _private prototype_ `bool IsMuteButtonEnabled() const;`
- L85 _private prototype_ `FReply OnClickUnmuteActivitesButton() const;`
- L86 _private prototype_ `FText GetUnmuteActivitiesToolTip() const;`
- L87 _private prototype_ `bool IsUnmuteButtonEnabled() const;`
- L89 _private prototype_ `FText GenerateTooltip(const FCanPerformActionOnActivities& CanPerformAction, FText SelectActivityToolTip, FText PerformActionToolTipFmt, FText CannotPerformActionToolTipFmt) const;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CONCERTSHAREDSLATE_API`
- L34 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SSessionHistory>, FMakeSessionHistory, SSessionHistory::FArguments) DECLARE_DELEGATE_RetVal_OneParam(FCanPerformActionResult, FCanPerformActionOnActivities, const TSet<TSharedRef<FConcertSessionActivity>>& ) DECLARE_DELEGATE_OneParam(FRequestActivitiesAction, const TSet<TSharedRef<FConcertSessionActivity>>&) SLATE_BEGIN_ARGS(SEditableSessionHistory) {} SLATE_EVENT(FMakeSessionHistory, MakeSessionHistory) SLATE_EVENT(FCanPerformActionOnActivities, CanDeleteActivities) SLATE_EVENT(FRequestActivitiesAction, DeleteActivities) SLATE_EVENT(FCanPerformActionOnActivities, CanMuteActivities) SLATE_EVENT(FRequestActivitiesAction, MuteActivities) SLATE_EVENT(FCanPerformActionOnActivities, CanUnmuteActivities) SLATE_EVENT(FRequestActivitiesAction, UnmuteActivities) SLATE_NAMED_SLOT(FArguments, StatusBar) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L35 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FCanPerformActionResult, FCanPerformActionOnActivities, const TSet<TSharedRef<FConcertSessionActivity>>& ) DECLARE_DELEGATE_OneParam(FRequestActivitiesAction, const TSet<TSharedRef<FConcertSessionActivity>>&) SLATE_BEGIN_ARGS(SEditableSessionHistory) {} SLATE_EVENT(FMakeSessionHistory, MakeSessionHistory) SLATE_EVENT(FCanPerformActionOnActivities, CanDeleteActivities) SLATE_EVENT(FRequestActivitiesAction, DeleteActivities) SLATE_EVENT(FCanPerformActionOnActivities, CanMuteActivities) SLATE_EVENT(FRequestActivitiesAction, MuteActivities) SLATE_EVENT(FCanPerformActionOnActivities, CanUnmuteActivities) SLATE_EVENT(FRequestActivitiesAction, UnmuteActivities) SLATE_NAMED_SLOT(FArguments, StatusBar) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L36 _delegate_ `DECLARE_DELEGATE_OneParam(FRequestActivitiesAction, const TSet<TSharedRef<FConcertSessionActivity>>&) SLATE_BEGIN_ARGS(SEditableSessionHistory) {} SLATE_EVENT(FMakeSessionHistory, MakeSessionHistory) SLATE_EVENT(FCanPerformActionOnActivities, CanDeleteActivities) SLATE_EVENT(FRequestActivitiesAction, DeleteActivities) SLATE_EVENT(FCanPerformActionOnActivities, CanMuteActivities) SLATE_EVENT(FRequestActivitiesAction, MuteActivities) SLATE_EVENT(FCanPerformActionOnActivities, CanUnmuteActivities) SLATE_EVENT(FRequestActivitiesAction, UnmuteActivities) SLATE_NAMED_SLOT(FArguments, StatusBar) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Session/History/SSessionHistory.h` (Public)


#### class `SSessionHistory`  
`class SSessionHistory : public SCompoundWidget`  
_L22-138_
- inherits: `SCompoundWidget`
- desc: Wraps a session table list with a search box and a status bar for visibility settings (show connection activities, etc.).
- L26 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FAllowActivity, const FConcertSyncActivity&, const TStructOnScope<FConcertSyncActivitySummary>&) static constexpr int64 MaximumNumberOfActivities = 1000;`
- L31 _public function_ `SLATE_BEGIN_ARGS(SSessionHistory) : _Columns({ UE::ConcertSharedSlate::ActivityColumn::AvatarColor(), UE::ConcertSharedSlate::ActivityColumn::ClientName(), UE::ConcertSharedSlate::ActivityColumn::Operation() }) , _DetailsAreaVisibility(EVisibility::Visible) , _SelectionMode(ESelectionMode::Single) , _DarkenMutedActivities(true)`
- L42 _public prototype_ `SLATE_EVENT(SConcertSessionActivities::FGetPackageEvent, GetPackageEvent) SLATE_EVENT(SConcertSessionActivities::FGetTransactionEvent, GetTransactionEvent) SLATE_EVENT(FOnContextMenuOpening, OnContextMenuOpening) SLATE_ARGUMENT(FName, PackageFilter) SLATE_EVENT(FAllowActivity, AllowActivity) /** Optional. The columns to show for each activity;`
- L90 _public prototype_ `void ReloadActivities(TMap<FGuid, FConcertClientInfo> EndpointClientInfoMap, TArray<FConcertSessionActivity> FetchedActivities);` — Fetches activities from the server and updates the list view.
- L93 _public prototype_ `void HandleActivityAddedOrUpdated(const FConcertClientInfo& InClientInfo, const FConcertSyncActivity& InActivity, const FStructOnScope& InActivitySummary);` — Callback for handling the a new or updated activity item.
- L95 _public function_ `bool IsLastColumn(FName ColumnId) const`
- L97 _public prototype_ `TSet<TSharedRef<FConcertSessionActivity>> GetSelectedActivities() const;`
- L98 _public function_ `const TArray<TSharedPtr<FConcertSessionActivity>>& GetActivities() const`
- L99 _public function_ `void SetSelectedActivities(const TArray<TSharedPtr<FConcertSessionActivity>>& ActivitiesToSelect)`
- L101 _public prototype_ `void OnColumnVisibilitySettingsChanged(const FColumnVisibilitySnapshot& ColumnSnapshot);`
- L106 _private prototype_ `void OnSearchTextChanged(const FText& InSearchText);` — Invoked when the text in the search box widget changes.
- L109 _private prototype_ `void OnSearchTextCommitted(const FText& InFilterText, ETextCommit::Type CommitType);` — Invoked when the text in the search box widget is committed.
- L112 _private prototype_ `FText HighlightSearchedText() const;` — Returns the text to highlight when the search bar has a text set.
- L117 _private member_ `TMap<FGuid, FConcertClientInfo> EndpointClientInfoMap;` — Holds the map of endpoint IDs to client info.
- L120 _private member_ `TMap<int64, TSharedPtr<FConcertSessionActivity>> ActivityMap;` — Holds the map of activity IDs to Concert activities.
- L123 _private member_ `TSharedPtr<SConcertSessionActivities> ActivityListView;` — Display the activity list.
- L126 _private member_ `TSharedPtr<FConcertSessionActivitiesOptions> ActivityListViewOptions;` — Controls the activity list view options
- L129 _private member_ `TSharedPtr<SSearchBox> SearchBox;` — The widget used to enter the text to search.
- L132 _private member_ `FText SearchedText;` — The searched text to highlight.
- L135 _private member_ `FAllowActivity AllowActivityFunc;` — Used to limit activities.
- L137 _private prototype_ `TOptional<FConcertClientInfo> GetClientInfo(FGuid Guid) const;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CONCERTSHAREDSLATE_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L26 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FAllowActivity, const FConcertSyncActivity&, const TStructOnScope<FConcertSyncActivitySummary>&) static constexpr int64 MaximumNumberOfActivities = 1000;`

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Session/History/SSessionHistoryWrapper.h` (Public)


#### class `SSessionHistoryWrapper`  
`class SSessionHistoryWrapper : public SCompoundWidget`  
_L14-27_
- inherits: `SCompoundWidget`
- desc: Shows a SSessionHistory widget - keeping alive the controller as long as this widget lives. Useful for closeable tabs.
- L18 _public function_ `SLATE_BEGIN_ARGS(SSessionHistoryWrapper)`
- L19 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FAbstractSessionHistoryController> InController);`
- L26 _private member_ `TSharedPtr<FAbstractSessionHistoryController> Controller;` — Manages SessionHistory

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CONCERTSHAREDSLATE_API`

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Widgets/Client/ClientInfoDelegate.h` (Public)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L13 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsLocalClient, const FGuid& ClientId);`
- L13 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsLocalClient, const FGuid& ClientId);` (scope `UE::ConcertSharedSlate`)
- L14 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TOptional<FConcertClientInfo>, FGetOptionalClientInfo, const FGuid& ClientEndpointId);`
- L14 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TOptional<FConcertClientInfo>, FGetOptionalClientInfo, const FGuid& ClientEndpointId);` (scope `UE::ConcertSharedSlate`)
- L19 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FGetClientParenthesesContent, const FGuid& ClientId);` — Used by SHorizontalList to determine what should go in the parentheses behind the display name, e.g. "Display Name (You)". Return FText::GetEmpty() if nothing should go into the parentheses.
- L19 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FGetClientParenthesesContent, const FGuid& ClientId);` (scope `UE::ConcertSharedSlate`) — Used by SHorizontalList to determine what should go in the parentheses behind the display name, e.g. "Display Name (You)". Return FText::GetEmpty() if nothing should go into the parentheses.
- L21 _function_ `FORCEINLINE FText EvaluateGetClientParenthesesContent(const FGetClientParenthesesContent& Getter, const FGuid& ClientId)` (scope `UE::ConcertSharedSlate`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Widgets/Client/ClientSorting.h` (Public)


#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L20 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FClientSortPredicate, const FConcertSessionClientInfo& Left, const FConcertSessionClientInfo& Right );`
- L20 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FClientSortPredicate, const FConcertSessionClientInfo& Left, const FConcertSessionClientInfo& Right );` (scope `UE::ConcertSharedSlate`)
- L36 _function_ `inline bool SortSpecifiedParenthesesFirstThenThenAlphabetical( const FConcertSessionClientInfo& Left, const FConcertSessionClientInfo& Right, const FGetClientParenthesesContent& GetClientParenthesesContent, const FText& ParenthesesContentToPlaceFirst )` (scope `UE::ConcertSharedSlate`) — Predicate for sorting everything that has ParenthesesContentToPlaceFirst first, and then sorts everything alphabetically. This is supposed to be used with SHorizontalClientList. Example input list: ["AClient", "BClient", "ZClient(You)"] Example output list sorted by ParenthesesContentToPlaceFirst == "You": ZClient(You), AClient, BClient
- L52 _function_ `inline bool SortLocalClientParenthesesFirstThenThenAlphabetical( const FConcertSessionClientInfo& Left, const FConcertSessionClientInfo& Right, const FGetClientParenthesesContent& GetClientParenthesesContent )` (scope `UE::ConcertSharedSlate`) — Sorts anything that has "You" in the parentheses first.

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Widgets/Client/SClientName.h` (Public)


#### class `UE::ConcertSharedSlate::SClientName`  
`class SClientName : public SCompoundWidget`  
_L33-73_
- inherits: `SCompoundWidget`
- desc: Knows how to display FConcertClientInfo. The widget looks like this: []DisplayName(ParenthesesContent) - [] is a square displaying the avatar colour (optional) - DisplayName is FConcertClientInfo::DisplayName - ParenthesesContent is additional info you can supply, like "You" (optional). See ParenthesesClientNameContent.
- L37 _public function_ `SLATE_BEGIN_ARGS(SClientName) : _DisplayAvatarColor(true) , _Font(FAppStyle::Get().GetFontStyle("BoldFont"))`
- L42 _public prototype_ `SLATE_ATTRIBUTE(TOptional<FConcertClientInfo>, ClientInfo) SLATE_ATTRIBUTE(FText, ParenthesisContent) SLATE_ATTRIBUTE(bool, DisplayAvatarColor) SLATE_ATTRIBUTE(FText, HighlightText) SLATE_ARGUMENT(FSlateFontInfo, Font) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The client info to display.
- L58 _public prototype_ `static FText GetDisplayText(const FConcertClientInfo& Info, bool bDisplayAsLocalClient);` — @return The display that would be used given the settings.
- L60 _public prototype_ `static FText GetDisplayText(const FConcertClientInfo& Info, const FText& ParenthesesContent = FText::GetEmpty());` — @return The display that would be used given the settings.
- L65 _private member_ `TAttribute<TOptional<FConcertClientInfo>> ClientInfoAttribute;` — The client info to display.
- L67 _private member_ `TAttribute<FText> ParenthesisContentAttribute;` — Content to display behind the display name in parentheses.
- L70 _private prototype_ `FText GetClientDisplayName() const;` — Gets the display name.
- L72 _private prototype_ `FSlateColor GetAvatarColor() const;` — Gets the avatar color

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CONCERTSHAREDSLATE_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L15 _namespace_ `namespace ParenthesesClientNameContent` (scope `UE::ConcertSharedSlate`)
- L18 _externvar_ `extern const FText LocalClient;` (scope `UE::ConcertSharedSlate::ParenthesesClientNameContent`) — The client corresponds to the local user. "You" is appended to name, e.g. "ClientName(You)".
- L20 _externvar_ `extern const FText OfflineClient;` (scope `UE::ConcertSharedSlate::ParenthesesClientNameContent`) — The client corresponds to a client that is not connected to the session.
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Widgets/Client/SHorizontalClientList.h` (Public)


#### class `UE::ConcertSharedSlate::SHorizontalClientList`  
`class SHorizontalClientList : public SCompoundWidget`  
_L23-88_
- inherits: `SCompoundWidget`
- desc: Aligns client widgets from left to right. If there is not enough space, a horizontal scroll bar cuts of the list.
- L28 _public prototype_ `static TOptional<FString> GetDisplayString( const TConstArrayView<FGuid>& Clients, const FGetOptionalClientInfo& GetClientInfoDelegate, const FClientSortPredicate& SortPredicate, const FGetClientParenthesesContent& GetClientParenthesesContent = {} );` — @return The display string a SHorizontalClientList would display with the given state. Returns unset optional if EmptyListSlot would be shown.
- L35 _public function_ `SLATE_BEGIN_ARGS(SHorizontalClientList) : _Font(FAppStyle::Get().GetFontStyle("NormalFont"))`
- L39 _public prototype_ `SLATE_EVENT(ConcertSharedSlate::FGetClientParenthesesContent, GetClientParenthesesContent) SLATE_EVENT(ConcertSharedSlate::FGetOptionalClientInfo, GetClientInfo) SLATE_ATTRIBUTE(bool, DisplayAvatarColor) SLATE_ATTRIBUTE(FText, HighlightText) SLATE_ARGUMENT(FSlateFontInfo, Font) SLATE_EVENT(FClientSortPredicate, SortPredicate) SLATE_ATTRIBUTE(FText, ListToolTipText) SLATE_NAMED_SLOT(FArguments, EmptyListSlot) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — Gets the content to place in parentheses behind the given client.
- L65 _public prototype_ `void RefreshList(const TConstArrayView<FGuid>& Clients) const;` — Refreshes the list.
- L70 _private member_ `FGetClientParenthesesContent GetClientParenthesesContentDelegate;` — Gets the content to place in parentheses behind the given client.
- L72 _private member_ `FGetOptionalClientInfo GetClientInfoDelegate;` — Used to get client display info for remote clients.
- L74 _private member_ `FClientSortPredicate SortPredicateDelegate;` — Sorts the client list
- L77 _private member_ `TAttribute<bool> ShouldDisplayAvatarColorAttribute;` — Whether the square in front of the client name should be displayed.
- L79 _private member_ `TAttribute<FText> HighlightTextAttribute;` — Used for highlighting in the text
- L82 _private member_ `FSlateFontInfo NameFont;` — The font to use for the names
- L85 _private member_ `TSharedPtr<SWidgetSwitcher> WidgetSwitcher;` — Displays the ScrollBox when there are clients and the EmptyListSlot otherwise.
- L87 _private member_ `TSharedPtr<SScrollBox> ScrollBox;` — Contains the children.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CONCERTSHAREDSLATE_API`
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Widgets/Client/SLocalClientName.h` (Public)


#### class `UE::ConcertSharedSlate::SLocalClientName`  
`class SLocalClientName : public SCompoundWidget`  
_L23-43_
- inherits: `SCompoundWidget`
- desc: Displays the name of a client. The name will look like "Client Name (me)". @see SRemoteClientName
- L27 _public function_ `SLATE_BEGIN_ARGS(SLocalClientName) : _Font(FAppStyle::Get().GetFontStyle("BoldFont"))`
- L31 _public prototype_ `SLATE_ATTRIBUTE(TOptional<FConcertClientInfo>, DisplayInfo) SLATE_ATTRIBUTE(bool, DisplayAvatarColor) SLATE_ATTRIBUTE(FText, HighlightText) SLATE_ARGUMENT(FSlateFontInfo, Font) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The client info to display.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CONCERTSHAREDSLATE_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)

### `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Widgets/Client/SRemoteClientName.h` (Public)


#### class `UE::ConcertSharedSlate::SRemoteClientName`  
`class SRemoteClientName : public SCompoundWidget`  
_L26-59_
- inherits: `SCompoundWidget`
- desc: Displays the name of a client. The name will look like "Client Name". @see SLocalClientName If the client disconnects, the last known info is used. If the client info is unknown, the widget will display an empty FConcertClientInfo;
- L30 _public function_ `SLATE_BEGIN_ARGS(SRemoteClientName) : _Font(FAppStyle::Get().GetFontStyle("BoldFont"))`
- L34 _public prototype_ `SLATE_ATTRIBUTE(TOptional<FConcertClientInfo>, DisplayInfo) SLATE_ATTRIBUTE(bool, DisplayAvatarColor) SLATE_ATTRIBUTE(FText, HighlightText) SLATE_ARGUMENT(FSlateFontInfo, Font) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The client info to display.
- L50 _private member_ `TAttribute<TOptional<FConcertClientInfo>> ClientDisplayInfo;` — The endpoint ID of the client to display.
- L56 _private member_ `mutable TOptional<FConcertClientInfo> LastKnownClientInfo;` — Cached so that the info remains known when the client disconnects. Must be mutable because TAttribute::CreateSP requires GetClientInfo to be const.
- L58 _private prototype_ `TOptional<FConcertClientInfo> GetClientInfo() const;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CONCERTSHAREDSLATE_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
