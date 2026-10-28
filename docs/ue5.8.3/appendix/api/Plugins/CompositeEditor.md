# Plugins / CompositeEditor

- module root: `Plugins/Compositing/Composite/Source/CompositeEditor`
- headers: 38; symbols: 583
- symbol kinds: class=35, delegate=11, enum=3, enumerator=9, function=26, member=110, namespace=7, prototype=368, struct=9, typedef=5
- PrivateDependencyModuleNames: AppFramework, ApplicationCore, ColorGradingEditor, CompositeCore, ConcertSyncClient, ContentBrowserData, CoreUObject, DetailCustomizations, EditorScriptingUtilities, EditorWidgets, Engine, InputCore, LevelEditor, LevelSequence, MediaAssets, MediaFrameworkUtilities, MediaProfileEditor, MovieScene, MovieSceneTools, MovieSceneTracks, ObjectMixerEditor, Projects, PropertyEditor, SceneOutliner, Sequencer, Slate, SlateCore, ToolMenus, ToolWidgets, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: Composite, Core

### `Plugins/Compositing/Composite/Source/CompositeEditor/Private/ActorFactories/CompositeActorFactory.h` (Private)


#### class `UCompositeActorFactory`  
`class UCompositeActorFactory : public UActorFactory`  
_L11-24_
- reflection: `UCLASS()`
- inherits: `UActorFactory`
- L17 _public prototype_ `UCompositeActorFactory(const FObjectInitializer& ObjInit);` — Constructor
- L22 _public prototype_ `virtual void PostSpawnActor(UObject* Asset, AActor* NewActor) override;`

### `Plugins/Compositing/Composite/Source/CompositeEditor/Private/ActorFactories/CompositeDepthMeshActorFactory.h` (Private)


#### class `UCompositeDepthMeshActorFactory`  
`class UCompositeDepthMeshActorFactory : public UActorFactory`  
_L11-23_
- reflection: `UCLASS()`
- inherits: `UActorFactory`
- L17 _public prototype_ `UCompositeDepthMeshActorFactory(const FObjectInitializer& ObjInit);` — Constructor
- L21 _public prototype_ `virtual void PostSpawnActor(UObject* Asset, AActor* NewActor) override;`

### `Plugins/Compositing/Composite/Source/CompositeEditor/Private/ActorFactories/CompositeSkySphereActorFactory.h` (Private)


#### class `UCompositeSkySphereActorFactory`  
`class UCompositeSkySphereActorFactory : public UActorFactory`  
_L11-23_
- reflection: `UCLASS()`
- inherits: `UActorFactory`
- L17 _public prototype_ `UCompositeSkySphereActorFactory(const FObjectInitializer& ObjInit);` — Constructor
- L21 _public prototype_ `virtual void PostSpawnActor(UObject* Asset, AActor* NewActor) override;`

### `Plugins/Compositing/Composite/Source/CompositeEditor/Private/ColorGradingDrawer/ColorGradingDataModelGenerator_Composite.h` (Private)


#### class `FColorGradingDataModelGenerator_Composite`  
`class FColorGradingDataModelGenerator_Composite : public IColorGradingEditorDataModelGenerator`  
_L8-22_
- inherits: `IColorGradingEditorDataModelGenerator`
- desc: Color drawer data model generator for UCompositePassColorGrading objects
- L11 _public function_ `static TSharedRef<IColorGradingEditorDataModelGenerator> MakeInstance()`
- L14 _public prototype_ `virtual void Initialize(const TSharedRef<FColorGradingEditorDataModel>& ColorGradingDataModel, const TSharedRef<IPropertyRowGenerator>& PropertyRowGenerator) override;`
- L15 _public prototype_ `virtual void Destroy(const TSharedRef<FColorGradingEditorDataModel>& ColorGradingDataModel, const TSharedRef<IPropertyRowGenerator>& PropertyRowGenerator) override;`
- L16 _public prototype_ `virtual void GenerateDataModel(IPropertyRowGenerator& PropertyRowGenerator, FColorGradingEditorDataModel& OutColorGradingDataModel) override;`
- L21 _private prototype_ `FColorGradingEditorDataModel::FColorGradingElement CreateColorGradingElement(const TSharedRef<IDetailTreeNode>& GroupNode, FText ElementLabel);` — Creates a new color grading element structure for the specified detail tree node, which is expected to have child color properties with the ColorGradingMode metadata set

### `Plugins/Compositing/Composite/Source/CompositeEditor/Private/ColorGradingDrawer/ColorGradingHierarchyConfig_Composite.h` (Private)


#### struct `FColorGradingHierarchyConfig_Composite`  
`struct FColorGradingHierarchyConfig_Composite : IColorGradingMixerObjectHierarchyConfig`  
_L8-17_
- inherits: `IColorGradingMixerObjectHierarchyConfig`
- desc: Color grading mixer hierarchy config for displaying UCompositePassColorGrading objects in the color grading drawer
- L11 _public function_ `static TSharedRef<IColorGradingMixerObjectHierarchyConfig> MakeInstance()`
- L14 _public prototype_ `virtual TArray<FObjectMixerEditorActorSubObject> GetActorSubObjects(UObject* ParentObject) const override;`
- L15 _public prototype_ `virtual TSet<FName> GetPropertiesThatRequireListRefresh() const override;`

### `Plugins/Compositing/Composite/Source/CompositeEditor/Private/ColorGradingDrawer/ColorGradingSelectionHandler_Composite.h` (Private)


#### struct `FColorGradingSelectionHandler_Composite`  
`struct FColorGradingSelectionHandler_Composite : IColorGradingMixerSelectionHandler`  
_L8-21_
- inherits: `IColorGradingMixerSelectionHandler`
- desc: Color grading selection handler that synchronizes selection between the color grading drawer and the Composure panel
- L11 _public prototype_ `static TSharedRef<IColorGradingMixerSelectionHandler> MakeInstance();`
- L14 _public prototype_ `virtual bool CanSelectSubObject(const UObject* InObject) override;`
- L15 _public prototype_ `virtual void SelectSubObjects(const TArray<UObject*>& InSelectedObjects, bool bShouldSelect, bool bSelectEvenIfHidden) const override;`
- L16 _public prototype_ `virtual TArray<UObject*> GetSelectedSubObjectsInEditor() const override;`
- L20 _private prototype_ `void OnComposurePanelSelectionChanged();`

### `Plugins/Compositing/Composite/Source/CompositeEditor/Private/CompositeAnalytics.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Composite`
- L9 _namespace_ `namespace Analytics` (scope `Composite`)
- L12 _prototype_ `void RecordActorAdded(const AActor& Actor);` (scope `Composite::Analytics`) — Records Editor.Usage.Composite.ActorAdded with the actor's class name.
- L15 _prototype_ `void RecordLayerAdded(const UCompositeLayerBase& Layer);` (scope `Composite::Analytics`) — Records Editor.Usage.Composite.LayerAdded with the layer's class name.
- L18 _prototype_ `void RecordPassAdded(const UCompositePassBase& Pass);` (scope `Composite::Analytics`) — Records Editor.Usage.Composite.PassAdded with the pass's class name.

### `Plugins/Compositing/Composite/Source/CompositeEditor/Private/CompositeEditorCommands.h` (Private)


#### class `FCompositeEditorCommands`  
`class FCompositeEditorCommands : public TCommands<FCompositeEditorCommands>`  
_L11-27_
- inherits: `TCommands<FCompositeEditorCommands>`
- desc: UI commands for actions that are specific to Composite editor
- L14 _public function_ `FCompositeEditorCommands() : TCommands<FCompositeEditorCommands>( "CompositeEditor", NSLOCTEXT("FCompositeEditorCommands", "CompositeEditor", "Composite Editor"), NAME_None, FAppStyle::GetAppStyleSetName() )`
- L22 _public prototype_ `virtual void RegisterCommands() override;`
- L25 _public member_ `TSharedPtr<FUICommandInfo> Enable;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> RemoveActor;`

### `Plugins/Compositing/Composite/Source/CompositeEditor/Private/CompositeEditorStyle.h` (Private)


#### class `FCompositeEditorStyle`  
`class FCompositeEditorStyle final : public FSlateStyleSet`  
_L6-16_
- inherits: `FSlateStyleSet`
- L9 _public prototype_ `static FCompositeEditorStyle& Get();`
- L11 _public prototype_ `static void Register();`
- L12 _public prototype_ `static void Unregister();`
- L15 _private prototype_ `FCompositeEditorStyle();`

### `Plugins/Compositing/Composite/Source/CompositeEditor/Private/Customizations/CompositeActorCustomization.h` (Private)


#### class `FCompositeActorCustomization`  
`class FCompositeActorCustomization : public IDetailCustomization`  
_L13-30_
- inherits: `IDetailCustomization`
- desc: Customization for the composite actor.
- L17 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of the details customization
- L20 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L25 _private prototype_ `FReply OpenComposurePanel();` — Raised when the 'Open Composure' button is clicked, and opens the Composure panel
- L29 _private member_ `TArray<TWeakObjectPtr<ACompositeActor>> CompositeActors;` — List of composite actors being displayed by this customization

### `Plugins/Compositing/Composite/Source/CompositeEditor/Private/Customizations/CompositeCustomizationHelpers.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace CompositeCustomizationHelpers`
- L18 _prototype_ `void CustomizeCameraActorProperty(IDetailLayoutBuilder& DetailLayout, TSharedPtr<IPropertyHandle> CameraActorHandle);` (scope `CompositeCustomizationHelpers`) — Customize a CameraActor soft object property to show an actor picker filtered to actors with a UCameraComponent. Shows transient actors (e.g. Sequencer spawnables) in the picker.
- L27 _prototype_ `bool ShouldFilterAssetByAllowedClasses(const FAssetData& AssetData, const TSharedRef<IPropertyHandle>& PropertyHandle);` (scope `CompositeCustomizationHelpers`) — Asset filter predicate that consults the property's AllowedClasses / DisallowedClasses metadata. Returns true (filter the asset OUT) when the asset's class is not a child of any AllowedClasses entry, or when it is a child of a DisallowedClasses entry. Returns false (keep the asset) when the metadata is empty or absent. Use as the OnShouldFilterAsset predicate for asset pickers so the metadata on the UPROPERTY remains the single source of truth.

### `Plugins/Compositing/Composite/Source/CompositeEditor/Private/Customizations/CompositeDepthMeshComponentCustomization.h` (Private)


