# Editor / EditorFramework

- module root: `Source/Editor/EditorFramework`
- headers: 21; symbols: 476
- symbol kinds: class=27, delegate=9, enum=7, enumerator=32, externvar=11, function=84, macro=6, member=99, namespace=5, prototype=181, struct=11, typedef=4
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, Slate, SlateCore, ToolMenus
- PublicDependencyModuleNames: EditorSubsystem, InteractiveToolsFramework, TypedElementFramework, TypedElementRuntime

### `Source/Editor/EditorFramework/Public/EditorFrameworkModule.h` (Public)


#### class `FEditorFrameworkModule`  
`class FEditorFrameworkModule : public IModuleInterface`  
_L7-12_
- inherits: `IModuleInterface`
- L10 _public prototype_ `virtual void StartupModule() override;`
- L11 _public prototype_ `virtual void ShutdownModule() override;`

### `Source/Editor/EditorFramework/Public/EditorModes.h` (Public)


#### class `FDynamicColoredMaterialRenderProxy`  
`class FDynamicColoredMaterialRenderProxy : public FDynamicPrimitiveResource, public FColoredMaterialRenderProxy`  
_L53-71_
- inherits: `FDynamicPrimitiveResource,FColoredMaterialRenderProxy`
- desc: Material proxy wrapper that can be created on the game thread and passed on to the render thread.
- L57 _public function_ `FDynamicColoredMaterialRenderProxy(const FMaterialRenderProxy* InParent,const FLinearColor& InColor) : FColoredMaterialRenderProxy(InParent,InColor)` — Initialization constructor.
- L61 _public prototype_ `virtual ~FDynamicColoredMaterialRenderProxy() = default;`
- L64 _public function_ `virtual void InitPrimitiveResource(FRHICommandListBase& RHICmdList)` — FDynamicPrimitiveResource interface.
- L67 _public function_ `virtual void ReleasePrimitiveResource()`

#### Free symbols / members of external scopes

