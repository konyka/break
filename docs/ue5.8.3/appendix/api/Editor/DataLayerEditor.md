# Editor / DataLayerEditor

- module root: `Source/Editor/DataLayerEditor`
- headers: 24; symbols: 545
- symbol kinds: class=20, delegate=14, enum=2, enumerator=8, function=122, macro=3, member=82, namespace=1, prototype=279, struct=10, typedef=4
- PrivateDependencyModuleNames: AssetTools, ContentBrowserData, Core, CoreUObject, EditorFramework, EditorSubsystem, EditorWidgets, Engine, InputCore, PropertyEditor, SceneOutliner, Slate, SlateCore, ToolMenus, UnrealEd

### `Source/Editor/DataLayerEditor/Private/DataLayer/DataLayerActorTreeItem.h` (Private)


#### struct `FDataLayerActorTreeItemData`  
`struct FDataLayerActorTreeItemData`  
_L19-27_
- L21 _public function_ `FDataLayerActorTreeItemData(AActor* InActor, UDataLayerInstance* InDataLayerInstance) : Actor(InActor) , DataLayerInstance(InDataLayerInstance)`
- L25 _public member_ `TWeakObjectPtr<AActor> Actor;`
- L26 _public member_ `TWeakObjectPtr<UDataLayerInstance> DataLayerInstance;`

#### struct `FDataLayerActorTreeItem`  
`struct FDataLayerActorTreeItem : public FActorTreeItem`  
_L32-107_
- inherits: `FActorTreeItem`
- L35 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FFilterPredicate, const AActor*, const UDataLayerInstance* InDataLayerInstance);`
- L36 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FInteractivePredicate, const AActor*, const UDataLayerInstance* InDataLayerInstance);`
- L38 _public function_ `FDataLayerActorTreeItem(const FDataLayerActorTreeItemData& InData) : FActorTreeItem(InData.Actor.Get()) , DataLayerInstance(InData.DataLayerInstance) , IDDataLayerActor(FDataLayerActorTreeItem::ComputeTreeItemID(Actor.Get(), DataLayerInstance.Get()))`
- L46 _public function_ `UDataLayerInstance* GetDataLayer() const`
- L48 _public function_ `const AActor* GetActor() const`
- L49 _public function_ `AActor* GetActor()`
- L51 _public function_ `static FSceneOutlinerTreeItemID ComputeTreeItemID(AActor* InActor, const UDataLayerInstance* InDataLayerInstance)`
- L62 _public function_ `bool Filter(FFilterPredicate Pred) const`
- L67 _public function_ `bool GetInteractiveState(FInteractivePredicate Pred) const`
- L73 _public function_ `virtual bool IsValid() const override` — Begin ISceneOutlinerTreeItem Implementation
- L74 _public function_ `virtual FSceneOutlinerTreeItemID GetID() const override`
- L75 _public function_ `virtual bool ShouldShowVisibilityState() const`
- L76 _public function_ `virtual bool HasVisibilityInfo() const override`
- L77 _public function_ `virtual void OnVisibilityChanged(const bool bNewVisibility) override`
- L78 _public function_ `virtual bool GetVisibility() const override`
- L83 _protected function_ `virtual void UpdateDisplayString() override`
- L90 _private function_ `void UpdateDisplayStringInternal()`
- L105 _private member_ `TWeakObjectPtr<UDataLayerInstance> DataLayerInstance;`
- L106 _private member_ `const FSceneOutlinerTreeItemID IDDataLayerActor;`

#### Free symbols / members of external scopes

- L35 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FFilterPredicate, const AActor*, const UDataLayerInstance* InDataLayerInstance);`
- L36 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FInteractivePredicate, const AActor*, const UDataLayerInstance* InDataLayerInstance);`

### `Source/Editor/DataLayerEditor/Private/DataLayer/DataLayerHierarchy.h` (Private)


#### class `FDataLayerHierarchy`  
`class FDataLayerHierarchy : public ISceneOutlinerHierarchy`  
_L25-75_
- inherits: `ISceneOutlinerHierarchy`
- L28 _public prototype_ `virtual ~FDataLayerHierarchy();`
- L29 _public prototype_ `static TUniquePtr<FDataLayerHierarchy> Create(FDataLayerMode* Mode, const TWeakObjectPtr<UWorld>& World);`
- L30 _public prototype_ `virtual void CreateItems(TArray<FSceneOutlinerTreeItemPtr>& OutItems) const override;`
- L31 _public function_ `virtual void CreateChildren(const FSceneOutlinerTreeItemPtr& Item, TArray<FSceneOutlinerTreeItemPtr>& OutChildren) const override`
- L32 _public prototype_ `virtual FSceneOutlinerTreeItemPtr FindOrCreateParentItem(const ISceneOutlinerTreeItem& Item, const TMap<FSceneOutlinerTreeItemID, FSceneOutlinerTreeItemPtr>& Items, bool bCreate = false) override;`
- L33 _public function_ `void SetShowEditorDataLayers(bool bInShowEditorDataLayers)`
- L34 _public function_ `void SetShowRuntimeDataLayers(bool bInShowRuntimeDataLayers)`
- L35 _public function_ `void SetShowDataLayerActors(bool bInShowDataLayerActors)`
- L36 _public function_ `void SetShowUnloadedActors(bool bInShowUnloadedActors)`
- L37 _public function_ `void SetShowOnlySelectedActors(bool bInbShowOnlySelectedActors)`
- L38 _public function_ `void SetHighlightSelectedDataLayers(bool bInHighlightSelectedDataLayers)`
- L39 _public function_ `void SetShowLevelInstanceContent(bool bInShowLevelInstanceContent)`
- L40 _public function_ `bool GetShowLevelInstanceContent() const`
- L42 _private prototype_ `UWorld* GetOwningWorld() const;`
- L43 _private prototype_ `FDataLayerHierarchy(FDataLayerMode* Mode, const TWeakObjectPtr<UWorld>& Worlds);`
- L44 _private prototype_ `FDataLayerHierarchy(const FDataLayerHierarchy&) = delete;`
- L45 _private prototype_ `FDataLayerHierarchy& operator=(const FDataLayerHierarchy&) = delete;`
- L47 _private prototype_ `void OnWorldPartitionCreated(UWorld* InWorld);`
- L48 _private prototype_ `void OnLevelActorsAdded(const TArray<AActor*>& InActors);`
- L49 _private prototype_ `void OnLevelActorsRemoved(const TArray<AActor*>& InActors);`
- L50 _private prototype_ `void OnLevelActorAdded(AActor* InActor);`
- L51 _private prototype_ `void OnLevelActorDeleted(AActor* InActor);`
- L52 _private prototype_ `void OnLevelActorListChanged();`
- L53 _private prototype_ `void OnWorldPartitionInitialized(UWorldPartition* InWorldPartition);`
- L54 _private prototype_ `void OnWorldPartitionUninitialized(UWorldPartition* InWorldPartition);`
- L55 _private prototype_ `void OnLevelAdded(ULevel* InLevel, UWorld* InWorld);`
- L56 _private prototype_ `void OnLevelRemoved(ULevel* InLevel, UWorld* InWorld);`
- L57 _private prototype_ `void OnLoadedActorAdded(AActor& InActor);`
- L58 _private prototype_ `void OnLoadedActorRemoved(AActor& InActor);`
- L59 _private prototype_ `void OnActorDescInstanceAdded(FWorldPartitionActorDescInstance* InActorDescInstance);`
- L60 _private prototype_ `void OnActorDescInstanceRemoved(FWorldPartitionActorDescInstance* InActorDescInstance);`
- L61 _private prototype_ `void OnActorDataLayersChanged(const TWeakObjectPtr<AActor>& InActor);`
- L62 _private prototype_ `void OnDataLayerChanged(const EDataLayerAction Action, const TWeakObjectPtr<const UDataLayerInstance>& ChangedDataLayer, const FName& ChangedProperty);`
- L63 _private prototype_ `void FullRefreshEvent();`
- L64 _private prototype_ `FSceneOutlinerTreeItemPtr CreateDataLayerTreeItem(UDataLayerInstance* InDataLayer, bool bInForce = false) const;`
- L65 _private prototype_ `bool IsDataLayerPartOfSelection(const UDataLayerInstance* DataLayer) const;`
- L67 _private member_ `TWeakObjectPtr<UWorld> RepresentingWorld;`
- L68 _private member_ `bool bShowEditorDataLayers;`
- L69 _private member_ `bool bShowRuntimeDataLayers;`
- L70 _private member_ `bool bShowDataLayerActors;`
- L71 _private member_ `bool bShowUnloadedActors;`
- L72 _private member_ `bool bShowOnlySelectedActors;`
- L73 _private member_ `bool bHighlightSelectedDataLayers;`
- L74 _private member_ `bool bShowLevelInstanceContent;`

### `Source/Editor/DataLayerEditor/Private/DataLayer/DataLayerInstanceCustomization.h` (Private)


#### class `FDataLayerInstanceDetails`  
`class FDataLayerInstanceDetails : public IDetailCustomization`  
_L13-25_
- inherits: `IDetailCustomization`
- L17 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L20 _protected function_ `FDataLayerInstanceDetails()`
- L24 _private prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface

### `Source/Editor/DataLayerEditor/Private/DataLayer/DataLayerMode.h` (Private)


#### struct `FDataLayerModeParams`  
`struct FDataLayerModeParams`  
_L47-57_
- L49 _public function_ `FDataLayerModeParams()`
- L51 _public prototype_ `FDataLayerModeParams(SSceneOutliner* InSceneOutliner, SDataLayerBrowser* InDataLayerBrowser, const TWeakObjectPtr<UWorld>& InSpecifiedWorldToDisplay = nullptr, FOnSceneOutlinerItemPicked InOnItemPicked = FOnSceneOutlinerItemPicked());`
- L53 _public member_ `TWeakObjectPtr<UWorld> SpecifiedWorldToDisplay = nullptr;`
- L54 _public member_ `SDataLayerBrowser* DataLayerBrowser;`
- L55 _public member_ `SSceneOutliner* SceneOutliner;`
- L56 _public member_ `FOnSceneOutlinerItemPicked OnItemPicked;`

