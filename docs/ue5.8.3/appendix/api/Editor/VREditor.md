# Editor / VREditor

- module root: `Source/Editor/VREditor`
- headers: 27; symbols: 1018
- symbol kinds: class=27, delegate=12, enum=8, enumerator=37, function=80, macro=6, member=369, namespace=1, prototype=459, struct=4, typedef=4, variable=11
- DynamicallyLoadedModuleNames: PlacementMode
- PrivateDependencyModuleNames: Analytics, AppFramework, ApplicationCore, Core, CoreUObject, EditorFramework, Engine, HeadMountedDisplay, InputCore, LevelEditor, LevelSequence, Projects, RenderCore, Sequencer, Slate, SlateCore, ToolMenus, UMG, UnrealEd
- PrivateIncludePathModuleNames: AssetTools, PlacementMode
- PublicDependencyModuleNames: HeadMountedDisplay, ViewportInteraction

### `Source/Editor/VREditor/Private/Teleporter/VREditorAutoScaler.h` (Private)


#### class `UVREditorAutoScaler`  
`class UVREditorAutoScaler: public UObject`  
_L21-48_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Automatically scales the user when dragging the world and pressing the touchpad
- L28 _public prototype_ `UVREditorAutoScaler();` — Default constructor
- L31 _public prototype_ `void Init( class UVREditorMode* InVRMode );` — Initializes the automatic scaler
- L34 _public prototype_ `void Shutdown();` — Shuts down the automatic scaler
- L39 _private prototype_ `void Scale( const float NewScale );` — Actual scale to a certain world to meters
- L42 _private prototype_ `void OnInteractorAction( class FEditorViewportClient& ViewportClient, class UViewportInteractor* Interactor, const struct FViewportActionKeyInput& Action, bool& bOutIsInputCaptured, bool& bWasHandled );` — Called when the user presses a button on their motion controller device
- L47 _private member_ `TObjectPtr<UVREditorMode> VRMode;` — `UPROPERTY()` — Owning mode

### `Source/Editor/VREditor/Private/UI/VREditorBaseUserWidget.h` (Private)


#### class `UVREditorBaseUserWidget`  
`class UVREditorBaseUserWidget : public UUserWidget`  
_L20-51_
- reflection: `UCLASS(Abstract)`
- inherits: `UUserWidget`
- desc: Base class for all of the VR widgets
- L27 _public prototype_ `UVREditorBaseUserWidget( const FObjectInitializer& ObjectInitializer );` — Default constructor that sets up CDO properties
- L30 _public function_ `class AVREditorFloatingUI* GetOwner()` — Gets the owner of this widget
- L36 _public function_ `const class AVREditorFloatingUI* GetOwner() const` — Gets the owner of this widget (const)
- L42 _public prototype_ `void SetOwner( class AVREditorFloatingUI* NewOwner );` — Sets the UI system that owns this widget
- L49 _protected member_ `TWeakObjectPtr<class AVREditorFloatingUI> Owner;` — `UPROPERTY()` — The UI system that owns this widget

### `Source/Editor/VREditor/Private/UI/VREditorDockableCameraWindow.h` (Private)


#### class `AVREditorDockableCameraWindow`  
`class AVREditorDockableCameraWindow : public AVREditorDockableWindow`  
_L12-20_
- reflection: `UCLASS()`
- inherits: `AVREditorDockableWindow`
- desc: A specialized dockable window for camera viewfinders in VR that applies the correct material
- L19 _public prototype_ `AVREditorDockableCameraWindow(const FObjectInitializer& ObjectInitializer);` — Default constructor

### `Source/Editor/VREditor/Private/UI/VREditorDockableWindow.h` (Private)


#### class `AVREditorDockableWindow`  
`class AVREditorDockableWindow : public AVREditorFloatingUI, public IViewportInteractableInterface`  
_L23-146_
- reflection: `UCLASS()`
- inherits: `AVREditorFloatingUI,IViewportInteractableInterface`
- desc: An interactive floating UI panel that can be dragged around
- L30 _public prototype_ `AVREditorDockableWindow(const FObjectInitializer& ObjectInitializer);` — Default constructor
- L31 _public prototype_ `virtual void PostActorCreated() override;`
- L34 _public prototype_ `virtual void TickManually( float DeltaTime ) override;` — Updates the meshes for the UI
- L37 _public prototype_ `void UpdateRelativeRoomTransform();` — Updates the last dragged relative position
- L40 _public prototype_ `UStaticMeshComponent* GetCloseButtonMeshComponent() const;` — Gets the close button component
- L43 _public prototype_ `UStaticMeshComponent* GetSelectionBarMeshComponent() const;` — Gets the selection bar component
- L46 _public prototype_ `float GetDockSelectDistance() const;` — Gets the distance between the interactor and the window when starting drag
- L49 _public prototype_ `void SetDockSelectDistance(const float InDockDistance);` — Set the distance between the interactor and the window when starting drag
- L52 _public prototype_ `virtual void OnPressed( UViewportInteractor* Interactor, const FHitResult& InHitResult, bool& bOutResultedInDrag ) override;` — IViewportInteractableInterface
- L53 _public prototype_ `virtual void OnHover( UViewportInteractor* Interactor ) override;`
- L56 _public prototype_ `virtual void OnHoverEnter( UViewportInteractor* Interactor, const FHitResult& InHitResult ) override;` — Enter hover with laser changes the color of SelectionMesh and CloseButtonMesh
- L59 _public prototype_ `virtual void OnHoverLeave( UViewportInteractor* Interactor, const UActorComponent* NewComponent ) override;` — Leaving hover with laser changes the color of SelectionMesh and CloseButtonMesh
- L60 _public prototype_ `virtual void OnDragRelease( UViewportInteractor* Interactor ) override;`
- L61 _public prototype_ `virtual class UViewportDragOperationComponent* GetDragOperationComponent() override;`
- L62 _public function_ `virtual bool CanBeSelected() override`
- L67 _protected prototype_ `virtual void SetupWidgetComponent() override;` — AVREditorFloatingUI overrides
- L68 _protected prototype_ `virtual void SetCollision(const ECollisionEnabled::Type InCollisionType, const ECollisionResponse InCollisionResponse, const ECollisionChannel InCollisionChannel) override;`
- L73 _private prototype_ `void SetWindowMesh(UStaticMesh* WindowMesh);` — Set the static mesh for the main window that backs our content
- L76 _private prototype_ `void SetSelectionBarColor( const FLinearColor& LinearColor );` — Set the color on the dynamic materials of the selection bar
- L79 _private prototype_ `void SetCloseButtonColor( const FLinearColor& LinearColor );` — Set the color on the dynamic materials of the close button
- L82 _private prototype_ `void SetDockButtonColor(const FLinearColor& LinearColor);` — Set the color on the dynamic materials of the dock button
- L86 _private member_ `TObjectPtr<class UStaticMeshComponent> DockButtonMeshComponent;` — `UPROPERTY()` — Mesh underneath the window for docking it to the world
- L90 _private member_ `TObjectPtr<class UStaticMeshComponent> SelectionBarMeshComponent;` — `UPROPERTY()` — Mesh underneath the window for easy selecting and dragging
- L94 _private member_ `TObjectPtr<class UStaticMeshComponent> CloseButtonMeshComponent;` — `UPROPERTY()` — Mesh that represents the close button for this UI
- L98 _private member_ `TObjectPtr<class UMaterialInstanceDynamic> DockButtonMID;` — `UPROPERTY()` — Dock Button dynamic material  (opaque)
- L102 _private member_ `TObjectPtr<class UMaterialInstanceDynamic> SelectionBarMID;` — `UPROPERTY()` — Selection bar dynamic material  (opaque)
- L106 _private member_ `TObjectPtr<class UMaterialInstanceDynamic> SelectionBarTranslucentMID;` — `UPROPERTY()` — Select bar dynamic material (translucent)
- L110 _private member_ `TObjectPtr<class UMaterialInstanceDynamic> CloseButtonMID;` — `UPROPERTY()` — Close button dynamic material  (opaque)
- L114 _private member_ `TObjectPtr<class UMaterialInstanceDynamic> CloseButtonTranslucentMID;` — `UPROPERTY()` — Close button dynamic material (translucent)
- L117 _private member_ `TObjectPtr<class UViewportDragOperationComponent> DragOperationComponent;` — `UPROPERTY()`
- L120 _private member_ `bool bIsLaserAimingTowardUI;` — True if at least one hand's laser is aiming toward the UI
- L123 _private member_ `float AimingAtMeFadeAlpha;` — Scalar that ramps up toward 1.0 after the user aims toward the UI
- L126 _private member_ `bool bIsHoveringOverSelectionBar;` — True if we're hovering over the selection bar
- L129 _private member_ `float SelectionBarHoverAlpha;` — Scalar that will advance toward 1.0 over time as we hover over the selection bar
- L132 _private member_ `bool bIsHoveringOverCloseButton;` — True if we're hovering over the close button
- L135 _private member_ `bool bIsHoveringOverDockButton;` — True if we're hovering over the dock button
- L138 _private member_ `float CloseButtonHoverAlpha;` — Scalar that will advance toward 1.0 over time as we hover over the close button
- L141 _private member_ `float DockButtonHoverAlpha;` — Scalar that will advance toward 1.0 over time as we hover over the dock button
- L144 _private member_ `float DockSelectDistance;` — Distance from interactor laser to the handle when starting dragging

#### class `UDockableWindowDragOperation`  
`class UDockableWindowDragOperation : public UViewportDragOperation`  
_L152-166_
- reflection: `UCLASS()`
- inherits: `UViewportDragOperation`
- desc: Calculation for dragging a dockable window
- L159 _public prototype_ `virtual void ExecuteDrag( class UViewportInteractor* Interactor, IViewportInteractableInterface* Interactable ) override;` — IViewportDragOperation
- L162 _public member_ `TOptional<FTransform> LastUIToWorld;` — Last frame's UIToWorld transform
- L165 _public member_ `TOptional<FTransform> LastLaserImpactToWorld;` — last frame's LaserImpactToWorld transform

### `Source/Editor/VREditor/Private/UI/VREditorFloatingCameraUI.h` (Private)