#### class `FCompositeDepthMeshComponentCustomization`  
`class FCompositeDepthMeshComponentCustomization : public IDetailCustomization`  
_L10-23_
- inherits: `IDetailCustomization`
- desc: Customization for the composite depth mesh component.
- L14 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of the details customization
- L17 _public prototype_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& DetailBuilder) override;` — IDetailCustomization interface
- L18 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L22 _private member_ `TWeakPtr<IDetailLayoutBuilder> CachedDetailBuilder;`

### `Plugins/Compositing/Composite/Source/CompositeEditor/Private/Customizations/CompositeLayerCustomization.h` (Private)


#### class `FCompositeLayerCustomization`  
`class FCompositeLayerCustomization : public IDetailCustomization`  
_L37-93_
- inherits: `IDetailCustomization`
- desc: Common base for all composite-layer detail customizations. Owns the shared layout-builder cache and pass-panel weak ptr, finalizes the IDetailCustomization dispatch (caches the builder, then forwards to CustomizeLayerDetails), and provides the helpers every layer customization needs: - AddDefaultLayerProperties: re-adds the default "Composite" simple-tier properties to a category in declaration order, with the inherited LayerPasses array filtered out by construction. - AddPassesGroup: hides LayerPasses and inserts the SCompositePassTreePanel group at the current insertion point, falling back to a "Multiple Values" row when multiple objects are selected. - HideLayerPasses: standalone hide for layers that drive their own pass tree (Plate). - RequestLayoutRefresh: invalidates the layout when a child widget reports a size change. SCompositeEditorPanel `static_cast`s stored IDetailCustomizations to this base when iterating customizations registered on UCompositeLayerBase-derived classes. UE modules disable RTTI, so the cast is the supported way to reach IsCustomizingObject / GetPassPanelWidget.
- L41 _public prototype_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& DetailBuilder) override final;`
- L42 _public function_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override final`
- L46 _public prototype_ `virtual void CustomizeLayerDetails(IDetailLayoutBuilder& InDetailLayout) = 0;` — Layer-specific layout. Called after the base has cached the builder.
- L49 _public prototype_ `TSharedPtr<SCompositePassTreePanel> GetPassPanelWidget() const;` — Pass panel widget hosted by this customization, if alive.
- L52 _public prototype_ `bool IsCustomizingObject(UObject* InObject) const;` — True if this customization is currently customizing the given object.
- L56 _public prototype_ `void RequestLayoutRefresh();` — Forces the cached layout to regenerate. Public so derived classes can bind it as a SLATE_EVENT callback via FSimpleDelegate::CreateSP.
- L59 _protected typedef_ `using FOnRowAdded = TFunction<void(const TSharedRef<IPropertyHandle>&, IDetailPropertyRow&)>;`
- L68 _protected prototype_ `void AddDefaultLayerProperties( IDetailCategoryBuilder& InCategory, TArrayView<const FName> InAdditionalHidden = {}, const FOnRowAdded& InOnRowAdded = nullptr);` — Adds the default simple-tier properties of InCategory in declaration order, skipping the inherited UCompositeLayerBase::LayerPasses (handled by AddPassesGroup) and any names in InAdditionalHidden. Already-customized properties are skipped to avoid double-adding rows. If supplied, InOnRowAdded runs for each added row, allowing per-property overrides.
- L80 _protected prototype_ `void AddPassesGroup( IDetailLayoutBuilder& InDetailLayout, IDetailCategoryBuilder& InCategory, UCompositeLayerBase* InLayer);` — Hides the inherited LayerPasses property and adds a "Passes" group to InCategory hosting an SCompositePassTreePanel over the layer's LayerPasses array. Pass nullptr for InLayer when multiple objects are selected; the helper inserts a "Multiple Values" row instead. Stores the created panel as PassPanel.
- L89 _protected prototype_ `void HideLayerPasses(IDetailLayoutBuilder& InDetailLayout);` — Hides the inherited UCompositeLayerBase::LayerPasses property. Use when the layer drives its own pass tree and AddPassesGroup is not appropriate.
- L91 _protected member_ `TWeakPtr<IDetailLayoutBuilder> CachedDetailBuilder;`
- L92 _protected member_ `TWeakPtr<SCompositePassTreePanel> PassPanel;`

### `Plugins/Compositing/Composite/Source/CompositeEditor/Private/Customizations/CompositeLayerPlanarReflectionCustomization.h` (Private)


#### class `FCompositeLayerPlanarReflectionCustomization`  
`class FCompositeLayerPlanarReflectionCustomization : public FCompositeLayerCustomization`  
_L12-21_
- inherits: `FCompositeLayerCustomization`
- desc: Customization for the composite planar reflection layer, primarily for displaying custom widgets for picking actors and managing passes
- L16 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of the details customization
- L19 _public prototype_ `virtual void CustomizeLayerDetails(IDetailLayoutBuilder& InDetailLayout) override;`

### `Plugins/Compositing/Composite/Source/CompositeEditor/Private/Customizations/CompositeLayerPlateCustomization.h` (Private)


#### class `FCompositeLayerPlateCustomization`  
`class FCompositeLayerPlateCustomization : public FCompositeLayerCustomization`  
_L22-128_
- inherits: `FCompositeLayerCustomization`
- desc: Customization for the composite plate layer, primary for displaying a custom widget for passes and composite meshes
- L26 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of the details customization
- L29 _public prototype_ `virtual void CustomizeLayerDetails(IDetailLayoutBuilder& InDetailLayout) override;`
- L32 _public prototype_ `TSharedPtr<SCompositeActorPickerTable> GetCompositeMeshPickerWidget() const;`
- L36 _private prototype_ `void CustomizeTexturePropertyRow(const TSharedPtr<IPropertyHandle>& InPropertyHandle, IDetailPropertyRow& InPropertyRow);` — Customizes the Texture property in UCompositeLayerPlate to add in the media profile source selector
- L39 _private prototype_ `void OnHiddenColumnsListChanged();` — Raised when the user has hidden columns in the composite mesh actor picker table
- L42 _private prototype_ `TSharedRef<SWidget> GetCompositeMeshColumnWidget(const TSoftObjectPtr<AActor>& InActor, const FName& InColumnName);` — Creates the widget to display for each actor in the Components column of the actor picker table
- L45 _private prototype_ `FText GetCompositeMeshMaterialLabel(TSoftObjectPtr<AActor> Actor) const;` — Gets the label to display for the Material column for each actor in the actor picker table
- L48 _private prototype_ `FText GetCompositeMeshComponentsLabel(TSoftObjectPtr<AActor> InActor) const;` — Gets the label to display for each actor in the Components column of the actor picker table
- L51 _private prototype_ `void OnExtendCompositeMeshAddMenu(FMenuBuilder& MenuBuilder);` — Raised by the composite mesh actor list when building the Add Actor menu
- L54 _private prototype_ `void SetAutoApplyMaterial(bool bInAutoApplyMaterial);` — Sets the AutoApplyMaterial flag to the specified value
- L57 _private prototype_ `bool IsAutoApplyMaterialChecked(bool bInAutoApplyMaterial) const;` — Checks if the AutoApplyMaterial flag is set to the specified value
- L60 _private prototype_ `FText GetMaterialSubMenuLabel() const;` — Gets the label for the Material selector sub menu in the Add menu
- L63 _private prototype_ `void CreateMaterialSubMenu(FMenuBuilder& InMenuBuilder);` — Creates the Material selector submenu in the Add menu
- L66 _private prototype_ `void SetAutoAppliedMaterialType(ECompositeMeshAppliedMaterialType InMaterialType);` — Sets the material type of the auto-applied material
- L69 _private prototype_ `bool IsAutoAppliedMaterialTypeChecked(ECompositeMeshAppliedMaterialType InMaterialType) const;` — Gets whether the specified material type is the currently selected type
- L72 _private prototype_ `FText GetCustomMaterialEntryLabel() const;` — Gets the label for the custom material menu entry in the Add dropdown menu
- L75 _private prototype_ `bool CanApplyCustomMaterial() const;` — Gets whether a custom material can currently be auto-applied
- L78 _private prototype_ `void OnCustomMaterialSelected(const FAssetData& AssetData);` — Raised when a new custom material is selected from the material browser in the Material submenu
- L81 _private prototype_ `void OnExtendCompositeMeshContextMenu(FMenuBuilder& MenuBuilder, TArray<TSoftObjectPtr<AActor>>& SelectedActors);` — Raised by the composite mesh actor list when building the context menu
- L84 _private prototype_ `void OnCompositeMeshActorToggled(TSoftObjectPtr<AActor> InActor);` — Raised when the composite mesh actor's entry in the Component section of the context menu is toggled
- L87 _private prototype_ `bool CanToggleCompositeMeshActor(TSoftObjectPtr<AActor> InActor) const;` — Gets whether the composite mesh actor's entry in the Component section of the context menu can be toggled
- L90 _private prototype_ `bool IsCompositeMeshActorChecked(TSoftObjectPtr<AActor> InActor) const;` — Gets the check state for the composite mesh actor's entry in the Component section of the context menu
- L93 _private prototype_ `void OnCompositeMeshPrimitiveToggled(TSoftObjectPtr<AActor> InActor, UPrimitiveComponent* InPrimitive);` — Raised when a composite mesh primitive entry is toggled in the Component section of the context menu
- L96 _private prototype_ `bool IsCompositeMeshPrimitiveChecked(TSoftObjectPtr<AActor> InActor, UPrimitiveComponent* InPrimitive) const;` — Gets whether a composite mesh primitive entry is checked in the Component section of the context menu
- L99 _private prototype_ `void OnCompositeMeshActorsAdded(TArray<TSoftObjectPtr<AActor>>& InActors);` — Raised when actors are added to the Plate's CompositeMeshes list
- L102 _private prototype_ `void ApplyMaterialToActor(TSoftObjectPtr<AActor>& InActor, UMaterialInterface* InMaterial);` — Raised when a material should be appplied to an actor in the actor picker list
- L105 _private prototype_ `void CreateCompositeMeshActor();` — Creates a composite mesh actor at the appropriate position in the level and adds it to the plate's composite meshes list
- L108 _private prototype_ `void CreateCompositeDepthMeshActor();` — Creates a composite depth mesh actor at the appropriate position in the level and adds it to the plate's composite meshes list
- L111 _private prototype_ `bool CanCreateCompositeMeshActor() const;` — Gets whether a composite mesh actor can be created for this plate layer
- L114 _private prototype_ `TSharedRef<SWidget> GetSkySphereActorMenu();` — Gets the dropdown menu widget to display when the sky sphere button is pressed
- L117 _private prototype_ `void PlaceCompositeSkySphereActor();` — Spawns a CompositeSkySphereActor in the current level
- L120 _private prototype_ `bool CanPlaceCompositeSkySphereActor() const;` — Gets whether a sky sphere actor can be placed
- L123 _private member_ `TWeakPtr<SCompositeActorPickerTable> CompositeMeshPicker;`
- L124 _private member_ `TSharedPtr<IPropertyHandle> TexturePropertyHandle;`
- L127 _private member_ `FAssetData CustomMaterialAsset = FAssetData();` — The custom material the user has selected to auto-apply to actors added to the composite meshes list

### `Plugins/Compositing/Composite/Source/CompositeEditor/Private/Customizations/CompositeLayerSceneCaptureCustomization.h` (Private)


#### class `FCompositeLayerSceneCaptureCustomization`  
`class FCompositeLayerSceneCaptureCustomization : public FCompositeLayerCustomization`  
_L12-21_
- inherits: `FCompositeLayerCustomization`
- desc: Customization for the composite scene capture layer, primary for displaying a custom widget for picking actors
- L16 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of the details customization
- L19 _public prototype_ `virtual void CustomizeLayerDetails(IDetailLayoutBuilder& InDetailLayout) override;`

### `Plugins/Compositing/Composite/Source/CompositeEditor/Private/Customizations/CompositeLayerShadowReflectionCustomization.h` (Private)


#### class `FCompositeLayerShadowReflectionCustomization`  
`class FCompositeLayerShadowReflectionCustomization : public FCompositeLayerCustomization`  
_L12-21_
- inherits: `FCompositeLayerCustomization`
- desc: Customization for the composite shadow/reflection layer, primarily for displaying custom widgets for picking actors and managing passes
- L16 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of the details customization
- L19 _public prototype_ `virtual void CustomizeLayerDetails(IDetailLayoutBuilder& InDetailLayout) override;`

### `Plugins/Compositing/Composite/Source/CompositeEditor/Private/Customizations/CompositeLayerSimplePassesCustomization.h` (Private)


#### class `FCompositeLayerSimplePassesCustomization`  
`class FCompositeLayerSimplePassesCustomization : public FCompositeLayerCustomization`  
_L14-22_
- inherits: `FCompositeLayerCustomization`
- desc: Customization for layers that only need the standard "Composite" category rename + a Passes group over the inherited UCompositeLayerBase::LayerPasses array. Used by UCompositeLayerMainRender and UCompositeLayerProcessing, which have no other custom widgets.
- L17 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L20 _public prototype_ `virtual void CustomizeLayerDetails(IDetailLayoutBuilder& InDetailLayout) override;`

### `Plugins/Compositing/Composite/Source/CompositeEditor/Private/Customizations/CompositeLayerSingleLightShadowCustomization.h` (Private)


#### class `FCompositeLayerSingleLightShadowCustomization`  
`class FCompositeLayerSingleLightShadowCustomization : public FCompositeLayerCustomization`  
_L12-21_
- inherits: `FCompositeLayerCustomization`
- desc: Customization for the composite single light shadow layer, for displaying custom widgets for picking actors and managing passes
- L16 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of the details customization
- L19 _public prototype_ `virtual void CustomizeLayerDetails(IDetailLayoutBuilder& InDetailLayout) override;`

### `Plugins/Compositing/Composite/Source/CompositeEditor/Private/Customizations/CompositePassBaseCustomization.h` (Private)


#### class `FCompositePassBaseCustomization`  
`class FCompositePassBaseCustomization : public IDetailCustomization`  
_L10-24_
- inherits: `IDetailCustomization`
- desc: Base customization for all derivations of UCompositePassBase
- L13 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L15 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;`
- L23 _protected prototype_ `void CustomizeIsEnabledProperty(IDetailLayoutBuilder& DetailLayout, bool bInPlace = true);` — Renames the IsEnabled property on the composite pass to reference the property owner's type (e.g. 'Enable Color Grading Pass') @param DetailLayout The detail layout builder @param bInPlace Whether the IsEnabled property should remain in its default position or be placed with the rest of the customized properties