#### class `FDataLayerMode`  
`class FDataLayerMode : public ISceneOutlinerMode`  
_L65-201_
- inherits: `ISceneOutlinerMode`
- L75 _public prototype_ `FDataLayerMode(const FDataLayerModeParams& Params);`
- L76 _public prototype_ `virtual ~FDataLayerMode();`
- L78 _public prototype_ `virtual void Rebuild() override;`
- L79 _public prototype_ `virtual TSharedPtr<SWidget> CreateContextMenu() override;`
- L80 _public prototype_ `virtual void InitializeViewMenuExtender(TSharedPtr<FExtender> Extender) override;`
- L81 _public prototype_ `virtual int32 GetTypeSortPriority(const ISceneOutlinerTreeItem& Item) const override;`
- L82 _public function_ `virtual ESelectionMode::Type GetSelectionMode() const override`
- L83 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L84 _public function_ `virtual bool IsInteractive() const override`
- L85 _public function_ `virtual bool CanRename() const override`
- L86 _public prototype_ `virtual bool CanRenameItem(const ISceneOutlinerTreeItem& Item) const override;`
- L87 _public function_ `virtual bool CanCustomizeToolbar() const`
- L88 _public function_ `virtual bool ShowStatusBar() const override`
- L89 _public function_ `virtual bool ShowViewButton() const override`
- L90 _public function_ `virtual bool ShowFilterOptions() const override`
- L91 _public prototype_ `virtual FText GetStatusText() const override;`
- L92 _public function_ `virtual FSlateColor GetStatusTextColor() const override`
- L93 _public prototype_ `virtual FFolder::FRootObject GetRootObject() const override;`
- L95 _public prototype_ `virtual void SynchronizeSelection() override;`
- L96 _public prototype_ `virtual void OnItemDoubleClick(FSceneOutlinerTreeItemPtr Item) override;`
- L97 _public prototype_ `virtual void OnItemAdded(FSceneOutlinerTreeItemPtr Item) override;`
- L98 _public prototype_ `virtual void OnItemRemoved(FSceneOutlinerTreeItemPtr Item) override;`
- L99 _public prototype_ `virtual void OnItemPassesFilters(const ISceneOutlinerTreeItem& Item) override;`
- L100 _public prototype_ `virtual FReply OnKeyDown(const FKeyEvent& InKeyEvent) override;`
- L101 _public prototype_ `virtual void OnItemSelectionChanged(FSceneOutlinerTreeItemPtr TreeItem, ESelectInfo::Type SelectionType, const FSceneOutlinerItemSelection& Selection) override;`
- L103 _public function_ `virtual bool CanSupportDragAndDrop() const`
- L104 _public prototype_ `virtual bool ParseDragDrop(FSceneOutlinerDragDropPayload& OutPayload, const FDragDropOperation& Operation) const override;`
- L105 _public prototype_ `virtual FSceneOutlinerDragValidationInfo ValidateDrop(const ISceneOutlinerTreeItem& DropTarget, const FSceneOutlinerDragDropPayload& Payload) const override;`
- L106 _public prototype_ `virtual void OnDrop(ISceneOutlinerTreeItem& DropTarget, const FSceneOutlinerDragDropPayload& Payload, const FSceneOutlinerDragValidationInfo& ValidationInfo) const override;`
- L107 _public prototype_ `virtual TSharedPtr<FDragDropOperation> CreateDragDropOperation(const FPointerEvent& MouseEvent, const TArray<FSceneOutlinerTreeItemPtr>& InTreeItems) const override;`
- L108 _public prototype_ `virtual FReply OnDragOverItem(const FDragDropEvent& Event, const ISceneOutlinerTreeItem& Item) const override;`
- L110 _public prototype_ `void DeleteItems(const TArray<TWeakPtr<ISceneOutlinerTreeItem>>& Items);`
- L111 _public prototype_ `SDataLayerBrowser* GetDataLayerBrowser() const;`
- L113 _public prototype_ `void BuildWorldPickerMenu(FMenuBuilder& MenuBuilder);`
- L116 _protected prototype_ `virtual TUniquePtr<ISceneOutlinerHierarchy> CreateHierarchy() override;`
- L119 _protected member_ `bool bHideEditorDataLayers;` — Should Editor DataLayers be hidden
- L121 _protected member_ `bool bHideRuntimeDataLayers;` — Should Runtime DataLayers be hidden
- L123 _protected member_ `bool bHideDataLayerActors;` — Should DataLayers actors be hidden
- L125 _protected member_ `bool bHideUnloadedActors;` — Should unloaded actors be hidden
- L127 _protected member_ `bool bShowOnlySelectedActors;` — Should show only selected actors
- L129 _protected member_ `bool bHighlightSelectedDataLayers;` — Should highlight DataLayers containing selected actors
- L131 _protected member_ `bool bHideLevelInstanceContent;` — Should level instance actors content be hidden
- L134 _protected member_ `FOnSceneOutlinerItemPicked OnItemPicked;` — Delegate to call when an item is picked
- L138 _private prototype_ `void RegisterContextMenu();` — Private Helpers
- L139 _private prototype_ `void ChooseRepresentingWorld();`
- L140 _private prototype_ `void OnSelectWorld(TWeakObjectPtr<UWorld> World);`
- L141 _private prototype_ `bool IsWorldChecked(TWeakObjectPtr<UWorld> World) const;`
- L142 _private prototype_ `TArray<FDataLayerActorMoveElement> GetDataLayerActorPairsFromOperation(const FDragDropOperation& Operation) const;`
- L143 _private prototype_ `TArray<AActor*> GetActorsFromOperation(const FDragDropOperation& Operation, bool bOnlyFindFirst = false) const;`
- L144 _private prototype_ `TArray<UDataLayerInstance*> GetDataLayerInstancesFromOperation(const FDragDropOperation& Operation, bool bOnlyFindFirst = false) const;`
- L145 _private prototype_ `TArray<const UDataLayerAsset*> GetDataLayerAssetsFromOperation(const FDragDropOperation& InDragDrop, bool bOnlyFindFirst = false) const;`
- L146 _private prototype_ `TArray<UDataLayerInstance*> GetSelectedDataLayers(SSceneOutliner* InSceneOutliner) const;`
- L147 _private prototype_ `void SetParentDataLayer(const TArray<UDataLayerInstance*> DataLayers, UDataLayerInstance* ParentDataLayer) const;`
- L148 _private prototype_ `void OnLevelSelectionChanged(UObject* Obj);`
- L149 _private prototype_ `void OnPostLoadMapWithWorld(UWorld* World);`
- L150 _private prototype_ `static void CreateDataLayerPicker(UToolMenu* InMenu, FOnDataLayerInstancePicked OnDataLayerInstancePicked, FOnShouldFilterDataLayerInstance OnShouldFilterDataLayerInstance, bool bInShowRoot = false);`
- L151 _private prototype_ `bool ShouldExpandDataLayer(const UDataLayerInstance* DataLayer) const;`
- L152 _private prototype_ `bool ContainsSelectedChildDataLayer(const UDataLayerInstance* DataLayer) const;`
- L153 _private prototype_ `void DeleteDataLayers(const TArray<UDataLayerInstance*>& InDataLayersToDelete);`
- L154 _private prototype_ `void RefreshSelection();`
- L155 _private prototype_ `void CacheSelectedItems(const FSceneOutlinerItemSelection& Selection);`
- L156 _private prototype_ `UWorld* GetOwningWorld() const;`
- L157 _private prototype_ `AWorldDataLayers* GetOwningWorldAWorldDataLayers() const;`
- L158 _private prototype_ `AWorldDataLayers* GetWorldDataLayersFromTreeItem(const ISceneOutlinerTreeItem& TreeItem) const;`
- L159 _private prototype_ `UDataLayerInstance* GetDataLayerInstanceFromTreeItem(const ISceneOutlinerTreeItem& TreeItem) const;`
- L160 _private prototype_ `FSceneOutlinerDragValidationInfo ValidateActorDrop(const ISceneOutlinerTreeItem& DropTarget, TArray<AActor*> PayloadActors, bool bMoveOperation = false) const;`
- L161 _private prototype_ `FSceneOutlinerDragValidationInfo ValidateDataLayerAssetDrop(const ISceneOutlinerTreeItem& DropTarget, const TArray<const UDataLayerAsset*>& DataLayerAssetsToDrop, bool bIsMovingDataLayerInstances = false) const;`
- L162 _private prototype_ `bool CanReferenceDataLayerAssets(const AWorldDataLayers* InWorldDataLayers, const TArray<const UDataLayerAsset*>& InReferencedDataLayerAssets, FText* OutFailureReason = nullptr) const;`
- L163 _private prototype_ `void OnDataLayerAssetDropped(const TArray<const UDataLayerAsset*>& DroppedDataLayerAsset, ISceneOutlinerTreeItem& DropTarget) const;`
- L166 _private prototype_ `static TSharedRef<FSceneOutlinerFilter> CreateShowOnlySelectedActorsFilter();` — Filter factories
- L167 _private prototype_ `static TSharedRef<FSceneOutlinerFilter> CreateHideEditorDataLayersFilter();`
- L168 _private prototype_ `static TSharedRef<FSceneOutlinerFilter> CreateHideRuntimeDataLayersFilter();`
- L169 _private prototype_ `static TSharedRef<FSceneOutlinerFilter> CreateHideDataLayerActorsFilter();`
- L170 _private prototype_ `static TSharedRef<FSceneOutlinerFilter> CreateHideUnloadedActorsFilter();`
- L171 _private prototype_ `static TSharedRef<FSceneOutlinerFilter> CreateHideLevelInstancesFilter();`
- L176 _private prototype_ `void FindInContentBrowser();` — Delegate to handle "Find in Content Browser" context menu option
- L178 _private prototype_ `bool CanFindInContentBrowser() const;` — Delegate to handle enabling the "Find in Content Browser" context menu option
- L180 _private member_ `TWeakObjectPtr<UWorld> RepresentingWorld;` — The world which we are currently representing
- L182 _private member_ `TWeakObjectPtr<UWorld> UserChosenWorld;` — The world which the user manually selected
- L184 _private member_ `SDataLayerBrowser* DataLayerBrowser;` — The DataLayer browser
- L186 _private member_ `UDataLayerEditorSubsystem* DataLayerEditorSubsystem;` — The DataLayerEditorSubsystem
- L188 _private member_ `const TWeakObjectPtr<UWorld> SpecifiedWorldToDisplay;` — If this mode was created to display a specific world, don't allow it to be reassigned
- L190 _private member_ `uint32 FilteredDataLayerCount = 0;` — Number of datalayers which have passed through the filters
- L192 _private member_ `TSet<TWeakObjectPtr<UDataLayerInstance>> ApplicableDataLayers;` — List of datalayers which passed the regular filters and may or may not have passed the search filter
- L194 _private member_ `mutable FString PickDataLayerDialogPath;` — The path at which the "Pick A Data Layer Asset" will be opened
- L196 _private member_ `TSharedPtr<FUICommandList> Commands;` — Command list
- L198 _private member_ `TSet<TWeakObjectPtr<const UDataLayerInstance>> SelectedDataLayersSet;`
- L199 _private typedef_ `typedef TPair<TWeakObjectPtr<const UDataLayerInstance>, TWeakObjectPtr<const AActor>> FSelectedDataLayerActor;`
- L200 _private member_ `TSet<FSelectedDataLayerActor> SelectedDataLayerActors;`

#### enum `FDataLayerMode::EItemSortOrder`  
`enum class EItemSortOrder : int32`  
_L68-73_
- L70 _public enumerator_ `WorldDataLayers = 0`
- L71 _public enumerator_ `DataLayer = 10`
- L72 _public enumerator_ `Actor = 20`

#### class `FDataLayerPickingMode`  
`class FDataLayerPickingMode : public FDataLayerMode`  
_L203-221_
- inherits: `FDataLayerMode`
- L206 _public prototype_ `FDataLayerPickingMode(const FDataLayerModeParams& Params);`
- L207 _public function_ `virtual TSharedPtr<SWidget> CreateContextMenu() override`
- L208 _public function_ `virtual bool ShowStatusBar() const override`
- L209 _public function_ `virtual bool ShowViewButton() const override`
- L210 _public function_ `virtual bool ShowFilterOptions() const override`
- L211 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L212 _public function_ `virtual bool CanRename() const override`
- L213 _public function_ `virtual bool CanRenameItem(const ISceneOutlinerTreeItem& Item) const override`
- L214 _public function_ `virtual bool CanCustomizeToolbar() const`
- L215 _public function_ `virtual void OnItemDoubleClick(FSceneOutlinerTreeItemPtr Item) override`
- L216 _public function_ `virtual FReply OnKeyDown(const FKeyEvent& InKeyEvent) override`
- L217 _public prototype_ `virtual void OnItemSelectionChanged(FSceneOutlinerTreeItemPtr TreeItem, ESelectInfo::Type SelectionType, const FSceneOutlinerItemSelection& Selection) override;`
- L218 _public function_ `virtual void SynchronizeSelection() override`
- L220 _public prototype_ `static TSharedRef<SWidget> CreateDataLayerPickerWidget(FOnDataLayerInstancePicked OnDataLayerInstancePicked, FOnShouldFilterDataLayerInstance OnShouldFilterDataLayerInstance = FOnShouldFilterDataLayerInstance());`

