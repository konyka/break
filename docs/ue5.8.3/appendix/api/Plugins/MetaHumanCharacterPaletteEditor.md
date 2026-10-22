# Plugins / MetaHumanCharacterPaletteEditor

- module root: `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPaletteEditor`
- headers: 22; symbols: 257
- symbol kinds: class=20, delegate=2, enum=3, enumerator=7, function=6, macro=1, member=56, namespace=8, prototype=149, struct=2, typedef=3
- PrivateDependencyModuleNames: AdvancedPreviewScene, Analytics, AssetDefinition, ContentBrowser, Core, CoreUObject, EditorFramework, EditorInteractiveToolsFramework, Engine, EngineSettings, InputCore, InteractiveToolsFramework, MessageLog, MetaHumanCharacterPalette, MetaHumanSDKEditor, Projects, PropertyEditor, Slate, SlateCore, ToolMenus, ToolWidgets, UnrealEd
- PublicDependencyModuleNames: 

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPaletteEditor/Private/AssetDefinitions/AssetDefinition_MetaHumanCollection.h` (Private)


#### class `UAssetDefinition_MetaHumanCollection`  
`class UAssetDefinition_MetaHumanCollection : public UAssetDefinitionDefault`  
_L10-22_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L16 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L17 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L18 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L19 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L20 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& InOpenArgs) const override;`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPaletteEditor/Private/AssetDefinitions/AssetDefinition_MetaHumanInstance.h` (Private)


#### class `UAssetDefinition_MetaHumanInstance`  
`class UAssetDefinition_MetaHumanInstance : public UAssetDefinitionDefault`  
_L10-22_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L16 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L17 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L18 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L19 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L20 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& InOpenArgs) const override;`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPaletteEditor/Private/AssetDefinitions/AssetDefinition_MetaHumanWardrobeItem.h` (Private)


#### class `UAssetDefinition_MetaHumanWardrobeItem`  
`class UAssetDefinition_MetaHumanWardrobeItem : public UAssetDefinitionDefault`  
_L10-22_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L16 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L17 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L18 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L19 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L20 _public prototype_ `virtual UThumbnailInfo* LoadThumbnailInfo(const FAssetData& InAssetData) const override;`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPaletteEditor/Private/Customizations/CollectionInstanceParametersCustomization.h` (Private)


#### class `FCollectionInstanceParametersCustomization`  
`class FCollectionInstanceParametersCustomization : public IDetailCustomization`  
_L11-19_
- inherits: `IDetailCustomization`
- desc: Detail customization for UMetaHumanPaletteEditorCollectionInstanceParameters.
- L14 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L17 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPaletteEditor/Private/Customizations/MetaHumanCharacterPaletteItemWrapperCustomization.h` (Private)


#### class `FMetaHumanCharacterPaletteItemWrapperCustomization`  
`class FMetaHumanCharacterPaletteItemWrapperCustomization : public IDetailCustomization`  
_L11-19_
- inherits: `IDetailCustomization`
- desc: Detail customization for UMetaHumanCharacterPaletteItemWrapper
- L14 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L17 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPaletteEditor/Private/MetaHumanCharacterPaletteEditorAnalytics.h` (Private)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MetaHuman` (scope `UE`)
- L13 _namespace_ `namespace Analytics` (scope `UE::MetaHuman`)
- L16 _prototype_ `void RecordCreateCollectionEvent(TNotNull<const UMetaHumanCollection*> InCollection);` (scope `UE::MetaHuman::Analytics`) — Recorded when a new MetaHuman Collection asset is created
- L19 _prototype_ `void RecordCreateInstanceEvent(TNotNull<const UMetaHumanCollection*> InCollection, TNotNull<const UMetaHumanInstance*> InInstance);` (scope `UE::MetaHuman::Analytics`) — Recorded when a new MetaHuman Instance asset is created
- L22 _prototype_ `void RecordBuildCollectionEvent(TNotNull<const UMetaHumanCollection*> InCollection);` (scope `UE::MetaHuman::Analytics`) — Recorded when a Collection is built via the Collection editor's Apply / Rebuild buttons
- L25 _prototype_ `void RecordOpenCollectionEditorEvent(TNotNull<const UMetaHumanCollection*> InCollection);` (scope `UE::MetaHuman::Analytics`) — Recorded when a Collection asset is opened for editing
- L28 _prototype_ `void RecordOpenInstanceEditorEvent(TNotNull<const UMetaHumanCollection*> InCollection, TNotNull<const UMetaHumanInstance*> InInstance);` (scope `UE::MetaHuman::Analytics`) — Recorded when an Instance asset is opened for editing
- L41 _prototype_ `void RecordDropItemsOnCollectionEvent( TNotNull<const UMetaHumanCollection*> InCollection, FName InTargetSlotName, int32 InNumItemsAdded, const FAssetData& InSampleAsset, const UMetaHumanWardrobeItem* InSampleWardrobeItem);` (scope `UE::MetaHuman::Analytics`) — Recorded when one or more items have been successfully added to a Collection via a drop zone. @param InCollection           The Collection that received the dropped items. @param InTargetSlotName       The slot the items were added to. @param InNumItemsAdded        The number of assets that were successfully added in this drop. @param InSampleAsset          One representative asset from the drop. For external Wardrobe Items, this is the principal asset the item wraps. @param InSampleWardrobeItem   The loaded Wardrobe Item if the first successful drop was an external Wardrobe Item asset, otherwise null.

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPaletteEditor/Private/MetaHumanCharacterPaletteEditorLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetaHumanCharacterPaletteEditor, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetaHumanCharacterPaletteEditor, Log, All);`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPaletteEditor/Private/MetaHumanCharacterPaletteItemWrapper.h` (Private)


#### class `UMetaHumanCharacterPaletteItemWrapper`  
`class UMetaHumanCharacterPaletteItemWrapper : public UObject`  
_L17-24_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: A UObject wrapper for FMetaHumanCharacterPaletteItem, so that it can be edited in a Details panel. Layout for this object is provided by FMetaHumanCharacterPaletteItemWrapperCustomization.
- L23 _public member_ `FMetaHumanCharacterPaletteItem Item;` — `UPROPERTY(EditAnywhere, Category = "Character", meta = (ShowOnlyInnerProperties))`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPaletteEditor/Private/MetaHumanInstanceActorFactory.h` (Private)


