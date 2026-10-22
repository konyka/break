# Plugins / LevelSnapshotsEditor

- module root: `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshotsEditor`
- headers: 42; symbols: 797
- symbol kinds: class=36, delegate=22, enum=5, enumerator=30, function=43, macro=1, member=221, namespace=4, prototype=420, struct=7, typedef=5, variable=3
- PrivateDependencyModuleNames: ApplicationCore, AssetDefinition, AssetRegistry, AssetTools, BlueprintGraph, ContentBrowser, CoreUObject, EditorFramework, EditorStyle, EditorWidgets, Engine, EngineAssetDefinitions, GameProjectGeneration, InputCore, Kismet, LevelSnapshotFilters, LevelSnapshots, Projects, PropertyEditor, Slate, SlateCore, ToolMenus, ToolWidgets, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: Core

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshotsEditor/Private/AssetDefinition/AssetDefinition_LevelSnapshot.h` (Private)


#### class `UAssetDefinition_LevelSnapshot`  
`class UAssetDefinition_LevelSnapshot : public UAssetDefinitionDefault`  
_L9-21_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L15 _public prototype_ `virtual FText GetAssetDisplayName() const override;` — UAssetDefinition Begin
- L16 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L17 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L18 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L19 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshotsEditor/Private/AssetDefinition/AssetDefinition_LevelSnapshotFilter.h` (Private)


#### class `UAssetDefinition_LevelSnapshotFilter`  
`class UAssetDefinition_LevelSnapshotFilter : public UAssetDefinition_Blueprint`  
_L10-21_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_Blueprint`
- L16 _public prototype_ `virtual FText GetAssetDisplayName() const override;` — UAssetDefinition Begin
- L17 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L18 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L19 _public prototype_ `virtual UFactory* GetFactoryForBlueprintType(UBlueprint* InBlueprint) const override;`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshotsEditor/Private/Customizations/NegatableFilterDetailsCustomization.h` (Private)


#### class `FNegatableFilterDetailsCustomization`  
`class FNegatableFilterDetailsCustomization : public IDetailCustomization`  
_L9-18_
- inherits: `IDetailCustomization`
- desc: Exposes invertability and name properties on UNegatableFilter. Also shows subobject properties inline.
- L15 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshotsEditor/Private/Data/DragDrop/FavoriteFilterDragDrop.h` (Private)


#### class `FFavoriteFilterDragDrop`  
`class FFavoriteFilterDragDrop : public FDragDropOperation`  
_L15-37_
- inherits: `FDragDropOperation`
- desc: Governs interaction when a user drags a favorite filter.
- L19 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FFavoriteFilterDragDrop, FDragDropOperation);`
- L21 _public prototype_ `FFavoriteFilterDragDrop(const TSubclassOf<ULevelSnapshotFilter>& InClassToInstantiate, ULevelSnapshotsEditorData* InSelectedFilterSetter);`
- L23 _public prototype_ `void OnEnterRow(const TSharedRef<SLevelSnapshotsEditorFilterRow>& EnteredRow);`
- L24 _public prototype_ `void OnLeaveRow(const TSharedRef<SLevelSnapshotsEditorFilterRow>& LeftRow);`
- L25 _public prototype_ `bool OnDropOnRow(const TSharedRef<SLevelSnapshotsEditorFilterRow>& DroppedOnRow);`
- L29 _private prototype_ `void ShowCannotDropFilter();`
- L30 _private prototype_ `void ShowCanDropFilter();`
- L31 _private prototype_ `void ShowFeedbackMessage(const FSlateBrush* Icon, const FText& Message);`
- L33 _private member_ `const TSubclassOf<ULevelSnapshotFilter> ClassToInstantiate;`
- L35 _private member_ `const TWeakObjectPtr<ULevelSnapshotsEditorData> SelectedFilterSetter;` — Used to set the filter being edited to newly created one.

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshotsEditor/Private/Data/FavoriteFilterContainer.h` (Private)


#### class `UFavoriteFilterContainer`  
`class UFavoriteFilterContainer : public UObject`  
_L16-71_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Keeps track of selected favorite filters.
- L22 _public prototype_ `virtual void PostInitProperties() override;`
- L23 _public prototype_ `virtual void BeginDestroy() override;`
- L26 _public prototype_ `void AddToFavorites(const TSubclassOf<ULevelSnapshotFilter>& NewFavoriteClass);`
- L27 _public prototype_ `void RemoveFromFavorites(const TSubclassOf<ULevelSnapshotFilter>& NoLongerFavoriteClass);`
- L28 _public prototype_ `void ClearFavorites();`
- L30 _public prototype_ `bool ShouldIncludeAllClassesInCategory(FName CategoryName) const;`
- L31 _public prototype_ `void SetShouldIncludeAllClassesInCategory(FName CategoryName, bool bShouldIncludeAll);`
- L33 _public prototype_ `const TArray<TSubclassOf<ULevelSnapshotFilter>>& GetFavorites() const;`
- L35 _public prototype_ `TArray<TSubclassOf<ULevelSnapshotFilter>> GetCommonFilters() const;` — Gets filters with the CommonSnapshotFilter uclass meta tag.
- L37 _public prototype_ `TArray<TSubclassOf<ULevelSnapshotFilter>> GetAllAvailableFilters() const;` — Gets all valid filter subclasses
- L39 _public prototype_ `TArray<FName> GetCategories() const;`
- L40 _public prototype_ `FText CategoryNameToText(FName CategoryName) const;`
- L41 _public prototype_ `TArray<TSubclassOf<ULevelSnapshotFilter>> GetFiltersInCategory(FName CategoryName) const;`
- L43 _public prototype_ `DECLARE_EVENT(UFavoriteFilterContainer, FOnFavoritesModified);`
- L44 _public member_ `FOnFavoritesModified OnFavoritesChanged;`
- L48 _private prototype_ `void CleanseFavorites();`
- L50 _private prototype_ `void SetIncludeAllNativeClasses(bool bShouldIncludeNative);`
- L51 _private prototype_ `void SetIncludeAllBlueprintClasses(bool bShouldIncludeBlueprint);`
- L52 _private prototype_ `bool ShouldIncludeAllNativeClasses() const;`
- L53 _private prototype_ `bool ShouldIncludeAllBlueprintClasses() const;`
- L56 _private prototype_ `const TArray<TSubclassOf<ULevelSnapshotFilter>>& GetAvailableNativeFilters() const;` — Gets C++ filters without CommonSnapshotFilter tag.
- L58 _private prototype_ `TArray<TSubclassOf<ULevelSnapshotBlueprintFilter>> GetAvailableBlueprintFilters() const;` — Gets Blueprint filters without CommonSnapshotFilter tag; they cannot have this tag btw.
- L64 _private member_ `TArray<TSubclassOf<ULevelSnapshotFilter>> Favorites;` — `UPROPERTY()` — The filters the user selected to use.
- L66 _private member_ `bool bIncludeAllNativeClasses = false;`
- L67 _private member_ `bool bIncludeAllBlueprintClasses = false;`
- L70 _private member_ `FDelegateHandle OnAssetDeleted;` — So we can remove any filter classes that were favourited

#### Free symbols / members of external scopes

- L43 _delegate_ `DECLARE_EVENT(UFavoriteFilterContainer, FOnFavoritesModified);`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshotsEditor/Private/Data/FilterListData.h` (Private)


#### struct `FFilterListData`  
`struct FFilterListData`  
_L14-34_
- desc: Contains all data required to display the filter results panel.
- L16 _public prototype_ `void UpdateFilteredList(UWorld* World, ULevelSnapshot* FromSnapshot, ULevelSnapshotFilter* FilterToApply);`
- L19 _public prototype_ `TWeakObjectPtr<AActor> GetSnapshotCounterpartFor(const AActor* WorldActor) const;` — If WorldActor is modified, returns the deserialized actor. If WorldActor is not modified, returns itself.
- L21 _public prototype_ `void ForEachModifiedActor(TFunctionRef<void(AActor*)> Callback) const;`
- L22 _public prototype_ `bool HasAnyModifiedActors() const;`
- L24 _public function_ `const FPropertySelectionMap& GetModifiedEditorObjectsSelectedProperties_AllowedByFilter() const`
- L25 _public function_ `const TSet<FSoftObjectPath>& GetRemovedOriginalActorPaths_AllowedByFilter() const`
- L26 _public function_ `const TSet<TWeakObjectPtr<AActor>>& GetAddedWorldActors_AllowedByFilter() const`
- L30 _private member_ `TWeakObjectPtr<ULevelSnapshot> RelatedSnapshot = nullptr;`
- L33 _private member_ `FPropertySelectionMap SelectionMap;` — Selected properties for actors allowed by filters.

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshotsEditor/Private/Data/FilterLoader.h` (Private)


#### class `UFilterLoader`  
`class UFilterLoader : public UObject`  
_L16-53_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Handles saving and loading of UDisjunctiveNormalFormFilter.
- L21 _public prototype_ `void OverwriteExisting();`
- L22 _public prototype_ `void SaveAs();`
- L23 _public prototype_ `void LoadAsset(const FAssetData& PickedAsset);`
- L25 _public prototype_ `TOptional<FAssetData> GetAssetLastSavedOrLoaded() const;`
- L28 _public prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& TransactionEvent) override;`
- L31 _public prototype_ `DECLARE_EVENT_OneParam(UFilterLoader, FOnLoadedFilters, ULevelSnapshotsFilterPreset*);`
- L33 _public member_ `FOnLoadedFilters OnFilterChanged;` — Called to notify everybody that the user now wants to edit this filter.
- L35 _public prototype_ `DECLARE_EVENT(UFilterLoader, FOnFilterWasSavedOrLoaded);`
- L37 _public member_ `FOnFilterWasSavedOrLoaded OnFilterWasSavedOrLoaded;` — Used by UI to know when SaveLoaded option may be shown.
- L42 _private prototype_ `void SetAssetBeingEdited(ULevelSnapshotsFilterPreset* NewAssetBeingEdited);`
- L44 _private prototype_ `void OnSaveOrLoadAssetOnDisk(ULevelSnapshotsFilterPreset* AssetOnDisk);`
- L45 _private prototype_ `void SetAssetLastSavedOrLoaded(ULevelSnapshotsFilterPreset* NewAsset);`
- L49 _private member_ `FSoftObjectPath AssetLastSavedOrLoaded = nullptr;` — `UPROPERTY()` — Set once user either has used RequestSaveAs or SetPickedAsset.
- L52 _private member_ `TObjectPtr<ULevelSnapshotsFilterPreset> AssetBeingEdited;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L31 _delegate_ `DECLARE_EVENT_OneParam(UFilterLoader, FOnLoadedFilters, ULevelSnapshotsFilterPreset*);`
- L35 _delegate_ `DECLARE_EVENT(UFilterLoader, FOnFilterWasSavedOrLoaded);`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshotsEditor/Private/Data/FilteredResults.h` (Private)


