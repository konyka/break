# Plugins / AvalancheEffectorsEditor

- module root: `Plugins/VirtualProduction/Avalanche/Source/AvalancheEffectorsEditor`
- headers: 9; symbols: 113
- symbol kinds: class=9, function=5, member=39, prototype=55, struct=2, typedef=3
- PrivateDependencyModuleNames: AvalancheComponentVisualizers, AvalancheCore, AvalancheEffectors, AvalancheInteractiveTools, AvalancheOutliner, AvalancheShapes, ClonerEffector, ClonerEffectorEditor, ComponentVisualizers, Core, CoreUObject, Engine, InputCore, InteractiveToolsFramework, Projects, Slate, SlateCore, UnrealEd
- PrivateIncludePathModuleNames: AvalancheShapesEditor

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEffectorsEditor/Private/AvaEffectorsEditorCommands.h` (Private)


#### class `FAvaEffectorsEditorCommands`  
`class FAvaEffectorsEditorCommands : public TCommands<FAvaEffectorsEditorCommands>`  
_L7-18_
- inherits: `TCommands<FAvaEffectorsEditorCommands>`
- L10 _public prototype_ `FAvaEffectorsEditorCommands();`
- L13 _public prototype_ `virtual void RegisterCommands() override;`
- L16 _public member_ `TMap<FName, TSharedPtr<FUICommandInfo>> Tool_Actor_Cloners;`
- L17 _public member_ `TMap<FName, TSharedPtr<FUICommandInfo>> Tool_Actor_Effectors;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEffectorsEditor/Private/AvaEffectorsEditorStyle.h` (Private)


#### class `FAvaEffectorsEditorStyle`  
`class FAvaEffectorsEditorStyle final : public FSlateStyleSet`  
_L7-18_
- inherits: `FSlateStyleSet`
- L10 _public function_ `static FAvaEffectorsEditorStyle& Get()`
- L16 _public prototype_ `FAvaEffectorsEditorStyle();`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEffectorsEditor/Private/AvalancheEffectorsEditorModule.h` (Private)


#### class `FAvalancheEffectorsEditorModule`  
`class FAvalancheEffectorsEditorModule : public IModuleInterface`  
_L13-33_
- inherits: `IModuleInterface`
- L17 _public prototype_ `virtual void StartupModule() override;`
- L18 _public prototype_ `virtual void ShutdownModule() override;`
- L22 _private prototype_ `void PostEngineInit();`
- L24 _private prototype_ `void RegisterComponentVisualizers();`
- L26 _private prototype_ `void RegisterOutlinerItems();`
- L27 _private prototype_ `void UnregisterOutlinerItems();`
- L29 _private member_ `TArray<TSharedPtr<FComponentVisualizer>> Visualizers;`
- L31 _private member_ `FDelegateHandle OutlinerContextClonerDelegateHandle;`
- L32 _private member_ `FDelegateHandle OutlinerContextEffectorDelegateHandle;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEffectorsEditor/Private/Cloner/AvaClonerActorTool.h` (Private)


#### class `UAvaClonerActorTool`  
`class UAvaClonerActorTool : public UAvaInteractiveToolsActorPointToolBase`  
_L9-19_
- reflection: `UCLASS()`
- inherits: `UAvaInteractiveToolsActorPointToolBase`
- L14 _public prototype_ `UAvaClonerActorTool();`
- L17 _public prototype_ `virtual void OnRegisterTool(IAvalancheInteractiveToolsModule* InAITModule) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEffectorsEditor/Private/Cloner/AvaClonerActorVis.h` (Private)


#### struct `HAvaClonerActorSpacingHitProxy`  
`struct HAvaClonerActorSpacingHitProxy : HAvaHitProxy`  
_L11-21_
- inherits: `HAvaHitProxy`
- L13 _public prototype_ `DECLARE_HIT_PROXY();`
- L15 _public function_ `HAvaClonerActorSpacingHitProxy(const UActorComponent* InComponent, ECEClonerAxis InAxis) : HAvaHitProxy(InComponent) , Axis(InAxis)`
- L20 _public member_ `ECEClonerAxis Axis = ECEClonerAxis::Custom;`

