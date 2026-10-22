# Plugins / XRCreative

- module root: `Plugins/Experimental/XRCreativeFramework/Source/XRCreative`
- headers: 16; symbols: 363
- symbol kinds: class=25, delegate=5, enum=1, enumerator=2, function=24, member=157, namespace=6, prototype=136, struct=3, typedef=4
- PrivateDependencyModuleNames: ConcertSyncClient, ConcertSyncCore, CoreUObject, DeveloperSettings, Engine, EnhancedInput, HeadMountedDisplay, InputCore, InputEditor, InteractiveToolsFramework, LevelEditor, LevelSequence, ModelViewViewModel, MultiUserClient, RenderCore, Slate, SlateCore, TypedElementFramework, TypedElementRuntime, UMG, UnrealEd, VREditor, XRBase
- PublicDependencyModuleNames: CommonUI, Core

### `Plugins/Experimental/XRCreativeFramework/Source/XRCreative/Private/ITF/SelectionInteraction.h` (Private)


#### class `UXRCreativeSelectionInteraction`  
`class UXRCreativeSelectionInteraction : public UObject, public IInputBehaviorSource, public IClickBehaviorTarget`  
_L18-85_
- reflection: `UCLASS()`
- inherits: `UObject,IInputBehaviorSource,IClickBehaviorTarget`
- L23 _public member_ `static constexpr double RayLength = 999999.0;`
- L25 _public typedef_ `using FActorPredicate = TUniqueFunction<bool(AActor*)>;`
- L26 _public typedef_ `using FTraceMethod = TUniqueFunction<FHitResult(const FInputDeviceRay&)>;`
- L28 _public prototype_ `UXRCreativeSelectionInteraction();`
- L37 _public prototype_ `void Initialize( UTypedElementSelectionSet* InSelectionSet, FActorPredicate InCanSelectCallback = nullptr, FTraceMethod InTraceCallback = nullptr);` — Set up the Interaction, creates and registers Behaviors/etc. @param InSelectionSet the typed element selection set we maintain a weak pointer to and operate on @param InCanSelectCallback this function will be called to determine if the selection can be changed to the specified actor (or null); when a tool is active, we may wish to lock selection @param InTraceCallback can be provided to override the default scene trace implementation
- L42 _public prototype_ `void Shutdown();`
- L45 _public function_ `virtual const UInputBehaviorSet* GetInputBehaviors() const` — IInputBehaviorSource interface
- L48 _public prototype_ `virtual FInputRayHit IsHitByClick(const FInputDeviceRay& ClickPos) override;` — IClickBehaviorTarget interface
- L49 _public prototype_ `virtual void OnClicked(const FInputDeviceRay& ClickPos) override;`
- L52 _public prototype_ `virtual void OnUpdateModifierState(int ModifierID, bool bIsOn) override;` — IModifierToggleBehaviorTarget interface
- L55 _protected prototype_ `FTypedElementHandle AcquireActorElementHandle(const AActor* Actor, const bool bAllowCreate);`
- L57 _protected prototype_ `FHitResult DefaultTrace(const FInputDeviceRay& InRay) const;`
- L62 _protected member_ `TObjectPtr<USingleClickInputBehavior> ClickBehavior;` — `UPROPERTY()` — click-to-select behavior
- L66 _protected member_ `TObjectPtr<UInputBehaviorSet> BehaviorSet;` — `UPROPERTY()` — set of all behaviors, will be passed up to UInputRouter
- L69 _protected member_ `TSet<const AActor*> OwnedElementActors;` — TODO: This should either be in a subsystem, or better yet the existing editor-only stores should be made not-editor-only.
- L70 _protected member_ `TTypedElementOwnerStore<FActorElementData, const AActor*> ActorElementOwnerStore;`
- L72 _protected member_ `TWeakObjectPtr<UTypedElementSelectionSet> WeakSelectionSet;`
- L75 _protected function_ `FActorPredicate CanSelectCallback = [](AActor*)` — default predicate allows anything
- L75 _protected member_ `FActorPredicate CanSelectCallback = [](AActor*) { return true; };` — default predicate allows anything
- L77 _protected member_ `FTraceMethod TraceCallback;`
- L80 _protected member_ `static const int AddToSelectionModifier = 1;` — flags used to identify behavior modifier keys/buttons
- L81 _protected member_ `bool bAddToSelectionEnabled = false;`
- L83 _protected member_ `static const int ToggleSelectionModifier = 2;`
- L84 _protected member_ `bool bToggleSelectionEnabled = false;`

### `Plugins/Experimental/XRCreativeFramework/Source/XRCreative/Private/ITF/TransformInteraction.h` (Private)


#### class `UXRCreativeTransformInteraction`  
`class UXRCreativeTransformInteraction : public UObject`  
_L28-86_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: UXRCreativeTransformInteraction manages a 3D Translate/Rotate/Scale (TRS) Gizmo. Gizmo local/global frame is not controlled here, the Gizmo looks this information up itself based on the EToolContextCoordinateSystem provided by the IToolsContextQueriesAPI implementation. You can configure the Gizmo to ignore this, in UpdateGizmoTargets() Behavior of the TRS Gizmo (ie pivot position, etc) is controlled by a standard UTransformProxy.
- L32 _private member_ `static const FString GizmoBuilderIdentifier;`
- L39 _public prototype_ `void Initialize(TSharedRef<FCombinedTransformGizmoActorFactory> InGizmoActorFactory, UTypedElementSelectionSet* InSelectionSet, UInteractiveGizmoManager* InGizmoManager, TUniqueFunction<bool()> InGizmoEnabledCallback);` — Set up the transform interaction. @param InGizmoEnabledCallback callback that determines if Gizmo should be created and visible. For example during a Tool we generally want to hide the TRS Gizmo.
- L44 _public prototype_ `void Shutdown();`
- L47 _public prototype_ `void SetEnableScaling(bool bEnable);` — `UFUNCTION(BlueprintCallable, Category="XR Creative")`
- L50 _public prototype_ `void SetEnableNonUniformScaling(bool bEnable);` — `UFUNCTION(BlueprintCallable, Category="XR Creative")`
- L54 _public prototype_ `void ForceUpdateGizmoState();` — `UFUNCTION(BlueprintCallable, Category="XR Creative")` — Recreate Gizmo. Call when external state changes, like set of selected objects
- L57 _protected member_ `FDelegateHandle SelectionChangedEventHandle;`
- L60 _protected member_ `TObjectPtr<UTransformProxy> TransformProxy;` — `UPROPERTY()`
- L63 _protected member_ `TObjectPtr<UCombinedTransformGizmo> TransformGizmo;` — `UPROPERTY()`
- L65 _protected member_ `TWeakObjectPtr<UTypedElementSelectionSet> WeakSelectionSet;`
- L66 _protected member_ `TWeakObjectPtr<UInteractiveGizmoManager> WeakGizmoManager;`
- L68 _protected member_ `TSharedPtr<FCombinedTransformGizmoActorFactory> GizmoActorFactory;`
- L73 _protected member_ `TArray<TWeakObjectPtr<AActor>> ManipulatedActors;` — Actors driven by TransformProxy. Notified via PostEditMove so the editor world's scene-query acceleration structure (used by ECC_Visibility line traces) stays in sync with their moved collision after a gizmo drag.
- L75 _protected member_ `FDelegateHandle EndTransformEditHandle;`
- L76 _protected member_ `FDelegateHandle TransformChangedUndoRedoHandle;`
- L78 _protected prototype_ `void UpdateGizmoTargets(const UTypedElementSelectionSet* InSelectionSet);`
- L80 _protected prototype_ `void NotifyActorsMoved(bool bFinished);`
- L82 _protected member_ `bool bEnableScaling = true;`
- L83 _protected member_ `bool bEnableNonUniformScaling = true;`
- L85 _protected function_ `TUniqueFunction<bool()> GizmoEnabledCallback = [&]()`
- L85 _protected member_ `TUniqueFunction<bool()> GizmoEnabledCallback = [&]() { return true; };`

