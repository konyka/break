# Editor / ViewportInteraction

- module root: `Source/Editor/ViewportInteraction`
- headers: 26; symbols: 694
- symbol kinds: class=36, delegate=11, enum=7, enumerator=30, function=63, macro=14, member=218, namespace=2, prototype=300, struct=6, variable=7
- PrivateDependencyModuleNames: LevelEditor
- PublicDependencyModuleNames: Core, CoreUObject, EditorFramework, Engine, InputCore, RHI, RenderCore, Slate, SlateCore, UnrealEd

### `Source/Editor/ViewportInteraction/Private/Gizmo/VIPivotTransformGizmo.h` (Private)


#### class `APivotTransformGizmo`  
`class UE_DEPRECATED(5.7, "The ViewportInteraction module is being deprecated alongside VR Editor mode.") APivotTransformGizmo : public ABaseTransformGizmo`  
_L19-66_
- reflection: `UCLASS()`
- inherits: `ABaseTransformGizmo`
- desc: A transform gizmo on the pivot that allows you to interact with selected objects by moving, scaling and rotating.
- L26 _public prototype_ `APivotTransformGizmo();` — Default constructor that sets up CDO properties
- L31 _public prototype_ `virtual void UpdateGizmo(const EGizmoHandleTypes InGizmoType, const ECoordSystem InGizmoCoordinateSpace, const FTransform& InLocalToWorld, const FBox& InLocalBounds, const FVector& InViewLocation, const float InScaleMultiplier, bool bInAllHandlesVisible, const bool bInAllowRotationAndScaleHandles, class UActorComponent* DraggingHandle, const TArray<UActorComponent*>& InHoveringOverHandles, const float InGizmoHoverScale, const float InGizmoHoverAnimationDuration) override;` — Called by the world interaction system after we've been spawned into the world, to allow us to create components and set everything up nicely for the selected objects that we'll be used to manipulate
- L38 _private member_ `TObjectPtr<class UUniformScaleGizmoHandleGroup> UniformScaleGizmoHandleGroup;` — `UPROPERTY()` — Uniform scale handle group component
- L42 _private member_ `TObjectPtr<class UPivotTranslationGizmoHandleGroup> TranslationGizmoHandleGroup;` — `UPROPERTY()` — Translation handle group component
- L46 _private member_ `TObjectPtr<class UPivotScaleGizmoHandleGroup> ScaleGizmoHandleGroup;` — `UPROPERTY()` — Scale handle group component
- L50 _private member_ `TObjectPtr<class UPivotPlaneTranslationGizmoHandleGroup> PlaneTranslationGizmoHandleGroup;` — `UPROPERTY()` — Plane translation handle group component
- L54 _private member_ `TObjectPtr<class UPivotRotationGizmoHandleGroup> RotationGizmoHandleGroup;` — `UPROPERTY()` — Rotation handle group component
- L58 _private member_ `TObjectPtr<class UStretchGizmoHandleGroup> StretchGizmoHandleGroup;` — `UPROPERTY()` — Stretch handle group component
- L61 _private member_ `float AimingAtGizmoScaleAlpha;` — The alpha for gizmo animation when aiming at it with a laser
- L65 _private member_ `TObjectPtr<UActorComponent> LastDraggingHandle;` — `UPROPERTY()` — Handle from previous tick that was dragged

#### class `UPivotTranslationGizmoHandleGroup`  
`class UE_DEPRECATED(5.7, "The ViewportInteraction module is being deprecated alongside VR Editor mode.") UPivotTranslationGizmoHandleGroup : public UAxisGizmoHandleGroup`  
_L72-87_
- reflection: `UCLASS()`
- inherits: `UAxisGizmoHandleGroup`
- desc: Axis Gizmo handle for translating
- L79 _public prototype_ `UPivotTranslationGizmoHandleGroup();` — Default constructor that sets up CDO properties
- L82 _public prototype_ `virtual void UpdateGizmoHandleGroup( const FTransform& LocalToWorld, const FBox& LocalBounds, const FVector ViewLocation, const bool bAllHandlesVisible, class UActorComponent* DraggingHandle, const TArray< UActorComponent* >& HoveringOverHandles, float AnimationAlpha, float GizmoScale, const float GizmoHoverScale, const float GizmoHoverAnimationDuration, bool& bOutIsHoveringOrDraggingThisHandleGroup ) override;` — Updates the gizmo handles
- L86 _public prototype_ `virtual EGizmoHandleTypes GetHandleType() const override;` — Gets the GizmoType for this Gizmo handle

#### class `UPivotScaleGizmoHandleGroup`  
`class UE_DEPRECATED(5.7, "The ViewportInteraction module is being deprecated alongside VR Editor mode.") UPivotScaleGizmoHandleGroup : public UAxisGizmoHandleGroup`  
_L93-111_
- reflection: `UCLASS()`
- inherits: `UAxisGizmoHandleGroup`
- desc: Axis Gizmo handle for scaling
- L100 _public prototype_ `UPivotScaleGizmoHandleGroup();` — Default constructor that sets up CDO properties
- L103 _public prototype_ `virtual void UpdateGizmoHandleGroup( const FTransform& LocalToWorld, const FBox& LocalBounds, const FVector ViewLocation, const bool bAllHandlesVisible, class UActorComponent* DraggingHandle, const TArray< UActorComponent* >& HoveringOverHandles, float AnimationAlpha, float GizmoScale, const float GizmoHoverScale, const float GizmoHoverAnimationDuration, bool& bOutIsHoveringOrDraggingThisHandleGroup ) override;` — Updates the gizmo handles
- L107 _public prototype_ `virtual EGizmoHandleTypes GetHandleType() const override;` — Gets the GizmoType for this Gizmo handle
- L110 _public prototype_ `virtual bool SupportsWorldCoordinateSpace() const override;` — Returns true if this type of handle is allowed with world space gizmos

#### class `UPivotPlaneTranslationGizmoHandleGroup`  
`class UE_DEPRECATED(5.7, "The ViewportInteraction module is being deprecated alongside VR Editor mode.") UPivotPlaneTranslationGizmoHandleGroup : public UAxisGizmoHandleGroup`  
_L117-132_
- reflection: `UCLASS()`
- inherits: `UAxisGizmoHandleGroup`
- desc: Axis Gizmo handle for plane translation
- L124 _public prototype_ `UPivotPlaneTranslationGizmoHandleGroup();` — Default constructor that sets up CDO properties
- L127 _public prototype_ `virtual void UpdateGizmoHandleGroup( const FTransform& LocalToWorld, const FBox& LocalBounds, const FVector ViewLocation, const bool bAllHandlesVisible, class UActorComponent* DraggingHandle, const TArray< UActorComponent* >& HoveringOverHandles, float AnimationAlpha, float GizmoScale, const float GizmoHoverScale, const float GizmoHoverAnimationDuration, bool& bOutIsHoveringOrDraggingThisHandleGroup ) override;` — Updates the gizmo handles
- L131 _public prototype_ `virtual EGizmoHandleTypes GetHandleType() const override;` — Gets the GizmoType for this Gizmo handle

#### class `UPivotRotationGizmoHandleGroup`  
`class UE_DEPRECATED(5.7, "The ViewportInteraction module is being deprecated alongside VR Editor mode.") UPivotRotationGizmoHandleGroup : public UAxisGizmoHandleGroup`  
_L139-193_
- reflection: `UCLASS()`
- inherits: `UAxisGizmoHandleGroup`
- desc: Axis Gizmo handle for rotation
- L146 _public prototype_ `UPivotRotationGizmoHandleGroup();` — Default constructor that sets up CDO properties
- L149 _public prototype_ `virtual void UpdateGizmoHandleGroup(const FTransform& LocalToWorld, const FBox& LocalBounds, const FVector ViewLocation, const bool bAllHandlesVisible, class UActorComponent* DraggingHandle, const TArray< UActorComponent* >& HoveringOverHandles, float AnimationAlpha, float GizmoScale, const float GizmoHoverScale, const float GizmoHoverAnimationDuration, bool& bOutIsHoveringOrDraggingThisHandleGroup ) override;` — Updates the gizmo handles
- L153 _public prototype_ `virtual EGizmoHandleTypes GetHandleType() const override;` — Gets the GizmoType for this Gizmo handle
- L158 _private prototype_ `void UpdateIndicator(USceneComponent* IndicatorRoot, const FVector& Direction, const uint32 FacingAxisIndex);` — Updates the root of an indicator to rotate the indicator itself
- L161 _private prototype_ `void ShowRotationVisuals(const bool bInShow);` — Make the components visible when dragging rotation
- L163 _private prototype_ `void SetupIndicator(USceneComponent* RootComponent, UGizmoHandleMeshComponent* IndicatorMeshComponent, UStaticMesh* Mesh);`
- L165 _private prototype_ `void SetIndicatorColor(UStaticMeshComponent* InMeshComponent, const FLinearColor& InHandleColor);`
- L169 _private member_ `TObjectPtr<USceneComponent> RootFullRotationHandleComponent;` — `UPROPERTY()` — Root component of all the mesh components that are used to visualize the rotation when dragging
- L173 _private member_ `TObjectPtr<class UGizmoHandleMeshComponent> FullRotationHandleMeshComponent;` — `UPROPERTY()` — When dragging a rotation handle the full rotation circle appears
- L177 _private member_ `TObjectPtr<class UGizmoHandleMeshComponent> StartRotationIndicatorMeshComponent;` — `UPROPERTY()` — The mesh that indicated the start rotation
- L181 _private member_ `TObjectPtr<USceneComponent> RootStartRotationIdicatorComponent;` — `UPROPERTY()` — The root component of the start rotation indicator
- L185 _private member_ `TObjectPtr<class UGizmoHandleMeshComponent> DeltaRotationIndicatorMeshComponent;` — `UPROPERTY()` — The mesh that indicated the delta rotation
- L189 _private member_ `TObjectPtr<USceneComponent> RootDeltaRotationIndicatorComponent;` — `UPROPERTY()` — The root component of the delta rotation indicator
- L192 _private member_ `TOptional<FQuat> StartDragRotation;` — The rotation when starting to drag the gizmo

### `Source/Editor/ViewportInteraction/Private/Gizmo/VIStretchGizmoHandle.h` (Private)


#### class `UStretchGizmoHandleGroup`  
`class UE_DEPRECATED(5.7, "The ViewportInteraction module is being deprecated alongside VR Editor mode.") UStretchGizmoHandleGroup : public UGizmoHandleGroup`  
_L22-40_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGizmoHandleGroup`
- desc: Gizmo handle for stretching/scaling
- L29 _public prototype_ `UStretchGizmoHandleGroup();` — Default constructor that sets up CDO properties
- L32 _public prototype_ `virtual void UpdateGizmoHandleGroup( const FTransform& LocalToWorld, const FBox& LocalBounds, const FVector ViewLocation, const bool bAllHandlesVisible, class UActorComponent* DraggingHandle, const TArray< UActorComponent* >& HoveringOverHandles, float AnimationAlpha, float GizmoScale, const float GizmoHoverScale, const float GizmoHoverAnimationDuration, bool& bOutIsHoveringOrDraggingThisHandleGroup ) override;` — Updates the Gizmo handles
- L36 _public prototype_ `virtual EGizmoHandleTypes GetHandleType() const override;` — Gets the GizmoType for this Gizmo handle
- L39 _public prototype_ `virtual bool SupportsWorldCoordinateSpace() const override;` — Returns true if this type of handle is allowed with world space gizmos

#### class `UStretchGizmoHandleDragOperation`  
`class UStretchGizmoHandleDragOperation : public UViewportDragOperation`  
_L43-51_
- reflection: `UCLASS()`
- inherits: `UViewportDragOperation`
- L50 _public prototype_ `virtual void ExecuteDrag(struct FDraggingTransformableData& DraggingData) override;` — IViewportDragOperation

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API VIEWPORTINTERACTION_API`

### `Source/Editor/ViewportInteraction/Private/Gizmo/VIUniformScaleGizmoHandle.h` (Private)


#### class `UUniformScaleGizmoHandleGroup`  
`class UE_DEPRECATED(5.7, "The ViewportInteraction module is being deprecated alongside VR Editor mode.") UUniformScaleGizmoHandleGroup : public UGizmoHandleGroup`  
_L21-44_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGizmoHandleGroup`
- desc: Gizmo handle for uniform scaling
- L28 _public prototype_ `UUniformScaleGizmoHandleGroup();` — Default constructor that sets up CDO properties
- L31 _public prototype_ `virtual void UpdateGizmoHandleGroup( const FTransform& LocalToWorld, const FBox& LocalBounds, const FVector ViewLocation, const bool bAllHandlesVisible, class UActorComponent* DraggingHandle, const TArray< UActorComponent* >& HoveringOverHandles, float AnimationAlpha, float GizmoScale, const float GizmoHoverScale, const float GizmoHoverAnimationDuration, bool& bOutIsHoveringOrDraggingThisHandleGroup ) override;` — Updates the Gizmo handles
- L35 _public prototype_ `virtual EGizmoHandleTypes GetHandleType() const override;` — Gets the GizmoType for this Gizmo handle
- L38 _public prototype_ `void SetUsePivotPointAsLocation( const bool bInUsePivotAsLocation );` — Sets if the pivot point is used as location for the handle
- L43 _private member_ `bool bUsePivotAsLocation;` — If the pivot point is used for the uniform scaling handle

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API VIEWPORTINTERACTION_API`

### `Source/Editor/ViewportInteraction/Private/ViewportInteractionInputProcessor.h` (Private)


#### class `FViewportInteractionInputProcessor`  
`class FViewportInteractionInputProcessor : public IInputProcessor`  
_L20-38_
- inherits: `IInputProcessor`
- L23 _public prototype_ `FViewportInteractionInputProcessor(class UViewportWorldInteraction* InWorldInteraction);`
- L24 _public prototype_ `virtual ~FViewportInteractionInputProcessor ();`
- L27 _public prototype_ `virtual void Tick( const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor ) override;`
- L28 _public prototype_ `virtual bool HandleKeyDownEvent( FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent ) override;`
- L29 _public prototype_ `virtual bool HandleKeyUpEvent( FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent ) override;`
- L30 _public prototype_ `virtual bool HandleAnalogInputEvent( FSlateApplication& SlateApp, const FAnalogInputEvent& InAnalogInputEvent ) override;`
- L31 _public prototype_ `virtual bool HandleMouseMoveEvent( FSlateApplication& SlateApp, const FPointerEvent& MouseEvent ) override;`
- L32 _public function_ `virtual const TCHAR* GetDebugName() const override`
- L37 _private member_ `class UViewportWorldInteraction* WorldInteraction;` — The WorldInteraction that will receive the input

### `Source/Editor/ViewportInteraction/Private/ViewportInteractionModule.h` (Private)


