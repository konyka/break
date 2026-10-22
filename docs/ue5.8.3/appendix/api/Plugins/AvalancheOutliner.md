# Plugins / AvalancheOutliner

- module root: `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner`
- headers: 84; symbols: 1460
- symbol kinds: class=80, delegate=10, enum=17, enumerator=60, function=225, macro=1, member=267, namespace=5, prototype=769, struct=18, typedef=8
- PrivateDependencyModuleNames: AvalancheEditorCore, AvalancheSceneTree, BlueprintGraph, EditorWidgets, InputCore, Projects, ToolMenus, ToolWidgets, TypedElementRuntime
- PublicDependencyModuleNames: AvalancheCore, Core, CoreUObject, DeveloperSettings, Engine, Slate, SlateCore, UnrealEd

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/AvaOutliner.h` (Private)


#### class `FAvaOutliner`  
`class FAvaOutliner : public IAvaOutliner , public FTickableEditorObject , public FEditorUndoClient`  
_L36-339_
- inherits: `IAvaOutliner,FTickableEditorObject,FEditorUndoClient`
- L42 _public prototype_ `FAvaOutliner(IAvaOutlinerProvider& InOutlinerProvider);`
- L51 _public prototype_ `UAvaOutlinerSubsystem* GetOutlinerSubsystem() const;` — Gets the Outliner Subsystem of the World this Outliner is responsible for NOTE: The OutlinerSubsystem's Outliner Instance should be the same as this one in the default implementation but can differ if there are multiple FAvaOutliner instances being used in custom implementations
- L57 _public prototype_ `bool IsActorAllowedInOutliner(const AActor* InActor) const;` — Determines whether the given actor can be presented in the Outliner, at all. This is a permanent check unlike filters that are temporary.
- L63 _public prototype_ `bool IsComponentAllowedInOutliner(const USceneComponent* InComponent) const;` — Determines whether the given scene component can be presented in the Outliner, at all. This is a permanent check unlike filters that are temporary.
- L65 _public prototype_ `bool CanProcessActorSpawn(AActor* InActor) const;`
- L67 _public prototype_ `TSharedPtr<FUICommandList> GetBaseCommandList() const;`
- L69 _public member_ `FOnOutlinerLoaded OnOutlinerLoaded;`
- L72 _public prototype_ `TArray<FName> GetRegisteredItemProxyTypeNames() const;` — Gathers the Type Names of all the Item Proxies that are registered both in the outliner proxy registry and the module's
- L75 _public prototype_ `void GetItemProxiesForItem(const FAvaOutlinerItemPtr& InItem, TArray<TSharedPtr<FAvaOutlinerItemProxy>>& OutItemProxies);` — Gathers all previously existing and new Item Proxies for a given Item
- L78 _public prototype_ `IAvaOutlinerItemProxyFactory* GetItemProxyFactory(FName InItemProxyTypeName) const;` — Tries to find the Item Proxy Factory for the given Item Proxy Type Name
- L80 _public prototype_ `const TSharedRef<FAvaOutlinerSaveState>& GetSaveState() const;`
- L83 _public prototype_ `bool IsOutlinerLocked() const;` — Returns whether the Outliner is in Read-only mode
- L85 _public prototype_ `void HandleUndoRedoTransaction(const FTransaction* Transaction, bool bIsUndo);`
- L88 _public function_ `virtual FOnOutlinerLoaded& GetOnOutlinerLoaded() override`
- L89 _public function_ `virtual IAvaOutlinerProvider& GetProvider() const override`
- L90 _public prototype_ `virtual void SetBaseCommandList(const TSharedPtr<FUICommandList>& InBaseCommandList) override;`
- L91 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L92 _public prototype_ `virtual TSharedPtr<IAvaOutlinerView> RegisterOutlinerView(int32 InOutlinerViewId) override;`
- L93 _public prototype_ `virtual TSharedPtr<IAvaOutlinerView> GetOutlinerView(int32 InOutlinerViewId) const override;`
- L94 _public prototype_ `virtual void RegisterItem(const FAvaOutlinerItemPtr& InItem) override;`
- L95 _public prototype_ `virtual void UnregisterItem(const FAvaOutlinerItemId& InItemId) override;`
- L96 _public prototype_ `virtual void RequestRefresh() override;`
- L97 _public prototype_ `virtual void Refresh() override;`
- L98 _public prototype_ `virtual TSharedRef<FAvaOutlinerItem> GetTreeRoot() const override;`
- L99 _public prototype_ `virtual FAvaOutlinerItemPtr FindItem(const FAvaOutlinerItemId& InItemId) const override;`
- L100 _public prototype_ `virtual void SetIgnoreNotify(EAvaOutlinerIgnoreNotifyFlags InFlag, bool bIgnore) override;`
- L101 _public prototype_ `virtual void OnActorsCopied(FString& InOutCopiedData, TConstArrayView<AActor*> InCopiedActors) override;`
- L102 _public prototype_ `virtual void OnActorsPasted(FStringView InPastedData, const TMap<FName, AActor*>& InPastedActors) override;`
- L103 _public prototype_ `virtual void OnActorsDuplicated(const TMap<AActor*, AActor*>& InDuplicateActorMap, FAvaOutlinerItemPtr InRelativeItem = nullptr, TOptional<EItemDropZone> InRelativeDropZone = TOptional<EItemDropZone>()) override;`
- L104 _public prototype_ `virtual void GroupSelection(AActor* InGroupingActor, const TOptional<FAttachmentTransformRules>& InTransformRules = TOptional<FAttachmentTransformRules>()) override;`
- L105 _public prototype_ `virtual void OnObjectSelectionChanged(const FAvaEditorSelection& InEditorSelection) override;`
- L106 _public prototype_ `virtual UWorld* GetWorld() const override;`
- L107 _public prototype_ `virtual const FAvaOutlinerItemProxyRegistry& GetItemProxyRegistry() const override;`
- L108 _public prototype_ `virtual bool IsDefaultWorldActorToHide(const UWorld* const InWorld, const AActor* const InActor) const override;`
- L111 _public prototype_ `FAvaOutlinerItemProxyRegistry& GetItemProxyRegistry();`
- L114 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L115 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L119 _public prototype_ `virtual TStatId GetStatId() const override;`
- L120 _public prototype_ `virtual void Tick(float InDeltaTime) override;`
- L129 _public prototype_ `void DuplicateItems(TArray<FAvaOutlinerItemPtr> InItems , FAvaOutlinerItemPtr InRelativeItem , TOptional<EItemDropZone> InRelativeDropZone);` — Creates a new set of items in the outliner based on the given template items @param InItems the template items to use for duplication @param InRelativeItem the existing outliner item that items should use as positional reference @param InRelativeDropZone where to put the duplicate items with relation to InRelativeItem (above, below, onto)
- L136 _public prototype_ `void DeleteItems(TArray<FAvaOutlinerItemPtr> InItems);` — Delete a set of items in the outliner by calling their custom delete handler
- L139 _public prototype_ `void UnregisterOutlinerView(int32 InOutlinerViewId);` — Unregisters the Outliner View bound to the given id
- L142 _public prototype_ `void UpdateRecentOutlinerViews(int32 InOutlinerViewId);` — Sets the given Outliner View Id as the most recent Outliner View
- L145 _public prototype_ `TSharedPtr<FAvaOutlinerView> GetMostRecentOutlinerView() const;` — Gets the outliner view that was most recently used (i.e. called FAvaOutliner::UpdateRecentOutlinerViews)
- L148 _public prototype_ `void ForEachOutlinerView(const TFunction<void(const TSharedPtr<FAvaOutlinerView>& InOutlinerView)>& InPredicate) const;` — Executes the given predicate for each Outliner View registered
- L156 _public function_ `template<typename InItemActionType, typename = typename TEnableIf<TIsDerivedFrom<InItemActionType, IAvaOutlinerAction>::IsDerived>::Type, typename ...InArgTypes> TSharedRef<InItemActionType> NewItemAction(InArgTypes&&... InArgs)` — Instantiates a new item action without adding it to the Pending Actions Queue. This should only be used directly when planning to enqueue multiple actions. @see FAvaOutliner::EnqueueItemActions
- L167 _public function_ `template<typename InItemActionType, typename = typename TEnableIf<TIsDerivedFrom<InItemActionType, IAvaOutlinerAction>::IsDerived>::Type, typename ...InArgTypes> void EnqueueItemAction(InArgTypes&&... InArgs)` — Instantiates a single new item action and immediately adds it to the Pending Actions Queue. Ideal for when dealing with a single action. For multiple actions use FAvaOutliner::EnqueueItemActions.
- L173 _public prototype_ `void EnqueueItemActions(TArray<TSharedPtr<IAvaOutlinerAction>>&& InItemActions) noexcept;` — Adds the given actions to the Pending Action Queue
- L176 _public prototype_ `int32 GetPendingItemActionCount() const;` — Returns the number of actions that been added to the queue so far before triggering a refresh
- L179 _public prototype_ `bool NeedsRefresh() const;` — Returns whether the Outliner is currently in need of a Refresh
- L187 _public prototype_ `TOptional<FAvaOutlinerColorPair> FindItemColor(const FAvaOutlinerItemPtr& InItem, bool bRecurseParent = true) const;` — Gets the color pair (color name, linear color) related to the Item @param InItem the item to query @param bRecurseParent whether to get the color of the parent (recursively) if the given item does not have a color by itself @returns the matching color pair or unset if item is invalid or no color could be found.
- L190 _public prototype_ `void SetItemColor(const FAvaOutlinerItemPtr& InItem, const FName& InColorName);` — Pairs the Item with the given color name, overriding the inherited color if different
- L193 _public prototype_ `void RemoveItemColor(const FAvaOutlinerItemPtr& InItem);` — Removes the Color pairing of the given Item (can still have an inherited color though)
- L196 _public prototype_ `const TMap<FName, FLinearColor>& GetColorMap() const;` — Returns the color map from the Outliner Settings
- L202 _public prototype_ `void NotifyItemIdChanged(const FAvaOutlinerItemId& OldId, const FAvaOutlinerItemPtr& InItem);` — Replaces the Item's Id in the Item Map. This can be due to an object item changing it's object (e.g. a bp component getting destroyed and recreated, the item should be the same but the underlying component will not be)
- L205 _public prototype_ `TArray<FAvaOutlinerItemPtr> GetSelectedItems() const;` — Returns the currently selected items in the most recent outliner view (since this list can vary between outliner views)
- L208 _public prototype_ `int32 GetSelectedItemCount() const;` — Returns the number of currently selected items in the most recent outliner view
- L215 _public prototype_ `void SelectItems(const TArray<FAvaOutlinerItemPtr>& InItems, EAvaOutlinerItemSelectionFlags InFlags = EAvaOutlinerItemSelectionFlags::SignalSelectionChange) const;` — Selects the given Items on all Outliner Views @param InItems the items to select @param InFlags how the items should be selected (appended, notify of selections, etc)
- L221 _public prototype_ `void ClearItemSelection(bool bSignalSelectionChange) const;` — Clears the Item Selection from all Outliner Views @param bSignalSelectionChange whether to notify the change in selection
- L224 _public prototype_ `static FAvaOutlinerItemPtr FindLowestCommonAncestor(const TArray<FAvaOutlinerItemPtr>& Items);` — Gets the closest item to all the given items while also being their common ancestor
- L227 _public prototype_ `static FAvaSceneItem MakeSceneItemFromOutlinerItem(const FAvaOutlinerItemPtr& InItem);` — Converts the given Outliner Item to a Scene Item that can be serialized in the Scene Tree
- L233 _public prototype_ `static void SortItems(TArray<FAvaOutlinerItemPtr>& OutOutlinerItems);` — Helper function to sort the given array of items based on their ordering in the Outliner @see FAvaOutliner::CompareOutlinerItemOrder
- L236 _public prototype_ `static void NormalizeItems(TArray<FAvaOutlinerItemPtr>& InOutItems);` — Normalizes the given Items by removing selected items that have their parent item also in the selection
- L239 _public prototype_ `FEditorModeTools* GetModeTools() const;` — Gets the Editor Mode Tools used to handle selections
- L242 _public prototype_ `void SyncModeToolsSelection(const TArray<FAvaOutlinerItemPtr>& InSelectedItems) const;` — Have the given Selected Items sync to the USelection Instances of Mode Tools
- L245 _public prototype_ `TArray<TWeakObjectPtr<AActor>> GetActorSceneOutlinerChildren(AActor* InParentActor) const;` — Gets all the Actors that have as their AActor::GetSceneOutlinerParent the given InParentActor
- L248 _public prototype_ `void OnActorSpawned(AActor* InActor);` — Tries to add the new Actor to the Outliner if not added already and if the Outliner allows the given actor to be added
- L251 _public prototype_ `void OnActorDestroyed(AActor* InActor);` — Called when an Actor has been destroyed. This enqueues the Removal the Actor Item to the Pending Action Queue
- L254 _public prototype_ `void OnActorAttachmentChanged(AActor* InActor, const AActor* InParent, bool bAttach);` — Called when an Actor's attachment has changed. This triggers a refresh
- L257 _public prototype_ `void OnObjectsReplaced(const TMap<UObject*, UObject*>& InReplacementMap);` — Called when the engine replaces an object. A common example is when a BP Component is destroyed, and replaced
- L260 _public prototype_ `void OnActorReplaced(AActor* InOldActor, AActor* InNewActor);` — Called when the engine replaces an Actor
- L263 _public prototype_ `void SetOutlinerModified();` — Marks the Outliner dirty. This triggers IAvaOutlinerProvider::OnOutlinerModified on next tick
- L265 _public prototype_ `void QueueActorHierarchyChange(AActor* InActor, const AActor* InParentActor, EAvaOutlinerHierarchyChangeType InChangeType);`
- L269 _private prototype_ `void BindWorldDelegates(UWorld* InWorld);` — Binds a given worlds delegates to the outliner, unbinding the previous bound world's
- L271 _private prototype_ `void UnbindWorldDelegates();` — Unbinds the last bound world's delegates from outliner
- L273 _private prototype_ `void AddItem(const FAvaOutlinerItemPtr& InItem);`
- L274 _private prototype_ `void RemoveItem(const FAvaOutlinerItemId& InItemId);`
- L275 _private prototype_ `void ForEachItem(TFunctionRef<void(const FAvaOutlinerItemPtr&)> InFunc);`
- L278 _private member_ `IAvaOutlinerProvider& OutlinerProvider;` — Interface providing the Outliner with logic such as Actor Duplication, Mode Tools, and extensibility options
- L281 _private member_ `TWeakPtr<FUICommandList> BaseCommandListWeak;` — the base command list gotten from the outliner provider to append our command list to
- L284 _private member_ `TWeakObjectPtr<UWorld> BoundWorldWeak;` — Latest world with bound delegates.
- L287 _private member_ `TMap<FAvaOutlinerItemId, FAvaOutlinerItemPtr> ItemMap;` — the map of the registered items
- L289 _private member_ `TMap<FAvaOutlinerItemId, FAvaOutlinerItemPtr> ItemsPendingAdd;`
- L291 _private member_ `TSet<FAvaOutlinerItemId> ItemsPendingRemove;`
- L294 _private member_ `TMap<TWeakObjectPtr<AActor>, TArray<TWeakObjectPtr<AActor>>> SceneOutlinerParentMap;` — Map of an Actor to its Child Actors defined as such via AActor::GetSceneOutlinerParent
- L297 _private member_ `TSharedRef<FAvaOutlinerTreeRoot> RootItem;` — The root of all the items in the outliner
- L300 _private member_ `FAvaOutlinerItemProxyRegistry ItemProxyRegistry;` — Outliner's Item Proxy Factory Registry Instance. This takes precedence over the Module's Factory Registry
- L303 _private member_ `TArray<TSharedPtr<IAvaOutlinerAction>> PendingActions;` — the current pending actions before refresh is called
- L306 _private member_ `TSharedPtr<TArray<TWeakObjectPtr<UObject>>> ObjectsLastSelected;` — the list of objects pending selection processing. filled in when getting notifies from the USelection instances
- L309 _private member_ `TSharedRef<FAvaOutlinerSaveState> SaveState;` — the save state object to help serialize the outliner state
- L312 _private member_ `TMap<int32, TSharedPtr<FAvaOutlinerView>> OutlinerViews;` — the map of registered outliner views
- L315 _private member_ `TArray<int32> RecentOutlinerViews;` — List of Outliner View Ids in order from least recent to most recent (i.e. Index 0 is least recent)
- L323 _private member_ `TArray<FActorHierarchyChange> QueuedActorHierarchyChanges;`
- L326 _private member_ `EAvaOutlinerIgnoreNotifyFlags IgnoreNotifyFlags = EAvaOutlinerIgnoreNotifyFlags::None;` — the current events to ignore and not handle automatically
- L329 _private member_ `bool bOutlinerDirty = false;` — Flag indicating whether the Outliner has been changed this tick and should call IAvaOutlinerProvider::OnOutlinerModified next tick
- L332 _private member_ `bool bRefreshing = false;` — Flag indicating Refreshing is taking place
- L335 _private member_ `bool bRefreshRequested = false;` — Flag indicating that a refresh must take place next tick
- L338 _private member_ `bool bIteratingItemMap = false;` — Flag indicating that the Item Map is iterating

#### struct `FAvaOutliner::FActorHierarchyChange`  
`struct FActorHierarchyChange`  
_L317-322_
- L319 _public member_ `TWeakObjectPtr<AActor> ActorWeak;`
- L320 _public member_ `TWeakObjectPtr<const AActor> ParentWeak;`
- L321 _public member_ `EAvaOutlinerHierarchyChangeType ChangeType;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/AvaOutlinerCommands.h` (Private)


#### class `FAvaOutlinerCommands`  
`class FAvaOutlinerCommands : public TCommands<FAvaOutlinerCommands>`  
_L10-51_
- inherits: `TCommands<FAvaOutlinerCommands>`
- L14 _public function_ `FAvaOutlinerCommands() : TCommands<FAvaOutlinerCommands>(TEXT("AvaOutliner") , LOCTEXT("MotionDesignOutliner", "Motion Design Outliner") , NAME_None , FAppStyle::GetAppStyleSetName())`
- L22 _public prototype_ `virtual void RegisterCommands() override;`
- L24 _public member_ `TSharedPtr<FUICommandInfo> Refresh;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> SelectAllChildren;`
- L28 _public member_ `TSharedPtr<FUICommandInfo> SelectImmediateChildren;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> SelectParent;`
- L32 _public member_ `TSharedPtr<FUICommandInfo> SelectFirstChild;`
- L34 _public member_ `TSharedPtr<FUICommandInfo> SelectPreviousSibling;`
- L36 _public member_ `TSharedPtr<FUICommandInfo> SelectNextSibling;`
- L38 _public member_ `TSharedPtr<FUICommandInfo> ExpandAll;`
- L40 _public member_ `TSharedPtr<FUICommandInfo> CollapseAll;`
- L42 _public member_ `TSharedPtr<FUICommandInfo> ExpandSelection;`
- L44 _public member_ `TSharedPtr<FUICommandInfo> CollapseSelection;`
- L46 _public member_ `TSharedPtr<FUICommandInfo> ScrollNextSelectionIntoView;`
- L48 _public member_ `TSharedPtr<FUICommandInfo> ToggleMutedHierarchy;`
- L50 _public member_ `TSharedPtr<FUICommandInfo> ToggleAutoExpandToSelection;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define LOCTEXT_NAMESPACE "AvaOutlinerCommands"`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/AvaOutlinerModule.h` (Private)


#### class `FAvaOutlinerModule`  
`class FAvaOutlinerModule : public IAvaOutlinerModule`  
_L12-165_
- inherits: `IAvaOutlinerModule`
- L15 _public function_ `static FAvaOutlinerModule& Get()`
- L21 _public prototype_ `virtual void StartupModule() override;`
- L22 _public prototype_ `virtual void ShutdownModule() override;`
- L26 _public function_ `virtual FOnExtendOutlinerToolMenu& GetOnExtendOutlinerItemContextMenu() override`
- L27 _public function_ `virtual FAvaOutlinerItemProxyRegistry& GetItemProxyRegistry() override`
- L28 _public function_ `virtual FOnExtendItemProxiesForItem& GetOnExtendItemProxiesForItem() override`
- L39 _public function_ `void RegisterFilterExpressionFactory(InArgsType&&... InArgs)`
- L52 _public function_ `void RegisterFilterSuggestionFactory(InArgsType&&... InArgs)`
- L63 _public prototype_ `bool CanFilterSupportComparisonOperation(const FName& InFilterKey, const ETextFilterComparisonOperation InOperation) const;` — Check if current filter expression factory support the comparison operation @param InFilterKey Filter key to get the filter expression factory needed @param InOperation Operation to check if supported @return True if operation is supported, False otherwise
- L72 _public prototype_ `bool FilterExpression(const FName& InFilterKey, const IAvaOutlinerItem& InItem, const FAvaTextFilterArgs& InArgs) const;` — Evaluate the expression and return the result @param InFilterKey Filter Key to get the Factory @param InItem Item that is currently checked @param InArgs Args to evaluate the expression see FAvaTextFilterArgs for more information @return True if the expression evaluated to True, False otherwise
- L79 _public prototype_ `TArray<TSharedPtr<IAvaFilterSuggestionFactory>> GetSuggestions(const EAvaFilterSuggestionType& InSuggestionType) const;` — Get all suggestions with the given type (Generic/ItemBased/All) @param InSuggestionType Type of suggestion to get, see EFilterSuggestionType for more information @return An Array containing all suggestions of the given type
- L86 _public prototype_ `FSlateIcon FindOverrideIcon(TSharedPtr<const FAvaOutlinerItem> InItem) const;` — Get the custom icon for the item if a customization for it exist @param InItem The item to search the icon for @return The custom icon for the item if a customization is found, FSlateIcon() otherwise
- L90 _protected prototype_ `virtual void UnregisterOverriddenIcon_Internal(const FAvaTypeId& InItemTypeId, const FName& InSpecializationIdentifier) override;`
- L91 _protected prototype_ `virtual void RegisterOverridenIcon_Internal(const FAvaTypeId& InItemTypeId, const TSharedRef<IAvaOutlinerIconCustomization>& InAvaOutlinerIconCustomization) override;`
- L99 _private prototype_ `void RegisterFilterExpressionFactory_Internal(const TSharedRef<IAvaFilterExpressionFactory>& InFilterExpressionFactory);` — Adds the given factory to the Map containing all of them if not already added. @param InFilterExpressionFactory Filter expression factory to register.
- L105 _private prototype_ `void RegisterFilterSuggestionFactory_Internal(const TSharedRef<IAvaFilterSuggestionFactory>& InFilterSuggestionFactory) ;` — Adds the given factory to the Map containing all of them if not already added. @param InFilterSuggestionFactory Filter suggestion factory to register.
- L112 _private prototype_ `TSharedPtr<IAvaOutlinerIconCustomization> GetCustomizationForItem(const TSharedPtr<const FAvaOutlinerItem>& InItem) const;` — Get the customization for the given item if any @param InItem Item to search the customization for @return The customization for the item if any, nullptr otherwise
- L117 _private prototype_ `void RegisterFilterExpressionFactories();` — Registers default filter expression factories.
- L122 _private prototype_ `void RegisterFilterSuggestionFactories();` — Registers default filter suggestion factories.
- L125 _private member_ `FOnExtendOutlinerToolMenu OnExtendOutlinerItemContextMenu;` — Delegate to extend the Item Context Menu
- L128 _private member_ `FOnExtendItemProxiesForItem OnGetItemProxiesForItem;` — Delegate to add in Item Proxies for a given Item / Item Type
- L131 _private member_ `FAvaOutlinerItemProxyRegistry ItemProxyRegistry;` — Module Instance of the Item Registry
- L134 _private member_ `TMap<FName, TSharedPtr<IAvaFilterExpressionFactory>> FilterExpressionFactories;` — Holds all the FilterExpressionFactory
- L137 _private member_ `TMap<FName, TSharedPtr<IAvaFilterSuggestionFactory>> FilterSuggestionsFactories;` — Holds all the FilterSuggestionFactory
- L156 _private function_ `friend uint32 GetTypeHash(FIconCustomizationKey const& InCustomizationKey)`
- L164 _private member_ `TMap<FIconCustomizationKey, TSharedPtr<IAvaOutlinerIconCustomization>> IconRegistry;` — Holds all the IconCustomizations