#### class `UMetaHumanInstanceActorFactory`  
`class UMetaHumanInstanceActorFactory : public UActorFactory`  
_L18-29_
- reflection: `UCLASS(MinimalAPI, config=Editor)`
- inherits: `UActorFactory`
- desc: Allows a MetaHuman Instance asset to be dragged from the Content Browser into a level viewport to spawn the appropriate actor.
- L24 _protected prototype_ `virtual UClass* GetDefaultActorClass(const FAssetData& AssetData) override;`
- L25 _protected prototype_ `virtual void PostSpawnActor(UObject* Asset, AActor* NewActor) override;`
- L26 _protected prototype_ `virtual UObject* GetAssetFromActorInstance(AActor* ActorInstance) override;`
- L27 _protected prototype_ `virtual bool CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg) override;`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPaletteEditor/Private/PaletteEditor/MetaHumanCharacterPaletteAssetEditor.h` (Private)


#### class `UMetaHumanCharacterPaletteAssetEditor`  
`class UMetaHumanCharacterPaletteAssetEditor : public UAssetEditor`  
_L16-55_
- reflection: `UCLASS()`
- inherits: `UAssetEditor`
- desc: An asset editor capable of editing MetaHuman Collection and Instance assets
- L23 _public prototype_ `virtual void GetObjectsToEdit(TArray<UObject*>& OutObjectsToEdit) override;`
- L24 _public prototype_ `virtual TSharedPtr<FBaseAssetToolkit> CreateToolkit() override;`
- L27 _public function_ `UMetaHumanCollection* GetMetaHumanCollection() const`
- L32 _public function_ `UMetaHumanInstance* GetMetaHumanInstance() const`
- L37 _public function_ `bool IsCollectionEditable() const`
- L43 _public prototype_ `void SetObjectToEdit(UMetaHumanCollection* InObject);` — The Collection is the object being edited. Instance will be the Collection's default instance.
- L45 _public prototype_ `void SetObjectToEdit(UMetaHumanInstance* InObject);` — The Instance is the object being edited. Its Collection will be accessible but not editable.
- L49 _private member_ `TObjectPtr<UMetaHumanCollection> Collection;` — `UPROPERTY()`
- L52 _private member_ `TObjectPtr<UMetaHumanInstance> Instance;` — `UPROPERTY()`
- L54 _private member_ `bool bIsCollectionEditable;`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPaletteEditor/Private/PaletteEditor/MetaHumanCharacterPaletteEditorCommands.h` (Private)


