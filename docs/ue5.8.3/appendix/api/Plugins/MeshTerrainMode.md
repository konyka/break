# Plugins / MeshTerrainMode

- module root: `Plugins/Experimental/MeshTerrainMode/Source/MeshTerrainMode`
- headers: 36; symbols: 1145
- symbol kinds: class=48, delegate=8, enum=9, enumerator=23, function=94, macro=3, member=477, namespace=70, prototype=395, struct=18
- DynamicallyLoadedModuleNames: PlacementMode
- PrivateDependencyModuleNames: ContentBrowserData, CoreUObject, DeveloperSettings, DynamicMesh, EditorConfig, EditorFramework, EditorInteractiveToolsFramework, EditorWidgets, Engine, GeometryCore, GeometryFramework, GeometryProcessingInterfaces, InputCore, InteractiveToolsFramework, LevelEditor, MeshLODToolset, MeshModelingTools, MeshModelingToolsEditorOnly, MeshModelingToolsEditorOnlyExp, MeshModelingToolsExp, MeshPartition, MeshPartitionEditor, MeshPartitionModelingToolset, ModelingComponents, ModelingComponentsEditorOnly, ModelingEditorUI, ModelingToolsEditorMode, Projects, PropertyEditor, RHI, Slate, SlateCore, StatusBar, StylusInput, ToolMenus, ToolPresetAsset, ToolPresetEditor, ToolWidgets, TypedElementRuntime, UnrealEd, WidgetRegistration
- PrivateIncludePathModuleNames: PlacementMode
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/MeshTerrainMode/Source/MeshTerrainMode/Private/DetailsCustomizations/BakeMeshAttributeToolCustomizations.h` (Private)


#### class `UE::MeshTerrain::FBakeMeshAttributeMapsToolDetails`  
`class FBakeMeshAttributeMapsToolDetails : public IDetailCustomization`  
_L11-16_
- inherits: `IDetailCustomization`
- desc: Customization for UBakeMeshAttributeMapsToolProperties
- L14 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L15 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`

#### class `UE::MeshTerrain::FBakeMultiMeshAttributeMapsToolDetails`  
`class FBakeMultiMeshAttributeMapsToolDetails : public IDetailCustomization`  
_L19-24_
- inherits: `IDetailCustomization`
- desc: Customization for UBakeMultiMeshAttributeMapsToolProperties
- L22 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L23 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`

#### class `UE::MeshTerrain::FBakeMeshAttributeVertexToolDetails`  
`class FBakeMeshAttributeVertexToolDetails : public IDetailCustomization`  
_L27-32_
- inherits: `IDetailCustomization`
- desc: Customization for UBakeMeshAttributeVertexToolProperties
- L30 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L31 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace MeshTerrain` (scope `UE`)

### `Plugins/Experimental/MeshTerrainMode/Source/MeshTerrainMode/Private/DetailsCustomizations/BakeTransformToolCustomizations.h` (Private)


#### class `UE::MeshTerrain::FBakeTransformToolDetails`  
`class FBakeTransformToolDetails : public IDetailCustomization`  
_L14-25_
- inherits: `IDetailCustomization`
- desc: Customization for UBakeTransformToolProperties
- L17 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L18 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L21 _protected prototype_ `void EvaluateBakeScaleMethodRestrictions(TSharedRef<IPropertyHandle> AllowNoScale, TSharedRef<IPropertyHandle> BakeScaleHandle);`
- L24 _protected member_ `TSharedPtr<FPropertyRestriction> BakeScaleMethodEnumRestriction;` — Property restriction applied to the EBakeScaleMethod enum dropdown box

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MeshTerrain` (scope `UE`)

### `Plugins/Experimental/MeshTerrainMode/Source/MeshTerrainMode/Private/DetailsCustomizations/BrushBasePropertiesCustomizations.h` (Private)


#### class `UE::MeshTerrain::FBrushBasePropertiesDetails`  
`class FBrushBasePropertiesDetails : public IDetailCustomization`  
_L10-15_
- inherits: `IDetailCustomization`
- L13 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L14 _public prototype_ `void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace MeshTerrain` (scope `UE`)

### `Plugins/Experimental/MeshTerrainMode/Source/MeshTerrainMode/Private/DetailsCustomizations/MeshTopologySelectionMechanicCustomization.h` (Private)


#### class `UE::MeshTerrain::FMeshTopologySelectionMechanicPropertiesDetails`  
`class FMeshTopologySelectionMechanicPropertiesDetails : public IDetailCustomization`  
_L14-19_
- inherits: `IDetailCustomization`
- desc: Customization for UMeshTopologySelectionMechanicProperties
- L17 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L18 _public prototype_ `void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MeshTerrain` (scope `UE`)

### `Plugins/Experimental/MeshTerrainMode/Source/MeshTerrainMode/Private/DetailsCustomizations/MeshVertexSculptToolCustomizations.h` (Private)


#### class `UE::MeshTerrain::FSculptBrushPropertiesDetails`  
`class FSculptBrushPropertiesDetails : public IDetailCustomization`  
_L29-34_
- inherits: `IDetailCustomization`
- desc: customization for USculptBrushProperties, creates two-column layout for secondary brush properties like lazy/etc
- L32 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L33 _public prototype_ `void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`

#### class `UE::MeshTerrain::FVertexBrushSculptPropertiesDetails`  
`class FVertexBrushSculptPropertiesDetails : public IDetailCustomization`  
_L39-61_
- inherits: `IDetailCustomization`
- desc: customization for vertexsculpt properties, creates combopanel for brush type, small-style combopanel for falloff type, and stacks controls to the right
- L42 _public prototype_ `virtual ~FVertexBrushSculptPropertiesDetails();`
- L44 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L45 _public prototype_ `void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L48 _protected member_ `TWeakObjectPtr<UMeshVertexSculptTool> TargetTool;`
- L50 _protected prototype_ `TSharedPtr<SWidget> MakeRegionFilterWidget();`
- L51 _protected prototype_ `TSharedPtr<SWidget> MakeFreezeTargetWidget();`
- L53 _protected member_ `TSharedPtr<SButton> FreezeTargetButton;`
- L54 _protected prototype_ `FReply OnToggledFreezeTarget();`
- L55 _protected prototype_ `void OnSetFreezeTarget(ECheckBoxState State);`
- L56 _protected prototype_ `bool IsFreezeTargetEnabled();`
- L58 _protected member_ `TSharedPtr<SComboPanel> FalloffTypeCombo;`
- L59 _protected member_ `TArray<TWeakObjectPtr<UObject>> ObjectsBeingCustomized;`
- L60 _protected member_ `FDelegateHandle FalloffTypeUpdateHandle;`

#### class `UE::MeshTerrain::FVertexBrushAlphaPropertiesDetails`  
`class FVertexBrushAlphaPropertiesDetails : public IDetailCustomization`  
_L67-82_
- inherits: `IDetailCustomization`
- desc: customization for UVertexBrushAlphaProperties, creates custom asset picker tileview-combopanel for brush alphas and stacks controls to the right
- L70 _public prototype_ `virtual ~FVertexBrushAlphaPropertiesDetails();`
- L72 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L73 _public prototype_ `void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L75 _public member_ `TSharedPtr<FRecentAlphasProvider> RecentAlphasProvider;`
- L78 _protected member_ `TWeakObjectPtr<UMeshVertexSculptTool> TargetTool;`
- L79 _protected member_ `TArray<TWeakObjectPtr<UObject>> ObjectsBeingCustomized;`
- L80 _protected member_ `TSharedPtr<SToolInputAssetComboPanel> AlphaAssetPicker;`
- L81 _protected member_ `FDelegateHandle AlphaTextureUpdateHandle;`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace MeshTerrain` (scope `UE`)

### `Plugins/Experimental/MeshTerrainMode/Source/MeshTerrainMode/Private/DetailsCustomizations/ModelingToolPropertyCustomizations.h` (Private)


#### class `UE::MeshTerrain::FModelingToolsAxisFilterCustomization`  
`class FModelingToolsAxisFilterCustomization : public IPropertyTypeCustomization`  
_L13-20_
- inherits: `IPropertyTypeCustomization`
- desc: Details customization for FModelingModeAxisFilter struct - X/Y/Z booleans are laid out in a single horizontal row
- L16 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L18 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L19 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`

#### class `UE::MeshTerrain::FModelingToolsColorChannelFilterCustomization`  
`class FModelingToolsColorChannelFilterCustomization : public IPropertyTypeCustomization`  
_L24-31_
- inherits: `IPropertyTypeCustomization`
- desc: Details customization for FModelingToolsColorChannelFilter struct - R/G/B/A booleans are laid out in a single horizontal row
- L27 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L29 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L30 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MeshTerrain` (scope `UE`)

### `Plugins/Experimental/MeshTerrainMode/Source/MeshTerrainMode/Private/DetailsCustomizations/ModelingToolsBrushSizeCustomization.h` (Private)


#### class `UE::MeshTerrain::FSculptToolsUIConstants`  
`class FSculptToolsUIConstants`  
_L13-19_
- desc: defining this here so we can use in FModelingToolsBrushSizeCustomization, should move to some shared constants header/file
- L17 _public member_ `static constexpr int SculptShortLabelWidth = 40;` — sculpt panel packs in the widgets w/ short fixed-width labels

#### class `UE::MeshTerrain::FModelingToolsBrushSizeCustomization`  
`class FModelingToolsBrushSizeCustomization : public IPropertyTypeCustomization`  
_L23-30_
- inherits: `IPropertyTypeCustomization`
- desc: Details customization for FBrushToolRadius struct. This maybe should be removed in favor of just doing custom UI in FSculptBrushPropertiesDetails...
- L26 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L28 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L29 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MeshTerrain` (scope `UE`)

### `Plugins/Experimental/MeshTerrainMode/Source/MeshTerrainMode/Private/DetailsCustomizations/SculptSubmodeCustomizations.h` (Private)


#### class `UE::MeshTerrain::FSculptBrushPropertiesCustomizations`  
`class FSculptBrushPropertiesCustomizations : public IMeshTerrainPropertyCustomization`  
_L12-20_
- inherits: `IMeshTerrainPropertyCustomization`
- L15 _public prototype_ `static TSharedRef<IMeshTerrainPropertyCustomization> MakeInstance();`
- L16 _public prototype_ `virtual TMap<FName, FMeshTerrainCustomizationData> GetCustomizationData() override;`
- L17 _public prototype_ `virtual TMap<FName, FMeshTerrainEditConditionData> GetEditConditionData() override;`
- L19 _private prototype_ `static TSharedRef<SWidget> MakeBrushSizeWidget(FProperty* BrushSizeProperty, UObject* PropListOwner);`

#### class `UE::MeshTerrain::FMeshEditingViewPropertiesCustomizations`  
`class FMeshEditingViewPropertiesCustomizations : public IMeshTerrainPropertyCustomization`  
_L22-27_
- inherits: `IMeshTerrainPropertyCustomization`
- L25 _public prototype_ `static TSharedRef<IMeshTerrainPropertyCustomization> MakeInstance();`
- L26 _public prototype_ `virtual TMap<FName, FMeshTerrainEditConditionData> GetEditConditionData() override;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MeshTerrain` (scope `UE`)

### `Plugins/Experimental/MeshTerrainMode/Source/MeshTerrainMode/Private/MeshTerrainDetailCustomizations.h` (Private)


#### enum `UE::MeshTerrain::EMeshTerrainCustomizationType`  
`enum class EMeshTerrainCustomizationType`  
_L15-20_
- L17 _public enumerator_ `None`
- L18 _public enumerator_ `WidgetOnly`
- L19 _public enumerator_ `WholeRow`

#### struct `UE::MeshTerrain::FMeshTerrainCustomizationData`  
`struct FMeshTerrainCustomizationData`  
_L22-32_
- L24 _public member_ `FGetMeshTerrainDetailCustomization DetailCustomization;`
- L25 _public member_ `EMeshTerrainCustomizationType Type;`
- L27 _public function_ `FMeshTerrainCustomizationData() : DetailCustomization(nullptr), Type(EMeshTerrainCustomizationType::None)`
- L28 _public function_ `FMeshTerrainCustomizationData(FGetMeshTerrainDetailCustomization InDetailsCustomization) : DetailCustomization(InDetailsCustomization), Type(EMeshTerrainCustomizationType::WidgetOnly)`
- L30 _public function_ `FMeshTerrainCustomizationData(const FGetMeshTerrainDetailCustomization& InDetailsCustomization, EMeshTerrainCustomizationType InType) : DetailCustomization(InDetailsCustomization), Type(InType)`

#### struct `UE::MeshTerrain::FMeshTerrainEditConditionData`  
`struct FMeshTerrainEditConditionData`  
_L34-38_
- L36 _public member_ `bool bEditConditionHides;`
- L37 _public member_ `FGetMeshTerrainEditCondition EditCondition;`

#### class `UE::MeshTerrain::IMeshTerrainPropertyCustomization`  
`class IMeshTerrainPropertyCustomization : public TSharedFromThis<IMeshTerrainPropertyCustomization>`  
_L40-47_
- inherits: `TSharedFromThis<IMeshTerrainPropertyCustomization>`
- L43 _public function_ `virtual ~IMeshTerrainPropertyCustomization()`
- L45 _public function_ `virtual TMap<FName, FMeshTerrainCustomizationData> GetCustomizationData()`
- L46 _public function_ `virtual TMap<FName, FMeshTerrainEditConditionData> GetEditConditionData()`

#### class `UE::MeshTerrain::FMeshTerrainDetailCustomizations`  
`class FMeshTerrainDetailCustomizations`  
_L50-76_
- L53 _public prototype_ `static FMeshTerrainDetailCustomizations* Get();`
- L55 _public prototype_ `static void RegisterCustomization(const FName& SectionName, TSharedRef<IMeshTerrainPropertyCustomization> InDelegate);`
- L58 _public prototype_ `static const TMap<FName, FMeshTerrainCustomizationData>* GetCustomizedWidgets(const FName& SectionName);` — Retrieve the map of all PropertyNames to their CustomizationData which fall in the given section
- L61 _public prototype_ `static const FMeshTerrainCustomizationData* GetCustomizationData(const UObject* PropOwner, const FProperty* Property);` — Retrieve the customization data matching the provided PropertyOwner and Property. Return null if none exists
- L64 _public prototype_ `static const TMap<FName, FMeshTerrainEditConditionData>* GetEditConditionData(const FName& SectionName);` — Retrieve the map of all PropertyNames to their EditCondition data which fall in the given section
- L67 _public prototype_ `static const FMeshTerrainEditConditionData* GetEditCondition(const UObject* PropOwner, const FProperty* Property);` — Retrieve the edit condition data matching the provided PropertyOwner and Property. Return null if none exists
- L70 _private function_ `FMeshTerrainDetailCustomizations()`
- L71 _private function_ `~FMeshTerrainDetailCustomizations()`
- L73 _private member_ `static FMeshTerrainDetailCustomizations* Instance;`
- L74 _private member_ `static TMap<FName, TMap<FName, FMeshTerrainCustomizationData>> Customizations;`
- L75 _private member_ `static TMap<FName, TMap<FName, FMeshTerrainEditConditionData>> EditConditions;`

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef<SWidget>, FGetMeshTerrainDetailCustomization, FProperty*, UObject*);`
- L9 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef<SWidget>, FGetMeshTerrainDetailCustomization, FProperty*, UObject*);`
- L10 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FGetMeshTerrainEditCondition, FProperty*, UObject*);`
- L10 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FGetMeshTerrainEditCondition, FProperty*, UObject*);`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MeshTerrain` (scope `UE`)

### `Plugins/Experimental/MeshTerrainMode/Source/MeshTerrainMode/Private/MeshTerrainDetailsSections.h` (Private)


#### class `FMeshTerrainDetailsSections`  
`class FMeshTerrainDetailsSections`  
_L7-26_
- L10 _public prototype_ `static FMeshTerrainDetailsSections* Get();`
- L11 _public prototype_ `static void Initialize();`
- L13 _public prototype_ `static TMap<FName, FName> GetSectionMappings(const FName& SectionName);`
- L15 _private prototype_ `FMeshTerrainDetailsSections();`
- L16 _private function_ `~FMeshTerrainDetailsSections()`
- L18 _private prototype_ `static void RegisterSculptSubmodeTabs();`
- L19 _private prototype_ `static void RegisterShapeSubmodeTabs();`
- L20 _private prototype_ `static void RegisterEditSubmodeTabs();`
- L21 _private prototype_ `static void RegisterCreateSubmodeTabs();`
- L22 _private prototype_ `static void RegisterPaintSubmodeTabs();`
- L24 _private member_ `static FMeshTerrainDetailsSections* Instance;`
- L25 _private member_ `static TMap<FName, TMap<FName, FName>> AllSectionMappings;`

### `Plugins/Experimental/MeshTerrainMode/Source/MeshTerrainMode/Private/MeshTerrainMode.h` (Private)


#### struct `UE::MeshTerrain::FClickContext`  
`struct FClickContext`  
_L31-35_
- L33 _public member_ `FHitResult* HitResult = nullptr;`
- L34 _public member_ `FMenuBuilder* Builder = nullptr;`