#### class `PRAGMA_DISABLE_DEPRECATION_WARNINGS`  
`PRAGMA_DISABLE_DEPRECATION_WARNINGS : public IViewportInteractionModule PRAGMA_ENABLE_DEPRECATION_WARNINGS`  
_L9-36_
- inherits: `IViewportInteractionModulePRAGMA_ENABLE_DEPRECATION_WARNINGS`
- L15 _public prototype_ `FViewportInteractionModule();`
- L16 _public prototype_ `virtual ~FViewportInteractionModule();`
- L19 _public prototype_ `virtual void StartupModule() override;` — FModuleInterface overrides
- L20 _public prototype_ `virtual void ShutdownModule() override;`
- L21 _public prototype_ `virtual void PostLoadCallback() override;`
- L22 _public function_ `virtual bool SupportsDynamicReloading() override`
- L27 _public prototype_ `static void ToggleMode();`
- L29 _public prototype_ `void EnabledViewportWorldInteractionFromCommand(const bool bEnabled);`
- L30 _public prototype_ `bool EnabledViewportWorldInteractionFromCommand();`
- L35 _private member_ `bool bEnabledViewportWorldInteractionFromCommand;` — If we started the ViewportWorldInteraction from Toggle command.

### `Source/Editor/ViewportInteraction/Public/ActorTransformer.h` (Public)


#### class `UActorTransformer`  
`class UE_DEPRECATED(5.7, "The ViewportInteraction module is being deprecated alongside VR Editor mode.") UActorTransformer : public UViewportTransformer`  
_L14-35_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UViewportTransformer`
- L21 _public prototype_ `virtual void Init( class UViewportWorldInteraction* InitViewportWorldInteraction ) override;` — UViewportTransformer overrides
- L22 _public prototype_ `virtual void Shutdown() override;`
- L23 _public function_ `virtual bool CanAlignToActors() const override`
- L27 _public prototype_ `virtual void OnStartDragging(class UViewportInteractor* Interactor) override;`
- L28 _public prototype_ `virtual void OnStopDragging(class UViewportInteractor* Interactor) override;`
- L33 _protected prototype_ `void OnActorSelectionChanged( UObject* ChangedObject );` — Called when selection changes in the level

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API VIEWPORTINTERACTION_API`

### `Source/Editor/ViewportInteraction/Public/ActorViewportTransformable.h` (Public)


#### class `FActorViewportTransformable`  
`class UE_DEPRECATED(5.7, "The ViewportInteraction module is being deprecated alongside VR Editor mode.") FActorViewportTransformable : public FViewportTransformable`  
_L17-43_
- inherits: `FViewportTransformable`
- desc: A transformable actor
- L23 _public function_ `FActorViewportTransformable() : ActorWeakPtr(), bShouldBeCarried( false )` — Sets up safe defaults
- L30 _public prototype_ `virtual const FTransform GetTransform() const override;` — FViewportTransformable overrides
- L31 _public prototype_ `virtual void ApplyTransform( const FTransform& NewTransform, const bool bSweep ) override;`
- L32 _public prototype_ `virtual FBox BuildBoundingBox( const FTransform& BoundingBoxToWorld ) const override;`
- L33 _public prototype_ `virtual bool IsPhysicallySimulated() const override;`
- L34 _public prototype_ `virtual bool ShouldBeCarried() const override;`
- L35 _public prototype_ `virtual void SetLinearVelocity( const FVector& NewVelocity ) override;`
- L36 _public prototype_ `virtual FVector GetLinearVelocity() const override;`
- L37 _public prototype_ `virtual void UpdateIgnoredActorList( TArray<class AActor*>& IgnoredActors ) override;`
- L40 _public member_ `TWeakObjectPtr<class AActor> ActorWeakPtr;` — The actual actor object
- L42 _public member_ `bool bShouldBeCarried;` — whether this actor should be 'carried' (moved and rotated) when dragged, if possible, instead of only translated

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API VIEWPORTINTERACTION_API`

### `Source/Editor/ViewportInteraction/Public/IViewportInteractionModule.h` (Public)


#### class `IViewportInteractionModule`  
`class UE_DEPRECATED(5.7, "The ViewportInteraction module is being deprecated alongside VR Editor mode.") IViewportInteractionModule : public IModuleInterface`  
_L12-37_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L23 _public function_ `static inline IViewportInteractionModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L33 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Source/Editor/ViewportInteraction/Public/MouseCursorInteractor.h` (Public)


#### class `UMouseCursorInteractor`  
`class UE_DEPRECATED(5.7, "The ViewportInteraction module is being deprecated alongside VR Editor mode.") UMouseCursorInteractor : public UViewportInteractor`  
_L17-44_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UViewportInteractor`
- desc: Viewport interactor for a mouse cursor
- L26 _public prototype_ `UMouseCursorInteractor();` — Default constructor.
- L29 _public prototype_ `void Init();` — Initialize default values
- L32 _public prototype_ `virtual void PollInput() override;` — ViewportInteractor overrides
- L33 _public prototype_ `virtual bool IsModifierPressed() const override;`
- L37 _protected prototype_ `virtual bool AllowLaserSmoothing() const;`
- L42 _private member_ `bool bIsControlKeyPressed;` — Whether the control key was pressed the last time input was polled

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API VIEWPORTINTERACTION_API`

### `Source/Editor/ViewportInteraction/Public/VIBaseTransformGizmo.h` (Public)


#### enum `EGizmoHandleTypes`  
`enum class UE_DEPRECATED(5.7, "The ViewportInteraction module is being deprecated alongside VR Editor mode.") EGizmoHandleTypes : uint8`  
_L21-27_
- reflection: `UENUM()`
- L23 _public enumerator_ `All = 0`
- L24 _public enumerator_ `Translate = 1`
- L25 _public enumerator_ `Rotate = 2`
- L26 _public enumerator_ `Scale = 3`

#### struct `FTransformGizmoMeasurement`  
`struct UE_DEPRECATED(5.7, "The ViewportInteraction module is being deprecated alongside VR Editor mode.") FTransformGizmoMeasurement`  
_L33-40_
- reflection: `USTRUCT()`
- desc: Displays measurements along the bounds of selected objects
- L39 _public member_ `TObjectPtr<class UTextRenderComponent> MeasurementText = nullptr;` — `UPROPERTY()` — The text that displays the actual measurement and units

#### class `ABaseTransformGizmo`  
`class UE_DEPRECATED(5.7, "The ViewportInteraction module is being deprecated alongside VR Editor mode.") ABaseTransformGizmo : public AActor`  
_L47-118_
- reflection: `UCLASS(MinimalAPI, Abstract, NotPlaceable)`
- inherits: `AActor`
- desc: Base class for transform gizmo
- L54 _public prototype_ `ABaseTransformGizmo();` — Default constructor that sets up CDO properties
- L57 _public function_ `virtual bool IsEditorOnly() const final`
- L64 _public prototype_ `void OnNewObjectsSelected();` — Call this when new objects become selected.  This triggers an animation transition.
- L69 _public prototype_ `class UViewportDragOperationComponent* GetInteractionType( UActorComponent* DraggedComponent, TOptional<FTransformGizmoHandlePlacement>& OutHandlePlacement );` — Called by the world interaction system when one of our components is dragged by the user to find out what type of interaction to do.  If null is passed in then we'll treat it as dragging the whole object (rather than a specific axis/handle)
- L72 _public prototype_ `float GetAnimationAlpha();` — Updates the animation with the current time and selected time
- L75 _public prototype_ `void SetOwnerWorldInteraction( class UViewportWorldInteraction* InWorldInteraction );` — Sets the owner
- L78 _public prototype_ `class UViewportWorldInteraction* GetOwnerWorldInteraction() const;` — Gets the owner
- L83 _public function_ `virtual void UpdateGizmo(const EGizmoHandleTypes InGizmoType, const ECoordSystem InGizmoCoordinateSpace, const FTransform& InLocalToWorld, const FBox& InLocalBounds, const FVector& InViewLocation, const float InScaleMultiplier, bool bInAllHandlesVisible, const bool bInAllowRotationAndScaleHandles, class UActorComponent* DraggingHandle, const TArray<UActorComponent*>& InHoveringOverHandles, const float InGizmoHoverScale, const float InGizmoHoverAnimationDuration)` — Called by the world interaction system after we've been spawned into the world, to allow us to create components and set everything up nicely for the selected objects that we'll be used to manipulate
- L88 _public prototype_ `EGizmoHandleTypes GetGizmoType() const;` — Gets the current gizmo handle type
- L93 _protected prototype_ `static void GetBoundingBoxEdge( const FBox& Box, const int32 AxisIndex, const int32 EdgeIndex, FVector& OutVertex0, FVector& OutVertex1 );` — Static: Given a bounding box and information about which edge to query, returns the vertex positions of that edge
- L96 _protected prototype_ `void UpdateHandleVisibility(const EGizmoHandleTypes InGizmoType, const ECoordSystem InGizmoCoordinateSpace, bool bInAllHandlesVisible, UActorComponent* DraggingHandle);` — Updates the visibility of all the handles
- L99 _protected prototype_ `bool GetShowMeasurementText() const;` — Gets if the gizmo shows measurement texts
- L102 _protected member_ `FTimespan SelectedAtTime;` — Real time that the gizmo was last attached to a selected set of objects.  This is used for animation transitions
- L106 _protected member_ `TObjectPtr<USceneComponent> SceneComponent;` — `UPROPERTY()` — Scene component root of this actor
- L110 _protected member_ `TArray< TObjectPtr<class UGizmoHandleGroup> > AllHandleGroups;` — `UPROPERTY()` — All gizmo components
- L114 _protected member_ `TObjectPtr<class UViewportWorldInteraction> WorldInteraction;` — `UPROPERTY()` — Owning object
- L117 _protected member_ `EGizmoHandleTypes GizmoType;` — Current gizmo type

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API VIEWPORTINTERACTION_API`

### `Source/Editor/ViewportInteraction/Public/VIGizmoHandle.h` (Public)


#### struct `FGizmoHandle`  
`struct UE_DEPRECATED(5.7, "The ViewportInteraction module is being deprecated alongside VR Editor mode.") FGizmoHandle`  
_L23-32_
- reflection: `USTRUCT()`
- L28 _public member_ `class UGizmoHandleMeshComponent* HandleMesh;` — Static mesh for this handle
- L31 _public member_ `float HoverAlpha;` — Scalar that will advance toward 1.0 over time as we hover over the gizmo handle

#### class `UGizmoHandleGroup`  
`class UE_DEPRECATED(5.7, "The ViewportInteraction module is being deprecated alongside VR Editor mode.") UGizmoHandleGroup : public USceneComponent`  
_L39-141_
- reflection: `UCLASS(MinimalAPI, ABSTRACT)`
- inherits: `USceneComponent`
- desc: Base class for gizmo handles
- L46 _public prototype_ `UGizmoHandleGroup();` — Default constructor that sets up CDO properties
- L49 _public prototype_ `FTransformGizmoHandlePlacement MakeHandlePlacementForIndex( const int32 HandleIndex ) const;` — Given the unique index, makes a handle
- L52 _public prototype_ `int32 MakeHandleIndex( const FTransformGizmoHandlePlacement HandlePlacement ) const;` — Makes a unique index for a handle
- L55 _public prototype_ `FString MakeHandleName( const FTransformGizmoHandlePlacement HandlePlacement ) const;` — Makes up a name string for a handle
- L58 _public prototype_ `static FVector GetAxisVector( const int32 AxisIndex, const ETransformGizmoHandleDirection HandleDirection );` — Static: Given an axis (0-2) and a facing direction, returns the vector normal for that axis
- L61 _public prototype_ `virtual void UpdateGizmoHandleGroup( const FTransform& LocalToWorld, const FBox& LocalBounds, const FVector ViewLocation, const bool bAllHandlesVisible, class UActorComponent* DraggingHandle, const TArray< UActorComponent* >& HoveringOverHandles, float AnimationAlpha, float GizmoScale, const float GizmoHoverScale, const float GizmoHoverAnimationDuration, bool& bOutIsHoveringOrDraggingThisHandleGroup );` — Updates the Gizmo handles, needs to be implemented by derived classes
- L65 _public prototype_ `void UpdateVisibilityAndCollision(const EGizmoHandleTypes GizmoType, const ECoordSystem GizmoCoordinateSpace, const bool bAllHandlesVisible, const bool bAllowRotationAndScaleHandles, UActorComponent* DraggingHandle);` — Default setting the visibility and collision for all the handles in this group
- L67 _public prototype_ `class UViewportDragOperationComponent* GetDragOperationComponent();`
- L70 _public prototype_ `virtual int32 GetDraggedHandleIndex( class UStaticMeshComponent* DraggedMesh );` — Finds the index of DraggedMesh in HandleMeshes
- L73 _public prototype_ `void SetGizmoMaterial( UMaterialInterface* Material );` — Sets the Gizmo material
- L76 _public prototype_ `void SetTranslucentGizmoMaterial( UMaterialInterface* Material );` — Sets the translucent Gizmo material
- L79 _public prototype_ `TArray< FGizmoHandle >& GetHandles();` — Gets all the handles
- L82 _public prototype_ `virtual EGizmoHandleTypes GetHandleType() const;` — Gets the GizmoType for this Gizmo handle
- L85 _public function_ `virtual bool SupportsWorldCoordinateSpace() const` — Returns true if this type of handle is allowed with world space gizmos
- L91 _public prototype_ `void SetShowOnUniversalGizmo( const bool bShowHandleUniversal );` — Sets if this handlegroup will be visible with the universal gizmo
- L94 _public prototype_ `bool GetShowOnUniversalGizmo() const;` — Gets if this handlegroup will be visible with the universal gizmo
- L97 _public prototype_ `void SetOwningTransformGizmo(class ABaseTransformGizmo* TransformGizmo);` — Sets the owning transform gizmo for this handle group
- L101 _protected prototype_ `void UpdateHandleColor( const int32 AxisIndex, FGizmoHandle& Handle, class UActorComponent* DraggingHandle, const TArray< UActorComponent* >& HoveringOverHandles );` — Updates the colors of the dynamic material instances for the handle passed using its axis index
- L104 _protected prototype_ `class UGizmoHandleMeshComponent* CreateMeshHandle( class UStaticMesh* HandleMesh, const FString& ComponentName );` — Helper function to create gizmo handle meshes
- L107 _protected prototype_ `class UGizmoHandleMeshComponent* CreateAndAddMeshHandle( class UStaticMesh* HandleMesh, const FString& ComponentName, const FTransformGizmoHandlePlacement& HandlePlacement );` — Creates handle meshcomponent and adds it to the Handles list
- L110 _protected prototype_ `void AddMeshToHandles( class UGizmoHandleMeshComponent* HandleMeshComponent, const FTransformGizmoHandlePlacement& HandlePlacement );` — Adds the HandleMeshComponent to the Handles list
- L113 _protected prototype_ `FTransformGizmoHandlePlacement GetHandlePlacement( const int32 X, const int32 Y, const int32 Z ) const;` — Gets the handleplacement axes
- L117 _protected member_ `TObjectPtr<UMaterialInterface> GizmoMaterial;` — `UPROPERTY()` — Gizmo material (opaque)
- L121 _protected member_ `TObjectPtr<UMaterialInterface> TranslucentGizmoMaterial;` — `UPROPERTY()` — Gizmo material (translucent)
- L125 _protected member_ `TArray< FGizmoHandle > Handles;` — `UPROPERTY()` — All the StaticMeshes for this handle type
- L129 _protected member_ `TObjectPtr<class ABaseTransformGizmo> OwningTransformGizmoActor;` — `UPROPERTY()` — The actor transform gizmo owning this handlegroup
- L132 _protected member_ `TObjectPtr<class UViewportDragOperationComponent> DragOperationComponent;` — `UPROPERTY()`
- L137 _private prototype_ `void UpdateHoverAnimation( class UActorComponent* DraggingHandle, const TArray< UActorComponent* >& HoveringOverHandles, const float GizmoHoverAnimationDuration, bool& bOutIsHoveringOrDraggingThisHandleGroup );` — Updates the hover animation for the HoveringOverHandles
- L140 _private member_ `bool bShowOnUniversalGizmo;` — If this handlegroup will be visible with the universal gizmo