- L13 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogEditorModes, Log, All);`
- L16 _namespace_ `namespace FBuiltinEditorModes`
- L19 _externvar_ `extern const FEditorModeID EM_None;` (scope `FBuiltinEditorModes`) — Gameplay, editor disabled.
- L22 _externvar_ `extern const FEditorModeID EM_Default;` (scope `FBuiltinEditorModes`) — Camera movement, actor placement.
- L25 _externvar_ `extern const FEditorModeID EM_Placement;` (scope `FBuiltinEditorModes`) — Placement mode
- L28 _externvar_ `extern const FEditorModeID EM_MeshPaint;` (scope `FBuiltinEditorModes`) — Mesh paint tool
- L31 _externvar_ `extern const FEditorModeID EM_Landscape;` (scope `FBuiltinEditorModes`) — Landscape editing
- L34 _externvar_ `extern const FEditorModeID EM_Foliage;` (scope `FBuiltinEditorModes`) — Foliage painting
- L37 _externvar_ `extern const FEditorModeID EM_Level;` (scope `FBuiltinEditorModes`) — Level editing mode
- L40 _externvar_ `extern const FEditorModeID EM_StreamingLevel;` (scope `FBuiltinEditorModes`) — Streaming level editing mode
- L43 _externvar_ `extern const FEditorModeID EM_Physics;` (scope `FBuiltinEditorModes`) — Physics manipulation mode ( available only when simulating in viewport )
- L46 _externvar_ `extern const FEditorModeID EM_ActorPicker;` (scope `FBuiltinEditorModes`) — Actor picker mode, used to interactively pick actors in the viewport
- L49 _externvar_ `extern const FEditorModeID EM_SceneDepthPicker;` (scope `FBuiltinEditorModes`) — Actor picker mode, used to interactively pick actors in the viewport

### `Source/Editor/EditorFramework/Public/EditorViewportLayout.h` (Public)


#### class `IEditorViewportLayoutEntity`  
`class IEditorViewportLayoutEntity : public TSharedFromThis<IEditorViewportLayoutEntity>`  
_L15-38_
- inherits: `TSharedFromThis<IEditorViewportLayoutEntity>`
- L19 _public prototype_ `virtual ~IEditorViewportLayoutEntity() = default;` — Virtual destruction
- L22 _public prototype_ `virtual TSharedRef<SWidget> AsWidget() const = 0;` — Return a widget that is represents this entity
- L25 _public prototype_ `virtual void SetKeyboardFocus() = 0;` — Set keyboard focus to this viewport entity
- L28 _public prototype_ `virtual void OnLayoutDestroyed() = 0;` — Called when the parent layout is being destroyed
- L31 _public prototype_ `virtual void SaveConfig(const FString& ConfigSection) = 0;` — Called to save this item's settings in the specified config section
- L34 _public prototype_ `virtual FName GetType() const = 0;` — Get the type of this viewport as a name
- L37 _public prototype_ `virtual void TakeHighResScreenShot() const = 0;` — Take a high res screen shot of viewport entity

#### class `FEditorViewportLayout`  
`class FEditorViewportLayout`  
_L40-62_
- L44 _public prototype_ `virtual ~FEditorViewportLayout() = default;` — Virtual destruction
- L46 _public function_ `virtual bool IsVisible() const`
- L51 _public function_ `const TMap< FName, TSharedPtr<IEditorViewportLayoutEntity> >& GetViewports() const` — @return All the viewports in this configuration
- L53 _public prototype_ `virtual void FactoryPaneConfigurationFromTypeName(const FName& InLayoutConfigTypeName) = 0;`
- L54 _public prototype_ `virtual const FName GetActivePaneConfigurationTypeName() const = 0;`
- L56 _public function_ `virtual void SaveConfig(const FString& LayoutSring) const`
- L57 _public function_ `virtual void LoadConfig(const FString& LayoutString)`
- L61 _protected member_ `TMap< FName, TSharedPtr< IEditorViewportLayoutEntity > > Viewports;` — List of all of the viewports in this layout, keyed on their config key

### `Source/Editor/EditorFramework/Public/Elements/Framework/TypedElementAssetEditorToolkitHostMixin.h` (Public)


#### class `FTypedElementAssetEditorToolkitHostMixin`  
`class FTypedElementAssetEditorToolkitHostMixin`  
_L12-42_
- desc: Mixin for asset editor customizations that provides access to the toolkit host of the asset editor.
- L18 _public function_ `const IToolkitHost* GetToolkitHost() const` — Get the toolkit host associated with our asset editor.
- L26 _public function_ `IToolkitHost* GetMutableToolkitHost()` — Get the toolkit host associated with our asset editor.
- L34 _public function_ `void SetToolkitHost(IToolkitHost* InToolkitHost)` — Set the toolkit host associated with our asset editor.
- L41 _private member_ `IToolkitHost* ToolkitHost = nullptr;` — The toolkit host associated with our asset editor.

### `Source/Editor/EditorFramework/Public/Elements/Framework/TypedElementViewportInteraction.h` (Public)


#### enum `ETypedElementViewportInteractionGizmoManipulationType`  
`enum class ETypedElementViewportInteractionGizmoManipulationType : uint8`  
_L28-34_
- L31 _public enumerator_ `Drag` — The gizmo manipulation resulted in a drag operation
- L33 _public enumerator_ `Click` — The gizmo manipulation resulted in a click operation

#### class `FTypedElementViewportInteractionCustomization`  
`class FTypedElementViewportInteractionCustomization : public FTypedElementAssetEditorToolkitHostMixin`  
_L39-54_
- inherits: `FTypedElementAssetEditorToolkitHostMixin`
- desc: Customization used to allow asset editors (such as the level editor) to override the base behavior of viewport interaction.
- L42 _public prototype_ `virtual ~FTypedElementViewportInteractionCustomization() = default;`
- L45 _public prototype_ `virtual bool GetGizmoPivotLocation(const TTypedElement<ITypedElementWorldInterface>& InElementWorldHandle, const UE::Widget::EWidgetMode InWidgetMode, FVector& OutPivotLocation);`
- L46 _public prototype_ `virtual void PreGizmoManipulationStarted(TArrayView<const FTypedElementHandle> InElementHandles, const UE::Widget::EWidgetMode InWidgetMode);`
- L47 _public prototype_ `virtual void GizmoManipulationStarted(const TTypedElement<ITypedElementWorldInterface>& InElementWorldHandle, const UE::Widget::EWidgetMode InWidgetMode);`
- L48 _public prototype_ `virtual void GizmoManipulationDeltaUpdate(const TTypedElement<ITypedElementWorldInterface>& InElementWorldHandle, const UE::Widget::EWidgetMode InWidgetMode, const EAxisList::Type InDragAxis, const FInputDeviceState& InInputState, const FTransform& InDeltaTransform, const FVector& InPivotLocation);`
- L49 _public prototype_ `virtual void GizmoManipulationStopped(const TTypedElement<ITypedElementWorldInterface>& InElementWorldHandle, const UE::Widget::EWidgetMode InWidgetMode, const ETypedElementViewportInteractionGizmoManipulationType InManipulationType);`
- L50 _public prototype_ `virtual void PostGizmoManipulationStopped(TArrayView<const FTypedElementHandle> InElementHandles, const UE::Widget::EWidgetMode InWidgetMode);`
- L51 _public prototype_ `virtual void MirrorElement(const TTypedElement<ITypedElementWorldInterface>& InElementWorldHandle, const FVector& InMirrorScale, const FVector& InPivotLocation);`
- L52 _public prototype_ `virtual bool GetFocusBounds(const TTypedElement<ITypedElementWorldInterface>& InElementWorldHandle, FBoxSphereBounds& OutBounds);`
- L53 _public prototype_ `virtual bool GetScaleForGizmo(const TTypedElement<ITypedElementWorldInterface>& InElementWorldHandle, FVector& OutScale);`

#### struct `FTypedElementViewportInteractionElement`  
`struct FTypedElementViewportInteractionElement`  
_L59-99_
- desc: Utility to hold a typed element handle and its associated world interface and  viewport interaction customization.
- L62 _public prototype_ `FTypedElementViewportInteractionElement() = default;`
- L64 _public function_ `FTypedElementViewportInteractionElement(TTypedElement<ITypedElementWorldInterface> InElementWorldHandle, FTypedElementViewportInteractionCustomization* InViewportInteractionCustomization) : ElementWorldHandle(MoveTemp(InElementWorldHandle)) , ViewportInteractionCustomization(InViewportInteractionCustomization)`
- L70 _public prototype_ `FTypedElementViewportInteractionElement(const FTypedElementViewportInteractionElement&) = default;`
- L71 _public prototype_ `FTypedElementViewportInteractionElement& operator=(const FTypedElementViewportInteractionElement&) = default;`
- L73 _public prototype_ `FTypedElementViewportInteractionElement(FTypedElementViewportInteractionElement&&) = default;`
- L74 _public prototype_ `FTypedElementViewportInteractionElement& operator=(FTypedElementViewportInteractionElement&&) = default;`
- L76 _public function_ `FORCEINLINE explicit operator bool() const`
- L81 _public function_ `FORCEINLINE bool IsSet() const`
- L88 _public function_ `bool GetGizmoPivotLocation(const UE::Widget::EWidgetMode InWidgetMode, FVector& OutPivotLocation) const`
- L89 _public function_ `void GizmoManipulationStarted(const UE::Widget::EWidgetMode InWidgetMode) const`
- L90 _public function_ `void GizmoManipulationDeltaUpdate(const UE::Widget::EWidgetMode InWidgetMode, const EAxisList::Type InDragAxis, const FInputDeviceState& InInputState, const FTransform& InDeltaTransform, const FVector& InPivotLocation) const`
- L91 _public function_ `void GizmoManipulationStopped(const UE::Widget::EWidgetMode InWidgetMode, const ETypedElementViewportInteractionGizmoManipulationType InManipulationType) const`
- L92 _public function_ `void MirrorElement(const FVector& InMirrorScale, const FVector& InPivotLocation) const`
- L93 _public function_ `bool GetFocusBounds(FBoxSphereBounds& OutBounds) const`
- L94 _public function_ `bool GetScaleForGizmo(FVector& OutScale) const`
- L97 _private member_ `TTypedElement<ITypedElementWorldInterface> ElementWorldHandle;`
- L98 _private member_ `FTypedElementViewportInteractionCustomization* ViewportInteractionCustomization = nullptr;`

#### class `UTypedElementViewportInteraction`  
`class UTypedElementViewportInteraction : public UObject, public TTypedElementInterfaceCustomizationRegistry<FTypedElementViewportInteractionCustomization>`  
_L106-156_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UObject,TTypedElementInterfaceCustomizationRegistry<FTypedElementViewportInteractionCustomization>`
- desc: A utility to handle higher-level viewport interactions, but default via UTypedElementWorldInterface, but asset editors can customize this behavior via FTypedElementViewportInteractionCustomization.
- L115 _public prototype_ `void BeginGizmoManipulation(FTypedElementListConstRef InElementsToMove, const UE::Widget::EWidgetMode InWidgetMode);` — Notify that the gizmo is potentially about to start manipulating the transform of the given set of elements. @note This list should have been pre-normalized via UTypedElementSelectionSet::GetNormalizedSelection or UTypedElementSelectionSet::GetNormalizedElementList, or FLevelEditorViewportClient::GetElementsToManipulate.
- L121 _public prototype_ `void UpdateGizmoManipulation(FTypedElementListConstRef InElementsToMove, const UE::Widget::EWidgetMode InWidgetMode, const EAxisList::Type InDragAxis, const FInputDeviceState& InInputState, const FTransform& InDeltaTransform);` — Notify that the gizmo has manipulated the transform of the given set of elements. @note This list should have been pre-normalized via UTypedElementSelectionSet::GetNormalizedSelection or UTypedElementSelectionSet::GetNormalizedElementList, or FLevelEditorViewportClient::GetElementsToManipulate.
- L127 _public prototype_ `void EndGizmoManipulation(FTypedElementListConstRef InElementsToMove, const UE::Widget::EWidgetMode InWidgetMode, const ETypedElementViewportInteractionGizmoManipulationType InManipulationType);` — Notify that the gizmo has finished manipulating the transform of the given set of elements. @note This list should have been pre-normalized via UTypedElementSelectionSet::GetNormalizedSelection or UTypedElementSelectionSet::GetNormalizedElementList, or FLevelEditorViewportClient::GetElementsToManipulate.
- L133 _public prototype_ `void ApplyDeltaToElement(const FTypedElementHandle& InElementHandle, const UE::Widget::EWidgetMode InWidgetMode, const EAxisList::Type InDragAxis, const FInputDeviceState& InInputState, const FTransform& InDeltaTransform);` — Apply the given delta to the specified element. This performs a similar operation to an in-flight gizmo manipulation, but without any pre/post-change notification.
- L138 _public prototype_ `void MirrorElement(const FTypedElementHandle& InElementHandle, const FVector& InMirrorScale);` — Apply the given mirror scale to the specified element.
- L144 _public prototype_ `bool GetFocusBounds(FTypedElementListConstRef InElements, FBoxSphereBounds& OutBox);` — Calculate the bounds of all elements in the list, to be focused on in the viewport @note This list should have been pre-normalized via UTypedElementSelectionSet::GetNormalizedSelection or UTypedElementSelectionSet::GetNormalizedElementList, or FLevelEditorViewportClient::GetElementsToManipulate.
- L150 _public prototype_ `bool GetScaleForGizmo(FTypedElementListConstRef InElements, FVector& OutScale);` — Calculate the combined, signed scale of all elements in the list, to be used for scale delta modifications (before applying). If there are multiple objects of differing scale, return the total bounds. @note This list should have been pre-normalized via UTypedElementSelectionSet::GetNormalizedSelection or UTypedElementSelectionSet::GetNormalizedElementList, or FLevelEditorViewportClient::GetElementsToManipulate.
- L155 _private prototype_ `FTypedElementViewportInteractionElement ResolveViewportInteractionElement(const FTypedElementHandle& InElementHandle) const;` — Attempt to resolve the selection interface and viewport interaction customization for the given element, if any.

#### Free symbols / members of external scopes

- L22 _macro_ `#define UE_API EDITORFRAMEWORK_API`

### `Source/Editor/EditorFramework/Public/Elements/Interfaces/TypedElementDetailsInterface.h` (Public)


#### class `ITypedElementDetailsObject`  
`class ITypedElementDetailsObject`  
_L15-29_
- desc: Proxy instance to provide a UObject for editing by a details panel. This instance will exist as long as the details panel is using it, so gives a lifetime to potentially synthesized UObject instances that are created purely for editing (eg, on instances).
- L18 _public prototype_ `virtual ~ITypedElementDetailsObject() = default;`
- L23 _public prototype_ `virtual UObject* GetObject() = 0;` — Get the underlying UObject that should be edited by the details panel, if any.
- L28 _public function_ `virtual void AddReferencedObjects(FReferenceCollector& Collector)` — Called during GC to collect references.