### `Plugins/Experimental/XRCreativeFramework/Source/XRCreative/Private/ITF/XRCreativeITFRenderComponent.h` (Private)


#### class `UXRCreativeITFRenderComponent`  
`class UXRCreativeITFRenderComponent : public UPrimitiveComponent`  
_L28-105_
- reflection: `UCLASS()`
- inherits: `UPrimitiveComponent`
- desc: UXRCreativeITFRenderComponent is a helper component that can provide a FPrimitiveDrawInterface API implementation. This PDI can be passed to UInterativeTool::Render() and UInteractiveGizmo::Render() (via a IToolsContextRenderAPI implementation). The UToolsContextRenderComponent will accumulate any DrawLine() and DrawPoint() requests and then pass them to it's SceneProxy for rendering in the next frame. (in the UE Editor, those functions can be passed an Editor PDI that can draw immediately, but this is not possible at Runtime, so we use this accumulate-and-draw workaround) TODO: lines and points could be drawn via Line/Point Components, which would allow them to be batched, providing much better performance.
- L57 _public prototype_ `TSharedPtr<FPrimitiveDrawInterface> GetPDIForView(const FSceneView* InView);` — @return a new FPrimitiveDrawInterface implementation allocated for the given FSceneView. See .cpp for details.
- L60 _public prototype_ `virtual void DrawLine( const FVector& Start, const FVector& End, const FLinearColor& Color, uint8 DepthPriorityGroup, float Thickness = 0.0f, float DepthBias = 0.0f, bool bScreenSpace = false );` — mirrors FPrimitiveDrawInterface::DrawLine()
- L71 _public prototype_ `virtual void DrawPoint( const FVector& Position, const FLinearColor& Color, float PointSize, uint8 DepthPriorityGroup );` — mirrors FPrimitiveDrawInterface::DrawPoint()
- L82 _protected member_ `TArray<FPDILine> CurrentLines;` — set of lines populated by DrawLine calls
- L85 _protected member_ `TArray<FPDIPoint> CurrentPoints;` — set of points created by DrawPoint calls
- L88 _protected member_ `FCriticalSection GeometryLock;` — protects CurrentLines and CurrentPoints
- L92 _protected prototype_ `TUniqueFunction<void(TArray<FPDILine>&, TArray<FPDIPoint>&)> MakeGetCurrentGeometryQueryFunc();` — returns a lambda that will be passed to SceneProxy, which will then allow it to steal values of CurrentLines and CurrentPoints
- L95 _protected prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L96 _protected prototype_ `virtual bool LineTraceComponent(FHitResult& OutHit, const FVector Start, const FVector End, const FCollisionQueryParams& Params) override;`
- L100 _protected prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`

#### struct `UXRCreativeITFRenderComponent::FPDILine`  
`struct FPDILine`  
_L34-43_
- desc: parameters passed to a PDI DrawLine() call
- L36 _public member_ `const FVector Start;`
- L37 _public member_ `const FVector End;`
- L38 _public member_ `const FLinearColor Color;`
- L39 _public member_ `uint8 DepthPriorityGroup;`
- L40 _public member_ `float Thickness;`
- L41 _public member_ `float DepthBias;`
- L42 _public member_ `bool bScreenSpace;`

#### struct `UXRCreativeITFRenderComponent::FPDIPoint`  
`struct FPDIPoint`  
_L46-52_
- desc: parameters passed to a PDI DrawPoint() call
- L48 _public member_ `FVector Position;`
- L49 _public member_ `FLinearColor Color;`
- L50 _public member_ `float PointSize;`
- L51 _public member_ `uint8 DepthPriorityGroup;`

### `Plugins/Experimental/XRCreativeFramework/Source/XRCreative/Private/Module.h` (Private)


#### class `FXRCreativeModule`  
`class FXRCreativeModule : public IModuleInterface`  
_L9-14_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;`
- L13 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/XRCreativeFramework/Source/XRCreative/Private/OneEuroFilter.h` (Private)


#### class `UE::XRCreative::FOneEuroFilter`  
`class FOneEuroFilter`  
_L16-75_
- desc: /
- L48 _public prototype_ `FOneEuroFilter();` — Default constructor
- L50 _public prototype_ `FOneEuroFilter(const double InMinCutoff, const double InCutoffSlope, const double InDeltaCutoff);`
- L53 _public prototype_ `FVector Filter(const FVector& InRaw, const double InDeltaTime);` — Smooth vector
- L56 _public prototype_ `void SetMinCutoff(const double InMinCutoff);` — Set the minimum cutoff
- L59 _public prototype_ `void SetCutoffSlope(const double InCutoffSlope);` — Set the cutoff slope
- L62 _public prototype_ `void SetDeltaCutoff(const double InDeltaCutoff);` — Set the delta slope
- L66 _private prototype_ `const FVector CalculateCutoff(const FVector& InValue);`
- L67 _private prototype_ `const FVector CalculateAlpha(const FVector& InCutoff, const double InDeltaTime) const;`
- L68 _private prototype_ `const double CalculateAlpha(const double InCutoff, const double InDeltaTime) const;`
- L70 _private member_ `double MinCutoff;`
- L71 _private member_ `double CutoffSlope;`
- L72 _private member_ `double DeltaCutoff;`
- L73 _private member_ `FLowpassFilter RawFilter;`
- L74 _private member_ `FLowpassFilter DeltaFilter;`

#### class `UE::XRCreative::FOneEuroFilter::FLowpassFilter`  
`class FLowpassFilter`  
_L20-43_
- L25 _public prototype_ `FLowpassFilter();` — Default constructor
- L28 _public prototype_ `FVector Filter(const FVector& InValue, const FVector& InAlpha);` — Calculate
- L31 _public prototype_ `bool IsFirstTime() const;` — If the filter was not executed yet
- L34 _public prototype_ `FVector GetPrevious() const;` — Get the previous filtered value
- L39 _private member_ `FVector Previous;` — The previous filtered value
- L42 _private member_ `bool bFirstTime;` — If this is the first time doing a filter

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace XRCreative` (scope `UE`)