#### class `UAxisGizmoHandleGroup`  
`class UE_DEPRECATED(5.7, "The ViewportInteraction module is being deprecated alongside VR Editor mode.") UAxisGizmoHandleGroup : public UGizmoHandleGroup`  
_L148-163_
- reflection: `UCLASS(MinimalAPI, ABSTRACT)`
- inherits: `UGizmoHandleGroup`
- desc: Base class for gizmo handles on axis
- L155 _protected prototype_ `void CreateHandles(UStaticMesh* HandleMesh, const FString& HandleComponentName);` — Creates mesh for every axis
- L161 _protected prototype_ `void UpdateHandlesRelativeTransformOnAxis( const FTransform& HandleToCenter, const float AnimationAlpha, const float GizmoScale, const float GizmoHoverScale, const FVector& ViewLocation, class UActorComponent* DraggingHandle, const TArray< UActorComponent* >& HoveringOverHandles );` — Calculates the transforms of meshes of this handlegroup @param HandleToCenter - The offset from the center of the gizmo in roomspace

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API VIEWPORTINTERACTION_API`

### `Source/Editor/ViewportInteraction/Public/VIGizmoHandleMeshComponent.h` (Public)


#### class `UGizmoHandleMeshComponent`  
`class UE_DEPRECATED(5.7, "The ViewportInteraction module is being deprecated alongside VR Editor mode.") UGizmoHandleMeshComponent : public UStaticMeshComponent`  
_L10-22_
- reflection: `UCLASS(hidecategories = Object)`
- inherits: `UStaticMeshComponent`
- L17 _public prototype_ `UGizmoHandleMeshComponent();` — Default constructor
- L20 _public prototype_ `virtual class FPrimitiveSceneProxy* CreateSceneProxy() override;`

### `Source/Editor/ViewportInteraction/Public/VISettings.h` (Public)


#### class `UVISettings`  
`class UE_DEPRECATED(5.7, "The ViewportInteraction module is being deprecated alongside VR Editor mode.") UVISettings : public UObject`  
_L14-40_
- reflection: `UCLASS(MinimalAPI, config = EditorSettings)`
- inherits: `UObject`
- desc: Implements the settings for Viewport Interaction and VR Mode. Note that this is primarily a base class for anything that needs to be accessed in the VI module.
- L21 _public function_ `UVISettings() : Super()` — Default constructor that sets up CDO properties
- L29 _public member_ `uint32 bScaleWorldFromFloor : 1;` — `UE_DEPRECATED(5.7, "The ViewportInteraction module is being deprecated alongside VR Editor mode.")` — `UPROPERTY(config)` — Whether the world should scale relative to your tracking space floor instead of the center of your hand locations
- L34 _public member_ `uint32 bScaleWorldWithDynamicPivot : 1;` — `UE_DEPRECATED(5.7, "The ViewportInteraction module is being deprecated alongside VR Editor mode.")` — `UPROPERTY(config)` — Whether to compute a new center point for scaling relative from by looking at how far either controller moved relative to the last frame
- L39 _public member_ `uint32 bAllowSimultaneousWorldScalingAndRotation : 1;` — `UE_DEPRECATED(5.7, "The ViewportInteraction module is being deprecated alongside VR Editor mode.")` — `UPROPERTY(config)` — When enabled, you can freely rotate and scale the world with two hands at the same time.  Otherwise, we'll detect whether to rotate or scale depending on how much of either gesture you initially perform.

### `Source/Editor/ViewportInteraction/Public/ViewportDragOperation.h` (Public)


#### class `UViewportDragOperation`  
`class UE_DEPRECATED(5.7, "The ViewportInteraction module is being deprecated alongside VR Editor mode.") UViewportDragOperation : public UObject`  
_L32-56_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Base class for interactable drag calculations
- L44 _public function_ `virtual void ExecuteDrag(class UViewportInteractor* Interactor, class IViewportInteractableInterface* Interactable)` — Execute dragging @param UViewportInteractor - The interactor causing the dragging @param IViewportInteractableInterface - The interactable owning this drag operation
- L52 _public function_ `virtual void ExecuteDrag(struct FDraggingTransformableData& DraggingData)` — Execute dragging @param UViewportInteractor - The interactor causing the dragging @param IViewportInteractableInterface - The interactable owning this drag operation
- L55 _public member_ `bool bPlaneConstraint;` — @todo ViewportInteraction: Temporary way to check if a drag operation needs to constrain the drag delta on a plane of a gizmo axis.

#### class `UViewportDragOperationComponent`  
`class UE_DEPRECATED(5.7, "The ViewportInteraction module is being deprecated alongside VR Editor mode.") UViewportDragOperationComponent : public UActorComponent`  
_L63-96_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UActorComponent`
- desc: Container component for UViewportDragOperation that can be used by objects in the world that are draggable and implement the ViewportInteractableInterface
- L70 _public prototype_ `UViewportDragOperationComponent();` — Default constructor.
- L73 _public prototype_ `UViewportDragOperation* GetDragOperation();` — Get the actual dragging operation
- L76 _public prototype_ `void SetDragOperationClass( const TSubclassOf<UViewportDragOperation> InDragOperation );` — Sets the drag operation class that will be used next time starting dragging
- L79 _public prototype_ `void StartDragOperation();` — Starts new dragging operation
- L82 _public prototype_ `void ClearDragOperation();` — Destroys the dragoperation
- L85 _public prototype_ `bool IsDragging() const;` — If this operation is currently active.
- L91 _private member_ `TObjectPtr<UViewportDragOperation> DragOperation;` — `UPROPERTY()` — The actual dragging implementation
- L95 _private member_ `TSubclassOf<UViewportDragOperation> DragOperationSubclass;` — `UPROPERTY()` — The next class that will be used as drag operation

#### struct `FDraggingTransformableData`  
`struct UE_DEPRECATED(5.7, "The ViewportInteraction module is being deprecated alongside VR Editor mode.") FDraggingTransformableData`  
_L102-161_
- reflection: `USTRUCT()`
- desc: Data structure that holds all arguments that can be used while dragging a transformable.
- L106 _public function_ `FDraggingTransformableData() : Interactor(nullptr), WorldInteraction(nullptr), PassDraggedTo(FVector::ZeroVector), OptionalHandlePlacement(), DragDelta(FVector::ZeroVector), ConstrainedDragDelta(FVector::ZeroVector), OtherHandDragDelta(FVector::ZeroVector), DraggedTo(FVector::ZeroVector), OtherHandDraggedTo(FVector::ZeroVector), DragDeltaFromStart(FVector::ZeroVector), OtherHandDragDeltaFromStart(FVector::ZeroVector), LaserPointerStart(FVector::ZeroVector), LaserPointerDirection(FVector::ZeroVector), GizmoStartTransform(FTransform::Identity), GizmoLastTransform(FTransform::Identity), OutGizmoUnsnappedTargetTransform(FTransform::Identity), GizmoStartLocalBounds(ForceInitToZero), GizmoCoordinateSpace(ECoordSystem::COORD_World), bOutMovedTransformGizmo(false), bOutShouldApplyVelocitiesFromDrag(false), OutUnsnappedDraggedTo(FVector::ZeroVector), bOutTranslated(false), bOutRotated(false), bOutScaled(false), bAllowSnap(true)`
- L134 _public member_ `class UViewportInteractor* Interactor;`
- L135 _public member_ `class UViewportWorldInteraction* WorldInteraction;`
- L137 _public member_ `FVector PassDraggedTo;`
- L138 _public member_ `TOptional<FTransformGizmoHandlePlacement> OptionalHandlePlacement;`
- L139 _public member_ `FVector DragDelta;`
- L140 _public member_ `FVector ConstrainedDragDelta;`
- L141 _public member_ `FVector OtherHandDragDelta;`
- L142 _public member_ `FVector DraggedTo;`
- L143 _public member_ `FVector OtherHandDraggedTo;`
- L144 _public member_ `FVector DragDeltaFromStart;`
- L145 _public member_ `FVector OtherHandDragDeltaFromStart;`
- L146 _public member_ `FVector LaserPointerStart;`
- L147 _public member_ `FVector LaserPointerDirection;`
- L148 _public member_ `FTransform GizmoStartTransform;`
- L149 _public member_ `FTransform GizmoLastTransform;`
- L150 _public member_ `FTransform OutGizmoUnsnappedTargetTransform;`
- L151 _public member_ `FBox GizmoStartLocalBounds;`
- L152 _public member_ `ECoordSystem GizmoCoordinateSpace;`
- L154 _public member_ `bool bOutMovedTransformGizmo;`
- L155 _public member_ `bool bOutShouldApplyVelocitiesFromDrag;`
- L156 _public member_ `FVector OutUnsnappedDraggedTo;`
- L157 _public member_ `bool bOutTranslated;`
- L158 _public member_ `bool bOutRotated;`
- L159 _public member_ `bool bOutScaled;`
- L160 _public member_ `bool bAllowSnap;`

#### Free symbols / members of external scopes

- L23 _macro_ `#define UE_API VIEWPORTINTERACTION_API`

### `Source/Editor/ViewportInteraction/Public/ViewportInteractableInterface.h` (Public)


#### class `UViewportInteractableInterface`  
`UViewportInteractableInterface : public UInterface`  
_L28-31_
- inherits: `UInterface`

#### class `IViewportInteractableInterface`  
`IViewportInteractableInterface`  
_L40-66_
- L47 _public prototype_ `virtual void OnPressed( UViewportInteractor* Interactor, const FHitResult& InHitResult, bool& bOutResultedInDrag ) PURE_VIRTUAL( IViewportInteractableInterface::OnPressed, );` — Called when an interactor presses this object
- L50 _public prototype_ `virtual void OnHover( UViewportInteractor* Interactor ) PURE_VIRTUAL( IViewportInteractableInterface::OnHover, );` — Called when an interactor hover over this object
- L53 _public prototype_ `virtual void OnHoverEnter( UViewportInteractor* Interactor, const FHitResult& InHitResult ) PURE_VIRTUAL( IViewportInteractableInterface::OnHoverEnter, );` — Called when an interactor starts hovering over this object
- L56 _public prototype_ `virtual void OnHoverLeave( UViewportInteractor* Interactor, const UActorComponent* NewComponent ) PURE_VIRTUAL( IViewportInteractableInterface::OnHoverLeave, );` — Called when an interactor leave hovering over this object
- L59 _public prototype_ `virtual void OnDragRelease( UViewportInteractor* Interactor ) PURE_VIRTUAL( IViewportInteractableInterface::OnDragRelease, );` — Called when an interactor stops dragging this object
- L62 _public prototype_ `virtual class UViewportDragOperationComponent* GetDragOperationComponent() PURE_VIRTUAL( IViewportInteractableInterface::GetDragOperationComponent, return nullptr; );` — Get dragging operation
- L65 _public prototype_ `virtual bool CanBeSelected() PURE_VIRTUAL( IViewportInteractableInterface::CanBeSelected, return false; );` — Whether this interactable can be selected.

### `Source/Editor/ViewportInteraction/Public/ViewportInteraction.h` (Public)
_(no declarations extracted)_

### `Source/Editor/ViewportInteraction/Public/ViewportInteractionAssetContainer.h` (Public)


#### class `UViewportInteractionAssetContainer`  
`class UE_DEPRECATED(5.7, "The ViewportInteraction module is being deprecated alongside VR Editor mode.") UViewportInteractionAssetContainer : public UDataAsset`  
_L17-100_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDataAsset`
- desc: Asset container for viewport interaction.
- L28 _public member_ `TObjectPtr<USoundBase> GizmoHandleSelectedSound;` — `UPROPERTY(EditAnywhere, Category = Sound)`
- L31 _public member_ `TObjectPtr<USoundBase> GizmoHandleDropSound;` — `UPROPERTY(EditAnywhere, Category = Sound)`
- L34 _public member_ `TObjectPtr<USoundBase> SelectionChangeSound;` — `UPROPERTY(EditAnywhere, Category = Sound)`
- L37 _public member_ `TObjectPtr<USoundBase> SelectionDropSound;` — `UPROPERTY(EditAnywhere, Category = Sound)`
- L40 _public member_ `TObjectPtr<USoundBase> SelectionStartDragSound;` — `UPROPERTY(EditAnywhere, Category = Sound)`
- L43 _public member_ `TObjectPtr<USoundBase> GridSnapSound;` — `UPROPERTY(EditAnywhere, Category = Sound)`
- L46 _public member_ `TObjectPtr<USoundBase> ActorSnapSound;` — `UPROPERTY(EditAnywhere, Category = Sound)`
- L49 _public member_ `TObjectPtr<USoundBase> UndoSound;` — `UPROPERTY(EditAnywhere, Category = Sound)`
- L52 _public member_ `TObjectPtr<USoundBase> RedoSound;` — `UPROPERTY(EditAnywhere, Category = Sound)`
- L59 _public member_ `TObjectPtr<UStaticMesh> GridMesh;` — `UPROPERTY(EditAnywhere, Category = Mesh)`
- L62 _public member_ `TObjectPtr<UStaticMesh> TranslationHandleMesh;` — `UPROPERTY(EditAnywhere, Category = Mesh)`
- L65 _public member_ `TObjectPtr<UStaticMesh> UniformScaleHandleMesh;` — `UPROPERTY(EditAnywhere, Category = Mesh)`
- L68 _public member_ `TObjectPtr<UStaticMesh> ScaleHandleMesh;` — `UPROPERTY(EditAnywhere, Category = Mesh)`
- L71 _public member_ `TObjectPtr<UStaticMesh> PlaneTranslationHandleMesh;` — `UPROPERTY(EditAnywhere, Category = Mesh)`
- L74 _public member_ `TObjectPtr<UStaticMesh> RotationHandleMesh;` — `UPROPERTY(EditAnywhere, Category = Mesh)`
- L77 _public member_ `TObjectPtr<UStaticMesh> RotationHandleSelectedMesh;` — `UPROPERTY(EditAnywhere, Category = Mesh)`
- L80 _public member_ `TObjectPtr<UStaticMesh> StartRotationIndicatorMesh;` — `UPROPERTY(EditAnywhere, Category = Mesh)`
- L83 _public member_ `TObjectPtr<UStaticMesh> CurrentRotationIndicatorMesh;` — `UPROPERTY(EditAnywhere, Category = Mesh)`
- L86 _public member_ `TObjectPtr<UStaticMesh> FreeRotationHandleMesh;` — `UPROPERTY(EditAnywhere, Category = Mesh)`
- L93 _public member_ `TObjectPtr<UMaterialInterface> GridMaterial;` — `UPROPERTY(EditAnywhere, Category = Material)`
- L96 _public member_ `TObjectPtr<UMaterialInterface> TransformGizmoMaterial;` — `UPROPERTY(EditAnywhere, Category = Material)`
- L99 _public member_ `TObjectPtr<UMaterialInterface> TranslucentTransformGizmoMaterial;` — `UPROPERTY(EditAnywhere, Category = Material)`

### `Source/Editor/ViewportInteraction/Public/ViewportInteractionDragOperations.h` (Public)


#### class `UTranslationDragOperation`  
`class UE_DEPRECATED(5.7, "The ViewportInteraction module is being deprecated alongside VR Editor mode.") UTranslationDragOperation : public UViewportDragOperation`  
_L20-26_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UViewportDragOperation`
- desc: Gizmo translation on one axis.
- L25 _public prototype_ `virtual void ExecuteDrag(struct FDraggingTransformableData& DraggingData) override;`