#### class `UTypedElementDetailsInterface`  
`class UTypedElementDetailsInterface : public UInterface`  
_L32-35_
- reflection: `UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `ITypedElementDetailsInterface`  
`class ITypedElementDetailsInterface`  
_L37-53_
- L46 _public function_ `virtual bool IsTopLevelElement(const FTypedElementHandle& InElementHandle)` — Is the given element considered "top-level" for editing? ie) Should it be edited simply from being part of the main selection set for a level?
- L52 _public function_ `virtual TUniquePtr<ITypedElementDetailsObject> GetDetailsObject(const FTypedElementHandle& InElementHandle)` — Get the proxy instance for the given element, if any. @see ITypedElementDetailsObject for more details about this proxy instance.

#### struct `TTypedElement`  
`template <> struct TTypedElement<ITypedElementDetailsInterface> : public TTypedElementBase<ITypedElementDetailsInterface>`  
_L56-60_
- inherits: `TTypedElementBase<ITypedElementDetailsInterface>`
- L58 _public function_ `bool IsTopLevelElement() const`
- L59 _public function_ `TUniquePtr<ITypedElementDetailsObject> GetDetailsObject() const`

### `Source/Editor/EditorFramework/Public/Elements/Interfaces/TypedElementEditorVisualizerInterface.h` (Public)


#### class `UTypedElementEditorVisualizerInterface`  
`class UTypedElementEditorVisualizerInterface : public UInterface`  
_L14-17_
- reflection: `UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `ITypedElementEditorVisualizerInterface`  
`class ITypedElementEditorVisualizerInterface`  
_L21-43_
- L38 _public function_ `virtual bool GetComponentVisualizersToUse(const FTypedElementHandle& InElementHandle, const UTypedElementSelectionSet* SelectionSet, TArray<FComponentVisualizerForSelection>& VisualizersOut) const` — For given element, appends any additional visualizers to use

#### struct `ITypedElementEditorVisualizerInterface::FComponentVisualizerForSelection`  
`struct FComponentVisualizerForSelection`  
_L29-33_
- L31 _public member_ `FCachedComponentVisualizer ComponentVisualizer;`
- L32 _public member_ `TOptional<TFunction<bool(void)>> IsEnabledDelegate;`

#### struct `TTypedElement`  
`template <> struct TTypedElement<ITypedElementEditorVisualizerInterface> : public TTypedElementBase<ITypedElementEditorVisualizerInterface>`  
_L46-53_
- inherits: `TTypedElementBase<ITypedElementEditorVisualizerInterface>`
- L48 _public function_ `bool GetComponentVisualizersToUse(const UTypedElementSelectionSet* SelectionSet, TArray<ITypedElementEditorVisualizerInterface::FComponentVisualizerForSelection>& VisualizersOut) const`

### `Source/Editor/EditorFramework/Public/Factories/AssetFactoryInterface.h` (Public)