#### class `UFilteredResults`  
`class UFilteredResults : public UObject`  
_L18-48_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Processes user defined filters into a selection set, which the user inspect in the results tab.
- L23 _public prototype_ `void CleanReferences();`
- L25 _public prototype_ `void SetActiveLevelSnapshot(ULevelSnapshot* InActiveLevelSnapshot);`
- L26 _public prototype_ `void SetUserFilters(ULevelSnapshotFilter* InUserFilters);`
- L29 _public prototype_ `void UpdateFilteredResults(UWorld* SelectedWorld);` — Extracts DeserializedActorsAndDesiredPaths and FilterResults is modified.
- L31 _public prototype_ `void SetPropertiesToRollback(const FPropertySelectionMap& InSelectionSet);`
- L32 _public prototype_ `const FPropertySelectionMap& GetPropertiesToRollback() const;`
- L34 _public prototype_ `FFilterListData& GetFilteredData();`
- L35 _public prototype_ `TWeakObjectPtr<ULevelSnapshotFilter> GetUserFilters() const;`
- L39 _private member_ `TWeakObjectPtr<ULevelSnapshot> UserSelectedSnapshot;`
- L42 _private member_ `FFilterListData FilteredData;` — Stores partially filtered data for displaying in filter results view.
- L44 _private member_ `TWeakObjectPtr<ULevelSnapshotFilter> UserFilters;`
- L47 _private member_ `FPropertySelectionMap PropertiesToRollback;` — Null until UpdatePropertiesToRollback is called.

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshotsEditor/Private/Data/Filters/ConjunctionFilter.h` (Private)


#### class `UConjunctionFilter`  
`class UConjunctionFilter : public ULevelSnapshotFilter`  
_L16-57_
- reflection: `UCLASS(meta = (InternalSnapshotFilter))`
- inherits: `ULevelSnapshotFilter`
- desc: Returns the result of and-ing all child filters. It is valid to have no children: in this case, this filter return false.
- L21 _public prototype_ `static FName GetChildrenMemberName();`
- L23 _public prototype_ `void MarkTransactional();`
- L28 _public prototype_ `UNegatableFilter* CreateChild(const TSubclassOf<ULevelSnapshotFilter>& FilterClass);` — Creates a new instance of FilterClass and places it in a new negatable filter. The resulting negatable filter is added as child.
- L30 _public prototype_ `void RemoveChild(UNegatableFilter* Child);` — Removes filter created by CreateChild.
- L31 _public prototype_ `const TArray<UNegatableFilter*>& GetChildren() const;`
- L33 _public prototype_ `void SetIsIgnored(bool Value);`
- L34 _public function_ `bool IsIgnored() const`
- L36 _public prototype_ `void OnRemoved();`
- L40 _public prototype_ `virtual EFilterResult::Type IsActorValid(const FIsActorValidParams& Params) const override;`
- L41 _public prototype_ `virtual EFilterResult::Type IsPropertyValid(const FIsPropertyValidParams& Params) const override;`
- L42 _public prototype_ `virtual EFilterResult::Type IsDeletedActorValid(const FIsDeletedActorValidParams& Params) const override;`
- L43 _public prototype_ `virtual EFilterResult::Type IsAddedActorValid(const FIsAddedActorValidParams& Params) const override;`
- L46 _public prototype_ `DECLARE_EVENT_OneParam(UConjunctionFilter, FOnChildModified, UNegatableFilter*);`
- L47 _public member_ `FOnChildModified OnChildAdded;`
- L48 _public member_ `FOnChildModified OnChildRemoved;`
- L53 _private member_ `TArray<TObjectPtr<UNegatableFilter>> Children;` — `UPROPERTY(Instanced)`
- L56 _private member_ `bool bIgnoreFilter = false;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L46 _delegate_ `DECLARE_EVENT_OneParam(UConjunctionFilter, FOnChildModified, UNegatableFilter*);`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshotsEditor/Private/Data/Filters/LevelSnapshotsFilterPreset.h` (Private)


#### enum `EFilterChangeType`  
`enum class EFilterChangeType : uint8`  
_L12-22_
- L15 _public enumerator_ `BlankRowAdded` — A blank row was added
- L17 _public enumerator_ `RowRemoved` — A row was removed
- L19 _public enumerator_ `RowChildFilterAddedOrRemoved` — A filter was added or removed to a row
- L21 _public enumerator_ `FilterPropertyModified` — A filter property was modified, e.g. set to ignored.

#### class `ULevelSnapshotsFilterPreset`  
`class ULevelSnapshotsFilterPreset : public ULevelSnapshotFilter`  
_L31-73_
- reflection: `UCLASS(meta = (InternalSnapshotFilter))`
- inherits: `ULevelSnapshotFilter`
- desc: Manages logic for combining filters in the editor. This filter may have no children: in this case, the filter returns true. Disjunctive normal form = ORs of ANDs. Example: (a && !b) || (c && d) || e
- L36 _public prototype_ `void MarkTransactional();`
- L39 _public prototype_ `UConjunctionFilter* CreateChild();` — Creates a new AND-filter and adds it to the list of children.
- L41 _public prototype_ `void RemoveConjunction(UConjunctionFilter* Child);` — Removes a filter previously created by CreateChild.
- L42 _public prototype_ `const TArray<UConjunctionFilter*>& GetChildren() const;`
- L45 _public prototype_ `virtual void BeginDestroy() override;`
- L49 _public prototype_ `virtual EFilterResult::Type IsActorValid(const FIsActorValidParams& Params) const override;`
- L50 _public prototype_ `virtual EFilterResult::Type IsPropertyValid(const FIsPropertyValidParams& Params) const override;`
- L51 _public prototype_ `virtual EFilterResult::Type IsDeletedActorValid(const FIsDeletedActorValidParams& Params) const override;`
- L52 _public prototype_ `virtual EFilterResult::Type IsAddedActorValid(const FIsAddedActorValidParams& Params) const override;`
- L62 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FModifyFilter, EFilterChangeType);` — Called when: - An AND row is added or removed - A negatable filter is added or removed - The properties of one of the filters is modified
- L63 _public member_ `FModifyFilter OnFilterModified;`
- L68 _private member_ `TArray<TObjectPtr<UConjunctionFilter>> Children;` — `UPROPERTY(Instanced)`
- L70 _private member_ `bool bHasJustCreatedNewChild = false;`
- L72 _private member_ `FDelegateHandle OnObjectTransactedHandle;`

#### Free symbols / members of external scopes

- L62 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FModifyFilter, EFilterChangeType);` — Called when: - An AND row is added or removed - A negatable filter is added or removed - The properties of one of the filters is modified

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshotsEditor/Private/Data/Filters/NegatableFilter.h` (Private)


#### enum `EFilterBehavior`  
`enum class EFilterBehavior : uint8`  
_L10-16_
- reflection: `UENUM()`
- L13 _public enumerator_ `DoNotNegate` — Pass on same result
- L15 _public enumerator_ `Negate` — Invert the result

#### class `UNegatableFilter`  
`class UNegatableFilter : public ULevelSnapshotFilter`  
_L22-69_
- reflection: `UCLASS(meta = (InternalSnapshotFilter))`
- inherits: `ULevelSnapshotFilter`
- desc: Calls a child filter and possibly negates its results.
- L28 _public prototype_ `static UNegatableFilter* CreateNegatableFilter(ULevelSnapshotFilter* ChildFilter, const TOptional<UObject*>& Outer = TOptional<UObject*>());` — Wraps the given filter with a negation. Defaults to ChildFilter's outer.
- L30 _public prototype_ `void SetFilterBehaviour(EFilterBehavior NewFilterBehavior);`
- L31 _public function_ `EFilterBehavior GetFilterBehavior() const`
- L33 _public prototype_ `void SetIsIgnored(bool Value);`
- L34 _public function_ `bool IsIgnored() const`
- L36 _public prototype_ `void OnRemoved();`
- L38 _public prototype_ `FText GetDisplayName() const;`
- L39 _public function_ `ULevelSnapshotFilter* GetChildFilter() const`
- L42 _public prototype_ `virtual EFilterResult::Type IsActorValid(const FIsActorValidParams& Params) const override;`
- L43 _public prototype_ `virtual EFilterResult::Type IsPropertyValid(const FIsPropertyValidParams& Params) const override;`
- L44 _public prototype_ `virtual EFilterResult::Type IsDeletedActorValid(const FIsDeletedActorValidParams& Params) const override;`
- L45 _public prototype_ `virtual EFilterResult::Type IsAddedActorValid(const FIsAddedActorValidParams& Params) const override;`
- L48 _public prototype_ `DECLARE_EVENT_OneParam(UNegatableFilter, FFilterDestroyed, UNegatableFilter*);`
- L49 _public member_ `FFilterDestroyed OnFilterDestroyed;`
- L55 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, Category = "Filter")` — Display name in editor. Defaults to class name if left empty.
- L61 _private member_ `EFilterBehavior FilterBehavior = EFilterBehavior::DoNotNegate;` — `UPROPERTY(EditAnywhere, Category = "Filter")` — Whether to pass on the result of the filter, negate it, or ignore it.
- L65 _private member_ `bool bIgnoreFilter = false;` — `UPROPERTY(EditAnywhere, Category = "Filter")` — Whether this filter should be ignored
- L68 _private member_ `TObjectPtr<ULevelSnapshotFilter> ChildFilter;` — `UPROPERTY(Instanced)`

#### Free symbols / members of external scopes

- L48 _delegate_ `DECLARE_EVENT_OneParam(UNegatableFilter, FFilterDestroyed, UNegatableFilter*);`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshotsEditor/Private/Data/LevelSnapshotsEditorData.h` (Private)


#### class `ULevelSnapshotsEditorData`  
`class ULevelSnapshotsEditorData : public UObject`  
_L21-123_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Stores all data shared across the editor's UI.
- L26 _public prototype_ `ULevelSnapshotsEditorData(const FObjectInitializer& ObjectInitializer);`
- L29 _public prototype_ `virtual void PostInitProperties() override;`
- L30 _public prototype_ `virtual void BeginDestroy() override;`
- L34 _public prototype_ `void CleanupAfterEditorClose();` — Called when the editor is about to be closed. Clears all pending subscriptions to avoid any memory leaks.
- L40 _public prototype_ `void SetActiveSnapshot(ULevelSnapshot* NewActiveSnapshot);` — @param NewActiveSnapshot Can be nullptr
- L41 _public function_ `void ClearActiveSnapshot()`
- L42 _public function_ `ULevelSnapshot* GetActiveSnapshot() const`
- L44 _public prototype_ `DECLARE_EVENT_OneParam(ULevelSnapshotsEditorData, FOnActiveSnapshotChanged, ULevelSnapshot* );`
- L45 _public member_ `FOnActiveSnapshotChanged OnActiveSnapshotChanged;`
- L50 _public prototype_ `static UWorld* GetEditorWorld();`
- L56 _public prototype_ `void SetEditedFilter(UNegatableFilter* InFilter);`
- L57 _public function_ `UNegatableFilter* GetEditedFilter() const`
- L58 _public function_ `bool IsEditingFilter(UNegatableFilter* Filter) const`
- L60 _public prototype_ `DECLARE_EVENT_OneParam(ULevelSnapshotsEditorData, FOnEditedFilterChanged, UNegatableFilter* );`
- L61 _public member_ `FOnEditedFilterChanged OnEditedFilterChanged;`
- L63 _public prototype_ `DECLARE_EVENT(ULevelSnapshotsEditorData, FOnRefreshResults);`
- L64 _public member_ `FOnRefreshResults OnRefreshResults;`
- L69 _public prototype_ `DECLARE_EVENT_TwoParams(ULevelSnapshotsEditorData, FUserDefinedFiltersChanged, ULevelSnapshotsFilterPreset* , ULevelSnapshotsFilterPreset* );`
- L71 _public member_ `FUserDefinedFiltersChanged OnUserDefinedFiltersChanged;` — Called when user loads a new set of filters.
- L76 _public prototype_ `UFavoriteFilterContainer* GetFavoriteFilters() const;`
- L77 _public prototype_ `ULevelSnapshotsFilterPreset* GetUserDefinedFilters() const;`
- L78 _public prototype_ `UFilterLoader* GetFilterLoader() const;`
- L79 _public prototype_ `UFilteredResults* GetFilterResults() const;`
- L81 _public prototype_ `void HandleFilterChange(EFilterChangeType FilterChangeType);`
- L82 _public prototype_ `bool IsFilterDirty() const;`
- L83 _public prototype_ `void SetIsFilterDirty(const bool bNewDirtyState);`
- L85 _public prototype_ `void HandleWorldActorsEdited(UObject* Object);`
- L89 _private member_ `FDelegateHandle OnWorldCleanup;`
- L90 _private member_ `FDelegateHandle OnObjectsEdited;`
- L91 _private member_ `FDelegateHandle TrackedFilterModifiedHandle;`
- L94 _private member_ `TObjectPtr<UFavoriteFilterContainer> FavoriteFilters;` — `UPROPERTY()`
- L97 _private member_ `TObjectPtr<ULevelSnapshotsFilterPreset> UserDefinedFilters;` — `UPROPERTY()` — Stores user-defined filters in chain of ORs of ANDs.
- L100 _private member_ `TObjectPtr<UFilterLoader> FilterLoader;` — `UPROPERTY()` — Handles save & load requests for exchanging UserDefinedFilters.
- L104 _private member_ `bool bIsFilterDirty = false;` — `UPROPERTY()` — Used for determining whether the filter state has changed since it was last refreshed.
- L108 _private member_ `bool bIsApplyingSnapshot = false;` — `UPROPERTY()` — Whether ActiveSnapshot is currently being restored. Does not allow changing the active snapshot while true.
- L112 _private member_ `TObjectPtr<UFilteredResults> FilterResults;` — `UPROPERTY()` — Converts UserDefinedFilters into ULevelSnapshotsSelectionSet display in results view.
- L116 _private member_ `TObjectPtr<ULevelSnapshot> ActiveSnapshot;` — `UPROPERTY()` — Snapshot selected by user
- L119 _private member_ `TObjectPtr<UNegatableFilter> EditedFilter;` — `UPROPERTY()` — Filter visible in details panel
- L121 _private function_ `void OnPreApplySnapshot()`
- L122 _private function_ `void OnPostApplySnapshot()`

#### Free symbols / members of external scopes