#### class `FMetaHumanCharacterPaletteEditorCommands`  
`class FMetaHumanCharacterPaletteEditorCommands : public TCommands<FMetaHumanCharacterPaletteEditorCommands>`  
_L8-22_
- inherits: `TCommands<FMetaHumanCharacterPaletteEditorCommands>`
- L11 _public prototype_ `FMetaHumanCharacterPaletteEditorCommands();`
- L13 _public prototype_ `virtual void RegisterCommands() override;`
- L16 _public member_ `TSharedPtr<FUICommandInfo> Apply;`
- L17 _public member_ `TSharedPtr<FUICommandInfo> AutoApplyInstanceEdits;`
- L18 _public member_ `TSharedPtr<FUICommandInfo> RebuildProduction;`
- L19 _public member_ `TSharedPtr<FUICommandInfo> AutoBuildPreview;`
- L20 _public member_ `TSharedPtr<FUICommandInfo> BuildAllItemsOnEdit;`
- L21 _public member_ `TSharedPtr<FUICommandInfo> ClearBuildCache;`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPaletteEditor/Private/PaletteEditor/MetaHumanCharacterPaletteEditorToolkit.h` (Private)


#### struct `FMetaHumanPaletteEditorItemInstanceParameters`  
`struct FMetaHumanPaletteEditorItemInstanceParameters`  
_L25-39_
- reflection: `USTRUCT()`
- L31 _public member_ `FMetaHumanPaletteItemPath ItemPath;` — `UPROPERTY()`
- L35 _public member_ `FText DisplayName;` — `UPROPERTY()` — Friendly name for the item, used as the category header by the details customization.
- L38 _public member_ `FInstancedPropertyBag InstanceParameters;` — `UPROPERTY(EditAnywhere, Category = "Overrides", meta = (FixedLayout, ShowOnlyInnerProperties))`

#### class `UMetaHumanPaletteEditorCollectionInstanceParameters`  
`class UMetaHumanPaletteEditorCollectionInstanceParameters : public UObject`  
_L42-51_
- reflection: `UCLASS(Transient)`
- inherits: `UObject`
- L50 _public member_ `TArray<FMetaHumanPaletteEditorItemInstanceParameters> UMetaHumanPaletteEditorCollectionInstanceParameters_Items;` — `UPROPERTY(EditAnywhere, Category = "Costume", meta = (ShowOnlyInnerProperties))` — This name needs to be unique among any properties defined in Instance Parameter structs provided by item pipelines, because of the way property change notifications work.

#### class `FMetaHumanCharacterPaletteEditorToolkit`  
`class FMetaHumanCharacterPaletteEditorToolkit : public FBaseAssetToolkit`  
_L56-148_
- inherits: `FBaseAssetToolkit`
- desc: The core class of the Palette editor
- L59 _public prototype_ `FMetaHumanCharacterPaletteEditorToolkit(UMetaHumanCharacterPaletteAssetEditor* InOwningAssetEditor);`
- L63 _protected prototype_ `virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;`
- L64 _protected prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;`
- L65 _protected prototype_ `virtual AssetEditorViewportFactoryFunction GetViewportDelegate() override;`
- L66 _protected prototype_ `virtual TSharedPtr<FEditorViewportClient> CreateEditorViewportClient() const override;`
- L67 _protected prototype_ `virtual TSharedRef<IDetailsView> CreateDetailsView() override;`
- L68 _protected prototype_ `virtual void RegisterToolbar() override;`
- L69 _protected prototype_ `virtual void PostInitAssetEditor() override;`
- L70 _protected prototype_ `virtual void SetEditingObject(UObject* InObject) override;`
- L71 _protected prototype_ `virtual void SaveAsset_Execute() override;`
- L72 _protected prototype_ `virtual void SaveAssetAs_Execute() override;`
- L73 _protected prototype_ `virtual bool OnRequestClose(EAssetEditorCloseReason InCloseReason) override;`
- L77 _private prototype_ `TSharedRef<SDockTab> SpawnTab_PartsView(const FSpawnTabArgs& Args);`
- L78 _private prototype_ `TSharedRef<SDockTab> SpawnTab_ItemDetails(const FSpawnTabArgs& Args);`
- L79 _private prototype_ `TSharedRef<SDockTab> SpawnTab_ItemInstanceParameters(const FSpawnTabArgs& Args);`
- L80 _private prototype_ `void OnPartsViewSelectionChanged(TSharedPtr<FMetaHumanCharacterPaletteItem> NewSelectedItem, ESelectInfo::Type SelectInfo);`
- L81 _private prototype_ `void OnPartsViewDoubleClick(TSharedPtr<FMetaHumanCharacterPaletteItem> Item, FName SlotName);`
- L82 _private prototype_ `void OnFinishedChangingItemProperties(const FPropertyChangedEvent& Event);`
- L83 _private prototype_ `void OnFinishedChangingInstanceParameters(const FPropertyChangedEvent& Event);`
- L84 _private prototype_ `void OnCollectionModified();`
- L85 _private prototype_ `void OnFinishedChangingCollectionProperties(const FPropertyChangedEvent& Event);`
- L87 _private prototype_ `void ToggleAutoBuildForPreview();`
- L88 _private prototype_ `bool IsAutoBuildForPreviewEnabled() const;`
- L90 _private prototype_ `void ApplyEditsToAsset();`
- L91 _private prototype_ `void BuildForProduction();`
- L92 _private prototype_ `bool IsApplyButtonEnabled() const;`
- L98 _private prototype_ `bool PromptToApplyEditsBeforeSave();` — Shows a dialog when there are unapplied edits, asking if the user wants to apply before saving. Returns true if the save should continue.
- L101 _private prototype_ `FString GetEditingAssetName() const;` — Returns the short name of the asset being edited
- L103 _private prototype_ `void ToggleAutoApplyInstanceEdits();`
- L104 _private prototype_ `bool ShouldAutoApplyInstanceEdits() const;`
- L106 _private prototype_ `void ToggleBuildAllItemsOnEdit();`
- L107 _private prototype_ `bool ShouldBuildAllItemsOnEdit() const;`
- L109 _private prototype_ `void ClearBuildCache();`
- L111 _private prototype_ `void UpdatePreview();`
- L112 _private prototype_ `void OnMetaHumanCharacterAssembled(EMetaHumanCharacterAssemblyResult Status);`
- L114 _private prototype_ `UMetaHumanCharacterPaletteAssetEditor* GetMutableCharacterEditor();`
- L115 _private prototype_ `const UMetaHumanCharacterPaletteAssetEditor* GetCharacterEditor() const;`
- L117 _private prototype_ `bool IsCollectionEditable() const;`
- L118 _private prototype_ `bool ShouldViewportShowProductionBuild() const;`
- L121 _private member_ `TUniquePtr<FPreviewScene> PreviewScene;` — The preview scene displayed in the viewport of the asset editor.
- L128 _private member_ `TWeakObjectPtr<AActor> PreviewActor;` — The actor spawned in the world of the preview scene This is a weak pointer because the PreviewScene should hold a strong reference to the actor, so the actor won't be deleted while the scene is alive, but we don't want this to become a dangling pointer after the scene is cleaned up.
- L130 _private member_ `TArray<TSharedPtr<FMetaHumanCharacterPaletteItem>> ListItems;`
- L132 _private member_ `TSharedPtr<IDetailsView> ItemDetailsView;`
- L133 _private member_ `TSharedPtr<IDetailsView> ItemInstanceParametersDetailsView;`
- L134 _private member_ `TSharedPtr<SCollectionItemTileView> PartsViewWidget;`
- L135 _private member_ `TSharedPtr<FMetaHumanCharacterPaletteItem> CurrentlySelectedItem;`
- L136 _private member_ `FMetaHumanPaletteItemKey CurrentlySelectedItemKey;`
- L138 _private member_ `TStrongObjectPtr<UMetaHumanCharacterPaletteItemWrapper> ItemWrapper;`
- L139 _private member_ `TStrongObjectPtr<UMetaHumanPaletteEditorCollectionInstanceParameters> InstanceParameterWrapper;`
- L141 _private member_ `TStrongObjectPtr<UMetaHumanCollection> PreviewCollection;`
- L142 _private member_ `TStrongObjectPtr<UMetaHumanInstance> PreviewInstance;`
- L144 _private member_ `bool bPreviewCollectionNeedsBuild = false;`
- L145 _private member_ `bool bCollectionHasUnappliedEdits = false;`
- L146 _private member_ `bool bInstanceHasUnappliedEdits = false;`
- L147 _private member_ `bool bShouldAutoApplyInstanceEdits = true;`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPaletteEditor/Private/PaletteEditor/MetaHumanCharacterPaletteEditorViewportClient.h` (Private)


#### class `FMetaHumanCharacterPaletteViewportClient`  
`class FMetaHumanCharacterPaletteViewportClient : public FEditorViewportClient`  
_L7-18_
- inherits: `FEditorViewportClient`
- L10 _public prototype_ `FMetaHumanCharacterPaletteViewportClient(FEditorModeTools* InModeToos, FPreviewScene* InPreviewScene);`
- L13 _public prototype_ `virtual void Tick(float InDeltaSeconds) override;`
- L14 _public prototype_ `virtual void Draw(FViewport* InViewport, FCanvas* InCanvas) override;`
- L17 _public member_ `FText OverlayText;`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPaletteEditor/Private/PaletteEditor/SMetaHumanCharacterPaletteEditorViewport.h` (Private)