### `Plugins/Compositing/Composite/Source/CompositeEditor/Private/Customizations/CompositePassColorKeyerCustomization.h` (Private)


#### class `FCompositePassColorKeyerCustomization`  
`class FCompositePassColorKeyerCustomization : public FCompositePassBaseCustomization`  
_L17-88_
- inherits: `FCompositePassBaseCustomization`
- desc: Customization for UCompositePassColorKeyer, which reorganizes some properties, and adds a 'Capture Clean Plate' button for simple clean plate capturing
- L20 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L22 _public prototype_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& DetailBuilder) override;`
- L23 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L26 _private prototype_ `void CaptureMediaTexture();`
- L29 _private prototype_ `void OnPreviewSizeChanged();` — Raised when the PlateTexturePreviewSize property changes values
- L32 _private prototype_ `TSharedRef<SWidget> CreateRGBNumericEntryWidget();` — Creates the custom RGB single row widget, which contains color-coded numeric spinners for each component
- L35 _private prototype_ `TSharedRef<SWidget> CreateCaptureButtonWidget();` — Creates the clean plate capture button widget
- L38 _private prototype_ `float GetCaptureCountdown() const;` — Gets the capture countdown property value on the UCompositePassColorKeyer objects being customized
- L41 _private prototype_ `TOptional<float> GetRGBWeightValue(TSharedPtr<IPropertyHandle> InPropertyHandle) const;` — Gets the RGB weight value for the specified component of the RGB property
- L44 _private prototype_ `void ChangeRGBWeightValue(float InNewValue, TSharedPtr<IPropertyHandle> InPropertyHandle);` — Sets the RGB weight value for the specified component of the RGB property
- L47 _private prototype_ `void CommitRGBWeightValue(float InNewValue, ETextCommit::Type InCommitType, TSharedPtr<IPropertyHandle> InPropertyHandle);` — Commits the RGB weight value for the specified component of the RGB property
- L50 _private prototype_ `bool IsRGBWeightEditable(TSharedPtr<IPropertyHandle> InPropertyHandle) const;` — Gets whether the RGB weight is editable for the  specified component of the RGB property
- L53 _private prototype_ `TOptional<float> GetRGBWeightMin(TSharedPtr<IPropertyHandle> InPropertyHandle) const;` — Gets the minimum RGB weight from the property metadata for the  specified component of the RGB property
- L56 _private prototype_ `TOptional<float> GetRGBWeightMax(TSharedPtr<IPropertyHandle> InPropertyHandle) const;` — Gets the maximum RGB weight from the property metadata for the  specified component of the RGB property
- L59 _private prototype_ `EVisibility GetCaptureButtonVisibility() const;` — Gets the visibility state of the 'Capture Clean Plate' button
- L62 _private prototype_ `bool IsCaptureButtonEnabled() const;` — Gets whether the 'Capture Clean Plate' button is enabled or not
- L66 _private member_ `TWeakPtr<IDetailLayoutBuilder> CachedDetailBuilder;` — Cached detail layout builder pointer, used to manually refresh the details panel
- L69 _private member_ `TSharedPtr<IPropertyHandle> KeyerSourceHandle;` — Property handle for UCompositePassColorKeyer.KeyerSource property
- L72 _private member_ `TSharedPtr<IPropertyHandle> PreviewSizeHandle;` — Property handle for UCompositePassColorKeyer.PlateTexturePreviewSize property
- L75 _private member_ `TSharedPtr<IPropertyHandle> CountdownHandle;` — Property handle for UCompositePassKeyer.CleanPlateCountdown property
- L78 _private member_ `TSharedPtr<IPropertyHandle> RedWeightHandle;` — Property handle for R component of the UCompositePassKeyer.RGBWeight property
- L81 _private member_ `TSharedPtr<IPropertyHandle> GreenWeightHandle;` — Property handle for G component of the UCompositePassKeyer.RGBWeight property
- L84 _private member_ `TSharedPtr<IPropertyHandle> BlueWeightHandle;` — Property handle for B component of the UCompositePassKeyer.RGBWeight property
- L87 _private member_ `TStrongObjectPtr<UMaterialInstanceDynamic> CaptureCleanPlateMID;` — Transient dynamic material instance used to capture a clean plate texture from the keyer's media source

### `Plugins/Compositing/Composite/Source/CompositeEditor/Private/Customizations/CompositePassMaskingCustomization.h` (Private)


#### class `FCompositePassMaskingCustomization`  
`class FCompositePassMaskingCustomization : public FCompositePassBaseCustomization`  
_L13-25_
- inherits: `FCompositePassBaseCustomization`
- desc: Customization for UCompositePassMasking that swaps the MaskTexture property's value widget for a media profile source texture picker.
- L16 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L18 _public prototype_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& DetailBuilder) override;`
- L19 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;`
- L22 _private prototype_ `void CustomizeMaskTexturePropertyRow(const TSharedPtr<IPropertyHandle>& InPropertyHandle, IDetailPropertyRow& InPropertyRow);`
- L24 _private member_ `TWeakPtr<IDetailLayoutBuilder> CachedDetailBuilder;`

### `Plugins/Compositing/Composite/Source/CompositeEditor/Private/Customizations/CompositeRenderTargetResolutionCustomization.h` (Private)


#### class `FResolutionTypeCustomization`  
`class FResolutionTypeCustomization : public IPropertyTypeCustomization`  
_L14-53_
- inherits: `IPropertyTypeCustomization`
- desc: Property type customization for FIntPoint render target resolution properties. Displays a resolution combobox with named presets and an aspect ratio lock.
- L29 _public typedef_ `using FNamedResolutionPtr = TSharedPtr<FNamedResolution>;`
- L31 _public member_ `static TArray<FNamedResolutionPtr> NamedResolutions;`
- L33 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L34 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L37 _private prototype_ `FText GetResolutionText() const;`
- L38 _private prototype_ `void SetResolution(FNamedResolutionPtr InNamedResolution, ESelectInfo::Type SelectInfo);`
- L39 _private prototype_ `bool GetAspectRatio(double& OutAspectRatio) const;`
- L40 _private prototype_ `void SetDimensionFromAspectRatio(const TSharedPtr<IPropertyHandle>& SrcDimHandle, const TSharedPtr<IPropertyHandle>& DestDimHandle, double AspectRatio);`
- L43 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;`
- L44 _private member_ `TSharedPtr<IPropertyHandle> XPropertyHandle;`
- L45 _private member_ `TSharedPtr<IPropertyHandle> YPropertyHandle;`
- L47 _private member_ `TSharedPtr<SComboBox<FNamedResolutionPtr>> ResolutionComboBox;`
- L49 _private member_ `TOptional<double> LockedAspectRatio = TOptional<double>();`
- L51 _private member_ `bool bAspectRatioRecursionGuard = false;`
- L52 _private member_ `bool bSettingNamedResolution = false;`

#### struct `FResolutionTypeCustomization::FNamedResolution`  
`struct FNamedResolution`  
_L17-28_
- L19 _public member_ `FText Name = FText::GetEmpty();`
- L20 _public member_ `FIntPoint Resolution = FIntPoint::ZeroValue;`
- L21 _public member_ `FText ToolTip = FText::GetEmpty();`
- L23 _public function_ `FNamedResolution(const FText& InName, const FIntPoint& InResolution, const FText& InToolTip) : Name(InName) , Resolution(InResolution) , ToolTip(InToolTip)`

#### class `FResolutionPropertyIdentifier`  
`class FResolutionPropertyIdentifier : public IPropertyTypeIdentifier`  
_L59-66_
- inherits: `IPropertyTypeIdentifier`
- desc: Property type identifier that matches FIntPoint properties named "RenderTargetResolution", selecting them for FResolutionTypeCustomization.
- L62 _public function_ `virtual bool IsPropertyTypeCustomized(const IPropertyHandle& PropertyHandle) const override`

### `Plugins/Compositing/Composite/Source/CompositeEditor/Private/Customizations/CompositeSkySphereActorCustomization.h` (Private)


#### class `FCompositeSkySphereActorCustomization`  
`class FCompositeSkySphereActorCustomization : public IDetailCustomization`  
_L20-37_
- inherits: `IDetailCustomization`
- desc: Details customization for ACompositeSkySphereActor. Registers section filter pills (General | Light | Materials | Ray Tracing | Static Mesh | Texture | All) via FPropertyEditorModule::FindOrCreateSection so they appear in the native UE5 pill row at the top of the Details panel. Also adds a media profile source picker to the Texture property, matching the plate layer UX.
- L24 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of the details customization
- L27 _public prototype_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& DetailBuilder) override;`
- L28 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;`
- L33 _private prototype_ `void CustomizeSections();` — Registers section filter pills via FPropertyEditorModule::FindOrCreateSection.
- L36 _private member_ `TWeakPtr<IDetailLayoutBuilder> CachedDetailBuilder;` — Cached layout builder for thumbnail pool access.

### `Plugins/Compositing/Composite/Source/CompositeEditor/Private/Customizations/CompositeViewProjectionComponentCustomization.h` (Private)


#### class `FCompositeViewProjectionComponentCustomization`  
`class FCompositeViewProjectionComponentCustomization : public IDetailCustomization`  
_L10-19_
- inherits: `IDetailCustomization`
- desc: Customization for the view projection component.
- L14 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of the details customization
- L17 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface

### `Plugins/Compositing/Composite/Source/CompositeEditor/Private/Sequencer/CompositeActorObjectSchema.h` (Private)