- L44 _delegate_ `DECLARE_EVENT_OneParam(ULevelSnapshotsEditorData, FOnActiveSnapshotChanged, ULevelSnapshot* );`
- L60 _delegate_ `DECLARE_EVENT_OneParam(ULevelSnapshotsEditorData, FOnEditedFilterChanged, UNegatableFilter* );`
- L63 _delegate_ `DECLARE_EVENT(ULevelSnapshotsEditorData, FOnRefreshResults);`
- L69 _delegate_ `DECLARE_EVENT_TwoParams(ULevelSnapshotsEditorData, FUserDefinedFiltersChanged, ULevelSnapshotsFilterPreset* , ULevelSnapshotsFilterPreset* );`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshotsEditor/Private/Data/UClassMetaDataDefinitions.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UClassMetaDataDefinitions`
- L15 _variable_ `const FName CommonSnapshotFilter("Com` (scope `UClassMetaDataDefinitions`) — This filter is shown directly in the favorite filter menu opposed to the native and blueprint filter submenus. Incompatible with InternalSnapshotFilter.
- L19 _variable_ `const FName InternalSnapshotFilter("Int` (scope `UClassMetaDataDefinitions`) — This filter does not show up in the favorite filter menu. Incompatible with CommonSnapshotFilter.

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshotsEditor/Private/Factories/LevelSnapshotEditorFactory.h` (Private)


#### class `ULevelSnapshotEditorFactory`  
`class ULevelSnapshotEditorFactory : public UFactory`  
_L10-21_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFactory`
- L16 _public prototype_ `ULevelSnapshotEditorFactory();`
- L18 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L19 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`
- L20 _public prototype_ `virtual uint32 GetMenuCategories() const override;`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshotsEditor/Private/Factories/LevelSnapshotFilterFactory.h` (Private)


#### class `ULevelSnapshotBlueprintFilterFactory`  
`class ULevelSnapshotBlueprintFilterFactory : public UFactory`  
_L11-28_
- reflection: `UCLASS(hidecategories = Object)`
- inherits: `UFactory`
- L15 _public prototype_ `ULevelSnapshotBlueprintFilterFactory();`
- L19 _public member_ `TSubclassOf<UObject> ParentClass;` — `UPROPERTY(VisibleAnywhere, Category="LevelSnapshotBlueprintFilterFactory", meta=(AllowAbstract = "", BlueprintBaseOnly = ""))` — The parent class of the created blueprint
- L22 _public prototype_ `virtual FText GetDisplayName() const override;`
- L23 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L24 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L25 _public prototype_ `virtual TArray<FAssetCategoryPath> GetAssetMenuPathsForCategory(FName InCategory) const override;`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshotsEditor/Private/LevelSnapshotsEditorCommands.h` (Private)


#### class `FLevelSnapshotsEditorCommands`  
`class FLevelSnapshotsEditorCommands : public TCommands<FLevelSnapshotsEditorCommands>`  
_L10-27_
- inherits: `TCommands<FLevelSnapshotsEditorCommands>`
- L14 _public function_ `FLevelSnapshotsEditorCommands() : TCommands<FLevelSnapshotsEditorCommands>(TEXT("LevelSnapshotsEditor"), NSLOCTEXT("Contexts", "LevelSnapshotsEditor", "Level Snapshots Editor"), NAME_None, FAppStyle::GetAppStyleSetName())`
- L19 _public prototype_ `virtual void RegisterCommands() override;`
- L21 _public member_ `TSharedPtr<FUICommandInfo> Apply;`
- L22 _public member_ `TSharedPtr<FUICommandInfo> UpdateResults;`
- L24 _public member_ `TSharedPtr<FUICommandInfo> UseCreationFormToggle;`
- L25 _public member_ `TSharedPtr<FUICommandInfo> OpenLevelSnapshotsEditorToolbarButton;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> LevelSnapshotsSettings;`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshotsEditor/Private/LevelSnapshotsEditorModule.h` (Private)


#### class `FLevelSnapshotsEditorModule`  
`class FLevelSnapshotsEditorModule : public IModuleInterface`  
_L19-58_
- inherits: `IModuleInterface`
- L23 _public prototype_ `static FLevelSnapshotsEditorModule& Get();`
- L24 _public prototype_ `static void OpenLevelSnapshotsSettings();`
- L27 _public prototype_ `virtual void StartupModule() override;`
- L28 _public prototype_ `virtual void ShutdownModule() override;`
- L31 _public function_ `static bool GetUseCreationForm()`
- L32 _public function_ `static void SetUseCreationForm(bool bInUseCreationForm)`
- L33 _public function_ `static void ToggleUseCreationForm()`
- L35 _public prototype_ `void OpenLevelSnapshotsDialogWithAssetSelected(const FAssetData& InAssetData);`
- L36 _public prototype_ `void OpenSnapshotsEditor();`
- L40 _private prototype_ `void RegisterTabSpawner();`
- L41 _private prototype_ `void UnregisterTabSpawner();`
- L43 _private prototype_ `TSharedRef<SDockTab> SpawnLevelSnapshotsTab(const FSpawnTabArgs& SpawnTabArgs);`
- L44 _private prototype_ `ULevelSnapshotsEditorData* AllocateTransientPreset();`
- L46 _private prototype_ `void RegisterEditorToolbar();`
- L47 _private prototype_ `void MapEditorToolbarActions();`
- L48 _private prototype_ `TSharedRef<SWidget> FillEditorToolbarComboButtonMenuOptions(TSharedPtr<class FUICommandList> Commands);`
- L52 _private member_ `TSharedPtr<FUICommandList> EditorToolbarButtonCommandList;` — Command list (for combo button sub menu options)
- L55 _private member_ `TWeakPtr<SLevelSnapshotsEditor> WeakSnapshotEditor;` — Lives for as long as the UI is open.
- L57 _private member_ `TSharedPtr<ISettingsSection> DataMangementSettingsSectionPtr;`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshotsEditor/Private/LevelSnapshotsEditorSettings.h` (Private)


#### class `ULevelSnapshotsEditorSettings`  
`class ULevelSnapshotsEditorSettings : public UObject`  
_L15-82_
- reflection: `UCLASS(config = Engine, defaultconfig)`
- inherits: `UObject`
- L20 _public prototype_ `static ULevelSnapshotsEditorSettings* Get();`
- L21 _public prototype_ `ULevelSnapshotsEditorSettings();`
- L23 _public prototype_ `FVector2D GetLastCreationWindowSize() const;`
- L25 _public prototype_ `void SetLastCreationWindowSize(const FVector2D InLastSize);` — Setting the Window Size through code will not save the size to the config. To make sure it's saved, call SaveConfig().
- L28 _public prototype_ `void SanitizeAllProjectSettingsPaths(const bool bSkipForwardSlash);` — Removes forbidden file path characters (e.g. /?:&\*"<>|%#@^. ) from project settings path strings. Optionally the forward slash can be kept so that the user can define a file structure.
- L30 _public prototype_ `static void SanitizePathInline(FString& InPath, const bool bSkipForwardSlash);` — Removes forbidden file path characters (e.g. /?:&\*"<>|%#@^ )
- L33 _public prototype_ `static FText ParseLevelSnapshotsTokensInText(const FText& InTextToParse, const FString& InWorldName);` — `UFUNCTION(BlueprintCallable, Category = "Level Snapshots")`
- L36 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L41 _public member_ `FDirectoryPath RootLevelSnapshotSaveDir { TEXT("/Game` — `UPROPERTY(config, EditAnywhere, Category = "Data", meta = (ContentDir))` — The base directory in which all snapshots will be saved. LevelSnapshotSaveDir specifies in which subdirectory snapshots are saved.
- L53 _public member_ `FString LevelSnapshotSaveDir = TEXT("{ma` — `UPROPERTY(config, EditAnywhere, Category = "Data")` — The format to use for the resulting filename. Extension will be added automatically. Any tokens of the form {token} will be replaced with the corresponding value: {map}		- The name of the captured map or level {user}		- The current OS user account name {year}       - The current year {month}      - The current month {day}        - The current day {date}       - The current date from the local computer in the format of {year}-{month}-{day} {time}       - The current time from the local computer in the format of hours-minutes-seconds
- L65 _public member_ `FString DefaultLevelSnapshotName = TEXT("{ma` — `UPROPERTY(config, EditAnywhere, Category = "Data")` — The format to use for the resulting filename. Extension will be added automatically. Any tokens of the form {token} will be replaced with the corresponding value: {map}		- The name of the captured map or level {user}		- The current OS user account name {year}       - The current year {month}      - The current month {day}        - The current day {date}       - The current date from the local computer in the format of {year}-{month}-{day} {time}       - The current time from the local computer in the format of hours-minutes-seconds
- L68 _public member_ `bool bEnableLevelSnapshotsToolbarButton = true;` — `UPROPERTY(config, EditAnywhere, Category = "Editor", meta = (ConfigRestartRequired = true))`
- L71 _public member_ `bool bUseCreationForm = true;` — `UPROPERTY(config, EditAnywhere, Category = "Editor")`
- L75 _public member_ `bool bClickActorGroupToSelectActorInScene;` — `UPROPERTY(config, EditAnywhere, Category = "Editor")` — If true, clicking on an actor group under 'Modified Actors' will select the actor in the scene. The previous selection will be deselected.
- L78 _public member_ `float PreferredCreationFormWindowWidth;` — `UPROPERTY(config, EditAnywhere, Category = "Editor")`
- L81 _public member_ `float PreferredCreationFormWindowHeight;` — `UPROPERTY(config, EditAnywhere, Category = "Editor")`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshotsEditor/Private/LevelSnapshotsEditorStyle.h` (Private)


#### class `FLevelSnapshotsEditorStyle`  
`class FLevelSnapshotsEditorStyle`  
_L8-37_
- L12 _public prototype_ `static void Initialize();`
- L14 _public prototype_ `static void Shutdown();`
- L16 _public prototype_ `static void ReloadTextures();`
- L18 _public prototype_ `static const ISlateStyle& Get();`
- L20 _public prototype_ `static FName GetStyleSetName();`
- L22 _public prototype_ `static const FLinearColor& GetColor(FName PropertyName, const ANSICHAR* Specifier = nullptr);`
- L24 _public prototype_ `static const FSlateBrush* GetBrush(FName PropertyName, const ANSICHAR* Specifier = nullptr);`
- L27 _public function_ `template< typename WidgetStyleType > static const WidgetStyleType& GetWidgetStyle(FName PropertyName, const ANSICHAR* Specifier = nullptr)`
- L33 _private prototype_ `static TSharedRef<FSlateStyleSet> Create();`
- L36 _private member_ `static TSharedPtr<FSlateStyleSet> StyleInstance;`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshotsEditor/Private/Misc/LevelSnapshotsEditorCustomWidgetGenerator.h` (Private)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace LevelSnapshotsEditorCustomWidgetGenerator`
- L15 _variable_ `const TArray<FName> IgnoredClassNames = { "PostProcessVolume" };` (scope `LevelSnapshotsEditorCustomWidgetGenerator`)
- L21 _prototype_ `void CreateRowsForPropertiesNotHandledByPropertyRowGenerator( TFieldPath<FProperty> InFieldPath, TObjectPtr<UObject> InSnapshotObject, TObjectPtr<UObject> InWorldObject, const TWeakPtr<SLevelSnapshotsEditorResults>& InResultsView, const TWeakPtr<FLevelSnapshotsEditorResultsRow>& InDirectParentRow);` (scope `LevelSnapshotsEditorCustomWidgetGenerator`) — When properties do not have widgets generated by the PRG we need to create widgets for them on a case-by-case basis.
- L28 _prototype_ `void* GetPropertyValueFromProperty(const FProperty* InProperty, const TObjectPtr<UObject> InObject);` (scope `LevelSnapshotsEditorCustomWidgetGenerator`)
- L31 _prototype_ `TSharedPtr<SWidget> GenerateGenericPropertyWidget( const FProperty* InProperty, const void* InPropertyValue, const TObjectPtr<UObject> InObject, const TFunction<FString(const FString&, const UObject*)> InWidgetTextEditLambda = nullptr);` (scope `LevelSnapshotsEditorCustomWidgetGenerator`) — Used for properties which are not specifically handled in another method. Returns an STextBlock widget with the value exported to text.
- L35 _prototype_ `TSharedPtr<SWidget> GenerateObjectPropertyWidget( const TObjectPtr<UObject> InObject, const TFunction<FString(const FString&, const UObject*)> InWidgetTextEditLambda = nullptr);` (scope `LevelSnapshotsEditorCustomWidgetGenerator`)
- L38 _prototype_ `TSharedPtr<SWidget> DeterminePropertyTypeAndReturnWidget(const FProperty* InProperty, const void* InPropertyValue, const TObjectPtr<UObject> InObject);` (scope `LevelSnapshotsEditorCustomWidgetGenerator`)
- L40 _prototype_ `TSharedRef<SWidget> MakeComboBoxWithSelection(const FString& InString, const FText& InToolTipText);` (scope `LevelSnapshotsEditorCustomWidgetGenerator`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshotsEditor/Private/Util/TakeSnapshotUtil.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace SnapshotEditor`
- L17 _prototype_ `UWorld* GetWorld(bool bIgnorePIE);` (scope `SnapshotEditor`) — Get the world to use for taking a level snapshot. @param bIgnorePIE  if true and we are in a PIE world, we ignore the PIE world and use the editor world context. @return The current UWorld.
- L22 _prototype_ `void TakeSnapshotWithOptionalForm();` (scope `SnapshotEditor`) — Shows the window for taking snapshots, if enabled by the user settings. Otherwise just takes a snapshot.
- L32 _prototype_ `ULevelSnapshot* TakeLevelSnapshotAndSaveToDisk(UWorld* World, const FString& FileName, const FString& FolderPath, const FString& Description, bool bShouldCreateUniqueFileName = true, bool bSaveAsync = false);` (scope `SnapshotEditor`) — @param World The world to take snapshot in @param FileName Name of saved snapshot asset @param FolderPath Where to save the asset @param Description The value of the description field of the snapshot @param bShouldCreateUniqueFileName Whether to use FileName as base to generate a unique file name @param bSaveAsync Whether to save the asset async. Saving sync will block user and this can take several minutes.
- L37 _prototype_ `void GenerateThumbnailForSnapshotAsset(ULevelSnapshot* Snapshot);` (scope `SnapshotEditor`) — Captures a screenshot from the editor camera and assigns it to the snapshot.

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshotsEditor/Private/Views/Filter/SLevelSnapshotsEditorFilters.h` (Private)


#### class `SLevelSnapshotsEditorFilters`  
`class SLevelSnapshotsEditorFilters : public SCompoundWidget`  
_L23-64_
- inherits: `SCompoundWidget`
- desc: Contents of filters tab
- L27 _public prototype_ `~SLevelSnapshotsEditorFilters();`
- L29 _public function_ `SLATE_BEGIN_ARGS(SLevelSnapshotsEditorFilters)`
- L31 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, ULevelSnapshotsEditorData* EditorData);`
- L35 _public prototype_ `ULevelSnapshotsEditorData* GetEditorData() const;`
- L36 _public prototype_ `const TSharedPtr<IDetailsView>& GetFilterDetailsView() const;`
- L37 _public prototype_ `bool IsResizingDetailsView() const;`
- L39 _public prototype_ `void RemoveFilter(UConjunctionFilter* FilterToRemove);`
- L43 _private prototype_ `void OnFilterModified(EFilterChangeType FilterChangeType);`
- L44 _private prototype_ `FReply OnClickUpdateResultsView();`
- L47 _private prototype_ `void RefreshGroups();` — Generate the groups using the preset's layout data.
- L49 _private prototype_ `FReply AddFilterClick();`
- L51 _private member_ `FDelegateHandle OnUserDefinedFiltersChangedHandle;`
- L52 _private member_ `FDelegateHandle OnEditedFilterChangedHandle;`
- L53 _private member_ `FDelegateHandle OnFilterModifiedHandle;`
- L55 _private member_ `TSharedPtr<SFavoriteFilterList> FavoriteList;`
- L56 _private member_ `TSharedPtr<SVerticalBox> FilterRowsList;`
- L59 _private member_ `TSharedPtr<IDetailsView> FilterDetailsView;` — Filter input details view
- L61 _private member_ `TSharedPtr<SCustomSplitter> DetailsSplitter;` — Splits filters and details panel
- L63 _private member_ `TWeakObjectPtr<ULevelSnapshotsEditorData> EditorDataPtr;`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshotsEditor/Private/Views/Input/SLevelSnapshotsEditorContextPicker.h` (Private)


#### class `SLevelSnapshotsEditorContextPicker`  
`class SLevelSnapshotsEditorContextPicker : public SCompoundWidget`  
_L18-64_
- inherits: `SCompoundWidget`
- L22 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnSelectWorldContext, FSoftObjectPath);`
- L24 _public prototype_ `~SLevelSnapshotsEditorContextPicker();`
- L26 _public function_ `SLATE_BEGIN_ARGS(SLevelSnapshotsEditorContextPicker)`
- L28 _public prototype_ `SLATE_ATTRIBUTE(FSoftObjectPath, SelectedWorldPath) SLATE_EVENT(FOnSelectWorldContext, OnSelectWorldContext) SLATE_END_ARGS() void Construct(const FArguments& InArgs, ULevelSnapshotsEditorData* InEditorData);` — Attribute for retrieving the current context
- L35 _public prototype_ `UWorld* GetSelectedWorld() const;`
- L36 _public prototype_ `FSoftObjectPath GetSelectedWorldSoftPath() const;`
- L40 _private prototype_ `static FText GetWorldDescription(const UWorld* World);`
- L42 _private prototype_ `TSharedRef<SWidget> BuildWorldPickerMenu();`
- L43 _private prototype_ `void RegisterWorldPickerWithEditorDataClass();`
- L46 _private prototype_ `FText GetWorldPickerMenuButtonText(const FSoftObjectPath& AssetPath, const FName& AssetName) const;`
- L47 _private prototype_ `FText GetCurrentContextText() const;`
- L48 _private prototype_ `const FSlateBrush* GetBorderBrush(FSoftObjectPath WorldPath) const;`
- L50 _private prototype_ `void OnSetWorldContextSelection(const FAssetData Asset);`
- L51 _private prototype_ `void SetSelectedWorld(const FSoftObjectPath& SelectedWorld);`
- L53 _private prototype_ `bool ShouldRadioButtonBeChecked(const FSoftObjectPath InWorldSoftPath) const;`
- L55 _private member_ `FOnSelectWorldContext OnSelectWorldContextEvent;`
- L57 _private member_ `TSharedPtr<STextBlock> PickerButtonTextBlock;`
- L58 _private member_ `TWeakObjectPtr<ULevelSnapshotsEditorData> DataPtr;`
- L61 _private member_ `FSoftObjectPath SelectedWorldPath;` — The selected radio button's world ref's soft path (for comparison)
- L63 _private member_ `FDelegateHandle OnMapOpenedDelegateHandle;`

#### Free symbols / members of external scopes

- L22 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSelectWorldContext, FSoftObjectPath);`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshotsEditor/Private/Views/Input/SLevelSnapshotsEditorInput.h` (Private)


#### class `SLevelSnapshotsEditorInput`  
`class SLevelSnapshotsEditorInput : public SCompoundWidget`  
_L17-43_
- inherits: `SCompoundWidget`
- L21 _public prototype_ `~SLevelSnapshotsEditorInput();`
- L23 _public function_ `SLATE_BEGIN_ARGS(SLevelSnapshotsEditorInput)`
- L26 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, ULevelSnapshotsEditorData* InEditorData);`
- L30 _public prototype_ `void OpenLevelSnapshotsDialogWithAssetSelected(const FAssetData& InAssetData) const;`
- L34 _private prototype_ `void OverrideWorld(FSoftObjectPath InNewContextPath);`
- L36 _private member_ `FDelegateHandle OnMapOpenedDelegateHandle;`
- L37 _private member_ `TWeakObjectPtr<ULevelSnapshotsEditorData> EditorData;`
- L39 _private member_ `TSharedPtr<SVerticalBox> EditorInputOuterVerticalBox;`
- L40 _private member_ `TSharedPtr<SLevelSnapshotsEditorContextPicker> EditorContextPickerPtr;`
- L41 _private member_ `TSharedPtr<SLevelSnapshotsEditorBrowser> EditorBrowserWidgetPtr;`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshotsEditor/Private/Views/Results/LevelSnapshotsEditorResultsHelpers.h` (Private)


#### struct `FComponentHierarchy`  
`struct FComponentHierarchy`  
_L7-14_
- L9 _public function_ `FComponentHierarchy(USceneComponent* InComponent) : Component(InComponent)`
- L12 _public member_ `const TWeakObjectPtr<USceneComponent> Component;`
- L13 _public member_ `TArray<TSharedRef<FComponentHierarchy>> DirectChildren;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace FLevelSnapshotsEditorResultsHelpers`
- L18 _prototype_ `TArray<TFieldPath<FProperty>> LoopOverProperties( const TWeakPtr<FRowGeneratorInfo>& InSnapshotRowGeneratorInfo, const TWeakPtr<FRowGeneratorInfo>& InWorldRowGeneratorInfo, const TWeakPtr<FLevelSnapshotsEditorResultsRow>& InDirectParentRow, FPropertySelectionMap& PropertySelectionMap, const TArray<TFieldPath<FProperty>>& PropertiesThatPassFilter, const TWeakPtr<SLevelSnapshotsEditorResults>& InResultsView);` (scope `FLevelSnapshotsEditorResultsHelpers`)
- L24 _prototype_ `void LoopOverHandleHierarchiesAndCreateRowHierarchy(ELevelSnapshotsObjectType InputType, const TWeakPtr<FPropertyHandleHierarchy>& InputHierarchy, const TWeakPtr<FLevelSnapshotsEditorResultsRow>& InDirectParentRow, FPropertySelectionMap& PropertySelectionMap, const TArray<TFieldPath<FProperty>>& PropertiesThatPassFilter, TArray<TFieldPath<FProperty>>& PropertyRowsGenerated, const TWeakPtr<SLevelSnapshotsEditorResults>& InResultsView, const TWeakPtr<FPropertyHandleHierarchy>& InHierarchyToSearchForCounterparts = nullptr);` (scope `FLevelSnapshotsEditorResultsHelpers`) — Do not pass in the base hierarchy, only children of the base hierarchy.
- L30 _prototype_ `TWeakPtr<FPropertyHandleHierarchy> FindCorrespondingHandle( const FLevelSnapshotPropertyChain& InPropertyChain, const FText& InDisplayName, const TWeakPtr<FPropertyHandleHierarchy>& HierarchyToSearch, bool& bFoundMatch);` (scope `FLevelSnapshotsEditorResultsHelpers`) — Finds a hierarchy entry recursively
- L34 _prototype_ `void CreatePropertyHandleHierarchyChildrenRecursively( const TSharedRef<IDetailTreeNode>& InNode, const TWeakPtr<FPropertyHandleHierarchy>& InParentHierarchy, const TWeakObjectPtr<UObject> InContainingObject);` (scope `FLevelSnapshotsEditorResultsHelpers`) — A helper function called by BuildPropertyHandleHierarchy
- L38 _prototype_ `TSharedPtr<FPropertyHandleHierarchy> BuildPropertyHandleHierarchy(const TWeakPtr<FRowGeneratorInfo>& InRowGenerator);` (scope `FLevelSnapshotsEditorResultsHelpers`) — Creates a node tree of all property handles created by PRG. The first node is a dummy node to contain all children.
- L40 _prototype_ `UObject* FindCounterpartComponent(const UActorComponent* SubObjectToMatch, const TSet<UActorComponent*>& InCounterpartSubObjects);` (scope `FLevelSnapshotsEditorResultsHelpers`)
- L49 _prototype_ `bool IsInstancedActorComponentDesirableForComponentArray( UActorComponent* ActorComponent, const bool bHideConstructionScriptComponentsInDetailsView = true);` (scope `FLevelSnapshotsEditorResultsHelpers`) — Determines whether the specified ActorComponent is an instanced actor component and whether or not it is desirable for the Level Snapshots process based on its creation method, this function's parameters and editor settings. @param ActorComponent The ActorComponent to check. @param bHideConstructionScriptComponentsInDetailsView Whether to hide construction script components in the details view. Default is true. @return true if the ActorComponent should be added to a given Level Snapshots component array, false otherwise.
- L57 _prototype_ `TSet<UActorComponent*> FilterOutActorComponentsBasedOnEditorSettings(const TSet<UActorComponent*>& UnfilteredActorComponentList);` (scope `FLevelSnapshotsEditorResultsHelpers`) — Filters out invalid and instanced actor components based on editor settings. @param UnfilteredActorComponentList The unfiltered list of actor components. @return The filtered set of actor components.
- L64 _prototype_ `TSet<UActorComponent*> FilterOutActorComponentsBasedOnEditorSettings(const TSet<TWeakObjectPtr<UActorComponent>>& UnfilteredActorComponentList);` (scope `FLevelSnapshotsEditorResultsHelpers`) — Filters out invalid and instanced actor components based on editor settings. @param UnfilteredActorComponentList The unfiltered list of actor components. @return The filtered set of actor components.
- L66 _prototype_ `int32 CreateNewHierarchyStructInLoop(const AActor* InActor, USceneComponent* SceneComponent, TArray<TWeakPtr<FComponentHierarchy>>& AllHierarchies);` (scope `FLevelSnapshotsEditorResultsHelpers`)
- L69 _prototype_ `TSharedRef<FComponentHierarchy> BuildComponentHierarchy(const AActor* InActor, TSet<UActorComponent*>& OutNonSceneComponents);` (scope `FLevelSnapshotsEditorResultsHelpers`) — Creates a node tree of all scene components in an actor. Only scene components can have children. Non-scene actor components do not
- L71 _prototype_ `void BuildNestedSceneComponentRowsRecursively(const TWeakPtr<FComponentHierarchy>& InHierarchy, const TSet<UActorComponent*>& InCounterpartComponents, FPropertyEditorModule& PropertyEditorModule, FPropertySelectionMap& PropertySelectionMap, const TWeakPtr<FLevelSnapshotsEditorResultsRow>& InDirectParentRow, const TWeakPtr<SLevelSnapshotsEditorResults>& InResultsView);` (scope `FLevelSnapshotsEditorResultsHelpers`)
- L76 _prototype_ `TWeakPtr<FLevelSnapshotsEditorResultsRow> BuildModifiedObjectRow(UObject* InWorldObject, UObject* InSnapshotObject, FPropertyEditorModule& PropertyEditorModule, FPropertySelectionMap& PropertySelectionMap, const TArray<TFieldPath<FProperty>>& PropertiesThatPassFilter, const TWeakPtr<FLevelSnapshotsEditorResultsRow>& InDirectParentRow, const TWeakPtr<SLevelSnapshotsEditorResults>& InResultsView, const FText& InDisplayNameOverride = FText::GetEmpty(), TWeakPtr<FRowGeneratorInfo> WorldRowGeneratorInfoOverride = nullptr, TWeakPtr<FRowGeneratorInfo> SnapshotRowGeneratorInfoOverride = nullptr);` (scope `FLevelSnapshotsEditorResultsHelpers`) — ForSubobjects and components with a known pairing. If RowGeneratorInfo pointers are not specified, ones will be created using the input objects.
- L82 _prototype_ `TWeakPtr<FLevelSnapshotsEditorResultsRow> BuildObjectRowForAddedObjectsToRemove( UObject* InAddedObject, const TSharedRef<FLevelSnapshotsEditorResultsRow> InDirectParentRow, const TSharedRef<SLevelSnapshotsEditorResults> InResultsView);` (scope `FLevelSnapshotsEditorResultsHelpers`)
- L85 _prototype_ `TWeakPtr<FLevelSnapshotsEditorResultsRow> BuildObjectRowForRemovedObjectsToAdd( UObject* InRemovedObject, const TSharedRef<FLevelSnapshotsEditorResultsRow> InDirectParentRow, const TSharedRef<SLevelSnapshotsEditorResults> InResultsView);` (scope `FLevelSnapshotsEditorResultsHelpers`)
- L89 _prototype_ `TWeakPtr<FLevelSnapshotsEditorResultsRow> FindComponentCounterpartAndBuildRow(UActorComponent* InWorldObject, const TSet<UActorComponent*>& InCounterpartObjects, FPropertyEditorModule& PropertyEditorModule, FPropertySelectionMap& PropertySelectionMap, const TArray<TFieldPath<FProperty>>& PropertiesThatPassFilter, const TWeakPtr<FLevelSnapshotsEditorResultsRow>& InDirectParentRow, const TWeakPtr<SLevelSnapshotsEditorResults>& InResultsView);` (scope `FLevelSnapshotsEditorResultsHelpers`) — For components without a known pairing

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshotsEditor/Private/Views/Results/LevelSnapshotsEditorResultsRow.h` (Private)


#### enum `ELevelSnapshotsObjectType`  
`enum ELevelSnapshotsObjectType : uint8`  
_L17-22_
- L19 _public enumerator_ `ObjectType_None`
- L20 _public enumerator_ `ObjectType_Snapshot`
- L21 _public enumerator_ `ObjectType_World`

#### struct `FLevelSnapshotsEditorResultsSplitterManager`  
`struct FLevelSnapshotsEditorResultsSplitterManager`  
_L24-28_
- L26 _public member_ `float NestedColumnWidth = 0.5f;` — The right side of the first splitter which contains the nested splitter for the property widgets
- L27 _public member_ `float SnapshotPropertyColumnWidth = 0.5f;`

#### struct `FLevelSnapshotsEditorResultsRowStateMemory`  
`struct FLevelSnapshotsEditorResultsRowStateMemory`  
_L30-47_
- L32 _public function_ `FLevelSnapshotsEditorResultsRowStateMemory()`
- L38 _public function_ `FLevelSnapshotsEditorResultsRowStateMemory(const FString& InPathToRow, const bool bNewIsExpanded, const ECheckBoxState NewWidgetCheckedState) : PathToRow(InPathToRow) , bIsExpanded(bNewIsExpanded) , WidgetCheckedState(NewWidgetCheckedState)`
- L44 _public member_ `FString PathToRow;`
- L45 _public member_ `bool bIsExpanded;`
- L46 _public member_ `ECheckBoxState WidgetCheckedState;`

#### struct `FRowGeneratorInfo`  
`struct FRowGeneratorInfo`  
_L49-74_
- L51 _public function_ `~FRowGeneratorInfo()`
- L56 _public function_ `FRowGeneratorInfo( const TWeakPtr<FLevelSnapshotsEditorResultsRow>& InBoundObject, const ELevelSnapshotsObjectType InGeneratorType, const TSharedRef<IPropertyRowGenerator>& InGeneratorObject) : BoundObject(InBoundObject) , GeneratorType(InGeneratorType) , GeneratorObject(InGeneratorObject)`
- L63 _public prototype_ `TWeakPtr<IPropertyRowGenerator> GetGeneratorObject() const;`
- L65 _public prototype_ `void FlushReferences();`
- L69 _private member_ `TWeakPtr<FLevelSnapshotsEditorResultsRow> BoundObject;` — The object that represents the object passed into the generator
- L71 _private member_ `ELevelSnapshotsObjectType GeneratorType = ObjectType_None;` — Whether this generator represents the snapshot or world object
- L73 _private member_ `TSharedPtr<IPropertyRowGenerator> GeneratorObject;` — The actual generator ptr

#### struct `FPropertyHandleHierarchy`  
`struct FPropertyHandleHierarchy`  
_L76-94_
- L78 _public prototype_ `FPropertyHandleHierarchy(const TSharedPtr<IDetailTreeNode>& InNode, const TSharedPtr<IPropertyHandle>& InHandle, const TWeakObjectPtr<UObject> InContainingObject);`
- L80 _public member_ `TSharedPtr<IDetailTreeNode> Node;`
- L81 _public member_ `TSharedPtr<IPropertyHandle> Handle;`
- L82 _public member_ `TArray<TSharedRef<FPropertyHandleHierarchy>> DirectChildren;`
- L84 _public member_ `TWeakObjectPtr<UObject> ContainingObject;`
- L85 _public member_ `TOptional<FLevelSnapshotPropertyChain> PropertyChain;`
- L88 _public member_ `FText DisplayName;` — Used as a fallback for identifying counterparts for collection members
- L90 _public function_ `bool IsValidHierarchy() const`

#### struct `FLevelSnapshotsEditorResultsRow`  
`struct FLevelSnapshotsEditorResultsRow final : TSharedFromThis<FLevelSnapshotsEditorResultsRow>`  
_L96-347_
- inherits: `TSharedFromThis<FLevelSnapshotsEditorResultsRow>`
- L127 _public prototype_ `~FLevelSnapshotsEditorResultsRow();`
- L129 _public prototype_ `void FlushReferences();`
- L131 _public prototype_ `FLevelSnapshotsEditorResultsRow( const FText InDisplayName, const ELevelSnapshotsEditorResultsRowType InRowType, const ECheckBoxState StartingWidgetCheckboxState, const TWeakPtr<SLevelSnapshotsEditorResults>& InResultsView, const TWeakPtr<FLevelSnapshotsEditorResultsRow>& InDirectParentRow = nullptr );`
- L139 _public prototype_ `void InitHeaderRow( const ELevelSnapshotsEditorResultsTreeViewHeaderType InHeaderType, const TArray<FText>& InColumns);`
- L142 _public prototype_ `void InitAddedActorRow(AActor* InAddedActor);`
- L143 _public prototype_ `void InitRemovedActorRow(const FSoftObjectPath& InRemovedActorPath);`
- L145 _public prototype_ `void InitAddedObjectRow(UObject* InAddedObjectToRemove);`
- L146 _public prototype_ `void InitRemovedObjectRow(UObject* InRemovedObjectToAdd);`
- L148 _public prototype_ `void InitActorRow(AActor* InSnapshotActor, AActor* InWorldActor);`
- L149 _public prototype_ `void InitObjectRow( UObject* InSnapshotObject, UObject* InWorldObject, const TWeakPtr<FRowGeneratorInfo>& InSnapshotRowGenerator, const TWeakPtr<FRowGeneratorInfo>& InWorldRowGenerator);`
- L154 _public prototype_ `void InitPropertyRow( const TWeakPtr<FLevelSnapshotsEditorResultsRow>& InContainingObjectGroup, const TSharedPtr<FPropertyHandleHierarchy>& InSnapshotHierarchy, const TSharedPtr<FPropertyHandleHierarchy>& InWorldHandleHierarchy, const bool bNewIsCounterpartValueSame);`
- L159 _public prototype_ `void InitPropertyRowWithCustomWidget( const TWeakPtr<FLevelSnapshotsEditorResultsRow>& InContainingObjectGroup, FProperty* InProperty, const TSharedPtr<SWidget> InSnapshotCustomWidget, const TSharedPtr<SWidget> InWorldCustomWidget);`
- L163 _public prototype_ `void ApplyRowStateMemoryIfAvailable();`
- L164 _public prototype_ `const FString& GetOrGenerateRowPath();`
- L166 _public prototype_ `void GenerateModifiedActorGroupChildren(FPropertySelectionMap& PropertySelectionMap);`
- L168 _public prototype_ `bool DoesRowRepresentGroup() const;`
- L169 _public prototype_ `bool DoesRowRepresentObject() const;`
- L171 _public prototype_ `ELevelSnapshotsEditorResultsRowType GetRowType() const;`
- L175 _public prototype_ `static ELevelSnapshotsEditorResultsRowType DetermineRowTypeFromProperty( FProperty* InProperty, const bool bIsCustomized, const bool bHasChildProperties);` — Returns the ELevelSnapshotsEditorResultsRowType of a given property. Will never return ActorGroup, SubobjectGroup or TreeViewHeader. Returns None on error.
- L178 _public prototype_ `const TArray<FText>& GetHeaderColumns() const;`
- L180 _public prototype_ `FText GetDisplayName() const;`
- L181 _public function_ `FText GetTooltip() const`
- L183 _public prototype_ `const FSlateBrush* GetIconBrush() const;`
- L186 _public prototype_ `const TArray<FLevelSnapshotsEditorResultsRowPtr>& GetChildRows() const;` — bHasGeneratedChildren must be true to get actual children.
- L187 _public prototype_ `void AddToChildRows(const FLevelSnapshotsEditorResultsRowPtr& InRow);`
- L188 _public prototype_ `void InsertChildRowAtIndex(const FLevelSnapshotsEditorResultsRowPtr& InRow, const int32 AtIndex = 0);`
- L190 _public prototype_ `bool GetIsTreeViewItemExpanded() const;`
- L191 _public prototype_ `void SetIsTreeViewItemExpanded(const bool bNewExpanded);`
- L193 _public prototype_ `bool GetShouldExpandAllChildren() const;`
- L194 _public prototype_ `void SetShouldExpandAllChildren(const bool bNewShouldExpandAllChildren);`
- L196 _public prototype_ `uint8 GetChildDepth() const;`
- L197 _public prototype_ `void SetChildDepth(const uint8 InDepth);`
- L199 _public prototype_ `TWeakPtr<FLevelSnapshotsEditorResultsRow> GetDirectParentRow() const;`
- L200 _public prototype_ `void SetDirectParentRow(const TWeakPtr<FLevelSnapshotsEditorResultsRow>& InDirectParentRow);`
- L203 _public prototype_ `TWeakPtr<FLevelSnapshotsEditorResultsRow> GetParentRowAtTopOfHierarchy();` — Walks up each direct parent's direct parents until it reaches the first FLevelSnapshotsEditorResultsRow without a direct parent, then returns it.
- L205 _public prototype_ `TWeakPtr<FLevelSnapshotsEditorResultsRow> GetContainingObjectGroup() const;`
- L207 _public prototype_ `bool GetHasGeneratedChildren() const;`
- L208 _public prototype_ `void SetHasGeneratedChildren(const bool bNewGenerated);`
- L211 _public prototype_ `bool MatchSearchTokensToSearchTerms(const TArray<FString> InTokens, const bool bMatchAnyTokens = false);` — If bMatchAnyTokens is false, only nodes that match all terms will be returned.
- L214 _public prototype_ `void ExecuteSearchOnChildNodes(const FString& SearchString) const;` — This overload creates tokens from a string first, then calls ExecuteSearchOnChildNodes(const TArray<FString>& Tokens).
- L215 _public prototype_ `void ExecuteSearchOnChildNodes(const TArray<FString>& Tokens) const;`
- L217 _public prototype_ `void SetCachedSearchTerms(const FString& InTerms);`
- L219 _public prototype_ `UObject* GetSnapshotObject() const;`
- L220 _public prototype_ `UObject* GetWorldObject() const;`
- L222 _public prototype_ `UObject* GetFirstValidObject(ELevelSnapshotsObjectType& ReturnedType) const;`
- L224 _public prototype_ `FSoftObjectPath GetObjectPath() const;`
- L226 _public prototype_ `FProperty* GetProperty() const;`
- L227 _public prototype_ `FLevelSnapshotPropertyChain GetPropertyChain() const;`
- L229 _public prototype_ `TSharedPtr<IDetailTreeNode> GetSnapshotPropertyNode() const;`
- L230 _public prototype_ `TSharedPtr<IDetailTreeNode> GetWorldPropertyNode() const;`
- L231 _public prototype_ `ELevelSnapshotsObjectType GetFirstValidPropertyNode(TSharedPtr<IDetailTreeNode>& OutNode) const;`
- L233 _public prototype_ `TSharedPtr<IPropertyHandle> GetSnapshotPropertyHandle() const;`
- L234 _public prototype_ `TSharedPtr<IPropertyHandle> GetWorldPropertyHandle() const;`
- L235 _public prototype_ `ELevelSnapshotsObjectType GetFirstValidPropertyHandle(TSharedPtr<IPropertyHandle>& OutHandle) const;`
- L237 _public prototype_ `TSharedPtr<SWidget> GetSnapshotPropertyCustomWidget() const;`
- L238 _public prototype_ `TSharedPtr<SWidget> GetWorldPropertyCustomWidget() const;`
- L241 _public prototype_ `bool HasCustomWidget(ELevelSnapshotsObjectType InQueryType) const;` — Returns true if a specified type of custom widget is valid for its row. Use ObjectType_None to return true only if both snapshot and world custom widgets are valid.
- L243 _public prototype_ `bool GetIsCounterpartValueSame() const;`
- L244 _public prototype_ `void SetIsCounterpartValueSame(const bool bIsValueSame);`
- L246 _public prototype_ `ECheckBoxState GetWidgetCheckedState() const;`
- L247 _public prototype_ `void SetWidgetCheckedState(const ECheckBoxState NewState, const bool bShouldUpdateHierarchyCheckedStates = false);`
- L249 _public prototype_ `ECheckBoxState GenerateChildWidgetCheckedStateBasedOnParent() const;`
- L251 _public prototype_ `bool GetIsNodeChecked() const;`
- L252 _public prototype_ `void SetIsNodeChecked(const bool bNewChecked, const bool bShouldUpdateHierarchyCheckedStates = false);`
- L256 _public prototype_ `bool HasVisibleChildren() const;`
- L258 _public prototype_ `bool HasCheckedChildren()const;`
- L259 _public prototype_ `bool HasUncheckedChildren() const;`
- L262 _public prototype_ `bool HasChangedChildren() const;` — Whether the group has any children with associated properties that have any difference between the chosen snapshot and the current level.
- L264 _public prototype_ `void GetAllCheckedChildProperties(TArray<FLevelSnapshotsEditorResultsRowPtr>& CheckedSinglePropertyNodeArray) const;`
- L265 _public prototype_ `void GetAllUncheckedChildProperties(TArray<FLevelSnapshotsEditorResultsRowPtr>& UncheckedSinglePropertyNodeArray) const;`
- L267 _public prototype_ `bool GetShouldCheckboxBeHidden() const;`
- L268 _public prototype_ `void SetShouldCheckboxBeHidden(const bool bNewShouldCheckboxBeHidden);`
- L270 _public prototype_ `EVisibility GetDesiredVisibility() const;`
- L275 _private member_ `ELevelSnapshotsEditorResultsRowType RowType = SingleProperty;` — Generic properties
- L276 _private member_ `FText DisplayName;`
- L277 _private member_ `FText Tooltip;`
- L278 _private member_ `TArray<FLevelSnapshotsEditorResultsRowPtr> ChildRows;`
- L279 _private member_ `bool bIsTreeViewItemExpanded = false;`
- L282 _private member_ `bool bShouldExpandAllChildren = false;` — Used to epand all children on shift+click.
- L285 _private member_ `ELevelSnapshotsEditorResultsTreeViewHeaderType HeaderType = HeaderType_None;` — For Header Rows
- L286 _private member_ `TArray<FText> HeaderColumns;`
- L289 _private member_ `uint8 ChildDepth = 0;` — Number of parents in row's ancestor chain
- L290 _private member_ `TWeakPtr<FLevelSnapshotsEditorResultsRow> DirectParentRow = nullptr;`
- L293 _private member_ `TWeakPtr<FLevelSnapshotsEditorResultsRow> ContainingObjectGroup = nullptr;` — This is the component, subobject or actor group to which this row belongs. If nullptr, this row is a top-level actor group.
- L296 _private member_ `bool bHasGeneratedChildren = false;` — Only applies to object groups - all of the property groups are generated with the rest of the single properties
- L299 _private member_ `FString CachedSearchTerms;` — When we generate Search Terms for a node, it's saved here so it does not need to be generated again until filters are changed
- L300 _private member_ `bool bDoesRowMatchSearchTerms = true;`
- L303 _private member_ `FString RowPath;` — This is a breadcrumb trail of display names used to find or store the state of the row.
- L306 _private member_ `FSoftObjectPath RemovedActorPath;` — For removed actor type rows
- L310 _private member_ `TWeakObjectPtr<UObject> SnapshotObject;`
- L311 _private member_ `TWeakObjectPtr<UObject> WorldObject;`
- L312 _private member_ `TWeakPtr<SLevelSnapshotsEditorResults> ResultsViewPtr;`
- L314 _private member_ `TWeakPtr<FRowGeneratorInfo> SnapshotRowGeneratorInfo;`
- L315 _private member_ `TWeakPtr<FRowGeneratorInfo> WorldRowGeneratorInfo;`
- L319 _private member_ `TSharedPtr<FPropertyHandleHierarchy> SnapshotPropertyHandleHierarchy;`
- L320 _private member_ `TSharedPtr<FPropertyHandleHierarchy> WorldPropertyHandleHierarchy;`
- L322 _private member_ `FProperty* RepresentedProperty;`
- L324 _private member_ `TSharedPtr<SWidget> SnapshotPropertyCustomWidget;`
- L325 _private member_ `TSharedPtr<SWidget> WorldPropertyCustomWidget;`
- L328 _private member_ `bool bIsCounterpartValueSame = false;` — Whether the snapshot and world object properties have the same value
- L330 _private member_ `bool bShouldCheckboxBeHidden;`
- L333 _private member_ `ECheckBoxState WidgetCheckedState = ECheckBoxState::Checked;` — Checkbox in widget is bound to this property
- L336 _private prototype_ `const FString& GetOrCacheSearchTerms();` — Returns a string of searchable keywords such as object names, property names, paths or anything else associated with the row that might be useful to search for.
- L339 _private prototype_ `void SetDoesRowMatchSearchTerms(const bool bNewMatch);` — Use MatchSearchTerms() first to match Search Terms against tokens, then call this method
- L341 _private prototype_ `void EvaluateAndSetAllParentGroupCheckedStates() const;`
- L344 _private prototype_ `bool ShouldRowBeVisible() const;` — Evaluates all factors which should make a row visible or invisible but does not set visibility.
- L346 _private prototype_ `void InitTooltipWithObject(const FSoftObjectPath& RowObject);`

#### enum `FLevelSnapshotsEditorResultsRow::ELevelSnapshotsEditorResultsRowType`  
`enum ELevelSnapshotsEditorResultsRowType`  
_L98-117_
- L100 _public enumerator_ `None`
- L101 _public enumerator_ `TreeViewHeader` — Includes rows that represent headers grouping together added, removed, or modified actor rows
- L102 _public enumerator_ `AddedActorToRemove` — Includes rows that represent actors which have been created in the world since the snapshot was taken
- L103 _public enumerator_ `RemovedActorToAdd` — Includes rows that represent actors which have been deleted from the world since the snapshot was taken
- L104 _public enumerator_ `ModifiedActorGroup` — Modified Actor group. Use AddedActor or RemovedActor for other Actor row types.
- L105 _public enumerator_ `AddedComponentToRemove` — Includes rows that represent Components which have been created in the world since the snapshot was taken
- L106 _public enumerator_ `RemovedComponentToAdd` — Includes rows that represent Components which have been deleted from the world since the snapshot was taken
- L107 _public enumerator_ `ModifiedComponentGroup` — Includes rows that represent UActorComponent types
- L108 _public enumerator_ `SubObjectGroup` — Includes rows that represent separate non-component objects wholly owned by the world or snapshot actor
- L109 _public enumerator_ `StructGroup` — Rows that represent a single struct or a struct inside of a struct
- L110 _public enumerator_ `StructInMap` — Rows that represent a struct that's a value inside of a map
- L111 _public enumerator_ `StructInSetOrArray` — Rows that represent a struct inside a collection that isn't a map
- L112 _public enumerator_ `CollectionGroup` — Includes rows that represent TMap, TSet, and TArray.
- L113 _public enumerator_ `SingleProperty`
- L114 _public enumerator_ `SinglePropertyInStruct`
- L115 _public enumerator_ `SinglePropertyInMap`
- L116 _public enumerator_ `SinglePropertyInSetOrArray`

#### enum `FLevelSnapshotsEditorResultsRow::ELevelSnapshotsEditorResultsTreeViewHeaderType`  
`enum ELevelSnapshotsEditorResultsTreeViewHeaderType`  
_L119-125_
- L121 _public enumerator_ `HeaderType_None`
- L122 _public enumerator_ `HeaderType_ModifiedActors`
- L123 _public enumerator_ `HeaderType_AddedActors`
- L124 _public enumerator_ `HeaderType_RemovedActors`

#### Free symbols / members of external scopes

- L15 _typedef_ `typedef TSharedPtr<FLevelSnapshotsEditorResultsRow> FLevelSnapshotsEditorResultsRowPtr;`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshotsEditor/Private/Views/Results/SLevelSnapshotsEditorResults.h` (Private)


#### class `SLevelSnapshotsEditorResults`  
`class SLevelSnapshotsEditorResults final : public SCompoundWidget`  
_L26-155_
- inherits: `SCompoundWidget`
- L31 _public function_ `SLATE_BEGIN_ARGS(SLevelSnapshotsEditorResults)`
- L34 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, ULevelSnapshotsEditorData* InEditorData);`
- L40 _public prototype_ `FMenuBuilder BuildShowOptionsMenu();`
- L42 _public prototype_ `void SetShowFilteredRows(const bool bNewSetting);`
- L43 _public prototype_ `void SetShowUnselectedRows(const bool bNewSetting);`
- L45 _public prototype_ `bool GetShowFilteredRows() const;`
- L46 _public prototype_ `bool GetShowUnselectedRows() const;`
- L48 _public prototype_ `void FlushMemory(const bool bShouldKeepMemoryAllocated);`
- L50 _public prototype_ `TOptional<ULevelSnapshot*> GetSelectedLevelSnapshot() const;`
- L52 _public prototype_ `void OnSnapshotSelected(ULevelSnapshot* InLevelSnapshot);`
- L53 _public prototype_ `void RefreshResults(const bool bSnapshotHasChanged = false);`
- L54 _public prototype_ `FReply OnClickApplyToWorld();`
- L56 _public prototype_ `void UpdateSnapshotNameText(const TOptional<ULevelSnapshot*>& InLevelSnapshot) const;`
- L57 _public prototype_ `void UpdateSnapshotInformationText();`
- L59 _public prototype_ `void RefreshScroll() const;`
- L62 _public prototype_ `void BuildSelectionSetFromSelectedPropertiesInEachActorGroup();` — This method builds a selection set of all visible and checked properties to pass back to apply to the world.
- L64 _public prototype_ `FString GetSearchStringFromSearchInputField() const;`
- L65 _public prototype_ `void ExecuteResultsViewSearchOnAllActors(const FString& SearchString) const;`
- L66 _public prototype_ `void ExecuteResultsViewSearchOnSpecifiedActors(const FString& SearchString, const TArray<TSharedPtr<FLevelSnapshotsEditorResultsRow>>& ActorRowsToConsider) const;`
- L68 _public prototype_ `bool DoesTreeViewHaveVisibleChildren() const;`
- L70 _public prototype_ `void SetTreeViewItemExpanded(const TSharedPtr<FLevelSnapshotsEditorResultsRow>& RowToExpand, const bool bNewExpansion) const;`
- L72 _public prototype_ `ULevelSnapshotsEditorData* GetEditorDataPtr() const;`
- L76 _public prototype_ `static FPropertyRowGeneratorArgs GetLevelSnapshotsAppropriatePropertyRowGeneratorArgs();`
- L80 _public prototype_ `TWeakPtr<FRowGeneratorInfo> RegisterRowGenerator( const TWeakPtr<FLevelSnapshotsEditorResultsRow>& InBoundObject, const ELevelSnapshotsObjectType InGeneratorType, FPropertyEditorModule& PropertyEditorModule);` — This method should be used in place of the PropertyEditorModule's CreatePropertyRowGenerator because the returned generator is put into a struct managed by the Results View.
- L84 _public prototype_ `void CleanUpGenerators(const bool bShouldKeepMemoryAllocated);`
- L86 _public prototype_ `bool FindRowStateMemoryByPath(const FString& InPath, FLevelSnapshotsEditorResultsRowStateMemory& OutRowStateMemory);`
- L87 _public prototype_ `void AddRowStateToRowStateMemory(const TSharedPtr<FLevelSnapshotsEditorResultsRowStateMemory> InRowStateMemory);`
- L88 _public prototype_ `void GenerateRowStateMemoryRecursively();`
- L92 _private prototype_ `FLevelSnapshotsEditorResultsRowPtr& GetOrCreateDummyRow();`
- L95 _private member_ `TSharedPtr<STextBlock> SelectedSnapshotNamePtr;` — Header Slate Pointers
- L98 _private member_ `TSharedPtr<SVerticalBox> InfoTextBox;` — Snapshot Information Text
- L99 _private member_ `TSharedPtr<STextBlock> SelectedActorCountText;`
- L100 _private member_ `TSharedPtr<STextBlock> MiscActorCountText;`
- L102 _private member_ `FText DefaultNameText;`
- L104 _private prototype_ `FReply SetAllActorGroupsCollapsed();`
- L108 _private prototype_ `void OnResultsViewSearchTextChanged(const FText& Text) const;`
- L110 _private member_ `FDelegateHandle OnActiveSnapshotChangedHandle;`
- L111 _private member_ `FDelegateHandle OnRefreshResultsHandle;`
- L113 _private member_ `TWeakObjectPtr<ULevelSnapshotsEditorData> EditorDataPtr;`
- L115 _private member_ `TSharedPtr<SSearchBox> ResultsSearchBoxPtr;`
- L116 _private member_ `TSharedPtr<SBox> ResultsBoxContainerPtr;`
- L120 _private member_ `bool bShowFilteredActors = false;`
- L121 _private member_ `bool bShowUnselectedActors = true;`
- L124 _private member_ `FLevelSnapshotsEditorResultsSplitterManagerPtr SplitterManagerPtr;` — For splitter sync
- L128 _private prototype_ `void GenerateTreeView(const bool bSnapshotHasChanged);`
- L129 _private prototype_ `bool GenerateTreeViewChildren_ModifiedActors(FLevelSnapshotsEditorResultsRowPtr ModifiedActorsHeader);`
- L130 _private prototype_ `bool GenerateTreeViewChildren_AddedActors(FLevelSnapshotsEditorResultsRowPtr AddedActorsHeader);`
- L131 _private prototype_ `bool GenerateTreeViewChildren_RemovedActors(FLevelSnapshotsEditorResultsRowPtr RemovedActorsHeader);`
- L133 _private prototype_ `void OnGetRowChildren(FLevelSnapshotsEditorResultsRowPtr Row, TArray<FLevelSnapshotsEditorResultsRowPtr>& OutChildren);`
- L134 _private prototype_ `void OnRowChildExpansionChange(FLevelSnapshotsEditorResultsRowPtr Row, const bool bIsExpanded, const bool bIsRecursive = false) const;`
- L136 _private prototype_ `void SetChildExpansionRecursively(const FLevelSnapshotsEditorResultsRowPtr& InRow, const bool bNewIsExpanded) const;`
- L138 _private member_ `TSharedPtr<STreeView<FLevelSnapshotsEditorResultsRowPtr>> TreeViewPtr;`
- L141 _private member_ `TArray<FLevelSnapshotsEditorResultsRowPtr> TreeViewRootHeaderObjects;` — Holds all the header groups
- L142 _private member_ `TArray<FLevelSnapshotsEditorResultsRowPtr> TreeViewModifiedActorGroupObjects;`
- L143 _private member_ `TArray<FLevelSnapshotsEditorResultsRowPtr> TreeViewAddedActorGroupObjects;`
- L144 _private member_ `TArray<FLevelSnapshotsEditorResultsRowPtr> TreeViewRemovedActorGroupObjects;`
- L147 _private member_ `FLevelSnapshotsEditorResultsRowPtr DummyRow;` — Used to show that a group has children before the children are actually generated
- L148 _private member_ `FFilterListData FilterListData;`
- L151 _private member_ `TSet<TSharedPtr<FRowGeneratorInfo>> RegisteredRowGenerators;` — The results view should be the sole manager of the RowGenerators' lifetimes
- L154 _private member_ `TSet<TSharedPtr<FLevelSnapshotsEditorResultsRowStateMemory>> RowStateMemory;` — This list remembers the checked and expansion states of previously created rows so these states can be recreated on refresh.

#### Free symbols / members of external scopes

- L23 _typedef_ `typedef TSharedPtr<FLevelSnapshotsEditorResultsRow> FLevelSnapshotsEditorResultsRowPtr;`
- L24 _typedef_ `typedef TSharedPtr<FLevelSnapshotsEditorResultsSplitterManager> FLevelSnapshotsEditorResultsSplitterManagerPtr;`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshotsEditor/Private/Views/Results/SLevelSnapshotsEditorResultsRow.h` (Private)