#### struct `FAvaOutlinerModule::FIconCustomizationKey`  
`struct FIconCustomizationKey`  
_L142-161_
- desc: Hold the key of the map containing the IconCustomizations
- L145 _public member_ `FAvaTypeId ItemTypeId = FAvaTypeId::Invalid();` — OutlinerClass FName (ex. AvaOutlinerItem)
- L148 _public member_ `FName CustomizationSpecializationIdentifier;` — Specialization identifier (ex. AvaShapeActor class FName for ActorIcon customization)
- L150 _public function_ `bool operator==(const FIconCustomizationKey& InOther) const`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/AvaOutlinerSettings.h` (Private)


#### class `UAvaOutlinerSettings`  
`class UAvaOutlinerSettings : public UDeveloperSettings`  
_L10-79_
- reflection: `UCLASS(config=EditorPerProjectUserSettings, meta=(DisplayName="Outliner"))`
- inherits: `UDeveloperSettings`
- L15 _public prototype_ `UAvaOutlinerSettings();`
- L17 _public prototype_ `static UAvaOutlinerSettings* Get();`
- L19 _public function_ `const TMap<FName, FLinearColor>& GetColorMap() const`
- L21 _public prototype_ `static FName GetCustomItemTypeFiltersName();`
- L23 _public function_ `const TMap<FName, FAvaOutlinerItemTypeFilterData>& GetCustomItemTypeFilters() const`
- L25 _public prototype_ `bool AddCustomItemTypeFilter(FName InKey, FAvaOutlinerItemTypeFilterData& InFilter);`
- L27 _public function_ `bool ShouldUseMutedHierarchy() const`
- L29 _public function_ `bool ShouldAutoExpandToSelection() const`
- L31 _public function_ `bool ShouldAlwaysShowVisibilityState() const`
- L33 _public function_ `bool ShouldAlwaysShowLockState() const`
- L35 _public function_ `EAvaOutlinerItemViewMode GetItemDefaultViewMode() const`
- L37 _public function_ `EAvaOutlinerItemViewMode GetItemProxyViewMode() const`
- L40 _private prototype_ `virtual void PostInitProperties() override;`
- L42 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L48 _private prototype_ `void HideItemColorMapAlphaChannel() const;` — Hides the Alpha Channel for the Value Color Property in ItemColorMap this has to be done manually as putting in meta=(HideAlphaChannel) in a map doesn't apply to the Value Property
- L51 _private member_ `TMap<FName, FLinearColor> ItemColorMap;` — `UPROPERTY(Config, EditAnywhere, Category = "Color")`
- L54 _private member_ `TMap<FName, FAvaOutlinerItemTypeFilterData> CustomItemTypeFilters;` — `UPROPERTY(Config, EditAnywhere, Category = "Filters")`
- L58 _private member_ `bool bAlwaysShowVisibilityState = false;` — `UPROPERTY(Config, EditAnywhere, Category = "Editor UX")` — Whether to show the visibility state always, rather than only showing when the item is hidden or hovered
- L62 _private member_ `bool bAlwaysShowLockState = false;` — `UPROPERTY(Config, EditAnywhere, Category = "Editor UX")` — Whether to show the lock state always, rather than only showing when the item is locked or hovered
- L66 _private member_ `bool bUseMutedHierarchy = true;` — `UPROPERTY(Config, EditAnywhere, Category = "Initial Values")` — Whether to show the parent of the shown items, even if the parents are filtered out
- L70 _private member_ `bool bAutoExpandToSelection = true;` — `UPROPERTY(Config, EditAnywhere, Category = "Initial Values")` — Whether to auto expand the hierarchy to show the item when selected
- L74 _private member_ `int32 ItemDefaultViewMode;` — `UPROPERTY(Config, EditAnywhere, Category = "Initial Values", meta=(Bitmask, BitmaskEnum="/Script/AvalancheOutliner.EAvaOutlinerItemViewMode"))` — The View Mode a Non-Actor / Non-Component Item supports by default
- L78 _private member_ `int32 ItemProxyViewMode;` — `UPROPERTY(Config, EditAnywhere, Category = "Initial Values", meta=(Bitmask, BitmaskEnum="/Script/AvalancheOutliner.EAvaOutlinerItemViewMode"))` — The View Mode a Proxy Item supports by default

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/AvaOutlinerStyle.h` (Private)


#### class `FAvaOutlinerStyle`  
`class FAvaOutlinerStyle final : public FSlateStyleSet`  
_L7-18_
- inherits: `FSlateStyleSet`
- L10 _public function_ `static FAvaOutlinerStyle& Get()`
- L16 _public prototype_ `FAvaOutlinerStyle();`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/AvaOutlinerView.h` (Private)


#### class `FAvaOutlinerView`  
`class FAvaOutlinerView : public IAvaOutlinerView`  
_L32-506_
- inherits: `IAvaOutlinerView`
- desc: A view instance of the Outliner, that handles viewing a subset of the outliner items based on item filters, search text, hierarchy type, etc
- L39 _private prototype_ `void Init(const TSharedRef<FAvaOutliner>& InOutliner, bool bCreateOutlinerWidget);` — Initializes the Outliner Instance. Only executed once
- L42 _private prototype_ `void CreateColumns();` — Creates the Base Columns and any other columns gotten via the Module or Provider
- L45 _public prototype_ `explicit FAvaOutlinerView(FPrivateToken);`
- L50 _public prototype_ `static FName GetOutlinerToolbarName();` — Gets the Tool Menu name for the ToolBar in each Outliner View Widget
- L53 _public prototype_ `static FName GetOutlinerItemContextMenuName();` — Gets the Tool Menu name for the Item Context Menu
- L61 _public prototype_ `static TSharedRef<FAvaOutlinerView> CreateInstance(int32 InOutlinerViewId , const TSharedRef<FAvaOutliner>& InOutliner , bool bCreateOutlinerWidget);` — Creates an Outliner View Instance and register it to the Outliner @param InOutlinerViewId the Id assigned to the Instance created @param InOutliner the Outliner this Instance View belongs to @param bCreateOutlinerWidget whether to create an SAvaOutliner to this view. Can be false if used for testing
- L65 _public prototype_ `void PostLoad();`
- L68 _public prototype_ `void OnOutlinerSettingsChanged(UObject* InObject, FPropertyChangedEvent& InPropertyChangedEvent);` — Called when the UAvaOutlinerSettings has a property change
- L74 _public prototype_ `void UpdateCustomFilters();` — Retrieves the latest list of Custom Filters specified in UAvaOutlinerSettings and recreates the filter instances for these
- L76 _public function_ `DECLARE_MULTICAST_DELEGATE(FOnCustomFiltersChanged) FOnCustomFiltersChanged& GetOnCustomFiltersChanged()`
- L79 _public prototype_ `void Tick(float InDeltaTime);`
- L85 _public prototype_ `void SaveState();` — Saves the Outliner View Data into the Save State object in FAvaOutliner @see FAvaOutlinerSaveState::SaveOutlinerViewState
- L91 _public prototype_ `void LoadState();` — Loads the data found in the FAvaOutliner's SaveState into the respective properties in this View @see FAvaOutlinerSaveState::LoadOutlinerViewState
- L93 _public prototype_ `void BindCommands(const TSharedPtr<FUICommandList>& InBaseCommandList);`
- L95 _public prototype_ `TSharedPtr<FUICommandList> GetBaseCommandList() const;`
- L97 _public function_ `TSharedPtr<FUICommandList> GetViewCommandList() const`
- L100 _public prototype_ `void UpdateRecentOutlinerViews();` — Notifies FAvaOutliner so that this view instance becomes the most recent interacted outliner view
- L103 _public prototype_ `bool IsMostRecentOutlinerView() const;` — Returns whether this view instance is the most recently interacted between the instances in FAvaOutliner
- L105 _public function_ `int32 GetOutlinerViewId() const`
- L107 _public function_ `TSharedPtr<FAvaOutliner> GetOutliner() const`
- L109 _public function_ `TSharedRef<FAvaOutlinerStats> GetOutlinerStats() const`
- L112 _public prototype_ `virtual TSharedRef<SWidget> GetOutlinerWidget() const override;`
- L113 _public prototype_ `virtual TSharedPtr<IAvaOutliner> GetOwnerOutliner() const override;`
- L116 _public prototype_ `void CreateToolbar();`
- L118 _public prototype_ `TSharedPtr<SWidget> CreateItemContextMenu();`
- L120 _public prototype_ `TSharedRef<SWidget> CreateOutlinerSettingsMenu();`
- L122 _public prototype_ `TSharedRef<SWidget> CreateOutlinerViewOptionsMenu();`
- L125 _public function_ `const TMap<FName, TSharedPtr<IAvaOutlinerColumn>>& GetColumns() const` — Get the Columns currently allocated in this Outliner Instance
- L128 _public prototype_ `bool ShouldShowColumnByDefault(const TSharedPtr<IAvaOutlinerColumn>& InColumn) const;` — Whether the given column should be shown by default. This is only used at the start when Creating the Columns
- L131 _public prototype_ `void UpdateColumnVisibilityMap();` — Updates the Cached Column Visibility Map to the latest current state of this View's Widget Columns
- L134 _public prototype_ `void RequestRefresh();` — Marks the Outliner View to be refreshed on Next Tick
- L136 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnOutlinerViewRefreshed);`
- L137 _public function_ `FOnOutlinerViewRefreshed& GetOnOutlinerViewRefreshed()`
- L140 _public prototype_ `void Refresh();` — Refreshes the Items visible in this View, and refreshes the Outliner Widget if it was created
- L142 _public prototype_ `void SetKeyboardFocus();`
- L145 _public prototype_ `void UpdateRootVisibleItems();` — Refreshes the Items that will be at the Top Level of the Tree (e.g. Actors with no parent item)
- L148 _public prototype_ `void UpdateItemExpansions();` — Updates the Item Expansions in the Tree Widget based on whether the Items have the Expanded flag or not
- L151 _public prototype_ `void NotifyObjectsReplaced();` — Called when Object Replacement has taken place. Used to invalidate the widget for painting
- L154 _public prototype_ `void OnFilterChanged();` — Called when the Text Filter has changed and thus needing to refresh to visualize the new filtered items
- L157 _public prototype_ `FAvaOutlinerItemPtr GetRootItem() const;` — The Root Item of the Tree. Convenience function to get the RootItem from FAvaOutliner
- L160 _public function_ `const TArray<FAvaOutlinerItemPtr>& GetRootVisibleItems() const` — Gets the Top Level Items that should be visible in the Tree. This can differ between views depending on Filters and other factors
- L162 _public prototype_ `void SetViewItemFlags(const FAvaOutlinerItemPtr& InItem, EAvaOutlinerItemFlags InFlags);`
- L164 _public prototype_ `EAvaOutlinerItemFlags GetViewItemFlags(const FAvaOutlinerItemPtr& InItem) const;`
- L166 _public prototype_ `void GetChildrenOfItem(FAvaOutlinerItemPtr InItem, TArray<FAvaOutlinerItemPtr>& OutChildren) const;`
- L175 _public prototype_ `void GetChildrenOfItem(FAvaOutlinerItemPtr InItem , TArray<FAvaOutlinerItemPtr>& OutChildren , EAvaOutlinerItemViewMode InViewMode , const TSet<FAvaOutlinerItemPtr>& InRecursionDisallowedItems) const;` — Gets the Children of a given Item. Can recurse if the immediate child is hidden (the children of these hidden items should still be given the opportunity to show up) @param InItem the Item to get the children of @param OutChildren the visible children in the give view mode. @param InViewMode the view mode(s) that the children should support to be added to OutChildren @param InRecursionDisallowedItems the items where recursion should not be performed
- L180 _public prototype_ `FLinearColor GetItemBrushColor(FAvaOutlinerItemPtr InItem) const;`
- L182 _public function_ `const TArray<TSharedPtr<IAvaOutlinerItemFilter>>& GetItemFilters() const`
- L184 _public function_ `const TArray<TSharedPtr<IAvaOutlinerItemFilter>>& GetCustomItemFilters() const`
- L186 _public function_ `const TSet<TSharedPtr<IAvaOutlinerItemFilter>>& GetActiveItemFilters() const`
- L188 _public function_ `TSharedRef<FAvaOutlinerTextFilter> GetTextFilter() const`
- L191 _public prototype_ `TArray<FAvaOutlinerItemPtr> GetViewSelectedItems() const;` — Gets the Currently Selected Items in the Tree View
- L194 _public prototype_ `int32 GetViewSelectedItemCount() const;` — Gets the Currently Selected Item Count in the Tree View
- L197 _public prototype_ `int32 CalculateVisibleItemCount() const;` — Calculates the amount of Items that are visible in this Outliner View
- L200 _public prototype_ `void SelectItems(TArray<FAvaOutlinerItemPtr> InItems, EAvaOutlinerItemSelectionFlags InFlags = EAvaOutlinerItemSelectionFlags::SignalSelectionChange);` — Selects the Item in this Outliner View
- L203 _public prototype_ `void ClearItemSelection(bool bSignalSelectionChange = true);` — Clears the currently Selected Items in the Outliner View
- L206 _public function_ `bool IsSyncingItemSelection() const` — Whether Sync Selection is currently taking place
- L210 _private prototype_ `void SetItemSelectionImpl(TArray<FAvaOutlinerItemPtr>&& InItems , bool bSignalSelectionChange);` — Sets the Selected Items to be the given Items in this List.
- L215 _public prototype_ `void NotifyItemSelectionChanged(const TArray<FAvaOutlinerItemPtr>& InSelectedItems , const FAvaOutlinerItemPtr& InItem , bool bUpdateModeTools);` — Called when Item selection has changed. This can be called by the OutlinerWidget or by the View itself if there's no OutlinerWidget
- L220 _public prototype_ `bool IsItemReadOnly(const FAvaOutlinerItemPtr& InItem) const;` — Whether the given Item is explicitly marked as Read-only in the Outliner
- L223 _public prototype_ `bool CanSelectItem(const FAvaOutlinerItemPtr& InItem) const;` — Whether the given Item can be selected in this Outliner View / Widget
- L226 _public prototype_ `bool IsItemSelected(const FAvaOutlinerItemPtr& InItem) const;` — Whether the current item is selected in this Outliner View / Widget
- L229 _public prototype_ `void SetParentItemExpansions(const FAvaOutlinerItemPtr& InItem, bool bIsExpanded);` — Change the expansion state of the parents (recursively) of the given item
- L232 _public prototype_ `void SetItemExpansion(const FAvaOutlinerItemPtr& InItem, bool bIsExpanded, bool bInUseFilter = true);` — Expands / Collapses the given Item
- L235 _public prototype_ `void SetItemExpansionRecursive(FAvaOutlinerItemPtr InItem, bool bIsExpanded);` — Expands / Collapses the given Item and its children recursively
- L238 _public prototype_ `void OnItemExpansionChanged(FAvaOutlinerItemPtr InItem, bool bIsExpanded);` — Called when the given item's expansion state (expanded/collapsed) has changed
- L241 _public prototype_ `bool ShouldShowItem(const FAvaOutlinerItemPtr& InItem, bool bInUseFilters, EAvaOutlinerItemViewMode InViewMode) const;` — Return whether the given item should be visible in this Outliner Instance
- L244 _public prototype_ `int32 GetVisibleChildIndex(const FAvaOutlinerItemPtr& InParentItem, const FAvaOutlinerItemPtr& InChildItem) const;` — Returns the Index of the Child from the Parent's Children Visible List (Visible List can vary between Outliner Instances)
- L247 _public prototype_ `FAvaOutlinerItemPtr GetVisibleChildAt(const FAvaOutlinerItemPtr& InParentItem, int32 InChildIndex) const;` — Returns the Child from the Parent's Children Visible List at the given Index (Visible List can vary between Outliner Instances)
- L250 _public prototype_ `bool IsOutlinerLocked() const;` — Returns whether the Outliner is Locked. See FAvaOutliner::IsOutlinerLocked
- L257 _public prototype_ `void EnableItemFilter(const TSharedPtr<IAvaOutlinerItemFilter>& InFilter, const bool bInRefreshOutliner = true);` — Activate the given Item Filter @param InFilter the filter to activate @param bInRefreshOutliner whether to refresh this view if the filter was added. false recommended if doing operations in bulk
- L264 _public prototype_ `void EnableItemFilterById(const FName& InFilterId, const bool bInRefreshOutliner = true);` — Activate the Item Filter with the given ID @param InFilterId the filter id associated with the Filter to activate @param bInRefreshOutliner whether to refresh this view if the filter was added. false recommended if doing operations in bulk
- L271 _public prototype_ `void DisableItemFilter(const TSharedPtr<IAvaOutlinerItemFilter>& InFilter, const bool bInRefreshOutliner = true);` — Deactivates the given Item Filter @param InFilter the filter to remove from the active filter list @param bInRefreshOutliner whether to refresh this view if the filter was removed. false recommended if doing operations in bulk
- L274 _public prototype_ `bool IsItemFilterEnabled(const TSharedPtr<IAvaOutlinerItemFilter>& InFilter) const;` — Whether the given Filter is in the Active Filter List
- L277 _public prototype_ `void SetSearchText(const FText& InText);` — Sets the Filter Text
- L280 _public prototype_ `FText GetSearchText() const;` — Gets the Current Filter Text
- L282 _public function_ `EAvaOutlinerItemViewMode GetItemDefaultViewMode() const`
- L283 _public function_ `EAvaOutlinerItemViewMode GetItemProxyViewMode() const`
- L285 _public prototype_ `void ToggleViewModeSupport(EAvaOutlinerItemViewMode& InOutViewMode, EAvaOutlinerItemViewMode InFlags);`
- L286 _public prototype_ `void ToggleItemDefaultViewModeSupport(EAvaOutlinerItemViewMode InFlags);`
- L287 _public prototype_ `void ToggleItemProxyViewModeSupport(EAvaOutlinerItemViewMode InFlags);`
- L289 _public prototype_ `ECheckBoxState GetViewModeCheckState(EAvaOutlinerItemViewMode InViewMode, EAvaOutlinerItemViewMode InFlags) const;`
- L290 _public prototype_ `ECheckBoxState GetItemDefaultViewModeCheckState(EAvaOutlinerItemViewMode InFlags) const;`
- L291 _public prototype_ `ECheckBoxState GetItemProxyViewModeCheckState(EAvaOutlinerItemViewMode InFlags) const;`
- L297 _public prototype_ `void ToggleMutedHierarchy();` — Action to turn Muted Hierarchy on or off @see bUseMutedHierarchy
- L298 _public function_ `bool CanToggleMutedHierarchy() const`
- L299 _public function_ `bool IsMutedHierarchyActive() const`
- L305 _public prototype_ `void ToggleAutoExpandToSelection();` — Action to turn Auto Expand to Selection on or off @see bAutoExpandToSelection
- L306 _public function_ `bool CanToggleAutoExpandToSelection() const`
- L307 _public function_ `bool ShouldAutoExpandToSelection() const`
- L309 _public prototype_ `void ToggleShowItemFilters();`
- L310 _public function_ `bool CanToggleShowItemFilters() const`
- L311 _public function_ `bool ShouldShowItemFilters() const`
- L314 _public prototype_ `void SetItemTypeHidden(FName InItemTypeName, bool bHidden);` — Sets whether the given item type should be hidden or not
- L317 _public prototype_ `void ToggleHideItemTypes(FName InItemTypeName);` — Toggles the given Item Types to Hide/Show
- L318 _public prototype_ `ECheckBoxState GetToggleHideItemTypesState(FName InItemTypeName) const;`
- L322 _public function_ `template<typename InItemType, typename = typename TEnableIf<TIsDerivedFrom<InItemType, IAvaOutlinerItem>::IsDerived>::Type> void HideItemType()` — Hides the given Outliner Item Type from showing in this Outliner View (e.g. Hide Components is used)
- L329 _public function_ `template<typename InItemType, typename = typename TEnableIf<TIsDerivedFrom<InItemType, IAvaOutlinerItem>::IsDerived>::Type> void ExposeItemType()` — Shows the given Outliner Item Type if it was hidden in this Outliner View (e.g. Showing Components again)
- L335 _public prototype_ `bool IsItemTypeHidden(FName InItemTypeName) const;` — Whether the given Outliner Item Type is currently hidden in this Outliner View
- L336 _public prototype_ `bool IsItemTypeHidden(const FAvaOutlinerItemPtr& InItem) const;`
- L339 _public function_ `template<typename InItemType, typename = typename TEnableIf<TIsDerivedFrom<InItemType, IAvaOutlinerItem>::IsDerived>::Type> bool IsItemTypeHidden() const`
- L345 _public prototype_ `void OnDragEnter(const FDragDropEvent& InDragDropEvent, FAvaOutlinerItemPtr InTargetItem);` — Called when a Drag enters the Outliner Widgets for the given Item (if null, treat as root)
- L348 _public prototype_ `void OnDragLeave(const FDragDropEvent& InDragDropEvent, FAvaOutlinerItemPtr InTargetItem);` — Called when a Drag leaves the Outliner Widgets for the given Item (if null, treat as root)
- L351 _public prototype_ `FReply OnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, FAvaOutlinerItemPtr InTargetItem);` — Called a Drag is attempted for the selected items in view
- L354 _public prototype_ `FReply OnDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone, FAvaOutlinerItemPtr InTargetItem);` — Processes the Drag and Drop for the given Item if valid, else it will process it for the Root Item
- L357 _public prototype_ `TOptional<EItemDropZone> OnCanDrop(const FDragDropEvent& InDragDropEvent , EItemDropZone InDropZone , FAvaOutlinerItemPtr InTargetItem) const;` — Determines whether the Drag and Drop can be processed by the given item
- L362 _public prototype_ `void SetDragIntoTreeRoot(bool bInIsDraggingIntoTreeRoot);` — Called when there's a Drag being started/ended to the Outliner Widget as a whole (i.e. root) and not an individual item
- L364 _public prototype_ `void RenameSelected();`
- L365 _public prototype_ `void ResetRenaming();`
- L366 _public prototype_ `void OnItemRenameAction(EAvaOutlinerRenameAction InRenameAction, const TSharedPtr<FAvaOutlinerView>& InOutlinerView);`
- L367 _public prototype_ `bool CanRenameSelected() const;`
- L369 _public prototype_ `void DeleteSelected();`
- L370 _public prototype_ `bool CanDeleteSelected() const;`
- L372 _public prototype_ `void DuplicateSelected();`
- L373 _public prototype_ `bool CanDuplicateSelected() const;`
- L375 _public prototype_ `void SelectChildren(bool bIsRecursive);`
- L376 _public prototype_ `bool CanSelectChildren() const;`
- L378 _public prototype_ `void SelectParent();`
- L379 _public prototype_ `bool CanSelectParent() const;`
- L381 _public prototype_ `void SelectFirstChild();`
- L382 _public prototype_ `bool CanSelectFirstChild() const;`
- L384 _public prototype_ `void SelectSibling(int32 InDeltaIndex);`
- L385 _public prototype_ `bool CanSelectSibling() const;`
- L387 _public prototype_ `void ExpandAll();`
- L388 _public prototype_ `bool CanExpandAll() const;`
- L390 _public prototype_ `void CollapseAll();`
- L391 _public prototype_ `bool CanCollapseAll() const;`
- L393 _public prototype_ `void ScrollNextIntoView();`
- L394 _public prototype_ `void ScrollPrevIntoView();`
- L395 _public prototype_ `bool CanScrollNextIntoView() const;`
- L396 _public prototype_ `void ScrollDeltaIndexIntoView(int32 DeltaIndex);`
- L397 _public prototype_ `void ScrollItemIntoView(const FAvaOutlinerItemPtr& InItem);`
- L400 _public prototype_ `void SortAndSelectItems(TArray<FAvaOutlinerItemPtr> InItemsToSelect);` — Sorts the given Items in the user-defined order and selects them, and if the Widget is valid focusing to the item in the Widget
- L404 _private prototype_ `static void PopulateItemContextMenu(UToolMenu* InToolMenu);` — Static Function to Populate the Outliner Item Context Menu. The Outliner View and Context Items are gotten via UAvaOutlinerItemsContext
- L407 _private prototype_ `static void PopulateToolBar(UToolMenu* InToolMenu);` — Static Function to Populate the Outliner Main Toolbar. The Outliner View is gotten via UAvaOutlinerToolbarContext
- L410 _private prototype_ `void RefreshOutliner(bool bInImmediateRefresh);` — Triggers a Refresh on the FAvaOutliner
- L413 _private member_ `int32 OutlinerViewId = -1;` — Local Identifier of this Instance
- L416 _private member_ `TWeakPtr<FAvaOutliner> OutlinerWeak;` — Weak pointer to the outliner this is a view of
- L419 _private member_ `TSharedPtr<SBorder> OutlinerWidgetContainer;` — Widget wrapping the outliner widget. Used so that the outliner widget's lifetime can be controlled by this container
- L422 _private member_ `TSharedPtr<SAvaOutliner> OutlinerWidget;` — Widget showing the View. Can be null if instanced for testing (i.e. bCreateOutlinerWidget is false in Init)
- L425 _private member_ `TSharedPtr<FUICommandList> ViewCommandList;` — Command List mapped to the View to handle things like Selected Items
- L428 _private member_ `TArray<FAvaOutlinerItemPtr> RootVisibleItems;` — Root Items from Outliner visible to this Instance. i.e. a Subset of all the Items in FAvaOutliner
- L431 _private member_ `TArray<FAvaOutlinerItemPtr> SelectedItems;` — A list of the Selected Items in this Outliner View
- L434 _private member_ `mutable TSet<FAvaOutlinerItemPtr> ReadOnlyItems;` — Set of Items that are Currently Read Only in this Instance. Mutable as this changes on GetChildrenOfItem const func
- L437 _private member_ `TMap<FAvaOutlinerItemId, EAvaOutlinerItemFlags> ViewItemFlags;` — Items specific to this Outliner Instance, rather than being shared across Outliners (e.g. Expansion flags)
- L439 _private member_ `TSharedRef<FAvaOutlinerTextFilter> TextFilter;`
- L442 _private member_ `TArray<TSharedPtr<IAvaOutlinerItemFilter>> ItemFilters;` — Native-constructed Item Filters in the Outliner
- L445 _private member_ `TArray<TSharedPtr<IAvaOutlinerItemFilter>> CustomItemFilters;` — Custom Item Filters constructed from UAvaOutlinerSettings
- L448 _private member_ `FOnCustomFiltersChanged OnCustomFiltersChanged;` — Delegate called when the Custom Item Filters have been modified, as these can be instanced after
- L451 _private member_ `FOnOutlinerViewRefreshed OnOutlinerViewRefreshed;` — Delegate called at the end of the Outliner View Refresh
- L454 _private member_ `TSet<TSharedPtr<IAvaOutlinerItemFilter>> ActiveItemFilters;` — Active Item Filters. Subset of ItemFilters
- L457 _private member_ `TMap<FName, TSharedPtr<IAvaOutlinerColumn>> Columns;` — Map of the Column Ids and the Colum with that Id. This is filled in FAvaOutlinerView::CreateColumns
- L460 _private member_ `TMap<FName, bool> ColumnVisibility;` — Map of the Column Ids to their Override (i.e. saved) Visibility
- L463 _private member_ `TSet<FName> HiddenItemTypes;` — A set of the Outliner Item Type Names that should be hidden in the Outliner
- L466 _private member_ `int32 NextSelectedItemIntoView = -1;` — The Index of the Item that will be scrolled into View
- L469 _private member_ `TArray<FAvaOutlinerItemPtr> SortedSelectedItems;` — Selected Items Sorted from Top To Bottom
- L472 _private member_ `TSharedRef<FAvaOutlinerStats> OutlinerStats;` — Stats for the Outliner Widget
- L475 _private member_ `TArray<FAvaOutlinerItemPtr> ItemsRemainingRename;` — The list of items that need renaming and are waiting for their turn to be renamed
- L478 _private member_ `FAvaOutlinerItemPtr CurrentItemRenaming;` — The current item in the process of renaming. Null if no renaming is taking place
- L481 _private member_ `EAvaOutlinerItemViewMode ItemDefaultViewMode = EAvaOutlinerItemViewMode::HorizontalItemList;` — This Outliner View's Setting for the Default Item's Default View Mode
- L484 _private member_ `EAvaOutlinerItemViewMode ItemProxyViewMode = EAvaOutlinerItemViewMode::None;` — This Outliner View's Setting for the Item Proxy's Default View Mode
- L487 _private member_ `bool bAutoExpandToSelection = false;` — Whether the expand the parents of an item when it's selected
- L490 _private member_ `bool bUseMutedHierarchy = false;` — Whether to also show the Parent Items in read-only mode when these are filtered out
- L493 _private member_ `bool bRefreshRequested = false;` — Flag to call FAvaOutlinerView::Refresh next tick
- L496 _private member_ `bool bRenamingItems = false;` — Whether Item renaming is taking place in this View
- L499 _private member_ `bool bRequestedRename = false;` — Whether Renaming Items should be processed next tick
- L502 _private member_ `bool bSyncingItemSelection = false;` — Whether Items are currently being synced to what the Widget or Interface sent. Used as a re-enter guard
- L505 _private member_ `bool bShowItemFilters = false;` — Flag used for the Outliner Widget to determine if the Item Filter Bar should open and show the Item Filters