#### class `UPlaneTranslationDragOperation`  
`class UE_DEPRECATED(5.7, "The ViewportInteraction module is being deprecated alongside VR Editor mode.") UPlaneTranslationDragOperation : public UViewportDragOperation`  
_L32-39_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UViewportDragOperation`
- desc: Gizmo translation on two axes.
- L37 _public prototype_ `UPlaneTranslationDragOperation();`
- L38 _public prototype_ `virtual void ExecuteDrag(struct FDraggingTransformableData& DraggingData) override;`

#### class `URotateOnAngleDragOperation`  
`class UE_DEPRECATED(5.7, "The ViewportInteraction module is being deprecated alongside VR Editor mode.") URotateOnAngleDragOperation : public UViewportDragOperation`  
_L45-67_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UViewportDragOperation`
- desc: Rotation around one axis based on input angle.
- L50 _public prototype_ `URotateOnAngleDragOperation();`
- L52 _public prototype_ `virtual void ExecuteDrag(struct FDraggingTransformableData& DraggingData) override;`
- L55 _public prototype_ `FVector GetLocalIntersectPointOnRotationGizmo() const;` — When RotateOnAngle we intersect on a plane to rotate the transform gizmo. This is the local point from the transform gizmo location of that intersect
- L60 _private member_ `TOptional<float> StartDragAngleOnRotation;` — Starting angle when rotating an object with  ETransformGizmoInteractionType::RotateOnAngle
- L63 _private member_ `TOptional<FVector> DraggingRotationHandleDirection;` — The direction of where the rotation handle is facing when starting rotation
- L66 _private member_ `FVector LocalIntersectPointOnRotationGizmo;` — Where the laser intersected on the gizmo rotation aligned plane.

#### class `UScaleDragOperation`  
`class UE_DEPRECATED(5.7, "The ViewportInteraction module is being deprecated alongside VR Editor mode.") UScaleDragOperation : public UViewportDragOperation`  
_L73-79_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UViewportDragOperation`
- desc: Scale on one axis.
- L78 _public prototype_ `virtual void ExecuteDrag(struct FDraggingTransformableData& DraggingData) override;`

#### class `UUniformScaleDragOperation`  
`class UE_DEPRECATED(5.7, "The ViewportInteraction module is being deprecated alongside VR Editor mode.") UUniformScaleDragOperation : public UViewportDragOperation`  
_L85-91_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UViewportDragOperation`
- desc: Scale on all axes.
- L90 _public prototype_ `virtual void ExecuteDrag(struct FDraggingTransformableData& DraggingData) override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API VIEWPORTINTERACTION_API`

### `Source/Editor/ViewportInteraction/Public/ViewportInteractionStyle.h` (Public)


#### class `FViewportInteractionStyle`  
`class UE_DEPRECATED(5.7, "The ViewportInteraction module is being deprecated alongside VR Editor mode.") FViewportInteractionStyle`  
_L15-45_
- L19 _public prototype_ `static void Initialize();`
- L21 _public prototype_ `static void Shutdown();`
- L24 _public prototype_ `static void ReloadTextures();` — reloads textures used by slate renderer
- L27 _public prototype_ `static const ISlateStyle& Get();` — @return The Slate style set for the UMG Style
- L29 _public prototype_ `static FName GetStyleSetName();`
- L31 _public function_ `static const FSlateBrush* GetBrush(FName PropertyName, const ANSICHAR* Specifier = NULL)`
- L38 _private prototype_ `static TSharedRef< class FSlateStyleSet > Create();`
- L42 _private member_ `static TSharedPtr< class FSlateStyleSet > ViewportInteractionStyleInstance;`

### `Source/Editor/ViewportInteraction/Public/ViewportInteractionTypes.h` (Public)


#### struct `FViewportActionKeyInput`  
`struct UE_DEPRECATED(5.7, "The ViewportInteraction module is being deprecated alongside VR Editor mode.") FViewportActionKeyInput`  
_L19-76_
- reflection: `USTRUCT(BlueprintType)`
- desc: Represents a generic action
- L23 _public function_ `FViewportActionKeyInput() : ActionType( NAME_None ) , Event( IE_Pressed ) , bIsInputCaptured( false ) , bIsAxis( false )`
- L30 _public function_ `FViewportActionKeyInput( const FName& InActionType ) : ActionType( InActionType ) , Event( IE_Pressed ) , bIsInputCaptured( false ) , bIsAxis( false )`
- L37 _public function_ `static FViewportActionKeyInput Axis(const FName& InActionType)`
- L46 _public member_ `FName ActionType;` — `UPROPERTY(BlueprintReadOnly, Category = Action)` — The name of this action
- L50 _public member_ `TEnumAsByte<EInputEvent> Event;` — `UPROPERTY(BlueprintReadOnly, Category = Action)` — Input event
- L55 _public member_ `bool bIsInputCaptured;` — `UPROPERTY()` — True if this action owned by an interactor is "captured" for each possible action type, meaning that only the active captor should handle input events until it is no longer captured.  It's the captors responsibility to set this using OnVRAction(), or clear it when finished with capturing.
- L58 _public member_ `bool bIsAxis;` — `UPROPERTY()`
- L60 _public function_ `bool operator==(const FViewportActionKeyInput& Other) const`