#### class `SLevelSnapshotsEditorResultsRow`  
`class SLevelSnapshotsEditorResultsRow : public SCompoundWidget`  
_L15-74_
- inherits: `SCompoundWidget`
- L19 _public function_ `SLATE_BEGIN_ARGS(SLevelSnapshotsEditorResultsRow)`
- L22 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TWeakPtr<FLevelSnapshotsEditorResultsRow>& InRow, const FLevelSnapshotsEditorResultsSplitterManagerPtr& InSplitterManagerPtr);`
- L26 _public prototype_ `~SLevelSnapshotsEditorResultsRow();`
- L28 _public prototype_ `void GenerateAddedAndRemovedRowComponents(const TSharedRef<SHorizontalBox> BasicRowWidgets, const FLevelSnapshotsEditorResultsRowPtr PinnedItem, const FText& InDisplayText) const;`
- L30 _public prototype_ `TSharedRef<SWidget> GenerateFinalValueWidget( const ELevelSnapshotsObjectType InObjectType, FLevelSnapshotsEditorResultsRowPtr PinnedItem, const bool bIsHeaderRow, const bool bNeedsNullWidget) const;`
- L33 _public prototype_ `static const FSlateBrush* GetBorderImage(const FLevelSnapshotsEditorResultsRow::ELevelSnapshotsEditorResultsRowType InRowType);`
- L35 _public prototype_ `float GetNameColumnSize() const;`
- L37 _public prototype_ `float CalculateAndReturnNestedColumnSize();`
- L39 _public prototype_ `float GetSnapshotColumnSize() const;`
- L41 _public prototype_ `float GetWorldColumnSize() const;`
- L43 _public prototype_ `void SetNestedColumnSize(const float InWidth) const;`
- L45 _public prototype_ `void SetSnapshotColumnSize(const float InWidth) const;`
- L47 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L51 _private member_ `TSharedPtr<SSplitter> OuterSplitterPtr = nullptr;`
- L52 _private member_ `TSharedPtr<SSplitter> NestedSplitterPtr = nullptr;`
- L54 _private member_ `TWeakPtr<FLevelSnapshotsEditorResultsRow> Item = nullptr;`
- L60 _private member_ `float CachedNestedColumnWidthAdjusted = 0.f;` — To sync up splitter location in tree view items, we need to account for the tree view's indentation. Instead of calculating the coefficient twice each frame (for left and right splitter slots), we do it once and cache it here.
- L62 _private member_ `FLevelSnapshotsEditorResultsSplitterManagerPtr SplitterManagerPtr;`
- L66 _private member_ `const FTextFormat AddTextFormat = FTextFormat(LOCTEXT("LevelSna`
- L67 _private member_ `const FTextFormat RemoveTextFormat = FTextFormat(LOCTEXT("LevelSna`
- L69 _private member_ `const FText ActorComponentText = LOCTEXT("LevelSn`
- L70 _private member_ `const FText SceneComponentText = LOCTEXT("LevelSn`
- L71 _private member_ `const FText SubobjectText = LOCTEXT("LevelSn`

#### Free symbols / members of external scopes

- L13 _typedef_ `typedef TSharedPtr<FLevelSnapshotsEditorResultsSplitterManager> FLevelSnapshotsEditorResultsSplitterManagerPtr;`
- L64 _macro_ `#define LOCTEXT_NAMESPACE "LevelSnapshotsEditor"`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshotsEditor/Private/Views/SLevelSnapshotsEditor.h` (Private)


#### class `SLevelSnapshotsEditor`  
`class SLevelSnapshotsEditor : public SCompoundWidget`  
_L22-65_
- inherits: `SCompoundWidget`
- L26 _private typedef_ `using Super = SCompoundWidget;`
- L28 _private member_ `static const FName AppIdentifier;`
- L29 _private member_ `static const FName ToolbarTabId;`
- L30 _private member_ `static const FName InputTabID;`
- L31 _private member_ `static const FName FilterTabID;`
- L32 _private member_ `static const FName ResultsTabID;`
- L35 _public function_ `SLATE_BEGIN_ARGS(SLevelSnapshotsEditor)`
- L36 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, ULevelSnapshotsEditorData* InEditorData, const TSharedRef<SDockTab>& ConstructUnderTab, const TSharedPtr<SWindow>& ConstructUnderWindow);`
- L40 _public prototype_ `void OpenLevelSnapshotsDialogWithAssetSelected(const FAssetData& InAssetData) const;`
- L44 _private prototype_ `void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager, const TSharedRef<FWorkspaceItem>& AppMenuGroup);`
- L46 _private prototype_ `TSharedRef<SDockTab> SpawnTab_CustomToolbar(const FSpawnTabArgs& Args);`
- L47 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Input(const FSpawnTabArgs& Args);`
- L48 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Filter(const FSpawnTabArgs& Args);`
- L49 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Results(const FSpawnTabArgs& Args);`
- L51 _private prototype_ `FReply OnClickTakeSnapshot();`
- L52 _private prototype_ `FReply OnClickInputPanelExpand();`
- L54 _private member_ `TWeakObjectPtr<ULevelSnapshotsEditorData> EditorData;`
- L56 _private member_ `TSharedPtr<SLevelSnapshotsEditorInput> EditorInputWidget;`
- L59 _private member_ `TSharedPtr<FTabManager> TabManager;` — Holds the tab manager that manages the tabs
- L61 _private member_ `TSharedPtr<SCheckBox> SettingsButtonPtr;`
- L63 _private member_ `TSharedPtr<SDockTab> InputTab;`
- L64 _private member_ `bool bInputPanelExpanded = true;`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshotsEditor/Private/Widgets/Filter/SCreateNewFilterWidget.h` (Private)


#### class `SCreateNewFilterWidget`  
`class SCreateNewFilterWidget : public SCompoundWidget`  
_L14-30_
- inherits: `SCompoundWidget`
- desc: Put into rows and allows user to create to pick a filter to add to the row.
- L18 _public function_ `SLATE_BEGIN_ARGS(SCreateNewFilterWidget)`
- L20 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UFavoriteFilterContainer* InAvailableFilters, UConjunctionFilter* InFilterToAddTo);`
- L26 _private member_ `TWeakObjectPtr<UFavoriteFilterContainer> AvailableFilters;`
- L27 _private member_ `TWeakObjectPtr<UConjunctionFilter> FilterToAddTo;`
- L29 _private member_ `TSharedPtr<SComboButton> ComboButton;`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshotsEditor/Private/Widgets/Filter/SFavoriteFilter.h` (Private)


#### class `SFavoriteFilter`  
`class SFavoriteFilter : public SCompoundWidget`  
_L17-38_
- inherits: `SCompoundWidget`
- desc: Display in the favorite filter list.
- L21 _public function_ `SLATE_BEGIN_ARGS(SFavoriteFilter)`
- L23 _public prototype_ `SLATE_ATTRIBUTE(FText, FilterName) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSubclassOf<ULevelSnapshotFilter>& InFilterClass, const TWeakObjectPtr<ULevelSnapshotsEditorData>& InEditorData);`
- L29 _public prototype_ `FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L30 _public prototype_ `FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L35 _private member_ `TSubclassOf<ULevelSnapshotFilter> FilterClass;`
- L37 _private member_ `TWeakObjectPtr<ULevelSnapshotsEditorData> DragDropActiveFilterSetterArgument;` — Passed to drag drop operation so it can set the filter being edited.

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshotsEditor/Private/Widgets/Filter/SFavoriteFilterList.h` (Private)


#### class `SFavoriteFilterList`  
`class SFavoriteFilterList : public SCompoundWidget`  
_L16-37_
- inherits: `SCompoundWidget`
- L20 _public prototype_ `~SFavoriteFilterList();`
- L22 _public function_ `SLATE_BEGIN_ARGS(SFavoriteFilterList)`
- L24 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UFavoriteFilterContainer* InModel, ULevelSnapshotsEditorData* InEditorData);`
- L30 _private prototype_ `void UpdateFilterList(ULevelSnapshotsEditorData* InEditorData);`
- L32 _private member_ `TSharedPtr<SWrapBox> FilterList;`
- L33 _private member_ `TSharedPtr<SComboButton> ComboButton;`
- L35 _private member_ `TWeakObjectPtr<UFavoriteFilterContainer> FavoriteModel;`
- L36 _private member_ `FDelegateHandle ChangedFavoritesDelegateHandle;`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshotsEditor/Private/Widgets/Filter/SFilterSearchMenu.h` (Private)


#### class `SFilterSearchMenu`  
`class SFilterSearchMenu : public SCompoundWidget`  
_L17-90_
- inherits: `SCompoundWidget`
- L21 _public prototype_ `DECLARE_DELEGATE_OneParam(FFilterDelegate, const TSubclassOf<ULevelSnapshotFilter>&);`
- L22 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsFilterSelected, const TSubclassOf<ULevelSnapshotFilter>&);`
- L23 _public prototype_ `DECLARE_DELEGATE_TwoParams(FSetIsCategorySelected, FName , bool );`
- L24 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsCategorySelected, FName );`
- L27 _public function_ `SLATE_BEGIN_ARGS(SFilterSearchMenu)`
- L29 _public prototype_ `SLATE_EVENT(FFilterDelegate, OnSelectFilter) SLATE_EVENT(FIsFilterSelected, OptionalIsFilterChecked) SLATE_EVENT(FSetIsCategorySelected, OptionalSetIsFilterCategorySelected) SLATE_EVENT(FIsCategorySelected, OptionalIsFilterCategorySelected) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UFavoriteFilterContainer* InFavoriteFilters);`
- L37 _public prototype_ `TSharedPtr<SSearchBox> GetSearchBox() const;`
- L41 _private prototype_ `void ResetOptions();`
- L43 _private prototype_ `void OnSearchChangedString(const FText& SearchText);`
- L44 _private prototype_ `void OnSearchCommited(const FText& SearchText, ETextCommit::Type CommitType);`
- L46 _private prototype_ `void ShowUnsearchedMenu();`
- L47 _private prototype_ `void ShowSearchResults();`
- L49 _private prototype_ `void OnClickItem(const TSharedPtr<TSubclassOf<ULevelSnapshotFilter>> Item);`
- L50 _private prototype_ `void OnItemSelected(const TSharedPtr<TSubclassOf<ULevelSnapshotFilter>> Item, ESelectInfo::Type SelectInfo);`
- L51 _private prototype_ `FReply OnHandleListViewKeyDown(const FGeometry& Geometry, const FKeyEvent& KeyEvent);`
- L52 _private prototype_ `TSharedRef<ITableRow> GenerateFilterClassWidget(TSharedPtr<TSubclassOf<ULevelSnapshotFilter>> InItem, const TSharedRef<STableViewBase>& OwnerTable) const;`
- L55 _private prototype_ `void OnUserConfirmedItemSelection(TSharedPtr<TSubclassOf<ULevelSnapshotFilter>> Item);` — Calls delegate and closes this menu
- L62 _private member_ `FFilterDelegate OnSelectFilter;` — Called when the user selects a filter
- L65 _private member_ `TWeakObjectPtr<UFavoriteFilterContainer> FilterContainer;` — Used to get available filters
- L72 _private member_ `TSharedPtr<SSearchBox> SearchBox;` — Searches filters
- L74 _private member_ `TSharedPtr<SHorizontalBox> MenuContainer;` — Dummy widget which holds either UnsearchedMenu or the results of the search.
- L77 _private member_ `TSharedPtr<SWidget> UnsearchedMenu;` — Unfiltered menu with submenu of filters.
- L79 _private member_ `TSharedPtr< SListView< TSharedPtr< TSubclassOf<ULevelSnapshotFilter> > > > SearchResultsWidget;` — Filtered menu with all filters matching the search.
- L85 _private member_ `TArray< TSharedPtr< TSubclassOf<ULevelSnapshotFilter> > > FilteredOptions;`
- L86 _private member_ `TArray<TSubclassOf<ULevelSnapshotFilter>> UnfilteredOptions;`
- L88 _private member_ `TSharedPtr<TSubclassOf<ULevelSnapshotFilter>> SelectedItem;`
- L89 _private member_ `FText HighlightText;`

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_DELEGATE_OneParam(FFilterDelegate, const TSubclassOf<ULevelSnapshotFilter>&);`
- L22 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsFilterSelected, const TSubclassOf<ULevelSnapshotFilter>&);`
- L23 _delegate_ `DECLARE_DELEGATE_TwoParams(FSetIsCategorySelected, FName , bool );`
- L24 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsCategorySelected, FName );`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshotsEditor/Private/Widgets/Filter/SHoverableFilterActions.h` (Private)


#### class `SHoverableFilterActions`  
`class SHoverableFilterActions : public SCompoundWidget`  
_L11-36_
- inherits: `SCompoundWidget`
- desc: Shows a checkbox for ignoring and a delete button
- L15 _public prototype_ `DECLARE_DELEGATE_RetVal(bool, FIsFilterIgnored);`
- L16 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnChangeFilterIgnored, bool );`
- L17 _public prototype_ `DECLARE_DELEGATE(FOnPressDelete);`
- L19 _public function_ `SLATE_BEGIN_ARGS(SHoverableFilterActions) : _BackgroundHoverColor(FLinearColor(0.f, 0.f, 0.f, 0.f))`
- L23 _public prototype_ `SLATE_EVENT(FIsFilterIgnored, IsFilterIgnored) SLATE_EVENT(FOnChangeFilterIgnored, OnChangeFilterIgnored) SLATE_EVENT(FOnPressDelete, OnPressDelete) SLATE_ATTRIBUTE(FSlateColor, BackgroundHoverColor) SLATE_END_ARGS() void Construct(FArguments InArgs, TWeakPtr<SWidget> InHoverOwner);`
- L33 _private member_ `FIsFilterIgnored IsFilterIgnored;`
- L34 _private member_ `FOnChangeFilterIgnored OnChangeFilterIgnored;`
- L35 _private member_ `FOnPressDelete OnPressDelete;`

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FIsFilterIgnored);`
- L16 _delegate_ `DECLARE_DELEGATE_OneParam(FOnChangeFilterIgnored, bool );`
- L17 _delegate_ `DECLARE_DELEGATE(FOnPressDelete);`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshotsEditor/Private/Widgets/Filter/SLevelSnapshotsFilterCheckBox.h` (Private)


