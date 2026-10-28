# Plugins / SmartObjectsEditorModule

- module root: `Plugins/Runtime/SmartObjects/Source/SmartObjectsEditorModule`
- headers: 17; symbols: 238
- symbol kinds: class=17, delegate=2, function=12, macro=4, member=60, namespace=3, prototype=139, struct=1
- PrivateDependencyModuleNames: ApplicationCore, AssetDefinition, BlueprintGraph, ComponentVisualizers, InputCore, PropertyAccessEditor, PropertyBindingUtils, PropertyBindingUtilsEditor, PropertyEditor, RenderCore, Slate, SlateCore, StructUtilsEditor, ToolMenus, ToolWidgets
- PublicDependencyModuleNames: AdvancedPreviewScene, Core, CoreUObject, Engine, GameplayTags, SmartObjectsModule, SourceControl, UnrealEd, WorldConditions

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsEditorModule/Private/AssetDefinition_SmartObjectDefinition.h` (Private)


#### class `UAssetDefinition_SmartObjectDefinition`  
`class UAssetDefinition_SmartObjectDefinition : public UAssetDefinitionDefault`  
_L9-21_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L15 _protected prototype_ `virtual FText GetAssetDisplayName() const override;` — UAssetDefinition Begin
- L16 _protected prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L17 _protected prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L18 _protected prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L19 _protected prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsEditorModule/Private/Customizations/SmartObjectDefinitionDataProxyDetails.h` (Private)


#### class `FSmartObjectDefinitionDataProxyDetails`  
`class FSmartObjectDefinitionDataProxyDetails : public IPropertyTypeCustomization`  
_L18-43_
- inherits: `IPropertyTypeCustomization`
- L22 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L25 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L26 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L30 _private prototype_ `FText GetDefinitionDataName() const;`
- L31 _private prototype_ `void OnCopy() const;`
- L32 _private prototype_ `void OnPaste() const;`
- L33 _private prototype_ `TSharedPtr<FSmartObjectViewModel> GetViewModel() const;`
- L34 _private prototype_ `FGuid GetItemID() const;`
- L36 _private prototype_ `TSharedRef<SWidget> GenerateStructPicker();`
- L37 _private prototype_ `void OnStructPicked(const UScriptStruct* InStruct);`
- L39 _private member_ `TSharedPtr<IPropertyUtilities> PropUtils;`
- L40 _private member_ `TSharedPtr<IPropertyHandle> StructProperty;`
- L41 _private member_ `TSharedPtr<IPropertyHandle> DataPropertyHandle;`
- L42 _private member_ `TSharedPtr<SComboButton> ComboButton;`

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsEditorModule/Private/Customizations/SmartObjectDefinitionDetails.h` (Private)


#### class `FSmartObjectDefinitionDetails`  
`class FSmartObjectDefinitionDetails : public IDetailCustomization`  
_L14-25_
- inherits: `IDetailCustomization`
- desc: Details customization or USmartObjectDefinition
- L18 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L21 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L24 _protected prototype_ `void MakeArrayCategory(IDetailLayoutBuilder& DetailBuilder, FName CategoryName, const FText& DisplayName, int32 SortOrder, TSharedPtr<IPropertyHandle> PropertyHandle) const;`

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsEditorModule/Private/Customizations/SmartObjectDefinitionReferenceDetails.h` (Private)


#### class `FSmartObjectDefinitionReferenceDetails`  
`class FSmartObjectDefinitionReferenceDetails : public IPropertyTypeCustomization`  
_L14-37_
- inherits: `IPropertyTypeCustomization`
- desc: Type customization for FSmartObjectDefinitionReference.
- L18 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L21 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InStructPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L22 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& InChildrenBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L26 _private prototype_ `void OnParametersChanged(const USmartObjectDefinition& SmartObjectDefinition) const;`
- L32 _private prototype_ `void SyncParameters(const USmartObjectDefinition* DefinitionToSync = nullptr) const;` — Synchronizes parameters with SmartObject Definition asset parameters if needed. @param DefinitionToSync Optional SmartObject Definition asset used to filter which parameters should be synced. A null value indicates that all parameters should be synced.
- L34 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;`
- L35 _private member_ `TSharedPtr<IPropertyHandle> ParametersHandle;`
- L36 _private member_ `TSharedPtr<IPropertyUtilities> PropUtils;`

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsEditorModule/Private/Customizations/SmartObjectSlotDefinitionDetails.h` (Private)