#### class `UE::MeshTerrain::UMeshTerrainMode`  
`class UMeshTerrainMode : public UBaseLegacyWidgetEdMode, public ILegacyEdModeSelectInterface`  
_L38-237_
- reflection: `UCLASS(Transient)`
- inherits: `UBaseLegacyWidgetEdMode,ILegacyEdModeSelectInterface`
- L42 _public member_ `const static FEditorModeID EM_MeshTerrainEditorModeId;`
- L44 _public prototype_ `UMeshTerrainMode();`
- L45 _public prototype_ `UMeshTerrainMode(FVTableHelper& Helper);`
- L46 _public prototype_ `~UMeshTerrainMode();`
- L52 _public prototype_ `virtual bool HandleClick(FEditorViewportClient* ViewportClient, HHitProxy* HitProxy, const FViewportClick& InClick) override;`
- L54 _public prototype_ `virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) override;`
- L56 _public prototype_ `virtual void ActorSelectionChangeNotify() override;`
- L58 _public prototype_ `virtual bool ShouldDrawWidget() const override;`
- L59 _public prototype_ `virtual bool ProcessEditDelete() override;`
- L60 _public prototype_ `virtual bool ProcessEditCut() override;`
- L61 _public prototype_ `virtual EEditAction::Type GetActionEditDuplicate() override;`
- L63 _public prototype_ `virtual bool CanAutoSave() const override;`
- L65 _public prototype_ `virtual bool GetPivotForOrbit(FVector& OutPivot) const override;`
- L67 _public function_ `virtual bool RequiresLegacyViewportInteractions() const override`
- L74 _public prototype_ `virtual void Enter() override;` — called when we "start" this editor mode (ie switch to this tab)
- L77 _public prototype_ `virtual void Exit() override;` — called when we "end" this editor mode (ie switch to another tab)
- L79 _public prototype_ `virtual bool ShouldToolStartBeAllowed(const FString& ToolIdentifier) const override;`
- L87 _public prototype_ `virtual bool BoxSelect(FBox& InBox, bool InSelect = true) override;` — ILegacyEdModeSelectInterface
- L88 _public prototype_ `virtual bool FrustumSelect(const FConvexVolume& InFrustum, FEditorViewportClient* InViewportClient, bool InSelect) override;`
- L92 _public prototype_ `virtual bool HasCustomViewportFocus() const override;` — Manage viewport focus
- L93 _public prototype_ `virtual FBox ComputeCustomViewportFocus() const override;`
- L101 _public function_ `virtual UGeometrySelectionManager* GetSelectionManager() const`
- L105 _public function_ `virtual UMeshTerrainModeSelectionInteraction* GetSelectionInteraction() const`
- L111 _public member_ `bool bEnableVolumeElementSelection = true;` — `UPROPERTY()`
- L114 _public member_ `bool bEnableStaticMeshElementSelection = true;` — `UPROPERTY()`
- L116 _public prototype_ `bool GetMeshElementSelectionSystemEnabled() const;`
- L117 _public prototype_ `void NotifySelectionSystemEnabledStateModified();`
- L120 _protected prototype_ `virtual void BindCommands() override;`
- L121 _protected prototype_ `virtual void CreateToolkit() override;`
- L122 _protected prototype_ `virtual void OnToolStarted(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;`
- L123 _protected prototype_ `virtual void OnToolEnded(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;`
- L125 _protected prototype_ `virtual void OnToolPostBuild(UInteractiveToolManager* InToolManager, EToolSide InSide, UInteractiveTool* InBuiltTool, UInteractiveToolBuilder* InToolBuilder, const FToolBuilderState& ToolState);`
- L128 _protected prototype_ `void RegisterUVEditor();` — Method to optionally register the UV Editor launcher in the Modeling Mode UV category if the plugin is available.
- L130 _protected member_ `FDelegateHandle MeshCreatedEventHandle;`
- L131 _protected member_ `FDelegateHandle TextureCreatedEventHandle;`
- L132 _protected member_ `FDelegateHandle MaterialCreatedEventHandle;`
- L133 _protected member_ `FDelegateHandle SelectionModifiedEventHandle;`
- L135 _protected member_ `FDelegateHandle EditorClosedEventHandle;`
- L136 _protected prototype_ `void OnEditorClosed();`
- L138 _protected member_ `TSharedPtr<FLevelObjectsObserver> LevelObjectsObserver;`
- L141 _protected member_ `TObjectPtr<UModelingSceneSnappingManager> SceneSnappingManager;` — `UPROPERTY()`
- L143 _protected prototype_ `void InitializeGeometrySelection();`
- L144 _protected prototype_ `void ShutdownGeometrySelection();`
- L146 _protected member_ `TArray<FString> RegisteredSelectionTools;`
- L149 _protected member_ `TObjectPtr<UGeometrySelectionManager> SelectionManager;` — `UPROPERTY()`
- L152 _protected member_ `TObjectPtr<UMeshTerrainModeSelectionInteraction> SelectionInteraction;` — `UPROPERTY()`
- L154 _protected member_ `FDelegateHandle SelectionManager_SelectionModifiedHandle;`
- L156 _protected prototype_ `bool GetGeometrySelectionChangesAllowed() const;`
- L157 _protected prototype_ `bool TestForEditorGizmoHit(const FInputDeviceRay&) const;`
- L160 _protected member_ `bool bSelectionSystemEnabled = false;`
- L162 _protected prototype_ `void UpdateSelectionManagerOnEditorSelectionChange(bool bEnteringMode = false);`
- L164 _protected prototype_ `void OnToolsContextRender(IToolsContextRenderAPI* RenderAPI);`
- L165 _protected prototype_ `void OnToolsContextDrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI);`
- L167 _protected prototype_ `void ModelingModeShortcutRequested(EMeshTerrainModeActionCommands Command);`
- L168 _protected prototype_ `void FocusCameraAtCursorHotkey();`
- L170 _protected prototype_ `void AcceptActiveToolActionOrTool();`
- L171 _protected prototype_ `void CancelActiveToolActionOrTool();`
- L172 _protected prototype_ `void OnEscapeKey();`
- L174 _protected prototype_ `void ConfigureRealTimeViewportsOverride(bool bEnable);`
- L176 _protected member_ `FDelegateHandle BlueprintPreCompileHandle;`
- L177 _protected prototype_ `void OnBlueprintPreCompile(UBlueprint* Blueprint);`
- L185 _protected member_ `TArray<TObjectPtr<UInteractiveCommand>> ModelingModeCommands;` — `UPROPERTY()`
- L189 _protected member_ `static FDateTime LastModeStartTimestamp;` — analytics tracking
- L190 _protected member_ `static FDateTime LastToolStartTimestamp;`
- L193 _protected member_ `static FDelegateHandle GlobalModelingWorldTeardownEventHandle;` — tracking of unlocked stuff
- L196 _protected prototype_ `void ExecuteRelaunchLastTool();` — Re-select the last target(s) and restart the last tool.
- L201 _protected member_ `TArray<TWeakObjectPtr<USceneComponent>> LastTargetComponents;` — Last-tool state for "Relaunch Last Tool" hotkey. 1 UEditableModifierBase (modifier), N UMeshProviderModifiers (base sections), or 1 UMeshPartitionEditorComponent (whole mesh partition).
- L202 _protected member_ `FString LastToolIdentifier;`
- L203 _protected member_ `FName LastSubmodeName;`
- L206 _private member_ `bool bIsToolActive = false;`
- L209 _private member_ `TSet<TWeakObjectPtr<AActor>> ActiveToolTargetActors;` — Actors that the active tool was launched against, captured at OnToolPostBuild and cleared at OnToolEnded.
- L211 _private prototype_ `void OnEditorModeIDChanged(const FEditorModeID& InID, bool bIsActive);`
- L212 _private prototype_ `void OnActivate();`
- L213 _private prototype_ `void OnDeactivate();`
- L216 _private prototype_ `static void PopulateModelingModeViewportToolbar(const FName InMenuName, const TSharedPtr<const FUICommandList>& InCommandList);` — add modeling-mode-specific portion of new viewport toolbar
- L218 _private prototype_ `static void RemoveModelingModeViewportToolbarExtensions();` — remove modeling-mode-specific portion of new viewport toolbar
- L221 _private prototype_ `bool CreateVSculptToolWidgets(FProperty* Prop, UObject* PropListOwner, TArray<UE::MeshTerrain::FPropertyWidget>& WidgetsToAdd, UInteractiveTool* Tool, const UE::MeshTerrain::EQuickPropertyDisplay DisplayType = UE::MeshTerrain::EQuickPropertyDisplay::WidgetAndLabel);` — appends all customized Widgets connected to the MeshVertexSculptTool to the provided Array
- L225 _private prototype_ `bool CreatePaintWeightsToolWidgets(FProperty* Prop, UObject* PropListOwner, TArray<UE::MeshTerrain::FPropertyWidget>& WidgetsToAdd, UInteractiveTool* Tool, const UE::MeshTerrain::EQuickPropertyDisplay DisplayType = UE::MeshTerrain::EQuickPropertyDisplay::WidgetAndLabel);` — appends all customized Widgets connected to the AttributePaintTool to the provided Array
- L228 _private prototype_ `bool ShowPressureSensitivityControls() const;`
- L230 _private prototype_ `void RegisterCustomTool( TSharedPtr<FUICommandInfo> UICommand, FString ToolIdentifier, UInteractiveToolBuilder* Builder, const TFunction<bool(UInteractiveToolManager*, EToolSide)>& ExecuteAction, const TFunction<bool(UInteractiveToolManager*, EToolSide)>& CanExecuteAction, const TFunction<bool(UInteractiveToolManager*, EToolSide)>& IsActionChecked);`

#### Free symbols / members of external scopes

- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace MeshTerrain` (scope `UE`)

### `Plugins/Experimental/MeshTerrainMode/Source/MeshTerrainMode/Private/MeshTerrainModeActions.h` (Private)


#### enum `UE::MeshTerrain::EMeshTerrainModeActionCommands`  
`enum class EMeshTerrainModeActionCommands`  
_L11-15_
- L13 _public enumerator_ `FocusViewToCursor`
- L14 _public enumerator_ `ToggleSelectionLockState`

#### class `UE::MeshTerrain::FMeshTerrainModeActionCommands`  
`class FMeshTerrainModeActionCommands : public TCommands<FMeshTerrainModeActionCommands>`  
_L18-30_
- inherits: `TCommands<FMeshTerrainModeActionCommands>`
- L21 _public prototype_ `FMeshTerrainModeActionCommands();`
- L23 _public prototype_ `virtual void RegisterCommands() override;`
- L25 _public member_ `TSharedPtr<FUICommandInfo> FocusViewCommand;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> ToggleSelectionLockStateCommand;`
- L28 _public prototype_ `static void RegisterCommandBindings(TSharedPtr<FUICommandList> UICommandList, TFunction<void(EMeshTerrainModeActionCommands)> OnCommandExecuted);`
- L29 _public prototype_ `static void UnRegisterCommandBindings(TSharedPtr<FUICommandList> UICommandList);`

#### class `UE::MeshTerrain::FMeshTerrainModeToolActionCommands`  
`class FMeshTerrainModeToolActionCommands : public TInteractiveToolCommands<FMeshTerrainModeToolActionCommands>`  
_L37-65_
- inherits: `TInteractiveToolCommands<FMeshTerrainModeToolActionCommands>`
- desc: TInteractiveToolCommands implementation for this module that provides standard Editor hotkey support
- L40 _public prototype_ `FMeshTerrainModeToolActionCommands();`
- L42 _public prototype_ `virtual void GetToolDefaultObjectList(TArray<UInteractiveTool*>& ToolCDOs) override;`
- L51 _public prototype_ `static void RegisterAllToolActions();` — Register all Tool command sets. Call this in module startup
- L56 _public prototype_ `static void UnregisterAllToolActions();` — Unregister all Tool command sets. Call this from module shutdown.
- L63 _public prototype_ `static void UpdateToolCommandBinding(UInteractiveTool* Tool, TSharedPtr<FUICommandList> UICommandList, bool bUnbind = false);` — Add or remove commands relevant to Tool to the given UICommandList. Call this when the active tool changes (eg on ToolManager.OnToolStarted / OnToolEnded) @param bUnbind if true, commands are removed, otherwise added

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace MeshTerrain` (scope `UE`)
- L72 _macro_ `#define DECLARE_TOOL_ACTION_COMMANDS(CommandsClassName) \`
- L81 _prototype_ `DECLARE_TOOL_ACTION_COMMANDS(FSculptToolActionCommands);` (scope `UE::MeshTerrain`)
- L82 _prototype_ `DECLARE_TOOL_ACTION_COMMANDS(FVertexSculptToolActionCommands);` (scope `UE::MeshTerrain`)
- L83 _prototype_ `DECLARE_TOOL_ACTION_COMMANDS(FMeshGroupPaintToolActionCommands);` (scope `UE::MeshTerrain`)
- L84 _prototype_ `DECLARE_TOOL_ACTION_COMMANDS(FMeshVertexPaintToolActionCommands);` (scope `UE::MeshTerrain`)
- L85 _prototype_ `DECLARE_TOOL_ACTION_COMMANDS(FMeshAttributePaintToolActionCommands);` (scope `UE::MeshTerrain`)
- L86 _prototype_ `DECLARE_TOOL_ACTION_COMMANDS(FTransformToolActionCommands);` (scope `UE::MeshTerrain`)
- L87 _prototype_ `DECLARE_TOOL_ACTION_COMMANDS(FDrawPolygonToolActionCommands);` (scope `UE::MeshTerrain`)
- L88 _prototype_ `DECLARE_TOOL_ACTION_COMMANDS(FMeshSelectionToolActionCommands);` (scope `UE::MeshTerrain`)
- L89 _prototype_ `DECLARE_TOOL_ACTION_COMMANDS(FEditMeshMaterialsToolActionCommands);` (scope `UE::MeshTerrain`)
- L90 _prototype_ `DECLARE_TOOL_ACTION_COMMANDS(FMeshPlaneCutToolActionCommands);` (scope `UE::MeshTerrain`)
- L91 _prototype_ `DECLARE_TOOL_ACTION_COMMANDS(FCubeGridToolActionCommands);` (scope `UE::MeshTerrain`)
- L92 _prototype_ `DECLARE_TOOL_ACTION_COMMANDS(FEditMeshPolygonsToolActionCommands);` (scope `UE::MeshTerrain`)
- L93 _prototype_ `DECLARE_TOOL_ACTION_COMMANDS(FDrawAndRevolveToolActionCommands);` (scope `UE::MeshTerrain`)
- L94 _prototype_ `DECLARE_TOOL_ACTION_COMMANDS(FMegaMeshHeightSculptToolCommands);` (scope `UE::MeshTerrain`)

### `Plugins/Experimental/MeshTerrainMode/Source/MeshTerrainMode/Private/MeshTerrainModeAssetUtils.h` (Private)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MeshTerrain` (scope `UE`)
- L28 _prototype_ `FString GetNewAssetPathName(const FString& BaseName, const UWorld* TargetWorld, FString SuggestedFolder);` (scope `UE::MeshTerrain`) — Determines path and name for a new Asset based on current mode settings, etc @param BaseName desired initial string for the name @param TargetWorld World the new Asset will be used in, which can determine its generated path based on various settings @param SuggestedFolder a suggested path for the asset, ignored if empty @return Path+Name for the new Asset (package)
- L35 _prototype_ `FString GetWorldRelativeAssetRootPath(const UWorld* World);` (scope `UE::MeshTerrain`) — Determines the world relative asset root path. @param World World the new Asset will be used in; if this is a nullptr then it will be set using the current world context. @return Asset root path relative to the world.
- L41 _prototype_ `FString GetGlobalAssetRootPath();` (scope `UE::MeshTerrain`) — Determines the global asset root path. @return Global asset root path.
- L48 _prototype_ `void OnNewAssetCreated(UObject* Asset);` (scope `UE::MeshTerrain`) — Utility function that may auto-save a newly created asset depending on current mode settings, and posts notifications for the Editor @param Asset the new asset object (eg UStaticMesh, UTexture2D, etc)
- L55 _prototype_ `bool AutoSaveAsset(UObject* Asset);` (scope `UE::MeshTerrain`) — Utility function that will attempt to auto-save an asset, and post Editor change notifications @param Asset the  asset object (eg UStaticMesh, UTexture2D, etc)

### `Plugins/Experimental/MeshTerrainMode/Source/MeshTerrainMode/Private/MeshTerrainModeEditablePaletteConfig.h` (Private)


#### class `UMeshTerrainModeEditableToolPaletteConfig`  
`class UMeshTerrainModeEditableToolPaletteConfig : public UEditorConfigBase, public IEditableToolPaletteConfigManager`  
_L16-37_
- reflection: `UCLASS(EditorConfig="MeshTerrainModeEditableToolPalette")`
- inherits: `UEditorConfigBase,IEditableToolPaletteConfigManager`
- desc: Implementation of IEditableToolPaletteConfigManager specific to ModelingMode, currently needed because we cannot have one at the FModeToolkit level due to EditorConfig depending on UnrealEd which is where the mode toolkit lives
- L23 _public prototype_ `virtual FEditableToolPaletteSettings* GetMutablePaletteConfig(const FName& InstanceName) override;` — IEditableToolPaletteConfigManager Interface
- L24 _public prototype_ `virtual const FEditableToolPaletteSettings* GetConstPaletteConfig(const FName& InstanceName) override;`
- L25 _public prototype_ `virtual void SavePaletteConfig(const FName& InstanceName) override;`
- L27 _public prototype_ `static void Initialize();`
- L28 _public function_ `static UMeshTerrainModeEditableToolPaletteConfig* Get()`
- L29 _public function_ `static IEditableToolPaletteConfigManager* GetAsConfigManager()`
- L32 _public member_ `TMap<FName, FEditableToolPaletteSettings> EditableToolPalettes;` — `UPROPERTY(meta=(EditorConfig))`
- L36 _private member_ `static TObjectPtr<UMeshTerrainModeEditableToolPaletteConfig> Instance;`

### `Plugins/Experimental/MeshTerrainMode/Source/MeshTerrainMode/Private/MeshTerrainModeHostCustomizationAPI.h` (Private)