#### class `SMetaHumanCharacterPaletteEditorViewport`  
`class SMetaHumanCharacterPaletteEditorViewport : public SAssetEditorViewport`  
_L7-15_
- inherits: `SAssetEditorViewport`
- L13 _public prototype_ `virtual void AddOverlayWidget(TSharedRef<SWidget> InWidget, int32 InZOrder = INDEX_NONE);` — These allow the toolkit to add an accept/cancel overlay when needed. PopulateViewportOverlays is not helpful here because that gets called just once.
- L14 _public prototype_ `virtual void RemoveOverlayWidget(TSharedRef<SWidget> InWidget);`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPaletteEditor/Private/ReplaceItemDialog.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MetaHuman` (scope `UE`)
- L21 _prototype_ `void OpenReplaceItemDialog(const TArray<UMetaHumanInstance*>& InInstances);` (scope `UE::MetaHuman`) — Opens a modal dialog that allows the user to redirect one or more item selections in a group of MetaHuman Instances to another item, or to remove them entirely. This is useful when an item is about to be removed from a Collection and any Instances that reference it need to be updated to point at a replacement item first.

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPaletteEditor/Private/Widgets/SCollectionItemTileView.h` (Private)


#### class `SCollectionItemTileView`  
`class SCollectionItemTileView : public SCompoundWidget`  
_L25-179_
- inherits: `SCompoundWidget`
- desc: A Content Browser-like view of all items across all slots in a MetaHuman Collection.
- L28 _public typedef_ `typedef typename TSlateDelegates<TSharedPtr<FMetaHumanCharacterPaletteItem>>::FOnSelectionChanged FOnSelectionChanged;`
- L29 _public typedef_ `typedef TDelegate<void(TSharedPtr<FMetaHumanCharacterPaletteItem>, FName)> FOnMouseButtonDoubleClick;`
- L30 _public typedef_ `typedef FSimpleDelegate FOnCollectionModified;`
- L32 _public function_ `SLATE_BEGIN_ARGS(SCollectionItemTileView)`
- L34 _public prototype_ `SLATE_ARGUMENT(UMetaHumanInstance*, MetaHumanInstance) SLATE_ARGUMENT_DEFAULT(UMetaHumanCollection*, MetaHumanCollection) = nullptr;`
- L43 _public prototype_ `SLATE_ARGUMENT_DEFAULT(bool, IsCollectionEditable) = false;` — True if this asset is allowed to edit the Collection, otherwise it will only view the Collection's contents
- L44 _public prototype_ `SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged) SLATE_EVENT(FOnMouseButtonDoubleClick, OnMouseButtonDoubleClick) SLATE_EVENT(FOnCollectionModified, OnCollectionModified) SLATE_END_ARGS() SCollectionItemTileView();`
- L51 _public prototype_ `void Construct(const FArguments& Args);`
- L53 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L60 _public prototype_ `void WriteItemToCollection( const FMetaHumanPaletteItemKey& OriginalItemKey, const TSharedRef<FMetaHumanCharacterPaletteItem>& ModifiedItem, bool bAffectsBuild = true);` — Write the edited item back to the Collection asset. @param bAffectsBuild  True if the Collection build should be invalidated by this change.
- L66 _public prototype_ `void Refresh();` — Refresh the slot filter buttons and items after the pipeline specification has changed
- L69 _public prototype_ `void InvalidateSelectableState();` — Refresh the state that determines whether each tile is selectable or not
- L71 _public prototype_ `void OnPreviewBuildComplete(bool bSucceeded);`
- L74 _public prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L75 _public prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L76 _public prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L77 _public prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L82 _private prototype_ `void PopulateAllItems();` — Populate AllItems from the collection
- L85 _private prototype_ `void RebuildFilteredItems();` — Rebuild FilteredItems from AllItems based on current filters
- L88 _private prototype_ `void BuildSlotFilterButtons();` — Build the slot filter buttons from the current pipeline specification
- L91 _private prototype_ `void OnSlotFilterChanged(ECheckBoxState NewState, FName SlotName);` — Slot filter button callbacks
- L92 _private prototype_ `ECheckBoxState IsSlotFilterChecked(FName SlotName) const;`
- L95 _private prototype_ `void OnSearchTextChanged(const FText& InText);` — Search box callback
- L98 _private prototype_ `TSharedRef<ITableRow> OnGenerateTile(TSharedPtr<FCollectionItemTileData> InItem, const TSharedRef<STableViewBase>& OwnerTable) const;` — Tile view callbacks
- L99 _private prototype_ `void OnTileViewSelectionChanged(TSharedPtr<FCollectionItemTileData> SelectedTile, ESelectInfo::Type SelectInfo);`
- L100 _private prototype_ `void OnTileViewDoubleClick(TSharedPtr<FCollectionItemTileData> SelectedTile);`
- L103 _private prototype_ `TSharedPtr<SWidget> OnTileViewContextMenuOpening();` — Context menu
- L104 _private prototype_ `void OnDeleteAction();`
- L107 _private prototype_ `bool IsItemActive(TSharedPtr<const FCollectionItemTileData> TileData) const;` — State queries
- L108 _private prototype_ `bool IsItemSelectable(TSharedPtr<const FCollectionItemTileData> TileData) const;`
- L109 _private prototype_ `FLinearColor GetSlotColorForItem(TSharedPtr<const FCollectionItemTileData> TileData) const;`
- L110 _private prototype_ `FLinearColor GetTintColorForTile(TSharedPtr<const FCollectionItemTileData> TileData) const;`
- L113 _private prototype_ `TArray<FName> GetTargetSlotNames() const;` — Drag and drop helpers
- L116 _private prototype_ `TArray<FName> GetCompatibleSlotsForDrag(const FDragDropEvent& DragDropEvent) const;` — Compute which visible slots accept the asset types being dragged
- L119 _private prototype_ `void ShowDropZoneOverlay(const TArray<FName>& CompatibleSlots);` — Show/hide the drop zone overlay
- L120 _private prototype_ `void HideDropZoneOverlay();`
- L123 _private prototype_ `EVisibility GetEmptyStateVisibility() const;` — Empty-state overlay. Shown when there are no items to display in the tile view.
- L124 _private prototype_ `FText GetEmptyStateAcceptedTypesText() const;`
- L127 _private prototype_ `TArray<FName> GetEmptyStateScopeSlotNames() const;` — Returns the visible slot names currently in scope for the empty-state hint text.
- L130 _private prototype_ `void RebuildEmptyStateAcceptedTypeNames();` — Recompute and cache the accepted asset type names for the empty-state hint text, based on current slot filters.
- L132 _private member_ `TStrongObjectPtr<UMetaHumanInstance> MetaHumanInstance;`
- L133 _private member_ `TStrongObjectPtr<UMetaHumanCollection> MetaHumanCollection;`
- L134 _private member_ `FOnSelectionChanged OnSelectionChangedDelegate;`
- L135 _private member_ `FOnMouseButtonDoubleClick OnMouseButtonDoubleClickDelegate;`
- L136 _private member_ `FOnCollectionModified OnCollectionModifiedDelegate;`
- L137 _private member_ `bool bIsCollectionEditable = false;`
- L140 _private member_ `TArray<TSharedPtr<FCollectionItemTileData>> AllItems;` — All items across all visible slots
- L148 _private member_ `TArray<FDeferredSlotSelection> PendingAutoSelections;`
- L151 _private member_ `TSharedRef<UE::Slate::Containers::TObservableArray<TSharedPtr<FCollectionItemTileData>>> FilteredItems;` — Filtered items currently shown in the tile view
- L153 _private member_ `TSharedRef<FAssetThumbnailPool> AssetThumbnailPool;`
- L154 _private member_ `TSharedPtr<STileView<TSharedPtr<FCollectionItemTileData>>> TileView;`
- L155 _private member_ `TSharedPtr<SWrapBox> SlotFilterBox;`
- L156 _private member_ `TSharedPtr<SSearchBox> SearchBox;`
- L157 _private member_ `TSharedPtr<class FUICommandList> ContextMenuCommandList;`
- L160 _private member_ `TSet<FName> ActiveSlotFilters;` — Currently active slot filters. Empty means show all.
- L167 _private member_ `TArray<FString> EmptyStateAcceptedTypeNames;` — Cached display names of asset classes accepted by the slots currently in scope for the empty-state hint text.
- L170 _private member_ `FString SearchText;` — Current search text
- L173 _private member_ `TMap<FName, FLinearColor> SlotColors;` — Cached slot colors from pipeline specification, keyed by slot name
- L176 _private member_ `TArray<FName> DragCompatibleSlots;` — Drop zone overlay state
- L177 _private member_ `TSharedPtr<SWidget> DropZoneOverlay;`
- L178 _private member_ `TSharedPtr<SOverlay> TileViewOverlay;`