#### class `FSmartObjectSlotDefinitionDetails`  
`class FSmartObjectSlotDefinitionDetails : public IPropertyTypeCustomization`  
_L15-38_
- inherits: `IPropertyTypeCustomization`
- L19 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L22 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L23 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L27 _private prototype_ `FText GetSlotName() const;`
- L28 _private prototype_ `void OnSlotNameCommitted(const FText& NewText, ETextCommit::Type InTextCommit) const;`
- L29 _private prototype_ `void OnCopy() const;`
- L30 _private prototype_ `void OnPaste() const;`
- L31 _private prototype_ `void CacheOuterDefinition();`
- L33 _private member_ `USmartObjectDefinition* Definition = nullptr;`
- L34 _private member_ `IPropertyUtilities* PropUtils = nullptr;`
- L35 _private member_ `TSharedPtr<IPropertyHandle> StructProperty;`
- L36 _private member_ `TSharedPtr<IPropertyHandle> NamePropertyHandle;`
- L37 _private member_ `TSharedPtr<IPropertyHandle> DefinitionDataPropertyHandle;`

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsEditorModule/Private/Customizations/SmartObjectSlotReferenceDetails.h` (Private)


#### class `FSmartObjectSlotReferenceDetails`  
`class FSmartObjectSlotReferenceDetails : public IPropertyTypeCustomization`  
_L16-36_
- inherits: `IPropertyTypeCustomization`
- L20 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L23 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L24 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L28 _private prototype_ `const USmartObjectDefinition* GetSmartObjectDefinition() const;`
- L30 _private prototype_ `void OnSlotComboChanged(const FGuid NewID);`
- L31 _private prototype_ `TSharedRef<SWidget> OnGetSlotListContent() const;`
- L32 _private prototype_ `FText GetCurrentSlotDesc() const;`
- L34 _private member_ `IPropertyUtilities* PropUtils = nullptr;`
- L35 _private member_ `TSharedPtr<IPropertyHandle> StructProperty;`

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsEditorModule/Private/SSmartObjectViewport.h` (Private)


#### class `SSmartObjectViewport`  
`class SSmartObjectViewport : public SEditorViewport, public ICommonEditorViewportToolbarInfoProvider`  
_L14-53_
- inherits: `SEditorViewport,ICommonEditorViewportToolbarInfoProvider`
- L18 _public function_ `SLATE_BEGIN_ARGS(SSmartObjectViewport)`
- L19 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FSmartObjectAssetEditorViewportClient>, EditorViewportClient) SLATE_ARGUMENT(TSharedPtr<FSmartObjectAssetToolkit>, AssetEditorToolkit) SLATE_ARGUMENT(FAdvancedPreviewScene*, PreviewScene) SLATE_END_ARGS();`
- L24 _public prototype_ `void Construct(const FArguments& InArgs);`
- L25 _public prototype_ `virtual ~SSmartObjectViewport() override = default;`
- L28 _public prototype_ `virtual TSharedRef<class SEditorViewport> GetViewportWidget() override;`
- L29 _public prototype_ `virtual TSharedPtr<FExtender> GetExtenders() const override;`
- L30 _public prototype_ `virtual void OnFloatingButtonClicked() override;`
- L36 _protected prototype_ `virtual void BindCommands() override;`
- L37 _protected prototype_ `virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;`
- L38 _protected prototype_ `virtual TSharedPtr<SWidget> BuildViewportToolbar() override;`
- L39 _protected prototype_ `virtual TSharedPtr<IPreviewProfileController> CreatePreviewProfileController() override;`
- L43 _protected member_ `TSharedPtr<SSmartObjectViewportToolBar> ViewportToolbar;` — The viewport toolbar
- L46 _protected member_ `TSharedPtr<FSmartObjectAssetEditorViewportClient> ViewportClient;` — Viewport client
- L49 _protected member_ `FAdvancedPreviewScene* PreviewScene = nullptr;` — The preview scene that we are viewing
- L52 _protected member_ `TWeakPtr<FSmartObjectAssetToolkit> AssetEditorToolkitPtr;` — Asset editor toolkit we are embedded in

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsEditorModule/Private/SmartObjectAssetEditorSettings.h` (Private)


