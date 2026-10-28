# Runtime / InteractiveToolsFramework

- module root: `Source/Runtime/InteractiveToolsFramework`
- headers: 124; symbols: 3880
- symbol kinds: class=245, delegate=32, enum=36, enumerator=168, function=538, macro=3, member=1168, namespace=40, prototype=1567, struct=65, typedef=17, variable=1
- PrivateDependencyModuleNames: EditorToolEvents, Engine, RHI, RenderCore, Slate, SlateCore
- PublicDependencyModuleNames: ApplicationCore, Core, CoreUObject, GeometryCore, InputCore, MeshDescription

### `Source/Runtime/InteractiveToolsFramework/Private/BaseGizmos/FreePositionSubGizmo.h` (Private)


#### class `UFreePositionSubGizmo`  
`class UFreePositionSubGizmo : public UPlanePositionGizmo`  
_L17-36_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPlanePositionGizmo`
- desc: UFreePositionSubGizmo is very similar to UPlanePositionGizmo with a camera axis source, but when using a custom destination function, it can use the destination to directly set a transform source.
- L22 _public prototype_ `bool InitializeAsScreenPlaneTranslateGizmo( const UE::GizmoUtil::FTransformSubGizmoCommonParams& Params, UE::GizmoUtil::FTransformSubGizmoSharedState* SharedState);`
- L27 _public prototype_ `virtual void OnClickDrag(const FInputDeviceRay& DragPos) override;` — IClickDragBehaviorTarget
- L35 _public member_ `TScriptInterface<IGizmoTransformSource> TransformSource;` — `UPROPERTY()` — AxisSource provides the 3D plane on which the interaction happens

### `Source/Runtime/InteractiveToolsFramework/Private/BaseGizmos/FreeRotationSubGizmo.h` (Private)


#### class `UFreeRotationSubGizmo`  
`class UFreeRotationSubGizmo : public UInteractiveGizmo, public IClickDragBehaviorTarget, public IHoverBehaviorTarget`  
_L27-135_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveGizmo,IClickDragBehaviorTarget,IHoverBehaviorTarget`
- desc: A free rotation sub gizmo implements an arcball-like rotation.
- L35 _public prototype_ `bool InitializeAsRotationGizmo( const UE::GizmoUtil::FTransformSubGizmoCommonParams& InitializationParams, UGizmoViewContext* ViewContext, UE::GizmoUtil::FTransformSubGizmoSharedState* SharedState);` — Initializes the properties for the gizmo
- L67 _public function_ `void SetUnscaledSphereRadius(double Radius)` — Determines the size of the invisible sphere we raycast to perform the rotation.
- L73 _public function_ `void SetShowSphereBoundsDuringInteraction(bool bOn)` — When true (default) a circle is drawn to show the outside bounds of the interaction sphere while interacting with the gizmo.
- L76 _public prototype_ `virtual void Setup() override;` — UInteractiveGizmo overrides
- L77 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L78 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L81 _public prototype_ `virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& PressPos) override;` — IClickDragBehaviorTarget implementation
- L82 _public prototype_ `virtual void OnClickPress(const FInputDeviceRay& PressPos) override;`
- L83 _public prototype_ `virtual void OnClickDrag(const FInputDeviceRay& DragPos) override;`
- L84 _public prototype_ `virtual void OnClickRelease(const FInputDeviceRay& ReleasePos) override;`
- L85 _public prototype_ `virtual void OnTerminateDragSequence() override;`
- L88 _public prototype_ `virtual FInputRayHit BeginHoverSequenceHitTest(const FInputDeviceRay& PressPos) override;` — IHoverBehaviorTarget implementation
- L89 _public prototype_ `virtual void OnBeginHover(const FInputDeviceRay& DevicePos) override;`
- L90 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) override;`
- L91 _public prototype_ `virtual void OnEndHover() override;`
- L99 _public member_ `TScriptInterface<IGizmoAxisSource> AxisSource;` — `UPROPERTY()` — AxisSource provides the origin of the interaction sphere and the plane to raycast when hitting outside the sphere
- L103 _public member_ `TScriptInterface<IGizmoClickTarget> HitTarget;` — `UPROPERTY()` — The HitTarget provides a hit-test against some 3D element (presumably a visual widget) that controls when interaction can start
- L107 _public member_ `TScriptInterface<IGizmoStateTarget> StateTarget;` — `UPROPERTY()` — StateTarget is notified when interaction starts and ends, so that things like undo/redo can be handled externally
- L111 _public member_ `TScriptInterface<IGizmoTransformSource> TransformSource;` — `UPROPERTY()` — Target that is rotated by the sub gizmo.
- L115 _public member_ `TObjectPtr<UGizmoViewContext> GizmoViewContext = nullptr;` — `UPROPERTY()` — View info used during raycasts
- L119 _public member_ `TObjectPtr<UClickDragInputBehavior> MouseBehavior;` — `UPROPERTY()` — The mouse click behavior of the gizmo is accessible so that it can be modified to use different mouse keys.
- L122 _private member_ `bool bInInteraction = false;`
- L123 _private member_ `bool bShowSphereBoundsDuringInteraction = true;`
- L125 _private member_ `FVector LastSphereIntersectionPoint;`
- L126 _private member_ `double InteractionSphereRadius = 0;`
- L127 _private prototype_ `bool ClickPress_IncrementalSphereBound(const FInputDeviceRay& PressPos);`
- L128 _private prototype_ `bool ClickDrag_IncrementalSphereBound(const FInputDeviceRay& DragPos);`
- L130 _private member_ `double UnscaledSphereRadius = 100;`
- L134 _private member_ `TUniqueFunction<void(float DeltaTime)> CustomTickFunction;` — Helper that can hold some extra upkeep to do during Tick (used to update a camera axis source if needed).

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace GizmoUtil` (scope `UE`)

### `Source/Runtime/InteractiveToolsFramework/Private/BaseGizmos/GizmoPrivateUtil.h` (Private)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace GizmoUtil` (scope `UE`)
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace GizmoUtil` (scope `UE`)
- L30 _prototype_ `EAxis::Type ToAxis(ETransformGizmoSubElements Element);` (scope `UE::GizmoUtil`) — Given a single element, gives the axis that defines that element (e.g., x for TranslateAxisX or TranslatePlaneYZ, etc). Gives EAxis::None if the element is not a single element.
- L36 _prototype_ `UGizmoViewContext* GetGizmoViewContext(UInteractiveGizmoManager* GizmoManager);` (scope `UE::GizmoUtil`) — Simple helper that gets the gizmo view context out of the context object store associated with a gizmo manager. Fires ensures if it does not find the expected objects along the way.
- L41 _prototype_ `bool UpdateCameraAxisSource(UGizmoConstantFrameAxisSource& CameraAxisSource, UInteractiveGizmoManager* GizmoManager, const FVector3d& AxisOrigin);` (scope `UE::GizmoUtil`) — Helper to update an axis source that is based on the camera location, called from tick.
- L53 _prototype_ `template <typename SubGizmoType> bool SetCommonSubGizmoProperties( SubGizmoType* Gizmo, const UE::GizmoUtil::FTransformSubGizmoCommonParams& Params, UE::GizmoUtil::FTransformSubGizmoSharedState* SharedState, UGizmoScaledAndUnscaledTransformSources*& TransformSourceOut);` (scope `UE::GizmoUtil`) — Helper that sets some common properties on sub gizmos, namely AxisSource, HitTarget, and StateTarget. Also returns a TransformSource, which typically gets wrapped up in a parameter source. Template because the properties it manipulates aren't part of a base class. Perhaps they should be, but we have not needed that yet, other than this.
- L63 _prototype_ `double ClampRayOrigin(const UGizmoViewContext* InViewContext, FVector& InOutRayOrigin, const FVector& InRayDirection, const double InMaxDepth = UE_LARGE_HALF_WORLD_MAX1);` (scope `UE::GizmoUtil`) — Helper to ensure that the ray origin is not too far in orthographic views to avoid numerical imprecision later @return the depth bias between the current ray origin and the updated one if the ray origin is greater than InMaxDepth

### `Source/Runtime/InteractiveToolsFramework/Private/InputBehaviorBindingComplexity.h` (Private)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace ITF` (scope `UE`)
- L5 _namespace_ `namespace Private` (scope `UE::ITF`)
- L8 _prototype_ `bool UseInputBindingComplexity();` (scope `UE::ITF::Private`)

### `Source/Runtime/InteractiveToolsFramework/Public/BaseBehaviors/AnyButtonInputBehavior.h` (Public)


#### class `UAnyButtonInputBehavior`  
`class UAnyButtonInputBehavior : public UInputBehavior`  
_L32-87_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInputBehavior`
- desc: UAnyButtonInputBehavior is a base behavior that provides a generic interface to a TargetButton on a physical Input Device. You can subclass UAnyButtonInputBehavior to write InputBehaviors that can work independent of a particular device type or button, by using the UAnyButtonInputBehavior functions below. The target device button is selected using the .ButtonNumber property, or you can override the relevant GetXButtonState() function if you need more control. @todo spatial controllers @todo support tablet fingers @todo support gamepad?
- L37 _public prototype_ `UAnyButtonInputBehavior();`
- L40 _public prototype_ `virtual EInputDevices GetSupportedDevices() override;` — Return set of devices supported by this behavior
- L43 _public prototype_ `virtual bool IsPressed(const FInputDeviceState& input);` — @return true if Target Button has been pressed this frame
- L46 _public prototype_ `virtual bool IsDown(const FInputDeviceState& input);` — @return true if Target Button is currently held down
- L49 _public prototype_ `virtual bool IsReleased(const FInputDeviceState& input);` — @return true if Target Button was released this frame
- L52 _public prototype_ `virtual bool IsDoubleClicked(const FInputDeviceState& input);` — @return true if Target Button was double clicked this frame
- L55 _public prototype_ `virtual FVector2D GetClickPoint(const FInputDeviceState& input);` — @return current 2D position of Target Device, or zero if device does not have 2D position
- L58 _public prototype_ `virtual FRay GetWorldRay(const FInputDeviceState& input);` — @return current 3D world ray for Target Device position
- L61 _public prototype_ `virtual FInputDeviceRay GetDeviceRay(const FInputDeviceState& input);` — @return current 3D world ray and optional 2D position for Target Device
- L64 _public prototype_ `EInputDevices GetActiveDevice() const;` — @return last-active supported Device
- L69 _public prototype_ `virtual void SetUseLeftMouseButton();` — Configure the target Mouse button to be the left button
- L71 _public prototype_ `virtual void SetUseMiddleMouseButton();` — Configure the target Mouse button to be the middle button
- L73 _public prototype_ `virtual void SetUseRightMouseButton();` — Configure the target Mouse button to be the right button
- L75 _public prototype_ `virtual void SetUseCustomMouseButton(TUniqueFunction<FDeviceButtonState(const FInputDeviceState& Input)>);` — Configure a custom target mouse button
- L80 _protected member_ `EInputDevices ActiveDevice;` — Which device is currently active
- L83 _protected member_ `TUniqueFunction<FDeviceButtonState(const FInputDeviceState& Input)> GetMouseButtonStateFunc;` — Returns FDeviceButtonState for target mouse button
- L86 _protected prototype_ `FDeviceButtonState GetButtonStateFunc(const FInputDeviceState& Input);` — Returns FDeviceButtonState for target active device button

### `Source/Runtime/InteractiveToolsFramework/Public/BaseBehaviors/BehaviorTargetInterfaces.h` (Public)


#### class `IModifierToggleBehaviorTarget`  
`class IModifierToggleBehaviorTarget`  
_L14-34_
- desc: IModifierToggleBehaviorTarget is an interface that InputBehaviors can use to notify a target about modifier toggle states (like shift key being down, etc). The meaning of the modifier ID is client-defined (generally provided to the InputBehavior in a registration step)
- L17 _public prototype_ `virtual ~IModifierToggleBehaviorTarget() = default;`
- L24 _public function_ `virtual void OnUpdateModifierState(int ModifierID, bool bIsOn)` — Notify target of current modifier state @param ModifierID client-defined integer that identifiers modifier @param bIsOn is modifier current on or off
- L31 _public function_ `virtual void OnForceEndCapture()` — Notify Target that capture is ending

#### class `IKeyInputBehaviorTarget`  
`class IKeyInputBehaviorTarget : public IModifierToggleBehaviorTarget`  
_L40-56_
- inherits: `IModifierToggleBehaviorTarget`
- desc: IKeyInputBehaviorTarget is an interface that InputBehaviors can use to notify a target about keyboard buttons toggling states, such as pressed or released.
- L43 _public prototype_ `virtual ~IKeyInputBehaviorTarget() = default;`
- L45 _public function_ `virtual void OnKeyPressed(const FKey& KeyID)`
- L49 _public function_ `virtual void OnKeyReleased(const FKey& KeyID)`
- L53 _public function_ `virtual void OnForceEndCapture()`

#### class `IClickBehaviorTarget`  
`class IClickBehaviorTarget : public IModifierToggleBehaviorTarget`  
_L63-81_
- inherits: `IModifierToggleBehaviorTarget`
- desc: Functions required to apply standard "Click" state machines to a target object. See USingleClickBehavior for an example of this kind of state machine.
- L66 _public prototype_ `virtual ~IClickBehaviorTarget() = default;`
- L73 _public prototype_ `virtual FInputRayHit IsHitByClick(const FInputDeviceRay& ClickPos) = 0;` — Test if target is hit by a click @param ClickPos device position/ray at click point @return hit information at this point
- L80 _public prototype_ `virtual void OnClicked(const FInputDeviceRay& ClickPos) = 0;` — Notify Target that click ocurred @param ClickPos device position/ray at click point

#### class `IClickDragBehaviorTarget`  
`class IClickDragBehaviorTarget : public IModifierToggleBehaviorTarget`  
_L90-125_
- inherits: `IModifierToggleBehaviorTarget`
- desc: Functions required to apply standard "Click-Drag" state machines to a target object. See UClickDragBehavior for an example of this kind of state machine.
- L93 _public prototype_ `virtual ~IClickDragBehaviorTarget() = default;`
- L100 _public prototype_ `virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& PressPos) = 0;` — Test if target can begin click-drag interaction at this point @param PressPos device position/ray at click point @return hit information at this point
- L107 _public prototype_ `virtual void OnClickPress(const FInputDeviceRay& PressPos) = 0;` — Notify Target that click press ocurred @param PressPos device position/ray at click point
- L113 _public prototype_ `virtual void OnClickDrag(const FInputDeviceRay& DragPos) = 0;` — Notify Target that input position has changed @param DragPos device position/ray at click point
- L119 _public prototype_ `virtual void OnClickRelease(const FInputDeviceRay& ReleasePos) = 0;` — Notify Target that click release occurred @param ReleasePos device position/ray at click point
- L124 _public prototype_ `virtual void OnTerminateDragSequence() = 0;` — Notify Target that click-drag sequence has been explicitly terminated (eg by escape key)

#### class `IMouseWheelBehaviorTarget`  
`class IMouseWheelBehaviorTarget : public IModifierToggleBehaviorTarget`  
_L131-158_
- inherits: `IModifierToggleBehaviorTarget`
- desc: Functions required to apply mouse wheel behavior
- L134 _public prototype_ `virtual ~IMouseWheelBehaviorTarget() = default;`
- L143 _public prototype_ `virtual FInputRayHit ShouldRespondToMouseWheel(const FInputDeviceRay& CurrentPos) = 0;` — The result's bHit property determines whether the mouse wheel action will be captured. (Perhaps the mouse wheel only does something when mousing over some part of a mesh) @param CurrentPos device position/ray at point where mouse wheel is engaged @return hit information at this point
- L150 _public prototype_ `virtual void OnMouseWheelScrollUp(const FInputDeviceRay& CurrentPos) = 0;` — @param CurrentPos device position/ray at point where mouse wheel is engaged
- L156 _public prototype_ `virtual void OnMouseWheelScrollDown(const FInputDeviceRay& CurrentPos) = 0;` — @param CurrentPos device position/ray at point where mouse wheel is engaged

#### class `IClickSequenceBehaviorTarget`  
`class IClickSequenceBehaviorTarget : public IModifierToggleBehaviorTarget`  
_L169-218_
- inherits: `IModifierToggleBehaviorTarget`
- desc: Target interface used by InputBehaviors that want to implement a multi-click sequence (eg such as drawing a polygon with multiple clicks)
- L172 _public prototype_ `virtual ~IClickSequenceBehaviorTarget() = default;`
- L178 _public function_ `virtual void OnBeginSequencePreview(const FInputDeviceRay& ClickPos)` — Notify Target device position has changed but a click sequence hasn't begun yet (eg for interactive previews) @param ClickPos device position/ray at click point
- L186 _public prototype_ `virtual bool CanBeginClickSequence(const FInputDeviceRay& ClickPos) = 0;` — Test if target would like to begin sequence based on this click. Gets checked both on mouse down and mouse up. @param ClickPos device position/ray at click point @return true if target wants to begin sequence
- L192 _public prototype_ `virtual void OnBeginClickSequence(const FInputDeviceRay& ClickPos) = 0;` — Notify Target about the first click in the sequence. @param ClickPos device position/ray at click point
- L198 _public function_ `virtual void OnNextSequencePreview(const FInputDeviceRay& ClickPos)` — Notify Target device position has changed but a click hasn't ocurred yet (eg for interactive previews) @param ClickPos device position/ray at click point
- L205 _public prototype_ `virtual bool OnNextSequenceClick(const FInputDeviceRay& ClickPos) = 0;` — Notify Target about next click in sqeuence @param ClickPos device position/ray at click point @return false if Target wants to terminate sequence
- L211 _public prototype_ `virtual void OnTerminateClickSequence() = 0;` — Notify Target that click sequence has been explicitly terminated (eg by escape key, cancel tool, etc). Also called if sequence is terminated from querying target with RequestAbortClickSequence().
- L217 _public function_ `virtual bool RequestAbortClickSequence()` — Target overrides this and returns true if it wants to abort click sequence. Behavior checks every update and if this ever returns true, terminates sequence

#### class `IHoverBehaviorTarget`  
`class IHoverBehaviorTarget : public IModifierToggleBehaviorTarget`  
_L229-253_
- inherits: `IModifierToggleBehaviorTarget`
- desc: IHoverBehaviorTarget allows Behaviors to notify Tools/etc about device event data in a generic way, without requiring that all Tools know about the concept of Hovering.
- L232 _public prototype_ `virtual ~IHoverBehaviorTarget() = default;`
- L237 _public prototype_ `virtual FInputRayHit BeginHoverSequenceHitTest(const FInputDeviceRay& PressPos) = 0;` — Do hover hit-test
- L242 _public prototype_ `virtual void OnBeginHover(const FInputDeviceRay& DevicePos) = 0;` — Initialize hover sequence at given position
- L247 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) = 0;` — Update active hover sequence with new input position
- L252 _public prototype_ `virtual void OnEndHover() = 0;` — Terminate active hover sequence

#### class `ITwoAxisPropertyEditBehaviorTarget`  
`class ITwoAxisPropertyEditBehaviorTarget`  
_L260-286_
- desc: ITwoAxisPropertyEditBehaviorTarget allows tools to expose properties to drag-based property edit behaviors.
- L279 _public prototype_ `virtual ~ITwoAxisPropertyEditBehaviorTarget() = default;`
- L281 _public prototype_ `virtual IPropertyInterface* GetHorizontalProperty() = 0;`
- L282 _public prototype_ `virtual IPropertyInterface* GetVerticalProperty() = 0;`
- L284 _public function_ `virtual FKey GetCaptureKey()`
- L285 _public function_ `virtual void PostDragUpdated()`

#### struct `ITwoAxisPropertyEditBehaviorTarget::IPropertyInterface`  
`struct IPropertyInterface`  
_L265-275_
- desc: IPropertyInterface encapsulates a virtual 'property' (which may or may not map to a single member or property)
- L267 _public prototype_ `virtual ~IPropertyInterface() = default;`
- L269 _public prototype_ `virtual FText GetName() = 0;` — Get a name for this virtual property (for display purposes).
- L270 _public prototype_ `virtual float GetValue() = 0;`
- L271 _public prototype_ `virtual void SetValue(float NewValue) = 0;`
- L272 _public function_ `virtual float GetEditRate()` — Scales how quickly this property is edited with respect to a fixed mouse movement.
- L273 _public function_ `virtual float MutateDelta(float Delta)` — Provides a hook to further augment the delta that is about to be applied to this property.
- L274 _public function_ `virtual bool IsEnabled()`

### `Source/Runtime/InteractiveToolsFramework/Public/BaseBehaviors/ClickDragBehavior.h` (Public)


#### class `UClickDragInputBehavior`  
`class UClickDragInputBehavior : public UAnyButtonInputBehavior`  
_L32-94_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnyButtonInputBehavior`
- desc: UClickDragInputBehavior implements a standard "button-click-drag"-style input behavior. An IClickDragBehaviorTarget instance must be provided which is manipulated by this behavior. The state machine works as follows: 1) on input-device-button-press, call Target::CanBeginClickDragSequence to determine if capture should begin 2) on input-device-move, call Target::OnClickDrag 3) on input-device-button-release, call Target::OnClickRelease If a ForceEndCapture occurs we call Target::OnTerminateDragSequence
- L37 _public prototype_ `UClickDragInputBehavior();`
- L42 _public member_ `FInputBehaviorModifierStates Modifiers;` — The modifier set for this behavior
- L48 _public prototype_ `virtual void Initialize(IClickDragBehaviorTarget* Target);` — Initialize this behavior with the given Target @param Target implementor of hit-test and on-clicked functions
- L54 _public member_ `TFunction<bool(const FInputDeviceState&)> ModifierCheckFunc = nullptr;` — WantsCapture() will only return capture request if this function returns true (or is null)
- L59 _public prototype_ `virtual FInputCapturePriority GetPriority() override;`
- L60 _public prototype_ `virtual FInputCaptureRequest WantsCapture(const FInputDeviceState& Input) override;`
- L61 _public prototype_ `virtual FInputCaptureUpdate BeginCapture(const FInputDeviceState& Input, EInputCaptureSide Side) override;`
- L62 _public prototype_ `virtual FInputCaptureUpdate UpdateCapture(const FInputDeviceState& Input, const FInputCaptureData& Data) override;`
- L63 _public prototype_ `virtual void ForceEndCapture(const FInputCaptureData& Data) override;`
- L71 _public member_ `bool bUpdateModifiersDuringDrag = false;` — `UPROPERTY()` — If true, then we will update Modifier states in UpdateCapture(). This defaults to false because in most cases during a capture you don't want this, eg in a brush interaction, if you have a shift-to-smooth modifier, you don't want to toggle this on/off during a sculpting stroke.
- L75 _protected member_ `IClickDragBehaviorTarget* Target;` — Click Target object
- L78 _protected member_ `bool bInClickDrag = false;` — set to true if we are in a capture
- L83 _protected prototype_ `virtual void OnClickPressInternal(const FInputDeviceState& Input, EInputCaptureSide Side);` — Internal function that forwards click evens to Target::OnClickPress, you can customize behavior here
- L88 _protected prototype_ `virtual void OnClickDragInternal(const FInputDeviceState& Input, const FInputCaptureData& Data);` — Internal function that forwards click evens to Target::OnClickDrag, you can customize behavior here
- L93 _protected prototype_ `virtual void OnClickReleaseInternal(const FInputDeviceState& Input, const FInputCaptureData& Data);` — Internal function that forwards click evens to Target::OnClickRelease, you can customize behavior here

#### class `ULocalClickDragInputBehavior`  
`class ULocalClickDragInputBehavior : public UClickDragInputBehavior, public IClickDragBehaviorTarget`  
_L106-163_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UClickDragInputBehavior,IClickDragBehaviorTarget`
- desc: ULocalClickDragInputBehavior is an implementation of UClickDragInputBehavior that also implements IClickDragBehaviorTarget directly, via a set of local lambda functions. To use/customize this class the client replaces the lambda functions with their own. This avoids having to create a second IClickDragBehaviorTarget implementation for trivial use-cases.
- L114 _public function_ `virtual void Initialize()` — Call this to initialize the class
- L120 _public function_ `TUniqueFunction<FInputRayHit(const FInputDeviceRay& PressPos)> CanBeginClickDragFunc = [](const FInputDeviceRay&)` — lambda implementation of CanBeginClickDragSequence
- L120 _public member_ `TUniqueFunction<FInputRayHit(const FInputDeviceRay& PressPos)> CanBeginClickDragFunc = [](const FInputDeviceRay&) { return FInputRayHit(); };` — lambda implementation of CanBeginClickDragSequence
- L123 _public function_ `TUniqueFunction<void(const FInputDeviceRay& PressPos)> OnClickPressFunc = [](const FInputDeviceRay&)` — lambda implementation of OnClickPress
- L123 _public member_ `TUniqueFunction<void(const FInputDeviceRay& PressPos)> OnClickPressFunc = [](const FInputDeviceRay&) {};` — lambda implementation of OnClickPress
- L126 _public function_ `TUniqueFunction<void(const FInputDeviceRay& PressPos)> OnClickDragFunc = [](const FInputDeviceRay&)` — lambda implementation of OnClickDrag
- L126 _public member_ `TUniqueFunction<void(const FInputDeviceRay& PressPos)> OnClickDragFunc = [](const FInputDeviceRay&) {};` — lambda implementation of OnClickDrag
- L129 _public function_ `TUniqueFunction<void(const FInputDeviceRay& ReleasePos)> OnClickReleaseFunc = [](const FInputDeviceRay&)` — lambda implementation of OnClickRelease
- L129 _public member_ `TUniqueFunction<void(const FInputDeviceRay& ReleasePos)> OnClickReleaseFunc = [](const FInputDeviceRay&) {};` — lambda implementation of OnClickRelease
- L132 _public function_ `TUniqueFunction<void()> OnTerminateFunc = []()` — lambda implementation of OnTerminateDragSequence
- L132 _public member_ `TUniqueFunction<void()> OnTerminateFunc = []() {};` — lambda implementation of OnTerminateDragSequence
- L139 _public function_ `virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& PressPos) override` — IClickDragBehaviorTarget implementation
- L144 _public function_ `virtual void OnClickPress(const FInputDeviceRay& PressPos) override`
- L149 _public function_ `virtual void OnClickDrag(const FInputDeviceRay& DragPos) override`
- L154 _public function_ `virtual void OnClickRelease(const FInputDeviceRay& ReleasePos) override`
- L159 _public function_ `virtual void OnTerminateDragSequence() override`

### `Source/Runtime/InteractiveToolsFramework/Public/BaseBehaviors/DoubleClickBehavior.h` (Public)


#### class `UDoubleClickInputBehavior`  
`class UDoubleClickInputBehavior : public USingleClickInputBehavior`  
_L37-46_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleClickInputBehavior`
- desc: UDoubleClickInputBehavior implements a standard "button-click"-style input behavior. The state machine works as follows: 1) on input-device-button-double-click, hit-test the target. If hit, begin capture 2) on input-device-button-release, hit-test the target. If hit, call Target::OnClicked(). If not hit, ignore click. The second hit-test is required to allow the click to be "cancelled" by moving away from the target. This is standard GUI behavior. You can disable this second hit test using the .HitTestOnRelease property. This is strongly discouraged. The hit-test and on-clicked functions are provided by a IClickBehaviorTarget instance. The expected sequence of mouse events for a double click is: a. MouseDown b. MouseUp c. MouseDoubleClick   <-- State machine starts here. d. MouseUp
- L42 _public prototype_ `UDoubleClickInputBehavior();`
- L45 _public prototype_ `virtual FInputCaptureRequest WantsCapture(const FInputDeviceState& Input) override;` — UInputBehavior implementation

#### class `ULocalDoubleClickInputBehavior`  
`class ULocalDoubleClickInputBehavior : public UDoubleClickInputBehavior, public IClickBehaviorTarget`  
_L54-94_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDoubleClickInputBehavior,IClickBehaviorTarget`
- desc: An implementation of UDoubleClickInputBehavior that also implements IClickBehaviorTarget directly, via a set of local lambda functions. To use/customize this class, the client replaces the lambda functions with their own. This avoids having to create a separate IClickBehaviorTarget implementation for trivial use-cases.
- L62 _public function_ `virtual void Initialize()` — Call this to initialize the class
- L68 _public function_ `TUniqueFunction<FInputRayHit(const FInputDeviceRay&)> IsHitByClickFunc = [](const FInputDeviceRay& ClickPos)` — lambda implementation of IsHitByClick
- L68 _public member_ `TUniqueFunction<FInputRayHit(const FInputDeviceRay&)> IsHitByClickFunc = [](const FInputDeviceRay& ClickPos) { return FInputRayHit(); };` — lambda implementation of IsHitByClick
- L71 _public function_ `TUniqueFunction<void(const FInputDeviceRay&)> OnClickedFunc = [](const FInputDeviceRay& ClickPos)` — lambda implementation of OnClicked
- L71 _public member_ `TUniqueFunction<void(const FInputDeviceRay&)> OnClickedFunc = [](const FInputDeviceRay& ClickPos) {};` — lambda implementation of OnClicked
- L74 _public function_ `TUniqueFunction< void(int, bool) > OnUpdateModifierStateFunc = [](int ModifierID, bool bIsOn)` — lambda implementation of OnUpdateModifierState
- L74 _public member_ `TUniqueFunction< void(int, bool) > OnUpdateModifierStateFunc = [](int ModifierID, bool bIsOn) {};` — lambda implementation of OnUpdateModifierState
- L79 _public function_ `virtual FInputRayHit IsHitByClick(const FInputDeviceRay& ClickPos) override`
- L84 _public function_ `virtual void OnClicked(const FInputDeviceRay& ClickPos) override`
- L90 _public function_ `virtual void OnUpdateModifierState(int ModifierID, bool bIsOn)` — IModifierToggleBehaviorTarget implementation

### `Source/Runtime/InteractiveToolsFramework/Public/BaseBehaviors/InputBehaviorModifierStates.h` (Public)


#### class `FInputBehaviorModifierStates`  
`class FInputBehaviorModifierStates`  
_L18-98_
- desc: FInputBehaviorModifierStates is an object that can be placed in an InputBehavior to allow users of the behavior to request that they be notified about modifier keys/buttons/etc state. We don't know ahead of time what might be used to determine modifier state, which input devices might be used, etc. So the user has to register (ModifierID,ModifierTestFunction) pairs. The behavior then calls UpdateModifiers() which will query each of the test functions and notify the target object about the state of the modifier.
- L21 _public typedef_ `typedef TFunction<bool(const FInputDeviceState&)> FModifierTestFunction;`
- L25 _protected member_ `TArray<int> ModifierIDs;` — List of modifier IDs that have been registered
- L27 _protected member_ `TMap<int, FModifierTestFunction> ModifierTests;` — The modifier test function for each ID
- L29 _protected member_ `TMap<int, bool> ModifierStates;` — The modifier states for each ID
- L38 _public function_ `void RegisterModifier(int ModifierID, const FModifierTestFunction& ModifierTest)` — Register a modifier ID and an associated test function @param ModifierID the modifier ID @param ModifierTest the test function
- L50 _public function_ `bool HasModifiers() const` — @return true if any modifiers have been registered
- L58 _public function_ `int32 GetActiveModifierCount() const` — @return The count of active modifiers
- L76 _public function_ `void UpdateModifiers(const FInputDeviceState& Input, IModifierToggleBehaviorTarget* ModifiersTarget)` — Look up the current state of each registered modifier and pass to the target @param Input the current input device state @param ModifiersTarget the target that is interested in the modifier values
- L90 _public function_ `void CacheModifierState(const FInputDeviceState& Input)` — Look up the current state of each registered modifier and cache their values. @param Input the current input device state

### `Source/Runtime/InteractiveToolsFramework/Public/BaseBehaviors/KeyAsModifierInputBehavior.h` (Public)


#### class `UKeyAsModifierInputBehavior`  
`class UKeyAsModifierInputBehavior : public UInputBehavior`  
_L30-72_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInputBehavior`
- desc: UKeyAsModifierInputBehavior converts a specific key press/release into a "Modifier" toggle via the IModifierToggleBehaviorTarget interface. It does not capture the key press; rather, it updates the modifier its WantsCapture call. This means that the modifier won't be updated if another behavior captures the keyboard.
- L35 _public prototype_ `UKeyAsModifierInputBehavior();`
- L37 _public function_ `virtual EInputDevices GetSupportedDevices() override`
- L48 _public prototype_ `virtual void Initialize(IModifierToggleBehaviorTarget* Target, int ModifierID, const FKey& ModifierKey);` — Initialize this behavior with the given Target @param Target implementor of modifier-toggle behavior @param ModifierID integer ID that identifiers the modifier toggle @param ModifierKey the key that will be used as the modifier toggle
- L56 _public prototype_ `void Initialize(IModifierToggleBehaviorTarget* TargetIn, int ModifierID, TFunction<bool(const FInputDeviceState&)> ModifierCheckFunc);` — Initialize this behavior with the given Target @param Target implementor of modifier-toggle behavior @param ModifierID integer ID that identifiers the modifier toggle @param ModifierCheckFunc the function that will be checked to set the the modifier.
- L59 _public prototype_ `virtual FInputCaptureRequest WantsCapture(const FInputDeviceState& Input) override;` — UInputBehavior implementation
- L60 _public prototype_ `virtual FInputCaptureUpdate BeginCapture(const FInputDeviceState& Input, EInputCaptureSide Side) override;`
- L61 _public prototype_ `virtual FInputCaptureUpdate UpdateCapture(const FInputDeviceState& Input, const FInputCaptureData& Data) override;`
- L62 _public prototype_ `virtual bool WantsForceEndCapture() override;`
- L63 _public prototype_ `virtual void ForceEndCapture(const FInputCaptureData& Data) override;`
- L68 _protected member_ `IModifierToggleBehaviorTarget* Target;` — Modifier Target object
- L71 _protected member_ `FInputBehaviorModifierStates Modifiers;` — Modifier set for this behavior, internally initialized with check on ModifierKey

#### class `UMouseButtonAsModifierInputBehavior`  
`class UMouseButtonAsModifierInputBehavior : public UKeyAsModifierInputBehavior`  
_L78-86_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UKeyAsModifierInputBehavior`
- desc: A version of UKeyAsModifierInputBehavior for mouse buttons
- L82 _private function_ `virtual EInputDevices GetSupportedDevices() override`

### `Source/Runtime/InteractiveToolsFramework/Public/BaseBehaviors/KeyInputBehavior.h` (Public)


#### class `UKeyInputBehavior`  
`class UKeyInputBehavior : public UInputBehavior`  
_L45-121_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInputBehavior`
- desc: UKeyInputBehavior provides a keyboard capturing behavior that works with single or multiple keys. Provided with a single key, the behavior triggers OnKeyPressed and OnKeyReleased events upon seeing the target key pressed down and released for the first time, ignoring any other key presses. When provided with multiple keys, the Behavior has variable behavior depending on whether bRequireAllKeys is set. If true, the behavior sequence is as follows: 1. Initiate capture when any of the target keys are pressed. 2. Continue capture until all target keys are pressed simultaneously 3. Upon seeing the last key to complete the full set of target keys, issue an OnKeyPressed for whichever key completed the requirement. 3b. If any of the target keys are released after the full set was pressed, issue an OnKeyReleased for whichever key was released, then end Capture. 4. If at any point all target keys are released after capture begins, end capture. If false, the behavior sequence is as follows: 1. Initiate capture when any of the target keys are pressed. 2. Continue capture while any of the target keys are still pressed. 3. Issue an OnKeyPressed for any target key pressed during the capture period. 4. Issue an OnKeyReleased for any target key released during the capture period. 5. If at any point all target keys are released, end capture.
- L50 _public prototype_ `UKeyInputBehavior();`
- L52 _public function_ `virtual EInputDevices GetSupportedDevices() override`
- L62 _public prototype_ `virtual void Initialize(IKeyInputBehaviorTarget* Target, const FKey& Key);` — Initialize this behavior with the given Target @param Target implementor of modifier-toggle behavior @param Key FKey that indicates the keyboard key for the behavior to watch for
- L69 _public prototype_ `virtual void Initialize(IKeyInputBehaviorTarget* Target, const TArray<FKey>& Keys);` — Initialize this behavior with the given Target @param Target implementor of modifier-toggle behavior @param Keys array of FKey that indicates the keyboard keys for the behavior to watch for
- L74 _public member_ `TFunction<bool(const FInputDeviceState&)> ModifierCheckFunc = nullptr;` — WantsCapture() will only return capture request if this function returns true (or is null)
- L77 _public prototype_ `virtual FInputCaptureRequest WantsCapture(const FInputDeviceState& Input) override;` — UInputBehavior implementation
- L78 _public prototype_ `virtual FInputCaptureUpdate BeginCapture(const FInputDeviceState& Input, EInputCaptureSide Side) override;`
- L79 _public prototype_ `virtual FInputCaptureUpdate UpdateCapture(const FInputDeviceState& Input, const FInputCaptureData& Data) override;`
- L80 _public prototype_ `virtual void ForceEndCapture(const FInputCaptureData& Data) override;`
- L81 _public prototype_ `virtual bool WantsForceEndCapture() override;`
- L86 _public prototype_ `bool IsKeyPressed(FKey InKey) const;` — @return Whether the given key is detected as pressed.
- L91 _public member_ `FInputBehaviorModifierStates Modifiers;` — The modifier set for this behavior
- L96 _public member_ `bool bRequireAllKeys = true;` — If true, behavior requires all keys provided at initialization to be active at the same time in order to count as a "key down" event. If false, any key in the list will trigger the key down event.
- L101 _public member_ `bool bAlwaysUpdateModifiers = false;` — If true, behavior will update modifiers also when not capturing. If false, modifiers will be updated only while capturing.
- L104 _protected prototype_ `virtual void OnKeyPressedInternal(const FInputDeviceState& Input);`
- L105 _protected prototype_ `virtual void OnKeyReleasedInternal(const FInputDeviceState& Input);`
- L108 _protected member_ `IKeyInputBehaviorTarget* Target;` — Modifier Target object
- L110 _protected member_ `TArray<FKey> TargetKeys;`
- L111 _protected member_ `TArray<bool> KeyActivations;`
- L114 _private prototype_ `void InitializeKeyActivations();`
- L115 _private prototype_ `bool IsTargetedKey(const FInputDeviceState& Input);`
- L116 _private prototype_ `bool UpdateActivations(const FInputDeviceState& Input, bool bEmitOnChange);`
- L117 _private prototype_ `bool IsAnyKeyPressed() const;`
- L118 _private prototype_ `bool AreAllKeysPressed() const;`
- L120 _private member_ `bool bAllKeysSeenPressed = false;`

### `Source/Runtime/InteractiveToolsFramework/Public/BaseBehaviors/MouseHoverBehavior.h` (Public)


#### class `UMouseHoverBehavior`  
`class UMouseHoverBehavior : public UInputBehavior`  
_L26-61_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInputBehavior`
- desc: Trivial InputBehavior that forwards InputBehavior hover events to a Target object via the IHoverBehaviorTarget interface.
- L31 _public prototype_ `UMouseHoverBehavior();`
- L36 _public member_ `FInputBehaviorModifierStates Modifiers;` — The modifier set for this behavior
- L38 _public prototype_ `virtual void Initialize(IHoverBehaviorTarget* Target);`
- L47 _public member_ `TFunction<bool(const FInputDeviceState&)> HoverModifierCheckFunc = nullptr;` — WantsHoverCapture() will only return capture request if this function returns true (or is null) Note that unlike click behaviors, hover behaviors continue to receive WantsCapture calls even when they hold capture (and end if they fail to request capture), so an active hover behavior will end if its HoverModifierCheckFunc returns false.
- L51 _public prototype_ `virtual EInputDevices GetSupportedDevices() override;`
- L53 _public prototype_ `virtual bool WantsHoverEvents() override;`
- L54 _public prototype_ `virtual FInputCaptureRequest WantsHoverCapture(const FInputDeviceState& InputState) override;`
- L55 _public prototype_ `virtual FInputCaptureUpdate BeginHoverCapture(const FInputDeviceState& InputState, EInputCaptureSide eSide) override;`
- L56 _public prototype_ `virtual FInputCaptureUpdate UpdateHoverCapture(const FInputDeviceState& InputState) override;`
- L57 _public prototype_ `virtual void EndHoverCapture() override;`
- L60 _protected member_ `IHoverBehaviorTarget* Target;`

#### class `ULocalMouseHoverBehavior`  
`class ULocalMouseHoverBehavior : public UMouseHoverBehavior, public IHoverBehaviorTarget`  
_L70-125_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMouseHoverBehavior,IHoverBehaviorTarget`
- desc: An implementation of UMouseHoverBehavior that also implements IHoverBehaviorTarget directly, via a set of local lambda functions. To use/customize this class, the client replaces the lambda functions with their own. This avoids having to create a separate IHoverBehaviorTarget implementation for trivial use-cases.
- L78 _public function_ `virtual void Initialize()` — Call this to initialize the class
- L84 _public function_ `TUniqueFunction<FInputRayHit(const FInputDeviceRay& PressPos)> BeginHitTestFunc = [](const FInputDeviceRay&)` — lambda implementation of BeginHoverSequenceHitTest
- L84 _public member_ `TUniqueFunction<FInputRayHit(const FInputDeviceRay& PressPos)> BeginHitTestFunc = [](const FInputDeviceRay&) { return FInputRayHit(); };` — lambda implementation of BeginHoverSequenceHitTest
- L87 _public function_ `TUniqueFunction<void(const FInputDeviceRay& PressPos)> OnBeginHoverFunc = [](const FInputDeviceRay&)` — lambda implementation of OnBeginHover
- L87 _public member_ `TUniqueFunction<void(const FInputDeviceRay& PressPos)> OnBeginHoverFunc = [](const FInputDeviceRay&) {};` — lambda implementation of OnBeginHover
- L90 _public function_ `TUniqueFunction<bool(const FInputDeviceRay& PressPos)> OnUpdateHoverFunc = [](const FInputDeviceRay&)` — lambda implementation of OnUpdateHover
- L90 _public member_ `TUniqueFunction<bool(const FInputDeviceRay& PressPos)> OnUpdateHoverFunc = [](const FInputDeviceRay&) { return false; };` — lambda implementation of OnUpdateHover
- L93 _public function_ `TUniqueFunction<void()> OnEndHoverFunc = []()` — lambda implementation of OnEndHover
- L93 _public member_ `TUniqueFunction<void()> OnEndHoverFunc = []() {};` — lambda implementation of OnEndHover
- L96 _public function_ `TUniqueFunction< void(int, bool) > OnUpdateModifierStateFunc = [](int ModifierID, bool bIsOn)` — lambda implementation of OnUpdateModifierState
- L96 _public member_ `TUniqueFunction< void(int, bool) > OnUpdateModifierStateFunc = [](int ModifierID, bool bIsOn) {};` — lambda implementation of OnUpdateModifierState
- L100 _public function_ `virtual FInputRayHit BeginHoverSequenceHitTest(const FInputDeviceRay& PressPos) override` — IHoverBehaviorTarget implementation
- L105 _public function_ `virtual void OnBeginHover(const FInputDeviceRay& DevicePos) override`
- L110 _public function_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) override`
- L115 _public function_ `virtual void OnEndHover() override`
- L121 _public function_ `virtual void OnUpdateModifierState(int ModifierID, bool bIsOn)` — IModifierToggleBehaviorTarget implementation

### `Source/Runtime/InteractiveToolsFramework/Public/BaseBehaviors/MouseWheelBehavior.h` (Public)


#### class `UMouseWheelInputBehavior`  
`class UMouseWheelInputBehavior : public UAnyButtonInputBehavior`  
_L20-57_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnyButtonInputBehavior`
- L25 _public prototype_ `UMouseWheelInputBehavior();`
- L31 _public prototype_ `virtual void Initialize(IMouseWheelBehaviorTarget* Target);` — Initialize this behavior with the given Target @param Target implementor of hit-test and on-clicked functions
- L37 _public member_ `TFunction<bool(const FInputDeviceState&)> ModifierCheckFunc = nullptr;` — WantsCapture() will only return capture request if this function returns true (or is null)
- L41 _public prototype_ `virtual FInputCaptureRequest WantsCapture(const FInputDeviceState& Input) override;` — UInputBehavior implementation
- L42 _public prototype_ `virtual FInputCaptureUpdate BeginCapture(const FInputDeviceState& Input, EInputCaptureSide eSide) override;`
- L43 _public prototype_ `virtual FInputCaptureUpdate UpdateCapture(const FInputDeviceState& Input, const FInputCaptureData& Data) override;`
- L44 _public prototype_ `virtual void ForceEndCapture(const FInputCaptureData& Data) override;`
- L49 _public member_ `FInputBehaviorModifierStates Modifiers;` — The modifier set for this behavior
- L55 _protected member_ `IMouseWheelBehaviorTarget* Target;`

### `Source/Runtime/InteractiveToolsFramework/Public/BaseBehaviors/MouseWheelModifierInputBehavior.h` (Public)


#### class `UMouseWheelModifierInputBehavior`  
`class UMouseWheelModifierInputBehavior : public UMouseWheelInputBehavior`  
_L14-20_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMouseWheelInputBehavior`
- L19 _public prototype_ `virtual FInputCaptureRequest WantsCapture(const FInputDeviceState& InputState) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API INTERACTIVETOOLSFRAMEWORK_API`

### `Source/Runtime/InteractiveToolsFramework/Public/BaseBehaviors/MultiClickSequenceInputBehavior.h` (Public)


#### class `UMultiClickSequenceInputBehavior`  
`class UMultiClickSequenceInputBehavior : public UAnyButtonInputBehavior`  
_L38-98_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnyButtonInputBehavior`
- desc: UMultiClickSequenceInputBehavior implements a generic multi-click-sequence input behavior. For example this behavior could be used to implement a multi-click polygon-drawing interaction. The internal state machine works as follows: 1) on input-device-button-press, check if target wants to begin sequence. If so, begin capture. 2) on button *release*, check if target wants to continue or terminate sequence a) if terminate, release capture b) if continue, do nothing (capture continues between presses) The target will receive "preview" notifications (basically hover) during updates where there is not a release. This can be used to (eg) update a rubber-band selection end point @todo it may be better to implement this as multiple captures, and use hover callbacks to do the between-capture previews. holding capture across mouse release is not ideal.
- L43 _public prototype_ `UMultiClickSequenceInputBehavior();`
- L48 _public member_ `FInputBehaviorModifierStates Modifiers;` — The modifier set for this behavior
- L54 _public prototype_ `virtual void Initialize(IClickSequenceBehaviorTarget* Target);` — Initialize this behavior with the given Target @param Target implementor of hit-test and on-clicked functions
- L60 _public member_ `TFunction<bool(const FInputDeviceState&)> ModifierCheckFunc = nullptr;` — The first click will only be accepted if this function returns true (or is null)
- L69 _public member_ `TFunction<bool(const FInputDeviceState&)> HoverModifierCheckFunc = nullptr;` — WantsHoverCapture() will only return capture request if this function returns true (or is null) Note that unlike click behaviors, hover behaviors continue to receive WantsCapture calls even when they hold capture (and end if they fail to request capture), so an active hover behavior will end if its HoverModifierCheckFunc returns false.
- L73 _public prototype_ `virtual FInputCaptureRequest WantsCapture(const FInputDeviceState& Input) override;`
- L74 _public prototype_ `virtual FInputCaptureUpdate BeginCapture(const FInputDeviceState& Input, EInputCaptureSide eSide) override;`
- L75 _public prototype_ `virtual FInputCaptureUpdate UpdateCapture(const FInputDeviceState& Input, const FInputCaptureData& Data) override;`
- L76 _public prototype_ `virtual void ForceEndCapture(const FInputCaptureData& Data) override;`
- L78 _public prototype_ `virtual bool WantsHoverEvents() override;`
- L79 _public prototype_ `virtual FInputCaptureRequest WantsHoverCapture(const FInputDeviceState& InputState) override;`
- L80 _public prototype_ `virtual FInputCaptureUpdate BeginHoverCapture(const FInputDeviceState& InputState, EInputCaptureSide eSide) override;`
- L81 _public prototype_ `virtual FInputCaptureUpdate UpdateHoverCapture(const FInputDeviceState& InputState) override;`
- L82 _public prototype_ `virtual void EndHoverCapture() override;`
- L95 _protected member_ `IClickSequenceBehaviorTarget* Target;` — Click Target object
- L97 _protected member_ `ESequenceState State = ESequenceState::NotStarted;`

#### enum `UMultiClickSequenceInputBehavior::ESequenceState`  
`enum class ESequenceState`  
_L88-92_
- L90 _public enumerator_ `NotStarted`
- L91 _public enumerator_ `WaitingForNextClick`

### `Source/Runtime/InteractiveToolsFramework/Public/BaseBehaviors/SingleClickBehavior.h` (Public)


#### class `USingleClickInputBehavior`  
`class USingleClickInputBehavior : public UAnyButtonInputBehavior`  
_L33-81_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnyButtonInputBehavior`
- desc: USingleClickInputBehavior implements a standard "button-click"-style input behavior. The state machine works as follows: 1) on input-device-button-press, hit-test the target. If hit, begin capture 2) on input-device-button-release, hit-test the target. If hit, call Target::OnClicked(). If not hit, ignore click. The second hit-test is required to allow the click to be "cancelled" by moving away from the target. This is standard GUI behavior. You can disable this second hit test using the .HitTestOnRelease property. This is strongly discouraged. The hit-test and on-clicked functions are provided by a IClickBehaviorTarget instance.
- L38 _public prototype_ `USingleClickInputBehavior();`
- L44 _public prototype_ `virtual void Initialize(IClickBehaviorTarget* Target);` — Initialize this behavior with the given Target @param Target implementor of hit-test and on-clicked functions
- L50 _public member_ `TFunction<bool(const FInputDeviceState&)> ModifierCheckFunc = nullptr;` — WantsCapture() will only return capture request if this function returns true (or is null)
- L55 _public prototype_ `virtual FInputCapturePriority GetPriority() override;`
- L56 _public prototype_ `virtual FInputCaptureRequest WantsCapture(const FInputDeviceState& Input) override;`
- L57 _public prototype_ `virtual FInputCaptureUpdate BeginCapture(const FInputDeviceState& Input, EInputCaptureSide eSide) override;`
- L58 _public prototype_ `virtual FInputCaptureUpdate UpdateCapture(const FInputDeviceState& Input, const FInputCaptureData& Data) override;`
- L59 _public prototype_ `virtual void ForceEndCapture(const FInputCaptureData& Data) override;`
- L65 _public member_ `bool HitTestOnRelease;` — `UPROPERTY()` — Hit-test is repeated on release (standard behavior). If false,
- L70 _public member_ `FInputBehaviorModifierStates Modifiers;` — The modifier set for this behavior
- L75 _protected member_ `IClickBehaviorTarget* Target;` — Click Target object
- L80 _protected prototype_ `virtual void Clicked(const FInputDeviceState& Input, const FInputCaptureData& Data);` — Internal function that forwards click evens to Target::OnClicked, you can customize behavior here

#### class `ULocalSingleClickInputBehavior`  
`class ULocalSingleClickInputBehavior : public USingleClickInputBehavior, public IClickBehaviorTarget`  
_L89-129_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleClickInputBehavior,IClickBehaviorTarget`
- desc: An implementation of USingleClickInputBehavior that also implements IClickBehaviorTarget directly, via a set of local lambda functions. To use/customize this class, the client replaces the lambda functions with their own. This avoids having to create a separate IClickBehaviorTarget implementation for trivial use-cases.
- L97 _public function_ `virtual void Initialize()` — Call this to initialize the class
- L103 _public function_ `TUniqueFunction<FInputRayHit(const FInputDeviceRay&)> IsHitByClickFunc = [](const FInputDeviceRay& ClickPos)` — lambda implementation of IsHitByClick
- L103 _public member_ `TUniqueFunction<FInputRayHit(const FInputDeviceRay&)> IsHitByClickFunc = [](const FInputDeviceRay& ClickPos) { return FInputRayHit(); };` — lambda implementation of IsHitByClick
- L106 _public function_ `TUniqueFunction<void(const FInputDeviceRay&)> OnClickedFunc = [](const FInputDeviceRay& ClickPos)` — lambda implementation of OnClicked
- L106 _public member_ `TUniqueFunction<void(const FInputDeviceRay&)> OnClickedFunc = [](const FInputDeviceRay& ClickPos) {};` — lambda implementation of OnClicked
- L109 _public function_ `TUniqueFunction< void(int, bool) > OnUpdateModifierStateFunc = [](int ModifierID, bool bIsOn)` — lambda implementation of OnUpdateModifierState
- L109 _public member_ `TUniqueFunction< void(int, bool) > OnUpdateModifierStateFunc = [](int ModifierID, bool bIsOn) {};` — lambda implementation of OnUpdateModifierState
- L114 _public function_ `virtual FInputRayHit IsHitByClick(const FInputDeviceRay& ClickPos) override`
- L119 _public function_ `virtual void OnClicked(const FInputDeviceRay& ClickPos) override`
- L125 _public function_ `virtual void OnUpdateModifierState(int ModifierID, bool bIsOn)` — IModifierToggleBehaviorTarget implementation

### `Source/Runtime/InteractiveToolsFramework/Public/BaseBehaviors/SingleClickOrDragBehavior.h` (Public)


#### class `USingleClickOrDragInputBehavior`  
`class USingleClickOrDragInputBehavior : public UAnyButtonInputBehavior`  
_L41-134_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnyButtonInputBehavior`
- desc: USingleClickOrDragInputBehavior is a combination of a USingleClickBehavior and UClickDragBehavior, and allows for the common UI interaction where a click-and-release does one action, but if the mouse is moved, then a drag interaction is started. For example click-to-select is often combined with a drag-marquee-rectangle in this way. This can be directly implemented with a UClickDragBehavior but requires the client to (eg) detect movement thresholds, etc. This class encapsulates all that state/logic. The .ClickDistanceThreshold parameter determines how far the mouse must move (in whatever device units are in use) to switch from a click to drag interaction The .bBeginDragIfClickTargetNotHit parameter determines if the drag interaction will be immediately initiated if the initial 'click' mouse-down does not hit a valid clickable target. Defaults to true. The hit-test and on-clicked functions are provided by a IClickBehaviorTarget instance, while an IClickDragBehaviorTarget provides the can-click-drag/begin-drag/update-drag/end-drag functionality.
- L50 _public member_ `FInputBehaviorModifierStates Modifiers;` — The modifier set for this behavior
- L56 _public prototype_ `virtual void Initialize(IClickBehaviorTarget* ClickTarget, IClickDragBehaviorTarget* DragTarget);` — Set the targets for Click and Drag interactions
- L61 _public prototype_ `virtual void SetDragTarget(IClickDragBehaviorTarget* DragTarget);` — Change the Drag BehaviorTarget
- L67 _public member_ `TFunction<bool(const FInputDeviceState&)> ModifierCheckFunc = nullptr;` — WantsCapture() will only return capture request if this function returns true (or is null)
- L72 _public prototype_ `virtual FInputCapturePriority GetPriority() override;`
- L73 _public prototype_ `virtual FInputCaptureRequest WantsCapture(const FInputDeviceState& Input) override;`
- L74 _public prototype_ `virtual FInputCaptureUpdate BeginCapture(const FInputDeviceState& Input, EInputCaptureSide eSide) override;`
- L75 _public prototype_ `virtual FInputCaptureUpdate UpdateCapture(const FInputDeviceState& Input, const FInputCaptureData& Data) override;`
- L76 _public prototype_ `virtual void ForceEndCapture(const FInputCaptureData& Data) override;`
- L82 _public member_ `bool bBeginDragIfClickTargetNotHit = true;` — `UPROPERTY()` — If true (default), then if the click-mouse-down does not hit a valid click target (determined by IClickBehaviorTarget::IsHitByClick), then the Drag will be initiated
- L87 _public member_ `float ClickDistanceThreshold = 5.0;` — `UPROPERTY()` — If the device moves more than this distance in 2D (pixel?) units, the interaction switches from click to drag
- L92 _protected member_ `IClickBehaviorTarget* ClickTarget;` — Click Target object
- L95 _protected member_ `IClickDragBehaviorTarget* DragTarget;` — Drag Target object
- L98 _protected member_ `FVector2D MouseDownPosition2D;` — Click-down position, to determine if mouse has moved far enough to swap to drag interaction
- L99 _protected member_ `FRay MouseDownRay;`
- L102 _protected member_ `EInputCaptureSide CaptureSide;` — Device capture
- L105 _protected member_ `bool bInDrag = false;` — set to true if we are in an active drag capture, eg after rejecting possible click
- L111 _protected member_ `bool bImmediatelyBeginDragInBeginCapture = false;` — flag used to communicate between WantsCapture and BeginCapture
- L116 _protected prototype_ `virtual void OnClickedInternal(const FInputDeviceState& Input, const FInputCaptureData& Data);` — Internal function that forwards click evens to ClickTarget::OnClicked, you can customize behavior here
- L121 _protected prototype_ `virtual void OnClickDragPressInternal(const FInputDeviceState& Input, EInputCaptureSide Side);` — Internal function that forwards click evens to DragTarget::OnClickPress, you can customize behavior here
- L126 _protected prototype_ `virtual void OnClickDragInternal(const FInputDeviceState& Input, const FInputCaptureData& Data);` — Internal function that forwards click evens to DragTarget::OnClickDrag, you can customize behavior here
- L131 _protected prototype_ `virtual void OnClickDragReleaseInternal(const FInputDeviceState& Input, const FInputCaptureData& Data);` — Internal function that forwards click evens to DragTarget::OnClickRelease, you can customize behavior here

### `Source/Runtime/InteractiveToolsFramework/Public/BaseBehaviors/SingleKeyCaptureBehavior.h` (Public)


#### class `USingleKeyCaptureBehavior`  
`class USingleKeyCaptureBehavior : public UInputBehavior`  
_L28-77_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInputBehavior`
- desc: USingleKeyCaptureBehavior captures a key press and routes it to target via the IModifierToggleBehaviorTarget interface. If you want similar behavior without actually capturing the key, you should use UKeyAsModifierInputBehavior.
- L33 _public prototype_ `USingleKeyCaptureBehavior();`
- L35 _public function_ `virtual EInputDevices GetSupportedDevices() override`
- L49 _public prototype_ `virtual void Initialize(IModifierToggleBehaviorTarget* Target, int ModifierID, const FKey& ModifierKey);` — Initialize this behavior with the given Target. Note that though it interacts through the IModifierToggleBehaviorTarget interface, the modifier here captures keyboard input, unlike the modifiers in UKeyAsMOdifierInputBehavior and other places. @param Target implementor of IModifierToggleBehaviorTarget @param ModifierID integer ID that identifiers the modifier toggle @param ModifierKey the key that will be used as the modifier toggle
- L55 _public member_ `TFunction<bool(const FInputDeviceState&)> ModifierCheckFunc = nullptr;` — WantsCapture() will only return capture request if this function returns true (or is null) Intended to be used for alt/ctrl/cmd/shift modifiers on the main key
- L59 _public prototype_ `virtual FInputCaptureRequest WantsCapture(const FInputDeviceState& Input) override;`
- L60 _public prototype_ `virtual FInputCaptureUpdate BeginCapture(const FInputDeviceState& Input, EInputCaptureSide Side) override;`
- L61 _public prototype_ `virtual FInputCaptureUpdate UpdateCapture(const FInputDeviceState& Input, const FInputCaptureData& Data) override;`
- L62 _public prototype_ `virtual void ForceEndCapture(const FInputCaptureData& Data) override;`
- L67 _protected member_ `IModifierToggleBehaviorTarget* Target;` — Modifier Target object
- L70 _protected member_ `FKey ModifierKey;` — Key that is used as modifier
- L73 _protected member_ `FInputBehaviorModifierStates Modifiers;` — Modifier set for this behavior, internally initialized with check on ModifierKey
- L76 _protected member_ `FKey PressedButton;` — The key that was pressed to activate capture

### `Source/Runtime/InteractiveToolsFramework/Public/BaseBehaviors/TwoAxisPropertyEditBehavior.h` (Public)


#### class `UTwoAxisPropertyEditInputBehavior`  
`class UTwoAxisPropertyEditInputBehavior : public UInputBehavior`  
_L19-77_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInputBehavior`
- desc: A behavior that captures a keyboard hotkey to enter a property adjustment sub-mode while the key is pressed. In this sub-mode, click-dragging the mouse will begin updating the properties specified by the behavior target.
- L25 _public prototype_ `void Initialize(ITwoAxisPropertyEditBehaviorTarget* InTarget);`
- L28 _public prototype_ `void ResetOrigin(FVector2D InScreenPosition, bool bHorizontalAdjust = true, bool bResetStartOrigin = false);` — Used to define the initial adjustment frame or to update the current reference point alternating between editing the 2 properties.
- L29 _public prototype_ `void DrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI) const;`
- L30 _public function_ `bool IsEditing() const`
- L34 _private prototype_ `void OnDragStart(FVector2D InScreenPosition);`
- L35 _private prototype_ `void OnDragUpdate(FVector2D InScreenPosition);`
- L36 _private prototype_ `void OnDragEnd();`
- L37 _private prototype_ `void ResetDragState();`
- L41 _private function_ `virtual EInputDevices GetSupportedDevices() override` — UInputBehavior implementation Routes input to the device specific handler functions.
- L42 _private prototype_ `virtual FInputCaptureRequest WantsCapture(const FInputDeviceState& InputState) override;`
- L43 _private prototype_ `virtual FInputCaptureUpdate BeginCapture(const FInputDeviceState& InputState, EInputCaptureSide eSide) override;`
- L44 _private prototype_ `virtual FInputCaptureUpdate UpdateCapture(const FInputDeviceState& InputState, const FInputCaptureData& CaptureData) override;`
- L45 _private prototype_ `virtual void ForceEndCapture(const FInputCaptureData& CaptureData) override;`
- L49 _private prototype_ `FInputCaptureRequest WantsMouseCapture(const FInputDeviceState& InputState);` — Mouse input handling - In these functions we assume input is from mouse device. This code is responsible for invoking OnDrag* functions at the proper times.
- L50 _private prototype_ `FInputCaptureUpdate BeginMouseCapture(const FInputDeviceState& InputState, EInputCaptureSide eSide);`
- L51 _private prototype_ `FInputCaptureUpdate UpdateMouseCapture(const FInputDeviceState& InputState, const FInputCaptureData& CaptureData);`
- L52 _private prototype_ `bool IsMousePressed(const FInputDeviceState& InputState) const;`
- L56 _private prototype_ `FInputCaptureRequest WantsKeyboardCapture(const FInputDeviceState& InputState);` — Keyboard input handling - In these functions we assume input is from keyboard device. This code is responsible for keeping bKeyPressed in the proper state.
- L57 _private prototype_ `FInputCaptureUpdate BeginKeyboardCapture(const FInputDeviceState& InputState, EInputCaptureSide eSide);`
- L58 _private prototype_ `FInputCaptureUpdate UpdateKeyboardCapture(const FInputDeviceState& InputState, const FInputCaptureData& CaptureData);`
- L59 _private prototype_ `bool IsKeyboardPressed(const FInputDeviceState& InputState) const;`
- L64 _private member_ `bool bInDrag = false;` — These 2 bools reflect which input we are currently capturing.
- L65 _private member_ `bool bKeyPressed = false;`
- L74 _private member_ `} State;` — Only valid if bInDrag is true
- L76 _private member_ `ITwoAxisPropertyEditBehaviorTarget* Target = nullptr;`

#### struct `UTwoAxisPropertyEditInputBehavior::FDragState`  
`struct FDragState`  
_L68-74_
- desc: Data that is only valid while in a drag (while bInDrag is true13).
- L70 _public member_ `float StartValue = 0.f;` — Cached initial values of the property being actively edited.
- L71 _public member_ `FVector2D StartOrigin;` — The screen space coordinate of the brush when the drag started.
- L72 _public member_ `FVector2D CurrentOrigin;` — The screen space coordinate of the origin of the current adjustment. Reset when changing between horizontal and vertical adjustment.
- L73 _public member_ `bool bAdjustingHorizontally = true;`

#### class `ULocalTwoAxisPropertyEditInputBehavior`  
`class ULocalTwoAxisPropertyEditInputBehavior : public UTwoAxisPropertyEditInputBehavior, public ITwoAxisPropertyEditBehaviorTarget`  
_L86-145_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTwoAxisPropertyEditInputBehavior,ITwoAxisPropertyEditBehaviorTarget`
- desc: Variant of the base behavior which allows tools to use lambda functions instead of explicitly defining a behavior target.
- L127 _public function_ `void Initialize()`
- L132 _public member_ `FPropertyInterface HorizontalProperty;`
- L133 _public member_ `FPropertyInterface VerticalProperty;`
- L134 _public function_ `TUniqueFunction<FKey()> GetCaptureKeyFunc = []()`
- L134 _public member_ `TUniqueFunction<FKey()> GetCaptureKeyFunc = [](){ return EKeys::B; };`
- L135 _public member_ `FSimpleMulticastDelegate OnDragUpdated;`
- L141 _private function_ `virtual IPropertyInterface* GetHorizontalProperty() override`
- L142 _private function_ `virtual IPropertyInterface* GetVerticalProperty() override`
- L143 _private function_ `virtual FKey GetCaptureKey() override`
- L144 _private function_ `virtual void PostDragUpdated() override`

#### struct `ULocalTwoAxisPropertyEditInputBehavior::FPropertyInterface`  
`struct FPropertyInterface : public IPropertyInterface`  
_L93-122_
- inherits: `IPropertyInterface`
- desc: Lambda implementation of IPropertyInterface
- L95 _public typedef_ `typedef TUniqueFunction<float(void)> FGetValueSignature;`
- L96 _public typedef_ `typedef TUniqueFunction<void(float)> FSetValueSignature;`
- L97 _public typedef_ `typedef TUniqueFunction<float(float)> FMutateDeltaSignature;`
- L99 _public member_ `FGetValueSignature GetValueFunc;`
- L100 _public member_ `FSetValueSignature SetValueFunc;`
- L101 _public function_ `FMutateDeltaSignature MutateDeltaFunc = [](float Delta)`
- L101 _public member_ `FMutateDeltaSignature MutateDeltaFunc = [](float Delta){ return Delta; };`
- L103 _public member_ `FText Name;`
- L104 _public member_ `float EditRate = 0.002f;`
- L105 _public member_ `bool bEnabled = false;`
- L107 _public function_ `bool IsValid() const`
- L116 _private function_ `virtual FText GetName() override`
- L117 _private function_ `virtual float GetValue() override`
- L118 _private function_ `virtual void SetValue(float NewValue) override`
- L119 _private function_ `virtual float GetEditRate() override`
- L120 _private function_ `virtual float MutateDelta(float Delta) override`
- L121 _private function_ `virtual bool IsEnabled() override`

### `Source/Runtime/InteractiveToolsFramework/Public/BaseBehaviors/Widgets/WidgetBaseBehavior.h` (Public)


#### class `UWidgetBaseBehavior`  
`class UWidgetBaseBehavior : public UInterface`  
_L19-22_
- reflection: `UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`
- desc: IWidgetBaseBehavior is an interface for tools that can modify / extend various step of a widget. If implementing this interface, please consider incrementing the LayerId if needed when overriding OnPaint.

#### class `IWidgetBaseBehavior`  
`class IWidgetBaseBehavior`  
_L24-42_
- L30 _public prototype_ `virtual bool OnKeyChar(const FGeometry& MyGeometry, const FCharacterEvent& InCharacterEvent);`
- L31 _public prototype_ `virtual bool OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);`
- L32 _public prototype_ `virtual bool OnKeyUp(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);`
- L33 _public prototype_ `virtual bool OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L34 _public prototype_ `virtual bool OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L35 _public prototype_ `virtual bool OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L36 _public prototype_ `virtual bool OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L37 _public prototype_ `virtual bool OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent);`
- L38 _public prototype_ `virtual bool OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L39 _public prototype_ `virtual void OnMouseCaptureLost(const FCaptureLostEvent& CaptureLostEvent);`
- L40 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const;`

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/AxisAngleGizmo.h` (Public)


#### class `UAxisAngleGizmoBuilder`  
`class UAxisAngleGizmoBuilder : public UInteractiveGizmoBuilder`  
_L36-42_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveGizmoBuilder`
- L41 _public prototype_ `virtual UInteractiveGizmo* BuildGizmo(const FToolBuilderState& SceneState) const override;`

#### class `UAxisAngleGizmo`  
`class UAxisAngleGizmo : public UInteractiveGizmo, public IClickDragBehaviorTarget, public IHoverBehaviorTarget`  
_L49-164_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveGizmo,IClickDragBehaviorTarget,IHoverBehaviorTarget`
- L58 _public prototype_ `bool InitializeAsRotateGizmo( const UE::GizmoUtil::FTransformSubGizmoCommonParams& InitializationParams, UE::GizmoUtil::FTransformSubGizmoSharedState* SharedState);` — Helper that initializes AxisSource, AngleSource, HitTarget, and StateTarget for the common case of being used to control the rotation of a transform. Safe to use for reinitialization.
- L64 _public prototype_ `virtual void Setup() override;`
- L68 _public prototype_ `virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& PressPos) override;`
- L69 _public prototype_ `virtual void OnClickPress(const FInputDeviceRay& PressPos) override;`
- L70 _public prototype_ `virtual void OnClickDrag(const FInputDeviceRay& DragPos) override;`
- L71 _public prototype_ `virtual void OnClickRelease(const FInputDeviceRay& ReleasePos) override;`
- L72 _public prototype_ `virtual void OnTerminateDragSequence() override;`
- L75 _public prototype_ `virtual FInputRayHit BeginHoverSequenceHitTest(const FInputDeviceRay& PressPos) override;` — IHoverBehaviorTarget implementation
- L76 _public prototype_ `virtual void OnBeginHover(const FInputDeviceRay& DevicePos) override;`
- L77 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) override;`
- L78 _public prototype_ `virtual void OnEndHover() override;`
- L81 _public prototype_ `virtual void OnUpdateModifierState(int ModifierID, bool bIsOn) override;` — IModifierToggleBehaviorTarget implementation (inherited via IClickDragBehaviorTarget)
- L88 _public member_ `TScriptInterface<IGizmoAxisSource> AxisSource;` — `UPROPERTY()`
- L91 _public member_ `TScriptInterface<IGizmoFloatParameterSource> AngleSource;` — `UPROPERTY()`
- L94 _public member_ `TScriptInterface<IGizmoClickTarget> HitTarget;` — `UPROPERTY()`
- L97 _public member_ `TScriptInterface<IGizmoStateTarget> StateTarget;` — `UPROPERTY()`
- L101 _public member_ `TObjectPtr<UClickDragInputBehavior> MouseBehavior;` — `UPROPERTY()` — The mouse click behavior of the gizmo is accessible so that it can be modified to use different mouse keys.
- L107 _public function_ `TUniqueFunction<bool()> ShouldUseCustomDestinationFunc = []()` — This gets checked to see if we should use the custom ray caster to get a destination point for the gizmo, rather than grabbing the intersection with the gizmo plane.
- L107 _public member_ `TUniqueFunction<bool()> ShouldUseCustomDestinationFunc = []() {return false; };` — This gets checked to see if we should use the custom ray caster to get a destination point for the gizmo, rather than grabbing the intersection with the gizmo plane.
- L125 _public member_ `TUniqueFunction<bool(const FCustomDestinationParams& WorldRay, FVector& OutputPoint)> CustomDestinationFunc = [](const FCustomDestinationParams& Params, FVector& OutputPoint) { return false; };` — If ShouldUseCustomDestinationFunc() returns true, this function is used to get a destination point, and the output parameter is picked in such a way that the closest axis in the plane of the gizmo (the positive or negative x or y, if we're rotating around z, for instance) moves to the closest point in the plane to the destination point. Used, for instance, for aligning to items in the scene.
- L126 _public function_ `[](const FCustomDestinationParams& Params, FVector& OutputPoint)`
- L130 _public member_ `bool bInInteraction = false;` — `UPROPERTY()`
- L133 _public member_ `FVector RotationOrigin;` — `UPROPERTY()`
- L136 _public member_ `FVector RotationAxis;` — `UPROPERTY()`
- L139 _public member_ `FVector RotationPlaneX;` — `UPROPERTY()`
- L142 _public member_ `FVector RotationPlaneY;` — `UPROPERTY()`
- L146 _public member_ `FVector InteractionStartPoint;` — `UPROPERTY()`
- L149 _public member_ `FVector InteractionCurPoint;` — `UPROPERTY()`
- L152 _public member_ `float InteractionStartAngle;` — `UPROPERTY()`
- L155 _public member_ `float InteractionCurAngle;` — `UPROPERTY()`
- L158 _protected member_ `FVector LastHitPosition;`
- L159 _protected member_ `float InitialTargetAngle;`
- L163 _protected member_ `float ClosestAxisStartAngle;` — The angle of the closest axis in the plane of the angle gizmo (will be 0, pi/2, pi, or 3pi/2). Used for snapping the nearest axis to a ray cast point when using CustomDestinationRayCaster.

#### struct `UAxisAngleGizmo::FCustomDestinationParams`  
`struct FCustomDestinationParams`  
_L109-116_
- L115 _public member_ `const FRay* WorldRay = nullptr;` — Right now we use the custom destination function for aligning to items in the scene, which we just need the world ray for. If we want to use functions that use other inputs as the basis for the destination, we would add those parameters here and would make sure that the gizmo passes them in.

#### Free symbols / members of external scopes

- L29 _namespace_ `namespace UE`
- L29 _namespace_ `namespace GizmoUtil` (scope `UE`)

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/AxisPositionGizmo.h` (Public)


#### class `UAxisPositionGizmoBuilder`  
`class UAxisPositionGizmoBuilder : public UInteractiveGizmoBuilder`  
_L37-43_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveGizmoBuilder`
- L42 _public prototype_ `virtual UInteractiveGizmo* BuildGizmo(const FToolBuilderState& SceneState) const override;`

#### class `UAxisPositionGizmo`  
`class UAxisPositionGizmo : public UInteractiveGizmo, public IClickDragBehaviorTarget, public IHoverBehaviorTarget`  
_L63-210_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveGizmo,IClickDragBehaviorTarget,IHoverBehaviorTarget`
- desc: UAxisPositionGizmo implements a gizmo interaction where 1D parameter value is manipulated by dragging a point on a 3D line/axis in space. The 3D point is converted to the axis parameter at the nearest point, giving us the 1D parameter value. As with other base gizmos, this class only implements the interaction. The visual aspect of the gizmo, the axis, and the parameter storage are all provided externally. The axis direction+origin is provided by an IGizmoAxisSource. The interaction target (ie the thing you have to click on to start the dragging interaction) is provided by an IGizmoClickTarget. The new 1D parameter value is sent to an IGizmoFloatParameterSource Internally a UClickDragInputBehavior is used to handle mouse input, configured in ::Setup()
- L72 _public prototype_ `bool InitializeAsTranslateGizmo( const UE::GizmoUtil::FTransformSubGizmoCommonParams& InitializationParams, UE::GizmoUtil::FTransformSubGizmoSharedState* SharedState);` — Helper that initializes AxisSource, ParameterSource, HitTarget, and StateTarget for the common case of being used to control the translation of a transform. Safe to use for reinitialization.
- L79 _public prototype_ `bool InitializeAsScaleGizmo( const UE::GizmoUtil::FTransformSubGizmoCommonParams& InitializationParams, bool bDisallowNegativeScaling, UE::GizmoUtil::FTransformSubGizmoSharedState* SharedState);` — Helper that initializes AxisSource, ParameterSource, HitTarget, and StateTarget for the common case of being used to control the scale of a transform. Safe to use for reinitialization.
- L86 _public prototype_ `virtual void Setup() override;`
- L90 _public prototype_ `virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& PressPos) override;`
- L91 _public prototype_ `virtual void OnClickPress(const FInputDeviceRay& PressPos) override;`
- L92 _public prototype_ `virtual void OnClickDrag(const FInputDeviceRay& DragPos) override;`
- L93 _public prototype_ `virtual void OnClickRelease(const FInputDeviceRay& ReleasePos) override;`
- L94 _public prototype_ `virtual void OnTerminateDragSequence() override;`
- L97 _public prototype_ `virtual FInputRayHit BeginHoverSequenceHitTest(const FInputDeviceRay& PressPos) override;` — IHoverBehaviorTarget implementation
- L98 _public prototype_ `virtual void OnBeginHover(const FInputDeviceRay& DevicePos) override;`
- L99 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) override;`
- L100 _public prototype_ `virtual void OnEndHover() override;`
- L110 _public member_ `TScriptInterface<IGizmoAxisSource> AxisSource;` — `UPROPERTY()` — AxisSource provides the 3D line on which the interaction happens
- L114 _public member_ `TScriptInterface<IGizmoFloatParameterSource> ParameterSource;` — `UPROPERTY()` — The 3D line-nearest-point is converted to a 1D coordinate along the line, and the change in value is sent to this ParameterSource
- L118 _public member_ `TObjectPtr<UGizmoViewContext> GizmoViewContext;` — `UE_DEPRECATED(5.5, "UAxisPositionGizmo does not use GizmoViewContext itself (it is used in gizmo components for hit testing).")` — `UPROPERTY()`
- L122 _public member_ `TScriptInterface<IGizmoClickTarget> HitTarget;` — `UPROPERTY()` — The HitTarget provides a hit-test against some 3D element (presumably a visual widget) that controls when interaction can start
- L126 _public member_ `TScriptInterface<IGizmoStateTarget> StateTarget;` — `UPROPERTY()` — StateTarget is notified when interaction starts and ends, so that things like undo/redo can be handled externally.
- L130 _public member_ `TObjectPtr<UClickDragInputBehavior> MouseBehavior;` — `UPROPERTY()` — The mouse click behavior of the gizmo is accessible so that it can be modified to use different mouse keys.
- L136 _public member_ `bool bEnableSignedAxis = false;` — `UPROPERTY()` — If enabled, then the sign on the parameter delta is always "increasing" when moving away from the origin point, rather than just being a projection onto the axis
- L142 _public function_ `TUniqueFunction<bool()> ShouldUseCustomDestinationFunc = []()` — This gets checked to see if we should use the custom destination function to get a destination point for the gizmo, rather than grabbing the closest point on axis to ray.
- L142 _public member_ `TUniqueFunction<bool()> ShouldUseCustomDestinationFunc = []() {return false; };` — This gets checked to see if we should use the custom destination function to get a destination point for the gizmo, rather than grabbing the closest point on axis to ray.
- L160 _public member_ `TUniqueFunction<bool(const FCustomDestinationParams& WorldRay, FVector& OutputPoint)> CustomDestinationFunc = [](const FCustomDestinationParams& Params, FVector& OutputPoint) { return false; };` — If ShouldUseCustomDestinationFunc() returns true, this function gets queried to get a destination point. The gizmo parameter will then be picked in such a way that the dragged location moves to the closest point on the axis to the destination point (optionally offset by the start click position relative the axis origin, if bCustomDestinationAlignsAxisOrigin is true, to align the axis origin itself). Can be used, for example, to align to items in the scene.
- L161 _public function_ `[](const FCustomDestinationParams& Params, FVector& OutputPoint)`
- L171 _public member_ `bool bCustomDestinationAlignsAxisOrigin = true;` — Only used when a custom destination is obtained from CustomDestinationFunc. When false, the custom destination is simply projected back to the axis to get the resulting parameter. This is useful when trying to align the dragged point on the gizmo to the destination point. If true, the same projection is performed, but the final parameter is adjusted to make the axis origin align to the destination instead, rather than the aligning the grabbed point (since the user probably grabbed the gizmo some distance away from the axis origin).
- L176 _public member_ `bool bInInteraction = false;` — `UPROPERTY()` — If true, we are in an active click+drag interaction, otherwise we are not
- L185 _public member_ `FVector InteractionOrigin;` — `UPROPERTY()`
- L188 _public member_ `FVector InteractionAxis;` — `UPROPERTY()`
- L191 _public member_ `FVector InteractionStartPoint;` — `UPROPERTY()`
- L194 _public member_ `FVector InteractionCurPoint;` — `UPROPERTY()`
- L197 _public member_ `float InteractionStartParameter;` — `UPROPERTY()`
- L200 _public member_ `float InteractionCurParameter;` — `UPROPERTY()`
- L203 _public member_ `float ParameterSign = 1.0f;` — `UPROPERTY()`
- L206 _protected member_ `FVector LastHitPosition;`
- L207 _protected member_ `float InitialTargetParameter;`
- L209 _protected member_ `float InteractionStartAxisOriginParameterOffset = 0;`

#### struct `UAxisPositionGizmo::FCustomDestinationParams`  
`struct FCustomDestinationParams`  
_L144-151_
- L150 _public member_ `const FRay* WorldRay = nullptr;` — Right now we use the custom destination function for aligning to items in the scene, which we just need the world ray for. If we want to use functions that use other inputs as the basis for the destination (for instance, just the line parameter), we would add those parameters here and would make sure that the gizmo passes them in.

#### Free symbols / members of external scopes

- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace GizmoUtil` (scope `UE`)

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/AxisSources.h` (Public)


#### class `UGizmoConstantAxisSource`  
`class UGizmoConstantAxisSource : public UObject, public IGizmoAxisSource`  
_L25-44_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,IGizmoAxisSource`
- desc: UGizmoConstantAxisSource is an IGizmoAxisSource implementation that internally stores the Origin and Direction constants
- L29 _public function_ `virtual FVector GetOrigin() const`
- L34 _public function_ `virtual FVector GetDirection() const`
- L40 _public member_ `FVector Origin = FVector::ZeroVector;` — `UPROPERTY()`
- L43 _public member_ `FVector Direction = FVector(0, 0, 1);` — `UPROPERTY()`

#### class `UGizmoConstantFrameAxisSource`  
`class UGizmoConstantFrameAxisSource : public UObject, public IGizmoAxisSource`  
_L55-88_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,IGizmoAxisSource`
- desc: UGizmoConstantFrameAxisSource is an IGizmoAxisSource implementation that internally stores the Origin, Direction, and X/Y Tangent constants.
- L59 _public function_ `virtual FVector GetOrigin() const`
- L64 _public function_ `virtual FVector GetDirection() const`
- L69 _public function_ `virtual bool HasTangentVectors() const override`
- L71 _public function_ `virtual void GetTangentVectors(FVector& TangentXOut, FVector& TangentYOut) const override`
- L78 _public member_ `FVector Origin = FVector::ZeroVector;` — `UPROPERTY()`
- L81 _public member_ `FVector Direction = FVector(0, 0, 1);` — `UPROPERTY()`
- L84 _public member_ `FVector TangentX = FVector(1, 0, 0);` — `UPROPERTY()`
- L87 _public member_ `FVector TangentY = FVector(0, 1, 0);` — `UPROPERTY()`

#### class `UGizmoWorldAxisSource`  
`class UGizmoWorldAxisSource : public UObject, public IGizmoAxisSource`  
_L98-132_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,IGizmoAxisSource`
- desc: UGizmoWorldAxisSource is an IGizmoAxisSource that provides one of the World axes (ie X/Y/Z axes) based on an integer AxisIndex in range [0,2]. The Orgin is internally stored as a FProperty.
- L102 _public function_ `virtual FVector GetOrigin() const`
- L107 _public function_ `virtual FVector GetDirection() const`
- L115 _public member_ `FVector Origin = FVector::ZeroVector;` — `UPROPERTY()`
- L119 _public member_ `int AxisIndex = 2;` — `UPROPERTY()` — Clamped internally to 0,1,2
- L122 _public function_ `static UGizmoWorldAxisSource* Construct( const FVector& WorldOrigin, int WorldAxisIndex, UObject* Outer = (UObject*)GetTransientPackage())`

#### class `UGizmoComponentAxisSource`  
`class UGizmoComponentAxisSource : public UObject, public IGizmoAxisSource`  
_L143-179_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,IGizmoAxisSource`
- desc: UGizmoComponentAxisSource is an IGizmoAxisSource implementation that provides one of the X/Y/Z axes of a Component's local coordinate system, mapped to World, based on an integer AxisIndex in range [0,2]. The Axis Origin is the Component's transform origin. Tangent vectors are provided.
- L147 _public prototype_ `virtual FVector GetOrigin() const;`
- L149 _public prototype_ `virtual FVector GetDirection() const;`
- L151 _public function_ `virtual bool HasTangentVectors() const`
- L153 _public prototype_ `virtual void GetTangentVectors(FVector& TangentXOut, FVector& TangentYOut) const;`
- L156 _public member_ `TObjectPtr<USceneComponent> Component;` — `UPROPERTY()`
- L160 _public member_ `int AxisIndex = 2;` — `UPROPERTY()` — Clamped internally to 0,1,2
- L164 _public member_ `bool bLocalAxes = true;` — `UPROPERTY()` — If false, returns World axes
- L167 _public function_ `static UGizmoComponentAxisSource* Construct( USceneComponent* ComponentIn, int LocalAxisIndex, bool bUseLocalAxes, UObject* Outer = (UObject*)GetTransientPackage())`

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/BrushStampIndicator.h` (Public)


#### class `UBrushStampIndicatorBuilder`  
`class UBrushStampIndicatorBuilder : public UInteractiveGizmoBuilder`  
_L13-18_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveGizmoBuilder`
- L17 _public prototype_ `virtual UInteractiveGizmo* BuildGizmo(const FToolBuilderState& SceneState) const override;`

#### class `UBrushStampIndicator`  
`class UBrushStampIndicator : public UInteractiveGizmo`  
_L26-115_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UInteractiveGizmo`
- desc: UBrushStampIndicator is a simple 3D brush indicator.
- L34 _public prototype_ `virtual void Setup() override;`
- L35 _public prototype_ `virtual void Shutdown() override;`
- L36 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L37 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L43 _public prototype_ `virtual void Update(float Radius, const FVector& Position, const FVector& Normal, float Falloff, float Strength);` — Update the Radius, Position, and Normal of the stamp indicator
- L48 _public prototype_ `virtual void Update(float Radius, const FTransform& WorldTransform, float Falloff);` — Update the Radius, Transform and Falloff of the Stamp Indicator
- L54 _public member_ `bool bVisible = true;` — `UPROPERTY()` — Controls whether Gizmo will draw visual elements. Does not currently affect AttachedComponent.
- L57 _public member_ `float BrushRadius = 1.0f;` — `UPROPERTY()`
- L60 _public member_ `float BrushFalloff = 0.5f;` — `UPROPERTY()`
- L63 _public member_ `float BrushStrength = 1.0f;` — `UPROPERTY()`
- L66 _public member_ `FVector BrushPosition = FVector::ZeroVector;` — `UPROPERTY()`
- L69 _public member_ `FVector BrushNormal = FVector(0, 0, 1);` — `UPROPERTY()`
- L74 _public member_ `bool bDrawIndicatorLines = true;` — `UPROPERTY()`
- L77 _public member_ `bool bDrawRadiusCircle = true;` — `UPROPERTY()`
- L80 _public member_ `bool bScaleNormalByStrength = false;` — `UPROPERTY()`
- L83 _public member_ `int SampleStepCount = 32;` — `UPROPERTY()`
- L86 _public member_ `FLinearColor LineColor = FLinearColor(0.06f, 0.96f, 0.06f);` — `UPROPERTY()`
- L89 _public member_ `float LineThickness = 2.0f;` — `UPROPERTY()`
- L92 _public member_ `bool bDepthTested = false;` — `UPROPERTY()`
- L97 _public member_ `bool bDrawSecondaryLines = true;` — `UPROPERTY()`
- L100 _public member_ `float SecondaryLineThickness = 0.5f;` — `UPROPERTY()`
- L103 _public member_ `FLinearColor SecondaryLineColor = FLinearColor(0.5f, 0.5f, 0.5f, 0.5f);` — `UPROPERTY()`
- L110 _public member_ `TObjectPtr<UPrimitiveComponent> AttachedComponent;` — `UPROPERTY()` — Optional Component that will be transformed such that it tracks the Radius/Position/Normal
- L113 _protected member_ `UPrimitiveComponent* ScaleInitializedComponent = nullptr;` — we are just using this as a key, never calling any functions on it
- L114 _protected member_ `FVector InitialComponentScale;`

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/CombinedTransformGizmo.h` (Public)


#### class `ACombinedTransformGizmoActor`  
`class ACombinedTransformGizmoActor : public AGizmoActor`  
_L48-193_
- reflection: `UCLASS(Transient, NotPlaceable, Hidden, NotBlueprintable, NotBlueprintType, MinimalAPI)`
- inherits: `AGizmoActor`
- desc: ACombinedTransformGizmoActor is an Actor type intended to be used with UCombinedTransformGizmo, as the in-scene visual representation of the Gizmo. FCombinedTransformGizmoActorFactory returns an instance of this Actor type (or a subclass), and based on which Translate and Rotate UProperties are initialized, will associate those Components with UInteractiveGizmo's that implement Axis Translation, Plane Translation, and Axis Rotation. If a particular sub-Gizmo is not required, simply set that FProperty to null. The static factory method ::ConstructDefault3AxisGizmo() creates and initializes an Actor suitable for use in a standard 3-axis Transformation Gizmo.
- L53 _public prototype_ `ACombinedTransformGizmoActor();`
- L62 _public member_ `TObjectPtr<UPrimitiveComponent> TranslateX;` — `UPROPERTY()` — X Axis Translation Component
- L66 _public member_ `TObjectPtr<UPrimitiveComponent> TranslateY;` — `UPROPERTY()` — Y Axis Translation Component
- L70 _public member_ `TObjectPtr<UPrimitiveComponent> TranslateZ;` — `UPROPERTY()` — Z Axis Translation Component
- L75 _public member_ `TObjectPtr<UPrimitiveComponent> TranslateYZ;` — `UPROPERTY()` — YZ Plane Translation Component
- L79 _public member_ `TObjectPtr<UPrimitiveComponent> TranslateXZ;` — `UPROPERTY()` — XZ Plane Translation Component
- L83 _public member_ `TObjectPtr<UPrimitiveComponent> TranslateXY;` — `UPROPERTY()` — XY Plane Translation Component
- L91 _public member_ `TObjectPtr<UPrimitiveComponent> RotateX;` — `UPROPERTY()` — X Axis Rotation Component
- L95 _public member_ `TObjectPtr<UPrimitiveComponent> RotateY;` — `UPROPERTY()` — Y Axis Rotation Component
- L99 _public member_ `TObjectPtr<UPrimitiveComponent> RotateZ;` — `UPROPERTY()` — Z Axis Rotation Component
- L103 _public member_ `TObjectPtr<UPrimitiveComponent> RotationSphere;` — `UPROPERTY()` — Circle that gets drawn around the outside of the gizmo to make it look like a sphere
- L106 _public member_ `TObjectPtr<UPrimitiveComponent> FreeRotateHandle;` — `UPROPERTY()`
- L109 _public member_ `TObjectPtr<UPrimitiveComponent> FreeTranslateHandle;` — `UPROPERTY()`
- L117 _public member_ `TObjectPtr<UPrimitiveComponent> UniformScale;` — `UPROPERTY()` — Uniform Scale Component
- L122 _public member_ `TObjectPtr<UPrimitiveComponent> AxisScaleX;` — `UPROPERTY()` — X Axis Scale Component
- L126 _public member_ `TObjectPtr<UPrimitiveComponent> AxisScaleY;` — `UPROPERTY()` — Y Axis Scale Component
- L130 _public member_ `TObjectPtr<UPrimitiveComponent> AxisScaleZ;` — `UPROPERTY()` — Z Axis Scale Component
- L135 _public member_ `TObjectPtr<UPrimitiveComponent> PlaneScaleYZ;` — `UPROPERTY()` — YZ Plane Scale Component
- L139 _public member_ `TObjectPtr<UPrimitiveComponent> PlaneScaleXZ;` — `UPROPERTY()` — XZ Plane Scale Component
- L143 _public member_ `TObjectPtr<UPrimitiveComponent> PlaneScaleXY;` — `UPROPERTY()` — XY Plane Scale Component
- L161 _public prototype_ `bool ReplaceSubGizmoComponent(ETransformGizmoSubElements Element, UPrimitiveComponent* NewComponent, const FTransform& SubGizmoToGizmo, UPrimitiveComponent** ReplacedComponentOut = nullptr);` — Replaces the component corresponding to the given element with a new component. @param Element Element to replace, should be a single element (no combined flags), except that RotateAllAxes will be interpreted to mean the rotation sphere component. @param NewComponent The component to replace with. If nullptr, no component is added (i.e. the function just deletes the existing component). If not nullptr, then the component should have this actor in its outer chain, i.e. it should have been created as NewObject<UYourComponentType>(ThisActor). @param SubGizmoToGizmo Transform from component to gizmo (i.e. the relative transform). @param ReplacedComponentOut Outputs a pointer to the replaced component, if there was one. Note that the component will already have had DestroyComponent() called on it. @return true if successful, which will be always as long as parameters are valid.
- L168 _public prototype_ `static ACombinedTransformGizmoActor* ConstructDefault3AxisGizmo( UWorld* World, UGizmoViewContext* GizmoViewContext );` — Create a new instance of ACombinedTransformGizmoActor and populate the various sub-components with standard GizmoXComponent instances suitable for a 3-axis transformer Gizmo
- L176 _public prototype_ `static ACombinedTransformGizmoActor* ConstructCustom3AxisGizmo( UWorld* World, UGizmoViewContext* GizmoViewContext, ETransformGizmoSubElements Elements );` — Create a new instance of ACombinedTransformGizmoActor. Populate the sub-components specified by Elements with standard GizmoXComponent instances suitable for a 3-axis transformer Gizmo
- L182 _private member_ `TArray<TWeakPtr<UE::GizmoRenderingUtil::FSubGizmoTransformAdjuster>> AdjustersThatMirrorOnlyInCombinedMode;`
- L188 _private member_ `TObjectPtr<UPrimitiveComponent> FullAxisScaleX;` — `UPROPERTY()` — These store versions of the axis scale components that can be used when not using a combined gizmo, if they differ.
- L190 _private member_ `TObjectPtr<UPrimitiveComponent> FullAxisScaleY;` — `UPROPERTY()`
- L192 _private member_ `TObjectPtr<UPrimitiveComponent> FullAxisScaleZ;` — `UPROPERTY()`

#### class `FCombinedTransformGizmoActorFactory`  
`class FCombinedTransformGizmoActorFactory`  
_L210-240_
- desc: FCombinedTransformGizmoActorFactory creates new instances of ACombinedTransformGizmoActor which are used by UCombinedTransformGizmo to implement 3D transformation Gizmos. An instance of FCombinedTransformGizmoActorFactory is passed to UCombinedTransformGizmo (by way of UCombinedTransformGizmoBuilder), which then calls CreateNewGizmoActor() to spawn new Gizmo Actors. By default CreateNewGizmoActor() returns a default Gizmo Actor suitable for a three-axis transformation Gizmo, override this function to customize the Actor sub-elements.
- L213 _public function_ `FCombinedTransformGizmoActorFactory(UGizmoViewContext* GizmoViewContextIn) : GizmoViewContext(GizmoViewContextIn)`
- L219 _public member_ `ETransformGizmoSubElements EnableElements = ETransformGizmoSubElements::TranslateAllAxes | ETransformGizmoSubElements::TranslateAllPlanes | ETransformGizmoSubElements::RotateAllAxes | ETransformGizmoSubElements::ScaleAllAxes | ETransformGizmoSubElements::ScaleAllPlanes | ETransformGizmoSubElements::ScaleUniform;` — Only these members of the ACombinedTransformGizmoActor gizmo will be initialized
- L231 _public prototype_ `virtual ACombinedTransformGizmoActor* CreateNewGizmoActor(UWorld* World) const;` — @param World the UWorld to create the new Actor in @return new ACombinedTransformGizmoActor instance with members initialized with Components suitable for a transformation Gizmo
- L239 _protected member_ `UGizmoViewContext* GizmoViewContext = nullptr;` — The default gizmos that we use need to have the current view information stored for them via the ITF context store so that they can figure out how big they are for hit testing, so this pointer needs to be set (and kept alive elsewhere) for the actor factory to work properly.

#### class `UCombinedTransformGizmoBuilder`  
`class UCombinedTransformGizmoBuilder : public UInteractiveGizmoBuilder`  
_L248-290_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveGizmoBuilder`
- L258 _public member_ `FString AxisPositionBuilderIdentifier;` — strings identifing GizmoBuilders already registered with GizmoManager. These builders will be used to spawn the various sub-gizmos
- L259 _public member_ `FString PlanePositionBuilderIdentifier;`
- L260 _public member_ `FString AxisAngleBuilderIdentifier;`
- L266 _public member_ `TSharedPtr<FCombinedTransformGizmoActorFactory> GizmoActorBuilder;` — If set, this Actor Builder will be passed to UCombinedTransformGizmo instances. Otherwise new instances of the base FCombinedTransformGizmoActorFactory are created internally.
- L276 _public member_ `TFunction<void(UPrimitiveComponent*, bool)> UpdateHoverFunction;` — If set, this hover function will be passed to UCombinedTransformGizmo instances to use instead of the default. Hover is complicated for UCombinedTransformGizmo because all it knows about the different gizmo scene elements is that they are UPrimitiveComponent (coming from the ACombinedTransformGizmoActor). The default hover function implementation is to try casting to UGizmoBaseComponent and calling ::UpdateHoverState(). If you are using different Components that do not subclass UGizmoBaseComponent, and you want hover to work, you will need to provide a different hover update function.
- L286 _public member_ `TFunction<void(UPrimitiveComponent*, EToolContextCoordinateSystem)> UpdateCoordSystemFunction;` — If set, this coord-system function will be passed to UCombinedTransformGizmo instances to use instead of the default UpdateCoordSystemFunction. By default the UCombinedTransformGizmo will query the external Context to ask whether it should be using world or local coordinate system. Then the default UpdateCoordSystemFunction will try casting to UGizmoBaseCmponent and passing that info on via UpdateWorldLocalState(); If you are using different Components that do not subclass UGizmoBaseComponent, and you want the coord system to be configurable, you will need to provide a different update function.
- L289 _public prototype_ `virtual UInteractiveGizmo* BuildGizmo(const FToolBuilderState& SceneState) const override;`

#### struct `FToolContextOptionalToggle`  
`struct FToolContextOptionalToggle`  
_L299-317_
- desc: FToolContextOptionalToggle is used to store a boolean flag where the value of the boolean may either be set directly, or it may be set by querying some external context. This struct does not directly do anything, it just wraps up the multiple flags/states needed to provide such functionality
- L301 _public member_ `bool bEnabledDirectly = false;`
- L302 _public member_ `bool bEnabledInContext = false;`
- L303 _public member_ `bool bInheritFromContext = false;`
- L305 _public function_ `FToolContextOptionalToggle()`
- L306 _public function_ `FToolContextOptionalToggle(bool bEnabled, bool bSetInheritFromContext)`
- L312 _public function_ `void UpdateContextValue(bool bNewValue)`
- L313 _public function_ `bool InheritFromContext() const`
- L316 _public function_ `bool IsEnabled() const` — @return true if Toggle is currently set to Enabled/On, under the current configuration

#### class `UCombinedTransformGizmo`  
`class UCombinedTransformGizmo : public UInteractiveGizmo`  
_L336-850_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveGizmo`
- desc: UCombinedTransformGizmo provides standard Transformation Gizmo interactions, applied to a UTransformProxy target object. By default the Gizmo will be a standard XYZ translate/rotate Gizmo (axis and plane translation). The in-scene representation of the Gizmo is a ACombinedTransformGizmoActor (or subclass). This Actor has FProperty members for the various sub-widgets, each as a separate Component. Any particular sub-widget of the Gizmo can be disabled by setting the respective Actor Component to null. So, to create non-standard variants of the Transform Gizmo, set a new GizmoActorBuilder in the UCombinedTransformGizmoBuilder registered with the GizmoManager. Return a suitably-configured GizmoActor and everything else will be handled automatically.
- L342 _public prototype_ `virtual void SetWorld(UWorld* World);`
- L343 _public prototype_ `virtual void SetGizmoActorBuilder(TSharedPtr<FCombinedTransformGizmoActorFactory> Builder);`
- L344 _public prototype_ `virtual void SetSubGizmoBuilderIdentifiers(FString AxisPositionBuilderIdentifier, FString PlanePositionBuilderIdentifier, FString AxisAngleBuilderIdentifier);`
- L345 _public prototype_ `virtual void SetUpdateHoverFunction(TFunction<void(UPrimitiveComponent*, bool)> HoverFunction);`
- L346 _public prototype_ `virtual void SetUpdateCoordSystemFunction(TFunction<void(UPrimitiveComponent*, EToolContextCoordinateSystem)> CoordSysFunction);`
- L360 _public prototype_ `bool SetSubGizmoComponent(ETransformGizmoSubElements Element, UPrimitiveComponent* Component, const FTransform& SubGizmoToGizmo);` — Sets a given sub gizmo component to the given component. This is only valid to call after Setup(), but can be before or after SetActiveTarget. @param Element Element to replace, should be a single element (no combined flags), except that RotateAllAxes will be interpreted to mean the rotation sphere component. @param NewComponent The component to replace with. If nullptr, no component is added (i.e. the function just deletes the existing component). If not nullptr, then the component should have the gizmo actor in its outer chain, e.g. NewObject<UYourComponentType>(ThisGizmo->GetGizmoActor()). @param SubGizmoToGizmo Transform from component to gizmo. @return true if successful.
- L371 _public prototype_ `virtual void SetWorldAlignmentFunctions( TUniqueFunction<bool()>&& ShouldAlignDestination, TUniqueFunction<bool(const FRay&, FVector&)>&& DestinationAlignmentRayCaster );` — If used, binds alignment functions to the sub gizmos that they can use to align to geometry in the scene. Specifically, translation and rotation gizmos will check ShouldAlignDestination() to see if they should use the custom ray caster (this allows the behavior to respond to modifier key presses, for instance), and then use DestinationAlignmentRayCaster() to find a point to align to. Subgizmos align to the point in different ways, usually by projecting onto the axis or plane that they operate in.
- L382 _public prototype_ `void SetCustomTranslationDeltaFunctions( TFunction<bool(double AxisDelta, double& SnappedDelta)> XAxis, TFunction<bool(double AxisDelta, double& SnappedDelta)> YAxis, TFunction<bool(double AxisDelta, double& SnappedDelta)> ZAxis);` — These allow for the deltas of gizmo manipulations to be constrained or clamped in custom ways, for instance to slow or stop the gizmo as the drag gets longer. The deltas constrained here are relative to drag start, and note that a custom constraint stops default world grid delta snapping from being applied on that axis. Providing nullptr to any of these removes the custom constraint.
- L386 _public prototype_ `void SetCustomRotationDeltaFunctions( TFunction<bool(double AxisDelta, double& SnappedDelta)> XAxis, TFunction<bool(double AxisDelta, double& SnappedDelta)> YAxis, TFunction<bool(double AxisDelta, double& SnappedDelta)> ZAxis);`
- L390 _public prototype_ `void SetCustomScaleDeltaFunctions( TFunction<bool(double AxisDelta, double& SnappedDelta)> XAxis, TFunction<bool(double AxisDelta, double& SnappedDelta)> YAxis, TFunction<bool(double AxisDelta, double& SnappedDelta)> ZAxis);`
- L401 _public prototype_ `virtual void SetIsNonUniformScaleAllowedFunction( TUniqueFunction<bool()>&& IsNonUniformScaleAllowed );` — By default, non-uniform scaling handles appear (assuming they exist in the gizmo to begin with), when CurrentCoordinateSystem == EToolContextCoordinateSystem::Local, since components can only be locally scaled. However, this can be changed to a custom check here, perhaps to hide them in extra conditions or to always show them (if the gizmo is not scaling a component).
- L409 _public function_ `virtual bool IsNonUniformScaleAllowed() const` — Exposes the return value of the current IsNonUniformScaleAllowed function so that, for instance, numerical UI can react appropriately.
- L415 _public prototype_ `virtual void SetDisallowNegativeScaling(bool bDisallow);` — By default, the nonuniform scale components can scale negatively. However, they can be made to clamp to zero instead by passing true here. This is useful for using the gizmo to flatten geometry.
- L419 _public prototype_ `virtual void Setup() override;` — UInteractiveGizmo overrides
- L420 _public prototype_ `virtual void Shutdown() override;`
- L421 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L428 _public prototype_ `virtual void SetActiveTarget(UTransformProxy* Target, IToolContextTransactionProvider* TransactionProvider = nullptr);` — Set the active target object for the Gizmo @param Target active target @param TransactionProvider optional IToolContextTransactionProvider implementation to use - by default uses GizmoManager
- L433 _public prototype_ `virtual void ClearActiveTarget();` — Clear the active target object for the Gizmo
- L437 _public member_ `TObjectPtr<UTransformProxy> ActiveTarget;` — `UPROPERTY()` — The active target object for the Gizmo
- L442 _public function_ `ACombinedTransformGizmoActor* GetGizmoActor() const` — @return the internal GizmoActor used by the Gizmo
- L447 _public prototype_ `FTransform GetGizmoTransform() const;` — @return current transform of Gizmo
- L455 _public prototype_ `void ReinitializeGizmoTransform(const FTransform& NewTransform, bool bKeepGizmoUnscaled = true);` — Repositions the gizmo without issuing undo/redo changes, triggering callbacks, or moving any components. Useful for resetting the gizmo to a new location without it being viewed as a gizmo manipulation. @param bKeepGizmoUnscaled If true, the scale component of NewTransform is passed through to the target but gizmo scale is set to 1
- L462 _public prototype_ `virtual void SetNewGizmoTransform(const FTransform& NewTransform, bool bKeepGizmoUnscaled = true);` — Set a new position for the Gizmo. This is done via the same mechanisms as the sub-gizmos, so it generates the same Change/Modify() events, and hence works with Undo/Redo @param bKeepGizmoUnscaled If true, the scale component of NewTransform is passed through to the target but gizmo scale is set to 1
- L468 _public prototype_ `virtual void BeginTransformEditSequence();` — Called at the start of a sequence of gizmo transform edits, for instance while dragging or manipulating the gizmo numerical UI.
- L473 _public prototype_ `virtual void EndTransformEditSequence();` — Called at the end of a sequence of gizmo transform edits.
- L478 _public prototype_ `void UpdateTransformDuringEditSequence(const FTransform& NewTransform, bool bKeepGizmoUnscaled = true);` — Updates the gizmo transform between Begin/EndTransformeditSequence calls.
- L484 _public prototype_ `virtual void SetNewChildScale(const FVector& NewChildScale);` — Explicitly set the child scale. Mainly useful to "reset" the child scale to (1,1,1) when re-using Gizmo across multiple transform actions. @warning does not generate change/modify events!!
- L489 _public prototype_ `virtual void SetVisibility(bool bVisible);` — Set visibility for this Gizmo
- L494 _public function_ `virtual bool IsVisible()` — @return true if Gizmo is visible
- L504 _public member_ `bool bSnapToWorldGrid = true;` — `UPROPERTY()` — bSnapToWorldGrid controls whether any position snapping is applied, if possible, for Axis and Plane translations, via the ContextQueriesAPI Despite the name, this flag controls both world-space grid snapping and relative snapping
- L509 _public member_ `FToolContextOptionalToggle RelativeTranslationSnapping = FToolContextOptionalToggle(true, true);` — Specify whether Relative snapping for Translations should be used in World frame mode. Relative snapping is always used in Local mode.
- L515 _public member_ `bool bGridSizeIsExplicit = false;` — `UPROPERTY()` — Optional grid size which overrides the Context Grid
- L517 _public member_ `FVector ExplicitGridSize;` — `UPROPERTY()`
- L523 _public member_ `bool bRotationGridSizeIsExplicit = false;` — `UPROPERTY()` — Optional grid size which overrides the Context Rotation Grid
- L525 _public member_ `FRotator ExplicitRotationGridSize;` — `UPROPERTY()`
- L531 _public member_ `bool bSnapToWorldRotGrid = true;` — `UPROPERTY()` — If true, then when using world frame, Axis and Plane rotation snap to the world grid via the ContextQueriesAPI (in RotationSnapFunction)
- L537 _public member_ `bool bSnapToScaleGrid = true;` — `UPROPERTY()` — If true, scaling snaps to the grid
- L544 _public member_ `bool bUseContextCoordinateSystem = true;` — `UPROPERTY()` — Whether to use the World/Local coordinate system provided by the context via the ContextyQueriesAPI.
- L551 _public member_ `EToolContextCoordinateSystem CurrentCoordinateSystem = EToolContextCoordinateSystem::Local;` — `UPROPERTY()` — Current coordinate system in use. If bUseContextCoordinateSystem is true, this value will be updated internally every Tick() by quering the ContextyQueriesAPI, otherwise the default is Local and the client can change it as necessary
- L560 _public member_ `bool bUseContextGizmoMode = true;` — `UPROPERTY()` — Whether to use the Gizmo Mode provided by the context via the ContextyQueriesAPI.
- L568 _public member_ `EToolContextTransformGizmoMode ActiveGizmoMode = EToolContextTransformGizmoMode::Combined;` — `UPROPERTY()` — Current dynamic sub-widget visibility mode to use (eg Translate-Only, Scale-Only, Combined, etc) If bUseContextGizmoMode is true, this value will be updated internally every Tick() by quering the ContextyQueriesAPI, otherwise the default is Combined and the client can change it as necessary
- L574 _public prototype_ `ETransformGizmoSubElements GetGizmoElements();` — Gets the elements that this gizmo was initialized with. Note that this may not account for individual element visibility- for instance the scaling component may not be visible if IsNonUniformScaleAllowed() is false.
- L588 _public prototype_ `void SetDisplaySpaceTransform(TOptional<FTransform> TransformIn);` — The DisplaySpaceTransform is not used by the gizmo itself, but can be used by external adapters that might display gizmo values, to give values relative to this transform rather than relative to world origin and axes. For example a numerical UI for a two-axis gizmo that is not in a world XY/YZ/XZ plane cannot use the global axes for setting the absolute position of the plane if it wants the gizmo to remain in that plane; instead, the DisplaySpaceTransform can give a space in which X and Y values keep the gizmo in the plane. Note that this is an optional feature, as it would require tools to keep this transform up to date if they want the UI to use it, so tools could just leave it unset.
- L589 _public function_ `const TOptional<FTransform>& GetDisplaySpaceTransform()`
- L594 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDisplaySpaceTransformChanged, UCombinedTransformGizmo*, TOptional<FTransform>);` — Broadcast at the end of a SetDisplaySpaceTransform call that changes the display space transform.
- L595 _public member_ `FOnDisplaySpaceTransformChanged OnDisplaySpaceTransformChanged;`
- L601 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSetActiveTarget, UCombinedTransformGizmo*, UTransformProxy*);` — Broadcast at the end of a SetActiveTarget call. Using this, an adapter such as a numerical UI widget can bind to the gizmo at construction and still be able to initialize using the transform proxy once that is set.
- L602 _public member_ `FOnSetActiveTarget OnSetActiveTarget;`
- L608 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnClearActiveTarget, UCombinedTransformGizmo*, UTransformProxy*);` — Broadcast at the beginning of a ClearActiveTarget call, when the ActiveTarget (if present) is not yet disconnected. Gives things a chance to unbind from it.
- L609 _public member_ `FOnClearActiveTarget OnAboutToClearActiveTarget;`
- L612 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnVisibilityChanged, UCombinedTransformGizmo*, bool);` — Broadcast at the end of a SetVisibility call if the visibility changes.
- L613 _public member_ `FOnVisibilityChanged OnVisibilityChanged;`
- L616 _protected member_ `TSharedPtr<FCombinedTransformGizmoActorFactory> GizmoActorBuilder;`
- L618 _protected member_ `FString AxisPositionBuilderIdentifier;`
- L619 _protected member_ `FString PlanePositionBuilderIdentifier;`
- L620 _protected member_ `FString AxisAngleBuilderIdentifier;`
- L625 _protected member_ `TFunction<void(UPrimitiveComponent*, bool)> UpdateHoverFunction;` — This function is called on each active GizmoActor Component to update it's hover state. If the Component is not a UGizmoBaseCmponent, the client needs to provide a different implementation of this function via the ToolBuilder
- L630 _protected member_ `TFunction<void(UPrimitiveComponent*, EToolContextCoordinateSystem)> UpdateCoordSystemFunction;` — This function is called on each active GizmoActor Component to update it's coordinate system (eg world/local). If the Component is not a UGizmoBaseCmponent, the client needs to provide a different implementation of this function via the ToolBuilder
- L634 _protected member_ `TArray<TObjectPtr<UPrimitiveComponent>> ActiveComponents;` — `UPROPERTY()` — List of current-active child components
- L638 _protected member_ `TArray<TObjectPtr<UInteractiveGizmo>> ActiveGizmos;` — `UPROPERTY()` — list of currently-active child gizmos
- L650 _protected member_ `TArray<FSubGizmoInfo> TranslationSubGizmos;`
- L651 _protected member_ `TArray<FSubGizmoInfo> RotationSubGizmos;`
- L652 _protected member_ `TArray<FSubGizmoInfo> UniformScaleSubGizmos;`
- L653 _protected member_ `TArray<FSubGizmoInfo> NonUniformScaleSubGizmos;`
- L655 _private member_ `TWeakObjectPtr<UInteractiveGizmo> AxisScaleXGizmo;`
- L656 _private member_ `TWeakObjectPtr<UInteractiveGizmo> AxisScaleYGizmo;`
- L657 _private member_ `TWeakObjectPtr<UInteractiveGizmo> AxisScaleZGizmo;`
- L659 _private member_ `TFunction<bool(double AxisDelta, double& SnappedDelta)> CustomTranslationDeltaConstraintFunctions[3];`
- L660 _private member_ `TFunction<bool(double AxisDelta, double& SnappedDelta)> CustomRotationDeltaConstraintFunctions[3];`
- L661 _private member_ `TFunction<bool(double AxisDelta, double& SnappedDelta)> CustomScaleDeltaConstraintFunctions[3];`
- L665 _protected member_ `UWorld* World;` — GizmoActors will be spawned in this World
- L674 _protected member_ `TObjectPtr<ACombinedTransformGizmoActor> GizmoActor;` — `UPROPERTY()` — Current active GizmoActor that was spawned by this Gizmo. Will be destroyed when this gizmo is, and expected not to be destroyed otherwise. Still, needs to be validated in case things go wrong and the world is destroyed before calling Shutdown on the gizmo.
- L683 _protected member_ `TObjectPtr<UGizmoConstantFrameAxisSource> CameraAxisSource;` — `UPROPERTY()` — Axis that points towards camera, X/Y plane tangents aligned to right/up. Shared across Gizmos, and created internally during SetActiveTarget()
- L686 _protected prototype_ `void UpdateCameraAxisSource();` — internal function that updates CameraAxisSource by getting current view state from GizmoManager
- L691 _protected member_ `TObjectPtr<UGizmoComponentAxisSource> AxisXSource;` — `UPROPERTY()` — X-axis source is shared across Gizmos, and created internally during SetActiveTarget()
- L695 _protected member_ `TObjectPtr<UGizmoComponentAxisSource> AxisYSource;` — `UPROPERTY()` — Y-axis source is shared across Gizmos, and created internally during SetActiveTarget()
- L699 _protected member_ `TObjectPtr<UGizmoComponentAxisSource> AxisZSource;` — `UPROPERTY()` — Z-axis source is shared across Gizmos, and created internally during SetActiveTarget()
- L708 _protected member_ `TObjectPtr<UGizmoComponentAxisSource> UnitAxisXSource;` — `UPROPERTY()` — Local X-axis source (ie 1,0,0) is shared across Scale Gizmos, and created internally during SetActiveTarget()
- L712 _protected member_ `TObjectPtr<UGizmoComponentAxisSource> UnitAxisYSource;` — `UPROPERTY()` — Y-axis source (ie 0,1,0) is shared across Scale Gizmos, and created internally during SetActiveTarget()
- L716 _protected member_ `TObjectPtr<UGizmoComponentAxisSource> UnitAxisZSource;` — `UPROPERTY()` — Z-axis source (ie 0,0,1) is shared across Scale Gizmos, and created internally during SetActiveTarget()
- L730 _protected member_ `TObjectPtr<UGizmoTransformChangeStateTarget> StateTarget;` — `UPROPERTY()` — State target is shared across gizmos, and created internally during SetActiveTarget(). Several FChange providers are registered with this StateTarget, including the UCombinedTransformGizmo itself (IToolCommandChangeSource implementation above is called)
- L736 _protected function_ `TUniqueFunction<bool()> ShouldAlignDestination = []()` — These are used to let the translation subgizmos use raycasts into the scene to align the gizmo with scene geometry. See comment for SetWorldAlignmentFunctions().
- L736 _protected member_ `TUniqueFunction<bool()> ShouldAlignDestination = []() { return false; };` — These are used to let the translation subgizmos use raycasts into the scene to align the gizmo with scene geometry. See comment for SetWorldAlignmentFunctions().
- L737 _protected function_ `TUniqueFunction<bool(const FRay&, FVector&)> DestinationAlignmentRayCaster = [](const FRay&, FVector&)`
- L737 _protected member_ `TUniqueFunction<bool(const FRay&, FVector&)> DestinationAlignmentRayCaster = [](const FRay&, FVector&) {return false; };`
- L739 _protected function_ `TUniqueFunction<bool()> IsNonUniformScaleAllowedFunc = [this]()`
- L739 _protected member_ `TUniqueFunction<bool()> IsNonUniformScaleAllowedFunc = [this]() { return CurrentCoordinateSystem == EToolContextCoordinateSystem::Local; };`
- L741 _protected member_ `bool bDisallowNegativeScaling = false;`
- L744 _protected member_ `TOptional<FTransform> DisplaySpaceTransform;` — See comment for SetDisplaySpaceTransform;
- L748 _protected typedef_ `using FTransformSubGizmoCommonParams = UE::GizmoUtil::FTransformSubGizmoCommonParams;`
- L749 _protected typedef_ `using FTransformSubGizmoSharedState = UE::GizmoUtil::FTransformSubGizmoSharedState;`
- L752 _protected prototype_ `virtual UInteractiveGizmo* AddAxisTranslationGizmo( FTransformSubGizmoCommonParams& Params, FTransformSubGizmoSharedState& SharedState);` — @return a new instance of the standard axis-translation Gizmo
- L756 _protected prototype_ `virtual UInteractiveGizmo* AddPlaneTranslationGizmo( FTransformSubGizmoCommonParams& Params, FTransformSubGizmoSharedState& SharedState);` — @return a new instance of the standard plane-translation Gizmo
- L760 _protected prototype_ `virtual UInteractiveGizmo* AddAxisRotationGizmo( FTransformSubGizmoCommonParams& Params, FTransformSubGizmoSharedState& SharedState);` — @return a new instance of the standard axis-rotation Gizmo
- L764 _protected prototype_ `virtual UInteractiveGizmo* AddAxisScaleGizmo( FTransformSubGizmoCommonParams& Params, FTransformSubGizmoSharedState& SharedState);` — @return a new instance of the standard axis-scaling Gizmo
- L768 _protected prototype_ `virtual UInteractiveGizmo* AddPlaneScaleGizmo( FTransformSubGizmoCommonParams& Params, FTransformSubGizmoSharedState& SharedState);` — @return a new instance of the standard plane-scaling Gizmo
- L772 _protected prototype_ `virtual UInteractiveGizmo* AddUniformScaleGizmo( FTransformSubGizmoCommonParams& Params, FTransformSubGizmoSharedState& SharedState);` — @return a new instance of the standard plane-scaling Gizmo
- L775 _protected prototype_ `virtual UInteractiveGizmo* AddFreeTranslationGizmo( FTransformSubGizmoCommonParams& Params, FTransformSubGizmoSharedState& SharedState);`
- L778 _protected prototype_ `virtual UInteractiveGizmo* AddFreeRotationGizmo( FTransformSubGizmoCommonParams& Params, FTransformSubGizmoSharedState& SharedState);`
- L782 _protected prototype_ `bool PositionSnapFunction(const FVector& WorldPosition, FVector& SnappedPositionOut) const;` — Axis and Plane TransformSources use these function to execute snapping queries
- L783 _protected prototype_ `bool PositionAxisDeltaSnapFunction(double AxisDelta, double& SnappedDeltaOut, int AxisIndex) const;`
- L784 _protected prototype_ `FQuat RotationSnapFunction(const FQuat& DeltaRotation) const;`
- L785 _protected prototype_ `bool RotationAxisAngleSnapFunction(double AxisAngleDelta, double& SnappedAxisAngleDeltaOut, int AxisIndex) const;`
- L789 _private prototype_ `bool ScaleAxisDeltaSnapFunction(double ScaleAxisDelta, double& SnappedAxisScaleDeltaOut, int AxisIndex) const;` — Used for scale delta snapping. Calls out to the non-axis endpoint by default
- L792 _protected prototype_ `bool ScaleSnapFunction(double DeltaScale) const;` — currently not implemented because WorldGridSnapping currently has no affect on scale/scale-snapping
- L794 _protected prototype_ `bool ScaleAxisDeltaSnapFunction(double ScaleAxisDelta, double & SnappedAxisScaleDeltaOut) const;` — Used for uniform scale delta snapping
- L798 _protected prototype_ `virtual UInteractiveGizmo* AddAxisTranslationGizmo( UPrimitiveComponent* AxisComponent, USceneComponent* RootComponent, IGizmoAxisSource* AxisSource, IGizmoTransformSource* TransformSource, IGizmoStateTarget* StateTarget, int AxisIndex);` — @return a new instance of the standard axis-translation Gizmo
- L806 _protected prototype_ `virtual UInteractiveGizmo* AddPlaneTranslationGizmo( UPrimitiveComponent* AxisComponent, USceneComponent* RootComponent, IGizmoAxisSource* AxisSource, IGizmoTransformSource* TransformSource, IGizmoStateTarget* StateTarget, int XAxisIndex, int YAxisIndex);` — @return a new instance of the standard plane-translation Gizmo
- L814 _protected prototype_ `virtual UInteractiveGizmo* AddAxisRotationGizmo( UPrimitiveComponent* AxisComponent, USceneComponent* RootComponent, IGizmoAxisSource* AxisSource, IGizmoTransformSource* TransformSource, IGizmoStateTarget* StateTarget);` — @return a new instance of the standard axis-rotation Gizmo
- L821 _protected prototype_ `virtual UInteractiveGizmo* AddAxisScaleGizmo( UPrimitiveComponent* AxisComponent, USceneComponent* RootComponent, IGizmoAxisSource* GizmoAxisSource, IGizmoAxisSource* ParameterAxisSource, IGizmoTransformSource* TransformSource, IGizmoStateTarget* StateTarget);` — @return a new instance of the standard axis-scaling Gizmo
- L828 _protected prototype_ `virtual UInteractiveGizmo* AddPlaneScaleGizmo( UPrimitiveComponent* AxisComponent, USceneComponent* RootComponent, IGizmoAxisSource* GizmoAxisSource, IGizmoAxisSource* ParameterAxisSource, IGizmoTransformSource* TransformSource, IGizmoStateTarget* StateTarget);` — @return a new instance of the standard plane-scaling Gizmo
- L835 _protected prototype_ `virtual UInteractiveGizmo* AddUniformScaleGizmo( UPrimitiveComponent* ScaleComponent, USceneComponent* RootComponent, IGizmoAxisSource* GizmoAxisSource, IGizmoAxisSource* ParameterAxisSource, IGizmoTransformSource* TransformSource, IGizmoStateTarget* StateTarget);` — @return a new instance of the standard plane-scaling Gizmo
- L842 _protected member_ `TUniquePtr<FTransformSubGizmoSharedState> SubGizmoSharedState;` — Useful for reinitializing components after SetActiveTarget, or for use by derived classes.
- L846 _private member_ `IToolContextTransactionProvider* TransactionProviderAtLastSetActiveTarget = nullptr;` — Here to support subgizmo reinitialization after SetActiveTarget has been called. Private instead of protected for now in case we change the approach here.
- L848 _private member_ `EToolContextTransformGizmoMode PreviousActiveGizmoMode = EToolContextTransformGizmoMode::Combined;`
- L849 _private prototype_ `void ApplyGizmoActiveMode();`

#### struct `UCombinedTransformGizmo::FSubGizmoInfo`  
`struct FSubGizmoInfo`  
_L644-649_
- desc: FSubGizmoInfo stores the (UPrimitiveComponent,UInteractiveGizmo) pair for a sub-element of the widget. The ActiveComponents and ActiveGizmos arrays keep those items alive, so this is redundant information, but useful for filtering/etc
- L647 _public member_ `TWeakObjectPtr<UPrimitiveComponent> Component;` — note: either of these may be invalid
- L648 _public member_ `TWeakObjectPtr<UInteractiveGizmo> Gizmo;`

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace GizmoUtil` (scope `UE`)
- L29 _namespace_ `namespace UE`
- L29 _namespace_ `namespace GizmoRenderingUtil` (scope `UE`)
- L594 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDisplaySpaceTransformChanged, UCombinedTransformGizmo*, TOptional<FTransform>);` — Broadcast at the end of a SetDisplaySpaceTransform call that changes the display space transform.
- L601 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSetActiveTarget, UCombinedTransformGizmo*, UTransformProxy*);` — Broadcast at the end of a SetActiveTarget call. Using this, an adapter such as a numerical UI widget can bind to the gizmo at construction and still be able to initialize using the transform proxy once that is set.
- L608 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnClearActiveTarget, UCombinedTransformGizmo*, UTransformProxy*);` — Broadcast at the beginning of a ClearActiveTarget call, when the ActiveTarget (if present) is not yet disconnected. Gives things a chance to unbind from it.
- L612 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnVisibilityChanged, UCombinedTransformGizmo*, bool);` — Broadcast at the end of a SetVisibility call if the visibility changes.

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/ComponentBoundTransformProxy.h` (Public)


#### class `UComponentBoundTransformProxy`  
`class UComponentBoundTransformProxy : public UTransformProxy`  
_L24-46_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UTransformProxy`
- desc: A variant of a transform proxy whose transform is always bound to a particular component. This means that if the component is moved as a result of its parents moving, the proxy will get that transform when queried. This makes the transform proxy very useful for being bound to sub gizmos that are moved by some parent gizmo. SetTransform will cause the proxy to set the transform on the bound component even if it is not part of its component set (to stay matched with the component) so AddComponent is not necessary for the bound component (nor is it likely to be used with this proxy, see below). This class is mainly intended to be bound to a single component and used for its delegates. It can still be used for the multi-component movement functionality of a transform proxy, but it is worth noting in that case that if the bound component is moved by its parent, the other components won't necessarily be moved unless SetTransform() is called on the proxy (or they happen to be parented in the same subtree).
- L36 _public prototype_ `virtual void BindToComponent(USceneComponent* Component, bool bStoreScaleSeparately);` — Make the proxy get its transform from the given component, and set the transform on this component whenever SetTransform is called. @param bStoreScaleSeparately If true, then the scale won't be obtained from the component, nor set on it. Instead it will be stored separately internally. This is useful when using a gizmo to manipulate scale, where you don't want the scale to be applied to the gizmo component itself.
- L39 _public prototype_ `virtual FTransform GetTransform() const override;` — UTransformProxy
- L40 _public prototype_ `virtual void SetTransform(const FTransform& Transform) override;`
- L41 _public prototype_ `virtual void UpdateSharedTransform() override;`
- L44 _protected member_ `TWeakObjectPtr<USceneComponent> BoundComponent;`
- L45 _protected member_ `bool bStoreScaleSeparately = true;`

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/GizmoActor.h` (Public)


#### class `AGizmoActor`  
`class AGizmoActor : public AInternalToolFrameworkActor`  
_L23-59_
- reflection: `UCLASS(Transient, NotPlaceable, Hidden, NotBlueprintable, NotBlueprintType, MinimalAPI)`
- inherits: `AInternalToolFrameworkActor`
- desc: AGizmoActor is a base class for Actors that would be created to represent Gizmos in the scene. Currently this does not involve any special functionality, but a set of static functions are provided to create default Components commonly used in Gizmos.
- L27 _public prototype_ `AGizmoActor();`
- L30 _public prototype_ `static UGizmoArrowComponent* AddDefaultArrowComponent( UWorld* World, AActor* Actor, UGizmoViewContext* GizmoViewContext, const FLinearColor& Color, const FVector& LocalDirection, const float Length = 80.0f );` — Add standard arrow component to Actor, generally used for axis-translation
- L35 _public prototype_ `static UGizmoRectangleComponent* AddDefaultRectangleComponent( UWorld* World, AActor* Actor, UGizmoViewContext* GizmoViewContext, const FLinearColor& Color, const FVector& PlaneAxis1, const FVector& PlaneAxisx2 );` — Add standard rectangle component to Actor, generally used for plane-translation
- L40 _public prototype_ `static UGizmoCircleComponent* AddDefaultCircleComponent( UWorld* World, AActor* Actor, UGizmoViewContext* GizmoViewContext, const FLinearColor& Color, const FVector& PlaneNormal, float Radius = 120.0f );` — Add standard circle component to Actor, generally used for axis-rotation
- L47 _public prototype_ `static UGizmoBoxComponent* AddDefaultBoxComponent( UWorld* World, AActor* Actor, UGizmoViewContext* GizmoViewContext, const FLinearColor& Color, const FVector& Origin, const FVector& Dimensions = FVector(20.0f, 20.0f, 20.0f) );` — Add standard 3D box component to Actor. By default the box is axis-aligned, centered at the specified Origin
- L54 _public prototype_ `static UGizmoLineHandleComponent* AddDefaultLineHandleComponent( UWorld* World, AActor* Actor, UGizmoViewContext* GizmoViewContext, const FLinearColor& Color, const FVector& PlaneNormal, const FVector& LocalDirection, const float Length = 60.f, const bool bImageScale = false );` — Add standard disk component to Actor, generally used for handles

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/GizmoArrowComponent.h` (Public)


#### class `UGizmoArrowComponent`  
`class UGizmoArrowComponent : public UGizmoBaseComponent`  
_L15-41_
- reflection: `UCLASS(ClassGroup = Utility, HideCategories = (Physics, Collision, Lighting, Rendering, Mobile), MinimalAPI)`
- inherits: `UGizmoBaseComponent`
- desc: Simple Component intended to be used as part of 3D Gizmos. Currently draws the "arrow" as a single 3D line.
- L21 _public member_ `FVector Direction = FVector(0,0,1);` — `UPROPERTY(EditAnywhere, Category = Options)`
- L24 _public member_ `float Gap = 5.0f;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L27 _public member_ `float Length = 60.0f;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L30 _public member_ `float Thickness = 2.0f;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L34 _private prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L35 _private prototype_ `virtual bool LineTraceComponent(FHitResult& OutHit, const FVector Start, const FVector End, const FCollisionQueryParams& Params) override;`
- L39 _private prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/GizmoBaseComponent.h` (Public)


#### class `UGizmoBaseComponentInterface`  
`class UGizmoBaseComponentInterface : public UInterface`  
_L14-17_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IGizmoBaseComponentInterface`  
`class IGizmoBaseComponentInterface`  
_L23-32_
- desc: Interface that allows a component to receive various gizmo-specific callbacks while still inheriting from some class other than UGizmoBaseComponent.
- L27 _public function_ `virtual void UpdateHoverState(bool bHoveringIn)`
- L29 _public function_ `virtual void UpdateWorldLocalState(bool bWorldIn)`
- L31 _public function_ `virtual void UpdateInteractingState(bool bInteractingIn)`

#### class `UGizmoBaseComponent`  
`class UGizmoBaseComponent : public UPrimitiveComponent , public IGizmoBaseComponentInterface`  
_L41-114_
- reflection: `UCLASS(ClassGroup = Utility, HideCategories = (Physics, Collision, Mobile), MinimalAPI)`
- inherits: `UPrimitiveComponent,IGizmoBaseComponentInterface`
- desc: Base class for simple Components intended to be used as part of 3D Gizmos. Contains common properties and utility functions. This class does nothing by itself, use subclasses like UGizmoCircleComponent
- L47 _public function_ `UGizmoBaseComponent()`
- L56 _public function_ `void NotifyExternalPropertyUpdates()` — Currently this must be called if you change UProps on Base or subclass, to recreate render proxy which has a local copy of those settings
- L64 _public member_ `FLinearColor Color = FLinearColor::Red;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L68 _public member_ `float HoverSizeMultiplier = 2.0f;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L72 _public member_ `float PixelHitDistanceThreshold = 7.0f;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L74 _public function_ `void SetGizmoViewContext(UGizmoViewContext* GizmoViewContextIn)`
- L82 _public function_ `virtual void UpdateHoverState(bool bHoveringIn) override` — `UFUNCTION()`
- L91 _public function_ `virtual void UpdateWorldLocalState(bool bWorldIn) override` — `UFUNCTION()`
- L103 _protected member_ `bool bHovering = false;` — hover state
- L106 _protected member_ `bool bWorld = false;` — world/local coordinates state
- L109 _protected member_ `TObjectPtr<UGizmoViewContext> GizmoViewContext = nullptr;` — `UPROPERTY()`
- L113 _protected member_ `bool bIsViewDependent = false;` — True when GizmoViewContext is not null. Here as a boolean so it can be pointed to by the proxy to see what it should do.

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/GizmoBoxComponent.h` (Public)


#### class `UGizmoBoxComponent`  
`class UGizmoBoxComponent : public UGizmoBaseComponent`  
_L15-49_
- reflection: `UCLASS(ClassGroup = Utility, HideCategories = (Physics, Collision, Lighting, Rendering, Mobile), MinimalAPI)`
- inherits: `UGizmoBaseComponent`
- desc: Simple Component intended to be used as part of 3D Gizmos. Draws outline of 3D Box based on parameters.
- L21 _public member_ `FVector Origin = FVector(0, 0, 0);` — `UPROPERTY(EditAnywhere, Category = Options)`
- L24 _public member_ `FQuat Rotation = FQuat::Identity;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L27 _public member_ `FVector Dimensions = FVector(20.0f, 20.0f, 20.0f);` — `UPROPERTY(EditAnywhere, Category = Options)`
- L30 _public member_ `float LineThickness = 2.0f;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L33 _public member_ `bool bRemoveHiddenLines = true;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L36 _public member_ `bool bEnableAxisFlip = true;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L40 _private prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L41 _private prototype_ `virtual bool LineTraceComponent(FHitResult& OutHit, const FVector Start, const FVector End, const FCollisionQueryParams& Params) override;`
- L42 _private prototype_ `virtual void GetUsedMaterials(TArray<UMaterialInterface*>& OutMaterials, bool bGetDebugMaterials = false) const override;`
- L46 _private prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/GizmoCircleComponent.h` (Public)


#### class `UGizmoCircleComponent`  
`class UGizmoCircleComponent : public UGizmoBaseComponent`  
_L15-53_
- reflection: `UCLASS(ClassGroup = Utility, HideCategories = (Physics, Collision, Mobile), MinimalAPI)`
- inherits: `UGizmoBaseComponent`
- desc: Simple Component intended to be used as part of 3D Gizmos. Draws a 3D circle based on parameters.
- L21 _public member_ `FVector Normal = FVector(0,0,1);` — `UPROPERTY(EditAnywhere, Category = Options)`
- L24 _public member_ `float Radius = 100.0f;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L27 _public member_ `float Thickness = 2.0f;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L30 _public member_ `int NumSides = 64;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L33 _public member_ `bool bViewAligned = false;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L36 _public member_ `bool bDrawFullCircle = false;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L42 _public member_ `bool bOnlyAllowFrontFacingHits = true;` — `UPROPERTY(EditAnywhere, Category = Options)` — If the circle was on a 3D sphere, then only the 'front' part of the circle can be hit, (in other words, if the ray would hit the sphere first, ignore the hit). Dynamically disabled if the circle is parallel to the view plane (ie "fully visible")
- L46 _private prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L47 _private prototype_ `virtual bool LineTraceComponent(FHitResult& OutHit, const FVector Start, const FVector End, const FCollisionQueryParams& Params) override;`
- L51 _private prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/GizmoComponents.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/GizmoElementArc.h` (Public)


#### class `UGizmoElementArc`  
`class UGizmoElementArc : public UGizmoElementCircleBase`  
_L19-41_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UGizmoElementCircleBase`
- desc: Simple object intended to be used as part of 3D Gizmos. Draws a thick arc based on parameters.
- L25 _public prototype_ `UGizmoElementArc();`
- L28 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI, const FRenderTraversalState& RenderState) override;`
- L29 _public prototype_ `virtual FInputRayHit LineTrace(const UGizmoViewContext* ViewContext, const FLineTraceTraversalState& LineTraceState, const FVector& RayOrigin, const FVector& RayDirection, FLineTraceOutput& OutLineTraceOutput) override;`
- L33 _public prototype_ `virtual void SetInnerRadius(double InInnerRadius);` — Inner circle radius.
- L34 _public prototype_ `virtual double GetInnerRadius() const;`
- L40 _protected member_ `double InnerRadius = 5.0;` — `UPROPERTY()` — Arc inner radius.

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/GizmoElementArrow.h` (Public)


#### class `UGizmoElementArrow`  
`class UGizmoElementArrow : public UGizmoElementGroupBase`  
_L24-158_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UGizmoElementGroupBase`
- desc: Simple object intended to be used as part of 3D Gizmos. Draws a 3D arrow based on parameters.
- L29 _public prototype_ `UGizmoElementArrow();`
- L32 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI, const FRenderTraversalState& RenderState) override;`
- L33 _public prototype_ `virtual FInputRayHit LineTrace(const UGizmoViewContext* ViewContext, const FLineTraceTraversalState& LineTraceState, const FVector& RayOrigin, const FVector& RayDirection, FLineTraceOutput& OutLineTraceOutput) override;`
- L37 _public prototype_ `virtual void SetBase(const FVector& InBase);` — Location of the base of arrow cylinder
- L38 _public prototype_ `virtual FVector GetBase() const;`
- L41 _public prototype_ `virtual void SetDirection(const FVector& InDirection);` — Arrow direction.
- L42 _public prototype_ `virtual FVector GetDirection() const;`
- L45 _public prototype_ `virtual void SetSideDirection(const FVector& InSideDirection);` — Arrow side direction for box head.
- L46 _public prototype_ `virtual FVector GetSideDirection() const;`
- L49 _public prototype_ `virtual void SetBodyLength(float InBodyLength);` — Arrow body length.
- L50 _public prototype_ `virtual float GetBodyLength() const;`
- L53 _public prototype_ `virtual void SetBodyRadius(float InBodyRadius);` — Arrow body cylinder radius.
- L54 _public prototype_ `virtual float GetBodyRadius() const;`
- L57 _public prototype_ `virtual void SetHeadLength(float InHeadLength);` — Arrow head length, used for both cone and cube head.
- L58 _public prototype_ `virtual float GetHeadLength() const;`
- L61 _public prototype_ `virtual void SetHeadRadius(float InHeadRadius);` — Arrow head radius, if cone.
- L62 _public prototype_ `virtual float GetHeadRadius() const;`
- L65 _public prototype_ `virtual void SetNumSides(int32 InNumSides);` — Number of sides for cylinder and cone, if relevant.
- L66 _public prototype_ `virtual int32 GetNumSides() const;`
- L69 _public prototype_ `virtual void SetEndCaps(bool InEndCaps);` — Whether to render and end cap on the base of the arrow head. Applicable when the ArrowHeadType is Cone.
- L70 _public prototype_ `virtual bool GetEndCaps() const;`
- L73 _public prototype_ `virtual void SetHeadType(EGizmoElementArrowHeadType InHeadType);` — Head type cone or cube.
- L74 _public prototype_ `virtual EGizmoElementArrowHeadType GetHeadType() const;`
- L77 _public prototype_ `virtual void SetIsDashed(bool bInDashing);` — Whether to render the body element with dashing.
- L78 _public prototype_ `virtual bool IsDashed() const;`
- L81 _public prototype_ `virtual void SetDashParameters(const float InDashLength = 10.0f, const TOptional<float>& InGapLength = TOptional<float>());` — The dash parameters for the body element, if enabled. If GapLength is not specified, it defaults to half DashLength.
- L82 _public prototype_ `virtual void GetDashParameters(float& OutDashLength, float& OutGapLength) const;`
- L85 _public prototype_ `virtual void SetPixelHitDistanceThreshold(float InPixelHitDistanceThreshold) override;` — Pixel hit distance threshold, element will be scaled enough to add this threshold when line-tracing.
- L88 _public prototype_ `virtual void SetMinimumPixelHitDistanceThreshold(float InMinimumPixelHitDistanceThreshold) override;` — Minimum Pixel hit distance threshold, element will be scaled enough to add this threshold when line-tracing.
- L91 _public prototype_ `void SetHitMask(const TWeakObjectPtr<UGizmoElementBase>& InHitMask);` — Hit Mask Gizmo element used for adaptive pixel hit threshold
- L96 _protected prototype_ `virtual void UpdateArrowBody();` — Update arrow cylinder based on parameters
- L99 _protected prototype_ `virtual void UpdateArrowHead();` — Update arrow cone or box based on parameters
- L102 _protected member_ `bool bUpdateArrowBody = true;` — Flag indicating body properties need to be updated prior to render
- L105 _protected member_ `bool bUpdateArrowHead = true;` — Flag indicating head properties need to be updated prior to render
- L109 _protected member_ `TObjectPtr<UGizmoElementCylinder> CylinderElement;` — `UPROPERTY()` — Arrow cylinder body
- L113 _protected member_ `TObjectPtr<UGizmoElementArrowHead> HeadElement;` — `UPROPERTY()` — Arrow head
- L117 _protected member_ `FVector Base = FVector::ZeroVector;` — `UPROPERTY()` — Location of center of arrow base circle.
- L121 _protected member_ `FVector Direction = FVector(0.0f, 0.0f, 1.0f);` — `UPROPERTY()` — Direction of arrow axis
- L125 _protected member_ `FVector SideDirection = FVector(0.0f, 1.0f, 0.0f);` — `UPROPERTY()` — Side direction for box head
- L129 _protected member_ `float BodyLength = 1.5f;` — `UPROPERTY()` — Arrow body length
- L133 _protected member_ `float BodyRadius = 0.5f;` — `UPROPERTY()` — Radius of arrow cylinder
- L137 _protected member_ `float HeadLength = 0.5f;` — `UPROPERTY()` — Length of head, cone or box
- L141 _protected member_ `float HeadRadius = 0.75f;` — `UPROPERTY()` — Radius of head cone
- L145 _protected member_ `int32 NumSides = 32;` — `UPROPERTY()` — Number of sides for tessellating cone and cylinder
- L149 _protected member_ `bool bEndCaps = false;` — `UPROPERTY()` — Whether to render an end cap on the base of the arrow head.
- L153 _protected member_ `EGizmoElementArrowHeadType HeadType = EGizmoElementArrowHeadType::Cone;` — `UPROPERTY()` — Head type
- L157 _protected member_ `TWeakObjectPtr<UGizmoElementBase> HitMask = nullptr;` — `UPROPERTY()` — Hit mask

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/GizmoElementArrowHead.h` (Public)


#### enum `EGizmoElementArrowHeadType`  
`enum class EGizmoElementArrowHeadType`  
_L15-21_
- reflection: `UENUM()`
- L17 _public enumerator_ `None`
- L18 _public enumerator_ `Cone`
- L19 _public enumerator_ `Cube`
- L20 _public enumerator_ `Sphere`

#### class `UGizmoElementArrowHead`  
`class UGizmoElementArrowHead : public UGizmoElementGroupBase`  
_L28-127_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UGizmoElementGroupBase`
- desc: Simple object intended to be used as part of 3D Gizmos. Draws a 3D arrowhead based on parameters.
- L33 _public prototype_ `UGizmoElementArrowHead();`
- L36 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI, const FRenderTraversalState& RenderState) override;`
- L37 _public prototype_ `virtual FInputRayHit LineTrace(const UGizmoViewContext* ViewContext, const FLineTraceTraversalState& LineTraceState, const FVector& RayOrigin, const FVector& RayDirection, FLineTraceOutput& OutLineTraceOutput) override;`
- L41 _public prototype_ `virtual void SetCenter(const FVector& InCenter);` — Location of center of the arrow head
- L42 _public prototype_ `virtual FVector GetCenter() const;`
- L45 _public prototype_ `virtual void SetDirection(const FVector& InDirection);` — Arrow direction.
- L46 _public prototype_ `virtual FVector GetDirection() const;`
- L49 _public prototype_ `virtual void SetSideDirection(const FVector& InSideDirection);` — Arrow side direction for box head.
- L50 _public prototype_ `virtual FVector GetSideDirection() const;`
- L53 _public prototype_ `virtual void SetLength(float InLength);` — Arrow head length, used for both cone and cube head.
- L54 _public prototype_ `virtual float GetLength() const;`
- L57 _public prototype_ `virtual void SetRadius(float InRadius);` — Arrow head radius, if cone or sphere.
- L58 _public prototype_ `virtual float GetRadius() const;`
- L61 _public prototype_ `virtual void SetNumSides(int32 InNumSides);` — Number of sides for cylinder and cone, if relevant.
- L62 _public prototype_ `virtual int32 GetNumSides() const;`
- L65 _public prototype_ `virtual void SetType(EGizmoElementArrowHeadType InHeadType);` — Head type cone or cube.
- L66 _public prototype_ `virtual EGizmoElementArrowHeadType GetType() const;`
- L69 _public prototype_ `virtual void SetPixelHitDistanceThreshold(float InPixelHitDistanceThreshold) override;` — Pixel hit distance threshold, element will be scaled enough to add this threshold when line-tracing.
- L72 _public prototype_ `void SetHitMask(const TWeakObjectPtr<UGizmoElementBase>& InHitMask);` — Hit Mask Gizmo element used for adaptive pixel hit threshold
- L77 _protected prototype_ `virtual void Update();` — Update the appropriate shape based on parameters
- L82 _protected member_ `bool bUpdate = true;` — Flag indicating properties need to be updated prior to render
- L86 _protected member_ `TObjectPtr<UGizmoElementCone> ConeElement;` — `UPROPERTY()` — Cone head
- L90 _protected member_ `TObjectPtr<UGizmoElementBox> BoxElement;` — `UPROPERTY()` — Box head
- L94 _protected member_ `TObjectPtr<UGizmoElementSphere> SphereElement;` — `UPROPERTY()` — Sphere head
- L98 _protected member_ `FVector Center = FVector::ZeroVector;` — `UPROPERTY()` — Location of center
- L102 _protected member_ `FVector Direction = FVector(0.0f, 0.0f, 1.0f);` — `UPROPERTY()` — Direction of arrow axis
- L106 _protected member_ `FVector SideDirection = FVector(0.0f, 1.0f, 0.0f);` — `UPROPERTY()` — Side direction for box
- L110 _protected member_ `float Length = 0.5f;` — `UPROPERTY()` — Length of head, cone or box
- L114 _protected member_ `float Radius = 0.75f;` — `UPROPERTY()` — Radius of head cone
- L118 _protected member_ `int32 NumSides = 32;` — `UPROPERTY()` — Number of sides for tessellating cone and cylinder
- L122 _protected member_ `EGizmoElementArrowHeadType Type = EGizmoElementArrowHeadType::Cone;` — `UPROPERTY()` — Head type
- L126 _protected member_ `TWeakObjectPtr<UGizmoElementBase> HitMask = nullptr;` — `UPROPERTY()` — Hit mask

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/GizmoElementBase.h` (Public)


#### class `UGizmoElementBase`  
`class UGizmoElementBase : public UObject`  
_L25-746_
- reflection: `UCLASS(Transient, Abstract, MinimalAPI)`
- inherits: `UObject`
- desc: Base class for 2d and 3d primitive objects intended to be used as part of 3D Gizmos. Contains common properties and utility functions. This class does nothing by itself, use subclasses like UGizmoElementCylinder
- L33 _public member_ `static constexpr float DefaultViewDependentAngleTol = 0.052f;` — ~3 degrees
- L34 _public member_ `static constexpr float DefaultViewDependentAxialMaxCosAngleTol = 0.998f;` — Cos(DefaultViewDependentAngleTol)
- L35 _public member_ `static constexpr float DefaultViewDependentPlanarMinCosAngleTol = 0.052f;` — Cos(HALF_PI - DefaultViewDependentAngleTol)
- L37 _public member_ `static constexpr float DefaultViewAlignAngleTol = 0.052f;` — ~3 degrees
- L38 _public member_ `static constexpr float DefaultViewAlignMaxCosAngleTol = 0.998f;` — Cos(DefaultViewAlignAngleTol)
- L40 _public member_ `static constexpr uint32 DefaultPartIdentifier = 0;` — Default part ID, used for elements that are not associated with any gizmo part
- L158 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI, const FRenderTraversalState& RenderState) PURE_VIRTUAL(UGizmoElementBase::Render);` — Render enabled visible element.
- L161 _public prototype_ `virtual void DrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI, const FRenderTraversalState& RenderState);` — Do screen space drawing.
- L164 _public prototype_ `virtual FInputRayHit LineTrace(const UGizmoViewContext* ViewContext, const FLineTraceTraversalState& LineTraceState, const FVector& RayOrigin, const FVector& RayDirection, FLineTraceOutput& OutLineTraceOutput) PURE_VIRTUAL(UGizmoElementBase::LineTrace, return FInputRayHit(););` — Line trace enabled hittable element.
- L168 _public prototype_ `virtual FInputRayHit LineTrace(const UGizmoViewContext* ViewContext, const FLineTraceTraversalState& LineTraceState, const FVector& RayOrigin, const FVector& RayDirection);` — `UE_DEPRECATED(5.7, "Use the version of LineTrace that outputs FLineTraceOutput instead.")` — Line trace enabled hittable element.
- L171 _public prototype_ `virtual void SetVisibleState(bool bVisible);` — Set/get the visible bit in element state.
- L172 _public prototype_ `virtual bool GetVisibleState() const;`
- L175 _public prototype_ `virtual void SetHittableState(bool bHittable);` — Set/get the hittable bit in element state.
- L176 _public prototype_ `virtual bool GetHittableState() const;`
- L179 _public prototype_ `virtual void SetHitPriority(const int32 InHitPriority);` — Set/get the hit priority. When hits overlap, higher priority elements will be hit first. If two elements have the same priority, the one that was closest to the hit location will be returned.
- L180 _public prototype_ `virtual int32 GetHitPriority() const;`
- L184 _public prototype_ `virtual void SetEnabled(bool bInEnabled);` — Element enabled flag. Render and LineTrace only occur when bEnabled is true. This flag is useful for turning on and off an element globally while retaining its specific settings.
- L185 _public prototype_ `virtual bool GetEnabled() const;`
- L188 _public prototype_ `virtual void SetEnabledForPerspectiveProjection(bool bInEnabledForPerspectiveProjection);` — Whether element is enabled for perspective projections.
- L189 _public prototype_ `virtual bool GetEnabledForPerspectiveProjection();`
- L192 _public prototype_ `virtual void SetEnabledInOrthographicProjection(bool bInEnabledForOrthographicProjection);` — Whether element is enabled for orthographic projections.
- L193 _public prototype_ `virtual bool GetEnabledInOrthographicProjection();`
- L196 _public prototype_ `virtual void SetEnabledForDefaultState(bool bInEnabledForDefaultState);` — Whether element is enabled when element state is default.
- L197 _public prototype_ `virtual bool GetEnabledForDefaultState();`
- L200 _public prototype_ `virtual void SetEnabledForHoveringState(bool bInEnabledForHoveringState);` — Whether element is enabled when element state is hovering.
- L201 _public prototype_ `virtual bool GetEnabledForHoveringState();`
- L204 _public prototype_ `virtual void SetEnabledForInteractingState(bool bInEnabledForInteractingState);` — Whether element is enabled when element state is interacting.
- L205 _public prototype_ `virtual bool GetEnabledForInteractingState();`
- L208 _public prototype_ `virtual void SetEnabledForSelectedState(bool bInEnabledForSelectedState);` — Whether element is enabled when element state is selected.
- L209 _public prototype_ `virtual bool GetEnabledForSelectedState();`
- L212 _public prototype_ `virtual void SetEnabledForSubduedState(bool bInEnabledForSubduedState);` — Whether element is enabled when element state is subdued.
- L213 _public prototype_ `virtual bool GetEnabledForSubduedState();`
- L216 _public prototype_ `virtual void SetIsVisibleFunction( TUniqueFunction<bool( const FSceneView* InView, EViewInteractionState InCurrentViewInteractionState, EGizmoElementInteractionState InCurrentInteractionState, const FTransform& InLocalToWorldTransform, const FVector& InLocalCenter)>&& InIsVisibleFunction);` — Sets the custom visibility function. Note that this is called in addition to built-in logic rather than as a replacement.
- L222 _public prototype_ `virtual void SetIsHittableFunction( TUniqueFunction<bool(const UGizmoViewContext* InViewContext, const FTransform& InLocalToWorldTransform, const FVector& InLocalCenter)>&& InIsHittableFunction);` — Sets the custom hittability function. Note that this is called in addition to built-in logic rather than as a replacement.
- L230 _public prototype_ `virtual void SetPartIdentifier(uint32 InPartId);` — For an element hierarchy representing multiple parts of a single gizmo, the part identifier establishes a correspondence between a gizmo part and the elements that represent that part. The recognized part identifier values should be defined in the gizmo. Gizmo part identifiers must be greater than or equal to one. Identifier 0 is reserved for the default ID which should be assigned to elements that do not correspond to any gizmo part, such as non-hittable decorative elements.
- L231 _public prototype_ `virtual uint32 GetPartIdentifier();`
- L232 _public prototype_ `virtual uint32 GetPartIdentifier() const;`
- L236 _public prototype_ `virtual void SetPartIdentifier(uint32 InPartId, const bool bInOverrideUnsetChildren, const bool bInOverrideSet = true);` — Sets the part identifier for this element and all of its children whose current ID is 0/Default. If bInOverrideSet is true, the PartId will be set even if it's currently 0.
- L239 _public prototype_ `virtual UGizmoElementBase* FindPartElement(const uint32 InPartId);` — Returns the element associated with the specified part id, or nullptr if not found.
- L242 _public prototype_ `virtual const UGizmoElementBase* FindPartElement(const uint32 InPartId) const;` — Returns the element associated with the specified part id, or nullptr if not found.
- L245 _public prototype_ `virtual TConstArrayView<TObjectPtr<UGizmoElementBase>> GetSubElements() const;` — Get the (top-level) sub-elements, if any.
- L248 _public prototype_ `virtual void SetElementState(EGizmoElementState InElementState);` — Object type bitmask indicating whether this object is visible or hittable or both
- L249 _public prototype_ `virtual EGizmoElementState GetElementState() const;`
- L252 _public prototype_ `virtual void SetElementInteractionState(EGizmoElementInteractionState InInteractionState);` — Object interaction state - None, Hovering, Interacting, Selected or Subdued
- L253 _public prototype_ `virtual EGizmoElementInteractionState GetElementInteractionState() const;`
- L257 _public prototype_ `virtual bool UpdatePartVisibleState(bool bVisible, uint32 InPartIdentifier);` — `UE_DEPRECATED(5.7, "Use UpdatePartVisibleState with bInAllowMultipleElements instead.")` — Update element's visibility state if element is associated with the specified gizmo part, return true if part was found.
- L261 _public prototype_ `virtual bool UpdatePartVisibleState(bool bVisible, uint32 InPartIdentifier, bool bInAllowMultipleElements);` — Update element's visibility state if element is associated with the specified gizmo part, return true if part was found. Setting bAllowMultipleElements to true will allow multiple elements with the same Part Id to be updated.
- L264 _public prototype_ `virtual TOptional<bool> GetPartVisibleState(uint32 InPartIdentifier) const;` — Get element's visible state for element associated with the specified gizmo part, if part id was found.
- L268 _public prototype_ `virtual bool UpdatePartHittableState(bool bHittable, uint32 InPartIdentifier);` — `UE_DEPRECATED(5.7, "Use UpdatePartHittableState with bInAllowMultipleElements instead.")` — Update element's hittable state if element is associated with the specified gizmo part, return true if part id was found.
- L272 _public prototype_ `virtual bool UpdatePartHittableState(bool bHittable, uint32 InPartIdentifier, bool bInAllowMultipleElements);` — Update element's hittable state if element is associated with the specified gizmo part, return true if part id was found. Setting bAllowMultipleElements to true will allow multiple elements with the same Part Id to be updated.
- L275 _public prototype_ `virtual TOptional<bool> GetPartHittableState(uint32 InPartIdentifier) const;` — Get element's hittable state for element associated with the specified gizmo part, if part id was found.
- L279 _public prototype_ `virtual bool UpdatePartInteractionState(EGizmoElementInteractionState InInteractionState, uint32 InPartIdentifier);` — `UE_DEPRECATED(5.7, "Use UpdatePartInteractionState with bInAllowMultipleElements instead.")` — Update element's interaction state if element is associated with the specified gizmo part, return true if part id was found.
- L283 _public prototype_ `virtual bool UpdatePartInteractionState(EGizmoElementInteractionState InInteractionState, uint32 InPartIdentifier, bool bInAllowMultipleElements);` — Update element's interaction state if element is associated with the specified gizmo part, return true if part id was found. Setting bAllowMultipleElements to true will allow multiple elements with the same Part Id to be updated.
- L286 _public prototype_ `virtual TOptional<EGizmoElementInteractionState> GetPartInteractionState(uint32 InPartIdentifier) const;` — Get element's interaction state for element associated with the specified gizmo part, if part id was found.
- L289 _public prototype_ `virtual void SetViewDependentType(EGizmoElementViewDependentType ViewDependentType);` — View-dependent type - None, Axis or Plane.
- L290 _public prototype_ `virtual EGizmoElementViewDependentType GetViewDependentType() const;`
- L296 _public prototype_ `virtual void SetViewDependentAngleTol(float InMaxAngleTol);` — View-dependent angle tolerance in radians For Axis, object is culled when angle between view dependent axis and view direction is less than tolerance angle. For Planar, cos of angle between view dependent axis (plane normal) and view direction. When the view direction is within this tolerance from the plane or axis, this object will be culled.
- L297 _public prototype_ `virtual float GetViewDependentAngleTol() const;`
- L300 _public prototype_ `virtual void SetViewDependentAxis(FVector InAxis);` — View-dependent axis or plane normal, based on the view-dependent type.
- L301 _public prototype_ `virtual FVector GetViewDependentAxis() const;`
- L304 _public prototype_ `virtual void SetViewAlignType(EGizmoElementViewAlignType InViewAlignType);` — View align type: None, PointEye, PointOnly, or Axial.
- L305 _public prototype_ `virtual EGizmoElementViewAlignType GetViewAlignType() const;`
- L310 _public prototype_ `virtual void SetViewAlignAxis(FVector InAxis);` — View align axis. PointEye, PointScreen and PointOnly rotate this axis to align with view up. Axial rotates about this axis.
- L311 _public prototype_ `virtual FVector GetViewAlignAxis() const;`
- L317 _public prototype_ `virtual void SetViewAlignNormal(FVector InAxis);` — View align normal. PointEye rotates the normal to align with camera view direction. PointScreen rotates the normal to align with screen forward direction. Axial rotates the normal around the axis to align as closely as possible with the view direction.
- L318 _public prototype_ `virtual FVector GetViewAlignNormal() const;`
- L322 _public prototype_ `virtual void SetViewAlignAxialAngleTol(float InMaxAngleTol);` — View-align angle tolerance in radians. Viewer alignment will not occur when the viewing angle is within this angle of view align axis.
- L323 _public prototype_ `virtual float GetViewAlignAxialAngleTol() const;`
- L328 _public prototype_ `virtual void SetViewDepthOffset(float InViewDepthOffset);` — Additional view-space offset to apply to the element, affecting both visuals and the hit geometry. Greater values are further away from the camera. An example use case: A large sphere and view-facing rectangle are both at the origin, but the rectangle should draw on top of the sphere. The sphere would otherwise overlap the rectangle.
- L329 _public prototype_ `virtual float GetViewDepthOffset() const;`
- L332 _public prototype_ `virtual void SetPixelHitDistanceThreshold(float InPixelHitDistanceThreshold);` — True if the ray hit the actual surface, rather than within a proximity (specified by PixelHitDistanceThreshold in GizmoElements). bool bIsSurfaceHit = false; }; public: Render enabled visible element. virtual void Render(IToolsContextRenderAPI* RenderAPI, const FRenderTraversalState& RenderState) PURE_VIRTUAL(UGizmoElementBase::Render); Do screen space drawing. INTERACTIVETOOLSFRAMEWORK_API virtual void DrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI, const FRenderTraversalState& RenderState); Line trace enabled hittable element. virtual FInputRayHit LineTrace(const UGizmoViewContext* ViewContext, const FLineTraceTraversalState& LineTraceState, const FVector& RayOrigin, const FVector& RayDirection, FLineTraceOutput& OutLineTraceOutput) PURE_VIRTUAL(UGizmoElementBase::LineTrace, return FInputRayHit();); Line trace enabled hittable element. UE_DEPRECATED(5.7, "Use the version of LineTrace that outputs FLineTraceOutput instead.") INTERACTIVETOOLSFRAMEWORK_API virtual FInputRayHit LineTrace(const UGizmoViewContext* ViewContext, const FLineTraceTraversalState& LineTraceState, const FVector& RayOrigin, const FVector& RayDirection); Set/get the visible bit in element state. INTERACTIVETOOLSFRAMEWORK_API virtual void SetVisibleState(bool bVisible); INTERACTIVETOOLSFRAMEWORK_API virtual bool GetVisibleState() const; Set/get the hittable bit in element state. INTERACTIVETOOLSFRAMEWORK_API virtual void SetHittableState(bool bHittable); INTERACTIVETOOLSFRAMEWORK_API virtual bo
- L333 _public prototype_ `virtual float GetPixelHitDistanceThreshold() const;`
- L336 _public prototype_ `virtual void SetMinimumPixelHitDistanceThreshold(const float InMinimumPixelHitDistanceThreshold);` — Minimum pixel hit distance threshold, element will be scaled enough to add this threshold when line-tracing the "exact" element (useful for pixel-thin elements where an "exact" hit would be otherwise challenging to hit).
- L337 _public prototype_ `virtual float GetMinimumPixelHitDistanceThreshold() const;`
- L351 _public prototype_ `virtual void SetMaterial(TWeakObjectPtr<UMaterialInterface> InMaterial, bool InOverridesChildState = false);` — Set mesh render state material attribute. @param InMaterial - material to be set @param InOverridesChildState - when true, this material will override the material of all child elements.
- L354 _public prototype_ `virtual const UMaterialInterface* GetMaterial() const;` — Get mesh render state material attribute's value.
- L357 _public prototype_ `virtual bool DoesMaterialOverrideChildState() const;` — Get mesh render state material attribute's override setting.
- L360 _public prototype_ `virtual void ClearMaterial();` — Clear mesh render state material attribute.
- L365 _public prototype_ `virtual void SetHoverMaterial(TWeakObjectPtr<UMaterialInterface> InHoverMaterial, bool InOverridesChildState = false);` — Set mesh render state hover material attribute. @param InHoverMaterial - hover material to be set @param InOverridesChildState - when true, this hover material will override the material of all child elements.
- L368 _public prototype_ `virtual const UMaterialInterface* GetHoverMaterial() const;` — Get mesh render state hover material attribute's value.
- L371 _public prototype_ `virtual bool DoesHoverMaterialOverrideChildState() const;` — Get mesh render state hover material attribute's override setting.
- L374 _public prototype_ `virtual void ClearHoverMaterial();` — Clear mesh render state hover material attribute.
- L379 _public prototype_ `virtual void SetInteractMaterial(TWeakObjectPtr<UMaterialInterface> InInteractMaterial, bool InOverridesChildState = false);` — Set mesh render state interact material attribute. @param InInteractMaterial - interact material to be set @param InOverridesChildState - when true, this interact material will override the material of all child elements.
- L382 _public prototype_ `virtual const UMaterialInterface* GetInteractMaterial() const;` — Get mesh render state interact material attribute's value.
- L385 _public prototype_ `virtual bool DoesInteractMaterialOverrideChildState() const;` — Get mesh render state interact material attribute's override setting.
- L388 _public prototype_ `virtual void ClearInteractMaterial();` — Clear mesh render interact state material attribute.
- L393 _public prototype_ `virtual void SetSelectMaterial(TWeakObjectPtr<UMaterialInterface> InSelectMaterial, bool InOverridesChildState = false);` — Set mesh render state Select material attribute. @param InSelectMaterial - Select material to be set @param InOverridesChildState - when true, this Select material will override the material of all child elements.
- L396 _public prototype_ `virtual const UMaterialInterface* GetSelectMaterial() const;` — Get mesh render state Select material attribute's value.
- L399 _public prototype_ `virtual bool DoesSelectMaterialOverrideChildState() const;` — Get mesh render state Select material attribute's override setting.
- L402 _public prototype_ `virtual void ClearSelectMaterial();` — Clear mesh render Select state material attribute.
- L407 _public prototype_ `virtual void SetSubdueMaterial(TWeakObjectPtr<UMaterialInterface> InSubdueMaterial, bool InOverridesChildState = false);` — Set mesh render state Subdue material attribute. @param InSubdueMaterial - Subdue material to be set @param InOverridesChildState - when true, this Subdue material will override the material of all child elements.
- L410 _public prototype_ `virtual const UMaterialInterface* GetSubdueMaterial() const;` — Get mesh render state Subdue material attribute's value.
- L413 _public prototype_ `virtual bool DoesSubdueMaterialOverrideChildState() const;` — Get mesh render state Subdue material attribute's override setting.
- L416 _public prototype_ `virtual void ClearSubdueMaterial();` — Clear mesh render Subdue state material attribute.
- L421 _public prototype_ `virtual void SetVertexColor(FLinearColor InVertexColor, bool InOverridesChildState = false);` — Set mesh render state vertex color attribute. @param InVertexColor - vertex color to be set @param InOverridesChildState - when true, this vertex color will override the material of all child elements.
- L424 _public prototype_ `virtual FLinearColor GetVertexColor() const;` — Get mesh render state vertex color attribute's value.
- L427 _public prototype_ `virtual bool HasVertexColor() const;` — Returns true, if mesh render state vertex color attribute has been set.
- L430 _public prototype_ `virtual bool DoesVertexColorOverrideChildState() const;` — Get mesh render state vertex color attribute's override setting.
- L433 _public prototype_ `virtual void ClearVertexColor();` — Clear mesh render state vertex color attribute.
- L438 _public prototype_ `virtual void SetHoverVertexColor(FLinearColor InVertexColor, bool InOverridesChildState = false);` — Set mesh render state vertex color attribute. @param InVertexColor - vertex color to be set @param InOverridesChildState - when true, this vertex color will override the material of all child elements.
- L441 _public prototype_ `virtual FLinearColor GetHoverVertexColor() const;` — Get mesh render state vertex color attribute's value.
- L444 _public prototype_ `virtual bool HasHoverVertexColor() const;` — Returns true, if mesh render state vertex color attribute has been set.
- L447 _public prototype_ `virtual bool DoesHoverVertexColorOverrideChildState() const;` — Get mesh render state vertex color attribute's override setting.
- L450 _public prototype_ `virtual void ClearHoverVertexColor();` — Clear mesh render state vertex color attribute.
- L455 _public prototype_ `virtual void SetInteractVertexColor(FLinearColor InVertexColor, bool InOverridesChildState = false);` — Set mesh render state vertex color attribute. @param InVertexColor - vertex color to be set @param InOverridesChildState - when true, this vertex color will override the material of all child elements.
- L458 _public prototype_ `virtual FLinearColor GetInteractVertexColor() const;` — Get mesh render state vertex color attribute's value.
- L461 _public prototype_ `virtual bool HasInteractVertexColor() const;` — Returns true, if mesh render state vertex color attribute has been set.
- L464 _public prototype_ `virtual bool DoesInteractVertexColorOverrideChildState() const;` — Get mesh render state vertex color attribute's override setting.
- L467 _public prototype_ `virtual void ClearInteractVertexColor();` — Clear mesh render state vertex color attribute.
- L472 _public prototype_ `virtual void SetSelectVertexColor(FLinearColor InVertexColor, bool InOverridesChildState = false);` — Set mesh render state vertex color attribute. @param InVertexColor - vertex color to be set @param InOverridesChildState - when true, this vertex color will override the material of all child elements.
- L475 _public prototype_ `virtual FLinearColor GetSelectVertexColor() const;` — Get mesh render state vertex color attribute's value.
- L478 _public prototype_ `virtual bool HasSelectVertexColor() const;` — Returns true, if mesh render state vertex color attribute has been set.
- L481 _public prototype_ `virtual bool DoesSelectVertexColorOverrideChildState() const;` — Get mesh render state vertex color attribute's override setting.
- L484 _public prototype_ `virtual void ClearSelectVertexColor();` — Clear mesh render state vertex color attribute.
- L489 _public prototype_ `virtual void SetSubdueVertexColor(FLinearColor InVertexColor, bool InOverridesChildState = false);` — Set mesh render state vertex color attribute. @param InVertexColor - vertex color to be set @param InOverridesChildState - when true, this vertex color will override the material of all child elements.
- L492 _public prototype_ `virtual FLinearColor GetSubdueVertexColor() const;` — Get mesh render state vertex color attribute's value.
- L495 _public prototype_ `virtual bool HasSubdueVertexColor() const;` — Returns true, if mesh render state vertex color attribute has been set.
- L498 _public prototype_ `virtual bool DoesSubdueVertexColorOverrideChildState() const;` — Get mesh render state vertex color attribute's override setting.
- L501 _public prototype_ `virtual void ClearSubdueVertexColor();` — Clear mesh render state vertex color attribute.
- L507 _protected member_ `bool bEnabled = true;` — `UPROPERTY()` — Whether element is enabled. Render and LineTrace only occur when bEnabled is true.
- L511 _protected member_ `bool bEnabledForPerspectiveProjection = true;` — `UPROPERTY()` — Whether element is enabled for perspective projection
- L515 _protected member_ `bool bEnabledForOrthographicProjection = true;` — `UPROPERTY()` — Whether element is enabled for orthographic projection
- L519 _protected member_ `bool bEnabledForDefaultState = true;` — `UPROPERTY()` — Whether element is enabled when element state is default
- L523 _protected member_ `bool bEnabledForHoveringState = true;` — `UPROPERTY()` — Whether element is enabled when element state is hovering
- L527 _protected member_ `bool bEnabledForInteractingState = true;` — `UPROPERTY()` — Whether element is enabled when element state is interacting
- L531 _protected member_ `bool bEnabledForSelectedState = true;` — `UPROPERTY()` — Whether element is enabled when element state is selected
- L535 _protected member_ `bool bEnabledForSubduedState = true;` — `UPROPERTY()` — Whether element is enabled when element state is subdued
- L540 _protected member_ `const FSceneView* InView, EViewInteractionState InCurrentViewInteractionState, EGizmoElementInteractionState InCurrentInteractionState, const FTransform& InLocalToWorldTransform, const FVector& InLocalCenter)> IsVisibleFunction = nullptr;`
- L543 _protected member_ `TUniqueFunction<bool(const UGizmoViewContext* InViewContext, const FTransform& InLocalToWorldTransform, const FVector& InLocalCenter)> IsHittableFunction = nullptr;` — An optional custom function to determine hittability of the element. Note that this is called in addition to the built-in checks, not in place of it.
- L547 _protected member_ `uint32 PartIdentifier = DefaultPartIdentifier;` — `UPROPERTY()` — Part identifier
- L551 _protected member_ `FGizmoElementMeshRenderStateAttributes MeshRenderAttributes;` — `UPROPERTY()` — Mesh render state attributes for this element
- L555 _protected member_ `EGizmoElementState ElementState = EGizmoElementState::VisibleAndHittable;` — `UPROPERTY()` — Element state - indicates whether object is visible or hittable
- L559 _protected member_ `EGizmoElementInteractionState ElementInteractionState = EGizmoElementInteractionState::None;` — `UPROPERTY()` — Current element interaction state - None, Hovering, Interacting, Selected or Subdued
- L563 _protected member_ `EGizmoElementViewDependentType ViewDependentType = EGizmoElementViewDependentType::None;` — `UPROPERTY()` — View-dependent type - None, Axis or Plane.
- L567 _protected member_ `FVector ViewDependentAxis = FVector::UpVector;` — `UPROPERTY()` — View-dependent axis or plane normal, based on the view-dependent type.
- L574 _protected member_ `float ViewDependentAngleTol = DefaultViewDependentAngleTol;` — `UPROPERTY()` — View-dependent angle tolerance based on : For Axis, minimum radians between view dependent axis and view direction. For Planar, minimum radians between view dependent axis and the plane where axis is its normal. When the angle between the view direction and the axis/plane is less than this tolerance, this object should be culled.
- L579 _protected member_ `float ViewDependentAxialMaxCosAngleTol = DefaultViewDependentAxialMaxCosAngleTol;` — `UPROPERTY()` — Axial view alignment minimum cos angle tolerance, computed based on ViewDependentAngleTol. When the cos of the angle between the view direction and the axis is less than this value, this object should not be culled.
- L584 _protected member_ `float ViewDependentPlanarMinCosAngleTol = DefaultViewDependentPlanarMinCosAngleTol;` — `UPROPERTY()` — Planar view alignment minimum cos angle tolerance, computed based on ViewDependentAngleTol. When the cos of the angle between the view direction and the axis is greater than this value, this object should not be culled.
- L591 _protected member_ `EGizmoElementViewAlignType ViewAlignType = EGizmoElementViewAlignType::None;` — `UPROPERTY()` — View align type: None, PointEye, or PointWorld. PointEye rotates this axis to align with the view up axis. PointWorld rotates this axis to align with the world up axis. Axial rotates around this axis to align the normal as closely as possible to the view direction.
- L595 _protected member_ `FVector ViewAlignAxis = FVector::UpVector;` — `UPROPERTY()` — View align axis.
- L601 _protected member_ `FVector ViewAlignNormal = -FVector::ForwardVector;` — `UPROPERTY()` — View align normal. PointEye and PointWorld both rotate the normal to align with the view direction. Axial rotates the normal to align as closely as possible with view direction.
- L606 _protected member_ `float ViewAlignAxialAngleTol = DefaultViewAlignAngleTol;` — `UPROPERTY()` — Axial view alignment angle tolerance in radians, based on angle between align normal and view direction. When angle between the view align normal and the view direction is greater than this angle, the align rotation will be computed.
- L611 _protected member_ `float ViewAlignAxialMaxCosAngleTol = DefaultViewAlignMaxCosAngleTol;` — `UPROPERTY()` — Axial view alignment minimum cos angle tolerance, computed based on ViewAlignAxialAngleTol. When the cos of the angle between the view direction and the align normal is less than this value, the align rotation will be computed.
- L615 _protected member_ `float PixelHitDistanceThreshold = 7.0f;` — `UPROPERTY()` — Pixel hit distance threshold, element will be scaled enough to add this threshold when line-tracing.
- L619 _protected member_ `float MinimumPixelHitDistanceThreshold = 1.0f;` — `UPROPERTY()` — Minimum pixel hit distance threshold, element will be scaled enough to add this threshold when line-tracing the "exact" element (useful for pixel-thin elements where an "exact" hit would be otherwise challenging to hit).
- L623 _protected member_ `int32 HitPriority = 0;` — `UPROPERTY()` — When hits overlap, higher priority elements will be hit first. If two elements have the same priority, the one that was closest to the hit location will be returned.
- L629 _private member_ `float ViewDepthOffset = 0.0;` — `UPROPERTY()` — Additional view-space offset to apply to the element, affecting both visuals and the hit geometry.
- L634 _protected prototype_ `void ForEachSubElement(const TFunctionRef<void(UGizmoElementBase*)>& InFunc);` — Iterate over each top-level element (sub-element), excluding the element itself.
- L637 _protected prototype_ `void ForEachSubElementRecursive(const TFunctionRef<void(UGizmoElementBase*)>& InFunc) const;` — Iterate over each element (sub-element) in the element tree, excluding the element itself.
- L640 _protected prototype_ `void ForEachSubElementRecursive(const TFunctionRef<void(UGizmoElementBase*)>& InFunc, const uint32 InPartId) const;` — Iterate over each sub-element with the given Part Id in the element tree, excluding the element itself.
- L643 _protected prototype_ `bool GetSubElementsRecursive(TArray<TObjectPtr<UGizmoElementBase>>& OutElements) const;` — Get all sub-elements for the element tree, if any. Returns true if any sub-elements were found.
- L646 _protected prototype_ `bool GetSubElementsRecursive(TArray<TObjectPtr<UGizmoElementBase>>& OutElements, const uint32 InPartId) const;` — Get all sub-elements with the given Part Id for the element tree, if any. Returns true if any sub-elements were found.
- L649 _protected prototype_ `virtual bool IsVisible(const FSceneView* View, EViewInteractionState InCurrentViewInteractionState, EGizmoElementInteractionState InCurrentInteractionState, const FTransform& InLocalToWorldTransform, const FVector& InLocalCenter) const;` — Return whether element is currently visible.
- L654 _protected prototype_ `virtual bool IsVisible(const FSceneView* View, EGizmoElementInteractionState InCurrentInteractionState, const FTransform& InLocalToWorldTransform, const FVector& InLocalCenter) const;` — `UE_DEPRECATED(5.8, "Use IsVisible that accepts a ViewInteractionState instead.")` — Return whether element is currently visible.
- L658 _protected prototype_ `virtual bool IsHittable(const UGizmoViewContext* ViewContext, const FTransform& InLocalToWorldTransform, const FVector& InLocalCenter) const;` — Return whether element is currently hittable.
- L661 _protected prototype_ `virtual bool GetViewDependentVisibility(const FSceneView* View, const FTransform& InLocalToWorldTransform, const FVector& InLocalCenter) const;` — Returns whether object is visible in input FSceneView based on view-dependent visibility settings.
- L664 _protected prototype_ `virtual bool GetViewDependentVisibility(const UGizmoViewContext* View, const FTransform& InLocalToWorldTransform, const FVector& InLocalCenter) const;` — Returns whether object is visible in input gizmo view context based on view-dependent visibility settings
- L667 _protected prototype_ `virtual bool GetViewDependentVisibility(const FVector& InViewLocation, const FVector& InViewDirection, bool bInPerspectiveView, const FTransform& InLocalToWorldTransform, const FVector& InLocalCenter) const;` — Returns whether object is visible based on view-dependent visibility settings.
- L670 _protected prototype_ `virtual bool GetEnabledForInteractionState(EGizmoElementInteractionState InInteractionState) const;` — Returns whether element is enabled for given interaction state.
- L673 _protected prototype_ `virtual bool GetEnabledForViewProjection(bool bIsPerspectiveProjection) const;` — Returns whether element is enabled for given view projection type.
- L677 _protected prototype_ `virtual bool GetViewAlignRot(const FSceneView* View, const FTransform& InLocalToWorldTransform, const FVector& InLocalCenter, FQuat& OutAlignRot) const;` — Return whether this element has a view alignment rotation based on input FSceneView and view-dependent alignment settings. @param OutAlignRot the rotation to align this element in local space, should be prepended to the local-to-world transform.
- L681 _protected prototype_ `virtual bool GetViewAlignRot(const UGizmoViewContext* View, const FTransform& InLocalToWorldTransform, const FVector& InLocalCenter, FQuat& OutAlignRot) const;` — Return whether this element has a view alignment rotation based on input gizmo view context and view-dependent alignment settings. @param OutAlignRot the rotation to align this element in local space, should be prepended to the local-to-world transform.
- L685 _protected prototype_ `virtual bool GetViewAlignRot(const FVector& InViewLocation, const FVector& InViewDirection, const FVector& InViewUp, bool bInPerspectiveView, const FTransform& InLocalToWorldTransform, const FVector& InLocalCenter, FQuat& OutAlignRot) const;` — Return whether this element has a view alignment rotation based on input view parameters and view-dependent alignment settings. @param OutAlignRot the rotation to align this element in local space, should be prepended to the local-to-world transform.
- L687 _protected prototype_ `virtual void ApplyViewDepthOffset(const FSceneView* InView, const double& InViewDepthOffset, FTransform& InOutTransform) const;`
- L689 _protected prototype_ `virtual void ApplyViewDepthOffset(const FVector& InViewLocation, const FVector& InViewDirection, const bool bInIsPerspectiveView, FTransform& InOutTransform) const;`
- L691 _protected prototype_ `virtual void ApplyViewDepthOffset(const FVector& InViewLocation, const FVector& InViewDirection, const bool bInIsPerspectiveView, const double& InViewDepthOffset, FTransform& InOutTransform) const;`
- L694 _protected prototype_ `UMaterialInterface* GetMaterial();` — Get mesh render state material attribute's value.
- L697 _protected prototype_ `UMaterialInterface* GetHoverMaterial();` — Get mesh render state hover material attribute's value.
- L700 _protected prototype_ `UMaterialInterface* GetInteractMaterial();` — Get mesh render state interact material attribute's value.
- L703 _protected prototype_ `UMaterialInterface* GetSelectMaterial();` — Get mesh render state Select material attribute's value.
- L706 _protected prototype_ `UMaterialInterface* GetSubdueMaterial();` — Get mesh render state Subdue material attribute's value.
- L713 _protected prototype_ `virtual bool UpdateRenderState(IToolsContextRenderAPI* RenderAPI, const FVector& InLocalCenter, FRenderTraversalState& InOutRenderState);` — Update render state during render traversal, determines the current render state for this element @param RenderAPI - tools render context @param InLocalCenter - local element center position @param InOutRenderState - render state's local to world transform will be updated with translation to center and view-dependent alignment rotation, if applicable. @return view dependent visibility, true if this element is visible in the current view.
- L719 _protected prototype_ `virtual bool UpdateRenderState(IToolsContextRenderAPI* RenderAPI, const FVector& InLocalCenter, FRenderTraversalState& InOutRenderState, bool& bOutHasAlignRot, FQuat& OutAlignRot);` — Update render state during render traversal, determines the current render state for this element Same parameters as UpdateRenderState above plus two output parameters: @param bOutHasAlignRot - whether alignment rotation was applied to output state @param OutAlignRot - alignment rotation applied to output state, if applicable.
- L726 _protected prototype_ `virtual bool UpdateLineTraceState(const UGizmoViewContext* ViewContext, const FVector& InLocalCenter, FLineTraceTraversalState& InOutLineTraceState);` — Update line trace state during line trace traversal, determines the current state for this element @param ViewContext - current gizmo view context @param InLocalCenter - local element center position, this will update InOutLineTraceState's LocalToWorldTransform with a translation to LocalCenter @param InOutLineTraceState - line trace state's local to world transform will be updated with translation to center and view-dependent alignment rotation, if applicable. @return view dependent visibility, true if this element is visible in the current view.
- L732 _protected prototype_ `virtual bool UpdateLineTraceState(const UGizmoViewContext* ViewContext, const FVector& InLocalCenter, FLineTraceTraversalState& InOutRenderState, bool& bOutHasAlignRot, FQuat& OutAlignRot);` — Update line trace state during line trace traversal, determines the current state for this element Same parameters as UpdateLineTraceState above plus two output parameters: @param bOutHasAlignRot - whether alignment rotation was applied to output state @param OutAlignRot - alignment rotation applied to output state, if applicable.
- L735 _protected prototype_ `[[nodiscard]] virtual FInputRayHit MakeRayHit(const double InHitDepth, FLineTraceOutput& OutLineTraceOutput);` — Initialize ray hit for this element, injecting the Part Identifier, Hit Priority, etc.
- L741 _protected prototype_ `bool VerifyUniformScale(const FVector& Scale) const;` — Helper method to verify scale is uniform. If it is non-uniform, a one-time warning log is issued. Returns true if scale is uniform.
- L745 _protected prototype_ `FQuat GetAlignRotBetweenCoordSpaces(FVector SourceForward, FVector SourceRight, FVector SourceUp, FVector TargetForward, FVector TargetRight, FVector TargetUp) const;` — Helper method for view alignment. Returns rotation between source and target input coordinate spaces.

#### struct `UGizmoElementBase::FRenderTraversalState`  
`struct FRenderTraversalState`  
_L51-124_
- desc: Render traversal state structure used to maintain the current render state while rendering. As the gizmo element hierarchy is traversed, current state is maintained and updated. Element state attribute inheritance works as follows: - Child element state that is not set inherits from parent state. - Child element state that is set replaces the parent state, except in the case of overrides. - Overrides: parent element state with override set to true replaces all child state regardless of whether the child state has been set.
- L55 _public member_ `FTransform LocalToWorldTransform;` — LocalToWorld transform Note: non-uniform scale is not supported and the X scale element will be used for uniform scaling.
- L59 _public member_ `FVector FlattenScale = FVector::OneVector;` — The potentially flattened scale of this state, if this view is orthographic. Otherwise, a unit vector. When rendering gizmos, `FScaleMatrix(FlattenScale)` can be applied to a rendering matrix so that gizmos never clip into the near orthographic view plane, even at extreme distances.
- L62 _public member_ `double PixelToWorldScale = 1.0;` — Pixel to world scale. Also accounts for DPI scale, @see IToolsContextRenderAPI::ViewCameraState.
- L65 _public member_ `double DepthAtPixelToWorldReferencePoint = -1.0;` — The screen space depth of the reference point used to compute PixelToWorldScale. Defaults to -1.0 (unset). Should not be used if negative.
- L68 _public member_ `EGizmoElementInteractionState InteractionState = EGizmoElementInteractionState::None;` — Interact state, if not equal to none, overrides the element's interact state
- L71 _public member_ `FGizmoElementMeshRenderStateAttributes MeshRenderState;` — Current state used for rendering meshes
- L74 _public member_ `FGizmoElementLineRenderStateAttributes LineRenderState;` — Current state used for rendering lines
- L77 _public prototype_ `void Initialize(const UE::GizmoRenderingUtil::ISceneViewInterface& InView, const FTransform& InTransform, const double InDPIScale = 1.0);` — Initialize state
- L81 _public prototype_ `void Initialize(const FSceneView* InSceneView, FTransform InTransform, const double InDPIScale = 1.0);` — `UE_DEPRECATED(5.8, "Use Initialize with ISceneViewInterface instead.")` — Initialize state
- L84 _public function_ `const UMaterialInterface* GetCurrentMaterial()` — Returns the mesh material based on the current interaction state.
- L89 _public function_ `const UMaterialInterface* GetCurrentMaterial() const`
- L95 _public function_ `FLinearColor GetCurrentVertexColor()` — Returns the mesh vertex color based on the current interaction state.
- L101 _public function_ `FLinearColor GetCurrentVertexColor() const` — Returns the mesh vertex color based on the current interaction state.
- L107 _public function_ `FLinearColor GetCurrentLineColor()` — Returns the line color based on the current interaction state.
- L113 _public function_ `FLinearColor GetCurrentLineColor() const` — Returns the line color based on the current interaction state.
- L119 _public prototype_ `FScaleMatrix SafeFlattenMatrix() const;` — Returns the flatten scale if the LocalToWorldTransform is safe to flatten. Otherwise, returns an unscaled matrix.
- L123 _public prototype_ `FScaleMatrix SafeFlattenMatrix(const FTransform& InLocalToWorldTransform) const;` — Returns the flatten scale if the provided LocalToWorldTransform is safe to flatten. Otherwise, returns an unscaled matrix. Useful if the transform matrix is altered elsewhere, and you need to ensure proper scaling for rendering.

#### struct `UGizmoElementBase::FLineTraceTraversalState`  
`struct FLineTraceTraversalState`  
_L126-143_
- L130 _public member_ `FTransform LocalToWorldTransform;` — LocalToWorld transform Note: non-uniform scale is not supported and the X scale element will be used for uniform scaling.
- L133 _public member_ `double PixelToWorldScale = 1.0;` — Pixel to world scale
- L136 _public member_ `bool bIsPerspectiveProjection = true;` — View context is perspective projection
- L139 _public member_ `EGizmoElementHitSortType HitSortType = EGizmoElementHitSortType::Closest;` — The criteria that determines the singular element when multiple are hit.
- L142 _public prototype_ `void Initialize(const UGizmoViewContext* InGizmoViewContext, FTransform InTransform);` — Initialize state

#### struct `UGizmoElementBase::FLineTraceOutput`  
`struct FLineTraceOutput`  
_L146-153_
- desc: Contains information about a line trace, in addition to FInputRayHit.
- L149 _public member_ `int32 HitPriority = 0;` — Client-defined hit priority. Higher priorities can optionally be used to prefer one hit over another
- L152 _public member_ `bool bIsSurfaceHit = false;` — True if the ray hit the actual surface, rather than within a proximity (specified by PixelHitDistanceThreshold in GizmoElements).

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/GizmoElementBox.h` (Public)


#### class `UGizmoElementBox`  
`class UGizmoElementBox : public UGizmoElementBase`  
_L17-61_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UGizmoElementBase`
- L24 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI, const FRenderTraversalState& RenderState) override;`
- L25 _public prototype_ `virtual FInputRayHit LineTrace(const UGizmoViewContext* ViewContext, const FLineTraceTraversalState& LineTraceState, const FVector& RayOrigin, const FVector& RayDirection, FLineTraceOutput& OutLineTraceOutput) override;`
- L29 _public prototype_ `virtual void SetCenter(const FVector& InCenter);` — Location of center of box's base.
- L30 _public prototype_ `virtual FVector GetCenter() const;`
- L33 _public prototype_ `virtual void SetUpDirection(const FVector& InUpDirection);` — Box axis up direction.
- L34 _public prototype_ `virtual FVector GetUpDirection() const;`
- L37 _public prototype_ `virtual void SetSideDirection(const FVector& InSideDirection);` — Box axis side direction.
- L38 _public prototype_ `virtual FVector GetSideDirection() const;`
- L41 _public prototype_ `virtual void SetDimensions(const FVector& InDimensions);` — Box dimensions.
- L42 _public prototype_ `virtual FVector GetDimensions() const;`
- L48 _protected member_ `FVector Center = FVector::ZeroVector;` — `UPROPERTY()` — Location of center of box
- L52 _protected member_ `FVector Dimensions = FVector(1.0f, 1.0f, 1.0f);` — `UPROPERTY()` — Box dimensions
- L56 _protected member_ `FVector UpDirection = FVector::UpVector;` — `UPROPERTY()` — Box up axis, corresponds to Z dimension
- L60 _protected member_ `FVector SideDirection = FVector::RightVector;` — `UPROPERTY()` — Box side axis, corresponds to Y dimension

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/GizmoElementCircle.h` (Public)


#### class `UGizmoElementCircle`  
`class UGizmoElementCircle : public UGizmoElementCircleBase`  
_L18-61_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UGizmoElementCircleBase`
- desc: Simple object intended to be used as part of 3D Gizmos. Draws a filled or line circle based on parameters. The circle element does not yet support partial circles.
- L24 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI, const FRenderTraversalState& RenderState) override;`
- L25 _public prototype_ `virtual FInputRayHit LineTrace(const UGizmoViewContext* ViewContext, const FLineTraceTraversalState& LineTraceState, const FVector& RayOrigin, const FVector& RayDirection, FLineTraceOutput& OutLineTraceOutput) override;`
- L29 _public prototype_ `virtual void SetDrawMesh(bool InDrawMesh);` — Draw mesh
- L30 _public prototype_ `virtual bool GetDrawMesh() const;`
- L33 _public prototype_ `virtual void SetDrawLine(bool InDrawLine);` — Draw line
- L34 _public prototype_ `virtual bool GetDrawLine() const;`
- L37 _public prototype_ `virtual void SetHitMesh(bool InHitMesh);` — Hit mesh
- L38 _public prototype_ `virtual bool GetHitMesh() const;`
- L41 _public prototype_ `virtual void SetHitLine(bool InHitLine);` — Hit line
- L42 _public prototype_ `virtual bool GetHitLine() const;`
- L48 _protected member_ `bool bDrawMesh = true;` — `UPROPERTY()` — Whether to render solid circle.
- L52 _protected member_ `bool bDrawLine = false;` — `UPROPERTY()` — Whether to render line circle.
- L56 _protected member_ `bool bHitMesh = true;` — `UPROPERTY()` — Whether to perform hit test on mesh.
- L60 _protected member_ `bool bHitLine = false;` — `UPROPERTY()` — Whether to perform hit test on line.

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/GizmoElementCircleBase.h` (Public)


#### class `UGizmoElementCircleBase`  
`class UGizmoElementCircleBase : public UGizmoElementLineBase`  
_L18-160_
- reflection: `UCLASS(Transient, Abstract, MinimalAPI)`
- inherits: `UGizmoElementLineBase`
- desc: Abstract base object for circle, torus and arc.
- L27 _public prototype_ `virtual void SetCenter(const FVector& InCenter);` — CircleBase center.
- L28 _public prototype_ `virtual FVector GetCenter() const;`
- L33 _public prototype_ `virtual void SetAxis0(const FVector& InAxis0);` — `UE_DEPRECATED(5.8, "Use SetAxisBitangent instead")` — Axis0 (or the Bitangent axis) of the plane in which the circle lies, must be perpendicular to the normal and tangent. Start and end angles for partial circles are relative to this axis.
- L37 _public prototype_ `virtual void SetAxisBitangent(const FVector& InAxisBitangent);` — Bitangent axis of the plane in which the circle lies, must be perpendicular to Axis1/Tangent. Start and end angles for partial circles are relative to this axis.
- L40 _public prototype_ `virtual FVector GetAxis0() const;` — `UE_DEPRECATED(5.8, "Use GetAxisBitangent instead")`
- L43 _public prototype_ `virtual FVector GetAxisBitangent() const;` — Bitangent axis of the plane in which the circle lies, must be perpendicular to Axis1/Tangent.
- L47 _public prototype_ `virtual void SetAxis1(const FVector& InAxis1);` — `UE_DEPRECATED(5.8, "Use SetAxisTangent instead")` — Axis1 (usually the "Side" axis) of the plane in which circle lies, must be perpendicular to Axis0.
- L50 _public prototype_ `virtual void SetAxisTangent(const FVector& InAxisTangent);` — Tangent axis of the plane in which the circle lies, must be perpendicular to the normal and bitangent.
- L53 _public prototype_ `virtual FVector GetAxis1() const;` — `UE_DEPRECATED(5.8, "Use GetAxisTangent instead")`
- L56 _public prototype_ `virtual FVector GetAxisTangent() const;` — Tangent axis of the plane in which the circle lies, must be perpendicular to the normal and bitangent.
- L59 _public prototype_ `virtual void SetRadius(double InRadius);` — Circle radius.
- L60 _public prototype_ `virtual double GetRadius() const;`
- L63 _public prototype_ `virtual void SetHoverRadiusMultiplier(double InHoverRadiusMultiplier);` — Multiplier applied to the circle radius when hovering
- L64 _public prototype_ `virtual double GetHoverRadiusMultiplier() const;`
- L67 _public prototype_ `virtual void SetInteractRadiusMultiplier(double InInteractRadiusMultiplier);` — Multiplier applied to the circle radius when interacting
- L68 _public prototype_ `virtual double GetInteractRadiusMultiplier() const;`
- L71 _public prototype_ `virtual void SetSelectRadiusMultiplier(double InSelectRadiusMultiplier);` — Multiplier applied to the circle radius when selected
- L72 _public prototype_ `virtual double GetSelectRadiusMultiplier() const;`
- L75 _public prototype_ `virtual void SetSubdueRadiusMultiplier(double InSubdueRadiusMultiplier);` — Multiplier applied to the circle radius when subdued
- L76 _public prototype_ `virtual double GetSubdueRadiusMultiplier() const;`
- L79 _public prototype_ `virtual void SetNumSegments(int32 InNumSegments);` — Number of segments for rendering circle.
- L80 _public prototype_ `virtual int32 GetNumSegments() const;`
- L84 _public prototype_ `virtual void SetPartialType(EGizmoElementPartialType InPartial);` — When Partial, renders partial arc based on angle. When PartialViewDependent, same as Partial but renders full arc when arc normal aligns with view direction
- L85 _public prototype_ `virtual EGizmoElementPartialType GetPartialType() const;`
- L88 _public prototype_ `virtual void SetPartialStartAngle(double InPartialAngle);` — Start of arc angle of partial torus in radians, relative to Axis0.
- L89 _public prototype_ `virtual double GetPartialStartAngle() const;`
- L92 _public prototype_ `virtual void SetPartialEndAngle(double InPartialAngle);` — Start of arc angle of partial torus in radians, relative to Axis1.
- L93 _public prototype_ `virtual double GetPartialEndAngle() const;`
- L97 _public prototype_ `virtual void SetPartialViewDependentMaxCosTol(double InPartialViewDependentMaxCosTol);` — If partial type is PartialViewDependent, when the cosine of angle between the normal and view direction is within this tolerance, the arc will be rendered as full rather than partial
- L98 _public prototype_ `virtual double GetPartialViewDependentMaxCosTol() const;`
- L104 _protected member_ `FVector Center = FVector::ZeroVector;` — `UPROPERTY()` — CircleBase center.
- L109 _protected member_ `FVector Axis0 = FVector::RightVector;` — `UPROPERTY()` — Axis0 of plane in which circle lies, must perpendicular to normal. Start and end angles for partial circles are relative to this axis.
- L113 _protected member_ `FVector Axis1 = FVector::ForwardVector;` — `UPROPERTY()` — Axis1 of plane in which circle lies, must perpendicular to Axis0.
- L117 _protected member_ `double Radius = 100.0;` — `UPROPERTY()` — Radius of main circle, some derived elements have inner radius (e.g. torus and arc)
- L121 _protected member_ `FGizmoPerStateValueDouble RadiusMultiplier;` — `UPROPERTY()` — Optional radius multipliers to apply when hovering, interacting, selected or subdued.
- L125 _protected member_ `int32 NumSegments = 64;` — `UPROPERTY()` — Number of segments for rendering arc.
- L129 _protected member_ `EGizmoElementPartialType PartialType = EGizmoElementPartialType::None;` — `UPROPERTY()` — True when the arc is not full.
- L133 _protected member_ `double PartialStartAngle = 0.0;` — `UPROPERTY()` — Start angle to render for partial torus
- L137 _protected member_ `double PartialEndAngle = UE_DOUBLE_TWO_PI;` — `UPROPERTY()`
- L142 _protected member_ `double PartialViewDependentMaxCosTol = 0.96f;` — `UPROPERTY()` — For PartialViewDependent, max cosine of angle between the normal and view direction Within this tolerance, the arc will be rendered as full rather than partial
- L147 _protected prototype_ `double GetCurrentRadius() const;` — Returns the current radius based on the current interaction state.
- L150 _protected prototype_ `bool IsPartial(const FSceneView* View, const FVector& InWorldCenter, const FVector& InWorldNormal);` — Returns whether element should be partial based on current view
- L153 _protected prototype_ `bool IsPartial(const UGizmoViewContext* ViewContext, const FVector& InWorldCenter, const FVector& InWorldNormal);` — Returns whether element should be partial based on current view
- L156 _protected prototype_ `bool IsPartial(const FVector& InWorldCenter, const FVector& InWorldNormal, const FVector& InViewLocation, const FVector& InViewDirection, const bool bIsPerspectiveProjection);` — Returns whether element should be partial based on current view

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/GizmoElementCone.h` (Public)


#### class `UGizmoElementCone`  
`class UGizmoElementCone : public UGizmoElementBase`  
_L17-77_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UGizmoElementBase`
- L24 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI, const FRenderTraversalState& RenderState) override;`
- L25 _public prototype_ `virtual FInputRayHit LineTrace(const UGizmoViewContext* ViewContext, const FLineTraceTraversalState& LineTraceState, const FVector& RayOrigin, const FVector& RayDirection, FLineTraceOutput& OutLineTraceOutput) override;`
- L29 _public prototype_ `virtual void SetOrigin(const FVector& InBase);` — Cone tip location.
- L30 _public prototype_ `virtual FVector GetOrigin() const;`
- L33 _public prototype_ `virtual void SetDirection(const FVector& InDirection);` — Cone axis direction pointing from tip toward base of cone.
- L34 _public prototype_ `virtual FVector GetDirection() const;`
- L37 _public prototype_ `virtual void SetHeight(float InHeight);` — Cone height.
- L38 _public prototype_ `virtual float GetHeight() const;`
- L41 _public prototype_ `virtual void SetRadius(float InRadius);` — Cone radius.
- L42 _public prototype_ `virtual float GetRadius() const;`
- L45 _public prototype_ `virtual void SetNumSides(int32 InNumSides);` — Number of sides for tessellating cone.
- L46 _public prototype_ `virtual int32 GetNumSides() const;`
- L49 _public prototype_ `virtual void SetEndCaps(bool InEndCaps);` — Whether to render and end cap on the base of the cone.
- L50 _public prototype_ `virtual bool GetEndCaps() const;`
- L56 _protected member_ `FVector Origin = FVector::ZeroVector;` — `UPROPERTY()` — Cone tip location.
- L60 _protected member_ `FVector Direction = FVector(0.0f, 0.0f, -1.0f);` — `UPROPERTY()` — Cone axis direction pointing from tip toward base of cone.
- L64 _protected member_ `float Height = 1.0f;` — `UPROPERTY()` — Cone height.
- L68 _protected member_ `float Radius = 0.5f;` — `UPROPERTY()` — Cone radius.
- L72 _protected member_ `int32 NumSides = 32;` — `UPROPERTY()` — Number of sides for tessellating cone.
- L76 _protected member_ `bool bEndCaps = false;` — `UPROPERTY()` — Whether to render and end cap on the base of the cone.

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/GizmoElementCylinder.h` (Public)


#### class `UGizmoElementCylinder`  
`class UGizmoElementCylinder : public UGizmoElementBase`  
_L17-97_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UGizmoElementBase`
- L24 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI, const FRenderTraversalState& RenderState) override;`
- L25 _public prototype_ `virtual FInputRayHit LineTrace(const UGizmoViewContext* ViewContext, const FLineTraceTraversalState& LineTraceState, const FVector& RayOrigin, const FVector& RayDirection, FLineTraceOutput& OutLineTraceOutput) override;`
- L29 _public prototype_ `virtual void SetBase(const FVector& InBase);` — Location of center of cylinder's base circle.
- L30 _public prototype_ `virtual FVector GetBase() const;`
- L33 _public prototype_ `virtual void SetDirection(const FVector& InDirection);` — Cylinder axis direction.
- L34 _public prototype_ `virtual FVector GetDirection() const;`
- L37 _public prototype_ `virtual void SetHeight(float InHeight);` — Cylinder height.
- L38 _public prototype_ `virtual float GetHeight() const;`
- L41 _public prototype_ `virtual void SetRadius(float InRadius);` — Cylinder radius.
- L42 _public prototype_ `virtual float GetRadius() const;`
- L45 _public prototype_ `virtual void SetNumSides(int32 InNumSides);` — Number of sides for tessellating cylinder.
- L46 _public prototype_ `virtual int32 GetNumSides() const;`
- L49 _public prototype_ `virtual void SetIsDashed(bool bInDashing);` — Whether to render with dashing.
- L50 _public prototype_ `virtual bool GetIsDashed() const;`
- L53 _public prototype_ `virtual void SetDashParameters(const float InDashLength = 10.0f, const TOptional<float>& InGapLength = TOptional<float>());` — The dash parameter, if enabled. If GapLength is not specified, it defaults to half DashLength.
- L54 _public prototype_ `virtual void GetDashParameters(float& OutDashLength, float& OutGapLength) const;`
- L57 _public prototype_ `virtual void SetScreenSpace(bool bInScreenSpace);` — Whether the radius, dash length and spacing (if applicable) are in screen space
- L58 _public prototype_ `virtual bool GetScreenSpace() const;`
- L64 _protected member_ `FVector Base = FVector::ZeroVector;` — `UPROPERTY()` — Location of center of cylinder's base circle.
- L68 _protected member_ `FVector Direction = FVector(0.0f, 0.0f, 1.0f);` — `UPROPERTY()` — Cylinder axis direction.
- L72 _protected member_ `float Height = 1.0f;` — `UPROPERTY()` — Cylinder height.
- L76 _protected member_ `float Radius = 0.5f;` — `UPROPERTY()` — Cylinder radius.
- L80 _protected member_ `int32 NumSides = 32;` — `UPROPERTY()` — Number of sides for tessellating cylinder.
- L84 _protected member_ `bool bIsDashed = false;` — `UPROPERTY()` — Whether to render with dashing.
- L88 _protected member_ `float DashLength = 10.0f;` — `UPROPERTY()` — The Dash Length, if Dashing is enabled.
- L92 _protected member_ `float DashGapLength = 5.0f;` — `UPROPERTY()` — The Dash Gap Length, if Dashing is enabled.
- L96 _protected member_ `bool bScreenSpace = false;` — `UPROPERTY(Getter = "GetScreenSpace", Setter = "SetScreenSpace")` — Whether the radius, dash length and spacing (if applicable) are in screen space

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/GizmoElementGroup.h` (Public)


#### class `UGizmoElementGroupBase`  
`class UGizmoElementGroupBase : public UGizmoElementLineBase`  
_L16-101_
- reflection: `UCLASS(Transient, Abstract, MinimalAPI)`
- inherits: `UGizmoElementLineBase`
- desc: Simple group object intended to be used as part of 3D Gizmos. Contains multiple gizmo objects.
- L25 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI, const FRenderTraversalState& RenderState) override;`
- L26 _public prototype_ `virtual void DrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI, const FRenderTraversalState& RenderState) override;`
- L27 _public prototype_ `virtual FInputRayHit LineTrace(const UGizmoViewContext* ViewContext, const FLineTraceTraversalState& LineTraceState, const FVector& RayOrigin, const FVector& RayDirection, FLineTraceOutput& OutLineTraceOutput) override;`
- L33 _public prototype_ `virtual void SetPartIdentifier(uint32 InPartId, const bool bInOverrideUnsetChildren, const bool bInOverrideSet = true) override;` — Sets the part identifier for this element and all of its children whose current ID is 0/Default.
- L36 _public prototype_ `virtual UGizmoElementBase* FindPartElement(const uint32 InPartId) override;` — Returns the element associated with the specified part id, or nullptr if not found.
- L39 _public prototype_ `virtual const UGizmoElementBase* FindPartElement(const uint32 InPartId) const override;` — Returns the element associated with the specified part id, or nullptr if not found.
- L42 _public prototype_ `virtual TConstArrayView<TObjectPtr<UGizmoElementBase>> GetSubElements() const override;` — Get the (top-level) sub-elements, if any.
- L46 _public prototype_ `virtual bool UpdatePartVisibleState(bool bVisible, uint32 InPartIdentifier, bool bInAllowMultipleElements = false) override;` — Update group and contained elements' visibility state for elements in specified gizmo parts, return true if part was found. Setting bAllowMultipleElements to true will allow multiple elements with the same Part Id to be updated.
- L49 _public prototype_ `virtual TOptional<bool> GetPartVisibleState(uint32 InPartIdentifier) const override;` — Get element's visible state for element associated with the specified gizmo part, if part was found.
- L53 _public prototype_ `virtual bool UpdatePartHittableState(bool bHittable, uint32 InPartIdentifier, bool bInAllowMultipleElements = false) override;` — Update group and contained elements' hittable state for elements in specified gizmo parts, return true if part was found. Setting bAllowMultipleElements to true will allow multiple elements with the same Part Id to be updated.
- L56 _public prototype_ `virtual TOptional<bool> GetPartHittableState(uint32 InPartIdentifier) const override;` — Get element's hittable state for element associated with the specified gizmo part, if part was found.
- L60 _public prototype_ `virtual bool UpdatePartInteractionState(EGizmoElementInteractionState InInteractionState, uint32 InPartIdentifier, bool bInAllowMultipleElements = false) override;` — Update group and contained elements' interaction state for elements in specified gizmo parts, return true if part was found. Setting bAllowMultipleElements to true will allow multiple elements with the same Part Id to be updated.
- L63 _public prototype_ `virtual TOptional<EGizmoElementInteractionState> GetPartInteractionState(uint32 InPartIdentifier) const override;` — Get element's interaction state for element associated with the specified gizmo part, if part was found.
- L66 _public prototype_ `virtual void SetConstantScale(bool InConstantScale);` — When true, maintains view-dependent constant scale for this gizmo object hierarchy
- L67 _public prototype_ `virtual bool GetConstantScale() const;`
- L70 _public prototype_ `virtual void SetHitOwner(bool bInHitOwner);` — Set whether this group should be treated as a hit owner and its part identifier returned when any of its sub-elements are hit.
- L71 _public prototype_ `virtual bool GetHitOwner() const;`
- L76 _protected prototype_ `virtual void Add(UGizmoElementBase* InElement);` — Add object to group.
- L79 _protected prototype_ `virtual void Remove(UGizmoElementBase* InElement);` — Remove object from group, if it exists
- L85 _protected member_ `bool bConstantScale = false;` — `UPROPERTY()` — When true, maintains view-dependent constant scale for this gizmo object hierarchy
- L90 _protected member_ `bool bHitOwner = false;` — `UPROPERTY()` — When true, this group is treated as a single element such that when LineTrace is called, if any of its sub-elements is hit, this group will be returned as the owner of the hit. This should be used when a group of elements should be treated as a single handle.
- L94 _protected member_ `TArray<TObjectPtr<UGizmoElementBase>> Elements;` — `UPROPERTY()` — Gizmo elements within this group
- L97 _protected prototype_ `virtual void ApplyUniformConstantScaleToTransform(double PixelToWorldScale, FTransform& InOutLocalToWorldTransform) const;` — Updates input transform's scale component to have uniform scale and applies constant scale if bConstantScale is true
- L100 _protected prototype_ `virtual void ApplyUniformConstantScaleToTransform(double PixelToWorldScale, FTransform& InOutLocalToWorldTransform, const bool bInForceApply) const;` — Updates input transform's scale component to have uniform scale and applies constant scale if bConstantScale or bInForceApply is true

#### class `UGizmoElementGroup`  
`class UGizmoElementGroup : public UGizmoElementGroupBase`  
_L108-119_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UGizmoElementGroupBase`
- desc: Simple group object intended to be used as part of 3D Gizmos. Contains multiple gizmo objects.

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/GizmoElementHitTargets.h` (Public)


#### class `UGizmoElementHitTarget`  
`class UGizmoElementHitTarget : public UObject, public IGizmoClickTarget`  
_L26-77_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,IGizmoClickTarget`
- desc: UGizmoElementHitTarget is an IGizmoClickTarget implementation that hit-tests any object derived from UGizmoElementBase This hit target should be used for hitting a whole gizmo element hierarchy. Use UGizmoElementHitMultiTarget, for hit targets that support hitting parts within a gizmo element hierarchy.
- L35 _public member_ `TObjectPtr<UGizmoElementBase> GizmoElement;` — `UPROPERTY()` — Gizmo element.
- L38 _public member_ `TObjectPtr<UGizmoViewContext> GizmoViewContext;` — `UPROPERTY()`
- L41 _public member_ `TObjectPtr<UTransformProxy> GizmoTransformProxy;` — `UPROPERTY()`
- L49 _public member_ `TFunction<bool(const FInputDeviceRay&)> Condition = nullptr;` — If set, this condition is checked before performing the hit test. This gives a way to disable the hit test without hiding the component. This is useful, for instance, in a repositionable transform gizmo in world-coordinate mode, where the rotation components need to be hittable for movement, but not for repositioning.
- L52 _public prototype_ `virtual FInputRayHit IsHit(const FInputDeviceRay& ClickPos) const;`
- L54 _public prototype_ `virtual void UpdateHoverState(bool bHovering) override;`
- L56 _public prototype_ `virtual void UpdateInteractingState(bool bInteracting) override;`
- L58 _public prototype_ `virtual void UpdateSelectedState(bool bInSelected) override;`
- L60 _public prototype_ `virtual void UpdateSubdueState(bool bSubdued) override;`
- L62 _public prototype_ `virtual void SetTransformAdjuster(const TSharedPtr<UE::GizmoRenderingUtil::IViewBasedTransformAdjuster>& InAdjuster) override;`
- L63 _public prototype_ `virtual TSharedPtr<UE::GizmoRenderingUtil::IViewBasedTransformAdjuster> GetTransformAdjuster() const override;`
- L66 _public prototype_ `static UGizmoElementHitTarget* Construct( UGizmoElementBase* InGizmoElement, UGizmoViewContext* InGizmoViewContext, UObject* Outer = (UObject*)GetTransientPackage());`
- L76 _protected member_ `TSharedPtr<UE::GizmoRenderingUtil::IViewBasedTransformAdjuster> TransformAdjuster = nullptr;` — An optional transform adjuster to apply when testing hit geometry. Note that while the name indicates it's view-based, it may also be used to apply any transform.

#### class `UGizmoElementHitMultiTarget`  
`class UGizmoElementHitMultiTarget : public UObject, public IGizmoClickMultiTarget`  
_L90-153_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,IGizmoClickMultiTarget`
- desc: UGizmoElementHitMultiTarget is an IGizmoClickMultiTarget implementation that hit-tests any object derived from UGizmoElementBase. This implementation is used for HitTargets which support hitting multiple parts within a gizmo element hierarchy. For a gizmo with multiple parts, the part identifier establishes a correspondence between a gizmo part and the elements representing that part within the hit target. The valid part identifiers should be defined in the gizmo. Identifier 0 is reserved for the default ID which should be assigned to elements that do not correspond to any gizmo part, such as non-hittable decorative elements.
- L99 _public member_ `TObjectPtr<UGizmoElementBase> GizmoElement;` — `UPROPERTY()` — Gizmo element.
- L102 _public member_ `TObjectPtr<UGizmoViewContext> GizmoViewContext;` — `UPROPERTY()`
- L105 _public member_ `TObjectPtr<UTransformProxy> GizmoTransformProxy;` — `UPROPERTY()`
- L113 _public member_ `TFunction<bool(const FInputDeviceRay&)> Condition = nullptr;` — If set, this condition is checked before performing the hit test. This gives a way to disable the hit test without hiding the component. This is useful, for instance, in a repositionable transform gizmo in world-coordinate mode, where the rotation components need to be hittable for movement, but not for repositioning.
- L116 _public prototype_ `virtual FInputRayHit IsHit(const FInputDeviceRay& ClickPos) const override;`
- L118 _public prototype_ `virtual void UpdateHoverState(bool bHovering, uint32 PartIdentifier) override;`
- L120 _public prototype_ `virtual void UpdateHoverState(bool bHovering, uint32 PartIdentifier, bool bInAllowMultipleElements);`
- L122 _public prototype_ `virtual void UpdateInteractingState(bool bInteracting, uint32 PartIdentifier) override;`
- L124 _public prototype_ `virtual void UpdateInteractingState(bool bInteracting, uint32 PartIdentifier, bool bInAllowMultipleElements);`
- L126 _public prototype_ `virtual void UpdateSelectedState(bool bInSelected, uint32 PartIdentifier) override;`
- L128 _public prototype_ `virtual void UpdateSelectedState(bool bInSelected, uint32 PartIdentifier, bool bInAllowMultipleElements);`
- L130 _public prototype_ `virtual void UpdateSubdueState(bool bInSubdued, uint32 PartIdentifier) override;`
- L132 _public prototype_ `virtual void UpdateSubdueState(bool bInSubdued, uint32 PartIdentifier, bool bInAllowMultipleElements);`
- L134 _public prototype_ `virtual void UpdateHittableState(bool bHittable, uint32 PartIdentifier) override;`
- L136 _public prototype_ `virtual void UpdateHittableState(bool bHittable, uint32 PartIdentifier, bool bInAllowMultipleElements);`
- L138 _public prototype_ `virtual void SetTransformAdjuster(const TSharedPtr<UE::GizmoRenderingUtil::IViewBasedTransformAdjuster>& InAdjuster) override;`
- L139 _public prototype_ `virtual TSharedPtr<UE::GizmoRenderingUtil::IViewBasedTransformAdjuster> GetTransformAdjuster() const override;`
- L142 _public prototype_ `static UGizmoElementHitMultiTarget* Construct( UGizmoElementBase* InGizmoElement, UGizmoViewContext* InGizmoViewContext, UObject* Outer = (UObject*)GetTransientPackage());`
- L152 _protected member_ `TSharedPtr<UE::GizmoRenderingUtil::IViewBasedTransformAdjuster> TransformAdjuster = nullptr;` — An optional transform adjuster to apply when testing hit geometry. Note that while the name indicates it's view-based, it may also be used to apply any transform.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace GizmoRenderingUtil` (scope `UE`)

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/GizmoElementLineBase.h` (Public)


#### class `UGizmoElementLineBase`  
`class UGizmoElementLineBase : public UGizmoElementBase`  
_L17-176_
- reflection: `UCLASS(Transient, Abstract, MinimalAPI)`
- inherits: `UGizmoElementBase`
- desc: Base class for 2d and 3d primitive objects which support line drawing, intended to be used as part of 3D Gizmos.
- L23 _public prototype_ `virtual float GetCurrentLineThickness(bool bPerspectiveView, float InViewFOV) const;` — Get line thickness for based on current element interaction state and view
- L26 _public prototype_ `virtual void SetLineThickness(float InLineThickness);` — Line thickness when rendering lines, 0.0 is valid and will render thinnest line
- L27 _public prototype_ `virtual float GetLineThickness() const;`
- L30 _public prototype_ `virtual void SetHoverLineThicknessMultiplier(float InHoverLineThicknessMultiplier);` — Multiplier applied to line thickness when hovering
- L31 _public prototype_ `virtual float GetHoverLineThicknessMultiplier() const;`
- L34 _public prototype_ `virtual void SetInteractLineThicknessMultiplier(float InInteractLineThicknessMultiplier);` — Multiplier applied to line thickness when interacting
- L35 _public prototype_ `virtual float GetInteractLineThicknessMultiplier() const;`
- L38 _public prototype_ `virtual void SetSelectLineThicknessMultiplier(float InSelectLineThicknessMultiplier);` — Multiplier applied to line thickness when selected
- L39 _public prototype_ `virtual float GetSelectLineThicknessMultiplier() const;`
- L42 _public prototype_ `virtual void SetSubdueLineThicknessMultiplier(float InSubdueLineThicknessMultiplier);` — Multiplier applied to line thickness when subdued
- L43 _public prototype_ `virtual float GetSubdueLineThicknessMultiplier() const;`
- L46 _public prototype_ `virtual void SetScreenSpaceLine(bool bInScreenSpaceLine);` — Whether line thickness is in screen space
- L47 _public prototype_ `virtual bool GetScreenSpaceLine() const;`
- L61 _public prototype_ `virtual void SetLineColor(FLinearColor InColor, bool InOverridesChildState = false);` — Set line render state line color attribute. @param InMaterial - line color to be set @param InOverridesChildState - when true, this line color will override the line color of all child elements.
- L64 _public prototype_ `virtual FLinearColor GetLineColor() const;` — Get line render state line color attribute's value.
- L67 _public prototype_ `virtual bool HasLineColor() const;` — Returns true if line render state line color attribute has been set.
- L70 _public prototype_ `virtual bool DoesLineColorOverrideChildState() const;` — Get line render state line color attribute's override setting.
- L73 _public prototype_ `virtual void ClearLineColor();` — Clear line render state line color attribute.
- L78 _public prototype_ `virtual void SetHoverLineColor(FLinearColor InColor, bool InOverridesChildState = false);` — Set line render state hover line color attribute. @param InMaterial - hover line color to be set @param InOverridesChildState - when true, this hover line color will override the line color of all child elements.
- L81 _public prototype_ `virtual FLinearColor GetHoverLineColor() const;` — Get line render state hover line color attribute's value.
- L84 _public prototype_ `virtual bool HasHoverLineColor() const;` — Returns true if line render state hover line color attribute has been set.
- L87 _public prototype_ `virtual bool DoesHoverLineColorOverrideChildState() const;` — Get line render state hover line color attribute's override setting.
- L90 _public prototype_ `virtual void ClearHoverLineColor();` — Clear line render state hover line color attribute.
- L95 _public prototype_ `virtual void SetInteractLineColor(FLinearColor InColor, bool InOverridesChildState = false);` — Set line render state interact line color attribute. @param InMaterial - interact line color to be set @param InOverridesChildState - when true, this interact line color will override the line color of all child elements.
- L98 _public prototype_ `virtual FLinearColor GetInteractLineColor() const;` — Get line render state interact line color attribute's value.
- L101 _public prototype_ `virtual bool HasInteractLineColor() const;` — Returns true if line render state interact line color attribute has been set.
- L104 _public prototype_ `virtual bool DoesInteractLineColorOverrideChildState() const;` — Get line render state interact line color attribute's override setting.
- L107 _public prototype_ `virtual void ClearInteractLineColor();` — Clear line render state interact line color attribute.
- L112 _public prototype_ `virtual void SetSelectLineColor(FLinearColor InColor, bool InOverridesChildState = false);` — Set line render state Select line color attribute. @param InColor - Select line color to be set @param InOverridesChildState - when true, this Select line color will override the line color of all child elements.
- L115 _public prototype_ `virtual FLinearColor GetSelectLineColor() const;` — Get line render state interact line color attribute's value.
- L118 _public prototype_ `virtual bool HasSelectLineColor() const;` — Returns true if line render state interact line color attribute has been set.
- L121 _public prototype_ `virtual bool DoesSelectLineColorOverrideChildState() const;` — Get line render state interact line color attribute's override setting.
- L124 _public prototype_ `virtual void ClearSelectLineColor();` — Clear line render state interact line color attribute.
- L129 _public prototype_ `virtual void SetSubdueLineColor(FLinearColor InColor, bool InOverridesChildState = false);` — Set line render state subdue line color attribute. @param InColor - subdue line color to be set @param InOverridesChildState - when true, this subdue line color will override the line color of all child elements.
- L132 _public prototype_ `virtual FLinearColor GetSubdueLineColor() const;` — Get line render state interact line color attribute's value.
- L135 _public prototype_ `virtual bool HasSubdueLineColor() const;` — Returns true if line render state interact line color attribute has been set.
- L138 _public prototype_ `virtual bool DoesSubdueLineColorOverrideChildState() const;` — Get line render state interact line color attribute's override setting.
- L141 _public prototype_ `virtual void ClearSubdueLineColor();` — Clear line render state interact line color attribute.
- L147 _protected member_ `FGizmoElementLineRenderStateAttributes LineRenderAttributes;` — `UPROPERTY()` — Line render state attributes for this element
- L151 _protected member_ `float LineThickness = 0.0;` — `UPROPERTY()` — Line thickness when rendering lines, must be >= 0.0, value of 0.0 will render thinnest line
- L155 _protected member_ `bool bScreenSpaceLine = true;` — `UPROPERTY()` — Whether line thickness is in screen space
- L159 _protected member_ `float HoverLineThicknessMultiplier = 2.0f;` — `UPROPERTY(EditAnywhere, Category = Options)` — Multiplier applied to line thickness when hovering
- L163 _protected member_ `float InteractLineThicknessMultiplier = 2.0f;` — `UPROPERTY(EditAnywhere, Category = Options)` — Multiplier applied to line thickness when interacting
- L167 _protected member_ `float SelectLineThicknessMultiplier = 2.0f;` — `UPROPERTY(EditAnywhere, Category = Options)` — Multiplier applied to line thickness when selected
- L171 _protected member_ `float SubdueLineThicknessMultiplier = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Options)` — Multiplier applied to line thickness when subdued
- L175 _protected prototype_ `virtual bool UpdateRenderState(IToolsContextRenderAPI* RenderAPI, const FVector& InLocalOrigin, FRenderTraversalState& InOutRenderState) override;` — Update render state during render traversal, determines the current render state for this element @return view dependent visibility, true if this element is visible in the current view.

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/GizmoElementLineStrip.h` (Public)


#### class `UGizmoElementLineStrip`  
`class UGizmoElementLineStrip : public UGizmoElementLineBase`  
_L19-75_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UGizmoElementLineBase`
- desc: Simple object intended to be used as part of 3D Gizmos. Draws a rectangle based on parameters.
- L26 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI, const FRenderTraversalState& RenderState) override;`
- L27 _public prototype_ `virtual FInputRayHit LineTrace(const UGizmoViewContext* ViewContext, const FLineTraceTraversalState& LineTraceState, const FVector& RayOrigin, const FVector& RayDirection, FLineTraceOutput& OutLineTraceOutput) override;`
- L31 _public prototype_ `virtual void SetVertices(const TArrayView<const FVector>& InVertices);` — The vertices of the line strip
- L32 _public prototype_ `virtual const TArray<FVector>& GetVertices() const;`
- L35 _public prototype_ `virtual void SetBase(FVector InBase);` — Base Location of the line strip
- L36 _public prototype_ `virtual FVector GetBase() const;`
- L39 _public prototype_ `virtual void SetUpDirection(const FVector& InUpDirection);` — Up direction
- L40 _public prototype_ `virtual FVector GetUpDirection() const;`
- L43 _public prototype_ `virtual void SetSideDirection(const FVector& InSideDirection);` — Side direction
- L44 _public prototype_ `virtual FVector GetSideDirection() const;`
- L47 _public prototype_ `virtual void SetDrawLineStrip(bool InDrawLineStrip);` — Defines if the vertices should be treated as a connected strip or separate line segments
- L48 _public prototype_ `virtual bool GetDrawLineStrip() const;`
- L52 _protected prototype_ `void ComputeProjectedVertices(const FTransform& InLocalToWorldTransform, bool bIncludeBase);`
- L56 _protected member_ `TArray<FVector> Vertices;` — `UPROPERTY()` — The vertices of the line strip
- L60 _protected member_ `FVector Base = FVector::ZeroVector;` — `UPROPERTY()` — Base Location of the line strip
- L64 _protected member_ `FVector UpDirection = FVector(0.0f, 0.0f, 1.0f);` — `UPROPERTY()` — Up direction
- L68 _protected member_ `FVector SideDirection = FVector(0.0f, 1.0f, 0.0f);` — `UPROPERTY()` — Side direction
- L72 _protected member_ `bool bDrawLineStrip = true;` — `UPROPERTY()` — Defines if the vertices should be treated as a connected strip or separate line segments
- L74 _protected member_ `TArray<FVector> ProjectedVertices;`

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/GizmoElementRectangle.h` (Public)


#### class `UGizmoElementRectangle`  
`class UGizmoElementRectangle : public UGizmoElementLineBase`  
_L19-99_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UGizmoElementLineBase`
- desc: Simple object intended to be used as part of 3D Gizmos. Draws a rectangle based on parameters.
- L26 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI, const FRenderTraversalState& RenderState) override;`
- L27 _public prototype_ `virtual FInputRayHit LineTrace(const UGizmoViewContext* ViewContext, const FLineTraceTraversalState& LineTraceState, const FVector& RayOrigin, const FVector& RayDirection, FLineTraceOutput& OutLineTraceOutput) override;`
- L31 _public prototype_ `virtual void SetCenter(FVector InCenter);` — Location of rectangle center
- L32 _public prototype_ `virtual FVector GetCenter() const;`
- L35 _public prototype_ `virtual void SetWidth(float InWidth);` — Width
- L36 _public prototype_ `virtual float GetWidth() const;`
- L39 _public prototype_ `virtual void SetHeight(float InHeight);` — Height
- L40 _public prototype_ `virtual float GetHeight() const;`
- L43 _public prototype_ `virtual void SetUpDirection(const FVector& InUpDirection);` — Up direction
- L44 _public prototype_ `virtual FVector GetUpDirection() const;`
- L47 _public prototype_ `virtual void SetSideDirection(const FVector& InSideDirection);` — Side direction
- L48 _public prototype_ `virtual FVector GetSideDirection() const;`
- L51 _public prototype_ `virtual void SetDrawMesh(bool InDrawMesh);` — Draw mesh
- L52 _public prototype_ `virtual bool GetDrawMesh() const;`
- L55 _public prototype_ `virtual void SetDrawLine(bool InDrawLine);` — Draw line
- L56 _public prototype_ `virtual bool GetDrawLine() const;`
- L59 _public prototype_ `virtual void SetHitMesh(bool InHitMesh);` — Hit mesh
- L60 _public prototype_ `virtual bool GetHitMesh() const;`
- L63 _public prototype_ `virtual void SetHitLine(bool InHitLine);` — Hit line
- L64 _public prototype_ `virtual bool GetHitLine() const;`
- L70 _protected member_ `FVector Center = FVector::ZeroVector;` — `UPROPERTY()` — Location of rectangle center
- L74 _protected member_ `float Width = 1.0f;` — `UPROPERTY()` — Width
- L78 _protected member_ `float Height = 1.0f;` — `UPROPERTY()` — Height
- L82 _protected member_ `FVector UpDirection = FVector(0.0f, 0.0f, 1.0f);` — `UPROPERTY()` — Up direction
- L86 _protected member_ `FVector SideDirection = FVector(0.0f, 1.0f, 0.0f);` — `UPROPERTY()` — Side direction
- L89 _protected member_ `bool bDrawMesh = true;` — `UPROPERTY()`
- L92 _protected member_ `bool bDrawLine = false;` — `UPROPERTY()`
- L95 _protected member_ `bool bHitMesh = true;` — `UPROPERTY()`
- L98 _protected member_ `bool bHitLine = false;` — `UPROPERTY()`

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/GizmoElementRenderState.h` (Public)


#### struct `FGizmoElementColorAttribute`  
`struct FGizmoElementColorAttribute`  
_L23-52_
- reflection: `USTRUCT()`
- desc: Color state attribute struct Stores color state value, whether state is set and whether it overrides child state.
- L27 _public member_ `static constexpr FLinearColor DefaultColor = FLinearColor(1.0f, 1.0f, 1.0f);`
- L31 _public member_ `FLinearColor Value = DefaultColor;` — `UPROPERTY()` — Color value
- L35 _public member_ `bool bHasValue = false;` — `UPROPERTY()` — True if value has been set.
- L39 _public member_ `bool bOverridesChildState = false;` — `UPROPERTY()` — True if this attribute overrides child state attributes
- L42 _public prototype_ `FLinearColor GetColor() const;` — Return the color value. This returns the default color value if no value has been set.
- L45 _public prototype_ `void SetColor(FLinearColor InColor, bool InOverridesChildState = false);` — Set color value and override flag
- L48 _public prototype_ `void Reset();` — Reset attribute to default values.
- L51 _public prototype_ `void UpdateState(const FGizmoElementColorAttribute& InChildColorAttribute);` — Update this state based on a child state attribute.

#### struct `FGizmoElementMaterialAttribute`  
`struct FGizmoElementMaterialAttribute`  
_L60-86_
- reflection: `USTRUCT()`
- desc: Material state attribute struct Stores material state value, whether state is set and whether it overrides child state.
- L66 _public member_ `TWeakObjectPtr<UMaterialInterface> Value = nullptr;` — `UPROPERTY()` — Material value
- L70 _public member_ `bool bOverridesChildState = false;` — `UPROPERTY()` — True if this attribute overrides child state attributes
- L73 _public prototype_ `const UMaterialInterface* GetMaterial() const;` — Return the material value.
- L76 _public prototype_ `UMaterialInterface* GetMaterial();` — Return the material value.
- L79 _public prototype_ `void SetMaterial(TWeakObjectPtr<UMaterialInterface> InColor, bool InOverridesChildState = false);` — Set material value and override flag
- L82 _public prototype_ `void Reset();` — Reset attribute to default values.
- L85 _public prototype_ `void UpdateState(const FGizmoElementMaterialAttribute& InChildMaterialAttribute);` — Update this state based on a child state attribute.

#### struct `FGizmoElementMeshRenderStateAttributes`  
`struct FGizmoElementMeshRenderStateAttributes`  
_L92-157_
- reflection: `USTRUCT()`
- desc: Mesh render state structure.
- L98 _public member_ `FGizmoElementMaterialAttribute Material;` — `UPROPERTY()` — Default material
- L102 _public member_ `FGizmoElementMaterialAttribute HoverMaterial;` — `UPROPERTY()` — Hover material
- L106 _public member_ `FGizmoElementMaterialAttribute InteractMaterial;` — `UPROPERTY()` — Interact material
- L110 _public member_ `FGizmoElementMaterialAttribute SelectMaterial;` — `UPROPERTY()` — Select material
- L114 _public member_ `FGizmoElementMaterialAttribute SubdueMaterial;` — `UPROPERTY()` — Subdue material
- L118 _public member_ `FGizmoElementColorAttribute VertexColor;` — `UPROPERTY()` — Mesh vertex color
- L122 _public member_ `FGizmoElementColorAttribute HoverVertexColor;` — `UPROPERTY()` — Hover mesh vertex color
- L126 _public member_ `FGizmoElementColorAttribute InteractVertexColor;` — `UPROPERTY()` — Interact mesh vertex color
- L130 _public member_ `FGizmoElementColorAttribute SelectVertexColor;` — `UPROPERTY()` — Select mesh vertex color
- L134 _public member_ `FGizmoElementColorAttribute SubdueVertexColor;` — `UPROPERTY()` — Subdue mesh vertex color
- L137 _public prototype_ `const UMaterialInterface* GetMaterial(EGizmoElementInteractionState InteractionState);` — Returns the material corresponding to the input interaction state
- L140 _public prototype_ `const UMaterialInterface* GetMaterial(EGizmoElementInteractionState InteractionState) const;` — Returns the material corresponding to the input interaction state
- L143 _public prototype_ `FLinearColor GetVertexColor(EGizmoElementInteractionState InteractionState);` — Returns mesh vertex color
- L146 _public prototype_ `FLinearColor GetVertexColor(EGizmoElementInteractionState InteractionState) const;` — Returns mesh vertex color
- L149 _public prototype_ `void Update(FGizmoElementMeshRenderStateAttributes& InChildAttributes);` — Update this mesh render state based on a child mesh render state attribute.
- L153 _private prototype_ `const UMaterialInterface* GetMaterialInternal(EGizmoElementInteractionState InteractionState) const;` — Returns the material corresponding to the input interaction state
- L156 _private prototype_ `FLinearColor GetVertexColorInternal(EGizmoElementInteractionState InteractionState) const;` — Returns mesh vertex color

#### struct `FGizmoElementLineRenderStateAttributes`  
`struct FGizmoElementLineRenderStateAttributes`  
_L163-199_
- reflection: `USTRUCT()`
- desc: Line render state structure.
- L169 _public member_ `FGizmoElementColorAttribute LineColor;` — `UPROPERTY()` — Line color
- L173 _public member_ `FGizmoElementColorAttribute HoverLineColor;` — `UPROPERTY()` — Hover line color
- L177 _public member_ `FGizmoElementColorAttribute InteractLineColor;` — `UPROPERTY()` — Interact line color
- L181 _public member_ `FGizmoElementColorAttribute SelectLineColor;` — `UPROPERTY()` — Select line color
- L185 _public member_ `FGizmoElementColorAttribute SubdueLineColor;` — `UPROPERTY()` — Subdue line color
- L188 _public prototype_ `FLinearColor GetLineColor(EGizmoElementInteractionState InteractionState);` — Returns the line color corresponding to the input interaction state
- L191 _public prototype_ `FLinearColor GetLineColor(EGizmoElementInteractionState InteractionState) const;` — Returns the line color corresponding to the input interaction state
- L194 _public prototype_ `void Update(FGizmoElementLineRenderStateAttributes& InChildAttributes);` — Update this line render state based on a child mesh render state attribute.
- L198 _private prototype_ `FLinearColor GetLineColorInternal(EGizmoElementInteractionState InteractionState) const;` — Returns the line color corresponding to the input interaction state, shared between the public const and non-const versions

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/GizmoElementShapes.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/GizmoElementShared.h` (Public)


#### enum `EGizmoElementState`  
`enum class EGizmoElementState : uint8`  
_L74-80_
- reflection: `UENUM()`
- desc: Visible/hittable state of gizmo element
- L76 _public enumerator_ `None = 0x00`
- L77 _public enumerator_ `Visible = 1<<1`
- L78 _public enumerator_ `Hittable = 1<<2`
- L79 _public enumerator_ `VisibleAndHittable = Visible | Hittable`

#### enum `EGizmoElementInteractionState`  
`enum class EGizmoElementInteractionState`  
_L88-97_
- reflection: `UENUM()`
- desc: Interaction state of gizmo element
- L90 _public enumerator_ `None`
- L91 _public enumerator_ `Hovering`
- L92 _public enumerator_ `Interacting`
- L93 _public enumerator_ `Selected` — When an element is "Selected", it is considered to be the target of Interaction via indirect manipulation (not hit tested).
- L94 _public enumerator_ `Subdued` — When one or more other elements considered part of a set is active, but this one is not (ie. X Axis is Interacting, Y and Z are Subdued).
- L96 _public enumerator_ `Max`

#### enum `EGizmoElementViewDependentType`  
`enum class EGizmoElementViewDependentType`  
_L106-111_
- reflection: `UENUM()`
- desc: View dependent type: automatically cull gizmo element based on view. Axis  - Cull object when angle between axis and view direction is within a given tolerance Plane - Cull object when angle between plane normal and view direction is perpendicular within a given tolerance
- L108 _public enumerator_ `None`
- L109 _public enumerator_ `Axis`
- L110 _public enumerator_ `Plane`

#### enum `EGizmoElementViewAlignType`  
`enum class EGizmoElementViewAlignType`  
_L122-129_
- reflection: `UENUM()`
- desc: View align type: automatically align gizmo element towards a view. PointOnly   - Align object forward axis to view direction only, useful for symmetrical objects such as a circle PointEye    - Align object forward axis to -camera view direction (camera pos - object center), align object up axis to scene view up PointScreen - Align object forward axis to scene view forward direction (view up ^ view right), align object up axis to scene view up Axial		- Rotate object around up axis, minimizing angle between forward axis and view direction
- L124 _public enumerator_ `None`
- L125 _public enumerator_ `PointOnly`
- L126 _public enumerator_ `PointEye`
- L127 _public enumerator_ `PointScreen`
- L128 _public enumerator_ `Axial`

#### enum `EGizmoElementPartialType`  
`enum class EGizmoElementPartialType`  
_L139-144_
- reflection: `UENUM()`
- desc: Partial type: render partial element for those elements which support it. Partial				- Render partial element. PartialViewDependent   - Render partial unless view direction aligns with an axis or normal specified by the element type.
- L141 _public enumerator_ `None`
- L142 _public enumerator_ `Partial`
- L143 _public enumerator_ `PartialViewDependent`

#### enum `EGizmoElementDrawType`  
`enum class EGizmoElementDrawType : uint8`  
_L148-156_
- reflection: `UENUM()`
- desc: Can be used to specify what visuals should be created for a given element, when multiple are available, ie. Fill and Line
- L150 _public enumerator_ `None = 0x00`
- L152 _public enumerator_ `Fill = 1 << 1`
- L153 _public enumerator_ `Line = 1 << 2`
- L155 _public enumerator_ `FillAndLine = Fill | Line`

#### enum `EGizmoElementHitSortType`  
`enum class EGizmoElementHitSortType : uint8`  
_L161-168_
- reflection: `UENUM(Flags)`
- desc: Used to specify the sort criteria when hit testing against multiple elements
- L163 _public enumerator_ `Closest = 1 << 0` — Sort hits by the closest to ray origin (default)
- L164 _public enumerator_ `Priority = 1 << 1` — Sort hits by hit priority (see UGizmoElementBase::HitPriority)
- L165 _public enumerator_ `Surface = 1 << 2` — Sort hits by whether they are surface hits (not proximity hits)
- L167 _public enumerator_ `PriorityThenSurfaceThenClosest = Priority | Surface | Closest` — Sort by all three listed criteria, in order

#### struct `FGizmoPerStateValueDouble`  
`struct FGizmoPerStateValueDouble`  
_L176-239_
- reflection: `USTRUCT(MinimalAPI, meta = (DisplayName = "Per-State Value (Double)"))`
- desc: Used to store per-state (double) values for gizmo elements. ie. line thickness multipliers.
- L180 _public typedef_ `using FValueType = double;`
- L187 _public member_ `TOptional<double> Default;` — `UPROPERTY(EditAnywhere, Category = "Value")` — Default value, used when the Interaction State is "None". Optional to allow explicit un-setting, implying inheritance or some other value source.
- L191 _public member_ `TOptional<double> Hover;` — `UPROPERTY(EditAnywhere, Category = "Value")` — Value used when hovering.
- L195 _public member_ `TOptional<double> Interact;` — `UPROPERTY(EditAnywhere, Category = "Value")` — Value used when interacting.
- L199 _public member_ `TOptional<double> Select;` — `UPROPERTY(EditAnywhere, Category = "Value")` — Value used when selected.
- L203 _public member_ `TOptional<double> Subdue;` — `UPROPERTY(EditAnywhere, Category = "Value")` — Value used when subdued.
- L206 _public prototype_ `double GetValueForState(const EGizmoElementInteractionState InState) const;` — Get the value for the given Interaction State, or Default if not set.
- L209 _public function_ `double GetDefaultValue() const` — Get the Default value if set, otherwise "ValueDefault"
- L212 _public function_ `double GetHoverValue() const` — Get the Hover value, or Default if not set.
- L215 _public function_ `double GetInteractValue() const` — Get the Interact value, or Default if not set.
- L218 _public function_ `double GetSelectValue() const` — Get the Select value, or Default if not set.
- L221 _public function_ `double GetSubdueValue() const` — Get the Subdue value, or Default if not set.
- L238 _private member_ `static constexpr double ValueDefault = 1.0;`

#### struct `FGizmoPerStateValueLinearColor`  
`struct FGizmoPerStateValueLinearColor`  
_L246-306_
- reflection: `USTRUCT(MinimalAPI, meta = (DisplayName = "Per-State Value (LinearColor)"))`
- desc: Used to store per-state (Linear Color) values for gizmo elements. ie. vertex color.
- L250 _public typedef_ `using FValueType = FLinearColor;`
- L257 _public member_ `TOptional<FLinearColor> Default;` — `UPROPERTY(EditAnywhere, Category = "Value")` — Default value, used when the Interaction State is "None". Optional to allow explicit un-setting, implying inheritance or some other value source.
- L261 _public member_ `TOptional<FLinearColor> Hover;` — `UPROPERTY(EditAnywhere, Category = "Value")` — Value used when hovering.
- L265 _public member_ `TOptional<FLinearColor> Interact;` — `UPROPERTY(EditAnywhere, Category = "Value")` — Value used when interacting.
- L269 _public member_ `TOptional<FLinearColor> Select;` — `UPROPERTY(EditAnywhere, Category = "Value")` — Value used when selected.
- L273 _public member_ `TOptional<FLinearColor> Subdue;` — `UPROPERTY(EditAnywhere, Category = "Value")` — Value used when subdued.
- L276 _public prototype_ `const FLinearColor& GetValueForState(const EGizmoElementInteractionState InState) const;` — Get the value for the given Interaction State, or Default if not set.
- L279 _public function_ `const FLinearColor& GetDefaultValue() const` — Get the Default value if set, otherwise FLinearColor::Transparent.
- L282 _public function_ `const FLinearColor& GetHoverValue() const` — Get the Hover value, or Default if not set.
- L285 _public function_ `const FLinearColor& GetInteractValue() const` — Get the Interact value, or Default if not set.
- L288 _public function_ `const FLinearColor& GetSelectValue() const` — Get the Select value, or Default if not set.
- L291 _public function_ `const FLinearColor& GetSubdueValue() const` — Get the Subdue value, or Default if not set.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace InteractiveToolsFramework` (scope `UE`)
- L17 _function_ `template <typename RealType UE_REQUIRES(std::is_floating_point_v<RealType>)> Geometry::TFrame3<RealType> MakePlaneFrame( const Math::TVector<RealType>& InOrigin, const Math::TVector<RealType>& InNormal, const Math::TVector<RealType>& InUp, const Math::TVector<RealType>& InSide)` (scope `UE::InteractiveToolsFramework`) — Construct a FFrame3 for the given plane parameters, to remove axis ambiguity and invalid transforms. Normal = X, Up = Z, Side = Y
- L29 _function_ `template <typename RealType UE_REQUIRES(std::is_floating_point_v<RealType>)> void BreakPlaneFrame( const Geometry::TFrame3<RealType>& InFrame, Math::TVector<RealType>& OutOrigin, Math::TVector<RealType>& OutNormal, Math::TVector<RealType>& OutUp, Math::TVector<RealType>& OutSide)` (scope `UE::InteractiveToolsFramework`) — Decompose a plane frame into its origin, normal, up, and side vectors.
- L45 _function_ `template <typename RealType UE_REQUIRES(std::is_floating_point_v<RealType>)> void BreakPlaneFrame( const Geometry::TFrame3<RealType>& InFrame, Math::TVector<RealType>& OutNormal, Math::TVector<RealType>& OutUp, Math::TVector<RealType>& OutSide)` (scope `UE::InteractiveToolsFramework`) — Decompose a plane frame into its normal, up, and side vectors.
- L57 _function_ `template <typename RealType UE_REQUIRES(std::is_floating_point_v<RealType>)> void BreakPlaneQuaternion( const FQuat& InQuaternion, Math::TVector<RealType>& OutNormal, Math::TVector<RealType>& OutUp, Math::TVector<RealType>& OutSide)` (scope `UE::InteractiveToolsFramework`) — Decompose a plane quaternion into its normal, up, and side vectors.
- L223 _function_ `friend bool operator==(const FGizmoPerStateValueDouble& InLeft, const FGizmoPerStateValueDouble& InRight)`
- L232 _function_ `friend bool operator!=(const FGizmoPerStateValueDouble& InLeft, const FGizmoPerStateValueDouble& InRight)`
- L293 _function_ `friend bool operator==(const FGizmoPerStateValueLinearColor& InLeft, const FGizmoPerStateValueLinearColor& InRight)`
- L302 _function_ `friend bool operator!=(const FGizmoPerStateValueLinearColor& Lhs, const FGizmoPerStateValueLinearColor& RHS)`

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/GizmoElementSphere.h` (Public)


#### class `UGizmoElementSphere`  
`class UGizmoElementSphere : public UGizmoElementBase`  
_L17-53_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UGizmoElementBase`
- L24 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI, const FRenderTraversalState& RenderState) override;`
- L25 _public prototype_ `virtual FInputRayHit LineTrace(const UGizmoViewContext* ViewContext, const FLineTraceTraversalState& LineTraceState, const FVector& RayOrigin, const FVector& RayDirection, FLineTraceOutput& OutLineTraceOutput) override;`
- L29 _public prototype_ `virtual void SetCenter(const FVector& InCenter);` — Location of center of sphere
- L30 _public prototype_ `virtual FVector GetCenter() const;`
- L33 _public prototype_ `virtual void SetRadius(float InRadius);` — Sphere radius.
- L34 _public prototype_ `virtual float GetRadius() const;`
- L37 _public prototype_ `virtual void SetNumSides(int32 InNumSides);` — Number of sides for tessellating sphere.
- L38 _public prototype_ `virtual int32 GetNumSides() const;`
- L44 _protected member_ `FVector Center = FVector::ZeroVector;` — `UPROPERTY()` — Location of center of sphere
- L48 _protected member_ `float Radius = 0.5f;` — `UPROPERTY()` — Sphere radius.
- L52 _protected member_ `int32 NumSides = 32;` — `UPROPERTY()` — Number of sides for tessellating sphere.

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/GizmoElementTorus.h` (Public)


#### class `UGizmoElementTorus`  
`class UGizmoElementTorus : public UGizmoElementCircleBase`  
_L22-91_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UGizmoElementCircleBase`
- desc: Simple object intended to be used as part of 3D Gizmos. Draws a torus based on parameters. Note: the LineTrace method does not perform a true ray-torus intersection! See comment above LineTrace method below for details of how this intersection is approximated.
- L29 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI, const FRenderTraversalState& RenderState) override;`
- L35 _public prototype_ `virtual FInputRayHit LineTrace(const UGizmoViewContext* ViewContext, const FLineTraceTraversalState& LineTraceState, const FVector& RayOrigin, const FVector& RayDirection, FLineTraceOutput& OutLineTraceOutput) override;` — LineTrace approximates ray-torus intersection by intersecting the ray with the plane in which the torus lies, then determining a hit point closest to the linear circle defined by torus center and torus outer radius. If the torus lies at a glancing angle, the ray-torus intersection is performed against cylinders approximating the shape of the torus.
- L39 _public prototype_ `virtual void SetInnerRadius(double InInnerRadius);` — Inner circles radius.
- L40 _public prototype_ `virtual double GetInnerRadius() const;`
- L43 _public prototype_ `virtual void SetHoverInnerRadiusMultiplier(double InHoverInnerRadiusMultiplier);` — Multiplier applied to the inner radius when hovering
- L44 _public prototype_ `virtual double GetHoverInnerRadiusMultiplier() const;`
- L47 _public prototype_ `virtual void SetInteractInnerRadiusMultiplier(double InInteractInnerRadiusMultiplier);` — Multiplier applied to the inner radius when interacting
- L48 _public prototype_ `virtual double GetInteractInnerRadiusMultiplier() const;`
- L51 _public prototype_ `virtual void SetSelectInnerRadiusMultiplier(double InSelectInnerRadiusMultiplier);` — Multiplier applied to the inner radius when selected
- L52 _public prototype_ `virtual double GetSelectInnerRadiusMultiplier() const;`
- L55 _public prototype_ `virtual void SetSubdueInnerRadiusMultiplier(double InSubdueInnerRadiusMultiplier);` — Multiplier applied to the inner radius when subdued
- L56 _public prototype_ `virtual double GetSubdueInnerRadiusMultiplier() const;`
- L59 _public prototype_ `virtual void SetNumInnerSlices(int32 InNumInnerSlices);` — Number of inner slices for rendering torus.
- L60 _public prototype_ `virtual int32 GetNumInnerSlices() const;`
- L63 _public prototype_ `virtual void SetEndCaps(bool InEndCaps);` — If partial, renders end caps when true.
- L64 _public prototype_ `virtual bool GetEndCaps() const;`
- L70 _protected member_ `double InnerRadius = 5.0;` — `UPROPERTY()` — Torus inner radius.
- L74 _protected member_ `FGizmoPerStateValueDouble InnerRadiusMultiplier;` — `UPROPERTY()` — Optional inner radius multipliers to apply when hovering, interacting, selected or subdued.
- L78 _protected member_ `int32 NumInnerSlices = 8;` — `UPROPERTY()` — Number of slices to render in each torus segment.
- L82 _protected member_ `bool bEndCaps = false;` — `UPROPERTY()` — Whether to render end caps on a partial torus.
- L87 _protected prototype_ `double GetCurrentInnerRadius() const;` — Returns the current inner radius based on the current interaction state.
- L89 _protected prototype_ `bool IsGlancingAngle(const UGizmoViewContext* View, const FVector& InWorldCenter, const FVector& InWorldNormal);`

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/GizmoElementTriangleList.h` (Public)


#### class `UGizmoElementTriangleList`  
`class UGizmoElementTriangleList : public UGizmoElementBase`  
_L17-67_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UGizmoElementBase`
- L24 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI, const FRenderTraversalState& RenderState) override;`
- L25 _public prototype_ `virtual FInputRayHit LineTrace(const UGizmoViewContext* ViewContext, const FLineTraceTraversalState& LineTraceState, const FVector& RayOrigin, const FVector& RayDirection, FLineTraceOutput& OutLineTraceOutput) override;`
- L29 _public prototype_ `virtual void SetVertices(const TArrayView<const FVector>& InVertices);` — The vertices of the triangle list, each tuple of 3 forming a triangle
- L30 _public prototype_ `virtual const TArray<FVector>& GetVertices() const;`
- L33 _public prototype_ `virtual void SetBase(FVector InBase);` — Base location the triangles
- L34 _public prototype_ `virtual FVector GetBase() const;`
- L37 _public prototype_ `virtual void SetUpDirection(const FVector& InUpDirection);` — Up direction
- L38 _public prototype_ `virtual FVector GetUpDirection() const;`
- L41 _public prototype_ `virtual void SetSideDirection(const FVector& InSideDirection);` — Side direction
- L42 _public prototype_ `virtual FVector GetSideDirection() const;`
- L46 _protected prototype_ `void ComputeProjectedVertices(const FTransform& InLocalToWorldTransform, bool bIncludeBase);`
- L48 _protected prototype_ `static bool Intersect(const FRay& Ray, const FVector& A, const FVector& B, const FVector& C, double Tolerance, double& Distance);`
- L52 _protected member_ `TArray<FVector> Vertices;` — `UPROPERTY()` — The vertices of the triangle list, each tuple of 3 forming a triangle
- L56 _protected member_ `FVector Base = FVector::ZeroVector;` — `UPROPERTY()` — Base location the triangles
- L60 _protected member_ `FVector UpDirection = FVector(0.0f, 0.0f, 1.0f);` — `UPROPERTY()` — Up direction
- L64 _protected member_ `FVector SideDirection = FVector(0.0f, 1.0f, 0.0f);` — `UPROPERTY()` — Side direction
- L66 _protected member_ `TArray<FVector> ProjectedVertices;`

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/GizmoInterfaces.h` (Public)


#### class `UGizmoTransformSource`  
`class UGizmoTransformSource : public UInterface`  
_L34-37_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IGizmoTransformSource`  
`class IGizmoTransformSource`  
_L41-50_
- desc: IGizmoTransformSource is an interface which is used to Get/Set an FTransform.
- L46 _public prototype_ `virtual FTransform GetTransform() const = 0;` — `UFUNCTION()`
- L49 _public prototype_ `virtual void SetTransform(const FTransform& NewTransform) = 0;` — `UFUNCTION()`

#### class `UGizmoAxisSource`  
`class UGizmoAxisSource : public UInterface`  
_L57-60_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IGizmoAxisSource`  
`class IGizmoAxisSource`  
_L68-97_
- desc: IGizmoAxisSource is an interface which is used to get information about a 3D Axis. At minimum this includes a 3D Direction Vector and Origin Point. Optionally the implementation may provide two Tangent Vectors which are assumed to be mutually-orthogonal and perpendicular to the Axis Direction (ie that's the normal and the 3 vectors form a coordinate frame).
- L74 _public prototype_ `virtual FVector GetOrigin() const = 0;` — `UFUNCTION()` — @return Origin Point of axis
- L78 _public prototype_ `virtual FVector GetDirection() const = 0;` — `UFUNCTION()` — @return Direction Vector of axis
- L82 _public function_ `virtual bool HasTangentVectors() const` — `UFUNCTION()` — @return true if this AxisSource has tangent vectors orthogonal to the Direction vector
- L88 _public function_ `virtual void GetTangentVectors(FVector& TangentXOut, FVector& TangentYOut) const` — `UFUNCTION()` — Get the two tangent vectors that are orthogonal to the Direction vector. @warning Only valid if HasTangentVectors() returns true
- L95 _public prototype_ `void GetAxisFrame( FVector& PlaneNormalOut, FVector& PlaneAxis1Out, FVector& PlaneAxis2Out) const;` — Utility function that always returns a 3D coordinate system (ie plane normal and perpendicular axes). Internally calls GetTangentVectors() if available, otherwise constructs arbitrary mutually perpendicular vectors.

#### class `UGizmoClickTarget`  
`class UGizmoClickTarget : public UInterface`  
_L105-108_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IGizmoClickTarget`  
`class IGizmoClickTarget`  
_L112-155_
- desc: IGizmoClickTarget is an interface used to provide a ray-object hit test.
- L120 _public prototype_ `virtual FInputRayHit IsHit(const FInputDeviceRay& ClickPos) const = 0;` — `UFUNCTION()` — @return FInputRayHit indicating whether or not the target object was hit by the device-ray at ClickPos
- L127 _public prototype_ `virtual void UpdateHoverState(bool bHovering) = 0;` — `UFUNCTION()` — Updates the hover state indicating whether the input device is currently hovering over the Standard gizmo. This should be be set to false once interaction with the gizmo commences.
- L134 _public prototype_ `virtual void UpdateInteractingState(bool bInteracting) = 0;` — `UFUNCTION()` — Updates the interacting state indicating when interaction with the Standard gizmo is actively occurring, typically upon the input device clicking and dragging the Standard gizmo.
- L141 _public prototype_ `virtual void UpdateSelectedState(bool bSelected) = 0;` — `UFUNCTION()` — Updates the selected state, indicating when the gizmo is currently selected, typically upon the input device clicking the Standard gizmo.
- L148 _public prototype_ `virtual void UpdateSubdueState(bool bSubdued) = 0;` — `UFUNCTION()` — Updates the subdued state, indicating when the element should have a subdued/background appearance, typically upon interacting with one of a set of gizmos representing 3 axis - the two not interacted with would be subdued.
- L151 _public function_ `virtual void SetTransformAdjuster(const TSharedPtr<UE::GizmoRenderingUtil::IViewBasedTransformAdjuster>& InAdjuster)` — Sets the optional transform adjuster to apply to the tested geometry.
- L154 _public function_ `virtual TSharedPtr<UE::GizmoRenderingUtil::IViewBasedTransformAdjuster> GetTransformAdjuster() const` — Get the (optional) transform adjuster applied to this Target.

#### class `UGizmoClickMultiTarget`  
`class UGizmoClickMultiTarget : public UInterface`  
_L158-161_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IGizmoClickMultiTarget`  
`class IGizmoClickMultiTarget`  
_L171-221_
- desc: IGizmoClickMultiTarget is an interface used to provide a ray-object hit test against a target which supports hitting parts of the target. For a gizmo with multiple parts, the part identifier establishes a correspondence between a gizmo part and the elements representing that part within the hit target. The valid part identifiers should be defined in the gizmo. Identifier 0 is reserved for the default ID which should be assigned to elements that do not correspond to any gizmo part, such as non-hittable decorative elements.
- L180 _public prototype_ `virtual FInputRayHit IsHit(const FInputDeviceRay& ClickPos) const = 0;` — `UFUNCTION()` — @return FInputRayHit indicating whether or not the target object was hit by the device-ray at ClickPos The ray hit contains client-defined ID, HitOwner and HitObject which are used to identify the hit part.
- L187 _public prototype_ `virtual void UpdateHoverState(bool bHovering, uint32 InPartIdentifier) = 0;` — `UFUNCTION()` — Updates the hover state of the specified gizmo part, indicating whether the input device is currently hovering over the Standard gizmo.
- L194 _public prototype_ `virtual void UpdateInteractingState(bool bInteracting, uint32 InPartIdentifier) = 0;` — `UFUNCTION()` — Updates the interacting state of the specified gizmo part, indicating when interaction with the Standard gizmo is actively occurring, typically upon the input device clicking and dragging the Standard gizmo.
- L201 _public prototype_ `virtual void UpdateSelectedState(bool bSelected, uint32 InPartIdentifier) = 0;` — `UFUNCTION()` — Updates the selected state of the specified gizmo part, indicating when the gizmo part is currently selected, typically upon the input device clicking the Standard gizmo.
- L208 _public prototype_ `virtual void UpdateSubdueState(bool bSubdued, uint32 InPartIdentifier) = 0;` — `UFUNCTION()` — Updates the subdued state of the specified gizmo part, indicating when the element should have a subdued/background appearance, typically upon interacting with one of a set of gizmos representing 3 axis - the two not interacted with would be subdued.
- L214 _public prototype_ `virtual void UpdateHittableState(bool bHittable, uint32 InPartIdentifier) = 0;` — `UFUNCTION()` — Updates the hittable state of the specified gizmo part.
- L217 _public function_ `virtual void SetTransformAdjuster(const TSharedPtr<UE::GizmoRenderingUtil::IViewBasedTransformAdjuster>& InAdjuster)` — Sets the optional transform adjuster to apply to the tested geometry.
- L220 _public function_ `virtual TSharedPtr<UE::GizmoRenderingUtil::IViewBasedTransformAdjuster> GetTransformAdjuster() const` — Get the (optional) transform adjuster applied to this Target.

#### class `UGizmoRenderTarget`  
`class UGizmoRenderTarget : public UInterface`  
_L227-230_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IGizmoRenderTarget`  
`class IGizmoRenderTarget`  
_L235-243_
- desc: UGizmoRenderTarget is an interface used to provide rendering of a target
- L242 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) const = 0;` — Renders the target using the current tools context.

#### class `UGizmoRenderMultiTarget`  
`class UGizmoRenderMultiTarget : public UInterface`  
_L249-252_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IGizmoRenderMultiTarget`  
`class IGizmoRenderMultiTarget`  
_L263-277_
- desc: IGizmoRenderMultiTarget is an interface used to provide rendering of a target and the ability to specify which part of a target should be visible. For a gizmo with multiple parts, the part identifier establishes a correspondence between a gizmo part and the elements representing that part within the hit target. The valid part identifiers should be defined in the gizmo. Identifier 0 is reserved for the default ID which should be assigned to elements that do not correspond to any gizmo part, such as non-hittable decorative elements.
- L270 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) const = 0;` — Renders the target using the current tools context.
- L276 _public prototype_ `virtual void UpdateVisibilityState(bool bVisible, uint32 InPartIdentifier) = 0;` — `UFUNCTION()` — Updates the visibility state of the specified gizmo part.

#### class `UGizmoStateTarget`  
`class UGizmoStateTarget : public UInterface`  
_L281-284_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IGizmoStateTarget`  
`class IGizmoStateTarget`  
_L288-309_
- desc: IGizmoStateTarget is an interface that is used to pass notifications about significant gizmo state updates
- L296 _public prototype_ `virtual void BeginUpdate() = 0;` — `UFUNCTION()` — BeginUpdate is called before a standard Gizmo begins changing a parameter (via a ParameterSource)
- L302 _public prototype_ `virtual void EndUpdate() = 0;` — `UFUNCTION()` — EndUpdate is called when a standard Gizmo is finished changing a parameter (via a ParameterSource)
- L308 _public prototype_ `virtual void CancelUpdate() = 0;` — `UFUNCTION()` — CancelUpdate is called when a gizmo cancels and reverts the changes to a parameter (via a ParameterSource)

#### class `UGizmoFloatParameterSource`  
`class UGizmoFloatParameterSource : public UInterface`  
_L316-319_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IGizmoFloatParameterSource`  
`class IGizmoFloatParameterSource`  
_L323-343_
- desc: IGizmoFloatParameterSource provides Get and Set for an arbitrary float-valued parameter.
- L330 _public prototype_ `virtual float GetParameter() const = 0;` — `UFUNCTION()` — @return value of parameter
- L334 _public prototype_ `virtual void BeginModify() = 0;` — `UFUNCTION()` — notify ParameterSource that a parameter modification is about to begin
- L338 _public prototype_ `virtual void SetParameter(float NewValue) = 0;` — `UFUNCTION()` — set value of parameter
- L342 _public prototype_ `virtual void EndModify() = 0;` — `UFUNCTION()` — notify ParameterSource that a parameter modification is complete

#### class `UGizmoVec2ParameterSource`  
`class UGizmoVec2ParameterSource : public UInterface`  
_L349-352_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IGizmoVec2ParameterSource`  
`class IGizmoVec2ParameterSource`  
_L356-376_
- desc: IGizmoVec2ParameterSource provides Get and Set for an arbitrary 2D-vector-valued parameter.
- L363 _public prototype_ `virtual FVector2D GetParameter() const = 0;` — `UFUNCTION()` — @return value of parameter
- L367 _public prototype_ `virtual void BeginModify() = 0;` — `UFUNCTION()` — notify ParameterSource that a parameter modification is about to begin
- L371 _public prototype_ `virtual void SetParameter(const FVector2D& NewValue) = 0;` — `UFUNCTION()` — set value of parameter
- L375 _public prototype_ `virtual void EndModify() = 0;` — `UFUNCTION()` — notify ParameterSource that a parameter modification is complete

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace GizmoRenderingUtil` (scope `UE`)

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/GizmoLineHandleComponent.h` (Public)


#### class `UGizmoLineHandleComponent`  
`class UGizmoLineHandleComponent : public UGizmoBaseComponent`  
_L16-47_
- reflection: `UCLASS(ClassGroup = Utility, HideCategories = (Physics, Collision, Lighting, Rendering, Mobile), MinimalAPI)`
- inherits: `UGizmoBaseComponent`
- desc: Simple Component intended to be used as part of 3D Gizmos. Draws line terminated by a short perpendicular handle line based on parameters.
- L22 _public member_ `FVector Normal = FVector(0, 0, 1);` — `UPROPERTY(EditAnywhere, Category = Options)`
- L25 _public member_ `float HandleSize = 10.0f;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L28 _public member_ `float Thickness = 2.0f;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L31 _public member_ `FVector Direction = FVector(0, 0, 1.);` — `UPROPERTY(EditAnywhere, Category = Options)`
- L34 _public member_ `float Length;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L37 _public member_ `bool bImageScale = true;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L40 _private prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L41 _private prototype_ `virtual bool LineTraceComponent(FHitResult& OutHit, const FVector Start, const FVector End, const FCollisionQueryParams& Params) override;`
- L45 _private prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/GizmoMath.h` (Public)


#### struct `GizmoMath::FDashLineSettings`  
`struct FDashLineSettings`  
_L171-220_
- desc: Helper struct used to pass parameters to the BuildDashedLine method. Also defines unique behavior for building dashes, which differs between world and screen-space.
- L174 _public member_ `double TotalLength = 0.0;` — Total length of the line.
- L177 _public member_ `double ScaledLength;` — Scaled Line length, e.g. matching pixel to world scale
- L180 _public member_ `TFunction<double(const double& InParam)> ParamToWorldFunction;` — Converts the given parameter along the length (0-1) to a world fraction.
- L183 _public member_ `TFunction<double(const double& InParam)> ParamToRadiusScaleFunction;` — Returns the radius scale at the given param (0-1)
- L186 _public member_ `float DashLength = 10.0f;` — Dashes length
- L189 _public member_ `float DashGapLength = 5.0f;` — Length of gaps between dashes
- L192 _public member_ `FVector ScreenStartPoint;` — Start point of the line
- L195 _public member_ `FVector ScreenEndPoint;` — End point of the line
- L198 _public member_ `int32 NumSides = 32;` — Resolution of the cylinder used to render the line - 3 or more vertices required
- L201 _public member_ `int32 MaxNumDashes = 512;` — Arbitrary maximum to prevent overflow in the case of very long cylinders
- L204 _public member_ `double LineFractionInView = 1.0;` — Reflects the fraction of the line (in world space) that's visible - e.g. 0.5 means half of the line is visible
- L207 _public member_ `double WorldStartFraction = 0.0;` — World-space fraction offset - non-zero only when the line origin is clamped
- L210 _public member_ `float Radius = 1.0f;` — Radius of the line
- L213 _public member_ `FColor Color;` — Color of the line
- L216 _public member_ `FMatrix RenderLocalToWorldMatrix;` — The local to world matrix which will be applied to the line geometry vertices
- L219 _public member_ `const UMaterialInterface* MaterialInterface;` — The material interface used by the line

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace GizmoMath`
- L23 _prototype_ `FVector ProjectPointOntoLine( const FVector& Point, const FVector& LineOrigin, const FVector& LineDirection);` (scope `GizmoMath`) — Project a point onto the line defined by LineOrigin and LineDirection @return projected point
- L31 _prototype_ `void NearestPointOnLine( const FVector& LineOrigin, const FVector& LineDirection, const FVector& QueryPoint, FVector& NearestPointOut, float& LineParameterOut);` (scope `GizmoMath`) — Find the nearest point to QueryPoint on the line defined by LineOrigin and LineDirection. Returns this point and the associated line-equation parameter
- L40 _prototype_ `void NearestPointOnLineToRay( const FVector& LineOrigin, const FVector& LineDirection, const FVector& RayOrigin, const FVector& RayDirection, FVector& NearestLinePointOut, float& LineParameterOut, FVector& NearestRayPointOut, float& RayParameterOut);` (scope `GizmoMath`) — Find the closest pair of points on a 3D line and 3D ray. Returns the points and line-equation parameters on both the line and ray.
- L51 _prototype_ `void RayPlaneIntersectionPoint( const FVector& PlaneOrigin, const FVector& PlaneNormal, const FVector& RayOrigin, const FVector& RayDirection, bool& bIntersectsOut, FVector& PlaneIntersectionPointOut);` (scope `GizmoMath`) — Find the intersection of the ray defined by RayOrigin and RayDirection with the plane defined by PlaneOrigin and PlaneNormal. Returns intersection success/failure in bIntersectsOut and the intersection point in PlaneIntersectionPointOut
- L61 _prototype_ `void RaySphereIntersection( const FVector& SphereOrigin, const float SphereRadius, const FVector& RayOrigin, const FVector& RayDirection, bool& bIntersectsOut, FVector& SphereIntersectionPointOut);` (scope `GizmoMath`) — Find the intersection of the ray defined by RayOrigin and RayDirection with the sphere defined by SphereOrigin and SphereRadius. Returns intersection success/failure in bIntersectsOut and the intersection point in SphereIntersectionPointOut
- L73 _prototype_ `template<typename RealType> void RayCylinderIntersection( const FVector& CylinderCenter, const FVector& CylinderAxis, RealType CylinderRadius, RealType CylinderHeight, const FVector& RayOrigin, const FVector& RayDirection, bool& bIntersectsOut, RealType& OutHitDepth);` (scope `GizmoMath`) — Find the intersection of the ray defined by RayOrigin and RayDirection with the cylinder defined by CylinderCenter, CylinderAxis, CylinderRadius, and CylinderHeight. Returns intersection success/failure in bOutIntersects and the hit depth parameter along the ray for the first intersection in OutHitDepth.
- L88 _prototype_ `template <typename RealType> void RayConeIntersection( const FVector& ConeCenter, const FVector& ConeDirection, RealType ConeCosAngle, RealType ConeHeight, const FVector& RayOrigin, const FVector& RayDirection, bool& bIntersectsOut, RealType& OutHitDepth);` (scope `GizmoMath`) — Find the intersection of the ray defined by RayOrigin and RayDirection with the cone defined by ConeCenter, ConeDirection, ConeCosAngle, and ConeHeight. Where ConeCosAngle is the cosine of the cone opening angle, defined as the angle at the apex between the cone's axis and slant edge. Returns intersection success/failure in bOutIntersects and the hit depth parameter along the ray for the first intersection in OutHitDepth.
- L100 _prototype_ `template <typename RealType> void IntervalIntervalIntersection( const RealType Interval0[2], const RealType Interval1[2], int& OutNumIntersections, RealType& OutResult0, RealType& OutResult1);` (scope `GizmoMath`) — Find the intersection of two floating point intervals in which the interval inputs contain pairs of floats sorted in increasing order. Returns the number of intersections intersection and intersection results in increasing order.
- L108 _prototype_ `void ClosetPointOnCircle( const FVector& QueryPoint, const FVector& CircleOrigin, const FVector& CircleNormal, float CircleRadius, FVector& ClosestPointOut);` (scope `GizmoMath`) — Find the closest point to QueryPoint that is on the circle defined by CircleOrigin, CircleNormal, and CircleRadius.
- L117 _prototype_ `void MakeNormalPlaneBasis( const FVector& PlaneNormal, FVector& BasisAxis1Out, FVector& BasisAxis2Out);` (scope `GizmoMath`) — Construct two mutually-perpendicular unit vectors BasisAxis1Out and BasisAxis2Out which are orthogonal to PlaneNormal
- L127 _prototype_ `float ComputeAngleInPlane( const FVector& Point, const FVector& PlaneOrigin, const FVector& PlaneNormal, const FVector& PlaneAxis1, const FVector& PlaneAxis2);` (scope `GizmoMath`) — Project the input Point into the plane defined by PlaneOrigin and PlaneNormal, and then measure it's signed angle relative to the in-plane X and Y axes defined by PlaneAxis1 and PlaneAxis2 @return the signed angle
- L139 _prototype_ `FVector2D ComputeCoordinatesInPlane( const FVector& Point, const FVector& PlaneOrigin, const FVector& PlaneNormal, const FVector& PlaneAxis1, const FVector& PlaneAxis2);` (scope `GizmoMath`) — Project the input Point into the plane defined by PlaneOrigin and PlaneNormal, and then calculate it's UV coordinates in the space defined by the plane axes PlaneAxis1 and PlaneAxis2 @return the UV coordinates
- L148 _prototype_ `FVector ProjectPointOntoPlane( const FVector& Point, const FVector& PlaneOrigin, const FVector& PlaneNormal);` (scope `GizmoMath`) — Project the input Point onto the plane defined by PlaneOrigin and PlaneNormal, @return Nearest position to Point lying in the plane
- L158 _prototype_ `template <typename RealType> RealType SnapToIncrement(RealType Value, RealType Increment);` (scope `GizmoMath`) — Round Value to nearest step of Increment @return snapped/rounded value
- L165 _prototype_ `FVector GetOrthogonalVector(const FVector& V);` (scope `GizmoMath`) — @todo change FVector to a templated vector type specialized by RealType (double or float) Compute vector orthogonal to V. @return Orthogonal vector
- L230 _prototype_ `void GetScreenSpaceLineStartEnd( const FSceneView* InSceneView, const FVector& InLineOrigin, const FVector& InLineDirection, const double& InLineLength, FVector& OutScreenStartPoint, FVector& OutScreenEndPoint, double& OutClampedWorldFraction, double& OutClampedWorldStartFraction );` (scope `GizmoMath`) — Get the screen-space start and end for the given line (from origin, direction, length). Z is depth from view, XY are in pixel space. OutClampedWorldFraction is used when one or more of the end points is beyond the view bounds, and reflects the fraction of the line (in world space) that's visible, ie. if only 50% of the line is within the viewport, this will return 0.5. OutClampedWorldStartFraction reflects the world-space offset from the line origin to the visible segment start - non-zero when the origin end of the line is clipped (e.g. camera-follow mode where the origin leaves the viewport).
- L241 _prototype_ `double GetPixelToWorldScaleAtScreenFraction( const double& InStartDepthInView, const double& InEndDepthInView, double InScreenFraction );` (scope `GizmoMath`)
- L245 _prototype_ `void BuildDashedLine(FPrimitiveDrawInterface* InPDI, const FDashLineSettings& InDashSettings);` (scope `GizmoMath`)

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/GizmoRectangleComponent.h` (Public)


#### class `UGizmoRectangleComponent`  
`class UGizmoRectangleComponent : public UGizmoBaseComponent`  
_L15-61_
- reflection: `UCLASS(ClassGroup = Utility, HideCategories = (Physics, Collision, Lighting, Rendering, Mobile), MinimalAPI)`
- inherits: `UGizmoBaseComponent`
- desc: Simple Component intended to be used as part of 3D Gizmos. Draws outline of 3D rectangle based on parameters.
- L21 _public member_ `FVector DirectionX = FVector(0, 0, 1);` — `UPROPERTY(EditAnywhere, Category = Options)`
- L24 _public member_ `FVector DirectionY = FVector(0, 1, 0);` — `UPROPERTY(EditAnywhere, Category = Options)`
- L31 _public member_ `bool bOrientYAccordingToCamera = false;` — `UPROPERTY(EditAnywhere, Category = Options)` — When true, instead of using the provided DirectionY, the component will use a direction orthogonal to the camera direction and DirectionX. This keeps the rectangle pinned along DirectionX but spun to be flatter relative the camera.
- L34 _public member_ `float OffsetX = 0.0f;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L37 _public member_ `float OffsetY = 0.0f;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L40 _public member_ `float LengthX = 20.0f;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L43 _public member_ `float LengthY = 20.0f;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L46 _public member_ `float Thickness = 2.0f;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L49 _public member_ `uint8 SegmentFlags = 0x1 | 0x2 | 0x4 | 0x8;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L53 _private prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L54 _private prototype_ `virtual bool LineTraceComponent(FHitResult& OutHit, const FVector Start, const FVector End, const FCollisionQueryParams& Params) override;`
- L55 _private prototype_ `virtual void GetUsedMaterials(TArray<UMaterialInterface*>& OutMaterials, bool bGetDebugMaterials = false) const override;`
- L59 _private prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/GizmoRenderingUtil.h` (Public)


#### class `UE::GizmoRenderingUtil::ISceneViewInterface`  
`class ISceneViewInterface`  
_L24-37_
- desc: Interface meant to wrap either an FSceneView or UGizmoViewContext so that a user can write one function to handle either one (for rendering and for hit testing).
- L27 _public prototype_ `virtual const FIntRect& GetUnscaledViewRect() const = 0;`
- L28 _public prototype_ `virtual FVector4 WorldToScreen(const FVector&) const = 0;`
- L29 _public prototype_ `virtual FVector GetViewLocation() const = 0;`
- L30 _public prototype_ `virtual FVector GetViewDirection() const = 0;`
- L31 _public prototype_ `virtual FVector GetViewRight() const = 0;`
- L32 _public prototype_ `virtual FVector GetViewUp() const = 0;`
- L33 _public prototype_ `virtual const FMatrix& GetProjectionMatrix() const = 0;`
- L34 _public prototype_ `virtual const FMatrix& GetViewMatrix() const = 0;`
- L35 _public prototype_ `virtual bool IsPerspectiveProjection() const = 0;`
- L36 _public prototype_ `virtual double GetDPIScale() const = 0;`

#### class `UE::GizmoRenderingUtil::FSceneViewWrapper`  
`class FSceneViewWrapper : public ISceneViewInterface`  
_L40-61_
- inherits: `ISceneViewInterface`
- desc: Wrapper around FSceneView to access it through ISceneViewInterface
- L43 _public function_ `explicit FSceneViewWrapper(const FSceneView& SceneView)`
- L48 _public function_ `virtual const FIntRect& GetUnscaledViewRect() const`
- L49 _public function_ `virtual FVector4 WorldToScreen(const FVector& VectorIn) const`
- L50 _public function_ `virtual FVector GetViewLocation() const`
- L51 _public function_ `virtual FVector GetViewDirection() const`
- L52 _public function_ `virtual FVector GetViewRight() const`
- L53 _public function_ `virtual FVector GetViewUp() const`
- L54 _public function_ `virtual const FMatrix& GetProjectionMatrix() const`
- L55 _public function_ `virtual const FMatrix& GetViewMatrix() const`
- L56 _public function_ `virtual bool IsPerspectiveProjection() const`
- L57 _public function_ `virtual double GetDPIScale() const`
- L60 _private member_ `const FSceneView* View;`

#### struct `UE::GizmoRenderingUtil::FDefaultGizmoMaterialExtraParams`  
`struct FDefaultGizmoMaterialExtraParams`  
_L78-81_
- L80 _public member_ `bool bDimOccluded = true;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace GizmoRenderingUtil` (scope `UE`)
- L65 _variable_ `const int32 GIZMO_TRANSLUCENCY_SORT_PRIORITY = 5000;` (scope `UE::GizmoRenderingUtil`) — Can be used as TranslucencySortPriority to make gizmo elements show up above other translucent objects
- L76 _prototype_ `UMaterialInterface* GetDefaultGizmoComponentMaterial(const FLinearColor& Color, UObject* Outer = nullptr);` (scope `UE::GizmoRenderingUtil`) — Gets a custom material suitable to use for gizmo components. The material is drawn on top of opaque geometry with dithering for portions behind opaque materials, but uses the custom depth buffer to properly occlude itself. Components using this material should set bRenderCustomDepth to true so they can occlude other gizmo elements. It is also suggested that TranslucencySortPriority be set to something like UE::GizmoRenderingUtil::GIZMO_TRANSLUCENCY_SORT_PRIORITY so that the component is drawn on top of other translucent materials. @param Outer Object to set as outer for the material instance. Typically can be left as nullptr to use transient package.
- L85 _prototype_ `UMaterialInterface* GetDefaultGizmoComponentMaterial(const FLinearColor& Color, const FDefaultGizmoMaterialExtraParams& Params, UObject* Outer = nullptr);` (scope `UE::GizmoRenderingUtil`) — Like the other overload, but with additional parameters.
- L92 _prototype_ `UViewAdjustedStaticMeshGizmoComponent* CreateDefaultMaterialGizmoMeshComponent( UStaticMesh* Mesh, UGizmoViewContext* GizmoViewContext, UObject* OwnerComponentOrActor, const FLinearColor& Color, bool bAddHoverMaterial = true);` (scope `UE::GizmoRenderingUtil`) — Helper that creates a component with the default gizmo material and sets up the component-side properties that are needed for it to properly work (translucency sort priority, etc). This may not be necessary if your component is using some other gizmo material that doesn't require component-side flags.
- L99 _prototype_ `UViewAdjustedStaticMeshGizmoComponent* CreateDefaultMaterialGizmoMeshComponent( UStaticMesh* Mesh, UInteractiveGizmoManager* GizmoManager, UObject* OwnerComponentOrActor, const FLinearColor& Color, bool bAddHoverMaterial = true);` (scope `UE::GizmoRenderingUtil`) — Overload that takes a gizmo manager to get the view context from that.
- L106 _prototype_ `FLinearColor GetDefaultAxisColor(EAxis::Type Axis);` (scope `UE::GizmoRenderingUtil`) — Gets a red/green/blue color based on the axis (X, Y, or Z).
- L112 _prototype_ `float CalculateLocalPixelToWorldScale( const FSceneView* View, const FVector& Location, const double InDPIScale = 1.0);` (scope `UE::GizmoRenderingUtil`) — @return Conversion factor between pixel and world-space coordinates at 3D point Location in View. @warning This is a local estimate and is increasingly incorrect as the 3D point gets further from Location
- L119 _prototype_ `template <typename RealType = float> RealType CalculateLocalPixelToWorldScale( const UE::GizmoRenderingUtil::ISceneViewInterface* View, const FVector& Location, const bool bInWithDPIScale = false, const TOptional<double>& InDPIScale = TOptional<double>());` (scope `UE::GizmoRenderingUtil`) — @note: if bInWithDPIScale is true, we use ISceneViewInterface::DPIScale or the provided InDPIScale when set.
- L125 _prototype_ `extern template float CalculateLocalPixelToWorldScale<float>(const UE::GizmoRenderingUtil::ISceneViewInterface*, const FVector&, bool, const TOptional<double>&);` (scope `UE::GizmoRenderingUtil`)
- L127 _prototype_ `extern template double CalculateLocalPixelToWorldScale<double>(const UE::GizmoRenderingUtil::ISceneViewInterface*, const FVector&, bool, const TOptional<double>&);` (scope `UE::GizmoRenderingUtil`)
- L135 _prototype_ `template <typename RealType = float> RealType CalculateViewDependentScaleAndFlatten( const UE::GizmoRenderingUtil::ISceneViewInterface* View, const FVector& Location, const RealType Scale, FVector& OutWorldFlattenScale);` (scope `UE::GizmoRenderingUtil`) — @return Legacy view dependent conversion factor. @return OutWorldFlattenScale vector to be applied in world space, can be used to flatten excluded dimension in orthographic views as it reverses the scale in that dimension.
- L141 _prototype_ `extern template float CalculateViewDependentScaleAndFlatten<float>(const UE::GizmoRenderingUtil::ISceneViewInterface*, const FVector&, float, FVector&);` (scope `UE::GizmoRenderingUtil`)
- L143 _prototype_ `extern template double CalculateViewDependentScaleAndFlatten<double>(const UE::GizmoRenderingUtil::ISceneViewInterface*, const FVector&, double, FVector&);` (scope `UE::GizmoRenderingUtil`)
- L145 _prototype_ `float CalculateViewDependentScaleAndFlatten( const FSceneView* View, const FVector& Location, const float Scale, FVector& OutWorldFlattenScale);` (scope `UE::GizmoRenderingUtil`)
- L153 _namespace_ `namespace GizmoRenderingUtil`
- L156 _prototype_ `float CalculateLocalPixelToWorldScale( const FSceneView* View, const FVector& Location);` (scope `GizmoRenderingUtil`) — `UE_DEPRECATED(5.5, "This function was moved to the UE::GizmoRenderingUtil namespace.")`
- L161 _prototype_ `float CalculateLocalPixelToWorldScale( const UGizmoViewContext* ViewContext, const FVector& Location);` (scope `GizmoRenderingUtil`) — `UE_DEPRECATED(5.5, "This function was moved to the UE::GizmoRenderingUtil namespace.")`
- L166 _prototype_ `float CalculateViewDependentScaleAndFlatten( const FSceneView* View, const FVector& Location, const float Scale, FVector& OutWorldFlattenScale);` (scope `GizmoRenderingUtil`) — `UE_DEPRECATED(5.5, "This function was moved to the UE::GizmoRenderingUtil namespace.")`

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/GizmoUtil.h` (Public)


#### class `FGizmoElementAccessor`  
`class FGizmoElementAccessor`  
_L18-41_
- desc: A utility class to access GizmoElements that aren't otherwise publicly exposed. Use responsibly.
- L21 _public prototype_ `static TConstArrayView<TObjectPtr<UGizmoElementBase>> GetSubElements(const UGizmoElementBase& InGizmoElement);`
- L22 _public prototype_ `static void GetSubElementsRecursive(const UGizmoElementBase& InGizmoElement, TArray<TObjectPtr<UGizmoElementBase>>& OutElements);`
- L23 _public prototype_ `static bool GetSubElementsRecursive(const UGizmoElementBase& InGizmoElement, TArray<TObjectPtr<UGizmoElementBase>>& OutElements, const uint32 InPartId);`
- L26 _public prototype_ `bool UpdateRenderState(UGizmoElementBase& InGizmoElement, IToolsContextRenderAPI* InRenderAPI, const FVector& InLocalCenter, UGizmoElementBase::FRenderTraversalState& InOutRenderState) const;` — Updates the given render state from the given GizmoElement.
- L29 _public prototype_ `bool UpdateRenderState(UGizmoElementBase& InGizmoElement, IToolsContextRenderAPI* InRenderAPI, const FVector& InLocalCenter, UGizmoElementBase::FRenderTraversalState& InOutRenderState, bool& bOutHasAlignRot, FQuat& OutAlignRot) const;` — Updates the given render state from the given GizmoElement.
- L32 _public prototype_ `static bool IsEnabledForInteractionState(const UGizmoElementBase& InGizmoElement, const TOptional<EGizmoElementInteractionState>& InInteractionState = {});` — Returns whether element is enabled for given interaction state. If the provided interaction state isn't set, it will use the currently applied state to the given element.
- L34 _public prototype_ `static bool IsPartial( UGizmoElementCircleBase& InGizmoElement, const FVector& InWorldCenter, const FVector& InWorldNormal, const FVector& InViewLocation, const FVector& InViewDirection, const bool bIsPerspectiveProjection);`

#### class `USimpleLambdaInteractiveGizmoBuilder`  
`class USimpleLambdaInteractiveGizmoBuilder : public UInteractiveGizmoBuilder`  
_L48-64_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveGizmoBuilder`
- desc: Gizmo builder that simply calls a particular lambda when building a gizmo. Makes it easy to register gizmo build behavior without writing a new class.
- L54 _public function_ `virtual UInteractiveGizmo* BuildGizmo(const FToolBuilderState& SceneState) const override`
- L63 _public member_ `TUniqueFunction<UInteractiveGizmo* (const FToolBuilderState& SceneState)> BuilderFunc;`

#### Free symbols / members of external scopes

- L66 _namespace_ `namespace UE`
- L66 _namespace_ `namespace GizmoUtil` (scope `UE`)
- L76 _prototype_ `UInteractiveGizmo* CreateGizmoViaSimpleBuilder(UInteractiveGizmoManager* GizmoManager, TSubclassOf<UInteractiveGizmo> GizmoClass, const FString& InstanceIdentifier, void* Owner);` (scope `UE::GizmoUtil`) — Uses the gizmo manager to create a gizmo of the given class (assuming that the gizmo type does not need any special setup beyond instantiation) without having to register a custom builder for that class ahead of time. This function lets the user bypass the need to define, register, and use a builder class, while still registering the gizmo properly with the gizmo manager. Under the hood, it creates and registers a temporary generic builder, uses it to make the gizmo, and then immediately deregisters the builder.
- L83 _function_ `template <typename GizmoClass> GizmoClass* CreateGizmoViaSimpleBuilder(UInteractiveGizmoManager* GizmoManager, const FString& InstanceIdentifier, void* GizmoOwner)` (scope `UE::GizmoUtil`) — Template version of CreateGizmoViaSimpleBuilder that does a cast on return.

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/GizmoViewContext.h` (Public)


#### class `UGizmoViewContext`  
`class UGizmoViewContext : public UObject, public UE::GizmoRenderingUtil::ISceneViewInterface`  
_L19-192_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,UE::GizmoRenderingUtil::ISceneViewInterface`
- desc: A context object that is meant to hold the scene information for the hovered viewport on a game thread, to be used by a gizmo later for hit testing. The organization mirrors FSceneView so that functions could be written in a templated way to use either FSceneView or UGizmoViewContext, though UGizmoViewContext only keeps the needed data.
- L60 _public function_ `void Reset(const FIntRect& InUnscaledViewRect, const FViewMatrices& InViewMatrices, const bool bInIsPerspectiveProjection, const FVector& InViewLocation)`
- L69 _public function_ `void ResetFromSceneView(const FSceneView& SceneView)` — Use this to reinitialize the object each frame for the hovered viewport.
- L75 _public function_ `const FIntRect& GetUnscaledViewRect() const override` — ISceneViewInterface
- L76 _public function_ `FVector GetViewLocation() const override`
- L77 _public function_ `FVector GetViewRight() const override`
- L78 _public function_ `FVector GetViewUp() const override`
- L79 _public function_ `FVector GetViewDirection() const override`
- L80 _public function_ `const FMatrix& GetProjectionMatrix() const override`
- L81 _public function_ `const FMatrix& GetViewMatrix() const override`
- L82 _public function_ `bool IsPerspectiveProjection() const override`
- L83 _public function_ `virtual double GetDPIScale() const override`
- L84 _public function_ `void SetDPIScale(const double InDPIScale)`
- L86 _public function_ `FVector4 WorldToScreen(const FVector& WorldPoint) const override`
- L92 _public function_ `FVector2D WorldToPixel(const FVector& WorldPoint) const` — WorldToScreen -> ScreenToPixel. A result of (-1, -1) indicates invalid W.
- L103 _public function_ `bool ScreenToPixel(const FVector4& ScreenPoint, FVector2D& OutPixelLocation) const`
- L124 _public function_ `FRay ScreenToRay(const FVector4& ScreenPosition) const`
- L160 _public function_ `FVector4 PixelToScreen(const FVector2D& PixelLocation, bool bClamped=true) const`
- L179 _public function_ `FRay PixelToScreenRay(const FVector2D& PixelLocation, bool bClamped=true) const`
- L185 _public member_ `FMatrices ViewMatrices;`
- L186 _public member_ `FIntRect UnscaledViewRect;`
- L187 _public member_ `FVector ViewLocation;`
- L190 _protected member_ `bool bIsPerspectiveProjection;`
- L191 _protected member_ `double DPIScale = 1.0;` — Usually set from ViewportClient

#### class `UGizmoViewContext::FMatrices`  
`class FMatrices`  
_L26-58_
- desc: Wrapping class for the matrices so that they can be accessed in the same way that they are accessed in FSceneView.
- L29 _public function_ `void ResetFromViewMatrices(const FViewMatrices& InViewMatrices)`
- L39 _public function_ `void ResetFromSceneView(const FSceneView& SceneView)`
- L44 _public function_ `const FMatrix& GetProjectionMatrix() const`
- L45 _public function_ `const FMatrix& GetInvProjectionMatrix() const`
- L46 _public function_ `const FMatrix& GetViewMatrix() const`
- L47 _public function_ `const FMatrix& GetInvViewMatrix() const`
- L48 _public function_ `const FMatrix& GetViewProjectionMatrix() const`
- L49 _public function_ `const FMatrix& GetInvViewProjectionMatrix() const`
- L52 _protected member_ `FMatrix ProjectionMatrix = FMatrix::Identity;`
- L53 _protected member_ `FMatrix InvProjectionMatrix = FMatrix::Identity;`
- L54 _protected member_ `FMatrix ViewMatrix = FMatrix::Identity;`
- L55 _protected member_ `FMatrix InvViewMatrix = FMatrix::Identity;`
- L56 _protected member_ `FMatrix ViewProjectionMatrix = FMatrix::Identity;`
- L57 _protected member_ `FMatrix InvViewProjectionMatrix = FMatrix::Identity;`

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/HitTargets.h` (Public)


#### class `UGizmoLambdaHitTarget`  
`class UGizmoLambdaHitTarget : public UObject, public IGizmoClickTarget`  
_L17-46_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,IGizmoClickTarget`
- desc: UGizmoLambdaHitTarget is an IGizmoClickTarget implementation that forwards the hit-test function to a TFunction
- L22 _public member_ `TUniqueFunction<FInputRayHit(const FInputDeviceRay&)> IsHitFunction;` — This function is called to determine if target is hit
- L25 _public member_ `TFunction<void(bool)> UpdateHoverFunction;` — This function is called to update hover state of the target
- L28 _public member_ `TFunction<void(bool)> UpdateInteractingFunction;` — This function is called to update interacting state of the target
- L31 _public member_ `TFunction<void(bool)> UpdateSelectedFunction;` — This function is called to update selected state of the target
- L34 _public member_ `TFunction<void(bool)> UpdateSubdueFunction;` — This function is called to update subdued state of the target
- L37 _public prototype_ `virtual FInputRayHit IsHit(const FInputDeviceRay& ClickPos) const;`
- L39 _public prototype_ `virtual void UpdateHoverState(bool bHovering) override;`
- L41 _public prototype_ `virtual void UpdateInteractingState(bool bInteracting) override;`
- L43 _public prototype_ `virtual void UpdateSelectedState(bool bSelected) override;`
- L45 _public prototype_ `virtual void UpdateSubdueState(bool bSubdued) override;`

#### class `UGizmoComponentHitTarget`  
`class UGizmoComponentHitTarget : public UObject, public IGizmoClickTarget`  
_L55-101_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,IGizmoClickTarget`
- desc: UGizmoComponentHitTarget is an IGizmoClickTarget implementation that hit-tests a UPrimitiveComponent
- L64 _public member_ `TObjectPtr<UPrimitiveComponent> Component;` — `UPROPERTY()` — Component->LineTraceComponent() is called to determine if the target is hit
- L72 _public member_ `TFunction<bool(const FInputDeviceRay&)> Condition = nullptr;` — If set, this condition is checked before performing the hit test. This gives a way to disable the hit test without hiding the component. This is useful, for instance, in a repositionable transform gizmo in world-coordinate mode, where the rotation components need to be hittable for movement, but not for repositioning.
- L75 _public member_ `TFunction<void(bool)> UpdateHoverFunction;` — This function is called to update hover state of the target
- L78 _public member_ `TFunction<void(bool)> UpdateInteractingFunction;` — This function is called to update interacting state of the target
- L81 _public member_ `TFunction<void(bool)> UpdateSelectedFunction;` — This function is called to update selected state of the target
- L84 _public member_ `TFunction<void(bool)> UpdateSubduedFunction;` — This function is called to update subdued state of the target
- L87 _public prototype_ `virtual FInputRayHit IsHit(const FInputDeviceRay& ClickPos) const;`
- L89 _public prototype_ `virtual void UpdateHoverState(bool bHovering) override;`
- L91 _public prototype_ `virtual void UpdateInteractingState(bool bHovering) override;`
- L93 _public prototype_ `virtual void UpdateSelectedState(bool bSelected) override;`
- L95 _public prototype_ `virtual void UpdateSubdueState(bool bSubdued) override;`
- L98 _public prototype_ `static UGizmoComponentHitTarget* Construct( UPrimitiveComponent* Component, UObject* Outer = (UObject*)GetTransientPackage());`

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/IntervalGizmo.h` (Public)


#### class `AIntervalGizmoActor`  
`class AIntervalGizmoActor : public AGizmoActor`  
_L35-70_
- reflection: `UCLASS(Transient, NotPlaceable, Hidden, NotBlueprintable, NotBlueprintType, MinimalAPI)`
- inherits: `AGizmoActor`
- desc: AIntervalGizmoActor is an Actor type intended to be used with UIntervalGizmo, as the in-scene visual representation of the Gizmo. FIntervalGizmoActorFactory returns an instance of this Actor type (or a subclass). If a particular sub-Gizmo is not required, simply set that UProperty to null.
- L40 _public prototype_ `AIntervalGizmoActor();`
- L45 _public member_ `TObjectPtr<UGizmoLineHandleComponent> UpIntervalComponent = nullptr;` — `UPROPERTY()`
- L48 _public member_ `TObjectPtr<UGizmoLineHandleComponent> DownIntervalComponent = nullptr;` — `UPROPERTY()`
- L51 _public member_ `TObjectPtr<UGizmoLineHandleComponent> ForwardIntervalComponent = nullptr;` — `UPROPERTY()`
- L54 _public member_ `TObjectPtr<UGizmoLineHandleComponent> BackwardIntervalComponent = nullptr;` — `UPROPERTY()`
- L57 _public member_ `TObjectPtr<UGizmoLineHandleComponent> RightIntervalComponent = nullptr;` — `UPROPERTY()`
- L60 _public member_ `TObjectPtr<UGizmoLineHandleComponent> LeftIntervalComponent = nullptr;` — `UPROPERTY()`
- L67 _public prototype_ `static AIntervalGizmoActor* ConstructDefaultIntervalGizmo(UWorld* World, UGizmoViewContext* GizmoViewContext);` — Create a new instance of AIntervalGizmoActor and populate the various sub-components with standard GizmoXComponent instances

#### class `FIntervalGizmoActorFactory`  
`class FIntervalGizmoActorFactory`  
_L84-107_
- desc: FIntervalGizmoActorFactory creates new instances of AIntervalGizmoActor which are used by UIntervalGizmo to implement 3D interval Gizmos. An instance of FIntervalGizmoActorFactory is passed to UIntervalGizmo (by way of UIntervalGizmoBuilder), which then calls CreateNewGizmoActor() to spawn new Gizmo Actors. By default CreateNewGizmoActor() returns a default Gizmo Actor suitable for a three-axis Interval Gizmo, override this function to customize the Actor sub-elements.
- L87 _public function_ `FIntervalGizmoActorFactory(UGizmoViewContext* GizmoViewContextIn) : GizmoViewContext(GizmoViewContextIn)`
- L96 _public function_ `virtual AIntervalGizmoActor* CreateNewGizmoActor(UWorld* World) const` — @param World the UWorld to create the new Actor in @return new AIntervalGizmoActor instance with members initialized with Components suitable for a transformation Gizmo
- L106 _protected member_ `UGizmoViewContext* GizmoViewContext = nullptr;` — Needs to be set (and kept alive elsewhere) so that created handle gizmos can adjust their length according to view (when not using world-scaling).

#### class `UIntervalGizmoBuilder`  
`class UIntervalGizmoBuilder : public UInteractiveGizmoBuilder`  
_L112-145_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveGizmoBuilder`
- L121 _public member_ `TSharedPtr<FIntervalGizmoActorFactory> GizmoActorBuilder;` — If set, this Actor Builder will be passed to UIntervalGizmo instances. Otherwise new instances of the base FIntervalGizmoActorFactory are created internally.
- L131 _public member_ `TFunction<void(UPrimitiveComponent*, bool)> UpdateHoverFunction;` — If set, this hover function will be passed to UIntervalGizmo instances to use instead of the default. Hover is complicated for UIntervalGizmo because all it knows about the different gizmo scene elements is that they are UPrimitiveComponent (coming from the AIntervalGizmoActor). The default hover function implementation is to try casting to UGizmoBaseComponent and calling ::UpdateHoverState(). If you are using different Components that do not subclass UGizmoBaseComponent, and you want hover to work, you will need to provide a different hover update function.
- L141 _public member_ `TFunction<void(UPrimitiveComponent*, EToolContextCoordinateSystem)> UpdateCoordSystemFunction;` — If set, this coord-system function will be passed to UIntervalGizmo instances to use instead of the default UpdateCoordSystemFunction. By default theUIntervalGizmo will query the external Context to ask whether it should be using world or local coordinate system. Then the default UpdateCoordSystemFunction will try casting to UGizmoBaseCmponent and passing that info on via UpdateWorldLocalState(); If you are using different Components that do not subclass UGizmoBaseComponent, and you want the coord system to be configurable, you will need to provide a different update function.
- L144 _public prototype_ `virtual UInteractiveGizmo* BuildGizmo(const FToolBuilderState& SceneState) const override;`

#### class `UIntervalGizmo`  
`class UIntervalGizmo : public UInteractiveGizmo`  
_L149-331_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveGizmo`
- L155 _public member_ `static FString GizmoName;`
- L157 _public prototype_ `virtual void SetWorld(UWorld* WorldIn);`
- L158 _public prototype_ `virtual void SetGizmoActorBuilder(TSharedPtr<FIntervalGizmoActorFactory> Builder);`
- L159 _public prototype_ `virtual void SetUpdateHoverFunction(TFunction<void(UPrimitiveComponent*, bool)> HoverFunction);`
- L160 _public prototype_ `virtual void SetUpdateCoordSystemFunction(TFunction<void(UPrimitiveComponent*, EToolContextCoordinateSystem)> CoordSysFunction);`
- L163 _public prototype_ `virtual void Setup() override;` — UInteractiveGizmo overrides
- L164 _public prototype_ `virtual void Shutdown() override;`
- L165 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L194 _public prototype_ `virtual void SetActiveTarget(UTransformProxy* TransformTargetIn, UGizmoLocalFloatParameterSource* UpInterval, UGizmoLocalFloatParameterSource* DownInterval, UGizmoLocalFloatParameterSource* ForwardInterval, IToolContextTransactionProvider* TransactionProvider = nullptr);`
- L196 _public prototype_ `virtual void SetActiveTarget(UTransformProxy* TransformTargetIn, const FParameterSources& ParameterSources, IToolContextTransactionProvider* TransactionProvider = nullptr);`
- L200 _public prototype_ `virtual void SetWorldAlignmentFunctions( TUniqueFunction<bool()>&& ShouldAlignDestination, TUniqueFunction<bool(const FRay&, FVector&)>&& DestinationAlignmentRayCaster );` — Sets functions that allow the endpoints of the intervals to be snapped to world geometry when ShouldAlignDestination is true
- L206 _public function_ `virtual void BeginEditSequence()` — Notifies listeners that a sequence of edits to the gizmo is beginning/ending (at the start/end of a drag).
- L207 _public function_ `virtual void EndEditSequence()`
- L212 _public prototype_ `virtual void ClearSources();` — Clear the parameter sources for this gizmo
- L217 _public prototype_ `virtual void ClearActiveTarget();` — Clear the active target object for the Gizmo
- L222 _public prototype_ `virtual FTransform GetGizmoTransform() const;` — Gets the location and orientation of the interval gizmo.
- L225 _public prototype_ `virtual void SetVisibility(bool bVisible);` — Set visibility of the Gizmo
- L229 _public member_ `TObjectPtr<UGizmoTransformChangeStateTarget> StateTarget = nullptr;` — `UPROPERTY()` — State target is shared across gizmos, and created internally during SetActiveTarget()
- L235 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnIntervalChanged, UIntervalGizmo*, const FVector&, float);` — Called when an interval is changed. The delegate gives a pointer to the gizmo, the direction of the interval in gizmo space, and the new parameter value.
- L236 _public member_ `FOnIntervalChanged OnIntervalChanged;`
- L239 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnBeginIntervalEdit, UIntervalGizmo*);` — Called when the gizmo is notified about the start of a sequence of interval changes.
- L240 _public member_ `FOnBeginIntervalEdit OnBeginIntervalGizmoEdit;`
- L243 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnEndIntervalEdit, UIntervalGizmo*);` — Called when the gizmo is notified about the end of a sequence of interval changes.
- L244 _public member_ `FOnEndIntervalEdit OnEndIntervalGizmoEdit;`
- L249 _protected member_ `TObjectPtr<UWorld> World;` — `UPROPERTY()` — GizmoActors will be spawned in this World
- L252 _protected member_ `TObjectPtr<AIntervalGizmoActor> GizmoActor = nullptr;` — `UPROPERTY()`
- L256 _protected member_ `TObjectPtr<UTransformProxy> TransformProxy = nullptr;` — `UPROPERTY()` — The gizmo tracks the location and orientation of the transform in this TransformProxy.
- L260 _protected member_ `TArray<TObjectPtr<UPrimitiveComponent>> ActiveComponents;` — `UPROPERTY()` — list of current-active child components
- L264 _protected member_ `TArray<TObjectPtr<UInteractiveGizmo>> ActiveGizmos;` — `UPROPERTY()` — list of currently-active child gizmos
- L268 _protected member_ `TObjectPtr<UGizmoLocalFloatParameterSource> UpIntervalSource = nullptr;` — `UPROPERTY()` — +/- Z axis parameter sources
- L270 _protected member_ `TObjectPtr<UGizmoLocalFloatParameterSource> DownIntervalSource = nullptr;` — `UPROPERTY()`
- L273 _protected member_ `TObjectPtr<UGizmoLocalFloatParameterSource> ForwardIntervalSource = nullptr;` — `UPROPERTY()` — +/- Y axis parameter sources
- L275 _protected member_ `TObjectPtr<UGizmoLocalFloatParameterSource> BackwardIntervalSource = nullptr;` — `UPROPERTY()`
- L278 _protected member_ `TObjectPtr<UGizmoLocalFloatParameterSource> RightIntervalSource = nullptr;` — `UPROPERTY()` — +/- X axis parameter sources
- L280 _protected member_ `TObjectPtr<UGizmoLocalFloatParameterSource> LeftIntervalSource = nullptr;` — `UPROPERTY()`
- L284 _protected member_ `TObjectPtr<UGizmoComponentAxisSource> AxisXSource = nullptr;` — `UPROPERTY()` — X-axis source is shared across Gizmos, and created internally during SetActiveTarget()
- L288 _protected member_ `TObjectPtr<UGizmoComponentAxisSource> AxisYSource = nullptr;` — `UPROPERTY()` — Y-axis source is shared across Gizmos, and created internally during SetActiveTarget()
- L292 _protected member_ `TObjectPtr<UGizmoComponentAxisSource> AxisZSource = nullptr;` — `UPROPERTY()` — Z-axis source is shared across Gizmos, and created internally during SetActiveTarget()
- L295 _protected member_ `TSharedPtr<FIntervalGizmoActorFactory> GizmoActorBuilder;`
- L300 _protected member_ `TFunction<void(UPrimitiveComponent*, bool)> UpdateHoverFunction;` — This function is called on each active GizmoActor Component to update it's hover state. If the Component is not a UGizmoBaseCmponent, the client needs to provide a different implementation of this function via the ToolBuilder
- L305 _protected member_ `TFunction<void(UPrimitiveComponent*, EToolContextCoordinateSystem)> UpdateCoordSystemFunction;` — This function is called on each active GizmoActor Component to update it's coordinate system (eg world/local). If the Component is not a UGizmoBaseCmponent, the client needs to provide a different implementation of this function via the ToolBuilder
- L307 _protected function_ `TUniqueFunction<bool()> ShouldAlignDestination = []()`
- L307 _protected member_ `TUniqueFunction<bool()> ShouldAlignDestination = []() { return false; };`
- L308 _protected function_ `TUniqueFunction<bool(const FRay&, FVector&)> DestinationAlignmentRayCaster = [](const FRay&, FVector&)`
- L308 _protected member_ `TUniqueFunction<bool(const FRay&, FVector&)> DestinationAlignmentRayCaster = [](const FRay&, FVector&) {return false; };`
- L312 _protected prototype_ `virtual UInteractiveGizmo* AddIntervalHandleGizmo( USceneComponent* RootComponent, UPrimitiveComponent* HandleComponent, IGizmoAxisSource* AxisSource, IGizmoFloatParameterSource* FloatParameterSource, float MinParameter, float MaxParameter, IGizmoStateTarget* StateTargetIn);` — @return a new instance of the standard axis-handle Gizmo
- L324 _private member_ `UE::Geometry::FInterval1f UpIntervalRange, DownIntervalRange, ForwardIntervalRange, BackwardIntervalRange, RightIntervalRange, LeftIntervalRange;` — Valid ranges for intervals
- L324 _private member_ `UE::Geometry::FInterval1f UpIntervalRange, DownIntervalRange, ForwardIntervalRange, BackwardIntervalRange, RightIntervalRange, LeftIntervalRange;` — Valid ranges for intervals
- L324 _private member_ `UE::Geometry::FInterval1f UpIntervalRange, DownIntervalRange, ForwardIntervalRange, BackwardIntervalRange, RightIntervalRange, LeftIntervalRange;` — Valid ranges for intervals
- L324 _private member_ `UE::Geometry::FInterval1f UpIntervalRange, DownIntervalRange, ForwardIntervalRange, BackwardIntervalRange, RightIntervalRange, LeftIntervalRange;` — Valid ranges for intervals
- L324 _private member_ `UE::Geometry::FInterval1f UpIntervalRange, DownIntervalRange, ForwardIntervalRange, BackwardIntervalRange, RightIntervalRange, LeftIntervalRange;` — Valid ranges for intervals
- L324 _private member_ `UE::Geometry::FInterval1f UpIntervalRange, DownIntervalRange, ForwardIntervalRange, BackwardIntervalRange, RightIntervalRange, LeftIntervalRange;` — Valid ranges for intervals
- L327 _private prototype_ `void EnumerateValidIntervals(TFunctionRef<void(UGizmoLocalFloatParameterSource* Source, UGizmoLineHandleComponent* Component, UGizmoComponentAxisSource* Axis, UE::Geometry::FInterval1f& IntervalRange, FVector3d Direction, float DirectionAxisSign)> IterFn);` — Call IterFn on each Source/Component combination where the Source is not null. Note IterFn will still be called if the component and/or axis are null.
- L330 _private prototype_ `void EnumerateAllIntervals(TFunctionRef<void(UGizmoLocalFloatParameterSource* Source, UGizmoLocalFloatParameterSource* OppositeSource, UGizmoLineHandleComponent* Component, UE::Geometry::FInterval1f& IntervalRange, float DirectionAxisSign)> IterFn);` — Call IterFn on each interval Component (including those without a Source)

#### enum `UIntervalGizmo::EDefaultParameterRanges`  
`enum class EDefaultParameterRanges`  
_L167-175_
- L170 _public enumerator_ `HalfRange` — Init all interval ranges to [0, +/- FLT_MAX] in the axis direction
- L172 _public enumerator_ `FullRange` — Init all interval ranges to [-FLT_MAX, FLT_MAX]
- L174 _public enumerator_ `HalfIfMatched` — Init interval ranges to 'half range' if 'matched' by the opposite interval on the same axis, or 'full range' otherwise

#### struct `UIntervalGizmo::FParameterSources`  
`struct FParameterSources`  
_L178-192_
- desc: Input parameter sources and related configuration
- L181 _public member_ `UGizmoLocalFloatParameterSource* RightInterval = nullptr;` — +/- X axis parameter sources
- L182 _public member_ `UGizmoLocalFloatParameterSource* LeftInterval = nullptr;`
- L184 _public member_ `UGizmoLocalFloatParameterSource* ForwardInterval = nullptr;` — +/- Y axis parameter sources
- L185 _public member_ `UGizmoLocalFloatParameterSource* BackwardInterval = nullptr;`
- L187 _public member_ `UGizmoLocalFloatParameterSource* UpInterval = nullptr;` — +/- Z axis parameter sources
- L188 _public member_ `UGizmoLocalFloatParameterSource* DownInterval = nullptr;`
- L190 _public member_ `EDefaultParameterRanges InitParameterRanges = EDefaultParameterRanges::HalfIfMatched;`

#### class `UGizmoAxisIntervalParameterSource`  
`class UGizmoAxisIntervalParameterSource : public UGizmoBaseFloatParameterSource`  
_L341-377_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGizmoBaseFloatParameterSource`
- desc: UGizmoAxisIntervalParameterSource is an IGizmoFloatParameterSource implementation that interprets the float value as the parameter of a line equation, and maps this parameter to a 3D translation along a line with origin/direction given by an IGizmoAxisSource. This translation is applied to an IGizmoTransformSource. This ParameterSource is intended to be used to create 3D Axis Interval Gizmos.
- L345 _public prototype_ `virtual float GetParameter() const override;`
- L347 _public prototype_ `virtual void SetParameter(float NewValue) override;`
- L349 _public prototype_ `virtual void BeginModify();`
- L351 _public prototype_ `virtual void EndModify();`
- L357 _public member_ `TScriptInterface<IGizmoFloatParameterSource> FloatParameterSource;` — `UPROPERTY()`
- L362 _public member_ `float MinParameter;` — `UPROPERTY()`
- L365 _public member_ `float MaxParameter;` — `UPROPERTY()`
- L372 _public prototype_ `static UGizmoAxisIntervalParameterSource* Construct( IGizmoFloatParameterSource* FloatSourceIn, float ParameterMin = -FLT_MAX, float ParameterMax = FLT_MAX, UObject* Outer = (UObject*)GetTransientPackage());` — Create a standard instance of this ParameterSource, with the given AxisSource and TransformSource

#### Free symbols / members of external scopes

- L235 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnIntervalChanged, UIntervalGizmo*, const FVector&, float);` — Called when an interval is changed. The delegate gives a pointer to the gizmo, the direction of the interval in gizmo space, and the new parameter value.
- L239 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnBeginIntervalEdit, UIntervalGizmo*);` — Called when the gizmo is notified about the start of a sequence of interval changes.
- L243 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnEndIntervalEdit, UIntervalGizmo*);` — Called when the gizmo is notified about the end of a sequence of interval changes.

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/ParameterSourcesFloat.h` (Public)


#### struct `FGizmoFloatParameterChange`  
`struct FGizmoFloatParameterChange`  
_L20-40_
- reflection: `USTRUCT()`
- desc: FGizmoVec2ParameterChange represents a change in the value of an IGizmoFloatParameterSource. IGizmoFloatParameterSource implementations use this to track changes and emit delta information.
- L25 _public member_ `float InitialValue = 0;` — `UPROPERTY()`
- L28 _public member_ `float CurrentValue = 0;` — `UPROPERTY()`
- L31 _public function_ `float GetChangeDelta() const`
- L36 _public function_ `explicit FGizmoFloatParameterChange(float StartValue = 0)`

#### class `UGizmoBaseFloatParameterSource`  
`class UGizmoBaseFloatParameterSource : public UObject, public IGizmoFloatParameterSource`  
_L48-76_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,IGizmoFloatParameterSource`
- desc: UGizmoBaseFloatParameterSource is a base implementation of IGizmoFloatParameterSource, which is not functional but adds an OnParameterChanged delegate for further subclasses.
- L52 _public function_ `virtual float GetParameter() const`
- L58 _public function_ `virtual void SetParameter(float NewValue)`
- L64 _public function_ `virtual void BeginModify()`
- L68 _public function_ `virtual void EndModify()`
- L74 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGizmoFloatParameterSourceChanged, IGizmoFloatParameterSource*, FGizmoFloatParameterChange);`
- L75 _public member_ `FOnGizmoFloatParameterSourceChanged OnParameterChanged;`

#### class `UGizmoLocalFloatParameterSource`  
`class UGizmoLocalFloatParameterSource : public UGizmoBaseFloatParameterSource`  
_L86-119_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGizmoBaseFloatParameterSource`
- desc: UGizmoLocalFloatParameterSource is an implementation of IGizmoFloatParameterSource (by way of UGizmoBaseFloatParameterSource) which locally stores the relevant Parameter and emits update events via the OnParameterChanged delegate.
- L90 _public function_ `virtual float GetParameter() const override`
- L95 _public function_ `virtual void SetParameter(float NewValue) override`
- L102 _public function_ `virtual void BeginModify()`
- L107 _public function_ `virtual void EndModify()`
- L115 _public member_ `float Value = 0.0f;` — `UPROPERTY()`
- L118 _public member_ `FGizmoFloatParameterChange LastChange;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L74 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGizmoFloatParameterSourceChanged, IGizmoFloatParameterSource*, FGizmoFloatParameterChange);`

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/ParameterSourcesVec2.h` (Public)


#### struct `FGizmoVec2ParameterChange`  
`struct FGizmoVec2ParameterChange`  
_L19-39_
- reflection: `USTRUCT()`
- desc: FGizmoVec2ParameterChange represents a change in the value of an IGizmoVec2ParameterSource. IGizmoVec2ParameterSource implementations use this to track changes and emit delta information.
- L24 _public member_ `FVector2D InitialValue = FVector2D::ZeroVector;` — `UPROPERTY()`
- L27 _public member_ `FVector2D CurrentValue = FVector2D::ZeroVector;` — `UPROPERTY()`
- L30 _public function_ `FVector2D GetChangeDelta() const`
- L35 _public function_ `explicit FGizmoVec2ParameterChange(const FVector2D& StartValue = FVector2D::ZeroVector)`

#### class `UGizmoBaseVec2ParameterSource`  
`class UGizmoBaseVec2ParameterSource : public UObject, public IGizmoVec2ParameterSource`  
_L48-76_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,IGizmoVec2ParameterSource`
- desc: UGizmoBaseVec2ParameterSource is a base implementation of IGizmoVec2ParameterSource, which is not functional but adds an OnParameterChanged delegate for further subclasses.
- L52 _public function_ `virtual FVector2D GetParameter() const`
- L58 _public function_ `virtual void SetParameter(const FVector2D& NewValue)`
- L64 _public function_ `virtual void BeginModify()`
- L68 _public function_ `virtual void EndModify()`
- L74 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGizmoVec2ParameterSourceChanged, IGizmoVec2ParameterSource*, FGizmoVec2ParameterChange);`
- L75 _public member_ `FOnGizmoVec2ParameterSourceChanged OnParameterChanged;`

#### class `UGizmoLocalVec2ParameterSource`  
`class UGizmoLocalVec2ParameterSource : public UGizmoBaseVec2ParameterSource`  
_L86-119_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGizmoBaseVec2ParameterSource`
- desc: UGizmoBaseVec2ParameterSource is an implementation of IGizmoVec2ParameterSource (by way of UGizmoBaseVec2ParameterSource) which locally stores the relevant Parameter and emits update events via the OnParameterChanged delegate.
- L90 _public function_ `virtual FVector2D GetParameter() const override`
- L95 _public function_ `virtual void SetParameter(const FVector2D& NewValue) override`
- L102 _public function_ `virtual void BeginModify()`
- L107 _public function_ `virtual void EndModify()`
- L115 _public member_ `FVector2D Value = FVector2D::ZeroVector;` — `UPROPERTY()`
- L118 _public member_ `FGizmoVec2ParameterChange LastChange;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L74 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGizmoVec2ParameterSourceChanged, IGizmoVec2ParameterSource*, FGizmoVec2ParameterChange);`

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/ParameterToTransformAdapters.h` (Public)


#### class `UGizmoAxisTranslationParameterSource`  
`class UGizmoAxisTranslationParameterSource : public UGizmoBaseFloatParameterSource`  
_L27-105_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGizmoBaseFloatParameterSource`
- desc: UGizmoAxisTranslationParameterSource is an IGizmoFloatParameterSource implementation that interprets the float value as the parameter of a line equation, and maps this parameter to a 3D translation along a line with origin/direction given by an IGizmoAxisSource. This translation is applied to an IGizmoTransformSource. This ParameterSource is intended to be used to create 3D Axis Translation Gizmos.
- L38 _public function_ `TUniqueFunction<bool(double AxisDelta, double& SnappedDelta)> AxisDeltaConstraintFunction = [](double, double&)` — Optional axis delta constraint function. This can be used to snap/constrain the "parameter delta" value, for example to snap it to fixed increments along the axis. @return true if constrained delta was found and should be used, false to ignore
- L38 _public member_ `TUniqueFunction<bool(double AxisDelta, double& SnappedDelta)> AxisDeltaConstraintFunction = [](double, double&) { return false; };` — Optional axis delta constraint function. This can be used to snap/constrain the "parameter delta" value, for example to snap it to fixed increments along the axis. @return true if constrained delta was found and should be used, false to ignore
- L46 _public function_ `TUniqueFunction<bool(const FVector& Input, FVector& PreProjectedOutput)> PositionConstraintFunction = [](const FVector&, FVector&)` — Optional position constraint function. Called during interaction with the new transform origin. To snap the transform to a new position, return as second value, and return true from your lambda. Note that returned snap point will be projected onto the current translation origin/axis. @return true if constraint point was found and should be used, false to ignore
- L46 _public member_ `TUniqueFunction<bool(const FVector& Input, FVector& PreProjectedOutput)> PositionConstraintFunction = [](const FVector&, FVector&) { return false; };` — Optional position constraint function. Called during interaction with the new transform origin. To snap the transform to a new position, return as second value, and return true from your lambda. Note that returned snap point will be projected onto the current translation origin/axis. @return true if constraint point was found and should be used, false to ignore
- L48 _public function_ `virtual float GetParameter() const override`
- L53 _public prototype_ `virtual void SetParameter(float NewValue) override;`
- L55 _public prototype_ `virtual void BeginModify() override;`
- L56 _public prototype_ `virtual void EndModify() override;`
- L62 _public member_ `TScriptInterface<IGizmoAxisSource> AxisSource;` — `UPROPERTY()` — The Parameter line-equation value is converted to a 3D Translation along this Axis
- L66 _public member_ `TScriptInterface<IGizmoTransformSource> TransformSource;` — `UPROPERTY()` — This TransformSource is updated by applying the constructed 3D translation
- L72 _public member_ `float Parameter = 0.0f;` — `UPROPERTY()` — Parameter is the line-equation parameter that this FloatParameterSource provides
- L76 _public member_ `FGizmoFloatParameterChange LastChange;` — `UPROPERTY()` — Active parameter change (only valid between BeginModify/EndModify)
- L80 _public member_ `FVector CurTranslationAxis;` — `UPROPERTY()` — tranlsation axis for current parameter edit (only valid between BeginModify/EndModify)
- L84 _public member_ `FVector CurTranslationOrigin;` — `UPROPERTY()` — tranlsation origin for current parameter edit (only valid between BeginModify/EndModify)
- L88 _public member_ `FTransform InitialTransform;` — `UPROPERTY()` — Saved copy of Initial Transform for current parameter edit (only valid between BeginModify/EndModify)
- L95 _public function_ `static UGizmoAxisTranslationParameterSource* Construct( IGizmoAxisSource* AxisSourceIn, IGizmoTransformSource* TransformSourceIn, UObject* Outer = (UObject*)GetTransientPackage())` — Create a standard instance of this ParameterSource, with the given AxisSource and TransformSource

#### class `UGizmoPlaneTranslationParameterSource`  
`class UGizmoPlaneTranslationParameterSource : public UGizmoBaseVec2ParameterSource`  
_L119-209_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGizmoBaseVec2ParameterSource`
- desc: UGizmoAxisRotationParameterSource is an IGizmoVec2ParameterSource implementation that interprets the FVector2D parameter as a position in a 2D plane, and maps this position to a 3D translation in a plane with origin/normal given by an IGizmoAxisSource. This translation is applied to an IGizmoTransformSource. This ParameterSource is intended to be used to create 3D Plane Translation Gizmos.
- L130 _public function_ `TUniqueFunction<bool(double AxisDelta, double& SnappedDelta)> AxisXDeltaConstraintFunction = [](double, double&)` — Optional axis delta constraint function. This can be used to snap/constrain the "parameter delta" value, for example to snap it to fixed increments along the axis. The AxisDeltaConstraintFunction is used separately for the X and Y axes of the plane translation @return true if constrained delta was found and should be used, false to ignore
- L130 _public member_ `TUniqueFunction<bool(double AxisDelta, double& SnappedDelta)> AxisXDeltaConstraintFunction = [](double, double&) { return false; };` — Optional axis delta constraint function. This can be used to snap/constrain the "parameter delta" value, for example to snap it to fixed increments along the axis. The AxisDeltaConstraintFunction is used separately for the X and Y axes of the plane translation @return true if constrained delta was found and should be used, false to ignore
- L131 _public function_ `TUniqueFunction<bool(double AxisDelta, double& SnappedDelta)> AxisYDeltaConstraintFunction = [](double, double&)`
- L131 _public member_ `TUniqueFunction<bool(double AxisDelta, double& SnappedDelta)> AxisYDeltaConstraintFunction = [](double, double&) { return false; };`
- L138 _public function_ `TUniqueFunction<bool(const FVector& Input, FVector& PreProjectedOutput)> PositionConstraintFunction = [](const FVector&, FVector&)` — Optional position constraint function. Called during interaction with the new transform origin. To snap the transform to a new position, return as second value, and return true from your lambda. @return true if constraint point was found and should be used, false to ignore
- L138 _public member_ `TUniqueFunction<bool(const FVector& Input, FVector& PreProjectedOutput)> PositionConstraintFunction = [](const FVector&, FVector&) { return false; };` — Optional position constraint function. Called during interaction with the new transform origin. To snap the transform to a new position, return as second value, and return true from your lambda. @return true if constraint point was found and should be used, false to ignore
- L142 _public member_ `bool bProjectConstrainedPosition = true;` — When true, the output of PositionConstraintFunction will be projected onto the current translation origin/axis.
- L144 _public function_ `virtual FVector2D GetParameter() const override`
- L149 _public prototype_ `virtual void SetParameter(const FVector2D& NewValue) override;`
- L151 _public prototype_ `virtual void BeginModify() override;`
- L152 _public prototype_ `virtual void EndModify() override;`
- L158 _public member_ `TScriptInterface<IGizmoAxisSource> AxisSource;` — `UPROPERTY()` — AxisSource provides the 3D plane (origin/normal/u/v) that is used to interpret the 2D parameters
- L162 _public member_ `TScriptInterface<IGizmoTransformSource> TransformSource;` — `UPROPERTY()` — This TransformSource is updated by applying the constructed 3D translation
- L168 _public member_ `FVector2D Parameter = FVector2D::ZeroVector;` — `UPROPERTY()` — Parameter is the two line-equation parameters that this Vec2ParameterSource provides
- L172 _public member_ `FGizmoVec2ParameterChange LastChange;` — `UPROPERTY()` — Active parameter change (only valid between BeginModify/EndModify)
- L176 _public member_ `FVector CurTranslationOrigin;` — `UPROPERTY()` — plane origin for current parameter edit (only valid between BeginModify/EndModify)
- L180 _public member_ `FVector CurTranslationNormal;` — `UPROPERTY()` — plane normal for current parameter edit (only valid between BeginModify/EndModify)
- L184 _public member_ `FVector CurTranslationAxisX;` — `UPROPERTY()` — in-plane axis X for current parameter edit (only valid between BeginModify/EndModify)
- L188 _public member_ `FVector CurTranslationAxisY;` — `UPROPERTY()` — in-plane axis Y for current parameter edit (only valid between BeginModify/EndModify)
- L192 _public member_ `FTransform InitialTransform;` — `UPROPERTY()` — Saved copy of Initial Transform for current parameter edit (only valid between BeginModify/EndModify)
- L199 _public function_ `static UGizmoPlaneTranslationParameterSource* Construct( IGizmoAxisSource* AxisSourceIn, IGizmoTransformSource* TransformSourceIn, UObject* Outer = (UObject*)GetTransientPackage())` — Create a standard instance of this ParameterSource, with the given AxisSource and TransformSource

#### class `UGizmoAxisRotationParameterSource`  
`class UGizmoAxisRotationParameterSource : public UGizmoBaseFloatParameterSource`  
_L223-300_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGizmoBaseFloatParameterSource`
- desc: UGizmoAxisRotationParameterSource is an IGizmoFloatParameterSource implementation that interprets the float parameter as an angle, and maps this angle to a 3D rotation around an IGizmoAxisSource (ie 3D axis). This rotation is applied to an IGizmoTransformSource. This ParameterSource is intended to be used to create 3D Rotation Gizmos.
- L233 _public function_ `TUniqueFunction<bool(double AngleDelta, double& SnappedAngleDelta)> AngleDeltaConstraintFunction = [](double, double&)` — Optional axis-delta-angle constraint function. This can be used to snap/constrain the "angle delta" value, for example to snap it to fixed angle steps around the axis. @return true if constrained angle was found and should be used, false to ignore
- L233 _public member_ `TUniqueFunction<bool(double AngleDelta, double& SnappedAngleDelta)> AngleDeltaConstraintFunction = [](double, double&) { return false; };` — Optional axis-delta-angle constraint function. This can be used to snap/constrain the "angle delta" value, for example to snap it to fixed angle steps around the axis. @return true if constrained angle was found and should be used, false to ignore
- L240 _public function_ `TUniqueFunction<FQuat(const FQuat&)> RotationConstraintFunction = [](const FQuat& DeltaRotation)` — Optional rotation constraint function. Called during interaction with the rotation delta To snap the rotation delta, return the snapped quat @return The snapped value of the rotation delta
- L240 _public member_ `TUniqueFunction<FQuat(const FQuat&)> RotationConstraintFunction = [](const FQuat& DeltaRotation) { return DeltaRotation; };` — Optional rotation constraint function. Called during interaction with the rotation delta To snap the rotation delta, return the snapped quat @return The snapped value of the rotation delta
- L242 _public function_ `virtual float GetParameter() const override`
- L247 _public prototype_ `virtual void SetParameter(float NewValue) override;`
- L249 _public prototype_ `virtual void BeginModify() override;`
- L250 _public prototype_ `virtual void EndModify() override;`
- L256 _public member_ `TScriptInterface<IGizmoAxisSource> AxisSource;` — `UPROPERTY()` — float-parameter Angle is mapped to a 3D Rotation around this Axis
- L260 _public member_ `TScriptInterface<IGizmoTransformSource> TransformSource;` — `UPROPERTY()` — This TransformSource is updated by applying the constructed 3D rotation
- L266 _public member_ `float Angle = 0.0f;` — `UPROPERTY()` — Angle is the parameter that this FloatParameterSource provides
- L270 _public member_ `FGizmoFloatParameterChange LastChange;` — `UPROPERTY()` — Active parameter change (only valid between BeginModify/EndModify)
- L274 _public member_ `FVector CurRotationAxis;` — `UPROPERTY()` — Rotation axis for current parameter edit (only valid between BeginModify/EndModify)
- L278 _public member_ `FVector CurRotationOrigin;` — `UPROPERTY()` — Rotation origin for current parameter edit (only valid between BeginModify/EndModify)
- L282 _public member_ `FTransform InitialTransform;` — `UPROPERTY()` — Saved copy of Initial Transform for current parameter edit (only valid between BeginModify/EndModify)
- L290 _public function_ `static UGizmoAxisRotationParameterSource* Construct( IGizmoAxisSource* AxisSourceIn, IGizmoTransformSource* TransformSourceIn, UObject* Outer = (UObject*)GetTransientPackage())` — Create a standard instance of this ParameterSource, with the given AxisSource and TransformSource

#### class `UGizmoUniformScaleParameterSource`  
`class UGizmoUniformScaleParameterSource : public UGizmoBaseVec2ParameterSource`  
_L322-409_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGizmoBaseVec2ParameterSource`
- desc: UGizmoUniformScaleParameterSource is an IGizmoVec2ParameterSource implementation that interprets the Vec2 parameter as the position in a 2D plane, and maps this parameter to a change in a uniform scale value. This scale is applied to an IGizmoTransformSource. The X/Y plane parameter deltas are converted to a uniform scale delta simply by adding them. This assumpes that the 3D plane is oriented such that "positive" along the X and Y tangent axes corresponds to something semantically meaningful. It's up to the client to do this. This ParameterSource is intended to be used to create 3D Uniform Scale Gizmos.
- L332 _public function_ `TUniqueFunction<bool(double ScaleAxisDelta, double& SnappedScaleAxisDelta)> ScaleAxisDeltaConstraintFunction = [](double, double&)` — Optional scale axis delta constraint function. This can be used to snap/constrain the "scale delta" value, for example to snap it to fixed increments along the axis. @return true if constrained delta was found and should be used, false to ignore
- L332 _public member_ `TUniqueFunction<bool(double ScaleAxisDelta, double& SnappedScaleAxisDelta)> ScaleAxisDeltaConstraintFunction = [](double, double&) { return false; };` — Optional scale axis delta constraint function. This can be used to snap/constrain the "scale delta" value, for example to snap it to fixed increments along the axis. @return true if constrained delta was found and should be used, false to ignore
- L338 _public function_ `TUniqueFunction<double(const double&)> ScaleConstraintFunction = [](const double& DeltaScale)` — Optional scale constraint function. Called during interaction with the scale delta To snap the scale delta, return the snapped value @return The snapped value of the scale delta
- L338 _public member_ `TUniqueFunction<double(const double&)> ScaleConstraintFunction = [](const double& DeltaScale) { return DeltaScale; };` — Optional scale constraint function. Called during interaction with the scale delta To snap the scale delta, return the snapped value @return The snapped value of the scale delta
- L341 _public function_ `virtual FVector2D GetParameter() const override`
- L346 _public prototype_ `virtual void SetParameter(const FVector2D& NewValue) override;`
- L348 _public prototype_ `virtual void BeginModify() override;`
- L349 _public prototype_ `virtual void EndModify() override;`
- L355 _public member_ `TScriptInterface<IGizmoAxisSource> AxisSource;` — `UPROPERTY()` — AxisSource provides the 3D plane (origin/normal/u/v) that is used to interpret the 2D parameters
- L359 _public member_ `TScriptInterface<IGizmoTransformSource> TransformSource;` — `UPROPERTY()` — This TransformSource is updated by applying the constructed 3D translation
- L363 _public member_ `float ScaleMultiplier = 0.02f;` — `UPROPERTY()` — Coordinate delta is multiplied by this amount
- L368 _public member_ `FVector2D Parameter = FVector2D::ZeroVector;` — `UPROPERTY()` — Parameter is the two line-equation parameters that this Vec2ParameterSource provides
- L372 _public member_ `FGizmoVec2ParameterChange LastChange;` — `UPROPERTY()` — Active parameter change (only valid between BeginModify/EndModify)
- L376 _public member_ `FVector CurScaleOrigin;` — `UPROPERTY()` — plane origin for current parameter edit (only valid between BeginModify/EndModify)
- L380 _public member_ `FVector CurScaleNormal;` — `UPROPERTY()` — plane normal for current parameter edit (only valid between BeginModify/EndModify)
- L384 _public member_ `FVector CurScaleAxisX;` — `UPROPERTY()` — in-plane axis X for current parameter edit (only valid between BeginModify/EndModify)
- L388 _public member_ `FVector CurScaleAxisY;` — `UPROPERTY()` — in-plane axis Y for current parameter edit (only valid between BeginModify/EndModify)
- L392 _public member_ `FTransform InitialTransform;` — `UPROPERTY()` — Saved copy of Initial Transform for current parameter edit (only valid between BeginModify/EndModify)
- L399 _public function_ `static UGizmoUniformScaleParameterSource* Construct( IGizmoAxisSource* AxisSourceIn, IGizmoTransformSource* TransformSourceIn, UObject* Outer = (UObject*)GetTransientPackage())` — Create a standard instance of this ParameterSource, with the given AxisSource and TransformSource

#### class `UGizmoAxisScaleParameterSource`  
`class UGizmoAxisScaleParameterSource : public UGizmoBaseFloatParameterSource`  
_L423-504_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGizmoBaseFloatParameterSource`
- desc: UGizmoAxisScaleParameterSource is an IGizmoFloatParameterSource implementation that interprets the float value as the parameter of a line equation, and maps this parameter to a scale factor along a line with origin/direction given by an IGizmoAxisSource. This scale is applied to an IGizmoTransformSource. This ParameterSource is intended to be used to create 3D Axis Scale Gizmos.
- L433 _public function_ `TUniqueFunction<bool(const double& ScaleAxisDelta, double& SnappedScaleAxisDelta)> ScaleAxisDeltaConstraintFunction = [](const double&, double&)` — Optional scale axis delta constraint function. This can be used to snap/constrain the "scale delta" value, for example to snap it to fixed increments along the axis. @return true if constrained delta was found and should be used, false to ignore
- L433 _public member_ `TUniqueFunction<bool(const double& ScaleAxisDelta, double& SnappedScaleAxisDelta)> ScaleAxisDeltaConstraintFunction = [](const double&, double&) { return false; };` — Optional scale axis delta constraint function. This can be used to snap/constrain the "scale delta" value, for example to snap it to fixed increments along the axis. @return true if constrained delta was found and should be used, false to ignore
- L439 _public function_ `TUniqueFunction<double(const double&)> ScaleConstraintFunction = [](const double& DeltaScale)` — Optional scale constraint function. Called during interaction with the scale delta To snap the scale delta, return the snapped value @return The snapped value of the scale delta
- L439 _public member_ `TUniqueFunction<double(const double&)> ScaleConstraintFunction = [](const double& DeltaScale) { return DeltaScale; };` — Optional scale constraint function. Called during interaction with the scale delta To snap the scale delta, return the snapped value @return The snapped value of the scale delta
- L441 _public function_ `virtual float GetParameter() const override`
- L446 _public prototype_ `virtual void SetParameter(float NewValue) override;`
- L448 _public prototype_ `virtual void BeginModify() override;`
- L449 _public prototype_ `virtual void EndModify() override;`
- L454 _public member_ `TScriptInterface<IGizmoAxisSource> AxisSource;` — `UPROPERTY()` — The Parameter line-equation value is converted to a 3D Translation along this Axis
- L458 _public member_ `TScriptInterface<IGizmoTransformSource> TransformSource;` — `UPROPERTY()` — This TransformSource is updated by applying the constructed 3D rotation
- L462 _public member_ `float ScaleMultiplier = 0.02f;` — `UPROPERTY()` — Coordinate delta is multiplied by this amount
- L466 _public member_ `bool bClampToZero = false;` — `UPROPERTY()` — If true, the minimal output scale will be zero.
- L471 _public member_ `float Parameter = 0.0f;` — `UPROPERTY()` — Parameter is the line-equation parameter that this FloatParameterSource provides
- L475 _public member_ `FGizmoFloatParameterChange LastChange;` — `UPROPERTY()` — Active parameter change (only valid between BeginModify/EndModify)
- L479 _public member_ `FVector CurScaleAxis;` — `UPROPERTY()` — scale axis for current parameter edit (only valid between BeginModify/EndModify)
- L483 _public member_ `FVector CurScaleOrigin;` — `UPROPERTY()` — scale origin for current parameter edit (only valid between BeginModify/EndModify)
- L487 _public member_ `FTransform InitialTransform;` — `UPROPERTY()` — Saved copy of Initial transform for current parameter edit (only valid between BeginModify/EndModify)
- L494 _public function_ `static UGizmoAxisScaleParameterSource* Construct( IGizmoAxisSource* AxisSourceIn, IGizmoTransformSource* TransformSourceIn, UObject* Outer = (UObject*)GetTransientPackage())` — Create a standard instance of this ParameterSource, with the given AxisSource and TransformSource

#### class `UGizmoPlaneScaleParameterSource`  
`class UGizmoPlaneScaleParameterSource : public UGizmoBaseVec2ParameterSource`  
_L521-625_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGizmoBaseVec2ParameterSource`
- desc: UGizmoPlaneScaleParameterSource  is an UGizmoBaseVec2ParameterSource implementation that maps a 2D parameter delta to a change in a 3D scaling vector, based on the tangent axes of a 3D plane This scale is applied to an IGizmoTransformSource. This ParameterSource is intended to be used to create 3D Plane Scale Gizmos.
- L532 _public function_ `TUniqueFunction<bool(const FVector&, FVector&)> PositionConstraintFunction = [](const FVector&, FVector&)` — Optional position constraint function. Called during interaction with the new transform origin. To snap the transform to a new position, return as second value, and return true from your lambda. Note that returned snap point will be projected onto the current translation origin/axis. @return true if constraint point was found and should be used, false to ignore
- L532 _public member_ `TUniqueFunction<bool(const FVector&, FVector&)> PositionConstraintFunction = [](const FVector&, FVector&) { return false; };` — Optional position constraint function. Called during interaction with the new transform origin. To snap the transform to a new position, return as second value, and return true from your lambda. Note that returned snap point will be projected onto the current translation origin/axis. @return true if constraint point was found and should be used, false to ignore
- L540 _public function_ `TUniqueFunction<bool(double ScaleAxisDelta, double& SnappedScaleAxisDelta)> ScaleAxisXDeltaConstraintFunction = [](double, double&)` — Optional scale axis delta constraint function. This can be used to snap/constrain the "scale delta" value, for example to snap it to fixed increments along the axis. The Axis[X/Y]DeltaConstraintFunctions are used separately for the X and Y axes of the scale translation @return true if constrained delta was found and should be used, false to ignore
- L540 _public member_ `TUniqueFunction<bool(double ScaleAxisDelta, double& SnappedScaleAxisDelta)> ScaleAxisXDeltaConstraintFunction = [](double, double&) { return false; };` — Optional scale axis delta constraint function. This can be used to snap/constrain the "scale delta" value, for example to snap it to fixed increments along the axis. The Axis[X/Y]DeltaConstraintFunctions are used separately for the X and Y axes of the scale translation @return true if constrained delta was found and should be used, false to ignore
- L541 _public function_ `TUniqueFunction<bool(double ScaleAxisDelta, double& SnappedScaleAxisDelta)> ScaleAxisYDeltaConstraintFunction = [](double, double&)`
- L541 _public member_ `TUniqueFunction<bool(double ScaleAxisDelta, double& SnappedScaleAxisDelta)> ScaleAxisYDeltaConstraintFunction = [](double, double&) { return false; };`
- L547 _public function_ `TUniqueFunction<FVector2D(const FVector2D&)> ScaleConstraintFunction = [](const FVector2D& DeltaScale)` — Optional scale constraint function. Called during interaction with the scale delta To snap the scale delta, return the snapped value @return The snapped value of the scale delta as a FVector2D containing the snapped values for the X and Y axes of the scale translation
- L547 _public member_ `TUniqueFunction<FVector2D(const FVector2D&)> ScaleConstraintFunction = [](const FVector2D& DeltaScale) { return DeltaScale; };` — Optional scale constraint function. Called during interaction with the scale delta To snap the scale delta, return the snapped value @return The snapped value of the scale delta as a FVector2D containing the snapped values for the X and Y axes of the scale translation
- L550 _public function_ `virtual FVector2D GetParameter() const override`
- L555 _public prototype_ `virtual void SetParameter(const FVector2D& NewValue) override;`
- L557 _public prototype_ `virtual void BeginModify() override;`
- L558 _public prototype_ `virtual void EndModify() override;`
- L564 _public member_ `TScriptInterface<IGizmoAxisSource> AxisSource;` — `UPROPERTY()` — AxisSource provides the 3D plane (origin/normal/u/v) that is used to interpret the 2D parameters
- L568 _public member_ `TScriptInterface<IGizmoTransformSource> TransformSource;` — `UPROPERTY()` — This TransformSource is updated by applying the constructed 3D translation
- L572 _public member_ `float ScaleMultiplier = 0.02f;` — `UPROPERTY()` — Coordinate delta is multiplied by this amount
- L576 _public member_ `bool bUseEqualScaling = false;` — `UPROPERTY()` — If true, the scaling will be done an equal amount in each axis, using the minimal value
- L580 _public member_ `bool bClampToZero = false;` — `UPROPERTY()` — If true, the minimal output scale will be zero.
- L584 _public member_ `FVector2D Parameter = FVector2D::ZeroVector;` — `UPROPERTY()` — Parameter is the two line-equation parameters that this Vec2ParameterSource provides
- L588 _public member_ `FGizmoVec2ParameterChange LastChange;` — `UPROPERTY()` — Active parameter change (only valid between BeginModify/EndModify)
- L592 _public member_ `FVector CurScaleOrigin;` — `UPROPERTY()` — plane origin for current parameter edit (only valid between BeginModify/EndModify)
- L596 _public member_ `FVector CurScaleNormal;` — `UPROPERTY()` — plane normal for current parameter edit (only valid between BeginModify/EndModify)
- L600 _public member_ `FVector CurScaleAxisX;` — `UPROPERTY()` — in-plane axis X for current parameter edit (only valid between BeginModify/EndModify)
- L604 _public member_ `FVector CurScaleAxisY;` — `UPROPERTY()` — in-plane axis Y for current parameter edit (only valid between BeginModify/EndModify)
- L608 _public member_ `FTransform InitialTransform;` — `UPROPERTY()` — Saved copy of Initial Transform for current parameter edit (only valid between BeginModify/EndModify)
- L615 _public function_ `static UGizmoPlaneScaleParameterSource* Construct( IGizmoAxisSource* AxisSourceIn, IGizmoTransformSource* TransformSourceIn, UObject* Outer = (UObject*)GetTransientPackage())` — Create a standard instance of this ParameterSource, with the given AxisSource and TransformSource

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/PlanePositionGizmo.h` (Public)


#### class `UPlanePositionGizmoBuilder`  
`class UPlanePositionGizmoBuilder : public UInteractiveGizmoBuilder`  
_L37-43_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveGizmoBuilder`
- L42 _public prototype_ `virtual UInteractiveGizmo* BuildGizmo(const FToolBuilderState& SceneState) const override;`

#### class `UPlanePositionGizmo`  
`class UPlanePositionGizmo : public UInteractiveGizmo, public IClickDragBehaviorTarget, public IHoverBehaviorTarget`  
_L64-228_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveGizmo,IClickDragBehaviorTarget,IHoverBehaviorTarget`
- desc: UPlanePositionGizmo implements a gizmo interaction where 2D parameter value is manipulated by dragging a point on a 3D plane in space. The 3D position is converted to 2D coordinates based on the tangent axes of the plane. As with other base gizmos, this class only implements the interaction. The visual aspect of the gizmo, the plane, and the parameter storage are all provided externally. The plane is provided by an IGizmoAxisSource. The origin and normal define the plane and then the tangent axes of the source define the coordinate space. The interaction target (ie the thing you have to click on to start the dragging interaction) is provided by an IGizmoClickTarget. The new 2D parameter value is sent to an IGizmoVec2ParameterSource Internally a UClickDragInputBehavior is used to handle mouse input, configured in ::Setup()
- L73 _public prototype_ `bool InitializeAsTranslateGizmo( const UE::GizmoUtil::FTransformSubGizmoCommonParams& InitializationParams, UE::GizmoUtil::FTransformSubGizmoSharedState* SharedState);` — Helper that initializes AxisSource, ParameterSource, HitTarget, and StateTarget for the common case of being used to control the translation of a transform. Safe to use for reinitialization.
- L81 _public prototype_ `bool InitializeAsScaleGizmo( const UE::GizmoUtil::FTransformSubGizmoCommonParams& InitializationParams, bool bDisallowNegativeScaling, UE::GizmoUtil::FTransformSubGizmoSharedState* SharedState);` — Helper that initializes AxisSource, ParameterSource, HitTarget, and StateTarget for the common case of being used to control the scale of a transform. Safe to use for reinitialization.
- L94 _public prototype_ `bool InitializeAsUniformScaleGizmo( const UE::GizmoUtil::FTransformSubGizmoCommonParams& Params, bool bDisallowNegativeScaling, UE::GizmoUtil::FTransformSubGizmoSharedState* SharedState);` — Helper that initializes AxisSource, ParameterSource, HitTarget, and StateTarget for the common case of being used to control the uniform scale of a transform, where the interaction plane remains aligned to the camera. Safe to use for reinitialization. Note: if SharedState contains a CameraAxisSource, this subgizmo will use it and will assume that something else is responsible for updating it. Otherwise this subgizmo will set the CameraAxisSource and update it in its own Tick function.
- L101 _public prototype_ `virtual void Setup() override;`
- L102 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L106 _public prototype_ `virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& PressPos) override;`
- L107 _public prototype_ `virtual void OnClickPress(const FInputDeviceRay& PressPos) override;`
- L108 _public prototype_ `virtual void OnClickDrag(const FInputDeviceRay& DragPos) override;`
- L109 _public prototype_ `virtual void OnClickRelease(const FInputDeviceRay& ReleasePos) override;`
- L110 _public prototype_ `virtual void OnTerminateDragSequence() override;`
- L113 _public prototype_ `virtual FInputRayHit BeginHoverSequenceHitTest(const FInputDeviceRay& PressPos) override;` — IHoverBehaviorTarget implementation
- L114 _public prototype_ `virtual void OnBeginHover(const FInputDeviceRay& DevicePos) override;`
- L115 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) override;`
- L116 _public prototype_ `virtual void OnEndHover() override;`
- L124 _public member_ `TScriptInterface<IGizmoAxisSource> AxisSource;` — `UPROPERTY()` — AxisSource provides the 3D plane on which the interaction happens
- L128 _public member_ `TScriptInterface<IGizmoVec2ParameterSource> ParameterSource;` — `UPROPERTY()` — The 3D plane coordinates are converted to 2D coordinates in the plane tangent space, and the change in value is sent to this ParameterSource
- L132 _public member_ `TScriptInterface<IGizmoClickTarget> HitTarget;` — `UPROPERTY()` — The HitTarget provides a hit-test against some 3D element (presumably a visual widget) that controls when interaction can start
- L136 _public member_ `TScriptInterface<IGizmoStateTarget> StateTarget;` — `UPROPERTY()` — StateTarget is notified when interaction starts and ends, so that things like undo/redo can be handled externally
- L140 _public member_ `TObjectPtr<UClickDragInputBehavior> MouseBehavior;` — `UPROPERTY()` — The mouse click behavior of the gizmo is accessible so that it can be modified to use different mouse keys.
- L145 _public member_ `bool bEnableSignedAxis = false;` — `UPROPERTY()` — If enabled, then the sign on the parameter delta is always "increasing" when moving away from the origin point, rather than just being a projection onto the axis
- L149 _public member_ `bool bFlipX = false;` — `UPROPERTY()` — If enabled, flip sign of parameter delta on X axis
- L153 _public member_ `bool bFlipY = false;` — `UPROPERTY()` — If enabled, flip sign of parameter delta on Y axis
- L159 _public function_ `TUniqueFunction<bool()> ShouldUseCustomDestinationFunc = []()` — This gets checked to see if we should use the custom ray caster to get a destination point for the gizmo, rather than grabbing the intersection with the gizmo plane.
- L159 _public member_ `TUniqueFunction<bool()> ShouldUseCustomDestinationFunc = []() {return false; };` — This gets checked to see if we should use the custom ray caster to get a destination point for the gizmo, rather than grabbing the intersection with the gizmo plane.
- L176 _public member_ `TUniqueFunction<bool(const FCustomDestinationParams& WorldRay, FVector& OutputPoint)> CustomDestinationFunc = [](const FCustomDestinationParams& Params, FVector& OutputPoint) { return false; };` — If ShouldUseCustomDestinationFunc() returns true, this function is used to get a destination point, and the output parameters are picked in such a way that the axis origin moves to the closest point in the plane to the destination point. Used, for instance, for aligning to items in the scene.
- L177 _public function_ `[](const FCustomDestinationParams& Params, FVector& OutputPoint)`
- L182 _public member_ `bool bInInteraction = false;` — `UPROPERTY()` — If true, we are in an active click+drag interaction, otherwise we are not
- L191 _public member_ `FVector InteractionOrigin;` — `UPROPERTY()`
- L194 _public member_ `FVector InteractionNormal;` — `UPROPERTY()`
- L197 _public member_ `FVector InteractionAxisX;` — `UPROPERTY()`
- L200 _public member_ `FVector InteractionAxisY;` — `UPROPERTY()`
- L204 _public member_ `FVector InteractionStartPoint;` — `UPROPERTY()`
- L207 _public member_ `FVector InteractionCurPoint;` — `UPROPERTY()`
- L210 _public member_ `FVector2D InteractionStartParameter;` — `UPROPERTY()`
- L213 _public member_ `FVector2D InteractionCurParameter;` — `UPROPERTY()`
- L216 _public member_ `FVector2D ParameterSigns = FVector2D(1, 1);` — `UPROPERTY()`
- L219 _protected member_ `FVector LastHitPosition;`
- L220 _protected member_ `FVector2D InitialTargetParameter;`
- L222 _protected member_ `FVector2D InteractionStartOriginParameterOffset;`
- L223 _protected member_ `FInputDeviceRay LastInputRay = FInputDeviceRay(FRay());`
- L227 _protected member_ `TUniqueFunction<void(float DeltaTime)> CustomTickFunction;` — Helper that can hold some extra upkeep to do during Tick (used to update a camera axis source if needed).

#### struct `UPlanePositionGizmo::FCustomDestinationParams`  
`struct FCustomDestinationParams`  
_L161-168_
- L167 _public member_ `const FRay* WorldRay = nullptr;` — Right now we use the custom destination function for aligning to items in the scene, which we just need the world ray for. If we want to use functions that use other inputs as the basis for the destination, we would add those parameters here and would make sure that the gizmo passes them in.

#### Free symbols / members of external scopes

- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace GizmoUtil` (scope `UE`)

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/RepositionableTransformGizmo.h` (Public)


#### class `URepositionableTransformGizmoBuilder`  
`class URepositionableTransformGizmoBuilder : public UCombinedTransformGizmoBuilder`  
_L17-24_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCombinedTransformGizmoBuilder`
- L23 _public prototype_ `virtual UInteractiveGizmo* BuildGizmo(const FToolBuilderState& SceneState) const override;`

#### class `URepositionableTransformGizmo`  
`class URepositionableTransformGizmo : public UCombinedTransformGizmo`  
_L31-78_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCombinedTransformGizmo`
- desc: A transform gizmo that also allows the user to reposition it by middle-clicking rotation/translation components.
- L42 _public prototype_ `virtual void SetActiveTarget(UTransformProxy* Target, IToolContextTransactionProvider* TransactionProvider = nullptr) override;` — Set the active target object for the Gizmo @param Target active target @param TransactionProvider optional IToolContextTransactionProvider implementation to use - by default uses GizmoManager
- L48 _public prototype_ `virtual void SetWorldAlignmentFunctions( TUniqueFunction<bool()>&& ShouldAlignTranslationIn, TUniqueFunction<bool(const FRay&, FVector&)>&& TranslationAlignmentRayCasterIn) override;` — Allows the user to provide functions to use for aligning the gizmo destination to items in the scene. Note that this affects both the movement and repositioning.
- L57 _public prototype_ `virtual void SetPivotAlignmentFunctions( TUniqueFunction<bool()>&& ShouldAlignPivotIn, TUniqueFunction<bool(const FRay&, FVector&)>&& PivotAlignmentRayCasterIn);` — Allows the user to provide functions to use in aligning the gizmo during repositioning only. This is because the repositining is likely to want different raycasts that don't ignore the moved components themselves, so that the gizmo can be aligned to a target component.
- L62 _protected function_ `TUniqueFunction<bool()> ShouldAlignPivot = []()`
- L62 _protected member_ `TUniqueFunction<bool()> ShouldAlignPivot = []() { return false; };`
- L63 _protected function_ `TUniqueFunction<bool(const FRay&, FVector&)> PivotAlignmentRayCaster = [](const FRay&, FVector&)`
- L63 _protected member_ `TUniqueFunction<bool(const FRay&, FVector&)> PivotAlignmentRayCaster = [](const FRay&, FVector&) {return false; };`
- L66 _protected member_ `TArray<UInteractiveGizmo*> PivotAlignmentGizmos;` — Subset of ActiveGizmos, for use by SetPivotAlignmentFunctions
- L69 _protected member_ `TObjectPtr<UGizmoTransformChangeStateTarget> RepositionStateTarget;` — `UPROPERTY()`
- L72 _protected prototype_ `void ModifyPivotAxisGizmo(UInteractiveGizmo* SubGizmoIn);` — Helper functions
- L73 _protected prototype_ `void ModifyPivotPlaneGizmo(UInteractiveGizmo* SubGizmoIn);`
- L74 _protected prototype_ `void ModifyPivotRotateGizmo(UInteractiveGizmo* SubGizmoIn);`
- L76 _private prototype_ `void ModifyPivotFreeTranslationGizmo(UInteractiveGizmo* SubGizmoIn);`
- L77 _private prototype_ `void ModifyPivotFreeRotationGizmo(UInteractiveGizmo* SubGizmoIn);`

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/ScalableSphereGizmo.h` (Public)


#### class `UScalableSphereGizmoBuilder`  
`class UScalableSphereGizmoBuilder : public UInteractiveGizmoBuilder`  
_L15-21_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveGizmoBuilder`
- L20 _public prototype_ `virtual UInteractiveGizmo* BuildGizmo(const FToolBuilderState& SceneState) const override;`

#### class `UScalableSphereGizmo`  
`class UScalableSphereGizmo : public UInteractiveGizmo, public IHoverBehaviorTarget`  
_L28-104_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveGizmo,IHoverBehaviorTarget`
- desc: UScalableSphereGizmo provides a sphere that can be scaled in all directions by dragging anywhere on the three axial circles that represent it
- L34 _public prototype_ `virtual void Setup() override;` — UInteractiveGizmo interface
- L35 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L38 _public prototype_ `virtual FInputRayHit BeginHoverSequenceHitTest(const FInputDeviceRay& PressPos) override;` — IHoverBehaviorTarget interface
- L39 _public function_ `virtual void OnBeginHover(const FInputDeviceRay& DevicePos) override`
- L40 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos);`
- L41 _public prototype_ `virtual void OnEndHover();`
- L46 _public prototype_ `virtual void SetTarget(UTransformProxy* InTarget);` — Set the Target to which the gizmo will be attached
- L48 _public prototype_ `virtual void OnBeginDrag(const FInputDeviceRay& Ray);`
- L49 _public prototype_ `virtual void OnUpdateDrag(const FInputDeviceRay& Ray);`
- L50 _public prototype_ `virtual void OnEndDrag(const FInputDeviceRay& Ray);`
- L53 _public prototype_ `bool HitTest(const FRay& Ray, FHitResult& OutHit, FVector& OutAxis, FTransform& OutTransform);` — Check if the input Ray hit any of the components of the internal actor
- L56 _public prototype_ `void SetRadius(float InRadius);` — Set the Radius of the Sphere
- L59 _public member_ `TFunction<void(const float)> UpdateRadiusFunc = nullptr;` — Called when the radius is chaged (by dragging or setting). Sends new radius as parameter.
- L63 _public member_ `float HitErrorThreshold{ 12.f };` — `UPROPERTY()` — The error threshold for hit detection with the sphere
- L67 _public member_ `FText TransactionDescription;` — `UPROPERTY()` — The text that will be used as the transaction description for undo/redo
- L72 _private prototype_ `bool CheckCircleIntersection(const FRay& Ray, FVector CircleNormal, FVector& OutHitLocation, FVector& OutHitAxis);` — Check if the Circle represented by CircleNormal centered at the gizmos location has been hit by the Ray
- L76 _private member_ `float Radius;` — `UPROPERTY()` — The radius of the sphere
- L80 _private member_ `bool bIsHovering{ false };` — `UPROPERTY()` — Whether the sphere is currently being hovered over
- L84 _private member_ `bool bIsDragging{ false };` — `UPROPERTY()` — Whether the sphere is currently being dragged
- L87 _private member_ `TObjectPtr<UTransformProxy> ActiveTarget;` — `UPROPERTY()`
- L91 _private member_ `FVector ActiveAxis;` — `UPROPERTY()` — The current axis that is being dragged along
- L95 _private member_ `FVector DragStartWorldPosition;` — `UPROPERTY()` — The position the drag was started on
- L99 _private member_ `FVector DragCurrentPositionProjected;` — `UPROPERTY()` — The position the drag is on currently (projected onto the line it is being dragged along)
- L103 _private member_ `float InteractionStartParameter;` — `UPROPERTY()` — The initial parameter along the drag axist

#### class `UScalableSphereGizmoInputBehavior`  
`class UScalableSphereGizmoInputBehavior : public UAnyButtonInputBehavior`  
_L111-130_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnyButtonInputBehavior`
- desc: A behavior that forwards clicking and dragging to the gizmo.
- L116 _public function_ `virtual FInputCapturePriority GetPriority() override`
- L118 _public prototype_ `virtual void Initialize(UScalableSphereGizmo* Gizmo);`
- L120 _public prototype_ `virtual FInputCaptureRequest WantsCapture(const FInputDeviceState& input) override;`
- L121 _public prototype_ `virtual FInputCaptureUpdate BeginCapture(const FInputDeviceState& input, EInputCaptureSide eSide) override;`
- L122 _public prototype_ `virtual FInputCaptureUpdate UpdateCapture(const FInputDeviceState& input, const FInputCaptureData& data) override;`
- L123 _public prototype_ `virtual void ForceEndCapture(const FInputCaptureData& data) override;`
- L126 _protected member_ `UScalableSphereGizmo* Gizmo;`
- L127 _protected member_ `FRay LastWorldRay;`
- L128 _protected member_ `FVector2D LastScreenPosition;`
- L129 _protected member_ `bool bInputDragCaptured;`

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/SimpleSingleClickGizmo.h` (Public)


#### class `USimpleSingleClickGizmo`  
`class USimpleSingleClickGizmo : public UInteractiveGizmo, public IClickBehaviorTarget, public IHoverBehaviorTarget`  
_L18-52_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveGizmo,IClickBehaviorTarget,IHoverBehaviorTarget`
- desc: Simple gizmo that triggers an OnClicked callback when it is clicked.
- L24 _public prototype_ `bool InitializeWithComponent(UPrimitiveComponent* ComponentIn);`
- L27 _public prototype_ `virtual void Setup() override;` — UInteractiveGizmo
- L30 _public prototype_ `virtual FInputRayHit IsHitByClick(const FInputDeviceRay& ClickPos) override;` — IClickBehaviorTarget
- L31 _public prototype_ `virtual void OnClicked(const FInputDeviceRay& ClickPos) override;`
- L34 _public prototype_ `virtual FInputRayHit BeginHoverSequenceHitTest(const FInputDeviceRay& PressPos) override;` — IHoverBehaviorTarget
- L35 _public prototype_ `virtual void OnBeginHover(const FInputDeviceRay& DevicePos) override;`
- L36 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) override;`
- L37 _public prototype_ `virtual void OnEndHover() override;`
- L41 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnClick, USimpleSingleClickGizmo&, const FInputDeviceRay&);`
- L42 _public member_ `FOnClick OnClick;`
- L46 _public member_ `TScriptInterface<IGizmoClickTarget> HitTarget;` — `UPROPERTY()` — The HitTarget provides a hit-test against some 3D element (presumably a visual widget) that controls when interaction can start
- L50 _public member_ `TObjectPtr<USingleClickInputBehavior> ClickBehavior;` — `UPROPERTY()` — The mouse click behavior of the gizmo is accessible so that it can be modified to use different mouse keys.

#### Free symbols / members of external scopes

- L41 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnClick, USimpleSingleClickGizmo&, const FInputDeviceRay&);`

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/StateTargets.h` (Public)


#### class `UGizmoNilStateTarget`  
`class UGizmoNilStateTarget : public UObject, public IGizmoStateTarget`  
_L34-49_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,IGizmoStateTarget`
- desc: UGizmoNilStateTarget is an implementation of IGizmoStateTarget that does nothing
- L38 _public function_ `virtual void BeginUpdate() final`
- L42 _public function_ `virtual void EndUpdate() final`
- L46 _public function_ `virtual void CancelUpdate() final`

#### class `UGizmoLambdaStateTarget`  
`class UGizmoLambdaStateTarget : public UObject, public IGizmoStateTarget`  
_L58-89_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,IGizmoStateTarget`
- desc: UGizmoLambdaStateTarget is an implementation of IGizmoStateTarget that forwards calls to its interface functions to external TFunctions
- L62 _public function_ `virtual void BeginUpdate()`
- L70 _public function_ `virtual void EndUpdate()`
- L78 _public function_ `virtual void CancelUpdate()`
- L86 _public member_ `TUniqueFunction<void(void)> BeginUpdateFunction = TUniqueFunction<void(void)>();`
- L87 _public member_ `TUniqueFunction<void(void)> EndUpdateFunction = TUniqueFunction<void(void)>();`
- L88 _public member_ `TUniqueFunction<void(void)> CancelUpdateFunction = TUniqueFunction<void(void)>();`

#### class `UGizmoObjectModifyStateTarget`  
`class UGizmoObjectModifyStateTarget : public UObject, public IGizmoStateTarget`  
_L98-170_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,IGizmoStateTarget`
- desc: UGizmoObjectModifyStateTarget is an implementation of IGizmoStateTarget that opens and closes change transactions on a target UObject via a GizmoManager.
- L102 _public function_ `virtual void BeginUpdate()`
- L114 _public function_ `virtual void EndUpdate()`
- L122 _public function_ `virtual void CancelUpdate() override`
- L134 _public member_ `TWeakObjectPtr<UObject> ModifyObject;` — The object that will be changed, ie have Modify() called on it on BeginUpdate()
- L139 _public member_ `FText TransactionDescription;` — Localized text description of the transaction (will be visible in Editor on undo/redo)
- L145 _public member_ `TScriptInterface<IToolContextTransactionProvider> TransactionManager;` — `UPROPERTY()` — Pointer to the GizmoManager or ToolManager that is used to open/close the transaction
- L154 _public function_ `static UGizmoObjectModifyStateTarget* Construct( UObject* ModifyObjectIn, const FText& DescriptionIn, IToolContextTransactionProvider* TransactionManagerIn, UObject* Outer = (UObject*)GetTransientPackage())` — Create and initialize an standard instance of UGizmoObjectModifyStateTarget @param ModifyObjectIn the object this StateTarget will call Modify() on @param DescriptionIn Localized text description of the transaction @param GizmoManagerIn pointer to the GizmoManager used to manage transactions

#### class `UGizmoTransformChangeStateTarget`  
`class UGizmoTransformChangeStateTarget : public UObject, public IGizmoStateTarget`  
_L187-331_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,IGizmoStateTarget`
- desc: UGizmoTransformChangeStateTarget is an implementation of IGizmoStateTarget that emits an FComponentWorldTransformChange on a target USceneComponent. This StateTarget also opens/closes an undo transaction via GizmoManager. The DependentChangeSources and ExternalDependentChangeSources lists allow additional FChange objects to be inserted into the transaction, provided by IToolCommandChangeSource implementations.
- L191 _public function_ `virtual void BeginUpdate()`
- L214 _public function_ `virtual void EndUpdate()`
- L251 _public function_ `virtual void CancelUpdate() override`
- L275 _public member_ `TWeakObjectPtr<USceneComponent> TargetComponent;` — The object that will be changed, ie have Modify() called on it on BeginUpdate()
- L280 _public member_ `FText ChangeDescription;` — Localized text description of the transaction (will be visible in Editor on undo/redo)
- L286 _public member_ `TScriptInterface<IToolContextTransactionProvider> TransactionManager;` — `UPROPERTY()` — Pointer to the GizmoManager or ToolManager that is used to open/close the transaction
- L289 _public member_ `FTransform InitialTransform;` — Start Transform, saved on BeginUpdate()
- L291 _public member_ `FTransform FinalTransform;` — End Transform, saved on EndUpdate()
- L298 _public member_ `TArray<TUniquePtr<IToolCommandChangeSource>> DependentChangeSources;` — Dependent-change generators. This will be told about update start/end, and any generated changes will also be emitted. This allows (eg) TransformProxy change events to be collected at the same time as changes to a gizmo target component.
- L303 _public member_ `TArray<IToolCommandChangeSource*> ExternalDependentChangeSources;` — Dependent-change generators that are not owned by this class, otherwise handled identically to DependentChangeSources
- L313 _public function_ `static UGizmoTransformChangeStateTarget* Construct( USceneComponent* TargetComponentIn, const FText& DescriptionIn, IToolContextTransactionProvider* TransactionManagerIn, UObject* Outer = (UObject*)GetTransientPackage())` — Create and initialize an standard instance of UGizmoTransformChangeStateTarget @param TargetComponentIn the USceneComponent this StateTarget will track transform changes on @param DescriptionIn Localized text description of the transaction @param TransactionManagerIn pointer to the GizmoManager or ToolManager used to manage transactions

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/TransformGizmoUtil.h` (Public)


#### class `UCombinedTransformGizmoContextObject`  
`class UCombinedTransformGizmoContextObject : public UObject`  
_L88-134_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UObject`
- desc: UCombinedTransformGizmoContextObject is a utility object that registers a set of Gizmo Builders for UCombinedTransformGizmo and variants. The intended usage is to call RegisterGizmosWithManager(), and then the UCombinedTransformGizmoContextObject will register itself as a ContextObject in the InteractiveToolsContext's ContextObjectStore. Then the Create3AxisTransformGizmo()/etc functions will spawn different variants of UCombinedTransformGizmo. The above UE::TransformGizmoUtil:: functions will look up the UCombinedTransformGizmoContextObject instance in the ContextObjectStore and then call the associated function below.
- L95 _public member_ `static const FString DefaultAxisPositionBuilderIdentifier;` — builder identifiers for default gizmo types. Perhaps should have an API for this...
- L96 _public member_ `static const FString DefaultPlanePositionBuilderIdentifier;`
- L97 _public member_ `static const FString DefaultAxisAngleBuilderIdentifier;`
- L98 _public member_ `static const FString DefaultThreeAxisTransformBuilderIdentifier;`
- L99 _public member_ `static const FString CustomThreeAxisTransformBuilderIdentifier;`
- L100 _public member_ `static const FString CustomRepositionableThreeAxisTransformBuilderIdentifier;`
- L102 _public prototype_ `void RegisterGizmosWithManager(UInteractiveToolManager* ToolManager);`
- L103 _public prototype_ `void DeregisterGizmosWithManager(UInteractiveToolManager* ToolManager);`
- L111 _public prototype_ `virtual UCombinedTransformGizmo* Create3AxisTransformGizmo(UInteractiveGizmoManager* GizmoManager, void* Owner = nullptr, const FString& InstanceIdentifier = FString());` — Activate a new instance of the default 3-axis transformation Gizmo. RegisterDefaultGizmos() must have been called first. @param Owner optional void pointer to whatever "owns" this Gizmo. Allows Gizmo to later be deleted using DestroyAllGizmosByOwner() @param InstanceIdentifier optional client-defined *unique* string that can be used to locate this instance @return new Gizmo instance that has been created and initialized
- L120 _public prototype_ `virtual UCombinedTransformGizmo* CreateCustomTransformGizmo(UInteractiveGizmoManager* GizmoManager, ETransformGizmoSubElements Elements, void* Owner = nullptr, const FString& InstanceIdentifier = FString());` — Activate a new customized instance of the default 3-axis transformation Gizmo, with only certain elements included. RegisterDefaultGizmos() must have been called first. @param Elements flags that indicate which standard gizmo sub-elements should be included @param Owner optional void pointer to whatever "owns" this Gizmo. Allows Gizmo to later be deleted using DestroyAllGizmosByOwner() @param InstanceIdentifier optional client-defined *unique* string that can be used to locate this instance @return new Gizmo instance that has been created and initialized
- L126 _public prototype_ `virtual UCombinedTransformGizmo* CreateCustomRepositionableTransformGizmo(UInteractiveGizmoManager* GizmoManager, ETransformGizmoSubElements Elements, void* Owner = nullptr, const FString& InstanceIdentifier = FString());` — Variant of CreateCustomTransformGizmo that creates a URepositionableTransformGizmo, which is an extension to UCombinedTransformGizmo that supports various snapping interactions
- L128 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGizmoCreated, UCombinedTransformGizmo*);`
- L129 _public member_ `FOnGizmoCreated OnGizmoCreated;`
- L132 _protected member_ `TSharedPtr<FCombinedTransformGizmoActorFactory> GizmoActorBuilder;`
- L133 _protected member_ `bool bDefaultGizmosRegistered = false;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L19 _namespace_ `namespace TransformGizmoUtil` (scope `UE`)
- L31 _prototype_ `bool RegisterTransformGizmoContextObject(UInteractiveToolsContext* ToolsContext);` (scope `UE::TransformGizmoUtil`) — If one does not already exist, create a new instance of UCombinedTransformGizmoContextObject and add it to the ToolsContext's ContextObjectStore @return true if the ContextObjectStore now has a UCombinedTransformGizmoContextObject (whether it already existed, or was created)
- L37 _prototype_ `bool DeregisterTransformGizmoContextObject(UInteractiveToolsContext* ToolsContext);` (scope `UE::TransformGizmoUtil`) — Remove any existing UCombinedTransformGizmoContextObject from the ToolsContext's ContextObjectStore @return true if the ContextObjectStore no longer has a UCombinedTransformGizmoContextObject (whether it was removed, or did not exist)
- L44 _prototype_ `UCombinedTransformGizmo* Create3AxisTransformGizmo(UInteractiveGizmoManager* GizmoManager, void* Owner = nullptr, const FString& InstanceIdentifier = FString());` (scope `UE::TransformGizmoUtil`) — Spawn a new standard 3-axis Transform gizmo (see UCombinedTransformGizmoContextObject::Create3AxisTransformGizmo for details) GizmoManager's ToolsContext must have a UCombinedTransformGizmoContextObject registered (see UCombinedTransformGizmoContextObject for details)
- L49 _prototype_ `UCombinedTransformGizmo* Create3AxisTransformGizmo(UInteractiveToolManager* ToolManager, void* Owner = nullptr, const FString& InstanceIdentifier = FString());` (scope `UE::TransformGizmoUtil`) — Spawn a new standard 3-axis Transform gizmo (see UCombinedTransformGizmoContextObject::Create3AxisTransformGizmo for details) ToolManager's ToolsContext must have a UCombinedTransformGizmoContextObject registered (see UCombinedTransformGizmoContextObject for details)
- L56 _prototype_ `UCombinedTransformGizmo* CreateCustomTransformGizmo(UInteractiveGizmoManager* GizmoManager, ETransformGizmoSubElements Elements, void* Owner = nullptr, const FString& InstanceIdentifier = FString());` (scope `UE::TransformGizmoUtil`) — Spawn a new custom Transform gizmo (see UCombinedTransformGizmoContextObject::CreateCustomTransformGizmo for details) GizmoManager's ToolsContext must have a UCombinedTransformGizmoContextObject registered (see UCombinedTransformGizmoContextObject for details)
- L61 _prototype_ `UCombinedTransformGizmo* CreateCustomTransformGizmo(UInteractiveToolManager* ToolManager, ETransformGizmoSubElements Elements, void* Owner = nullptr, const FString& InstanceIdentifier = FString());` (scope `UE::TransformGizmoUtil`) — Spawn a new custom Transform gizmo (see UCombinedTransformGizmoContextObject::CreateCustomTransformGizmo for details) ToolManager's ToolsContext must have a UCombinedTransformGizmoContextObject registered (see UCombinedTransformGizmoContextObject for details)
- L68 _prototype_ `UCombinedTransformGizmo* CreateCustomRepositionableTransformGizmo(UInteractiveGizmoManager* GizmoManager, ETransformGizmoSubElements Elements, void* Owner = nullptr, const FString& InstanceIdentifier = FString());` (scope `UE::TransformGizmoUtil`) — Spawn a new custom Transform gizmo (see UCombinedTransformGizmoContextObject::CreateCustomTransformGizmo for details) GizmoManager's ToolsContext must have a UCombinedTransformGizmoContextObject registered (see UCombinedTransformGizmoContextObject for details)
- L73 _prototype_ `UCombinedTransformGizmo* CreateCustomRepositionableTransformGizmo(UInteractiveToolManager* ToolManager, ETransformGizmoSubElements Elements, void* Owner = nullptr, const FString& InstanceIdentifier = FString());` (scope `UE::TransformGizmoUtil`) — Spawn a new custom Transform gizmo (see UCombinedTransformGizmoContextObject::CreateCustomRepositionableTransformGizmo for details) ToolManager's ToolsContext must have a UCombinedTransformGizmoContextObject registered (see UCombinedTransformGizmoContextObject for details)
- L128 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGizmoCreated, UCombinedTransformGizmo*);`

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/TransformProxy.h` (Public)


#### class `UTransformProxy`  
`class UTransformProxy : public UObject`  
_L39-192_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UObject`
- desc: UTransformProxy is used to transform a set of sub-objects. An internal FTransform is generated based on the sub-object set, and the relative FTransform of each sub-object is stored. Then as this main transform is updated, the sub-objects are also updated. Currently only USceneComponent sub-objects are supported. If only one sub-object is set, the main transform is the sub-object transform. Otherwise the main transform is centered at the average origin and has no rotation.
- L49 _public prototype_ `virtual void AddComponent(USceneComponent* Component, bool bModifyComponentOnTransform = true);` — Add a component sub-object to the proxy set. @param bModifyComponentOnTransform if true, Component->Modify() is called before the Component transform is updated @warning The internal shared transform is regenerated each time a component is added
- L60 _public prototype_ `virtual void AddComponentCustom( USceneComponent* Component, TUniqueFunction<FTransform(void)> GetTransformFunc, TUniqueFunction<void(const FTransform&)> SetTransformFunc, int64 UserDefinedIndex = 0, bool bModifyComponentOnTransform = true);` — Add a component sub-object to the proxy set with custom transform access functions. This can be used to do things like add an ISM Instance to the TransformProxy. @param GetTransformFunc return current transform @param SetTransformFunc set current transform @param UserDefinedIndex an arbitrary integer that can be provided, not currently used but may be useful in subclasses @param bModifyComponentOnTransform if true, Component->Modify() is called before the Component transform is updated @warning The internal shared transform is regenerated each time a component is added
- L71 _public prototype_ `virtual FTransform GetTransform() const;` — @return the shared transform for all the sub-objects
- L76 _public prototype_ `virtual void SetTransform(const FTransform& Transform);` — Update the main transform and then update the sub-objects based on their relative transformations
- L86 _public prototype_ `virtual void BeginTransformEditSequence();` — In some use cases SetTransform() will be called repeatedly (eg during an interactive gizmo edit). External code may know and/or need to know when such a sequence starts/ends. The OnBeginTransformEdit/OnEndTransformEdit delegates can provide these notifications, however client code must call BeginTransformEditSequence()/EndTransformEditSequence() to fire those delegates as the TransformProxy doesn't know about this external state. @note FTransformProxyChangeSource will call these functions on Begin/End
- L91 _public prototype_ `virtual void EndTransformEditSequence();` — External clients should call this when done a sequence of SetTransform calls (see BeginTransformEditSequence)
- L97 _public prototype_ `virtual void BeginPivotEditSequence();` — Clients should call this before a sequence of SetTransform calls that have bSetPivotMode as true (see comment in BeginTransformEditSequence).
- L103 _public prototype_ `virtual void EndPivotEditSequence();` — Clients should call this when done with a sequence of SetTransform that have bSetPivotMode as true (see comment in BeginTransformEditSequence).
- L110 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnTransformChanged, UTransformProxy*, FTransform);` — This delegate is fired whenever the transform changes in a way that updates the contained components. I.e., SetTransform is called with bSetPivotMode being false.
- L111 _public member_ `FOnTransformChanged OnTransformChanged;`
- L117 _public member_ `FOnTransformChanged OnTransformChangedUndoRedo;` — This delegate is fired whenever the transform is changed by a FTransformProxyChange, ie on undo/redo. OnTransformChanged is also fired in those cases, this extra event can be used when undo/redo state changes need to be handled specifically.
- L120 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnBeginTransformEdit, UTransformProxy*);` — This delegate is fired when BeginTransformEditSequence() is called to indicate that a sequence of transform updates has started
- L121 _public member_ `FOnBeginTransformEdit OnBeginTransformEdit;`
- L124 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnEndTransformEdit, UTransformProxy*);` — This delegate is fired when EndTransformEditSequence() is called to indicate that a sequence of transform updates has ended
- L125 _public member_ `FOnEndTransformEdit OnEndTransformEdit;`
- L131 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPivotChanged, UTransformProxy*, FTransform);` — This delegate is fired whenever the internal transform changes due to a pivot reposition, ie on AddComponent and when SetTransform is called with bSetPivotMode being true.
- L132 _public member_ `FOnPivotChanged OnPivotChanged;`
- L135 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnBeginPivotEdit, UTransformProxy*);` — This delegate is fired when BeginTransformEditSequence() is called to indicate that a sequence of pivot updates has started
- L136 _public member_ `FOnBeginPivotEdit OnBeginPivotEdit;`
- L139 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnEndPivotEdit, UTransformProxy*);` — This delegate is fired when EndTransformEditSequence() is called to indicate that a sequence of pivot updates has ended
- L140 _public member_ `FOnEndPivotEdit OnEndPivotEdit;`
- L146 _public member_ `bool bRotatePerObject = false;` — `UPROPERTY()` — If true, relative rotation of shared transform is applied to objects before relative translation (ie they rotate in place)
- L152 _public member_ `bool bSetPivotMode = false;` — `UPROPERTY()` — If true, then on SetTransform() the components are not moved, and their local transforms are recalculated
- L174 _protected member_ `TArray<FRelativeObject> Objects;` — List of sub-objects
- L178 _protected member_ `FTransform SharedTransform;` — `UPROPERTY()` — The main transform
- L182 _protected member_ `FTransform InitialSharedTransform;` — `UPROPERTY()` — The main transform
- L185 _protected prototype_ `virtual void UpdateSharedTransform();` — Recalculate main SharedTransform when object set changes
- L188 _protected prototype_ `virtual void UpdateObjectTransforms();` — Recalculate per-object relative transforms
- L191 _protected prototype_ `virtual void UpdateObjects();` — Propagate a transform update to the sub-objects

#### struct `UTransformProxy::FRelativeObject`  
`struct FRelativeObject`  
_L157-171_
- L159 _public member_ `TWeakObjectPtr<USceneComponent> Component;`
- L160 _public member_ `bool bModifyComponentOnTransform;`
- L162 _public member_ `int64 UserDefinedIndex;` — no current purpose, reserved for subclass/future use
- L164 _public member_ `TUniqueFunction<FTransform(void)> GetTransformFunc;`
- L165 _public member_ `TUniqueFunction<void(const FTransform&)> SetTransformFunc;`
- L168 _public member_ `FTransform StartTransform;` — The initial transform of the object, set during UpdateSharedTransform()
- L170 _public member_ `FTransform RelativeTransform;` — The transform of the object relative to

#### class `FTransformProxyChange`  
`class FTransformProxyChange : public FToolCommandChange`  
_L199-210_
- inherits: `FToolCommandChange`
- desc: FTransformProxyChange tracks a change to the base transform for a TransformProxy
- L202 _public member_ `FTransform From;`
- L203 _public member_ `FTransform To;`
- L204 _public member_ `bool bSetPivotMode = false;`
- L206 _public prototype_ `virtual void Apply(UObject* Object) override;`
- L207 _public prototype_ `virtual void Revert(UObject* Object) override;`
- L209 _public function_ `virtual FString ToString() const override`

#### class `FTransformProxyChangeSource`  
`class FTransformProxyChangeSource : public IToolCommandChangeSource`  
_L216-242_
- inherits: `IToolCommandChangeSource`
- desc: FTransformProxyChangeSource generates FTransformProxyChange instances on Begin/End. Instances of this class can (for example) be attached to a UGizmoTransformChangeStateTarget for use TransformGizmo change tracking.
- L219 _public function_ `FTransformProxyChangeSource(UTransformProxy* ProxyIn)`
- L224 _public prototype_ `virtual ~FTransformProxyChangeSource() = default;`
- L226 _public member_ `TWeakObjectPtr<UTransformProxy> Proxy;`
- L227 _public member_ `TUniquePtr<FTransformProxyChange> ActiveChange;`
- L229 _public prototype_ `virtual void BeginChange() override;`
- L230 _public prototype_ `virtual TUniquePtr<FToolCommandChange> EndChange() override;`
- L231 _public prototype_ `virtual UObject* GetChangeTarget() override;`
- L232 _public prototype_ `virtual FText GetChangeDescription() override;`
- L233 _public prototype_ `virtual void CancelChange() override;`
- L241 _public member_ `bool bOverrideSetPivotMode = false;` — If true, the emitted changes will always have bSetPivotMode set to true, regardless of the current proxy settings. This is meant to accompany a UGizmoTransformProxyTransformSource that has bOverrideSetPivotMode set to true, used for gizmos that reposition a proxy that otherwise behaves normally.

#### Free symbols / members of external scopes

- L110 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnTransformChanged, UTransformProxy*, FTransform);` — This delegate is fired whenever the transform changes in a way that updates the contained components. I.e., SetTransform is called with bSetPivotMode being false.
- L120 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnBeginTransformEdit, UTransformProxy*);` — This delegate is fired when BeginTransformEditSequence() is called to indicate that a sequence of transform updates has started
- L124 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnEndTransformEdit, UTransformProxy*);` — This delegate is fired when EndTransformEditSequence() is called to indicate that a sequence of transform updates has ended
- L131 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPivotChanged, UTransformProxy*, FTransform);` — This delegate is fired whenever the internal transform changes due to a pivot reposition, ie on AddComponent and when SetTransform is called with bSetPivotMode being true.
- L135 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnBeginPivotEdit, UTransformProxy*);` — This delegate is fired when BeginTransformEditSequence() is called to indicate that a sequence of pivot updates has started
- L139 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnEndPivotEdit, UTransformProxy*);` — This delegate is fired when EndTransformEditSequence() is called to indicate that a sequence of pivot updates has ended

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/TransformSources.h` (Public)


#### class `UGizmoBaseTransformSource`  
`class UGizmoBaseTransformSource : public UObject, public IGizmoTransformSource`  
_L34-51_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,IGizmoTransformSource`
- desc: UGizmoBaseTransformSource is a base implementation of IGizmoTransformSource that adds an OnTransformChanged delegate. This class cannot be used directly and must be subclassed.
- L38 _public function_ `virtual FTransform GetTransform() const`
- L43 _public function_ `virtual void SetTransform(const FTransform& NewTransform)`
- L49 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGizmoTransformSourceChanged, IGizmoTransformSource*);`
- L50 _public member_ `FOnGizmoTransformSourceChanged OnTransformChanged;`

#### class `UGizmoComponentWorldTransformSource`  
`class UGizmoComponentWorldTransformSource : public UGizmoBaseTransformSource`  
_L61-90_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGizmoBaseTransformSource`
- desc: UGizmoComponentWorldTransformSource implements IGizmoTransformSource (via UGizmoBaseTransformSource) based on the internal transform of a USceneComponent.
- L66 _public prototype_ `virtual FTransform GetTransform() const override;`
- L68 _public prototype_ `virtual void SetTransform(const FTransform& NewTransform) override;`
- L71 _public member_ `TObjectPtr<USceneComponent> Component;` — `UPROPERTY()`
- L75 _public member_ `bool bModifyComponentOnTransform = true;` — `UPROPERTY()` — If true, Component->Modify() is called on SetTransform
- L82 _public function_ `static UGizmoComponentWorldTransformSource* Construct( USceneComponent* Component, UObject* Outer = (UObject*)GetTransientPackage())` — Construct a default instance of UGizmoComponentWorldTransformSource with the given Component

#### struct `FSeparateScaleProvider`  
`struct FSeparateScaleProvider`  
_L100-104_
- desc: @deprecated This class was used with UGizmoScaledTransformSource, but UGizmoScaledAndUnscaledTransformSources will likely handle any similar use cases in a cleaner way. FSeparateScaleProvider provides TFunction-implementable API that sets/gets a Scaling Vector from an external source.
- L102 _public function_ `TFunction<FVector(void)> GetScale = []()`
- L102 _public member_ `TFunction<FVector(void)> GetScale = []() { return FVector::OneVector; };`
- L103 _public function_ `TFunction<void(FVector)> SetScale = [](FVector)`
- L103 _public member_ `TFunction<void(FVector)> SetScale = [](FVector) {};`

#### class `UGizmoScaledTransformSource`  
`class UGizmoScaledTransformSource : public UGizmoBaseTransformSource`  
_L120-165_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGizmoBaseTransformSource`
- desc: @deprecated Use UGizmoScaledAndUnscaledTransformSources instead. Old description: UGizmoScaledTransformSource wraps another IGizmoTransformSource implementation and adds a separate scaling vector to the Transform. The main use of this class is to support scaling in a 3D gizmo without actually scaling the Gizmo itself. Generally our pattern is to apply the gizmo's position/rotation transform to the target object via a TransformProxy, but that does not work with Scaling. So this class stores the scaling vector separately, provided by an external source via FSeparateScaleProvider, and in GetTransform/SetTransform rewrites the Transform from the child IGizmoTransformSource with the new scale.
- L128 _public prototype_ `virtual FTransform GetTransform() const override;` — IGizmoTransformSource implementation, returns child transform with local sclae
- L133 _public prototype_ `virtual void SetTransform(const FTransform& NewTransform) override;` — IGizmoTransformSource implementation, removes scale and sends to ScaleProvider, then forwards remaining rotate+translate transform to child
- L139 _public member_ `TScriptInterface<IGizmoTransformSource> ChildTransformSource;` — `UPROPERTY()` — Child transform source
- L144 _public member_ `FSeparateScaleProvider ScaleProvider;` — Provider for external scale value/storage
- L149 _public prototype_ `FTransform GetScaledTransform() const;` — Return the child transform with combined scale
- L155 _public function_ `static UGizmoScaledTransformSource* Construct( IGizmoTransformSource* ChildSource, FSeparateScaleProvider ScaleProviderIn, UObject* Outer = (UObject*)GetTransientPackage())` — Construct a default instance of UGizmoComponentWorldTransformSource with the given Component

#### class `UGizmoTransformProxyTransformSource`  
`class UGizmoTransformProxyTransformSource : public UGizmoBaseTransformSource`  
_L177-211_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGizmoBaseTransformSource`
- desc: UGizmoTransformProxyTransformSource implements IGizmoTransformSource (via UGizmoBaseTransformSource) based on the internal transform of a UTransformProxy.
- L182 _public prototype_ `virtual FTransform GetTransform() const override;`
- L184 _public prototype_ `virtual void SetTransform(const FTransform& NewTransform) override;`
- L187 _public member_ `TObjectPtr<UTransformProxy> Proxy;` — `UPROPERTY()`
- L194 _public member_ `bool bOverrideSetPivotMode = false;` — If true, the underlying proxy is modified with its SetPivotMode flag temporarily set to true. This allows the transform source to be used for proxy repositioning on a proxy that otherwise operates normally.
- L196 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGizmoTransformSourcePivotChanged, IGizmoTransformSource*);`
- L197 _public member_ `FOnGizmoTransformSourcePivotChanged OnPivotChanged;`
- L203 _public function_ `static UGizmoTransformProxyTransformSource* Construct( UTransformProxy* Proxy, UObject* Outer = (UObject*)GetTransientPackage())` — Construct a default instance of UGizmoComponentWorldTransformSource with the given Proxy

#### class `UGizmoScaledAndUnscaledTransformSources`  
`class UGizmoScaledAndUnscaledTransformSources : public UGizmoBaseTransformSource`  
_L222-273_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGizmoBaseTransformSource`
- desc: A wrapper around two IGizmoTransformSource's that generally forwards transforms to/from its ScaledTransformSource, but also forwards an unscaled version of the transform to UnscaledTransformSource on SetTransform calls. This handles the common case of wanting to apply the entire transform to one IGizmoTransformSource, but only the unscaled transform to a gizmo component (since we don't want to scale the gizmo component but do want to rotate/translate it).
- L228 _public prototype_ `virtual FTransform GetTransform() const override;` — Gets the transform from ScaledTransformSource.
- L231 _public prototype_ `virtual void SetTransform(const FTransform& NewTransform) override;` — Calls SetTransform on ScaledTransformSource and passes the unscaled version to UnscaledTransformSource.
- L234 _public member_ `TScriptInterface<IGizmoTransformSource> ScaledTransformSource;` — `UPROPERTY()`
- L237 _public member_ `TScriptInterface<IGizmoTransformSource> UnscaledTransformSource;` — `UPROPERTY()`
- L245 _public function_ `static UGizmoScaledAndUnscaledTransformSources* Construct( IGizmoTransformSource* ScaledSource, USceneComponent* GizmoComponentIn, UObject* Outer = (UObject*)GetTransientPackage())` — Constructs a UGizmoScaledAndUnscaledTransformSources by wrapping the provided IGizmoTransformSource as its scaled transform source, and the given gizmo in a UGizmoComponentWorldTransformSource as its unscaled transform source.
- L263 _public function_ `static UGizmoScaledAndUnscaledTransformSources* Construct( IGizmoTransformSource* ScaledSource, IGizmoTransformSource* UnscaledSource, UObject* Outer = (UObject*)GetTransientPackage())` — Constructs a UGizmoScaledAndUnscaledTransformSources around the given two IGizmoTransformSource's.

#### Free symbols / members of external scopes

- L49 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGizmoTransformSourceChanged, IGizmoTransformSource*);`
- L196 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGizmoTransformSourcePivotChanged, IGizmoTransformSource*);`

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/TransformSubGizmoUtil.h` (Public)


#### struct `UE::GizmoUtil::FTransformSubGizmoCommonParams`  
`struct FTransformSubGizmoCommonParams`  
_L36-77_
- desc: Common parameters needed for initializing a sub gizmo. Used in several sub gizmo reinitialization functions (such as UAxisPositionGizmo::InitializeAsTranslateGizmo).
- L38 _public member_ `UPrimitiveComponent* Component = nullptr;`
- L39 _public member_ `UTransformProxy* TransformProxy = nullptr;`
- L40 _public member_ `EAxis::Type Axis = EAxis::None;`
- L45 _public member_ `bool bAxisIsBasedOnRootComponent = true;` — If true, we use the axis of the root gizmo component. If false, we use an axis of the component itself, which is determined by its transform. Does not attempt to use shared state for axis if false.
- L51 _public member_ `TOptional<FText> TransactionName;` — Default transaction name and provider are used if not provided. Not used if one is gotten from shared state.
- L52 _public member_ `IToolContextTransactionProvider* TransactionProvider = nullptr;`
- L55 _public member_ `UObject* OuterForSubobjects = nullptr;` — Transient package is used if custom outer is not provided
- L61 _public member_ `bool bManipulatesRootComponent = true;` — If true, the gizmo moves the parent root component rather than just its own component, like the standard TRS sub gizmos do. If false, the gizmo moves just its component, leaving the parent in place. Does not attempt to use shared state for transform source or state target if false.
- L71 _public function_ `int GetClampedAxisIndex() const` — Returns the Axis parameter as an index in the range [0,2] where 0 corresponds to X (or None), 1 corresponds to Y, and 2 corresponds to Z.

#### struct `UE::GizmoUtil::FTransformSubGizmoSharedState`  
`struct FTransformSubGizmoSharedState`  
_L98-105_
- desc: A struct to hold some objects that can be reused across multiple sub gizmos that operate on the same compound gizmo, to avoid creating redundant objects. For instance, the transform source can be the same for the sub gizmos that manipulate the same overall TRS gizmo, so the first sub gizmo would create that transform source, and the subsequent ones will reuse it. Note: While the initialization functions will try to do reasonable things with this shared state (for instance, not attempt to use shared state for the axis source if the axis source is marked as being based off of this component, rather than the root), it is still up to the user to decide whether shared state should be an option. For instance, if your sub gizmo manipulates the root as normal but for some reason targets a different TransformProxy than other subgizmos, then it shouldn't share a TransformSource or StateTarget with the other gizmos, so either the shared state struct should not be used (preferable), or those properties in the struct should be nulled out before/after the call. In general, if your sub gizmo is part of the overall TRS gizmo itself (i.e. represents one of its elements), then using the shared state struct will make sense, and will save you a few redundant object creations. If your sub gizmo is just attached to the TRS gizmo but moves independently, then it may not be safe to use the shared state struct, and may not be worth the potential trouble even if you could save an object.
- L100 _public member_ `UGizmoScaledAndUnscaledTransformSources* TransformSource = nullptr;`
- L101 _public member_ `UGizmoTransformChangeStateTarget* StateTarget = nullptr;`
- L102 _public member_ `UGizmoConstantFrameAxisSource* CameraAxisSource = nullptr;`
- L103 _public member_ `UGizmoComponentAxisSource* CardinalAxisSources[3] = { 0 };`
- L104 _public member_ `UGizmoComponentAxisSource* UnitCardinalAxisSources[3] = { 0 };`

#### struct `UE::GizmoUtil::FInitMeshSubGizmoParams`  
`struct FInitMeshSubGizmoParams`  
_L117-147_
- desc: Parameter struct for InitializeSubGizmoElementsWithMesh
- L121 _public member_ `UCombinedTransformGizmo* ParentGizmo = nullptr;`
- L124 _public member_ `ETransformGizmoSubElements Elements = ETransformGizmoSubElements::None;` — If there are multiple elements, the same mesh will be set for all of them. This makes it easy to, for example, set all of the arrow components at once.
- L125 _public member_ `UStaticMesh* Mesh = nullptr;`
- L129 _public member_ `FTransform ComponentToGizmo = FTransform::Identity;`
- L134 _public member_ `bool bRotateTransformBasisBasedOnElement = true;` — When true, ComponentToGizmo is adjusted such that the gizmo basis points along the relevant element axis. This allows ComponentToGizmo to be specified once for the x axis case, and be reused for the y/z axes with the proper rotation.
- L138 _public member_ `bool bMirrorBasedOnOctant = false;` — When true, the sub gizmo is mirrored across the gizmo origin depending on where in relation to the gizmo the camera is positioned.
- L141 _public member_ `TOptional<FLinearColor> Color;` — Leaving this unset causes the color to be determined by axis.
- L144 _public member_ `UStaticMesh* SubstituteInteractionMesh = nullptr;` — Mesh to swap in when the user is dragging the gizmo.
- L146 _public member_ `FTransform SubstituteMeshToComponent = FTransform::Identity;` — Only used when SubstituteInteractionMesh is being set

#### Free symbols / members of external scopes

- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace GizmoUtil` (scope `UE`)
- L114 _prototype_ `FTransform GetRotatedBasisTransform(const FTransform& TransformIn, EAxis::Type AxisToBeX);` (scope `UE::GizmoUtil`) — Rotates a transform such that its basis still lies along the cardinal axes but rotated in such a way that the given axis is in the X direction. For example, if you have a transform that makes a component work well as an X axis in a TRS gizmo, using this function with AxisToBeX set to Y will rotate the transform to work well as the Y axis, because the basis will have been rotated to be YZX.
- L155 _prototype_ `void InitializeSubGizmoElementsWithMesh(const FInitMeshSubGizmoParams& Params, TArray<TPair<ETransformGizmoSubElements, UViewAdjustedStaticMeshGizmoComponent*>>* ElementComponentsOut = nullptr);` (scope `UE::GizmoUtil`) — Given a UCombinedTransformGizmo, swaps selected elements with custom meshes. @param ComponentsOut Optional output array of newly created gizmo components, as pairs with the single element that they were created for.

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/ViewAdjustedStaticMeshGizmoComponent.h` (Public)


#### class `UViewAdjustedStaticMeshGizmoComponent`  
`class UViewAdjustedStaticMeshGizmoComponent : public UStaticMeshComponent , public IGizmoBaseComponentInterface`  
_L24-113_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType, ClassGroup = Gizmos, meta = (BlueprintSpawnableComponent))`
- inherits: `UStaticMeshComponent,IGizmoBaseComponentInterface`
- desc: Version of a static mesh component that only takes the dynamic draw path and has the ability to adjust the transform based on view information.
- L33 _public function_ `void SetGizmoViewContext(UGizmoViewContext* GizmoViewContextIn)` — The gizmo view context is needed to be able to line trace the component, since its collision data needs updating based on view.
- L35 _public prototype_ `void SetTransformAdjuster(TSharedPtr<UE::GizmoRenderingUtil::IViewBasedTransformAdjuster> Adjuster);`
- L36 _public function_ `TSharedPtr<UE::GizmoRenderingUtil::IViewBasedTransformAdjuster> GetTransformAdjuster() const`
- L43 _public prototype_ `void SetRenderVisibilityFunction(TFunction<bool(const UE::GizmoRenderingUtil::ISceneViewInterface& View, const FTransform& ComponentToWorld)> RenderVisibilityFunc);` — The render visibility function is an optional function that can hide the component based on view information (for instance to hide an arrow gizmo when looking directly down the arrow). It must be callable from both the game and the render threads (for line traces and rendering).
- L46 _public function_ `TFunction<bool(const UE::GizmoRenderingUtil::ISceneViewInterface& View, const FTransform& ComponentToWorld)> GetRenderVisibilityFunction() const`
- L49 _public prototype_ `void SetAllMaterials(UMaterialInterface* Material);` — Helper method that just sets the same material in all slots. Does not include hover override material.
- L55 _public prototype_ `void SetHoverOverrideMaterial(UMaterialInterface* Material);` — Sets a material that will override all material slots whenever the component is told that is being hovered (via UpdateHoverState).
- L57 _public function_ `UMaterialInterface* GetHoverOverrideMaterial()`
- L58 _public function_ `bool IsBeingHovered()`
- L64 _public prototype_ `void SetSubstituteInteractionComponent(UPrimitiveComponent* Component, const FTransform& RelativeTransform = FTransform::Identity);` — Sets a mesh that is swapped in while the component is being interacted with. This is done by not rendering this component and making the substitute component visible.
- L66 _public function_ `bool IsHiddenByInteraction()`
- L69 _public prototype_ `virtual void UpdateHoverState(bool bHoveringIn) override;` — IGizmoBaseComponentInterface
- L70 _public prototype_ `virtual void UpdateWorldLocalState(bool bWorldIn) override;`
- L71 _public prototype_ `virtual void UpdateInteractingState(bool bInteracting) override;`
- L75 _public prototype_ `virtual FMaterialRelevance GetMaterialRelevance(ERHIFeatureLevel::Type InFeatureLevel) const override;` — `UE_DEPRECATED(5.7, "Please use GetMaterialRelevance with EShaderPlatform argument and not ERHIFeatureLevel::Type")` — UMeshComponent
- L76 _public prototype_ `virtual FMaterialRelevance GetMaterialRelevance(EShaderPlatform InShaderPlatform) const override;`
- L79 _public prototype_ `virtual bool LineTraceComponent(FHitResult& OutHit, const FVector Start, const FVector End, const FCollisionQueryParams& Params) override;` — UPrimitiveComponent
- L82 _public prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;` — USceneComponent
- L85 _public function_ `virtual bool IsHLODRelevant() const override` — UActorComponent
- L88 _public function_ `virtual bool NeedsLoadForServer() const override` — UObject
- L92 _protected prototype_ `virtual FPrimitiveSceneProxy* CreateStaticMeshSceneProxy(Nanite::FMaterialAudit& NaniteMaterials, bool bCreateNanite) override;` — UStaticMeshComponent
- L98 _private member_ `TObjectPtr<UGizmoViewContext> GizmoViewContext = nullptr;` — `UPROPERTY()` — Needed for proper line traces
- L101 _private member_ `TObjectPtr<UPrimitiveComponent> SubstituteInteractionComponent = nullptr;` — `UPROPERTY()`
- L104 _private member_ `TObjectPtr<UMaterialInterface> HoverOverrideMaterial = nullptr;` — `UPROPERTY()`
- L106 _private member_ `TSharedPtr<UE::GizmoRenderingUtil::IViewBasedTransformAdjuster> TransformAdjuster;`
- L108 _private member_ `bool bHovered = false;`
- L109 _private member_ `bool bInteracted = false;`
- L112 _private member_ `TFunction<bool(const UE::GizmoRenderingUtil::ISceneViewInterface& View, const FTransform& ComponentToWorld)> RenderVisibilityFunc = nullptr;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API INTERACTIVETOOLSFRAMEWORK_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace GizmoRenderingUtil` (scope `UE`)

### `Source/Runtime/InteractiveToolsFramework/Public/BaseGizmos/ViewBasedTransformAdjusters.h` (Public)


#### class `UE::GizmoRenderingUtil::IViewBasedTransformAdjuster`  
`class IViewBasedTransformAdjuster`  
_L22-67_
- desc: Interface for a helper that can adjust a component's transform based on view information, used by UViewAdjustedStaticMeshGizmoComponent. Adjusters are typically expected to be safely shareable across game and render threads, so if they are not constant, they are expected to handle updates safely in their implementation.
- L25 _public prototype_ `virtual ~IViewBasedTransformAdjuster() = default;`
- L30 _public prototype_ `virtual FTransform GetAdjustedComponentToWorld( const ISceneViewInterface& View, const FTransform& CurrentComponentToWorld) = 0;` — Given the component location and the view information, gives the desired transform of the component.
- L39 _public function_ `virtual FTransform GetAdjustedComponentToWorld_RenderThread( const ISceneViewInterface& View, const FTransform& CurrentComponentToWorld)` — If an adjuster is used by a render proxy, it will use this endpoint for getting the transform. This allows an adjuster to be potentially shared between game and render threads. Of course, a component might instead choose to create a new adjuster whenever the render proxy is recreated, and recreate the proxy whenever any relevant parameters change.
- L52 _public function_ `virtual void UpdateWorldLocalState(bool bWorldIn)` — Not every adjuster will care about the world/local setting, but it is useful for the a component that uses it to be able to blindly pass this information down without caring about the type of adjuster.
- L62 _public function_ `virtual FBoxSphereBounds GetViewIndependentBounds(const FTransform& LocalToWorld, const FBoxSphereBounds& OriginalBounds)` — Returns the transform that should be returned by a USceneComponent CalcBounds method, which can't know about the view. Although the default is to return the original bounds, any adjuster that scales the mesh arbitrarily large will probably need to return infinite bounds, whereas an adjuster that only changes orienation must account for any possible orientation. Note that returning infinite bounds causes the relevant components to no longer be frustum-culled, but this is acceptible for gizmos, which are typically few and on-screen.

#### class `UE::GizmoRenderingUtil::FSimpleConstantViewScaleAdjuster`  
`class FSimpleConstantViewScaleAdjuster : public IViewBasedTransformAdjuster`  
_L74-85_
- inherits: `IViewBasedTransformAdjuster`
- desc: Adjuster that maintains same view size but otherwise keeps the component transform. Note that this will look wrong if the component is not at the gizmo origin, because the distance relative to gizmo origin won't be scaled. Use FGizmoSubComponentTransformAdjuster if that is needed.
- L78 _public prototype_ `virtual FTransform GetAdjustedComponentToWorld( const ISceneViewInterface& View, const FTransform& CurrentComponentToWorld) override;` — IGizmoViewTransformAdjuster
- L82 _public prototype_ `virtual FBoxSphereBounds GetViewIndependentBounds(const FTransform& LocalToWorld, const FBoxSphereBounds& OriginalBounds) override;`

#### class `UE::GizmoRenderingUtil::FSubGizmoTransformAdjuster`  
`class FSubGizmoTransformAdjuster : public IViewBasedTransformAdjuster,`  
_L91-178_
- inherits: `IViewBasedTransformAdjuster,TSharedFromThis<FSubGizmoTransformAdjuster,ESPMode::ThreadSafe>`
- desc: An adjuster that can do various transformations common for sub gizmos, which are based off of the parent gizmo transform (in addition to the actual component transform).
- L115 _public function_ `FSubGizmoTransformAdjuster( const FTransform& GizmoOriginToComponent = FTransform::Identity, const FSettings& SettingsIn = FSettings()) : GizmoOriginToComponent_GameThread(GizmoOriginToComponent) , GizmoOriginToComponent_RenderThread(GizmoOriginToComponent) , Settings(SettingsIn)`
- L126 _public prototype_ `void SetGizmoOriginTransform(const FTransform& GizmoOriginToComponent);` — Update the transform of the gizmo origin relative to this component. This is safe to do even if the adjuster is used by the render thread (the render-side update gets queued properly).
- L128 _public function_ `void SetMirrorBasedOnOctant(bool bOn)`
- L132 _public function_ `void SetSettings(const FSettings& SettingsIn)`
- L146 _public prototype_ `static TSharedPtr<FSubGizmoTransformAdjuster> AddTransformAdjuster( UViewAdjustedStaticMeshGizmoComponent* ComponentIn, USceneComponent* GizmoRootComponent, bool bMirrorBasedOnOctant);` — Static helper method to create and add this adjuster to a gizmo component for the common case of keeping a constant size gizmo. @param GizmoRootComponent The distance relative to this component is kept constant, and this is the component whose rotation is considered to be 0 when using global mode. @param bMirrorBasedOnOctant If true, mirrors the component around the ComponentToKeepDistanceConstantTo depending on which octant of that component the view is located in.
- L150 _public prototype_ `static TSharedPtr<FSubGizmoTransformAdjuster> AddTransformAdjuster( UViewAdjustedStaticMeshGizmoComponent* ComponentIn, USceneComponent* GizmoRootComponent, TFunction<bool()> ShouldMirrorBasedOnOctant);`
- L156 _public prototype_ `virtual FTransform GetAdjustedComponentToWorld( const UE::GizmoRenderingUtil::ISceneViewInterface& View, const FTransform& CurrentComponentToWorld) override;` — IGizmoViewTransformAdjuster
- L160 _public prototype_ `virtual FTransform GetAdjustedComponentToWorld_RenderThread( const ISceneViewInterface& View, const FTransform& CurrentComponentToWorld) override;`
- L163 _public function_ `virtual void UpdateWorldLocalState(bool bWorldIn) override`
- L168 _public prototype_ `virtual FBoxSphereBounds GetViewIndependentBounds(const FTransform& LocalToWorld, const FBoxSphereBounds& OriginalBounds) override;`
- L171 _private member_ `FTransform GizmoOriginToComponent_GameThread = FTransform::Identity;`
- L172 _private member_ `FTransform GizmoOriginToComponent_RenderThread = FTransform::Identity;`
- L177 _private member_ `FSettings Settings;` — We might decide to have a render thread version of the settings as well, but it's unclear whether it's worth it, since it seems like a brief inconsistency during the update is unlikely to cause much of a problem: a user is unlikely to be changing multiple bools at once, and reading an outdated bool seems fine.

#### struct `UE::GizmoRenderingUtil::FSubGizmoTransformAdjuster::FSettings`  
`struct FSettings`  
_L96-113_
- L100 _public function_ `FSettings()` — Some compilers (clang, at least) have issues with using a nested class with default initializers and a default constructor as a default argument in a function, hence this constructor.
- L103 _public member_ `bool bKeepConstantViewSize = true;` — Keeps view size and offset relative to parent gizmo constant
- L105 _public member_ `bool bMirrorBasedOnOctant = true;` — Mirrors the component depending on which octant of the parent gizmo the view is located
- L109 _public member_ `bool bUseWorldAxesForGizmo = false;` — Considers the parent gizmo transform to be unrotated, and applies the relative component transform on top of that. This is frequently not necessary to set because code upstream will typically update it every tick anyway via UViewAdjustedStaticMeshGizmoComponent's UpdateWorldLocalState implementation.
- L112 _public member_ `double DistanceInFrontOfCameraInOrtho = 0;` — If positive, keeps the component a given distance in front of the ortho camera, to avoid clipping it. Applied before bKeepConstantViewSize.

#### class `UE::GizmoRenderingUtil::FConstantViewRelativeTransformAdjuster`  
`class FConstantViewRelativeTransformAdjuster : public IViewBasedTransformAdjuster`  
_L188-207_
- inherits: `IViewBasedTransformAdjuster`
- L191 _public function_ `FConstantViewRelativeTransformAdjuster(const FTransform& ViewRelativeTransformIn, bool bConstantSize = true) : ViewRelativeTransform(ViewRelativeTransformIn) , bKeepConstantViewSize(bConstantSize)`
- L198 _public prototype_ `virtual FTransform GetAdjustedComponentToWorld( const UE::GizmoRenderingUtil::ISceneViewInterface& View, const FTransform& CurrentComponentToWorld) override;` — IGizmoViewTransformAdjuster
- L202 _public prototype_ `virtual FBoxSphereBounds GetViewIndependentBounds(const FTransform& LocalToWorld, const FBoxSphereBounds& OriginalBounds) override;`
- L205 _private member_ `FTransform ViewRelativeTransform = FTransform::Identity;`
- L206 _private member_ `bool bKeepConstantViewSize = true;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace GizmoRenderingUtil` (scope `UE`)

### `Source/Runtime/InteractiveToolsFramework/Public/BaseTools/BaseBrushTool.h` (Public)


#### class `UBrushBaseProperties`  
`class UBrushBaseProperties : public UInteractiveToolPropertySet`  
_L18-79_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Standard properties for a Brush-type Tool
- L23 _public prototype_ `UBrushBaseProperties();`
- L27 _public member_ `float BrushSize;` — `UPROPERTY(EditAnywhere, Category = Brush, meta = (DisplayName = "Size", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "10.0", DisplayPriority = 1, HideEditConditionToggle, EditCondition = "bSpecifyRadius == false", ModelingQuickSettings = 100))` — Relative size of brush
- L31 _public member_ `bool bSpecifyRadius;` — `UPROPERTY(EditAnywhere, Category = Brush, AdvancedDisplay)` — If true, ignore relative Brush Size and use explicit world Radius
- L36 _public member_ `float BrushRadius;` — `UPROPERTY(EditAnywhere, Category = Brush, AdvancedDisplay, meta = (EditCondition = "bSpecifyRadius", DisplayName = "Radius", UIMin = "1.0", UIMax = "1000.0", ClampMin = "0.1", ClampMax = "50000.0", ModelingQuickSettings = 100))` — Radius of brush
- L43 _public member_ `bool bToolSupportsPressureSensitivity = false;` — `UPROPERTY()`
- L47 _public member_ `bool bEnablePressureSensitivity = false;` — `UPROPERTY(EditAnywhere, Category = Brush, meta = (EditCondition = "bToolSupportsPressureSensitivity", EditConditionHides))` — When set, stylus pressure is used to adjust radius
- L54 _public member_ `float BrushStrength;` — `UPROPERTY(EditAnywhere, Category = Brush, meta = (DisplayName = "Strength", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0", HideEditConditionToggle, EditConditionHides, EditCondition = "bShowStrength", DisplayPriority = 2, ModelingQuickEdit, ModelingQuickSettings = 200))` — Strength of the brush (0.0 - 1.0)
- L61 _public member_ `float BrushFalloffAmount;` — `UPROPERTY(EditAnywhere, Category = Brush, meta = (DisplayName = "Falloff", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0", HideEditConditionToggle, EditConditionHides, EditCondition="bShowFalloff", DisplayPriority = 3, ModelingQuickEdit, ModelingQuickSettings = 300))` — Amount of falloff to apply (0.0 - 1.0)
- L66 _public member_ `bool bHitBackFaces = false;` — `UPROPERTY(EditAnywhere, Category = Brush, meta = (DisplayPriority = 6, HideEditConditionToggle, EditConditionHides, EditCondition = "bShowHitBackFaces"))` — Allow the Brush to hit the back-side of the mesh
- L70 _public member_ `bool bShowStrength = true;` — `UPROPERTY(meta = (TransientToolProperty))` — If false, then BrushStrength will not be shown in DetailsView panels (otherwise no effect)
- L74 _public member_ `bool bShowFalloff = true;` — `UPROPERTY(meta = (TransientToolProperty))` — If false, then BrushFalloffAmount will not be shown in DetailsView panels (otherwise no effect)
- L78 _public member_ `bool bShowHitBackFaces = false;` — `UPROPERTY(meta = (TransientToolProperty))` — If false, then bHitBackFaces will not be shown in DetailsView panels (otherwise no effect)

#### struct `FBrushStampData`  
`struct FBrushStampData`  
_L86-101_
- reflection: `USTRUCT()`
- desc: Generic Brush Stamp data
- L90 _public member_ `float Radius;` — Radius of brush stamp
- L92 _public member_ `FVector WorldPosition;` — World Position of brush stamp
- L94 _public member_ `FVector WorldNormal;` — World Normal of brush stamp
- L97 _public member_ `FHitResult HitResult;` — Hit Result provided by implementations - may not be fully populated
- L100 _public member_ `float Falloff;` — Falloff of brush stamp

#### class `UBrushAdjusterInputBehavior`  
`class UE_DEPRECATED(5.5, "UBrushAdjusterInputBehavior is deprecated, use UTwoAxisPropertyEditInputBehavior instead.") UBrushAdjusterInputBehavior : public UAnyButtonInputBehavior`  
_L113-165_
- reflection: `UCLASS()`
- inherits: `UAnyButtonInputBehavior`
- desc: A behavior that captures a keyboard hotkey to enter a sub-mode "bAdjustingBrush" while the key is pressed. The target tool must call OnDragStart() and OnDragUpdate() to feed the screen coordinates of the mouse for the duration of the behavior. And use "GetIsBrushBeingAdjusted" to pause/disable the brush motion while it is being adjusted. OnDragStart() defines the starting location of an adjustment OnDragUpdate() adjusts the brush strength and radius based on the magnitude of the screen coordinate delta in the vertical and horizontal directions respectively.
- L119 _public prototype_ `void Initialize(UBaseBrushTool* InBrushTool);`
- L121 _public prototype_ `void DrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI);`
- L123 _public function_ `void SetStrengthAdjustSpeed(float InStrengthSpeed)`
- L124 _public function_ `void SetSizeAdjustSpeed(float InSizeSpeed)`
- L126 _public prototype_ `void OnDragStart(FVector2D InScreenPosition);`
- L127 _public prototype_ `void OnDragUpdate(FVector2D InScreenPosition);`
- L129 _public function_ `bool IsBrushBeingAdjusted() const`
- L132 _public prototype_ `virtual EInputDevices GetSupportedDevices() override;` — UAnyButtonInputBehavior
- L133 _public prototype_ `virtual bool IsPressed(const FInputDeviceState& Input) override;`
- L134 _public prototype_ `virtual bool IsReleased(const FInputDeviceState& Input) override;`
- L135 _public prototype_ `virtual FInputCaptureRequest WantsCapture(const FInputDeviceState& Input) override;`
- L136 _public prototype_ `virtual FInputCaptureUpdate BeginCapture(const FInputDeviceState& Input, EInputCaptureSide eSide) override;`
- L137 _public prototype_ `virtual FInputCaptureUpdate UpdateCapture(const FInputDeviceState& Input, const FInputCaptureData& data) override;`
- L138 _public prototype_ `virtual void ForceEndCapture(const FInputCaptureData& data) override;`
- L143 _private prototype_ `void ResetAdjustmentOrigin(FVector2D InScreenPosition, bool bHorizontalAdjust);`
- L146 _private member_ `bool bAdjustingBrush = false;` — true for the duration of the behavior (while hotkey is down)
- L148 _private member_ `FVector2D BrushOrigin;` — screen coordinate when hotkey pressed (or when re-centered if changing direction)
- L150 _private member_ `FVector2D AdjustmentOrigin;` — screen coordinate when hotkey pressed (or when re-centered if changing direction)
- L152 _private member_ `float StartBrushRadius;` — the radius of the brush when we started a drag
- L154 _private member_ `float StartBrushStrength;` — the strength of the brush when we started a drag
- L156 _private member_ `bool bAdjustingHorizontally = true;` — supports separate horizontal / vertical adjustments (switching dynamically based on magnitude)
- L159 _private member_ `float SizeAdjustSpeed = 0.002f;` — the speed (centimeters per unit of screen coordinate) to adjust brush size when dragging
- L161 _private member_ `float StrengthAdjustSpeed = 0.005f;` — the speed (in strength per unit of screen coordinate) to adjust brush strength when dragging
- L164 _private member_ `UBaseBrushTool* BrushTool;` — the target brush tool to adjust

#### class `UBaseBrushTool`  
`class UBaseBrushTool : public UMeshSurfacePointTool`  
_L177-285_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSurfacePointTool`
- desc: UBaseBrushTool implements standard brush-style functionality for an InteractiveTool. This includes: 1) brush radius property set with dimension-relative brush sizing and default brush radius hotkeys 2) brush indicator visualization 3) tracking of last brush stamp location via .LastBrushStamp FProperty 4) status of brush stroke via .bInBrushStroke FProperty 5) "B" hotkey to adjust brush radius / strength by click-dragging in the viewport
- L182 _public prototype_ `UBaseBrushTool();`
- L184 _public prototype_ `virtual void RegisterActions(FInteractiveToolActionSet& ActionSet) override;`
- L187 _public prototype_ `virtual void Setup() override;` — UInteractiveTool
- L188 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L189 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L190 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L191 _public prototype_ `virtual void DrawHUD( FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI ) override;`
- L193 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L196 _public prototype_ `virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& PressPos) override;` — IClickDragBehaviorTarget implementation
- L199 _public prototype_ `virtual void OnBeginDrag(const FRay& Ray) override;` — UMeshSurfacePointTool implementation
- L200 _public prototype_ `virtual void OnUpdateDrag(const FRay& Ray) override;`
- L201 _public prototype_ `virtual void OnEndDrag(const FRay& Ray) override;`
- L202 _public prototype_ `virtual void OnCancelDrag() override;`
- L203 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) override;`
- L209 _public member_ `TObjectPtr<UBrushBaseProperties> BrushProperties;` — `UPROPERTY()` — Properties that control brush size/etc
- L214 _public member_ `bool bInBrushStroke = false;` — `UE_DEPRECATED(5.5, "The bInBrushStroke property is deprecated. This will now always be true in OnBeginDrag/OnUpdateDrag/OnEndDrag.")` — `UPROPERTY()` — Set to true by Tool if user is currently in an active brush stroke
- L218 _public member_ `float WorldToLocalScale = 1.0f;` — `UPROPERTY()` — Uniform scale factor that scales from world space (where brush usually exists) to local space
- L222 _public member_ `FBrushStampData LastBrushStamp;` — `UPROPERTY()` — Position of brush at last update (both during stroke and during Hover)
- L226 _public prototype_ `virtual void IncreaseBrushSizeAction();`
- L227 _public prototype_ `virtual void DecreaseBrushSizeAction();`
- L228 _public prototype_ `virtual void IncreaseBrushStrengthAction();`
- L229 _public prototype_ `virtual void DecreaseBrushStrengthAction();`
- L230 _public prototype_ `virtual void IncreaseBrushFalloffAction();`
- L231 _public prototype_ `virtual void DecreaseBrushFalloffAction();`
- L235 _public function_ `virtual bool IsInBrushStroke() const` — `UE_DEPRECATED(5.5, "The IsInBrushStroke function is deprecated. This will now always be true in OnBeginDrag/OnUpdateDrag/OnEndDrag.")`
- L238 _public prototype_ `virtual double GetCurrentBrushRadius() const;`
- L239 _public function_ `virtual double GetCurrentBrushRadiusLocal() const`
- L241 _public prototype_ `void SetBrushEnabled(bool bIsEnabled);`
- L244 _public function_ `virtual bool SupportsBrushAdjustmentInput()` — return false to disable the hotkey for adjusting the brush radius and strength in the viewport
- L251 _protected function_ `virtual double EstimateMaximumTargetDimension()` — Subclasses should implement this to give an estimate of target dimension for brush size scaling
- L253 _protected function_ `virtual double GetActivePressure() const`
- L255 _protected member_ `TInterval<float> BrushRelativeSizeRange;`
- L256 _protected member_ `double CurrentBrushRadius;`
- L257 _protected prototype_ `void RecalculateBrushRadius();`
- L260 _protected member_ `TSoftClassPtr<UBrushBaseProperties> PropertyClass;` — `UPROPERTY()`
- L268 _protected member_ `TObjectPtr<UBrushStampIndicator> BrushStampIndicator;` — `UPROPERTY()`
- L270 _protected prototype_ `virtual void SetupBrushStampIndicator();`
- L271 _protected prototype_ `virtual void UpdateBrushStampIndicator();`
- L272 _protected prototype_ `virtual void ShutdownBrushStampIndicator();`
- L277 _protected member_ `TWeakObjectPtr<UBrushAdjusterInputBehavior> BrushAdjusterBehavior;` — `UE_DEPRECATED(5.5, "BrushAdjusterBehavior is deprecated, use BrushEditBehavior instead.")` — adjusts size and strength properties while holding hotkey during click/drag
- L280 _protected member_ `TWeakObjectPtr<ULocalTwoAxisPropertyEditInputBehavior> BrushEditBehavior;`
- L283 _private member_ `double ActivePressure = 1.0;`
- L284 _private member_ `bool bEnabled = true;`

### `Source/Runtime/InteractiveToolsFramework/Public/BaseTools/ClickDragTool.h` (Public)


#### class `UClickDragToolBuilder`  
`class UClickDragToolBuilder : public UInteractiveToolBuilder`  
_L24-31_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolBuilder`
- desc: Builder for UClickDragTool
- L29 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L30 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`

#### class `UClickDragTool`  
`class UClickDragTool : public UInteractiveTool, public IClickDragBehaviorTarget`  
_L41-87_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveTool,IClickDragBehaviorTarget`
- desc: UClickDragTool is a base tool that basically just implements IClickDragBehaviorTarget, and on setup registers a UClickDragInputBehavior. You can subclass this Tool to implement basic click-drag type Tools. If you want to do more advanced things, like handle modifier buttons/keys, you will need to implement IClickDragBehaviorTarget yourself
- L50 _public prototype_ `virtual void Setup() override;` — Register default primary-button-click InputBehaviors
- L62 _public prototype_ `virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& PressPos) override;` — Test if target can begin click-drag interaction at this point @param ClickPos device position/ray at click point @return true if target wants to begin sequence
- L68 _public prototype_ `virtual void OnClickPress(const FInputDeviceRay& PressPos) override;` — Notify Target that click press ocurred @param ClickPos device position/ray at click point
- L74 _public prototype_ `virtual void OnClickDrag(const FInputDeviceRay& DragPos) override;` — Notify Target that input position has changed @param ClickPos device position/ray at click point
- L80 _public prototype_ `virtual void OnClickRelease(const FInputDeviceRay& ReleasePos) override;` — Notify Target that click release occurred @param ClickPos device position/ray at click point
- L85 _public prototype_ `virtual void OnTerminateDragSequence() override;` — Notify Target that click-drag sequence has been explicitly terminated (eg by escape key)

### `Source/Runtime/InteractiveToolsFramework/Public/BaseTools/MeshSurfacePointTool.h` (Public)


#### class `IToolStylusStateProviderAPI`  
`class IToolStylusStateProviderAPI`  
_L19-23_
- desc: This is a temporary interface to provide stylus pressure, currently necessary due to limitations in the stylus plugin architecture. Should be removed once InputState/InputBehavior can support stylus events
- L22 _public prototype_ `virtual float GetCurrentPressure() const = 0;`

#### class `UMeshSurfacePointToolBuilder`  
`class UMeshSurfacePointToolBuilder : public UInteractiveToolWithToolTargetsBuilder`  
_L29-50_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolWithToolTargetsBuilder`
- L34 _public member_ `IToolStylusStateProviderAPI* StylusAPI = nullptr;`
- L37 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;` — @return true if a single mesh source can be found in the active selection
- L40 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;` — @return new Tool instance initialized with selected mesh source
- L43 _public prototype_ `virtual UMeshSurfacePointTool* CreateNewTool(const FToolBuilderState& SceneState) const;` — @return new Tool instance. Override this in subclasses to build a different Tool class type
- L46 _public prototype_ `virtual void InitializeNewTool(UMeshSurfacePointTool* Tool, const FToolBuilderState& SceneState) const;` — Called by BuildTool to configure the Tool with the input MeshSource based on the SceneState
- L49 _protected prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### class `UMeshSurfacePointTool`  
`class UMeshSurfacePointTool : public USingleSelectionTool, public IClickDragBehaviorTarget, public IHoverBehaviorTarget`  
_L63-159_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleSelectionTool,IClickDragBehaviorTarget,IHoverBehaviorTarget`
- desc: UMeshSurfacePointTool is a base Tool implementation that can be used to implement various "point on surface" interactions. The tool acts on an input IMeshDescriptionSource object, which the standard Builder can extract from the current selection (eg Editor selection). Subclasses override the OnBeginDrag/OnUpdateDrag/OnEndDrag and OnUpdateHover functions to implement custom behavior.
- L71 _public prototype_ `virtual void Setup() override;` — Register InputBehaviors, etc
- L74 _public prototype_ `virtual void SetStylusAPI(IToolStylusStateProviderAPI* StylusAPI);` — Set current stlyus API source
- L81 _public prototype_ `virtual bool HitTest(const FRay& Ray, FHitResult& OutHit);` — @return true if the target MeshSource is hit by the Ray
- L86 _public prototype_ `virtual void OnBeginDrag(const FRay& Ray);` — This function is called when the user begins a click-drag-release interaction
- L91 _public prototype_ `virtual void OnUpdateDrag(const FRay& Ray);` — This function is called each frame that the user is in a click-drag-release interaction
- L96 _public prototype_ `virtual void OnEndDrag(const FRay& Ray);` — This function is called when the user releases the button driving a click-drag-release interaction
- L101 _public function_ `virtual void OnCancelDrag()` — This function is called when the user's drag is cancelled, for example due to the whole tool being shut down.
- L105 _public prototype_ `virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& PressPos) override;` — IClickDragBehaviorTarget implementation
- L106 _public prototype_ `virtual void OnClickPress(const FInputDeviceRay& PressPos) override;`
- L107 _public prototype_ `virtual void OnClickDrag(const FInputDeviceRay& DragPos) override;`
- L108 _public prototype_ `virtual void OnClickRelease(const FInputDeviceRay& ReleasePos) override;`
- L109 _public prototype_ `virtual void OnTerminateDragSequence() override;`
- L110 _public prototype_ `virtual void OnUpdateModifierState(int ModifierID, bool bIsOn) override;`
- L115 _public prototype_ `virtual FInputRayHit BeginHoverSequenceHitTest(const FInputDeviceRay& PressPos) override;`
- L116 _public function_ `virtual void OnBeginHover(const FInputDeviceRay& DevicePos) override`
- L117 _public function_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) override`
- L118 _public function_ `virtual void OnEndHover() override`
- L122 _public prototype_ `virtual bool GetWorldSpaceFocusPoint(const FRay& WorldRay, FVector& PointOut) override;` — IInteractiveToolCameraFocusAPI implementation
- L126 _public prototype_ `virtual void SetShiftToggle(bool bShiftDown);` — Called by registered InputBehaviors to set the state of the "shift" button (or device equivalent)
- L129 _public function_ `virtual bool GetShiftToggle() const` — @return current state of the shift toggle
- L132 _public prototype_ `virtual void SetCtrlToggle(bool bCtrlDown);` — Called by registered InputBehaviors to set the state of the "ctrl" button (or device equivalent)
- L135 _public function_ `virtual bool GetCtrlToggle() const` — @return current state of the ctrl toggle
- L138 _public prototype_ `virtual float GetCurrentDevicePressure() const;` — @return current input device pressure in range 0-1
- L140 _public prototype_ `void SetWorld(UWorld* World);`
- L141 _public prototype_ `UWorld* GetTargetWorld();`
- L145 _protected member_ `bool bShiftToggle = false;` — Current state of the shift modifier toggle
- L148 _protected member_ `bool bCtrlToggle = false;` — Current state of the ctrl modifier toggle
- L150 _protected member_ `FRay LastWorldRay;`
- L152 _protected member_ `IToolStylusStateProviderAPI* StylusAPI = nullptr;`
- L155 _protected member_ `TWeakObjectPtr<UWorld> TargetWorld = nullptr;` — `UPROPERTY()`
- L157 _protected member_ `static constexpr int ShiftModifier = 1;`
- L158 _protected member_ `static constexpr int CtrlModifier = 2;`

### `Source/Runtime/InteractiveToolsFramework/Public/BaseTools/SingleClickTool.h` (Public)


#### class `USingleClickToolBuilder`  
`class USingleClickToolBuilder : public UInteractiveToolBuilder`  
_L25-32_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolBuilder`
- desc: Builder for USingleClickTool
- L30 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L31 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`

#### class `USingleClickTool`  
`class USingleClickTool : public UInteractiveTool, public IClickBehaviorTarget`  
_L48-69_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveTool,IClickBehaviorTarget`
- desc: USingleClickTool is perhaps the simplest possible interactive tool. It simply reacts to default primary button clicks for the active device (eg left-mouse clicks). The function ::IsHitByClick() determines what is clickable by this Tool. The default is to return true, which means the click will activate anywhere (the Tool itself has no notion of Actors, Components, etc). You can override this function to, for example, filter out clicks that don't hit a target object, etc. The function ::OnClicked() implements the action that will occur when a click happens. You must override this to implement any kind of useful behavior.
- L57 _public prototype_ `virtual void Setup() override;` — Register default primary-button-click InputBehaviors
- L62 _public prototype_ `virtual FInputRayHit IsHitByClick(const FInputDeviceRay& ClickPos);` — Test if the Target is hit at this 2D position / 3D ray
- L67 _public prototype_ `virtual void OnClicked(const FInputDeviceRay& ClickPos);` — Click the Target at this 2D position / 3D ray. Default behavior is to print debug string.

### `Source/Runtime/InteractiveToolsFramework/Public/Changes/ToolCommandChangeSequence.h` (Public)


#### class `FToolCommandChangeSequence`  
`class FToolCommandChangeSequence : public FToolCommandChange`  
_L16-79_
- inherits: `FToolCommandChange`
- desc: FCommandChangeSequence contains a list of FCommandChanges and associated target UObjects. The sequence of changes is applied atomically. @warning if the target weak UObject pointers become invalid, those changes are skipped. Possibly leaves things in an undefined state...
- L25 _protected member_ `TArray<TSharedPtr<FChangeElem>> Sequence;`
- L28 _public function_ `FToolCommandChangeSequence()`
- L33 _public function_ `void AppendChange(UObject* Target, TUniquePtr<FToolCommandChange> Change)` — Add a change to the sequence
- L42 _public function_ `virtual void Apply(UObject* Object) override` — Apply sequence of changes in-order
- L56 _public function_ `virtual void Revert(UObject* Object) override` — Reverts sequence of changes in reverse-order
- L70 _public function_ `virtual FString ToString() const override` — @return string describing this change sequenece

#### struct `FToolCommandChangeSequence::FChangeElem`  
`struct FChangeElem`  
_L19-23_
- L21 _public member_ `TWeakObjectPtr<UObject> TargetObject;`
- L22 _public member_ `TUniquePtr<FToolCommandChange> Change;`

### `Source/Runtime/InteractiveToolsFramework/Public/Changes/TransformChange.h` (Public)


#### class `FComponentWorldTransformChange`  
`class FComponentWorldTransformChange : public FToolCommandChange`  
_L17-37_
- inherits: `FToolCommandChange`
- desc: FComponentWorldTransformChange represents an undoable change to the world transform of a USceneComponent.
- L20 _public prototype_ `FComponentWorldTransformChange();`
- L21 _public prototype_ `FComponentWorldTransformChange(const FTransform& From, const FTransform& To);`
- L23 _public member_ `FTransform FromWorldTransform;`
- L24 _public member_ `FTransform ToWorldTransform;`
- L27 _public member_ `TFunction<void(FComponentWorldTransformChange*, UObject*, bool)> OnChangeAppliedFunc;` — This function is called on Apply and Revert (last argument is true on Apply)
- L30 _public prototype_ `virtual void Apply(UObject* Object) override;` — Makes the change to the object
- L33 _public prototype_ `virtual void Revert(UObject* Object) override;` — Reverts change to the object
- L36 _public prototype_ `virtual FString ToString() const override;` — Describes this change (for debugging)

### `Source/Runtime/InteractiveToolsFramework/Public/ComponentSourceInterfaces.h` (Public)


#### class `FPrimitiveComponentTarget`  
`class FPrimitiveComponentTarget`  
_L29-110_
- desc: @deprecated Use tool targets instead, such as UPrimitiveComponentToolTarget Wrapper around a UObject Component that can provide a MeshDescription, and (optionally) bake a modified MeshDescription back to this Component. An example of a Source might be a StaticMeshComponent. How a modified MeshDescription is committed back is context-dependent (in Editor vs PIE vs Runtime, etc). (Conceivably this doesn't have to be backed by a Component, but most usage will assume there is an Actor)
- L32 _public prototype_ `virtual ~FPrimitiveComponentTarget()= default;`
- L37 _public function_ `FPrimitiveComponentTarget( UPrimitiveComponent* Component ): Component( Component )` — Constructor UPrimitivecomponent* @param Component the UPrimitiveComponent* to target
- L40 _public prototype_ `virtual bool IsValid() const;` — @return true if component target is still valid. May become invalid for various reasons (eg Component was deleted out from under us)
- L43 _public prototype_ `AActor* GetOwnerActor() const;` — @return the Actor that owns this Component
- L46 _public prototype_ `UPrimitiveComponent* GetOwnerComponent() const;` — @return the Component this is a Source for
- L49 _public prototype_ `int32 GetNumMaterials() const;` — @return number of material indices in use by this Component
- L56 _public prototype_ `UMaterialInterface* GetMaterial(int32 MaterialIndex) const;` — Get pointer to a Material provided by this Source @param MaterialIndex index of the material @return MaterialInterface pointer, or null if MaterialIndex is invalid
- L63 _public prototype_ `virtual void GetMaterialSet(FComponentMaterialSet& MaterialSetOut, bool bAssetMaterials = false) const;` — Get material set provided by this source @param MaterialSetOut returned material set @param bAssetMaterials if an underlying asset exists, return the Asset-level material assignment instead of the component materials
- L69 _public prototype_ `FTransform GetWorldTransform() const;` — @return the transform on this component @todo Do we need to return a list of transforms here?
- L77 _public prototype_ `bool HitTest(const FRay& WorldRay, FHitResult& OutHit) const;` — Compute ray intersection with the MeshDescription this Source is providing @param WorldRay ray in world space @param OutHit hit test data @return true if ray intersected Component
- L83 _public prototype_ `void SetOwnerVisibility(bool bVisible) const;` — Set the visibility of the Component associated with this Source (ie to hide during Tool usage) @param bVisible desired visibility
- L91 _public prototype_ `virtual bool HasSameSourceData(const FPrimitiveComponentTarget& OtherTarget) const = 0;` — Checks if the underlying asset that would be edited by CommitMesh() is the same for two ComponentTargets @param OtherTarget Another component target to compare against @return true if both component targets are known to share the same source asset
- L98 _public prototype_ `virtual void CommitMaterialSetUpdate(const FComponentMaterialSet& MaterialSet, bool bApplyToAsset);` — Commit an update to the material set. This may generate a transaction. @param MaterialSet new list of materials @param bApplyToAsset if true, materials of Asset are updated (if Asset exists), rather than Component
- L105 _public typedef_ `using FCommitter = TFunction< void( const FCommitParams& ) >;`
- L106 _public prototype_ `virtual FMeshDescription* GetMesh() = 0;`
- L107 _public prototype_ `virtual void CommitMesh( const FCommitter& ) = 0;`
- L109 _public member_ `UPrimitiveComponent* Component{};`

#### struct `FPrimitiveComponentTarget::FCommitParams`  
`struct FCommitParams`  
_L101-104_
- L103 _public member_ `FMeshDescription* MeshDescription{ nullptr };`

#### class `FComponentTargetFactory`  
`class FComponentTargetFactory`  
_L113-119_
- desc: @deprecated Use tool target factories instead.
- L116 _public prototype_ `virtual ~FComponentTargetFactory()= default;`
- L117 _public prototype_ `virtual bool CanBuild( UActorComponent* Candidate ) = 0;`
- L118 _public prototype_ `virtual TUniquePtr<FPrimitiveComponentTarget> Build( UPrimitiveComponent* PrimitiveComponent ) = 0;`

#### Free symbols / members of external scopes

- L128 _prototype_ `int32 AddComponentTargetFactory( TUniquePtr<FComponentTargetFactory> Factory );` — @deprecated Add tool target factories to the tool target manager instead. Add a factory method to make ComponentTarget from UPrimitiveComponent* @param Factory The ComponentTargetFactory @return integer indentifier that identifies this Factory
- L134 _prototype_ `FComponentTargetFactory* FindComponentTargetFactoryByKey(int32 Key);` — @return ComponentTargetFactory associated with the given Key, or nullptr if not found
- L140 _prototype_ `bool RemoveComponentTargetFactoryByKey(int32 Key);` — @return true if ComponentTargetFactory associated with the given Key was found and removed
- L146 _prototype_ `void RemoveAllComponentTargetFactoryies();` — remove all registered ComponentTargetFactory objects
- L158 _prototype_ `TUniquePtr<FPrimitiveComponentTarget> MakeComponentTarget(UPrimitiveComponent* Component);` — @deprecated Ask your tool target manager to build a target for you instead. Create a TargetComponent for the given Component @param Component A UObject that we would like to use as tool target. This must presently descend from UPrimitiveComponent @return An FComponentTarget instance. Must not return null, though the MeshSource and MeshSink in it's MeshBridge may be
- L168 _prototype_ `bool CanMakeComponentTarget(UActorComponent* Component);` — @deprecated Ask your tool target manager instead. Determine whether a TargetComponent can be created for the given Component @param Component A UObject that we would like to use as tool target. @return bool signifying whether or not a ComponentTarget can be built

### `Source/Runtime/InteractiveToolsFramework/Public/ContextObjectStore.h` (Public)


#### class `UContextObjectStore`  
`class UContextObjectStore : public UObject`  
_L24-90_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UObject`
- desc: A context object store allows tools to get access to arbitrary objects which expose data or APIs to enable additional functionality. Some example use cases of context objects: - A tool builder may disallow a particular tool if a needed API object is not present in the context store. - A tool may allow extra actions if it has access to a particular API object in the context store. - A tool may choose to initialize itself differently based on the presence of a selection-holding data object in the context store.
- L34 _public function_ `template <typename TObjectType> TObjectType* FindContext() const` — Finds the first the context object of the given type. Can return a subclass of the given type. @returns the found context object, casted to the given type, or nullptr if none matches.
- L56 _public prototype_ `UObject* FindContextByClass(UClass* InClass) const;` — Finds the first context object that derives from the given class. @returns the found context object, or nullptr if none matches.
- L62 _public prototype_ `bool AddContextObject(UObject* InContextObject);` — Adds a data object to the tool manager's set of shared data objects. @returns true if the addition is successful.
- L68 _public prototype_ `bool RemoveContextObject(UObject* InContextObject);` — Removes a data object from the tool manager's set of shared data objects. @returns true if the removal is successful.
- L74 _public prototype_ `bool RemoveContextObjectsOfType(const UClass* InClass);` — Removes any data objects from the tool manager's set of shared data objects that are of type @param InClass @returns true if any objects are removed.
- L77 _public function_ `template <class TObjectType> bool RemoveContextObjectsOfType()`
- L85 _public prototype_ `void Shutdown();` — Shuts down the context object store, releasing hold on any stored content objects.
- L89 _protected member_ `TArray<TObjectPtr<UObject>> ContextObjects;` — `UPROPERTY()`

### `Source/Runtime/InteractiveToolsFramework/Public/InputBehavior.h` (Public)


#### enum `EInputCaptureSide`  
`enum class EInputCaptureSide`  
_L19-26_
- reflection: `UENUM()`
- desc: Input can be captured separately for Left and Right sides (eg for VR controllers) Currently mouse is Left.
- L21 _public enumerator_ `None = 0`
- L22 _public enumerator_ `Left = 1`
- L23 _public enumerator_ `Right = 2`
- L24 _public enumerator_ `Both = 3`
- L25 _public enumerator_ `Any = 99`

#### struct `FInputCaptureData`  
`struct FInputCaptureData`  
_L34-46_
- desc: An active capturing behavior may need to keep track of additional data that cannot be stored within the behavior (for example if the same behavior instance is capturing for Left and Right separately). So FInputCaptureUpdate can optionally return this structure, and we will pass it to the next UpdateCapture() call
- L37 _public member_ `EInputCaptureSide WhichSide;` — Which side do we want to capture on
- L39 _public member_ `void* CustomData;` — pointer to data defined by the InputBehavior, which is also responsible for cleaning it up
- L41 _public function_ `FInputCaptureData()`

#### enum `EInputCaptureRequestType`  
`enum class EInputCaptureRequestType`  
_L53-57_
- reflection: `UENUM()`
- desc: Used by FInputCaptureRequest to indicate whether the InputBehavior wants to capture or ignore an input event
- L55 _public enumerator_ `Begin = 1`
- L56 _public enumerator_ `Ignore = 2`

#### struct `FInputCaptureRequest`  
`struct FInputCaptureRequest`  
_L66-112_
- desc: UInputBehavior returns an FInputCaptureRequest from WantsCapture() to indicate whether it wants to capture or ignore an input event
- L69 _public member_ `UInputBehavior* Source;` — Which input behavior generated this request
- L71 _public member_ `EInputCaptureRequestType Type;` — What type of capture request is this (Begin or Ignore)
- L73 _public member_ `EInputCaptureSide Side;` — Which side does request want to capture on
- L76 _public member_ `double HitDepth;` — Depth along hit-test ray
- L79 _public member_ `void* Owner;` — Owner of the requesting behavior. Behavior doesn't know this, so this is initialized to null
- L81 _public function_ `FInputCaptureRequest( EInputCaptureRequestType type, UInputBehavior* behavior, EInputCaptureSide whichSide, double hitDepth = TNumericLimits<double>::Max() )`
- L96 _public function_ `static FInputCaptureRequest Begin( UInputBehavior* behavior, EInputCaptureSide whichSide, double hitDepth = TNumericLimits<double>::Max() )` — Create a Begin-capture request
- L104 _public function_ `static FInputCaptureRequest Ignore()` — Create an ignore-capture request

#### enum `EInputCaptureState`  
`enum class EInputCaptureState`  
_L119-125_
- reflection: `UENUM()`
- desc: FInputCaptureUpdate uses this type to indicate what state the capturing Behavior would like to transition to, based on the input event
- L121 _public enumerator_ `Begin = 1` — start capturing (which should always be the case if BeginCapture is called)
- L122 _public enumerator_ `Continue = 2` — Behavior wants to continue capturing
- L123 _public enumerator_ `End = 3` — Behavior wants to end capturing
- L124 _public enumerator_ `Ignore = 4` — Behavior ignored this event

#### struct `FInputCaptureUpdate`  
`struct FInputCaptureUpdate`  
_L131-182_
- desc: IInputBehavior returns an FInputCaptureUpdate from BeginCapture() and UpdateCapture(), which indicates to the InputRouter what the Behavior would like to have happen.
- L134 _public member_ `EInputCaptureState State;` — Indicates what capture state the Behavior wants to transition to
- L136 _public member_ `UInputBehavior* Source;` — Which Behavior did this update come from
- L138 _public member_ `FInputCaptureData Data;` — custom data for the active capture that should be propagated to next UpdateCapture() call
- L146 _public function_ `static FInputCaptureUpdate Begin(UInputBehavior* SourceBehavior, EInputCaptureSide WhichSide, void* CustomData = nullptr)` — Create a begin-capturing instance of FInputCaptureUpdate @param Source UInputBehavior that is returning this update @param Which Which side we are capturing on @param CustomData client-provided data that will be passed to UInputBehavior::UpdateCapture() calls. Client owns this memory!
- L152 _public function_ `static FInputCaptureUpdate Continue()` — Create a default continue-capturing instance of FInputCaptureUpdate
- L157 _public function_ `static FInputCaptureUpdate End()` — Create a default end-capturing instance of FInputCaptureUpdate
- L162 _public function_ `static FInputCaptureUpdate Ignore()` — Create a default ignore-capturing instance of FInputCaptureUpdate
- L173 _public function_ `FInputCaptureUpdate( EInputCaptureState StateIn, UInputBehavior* SourceBehaviorIn, EInputCaptureSide WhichSideIn, void* CustomData = nullptr )` — @param StateIn desired capture state @param Source UInputBehavior that is returning this update @param Which Which side we are capturing on @param CustomData client-provided data that will be passed to UInputBehavior::UpdateCapture() calls. Client owns this memory!

#### struct `FInputCapturePriority`  
`struct FInputCapturePriority`  
_L188-247_
- desc: Each UInputBehavior provides a priority that is used to help resolve situations when multiple Behaviors want to capture based on the same input event
- L190 _public member_ `static constexpr int DEFAULT_GIZMO_PRIORITY = 50;`
- L191 _public member_ `static constexpr int DEFAULT_TOOL_PRIORITY = 100;`
- L212 _public member_ `static constexpr int BINDING_COMPLEXITY_PRIORITY_STEP = 9;` — The binding complexity priority convention is a solution to the problem of ensuring the right behavior gets capture. Take the case of one behavior looking for LMB and another looking for Alt+LMB. If they have the same priority, which behavior gets capture is effectively non-deterministic. Priority would then need to be hand-tuned relative to each other, an inherently brittle task. If all behaviors agree that that additional binding complexity increases capture priority by a set amount, all they must do is correctly publish their priority by this convention, and they will win out over less complex behaviors and gracefully lose to more complex behaviors. An alternative discussed and discarded was to have behaviors assert their negative bindings. In this mode, a behavior wouldn't just look for LMB, it would look for LMB as well as NOT RMB, MMB, Ctrl, Alt, Shift, etc. This was rejected. Knowing how much to negatively assert is not well defined. Additionally, users often expect that pressing (for example) Alt+LMB will trigger an LMB action if nothing is bound to Alt+LMB. The value of BINDING_COMPLEXITY_PRIORITY_STEP can be increased to give more wiggle room for nuanced behavior layering. As of writing, this number is intended such that `DEFAULT_TOOL_PRIORITY - BINDING_COMPLEXITY_PRIORITY_STEP * 5 > DEFAULT_GIZMO_PRIORITY`. The actual value should be considered experimental.
- L215 _public member_ `int Priority;` — Constant priority value
- L217 _public function_ `FInputCapturePriority(int priority = DEFAULT_TOOL_PRIORITY)`
- L223 _public function_ `FInputCapturePriority MakeLower(int DeltaAmount = 1) const` — @return a priority lower than this priority
- L229 _public function_ `FInputCapturePriority MakeHigher(int DeltaAmount = 1) const` — @return a priority higher than this priority
- L234 _public function_ `FInputCapturePriority ApplyBindingComplexity(int InComplexity) const`

#### class `UInputBehavior`  
`class UInputBehavior : public UObject`  
_L274-355_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UObject`
- desc: An InputBehavior implements a state machine for a user interaction. The InputRouter maintains a set of active Behaviors, and when new input events occur, it calls WantsCapture() to check if the Behavior would like to begin capturing the applicable input event stream (eg for a mouse, one or both VR controllers, etc). If the Behavior acquires capture, UpdateCapture() is called until the Behavior indicates that it wants to release the device, or until the InputRouter force-terminates the capture via ForceEndCapture(). For example, something like ButtonSetClickBehavior might work as follows: - in WantsCapture(), if left mouse is pressed and a button is under cursor, return Begin, otherwise Ignore - in BeginCapture(), save identifier for button that is under cursor - in UpdateCapture() - if left mouse is down, return Continue - if left mouse is released: - if saved button is still under cursor, call button.Clicked() - return End Written sufficiently generically, the above Behavior doesn't need to know about buttons, it just needs to know how to hit-test the clickable object(s). Similarly separate Behaviors can be written for mouse, VR, touch, gamepad, etc. Implementing interactions in this way allows the input handling to be separated from functionality.
- L279 _public prototype_ `UInputBehavior();`
- L282 _public prototype_ `virtual FInputCapturePriority GetPriority();` — The priority is used to resolve situations where multiple behaviors want the same capture
- L285 _public prototype_ `virtual void SetDefaultPriority(const FInputCapturePriority& Priority);` — Configure the default priority of an instance of this behavior
- L288 _public prototype_ `virtual EInputDevices GetSupportedDevices();` — Which device types does this Behavior support
- L291 _public prototype_ `virtual FInputCaptureRequest WantsCapture(const FInputDeviceState& InputState);` — Given the input state, does this Behavior want to begin capturing some input devices?
- L294 _public prototype_ `virtual FInputCaptureUpdate BeginCapture( const FInputDeviceState& InputState, EInputCaptureSide eSide );` — Called after WantsCapture() returns a capture request that was accepted
- L302 _public prototype_ `virtual FInputCaptureUpdate UpdateCapture( const FInputDeviceState& InputState, const FInputCaptureData& CaptureData );` — Called for each new input event during a capture sequence. Return Continue to keep capturing, or End to finish capturing.
- L307 _public prototype_ `virtual void ForceEndCapture(const FInputCaptureData& CaptureData);` — If this is called, the Behavior has forcibly lost capture (eg due to app losing focus for example) and needs to clean up accordingly
- L314 _public prototype_ `virtual bool WantsHoverEvents();` — return true if this Behavior supports hover (ie passive input events)
- L317 _public prototype_ `virtual FInputCaptureRequest WantsHoverCapture(const FInputDeviceState& InputState);` — Given the input state, does this Behavior want to begin capturing some input devices for hover
- L320 _public prototype_ `virtual FInputCaptureUpdate BeginHoverCapture( const FInputDeviceState& InputState, EInputCaptureSide eSide );` — Called after WantsHoverCapture() returns a capture request that was accepted
- L325 _public prototype_ `virtual FInputCaptureUpdate UpdateHoverCapture(const FInputDeviceState& InputState);` — Called on each new hover input event, ie if no other behavior is actively capturing input
- L328 _public prototype_ `virtual void EndHoverCapture();` — If a different hover capture begins, focus is lost, a tool starts, etc, any active hover visualization needs to terminate
- L334 _public prototype_ `virtual bool WantsForceEndCapture();` — When this function returns true, this behavior will always receive ForceEndCapture calls even when it is not actively capturing. This is useful for behaviors that do not capture, but hold state (ex. Key Modifiers) and want to be notified when to clear that state.
- L350 _protected member_ `FInputCapturePriority DefaultPriority;` — priority returned by GetPriority()

#### Free symbols / members of external scopes

- L239 _function_ `friend bool operator<(const FInputCapturePriority& l, const FInputCapturePriority& r)`
- L243 _function_ `friend bool operator==(const FInputCapturePriority& l, const FInputCapturePriority& r)`

### `Source/Runtime/InteractiveToolsFramework/Public/InputBehaviorSet.h` (Public)


#### struct `FBehaviorInfo`  
`struct FBehaviorInfo`  
_L25-43_
- reflection: `USTRUCT()`
- desc: This is an internal structure used by UInputBehaviorSet.
- L31 _public member_ `TObjectPtr<UInputBehavior> Behavior = nullptr;` — `UPROPERTY()` — Reference to a Behavior
- L34 _public member_ `void* Source = nullptr;` — Source object that provided this Behavior
- L37 _public member_ `FString Group;` — Group identifier for this Behavior

#### class `UInputBehaviorSet`  
`class UInputBehaviorSet : public UObject`  
_L58-157_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UObject`
- desc: UInputBehaviorSet manages a set of UInputBehaviors, and provides various functions to query and forward events to the set. Tools and Widgets provide instances of this via IInputBehaviorSource, and UInputRouter collects and manages them (see comments there) Behaviors in the set each have a source pointer and group tag, which allows sets of behaviors to be managed together. For example one UInputBehaviorSet can be merged into another and removed later.
- L63 _public prototype_ `UInputBehaviorSet();`
- L64 _public prototype_ `virtual ~UInputBehaviorSet();`
- L72 _public prototype_ `virtual bool IsEmpty() const;` — @return true if there are no Behaviors in set
- L80 _public prototype_ `virtual void Add(UInputBehavior* Behavior, void* Source = nullptr, const FString& GroupName = "");` — Add a Behavior to the set @param Behavior Behavior to add to set @param Source pointer to owning object, used only to identify Behavior later @param GroupName string identifier for this Behavior or group of Behaviors
- L88 _public prototype_ `virtual void Add(const UInputBehaviorSet* OtherSet, void* NewSource = nullptr, const FString& NewGroupName = "");` — Merge another BehaviorSet into this Set @param OtherSet Set of Behaviors to add to this Set @param Source pointer to owning object, used only to identify Behavior later. If nullptr, source is copied from other Set. @param NewGroupName string identifier for this Behavior or group of Behaviors. If empty string, group is copied from other Set.
- L95 _public prototype_ `virtual bool Remove(UInputBehavior* Behavior);` — Remove a Behavior from the Set @param Behavior Behavior to remove @return true if Behavior was found and removed
- L101 _public prototype_ `virtual bool RemoveByGroup(const FString& GroupName);` — Remove a group of Behaviors from the Set @param GroupName name of group, all Behaviors that were added with this GroupName are removed @return true if any Behaviors were found and removed
- L107 _public prototype_ `virtual bool RemoveBySource(void* Source);` — Remove a group of Behaviors from the Set @param Source source object pointer, all Behaviors that were added with this Source pointer are removed. @return true if any Behaviors were found and removed
- L111 _public prototype_ `virtual void RemoveAll();` — Remove all Behaviors from the set
- L124 _public prototype_ `virtual void CollectWantsCapture(const FInputDeviceState& InputState, TArray<FInputCaptureRequest>& ResultOut);` — Call UInputBehavior::WantsCapture() on each valid Behavior and collect up the requests that indicated a Capture was desired. @param InputState current input device state information @param ResultOut returned set of non-Ignoring FInputCaptureRequests returned by Behaviors
- L131 _public prototype_ `virtual void CollectWantsHoverCapture(const FInputDeviceState& InputState, TArray<FInputCaptureRequest>& ResultOut);` — Call UInputBehavior::WantsCapture() on each valid Behavior and collect up the requests that indicated a Capture was desired. @param InputState current input device state information @param ResultOut returned set of non-Ignoring FInputCaptureRequests returned by Behaviors
- L136 _public prototype_ `virtual void CollectWantsForceEndCapture(TArray<UInputBehavior*>& ResultOut);` — Call UInputBehavior::WantsForceEndCapture on each valid Behavior and collect up the requests that indicated that a ForceEndCapture was desired.
- L143 _protected member_ `TArray<FBehaviorInfo> Behaviors;` — `UPROPERTY()` — Current set of known Behaviors
- L148 _protected prototype_ `virtual void BehaviorsModified();` — called internally when Behaviors list is updated, to re-sort by Priority, etc (@todo: and emit change event)
- L152 _protected function_ `bool SupportsInputType(UInputBehavior* Behavior, const FInputDeviceState& InputState)` — @return true if Behavior supports InputState.InputDevice

#### class `UInputBehaviorSource`  
`class UInputBehaviorSource : public UInterface`  
_L165-168_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`
- desc: UInterface for IInputBehavior

#### class `IInputBehaviorSource`  
`class IInputBehaviorSource`  
_L176-185_
- desc: UObjects that implement IInputBehaviorSource have an UInputBehaviorSet that they can provide (to UInputRouter, primarily) @todo callback/delegate for when the provided InputBehaviorSet changes
- L184 _public prototype_ `virtual const UInputBehaviorSet* GetInputBehaviors() const = 0;` — @return The current UInputBehaviorSet for this Source

#### class `ULocalInputBehaviorSource`  
`class ULocalInputBehaviorSource : public UObject, public IInputBehaviorSource`  
_L194-204_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UObject,IInputBehaviorSource`
- desc: An implementation of IInputBehaviorSource that forwards to a user provided-lambda, to allow a tool to supply a behavior source different from the one it is implementing itself. Useful, for instance, when a tool wants to supply different behaviors to separate input routers.
- L200 _public function_ `TUniqueFunction<const UInputBehaviorSet* ()> GetInputBehaviorsFunc = []()`
- L200 _public member_ `TUniqueFunction<const UInputBehaviorSet* ()> GetInputBehaviorsFunc = []() { return nullptr; };`
- L203 _public function_ `virtual const UInputBehaviorSet* GetInputBehaviors() const override` — IInputBehaviorSource

#### Free symbols / members of external scopes

- L39 _function_ `friend bool operator<(const FBehaviorInfo& l, const FBehaviorInfo& r)`

### `Source/Runtime/InteractiveToolsFramework/Public/InputRouter.h` (Public)


#### class `UInputRouter`  
`class UInputRouter : public UObject`  
_L38-127_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UObject`
- desc: UInputRouter mediates between a higher-level input event source (eg like an FEdMode) and a set of InputBehaviors that respond to those events. Sets of InputBehaviors are registered, and then PostInputEvent() is called for each event. Internally one of the active Behaviors may "capture" the event stream. Separate "Left" and "Right" captures are supported, which means that (eg) an independent capture can be tracked for each VR controller. If the input device supports "hover",  PostHoverInputEvent() will forward hover events to InputBehaviors that also support it.
- L45 _protected prototype_ `UInputRouter();`
- L48 _protected prototype_ `virtual void Initialize(IToolsContextTransactionsAPI* TransactionsAPI);` — Initialize the InputRouter with the necessary Context-level state. UInteractiveToolsContext calls this, you should not.
- L51 _protected prototype_ `virtual void Shutdown();` — Shutdown the InputRouter. Called by UInteractiveToolsContext.
- L55 _public prototype_ `virtual void RegisterSource(IInputBehaviorSource* Source);` — Add a new behavior Source. Behaviors from this source will be added to the active behavior set.
- L58 _public prototype_ `virtual void DeregisterSource(IInputBehaviorSource* Source);` — Remove Behaviors from this Source from the active set
- L61 _public prototype_ `virtual bool PostInputEvent(const FInputDeviceState& Input);` — Insert a new input event which is used to check for new captures, or forwarded to active capture
- L64 _public prototype_ `virtual bool HasActiveMouseCapture() const;` — Returns true if there is an active mouse capture
- L69 _public prototype_ `virtual void PostHoverInputEvent(const FInputDeviceState& Input);` — Insert a new hover input event which is forwarded to all hover-enabled Behaviors
- L72 _public prototype_ `virtual void ForceTerminateSource(IInputBehaviorSource* Source);` — If this Behavior is capturing, call ForceEndCapture() to notify that we are taking capture away
- L75 _public prototype_ `virtual void ForceTerminateAll();` — Terminate any active captures and end all hovers
- L81 _public member_ `bool bAutoInvalidateOnHover;` — `UPROPERTY()` — If true, then we post an Invalidation (ie redraw) request if any active InputBehavior responds to Hover events (default false)
- L85 _public member_ `bool bAutoInvalidateOnCapture;` — `UPROPERTY()` — If true, then we post an Invalidation (ie redraw) request on every captured input event (default false)
- L89 _protected member_ `IToolsContextTransactionsAPI* TransactionsAPI;`
- L92 _protected member_ `TObjectPtr<UInputBehaviorSet> ActiveInputBehaviors;` — `UPROPERTY()`
- L94 _protected member_ `UInputBehavior* ActiveKeyboardCapture = nullptr;`
- L95 _protected member_ `void* ActiveKeyboardCaptureOwner = nullptr;`
- L96 _protected member_ `FInputCaptureData ActiveKeyboardCaptureData;`
- L98 _protected member_ `UInputBehavior* ActiveLeftCapture = nullptr;`
- L99 _protected member_ `void* ActiveLeftCaptureOwner = nullptr;`
- L100 _protected member_ `FInputCaptureData ActiveLeftCaptureData;`
- L102 _protected member_ `UInputBehavior* ActiveRightCapture = nullptr;`
- L103 _protected member_ `void* ActiveRightCaptureOwner = nullptr;`
- L104 _protected member_ `FInputCaptureData ActiveRightCaptureData;`
- L106 _protected prototype_ `virtual void PostInputEvent_Keyboard(const FInputDeviceState& Input);`
- L107 _protected prototype_ `void CheckForKeyboardCaptures(const FInputDeviceState& Input);`
- L108 _protected prototype_ `void HandleCapturedKeyboardInput(const FInputDeviceState& Input);`
- L110 _protected prototype_ `virtual void PostInputEvent_Mouse(const FInputDeviceState& Input);`
- L111 _protected prototype_ `void CheckForMouseCaptures(const FInputDeviceState& Input);`
- L112 _protected prototype_ `void HandleCapturedMouseInput(const FInputDeviceState& Input);`
- L118 _protected member_ `UInputBehavior* ActiveLeftHoverCapture = nullptr;`
- L119 _protected member_ `void* ActiveLeftHoverCaptureOwner = nullptr;`
- L121 _protected member_ `FInputDeviceState LastMouseInputState;`
- L123 _protected prototype_ `void TerminateHover(EInputCaptureSide Side);`
- L124 _protected prototype_ `bool ProcessMouseHover(const FInputDeviceState& Input);`
- L125 _protected prototype_ `bool UpdateExistingHoverCaptureIfPresent(const FInputDeviceState& Input);`
- L126 _protected prototype_ `void OnApplicationFocusChanged(bool bInIsFocused);`

### `Source/Runtime/InteractiveToolsFramework/Public/InputState.h` (Public)


#### enum `EInputDevices`  
`enum class EInputDevices`  
_L29-41_
- reflection: `UENUM()`
- desc: Input event data can be applicable to many possible input devices. These flags are used to indicate specific or sets of device types.
- L31 _public enumerator_ `None = 0`
- L32 _public enumerator_ `Keyboard = 1`
- L33 _public enumerator_ `Mouse = 2`
- L34 _public enumerator_ `Gamepad = 4`
- L36 _public enumerator_ `OculusTouch = 8`
- L37 _public enumerator_ `HTCViveWands = 16`
- L38 _public enumerator_ `AnySpatialDevice = OculusTouch | HTCViveWands`
- L40 _public enumerator_ `TabletFingers = 1024`

#### struct `FInputRayHit`  
`struct FInputRayHit`  
_L51-128_
- reflection: `USTRUCT(BlueprintType)`
- desc: FInputRayHit is returned by various hit-test interface functions. Generally this is intended to be returned as the result of a hit-test with a FInputDeviceRay
- L57 _public member_ `bool bHit;` — `UPROPERTY(BlueprintReadWrite, Category = InputRayHit)` — true if ray hit something, false otherwise
- L61 _public member_ `double HitDepth;` — `UPROPERTY(BlueprintReadWrite, Category = InputRayHit)` — distance along ray at which intersection occurred
- L65 _public member_ `FVector HitNormal;` — `UPROPERTY(BlueprintReadWrite, Category = InputRayHit)` — Normal at hit point, if available
- L69 _public member_ `bool bHasHitNormal;` — `UPROPERTY(BlueprintReadWrite, Category = InputRayHit)` — True if HitNormal was set
- L73 _public member_ `int32 HitIdentifier;` — `UPROPERTY(BlueprintReadWrite, Category = InputRayHit)` — Client-defined integer identifier for hit object/element/target/etc
- L79 _public member_ `void* HitOwner;` — Client-defined pointer for hit object/element/target/etc. HitOwner and HitObject should be set to the same pointer if the HitOwner derives from UObject.
- L86 _public member_ `TWeakObjectPtr<UObject> HitObject;` — `UPROPERTY(BlueprintReadWrite, Category = InputRayHit)` — Client-defined pointer for UObject-derived hit owners. HitOwner and HitObject should be set to the same pointer if the HitOwner derives from UObject.
- L89 _public function_ `void SetHitObject(UObject* InHitObject)` — Set hit object, will also set hit owner to the same value
- L95 _public function_ `FInputRayHit()`
- L106 _public function_ `explicit FInputRayHit(double HitDepthIn)`
- L117 _public function_ `explicit FInputRayHit(double HitDepthIn, const FVector& HitNormalIn)`

#### struct `FDeviceButtonState`  
`struct FDeviceButtonState`  
_L143-192_
- reflection: `USTRUCT(BlueprintType)`
- desc: Current State of a physical device button (mouse, key, etc) at a point in time. Each "click" of a button should involve at minimum two separate state events, one where bPressed=true and one where bReleased=true. Each of these states should occur only once. In addition there may be additional frames where the button is held down and bDown=true and bPressed=false.
- L149 _public member_ `FKey Button;` — `UPROPERTY(transient, BlueprintReadWrite, Category = DeviceButtonState)` — Button identifier
- L153 _public member_ `bool bPressed;` — `UPROPERTY(transient, BlueprintReadWrite, Category = DeviceButtonState)` — Was the button pressed down this frame. This should happen once per "click"
- L157 _public member_ `bool bDown;` — `UPROPERTY(transient, BlueprintReadWrite, Category = DeviceButtonState)` — Is the button currently pressed down. This should be true every frame the button is pressed.
- L161 _public member_ `bool bReleased;` — `UPROPERTY(transient, BlueprintReadWrite, Category = DeviceButtonState)` — Was the button released this frame. This should happen once per "click"
- L165 _public member_ `bool bDoubleClicked;` — `UPROPERTY(Transient, BlueprintReadWrite, Category = DeviceButtonState)` — Was the button double clicked this frame. This should happen only once per "double click"
- L167 _public function_ `FDeviceButtonState()`
- L173 _public function_ `FDeviceButtonState(const FKey& ButtonIn)`
- L180 _public function_ `void SetStates(bool bPressedIn, bool bDownIn, bool bReleasedIn, bool bDoubleClickedIn = false)` — Update the states of this button
- L188 _public function_ `bool IsValid() const`

#### struct `FKeyboardInputDeviceState`  
`struct FKeyboardInputDeviceState`  
_L201-208_
- reflection: `USTRUCT(BlueprintType)`
- desc: Current state of active keyboard key at a point in time @todo would be useful to track set of active keys
- L207 _public member_ `FDeviceButtonState ActiveKey;` — `UPROPERTY(transient, BlueprintReadWrite, Category = KeyboardInputDeviceState)` — state of active key that was modified (ie press or release)

#### struct `FMouseInputDeviceState`  
`struct FMouseInputDeviceState`  
_L216-273_
- reflection: `USTRUCT(BlueprintType)`
- desc: Current State of a physical Mouse device at a point in time.
- L222 _public member_ `FDeviceButtonState Left;` — `UPROPERTY(transient, BlueprintReadWrite, Category = MouseInputDeviceState)` — State of the left mouse button
- L226 _public member_ `FDeviceButtonState Middle;` — `UPROPERTY(transient, BlueprintReadWrite, Category = MouseInputDeviceState)` — State of the middle mouse button
- L230 _public member_ `FDeviceButtonState Right;` — `UPROPERTY(transient, BlueprintReadWrite, Category = MouseInputDeviceState)` — State of the right mouse button
- L234 _public member_ `float WheelDelta;` — `UPROPERTY(transient, BlueprintReadWrite, Category = MouseInputDeviceState)` — Change in 'ticks' of the mouse wheel since last state event
- L238 _public member_ `FVector2D Position2D;` — `UPROPERTY(transient, BlueprintReadWrite, Category = MouseInputDeviceState)` — Current 2D position of the mouse, in application-defined coordinate system
- L242 _public member_ `FVector2D Delta2D;` — `UPROPERTY(transient, BlueprintReadWrite, Category = MouseInputDeviceState)` — Change in 2D mouse position from last state event
- L246 _public member_ `FRay WorldRay;` — `UPROPERTY(transient, BlueprintReadWrite, Category = MouseInputDeviceState)` — Ray into current 3D scene at current 2D mouse position
- L250 _public member_ `FVector2D UnboundedPosition2D;` — `UPROPERTY(transient, BlueprintReadWrite, Category = MouseInputDeviceState)` — The 2D position of the mouse, unconstrained by screen real-estate. Computed by summing unbound deltas.
- L254 _public member_ `FVector2D UnboundedMouseDelta2D;` — `UPROPERTY(transient, BlueprintReadWrite, Category = MouseInputDeviceState)` — Change in 2D mouse position, valid also for movements outside the display bounds
- L258 _public member_ `FRay UnboundedWorldRay;` — `UPROPERTY(transient, BlueprintReadWrite, Category = MouseInputDeviceState)` — Ray into current 3D scene at current unbounded 2D mouse position
- L260 _public function_ `FMouseInputDeviceState()`

#### struct `FInputDeviceState`  
`struct FInputDeviceState`  
_L283-384_
- reflection: `USTRUCT(BlueprintType, MinimalAPI)`
- desc: Current state of physical input devices at a point in time. Assumption is that the state refers to a single physical input device, ie InputDevice field is a single value of EInputDevices and not a combination.
- L292 _public member_ `EInputDevices InputDevice;` — `UPROPERTY(transient, BlueprintReadWrite, Category = MouseInputDeviceState)` — Which InputDevice member is valid in this state
- L300 _public member_ `bool bShiftKeyDown;` — `UPROPERTY(transient, BlueprintReadWrite, Category = MouseInputDeviceState)` — Is they keyboard SHIFT modifier key currently pressed down
- L304 _public member_ `bool bAltKeyDown;` — `UPROPERTY(transient, BlueprintReadWrite, Category = MouseInputDeviceState)` — Is they keyboard ALT modifier key currently pressed down
- L308 _public member_ `bool bCtrlKeyDown;` — `UPROPERTY(transient, BlueprintReadWrite, Category = MouseInputDeviceState)` — Is they keyboard CTRL modifier key currently pressed down
- L312 _public member_ `bool bCmdKeyDown;` — `UPROPERTY(transient, BlueprintReadWrite, Category = MouseInputDeviceState)` — Is they keyboard CMD modifier key currently pressed down (only on Apple devices)
- L316 _public member_ `FKeyboardInputDeviceState Keyboard;` — `UPROPERTY(transient, BlueprintReadWrite, Category = MouseInputDeviceState)` — Current state of Keyboard device, if InputDevice == EInputDevices::Keyboard
- L320 _public member_ `FMouseInputDeviceState Mouse;` — `UPROPERTY(transient, BlueprintReadWrite, Category = MouseInputDeviceState)` — Current state of Mouse device, if InputDevice == EInputDevices::Mouse
- L322 _public function_ `FInputDeviceState()`
- L331 _public function_ `void SetModifierKeyStates(bool bShiftDown, bool bAltDown, bool bCtrlDown, bool bCmdDown)` — Update keyboard modifier key states
- L343 _public function_ `bool IsFromDevice(EInputDevices DeviceType) const` — @param DeviceType Combination of device-type flags @return true if this input state is for an input device that matches the query flags
- L362 _public function_ `static bool IsShiftKeyDown(const FInputDeviceState& InputState)` — @return true if shift key is down in input state
- L368 _public function_ `static bool IsCtrlKeyDown(const FInputDeviceState& InputState)` — @return true if ctrl key is down in input state
- L374 _public function_ `static bool IsAltKeyDown(const FInputDeviceState& InputState)` — @return true if alt key is down in input state
- L380 _public function_ `static bool IsCmdKeyDown(const FInputDeviceState& InputState)` — @return true if Apple Command key is down in input state

#### struct `FInputDeviceRay`  
`struct FInputDeviceRay`  
_L395-449_
- reflection: `USTRUCT(BlueprintType)`
- desc: FInputDeviceRay represents a 3D ray created based on an input device. If the device is a 2D input device like a mouse, then the ray may have an associated 2D screen position.
- L401 _public member_ `FRay WorldRay;` — `UPROPERTY(transient, BlueprintReadWrite, Category = InputDeviceRay)` — 3D ray in 3D scene, in world coordinates
- L405 _public member_ `bool bHas2D = false;` — `UPROPERTY(transient, BlueprintReadWrite, Category = InputDeviceRay)` — If true, WorldRay has 2D device position coordinates
- L409 _public member_ `FVector2D ScreenPosition;` — `UPROPERTY(transient, BlueprintReadWrite, Category = InputDeviceRay)` — 2D device position coordinates associated with the ray
- L412 _public function_ `FInputDeviceRay()` — this is required for a USTRUCT
- L419 _public function_ `explicit FInputDeviceRay(const FRay& WorldRayIn)`
- L426 _public function_ `FInputDeviceRay(const FRay& WorldRayIn, const FVector2D& ScreenPositionIn)`
- L433 _public function_ `FInputDeviceRay(const FInputDeviceState& Input)`

#### Free symbols / members of external scopes

- L42 _prototype_ `ENUM_CLASS_FLAGS(EInputDevices);`
- L288 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FDeviceButtonState, FGetDeviceButtonState, const FKey&);`

### `Source/Runtime/InteractiveToolsFramework/Public/InteractionMechanic.h` (Public)


#### class `UInteractionMechanic`  
`class UInteractionMechanic : public UObject`  
_L29-70_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UObject`
- desc: A UInteractionMechanic implements a "user interaction". This is generally a subset of an InteractiveTool, for example an interaction to draw a polygon could be used in many tools, but requires handling input events and converting them to click points on a plane, handling various cases like closing a loop, undo/redo of points, etc. Ideally all these aspects should be able to be wrapped up in an UInteractionMechanic that multiple Tools can use. (This class is still a work in progress)
- L34 _public prototype_ `UInteractionMechanic();`
- L39 _public prototype_ `virtual void Setup(UInteractiveTool* ParentTool);` — Called to initialize the InteractionMechanic
- L44 _public prototype_ `virtual void Shutdown();` — Called to clean up the InteractionMechanic
- L50 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI);` — Allow the Mechanic to do any custom drawing (ie via PDI/RHI) @param RenderAPI Abstraction that provides access to Rendering in the current ToolsContext
- L55 _public prototype_ `virtual void Tick(float DeltaTime);` — ALlow the Mechanic to Tick
- L58 _protected member_ `TWeakObjectPtr<UInteractiveTool> ParentTool;`
- L60 _protected prototype_ `UInteractiveTool* GetParentTool() const;`
- L66 _protected prototype_ `virtual void AddToolPropertySource(UInteractiveToolPropertySet* PropertySet);` — Add a PropertySet object for this Mechanic to parent Tool @param PropertySet Property Set object to add
- L69 _protected prototype_ `virtual bool SetToolPropertySourceEnabled(UInteractiveToolPropertySet* PropertySet, bool bEnabled);` — Enable/Disable a PropertySet object for the parent tool.

### `Source/Runtime/InteractiveToolsFramework/Public/InteractiveCommand.h` (Public)


#### class `UInteractiveCommandArguments`  
`class UInteractiveCommandArguments : public UObject`  
_L18-30_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: UInteractiveCommandArguments are arguments passed to a UInteractiveCommand. Subclasses of UInteractiveCommand will generally be paired with subclasses of UInteractiveCommandArguments. The base UInteractiveCommandArguments provides support for transactions via a IToolsContextTransactionsAPI
- L23 _public function_ `virtual void SetTransactionsAPI(IToolsContextTransactionsAPI* TransactionsAPIIn)`
- L24 _public function_ `virtual bool HasTransactionsAPI() const`
- L25 _public function_ `virtual IToolsContextTransactionsAPI* GetTransactionsAPI() const`
- L28 _protected member_ `IToolsContextTransactionsAPI* TransactionsAPI = nullptr;`

#### class `UInteractiveCommandResult`  
`class UInteractiveCommandResult : public UObject`  
_L38-42_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: UInteractiveCommandResult subclasses are returned from UInteractiveCommands, to allow commands to return custom information.

#### class `UInteractiveCommand`  
`class UInteractiveCommand : public UObject`  
_L52-81_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UObject`
- desc: A UInteractiveCommand is an atomic action that can be executed via some user interaction. For example clicking a button that deletes an active selection can be considered an Interactive Command. This differs from an Interactive Tool in that there is no ongoing user interaction once the command has been initiated.
- L61 _public function_ `virtual FText GetCommandShortString() const` — @return a short text string that can be used for the command in (eg) Editor transaction/undo toasts
- L69 _public function_ `virtual bool CanExecuteCommand(UInteractiveCommandArguments* Arguments)` — @return true if it is safe to call ExecuteCommand() with the given Arguments
- L78 _public function_ `virtual void ExecuteCommand(UInteractiveCommandArguments* Arguments, UInteractiveCommandResult** Result = nullptr)` — Execute the command with the given Arguments @param Result optional command result. Command would have to allocate the UInteractiveCommandResult object to return it, but is not required to. Caller should not assume that a non-null Result is necessarily returned.

### `Source/Runtime/InteractiveToolsFramework/Public/InteractiveGizmo.h` (Public)


#### class `UInteractiveGizmo`  
`class UInteractiveGizmo : public UObject, public IInputBehaviorSource`  
_L28-101_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UObject,IInputBehaviorSource`
- desc: UInteractiveGizmo is the base class for all Gizmos in the InteractiveToolsFramework. @todo callback/delegate for if/when .InputBehaviors changes @todo callback/delegate for when Gizmo properties change
- L33 _public prototype_ `UInteractiveGizmo();`
- L38 _public prototype_ `virtual void Setup();` — Called by GizmoManager to initialize the Gizmo *after* GizmoBuilder::BuildGizmo() has been called
- L43 _public prototype_ `virtual void Shutdown();` — Called by GizmoManager to shut down the Gizmo
- L49 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI);` — Allow the Gizmo to do any custom drawing (ie via PDI/RHI) @param RenderAPI Abstraction that provides access to Rendering in the current ToolsContext
- L56 _public prototype_ `virtual void DrawHUD( FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI );` — Allow the Gizmo to do any custom screen space drawing @param Canvas the FCanvas to use to do the drawing @param RenderAPI Abstraction that provides access to Rendering in the current ToolsContext
- L62 _public prototype_ `virtual void Tick(float DeltaTime);` — Allow the Gizmo to do any necessary processing on Tick @param DeltaTime the time delta since last tick
- L69 _public prototype_ `virtual UInteractiveGizmoManager* GetGizmoManager() const;` — @return GizmoManager that owns this Gizmo
- L81 _public prototype_ `virtual void AddInputBehavior(UInputBehavior* Behavior);` — Add an input behavior for this Gizmo @param Behavior behavior to add
- L87 _public prototype_ `virtual void RemoveInputBehavior(UInputBehavior* Behavior);` — Remove an input behavior from this Gizmo @param Behavior behavior to add
- L92 _public prototype_ `virtual const UInputBehaviorSet* GetInputBehaviors() const;` — @return Current input behavior set.
- L100 _protected member_ `TObjectPtr<UInputBehaviorSet> InputBehaviors;` — `UPROPERTY()` — The current set of InputBehaviors provided by this Gizmo

#### enum `ETransformGizmoSubElements`  
`enum class ETransformGizmoSubElements`  
_L110-150_
- reflection: `UENUM()`
- desc: ETransformGizmoSubElements identifies the sub-elements of a standard 3-axis transformation Gizmo. Used by GizmoManager to customize UCombinedTransformGizmo instances.
- L112 _public enumerator_ `None = 0`
- L114 _public enumerator_ `TranslateAxisX = 1<<1`
- L115 _public enumerator_ `TranslateAxisY = 1<<2`
- L116 _public enumerator_ `TranslateAxisZ = 1<<3`
- L117 _public enumerator_ `TranslateAllAxes = TranslateAxisX | TranslateAxisY | TranslateAxisZ`
- L119 _public enumerator_ `TranslatePlaneXY = 1<<4`
- L120 _public enumerator_ `TranslatePlaneXZ = 1<<5`
- L121 _public enumerator_ `TranslatePlaneYZ = 1<<6`
- L122 _public enumerator_ `TranslateAllPlanes = TranslatePlaneXY | TranslatePlaneXZ | TranslatePlaneYZ`
- L124 _public enumerator_ `RotateAxisX = 1<<7`
- L125 _public enumerator_ `RotateAxisY = 1<<8`
- L126 _public enumerator_ `RotateAxisZ = 1<<9`
- L127 _public enumerator_ `RotateAllAxes = RotateAxisX | RotateAxisY | RotateAxisZ`
- L129 _public enumerator_ `ScaleAxisX = 1<<10`
- L130 _public enumerator_ `ScaleAxisY = 1<<11`
- L131 _public enumerator_ `ScaleAxisZ = 1<<12`
- L132 _public enumerator_ `ScaleAllAxes = ScaleAxisX | ScaleAxisY | ScaleAxisZ`
- L134 _public enumerator_ `ScalePlaneYZ = 1<<13`
- L135 _public enumerator_ `ScalePlaneXZ = 1<<14`
- L136 _public enumerator_ `ScalePlaneXY = 1<<15`
- L137 _public enumerator_ `ScaleAllPlanes = ScalePlaneXY | ScalePlaneXZ | ScalePlaneYZ`
- L139 _public enumerator_ `ScaleUniform = 1<<16`
- L141 _public enumerator_ `FreeTranslate = 1<<17`
- L142 _public enumerator_ `FreeRotate = 1<<18`
- L144 _public enumerator_ `StandardTranslateRotate = TranslateAllAxes | TranslateAllPlanes | RotateAllAxes | FreeTranslate | FreeRotate`
- L146 _public enumerator_ `TranslateRotateUniformScale = TranslateAllAxes | TranslateAllPlanes | RotateAllAxes | ScaleUniform | FreeTranslate | FreeRotate`
- L148 _public enumerator_ `FullTranslateRotateScale = TranslateAllAxes | TranslateAllPlanes | RotateAllAxes | ScaleAllAxes | ScaleAllPlanes | ScaleUniform | FreeTranslate | FreeRotate`

#### Free symbols / members of external scopes

- L151 _prototype_ `ENUM_CLASS_FLAGS(ETransformGizmoSubElements);`

### `Source/Runtime/InteractiveToolsFramework/Public/InteractiveGizmoBuilder.h` (Public)


#### class `UInteractiveGizmoBuilder`  
`class UInteractiveGizmoBuilder : public UObject`  
_L18-34_
- reflection: `UCLASS(Transient, Abstract, MinimalAPI)`
- inherits: `UObject`
- desc: A UInteractiveGizmoBuilder creates a new instance of an InteractiveGizmo (basically this is a Factory). These are registered with the InteractiveGizmoManager, which calls BuildGizmo(). This is an abstract base class, you must subclass it in order to create your particular Gizmo instance
- L29 _public function_ `virtual UInteractiveGizmo* BuildGizmo(const FToolBuilderState& SceneState) const` — Create a new instance of this builder's Gizmo @param SceneState the current scene selection state, etc @return a new instance of the Gizmo, or nullptr on error/failure

### `Source/Runtime/InteractiveToolsFramework/Public/InteractiveGizmoManager.h` (Public)


#### struct `FActiveGizmo`  
`struct FActiveGizmo`  
_L20-29_
- reflection: `USTRUCT()`
- L25 _public member_ `TObjectPtr<UInteractiveGizmo> Gizmo = nullptr;` — `UPROPERTY()`
- L26 _public member_ `FString BuilderIdentifier;`
- L27 _public member_ `FString InstanceIdentifier;`
- L28 _public member_ `void* Owner = nullptr;`

#### class `UInteractiveGizmoManager`  
`class UInteractiveGizmoManager : public UObject, public IToolContextTransactionProvider`  
_L39-256_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UObject,IToolContextTransactionProvider`
- desc: UInteractiveGizmoManager allows users of the Tools framework to create and operate Gizmo instances. For each Gizmo, a (string,GizmoBuilder) pair is registered with the GizmoManager. Gizmos can then be activated via the string identifier.
- L46 _protected prototype_ `UInteractiveGizmoManager();`
- L49 _protected prototype_ `virtual void Initialize(IToolsContextQueriesAPI* QueriesAPI, IToolsContextTransactionsAPI* TransactionsAPI, UInputRouter* InputRouter);` — Initialize the GizmoManager with the necessary Context-level state. UInteractiveToolsContext calls this, you should not.
- L52 _protected prototype_ `virtual void Shutdown();` — Shutdown the GizmoManager. Called by UInteractiveToolsContext.
- L65 _public prototype_ `virtual void RegisterGizmoType(const FString& BuilderIdentifier, UInteractiveGizmoBuilder* Builder);` — Register a new GizmoBuilder @param BuilderIdentifier string used to identify this Builder @param Builder new GizmoBuilder instance
- L72 _public prototype_ `virtual bool DeregisterGizmoType(const FString& BuilderIdentifier);` — Remove a GizmoBuilder from the set of known GizmoBuilders @param BuilderIdentifier identification string that was passed to RegisterGizmoType() @return true if Builder was found and deregistered
- L83 _public prototype_ `virtual UInteractiveGizmo* CreateGizmo(const FString& BuilderIdentifier, const FString& InstanceIdentifier = FString(), void* Owner = nullptr);` — Try to activate a new Gizmo instance @param BuilderIdentifier string used to identify Builder that should be called @param InstanceIdentifier optional client-defined string that can be used to locate this instance (must be unique across all Gizmos) @param Owner void pointer to whatever "owns" this Gizmo. Allows Gizmo to later be deleted using DestroyAllGizmosByOwner() @return new Gizmo instance that has been created and initialized
- L94 _public function_ `template<typename GizmoType> GizmoType* CreateGizmo(const FString& BuilderIdentifier, const FString& InstanceIdentifier = FString(), void* Owner = nullptr)` — Try to activate a new Gizmo instance @param BuilderIdentifier string used to identify Builder that should be called @param InstanceIdentifier optional client-defined string that can be used to locate this instance (must be unique across all Gizmos) @param Owner void pointer to whatever "owns" this Gizmo. Allows Gizmo to later be deleted using DestroyAllGizmosByOwner() @return new Gizmo instance that has been created and initialized, and cast to template type
- L106 _public prototype_ `virtual bool DestroyGizmo(UInteractiveGizmo* Gizmo);` — Shutdown and remove a Gizmo @param Gizmo the Gizmo to shutdown and remove @return true if the Gizmo was found and removed
- L112 _public prototype_ `virtual void DestroyAllGizmosOfType(const FString& BuilderIdentifier);` — Destroy all Gizmos that were created by the identified GizmoBuilder @param BuilderIdentifier the Builder string registered with RegisterGizmoType
- L118 _public prototype_ `virtual void DestroyAllGizmosByOwner(void* Owner);` — Destroy all Gizmos that are owned by the given pointer @param Owner pointer that was passed to CreateGizmo
- L126 _public prototype_ `virtual TArray<UInteractiveGizmo*> FindAllGizmosOfType(const FString& BuilderIdentifier);` — Find all the existing Gizmo instances that were created by the identified GizmoBuilder @param BuilderIdentifier the Builder string registered with RegisterGizmoType @return list of found Gizmos
- L133 _public prototype_ `virtual UInteractiveGizmo* FindGizmoByInstanceIdentifier(const FString& Identifier) const;` — Find the Gizmo that was created with the given instance identifier @param Identifier the InstanceIdentifier that was passed to CreateGizmo() @return the found Gizmo, or null
- L143 _public prototype_ `virtual void DisplayMessage(const FText& Message, EToolMessageLevel Level);` — Post a message via the Transactions API
- L146 _public prototype_ `virtual void PostInvalidation();` — Request an Invalidation via the Transactions API (ie to cause a repaint, etc)
- L152 _public prototype_ `virtual void BeginUndoTransaction(const FText& Description);` — Request that the Context open a Transaction, whatever that means to the current Context @param Description text description of this transaction (this is the string that appears on undo/redo in the UE Editor)
- L155 _public prototype_ `virtual void EndUndoTransaction();` — Request that the Context close and commit the open Transaction
- L158 _public prototype_ `virtual void CancelUndoTransaction() override;` — Request that the Context cancel and revert the open Transaction
- L166 _public prototype_ `virtual void EmitObjectChange(UObject* TargetObject, TUniquePtr<FToolCommandChange> Change, const FText& Description );` — Forward an FChange object to the Context @param TargetObject the object that the FChange applies to @param Change the change object that the Context should insert into the transaction history @param Description text description of this change (this is the string that appears on undo/redo in the UE Editor)
- L174 _public prototype_ `virtual void Tick(float DeltaTime);` — Tick any active Gizmos. Called by UInteractiveToolsContext
- L177 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI);` — Render any active Gizmos. Called by UInteractiveToolsContext.
- L180 _public prototype_ `virtual void DrawHUD( FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI );` — Let active Gizmos do screen space drawing.  Called by UInteractiveToolsContext
- L187 _public function_ `virtual IToolsContextQueriesAPI* GetContextQueriesAPI()` — @return current IToolsContextQueriesAPI
- L192 _public prototype_ `UContextObjectStore* GetContextObjectStore() const;` — @return the context object store from the owning tools context.
- L204 _public prototype_ `virtual void RegisterDefaultGizmos();` — Register default gizmo types
- L212 _public prototype_ `virtual UCombinedTransformGizmo* Create3AxisTransformGizmo(void* Owner = nullptr, const FString& InstanceIdentifier = FString());` — Activate a new instance of the default 3-axis transformation Gizmo. RegisterDefaultGizmos() must have been called first. @param Owner optional void pointer to whatever "owns" this Gizmo. Allows Gizmo to later be deleted using DestroyAllGizmosByOwner() @param InstanceIdentifier optional client-defined *unique* string that can be used to locate this instance @return new Gizmo instance that has been created and initialized
- L221 _public prototype_ `virtual UCombinedTransformGizmo* CreateCustomTransformGizmo(ETransformGizmoSubElements Elements, void* Owner = nullptr, const FString& InstanceIdentifier = FString());` — Activate a new customized instance of the default 3-axis transformation Gizmo, with only certain elements included. RegisterDefaultGizmos() must have been called first. @param Elements flags that indicate which standard gizmo sub-elements should be included @param Owner optional void pointer to whatever "owns" this Gizmo. Allows Gizmo to later be deleted using DestroyAllGizmosByOwner() @param InstanceIdentifier optional client-defined *unique* string that can be used to locate this instance @return new Gizmo instance that has been created and initialized
- L223 _public prototype_ `virtual UCombinedTransformGizmo* CreateCustomRepositionableTransformGizmo(ETransformGizmoSubElements Elements, void* Owner = nullptr, const FString& InstanceIdentifier = FString());`
- L227 _public member_ `static FString DefaultAxisPositionBuilderIdentifier;` — builder identifiers for default gizmo types. Perhaps should have an API for this...
- L228 _public member_ `static FString DefaultPlanePositionBuilderIdentifier;`
- L229 _public member_ `static FString DefaultAxisAngleBuilderIdentifier;`
- L230 _public member_ `static FString DefaultThreeAxisTransformBuilderIdentifier;`
- L231 _public member_ `static const FString CustomThreeAxisTransformBuilderIdentifier;`
- L232 _public member_ `static const FString CustomRepositionableThreeAxisTransformBuilderIdentifier;`
- L233 _public member_ `static FString DefaultScalableSphereBuilderIdentifier;`
- L238 _protected member_ `TArray<FActiveGizmo> ActiveGizmos;` — `UPROPERTY()` — set of Currently-active Gizmos
- L243 _protected member_ `IToolsContextQueriesAPI* QueriesAPI;` — Current Context-Queries implementation
- L245 _protected member_ `IToolsContextTransactionsAPI* TransactionsAPI;` — Current Transactions implementation
- L248 _protected member_ `UInputRouter* InputRouter;` — Current InputRouter (Context owns this)
- L252 _protected member_ `TMap<FString, TObjectPtr<UInteractiveGizmoBuilder>> GizmoBuilders;` — `UPROPERTY()` — Current set of named GizmoBuilders
- L254 _protected member_ `bool bDefaultGizmosRegistered = false;`
- L255 _protected member_ `TSharedPtr<FCombinedTransformGizmoActorFactory> GizmoActorBuilder;`

### `Source/Runtime/InteractiveToolsFramework/Public/InteractiveTool.h` (Public)


#### enum `EToolShutdownType`  
`enum class EToolShutdownType : uint8`  
_L44-52_
- reflection: `UENUM(BlueprintType)`
- desc: Passed to UInteractiveTool::Shutdown to indicate how Tool should shut itself down
- L47 _public enumerator_ `Completed = 0` — Tool cleans up and exits. Pass this to tools that do not have Accept/Cancel options.
- L49 _public enumerator_ `Accept = 1` — Tool commits current preview to scene
- L51 _public enumerator_ `Cancel = 2` — Tool discards current preview without modifying scene

#### enum `EToolShutdownReason`  
`enum class EToolShutdownReason : uint8`  
_L55-61_
- desc: Used in various ways by the tool manager and some optional tool interfaces to make shutdown responses configurable.
- L58 _public enumerator_ `Unspecified = 0` — The reason for the shutdown was left unspecified.
- L60 _public enumerator_ `SwitchTool = 1` — Another tool is being activated without the user having explicitly shut down this one.

#### struct `FInteractiveToolInfo`  
`struct FInteractiveToolInfo`  
_L66-74_
- desc: FInteractiveToolInfo provides information about a tool (name, tooltip, etc)
- L69 _public member_ `FText ToolDisplayName = FText::GetEmpty();` — Name of Tool. May be FText::Empty(), but will default to Tool->GetClass()->GetDisplayNameText() in InteractiveTool constructor
- L71 _public member_ `FText ToolDisplayMessage = FText::GetEmpty();` — Display message that can be used as a tool tip or to provide information about the tool.
- L73 _public member_ `const FSlateBrush* ToolIcon = nullptr;` — The icon to use for the tool ui command.

#### class `FWatchablePropertySet`  
`class FWatchablePropertySet`  
_L77-239_
- L176 _public prototype_ `FWatchablePropertySet() = default;`
- L177 _public prototype_ `FWatchablePropertySet(const FWatchablePropertySet&) = delete;`
- L178 _public prototype_ `FWatchablePropertySet& operator=(const FWatchablePropertySet&) = delete;`
- L180 _public function_ `void CheckAndUpdateWatched()`
- L187 _public function_ `void SilentUpdateWatched()`
- L199 _public function_ `void SilentUpdateWatcherAtIndex(int32 i)` — Silently updates just a single watcher, using an index gotten from WatchProperty. Useful when you want watching to still work for other properties changed in the same tick.
- L207 _public function_ `template <typename PropType> int32 WatchProperty(const PropType& ValueIn, typename TPropertyWatcher<PropType>::FChangedCallback OnChangedIn)` — @return Index of the watcher, which can be used in SilentUpdateWatcherAtIndex
- L214 _public function_ `template <typename PropType> int32 WatchProperty(typename TPropertyWatcher<PropType>::FValueGetter GetValueIn, typename TPropertyWatcher<PropType>::FChangedCallback OnChangedIn)` — @return Index of the watcher, which can be used in SilentUpdateWatcherAtIndex
- L222 _public function_ `template <typename PropType> int32 WatchProperty(const PropType& ValueIn, typename TPropertyWatcher<PropType>::FChangedCallback OnChangedIn, typename TPropertyWatcher<PropType>::FNotEqualTestFunction NotEqualsIn)` — @return Index of the watcher, which can be used in SilentUpdateWatcherAtIndex
- L230 _public function_ `template <typename PropType> int32 WatchProperty(typename TPropertyWatcher<PropType>::FValueGetter GetValueIn, typename TPropertyWatcher<PropType>::FChangedCallback OnChangedIn, typename TPropertyWatcher<PropType>::FNotEqualTestFunction NotEqualsIn)` — @return Index of the watcher, which can be used in SilentUpdateWatcherAtIndex
- L238 _private member_ `TArray<TUniquePtr<FPropertyWatcher>> PropertyWatchers;`

#### class `FWatchablePropertySet::FPropertyWatcher`  
`class FPropertyWatcher`  
_L83-89_
- desc: Property watching infrastructure
- L86 _public prototype_ `virtual ~FPropertyWatcher() = default;`
- L87 _public prototype_ `virtual void CheckAndUpdate() = 0;`
- L88 _public prototype_ `virtual void SilentUpdate() = 0;`

#### class `FWatchablePropertySet::TPropertyWatcher`  
`template <typename PropType> class TPropertyWatcher : public FPropertyWatcher`  
_L92-174_
- inherits: `FPropertyWatcher`
- L95 _public typedef_ `using FValueGetter = TFunction<PropType(void)>;`
- L96 _public typedef_ `using FChangedCallback = TFunction<void(const PropType&)>;`
- L97 _public typedef_ `using FNotEqualTestFunction = TFunction<bool(const PropType&, const PropType&)>;` — Define "!=" for PropType
- L118 _public function_ `template<typename Q = PropType, typename = typename TEnableIf<TModels_V<CInequalityComparable, Q>>::Type> TPropertyWatcher(const PropType& Property, FChangedCallback OnChangedIn) : Cached(), GetValue([&Property]() {return Property; }), OnChanged(MoveTemp(OnChangedIn)), NotEqual([](const PropType& A, const PropType& B) { return A != B; })` — Two-argument constructor, enabled only if PropType is CInequalityComparable
- L121 _public function_ `: Cached(), GetValue([&Property]() {return Property; }), OnChanged(MoveTemp(OnChangedIn)), NotEqual([](const PropType& A, const PropType& B) { return A != B; })`
- L128 _public function_ `template<typename Q = PropType, typename = typename TEnableIf<TModels_V<CInequalityComparable, Q>>::Type> TPropertyWatcher(FValueGetter GetValueIn, FChangedCallback OnChangedIn) : Cached(), GetValue(MoveTemp(GetValueIn)), OnChanged(MoveTemp(OnChangedIn)), NotEqual([](const PropType& A, const PropType& B) { return A != B; })` — Two-argument constructor, enabled only if PropType is CInequalityComparable
- L133 _public function_ `: Cached(), GetValue(MoveTemp(GetValueIn)), OnChanged(MoveTemp(OnChangedIn)), NotEqual([](const PropType& A, const PropType& B) { return A != B; })`
- L136 _public function_ `TPropertyWatcher(const PropType& Property, FChangedCallback OnChangedIn, FNotEqualTestFunction NotEqualIn) : Cached(), GetValue([&Property]() {return Property; }), OnChanged(MoveTemp(OnChangedIn)), NotEqual(MoveTemp(NotEqualIn))`
- L140 _public function_ `: Cached(), GetValue([&Property]() {return Property; }), OnChanged(MoveTemp(OnChangedIn)), NotEqual(MoveTemp(NotEqualIn))`
- L145 _public function_ `TPropertyWatcher(FValueGetter GetValueIn, FChangedCallback OnChangedIn, FNotEqualTestFunction NotEqualIn) : Cached(), GetValue(MoveTemp(GetValueIn)), OnChanged(MoveTemp(OnChangedIn)), NotEqual(MoveTemp(NotEqualIn))`
- L154 _public function_ `void CheckAndUpdate() final`
- L164 _public function_ `void SilentUpdate() final`
- L170 _private member_ `TOptional<PropType> Cached;`
- L171 _private member_ `FValueGetter GetValue;`
- L172 _private member_ `FChangedCallback OnChanged;`
- L173 _private member_ `FNotEqualTestFunction NotEqual;`

#### struct `FWatchablePropertySet::TPropertyWatcher::CInequalityComparable`  
`struct CInequalityComparable`  
_L103-109_
- desc: Describes a type having a "!=" comparasion operator. (Note: it would probably be cleaner to require operator==, however some types have operator!= but no operator==, and we do only use != in the code.)
- L106 _public prototype_ `template <typename T> auto Requires(bool& Result, const T& A, const T& B) -> decltype( Result = A != B );`

#### class `UInteractiveToolPropertySet`  
`class UInteractiveToolPropertySet : public UObject, public FWatchablePropertySet`  
_L256-357_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UObject,FWatchablePropertySet`
- desc: A UInteractiveTool contains a set of UObjects that contain "properties" of the Tool, ie the configuration flags, parameters, etc that control the Tool. Currently any UObject can be added as a property set, however there is no automatic mechanism for those child UObjects to notify the Tool when a property changes. If you make your property set UObjects subclasses of UInteractiveToolPropertySet, then when the Tool Properties are changed *in the Editor*, the parent Tool will be automatically notified. You can override UInteractiveTool::OnPropertyModified() to act on these notifications
- L262 _public function_ `FInteractiveToolPropertySetModifiedSignature& GetOnModified()` — @return the multicast delegate that is called when properties are modified
- L268 _public function_ `bool IsPropertySetEnabled() const` — Return true if this property set is enabled. Enabled/Disable state is intended to be used to control things like visibility in UI/etc.
- L299 _public prototype_ `virtual void SaveProperties(UInteractiveTool* SaveFromTool, const FString& CacheIdentifier = TEXT(""));` — Save the values of this PropertySet with the given CacheIdentifier. The Tool parameter is currently ignored.
- L305 _public prototype_ `virtual void RestoreProperties(UInteractiveTool* RestoreToTool, const FString& CacheIdentifier = TEXT(""));` — Restore the values of the Property Set with the given CacheIdentifier. The Tool parameter is currently ignored.
- L309 _protected prototype_ `virtual void SaveRestoreProperties(UInteractiveTool* RestoreToTool, const FString& CacheIdentifier, bool bSaving);` — Utility func used to implement the default Save/RestoreProperties funcs
- L318 _protected prototype_ `TObjectPtr<UInteractiveToolPropertySet> GetDynamicPropertyCache(const FString& CacheIdentifier, bool& bWasCreatedOut);` — `UE_DEPRECATED(5.8, "Use FindDynamicPropertyCache or FindOrAddDynamicPropertyCache instead.")` — GetDynamicPropertyCache return class-internal objects that subclasses can use to save/restore properties. @param CacheIdentifier multiple versions of the UInteractiveToolPropertySet can be stored, CacheIdentifier indicates which one to use @param bWasCreatedOut true is returned here if this is the first time the object was seen @return instance of the current subclass that can be used to save/restore values
- L326 _protected prototype_ `TObjectPtr<UInteractiveToolPropertySet> FindDynamicPropertyCache(const FString& CacheIdentifier) const;` — FindDynamicPropertyCache returns class-internal objects that subclasses can use to save/restore properties, or nullptr if the cache entry does not exist. @param CacheIdentifier multiple versions of the UInteractiveToolPropertySet can be stored, CacheIdentifier indicates which one to use @return instance of the current subclass that can be used to save/restore values, or nullptr if the entry does not exist.
- L334 _protected prototype_ `TObjectPtr<UInteractiveToolPropertySet> FindOrAddDynamicPropertyCache(const FString& CacheIdentifier) const;` — FindOrAddDynamicPropertyCache returns class-internal objects that subclasses can use to save/restore properties. Creates a cache entry if one does not yet exist. @param CacheIdentifier multiple versions of the UInteractiveToolPropertySet can be stored, CacheIdentifier indicates which one to use @return instance of the current subclass that can be used to save/restore values
- L343 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);` — Posts a message to the OnModified delegate with the modified FProperty @warning Please consider listening to OnModified instead of overriding this function @warning this function is currently only called in Editor (not at runtime)
- L348 _protected member_ `TMap<FString, TObjectPtr<UInteractiveToolPropertySet>> CachedPropertiesMap;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional, SkipSerialization)`
- L352 _protected member_ `bool bIsPropertySetEnabled = true;` — `UPROPERTY(Transient, DuplicateTransient, SkipSerialization, meta=(TransientToolProperty))` — Controls whether a property set is shown in the UI.  Transient so that disabling a PropertySet in one tool doesn't disable it in others.
- L356 _protected member_ `FInteractiveToolPropertySetModifiedSignature OnModified;`

#### class `UInteractiveTool`  
`class UInteractiveTool : public UObject, public IInputBehaviorSource`  
_L380-685_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UObject,IInputBehaviorSource`
- desc: UInteractiveTool is the base class for all Tools in the InteractiveToolsFramework. A Tool is is a "lightweight mode" that may "own" one or more Actors/Components/etc in the current scene, may capture certain input devices or event streams, and so on. The base implementation essentially does nothing but provide sane default behaviors. The BaseTools/ subfolder contains implementations of various kinds of standard "tool behavior", like a tool that responds to a mouse click, etc, that can be extended to implement custom behaviors. In the framework, you do not create instances of UInteractiveTool yourself. You provide a UInteractiveToolBuilder implementation that can properly construct an instance of your Tool, this is where for example default parameters would be set. The ToolBuilder is registered with the ToolManager, and then UInteractiveToolManager::ActivateTool() is used to kick things off. @todo callback/delegate for if/when .InputBehaviors changes @todo callback/delegate for when tool properties change
- L385 _public prototype_ `UInteractiveTool();`
- L390 _public prototype_ `virtual void Setup();` — Called by ToolManager to initialize the Tool *after* ToolBuilder::BuildTool() has been called
- L396 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType);` — Called by ToolManager to shut down the Tool @param ShutdownType indicates how the tool should shutdown (ie Accept or Cancel current preview, etc)
- L402 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI);` — Allow the Tool to do any custom drawing (ie via PDI/RHI) @param RenderAPI Abstraction that provides access to Rendering in the current ToolsContext
- L409 _public prototype_ `virtual void DrawHUD( FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI );` — Allow the Tool to do any custom screen space drawing @param Canvas the FCanvas to use to do the drawing @param RenderAPI Abstraction that provides access to Rendering in the current ToolsContext
- L415 _public prototype_ `virtual void Tick(float DeltaTime) final;` — Non overrideable func which does processing and calls the tool's OnTick @param DeltaTime the time delta since last tick
- L420 _public prototype_ `virtual UInteractiveToolManager* GetToolManager() const;` — @return ToolManager that owns this Tool
- L426 _public prototype_ `virtual bool HasCancel() const;` — @return true if this Tool support being Cancelled, ie calling Shutdown(EToolShutdownType::Cancel)
- L431 _public prototype_ `virtual bool HasAccept() const;` — @return true if this Tool support being Accepted, ie calling Shutdown(EToolShutdownType::Accept)
- L436 _public prototype_ `virtual bool CanAccept() const;` — @return true if this Tool is currently in a state where it can be Accepted. This may be false if for example there was an error in the Tool.
- L450 _public prototype_ `virtual void AddInputBehavior(UInputBehavior* Behavior, void* Source = nullptr);` — Add an input behavior for this Tool. Typically only effective when called during tool Setup(), as the behavior set gets submitted to the input router after that call. @param Behavior behavior to add @param Source Optional pointer that could be used to identify the behavior for removal later.
- L458 _public prototype_ `virtual void RemoveInputBehaviorsBySource(void* Source);` — Remove all input behaviors that had the given source pointer set during their addition. Typically only effective when called during tool Setup(), as the behavior set gets submitted to the input router after that call. @param Source Identifying pointer
- L463 _public prototype_ `virtual const UInputBehaviorSet* GetInputBehaviors() const;` — @return Current input behavior set.
- L473 _public prototype_ `virtual TArray<UObject*> GetToolProperties(bool bEnabledOnly = true) const;` — @return list of property UObjects for this tool (ie to add to a DetailsViewPanel, for example)
- L478 _public prototype_ `DECLARE_MULTICAST_DELEGATE(OnInteractiveToolPropertySetsModified);` — OnPropertySetsModified is broadcast whenever the contents of the ToolPropertyObjects array is modified
- L479 _public member_ `OnInteractiveToolPropertySetsModified OnPropertySetsModified;`
- L490 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(OnInteractiveToolPropertyInternallyModified, UObject*);` — OnPropertyModifiedDirectlyByTool is broadcast whenever the ToolPropertyObjects array stays the same, but a property inside of one of the objects is changed internally by the tool. This allows any external display of such properties to properly update. In a DetailsViewPanel, for instance, it refreshes certain cached states such as edit condition states for other properties. This should only broadcast when the tool itself is responsible for the change, so it typically isn't broadcast from the tool's OnPropertyModified function.
- L491 _public member_ `OnInteractiveToolPropertyInternallyModified OnPropertyModifiedDirectlyByTool;`
- L498 _public function_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property)` — Automatically called by UInteractiveToolPropertySet.OnModified delegate to notify Tool of child property set changes @param PropertySet which UInteractiveToolPropertySet was modified @param Property which FProperty in the set was modified
- L507 _protected member_ `TObjectPtr<UInputBehaviorSet> InputBehaviors;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional, SkipSerialization)` — The current set of InputBehaviors provided by this Tool
- L511 _protected member_ `TArray<TObjectPtr<UObject>> ToolPropertyObjects;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional, SkipSerialization)` — The current set of Property UObjects provided by this Tool. May contain pointer to itself.
- L517 _protected prototype_ `virtual void AddToolPropertySource(UObject* PropertyObject);` — Add a Property object for this Tool @param Property object to add
- L523 _protected prototype_ `virtual void AddToolPropertySource(UInteractiveToolPropertySet* PropertySet);` — Add a PropertySet object for this Tool @param PropertySet Property Set object to add
- L530 _protected prototype_ `virtual bool RemoveToolPropertySource(UInteractiveToolPropertySet* PropertySet);` — Remove a PropertySet object from this Tool. If found, will broadcast OnPropertySetsModified @param PropertySet property set to remove. @return true if PropertySet is found and removed
- L539 _protected prototype_ `virtual bool ReplaceToolPropertySource(UInteractiveToolPropertySet* CurPropertySet, UInteractiveToolPropertySet* ReplaceWith, bool bSetToEnabled = true);` — Replace a PropertySet object on this Tool with another property set. If replaced, will broadcast OnPropertySetsModified @param CurPropertySet property set to remove @param ReplaceWith property set to add @param bSetToEnabled if true, ReplaceWith property set is explicitly enabled (otherwise enable/disable state is unmodified) @return true if CurPropertySet is found and replaced
- L547 _protected prototype_ `virtual bool SetToolPropertySourceEnabled(UInteractiveToolPropertySet* PropertySet, bool bEnabled);` — Enable/Disable a PropertySet object for this Tool. If found and state was modified, will broadcast OnPropertySetsModified @param PropertySet Property Set object to modify @param bEnabled whether to enable or disable @return true if PropertySet was found
- L555 _protected prototype_ `virtual void NotifyOfPropertyChangeByTool(UInteractiveToolPropertySet* PropertySet) const;` — Call after changing a propertyset internally in the tool to allow external views of the property set to update properly. This is meant as an outward notification mechanism, not a way to to pass along notifications, so don't call this if the property is changed externally (i.e., this should not usually be called from OnPropertyModified unless the tool adds changes of its own).
- L570 _protected prototype_ `virtual void UpdateAcceptWarnings(EAcceptWarning Warning);` — Helper function to update a standard warning when we need to explain why "Accept" is disabled Note that calling this base implementation will clear any unrelated warnings. Note that this function is not automatically called by the base class. @param Warning Reason that tool cannot be accepted (or EAcceptWarning::NoWarning if no warning need be displayed)
- L575 _private member_ `bool bLastShowedAcceptWarning = false;` — Tracks whether the UpdateAcceptWarnings function showed a warning the last time it was called. Used to avoid clearing the tool display message in cases where it was not set by this function.
- L584 _protected function_ `virtual void OnTick(float DeltaTime)` — Allow the Tool to do any necessary processing on Tick @param DeltaTime the time delta since last tick
- L600 _public prototype_ `virtual FInteractiveToolActionSet* GetActionSet();` — Get the internal Action Set for this Tool. The action set is created and registered on-demand. @return pointer to initialized Action set
- L606 _public prototype_ `virtual void ExecuteAction(int32 ActionID);` — Request that the Action identified by ActionID be executed. Default implementation forwards these requests to internal ToolActionSet.
- L615 _protected prototype_ `virtual void RegisterActions(FInteractiveToolActionSet& ActionSet);` — Override this function to register the set of Actions this Tool supports, using FInteractiveToolActionSet::RegisterAction. Note that for the actions to be triggered, you will also need to add corresponding registration per tool -- see Engine\Plugins\Editor\ModelingToolsEditorMode\Source\ModelingToolsEditorMode\Public\ModelingToolsActions.h for examples
- L623 _private member_ `FInteractiveToolActionSet* ToolActionSet = nullptr;` — Set of actions this Tool can execute. This variable is allocated on-demand. Use GetActionSet() instead of accessing this pointer directly!
- L636 _public function_ `virtual FInteractiveToolInfo GetToolInfo() const` — @return ToolInfo structure for this Tool
- L644 _public function_ `virtual void SetToolInfo(const FInteractiveToolInfo& NewInfo)` — Replace existing ToolInfo with new data
- L652 _public function_ `virtual void SetToolDisplayName(const FText& NewName)` — Set Tool name
- L660 _public function_ `virtual void SetToolDisplayMessage(const FText& NewDisplayMessage)` — Set the Tool's Display Message
- L668 _public function_ `virtual void SetToolIcon(const FSlateBrush* NewIcon)` — Set the Tool's Icon
- L677 _private member_ `FInteractiveToolInfo DefaultToolInfo;` — ToolInfo for this Tool

#### enum `UInteractiveTool::EAcceptWarning`  
`enum EAcceptWarning`  
_L557-561_
- L559 _public enumerator_ `NoWarning`
- L560 _public enumerator_ `EmptyForbidden`

#### Free symbols / members of external scopes

- L242 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FInteractiveToolPropertySetModifiedSignature, UObject*, FProperty*);` — This delegate is used by UInteractiveToolPropertySet
- L242 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FInteractiveToolPropertySetModifiedSignature, UObject*, FProperty*);` — This delegate is used by UInteractiveToolPropertySet
- L478 _delegate_ `DECLARE_MULTICAST_DELEGATE(OnInteractiveToolPropertySetsModified);` — OnPropertySetsModified is broadcast whenever the contents of the ToolPropertyObjects array is modified
- L490 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(OnInteractiveToolPropertyInternallyModified, UObject*);` — OnPropertyModifiedDirectlyByTool is broadcast whenever the ToolPropertyObjects array stays the same, but a property inside of one of the objects is changed internally by the tool. This allows any external display of such properties to properly update. In a DetailsViewPanel, for instance, it refreshes certain cached states such as edit condition states for other properties. This should only broadcast when the tool itself is responsible for the change, so it typically isn't broadcast from the tool's OnPropertyModified function.

### `Source/Runtime/InteractiveToolsFramework/Public/InteractiveToolActionSet.h` (Public)


#### enum `EStandardToolActions`  
`enum class EStandardToolActions`  
_L23-31_
- desc: Standard Actions that can be shared across multiple Tools. The enum values are used as FInteractiveToolAction.ActionID. If you need to define your own values, start at BaseClientDefinedActionID
- L25 _public enumerator_ `IncreaseBrushSize = 100`
- L26 _public enumerator_ `DecreaseBrushSize = 101`
- L27 _public enumerator_ `ToggleWireframe = 102`
- L30 _public enumerator_ `BaseClientDefinedActionID = 10000`

#### enum `EToolActionKeyRepeatMode`  
`enum class EToolActionKeyRepeatMode`  
_L38-42_
- desc: Controls whether a tool Action re-fires (by key repeat) while its shortcut key is held down
- L40 _public enumerator_ `Disabled`
- L41 _public enumerator_ `Enabled`

#### struct `FInteractiveToolAction`  
`struct FInteractiveToolAction`  
_L49-95_
- desc: FInteractiveToolAction is returned by a UInteractiveTool to represent an "Action" the Tool can execute.
- L52 _public member_ `const UClass* ClassType;` — Which type of UInteractiveTool this Action can be applied to
- L55 _public member_ `int32 ActionID;` — Identifier for this Action
- L58 _public member_ `FString ActionName;` — Internal name for this Action
- L60 _public member_ `FText ShortName;` — Short name for this Action
- L62 _public member_ `FText Description;` — Descriptive name for this Action
- L65 _public member_ `EModifierKey::Type DefaultModifiers;` — Suggested modifier keys for this Action
- L67 _public member_ `FKey DefaultKey;` — Suggested keybinding for this Action.
- L70 _public member_ `EToolActionKeyRepeatMode KeyRepeatMode = EToolActionKeyRepeatMode::Disabled;` — Whether to re-fire (by key repeat) this Action while the shortcut key is held down
- L73 _public member_ `TFunction<void()> OnAction;` — Call this function to execute the Action
- L76 _public function_ `FInteractiveToolAction()`
- L82 _public function_ `FInteractiveToolAction(const UClass* ClassTypeIn, int32 ActionIDIn, const FString& ActionNameIn, const FText& ShortNameIn, const FText& DescriptionIn, EModifierKey::Type DefaultModifiersIn, const FKey& DefaultKeyIn )`

#### class `FInteractiveToolActionSet`  
`class FInteractiveToolActionSet`  
_L103-135_
- desc: FInteractiveToolActionSet maintains a list of FInteractiveToolAction. Each UInteractiveTool contains an instance of this class.
- L111 _public prototype_ `void RegisterAction(UInteractiveTool* Tool, int32 ActionID, const FString& ActionName, const FText& ShortUIName, const FText& DescriptionText, EModifierKey::Type Modifiers, const FKey& ShortcutKey, TFunction<void()> ActionFunction, EToolActionKeyRepeatMode KeyRepeatMode = EToolActionKeyRepeatMode::Disabled );` — Register an Action with the ActionSet. This function is intended to be called by UInteractiveTool::RegisterActions() implementations
- L121 _public prototype_ `const FInteractiveToolAction* FindActionByID(int32 ActionID) const;` — Find an existing Action by ID @return located Action, or nullptr if not found
- L126 _public prototype_ `void CollectActions(TArray<FInteractiveToolAction>& OutActions) const;` — Return the internal list of registered Actions by adding to the OutActions array
- L131 _public prototype_ `void ExecuteAction(int32 ActionID) const;` — Execute the action identified by ActionID
- L134 _protected member_ `TArray<FInteractiveToolAction> Actions;`

### `Source/Runtime/InteractiveToolsFramework/Public/InteractiveToolBuilder.h` (Public)


#### class `UInteractiveToolBuilder`  
`class UInteractiveToolBuilder : public UObject`  
_L27-77_
- reflection: `UCLASS(Transient, Abstract, MinimalAPI)`
- inherits: `UObject`
- desc: A UInteractiveToolBuilder creates a new instance of an InteractiveTool (basically this is a Factory). These are registered with the InteractiveToolManager, which calls BuildTool() if CanBuildTool() returns true. In addition CanBuildTool() will be queried to (for example) enable/disable UI buttons, etc. This is an abstract base class, you must subclass it in order to create your particular Tool instance
- L38 _public function_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const` — Check if, given the current scene state, a new instance of this builder's Tool can be created @param SceneState the current scene selection state, etc @return true if a new Tool instance can be created
- L49 _public function_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const` — Create a new instance of this builder's Tool @param SceneState the current scene selection state, etc @return a new instance of the Tool, or nullptr on error/failure
- L62 _public function_ `virtual void PostBuildTool(UInteractiveTool* Tool, const FToolBuilderState& SceneState) const` — PostBuildTool is called by the ToolManager after a new Tool instance has been built. This allows clients to extend a ToolBuilder with additional customization/etc, instead of having to entirely replace the existing BuildTool() @param Tool the new Tool instance @param SceneState the scene state used to create the new Tool
- L73 _public function_ `virtual void PostSetupTool(UInteractiveTool* Tool, const FToolBuilderState& SceneState) const` — PostBuildTool is called by the ToolManager after a new Tool instance has been built and Setup() has been called. This allows clients to make modifications to Tools like changing initial parameters without subclassing the Tool @param Tool the new Tool instance @param SceneState the scene state used to create the new Tool

#### class `UInteractiveToolWithToolTargetsBuilder`  
`class UInteractiveToolWithToolTargetsBuilder : public UInteractiveToolBuilder`  
_L86-100_
- reflection: `UCLASS(Transient, Abstract, MinimalAPI)`
- inherits: `UInteractiveToolBuilder`
- desc: A UInteractiveToolWithToolTargetsBuilder creates a new instance of an InteractiveTool that uses tool targets. See ToolTarget.h for more information on tool targets and their usage. This class defines the common interface(s) for defining the tool target requirements of the tool it builds. This is an abstract base class, you must subclass it in order to create your particular Tool instance.
- L95 _protected function_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const` — Gives the target requirements of the associated tool. Usually, it is the tool builder will use this function in CanBuildTool and BuildTool to find and create any necessary targets.

### `Source/Runtime/InteractiveToolsFramework/Public/InteractiveToolChange.h` (Public)


#### class `FToolCommandChange`  
`class FToolCommandChange : public FCommandChange`  
_L17-22_
- inherits: `FCommandChange`
- desc: FToolCommandChange is a base class for command changes used by the Tools Framework.
- L21 _public function_ `virtual FString ToString() const override`

#### class `UToolContextTransactionProvider`  
`class UToolContextTransactionProvider : public UInterface`  
_L29-32_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IToolContextTransactionProvider`  
`class IToolContextTransactionProvider`  
_L38-61_
- desc: IToolContextTransactionProvider is a UInterface that defines several functions that InteractiveTool code uses to interface with the higher-level transaction system. UInteractiveToolManager and UInteractiveGizmoManager both implement this interface.
- L46 _public prototype_ `virtual void BeginUndoTransaction(const FText& Description) = 0;` — Request that the Context open a Transaction, whatever that means to the current Context @param Description text description of this transaction (this is the string that appears on undo/redo in the UE Editor)
- L49 _public prototype_ `virtual void EndUndoTransaction() = 0;` — Request that the Context close and commit the open Transaction
- L52 _public prototype_ `virtual void CancelUndoTransaction() = 0;` — Request that the Context cancel and revert the open Transaction
- L60 _public prototype_ `virtual void EmitObjectChange(UObject* TargetObject, TUniquePtr<FToolCommandChange> Change, const FText& Description) = 0;` — Forward an FChange object to the Context @param TargetObject the object that the FChange applies to @param Change the change object that the Context should insert into the transaction history @param Description text description of this change (this is the string that appears on undo/redo in the UE Editor)

#### class `IToolCommandChangeSource`  
`class IToolCommandChangeSource`  
_L70-84_
- desc: IToolCommandChangeSource is a generic interface for generating a change object. This is useful to
- L73 _public prototype_ `virtual ~IToolCommandChangeSource() = default;`
- L75 _public prototype_ `virtual void BeginChange() = 0;`
- L79 _public prototype_ `virtual TUniquePtr<FToolCommandChange> EndChange() = 0;`
- L80 _public prototype_ `virtual UObject* GetChangeTarget() = 0;`
- L81 _public prototype_ `virtual FText GetChangeDescription() = 0;`
- L83 _public prototype_ `virtual void CancelChange() = 0;`

#### class `TWrappedToolCommandChange`  
`template<typename ChangeType> class TWrappedToolCommandChange : public FToolCommandChange`  
_L98-136_
- inherits: `FToolCommandChange`
- desc: Holds another Change and forwards Apply/Revert to it, with calls to Before/After lambas, allowing client classes to respond to a change without having to intercept it explicitly. (Be very careful with these lambdas!)
- L101 _public member_ `TUniquePtr<ChangeType> WrappedChange;`
- L103 _public member_ `TUniqueFunction<void(bool bRevert)> BeforeModify;`
- L104 _public member_ `TUniqueFunction<void(bool bRevert)> AfterModify;`
- L106 _public function_ `virtual void Apply(UObject* Object) override`
- L119 _public function_ `virtual void Revert(UObject* Object) override`
- L132 _public function_ `virtual FString ToString() const override`

### `Source/Runtime/InteractiveToolsFramework/Public/InteractiveToolManager.h` (Public)


#### enum `EToolSide`  
`enum class EToolSide`  
_L19-26_
- reflection: `UENUM()`
- desc: A Tool can be activated on a particular input device, currently identified by a "side"
- L22 _public enumerator_ `Left = 1` — Left-hand Tool, also used for Mouse
- L23 _public enumerator_ `Mouse = 1`
- L25 _public enumerator_ `Right = 2` — Right-hand Tool

#### enum `EToolChangeTrackingMode`  
`enum class EToolChangeTrackingMode`  
_L35-43_
- reflection: `UENUM()`
- desc: UInteractiveToolManager can emit change events for the active tool in various ways. This allows different modes to control how tools activate/deactivate on undo/redo, which is necessary because some modes (eg Modeling Mode) do not support redo "into" a Tool, while others require it (like Paint Mode)
- L38 _public enumerator_ `NoChangeTracking = 1` — Do not emit any Active Tool change events
- L40 _public enumerator_ `UndoToExit = 2` — When Activating a new Tool, emit a change that will cancel/deactivate that Tool on Undo, but not reactivate it on Redo
- L42 _public enumerator_ `FullUndoRedo = 3` — Full change tracking of active Tool. Note that on Activation when an existing Tool is auto-shutdown, two separate FChanges are emitted, wrapped in a single Transaction

#### enum `EToolManagerToolSwitchMode`  
`enum class EToolManagerToolSwitchMode`  
_L49-59_
- reflection: `UENUM()`
- desc: Determines how a currently active tool is shutdown when switching to another tool.
- L52 _public enumerator_ `AcceptIfAble` — Accept if able, cancel if not (and complete if neither is possible)
- L54 _public enumerator_ `CancelIfAble` — Cancel if able, complete if not
- L56 _public enumerator_ `CustomizableAcceptIfAble` — Like AcceptIfAble, except a tool can change the shutdown type by implementing IInteractiveToolShutdownQueryAPI
- L58 _public enumerator_ `CustomizableCancelIfAble` — Like CancelIfAble, except a tool can change the shutdown type by implementing IInteractiveToolShutdownQueryAPI

#### class `UInteractiveToolManager`  
`class UInteractiveToolManager : public UObject, public IToolContextTransactionProvider`  
_L78-418_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UObject,IToolContextTransactionProvider`
- desc: UInteractiveToolManager allows users of the tools framework to create and operate Tool instances. For each Tool, a (string,ToolBuilder) pair is registered with the ToolManager. Tools can then be activated via the string identifier. Currently a single Tool can be active for each input device. So for mouse input a single Tool is available and effectively a lightweight mode. The mouse uses the "Left" tool slot. For VR controllers and touch input, a "Left" and "Right" tool can be active at the same time. @todo this is not fully supported yet Tools are not directly created. Use SelectActiveToolType(side,string) to set the active ToolBuilder on a given side, and then use ActivateTool() to create the new Tool instance.
- L85 _protected prototype_ `UInteractiveToolManager();`
- L88 _protected prototype_ `virtual void Initialize(IToolsContextQueriesAPI* QueriesAPI, IToolsContextTransactionsAPI* TransactionsAPI, UInputRouter* InputRouter);` — Initialize the ToolManager with the necessary Context-level state. UInteractiveToolsContext calls this, you should not.
- L91 _protected prototype_ `virtual void Shutdown();` — Shutdown the ToolManager. Called by UInteractiveToolsContext.
- L94 _protected prototype_ `virtual void DoPostBuild(EToolSide Side, UInteractiveTool* InBuiltTool, UInteractiveToolBuilder* InToolBuilder, const FToolBuilderState& InBuilderState);` — Called immediately after a tool is built. Broadcasts OnToolPostBuild.
- L97 _protected prototype_ `virtual void DoPostSetup(EToolSide Side, UInteractiveTool* InInteractiveTool, UInteractiveToolBuilder* InToolBuilder, const FToolBuilderState& InBuilderState);` — Called immediately after a tool's Setup is called. Broadcasts OnToolPostSetup.
- L105 _public function_ `bool IsActive() const` — @return true if ToolManager is currently active, ie between Initialize() and Shutdown()
- L117 _public prototype_ `virtual void RegisterToolType(const FString& Identifier, UInteractiveToolBuilder* Builder);` — Register a new ToolBuilder @param Identifier string used to identify this Builder @param Builder new ToolBuilder instance
- L124 _public prototype_ `virtual void UnregisterToolType(const FString& Identifier);` — Unregisters a ToolBuilder @param Identifier string used to identify this Builder @param Builder new ToolBuilder instance
- L131 _public prototype_ `virtual bool SelectActiveToolType(EToolSide Side, const FString& Identifier);` — Set active ToolBuilder for a ToolSide via string identifier @param Side which "side" should we set this Builder on @param Identifier name of ToolBuilder that was passed to RegisterToolType()
- L137 _public prototype_ `virtual const FString& GetActiveToolType(EToolSide Side) const;` — Get active ToolBuilder string identifier for a ToolSide @param Side which "side" should we get this Builder from
- L145 _public prototype_ `virtual bool CanActivateTool(EToolSide eSide, FString Identifier);` — Check if a named Tool type can currently be activated on the given ToolSide @param Side which "side" you would like to active the tool on @param Identifier string name of the Tool type @return true if the Tool type could be activated
- L153 _public prototype_ `virtual bool ActivateTool(EToolSide Side);` — Try to activate a new Tool instance on the given Side. If another tool is already active, it will be shut down according to ToolSwitchMode. @param Side which "side" you would like to active the tool on @return true if a new Tool instance was created and initialized
- L160 _public prototype_ `virtual bool HasActiveTool(EToolSide Side) const;` — Check if there is an active Tool on the given Side @param Side which Side to check @return true if there is an active Tool on that side
- L166 _public function_ `virtual EToolManagerToolSwitchMode GetToolSwitchMode() const` — Get the current setting for how to deactivate an already-active tool if switching directly to another tool.
- L176 _public function_ `virtual void SetToolSwitchMode(EToolManagerToolSwitchMode ToolSwitchModeIn)` — Set the behavior for how to deactivate an already-active tool if ActivateTool is called while HasActiveTool is true. Note: a higher level system could choose to enforce its preferences for this behavior by querying HasActiveTool and making sure to shut down the previous tool before calling ActivateTool. However it is convenient to be able to set the behavior at the tool manager level.
- L181 _public prototype_ `virtual bool HasAnyActiveTool() const;` — @return true if there are any active tools
- L189 _public prototype_ `virtual UInteractiveTool* GetActiveTool(EToolSide Side);` — Get pointer to active Tool on a given side @param Side which Side is being requested @return pointer to Tool instance active on that Side, or nullptr if no such Tool exists
- L196 _public prototype_ `virtual UInteractiveToolBuilder* GetActiveToolBuilder(EToolSide Side);` — Get pointer to active Tool Builder on a given side @param Side which Side is being requested @return pointer to Tool Builder instance active on that Side, or nullptr if no such ToolBuilder exists
- L203 _public prototype_ `virtual FString GetActiveToolName(EToolSide Side);` — Get name of registered ToolBuilder that created active tool for given side, or empty string if no tool is active @param Side which Side is being requested @return name of tool, or empty string if no tool is active
- L210 _public prototype_ `virtual bool CanAcceptActiveTool(EToolSide Side);` — Check if an active Tool on the given Side can be Accepted in its current state @param Side which Side to check @return true if there is an active Tool and it returns true from HasAccept() and CanAccept()
- L217 _public prototype_ `virtual bool CanCancelActiveTool(EToolSide Side);` — Check if an active Tool on the given Side can be Canceled @param Side which Side to check @return true if there is an active Tool and it returns true from HasCancel()
- L224 _public prototype_ `virtual void DeactivateTool(EToolSide Side, EToolShutdownType ShutdownType);` — Shut down an active Tool on the given side @param Side which "side" you would like to shut down @param ShutdownType how should the tool be terminated (eg Accept/Cancel)
- L229 _public prototype_ `EToolShutdownType GetPreferredShutdownType(EToolSide Side, EToolShutdownReason ShutdownReason = EToolShutdownReason::Unspecified);` — Determines the preferred shutdown type for the active tool based on the tool's type and the tool manager's configuration.
- L235 _public prototype_ `virtual void ConfigureChangeTrackingMode(EToolChangeTrackingMode ChangeMode);` — Configure how tool changes emit change events. See EToolChangeTrackingMode for details.
- L240 _public prototype_ `virtual EToolChangeTrackingMode GetChangeTrackingMode() const;` — Returns how tool changes emit change events. See EToolChangeTrackingMode for details.
- L247 _public prototype_ `virtual void DisplayMessage(const FText& Message, EToolMessageLevel Level);` — Post a message via the Transactions API
- L250 _public prototype_ `virtual void PostInvalidation();` — Request an Invalidation via the Transactions API (ie to cause a repaint, etc)
- L256 _public prototype_ `virtual void BeginUndoTransaction(const FText& Description);` — Request that the Context open a Transaction, whatever that means to the current Context @param Description text description of this transaction (this is the string that appears on undo/redo in the UE Editor)
- L259 _public prototype_ `virtual void EndUndoTransaction();` — Request that the Context close and commit the open Transaction
- L262 _public prototype_ `virtual void CancelUndoTransaction() override;` — Request that the Context cancel and revert the open Transaction
- L270 _public prototype_ `virtual void EmitObjectChange(UObject* TargetObject, TUniquePtr<FToolCommandChange> Change, const FText& Description );` — Forward an FChange object to the Context @param TargetObject the object that the FChange applies to @param Change the change object that the Context should insert into the transaction history @param Description text description of this change (this is the string that appears on undo/redo in the UE Editor)
- L276 _public prototype_ `virtual bool RequestSelectionChange(const FSelectedObjectsChangeList& SelectionChange);` — Forward an FChange object to the Context
- L283 _public prototype_ `virtual void Tick(float DeltaTime);` — Tick any active Tools. Called by UInteractiveToolsContext
- L286 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI);` — Render any active Tools. Called by UInteractiveToolsContext.
- L289 _public prototype_ `virtual void DrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI);` — Let active Tools do their screen space drawing. Called by UInteractiveToolsContext.
- L304 _public prototype_ `virtual bool PostActiveToolShutdownRequest( UInteractiveTool* Tool, EToolShutdownType ShutdownType, bool bShowUnexpectedShutdownMessage = false, const FText& UnexpectedShutdownMessage = FText() );` — A Tool (or other code) can call this function to request that the Tool be deactivated. The Tool must be active. By default, ::DeactivateTool() wil be called. However if some external code has bound to the OnToolShutdownRequest delegate, the request will be forwarded to that function first (::DeactivateTool() will still be called if it returns false) If this function is called during InteractiveTool::Setup(), the Tool invocation will be aborted, ie the Tool will be immediately shutdown with EToolShutdownType::Cancel, and never become "Active"/etc. Note also that in this case the shutdown request *will not* be forwarded to the OnToolShutdownRequest delegate. @param bShowUnexpectedShutdownMessage if this was an unexpected shutdown, passing true here, along with a non-empty UnexpectedShutdownMessage, will result in OnToolUnexpectedShutdownMessage being called @param UnexpectedShutdownMessage message provided by the caller meant to explain why the Tool has unexpectedly been shut down
- L310 _public prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FOnToolShutdownRequest, UInteractiveToolManager*, UInteractiveTool*, EToolShutdownType);`
- L316 _public member_ `FOnToolShutdownRequest OnToolShutdownRequest;` — If bound, OnToolShutdownRequest is called by PostActiveToolShutdownRequest to optionally handle requests to shut down a Tool (which may be sent by the Tool itself). Return true to indicate that the request will be handled, otherwise ::DeactivateTool() will be called
- L318 _public prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnToolUnexpectedShutdownMessage, UInteractiveToolManager*, UInteractiveTool*, const FText& Message, bool bWasDuringToolSetup);`
- L324 _public member_ `FOnToolUnexpectedShutdownMessage OnToolUnexpectedShutdownMessage;` — PostActiveToolShutdownRequest() will broadcast this delegate with a Message if bShowUnexpectedShutdownMessage=true. If the shutdown was during Tool Setup/startup, bWasDuringToolSetup will be passed as true
- L332 _public function_ `virtual IToolsContextQueriesAPI* GetContextQueriesAPI()` — @return current IToolsContextQueriesAPI
- L335 _public function_ `virtual IToolsContextTransactionsAPI* GetContextTransactionsAPI() final` — @return current IToolsContextTransactionsAPI
- L337 _public prototype_ `UInteractiveGizmoManager* GetPairedGizmoManager();`
- L342 _public prototype_ `UContextObjectStore* GetContextObjectStore() const;` — @return the context object store from the owning tools context.
- L347 _public member_ `TObjectPtr<UInteractiveTool> ActiveLeftTool;` — `UPROPERTY()` — Currently-active Left Tool, or null if no Tool is active
- L351 _public member_ `TObjectPtr<UInteractiveTool> ActiveRightTool;` — `UPROPERTY()` — Currently-active Right Tool, or null if no Tool is active
- L357 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FToolManagerToolStartedSignature, UInteractiveToolManager*, UInteractiveTool*);`
- L358 _public member_ `FToolManagerToolStartedSignature OnToolStarted;`
- L360 _public prototype_ `DECLARE_MULTICAST_DELEGATE_FiveParams(FToolManagerToolPostBuildSignature, UInteractiveToolManager*, EToolSide, UInteractiveTool*, UInteractiveToolBuilder*, const FToolBuilderState&);`
- L361 _public member_ `FToolManagerToolPostBuildSignature OnToolPostBuild;`
- L363 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FToolManagerToolPostSetupSignature, UInteractiveToolManager*, EToolSide, UInteractiveTool*);`
- L364 _public member_ `FToolManagerToolPostSetupSignature OnToolPostSetup;`
- L366 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FToolManagerToolEndedSignature, UInteractiveToolManager*, UInteractiveTool*);`
- L367 _public member_ `FToolManagerToolEndedSignature OnToolEnded;`
- L370 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FToolManagerToolCancelledSignature, UInteractiveToolManager*, UInteractiveTool*, EToolShutdownType);` — Variant of OnToolEnded that also reports the EToolShutdownType
- L371 _public member_ `FToolManagerToolCancelledSignature OnToolEndedWithStatus;`
- L376 _protected member_ `IToolsContextQueriesAPI* QueriesAPI;` — Pointer to current Context-Queries implementation
- L378 _protected member_ `IToolsContextTransactionsAPI* TransactionsAPI;` — Pointer to current Transactions implementation
- L381 _protected member_ `UInputRouter* InputRouter;` — Pointer to current InputRouter (Context owns this)
- L384 _protected member_ `bool bIsActive = false;` — This flag is set to true on Initialize() and false on Shutdown().
- L388 _protected member_ `bool bInToolSetup = false;` — This bool is for handling the case where a Tool posts a shutdown request during it's Setup() call. In that case we will terminate the Tool immediately
- L389 _protected member_ `bool bToolRequestedTerminationDuringSetup = false;`
- L394 _protected member_ `TMap<FString, TObjectPtr<UInteractiveToolBuilder>> ToolBuilders;` — `UPROPERTY()` — Current set of named ToolBuilders
- L397 _protected member_ `FString ActiveLeftBuilderName;` — Currently-active Left ToolBuilder
- L398 _protected member_ `UInteractiveToolBuilder* ActiveLeftBuilder;`
- L400 _protected member_ `FString ActiveRightBuilderName;` — Currently-active Right ToolBuilder
- L401 _protected member_ `UInteractiveToolBuilder* ActiveRightBuilder;`
- L403 _protected member_ `EToolChangeTrackingMode ActiveToolChangeTrackingMode;`
- L404 _protected member_ `EToolManagerToolSwitchMode ToolSwitchMode = EToolManagerToolSwitchMode::CustomizableAcceptIfAble;`
- L406 _protected member_ `FString ActiveLeftToolName;`
- L407 _protected member_ `FString ActiveRightToolName;`
- L408 _protected member_ `bool bInToolShutdown = false;`
- L411 _protected member_ `bool bActiveToolMadeSelectionStoreRequest = false;` — `UE_DEPRECATED(5.5, "bActiveToolMadeSelectionStoreRequest is no longer used.")`
- L413 _protected prototype_ `virtual bool ActivateToolInternal(EToolSide Side);`
- L414 _protected prototype_ `virtual void DeactivateToolInternal(EToolSide Side, EToolShutdownType ShutdownType);`

#### class `FBeginToolChange`  
`class FBeginToolChange : public FToolCommandChange`  
_L427-437_
- inherits: `FToolCommandChange`
- desc: FBeginToolChange is used by UInteractiveToolManager to back out of a Tool on Undo. No action is taken on Redo, ie we do not re-start the Tool on Redo.
- L430 _public prototype_ `virtual void Apply(UObject* Object) override;`
- L432 _public prototype_ `virtual void Revert(UObject* Object) override;`
- L434 _public prototype_ `virtual bool HasExpired(UObject* Object) const override;`
- L436 _public prototype_ `virtual FString ToString() const override;`

#### class `FActivateToolChange`  
`class FActivateToolChange : public FToolCommandChange`  
_L443-460_
- inherits: `FToolCommandChange`
- desc: FActivateToolChange is used by UInteractiveToolManager to change the active tool. This Change has two modes, either activating or deactivating.
- L446 _public member_ `EToolSide Side;`
- L447 _public member_ `FString ToolType;`
- L448 _public member_ `bool bIsDeactivate = false;`
- L449 _public member_ `EToolShutdownType ShutdownType;`
- L451 _public function_ `FActivateToolChange(EToolSide SideIn, FString ToolTypeIn) : Side(SideIn), ToolType(ToolTypeIn), bIsDeactivate(false)`
- L453 _public function_ `FActivateToolChange(EToolSide SideIn, FString ToolTypeIn, EToolShutdownType ShutdownTypeIn) : Side(SideIn), ToolType(ToolTypeIn), bIsDeactivate(true), ShutdownType(ShutdownTypeIn)`
- L456 _public prototype_ `virtual void Apply(UObject* Object) override;`
- L457 _public prototype_ `virtual void Revert(UObject* Object) override;`
- L458 _public prototype_ `virtual bool HasExpired(UObject* Object) const override;`
- L459 _public prototype_ `virtual FString ToString() const override;`

#### class `FToolChangeWrapperChange`  
`class FToolChangeWrapperChange : public FToolCommandChange`  
_L470-484_
- inherits: `FToolCommandChange`
- desc: FToolChangeWrapperChange wraps an FChange emitted by an InteractiveTool, allowing us to Expire the change without each FChange implementation needing to handle this explicitly.
- L473 _public member_ `TWeakObjectPtr<UInteractiveToolManager> ToolManager;`
- L474 _public member_ `TWeakObjectPtr<UInteractiveTool> ActiveTool;`
- L475 _public member_ `TUniquePtr<FToolCommandChange> ToolChange;`
- L477 _public prototype_ `virtual void Apply(UObject* Object) override;`
- L479 _public prototype_ `virtual void Revert(UObject* Object) override;`
- L481 _public prototype_ `virtual bool HasExpired(UObject* Object) const override;`
- L483 _public prototype_ `virtual FString ToString() const override;`

#### Free symbols / members of external scopes

- L310 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FOnToolShutdownRequest, UInteractiveToolManager*, UInteractiveTool*, EToolShutdownType);`
- L318 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnToolUnexpectedShutdownMessage, UInteractiveToolManager*, UInteractiveTool*, const FText& Message, bool bWasDuringToolSetup);`
- L357 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FToolManagerToolStartedSignature, UInteractiveToolManager*, UInteractiveTool*);`
- L360 _delegate_ `DECLARE_MULTICAST_DELEGATE_FiveParams(FToolManagerToolPostBuildSignature, UInteractiveToolManager*, EToolSide, UInteractiveTool*, UInteractiveToolBuilder*, const FToolBuilderState&);`
- L363 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FToolManagerToolPostSetupSignature, UInteractiveToolManager*, EToolSide, UInteractiveTool*);`
- L366 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FToolManagerToolEndedSignature, UInteractiveToolManager*, UInteractiveTool*);`
- L370 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FToolManagerToolCancelledSignature, UInteractiveToolManager*, UInteractiveTool*, EToolShutdownType);` — Variant of OnToolEnded that also reports the EToolShutdownType

### `Source/Runtime/InteractiveToolsFramework/Public/InteractiveToolObjects.h` (Public)


#### class `AInternalToolFrameworkActor`  
`class AInternalToolFrameworkActor : public AActor`  
_L18-35_
- reflection: `UCLASS(Transient, NotPlaceable, Hidden, NotBlueprintable, NotBlueprintType, MinimalAPI)`
- inherits: `AActor`
- desc: AInternalToolFrameworkActor is a base class for internal Actors that the ToolsFramework may spawn (for gizmos, mesh previews, etc). These Actors may need special-case handling, for example to prevent the user from selecting and deleting them.
- L27 _public member_ `bool bIsSelectableInEditor = false;` — `UPROPERTY()` — Controls whether this InternalToolFrameworkActor can be selected in the Editor.
- L30 _public function_ `virtual bool IsSelectable() const override`

#### class `UToolFrameworkComponent`  
`class UToolFrameworkComponent : public UInterface`  
_L43-46_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`
- desc: UInterface for IToolFrameworkComponent

#### class `IToolFrameworkComponent`  
`class IToolFrameworkComponent`  
_L50-55_
- desc: IToolFrameworkComponent is an interface we can attach to custom Components used in the Tools framework. Currently this interface is only used to identify such Components (to prevent certain Actors from being deleted)

### `Source/Runtime/InteractiveToolsFramework/Public/InteractiveToolQueryInterfaces.h` (Public)


#### class `UInteractiveToolCameraFocusAPI`  
`class UInteractiveToolCameraFocusAPI : public UInterface`  
_L20-23_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`
- desc: UInterface for IInteractiveToolCameraFocusAPI

#### class `IInteractiveToolCameraFocusAPI`  
`class IInteractiveToolCameraFocusAPI`  
_L40-68_
- desc: IInteractiveToolCameraFocusAPI provides two functions that can be used to extract "Focus" / "Region of Interest" information about an active Tool: GetWorldSpaceFocusBox() - provides a bounding box for an "active region" if one is known. An example of using the FocusBox would be to center/zoom the camera in a 3D viewport onto this box when the user hits a hotkey (eg 'f' in the Editor). Should default to the entire active object, if no subregion is available. GetWorldSpaceFocusPoint() - provides a "Focus Point" at the cursor ray if one is known. This can be used to (eg) center the camera at the focus point. The above functions should not be called unless the corresponding SupportsX() function returns true.
- L48 _public function_ `virtual bool SupportsWorldSpaceFocusBox()` — @return true if the implementation can provide a Focus Box
- L53 _public function_ `virtual FBox GetWorldSpaceFocusBox()` — @return the current Focus Box
- L58 _public function_ `virtual bool SupportsWorldSpaceFocusPoint()` — @return true if the implementation can provide a Focus Point
- L65 _public function_ `virtual bool GetWorldSpaceFocusPoint(const FRay& WorldRay, FVector& PointOut)` — @param WorldRay 3D Ray that should be used to find the focus point, generally ray under cursor @param PointOut computed Focus Point @return true if a Focus Point was found, can return false if (eg) the ray missed the target objects

#### class `UInteractiveToolNestedAcceptCancelAPI`  
`class UInteractiveToolNestedAcceptCancelAPI : public UInterface`  
_L78-81_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`
- desc: UInterface for IInteractiveToolNestedAcceptCancelAPI

#### class `IInteractiveToolNestedAcceptCancelAPI`  
`class IInteractiveToolNestedAcceptCancelAPI`  
_L91-131_
- desc: IInteractiveToolNestedAcceptCancelAPI provides an API for a Tool to publish intent and ability to Accept or Cancel sub-operations. For example in a Tool that has an editable active Selection, we might want the Escape hotkey to Clear any active selection, and then on a second press, to Cancel the Tool. This API allows a Tool to say "I can consume a Cancel action", and similarly for Accept (although this is much less common).
- L99 _public function_ `virtual bool SupportsNestedCancelCommand()` — @return true if the implementor of this API may be able to consume a Cancel action
- L104 _public function_ `virtual bool CanCurrentlyNestedCancel()` — @return true if the implementor of this API can currently consume a Cancel action
- L110 _public function_ `virtual bool ExecuteNestedCancelCommand()` — Called by Editor levels to tell the implementor (eg Tool) to execute a nested Cancel action @return true if the implementor consumed the Cancel action
- L117 _public function_ `virtual bool SupportsNestedAcceptCommand()` — @return true if the implementor of this API may be able to consume an Accept action
- L122 _public function_ `virtual bool CanCurrentlyNestedAccept()` — @return true if the implementor of this API can currently consume an Accept action
- L128 _public function_ `virtual bool ExecuteNestedAcceptCommand()` — Called by Editor levels to tell the implementor (eg Tool) to execute a nested Accept action @return true if the implementor consumed the Accept action

#### class `UInteractiveToolShutdownQueryAPI`  
`class UInteractiveToolShutdownQueryAPI : public UInterface`  
_L135-138_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`
- desc: UInterface for IInteractiveToolShutdownQueryAPI

#### class `IInteractiveToolShutdownQueryAPI`  
`class IInteractiveToolShutdownQueryAPI`  
_L152-208_
- desc: Allows an interactive tool to influence the way it is shut down, if the tool host supports that kind of customization. This can be helpful, for example, if your tool prefers a specific shutdown type in various situations, but a tool can't rely on this interface being queried unless it knows that it will only be used by systems that respect it. A simple interactive tools framework context implementation does not need to bother querying the tool on its preferences (aside from the already existing CanAccept method on the actual tool object). Note that there are different systems that might choose to query this interface. The tool manager might want to query it if its ToolSwitchMode is set to be customizable, or the mode or mode toolkit might query it when shutting down the tool in various situations.
- L172 _public function_ `virtual EToolShutdownType GetPreferredShutdownType(EShutdownReason ShutdownReason, EToolShutdownType StandardShutdownType) const PRAGMA_ENABLE_DEPRECATION_WARNINGS` — `UE_DEPRECATED(5.7, "Prefer the GetPreferredShutdownType variant which uses EToolShutdownReason.")` — Given a shutdown situation, tells what kind of shutdown method the tool might prefer. @param ShutdownReason Information about the shutdown type @param StandardShutdownType Shutdown type that the host would use if it weren't giving the tool a chance to customize the behavior. @return Shutdown type that the tool would prefer that the host use in this situation.
- L185 _public function_ `virtual EToolShutdownType GetPreferredShutdownType(EToolShutdownReason ShutdownReason, EToolShutdownType StandardShutdownType) const` — Given a shutdown situation, tells what kind of shutdown method the tool might prefer. @param ShutdownReason Information about the shutdown type @param StandardShutdownType Shutdown type that the host would use if it weren't giving the tool a chance to customize the behavior. @return Shutdown type that the tool would prefer that the host use in this situation.

#### enum `IInteractiveToolShutdownQueryAPI::EShutdownReason`  
`enum class UE_DEPRECATED(5.7, "EShutdownReason has moved to InteractiveTool.h (under the name EToolShutdownReason).") EShutdownReason`  
_L157-161_
- L160 _public enumerator_ `SwitchTool` — Another tool is being activated without the user having explicitly shut down this one.

#### class `UInteractiveToolExclusiveToolAPI`  
`class UInteractiveToolExclusiveToolAPI : public UInterface`  
_L213-216_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`
- desc: UInterface for IInteractiveToolExclusiveToolAPI

#### class `IInteractiveToolExclusiveToolAPI`  
`class IInteractiveToolExclusiveToolAPI`  
_L225-228_
- desc: IInteractiveToolExclusiveToolAPI provides an API to inform the ToolManager about tool exclusivity. An exclusive tool prevents other tools from building & activating while the tool is active. This is useful in scenarios where tools want to enforce an explicit Accept, Cancel or Complete user input to exit the tool.

#### class `UInteractiveToolEditorGizmoAPI`  
`class UInteractiveToolEditorGizmoAPI : public UInterface`  
_L234-237_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`
- desc: UInterface for IInteractiveToolEditorGizmoAPI

#### class `IInteractiveToolEditorGizmoAPI`  
`class IInteractiveToolEditorGizmoAPI`  
_L243-252_
- desc: IInteractiveToolEditorGizmoAPI provides an API to indicate whether the standard editor gizmos can be enabled while this tool is active.
- L251 _public function_ `virtual bool GetAllowStandardEditorGizmos()` — @return true if the tool implementing this API allows the editor gizmos to be enabled while the tool is active

#### class `UInteractiveToolManageGeometrySelectionAPI`  
`class UInteractiveToolManageGeometrySelectionAPI : public UInterface`  
_L258-261_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`
- desc: UInterface for IInteractiveToolManageGeometrySelectionAPI

#### class `IInteractiveToolManageGeometrySelectionAPI`  
`class IInteractiveToolManageGeometrySelectionAPI`  
_L266-275_
- desc: Provides an API to allow a tool to report how it has affected (updated or invalidated) geometry selections on the tool's targets
- L274 _public function_ `virtual bool IsInputSelectionValidOnOutput()` — @return true if the tool implementing this API has not updated the geometry selection or modified geometry to invalidate any previous geometry selection, i.e. has not removed/added vertices/edges/triangles

### `Source/Runtime/InteractiveToolsFramework/Public/InteractiveToolsContext.h` (Public)


#### class `UInteractiveToolsContext`  
`class UInteractiveToolsContext : public UObject`  
_L39-166_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UObject`
- desc: InteractiveToolsContext owns the core parts of an Interactive Tools Framework implementation - the InputRouter, ToolManager, GizmoManager, TargetManager, ToolGroupManager, and ContextStore. In the simplest use case, UInteractiveToolsContext is just a top-level container that will keep the various UObjects alive, and provide an easy way to access them. However in a more complex situation it may be desirable to subclass and extend the ToolsContext. For example, UEdModeInteractiveToolsContext allows a ToolsContext to live within a UEdMode.
- L44 _public prototype_ `UInteractiveToolsContext();`
- L62 _public prototype_ `virtual void SetCreateInputRouterFunc(TUniqueFunction<UInputRouter* (const FContextInitInfo&)> Func);` — Replace the internal functions that are called to create/destroy the sub-objects owned by the ITC. By doing this, clients of the ITF can provide their own subclass implementations, or do other custom setup/teardown as necessary. See comments above CreateInputRouterFunc below
- L63 _public prototype_ `virtual void SetCreateToolManagerFunc(TUniqueFunction<UInteractiveToolManager* (const FContextInitInfo&)> Func);`
- L64 _public prototype_ `virtual void SetCreateToolTargetManagerFunc(TUniqueFunction<UToolTargetManager* (const FContextInitInfo&)> Func);`
- L65 _public prototype_ `virtual void SetCreateGizmoManagerFunc(TUniqueFunction<UInteractiveGizmoManager* (const FContextInitInfo&)> Func);`
- L66 _public prototype_ `virtual void SetCreateContextStoreFunc(TUniqueFunction<UContextObjectStore* (const FContextInitInfo&)> Func);`
- L67 _public prototype_ `virtual void SetCreateToolGroupManagerFunc(TUniqueFunction<UToolGroupManager* (const FContextInitInfo&)> Func);`
- L69 _public prototype_ `virtual void SetShutdownInputRouterFunc(TUniqueFunction<void(UInputRouter*)> Func);`
- L70 _public prototype_ `virtual void SetShutdownToolManagerFunc(TUniqueFunction<void(UInteractiveToolManager*)> Func);`
- L71 _public prototype_ `virtual void SetShutdownToolTargetManagerFunc(TUniqueFunction<void(UToolTargetManager*)> Func);`
- L72 _public prototype_ `virtual void SetShutdownGizmoManagerFunc(TUniqueFunction<void(UInteractiveGizmoManager*)> Func);`
- L73 _public prototype_ `virtual void SetShutdownContextStoreFunc(TUniqueFunction<void(UContextObjectStore*)> Func);`
- L74 _public prototype_ `virtual void SetShutdownToolGroupManagerFunc(TUniqueFunction<void(UToolGroupManager*)> Func);`
- L81 _public prototype_ `virtual void Initialize(IToolsContextQueriesAPI* QueriesAPI, IToolsContextTransactionsAPI* TransactionsAPI);` — Initialize the Context. This creates the InputRouter, ToolManager, GizmoManager, TargetManager, and ContextStore @param QueriesAPI client-provided implementation of the API for querying the higher-evel scene state @param TransactionsAPI client-provided implementation of the API for publishing events and transactions
- L84 _public prototype_ `virtual void Shutdown();` — Shutdown Context by destroying InputRouter and ToolManager
- L86 _public prototype_ `virtual void DeactivateActiveTool(EToolSide WhichSide, EToolShutdownType ShutdownType);`
- L87 _public prototype_ `virtual void DeactivateAllActiveTools(EToolShutdownType ShutdownType);`
- L89 _public prototype_ `bool CanStartTool(EToolSide WhichSide, const FString& ToolTypeIdentifier) const;`
- L90 _public prototype_ `bool HasActiveTool(EToolSide WhichSide) const;`
- L91 _public prototype_ `FString GetActiveToolName(EToolSide WhichSide) const;`
- L92 _public prototype_ `bool ActiveToolHasAccept(EToolSide WhichSide) const;`
- L93 _public prototype_ `bool CanAcceptActiveTool(EToolSide WhichSide) const;`
- L94 _public prototype_ `bool CanCancelActiveTool(EToolSide WhichSide) const;`
- L95 _public prototype_ `bool CanCompleteActiveTool(EToolSide WhichSide) const;`
- L96 _public prototype_ `bool StartTool(EToolSide WhichSide, const FString& ToolTypeIdentifier);`
- L97 _public prototype_ `void EndTool(EToolSide WhichSide, EToolShutdownType ShutdownType);`
- L98 _public prototype_ `bool IsToolActive(EToolSide WhichSide, const FString ToolIdentifier) const;`
- L102 _public prototype_ `virtual void PostToolNotificationMessage(const FText& Message);` — forwards message to OnToolNotificationMessage delegate
- L103 _public prototype_ `virtual void PostToolWarningMessage(const FText& Message);`
- L105 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FToolsContextToolNotification, const FText&);`
- L106 _public member_ `FToolsContextToolNotification OnToolNotificationMessage;`
- L107 _public member_ `FToolsContextToolNotification OnToolWarningMessage;`
- L112 _public member_ `TObjectPtr<UInputRouter> InputRouter;` — `UPROPERTY()` — current UInputRouter for this Context
- L116 _public member_ `TObjectPtr<UToolTargetManager> TargetManager;` — `UPROPERTY()` — current UToolTargetManager for this Context
- L120 _public member_ `TObjectPtr<UInteractiveToolManager> ToolManager;` — `UPROPERTY()` — current UInteractiveToolManager for this Context
- L124 _public member_ `TObjectPtr<UInteractiveGizmoManager> GizmoManager;` — `UPROPERTY()` — current UInteractiveGizmoManager for this Context
- L128 _public member_ `TObjectPtr<UToolGroupManager> ToolGroupManager;` — `UPROPERTY()` — current UToolGroupManager for this Context
- L135 _public member_ `TObjectPtr<UContextObjectStore> ContextObjectStore;` — `UPROPERTY()` — Current Context Object Store for this Context. Stores arbitrary objects which share data or expose APIs across interactive tools and managers belonging to this context.
- L146 _protected member_ `TUniqueFunction<UInputRouter* (const FContextInitInfo&)> CreateInputRouterFunc;` — Initialize() calls these functions to create the main child objects needed to operate the Tools Framework - InputRouter, ToolManager, GizmoManager, TargetManager, ContextStore. Default implementations are set up in the UInteractiveToolsContext() constructor, however users of the framework are free to replace these with subclasses, or do more complex initialization, by replacing these functions with their own versions before calling Initialize(). (the same could be accomplished by subclassing and overriding Initialize(), however using these lambda functions will be a safer alternative in many cases)
- L147 _protected member_ `TUniqueFunction<UInteractiveToolManager* (const FContextInitInfo&)> CreateToolManagerFunc;`
- L148 _protected member_ `TUniqueFunction<UToolTargetManager* (const FContextInitInfo&)> CreateToolTargetManagerFunc;`
- L149 _protected member_ `TUniqueFunction<UInteractiveGizmoManager* (const FContextInitInfo&)> CreateGizmoManagerFunc;`
- L150 _protected member_ `TUniqueFunction<UContextObjectStore* (const FContextInitInfo&)> CreateContextStoreFunc;`
- L151 _protected member_ `TUniqueFunction<UToolGroupManager* (const FContextInitInfo&)> CreateToolGroupManagerFunc;`
- L155 _protected member_ `TUniqueFunction<void(UInputRouter*)> ShutdownInputRouterFunc;` — Analogous to the CreateX() functions above, these function are called by Shutdown() to terminate and clean up after the various elements.
- L156 _protected member_ `TUniqueFunction<void(UInteractiveToolManager*)> ShutdownToolManagerFunc;`
- L157 _protected member_ `TUniqueFunction<void(UToolTargetManager*)> ShutdownToolTargetManagerFunc;`
- L158 _protected member_ `TUniqueFunction<void(UInteractiveGizmoManager*)> ShutdownGizmoManagerFunc;`
- L159 _protected member_ `TUniqueFunction<void(UContextObjectStore*)> ShutdownContextStoreFunc;`
- L160 _protected member_ `TUniqueFunction<void(UToolGroupManager*)> ShutdownToolGroupManagerFunc;`
- L165 _protected member_ `TSoftClassPtr<UInteractiveToolManager> ToolManagerClass;` — `UPROPERTY()` — todo: deprecate and remove this, can now be accomplished via CreateToolManagerFunc()

#### struct `UInteractiveToolsContext::FContextInitInfo`  
`struct FContextInitInfo`  
_L49-55_
- desc: FContextInitInfo is used by Initialize() to pass information to the various creator functions below. See ::UInteractiveToolsContext() and ::Initialize() for how these fields are used/initialized. In particular, InputRouter will not be set until after the UInputRouter has been created
- L51 _public member_ `UInteractiveToolsContext* ToolsContext = nullptr;`
- L52 _public member_ `IToolsContextQueriesAPI* QueriesAPI = nullptr;`
- L53 _public member_ `IToolsContextTransactionsAPI* TransactionsAPI = nullptr;`
- L54 _public member_ `UInputRouter* InputRouter = nullptr;`

#### Free symbols / members of external scopes

- L105 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FToolsContextToolNotification, const FText&);`

### `Source/Runtime/InteractiveToolsFramework/Public/InteractiveToolsFramework.h` (Public)


#### class `FInteractiveToolsFrameworkModule`  
`class FInteractiveToolsFrameworkModule : public IModuleInterface`  
_L9-16_
- inherits: `IModuleInterface`
- L14 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L15 _public prototype_ `virtual void ShutdownModule() override;`

### `Source/Runtime/InteractiveToolsFramework/Public/MultiSelectionTool.h` (Public)


#### class `UMultiSelectionTool`  
`class UMultiSelectionTool : public UInteractiveTool, public IInteractiveToolCameraFocusAPI`  
_L13-54_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UInteractiveTool,IInteractiveToolCameraFocusAPI`
- L17 _public function_ `void SetTargets(TArray<TObjectPtr<UToolTarget>> TargetsIn)`
- L25 _public function_ `virtual bool AreAllTargetsValid() const` — @return true if all ComponentTargets of this tool are still valid
- L39 _public function_ `virtual bool CanAccept() const override`
- L46 _protected member_ `TArray<TObjectPtr<UToolTarget>> Targets{};` — `UPROPERTY()`
- L50 _public prototype_ `virtual bool SupportsWorldSpaceFocusBox() override;` — IInteractiveToolCameraFocusAPI implementation
- L51 _public prototype_ `virtual FBox GetWorldSpaceFocusBox() override;`
- L52 _public prototype_ `virtual bool SupportsWorldSpaceFocusPoint() override;`
- L53 _public prototype_ `virtual bool GetWorldSpaceFocusPoint(const FRay& WorldRay, FVector& PointOut) override;`

### `Source/Runtime/InteractiveToolsFramework/Public/SceneQueries/SceneSnappingManager.h` (Public)


#### struct `FSceneQueryVisibilityFilter`  
`struct FSceneQueryVisibilityFilter`  
_L23-33_
- L26 _public member_ `const TArray<const UPrimitiveComponent*>* ComponentsToIgnore = nullptr;` — Optional: components to consider invisible even if they aren't.
- L29 _public member_ `const TArray<const UPrimitiveComponent*>* InvisibleComponentsToInclude = nullptr;` — Optional: components to consider visible even if they aren't.
- L32 _public prototype_ `bool IsVisible(const UPrimitiveComponent* Component) const;` — @return true if the Component is currently configured as visible (does not consider ComponentsToIgnore or InvisibleComponentsToInclude lists)

#### enum `ESceneHitQueryTargetType`  
`enum class ESceneHitQueryTargetType : uint8`  
_L37-52_
- reflection: `UENUM()`
- desc: Types of Hit Targets that a caller may want to run hit queries against.
- L39 _public enumerator_ `None = 0`
- L41 _public enumerator_ `MeshVertex = 1` — Consider any mesh vertex
- L43 _public enumerator_ `MeshEdge = 2` — Consider any mesh edge
- L45 _public enumerator_ `PrimitiveSurface = 4` — Hit any primitive with a surface representation
- L47 _public enumerator_ `PrimitiveTransform = 8` — Any primitive with a transform representation
- L49 _public enumerator_ `Custom = 16` — As defined by an FName
- L51 _public enumerator_ `All = MeshVertex | MeshEdge | PrimitiveSurface | PrimitiveTransform | Custom`

#### struct `FSceneHitQueryRequest`  
`struct FSceneHitQueryRequest`  
_L59-73_
- desc: Configuration variables for a USceneSnappingManager hit query request.
- L62 _public member_ `FRay WorldRay;` — Scene query ray.
- L65 _public member_ `ESceneHitQueryTargetType TargetTypes = ESceneHitQueryTargetType::All;` — What does the caller want to try to hit.
- L68 _public member_ `TSet<FName> CustomTargetTypes;` — The name of the custom TargetTypes, if applicable.
- L70 _public member_ `bool bWantHitGeometryInfo = false;`
- L72 _public member_ `FSceneQueryVisibilityFilter VisibilityFilter;`

#### struct `FSceneHitQueryResult`  
`struct FSceneHitQueryResult`  
_L79-99_
- desc: Computed result of a USceneSnappingManager hit query request
- L82 _public member_ `AActor* TargetActor = nullptr;` — Actor that owns hit target
- L84 _public member_ `UPrimitiveComponent* TargetComponent = nullptr;` — Component that owns hit target
- L87 _public member_ `FVector3d Position = FVector3d::Zero();` — hit position
- L89 _public member_ `FVector3d Normal = FVector3d::UnitZ();` — hit normal
- L92 _public member_ `int HitTriIndex = -1;` — integer ID of triangle that was hit
- L94 _public member_ `FVector3d TriVertices[3];` — Vertices of triangle that was hit (for debugging, may not be set)
- L96 _public member_ `FHitResult HitResult;`
- L98 _public prototype_ `void InitializeHitResult(const FSceneHitQueryRequest& FromRequest);`

#### enum `ESceneSnapQueryType`  
`enum class ESceneSnapQueryType : uint8`  
_L106-118_
- reflection: `UENUM()`
- desc: Types of Snap Queries that a USceneSnappingManager may support
- L109 _public enumerator_ `Position = 1` — Position/Translation snapping
- L111 _public enumerator_ `Rotation = 2` — Full rotation snapping (which could affect the axis of rotation)
- L113 _public enumerator_ `RotationAngle = 3` — Snaps the rotation angle only (in degrees).
- L115 _public enumerator_ `Scale = 4` — Scale snapping
- L117 _public enumerator_ `Transform = 5` — Transform snapping (ie. snap to surface is both position and rotation)

#### enum `ESceneSnapQueryTargetType`  
`enum class ESceneSnapQueryTargetType : uint8`  
_L123-138_
- reflection: `UENUM()`
- desc: Types of Snap Targets that a caller may want to run snap queries against.
- L125 _public enumerator_ `None = 0`
- L127 _public enumerator_ `MeshVertex = 1` — Consider any mesh vertex
- L129 _public enumerator_ `MeshEdge = 2` — Consider any mesh edge
- L131 _public enumerator_ `Grid = 4` — Grid Snapping
- L133 _public enumerator_ `ObjectTransform = 8` — Any object with a transform representation
- L135 _public enumerator_ `Custom = 16` — As defined by an FName
- L137 _public enumerator_ `All = MeshVertex | MeshEdge | Grid | ObjectTransform | Custom`

#### enum `ESceneSnapQueryTargetResult`  
`enum class ESceneSnapQueryTargetResult : uint8`  
_L145-158_
- reflection: `UENUM()`
- desc: Describes the result of the attempted snap operation. Note that this differs to FSceneSnapQueryResult in that it only indicates the success or failure of the snap, not the resulting data.
- L148 _public enumerator_ `NotSnapped` — Snapping was valid and attempted, but did not snap to target.
- L151 _public enumerator_ `Snapped` — Snapping was valid and attempted, and did snap to target. This may indicate no further snapping operations should be attempted for the given interaction.
- L154 _public enumerator_ `Disabled` — Snapping is valid and supported, but is disabled (usually due to a user setting).
- L157 _public enumerator_ `Unsupported` — The snapping query isn't valid for this Query Target.

#### class `FSceneSnapQueryTargetHandler`  
`class FSceneSnapQueryTargetHandler`  
_L162-197_
- desc: A custom query target implementation, allowing extensibility and handling of custom targets not defined in the ESceneSnapQueryTargetType enum.
- L165 _public prototype_ `virtual ~FSceneSnapQueryTargetHandler() = default;`
- L167 _public prototype_ `virtual ESceneSnapQueryTargetResult SnapPosition(const FSceneSnapQueryRequest& InRequest, TArray<FSceneSnapQueryResult>& OutResults) const;`
- L168 _public function_ `virtual ESceneSnapQueryTargetResult SnapPosition(const FVector& InPosition, FVector& OutSnappedPosition, const EAxisList::Type InAxisList = EAxisList::All) const`
- L169 _public function_ `virtual ESceneSnapQueryTargetResult SnapPositionAxis(const double InAxisValue, double& OutSnappedAxisValue, const EAxisList::Type InAxis) const`
- L171 _public prototype_ `virtual ESceneSnapQueryTargetResult SnapRotation(const FSceneSnapQueryRequest& InRequest, TArray<FSceneSnapQueryResult>& OutResults) const;`
- L172 _public function_ `virtual ESceneSnapQueryTargetResult SnapRotation(const FQuat& InRotation, FQuat& OutSnappedRotation, const EAxisList::Type InAxisList = EAxisList::All) const`
- L173 _public function_ `virtual ESceneSnapQueryTargetResult SnapRotationAxisAngle(const double& InAngle, double& OutSnappedAngle, const EAxisList::Type InAxis) const`
- L175 _public prototype_ `virtual ESceneSnapQueryTargetResult SnapScale(const FSceneSnapQueryRequest& InRequest, TArray<FSceneSnapQueryResult>& OutResults) const;`
- L176 _public function_ `virtual ESceneSnapQueryTargetResult SnapScale(const FVector& InScale, FVector& OutSnappedScale, const EAxisList::Type InAxisList = EAxisList::All) const`
- L177 _public function_ `virtual ESceneSnapQueryTargetResult SnapScaleAxis(const double InAxisValue, double& OutSnappedAxisValue, const EAxisList::Type InAxis) const`
- L179 _public function_ `virtual ESceneSnapQueryTargetType GetTargetTypes() const`
- L182 _public function_ `virtual bool IsQueryTypeSupported(const ESceneSnapQueryType InQueryType) const` — Returns true if the given query type can -ever- be supported, regardless of any variable state.
- L184 _public function_ `bool operator==(const FSceneSnapQueryTargetHandler& InOther) const`
- L189 _public function_ `bool operator !=(const FSceneSnapQueryTargetHandler& InOther) const`
- L196 _public member_ `FName TargetName;` — Unique query target name, ie. "Grid"

#### class `TSceneSnapQueryTargetHandler`  
`template <typename TargetRequestParametersType UE_REQUIRES(std::is_class_v<TargetRequestParametersType>)> class TSceneSnapQueryTargetHandler : public FSceneSnapQueryTargetHandler`  
_L207-230_
- inherits: `FSceneSnapQueryTargetHandler`
- desc: A custom query target implementation with typed parameters, allowing extensibility and handling of custom targets not defined in the ESceneSnapQueryTargetType enum.
- L210 _public function_ `virtual ESceneSnapQueryTargetResult SnapPosition(const FSceneSnapQueryRequest& InRequest, TArray<FSceneSnapQueryResult>& OutResults) const override`
- L211 _public function_ `virtual ESceneSnapQueryTargetResult SnapPosition(const FVector& InPosition, FVector& OutSnappedPosition, const EAxisList::Type InAxisList = EAxisList::All) const override`
- L212 _public function_ `virtual ESceneSnapQueryTargetResult SnapPosition(const TargetRequestParametersType& InTargetRequest, const FVector& InPosition, FVector& OutSnappedPosition, const EAxisList::Type InAxisList = EAxisList::All) const`
- L214 _public function_ `virtual ESceneSnapQueryTargetResult SnapPositionAxis(const double InAxisValue, double& OutSnappedAxisValue, const EAxisList::Type InAxis) const override`
- L215 _public function_ `virtual ESceneSnapQueryTargetResult SnapPositionAxis(const TargetRequestParametersType& InTargetRequest, const double InAxisValue, double& OutSnappedAxisValue, const EAxisList::Type InAxis) const`
- L217 _public function_ `virtual ESceneSnapQueryTargetResult SnapRotation(const FSceneSnapQueryRequest& InRequest, TArray<FSceneSnapQueryResult>& OutResults) const override`
- L218 _public function_ `virtual ESceneSnapQueryTargetResult SnapRotation(const FQuat& InRotation, FQuat& OutSnappedRotation, const EAxisList::Type InAxisList = EAxisList::All) const override`
- L219 _public function_ `virtual ESceneSnapQueryTargetResult SnapRotation(const TargetRequestParametersType& InTargetRequest, const FQuat& InRotation, FQuat& OutSnappedRotation, const EAxisList::Type InAxisList = EAxisList::All) const`
- L221 _public function_ `virtual ESceneSnapQueryTargetResult SnapRotationAxisAngle(const double& InAngle, double& OutSnappedAngle, const EAxisList::Type InAxis) const override`
- L222 _public function_ `virtual ESceneSnapQueryTargetResult SnapRotationAxisAngle(const TargetRequestParametersType& InTargetRequest, const double& InAngle, double& OutSnappedAngle, const EAxisList::Type InAxis) const`
- L224 _public function_ `virtual ESceneSnapQueryTargetResult SnapScale(const FSceneSnapQueryRequest& InRequest, TArray<FSceneSnapQueryResult>& OutResults) const override`
- L225 _public function_ `virtual ESceneSnapQueryTargetResult SnapScale(const FVector& InScale, FVector& OutSnappedScale, const EAxisList::Type InAxisList = EAxisList::All) const override`
- L226 _public function_ `virtual ESceneSnapQueryTargetResult SnapScale(const TargetRequestParametersType& InTargetRequest, const FVector& InScale, FVector& OutSnappedScale, const EAxisList::Type InAxisList = EAxisList::All) const`
- L228 _public function_ `virtual ESceneSnapQueryTargetResult SnapScaleAxis(const double InAxisValue, double& OutSnappedAxisValue, const EAxisList::Type InAxis) const override`
- L229 _public function_ `virtual ESceneSnapQueryTargetResult SnapScaleAxis(const TargetRequestParametersType& InTargetRequest, const double InAxisValue, double& OutSnappedAxisValue, const EAxisList::Type InAxis) const`

#### struct `FSceneSnapQueryRequest`  
`struct FSceneSnapQueryRequest`  
_L235-299_
- desc: Configuration variables for a USceneSnappingManager snap query request.
- L238 _public member_ `EToolContextCoordinateSystem RequestCoordinateSpace;` — Coordinate space of the request data
- L241 _public member_ `FTransform CoordinateTransform = FTransform::Identity;` — Coordinate transform, which may be the same as Transform but could also be a screen-space plane.
- L244 _public member_ `TOptional<EToolContextCoordinateSystem> ResultCoordinateSpace;` — Optionally specify the desired result coordinate space, which can prevent unnecessary transforms. Defaults to the requested RequestCoordinateSpace
- L247 _public member_ `ESceneSnapQueryType RequestType = ESceneSnapQueryType::Position;` — What type of snap query geometry is this
- L250 _public member_ `ESceneSnapQueryTargetType TargetTypes = ESceneSnapQueryTargetType::Grid;` — What does caller want to try to snap to
- L253 _public member_ `TSet<FName> CustomTargetTypes;` — The name of the custom TargetTypes, if applicable.
- L256 _public member_ `TOptional<FVector> GridSize{};` — Optional explicitly specified position grid
- L259 _public member_ `TOptional<FRotator> RotGridSize{};` — Optional explicitly specified rotation grid
- L262 _public member_ `TOptional<FVector> ScaleGridSize{};` — Optional explicitly specified scale grid
- L265 _public member_ `FTransform Transform = FTransform::Identity;` — Snap input transform in absolute coordinates (not delta)
- L268 _public member_ `FVector Position = FVector::ZeroVector;` — Snap input position
- L274 _public member_ `float VisualAngleThresholdDegrees = 15.0;` — When considering if one point is close enough to another point for snapping purposes, they must deviate less than this number of degrees (in visual angle) to be considered an acceptable snap position.
- L277 _public member_ `FQuat DeltaRotation = FQuat(EForceInit::ForceInitToZero);` — Snap input rotation delta
- L280 _public member_ `double RotationAngle = 0.0;` — Snap input rotation angle
- L283 _public member_ `EAxisList::Type AxisList = EAxisList::All;` — Snap input axis constraints, defaults to all (unconstrained)
- L286 _public member_ `FVector Scale = FVector::OneVector;` — Snap input scale
- L289 _public member_ `FRay WorldRay;` — Scene query ray, required by some snapping operations.
- L292 _public member_ `const TArray<const UPrimitiveComponent*>* ComponentsToIgnore = nullptr;` — Optional: components to consider invisible even if they aren't.
- L295 _public member_ `const TArray<const UPrimitiveComponent*>* InvisibleComponentsToInclude = nullptr;` — Optional: components to consider visible even if they aren't.
- L298 _public prototype_ `EToolContextCoordinateSystem GetResultCoordinateSpace() const;` — @return The ResultCoordinateSpace if set, otherwise the RequestCoordinateSpace

#### struct `FSceneSnapQueryResult`  
`struct FSceneSnapQueryResult`  
_L305-335_
- desc: Computed result of a USceneSnappingManager snap query request
- L308 _public member_ `TOptional<EToolContextCoordinateSystem> CoordinateSpace;` — (Optionally set) Coordinate space of the result data
- L311 _public member_ `AActor* TargetActor = nullptr;` — Actor that owns snap target
- L313 _public member_ `UActorComponent* TargetComponent = nullptr;` — Component that owns snap target
- L315 _public member_ `ESceneSnapQueryTargetType TargetType = ESceneSnapQueryTargetType::None;` — What kind of geometric element(s) were snapped to
- L318 _public member_ `FVector Position = FVector::ZeroVector;` — Snap position (may not be set depending on query types)
- L320 _public member_ `FVector Normal;` — Snap normal (may not be set depending on query types)
- L322 _public member_ `FQuat DeltaRotation = FQuat::Identity;` — Snap rotation delta (may not be set depending on query types)
- L324 _public member_ `double RotationAngle = 0.0;` — Snap rotation angle (may not be set depending on query types)
- L326 _public member_ `FVector Scale = FVector::ZeroVector;` — Snap scale (may not be set depending on query types)
- L329 _public member_ `FVector TriVertices[3];` — Vertices of triangle that contains result (for debugging, may not be set)
- L331 _public member_ `int TriSnapIndex;` — Vertex/Edge index we snapped to in triangle
- L334 _public prototype_ `EToolContextCoordinateSystem GetCoordinateSpace(const FSceneSnapQueryRequest& InFromRequest) const;` — @return The CoordinateSpace if set, otherwise the ResultCoordinateSpace from the provided request

#### class `USceneSnappingManager`  
`class USceneSnappingManager : public UObject`  
_L348-400_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: USceneSnappingManager is intended to be used as a base class for a Snapping implementation stored in the ContextObjectStore of an InteractiveToolsContext. ITF classes like Tools and Gizmos can then access this object and run snap queries via the various API functions. USceneSnappingManager::Find() can be used to look up a registered USceneSnappingManager, if one is available See UModelingSceneSnappingManager for a sample implementation.
- L360 _public function_ `virtual bool ExecuteSceneHitQuery(const FSceneHitQueryRequest& Request, FSceneHitQueryResult& ResultOut) const` — Try to find a Hit Object in the scene that satisfies the Hit Query @param Request hit query configuration @param Results hit query result @return true if any valid hit target was found @warning implementations are not required (and may not be able) to support hit testing
- L372 _public function_ `virtual bool ExecuteSceneHitQuery(const FSceneHitQueryRequest& Request, TArray<FSceneHitQueryResult>& ResultsOut) const` — Try to find a Hit Object in the scene that satisfies the Hit Query, returning all candidate results @param Request hit query configuration @param Results hit query results @return true if any valid hit target was found @warning implementations are not required (and may not be able) to support hit testing
- L384 _public function_ `virtual bool ExecuteSceneSnapQuery(const FSceneSnapQueryRequest& Request, TArray<FSceneSnapQueryResult>& ResultsOut) const` — Try to find Snap Targets/Results in the scene that satisfy the Snap Query. @param Request snap query configuration @param Results list of potential snap results @return true if any valid snap target/result was found @warning implementations are not required (and may not be able) to support snapping
- L394 _public prototype_ `static USceneSnappingManager* Find(UInteractiveToolManager* ToolManager);` — @return existing USceneSnappingManager registered in context store via the ToolManager, or nullptr if not found
- L399 _public prototype_ `static USceneSnappingManager* Find(UInteractiveGizmoManager* GizmoManager);` — @return existing USceneSnappingManager registered in context store via the ToolManager, or nullptr if not found

#### Free symbols / members of external scopes

- L53 _prototype_ `ENUM_CLASS_FLAGS(ESceneHitQueryTargetType);`
- L139 _prototype_ `ENUM_CLASS_FLAGS(ESceneSnapQueryTargetType);`
- L199 _function_ `inline uint32 GetTypeHash(const FSceneSnapQueryTargetHandler& InSnapQueryTargetHandler)`

### `Source/Runtime/InteractiveToolsFramework/Public/SelectionSet.h` (Public)


#### class `USelectionSet`  
`class USelectionSet : public UObject`  
_L28-50_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UObject`
- desc: USelectionSet is a base class for Selection objects. For example the UMeshSelectionSet implementation stores information on selected triangles, vertices, etc.
- L33 _protected member_ `FSelectionSetModifiedSignature OnModified;`
- L39 _public function_ `FSelectionSetModifiedSignature& GetOnModified()` — @return the multicast delegate that is called when properties are modified
- L45 _public function_ `void NotifySelectionSetModified()` — posts a message to the OnModified delegate with the modified FProperty

#### enum `EMeshSelectionElementType`  
`enum class EMeshSelectionElementType`  
_L55-61_
- L57 _public enumerator_ `Vertex = 0`
- L58 _public enumerator_ `Face = 1`
- L59 _public enumerator_ `Edge = 2`
- L60 _public enumerator_ `Group = 3`

#### class `UMeshSelectionSet`  
`class UMeshSelectionSet : public USelectionSet`  
_L70-119_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `USelectionSet`
- desc: UMeshSelectionSet is an implementation of USelectionSet that represents selections on indexed meshes. Vertices, Edges, Faces, and Groups can be selected.
- L75 _public prototype_ `UMeshSelectionSet();`
- L78 _public member_ `TArray<int32> Vertices;` — `UPROPERTY()`
- L81 _public member_ `TArray<int32> Edges;` — `UPROPERTY()`
- L84 _public member_ `TArray<int32> Faces;` — `UPROPERTY()`
- L87 _public member_ `TArray<int32> Groups;` — `UPROPERTY()`
- L92 _public prototype_ `TArray<int>& GetElements(EMeshSelectionElementType ElementType);` — @return current selected elements of the given ElementType
- L95 _public prototype_ `const TArray<int>& GetElements(EMeshSelectionElementType ElementType) const;` — @return current selected elements of the given ElementType
- L101 _public prototype_ `void AddIndices(EMeshSelectionElementType ElementType, const TArray<int32>& Indices);` — Add list of Indices to the current selection for the given ElementType @warning no duplicate detection is currently done
- L107 _public prototype_ `void AddIndices(EMeshSelectionElementType ElementType, const TSet<int32>& Indices);` — Add list of Indices to the current selection for the given ElementType @warning no duplicate detection is currently done
- L113 _public prototype_ `void RemoveIndices(EMeshSelectionElementType ElementType, const TArray<int32>& Indices);` — Remove list of Indices from the current selection for the given ElementType
- L118 _public prototype_ `void RemoveIndices(EMeshSelectionElementType ElementType, const TSet<int32>& Indices);` — Remove list of Indices from the current selection for the given ElementType

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FSelectionSetModifiedSignature, USelectionSet*);` — This delegate is used by UInteractiveToolPropertySet
- L19 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FSelectionSetModifiedSignature, USelectionSet*);` — This delegate is used by UInteractiveToolPropertySet

### `Source/Runtime/InteractiveToolsFramework/Public/SingleSelectionTool.h` (Public)


#### class `USingleSelectionTool`  
`class USingleSelectionTool : public UInteractiveTool, public IInteractiveToolCameraFocusAPI`  
_L13-61_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UInteractiveTool,IInteractiveToolCameraFocusAPI`
- L20 _public function_ `virtual void SetTarget(UToolTarget* TargetIn)` — Set the ToolTarget for the Tool
- L28 _public function_ `virtual UToolTarget* GetTarget()` — @return the ToolTarget for the Tool
- L36 _public function_ `virtual bool AreAllTargetsValid() const` — @return true if all ToolTargets of this tool are still valid
- L43 _public function_ `virtual bool CanAccept() const override`
- L50 _protected member_ `TObjectPtr<UToolTarget> Target;` — `UPROPERTY()`
- L56 _public prototype_ `virtual bool SupportsWorldSpaceFocusBox() override;` — IInteractiveToolCameraFocusAPI implementation
- L57 _public prototype_ `virtual FBox GetWorldSpaceFocusBox() override;`
- L58 _public prototype_ `virtual bool SupportsWorldSpaceFocusPoint() override;`
- L59 _public prototype_ `virtual bool GetWorldSpaceFocusPoint(const FRay& WorldRay, FVector& PointOut) override;`

### `Source/Runtime/InteractiveToolsFramework/Public/TargetInterfaces/AssetBackedTarget.h` (Public)


#### class `UAssetBackedTarget`  
`class UAssetBackedTarget : public UInterface`  
_L13-16_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IAssetBackedTarget`  
`class IAssetBackedTarget`  
_L18-33_
- L26 _public prototype_ `virtual UObject* GetSourceData() const = 0;` — @return the underlying source asset for this Target.
- L28 _public function_ `virtual bool HasSameSourceData(UToolTarget* OtherTarget) const`

### `Source/Runtime/InteractiveToolsFramework/Public/TargetInterfaces/MaterialProvider.h` (Public)


#### struct `FComponentMaterialSet`  
`struct FComponentMaterialSet`  
_L15-23_
- desc: FComponentMaterialSet is the set of materials assigned to a component (ie Material Slots on a StaticMesh)
- L17 _public member_ `TArray<UMaterialInterface*> Materials;`
- L19 _public function_ `bool operator!=(const FComponentMaterialSet& Other) const`

#### class `UMaterialProvider`  
`class UMaterialProvider : public UInterface`  
_L26-29_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IMaterialProvider`  
`class IMaterialProvider`  
_L31-71_
- L38 _public prototype_ `virtual int32 GetNumMaterials() const = 0;` — @return number of material indices in use by this Component
- L45 _public prototype_ `virtual UMaterialInterface* GetMaterial(int32 MaterialIndex) const = 0;` — Get pointer to a Material provided by this Source @param MaterialIndex index of the material @return MaterialInterface pointer, or null if MaterialIndex is invalid
- L53 _public prototype_ `virtual void GetMaterialSet(FComponentMaterialSet& MaterialSetOut, bool bPreferAssetMaterials = false) const = 0;` — Get material set provided by this source @param MaterialSetOut returned material set @param bAssetMaterials Prefer the underlying asset materials. This may be ignored by targets to which this is not relevant.
- L70 _public prototype_ `virtual bool CommitMaterialSetUpdate(const FComponentMaterialSet& MaterialSet, bool bApplyToAsset) = 0;` — Commit an update to the material set. This may generate a transaction. Note that a target may not allow applying the material to an underlying asset, or may not even allow having the material applied to the instance, in which case the function will return false without doing anything. TODO: We may decide that we want some functions to query whether the object allows one or the other, or we may break this out into a separate interface. We'll wait to see when this actually becomes necessary to see the most convenient way to go at that point. @param MaterialSet new list of materials @return true if successful

### `Source/Runtime/InteractiveToolsFramework/Public/TargetInterfaces/MeshDescriptionCommitter.h` (Public)


#### class `UMeshDescriptionCommitter`  
`class UMeshDescriptionCommitter : public UInterface`  
_L14-17_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IMeshDescriptionCommitter`  
`class IMeshDescriptionCommitter`  
_L19-93_
- L28 _public function_ `virtual bool CommitMeshDescription(const FMeshDescription& Mesh, const FCommitMeshParameters& CommitParams = FCommitMeshParameters() )` — Commits the given FMeshDescription.
- L48 _public function_ `virtual bool CommitMeshDescription(FMeshDescription&& Mesh, const FCommitMeshParameters& CommitParams = FCommitMeshParameters())` — Commits the given FMeshDescription.
- L67 _public function_ `virtual TArray<int32> GetPolygonGroupToMaterialIndexMap() const` — @return a mapping from material ID to polygon group ID. If empty, an identity mapping is assumed.
- L82 _protected typedef_ `using FCommitter = TFunction<void(const FCommitterParams&)>;`
- L91 _protected prototype_ `virtual void CommitMeshDescription(const FCommitter& Committer, const FCommitMeshParameters& CommitParams = FCommitMeshParameters()) = 0;` — Commit a mesh description. The mesh description to be committed will be passed to the given function as a parameter, and it is up to the function to update it properly. @param Committer A function that takes in const IMeshDescriptionCommitter::FCommitParams& and populates the FMeshDescription pointed to by the MeshDescription pointer inside.

#### struct `IMeshDescriptionCommitter::FCommitterParams`  
`struct FCommitterParams`  
_L74-81_
- L80 _public member_ `FMeshDescription* MeshDescriptionOut = nullptr;` — Mesh description that should be populated/updated by the passed-in function and which will be committed to the target.

#### Free symbols / members of external scopes

- L34 _function_ `` (scope `IMeshDescriptionCommitter::CommitMeshDescription`)

### `Source/Runtime/InteractiveToolsFramework/Public/TargetInterfaces/MeshDescriptionProvider.h` (Public)


#### class `UMeshDescriptionProvider`  
`class UMeshDescriptionProvider : public UInterface`  
_L13-16_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IMeshDescriptionProvider`  
`class IMeshDescriptionProvider`  
_L18-84_
- L28 _public prototype_ `virtual const FMeshDescription* GetMeshDescription(const FGetMeshParameters& GetMeshParams = FGetMeshParameters()) = 0;` — Access the MeshDescription available through this Provider. Note that this MeshDescription may or may not be owned by the provider and should not be modified directly. Use IMeshDescriptionCommitter for writes. @return pointer to MeshDescription
- L39 _public prototype_ `virtual FMeshDescription GetEmptyMeshDescription() = 0;` — Returns an empty mesh description appropriate for the provider, i.e. configured with appropriate mesh attributes but otherwise devoid of topology or element data. Note: Some of our code expects at least FStaticMeshAttributes to be registered with the provided mesh description, and will break if some of the attributes that FStaticMeshAttributes uses are not present. The only reason we don't provide a default implementation here that is identical to the one used in StaticMeshToolTarget.cpp is to avoid a dependency on the static mesh description module in ITF.
- L44 _public function_ `virtual FMeshDescription GetMeshDescriptionCopy(const FGetMeshParameters& GetMeshParams)` — Get a copy of the MeshDescription available through this Provider.
- L53 _public function_ `virtual TArray<EMeshLODIdentifier> GetAvailableLODs(bool bSkipAutoGenerated = true) const` — For providers that have LODs (i.e. if SupportsLODs returns true), returns an array of all available LODs. Otherwise, returns an array with just the Default LOD. @param bSkipAutoGenerated	Skip auto-generated LODs, which have no associated source Mesh Description
- L63 _public function_ `virtual EMeshLODIdentifier GetMeshDescriptionLOD() const` — For providers that have LODs (i.e. if SupportsLODs returns true), returns the LOD that GetMeshDescription/etc will return. Otherwise, returns Default LOD.
- L71 _public function_ `virtual bool SupportsLODs() const` — @return true if the provider is able to provide different Mesh Descriptions for different requested LODs.  If so, GetAvailableLODs() will return the available LODs.
- L79 _public function_ `virtual TArray<int32> GetPolygonGroupToMaterialIndexMap() const` — @return a mapping from section ID to material ID. If empty, an identity mapping is assumed.

### `Source/Runtime/InteractiveToolsFramework/Public/TargetInterfaces/MeshTargetInterfaceTypes.h` (Public)


#### enum `EMeshLODIdentifier`  
`enum class EMeshLODIdentifier`  
_L10-25_
- desc: EMeshLODIdentifier is used to identify the LOD of a mesh for reading/writing.
- L12 _public enumerator_ `LOD0 = 0`
- L13 _public enumerator_ `LOD1 = 1`
- L14 _public enumerator_ `LOD2 = 2`
- L15 _public enumerator_ `LOD3 = 3`
- L16 _public enumerator_ `LOD4 = 4`
- L17 _public enumerator_ `LOD5 = 5`
- L18 _public enumerator_ `LOD6 = 6`
- L19 _public enumerator_ `LOD7 = 7`
- L21 _public enumerator_ `HiResSource = 100` — HiRes source mesh is optional, and will fall back to LOD0 if not available
- L23 _public enumerator_ `Default = 1000` — use whatever is the "standard" LOD - generally LOD0
- L24 _public enumerator_ `MaxQuality = 1001` — use HiRes source mesh if available, or LOD0 otherwise

#### struct `FGetMeshParameters`  
`struct FGetMeshParameters`  
_L32-49_
- desc: FGetMeshParameters is used by ToolTarget Interfaces/Implementations that support returning a mesh, to allow clients to specify various options like a specific LOD of a mesh, which attributes are required, etc.
- L34 _public prototype_ `FGetMeshParameters() = default;`
- L35 _public function_ `explicit FGetMeshParameters(bool bHaveRequestLOD, EMeshLODIdentifier RequestLOD) : bHaveRequestLOD(bHaveRequestLOD), RequestLOD(RequestLOD)`
- L40 _public member_ `bool bHaveRequestLOD = false;` — If true, RequestLOD specifies which mesh LOD should be returned, if available. If not available, behavior is implementation-dependent.
- L42 _public member_ `EMeshLODIdentifier RequestLOD = EMeshLODIdentifier::Default;` — Specify which LOD to fetch from a mesh-containing ToolTarget. Ignored unless bHaveRequestLOD == true.
- L48 _public member_ `bool bWantMeshTangents = false;` — If true, returned Mesh should have Tangents available. In some cases (eg StaticMesh) this may require that the ToolTarget implementation computes the Tangents, which may only be possible on a copy of the mesh

#### struct `FCommitMeshParameters`  
`struct FCommitMeshParameters`  
_L56-67_
- desc: FCommitMeshParameters is used by ToolTarget Interfaces/Implementations that support setting a mesh (eg on a StaticMesh Asset), to allow the client to specify various options
- L58 _public prototype_ `FCommitMeshParameters() = default;`
- L59 _public function_ `explicit FCommitMeshParameters(bool bHaveTargetLOD, EMeshLODIdentifier TargetLOD) : bHaveTargetLOD(bHaveTargetLOD), TargetLOD(TargetLOD)`
- L64 _public member_ `bool bHaveTargetLOD = false;` — If true, TargetLOD specifies which mesh LOD should be set/updated
- L66 _public member_ `EMeshLODIdentifier TargetLOD = EMeshLODIdentifier::Default;` — Specify which LOD to set in a mesh-containing ToolTarget. Ignored unless bHaveTargetLOD == true.

#### Free symbols / members of external scopes

- L26 _typedef_ `typedef EMeshLODIdentifier EStaticMeshEditingLOD;`

### `Source/Runtime/InteractiveToolsFramework/Public/TargetInterfaces/PhysicsDataSource.h` (Public)


#### class `UPhysicsDataSource`  
`class UPhysicsDataSource : public UInterface`  
_L14-17_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IPhysicsDataSource`  
`class IPhysicsDataSource`  
_L22-39_
- desc: IPhysicsDataSource is a ToolTarget Interface that provides read/write access to physics-related data structures.
- L31 _public prototype_ `virtual UBodySetup* GetBodySetup() const = 0;` — @return The UBodySetup for this physics data source. If Nullptr, no physics data exists or is available.
- L37 _public prototype_ `virtual IInterface_CollisionDataProvider* GetComplexCollisionProvider() const = 0;` — @return The CollisionDataProvider for this physics data source. If Nullptr, no physics data exists or is available.

### `Source/Runtime/InteractiveToolsFramework/Public/TargetInterfaces/PrimitiveComponentBackedTarget.h` (Public)


#### class `UPrimitiveComponentBackedTarget`  
`class UPrimitiveComponentBackedTarget : public USceneComponentBackedTarget`  
_L19-22_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `USceneComponentBackedTarget`

#### class `IPrimitiveComponentBackedTarget`  
`class IPrimitiveComponentBackedTarget : public ISceneComponentBackedTarget`  
_L24-40_
- inherits: `ISceneComponentBackedTarget`
- L31 _public prototype_ `virtual UPrimitiveComponent* GetOwnerComponent() const = 0;` — @return the Component this is a Source for
- L39 _public prototype_ `virtual bool HitTestComponent(const FRay& WorldRay, FHitResult& OutHit) const = 0;` — Compute ray intersection with geometry this Source is providing (if any) @param WorldRay ray in world space @param OutHit hit test data @return true if ray intersected Component

### `Source/Runtime/InteractiveToolsFramework/Public/TargetInterfaces/SceneComponentBackedTarget.h` (Public)


#### class `USceneComponentBackedTarget`  
`class USceneComponentBackedTarget : public UInterface`  
_L16-19_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `ISceneComponentBackedTarget`  
`class ISceneComponentBackedTarget`  
_L21-44_
- L28 _public prototype_ `virtual USceneComponent* GetOwnerSceneComponent() const = 0;` — @return the ActorComponent this is a Source for
- L31 _public prototype_ `virtual AActor* GetOwnerActor() const = 0;` — @return the Actor that owns this Component
- L37 _public prototype_ `virtual void SetOwnerVisibility(bool bVisible) const = 0;` — Set the visibility of the Component associated with this Source (ie to hide during Tool usage) @param bVisible desired visibility
- L43 _public prototype_ `virtual FTransform GetWorldTransform() const = 0;` — @return the transform on this component @todo Do we need to return a list of transforms here?

### `Source/Runtime/InteractiveToolsFramework/Public/TargetInterfaces/SkeletalMeshBackedTarget.h` (Public)


#### class `USkeletalMeshBackedTarget`  
`class USkeletalMeshBackedTarget : public UAssetBackedTarget`  
_L13-16_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UAssetBackedTarget`

#### class `ISkeletalMeshBackedTarget`  
`class ISkeletalMeshBackedTarget : public IAssetBackedTarget`  
_L18-35_
- inherits: `IAssetBackedTarget`
- L26 _public function_ `virtual UObject* GetSourceData() const override` — @return the underlying source asset for this Target.
- L34 _public prototype_ `virtual USkeletalMesh* GetSkeletalMesh() const = 0;` — @return the underlying source USkeletalMesh asset for this Target

### `Source/Runtime/InteractiveToolsFramework/Public/TargetInterfaces/StaticMeshBackedTarget.h` (Public)


#### class `UStaticMeshBackedTarget`  
`class UStaticMeshBackedTarget : public UAssetBackedTarget`  
_L14-17_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UAssetBackedTarget`

#### class `IStaticMeshBackedTarget`  
`class IStaticMeshBackedTarget : public IAssetBackedTarget`  
_L19-36_
- inherits: `IAssetBackedTarget`
- L27 _public function_ `virtual UObject* GetSourceData() const override` — @return the underlying source asset for this Target.
- L35 _public prototype_ `virtual UStaticMesh* GetStaticMesh() const = 0;` — @return the underlying source StaticMesh asset for this Target

### `Source/Runtime/InteractiveToolsFramework/Public/ToolBuilderUtil.h` (Public)


#### Free symbols / members of external scopes

- L15 _namespace_ `namespace ToolBuilderUtil`
- L19 _prototype_ `int CountComponents(const FToolBuilderState& InputState, const TFunction<bool(UActorComponent*)>& Predicate);` (scope `ToolBuilderUtil`)
- L23 _prototype_ `UActorComponent* FindFirstComponent(const FToolBuilderState& InputState, const TFunction<bool(UActorComponent*)>& Predicate);` (scope `ToolBuilderUtil`)
- L27 _prototype_ `TArray<UActorComponent*> FindAllComponents(const FToolBuilderState& InputState, const TFunction<bool(UActorComponent*)>& Predicate);` (scope `ToolBuilderUtil`)
- L32 _prototype_ `template<typename ComponentType> int CountSelectedComponentsOfType(const FToolBuilderState& InputState);` (scope `ToolBuilderUtil`) — Count number of components of given type. If Component selection is not empty, returns that count, otherwise counts in all selected Actors
- L36 _prototype_ `template<typename ComponentType> ComponentType* FindFirstComponentOfType(const FToolBuilderState& InputState);` (scope `ToolBuilderUtil`) — First first available component of given type. Searches Components selection list first, then all Actors
- L39 _prototype_ `void EnumerateComponents(const FToolBuilderState& InputState, TFunctionRef<void(UActorComponent*)> ComponentFunc);` (scope `ToolBuilderUtil`)
- L43 _prototype_ `int32 CountActors(const FToolBuilderState& InputState, const TFunction<bool(AActor*)>& Predicate);` (scope `ToolBuilderUtil`)
- L47 _prototype_ `AActor* FindFirstActor(const FToolBuilderState& InputState, const TFunction<bool(AActor*)>& Predicate);` (scope `ToolBuilderUtil`)
- L51 _prototype_ `TArray<AActor*> FindAllActors(const FToolBuilderState& InputState, const TFunction<bool(AActor*)>& Predicate);` (scope `ToolBuilderUtil`)
- L55 _prototype_ `template<typename ActorType> int CountSelectedActorsOfType(const FToolBuilderState& InputState);` (scope `ToolBuilderUtil`) — Count number of selected Actors of given type.
- L59 _prototype_ `template<typename ActorType> ActorType* FindFirstActorOfType(const FToolBuilderState& InputState);` (scope `ToolBuilderUtil`) — Find first first available Actor of given type, or return nullptr if not found
- L63 _prototype_ `bool ComponentTypeCouldHaveUVs(const UActorComponent& Component);` (scope `ToolBuilderUtil`)
- L67 _prototype_ `bool IsVolume(const UActorComponent& Component);` (scope `ToolBuilderUtil`)
- L74 _function_ `template<typename ComponentType> int ToolBuilderUtil::CountSelectedComponentsOfType(const FToolBuilderState& InputState)` (scope `ToolBuilderUtil`) — Template Implementations
- L76 _function_ `return CountComponents(InputState, [](UActorComponent* Component) { return Cast<ComponentType>(Component) != nullptr; });` (scope `ToolBuilderUtil::CountSelectedComponentsOfType`)
- L80 _function_ `template<typename ComponentType> ComponentType* ToolBuilderUtil::FindFirstComponentOfType(const FToolBuilderState& InputState)` (scope `ToolBuilderUtil`)
- L82 _function_ `return static_cast<ComponentType*>(FindFirstComponent(InputState, [](UActorComponent* Component) { return Cast<ComponentType>(Component) != nullptr; }));` (scope `ToolBuilderUtil::FindFirstComponentOfType`)
- L86 _function_ `template<typename ActorType> int ToolBuilderUtil::CountSelectedActorsOfType(const FToolBuilderState& InputState)` (scope `ToolBuilderUtil`)
- L88 _function_ `return CountActors(InputState, [](AActor* Actor) { return Cast<ActorType>(Actor) != nullptr; });` (scope `ToolBuilderUtil::CountSelectedActorsOfType`)
- L92 _function_ `template<typename ActorType> ActorType* ToolBuilderUtil::FindFirstActorOfType(const FToolBuilderState& InputState)` (scope `ToolBuilderUtil`)
- L94 _function_ `AActor* Found = FindFirstActor(InputState, [](AActor* Actor) { return Cast<ActorType>(Actor) != nullptr; });` (scope `ToolBuilderUtil::FindFirstActorOfType`)

### `Source/Runtime/InteractiveToolsFramework/Public/ToolContextInterfaces.h` (Public)


#### struct `FToolBuilderState`  
`struct FToolBuilderState`  
_L49-75_
- desc: FToolBuilderState is a bucket of state information that a ToolBuilder might need to construct a Tool. This information comes from a level above the Tools framework, and depends on the context we are in (Editor vs Runtime, for example).
- L52 _public member_ `UWorld* World = nullptr;` — The current UWorld
- L54 _public member_ `UInteractiveToolManager* ToolManager = nullptr;` — The current ToolManager
- L56 _public member_ `UToolTargetManager* TargetManager = nullptr;` — The current TargetManager
- L58 _public member_ `UInteractiveGizmoManager* GizmoManager = nullptr;` — The current GizmoManager
- L61 _public member_ `TArray<AActor*> SelectedActors;` — Current selected Actors. May be empty or nullptr.
- L63 _public member_ `TArray<UActorComponent*> SelectedComponents;` — Current selected Components. May be empty or nullptr.
- L66 _public member_ `TWeakObjectPtr<UTypedElementSelectionSet> TypedElementSelectionSet;` — `UE_DEPRECATED(5.1, "This has moved to a context object. See IAssetEditorContextInterface")`
- L69 _public prototype_ `FToolBuilderState() = default;`
- L70 _public prototype_ `FToolBuilderState(FToolBuilderState&&) = default;`
- L71 _public prototype_ `FToolBuilderState(const FToolBuilderState&) = default;`
- L72 _public prototype_ `FToolBuilderState& operator=(FToolBuilderState&&) = default;`
- L73 _public prototype_ `FToolBuilderState& operator=(const FToolBuilderState&) = default;`

#### struct `FViewCameraState`  
`struct FViewCameraState`  
_L82-114_
- desc: FViewCameraState is a bucket of state information that a Tool might need to implement interactions that depend on the current scene view.
- L85 _public member_ `FVector Position = FVector(EForceInit::ForceInit);` — Current camera/head position
- L87 _public member_ `FQuat Orientation = FQuat(EForceInit::ForceInit);` — Current camera/head orientation
- L89 _public member_ `float HorizontalFOVDegrees = 90;` — Current Horizontal Field of View Angle in Degrees. Only relevant if bIsOrthographic is false.
- L91 _public member_ `float OrthoWorldCoordinateWidth = 100;` — Current width of viewport in world space coordinates. Only valid if bIsOrthographic is true.
- L93 _public member_ `float AspectRatio = 1;` — Current Aspect Ratio
- L95 _public member_ `bool bIsOrthographic = false;` — Is current view an orthographic view
- L97 _public member_ `bool bIsVR = false;` — Is current view a VR view
- L99 _public member_ `double DPIScale = 1.0;` — DPI scale
- L102 _public function_ `FVector Right() const` — @return "right"/horizontal direction in camera plane
- L104 _public function_ `FVector Up() const` — @return "up"/vertical direction in camera plane
- L106 _public function_ `FVector Forward() const` — @return forward camera direction
- L109 _public function_ `float GetPDIScalingFactor() const` — @return scaling factor that should be applied to PDI thickness/size
- L112 _public function_ `float GetFOVAngleNormalizationFactor() const` — @return FOV normalization factor that should be applied when comparing angles

#### enum `EStandardToolContextMaterials`  
`enum class EStandardToolContextMaterials`  
_L120-124_
- reflection: `UENUM()`
- desc: Types of standard materials that Tools may request from Context
- L123 _public enumerator_ `VertexColorMaterial = 1` — White material that displays vertex colors set on mesh

#### enum `EToolContextCoordinateSystem`  
`enum class EToolContextCoordinateSystem : uint8`  
_L129-137_
- reflection: `UENUM()`
- desc: Types of coordinate systems that a Tool/Gizmo might use
- L132 _public enumerator_ `World = 0` — World space coordinate system
- L134 _public enumerator_ `Local = 1` — Local coordinate system
- L136 _public enumerator_ `Screen = 2` — Screen space coordinate system

#### enum `EToolContextTransformGizmoMode`  
`enum class EToolContextTransformGizmoMode : uint8`  
_L146-158_
- reflection: `UENUM()`
- desc: High-level configuration options for a standard 3D translate/rotate/scale Gizmo, like is commonly used in 3D DCC tools, game editors, etc This is meant to be used to convey UI-level settings to Tools/Gizmos, eg like the W/E/R toggles for Rranslate/Rotate/Scale in Maya or UE Editor. More granular control over precise gizmo elements is available through other mechanisms, eg the ETransformGizmoSubElements flags in UCombinedTransformGizmo
- L149 _public enumerator_ `NoGizmo = 0` — Hide all Gizmo sub-elements
- L151 _public enumerator_ `Translation = 1` — Only Show Translation sub-elements
- L153 _public enumerator_ `Rotation = 2` — Only Show Rotation sub-elements
- L155 _public enumerator_ `Scale = 3` — Only Show Scale sub-elements
- L157 _public enumerator_ `Combined = 8` — Show all available Gizmo sub-elements

#### struct `FToolContextSnappingConfiguration`  
`struct FToolContextSnappingConfiguration`  
_L165-217_
- desc: Snapping configuration settings/state
- L168 _public member_ `bool bIsSnappingActive = true;` — Whether to perform any kind of snapping
- L171 _public member_ `bool bEnablePositionGridSnapping = false;` — Specify whether position snapping should be applied
- L173 _public member_ `FVector PositionGridDimensions = FVector::Zero();` — Specify position grid spacing or cell dimensions
- L178 _public function_ `bool IsPositionGridSnappingActive() const` — @return true if position grid snapping is active (snapping enabled AND position grid snapping enabled)
- L181 _public member_ `bool bEnableRotationGridSnapping = false;` — Specify whether rotation snapping should be applied
- L183 _public member_ `FRotator RotationGridAngles = FRotator::ZeroRotator;` — Specify rotation snapping step size
- L188 _public function_ `bool IsRotationGridSnappingActive() const` — @return true if rotation grid/angular snapping is active (snapping enabled AND rotation grid snapping enabled)
- L191 _public member_ `bool bEnableScaleGridSnapping = false;` — Specify whether scale snapping should be applied
- L193 _public member_ `float ScaleGridSize = 1.0f;` — Specify scale factor
- L198 _public function_ `bool IsScaleGridSnappingActive() const` — @return true if scale grid snapping is active (snapping enabled AND scale grid snapping enabled)
- L201 _public member_ `bool bEnableAbsoluteWorldSnapping = false;` — Specify whether Position snapping in World Coordinate System should be Absolute or Relative
- L211 _public member_ `} ObjectTransform;`
- L216 _public function_ `bool IsObjectTransformSnappingActive() const` — @return true if object transform snapping is active (snapping enabled AND object transform snapping enabled)

#### struct `FToolContextSnappingConfiguration::FObjectTransformSnapping`  
`struct FObjectTransformSnapping`  
_L204-211_
- desc: Stores parameters applicable to actor/object transform snapping, corresponds with ESceneSnapQueryTargetType::ObjectTransform
- L207 _public member_ `bool bEnable = false;` — Specify whether this snapping type is enabled
- L210 _public member_ `float SnapDistance = 0.0f;` — The distance/radius around a candidate transform to automatically snap to. 0.0 requires precise placement.

#### class `UToolsContextCursorAPI`  
`class UToolsContextCursorAPI : public UObject`  
_L225-293_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Users of the Tools Framework can use  UToolsContextCursorAPI to access to setting and retrieving cursor overrides for tool activities.
- L230 _private member_ `EMouseCursor::Type CursorOverrideShape;`
- L231 _private member_ `TSharedPtr<SWidget> CursorOverrideWidget;`
- L232 _private member_ `bool bIsCursorOverridden;`
- L234 _private member_ `TOptional<bool> UseSoftwareCursorOverride;`
- L238 _public function_ `UToolsContextCursorAPI()`
- L245 _public prototype_ `virtual ~UToolsContextCursorAPI() override = default;`
- L247 _public function_ `virtual EMouseCursor::Type GetCurrentCursorOverride() const`
- L252 _public function_ `virtual TSharedPtr<SWidget> GetCurrentCursorOverrideWidget() const`
- L257 _public function_ `virtual bool IsCursorOverridden() const`
- L262 _public function_ `virtual void SetCursorOverride(EMouseCursor::Type CursorOverride)`
- L268 _public function_ `virtual void SetCursorOverrideWidget(const TSharedRef<SWidget>& InCursorOverrideWidget)`
- L275 _public function_ `void SetUseSoftwareCursor(const TOptional<bool>& InUseSoftwareCursorOverride)`
- L280 _public function_ `TOptional<bool> GetUseSoftwareCursorOverride() const`
- L286 _public function_ `virtual void ClearCursorOverride()` — Clears the custom widget, if any, resets the shape to Default and resets the overridden flag.

#### class `IToolsContextQueriesAPI`  
`class IToolsContextQueriesAPI`  
_L299-352_
- desc: Users of the Tools Framework need to implement IToolsContextQueriesAPI to provide access to scene state information like the current UWorld, active USelections, etc.
- L302 _public prototype_ `virtual ~IToolsContextQueriesAPI() = default;`
- L307 _public prototype_ `virtual UWorld* GetCurrentEditingWorld() const = 0;` — @return the UWorld currently being targetted by the ToolsContext, default location for new Actors/etc
- L313 _public prototype_ `virtual void GetCurrentSelectionState(FToolBuilderState& StateOut) const = 0;` — Collect up current-selection information for the current scene state (ie what is selected in Editor, etc) @param StateOut this structure is populated with available state information
- L319 _public prototype_ `virtual void GetCurrentViewState(FViewCameraState& StateOut) const = 0;` — Request information about current view state @param StateOut this structure is populated with available state information
- L324 _public function_ `virtual EToolContextCoordinateSystem GetCurrentCoordinateSystem() const` — Request current external coordinate-system setting. Defaults to World coordinates.
- L329 _public function_ `virtual EToolContextTransformGizmoMode GetCurrentTransformGizmoMode() const` — Request current external Gizmo Mode setting. Defaulting this to Combined gizmo as this was the default behavior before UE-5.2.
- L334 _public function_ `virtual FToolContextSnappingConfiguration GetCurrentSnappingSettings() const` — Request current external snapping settings. Defaults to no snapping.
- L341 _public prototype_ `virtual UMaterialInterface* GetStandardMaterial(EStandardToolContextMaterials MaterialType) const = 0;` — Many tools need standard types of materials that the user should provide (eg a vertex-color material, etc) @param MaterialType the type of material being requested @return Instance of material to use for this purpose
- L346 _public prototype_ `virtual FViewport* GetHoveredViewport() const = 0;` — @returns the last valid viewport that was hovered, or nullptr.
- L351 _public prototype_ `virtual FViewport* GetFocusedViewport() const = 0;` — @returns the last valid viewport that received some input, or nullptr.

#### enum `EToolMessageLevel`  
`enum class EToolMessageLevel`  
_L359-371_
- reflection: `UENUM()`
- desc: Level of severity of messages emitted by Tool framework
- L362 _public enumerator_ `Internal = 0` — Development message goes into development log
- L364 _public enumerator_ `UserMessage = 1` — User message should appear in user-facing log
- L366 _public enumerator_ `UserNotification = 2` — Notification message should be shown in a non-modal notification window
- L368 _public enumerator_ `UserWarning = 3` — Warning message should be shown in a non-modal notification window with panache
- L370 _public enumerator_ `UserError = 4` — Error message should be shown in a modal notification window

#### enum `ESelectedObjectsModificationType`  
`enum class ESelectedObjectsModificationType`  
_L376-382_
- reflection: `UENUM()`
- desc: Type of change we want to apply to a selection
- L378 _public enumerator_ `Replace = 0`
- L379 _public enumerator_ `Add = 1`
- L380 _public enumerator_ `Remove = 2`
- L381 _public enumerator_ `Clear = 3`

#### struct `FSelectedObjectsChangeList`  
`struct FSelectedObjectsChangeList`  
_L386-394_
- desc: Represents a change to a set of selected Actors and Components
- L389 _public member_ `ESelectedObjectsModificationType ModificationType;` — How should this list be interpreted in the context of a larger selection set
- L391 _public member_ `TArray<AActor*> Actors;` — List of Actors
- L393 _public member_ `TArray<UActorComponent*> Components;` — List of Componets

#### class `IToolsContextTransactionsAPI`  
`class IToolsContextTransactionsAPI`  
_L405-461_
- desc: Users of the Tools Framework need to implement IToolsContextTransactionsAPI so that the Tools have the ability to create Transactions and emit Changes. Note that this is technically optional, but that undo/redo won't be supported without it.
- L408 _public prototype_ `virtual ~IToolsContextTransactionsAPI() = default;`
- L415 _public prototype_ `virtual void DisplayMessage(const FText& Message, EToolMessageLevel Level) = 0;` — Request that context display message information. @param Message text of message @param Level severity level of message
- L423 _public prototype_ `virtual void PostInvalidation() = 0;` — Forward an invalidation request from Tools framework, to cause repaint/etc. This is not always necessary but in some situations (eg in Non-Realtime mode in Editor) a redraw will not happen every frame. See UInputRouter for options to enable auto-invalidation.
- L430 _public prototype_ `virtual void BeginUndoTransaction(const FText& Description) = 0;` — Begin a Transaction, whatever this means in the current Context. For example in the Editor it means open a GEditor Transaction. You must call EndUndoTransaction() after calling this. @param Description text description of the transaction that could be shown to user
- L435 _public prototype_ `virtual void EndUndoTransaction() = 0;` — Complete the Transaction. Assumption is that Begin/End are called in pairs.
- L440 _public prototype_ `virtual void CancelUndoTransaction() = 0;` — Cancel and revert a started Transaction.
- L450 _public prototype_ `virtual void AppendChange(UObject* TargetObject, TUniquePtr<FToolCommandChange> Change, const FText& Description) = 0;` — Insert an FChange into the transaction history in the current Context. It is safe but not necessary to call this between Begin/EndUndoTransaction; the FChange will be automatically inserted into a Transaction. @param TargetObject The UObject this Change is applied to @param Change The Change implementation @param Description text description of the transaction that could be shown to user
- L459 _public prototype_ `virtual bool RequestSelectionChange(const FSelectedObjectsChangeList& SelectionChange) = 0;` — Request a modification to the current selected objects @param SelectionChange desired modification to current selection @return true if the selection change could be applied

#### enum `EViewInteractionState`  
`enum class EViewInteractionState`  
_L464-470_
- reflection: `UENUM()`
- L465 _public enumerator_ `None = 0`
- L466 _public enumerator_ `Hovered = 1`
- L467 _public enumerator_ `Focused = 2`
- L469 _public enumerator_ `All = Hovered | Focused`

#### class `IToolsContextRenderAPI`  
`class IToolsContextRenderAPI`  
_L479-495_
- desc: Users of the Tools Framework need to implement IToolsContextRenderAPI to allow Tools, Indicators, and Gizmos to make low-level rendering calls for things like line drawing. This API will be passed to eg UInteractiveTool::Render(), so access is only provided when it makes sense to call the functions
- L482 _public prototype_ `virtual ~IToolsContextRenderAPI() = default;`
- L485 _public prototype_ `virtual FPrimitiveDrawInterface* GetPrimitiveDrawInterface() = 0;` — @return Current PDI
- L488 _public prototype_ `virtual const FSceneView* GetSceneView() = 0;` — @return Current FSceneView
- L491 _public prototype_ `virtual FViewCameraState GetCameraState() = 0;` — @return Current Camera State for this Render API
- L494 _public prototype_ `virtual EViewInteractionState GetViewInteractionState() = 0;` — @return Current interaction state of the view to render

#### Free symbols / members of external scopes

- L397 _typedef_ `typedef FSelectedObjectsChangeList FSelectedOjectsChangeList;` — `UE_DEPRECATED(5.4, "Use FSelectedObjectsChangeList instead")`
- L471 _prototype_ `ENUM_CLASS_FLAGS(EViewInteractionState);`

### `Source/Runtime/InteractiveToolsFramework/Public/ToolDataVisualizer.h` (Public)


#### class `FToolDataVisualizer`  
`class FToolDataVisualizer`  
_L18-343_
- desc: FToolDataVisualizer is a utility class for Tool and Gizmo implementations to use to draw 3D lines, points, etc. Currently uses PDI drawing but may use different back-ends in the future
- L22 _public member_ `FLinearColor LineColor;` — Default color used for drawing lines
- L24 _public member_ `float LineThickness = 1.0f;` — Default thickness used for drawing lines
- L26 _public member_ `float ArrowHeadSize = 4.0f;` — Default size used for drawing arrow heads
- L29 _public member_ `FLinearColor PointColor;` — Default color used for drawing points
- L31 _public member_ `float PointSize = 1.0f;` — Default size used for drawing points
- L34 _public member_ `float DepthBias = 0.0f;` — Depth bias applied to lines
- L36 _public member_ `bool bDepthTested = true;` — Should lines be clipped by 3D geometry, or should they be drawn with quasi-transparency
- L39 _public prototype_ `FToolDataVisualizer();`
- L40 _public prototype_ `FToolDataVisualizer(const FToolDataVisualizer&);`
- L41 _public prototype_ `virtual ~FToolDataVisualizer();`
- L50 _public prototype_ `void BeginFrame(IToolsContextRenderAPI* RenderAPI, const FViewCameraState& CameraState);` — This must be called every frame to allow Visualizer to extract necessary rendering data/objects
- L53 _public prototype_ `void BeginFrame(IToolsContextRenderAPI* RenderAPI);` — This must be called every frame to allow Visualizer to extract necessary rendering data/objects
- L56 _public prototype_ `void EndFrame();` — this should be called at the end of every frame to allow for necessary cleanup
- L64 _public prototype_ `void SetTransform(const FTransform& Transform);` — Clear transform stack and push the given Transform
- L66 _public prototype_ `void PushTransform(const FTransform& Transform);` — Push a Transform onto the transform stack
- L68 _public prototype_ `void PopTransform();` — Pop a transform from the transform stack
- L70 _public prototype_ `void PopAllTransforms();` — Clear the transform stack to identity
- L73 _public function_ `FVector TransformP(const FVector& Point)` — @return input Point transformed by transform stack
- L79 _public function_ `FVector TransformV(const FVector& Vector)` — @return input Vector transformed by transform stack
- L85 _public function_ `FVector TransformN(const FVector& Normal)` — @return input Normal transformed by transform stack
- L101 _public function_ `void SetLineParameters(const FLinearColor& Color, float Thickness, float InArrowHeadSize = 4.0f)` — Update the default line color and thickness
- L109 _public function_ `void SetPointParameters(const FLinearColor& Color, float Size)` — Update the default point color and size
- L123 _public function_ `template<typename PointType> void DrawLine(const PointType& A, const PointType& B)` — Draw a line with default parameters
- L130 _public function_ `template<typename PointType> void DrawLine(const PointType& A, const PointType& B, const FLinearColor& Color)` — Draw a line with the given Color, otherwise use default parameters
- L137 _public function_ `template<typename PointType> void DrawLine(const PointType& A, const PointType& B, const FLinearColor& Color, float LineThicknessIn)` — Draw a line with the given Color and Thickness, otherwise use default parameters
- L144 _public function_ `template<typename PointType> void DrawLine(const PointType& A, const PointType& B, const FLinearColor& Color, float LineThicknessIn, bool bDepthTestedIn)` — Draw a line with the given parameters
- L151 _public function_ `template<typename PointType> void DrawDirectionalArrow(const PointType& A, const PointType& B, const FVector& InNormal)` — Draw an arrow with default parameters
- L158 _public function_ `template<typename PointType> void DrawDirectionalArrow(const PointType& A, const PointType& B, const FVector& InNormal, const FLinearColor& Color)` — Draw a line with the given Color, otherwise use default parameters
- L165 _public function_ `template<typename PointType> void DrawDirectionalArrow(const PointType& A, const PointType& B, const FVector& InNormal, const FLinearColor& Color, float InArrowHeadSize, float LineThicknessIn)` — Draw a line with the given Color and Thickness, otherwise use default parameters
- L172 _public function_ `template<typename PointType> void DrawDirectionalArrow(const PointType& A, const PointType& B, const FVector& InNormal, const FLinearColor& Color, float InArrowHeadSize, float LineThicknessIn, bool bDepthTestedIn)` — Draw a line with the given parameters
- L180 _public function_ `template<typename PointType> void DrawPoint(const PointType& Position)` — Draw a point with default parameters
- L187 _public function_ `template<typename PointType> void DrawPoint(const PointType& Position, const FLinearColor& Color)` — Draw a point with the given Color, otherwise use default parameters
- L194 _public function_ `template<typename PointType> void DrawPoint(const PointType& Position, const FLinearColor& Color, float PointSizeIn, bool bDepthTestedIn)` — Draw a point with the given parameters
- L202 _public function_ `template<typename PointType> void DrawCircle(const PointType& Position, const PointType& Normal, float Radius, int Steps, const FLinearColor& Color, float LineThicknessIn, bool bDepthTestedIn)` — Draw a 3D circle at given position/normal with the given parameters. Tangent axes are defined internally
- L209 _public function_ `template<typename PointType> void DrawViewFacingCircle(const PointType& Position, float Radius, int Steps, const FLinearColor& Color, float LineThicknessIn, bool bDepthTestedIn)` — Draw a 3D circle at given position/normal with the given parameters. Tangent axes are defined internally
- L216 _public function_ `template<typename PointType> void DrawArc(const PointType& Position, const PointType& Normal, float Radius, int Steps, float MinAngle, float MaxAngle, const FLinearColor& Color, float LineThicknessIn, bool bDepthTestedIn)` — Draw a 3D arc at given position/normal with the given parameters. Tangent axes are defined internally
- L223 _public function_ `template<typename PointType> void DrawViewFacingArc(const PointType& Position, float Radius, int Steps, float MinAngle, float MaxAngle, const FLinearColor& Color, float LineThicknessIn, bool bDepthTestedIn)` — Draw a 3D arc at given position/normal with the given parameters. Tangent axes are defined internally
- L230 _public function_ `template<typename PointType> void DrawViewFacingX(const PointType& Position, float Width)` — Draw a world-space X facing the viewer at the given position.
- L237 _public function_ `template<typename PointType> void DrawViewFacingX(const PointType& Position, float Width, const FLinearColor& Color, float LineThicknessIn, bool bDepthTestedIn)` — Draw a world-space X facing the viewer at the given position.
- L244 _public function_ `template<typename PointType> void DrawWireCylinder(const PointType& Position, const PointType& Normal, float Radius, float Height, int Steps, const FLinearColor& Color, float LineThicknessIn, bool bDepthTestedIn)` — Draw a 3D cylinder, parameterized the same as the 3D circle but extruded by Height
- L251 _public function_ `template<typename PointType> void DrawWireCylinder(const PointType& Position, const PointType& Normal, float Radius, float Height, int Steps)` — Draw a 3D cylinder, parameterized the same as the 3D circle but extruded by Height
- L257 _public function_ `void DrawWireBox(const FBox& Box)` — Draw a 3D box, parameterized the same as the 3D circle but extruded by Height
- L262 _public function_ `void DrawWireBox(const FBox& Box, const FLinearColor& Color, float LineThicknessIn, bool bDepthTestedIn)`
- L268 _public function_ `template<typename PointType> void DrawSquare(const PointType& Center, const PointType& SideA, const PointType& SideB, const FLinearColor& Color, float LineThicknessIn, bool bDepthTestedIn)`
- L274 _public function_ `template<typename PointType> void DrawSquare(const PointType& Center, const PointType& SideA, const PointType& SideB)`
- L280 _public function_ `template<typename PointType> void DrawGrid(const PointType& Center, const PointType& Normal, const PointType& Size, const FLinearColor& Color, float LineThicknessIn, bool bDepthTestedIn)`
- L286 _public function_ `template<typename PointType> void DrawGrid(const PointType& Center, const PointType& Normal, const PointType& Up, const PointType& Side, const PointType& Size, const FLinearColor& Color, float LineThicknessIn, bool bDepthTestedIn)`
- L293 _public function_ `template<typename PointType> void DrawDisc(const PointType& Position, const PointType& Normal, float Radius, int Steps, const FColor& Color, FMaterialRenderProxy* RenderProxy, bool bDepthTestedIn)` — Draw a 3D disc at given position/normal with the given parameters. Tangent axes are defined internally
- L300 _protected member_ `FPrimitiveDrawInterface* CurrentPDI = nullptr;` — We use this for drawing, extracted in InitializeFrame
- L302 _protected member_ `FViewCameraState CameraState;`
- L303 _protected member_ `bool bHaveCameraState;`
- L307 _protected member_ `float PDISizeScale = 1.0;` — screen-space line thicknesses and point sizes are multiplied by this value to try to normalize for variable thickness that occurs at different FOVs.
- L310 _protected member_ `TArray<FTransform> TransformStack;`
- L311 _protected member_ `FTransform TotalTransform;`
- L314 _protected prototype_ `virtual void InternalDrawTransformedLine(const FVector& A, const FVector& B, const FLinearColor& Color, float LineThickness, bool bDepthTested);` — actually does the line drawing; assumes A and B are already transformed
- L316 _protected prototype_ `virtual void InternalDrawDirectionalArrow(const FVector& A, const FVector& B, const FVector& InNormal, const FLinearColor& Color, const float InHeadSize, float LineThickness, bool bDepthTested);` — actually does the arrow drawing; assumes A and B are already transformed
- L318 _protected prototype_ `virtual void InternalDrawTransformedPoint(const FVector& Position, const FLinearColor& Color, float PointSize, bool bDepthTested);` — actually does the point drawing; assumes Position is already transformed
- L322 _protected prototype_ `virtual void InternalDrawCircle(const FVector& Position, const FVector& Normal, float Radius, int Steps, const FLinearColor& Color, float LineThickness, bool bDepthTested);` — actually does the circle drawing
- L324 _protected prototype_ `virtual void InternalDrawViewFacingCircle(const FVector& Position, float Radius, int Steps, const FLinearColor& Color, float LineThickness, bool bDepthTested);` — actually does the circle drawing
- L326 _protected prototype_ `virtual void InternalDrawArc(const FVector& InPosition, const FVector& InNormal, const float InRadius, int32 InSteps, const float InMinAngle, const float InMaxAngle, const FLinearColor& Color, float LineThickness, bool bDepthTested);` — actually does the arc drawing
- L328 _protected prototype_ `virtual void InternalDrawViewFacingArc(const FVector& InPosition, float InRadius, int32 InSteps, const float InMinAngle, const float InMaxAngle, const FLinearColor& Color, float LineThickness, bool bDepthTested);` — actually does the arc drawing
- L330 _protected prototype_ `virtual void InternalDrawWireCylinder(const FVector& Position, const FVector& Normal, float Radius, float Height, int Steps, const FLinearColor& Color, float LineThickness, bool bDepthTested);` — actually does the cylinder drawing
- L332 _protected prototype_ `virtual void InternalDrawWireBox(const FBox& Box, const FLinearColor& Color, float LineThickness, bool bDepthTested);` — actually does the box drawing
- L334 _protected prototype_ `virtual void InternalDrawSquare(const FVector& Center, const FVector& SideA, const FVector& SideB, const FLinearColor& Color, float LineThickness, bool bDepthTested);` — actually does the square drawing
- L336 _protected prototype_ `virtual void InternalDrawGrid(const FVector& Center, const FVector& Normal, const FVector& Size, const FLinearColor& Color, float LineThickness, bool bDepthTested);` — actually does the grid drawing
- L338 _protected prototype_ `virtual void InternalDrawGrid(const FVector& Center, const FVector& Normal, const FVector& Up, const FVector& Side, const FVector& Size, const FLinearColor& Color, float LineThickness, bool bDepthTested);` — actually does the grid drawing
- L340 _protected prototype_ `virtual void InternalDrawViewFacingX(const FVector& Position, float Width, const FLinearColor& Color, float LineThickness, bool bDepthTested);` — actually does the X drawing
- L342 _protected prototype_ `virtual void InternalDrawDisc(const FVector& Position, const FVector& Normal, float Radius, int Steps, const FColor& Color, FMaterialRenderProxy* RenderProxy, bool bDepthTested);` — actually does the disc drawing

### `Source/Runtime/InteractiveToolsFramework/Public/ToolGroup.h` (Public)


#### struct `FTool`  
`struct FTool`  
_L14-21_
- desc: Describes a tool type to be registered into a UInteractiveToolManager.
- L17 _public member_ `FString Name;` — ITF Tool Identifier (ToolManager tool type id)
- L20 _public member_ `TSubclassOf<UInteractiveToolBuilder> BuilderClass;` — Builder class registered with the ToolManager.

#### class `FToolGroup`  
`class FToolGroup`  
_L36-114_
- desc: Declarative description of a ToolGroup. A ToolGroup describes: - which tool types should be registered (FTool entries), - which shared, context-wide features should be installed (Install/Uninstall callbacks), - which input behaviors should be active (built into a per-context UInputBehaviorSet), - optional context policy hooks (eg editor-only widget visibility). ToolGroups are intentionally *immutable descriptors* and must not own per-context runtime state. All per-context state (registered tool ids, acquired features, behavior sets, etc.) is owned by UToolGroupManager in FEnabledToolGroupState.
- L53 _public typedef_ `using FBuildBehaviorsHook = TFunction<void(UInteractiveToolsContext& ToolsContext, UInputBehaviorSet& BehaviorSet)>;` — Hook used to build the per-context input behaviors for this group.
- L55 _public prototype_ `virtual ~FToolGroup() = default;`
- L58 _public function_ `virtual void EnumerateTools(TFunction<bool(const FTool&)> ToolFunc) const` — Enumerate tools in this group. Enumeration continues while ToolFunc returns true.
- L74 _public function_ `virtual void EnumerateFeatures(TFunction<bool(const FFeature&)> FeatureFunc) const` — Enumerate shared feature requirements for this group.
- L96 _public function_ `virtual void BuildInputBehaviors(UInteractiveToolsContext& ToolsContext, UInputBehaviorSet& BehaviorSet) const` — Populate per-context behaviors into the provided BehaviorSet. Behavior instances are generally not safe to share across tools contexts. The ToolGroupManager will allocate a new BehaviorSet per enabled group per context, call this hook, and then register a behavior source with the context's InputRouter.
- L107 _public member_ `TArray<FTool> Tools;` — Declarative tool list.
- L110 _public member_ `TArray<FFeature> Features;` — Declarative feature requirements.
- L113 _public member_ `FBuildBehaviorsHook BuildBehaviorsFunc;` — Optional behavior builder (called per enabled group per context).

#### struct `FToolGroup::FFeature`  
`struct FFeature`  
_L40-50_
- desc: A shared, reference-counted feature installed into a UInteractiveToolsContext.
- L43 _public member_ `FName Key;` — Stable key identifying the feature within a tools context.
- L46 _public member_ `TFunction<void(UInteractiveToolsContext&)> Install;` — Called on 0->1 ref-count transition.
- L49 _public member_ `TFunction<void(UInteractiveToolsContext&)> Uninstall;` — Called on 1->0 ref-count transition.

### `Source/Runtime/InteractiveToolsFramework/Public/ToolGroupManager.h` (Public)


#### struct `FToolGroupFeatureEntry`  
`struct FToolGroupFeatureEntry`  
_L26-40_
- desc: Stored state for a single acquired feature key. Features are context-wide singleton-style services (target factories, snapping managers, etc.) installed into a UInteractiveToolsContext and shared across multiple enabled tool groups.
- L33 _public member_ `int32 RefCount = 0;` — Current number of enabled ToolGroups that depend on this feature. RefCount is managed by FToolGroupFeatureRegistry and should not be manipulated directly.
- L36 _public member_ `TFunction<void(UInteractiveToolsContext&)> Install;` — Called only when RefCount transitions 0 -> 1.
- L39 _public member_ `TFunction<void(UInteractiveToolsContext&)> Uninstall;` — Called only when RefCount transitions 1 -> 0.

#### class `FToolGroupFeatureRegistry`  
`class FToolGroupFeatureRegistry`  
_L50-78_
- desc: Reference-counted registry for context-wide features. This lives per UToolGroupManager (ie per UInteractiveToolsContext). Multiple groups can request the same feature key; the first request installs it into the context and the final release uninstalls it.
- L64 _public prototype_ `void Acquire( FToolGroupFeatureKey Key, UInteractiveToolsContext& Context, TFunction<void(UInteractiveToolsContext&)> Install, TFunction<void(UInteractiveToolsContext&)> Uninstall);` — Acquire the feature. If this is the first acquire for Key (0 -> 1), Install will be executed and the provided Install/Uninstall callbacks will be stored as the feature definition for this context. If the feature is already acquired (RefCount > 0), the stored Install/Uninstall callbacks are retained. Callers may pass callbacks again (eg from immutable ToolGroup descriptors); these callbacks are ignored and only the ref-count is incremented. Note: Feature keys are expected to uniquely identify feature behavior within a context. If multiple callers provide different implementations for the same key, behavior is defined by the first acquire.
- L71 _public prototype_ `void Release(FToolGroupFeatureKey Key, UInteractiveToolsContext& Context);` — Release a previously acquired feature. Final release triggers Uninstall.
- L74 _public function_ `bool IsAcquired(FToolGroupFeatureKey Key) const` — True if the feature key is currently acquired by at least one group.
- L77 _private member_ `TMap<FToolGroupFeatureKey, FToolGroupFeatureEntry> Features;`

#### struct `FEnabledToolGroupState`  
`struct FEnabledToolGroupState`  
_L92-111_
- reflection: `USTRUCT()`
- desc: Per-context runtime state for an enabled ToolGroup. ToolGroups themselves are immutable descriptors. All per-context state is owned here by the per-context UToolGroupManager, including: - which tool type ids were registered for this group, - which shared features were acquired for this group, - the per-context UInputBehaviorSet constructed for this group, - the behavior source adapter registered with the context's InputRouter.
- L98 _public member_ `TObjectPtr<UInputBehaviorSet> BehaviorSet = nullptr;` — `UPROPERTY(transient)` — Per-context behavior set for this enabled group.
- L101 _public member_ `TSet<FString> RegisteredToolTypeIds;` — Tool type identifiers registered with the ToolManager on behalf of this group.
- L104 _public member_ `TSet<FToolGroupFeatureKey> AcquiredFeatures;` — Features acquired by this enabled group (explicit tracking for cleanup).
- L107 _public member_ `TSharedPtr<IInputBehaviorSource> BehaviorSource;` — Adapter registered with the InputRouter for this group.
- L110 _public member_ `bool bRegisteredAsBehaviorSource = false;` — True if BehaviorSource has been registered with the owning context's InputRouter.

#### class `UToolGroupManager`  
`class UToolGroupManager : public UObject`  
_L129-192_
- reflection: `UCLASS(Transient)`
- inherits: `UObject`
- desc: Manages ToolGroups for a single UInteractiveToolsContext. UToolGroupManager is stored per-tools-context and is responsible for materializing per-context runtime state from immutable tool group descriptors. Responsibilities: - register immutable ToolGroup descriptors by name, - enable/disable groups within this tools context, - register/unregister tool types with UInteractiveToolManager, - acquire/release shared features via FToolGroupFeatureRegistry, - build/register per-context input behaviors with the context's InputRouter, - answer queries like "which enabled group owns the currently active tool".
- L135 _public prototype_ `void Initialize();` — Initialize internal state. Must be called before registering/enabling groups.
- L138 _public prototype_ `void Shutdown();` — Shutdown and disable all enabled tool groups, unregistering their tool types.
- L141 _public prototype_ `bool RegisterToolGroup(FName GroupName, TSharedPtr<const FToolGroup> ToolGroup);` — Register an immutable ToolGroup descriptor that can later be enabled in this context.
- L144 _public prototype_ `bool HasToolGroup(FName GroupName) const;` — Returns true if a tool group descriptor with this name is registered.
- L147 _public prototype_ `bool EnableToolGroup(FName GroupName);` — Enable (materialize + register) the named tool group in this context.
- L150 _public prototype_ `bool DisableToolGroup(FName GroupName);` — Disable (unregister + cleanup) the named tool group in this context.
- L153 _public prototype_ `void DisableAllToolGroups();` — Disable all enabled tool groups in this context.
- L157 _public prototype_ `bool IsToolGroupEnabled(FName GroupName) const;` — Returns true if the named group is currently enabled in this context.
- L160 _public prototype_ `TArray<FName> GetEnabledToolGroupNames() const;` — Returns the names of currently enabled groups.
- L165 _public prototype_ `TOptional<FName> FindEnabledGroupOwningActiveTool(EToolSide Side) const;` — If a tool is currently active, returns the name of the enabled group that registered it.
- L168 _public prototype_ `bool HasAnyEnabledToolGroups();` — Returns true if any tool groups are enabled in this context.
- L171 _private prototype_ `void AcquireGroupFeatures(const FToolGroup& ToolGroup, FEnabledToolGroupState& State, UInteractiveToolsContext& Context);`
- L172 _private prototype_ `void ReleaseAllFeaturesForGroup(FEnabledToolGroupState& State, UInteractiveToolsContext& Context);`
- L174 _private prototype_ `void RegisterGroupTools(const FToolGroup& ToolGroup, FEnabledToolGroupState& State, UInteractiveToolManager& ToolManager);`
- L175 _private prototype_ `void UnregisterGroupTools(FEnabledToolGroupState& State, UInteractiveToolManager& ToolManager);`
- L177 _private prototype_ `void RegisterGroupBehaviors(const FToolGroup& ToolGroup, FEnabledToolGroupState& State, UInteractiveToolsContext& Context);`
- L178 _private prototype_ `void UnregisterGroupBehaviors(FEnabledToolGroupState& State, UInteractiveToolsContext& Context);`
- L180 _private prototype_ `UInteractiveToolsContext* GetOwningContext() const;`
- L184 _private member_ `TMap<FName, TSharedPtr<const FToolGroup>> RegisteredGroups;` — Registered immutable tool group descriptors by name.
- L188 _private member_ `TMap<FName, FEnabledToolGroupState> EnabledGroups;` — `UPROPERTY(Transient)` — Per-context runtime state for enabled groups.
- L191 _private member_ `FToolGroupFeatureRegistry FeatureRegistry;` — Ref-counted context-wide feature registry.

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API INTERACTIVETOOLSFRAMEWORK_API`
- L17 _typedef_ `using FToolGroupFeatureKey = FName;` — Stable identifier for a shared feature installed into a UInteractiveToolsContext.

### `Source/Runtime/InteractiveToolsFramework/Public/ToolTargetManager.h` (Public)


#### class `UToolTargetManager`  
`class UToolTargetManager : public UObject`  
_L36-163_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UObject`
- desc: The tool target manager converts input objects into tool targets- objects that can expose various interfaces that tools need to operate on them. Someday, the tool target manager may implement caching of targets. See the class comment for UToolTarget for more info.
- L44 _public function_ `bool IsActive() const` — @return true if ToolManager is currently active, ie between Initialize() and Shutdown()
- L49 _public prototype_ `virtual void AddTargetFactory(UToolTargetFactory* Factory);` — Add a new ToolTargetFactory
- L54 _public prototype_ `virtual void RemoveTargetFactoriesByPredicate(TFunctionRef<bool(UToolTargetFactory*)> Predicate);` — Remove existing ToolTargetFactories by predicate
- L59 _public prototype_ `virtual UToolTargetFactory* FindFirstFactoryByPredicate(TFunctionRef<bool(UToolTargetFactory*)> Predicate);` — Find the first ToolTargetFactory that passes the Predicate function
- L65 _public function_ `template<typename CastToType> CastToType* FindFirstFactoryByType()` — Find the first ToolTargetFactory of a given type
- L74 _public prototype_ `virtual bool CanBuildTarget(UObject* SourceObject, const FToolTargetTypeRequirements& TargetRequirements) const;` — Examines stored target factories to see if one can build the requested type of target.
- L84 _public prototype_ `virtual UToolTarget* BuildTarget(UObject* SourceObject, const FToolTargetTypeRequirements& TargetRequirements);` — Uses one of the stored factories to build a tool target out of the given input object that satisfies the given requirements. If multiple factories are capable of building a qualifying target, the first encountered one will be used. If none are capable, a nullptr is returned. @return Tool target that staisfies given requirements, or nullptr if none could be created.
- L88 _public function_ `template<typename CastToType> CastToType* BuildTarget(UObject* SourceObject, const FToolTargetTypeRequirements& TargetType)` — Much like BuildTarget, but casts the target to the template argument before returning.
- L98 _public prototype_ `virtual int32 CountSelectedAndTargetable(const FToolBuilderState& SceneState, const FToolTargetTypeRequirements& TargetRequirements) const;` — Looks through the currently selected components and actors and counts the number of inputs that could be used to create qualifying tool targets.
- L105 _public prototype_ `virtual void EnumerateSelectedAndTargetableComponents(const FToolBuilderState& SceneState, const FToolTargetTypeRequirements& TargetRequirements, TFunctionRef<void(UActorComponent*)> ComponentFunc) const;` — Looks through the currently selected components and actors and counts the number of inputs that could be used to create qualifying tool targets.
- L113 _public prototype_ `virtual int32 CountSelectedAndTargetableWithPredicate(const FToolBuilderState& SceneState, const FToolTargetTypeRequirements& TargetRequirements, TFunctionRef<bool(UActorComponent&)> ComponentPred) const;` — Looks through the currently selected components and actors and counts the number of inputs that could be used to create qualifying tool targets with an additional test predicate.
- L122 _public prototype_ `virtual UToolTarget* BuildFirstSelectedTargetable(const FToolBuilderState& SceneState, const FToolTargetTypeRequirements& TargetRequirements);` — Looks through the currently selected components and actors and builds a target out of the first encountered element that satisfies the requirements.
- L129 _public prototype_ `virtual TArray<TObjectPtr<UToolTarget>> BuildAllSelectedTargetable(const FToolBuilderState& SceneState, const FToolTargetTypeRequirements& TargetRequirements);` — Looks through the current selected components and actors and builds all targets that satisfy the requirements.
- L133 _public prototype_ `virtual void Initialize();` — Initialize the ToolTargetManager. UInteractiveToolsContext calls this, you should not.
- L136 _public prototype_ `virtual void Shutdown();` — Shutdown the ToolTargetManager. Called by UInteractiveToolsContext.
- L139 _public function_ `virtual void SetInputFilterFunction(TFunction<bool(const UObject*)> ShouldAllowBuildingFromInputObject)` — Additional filter function that will be applied in CanBuildTarget and BuildTarget.
- L151 _protected function_ `UToolTargetManager()`
- L154 _protected member_ `bool bIsActive = false;` — This flag is set to true on Initialize() and false on Shutdown().
- L157 _protected member_ `TArray<TObjectPtr<UToolTargetFactory>> Factories;` — `UPROPERTY()`
- L162 _private member_ `TFunction<bool(const UObject*)> InputFilterFunction;`

#### Free symbols / members of external scopes

- L67 _function_ `UToolTargetFactory* Found = FindFirstFactoryByPredicate([](UToolTargetFactory* Factory) { return Cast<CastToType>(Factory) != nullptr; });` (scope `UToolTargetManager::FindFirstFactoryByType`)

### `Source/Runtime/InteractiveToolsFramework/Public/ToolTargets/PrimitiveComponentToolTarget.h` (Public)


#### class `UPrimitiveComponentToolTarget`  
`class UPrimitiveComponentToolTarget : public UToolTarget, public IPrimitiveComponentBackedTarget`  
_L17-47_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UToolTarget,IPrimitiveComponentBackedTarget`
- desc: A tool target to share some reusable code for tool targets that are backed by primitive components.
- L23 _public prototype_ `virtual bool IsValid() const override;` — UToolTarget
- L26 _public prototype_ `virtual UPrimitiveComponent* GetOwnerComponent() const override;` — IPrimitiveComponentBackedTarget implementation
- L27 _public prototype_ `virtual USceneComponent* GetOwnerSceneComponent() const override;`
- L28 _public prototype_ `virtual AActor* GetOwnerActor() const override;`
- L29 _public prototype_ `virtual void SetOwnerVisibility(bool bVisible) const override;`
- L30 _public prototype_ `virtual FTransform GetWorldTransform() const override;`
- L31 _public prototype_ `virtual bool HitTestComponent(const FRay& WorldRay, FHitResult& OutHit) const override;`
- L34 _public prototype_ `void BeginDestroy() override;` — UObject
- L39 _protected prototype_ `void InitializeComponent(UPrimitiveComponent* ComponentIn);`
- L41 _protected member_ `TWeakObjectPtr<UPrimitiveComponent> Component;`
- L45 _private prototype_ `void OnObjectsReplaced(const FCoreUObjectDelegates::FReplacementObjectMap& Map);`

#### class `UPrimitiveComponentToolTargetFactory`  
`class UPrimitiveComponentToolTargetFactory : public UToolTargetFactory`  
_L53-59_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UToolTargetFactory`
- desc: Factory for UPrimitiveComponentToolTarget to be used by the target manager.
- L57 _public prototype_ `virtual bool CanBuildTarget(UObject* SourceObject, const FToolTargetTypeRequirements& TargetTypeInfo) const override;`
- L58 _public prototype_ `virtual UToolTarget* BuildTarget(UObject* SourceObject, const FToolTargetTypeRequirements& TargetTypeInfo) override;`

### `Source/Runtime/InteractiveToolsFramework/Public/ToolTargets/SceneComponentToolTarget.h` (Public)


#### class `USceneComponentToolTarget`  
`class USceneComponentToolTarget : public UToolTarget, public ISceneComponentBackedTarget`  
_L17-45_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UToolTarget,ISceneComponentBackedTarget`
- desc: A tool target to share some reusable code for tool targets that are backed by scene components
- L23 _public prototype_ `virtual bool IsValid() const override;` — UToolTarget
- L26 _public prototype_ `virtual USceneComponent* GetOwnerSceneComponent() const;` — ISceneComponentBackedTarget implementation
- L27 _public prototype_ `virtual AActor* GetOwnerActor() const;`
- L28 _public prototype_ `virtual void SetOwnerVisibility(bool bVisible) const;`
- L29 _public prototype_ `virtual FTransform GetWorldTransform() const;`
- L32 _public prototype_ `void BeginDestroy() override;` — UObject
- L37 _protected prototype_ `void InitializeComponent(USceneComponent* ComponentIn);`
- L39 _protected member_ `TWeakObjectPtr<USceneComponent> Component;`
- L43 _private prototype_ `void OnObjectsReplaced(const FCoreUObjectDelegates::FReplacementObjectMap& Map);`

#### class `USceneComponentToolTargetFactory`  
`class USceneComponentToolTargetFactory : public UToolTargetFactory`  
_L51-57_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UToolTargetFactory`
- desc: Factory for USceneComponentToolTarget to be used by the target manager.
- L55 _public prototype_ `virtual bool CanBuildTarget(UObject* SourceObject, const FToolTargetTypeRequirements& TargetTypeInfo) const override;`
- L56 _public prototype_ `virtual UToolTarget* BuildTarget(UObject* SourceObject, const FToolTargetTypeRequirements& TargetTypeInfo) override;`

### `Source/Runtime/InteractiveToolsFramework/Public/ToolTargets/ToolTarget.h` (Public)


#### class `UToolTarget`  
`class UToolTarget : public UObject`  
_L39-46_
- reflection: `UCLASS(Transient, Abstract, MinimalAPI)`
- inherits: `UObject`
- desc: A tool target is a stand-in object that a tool can operate on. It exposes the necessary interfaces to the tool. There are two intended purposes of the tool target system: 1. Allow tools to operate on arbitrary objects as long as they can be made to provide the tool with the necessary inputs. For instance, a mesh editing tool should be able to operate on skeletal, static, volume, and other mesh as long as the target manager has a registered factory that can use that type of mesh to create a suitable target. 2. (not yet used) Help cache tool inputs. I.e., if a tool requires an expensive conversion before it can work on an item, the converted result can be stored in the tool target which can be cached by the target manager and provided the next time the same type of target is requested for that item. Given an object, tool builders usually ask the target manager to turn it into a target that has the interfaces the tools needs. The tools cast the target to those interfaces to use them.
- L45 _public prototype_ `virtual bool IsValid() const PURE_VIRTUAL(UToolTarget::IsValid, return false;);` — @return true if target is still valid. May become invalid for various reasons (eg Component was deleted out from under us)

#### class `FToolTargetTypeRequirements`  
`class FToolTargetTypeRequirements`  
_L53-82_
- desc: A structure used to specify the requirements of a tool for its target. E.g., a tool may need a target that has interfaces x,y,z.
- L57 _public member_ `TArray<const UClass*, TInlineAllocator<5>> Interfaces;`
- L59 _public function_ `FToolTargetTypeRequirements()`
- L63 _public function_ `explicit FToolTargetTypeRequirements(const UClass* Interface0)`
- L68 _public function_ `explicit FToolTargetTypeRequirements(const TArray<const UClass*>& InterfacesIn)`
- L73 _public function_ `FToolTargetTypeRequirements& Add(UClass* Interface)`
- L79 _public prototype_ `bool AreSatisfiedBy(UClass* Class) const;`
- L81 _public prototype_ `bool AreSatisfiedBy(UToolTarget* ToolTarget) const;`

#### class `UToolTargetFactory`  
`class UToolTargetFactory : public UObject`  
_L91-129_
- reflection: `UCLASS(Transient, Abstract, MinimalAPI)`
- inherits: `UObject`
- desc: Base class for factories of tool targets, which let a tool manager build targets out of inputs without knowing anything about the inputs itself, as long as it has a factory registered that is able to process the input.
- L96 _public prototype_ `virtual bool CanBuildTarget(UObject* SourceObject, const FToolTargetTypeRequirements& TargetTypeInfo) const PURE_VIRTUAL(UToolTargetFactory::CanBuildTarget, return false;);`
- L97 _public prototype_ `virtual UToolTarget* BuildTarget(UObject* SourceObject, const FToolTargetTypeRequirements& TargetTypeInfo) PURE_VIRTUAL(UToolTargetFactory::BuildTarget, return nullptr;);`
- L112 _public prototype_ `virtual int32 CanBuildTargets(const TArray<UObject*>& InputObjects, const FToolTargetTypeRequirements& TargetTypeInfo, TArray<bool>& WouldBeUsedOut);` — Called to see if a factory could make one or more targets out of the given array of input objects, if multiple are provided. @param WouldBeUsedOut Set to be 1:1 with InputObjects, with each entry set to true if that input object would be used in the creation of a tool target @return Number of targets that would be returned by the equivalent BuildTargets call.
- L120 _public prototype_ `virtual TArray<UToolTarget*> BuildTargets(const TArray<UObject*>& InputObjects, const FToolTargetTypeRequirements& TargetTypeInfo, TArray<bool>& WasUsedOut);` — Called to build one or more targets out of the given array of input objects, if multiple are provided. @param WouldBeUsedOut Set to be 1:1 with InputObjects, with each entry set to true if that input object was used in the creation of a tool target
- L128 _public prototype_ `virtual UToolTarget* BuildFirstTarget(const TArray<UObject*>& InputObjects, const FToolTargetTypeRequirements& TargetTypeInfo, TArray<bool>& WasUsedOut);` — Called by BuildFirstSelectedTargetable, intended to create just one target out of the given input. @param WouldBeUsedOut Set to be 1:1 with InputObjects, with each entry set to true if that input object was used in the creation of a tool target