#### class `UAssetFactoryInterface`  
`class UAssetFactoryInterface : public UInterface`  
_L24-27_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IAssetFactoryInterface`  
`class IAssetFactoryInterface`  
_L29-90_
- L39 _public prototype_ `virtual bool CanPlaceElementsFromAssetData(const FAssetData& InAssetData) = 0;` — Given an FAssetData, determine if this asset factory can place any elements. @returns true if the factory can be used to place elements.
- L47 _public prototype_ `virtual bool PrePlaceAsset(FAssetPlacementInfo& InPlacementInfo, const FPlacementOptions& InPlacementOptions) = 0;` — Performs any final tweaking of the PlacementInfo that the asset factory may need to do. This includes final adjustments to things like transforms. This should NOT perform any viewport or editor specific adjustments, such as grid snapping, alignment to hit objects, or undo tracking. @returns true if the asset is still valid to place after final adjustments.
- L54 _public prototype_ `virtual TArray<FTypedElementHandle> PlaceAsset(const FAssetPlacementInfo& InPlacementInfo, const FPlacementOptions& InPlacementOptions) = 0;` — Places the asset. @returns valid FTypedElementHandles that were placed by the factory from the given asset.
- L60 _public prototype_ `virtual void PostPlaceAsset(TArrayView<const FTypedElementHandle> InHandle, const FAssetPlacementInfo& InPlacementInfo, const FPlacementOptions& InPlacementOptions) = 0;` — Finalizes any placed elements based on adjustments the factory may need to do. This should NOT include any adjustments from viewport or asset editor specific functionality, such as finalizing undo tracking.
- L68 _public prototype_ `virtual FAssetData GetAssetDataFromElementHandle(const FTypedElementHandle& InHandle) = 0;` — Given an FTypedElementHandle, attempt to resolve the handle to the FAssetData which may have placed it. The FAssetData may be a wrapped type, like a static mesh component component inside a static mesh actor. @returns the FAssetData which corresponds to the placed FTypedElementHandle. The returned FAssetData may be invalid.
- L76 _public prototype_ `virtual void BeginPlacement(const FPlacementOptions& InPlacementOptions) = 0;` — Sets up any states that the factory needs to track across a placement call. Called once per factory during a PlaceAssets call from the placement subsystem. For example, for instanced static mesh placement, we may want to disable rebuilding the parent component's tree until EndPlacement is called.
- L84 _public prototype_ `virtual void EndPlacement(TArrayView<const FTypedElementHandle> InPlacedElements, const FPlacementOptions& InPlacementOptions) = 0;` — Tears down any state, or kicks off any rebuilds of data that this asset type may need. Called once per factory during a PlaceAssets call from the placement subsystem. For example, for instanced static mesh placement, we'd rebuild the parent component's tree here.
- L89 _public prototype_ `virtual UInstancedPlacemenClientSettings* FactorySettingsObjectForPlacement(const FAssetData& InAssetData, const FPlacementOptions& InPlacementOptions) = 0;` — Returns the settings object which this factory will use to customize placement settings, based on the given placement information.

### `Source/Editor/EditorFramework/Public/Styling/DepthBarStyle.h` (Public)


#### struct `FDepthBarStyle`  
`struct FDepthBarStyle : public FSlateWidgetStyle`  
_L14-105_
- reflection: `USTRUCT()`
- inherits: `FSlateWidgetStyle`
- L18 _public prototype_ `FDepthBarStyle();`
- L19 _public prototype_ `FDepthBarStyle(const FDepthBarStyle&);`
- L22 _public prototype_ `virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;`
- L24 _public member_ `static const FName TypeName;`
- L25 _public function_ `virtual const FName GetTypeName() const override`
- L27 _public prototype_ `static const FDepthBarStyle& GetDefault();`
- L30 _public member_ `FMargin Padding = FMargin(4.0f);` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L31 _public function_ `FDepthBarStyle& SetPadding(const FMargin& InPadding)`
- L34 _public member_ `FSlateBrush BackgroundBrush;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L35 _public function_ `FDepthBarStyle& SetBackgroundBrush(const FSlateBrush& InBackground)`
- L38 _public member_ `FSlateBrush TrackBrush;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L39 _public function_ `FDepthBarStyle& SetTrack(const FSlateBrush& InTrack)`
- L42 _public member_ `float TrackWidth = 2.0f;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L43 _public function_ `FDepthBarStyle& SetTrackWidth(float InTrackWidth)`
- L46 _public member_ `FSlateBrush SliceNormalBrush;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L47 _public function_ `FDepthBarStyle& SetSliceNormal(const FSlateBrush& InSliceNormal)`
- L50 _public member_ `FSlateBrush SliceHoveredBrush;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L51 _public function_ `FDepthBarStyle& SetSliceHovered(const FSlateBrush& InSliceHovered)`
- L54 _public member_ `float SliceWidth = 16.0f;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L55 _public function_ `FDepthBarStyle& SetSliceWidth(float InSliceWidth)`
- L58 _public member_ `FSlateBrush SliceTopBrush;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L59 _public function_ `FDepthBarStyle& SetSliceTopBrush(const FSlateBrush& InSliceTopBrush)`
- L62 _public member_ `FSlateBrush SliceTopHoveredBrush;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L63 _public function_ `FDepthBarStyle& SetSliceTopHovered(const FSlateBrush& InSliceTopHovered)`
- L66 _public member_ `FSlateBrush SliceBottomBrush;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L67 _public function_ `FDepthBarStyle& SetSliceBottom(const FSlateBrush& InSliceBottom)`
- L70 _public member_ `FSlateBrush SliceBottomHoveredBrush;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L71 _public function_ `FDepthBarStyle& SetSliceBottomHovered(const FSlateBrush& InSliceBottomHovered)`
- L74 _public member_ `FVector2f SliceHandleSize = FVector2f(16.0f, 16.0f);` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L75 _public function_ `FDepthBarStyle& SetSliceHandleSize(const FVector2f& InHandleSize)`
- L78 _public member_ `FSlateBrush FarPlaneButtonBrush;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L79 _public function_ `FDepthBarStyle& SetFarPlaneButtonBrush(const FSlateBrush& InFarPlaneButton)`
- L82 _public member_ `FSlateBrush NearPlaneButtonBrush;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L83 _public function_ `FDepthBarStyle& SetNearPlaneButtonBrush(const FSlateBrush& InNearPlaneButton)`
- L86 _public member_ `FVector2f PlaneButtonSize = FVector2f(16.0f, 16.0f);` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L87 _public function_ `FDepthBarStyle& SetPlaneButtonSize(const FVector2f& InHandleSize)`
- L90 _public member_ `FMargin FarPlaneButtonPadding = FMargin(4.0f);` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L91 _public function_ `FDepthBarStyle& SetFarPlaneButtonPadding(const FMargin& InPlaneButtonPadding)`
- L94 _public member_ `FMargin NearPlaneButtonPadding = FMargin(4.0f);` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L95 _public function_ `FDepthBarStyle& SetNearPlaneButtonPadding(const FMargin& InPlaneButtonPadding)`
- L98 _public member_ `FSlateColor PlaneButtonNormalColor = EStyleColor::ForegroundHeader;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L99 _public function_ `FDepthBarStyle& SetPlaneButtonNormalColor(const FSlateColor& InColor)`
- L102 _public member_ `FSlateColor PlaneButtonHoveredColor = EStyleColor::ForegroundHover;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L103 _public function_ `FDepthBarStyle& SetPlaneButtonHoveredColor(const FSlateColor& InColor)`

### `Source/Editor/EditorFramework/Public/Subsystems/EditorElementSubsystem.h` (Public)


#### class `UEditorElementSubsystem`  
`class UEditorElementSubsystem : public UEditorSubsystem`  
_L23-54_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UEditorSubsystem`
- L32 _public prototype_ `static bool SetElementTransform(FTypedElementHandle InElementHandle, const FTransform& InWorldTransform);` — Sets the world transform of the given element handle, if possible. @returns false if the world transform could not be set.
- L37 _public prototype_ `static FTypedElementListRef GetEditorNormalizedSelectionSet(const UTypedElementSelectionSet& SelectionSet);` — Return a normalized selection set like the editor would use for the gizmo manipulations
- L44 _public prototype_ `static FTypedElementListRef GetEditorManipulableElements(const FTypedElementListRef& NormalizedSelection, UE::Widget::EWidgetMode InManipulationType = UE::Widget::WM_Translate, UWorld* InRequiredWorld = nullptr);` — Return only the manipulatable elements from a selection list. Require a editor normalized selection list to behave like the editor selection Note: A manipulable element is a element that would be move when manipulating the gizmo in the editor
- L51 _public prototype_ `static TTypedElement<ITypedElementWorldInterface> GetLastSelectedEditorManipulableElement(const FTypedElementListRef& NormalizedSelection, UE::Widget::EWidgetMode InManipulationType = UE::Widget::WM_Translate, UWorld* InRequiredWorld = nullptr);` — Return the most recently selected element that is manipulable. Require a editor normalized selection list to behave like the editor selection Note: A manipulable element is a element that would be move when manipulating the gizmo in the editor.
- L53 _public prototype_ `static bool IsElementEditorManipulable(const TTypedElement<ITypedElementWorldInterface>& WorldElement, UE::Widget::EWidgetMode InManipulationType = UE::Widget::WM_Translate, UWorld* InRequiredWorld = nullptr);`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API EDITORFRAMEWORK_API`

### `Source/Editor/EditorFramework/Public/Subsystems/PlacementSubsystem.h` (Public)


#### struct `FAssetPlacementInfo`  
`struct FAssetPlacementInfo`  
_L36-70_
- reflection: `USTRUCT()`
- L42 _public member_ `FAssetData AssetToPlace;` — `UPROPERTY()` — The asset data which should be placed.
- L46 _public member_ `FName NameOverride;` — `UPROPERTY()` — If set, will override the name on placed elements instead of factory defined defaults.
- L50 _public member_ `TWeakObjectPtr<ULevel> PreferredLevel;` — `UPROPERTY()` — If set, the factory will attempt to place inside the given level. World partitioning may ultimately override this preference.
- L54 _public member_ `FTransform FinalizedTransform;` — `UPROPERTY()` — The finalized transform where the factory should be place the asset. This should include any location snapping or other considerations from viewports or editor settings.
- L58 _public member_ `TScriptInterface<IAssetFactoryInterface> FactoryOverride;` — `UPROPERTY()` — If set, will use the given factory to place the asset, instead of allowing the placement subsystem to determine which factory to use.
- L66 _public member_ `FGuid ItemGuid;` — `UPROPERTY()` — The Guid which corresponds to the item that should be placed. If unset, the asset package's persistent guid will be used. Factories should use this to tie any decomposed assets together. For example, the ItemGuid would correspond to the client in an AISMPartitionActor for tracking all static meshes which make up a decomposed actor.
- L69 _public member_ `TObjectPtr<UInstancedPlacemenClientSettings> SettingsObject = nullptr;` — `UPROPERTY()`

#### struct `FPlacementOptions`  
`struct FPlacementOptions`  
_L73-91_
- reflection: `USTRUCT()`
- L82 _public member_ `FGuid InstancedPlacementGridGuid;` — `UPROPERTY()` — The guid to use by factories for instanced placement. If unset, factories will not use instanced placement. This is used to reduce contention within one file per actor within a partition.
- L86 _public member_ `bool bPreferBatchPlacement = true;` — `UPROPERTY()` — If true, asset factory implementations should prefer a batch placement algorithm (like duplicating an object) over a single placement algorithm.
- L90 _public member_ `bool bIsCreatingPreviewElements = false;` — `UPROPERTY()` — If true, creates transient preview elements, which are transient and not saved to a level.

#### class `UPlacementSubsystem`  
`class UPlacementSubsystem : public UEditorSubsystem`  
_L94-149_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UEditorSubsystem`
- L100 _public prototype_ `void Initialize(FSubsystemCollectionBase& Collection) override;` — USubsystem Interface
- L101 _public prototype_ `void Deinitialize() override;`
- L108 _public prototype_ `TArray<FTypedElementHandle> PlaceAsset(const FAssetPlacementInfo& InPlacementInfo, const FPlacementOptions& InPlacementOptions);` — Places a single asset based on the given FAssetPlacementInfo and FPlacementOptions. @returns an array of FTypedElementHandles corresponding to any successfully placed elements.
- L114 _public prototype_ `TArray<FTypedElementHandle> PlaceAssets(TArrayView<const FAssetPlacementInfo> InPlacementInfos, const FPlacementOptions& InPlacementOptions);` — Places multiple assets based on the given FAssetPlacementInfos and FPlacementOptions. @returns an array of FTypedElementHandles corresponding to any successfully placed elements.
- L120 _public prototype_ `TScriptInterface<IAssetFactoryInterface> FindAssetFactoryFromAssetData(const FAssetData& InAssetData);` — Finds a registered AssetFactory for the given FAssetData. @returns the first found factory, or nullptr if no valid factory is found.
- L126 _public prototype_ `bool IsCreatingPreviewElements() const;` — Determines if the placement system is currently placing preview elements. @returns true if the current PlaceAssets call is creating preview elements.
- L128 _public prototype_ `FSimpleMulticastDelegate& OnPlacementFactoriesRegistered();`
- L130 _public prototype_ `TScriptInterface<IAssetFactoryInterface> GetAssetFactoryFromFactoryClass(UClass* InFactoryInterfaceClass) const;`
- L133 _public prototype_ `TScriptInterface<IAssetFactoryInterface> GetAssetFactoryFromFactoryClass(TSubclassOf<UClass> InFactoryInterfaceClass) const;` — `UE_DEPRECATED(5.4, "This overload never worked as intended. Use the UClass* overload instead.")`
- L135 _public prototype_ `void RegisterAssetFactory(TScriptInterface<IAssetFactoryInterface> AssetFactory);`
- L137 _public prototype_ `void UnregisterAssetFactory(TScriptInterface<IAssetFactoryInterface> AssetFactory);`
- L140 _private prototype_ `void RegisterPlacementFactories();`
- L141 _private prototype_ `void UnregisterPlacementFactories();`
- L144 _private member_ `TArray<TScriptInterface<IAssetFactoryInterface>> AssetFactories;` — `UPROPERTY()`
- L146 _private member_ `FSimpleMulticastDelegate PlacementFactoriesRegistered;`
- L148 _private member_ `bool bIsCreatingPreviewElements = false;`

#### Free symbols / members of external scopes

- L24 _macro_ `#define UE_API EDITORFRAMEWORK_API`

### `Source/Editor/EditorFramework/Public/Toolkits/AssetEditorModeUILayer.h` (Public)