#### class `FAvaClonerActorVisualizer`  
`class FAvaClonerActorVisualizer : public FAvaVisualizerBase`  
_L24-64_
- inherits: `FAvaVisualizerBase`
- desc: Custom visualization for cloner actor to handle spacing in various layouts
- L27 _public typedef_ `using Super = FAvaVisualizerBase;`
- L28 _public typedef_ `using MeshType = UCEClonerComponent;`
- L30 _public prototype_ `FAvaClonerActorVisualizer();`
- L33 _public prototype_ `virtual UActorComponent* GetEditedComponent() const override;`
- L34 _public prototype_ `virtual TMap<UObject*, TArray<FProperty*>> GatherEditableProperties(UObject* InObject) const override;`
- L35 _public prototype_ `virtual bool VisProxyHandleClick(FEditorViewportClient* InViewportClient, HComponentVisProxy* InVisProxy, const FViewportClick& InClick) override;`
- L36 _public prototype_ `virtual bool GetWidgetLocation(const FEditorViewportClient* InViewportClient, FVector& OutLocation) const override;`
- L37 _public prototype_ `virtual bool GetWidgetMode(const FEditorViewportClient* InViewportClient, UE::Widget::EWidgetMode& OutMode) const override;`
- L38 _public prototype_ `virtual bool GetWidgetAxisList(const FEditorViewportClient* InViewportClient, UE::Widget::EWidgetMode InWidgetMode, EAxisList::Type& OutAxisList) const override;`
- L39 _public prototype_ `virtual bool GetWidgetAxisListDragOverride(const FEditorViewportClient* InViewportClient, UE::Widget::EWidgetMode InWidgetMode, EAxisList::Type& OutAxisList) const override;`
- L40 _public prototype_ `virtual bool ResetValue(FEditorViewportClient* InViewportClient, HHitProxy* InHitProxy) override;`
- L41 _public prototype_ `virtual bool IsEditing() const override;`
- L42 _public prototype_ `virtual void EndEditing() override;`
- L43 _public prototype_ `virtual void StoreInitialValues() override;`
- L44 _public prototype_ `virtual FBox GetComponentBounds(const UActorComponent* InComponent) const override;`
- L45 _public prototype_ `virtual bool HandleInputDeltaInternal(FEditorViewportClient* InViewportClient, FViewport* InViewport, const FVector& InAccumulatedTranslation, const FRotator& InAccumulatedRotation, const FVector& InAccumulatedScale) override;`
- L46 _public prototype_ `virtual void DrawVisualizationEditing(const UActorComponent* InComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32& InOutIconIndex) override;`
- L47 _public prototype_ `virtual void DrawVisualizationNotEditing(const UActorComponent* InComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32& InOutIconIndex) override;`
- L50 _public function_ `UCEClonerComponent* GetClonerComponent() const`
- L56 _protected prototype_ `FVector GetHandleSpacingLocation(const UCEClonerComponent* InClonerComponent, ECEClonerAxis InAxis) const;`
- L57 _protected prototype_ `void DrawSpacingButton(const UCEClonerComponent* InClonerComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32 InIconIndex, ECEClonerAxis InAxis, FLinearColor InColor) const;`
- L59 _protected member_ `TWeakObjectPtr<UCEClonerComponent> ClonerComponentWeak = nullptr;`
- L61 _protected member_ `FVector InitialSpacing = FVector::ZeroVector;`
- L62 _protected member_ `bool bEditingSpacing = false;`
- L63 _protected member_ `ECEClonerAxis EditingAxis = ECEClonerAxis::X;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEffectorsEditor/Private/Cloner/AvaClonerEditorOutlinerContextMenu.h` (Private)