### `Plugins/Experimental/XRCreativeFramework/Source/XRCreative/Private/XRCreativeLog.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogXRCreative, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogXRCreative, Log, All);`

### `Plugins/Experimental/XRCreativeFramework/Source/XRCreative/Public/XRCreativeAvatar.h` (Public)


#### class `AXRCreativeAvatar`  
`class AXRCreativeAvatar : public APawn`  
_L34-213_
- reflection: `UCLASS()`
- inherits: `APawn`
- L39 _public prototype_ `AXRCreativeAvatar(const FObjectInitializer& ObjectInitializer);`
- L41 _public function_ `virtual bool HasLocalNetOwner() const override`
- L47 _public prototype_ `virtual void OnConstruction(const FTransform& InTransform) override;`
- L48 _public prototype_ `virtual void BeginDestroy() override;`
- L49 _public prototype_ `virtual void Tick(float InDeltaSeconds) override;`
- L50 _public prototype_ `virtual void BeginPlay() override;`
- L51 _public prototype_ `virtual void GetActorEyesViewPoint(FVector& Location, FRotator& Rotation) const override;`
- L53 _public prototype_ `void ConfigureToolset(UXRCreativeToolset* InToolset);`
- L54 _public function_ `const UXRCreativeToolset* GetToolset() const`
- L55 _public function_ `const TArray<TObjectPtr<UXRCreativeTool>>& GetTools() const`
- L58 _public prototype_ `FTransform GetHeadTransform() const;` — `UFUNCTION(BlueprintCallable, Category="XR Creative")`
- L61 _public prototype_ `FTransform GetHeadTransformRoomSpace() const;` — `UFUNCTION(BlueprintCallable, Category="XR Creative")`
- L63 _public prototype_ `bool GetLaserForHand(EControllerHand InHand, FVector& OutLaserStart, FVector& OutLaserEnd) const;`
- L66 _public prototype_ `void SetComponentTickInEditor(UActorComponent* Component, bool bShouldTickInEditor);` — `UFUNCTION(BlueprintCallable, Category="XR Creative")`
- L76 _public prototype_ `void RegisterObjectForInput(UObject* Object);` — `UFUNCTION(BlueprintCallable, Category="XR Creative")` — Registers the given object with the Avatar's Input Component This allows dynamic input bindings such as input events in blueprints to work correctly Note: Ensure you call UnregisterObjectForInput when you are finished with the object otherwise input events will still fire until GC actually destroys the object @param Object The object to register
- L83 _public prototype_ `void UnregisterObjectForInput(UObject* Object);` — `UFUNCTION(BlueprintCallable, Category="XR Creative")` — Unregisters the given object with the Avatar's Input Component @param Object The object to unregister
- L87 _public prototype_ `void AddInputMappingContext(UInputMappingContext* Context, int32 Priority, const FModifyContextOptions Options);` — `UFUNCTION(BlueprintCallable, Category="XR Creative")` — Adds an explicitly provided Input Mapping Context to the input system
- L91 _public prototype_ `void RemoveInputMappingContext(UInputMappingContext* Context, const FModifyContextOptions Options);` — `UFUNCTION(BlueprintCallable, Category="XR Creative")` — Removes an explicitly provided Input Mapping Context to the input system
- L94 _public prototype_ `void ClearAllInputMappings();` — `UFUNCTION(BlueprintCallable, Category="XR Creative")`
- L100 _public prototype_ `void BP_OnVRInitialize();` — `UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="XR Creative", meta=(DisplayName = "On Enter VR"))`
- L109 _public prototype_ `virtual void PlayHapticEffect(UHapticFeedbackEffect_Base* HapticEffect, const int ControllerID, const EControllerHand Hand, float Scale, bool bLoop);` — `UFUNCTION(BlueprintCallable, Category="XR Creative")` — Play haptic feedback asset on a given hand - only left and right supported @param HapticEffect			The haptic effect to play @param Hand					Which hand to play the haptic effect on @param ControllerID			ID of PlayerController if in PIE or runtime (not required in-editor) @param Scale					Scale between 0.0 and 1.0 on the intensity of playback
- L116 _public prototype_ `void StopHapticEffect(EControllerHand Hand, const int ControllerID);` — `UFUNCTION(BlueprintCallable, Category="XR Creative")` — Instantly stop a haptic feedback for a given hand - only left and right supported @param Hand					Which hand to stop the haptic effect on @param ControllerID			ID of PlayerController if in PIE or runtime (not required in-editor)
- L121 _public function_ `AActor* SpawnTransientActor(TSubclassOf<AActor> ActorClass, const FString& ActorName)` — `UFUNCTION(BlueprintCallable, Category="XR Creative")` — Includes special handling to not dirty editor worlds.
- L126 _public function_ `AActor* SpawnTransientActor(TSubclassOf<AActor> ActorClass, const FString& ActorName, TFunctionRef<void (AActor*)> DeferredConstructionCallback)`
- L133 _public prototype_ `ALevelSequenceActor* OpenLevelSequence(ULevelSequence* LevelSequence);` — `UFUNCTION(BlueprintCallable, Category="XR Creative")`
- L140 _protected prototype_ `IEnhancedInputSubsystemInterface* GetEnhancedInputSubsystemInterface() const;` — Gets the input interface for the currently active input method. Will switch between editor and player based input as needed
- L143 _protected prototype_ `void RegisterInputComponent();` — Utility functions for registering and unregistering our input component with the correct input system
- L144 _protected prototype_ `void UnregisterInputComponent();`
- L146 _protected member_ `bool bIsInputRegistered = false;`
- L148 _protected prototype_ `void ProcessHaptics(const float DeltaTime);`
- L151 _protected member_ `TSharedPtr<FActiveHapticFeedbackEffect> ActiveHapticEffect_Left;` — Currently playing haptic effects for both the left and right hand
- L152 _protected member_ `TSharedPtr<FActiveHapticFeedbackEffect> ActiveHapticEffect_Right;`
- L155 _protected prototype_ `AActor* InternalSpawnTransientActor(TSubclassOf<AActor> ActorClass, const FString& ActorName, TOptional<TFunctionRef<void (AActor*)>> DeferredConstructionCallback);` — Includes special handling to not dirty editor worlds.
- L158 _protected prototype_ `void MultiUserStartup();`
- L159 _protected prototype_ `void MultiUserShutdown();`
- L161 _protected prototype_ `void HandleSessionStartup(TSharedRef<IConcertClientSession> InSession);`
- L162 _protected prototype_ `void HandleSessionShutdown(TSharedRef<IConcertClientSession> InSession);`
- L165 _protected member_ `FDelegateHandle OnSessionStartupHandle;` — Delegate handle for a the callback when a session starts up
- L168 _protected member_ `FDelegateHandle OnSessionShutdownHandle;` — Delegate handle for a the callback when a session shuts down
- L171 _protected member_ `TWeakPtr<IConcertClientSession> WeakSession;` — Weak pointer to the client session with which to send events. May be null or stale.
- L176 _protected member_ `TObjectPtr<UMotionControllerComponent> LeftController;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="XR Creative Avatar")`
- L179 _protected member_ `TObjectPtr<UMotionControllerComponent> LeftControllerAim;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="XR Creative Avatar")`
- L182 _protected member_ `TObjectPtr<UXRCreativePointerComponent> LeftControllerPointer;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="XR Creative Avatar")`
- L185 _protected member_ `TObjectPtr<UMotionControllerComponent> RightController;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="XR Creative Avatar")`
- L188 _protected member_ `TObjectPtr<UMotionControllerComponent> RightControllerAim;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="XR Creative Avatar")`
- L191 _protected member_ `TObjectPtr<UXRCreativePointerComponent> RightControllerPointer;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="XR Creative Avatar")`
- L194 _protected member_ `TObjectPtr<USkeletalMeshComponent> LeftControllerModel;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="XR Creative Avatar")`
- L197 _protected member_ `TObjectPtr<USkeletalMeshComponent> RightControllerModel;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="XR Creative Avatar")`
- L200 _protected member_ `TObjectPtr<UWidgetComponent> MenuWidget;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="XR Creative Avatar")`
- L203 _protected member_ `TObjectPtr<UWidgetInteractionComponent> WidgetInteraction;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="XR Creative Avatar")`
- L206 _protected member_ `TObjectPtr<UXRCreativeITFComponent> ToolsComponent;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="XR Creative Avatar")`
- L209 _protected member_ `TObjectPtr<UXRCreativeToolset> Toolset;` — `UPROPERTY(BlueprintReadOnly, Category="XR Creative Avatar")`
- L212 _protected member_ `TArray<TObjectPtr<UXRCreativeTool>> Tools;` — `UPROPERTY(BlueprintReadOnly, Category="XR Creative Avatar")`