#### class `AVREditorFloatingCameraUI`  
`class AVREditorFloatingCameraUI : public AVREditorFloatingUI`  
_L24-42_
- reflection: `UCLASS(Transient)`
- inherits: `AVREditorFloatingUI`
- desc: Represents an interactive floating UI camera preview panel in the VR Editor
- L32 _public member_ `FVector OffsetFromCamera;` — `UPROPERTY(EditDefaultsOnly, Category = "FloatingCameraUI")` — The offset of this UI from its camera
- L34 _public prototype_ `AVREditorFloatingCameraUI(const FObjectInitializer& ObjectInitializer);`
- L35 _public prototype_ `void SetLinkedActor(class AActor* InActor);`
- L37 _public prototype_ `virtual FTransform MakeCustomUITransform() override;`
- L41 _private member_ `TWeakObjectPtr<AActor> LinkedActor;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L18 _typedef_ `typedef FName VREditorPanelID;`

### `Source/Editor/VREditor/Private/UI/VREditorRadialFloatingUI.h` (Private)


#### class `AVREditorRadialFloatingUI`  
`class AVREditorRadialFloatingUI : public AVREditorBaseActor`  
_L23-218_
- reflection: `UCLASS()`
- inherits: `AVREditorBaseActor`
- desc: Represents an interactive floating UI panel in the VR Editor
- L30 _public prototype_ `AVREditorRadialFloatingUI();` — Default constructor which sets up safe defaults
- L31 _public prototype_ `virtual void PostActorCreated() override;`
- L34 _public prototype_ `void SetSlateWidget( class UVREditorUISystem& InitOwner, const TSharedRef<SWidget>& InitSlateWidget, const FIntPoint InitResolution, const float InitScale, const EDockedTo InitDockedTo );` — Creates a FVREditorFloatingUI using a Slate widget, and sets up safe defaults
- L37 _public function_ `bool IsUIVisible() const` — @return Returns true if the UI is visible (or wants to be visible -- it might be transitioning
- L43 _public prototype_ `void ShowUI( const bool bShow, const bool bAllowFading = true, const float InitFadeDelay = 0.0f, const bool bPlaySound = true );` — Shows or hides the UI (also enables collision, and performs a transition effect)
- L46 _public function_ `const TArray<class UVREditorWidgetComponent*>& GetWidgetComponents() const` — Returns the widget component for this UI, or nullptr if not spawned right now
- L52 _public function_ `class UStaticMeshComponent* GetMeshComponent()` — Returns the mesh component for this UI, or nullptr if not spawned right now
- L58 _public prototype_ `FVector2D GetSize() const;` — Returns the actual size of the UI in either axis, after scaling has been applied.  Does not take into animation or world scaling
- L61 _public prototype_ `float GetScale() const;` — Gets the scale
- L64 _public prototype_ `void SetScale( const float NewSize );` — Sets a new size for the UI
- L67 _public prototype_ `virtual void SetTransform( const FTransform& Transform ) override;` — Sets the UI transform
- L70 _public prototype_ `virtual void Destroyed() override;` — AActor overrides
- L71 _public function_ `virtual bool IsEditorOnly() const final`
- L78 _public function_ `UVREditorUISystem& GetOwner()` — Returns the owner of this object
- L85 _public function_ `const UVREditorUISystem& GetOwner() const` — Returns the owner of this object (const)
- L92 _public prototype_ `float GetInitialScale() const;` — Gets the initial size of this UI
- L95 _public prototype_ `virtual void SetupWidgetComponent(TSharedPtr<SWidget> SlateWidget);` — Called to finish setting everything up, after a widget has been assigned
- L98 _public prototype_ `void Reset();` — Reset for the next radial menu to be created
- L101 _public function_ `void SetNumberOfEntries(const float InNumberOfEntries)` — Set the number of entries for the menu
- L107 _public function_ `void SetButtonTypeOverride(const FName InButtonTypeOverride)` — Set the button type for the menu
- L113 _public function_ `void SetCurrentMenuWidget(const TSharedPtr<class SMultiBoxWidget> InWidget)` — Store the menu widget for the menu
- L119 _public function_ `const TSharedPtr<class SMultiBoxWidget> GetCurrentMenuWidget()` — Return the menu widget for comparison
- L129 _public prototype_ `const void HighlightSlot(const FVector2D& TrackpadPosition);` — Highlight the widget in a slot based on a given trackpad position @param	TrackpadPosition	The current trackpad or thumbstick position
- L132 _public prototype_ `void SimulateLeftClick();` — Simulate a left-mouse click (down and up) on the currently hovered button
- L135 _public prototype_ `const TSharedPtr<SButton>& GetCurrentlyHoveredButton();` — Gets the currently hovered button
- L137 _public prototype_ `void UpdateCentralWidgetComponent(const TSharedPtr<SWidget>& NewCentralSlateWidget);`
- L142 _protected prototype_ `FVector CalculateAnimatedScale() const;` — Returns a scale to use for this widget that takes into account animation
- L145 _protected prototype_ `virtual void SetCollision(const ECollisionEnabled::Type InCollisionType, const ECollisionResponse InCollisionResponse, const ECollisionChannel InCollisionChannel);` — Set collision on components
- L150 _private prototype_ `virtual void UpdateFadingState( const float DeltaTime );` — Called after spawning, and every Tick, to update opacity of the widget
- L154 _protected member_ `TSharedPtr<class SMultiBoxWidget> MenuMultiBoxWidget;` — Stores the widget associated with the quick menu
- L157 _protected member_ `TArray<TSharedPtr<SWidget>> SlateWidgets;` — Slate widget we're drawing, or null if we're drawing a UMG user widget
- L161 _protected member_ `TArray<TObjectPtr<class UVREditorWidgetComponent>> WidgetComponents;` — `UPROPERTY()` — When in a spawned state, this is the widget component to represent the widget
- L165 _protected member_ `TObjectPtr<class UStaticMeshComponent> WindowMeshComponent;` — `UPROPERTY()` — The floating window mesh
- L169 _protected member_ `TObjectPtr<class UStaticMeshComponent> ArrowMeshComponent;` — `UPROPERTY()` — The arrow indicator mesh
- L173 _protected member_ `TObjectPtr<class UVREditorWidgetComponent> CentralWidgetComponent;` — `UPROPERTY()` — The central helper widget
- L175 _protected member_ `TSharedPtr<SWidget> CentralSlateWidget;`
- L178 _protected member_ `FIntPoint Resolution;` — Resolution we should draw this UI at, regardless of scale
- L183 _private member_ `class UVREditorUISystem* Owner;` — Owning object
- L187 _private member_ `TOptional<bool> bShouldBeVisible;` — True if the UI wants to be visible, or false if it wants to be hidden.  Remember, we might still be visually transitioning between states
- L190 _private member_ `float FadeAlpha;` — Fade alpha, for visibility transitions
- L193 _private member_ `float FadeDelay;` — Delay to fading in or out. Set on ShowUI and cleared on finish of fade in/out
- L196 _private member_ `float InitialScale;` — The starting scale of this UI
- L199 _private member_ `float NumberOfEntries;` — Number of entries in the radial menu
- L202 _private member_ `FName ButtonTypeOverride;` — Radial menu supports SButton and SMenuEntryButton, but needs to know which type it has
- L205 _private member_ `TSharedPtr<SButton> CurrentlyHoveredButton;` — Stores the currently hovered button
- L208 _private member_ `class UVREditorWidgetComponent* CurrentlyHoveredWidget;` — Stores the currently hovered widget component
- L211 _private member_ `float GlowAmount;` — Glow amount of window frame - VFX
- L213 _private member_ `float DefaultGlowAmount;`
- L216 _private member_ `float ArrowAlpha;` — Alpha of arrow - VFX

### `Source/Editor/VREditor/Private/VREditorActions.h` (Private)


#### class `FVREditorActionCallbacks`  
`class FVREditorActionCallbacks`  
_L21-208_
- desc: Implementation of various VR editor action callback functions
- L26 _public prototype_ `static ECheckBoxState GetTranslationSnapState();` — Returns the checked state of the translation snap enable/disable button
- L29 _public prototype_ `static void OnTranslationSnapSizeButtonClicked();` — Rotates through the available translation snap sizes
- L32 _public prototype_ `static FText GetTranslationSnapSizeText();` — Returns the translation snap size as text to use as the button display text
- L35 _public prototype_ `static ECheckBoxState GetRotationSnapState();` — Returns the checked state of the rotation snap enable/disable button
- L38 _public prototype_ `static void OnRotationSnapSizeButtonClicked();` — Rotates through the available rotation snap sizes
- L41 _public prototype_ `static FText GetRotationSnapSizeText();` — Returns the rotation snap size as text to use as the button display text
- L44 _public prototype_ `static ECheckBoxState GetScaleSnapState();` — Returns the checked state of the scale snap enable/disable button
- L47 _public prototype_ `static void OnScaleSnapSizeButtonClicked();` — Rotates through the available scale snap sizes
- L50 _public prototype_ `static FText GetScaleSnapSizeText();` — Returns the scale snap size as text to use as the button display text
- L56 _public prototype_ `static void OnGizmoCoordinateSystemButtonClicked(UVREditorMode* InVRMode);` — Toggles the gizmo coordinate system between local and world space @param InVRMode Currently active VRMode
- L58 _public prototype_ `static void SetCoordinateSystem(UVREditorMode* InVRMode, ECoordSystem InCoordSystem);`
- L60 _public prototype_ `static ECheckBoxState IsActiveCoordinateSystem(UVREditorMode* InVRMode, ECoordSystem InCoordSystem);`
- L63 _public prototype_ `static FText GetGizmoCoordinateSystemText();` — Returns the gizmo coordinate system as text to use as the button display text
- L69 _public prototype_ `static void UpdateGizmoCoordinateSystemText(UVREditorMode* InVRMode);` — Updates the gizmo coordinate system text if the coordinate system or gizmo type is changed @param InVRMode Currently active VRMode
- L75 _public prototype_ `static void OnGizmoModeButtonClicked(UVREditorMode* InVRMode);` — Rotates the gizmo type through universal, translate, rotate, and scale @param InVRMode Currently active VRMode
- L77 _public prototype_ `static void SetGizmoMode(UVREditorMode* InVRMode, EGizmoHandleTypes InGizmoMode);`
- L79 _public prototype_ `static EGizmoHandleTypes GetGizmoMode(const UVREditorMode* InVRMode);`
- L81 _public prototype_ `static ECheckBoxState IsActiveGizmoMode(UVREditorMode* InVRMode, EGizmoHandleTypes InGizmoMode);`
- L84 _public prototype_ `static FText GetGizmoModeText();` — Returns the gizmo type as text to use as the button display text
- L90 _public prototype_ `static void UpdateGizmoModeText(UVREditorMode* InVRMode);` — Updates the gizmo coordinate type text if the coordinate system or gizmo type is changed @param InVRMode Currently active VRMode
- L97 _public prototype_ `static void OnUIToggleButtonClicked(UVREditorMode* InVRMode, VREditorPanelID PanelToToggle);` — Toggles a VR UI panel's state between visible and invisible @param InVRMode Currently active VRMode @param PanelToToggle UI panel to change the state of
- L104 _public prototype_ `static ECheckBoxState GetUIToggledState(UVREditorMode* InVRMode, VREditorPanelID PanelToCheck);` — Returns a VR UI panel's visibility - used for check boxes on the menu button @param InVRMode Currently active VRMode @param PanelToToggle UI panel to read the state of
- L110 _public prototype_ `static void OnSnapActorsToGroundClicked(UVREditorMode* InVRMode);` — Snaps currently selected Actors to the ground @param InVRMode Currently active VRMode
- L116 _public prototype_ `static void SimulateCharacterEntry(const FString InChar);` — Simulates the user entering characters with a keyboard for data entry @param InChar String of characters to enter
- L119 _public prototype_ `static void SimulateBackspace();` — Send a backspace event. Slate editable text fields handle backspace as a TCHAR(8) character entry
- L126 _public prototype_ `static void SimulateKeyDown( const FKey Key, const bool bRepeat );` — Simulates the user pressing a key down @param Key Key to press @param bRepeat Whether or not to repeat
- L132 _public prototype_ `static void SimulateKeyUp( const FKey Key );` — Simulates the user releasing a key @param Key Key to release
- L135 _public prototype_ `static void CreateNewSequence(UVREditorMode* InVRMode);` — Create a new level sequence with an auto-generated name
- L138 _public prototype_ `static void CloseSequencer(class UMovieSceneSequence* OpenSequence);` — Close the sequencer instance
- L141 _public prototype_ `static void PlaySequenceAtRate(UVREditorMode* InVRMode, float Rate);` — Plays the current sequence at a specified rate
- L144 _public prototype_ `static void PauseSequencePlayback(UVREditorMode* InVRMode);` — Pauses sequence playback
- L147 _public prototype_ `static void PlayFromBeginning(UVREditorMode* InVRMode);` — Plays at a rate of 1.0 from the local start of the sequence
- L150 _public prototype_ `static void ToggleLooping(UVREditorMode* InVRMode);` — Toggles looping the sequence
- L153 _public prototype_ `static FText GetSequencerLoopingText();` — The type of looping for the current sequence
- L156 _public prototype_ `static void UpdateSequencerLoopingText(UVREditorMode * InVRMode);` — Updates the sequencer toggling display
- L159 _public prototype_ `static void SetSelectionRangeStart(UVREditorMode* InVRMode);` — Sets the current sequence's selection range start to the current time
- L162 _public prototype_ `static void SetSelectionRangeEnd(UVREditorMode* InVRMode);` — Sets the current sequence's selection range end to the current time
- L164 _public prototype_ `static void ToggleSequencerScrubbing(UVREditorMode* InVRMode, UVREditorInteractor* InController);`
- L166 _public prototype_ `static ECheckBoxState GetSequencerScrubState(UVREditorInteractor* InController);`
- L169 _public prototype_ `static void ToggleAligningToActors(UVREditorMode* InVRMode);` — Toggles whether or not the world interaction method should align transformables to actors in the scene
- L172 _public prototype_ `static ECheckBoxState AreAligningToActors(UVREditorMode* InVRMode);` — True if the world interaction method is currently aligning transformables to actors in the scene
- L175 _public prototype_ `static void ToggleSelectingCandidateActors(UVREditorMode* InVRMode);` — Either selects or deselects alignment candidates
- L178 _public prototype_ `static bool CanSelectCandidateActors(UVREditorMode* InVRMode);` — Can only select candidate actors if actor alignment is active
- L181 _public prototype_ `static FText GetSelectingCandidateActorsText();` — Dynamic label for the alignment candidate button
- L184 _public prototype_ `static void UpdateSelectingCandidateActorsText(UVREditorMode* InVRMode);` — Updates the alignment candidate label based on the current aligning state
- L187 _public prototype_ `static void ChangeEditorModes(FEditorModeID InMode);` — Changes the editor mode to the given ID
- L190 _public prototype_ `static ECheckBoxState EditorModeActive(FEditorModeID InMode);` — Checks whether the editor mode for the given ID is active
- L193 _public prototype_ `static void DeselectAll();` — Deselects everything currently selected
- L196 _public prototype_ `static void ExitVRMode(UVREditorMode* InVRMode);` — Exit the VR mode
- L200 _public member_ `static FText GizmoCoordinateSystemText;`
- L202 _public member_ `static FText GizmoModeText;`
- L204 _public member_ `static FText SelectingCandidateActorsText;`
- L206 _public member_ `static FText SequencerLoopText;`

### `Source/Editor/VREditor/Private/VREditorAvatarActor.h` (Private)


#### class `AVREditorAvatarActor`  
`class AVREditorAvatarActor : public AActor`  
_L20-121_
- reflection: `UCLASS()`
- inherits: `AActor`
- desc: Avatar Actor
- L27 _public prototype_ `AVREditorAvatarActor();` — Default constructor
- L30 _public prototype_ `void Init( class UVREditorMode* InVRMode );` — Called by VREditorMode::Enter to initialize all post constructor components and to set the VRMode
- L33 _public prototype_ `void TickManually( const float DeltaTime );` — Called by VREditorMode to update us every frame
- L36 _public function_ `virtual bool IsEditorOnly() const final` — UObject overrides
- L42 _public function_ `virtual bool HasLocalNetOwner() const override`
- L52 _private member_ `TObjectPtr<class UStaticMeshComponent> HeadMeshComponent;` — `UPROPERTY()` — Our avatar's head mesh
- L56 _private member_ `TObjectPtr<class UStaticMeshComponent> WorldMovementGridMeshComponent;` — `UPROPERTY()` — The grid that appears while the user is dragging the world around
- L64 _private member_ `TObjectPtr<class UMaterialInstanceDynamic> WorldMovementGridMID;` — `UPROPERTY()` — Grid mesh component dynamic material instance to set the opacity
- L68 _private member_ `float WorldMovementGridOpacity;` — `UPROPERTY()` — Opacity of the movement grid and post process
- L72 _private member_ `bool bIsDrawingWorldMovementPostProcess;` — `UPROPERTY()` — True if we're currently drawing our world movement post process
- L76 _private member_ `TObjectPtr<class UMaterialInstanceDynamic> WorldMovementPostProcessMaterial;` — `UPROPERTY()` — Post process material for "greying out" the world while in world movement mode
- L84 _private member_ `TObjectPtr<class UStaticMeshComponent> ScaleProgressMeshComponent;` — `UPROPERTY()` — Background progressbar scaling mesh
- L88 _private member_ `TObjectPtr<class UStaticMeshComponent> CurrentScaleProgressMeshComponent;` — `UPROPERTY()` — Current scale progressbar mesh
- L92 _private member_ `TObjectPtr<class UTextRenderComponent> UserScaleIndicatorText;` — `UPROPERTY()` — Current scale text
- L96 _private member_ `TObjectPtr<UMaterialInstanceDynamic> FixedUserScaleMID;` — `UPROPERTY()` — Base dynamic material for the user scale fixed progressbar
- L100 _private member_ `TObjectPtr<UMaterialInstanceDynamic> TranslucentFixedUserScaleMID;` — `UPROPERTY()` — Translucent dynamic material for the user scale fixed progressbar
- L104 _private member_ `TObjectPtr<UMaterialInstanceDynamic> CurrentUserScaleMID;` — `UPROPERTY()` — Base dynamic material for the current user scale progressbar
- L108 _private member_ `TObjectPtr<UMaterialInstanceDynamic> TranslucentCurrentUserScaleMID;` — `UPROPERTY()` — Translucent dynamic material for the current user scale progressbar
- L116 _private member_ `TObjectPtr<class UPostProcessComponent> PostProcessComponent;` — `UPROPERTY()` — Post process for drawing VR-specific post effects
- L120 _private member_ `TObjectPtr<class UVREditorMode> VRMode;` — `UPROPERTY()` — Owning object

### `Source/Editor/VREditor/Private/VREditorCameraWidgetComponent.h` (Private)


#### class `UVREditorCameraWidgetComponent`  
`class UVREditorCameraWidgetComponent : public UVREditorWidgetComponent`  
_L12-19_
- reflection: `UCLASS(hidedropdown)`
- inherits: `UVREditorWidgetComponent`
- desc: A specialized WidgetComponent that color-corrects cameras previews (viewfinders) in VR
- L17 _public prototype_ `UVREditorCameraWidgetComponent();`

### `Source/Editor/VREditor/Private/VREditorFloatingText.h` (Private)


#### class `AFloatingText`  
`class AFloatingText : public AActor`  
_L14-78_
- reflection: `UCLASS(NotPlaceable, NotBlueprintable)`
- inherits: `AActor`
- desc: Draws 3D text in the world along with targeting line cues
- L21 _public prototype_ `AFloatingText();` — Default constructor that sets up CDO properties
- L24 _public prototype_ `virtual void PostActorCreated() override;` — AActor overrides
- L25 _public function_ `virtual bool IsEditorOnly() const final`
- L31 _public prototype_ `void SetText( const FText& NewText );` — Sets the text to display
- L34 _public prototype_ `void SetOpacity( const float Opacity );` — Sets the opacity of the actor
- L37 _public prototype_ `void Update( const FVector OrientateToward );` — Call this every frame to orientate the text toward the specified transform
- L44 _private member_ `TObjectPtr<class USceneComponent> SceneComponent;` — `UPROPERTY()` — Scene component root of this actor
- L48 _private member_ `TObjectPtr<class UStaticMeshComponent> FirstLineComponent;` — `UPROPERTY()` — First line segment component.  Starts at the designation location, goes toward the line connection point.
- L52 _private member_ `TObjectPtr<class UStaticMeshComponent> JointSphereComponent;` — `UPROPERTY()` — Sphere that connects the two line segments and makes the joint look smooth and round
- L56 _private member_ `TObjectPtr<class UStaticMeshComponent> SecondLineComponent;` — `UPROPERTY()` — Second line segment component.  Starts at the connection point and goes toward the 3D text.
- L60 _private member_ `TObjectPtr<class UTextRenderComponent> TextComponent;` — `UPROPERTY()` — The 3D text we're drawing.  Positioned at the end of the second line.
- L64 _private member_ `TObjectPtr<class UMaterialInterface> MaskedTextMaterial;` — `UPROPERTY()` — Masked text material.  Used after faded in
- L68 _private member_ `TObjectPtr<class UMaterialInterface> TranslucentTextMaterial;` — `UPROPERTY()` — Translucent text material.  Used during fading
- L72 _private member_ `TObjectPtr<class UMaterialInterface> LineMaterial;` — `UPROPERTY()` — Material to use for the line meshes
- L76 _private member_ `TObjectPtr<class UMaterialInstanceDynamic> LineMaterialMID;` — `UPROPERTY(transient)` — Dynamic material instance for fading lines in and out

### `Source/Editor/VREditor/Private/VREditorModeManager.h` (Private)


#### class `FVREditorModeManager`  
`class FVREditorModeManager : public FGCObject, public FTickableEditorObject`  
_L20-127_
- inherits: `FGCObject,FTickableEditorObject`
- desc: Manages starting and closing the VREditor mode
- L24 _public prototype_ `FVREditorModeManager();` — Default constructor
- L27 _public prototype_ `~FVREditorModeManager();` — Default destructor
- L30 _public prototype_ `virtual void Tick(float DeltaTime) override;` — FTickableEditorObject overrides
- L31 _public prototype_ `virtual bool IsTickable() const override;`
- L32 _public function_ `virtual TStatId GetStatId() const override`
- L38 _public prototype_ `void EnableVREditor( const bool bEnable, const bool bForceWithoutHMD );` — Start or stop the VR Editor
- L41 _public prototype_ `bool IsVREditorActive() const;` — If the VR Editor is currently running
- L44 _public prototype_ `bool IsVREditorAvailable() const;` — If the VR Editor is currently available
- L47 _public prototype_ `bool IsVREditorButtonActive() const;` — If the VR Editor button active
- L50 _public prototype_ `UVREditorModeBase* GetCurrentVREditorMode();` — Gets the current VR Editor mode that was enabled
- L53 _public prototype_ `virtual void AddReferencedObjects( FReferenceCollector& Collector );` — FGCObject
- L54 _public function_ `virtual FString GetReferencerName() const override`
- L61 _public function_ `FOnVREditingModeEnter& OnVREditingModeEnter()` — Return a multicast delegate which is executed when VR mode starts.
- L64 _public function_ `FOnVREditingModeExit& OnVREditingModeExit()` — Return a multicast delegate which is executed when VR mode stops.
- L69 _public prototype_ `void GetConcreteModeClasses(TArray<UClass*>& OutModeClasses) const;` — Loads each cached UVREditorModeBase-derived class path, checking and appending only those which are suitable for use (not abstract, etc.) to the provided array.
- L71 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FModeClassAdded, const FTopLevelAssetPath&);`
- L72 _public member_ `FModeClassAdded OnModeClassAdded;`
- L74 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FModeClassRemoved, const FTopLevelAssetPath&);`
- L75 _public member_ `FModeClassRemoved OnModeClassRemoved;`
- L78 _private prototype_ `UClass* TryGetConcreteModeClass(const FTopLevelAssetPath& ClassPath) const;`
- L81 _private prototype_ `void GetModeClassPaths(TSet<FTopLevelAssetPath>& OutModeClassPaths) const;` — Queries the asset registry for asset paths of all classes derived from UVREditorModeBase.
- L84 _private prototype_ `void UpdateCachedModeClassPaths();` — Stores the results of GetModeClassPaths() into CachedModeClassPaths.
- L87 _private member_ `TSet<FTopLevelAssetPath> CachedModeClassPaths;` — Cached UVREditorModeBase-derived assets, updated in response to asset registry events.
- L89 _private prototype_ `void HandleAssetFilesLoaded();`
- L90 _private prototype_ `void HandleAssetAddedOrRemoved(TConstArrayView<FAssetData> NewAssetData);`
- L93 _private member_ `FOnVREditingModeEnter OnVREditingModeEnterHandle;` — Broadcasts when VR mode is started
- L96 _private member_ `FOnVREditingModeExit OnVREditingModeExitHandle;` — Broadcasts when VR mode is stopped
- L98 _private prototype_ `void HandleModeEntryComplete();`
- L101 _private prototype_ `void StartVREditorMode( const bool bForceWithoutHMD );` — Saves the WorldToMeters and enters the mode belonging to GWorld
- L104 _private prototype_ `void CloseVREditor(const bool bShouldDisableStereo );` — Closes the current VR Editor if any and sets the WorldToMeters to back to the one from before entering the VR mode
- L107 _private prototype_ `void SetDirectWorldToMeters( const float NewWorldToMeters );` — Directly set the GWorld WorldToMeters
- L110 _private prototype_ `void OnMapChanged( UWorld* World, EMapChangeType MapChangeType );` — On level changed
- L113 _private prototype_ `void HandleEditorPreExit();` — Ensure we shut down cleanly early in editor shutdown.
- L117 _private member_ `TObjectPtr<UVREditorModeBase> CurrentVREditorMode;` — `UPROPERTY()` — The current mode, nullptr if none
- L120 _private member_ `bool bEnableVRRequest;` — If the VR Editor mode needs to be enabled next tick
- L123 _private member_ `EHMDWornState::Type HMDWornState;` — True when we detect that the user is wearing the HMD
- L126 _private member_ `bool bAddedViewportWorldInteractionExtension;` — True if the ViewportWorldInteraction extension was not pre-existing.

#### Free symbols / members of external scopes

- L71 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FModeClassAdded, const FTopLevelAssetPath&);`
- L74 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FModeClassRemoved, const FTopLevelAssetPath&);`

### `Source/Editor/VREditor/Private/VREditorModule.h` (Private)


#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogVREditor, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogVREditor, Log, All);`

### `Source/Editor/VREditor/Private/VREditorPlacement.h` (Private)