#### enum `EViewportInteractionDraggingMode`  
`enum class UE_DEPRECATED(5.7, "The ViewportInteraction module is being deprecated alongside VR Editor mode.") EViewportInteractionDraggingMode : uint8`  
_L81-106_
- reflection: `UENUM()`
- desc: Methods of dragging objects around in VR
- L84 _public enumerator_ `Nothing` — Not dragging right now with this hand
- L87 _public enumerator_ `TransformablesWithGizmo` — Dragging transformables (e.g. actors, components, geometry elements) around using the transform gizmo
- L90 _public enumerator_ `TransformablesAtLaserImpact` — Transformables locked to the impact point under the laser
- L93 _public enumerator_ `AssistingDrag` — We're grabbing an object (or the world) that was already grabbed by the other hand
- L96 _public enumerator_ `TransformablesFreely` — Freely moving, rotating and scaling transformables with one or two hands
- L99 _public enumerator_ `World` — Moving the world itself around (actually, moving the camera in such a way that it feels like you're moving the world)
- L102 _public enumerator_ `Interactable` — Moving a custom interactable
- L105 _public enumerator_ `Material` — Dragging a material

#### enum `ETransformGizmoHandleDirection`  
`enum class UE_DEPRECATED(5.7, "The ViewportInteraction module is being deprecated alongside VR Editor mode.") ETransformGizmoHandleDirection`  
_L109-114_
- desc: Directions that a transform handle can face along any given axis
- L111 _public enumerator_ `Negative`
- L112 _public enumerator_ `Center`
- L113 _public enumerator_ `Positive`

#### struct `FTransformGizmoHandlePlacement`  
`struct UE_DEPRECATED(5.7, "The ViewportInteraction module is being deprecated alongside VR Editor mode.") FTransformGizmoHandlePlacement`  
_L119-133_
- reflection: `USTRUCT()`
- desc: Placement of a handle in pivot space
- L124 _public member_ `ETransformGizmoHandleDirection Axes[ 3 ];` — Handle direction in X, Y and Z
- L132 _public prototype_ `void GetCenterHandleCountAndFacingAxisIndex( int32& OutCenterHandleCount, int32& OutFacingAxisIndex, int32& OutCenterAxisIndex ) const;` — Finds the center handle count and facing axis index.  The center handle count is simply the number of axes where the handle would be centered on the bounds along that axis.  The facing axis index is the index (0-2) of the axis where the handle would be facing, or INDEX_NONE for corners or edges. The center axis index is valid for edges, and defines the axis perpendicular to that edge direction, or INDEX_NONE if it's not an edge

#### enum `ELockedWorldDragMode`  
`enum class UE_DEPRECATED(5.7, "The ViewportInteraction module is being deprecated alongside VR Editor mode.") ELockedWorldDragMode`  
_L136-141_
- L138 _public enumerator_ `Unlocked`
- L139 _public enumerator_ `OnlyRotating`
- L140 _public enumerator_ `OnlyScaling`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API VIEWPORTINTERACTION_API`
- L68 _function_ `friend uint32 GetTypeHash(const FViewportActionKeyInput& Input)`

### `Source/Editor/ViewportInteraction/Public/ViewportInteractionUtils.h` (Public)


#### class `ViewportInteractionUtils::FOneEuroFilter`  
`class FOneEuroFilter`  
_L17-76_
- desc: /
- L49 _public prototype_ `FOneEuroFilter();` — Default constructor
- L51 _public prototype_ `FOneEuroFilter(const double InMinCutoff, const double InCutoffSlope, const double InDeltaCutoff);`
- L54 _public prototype_ `FVector Filter(const FVector& InRaw, const double InDeltaTime);` — Smooth vector
- L57 _public prototype_ `void SetMinCutoff(const double InMinCutoff);` — Set the minimum cutoff
- L60 _public prototype_ `void SetCutoffSlope(const double InCutoffSlope);` — Set the cutoff slope
- L63 _public prototype_ `void SetDeltaCutoff(const double InDeltaCutoff);` — Set the delta slope
- L67 _private prototype_ `const FVector CalculateCutoff(const FVector& InValue);`
- L68 _private prototype_ `const FVector CalculateAlpha(const FVector& InCutoff, const double InDeltaTime) const;`
- L69 _private prototype_ `const double CalculateAlpha(const double InCutoff, const double InDeltaTime) const;`
- L71 _private member_ `double MinCutoff;`
- L72 _private member_ `double CutoffSlope;`
- L73 _private member_ `double DeltaCutoff;`
- L74 _private member_ `FLowpassFilter RawFilter;`
- L75 _private member_ `FLowpassFilter DeltaFilter;`

#### class `ViewportInteractionUtils::FOneEuroFilter::FLowpassFilter`  
`class FLowpassFilter`  
_L21-44_
- L26 _public prototype_ `FLowpassFilter();` — Default constructor
- L29 _public prototype_ `FVector Filter(const FVector& InValue, const FVector& InAlpha);` — Calculate
- L32 _public prototype_ `bool IsFirstTime() const;` — If the filter was not executed yet
- L35 _public prototype_ `FVector GetPrevious() const;` — Get the previous filtered value
- L40 _private member_ `FVector Previous;` — The previous filtered value
- L43 _private member_ `bool bFirstTime;` — If this is the first time doing a filter

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API VIEWPORTINTERACTION_API`
- L11 _namespace_ `namespace ViewportInteractionUtils`

### `Source/Editor/ViewportInteraction/Public/ViewportInteractor.h` (Public)


#### enum `EHitResultGizmoFilterMode`  
`enum class UE_DEPRECATED(5.7, "The ViewportInteraction module is being deprecated alongside VR Editor mode.") EHitResultGizmoFilterMode : uint8`  
_L24-29_
- reflection: `UENUM(BlueprintType)`
- desc: Filter mode for GetHitResultFromLaserPointer
- L26 _public enumerator_ `All`
- L27 _public enumerator_ `NoGizmos`
- L28 _public enumerator_ `GizmosOnly`

#### class `UViewportInteractor`  
`class UE_DEPRECATED(5.7, "The ViewportInteraction module is being deprecated alongside VR Editor mode.") UViewportInteractor : public UObject`  
_L35-332_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable, BlueprintType)`
- inherits: `UObject`
- desc: Represents the interactor in the world
- L42 _public prototype_ `UViewportInteractor();` — Default constructor
- L45 _public prototype_ `struct FViewportInteractorData& GetInteractorData();` — Gets the private data for this interactor
- L48 _public prototype_ `const struct FViewportInteractorData& GetInteractorData() const;` — Gets the private data for this interactor (const)
- L51 _public prototype_ `void SetWorldInteraction( class UViewportWorldInteraction* InWorldInteraction );` — Sets the world interaction
- L55 _public prototype_ `UViewportWorldInteraction* GetWorldInteraction() const;` — `UFUNCTION(BlueprintCallable, Category = "Interactor")` — Gets the world interaction
- L58 _public prototype_ `void SetOtherInteractor( UViewportInteractor* InOtherInteractor );` — Sets the other interactor
- L61 _public prototype_ `void RemoveOtherInteractor();` — Removes the other interactor reference for this interactor
- L65 _public prototype_ `UViewportInteractor* GetOtherInteractor() const;` — `UFUNCTION(BlueprintCallable, Category = "Interactor")` — Gets the paired interactor assigned by the world interaction, can return null when there is no other interactor
- L69 _public prototype_ `void Shutdown();` — `UFUNCTION(BlueprintNativeEvent, CallInEditor, Category = "Interactor")` — Whenever the ViewportWorldInteraction is shut down, the interacts will shut down as well
- L73 _public prototype_ `void Tick( const float DeltaTime );` — `UFUNCTION(BlueprintNativeEvent, CallInEditor, Category = "Interactor")` — Update for this interactor called by the ViewportWorldInteraction
- L76 _public prototype_ `virtual class UActorComponent* GetLastHoverComponent();` — Gets the last component hovered on by the interactor laser.
- L79 _public prototype_ `void AddKeyAction( const FKey& Key, const FViewportActionKeyInput& Action );` — Adds a new action to the KeyToActionMap
- L82 _public prototype_ `void RemoveKeyAction( const FKey& Key );` — Removes an action from the KeyToActionMap
- L85 _public function_ `virtual void PollInput()` — Base classes need to implement getting the input for the input devices for that interactor
- L93 _public prototype_ `bool HandleInputKey( class FEditorViewportClient& ViewportClient, const FKey Key, const EInputEvent Event );` — Handles key input and translates it actions C++ Child classes are expected to to call there super versions of this. BP will have there "Receive" versions called from within these function and do not have to call there parents.  They simply need to return if they handled the input or not.
- L101 _public prototype_ `bool HandleInputAxis( class FEditorViewportClient& ViewportClient, const FKey Key, const float Delta, const float DeltaTime );` — Handles axis input and translates it to actions C++ Child classes are expected to to call there super versions of this. BP will have there "Receive" versions called from within these function and do not have to call there parents.They simply need to return if they handled the input or not.
- L104 _public function_ `virtual bool IsModifierPressed() const` — @return	Returns true if this interactor's designated 'modifier button' is currently held down.  Some interactors may not support this
- L111 _public prototype_ `FTransform GetTransform() const;` — `UFUNCTION(BlueprintCallable, Category = "Interactor")` — Gets the world transform of this interactor
- L115 _public prototype_ `FTransform GetRoomSpaceTransform() const;` — `UFUNCTION(BlueprintCallable, Category = "Interactor")` — Gets the hand transform of the interactor, in the local tracking space
- L119 _public prototype_ `FTransform GetLastTransform() const;` — `UFUNCTION(BlueprintCallable, Category = "Interactor")` — Gets the last world transform of this interactor
- L123 _public prototype_ `FTransform GetLastRoomSpaceTransform() const;` — `UFUNCTION(BlueprintCallable, Category = "Interactor")` — Gets the last hand transform of the interactor, in the local tracking space
- L127 _public prototype_ `EViewportInteractionDraggingMode GetDraggingMode() const;` — `UFUNCTION(BlueprintCallable, Category = "Interactor")` — Gets the current interactor data dragging mode
- L130 _public prototype_ `EViewportInteractionDraggingMode GetLastDraggingMode() const;` — Gets the interactor data previous dragging mode
- L133 _public prototype_ `FVector GetDragTranslationVelocity() const;` — Gets the interactor data drag velocity
- L136 _public prototype_ `void SetHoverLocation(const FVector& InHoverLocation);` — Sets the hover location
- L149 _public prototype_ `bool GetLaserPointer( FVector& LaserPointerStart, FVector& LaserPointerEnd, const bool bEvenIfBlocked = false, const float LaserLengthOverride = 0.0f );` — `UFUNCTION(BlueprintCallable, Category = "Interactor")` — Gets the start and end point of the laser pointer for the specified hand @param LasertPointerStart	(Out) The start location of the laser pointer in world space @param LasertPointerEnd		(Out) The end location of the laser pointer in world space @param bEvenIfBlocked		If true, returns a laser pointer even if the hand has UI in front of it (defaults to false) @param LaserLengthOverride	If zero the default laser length (VREdMode::GetLaserLength) is used @return	True if we have motion controller data for this hand and could return a valid result
- L159 _public prototype_ `bool GetGrabberSphere( FSphere& OutGrabberSphere, const bool bEvenIfBlocked = false );` — Gets a sphere on this interactor that can be used to interact with objects in close proximity @param	OutGrabberSphere	The sphere in world space @param	bEvenIfBlocked	When set to true, a valid sphere may be returned even if there is UI attached in front of this interactor @return	True if the sphere is available and valid, or false is the interactor was busy or we could not determine a valid position for the interactor
- L162 _public prototype_ `float GetLaserPointerMaxLength() const;` — Gets the maximum length of a laser pointer
- L165 _public function_ `virtual void PlayHapticEffect( const float Strength )` — Triggers a force feedback effect on device if possible
- L179 _public function_ `virtual FHitResult GetHitResultFromLaserPointer(TArray<AActor*>* OptionalListOfIgnoredActors, const bool bIgnoreGizmos = false, TArray<UClass*>* ObjectsInFrontOfGizmo = nullptr, const bool bEvenIfBlocked = false, const float LaserLengthOverride = 0.0f)` — `UE_DEPRECATED(4.23, "bool bIgnoreGizmos replaced with EHitResultGizmoFilterMode GizmoFilterMode")` — Traces along the laser pointer vector and returns what it first hits in the world @param OptionalListOfIgnoredActors Actors to exclude from hit testing @param bIgnoreGizmos True if no gizmo results should be returned, otherwise they are preferred (x-ray) @param bEvenIfUIIsInFront If true, ignores any UI that might be blocking the ray @param LaserLengthOverride If zero the default laser length (VREdMode::GetLaserLength) is used @return What the laster pointer hit @deprecated bool bIgnoreGizmos replaced with EHitResultGizmoFilterMode GizmoFilterMode
- L194 _public prototype_ `virtual FHitResult GetHitResultFromLaserPointer( TArray<AActor*>* OptionalListOfIgnoredActors = nullptr, const EHitResultGizmoFilterMode GizmoFilterMode = EHitResultGizmoFilterMode::All, TArray<UClass*>* ObjectsInFrontOfGizmo = nullptr, const bool bEvenIfBlocked = false, const float LaserLengthOverride = 0.0f );` — Traces along the laser pointer vector and returns what it first hits in the world @param OptionalListOfIgnoredActors Actors to exclude from hit testing @param GizmoFilterMode filters the types of gizmos for the hit test @param bEvenIfUIIsInFront If true, ignores any UI that might be blocking the ray @param LaserLengthOverride If zero the default laser length (VREdMode::GetLaserLength) is used @return What the laster pointer hit
- L197 _public prototype_ `virtual void ResetHoverState();` — Reset the values before checking the hover actions
- L200 _public function_ `virtual void CalculateDragRay( double& InOutDragRayLength, double& InOutDragRayVelocity )` — Needs to be implemented by the base to calculate drag ray length and the velocity for the ray
- L203 _public function_ `virtual void CalculateDragRay( float& InOutDragRayLength, float& InOutDragRayVelocity )` — `UE_DEPRECATED(5.2, "CalculateDragRay() now uses double-precision arguments.")`
- L214 _public prototype_ `virtual bool GetTransformAndForwardVector( FTransform& OutHandTransform, FVector& OutForwardVector ) const;` — `UFUNCTION(BlueprintCallable, Category = "Interactor")` — Creates a hand transform and forward vector for a laser pointer for a given hand @param OutHandTransform	The created hand transform @param OutForwardVector	The forward vector of the hand @return	True if we have motion controller data for this hand and could return a valid result
- L217 _public prototype_ `virtual void OnStartDragging( const FVector& HitLocation, const bool bIsPlacingNewObjects );` — Called by StartDragging in world interaction to give the interactor a chance of acting upon starting a drag operation
- L221 _public prototype_ `FVector GetHoverLocation();` — `UFUNCTION(BlueprintCallable, Category = "Interactor")` — Gets the interactor laser hover location
- L224 _public prototype_ `bool IsHovering() const;` — If the interactor laser is currently hovering
- L228 _public prototype_ `bool IsHoveringOverGizmo() const;` — `UFUNCTION(BlueprintCallable, Category = "Interactor")` — If the interactor laser is currently hovering over a gizmo handle
- L232 _public prototype_ `void SetDraggingMode( const EViewportInteractionDraggingMode NewDraggingMode );` — `UFUNCTION(BlueprintCallable, Category = "Interactor")` — Sets the current dragging mode for this interactor
- L235 _public function_ `virtual bool GetIsLaserBlocked() const` — To be overridden by base class. Called by GetLaserPointer to give the derived interactor a chance to disable the laser. By default it is not blocked
- L239 _public prototype_ `FViewportActionKeyInput* GetActionWithName( const FName InActionName );` — @todo ViewportInteractor: This should be changed to return a const pointer, but we need to fix up some dragging code in WorldInteraction first
- L242 _public prototype_ `float GetDragHapticFeedbackStrength() const;` — Gets the drag haptic feedback strength console variable
- L245 _public prototype_ `bool IsHoveringOverPriorityType() const;` — If this interactor is hovering over a type that has priority from GetHitResultFromLaserPointer
- L248 _public prototype_ `bool IsHoveringOverSelectedActor() const;` — Returns true if currently hovering over selected actor
- L251 _public prototype_ `void ResetLaserEnd();` — Reset the stored laser end location at the end of tick
- L255 _public prototype_ `void SetHitResultGizmoFilterMode(EHitResultGizmoFilterMode newFilter);` — `UFUNCTION(BlueprintCallable, Category = "Interactor")` — Sets the current gizmo filter mode used for Interaction
- L259 _public prototype_ `EHitResultGizmoFilterMode GetHitResultGizmoFilterMode() const;` — `UFUNCTION(BlueprintCallable, Category = "Interactor")` — Gets current gizmo filter mode used for Interaction
- L263 _public prototype_ `void SetCanCarry(const bool bInCanCarry);` — `UFUNCTION(BlueprintCallable, Category = "Interactor")` — Sets if the interactor can carry an object
- L267 _public prototype_ `bool CanCarry() const;` — `UFUNCTION(BlueprintCallable, Category = "Interactor")` — Gets if the interactor can carry an object
- L272 _protected function_ `virtual void PreviewInputKey( class FEditorViewportClient& ViewportClient, FViewportActionKeyInput& Action, const FKey Key, const EInputEvent Event, bool& bOutWasHandled )` — To be overridden. Called by HandleInputKey before delegates and default input implementation
- L275 _protected function_ `virtual void PreviewInputAxis( class FEditorViewportClient& ViewportClient, FViewportActionKeyInput& Action, const FKey Key, const float Delta, const float DeltaTime, bool& bOutWasHandled )` — To be overridden. Called by HandleInputAxis before delegates and default input implementation
- L278 _protected function_ `virtual void HandleInputKey( class FEditorViewportClient& ViewportClient, FViewportActionKeyInput& Action, const FKey Key, const EInputEvent Event, bool& bOutWasHandled )` — To be overridden. Called by HandleInputKey before delegates and default input implementation
- L282 _protected prototype_ `void HandleInputKey_BP( const FViewportActionKeyInput& Action, const FKey Key, const EInputEvent Event, bool& bOutWasHandled);` — `UFUNCTION(BlueprintImplementableEvent, CallInEditor, meta = (DisplayName = "HandleInputKey"), Category = "Interactor")` — To be overridden. Called by HandleInputKey before delegates and default input implementation
- L285 _protected function_ `virtual void HandleInputAxis( class FEditorViewportClient& ViewportClient, FViewportActionKeyInput& Action, const FKey Key, const float Delta, const float DeltaTime, bool& bOutWasHandled )` — To be overridden. Called by HandleInputAxis before delegates and default input implementation
- L289 _protected prototype_ `void HandleInputAxis_BP( const FViewportActionKeyInput& Action, const FKey Key, const float Delta, const float DeltaTime, bool& bOutWasHandled);` — `UFUNCTION(BlueprintImplementableEvent, CallInEditor, meta = (DisplayName = "HandleInputAxis"), Category = "Interactor")` — To be overridden. Called by HandleInputAxis before delegates and default input implementation
- L292 _protected prototype_ `virtual bool AllowLaserSmoothing() const;` — If this interactors allows to smooth the laser. Default is true.
- L297 _protected member_ `FViewportInteractorData InteractorData;` — All the private data for the interactor
- L301 _protected member_ `TMap<FKey, FViewportActionKeyInput> KeyToActionMap;` — `UPROPERTY()` — Mapping of raw keys to actions
- L305 _protected member_ `TObjectPtr<class UViewportWorldInteraction> WorldInteraction;` — `UPROPERTY()` — The owning world interaction
- L309 _protected member_ `TObjectPtr<UViewportInteractor> OtherInteractor;` — `UPROPERTY()` — The paired interactor by the world interaction
- L312 _protected member_ `bool bAllowGrabberSphere;` — True if this interactor supports 'grabber sphere' interaction.  Usually disabled for mouse cursors
- L315 _protected member_ `bool bCanCarry;` — True if this interactor can 'carry' objects in VR, that is, translation and rotation of the interactor is inherited by the object, instead of just translation
- L318 _protected member_ `TOptional<FVector> SavedLaserPointerEnd;` — Store end of the laser pointer. This will be returned when calling GetLaserPointer multiple times a tick
- L321 _protected member_ `TOptional<FHitResult> SavedHitResult;` — Store the last hitresult from the laser, to use that when calling GetHitResultFromLaserPointer multiple times in a tick.
- L324 _protected member_ `TOptional<EHitResultGizmoFilterMode> SavedHitResultFilterMode;` — Store the last hitresult from the laser, to use that when calling GetHitResultFromLaserPointer multiple times in a tick.
- L328 _private member_ `EHitResultGizmoFilterMode CurrentHitResultGizmoFilterMode;`
- L331 _private member_ `ViewportInteractionUtils::FOneEuroFilter SmoothingOneEuroFilter;` — Smoothing filter for laser

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API VIEWPORTINTERACTION_API`

### `Source/Editor/ViewportInteraction/Public/ViewportInteractorData.h` (Public)