### `Plugins/Experimental/XRCreativeFramework/Source/XRCreative/Public/XRCreativeGameMode.h` (Public)


#### class `AXRCreativeGameMode`  
`class AXRCreativeGameMode : public AGameModeBase`  
_L13-23_
- reflection: `UCLASS()`
- inherits: `AGameModeBase`
- L18 _public prototype_ `UXRCreativeToolset* GetToolset() const;`
- L22 _protected member_ `TSoftObjectPtr<UXRCreativeToolset> ToolsetClass;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="XR Creative")`

### `Plugins/Experimental/XRCreativeFramework/Source/XRCreative/Public/XRCreativeGizmos.h` (Public)


#### class `UXRCreativeGizmoBuilder`  
`class UXRCreativeGizmoBuilder : public UCombinedTransformGizmoBuilder`  
_L21-29_
- reflection: `UCLASS()`
- inherits: `UCombinedTransformGizmoBuilder`
- desc: Responsible for instantiating our UXRCreativeGizmo subclass.
- L26 _public prototype_ `UXRCreativeGizmoBuilder();`
- L28 _public prototype_ `virtual UInteractiveGizmo* BuildGizmo(const FToolBuilderState& SceneState) const override;`

#### class `UXRCreativeGizmo`  
`class UXRCreativeGizmo : public UCombinedTransformGizmo`  
_L34-55_
- reflection: `UCLASS()`
- inherits: `UCombinedTransformGizmo`
- desc: Implements our UpdateHoverFunction, and introduces an analogous UpdateInteractingFunction.
- L39 _public prototype_ `virtual void Setup() override;`
- L40 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L43 _protected typedef_ `using FTransformSubGizmoCommonParams = UE::GizmoUtil::FTransformSubGizmoCommonParams;`
- L44 _protected typedef_ `using FTransformSubGizmoSharedState = UE::GizmoUtil::FTransformSubGizmoSharedState;`
- L46 _protected prototype_ `virtual UInteractiveGizmo* AddAxisTranslationGizmo(FTransformSubGizmoCommonParams& Params, FTransformSubGizmoSharedState& SharedState) override;`
- L47 _protected prototype_ `virtual UInteractiveGizmo* AddPlaneTranslationGizmo(FTransformSubGizmoCommonParams& Params, FTransformSubGizmoSharedState& SharedState) override;`
- L48 _protected prototype_ `virtual UInteractiveGizmo* AddAxisRotationGizmo(FTransformSubGizmoCommonParams& Params, FTransformSubGizmoSharedState& SharedState) override;`
- L49 _protected prototype_ `virtual UInteractiveGizmo* AddAxisScaleGizmo(FTransformSubGizmoCommonParams& Params, FTransformSubGizmoSharedState& SharedState) override;`
- L50 _protected prototype_ `virtual UInteractiveGizmo* AddPlaneScaleGizmo(FTransformSubGizmoCommonParams& Params, FTransformSubGizmoSharedState& SharedState) override;`
- L51 _protected prototype_ `virtual UInteractiveGizmo* AddUniformScaleGizmo(FTransformSubGizmoCommonParams& Params, FTransformSubGizmoSharedState& SharedState) override;`
- L54 _protected member_ `TFunction<void(UPrimitiveComponent*, bool)> UpdateInteractingFunction;`