#### class `UAssetEditorUISubsystem`  
`class UAssetEditorUISubsystem : public UEditorSubsystem`  
_L44-57_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorSubsystem`
- L49 _public member_ `static const FName VerticalToolbarID;`
- L50 _public member_ `static const FName TopLeftTabID;`
- L51 _public member_ `static const FName BottomLeftTabID;`
- L52 _public member_ `static const FName TopRightTabID;`
- L53 _public member_ `static const FName BottomRightTabID;`
- L56 _protected function_ `virtual void RegisterLayoutExtensions(FLayoutExtender& Extender)`

#### class `FAssetEditorModeUILayer`  
`class FAssetEditorModeUILayer : public TSharedFromThis<FAssetEditorModeUILayer>`  
_L59-132_
- inherits: `TSharedFromThis<FAssetEditorModeUILayer>`
- L62 _public prototype_ `FAssetEditorModeUILayer(const IToolkitHost* InToolkitHost);`
- L63 _public function_ `FAssetEditorModeUILayer()`
- L64 _public prototype_ `virtual ~FAssetEditorModeUILayer() = default;`
- L66 _public prototype_ `virtual void OnToolkitHostingStarted(const TSharedRef<IToolkit>& Toolkit);` — Called by SLevelEditor to notify the toolbox about a new toolkit being hosted
- L69 _public prototype_ `virtual void OnToolkitHostingFinished(const TSharedRef<IToolkit>& Toolkit);` — Called by SLevelEditor to notify the toolbox about an existing toolkit no longer being hosted
- L70 _public prototype_ `virtual TSharedPtr<FTabManager> GetTabManager();`
- L71 _public prototype_ `virtual TSharedPtr<FWorkspaceItem> GetModeMenuCategory() const;`
- L72 _public prototype_ `virtual void SetModePanelInfo(const FName InTabSpawnerID, const FMinorTabConfig& InTabInfo);`
- L73 _public prototype_ `virtual TMap<FName, TWeakPtr<SDockTab>> GetSpawnedTabs();`
- L76 _public prototype_ `virtual void SetSecondaryModeToolbarName(FName InName);` — Called by the Toolkit Host to set the name of the ModeToolbar this mode will extend
- L78 _public function_ `virtual FSimpleDelegate& ToolkitHostReadyForUI()`
- L82 _public function_ `virtual FSimpleDelegate& ToolkitHostShutdownUI()`
- L86 _public function_ `virtual const FName GetStatusBarName() const`
- L90 _public function_ `virtual const FName GetSecondaryModeToolbarName() const`
- L94 _public function_ `virtual const TSharedRef<FUICommandList> GetModeCommands() const`
- L99 _public function_ `virtual FNewToolMenuDelegate& RegisterSecondaryModeToolbarExtension()` — Called by the mode toolkit to extend the toolbar
- L105 _protected prototype_ `const FOnSpawnTab& GetStoredSpawner(const FName TabID);`
- L106 _protected prototype_ `void RegisterModeTabSpawners();`
- L107 _protected prototype_ `void RegisterModeTabSpawner(const FName TabID);`
- L108 _protected prototype_ `TSharedRef<SDockTab> SpawnStoredTab(const FSpawnTabArgs& Args, const FName TabID);`
- L109 _protected prototype_ `bool CanSpawnStoredTab(const FSpawnTabArgs& Args, const FName TabID);`
- L110 _protected prototype_ `FText GetTabSpawnerName(const FName TabID) const;`
- L111 _protected prototype_ `FText GetTabSpawnerTooltip(const FName TabID) const;`
- L112 _protected prototype_ `const FSlateIcon& GetTabSpawnerIcon(const FName TabID) const;`
- L116 _protected member_ `const IToolkitHost* ToolkitHost;` — The host of the toolkits created by modes
- L117 _protected member_ `TArray<FName> ModeTabIDs;`
- L118 _protected member_ `TWeakPtr<IToolkit> HostedToolkit;`
- L119 _protected member_ `TMap<FName, FMinorTabConfig> RequestedTabInfo;`
- L120 _protected member_ `TMap<FName, TWeakPtr<SDockTab>> SpawnedTabs;`
- L121 _protected member_ `FSimpleDelegate OnToolkitHostReadyForUI;`
- L122 _protected member_ `FSimpleDelegate OnToolkitHostShutdownUI;`
- L125 _protected member_ `FName SecondaryModeToolbarName;` — The name of the mode toolbar that this mode will extend (appears below the main toolbar)
- L128 _protected member_ `FNewToolMenuDelegate OnRegisterSecondaryModeToolbarExtension;` — Delegate called to actually extend the mode toolbar
- L131 _protected member_ `TSharedRef<FUICommandList> ModeCommands;` — A list of commands this ModeUILayer is aware of, currently only passed into the Mode Toolbar

#### Free symbols / members of external scopes

- L31 _macro_ `#define UE_API EDITORFRAMEWORK_API`

### `Source/Editor/EditorFramework/Public/Toolkits/IToolkit.h` (Public)


#### enum `EToolkitMode::Type`  
`enum Type`  
_L18-25_
- L21 _public enumerator_ `Standalone` — Stand-alone asset editing "app"
- L24 _public enumerator_ `WorldCentric` — World-centric asset editor, with an interface that sits alongside the level editor

#### enum `EToolkitTabSpot::Type`  
`enum Type`  
_L31-54_
- L35 _public enumerator_ `Details` — A good place to put a details tab or property tree, or other tabs that display information about the current object the user has selected
- L38 _public enumerator_ `Document` — This is for document windows, such as a graph editor or a profiling results panel
- L41 _public enumerator_ `Navigation` — Put navigation-related panels here, such as a list of editable sub-objects
- L44 _public enumerator_ `ToolBar` — Tool bar panels are usually displayed at the top of the tool in a narrow strip
- L47 _public enumerator_ `Placement` — Placement panels host tools for creating new things.  This is usually displayed in the top left or center left of a window
- L50 _public enumerator_ `Viewport` — Preview viewports
- L53 _public enumerator_ `BelowLevelEditor` — Area below the level editor. Useful for things that should fill the entire width of the level editor