#### class `USmartObjectAssetEditorSettings`  
`class USmartObjectAssetEditorSettings : public UObject`  
_L11-21_
- reflection: `UCLASS(config=EditorPerProjectUserSettings)`
- inherits: `UObject`
- desc: Settings for the SmartObject asset editor
- L16 _public prototype_ `USmartObjectAssetEditorSettings();`
- L20 _public member_ `bool bShowGridByDefault;` — `UPROPERTY(config, EditAnywhere, Category="Grid")` — Indicates whether or not the grid must be shown by default when the editor is opened

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsEditorModule/Private/SmartObjectAssetEditorViewportClient.h` (Private)


#### class `FSmartObjectAssetEditorViewportClient`  
`class FSmartObjectAssetEditorViewportClient : public FEditorViewportClient`  
_L17-90_
- inherits: `FEditorViewportClient`
- L20 _public prototype_ `explicit FSmartObjectAssetEditorViewportClient(const TSharedRef<const FSmartObjectAssetToolkit>& InAssetEditorToolkit, FPreviewScene* InPreviewScene = nullptr, const TWeakPtr<SEditorViewport>& InEditorViewportWidget = nullptr);`
- L23 _public prototype_ `void SetViewModel(TSharedPtr<FSmartObjectViewModel> InViewModel);`
- L24 _public prototype_ `void SetSmartObjectDefinition(USmartObjectDefinition& Definition);`
- L25 _public prototype_ `void SetPreviewMesh(UStaticMesh* InStaticMesh);`
- L26 _public prototype_ `void SetPreviewActor(AActor* InActor);`
- L27 _public prototype_ `void SetPreviewActorClass(const UClass* ActorClass);`
- L28 _public prototype_ `void ResetPreviewActor();`
- L30 _public function_ `USmartObjectDefinition* GetSmartObjectDefinition() const`
- L33 _protected prototype_ `virtual void Draw(const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`
- L34 _protected prototype_ `virtual void DrawCanvas( FViewport& InViewport, FSceneView& View, FCanvas& Canvas ) override;`
- L35 _protected prototype_ `virtual void ProcessClick(FSceneView& View, HHitProxy* HitProxy, FKey Key, EInputEvent Event, uint32 HitX, uint32 HitY) override;`
- L36 _protected prototype_ `virtual void TrackingStarted(const struct FInputEventState& InInputState, bool bIsDraggingWidget, bool bNudge) override;`
- L37 _protected prototype_ `virtual void TrackingStopped() override;`
- L38 _protected prototype_ `virtual bool InputWidgetDelta(FViewport* InViewport, EAxisList::Type CurrentAxis, FVector& Drag, FRotator& Rot, FVector& Scale) override;`
- L40 _protected prototype_ `virtual FVector GetWidgetLocation() const override;`
- L41 _protected prototype_ `virtual FMatrix GetWidgetCoordSystem() const override;`
- L42 _protected prototype_ `virtual ECoordSystem GetWidgetCoordSystemSpace() const override;`
- L43 _protected prototype_ `virtual UE::Widget::EWidgetMode GetWidgetMode() const override;`
- L44 _protected prototype_ `virtual bool CanSetWidgetMode(UE::Widget::EWidgetMode NewMode) const override;`
- L45 _protected prototype_ `virtual void SetWidgetMode(UE::Widget::EWidgetMode NewMode) override;`
- L46 _protected prototype_ `virtual void SetWidgetCoordSystemSpace(ECoordSystem NewCoordSystem) override;`
- L49 _protected prototype_ `FBox GetPreviewBounds() const;` — Computes and returns a bounding box that encapsulated preview actor or mesh
- L52 _private prototype_ `void RemoveViewModelDelegates();`
- L53 _private prototype_ `void HandleSelectionChanged(TConstArrayView<FGuid> Selection);`
- L55 _private prototype_ `void BeginTransaction(FText Text);`
- L56 _private prototype_ `void EndTransaction();`
- L59 _private prototype_ `TConstArrayView<FGuid> GetSelection() const;` — Helper method to return selection from view model.
- L62 _private member_ `TSharedPtr<FSmartObjectViewModel> ViewModel;` — Pointer to the view model
- L65 _private member_ `TWeakObjectPtr<USmartObjectDefinition> SmartObjectDefinition = nullptr;` — Weak pointer to the Smart Object definition that is edited
- L68 _private member_ `TWeakObjectPtr<AActor> PreviewActor = nullptr;` — Weak pointer to the preview actor added to the preview scene
- L71 _private member_ `TWeakPtr<const FSmartObjectAssetToolkit> AssetEditorToolkit;` — Weak pointer back to asset editor we are embedded in
- L74 _private member_ `FScopedTransaction* ScopedTransaction = nullptr;` — Pointer to currently active transaction
- L77 _private member_ `bool bIsManipulating = false;` — True if currently using the transform widget
- L80 _private member_ `UE::Widget::EWidgetMode WidgetMode = UE::Widget::WM_Translate;` — Currently active transform widget type.
- L83 _private member_ `ECoordSystem WidgetCoordSystemSpace = COORD_World;` — Currently active transform widget coord system.
- L86 _private member_ `mutable FVector CachedWidgetLocation = FVector::ZeroVector;` — Cached widget location (updated from slots and annotations before manipulating the gizmo)
- L89 _private member_ `FDelegateHandle SelectionChangedHandle;` — Handle from registered selection change callback in viewmodel

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsEditorModule/Private/SmartObjectComponentVisualizer.h` (Private)


#### struct `HSmartObjectItemProxy`  
`struct HSmartObjectItemProxy : public HHitProxy`  
_L17-32_
- inherits: `HHitProxy`
- desc: Hit proxy for Smart Object slots and annotations.
- L19 _public prototype_ `DECLARE_HIT_PROXY( );`
- L21 _public function_ `HSmartObjectItemProxy(const FGuid InID) : HHitProxy(HPP_Foreground) , ItemID(InID)`
- L26 _public function_ `virtual EMouseCursor::Type GetMouseCursor() override`
- L31 _public member_ `FGuid ItemID;`

#### class `FSmartObjectComponentVisualizer`  
`class FSmartObjectComponentVisualizer : public FComponentVisualizer`  
_L47-52_
- inherits: `FComponentVisualizer`
- desc: Visualizer for SmartObjectComponent
- L50 _protected prototype_ `virtual void DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`
- L51 _protected prototype_ `virtual void DrawVisualizationHUD(const UActorComponent* Component, const FViewport* Viewport, const FSceneView* View, FCanvas* Canvas) override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API SMARTOBJECTSEDITORMODULE_API`
- L37 _namespace_ `namespace UE`
- L37 _namespace_ `namespace SmartObject` (scope `UE`)
- L37 _namespace_ `namespace Editor` (scope `UE::SmartObject`)
- L39 _prototype_ `void Draw(const USmartObjectDefinition& Definition, TConstArrayView<FGuid> Selection, const FTransform& OwnerLocalToWorld, const FSceneView& View, FPrimitiveDrawInterface& PDI, const UWorld& World, const AActor* PreviewActor);` (scope `UE::SmartObject::Editor`)
- L40 _prototype_ `void DrawCanvas(const USmartObjectDefinition& Definition, TConstArrayView<FGuid> Selection, const FTransform& OwnerLocalToWorld, const FSceneView& View, FCanvas& Canvas, const UWorld& World, const AActor* PreviewActor);` (scope `UE::SmartObject::Editor`)

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsEditorModule/Private/SmartObjectDefinitionFactory.h` (Private)


#### class `USmartObjectDefinitionFactory`  
`class USmartObjectDefinitionFactory : public UFactory`  
_L14-20_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFactory`
- desc: Factory responsible to create SmartObjectDefinitions
- L19 _protected prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SMARTOBJECTSEDITORMODULE_API`

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsEditorModule/Private/SmartObjectEditorStyle.h` (Private)


#### class `FSmartObjectEditorStyle`  
`class FSmartObjectEditorStyle final : public FSlateStyleSet`  
_L7-20_
- inherits: `FSlateStyleSet`
- L10 _public prototype_ `virtual ~FSmartObjectEditorStyle();`
- L12 _public prototype_ `static FSmartObjectEditorStyle& Get();`
- L13 _public prototype_ `static void Shutdown();`
- L15 _public member_ `static FColor TypeColor;`
- L17 _private prototype_ `FSmartObjectEditorStyle();`
- L19 _private member_ `static TUniquePtr<FSmartObjectEditorStyle> Instance;`

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsEditorModule/Private/SmartObjectViewModel.h` (Private)


#### class `FSmartObjectViewModel`  
`class FSmartObjectViewModel : public FEditorUndoClient, public TSharedFromThis<FSmartObjectViewModel>`  
_L13-53_
- inherits: `FEditorUndoClient,TSharedFromThis<FSmartObjectViewModel>`
- desc: ModelView for editing Smart Object Asset.
- L16 _public prototype_ `explicit FSmartObjectViewModel(USmartObjectDefinition* InDefinition);`
- L19 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSelectionChanged, TConstArrayView<FGuid> );`
- L20 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSlotsChanged, USmartObjectDefinition* );`
- L22 _public prototype_ `static TSharedPtr<FSmartObjectViewModel> Register(USmartObjectDefinition* InDefinition);`
- L23 _public prototype_ `void Unregister();`
- L24 _public prototype_ `static TSharedPtr<FSmartObjectViewModel> Get(const USmartObjectDefinition* InDefinition);`
- L26 _public prototype_ `void ResetSelection();`
- L27 _public prototype_ `void SetSelection(const TConstArrayView<FGuid> Items);`
- L28 _public prototype_ `void AddToSelection(const FGuid& Item);`
- L29 _public prototype_ `void RemoveFromSelection(const FGuid& Item);`
- L30 _public prototype_ `bool IsSelected(const FGuid& Item) const;`
- L31 _public prototype_ `TConstArrayView<FGuid> GetSelection() const;`
- L34 _public function_ `FOnSelectionChanged& GetOnSelectionChanged()` — Called each time the selection changes.
- L36 _public function_ `FOnSlotsChanged& GetOnSlotsChanged()`
- L38 _public prototype_ `FGuid AddSlot(const FGuid InsertAfterSlotID);`
- L39 _public prototype_ `void MoveSlot(const FGuid SourceSlotID, const FGuid TargetSlotID);`
- L40 _public prototype_ `void RemoveSlot(const FGuid SlotID);`
- L42 _public function_ `USmartObjectDefinition* GetAsset() const`
- L48 _protected member_ `static TArray<TSharedPtr<FSmartObjectViewModel>> AllViewModels;`
- L49 _protected member_ `TWeakObjectPtr<USmartObjectDefinition> WeakDefinition;`
- L50 _protected member_ `TArray<FGuid> Selection;`
- L51 _protected member_ `FOnSelectionChanged OnSelectionChanged;`
- L52 _protected member_ `FOnSlotsChanged OnSlotsChanged;`

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSelectionChanged, TConstArrayView<FGuid> );`
- L20 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSlotsChanged, USmartObjectDefinition* );`

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsEditorModule/Public/SmartObjectAssetEditor.h` (Public)