#### struct `FAvaOutlinerView::FPrivateToken`  
`struct FPrivateToken`  
_L36-36_
- L36 _public prototype_ `struct FPrivateToken`

#### Free symbols / members of external scopes

- L76 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnCustomFiltersChanged) FOnCustomFiltersChanged& GetOnCustomFiltersChanged() { return OnCustomFiltersChanged; } void Tick(float InDeltaTime);`
- L136 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnOutlinerViewRefreshed);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/Clipboard/AvaOutlinerClipboardData.h` (Private)


#### class `UAvaOutlinerClipboardData`  
`class UAvaOutlinerClipboardData : public UObject`  
_L12-20_
- reflection: `UCLASS()`
- inherits: `UObject`
- L19 _public member_ `TArray<FName> ActorNames;` — `UPROPERTY()` — Copied Actor names in the order that they should be processed by Outliner

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/Clipboard/AvaOutlinerExporter.h` (Private)


#### class `FAvaOutlinerExporter`  
`class FAvaOutlinerExporter`  
_L14-25_
- desc: Handles exporting the given Copied Actors' Outliner Data to String Text
- L17 _public prototype_ `explicit FAvaOutlinerExporter(const TSharedRef<FAvaOutliner>& InAvaOutliner);`
- L19 _public prototype_ `void ExportText(FString& InOutCopiedData, TConstArrayView<AActor*> InCopiedActors);`
- L22 _private prototype_ `UAvaOutlinerClipboardData* CreateClipboardData(TConstArrayView<AActor*> InCopiedActors);`
- L24 _private member_ `TWeakPtr<FAvaOutliner> AvaOutlinerWeak;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/Clipboard/AvaOutlinerImporter.h` (Private)


#### class `FAvaOutlinerImporter`  
`class FAvaOutlinerImporter`  
_L13-26_
- desc: Handles parsing String Data to import outliner data
- L16 _public prototype_ `explicit FAvaOutlinerImporter(const TSharedRef<FAvaOutliner>& InAvaOutliner);`
- L18 _public prototype_ `void ImportText(FStringView InPastedData, const TMap<FName, AActor*>& InPastedActors);`
- L21 _private prototype_ `static bool ParseCommand(const TCHAR** InStream, const TCHAR* InToken);`
- L23 _private prototype_ `TArray<FName> ImportOutlinerData(const FString& InBuffer);`
- L25 _private member_ `TWeakPtr<FAvaOutliner> AvaOutlinerWeak;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/Columns/AvaOutlinerColorColumn.h` (Private)


#### class `FAvaOutlinerColorColumn`  
`class FAvaOutlinerColorColumn : public IAvaOutlinerColumn`  
_L7-21_
- inherits: `IAvaOutlinerColumn`
- L10 _public prototype_ `UE_AVA_INHERITS(FAvaOutlinerColorColumn, IAvaOutlinerColumn);`
- L14 _protected prototype_ `virtual FText GetColumnDisplayNameText() const override;`
- L15 _protected function_ `virtual bool ShouldShowColumnByDefault() const override`
- L16 _protected prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L17 _protected prototype_ `virtual TSharedRef<SWidget> ConstructRowWidget(FAvaOutlinerItemPtr InItem , const TSharedRef<FAvaOutlinerView>& InOutlinerView , const TSharedRef<SAvaOutlinerTreeRow>& InRow) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/Columns/AvaOutlinerColumnExtender.h` (Private)


#### class `FAvaOutlinerColumnExtender`  
`class FAvaOutlinerColumnExtender`  
_L21-50_
- desc: Extension Class to add Outliner Columns Example #1: This would create a Tag Column at the end of the current column list (order matters!) ColumnExtender.AddColumn<FAvaOutlinerTagColumn>(); Example #2: This would create a Tag Column before the Label Column (if it doesn't exist, it's the same behavior as the above example) ColumnExtender.AddColumn<FAvaOutlinerTagColumn, EAvaOutlinerExtensionPosition::Before, FAvaOutlinerLabelColumn>();
- L23 _private typedef_ `using FAvaOutlinerColumnPtr = TSharedPtr<IAvaOutlinerColumn>;`
- L28 _public function_ `void AddColumn()`
- L40 _public function_ `const TArray<FAvaOutlinerColumnPtr>& GetColumns() const`
- L43 _private prototype_ `void AddColumn(FAvaOutlinerColumnPtr InColumn , EAvaOutlinerExtensionPosition InExtensionPosition , FName InReferenceColumnId);`
- L47 _private prototype_ `int32 FindColumnIndex(FName InColumnId) const;`
- L49 _private member_ `TArray<FAvaOutlinerColumnPtr> Columns;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/Columns/AvaOutlinerItemsColumn.h` (Private)


#### class `FAvaOutlinerItemsColumn`  
`class FAvaOutlinerItemsColumn : public IAvaOutlinerColumn`  
_L10-24_
- inherits: `IAvaOutlinerColumn`
- desc: Column to help visualize Child Items of a given Item when the Item is collapsed
- L13 _public prototype_ `UE_AVA_INHERITS(FAvaOutlinerItemsColumn, IAvaOutlinerColumn);`
- L17 _protected prototype_ `virtual FText GetColumnDisplayNameText() const override;`
- L18 _protected function_ `virtual bool ShouldShowColumnByDefault() const override`
- L19 _protected prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L20 _protected prototype_ `virtual TSharedRef<SWidget> ConstructRowWidget(FAvaOutlinerItemPtr InItem , const TSharedRef<FAvaOutlinerView>& InOutlinerView , const TSharedRef<SAvaOutlinerTreeRow>& InRow) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/Columns/AvaOutlinerLabelColumn.h` (Private)


#### class `FAvaOutlinerLabelColumn`  
`class FAvaOutlinerLabelColumn : public IAvaOutlinerColumn`  
_L7-20_
- inherits: `IAvaOutlinerColumn`
- L10 _public prototype_ `UE_AVA_INHERITS(FAvaOutlinerLabelColumn, IAvaOutlinerColumn);`
- L14 _protected prototype_ `virtual FText GetColumnDisplayNameText() const override;`
- L15 _protected prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L16 _protected prototype_ `virtual TSharedRef<SWidget> ConstructRowWidget(FAvaOutlinerItemPtr InItem , const TSharedRef<FAvaOutlinerView>& InOutlinerView , const TSharedRef<SAvaOutlinerTreeRow>& InRow) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/Columns/AvaOutlinerLockColumn.h` (Private)


#### class `FAvaOutlinerLockColumn`  
`class FAvaOutlinerLockColumn : public IAvaOutlinerColumn`  
_L7-21_
- inherits: `IAvaOutlinerColumn`
- L10 _public prototype_ `UE_AVA_INHERITS(FAvaOutlinerLockColumn, IAvaOutlinerColumn);`
- L14 _protected prototype_ `virtual FText GetColumnDisplayNameText() const override;`
- L15 _protected function_ `virtual bool ShouldShowColumnByDefault() const override`
- L16 _protected prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L17 _protected prototype_ `virtual TSharedRef<SWidget> ConstructRowWidget(FAvaOutlinerItemPtr InItem , const TSharedRef<FAvaOutlinerView>& InOutlinerView , const TSharedRef<SAvaOutlinerTreeRow>& InRow) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/Columns/AvaOutlinerTagColumn.h` (Private)


#### class `FAvaOutlinerTagColumn`  
`class FAvaOutlinerTagColumn : public IAvaOutlinerColumn`  
_L7-20_
- inherits: `IAvaOutlinerColumn`
- L10 _public prototype_ `UE_AVA_INHERITS(FAvaOutlinerTagColumn, IAvaOutlinerColumn);`
- L14 _protected prototype_ `virtual FText GetColumnDisplayNameText() const override;`
- L15 _protected prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L16 _protected prototype_ `virtual TSharedRef<SWidget> ConstructRowWidget(FAvaOutlinerItemPtr InItem ,const TSharedRef<FAvaOutlinerView>& InOutlinerView , const TSharedRef<SAvaOutlinerTreeRow>& InRow) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/Columns/AvaOutlinerVisibilityColumn.h` (Private)


#### struct `FAvaOutlinerVisibilityCache`  
`struct FAvaOutlinerVisibilityCache`  
_L8-33_
- desc: A struct which gets, and caches the visibility of an item
- L30 _public member_ `mutable TMap<TWeakPtr<IAvaOutlinerItem>, FVisibilityInfo> VisibilityInfo;` — Map of tree item to visibility
- L32 _public prototype_ `bool GetVisibility(EAvaOutlinerVisibilityType Type, const FAvaOutlinerItemPtr& Item) const;`

#### struct `FAvaOutlinerVisibilityCache::FVisibilityInfo`  
`struct FVisibilityInfo`  
_L10-27_
- L12 _public function_ `FVisibilityInfo(EAvaOutlinerVisibilityType Type, bool bVisible)`
- L17 _public member_ `TMap<EAvaOutlinerVisibilityType, bool> Visibility;`
- L19 _public function_ `bool GetVisibility(EAvaOutlinerVisibilityType Type) const`

#### class `FAvaOutlinerVisibilityColumn`  
`class FAvaOutlinerVisibilityColumn : public IAvaOutlinerColumn`  
_L35-56_
- inherits: `IAvaOutlinerColumn`
- L38 _public prototype_ `UE_AVA_INHERITS(FAvaOutlinerVisibilityColumn, IAvaOutlinerColumn);`
- L41 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L42 _public function_ `virtual bool ShouldShowColumnByDefault() const override`
- L43 _public prototype_ `virtual TSharedRef<SWidget> ConstructRowWidget(FAvaOutlinerItemPtr InItem , const TSharedRef<FAvaOutlinerView>& InOutlinerView , const TSharedRef<SAvaOutlinerTreeRow>& InRow) override;`
- L48 _public prototype_ `virtual bool IsItemVisible(const FAvaOutlinerItemPtr& Item);`
- L50 _public prototype_ `virtual EAvaOutlinerVisibilityType GetVisibilityType() const = 0;`
- L52 _public prototype_ `virtual void Tick(float InDeltaTime) override;`
- L55 _protected member_ `FAvaOutlinerVisibilityCache VisibilityCache;`

#### class `FAvaOutlinerEditorVisibilityColumn`  
`class FAvaOutlinerEditorVisibilityColumn : public FAvaOutlinerVisibilityColumn`  
_L58-72_
- inherits: `FAvaOutlinerVisibilityColumn`
- L61 _public prototype_ `UE_AVA_INHERITS(FAvaOutlinerEditorVisibilityColumn, FAvaOutlinerVisibilityColumn);`
- L63 _public function_ `virtual FText GetColumnDisplayNameText() const override`
- L68 _public function_ `virtual EAvaOutlinerVisibilityType GetVisibilityType() const override`

#### class `FAvaOutlinerRuntimeVisibilityColumn`  
`class FAvaOutlinerRuntimeVisibilityColumn : public FAvaOutlinerVisibilityColumn`  
_L74-88_
- inherits: `FAvaOutlinerVisibilityColumn`
- L77 _public prototype_ `UE_AVA_INHERITS(FAvaOutlinerRuntimeVisibilityColumn, FAvaOutlinerVisibilityColumn);`
- L79 _public function_ `virtual FText GetColumnDisplayNameText() const override`
- L84 _public function_ `virtual EAvaOutlinerVisibilityType GetVisibilityType() const override`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/Columns/IAvaOutlinerColumn.h` (Private)


#### class `IAvaOutlinerColumn`  
`class IAvaOutlinerColumn : public IAvaTypeCastable, public TSharedFromThis<IAvaOutlinerColumn>`  
_L12-34_
- inherits: `IAvaTypeCastable,TSharedFromThis<IAvaOutlinerColumn>`
- L15 _public prototype_ `UE_AVA_INHERITS(IAvaOutlinerColumn, IAvaTypeCastable);`
- L17 _public function_ `FName GetColumnId() const`
- L19 _public prototype_ `virtual FText GetColumnDisplayNameText() const = 0;`
- L21 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() = 0;`
- L27 _public function_ `virtual bool ShouldShowColumnByDefault() const` — Determines whether the Column should be Showing by Default while still be able to toggle it on/off. Used when calling SHeaderRow::SetShowGeneratedColumn (requires ShouldGenerateWidget to not be set).
- L29 _public prototype_ `virtual TSharedRef<SWidget> ConstructRowWidget(FAvaOutlinerItemPtr InItem , const TSharedRef<FAvaOutlinerView>& InOutlinerView , const TSharedRef<SAvaOutlinerTreeRow>& InRow) = 0;`
- L33 _public function_ `virtual void Tick(float InDeltaTime)`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/Columns/Slate/SAvaOutlinerColor.h` (Private)


#### class `SAvaOutlinerColor`  
`class SAvaOutlinerColor : public SCompoundWidget`  
_L13-58_
- inherits: `SCompoundWidget`
- L16 _public function_ `SLATE_BEGIN_ARGS(SAvaOutlinerColor)`
- L17 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs , const FAvaOutlinerItemPtr& InItem , const TSharedRef<FAvaOutlinerView>& InOutlinerView , const TSharedRef<SAvaOutlinerTreeRow>& InRow);`
- L24 _public prototype_ `FLinearColor FindItemColor() const;`
- L25 _public prototype_ `void RemoveItemColor() const;`
- L27 _public prototype_ `FSlateColor GetBorderColor() const;`
- L28 _public prototype_ `FLinearColor GetStateColorAndOpacity() const;`
- L30 _public prototype_ `TSharedRef<SWidget> GetOutlinerColorOptions();`
- L32 _public prototype_ `FReply OnColorEntrySelected(FName InColorEntry) const;`
- L34 _public prototype_ `void Press();`
- L35 _public prototype_ `void Release();`
- L37 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L38 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L39 _public prototype_ `virtual void OnFocusLost(const FFocusEvent& InFocusEvent) override;`
- L41 _public prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L42 _public prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L45 _private member_ `TSharedPtr<SMenuAnchor> ColorOptions;`
- L47 _private member_ `TWeakPtr<IAvaOutlinerItem> ItemWeak;`
- L49 _private member_ `TWeakPtr<SAvaOutlinerTreeRow> RowWeak;`
- L51 _private member_ `TWeakPtr<FAvaOutliner> OutlinerWeak;`
- L53 _private member_ `TWeakPtr<FAvaOutlinerView> OutlinerViewWeak;`
- L55 _private member_ `mutable FName ItemColor = NAME_None;`
- L57 _private member_ `bool bIsPressed = false;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/Columns/Slate/SAvaOutlinerItemChip.h` (Private)


#### class `SAvaOutlinerItemChip`  
`class SAvaOutlinerItemChip : public SBorder`  
_L20-72_
- inherits: `SBorder`
- desc: Chip Widgets that represent an Item in a compact way in the Items Column
- L23 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(FReply, FOnItemChipClicked, const FAvaOutlinerItemPtr& InItem, const FPointerEvent& InMouseEvent);`
- L25 _public function_ `SLATE_BEGIN_ARGS(SAvaOutlinerItemChip)`
- L26 _public prototype_ `SLATE_EVENT(FOnItemChipClicked, OnItemChipClicked) SLATE_EVENT(FOnDragOver, OnValidDragOver) SLATE_STYLE_ARGUMENT(FTableRowStyle, ChipStyle) SLATE_END_ARGS() void Construct(const FArguments& InArgs , const TSharedRef<IAvaOutlinerItem>& InItem , const TSharedPtr<FAvaOutlinerView>& InOutlinerView);`
- L36 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& InArgs, const FGeometry& InAllottedGeometry, const FSlateRect& InCullingRect , FSlateWindowElementList& OutDrawElements, int32 LayerId , const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L39 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L40 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L41 _public prototype_ `virtual void OnMouseCaptureLost(const FCaptureLostEvent& InCaptureLostEvent) override;`
- L42 _public prototype_ `virtual FReply OnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L43 _public prototype_ `virtual FReply OnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent) override;`
- L44 _public prototype_ `virtual FReply OnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent) override;`
- L45 _public prototype_ `virtual void OnDragLeave(const FDragDropEvent& InDragDropEvent) override;`
- L48 _public prototype_ `bool IsSelected() const;`
- L49 _public prototype_ `const FSlateBrush* GetItemBackgroundBrush() const;`
- L50 _public prototype_ `const FSlateBrush* GetDropIndicatorBrush(EItemDropZone InItemDropZone) const;`
- L53 _private function_ `bool IsPressed() const`
- L54 _private prototype_ `void Press();`
- L55 _private prototype_ `void Release();`
- L57 _private prototype_ `static EItemDropZone GetHoverZone(const FVector2f& InLocalPosition, const FVector2f& InLocalSize);`
- L59 _private member_ `FAvaOutlinerItemWeakPtr ItemWeak;`
- L61 _private member_ `TWeakPtr<FAvaOutlinerView> OutlinerViewWeak;`
- L63 _private member_ `TOptional<EItemDropZone> ItemDropZone;`
- L65 _private member_ `const FTableRowStyle* ChipStyle = nullptr;`
- L67 _private member_ `FOnItemChipClicked OnItemChipClicked;`
- L69 _private member_ `FOnDragOver OnValidDragOver;`
- L71 _private member_ `bool bIsPressed = false;`

#### Free symbols / members of external scopes

- L23 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(FReply, FOnItemChipClicked, const FAvaOutlinerItemPtr& InItem, const FPointerEvent& InMouseEvent);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/Columns/Slate/SAvaOutlinerItemList.h` (Private)


#### class `SAvaOutlinerItemList`  
`class SAvaOutlinerItemList : public SCompoundWidget`  
_L13-44_
- inherits: `SCompoundWidget`
- desc: Widget that visualizes the list of children an Item has when collapsed
- L16 _public function_ `SLATE_BEGIN_ARGS(SAvaOutlinerItemList)`
- L19 _public prototype_ `virtual ~SAvaOutlinerItemList() override;`
- L21 _public prototype_ `void Construct(const FArguments& InArgs , const FAvaOutlinerItemPtr& InParentItem , const TSharedRef<FAvaOutlinerView>& InOutlinerView , const TSharedRef<SAvaOutlinerTreeRow>& InRow);`
- L26 _public prototype_ `void OnItemExpansionChanged(const TSharedPtr<FAvaOutlinerView>& InOutlinerView, bool bInIsExpanded);`
- L28 _public prototype_ `void Refresh();`
- L30 _public prototype_ `FReply OnItemChipSelected(const FAvaOutlinerItemPtr& InItem, const FPointerEvent& InMouseEvent);`
- L32 _public prototype_ `FReply OnItemChipValidDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent);`
- L35 _private member_ `FAvaOutlinerItemWeakPtr ParentItemWeak;`
- L37 _private member_ `TArray<FAvaOutlinerItemWeakPtr> ChildItemListWeak;`
- L39 _private member_ `TWeakPtr<FAvaOutlinerView> OutlinerViewWeak;`
- L41 _private member_ `TWeakPtr<SAvaOutlinerTreeRow> TreeRowWeak;`
- L43 _private member_ `TSharedPtr<SScrollBox> ItemListBox;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/Columns/Slate/SAvaOutlinerLabelComponent.h` (Private)


#### class `SAvaOutlinerLabelComponent`  
`class SAvaOutlinerLabelComponent : public SAvaOutlinerLabelItem`  
_L9-20_
- inherits: `SAvaOutlinerLabelItem`
- L12 _public function_ `SLATE_BEGIN_ARGS(SAvaOutlinerLabelComponent)`
- L13 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs , const TSharedRef<FAvaOutlinerComponent>& InItem , const TSharedRef<SAvaOutlinerTreeRow>& InRow);`
- L19 _public prototype_ `virtual const FInlineEditableTextBlockStyle* GetTextBlockStyle() const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/Columns/Slate/SAvaOutlinerLabelItem.h` (Private)


#### class `SAvaOutlinerLabelItem`  
`class SAvaOutlinerLabelItem : public SCompoundWidget`  
_L16-52_
- inherits: `SCompoundWidget`
- L19 _public function_ `SLATE_BEGIN_ARGS(SAvaOutlinerLabelItem)`
- L20 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs , const TSharedRef<IAvaOutlinerItem>& InItem , const TSharedRef<SAvaOutlinerTreeRow>& InRow);`
- L26 _public prototype_ `bool IsReadOnly() const;`
- L28 _public prototype_ `bool IsItemEnabled() const;`
- L30 _public prototype_ `bool OnVerifyItemLabelChanged(const FText& InLabel, FText& OutErrorMessage);`
- L32 _public prototype_ `void OnLabelTextCommitted(const FText& InLabel, ETextCommit::Type InCommitInfo);`
- L33 _public prototype_ `void RenameItem(const FText& InLabel);`
- L35 _public prototype_ `void OnRenameAction(EAvaOutlinerRenameAction InRenameAction, const TSharedPtr<FAvaOutlinerView>& InOutlinerView) const;`
- L37 _public prototype_ `void OnEnterEditingMode();`
- L38 _public prototype_ `void OnExitEditingMode();`
- L40 _public prototype_ `virtual const FInlineEditableTextBlockStyle* GetTextBlockStyle() const;`
- L43 _private member_ `TSharedPtr<SInlineEditableTextBlock> InlineTextBlock;`
- L45 _private member_ `FAvaOutlinerItemWeakPtr ItemWeak;`
- L47 _private member_ `TWeakPtr<FAvaOutlinerView> OutlinerViewWeak;`
- L49 _private member_ `TAttribute<FText> HighlightText;`
- L51 _private member_ `bool bInEditingMode = false;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/Columns/Slate/SAvaOutlinerLock.h` (Private)


#### class `SAvaOutlinerLock`  
`class SAvaOutlinerLock : public SImage`  
_L19-64_
- inherits: `SImage`
- L22 _public function_ `SLATE_BEGIN_ARGS(SAvaOutlinerLock)`
- L23 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs , const TSharedRef<FAvaOutlinerView>& InOutlinerView , const FAvaOutlinerItemPtr& InItem , const TSharedRef<SAvaOutlinerTreeRow>& InRow);`
- L30 _public prototype_ `virtual FSlateColor GetForegroundColor() const override;`
- L32 _public prototype_ `void SetItemLocked(bool bInLocked);`
- L34 _public prototype_ `bool IsItemLocked() const;`
- L36 _public prototype_ `const FSlateBrush* GetBrush() const;`
- L38 _public prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L41 _public prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;` — If a lock drag drop operation has entered this widget, set its item to the new lock state
- L43 _public prototype_ `FReply HandleClick();`
- L45 _public prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L47 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L49 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L51 _public prototype_ `virtual void OnMouseCaptureLost(const FCaptureLostEvent& CaptureLostEvent) override;`
- L54 _private member_ `TWeakPtr<IAvaOutlinerItem> ItemWeak;`
- L56 _private member_ `TWeakPtr<FAvaOutlinerView> OutlinerViewWeak;`
- L58 _private member_ `TWeakPtr<SAvaOutlinerTreeRow> RowWeak;`
- L60 _private member_ `TUniquePtr<FScopedTransaction> UndoTransaction;`
- L62 _private member_ `const FSlateBrush* LockedBrush = nullptr;`
- L63 _private member_ `const FSlateBrush* UnlockedBrush = nullptr;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/Columns/Slate/SAvaOutlinerTag.h` (Private)