#### class `UVREditorPlacement`  
`class UVREditorPlacement : public UObject`  
_L25-69_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: VR Editor interaction with the 3D world
- L32 _public prototype_ `UVREditorPlacement();` — Default constructor
- L35 _public prototype_ `void Init(UVREditorMode* InVRMode);` — Registers to events and sets initial values
- L38 _public prototype_ `void Shutdown();` — Removes registered event
- L43 _protected prototype_ `void StopDragging( UViewportInteractor* Interactor );` — When an interactor stops dragging
- L46 _protected prototype_ `void UpdateNearClipPlaneOnScaleChange(const float NewWorldToMetersScale);` — When the world scale changes, update the near clip plane
- L52 _protected member_ `TObjectPtr<UVREditorMode> VRMode;` — `UPROPERTY()` — Owning object
- L56 _protected member_ `TObjectPtr<UViewportWorldInteraction> ViewportWorldInteraction;` — `UPROPERTY()` — The actual ViewportWorldInteraction
- L64 _protected member_ `TObjectPtr<class UWidgetComponent> FloatingUIAssetDraggedFrom;` — `UPROPERTY()` — The UI used to drag an asset into the level
- L68 _protected member_ `TObjectPtr<UObject> PlacingMaterialOrTextureAsset;` — `UPROPERTY()` — The material or texture asset we're dragging to place on an object

### `Source/Editor/VREditor/Private/VREditorWidgetComponent.h` (Private)


#### enum `EVREditorWidgetDrawingPolicy`  
`enum class EVREditorWidgetDrawingPolicy : uint8`  
_L11-15_
- reflection: `UENUM()`
- L13 _public enumerator_ `Always`
- L14 _public enumerator_ `Hovering`

#### class `UVREditorWidgetComponent`  
`class UVREditorWidgetComponent : public UWidgetComponent`  
_L21-60_
- reflection: `UCLASS(hidedropdown)`
- inherits: `UWidgetComponent`
- desc: A specialized WidgetComponent for the VREditor
- L27 _public prototype_ `UVREditorWidgetComponent();` — Default constructor that sets up CDO properties
- L29 _public function_ `void SetDrawingPolicy(EVREditorWidgetDrawingPolicy Value)`
- L30 _public function_ `EVREditorWidgetDrawingPolicy GetDrawingPolicy() const`
- L32 _public function_ `void SetIsHovering(bool Value)`
- L33 _public function_ `bool GetIsHovering() const`
- L36 _protected prototype_ `virtual bool ShouldDrawWidget() const override;`
- L38 _protected prototype_ `virtual void DrawWidgetToRenderTarget(float DeltaTime) override;`
- L45 _private member_ `EVREditorWidgetDrawingPolicy DrawingPolicy;` — `UPROPERTY()` — High level redrawing policy for the widget component.
- L52 _private member_ `bool bIsHovering;` — `UPROPERTY()` — Controls if we draw, the VREditorWidget allows for manual enabling or disabling of updating the slate widget.
- L59 _private member_ `bool bHasEverDrawn;` — `UPROPERTY()` — Recorders if we've drawn at least once, that way we can always draw the first frame then go manual after that.

### `Source/Editor/VREditor/Public/IVREditorModule.h` (Public)


#### class `IVREditorModule`  
`class IVREditorModule : public IModuleInterface`  
_L18-129_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L22 _public prototype_ `virtual FOnVREditingModeEnter& OnVREditingModeEnter() = 0;` — @return a multicast delegate which is executed when VR mode starts.
- L25 _public prototype_ `virtual FOnVREditingModeExit& OnVREditingModeExit() = 0;` — @return a multicast delegate which is executed when VR mode stops.
- L33 _public function_ `static inline IVREditorModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L43 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L53 _public prototype_ `virtual bool IsVREditorEnabled() const = 0;` — Checks whether or not editor VR features are enabled @return	True if VR mode is on
- L61 _public prototype_ `virtual bool IsVREditorAvailable() const = 0;` — Checks to see whether its possible to use VR mode in this session.  Basically, this makes sure that you have the appropriate hardware connected @return	True if EnableVREditor() can be used to activate VR mode
- L68 _public prototype_ `virtual bool IsVREditorButtonActive() const = 0;` — Checks to see if the VR Mode button should be active or grayed out (such as during SIE) @return	True if button should be active
- L77 _public prototype_ `virtual void EnableVREditor( const bool bEnable, const bool bForceWithoutHMD = false ) = 0;` — Enables or disables editor VR features.  Calling this to active VR will turn on the HMD and setup the editor UI for VR interaction. @param	bEnable	True to enable VR, or false to turn it off @param	bForceWithoutHMD	If set to true, will enter VR mode without switching to HMD/stereo.  This can be useful for testing.
- L85 _public prototype_ `virtual bool IsVREditorModeActive() = 0;` — `UE_DEPRECATED(5.7, "Test whether GetVRModeBase returns nullptr instead; this only returns true for the deprecated UVREditorMode.")` — Check if the VR Editor is currently running @return True if the VREditor is currently running
- L93 _public prototype_ `virtual class UVREditorMode* GetVRMode() = 0;` — `UE_DEPRECATED(5.7, "Use GetVRModeBase instead; this only supports the deprecated UVREditorMode.")` — Get the current VREditor running @return The current VREditor running
- L96 _public prototype_ `virtual class UVREditorModeBase* GetVRModeBase() = 0;` — @return The active UVREditorModeBase
- L104 _public prototype_ `virtual void UpdateActorPreview(TSharedRef<class SWidget> InWidget, int32 Index, AActor *Actor = nullptr, bool bIsDetached = false) = 0;` — `UE_DEPRECATED(5.7, "VR Editor mode is deprecated; use the XR Creative Framework plugin instead.")` — Update the actor preview (for example, the view from a camera attached to a pawn) in VR mode @param The new actor preview widget
- L114 _public prototype_ `virtual void UpdateExternalUMGUI(const struct FVREditorFloatingUICreationContext& CreationContext) = 0;` — `UE_DEPRECATED(5.7, "VR Editor mode is deprecated; use the XR Creative Framework plugin instead.")` — Update any external UMG UI spawned from the radial menu @param The new widget @param The label to use for the UI
- L123 _public prototype_ `virtual void UpdateExternalSlateUI(TSharedRef<SWidget> InSlateWidget, FName Name, FVector2D InSize = FVector2D::ZeroVector) = 0;` — `UE_DEPRECATED(5.7, "VR Editor mode is deprecated; use the XR Creative Framework plugin instead.")` — Update any external Slate UI spawned from the radial menu @param The new widget @param The label to use for the UI
- L127 _public prototype_ `virtual TSharedPtr<class FExtender> GetRadialMenuExtender() = 0;` — `UE_DEPRECATED(5.7, "VR Editor mode is deprecated; use the XR Creative Framework plugin instead.")` — Gets the radial menu extender.  This can be used to add your own menu items to the VR radial menu

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnVREditingModeEnter);`
- L12 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnVREditingModeEnter);`
- L13 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnVREditingModeExit);`
- L13 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnVREditingModeExit);`

### `Source/Editor/VREditor/Public/Teleporter/VREditorTeleporter.h` (Public)


#### class `AVREditorTeleporter`  
`class UE_DEPRECATED(5.7, "VR Editor mode is deprecated; use the XR Creative Framework plugin instead.") AVREditorTeleporter : public AActor`  
_L26-198_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType)`
- inherits: `AActor`
- desc: VR Editor teleport manager and the visual representation of the teleport
- L33 _public prototype_ `AVREditorTeleporter();` — Default constructor that sets up CDO properties
- L37 _public prototype_ `void Init( class UVREditorMode* InMode );` — `UFUNCTION(BlueprintNativeEvent, CallInEditor, Category = "Teleporter")` — Initializes the teleporter
- L41 _public prototype_ `void Shutdown();` — `UFUNCTION(BlueprintNativeEvent, CallInEditor, Category = "Teleporter")` — Shuts down the teleporter
- L45 _public prototype_ `bool IsAiming() const;` — `UFUNCTION(BlueprintCallable, Category = "Teleporter")` — Whether we are currently aiming to teleport.
- L48 _public prototype_ `bool IsTeleporting() const;` — `UFUNCTION(BlueprintCallable, Category = "Teleporter")`
- L51 _public prototype_ `class UVREditorMode* GetVRMode() const;` — `UFUNCTION(BlueprintCallable, Category = "Teleporter")`
- L55 _public prototype_ `void StartTeleport();` — `UFUNCTION(BlueprintNativeEvent, CallInEditor, Category = "Teleporter")` — Start teleporting, does a ray trace with the hand passed and calculates the locations for lerp movement in Teleport
- L59 _public prototype_ `void TeleportDone();` — `UFUNCTION(BlueprintNativeEvent, CallInEditor, Category = "Teleporter")` — Called when teleport is done for cleanup
- L63 _public prototype_ `void SetVisibility( const bool bVisible );` — `UFUNCTION(BlueprintCallable, Category = "Teleporter")` — Hide or show the teleporter visuals
- L67 _public prototype_ `void SetColor( const FLinearColor& Color );` — `UFUNCTION(BlueprintCallable, Category = "Teleporter")` — Sets the color for the teleporter visuals
- L71 _public prototype_ `float GetSlideDelta( UVREditorInteractor* Interactor, const bool Axis );` — `UFUNCTION(BlueprintNativeEvent, Category = "Teleporter")` — Get slide delta to push/pull or scale the teleporter
- L76 _private prototype_ `virtual void Tick(const float DeltaTime) override;`
- L77 _private function_ `virtual bool IsEditorOnly() const final`
- L85 _private prototype_ `void StartAiming( class UViewportInteractor* Interactor );` — `UFUNCTION(BlueprintCallable, Category = "Teleporter")` — Functions we call to handle teleporting in navigation mode
- L89 _private prototype_ `void StopAiming();` — `UFUNCTION(BlueprintCallable, Category = "Teleporter")` — Cancel teleport aiming mode without doing the teleport
- L93 _private prototype_ `void DoTeleport();` — `UFUNCTION(BlueprintCallable, Category = "Teleporter")` — Do and finalize teleport.
- L99 _private prototype_ `UViewportInteractor* GetInteractorTryingTeleport() const;` — `UFUNCTION(BlueprintCallable, Category = "Teleporter")` — Get the actor we're currently trying to teleport with. Valid during aiming and teleporting.
- L102 _private prototype_ `void OnPreviewInputAction(class FEditorViewportClient& ViewportClient, UViewportInteractor* Interactor, const struct FViewportActionKeyInput& Action, bool& bOutIsInputCaptured, bool& bWasHandled);` — Called when the user presses a button on their motion controller device
- L106 _private prototype_ `void Teleport(const float DeltaTime);` — Move the roomspace using lerp towards the new location
- L109 _private prototype_ `void UpdateTeleportAim(const float DeltaTime);` — Updating aiming with teleport to end of laser and pulling and pushing
- L112 _private prototype_ `FVector UpdatePushPullTeleporter(class UVREditorInteractor* VREditorInteractor, const FVector& LaserPointerStart, const FVector& LaserPointerEnd, const bool bEnablePushPull = true);` — Helper function to push and pull the teleporter along the laser
- L115 _private prototype_ `void UpdateVisuals(const FVector& NewLocation);` — Figures out the new transforms for all the visuals based on the new location and the transforms of the HMD and motioncontrollers
- L118 _private prototype_ `void Show(const bool bShow);` — If we want to start showing or hiding the meshes
- L120 _private prototype_ `void UpdateFadingState(const float DeltaTime);`
- L123 _private prototype_ `float CalculateAnimatedScaleFactor() const;` — Calculated the scale for animation
- L127 _private member_ `TObjectPtr<UVREditorMode> VRMode;` — `UPROPERTY()` — The owning VR mode
- L137 _private member_ `EState TeleportingState;` — The current teleport state
- L140 _private member_ `float TeleportLerpAlpha;` — The current lerp of the teleport between the TeleportStartLocation and the TeleportGoalLocation
- L143 _private member_ `FVector TeleportStartLocation;` — Set on the current Roomspace location in the world in StartTeleport before doing the actual teleporting
- L146 _private member_ `FVector TeleportGoalLocation;` — The calculated goal location in StartTeleport to move the Roomspace to
- L150 _private member_ `TObjectPtr<UStaticMeshComponent> TeleportDirectionMeshComponent;` — `UPROPERTY()` — Visuals for the feet location of the teleporter with the same direction of the HMD yaw
- L154 _private member_ `TObjectPtr<UStaticMeshComponent> HMDMeshComponent;` — `UPROPERTY()` — Visuals for teleport HMD
- L158 _private member_ `TObjectPtr<UStaticMeshComponent> LeftMotionControllerMeshComponent;` — `UPROPERTY()` — Visuals for teleport left motion controller
- L162 _private member_ `TObjectPtr<UStaticMeshComponent> RightMotionControllerMeshComponent;` — `UPROPERTY()` — Visuals for teleport right motion controller
- L166 _private member_ `TObjectPtr<UMaterialInstanceDynamic> TeleportMID;` — `UPROPERTY()` — Dynamic material for teleport visuals
- L170 _private member_ `TObjectPtr<UViewportInteractor> InteractorTryingTeleport;` — `UPROPERTY()` — The interactor that started aiming to teleport
- L173 _private member_ `FVector OffsetDistance;` — When offset between the hoverlocation of the laser and the calculated  teleport
- L176 _private member_ `float TeleportGoalScale;` — The goal world to meters scale. This value is used to scale the visuals and will be used to set world to meters scale after teleporting
- L179 _private member_ `double DragRayLength;` — The current length of the laser where the teleport should be at
- L182 _private member_ `double DragRayLengthVelocity;` — The current drag velocity to push or pull the teleport along the laser
- L185 _private member_ `bool bPushedFromEndOfLaser;` — If the teleporter has been pushed by the trackpad
- L188 _private member_ `bool bInitialTeleportAim;` — Is this the first time aiming for teleporting, we don't have to smooth movement for initial tick
- L191 _private member_ `float FadeAlpha;` — Fade alpha, for visibility transitions
- L194 _private member_ `TOptional<bool> bShouldBeVisible;` — If the teleporter should fade in
- L197 _private member_ `uint32 TeleportTickDelay;` — Delay to start the actual moving to the end location

#### enum `AVREditorTeleporter::EState`  
`enum EState`  
_L129-134_
- L131 _public enumerator_ `None = 0` — When not aiming for a teleport
- L132 _public enumerator_ `Aiming = 1` — Aiming at the end of the laser, user can also scale using touchpad/analog stick
- L133 _public enumerator_ `Teleporting = 3` — Currently teleporting from one location to another with lerp

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API VREDITOR_API`

### `Source/Editor/VREditor/Public/UI/VREditorFloatingUI.h` (Public)


#### struct `FVREditorFloatingUICreationContext`  
`struct UE_DEPRECATED(5.7, "VR Editor mode is deprecated; use the XR Creative Framework plugin instead.") FVREditorFloatingUICreationContext`  
_L25-70_
- reflection: `USTRUCT(BlueprintType)`
- desc: Creation parameters for AVREditorFloatingUI
- L33 _public member_ `TSubclassOf<UUserWidget> WidgetClass;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR Mode UI")` — Widget to open in the VR window. null to close an open window (if if matches the PanelID)
- L38 _public member_ `FName PanelID;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR Mode UI")` — ID that the UI system will use to identify the panel. MUST BE UNIQUE!
- L41 _public member_ `TObjectPtr<AActor> ParentActor = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Virtual Production UI")`
- L45 _public member_ `FTransform PanelSpawnOffset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR Mode UI")` — Optional offset from HMD where the window opens. Pass FTransform::Identity for default logic - window will open at controller location.
- L49 _public member_ `FVector2D PanelSize = FVector2D(0.0f);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR Mode UI")` — Panel size. Should match the size of the UMG passed in.
- L53 _public member_ `TObjectPtr<UStaticMesh> PanelMesh = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR Mode UI")` — Optional custom mesh to use for the VR window.
- L57 _public member_ `float EditorUISize = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR Mode UI")` — Optional override for "VREd.EditorUISize". Leave at 0 for default.
- L61 _public member_ `bool bHideWindowHandles = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR Mode UI")` — Turn off handles under window? (X-To-Close, movement bar...)
- L65 _public member_ `bool bMaskOutWidgetBackground = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Virtual Production UI")` — Turn off the widget's background to create a see-through look.
- L69 _public member_ `bool bNoCloseButton = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Virtual Production UI")` — If bHideWindowHandles is false, this window doesn't have a close button. (