#### class `UE::MeshTerrain::UMeshTerrainModeHostCustomizationAPI`  
`class UMeshTerrainModeHostCustomizationAPI : public UObject, public IToolHostCustomizationAPI`  
_L23-45_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UObject,IToolHostCustomizationAPI`
- desc: An implementation of IToolHostCustomizationAPI meant to be used with modeling tools editor mode. Mostly it just forwards the relevant requests to the mode toolkit, which changes its accept/cancel/complete overlay buttons temporarily (until the next click of those buttons).
- L28 _public function_ `virtual bool SupportsAcceptCancelButtonOverride() override`
- L29 _public prototype_ `virtual bool RequestAcceptCancelButtonOverride(FAcceptCancelButtonOverrideParams& Params) override;`
- L31 _public function_ `virtual bool SupportsCompleteButtonOverride() override`
- L32 _public prototype_ `virtual bool RequestCompleteButtonOverride(FCompleteButtonOverrideParams& Params) override;`
- L34 _public prototype_ `virtual void ClearButtonOverrides() override;`
- L37 _public prototype_ `static UMeshTerrainModeHostCustomizationAPI* Register(UInteractiveToolsContext* ToolsContext, TSharedRef<FMeshTerrainModeToolkit> Toolkit);` — Helper to create, initialize, and register a UModelingToolsHostCustomizationAPI object with the context store
- L41 _public prototype_ `static bool Deregister(UInteractiveToolsContext* ToolsContext);` — Helper to deregister the UModelingToolsHostCustomizationAPI from the context store
- L44 _protected member_ `TWeakPtr<FMeshTerrainModeToolkit> Toolkit;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MeshTerrain` (scope `UE`)

### `Plugins/Experimental/MeshTerrainMode/Source/MeshTerrainMode/Private/MeshTerrainModeManagerActions.h` (Private)


#### class `FMeshTerrainModeManagerCommands`  
`class FMeshTerrainModeManagerCommands : public TCommands<FMeshTerrainModeManagerCommands>`  
_L11-316_
- inherits: `TCommands<FMeshTerrainModeManagerCommands>`
- desc: TInteractiveToolCommands implementation for Modeling Mode Tools
- L14 _public prototype_ `FMeshTerrainModeManagerCommands();`
- L25 _protected member_ `TArray<FStartToolCommand> RegisteredTools;` — Tool start-commands listed below are stored in this list
- L32 _protected member_ `TArray<FDynamicExtensionCommand> ExtensionPaletteCommands;`
- L38 _public prototype_ `TSharedPtr<FUICommandInfo> FindToolByName(FString Name, bool& bFound) const;` — Find Tool start-command below by registered name (tool icon name in Mode palette)
- L44 _public prototype_ `FText GetCommandLabel(TSharedPtr<const FUICommandInfo> Command, bool bShortName) const;` — Helper that gets the regular command label (result of GetLabel) or a shortened version if one was registered and bShortName is true.
- L50 _public member_ `TSharedPtr<FUICommandInfo> BeginAddBoxPrimitiveTool;`
- L51 _public member_ `TSharedPtr<FUICommandInfo> BeginAddCylinderPrimitiveTool;`
- L52 _public member_ `TSharedPtr<FUICommandInfo> BeginAddCapsulePrimitiveTool;`
- L53 _public member_ `TSharedPtr<FUICommandInfo> BeginAddConePrimitiveTool;`
- L54 _public member_ `TSharedPtr<FUICommandInfo> BeginAddArrowPrimitiveTool;`
- L55 _public member_ `TSharedPtr<FUICommandInfo> BeginAddRectanglePrimitiveTool;`
- L56 _public member_ `TSharedPtr<FUICommandInfo> BeginAddDiscPrimitiveTool;`
- L57 _public member_ `TSharedPtr<FUICommandInfo> BeginAddTorusPrimitiveTool;`
- L58 _public member_ `TSharedPtr<FUICommandInfo> BeginAddSpherePrimitiveTool;`
- L59 _public member_ `TSharedPtr<FUICommandInfo> BeginAddStairsPrimitiveTool;`
- L61 _public member_ `TSharedPtr<FUICommandInfo> BeginAddPatchTool;`
- L62 _public member_ `TSharedPtr<FUICommandInfo> BeginRevolveBoundaryTool;`
- L63 _public member_ `TSharedPtr<FUICommandInfo> BeginDrawPolygonTool;`
- L64 _public member_ `TSharedPtr<FUICommandInfo> BeginDrawPolyPathTool;`
- L65 _public member_ `TSharedPtr<FUICommandInfo> BeginDrawAndRevolveTool;`
- L66 _public member_ `TSharedPtr<FUICommandInfo> BeginRevolveSplineTool;`
- L67 _public member_ `TSharedPtr<FUICommandInfo> BeginShapeSprayTool;`
- L68 _public member_ `TSharedPtr<FUICommandInfo> BeginDrawSplineTool;`
- L69 _public member_ `TSharedPtr<FUICommandInfo> BeginTriangulateSplinesTool;`
- L71 _public member_ `TSharedPtr<FUICommandInfo> BeginSculptMeshTool;`
- L72 _public member_ `TSharedPtr<FUICommandInfo> BeginCubeGridTool;`
- L73 _public member_ `TSharedPtr<FUICommandInfo> BeginPolyEditTool;`
- L74 _public member_ `TSharedPtr<FUICommandInfo> BeginSubdividePolyTool;`
- L75 _public member_ `TSharedPtr<FUICommandInfo> BeginTriEditTool;`
- L76 _public member_ `TSharedPtr<FUICommandInfo> BeginPolyDeformTool;`
- L77 _public member_ `TSharedPtr<FUICommandInfo> BeginSmoothMeshTool;`
- L78 _public member_ `TSharedPtr<FUICommandInfo> BeginOffsetMeshTool;`
- L79 _public member_ `TSharedPtr<FUICommandInfo> BeginDisplaceMeshTool;`
- L80 _public member_ `TSharedPtr<FUICommandInfo> BeginMeshSpaceDeformerTool;`
- L81 _public member_ `TSharedPtr<FUICommandInfo> BeginTransformMeshesTool;`
- L82 _public member_ `TSharedPtr<FUICommandInfo> BeginEditPivotTool;`
- L83 _public member_ `TSharedPtr<FUICommandInfo> BeginAddPivotActorTool;`
- L84 _public member_ `TSharedPtr<FUICommandInfo> BeginBakeTransformTool;`
- L85 _public member_ `TSharedPtr<FUICommandInfo> BeginCombineMeshesTool;`
- L86 _public member_ `TSharedPtr<FUICommandInfo> BeginDuplicateMeshesTool;`
- L87 _public member_ `TSharedPtr<FUICommandInfo> BeginAlignObjectsTool;`
- L88 _public member_ `TSharedPtr<FUICommandInfo> BeginTransferMeshTool;`
- L89 _public member_ `TSharedPtr<FUICommandInfo> BeginConvertMeshesTool;`
- L90 _public member_ `TSharedPtr<FUICommandInfo> BeginSplitMeshesTool;`
- L91 _public member_ `TSharedPtr<FUICommandInfo> BeginPatternTool;`
- L92 _public member_ `TSharedPtr<FUICommandInfo> BeginHarvestInstancesTool;`
- L94 _public member_ `TSharedPtr<FUICommandInfo> BeginSculptMeshMoveBrushTool;`
- L95 _public member_ `TSharedPtr<FUICommandInfo> BeginSculptMeshPullKelvinBrushTool;`
- L96 _public member_ `TSharedPtr<FUICommandInfo> BeginSculptMeshPullSharpKelvinBrushTool;`
- L97 _public member_ `TSharedPtr<FUICommandInfo> BeginSculptMeshSmoothBrushTool;`
- L98 _public member_ `TSharedPtr<FUICommandInfo> BeginSculptMeshSmoothFillBrushTool;`
- L99 _public member_ `TSharedPtr<FUICommandInfo> BeginSculptMeshOffsetBrushTool;`
- L100 _public member_ `TSharedPtr<FUICommandInfo> BeginSculptMeshSculptViewBrushTool;`
- L101 _public member_ `TSharedPtr<FUICommandInfo> BeginSculptMeshSculptMaxBrushTool;`
- L102 _public member_ `TSharedPtr<FUICommandInfo> BeginSculptMeshInflateBrushTool;`
- L103 _public member_ `TSharedPtr<FUICommandInfo> BeginSculptMeshScaleKelvinBrushTool;`
- L104 _public member_ `TSharedPtr<FUICommandInfo> BeginSculptMeshPinchBrushTool;`
- L105 _public member_ `TSharedPtr<FUICommandInfo> BeginSculptMeshTwistKelvinBrushTool;`
- L106 _public member_ `TSharedPtr<FUICommandInfo> BeginSculptMeshFlattenBrushTool;`
- L107 _public member_ `TSharedPtr<FUICommandInfo> BeginSculptMeshPlaneBrushTool;`
- L108 _public member_ `TSharedPtr<FUICommandInfo> BeginSculptMeshPlaneViewAlignedBrushTool;`
- L109 _public member_ `TSharedPtr<FUICommandInfo> BeginSculptMeshFixedPlaneBrushTool;`
- L110 _public member_ `TSharedPtr<FUICommandInfo> BeginSculptMeshEraseLayerTool;`
- L112 _public member_ `TSharedPtr<FUICommandInfo> BeginRemeshSculptMeshTool;`
- L113 _public member_ `TSharedPtr<FUICommandInfo> BeginRemeshMeshTool;`
- L114 _public member_ `TSharedPtr<FUICommandInfo> BeginProjectToTargetTool;`
- L115 _public member_ `TSharedPtr<FUICommandInfo> BeginSimplifyMeshTool;`
- L116 _public member_ `TSharedPtr<FUICommandInfo> BeginEditNormalsTool;`
- L117 _public member_ `TSharedPtr<FUICommandInfo> BeginEditTangentsTool;`
- L118 _public member_ `TSharedPtr<FUICommandInfo> BeginRemoveOccludedTrianglesTool;`
- L119 _public member_ `TSharedPtr<FUICommandInfo> BeginUVProjectionTool;`
- L120 _public member_ `TSharedPtr<FUICommandInfo> BeginUVLayoutTool;`
- L121 _public member_ `TSharedPtr<FUICommandInfo> BeginPlaneCutTool;`
- L122 _public member_ `TSharedPtr<FUICommandInfo> BeginMirrorTool;`
- L123 _public member_ `TSharedPtr<FUICommandInfo> BeginHoleFillTool;`
- L124 _public member_ `TSharedPtr<FUICommandInfo> BeginLatticeDeformerTool;`
- L125 _public member_ `TSharedPtr<FUICommandInfo> BeginPolygonCutTool;`
- L128 _public member_ `TSharedPtr<FUICommandInfo> BeginVoxelMergeTool;`
- L129 _public member_ `TSharedPtr<FUICommandInfo> BeginVoxelBooleanTool;`
- L132 _public member_ `TSharedPtr<FUICommandInfo> BeginVoxelSolidifyTool;`
- L133 _public member_ `TSharedPtr<FUICommandInfo> BeginVoxelBlendTool;`
- L134 _public member_ `TSharedPtr<FUICommandInfo> BeginVoxelMorphologyTool;`
- L135 _public member_ `TSharedPtr<FUICommandInfo> BeginSelfUnionTool;`
- L136 _public member_ `TSharedPtr<FUICommandInfo> BeginMeshBooleanTool;`
- L137 _public member_ `TSharedPtr<FUICommandInfo> BeginMeshTrimTool;`
- L138 _public member_ `TSharedPtr<FUICommandInfo> BeginCutMeshWithMeshTool;`
- L139 _public member_ `TSharedPtr<FUICommandInfo> BeginMeshSelectionTool;`
- L140 _public member_ `TSharedPtr<FUICommandInfo> BeginBspConversionTool;`
- L141 _public member_ `TSharedPtr<FUICommandInfo> BeginMeshToVolumeTool;`
- L142 _public member_ `TSharedPtr<FUICommandInfo> BeginVolumeToMeshTool;`
- L143 _public member_ `TSharedPtr<FUICommandInfo> BeginMeshGroupPaintTool;`
- L144 _public member_ `TSharedPtr<FUICommandInfo> BeginMeshVertexPaintTool;`
- L146 _public member_ `TSharedPtr<FUICommandInfo> BeginPhysicsInspectorTool;`
- L147 _public member_ `TSharedPtr<FUICommandInfo> BeginSimpleCollisionEditorTool;`
- L148 _public member_ `TSharedPtr<FUICommandInfo> BeginSetCollisionGeometryTool;`
- L149 _public member_ `TSharedPtr<FUICommandInfo> BeginEditCollisionGeometryTool;`
- L150 _public member_ `TSharedPtr<FUICommandInfo> BeginExtractCollisionGeometryTool;`
- L152 _public member_ `TSharedPtr<FUICommandInfo> BeginMeshInspectorTool;`
- L153 _public member_ `TSharedPtr<FUICommandInfo> BeginGlobalUVGenerateTool;`
- L154 _public member_ `TSharedPtr<FUICommandInfo> BeginGroupUVGenerateTool;`
- L155 _public member_ `TSharedPtr<FUICommandInfo> BeginWeldEdgesTool;`
- L156 _public member_ `TSharedPtr<FUICommandInfo> BeginPolyGroupsTool;`
- L157 _public member_ `TSharedPtr<FUICommandInfo> BeginEditMeshMaterialsTool;`
- L158 _public member_ `TSharedPtr<FUICommandInfo> BeginTransformUVIslandsTool;`
- L159 _public member_ `TSharedPtr<FUICommandInfo> BeginMeshAttributePaintTool;`
- L160 _public member_ `TSharedPtr<FUICommandInfo> BeginAttributeEditorTool;`
- L161 _public member_ `TSharedPtr<FUICommandInfo> BeginBakeMeshAttributeMapsTool;`
- L162 _public member_ `TSharedPtr<FUICommandInfo> BeginBakeMultiMeshAttributeMapsTool;`
- L163 _public member_ `TSharedPtr<FUICommandInfo> BeginBakeRenderCaptureTool;`
- L164 _public member_ `TSharedPtr<FUICommandInfo> BeginBakeMeshAttributeVertexTool;`
- L165 _public member_ `TSharedPtr<FUICommandInfo> BeginUVSeamEditTool;`
- L167 _public member_ `TSharedPtr<FUICommandInfo> BeginSkinWeightsPaintTool;`
- L168 _public member_ `TSharedPtr<FUICommandInfo> BeginSkinWeightsBindingTool;`
- L170 _public member_ `TSharedPtr<FUICommandInfo> BeginSkeletonEditingTool;`
- L172 _public member_ `TSharedPtr<FUICommandInfo> BeginLODManagerTool;`
- L173 _public member_ `TSharedPtr<FUICommandInfo> BeginGenerateStaticMeshLODAssetTool;`
- L174 _public member_ `TSharedPtr<FUICommandInfo> BeginISMEditorTool;`
- L176 _public member_ `TSharedPtr<FUICommandInfo> BeginPolyModelTool_Inset;`
- L177 _public member_ `TSharedPtr<FUICommandInfo> BeginPolyModelTool_Outset;`
- L178 _public member_ `TSharedPtr<FUICommandInfo> BeginPolyModelTool_CutFaces;`
- L179 _public member_ `TSharedPtr<FUICommandInfo> BeginPolyModelTool_InsertEdgeLoop;`
- L180 _public member_ `TSharedPtr<FUICommandInfo> BeginPolyModelTool_ExtrudeEdges;`
- L181 _public member_ `TSharedPtr<FUICommandInfo> BeginPolyModelTool_PushPull;`
- L182 _public member_ `TSharedPtr<FUICommandInfo> BeginPolyModelTool_Bevel;`
- L184 _public member_ `TSharedPtr<FUICommandInfo> BeginPolyModelTool_PolyEd;`
- L185 _public member_ `TSharedPtr<FUICommandInfo> BeginPolyModelTool_TriSel;`
- L189 _public member_ `TSharedPtr<FUICommandInfo> MeshSelectionModeAction_NoSelection;` — selection state actions
- L190 _public member_ `TSharedPtr<FUICommandInfo> MeshSelectionModeAction_MeshTriangles;`
- L191 _public member_ `TSharedPtr<FUICommandInfo> MeshSelectionModeAction_MeshVertices;`
- L192 _public member_ `TSharedPtr<FUICommandInfo> MeshSelectionModeAction_MeshEdges;`
- L193 _public member_ `TSharedPtr<FUICommandInfo> MeshSelectionModeAction_GroupFaces;`
- L194 _public member_ `TSharedPtr<FUICommandInfo> MeshSelectionModeAction_GroupCorners;`
- L195 _public member_ `TSharedPtr<FUICommandInfo> MeshSelectionModeAction_GroupEdges;`
- L198 _public member_ `TSharedPtr<FUICommandInfo> BeginSelectionAction_Delete;`
- L199 _public member_ `TSharedPtr<FUICommandInfo> BeginSelectionAction_Disconnect;`
- L200 _public member_ `TSharedPtr<FUICommandInfo> BeginSelectionAction_Retriangulate;`
- L202 _public member_ `TSharedPtr<FUICommandInfo> BeginSelectionAction_SelectAll;`
- L203 _public member_ `TSharedPtr<FUICommandInfo> BeginSelectionAction_ExpandToConnected;`
- L204 _public member_ `TSharedPtr<FUICommandInfo> BeginSelectionAction_Invert;`
- L205 _public member_ `TSharedPtr<FUICommandInfo> BeginSelectionAction_InvertConnected;`
- L206 _public member_ `TSharedPtr<FUICommandInfo> BeginSelectionAction_Expand;`
- L207 _public member_ `TSharedPtr<FUICommandInfo> BeginSelectionAction_Contract;`
- L209 _public member_ `TSharedPtr<FUICommandInfo> BeginSelectionAction_Extrude;`
- L210 _public member_ `TSharedPtr<FUICommandInfo> BeginSelectionAction_Offset;`
- L212 _public member_ `TSharedPtr<FUICommandInfo> SelectionDragMode_None;`
- L213 _public member_ `TSharedPtr<FUICommandInfo> SelectionDragMode_Path;`
- L214 _public member_ `TSharedPtr<FUICommandInfo> SelectionLocalFrameMode_Geometry;`
- L215 _public member_ `TSharedPtr<FUICommandInfo> SelectionLocalFrameMode_Object;`
- L216 _public member_ `TSharedPtr<FUICommandInfo> SelectionMeshTypes_Volumes;`
- L217 _public member_ `TSharedPtr<FUICommandInfo> SelectionMeshTypes_StaticMeshes;`
- L218 _public member_ `TSharedPtr<FUICommandInfo> SelectionLocking;`
- L220 _public member_ `TSharedPtr<FUICommandInfo> AddToFavorites;`
- L221 _public member_ `TSharedPtr<FUICommandInfo> RemoveFromFavorites;`
- L222 _public member_ `TSharedPtr<FUICommandInfo> LoadFavoritesTools;`
- L223 _public member_ `TSharedPtr<FUICommandInfo> LoadSelectionTools;`
- L224 _public member_ `TSharedPtr<FUICommandInfo> LoadShapesTools;`
- L225 _public member_ `TSharedPtr<FUICommandInfo> LoadCreateTools;`
- L226 _public member_ `TSharedPtr<FUICommandInfo> LoadPolyTools;`
- L227 _public member_ `TSharedPtr<FUICommandInfo> LoadTriTools;`
- L228 _public member_ `TSharedPtr<FUICommandInfo> LoadDeformTools;`
- L229 _public member_ `TSharedPtr<FUICommandInfo> LoadTransformTools;`
- L230 _public member_ `TSharedPtr<FUICommandInfo> LoadMeshOpsTools;`
- L231 _public member_ `TSharedPtr<FUICommandInfo> LoadVoxOpsTools;`
- L232 _public member_ `TSharedPtr<FUICommandInfo> LoadAttributesTools;`
- L233 _public member_ `TSharedPtr<FUICommandInfo> LoadUVsTools;`
- L234 _public member_ `TSharedPtr<FUICommandInfo> LoadBakingTools;`
- L235 _public member_ `TSharedPtr<FUICommandInfo> LoadVolumeTools;`
- L236 _public member_ `TSharedPtr<FUICommandInfo> LoadLodsTools;`
- L238 _public member_ `TSharedPtr<FUICommandInfo> LaunchUVEditor;` — For connecting ModelingMode with UVEditor plugin
- L240 _public member_ `TSharedPtr<FUICommandInfo> LoadSkinTools;` — skeletal mesh editing tools
- L241 _public member_ `TSharedPtr<FUICommandInfo> LoadSkeletonTools;`
- L244 _public member_ `TSharedPtr<FUICommandInfo> BeginConvertMegaMeshTool;` — MegaMesh tools
- L245 _public member_ `TSharedPtr<FUICommandInfo> BeginSplitMegaMeshTool;`
- L246 _public member_ `TSharedPtr<FUICommandInfo> BeginMergeMegaMeshTool;`
- L247 _public member_ `TSharedPtr<FUICommandInfo> BeginResectionMeshTool;`
- L248 _public member_ `TSharedPtr<FUICommandInfo> BeginStitchMegaMeshTool;`
- L249 _public member_ `TSharedPtr<FUICommandInfo> BeginHeightmapImport;`
- L250 _public member_ `TSharedPtr<FUICommandInfo> BeginHeightSculptTool;`
- L251 _public member_ `TSharedPtr<FUICommandInfo> BeginExpandMegaMeshTool;`
- L253 _public member_ `TSharedPtr<FUICommandInfo> BeginHeightSculptBrushTool;`
- L254 _public member_ `TSharedPtr<FUICommandInfo> BeginHeightSmoothBrushTool;`
- L255 _public member_ `TSharedPtr<FUICommandInfo> BeginHeightFlattenBrushTool;`
- L256 _public member_ `TSharedPtr<FUICommandInfo> BeginSlopeErodeBrushTool;`
- L258 _public member_ `TSharedPtr<FUICommandInfo> BeginCreateMegaMeshRectangleTool;`
- L259 _public member_ `TSharedPtr<FUICommandInfo> BeginAddModifierTool;`
- L260 _public member_ `TSharedPtr<FUICommandInfo> BeginAppendModifierTool;`
- L262 _public member_ `TSharedPtr<FUICommandInfo> BeginAddRemeshModifierTool;`
- L263 _public member_ `TSharedPtr<FUICommandInfo> BeginAddPatchModifierTool;`
- L264 _public member_ `TSharedPtr<FUICommandInfo> BeginAddProjectModifierTool;`
- L265 _public member_ `TSharedPtr<FUICommandInfo> BeginAddInstancedPatchModifierTool;`
- L266 _public member_ `TSharedPtr<FUICommandInfo> BeginAddTexturePatchModifierTool;`
- L267 _public member_ `TSharedPtr<FUICommandInfo> BeginAddSplineModifierTool;`
- L268 _public member_ `TSharedPtr<FUICommandInfo> BeginAddMeshLayerModifierTool;`
- L269 _public member_ `TSharedPtr<FUICommandInfo> BeginAddNoiseModifierTool;`
- L270 _public member_ `TSharedPtr<FUICommandInfo> BeginAddBooleanModifierTool;`
- L271 _public member_ `TSharedPtr<FUICommandInfo> BeginAddLatticeModifierTool;`
- L272 _public member_ `TSharedPtr<FUICommandInfo> BeginAddSplineRemeshModifierTool;`
- L274 _public member_ `TSharedPtr<FUICommandInfo> RelaunchLastTool;`
- L277 _public member_ `TSharedPtr<FUICommandInfo> EnterShapesSubmode;` — Submodes
- L278 _public member_ `TSharedPtr<FUICommandInfo> EnterCreateSubmode;`
- L279 _public member_ `TSharedPtr<FUICommandInfo> EnterEditSubmode;`
- L280 _public member_ `TSharedPtr<FUICommandInfo> EnterSculptSubmode;`
- L281 _public member_ `TSharedPtr<FUICommandInfo> EnterBakeSubmode;`
- L282 _public member_ `TSharedPtr<FUICommandInfo> EnterPaintSubmode;`
- L283 _public member_ `TSharedPtr<FUICommandInfo> EnterModifiersSubmode;`
- L289 _public member_ `TSharedPtr<FUICommandInfo> AcceptActiveTool;`
- L290 _public member_ `TSharedPtr<FUICommandInfo> CancelActiveTool;`
- L291 _public member_ `TSharedPtr<FUICommandInfo> CompleteActiveTool;`
- L293 _public member_ `TSharedPtr<FUICommandInfo> AcceptOrCompleteActiveTool;`
- L294 _public member_ `TSharedPtr<FUICommandInfo> CancelOrCompleteActiveTool;`
- L299 _public prototype_ `virtual void RegisterCommands() override;` — Initialize above commands
- L307 _public prototype_ `static TSharedPtr<FUICommandInfo> RegisterExtensionPaletteCommand( FName Name, const FText& Label, const FText& Tooltip, const FSlateIcon& Icon);` — Dynamically register a new UI Command based on the given Name/Label/Tooltip/Icon. This is intended to be used outside of RegisterCommands(), eg by Modeling Mode extensions loaded when the Toolkit is created.
- L315 _private member_ `TMap<FUICommandInfo*, int32> CommandToRegisteredToolsIndex;` — Gets index into RegisteredTools for a given command.

#### struct `FMeshTerrainModeManagerCommands::FStartToolCommand`  
`struct FStartToolCommand`  
_L17-24_
- L19 _public member_ `FString ToolUIName;`
- L20 _public member_ `TSharedPtr<FUICommandInfo> ToolCommand;`
- L23 _public member_ `FText ShortName;` — Optional (not used if empty). Only relevant if using short labels for tools

#### struct `FMeshTerrainModeManagerCommands::FDynamicExtensionCommand`  
`struct FDynamicExtensionCommand`  
_L27-31_
- L29 _public member_ `FName RegistrationName;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> Command;`

### `Plugins/Experimental/MeshTerrainMode/Source/MeshTerrainMode/Private/MeshTerrainModeModule.h` (Private)


#### class `UE::MeshTerrain::FMeshTerrainModeModule`  
`class FMeshTerrainModeModule : public IModuleInterface`  
_L13-29_
- inherits: `IModuleInterface`
- L18 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L19 _public prototype_ `virtual void ShutdownModule() override;`
- L21 _public prototype_ `void OnPostEngineInit();`
- L25 _private member_ `TArray<FName> ClassesToUnregisterOnShutdown;` — StaticClass is not safe on shutdown, so we cache the name, and use this to unregister on shut down
- L26 _private member_ `TArray<FName> PropertiesToUnregisterOnShutdown;`
- L28 _private prototype_ `static void RegisterCustomizations();`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MeshTerrain` (scope `UE`)