#### class `IToolkit`  
`class IToolkit`  
_L61-142_
- desc: Interface for editor toolkits (asset editors and mode tools)
- L65 _public prototype_ `virtual ~IToolkit() = default;`
- L68 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) = 0;` — Register tabs that this toolkit can spawn with the TabManager
- L71 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) = 0;` — Unregister tabs that this toolkit can spawn
- L76 _public prototype_ `virtual FName GetToolkitFName() const = 0;` — Returns the invariant name of this toolkit type
- L79 _public prototype_ `virtual FName GetToolkitContextFName() const = 0;` — Returns the invariant name of this toolkit type, used for establishing the context for help, documentation and tutorials
- L82 _public prototype_ `virtual FText GetBaseToolkitName() const = 0;` — Returns the localized name of this toolkit type (typically just "<ClassName> editor")
- L85 _public prototype_ `virtual FText GetToolkitName() const = 0;` — Returns the localized name of this toolkit
- L88 _public prototype_ `virtual FText GetTabSuffix() const = 0;` — Returns the localized tab suffix
- L91 _public prototype_ `virtual FText GetToolkitToolTipText() const = 0;` — Returns the localized tooltip text of this toolkit
- L94 _public prototype_ `virtual TSharedRef<FWorkspaceItem> GetWorkspaceMenuCategory() const = 0;` — Returns the workspace menu category of this toolkit
- L97 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const = 0;` — Returns the localize prefix string to use for tab labels in world-centric mode.
- L100 _public prototype_ `virtual bool IsAssetEditor() const = 0;` — Returns true if this toolkit is used to edit assets (even if it's not necessarily editing one right now.)
- L103 _public prototype_ `virtual const TArray< UObject* >* GetObjectsCurrentlyBeingEdited() const = 0;` — For asset editor toolkits, returns the UObjects for the assets currently being edited
- L106 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const = 0;` — @return Returns the color and opacity to use for the color that appears behind the tab text for this toolkit's tab in world-centric mode.
- L109 _public prototype_ `virtual bool IsHosted() const = 0;` — @return Returns true if this toolkit is currently hosted.  All toolkits are hosted except during a shutdown situation.
- L112 _public prototype_ `virtual const TSharedRef<IToolkitHost> GetToolkitHost() const = 0;` — @return Returns the toolkit host for this toolkit
- L121 _public prototype_ `virtual bool ProcessCommandBindings(const FKeyEvent& InKeyEvent) const = 0;` — Processes any UI commands which are activated by the specified event @param InKeyEvent	The event to check @return true if an action was processed
- L124 _public prototype_ `virtual void BringToolkitToFront() = 0;` — Call this function to bring all of this toolkit's tabs to the foreground in their respective stacks.  Also causes the toolkit's host window to be foregrounded, too!
- L127 _public prototype_ `virtual bool IsBlueprintEditor() const = 0;` — Returns if this is a IBlueprintEditor derivation
- L130 _public function_ `virtual void ToolkitBroughtToFront()` — Called when a toolkit has been brought to the 'front'
- L133 _public function_ `virtual bool IsSimpleAssetEditor() const` — Returns true if this is the default generic asset editor used by multiple classes
- L136 _public prototype_ `virtual FEditorModeTools& GetEditorModeManager() const = 0;` — Gets the mode manager for this toolkit
- L139 _public prototype_ `virtual TSharedPtr<SWidget> GetInlineContent() const = 0;` — @returns the inline content that this toolkit returns
- L141 _public function_ `virtual void SetModeUILayer(const TSharedPtr<FAssetEditorModeUILayer> InLayer)`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace EToolkitMode`
- L29 _namespace_ `namespace EToolkitTabSpot`

### `Source/Editor/EditorFramework/Public/Toolkits/IToolkitHost.h` (Public)


#### class `IToolkitHost`  
`class IToolkitHost`  
_L14-81_
- desc: Base interface class for toolkit hosts
- L18 _public prototype_ `virtual ~IToolkitHost() = default;`
- L21 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnActiveViewportChanged, TSharedPtr<IAssetViewport>, TSharedPtr<IAssetViewport>) virtual TSharedRef< class SWidget > GetParentWidget() = 0;` — Notificaton when the active viewport changed
- L28 _public prototype_ `virtual void BringToFront() = 0;` — Brings this toolkit host's window (and tab, if it has one), to the front
- L31 _public prototype_ `virtual TSharedPtr< class FTabManager > GetTabManager() const = 0;` — Access the toolkit host's tab manager
- L34 _public prototype_ `virtual void OnToolkitHostingStarted( const TSharedRef< class IToolkit >& Toolkit ) = 0;` — Called when a toolkit is opened within this host
- L37 _public prototype_ `virtual void OnToolkitHostingFinished( const TSharedRef< class IToolkit >& Toolkit ) = 0;` — Called when a toolkit is no longer being hosted within this host
- L40 _public prototype_ `virtual class UWorld* GetWorld() const = 0;` — @return For world-centric toolkit hosts, gets the UWorld associated with this host
- L43 _public prototype_ `virtual FEditorModeTools& GetEditorModeManager() const = 0;` — Returns the mode manager for this toolkit host. For standalone toolkits
- L46 _public prototype_ `virtual UTypedElementCommonActions* GetCommonActions() const = 0;` — Returns the common actions implementation for this toolkit host
- L50 _public prototype_ `virtual FName GetStatusBarName() const = 0;` — Returns the status bar name that can be used with UStatusBarSubsystem to display messages in the status bar of this toolkit host. Should return NAME_None if not applicable.
- L54 _public function_ `virtual void AddViewportOverlayWidget(TSharedRef<SWidget> InOverlaidWidget, TSharedPtr<IAssetViewport> InViewport = nullptr)` — Allows Toolkits to push widgets to the viewport.  Passing a nullptr for the Viewport will add  or remove the OverlayWidget to or from the ActiveViewport
- L61 _public function_ `virtual void AddViewportOverlayWidget(TSharedRef<SWidget> InOverlaidWidget, int32 ZOrder, TSharedPtr<IAssetViewport> InViewport = nullptr)` — Allows Toolkits to push widgets to the viewport with a specific Z-Order.  Passing a nullptr for the Viewport will add  or remove the OverlayWidget to or from the ActiveViewport
- L63 _public function_ `virtual void RemoveViewportOverlayWidget(TSharedRef<SWidget> InOverlaidWidget, TSharedPtr<IAssetViewport> InViewport = nullptr)`
- L67 _public function_ `virtual FVector2D GetActiveViewportSize() final` — `UE_DEPRECATED(5.6, "Viewport sizes are represented in float, please update your callsites to use GetActiveViewportWidgetSize and use FVector2f for slate sizes.")` — Return the size of the active viewport, accounting for DPI Scale
- L73 _public function_ `virtual FVector2f GetActiveViewportWidgetSize() const` — Return the size of the active viewport, accounting for DPI Scale
- L79 _public prototype_ `virtual FOnActiveViewportChanged& OnActiveViewportChanged() = 0;` — Gets a multicast delegate which is executed whenever the toolkit host's active viewport changes.

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnActiveViewportChanged, TSharedPtr<IAssetViewport>, TSharedPtr<IAssetViewport>) virtual TSharedRef< class SWidget > GetParentWidget() = 0;` — Notificaton when the active viewport changed

### `Source/Editor/EditorFramework/Public/Toolkits/ToolkitManager.h` (Public)


#### class `FToolkitManager`  
`class FToolkitManager`  
_L16-44_
- desc: Singleton that managers instances of editor toolkits
- L21 _public prototype_ `static FToolkitManager& Get();` — Get the singleton instance of the asset editor manager
- L24 _public prototype_ `void RegisterNewToolkit( const TSharedRef< IToolkit > NewToolkit );` — Call this to register a newly-created toolkit.
- L27 _public prototype_ `void CloseToolkit( const TSharedRef< IToolkit > ClosingToolkit );` — Call this to close an existing toolkit
- L30 _public prototype_ `void OnToolkitHostDestroyed( IToolkitHost* HostBeingDestroyed );` — Called by a toolkit host itself right before it goes away, so that we can make sure the toolkits are destroyed too
- L33 _public prototype_ `TSharedPtr< IToolkit > FindEditorForAsset( const UObject* Asset );` — Tries to find an open asset editor that's editing the specified asset, and returns the toolkit for that asset editor
- L37 _private prototype_ `FToolkitManager();` — Buried constructor since the asset editor manager is a singleton
- L43 _private member_ `TArray< TSharedPtr< IToolkit > > Toolkits;` — List of all currently open toolkits

### `Source/Editor/EditorFramework/Public/Tools/AssetEditorContextInterface.h` (Public)


#### class `UAssetEditorContextInterface`  
`class UAssetEditorContextInterface : public UInterface`  
_L14-17_
- reflection: `UINTERFACE(Blueprintable, MinimalAPI)`
- inherits: `UInterface`

#### class `IAssetEditorContextInterface`  
`class IAssetEditorContextInterface`  
_L22-56_
- desc: An interface for a context object that exposes common functionality of an asset editor.
- L30 _public prototype_ `virtual const UTypedElementSelectionSet* GetSelectionSet() const = 0;` — Get the selection set that the asset editor uses.
- L35 _public prototype_ `virtual UTypedElementSelectionSet* GetMutableSelectionSet() = 0;` — Get the selection set that the asset editor uses.
- L40 _public prototype_ `virtual UTypedElementCommonActions* GetCommonActions() = 0;` — Get the typed element common actions for the asset editor.
- L45 _public prototype_ `virtual UWorld* GetEditingWorld() const = 0;` — Gets the world on which the asset editor performs actions.
- L50 _public prototype_ `virtual const IToolkitHost* GetToolkitHost() const = 0;` — Get the toolkit host associated with our asset editor.
- L55 _public prototype_ `virtual IToolkitHost* GetMutableToolkitHost() = 0;` — Get the toolkit host associated with our asset editor.

### `Source/Editor/EditorFramework/Public/Tools/Modes.h` (Public)


#### struct `FEditorModeInfo`  
`struct FEditorModeInfo`  
_L17-51_
- L20 _public prototype_ `FEditorModeInfo();` — Default constructor
- L23 _public prototype_ `FEditorModeInfo( FEditorModeID InID, FText InName = FText(), FSlateIcon InIconBrush = FSlateIcon(), TAttribute<bool> InVisibility = false, int32 InPriorityOrder = MAX_int32 );` — Helper constructor
- L32 _public member_ `FEditorModeID ID;` — The mode ID
- L35 _public member_ `FName ToolbarCustomizationName;` — Name of the toolbar this mode uses and can be used by external systems to customize that mode toolbar
- L38 _public member_ `FText Name;` — Name for the editor to display
- L41 _public member_ `FSlateIcon IconBrush;` — The mode icon
- L44 _public member_ `int32 PriorityOrder;` — The priority of this mode which will determine its default order and shift+X command assignment
- L47 _public prototype_ `bool IsVisible() const;` — Whether or not the mode should be visible in the mode toolbar
- L50 _protected member_ `TAttribute<bool> Visibility;`

#### Free symbols / members of external scopes

- L15 _typedef_ `typedef FName FEditorModeID;` — The shorthand identifier used for editor modes
- L53 _delegate_ `DECLARE_MULTICAST_DELEGATE(FRegisteredModesChangedEvent);`
- L53 _prototype_ `DECLARE_MULTICAST_DELEGATE(FRegisteredModesChangedEvent);`
- L54 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnModeRegistered, FEditorModeID);`
- L54 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnModeRegistered, FEditorModeID);`
- L55 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnModeUnregistered, FEditorModeID);`
- L55 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnModeUnregistered, FEditorModeID);`

### `Source/Editor/EditorFramework/Public/UnrealWidgetFwd.h` (Public)


#### enum `ECoordSystem`  
`enum ECoordSystem`  
_L8-16_
- desc: Coordinate system identifiers.
- L10 _public enumerator_ `COORD_None = -1`
- L11 _public enumerator_ `COORD_World`
- L12 _public enumerator_ `COORD_Local`
- L13 _public enumerator_ `COORD_Parent`
- L14 _public enumerator_ `COORD_Explicit`
- L15 _public enumerator_ `COORD_Max`

#### enum `UE::Widget::EWidgetMode`  
`enum EWidgetMode`  
_L20-29_
- L22 _public enumerator_ `WM_None = -1`
- L23 _public enumerator_ `WM_Translate`
- L24 _public enumerator_ `WM_TranslateRotateZ`
- L25 _public enumerator_ `WM_2D`
- L26 _public enumerator_ `WM_Rotate`
- L27 _public enumerator_ `WM_Scale`
- L28 _public enumerator_ `WM_Max`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Widget` (scope `UE`)