#### class `UE::Sequencer::FCompositeActorObjectSchema`  
`class FCompositeActorObjectSchema : public IObjectSchema`  
_L25-50_
- inherits: `IObjectSchema`
- desc: Object schema that exposes ACompositeActor layers and their passes as possessable sub-objects in the Sequencer outliner. Handles two nesting levels: Actor -> Layers  (UCompositeLayerBase children of ACompositeActor) Layer -> Passes  (UCompositePassBase children of UCompositeLayerBase)
- L29 _public prototype_ `virtual UObject* GetParentObject(UObject* Object) const override;`
- L30 _public prototype_ `virtual FObjectSchemaRelevancy GetRelevancy(const UObject* InObject) const override;`
- L31 _public prototype_ `virtual TSharedPtr<FExtender> ExtendObjectBindingMenu(TSharedRef<FUICommandList> CommandList, TWeakPtr<ISequencer> WeakSequencer, TArrayView<UObject* const> ContextSensitiveObjects) const override;`
- L32 _public prototype_ `virtual FText GetPrettyName(const UObject* Object) const override;`
- L37 _private prototype_ `void HandleActorTrackMenu(FMenuBuilder& MenuBuilder, TWeakPtr<ISequencer> WeakSequencer, TArray<ACompositeActor*> Actors) const;` — Populates the actor-level track menu with composite layers and actor components not yet bound in Sequencer.
- L40 _private prototype_ `void HandleLayerTrackMenu(FMenuBuilder& MenuBuilder, TWeakPtr<ISequencer> WeakSequencer, TArray<UCompositeLayerBase*> Layers) const;` — Populates the layer-level track menu with composite passes (from all pass arrays) not yet bound in Sequencer.
- L43 _private prototype_ `void HandleAddLayerExecute(TWeakObjectPtr<UCompositeLayerBase> Layer, TWeakPtr<ISequencer> WeakSequencer) const;` — Creates a possessable binding for a composite layer in a scoped undo transaction.
- L46 _private prototype_ `void HandleAddPassExecute(TWeakObjectPtr<UCompositePassBase> Pass, TWeakPtr<ISequencer> WeakSequencer) const;` — Creates a possessable binding for a composite pass in a scoped undo transaction.
- L49 _private prototype_ `void HandleAddComponentExecute(TWeakObjectPtr<UActorComponent> Component, TWeakPtr<ISequencer> WeakSequencer) const;` — Creates a possessable binding for an actor component in a scoped undo transaction.

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Sequencer` (scope `UE`)

### `Plugins/Compositing/Composite/Source/CompositeEditor/Private/Sequencer/CompositeDetailKeyframeHandler.h` (Private)


#### class `FCompositeDetailKeyframeHandler`  
`class FCompositeDetailKeyframeHandler : public IDetailKeyframeHandler`  
_L14-25_
- inherits: `IDetailKeyframeHandler`
- desc: Keyframe handler for the Composite editor panel's DetailsView. Delegates to active Sequencer instances obtained from FLevelEditorSequencerIntegration. Stateless — queries live sequencer state on each call so it handles Sequencer open/close automatically.
- L17 _public prototype_ `virtual bool IsPropertyKeyable(const UClass* InObjectClass, const IPropertyHandle& PropertyHandle) const override;`
- L18 _public prototype_ `virtual bool IsPropertyKeyingEnabled() const override;`
- L19 _public prototype_ `virtual bool IsPropertyAnimated(const IPropertyHandle& PropertyHandle, UObject* ParentObject) const override;`
- L20 _public prototype_ `virtual void OnKeyPropertyClicked(const IPropertyHandle& KeyedPropertyHandle) override;`
- L21 _public prototype_ `virtual EPropertyKeyedStatus GetPropertyKeyedStatus(const IPropertyHandle& PropertyHandle) const override;`
- L24 _private prototype_ `TArray<TWeakPtr<ISequencer>> GetSequencers() const;`

### `Plugins/Compositing/Composite/Source/CompositeEditor/Private/UI/CompositeEditorPanelSettings.h` (Private)


#### enum `ECompositeMeshAppliedMaterialType`  
`enum class ECompositeMeshAppliedMaterialType : uint8`  
_L10-15_
- reflection: `UENUM()`
- L12 _public enumerator_ `LitMaskedMaterial`
- L13 _public enumerator_ `UnlitAlphaMaterial`
- L14 _public enumerator_ `CustomMaterial`

#### enum `ECompositeMeshVisualizationMode`  
`enum class ECompositeMeshVisualizationMode : uint8`  
_L19-29_
- reflection: `UENUM()`
- desc: Mode controlling the composite mesh visualization overlay driven by the MPC_Composite "MeshVisualization" scalar.
- L22 _public enumerator_ `Disabled` — Visualization overlay is off.
- L25 _public enumerator_ `EnabledWhenNotPiloting` — Overlay is shown only while the active composite actor's camera is not being piloted.
- L28 _public enumerator_ `Enabled` — Overlay is always shown.

#### class `UCompositeEditorPanelSettings`  
`class UCompositeEditorPanelSettings : public UObject`  
_L33-57_
- reflection: `UCLASS(MinimalAPI, Config=EditorPerProjectUserSettings)`
- inherits: `UObject`
- desc: Settings for the Composure panel
- L40 _public member_ `bool bAutoApplyCompositeMeshMaterial = true;` — `UPROPERTY(Config)` — Whether the selected material is applied to actors that are added to the composite meshes list in the Plate layer
- L44 _public member_ `ECompositeMeshAppliedMaterialType CompositeMeshMaterialType = ECompositeMeshAppliedMaterialType::LitMaskedMaterial;` — `UPROPERTY(Config)` — The material type to apply to actors that are added to the composite meshes list in the Plate layer
- L48 _public member_ `TArray<FName> CompositeMeshTableHiddenColumns = TArray<FName>();` — `UPROPERTY(Config)` — List of columns that have been hidden by the user in the composite meshes list in the Plate layer
- L52 _public member_ `bool bSyncActorSelection = true;` — `UPROPERTY(Config)` — Indicates that actor pickers in the Composure panel will sync their selection with the editor selection
- L56 _public member_ `ECompositeMeshVisualizationMode MeshVisualizationMode = ECompositeMeshVisualizationMode::Disabled;` — `UPROPERTY(Config)` — Composite mesh visualization mode driving the MPC_Composite.MeshVisualization scalar.

### `Plugins/Compositing/Composite/Source/CompositeEditor/Private/UI/CompositeLayerPassListOwner.h` (Private)


#### class `FCompositeLayerPassListOwner`  
`class FCompositeLayerPassListOwner : public ICompositePassListOwner`  
_L15-44_
- inherits: `ICompositePassListOwner`
- desc: ICompositePassListOwner for any layer with a single LayerPasses array on UCompositeLayerBase. Plate uses its own multi-group owner (FCompositePlatePassListOwner) since it has Media/Scene/Layer arrays.
- L18 _public prototype_ `explicit FCompositeLayerPassListOwner(const TWeakObjectPtr<UCompositeLayerBase>& InLayer);`
- L20 _public prototype_ `virtual bool IsObjectValid() override;`
- L21 _public prototype_ `virtual TStrongObjectPtr<UObject> GetObject() override;`
- L22 _public prototype_ `virtual bool IsPassListPropertyName(const FName& InPropertyName) override;`
- L23 _public prototype_ `virtual bool IsValidPassIndex(int32 InGroupIndex, int32 InPassIndex) override;`
- L24 _public prototype_ `virtual UCompositePassBase* GetPass(int32 InGroupIndex, int32 InPassIndex) override;`
- L25 _public function_ `virtual int32 GetNumGroups() const override`
- L26 _public prototype_ `virtual TArray<TObjectPtr<UCompositePassBase>>& GetPassesForGroup(int32 InGroupIndex) override;`
- L28 _public function_ `virtual FString GetGroupFilterString(int32 InGroupIndex) override`
- L29 _public function_ `virtual const FSlateBrush* GetGroupIcon(int32 InGroupIndex) override`
- L30 _public function_ `virtual FText GetGroupDisplayName(int32 InGroupIndex) override`
- L31 _public function_ `virtual FGroupFilterConfig GetGroupFilterConfig(int32 InGroupIndex) override`
- L32 _public function_ `virtual int32 GetDefaultGroupForNewPass(const UClass* InPassClass) const override`
- L34 _public prototype_ `virtual bool CanAddPass(const UClass* InPassClass, int32 InGroupIndex, int32 InPassIndex) const override;`
- L35 _public prototype_ `virtual int32 AddPass(const UClass* InPassClass, int32 InGroupIndex, int32 InPassIndex) override;`
- L36 _public prototype_ `virtual TArray<int32> CopyPasses(const TArray<UCompositePassBase*>& InPassesToCopy, int32 InGroupIndex, int32 InPassIndex) override;`
- L37 _public prototype_ `virtual void MovePass(int32 InSourceGroupIndex, int32 InSourcePassIndex, int32 InDestGroupIndex, int32 InDestPassIndex) override;`
- L38 _public prototype_ `virtual void RemovePasses(int32 InGroupIndex, const TArray<int32>& InPassIndices) override;`
- L41 _private prototype_ `static FProperty* GetPassListProperty();`
- L43 _private member_ `TWeakObjectPtr<UCompositeLayerBase> Layer;`

### `Plugins/Compositing/Composite/Source/CompositeEditor/Private/UI/CompositePlatePassListOwner.h` (Private)


#### class `FCompositePlatePassListOwner`  
`class FCompositePlatePassListOwner : public ICompositePassListOwner`  
_L9-61_
- inherits: `ICompositePassListOwner`
- desc: ICompositePassListOwner implementation for UCompositeLayerPlate that manages its pass lists
- L21 _public function_ `FCompositePlatePassListOwner(const TWeakObjectPtr<UCompositeLayerPlate>& InPlate) : Plate(InPlate)`
- L28 _public prototype_ `virtual bool IsObjectValid() override;`
- L29 _public prototype_ `virtual TStrongObjectPtr<UObject> GetObject() override;`
- L30 _public prototype_ `virtual bool IsPassListPropertyName(const FName& InPropertyName) override;`
- L32 _public prototype_ `virtual bool IsValidPassIndex(int32 InGroupIndex, int32 InPassIndex) override;`
- L33 _public prototype_ `virtual UCompositePassBase* GetPass(int32 InGroupIndex, int32 InPassIndex) override;`
- L34 _public function_ `virtual int32 GetNumGroups() const override`
- L35 _public prototype_ `virtual TArray<TObjectPtr<UCompositePassBase>>& GetPassesForGroup(int32 InGroupIndex) override;`
- L37 _public prototype_ `virtual FString GetGroupFilterString(int32 InGroupIndex) override;`
- L38 _public prototype_ `virtual const FSlateBrush* GetGroupIcon(int32 InGroupIndex) override;`
- L39 _public prototype_ `virtual FText GetGroupDisplayName(int32 InGroupIndex) override;`
- L40 _public prototype_ `virtual FGroupFilterConfig GetGroupFilterConfig(int32 InGroupIndex) override;`
- L42 _public prototype_ `virtual int32 GetDefaultGroupForNewPass(const UClass* InPassClass) const override;`
- L43 _public prototype_ `virtual bool CanAddPass(const UClass* InPassClass, int32 InGroupIndex, int32 InPassIndex) const override;`
- L44 _public prototype_ `virtual int32 AddPass(const UClass* InPassClass, int32 InGroupIndex, int32 InPassIndex) override;`
- L45 _public prototype_ `virtual TArray<int32> CopyPasses(const TArray<UCompositePassBase*>& InPassesToCopy, int32 InGroupIndex, int32 InPassIndex) override;`
- L46 _public prototype_ `virtual void MovePass(int32 InSourceGroupIndex, int32 InSourcePassIndex, int32 InDestGroupIndex, int32 InDestPassIndex) override;`
- L47 _public prototype_ `virtual void RemovePasses(int32 InGroupIndex, const TArray<int32>& InPassIndices) override;`
- L53 _private prototype_ `TArray<TObjectPtr<UCompositePassBase>>& GetPassList(EPassType InPassType);` — Gets a reference to the pass list that corresponds to the specified pass type in the plate. The plate pointer must be valid to call properly
- L56 _private prototype_ `static FProperty* GetPassListProperty(EPassType InPassType);` — Gets the FProperty object for the list that corresponds to the specified pass type in the plate
- L60 _private member_ `TWeakObjectPtr<UCompositeLayerPlate> Plate;` — The plate UObject whose pass lists are being provided

#### enum `FCompositePlatePassListOwner::EPassType`  
`enum class EPassType : uint8`  
_L13-18_
- desc: Pass type which corresponds to which list in the plate layer a pass is stored in. The enum order determines display order — media passes are last so they appear at the bottom.
- L15 _public enumerator_ `Layer`
- L16 _public enumerator_ `Media`
- L17 _public enumerator_ `MAX`

### `Plugins/Compositing/Composite/Source/CompositeEditor/Private/UI/SCompositeActorPickerSceneOutliner.h` (Private)


#### class `SCompositeActorPickerSceneOutliner`  
`class SCompositeActorPickerSceneOutliner : public SCompoundWidget`  
_L13-39_
- inherits: `SCompoundWidget`
- desc: Scene Outliner used for picking multiple actors quickly for a composite actor list
- L16 _public function_ `SLATE_BEGIN_ARGS(SCompositeActorPickerSceneOutliner)`
- L17 _public prototype_ `SLATE_EVENT(FSimpleDelegate, OnActorListChanged) SLATE_ARGUMENT(TSharedPtr<FSceneOutlinerFilters>, SceneOutlinerFilters) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FCompositeActorPickerListRef& InActorListRef);`
- L25 _private prototype_ `bool OnGetActorSelected(AActor* InActor);` — Raised when the selection state of a specific actor needs to be determined
- L28 _private prototype_ `void OnActorSelected(AActor* InActor, bool bIsSelected);` — Raised when the selection state of a specific actor has changed
- L31 _private prototype_ `void OnAllActorsSelected(const TArray<AActor*>& InActors, bool bIsSelected);` — Raised when the header checkbox toggles to select or deselect all actors at once
- L35 _private member_ `FCompositeActorPickerListRef ActorListRef;` — Reference to the actor list being modified by this actor picker
- L38 _private member_ `FSimpleDelegate OnActorListChanged;` — Raised when the actor list has changed

### `Plugins/Compositing/Composite/Source/CompositeEditor/Private/UI/SCompositeActorPickerTable.h` (Private)


#### struct `FCompositeActorPickerListRef`  
`struct FCompositeActorPickerListRef`  
_L22-61_
- desc: Stores a pointer reference to a list of actors on a UObject to be managed by the actor picker
- L24 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnActorsAdded, TArray<TSoftObjectPtr<AActor>>&);`
- L27 _public prototype_ `FCompositeActorPickerListRef(const TWeakObjectPtr<UObject>& InActorListOwner, const FName& InActorListPropertyName, TArray<TSoftObjectPtr<AActor>>* InActorList, const FCompositeSpawnableBindings* InSpawnableBindings = nullptr);`
- L29 _public function_ `FCompositeActorPickerListRef()`
- L32 _public prototype_ `bool IsValid() const;` — Gets whether the pointer to the actor list is valid
- L35 _public prototype_ `void NotifyPreEditChange();` — Raises the owner's PreEditChange event for the actor list property
- L38 _public prototype_ `void NotifyPostEditChangeList(EPropertyChangeType::Type InChangeType, int32 LastModifiedIndex = INDEX_NONE);` — Raises the owner's PostEditchange event for the actor list property
- L41 _public prototype_ `FText GetToolTipText(bool bShortTooltip = false) const;` — Finds the localized tooltip or native tooltip as a fallback.
- L45 _public member_ `TWeakObjectPtr<UObject> ActorListOwner = nullptr;` — Reference to the UObject that owns the actor list being edited by this widget
- L48 _public member_ `FName ActorListPropertyName = NAME_None;` — The name of the actor list property within ActorListOwner
- L51 _public member_ `FProperty* ActorListProperty = nullptr;` — The property in ActorListOwner of the actor list
- L54 _public member_ `TArray<TSoftObjectPtr<AActor>>* ActorList = nullptr;` — Pointer to the actor list being edited by this widget
- L57 _public member_ `FOnActorsAdded OnActorsAdded;` — Raised when any actors are added to the actor list
- L60 _public member_ `const FCompositeSpawnableBindings* SpawnableBindings = nullptr;` — Optional read-only view of the layer's spawnable side-channel; when non-null the widget shows [Pending Spawnable] for stale entries.