### `Plugins/Experimental/MeshTerrainMode/Source/MeshTerrainMode/Private/MeshTerrainModeSelectionInteraction.h` (Private)


#### enum `EMeshTerrainModeSelectionInteraction_DragMode`  
`enum class EMeshTerrainModeSelectionInteraction_DragMode : uint8`  
_L31-36_
- reflection: `UENUM()`
- L33 _public enumerator_ `NoDragInteraction = 0`
- L34 _public enumerator_ `PathInteraction = 1`
- L35 _public enumerator_ `RectangleMarqueeInteraction = 2`

#### enum `EMeshTerrainModeSelectionInteraction_LocalFrameMode`  
`enum class EMeshTerrainModeSelectionInteraction_LocalFrameMode : uint8`  
_L39-43_
- reflection: `UENUM()`
- L41 _public enumerator_ `FromGeometry = 0`
- L42 _public enumerator_ `FromObject = 1`

#### class `UMeshTerrainModeSelectionInteraction`  
`class UMeshTerrainModeSelectionInteraction : public UObject, public IInputBehaviorSource, public IClickBehaviorTarget, public IHoverBehaviorTarget`  
_L64-231_
- reflection: `UCLASS()`
- inherits: `UObject,IInputBehaviorSource,IClickBehaviorTarget,IHoverBehaviorTarget`
- desc: UMeshTerrainModeSelectionInteraction provides element-level selection behavior (ie mesh triangles/edges/vertices) via the UGeometrySelectionManager. The Interaction doesn't actually know about the meshes or interact with them at all, it simply "operates" the SelectionManager based on user input. In addition to handling selection/deselection behaviors based on user input, the UModelingSelectionInteraction also creates a Gizmo for the active selection if it is transformable, and forwards gizmo transformations to the SelectionManager. Currently some desired Selection-related interactions require a slightly convoluted path through the code, because (for example) we want the standard UE editor gizmo to have "click precedence" over our selection click behaviors. However we will get the input event first, so we need to be able to check if the gizmo is hit via a callback function provided by the EdMode owning the ToolsContext this Interaction will be registered in. Similarly we need to be able to filter out hits if a closer visible object is hit, because there is no higher-level Behavior that will do that for us. (This may be improved in future, if more of the existing Editor interaction behaviors are re-implemented as InputBehaviors)
- L74 _public prototype_ `virtual void Initialize( TObjectPtr<UGeometrySelectionManager> SelectionManager, TUniqueFunction<bool()> CanChangeSelectionCallbackIn, TUniqueFunction<bool(const FInputDeviceRay&)> ExternalHitCaptureCallbackIn);` — Set up the Interaction, creates and registers Behaviors/etc. @param CanChangeSelectionCallbackIn this function will be called to determine if the current Selection is allowed to be modified (for example, when a Tool is active, we may wish to lock selection)
- L79 _public prototype_ `virtual void Shutdown();`
- L81 _public function_ `UGeometrySelectionManager* GetSelectionManager()`
- L82 _public prototype_ `UE::Geometry::FGeometrySelectionUpdateConfig GetActiveSelectionUpdateConfig() const;`
- L84 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI);`
- L85 _public prototype_ `virtual void DrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI);`
- L92 _public function_ `EMeshTerrainModeSelectionInteraction_DragMode GetActiveDragMode() const`
- L93 _public prototype_ `void SetActiveDragMode(EMeshTerrainModeSelectionInteraction_DragMode NewMode);`
- L100 _public prototype_ `virtual void ApplyPendingTransformInteractions();` — this needs to be called from EdMode tick or rendering, to avoid mouse-interrupt priority issues
- L102 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnBeginTransformInteraction);`
- L103 _public member_ `FOnBeginTransformInteraction OnTransformBegin;`
- L105 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnEndTransformInteraction);`
- L106 _public member_ `FOnEndTransformInteraction OnTransformEnd;`
- L111 _public function_ `EMeshTerrainModeSelectionInteraction_LocalFrameMode GetLocalFrameMode() const` — Support for Adjusting Local Frame Mode
- L112 _public prototype_ `void SetLocalFrameMode(EMeshTerrainModeSelectionInteraction_LocalFrameMode NewLocalFrameMode);`
- L117 _protected member_ `TObjectPtr<USingleClickOrDragInputBehavior> ClickOrDragBehavior;` — `UPROPERTY()` — click-to-select behavior, various drag behaviors
- L121 _protected member_ `TObjectPtr<UMouseHoverBehavior> HoverBehavior;` — `UPROPERTY()` — mouse hover behavior
- L125 _protected member_ `TObjectPtr<UInputBehaviorSet> BehaviorSet;` — `UPROPERTY()` — set of all behaviors, will be passed up to UInputRouter
- L131 _public function_ `virtual const UInputBehaviorSet* GetInputBehaviors() const` — IInputBehaviorSource API
- L139 _public prototype_ `virtual FInputRayHit IsHitByClick(const FInputDeviceRay& ClickPos) override;` — IClickBehaviorTarget implementation
- L140 _public prototype_ `virtual void OnClicked(const FInputDeviceRay& ClickPos) override;`
- L146 _public prototype_ `virtual FInputRayHit BeginHoverSequenceHitTest(const FInputDeviceRay& PressPos) override;` — IHoverBehaviorTarget implementation
- L147 _public prototype_ `virtual void OnBeginHover(const FInputDeviceRay& DevicePos) override;`
- L148 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) override;`
- L149 _public prototype_ `virtual void OnEndHover() override;`
- L154 _public prototype_ `virtual void OnUpdateModifierState(int ModifierID, bool bIsOn) override;` — IModifierToggleBehaviorTarget implementation
- L160 _protected function_ `TUniqueFunction<bool()> CanChangeSelectionCallback = []()` — default change-selection callback always allows selection change
- L160 _protected member_ `TUniqueFunction<bool()> CanChangeSelectionCallback = []() { return true; };` — default change-selection callback always allows selection change
- L163 _protected function_ `TUniqueFunction<bool(const FInputDeviceRay&)> ExternalHitCaptureCallback = [](const FInputDeviceRay&)`
- L163 _protected member_ `TUniqueFunction<bool(const FInputDeviceRay&)> ExternalHitCaptureCallback = [](const FInputDeviceRay&) { return false; };`
- L165 _protected prototype_ `void ComputeSceneHits(const FInputDeviceRay& ClickPos, bool& bHitActiveObjects, FInputRayHit& ActiveObjectHit, bool& bHitInactiveObjectFirst, FInputRayHit& InactiveObjectHit);`
- L169 _protected member_ `bool bClearSelectionOnClicked = false;`
- L172 _protected member_ `static const int AddToSelectionModifier = 1;` — flags used to identify behavior modifier keys/buttons
- L173 _protected member_ `bool bAddToSelectionEnabled = false;`
- L175 _protected member_ `static const int ToggleSelectionModifier = 2;`
- L176 _protected member_ `bool bToggleSelectionEnabled = false;`
- L181 _protected member_ `TObjectPtr<UGeometrySelectionManager> SelectionManager;` — `UPROPERTY()`
- L183 _protected member_ `FDelegateHandle OnSelectionModifiedDelegate;`
- L184 _protected prototype_ `void OnSelectionManager_SelectionModified();`
- L190 _protected member_ `TObjectPtr<UTransformProxy> TransformProxy;` — `UPROPERTY()`
- L193 _protected member_ `TObjectPtr<UCombinedTransformGizmo> TransformGizmo;` — `UPROPERTY()`
- L196 _protected member_ `TObjectPtr<UDragAlignmentInteraction> DragAlignmentInteraction;` — `UPROPERTY()`
- L199 _protected member_ `TObjectPtr<UKeyAsModifierInputBehavior> DragAlignmentToggleBehavior;` — `UPROPERTY()`
- L201 _protected member_ `UE::Geometry::FFrame3d InitialGizmoFrame;`
- L202 _protected member_ `FVector3d InitialGizmoScale;`
- L203 _protected member_ `UE::Geometry::FFrame3d LastUpdateGizmoFrame;`
- L204 _protected member_ `FVector3d LastUpdateGizmoScale;`
- L205 _protected member_ `FVector3d LastTranslationDelta;`
- L206 _protected member_ `FVector4d LastRotateDelta;`
- L207 _protected member_ `FVector3d LastScaleDelta;`
- L208 _protected member_ `bool bInActiveTransform = false;`
- L210 _protected prototype_ `void UpdateGizmoOnSelectionChange();`
- L211 _protected member_ `bool bGizmoUpdatePending = false;`
- L213 _protected prototype_ `void OnBeginGizmoTransform(UTransformProxy* Proxy);`
- L214 _protected prototype_ `void OnEndGizmoTransform(UTransformProxy* Proxy);`
- L215 _protected prototype_ `void OnGizmoTransformChanged(UTransformProxy* Proxy, FTransform Transform);`
- L219 _protected member_ `EMeshTerrainModeSelectionInteraction_DragMode ActiveDragMode = EMeshTerrainModeSelectionInteraction_DragMode::NoDragInteraction;`
- L220 _protected prototype_ `void UpdateActiveDragMode();`
- L222 _protected member_ `EMeshTerrainModeSelectionInteraction_LocalFrameMode LocalFrameMode = EMeshTerrainModeSelectionInteraction_LocalFrameMode::FromGeometry;`
- L225 _protected member_ `TObjectPtr<URectangleMarqueeInteraction> RectangleMarqueeInteraction;` — `UPROPERTY()`
- L227 _protected prototype_ `void OnMarqueeRectangleFinished(const FCameraRectangle& Rectangle, bool bCancelled);`
- L230 _protected member_ `TObjectPtr<UMeshTerrainModePathSelectionInteraction> PathSelectionInteraction;` — `UPROPERTY()`

#### class `UMeshTerrainModePathSelectionInteraction`  
`class UMeshTerrainModePathSelectionInteraction : public UObject, public IClickDragBehaviorTarget`  
_L242-258_
- reflection: `UCLASS()`
- inherits: `UObject,IClickDragBehaviorTarget`
- desc: UPathSelectionInteraction is a simple drag-interaction for Selection, which essentially just selects/deselects any element hit by the cursor. Currently no attempt is made to (eg) subsample, so a fast-moving cursor will skip over some faces.
- L246 _public prototype_ `void Setup(UMeshTerrainModeSelectionInteraction* SelectionInteraction);`
- L250 _protected member_ `TWeakObjectPtr<UMeshTerrainModeSelectionInteraction> SelectionInteraction = nullptr;` — `UPROPERTY()`
- L252 _protected prototype_ `virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& PressPos) override;`
- L253 _protected prototype_ `virtual void OnClickPress(const FInputDeviceRay& PressPos) override;`
- L254 _protected prototype_ `virtual void OnClickDrag(const FInputDeviceRay& DragPos) override;`
- L255 _protected prototype_ `virtual void OnClickRelease(const FInputDeviceRay& ReleasePos) override;`
- L256 _protected prototype_ `virtual void OnTerminateDragSequence() override;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Geometry` (scope `UE`)
- L102 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnBeginTransformInteraction);`
- L105 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnEndTransformInteraction);`

### `Plugins/Experimental/MeshTerrainMode/Source/MeshTerrainMode/Private/MeshTerrainModeSettings.h` (Private)


#### enum `EMeshTerrainModeDefaultMeshObjectType`  
`enum class EMeshTerrainModeDefaultMeshObjectType`  
_L16-24_
- reflection: `UENUM()`
- L19 _public enumerator_ `StaticMeshAsset` — Generate a new Static Mesh Asset (using Generated Asset settings below) and AStaticMeshActor
- L21 _public enumerator_ `VolumeActor` — Generate a new AVolume Actor
- L23 _public enumerator_ `DynamicMeshActor` — Generate a new ADynamicMeshActor (stored locally in the Level)