#### class `USmartObjectAssetEditor`  
`class USmartObjectAssetEditor : public UAssetEditor`  
_L11-24_
- reflection: `UCLASS(Transient)`
- inherits: `UAssetEditor`
- L15 _public prototype_ `void SetObjectToEdit(UObject* InObject);`
- L18 _protected prototype_ `virtual void GetObjectsToEdit(TArray<UObject*>& OutObjectsToEdit) override;`
- L19 _protected prototype_ `virtual TSharedPtr<FBaseAssetToolkit> CreateToolkit() override;`
- L23 _private member_ `TObjectPtr<UObject> ObjectToEdit;` — `UPROPERTY(Transient)`

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsEditorModule/Public/SmartObjectAssetToolkit.h` (Public)


#### class `FSmartObjectAssetToolkit`  
`class FSmartObjectAssetToolkit : public FBaseAssetToolkit, public FSelfRegisteringEditorUndoClient, public FGCObject`  
_L24-110_
- inherits: `FBaseAssetToolkit,FSelfRegisteringEditorUndoClient,FGCObject`
- L27 _public prototype_ `explicit FSmartObjectAssetToolkit(UAssetEditor* InOwningAssetEditor);`
- L28 _public prototype_ `virtual ~FSmartObjectAssetToolkit();`
- L30 _public prototype_ `virtual TSharedPtr<FEditorViewportClient> CreateEditorViewportClient() const override;`
- L33 _protected prototype_ `virtual void PostInitAssetEditor() override;`
- L34 _protected prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L35 _protected prototype_ `virtual void OnClose() override;`
- L36 _protected prototype_ `virtual void SetEditingObject(class UObject* InObject) override;`
- L38 _protected prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L39 _protected function_ `virtual FString GetReferencerName() const override`
- L44 _protected prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L45 _protected prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L49 _private prototype_ `void OnParametersChanged(const USmartObjectDefinition& SmartObjectDefinition);`
- L51 _private prototype_ `void UpdatePreviewActor();`
- L52 _private prototype_ `void UpdateCachedPreviewDataFromDefinition();`
- L54 _private prototype_ `void UpdateItemList();`
- L57 _private prototype_ `void OnPropertyChanged(UObject* ObjectBeingModified, FPropertyChangedEvent& PropertyChangedEvent);` — Callback to detect changes in number of slot to keep gizmos in sync.
- L60 _private prototype_ `TSharedRef<SDockTab> SpawnTab_PreviewSettings(const FSpawnTabArgs& Args);` — Creates a tab allowing the user to select a mesh or actor template to spawn in the preview scene.
- L61 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Outliner(const FSpawnTabArgs& Args);`
- L62 _private prototype_ `TSharedRef<SDockTab> SpawnTab_SelectionDetails(const FSpawnTabArgs& Args);`
- L63 _private prototype_ `TSharedRef<SDockTab> SpawnTab_SceneViewport(const FSpawnTabArgs& Args);`
- L65 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FSmartObjectOutlinerItem> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L66 _private prototype_ `void OnGetChildren(TSharedPtr<FSmartObjectOutlinerItem> InItem, TArray<TSharedPtr<FSmartObjectOutlinerItem>>& OutChildren) const;`
- L67 _private prototype_ `void OnOutlinerSelectionChanged(TSharedPtr<FSmartObjectOutlinerItem> SelectedItem, ESelectInfo::Type SelectType);`
- L68 _private prototype_ `TSharedPtr<SWidget> OnOutlinerContextMenu();`
- L69 _private prototype_ `void HandleSelectionChanged(TConstArrayView<FGuid> Selection);`
- L70 _private prototype_ `void HandleSlotsChanged(USmartObjectDefinition* Definition);`
- L72 _private prototype_ `FReply OnOutlinerDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) const;`
- L73 _private prototype_ `TOptional<EItemDropZone> OnOutlinerCanAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, const TSharedPtr<FSmartObjectOutlinerItem> TargetItem) const;`
- L74 _private prototype_ `FReply OnOutlinerAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, const TSharedPtr<FSmartObjectOutlinerItem> TargetItem);`
- L76 _private prototype_ `void UpdateDetailsSelection();`
- L78 _private prototype_ `FText GetOutlinerItemDescription(TSharedPtr<FSmartObjectOutlinerItem> Item) const;`
- L79 _private prototype_ `FSlateColor GetOutlinerItemColor(TSharedPtr<FSmartObjectOutlinerItem> Item) const;`
- L82 _private member_ `static const FName PreviewSettingsTabID;` — Additional Tab to select mesh/actor to add a 3D preview in the scene.
- L83 _private member_ `static const FName OutlinerTabID;`
- L84 _private member_ `static const FName SceneViewportTabID;`
- L85 _private member_ `static const FName DetailsTabID;`
- L88 _private member_ `TUniquePtr<FAdvancedPreviewScene> AdvancedPreviewScene;` — Scene in which the 3D preview of the asset lives.
- L91 _private member_ `TSharedPtr<IStructureDetailsView> PreviewDetailsView;` — Details view for the preview settings.
- L93 _private member_ `TSharedPtr<FStructOnScope> CachedPreviewData;`
- L95 _private member_ `TSharedPtr<STreeView<TSharedPtr<FSmartObjectOutlinerItem>>> ItemTreeWidget;`
- L96 _private member_ `TArray<TSharedPtr<FSmartObjectOutlinerItem>> ItemList;`
- L97 _private member_ `bool bUpdatingOutlinerSelection = false;`
- L98 _private member_ `bool bUpdatingViewSelection = false;`
- L100 _private member_ `TSharedPtr<SDockTab> DetailsTab;`
- L101 _private member_ `TSharedPtr<IDetailsView> DetailsAssetView;`
- L104 _private member_ `mutable TSharedPtr<class FSmartObjectAssetEditorViewportClient> SmartObjectViewportClient;` — Typed pointer to the custom ViewportClient created by the toolkit.
- L106 _private member_ `TSharedPtr<FSmartObjectViewModel> ViewModel;`
- L108 _private member_ `FDelegateHandle SelectionChangedHandle;`
- L109 _private member_ `FDelegateHandle SlotsChangedHandle;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SMARTOBJECTSEDITORMODULE_API`

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsEditorModule/Public/SmartObjectsEditorModule.h` (Public)


#### class `ISmartObjectsEditorModule`  
`class ISmartObjectsEditorModule : public IModuleInterface`  
_L10-35_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L21 _public function_ `static inline ISmartObjectsEditorModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L31 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsEditorModule/Public/WorldPartitionSmartObjectCollectionBuilder.h` (Public)


#### class `UWorldPartitionSmartObjectCollectionBuilder`  
`class UWorldPartitionSmartObjectCollectionBuilder : public UWorldPartitionBuilder`  
_L18-39_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWorldPartitionBuilder`
- desc: WorldPartitionBuilder dedicated to collect all smart object components from a world and store them in the collection.
- L22 _private prototype_ `static bool CanBuildCollections(const UWorld* InWorld, FName BuildOption);`
- L23 _private prototype_ `static EEditorBuildResult BuildCollections(UWorld* InWorld, FName BuildOption);`
- L26 _protected function_ `virtual bool RequiresCommandletRendering() const override`
- L27 _protected function_ `virtual ELoadingMode GetLoadingMode() const override`
- L28 _protected prototype_ `virtual bool RunInternal(UWorld* World, const FCellInfo& InCellInfo, FPackageSourceControlHelper& PackageHelper) override;`
- L29 _protected prototype_ `virtual bool PreRun(UWorld* World, FPackageSourceControlHelper& PackageHelper) override;`
- L30 _protected prototype_ `virtual bool PostRun(UWorld* World, FPackageSourceControlHelper& PackageHelper, const bool bInRunSuccess) override;`
- L32 _protected member_ `TArray<uint32> NumSmartObjectsBefore;`
- L33 _protected member_ `TArray<uint32> OriginalContentsHash;`
- L34 _protected member_ `uint32 NumSmartObjectsTotal = 0;`
- L36 _protected member_ `bool bRemoveEmptyCollections = false;`
- L38 _protected member_ `TArray<FWorldPartitionReference> SmartObjectReferences;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SMARTOBJECTSEDITORMODULE_API`