#### class `SCompositeActorPickerTable`  
`class SCompositeActorPickerTable : public SCompoundWidget, public FEditorUndoClient`  
_L66-237_
- inherits: `SCompoundWidget,FEditorUndoClient`
- desc: A table that displays a list of selected actors as well as a picker to easily add or remove actors from the current level
- L82 _private typedef_ `using FActorListItemRef = TSharedPtr<FActorListItem>;`
- L85 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnGenerateHeaderColumns, TSharedRef<SHeaderRow> ) DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef<SWidget>, FOnGenerateColumnWidget, const TSoftObjectPtr<AActor>& , const FName& ) DECLARE_DELEGATE_OneParam(FOnExtendAddMenu, FMenuBuilder&);`
- L88 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnExtendContextMenu, FMenuBuilder&, TArray<TSoftObjectPtr<AActor>>& );`
- L89 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnApplyMaterialToActor, TSoftObjectPtr<AActor>& , UMaterialInterface* );`
- L93 _public prototype_ `static TSharedPtr<FSceneOutlinerFilters> MakeDefaultSceneOutlinerFilters(bool bExcludeCompositeMeshActors = true);` — Returns default scene outliner filters that check IsAllowedPrimitiveClass and optionally exclude ACompositeMeshActor.
- L102 _public prototype_ `static bool IsAllowedActor(AActor* InActor);` — True if InActor is eligible to be added to a Composite layer/pass actor list. Non-transient actors always qualify. Transient actors only qualify when they are sequencer spawnables — those resolve through the parallel FCompositeSpawnableBindings side-channel. Other transients (editor previews, runtime-only spawns, drag-preview duplicates) are rejected.
- L104 _public function_ `SLATE_BEGIN_ARGS(SCompositeActorPickerTable) : _ShowApplyMaterialSection(false)`
- L105 _public prototype_ `SLATE_ATTRIBUTE(TSharedPtr<FSceneOutlinerFilters>, SceneOutlinerFilters) SLATE_ARGUMENT(TArray<FName>, HiddenColumnsList) SLATE_EVENT(FSimpleDelegate, OnHiddenColumnsListChanged) SLATE_EVENT(FOnGenerateHeaderColumns, OnGenerateHeaderColumns) SLATE_EVENT(FOnGenerateColumnWidget, OnGenerateColumnWidget) SLATE_EVENT(FOnExtendAddMenu, OnExtendAddMenu) SLATE_EVENT(FOnExtendContextMenu, OnExtendContextMenu) SLATE_EVENT(FSimpleDelegate, OnLayoutSizeChanged) SLATE_ATTRIBUTE(bool, ShowApplyMaterialSection) SLATE_EVENT(FOnApplyMaterialToActor, OnApplyMaterialToActor) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FCompositeActorPickerListRef& InActorListRef);`
- L122 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SWidget interface
- L123 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L127 _public prototype_ `virtual void PostUndo(bool bSuccess) override;` — FEditorUndoClient Interface
- L128 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L132 _public prototype_ `TArray<FName> GetHiddenColumnsList() const;` — Gets the list of columns that are currently hidden in the actor table
- L136 _private prototype_ `void BindCommands();` — Binds any commands to callbacks for the actor list view
- L139 _private prototype_ `void FillActorList();` — Fills the list view's source list with the valid actors from the actor list and applies any active filters
- L142 _private prototype_ `void FilterActorList();` — Filters the actor list using any active filters
- L145 _private prototype_ `void OnFilterChanged();` — Raised when the toolbar filter has changed
- L148 _private prototype_ `TSharedPtr<SWidget> CreateListContextMenu();` — Create the right click context menu for the actor list view
- L151 _private prototype_ `void OnActorSelectionChanged(FActorListItemRef ActorListItem, ESelectInfo::Type InSelectType);` — Raised when an actor item is selected in the list view
- L154 _private prototype_ `void OnLevelSelectionChanged(UObject* NewSelection);` — Raised when the editor selection is changed
- L157 _private prototype_ `bool OnAllowListDrop(TSharedPtr<FDragDropOperation> InDragDropOperation);` — Raised when a drag drop operation is trying to be dropped on the actor list
- L160 _private prototype_ `FReply OnListDropped(const FGeometry& Geometry, const FDragDropEvent& DragDropEvent);` — Raised when a drag drop operation is being dropped on the actor list
- L163 _private prototype_ `FText GetFilterStatusText() const;` — Gets the filter status text
- L166 _private prototype_ `FSlateColor GetFilterStatusTextColor() const;` — Gets the color for the filter status text
- L169 _private prototype_ `void RemoveActors();` — Removes the selected actors from the list
- L172 _private prototype_ `void ApplyMaterialToActors(FString InMaterialPath);` — Apply the specified material to the the selected actors from the list
- L175 _private prototype_ `bool CanEditActors() const;` — Gets whether the contextual menu commands can be used
- L178 _private prototype_ `bool CanApplyCustomMaterial() const;` — Gets whether a custom material can be applied to the selected actors
- L181 _private prototype_ `FText GetCustomMaterialSubMenuLabel() const;` — Gets the label for the custom material sub-menu in the context menu
- L184 _private prototype_ `void CreateCustomMaterialSubMenu(FMenuBuilder& InMenuBuilder);` — Creates the custom material sub-menu in the context menu
- L187 _private prototype_ `void OnCustomMaterialSelected(const FAssetData& InAssetData);` — Raised when a new material is selected in the material browser in the custom material sub-menu
- L190 _private prototype_ `void OnObjectPropertyChanged(UObject* InObject, FPropertyChangedEvent& InPropertyChangedEvent);` — Raised when a property on the object has changed
- L194 _private member_ `TSharedPtr<SListView<FActorListItemRef>> ListView;` — List view that displays the list of selected actors
- L197 _private member_ `TSharedPtr<SHeaderRow> HeaderRow;` — Header row of the list view that displays the columns of the list
- L200 _private member_ `TSharedPtr<SCompositeActorPickerToolbar> Toolbar;` — The toolbar that contains the Add button and the filter text box
- L203 _private member_ `FCompositeActorPickerListRef ActorListRef;` — The reference to the actor list being managed by this actor picker
- L206 _private member_ `TArray<FActorListItemRef> ActorListItems;` — The list of actors to display in the list view
- L209 _private member_ `TArray<FActorListItemRef> FilteredActorListItems;` — Filtered list of actors to display in the list view
- L212 _private member_ `TSharedPtr<FUICommandList> CommandList;` — The command list for commands related to the actor list view
- L215 _private member_ `int32 CachedListViewNumChildren = 0;` — Stores the last observed number of widgets the list view is actually displaying, used to determine if the list view's layout has changed
- L218 _private member_ `FOnExtendAddMenu OnExtendAddMenu;` — Raised when building the Add menu, allows the menu contents to be extended with additional entries
- L221 _private member_ `FOnExtendContextMenu OnExtendContextMenu;` — Raised when building the context menu for entries in the table, allows the context menu contents to be extended with additional entries
- L224 _private member_ `FSimpleDelegate OnLayoutSizeChanged;` — Raised when the number of items in the list view changes
- L227 _private member_ `TAttribute<bool> bShowApplyMaterialSection;` — Flag to enable the material application section for selected actors.
- L230 _private member_ `FAssetData CustomMaterialAsset = FAssetData();` — Selected custom material to apply to selected actors
- L233 _private member_ `FOnApplyMaterialToActor OnApplyMaterialToActor;` — Raised when a material is being applied to an actor. Allows for custom logic on how the material is applied

#### struct `SCompositeActorPickerTable::FActorListItem`  
`struct FActorListItem`  
_L69-81_
- L72 _public member_ `TSoftObjectPtr<AActor> Actor;` — Soft reference to the actor this item represents
- L75 _public member_ `int32 Index;` — The index of the actor in the list
- L77 _public function_ `FActorListItem(const TSoftObjectPtr<AActor>& InActor, int32 InIndex) : Actor(InActor) , Index(InIndex)`

#### Free symbols / members of external scopes

- L24 _delegate_ `DECLARE_DELEGATE_OneParam(FOnActorsAdded, TArray<TSoftObjectPtr<AActor>>&);`
- L85 _delegate_ `DECLARE_DELEGATE_OneParam(FOnGenerateHeaderColumns, TSharedRef<SHeaderRow> ) DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef<SWidget>, FOnGenerateColumnWidget, const TSoftObjectPtr<AActor>& , const FName& ) DECLARE_DELEGATE_OneParam(FOnExtendAddMenu, FMenuBuilder&);`
- L86 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef<SWidget>, FOnGenerateColumnWidget, const TSoftObjectPtr<AActor>& , const FName& ) DECLARE_DELEGATE_OneParam(FOnExtendAddMenu, FMenuBuilder&);`
- L87 _delegate_ `DECLARE_DELEGATE_OneParam(FOnExtendAddMenu, FMenuBuilder&);`
- L88 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnExtendContextMenu, FMenuBuilder&, TArray<TSoftObjectPtr<AActor>>& );`
- L89 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnApplyMaterialToActor, TSoftObjectPtr<AActor>& , UMaterialInterface* );`

