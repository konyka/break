# Plugins / AvalancheComponentVisualizers

- module root: `Plugins/VirtualProduction/Avalanche/Source/AvalancheComponentVisualizers`
- headers: 8; symbols: 144
- symbol kinds: class=8, function=27, member=22, namespace=2, prototype=81, struct=2, typedef=1, variable=1
- PrivateDependencyModuleNames: Avalanche, AvalancheViewport, CustomDetailsView, DeveloperSettings, EditorFramework, GeometryFramework, Slate, UnrealEd
- PublicDependencyModuleNames: ComponentVisualizers, Core, CoreUObject, Engine, SlateCore

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheComponentVisualizers/Private/AvaComponentVisualizersEdMode.h` (Private)


#### class `UAvaComponentVisualizersEdMode`  
`class UAvaComponentVisualizersEdMode : public UEdMode, public ILegacyEdModeWidgetInterface`  
_L12-52_
- reflection: `UCLASS()`
- inherits: `UEdMode,ILegacyEdModeWidgetInterface`
- L17 _public member_ `const static FEditorModeID EM_AvaComponentVisualizersEdModeId;`
- L19 _public prototype_ `static TSharedPtr<FAvaVisualizerBase> GetActiveVisualizer();`
- L20 _public prototype_ `static void OnVisualizerActivated(TSharedPtr<FAvaVisualizerBase> InVisualizer);`
- L21 _public prototype_ `static void OnVisualizerDeactivated(TSharedPtr<FAvaVisualizerBase> InVisualizer);`
- L23 _public prototype_ `UAvaComponentVisualizersEdMode();`
- L24 _public prototype_ `virtual ~UAvaComponentVisualizersEdMode() override = default;`
- L27 _public function_ `virtual bool IsCompatibleWith(FEditorModeID OtherModeID) const override`
- L28 _public function_ `virtual bool UsesToolkits() const`
- L29 _public prototype_ `virtual void ModeTick(float DeltaTime) override;`
- L30 _public prototype_ `virtual void Exit() override;`
- L34 _public function_ `virtual bool AllowWidgetMove() override`
- L35 _public function_ `virtual bool CanCycleWidgetMode() const override`
- L36 _public function_ `virtual bool ShowModeWidgets() const override`
- L37 _public prototype_ `virtual EAxisList::Type GetWidgetAxisToDraw(UE::Widget::EWidgetMode InWidgetMode) const override;`
- L38 _public prototype_ `virtual FVector GetWidgetLocation() const override;`
- L39 _public function_ `virtual bool ShouldDrawWidget() const override`
- L40 _public function_ `virtual bool UsesTransformWidget() const override`
- L41 _public prototype_ `virtual bool UsesTransformWidget(UE::Widget::EWidgetMode CheckMode) const override;`
- L42 _public prototype_ `virtual FVector GetWidgetNormalFromCurrentAxis(void* InData) override;`
- L43 _public prototype_ `virtual void SetCurrentWidgetAxis(EAxisList::Type InAxis) override;`
- L44 _public prototype_ `virtual EAxisList::Type GetCurrentWidgetAxis() const override;`
- L45 _public prototype_ `virtual bool UsesPropertyWidgets() const override;`
- L46 _public prototype_ `virtual bool GetCustomDrawingCoordinateSystem(FMatrix& OutMatrix, void* InData) override;`
- L47 _public prototype_ `virtual bool GetCustomInputCoordinateSystem(FMatrix& OutMatrix, void* InData) override;`
- L51 _protected member_ `static TWeakPtr<FAvaVisualizerBase> ActiveVisualizerWeak;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheComponentVisualizers/Private/AvaComponentVisualizersSettings.h` (Private)


#### class `UAvaComponentVisualizersSettings`  
`class UAvaComponentVisualizersSettings : public UDeveloperSettings, public IAvaComponentVisualizersSettings`  
_L10-37_
- reflection: `UCLASS(Config = EditorPerProjectUserSettings, meta = (DisplayName = "Visualizers"))`
- inherits: `UDeveloperSettings,IAvaComponentVisualizersSettings`
- L15 _public prototype_ `static UAvaComponentVisualizersSettings* Get();`
- L17 _public prototype_ `UAvaComponentVisualizersSettings();`
- L24 _public member_ `float SpriteSize;` — `UPROPERTY(Config, EditAnywhere, Category = "Motion Design")` — The ideal size for sprites when at the default camera range. Beyond which they will start to become smaller. This is a guide size and icons may be intentionally bigger or smaller based on their role.
- L27 _public member_ `TMap<FName, TSoftObjectPtr<UTexture2D>> VisualizerSprites;` — `UPROPERTY(Config, EditAnywhere, Category = "Motion Design")`
- L30 _public prototype_ `virtual float GetSpriteSize() const override;`
- L31 _public prototype_ `virtual void SetSpriteSize(float InSpriteSize) override;`
- L32 _public prototype_ `virtual UTexture2D* GetVisualizerSprite(FName InName) const override;`
- L33 _public prototype_ `virtual void SetVisualizerSprite(FName InName, UTexture2D* InTexture) override;`
- L34 _public prototype_ `virtual void SetDefaultVisualizerSprite(FName InName, UTexture2D* InTexture) override;`
- L35 _public prototype_ `virtual void SaveSettings() override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheComponentVisualizers/Private/AvaComponentVisualizersViewportOverlay.h` (Private)


#### class `FAvaComponentVisualizersViewportOverlay`  
`class FAvaComponentVisualizersViewportOverlay : public IAvaComponentVisualizersViewportOverlay`  
_L10-23_
- inherits: `IAvaComponentVisualizersViewportOverlay`
- L13 _public prototype_ `virtual ~FAvaComponentVisualizersViewportOverlay() override = default;`
- L16 _public prototype_ `virtual void AddWidget(const TArray<TSharedPtr<IAvaViewportClient>>& InAvaViewportClients, const TArray<UObject*>& InSelectedObjects) override;`
- L17 _public prototype_ `virtual void RemoveWidget(const TArray<TSharedPtr<IAvaViewportClient>>& InAvaViewportClients) override;`
- L18 _public prototype_ `virtual bool IsWidgetActive() const override;`
- L22 _protected member_ `TSharedPtr<SWidget> OverlayWidget;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheComponentVisualizers/Private/AvalancheComponentVisualizersModule.h` (Private)


#### class `FAvalancheComponentVisualizersModule`  
`class FAvalancheComponentVisualizersModule : public IAvalancheComponentVisualizersModule`  
_L7-16_
- inherits: `IAvalancheComponentVisualizersModule`
- L11 _public prototype_ `virtual IAvaComponentVisualizersSettings* GetSettings() const override;`
- L12 _public prototype_ `virtual void RegisterComponentVisualizer(FName InComponentClassName, TSharedRef<FComponentVisualizer> InVisualizer) const override;`
- L13 _public prototype_ `virtual bool IsAvalancheVisualizer(TSharedRef<FComponentVisualizer> InVisualizer) const override;`
- L14 _public prototype_ `virtual IAvaComponentVisualizersViewportOverlay& GetViewportOverlay() const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheComponentVisualizers/Public/AvaVisBase.h` (Public)


#### struct `HAvaHitProxy`  
`struct HAvaHitProxy : HComponentVisProxy`  
_L8-15_
- inherits: `HComponentVisProxy`
- L10 _public prototype_ `DECLARE_HIT_PROXY();`
- L12 _public function_ `HAvaHitProxy(const UActorComponent* InComponent) : HComponentVisProxy(InComponent, HPP_Wireframe)`

#### struct `HAvaDirectHitProxy`  
`struct HAvaDirectHitProxy : HAvaHitProxy`  
_L17-24_
- inherits: `HAvaHitProxy`
- L19 _public prototype_ `DECLARE_HIT_PROXY();`
- L21 _public function_ `HAvaDirectHitProxy(const UActorComponent* InComponent) : HAvaHitProxy(InComponent)`

#### class `FAvaVisualizerBase`  
`class FAvaVisualizerBase : public FComponentVisualizer`  
_L60-196_
- inherits: `FComponentVisualizer`
- desc: Select shape: - DrawVisualization Select HitProxy: - VisProxyHandleClick |- EndEditing |   |- EndTransaction |   \- Update ST that no Vis is active. \- StartEditing |- Store component & HP settings \- Update ST that we are active. Mouse down on widget: - Viewport: TrackingStarted (not used) Drag mouse - HandleInputDelta |- (Not tracking) |   \- StartTracking |       |- TrackingStarted |       \- StoreInitialValues \- HandleInputDeltaInternal Release mouse - Viewport: TrackingStopped \- TrackingStopped \- EndTransaction (see above)
- L65 _public typedef_ `using Super = FComponentVisualizer;`
- L67 _public function_ `FEditorViewportClient* GetLastUsedViewportClient() const`
- L70 _public prototype_ `virtual TMap<UObject*, TArray<FProperty*>> GatherEditableProperties(UObject* InObject) const = 0;` — Returns a list of objects and the properties being edited on that object.
- L72 _public function_ `virtual const USceneComponent* GetEditedSceneComponent() const`
- L73 _public prototype_ `virtual const USceneComponent* GetEditedSceneComponent(const UActorComponent* InComponent) const;`
- L75 _public function_ `virtual bool GetWidgetMode(const FEditorViewportClient* InViewportClient, UE::Widget::EWidgetMode& OutMode) const`
- L77 _public function_ `virtual bool GetWidgetAxisList(const FEditorViewportClient* InViewportClient, UE::Widget::EWidgetMode InWidgetMode, EAxisList::Type& OutAxisList) const`
- L80 _public prototype_ `virtual void StartEditing(FEditorViewportClient* InViewportClient, UActorComponent* InEditedComponent);`
- L82 _public function_ `virtual bool IsEditing() const`
- L85 _public function_ `virtual bool GetWidgetAxisListDragOverride(const FEditorViewportClient* InViewportClient, UE::Widget::EWidgetMode InWidgetMode, EAxisList::Type& OutAxisList) const` — Used to override the axis used to actually calculate drag.
- L88 _public function_ `virtual bool ResetValue(FEditorViewportClient* InViewportClient, HHitProxy* InHitProxy)`
- L90 _public function_ `bool IsTracking() const`
- L92 _public function_ `TSharedPtr<FAvaSnapOperation> GetSnapOperation() const`
- L95 _public prototype_ `virtual void DrawVisualization(const UActorComponent* InComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI) override;`
- L96 _public function_ `virtual void DrawVisualizationHUD(const UActorComponent* InComponent, const FViewport* InViewport, const FSceneView* InView, FCanvas* InCanvas) override`
- L97 _public prototype_ `virtual bool GetCustomInputCoordinateSystem(const FEditorViewportClient* InViewportClient, FMatrix& OutMatrix) const override;`
- L98 _public prototype_ `virtual bool HandleInputDelta(FEditorViewportClient* InViewportClient, FViewport* InViewport, FVector& InDeltaTranslate, FRotator& InDeltaRotate, FVector& InDeltaScale) override;`
- L100 _public prototype_ `virtual bool HandleModifiedClick(FEditorViewportClient* InViewportClient, HHitProxy* InHitProxy, const FViewportClick& InClick) override;`
- L102 _public prototype_ `virtual void EndEditing() override;` — Editing -> We have a hitproxy selected
- L104 _public prototype_ `virtual void TrackingStarted(FEditorViewportClient* InViewportClient) override;` — Tracking -> We are actively dragging a widget
- L105 _public prototype_ `virtual void TrackingStopped(FEditorViewportClient* InViewportClient, bool bInDidMove) override;`
- L110 _protected prototype_ `static void NotifyPropertyModified(UObject* InObject, FProperty* InProperty, EPropertyChangeType::Type InPropertyChangeType = EPropertyChangeType::Unspecified, FProperty* InMemberProperty = nullptr);` — Notify that a component property has been modified
- L114 _protected prototype_ `static void NotifyPropertiesModified(UObject* InObject, const TArray<FProperty*>& InProperties, EPropertyChangeType::Type InPropertyChangeType = EPropertyChangeType::Unspecified, FProperty* InMemberProperty = nullptr);` — Notify that many component properties have been modified
- L118 _protected prototype_ `static void NotifyPropertyChainModified(UObject* InObject, FProperty* InProperty, EPropertyChangeType::Type InPropertyChangeType, int32 InContainerIdx, TArray<FProperty*> InMemberChainProperties);` — Notify that a component property has been modified inside a container
- L121 _protected member_ `static FLinearColor Inactive;`
- L122 _protected member_ `static FLinearColor Active;`
- L123 _protected member_ `static FLinearColor ActiveAltMode;`
- L124 _protected member_ `static FLinearColor Enabled;`
- L125 _protected member_ `static FLinearColor Disabled;`
- L127 _protected prototype_ `static float GetIconSizeScale(const FSceneView* InView, const FVector& InWorldPosition);`
- L128 _protected prototype_ `static const FLinearColor& GetIconColor(bool bInActive, bool bInAltMode = false);`
- L131 _protected member_ `FEditorViewportClient* LastUsedViewportClient = nullptr;` — Last used viewport client
- L132 _protected member_ `bool bCVarAutoSelectComponent = true;`
- L135 _protected member_ `bool bHasInitialWidgetLocation;` — Delta sums
- L136 _protected member_ `FVector InitialWidgetLocation;`
- L137 _protected member_ `FVector AccumulatedTranslation;`
- L138 _protected member_ `FRotator AccumulatedRotation;`
- L139 _protected member_ `FVector AccumulatedScale;`
- L142 _protected member_ `FVector IconStartPosition;` — Top icons
- L145 _protected member_ `int32 TransactionIdx;` — Tracking info
- L146 _protected member_ `bool bTracking;`
- L147 _protected member_ `bool bHasBeenModified;`
- L150 _protected member_ `TSharedPtr<FAvaSnapOperation> SnapOperation;` — Snapping stuff
- L152 _protected prototype_ `FAvaVisualizerBase() = default;`
- L153 _protected prototype_ `virtual ~FAvaVisualizerBase() override = default;`
- L155 _protected function_ `virtual void DrawVisualizationNotEditing(const UActorComponent* InComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32& InOutIconIndex)`
- L158 _protected function_ `virtual void DrawVisualizationEditing(const UActorComponent* InComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32& InOutIconIndex)`
- L161 _protected prototype_ `void StartTransaction();`
- L162 _protected prototype_ `void EndTransaction();`
- L163 _protected prototype_ `virtual void StoreInitialValues();`
- L165 _protected prototype_ `virtual FBox GetComponentBounds(const UActorComponent* InComponent) const;`
- L166 _protected prototype_ `virtual FTransform GetComponentTransform(const UActorComponent* InComponent) const;`
- L170 _protected prototype_ `bool CalcIconLocation(const USceneComponent* InComponent, const FSceneView* InView);` — Calculates the location of the first top-of-shape icon in world space Uses the shape's bounding box to do this.
- L173 _protected prototype_ `void GetIconMetrics(const FSceneView* InView, int32 InIconIndex, FVector& InOutPosition, float& InOutSize) const;` — Gets the position and size of icons based on the above ^
- L175 _protected prototype_ `UE::Widget::EWidgetMode GetViewportWidgetMode(FEditorViewportClient* InViewportClient) const;`
- L176 _protected prototype_ `EAxisList::Type GetViewportWidgetAxisList(FEditorViewportClient* InViewportClient) const;`
- L179 _protected prototype_ `FVector GetLocalVector(FEditorViewportClient* InViewport, const FVector& InVector) const;` — Converts vectors from world space to local space
- L181 _protected function_ `virtual bool HandleInputDeltaInternal(FEditorViewportClient* InViewportClient, FViewport* InViewport, const FVector& InAccumulatedTranslation, const FRotator& InAccumulatedRotation, const FVector& InAccumulatedScale)`
- L184 _protected prototype_ `bool IsMouseOverComponent(const UActorComponent* InComponent, const FSceneView* InView) const;`
- L185 _protected prototype_ `bool ShouldDrawExtraHandles(const UActorComponent* InComponent, const FSceneView* InView) const;`
- L187 _protected function_ `virtual void AddSnapDataBinding()`
- L189 _protected function_ `virtual void GenerateContextSensitiveSnapPoints()`
- L191 _protected prototype_ `virtual void TrackingStartedInternal(FEditorViewportClient* InViewportClient);`
- L192 _protected prototype_ `virtual void TrackingStoppedInternal(FEditorViewportClient* InViewportClient);`
- L194 _protected prototype_ `void ModifyProperty(UObject* InObject, FProperty* InProperty, EPropertyChangeType::Type InPropertyChangeType, TFunctionRef<void()> InFunction);`
- L195 _protected prototype_ `void ModifyProperty(UObject* InObject, FName InPropertyName, EPropertyChangeType::Type InPropertyChangeType, TFunctionRef<void()> InFunction);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheComponentVisualizers/Public/IAvaComponentVisualizersSettings.h` (Public)


#### class `IAvaComponentVisualizersSettings`  
`class IAvaComponentVisualizersSettings`  
_L9-24_
- L12 _public prototype_ `virtual float GetSpriteSize() const = 0;`
- L14 _public prototype_ `virtual void SetSpriteSize(float InSpriteSize) = 0;`
- L16 _public prototype_ `virtual UTexture2D* GetVisualizerSprite(FName InName) const = 0;`
- L18 _public prototype_ `virtual void SetVisualizerSprite(FName InName, UTexture2D* InTexture) = 0;`
- L21 _public prototype_ `virtual void SetDefaultVisualizerSprite(FName InName, UTexture2D* InTexture) = 0;` — Same as above, but doesn't replace an existing value
- L23 _public prototype_ `virtual void SaveSettings() = 0;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheComponentVisualizers/Public/IAvaComponentVisualizersViewportOverlay.h` (Public)


#### class `IAvaComponentVisualizersViewportOverlay`  
`class IAvaComponentVisualizersViewportOverlay`  
_L11-21_
- L14 _public prototype_ `virtual ~IAvaComponentVisualizersViewportOverlay() = default;`
- L16 _public prototype_ `virtual void AddWidget(const TArray<TSharedPtr<IAvaViewportClient>>& InAvaViewportClients, const TArray<UObject*>& InSelectedObjects) = 0;`
- L18 _public prototype_ `virtual void RemoveWidget(const TArray<TSharedPtr<IAvaViewportClient>>& InAvaViewportClients) = 0;`
- L20 _public prototype_ `virtual bool IsWidgetActive() const = 0;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheComponentVisualizers/Public/IAvalancheComponentVisualizersModule.h` (Public)


#### class `IAvalancheComponentVisualizersModule`  
`class IAvalancheComponentVisualizersModule : public IModuleInterface`  
_L19-62_
- inherits: `IModuleInterface`
- L22 _public function_ `static IAvalancheComponentVisualizersModule& Get()`
- L27 _public function_ `static IAvalancheComponentVisualizersModule* GetIfLoaded()`
- L34 _public function_ `template<typename InComponentClass, typename InVisualizerClass, typename InStorageType = TArray<TSharedPtr<FComponentVisualizer>>> static TSharedPtr<FComponentVisualizer> RegisterComponentVisualizer(InStorageType* Storage = nullptr)` — Could also use a TSet or custom storage class.
- L55 _public prototype_ `virtual IAvaComponentVisualizersSettings* GetSettings() const = 0;`
- L57 _public prototype_ `virtual void RegisterComponentVisualizer(FName InComponentClassName, TSharedRef<FComponentVisualizer> InVisualizer) const = 0;`
- L59 _public prototype_ `virtual bool IsAvalancheVisualizer(TSharedRef<FComponentVisualizer> InVisualizer) const = 0;`
- L61 _public prototype_ `virtual IAvaComponentVisualizersViewportOverlay& GetViewportOverlay() const = 0;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace AvaComponentVisualizers` (scope `UE`)
- L16 _variable_ `const FName ModuleName = TEXT("Ava` (scope `UE::AvaComponentVisualizers`)
