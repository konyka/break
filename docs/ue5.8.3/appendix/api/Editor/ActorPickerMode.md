# Editor / ActorPickerMode

- module root: `Source/Editor/ActorPickerMode`
- headers: 3; symbols: 64
- symbol kinds: class=3, delegate=3, enum=2, enumerator=6, function=1, macro=1, member=10, namespace=1, prototype=37
- DynamicallyLoadedModuleNames: LevelEditor
- PrivateDependencyModuleNames: Core, CoreUObject, EditorFramework, EditorInteractiveToolsFramework, Engine, InputCore, InteractiveToolsFramework, Slate, SlateCore, UnrealEd

### `Source/Editor/ActorPickerMode/Private/ActorPickerViewportInteraction.h` (Private)


#### class `UActorPickerViewportInteraction`  
`class UActorPickerViewportInteraction : public UViewportClickInteraction, public IHoverBehaviorTarget`  
_L12-33_
- reflection: `UCLASS()`
- inherits: `UViewportClickInteraction,IHoverBehaviorTarget`
- L17 _public prototype_ `UActorPickerViewportInteraction();`
- L19 _public prototype_ `virtual void OnClickDown(const FInputDeviceRay& InClickPos) override;`
- L21 _public prototype_ `virtual FInputRayHit BeginHoverSequenceHitTest(const FInputDeviceRay& PressPos) override;`
- L22 _public prototype_ `virtual void OnBeginHover(const FInputDeviceRay& DevicePos) override;`
- L23 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) override;`
- L24 _public prototype_ `virtual void OnEndHover() override;`
- L26 _public prototype_ `void SetMode(const TSharedPtr<FEdModeActorPicker>& InMode);`
- L29 _protected prototype_ `virtual void BuildBehaviors() override;`
- L30 _protected prototype_ `virtual void ProcessClick_Internal(const FViewportClick& InViewportClick, HHitProxy* InHitProxy, FSceneView& View) override;`
- L32 _protected member_ `TWeakPtr<FEdModeActorPicker> WeakMode;`

### `Source/Editor/ActorPickerMode/Private/EditorModeActorPicker.h` (Private)


#### enum `EPickState::Type`  
`enum Type`  
_L18-24_
- L20 _public enumerator_ `NotOverViewport`
- L21 _public enumerator_ `OverViewport`
- L22 _public enumerator_ `OverIncompatibleActor`
- L23 _public enumerator_ `OverActor`

#### class `FEdModeActorPicker`  
`class FEdModeActorPicker : public FEdMode`  
_L30-88_
- inherits: `FEdMode`
- desc: Editor mode used to interactively pick actors in the level editor viewports.
- L33 _public prototype_ `FEdModeActorPicker();`
- L36 _public prototype_ `virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) override;` — Begin FEdMode interface
- L37 _public prototype_ `virtual bool MouseEnter(FEditorViewportClient* ViewportClient, FViewport* Viewport,int32 x, int32 y) override;`
- L38 _public prototype_ `virtual bool MouseLeave(FEditorViewportClient* ViewportClient, FViewport* Viewport) override;`
- L39 _public prototype_ `virtual bool MouseMove(FEditorViewportClient* ViewportClient, FViewport* Viewport, int32 x, int32 y) override;`
- L40 _public prototype_ `virtual bool LostFocus(FEditorViewportClient* ViewportClient, FViewport* Viewport) override;`
- L41 _public prototype_ `virtual bool InputKey(FEditorViewportClient* ViewportClient, FViewport* Viewport, FKey Key, EInputEvent Event) override;`
- L42 _public prototype_ `virtual bool GetCursor(EMouseCursor::Type& OutCursor) const override;`
- L43 _public prototype_ `virtual bool UsesToolkits() const override;`
- L44 _public prototype_ `virtual bool IsCompatibleWith(FEditorModeID OtherModeID) const override;`
- L45 _public prototype_ `virtual void Enter() override;`
- L46 _public prototype_ `virtual void Exit() override;`
- L47 _public function_ `virtual bool RequiresLegacyViewportInteractions() const override`
- L51 _public prototype_ `FText GetCursorDecoratorText() const;` — Delegate used to display information about picking near the cursor
- L53 _public prototype_ `void UpdateHoveredActor(const HHitProxy* HitProxy);`
- L54 _public prototype_ `void OnTrySelectActor(const HHitProxy* HitProxy);`
- L56 _public prototype_ `bool IsActorValid(const AActor *const Actor) const;`
- L60 _public member_ `TWeakObjectPtr<AActor> HoveredActor;` — Flag for display state
- L63 _public member_ `EPickState::Type PickState;` — Flag for display state
- L66 _public member_ `TSharedPtr<SWindow> CursorDecoratorWindow;` — The window that owns the decorator widget
- L69 _public member_ `FOnActorSelected OnActorSelected;` — Delegates used to pick actors
- L70 _public member_ `FOnGetAllowedClasses OnGetAllowedClasses;`
- L71 _public member_ `FOnShouldFilterActor OnShouldFilterActor;`
- L75 _private prototype_ `void OnBuildViewportInteractions(UViewportInteractionsBehaviorSource* Source);`
- L76 _private member_ `TWeakObjectPtr<UActorPickerViewportInteraction> ViewportInteraction;`
- L86 _private prototype_ `void UpdateWidgetVisibility(const WidgetVisibilityState InState, FEditorViewportClient* InViewportClient = nullptr);`
- L87 _private member_ `TFunction<void()> WidgetVisibilityFunction = TFunction<void()>();`

#### enum `FEdModeActorPicker::WidgetVisibilityState`  
`enum class WidgetVisibilityState : uint8`  
_L80-84_
- L82 _public enumerator_ `StoreAndHide`
- L83 _public enumerator_ `Restore`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace EPickState`

