# Plugins / AvalancheTextEditor

- module root: `Plugins/VirtualProduction/Avalanche/Source/AvalancheTextEditor`
- headers: 6; symbols: 130
- symbol kinds: class=6, function=12, member=36, prototype=64, struct=11, typedef=1
- PrivateDependencyModuleNames: Avalanche, AvalancheComponentVisualizers, AvalancheEditorCore, AvalancheInteractiveTools, AvalancheLevelViewport, AvalancheText, ComponentVisualizers, Core, CoreUObject, DynamicMaterialEditor, EditorScriptingUtilities, Engine, InputCore, InteractiveToolsFramework, Projects, PropertyEditor, Slate, SlateCore, Text3D, UnrealEd
- PrivateIncludePathModuleNames: AvalancheShapesEditor

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTextEditor/Private/AvaTextActorFactory.h` (Private)


#### class `UAvaTextActorFactory`  
`class UAvaTextActorFactory : public UActorFactory`  
_L9-20_
- reflection: `UCLASS()`
- inherits: `UActorFactory`
- L14 _public prototype_ `UAvaTextActorFactory();`
- L17 _public prototype_ `virtual void PostSpawnActor(UObject* InAsset, AActor* InNewActor) override;`
- L18 _public prototype_ `virtual void PostPlaceAsset(TArrayView<const FTypedElementHandle> InHandle, const FAssetPlacementInfo& InPlacementInfo, const FPlacementOptions& InPlacementOptions) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTextEditor/Private/AvaTextEditorCommands.h` (Private)


#### class `FAvaTextEditorCommands`  
`class FAvaTextEditorCommands : public TCommands<FAvaTextEditorCommands>`  
_L7-17_
- inherits: `TCommands<FAvaTextEditorCommands>`
- L10 _public prototype_ `FAvaTextEditorCommands();`
- L13 _public prototype_ `virtual void RegisterCommands() override;`
- L16 _public member_ `TSharedPtr<FUICommandInfo> Tool_Actor_Text3D;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTextEditor/Private/AvaTextEditorModule.h` (Private)


#### class `FAvaTextEditorModule`  
`class FAvaTextEditorModule : public IModuleInterface`  
_L16-31_
- inherits: `IModuleInterface`
- L21 _public prototype_ `virtual void StartupModule() override;`
- L22 _public prototype_ `virtual void ShutdownModule() override;`
- L26 _private member_ `TArray<TSharedPtr<FComponentVisualizer>> Visualizers;`
- L28 _private prototype_ `void RegisterComponentVisualizers();`
- L30 _private prototype_ `void RegisterDynamicMaterialPropertyGenerator();`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTextEditor/Private/AvaTextEditorStyle.h` (Private)