#### Free symbols / members of external scopes

- L60 _delegate_ `DECLARE_DELEGATE_OneParam(FOnDataLayerInstancePicked, UDataLayerInstance*);` — Called when data layer instance is picked in the Data Layer Picker
- L60 _prototype_ `DECLARE_DELEGATE_OneParam(FOnDataLayerInstancePicked, UDataLayerInstance*);` — Called when data layer instance is picked in the Data Layer Picker
- L63 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnShouldFilterDataLayerInstance, const UDataLayerInstance*);` — Called to check if a data layer instance should be filtered out by Data Layer Picker. Return true to exclude the data layer instance.
- L63 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnShouldFilterDataLayerInstance, const UDataLayerInstance*);` — Called to check if a data layer instance should be filtered out by Data Layer Picker. Return true to exclude the data layer instance.

### `Source/Editor/DataLayerEditor/Private/DataLayer/DataLayerNameEditSink.h` (Private)


#### class `FDataLayerNameEditSink`  
`class FDataLayerNameEditSink : public UE::EditorWidgets::IObjectNameEditSink`  
_L12-61_
- inherits: `UE::EditorWidgets::IObjectNameEditSink`
- L14 _private function_ `virtual UClass* GetSupportedClass() const override`
- L19 _private function_ `virtual FText GetObjectDisplayName(UObject* Object) const override`
- L35 _private function_ `virtual bool IsObjectDisplayNameReadOnly(UObject* Object) const override`
- L41 _private function_ `virtual bool SetObjectDisplayName(UObject* Object, FString DisplayName) override`
- L57 _private function_ `virtual FText GetObjectNameTooltip(UObject* Object) const override`

#### Free symbols / members of external scopes

- L10 _macro_ `#define LOCTEXT_NAMESPACE "DataLayer"`

### `Source/Editor/DataLayerEditor/Private/DataLayer/DataLayerOutlinerDebugColorColumn.h` (Private)


#### class `FDataLayerOutlinerDebugColorColumn`  
`class FDataLayerOutlinerDebugColorColumn : public ISceneOutlinerColumn`  
_L15-35_
- inherits: `ISceneOutlinerColumn`
- L19 _public function_ `FDataLayerOutlinerDebugColorColumn(ISceneOutliner& SceneOutliner) : WeakSceneOutliner(StaticCastSharedRef<ISceneOutliner>(SceneOutliner.AsShared()))`
- L20 _public prototype_ `virtual ~FDataLayerOutlinerDebugColorColumn() = default;`
- L21 _public prototype_ `static FName GetID();`
- L25 _public function_ `virtual FName GetColumnID() override`
- L26 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L27 _public prototype_ `virtual const TSharedRef<SWidget> ConstructRowWidget(FSceneOutlinerTreeItemRef TreeItem, const STableRow<FSceneOutlinerTreeItemPtr>& Row) override;`
- L28 _public function_ `virtual bool SupportsSorting() const override`
- L34 _private member_ `TWeakPtr<ISceneOutliner> WeakSceneOutliner;`

### `Source/Editor/DataLayerEditor/Private/DataLayer/DataLayerOutlinerDeleteButtonColumn.h` (Private)


#### class `FDataLayerOutlinerDeleteButtonColumn`  
`class FDataLayerOutlinerDeleteButtonColumn : public ISceneOutlinerColumn`  
_L15-35_
- inherits: `ISceneOutlinerColumn`
- L19 _public function_ `FDataLayerOutlinerDeleteButtonColumn(ISceneOutliner& SceneOutliner) : WeakSceneOutliner(StaticCastSharedRef<ISceneOutliner>(SceneOutliner.AsShared()))`
- L20 _public prototype_ `virtual ~FDataLayerOutlinerDeleteButtonColumn() = default;`
- L21 _public prototype_ `static FName GetID();`
- L25 _public function_ `virtual FName GetColumnID() override`
- L26 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L27 _public prototype_ `virtual const TSharedRef<SWidget> ConstructRowWidget(FSceneOutlinerTreeItemRef TreeItem, const STableRow<FSceneOutlinerTreeItemPtr>& Row) override;`
- L28 _public function_ `virtual bool SupportsSorting() const override`
- L34 _private member_ `TWeakPtr<ISceneOutliner> WeakSceneOutliner;`

### `Source/Editor/DataLayerEditor/Private/DataLayer/DataLayerOutlinerHasErrorColumn.h` (Private)


#### class `FDataLayerOutlinerHasErrorsColumn`  
`class FDataLayerOutlinerHasErrorsColumn : public ISceneOutlinerColumn`  
_L15-33_
- inherits: `ISceneOutlinerColumn`
- L18 _public function_ `FDataLayerOutlinerHasErrorsColumn(ISceneOutliner& SceneOutliner) : WeakSceneOutliner(StaticCastSharedRef<ISceneOutliner>(SceneOutliner.AsShared()))`
- L19 _public prototype_ `virtual ~FDataLayerOutlinerHasErrorsColumn() = default;`
- L20 _public prototype_ `static FName GetID();`
- L24 _public function_ `virtual FName GetColumnID() override`
- L25 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L26 _public prototype_ `virtual const TSharedRef<SWidget> ConstructRowWidget(FSceneOutlinerTreeItemRef TreeItem, const STableRow<FSceneOutlinerTreeItemPtr>& Row) override;`
- L27 _public function_ `virtual bool SupportsSorting() const override`
- L32 _private member_ `TWeakPtr<ISceneOutliner> WeakSceneOutliner;`

### `Source/Editor/DataLayerEditor/Private/DataLayer/DataLayerOutlinerIsLoadedInEditorColumn.h` (Private)


#### class `FDataLayerOutlinerIsLoadedInEditorColumn`  
`class FDataLayerOutlinerIsLoadedInEditorColumn : public ISceneOutlinerColumn`  
_L15-32_
- inherits: `ISceneOutlinerColumn`
- L18 _public function_ `FDataLayerOutlinerIsLoadedInEditorColumn(ISceneOutliner& SceneOutliner) : WeakSceneOutliner(StaticCastSharedRef<ISceneOutliner>(SceneOutliner.AsShared()))`
- L19 _public prototype_ `virtual ~FDataLayerOutlinerIsLoadedInEditorColumn() = default;`
- L20 _public prototype_ `static FName GetID();`
- L24 _public function_ `virtual FName GetColumnID() override`
- L25 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L26 _public prototype_ `virtual const TSharedRef<SWidget> ConstructRowWidget(FSceneOutlinerTreeItemRef TreeItem, const STableRow<FSceneOutlinerTreeItemPtr>& Row) override;`
- L27 _public function_ `virtual bool SupportsSorting() const override`
- L31 _private member_ `TWeakPtr<ISceneOutliner> WeakSceneOutliner;`

### `Source/Editor/DataLayerEditor/Private/DataLayer/DataLayerOutlinerIsVisibleColumn.h` (Private)


#### class `FDataLayerOutlinerIsVisibleColumn`  
`class FDataLayerOutlinerIsVisibleColumn : public FSceneOutlinerGutter`  
_L14-28_
- inherits: `FSceneOutlinerGutter`
- L17 _public function_ `FDataLayerOutlinerIsVisibleColumn(ISceneOutliner& SceneOutliner) : FSceneOutlinerGutter(SceneOutliner)`
- L18 _public prototype_ `virtual ~FDataLayerOutlinerIsVisibleColumn() = default;`
- L19 _public prototype_ `static FName GetID();`
- L23 _public function_ `virtual FName GetColumnID() override`
- L24 _public prototype_ `virtual const TSharedRef<SWidget> ConstructRowWidget(FSceneOutlinerTreeItemRef TreeItem, const STableRow<FSceneOutlinerTreeItemPtr>& Row) override;`
- L25 _public function_ `virtual bool SupportsSorting() const override`

### `Source/Editor/DataLayerEditor/Private/DataLayer/DataLayerPropertyTypeCustomization.h` (Private)


#### struct `FDataLayerPropertyTypeCustomization`  
`struct FDataLayerPropertyTypeCustomization : public IPropertyTypeCustomization`  
_L26-30_
- inherits: `IPropertyTypeCustomization`
- L28 _public function_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override`
- L29 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override`

### `Source/Editor/DataLayerEditor/Private/DataLayer/DataLayerTreeItem.h` (Private)


#### struct `FDataLayerTreeItem`  
`struct FDataLayerTreeItem : ISceneOutlinerTreeItem`  
_L20-60_
- inherits: `ISceneOutlinerTreeItem`
- L23 _public prototype_ `FDataLayerTreeItem(UDataLayerInstance* InDataLayerInstance);`
- L24 _public function_ `UDataLayerInstance* GetDataLayer() const`
- L27 _public function_ `virtual bool IsValid() const override` — Begin ISceneOutlinerTreeItem Implementation
- L28 _public function_ `virtual FSceneOutlinerTreeItemID GetID() const override`
- L29 _public prototype_ `virtual FString GetDisplayString() const override;`
- L30 _public prototype_ `virtual bool CanInteract() const override;`
- L31 _public prototype_ `virtual TSharedRef<SWidget> GenerateLabelWidget(ISceneOutliner& Outliner, const STableRow<FSceneOutlinerTreeItemPtr>& InRow) override;`
- L32 _public function_ `virtual bool HasVisibilityInfo() const override`
- L33 _public prototype_ `virtual void OnVisibilityChanged(const bool bNewVisibility) override;`
- L34 _public prototype_ `virtual bool GetVisibility() const override;`
- L35 _public prototype_ `virtual bool ShouldShowVisibilityState() const override;`
- L38 _public prototype_ `bool ShouldBeHighlighted() const;`
- L39 _public function_ `void SetIsHighlightedIfSelected(bool bInIsHighlightedIfSelected)`
- L41 _public member_ `static const FSceneOutlinerTreeItemType Type;`
- L43 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FFilterPredicate, const UDataLayerInstance*);`
- L44 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FInteractivePredicate, const UDataLayerInstance*);`
- L46 _public function_ `bool Filter(FFilterPredicate Pred) const`
- L51 _public function_ `bool GetInteractiveState(FInteractivePredicate Pred) const`
- L57 _private member_ `TWeakObjectPtr<UDataLayerInstance> DataLayerInstance;`
- L58 _private member_ `const FObjectKey ID;`
- L59 _private member_ `bool bIsHighlighedtIfSelected;`

#### Free symbols / members of external scopes

- L43 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FFilterPredicate, const UDataLayerInstance*);`
- L44 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FInteractivePredicate, const UDataLayerInstance*);`

### `Source/Editor/DataLayerEditor/Private/DataLayer/DataLayersActorDescTreeItem.h` (Private)