#### enum `EMeshTerrainModeAssetGenerationBehavior`  
`enum class EMeshTerrainModeAssetGenerationBehavior`  
_L29-39_
- reflection: `UENUM()`
- L32 _public enumerator_ `AutoGenerateAndAutosave` — Generate and automatically Save new Assets on creation
- L35 _public enumerator_ `AutoGenerateButDoNotAutosave` — Generate new Assets and mark as Modified but do not automatically Save
- L38 _public enumerator_ `InteractivePromptToSave` — Prompt to Save each new Asset upon Creation

#### enum `EMeshTerrainModeAssetGenerationLocation`  
`enum class EMeshTerrainModeAssetGenerationLocation`  
_L44-54_
- reflection: `UENUM()`
- L47 _public enumerator_ `AutoGeneratedWorldRelativeAssetPath` — All generated assets will be stored in an AutoGenerated folder that is located relative to the World they are being saved in
- L50 _public enumerator_ `AutoGeneratedGlobalAssetPath` — All generated assets will be stored in a root-level AutoGenerated folder
- L53 _public enumerator_ `CurrentAssetBrowserPathIfAvailable` — Generated assets will be stored in the currently-visible Asset Browser folder if available, otherwise at the Auto Generated Asset Path

#### class `UMeshTerrainModeSettings`  
`class UMeshTerrainModeSettings : public UDeveloperSettings`  
_L61-226_
- reflection: `UCLASS(MinimalAPI, config=Editor)`
- inherits: `UDeveloperSettings`
- desc: Settings for the Mesh Terrain Mode plug-in.
- L69 _public function_ `virtual FName GetContainerName() const override`
- L70 _public function_ `virtual FName GetCategoryName() const override`
- L71 _public function_ `virtual FName GetSectionName() const override`
- L73 _public prototype_ `virtual FText GetSectionText() const override;`
- L74 _public prototype_ `virtual FText GetSectionDescription() const override;`
- L80 _protected member_ `bool bEnableDynamicMeshActors = false;` — `UPROPERTY()` — Enable/Disable the options to emit Dynamic Mesh Actors in Mesh Terrain Mode
- L84 _protected member_ `EMeshTerrainModeAssetGenerationLocation AssetGenerationLocation = EMeshTerrainModeAssetGenerationLocation::AutoGeneratedWorldRelativeAssetPath;` — `UPROPERTY(config, EditAnywhere, Category = "Mesh Terrain Mode|Generated Assets")` — Where should Assets auto-generated by Mesh Terrain be stored by default
- L88 _protected member_ `EMeshTerrainModeAssetGenerationBehavior AssetGenerationMode = EMeshTerrainModeAssetGenerationBehavior::AutoGenerateButDoNotAutosave;` — `UPROPERTY(config, EditAnywhere, Category = "Mesh Terrain Mode|Generated Assets")` — How should Assets auto-generated by Mesh Terrain be handled in terms of saving, naming, etc
- L92 _public function_ `EMeshTerrainModeAssetGenerationLocation GetAssetGenerationLocation() const`
- L99 _public function_ `void SetAssetGenerationLocation(const EMeshTerrainModeAssetGenerationLocation Location)`
- L104 _public function_ `EMeshTerrainModeAssetGenerationBehavior GetAssetGenerationMode() const`
- L111 _public function_ `void SetAssetGenerationMode(const EMeshTerrainModeAssetGenerationBehavior Mode)`
- L118 _public member_ `EMeshTerrainModeDefaultMeshObjectType DefaultMeshObjectType = EMeshTerrainModeDefaultMeshObjectType::StaticMeshAsset;` — `UPROPERTY(config, EditAnywhere, Category = "Mesh Terrain Mode")` — What type of Mesh Object should Output Type Setting default to in Mesh Terrain Mode (takes effect after Editor restart)
- L122 _public member_ `FString AutoGeneratedAssetPath = TEXT("_GE` — `UPROPERTY(config, EditAnywhere, Category = "Mesh Terrain Mode|Generated Assets")` — Assets auto-generated by Mesh Terrain are stored at this path, relative to the parent path defined by the Location. Set to an empty string to disable.
- L126 _public member_ `bool bStoreUnsavedLevelAssetsInTopLevelGameFolder = true;` — `UPROPERTY(config, EditAnywhere, Category = "Mesh Terrain Mode|Generated Assets")` — If true, Auto-Generated Assets created in an unsaved Level will be stored relative to top-level folder, otherwise they will be stored in /Temp and cannot be saved until they are explicitly moved to a permanent location
- L130 _public member_ `bool bUsePerUserAutogenSubfolder = true;` — `UPROPERTY(config, EditAnywhere, Category = "Mesh Terrain Mode|Generated Assets")` — If true, Autogenerated Assets are stored in per-user folders below the Autogen path
- L134 _public member_ `FString AutogenSubfolderUserNameOverride;` — `UPROPERTY(config, EditAnywhere, Category = "Mesh Terrain Mode|Generated Assets")` — Overrides the user name used for per-user folders below the Autogen path. This might be necessary to resolve issues with source control, for example. Note that the per-user folder name might not contain the name exactly as provided.
- L138 _public member_ `bool bAppendRandomStringToName = true;` — `UPROPERTY(config, EditAnywhere, Category = "Mesh Terrain Mode|Generated Assets")` — If true, Autogenerated Assets have a short random string generated and appended to their name
- L146 _public member_ `bool bRespectLevelEditorGizmoMode = false;` — `UPROPERTY(config, EditAnywhere, Category = "Mesh Terrain Mode|User Interface")` — If true, the standard UE Editor Gizmo Mode (ie selected via the Level Editor Viewport toggle) will be used to configure the Gizmo, otherwise a Combined Gizmo will always be used. It may be necessary to exit and re-enter Mesh Terrain Mode after changing this setting.
- L154 _public member_ `bool bEnableMeshSelections = false;` — `UPROPERTY(config, EditAnywhere, Category = "Mesh Terrain Mode|Selection", meta = (DisplayName="Enable Mesh Selection UI"))` — Enable/Disable the Mesh Selection System.
- L156 _public function_ `virtual bool GetMeshSelectionsEnabled() const`
- L161 _public function_ `virtual void SetMeshSelectionsEnabled(const bool bEnabled)`
- L167 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(UMeshTerrainModeSettingsModified, UObject*, FProperty*);`
- L168 _public member_ `UMeshTerrainModeSettingsModified OnModified;`
- L170 _public function_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override`
- L181 _public function_ `virtual bool InRestrictiveMode() const`
- L186 _public function_ `virtual void SetRestrictiveMode(bool bEnabled)`
- L191 _public function_ `virtual FString GetRestrictiveModeAutoGeneratedAssetPath() const`
- L196 _public function_ `virtual bool SetRestrictiveModeAutoGeneratedAssetPath(const FString& AssetPath)`
- L210 _protected member_ `FString RestrictiveModeAutoGeneratedAssetPath = TEXT("Mes` — `UPROPERTY(Config)` — Assets auto-generated by Mesh Terrain are stored at this path when in restrictive mode, relative to the package folder path.
- L212 _protected member_ `bool bRestrictiveMode = false;`
- L225 _public member_ `bool bEnableAbsoluteWorldSnapping = false;` — `UPROPERTY(Transient)` — Toggle Absolute World Grid Position snapping

#### struct `FMeshTerrainModeCustomSectionColor`  
`struct FMeshTerrainModeCustomSectionColor`  
_L235-246_
- reflection: `USTRUCT()`
- desc: Defines a color to be used for a particular Tool Palette Section
- L241 _public member_ `FString SectionName = TEXT("");` — `UPROPERTY(EditAnywhere, Category = "SectionColor")` — Name of Section in Mesh Terrain Mode Palette
- L245 _public member_ `FLinearColor Color = FLinearColor::Gray;` — `UPROPERTY(EditAnywhere, Category = "SectionColor")` — Custom Header Color

#### struct `FMeshTerrainModeCustomToolColor`  
`struct FMeshTerrainModeCustomToolColor`  
_L253-270_
- reflection: `USTRUCT()`
- desc: Defines a color to be used for a particular Tool Palette Tool
- L265 _public member_ `FString ToolName = TEXT("");` — `UPROPERTY(EditAnywhere, Category = "ToolColor")` — Name of Section or Tool in Mesh Terrain Mode Palette Format: SectionName        (Specifies a default color for all tools in the section.) SectionName.ToolName        (Specifies an override color for a specific tool in the given section.)
- L269 _public member_ `FLinearColor Color = FLinearColor::Gray;` — `UPROPERTY(EditAnywhere, Category = "ToolColor")` — Custom Tool Color

#### struct `FMeshTerrainModeAssetCollectionSet`  
`struct FMeshTerrainModeAssetCollectionSet`  
_L277-288_
- reflection: `USTRUCT()`
- desc: Defines a Named list/set of content-browser Collection names
- L283 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, Category = "CollectionSet")` — Name of the set of collections
- L287 _public member_ `TArray<FCollectionReference> Collections;` — `UPROPERTY(EditAnywhere, Category = "CollectionSet")` — List of Collection names

#### class `UMeshTerrainModeCustomizationSettings`  
`class UMeshTerrainModeCustomizationSettings : public UDeveloperSettings`  
_L292-416_
- reflection: `UCLASS(config=Editor)`
- inherits: `UDeveloperSettings`
- L299 _public function_ `virtual FName GetContainerName() const`
- L300 _public function_ `virtual FName GetCategoryName() const`
- L301 _public function_ `virtual FName GetSectionName() const`
- L303 _public prototype_ `virtual FText GetSectionText() const override;`
- L304 _public prototype_ `virtual FText GetSectionDescription() const override;`
- L312 _public member_ `TArray<FMeshTerrainModeAssetCollectionSet> BrushAlphaSets;` — `UPROPERTY(config, EditAnywhere, Category = "Mesh Terrain Mode|Tool Assets")` — A Brush Alpha Set is a named list of Content Browser Collections, which will be shown as a separate tab in the Texture Asset Picker used in various Mesh Terrain Mode when selecting a Brush Alpha (eg in Sculpting)
- L319 _public member_ `bool bShowCategoryButtonLabels = true;` — `UPROPERTY(config, EditAnywhere, Category = "Mesh Terrain Mode|UI Customization")` — If true, the category labels will be shown on the toolbar buttons, else they will be hidden
- L325 _public member_ `bool bAlwaysShowToolButtons = false;` — `UPROPERTY(config, EditAnywhere, Category = "Mesh Terrain Mode|UI Customization")` — If true, Tool buttons will always be shown when in a Tool. By default they will be hidden.
- L329 _public member_ `bool bEscapeAcceptsToolResult = false;` — `UPROPERTY(config, EditAnywhere, Category = "Mesh Terrain Mode|UI Customization")` — If true, pressing Escape will Accept the active tool result instead of Cancelling it. Defaults to off.
- L333 _public member_ `bool bExitModeAcceptsToolResult = true;` — `UPROPERTY(config, EditAnywhere, Category = "Mesh Terrain Mode|UI Customization")` — If true, exiting Mesh Terrain Mode will Accept the active tool result instead of Cancelling it. Defaults to on.
- L339 _public member_ `FLinearColor UnselectedColor = FLinearColor(.068478f, 0.56478f, 0.708376f,.5f);` — `UPROPERTY(Config, EditAnywhere, Category = "Mesh Terrain Mode|Mesh Element Selection Mode")` — Custom color for when geometry is not a part of current selection when using Mesh Element Selection
- L345 _public member_ `FLinearColor HoverOverSelectedColor = FLinearColor(1.0f, 0.943014f, 0.74f);` — `UPROPERTY(Config, EditAnywhere, Category = "Mesh Terrain Mode|Mesh Element Selection Mode")` — Custom color hovering over selected geometry in Mesh Element Selection
- L351 _public member_ `FLinearColor HoverOverUnselectedColor = FLinearColor(1.0f, 0.25f, 0.712328f, .5f);` — `UPROPERTY(Config, EditAnywhere, Category = "Mesh Terrain Mode|Mesh Element Selection Mode")` — Custom color hovering over unselected geometry in Mesh Element Selection
- L357 _public member_ `FLinearColor GeometrySelectedColor = FLinearColor(0.982251f, 0.672443f, 0.029557f, .5f);` — `UPROPERTY(Config, EditAnywhere, Category = "Mesh Terrain Mode|Mesh Element Selection Mode")` — Custom color for when geometry is a part of the current selection when using Mesh Element Selection
- L363 _public member_ `FLinearColor GeometrySoftSelectedColor = FLinearColor(0.063f, 0.161f, 0.71f, .5f);` — `UPROPERTY(Config, EditAnywhere, Category = "Mesh Terrain Mode|Mesh Element Selection Mode")` — Custom color for when geometry is a part of the soft selection when using Mesh Element Selection
- L369 _public member_ `FVector2f SubmodeToolPanelSize = FVector2f::ZeroVector;` — `UPROPERTY(config, EditAnywhere, Category = "Mesh Terrain Mode|UI Customization")` — Saved size for the Submode Tool Panel
- L375 _public member_ `FToolWidget_DragBoxPosition DetailsOverlayPosition;` — `UPROPERTY(config, EditAnywhere, Category = "Mesh Terrain Mode|UI Customization")` — Saved position for the viewport Tool Details panel
- L381 _public member_ `FVector2f DetailsOverlaySize = FVector2f::ZeroVector;` — `UPROPERTY(Config, EditAnywhere, Category = "Mesh Terrain Mode|UI Customization")` — Saved size for the viewport Tool Details panel
- L387 _public member_ `FToolWidget_DragBoxPosition QuickSettingsOverlayPosition;` — `UPROPERTY(config, EditAnywhere, Category = "Mesh Terrain Mode|UI Customization")` — Saved position for the viewport Quick Settings bar
- L394 _public member_ `int32 LastMeshSelectionDragMode = 0;` — `UPROPERTY(config)`
- L397 _public member_ `int32 LastMeshSelectionLocalFrameMode = 0;` — `UPROPERTY(config)`
- L404 _public member_ `int32 LastMeshSelectionElementType = 0;` — `UPROPERTY()`
- L407 _public member_ `int32 LastMeshSelectionTopologyMode = 0;` — `UPROPERTY()`
- L410 _public member_ `bool bLastMeshSelectionVolumeToggle = true;` — `UPROPERTY()`
- L413 _public member_ `bool bLastMeshSelectionStaticMeshToggle = true;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MESHTERRAINMODE_API`
- L167 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(UMeshTerrainModeSettingsModified, UObject*, FProperty*);`

### `Plugins/Experimental/MeshTerrainMode/Source/MeshTerrainMode/Private/MeshTerrainModeStyle.h` (Private)


#### class `FMeshTerrainModeStyle`  
`class FMeshTerrainModeStyle`  
_L9-28_
- L12 _public prototype_ `static void Initialize();`
- L14 _public prototype_ `static void Shutdown();`
- L16 _public prototype_ `static TSharedPtr< class ISlateStyle > Get();`
- L18 _public prototype_ `static FName GetStyleSetName();`
- L21 _public prototype_ `static const FSlateBrush* GetBrush(FName PropertyName, const ANSICHAR* Specifier = NULL);` — use to access icons defined by the style set by name, eg GetBrush("BrushFalloffIcons.Smooth")
- L24 _private prototype_ `static FString InContent(const FString& RelativePath, const ANSICHAR* Extension);`
- L27 _private member_ `static TSharedPtr< class FSlateStyleSet > StyleSet;`

### `Plugins/Experimental/MeshTerrainMode/Source/MeshTerrainMode/Private/MeshTerrainModeStylusInputHandler.h` (Private)


#### class `UE::MeshTerrain::FStylusInputHandler`  
`class FStylusInputHandler final : public UE::StylusInput::IStylusInputEventHandler, public IToolStylusStateProviderAPI`  
_L26-67_
- inherits: `UE::StylusInput::IStylusInputEventHandler,IToolStylusStateProviderAPI`
- desc: FStylusInputHandler registers itself as a listener for stylus events and implements the IToolStylusStateProviderAPI interface, which allows MeshSurfacePointTool implementations to query for pen pressure. This is kind of a hack. Unfortunately, the current Stylus module is a Plugin so it cannot be used in the base ToolsFramework directly. So, we need this in the Mode as a workaround.
- L29 _public prototype_ `FStylusInputHandler();`
- L39 _public prototype_ `bool RegisterWindow(const TSharedRef<SWidget>& Widget);` — Registers the window containing the given Widget for Stylus input handling. Registered windows persist for the lifetime of the StylusInputHandler. @param Widget The widget whose window is to be registered. @return True if the window was registered, false if the window was invalid or was previously registered.
- L43 _public prototype_ `virtual FString GetName() override;` — IStylusInputEventHandler implementation
- L44 _public prototype_ `virtual void OnPacket(const UE::StylusInput::FStylusInputPacket& Packet, UE::StylusInput::IStylusInputInstance* Instance) override;`
- L48 _public function_ `virtual float GetCurrentPressure() const override` — IToolStylusStateProviderAPI implementation
- L57 _public prototype_ `bool AnyContextSupportsPressure() const;` — Query if any active contexts supports pressure @return True if an active contexts supports pressure
- L60 _private prototype_ `void ProcessPacket(const UE::StylusInput::FStylusInputPacket& Packet, UE::StylusInput::IStylusInputInstance* Instance);`
- L61 _private prototype_ `const UE::StylusInput::IStylusInputTabletContext* GetTabletContext(UE::StylusInput::IStylusInputInstance* Instance, uint32 TabletContextID);`
- L63 _private member_ `TMap<TSharedPtr<SWindow>, UE::StylusInput::IStylusInputInstance*> StylusInputInstances;`
- L64 _private member_ `TMap<uint32, TSharedPtr<UE::StylusInput::IStylusInputTabletContext>> TabletContexts;`
- L66 _private member_ `float ActivePressure = 1.0f;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MeshTerrain` (scope `UE`)

### `Plugins/Experimental/MeshTerrainMode/Source/MeshTerrainMode/Private/MeshTerrainModeToolExtensions.h` (Private)