#### class `AVREditorFloatingUI`  
`class UE_DEPRECATED(5.7, "VR Editor mode is deprecated; use the XR Creative Framework plugin instead.") AVREditorFloatingUI : public AVREditorBaseActor`  
_L77-251_
- reflection: `UCLASS()`
- inherits: `AVREditorBaseActor`
- desc: Represents an interactive floating UI panel in the VR Editor
- L84 _public prototype_ `AVREditorFloatingUI(const FObjectInitializer& ObjectInitializer);` — Default constructor which sets up safe defaults
- L87 _public prototype_ `void SetSlateWidget( class UVREditorUISystem& InitOwner, const VREditorPanelID& InID, const TSharedRef<SWidget>& InitSlateWidget, const FIntPoint InitResolution, const float InitScale, const EDockedTo InitDockedTo );` — Creates a FVREditorFloatingUI using a Slate widget, and sets up safe defaults
- L88 _public prototype_ `void SetSlateWidget(const TSharedRef<SWidget>& InitSlateWidget);`
- L91 _public prototype_ `void SetUMGWidget(class UVREditorUISystem& InitOwner, const VREditorPanelID& InID, class TSubclassOf<class UUserWidget> InitUserWidgetClass, const FIntPoint InitResolution, const float InitScale, const EDockedTo InitDockedTo);` — Creates a FVREditorFloatingUI using a UMG user widget, and sets up safe defaults
- L93 _public prototype_ `virtual void TickManually(float DeltaTime) override;`
- L96 _public function_ `bool IsUIVisible() const` — @return Returns true if the UI is visible (or wants to be visible -- it might be transitioning
- L102 _public prototype_ `void ShowUI( const bool bShow, const bool bAllowFading = true, const float InitFadeDelay = 0.0f, const bool bInClearWidgetOnHide = false );` — Shows or hides the UI (also enables collision, and performs a transition effect)
- L105 _public prototype_ `void SetResolution(const FIntPoint& InResolution);` — Sets the resolution of this floating UI panel and resets the window mesh accordingly.
- L108 _public function_ `class UVREditorWidgetComponent* GetWidgetComponent()` — Returns the widget component for this UI, or nullptr if not spawned right now
- L114 _public function_ `class UStaticMeshComponent* GetMeshComponent()` — Returns the mesh component for this UI, or nullptr if not spawned right now
- L120 _public prototype_ `FVector2D GetSize() const;` — Returns the actual size of the UI in either axis, after scaling has been applied.  Does not take into animation or world scaling
- L123 _public prototype_ `float GetScale() const;` — Gets the scale
- L126 _public prototype_ `void SetScale(const float NewSize, const bool bScaleWidget = true);` — Sets a new size for the UI
- L129 _public prototype_ `void SetWidgetComponentScale(const FVector& InScale);` — Set the widget scale
- L132 _public prototype_ `virtual void SetTransform( const FTransform& Transform ) override;` — Sets the UI transform
- L135 _public prototype_ `virtual void BeginDestroy() override;` — AActor overrides
- L136 _public prototype_ `virtual void Destroyed() override;`
- L138 _public prototype_ `void CleanupWidgetReferences();`
- L140 _public function_ `virtual bool IsEditorOnly() const final`
- L147 _public function_ `UVREditorUISystem& GetOwner()` — Returns the owner of this object
- L154 _public function_ `const UVREditorUISystem& GetOwner() const` — Returns the owner of this object (const)
- L162 _public function_ `template<class T> T* GetUserWidget() const` — Returns casted userwidget
- L168 _public prototype_ `UUserWidget* GetUserWidget();` — Gets the current user widget of this floating UI, return nullptr if using slate widget
- L171 _public prototype_ `float GetInitialScale() const;` — Gets the initial size of this UI
- L174 _public prototype_ `virtual void SetupWidgetComponent();` — Called to finish setting everything up, after a widget has been assigned
- L177 _public prototype_ `VREditorPanelID GetID() const;` — Gets the ID of this panel.
- L180 _public prototype_ `TSharedPtr<SWidget> GetSlateWidget() const;` — Gets the current slate widget.
- L183 _public prototype_ `void SetWindowMesh(class UStaticMesh* InWindowMesh);` — Set mesh on window mesh component.
- L187 _public member_ `FVREditorFloatingUICreationContext CreationContext;` — `UPROPERTY()` — All params used to create this panel if this panel has a UMG widget and was created via BP. Invalid otherwise.
- L192 _protected prototype_ `FVector CalculateAnimatedScale() const;` — Returns a scale to use for this widget that takes into account animation
- L195 _protected prototype_ `virtual void SetCollision(const ECollisionEnabled::Type InCollisionType, const ECollisionResponse InCollisionResponse, const ECollisionChannel InCollisionChannel);` — Set collision on components
- L200 _private prototype_ `virtual void UpdateFadingState( const float DeltaTime );` — Called after spawning, and every Tick, to update opacity of the widget
- L204 _protected member_ `TSharedPtr<SWidget> SlateWidget;` — Slate widget we're drawing, or null if we're drawing a UMG user widget
- L208 _protected member_ `TObjectPtr<UUserWidget> UserWidget;` — `UPROPERTY()` — UMG user widget we're drawing, or nullptr if we're drawing a Slate widget
- L212 _protected member_ `TObjectPtr<class UVREditorWidgetComponent> WidgetComponent;` — `UPROPERTY()` — When in a spawned state, this is the widget component to represent the widget
- L216 _protected member_ `TObjectPtr<class UStaticMeshComponent> WindowMeshComponent;` — `UPROPERTY()` — The floating window mesh
- L219 _protected member_ `FIntPoint Resolution;` — Resolution we should draw this UI at, regardless of scale
- L221 _protected member_ `float WorldPlacedScaleFactor;`
- L226 _private member_ `class UVREditorUISystem* Owner;` — Owning object
- L230 _private member_ `TObjectPtr<UClass> UserWidgetClass;` — `UPROPERTY()` — Class of the UMG widget we're spawning
- L234 _private member_ `TOptional<bool> bShouldBeVisible;` — True if the UI wants to be visible, or false if it wants to be hidden.  Remember, we might still be visually transitioning between states
- L237 _private member_ `float FadeAlpha;` — Fade alpha, for visibility transitions
- L240 _private member_ `float FadeDelay;` — Delay to fading in or out. Set on ShowUI and cleared on finish of fade in/out
- L243 _private member_ `float InitialScale;` — The starting scale of this UI
- L246 _private member_ `VREditorPanelID UISystemID;` — The ID of this floating UI.
- L249 _private member_ `bool bClearWidgetOnHide;` — Null out the widget when hidden.

#### Free symbols / members of external scopes

- L19 _typedef_ `typedef FName VREditorPanelID;`

### `Source/Editor/VREditor/Public/UI/VREditorUISystem.h` (Public)


#### enum `EVREditorAnimationState`  
`enum class UE_DEPRECATED(5.7, "VR Editor mode is deprecated; use the XR Creative Framework plugin instead.") EVREditorAnimationState : uint8`  
_L42-47_
- desc: Stores the animation playback state of a VR UI element
- L44 _public enumerator_ `None`
- L45 _public enumerator_ `Forward`
- L46 _public enumerator_ `Backward`

#### struct `FVRButton`  
`struct UE_DEPRECATED(5.7, "VR Editor mode is deprecated; use the XR Creative Framework plugin instead.") FVRButton`  
_L51-98_
- reflection: `USTRUCT()`
- desc: Structure to keep track of all relevant interaction and animation elements of a VR Button
- L57 _public member_ `TObjectPtr<UVREditorWidgetComponent> ButtonWidget;` — `UPROPERTY()` — Pointer to button
- L60 _public member_ `EVREditorAnimationState AnimationDirection;` — Animation playback state of the button
- L63 _public member_ `FVector OriginalRelativeScale;` — Original relative scale of the button element
- L66 _public member_ `float CurrentScale;` — Current scale of the button element
- L69 _public member_ `float MinScale;` — Minimum scale of the button element
- L72 _public member_ `float MaxScale;` — Maximum scale of the button element
- L75 _public member_ `float ScaleRate;` — Rate at which the button changes scale. Currently the same for scaling up and scaling down.
- L77 _public function_ `FVRButton() : ButtonWidget(nullptr), AnimationDirection(EVREditorAnimationState::None), OriginalRelativeScale(FVector::ZeroVector), CurrentScale(1.0f), MinScale(1.0f), MaxScale(1.10f), ScaleRate(2.0f)`
- L87 _public function_ `FVRButton(class UVREditorWidgetComponent* InButtonWidget, FVector InOriginalScale, EVREditorAnimationState InAnimationDirection = EVREditorAnimationState::None, float InCurrentScale = 1.0f, float InMinScale = 1.0f, float InMaxScale = 1.25f, float InScaleRate = 2.0f) : ButtonWidget(InButtonWidget), AnimationDirection(InAnimationDirection), OriginalRelativeScale(InOriginalScale), CurrentScale(InCurrentScale), MinScale(InMinScale), MaxScale(InMaxScale), ScaleRate(InScaleRate)`

#### class `UVREditorUISystem`  
`class UE_DEPRECATED(5.7, "VR Editor mode is deprecated; use the XR Creative Framework plugin instead.") UVREditorUISystem : public UObject`  
_L105-447_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: VR Editor user interface manager
- L112 _public prototype_ `UVREditorUISystem();` — Default constructor
- L115 _public prototype_ `void Init(class UVREditorMode* InVRMode);` — Initializes default values for the UISystem and creates the UI panels
- L117 _public prototype_ `void UpdateInteractors();`
- L120 _public prototype_ `void Shutdown();` — Shuts down the UISystem whenever the mode is exited
- L123 _public prototype_ `void Tick( class FEditorViewportClient* ViewportClient, const float DeltaTime );` — Called by VREditorMode to update us every frame
- L126 _public prototype_ `void Render( const class FSceneView* SceneView, class FViewport* Viewport, class FPrimitiveDrawInterface* PDI );` — Called by VREditorMode to draw debug graphics every frame
- L129 _public function_ `class UVREditorMode& GetOwner()` — Gets the owner of this system
- L135 _public function_ `const class UVREditorMode& GetOwner() const` — Gets the owner of this system (const)
- L141 _public prototype_ `bool IsShowingEditorUIPanel(const VREditorPanelID& InPanelID) const;` — Returns true if the specified editor UI panel is currently visible
- L144 _public prototype_ `void ShowEditorUIPanel(const UWidgetComponent* WidgetComponent, UVREditorInteractor* Interactor, const bool bShouldShow, const bool bSpawnInFront = false, const bool bDragFromOpen = false, const bool bPlaySound = true);` — Sets whether the specified editor UI panel should be visible.  Any other UI floating off this hand will be dismissed when showing it.
- L145 _public prototype_ `void ShowEditorUIPanel(const VREditorPanelID& InPanelID, UVREditorInteractor* Interactor, const bool bShouldShow, const bool bSpawnInFront = false, const bool bDragFromOpen = false, const bool bPlaySound = true);`
- L146 _public prototype_ `void ShowEditorUIPanel(AVREditorFloatingUI* Panel, UVREditorInteractor* Interactor, const bool bShouldShow, const bool bSpawnInFront = false, const bool bDragFromOpen = false, const bool bPlaySound = true);`
- L149 _public prototype_ `bool IsShowingRadialMenu(const UVREditorInteractor* Interactor ) const;` — Returns true if the radial menu is visible on this hand
- L152 _public prototype_ `void TryToSpawnRadialMenu( UVREditorInteractor* Interactor, const bool bForceRefresh, const bool bPlaySound = true );` — Tries to spawn the radial menu (if the specified hand isn't doing anything else)
- L155 _public prototype_ `void HideRadialMenu(const bool bPlaySound = true, const bool bAllowFading = true);` — Hides the radial menu if the specified hand is showing it
- L158 _public prototype_ `void StartDraggingDockUI( class AVREditorDockableWindow* InitDraggingDockUI, UVREditorInteractor* Interactor, const float DockSelectDistance, const bool bPlaySound = true );` — Start dragging a dock window on the hand
- L161 _public prototype_ `FTransform MakeDockableUITransformOnLaser( AVREditorDockableWindow* InitDraggingDockUI, UVREditorInteractor* Interactor, const float DockSelectDistance ) const;` — Makes up a transform for a dockable UI when dragging it with a laser at the specified distance from the laser origin
- L164 _public prototype_ `FTransform MakeDockableUITransform( AVREditorDockableWindow* InitDraggingDockUI, UVREditorInteractor* Interactor, const float DockSelectDistance );` — Makes up a transform for a dockable UI when dragging it that includes the original offset from the laser's impact point
- L167 _public prototype_ `class AVREditorDockableWindow* GetDraggingDockUI() const;` — Returns the current dragged dock window, nullptr if none
- L170 _public prototype_ `void StopDraggingDockUI( UVREditorInteractor* VREditorInteractor, const bool bPlaySound = true );` — Resets all values to stop dragging the current dock window
- L173 _public prototype_ `bool IsDraggingDockUI();` — Are we currently dragging a dock window
- L175 _public prototype_ `bool IsInteractorDraggingDockUI( const UVREditorInteractor* Interactor ) const;`
- L178 _public prototype_ `bool IsDraggingPanelFromOpen() const;` — If a panel was opened and dragged with the UI interactor
- L181 _public prototype_ `void TogglePanelsVisibility();` — Hides and unhides all the editor UI panels
- L184 _public prototype_ `float GetMaxDockWindowSize() const;` — Get the maximum dock window size
- L187 _public prototype_ `float GetMinDockWindowSize() const;` — Get the minimum dock window size
- L190 _public prototype_ `void TogglePanelVisibility(const VREditorPanelID& InPanelID);` — Toggles the visibility of the panel, if the panel is in room space it will be hidden and docked to nothing
- L193 _public prototype_ `class AVREditorRadialFloatingUI* GetRadialMenuFloatingUI() const;` — Returns the radial widget so other classes, like the interactors, can access its functionality
- L200 _public prototype_ `static const TSharedRef<SWidget>& FindWidgetOfType(const TSharedRef<SWidget>& Content, FName WidgetType);` — Finds a widget with a given name inside the Content argument @param Content The widget to begin searching in @param The FName of the widget type to find.
- L207 _public prototype_ `static const bool FindAllWidgetsOfType(TArray<TSharedRef<SWidget>>& FoundWidgets, const TSharedRef<SWidget>& Content, FName WidgetType);` — Finds a widget with a given name inside the Content argument @param Content The widget to begin searching in @param The FName of the widget type to find.
- L210 _public prototype_ `void UpdateSequencerUI();` — Function to force an update of the Sequencer UI based on a change
- L213 _public prototype_ `void UpdateActorPreviewUI(TSharedRef<SWidget> InWidget, int32 Index, AActor *InActor );` — Function to force an update of the Actor Preview UI based on a change
- L216 _public prototype_ `void UpdateDetachedActorPreviewUI(TSharedRef<SWidget> InWidget, int32 Index);` — Function to force an update of the Actor Preview UI based on a change when the preview is detached from the actor
- L218 _public prototype_ `void UpdateExternalUMGUI(const struct FVREditorFloatingUICreationContext& CreationContext);`
- L220 _public prototype_ `void UpdateExternalSlateUI(TSharedRef<SWidget> InWidget, FName Name, FVector2D InSize);`
- L223 _public prototype_ `void TransitionWorld(UWorld* NewWorld, EEditorWorldExtensionTransitionState TransitionState);` — Transition the user widgets to a new world
- L225 _public function_ `UVRRadialMenuHandler* GetRadialMenuHandler()`
- L231 _public prototype_ `void OnHoverBeginEffect(UVREditorWidgetComponent* Button);` — Called when a laser or simulated mouse hover enters a button
- L233 _public prototype_ `void OnHoverEndEffect(UVREditorWidgetComponent* Button);` — Called when a laser or simulated mouse hover leaves a button
- L236 _public prototype_ `void SequencerOpenendFromRadialMenu(const bool bInOpenedFromRadialMenu = true);` — Set if sequencer was opened from the radial menu
- L239 _public prototype_ `bool CanScalePanel() const;` — If a dockable window can be scaled
- L242 _public prototype_ `class UVREditorInteractor* GetUIInteractor();` — Get the interactor that holds the radial menu
- L244 _public member_ `static const VREditorPanelID ContentBrowserPanelID;`
- L245 _public member_ `static const VREditorPanelID WorldOutlinerPanelID;`
- L246 _public member_ `static const VREditorPanelID DetailsPanelID;`
- L247 _public member_ `static const VREditorPanelID ModesPanelID;`
- L248 _public member_ `static const VREditorPanelID TutorialPanelID;`
- L249 _public member_ `static const VREditorPanelID WorldSettingsPanelID;`
- L250 _public member_ `static const VREditorPanelID ColorPickerPanelID;`
- L251 _public member_ `static const VREditorPanelID SequencerPanelID;`
- L252 _public member_ `static const VREditorPanelID InfoDisplayPanelID;`
- L253 _public member_ `static const VREditorPanelID RadialMenuPanelID;`
- L254 _public member_ `static const VREditorPanelID TabManagerPanelID;`
- L257 _public prototype_ `AVREditorFloatingUI* GetPanel(const VREditorPanelID& InPanelID) const;` — Get UI panel Actor from the passed ID
- L262 _protected prototype_ `void OnPreviewInputAction( class FEditorViewportClient& ViewportClient, UViewportInteractor* Interactor, const struct FViewportActionKeyInput& Action, bool& bOutIsInputCaptured, bool& bWasHandled );` — Called to "preview" an input event to get a first chance at it.
- L266 _protected prototype_ `void OnVRAction( class FEditorViewportClient& ViewportClient, UViewportInteractor* Interactor, const struct FViewportActionKeyInput& Action, bool& bOutIsInputCaptured, bool& bWasHandled );` — Called when the user presses a button on their motion controller device
- L270 _protected prototype_ `void OnVRHoverUpdate( UViewportInteractor* Interactor, FVector& HoverImpactPoint, bool& bWasHandled );` — Called every frame to update hover state
- L273 _protected prototype_ `void CreateUIs();` — Testing Slate UI
- L276 _protected prototype_ `void IsProxyTabSupported( FTabId TabId, bool& bOutIsTabSupported );` — Called by proxy tab manager to ask us whether we support the specified tab ID.  bOutIsTabSupported defaults to true.
- L282 _protected prototype_ `void OnProxyTabLaunched(TSharedPtr<SDockTab> NewTab);` — Called when the injected proxy tab manager reports a new tab has been launched, signaling an asset editor has been launched, but really it could be any major global tab.
- L285 _protected prototype_ `void OnAttentionDrawnToTab(TSharedPtr<SDockTab> NewTab);` — Called when the injected proxy tab manager reports needing to draw attention to a tab.
- L288 _protected prototype_ `void ShowAssetEditor();` — Show the asset editor if it's not currently visible.
- L291 _protected prototype_ `void OnAssetEditorOpened(UObject* Asset);` — Called when an asset editor opens an asset while in VR Editor Mode.
- L294 _protected prototype_ `void DockableAreaRestored();` — Can be used when the tab manager is restoring a dockable tab area
- L297 _protected prototype_ `void CreateVRColorPicker(const TSharedRef<SColorPicker>& ColorPicker);` — Creates a VR-specific color picker. Gets bound to SColorPicker's creation override delegate
- L300 _protected prototype_ `void DestroyVRColorPicker();` — Hides the VR-specific color picker. Gets bound to SColorPicker's destruction override delegate
- L303 _protected prototype_ `void MakeUniformGridMenu( const TSharedRef<FMultiBox>& MultiBox, const TSharedRef<SMultiBoxWidget>& MultiBoxWidget, int32 Columns);` — Makes a uniform grid widget from the menu information contained in a MultiBox and MultiBoxWidget
- L305 _protected prototype_ `void MakeRadialBoxMenu(const TSharedRef<FMultiBox>& MultiBox, const TSharedRef<SMultiBoxWidget>& MultiBoxWidget, float RadiusRatioOverride, FName ButtonTypeOverride);` — Makes a radial box widget from the menu information contained in a MultiBox and MultiBoxWidget
- L308 _protected prototype_ `TSharedRef<SWidget> AddHoverableButton(TSharedRef<SWidget>& BlockWidget, FName ButtonType, TSharedRef<SOverlay>& TestOverlay);` — Adds a hoverable button of a given type to an overlay, using menu data from a BlockWidget
- L310 _protected prototype_ `TSharedRef<SWidget> SetButtonFormatting(TSharedRef<SWidget>& BlockWidget, float WrapSize);` — Sets the text wrap size of the text block element nested in a BlockWidget
- L313 _protected prototype_ `void BuildRadialMenuWidget();` — Builds the radial menu Slate widget
- L315 _protected prototype_ `void BuildNumPadWidget();` — Builds the numpad Slate widget
- L317 _protected prototype_ `void SwapRadialMenu();` — Swaps the content of the radial menu between the radial menu and the numpad
- L323 _protected prototype_ `void HandleEditorModeChanged(const FEditorModeID& EditorModeID, bool IsEnabled);` — Handles being notified when any editor mode changes to see if any VR Editor UI needs to change. @param Mode The mode that changed. @param IsEnabled true if the mode is enabled, otherwise false.
- L326 _protected prototype_ `void ResetAll();` — Reset function that puts you back in placement mode, closes all UIs, etc.
- L329 _protected prototype_ `bool CheckForVRDragDrop();` — The VR Editor UI System's rules for when drag drop should be checked for
- L332 _protected prototype_ `bool ShouldPreviewPanel();` — Preview the UI panel's location if spawning with the UI interactor, else spawn immediately
- L335 _protected prototype_ `void ToggledDebugMode(bool bDebugModeEnabled);` — When VR Mode debug was toggled.
- L337 _protected prototype_ `void OnCloseAssetEditor(UObject* Asset, EAssetEditorCloseReason CloseReason);`
- L342 _protected member_ `TObjectPtr<class UVREditorMode> VRMode;` — `UPROPERTY()` — Owning object
- L346 _protected member_ `TMap<FName, TObjectPtr<class AVREditorFloatingUI>> FloatingUIs;` — `UPROPERTY()` — All of the floating UIs.  These may or may not be visible (spawned)
- L350 _protected member_ `TMap<FName, TObjectPtr<class AActor>> PreviewWindowInfo;` — `UPROPERTY()` — All of the preview window info.
- L354 _protected member_ `TObjectPtr<class AVREditorFloatingUI> InfoDisplayPanel;` — `UPROPERTY()` — Our Quick Menu UI
- L360 _protected member_ `TWeakPtr<SWidget> CurrentWidgetOnInfoDisplay;` — The current widget used on the info display. Often we wrap a widget in a widget to configure the settings (e.g. DPI). To check the info display widget with other widgets we need that wrapper widget.
- L364 _protected member_ `TObjectPtr<class AVREditorRadialFloatingUI> QuickRadialMenu;` — `UPROPERTY()` — The Radial Menu UI
- L367 _protected member_ `float RadialMenuHideDelayTime;` — The time since the radial menu was updated
- L370 _protected member_ `bool bRadialMenuVisibleAtSwap;` — True if the radial menu was visible when the content was swapped
- L373 _protected member_ `bool bRadialMenuIsNumpad;` — True if the radial menu is currently displaying the numpad
- L380 _protected member_ `class UVREditorInteractor* InteractorDraggingUI;` — Interactor that is dragging the UI
- L383 _protected member_ `FTransform DraggingUIOffsetTransform;` — Offset transform from room-relative transform to the object where we picked it up at
- L387 _protected member_ `TObjectPtr<class AVREditorDockableWindow> DraggingUI;` — `UPROPERTY()` — The current UI that is being dragged
- L391 _protected member_ `TObjectPtr<class AVREditorDockableWindow> ColorPickerUI;` — `UPROPERTY()` — The color picker dockable window
- L398 _protected member_ `TObjectPtr<class UVREditorInteractor> LaserInteractor;` — `UPROPERTY()` — Interactor that has a laser and is generally interacting with the scene
- L401 _protected member_ `TObjectPtr<class UVREditorInteractor> UIInteractor;` — `UPROPERTY()` — Interactor that usually accesses UI and other helper functionality
- L408 _protected member_ `TSharedPtr<FProxyTabmanager> ProxyTabManager;` — Allows us to steal the global tabs and show them in the world.
- L411 _protected member_ `bool bRefocusViewport;` — Set to true when we need to refocus the viewport.
- L414 _protected member_ `FVector LastDraggingHoverLocation;` — The last dragged hover location by the laser
- L418 _protected member_ `TArray<FVRButton> VRButtons;` — `UPROPERTY()` — All buttons created for the radial and quick menus
- L422 _protected member_ `TObjectPtr<UVRRadialMenuHandler> RadialMenuHandler;` — `UPROPERTY()` — The add-on that handles radial menu switching
- L425 _protected member_ `FOnRadialMenuGenerated ExistingActionsMenu;` — When replacing the actions menu, store off any existing actions
- L428 _protected member_ `FText ExistingActionsMenuLabel;` — When replacing the actions menu, store off the name of the existing actions menu
- L431 _protected member_ `FTimespan RadialMenuModifierSpawnTime;` — The time the modifier was pressed at to spawn the menu
- L434 _protected member_ `bool bSequencerOpenedFromRadialMenu;` — If sequenced was opened from the radial menu or somewhere else such as the content browser.
- L437 _protected member_ `bool bDragPanelFromOpen;` — If started dragging from opening a UI panel
- L440 _protected member_ `float DragPanelFromOpenTime;` — The time dragging a panel that was opened resulting in an instant drag
- L444 _protected member_ `bool bPanelCanScale;` — When started dragging from the radial menu we want the analog stick to be reset before the user is allowed to scale the panel. Otherwise the panel will immediately start scaling because the user is using the analog stick to aim at the radial menu items.
- L446 _protected member_ `FDelegateHandle AssetEditorCloseDelegate;`

#### Free symbols / members of external scopes

- L35 _typedef_ `typedef FName FEditorModeID;`
- L37 _typedef_ `typedef FName VREditorPanelID;`

### `Source/Editor/VREditor/Public/UI/VRRadialMenuHandler.h` (Public)


#### class `UVRRadialMenuHandler`  
`class UE_DEPRECATED(5.7, "VR Editor mode is deprecated; use the XR Creative Framework plugin instead.") UVRRadialMenuHandler : public UObject`  
_L25-90_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: VR Editor user interface manager
- L32 _public prototype_ `UVRRadialMenuHandler();` — Default constructor
- L35 _public prototype_ `void BuildRadialMenuCommands(FMenuBuilder& MenuBuilder, TSharedPtr<FUICommandList> CommandList, UVREditorMode* VRMode, float& RadiusOverride);` — Builds the current radial menu
- L38 _public prototype_ `void RegisterMenuGenerator(const FOnRadialMenuGenerated NewMenuGenerator, const bool bShouldAddToStack = true);` — Registers a new menu generator and replaces the currently displayed menu if the radial menu is open
- L40 _public function_ `FOnRadialMenuGenerated GetCurrentMenuGenerator()`
- L45 _public function_ `FOnRadialMenuGenerated GetHomeMenuGenerator()`
- L51 _public prototype_ `void BackOutMenu();` — Returns to the previous radial menu
- L54 _public prototype_ `void Home();` — Returns to the home menu
- L56 _public prototype_ `void Init(class UVREditorUISystem* InUISystem);`
- L60 _protected prototype_ `void HomeMenuGenerator(FMenuBuilder& MenuBuilder, TSharedPtr<FUICommandList> CommandList, UVREditorMode* VRMode, float& RadiusOverride);` — Functions to bind to each menu delegate
- L62 _protected prototype_ `void SnapMenuGenerator(FMenuBuilder& MenuBuilder, TSharedPtr<FUICommandList> CommandList, UVREditorMode* VRMode, float& RadiusOverride);`
- L64 _protected prototype_ `void GizmoMenuGenerator(FMenuBuilder& MenuBuilder, TSharedPtr<FUICommandList> CommandList, UVREditorMode* VRMode, float& RadiusOverride);`
- L66 _protected prototype_ `void EditMenuGenerator(FMenuBuilder& MenuBuilder, TSharedPtr<FUICommandList> CommandList, UVREditorMode* VRMode, float& RadiusOverride);`
- L68 _protected prototype_ `void SystemMenuGenerator(FMenuBuilder& MenuBuilder, TSharedPtr<FUICommandList> CommandList, UVREditorMode* VRMode, float& RadiusOverride);`
- L72 _protected member_ `FOnRadialMenuGenerated OnRadialMenuGenerated;`
- L74 _protected member_ `FOnRadialMenuGenerated HomeMenu;`
- L76 _protected member_ `FOnRadialMenuGenerated SnapMenu;`
- L78 _protected member_ `FOnRadialMenuGenerated GizmoMenu;`
- L80 _protected member_ `FOnRadialMenuGenerated EditMenu;`
- L82 _protected member_ `FOnRadialMenuGenerated SystemMenu;`
- L84 _protected member_ `static FText ActionMenuLabel;`
- L86 _protected member_ `class UVREditorUISystem* UIOwner;`
- L88 _protected member_ `TArray<FOnRadialMenuGenerated> MenuStack;`

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_DELEGATE_FourParams(FOnRadialMenuGenerated, FMenuBuilder&, TSharedPtr<FUICommandList>, UVREditorMode*, float&);`
- L19 _prototype_ `DECLARE_DELEGATE_FourParams(FOnRadialMenuGenerated, FMenuBuilder&, TSharedPtr<FUICommandList>, UVREditorMode*, float&);` — `UE_DEPRECATED(5.7, "VR Editor mode is deprecated; use the XR Creative Framework plugin instead.")`

### `Source/Editor/VREditor/Public/VREditorAssetContainer.h` (Public)


#### class `UVREditorAssetContainer`  
`class UE_DEPRECATED(5.7, "VR Editor mode is deprecated; use the XR Creative Framework plugin instead.") UVREditorAssetContainer : public UDataAsset`  
_L22-180_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDataAsset`
- desc: Asset container for VREditor.
- L33 _public member_ `TObjectPtr<USoundBase> DockableWindowCloseSound;` — `UPROPERTY(EditAnywhere, Category = Sound)`
- L36 _public member_ `TObjectPtr<USoundBase> DockableWindowOpenSound;` — `UPROPERTY(EditAnywhere, Category = Sound)`
- L39 _public member_ `TObjectPtr<USoundBase> DockableWindowDropSound;` — `UPROPERTY(EditAnywhere, Category = Sound)`
- L42 _public member_ `TObjectPtr<USoundBase> DockableWindowDragSound;` — `UPROPERTY(EditAnywhere, Category = Sound)`
- L45 _public member_ `TObjectPtr<USoundBase> DropFromContentBrowserSound;` — `UPROPERTY(EditAnywhere, Category = Sound)`
- L48 _public member_ `TObjectPtr<USoundBase> RadialMenuOpenSound;` — `UPROPERTY(EditAnywhere, Category = Sound)`
- L51 _public member_ `TObjectPtr<USoundBase> RadialMenuCloseSound;` — `UPROPERTY(EditAnywhere, Category = Sound)`
- L54 _public member_ `TObjectPtr<USoundBase> TeleportSound;` — `UPROPERTY(EditAnywhere, Category = Sound)`
- L57 _public member_ `TObjectPtr<USoundCue> ButtonPressSound;` — `UPROPERTY(EditAnywhere, Category = Sound)`
- L60 _public member_ `TObjectPtr<USoundBase> AutoScaleSound;` — `UPROPERTY(EditAnywhere, Category = Sound)`
- L67 _public member_ `TObjectPtr<UStaticMesh> GenericHMDMesh;` — `UPROPERTY(EditAnywhere, Category = Mesh)`
- L70 _public member_ `TObjectPtr<UStaticMesh> PlaneMesh;` — `UPROPERTY(EditAnywhere, Category = Mesh)`
- L73 _public member_ `TObjectPtr<UStaticMesh> CylinderMesh;` — `UPROPERTY(EditAnywhere, Category = Mesh)`
- L76 _public member_ `TObjectPtr<UStaticMesh> LaserPointerStartMesh;` — `UPROPERTY(EditAnywhere, Category = Mesh)`
- L79 _public member_ `TObjectPtr<UStaticMesh> LaserPointerMesh;` — `UPROPERTY(EditAnywhere, Category = Mesh)`
- L82 _public member_ `TObjectPtr<UStaticMesh> LaserPointerEndMesh;` — `UPROPERTY(EditAnywhere, Category = Mesh)`
- L85 _public member_ `TObjectPtr<UStaticMesh> LaserPointerHoverMesh;` — `UPROPERTY(EditAnywhere, Category = Mesh)`
- L88 _public member_ `TObjectPtr<UStaticMesh> VivePreControllerMesh;` — `UPROPERTY(EditAnywhere, Category = Mesh)`
- L91 _public member_ `TObjectPtr<UStaticMesh> OculusControllerMesh;` — `UPROPERTY(EditAnywhere, Category = Mesh)`
- L94 _public member_ `TObjectPtr<UStaticMesh> GenericControllerMesh;` — `UPROPERTY(EditAnywhere, Category = Mesh)`
- L97 _public member_ `TObjectPtr<UStaticMesh> TeleportRootMesh;` — `UPROPERTY(EditAnywhere, Category = Mesh)`
- L100 _public member_ `TObjectPtr<UStaticMesh> WindowMesh;` — `UPROPERTY(EditAnywhere, Category = Mesh)`
- L103 _public member_ `TObjectPtr<UStaticMesh> WindowSelectionBarMesh;` — `UPROPERTY(EditAnywhere, Category = Mesh)`
- L106 _public member_ `TObjectPtr<UStaticMesh> WindowCloseButtonMesh;` — `UPROPERTY(EditAnywhere, Category = Mesh)`
- L109 _public member_ `TObjectPtr<UStaticMesh> RadialMenuMainMesh;` — `UPROPERTY(EditAnywhere, Category = Mesh)`
- L112 _public member_ `TObjectPtr<UStaticMesh> RadialMenuPointerMesh;` — `UPROPERTY(EditAnywhere, Category = Mesh)`
- L115 _public member_ `TObjectPtr<UStaticMesh> PointerCursorMesh;` — `UPROPERTY(EditAnywhere, Category = Mesh)`
- L118 _public member_ `TObjectPtr<UStaticMesh> LineSegmentCylinderMesh;` — `UPROPERTY(EditAnywhere, Category = Mesh)`
- L121 _public member_ `TObjectPtr<UStaticMesh> JointSphereMesh;` — `UPROPERTY(EditAnywhere, Category = Mesh)`
- L124 _public member_ `TObjectPtr<UStaticMesh> DockingButtonMesh;` — `UPROPERTY(EditAnywhere, Category = Mesh)`
- L131 _public member_ `TObjectPtr<UMaterialInterface> GridMaterial;` — `UPROPERTY(EditAnywhere, Category = Material)`
- L134 _public member_ `TObjectPtr<UMaterialInterface> LaserPointerMaterial;` — `UPROPERTY(EditAnywhere, Category = Material)`
- L137 _public member_ `TObjectPtr<UMaterialInterface> LaserPointerTranslucentMaterial;` — `UPROPERTY(EditAnywhere, Category = Material)`
- L140 _public member_ `TObjectPtr<UMaterial> WorldMovementPostProcessMaterial;` — `UPROPERTY(EditAnywhere, Category = Material)`
- L143 _public member_ `TObjectPtr<UMaterialInterface> TextMaterial;` — `UPROPERTY(EditAnywhere, Category = Material)`
- L146 _public member_ `TObjectPtr<UMaterialInterface> VivePreControllerMaterial;` — `UPROPERTY(EditAnywhere, Category = Material)`
- L149 _public member_ `TObjectPtr<UMaterialInterface> OculusControllerMaterial;` — `UPROPERTY(EditAnywhere, Category = Material)`
- L152 _public member_ `TObjectPtr<UMaterialInterface> TeleportMaterial;` — `UPROPERTY(EditAnywhere, Category = Material)`
- L155 _public member_ `TObjectPtr<UMaterialInterface> WindowMaterial;` — `UPROPERTY(EditAnywhere, Category = Material)`
- L158 _public member_ `TObjectPtr<UMaterialInterface> WindowTranslucentMaterial;` — `UPROPERTY(EditAnywhere, Category = Material)`
- L161 _public member_ `TObjectPtr<UMaterial> LineMaterial;` — `UPROPERTY(EditAnywhere, Category = Material)`
- L164 _public member_ `TObjectPtr<UMaterialInterface> TranslucentTextMaterial;` — `UPROPERTY(EditAnywhere, Category = Material)`
- L167 _public member_ `TObjectPtr<UMaterialInterface> WidgetMaterial;` — `UPROPERTY(EditAnywhere, Category = Material)`
- L171 _public member_ `TObjectPtr<UMaterialInterface> CameraWidgetMaterial;` — `UPROPERTY(EditAnywhere, Category = Material)` — Specific material for camera widgets that operates in linear color space
- L179 _public member_ `TObjectPtr<UFont> TextFont;` — `UPROPERTY(EditAnywhere, Category = Font)`

### `Source/Editor/VREditor/Public/VREditorBaseActor.h` (Public)


#### class `AVREditorBaseActor`  
`class UE_DEPRECATED(5.7, "VR Editor mode is deprecated; use the XR Creative Framework plugin instead.") AVREditorBaseActor : public AActor`  
_L14-141_
- reflection: `UCLASS()`
- inherits: `AActor`
- desc: Represents an actor specifically for VR Editor that has roomspace transformation
- L21 _public prototype_ `AVREditorBaseActor();` — Default constructor which sets up safe defaults
- L24 _public prototype_ `void SetVRMode( class UVREditorMode* InVRMode );` — Sets the owning VR mode
- L41 _public prototype_ `virtual void TickManually( float DeltaTime );` — Called by the UI system to tick this UI every frame.  We can't use AActor::Tick() because this actor can exist in the editor's world, which never ticks.
- L44 _public function_ `virtual void SetTransform( const FTransform& Transform )` — Sets the transf
- L47 _public prototype_ `void SetRelativeOffset( const FVector& InRelativeOffset );` — Sets the relative offset of the UI
- L50 _public prototype_ `void SetLocalRotation( const FRotator& InRelativeRotation );` — Sets the local rotation of the UI
- L53 _public function_ `EDockedTo GetDockedTo() const` — Returns what we're docked to, if anything
- L59 _public function_ `EDockedTo GetPreviouslyDockedTo() const` — Returns what we were previously docked to
- L65 _public prototype_ `void SetDockedTo( const EDockedTo NewDockedTo );` — Sets what this UI is docked to
- L68 _public prototype_ `void MoveTo( const FTransform& ResultTransform, const float TotalMoveToTime, const EDockedTo ResultDock );` — Start moving towards a transform
- L71 _public prototype_ `void StopMoveTo();` — Abort moving to transform and move instant to MoveToTransform
- L74 _public prototype_ `FTransform MakeUITransformLockedToHand( class UViewportInteractor* Interactor, const bool bOnArm, const FVector& InRelativeOffset, const FRotator& InLocalRotation );` — Get a relative transform from the hand
- L79 _protected prototype_ `void UpdateTransformIfDocked();` — Called every tick to keep the UI position up to date
- L82 _protected prototype_ `FTransform MakeUITransformLockedToHand( class UViewportInteractor* Interactor, const bool bOnArm );` — Given a hand to lock to, returns a transform to place UI at that hand's location and orientation
- L86 _protected prototype_ `FTransform MakeUITransformLockedToRoom();` — Create a room transform with the RelativeOffset and LocalRotation
- L89 _protected prototype_ `void TickMoveTo( const float DeltaTime );` — Updates the lerp movement
- L92 _protected function_ `virtual FTransform MakeCustomUITransform()` — Called when DockTo state is custom, needs to be implemented by derived classes
- L95 _protected function_ `virtual void UpdateFadingState( const float DeltaTime )` — Called after spawning, and every Tick, to update opacity of the actor, has to be implemented by the derived actor
- L98 _protected member_ `float Scale;` — How big the actor should be
- L105 _protected member_ `TObjectPtr<class UVREditorMode> VRMode;` — `UPROPERTY()` — The VR mode that owns this actor
- L110 _private member_ `FRotator LocalRotation;` — Local rotation of the UI
- L113 _private member_ `FVector RelativeOffset;` — Relative offset of the UI
- L116 _private member_ `EDockedTo DockedTo;` — What the UI is attached to
- L119 _private member_ `EDockedTo PreviousDockedTo;` — What was the UI previously attached to
- L122 _private member_ `bool bIsMoving;` — If the UI is currently moving
- L125 _private member_ `FTransform MoveToTransform;` — The end transform to move to
- L128 _private member_ `FTransform StartMoveToTransform;` — The actor transform when started moving
- L131 _private member_ `float MoveToAlpha;` — Current lerp alpha
- L134 _private member_ `float MoveToTime;` — Total time to move to the end transform
- L137 _private member_ `EDockedTo MoveToResultDock;` — Dock state to switch to when finished moving
- L140 _private member_ `TOptional<FTransform> LastDockedUIToWorld;` — When docked, our transform last frame.  This is used for smoothing

#### enum `AVREditorBaseActor::EDockedTo`  
`enum class EDockedTo`  
_L27-37_
- desc: Possible UI attachment points
- L29 _public enumerator_ `Nothing`
- L30 _public enumerator_ `LeftHand`
- L31 _public enumerator_ `RightHand`
- L32 _public enumerator_ `LeftArm`
- L33 _public enumerator_ `RightArm`
- L34 _public enumerator_ `Room`
- L35 _public enumerator_ `Custom`
- L36 _public enumerator_ `Dragging`

### `Source/Editor/VREditor/Public/VREditorInteractor.h` (Public)


#### enum `EControllerType`  
`enum class UE_DEPRECATED(5.7, "VR Editor mode is deprecated; use the XR Creative Framework plugin instead.") EControllerType : uint8`  
_L23-30_
- reflection: `UENUM(BlueprintType)`
- L25 _public enumerator_ `Laser`
- L26 _public enumerator_ `AssistingLaser`
- L27 _public enumerator_ `UI`
- L28 _public enumerator_ `Navigation`
- L29 _public enumerator_ `Unknown`

#### enum `ETouchSwipeDirection`  
`enum class UE_DEPRECATED(5.7, "VR Editor mode is deprecated; use the XR Creative Framework plugin instead.") ETouchSwipeDirection : uint8`  
_L34-41_
- reflection: `UENUM(BlueprintType)`
- desc: Directions the trackpad can be swiped to
- L36 _public enumerator_ `None = 0`
- L37 _public enumerator_ `Left = 1`
- L38 _public enumerator_ `Right = 2`
- L39 _public enumerator_ `Up = 3`
- L40 _public enumerator_ `Down = 4`

#### class `UVREditorInteractor`  
`class UE_DEPRECATED(5.7, "VR Editor mode is deprecated; use the XR Creative Framework plugin instead.") UVREditorInteractor : public UViewportInteractor`  
_L47-515_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType)`
- inherits: `UViewportInteractor`
- desc: VREditor default interactor
- L54 _public prototype_ `UVREditorInteractor();` — Default constructor
- L57 _public function_ `class UVREditorMode& GetVRMode()` — Gets the owner of this system
- L63 _public function_ `const class UVREditorMode& GetVRMode() const` — Gets the owner of this system (const)
- L69 _public function_ `const TMap<FKey, FViewportActionKeyInput>& GetKeyToActionMap() const` — Gets the key-to-action map (const)
- L74 _public prototype_ `virtual TMap<FViewportActionKeyInput, TArray<FKey>> GetKnownActionMappings(EControllerHand InHand = EControllerHand::AnyHand, FName InHMDDeviceType = NAME_None) const;`
- L78 _public prototype_ `void Init( class UVREditorMode* InVRMode );` — `UFUNCTION(BlueprintNativeEvent, CallInEditor, Category = "UVREditorInteractor")` — Initialize default values
- L82 _public prototype_ `void SetupComponent( AActor* OwningActor );` — `UFUNCTION(BlueprintNativeEvent, CallInEditor, Category = "UVREditorInteractor")` — Sets up all components
- L86 _public prototype_ `virtual void Shutdown_Implementation() override;` — ViewportInteractorInterface overrides
- L87 _public prototype_ `virtual void Tick_Implementation( const float DeltaTime ) override;`
- L88 _public prototype_ `virtual void CalculateDragRay( double& InOutDragRayLength, double& InOutDragRayVelocity ) override;`
- L92 _public prototype_ `FName GetHMDDeviceType() const;` — `UFUNCTION(BlueprintCallable, Category = "UVREditorInteractor")` — @return Returns the type of HMD we're dealing with
- L94 _public prototype_ `virtual FHitResult GetHitResultFromLaserPointer( TArray<AActor*>* OptionalListOfIgnoredActors = nullptr, const EHitResultGizmoFilterMode GizmoFilerMode = EHitResultGizmoFilterMode::All, TArray<UClass*>* ObjectsInFrontOfGizmo = nullptr, const bool bEvenIfBlocked = false, const float LaserLengthOverride = 0.0f ) override;`
- L96 _public prototype_ `virtual void ResetHoverState() override;`
- L97 _public prototype_ `virtual bool IsModifierPressed() const override;`
- L98 _public prototype_ `virtual void PreviewInputKey( class FEditorViewportClient& ViewportClient, FViewportActionKeyInput& Action, const FKey Key, const EInputEvent Event, bool& bOutWasHandled ) override;`
- L99 _public prototype_ `virtual void HandleInputKey( class FEditorViewportClient& ViewportClient, FViewportActionKeyInput& Action, const FKey Key, const EInputEvent Event, bool& bOutWasHandled ) override;`
- L100 _public prototype_ `virtual bool GetTransformAndForwardVector( FTransform& OutHandTransform, FVector& OutForwardVector ) const override;`
- L101 _public prototype_ `virtual void HandleInputAxis( FEditorViewportClient& ViewportClient, FViewportActionKeyInput& Action, const FKey Key, const float Delta, const float DeltaTime, bool& bOutWasHandled ) override;`
- L104 _public prototype_ `void ToggleSequencerScrubbingMode();` — Toggles whether or not this controller is being used to scrub sequencer
- L107 _public prototype_ `bool IsScrubbingSequencer() const;` — Returns whether or not this controller is being used to scrub sequencer
- L111 _public prototype_ `class UMotionControllerComponent* GetMotionControllerComponent() const;` — `UFUNCTION(BlueprintCallable, Category = "UVREditorInteractor")` — Get the motioncontroller component of this interactor
- L116 _public prototype_ `void SetControllerHandSide( const FName InControllerHandSide );` — `UFUNCTION(BlueprintCallable, Category = "UVREditorInteractor")` — Sets the EControllerHand for this motioncontroller
- L120 _public prototype_ `FName GetControllerHandSide() const;` — `UFUNCTION(BlueprintCallable, Category = "UVREditorInteractor")` — Sets the EControllerHand for this motioncontroller
- L124 _public prototype_ `float GetSlideDelta() const;` — `UFUNCTION(CallInEditor, BlueprintNativeEvent, Category = "UVREditorInteractor")` — Returns the slide delta for pushing and pulling objects. Needs to be implemented by derived classes (e.g. touchpad for vive controller or scrollweel for mouse )
- L127 _public prototype_ `virtual void PlayHapticEffect( const float Strength ) override;` — Starts haptic feedback for physical motion controller
- L131 _public prototype_ `void SetForceShowLaser( const bool bInForceShow );` — `UFUNCTION(BlueprintCallable, Category = "UVREditorInteractor")` — Set if we want to force to show the laser
- L134 _public prototype_ `bool IsCarrying() const;` — Tells us if thie interator is carrying a "carryable" actor, like a camera, which matches the interactor motions instead of using manipulators.
- L145 _public prototype_ `float GetTrackpadSlideDelta( const bool Axis = 1 ) const;` — Gets the trackpad delta of the axis passed. @param Axis	The axis of which we want the slide delta. 0 is X axis and 1 is Y axis.Default is axis Y
- L148 _public prototype_ `void ResetTrackpad();` — Resets all the trackpad related values to default.
- L152 _public prototype_ `bool IsTouchingTrackpad() const;` — `UFUNCTION(BlueprintCallable, Category = "UVREditorInteractor")` — Check if the touchpad is currently touched
- L156 _public prototype_ `FVector2D GetTrackpadPosition() const;` — `UFUNCTION(BlueprintCallable, Category = "UVREditorInteractor")` — Get the current position of the trackpad or analog stick
- L160 _public prototype_ `FVector2D GetLastTrackpadPosition() const;` — `UFUNCTION(BlueprintCallable, Category = "UVREditorInteractor")` — Get the last position of the trackpad or analog stick
- L163 _public prototype_ `bool IsTrackpadPositionValid( const int32 AxisIndex ) const;` — If the trackpad values are valid
- L166 _public prototype_ `FTimespan& GetLastTrackpadPositionUpdateTime();` — Get when the last time the trackpad position was updated
- L169 _public prototype_ `FTimespan& GetLastActiveTrackpadUpdateTime();` — Get when the last time the trackpad position was updated
- L176 _public prototype_ `const FVector& GetLaserStart() const;` — `UFUNCTION(BlueprintCallable, Category = "UVREditorInteractor")` — Getters and setters
- L179 _public prototype_ `const FVector& GetLaserEnd() const;` — `UFUNCTION(BlueprintCallable, Category = "UVREditorInteractor")`
- L183 _public prototype_ `void SetForceLaserColor( const FLinearColor& InColor );` — `UFUNCTION(BlueprintCallable, Category = "UVREditorInteractor")` — Next frame this will be used as color for the laser
- L186 _public prototype_ `AVREditorTeleporter* GetTeleportActor();` — `UFUNCTION(BlueprintCallable, Category = "UVREditorInteractor")`
- L190 _public prototype_ `EControllerHand GetControllerSide() const;` — `UFUNCTION(BlueprintCallable, Category = "UVREditorInteractor")` — Get the side of the controller
- L194 _public prototype_ `EControllerType GetControllerType() const;` — `UFUNCTION(BlueprintCallable, Category = "VREditorInteractor")` — Returns what controller type this is for asymmetric control schemes
- L198 _public prototype_ `void SetControllerType( const EControllerType InControllerType );` — `UFUNCTION(BlueprintCallable, Category = "VREditorInteractor")` — Set what controller type this is for asymmetric control schemes
- L207 _public prototype_ `bool TryOverrideControllerType( const EControllerType InControllerType );` — `UFUNCTION(BlueprintCallable, Category = "VREditorInteractor")` — Temporary set what controller type this is for asymmetric control schemes. You can't override the controller type when there's already an override. Remove the temporary controller type with EControllerType::Unknown @return true if the controller type was changed
- L211 _public prototype_ `bool IsHoveringOverUI() const;` — `UFUNCTION(BlueprintCallable, Category = "VREditorInteractor")` — Gets if this interactor is hovering over UI
- L214 _public prototype_ `void SetHasUIOnForearm( const bool bInHasUIOnForearm );` — Sets if the quick menu is on this interactor
- L217 _public prototype_ `bool HasUIOnForearm() const;` — Check if the quick menu is on this interactor
- L220 _public prototype_ `UWidgetComponent* GetLastHoveredWidgetComponent() const;` — Gets the current hovered widget component if any
- L223 _public prototype_ `void SetLastHoveredWidgetComponent( UWidgetComponent* NewHoveringOverWidgetComponent );` — Sets the current hovered widget component
- L226 _public prototype_ `void SetIsClickingOnUI( const bool bInIsClickingOnUI );` — Sets if the interactor is clicking on any UI
- L230 _public prototype_ `bool IsClickingOnUI() const;` — `UFUNCTION(BlueprintCallable, Category = "VREditorInteractor")` — Gets if the interactor is clicking on any UI
- L233 _public prototype_ `void SetIsHoveringOverUI( const bool bInIsHoveringOverUI );` — Sets if the interactor is hovering over any UI
- L236 _public prototype_ `void SetIsRightClickingOnUI( const bool bInIsRightClickingOnUI );` — Sets if the interactor is right  hover over any UI
- L239 _public prototype_ `bool IsRightClickingOnUI() const;` — Gets if the interactor is right clicking on UI
- L242 _public prototype_ `void SetLastUIPressTime( const double InLastUIPressTime );` — Sets the time the interactor last pressed on UI
- L245 _public prototype_ `double GetLastUIPressTime() const;` — Gets last time the interactor pressed on UI
- L248 _public prototype_ `void SetUIScrollVelocity( const float InUIScrollVelocity );` — Sets the UI scroll velocity
- L251 _public prototype_ `float GetUIScrollVelocity() const;` — Gets the UI scroll velocity
- L255 _public prototype_ `float GetSelectAndMoveTriggerValue() const;` — `UFUNCTION(BlueprintCallable, Category = "VREditorInteractor")` — Gets the trigger value
- L258 _public prototype_ `virtual bool GetIsLaserBlocked() const override;` — ViewportInteractor overrides, checks if the laser is blocked by UI
- L262 _public prototype_ `void ReplaceHandMeshComponent(UStaticMesh* NewMesh, FVector MeshScale = FVector(1.f, 1.f, 1.f));` — `UFUNCTION(BlueprintCallable, Category = "VREditorInteractor")` — Replace the default VR controller mesh with a custom one.
- L264 _public prototype_ `bool IsActionKeyPressed(FName ActionName) const;`
- L269 _protected prototype_ `virtual void PollInput() override;` — Polls input for the motion controllers transforms
- L273 _protected member_ `bool bIsUndoRedoSwipeEnabled;` — `UPROPERTY(EditDefaultsOnly, Category = "VREditorInteractor")` — Whether swiping left/right on touchpad/joystick triggers undo/redo
- L277 _protected member_ `TObjectPtr<class UMotionControllerComponent> MotionControllerComponent;` — `UPROPERTY()` — Motion controller component which handles late-frame transform updates of all parented sub-components
- L281 _protected member_ `TObjectPtr<class UMotionControllerComponent> LaserMotionControllerComponent;` — `UPROPERTY()` — Separate motion controller component set to the "aim" pose motion source, used for the laser pointer.
- L289 _protected member_ `TObjectPtr<class UStaticMeshComponent> HandMeshComponent;` — `UPROPERTY(BlueprintReadWrite, Category = "VREditorInteractor")` — Access to the current handmesh. Use ReplaceHandMeshComponent() to update the entire StaticMeshComponent.
- L292 _protected prototype_ `void UpdateHandMeshRelativeTransform();` — `UFUNCTION(BlueprintNativeEvent)`
- L294 _protected member_ `FVector3d HandMeshBaseScale;`
- L295 _protected member_ `FTransform HandMeshGripTransform;`
- L302 _private member_ `TObjectPtr<class USplineComponent> LaserSplineComponent;` — `UPROPERTY()` — Spline for this hand's laser pointer
- L306 _private member_ `TArray<TObjectPtr<class USplineMeshComponent>> LaserSplineMeshComponents;` — `UPROPERTY()` — Spline meshes for curved laser
- L310 _private member_ `TObjectPtr<class UMaterialInstanceDynamic> LaserPointerMID;` — `UPROPERTY()` — MID for laser pointer material (opaque parts)
- L314 _private member_ `TObjectPtr<class UMaterialInstanceDynamic> TranslucentLaserPointerMID;` — `UPROPERTY()` — MID for laser pointer material (translucent parts)
- L318 _private member_ `TObjectPtr<class UStaticMeshComponent> HoverMeshComponent;` — `UPROPERTY()` — Hover impact indicator mesh
- L322 _private member_ `TObjectPtr<class UPointLightComponent> HoverPointLightComponent;` — `UPROPERTY()` — Hover point light
- L326 _private member_ `TObjectPtr<class UMaterialInstanceDynamic> HandMeshMID;` — `UPROPERTY()` — MID for hand mesh
- L330 _private member_ `TObjectPtr<AActor> OwningAvatar;` — `UPROPERTY()` — Avatar actor that we're attached to. Cached so that we can change the HandMeshComponent via BP at runtime.
- L333 _private member_ `bool bHaveMotionController;` — True if this hand has a motion controller (or both!)
- L336 _private member_ `static const FName TrackpadPositionX;` — Special key action names for motion controllers
- L337 _private member_ `static const FName TrackpadPositionY;`
- L338 _private member_ `static const FName TriggerAxis;`
- L339 _private member_ `static const FName MotionController_Left_FullyPressedTriggerAxis;`
- L340 _private member_ `static const FName MotionController_Right_FullyPressedTriggerAxis;`
- L341 _private member_ `static const FName MotionController_Left_PressedTriggerAxis;`
- L342 _private member_ `static const FName MotionController_Right_PressedTriggerAxis;`
- L345 _private member_ `TMap<FName, bool> ActionKeysPressed;` — Is the button for the specified action currently held down?
- L349 _private member_ `bool bIsModifierPressed;` — `UE_DEPRECATED(5.1, "Use IsActionKeyPressed(VRActionTypes::Modifier) instead.")` — Is the Modifier button held down?
- L352 _private member_ `float SelectAndMoveTriggerValue;` — Current trigger pressed amount for 'select and move' (0.0 - 1.0)
- L354 _private member_ `FVector LaserStart;`
- L356 _private member_ `FVector LaserEnd;`
- L361 _private prototype_ `void ApplyButtonPressColors( const FViewportActionKeyInput& Action );` — Changes the color of the buttons on the handmesh
- L364 _private prototype_ `void SetMotionControllerButtonPressedVisuals( const EInputEvent Event, const FName& ParameterName, const float PressStrength );` — Set the visuals for a button on the motion controller
- L367 _private prototype_ `void ShowHelpForHand( const bool bShowIt );` — Pops up some help text labels for the controller in the specified hand, or hides it, if requested
- L370 _private prototype_ `void UpdateHelpLabels();` — Called every frame to update the position of any floating help labels
- L373 _private prototype_ `UStaticMeshSocket* FindMeshSocketForKey( UStaticMesh* StaticMesh, const FKey Key );` — Given a mesh and a key name, tries to find a socket on the mesh that matches a supported key
- L376 _private prototype_ `void UpdateSplineLaser( const FVector& InStartLocation, const FVector& InEndLocation, const FVector& InForward );` — Updates all the segments of the curved laser
- L379 _private prototype_ `void SetLaserVisibility( const bool bVisible );` — Sets the visibility on all curved laser segments
- L382 _private prototype_ `void SetLaserVisuals( const FLinearColor& NewColor, const float CrawlFade, const float CrawlSpeed );` — Sets the visuals of the LaserPointer
- L385 _private prototype_ `void UpdateRadialMenuInput( const float DeltaTime );` — Updates the radial menu
- L388 _private prototype_ `void SetHandMeshComponentProperties();` — Initialize shared HandMeshComponent settings
- L391 _private prototype_ `void UndoRedoFromSwipe( const ETouchSwipeDirection InSwipeDirection );` — Start undo or redo from swipe for the Vive
- L399 _private member_ `EControllerType ControllerType;` — `UPROPERTY()` — For asymmetrical systems - what type of controller this is
- L403 _private member_ `EControllerType OverrideControllerType;` — `UPROPERTY()` — What was our previous controller type
- L411 _private member_ `bool bHasUIInFront;` — True if a floating UI panel is attached to the front of the hand, and we shouldn't bother drawing a laser pointer or enabling certain other features
- L414 _private member_ `bool bHasUIOnForearm;` — True if a floating UI panel is attached to our forearm, so we shouldn't bother drawing help labels
- L417 _private member_ `bool bIsClickingOnUI;` — True if we're currently holding the 'SelectAndMove' button down after clicking on UI
- L420 _private member_ `bool bIsRightClickingOnUI;` — When bIsClickingOnUI is true, this will be true if we're "right clicking".  That is, the Modifier key was held down at the time that the user clicked
- L423 _private member_ `bool bIsHoveringOverUI;` — True if we're hovering over UI right now.  When hovering over UI, we don't bother drawing a see-thru laser pointer
- L426 _private member_ `float UIScrollVelocity;` — Inertial scrolling -- how fast to scroll the mousewheel over UI
- L429 _private member_ `double LastUIPressTime;` — Last real time that we pressed the 'SelectAndMove' button on UI.  This is used to detect double-clicks.
- L439 _protected member_ `bool bIsTouchingTrackpad;` — `UE_DEPRECATED(5.1, "Use IsActionKeyPressed(VRActionTypes::Touch) instead.")` — True if the trackpad is actively being touched
- L443 _protected member_ `bool bIsPressingTrackpad;` — `UE_DEPRECATED(5.1, "Use IsActionKeyPressed(VRActionTypes::ConfirmRadialSelection) instead.")` — True if pressing trackpad button (or analog stick button is down)
- L446 _protected member_ `FVector2D TrackpadPosition;` — Position of the touched trackpad
- L449 _protected member_ `FVector2D LastTrackpadPosition;` — Last position of the touched trackpad
- L452 _protected member_ `bool bIsTrackpadPositionValid[2];` — True if we have a valid trackpad position (for each axis)
- L455 _protected member_ `FTimespan LastTrackpadPositionUpdateTime;` — Real time that the last trackpad position was last updated.  Used to filter out stale previous data.
- L458 _protected member_ `FTimespan LastActiveTrackpadUpdateTime;` — Real time that the last trackpad position was over the dead zone threshold.
- L461 _protected member_ `bool bForceShowLaser;` — Forcing to show laser
- L464 _protected member_ `TOptional<FLinearColor> ForceLaserColor;` — The color that will be used for one frame
- L467 _protected member_ `bool bFlickActionExecuted;` — Whether a flick action was executed
- L470 _protected member_ `bool bIsScrubbingSequence;` — whether or not this controller is being used to scrub sequencer
- L478 _protected member_ `FName ControllerMotionSource;` — `UPROPERTY()` — Right or left hand
- L481 _protected member_ `bool bWantHelpLabels;` — True if we want help labels to be visible right now, otherwise false
- L484 _protected member_ `TMap< FKey, class AFloatingText* > HelpLabels;` — Help labels for buttons on the motion controllers
- L487 _protected member_ `FTimespan HelpLabelShowOrHideStartTime;` — Time that we either started showing or hiding help labels (for fade transitions)
- L494 _protected member_ `bool bIsTriggerFullyPressed;` — True if trigger is fully pressed right now (or within some small threshold)
- L497 _protected member_ `bool bIsTriggerPressed;` — True if the trigger is currently pulled far enough that we consider it in a "half pressed" state
- L500 _protected member_ `bool bHasTriggerBeenReleasedSinceLastPress;` — True if trigger has been fully released since the last press
- L507 _protected member_ `FVector2D InitialTouchPosition;` — Initial position when starting to touch the trackpad
- L510 _protected member_ `ETouchSwipeDirection LastSwipe;` — Latest swipe direction on the trackpad
- L514 _protected member_ `TObjectPtr<class UVREditorMode> VRMode;` — `UPROPERTY()` — The mode that owns this interactor

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API VREDITOR_API`

### `Source/Editor/VREditor/Public/VREditorMode.h` (Public)


#### class `UVREditorMode`  
`class UE_DEPRECATED(5.7, "VR Editor mode is deprecated; use the XR Creative Framework plugin instead.") UVREditorMode : public UVREditorModeBase`  
_L59-483_
- reflection: `UCLASS(MinimalAPI, Abstract, Transient)`
- inherits: `UVREditorModeBase`
- desc: VR Editor Mode. Extends editor viewports with functionality for VR controls and object manipulation
- L66 _public prototype_ `UVREditorMode();` — Default constructor
- L69 _public prototype_ `void SetHMDDeviceTypeOverride( FName InOverrideType );` — Overrides the HMD device type, which is otherwise derived from the XR system name.
- L74 _public prototype_ `virtual void Init() override;` — Initialize the VREditor
- L77 _public prototype_ `virtual void Shutdown() override;` — Shutdown the VREditor
- L80 _protected prototype_ `virtual void TransitionWorld(UWorld* NewWorld, EEditorWorldExtensionTransitionState TransitionState) override;`
- L85 _public function_ `virtual bool NeedsSyntheticDpad()`
- L91 _public function_ `virtual bool ShouldDisplayExperimentalWarningOnEntry() const` — `UE_DEPRECATED(5.1, "This method is no longer used; the associated warning is no longer displayed.")`
- L94 _public prototype_ `virtual void Enter() override;` — When the user actually enters the VR Editor mode
- L97 _public prototype_ `virtual void Exit( bool bShouldDisableStereo ) override;` — When the user leaves the VR Editor mode
- L100 _public prototype_ `void PreTick( const float DeltaTime );` — Tick before the ViewportWorldInteraction is ticked
- L103 _public prototype_ `void PostTick( const float DeltaTime );` — Tick after the ViewportWorldInteraction is ticked
- L106 _public function_ `virtual bool WantsToExitMode() const override` — Returns true if the user wants to exit this mode
- L111 _public prototype_ `void AllocateInteractors();`
- L114 _public prototype_ `void StartExitingVRMode();` — Call this to start exiting VR mode
- L116 _public prototype_ `virtual bool GetLaserForHand(EControllerHand InHand, FVector& OutLaserStart, FVector& OutLaserEnd) const override;`
- L120 _public prototype_ `virtual FTransform GetRoomTransform() const override;` — Gets the world space transform of the calibrated VR room origin.  When using a seated VR device, this will feel like the camera's world transform (before any HMD positional or rotation adjustments are applied.)
- L123 _public prototype_ `void SetRoomTransform( const FTransform& NewRoomTransform );` — Sets a new transform for the room, in world space.  This is basically setting the editor's camera transform for the viewport
- L126 _public prototype_ `FTransform GetRoomSpaceHeadTransform() const;` — Gets the transform of the user's HMD in room space
- L133 _public prototype_ `virtual FTransform GetHeadTransform() const override;` — Gets the world space transform of the HMD (head) @return	World space space HMD transform
- L136 _public prototype_ `const class UViewportWorldInteraction& GetWorldInteraction() const;` — Gets access to the world interaction system (const)
- L139 _public prototype_ `class UViewportWorldInteraction& GetWorldInteraction();` — Gets access to the world interaction system
- L142 _public prototype_ `bool IsFullyInitialized() const;` — If the mode was completely initialized
- L145 _public prototype_ `DECLARE_EVENT_OneParam(UVREditorMode, FOnVRTickHandle, const float );` — Gets the tick handle to give external systems the change to be ticked right after the ViewportWorldInteraction is ticked
- L146 _public function_ `FOnVRTickHandle& OnTickHandle()`
- L152 _public function_ `int32 GetMotionControllerID() const` — Returns the Unreal controller ID for the motion controllers we're using
- L158 _public function_ `bool IsFlashlightOn() const` — Returns whether or not the flashlight is visible
- L164 _public function_ `inline FTimespan GetTimeSinceModeEntered() const` — Returns the time since the VR Editor mode was last entered
- L172 _public function_ `template<class T> static T OvershootEaseOut( T Alpha, const float OvershootAmount = 1.0f )` — @todo vreditor: Move this to FMath so we can use it everywhere NOTE: OvershootAmount is usually between 0.5 and 2.0, but can go lower and higher for extreme overshots
- L179 _public function_ `const class UVREditorUISystem& GetUISystem() const` — Gets access to the VR UI system (const)
- L185 _public function_ `class UVREditorUISystem& GetUISystem()` — Gets access to the VR UI system
- L191 _public function_ `bool UISystemIsActive() const` — Check whether the UISystem exists
- L197 _public prototype_ `bool IsShowingRadialMenu( const class UVREditorInteractor* Interactor ) const;` — Lets other modules know if the radial menu is visible on a given interactor so input should be handled differently
- L201 _public prototype_ `void SetGameView(bool bGameView);` — `UFUNCTION(BlueprintCallable, Category="VREditorMode")` — Display the scene more closely to how it would appear at runtime (as opposed to edit time).
- L205 _public prototype_ `bool IsInGameView() const;` — `UFUNCTION(BlueprintCallable, Category="VREditorMode")` — Returns whether game view is currently active.
- L209 _public prototype_ `float GetWorldScaleFactor() const;` — `UFUNCTION(BlueprintCallable, Category = "VREditorMode")` — Gets the world scale factor, which can be multiplied by a scale vector to convert to room space
- L212 _public prototype_ `void ToggleFlashlight( class UVREditorInteractor* Interactor );` — Spawns a flashlight on the specified hand
- L215 _public prototype_ `void CycleTransformGizmoHandleType();` — Will update the TransformGizmo Actor with the next Gizmo type
- L218 _public prototype_ `EGizmoHandleTypes GetCurrentGizmoType() const;` — Gets the current Gizmo handle type
- L221 _public prototype_ `FName GetHMDDeviceType() const;` — @return Returns the type of HMD we're dealing with
- L224 _public prototype_ `bool IsHandAimingTowardsCapsule(class UViewportInteractor* Interactor, const FTransform& CapsuleTransform, const FVector CapsuleStart, const FVector CapsuleEnd, const float CapsuleRadius, const float MinDistanceToCapsule, const FVector CapsuleFrontDirection, const float MinDotForAimingAtCapsule) const;` — @return Checks to see if the specified interactor is aiming roughly toward the specified capsule
- L227 _public prototype_ `class UVREditorInteractor* GetHandInteractor( const EControllerHand ControllerHand ) const;` — Gets the hand interactor
- L230 _public prototype_ `void SnapSelectedActorsToGround();` — Snaps the current selected actor to the ground
- L241 _public function_ `virtual TSharedRef<FBaseSavedEditorState> CreateSavedState() override`
- L244 _public prototype_ `const FSavedEditorState& GetSavedEditorState() const;` — Gets the saved editor state from entering the mode
- L246 _public prototype_ `DECLARE_DELEGATE(FOnVREditingModeExit);`
- L248 _public member_ `FOnVREditingModeExit OnVREditingModeExit_Handler;` — Used to override dockable area restoration behavior
- L250 _public prototype_ `void SaveSequencerSettings(bool bInKeyAllEnabled, EAutoChangeMode InAutoChangeMode, const class USequencerSettings& InSequencerSettings);`
- L253 _public prototype_ `UStaticMeshComponent* CreateMotionControllerMesh( AActor* OwningActor, USceneComponent* AttachmentToComponent, UStaticMesh* OptionalControllerMesh = nullptr );` — Create a static motion controller mesh for the current HMD platform
- L256 _public prototype_ `UStaticMeshComponent* CreateMesh( AActor* OwningActor, const FString& MeshName, USceneComponent* AttachmentToComponent );` — Helper functions to create a static mesh
- L257 _public prototype_ `UStaticMeshComponent* CreateMesh(AActor* OwningActor, UStaticMesh* Mesh, USceneComponent* AttachmentToComponent );`
- L260 _public prototype_ `const class UVREditorAssetContainer& GetAssetContainer() const;` — Gets the container for all the assets of VREditor.
- L263 _public prototype_ `static class UVREditorAssetContainer& LoadAssetContainer();` — Loads and returns the container for all the assets of VREditor.
- L266 _public prototype_ `void PlaySound(USoundBase* SoundBase, const FVector& InWorldLocation, const float InVolume = 1.0f);` — Plays sound at location.
- L269 _public prototype_ `DECLARE_EVENT_ThreeParams( UVREditorPlacement, FOnPlaceDraggedMaterial, UPrimitiveComponent*, UMaterialInterface*, bool& );` — Delegate to be called when a material is placed
- L270 _public function_ `FOnPlaceDraggedMaterial& OnPlaceDraggedMaterial()`
- L273 _public prototype_ `DECLARE_EVENT_OneParam(UVREditorPlacement, FOnPlacePreviewActor, bool);` — Delegate to be called when a preview actor is placed
- L274 _public function_ `FOnPlacePreviewActor& OnPlacePreviewActor()`
- L277 _public prototype_ `bool IsAimingTeleport() const;` — Return true if currently aiming to teleport.
- L278 _public prototype_ `bool IsTeleporting() const;`
- L281 _public prototype_ `static void ToggleDebugMode();` — Toggles the debug mode.
- L284 _public prototype_ `static bool IsDebugModeEnabled();` — Returns if the VR Mode is in debug mode.
- L287 _public prototype_ `class AVREditorTeleporter* GetTeleportActor();` — Get Teleporter
- L290 _public prototype_ `DECLARE_EVENT_OneParam(UVREditorMode, FOnToggleVRModeDebug, bool);` — Delegate to be called when the debug mode is toggled.
- L291 _public function_ `FOnToggleVRModeDebug& OnToggleDebugMode()`
- L293 _public function_ `const TArray<UVREditorInteractor*> GetVRInteractors() const`
- L301 _private prototype_ `void OnEditorClosed();` — Called when the editor is closed
- L304 _private prototype_ `void OnVREditorWindowClosed( const TSharedRef<SWindow>& ClosedWindow );` — Called when someone closes a standalone VR Editor window
- L307 _private prototype_ `void RestoreWorldToMeters();` — Restore the world to meters to the saved one when entering VR Editor
- L315 _protected prototype_ `void BeginEntry();`
- L316 _protected prototype_ `void SetupSubsystems();`
- L317 _protected prototype_ `void FinishEntry();`
- L320 _protected member_ `TWeakPtr< class SWindow > VREditorWindowWeakPtr;` — The VR editor window, if it's open right now
- L323 _protected member_ `bool bWantsToExitMode;` — True if we currently want to exit VR mode.  This is used to defer exiting until it is safe to do that
- L326 _protected member_ `bool bIsFullyInitialized;` — True if VR mode is fully initialized and ready to render
- L329 _protected member_ `FTimespan AppTimeModeEntered;` — App time that we entered this mode
- L337 _protected member_ `TObjectPtr<class AVREditorAvatarActor> AvatarActor;` — `UPROPERTY()` — Actor with components to represent the VR avatar in the world, including motion controller meshes
- L345 _protected member_ `class USpotLightComponent* FlashlightComponent;` — Spotlight for the flashlight
- L348 _protected member_ `bool bIsFlashlightOn;` — If there is currently a flashlight in the scene
- L355 _protected member_ `int32 MotionControllerID;` — The Unreal controller ID for the motion controllers we're using
- L362 _protected member_ `FOnVRTickHandle TickHandle;`
- L365 _protected member_ `FOnPlaceDraggedMaterial OnPlaceDraggedMaterialEvent;` — Event broadcast when a material is placed
- L368 _protected member_ `FOnPlacePreviewActor OnPlacePreviewActorEvent;` — Event broadcast when a preview actor is placed
- L376 _protected member_ `TObjectPtr<class UVREditorUISystem> UISystem;` — `UPROPERTY()` — VR UI system
- L380 _protected member_ `TObjectPtr<class AVREditorTeleporter> TeleportActor;` — `UPROPERTY()` — Teleporter system
- L384 _protected member_ `TObjectPtr<class UVREditorAutoScaler> AutoScalerSystem;` — `UPROPERTY()` — Automatic scale system
- L392 _protected member_ `TObjectPtr<class UViewportWorldInteraction> WorldInteraction;` — `UPROPERTY()` — World interaction manager
- L395 _protected member_ `EGizmoHandleTypes CurrentGizmoType;` — The current Gizmo type that is used for the TransformGizmo Actor
- L398 _protected member_ `TObjectPtr<class UVREditorPlacement> PlacementSystem;` — `UPROPERTY()`
- L405 _protected member_ `TArray<TObjectPtr<UVREditorInteractor>> Interactors;` — `UPROPERTY()`
- L426 _public prototype_ `FLinearColor GetColor( const EColors Color ) const;` — Gets the color
- L429 _public prototype_ `float GetDefaultVRNearClipPlane() const;` — Get the default near clipping plane for VR editing
- L432 _public prototype_ `void RefreshVREditorSequencer(class ISequencer* InCurrentSequencer);` — Runtime and plugin modules can force VR Editor to refresh using this function
- L435 _public prototype_ `void RefreshActorPreviewWidget(TSharedRef<SWidget> InWidget, int32 Index, AActor *Actor, bool bIsPanelDetached = false);` — Refresh the current actor preview widget on an in-world UI panel
- L438 _public prototype_ `void UpdateExternalUMGUI(const struct FVREditorFloatingUICreationContext& CreationContext);` — General way to spawn an external UMG UI from a radial menu
- L441 _public prototype_ `void UpdateExternalSlateUI(TSharedRef<SWidget> InWidget, FName Name, FVector2D InSize);` — General way to spawn an external Slate UI from a radial menu
- L444 _public prototype_ `class ISequencer* GetCurrentSequencer();` — Returns the currently active sequencer
- L447 _public member_ `static const TCHAR* AssetContainerPath;` — The asset container path
- L451 _public member_ `TSoftClassPtr<UVREditorInteractor> InteractorClass;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, NoClear, Category="Classes")` — The controller to use when UnrealEd is in VR mode. Use VREditorInteractor get default editor behavior, or select a custom controller for special behavior
- L455 _public member_ `TSoftClassPtr<AVREditorTeleporter> TeleporterClass;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, NoClear, Category="Classes")` — The teleporter to use when UnrealEd is in VR mode. Use VREditorTeleporter to get default editor behavior, or select a custom teleporter
- L460 _private member_ `TArray<FLinearColor> Colors;` — All the colors for this mode
- L463 _private member_ `bool bFirstTick;` — If this is the first tick or before
- L466 _private member_ `class ISequencer* CurrentSequencer;` — Pointer to the current Sequencer
- L471 _private member_ `TObjectPtr<class UVREditorAssetContainer> AssetContainer;` — `UPROPERTY()` — Container of assets
- L474 _private member_ `static bool bDebugModeEnabled;` — Whether currently in debug mode or not.
- L477 _private member_ `FOnToggleVRModeDebug OnToggleDebugModeEvent;` — Event that gets broadcasted when debug mode is toggled.
- L480 _private member_ `FName HMDDeviceTypeOverride = NAME_None;` — Overridden HMD device type. If NAME_None, HMD device type is derived from the XR system name.
- L482 _private member_ `bool bAddedViewportWorldInteractionExtension = false;`

#### struct `UVREditorMode::FSavedEditorState`  
`struct FSavedEditorState : public FBaseSavedEditorState`  
_L233-239_
- inherits: `FBaseSavedEditorState`
- desc: Saved information about the editor and viewport we possessed, so we can restore it after exiting VR mode
- L235 _public member_ `float DragTriggerDistance = 0.0f;`
- L236 _public member_ `float TransformGizmoScale = 1.0f;`
- L237 _public member_ `bool bKeyAllEnabled = false;`
- L238 _public member_ `EAutoChangeMode AutoChangeMode;`

#### enum `UVREditorMode::EColors`  
`enum EColors`  
_L412-423_
- desc: Color types
- L414 _public enumerator_ `DefaultColor`
- L415 _public enumerator_ `SelectionColor`
- L416 _public enumerator_ `WorldDraggingColor`
- L417 _public enumerator_ `UIColor`
- L418 _public enumerator_ `UISelectionBarColor`
- L419 _public enumerator_ `UISelectionBarHoverColor`
- L420 _public enumerator_ `UICloseButtonColor`
- L421 _public enumerator_ `UICloseButtonHoverColor`
- L422 _public enumerator_ `TotalCount`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API VREDITOR_API`
- L40 _namespace_ `namespace VRActionTypes`
- L42 _variable_ `static const FName Touch( "Touc` (scope `VRActionTypes`)
- L43 _variable_ `static const FName Modifier( "Modi` (scope `VRActionTypes`)
- L44 _variable_ `static const FName Modifier2( "Modi` (scope `VRActionTypes`)
- L45 _variable_ `static const FName ConfirmRadialSelection( "Conf` (scope `VRActionTypes`)
- L46 _variable_ `static const FName TrackpadPositionX( "Trac` (scope `VRActionTypes`)
- L47 _variable_ `static const FName TrackpadPositionY( "Trac` (scope `VRActionTypes`)
- L48 _variable_ `static const FName TrackpadUp("Tra` (scope `VRActionTypes`)
- L49 _variable_ `static const FName TrackpadDown("Tra` (scope `VRActionTypes`)
- L50 _variable_ `static const FName TrackpadRight("Tra` (scope `VRActionTypes`)
- L51 _variable_ `static const FName TrackpadLeft("Tra` (scope `VRActionTypes`)
- L52 _variable_ `static const FName TriggerAxis( "Trig` (scope `VRActionTypes`)
- L145 _delegate_ `DECLARE_EVENT_OneParam(UVREditorMode, FOnVRTickHandle, const float );` — Gets the tick handle to give external systems the change to be ticked right after the ViewportWorldInteraction is ticked
- L246 _delegate_ `DECLARE_DELEGATE(FOnVREditingModeExit);`
- L269 _delegate_ `DECLARE_EVENT_ThreeParams( UVREditorPlacement, FOnPlaceDraggedMaterial, UPrimitiveComponent*, UMaterialInterface*, bool& );` — Delegate to be called when a material is placed
- L273 _delegate_ `DECLARE_EVENT_OneParam(UVREditorPlacement, FOnPlacePreviewActor, bool);` — Delegate to be called when a preview actor is placed
- L290 _delegate_ `DECLARE_EVENT_OneParam(UVREditorMode, FOnToggleVRModeDebug, bool);` — Delegate to be called when the debug mode is toggled.

### `Source/Editor/VREditor/Public/VREditorModeBase.h` (Public)


#### class `UVREditorModeBase`  
`class UVREditorModeBase : public UEditorWorldExtension`  
_L20-112_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType, Blueprintable, Transient)`
- inherits: `UEditorWorldExtension`
- L29 _public prototype_ `virtual void Init() override;`
- L30 _public prototype_ `virtual void Shutdown() override;`
- L33 _public prototype_ `virtual void Enter();`
- L34 _public prototype_ `virtual void Exit(bool bShouldDisableStereo);`
- L37 _public function_ `virtual void SetActuallyUsingVR(bool bShouldActuallyUseVR)` — Sets whether we should actually use an HMD. Call this before activating VR mode
- L40 _public function_ `virtual bool IsActuallyUsingVR() const` — Returns true if we're actually using VR, or false if we're faking it
- L43 _public function_ `virtual bool WantsToExitMode() const` — Returns true if the user wants to exit this mode
- L46 _public function_ `virtual FTransform GetRoomTransform() const` — Returns the transform which takes poses from XR tracking space ("room" space) to world space.
- L49 _public function_ `virtual FTransform GetHeadTransform() const` — Returns the user's head pose in world space.
- L52 _public function_ `virtual bool GetLaserForHand(EControllerHand InHand, FVector& OutLaserStart, FVector& OutLaserEnd) const` — Gives start and end points in world space for an active laser, or returns false if there is no active laser for the specified hand.
- L55 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnVRModeEntryComplete);` — Delegate to be called when async VR mode entry has been completed.
- L56 _public function_ `FOnVRModeEntryComplete& OnVRModeEntryComplete()`
- L59 _public prototype_ `const class SLevelViewport& GetLevelViewportPossessedForVR() const;` — TODO: Deprecate these in favor of replacements below; viewport may be null.
- L60 _public prototype_ `class SLevelViewport& GetLevelViewportPossessedForVR();`
- L62 _public function_ `TSharedPtr<SLevelViewport> GetVrLevelViewport()`
- L63 _public function_ `TSharedPtr<const SLevelViewport> GetVrLevelViewport() const`
- L67 _protected function_ `virtual TSharedRef<FBaseSavedEditorState> CreateSavedState()` — Derived classes can override this to return a derived state struct, and add their own saved state.
- L70 _protected function_ `FBaseSavedEditorState& SavedEditorStateChecked()` — Gets the saved editor state from entering the mode
- L71 _protected function_ `const FBaseSavedEditorState& SavedEditorStateChecked() const`
- L74 _protected prototype_ `virtual void StartViewport(TSharedPtr<SLevelViewport> Viewport);` — Start using the viewport passed
- L77 _protected prototype_ `virtual void CloseViewport(bool bShouldDisableStereo);` — Close the current viewport
- L79 _protected prototype_ `virtual void StereoViewportSetup(TSharedRef<SLevelViewport> Viewport);`
- L80 _protected prototype_ `virtual void StereoViewportShutdown(TSharedRef<SLevelViewport> Viewport);`
- L82 _protected prototype_ `virtual void EnableStereo();`
- L83 _protected prototype_ `virtual void DisableStereo();`
- L87 _protected member_ `bool bActuallyUsingVR;` — True if we're in using an actual HMD in this mode, or false if we're "faking" VR mode for testing
- L90 _protected member_ `FOnVRModeEntryComplete OnVRModeEntryCompleteEvent;` — Delegate broadcast when async VR mode entry is completed.
- L92 _protected member_ `TWeakPtr<SLevelViewport> VREditorLevelViewportWeakPtr;`
- L111 _protected member_ `TSharedPtr<FBaseSavedEditorState> SavedEditorStatePtr;`

#### struct `UVREditorModeBase::FBaseSavedEditorState`  
`struct FBaseSavedEditorState`  
_L95-109_
- desc: Saved information about the editor and viewport we possessed, so we can restore it after exiting VR mode
- L97 _public member_ `ELevelViewportType ViewportType = LVT_Perspective;`
- L98 _public member_ `FVector ViewLocation = FVector::ZeroVector;`
- L99 _public member_ `FRotator ViewRotation = FRotator::ZeroRotator;`
- L100 _public member_ `FEngineShowFlags ShowFlags = ESFIM_Editor;`
- L101 _public member_ `bool bLockedPitch = false;`
- L102 _public member_ `bool bAlwaysShowModeWidgetAfterSelectionChanges = false;`
- L103 _public member_ `float NearClipPlane = 0.0f;`
- L104 _public member_ `bool bRealTime = false;`
- L105 _public member_ `bool bOnScreenMessages = false;`
- L106 _public member_ `EHMDTrackingOrigin::Type TrackingOrigin = EHMDTrackingOrigin::Local;`
- L107 _public member_ `float WorldToMetersScale = 100.0f;`
- L108 _public member_ `bool bCinematicControlViewport = false;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API VREDITOR_API`
- L55 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnVRModeEntryComplete);` — Delegate to be called when async VR mode entry has been completed.

### `Source/Editor/VREditor/Public/VREditorStyle.h` (Public)


#### class `FVREditorStyle`  
`class UE_DEPRECATED(5.7, "VR Editor mode is deprecated; use the XR Creative Framework plugin instead.") FVREditorStyle`  
_L14-46_
- L18 _public prototype_ `static void Shutdown();`
- L21 _public prototype_ `static void ReloadTextures();` — reloads textures used by slate renderer
- L24 _public prototype_ `static const ISlateStyle& Get();` — @return The Slate style set for the UMG Style
- L26 _public prototype_ `static FName GetStyleSetName();`
- L28 _public prototype_ `static FName GetSecondaryStyleSetName();`
- L30 _public prototype_ `static FName GetNumpadStyleSetName();`
- L32 _public function_ `static const FSlateBrush* GetBrush(FName PropertyName, const ANSICHAR* Specifier = NULL)`
- L39 _private prototype_ `static TSharedRef< class FSlateStyleSet > Create();`
- L43 _private member_ `static TSharedPtr< class FSlateStyleSet > VREditorStyleInstance;`

### `Source/Editor/VREditor/Public/VRModeSettings.h` (Public)


#### enum `EInteractorHand`  
`enum class UE_DEPRECATED(5.7, "VR Editor mode is deprecated; use the XR Creative Framework plugin instead.") EInteractorHand : uint8`  
_L20-27_
- reflection: `UENUM()`
- L23 _public enumerator_ `Right` — Right hand
- L26 _public enumerator_ `Left` — Left hand

#### class `UVRModeSettings`  
`class UVRModeSettings : public UVISettings`  
_L34-108_
- reflection: `UCLASS(MinimalAPI, config = EditorSettings)`
- inherits: `UVISettings`
- desc: Implements the settings for VR Mode.
- L43 _public prototype_ `UVRModeSettings();` — Default constructor that sets up CDO properties
- L47 _public member_ `uint32 bEnableAutoVREditMode : 1;` — `UPROPERTY(EditAnywhere, config, Category = "General", meta = (DisplayName = "Enable VR Mode Auto-Entry"))` — If true, wearing a Vive or Oculus Rift headset will automatically enter VR Editing mode
- L52 _public member_ `uint32 bAutokeySequences : 1;` — `UE_DEPRECATED(5.7, "VR Editor mode is deprecated; use the XR Creative Framework plugin instead.")` — `UPROPERTY(config)` — Whether or not sequences should be autokeyed
- L58 _public member_ `EInteractorHand InteractorHand;` — `UE_DEPRECATED(5.7, "VR Editor mode is deprecated; use the XR Creative Framework plugin instead.")` — `UPROPERTY(config)` — Which hand should have the primary interactor laser on it
- L64 _public member_ `uint32 bShowWorldMovementGrid : 1;` — `UE_DEPRECATED(5.7, "VR Editor mode is deprecated; use the XR Creative Framework plugin instead.")` — `UPROPERTY(config)` — Show the movement grid for orientation while moving through the world
- L69 _public member_ `uint32 bShowWorldMovementPostProcess : 1;` — `UE_DEPRECATED(5.7, "VR Editor mode is deprecated; use the XR Creative Framework plugin instead.")` — `UPROPERTY(config)` — Dim the surroundings while moving through the world
- L74 _public member_ `uint32 bShowWorldScaleProgressBar : 1;` — `UE_DEPRECATED(5.7, "VR Editor mode is deprecated; use the XR Creative Framework plugin instead.")` — `UPROPERTY(config)` — Display a progress bar while scaling that shows your current scale
- L79 _public member_ `float UIBrightness;` — `UE_DEPRECATED(5.7, "VR Editor mode is deprecated; use the XR Creative Framework plugin instead.")` — `UPROPERTY(config)` — Adjusts the brightness of the UI panels
- L84 _public member_ `float GizmoScale;` — `UE_DEPRECATED(5.7, "VR Editor mode is deprecated; use the XR Creative Framework plugin instead.")` — `UPROPERTY(config)` — The size of the transform gizmo
- L89 _public member_ `float DoubleClickTime;` — `UE_DEPRECATED(5.7, "VR Editor mode is deprecated; use the XR Creative Framework plugin instead.")` — `UPROPERTY(config)` — The maximum time in seconds between two clicks for a double-click to register
- L94 _public member_ `float TriggerPressedThreshold_Vive;` — `UE_DEPRECATED(5.7, "VR Editor mode is deprecated; use the XR Creative Framework plugin instead.")` — `UPROPERTY(config)` — The amount (between 0-1) you have to depress the Vive controller trigger to register a press
- L99 _public member_ `float TriggerPressedThreshold_Rift;` — `UE_DEPRECATED(5.7, "VR Editor mode is deprecated; use the XR Creative Framework plugin instead.")` — `UPROPERTY(config)` — The amount (between 0-1) you have to depress the Oculus Touch controller trigger to register a press
- L103 _public member_ `TSoftClassPtr<UVREditorModeBase> ModeClass;` — `UPROPERTY(EditAnywhere, config, NoClear, Category = "General")` — The mode extension to use when UnrealEd is in VR mode. Use VREditorMode to get default editor behavior or select a custom mode.
- L106 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API VREDITOR_API`