#### struct `FDataLayerActorDescTreeItemData`  
`struct FDataLayerActorDescTreeItemData`  
_L23-34_
- L25 _public function_ `FDataLayerActorDescTreeItemData(const FGuid& InActorGuid, UActorDescContainerInstance* InContainerInstance, UDataLayerInstance* InDataLayer) : ActorGuid(InActorGuid) , ContainerInstance(InContainerInstance) , DataLayer(InDataLayer)`
- L31 _public member_ `const FGuid& ActorGuid;`
- L32 _public member_ `UActorDescContainerInstance* const ContainerInstance;`
- L33 _public member_ `TWeakObjectPtr<UDataLayerInstance> DataLayer;`

#### struct `FDataLayerActorDescTreeItem`  
`struct FDataLayerActorDescTreeItem : public FActorDescTreeItem`  
_L39-98_
- inherits: `FActorDescTreeItem`
- L42 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FFilterPredicate, const FWorldPartitionActorDescInstance* ActorDescInstance, const UDataLayerInstance* DataLayer);`
- L43 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FInteractivePredicate, const FWorldPartitionActorDescInstance* ActorDescInstance, const UDataLayerInstance* DataLayer);`
- L45 _public function_ `FDataLayerActorDescTreeItem(const FDataLayerActorDescTreeItemData& InData) : FActorDescTreeItem(InData.ActorGuid, InData.ContainerInstance) , DataLayer(InData.DataLayer) , IDDataLayerActorDesc(FDataLayerActorDescTreeItem::ComputeTreeItemID(InData.ActorGuid, InData.ContainerInstance, InData.DataLayer.Get()))`
- L63 _public function_ `UDataLayerInstance* GetDataLayer() const`
- L65 _public function_ `static FSceneOutlinerTreeItemID ComputeTreeItemID(FGuid InActorGuid, UActorDescContainerInstance* InContainerInstance, const UDataLayerInstance* InDataLayer)`
- L76 _public function_ `bool Filter(FFilterPredicate Pred) const`
- L81 _public function_ `bool GetInteractiveState(FInteractivePredicate Pred) const`
- L87 _public function_ `virtual bool IsValid() const override` — Begin ISceneOutlinerTreeItem Implementation
- L88 _public function_ `virtual FSceneOutlinerTreeItemID GetID() const override`
- L89 _public function_ `virtual bool ShouldShowVisibilityState() const`
- L90 _public function_ `virtual bool HasVisibilityInfo() const override`
- L91 _public function_ `virtual void OnVisibilityChanged(const bool bNewVisibility) override`
- L92 _public function_ `virtual bool GetVisibility() const override`
- L96 _private member_ `TWeakObjectPtr<UDataLayerInstance> DataLayer;`
- L97 _private member_ `const FSceneOutlinerTreeItemID IDDataLayerActorDesc;`

#### Free symbols / members of external scopes

- L42 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FFilterPredicate, const FWorldPartitionActorDescInstance* ActorDescInstance, const UDataLayerInstance* DataLayer);`
- L43 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FInteractivePredicate, const FWorldPartitionActorDescInstance* ActorDescInstance, const UDataLayerInstance* DataLayer);`

### `Source/Editor/DataLayerEditor/Private/DataLayer/SDataLayerBrowser.h` (Private)


#### class `SDataLayerBrowser`  
`class SDataLayerBrowser : public SCompoundWidget`  
_L19-47_
- inherits: `SCompoundWidget`
- L23 _public function_ `SLATE_BEGIN_ARGS( SDataLayerBrowser )`
- L24 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L34 _public prototype_ `void SyncDataLayerBrowserToDataLayer(const UDataLayerInstance* DataLayer);`
- L35 _public prototype_ `void OnSelectionChanged(TSet<TWeakObjectPtr<const UDataLayerInstance>>& SelectedDataLayersSet);`
- L38 _private prototype_ `void InitializeDataLayerBrowser();`
- L40 _private member_ `TSet<TWeakObjectPtr<const UDataLayerInstance>> SelectedDataLayersSet;`
- L41 _private member_ `TSharedPtr<class SDataLayerOutliner> DataLayerOutliner;`
- L42 _private member_ `TSharedPtr<class IDetailsView> DetailsWidget;`
- L43 _private member_ `TSharedPtr<SButton> ToggleModeButton;`
- L44 _private member_ `TSharedPtr<SVerticalBox> ContentAreaBox;`
- L45 _private member_ `TSharedPtr<SBorder> DataLayerContentsSection;`
- L46 _private member_ `TSharedPtr<SBorder> DataLayerContentsHeader;`

### `Source/Editor/DataLayerEditor/Private/DataLayer/SDataLayerOutliner.h` (Private)


#### class `SDataLayerOutliner`  
`class SDataLayerOutliner : public SSceneOutliner`  
_L12-30_
- inherits: `SSceneOutliner`
- L15 _public function_ `void Construct(const FArguments& InArgs, const FSceneOutlinerInitializationOptions& InitOptions)`
- L20 _public function_ `SDataLayerOutliner()`
- L21 _public prototype_ `virtual ~SDataLayerOutliner() = default;`
- L23 _public prototype_ `void CustomAddToToolbar(TSharedPtr<class SHorizontalBox> Toolbar) override;`
- L25 _private prototype_ `bool CanAddSelectedActorsToSelectedDataLayers() const;`
- L26 _private prototype_ `bool CanRemoveSelectedActorsFromSelectedDataLayers() const;`
- L27 _private prototype_ `FReply OnAddSelectedActorsToSelectedDataLayersClicked();`
- L28 _private prototype_ `FReply OnRemoveSelectedActorsFromSelectedDataLayersClicked();`
- L29 _private prototype_ `TArray<class UDataLayerInstance*> GetSelectedDataLayers() const;`

### `Source/Editor/DataLayerEditor/Private/DataLayer/WorldDataLayersTreeItem.h` (Private)


#### struct `FWorldDataLayersTreeItem`  
`struct FWorldDataLayersTreeItem : ISceneOutlinerTreeItem`  
_L21-57_
- inherits: `ISceneOutlinerTreeItem`
- L24 _public prototype_ `FWorldDataLayersTreeItem(AWorldDataLayers* InWorldDataLayers);`
- L25 _public function_ `AWorldDataLayers* GetWorldDataLayers() const`
- L28 _public function_ `virtual bool IsValid() const override` — Begin ISceneOutlinerTreeItem Implementation
- L29 _public function_ `virtual FSceneOutlinerTreeItemID GetID() const override`
- L30 _public prototype_ `virtual FString GetDisplayString() const override;`
- L31 _public prototype_ `virtual bool CanInteract() const override;`
- L32 _public prototype_ `virtual TSharedRef<SWidget> GenerateLabelWidget(ISceneOutliner& Outliner, const STableRow<FSceneOutlinerTreeItemPtr>& InRow) override;`
- L33 _public function_ `virtual bool ShouldShowVisibilityState() const override`
- L36 _public prototype_ `int32 GetSortPriority() const;`
- L38 _public member_ `static const FSceneOutlinerTreeItemType Type;`
- L40 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FFilterPredicate, const AWorldDataLayers*);`
- L41 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FInteractivePredicate, const AWorldDataLayers*);`
- L43 _public function_ `bool Filter(FFilterPredicate Pred) const`
- L48 _public function_ `bool GetInteractiveState(FInteractivePredicate Pred) const`
- L54 _private prototype_ `bool IsReadOnly() const;`
- L55 _private member_ `TWeakObjectPtr<AWorldDataLayers> WorldDataLayers;`
- L56 _private member_ `const FObjectKey ID;`

#### Free symbols / members of external scopes

- L40 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FFilterPredicate, const AWorldDataLayers*);`
- L41 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FInteractivePredicate, const AWorldDataLayers*);`

### `Source/Editor/DataLayerEditor/Public/DataLayer/DataLayerAction.h` (Public)


#### enum `EDataLayerAction`  
`enum class EDataLayerAction : uint8`  
_L7-14_
- L9 _public enumerator_ `Add`
- L10 _public enumerator_ `Modify`
- L11 _public enumerator_ `Delete`
- L12 _public enumerator_ `Rename`
- L13 _public enumerator_ `Reset`

### `Source/Editor/DataLayerEditor/Public/DataLayer/DataLayerDragDropOp.h` (Public)


#### class `FDataLayerDragDropOp`  
`class FDataLayerDragDropOp : public FDecoratedDragDropOp`  
_L19-39_
- inherits: `FDecoratedDragDropOp`
- desc: Drag/drop operation for dragging layers in the editor
- L22 _public function_ `DRAG_DROP_OPERATOR_TYPE(FDataLayerDragDropOp, FDecoratedDragDropOp) void Init(const TArray<TWeakObjectPtr<UDataLayerInstance>>& InDataLayerInstances)`
- L36 _public member_ `TArray< TWeakObjectPtr<UDataLayerInstance> > DataLayerInstances;` — The labels of the layers being dragged
- L38 _public prototype_ `virtual void Construct() override;`

#### class `FDataLayerActorMoveOp`  
`class FDataLayerActorMoveOp : public FDecoratedDragDropOp`  
_L42-51_
- inherits: `FDecoratedDragDropOp`
- desc: Drag/drop operation for moving actor(s) in a data layer in the editor
- L45 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FDataLayerActorMoveOp, FDecoratedDragDropOp) TArray<FDataLayerActorMoveElement> DataLayerActorMoveElements;`
- L50 _public prototype_ `virtual void Construct() override;`

#### Free symbols / members of external scopes

- L16 _typedef_ `typedef TPair< TWeakObjectPtr<AActor>, TWeakObjectPtr<UDataLayerInstance>> FDataLayerActorMoveElement;`

### `Source/Editor/DataLayerEditor/Public/DataLayer/DataLayerEditorState.h` (Public)


#### class `UDataLayerEditorState`  
`class UDataLayerEditorState : public UWorldDependantEditorState`  
_L11-28_
- reflection: `UCLASS()`
- inherits: `UWorldDependantEditorState`
- L16 _private prototype_ `virtual FText GetCategoryText() const override;`
- L18 _private prototype_ `virtual FOperationResult CaptureState() override;`
- L19 _private prototype_ `virtual FOperationResult RestoreState() const override;`
- L24 _private member_ `TArray<TObjectPtr<const UDataLayerAsset>> NotLoadedDataLayers;` — `UPROPERTY(EditAnywhere, Category = DataLayers)`
- L27 _private member_ `TArray<TObjectPtr<const UDataLayerAsset>> LoadedDataLayers;` — `UPROPERTY(EditAnywhere, Category = DataLayers)`

### `Source/Editor/DataLayerEditor/Public/DataLayer/DataLayerEditorSubsystem.h` (Public)


#### struct `FDataLayerCreationParameters`  
`struct FDataLayerCreationParameters`  
_L55-71_
- reflection: `USTRUCT(BlueprintType)`
- L59 _public prototype_ `FDataLayerCreationParameters();`
- L63 _public member_ `TObjectPtr<UDataLayerAsset> DataLayerAsset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Layer")` — Required if bIsPrivate is false. Will assign the asset to the created instance.
- L67 _public member_ `TObjectPtr<AWorldDataLayers> WorldDataLayers;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Layer")` — Optional. Will default at the level WorldDataLayers if unset.
- L70 _public member_ `bool bIsPrivate;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Layer")`

#### class `UActorEditorContextDataLayerState`  
`class UActorEditorContextDataLayerState : public UActorEditorContextClientState`  
_L74-84_
- reflection: `UCLASS()`
- inherits: `UActorEditorContextClientState`
- L80 _public member_ `TObjectPtr<const UExternalDataLayerAsset> ExternalDataLayerAsset;` — `UPROPERTY(VisibleAnywhere, Category="Data Layers")`
- L83 _public member_ `TArray<TSoftObjectPtr<const UDataLayerAsset>> DataLayerAssets;` — `UPROPERTY(VisibleAnywhere, Category="Data Layers")`