#### class `AXRCreativeCombinedTransformGizmoActor`  
`class AXRCreativeCombinedTransformGizmoActor : public ACombinedTransformGizmoActor`  
_L62-174_
- reflection: `UCLASS(Blueprintable, NonTransient)`
- inherits: `ACombinedTransformGizmoActor`
- L67 _public prototype_ `AXRCreativeCombinedTransformGizmoActor();`
- L69 _public prototype_ `void SetEnabledElements(ETransformGizmoSubElements EnableElements);`
- L72 _public member_ `TObjectPtr<USceneComponent> WorldAligned;` — `UPROPERTY(BlueprintReadOnly, Category="Gizmo")`
- L74 _public member_ `TWeakObjectPtr<UInteractiveGizmoManager> WeakGizmoManager;`
- L76 _public member_ `TWeakObjectPtr<AXRCreativeAvatar> OwnerAvatar;`
- L80 _public function_ `AXRCreativeAvatar* GetOwnerAvatar()` — `UFUNCTION(BlueprintCallable, Category="XRCreative|Gizmo")` — Get the XRCreative Avatar that spawned this Gizmo
- L90 _public member_ `TObjectPtr<USceneComponent> XRSceneRoot;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gizmo")`
- L98 _public member_ `TObjectPtr<UXRCreativeGizmoMeshComponent> XRTranslateX;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gizmo")` — X Axis Translation Component
- L102 _public member_ `TObjectPtr<UXRCreativeGizmoMeshComponent> XRTranslateY;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gizmo")` — Y Axis Translation Component
- L106 _public member_ `TObjectPtr<UXRCreativeGizmoMeshComponent> XRTranslateZ;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gizmo")` — Z Axis Translation Component
- L111 _public member_ `TObjectPtr<UXRCreativeGizmoMeshComponent> XRTranslateYZ;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gizmo")` — YZ Plane Translation Component
- L115 _public member_ `TObjectPtr<UXRCreativeGizmoMeshComponent> XRTranslateXZ;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gizmo")` — XZ Plane Translation Component
- L119 _public member_ `TObjectPtr<UXRCreativeGizmoMeshComponent> XRTranslateXY;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gizmo")` — XY Plane Translation Component
- L127 _public member_ `TObjectPtr<UXRCreativeGizmoMeshComponent> XRRotateX;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gizmo")` — X Axis Rotation Component
- L131 _public member_ `TObjectPtr<UXRCreativeGizmoMeshComponent> XRRotateY;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gizmo")` — Y Axis Rotation Component
- L135 _public member_ `TObjectPtr<UXRCreativeGizmoMeshComponent> XRRotateZ;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gizmo")` — Z Axis Rotation Component
- L139 _public member_ `TObjectPtr<UXRCreativeGizmoMeshComponent> XRRotationSphere;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gizmo")` — Z Axis Rotation Component
- L147 _public member_ `TObjectPtr<UXRCreativeGizmoMeshComponent> XRUniformScale;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gizmo")` — Uniform Scale Component
- L152 _public member_ `TObjectPtr<UXRCreativeGizmoMeshComponent> XRAxisScaleX;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gizmo")` — X Axis Scale Component
- L156 _public member_ `TObjectPtr<UXRCreativeGizmoMeshComponent> XRAxisScaleY;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gizmo")` — Y Axis Scale Component
- L160 _public member_ `TObjectPtr<UXRCreativeGizmoMeshComponent> XRAxisScaleZ;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gizmo")` — Z Axis Scale Component
- L165 _public member_ `TObjectPtr<UXRCreativeGizmoMeshComponent> XRPlaneScaleYZ;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gizmo")` — YZ Plane Scale Component
- L169 _public member_ `TObjectPtr<UXRCreativeGizmoMeshComponent> XRPlaneScaleXZ;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gizmo")` — XZ Plane Scale Component
- L173 _public member_ `TObjectPtr<UXRCreativeGizmoMeshComponent> XRPlaneScaleXY;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gizmo")` — XY Plane Scale Component