#### class `SLevelSnapshotsFilterCheckBox`  
`class SLevelSnapshotsFilterCheckBox : public SCompoundWidget`  
_L14-45_
- inherits: `SCompoundWidget`
- desc: Displays contents of filters.
- L18 _public function_ `SLATE_BEGIN_ARGS(SLevelSnapshotsFilterCheckBox)`
- L20 _public prototype_ `SLATE_DEFAULT_SLOT( FArguments, Content ) SLATE_EVENT(FOnClicked, OnFilterCtrlClicked) SLATE_EVENT(FOnClicked, OnFilterAltClicked) SLATE_EVENT(FOnClicked, OnFilterMiddleButtonClicked) SLATE_EVENT(FOnClicked, OnFilterRightButtonClicked) SLATE_EVENT(FOnClicked, OnFilterClickedOnce) SLATE_ATTRIBUTE( FMargin, Padding ) SLATE_ATTRIBUTE( FSlateColor, ForegroundColor ) SLATE_ARGUMENT( EHorizontalAlignment, HAlign ) SLATE_END_ARGS();`
- L31 _public prototype_ `void Construct(const FArguments& Args);`
- L33 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L34 _public prototype_ `virtual FReply OnMouseButtonUp( const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent ) override;`
- L38 _private member_ `FOnClicked OnFilterCtrlClicked;`
- L39 _private member_ `FOnClicked OnFilterAltClicked;`
- L40 _private member_ `FOnClicked OnFilterMiddleButtonClicked;`
- L41 _private member_ `FOnClicked OnFilterRightButtonClicked;`
- L42 _private member_ `FOnClicked OnFilterClickedOnce;`
- L44 _private member_ `TSharedPtr<SBorder> ContentContainer;`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshotsEditor/Private/Widgets/Filter/SSaveAndLoadFilters.h` (Private)


#### class `SSaveAndLoadFilters`  
`class SSaveAndLoadFilters : public SCompoundWidget`  
_L12-28_
- inherits: `SCompoundWidget`
- desc: Creates buttons for save & load of filters.
- L16 _public function_ `SLATE_BEGIN_ARGS(SSaveAndLoadFilters)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, ULevelSnapshotsEditorData* InEditorData);`
- L24 _private prototype_ `TSharedRef<SWidget> GenerateSaveLoadMenu();`
- L26 _private member_ `TWeakObjectPtr<ULevelSnapshotsEditorData> EditorData;`
- L27 _private member_ `TWeakObjectPtr<UFilterLoader> FilterLoader;`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshotsEditor/Private/Widgets/SLevelSnapshotsEditorBrowser.h` (Private)