#### class `UDataLayerEditorSubsystem`  
`class UDataLayerEditorSubsystem final : public UEditorSubsystem, public IActorEditorContextClient, public FTickableGameObject`  
_L87-863_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UEditorSubsystem,IActorEditorContextClient,FTickableGameObject`
- L92 _public prototype_ `UDataLayerEditorSubsystem();`
- L94 _public prototype_ `static UDataLayerEditorSubsystem* Get();`
- L96 _public typedef_ `typedef IFilter<const TWeakObjectPtr<AActor>&> FActorFilter;`
- L101 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;` — Prepares for use
- L106 _public prototype_ `virtual void Deinitialize() override;` — Internal cleanup
- L111 _public prototype_ `virtual ~UDataLayerEditorSubsystem() = default;` — Destructor
- L114 _public prototype_ `virtual UWorld* GetTickableGameObjectWorld() const override;`
- L115 _public function_ `virtual bool IsTickableInEditor() const`
- L116 _public prototype_ `virtual ETickableTickType GetTickableTickType() const override;`
- L117 _public prototype_ `virtual bool IsTickable() const override;`
- L118 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L119 _public function_ `TStatId GetStatId() const override`
- L123 _public prototype_ `virtual void BeginDestroy() override;`
- L127 _public prototype_ `virtual void OnExecuteActorEditorContextAction(UWorld* InWorld, const EActorEditorContextAction& InType, AActor* InActor = nullptr) override;`
- L128 _public prototype_ `virtual void CaptureActorEditorContextState(UWorld* InWorld, UActorEditorContextStateCollection* InStateCollection) const override;`
- L129 _public prototype_ `virtual void RestoreActorEditorContextState(UWorld* InWorld, const UActorEditorContextStateCollection* InStateCollection) override;`
- L130 _public prototype_ `virtual bool GetActorEditorContextDisplayInfo(UWorld* InWorld, FActorEditorContextClientDisplayInfo& OutDiplayInfo) const override;`
- L131 _public function_ `virtual bool CanResetContext(UWorld* InWorld) const override`
- L132 _public prototype_ `virtual TSharedRef<SWidget> GetActorEditorContextWidget(UWorld* InWorld) const override;`
- L133 _public function_ `virtual FOnActorEditorContextClientChanged& GetOnActorEditorContextClientChanged() override`
- L136 _public prototype_ `void AddToActorEditorContext(UDataLayerInstance* InDataLayerInstance);` — `UFUNCTION(BlueprintCallable, Category = DataLayers)`
- L138 _public prototype_ `void RemoveFromActorEditorContext(UDataLayerInstance* InDataLayerInstance);` — `UFUNCTION(BlueprintCallable, Category = DataLayers)`
- L140 _public prototype_ `bool SetActorEditorContextCurrentExternalDataLayer(const UExternalDataLayerAsset* InExternalDataLayerAsset);` — `UFUNCTION(BlueprintCallable, Category = DataLayers)`
- L142 _public prototype_ `const UExternalDataLayerAsset* GetActorEditorContextCurrentExternalDataLayer() const;` — `UFUNCTION(BlueprintCallable, Category = DataLayers)`
- L144 _public prototype_ `TArray<const UDataLayerInstance*> GetDataLayerInstances(const TArray<const UDataLayerAsset*> DataLayerAssets) const;`
- L147 _public prototype_ `template<class DataLayerType, typename ...Args> DataLayerType* CreateDataLayerInstance(AWorldDataLayers* WorldDataLayers, Args&&... InArgs);`
- L159 _public prototype_ `DECLARE_EVENT_ThreeParams(UDataLayerEditorSubsystem, FOnDataLayerChanged, const EDataLayerAction , const TWeakObjectPtr<const UDataLayerInstance>& , const FName& );` — Broadcasts whenever one or more DataLayers are modified Actions Add    : The specified ChangedDataLayer is a newly created UDataLayerInstance Modify : The specified ChangedDataLayer was just modified, if ChangedDataLayer is invalid then multiple DataLayers were modified. ChangedProperty specifies what field on the UDataLayerInstance was changed, if NAME_None then multiple fields were changed Delete : A DataLayer was deleted Rename : The specified ChangedDataLayer was just renamed Reset  : A large amount of changes have occurred to a number of DataLayers.
- L160 _public function_ `FOnDataLayerChanged& OnDataLayerChanged()`
- L163 _public prototype_ `DECLARE_EVENT_OneParam(UDataLayerEditorSubsystem, FOnActorDataLayersChanged, const TWeakObjectPtr<AActor>& );` — Broadcasts whenever one or more Actors changed UDataLayerInstances
- L164 _public function_ `FOnActorDataLayersChanged& OnActorDataLayersChanged()`
- L167 _public prototype_ `DECLARE_EVENT_OneParam(UDataLayerEditorSubsystem, FOnActorDataLayersEditorLoadingStateChanged, bool );` — Broadcasts whenever one or more DataLayers editor loading state changed
- L168 _public function_ `FOnActorDataLayersEditorLoadingStateChanged& OnActorDataLayersEditorLoadingStateChanged()`
- L175 _public function_ `bool IsActorValidForDataLayer(AActor* Actor)` — `UE_DEPRECATED(all, "Use IsActorValidForDataLayerInstances instead.")` — `UFUNCTION(meta = (DeprecatedFunction, DeprecationMessage = "Use IsActorValidForDataLayerInstances instead."))`
- L184 _public prototype_ `bool IsActorValidForDataLayerInstances(AActor* Actor, const TArray<UDataLayerInstance*>& DataLayerInstances);` — `UFUNCTION(BlueprintCallable, Category = DataLayers)` — Checks to see if the specified actor is in an appropriate state to interact with DataLayers @param	Actor				The actor to validate @param  DataLayerInstances	The data layers used to do the validation
- L194 _public prototype_ `bool AddActorToDataLayer(AActor* Actor, UDataLayerInstance* DataLayer);` — `UFUNCTION(BlueprintCallable, Category = DataLayers)` — Adds the actor to the DataLayer. @param	Actor		The actor to add to the DataLayer @param	DataLayer	The DataLayer to add the actor to @return				true if the actor was added.  false is returned if the actor already belongs to the DataLayer.
- L204 _public prototype_ `bool AddActorToDataLayers(AActor* Actor, const TArray<UDataLayerInstance*>& DataLayers);` — `UFUNCTION(BlueprintCallable, Category = DataLayers)` — Adds the provided actor to the DataLayers. @param	Actor		The actor to add to the provided DataLayers @param	DataLayers	A valid list of DataLayers. @return				true if the actor was added to at least one of the provided DataLayers.
- L214 _public prototype_ `bool RemoveActorFromDataLayer(AActor* Actor, UDataLayerInstance* DataLayerToRemove);` — `UFUNCTION(BlueprintCallable, Category = DataLayers)` — Removes an actor from the specified DataLayer. @param	Actor			The actor to remove from the provided DataLayer @param	DataLayerToRemove	The DataLayer to remove the actor from @return					true if the actor was removed from the DataLayer.  false is returned if the actor already belonged to the DataLayer.
- L224 _public prototype_ `bool RemoveActorFromDataLayers(AActor* Actor, const TArray<UDataLayerInstance*>& DataLayers);` — `UFUNCTION(BlueprintCallable, Category = DataLayers)` — Removes the provided actor from the DataLayers. @param	Actor		The actor to remove from the provided DataLayers @param	DataLayers	A valid list of DataLayers. @return				true if the actor was removed from at least one of the provided DataLayers.
- L233 _public prototype_ `bool RemoveActorFromAllDataLayers(AActor* Actor);` — `UFUNCTION(BlueprintCallable, Category = DataLayers)` — Removes an actor from all DataLayers. @param	Actor			The actor to modify @return					true if the actor was changed.
- L242 _public prototype_ `bool RemoveActorsFromAllDataLayers(const TArray<AActor*>& Actors);` — `UFUNCTION(BlueprintCallable, Category = DataLayers)` — Removes an actor from all DataLayers. @param	Actor			The actors to modify @return					true if any actor was changed.
- L255 _public prototype_ `bool AddActorsToDataLayer(const TArray<AActor*>& Actors, UDataLayerInstance* DataLayer);` — `UFUNCTION(BlueprintCallable, Category = DataLayers)` — Add the actors to the DataLayer @param	Actors		The actors to add to the DataLayer @param	DataLayer	The DataLayer to add to @return				true if at least one actor was added to the DataLayer.  false is returned if all the actors already belonged to the DataLayer.
- L265 _public prototype_ `bool AddActorsToDataLayers(const TArray<AActor*>& Actors, const TArray<UDataLayerInstance*>& DataLayers);` — `UFUNCTION(BlueprintCallable, Category = DataLayers)` — Add the actors to the DataLayers @param	Actors		The actors to add to the DataLayers @param	DataLayers	A valid list of DataLayers. @return				true if at least one actor was added to at least one DataLayer.  false is returned if all the actors already belonged to all specified DataLayers.
- L275 _public prototype_ `bool RemoveActorsFromDataLayer(const TArray<AActor*>& Actors, UDataLayerInstance* DataLayer);` — `UFUNCTION(BlueprintCallable, Category = DataLayers)` — Removes the actors from the specified DataLayer. @param	Actors			The actors to remove from the provided DataLayer @param	DataLayerToRemove	The DataLayer to remove the actors from @return					true if at least one actor was removed from the DataLayer.  false is returned if all the actors already belonged to the DataLayer.
- L285 _public prototype_ `bool RemoveActorsFromDataLayers(const TArray<AActor*>& Actors, const TArray<UDataLayerInstance*>& DataLayers);` — `UFUNCTION(BlueprintCallable, Category = DataLayers)` — Remove the actors from the DataLayers @param	Actors		The actors to remove to the DataLayers @param	DataLayers	A valid list of DataLayers. @return				true if at least one actor was removed from at least one DataLayer.  false is returned if none of the actors belonged to any of the specified DataLayers.
- L297 _public prototype_ `bool AddSelectedActorsToDataLayer(UDataLayerInstance* DataLayer);` — `UFUNCTION(BlueprintCallable, Category = DataLayers)` — Adds selected actors to the DataLayer. @param	DataLayer	A DataLayer. @return				true if at least one actor was added.  false is returned if all selected actors already belong to the DataLayer.
- L306 _public prototype_ `bool AddSelectedActorsToDataLayers(const TArray<UDataLayerInstance*>& DataLayers);` — `UFUNCTION(BlueprintCallable, Category = DataLayers)` — Adds selected actors to the DataLayers. @param	DataLayers	A valid list of DataLayers. @return				true if at least one actor was added.  false is returned if all selected actors already belong to the DataLayers.
- L315 _public prototype_ `bool RemoveSelectedActorsFromDataLayer(UDataLayerInstance* DataLayer);` — `UFUNCTION(BlueprintCallable, Category = DataLayers)` — Removes the selected actors from the DataLayer. @param	DataLayer	A DataLayer. @return				true if at least one actor was added.  false is returned if all selected actors already belong to the DataLayer.
- L324 _public prototype_ `bool RemoveSelectedActorsFromDataLayers(const TArray<UDataLayerInstance*>& DataLayers);` — `UFUNCTION(BlueprintCallable, Category = DataLayers)` — Removes selected actors from the DataLayers. @param	DataLayers	A valid list of DataLayers. @return				true if at least one actor was removed.
- L340 _public prototype_ `bool SelectActorsInDataLayer(UDataLayerInstance* DataLayer, const bool bSelect, const bool bNotify, const bool bSelectEvenIfHidden = false);` — `UFUNCTION(BlueprintCallable, Category = DataLayers)` — Selects/de-selects actors belonging to the DataLayer. @param	DataLayer						A valid DataLayer. @param	bSelect							If true actors are selected; if false, actors are deselected. @param	bNotify							If true the Editor is notified of the selection change; if false, the Editor will not be notified. @param	bSelectEvenIfHidden	[optional]	If true even hidden actors will be selected; if false, hidden actors won't be selected. @return									true if at least one actor was selected/deselected.
- L352 _public prototype_ `bool SelectActorsInDataLayer(UDataLayerInstance* DataLayer, const bool bSelect, const bool bNotify, const bool bSelectEvenIfHidden, const TSharedPtr<FActorFilter>& Filter);` — Selects/de-selects actors belonging to the DataLayer. @param	DataLayer						A valid DataLayer. @param	bSelect							If true actors are selected; if false, actors are deselected. @param	bNotify							If true the Editor is notified of the selection change; if false, the Editor will not be notified. @param	bSelectEvenIfHidden	[optional]	If true even hidden actors will be selected; if false, hidden actors won't be selected. @param	Filter	[optional]				Actor that don't pass the specified filter restrictions won't be selected. @return									true if at least one actor was selected/deselected.
- L364 _public prototype_ `bool SelectActorsInDataLayers(const TArray<UDataLayerInstance*>& DataLayers, const bool bSelect, const bool bNotify, const bool bSelectEvenIfHidden = false);` — `UFUNCTION(BlueprintCallable, Category = DataLayers)` — Selects/de-selects actors belonging to the DataLayers. @param	DataLayers						A valid list of DataLayers. @param	bSelect							If true actors are selected; if false, actors are deselected. @param	bNotify							If true the Editor is notified of the selection change; if false, the Editor will not be notified @param	bSelectEvenIfHidden	[optional]	If true even hidden actors will be selected; if false, hidden actors won't be selected. @return									true if at least one actor was selected/deselected.
- L376 _public prototype_ `bool SelectActorsInDataLayers(const TArray<UDataLayerInstance*>& DataLayers, const bool bSelect, const bool bNotify, const bool bSelectEvenIfHidden, const TSharedPtr<FActorFilter>& Filter);` — Selects/de-selects actors belonging to the DataLayers. @param	DataLayers						A valid list of DataLayers. @param	bSelect							If true actors are selected; if false, actors are deselected. @param	bNotify							If true the Editor is notified of the selection change; if false, the Editor will not be notified @param	bSelectEvenIfHidden	[optional]	If true even hidden actors will be selected; if false, hidden actors won't be selected. @param	Filter	[optional]				Actor that don't pass the specified filter restrictions won't be selected. @return									true if at least one actor was selected/deselected.
- L385 _public prototype_ `void SetActorsPinStateInDataLayers(const TArray<UDataLayerInstance*>& DataLayerInstances, const bool bPinned);` — Pin/unpin actors belonging to the DataLayers. @param	DataLayerInstances				A valid list of Data Layer Instances. @param	bPinned							If true actors are pinned; if false, actors are unpinned.
- L403 _public prototype_ `bool UpdateActorVisibility(AActor* Actor, bool& bOutSelectionChanged, bool& bOutActorModified, const bool bNotifySelectionChange, const bool bRedrawViewports);` — `UFUNCTION(BlueprintCallable, Category = DataLayers)` — Updates the provided actors visibility in the viewports @param	Actor						Actor to update @param	bOutSelectionChanged [OUT]	Whether the Editors selection changed @param	bOutActorModified [OUT]		Whether the actor was modified @param	bNotifySelectionChange		If true the Editor is notified of the selection change; if false, the Editor will not be notified @param	bRedrawViewports			If true the viewports will be redrawn; if false, they will not
- L412 _public prototype_ `bool UpdateAllActorsVisibility(const bool bNotifySelectionChange, const bool bRedrawViewports);` — `UFUNCTION(BlueprintCallable, Category = DataLayers)` — Updates the visibility of all actors in the viewports @param	bNotifySelectionChange		If true the Editor is notified of the selection change; if false, the Editor will not be notified @param	bRedrawViewports			If true the viewports will be redrawn; if false, they will not
- L425 _public prototype_ `void AppendActorsFromDataLayer(UDataLayerInstance* DataLayer, TArray<AActor*>& InOutActors) const;` — `UFUNCTION(BlueprintCallable, Category = DataLayers)` — Appends all the actors associated with the specified DataLayer. @param	DataLayer			The DataLayer to find actors for. @param	InOutActors			The list to append the found actors to.
- L434 _public prototype_ `void AppendActorsFromDataLayer(UDataLayerInstance* DataLayer, TArray<AActor*>& InOutActors, const TSharedPtr<FActorFilter>& Filter) const;` — Appends all the actors associated with the specified DataLayer. @param	DataLayer			The DataLayer to find actors for. @param	InOutActors			The list to append the found actors to. @param	Filter	[optional]	Actor that don't pass the specified filter restrictions won't be selected.
- L443 _public prototype_ `void AppendActorsFromDataLayers(const TArray<UDataLayerInstance*>& DataLayers, TArray<AActor*>& InOutActors) const;` — `UFUNCTION(BlueprintCallable, Category = DataLayers)` — Appends all the actors associated with ANY of the specified DataLayers. @param	DataLayers			The DataLayers to find actors for. @param	InOutActors			The list to append the found actors to.
- L452 _public prototype_ `void AppendActorsFromDataLayers(const TArray<UDataLayerInstance*>& DataLayers, TArray<AActor*>& InOutActors, const TSharedPtr<FActorFilter>& Filter) const;` — Appends all the actors associated with ANY of the specified DataLayers. @param	DataLayers			The DataLayers to find actors for. @param	InOutActors			The list to append the found actors to. @param	Filter	[optional]	Actor that don't pass the specified filter restrictions won't be selected.
- L461 _public prototype_ `TArray<AActor*> GetActorsFromDataLayer(UDataLayerInstance* DataLayer) const;` — `UFUNCTION(BlueprintCallable, Category = DataLayers)` — Gets all the actors associated with the specified DataLayer. Analog to AppendActorsFromDataLayer but it returns rather than appends the actors. @param	DataLayer			The DataLayer to find actors for. @return						The list to assign the found actors to.
- L470 _public prototype_ `TArray<AActor*> GetActorsFromDataLayer(UDataLayerInstance* DataLayer, const TSharedPtr<FActorFilter>& Filter) const;` — Gets all the actors associated with the specified DataLayer. Analog to AppendActorsFromDataLayer but it returns rather than appends the actors. @param	DataLayer			The DataLayer to find actors for. @param	Filter	[optional]	Actor that don't pass the specified filter restrictions won't be selected. @return						The list to assign the found actors to.
- L479 _public prototype_ `TArray<AActor*> GetActorsFromDataLayers(const TArray<UDataLayerInstance*>& DataLayers) const;` — `UFUNCTION(BlueprintCallable, Category = DataLayers)` — Gets all the actors associated with ANY of the specified DataLayers. Analog to AppendActorsFromDataLayers but it returns rather than appends the actors. @param	DataLayers			The DataLayers to find actors for. @return						The list to assign the found actors to.
- L488 _public prototype_ `TArray<AActor*> GetActorsFromDataLayers(const TArray<UDataLayerInstance*>& DataLayers, const TSharedPtr<FActorFilter>& Filter) const;` — Gets all the actors associated with ANY of the specified DataLayers. Analog to AppendActorsFromDataLayers but it returns rather than appends the actors. @param	DataLayers			The DataLayers to find actors for. @param	Filter	[optional]	Actor that don't pass the specified filter restrictions won't be selected. @return						The list to assign the found actors to.
- L497 _public prototype_ `void SetDataLayerVisibility(UDataLayerInstance* DataLayer, const bool bIsVisible);` — `UFUNCTION(BlueprintCallable, Category = DataLayers)` — Changes the DataLayer's visibility to the provided state @param	DataLayer	The DataLayer to affect. @param	bIsVisible	If true the DataLayer will be visible; if false, the DataLayer will not be visible.
- L506 _public prototype_ `void SetDataLayersVisibility(const TArray<UDataLayerInstance*>& DataLayers, const bool bIsVisible);` — `UFUNCTION(BlueprintCallable, Category = DataLayers)` — Changes visibility of the DataLayers to the provided state @param	DataLayers	The DataLayers to affect @param	bIsVisible	If true the DataLayers will be visible; if false, the DataLayers will not be visible
- L514 _public prototype_ `void ToggleDataLayerVisibility(UDataLayerInstance* DataLayer);` — `UFUNCTION(BlueprintCallable, Category = DataLayers)` — Toggles the DataLayer's visibility @param DataLayer	The DataLayer to affect
- L522 _public prototype_ `void ToggleDataLayersVisibility(const TArray<UDataLayerInstance*>& DataLayers);` — `UFUNCTION(BlueprintCallable, Category = DataLayers)` — Toggles the visibility of all of the DataLayers @param	DataLayers	The DataLayers to affect
- L534 _public prototype_ `bool SetDataLayerIsLoadedInEditor(UDataLayerInstance* DataLayer, const bool bIsLoadedInEditor, const bool bIsFromUserChange);` — `UFUNCTION(BlueprintCallable, Category = DataLayers)` — Changes the DataLayer's IsLoadedInEditor flag to the provided state @param	DataLayer						The DataLayer to affect. @param	bIsLoadedInEditor				The new value of the flag IsLoadedInEditor. If True, the Editor loading will consider this DataLayer to load or not an Actor part of this DataLayer. An Actor will not be loaded in the Editor if all its DataLayers are not LoadedInEditor. @param	bIsFromUserChange				If this change originates from a user change or not.
- L546 _public prototype_ `bool SetDataLayersIsLoadedInEditor(const TArray<UDataLayerInstance*>& DataLayers, const bool bIsLoadedInEditor, const bool bIsFromUserChange);` — `UFUNCTION(BlueprintCallable, Category = DataLayers)` — Changes the IsLoadedInEditor flag of the DataLayers to the provided state @param	DataLayers						The DataLayers to affect @param	bIsLoadedInEditor				The new value of the flag IsLoadedInEditor. If True, the Editor loading will consider this DataLayer to load or not an Actor part of this DataLayer. An Actor will not be loaded in the Editor if all its DataLayers are not LoadedInEditor. @param	bIsFromUserChange				If this change originates from a user change or not.
- L555 _public prototype_ `bool ToggleDataLayerIsLoadedInEditor(UDataLayerInstance* DataLayer, const bool bIsFromUserChange);` — `UFUNCTION(BlueprintCallable, Category = DataLayers)` — Toggles the DataLayer's IsLoadedInEditor flag @param	DataLayer						The DataLayer to affect @param	bIsFromUserChange				If this change originates from a user change or not.
- L564 _public prototype_ `bool ToggleDataLayersIsLoadedInEditor(const TArray<UDataLayerInstance*>& DataLayers, const bool bIsFromUserChange);` — `UFUNCTION(BlueprintCallable, Category = DataLayers)` — Toggles the IsLoadedInEditor flag of all of the DataLayers @param	DataLayers						The DataLayers to affect @param	bIsFromUserChange				If this change originates from a user change or not.
- L570 _public prototype_ `void MakeAllDataLayersVisible();` — `UFUNCTION(BlueprintCallable, Category = DataLayers)` — Set the visibility of all DataLayers to true
- L579 _public prototype_ `UDataLayerInstance* GetDataLayerInstance(const UDataLayerAsset* DataLayerAsset) const;` — `UFUNCTION(BlueprintCallable, Category = DataLayers)` — Gets the UDataLayerInstance associated to the DataLayerAsset @param	DataLayerAsset	The DataLayerAsset associated to the UDataLayerInstance @return					The UDataLayerInstance of the provided DataLayerAsset
- L588 _public prototype_ `TArray<UDataLayerInstance*> GetDataLayerInstances(const TArray<UDataLayerAsset*> DataLayerAssets) const;` — `UFUNCTION(BlueprintCallable, Category = DataLayers)` — Gets the UDataLayerInstances associated to the each DataLayerAssets @param	DataLayerAssets	The array of DataLayerAssets associated to UDataLayerInstances @return					The array of UDataLayerInstances corresponding to a DataLayerAsset in the DataLayerAssets array
- L596 _public prototype_ `UDataLayerInstance* GetDataLayerInstance(const FName& DataLayerInstanceName) const;` — Gets the UDataLayerInstance Object of the DataLayer name @param	DataLayerName	The name of the DataLayer whose UDataLayerInstance Object is returned @return					The UDataLayerInstance Object of the provided DataLayer name
- L603 _public prototype_ `void AddAllDataLayersTo(TArray<TWeakObjectPtr<UDataLayerInstance>>& OutDataLayers) const;` — Gets all known DataLayers and appends them to the provided array @param OutDataLayers[OUT] Output array to store all known DataLayers
- L612 _public prototype_ `UDataLayerInstance* CreateDataLayerInstance(const FDataLayerCreationParameters& Parameters);` — `UFUNCTION(BlueprintCallable, Category = DataLayers)` — Creates a UDataLayerInstance Object @param	Parameters The Data Layer Instance creation parameters @return	The newly created UDataLayerInstance Object
- L623 _public prototype_ `bool SetParentDataLayer(UDataLayerInstance* DataLayer, UDataLayerInstance* ParentDataLayer);` — `UFUNCTION(BlueprintCallable, Category = DataLayers)` — Sets a Parent DataLayer for a specified DataLayer @param DataLayer		The child DataLayer. @param ParentDataLayer	The parent DataLayer. @return	true if succeeded, false if failed.
- L632 _public prototype_ `void SetParentDataLayerForDataLayers(const TArray<UDataLayerInstance*>& DataLayers, UDataLayerInstance* ParentDataLayer);` — `UFUNCTION(BlueprintCallable, Category = DataLayers)` — Sets a Parent DataLayer for a specified list of DataLayers @param DataLayers		The child DataLayers. @param ParentDataLayer	The parent DataLayer.
- L641 _public prototype_ `void SetDataLayerInitialRuntimeState(UDataLayerInstance* DataLayer, EDataLayerRuntimeState InitialRuntimeState);` — `UFUNCTION(BlueprintCallable, Category = DataLayers)` — Sets the initial runtime state of the DataLayers @param	DataLayer						The DataLayer to affect @param	InitialRuntimeState				The initial runtime state.
- L650 _public prototype_ `void SetDataLayerIsInitiallyVisible(UDataLayerInstance* DataLayer, bool bIsInitiallyVisible);` — `UFUNCTION(BlueprintCallable, Category = DataLayers)` — Sets the initial editor visibility state of the DataLayers @param	DataLayer						The DataLayer to affect @param	InitialRuntimeState				The initial editor visibility state.
- L658 _public prototype_ `void DeleteDataLayers(const TArray<UDataLayerInstance*>& DataLayersToDelete);` — `UFUNCTION(BlueprintCallable, Category = DataLayers)` — Deletes all of the provided DataLayers @param DataLayersToDelete	A valid list of DataLayer.
- L666 _public prototype_ `void DeleteDataLayer(UDataLayerInstance* DataLayerToDelete);` — `UFUNCTION(BlueprintCallable, Category = DataLayers)` — Deletes the provided DataLayer @param DataLayerToDelete		A valid DataLayer
- L672 _public prototype_ `TArray<UDataLayerInstance*> GetAllDataLayers();` — `UFUNCTION(BlueprintCallable, Category = DataLayers)` — Returns all Data Layers
- L677 _public prototype_ `bool ResetUserSettings();` — Resets user override settings of all DataLayers
- L682 _public function_ `bool DoesDataLayerContainSelectedActors(const UDataLayerInstance* DataLayer) const` — Returns whether the DataLayer contains one of more actors that are part of the editor selection.
- L688 _public function_ `bool HasDeprecatedDataLayers() const` — `UE_DEPRECATED(5.8, "Deprecated data layers should have been removed by now.")` — Whether there are any deprecated DataLayerInstance found
- L693 _public prototype_ `bool SetDataLayerShortName(UDataLayerInstance* InDataLayerInstance, const FString& InNewShortName);` — Assign new unique short name to DataLayerInstance if it supports it.
- L700 _public prototype_ `bool ApplyActorEditorContextDataLayersToActors(const TArray<AActor*>& InActors);` — Move actors to the Actor Editor Context's Data Layers. @return true if operation succeeded.
- L703 _public prototype_ `bool PassDataLayersFilter(UWorld* World, const FWorldPartitionHandle& ActorHandle);` — Returns whether the actor handle passes the data layers filter.
- L711 _public function_ `void UpdateAllViewVisibility(UDEPRECATED_DataLayer* DataLayerThatChanged)` — `UE_DEPRECATED(all, "Per-view Data Layer visibility was removed.")` — `UFUNCTION(BlueprintCallable, Category = DataLayers, meta = (DeprecatedFunction, DeprecationMessage = "Per-view Data Layer visibility was removed."))`
- L715 _public function_ `void UpdateActorAllViewsVisibility(AActor* Actor)` — `UE_DEPRECATED(all, "Per-view Data Layer visibility was removed.")` — `UFUNCTION(BlueprintCallable, Category = DataLayers, meta = (DeprecatedFunction, DeprecationMessage = "Per-view Data Layer visibility was removed."))`
- L719 _public function_ `bool SetDataLayerIsDynamicallyLoadedInEditor(UDEPRECATED_DataLayer* DataLayer, const bool bIsLoadedInEditor, const bool bIsFromUserChange)` — `UE_DEPRECATED(all, "Use SetDataLayerIsLoadedInEditor() instead.")` — `UFUNCTION(BlueprintCallable, Category = DataLayers, meta = (DeprecatedFunction, DeprecationMessage = "Use SetDataLayerIsLoadedInEditor instead"))`
- L723 _public function_ `bool SetDataLayersIsDynamicallyLoadedInEditor(const TArray<UDEPRECATED_DataLayer*>& DataLayers, const bool bIsLoadedInEditor, const bool bIsFromUserChange)` — `UE_DEPRECATED(all, "Use SetDataLayersIsLoadedInEditor() instead.")` — `UFUNCTION(BlueprintCallable, Category = DataLayers, meta = (DeprecatedFunction, DeprecationMessage = "Use SetDataLayersIsLoadedInEditor instead"))`
- L727 _public function_ `bool ToggleDataLayerIsDynamicallyLoadedInEditor(UDEPRECATED_DataLayer* DataLayer, const bool bIsFromUserChange)` — `UE_DEPRECATED(all, "Use ToggleDataLayerIsLoadedInEditor() instead.")` — `UFUNCTION(BlueprintCallable, Category = DataLayers, meta = (DeprecatedFunction, DeprecationMessage = "Use ToggleDataLayerIsLoadedInEditor instead"))`
- L731 _public function_ `bool ToggleDataLayersIsDynamicallyLoadedInEditor(const TArray<UDEPRECATED_DataLayer*>& DataLayers, const bool bIsFromUserChange)` — `UE_DEPRECATED(all, "Use ToggleDataLayersIsLoadedInEditor() instead.")` — `UFUNCTION(BlueprintCallable, Category = DataLayers, meta = (DeprecatedFunction, DeprecationMessage = "Use ToggleDataLayersIsLoadedInEditor instead"))`
- L735 _public function_ `UDataLayerInstance* GetDataLayer(const struct FActorDataLayer& ActorDataLayer) const` — `UE_DEPRECATED(all, "Use GetDataLayerInstance instead")` — `UFUNCTION(meta = (DeprecatedFunction, DeprecationMessage = "Use GetDataLayerInstance instead"))`
- L741 _public function_ `UDataLayerInstance* GetDataLayerFromLabel(const FName& DataLayerLabel) const` — `UE_DEPRECATED(all, "Use GetDataLayerInstance instead")` — `UFUNCTION(meta = (DeprecatedFunction, DeprecationMessage = "Use GetDataLayerInstance instead"))`
- L745 _public function_ `bool RenameDataLayer(UDataLayerInstance* DataLayer, const FName& NewDataLayerLabel)` — `UE_DEPRECATED(all, "Renaming is not permitted anymore")` — `UFUNCTION(meta = (DeprecatedFunction, DeprecationMessage = "Renaming is not permitted anymore"))`
- L749 _public function_ `UDataLayerInstance* CreateDataLayer(UDataLayerInstance* ParentDataLayer = nullptr)` — `UE_DEPRECATED(all, "Use CreateDataLayerInstance with FDataLayerCreationParameters instead")` — `UFUNCTION(meta = (DeprecatedFunction, DeprecationMessage = "Use CreateDataLayerInstance with FDataLayerCreationParameters instead"))`
- L760 _private prototype_ `void InitializeNewActorDataLayers(AActor* Actor);` — Synchronizes an newly created Actor's DataLayers with the DataLayer system @param	Actor	The actor to initialize
- L767 _private prototype_ `TArray<AActor*> GetSelectedActors() const;` — Find and return the selected actors. @return				The selected AActor's as a TArray.
- L774 _private prototype_ `UWorld* GetWorld() const;` — Get the current UWorld object. @return						The UWorld* object
- L777 _private prototype_ `void EditorMapChange();` — Delegate handler for FEditorDelegates::MapChange. It internally calls DataLayerChanged.Broadcast.
- L780 _private prototype_ `void EditorRefreshDataLayerBrowser();` — Delegate handler for FEditorDelegates::RefreshDataLayerBrowser. It internally calls UpdateAllActorsVisibility to refresh the actors of each DataLayer.
- L783 _private prototype_ `void PostUndoRedo();` — Delegate handler for FEditorDelegates::PostUndoRedo. It internally calls DataLayerChanged.Broadcast and UpdateAllActorsVisibility to refresh the actors of each DataLayer.
- L785 _private prototype_ `void UpdateRegisteredWorldDelegates();`
- L786 _private prototype_ `void OnWorldPartitionInitialized(UWorldPartition* InWorldPartition);`
- L787 _private prototype_ `void OnWorldPartitionUninitialized(UWorldPartition* InWorldPartition);`
- L788 _private prototype_ `void OnLoadedActorAddedToLevel(AActor& InActor);`
- L789 _private prototype_ `void OnDataLayerEditorLoadingStateChanged(bool bIsFromUserChange);`
- L791 _private prototype_ `bool SetDataLayerIsLoadedInEditorInternal(UDataLayerInstance* DataLayer, const bool bIsLoadedInEditor, const bool bIsFromUserChange);`
- L793 _private prototype_ `void BroadcastActorDataLayersChanged(const TWeakObjectPtr<AActor>& ChangedActor);`
- L794 _private prototype_ `void BroadcastDataLayerChanged(const EDataLayerAction Action, const TWeakObjectPtr<const UDataLayerInstance>& ChangedDataLayer, const FName& ChangedProperty);`
- L795 _private prototype_ `void BroadcastDataLayerEditorLoadingStateChanged(bool bIsFromUserChange);`
- L796 _private prototype_ `void OnSelectionChanged();`
- L797 _private prototype_ `void RebuildSelectedDataLayersFromEditorSelection();`
- L798 _private prototype_ `const TSet<TWeakObjectPtr<const UDataLayerInstance>>& GetSelectedDataLayersFromEditorSelection() const;`
- L799 _private prototype_ `bool SetParentDataLayerForDataLayersInternal(const TArray<UDataLayerInstance*>& DataLayers, UDataLayerInstance* ParentDataLayer);`
- L801 _private prototype_ `bool UpdateAllActorsVisibility(const bool bNotifySelectionChange, const bool bRedrawViewports, ULevel* InLevel);`
- L803 _private prototype_ `bool IsActorValidForDataLayerForClasses(AActor* Actor, const TSet<TSubclassOf<UDataLayerInstance>>& DataLayerInstanceClasses);`
- L806 _private prototype_ `void OnActorPreSpawnInitialization(AActor* InActor);` — External Data Layer methods
- L807 _private prototype_ `void OnNewActorsPlaced(UObject* InObjToUse, const TArray<AActor*>& InPlacedActors);`
- L808 _private prototype_ `void OnEditorActorReplaced(AActor* InOldActor, AActor* InNewActor);`
- L809 _private prototype_ `void OnExternalDataLayerAssetRegistrationStateChanged(const UExternalDataLayerAsset* ExternalDataLayerAsset, EExternalDataLayerRegistrationState OldState, EExternalDataLayerRegistrationState NewState);`
- L810 _private prototype_ `TUniquePtr<FLevelEditorDragDropWorldSurrogateReferencingObject> OnLevelEditorDragDropWorldSurrogateReferencingObject(UWorld* ReferencingWorld, const FSoftObjectPath& Object);`
- L811 _private prototype_ `void ApplyContext(AActor* InActor, bool bInForceTryApply = false, AActor* InReplacedActor = nullptr);`
- L812 _private prototype_ `const UExternalDataLayerInstance* GetActorSpawningExternalDataLayerInstance(AActor* InActor) const;`
- L813 _private prototype_ `static const UExternalDataLayerAsset* GetReferencingWorldSurrogateObjectForObject(UWorld* ReferencingWorld, const FSoftObjectPath& ObjectPath);`
- L814 _private prototype_ `bool MoveActorToDataLayers(AActor* InActor, const TArray<UDataLayerInstance*>& InDataLayerInstances);`
- L815 _private prototype_ `void MoveActorToExternalDataLayer(AActor* InActor, const UExternalDataLayerInstance* InExternalDataLayerInstance, bool bInNotifyFailureReason = true);`
- L816 _private prototype_ `bool ShouldHandleActor(AActor* InActor) const;`
- L819 _private member_ `mutable TSet<TWeakObjectPtr<const UDataLayerInstance>> SelectedDataLayersFromEditorSelection;` — Contains Data Layers that contain actors that are part of the editor selection
- L822 _private member_ `mutable bool bRebuildSelectedDataLayersFromEditorSelection;` — Internal flag to know if SelectedDataLayersFromEditorSelection needs to be rebuilt.
- L825 _private member_ `bool bAsyncBroadcastDataLayerChanged;` — When true, next Tick will call BroadcastDataLayerChanged
- L828 _private member_ `bool bAsyncUpdateAllActorsVisibility;` — When true, next Tick will call UpdateAllActorsVisibility
- L831 _private member_ `bool bAsyncInvalidateViewports;` — When true, next Tick will force invalid editing viewports
- L834 _private member_ `FOnDataLayerChanged DataLayerChanged;` — Fires whenever one or more DataLayer changes
- L837 _private member_ `FOnActorDataLayersChanged ActorDataLayersChanged;` — Fires whenever one or more actor DataLayer changes
- L840 _private member_ `FOnActorDataLayersEditorLoadingStateChanged DataLayerEditorLoadingStateChanged;` — Fires whenever one or more DataLayer editor loading state changed
- L842 _private member_ `FDelegateHandle OnActorDataLayersEditorLoadingStateChangedEngineBridgeHandle;`
- L845 _private member_ `TSharedPtr<class FDataLayersBroadcast> DataLayersBroadcast;` — Auxiliary class that sets the callback functions for multiple delegates
- L848 _private member_ `FOnActorEditorContextClientChanged ActorEditorContextClientChanged;` — Delegate used to notify changes to ActorEditorContextSubsystem
- L851 _private member_ `TWeakObjectPtr<UWorld> LastRegisteredWorldDelegates;` — Last World to have registered world delegates
- L854 _private member_ `FDelegateHandle OnActorPreSpawnInitializationDelegate;` — Delegate handle for world's AddOnActorPreSpawnInitialization
- L857 _private member_ `TOptional<FText> LastWarningNotification;` — Last pushed warning to be send to the notification manager at next tick
- L866 _function_ `template<class DataLayerInstanceType, typename ...Args> DataLayerInstanceType* UDataLayerEditorSubsystem::CreateDataLayerInstance(AWorldDataLayers* WorldDataLayers, Args&&... InArgs)`