#### class `SAvaOutlinerTag`  
`class SAvaOutlinerTag : public SCompoundWidget`  
_L10-24_
- inherits: `SCompoundWidget`
- L13 _public function_ `SLATE_BEGIN_ARGS(SAvaOutlinerTag)`
- L14 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs , const FAvaOutlinerItemPtr& InItem , const TSharedRef<SAvaOutlinerTreeRow>& InRow);`
- L20 _public prototype_ `FText GetText() const;`
- L23 _private member_ `TWeakPtr<IAvaOutlinerItem> Item;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/Columns/Slate/SAvaOutlinerVisibility.h` (Private)


#### class `SAvaOutlinerVisibility`  
`class SAvaOutlinerVisibility : public SImage`  
_L14-77_
- inherits: `SImage`
- desc: Widget responsible for managing the visibility for a single item
- L17 _public function_ `SLATE_BEGIN_ARGS(SAvaOutlinerVisibility)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs , const TSharedRef<FAvaOutlinerVisibilityColumn>& InColumn , const TSharedRef<FAvaOutlinerView>& InOutlinerView , const FAvaOutlinerItemPtr& InItem , const TSharedRef<SAvaOutlinerTreeRow>& InRow);`
- L28 _private function_ `virtual bool IsVisibilityWidgetEnabled() const` — Returns whether the widget is enabled or not
- L30 _private prototype_ `EAvaOutlinerVisibilityType GetVisibilityType() const;`
- L32 _private prototype_ `virtual const FSlateBrush* GetBrush() const;`
- L34 _private prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L37 _private prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;` — If a visibility drag drop operation has entered this widget, set its item to the new visibility state
- L39 _private prototype_ `FReply HandleClick();`
- L41 _private prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L43 _private prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L45 _private prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L47 _private prototype_ `virtual void OnMouseCaptureLost(const FCaptureLostEvent& CaptureLostEvent) override;`
- L50 _private prototype_ `virtual void OnSetItemVisibility(const FAvaOutlinerItemPtr& Item, const bool bNewVisibility);` — Called when visibility change happens on an Item.
- L52 _private prototype_ `virtual FSlateColor GetForegroundColor() const override;`
- L55 _private prototype_ `bool IsItemVisible() const;` — Check if our wrapped tree item is visible
- L58 _private prototype_ `void SetIsVisible(const bool bVisible);` — Set the item this widget is responsible for to be hidden or shown
- L61 _private member_ `TWeakPtr<IAvaOutlinerItem> ItemWeak;` — The tree item we relate to
- L64 _private member_ `TWeakPtr<FAvaOutlinerView> OutlinerViewWeak;` — Reference back to the outliner so we can set visibility of a whole selection
- L66 _private member_ `TWeakPtr<FAvaOutlinerVisibilityColumn> ColumnWeak;`
- L68 _private member_ `TWeakPtr<SAvaOutlinerTreeRow> RowWeak;`
- L70 _private member_ `TUniquePtr<FScopedTransaction> UndoTransaction;`
- L73 _private member_ `const FSlateBrush* VisibleHoveredBrush = nullptr;` — Visibility brushes for the various states
- L74 _private member_ `const FSlateBrush* VisibleNotHoveredBrush = nullptr;`
- L75 _private member_ `const FSlateBrush* NotVisibleHoveredBrush = nullptr;`
- L76 _private member_ `const FSlateBrush* NotVisibleNotHoveredBrush = nullptr;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/Data/AvaOutlinerSaveState.h` (Private)


#### struct `FAvaOutlinerViewSaveState`  
`struct FAvaOutlinerViewSaveState`  
_L11-32_
- L13 _public prototype_ `FAvaOutlinerViewSaveState();`
- L15 _public member_ `TMap<FString, EAvaOutlinerItemFlags> ViewItemFlags;`
- L17 _public member_ `TMap<FName, bool> ColumnVisibility;`
- L19 _public member_ `TSet<FName> ActiveItemFilters;`
- L21 _public member_ `TOptional<TSet<FName>> HiddenItemTypes;`
- L23 _public member_ `EAvaOutlinerItemViewMode ItemDefaultViewMode;`
- L25 _public member_ `EAvaOutlinerItemViewMode ItemProxyViewMode;`
- L27 _public member_ `bool bUseMutedHierarchy;`
- L29 _public member_ `bool bAutoExpandToSelection;`

#### struct `FAvaOutlinerSaveState`  
`struct FAvaOutlinerSaveState`  
_L34-85_
- L38 _public prototype_ `FAvaOutlinerSaveState() = default;`
- L40 _public prototype_ `void Serialize(FAvaOutliner& InOutliner, FArchive& Ar);`
- L43 _public prototype_ `void SaveOutlinerViewState(const FAvaOutliner& InOutliner, FAvaOutlinerView& InOutlinerView);` — Save the current state of the Outliner Widget (e.g. Quick Type Filters, Search Text, Scoped Item Flags, etc)
- L46 _public prototype_ `void LoadOutlinerViewState(const FAvaOutliner& InOutliner, FAvaOutlinerView& InOutOutlinerView);` — Load the current state of the Outliner Widget (e.g. Quick Type Filters, Search Text, Scoped Item Flags, etc)
- L48 _public function_ `const TMap<FString, FName>& GetItemColoring() const`
- L52 _private prototype_ `void SaveOutlinerViewItems(const FAvaOutliner& InOutliner , const FAvaOutlinerView& InOutlinerView , FAvaOutlinerViewSaveState& OutSaveState);` — Save the Item State in the Outliner Widget (e.g. Item Scoped Flags)
- L57 _private prototype_ `void LoadOutlinerViewItems(const FAvaOutliner& InOutliner , FAvaOutlinerView& InOutOutlinerView , const FAvaOutlinerViewSaveState& InSaveState);` — Load the Item State in the Outliner Widget (e.g. Item Scoped Flags)
- L62 _private prototype_ `void SaveSceneTree(const FAvaOutliner& InOutliner, bool bInResetTree);` — Save the Current Outliner Item
- L65 _private prototype_ `void SaveSceneTreeRecursive(const FAvaOutlinerItemPtr& InParentItem, FAvaSceneTree& InSceneTree, UObject* InContext);` — Save the Current Outliner Item
- L68 _private prototype_ `void LoadSceneTree(const FAvaOutlinerItemPtr& InParentItem, FAvaSceneTree* InSceneTree, UObject* InContext);` — Load the Current Outliner Item and the Outliner Widget View for that Item
- L70 _private prototype_ `void EnsureOutlinerViewCount(int32 InOutlinerViewId);`
- L72 _private prototype_ `void UpdateItemIdContexts(FStringView InNewContext);`
- L78 _private member_ `TMap<FString, int32> ItemSorting_DEPRECATED;` — Deprecated in favor of using Motion Design Scene Tree @see FAvaSceneTree
- L80 _private member_ `TMap<FString, FName> ItemColoring;`
- L82 _private member_ `TArray<FAvaOutlinerViewSaveState> OutlinerViewSaveStates;`
- L84 _private member_ `FString ContextPath;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/Data/AvaOutlinerVersion.h` (Private)


#### struct `FAvaOutlinerVersion`  
`struct FAvaOutlinerVersion`  
_L8-40_
- desc: Version used for serializing Motion Design Outliner Data
- L11 _private prototype_ `FAvaOutlinerVersion() = delete;`
- L39 _public member_ `const static FGuid GUID;`

#### enum `FAvaOutlinerVersion::Type`  
`enum Type`  
_L14-37_
- L17 _public enumerator_ `PreVersioning = 0` — Before file versioning was implemented
- L20 _public enumerator_ `HiddenItemTypes` — Outliner View: Serialization of Hidden Item Types
- L23 _public enumerator_ `ViewModes` — Outliner View: Serialization of View Mode Settings
- L26 _public enumerator_ `ColumnVisibility` — Outliner View: Serialization of Outliner Column Visibility
- L29 _public enumerator_ `SceneTree` — Outliner: Moved Item Ordering Serialization to using Motion Design Scene Tree
- L32 _public enumerator_ `ItemIdFullObjectPath` — Outliner: Changed Item Id to be Full Object Path String rather than just the Sub String
- L35 _public enumerator_ `VersionPlusOne` — New versions are to be added above here
- L36 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/DragDropOps/Handlers/AvaOutlinerActorDropHandler.h` (Private)


#### class `FAvaOutlinerActorDropHandler`  
`class FAvaOutlinerActorDropHandler : public FAvaOutlinerItemDropHandler`  
_L8-21_
- inherits: `FAvaOutlinerItemDropHandler`
- desc: Class that handles Dropping Actor Items into a Target Item
- L11 _public prototype_ `UE_AVA_INHERITS(FAvaOutlinerActorDropHandler, FAvaOutlinerItemDropHandler);`
- L15 _private prototype_ `virtual bool IsDraggedItemSupported(const FAvaOutlinerItemPtr& InDraggedItem) const override;`
- L16 _private prototype_ `virtual TOptional<EItemDropZone> CanDrop(EItemDropZone InDropZone, FAvaOutlinerItemPtr InTargetItem) const override;`
- L17 _private prototype_ `virtual bool Drop(EItemDropZone InDropZone, FAvaOutlinerItemPtr InTargetItem) override;`
- L20 _private prototype_ `void MoveItems(EItemDropZone InDropZone, FAvaOutlinerItemPtr InTargetItem);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/Filters/AvaOutlinerFilterExpressionContext.h` (Private)


#### class `FAvaOutlinerFilterExpressionContext`  
`class FAvaOutlinerFilterExpressionContext : public ITextFilterExpressionContext`  
_L13-38_
- inherits: `ITextFilterExpressionContext`
- desc: Expression context to test the given asset data against the current text filter
- L16 _public function_ `FAvaOutlinerFilterExpressionContext() : Item(nullptr)`
- L19 _public prototype_ `void SetItem(const IAvaOutlinerItem& InItem);`
- L21 _public prototype_ `void ClearItem();`
- L23 _public prototype_ `virtual bool TestBasicStringExpression(const FTextFilterString& InValue , const ETextFilterTextComparisonMode InTextComparisonMode) const override;`
- L26 _public prototype_ `virtual bool TestComplexExpression(const FName& InKey , const FTextFilterString& InValue , const ETextFilterComparisonOperation InComparisonOperation , const ETextFilterTextComparisonMode InTextComparisonMode) const override;`
- L33 _private member_ `const IAvaOutlinerItem* Item;` — Pointer to the asset we're currently filtering
- L35 _private member_ `FName ItemName;`
- L37 _private member_ `FName ItemClass;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/Filters/AvaOutlinerTextFilter.h` (Private)


#### class `FAvaOutlinerTextFilter`  
`class FAvaOutlinerTextFilter : public IFilter<FAvaOutlinerFilterType> , public TSharedFromThis<FAvaOutlinerTextFilter>`  
_L12-35_
- inherits: `IFilter<FAvaOutlinerFilterType>,TSharedFromThis<FAvaOutlinerTextFilter>`
- L17 _public prototype_ `FAvaOutlinerTextFilter();`
- L20 _public function_ `virtual FChangedEvent& OnChanged() override`
- L21 _public prototype_ `virtual bool PassesFilter(FAvaOutlinerFilterType InItem) const override;`
- L24 _public prototype_ `FText GetFilterText() const;`
- L26 _public prototype_ `void SetFilterText(const FText& InFilterText);`
- L30 _private member_ `TSharedRef<FAvaOutlinerFilterExpressionContext> TextFilterExpressionContext;` — Transient context data, used when calling PassesFilter. Kept around to minimize re-allocations between multiple calls to PassesFilter
- L32 _private member_ `FTextFilterExpressionEvaluator TextFilterExpressionEvaluator;`
- L34 _private member_ `FChangedEvent ChangedEvent;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/Filters/Expressions/AvaFilterColorExpressionFactory.h` (Private)


#### class `FAvaFilterColorExpressionFactory`  
`class FAvaFilterColorExpressionFactory final : public IAvaFilterExpressionFactory`  
_L7-17_
- inherits: `IAvaFilterExpressionFactory`
- L10 _public member_ `static const FName KeyName;`
- L13 _public prototype_ `virtual FName GetFilterIdentifier() const override;`
- L14 _public prototype_ `virtual bool FilterExpression(const IAvaOutlinerItem& InItem, const FAvaTextFilterArgs& InArgs) const override;`
- L15 _public prototype_ `virtual bool SupportsComparisonOperation(const ETextFilterComparisonOperation& InComparisonOperation) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/Filters/Expressions/AvaFilterNameExpressionFactory.h` (Private)


#### class `FAvaFilterNameExpressionFactory`  
`class FAvaFilterNameExpressionFactory final : public IAvaFilterExpressionFactory`  
_L7-17_
- inherits: `IAvaFilterExpressionFactory`
- L10 _public member_ `static const FName KeyName;`
- L13 _public prototype_ `virtual FName GetFilterIdentifier() const override;`
- L14 _public prototype_ `virtual bool FilterExpression(const IAvaOutlinerItem& InItem, const FAvaTextFilterArgs& InArgs) const override;`
- L15 _public prototype_ `virtual bool SupportsComparisonOperation(const ETextFilterComparisonOperation& InComparisonOperation) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/Filters/Expressions/AvaFilterTagExpressionFactory.h` (Private)


#### class `FAvaFilterTagExpressionFactory`  
`class FAvaFilterTagExpressionFactory final : public IAvaFilterExpressionFactory`  
_L7-17_
- inherits: `IAvaFilterExpressionFactory`
- L10 _public member_ `static const FName KeyName;`
- L13 _public prototype_ `virtual FName GetFilterIdentifier() const override;`
- L14 _public prototype_ `virtual bool FilterExpression(const IAvaOutlinerItem& InItem, const FAvaTextFilterArgs& InArgs) const override;`
- L15 _public prototype_ `virtual bool SupportsComparisonOperation(const ETextFilterComparisonOperation& InComparisonOperation) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/Filters/Expressions/AvaFilterTypeExpressionFactory.h` (Private)


#### class `FAvaFilterTypeExpressionFactory`  
`class FAvaFilterTypeExpressionFactory final : public IAvaFilterExpressionFactory`  
_L7-17_
- inherits: `IAvaFilterExpressionFactory`
- L10 _public member_ `static const FName KeyName;`
- L13 _public prototype_ `virtual FName GetFilterIdentifier() const override;`
- L14 _public prototype_ `virtual bool FilterExpression(const IAvaOutlinerItem& InItem, const FAvaTextFilterArgs& InArgs) const override;`
- L15 _public prototype_ `virtual bool SupportsComparisonOperation(const ETextFilterComparisonOperation& InComparisonOperation) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/Filters/IAvaFilterExpressionFactory.h` (Private)


#### struct `FAvaTextFilterArgs`  
`struct FAvaTextFilterArgs`  
_L13-29_
- desc: Holds the arguments required for the expression evaluation.
- L16 _public member_ `FName ItemClass;` — item Class
- L19 _public member_ `FName ItemDisplayName;` — Item Display Name
- L22 _public member_ `FName ValueToCheck;` — Second Value
- L25 _public member_ `ETextFilterComparisonOperation ComparisonOperation;` — Comparison Operation requested (Equal/Greater/etc...) still needed for certain Filter
- L28 _public member_ `ETextFilterTextComparisonMode ComparisonMode;` — Comparison Mode requested see ETextFilterTextComparisonMode for more information

#### class `IAvaFilterExpressionFactory`  
`class IAvaFilterExpressionFactory : public TSharedFromThis<IAvaFilterExpressionFactory>`  
_L31-66_
- inherits: `TSharedFromThis<IAvaFilterExpressionFactory>`
- L34 _public function_ `virtual ~IAvaFilterExpressionFactory()`
- L37 _public prototype_ `virtual FName GetFilterIdentifier() const = 0;` — Get the filter identifier for this factory
- L47 _public function_ `static TSharedRef<InFilterExpressionFactoryType> MakeInstance(InArgsType&&... InArgs)`
- L58 _public prototype_ `virtual bool FilterExpression(const IAvaOutlinerItem& InItem, const FAvaTextFilterArgs& InArgs) const = 0;` — Evaluate the expression with the Value given @param InItem Current Item being checked @param InArgs The argument containing the data to evaluate the expression see FAvaTextFilterArgs for more information @return True if the expression evaluate to True, False otherwise
- L65 _public prototype_ `virtual bool SupportsComparisonOperation(const ETextFilterComparisonOperation& InComparisonOperation) const = 0;` — Whether the factory support a given Comparison Operation @param InComparisonOperation Comparison Operation to check @return True if Factory support passed Comparison Operation, False otherwise

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/Filters/IAvaFilterSuggestionFactory.h` (Private)


#### enum `EAvaFilterSuggestionType`  
`enum class EAvaFilterSuggestionType : uint8`  
_L10-16_
- L12 _public enumerator_ `None = 0x00`
- L13 _public enumerator_ `Generic = 0x01` — None      = 0x00,   None
- L14 _public enumerator_ `ItemBased = 0x10` — Generic   = 0x01,   Executed without the need to cycle through outliner item (for example Colors in the Settings)
- L15 _public enumerator_ `All = 0x11` — ItemBased = 0x10,   Executed for each item in the outliner, the item is passed down to get suggestion from it

#### struct `FAvaFilterSuggestionPayload`  
`struct FAvaFilterSuggestionPayload : public IAvaTypeCastable, public TSharedFromThis<FAvaFilterSuggestionPayload>`  
_L23-41_
- inherits: `IAvaTypeCastable,TSharedFromThis<FAvaFilterSuggestionPayload>`
- desc: Holds the arguments required for the suggestion factory to get the suggestion.
- L26 _public function_ `UE_AVA_INHERITS(FAvaFilterSuggestionPayload, IAvaTypeCastable) FAvaFilterSuggestionPayload(TArray<FAssetSearchBoxSuggestion>& OutPossibleSuggestions , const FString& InFilterValue) : OutPossibleSuggestions(OutPossibleSuggestions) , FilterValue(InFilterValue)`
- L37 _public member_ `TArray<FAssetSearchBoxSuggestion>& OutPossibleSuggestions;` — Holds all the suggestion that will be shown
- L40 _public member_ `FString FilterValue;` — The current string value written in the searchbox

#### struct `FAvaFilterSuggestionItemPayload`  
`struct FAvaFilterSuggestionItemPayload : public FAvaFilterSuggestionPayload`  
_L46-67_
- inherits: `FAvaFilterSuggestionPayload`
- desc: Specialization for the ItemBased suggestion factory that needs more arguments
- L49 _public function_ `UE_AVA_INHERITS(FAvaFilterSuggestionItemPayload, FAvaFilterSuggestionPayload) FAvaFilterSuggestionItemPayload(TArray<FAssetSearchBoxSuggestion>& OutPossibleSuggestions , const FString& InFilterValue , const FAvaOutlinerItemPtr& InItem , TSet<FString>& OutFilterCache) : FAvaFilterSuggestionPayload(OutPossibleSuggestions, InFilterValue) , Item(InItem) , OutFilterCache(OutFilterCache)`
- L63 _public member_ `FAvaOutlinerItemPtr Item;` — Current item to check
- L66 _public member_ `TSet<FString>& OutFilterCache;` — Used to speed up the check on whether a suggestion is already added

#### class `IAvaFilterSuggestionFactory`  
`class IAvaFilterSuggestionFactory : public TSharedFromThis<IAvaFilterSuggestionFactory>`  
_L69-101_
- inherits: `TSharedFromThis<IAvaFilterSuggestionFactory>`
- L72 _public function_ `virtual ~IAvaFilterSuggestionFactory()`
- L82 _public function_ `static TSharedRef<InSuggestionFactoryType> MakeInstance(InArgsType&&... InArgs)`
- L91 _public prototype_ `virtual EAvaFilterSuggestionType GetSuggestionType() const = 0;` — Get the type of the suggestion @return The type of the suggestion see EAvaFilterSuggestionType for more information
- L94 _public prototype_ `virtual FName GetSuggestionIdentifier() const = 0;` — Get the suggestion identifier for this factory
- L100 _public prototype_ `virtual void AddSuggestion(const TSharedRef<FAvaFilterSuggestionPayload> InPayload) = 0;` — Add suggestions entry to be shown @param InPayload Arguments to be passed to the factory to get the suggestion to show

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/Filters/Suggestions/AvaFilterColorSuggestionFactory.h` (Private)


#### class `FAvaFilterColorSuggestionFactory`  
`class FAvaFilterColorSuggestionFactory final : public IAvaFilterSuggestionFactory`  
_L7-17_
- inherits: `IAvaFilterSuggestionFactory`
- L10 _public member_ `static const FName KeyName;`
- L13 _public function_ `virtual EAvaFilterSuggestionType GetSuggestionType() const override`
- L14 _public function_ `virtual FName GetSuggestionIdentifier() const override`
- L15 _public prototype_ `virtual void AddSuggestion(const TSharedRef<FAvaFilterSuggestionPayload> InPayload) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/Filters/Suggestions/AvaFilterNameSuggestionFactory.h` (Private)


#### class `FAvaFilterNameSuggestionFactory`  
`class FAvaFilterNameSuggestionFactory final : public IAvaFilterSuggestionFactory`  
_L7-17_
- inherits: `IAvaFilterSuggestionFactory`
- L10 _public member_ `static const FName KeyName;`
- L13 _public function_ `virtual EAvaFilterSuggestionType GetSuggestionType() const override`
- L14 _public function_ `virtual FName GetSuggestionIdentifier() const override`
- L15 _public prototype_ `virtual void AddSuggestion(const TSharedRef<FAvaFilterSuggestionPayload> InPayload) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/Filters/Suggestions/AvaFilterTagSuggestionFactory.h` (Private)


#### class `FAvaFilterTagSuggestionFactory`  
`class FAvaFilterTagSuggestionFactory final : public IAvaFilterSuggestionFactory`  
_L7-17_
- inherits: `IAvaFilterSuggestionFactory`
- L10 _public member_ `static const FName KeyName;`
- L13 _public function_ `virtual EAvaFilterSuggestionType GetSuggestionType() const override`
- L14 _public function_ `virtual FName GetSuggestionIdentifier() const override`
- L15 _public prototype_ `virtual void AddSuggestion(const TSharedRef<FAvaFilterSuggestionPayload> InPayload) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/Filters/Suggestions/AvaFilterTypeSuggestionFactory.h` (Private)


#### class `FAvaFilterTypeSuggestionFactory`  
`class FAvaFilterTypeSuggestionFactory final : public IAvaFilterSuggestionFactory`  
_L7-17_
- inherits: `IAvaFilterSuggestionFactory`
- L10 _public member_ `static const FName KeyName;`
- L13 _public function_ `virtual EAvaFilterSuggestionType GetSuggestionType() const override`
- L14 _public function_ `virtual FName GetSuggestionIdentifier() const override`
- L15 _public prototype_ `virtual void AddSuggestion(const TSharedRef<FAvaFilterSuggestionPayload> InPayload) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/Item/AvaOutlinerTreeRoot.h` (Private)


#### class `FAvaOutlinerTreeRoot`  
`class FAvaOutlinerTreeRoot final : public FAvaOutlinerItem`  
_L11-43_
- inherits: `FAvaOutlinerItem`
- desc: The Item that ensures that every item (except self) has a parent in the hierarchy to make it easier to handle. This is not really a visual item, so it can't appear in the Outliner View
- L14 _public function_ `UE_AVA_INHERITS_WITH_SUPER(FAvaOutlinerTreeRoot, FAvaOutlinerItem) FAvaOutlinerTreeRoot(IAvaOutliner& InOutliner) : FAvaOutlinerItem(InOutliner)`
- L21 _public prototype_ `virtual ~FAvaOutlinerTreeRoot() override = default;`
- L24 _public prototype_ `virtual void FindChildren(TArray<FAvaOutlinerItemPtr>& OutChildren, bool bRecursive) override;`
- L25 _public prototype_ `virtual bool CanAddChild(const FAvaOutlinerItemPtr& InChild) const override;`
- L26 _public prototype_ `virtual TArray<FAvaOutlinerItemPtr> AddChildren(const FAvaOutlinerAddItemParams& InAddItemParams) override;`
- L27 _public prototype_ `virtual bool IsAllowedInOutliner() const override;`
- L28 _public prototype_ `virtual FText GetDisplayName() const override;`
- L29 _public prototype_ `virtual FText GetClassName() const override;`
- L30 _public prototype_ `virtual FText GetIconTooltipText() const override;`
- L31 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L32 _public prototype_ `virtual TSharedRef<SWidget> GenerateLabelWidget(const TSharedRef<SAvaOutlinerTreeRow>& InRow) override;`
- L33 _public prototype_ `virtual bool CanRename() const override;`
- L34 _public prototype_ `virtual bool Rename(const FString& InName) override;`
- L35 _public prototype_ `virtual TOptional<EItemDropZone> CanAcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone) override;`
- L36 _public prototype_ `virtual FReply AcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone) override;`
- L41 _protected prototype_ `virtual FAvaOutlinerItemId CalculateItemId() const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/ItemActions/AvaOutlinerAddItem.h` (Private)


#### class `FAvaOutlinerAddItem`  
`class FAvaOutlinerAddItem : public IAvaOutlinerAction`  
_L12-27_
- inherits: `IAvaOutlinerAction`
- desc: Item Action responsible of adding an item to the Tree under a given optional Parent. If Parent is null, it is added as a Top Level Item.
- L15 _public prototype_ `UE_AVA_INHERITS(FAvaOutlinerAddItem, IAvaOutlinerAction);`
- L17 _public prototype_ `FAvaOutlinerAddItem(const FAvaOutlinerAddItemParams& InAddItemParams);`
- L20 _public prototype_ `virtual bool ShouldTransact() const override;`
- L21 _public prototype_ `virtual void Execute(FAvaOutliner& InOutliner) override;`
- L22 _public prototype_ `virtual void OnObjectsReplaced(const TMap<UObject*, UObject*>& InReplacementMap, bool bRecursive) override;`
- L26 _protected member_ `FAvaOutlinerAddItemParams AddParams;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/ItemActions/AvaOutlinerItemAction.h` (Private)


#### class `IAvaOutlinerAction`  
`class IAvaOutlinerAction : public IAvaTypeCastable`  
_L14-27_
- inherits: `IAvaTypeCastable`
- desc: Interface class for an Action in the Outliner (e.g. Add/Delete/Move Tree Item)
- L17 _public prototype_ `UE_AVA_INHERITS(IAvaOutlinerAction, IAvaTypeCastable);`
- L20 _public function_ `virtual bool ShouldTransact() const` — Determines whether the given action modifies its objects and should transact
- L23 _public prototype_ `virtual void Execute(FAvaOutliner& InOutliner) = 0;` — The Action to execute on the given Outliner
- L26 _public prototype_ `virtual void OnObjectsReplaced(const TMap<UObject*, UObject*>& InReplacementMap, bool bRecursive) = 0;` — Replace any Objects that might be held in this Action that has been killed and replaced by a new object (e.g. BP Components)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/ItemActions/AvaOutlinerRemoveItem.h` (Private)