#### class `SLevelSnapshotsEditorBrowser`  
`class SLevelSnapshotsEditorBrowser : public SCompoundWidget`  
_L14-41_
- inherits: `SCompoundWidget`
- L17 _public function_ `SLATE_BEGIN_ARGS(SLevelSnapshotsEditorBrowser)`
- L21 _public prototype_ `SLATE_ATTRIBUTE(FSoftObjectPath, OwningWorldPath) SLATE_END_ARGS() void Construct(const FArguments& InArgs, ULevelSnapshotsEditorData* InEditorData);` — Attribute for retrieving the current context
- L28 _public prototype_ `void SelectAsset(const FAssetData& InAssetData) const;`
- L32 _private prototype_ `TArray<FAssetViewCustomColumn> GetCustomColumns() const;`
- L33 _private prototype_ `void OnAssetDoubleClicked(const FAssetData& InAssetData) const;`
- L34 _private prototype_ `bool OnShouldFilterAsset(const FAssetData& InAssetData) const;`
- L35 _private prototype_ `TSharedPtr<SWidget> OnGetAssetContextMenu(const TArray<FAssetData>& SelectedAssets);`
- L36 _private prototype_ `TSharedRef<SToolTip> CreateCustomTooltip(FAssetData& AssetData);`
- L38 _private member_ `TAttribute<FSoftObjectPath> OwningWorldPathAttribute;`
- L40 _private member_ `TWeakObjectPtr<ULevelSnapshotsEditorData> EditorData;`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshotsEditor/Private/Widgets/SLevelSnapshotsEditorCreationForm.h` (Private)


#### class `SLevelSnapshotsEditorCreationForm`  
`class SLevelSnapshotsEditorCreationForm : public SCompoundWidget`  
_L14-45_
- inherits: `SCompoundWidget`
- L18 _public prototype_ `static TSharedRef<SWindow> MakeAndShowCreationWindow(const FCloseCreationFormDelegate& CallOnClose);`
- L20 _public function_ `SLATE_BEGIN_ARGS(SLevelSnapshotsEditorCreationForm)`
- L22 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TWeakPtr<SWindow> InWidgetWindow, const FCloseCreationFormDelegate& CallOnClose);`
- L26 _public prototype_ `FText GetNameOverrideText() const;`
- L27 _public prototype_ `void SetNameOverrideText(const FText& InNewText, ETextCommit::Type InCommitType);`
- L28 _public prototype_ `void SetDescriptionText(const FText& InNewText, ETextCommit::Type InCommitType);`
- L30 _public prototype_ `EVisibility GetNameDiffersFromDefaultAsVisibility() const;`
- L32 _public prototype_ `FReply OnResetNameClicked();`
- L33 _public prototype_ `FReply OnCreateButtonPressed();`
- L37 _private member_ `TWeakPtr<SWindow> WidgetWindow;`
- L39 _private member_ `FText DescriptionText;`
- L40 _private member_ `TOptional<FString> NameOverride;`
- L41 _private member_ `FCloseCreationFormDelegate CallOnCloseDelegate;`
- L43 _private prototype_ `TSharedRef<SWidget> MakeDataManagementSettingsDetailsWidget() const;`
- L44 _private prototype_ `void OnWindowClosed(const TSharedRef<SWindow>& ParentWindow) const;`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_DELEGATE_TwoParams(FCloseCreationFormDelegate, const FText& , const FString& );`
- L8 _prototype_ `DECLARE_DELEGATE_TwoParams(FCloseCreationFormDelegate, const FText& , const FString& );`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshotsEditor/Private/Widgets/SLevelSnapshotsEditorFilter.h` (Private)