#### Free symbols / members of external scopes

- L34 _macro_ `#define UE_API DATALAYEREDITOR_API`
- L52 _namespace_ `namespace WorldPartitionTests`
- L159 _delegate_ `DECLARE_EVENT_ThreeParams(UDataLayerEditorSubsystem, FOnDataLayerChanged, const EDataLayerAction , const TWeakObjectPtr<const UDataLayerInstance>& , const FName& );` — Broadcasts whenever one or more DataLayers are modified Actions Add    : The specified ChangedDataLayer is a newly created UDataLayerInstance Modify : The specified ChangedDataLayer was just modified, if ChangedDataLayer is invalid then multiple DataLayers were modified. ChangedProperty specifies what field on the UDataLayerInstance was changed, if NAME_None then multiple fields were changed Delete : A DataLayer was deleted Rename : The specified ChangedDataLayer was just renamed Reset  : A large amount of changes have occurred to a number of DataLayers.
- L163 _delegate_ `DECLARE_EVENT_OneParam(UDataLayerEditorSubsystem, FOnActorDataLayersChanged, const TWeakObjectPtr<AActor>& );` — Broadcasts whenever one or more Actors changed UDataLayerInstances
- L167 _delegate_ `DECLARE_EVENT_OneParam(UDataLayerEditorSubsystem, FOnActorDataLayersEditorLoadingStateChanged, bool );` — Broadcasts whenever one or more DataLayers editor loading state changed