### `Source/Editor/VREditor/Public/VRScoutingInteractor.h` (Public)


#### class `UVRScoutingInteractor`  
`class UE_DEPRECATED(5.7, "VR Editor mode is deprecated; use the XR Creative Framework plugin instead.") UVRScoutingInteractor : public UVREditorInteractor`  
_L26-91_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UVREditorInteractor`
- desc: Represents the interactor in the world
- L33 _public prototype_ `UVRScoutingInteractor();` — Default constructor
- L36 _public prototype_ `virtual float GetSlideDelta_Implementation() const override;` — Gets the trackpad slide delta
- L39 _public prototype_ `virtual void SetupComponent_Implementation(AActor* OwningActor) override;` — Sets up all components
- L42 _public prototype_ `virtual void Shutdown_Implementation() override;` — IViewportInteractorInterface overrides
- L46 _public prototype_ `void SetGizmoMode(EGizmoHandleTypes InGizmoMode);` — `UFUNCTION(BlueprintCallable, Category = "Scouting")` — Sets the gizmo mode for selected object
- L50 _public prototype_ `EGizmoHandleTypes GetGizmoMode() const;` — `UFUNCTION(BlueprintCallable, Category = "Scouting")` — Gets the gizmo mode for selected object
- L54 _public prototype_ `static TArray<AActor*> GetSelectedActors();` — `UFUNCTION(BlueprintCallable, Category = "Scouting")` — Gets all actors that are selected in the world editor
- L58 _public member_ `TObjectPtr<class UStaticMeshComponent> FlyingIndicatorComponent;` — `UPROPERTY(Category = Interactor, EditAnywhere, BlueprintReadOnly)` — Shown in Navigation mode
- L62 _public function_ `UInputComponent* GetInputComponent() const` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Input|Editor")` — Returns the current InputComponent. This will be NULL unless bReceivesEditorInput is set to true.
- L68 _public prototype_ `void SetReceivesEditorInput(bool bInValue);` — `UFUNCTION(BlueprintSetter, Category = "Input|Editor")`
- L71 _public function_ `bool GetReceivesEditorInput() const` — `UFUNCTION(BlueprintGetter, BlueprintPure, Category = "Input|Editor")`
- L79 _private prototype_ `void CreateEditorInput();` — Creates the EditorOnlyInputComponent if it does not already exist and registers all subobject callbacks to it
- L82 _private prototype_ `void RemoveEditorInput();` — Removes the EditorOnlyInputComponent from this object
- L85 _private member_ `TObjectPtr<UInputComponent> EditorOnlyInputComponent;` — `UPROPERTY(Transient, DuplicateTransient)`
- L89 _private member_ `bool bReceivesEditorInput = true;` — `UPROPERTY(EditAnywhere, Category = "Input|Editor", BlueprintSetter = SetReceivesEditorInput, BlueprintGetter = GetReceivesEditorInput)` — If set to true, then this interactor will be able to recieve input delegate callbacks when in the editor. Defaults to true since we will always want this interactor to consume input

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API VREDITOR_API`