#### class `SLevelSnapshotsEditorFilter`  
`class SLevelSnapshotsEditorFilter : public SCompoundWidget`  
_L23-73_
- inherits: `SCompoundWidget`
- desc: Displays a filter in the editor.
- L26 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnClickRemoveFilter, TSharedRef<SLevelSnapshotsEditorFilter>);`
- L27 _public prototype_ `DECLARE_DELEGATE_RetVal(bool, FIsParentFilterIgnored);`
- L29 _public prototype_ `~SLevelSnapshotsEditorFilter();`
- L30 _public function_ `SLATE_BEGIN_ARGS(SLevelSnapshotsEditorFilter)`
- L32 _public prototype_ `SLATE_EVENT(FOnClickRemoveFilter, OnClickRemoveFilter) SLATE_EVENT(FIsParentFilterIgnored, IsParentFilterIgnored) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TWeakObjectPtr<UNegatableFilter>& InFilter, ULevelSnapshotsEditorData* InEditorData);`
- L38 _public prototype_ `const TWeakObjectPtr<UNegatableFilter>& GetSnapshotFilter() const;`
- L41 _public prototype_ `int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L47 _private prototype_ `FText GetFilterTooltip() const;`
- L48 _private prototype_ `FSlateColor GetFilterColor() const;`
- L50 _private prototype_ `FReply OnSelectFilterForEdit();`
- L51 _private prototype_ `FReply OnNegateFilter();`
- L52 _private prototype_ `FReply OnRemoveFilter();`
- L54 _private prototype_ `void OnActiveFilterChanged(UNegatableFilter* NewFilter);`
- L57 _private member_ `FOnClickRemoveFilter OnClickRemoveFilter;` — Used to remove this filter
- L59 _private member_ `FIsParentFilterIgnored IsParentFilterIgnored;` — Used to darken filter colour when the parent is ignored.
- L61 _private member_ `FDelegateHandle OnFilterDestroyedDelegateHandle;`
- L62 _private member_ `FDelegateHandle ActiveFilterChangedDelegateHandle;`
- L63 _private member_ `bool bShouldHighlightFilter = false;`
- L66 _private member_ `TSharedPtr<SLevelSnapshotsFilterCheckBox> ToggleButtonPtr;` — The button to toggle the filter on or off
- L68 _private member_ `TSharedPtr<SClickableText> FilterNamePtr;` — Displays filter name and shows details panel when clicked.
- L71 _private member_ `TWeakObjectPtr<UNegatableFilter> SnapshotFilter;` — Filter managed by this widget
- L72 _private member_ `TWeakObjectPtr<ULevelSnapshotsEditorData> EditorData;`