### `Source/Editor/DataLayerEditor/Public/DataLayer/DataLayerFactory.h` (Public)


#### class `UDataLayerFactory`  
`class UDataLayerFactory : public UFactory`  
_L19-26_
- reflection: `UCLASS(hidecategories = Object, MinimalAPI)`
- inherits: `UFactory`
- L24 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

### `Source/Editor/DataLayerEditor/Public/DataLayer/DataLayerPropertyTypeCustomizationHelper.h` (Public)


#### struct `FDataLayerPropertyTypeCustomizationHelper`  
`struct FDataLayerPropertyTypeCustomizationHelper`  
_L15-18_
- L17 _public function_ `static TSharedRef<SWidget> CreateDataLayerMenu(TFunction<void(const UDataLayerInstance* DataLayer)> OnDataLayerSelectedFunction, TFunction<bool(const UDataLayerInstance*)> OnShouldFilterDataLayerInstanceFunction = [](const UDataLayerInstance*){ return false; });`
- L17 _public prototype_ `static TSharedRef<SWidget> CreateDataLayerMenu(TFunction<void(const UDataLayerInstance* DataLayer)> OnDataLayerSelectedFunction, TFunction<bool(const UDataLayerInstance*)> OnShouldFilterDataLayerInstanceFunction = [](const UDataLayerInstance*){ return false; });`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API DATALAYEREDITOR_API`

### `Source/Editor/DataLayerEditor/Public/DataLayer/ExternalDataLayerFactory.h` (Public)


#### class `UExternalDataLayerFactory`  
`class UExternalDataLayerFactory : public UFactory`  
_L10-18_
- reflection: `UCLASS(hidecategories = Object, MinimalAPI)`
- inherits: `UFactory`
- L15 _private prototype_ `virtual bool CanCreateNew() const override;`
- L16 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

### `Source/Editor/DataLayerEditor/Public/DataLayerEditorModule.h` (Public)


#### class `FDataLayerEditorModule`  
`class FDataLayerEditorModule : public IDataLayerEditorModule`  
_L25-68_
- inherits: `IDataLayerEditorModule`
- desc: The module holding all of the UI related pieces for DataLayers
- L32 _public prototype_ `virtual void StartupModule();` — Called right after the module DLL has been loaded and the module object has been created
- L37 _public prototype_ `virtual void ShutdownModule();` — Called before the module is unloaded, right before the module object is destroyed.
- L42 _public prototype_ `virtual TSharedRef<class SWidget> CreateDataLayerBrowser();` — Creates a DataLayer Browser widget
- L47 _public prototype_ `virtual void SyncDataLayerBrowserToDataLayer(const UDataLayerInstance* DataLayer);` — Selected DataLayer in DataLayer Browser widget
- L50 _public typedef_ `typedef TPair<TWeakObjectPtr<const UDataLayerInstance>, TWeakObjectPtr<const AActor>> FDataLayerActor;` — Delegates to be called to extend the DataLayers menus
- L51 _public prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(TSharedRef<FExtender>, FDataLayersMenuExtender, const TSharedRef<FUICommandList>, const TSet<TWeakObjectPtr<const UDataLayerInstance>>& , const TSet<FDataLayerActor>& );`
- L52 _public function_ `virtual TArray<FDataLayersMenuExtender>& GetAllDataLayersMenuExtenders()`
- L55 _public prototype_ `virtual bool AddActorToDataLayers(AActor* Actor, const TArray<UDataLayerInstance*>& DataLayers) override;` — Implement IDataLayerEditorModule
- L56 _public prototype_ `virtual void SetActorEditorContextCurrentExternalDataLayer(const UExternalDataLayerAsset* InExternalDataLayerAsset) override;`
- L59 _private prototype_ `void RegisterMenus();`
- L60 _private prototype_ `void MoveToExternalDataLayerMenu(UToolMenu* Menu);`
- L61 _private prototype_ `bool MoveActorsToExternalDataLayer(const TArray<AActor*>& InSelectedActors, const UExternalDataLayerInstance* InExternalDataLayerInstance, FText* OutReason = nullptr);`
- L62 _private prototype_ `TArray<AActor*> GetSelectedActors() const;`
- L64 _private member_ `TWeakPtr<SWidget> DataLayerBrowser;`
- L67 _private member_ `TArray<FDataLayersMenuExtender> DataLayersMenuExtenders;` — All extender delegates for the DataLayers menus

#### Free symbols / members of external scopes

- L51 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(TSharedRef<FExtender>, FDataLayersMenuExtender, const TSharedRef<FUICommandList>, const TSet<TWeakObjectPtr<const UDataLayerInstance>>& , const TSet<FDataLayerActor>& );`