### `Plugins/Compositing/Composite/Source/CompositeEditor/Private/UI/SCompositeEditorPanel.h` (Private)


#### class `SCompositeEditorPanel`  
`class SCompositeEditorPanel : public SCompoundWidget`  
_L16-89_
- inherits: `SCompoundWidget`
- desc: Editor that displays the compositing actors in the level and displays the layer tree and layer properties for them
- L19 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnSelectionChanged) static void RegisterTabSpawner();`
- L25 _public prototype_ `static void UnregisterTabSpawner();` — Unregisters the tab spawner for the panel with the editor
- L28 _public prototype_ `static void UpdateActivePanelSelection(const TArray<UObject*>& InSelection);` — Updates the selected composite actors, layers, and passes in the active Composure panel, if one is open
- L31 _public prototype_ `static TArray<UObject*> GetActivePanelSelection();` — Gets the currently selected composite actors, layers, and passes in the active Composure panel, if one is open
- L34 _public function_ `static FOnSelectionChanged& GetOnSelectionChanged()` — Static delegate that is raised whenever the selection is changed in the active Composure panel
- L37 _public function_ `SLATE_BEGIN_ARGS(SCompositeEditorPanel)`
- L38 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L43 _public prototype_ `void SelectCompositeActors(const TArray<TWeakObjectPtr<ACompositeActor>>& InCompositeActors);` — Selects the specified composite actors in the layer tree
- L47 _private prototype_ `void SelectObjects(const TArray<UObject*>& InSelection);` — Selects any composite actors, layers, and passes in the specified list of objects
- L50 _private prototype_ `TArray<UObject*> GetSelectedObjects() const;` — Gets the actively selected composite actors, layers, and passes in this panel
- L53 _private prototype_ `void OnLayerSelectionChanged(const TArray<UObject*>& SelectedLayers);` — Raised when the selected layers in the tree view have changed
- L56 _private prototype_ `void OnLayerStateChanged();` — Raised when a layer's editable state changes (e.g. Solo toggled); forces details view to re-evaluate CanEditChange
- L59 _private prototype_ `float GetLayerTreeMinHeight() const;` — Gets the minimum height to display the full layer tree
- L66 _private function_ `template<typename TClass, typename TCustomization> TSharedRef<IDetailCustomization> CreateCustomization()` — Generic callback to create a customization of the specified type for the specified object type being customized. A weak reference to the customization will be stored in the InstancedCustomizations map keyed under the type being customized
- L82 _private member_ `TSharedPtr<SCompositePanelLayerTree> LayerTree;` — The tree view widget that displays the composite layers
- L85 _private member_ `TSharedPtr<IDetailsView> DetailsView;` — The details view that displays the properties of the selected layers and actors
- L88 _private member_ `TMap<UClass*, TArray<TWeakPtr<IDetailCustomization>>> InstancedCustomizations;` — A list of pointers to details customizations in use by the details panel, indexed by class being customized

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnSelectionChanged) static void RegisterTabSpawner();`

### `Plugins/Compositing/Composite/Source/CompositeEditor/Private/UI/SCompositePanelLayerTree.h` (Private)