#### struct `FViewportInteractorData`  
`struct UE_DEPRECATED(5.7, "The ViewportInteraction module is being deprecated alongside VR Editor mode.") FViewportInteractorData`  
_L16-205_
- desc: Represents a single virtual hand
- L23 _public member_ `FTransform Transform;` — Your hand (laser origin) in the virtual world in world space, usually driven by VR motion controllers
- L26 _public member_ `FTransform RoomSpaceTransform;` — Your hand transform, in the local tracking space (unaffected by world scaling)
- L29 _public member_ `FTransform LastTransform;` — Hand transform in world space from the previous frame
- L32 _public member_ `FTransform LastRoomSpaceTransform;` — Room space hand transform from the previous frame
- L39 _public member_ `TWeakObjectPtr<UWidgetComponent> LastHoveredWidgetComponent;` — The widget component we last hovered over.  This is used to detect when the laser pointer moves over or leaves a widget, and is not reset every frame
- L42 _public member_ `TOptional<FVector> HoverLocation;` — Position the laser pointer impacted an interactive object at (UI, meshes, etc.)
- L45 _public member_ `TWeakObjectPtr<class UActorComponent> LastHoveredActorComponent;` — The current component hovered by the laser pointer of this hand
- L49 _public member_ `FVector LastHoverLocationOverUI;` — The last location that we hovered over UI at in the world.  This is used for dragging and dropping from UI that may have already been closed, such as Content Browser
- L56 _public member_ `TWeakObjectPtr<UActorComponent> ClickingOnComponent;` — True if we're currently holding the 'SelectAndMove' button down after clicking on an actor
- L64 _public member_ `EViewportInteractionDraggingMode DraggingMode;` — What we're currently dragging with this hand, if anything
- L67 _public member_ `EViewportInteractionDraggingMode LastDraggingMode;` — What we were doing last.  Used for inertial movement.
- L70 _public member_ `bool bDraggingWithGrabberSphere;` — True if we're dragging using the grabber sphere, or false if we're using the laser (or world movement)
- L73 _public member_ `bool bIsFirstDragUpdate;` — True if this is the first update since we started dragging
- L76 _public member_ `bool bWasAssistingDrag;` — True if we were assisting the other hand's drag the last time we did anything.  This is used for inertial movement
- L79 _public member_ `double DragRayLength;` — Length of the ray that's dragging
- L82 _public member_ `FVector LastDragToLocation;` — Location that we dragged to last frame (end point of the ray)
- L85 _public member_ `FTransform InteractorTransformAtDragStart;` — The transform of the interactor when we first started the drag
- L88 _public member_ `FVector GrabberSphereLocationAtDragStart;` — Where the grabber sphere center point was when we first started the drag
- L91 _public member_ `FVector ImpactLocationAtDragStart;` — Grabber sphere or laser pointer impact location at the drag start
- L94 _public member_ `FVector DragTranslationVelocity;` — How fast to move selected objects every frame for inertial translation
- L97 _public member_ `double DragRayLengthVelocity;` — How fast to adjust ray length every frame for inertial ray length changes
- L101 _public member_ `bool bIsDrivingVelocityOfSimulatedTransformables;` — While dragging, true if we're dragging at least one simulated object that we're driving the velocities of.  When this is true, our default inertia system is disabled and we rely on the physics engine to take care of inertia
- L109 _public member_ `FTransform GizmoStartTransform;` — Where the gizmo was placed at the beginning of the current interaction
- L112 _public member_ `FTransform GizmoLastTransform;` — Where the gizmo was last frame.  This is used for interpolation and smooth snapping
- L115 _public member_ `FTransform GizmoTargetTransform;` — Where the gizmo wants to be right now, with snaps applied.
- L118 _public member_ `FTransform GizmoUnsnappedTargetTransform;` — Where the gizmo wants to be right now, if no snaps were applied.  This is used for interpolation and smooth snapping
- L121 _public member_ `FTransform GizmoInterpolationSnapshotTransform;` — A transform that we're interpolating from, toward the target transform.  This is used when placing objects, so they'll smoothly interpolate to their initial location.
- L124 _public member_ `FBox GizmoStartLocalBounds;` — Our gizmo bounds at the start of the interaction, in actor local space.
- L126 _public member_ `ELockedWorldDragMode LockedWorldDragMode;`
- L127 _public member_ `float GizmoScaleSinceDragStarted;`
- L128 _public member_ `float GizmoRotationRadiansSinceDragStarted;`
- L131 _public member_ `FVector GizmoSpaceFirstDragUpdateOffsetAlongAxis;` — For a single axis drag, this is the cached local offset where the laser pointer ray intersected the axis line on the first frame of the drag
- L135 _public member_ `FVector GizmoSpaceDragDeltaFromStartOffset;` — When dragging with an axis/plane constraint applied, this is the difference between the actual "delta from start" and the constrained "delta from start". This is used when the user releases the object and inertia kicks in
- L138 _public member_ `TWeakObjectPtr<class UViewportDragOperationComponent> DragOperationComponent;` — The gizmo interaction we're doing with this hand
- L141 _public member_ `class UViewportDragOperation* LastDragOperation;` — The last drag operation.
- L144 _public member_ `TOptional<FTransformGizmoHandlePlacement> OptionalHandlePlacement;` — Which handle on the gizmo we're interacting with, if any
- L147 _public member_ `TWeakObjectPtr<class USceneComponent> DraggingTransformGizmoComponent;` — The gizmo component we're dragging right now
- L150 _public member_ `TWeakObjectPtr<class USceneComponent> HoveringOverTransformGizmoComponent;` — Gizmo component that we're hovering over, or nullptr if not hovering over any
- L153 _public member_ `TWeakObjectPtr<class USceneComponent> HoverHapticCheckLastHoveredGizmoComponent;` — Gizmo handle that we hovered over last (used only for avoiding spamming of hover haptics!)
- L156 _public member_ `bool bHitResultIsPriorityType;` — If the latest hitresult is hovering over a priority type
- L160 _public member_ `FVector StartHitLocationToTransformableCenter;` — The offset between the hitlocation of the object selected to start dragging and its center. This is used to offset the objects when dragging to the end of the laser
- L163 _public function_ `FViewportInteractorData()` — Default constructor for FVirtualHand that initializes safe defaults

### `Source/Editor/ViewportInteraction/Public/ViewportTransformable.h` (Public)


#### class `FViewportTransformable`  
`class UE_DEPRECATED(5.7, "The ViewportInteraction module is being deprecated alongside VR Editor mode.") FViewportTransformable`  
_L15-77_
- desc: Represents an object that we're actively interacting with, such as a selected actor
- L21 _public function_ `FViewportTransformable() : StartTransform( FTransform::Identity )` — Sets up safe defaults
- L26 _public function_ `virtual ~FViewportTransformable()`
- L31 _public prototype_ `virtual const FTransform GetTransform() const = 0;` — Gets the current transform of this object
- L34 _public prototype_ `virtual void ApplyTransform( const FTransform& NewTransform, const bool bSweep ) = 0;` — Updates the transform of the actual object
- L37 _public prototype_ `virtual FBox BuildBoundingBox( const FTransform& BoundingBoxToWorld ) const = 0;` — Returns the bounding box of this transformable, built in the specified coordinate system
- L41 _public function_ `virtual bool IsUnorientedPoint() const` — Returns true if this transformable is a single, unoriented point in space, thus never supports being rotated or scaled when only a single transformable is selected.
- L47 _public function_ `virtual bool IsPhysicallySimulated() const` — Returns true if this transformable is a physically simulated kinematic object
- L53 _public function_ `virtual bool ShouldBeCarried() const` — Returns true if this transformable should be 'carried' (moved and rotated) when dragged, if possible, instead of only translated
- L59 _public function_ `virtual void SetLinearVelocity( const FVector& NewVelocity )` — For physically simulated objects, sets the new velocity of the object
- L64 _public function_ `virtual FVector GetLinearVelocity() const` — Get the velocity of the object
- L70 _public function_ `virtual void UpdateIgnoredActorList( TArray<class AActor*>& IgnoredActors )` — For actor transformables, this will add it's actor to the incoming list
- L76 _public member_ `FTransform StartTransform;` — The object's world space transform when we started the action

### `Source/Editor/ViewportInteraction/Public/ViewportTransformer.h` (Public)