#### class `FAvaOutlinerRemoveItem`  
`class FAvaOutlinerRemoveItem : public IAvaOutlinerAction`  
_L11-25_
- inherits: `IAvaOutlinerAction`
- desc: Item Action responsible of removing/unregistering Items from the Tree
- L14 _public prototype_ `UE_AVA_INHERITS(FAvaOutlinerRemoveItem, IAvaOutlinerAction);`
- L16 _public prototype_ `FAvaOutlinerRemoveItem(const FAvaOutlinerRemoveItemParams& InRemoveItemParams);`
- L19 _public prototype_ `virtual void Execute(FAvaOutliner& InOutliner) override;`
- L20 _public prototype_ `virtual void OnObjectsReplaced(const TMap<UObject*, UObject*>& InReplacementMap, bool bRecursive) override;`
- L24 _protected member_ `FAvaOutlinerRemoveItemParams RemoveParams;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/Menu/AvaOutlinerViewToolbarContext.h` (Private)


#### class `UAvaOutlinerViewToolbarContext`  
`class UAvaOutlinerViewToolbarContext : public UObject`  
_L12-25_
- reflection: `UCLASS()`
- inherits: `UObject`
- L19 _public prototype_ `UAvaOutlinerViewToolbarContext() = default;`
- L21 _public function_ `TSharedPtr<FAvaOutlinerView> GetOutlinerView() const`
- L24 _private member_ `TWeakPtr<FAvaOutlinerView> OutlinerViewWeak;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/Slate/SAvaOutliner.h` (Private)


#### class `SAvaOutliner`  
`class SAvaOutliner : public SCompoundWidget`  
_L27-112_
- inherits: `SCompoundWidget`
- L30 _public function_ `SLATE_BEGIN_ARGS(SAvaOutliner)`
- L31 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FAvaOutlinerView>& InOutlinerView);`
- L37 _public function_ `TSharedPtr<SAvaOutlinerTreeView> GetTreeView() const`
- L39 _public prototype_ `void SetToolBarWidget(TSharedRef<SWidget> InToolBarWidget);`
- L41 _public prototype_ `void ReconstructColumns();`
- L43 _public prototype_ `void Refresh();`
- L45 _public prototype_ `void SetItemSelection(const TArray<FAvaOutlinerItemPtr>& InItems, bool bSignalSelectionChange);`
- L47 _public prototype_ `void OnItemSelectionChanged(FAvaOutlinerItemPtr InItem, ESelectInfo::Type InSelectionType);`
- L49 _public prototype_ `void ScrollItemIntoView(const FAvaOutlinerItemPtr& InItem) const;`
- L51 _public prototype_ `void SetItemExpansion(FAvaOutlinerItemPtr Item, bool bShouldExpand) const;`
- L53 _public prototype_ `void UpdateItemExpansions(FAvaOutlinerItemPtr Item) const;`
- L55 _public prototype_ `TSharedRef<ITableRow> OnItemGenerateRow(FAvaOutlinerItemPtr Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L57 _public prototype_ `void SetKeyboardFocus() const;`
- L59 _public prototype_ `FText GetSearchText() const;`
- L60 _public prototype_ `void OnSearchTextChanged(const FText& FilterText) const;`
- L61 _public prototype_ `void OnSearchTextCommitted(const FText& FilterText, ETextCommit::Type CommitType) const;`
- L63 _public prototype_ `virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L64 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L65 _public prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L66 _public prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L67 _public prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L69 _public prototype_ `void SetTreeBorderVisibility(bool bVisible);`
- L71 _public prototype_ `void GenerateColumnVisibilityMap(TMap<FName, bool>& OutVisibilityMap);`
- L73 _public prototype_ `void OnAssetSearchSuggestionFilter(const FText& InSearchText, TArray<FAssetSearchBoxSuggestion>& OutPossibleSuggestions, FText& OutSuggestionHighlightText) const;`
- L75 _public prototype_ `FText OnAssetSearchSuggestionChosen(const FText& InSearchText, const FString& InSuggestion) const;`
- L77 _public prototype_ `void OnSaveSearchButtonClicked(const FText& InText);`
- L79 _public prototype_ `void OnCreateCustomTextFilter(const FCustomTextFilterData& InFilterData, bool ApplyFilter) const;`
- L81 _public prototype_ `void OnCancelCustomTextFilterDialog() const;`
- L83 _public prototype_ `void CreateCustomTextFilterWindow(const FText& InText);`
- L87 _private member_ `TWeakPtr<FAvaOutlinerView> OutlinerViewWeak;` — The Outliner Instance that created this Widget
- L90 _private member_ `TSharedPtr<SBox> ToolBarBox;` — The toolbar container
- L93 _private member_ `TSharedPtr<SHeaderRow> HeaderRowWidget;` — The header row of the Outliner
- L95 _private member_ `TSharedPtr<SBorder> TreeBorder;`
- L97 _private member_ `TSharedPtr<SAvaOutlinerTreeView> TreeView;`
- L99 _private member_ `TSharedPtr<SComboButton> SettingsMenu;`
- L101 _private member_ `TSharedPtr<SAssetSearchBox> SearchBoxPtr;`
- L104 _private member_ `TWeakPtr<SWindow> CustomTextFilterWindow;` — The window containing the custom text filter dialog
- L107 _private member_ `bool bIsEnterLastKeyPressed = false;` — If true the SuggestionList shouldn't appear since we selected what we wanted
- L109 _private member_ `bool bSelectingItems = false;`
- L111 _private member_ `TSet<TWeakPtr<FAvaOutlinerItemDragDropOp>> ItemDragDropOps;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/Slate/SAvaOutlinerExpanderArrow.h` (Private)


#### class `SAvaOutlinerExpanderArrow`  
`class SAvaOutlinerExpanderArrow : public SExpanderArrow`  
_L9-31_
- inherits: `SExpanderArrow`
- L12 _public function_ `SLATE_BEGIN_ARGS(SAvaOutlinerExpanderArrow)`
- L13 _public prototype_ `SLATE_ARGUMENT(SExpanderArrow::FArguments, ExpanderArrowArgs) SLATE_ATTRIBUTE(FLinearColor, WireTint) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<ITableRow>& TableRow);`
- L21 _protected prototype_ `virtual int32 OnPaint(const FPaintArgs& Args , const FGeometry& AllottedGeometry , const FSlateRect& MyCullingRect , FSlateWindowElementList& OutDrawElements , int32 LayerId , const FWidgetStyle& InWidgetStyle , bool bParentEnabled) const override;`
- L30 _protected member_ `TAttribute<FLinearColor> WireTint;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/Slate/SAvaOutlinerItemFilters.h` (Private)


#### class `SAvaOutlinerItemFilters`  
`class SAvaOutlinerItemFilters : public SCompoundWidget`  
_L17-77_
- inherits: `SCompoundWidget`
- L20 _public function_ `SLATE_BEGIN_ARGS(SAvaOutlinerItemFilters)`
- L21 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FAvaOutlinerView>& InOutlinerView);`
- L28 _public prototype_ `void AddItemFilterSlot(const TSharedPtr<IAvaOutlinerItemFilter>& InFilter, bool bIsCustomSlot);` — Adds the Filter
- L30 _public prototype_ `void UpdateCustomItemFilters();`
- L32 _public prototype_ `void OnOutlinerLoaded();`
- L34 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L35 _public prototype_ `FSlateColor GetFilterStateColor(TSharedPtr<IAvaOutlinerItemFilter> Filter) const;`
- L37 _public prototype_ `ECheckBoxState IsChecked(TSharedPtr<IAvaOutlinerItemFilter> Filter) const;`
- L38 _public prototype_ `void OnCheckBoxStateChanged(ECheckBoxState CheckBoxState, TSharedPtr<IAvaOutlinerItemFilter> Filter) const;`
- L40 _public prototype_ `float GetShowItemFiltersLerp() const;`
- L41 _public prototype_ `void OnShowItemFiltersChanged(const FAvaOutlinerView& InOutlinerView);`
- L43 _public prototype_ `FReply ToggleShowItemFilters();`
- L45 _public prototype_ `FReply SelectAll();`
- L46 _public prototype_ `FReply DeselectAll();`
- L49 _private prototype_ `FText GetFilterItemMenuButtonToolTip() const;`
- L50 _private prototype_ `const FSlateBrush* GetFilterItemMenuButtonIcon() const;`
- L52 _private member_ `TWeakPtr<FAvaOutlinerView> OutlinerViewWeak;`
- L54 _private member_ `TSharedPtr<SBox> ItemFilterBox;`
- L56 _private member_ `TSharedPtr<SScrollBox> ItemFilterScrollBox;`
- L58 _private member_ `TMap<FName, TSharedPtr<SWidget>> ItemFilterSlots;`
- L65 _private member_ `TMap<FName, TSharedPtr<SWidget>> CustomItemFilterSlots;` — Map of Filter Ids and their Slot. This is a separate map purely to allow users to use filter-ids of natively constructed item filters as they are not exposed
- L67 _private member_ `FCurveSequence ExpandFiltersSequence;`
- L70 _private member_ `float ItemFilterBoxTargetHeight = 0.f;` — Target Height of the Item Filter Box when playing the sequence
- L73 _private member_ `bool bShowItemFilters = false;` — Whether to expand and show the Item Filter List
- L76 _private member_ `bool bPlayedSequenceLastTick = true;` — The cached state of Expand Filters Sequence, to know when states have changed. Default to true so that we run it at the start

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/Slate/SAvaOutlinerTreeRow.h` (Private)


#### class `SAvaOutlinerTreeRow`  
`class SAvaOutlinerTreeRow : public SMultiColumnTableRow<FAvaOutlinerItemPtr>`  
_L13-46_
- inherits: `SMultiColumnTableRow<FAvaOutlinerItemPtr>`
- L16 _public function_ `SLATE_BEGIN_ARGS(SAvaOutlinerTreeRow)`
- L17 _public prototype_ `SLATE_ATTRIBUTE(FText, HighlightText) SLATE_END_ARGS() void Construct(const FArguments& InArgs , const TSharedRef<FAvaOutlinerView>& InOutlinerView , const TSharedPtr<SAvaOutlinerTreeView>& InTreeView , const FAvaOutlinerItemPtr& InItem);`
- L25 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& InColumnName) override;`
- L27 _public function_ `TAttribute<FText> GetHighlightText() const`
- L29 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L31 _public prototype_ `TSharedPtr<FAvaOutlinerView> GetOutlinerView() const;`
- L33 _public function_ `const FTableRowStyle* GetStyle() const`
- L36 _public prototype_ `FReply OnDefaultDrop(const FDragDropEvent& InDragDropEvent) const;` — The default reply if a row did not handle AcceptDrop
- L39 _private member_ `FAvaOutlinerItemPtr Item;`
- L41 _private member_ `TWeakPtr<SAvaOutlinerTreeView> TreeViewWeak;`
- L43 _private member_ `TWeakPtr<FAvaOutlinerView> OutlinerViewWeak;`
- L45 _private member_ `TAttribute<FText> HighlightText;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/Slate/SAvaOutlinerTreeView.h` (Private)


#### class `SAvaOutlinerTreeView`  
`class SAvaOutlinerTreeView : public STreeView<FAvaOutlinerItemPtr>`  
_L10-48_
- inherits: `STreeView<FAvaOutlinerItemPtr>`
- L13 _public function_ `SLATE_BEGIN_ARGS(SAvaOutlinerTreeView)`
- L14 _public prototype_ `SLATE_ARGUMENT(STreeView<FAvaOutlinerItemPtr>::FArguments, TreeViewArgs) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<FAvaOutlinerView>& InOutlinerView);`
- L19 _public prototype_ `int32 GetItemIndex(FAvaOutlinerItemPtr Item) const;`
- L21 _public prototype_ `void FocusOnItem(const FAvaOutlinerItemPtr& InItem);`
- L23 _public prototype_ `void ScrollItemIntoView(const FAvaOutlinerItemPtr& InItem);`
- L25 _public prototype_ `void UpdateItemExpansions(FAvaOutlinerItemPtr InItem);`
- L28 _public prototype_ `virtual void Private_UpdateParentHighlights() override;`
- L32 _public prototype_ `virtual void Private_SetItemSelection(FAvaOutlinerItemPtr InItem, bool bShouldBeSelected, bool bWasUserDirected = false) override;`
- L33 _public prototype_ `virtual void Private_SignalSelectionChanged(ESelectInfo::Type SelectInfo) override;`
- L34 _public prototype_ `virtual void Private_ClearSelection() override;`
- L38 _public prototype_ `virtual FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const override;`
- L39 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L40 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L41 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L45 _private member_ `TWeakPtr<FAvaOutlinerView> OutlinerViewWeak;`
- L47 _private member_ `TItemSet PreviousSelectedItems;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/Slate/Styling/AvaOutlinerStyleUtils.h` (Private)


#### enum `UE::AvaOutliner::Private::EStyleType`  
`enum class EStyleType`  
_L14-19_
- L16 _public enumerator_ `Normal`
- L17 _public enumerator_ `Hovered`
- L18 _public enumerator_ `Pressed`

#### struct `UE::AvaOutliner::Private::FStyleUtils`  
`struct FStyleUtils`  
_L21-30_
- L23 _public prototype_ `static const FToolBarStyle& GetSlimToolBarStyle();`
- L25 _public prototype_ `static const FSlateBrush& GetBrush(EStyleType InStyleType, bool bIsSelected);`
- L27 _public prototype_ `static FSlateColor GetColor(EStyleType InStyleType, bool bIsSelected);`
- L29 _public prototype_ `static FSlateColorBrush GetColorBrush(EStyleType InStyleType, bool bIsSelected);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace AvaOutliner` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::AvaOutliner`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/Stats/AvaOutlinerStats.h` (Private)


#### enum `EAvaOutlinerStatCountType`  
`enum class EAvaOutlinerStatCountType : uint8`  
_L9-16_
- L11 _public enumerator_ `None`
- L13 _public enumerator_ `VisibleItemCount` — Number of items that are present in the Outliner View (not to be confused with Actor/Component Visibility)
- L15 _public enumerator_ `SelectedItemCount` — Number of items that are selected in the Outliner View

#### struct `FAvaOutlinerStats`  
`struct FAvaOutlinerStats`  
_L21-44_
- desc: Responsible for holding Stat information for an Outliner View
- L27 _public prototype_ `void Tick(FAvaOutlinerView& InOutlinerView);` — Updates to check whether a given stat type is dirty. Even though this is Ticked every frame it will only do work for the dirty stats
- L30 _public prototype_ `void MarkCountTypeDirty(EAvaOutlinerStatCountType CountType);` — Dirties a given count type
- L33 _public prototype_ `void SetStatCount(EAvaOutlinerStatCountType CountType, int32 Count);` — Sets the count for a given countable stat type
- L36 _public prototype_ `int32 GetStatCount(EAvaOutlinerStatCountType CountType) const;` — Gets the count for a given countable stat type
- L40 _private member_ `TMap<EAvaOutlinerStatCountType, int32> StatCount;` — Map of a Countable Stat Type and the current count it has in this Instance
- L43 _private member_ `TSet<EAvaOutlinerStatCountType> DirtyStatTypes;` — The Count Types that have changed and must be modified on next Tick

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/Stats/Slate/SAvaOutlinerStats.h` (Private)


#### class `SAvaOutlinerStats`  
`class SAvaOutlinerStats : public SCompoundWidget`  
_L10-28_
- inherits: `SCompoundWidget`
- L13 _public function_ `SLATE_BEGIN_ARGS(SAvaOutlinerStats)`
- L14 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FAvaOutlinerView>& InOutlinerView);`
- L18 _public prototype_ `FText GetStatsCount(EAvaOutlinerStatCountType CountType) const;`
- L20 _public prototype_ `FReply ScrollToPreviousSelection() const;`
- L22 _public prototype_ `FReply ScrollToNextSelection() const;`
- L24 _public prototype_ `EVisibility GetSelectionNavigationVisibility() const;`
- L27 _private member_ `TWeakPtr<FAvaOutlinerView> OutlinerViewWeak;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Public/AvaOutlinerDefines.h` (Public)


#### enum `EAvaOutlinerItemFlags`  
`enum class EAvaOutlinerItemFlags : uint8`  
_L19-28_
- L21 _public enumerator_ `None = 0`
- L23 _public enumerator_ `IgnorePendingKill = 1 << 0` — Whether Item should get the underlying UObject ignoring if it's pending kill
- L25 _public enumerator_ `PendingRemoval = 1 << 1` — Item pending Removal from the Outliner
- L27 _public enumerator_ `Expanded = 1 << 2` — Whether the Item is in expanded state to show its child items

#### enum `EAvaOutlinerItemSelectionFlags`  
`enum class EAvaOutlinerItemSelectionFlags : uint8`  
_L32-43_
- desc: Flags specifying how an Item should be Selected
- L34 _public enumerator_ `None = 0`
- L36 _public enumerator_ `AppendToCurrentSelection = 1 << 0` — Append to the Current Selection
- L38 _public enumerator_ `SignalSelectionChange = 1 << 1` — Signal Selection Change (e.g. to trigger on Selection Change Delegate)
- L40 _public enumerator_ `IncludeChildren = 1 << 2` — Auto-include the Items' Children in the Selection
- L42 _public enumerator_ `ScrollIntoView = 1 << 3` — Whether to Scroll first Item into View

#### enum `EAvaOutlinerIgnoreNotifyFlags`  
`enum class EAvaOutlinerIgnoreNotifyFlags : uint8`  
_L46-54_
- L48 _public enumerator_ `None = 0`
- L50 _public enumerator_ `Spawn = 1 << 0` — Ignores automatically handling actor spawns, usually so that it is manually handled
- L52 _public enumerator_ `Duplication = 1 << 1` — Ignores automatically handling actor duplications, usually so that it is manually handled
- L53 _public enumerator_ `All = 0xFF`

#### enum `EAvaOutlinerVisibilityType`  
`enum class EAvaOutlinerVisibilityType : uint8`  
_L57-64_
- L59 _public enumerator_ `None`
- L61 _public enumerator_ `Editor` — Visible in Editor
- L63 _public enumerator_ `Runtime` — Visible in Game

#### enum `EAvaOutlinerRenameAction`  
`enum class EAvaOutlinerRenameAction : uint8`  
_L66-72_
- L68 _public enumerator_ `None`
- L69 _public enumerator_ `Requested`
- L70 _public enumerator_ `Completed`
- L71 _public enumerator_ `Cancelled`

#### enum `EAvaOutlinerExtensionPosition`  
`enum class EAvaOutlinerExtensionPosition`  
_L74-78_
- L76 _public enumerator_ `Before`
- L77 _public enumerator_ `After`

#### enum `EAvaOutlinerItemViewMode`  
`enum class EAvaOutlinerItemViewMode : uint8`  
_L82-93_
- reflection: `UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- desc: The type of visualization being done to the item
- L84 _public enumerator_ `None = 0 UMETA(Hidden)`
- L87 _public enumerator_ `ItemTree = 1 << 0` — Outliner Tree Hierarchy View of the Items
- L89 _public enumerator_ `HorizontalItemList = 1<< 1` — Flattened Horizontal List of Nested Items shown in the "Items" column
- L92 _public enumerator_ `All = ItemTree | HorizontalItemList` — All the Views

#### enum `EAvaOutlinerDragDropActionType`  
`enum class EAvaOutlinerDragDropActionType : uint8`  
_L96-100_
- L98 _public enumerator_ `Move`
- L99 _public enumerator_ `Copy`

#### Free symbols / members of external scopes

- L14 _typedef_ `using FAvaOutlinerColorPair = TPair<FName, FLinearColor>;`
- L15 _typedef_ `using FAvaOutlinerFilterType = const IAvaOutlinerItem&;`
- L16 _typedef_ `using FAvaOutlinerItemPtr = TSharedPtr<IAvaOutlinerItem>;`
- L17 _typedef_ `using FAvaOutlinerItemWeakPtr = TWeakPtr<IAvaOutlinerItem>;`
- L29 _prototype_ `ENUM_CLASS_FLAGS(EAvaOutlinerItemFlags);`
- L44 _prototype_ `ENUM_CLASS_FLAGS(EAvaOutlinerItemSelectionFlags);`
- L55 _prototype_ `ENUM_CLASS_FLAGS(EAvaOutlinerIgnoreNotifyFlags);`
- L94 _prototype_ `ENUM_CLASS_FLAGS(EAvaOutlinerItemViewMode);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Public/AvaOutlinerSubsystem.h` (Public)


#### enum `EAvaOutlinerHierarchyChangeType`  
`enum class EAvaOutlinerHierarchyChangeType : uint8`  
_L14-22_
- reflection: `UENUM()`
- L17 _public enumerator_ `Detached` — When the actor has detached from the Parent
- L19 _public enumerator_ `Attached` — When the actor has attached to the Parent
- L21 _public enumerator_ `Rearranged` — When the actor was rearranged and kept its attachment to the Parent

#### class `UAvaOutlinerSubsystem`  
`class UAvaOutlinerSubsystem : public UWorldSubsystem`  
_L26-68_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWorldSubsystem`
- desc: Subsystem in charge of instancing and keeping reference of the World's Outliner
- L38 _public prototype_ `TSharedRef<IAvaOutliner> GetOrCreateOutliner(IAvaOutlinerProvider& InProvider, bool bInForceCreate = false);` — Instantiates the World's Outliner @param InProvider the outliner provider @param bInForceCreate whether to create a new IAvaOutliner even if one already exists @returns an existing or new valid IAvaOutliner instance @note the subsystem holds a non-owning reference of the outliner, the provider is what ideally should be holding the owning reference
- L40 _public function_ `TSharedPtr<IAvaOutliner> GetOutliner() const`
- L45 _public prototype_ `DECLARE_EVENT_ThreeParams(UAvaOutlinerSubsystem, FActorHierarchyChanged, AActor* , const AActor* , EAvaOutlinerHierarchyChangeType);`
- L46 _public function_ `FActorHierarchyChanged& OnActorHierarchyChanged()`
- L57 _public prototype_ `void BroadcastActorHierarchyChanged(AActor* InActor, const AActor* InParentActor, EAvaOutlinerHierarchyChangeType InChangeType) const;` — Called when the Actor has changed in the Outliner Hierarchy @param InActor the actor that changed @param InParentActor the parent actor involved (old if detached, new if attached, null if the root or invalid actor) @param InChangeType the type of hierarchical change notified
- L61 _protected prototype_ `virtual bool DoesSupportWorldType(const EWorldType::Type InWorldType) const override;`
- L65 _private member_ `TWeakPtr<IAvaOutliner> OutlinerWeak;`
- L67 _private member_ `FActorHierarchyChanged ActorHierarchyChangedEvent;`

#### Free symbols / members of external scopes

- L45 _delegate_ `DECLARE_EVENT_ThreeParams(UAvaOutlinerSubsystem, FActorHierarchyChanged, AActor* , const AActor* , EAvaOutlinerHierarchyChangeType);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Public/DragDropOps/AvaOutlinerItemDragDropOp.h` (Public)


#### class `FAvaOutlinerItemDragDropOp`  
`class FAvaOutlinerItemDragDropOp : public FDecoratedDragDropOp`  
_L15-72_
- inherits: `FDecoratedDragDropOp`
- desc: Drag Drop Operation for Ava Outliner Items. Customized behavior can be added in via the AddDropHandler function
- L18 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FAvaOutlinerItemDragDropOp, FDecoratedDragDropOp) static TSharedRef<FAvaOutlinerItemDragDropOp> New(const TArray<FAvaOutlinerItemPtr>& InItems , const TSharedPtr<FAvaOutlinerView>& InOutlinerView , EAvaOutlinerDragDropActionType InActionType);`
- L24 _public function_ `TSharedPtr<IAvaOutlinerView> GetOutlinerView() const`
- L29 _public function_ `TConstArrayView<FAvaOutlinerItemPtr> GetItems() const`
- L34 _public function_ `EAvaOutlinerDragDropActionType GetActionType() const`
- L40 _public prototype_ `void GetDragDropOpActors(TArray<TWeakObjectPtr<AActor>>& OutActors) const;` — Retrieves the Actors found in the DragDropOp, assuming this is of type FAvaOutlinerItemDragDropOp
- L43 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnItemDragDropOpInitialized, FAvaOutlinerItemDragDropOp&) static FOnItemDragDropOpInitialized& OnItemDragDropOpInitialized();` — Called when the FAvaOutlinerItemDragDropOp has been created and Initialized in FAvaOutlinerItemDragDropOp::Init
- L49 _public function_ `void AddDropHandler(InArgTypes&&... InArgs)`
- L56 _public prototype_ `FReply Drop(EItemDropZone InDropZone, FAvaOutlinerItemPtr InTargetItem);`
- L58 _public prototype_ `TOptional<EItemDropZone> CanDrop(EItemDropZone InDropZone, FAvaOutlinerItemPtr InTargetItem) const;`
- L61 _protected prototype_ `void Init(const TArray<FAvaOutlinerItemPtr>& InItems , const TSharedPtr<FAvaOutlinerView>& InOutlinerView , EAvaOutlinerDragDropActionType InActionType);`
- L65 _protected member_ `TArray<FAvaOutlinerItemPtr> Items;`
- L67 _protected member_ `TArray<TSharedRef<FAvaOutlinerItemDropHandler>> DropHandlers;`
- L69 _protected member_ `TWeakPtr<IAvaOutlinerView> OutlinerViewWeak;`
- L71 _protected member_ `EAvaOutlinerDragDropActionType ActionType = EAvaOutlinerDragDropActionType::Move;`

#### Free symbols / members of external scopes

- L43 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnItemDragDropOpInitialized, FAvaOutlinerItemDragDropOp&) static FOnItemDragDropOpInitialized& OnItemDragDropOpInitialized();` — Called when the FAvaOutlinerItemDragDropOp has been created and Initialized in FAvaOutlinerItemDragDropOp::Init

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Public/DragDropOps/Handlers/AvaOutlinerItemDropHandler.h` (Public)