#### class `UXRCreativeGizmoMeshComponent`  
`class UXRCreativeGizmoMeshComponent : public UStaticMeshComponent`  
_L181-218_
- reflection: `UCLASS()`
- inherits: `UStaticMeshComponent`
- L186 _public prototype_ `void Initialize();`
- L187 _public prototype_ `void UpdateHoverState(bool bInHovering);`
- L188 _public prototype_ `void UpdateInteractingState(bool bInInteracting);`
- L191 _public member_ `FXRCreativeGizmoStateChanged OnHoveringChanged;` — `UPROPERTY(BlueprintAssignable)`
- L194 _public member_ `FXRCreativeGizmoStateChanged OnInteractingChanged;` — `UPROPERTY(BlueprintAssignable)`
- L196 _public prototype_ `FTransform CalcViewDependent(const FViewCameraState& InView, EToolContextCoordinateSystem InCoords) const;`
- L198 _public member_ `IGizmoAxisSource* AxisSource = nullptr;`
- L202 _protected member_ `bool bHovering;` — `UPROPERTY(BlueprintReadOnly, Category="Gizmo")`
- L205 _protected member_ `bool bInteracting;` — `UPROPERTY(BlueprintReadOnly, Category="Gizmo")`
- L208 _protected member_ `float HideAbsoluteViewDotThreshold = -1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gizmo")`
- L211 _protected member_ `bool bReflectOnPrimaryAxis;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gizmo")`
- L214 _protected member_ `bool bReflectOnTangentAxes;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gizmo")`
- L217 _protected member_ `TArray<TObjectPtr<UMaterialInstanceDynamic>> Materials;` — `UPROPERTY(Transient)`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace GizmoUtil` (scope `UE`)
- L177 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FXRCreativeGizmoStateChanged, UXRCreativeGizmoMeshComponent*, Component, bool, bNewState);`
- L177 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FXRCreativeGizmoStateChanged, UXRCreativeGizmoMeshComponent*, Component, bool, bNewState);`

### `Plugins/Experimental/XRCreativeFramework/Source/XRCreative/Public/XRCreativeITFComponent.h` (Public)


#### class `UXRCreativeITFComponent`  
`class UXRCreativeITFComponent : public UActorComponent`  
_L31-162_
- reflection: `UCLASS()`
- inherits: `UActorComponent`
- L36 _public prototype_ `UXRCreativeITFComponent();`
- L38 _public prototype_ `void SetPointerComponent(UXRCreativePointerComponent* InPointer);`
- L40 _public prototype_ `virtual void InitializeComponent() override;`
- L41 _public prototype_ `virtual void UninitializeComponent() override;`
- L42 _public prototype_ `virtual void TickComponent(float InDeltaTime, enum ELevelTick InTickType, FActorComponentTickFunction* InThisTickFunction) override;`
- L44 _public prototype_ `bool IsInEditor() const;`
- L48 _public prototype_ `bool CanUndo() const;` — `UFUNCTION(BlueprintCallable, Category="XR Creative|Tools")`
- L51 _public prototype_ `bool CanRedo() const;` — `UFUNCTION(BlueprintCallable, Category="XR Creative|Tools")`
- L54 _public prototype_ `void Undo();` — `UFUNCTION(BlueprintCallable, Category="XR Creative|Tools")`
- L57 _public prototype_ `void Redo();` — `UFUNCTION(BlueprintCallable, Category="XR Creative|Tools")`
- L59 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUndoRedo);`
- L62 _public member_ `FOnUndoRedo OnUndo;` — `UPROPERTY(BlueprintAssignable, Category="XR Creative|Tools")`
- L65 _public member_ `FOnUndoRedo OnRedo;` — `UPROPERTY(BlueprintAssignable, Category="XR Creative|Tools")`
- L69 _public prototype_ `void LeftMousePressed();` — `UFUNCTION(BlueprintCallable, Category="XR Creative|Tools")`
- L72 _public prototype_ `void LeftMouseReleased();` — `UFUNCTION(BlueprintCallable, Category="XR Creative|Tools")`
- L76 _public prototype_ `UTypedElementSelectionSet* GetSelectionSet() const;` — `UFUNCTION(BlueprintCallable, Category="XR Creative|Tools")`
- L80 _public prototype_ `bool HaveActiveTool();` — `UFUNCTION(BlueprintCallable, Category="XR Creative|Tools")`
- L84 _public function_ `EToolContextCoordinateSystem GetCurrentCoordinateSystem() const` — `UFUNCTION(BlueprintCallable, Category="XR Creative|Tools")`
- L87 _public prototype_ `void SetCurrentCoordinateSystem(EToolContextCoordinateSystem CoordSystem);` — `UFUNCTION(BlueprintCallable, Category="XR Creative|Tools")`
- L91 _public function_ `EToolContextTransformGizmoMode GetCurrentTransformGizmoMode() const` — `UFUNCTION(BlueprintCallable, Category="XR Creative|Tools")`
- L94 _public prototype_ `void SetCurrentTransformGizmoMode(EToolContextTransformGizmoMode GizmoMode);` — `UFUNCTION(BlueprintCallable, Category="XR Creative|Tools")`
- L97 _public prototype_ `void RecreateActorPhysicsState(AActor* Actor);` — `UFUNCTION(BlueprintCallable, Category="XR Creative|Tools")`
- L100 _public member_ `TWeakObjectPtr<AXRCreativeCombinedTransformGizmoActor> GizmoActor;` — `UPROPERTY()`
- L103 _public function_ `AXRCreativeCombinedTransformGizmoActor* GetGizmoActor() const` — `UFUNCTION(BlueprintCallable, Category="XR Creative|Tools")`
- L105 _public function_ `TSubclassOf<AXRCreativeCombinedTransformGizmoActor> GetCombinedGizmoActorClass() const`
- L109 _protected member_ `TSubclassOf<AXRCreativeCombinedTransformGizmoActor> CombinedGizmoActorClass;` — `UPROPERTY(EditAnywhere, Category="XR Creative")`
- L112 _protected member_ `TArray<TSubclassOf<AActor>> UnselectableActorClasses;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="XR Creative")`
- L115 _protected member_ `FCanSelectActorPredicate CanSelectPredicate;` — `UPROPERTY(BlueprintReadWrite, Category="XR Creative|Tools")`
- L118 _protected member_ `TObjectPtr<UXRCreativePointerComponent> PointerComponent;` — `UPROPERTY()`
- L121 _protected member_ `TObjectPtr<UInteractiveToolsContext> ToolsContext;` — `UPROPERTY()`
- L124 _protected member_ `TObjectPtr<UTypedElementSelectionSet> SelectionSet;` — `UPROPERTY()`
- L127 _protected member_ `TObjectPtr<UXRCreativeSelectionInteraction> SelectionInteraction;` — `UPROPERTY()`
- L130 _protected member_ `TObjectPtr<UXRCreativeTransformInteraction> TransformInteraction;` — `UPROPERTY()`
- L133 _protected member_ `TObjectPtr<UXRCreativeITFRenderComponent> PDIRenderComponent;` — `UPROPERTY()`
- L136 _protected member_ `EToolContextCoordinateSystem CurrentCoordinateSystem = EToolContextCoordinateSystem::World;` — `UPROPERTY()`
- L139 _protected member_ `EToolContextTransformGizmoMode CurrentTransformGizmoMode = EToolContextTransformGizmoMode::Combined;` — `UPROPERTY()`
- L142 _protected prototype_ `void ToolsTick(float InDeltaTime);`
- L145 _protected prototype_ `void EditorToolsTick(float InDeltaTime);`
- L147 _protected prototype_ `void HandleTransactorUndo(const FTransactionContext& TransactionContext, bool Succeeded);`
- L148 _protected prototype_ `void HandleTransactorRedo(const FTransactionContext& TransactionContext, bool Succeeded);`
- L152 _protected member_ `bool bIsShuttingDown = false;`
- L154 _protected member_ `TSharedPtr<FXRCreativeToolsContextQueriesImpl> ContextQueriesAPI;`
- L155 _protected member_ `TSharedPtr<FXRCreativeToolsContextTransactionImpl> ContextTransactionsAPI;`
- L157 _protected member_ `FVector2D PrevMousePosition = FVector2D::ZeroVector;`
- L158 _protected member_ `FInputDeviceState CurrentMouseState;`
- L159 _protected member_ `bool bPendingMouseStateChange = false;`
- L161 _protected member_ `FViewCameraState CurrentViewCameraState;`

#### Free symbols / members of external scopes