#### class `UViewportTransformer`  
`class UE_DEPRECATED(5.7, "The ViewportInteraction module is being deprecated alongside VR Editor mode.") UViewportTransformer : public UObject`  
_L18-58_
- reflection: `UCLASS(MinimalAPI, abstract)`
- inherits: `UObject`
- L25 _public prototype_ `virtual void Init( UViewportWorldInteraction* InitViewportWorldInteraction );` — `UFUNCTION()`
- L28 _public prototype_ `virtual void Shutdown();` — `UFUNCTION()`
- L32 _public function_ `virtual bool CanAlignToActors() const` — `UFUNCTION()` — @return If this transformer can be used to align its transformable to actors in the scene
- L39 _public function_ `virtual bool ShouldCenterTransformGizmoPivot() const` — `UFUNCTION()` — @return True if the transform gizmo should be aligned to the center of the bounds of all selected objects with more than one is selected.  Otherwise it will be at the pivot of the last transformable, similar to legacl editor actor selection
- L46 _public function_ `virtual void OnStartDragging(UViewportInteractor* Interactor)` — `UFUNCTION()` — When starting to drag
- L50 _public function_ `virtual void OnStopDragging(UViewportInteractor* Interactor)` — `UFUNCTION()` — When ending drag
- L56 _protected member_ `TObjectPtr<UViewportWorldInteraction> ViewportWorldInteraction;` — `UPROPERTY()` — The viewport world interaction object we're registered with

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API VIEWPORTINTERACTION_API`

### `Source/Editor/ViewportInteraction/Public/ViewportWorldInteraction.h` (Public)


#### enum `EViewportWorldInteractionType`  
`enum class UE_DEPRECATED(5.7, "The ViewportInteraction module is being deprecated alongside VR Editor mode.") EViewportWorldInteractionType : uint8`  
_L45-49_
- reflection: `UENUM()`
- L47 _public enumerator_ `VR = 0`
- L48 _public enumerator_ `Legacy = 1`

#### class `UViewportWorldInteraction`  
`class UE_DEPRECATED(5.7, "The ViewportInteraction module is being deprecated alongside VR Editor mode.") UViewportWorldInteraction : public UEditorWorldExtension`  
_L52-768_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Transient)`
- inherits: `UEditorWorldExtension`
- L58 _public prototype_ `UViewportWorldInteraction();`
- L60 _public prototype_ `virtual void Init() override;` — UEditorExtension overrides
- L61 _public prototype_ `virtual void Shutdown() override;`
- L62 _public prototype_ `virtual void Tick( float DeltaSeconds ) override;`
- L65 _public prototype_ `void InitColors();` — Initialize colors
- L69 _public prototype_ `void AddInteractor( UViewportInteractor* Interactor );` — `UFUNCTION(BlueprintCallable, Category = "ViewportWorldInteraction")` — Adds interactor to the worldinteraction
- L73 _public prototype_ `void RemoveInteractor( UViewportInteractor* Interactor );` — `UFUNCTION(BlueprintCallable, Category = "ViewportWorldInteraction")` — Removes interactor from the worldinteraction and removes the interactor from its paired interactor if any
- L77 _public prototype_ `void AddMouseCursorInteractor();` — Creates an interactor for the mouse cursor.  If one already exists, this will add a reference to it.  Remember to call ReleaseMouseCursorInteractor() when you're done.
- L81 _public prototype_ `void ReleaseMouseCursorInteractor();` — When you're finished with the mouse cursor interactor, call this to release it.  It will be destroyed unless another system is still using it
- L84 _public prototype_ `DECLARE_EVENT_ThreeParams( UViewportWorldInteraction, FOnVIHoverUpdate, class UViewportInteractor* , FVector& , bool& );` — Gets the event for hovering update which is broadcasted for each interactor
- L85 _public function_ `FOnVIHoverUpdate& OnViewportInteractionHoverUpdate()`
- L88 _public prototype_ `DECLARE_EVENT_FiveParams( UViewportWorldInteraction, FOnPreviewInputAction, class FEditorViewportClient& , class UViewportInteractor* , const struct FViewportActionKeyInput& , bool& , bool& );` — Gets the event for previewing input actions.  This allows systems to get a first chance at actions before everything else.
- L89 _public function_ `FOnPreviewInputAction& OnPreviewInputAction()`
- L92 _public prototype_ `DECLARE_EVENT_FiveParams( UViewportWorldInteraction, FOnVIActionHandle, class FEditorViewportClient& , class UViewportInteractor* , const struct FViewportActionKeyInput& , bool& , bool& );` — Gets the event for input actions update which is broadcasted for each interactor
- L93 _public function_ `FOnVIActionHandle& OnViewportInteractionInputAction()`
- L96 _public prototype_ `DECLARE_EVENT_ThreeParams( UViewportWorldInteraction, FOnViewportInteractionInputUnhandled, class FEditorViewportClient& , class UViewportInteractor* , const struct FViewportActionKeyInput& );` — Called when the user clicks on 'nothing' to allow systems to deselect anything that's selected
- L97 _public function_ `FOnViewportInteractionInputUnhandled& OnViewportInteractionInputUnhandled()`
- L100 _public prototype_ `DECLARE_EVENT_FourParams( UViewportWorldInteraction, FOnHandleInputKey, class FEditorViewportClient* , const FKey , const EInputEvent , bool& );` — To handle raw key input from the Input Preprocessor
- L101 _public function_ `FOnHandleInputKey& OnHandleKeyInput()`
- L104 _public prototype_ `DECLARE_EVENT_SixParams( UViewportWorldInteraction, FOnHandleInputAxis, class FEditorViewportClient* , const int32 , const FKey , const float , const float , bool& );` — To handle raw axis input from the Input Preprocessor
- L105 _public function_ `FOnHandleInputAxis& OnHandleAxisInput()`
- L108 _public prototype_ `DECLARE_EVENT_OneParam( UViewportWorldInteraction, FOnStartDragging, class UViewportInteractor* );` — Gets the event for when an interactor starts dragging
- L109 _public function_ `FOnStartDragging& OnStartDragging()`
- L112 _public prototype_ `DECLARE_EVENT_OneParam( UViewportWorldInteraction, FOnStopDragging, class UViewportInteractor* );` — Gets the event for when an interactor stops dragging
- L113 _public function_ `FOnStopDragging& OnStopDragging()`
- L116 _public prototype_ `DECLARE_EVENT( UViewportWorldInteraction, FOnFinishedMovingTransformables );` — Gets the event for when the current set of transformables has finally stop moving (after a drag, and all inertial effects or snapping interpolation has completed
- L117 _public function_ `FOnFinishedMovingTransformables& OnFinishedMovingTransformables()`
- L119 _public prototype_ `DECLARE_EVENT_OneParam( UViewportWorldInteraction, FOnViewportWorldInteractionTick, const float );`
- L120 _public function_ `FOnViewportWorldInteractionTick& OnPreWorldInteractionTick()`
- L121 _public function_ `FOnViewportWorldInteractionTick& OnPostWorldInteractionTick()`
- L125 _public prototype_ `void SetTransformer( class UViewportTransformer* NewTransformer );` — Sets the system that should be used to transform objects in the scene.  Only one can be active at a time.  If you pass nullptr, a default transformer for actors/components will be enabled
- L128 _public function_ `const UViewportTransformer* GetTransformer() const` — @return	Gets the currently active transformer object
- L135 _public prototype_ `void SetTransformables( TArray< TUniquePtr< FViewportTransformable > >&& NewTransformables, const bool bNewObjectsSelected );` — Sets the list of objects that this system will be responsible for transforming when interacting using the gizmo or directly on the objects
- L138 _public prototype_ `void SetDefaultOptionalViewportClient( const TSharedPtr<class FEditorViewportClient>& InEditorViewportClient );` — When using VR, this sets the viewport client that's been "possessed" by the head mounted display.  Only valid when VR is enabled.
- L141 _public prototype_ `void PairInteractors( UViewportInteractor* FirstInteractor, UViewportInteractor* SecondInteractor );` — Pairs to interactors by setting	the other interactor for each interactor
- L150 _public prototype_ `void AddActorToExcludeFromHitTests( AActor* ActorToExcludeFromHitTests );` — `UFUNCTION(BlueprintCallable, Category = "ViewportWorldInteraction")` — Adds an actor to the list of actors to never allow an interactor to hit in the scene.  No selection.  No hover. There's no need to remove actors from this list.  They'll expire from it automatically when destroyed. @param	ActorToExcludeFromHitTests	The actor that should be forever excluded from hit tests
- L153 _public function_ `const TArray<TWeakObjectPtr<AActor>>& GetActorsToExcludeFromHitTest() const` — @return	Returns the list of actors that should never be included in interctor hit tests (hovering or selection)
- L162 _public prototype_ `virtual bool InputKey( FEditorViewportClient* InViewportClient, FViewport* Viewport, FKey Key, EInputEvent Event ) override;`
- L163 _public prototype_ `virtual bool InputAxis( FEditorViewportClient* InViewportClient, FViewport* Viewport, int32 ControllerId, FKey Key, float Delta, float DeltaTime ) override;`
- L166 _public prototype_ `bool PreprocessedInputKey( const FKey Key, const EInputEvent Event );` — Handles the key input from the Input Preprocessor
- L169 _public prototype_ `bool PreprocessedInputAxis( const int32 ControllerId, const FKey Key, const float Delta, const double DeltaTime );` — Handles the axis input from the Input Preprocessor
- L174 _public prototype_ `FTransform GetRoomTransform() const;` — `UFUNCTION(BlueprintCallable, Category = "ViewportWorldInteraction")` — Gets the world space transform of the calibrated VR room origin.  When using a seated VR device, this will feel like the camera's world transform (before any HMD positional or rotation adjustments are applied.)
- L178 _public prototype_ `FTransform GetRoomSpaceHeadTransform() const;` — `UFUNCTION(BlueprintCallable, Category = "ViewportWorldInteraction")` — Gets the transform of the viewport / user's HMD in room space
- L182 _public prototype_ `FTransform GetHeadTransform() const;` — `UFUNCTION(BlueprintCallable, Category = "ViewportWorldInteraction")` — Gets the transform of the viewport / user's HMD in world space
- L187 _public prototype_ `void SetHeadTransform( const FTransform& NewHeadTransform );` — `UFUNCTION(BlueprintCallable, Category = "ViewportWorldInteraction")` — Sets a new transform for the room so that the HMD is aligned to the new transform. The Head is kept level to the ground and only rotated on the yaw
- L190 _public prototype_ `bool HaveHeadTransform() const;` — Returns true if we actually are using VR and have a valid head location, meaning a call to GetHeadTransform() is valid
- L193 _public prototype_ `void SetRoomTransform( const FTransform& NewRoomTransform );` — Sets a new transform for the room, in world space.  This is basically setting the editor's camera transform for the viewport
- L196 _public prototype_ `void SetRoomTransformForNextFrame(const FTransform& NewRoomTransform);` — `UFUNCTION(BlueprintCallable, Category = "ViewportWorldInteraction")`
- L200 _public prototype_ `float GetWorldScaleFactor() const;` — `UFUNCTION(BlueprintCallable, Category = "ViewportWorldInteraction")` — Gets the world scale factor, which can be multiplied by a scale vector to convert to room space
- L203 _public prototype_ `FEditorViewportClient* GetDefaultOptionalViewportClient() const;` — Gets the currently used viewport
- L206 _public function_ `int32 GetMotionControllerID() const` — Returns the Unreal controller ID for the motion controllers we're using
- L212 _public prototype_ `void Undo();` — Invokes the editor's undo system to undo the last change
- L215 _public prototype_ `void Redo();` — Redoes the last change
- L218 _public prototype_ `void DeleteSelectedObjects();` — Deletes all the selected objects
- L221 _public prototype_ `void Copy();` — Copies selected objects to the clipboard
- L224 _public prototype_ `void Paste();` — Pastes the clipboard contents into the scene
- L227 _public prototype_ `void Duplicate();` — Duplicates the selected objects
- L230 _public prototype_ `void Deselect();` — Deselects all the current selected objects
- L233 _public prototype_ `void StopDragging( class UViewportInteractor* Interactor );` — Called to finish a drag action with the specified interactor
- L236 _public prototype_ `void StartDragging( UViewportInteractor* Interactor, UActorComponent* ClickedTransformGizmoComponent, const FVector& HitLocation, const bool bIsPlacingNewObjects, const bool bAllowInterpolationWhenPlacing, const bool bShouldUseLaserImpactDrag, const bool bStartTransaction, const bool bWithGrabberSphere );` — Starts dragging selected objects around.  Called when clicking and dragging on actors/gizmos in the world, or when placing new objects.
- L238 _public prototype_ `DECLARE_EVENT_OneParam( UViewportWorldInteraction, FOnWorldScaleChanged, const float );`
- L239 _public function_ `virtual FOnWorldScaleChanged& OnWorldScaleChanged()`
- L242 _public prototype_ `void SetTransformGizmoCoordinateSpace( const ECoordSystem NewCoordSystem );` — Sets which transform gizmo coordinate space is used
- L245 _public prototype_ `ECoordSystem GetTransformGizmoCoordinateSpace() const;` — Returns which transform gizmo coordinate space we're using, world or local
- L248 _public prototype_ `float GetMaxScale();` — Returns the maximum user scale
- L251 _public prototype_ `float GetMinScale();` — Returns the minimum user scale
- L255 _public prototype_ `void SetWorldToMetersScale( const float NewWorldToMetersScale, const bool bCompensateRoomWorldScale = false );` — `UFUNCTION(BlueprintCallable, Category = "ViewportWorldInteraction")` — Sets GNewWorldToMetersScale
- L260 _public function_ `void SkipInteractiveWorldMovementThisFrame()` — Tells the world interaction system to skip updates of world movement this frame.  This is useful if you've called SetWorldToMetersScale() yourself to set a static world scale, and the cached room-space transforms for the last frame will no longer make sense
- L266 _public prototype_ `bool IsInteractableComponent( const UActorComponent* Component ) const;` — Checks to see if we're allowed to interact with the specified component
- L270 _public prototype_ `class ABaseTransformGizmo* GetTransformGizmoActor();` — `UFUNCTION(BlueprintCallable, Category = "ViewportWorldInteraction")` — Gets the transform gizmo actor, or returns null if we currently don't have one
- L273 _public prototype_ `void SetTransformGizmoVisible( const bool bShouldBeVisible );` — Sets whether the transform gizmo should be visible at all
- L276 _public prototype_ `bool ShouldTransformGizmoBeVisible() const;` — Returns whether the transform gizmo should be visible
- L280 _public prototype_ `bool IsTransformGizmoVisible() const;` — Returns whether the transform gizmo is actually visible right now.  This is different than whether it 'should' be visible, as the gizmo can be implicitly hidden if there are no selected objects, for example.
- L283 _public prototype_ `void SetTransformGizmoScale( const float NewScale );` — Sets how large the transform gizmo is
- L286 _public prototype_ `float GetTransformGizmoScale() const;` — Returns the current transform gizmo scale
- L289 _public prototype_ `void SetDraggedSinceLastSelection( const bool bNewDraggedSinceLastSelection );` — Sets if objects are dragged with either hand since last time selecting something
- L292 _public prototype_ `void SetLastDragGizmoStartTransform( const FTransform NewLastDragGizmoStartTransform );` — Sets the transform of the gizmo when starting drag
- L296 _public prototype_ `const TArray<UViewportInteractor*>& GetInteractors() const;` — `UFUNCTION(BlueprintCallable, Category = "ViewportWorldInteraction")` — Gets all the interactors
- L299 _public prototype_ `void ApplyVelocityDamping( FVector& Velocity, const bool bVelocitySensitive );` — Given a world space velocity vector, applies inertial damping to it to slow it down
- L302 _public prototype_ `EGizmoHandleTypes GetCurrentGizmoType() const;` — Gets the current Gizmo handle type
- L305 _public prototype_ `void SetGizmoHandleType( const EGizmoHandleTypes InGizmoHandleType );` — Sets the current gizmo handle type
- L308 _public prototype_ `void SetTransformGizmoClass( const TSubclassOf<ABaseTransformGizmo>& NewTransformGizmoClass );` — Changes the transform gizmo class that it will change to next refresh
- L311 _public prototype_ `void SetDraggedInteractable( IViewportInteractableInterface* InDraggedInteractable, UViewportInteractor* Interactor );` — Sets the currently dragged interactavle
- L314 _public prototype_ `bool IsOtherInteractorHoveringOverComponent( UViewportInteractor* Interactor, UActorComponent* Component ) const;` — Check if there is another interactor hovering over the component
- L317 _public prototype_ `void CycleTransformGizmoCoordinateSpace();` — Switch which transform gizmo coordinate space we're using.
- L320 _public prototype_ `bool FindPlacementPointUnderLaser( UViewportInteractor* Interactor, FVector& OutHitLocation );` — Figures out where to place an object when tracing it against the scene using a laser pointer
- L323 _public prototype_ `FTrackingTransaction& GetTrackingTransaction();` — Gets the tracking transactions
- L326 _public prototype_ `void SetUseInputPreprocessor( bool bInUseInputPreprocessor );` — Sets whether we should allow input events from the input preprocessor or not
- L329 _public function_ `TArray< TUniquePtr< FViewportTransformable > >& GetTransformables()` — Gets a list of all of the objects we're currently interacting with, such as selected actors
- L335 _public prototype_ `void AllowWorldMovement( bool bAllow );` — The ability to move and scale the world
- L338 _public prototype_ `bool AreAligningToActors() const;` — For other systems to check if the Viewport World Interaction system is currently aligning transformables to actors
- L340 _public prototype_ `bool HasCandidatesSelected();` — For other systems to check if the Viewport World Interaction system currently has candidate actors selected
- L342 _public prototype_ `void SetSelectionAsCandidates();` — If there are no currently selected candidates, use the currently selected actors as candidates. Otherwise, reset the candidates
- L345 _public prototype_ `float GetCurrentDeltaTime() const;` — Gets the current delta time, so functions that don't get the delta time passed can still get it
- L348 _public prototype_ `bool ShouldSuppressExistingCursor() const;` — Getters and setters for whether or not to show the cursor on the viewport
- L349 _public function_ `void SetShouldSuppressExistingCursor(const bool bInShouldSuppressCursor)`
- L355 _public prototype_ `bool ShouldForceCursor() const;` — Getters and setters for whether or not to show the cursor on the viewport
- L356 _public prototype_ `void SetForceCursor(const bool bInShouldForceCursor);`
- L359 _public prototype_ `const UViewportInteractionAssetContainer& GetAssetContainer() const;` — Gets the container for all the assets of ViewportInteraction.
- L362 _public prototype_ `static const UViewportInteractionAssetContainer* LoadAssetContainer();` — Static function to load the asset container
- L365 _public prototype_ `void PlaySound(USoundBase* SoundBase, const FVector& InWorldLocation, const float InVolume = 1.0f);` — Plays sound at location.
- L368 _public prototype_ `void SetInVR(const bool bInVR);` — Set if this world interaction is in VR.
- L371 _public prototype_ `bool IsInVR() const;` — Get if this world interaction is in VR.
- L373 _public prototype_ `FVector SnapLocation(const bool bLocalSpaceSnapping, const FVector& DesiredGizmoLocation, const FTransform &GizmoStartTransform, const FVector SnapGridBase, const bool bShouldConstrainMovement, const FVector AlignAxes);`
- L376 _public prototype_ `void UseLegacyInteractions();` — Forces the VWI to fall back to standard desktop interactions
- L379 _public prototype_ `void UseVWInteractions();` — Sets the VWI to use its own interactions
- L383 _protected prototype_ `virtual void TransitionWorld(UWorld* NewWorld, EEditorWorldExtensionTransitionState TransitionState) override;`
- L384 _protected prototype_ `virtual void EnteredSimulateInEditor() override;`
- L385 _protected prototype_ `virtual void LeftSimulateInEditor(UWorld* SimulateWorld) override;`
- L390 _private prototype_ `void OnEditorClosed();` — Called when the editor is closed
- L393 _private prototype_ `void HoverTick( const float DeltaTime );` — Called every frame to update hover state
- L396 _private prototype_ `void InteractionTick( const float DeltaTime );` — Updates the interaction
- L400 _private prototype_ `void UpdateDragging( const float DeltaTime, bool& bIsFirstDragUpdate, UViewportInteractor* Interactor, const EViewportInteractionDraggingMode DraggingMode, class UViewportDragOperation* DragOperation, const bool bWithTwoHands, const TOptional<FTransformGizmoHandlePlacement> OptionalHandlePlacement, const FVector& DragDelta, const FVector& OtherHandDragDelta, const FVector& DraggedTo, const FVector& OtherHandDraggedTo, const FVector& DragDeltaFromStart, const FVector& OtherHandDragDeltaFromStart, const FVector& LaserPointerStart, const FVector& LaserPointerDirection, const float LaserPointerMaxLength, const bool bIsLaserPointerValid, const FTransform& GizmoStartTransform, FTransform& GizmoLastTransform, FTransform& GizmoTargetTransform, FTransform& GizmoUnsnappedTargetTransform, const FTransform& GizmoInterpolationSnapshotTransform, const FBox& GizmoStartLocalBounds, const USceneComponent* const DraggingTransformGizmoComponent, FVector& GizmoSpaceFirstDragUpdateOffsetAlongAxis, FVector& DragDeltaFromStartOffset, ELockedWorldDragMode& LockedWorldDragMode, float& GizmoScaleSinceDragStarted, float& GizmoRotationRadiansSinceDragStarted, bool& bIsDrivingVelocityOfSimulatedTransformables, FVector& OutUnsnappedDraggedTo);` — Called by the world interaction system when one of our components is dragged by the user.  If null is passed in then we'll treat it as dragging the whole object (rather than a specific axis/handle)
- L434 _private prototype_ `FVector ComputeConstrainedDragDeltaFromStart( const bool bIsFirstDragUpdate, const bool bOnPlane, const TOptional<FTransformGizmoHandlePlacement> OptionalHandlePlacement, const FVector& DragDeltaFromStart, const FVector& LaserPointerStart, const FVector& LaserPointerDirection, const bool bIsLaserPointerValid, const FTransform& GizmoStartTransform, const float LaserPointerMaxLength, FVector& GizmoSpaceFirstDragUpdateOffsetAlongAxis, FVector& DragDeltaFromStartOffset, FVector& OutClosestPointOnLaser) const;` — Given a drag delta from a starting point, contrains that delta based on a gizmo handle axis
- L450 _private prototype_ `void FinishedMovingTransformables();` — Called after dragging has finished with one or both hands and all inertial movement and interpolation has finished with the set of transformables we were working with.  Will also be called if the drag was interrupted.
- L453 _private prototype_ `bool IsSmoothSnappingEnabled() const;` — Checks to see if smooth snapping is currently enabled
- L456 _private function_ `inline FTimespan GetTimeSinceEntered() const` — Returns the time since this was last entered
- L462 _private prototype_ `void PollInputIfNeeded();` — Conditionally polls input from interactors, if we haven't done that already this frame
- L465 _private prototype_ `void RefreshTransformGizmo( const bool bNewObjectsSelected );` — Refreshes the transform gizmo to match the currently selected actor set
- L468 _private prototype_ `void SpawnTransformGizmoIfNeeded();` — Spawn new transform gizmo when refreshing and at start if there is none yet or the current one is different from the TransformGizmoClass
- L471 _private prototype_ `UViewportInteractor* GetOtherInteractorIntertiaContribute( UViewportInteractor* Interactor );` — Gets the inertie contribution of another interactor
- L474 _private prototype_ `void DestroyActors();` — Destroys the actors
- L477 _private function_ `class UMaterialInstanceDynamic* GetSnapGridMID()` — Gets the snap grid mesh MID
- L484 _private prototype_ `void SpawnGridMeshActor();` — Spawns the grid actor
- L487 _private prototype_ `FVector CalculateAverageLocationOfTransformables();` — Average location of all the current transformables
- L490 _private prototype_ `FVector FindTransformGizmoAlignPoint(const FTransform& GizmoStartTransform, const FTransform& DesiredGizmoTransform, const bool bShouldConstrainMovement, FVector ConstraintAxes);` — Location the transformable should snap to if aligning to other transformables
- L491 _private prototype_ `void DrawBoxBrackets(const FBox InActor, const FTransform LocalToWorld, const FLinearColor BracketColor);`
- L494 _private prototype_ `void CompensateRoomTransformForWorldScale(FTransform& InOutRoomTransform, const float InNewWorldToMetersScale, const FVector& InRoomPivotLocation);` — Calculate a new room transform location according to the world to meters scale
- L497 _private prototype_ `bool HasTransformableWithVelocityInSimulate() const;` — If there is a transformable with velocity in simulate
- L500 _private prototype_ `class FEditorModeTools& GetModeTools() const;` — Get mode tools from the viewport client.
- L518 _public prototype_ `FLinearColor GetColor(const EColors Color, const float Multiplier = 1.f) const;` — Gets the color from color type
- L523 _private member_ `static const TCHAR* AssetContainerPath;` — The path of the asset container
- L526 _private member_ `TArray<FLinearColor> Colors;` — All the colors for this mode
- L529 _private member_ `TArray<const AActor*> CandidateActors;` — Candidate actors for aligning in the scene
- L534 _protected member_ `bool bDraggedSinceLastSelection;` — True if we've dragged objects with either hand since the last time we selected something
- L537 _protected member_ `FTransform LastDragGizmoStartTransform;` — Gizmo start transform of the last drag we did with either hand.  Only valid if bDraggedSinceLastSelection is true
- L544 _protected member_ `FTrackingTransaction TrackingTransaction;` — Manages saving undo for selected actors while we're dragging them around
- L549 _private member_ `FTimespan AppTimeEntered;` — App time that we entered this
- L553 _private member_ `TArray< TObjectPtr<class UViewportInteractor> > Interactors;` — `UPROPERTY()` — All the interactors registered to modify the world
- L557 _private member_ `TObjectPtr<class UViewportTransformer> ViewportTransformer;` — `UPROPERTY()` — The active system being used to transform objects
- L564 _private member_ `class FEditorViewportClient* DefaultOptionalViewportClient;` — The viewport that the worldinteraction is used for
- L568 _private member_ `uint32 LastFrameNumberInputWasPolled;` — The last frame that input was polled.  We keep track of this so that we can make sure to poll for latest input right before its first needed each frame
- L571 _private member_ `int32 MotionControllerID;` — The Unreal controller ID for the motion controllers we're using
- L579 _private member_ `float LastWorldToMetersScale;` — The world to meters scale before we changed it (last frame's world to meters scale)
- L582 _private member_ `bool bSkipInteractiveWorldMovementThisFrame;` — True if we should skip interactive world movement/rotation/scaling this frame (because it was already set by something else)
- L588 _private member_ `TOptional<TTuple<FTransform,uint32>> RoomTransformToSetOnFrame;` — The room transform to apply at the beginning of the next frame (if needed.)  This is used to defer updates of the room transform to match with the GNewWorldToMetersScale, which will also take effect on the next frame.  It's critical that those two are applied at the same time, because otherwise a frame rate dependent feedback loop will occur
- L591 _private member_ `float LowSpeedInertiaDamping;` — Storage for Low speed damping value for when we're dragging ourself around the world
- L594 _private member_ `float HighSpeedInertiaDamping;` — Storage for High speed damping value for when we're dragging ourself around the world
- L601 _private member_ `TSet<FViewportHoverTarget> HoveredObjects;` — Set of objects that are currently hovered over
- L609 _private member_ `bool bAreTransformablesMoving;` — True if transformables are being moved around, including any inertial movement or movement caused by smooth snapping or placement interpolation.
- L612 _private member_ `bool bIsInterpolatingTransformablesFromSnapshotTransform;` — True if our transformables are currently interpolating to their target location
- L615 _private member_ `bool bFreezePlacementWhileInterpolatingTransformables;` — When interpolating from a snapshot transform, this will be true if we should freeze the destination placement location until the interpolation finishes
- L618 _private member_ `FTimespan TransformablesInterpolationStartTime;` — Time that we started interpolating at
- L621 _private member_ `float TransformablesInterpolationDuration;` — Duration to interpolate transformables over
- L629 _private member_ `TObjectPtr<class ABaseTransformGizmo> TransformGizmoActor;` — `UPROPERTY()` — Transform gizmo actor, for manipulating selected actor(s)
- L632 _private member_ `TSubclassOf<ABaseTransformGizmo> TransformGizmoClass;` — Class used for when refreshing the transform gizmo
- L635 _private member_ `FBox GizmoLocalBounds;` — Current gizmo bounds in local space.  Updated every frame.  This is not the same as the gizmo actor's bounds.
- L638 _private member_ `bool bShouldTransformGizmoBeVisible;` — Whether the gizmo should be visible or not
- L641 _private member_ `float TransformGizmoScale;` — How big the transform gizmo should be
- L644 _private member_ `TArray< TUniquePtr< FViewportTransformable > > Transformables;` — All of the objects we're currently interacting with, such as selected actors
- L647 _private member_ `TOptional<EGizmoHandleTypes> GizmoType;`
- L650 _private member_ `TOptional<FTransform> LastCarryingTransform;` — When carrying, the last position of the interactor that was carrying.  Used for smoothing motion.
- L658 _private member_ `TObjectPtr<class AActor> SnapGridActor;` — `UPROPERTY()` — Actor for the snap grid
- L662 _private member_ `TObjectPtr<class UStaticMeshComponent> SnapGridMeshComponent;` — `UPROPERTY()` — The plane mesh we use to draw a snap grid under selected objects
- L666 _private member_ `TObjectPtr<class UMaterialInstanceDynamic> SnapGridMID;` — `UPROPERTY()` — MID for the snap grid, so we can update snap values on the fly
- L673 _private member_ `class IViewportInteractableInterface* DraggedInteractable;` — The current dragged interactable
- L680 _private member_ `FOnVIHoverUpdate OnHoverUpdateEvent;` — Event that fires every frame to update hover state based on what's under the cursor.  Set bWasHandled to true if you detect something to hover.
- L683 _private member_ `FOnPreviewInputAction OnPreviewInputActionEvent;` — Event for previewing input actions.  This allows systems to get a first chance at actions before everything else.
- L686 _private member_ `FOnVIActionHandle OnInputActionEvent;` — Event that is fired for when a key is pressed by an interactor
- L689 _private member_ `FOnViewportInteractionInputUnhandled OnViewportInteractionInputUnhandledEvent;` — Called when the user clicks on 'nothing' to request systems to deselect anything that's selected
- L692 _private member_ `FOnHandleInputKey OnKeyInputEvent;` — Event that is fired when new key input is received by the InputProcessor
- L695 _private member_ `FOnHandleInputAxis OnAxisInputEvent;` — Event that is fired when new axis input is received by the InputProcessor
- L698 _private member_ `FOnStartDragging OnStartDraggingEvent;` — Event that is fired when an interactor starts dragging
- L701 _private member_ `FOnStopDragging OnStopDraggingEvent;` — Event that is fired when an interactor stopped dragging
- L704 _private member_ `FOnFinishedMovingTransformables OnFinishedMovingTransformablesEvent;` — Event for when the current set of transformables has finally stop moving (after a drag, and all inertial effects or snapping interpolation has completed
- L707 _private member_ `FOnViewportWorldInteractionTick OnPreWorldInteractionTickEvent;` — Event to tick before the worldinteraction ticks
- L710 _private member_ `FOnViewportWorldInteractionTick OnPostWorldInteractionTickEvent;` — Event to tick after the worldinteraction has ticked
- L718 _private member_ `TObjectPtr<class UMouseCursorInteractor> DefaultMouseCursorInteractor;` — `UPROPERTY()` — The default mouse cursor interactor, activated on demand
- L721 _private member_ `int32 DefaultMouseCursorInteractorRefCount;` — Reference count for the default mouse cursor interactor.  When this reaches zero, the mouse cursor interactor goes away.
- L725 _private member_ `TArray<TWeakObjectPtr<AActor>> ActorsToExcludeFromHitTest;` — `UPROPERTY()` — List of actors which should never be hit by an interactor, such as the 'avatar mesh actor' in VR
- L732 _private member_ `bool bIsInVR;` — If this world interaction is in VR
- L739 _private member_ `FOnWorldScaleChanged OnWorldScaleChangedEvent;` — Event that is fired when the world scale changes
- L742 _private member_ `bool bUseInputPreprocessor;` — If this world interaction should get input from the input processor
- L745 _private member_ `bool bAllowWorldMovement;` — If the user can scale and navigate around in the world
- L748 _private member_ `float CurrentDeltaTime;` — The delta time of this tick
- L751 _private member_ `bool bShouldSuppressCursor;` — Whether or not to show the cursor on the viewport
- L754 _private member_ `bool bShouldForceCursor;` — Whether or not to force the cursor on the viewport
- L757 _private member_ `uint32 CurrentTickNumber;` — The current tick number
- L761 _private member_ `TObjectPtr<const UViewportInteractionAssetContainer> AssetContainer;` — `UPROPERTY()` — Container of assets
- L764 _private member_ `bool bPlayNextRefreshTransformGizmoSound;` — If we want to skip playing the sound when refreshing the transform gizmo next time
- L767 _private member_ `TSharedPtr<class FViewportInteractionInputProcessor> InputProcessor;` — Slate Input Processor

#### enum `UViewportWorldInteraction::EColors`  
`enum EColors`  
_L506-515_
- L508 _public enumerator_ `DefaultColor`
- L509 _public enumerator_ `Forward`
- L510 _public enumerator_ `Right`
- L511 _public enumerator_ `Up`
- L512 _public enumerator_ `GizmoHover`
- L513 _public enumerator_ `GizmoDragging`
- L514 _public enumerator_ `TotalCount`

#### Free symbols / members of external scopes

- L22 _macro_ `#define UE_API VIEWPORTINTERACTION_API`
- L27 _namespace_ `namespace ViewportWorldActionTypes`
- L29 _variable_ `static const FName NoAction( "NoAc` (scope `ViewportWorldActionTypes`)
- L30 _variable_ `static const FName WorldMovement( "Worl` (scope `ViewportWorldActionTypes`)
- L31 _variable_ `static const FName SelectAndMove( "Sele` (scope `ViewportWorldActionTypes`)
- L32 _variable_ `static const FName SelectAndMove_FullyPressed( "Sele` (scope `ViewportWorldActionTypes`)
- L33 _variable_ `static const FName Undo( "Undo` (scope `ViewportWorldActionTypes`)
- L34 _variable_ `static const FName Redo( "Redo` (scope `ViewportWorldActionTypes`)
- L35 _variable_ `static const FName Delete( "Dele` (scope `ViewportWorldActionTypes`)
- L84 _delegate_ `DECLARE_EVENT_ThreeParams( UViewportWorldInteraction, FOnVIHoverUpdate, class UViewportInteractor* , FVector& , bool& );` — Gets the event for hovering update which is broadcasted for each interactor
- L88 _delegate_ `DECLARE_EVENT_FiveParams( UViewportWorldInteraction, FOnPreviewInputAction, class FEditorViewportClient& , class UViewportInteractor* , const struct FViewportActionKeyInput& , bool& , bool& );` — Gets the event for previewing input actions.  This allows systems to get a first chance at actions before everything else.
- L92 _delegate_ `DECLARE_EVENT_FiveParams( UViewportWorldInteraction, FOnVIActionHandle, class FEditorViewportClient& , class UViewportInteractor* , const struct FViewportActionKeyInput& , bool& , bool& );` — Gets the event for input actions update which is broadcasted for each interactor
- L96 _delegate_ `DECLARE_EVENT_ThreeParams( UViewportWorldInteraction, FOnViewportInteractionInputUnhandled, class FEditorViewportClient& , class UViewportInteractor* , const struct FViewportActionKeyInput& );` — Called when the user clicks on 'nothing' to allow systems to deselect anything that's selected
- L100 _delegate_ `DECLARE_EVENT_FourParams( UViewportWorldInteraction, FOnHandleInputKey, class FEditorViewportClient* , const FKey , const EInputEvent , bool& );` — To handle raw key input from the Input Preprocessor
- L104 _delegate_ `DECLARE_EVENT_SixParams( UViewportWorldInteraction, FOnHandleInputAxis, class FEditorViewportClient* , const int32 , const FKey , const float , const float , bool& );` — To handle raw axis input from the Input Preprocessor
- L108 _delegate_ `DECLARE_EVENT_OneParam( UViewportWorldInteraction, FOnStartDragging, class UViewportInteractor* );` — Gets the event for when an interactor starts dragging
- L112 _delegate_ `DECLARE_EVENT_OneParam( UViewportWorldInteraction, FOnStopDragging, class UViewportInteractor* );` — Gets the event for when an interactor stops dragging
- L116 _delegate_ `DECLARE_EVENT( UViewportWorldInteraction, FOnFinishedMovingTransformables );` — Gets the event for when the current set of transformables has finally stop moving (after a drag, and all inertial effects or snapping interpolation has completed
- L119 _delegate_ `DECLARE_EVENT_OneParam( UViewportWorldInteraction, FOnViewportWorldInteractionTick, const float );`
- L238 _delegate_ `DECLARE_EVENT_OneParam( UViewportWorldInteraction, FOnWorldScaleChanged, const float );`