#### class `FAvaOutlinerItemDropHandler`  
`class FAvaOutlinerItemDropHandler : public IAvaTypeCastable, public TSharedFromThis<FAvaOutlinerItemDropHandler>`  
_L20-70_
- inherits: `IAvaTypeCastable,TSharedFromThis<FAvaOutlinerItemDropHandler>`
- desc: Base Class to Handle Dropping Outliner Items into a Target Outliner Item @see built-in example FAvaOutlinerActorDropHandler
- L24 _private prototype_ `void Initialize(const FAvaOutlinerItemDragDropOp& InDragDropOp);`
- L27 _public prototype_ `UE_AVA_INHERITS(FAvaOutlinerItemDropHandler, IAvaTypeCastable);`
- L29 _public function_ `TConstArrayView<FAvaOutlinerItemPtr> GetItems() const`
- L35 _protected prototype_ `virtual bool IsDraggedItemSupported(const FAvaOutlinerItemPtr& InDraggedItem) const = 0;`
- L37 _protected prototype_ `virtual TOptional<EItemDropZone> CanDrop(EItemDropZone InDropZone, FAvaOutlinerItemPtr InTargetItem) const = 0;`
- L39 _protected prototype_ `virtual bool Drop(EItemDropZone InDropZone, FAvaOutlinerItemPtr InTargetItem) = 0;`
- L47 _protected function_ `template<typename InItemType, typename = typename TEnableIf<TIsDerivedFrom<InItemType, IAvaOutlinerItem>::Value>::Type> void ForEachItem(const TFunctionRef<EIterationResult(InItemType&)>& InFunc) const`
- L67 _protected member_ `TArray<FAvaOutlinerItemPtr> Items;`
- L69 _protected member_ `EAvaOutlinerDragDropActionType ActionType = EAvaOutlinerDragDropActionType::Move;`

#### enum `FAvaOutlinerItemDropHandler::EIterationResult`  
`enum class EIterationResult`  
_L41-45_
- L43 _public enumerator_ `Continue`
- L44 _public enumerator_ `Break`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Public/Filters/AvaOutlinerItemTypeFilter.h` (Public)


#### enum `EAvaOutlinerTypeFilterMode`  
`enum class EAvaOutlinerTypeFilterMode : uint8`  
_L15-24_
- reflection: `UENUM()`
- L17 _public enumerator_ `None = 0`
- L20 _public enumerator_ `MatchesType = 1 << 0` — Outliner Item type matches the Filter Type
- L23 _public enumerator_ `ContainerOfType = 1 << 1` — Outliner Item contains an item (as a descendant/child) of that type

#### struct `FAvaOutlinerItemTypeFilterData`  
`struct FAvaOutlinerItemTypeFilterData`  
_L28-81_
- reflection: `USTRUCT()`
- L32 _public prototype_ `FAvaOutlinerItemTypeFilterData() = default;`
- L34 _public prototype_ `FAvaOutlinerItemTypeFilterData(const TArray<TSubclassOf<UObject>>& InFilterClasses , EAvaOutlinerTypeFilterMode InMode = EAvaOutlinerTypeFilterMode::MatchesType , const FSlateBrush* InIconBrush = nullptr , const FText& InTooltipText = FText::GetEmpty() , EClassFlags InRequiredClassFlags = CLASS_None , EClassFlags InRestrictedClassFlags = CLASS_None);`
- L41 _public prototype_ `bool HasValidFilterData() const;`
- L43 _public prototype_ `FText GetTooltipText() const;`
- L45 _public prototype_ `const FSlateBrush* GetIcon() const;`
- L47 _public prototype_ `EAvaOutlinerTypeFilterMode GetFilterMode() const;`
- L49 _public prototype_ `void SetOverrideIconColor(FSlateColor InNewIconColor);`
- L51 _public prototype_ `bool IsValidClass(const UClass* InClass) const;`
- L53 _public prototype_ `void SetFilterText(const FText& InText);`
- L55 _public prototype_ `bool PassesFilterText(const FAvaOutlinerObject& InItem) const;`
- L59 _private member_ `TArray<TSubclassOf<UObject>> FilterClasses;` — `UPROPERTY(EditAnywhere, Category = "Filter")`
- L62 _private member_ `EAvaOutlinerTypeFilterMode FilterMode = EAvaOutlinerTypeFilterMode::MatchesType;` — `UPROPERTY(EditAnywhere, Category = "Filter")`
- L65 _private member_ `FText FilterText;` — `UPROPERTY(EditAnywhere, Category = "Filter|Advanced")`
- L68 _private member_ `FText TooltipText;` — `UPROPERTY(EditAnywhere, Category = "Filter")`
- L71 _private member_ `FSlateBrush OverrideIcon;` — `UPROPERTY(EditAnywhere, Category = "Filter", meta=(EditCondition="bUseOverrideIcon"))`
- L74 _private member_ `bool bUseOverrideIcon = true;` — `UPROPERTY(EditAnywhere, Category = "Filter", meta=(InlineEditConditionToggle))`
- L76 _private member_ `const FSlateBrush* IconBrush = nullptr;`
- L78 _private member_ `EClassFlags RequiredClassFlags = CLASS_None;`
- L80 _private member_ `EClassFlags RestrictedClassFlags = CLASS_None;`

#### class `FAvaOutlinerItemTypeFilter`  
`class FAvaOutlinerItemTypeFilter : public IAvaOutlinerItemFilter`  
_L85-135_
- inherits: `IAvaOutlinerItemFilter`
- L88 _public function_ `explicit FAvaOutlinerItemTypeFilter(FName InFilterId , const TArray<TSubclassOf<UObject>>& InFilterClasses , EAvaOutlinerTypeFilterMode InMode = EAvaOutlinerTypeFilterMode::MatchesType , const FSlateBrush* InIconBrush = nullptr , const FText& InTooltipText = FText::GetEmpty() , EClassFlags InRequiredClassFlags = CLASS_None , EClassFlags InRestrictedClassFlags = CLASS_None) : FilterId(InFilterId) , FilterData(InFilterClasses, InMode, InIconBrush, InTooltipText, InRequiredClassFlags, InRestrictedClassFlags)`
- L100 _public function_ `explicit FAvaOutlinerItemTypeFilter(FName InFilterId, const FAvaOutlinerItemTypeFilterData& InFilterData) : FilterId(InFilterId) , FilterData(InFilterData)`
- L106 _public function_ `explicit FAvaOutlinerItemTypeFilter(FName InFilterId , const FAvaOutlinerItemTypeFilterPassDelegate& InFilterPassDelegate , const FSlateBrush* InIconBrush = nullptr , const FText& InTooltipText = FText::GetEmpty()) : FilterId(InFilterId) , FilterData({}, EAvaOutlinerTypeFilterMode::MatchesType, InIconBrush, InTooltipText, CLASS_None, CLASS_None) , FilterPassDelegate(InFilterPassDelegate)`
- L118 _protected function_ `virtual FChangedEvent& OnChanged() override`
- L119 _protected prototype_ `virtual bool PassesFilter(FAvaOutlinerFilterType InItem) const override;`
- L123 _protected prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L124 _protected prototype_ `virtual FText GetTooltipText() const override;`
- L125 _protected function_ `virtual FName GetFilterId() const override`
- L128 _protected member_ `FName FilterId;`
- L130 _protected member_ `FAvaOutlinerItemTypeFilterData FilterData;`
- L132 _protected member_ `FChangedEvent ChangedEvent;`
- L134 _protected member_ `FAvaOutlinerItemTypeFilterPassDelegate FilterPassDelegate;`

#### Free symbols / members of external scopes

- L25 _prototype_ `ENUM_CLASS_FLAGS(EAvaOutlinerTypeFilterMode);`
- L83 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FAvaOutlinerItemTypeFilterPassDelegate, FAvaOutlinerFilterType);`
- L83 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FAvaOutlinerItemTypeFilterPassDelegate, FAvaOutlinerFilterType);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Public/Filters/IAvaOutlinerItemFilter.h` (Public)


#### class `IAvaOutlinerItemFilter`  
`class IAvaOutlinerItemFilter : public IFilter<FAvaOutlinerFilterType> , public TSharedFromThis<IAvaOutlinerItemFilter>`  
_L13-26_
- inherits: `IFilter<FAvaOutlinerFilterType>,TSharedFromThis<IAvaOutlinerItemFilter>`
- L19 _public prototype_ `virtual FName GetFilterId() const = 0;` — Gets a Unique Identifier for the Filter
- L22 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const = 0;` — Gets a the Filter Icon Brush to represent in the Outliner
- L25 _public prototype_ `virtual FText GetTooltipText() const = 0;` — Gets the Filter Tooltip to show in the Outliner

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Public/IAvaOutliner.h` (Public)


#### class `IAvaOutliner`  
`class IAvaOutliner : public TSharedFromThis<IAvaOutliner>`  
_L37-200_
- inherits: `TSharedFromThis<IAvaOutliner>`
- desc: The Outliner Object that is commonly instanced once per World (unless for advanced use where there are different outliner instances with different item ordering and behaviors). This is the object that dictates core outliner behavior like how items are sorted, which items are allowed, etc. Views are the objects that take this core behavior and show a part of it (e.g. through filters).
- L40 _public prototype_ `virtual ~IAvaOutliner() = default;`
- L42 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnOutlinerLoaded);`
- L43 _public prototype_ `virtual FOnOutlinerLoaded& GetOnOutlinerLoaded() = 0;`
- L45 _public prototype_ `virtual IAvaOutlinerProvider& GetProvider() const = 0;`
- L48 _public prototype_ `virtual void SetBaseCommandList(const TSharedPtr<FUICommandList>& InBaseCommandList) = 0;` — Sets the Command List that the Outliner Views will use to append their Command Lists to
- L51 _public prototype_ `virtual void Serialize(FArchive& Ar) = 0;` — Serializes the Outliner Save State to the given archive
- L54 _public prototype_ `virtual TSharedPtr<IAvaOutlinerView> RegisterOutlinerView(int32 InOutlinerViewId) = 0;` — Register a new Outliner View to the Outliner to the given id, replacing the old view that was bound to the given id
- L57 _public prototype_ `virtual TSharedPtr<IAvaOutlinerView> GetOutlinerView(int32 InOutlinerViewId) const = 0;` — Gets the Outliner View bound to the given id
- L61 _public function_ `template<typename InItemType, typename = typename TEnableIf<TIsDerivedFrom<InItemType, IAvaOutlinerItem>::IsDerived>::Type, typename ...InArgTypes> TSharedRef<InItemType> FindOrAdd(InArgTypes&&... InArgs)` — Instantiates a new Item and automatically registers it to the Outliner
- L82 _public function_ `template<typename InItemProxyType, typename = typename TEnableIf<TIsDerivedFrom<InItemProxyType, FAvaOutlinerItemProxy>::IsDerived>::Type> IAvaOutlinerItemProxyFactory* GetItemProxyFactory() const` — Tries to find the Item Proxy Factory for the given Item Proxy Type Name
- L99 _public function_ `template<typename InItemProxyType, typename = typename TEnableIf<TIsDerivedFrom<InItemProxyType, FAvaOutlinerItemProxy>::IsDerived>::Type> TSharedPtr<FAvaOutlinerItemProxy> GetOrCreateItemProxy(const FAvaOutlinerItemPtr& InParentItem)` — Tries to get the Item Proxy Factory for the given Item Proxy type, first trying the Outliner Registry then the Module's then returns an existing item proxy created via the factory, or creates one if there's no existing item proxy @returns the Item Proxy created by the Factory. Can be null if no factory was found or if the factory intentionally returns null
- L128 _public prototype_ `virtual void RegisterItem(const FAvaOutlinerItemPtr& InItem) = 0;` — Registers the given Item, replacing the old one.
- L131 _public prototype_ `virtual void UnregisterItem(const FAvaOutlinerItemId& InItemId) = 0;` — Unregisters the Item having the given ItemId
- L134 _public prototype_ `virtual void RequestRefresh() = 0;` — Ensures that the next time Refresh is called in tick, Refresh will be called
- L141 _public prototype_ `virtual void Refresh() = 0;` — Flushes the Pending Actions from the Queue while also updating the state of the Outliner. Calling it directly is forcing it to happen. If a refresh is needed it will be called on the next tick automatically.
- L144 _public prototype_ `virtual TSharedRef<FAvaOutlinerItem> GetTreeRoot() const = 0;` — Gets the Tree Root Item of the Outliner
- L150 _public prototype_ `virtual FAvaOutlinerItemPtr FindItem(const FAvaOutlinerItemId& InItemId) const = 0;` — Finds the Registered Item that has the given Id @returns the Item with the given Id, or null if the item does not exist or was not registered to the Outliner
- L157 _public prototype_ `virtual void SetIgnoreNotify(EAvaOutlinerIgnoreNotifyFlags InFlag, bool bIgnore) = 0;` — Adds or Removes the Ignore Notify Flags to prevent certain actions from automatically happening when they're triggered @param InFlag the ignore flag to add or remove @param bIgnore whether to add (true) or remove (false) the flag
- L164 _public prototype_ `virtual void OnActorsCopied(FString& InOutCopiedData, TConstArrayView<AActor*> InCopiedActors) = 0;` — Should be called when Actors have been copied and give Ava Outliner opportunity to add to the Buffer to copy the Outliner data for those Actors @param InOutCopiedData the data to process / append to for copy @param InCopiedActors the actors to copy
- L171 _public prototype_ `virtual void OnActorsPasted(FStringView InPastedData, const TMap<FName, AActor*>& InPastedActors) = 0;` — Should be called when Actors have been pasted to parse the data that was filled in by IAvaOutliner::OnActorsCopied @param InPastedData pasted string data @param InPastedActors map of the original actor name to its created actor on paste
- L179 _public prototype_ `virtual void OnActorsDuplicated(const TMap<AActor*, AActor*>& InDuplicateActorMap , FAvaOutlinerItemPtr InRelativeItem = nullptr , TOptional<EItemDropZone> InRelativeDropZone = TOptional<EItemDropZone>()) = 0;` — Handles when Actors have been Duplicated @param InDuplicateActorMap the map of the Duplicate Actors to their Templates @param InRelativeItem he item to use as positional reference to where to place the duplicate items in the outliner @param InRelativeDropZone where to put the duplicate items relative to the InRelativeItem (above, below, onto)
- L187 _public prototype_ `virtual void GroupSelection(AActor* InGroupingActor, const TOptional<FAttachmentTransformRules>& InTransformRules) = 0;` — Gets all the Selected Items and puts/attaches them under the given Grouping Actor. Requires that the Grouping Actor is valid and spawned in the World.
- L190 _public prototype_ `virtual void OnObjectSelectionChanged(const FAvaEditorSelection& InEditorSelection) = 0;` — Called when the objects have been selected and notified through USelection Instances in Mode Tools
- L193 _public prototype_ `virtual UWorld* GetWorld() const = 0;` — Gets the World the Outliner is working with
- L196 _public prototype_ `virtual bool IsDefaultWorldActorToHide(const UWorld* const InWorld, const AActor* const InActor) const = 0;` — Returns true if the given actor is a default actor of the given world that will be hidden from the outliner.
- L199 _protected prototype_ `virtual const FAvaOutlinerItemProxyRegistry& GetItemProxyRegistry() const = 0;`

#### Free symbols / members of external scopes

- L42 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnOutlinerLoaded);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Public/IAvaOutlinerModule.h` (Public)


#### class `IAvaOutlinerModule`  
`class IAvaOutlinerModule : public IModuleInterface`  
_L22-81_
- inherits: `IModuleInterface`
- L26 _public function_ `static IAvaOutlinerModule& Get()` — Returns the instance of this module, assuming it's loaded
- L31 _public function_ `static bool IsLoaded()` — Returns whether this module has been loaded
- L36 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnExtendOutlinerToolMenu, UToolMenu*);`
- L39 _public prototype_ `virtual FOnExtendOutlinerToolMenu& GetOnExtendOutlinerItemContextMenu() = 0;` — Option to extend the Outliner Item Context Menu
- L42 _public prototype_ `virtual FAvaOutlinerItemProxyRegistry& GetItemProxyRegistry() = 0;` — Get the Module's Item Proxy Registry. Used as back up in case the Outliner's Instance does not have the Item type registered
- L44 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnExtendItemProxiesForItem, IAvaOutliner&, const FAvaOutlinerItemPtr&, TArray<TSharedPtr<FAvaOutlinerItemProxy>>&);`
- L47 _public prototype_ `virtual FOnExtendItemProxiesForItem& GetOnExtendItemProxiesForItem() = 0;` — Gets the Delegate to call for adding in the Item Proxies to put under the given Item
- L59 _public function_ `InIconCustomization& RegisterOverriddenIcon(InArgsType&&... InArgs)`
- L73 _public function_ `void UnregisterOverriddenIcon(FName InAdditionalKeyParameter)`
- L79 _protected prototype_ `virtual void RegisterOverridenIcon_Internal(const FAvaTypeId& InItemTypeId, const TSharedRef<IAvaOutlinerIconCustomization>& InAvaOutlinerIconCustomization) = 0;`
- L80 _protected prototype_ `virtual void UnregisterOverriddenIcon_Internal(const FAvaTypeId& InItemTypeId, const FName& InSpecializationIdentifier) = 0;`

#### Free symbols / members of external scopes

- L36 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnExtendOutlinerToolMenu, UToolMenu*);`
- L44 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnExtendItemProxiesForItem, IAvaOutliner&, const FAvaOutlinerItemPtr&, TArray<TSharedPtr<FAvaOutlinerItemProxy>>&);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Public/IAvaOutlinerProvider.h` (Public)


#### class `IAvaOutlinerProvider`  
`class IAvaOutlinerProvider`  
_L25-95_
- desc: Provides the Outliner with functionality it is not responsible for Some examples include the World to use, Mode Tools, Duplicating Actors, etc It also allows custom extensibility options for the Outliner
- L28 _public prototype_ `virtual ~IAvaOutlinerProvider() = default;`
- L31 _public function_ `virtual bool ShouldCreateWidget() const` — Whether an Outliner Widget should be created
- L34 _public prototype_ `virtual bool CanOutlinerProcessActorSpawn(AActor* InActor) const = 0;` — Determines whether an Actor can be added and be visible in the Outliner
- L37 _public prototype_ `virtual bool ShouldLockOutliner() const = 0;` — Determines whether the Outliner should be read-only
- L40 _public prototype_ `virtual bool ShouldHideItem(const FAvaOutlinerItemPtr& Item) const = 0;` — An extended check to determine whether Item should be hidden in the Outliner
- L46 _public prototype_ `virtual void OutlinerDuplicateActors(const TArray<AActor*>& InTemplateActors) = 0;` — Called when the Outliner requests the duplicate of the given template actors Implementation must return a map of the Duplicate Actor to the Template Actor
- L51 _public prototype_ `virtual void OutlinerDeleteActors(const TArray<AActor*>& InDeleteActors) = 0;` — Called when the Outliner requests the deletion of the given actors
- L54 _public prototype_ `virtual FEditorModeTools* GetOutlinerModeTools() const = 0;` — Returns the Mode Tools used (e.g. for Selections)
- L57 _public prototype_ `virtual FAvaSceneTree* GetSceneTree() const = 0;` — Returns the Scene Tree to use for the Outliner Tree Ordering
- L60 _public prototype_ `virtual UWorld* GetOutlinerWorld() const = 0;` — Returns the World to use for the Outliner
- L63 _public prototype_ `virtual FTransform GetOutlinerDefaultActorSpawnTransform() const = 0;` — Gets the Default Transform to use when Spawning an Actor from the Outliner (used when there's no info related to Transform)
- L66 _public function_ `virtual void ExtendOutlinerToolBar(UToolMenu* InToolBarMenu)` — Option to quickly extend the Outliner ToolBar without having to implement UToolMenus::Get()->ExtendMenu
- L69 _public function_ `virtual void ExtendOutlinerItemContextMenu(UToolMenu* InItemContextMenu)` — Option to quickly extend the Outliner Item Context Menu without having to implement UToolMenus::Get()->ExtendMenu
- L72 _public function_ `virtual void ExtendOutlinerItemFilters(TArray<TSharedPtr<class IAvaOutlinerItemFilter>>& InItemFilters)` — Extension to add Item Filters to the Outliner
- L75 _public prototype_ `virtual TOptional<EItemDropZone> OnOutlinerItemCanAcceptDrop(const FDragDropEvent& DragDropEvent , EItemDropZone DropZone , FAvaOutlinerItemPtr TargetItem) const = 0;` — Determines whether an external Drag Drop event (i.e. not an Outliner one) can be accepted by the Outliner for a given Target Item
- L80 _public prototype_ `virtual FReply OnOutlinerItemAcceptDrop(const FDragDropEvent& DragDropEvent , EItemDropZone DropZone , FAvaOutlinerItemPtr TargetItem) = 0;` — Processes an external Drag Drop event (i.e. not an Outliner one) for a given Target item
- L85 _public function_ `virtual void NotifyOutlinerItemRenamed(const FAvaOutlinerItemPtr& InItem)` — Called when an Item has been Renamed
- L88 _public function_ `virtual void NotifyOutlinerItemDeleted(const FAvaOutlinerItemPtr& InItem)` — Called when an Item has been deleted
- L91 _public function_ `virtual void NotifyOutlinerItemLockChanged(const FAvaOutlinerItemPtr& InItem)` — Called when an Item's Lock has Changed
- L94 _public prototype_ `virtual const FAttachmentTransformRules& GetTransformRule(bool bIsPrimaryTransformRule) const = 0;` — Returns the transform rule to be applied when nesting items. It can be selected between primary or secondary.

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Public/IAvaOutlinerView.h` (Public)


#### class `IAvaOutlinerView`  
`class IAvaOutlinerView : public TSharedFromThis<IAvaOutlinerView>`  
_L10-19_
- inherits: `TSharedFromThis<IAvaOutlinerView>`
- L13 _public prototype_ `virtual ~IAvaOutlinerView() = default;`
- L16 _public prototype_ `virtual TSharedRef<SWidget> GetOutlinerWidget() const = 0;` — Returns the Outliner Widget. Can be null widget
- L18 _public prototype_ `virtual TSharedPtr<IAvaOutliner> GetOwnerOutliner() const = 0;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Public/Icon/AvaOutlinerIconCustomization.h` (Public)


#### class `IAvaOutlinerIconCustomization`  
`class IAvaOutlinerIconCustomization`  
_L11-21_
- L14 _public prototype_ `virtual ~IAvaOutlinerIconCustomization() = default;`
- L16 _public prototype_ `virtual FName GetOutlinerItemIdentifier() const = 0;`
- L18 _public prototype_ `virtual bool HasOverrideIcon(TSharedPtr<const FAvaOutlinerItem> InOutlinerItem) const = 0;`
- L20 _public prototype_ `virtual FSlateIcon GetOverrideIcon(TSharedPtr<const FAvaOutlinerItem> InOutlinerItem) const = 0;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Public/Icon/AvaOutlinerObjectIconCustomization.h` (Public)