- L27 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(bool, FCanSelectActorPredicate, AActor*, SelectionCandidate);`
- L27 _prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(bool, FCanSelectActorPredicate, AActor*, SelectionCandidate);`
- L59 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUndoRedo);`

### `Plugins/Experimental/XRCreativeFramework/Source/XRCreative/Public/XRCreativePointerComponent.h` (Public)


#### class `UXRCreativePointerComponent`  
`class UXRCreativePointerComponent : public USceneComponent`  
_L18-78_
- reflection: `UCLASS(ClassGroup = ("XR Creative"), meta=(BlueprintSpawnableComponent))`
- inherits: `USceneComponent`
- L23 _public prototype_ `UXRCreativePointerComponent();`
- L25 _public prototype_ `virtual void InitializeComponent() override;`
- L26 _public prototype_ `virtual void UninitializeComponent() override;`
- L27 _public prototype_ `virtual void TickComponent(float InDeltaTime, enum ELevelTick InTickType, FActorComponentTickFunction* InThisTickFunction) override;`
- L34 _public prototype_ `FVector GetRawTraceEnd(const bool bScaledByImpact = true) const;` — `UFUNCTION(BlueprintCallable, Category="XR Creative")` — If bScaledByImpact is false, this returns the raw input to the smoothing filter, `TraceMaxLength` units away in the +X direction. If bScaledByImpact is true, the magnitude is shortened to the length of the blocking hit (if any).
- L41 _public prototype_ `FVector GetFilteredTraceEnd(const bool bScaledByImpact = true) const;` — `UFUNCTION(BlueprintCallable, Category="XR Creative")` — If bScaledByImpact is false, this is the smoothed filter output, roughly `TraceMaxLength` units away, roughly in the +X direction. If bScaledByImpact is true, the magnitude is shortened to match the length of a blocking hit (if any).
- L44 _public function_ `const FHitResult& GetHitResult() const` — `UFUNCTION(BlueprintCallable, Category="XR Creative")`
- L47 _public function_ `bool IsEnabled() const` — `UFUNCTION(BlueprintCallable, Category="XR Creative")`
- L50 _public function_ `void SetEnabled(bool bInEnabled)` — `UFUNCTION(BlueprintCallable, Category="XR Creative")`
- L52 _public prototype_ `FCollisionQueryParams GetQueryParams() const;`
- L56 _protected member_ `float TraceMaxLength;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="XR Creative")`
- L59 _protected member_ `float SmoothingLag;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="XR Creative")`
- L62 _protected member_ `float SmoothingMinCutoff;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="XR Creative")`
- L65 _protected member_ `bool bEnabled;` — `UPROPERTY(EditAnywhere, Getter=IsEnabled, Setter=SetEnabled, Category="XR Creative")`
- L68 _protected member_ `TArray<TObjectPtr<AActor>> IgnoredActors;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="XR Creative")`
- L71 _protected member_ `TArray<TObjectPtr<UPrimitiveComponent>> IgnoredComponents;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="XR Creative")`
- L74 _protected member_ `FVector RawTraceEnd;`
- L75 _protected member_ `FHitResult HitResult;`
- L77 _protected member_ `TPimplPtr<UE::XRCreative::FOneEuroFilter> SmoothingFilter;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace XRCreative` (scope `UE`)

### `Plugins/Experimental/XRCreativeFramework/Source/XRCreative/Public/XRCreativeSettings.h` (Public)


#### enum `EXRCreativeHandedness`  
`enum class EXRCreativeHandedness : uint8`  
_L10-14_
- reflection: `UENUM(BlueprintType)`
- L12 _public enumerator_ `Left UMETA(DisplayName = "Left")`
- L13 _public enumerator_ `Right UMETA(DisplayName = "Right")`

#### class `UXRCreativeSettings`  
`class UXRCreativeSettings : public UDeveloperSettings`  
_L21-32_
- reflection: `UCLASS(Config=XRCreativeSettings, DefaultConfig, DisplayName="XR Creative")`
- inherits: `UDeveloperSettings`
- desc: Per project settings for XRCreative.
- L27 _public prototype_ `virtual FName GetCategoryName() const override;`
- L31 _public prototype_ `static UXRCreativeSettings* GetXRCreativeSettings();` — `UFUNCTION(BlueprintPure, Category="XR Creative")`

#### class `UXRCreativeEditorSettings`  
`class UXRCreativeEditorSettings : public UDeveloperSettings`  
_L40-57_
- inherits: `UDeveloperSettings`
- L46 _public prototype_ `virtual FName GetCategoryName() const override;`
- L50 _public prototype_ `static UXRCreativeEditorSettings* GetXRCreativeEditorSettings();` — `UFUNCTION(BlueprintPure, Category="XR Creative Editor")`
- L56 _public member_ `EXRCreativeHandedness Handedness = EXRCreativeHandedness::Right;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category="XR Creative", meta=(DisplayName="Handedness"))` — Manages Left/Right handedness user preferences. Modifying this setting requires an editor restart to take effect.

### `Plugins/Experimental/XRCreativeFramework/Source/XRCreative/Public/XRCreativeSubsystem.h` (Public)


#### class `UXRCreativeSubsystem`  
`class UXRCreativeSubsystem : public UEngineSubsystem`  
_L13-39_
- reflection: `UCLASS()`
- inherits: `UEngineSubsystem`
- L18 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L21 _public function_ `UMVVMViewModelCollectionObject* GetViewModelCollection() const` — `UFUNCTION(BlueprintCallable, Category="XR Creative|Viewmodel")`
- L29 _public prototype_ `static bool EnterVRMode();` — `UFUNCTION(BlueprintCallable, Category="XR Creative")` — Enter VR Mode
- L33 _public prototype_ `static void ExitVRMode();` — `UFUNCTION(BlueprintCallable, Category="XR Creative")` — Exit VR Mode
- L38 _private member_ `TObjectPtr<UMVVMViewModelCollectionObject> ViewModelCollection;` — `UPROPERTY(Transient)`

### `Plugins/Experimental/XRCreativeFramework/Source/XRCreative/Public/XRCreativeTeleporter.h` (Public)


#### class `AXRCreativeTeleporter`  
`class AXRCreativeTeleporter : public AActor`  
_L13-55_
- reflection: `UCLASS()`
- inherits: `AActor`
- L19 _public prototype_ `AXRCreativeTeleporter(const FObjectInitializer& ObjectInitializer);` — Sets default values for this actor's properties
- L21 _public function_ `virtual bool HasLocalNetOwner() const override`
- L28 _public prototype_ `virtual void Tick(float DeltaTime) override;` — Called every frame
- L32 _protected prototype_ `virtual void BeginPlay() override;` — Called when the game starts or when spawned
- L35 _protected member_ `TObjectPtr<UMotionControllerComponent> LeftController;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="XR Creative Teleporter")`
- L38 _protected member_ `TObjectPtr<UMotionControllerComponent> RightController;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="XR Creative Teleporter")`
- L41 _protected member_ `TObjectPtr<UStaticMeshComponent> TeleportMesh;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="XR Creative Teleporter")`
- L44 _protected member_ `TObjectPtr<UMotionControllerComponent> HeadMountedDisplay;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="XR Creative Teleporter")`
- L47 _protected member_ `TObjectPtr<UStaticMeshComponent> LeftControllerVisual;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="XR Creative Teleporter")`
- L50 _protected member_ `TObjectPtr<UStaticMeshComponent> RightControllerVisual;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="XR Creative Teleporter")`
- L53 _protected member_ `TObjectPtr<UStaticMeshComponent> HMDVisual;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="XR Creative Teleporter")`

### `Plugins/Experimental/XRCreativeFramework/Source/XRCreative/Public/XRCreativeToolActor.h` (Public)


#### class `AXRCreativeToolActor`  
`class AXRCreativeToolActor : public AActor`  
_L12-41_
- reflection: `UCLASS(Blueprintable, Abstract)`
- inherits: `AActor`
- L18 _public prototype_ `AXRCreativeToolActor();` — Sets default values for this actor's properties
- L21 _public member_ `TObjectPtr<AXRCreativeAvatar> OwnerAvatar;` — `UPROPERTY(BlueprintReadWrite, Category="XR Creative")`
- L25 _protected prototype_ `virtual void BeginPlay() override;` — Called when the game starts or when spawned
- L29 _public prototype_ `virtual void Tick(float DeltaTime) override;` — Called every frame
- L34 _public prototype_ `void InitializeTool();` — `UFUNCTION(BlueprintImplementableEvent, BlueprintCallable,Category="XR Creative")`
- L37 _public prototype_ `void TickTool(float DeltaSeconds);` — `UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="XR Creative")`
- L40 _public prototype_ `bool ShutDownTool();` — `UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="XR Creative")`

### `Plugins/Experimental/XRCreativeFramework/Source/XRCreative/Public/XRCreativeToolset.h` (Public)


#### class `UXRCreativePaletteTab`  
`class UXRCreativePaletteTab : public UCommonActivatableWidget`  
_L20-23_
- reflection: `UCLASS()`
- inherits: `UCommonActivatableWidget`

#### class `UXRCreativePalette`  
`class UXRCreativePalette : public UCommonActivatableWidget`  
_L27-40_
- reflection: `UCLASS()`
- inherits: `UCommonActivatableWidget`
- L32 _public function_ `void SetOwner(class AXRCreativeAvatar* InOwner)`
- L36 _protected member_ `TArray<TObjectPtr<UXRCreativePaletteTab>> Tabs;` — `UPROPERTY(BlueprintReadOnly, Category="XR Creative")`
- L39 _protected member_ `TObjectPtr<AXRCreativeAvatar> Owner;` — `UPROPERTY(BlueprintReadWrite, Category="XR Creative")`

#### class `UXRCreativeTool`  
`class UXRCreativeTool : public UObject`  
_L47-62_
- reflection: `UCLASS(Abstract, BlueprintType)`
- inherits: `UObject`
- L53 _public prototype_ `virtual FName GetToolName() const PURE_VIRTUAL( UXRCreativeTool::GetToolName, return NAME_None; );` — `UFUNCTION(BlueprintCallable, Category="XR Creative")`
- L56 _public prototype_ `virtual FText GetDisplayName() const PURE_VIRTUAL( UXRCreativeTool::GetDisplayName, return FText::GetEmpty(); );` — `UFUNCTION(BlueprintCallable, Category="XR Creative")`
- L59 _public prototype_ `virtual TSubclassOf<class UXRCreativePaletteToolTab> GetPaletteTabClass() const PURE_VIRTUAL( UXRCreativeTool::GetPaletteTabClass, return nullptr; );` — `UFUNCTION(BlueprintCallable, Category="XR Creative")`

#### class `UXRCreativeBlueprintableTool`  
`class UXRCreativeBlueprintableTool : public UXRCreativeTool`  
_L66-101_
- reflection: `UCLASS(Abstract, Blueprintable)`
- inherits: `UXRCreativeTool`
- L71 _public function_ `virtual FName GetToolName() const override`
- L72 _public function_ `virtual FText GetDisplayName() const override`
- L73 _public function_ `virtual TSubclassOf<UXRCreativePaletteToolTab> GetPaletteTabClass() const override`
- L76 _public prototype_ `UInputMappingContext* GetToolInputMappingContext();` — `UFUNCTION(BlueprintPure, Category="XR Creative")`
- L80 _protected member_ `FName ToolName;` — `UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="XR Creative")`
- L83 _protected member_ `FText DisplayName;` — `UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="XR Creative")`
- L86 _protected member_ `TSubclassOf<UMVVMViewModelBase> ToolViewmodel;` — `UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="XR Creative")`
- L89 _protected member_ `TSubclassOf<UXRCreativePaletteToolTab> PaletteTabClass;` — `UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="XR Creative")`
- L92 _protected member_ `TSubclassOf<AXRCreativeToolActor> ToolActor;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="XR Creative")`
- L95 _protected member_ `TObjectPtr<UInputMappingContext> RightHandedInputMappingContext;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="XR Creative")`
- L98 _protected member_ `TObjectPtr<UInputMappingContext> LeftHandedInputMappingContext;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="XR Creative")`

#### class `UXRCreativePaletteToolTab`  
`class UXRCreativePaletteToolTab : public UXRCreativePaletteTab`  
_L105-112_
- reflection: `UCLASS()`
- inherits: `UXRCreativePaletteTab`
- L111 _protected member_ `TWeakObjectPtr<UXRCreativeTool> Tool;` — `UPROPERTY(BlueprintReadOnly, Category="XR Creative")`

#### struct `FXRCreativeToolEntry`  
`struct FXRCreativeToolEntry`  
_L118-127_
- reflection: `USTRUCT(BlueprintType)`
- L123 _public member_ `TSubclassOf<UXRCreativeTool> ToolClass;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="XR Creative")`
- L126 _public member_ `TObjectPtr<UTexture2D> ToolIcon;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="XR Creative")`

#### class `UXRCreativeToolset`  
`class UXRCreativeToolset : public UPrimaryDataAsset`  
_L131-172_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UPrimaryDataAsset`
- L141 _public member_ `FText ToolsetName;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="XR Creative")`
- L144 _public member_ `TSubclassOf<AXRCreativeAvatar> Avatar;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="XR Creative")`
- L148 _public member_ `TObjectPtr<UInputMappingContext> RightHandedInputMappingContext;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="XR Creative")` — Default Input Mapping is used for Right-Handed users, or if no LeftInputMappingContext is provided.
- L152 _public member_ `TObjectPtr<UInputMappingContext> LeftHandedInputMappingContext;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="XR Creative")` — If Handedness is selected in XRCreative Settings, uses this entry in place of Default/Right
- L155 _public member_ `TArray<FXRCreativeToolEntry> Tools;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="XR Creative")`
- L158 _public member_ `TSubclassOf<UXRCreativePalette> Palette;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="XR Creative")`
- L161 _public member_ `bool bEnableUIMenuActor = false;` — `UPROPERTY(EditAnywhere, Category="XR Creative")`
- L164 _public function_ `bool GetEnableUIMenuActor() const` — `UFUNCTION(BlueprintCallable, Category="XR Creative")`
- L168 _public member_ `TSubclassOf<AActor> UIMenuActor;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="XR Creative", meta=(EditCondition="bEnableUIMenuActor"))` — Enable for legacy or custom menu actors.
- L171 _public function_ `virtual TSubclassOf<AActor> GetUIMenuActor() const` — `UFUNCTION(BlueprintCallable, Category="XR Creative")`

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogXRCreativeToolset, Log, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogXRCreativeToolset, Log, All);`