#### class `FAvaClonerEditorOutlinerContextMenu`  
`class FAvaClonerEditorOutlinerContextMenu`  
_L13-21_
- desc: Context menu actions in outliner related to cloner
- L17 _public prototype_ `static void OnExtendOutlinerContextMenu(UToolMenu* InToolMenu);` — Extend outliner context menu
- L20 _public prototype_ `static void GetContextObjects(const UAvaOutlinerItemsContext* InContext, TSet<UObject*>& OutObjects);` — Gets all pertinent context object in this context

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEffectorsEditor/Private/Effector/AvaEffectorActorTool.h` (Private)


#### class `UAvaEffectorActorTool`  
`class UAvaEffectorActorTool : public UAvaInteractiveToolsActorPointToolBase`  
_L9-19_
- reflection: `UCLASS()`
- inherits: `UAvaInteractiveToolsActorPointToolBase`
- L14 _public prototype_ `UAvaEffectorActorTool();`
- L17 _public prototype_ `virtual void OnRegisterTool(IAvalancheInteractiveToolsModule* InAITModule) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEffectorsEditor/Private/Effector/AvaEffectorActorVis.h` (Private)


#### struct `HAvaEffectorActorZoneHitProxy`  
`struct HAvaEffectorActorZoneHitProxy : HAvaHitProxy`  
_L8-18_
- inherits: `HAvaHitProxy`
- L10 _public prototype_ `DECLARE_HIT_PROXY();`
- L12 _public function_ `HAvaEffectorActorZoneHitProxy(const UActorComponent* InComponent, int32 InHandleType) : HAvaHitProxy(InComponent) , HandleType(InHandleType)`
- L17 _public member_ `int32 HandleType = INDEX_NONE;`

#### class `FAvaEffectorActorVisualizer`  
`class FAvaEffectorActorVisualizer : public FAvaVisualizerBase`  
_L21-95_
- inherits: `FAvaVisualizerBase`
- desc: Custom visualization for effector actor to handle weight zones
- L24 _public typedef_ `using Super = FAvaVisualizerBase;`
- L26 _public prototype_ `FAvaEffectorActorVisualizer();`
- L29 _public prototype_ `virtual UActorComponent* GetEditedComponent() const override;`
- L30 _public prototype_ `virtual TMap<UObject*, TArray<FProperty*>> GatherEditableProperties(UObject* InObject) const override;`
- L31 _public prototype_ `virtual bool VisProxyHandleClick(FEditorViewportClient* InViewportClient, HComponentVisProxy* InVisProxy, const FViewportClick& InClick) override;`
- L32 _public prototype_ `virtual bool GetWidgetLocation(const FEditorViewportClient* InViewportClient, FVector& OutLocation) const override;`
- L33 _public prototype_ `virtual bool GetWidgetMode(const FEditorViewportClient* InViewportClient, UE::Widget::EWidgetMode& OutMode) const override;`
- L34 _public prototype_ `virtual bool GetWidgetAxisList(const FEditorViewportClient* InViewportClient, UE::Widget::EWidgetMode InWidgetMode, EAxisList::Type& OutAxisList) const override;`
- L35 _public prototype_ `virtual bool GetWidgetAxisListDragOverride(const FEditorViewportClient* InViewportClient, UE::Widget::EWidgetMode InWidgetMode, EAxisList::Type& OutAxisList) const override;`
- L36 _public prototype_ `virtual bool ResetValue(FEditorViewportClient* InViewportClient, HHitProxy* InHitProxy) override;`
- L37 _public prototype_ `virtual bool IsEditing() const override;`
- L38 _public prototype_ `virtual void EndEditing() override;`
- L39 _public prototype_ `virtual void StoreInitialValues() override;`
- L40 _public prototype_ `virtual FBox GetComponentBounds(const UActorComponent* InComponent) const override;`
- L41 _public prototype_ `virtual bool HandleInputDeltaInternal(FEditorViewportClient* InViewportClient, FViewport* InViewport, const FVector& InAccumulatedTranslation, const FRotator& InAccumulatedRotation, const FVector& InAccumulatedScale) override;`
- L42 _public prototype_ `virtual void DrawVisualizationEditing(const UActorComponent* InComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32& InOutIconIndex) override;`
- L43 _public prototype_ `virtual void DrawVisualizationNotEditing(const UActorComponent* InComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32& InOutIconIndex) override;`
- L46 _public function_ `UCEEffectorComponent* GetEffectorComponent() const`
- L52 _protected prototype_ `FVector GetHandleZoneLocation(const UCEEffectorComponent* InEffectorComponent, int32 InHandleType) const;`
- L53 _protected prototype_ `void DrawZoneButton(const UCEEffectorComponent* InEffectorComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32 InIconIndex, int32 InHandleType, FLinearColor InColor) const;`
- L55 _protected member_ `FProperty* InnerRadiusProperty;`
- L56 _protected member_ `FProperty* OuterRadiusProperty;`
- L58 _protected member_ `FProperty* InnerExtentProperty;`
- L59 _protected member_ `FProperty* OuterExtentProperty;`
- L61 _protected member_ `FProperty* PlaneSpacingProperty;`
- L63 _protected member_ `FProperty* RadialAngleProperty;`
- L64 _protected member_ `FProperty* RadialMinRadiusProperty;`
- L65 _protected member_ `FProperty* RadialMaxRadiusProperty;`
- L67 _protected member_ `FProperty* TorusRadiusProperty;`
- L68 _protected member_ `FProperty* TorusInnerRadiusProperty;`
- L69 _protected member_ `FProperty* TorusOuterRadiusProperty;`
- L71 _protected member_ `TWeakObjectPtr<UCEEffectorComponent> EffectorComponentWeak = nullptr;`
- L73 _protected member_ `float InitialInnerRadius = 0.f;`
- L74 _protected member_ `float InitialOuterRadius = 0.f;`
- L76 _protected member_ `FVector InitialInnerExtent = FVector(0.f);`
- L77 _protected member_ `FVector InitialOuterExtent = FVector(0.f);`
- L79 _protected member_ `float InitialPlaneSpacing = 0.f;`
- L81 _protected member_ `float InitialRadialAngle = 0.f;`
- L82 _protected member_ `float InitialRadialMinRadius = 0.f;`
- L83 _protected member_ `float InitialRadialMaxRadius = 0.f;`
- L85 _protected member_ `float InitialTorusRadius = 0.f;`
- L86 _protected member_ `float InitialTorusInnerRadius = 0.f;`
- L87 _protected member_ `float InitialTorusOuterRadius = 0.f;`
- L89 _protected member_ `static constexpr int32 HandleTypeInnerZone = 0;`
- L90 _protected member_ `static constexpr int32 HandleTypeOuterZone = 1;`
- L91 _protected member_ `static constexpr int32 HandleTypeRadius = 2;`
- L92 _protected member_ `static constexpr int32 HandleTypeAngle = 3;`
- L94 _protected member_ `int32 EditingHandleType = INDEX_NONE;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEffectorsEditor/Private/Effector/AvaEffectorEditorOutlinerContextMenu.h` (Private)


#### class `FAvaEffectorEditorOutlinerContextMenu`  
`class FAvaEffectorEditorOutlinerContextMenu`  
_L13-21_
- desc: Context menu actions in outliner related to effector
- L17 _public prototype_ `static void OnExtendOutlinerContextMenu(UToolMenu* InToolMenu);` — Extend outliner context menu
- L20 _public prototype_ `static void GetContextObjects(const UAvaOutlinerItemsContext* InContext, TSet<UObject*>& OutObjects);` — Gets all pertinent context object in this context