#### class `FAvaOutlinerObjectIconCustomization`  
`class FAvaOutlinerObjectIconCustomization : public IAvaOutlinerIconCustomization`  
_L14-31_
- inherits: `IAvaOutlinerIconCustomization`
- L17 _public prototype_ `FAvaOutlinerObjectIconCustomization(const UClass* InSupportedClass);`
- L19 _public prototype_ `void SetOverriddenIcon(const FOnGetOverriddenObjectIcon& InOverriddenIcon);`
- L23 _private prototype_ `virtual FName GetOutlinerItemIdentifier() const override;`
- L24 _private prototype_ `virtual bool HasOverrideIcon(TSharedPtr<const FAvaOutlinerItem> InOutlinerItem) const override;`
- L25 _private prototype_ `virtual FSlateIcon GetOverrideIcon(TSharedPtr<const FAvaOutlinerItem> InOutlinerItem) const override;`
- L28 _private member_ `FName SupportedClassName;`
- L30 _private member_ `FOnGetOverriddenObjectIcon OnGetOverriddenIcon;`

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FSlateIcon , FOnGetOverriddenObjectIcon, TSharedPtr<const FAvaOutlinerItem> ) class FAvaOutlinerObjectIconCustomization : public IAvaOutlinerIconCustomization { public: FAvaOutlinerObjectIconCustomization(const UClass* InSupportedClass); void SetOverriddenIcon(const FOnGetOverriddenObjectIcon& InOverriddenIcon); private:`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Public/Item/AvaOutlinerActor.h` (Public)


#### class `FAvaOutlinerActor`  
`class FAvaOutlinerActor : public FAvaOutlinerObject`  
_L12-54_
- inherits: `FAvaOutlinerObject`
- desc: Item in Outliner representing an AActor.
- L15 _public prototype_ `UE_AVA_INHERITS_WITH_SUPER(FAvaOutlinerActor, FAvaOutlinerObject);`
- L17 _public prototype_ `FAvaOutlinerActor(IAvaOutliner& InOutliner, AActor* InActor);`
- L20 _public prototype_ `virtual void FindChildren(TArray<FAvaOutlinerItemPtr>& OutChildren, bool bRecursive) override;`
- L21 _public prototype_ `virtual void GetItemProxies(TArray<TSharedPtr<FAvaOutlinerItemProxy>>& OutItemProxies) override;`
- L22 _public function_ `virtual bool IsSortable() const override`
- L23 _public prototype_ `virtual bool CanAddChild(const FAvaOutlinerItemPtr& InChild) const override;`
- L24 _public prototype_ `virtual void OnChildrenAdded(TConstArrayView<FAvaOutlinerItemPtr> InAddedChildren, const FAvaOutlinerAddItemParams& InAddItemParams) override;`
- L25 _public prototype_ `virtual bool RemoveChild(const FAvaOutlinerRemoveItemParams& InRemoveItemParams) override;`
- L26 _public function_ `virtual bool CanBeTopLevel() const override`
- L27 _public prototype_ `virtual bool IsAllowedInOutliner() const override;`
- L28 _public prototype_ `virtual EAvaOutlinerItemViewMode GetSupportedViewModes(const FAvaOutlinerView& InOutlinerView) const override;`
- L29 _public function_ `virtual bool CanReceiveParentVisibilityPropagation() const override`
- L30 _public function_ `virtual bool ShowVisibility(EAvaOutlinerVisibilityType VisibilityType) const override`
- L31 _public prototype_ `virtual bool GetVisibility(EAvaOutlinerVisibilityType VisibilityType) const override;`
- L32 _public prototype_ `virtual void OnVisibilityChanged(EAvaOutlinerVisibilityType VisibilityType, bool bNewVisibility) override;`
- L33 _public function_ `virtual bool CanRename() const override`
- L34 _public prototype_ `virtual bool Rename(const FString& InName) override;`
- L35 _public function_ `virtual bool CanDelete() const override`
- L36 _public function_ `virtual bool Delete() override`
- L37 _public function_ `virtual bool CanLock() const override`
- L38 _public prototype_ `virtual void SetLocked(bool bInIsLocked) override;`
- L39 _public prototype_ `virtual bool IsLocked() const override;`
- L40 _public prototype_ `virtual FText GetDisplayName() const override;`
- L41 _public prototype_ `virtual TArray<FName> GetTags() const override;`
- L42 _public prototype_ `virtual TOptional<EItemDropZone> CanAcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone) override;`
- L43 _public prototype_ `virtual FReply AcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone) override;`
- L46 _public function_ `AActor* GetActor() const`
- L50 _protected prototype_ `virtual void SetObject_Impl(UObject* InObject) override;`
- L53 _protected member_ `TWeakObjectPtr<AActor> Actor;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Public/Item/AvaOutlinerComponent.h` (Public)


#### class `FAvaOutlinerComponent`  
`class FAvaOutlinerComponent : public FAvaOutlinerObject`  
_L12-45_
- inherits: `FAvaOutlinerObject`
- desc: Item in Outliner representing a USceneComponent.
- L15 _public prototype_ `UE_AVA_INHERITS_WITH_SUPER(FAvaOutlinerComponent, FAvaOutlinerObject);`
- L17 _public prototype_ `FAvaOutlinerComponent(IAvaOutliner& InOutliner, USceneComponent* InComponent);`
- L20 _public prototype_ `virtual void FindChildren(TArray<FAvaOutlinerItemPtr>& OutChildren, bool bRecursive) override;`
- L21 _public prototype_ `virtual void GetItemProxies(TArray<TSharedPtr<FAvaOutlinerItemProxy>>& OutItemProxies) override;`
- L22 _public prototype_ `virtual bool CanAddChild(const FAvaOutlinerItemPtr& InChild) const override;`
- L23 _public prototype_ `virtual void OnChildrenAdded(TConstArrayView<FAvaOutlinerItemPtr> InAddedChildren, const FAvaOutlinerAddItemParams& InAddItemParams) override;`
- L24 _public prototype_ `virtual bool RemoveChild(const FAvaOutlinerRemoveItemParams& InRemoveItemParams) override;`
- L25 _public prototype_ `virtual EAvaOutlinerItemViewMode GetSupportedViewModes(const FAvaOutlinerView& InOutlinerView) const override;`
- L26 _public prototype_ `virtual bool IsAllowedInOutliner() const override;`
- L27 _public prototype_ `virtual TSharedRef<SWidget> GenerateLabelWidget(const TSharedRef<SAvaOutlinerTreeRow>& InRow) override;`
- L28 _public function_ `virtual bool CanReceiveParentVisibilityPropagation() const override`
- L29 _public function_ `virtual bool ShowVisibility(EAvaOutlinerVisibilityType VisibilityType) const override`
- L30 _public prototype_ `virtual bool GetVisibility(EAvaOutlinerVisibilityType VisibilityType) const override;`
- L31 _public prototype_ `virtual void OnVisibilityChanged(EAvaOutlinerVisibilityType VisibilityType, bool bNewVisibility) override;`
- L32 _public function_ `virtual bool CanRename() const override`
- L33 _public prototype_ `virtual FLinearColor GetItemColor() const override;`
- L34 _public prototype_ `virtual TArray<FName> GetTags() const override;`
- L37 _public function_ `USceneComponent* GetComponent() const`
- L41 _protected prototype_ `virtual void SetObject_Impl(UObject* InObject) override;`
- L44 _protected member_ `TWeakObjectPtr<USceneComponent> Component;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Public/Item/AvaOutlinerComponentProxy.h` (Public)


#### class `FAvaOutlinerComponentProxy`  
`class FAvaOutlinerComponentProxy : public FAvaOutlinerItemProxy`  
_L7-24_
- inherits: `FAvaOutlinerItemProxy`
- L10 _public prototype_ `UE_AVA_INHERITS_WITH_SUPER(FAvaOutlinerComponentProxy, FAvaOutlinerItemProxy) FAvaOutlinerComponentProxy(IAvaOutliner& InOutliner, const FAvaOutlinerItemPtr& InParentItem);`
- L15 _public prototype_ `virtual FText GetDisplayName() const override;`
- L16 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L17 _public prototype_ `virtual FText GetIconTooltipText() const override;`
- L18 _public prototype_ `virtual EAvaOutlinerItemViewMode GetSupportedViewModes(const FAvaOutlinerView& InOutlinerView) const override;`
- L22 _public prototype_ `virtual void GetProxiedItems(const TSharedRef<IAvaOutlinerItem>& InParent, TArray<FAvaOutlinerItemPtr>& OutChildren, bool bInRecursive) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Public/Item/AvaOutlinerItem.h` (Public)


#### class `FAvaOutlinerItem`  
`class FAvaOutlinerItem : public IAvaOutlinerItem`  
_L13-113_
- inherits: `IAvaOutlinerItem`
- desc: Base Implementation of IAvaOutlinerItem
- L18 _public prototype_ `UE_AVA_INHERITS_WITH_SUPER(FAvaOutlinerItem, IAvaOutlinerItem);`
- L20 _public prototype_ `FAvaOutlinerItem(IAvaOutliner& InOutliner);`
- L25 _public prototype_ `virtual TSharedRef<IAvaOutliner> GetOwnerOutliner() const override;`
- L26 _public prototype_ `virtual bool IsItemValid() const override;`
- L27 _public prototype_ `virtual void RefreshChildren() override;`
- L28 _public function_ `virtual const TArray<FAvaOutlinerItemPtr>& GetChildren() const override`
- L29 _public prototype_ `virtual void FindChildren(TArray<FAvaOutlinerItemPtr>& OutChildren, bool bRecursive) override;`
- L30 _public function_ `virtual TArray<FAvaOutlinerItemPtr>& GetChildrenMutable() override`
- L31 _public function_ `virtual bool IsSortable() const override`
- L32 _public prototype_ `virtual bool CanAddChild(const FAvaOutlinerItemPtr& InChild) const override;`
- L33 _public prototype_ `virtual TArray<FAvaOutlinerItemPtr> AddChildren(const FAvaOutlinerAddItemParams& InAddItemParams) override;`
- L34 _public prototype_ `virtual bool RemoveChild(const FAvaOutlinerRemoveItemParams& InRemoveItemParams) override;`
- L35 _public function_ `virtual FAvaOutlinerItemPtr GetParent() const override`
- L36 _public function_ `virtual bool CanBeTopLevel() const override`
- L37 _public prototype_ `virtual void SetParent(FAvaOutlinerItemPtr InParent) override;`
- L38 _public function_ `virtual bool IsAllowedInOutliner() const override`
- L39 _public prototype_ `virtual EAvaOutlinerItemViewMode GetSupportedViewModes(const FAvaOutlinerView& InOutlinerView) const override;`
- L40 _public prototype_ `virtual FAvaOutlinerItemId GetItemId() const override final;`
- L41 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L42 _public prototype_ `virtual TSharedRef<SWidget> GenerateLabelWidget(const TSharedRef<SAvaOutlinerTreeRow>& InRow) override;`
- L43 _public function_ `virtual bool ShowVisibility(EAvaOutlinerVisibilityType VisibilityType) const override`
- L44 _public function_ `virtual bool CanReceiveParentVisibilityPropagation() const override`
- L45 _public function_ `virtual bool GetVisibility(EAvaOutlinerVisibilityType VisibilityType) const override`
- L46 _public function_ `virtual bool CanAutoExpand() const override`
- L47 _public function_ `virtual bool CanRename() const override`
- L48 _public prototype_ `virtual bool Rename(const FString& InName) override;`
- L49 _public function_ `virtual bool CanDelete() const override`
- L50 _public prototype_ `virtual bool Delete() override;`
- L51 _public function_ `virtual bool CanLock() const override`
- L52 _public prototype_ `virtual void SetLocked(bool bInIsLocked) override;`
- L53 _public function_ `virtual bool IsLocked() const override`
- L54 _public prototype_ `virtual void AddFlags(EAvaOutlinerItemFlags Flags) override;`
- L55 _public prototype_ `virtual void RemoveFlags(EAvaOutlinerItemFlags Flags) override;`
- L56 _public prototype_ `virtual bool HasAnyFlags(EAvaOutlinerItemFlags Flags) const override;`
- L57 _public prototype_ `virtual bool HasAllFlags(EAvaOutlinerItemFlags Flags) const override;`
- L58 _public function_ `virtual void SetFlags(EAvaOutlinerItemFlags InFlags) override`
- L59 _public function_ `virtual EAvaOutlinerItemFlags GetFlags() const override`
- L60 _public prototype_ `virtual TOptional<FAvaOutlinerColorPair> GetColor(bool bRecurse = true) const override;`
- L61 _public prototype_ `virtual TOptional<EItemDropZone> CanAcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone) override;`
- L62 _public prototype_ `virtual FReply AcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone) override;`
- L63 _public prototype_ `virtual FLinearColor GetItemColor() const override;`
- L64 _public function_ `virtual FOnRenameAction& OnRenameAction() override`
- L65 _public function_ `virtual FOnExpansionChanged& OnExpansionChanged() override`
- L70 _protected prototype_ `virtual FAvaOutlinerItemId CalculateItemId() const = 0;` — Gets the Item Id with the latest information (e.g. parent, object, etc)
- L73 _protected prototype_ `void RecalculateItemId();` — Sets the ItemId member var to what CalculateItemId returns
- L77 _protected function_ `void AddChildChecked(const FAvaOutlinerAddItemParams& InAddItemParams)` — `UE_DEPRECATED(5.6, "Use AddChildrenInternal instead")` — The actual implementation of putting the given Item under the Children array
- L83 _protected prototype_ `TArray<FAvaOutlinerItemPtr> AddChildrenInternal(const FAvaOutlinerAddItemParams& InAddItemParams);` — The actual implementation of putting the given Item under the Children array
- L86 _protected prototype_ `bool RemoveChildChecked(const FAvaOutlinerRemoveItemParams& InRemoveItemParams);` — The actual implementation of removing the given item from the Children array
- L89 _protected prototype_ `void HandleNewSortableChildren(TArray<FAvaOutlinerItemPtr> InSortableChildren);` — Careful handling of multiple children being detected and added to this item children array
- L92 _protected prototype_ `FReply CreateItemsFromAssetDrop(const TSharedPtr<FAssetDragDropOp>& AssetDragDropOp, EItemDropZone DropZone, ULevel* Level);` — Handling when an Asset from Content Browser has been dragged on to this item
- L95 _protected member_ `IAvaOutliner& Outliner;` — Reference to the Owning Outliner
- L98 _protected member_ `TWeakPtr<IAvaOutlinerItem> ParentWeak;` — Weak pointer to the Parent Item. Can be null, but if valid, the Parent should have this item in the Children Array
- L101 _protected member_ `TArray<FAvaOutlinerItemPtr> Children;` — Array of Shared pointers to the Child Items. These Items should have their ParentWeak pointing to this item
- L104 _protected member_ `FOnExpansionChanged OnExpansionChangedDelegate;` — Delegate for when Expansion changes in the Item
- L107 _protected member_ `FOnRenameAction OnRenameActionDelegate;` — The delegate for renaming
- L110 _protected member_ `EAvaOutlinerItemFlags ItemFlags = EAvaOutlinerItemFlags::None;` — The current flags set for this item
- L112 _protected member_ `FAvaOutlinerItemId ItemId;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Public/Item/AvaOutlinerItemId.h` (Public)


#### struct `FAvaOutlinerItemId`  
`struct FAvaOutlinerItemId`  
_L14-144_
- desc: Struct to identify an item in the Outliner
- L17 _public prototype_ `FAvaOutlinerItemId() = default;` — Default Ctor. Does not run any CalculateTypeHash so this instance remains invalid
- L24 _public function_ `FAvaOutlinerItemId(const UObject* InObject)` — Ctor used for Objects that appear ONCE in the Outliner (e.g. an Actor or Component), so only the Object itself is needed for the Id for objects that can appear multiple times because they're referenced multiple times, see the ctor below that takes in a Referencing Item and Referencing Id @param InObject the object that the item represents
- L45 _public function_ `FAvaOutlinerItemId(const UObject* InObject, const FAvaOutlinerItemPtr& InReferencingItem, const FString& InReferencingId) : FAvaOutlinerItemId(InReferencingItem->GetItemId())` — Ctor used for Objects that are expected to appear multiple times in the Outliner (e.g. a Material Ref) Example Id #1: [Component Path], [Full Path of Material Asset], [Slot Index] "/Game/World.World:PersistentLevel.StaticMeshActor_0.StaticMeshComponent,/Game/Materials/M_TestMaterial.M_TestMaterial,[Slot 0]" Example Id #2: [Component Path], [Material Instance Dynamic Path], [Slot Index] "/Game/World.World:PersistentLevel.StaticMeshActor_0.StaticMeshComponent,/Game/World.World:PersistentLevel.StaticMeshActor_0.StaticMeshComponent.MaterialInstanceDynamic_0,[Slot 0]" @param InObject the Object being referenced multiple times (e.g. a Material) @param InReferencingItem the Item holding a reference to the object (e.g. a Primitive Comp referencing a Material) @param InReferencingId the Id to differentiate this reference from other references within the same object (e.g. can be slot or property name)
- L59 _public function_ `FAvaOutlinerItemId(const FAvaOutlinerItemPtr& InParentItem, const IAvaOutlinerItemProxyFactory& InItemProxyFactory) : FAvaOutlinerItemId(InParentItem->GetItemId())` — Ctor used for making the Item Id for a item proxy that will be under the given Parent Item. Used when the actual Item Proxy is not created yet, but know it's factory and want to know whether the item proxy already exists @param InParentItem the parent item holding the item proxy @param InItemProxyFactory the factory responsible of creating the item proxy
- L71 _public function_ `FAvaOutlinerItemId(const FAvaOutlinerItemPtr& InParentItem, const IAvaOutlinerItem& InItemProxy) : FAvaOutlinerItemId(InParentItem->GetItemId())` — Ctor used for making the Item Id for a Item Proxy under the given Parent Item. @param InParentItem the parent item holding the item proxy @param InItemProxy the item proxy under the parent item
- L79 _public function_ `FAvaOutlinerItemId(const FString& InUniqueId)` — More flexible option to just specify the string directly. Could be used for folders (e.g. for a nested folder C could be "A/B/C"
- L85 _public function_ `FAvaOutlinerItemId(const FAvaOutlinerItemId& Other)`
- L90 _public function_ `FAvaOutlinerItemId(FAvaOutlinerItemId&& Other) noexcept`
- L95 _public function_ `FAvaOutlinerItemId& operator=(const FAvaOutlinerItemId& Other)`
- L102 _public function_ `FAvaOutlinerItemId& operator=(FAvaOutlinerItemId&& Other) noexcept`
- L109 _public function_ `bool operator==(const FAvaOutlinerItemId& Other) const`
- L114 _public function_ `bool operator!=(const FAvaOutlinerItemId& Other) const`
- L120 _public function_ `bool IsValid() const` — Returns whether this Id has a cached hash (i.e. ran any ctor except the default one)
- L127 _public function_ `FString GetStringId() const`
- L130 _private function_ `FString GetObjectPath(const UObject* InObject) const`
- L135 _private function_ `void CalculateTypeHash()`
- L141 _private member_ `FString Id;`
- L142 _private member_ `uint32 CachedHash = 0;`
- L143 _private member_ `bool bHasCachedHash = false;`

#### Free symbols / members of external scopes

- L122 _function_ `friend uint32 GetTypeHash(const FAvaOutlinerItemId& ItemId)`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Public/Item/AvaOutlinerItemParameters.h` (Public)


#### enum `EAvaOutlinerAddItemFlags`  
`enum class EAvaOutlinerAddItemFlags : uint8`  
_L11-20_
- L13 _public enumerator_ `None = 0`
- L15 _public enumerator_ `AddChildren = 1 << 0` — Also add the children of the given item even if they were not made into their own Add Item Action
- L17 _public enumerator_ `Select = 1 << 1` — Select this Item on Add
- L19 _public enumerator_ `Transact = 1 << 2` — Make a Transaction for this Action

#### struct `FAvaOutlinerAddItemParams`  
`struct FAvaOutlinerAddItemParams`  
_L23-69_
- L27 _public prototype_ `FAvaOutlinerAddItemParams() = default;` — Note: We need to explicitly disable warnings on these constructors/operators for clang to be happy with deprecated variables
- L28 _public prototype_ `~FAvaOutlinerAddItemParams() = default;`
- L29 _public prototype_ `FAvaOutlinerAddItemParams(const FAvaOutlinerAddItemParams&) = default;`
- L30 _public prototype_ `FAvaOutlinerAddItemParams(FAvaOutlinerAddItemParams&&) = default;`
- L31 _public prototype_ `FAvaOutlinerAddItemParams& operator=(const FAvaOutlinerAddItemParams&) = default;`
- L32 _public prototype_ `FAvaOutlinerAddItemParams& operator=(FAvaOutlinerAddItemParams&&) = default;`
- L35 _public function_ `explicit FAvaOutlinerAddItemParams(const FAvaOutlinerItemPtr& InItem , EAvaOutlinerAddItemFlags InFlags = EAvaOutlinerAddItemFlags::None , const FAvaOutlinerItemPtr& InRelativeItem = nullptr , TOptional<EItemDropZone> InRelativeDropZone = TOptional<EItemDropZone>()) : RelativeItem(InRelativeItem) , RelativeDropZone(InRelativeDropZone) , Flags(InFlags)`
- L50 _public member_ `FAvaOutlinerItemPtr Item;` — `UE_DEPRECATED(5.6, "Use 'Items' instead")`
- L53 _public member_ `TArray<FAvaOutlinerItemPtr, TInlineAllocator<1>> Items;` — The items to add
- L56 _public member_ `FAvaOutlinerItemPtr RelativeItem;` — The Item to use as base in where to place the Item
- L59 _public member_ `TOptional<EItemDropZone> RelativeDropZone;` — The Placement Order from the Relative Item (Onto/Inside, Above, Below)
- L62 _public member_ `EAvaOutlinerAddItemFlags Flags = EAvaOutlinerAddItemFlags::None;` — Some Extra Flags for what to do when Adding or After Adding the Items
- L65 _public member_ `EAvaOutlinerItemSelectionFlags SelectionFlags = EAvaOutlinerItemSelectionFlags::None;` — Flags to Indicate how we should Select the Item. This only applies if bool bSelectItem is true
- L68 _public member_ `TOptional<FAttachmentTransformRules> AttachmentTransformRules;` — Optional Transform override Rule when Attaching Items

#### struct `FAvaOutlinerRemoveItemParams`  
`struct FAvaOutlinerRemoveItemParams`  
_L71-82_
- L73 _public function_ `FAvaOutlinerRemoveItemParams(const FAvaOutlinerItemPtr& InItem = nullptr) : Item(InItem)`
- L78 _public member_ `FAvaOutlinerItemPtr Item;`
- L81 _public member_ `TOptional<FDetachmentTransformRules> DetachmentTransformRules;` — Optional Transform override Rule when Detaching Items

#### Free symbols / members of external scopes

- L21 _prototype_ `ENUM_CLASS_FLAGS(EAvaOutlinerAddItemFlags);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Public/Item/AvaOutlinerItemProxy.h` (Public)


#### class `FAvaOutlinerItemProxy`  
`class FAvaOutlinerItemProxy : public FAvaOutlinerItem`  
_L14-45_
- inherits: `FAvaOutlinerItem`
- desc: Item Proxies are Outliner Items that have as only purpose to group and hold common items together. The description or name of such commonality between these Items should be the name of the Proxy that holds them. NOTE: Although Item Proxies by default require to have a Parent to Show in Outliner, they can be created without parent as means to get overriden behavior (e.g. DisplayName, Icon, etc)
- L17 _public prototype_ `UE_AVA_INHERITS_WITH_SUPER(FAvaOutlinerItemProxy, FAvaOutlinerItem);`
- L19 _public prototype_ `FAvaOutlinerItemProxy(IAvaOutliner& InOutliner, const FAvaOutlinerItemPtr& InParentItem);`
- L22 _public prototype_ `virtual bool IsItemValid() const override;`
- L23 _public prototype_ `virtual void FindChildren(TArray<FAvaOutlinerItemPtr>& OutChildren, bool bRecursive) override final;`
- L24 _public prototype_ `virtual void SetParent(FAvaOutlinerItemPtr InParent) override;`
- L25 _public prototype_ `virtual EAvaOutlinerItemViewMode GetSupportedViewModes(const FAvaOutlinerView& InOutlinerView) const override;`
- L26 _public prototype_ `virtual bool CanAutoExpand() const override;`
- L27 _public function_ `virtual FText GetClassName() const override`
- L30 _public function_ `void SetPriority(uint32 InPriority)`
- L32 _public function_ `uint32 GetPriority() const`
- L35 _public prototype_ `virtual void GetProxiedItems(const TSharedRef<IAvaOutlinerItem>& InParent, TArray<FAvaOutlinerItemPtr>& OutChildren, bool bInRecursive) = 0;` — Gets the Items that this Item Proxy is representing / holding (i.e. children)
- L39 _protected prototype_ `virtual FAvaOutlinerItemId CalculateItemId() const override;`
- L44 _private member_ `uint32 Priority = 0;` — This Item Proxy's Order Priority (i.e. Highest priority is placed topmost or leftmost (depending on Orientation). Priority 0 is lowest priority

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Public/Item/AvaOutlinerItemUtils.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace AvaOutliner` (scope `UE`)
- L14 _prototype_ `bool CompareOutlinerItemOrder(const FAvaOutlinerItemPtr& A, const FAvaOutlinerItemPtr& B);` (scope `UE::AvaOutliner`) — Compares the absolute order of the items in the Outliner and returns true if A comes before B in the outliner. Useful to use when sorting Items.
- L17 _prototype_ `void SplitItems(const TArray<FAvaOutlinerItemPtr>& InItems , TArray<FAvaOutlinerItemPtr>& OutSortable , TArray<FAvaOutlinerItemPtr>& OutUnsortable);` (scope `UE::AvaOutliner`) — Returns two subset arrays of Items: one is containing only Sortable Items and the other Non Sortable Items

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Public/Item/AvaOutlinerLevel.h` (Public)


#### class `FAvaOutlinerLevel`  
`class FAvaOutlinerLevel : public FAvaOutlinerObject`  
_L12-40_
- inherits: `FAvaOutlinerObject`
- desc: Item in Outliner representing a Level.
- L15 _public prototype_ `UE_AVA_INHERITS_WITH_SUPER(FAvaOutlinerLevel, FAvaOutlinerObject);`
- L17 _public prototype_ `FAvaOutlinerLevel(IAvaOutliner& InOutliner, ULevel* InLevel);`
- L20 _public prototype_ `virtual void FindChildren(TArray<FAvaOutlinerItemPtr>& OutChildren, bool bRecursive) override;`
- L21 _public prototype_ `virtual bool RemoveChild(const FAvaOutlinerRemoveItemParams& InRemoveItemParams) override;`
- L22 _public prototype_ `virtual EAvaOutlinerItemViewMode GetSupportedViewModes(const FAvaOutlinerView& InOutlinerView) const override;`
- L23 _public function_ `virtual bool CanBeTopLevel() const override`
- L24 _public function_ `virtual bool CanRename() const override`
- L25 _public function_ `virtual bool CanLock() const override`
- L26 _public prototype_ `virtual FText GetDisplayName() const override;`
- L27 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L28 _public prototype_ `virtual TOptional<EItemDropZone> CanAcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone) override;`
- L29 _public prototype_ `virtual FReply AcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone) override;`
- L32 _public prototype_ `ULevel* GetLevel() const;`
- L36 _protected prototype_ `virtual void SetObject_Impl(UObject* InObject) override;`
- L39 _protected member_ `TWeakObjectPtr<ULevel> LevelWeak;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Public/Item/AvaOutlinerMaterial.h` (Public)


#### class `FAvaOutlinerMaterial`  
`class FAvaOutlinerMaterial : public FAvaOutlinerObjectReference`  
_L14-46_
- inherits: `FAvaOutlinerObjectReference`
- desc: Item in Outliner representing a Material. Inherits from FAvaOutlinerObjectReference as multiple objects can have the same material
- L17 _public prototype_ `UE_AVA_INHERITS_WITH_SUPER(FAvaOutlinerMaterial, FAvaOutlinerObjectReference) FAvaOutlinerMaterial(IAvaOutliner& InOutliner , UMaterialInterface* InMaterial , const FAvaOutlinerItemPtr& InReferencingItem , int32 InMaterialIndex);`
- L24 _public function_ `UMaterialInterface* GetMaterial() const`
- L27 _public prototype_ `virtual TOptional<EItemDropZone> CanAcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone) override;`
- L28 _public prototype_ `virtual FReply AcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone) override;`
- L29 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L33 _protected prototype_ `UPrimitiveComponent* GetReferencingPrimitive() const;`
- L35 _protected prototype_ `void OnMaterialChanged();`
- L38 _protected prototype_ `virtual void SetObject_Impl(UObject* InObject) override;`
- L41 _protected member_ `TWeakObjectPtr<UMaterialInterface> Material;`
- L43 _protected member_ `FSlateIcon MaterialIcon;`
- L45 _protected member_ `int32 MaterialIndex = 0;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Public/Item/AvaOutlinerMaterialProxy.h` (Public)


#### class `FAvaOutlinerMaterialProxy`  
`class FAvaOutlinerMaterialProxy : public FAvaOutlinerItemProxy`  
_L8-37_
- inherits: `FAvaOutlinerItemProxy`
- L11 _public prototype_ `UE_AVA_INHERITS_WITH_SUPER(FAvaOutlinerMaterialProxy, FAvaOutlinerItemProxy);`
- L13 _public prototype_ `FAvaOutlinerMaterialProxy(IAvaOutliner& InOutliner, const FAvaOutlinerItemPtr& InParentItem);`
- L18 _public prototype_ `virtual void OnItemRegistered() override;`
- L19 _public prototype_ `virtual void OnItemUnregistered() override;`
- L20 _public prototype_ `virtual FText GetDisplayName() const override;`
- L21 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L22 _public prototype_ `virtual FText GetIconTooltipText() const override;`
- L26 _public prototype_ `virtual void GetProxiedItems(const TSharedRef<IAvaOutlinerItem>& InParent, TArray<FAvaOutlinerItemPtr>& OutChildren, bool bInRecursive) override;`
- L30 _private prototype_ `void BindDelegates();`
- L32 _private prototype_ `void UnbindDelegates();`
- L34 _private prototype_ `void OnObjectPropertyChanged(UObject* InObject, struct FPropertyChangedEvent& InPropertyChangedEvent);`
- L36 _private member_ `FDelegateHandle OnObjectPropertyChangedHandle;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Public/Item/AvaOutlinerObject.h` (Public)


#### class `FAvaOutlinerObject`  
`class FAvaOutlinerObject : public FAvaOutlinerItem`  
_L9-42_
- inherits: `FAvaOutlinerItem`
- desc: Item Class that represents a UObject
- L12 _public prototype_ `UE_AVA_INHERITS_WITH_SUPER(FAvaOutlinerObject, FAvaOutlinerItem);`
- L14 _public prototype_ `FAvaOutlinerObject(IAvaOutliner& InOutliner, UObject* InObject);`
- L17 _public prototype_ `virtual bool IsItemValid() const override;`
- L18 _public prototype_ `virtual void Select(FAvaOutlinerScopedSelection& InSelection) const override;`
- L19 _public prototype_ `virtual bool IsSelected(const FAvaOutlinerScopedSelection& InSelection) const override;`
- L20 _public prototype_ `virtual FText GetDisplayName() const override;`
- L21 _public prototype_ `virtual FText GetClassName() const override;`
- L22 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L23 _public prototype_ `virtual FText GetIconTooltipText() const override;`
- L24 _public prototype_ `virtual bool IsAllowedInOutliner() const override;`
- L25 _public prototype_ `virtual void OnObjectsReplaced(const TMap<UObject*, UObject*>& InReplacementMap, bool bRecursive) override;`
- L26 _public function_ `virtual bool CanRename() const override`
- L27 _public prototype_ `virtual bool Rename(const FString& InName) override;`
- L30 _public function_ `UObject* GetObject() const`
- L32 _public prototype_ `void SetObject(UObject* InObject);`
- L36 _protected prototype_ `virtual FAvaOutlinerItemId CalculateItemId() const override;`
- L39 _protected prototype_ `virtual void SetObject_Impl(UObject* InObject);`
- L41 _protected member_ `TWeakObjectPtr<UObject> Object;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Public/Item/AvaOutlinerObjectReference.h` (Public)


#### class `FAvaOutlinerSharedObject`  
`class FAvaOutlinerSharedObject : public FAvaOutlinerObject`  
_L19-39_
- inherits: `FAvaOutlinerObject`
- desc: Object Item that will be shared across multiple objects (e.g. Materials). This is not an Item added directly to the Outliner directly but rather shown through its Reference Items. For Example, for a given material that is used across multiple Items, the Material Object itself would be considered a FAvaOutlinerSharedObject but the actual Item in the Outliner shown will be a FAvaOutlinerObjectReference. @see FAvaOutlinerObjectReference
- L22 _public prototype_ `UE_AVA_INHERITS_WITH_SUPER(FAvaOutlinerSharedObject, FAvaOutlinerObject);`
- L24 _public prototype_ `FAvaOutlinerSharedObject(IAvaOutliner& InOutliner, UObject* InObject);`
- L27 _public function_ `virtual bool IsAllowedInOutliner() const override`
- L28 _public function_ `virtual bool CanBeTopLevel() const override`
- L31 _public prototype_ `void AddReference(const TSharedRef<FAvaOutlinerObjectReference>& InObjectReference);`
- L33 _public prototype_ `void RemoveReference(const TSharedRef<FAvaOutlinerObjectReference>& InObjectReference);`
- L35 _public prototype_ `TArray<FAvaOutlinerItemPtr> GetObjectReferences() const;`
- L38 _private member_ `TArray<TWeakPtr<FAvaOutlinerObjectReference>> ObjectReferences;`

#### class `FAvaOutlinerObjectReference`  
`class FAvaOutlinerObjectReference : public FAvaOutlinerObject`  
_L45-78_
- inherits: `FAvaOutlinerObject`
- desc: Reference Item of FAvaOutlinerSharedObject that holds an Object that is likely used across other items in the Outliner. @see FAvaOutlinerSharedObject
- L48 _public prototype_ `UE_AVA_INHERITS_WITH_SUPER(FAvaOutlinerObjectReference, FAvaOutlinerObject);`
- L50 _public prototype_ `FAvaOutlinerObjectReference(IAvaOutliner& InOutliner , UObject* InObject , const FAvaOutlinerItemPtr& InReferencingItem , const FString& InReferenceId);`
- L56 _public prototype_ `virtual void OnItemRegistered() override;`
- L57 _public prototype_ `virtual void OnItemUnregistered() override;`
- L58 _public prototype_ `virtual bool IsItemValid() const override;`
- L59 _public prototype_ `virtual FText GetDisplayName() const override;`
- L62 _public function_ `FAvaOutlinerItemPtr GetReferencingItem() const`
- L66 _protected prototype_ `virtual FAvaOutlinerItemId CalculateItemId() const override;`
- L70 _protected member_ `FAvaOutlinerItemWeakPtr ReferencingItemWeak;` — The item referencing the object (e.g. a Component item holding reference of a Material)
- L77 _protected member_ `FString ReferenceId;` — Id to distinguish the reference from other references held by the same Referencing Item. This reference Id can be the for example a slot index of the material in a primitive component or can be the uproperty name of the variable holding the reference

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Public/Item/IAvaOutlinerItem.h` (Public)