#### struct `FExtensionSubmodeAddon`  
`struct FExtensionSubmodeAddon`  
_L19-33_
- L21 _public function_ `FExtensionSubmodeAddon(FName Name, const UE::MeshTerrain::FSubmodeToolPalette& Palette) : SubmodeName(Name) , ToolPalette(Palette)`
- L26 _public function_ `FExtensionSubmodeAddon(const FExtensionSubmodeAddon& Other) : SubmodeName(Other.SubmodeName) , ToolPalette(Other.ToolPalette)`
- L31 _public member_ `FName SubmodeName;`
- L32 _public member_ `UE::MeshTerrain::FSubmodeToolPalette ToolPalette;`

#### struct `FExtensionSubmodeDescription`  
`struct FExtensionSubmodeDescription`  
_L39-43_
- desc: IModelingProtoModeToolExtension implementations return the list of Tools & Submodes they provide via instances of FExtensionSubmodeDescription.
- L42 _public member_ `TFunction<TSharedPtr<UE::MeshTerrain::FSubmode>()> MakeNewSubmode;` — Submode that is added to the toolset.

#### struct `FExtensionCustomToolDescription`  
`struct FExtensionCustomToolDescription : public FExtensionToolDescription`  
_L45-67_
- inherits: `FExtensionToolDescription`
- L52 _public member_ `TFunction<bool(UInteractiveToolManager*, EToolSide)> ExecuteAction;` — Specify this function to override the default ExecuteAction behavior of executing the associated action. @return True, if the ExecuteAction was handled by this override, false otherwise.
- L59 _public member_ `TFunction<bool(UInteractiveToolManager*, EToolSide)> CanExecuteAction;` — Specify this function to override the default CanExecuteAction handled by the owning Mode. @return True if the action can be executed.
- L66 _public member_ `TFunction<bool(UInteractiveToolManager*, EToolSide)> IsActionChecked;` — Specify this function to override the default IsActionChecked behavior of comparing the ActiveToolName against the ToolIdentifier. @return True if the action checkbox should be checked.