#### struct `SCollectionItemTileView::FDeferredSlotSelection`  
`struct FDeferredSlotSelection`  
_L143-147_
- desc: Selections deferred until the build completes
- L145 _public member_ `FName SlotName;`
- L146 _public member_ `FMetaHumanPaletteItemKey ItemKey;`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPaletteEditor/Public/MetaHumanCharacterEditorActorInterface.h` (Public)


#### enum `EMetaHumanHairVisibilityState`  
`enum class EMetaHumanHairVisibilityState : uint8`  
_L16-20_
- reflection: `UENUM(BlueprintType)`
- L18 _public enumerator_ `Shown`
- L19 _public enumerator_ `Hidden`

#### enum `EMetaHumanClothingVisibilityState`  
`enum class EMetaHumanClothingVisibilityState : uint8`  
_L23-28_
- reflection: `UENUM(BlueprintType)`
- L25 _public enumerator_ `Shown`
- L26 _public enumerator_ `UseOverrideMaterial`
- L27 _public enumerator_ `Hidden`

#### enum `EMetaHumanActorDrivingAnimationMode`  
`enum class EMetaHumanActorDrivingAnimationMode : uint8`  
_L34-41_
- reflection: `UENUM(BlueprintType)`
- desc: How the actor should handle animation playback
- L37 _public enumerator_ `FromRetargetSource` — Animation will be handled by a retargeting component
- L40 _public enumerator_ `Manual` — Animation will be played directly in the components

#### class `UMetaHumanCharacterEditorActorInterface`  
`class UMetaHumanCharacterEditorActorInterface : public UInterface`  
_L49-52_
- reflection: `UINTERFACE(BlueprintType, meta=(CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`
- desc: An actor implementing this interface can be used as a preview actor in the MetaHuman Character editor. The MetaHuman Character Pipeline determines the type of preview actor to spawn.

#### class `IMetaHumanCharacterEditorActorInterface`  
`class IMetaHumanCharacterEditorActorInterface : public IInterface`  
_L54-202_
- inherits: `IInterface`
- L86 _public prototype_ `virtual void InitializeMetaHumanCharacterEditorActor( TNotNull<const UMetaHumanInstance*> InCharacterInstance, TNotNull<UMetaHumanCharacter*> InCharacter, TNotNull<USkeletalMesh*> InFaceMesh, TNotNull<USkeletalMesh*> InBodyMesh, int32 InNumLODs, const TArray<int32>& InFaceLODMapping, const TArray<int32>& InBodyLODMapping) = 0;` — Called by the Character editor to initialize the preview actor. Will only be called once on each instance, after object construction but before actor spawn, and hence before the Blueprint construction script runs, if this is a Blueprint actor. All other functions will be called after actor spawn, except where noted. InCharacterInstance is a valid instance using the same Pipeline that spawned this actor. InCharacter is the Character being edited. This should be returned from GetCharacter. InFaceMesh and InBodyMesh should be assigned to SkeletalMeshComponents. InNumLODs is the number of LODs the actor should have. This can be assigned to the LODSyncComponent's NumLODs property if using a LODSyncComponent. The InFaceLODMapping and InBodyLODMapping arrays will have this number of elements. InFaceLODMapping is a mapping from the actor LOD to the face mesh LOD. For example, if InNumLODs is 4 and InFaceLODMapping is { 0, 0, 1, 1 }, then if SetForcedLOD is called with 3 as the argument, this selects actor LOD 3, which corresponds to InFaceLODMapping[3], which is 1, so the face mesh component should be set to LOD 1. If this actor uses the LODSyncComponent, it can make a CustomLODMapping entry for the Face component and assign InFaceLODMapping to it. See AMetaHumanCharacterEditorActor for reference.
- L104 _public prototype_ `virtual void SetForcedLOD(int32 InForcedLOD) = 0;` — Forces the given actor LOD to be displayed. The face and body LODs to be used are determined by the mapping arrays passed into InitializeMetaHumanCharacterEditorActor. If InForcedLOD is INDEX_NONE, the actor LOD is not forced and should be selected naturally, e.g. based on screen size.
- L111 _public prototype_ `virtual TNotNull<UMetaHumanCharacter*> GetCharacter() const = 0;` — Returns the Character passed into InitializeMetaHumanCharacterEditorActor. May be called at any time after InitializeMetaHumanCharacterEditorActor.
- L114 _public prototype_ `virtual TNotNull<const USkeletalMeshComponent*> GetFaceComponent() const = 0;` — Returns the component that the Face mesh is assigned to
- L117 _public prototype_ `virtual TNotNull<const USkeletalMeshComponent*> GetBodyComponent() const = 0;` — Returns the component that the Body mesh is assigned to
- L130 _public prototype_ `virtual void SetActorDrivingAnimationMode(EMetaHumanActorDrivingAnimationMode InDrivingAnimationMode) = 0;` — @brief Sets how the actor should handle animation playback. Determines how the actor handles animation playback. FromRetargetSource tells the actor that animation will handled by an IK retargeter, i.e., animation is played in an invisible actor and then retargeted to this actor. The driving skeletal mesh is set using SetDrivingSkeletalMesh. Manual means that animation will be played back directly in the actor, being it using animation sequences or sequencer. @param InMode the animation mode to set
- L139 _public prototype_ `virtual void SetDrivingSkeletalMesh(USkeletalMeshComponent* DrivingSkelMeshComponent) = 0;` — @brief Follow and retarget from the pose of the driving skeletal mesh. Automatically switches the animation mode to RetargetFromSource @param DrivingSkelMeshComponent The skeleletal mesh component that will be the retargeting source
- L147 _public prototype_ `virtual void OnFaceMeshUpdated() = 0;` — Will be called when the Face mesh is updated. Implementers will need to call MarkRenderStateDirty and UpdateBounds on the component to ensure any material or geometry changes are correctly applied.
- L153 _public prototype_ `virtual void ReinitAnimation() = 0;` — Enable animation. This could be assigning an anim graph or a sequence onto the body and/or face.
- L160 _public prototype_ `virtual void ResetAnimation() = 0;` — `UE_DEPRECATED(5.7, "Disabling animation is now handled internally by the actors and this function is not needed anymore")` — Disable animation. Disconnects anim instances and reset the skeletal meshes to their reference pose.
- L168 _public prototype_ `virtual void OnBodyMeshUpdated() = 0;` — Will be called when the Body mesh is updated. Implementers will need to call MarkRenderStateDirty and UpdateBounds on the component to ensure any material or geometry changes are correctly applied.
- L171 _public prototype_ `virtual void UpdateFaceComponentMesh(USkeletalMesh* InFaceMesh) = 0;` — Updates Face Mesh with the new object when it is created in the character
- L174 _public prototype_ `virtual void UpdateBodyComponentMesh(USkeletalMesh* InBodyMesh) = 0;` — Updates Body Mesh with the new object when it is created in the character
- L177 _public prototype_ `virtual void SetHairVisibilityState(EMetaHumanHairVisibilityState State) = 0;` — Any hair components on the actor should be set to the given visibility state
- L186 _public prototype_ `virtual void SetClothingVisibilityState(EMetaHumanClothingVisibilityState State, UMaterialInterface* OverrideMaterial = nullptr) = 0;` — Any clothing components should be set to the given visibility state. If the state is UseOverrideMaterial, the provided material should be applied. The original materials should be restored on the next time the state is changed.
- L193 _public prototype_ `virtual void SetShowNormalsOnFace(const bool InShowNormals) = 0;`
- L194 _public prototype_ `virtual void SetShowNormalsOnBody(const bool InShowNormals) = 0;`
- L196 _public prototype_ `virtual void SetShowTangentsOnFace(const bool InShowNormals) = 0;`
- L197 _public prototype_ `virtual void SetShowTangentsOnBody(const bool InShowNormals) = 0;`
- L199 _public prototype_ `virtual void SetShowBinormalsOnFace(const bool InShowBinormals) = 0;`
- L200 _public prototype_ `virtual void SetShowBinormalsOnBody(const bool InShowBinormals) = 0;`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPaletteEditor/Public/MetaHumanCharacterPaletteEditorModule.h` (Public)


#### class `FMetaHumanCharacterPaletteEditorModule`  
`class FMetaHumanCharacterPaletteEditorModule : public IModuleInterface`  
_L8-27_
- inherits: `IModuleInterface`
- L12 _public prototype_ `static FMetaHumanCharacterPaletteEditorModule& GetChecked();`
- L15 _public prototype_ `virtual void StartupModule() override;`
- L16 _public prototype_ `virtual void ShutdownModule() override;`
- L19 _public prototype_ `DECLARE_EVENT_OneParam(FMetaHumanCharacterPaletteEditorModule, FOnRegisterLayoutExtensions, class FLayoutExtender&);`
- L20 _public function_ `FOnRegisterLayoutExtensions& OnRegisterLayoutExtensions()`
- L26 _private member_ `FOnRegisterLayoutExtensions RegisterLayoutExtensions;`

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_EVENT_OneParam(FMetaHumanCharacterPaletteEditorModule, FOnRegisterLayoutExtensions, class FLayoutExtender&);`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPaletteEditor/Public/MetaHumanCharacterPaletteUnpackHelpers.h` (Public)


#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API METAHUMANCHARACTERPALETTEEDITOR_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MetaHuman` (scope `UE`)
- L14 _namespace_ `namespace PaletteUnpackHelpers` (scope `UE::MetaHuman`)
- L20 _prototype_ `void CopyMaterialParametersIfNeeded(EMaterialParameterType InParamType, TNotNull<const UMaterialInterface*> InSourceMaterial, TNotNull<UMaterialInstanceConstant*> InTargetMaterial);` (scope `UE::MetaHuman::PaletteUnpackHelpers`) — Copy the material parameters of a given type from the source to the target material only if the values are not the same. This ensures the target material will only have the overrides for parameters that have different values.
- L26 _prototype_ `UMaterialInstanceConstant* CreateMaterialInstanceCopy(TNotNull<const UMaterialInstance*> InMaterialInstance, TNotNull<UObject*> InOuter);` (scope `UE::MetaHuman::PaletteUnpackHelpers`) — Creates a material instance constant from the given material instance. Parameters are only copied if they differ from the base material. This prevents the new material from having all of its parameters overridden

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPaletteEditor/Public/MetaHumanCollectionFactory.h` (Public)


#### class `UMetaHumanCollectionFactory`  
`class UMetaHumanCollectionFactory : public UFactory`  
_L10-22_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L16 _public prototype_ `UMetaHumanCollectionFactory();`
- L19 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* Context, FFeedbackContext* Warn) override;`
- L20 _public prototype_ `virtual FText GetToolTip() const override;`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPaletteEditor/Public/MetaHumanStructHost.h` (Public)


#### class `UMetaHumanStructHost`  
`class UMetaHumanStructHost : public UObject`  
_L16-23_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: A simple wrapper to allow an FInstancedStruct to be visible to the Garbage Collector. Useful for subclasses of UMetaHumanCharacterEditorPipeline, which often hold local objects that need to survive GC.
- L22 _public member_ `FInstancedStruct Struct;` — `UPROPERTY()`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPaletteEditor/Public/MetaHumanWardrobeItemFactory.h` (Public)


#### class `UMetaHumanWardrobeItemFactory`  
`class UMetaHumanWardrobeItemFactory : public UFactory`  
_L10-22_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L16 _public prototype_ `UMetaHumanWardrobeItemFactory();`
- L19 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* Context, FFeedbackContext* Warn) override;`
- L20 _public prototype_ `virtual FText GetToolTip() const override;`