#### class `IAvaOutlinerItem`  
`class IAvaOutlinerItem : public IAvaTypeCastable, public TSharedFromThis<IAvaOutlinerItem>`  
_L31-348_
- inherits: `IAvaTypeCastable,TSharedFromThis<IAvaOutlinerItem>`
- desc: An Outliner Item is the class that represents a Single Element (i.e. Node) in the Outliner Tree. This can be an Item that represents an Object (e.g. Actor,Component) or a Folder, or something else.
- L34 _protected typedef_ `using IndexType = TArray<IAvaOutlinerItem>::SizeType;`
- L37 _public prototype_ `UE_AVA_INHERITS(IAvaOutlinerItem, IAvaTypeCastable);`
- L40 _public function_ `virtual void Select(FAvaOutlinerScopedSelection& InSelection) const` — Used to signal the Scoped Selection that this Item should be Selected
- L43 _public function_ `virtual bool IsSelected(const FAvaOutlinerScopedSelection& InSelection) const` — Determines whether the given Item is selected in the given Scoped Selection
- L46 _public function_ `virtual bool IsSelectable() const` — Whether the Item can be selected in Outliner at all
- L49 _public prototype_ `virtual TSharedRef<IAvaOutliner> GetOwnerOutliner() const = 0;` — Gets the Outliner that owns this Item
- L52 _public prototype_ `virtual bool IsItemValid() const = 0;` — Determines whether the Item properties are in a valid state
- L55 _public function_ `virtual void OnItemRegistered()` — Called when the Item has been registered into the Outliner
- L58 _public function_ `virtual void OnItemUnregistered()` — Called when the Item has been unregistered from the Outliner
- L61 _public function_ `virtual void OnItemSelectionChanged(bool bInIsSelected)` — Called when the Item been selected/deselected from the Tree View
- L64 _public prototype_ `virtual void RefreshChildren() = 0;` — Refreshes what the Parent and Children are of this Item. (not recursive!)
- L67 _public function_ `virtual void ResetChildren()` — Resets both the Cached Visible Children and Children (before doing so, sets all child's parents to null)
- L84 _public prototype_ `virtual bool IsSortable() const = 0;` — Determines whether this item can be sorted by the Outliner or not. Unsorted Items usually mean that they have their own way of sorting that Outliner's Item Sorting Data should not interfere with. Note: Unsorted Children go before Sorted Items (e.g. Item Proxies go first before Actors below a Parent)
- L87 _public prototype_ `virtual bool CanAddChild(const FAvaOutlinerItemPtr& InChild) const = 0;` — Determines whether the given Child is supported and can be added under this Item
- L94 _public function_ `virtual bool AddChild(const FAvaOutlinerAddItemParams& InAddItemParams) final` — `UE_DEPRECATED(5.6, "Use AddChildren instead")` — Adds another Child under this Item if such Item is supported. Returns true if it did, false if it could not add it (e.g. item not supported).
- L103 _public prototype_ `virtual TArray<FAvaOutlinerItemPtr> AddChildren(const FAvaOutlinerAddItemParams& InAddItemParams) = 0;` — Adds the items in the add items struct under this item if such items are supported. Returns the children that were successfully added
- L106 _public function_ `virtual void OnChildrenAdded(TConstArrayView<FAvaOutlinerItemPtr> InAddedChildren, const FAvaOutlinerAddItemParams& InAddItemParams)` — Called when children have been added to this item
- L112 _public prototype_ `virtual bool RemoveChild(const FAvaOutlinerRemoveItemParams& InRemoveItemParams) = 0;` — Removes the given child from this Item if it was ever indeed a child. Returns true if the removal did happen.
- L115 _public prototype_ `virtual void FindChildren(TArray<FAvaOutlinerItemPtr>& OutChildren, bool bRecursive) = 0;` — Figures out the Children of this Item. This is only relevant for items that do have that functionality (e.g. Components or Actors)
- L117 _public function_ `void FindValidChildren(TArray<FAvaOutlinerItemPtr>& OutChildren, bool bRecursive)`
- L129 _public function_ `virtual void GetItemProxies(TArray<TSharedPtr<FAvaOutlinerItemProxy>>& OutItemProxies)` — Gets the Item Proxies for this Item (e.g. Component Item that represent Primitives add in a Material Proxy to display)
- L136 _public function_ `virtual TArray<FAvaOutlinerItemPtr> FindPath(const TArray<FAvaOutlinerItemPtr>& Items) const` — Tries to Find the First Path of Descendants (not including self) that lead to a given Item in the Set. The last item is the Item in the Set that was found so path might be A/B/C/.../ItemInSet  where A is Child of This. Returns Empty array if failed.
- L159 _public prototype_ `virtual const TArray<FAvaOutlinerItemPtr>& GetChildren() const = 0;` — Gets the current Child Items of this Item
- L162 _public prototype_ `virtual TArray<FAvaOutlinerItemPtr>& GetChildrenMutable() = 0;` — Gets the current Child Items of this Item
- L169 _public function_ `virtual IndexType GetChildIndex(const FAvaOutlinerItemPtr& ChildItem) const` — Gets the Index that the given Child Item is at. NOTE: This includes HIDDEN items as Item Visibility is relative to each Outliner View. To consider only Visible Items, use FAvaOutlinerView::GetVisibleChildAt.
- L179 _public function_ `virtual FAvaOutlinerItemPtr GetChildAt(IndexType Index) const` — Gets the Child Item at the given Index. NOTE: This includes HIDDEN items as Item Visibility is relative to each Outliner View. To consider only Visible Items, use FAvaOutlinerView::GetVisibleChildAt.
- L190 _public prototype_ `virtual FAvaOutlinerItemPtr GetParent() const = 0;` — Gets the Parent of this Item. Should only be null prior to registering it in Outliner or if its Root Item
- L196 _public prototype_ `virtual bool CanBeTopLevel() const = 0;` — Whether this Item can be at the Top Level just beneath the Root, or it needs to always be under some other Item E.g. Actors can be Top Level, but Components or Materials can't
- L199 _public prototype_ `virtual void SetParent(FAvaOutlinerItemPtr InParent) = 0;` — Sets the Parent. Note that the Parent must've already have this instance as a child (check is done)
- L202 _public prototype_ `virtual FAvaOutlinerItemId GetItemId() const = 0;` — Gets the Id of this Item
- L205 _public prototype_ `virtual bool IsAllowedInOutliner() const = 0;` — Returns whether this Item (and what it represents) should be allowed to be registered in Outliner
- L208 _public prototype_ `virtual FText GetDisplayName() const = 0;` — Gets the Display Name Text of the Item
- L211 _public prototype_ `virtual FText GetClassName() const = 0;` — Gets the Class/Type of this Item (e.g. for Items that represent UObjects, it will be the UObject class)
- L213 _public prototype_ `virtual FSlateIcon GetIcon() const = 0;`
- L215 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const = 0;`
- L217 _public prototype_ `virtual FText GetIconTooltipText() const = 0;`
- L220 _public prototype_ `virtual EAvaOutlinerItemViewMode GetSupportedViewModes(const FAvaOutlinerView& InOutlinerView) const = 0;` — Gets the View Modes that this Item Supports
- L223 _public function_ `virtual bool IsViewModeSupported(EAvaOutlinerItemViewMode InViewMode, const FAvaOutlinerView& InOutlinerView) const` — Whether this Item should be visualized in the given View Mode, for the given Outliner View
- L233 _public function_ `virtual void OnObjectsReplaced(const TMap<UObject*, UObject*>& InReplacementMap, bool bRecursive)` — Called when objects have been replaced on the Engine side. Used to replace any UObjects used by this item @param InReplacementMap the map of old object that is garbage to the new object that replaced it @param bRecursive whether to recurse this same function to children items
- L248 _public prototype_ `virtual TSharedRef<SWidget> GenerateLabelWidget(const TSharedRef<SAvaOutlinerTreeRow>& InRow) = 0;` — Function responsible of Generating the Label Widget for this Item (i.e. the column containing the Icon and the Name)
- L251 _public prototype_ `virtual bool ShowVisibility(EAvaOutlinerVisibilityType VisibilityType) const = 0;` — Whether this Item supports Visibility for the Given Type
- L254 _public prototype_ `virtual bool CanReceiveParentVisibilityPropagation() const = 0;` — Whether a change in Parent Visibility should also affect this Item's Visibility
- L257 _public prototype_ `virtual bool GetVisibility(EAvaOutlinerVisibilityType VisibilityType) const = 0;` — Whether this Item is currently visible or not for the Given Type
- L260 _public function_ `virtual void OnVisibilityChanged(EAvaOutlinerVisibilityType VisibilityType, bool bNewVisibility)` — Called when the Visibility on Item has been changed on the Outliner side
- L267 _public typedef_ `using FOnExpansionChanged = TMulticastDelegate<void(const TSharedPtr<FAvaOutlinerView>&, bool)>;` — Delegate signature for when the Item Expansion Changes const TSharedPtr<FAvaOutlinerView>& - The Outliner View where this Expansion happened bool - Whether the Item is expanded
- L270 _public prototype_ `virtual FOnExpansionChanged& OnExpansionChanged() = 0;` — Called when Expansion state (Expanded/Collapsed) has been changed
- L273 _public prototype_ `virtual bool CanAutoExpand() const = 0;` — Whether the Item is able to expand when AutoExpand functionality is enabled
- L276 _public prototype_ `virtual bool CanRename() const = 0;` — Whether this Item can be renamed or not
- L279 _public prototype_ `virtual bool Rename(const FString& InName) = 0;` — The implementation to rename the item (e.g. for AActor it will be the Actor Label that is changed)
- L282 _public prototype_ `virtual bool CanDelete() const = 0;` — Whether this Item can be deleted or not
- L285 _public prototype_ `virtual bool Delete() = 0;` — The implementation to delete the item
- L288 _public prototype_ `virtual bool CanLock() const = 0;` — Whether an Item can be Locked in any kind. E.g. Actors can be location-locked
- L291 _public prototype_ `virtual void SetLocked(bool bInIsLocked) = 0;` — Lock/Unlock the Item
- L294 _public prototype_ `virtual bool IsLocked() const = 0;` — Whether the Item is currently Locked
- L296 _public prototype_ `virtual void AddFlags(EAvaOutlinerItemFlags Flag) = 0;`
- L298 _public prototype_ `virtual void RemoveFlags(EAvaOutlinerItemFlags Flag) = 0;`
- L300 _public prototype_ `virtual bool HasAnyFlags(EAvaOutlinerItemFlags Flag) const = 0;`
- L302 _public prototype_ `virtual bool HasAllFlags(EAvaOutlinerItemFlags Flag) const = 0;`
- L304 _public prototype_ `virtual void SetFlags(EAvaOutlinerItemFlags InFlags) = 0;`
- L306 _public prototype_ `virtual EAvaOutlinerItemFlags GetFlags() const = 0;`
- L309 _public function_ `virtual TArray<FName> GetTags() const` — Gets the Tags found for this Item (e.g. for Actors, actor tags and for Components Component Tags)
- L312 _public prototype_ `virtual TOptional<FAvaOutlinerColorPair> GetColor(bool bRecurse = true) const = 0;` — returns the Item's Color Name and Color (either inherited if bRecurse is true, or explicit if false)
- L315 _public function_ `int32 GetItemTreeHeight() const` — Returns the item's height in tree, Root Item should return 0 as it has no Parent
- L332 _public typedef_ `using FOnRenameAction = TMulticastDelegate<void(EAvaOutlinerRenameAction, const TSharedPtr<FAvaOutlinerView>&)>;` — Delegate signature for relaying an Item Rename action EAvaOutlinerRenameAction the type of action being relayed (e.g. request a rename, or notify rename complete, etc) const TSharedPtr<FAvaOutlinerView>& - The Outliner View where the rename action is taking place
- L335 _public prototype_ `virtual FOnRenameAction& OnRenameAction() = 0;` — Broadcasts whenever a rename action takes place from a given view (e.g. when pressing "F2" to rename, or committing the rename text)
- L338 _public prototype_ `virtual TOptional<EItemDropZone> CanAcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone) = 0;` — Determines if and where the incoming Drag Drop Event can be processed by this item
- L341 _public prototype_ `virtual FReply AcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone) = 0;` — Processes the Drag and Drop Event for this Item
- L344 _public prototype_ `virtual FLinearColor GetItemColor() const = 0;` — Gets the Brush Color to use for the Item in the Outliner (e.g. Components should be grayed out a bit)
- L347 _public function_ `bool IsIgnoringPendingKill() const` — Whether Ignoring Pending Kill. Useful to get underlying UObjects that are pending kill and get the pointer to it and not a null value

#### struct `FAvaOutlinerItemFlagGuard`  
`struct FAvaOutlinerItemFlagGuard`  
_L351-375_
- desc: Adds Scoped Item Flags, removes them when out of scope. Useful for temp checks like IgnorePendingKill
- L353 _public function_ `FAvaOutlinerItemFlagGuard(FAvaOutlinerItemPtr InItem, EAvaOutlinerItemFlags ItemFlags)`
- L363 _public function_ `~FAvaOutlinerItemFlagGuard()`
- L372 _protected member_ `FAvaOutlinerItemPtr Item;`
- L374 _protected member_ `EAvaOutlinerItemFlags OldItemFlags;`

#### Free symbols / members of external scopes

- L123 _function_ `` (scope `IAvaOutlinerItem::FindValidChildren`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Public/ItemProxies/AvaOutlinerItemProxyRegistry.h` (Public)


#### class `FAvaOutlinerItemProxyRegistry`  
`class FAvaOutlinerItemProxyRegistry`  
_L16-80_
- desc: Handles registering an Outliner Item Type with an Outliner Item Proxy Factory that creates the respective IAvaOutlinerItemProxy @see IAvaOutlinerItemProxy
- L22 _public function_ `void RegisterItemProxyFactory(InArgTypes&&... InArgs)`
- L34 _public function_ `void RegisterItemProxyWithDefaultFactory()`
- L41 _public function_ `template<typename InItemProxyType, typename = typename TEnableIf<TIsDerivedFrom<InItemProxyType, FAvaOutlinerItemProxy>::IsDerived>::Type> void UnregisterItemProxyFactory()` — Unregisters the given Item Type from having an Item Proxy Factory
- L46 _public function_ `void UnregisterItemProxyFactory(FName InItemProxyTypeName)`
- L52 _public function_ `void UnregisterAllItemProxyFactories()` — Unregisters all the Item Proxy Factories for this Instance
- L58 _public function_ `IAvaOutlinerItemProxyFactory* GetItemProxyFactory(FName InItemProxyTypeName) const` — Gets the Item Proxy Factory for the given Item Proxy Type Name. Returns nullptr if not found
- L69 _public function_ `template<typename InItemProxyType, typename = typename TEnableIf<TIsDerivedFrom<InItemProxyType, FAvaOutlinerItemProxy>::IsDerived>::Type> IAvaOutlinerItemProxyFactory* GetItemProxyFactory() const` — Gets the Item Proxy Factory if it was registered with the Item Proxy Type Name. Returns nullptr if not found
- L75 _public function_ `void GetRegisteredItemProxyTypeNames(TSet<FName>& OutItemProxyTypeNames) const` — Gets all the Item Proxy Type Names that exist in this registry
- L79 _private member_ `TMap<FName, TSharedRef<IAvaOutlinerItemProxyFactory>> ItemProxyFactories;` — Map of the Item Proxy Type Name and its Item Proxy Factory

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Public/ItemProxies/Factories/AvaOutlinerItemProxyDefaultFactory.h` (Public)


#### class `TAvaOutlinerItemProxyDefaultFactoryBase`  
`class TAvaOutlinerItemProxyDefaultFactoryBase : public IAvaOutlinerItemProxyFactory`  
_L14-30_
- inherits: `IAvaOutlinerItemProxyFactory`
- L17 _public function_ `virtual FName GetItemProxyTypeName() const override`
- L24 _protected function_ `template<typename... InArgTypes> TSharedRef<FAvaOutlinerItemProxy> DefaultCreateItemProxy(InArgTypes&&... InArgs)`

#### class `TAvaOutlinerItemProxyDefaultFactory`  
`class TAvaOutlinerItemProxyDefaultFactory : public TAvaOutlinerItemProxyDefaultFactoryBase<InItemProxyType, InItemProxyPriority>`  
_L34-41_
- inherits: `TAvaOutlinerItemProxyDefaultFactoryBase<InItemProxyType,InItemProxyPriority>`
- L37 _public function_ `virtual TSharedPtr<FAvaOutlinerItemProxy> CreateItemProxy(IAvaOutliner& InOutliner, const FAvaOutlinerItemPtr& InParentItem) override`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Public/ItemProxies/IAvaOutlinerItemProxyFactory.h` (Public)


#### class `IAvaOutlinerItemProxyFactory`  
`class IAvaOutlinerItemProxyFactory`  
_L16-26_
- desc: Item Proxy Factories are the classes that instance or get the existing Outliner Item Proxies for a given Item @see IAvaOutlinerItemProxy
- L19 _public prototype_ `virtual ~IAvaOutlinerItemProxyFactory() = default;`
- L22 _public prototype_ `virtual FName GetItemProxyTypeName() const = 0;` — Gets the Type Name of the Item Proxy the Factory creates
- L25 _public prototype_ `virtual TSharedPtr<FAvaOutlinerItemProxy> CreateItemProxy(IAvaOutliner& InOutliner, const FAvaOutlinerItemPtr& InParentItem) = 0;` — Returns a newly created instance of the Relevant Item Proxy if successful

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Public/Selection/AvaOutlinerScopedSelection.h` (Public)


#### enum `EAvaOutlinerScopedSelectionPurpose`  
`enum class EAvaOutlinerScopedSelectionPurpose`  
_L11-17_
- L14 _public enumerator_ `Sync` — At the end of the Scope, it will set whatever has been added to the Selected List to be the new Selection
- L16 _public enumerator_ `Read` — Used only to check for whether an Object is Selected or not. Cannot execute "Select"

#### class `FAvaOutlinerScopedSelection`  
`class FAvaOutlinerScopedSelection`  
_L20-47_
- desc: Handler to Sync Selection from Outliner to the Editor Mode Tools
- L23 _public prototype_ `explicit FAvaOutlinerScopedSelection(const FEditorModeTools& InEditorModeTools , EAvaOutlinerScopedSelectionPurpose InPurpose = EAvaOutlinerScopedSelectionPurpose::Read);`
- L26 _public prototype_ `~FAvaOutlinerScopedSelection();`
- L28 _public prototype_ `void Select(UObject* InObject);`
- L30 _public prototype_ `bool IsSelected(const UObject* InObject) const;`
- L32 _public prototype_ `const FEditorModeTools& GetEditorModeTools() const;`
- L35 _private prototype_ `void SyncSelections();`
- L37 _private member_ `const FEditorModeTools& EditorModeTools;`
- L40 _private member_ `TSet<const UObject*> ObjectsSet;` — All Objects Selected (Actors, Components, Objects)
- L42 _private member_ `TArray<UObject*> SelectedActors;`
- L43 _private member_ `TArray<UObject*> SelectedComponents;`
- L44 _private member_ `TArray<UObject*> SelectedObjects;`
- L46 _private member_ `EAvaOutlinerScopedSelectionPurpose Purpose;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Public/ToolMenuContext/AvaOutlinerItemsContext.h` (Public)


#### class `UAvaOutlinerItemsContext`  
`class UAvaOutlinerItemsContext : public UObject`  
_L15-36_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L22 _public function_ `TSharedPtr<IAvaOutliner> GetOutliner() const`
- L27 _public function_ `TConstArrayView<FAvaOutlinerItemWeakPtr> GetItems() const`
- L33 _private member_ `TWeakPtr<IAvaOutliner> OutlinerWeak;`
- L35 _private member_ `TArray<FAvaOutlinerItemWeakPtr> ItemListWeak;`