### `Source/Editor/EditorFramework/Public/ViewportTabContent.h` (Public)


#### class `FViewportTabContent`  
`class FViewportTabContent`  
_L27-77_
- L30 _public prototype_ `virtual ~FViewportTabContent() = default;`
- L33 _public prototype_ `bool IsVisible() const;` — Returns whether the tab is currently shown
- L36 _public prototype_ `bool BelongsToTab(TSharedRef<SDockTab> InParentTab) const;` — @return True if this viewport belongs to the tab given
- L44 _public prototype_ `bool IsViewportConfigurationSet(const FName& ConfigurationName) const;` — Returns whether the named layout is currently selected @param ConfigurationName		The name of the layout (for the names in namespace LevelViewportConfigurationNames) @return						True, if the named layout is currently active
- L46 _public function_ `virtual void SetViewportConfiguration(const FName& ConfigurationName)`
- L52 _public function_ `virtual void BindViewportLayoutCommands(FUICommandList& InOutCommandList, FName ViewportConfigKey)` — Maps the common commands into the given command list for this layout to the given viewport based on the config key. This call is only additive to the command list, and does not clear or erase already mapped actions.
- L54 _public prototype_ `const TMap< FName, TSharedPtr< IEditorViewportLayoutEntity > >* GetViewports() const;`
- L56 _public typedef_ `using ViewportActionFunction = TFunction<void(FName Name, TSharedPtr<IEditorViewportLayoutEntity>)>;`
- L57 _public prototype_ `void PerformActionOnViewports(ViewportActionFunction& TFuncPtr);`
- L59 _public prototype_ `DECLARE_EVENT(FViewportTabContent, FViewportTabContentLayoutChangedEvent);`
- L60 _public function_ `virtual FViewportTabContentLayoutChangedEvent& OnViewportTabContentLayoutChanged()`
- L62 _public prototype_ `DECLARE_EVENT_OneParam(FViewportTabContent, FViewportTabContentLayoutStartChangeEvent, bool);`
- L63 _public function_ `virtual FViewportTabContentLayoutStartChangeEvent& OnViewportTabContentLayoutStartChange()`
- L66 _protected member_ `FViewportTabContentLayoutChangedEvent OnViewportTabContentLayoutChangedEvent;`
- L67 _protected member_ `FViewportTabContentLayoutStartChangeEvent OnViewportTabContentLayoutStartChangeEvent;`
- L69 _protected member_ `TWeakPtr<SDockTab> ParentTab;`
- L71 _protected member_ `FString LayoutString;`
- L74 _protected member_ `TSharedPtr<FEditorViewportLayout> ActiveViewportLayout;` — Current layout
- L76 _protected member_ `TOptional<FName> PreviouslyFocusedViewport;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API EDITORFRAMEWORK_API`
- L59 _delegate_ `DECLARE_EVENT(FViewportTabContent, FViewportTabContentLayoutChangedEvent);`
- L62 _delegate_ `DECLARE_EVENT_OneParam(FViewportTabContent, FViewportTabContentLayoutStartChangeEvent, bool);`

### `Source/Editor/EditorFramework/Public/Viewports/InViewportUIDragOperation.h` (Public)