#### class `FAvaTextEditorStyle`  
`class FAvaTextEditorStyle final : public FSlateStyleSet`  
_L7-18_
- inherits: `FSlateStyleSet`
- L10 _public function_ `static FAvaTextEditorStyle& Get()`
- L16 _public prototype_ `FAvaTextEditorStyle();`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTextEditor/Private/Tool/AvaTextActorTool.h` (Private)


#### class `UAvaTextActorTool`  
`class UAvaTextActorTool : public UAvaInteractiveToolsActorPointToolBase`  
_L9-19_
- reflection: `UCLASS()`
- inherits: `UAvaInteractiveToolsActorPointToolBase`
- L14 _public prototype_ `UAvaTextActorTool();`
- L17 _public prototype_ `virtual void OnRegisterTool(IAvalancheInteractiveToolsModule* InAITModule) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTextEditor/Private/Visualizer/AvaTextVisualizer.h` (Private)


#### struct `HAvaTextMaxTextHeightProxy`  
`struct HAvaTextMaxTextHeightProxy : HAvaHitProxy`  
_L11-18_
- inherits: `HAvaHitProxy`
- L13 _public prototype_ `DECLARE_HIT_PROXY();`
- L15 _public function_ `HAvaTextMaxTextHeightProxy(const UActorComponent* InComponent) : HAvaHitProxy(InComponent)`

#### struct `HAvaTextMaxTextHeightHandleProxy`  
`struct HAvaTextMaxTextHeightHandleProxy : HAvaHitProxy`  
_L20-27_
- inherits: `HAvaHitProxy`
- L22 _public prototype_ `DECLARE_HIT_PROXY();`
- L24 _public function_ `HAvaTextMaxTextHeightHandleProxy(const UActorComponent* InComponent) : HAvaHitProxy(InComponent)`

#### struct `HAvaTextMaxTextWidthProxy`  
`struct HAvaTextMaxTextWidthProxy : HAvaHitProxy`  
_L29-36_
- inherits: `HAvaHitProxy`
- L31 _public prototype_ `DECLARE_HIT_PROXY();`
- L33 _public function_ `HAvaTextMaxTextWidthProxy(const UActorComponent* InComponent) : HAvaHitProxy(InComponent)`

#### struct `HAvaTextMaxTextWidthHandleProxy`  
`struct HAvaTextMaxTextWidthHandleProxy : HAvaHitProxy`  
_L38-45_
- inherits: `HAvaHitProxy`
- L40 _public prototype_ `DECLARE_HIT_PROXY();`
- L42 _public function_ `HAvaTextMaxTextWidthHandleProxy(const UActorComponent* InComponent) : HAvaHitProxy(InComponent)`

#### struct `HAvaTextScaleProportionallyProxy`  
`struct HAvaTextScaleProportionallyProxy : HAvaHitProxy`  
_L47-54_
- inherits: `HAvaHitProxy`
- L49 _public prototype_ `DECLARE_HIT_PROXY();`
- L51 _public function_ `HAvaTextScaleProportionallyProxy(const UActorComponent* InComponent) : HAvaHitProxy(InComponent)`

#### struct `HAvaTextEditGradientProxy`  
`struct HAvaTextEditGradientProxy : HAvaHitProxy`  
_L56-63_
- inherits: `HAvaHitProxy`
- L58 _public prototype_ `DECLARE_HIT_PROXY();`
- L60 _public function_ `HAvaTextEditGradientProxy(const UActorComponent* InComponent) : HAvaHitProxy(InComponent)`

#### struct `HAvaTextGradientLineStartHandleProxy`  
`struct HAvaTextGradientLineStartHandleProxy : HAvaHitProxy`  
_L65-72_
- inherits: `HAvaHitProxy`
- L67 _public prototype_ `DECLARE_HIT_PROXY();`
- L69 _public function_ `HAvaTextGradientLineStartHandleProxy(const UActorComponent* InComponent) : HAvaHitProxy(InComponent)`

#### struct `HAvaTextGradientLineEndHandleProxy`  
`struct HAvaTextGradientLineEndHandleProxy : HAvaHitProxy`  
_L74-81_
- inherits: `HAvaHitProxy`
- L76 _public prototype_ `DECLARE_HIT_PROXY();`
- L78 _public function_ `HAvaTextGradientLineEndHandleProxy(const UActorComponent* InComponent) : HAvaHitProxy(InComponent)`

#### struct `HAvaTextGradientCenterHandleProxy`  
`struct HAvaTextGradientCenterHandleProxy : HAvaHitProxy`  
_L83-90_
- inherits: `HAvaHitProxy`
- L85 _public prototype_ `DECLARE_HIT_PROXY();`
- L87 _public function_ `HAvaTextGradientCenterHandleProxy(const UActorComponent* InComponent) : HAvaHitProxy(InComponent)`

#### struct `HAvaTextGradientSmoothnessHandleProxy`  
`struct HAvaTextGradientSmoothnessHandleProxy : HAvaHitProxy`  
_L92-99_
- inherits: `HAvaHitProxy`
- L94 _public prototype_ `DECLARE_HIT_PROXY();`
- L96 _public function_ `HAvaTextGradientSmoothnessHandleProxy(const UActorComponent* InComponent) : HAvaHitProxy(InComponent)`

#### struct `HAvaTextCharacterKerningHandleProxy`  
`struct HAvaTextCharacterKerningHandleProxy : HAvaHitProxy`  
_L101-111_
- inherits: `HAvaHitProxy`
- L103 _public prototype_ `DECLARE_HIT_PROXY();`
- L105 _public function_ `HAvaTextCharacterKerningHandleProxy(const UActorComponent* InComponent, uint16 InIndex) : HAvaHitProxy(InComponent) , Index(InIndex)`
- L110 _public member_ `uint16 Index;`

#### class `FAvaTextVisualizer`  
`class FAvaTextVisualizer : public FAvaVisualizerBase`  
_L113-246_
- inherits: `FAvaVisualizerBase`
- L116 _public typedef_ `using Super = FAvaVisualizerBase;`
- L118 _public prototype_ `void ResetEditingFlags();`
- L120 _public prototype_ `FAvaTextVisualizer();`
- L123 _public prototype_ `virtual UActorComponent* GetEditedComponent() const override;`
- L124 _public prototype_ `virtual TMap<UObject*, TArray<FProperty*>> GatherEditableProperties(UObject* InObject) const override;`
- L125 _public prototype_ `virtual bool VisProxyHandleClick(FEditorViewportClient* InViewportClient, HComponentVisProxy* VisProxy, const FViewportClick& Click) override;`
- L127 _public prototype_ `virtual bool GetWidgetLocation(const FEditorViewportClient* ViewportClient, FVector& OutLocation) const override;`
- L128 _public prototype_ `virtual bool GetWidgetMode(const FEditorViewportClient* ViewportClient, UE::Widget::EWidgetMode& Mode) const override;`
- L129 _public prototype_ `virtual bool GetWidgetAxisList(const FEditorViewportClient* ViewportClient, UE::Widget::EWidgetMode WidgetMode, EAxisList::Type& AxisList) const override;`
- L131 _public prototype_ `virtual bool GetWidgetAxisListDragOverride(const FEditorViewportClient* ViewportClient, UE::Widget::EWidgetMode WidgetMode, EAxisList::Type& AxisList) const override;`
- L133 _public prototype_ `virtual bool ResetValue(FEditorViewportClient* InViewportClient, HHitProxy* HitProxy) override;`
- L134 _public prototype_ `virtual bool IsEditing() const override;`
- L135 _public prototype_ `virtual void EndEditing() override;`
- L139 _protected member_ `static inline constexpr float TopHeightFraction = 0.6f;`
- L140 _protected member_ `static inline constexpr float BotHeightFraction = 0.17f;`
- L142 _protected member_ `FProperty* HasMaxWidthProperty;`
- L143 _protected member_ `FProperty* HasMaxHeightProperty;`
- L144 _protected member_ `FProperty* MaxWidthProperty;`
- L145 _protected member_ `FProperty* MaxHeightProperty;`
- L146 _protected member_ `FProperty* ScaleProportionallyProperty;`
- L147 _protected member_ `FProperty* CharacterKerningProperty;`
- L149 _protected member_ `TWeakObjectPtr<UText3DComponent> TextComponent;`
- L150 _protected member_ `mutable FBox Bounds;`
- L151 _protected member_ `mutable int32 LineCount;`
- L152 _protected member_ `float LineHeight;`
- L153 _protected member_ `bool bInitialMaxWidthEnabled;`
- L154 _protected member_ `bool bInitialMaxHeightEnabled;`
- L155 _protected member_ `float InitialMaxWidth;`
- L156 _protected member_ `float InitialMaxHeight;`
- L157 _protected member_ `bool bInitialScaleProportionally;`
- L158 _protected member_ `bool bEditingWidth;`
- L159 _protected member_ `bool bEditingHeight;`
- L161 _protected member_ `bool bShowGradientControls;`
- L162 _protected member_ `bool bEditingGradientRotation_StartHandle;`
- L163 _protected member_ `bool bEditingGradientRotation_EndHandle;`
- L164 _protected member_ `bool bEditingGradientOffset;`
- L165 _protected member_ `bool bEditingGradientSmoothness;`
- L166 _protected member_ `bool bEditingKerning;`
- L167 _protected member_ `int32 EditingKerningIndex = INDEX_NONE;`
- L169 _protected member_ `float InitialGradientRotation;`
- L170 _protected member_ `float InitialGradientOffset;`
- L171 _protected member_ `float InitialGradientSmoothness;`
- L172 _protected member_ `float InitialCharacterKerning;`
- L174 _protected member_ `FVector GradientEditBeginLocation_StartHandle;`
- L175 _protected member_ `FVector GradientEditBeginLocation_EndHandle;`
- L176 _protected member_ `FVector GradientEditBeginLocation_Center;`
- L178 _protected prototype_ `virtual void DrawVisualizationNotEditing(const UActorComponent* InComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32& InOutIconIndex) override;`
- L181 _protected prototype_ `virtual void DrawVisualizationEditing(const UActorComponent* InComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32& InOutIconIndex) override;`
- L184 _protected prototype_ `virtual bool HandleInputDeltaInternal(FEditorViewportClient* InViewportClient, FViewport* InViewport, const FVector& InAccumulatedTranslation, const FRotator& InAccumulatedRotation, const FVector& InAccumulatedScale) override;`
- L187 _protected prototype_ `virtual void StoreInitialValues() override;`
- L188 _protected prototype_ `void StoreTextMetrics(const UText3DComponent* InTextComp);`
- L190 _protected prototype_ `virtual void TrackingStopped(FEditorViewportClient* InViewportClient, bool bInDidMove) override;`
- L192 _protected prototype_ `void DrawMaxTextSizeVisualization(const UText3DComponent* InTextComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI) const;`
- L194 _protected prototype_ `static bool DrawGradientCenterHandle(const UText3DComponent* InTextComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, FVector InGradientCenter);`
- L197 _protected prototype_ `static bool DrawGradientSmoothnessHandle(const UText3DComponent* InTextComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, FVector InHandleLocation);`
- L200 _protected prototype_ `void DrawGradientHandles(const UText3DComponent* InText3DComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI) const;`
- L202 _protected prototype_ `FBox GetBoundsMax(const UText3DComponent* InTextComp) const;`
- L204 _protected prototype_ `FVector GetWidthHandleLocation(const UText3DComponent* InTextComp) const;`
- L206 _protected prototype_ `FVector GetHeightHandleLocation(const UText3DComponent* InTextComp) const;`
- L208 _protected prototype_ `void GetTextActorGradientControlsLocations(const UText3DComponent* InText3DComponent, FVector& OutGradientCenterLocation, FVector& OutGradientStartLocation, FVector& OutGradientEndLocation) const;`
- L211 _protected prototype_ `FVector GetGradientEndHandleLocation(const UText3DComponent* InTextComponent) const;`
- L212 _protected prototype_ `FVector GetGradientCenterHandleLocation(const UText3DComponent* InTextComponent) const;`
- L213 _protected prototype_ `FVector GetGradientStartHandleLocation(const UText3DComponent* InTextComponent) const;`
- L214 _protected prototype_ `FVector GetGradientSmoothnessHandleLocation(const UText3DComponent* InText3DComponent) const;`
- L215 _protected prototype_ `FVector GetKerningHandleLocation(const UText3DComponent* InTextComponent, int32 InIndex) const;`
- L217 _protected prototype_ `void DrawMaxTextWidthButton(const UText3DComponent* InTextComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32 InIconIndex, const FLinearColor& InColor) const;`
- L220 _protected prototype_ `void DrawMaxTextHeightButton(const UText3DComponent* InTextComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32 InIconIndex, const FLinearColor& InColor) const;`
- L223 _protected prototype_ `void DrawScaleProportionallyButton(const UText3DComponent* InTextComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32 InIconIndex, const FLinearColor& InColor) const;`
- L226 _protected prototype_ `void DrawEditGradientButton(const UText3DComponent* InTextComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32 InIconIndex, const FLinearColor& InColor) const;`
- L229 _protected prototype_ `void DrawMaxTextWidthHandle(const UText3DComponent* InTextComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, const FLinearColor& InColor) const;`
- L232 _protected prototype_ `void DrawMaxTextHeightHandle(const UText3DComponent* InTextComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, const FLinearColor& InColor) const;`
- L235 _protected prototype_ `void DrawGradientLineStartHandle(const UText3DComponent* InTextComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, const FVector& InLocation, const FLinearColor& InColor) const;`
- L238 _protected prototype_ `void DrawGradientLineEndHandle(const UText3DComponent* InTextComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, const FVector& InLocation, const FLinearColor& InColor) const;`
- L241 _protected prototype_ `void DrawCharacterKerningButton(const UText3DComponent* InTextComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32 InIconIndex, const FLinearColor& InColor);`
- L244 _protected prototype_ `void DrawCharacterKerningHandle(const UText3DComponent* InTextComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, const FVector& InLocation, uint16 InCharacterIndex, const FLinearColor& InColor) const;`