#### Free symbols / members of external scopes

- L26 _delegate_ `DECLARE_DELEGATE_OneParam(FOnClickRemoveFilter, TSharedRef<SLevelSnapshotsEditorFilter>);`
- L27 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FIsParentFilterIgnored);`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshotsEditor/Private/Widgets/SLevelSnapshotsEditorFilterList.h` (Private)


#### class `SLevelSnapshotsEditorFilterList`  
`class SLevelSnapshotsEditorFilterList : public SCompoundWidget`  
_L20-45_
- inherits: `SCompoundWidget`
- desc: Lists a bunch of filters.
- L24 _public function_ `SLATE_BEGIN_ARGS(SLevelSnapshotsEditorFilterList)`
- L26 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UConjunctionFilter* InManagedAndCondition, ULevelSnapshotsEditorData* InEditorData);`
- L32 _private prototype_ `void Rebuild();`
- L34 _private prototype_ `void OnClickRemoveFilter(TSharedRef<SLevelSnapshotsEditorFilter> RemovedFilterWidget) const;`
- L35 _private prototype_ `bool AddTutorialTextAndCreateFilterWidgetIfEmpty() const;`
- L36 _private prototype_ `void AddChild(UNegatableFilter* AddedFilter, bool bSkipAnd = false) const;`
- L39 _private member_ `TSharedPtr<SWrapBox> FilterBox;` — The horizontal box which contains all the filters
- L41 _private member_ `TSharedPtr<SCreateNewFilterWidget> AddFilterWidget;` — Wiget with which user can add filters
- L43 _private member_ `TWeakObjectPtr<ULevelSnapshotsEditorData> EditorData;`
- L44 _private member_ `TWeakObjectPtr<UConjunctionFilter> ManagedAndCondition;`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshotsEditor/Private/Widgets/SLevelSnapshotsEditorFilterRow.h` (Private)


#### class `SLevelSnapshotsEditorFilterRow`  
`class SLevelSnapshotsEditorFilterRow : public SCompoundWidget`  
_L15-48_
- inherits: `SCompoundWidget`
- desc: Creates all widgets needed to show an AND-condition of filters.
- L19 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnClickRemoveRow, TSharedRef<SLevelSnapshotsEditorFilterRow>);`
- L21 _public function_ `SLATE_BEGIN_ARGS(SLevelSnapshotsEditorFilterRow)`
- L23 _public prototype_ `SLATE_EVENT(FOnClickRemoveRow, OnClickRemoveRow) SLATE_END_ARGS() void Construct( const FArguments& InArgs, ULevelSnapshotsEditorData* InEditorData, UConjunctionFilter* InManagedFilter, const bool bShouldShowOrInFront );`
- L33 _public prototype_ `const TWeakObjectPtr<UConjunctionFilter>& GetManagedFilter();`
- L36 _public prototype_ `void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L37 _public prototype_ `void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L38 _public prototype_ `FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L43 _private member_ `FOnClickRemoveRow OnClickRemoveRow;`
- L45 _private member_ `TWeakObjectPtr<UConjunctionFilter> ManagedFilterWeakPtr;`
- L47 _private member_ `TSharedPtr<SLevelSnapshotsEditorFilterList> FilterList;` — Stores all filters

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_DELEGATE_OneParam(FOnClickRemoveRow, TSharedRef<SLevelSnapshotsEditorFilterRow>);`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshotsEditor/Public/LevelSnapshotsEditorFunctionLibrary.h` (Public)


#### class `ULevelSnapshotsEditorFunctionLibrary`  
`class ULevelSnapshotsEditorFunctionLibrary : public UBlueprintFunctionLibrary`  
_L13-39_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L26 _public prototype_ `static ULevelSnapshot* TakeLevelSnapshotAndSaveToDisk( const UObject* WorldContextObject, const FString& FileName, const FString& FolderPath, const FString& Description, const bool bShouldCreateUniqueFileName = true);` — `UFUNCTION(BlueprintCallable, Category = "LevelSnapshots", meta = (DevelopmentOnly, WorldContext = "WorldContextObject"))` — @brief Creates a new Level Snapshot asset in the content browser and then captures the target world @param WorldContextObject Context object to determine which world to take the snapshot in @param FileName The desired asset file name @param FolderPath The desired asset location @param bShouldCreateUniqueFileName If true, the asset name will have a number incrementally added to the file name if an asset with a similar name already exists. If false, the existing asset will be overwritten.
- L33 _public prototype_ `static void TakeAndSaveLevelSnapshotEditorWorld(const FString& FileName, const FString& FolderPath, const FString& Description);` — `UFUNCTION(BlueprintCallable, Category = "LevelSnapshots")` — Uses TakeLevelSnapshotAndSaveToDisk() and assumes Editor World
- L37 _public prototype_ `static void GenerateThumbnailForSnapshotAsset(ULevelSnapshot* SnapshotPackage);` — `UFUNCTION(BlueprintCallable, Category = "LevelSnapshots")` — If the snapshot is saved in the registry, takes a screenshot of the editor scene and sets it as thumnail for the snapshot.