#### class `IMeshTerrainModeToolExtension`  
`class IMeshTerrainModeToolExtension : public IModelingModeToolExtension`  
_L74-99_
- inherits: `IModelingModeToolExtension`
- desc: IModelingProtoModeToolExtension uses the IModularFeature API to allow a Plugin to provide a set of InteractiveTool's to be exposed in Modeling Proto Mode.
- L77 _public function_ `virtual ~IMeshTerrainModeToolExtension()`
- L82 _public function_ `virtual void GetExtensionSubmodeAddons(TArray<FExtensionSubmodeAddon>& AddonsOut)` — Query the Extension for a list of tools to add on to existing Submodes.
- L87 _public function_ `virtual void GetExtensionSubmodes(TArray<FExtensionSubmodeDescription>& SubmodesOut)` — Query the Extension for a list of Submodes to expose in Modeling Mode.
- L92 _public function_ `virtual void GetExtensionCustomTools(const FExtensionToolQueryInfo& QueryInfo, TArray<FExtensionCustomToolDescription>& OutTools)` — Custom tool registration with optional overrides for ExecuteAction, CanExecuteAction and IsActionChecked.
- L94 _public function_ `static FName GetModularFeatureName()`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`

### `Plugins/Experimental/MeshTerrainMode/Source/MeshTerrainMode/Private/MeshTerrainModeToolkit.h` (Private)


#### struct `UE::MeshTerrain::FToolPresetOption`  
`struct FToolPresetOption`  
_L43-50_
- L45 _public member_ `FString PresetLabel;`
- L46 _public member_ `FString PresetTooltip;`
- L47 _public member_ `FSlateIcon PresetIcon;`
- L48 _public member_ `int32 PresetIndex;`
- L49 _public member_ `FSoftObjectPath PresetCollection;`

#### class `UE::MeshTerrain::FMeshTerrainModeToolkit`  
`class FMeshTerrainModeToolkit : public FModeToolkit`  
_L52-299_
- inherits: `FModeToolkit`
- L56 _public prototype_ `FMeshTerrainModeToolkit();`
- L60 _public prototype_ `virtual void Init(const TSharedPtr<IToolkitHost>& InitToolkitHost, TWeakObjectPtr<UEdMode> InOwningMode) override;` — FModeToolkit interface
- L61 _public prototype_ `virtual void RequestModeUITabs() override;`
- L62 _public prototype_ `virtual void InvokeUI() override;`
- L63 _public prototype_ `virtual void ShutdownUI() override;`
- L66 _public prototype_ `virtual FName GetToolkitFName() const override;` — IToolkit interface
- L67 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L68 _public prototype_ `virtual TSharedPtr<class SWidget> GetInlineContent() const override;`
- L71 _public prototype_ `virtual void InitializeAfterModeSetup();` — initialize toolkit widgets that need to wait until mode is initialized/entered
- L72 _public prototype_ `virtual void UninitializeOnModeDeactivate();`
- L75 _public prototype_ `virtual void PostNotification(const FText& Message);` — set/clear notification message area
- L76 _public prototype_ `virtual void ClearNotification();`
- L79 _public prototype_ `virtual void PostWarning(const FText& Message);` — set/clear warning message area
- L80 _public prototype_ `virtual void ClearWarning();`
- L83 _public prototype_ `virtual void GetToolPaletteNames(TArray<FName>& InPaletteName) const override;` — Returns the Mode specific tabs in the mode toolbar
- L84 _public prototype_ `virtual FText GetToolPaletteDisplayName(FName PaletteName) const override;`
- L85 _public prototype_ `virtual void OnToolPaletteChanged(FName PaletteName) override;`
- L86 _public function_ `virtual bool HasIntegratedToolPalettes() const override`
- L87 _public function_ `virtual bool HasExclusiveToolPalettes() const override`
- L89 _public function_ `virtual FText GetActiveToolDisplayName() const override`
- L90 _public function_ `virtual FText GetActiveToolMessage() const override`
- L92 _public prototype_ `virtual void ShowRealtimeAndModeWarnings(bool bShowRealtimeWarning);`
- L94 _public prototype_ `virtual void OnToolStarted(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;`
- L95 _public prototype_ `virtual void OnToolEnded(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;`
- L97 _public prototype_ `virtual void CustomizeModeDetailsViewArgs(FDetailsViewArgs& ArgsInOut) override;`
- L99 _public prototype_ `void OnActiveViewportChanged(TSharedPtr<IAssetViewport>, TSharedPtr<IAssetViewport> );`
- L101 _public prototype_ `virtual bool RequestAcceptCancelButtonOverride(IToolHostCustomizationAPI::FAcceptCancelButtonOverrideParams& Params);`
- L102 _public prototype_ `virtual bool RequestCompleteButtonOverride(IToolHostCustomizationAPI::FCompleteButtonOverrideParams& Params);`
- L103 _public prototype_ `virtual void ClearButtonOverrides();`
- L106 _public prototype_ `virtual FText GetRestrictiveModeAutoGeneratedAssetPathText() const;` — Read and write Autogen Subfolder quick setting in restrictive mode.
- L107 _public prototype_ `virtual void OnRestrictiveModeAutoGeneratedAssetPathTextCommitted(const FText& InNewText, ETextCommit::Type InTextCommit) const;`
- L111 _public prototype_ `void BindGizmoNumericalUI();` — The mode is expected to call this after setting up the gizmo context object so that any subsequently created gizmos are bound to the numerical UI.
- L114 _public prototype_ `UGeometrySelectionManager* GetMeshSelectionManager();` — get cached UGeometrySelectionManager pointer for the current Mode
- L117 _public function_ `bool IsInActiveTool() const` — @return true if we are currently in a tool, used to enable/disable UI things
- L121 _public function_ `TSharedPtr<STransformGizmoNumericalUIOverlay> GetGizmoNumericalUIOverlayWidget()` — This is exposed only for the convenience of being able to create the numerical UI submenu in a non-member function in ModelingModeToolkit_Toolbars.cpp
- L123 _public prototype_ `void NotifySelectionSystemEnabledStateModified();`
- L126 _public prototype_ `void DisconnectStylusStateProviderAPI();` — Tells the stylus API to clean up any active tracked windows / contexts
- L128 _public prototype_ `IToolStylusStateProviderAPI* GetStylusStateProviderAPI() const;`
- L130 _public prototype_ `bool HandleClick(FClickContext& InOutContext);`
- L133 _public prototype_ `TSharedPtr<UE::MeshTerrain::FModelingQuickPropertyCustomizations> GetQuickSettingsCustomizations() const;` — Gets the Modeling Quick Settings customizations
- L136 _public prototype_ `TSharedPtr<UE::MeshTerrain::FModelingQuickPropertyCustomizations> GetQuickEditCustomizations() const;` — Gets the Modeling Quick Edit customizations
- L139 _public prototype_ `void RebuildQuickSettingsWidget(UInteractiveTool* Tool = nullptr) const;` — Rebuild the QuickSettings widget to reflect the provided tool. If no tool is provided, uses the currently active tool
- L142 _public prototype_ `void RebuildSectionedDetailsOverlayWidget();` — Rebuild the sectioned DetailsOverlay widget to reflect the provided tool. If none is provided, will use the active tool
- L144 _public function_ `void ShowQuickSettingsOverlayWidget(bool bVisible)`
- L145 _public function_ `void ShowDetailsOverlayWidget(bool bVisible)`
- L146 _public function_ `void ShowNumericalUIOverlayWidget(bool bVisible)`
- L148 _public prototype_ `bool ExperimentalToolsEnabled() const;`
- L153 _private member_ `const static TArray<FName> PaletteNames_Standard;`
- L155 _private member_ `bool bInActiveTool = false;`
- L156 _private member_ `FText ActiveToolName;`
- L157 _private member_ `FText ActiveToolMessage;`
- L158 _private member_ `FStatusBarMessageHandle ActiveToolMessageHandle;`
- L159 _private member_ `const FSlateBrush* ActiveToolIcon = nullptr;`
- L161 _private member_ `TOptional<IToolHostCustomizationAPI::FAcceptCancelButtonOverrideParams> AcceptCancelButtonParams;`
- L162 _private member_ `TOptional<IToolHostCustomizationAPI::FCompleteButtonOverrideParams> CompleteButtonParams;`
- L163 _private member_ `bool bCurrentOverrideButtonsWereClicked = false;`
- L165 _private prototype_ `FReply HandleAcceptCancelClick(bool bAccept);`
- L166 _private prototype_ `FReply HandleCompleteClick();`
- L168 _private member_ `UGeometrySelectionManager* CachedSelectionManager = nullptr;`
- L170 _private member_ `TSharedPtr<SWidget> ToolkitWidget;`
- L171 _private prototype_ `void UpdateActiveToolProperties();`
- L172 _private prototype_ `void InvalidateCachedDetailPanelState(UObject* ChangedObject);`
- L175 _private prototype_ `void RegisterPalettes();` — A utility function to register the tool palettes with the ToolkitBuilder
- L176 _private member_ `FDelegateHandle ActivePaletteChangedHandle;`
- L178 _private member_ `TSharedPtr<SWidget> ToolShutdownViewportOverlayWidget;`
- L179 _private prototype_ `void MakeToolShutdownOverlayWidget();`
- L181 _private member_ `TSharedPtr<UE::ToolWidgets::SDraggableBoxOverlay> SubmodeToolPanelOverlay;`
- L182 _private member_ `TSharedPtr<UE::MeshTerrain::SSubmodeToolPanel> SubmodeToolPanel;`
- L183 _private prototype_ `void MakeSubmodeToolPanelOverlayWidget();`
- L184 _private member_ `TSharedPtr<UE::ToolWidgets::SDraggableBoxOverlay> SubmodePaletteOverlay;`
- L185 _private member_ `TSharedPtr<UE::MeshTerrain::SSubmodePalette> SubmodePalette;`
- L186 _private prototype_ `void MakeSubmodePaletteOverlayWidget();`
- L187 _private member_ `constexpr static float SubmodePalettePadding = 4.0f;`
- L189 _private prototype_ `void InitializeSubmodes();`
- L190 _private prototype_ `TSharedPtr<UE::MeshTerrain::FSubmode> GetDefaultSubmode() const;`
- L191 _private member_ `TMap<FName, TSharedPtr<UE::MeshTerrain::FSubmode>> Submodes;`
- L194 _private prototype_ `void ActivateSubmode(TSharedPtr<UE::MeshTerrain::FSubmode> Submode);` — activates and deactivates submodes
- L195 _private prototype_ `void DeactivateSubmode();`
- L198 _private prototype_ `void MakeQuickSettingsOverlayWidget();` — ModelingQuickSettings widget
- L199 _private member_ `TSharedPtr<SModelingQuickSettingsWidget> QuickSettingsWidget;`
- L200 _private member_ `TSharedPtr<UE::ToolWidgets::SDraggableBoxOverlay> QuickSettingsOverlayWidget;`
- L201 _private member_ `bool bShowQuickSettingsOverlayWidget = false;`
- L204 _private member_ `TSharedPtr<UE::MeshTerrain::FModelingQuickPropertyCustomizations> QuickEditCustomizations;` — represents the Quick Edit (RMB context menu) customizations
- L206 _private prototype_ `TSharedPtr<SWidget> MakeToolShutdownButtons();`
- L208 _private prototype_ `FToolWidget_DragBoxPosition GetDetailsOverlayPosition() const;`
- L209 _private prototype_ `TOptional<FVector2f> GetDetailsOverlaySize() const;`
- L210 _private prototype_ `FToolWidget_DragBoxPosition GetQuickSettingsOverlayPosition() const;`
- L212 _private prototype_ `void MakeDetailsOverlayWidget();`
- L215 _private prototype_ `void MakeFullDetailsOverlayWidget();` — the two different types of details views that can be built
- L216 _private prototype_ `void MakeSectionedDetailsOverlayWidget();`
- L218 _private prototype_ `void UpdateDetailsOverlayWidget() const;`
- L219 _private prototype_ `void UpdateQuickSettingsOverlayWidget() const;`
- L220 _private member_ `TSharedPtr<UE::ToolWidgets::SDraggableBoxOverlay> DetailsOverlayWidget;`
- L221 _private member_ `bool bShowDetailsOverlayWidget = true;`
- L223 _private prototype_ `void MakeGizmoNumericalUIOverlayWidget();`
- L224 _private member_ `TSharedPtr<STransformGizmoNumericalUIOverlay> GizmoNumericalUIOverlayWidget;`
- L225 _private member_ `bool bShowNumericalUIOverlayWidget = true;`
- L228 _private member_ `TSharedPtr<UE::MeshTerrain::SSectionedDetailsViewWidget> SectionedDetailsViewWidget;` — Sectioned Details Overlay Widget
- L229 _private member_ `TSharedPtr<IDetailsView> SectionedDetailsView;`
- L231 _private prototype_ `TSharedRef<SWidget> MakeMenu_ModelingModeConfigSettings();`
- L233 _private member_ `TSharedPtr<STextBlock> ModeWarningArea;`
- L234 _private member_ `TSharedPtr<STextBlock> ModeHeaderArea;`
- L235 _private member_ `TSharedPtr<STextBlock> ToolWarningArea;`
- L236 _private member_ `TSharedPtr<SButton> AcceptButton;`
- L237 _private member_ `TSharedPtr<SButton> CancelButton;`
- L238 _private member_ `TSharedPtr<SButton> CompletedButton;`
- L240 _private member_ `FText ActiveWarning{};`
- L243 _private member_ `TSharedPtr<SWidget> ToolPresetArea;` — Presets
- L244 _private prototype_ `TSharedPtr<SWidget> MakePresetPanel();`
- L245 _private member_ `TSharedPtr<FAssetData> CurrentPreset;`
- L246 _private member_ `FSoftObjectPath CurrentPresetPath;`
- L247 _private member_ `FText CurrentPresetLabel;`
- L248 _private member_ `FToolPresetOption SelectedPresetToEdit;`
- L249 _private member_ `FString NewPresetLabel;`
- L250 _private member_ `FString NewPresetTooltip;`
- L251 _private member_ `FSlateIcon NewPresetIcon;`
- L253 _private member_ `TArray<TSharedPtr<FToolPresetOption>> AvailablePresetsForTool;`
- L254 _private member_ `TSharedPtr<SEditableComboBox<TSharedPtr<FString>>> PresetComboBox;`
- L255 _private member_ `TSharedPtr<FRecentPresetCollectionProvider> RecentPresetCollectionProvider;`
- L257 _private prototype_ `TSharedRef<SWidget> GetPresetCreateButtonContent();`
- L259 _private prototype_ `void CreateNewPresetInCollection(const FString& PresetLabel, FSoftObjectPath CollectionPath, const FString& ToolTip, FSlateIcon Icon);`
- L260 _private prototype_ `void LoadPresetFromCollection(const int32 PresetIndex, FSoftObjectPath CollectionPath);`
- L261 _private prototype_ `void UpdatePresetInCollection(const FToolPresetOption& PresetToEditIn, bool bUpdateStoredPresetValues);`
- L263 _private function_ `FString GetCurrentPresetPath() const`
- L264 _private prototype_ `void HandlePresetAssetChanged(const FAssetData& InAssetData);`
- L265 _private prototype_ `bool HandleFilterPresetAsset(const FAssetData& InAssetData);`
- L267 _private prototype_ `void RebuildPresetListForTool(bool bSettingsOpened);`
- L268 _private prototype_ `TSharedRef<SWidget> MakePresetComboWidget(TSharedPtr<FString> InItem);`
- L269 _private prototype_ `bool IsPresetEnabled() const;`
- L270 _private prototype_ `void ClearPresetComboList();`
- L275 _private prototype_ `void UpdateCategoryButtonLabelVisibility(UObject* Obj, FPropertyChangedEvent& ChangeEvent);` — Updates the category button labels' visibility based off of the current editor preference for it
- L280 _private prototype_ `void UpdateSelectionColors(UObject* Obj, FPropertyChangedEvent& ChangeEvent) const;` — Updates the mesh element selection colors based off of the current editor preference for it
- L282 _private prototype_ `void UpdateOverlayWidgets(UObject* Obj, FPropertyChangedEvent& ChangeEvent) const;`
- L284 _private member_ `TSharedPtr<FEditablePalette> FavoritesPalette;`
- L286 _private member_ `bool bFirstInitializeAfterModeSetup = true;`
- L287 _private member_ `bool bShowActiveSelectionActions = true;`
- L289 _private member_ `TSharedPtr<UE::MeshTerrain::FSubmode> ActiveSubmode;`
- L291 _private member_ `TUniquePtr<UE::MeshTerrain::FStylusInputHandler> StylusInputHandler;`
- L294 _private prototype_ `TArray<UObject*> GetActiveToolProperties() const;` — This is sort of temporary, I imagine there is a better way.
- L295 _private member_ `TFunction<TArray<UObject*>(void)> GetActiveToolPropertiesImpl;`
- L297 _private member_ `TWeakPtr<SSplitter> LevelViewportSplitter;`
- L298 _private member_ `int LevelViewportSplitterSlot = INDEX_NONE;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MeshTerrain` (scope `UE`)
- L15 _namespace_ `namespace ETextCommit`
- L17 _macro_ `#define LOCTEXT_NAMESPACE "MeshTerrainModeToolkit"`
- L29 _namespace_ `namespace UE`
- L29 _namespace_ `namespace ToolWidgets` (scope `UE`)
- L34 _namespace_ `namespace UE`
- L34 _namespace_ `namespace MeshTerrain` (scope `UE`)

### `Plugins/Experimental/MeshTerrainMode/Source/MeshTerrainMode/Private/Submodes/CreateSubmode.h` (Private)


#### class `UE::MeshTerrain::FCreateSubmode`  
`class FCreateSubmode : public FSubmode`  
_L10-23_
- inherits: `FSubmode`
- L13 _public prototype_ `FCreateSubmode(const TSharedPtr<FModeToolkit>& InToolkit);`
- L14 _public prototype_ `virtual ~FCreateSubmode() override = default;`
- L17 _public prototype_ `virtual FName GetName() const override;` — FSubmode
- L18 _public prototype_ `virtual void Activate() override;`
- L19 _public prototype_ `virtual void Deactivate() override;`
- L21 _public prototype_ `static FName GetStaticName();`
- L22 _public prototype_ `static TSharedPtr<FUICommandInfo> GetStaticEnterSubmodeAction();`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace MeshTerrain` (scope `UE`)

### `Plugins/Experimental/MeshTerrainMode/Source/MeshTerrainMode/Private/Submodes/EditSubmode.h` (Private)


#### class `UE::MeshTerrain::FEditSubmode`  
`class FEditSubmode : public FSubmode`  
_L10-23_
- inherits: `FSubmode`
- L13 _public prototype_ `FEditSubmode(const TSharedPtr<FModeToolkit>& InToolkit);`
- L14 _public prototype_ `virtual ~FEditSubmode() override = default;`
- L17 _public prototype_ `virtual FName GetName() const override;` — FSubmode
- L18 _public prototype_ `virtual void Activate() override;`
- L19 _public prototype_ `virtual void Deactivate() override;`
- L21 _public prototype_ `static FName GetStaticName();`
- L22 _public prototype_ `static TSharedPtr<FUICommandInfo> GetStaticEnterSubmodeAction();`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace MeshTerrain` (scope `UE`)

### `Plugins/Experimental/MeshTerrainMode/Source/MeshTerrainMode/Private/Submodes/ModifiersSubmode.h` (Private)


#### class `UE::MeshTerrain::FModifiersSubmode`  
`class FModifiersSubmode : public FSubmode`  
_L12-35_
- inherits: `FSubmode`
- L15 _public prototype_ `FModifiersSubmode(const TSharedPtr<FModeToolkit>& InToolkit);`
- L16 _public prototype_ `virtual ~FModifiersSubmode() override = default;`
- L19 _public prototype_ `virtual FName GetName() const override;` — FSubmode
- L20 _public prototype_ `virtual void Activate() override;`
- L21 _public prototype_ `virtual void Deactivate() override;`
- L23 _public prototype_ `static FName GetStaticName();`
- L24 _public prototype_ `static TSharedPtr<FUICommandInfo> GetStaticEnterSubmodeAction();`
- L26 _public prototype_ `virtual TSharedPtr<SWidget> GetToolPaletteHeader() override;`
- L34 _private member_ `TArray<FPlaceableGroup> ModifierPlaceables;`

#### struct `UE::MeshTerrain::FModifiersSubmode::FPlaceableGroup`  
`struct FPlaceableGroup`  
_L29-33_
- L31 _public member_ `FText Label;`
- L32 _public member_ `TArray<TSharedPtr<FPlaceableItem>> Placeables;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MeshTerrain` (scope `UE`)

### `Plugins/Experimental/MeshTerrainMode/Source/MeshTerrainMode/Private/Submodes/PaintSubmode.h` (Private)


#### class `UE::MeshTerrain::FPaintSubmode`  
`class FPaintSubmode : public FSubmode`  
_L10-24_
- inherits: `FSubmode`
- L13 _public prototype_ `FPaintSubmode(const TSharedPtr<FModeToolkit>& InToolkit);`
- L14 _public prototype_ `virtual ~FPaintSubmode() override = default;`
- L17 _public prototype_ `virtual FName GetName() const override;` — FSubmode
- L18 _public prototype_ `virtual void Activate() override;`
- L19 _public prototype_ `virtual void Deactivate() override;`
- L20 _public prototype_ `virtual void OnToolStarted(UInteractiveTool* Tool) override;`
- L22 _public prototype_ `static FName GetStaticName();`
- L23 _public prototype_ `static TSharedPtr<FUICommandInfo> GetStaticEnterSubmodeAction();`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace MeshTerrain` (scope `UE`)

### `Plugins/Experimental/MeshTerrainMode/Source/MeshTerrainMode/Private/Submodes/SculptSubmode.h` (Private)


#### class `UE::MeshTerrain::FSculptSubmode`  
`class FSculptSubmode : public FSubmode`  
_L10-23_
- inherits: `FSubmode`
- L13 _public prototype_ `FSculptSubmode(const TSharedPtr<FModeToolkit>& InToolkit);`
- L14 _public prototype_ `virtual ~FSculptSubmode() override = default;`
- L17 _public prototype_ `virtual FName GetName() const override;` — FSubmode
- L18 _public prototype_ `virtual void Activate() override;`
- L19 _public prototype_ `virtual void Deactivate() override;`
- L21 _public prototype_ `static FName GetStaticName();`
- L22 _public prototype_ `static TSharedPtr<FUICommandInfo> GetStaticEnterSubmodeAction();`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace MeshTerrain` (scope `UE`)

### `Plugins/Experimental/MeshTerrainMode/Source/MeshTerrainMode/Private/Submodes/ShapesSubmode.h` (Private)


#### class `UE::MeshTerrain::FShapesSubmode`  
`class FShapesSubmode : public FSubmode`  
_L10-23_
- inherits: `FSubmode`
- L13 _public prototype_ `FShapesSubmode(const TSharedPtr<FModeToolkit>& InToolkit);`
- L14 _public prototype_ `virtual ~FShapesSubmode() override = default;`
- L17 _public prototype_ `virtual FName GetName() const override;` — FSubmode
- L18 _public prototype_ `virtual void Activate() override;`
- L19 _public prototype_ `virtual void Deactivate() override;`
- L21 _public prototype_ `static FName GetStaticName();`
- L22 _public prototype_ `static TSharedPtr<FUICommandInfo> GetStaticEnterSubmodeAction();`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace MeshTerrain` (scope `UE`)

### `Plugins/Experimental/MeshTerrainMode/Source/MeshTerrainMode/Private/Submodes/Submode.h` (Private)


#### struct `UE::MeshTerrain::FSubmodeToolPalette`  
`struct FSubmodeToolPalette`  
_L19-26_
- desc: A struct that provides the data for a single tool Palette
- L21 _public prototype_ `FSubmodeToolPalette(const FText& InPaletteLabel, const TArray<TSharedPtr<FUICommandInfo>>& InToolCommands);`
- L22 _public prototype_ `FSubmodeToolPalette(const FSubmodeToolPalette& Other);`
- L24 _public member_ `FText PaletteLabel;`
- L25 _public member_ `TArray<TSharedPtr<FUICommandInfo>> ToolCommands;`

#### class `UE::MeshTerrain::FSubmode`  
`class FSubmode`  
_L28-54_
- L31 _public prototype_ `FSubmode(const TSharedPtr<FModeToolkit>& InToolkit);`
- L32 _public prototype_ `virtual ~FSubmode() = default;`
- L34 _public prototype_ `virtual FName GetName() const = 0;`
- L36 _public function_ `virtual void Activate()`
- L37 _public function_ `virtual void Deactivate()`
- L40 _public function_ `virtual void OnToolStarted(UInteractiveTool* Tool)` — Called when one of a submode's tools has begun or ended
- L41 _public function_ `virtual void OnToolEnded(UInteractiveTool* Tool)`
- L43 _public function_ `virtual bool HandleClick(FClickContext& InOutContext) const`
- L45 _public prototype_ `TSharedPtr<FUICommandInfo> GetEnterSubmodeAction() const;`
- L46 _public function_ `virtual TSharedPtr<SWidget> GetToolPaletteHeader()`
- L47 _public prototype_ `const TArray<FSubmodeToolPalette>& GetToolPalettes() const;`
- L48 _public prototype_ `void AddToolPalette(const FSubmodeToolPalette& Palette);`
- L51 _protected member_ `TWeakPtr<FModeToolkit> Toolkit = nullptr;`
- L52 _protected member_ `TSharedPtr<FUICommandInfo> EnterSubmodeAction = nullptr;`
- L53 _protected member_ `TArray<FSubmodeToolPalette> ToolPalettes;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MeshTerrain` (scope `UE`)

### `Plugins/Experimental/MeshTerrainMode/Source/MeshTerrainMode/Private/Widgets/MeshTerrainModeUtil.h` (Private)


#### enum `UE::MeshTerrain::EQuickPropertyDisplay`  
`enum class EQuickPropertyDisplay : uint8`  
_L15-21_
- desc: Types of Property displays
- L18 _public enumerator_ `WidgetOnly = 0` — A Quick Property's display should only include the widget itself (SSpinbox, SButton, etc.)
- L20 _public enumerator_ `WidgetAndLabel = 1` — A Quick Property's display should include both the widget itself (SSpinbox, SButton, etc.) and the property's label

#### enum `UE::MeshTerrain::EBoolPropertyDisplay`  
`enum class EBoolPropertyDisplay : uint8`  
_L24-30_
- desc: Types of boolean displays
- L27 _public enumerator_ `Button = 0` — A button containing either the property label, or an icon (when a customization is registered)
- L29 _public enumerator_ `CheckBox = 1` — Represented as a standard checkbox

#### struct `UE::MeshTerrain::FPropertyWidget`  
`struct FPropertyWidget`  
_L33-39_
- desc: A struct to track properties and the widgets which represent them
- L35 _public prototype_ `FPropertyWidget(const FText& InPropertyName, const TSharedRef<SWidget>& InWidgetRepresentation);`
- L37 _public member_ `FText PropertyName;`
- L38 _public member_ `TSharedRef<SWidget> WidgetRepresentation;`

#### class `UE::MeshTerrain::FModelingQuickPropertyCustomizations`  
`class FModelingQuickPropertyCustomizations`  
_L44-92_
- desc: FModelingQuickPropertyCustomizations
- L47 _public function_ `FModelingQuickPropertyCustomizations()`
- L50 _public function_ `TMap<UClass*, FGetQuickPropertyCustomization> GetCustomizations()` — return a map containing all the Modeling Quick Property registered customizations
- L53 _public function_ `TMap<FName, TAttribute<const FSlateBrush*>> GetBoolCustomizations()` — return a map containing all the Modeling Quick Property registered boolean customizations
- L56 _public function_ `void RegisterQuickPropertyCustomization(UClass* ToolClass, FGetQuickPropertyCustomization CustomizationDelegate)` — register a customization function to a tool
- L66 _public function_ `void RegisterQuickPropertyBooleanCustomization(const FName BoolPropName, const TAttribute<const FSlateBrush*>& IconOverride)` — register a slate brush override to a boolean property
- L72 _public function_ `void RegisterQuickPropertyStructTypeCustomization(UScriptStruct* StructType, FGetQuickPropertyCustomization CustomizationDelegate)` — register a customization function to a struct type, applied to any tool that exposes a tagged property of that struct type
- L81 _public function_ `TMap<UScriptStruct*, FGetQuickPropertyCustomization> GetStructTypeCustomizations()` — return a map containing all registered struct-type customizations
- L85 _private member_ `TMap<UClass*, FGetQuickPropertyCustomization> Customizations;` — maps tool class to its customization function
- L88 _private member_ `TMap<FName, TAttribute<const FSlateBrush*>> BoolCustomizations;` — maps boolean property names to their intended slate brush overrides
- L91 _private member_ `TMap<UScriptStruct*, FGetQuickPropertyCustomization> StructTypeCustomizations;` — maps struct types to their customization functions, applied regardless of tool class

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MeshTerrain` (scope `UE`)
- L41 _delegate_ `DECLARE_DELEGATE_RetVal_FiveParams(bool, FGetQuickPropertyCustomization, FProperty*, UObject*, TArray<FPropertyWidget>&, UInteractiveTool*, EQuickPropertyDisplay);`
- L41 _prototype_ `DECLARE_DELEGATE_RetVal_FiveParams(bool, FGetQuickPropertyCustomization, FProperty*, UObject*, TArray<FPropertyWidget>&, UInteractiveTool*, EQuickPropertyDisplay);` (scope `UE::MeshTerrain`)
- L96 _prototype_ `void CollectTaggedWidgetsRecursive( FProperty* Property, UObject* PropListOwner, const TCHAR* Tag, UInteractiveTool* ActiveTool, TMap<int, TArray<FPropertyWidget>>& PriorityToWidgets, const TFunction<void(FProperty* Prop, UObject* PropListOwner, TArray<FPropertyWidget>& Widgets)>& HandlePropsFunc, TMap<UClass*, FGetQuickPropertyCustomization> Customizations, const EQuickPropertyDisplay CustomizationDisplayType = EQuickPropertyDisplay::WidgetAndLabel, TMap<UScriptStruct*, FGetQuickPropertyCustomization> StructTypeCustomizations = {});` (scope `UE::MeshTerrain`)
- L109 _prototype_ `void AddSliderWidget(FFloatProperty* FloatProperty, UObject* PropListOwner, TArray<FPropertyWidget>& WidgetsToAdd, const EQuickPropertyDisplay DisplayType = EQuickPropertyDisplay::WidgetAndLabel);` (scope `UE::MeshTerrain`)
- L111 _prototype_ `void AddEnumWidget(FEnumProperty* EnumProperty, UObject* PropListOwner, TArray<FPropertyWidget>& WidgetsToAdd, const EQuickPropertyDisplay DisplayType = EQuickPropertyDisplay::WidgetAndLabel);` (scope `UE::MeshTerrain`)
- L113 _prototype_ `void AddBoolWidget(FBoolProperty* BoolProperty, UObject* PropListOwner, TArray<FPropertyWidget>& WidgetsToAdd, TMap<FName, TAttribute<const FSlateBrush*>> BoolCustomizations, const EQuickPropertyDisplay DisplayType = EQuickPropertyDisplay::WidgetOnly, const EBoolPropertyDisplay BoolDisplayType = EBoolPropertyDisplay::Button);` (scope `UE::MeshTerrain`)
- L116 _prototype_ `TSharedRef<SWidget> CreateQuickEditPropertyRow(const FPropertyWidget& PropertyWidget);` (scope `UE::MeshTerrain`)
- L121 _prototype_ `bool CreateFalloffWidget(FProperty* FalloffProperty, UObject* PropListOwner, TArray<FPropertyWidget>& WidgetsToAdd, UInteractiveTool* Tool, const EQuickPropertyDisplay DisplayType = EQuickPropertyDisplay::WidgetOnly);` (scope `UE::MeshTerrain`) — appends a Widget representing the Falloff property to the provided Array
- L125 _prototype_ `bool CreateBrushSizeToggleWidget(FProperty* Prop, UObject* PropListOwner, TArray<FPropertyWidget>& WidgetsToAdd, UInteractiveTool* Tool, const EQuickPropertyDisplay DisplayType = EQuickPropertyDisplay::WidgetAndLabel, FIsActionButtonVisible PressureButtonVisible = nullptr);` (scope `UE::MeshTerrain`) — appends a Widget representing the BrushSize property to the provided Array - including world/adaptive size toggle
- L130 _prototype_ `bool CreateAlphaWidget(FProperty* AlphaProperty, UObject* PropListOwner, TArray<FPropertyWidget>& WidgetsToAdd, UInteractiveTool* Tool, EQuickPropertyDisplay DisplayType = EQuickPropertyDisplay::WidgetAndLabel);` (scope `UE::MeshTerrain`) — appends a Widget representing the Alpha property to the provided Array
- L134 _prototype_ `bool CreateStrengthWidget(FProperty* StrengthProperty, UObject* PropListOwner, TArray<FPropertyWidget>& WidgetsToAdd, UInteractiveTool* Tool, EQuickPropertyDisplay DisplayType = EQuickPropertyDisplay::WidgetAndLabel, FIsActionButtonVisible PressureButtonVisible = nullptr);` (scope `UE::MeshTerrain`) — appends a Widget representing the Strength property to the provided Array
- L139 _prototype_ `bool CreateBrushSizeWidget(FProperty* Prop, UObject* PropListOwner, TArray<FPropertyWidget>& WidgetsToAdd, UInteractiveTool* Tool, const EQuickPropertyDisplay DisplayType = EQuickPropertyDisplay::WidgetAndLabel, FIsActionButtonVisible PressureButtonVisible = nullptr);` (scope `UE::MeshTerrain`) — appends a Widget representing the BrushSize property to the provided Array - only including slider and pressure sensitivity toggle
- L144 _prototype_ `bool CreateBrushRadiusWidget(FProperty* Prop, UObject* PropListOwner, TArray<FPropertyWidget>& WidgetsToAdd, UInteractiveTool* Tool, const EQuickPropertyDisplay DisplayType = EQuickPropertyDisplay::WidgetAndLabel);` (scope `UE::MeshTerrain`) — appends a Widget representing the BrushRadius property to the provided Array - only including slider
- L150 _prototype_ `bool GetBrushRadiusRangeOverride( const UInteractiveTool* Tool, FString& OutUIMin, FString& OutUIMax, FString& OutClampMin, FString& OutClampMax);` (scope `UE::MeshTerrain`) — Resolves the effective slider range for the BrushRadius property when it is owned by a specific tool. Returns true if any of the output strings have been replaced, false otherwise. An output left empty by the helper means "fall back to the FProperty's declared metadata".
- L160 _prototype_ `void GetSculptBrushSizeRange( const UInteractiveTool* Tool, EBrushToolSizeType SizeType, TInterval<float>& OutUIRange, TInterval<float>& OutValueRange);` (scope `UE::MeshTerrain`) — Resolves the effective slider range for FBrushToolRadius given the active tool and which mode (Adaptive vs World) is currently selected. Returns the defaults from the metadata when no tool-specific override applies; otherwise returns a widened range tailored to the tool.
- L167 _prototype_ `bool CreateEditorGizmoToggleWidget(FProperty* Prop, UObject* PropListOwner, TArray<FPropertyWidget>& WidgetsToAdd, UInteractiveTool* Tool, const EQuickPropertyDisplay DisplayType = EQuickPropertyDisplay::WidgetAndLabel);` (scope `UE::MeshTerrain`) — appends a toggle Widget for the bAllowEditorGizmo property to the provided Array
- L171 _prototype_ `bool CreateShowGizmoToggleWidget(FProperty* Prop, UObject* PropListOwner, TArray<FPropertyWidget>& WidgetsToAdd, UInteractiveTool* Tool, const EQuickPropertyDisplay DisplayType = EQuickPropertyDisplay::WidgetOnly);` (scope `UE::MeshTerrain`) — appends a toggle Widget for the bShowGizmo property to the provided Array
- L177 _prototype_ `bool CreateChannelNameWidget(FProperty* ChannelNameProperty, UObject* PropListOwner, TArray<FPropertyWidget>& WidgetsToAdd, UInteractiveTool* Tool, const EQuickPropertyDisplay DisplayType = EQuickPropertyDisplay::WidgetAndLabel);` (scope `UE::MeshTerrain`) — appends a Widget representing a MeshPartition::FChannelName property to the provided Array. Renders a searchable combo box constrained to GetOptions values, with a toggle to switch to free-text entry, matching the look of FToggleableConstraintNameCustomization.

### `Plugins/Experimental/MeshTerrainMode/Source/MeshTerrainMode/Private/Widgets/ModelingQuickSettingsWidget.h` (Private)


#### class `SModelingQuickSettingsWidget`  
`class SModelingQuickSettingsWidget : public SCompoundWidget`  
_L16-62_
- inherits: `SCompoundWidget`
- desc: SModelingQuickSettingsWidget
- L19 _public function_ `SLATE_BEGIN_ARGS( SModelingQuickSettingsWidget )`
- L20 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<SWidget>, ToolShutdownButtons) SLATE_END_ARGS();`
- L23 _public prototype_ `SModelingQuickSettingsWidget();`
- L25 _public prototype_ `void Construct(const FArguments& InArgs);`
- L28 _public prototype_ `void SetActiveTool(UInteractiveTool* Tool);` — Builds the ModelingQuickSettings widget based on the active tool & its properties
- L31 _public function_ `void SetDetailsView(const TSharedPtr<IDetailsView>& InDetailsView)` — Sets the IDetailsView for the tool (active tool's IDetailsView)
- L34 _public member_ `FOnPropertiesButtonPressed OnPropertiesButtonPressed;` — Handle the button which displays/hides the details view widget
- L35 _public function_ `bool ShowingDetailsView() const`
- L36 _public function_ `void SetShowingDetailsView(const bool bShowDetailsView)`
- L39 _public function_ `TSharedPtr<UE::MeshTerrain::FModelingQuickPropertyCustomizations> GetCustomizations()` — Gets the Modeling Quick Settings customizations for the widget
- L41 _private member_ `TSharedPtr<SHorizontalBox> Container;`
- L42 _private member_ `TSharedPtr<SHorizontalBox> ShutdownContainer;`
- L44 _private prototype_ `FMargin ComputeContentPadding() const;`
- L47 _private prototype_ `void AddToolPropertiesToWidget(const TArray<UObject*>&) const;` — add widgets to the Quick Settings Overlay for given tool properties
- L50 _private prototype_ `TSharedRef<SWidget> CreateDetailPanel() const;` — creates details panel from IDetailsView
- L51 _private member_ `TSharedPtr<IDetailsView> DetailsView = nullptr;`
- L54 _private member_ `TSharedPtr<SWidget> ToolShutdownButtons;` — Widget which contains tool shutdown buttons (accept, cancel, complete)
- L55 _private member_ `bool bCurrentlyShowingDetailsView = false;`
- L58 _private member_ `TSharedPtr<UE::MeshTerrain::FModelingQuickPropertyCustomizations> QuickSettingsCustomizations;` — represents the widget's Modeling Quick Settings Customizations
- L61 _private member_ `UInteractiveTool* ActiveTool = nullptr;` — the currently active tool

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MeshTerrain` (scope `UE`)
- L13 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPropertiesButtonPressed, bool);`
- L13 _prototype_ `DECLARE_DELEGATE_OneParam(FOnPropertiesButtonPressed, bool);`

### `Plugins/Experimental/MeshTerrainMode/Source/MeshTerrainMode/Private/Widgets/SDetailsViewPropertiesSection.h` (Private)


#### class `UE::MeshTerrain::SDetailsViewPropertiesSection`  
`class SDetailsViewPropertiesSection : public SCompoundWidget`  
_L14-47_
- inherits: `SCompoundWidget`
- L17 _public function_ `SLATE_BEGIN_ARGS(SDetailsViewPropertiesSection)`
- L18 _public function_ `SLATE_EVENT(FSimpleDelegate, OnSectionedDetailsPanelRequestRebuild) SLATE_END_ARGS() SDetailsViewPropertiesSection()`
- L23 _public prototype_ `void Construct(const FArguments& InArgs);`
- L26 _public prototype_ `void UpdateActiveSection(const TArray<FDetailsCategory>& NewActiveSection, const TSharedPtr<IDetailsView>& DetailsView);` — Update the currently active section and refresh the widget to reflect it
- L29 _public function_ `TSharedPtr<TSet<FProperty*>> GetActiveProperties() const` — Return a set of properties that should be currently displayed
- L32 _private member_ `TSharedPtr<SVerticalBox> Container;`
- L34 _private member_ `FSimpleDelegate OnSectionedDetailsPanelRequestRebuild;`
- L36 _private member_ `TSharedPtr<TSet<FProperty*>> ActiveProperties;`
- L39 _private prototype_ `TSharedPtr<SWidget> MakeCategoryHeader(const FName CategoryName);` — creates a widget representation of the Category Header
- L42 _private prototype_ `void Rebuild();` — refresh the widget
- L43 _private prototype_ `void Rebuild(TSharedPtr<IDetailsView> DetailsView);`
- L46 _private member_ `TArray<FDetailsCategory> ActiveSection;` — the active section, represented as an array of its categories. Empty if no section is active

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MeshTerrain` (scope `UE`)
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MeshTerrain` (scope `UE`)

### `Plugins/Experimental/MeshTerrainMode/Source/MeshTerrainMode/Private/Widgets/SPlaceableItemEntry.h` (Private)


#### class `UE::MeshTerrain::SPlaceableItemEntry`  
`class SPlaceableItemEntry : public SCompoundWidget`  
_L31-71_
- inherits: `SCompoundWidget`
- desc: A tile representation of the class or the asset.  These are embedded into the views inside of each tab.
- L34 _public function_ `SLATE_BEGIN_ARGS(SPlaceableItemEntry)`
- L35 _public prototype_ `SLATE_ATTRIBUTE(FVector2D, IconSize) SLATE_ATTRIBUTE(FText, HighlightText) SLATE_ATTRIBUTE(FSlateFontInfo, Font) SLATE_EVENT( FOnGetContent, OnGetMenuContent ) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<const FPlaceableItem>& InItem);`
- L44 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L45 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L46 _public prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L48 _public prototype_ `bool IsPressed() const;`
- L50 _public member_ `TSharedPtr<const FPlaceableItem> Item;`
- L55 _private member_ `FOnGetContent OnGetMenuContent;` — Delegate to execute to get the menu content of this button
- L57 _private prototype_ `const FSlateBrush* GetBorder() const;`
- L59 _private member_ `bool bIsPressed = false;`
- L62 _private member_ `const FSlateBrush* NormalImage = nullptr;` — Brush resource that represents a button
- L64 _private member_ `const FSlateBrush* HoverImage = nullptr;` — Brush resource that represents a button when it is hovered
- L66 _private member_ `const FSlateBrush* PressedImage = nullptr;` — Brush resource that represents a button when it is pressed
- L68 _private member_ `FVector2D IconSize = FVector2D(20.0,20.0);`
- L70 _private member_ `TAttribute<FSlateFontInfo> Font;`

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace MeshTerrain` (scope `UE`)