#### class `SCompositePanelLayerTree`  
`class SCompositePanelLayerTree : public SCompoundWidget, public FEditorUndoClient`  
_L21-268_
- inherits: `SCompoundWidget,FEditorUndoClient`
- desc: A hierarchical view that displays all compositing actors and their rendering layers in the level
- L24 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnSelectionChanged, const TArray<UObject*>&);`
- L25 _public prototype_ `DECLARE_DELEGATE(FOnLayerStateChanged);`
- L53 _private typedef_ `using FCompositeActorTreeItemPtr = TSharedPtr<FCompositeActorTreeItem>;`
- L56 _public function_ `SLATE_BEGIN_ARGS(SCompositePanelLayerTree)`
- L57 _public prototype_ `SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged) SLATE_EVENT(FOnLayerStateChanged, OnLayerStateChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L66 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SWidget interface
- L67 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L71 _public prototype_ `virtual void PostUndo(bool bSuccess) override;` — FEditorUndoClient Interface
- L72 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L76 _public prototype_ `void SelectCompositeActors(const TArray<TWeakObjectPtr<ACompositeActor>>& InCompositeActors);` — Selects the specified composite actors in the layer tree
- L79 _public prototype_ `void SelectObjects(const TArray<UObject*>& InObjects);` — Selects all matching composite actors and layers in the tree from the specified list of objects
- L82 _public prototype_ `TArray<UObject*> GetSelectedObjects();` — Gets a list of the currently selected composite actors and layers in the tree
- L85 _public prototype_ `float GetMinimumHeight() const;` — Computes the minimum height necessary to display the layer tree with all layers visible
- L89 _private prototype_ `void BindCommands();` — Binds commands and callbacks to the command list
- L92 _private prototype_ `void FillCompositeActorTree(bool bPreserveSelection = false);` — Fills the tree view with all composite actors found on the current level
- L95 _private prototype_ `void FillCompositeActorTreeItem(FCompositeActorTreeItemPtr& InOutTreeItem);` — Fills the children of the composite actor tree item with tree items for each of the composite actor's layers
- L98 _private prototype_ `void RefreshCompositeActorLayers(ACompositeActor* InCompositeActor, bool bRefreshTree = true, bool bPreserveSelection = false);` — Refreshes the child tree elements for the specified composite actor
- L101 _private prototype_ `void SelectCompositeActorLayers(ACompositeActor* InCompositeActor, const TArray<int32>& InLayersToSelect);` — Selects the specified layers of a composite actor in the tree view
- L104 _private prototype_ `void RefreshAndExpandTreeView();` — Refreshes the tree view and expands all tree view items
- L107 _private prototype_ `bool CanAddLayer() const;` — Gets whether it is possible to add a layer based on active selection or lack thereof.
- L110 _private prototype_ `bool CanPilotCamera() const;` — Gets whether the currently selected composite actor has a camera that can be piloted
- L113 _private prototype_ `bool IsPilotingCamera() const;` — Gets whether camera actor of the currently selected composite actor is being piloted
- L116 _private prototype_ `void OnPilotCameraToggled(bool bPilotCamera);` — Sets the piloted actor to the currently selected composite actor camera, or clears it if it is already being piloted
- L119 _private prototype_ `AActor* GetActiveCompositeActorCamera() const;` — Gets the currently active composite actor's camera, or nullptr if no active composite actor or no valid camera was found
- L122 _private prototype_ `void PilotCamera(AActor* InCameraActorToPilot);` — Starts piloting the specified camera actor
- L125 _private prototype_ `void StopPilotingCamera();` — Stops piloting the currently piloted camera actor
- L128 _private prototype_ `void VerifyActiveCompositeActorPiloting();` — Checks whether the current active composite actor's camera is still the actor being piloted, and if not, stops piloting
- L131 _private prototype_ `ECompositeMeshVisualizationMode GetMeshVisualizationMode() const;` — Gets the currently selected composite mesh visualization mode from the editor settings.
- L134 _private prototype_ `void SetMeshVisualizationMode(ECompositeMeshVisualizationMode InMode);` — Updates the editor settings with the new visualization mode and refreshes the MPC scalar immediately.
- L137 _private prototype_ `static float ResolveMeshVisualizationValue(ECompositeMeshVisualizationMode InMode, bool bIsPilotingCompositeCamera);` — Computes the effective visualization scalar (0 or 1) for the given mode and piloting state.
- L140 _private prototype_ `void UpdateMeshVisualizationMPC();` — Writes the effective visualization scalar to MPC_Composite if it differs from the last-written value.
- L143 _private prototype_ `ECheckBoxState GetGlobalActiveCheckState() const;` — Gets the global active checkbox state.
- L146 _private prototype_ `void OnGlobalActiveCheckStateChanged(ECheckBoxState CheckBoxState);` — Sets the Active flag for all currently filtered items in the tree view
- L149 _private prototype_ `ECheckBoxState GetGlobalEnabledCheckState() const;` — Gets the check state for the global enabled checkbox
- L152 _private prototype_ `void OnGlobalEnabledCheckStateChanged(ECheckBoxState CheckBoxState);` — Sets the Enabled flag for all currently filtered items in the tree view
- L155 _private prototype_ `void OnLayerSelectionChanged(FCompositeActorTreeItemPtr InTreeItem, ESelectInfo::Type SelectInfo);` — Callback that is raised when the selected items in the tree view change
- L158 _private prototype_ `void InvokeLayerSelectionChanged();` — Invokes the OnSelectionChanged delegate with the appropriate selected layers
- L161 _private prototype_ `void OnFilterChanged();` — Callback that is raised when the tree view filter is changed, applies the new filter to the composite actor tree items
- L164 _private prototype_ `FText GetFilterStatusText() const;` — Gets the status text to display at the bottom of the tree view that shows the number of actors filtered and selected
- L167 _private prototype_ `FSlateColor GetFilterStatusTextColor() const;` — Gets the color of the filter status text
- L170 _private prototype_ `TSharedPtr<SWidget> CreateTreeContextMenu();` — Creates the right click context menu for the tree view
- L173 _private prototype_ `void AddCompositeActor();` — Adds a new composite actor to the level
- L176 _private prototype_ `void OnLayerAdded(const UClass* InLayerClass);` — Raised when a new layer is being added to the selected composite actor
- L179 _private prototype_ `void OnCompositeActorActivated(const TStrongObjectPtr<ACompositeActor>& CompositeActor);` — Raised when a composite actor is made the composite actor
- L182 _private prototype_ `FReply OnLayerSoloToggled(const FCompositeActorTreeItemPtr& InLayerTreeItem);` — Raised when the Solo button has been toggled on the specified layer tree item
- L185 _private prototype_ `void OnLayerMoved(const FCompositeActorTreeItemPtr& InTreeItem, int32 InDestIndex);` — Raised when a layer has been moved via a drag drop operation to the specified destination index
- L188 _private prototype_ `void OnActorAddedToLevel(AActor* Actor);` — Callbacks for any editor events that may necessitate updating the composite actors being displayed in the tree view
- L189 _private prototype_ `void OnLevelActorListChanged();`
- L190 _private prototype_ `void OnActorRemovedFromLevel(AActor* Actor);`
- L191 _private prototype_ `void OnMapChange(uint32 MapFlags);`
- L192 _private prototype_ `void OnNewCurrentLevel();`
- L193 _private prototype_ `void OnLevelAdded(ULevel* InLevel, UWorld* InWorld);`
- L194 _private prototype_ `void OnLevelRemoved(ULevel* InLevel, UWorld* InWorld);`
- L195 _private prototype_ `void OnObjectReplaced(const TMap<UObject*, UObject*>& Tuples);`
- L196 _private prototype_ `void OnObjectPropertyChanged(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent);`
- L199 _private prototype_ `void CopySelectedItems();` — Generic command callbacks to handle copy, cut, paste, delete, and rename
- L200 _private prototype_ `bool CanCopySelectedItems();`
- L201 _private prototype_ `void CutSelectedItems();`
- L202 _private prototype_ `bool CanCutSelectedItems();`
- L203 _private prototype_ `void PasteSelectedItems();`
- L204 _private prototype_ `bool CanPasteSelectedItems();`
- L205 _private prototype_ `void DuplicateSelectedItems();`
- L206 _private prototype_ `bool CanDuplicateSelectedItems();`
- L207 _private prototype_ `void DeleteSelectedItems();`
- L208 _private prototype_ `bool CanDeleteSelectedItems();`
- L209 _private prototype_ `void RenameSelectedItem();`
- L210 _private prototype_ `bool CanRenameSelectedItem();`
- L211 _private prototype_ `void EnableSelectedItems();`
- L212 _private prototype_ `bool CanEnableSelectedItems();`
- L216 _private member_ `TSharedPtr<STreeView<FCompositeActorTreeItemPtr>> TreeView;` — Tree view widget that displays the level's composite actors and their layers
- L219 _private member_ `TArray<FCompositeActorTreeItemPtr> CompositeActorTreeItems;` — A list of all tree items that can be displayed in the tree view
- L222 _private member_ `TArray<FCompositeActorTreeItemPtr> FilteredCompositeActorTreeItems;` — The actual list of tree items to display when a filter has been applied
- L225 _private member_ `TSharedPtr<SCompositePanelLayerTreeToolbar> Toolbar;` — Toolbar being displayed above the tree view
- L228 _private member_ `TSharedPtr<SWidget> FooterContainer;` — The root widget that contains all the footer content
- L231 _private member_ `TSharedPtr<FUICommandList> CommandList;` — The command list for commands related to the tree view
- L234 _private member_ `FOnSelectionChanged OnSelectionChanged;` — Raised when the selected tree items have changed
- L237 _private member_ `FOnLayerStateChanged OnLayerStateChanged;` — Raised when a layer's editable state has changed (e.g. Solo toggled) and the details panel should re-evaluate CanEditChange
- L240 _private member_ `TWeakObjectPtr<ACompositeActor> LastActiveActor;` — Last active actor.
- L246 _private member_ `TOptional<FViewportCameraTransform> CachedPerspectiveCameraTransform;` — Used to store last perspective camera transform before piloting (Actor Lock) Once piloting ends, this transform is re-applied to the camera.
- L249 _private member_ `TOptional<float> CachedViewFOV;` — Cached field of view to re-apply once piloting ends.
- L252 _private member_ `bool bSilenceSelectionChanges = false;` — When true, selection changes in the tree view will not invoke the SelectionChanged delegate
- L255 _private member_ `bool bCachedIsPilotingCamera = false;` — Stores whether the active composite actor's camera is currently being piloted
- L258 _private member_ `TWeakObjectPtr<UMaterialParameterCollection> CachedVisualizationMPC;` — Lazy-loaded reference to MPC_Composite used to publish the visualization scalar.
- L261 _private member_ `TWeakObjectPtr<UWorld> CachedVisualizationWorld;` — World that LastWrittenMeshVisualization refers to; cache is invalidated when the editor world changes.
- L264 _private member_ `TOptional<float> LastWrittenMeshVisualization;` — Last value written to the MPC scalar to avoid redundant per-tick updates.

#### struct `SCompositePanelLayerTree::FCompositeActorTreeItem`  
`struct FCompositeActorTreeItem`  
_L29-51_
- desc: Item that stores a composite actor and layer index to display in the layer tree view
- L32 _public member_ `TWeakObjectPtr<ACompositeActor> CompositeActor = nullptr;` — Composite actor whose layer is being displayed
- L35 _public member_ `int32 LayerIndex = INDEX_NONE;` — Index of the layer in the composite actor's CompositeLayers list. If INDEX_NONE, then this tree item is the composite actor itself
- L38 _public member_ `TArray<TSharedPtr<FCompositeActorTreeItem>> Children;` — Child tree items of this tree item
- L41 _public member_ `bool bFilteredOut = false;` — Indicates that this item is being filtered out by the active filter
- L44 _public prototype_ `bool HasValidCompositeActor() const;` — Gets whether this tree item references a valid composite actor
- L47 _public prototype_ `bool HasValidCompositeLayer() const;` — Gets whether this tree item references a valid composite layer
- L50 _public prototype_ `UCompositeLayerBase* GetCompositeLayer() const;` — Gets the composite layer this tree item references

#### Free symbols / members of external scopes

- L24 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSelectionChanged, const TArray<UObject*>&);`
- L25 _delegate_ `DECLARE_DELEGATE(FOnLayerStateChanged);`

### `Plugins/Compositing/Composite/Source/CompositeEditor/Private/UI/SCompositePassTree.h` (Private)


#### class `ICompositePassListOwner`  
`class ICompositePassListOwner`  
_L16-70_
- desc: Wrapper around a UObject that owns one or more lists of composite passes to display in the pass tree
- L20 _public prototype_ `virtual bool IsObjectValid() = 0;` — Gets whether the backing UObject that owns the pass list(s) is valid
- L23 _public prototype_ `virtual TStrongObjectPtr<UObject> GetObject() = 0;` — Gets a strong pointer to the backing UObject that owns the pass list(s)
- L26 _public prototype_ `virtual bool IsPassListPropertyName(const FName& InPropertyName) = 0;` — Gets whether the specified property name matches any of the properties related to the pass list(s) being provided
- L29 _public prototype_ `virtual bool IsValidPassIndex(int32 InGroupIndex, int32 InPassIndex) = 0;` — Gets whether the specified group and pass indices reference a valid pass in the owner's pass list(s)
- L32 _public prototype_ `virtual UCompositePassBase* GetPass(int32 InGroupIndex, int32 InPassIndex) = 0;` — Gets the pass for the specified group and pass indices, or nullptr if no pass is found
- L35 _public prototype_ `virtual int32 GetNumGroups() const = 0;` — Gets the number of different groups all the passes managed by the owner should be stored and displayed in
- L38 _public prototype_ `virtual TArray<TObjectPtr<UCompositePassBase>>& GetPassesForGroup(int32 InGroupIndex) = 0;` — Gets all the passes for the specified group index; use INDEX_NONE if there are no distinct groups
- L41 _public prototype_ `virtual FString GetGroupFilterString(int32 InGroupIndex) = 0;` — Gets the string used for filtering in the tree view for a specified pass group
- L44 _public prototype_ `virtual const FSlateBrush* GetGroupIcon(int32 InGroupIndex) = 0;` — Gets the icon used for displaying the group in the tree view for a specified pass group
- L47 _public prototype_ `virtual FText GetGroupDisplayName(int32 InGroupIndex) = 0;` — Gets the display name used for displaying the group in the tree view for a specified pass group
- L51 _public prototype_ `virtual FGroupFilterConfig GetGroupFilterConfig(int32 InGroupIndex) = 0;` — Gets the filter config used to display filtering pills in the tree view for a specified pass group
- L54 _public prototype_ `virtual int32 GetDefaultGroupForNewPass(const UClass* InPassClass) const = 0;` — Gets the default group a new pass should be added in when no group is selected, or INDEX_NONE if the pass should not be added to a group
- L57 _public prototype_ `virtual bool CanAddPass(const UClass* InPassClass, int32 InGroupIndex, int32 InPassIndex) const = 0;` — Gets whether a pass of the specified type can be added to the specified group at the specified location
- L60 _public prototype_ `virtual int32 AddPass(const UClass* InPassClass, int32 InGroupIndex, int32 InPassIndex) = 0;` — Adds a pass of the specified type to the specified group at the specified location
- L63 _public prototype_ `virtual TArray<int32> CopyPasses(const TArray<UCompositePassBase*>& InPassesToCopy, int32 InGroupIndex, int32 InPassIndex) = 0;` — Copies all the specified passes into the specified group at the specified location
- L66 _public prototype_ `virtual void MovePass(int32 InSourceGroupIndex, int32 InSourcePassIndex, int32 InDestGroupIndex, int32 InDestPassIndex) = 0;` — Moves a pass from the specified group and location to the specified destination group and location
- L69 _public prototype_ `virtual void RemovePasses(int32 InGroupIndex, const TArray<int32>& InPassIndices) = 0;` — Removes all passes at the specified group

#### struct `ICompositePassListOwner::FGroupFilterConfig`  
`struct FGroupFilterConfig`  
_L49-49_
- L49 _public member_ `struct FGroupFilterConfig { FString FilterName; FText DisplayName; FText ToolTip; };`
- L49 _public member_ `struct FGroupFilterConfig { FString FilterName; FText DisplayName; FText ToolTip; };`
- L49 _public member_ `struct FGroupFilterConfig { FString FilterName; FText DisplayName; FText ToolTip; };`

#### class `SCompositePassTree`  
`class SCompositePassTree : public SCompoundWidget, public FSelfRegisteringEditorUndoClient`  
_L75-243_
- inherits: `SCompoundWidget,FSelfRegisteringEditorUndoClient`
- desc: Widget that displays a filterable tree view for the passes within a composite plate layer
- L78 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnSelectionChanged, const TArray<UObject*>&);`
- L117 _private typedef_ `using FPassTreeItemPtr = TSharedPtr<FPassTreeItem>;`
- L120 _public function_ `SLATE_BEGIN_ARGS(SCompositePassTree)`
- L121 _public prototype_ `SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged) SLATE_EVENT(FSimpleDelegate, OnLayoutChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<ICompositePassListOwner>& InPassListOwner);`
- L130 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;` — SWidget interface
- L134 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L135 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L139 _public prototype_ `void SelectPasses(const TArray<UCompositePassBase*>& InPasses);` — Selects the specified passes in the pass tree
- L142 _public prototype_ `TArray<UCompositePassBase*> GetSelectedPasses() const;` — Gets a list of currently selected passes in the pass tree
- L146 _private prototype_ `void BindCommands();` — Binds commands in the command list to callbacks
- L149 _private prototype_ `void FillPassTreeItems(bool bPreserveSelection = false);` — Creates any tree items needed for all passes in the plate
- L152 _private prototype_ `void FilterPassTreeItems();` — Applies the current filter to the pass tree items to build a filtered list of tree items
- L155 _private prototype_ `void RefreshGroup(int32 InGroupIndex, bool bRefreshTreeView = true);` — Refreshes the tree items for the passes in the specified group
- L158 _private prototype_ `void RefreshAndExpandTreeView();` — Refreshes the tree view's displayed list and automatically expands all tree items
- L161 _private prototype_ `TSharedPtr<SWidget> CreateTreeContextMenu();` — Creates the tree view right click context menu
- L164 _private prototype_ `ECheckBoxState GetGlobalEnabledState() const;` — Gets the global enabled state for all passes on the plate
- L167 _private prototype_ `void OnGlobalEnabledStateChanged(ECheckBoxState CheckBoxState);` — Sets the enabled state for all passes on the plate
- L170 _private prototype_ `bool HasAnyPasses() const;` — Gets whether any passes exist across all groups
- L173 _private prototype_ `void OnPassMoved(const TSharedPtr<FPassTreeItem>& InTreeItem, int32 InDestGroupIndex, int InDestIndex);` — Raised when a pass has been moved via a drag drop operation
- L176 _private prototype_ `void OnPassSelectionChanged(TSharedPtr<FPassTreeItem> InTreeItem, ESelectInfo::Type SelectInfo);` — Raised when the selected items in the tree view have bene changed
- L179 _private prototype_ `void OnFilterChanged();` — Raised when the active filter has been changed
- L182 _private prototype_ `void OnPassAdded(const UClass* InPassClass);` — Raised when a new pass is being added
- L185 _private prototype_ `bool OnFilterNewPassType(const UClass* InPassType) const;` — Raised when the toolbar is adding pass types to the Add Pass menu, allowing types to be filtered out
- L188 _private prototype_ `FText GetFilterStatusText() const;` — Gets status text based on selection and active filter
- L191 _private prototype_ `FSlateColor GetFilterStatusColor() const;` — Gets status text color based on selection and active filter
- L194 _private prototype_ `void OnObjectPropertyChanged(UObject* InObject, FPropertyChangedEvent& InPropertyChangedEvent);` — Raised when a property on the object has changed
- L197 _private prototype_ `void CopySelectedItems();` — Generic command callbacks to handle copy, cut, paste, delete, and enable
- L198 _private prototype_ `bool CanCopySelectedItems();`
- L199 _private prototype_ `void CutSelectedItems();`
- L200 _private prototype_ `bool CanCutSelectedItems();`
- L201 _private prototype_ `void PasteSelectedItems();`
- L202 _private prototype_ `bool CanPasteSelectedItems();`
- L203 _private prototype_ `void DuplicateSelectedItems();`
- L204 _private prototype_ `bool CanDuplicateSelectedItems();`
- L205 _private prototype_ `void DeleteSelectedItems();`
- L206 _private prototype_ `bool CanDeleteSelectedItems();`
- L207 _private prototype_ `void RenameSelectedItem();`
- L208 _private prototype_ `bool CanRenameSelectedItem();`
- L209 _private prototype_ `void EnableSelectedItems();`
- L210 _private prototype_ `bool CanEnableSelectedItems();`
- L214 _private member_ `TSharedPtr<ICompositePassListOwner> PassListOwner;` — The owner whose passes are being displayed
- L217 _private member_ `TArray<FPassTreeItemPtr> PassTreeItems;` — List of all pass tree items for the plate
- L220 _private member_ `TArray<FPassTreeItemPtr> FilteredPassTreeItems;` — List of all passes that match the current filter
- L223 _private member_ `TSharedPtr<STreeView<FPassTreeItemPtr>> TreeView;` — Tree view that displays a hierarchical list of passes on the plate
- L226 _private member_ `TSharedPtr<SCompositePassTreeToolbar> Toolbar;` — Toolbar widget displayed above the tree view
- L229 _private member_ `TSharedPtr<FUICommandList> CommandList;` — The command list for commands related to the tree view
- L232 _private member_ `bool bSilenceSelectionChanges;` — When true, selection changes in the tree view will not invoke the SelectionChanged delegate
- L235 _private member_ `FOnSelectionChanged OnSelectionChanged;` — Delegate that gets raised when the tree view selection changes
- L238 _private member_ `FSimpleDelegate OnLayoutChanged;` — Delegate raised when there is a potential layout change to the tree view, to give containers the opportunity to correctly resize their layouts

#### struct `SCompositePassTree::FPassTreeItem`  
`struct FPassTreeItem`  
_L82-116_
- desc: Stores data needed for a single row item in the tree view
- L85 _public member_ `TSharedPtr<ICompositePassListOwner> Owner = nullptr;` — Owner object whose passes are being displayed
- L88 _public member_ `int32 PassIndex = INDEX_NONE;` — If this tree item is for a specific pass, this is the pass's index in the plate's corresponding list of passes
- L91 _public member_ `int32 GroupIndex = INDEX_NONE;` — The group this tree item belongs to
- L94 _public member_ `bool bFilteredOut = false;` — Indicates if this tree item is being filtered out by the current filter
- L97 _public member_ `TArray<TSharedPtr<FPassTreeItem>> Children;` — Child tree items of this tree item
- L100 _public prototype_ `bool HasValidOwner() const;` — Gets whether the pass list owner pointer is valid
- L103 _public prototype_ `bool HasValidPassIndex() const;` — Gets whether the pass index is valid within the plate's list of passes
- L106 _public prototype_ `UCompositePassBase* GetPass() const;` — Gets the pass object referenced by this tree item
- L109 _public prototype_ `FString GetGroupFilterString() const;` — If this item is a group item, gets the filter string to use for the item
- L112 _public prototype_ `const FSlateBrush* GetGroupIcon() const;` — If this item is a group item, gets the icon to use for the item
- L115 _public prototype_ `FText GetGroupDisplayName() const;` — If this item is a group item, gets the display name to use for the item

#### Free symbols / members of external scopes

- L78 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSelectionChanged, const TArray<UObject*>&);`