### `Source/Editor/ActorPickerMode/Public/ActorPickerMode.h` (Public)


#### class `FActorPickerModeModule`  
`class FActorPickerModeModule : public IModuleInterface`  
_L20-51_
- inherits: `IModuleInterface`
- desc: Actor picker mode module
- L24 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface
- L25 _public prototype_ `virtual void ShutdownModule() override;`
- L34 _public prototype_ `void BeginActorPickingMode(FOnGetAllowedClasses InOnGetAllowedClasses, FOnShouldFilterActor InOnShouldFilterActor, FOnActorSelected InOnActorSelected) const;` — Enter actor picking mode (note: will cancel any current actor picking) @param	InOnGetAllowedClasses	Delegate used to only allow actors using a particular set of classes (empty to accept all actor classes; works alongside InOnShouldFilterActor) @param	InOnShouldFilterActor	Delegate used to only allow particular actors (empty to accept all actors; works alongside InOnGetAllowedClasses) @param	InOnActorSelected		Delegate to call when a valid actor is selected
- L37 _public prototype_ `void EndActorPickingMode() const;` — Exit actor picking mode
- L40 _public prototype_ `bool IsInActorPickingMode() const;` — @return Whether or not actor picking mode is currently active
- L45 _private prototype_ `void OnApplicationDeactivated(const bool IsActive) const;` — Handler for when the application is deactivated.
- L47 _private prototype_ `static FEditorModeTools* GetLevelEditorModeManager();`
- L50 _private member_ `FDelegateHandle OnApplicationDeactivatedHandle;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ACTORPICKERMODE_API`
- L13 _delegate_ `DECLARE_DELEGATE_OneParam( FOnGetAllowedClasses, TArray<const UClass*>& );`
- L13 _prototype_ `DECLARE_DELEGATE_OneParam( FOnGetAllowedClasses, TArray<const UClass*>& );`
- L14 _delegate_ `DECLARE_DELEGATE_OneParam( FOnActorSelected, AActor* );`
- L14 _prototype_ `DECLARE_DELEGATE_OneParam( FOnActorSelected, AActor* );`
- L15 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnShouldFilterActor, const AActor*);`
- L15 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnShouldFilterActor, const AActor*);`