### `Plugins/Experimental/MeshTerrainMode/Source/MeshTerrainMode/Private/Widgets/SSectionedDetailsViewWidget.h` (Private)


#### struct `UE::MeshTerrain::FPropertyDetails`  
`struct FPropertyDetails`  
_L16-20_
- desc: stores information about a property to be represented in the Widget
- L18 _public member_ `FProperty* Property;`
- L19 _public member_ `UObject* PropOwner;`

#### struct `UE::MeshTerrain::FDetailsCategory`  
`struct FDetailsCategory`  
_L23-27_
- desc: stores information about a Category and the Properties that fall under it
- L25 _public member_ `FName CategoryName;`
- L26 _public member_ `TArray<FPropertyDetails> Properties;`

#### struct `UE::MeshTerrain::FDetailsSection`  
`struct FDetailsSection`  
_L30-34_
- desc: stores information about a Section (tab) and the categories to be included within it
- L32 _public member_ `FName SectionName;`
- L33 _public member_ `TArray<FDetailsCategory> Categories;`

#### class `UE::MeshTerrain::SSectionedDetailsViewWidget`  
`class SSectionedDetailsViewWidget : public SCompoundWidget`  
_L37-85_
- inherits: `SCompoundWidget`
- desc: SSectionedDetailsViewWidget
- L40 _public function_ `SLATE_BEGIN_ARGS( SSectionedDetailsViewWidget )`
- L41 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<SWidget>, ToolShutdownButtons) SLATE_ARGUMENT(TSharedPtr<SWidget>, CloseDetailsViewButton) SLATE_END_ARGS();`
- L45 _public function_ `SSectionedDetailsViewWidget()`
- L47 _public prototype_ `void Construct(const FArguments& InArgs);`
- L50 _public prototype_ `void SetActiveTool(UInteractiveTool* Tool, const FSlateBrush* ActiveToolIcon, FText ActiveToolName, bool bDisplayToolShutdownButtons = true);` — Builds the SSectionedDetailsView widget based on the active tool & its properties
- L53 _public function_ `void SetDetailsView(const TSharedPtr<IDetailsView>& InDetailsView)` — Sets the detail view to be used in the PropertiesSection, with properties filtered accordingly
- L57 _public prototype_ `TSharedPtr<TSet<FProperty*>> GetActiveProperties() const;` — Return a set of properties which are 'active' and should be displayed. A property is 'active' if it falls under a category that is currently 'active' (or all categories are active)
- L59 _public member_ `FSimpleDelegate OnSectionedDetailsPanelRequestRebuild;`
- L60 _public member_ `TSharedPtr<SVerticalBox> Container;`
- L64 _private member_ `TSharedPtr<SDetailsViewPropertiesSection> PropertiesSection;` — The section of this widget which contains the categories and their properties
- L66 _private prototype_ `void RebuildPropertiesSection();` — Force a rebuild of this Properties section, when tool or active category changes
- L69 _private member_ `TSharedPtr<SWidget> ToolShutdownButtons;` — Widget which contains tool shutdown buttons (accept, cancel, complete)
- L72 _private member_ `TSharedPtr<SWidget> CloseDetailsViewButton;` — Widget which contains details view 'close' button
- L75 _private member_ `TSharedPtr<IDetailsView> DetailsView = nullptr;` — The details view to be displayed in the properties section, displaying only the active properties
- L78 _private member_ `FName ActiveSection;` — The name of the active sections/tabs to be displayed. 'None' if no tabs are active, 'ALL_SECTIONS' if all
- L81 _private member_ `TArray<FDetailsCategory> AllCategories;` — Keep an array of all the categories, represented as FDetailsCategory, for the case of the 'all sections' tab
- L84 _private member_ `TMap<FName, TArray<FDetailsCategory>> AllSections;` — contains information about all sections/tabs that have been registered for each of the current tool's property sets

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MeshTerrain` (scope `UE`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MeshTerrain` (scope `UE`)
- L88 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMeshTerrain, Warning, All);`
- L88 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMeshTerrain, Warning, All);`

### `Plugins/Experimental/MeshTerrainMode/Source/MeshTerrainMode/Private/Widgets/SSubmodePalette.h` (Private)


#### class `UE::MeshTerrain::SSubmodeToolPanel`  
`class SSubmodeToolPanel : public SCompoundWidget`  
_L19-57_
- inherits: `SCompoundWidget`
- L22 _public function_ `SLATE_BEGIN_ARGS( SSubmodeToolPanel )`
- L23 _public prototype_ `SLATE_ATTRIBUTE(FOptionalSize, Width) SLATE_ATTRIBUTE(FSlateFontInfo, Font) SLATE_ARGUMENT_DEFAULT(EVisibility, LabelVisibility) = EVisibility::Visible;`
- L26 _public prototype_ `SLATE_END_ARGS();`
- L28 _public function_ `SSubmodeToolPanel()`
- L30 _public prototype_ `void Construct(const FArguments& InArgs);`
- L33 _public prototype_ `void SetToolCommandList(const TSharedRef<FUICommandList>& CommandList);` — Assign the Command List for the Tool Container.
- L35 _public prototype_ `void SetActiveSubmode(const TSharedPtr<UE::MeshTerrain::FSubmode>& SubmodePtr);`
- L37 _public prototype_ `EVisibility GetLabelVisibility() const;`
- L38 _public prototype_ `void SetLabelVisibility(EVisibility Vis);`
- L41 _private prototype_ `void UpdateToolsPalette();`
- L43 _private prototype_ `bool IsLabelVisible() const;`
- L45 _private member_ `TAttribute<FOptionalSize> Width = 140.0f;`
- L46 _private member_ `TAttribute<FSlateFontInfo> Font;`
- L48 _private member_ `EVisibility DesiredLabelVisibility = EVisibility::Visible;`
- L49 _private member_ `EVisibility LabelVisibility = EVisibility::Visible;`
- L51 _private member_ `TSharedPtr<FUICommandList> ToolCommandList;`
- L54 _private member_ `TSharedPtr<UE::MeshTerrain::FSubmode> ActiveSubmodePtr = nullptr;` — A pointer to the currently active palette.
- L56 _private member_ `TSharedPtr<SVerticalBox> ToolContainer;`

#### class `UE::MeshTerrain::SSubmodesPanel`  
`class SSubmodesPanel : public SCompoundWidget`  
_L61-102_
- inherits: `SCompoundWidget`
- L64 _public function_ `SLATE_BEGIN_ARGS( SSubmodesPanel )`
- L65 _public prototype_ `SLATE_ARGUMENT_DEFAULT(EVisibility, LabelVisibility) = EVisibility::Visible;`
- L66 _public prototype_ `SLATE_END_ARGS();`
- L68 _public function_ `SSubmodesPanel()`
- L70 _public prototype_ `void Construct(const FArguments& InArgs);`
- L73 _public prototype_ `void AddSubmode(const TSharedPtr<UE::MeshTerrain::FSubmode>& SubmodePtr);` — Register a submode with the palette.
- L76 _public prototype_ `const TSharedPtr<FUICommandList>& GetSubmodePaletteCommandList();` — Gets the pointer to the FUICommandList for the FUICommandInfos which load a tool palette.
- L79 _public prototype_ `void EnterSubmode(const TSharedPtr<UE::MeshTerrain::FSubmode>& SubmodePtr);` — Enter the given Submode.
- L82 _public prototype_ `void CreateSubmodesPalette();` — Creates the palette containing all submodes.
- L85 _public function_ `TSharedPtr<UE::MeshTerrain::FSubmode> GetActiveSubmodePtr()` — Retrieve the active submode pointer
- L88 _public member_ `FSimpleMulticastDelegate OnSubmodePaletteChanged;` — Delegate for when the active submode is changed
- L91 _private member_ `EVisibility LabelVisibility = EVisibility::Visible;`
- L93 _private member_ `TArray<TSharedPtr<UE::MeshTerrain::FSubmode>> SubmodeList;`
- L95 _private member_ `TSharedPtr<FUICommandList> SubmodePaletteCommandList;`
- L98 _private member_ `TSharedPtr<UE::MeshTerrain::FSubmode> ActiveSubmodePtr = nullptr;` — A pointer to the currently active palette.
- L101 _private member_ `TSharedPtr<SVerticalBox> SubmodeContainer;` — Containers for the change submode widgets.

#### class `UE::MeshTerrain::SSubmodePalette`  
`class SSubmodePalette : public SCompoundWidget`  
_L108-145_
- inherits: `SCompoundWidget`
- desc: A class to define a submode palette.
- L111 _public function_ `SLATE_BEGIN_ARGS( SSubmodePalette )`
- L112 _public prototype_ `SLATE_ATTRIBUTE(FOptionalSize, Width) SLATE_ATTRIBUTE(FSlateFontInfo, ToolPanelFont) SLATE_END_ARGS();`
- L116 _public function_ `SSubmodePalette()`
- L118 _public prototype_ `void Construct(const FArguments& InArgs);`
- L121 _public function_ `void AddSubmode(const TSharedPtr<UE::MeshTerrain::FSubmode>& SubmodePtr)` — Register a submode with the palette.
- L124 _public function_ `const TSharedPtr<FUICommandList>& GetSubmodePaletteCommandList()` — Gets the pointer to the FUICommandList for the FUICommandInfos which load a tool palette.
- L127 _public function_ `void SetToolCommandList(const TSharedRef<FUICommandList>& CommandList)` — Assign the Command List for the Tool Container.
- L130 _public function_ `void EnterSubmode(const TSharedPtr<UE::MeshTerrain::FSubmode>& SubmodePtr)` — Enter the given Submode.
- L133 _public function_ `void CreateSubmodesPalette()` — Creates the palette containing all submodes.
- L137 _private member_ `FDelegateHandle ActivePaletteChangedHandle;`
- L139 _private member_ `TAttribute<FOptionalSize> Width = 200.0f;`
- L140 _private member_ `TAttribute<FSlateFontInfo> ToolPanelFont;`
- L143 _private member_ `TSharedPtr<SSubmodesPanel> SubmodeContainer;` — Containers for the change submode widgets and the submodes's tool widgets.
- L144 _private member_ `TSharedPtr<SSubmodeToolPanel> ToolContainer;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MeshTerrain` (scope `UE`)