#### class `FInViewportUIDragOperation`  
`class FInViewportUIDragOperation : public FDragDropOperation`  
_L23-78_
- inherits: `FDragDropOperation`
- desc: A Sample implementation of IDragDropOperation
- L27 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FInViewportUIDragOperation, FDragDropOperation) /** * Invoked when the drag and drop operation has ended. * * @param bDropWasHandled true when the drop was handled by some widget;`
- L41 _public prototype_ `virtual void OnDragged(const FDragDropEvent& DragDropEvent) override;` — Called when the mouse was moved during a drag and drop operation @param DragDropEvent    The event that describes this drag drop operation.
- L52 _public prototype_ `static TSharedRef<FInViewportUIDragOperation> New(const TSharedRef<class SWidget>& InUIToBeDragged, const FVector2D InDecoratorOffset, const FVector2D& OwnerAreaSize, FOnInViewportUIDropped& InDropDelegate);` — Create this Drag and Drop Content @param InUIToBeDragged	  The UI being dragged @param InDecoratorOffset   Where within the UI we grabbed, so we're not dragging by the upper left of the UI. @param OwnerAreaSize       Size of the DockArea at the time when we start dragging. @return a new FDockingDragOperation
- L54 _public prototype_ `virtual ~FInViewportUIDragOperation();`
- L57 _public prototype_ `const FVector2f GetDecoratorOffsetFromCursor();` — @return The offset into the tab where the user grabbed in Slate Units.
- L59 _public prototype_ `void BroadcastDropEvent(const FVector2D InLocation);`
- L63 _protected prototype_ `FInViewportUIDragOperation(const TSharedRef<class SWidget>& InUIToBeDragged, const FVector2D InDecoratorOffsetFromCursor, const FVector2D& OwnerAreaSize, FOnInViewportUIDropped& InDropDelegate);` — The constructor is protected, so that this class can only be instantiated as a shared pointer.
- L66 _protected member_ `TSharedPtr<class SWidget> UIBeingDragged;` — What is actually being dragged in this operation
- L69 _protected member_ `FVector2f DecoratorOffsetFromCursor;` — Where the user grabbed the UI measured in screen space from its top-left corner
- L72 _protected member_ `TSharedPtr<SDockingTabStack> CursorDecoratorStackNode;` — Decorator widget where we add temp doc tabs to
- L75 _protected member_ `FVector2f LastContentSize;` — What the size of the content was when it was last shown. The user drags splitters to set this size; it is legitimate state.
- L77 _protected member_ `FOnInViewportUIDropped DropDelegate;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API EDITORFRAMEWORK_API`
- L18 _delegate_ `DECLARE_DELEGATE_OneParam(FOnInViewportUIDropped, const FVector2D DropLocation) class SDockingTabStack;`

### `Source/Editor/EditorFramework/Public/Viewports/SDepthBar.h` (Public)


#### class `SDepthBar`  
`class SDepthBar : public SPanel`  
_L17-269_
- inherits: `SPanel`
- L92 _public function_ `static FDepthIndicatorSlot::FSlotArguments Slot()`
- L97 _public function_ `DECLARE_DELEGATE_OneParam(FOnDepthChanged, const TOptional<double>&) SLATE_BEGIN_ARGS(SDepthBar)`
- L117 _public typedef_ `using FScopedWidgetDepthIndicatorSlotArguments = TPanelChildren<FDepthIndicatorSlot>::FScopedWidgetSlotArguments;`
- L118 _public function_ `FScopedWidgetDepthIndicatorSlotArguments AddDepthIndicatorSlot()`
- L123 _public function_ `FScopedWidgetDepthIndicatorSlotArguments InsertDepthIndicatorSlot(int32 Index = INDEX_NONE)`
- L128 _public prototype_ `FDepthIndicatorSlot& GetDepthIndicatorSlot(int32 Index);`
- L129 _public prototype_ `const FDepthIndicatorSlot& GetDepthIndicatorSlot(int32 Index) const;`
- L130 _public prototype_ `void ClearDepthIndicators();`
- L132 _public function_ `SDepthBar() : DepthIndicatorChildren(this) , DepthLabelChildren(this) , AllChildren(this)`
- L141 _public prototype_ `void Construct(const FArguments& InArgs);`
- L143 _public prototype_ `virtual FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const override;`
- L144 _public prototype_ `virtual void OnArrangeChildren(const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren) const override;`
- L146 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L147 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L148 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L149 _public prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L150 _public prototype_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;`
- L153 _protected prototype_ `virtual FChildren* GetChildren() override;`
- L154 _protected prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L155 _protected prototype_ `virtual FVector2D ComputeDesiredSize(float LayoutScaleMultiplier) const override;`
- L216 _private typedef_ `using FScopedWidgetDepthLabelSlotArguments = TPanelChildren<FDepthLabelSlot>::FScopedWidgetSlotArguments;`
- L217 _private function_ `FScopedWidgetDepthLabelSlotArguments AddDepthLabelSlot()`
- L222 _private function_ `FScopedWidgetDepthLabelSlotArguments InsertDepthLabelSlot(int32 Index = INDEX_NONE)`
- L228 _private prototype_ `FMargin GetBarInset() const;` — Gets the inset space where bar drawing occurs
- L230 _private prototype_ `TOptional<FBarPositions> GetBarPositions(const FGeometry& InGeometry) const;`
- L232 _private prototype_ `EVisibility GetFarPlaneLabelVisibility() const;`
- L233 _private prototype_ `EVisibility GetNearPlaneLabelVisibility() const;`
- L234 _private prototype_ `FText GetFarPlaneText() const;`
- L235 _private prototype_ `FText GetNearPlaneText() const;`
- L237 _private member_ `TPanelChildren<FDepthIndicatorSlot> DepthIndicatorChildren;`
- L238 _private member_ `TPanelChildren<FDepthLabelSlot> DepthLabelChildren;`
- L239 _private member_ `FCombinedChildren AllChildren;`
- L252 _private member_ `EDragTarget HoverTarget = EDragTarget::None;`
- L253 _private member_ `EDragTarget DragTarget = EDragTarget::None;`
- L256 _private member_ `FVector2D StartDragPosition = FVector2D::Zero();` — Store drag position as doubles rather than floats to handle precision drags on very large worlds
- L257 _private member_ `FVector2D DragPosition = FVector2D::Zero();`
- L259 _private member_ `TAttribute<EMode> Mode;`
- L260 _private member_ `TAttribute<TOptional<FDepthSpace>> DepthSpace;`
- L261 _private member_ `TAttribute<TOptional<double>> NearPlane;`
- L262 _private member_ `TAttribute<TOptional<double>> FarPlane;`
- L263 _private member_ `FOnDepthChanged OnNearPlaneChanged;`
- L264 _private member_ `FOnDepthChanged OnFarPlaneChanged;`
- L267 _private member_ `const FDepthBarStyle* Style = nullptr;`

#### enum `SDepthBar::EMode`  
`enum class EMode`  
_L20-24_
- L22 _public enumerator_ `Perspective`
- L23 _public enumerator_ `Orthographic`

#### struct `SDepthBar::FDepthSpace`  
`struct FDepthSpace`  
_L26-61_
- L28 _public prototype_ `FDepthSpace(const FVector& InOrigin, const FVector& InForward, const FBox& Bounds);`
- L30 _public function_ `const FVector& GetPosition() const`
- L31 _public function_ `const FVector& GetForward() const`
- L34 _public function_ `double GetAlignedMin() const` — Gets the minimum value relative to originating direction
- L36 _public function_ `double GetAlignedMax() const` — Gets the maximum value relative to originating direction
- L39 _public prototype_ `double GetAlignedPosition(const FVector& Position) const;` — Get the point of the position on the line starting at the origin, facing along the forward.
- L42 _public prototype_ `double AlignedToRelativePosition(double AlignedPosition) const;` — Get the relative value of the given axis-aligned position
- L45 _public prototype_ `double RelativeToAlignedPosition(double RelativePosition) const;` — Get the axis-aligned value of the given relative position
- L48 _public prototype_ `double RelativeToBoundsPosition(double RelativePosition) const;` — Get the bounds position of the given relative position
- L51 _public prototype_ `double BoundsToRelativePosition(double BoundsPosition) const;` — Get the relative value of the given bounds position
- L54 _private member_ `FVector Origin;`
- L55 _private member_ `FVector Forward;`
- L57 _private member_ `double AlignedMin;`
- L58 _private member_ `double AlignedMax;`
- L60 _private member_ `bool bFlipped;`

#### class `SDepthBar::FDepthIndicatorSlot`  
`class FDepthIndicatorSlot : public TBasicLayoutWidgetSlot<FDepthIndicatorSlot>`  
_L66-90_
- inherits: `TBasicLayoutWidgetSlot<FDepthIndicatorSlot>`
- desc: A slot that is placed along the depth bar, representing a range within the depth space
- L70 _public function_ `SLATE_SLOT_BEGIN_ARGS(FDepthIndicatorSlot, TBasicLayoutWidgetSlot<FDepthIndicatorSlot>) SLATE_ATTRIBUTE(FBoxSphereBounds, Bounds) SLATE_SLOT_END_ARGS() void SetBounds(TAttribute<FBoxSphereBounds> InBounds)`
- L80 _public function_ `void Construct(const FChildren& SlotOwner, FSlotArguments&& InArgs)`
- L86 _public function_ `const TAttribute<FBoxSphereBounds>& GetBounds() const`
- L89 _protected member_ `TAttribute<FBoxSphereBounds> Bounds;`

#### struct `SDepthBar::FBarPositions`  
`struct FBarPositions`  
_L159-174_
- L161 _public member_ `FDepthSpace DepthSpace;`
- L164 _public member_ `double BarMin;` — The Top of the bar (i.e. the far plane max)
- L166 _public member_ `double BarMax;` — The Bottom of the bar (i.e. the near plane min)
- L168 _public member_ `double BarFarPlane;`
- L169 _public member_ `double BarNearPlane;`
- L171 _public prototype_ `double WorldToBarPosition(const FVector& WorldPosition) const;`
- L172 _public prototype_ `double RelativeToBarPosition(double RelativePosition) const;`
- L173 _public prototype_ `double BarToAlignedPosition(double BarPosition) const;`

#### struct `SDepthBar::FDepthLabelSlot`  
`struct FDepthLabelSlot : public TSlotBase<FDepthLabelSlot>`  
_L179-214_
- inherits: `TSlotBase<FDepthLabelSlot>`
- desc: Depth label slots are displayed next to the bar
- L181 _public prototype_ `SLATE_SLOT_BEGIN_ARGS(FDepthLabelSlot, TSlotBase<FDepthLabelSlot>) SLATE_EVENT(FGetBarPosition, OnGetBarPosition) SLATE_ATTRIBUTE(EVerticalAlignment, VAlign);`
- L185 _public function_ `SLATE_SLOT_END_ARGS() void Construct(const FChildren& SlotOwner, FSlotArguments&& InArgs)`
- L194 _public function_ `float GetBarPosition(const FBarPositions& BarPositions) const`
- L203 _public function_ `EVerticalAlignment GetVerticalAlignment() const`
- L212 _protected member_ `FGetBarPosition OnGetBarPosition;`
- L213 _protected member_ `TAttribute<EVerticalAlignment> VAlign = VAlign_Center;`

#### enum `SDepthBar::EDragTarget`  
`enum class EDragTarget`  
_L241-251_
- L243 _public enumerator_ `None`
- L245 _public enumerator_ `Near_Button`
- L246 _public enumerator_ `Far_Button`
- L248 _public enumerator_ `Near_Handle`
- L249 _public enumerator_ `Far_Handle`
- L250 _public enumerator_ `Slice`

#### Free symbols / members of external scopes

- L97 _delegate_ `DECLARE_DELEGATE_OneParam(FOnDepthChanged, const TOptional<double>&) SLATE_BEGIN_ARGS(SDepthBar) {} SLATE_ATTRIBUTE(EMode, Mode) SLATE_ATTRIBUTE(TOptional<FDepthSpace>, DepthSpace) SLATE_ATTRIBUTE(TOptional<double>, NearPlane) SLATE_ATTRIBUTE(TOptional<double>, FarPlane) SLATE_EVENT(FOnDepthChanged, OnNearPlaneChanged) SLATE_EVENT(FOnDepthChanged, OnFarPlaneChanged) SLATE_SLOT_ARGUMENT(SDepthBar::FDepthIndicatorSlot, Slots) PRAGMA_DISABLE_EXPERIMENTAL_WARNINGS SLATE_STYLE_ARGUMENT(FDepthBarStyle, Style) PRAGMA_ENABLE_EXPERIMENTAL_WARNINGS SLATE_END_ARGS() using FScopedWidgetDepthIndicatorSlotArguments = TPanelChildren<FDepthIndicatorSlot>::FScopedWidgetSlotArguments;`
- L176 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(float, FGetBarPosition, const FBarPositions& BarPositions)`