### `Plugins/Compositing/Composite/Source/CompositeEditor/Private/UI/SCompositePassTreePanel.h` (Private)


#### class `SCompositePassTreePanel`  
`class SCompositePassTreePanel : public SCompoundWidget`  
_L16-54_
- inherits: `SCompoundWidget`
- desc: A panel that displays a tree view and a details panel for passes within the plate composite layer
- L19 _public function_ `SLATE_BEGIN_ARGS(SCompositePassTreePanel)`
- L20 _public prototype_ `SLATE_EVENT(FSimpleDelegate, OnLayoutSizeChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<ICompositePassListOwner>& InPassListOwner);`
- L26 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SWidget interface
- L30 _public prototype_ `void SelectPasses(TArray<UCompositePassBase*>& InPasses);` — Selects the specified passes in the pass tree
- L33 _public prototype_ `TArray<UCompositePassBase*> GetSelectedPasses() const;` — Gets a list of currently selected passes in the pass tree
- L37 _private prototype_ `void OnTreeViewSelectionChanged(const TArray<UObject*>& Objects);` — Raised when the selected items in the tree view have changed
- L41 _private member_ `TSharedPtr<SCompositePassTree> TreeView;` — Tree view that displays a hierarchical list of passes in the plate
- L44 _private member_ `TSharedPtr<IDetailsView> DetailsView;` — The details view to display selected pass properties
- L47 _private member_ `int32 CachedDetailsViewRowCount = 0;` — To identify when the details view has changed size by showing a new object or expanding a property group, keep track of its reported row count every tick
- L50 _private member_ `bool bLayoutSizeChanged = false;` — Flag used to indicate if OnLayoutSizeChanged needs to be called on the next tick
- L53 _private member_ `FSimpleDelegate OnLayoutSizeChanged;` — Delegate that is raised when a potential size change has been detected in the panel (e.g. the details panel is displaying a new object)

### `Plugins/Compositing/Composite/Source/CompositeEditor/Private/Util/CompositeSequencerAutoKeySuppression.h` (Private)


#### struct `FScopedSequencerAutoKeySuppression`  
`struct FScopedSequencerAutoKeySuppression`  
_L17-47_
- desc: RAII guard that suppresses Sequencer auto-key for the duration of its scope by flipping every open Sequencer's AllowEditsMode to AllowLevelEditsOnly. Restores the previous mode on destruction. Used by the customization helpers (sender-side, around SetValue) and the CompositeEditor module (peer-side, across a Concert apply window).
- L19 _public function_ `FScopedSequencerAutoKeySuppression()`
- L31 _public function_ `~FScopedSequencerAutoKeySuppression()`
- L42 _public prototype_ `FScopedSequencerAutoKeySuppression(const FScopedSequencerAutoKeySuppression&) = delete;`
- L43 _public prototype_ `FScopedSequencerAutoKeySuppression& operator=(const FScopedSequencerAutoKeySuppression&) = delete;`
- L46 _private member_ `TArray<TPair<TWeakPtr<ISequencer>, EAllowEditsMode>> CachedModes;`

### `Plugins/Compositing/Composite/Source/CompositeEditor/Public/CompositeEditorModule.h` (Public)


#### class `FCompositeEditorModule`  
`class FCompositeEditorModule : public IModuleInterface`  
_L17-66_
- inherits: `IModuleInterface`
- L21 _public prototype_ `FCompositeEditorModule();`
- L22 _public prototype_ `~FCompositeEditorModule();`
- L25 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L26 _public prototype_ `virtual void ShutdownModule() override;`
- L30 _private prototype_ `void OnPostEngineInit();` — Called after the engine has initialized.
- L33 _private prototype_ `void OnLevelActorAdded(AActor* InActor);` — Called when an Actor has been added to a level.
- L36 _private prototype_ `void TriggerHoldoutCompositeWarning(const class UHoldoutCompositeComponent* InComponent);` — Callback to trigger warnings when an holdout composite component is created with a composite actor.
- L39 _private prototype_ `void RegisterTabSpawners();` — Register tab spawners.
- L42 _private prototype_ `void UnregisterTabSpawners();` — Unregister tab spawners.
- L44 _private prototype_ `void RegisterCustomizations();`
- L45 _private prototype_ `void UnregisterCustomizations();`
- L48 _private prototype_ `void RegisterConcertApplyListener();` — Subscribe to Concert apply notifications to suppress Sequencer auto-key on the receiving editor.
- L51 _private prototype_ `void UnregisterConcertApplyListener();` — Unsubscribe and release any held suppression.
- L54 _private prototype_ `void OnConcertApplyTransaction(ETransactionNotification InNotification, const bool bIsSnapshot);` — Holds the Sequencer auto-key suppression for the duration of a Concert apply (Begin -> construct, End -> reset).
- L59 _private member_ `FDelegateHandle OnTabManagerChangedDelegateHandle;` — Tab manager change delegate.
- L62 _private member_ `TSharedPtr<UE::Sequencer::FCompositeActorObjectSchema> CompositeActorObjectSchema;` — Sequencer object schema for exposing layers and passes as possessable sub-objects.
- L65 _private member_ `TUniquePtr<FScopedSequencerAutoKeySuppression> ConcertApplyAutoKeySuppression;` — Sequencer auto-key suppression held for the active Concert apply window.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Sequencer` (scope `UE`)
- L15 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogCompositeEditor, Log, All);` — Log category for this module.
- L15 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCompositeEditor, Log, All);` — Log category for this module.
