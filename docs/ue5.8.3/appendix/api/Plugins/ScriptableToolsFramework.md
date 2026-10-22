# Plugins / ScriptableToolsFramework

- module root: `Plugins/Runtime/ScriptableToolsFramework/Source/ScriptableToolsFramework`
- headers: 26; symbols: 686
- symbol kinds: class=37, delegate=32, enum=11, enumerator=55, function=27, macro=12, member=178, namespace=1, prototype=328, struct=4, typedef=1
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: Engine, Slate, SlateCore
- PublicDependencyModuleNames: Core, CoreUObject, GeometryCore, InputCore, InteractiveToolsFramework, ModelingComponents, PhysicsCore, RenderCore, UMG

### `Plugins/Runtime/ScriptableToolsFramework/Source/ScriptableToolsFramework/Private/Behaviors/ScriptableToolBehavior.h` (Private)


#### class `UScriptableToolBehavior`  
`class UScriptableToolBehavior : public UObject`  
_L10-22_
- reflection: `UCLASS(Abstract)`
- inherits: `UObject`
- L16 _public function_ `UScriptableToolBehavior()`
- L18 _public prototype_ `void SetDefaultPriority(const FInputCapturePriority& Priority);`
- L20 _public prototype_ `virtual UInputBehavior* GetWrappedBehavior() PURE_VIRTUAL(UScriptableToolBehavior::GetWrappedBehavior, return nullptr;);`

### `Plugins/Runtime/ScriptableToolsFramework/Source/ScriptableToolsFramework/Private/Behaviors/ScriptableToolClickDragBehavior.h` (Private)


#### class `UScriptableToolClickDragBehavior`  
`class UScriptableToolClickDragBehavior : public UScriptableToolBehavior, public IClickDragBehaviorTarget`  
_L16-70_
- reflection: `UCLASS()`
- inherits: `UScriptableToolBehavior,IClickDragBehaviorTarget`
- L21 _public function_ `UScriptableToolClickDragBehavior()`
- L23 _public prototype_ `void Init(TObjectPtr<UScriptableModularBehaviorTool> BehaviorHostIn, FMouseBehaviorModiferCheckDelegate ModifierCheckFuncIn, FTestCanBeginClickDragSequenceDelegate TestCanBeginClickDragSequenceFuncIn, FOnClickPressDelegate OnClickPressFuncIn, FOnClickDragDelegate OnClickDragFuncIn, FOnClickReleaseDelegate OnClickReleaseFuncIn, FOnTerminateDragSequenceDelegate OnTerminateDragSequenceFuncIn, EScriptableToolMouseButton MouseButtonIn, bool bUpdateModifiersDuringDragIn);`
- L33 _public prototype_ `virtual UInputBehavior* GetWrappedBehavior() override;`
- L35 _public prototype_ `virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& PressPos) override;`
- L36 _public prototype_ `virtual void OnClickPress(const FInputDeviceRay& PressPos) override;`
- L37 _public prototype_ `virtual void OnClickDrag(const FInputDeviceRay& DragPos) override;`
- L38 _public prototype_ `virtual void OnClickRelease(const FInputDeviceRay& ReleasePos) override;`
- L39 _public prototype_ `virtual void OnTerminateDragSequence() override;`
- L40 _public prototype_ `virtual void OnUpdateModifierState(int ModifierID, bool bIsOn) override;`
- L45 _private member_ `TObjectPtr<UScriptableModularBehaviorTool> BehaviorHost;` — `UPROPERTY()`
- L48 _private member_ `TObjectPtr<UClickDragInputBehavior> Behavior;` — `UPROPERTY()`
- L51 _private member_ `FMouseBehaviorModiferCheckDelegate ModifierCheckFunc;` — `UPROPERTY()`
- L54 _private member_ `FTestCanBeginClickDragSequenceDelegate TestCanBeginClickDragSequenceFunc;` — `UPROPERTY()`
- L57 _private member_ `FOnClickPressDelegate OnClickPressFunc;` — `UPROPERTY()`
- L60 _private member_ `FOnClickDragDelegate OnClickDragFunc;` — `UPROPERTY()`
- L63 _private member_ `FOnClickReleaseDelegate OnClickReleaseFunc;` — `UPROPERTY()`
- L66 _private member_ `FOnTerminateDragSequenceDelegate OnTerminateDragSequenceFunc;` — `UPROPERTY()`
- L69 _private member_ `EScriptableToolMouseButton MouseButton;` — `UPROPERTY()`

### `Plugins/Runtime/ScriptableToolsFramework/Source/ScriptableToolsFramework/Private/Behaviors/ScriptableToolDoubleClickBehavior.h` (Private)


#### class `UScriptableToolDoubleClickBehavior`  
`class UScriptableToolDoubleClickBehavior : public UScriptableToolSingleClickBehavior`  
_L10-18_
- reflection: `UCLASS()`
- inherits: `UScriptableToolSingleClickBehavior`
- L15 _public function_ `UScriptableToolDoubleClickBehavior()`
- L17 _public prototype_ `virtual USingleClickInputBehavior* CreateNewBehavior() const override;`

### `Plugins/Runtime/ScriptableToolsFramework/Source/ScriptableToolsFramework/Private/Behaviors/ScriptableToolKeyInputBehavior.h` (Private)


#### class `UScriptableToolKeyInputBehavior`  
`class UScriptableToolKeyInputBehavior : public UScriptableToolBehavior, public IKeyInputBehaviorTarget`  
_L15-61_
- reflection: `UCLASS()`
- inherits: `UScriptableToolBehavior,IKeyInputBehaviorTarget`
- L20 _public function_ `UScriptableToolKeyInputBehavior()`
- L22 _public prototype_ `void Init(TObjectPtr<UScriptableModularBehaviorTool> BehaviorHostIn, FMouseBehaviorModiferCheckDelegate ModifierCheckFuncIn, FOnKeyStateToggleDelegate OnKeyPressedFuncIn, FOnKeyStateToggleDelegate OnKeyReleasedFuncIn, FOnForceEndCaptureDelegate_ScriptableTools OnForceEndCaptureFuncIn, const TArray<FKey>& ListenKeysIn, bool bRequireAllKeys);`
- L30 _public prototype_ `virtual UKeyInputBehavior* CreateNewBehavior() const;`
- L31 _public prototype_ `virtual UInputBehavior* GetWrappedBehavior() override;`
- L33 _public prototype_ `virtual void OnKeyPressed(const FKey& KeyID) override;`
- L34 _public prototype_ `virtual void OnKeyReleased(const FKey& KeyID) override;`
- L35 _public prototype_ `virtual void OnForceEndCapture() override;`
- L37 _public prototype_ `virtual void OnUpdateModifierState(int ModifierID, bool bIsOn) override;`
- L42 _private member_ `TObjectPtr<UScriptableModularBehaviorTool> BehaviorHost;` — `UPROPERTY()`
- L45 _private member_ `TObjectPtr<UKeyInputBehavior> Behavior;` — `UPROPERTY()`
- L48 _private member_ `FMouseBehaviorModiferCheckDelegate ModifierCheckFunc;` — `UPROPERTY()`
- L51 _private member_ `FOnKeyStateToggleDelegate OnKeyPressedFunc;` — `UPROPERTY()`
- L54 _private member_ `FOnKeyStateToggleDelegate OnKeyReleasedFunc;` — `UPROPERTY()`
- L57 _private member_ `FOnForceEndCaptureDelegate_ScriptableTools OnForceEndCaptureFunc;` — `UPROPERTY()`
- L60 _private member_ `TArray<FKey> ListenKeys;` — `UPROPERTY()`

### `Plugins/Runtime/ScriptableToolsFramework/Source/ScriptableToolsFramework/Private/Behaviors/ScriptableToolMouseHoverBehavior.h` (Private)


#### class `UScriptableToolMouseHoverBehavior`  
`class UScriptableToolMouseHoverBehavior : public UScriptableToolBehavior, public IHoverBehaviorTarget`  
_L16-61_
- reflection: `UCLASS()`
- inherits: `UScriptableToolBehavior,IHoverBehaviorTarget`
- L21 _public function_ `UScriptableToolMouseHoverBehavior()`
- L23 _public prototype_ `void Init(TObjectPtr<UScriptableModularBehaviorTool> BehaviorHostIn, FMouseBehaviorModiferCheckDelegate HoverModifierCheckFuncIn, FBeginHoverSequenceHitTestDelegate BeginHoverSequenceHitTestFuncIn, FOnBeginHoverDelegate OnBeginHoverFuncIn, FOnUpdateHoverDelegate OnUpdateHoverFuncIn, FOnEndHoverDelegate OnEndHoverFuncIn);`
- L30 _public prototype_ `virtual UInputBehavior* GetWrappedBehavior() override;`
- L32 _public prototype_ `virtual FInputRayHit BeginHoverSequenceHitTest(const FInputDeviceRay& PressPos) override;`
- L33 _public prototype_ `virtual void OnBeginHover(const FInputDeviceRay& DevicePos) override;`
- L34 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) override;`
- L35 _public prototype_ `virtual void OnEndHover() override;`
- L36 _public prototype_ `virtual void OnUpdateModifierState(int ModifierID, bool bIsOn) override;`
- L41 _private member_ `TObjectPtr<UScriptableModularBehaviorTool> BehaviorHost;` — `UPROPERTY()`
- L44 _private member_ `TObjectPtr<UMouseHoverBehavior> Behavior;` — `UPROPERTY()`
- L47 _private member_ `FMouseBehaviorModiferCheckDelegate HoverModifierCheckFunc;` — `UPROPERTY()`
- L50 _private member_ `FBeginHoverSequenceHitTestDelegate BeginHoverSequenceHitTestFunc;` — `UPROPERTY()`
- L53 _private member_ `FOnBeginHoverDelegate OnBeginHoverFunc;` — `UPROPERTY()`
- L56 _private member_ `FOnUpdateHoverDelegate OnUpdateHoverFunc;` — `UPROPERTY()`
- L59 _private member_ `FOnEndHoverDelegate OnEndHoverFunc;` — `UPROPERTY()`

### `Plugins/Runtime/ScriptableToolsFramework/Source/ScriptableToolsFramework/Private/Behaviors/ScriptableToolMouseWheelBehavior.h` (Private)


#### class `UScriptableToolMouseWheelBehavior`  
`class UScriptableToolMouseWheelBehavior : public UScriptableToolBehavior, public IMouseWheelBehaviorTarget`  
_L16-56_
- reflection: `UCLASS()`
- inherits: `UScriptableToolBehavior,IMouseWheelBehaviorTarget`
- L21 _public function_ `UScriptableToolMouseWheelBehavior()`
- L23 _public prototype_ `void Init(TObjectPtr<UScriptableModularBehaviorTool> BehaviorHostIn, FMouseBehaviorModiferCheckDelegate ModifierCheckFuncIn, FTestShouldRespondToMouseWheelDelegate TestShouldRespondToMouseWheelFuncIn, FOnMouseWheelScrollUpDelegate OnMouseWheelScrollUpFuncIn, FOnMouseWheelScrollDownDelegate OnMouseWheelScrollDownFuncIn);`
- L29 _public prototype_ `virtual UInputBehavior* GetWrappedBehavior() override;`
- L31 _public prototype_ `virtual FInputRayHit ShouldRespondToMouseWheel(const FInputDeviceRay& CurrentPos) override;`
- L32 _public prototype_ `virtual void OnMouseWheelScrollUp(const FInputDeviceRay& CurrentPos) override;`
- L33 _public prototype_ `virtual void OnMouseWheelScrollDown(const FInputDeviceRay& CurrentPos) override;`
- L34 _public prototype_ `virtual void OnUpdateModifierState(int ModifierID, bool bIsOn) override;`
- L39 _private member_ `TObjectPtr<UScriptableModularBehaviorTool> BehaviorHost;` — `UPROPERTY()`
- L42 _private member_ `TObjectPtr<UMouseWheelInputBehavior> Behavior;` — `UPROPERTY()`
- L45 _private member_ `FMouseBehaviorModiferCheckDelegate ModifierCheckFunc;` — `UPROPERTY()`
- L48 _private member_ `FTestShouldRespondToMouseWheelDelegate TestShouldRespondToMouseWheelFunc;` — `UPROPERTY()`
- L51 _private member_ `FOnMouseWheelScrollUpDelegate OnMouseWheelScrollUpFunc;` — `UPROPERTY()`
- L54 _private member_ `FOnMouseWheelScrollDownDelegate OnMouseWheelScrollDownFunc;` — `UPROPERTY()`

### `Plugins/Runtime/ScriptableToolsFramework/Source/ScriptableToolsFramework/Private/Behaviors/ScriptableToolMultiClickSequenceBehavior.h` (Private)


#### class `UScriptableToolClickSequenceBehavior`  
`class UScriptableToolClickSequenceBehavior : public UScriptableToolBehavior, public IClickSequenceBehaviorTarget`  
_L16-83_
- reflection: `UCLASS()`
- inherits: `UScriptableToolBehavior,IClickSequenceBehaviorTarget`
- L21 _public function_ `UScriptableToolClickSequenceBehavior()`
- L23 _public prototype_ `void Init(TObjectPtr<UScriptableModularBehaviorTool> BehaviorHostIn, FMouseBehaviorModiferCheckDelegate ModifierCheckFuncIn, FMouseBehaviorModiferCheckDelegate HoverModifierCheckFuncIn, FOnBeginSequencePreviewDelegate OnBeginSequencePreviewFuncIn, FCanBeginClickSequenceDelegate CanBeginClickSequenceFuncIn, FOnBeginClickSequenceDelegate OnBeginClickSequenceFuncIn, FOnNextSequencePreviewDelegate OnNextSequencePreviewFuncIn, FOnNextSequenceClickDelegate OnNextSequenceClickFuncIn, FOnTerminateClickSequenceDelegate OnTerminateClickSequenceFuncIn, FRequestAbortClickSequenceDelegate RequestAbortClickSequenceFuncIn, EScriptableToolMouseButton MouseButtonIn);`
- L35 _public prototype_ `virtual UInputBehavior* GetWrappedBehavior() override;`
- L37 _public prototype_ `virtual void OnBeginSequencePreview(const FInputDeviceRay& ClickPos) override;`
- L38 _public prototype_ `virtual bool CanBeginClickSequence(const FInputDeviceRay& ClickPos) override;`
- L39 _public prototype_ `virtual void OnBeginClickSequence(const FInputDeviceRay& ClickPos) override;`
- L40 _public prototype_ `virtual void OnNextSequencePreview(const FInputDeviceRay& ClickPos) override;`
- L41 _public prototype_ `virtual bool OnNextSequenceClick(const FInputDeviceRay& ClickPos) override;`
- L42 _public prototype_ `virtual void OnTerminateClickSequence() override;`
- L43 _public prototype_ `virtual bool RequestAbortClickSequence() override;`
- L44 _public prototype_ `virtual void OnUpdateModifierState(int ModifierID, bool bIsOn) override;`
- L49 _private member_ `TObjectPtr<UScriptableModularBehaviorTool> BehaviorHost;` — `UPROPERTY()`
- L52 _private member_ `TObjectPtr<UMultiClickSequenceInputBehavior> Behavior;` — `UPROPERTY()`
- L55 _private member_ `FMouseBehaviorModiferCheckDelegate ModifierCheckFunc;` — `UPROPERTY()`
- L58 _private member_ `FMouseBehaviorModiferCheckDelegate HoverModifierCheckFunc;` — `UPROPERTY()`
- L61 _private member_ `FOnBeginSequencePreviewDelegate OnBeginSequencePreviewFunc;` — `UPROPERTY()`
- L64 _private member_ `FCanBeginClickSequenceDelegate CanBeginClickSequenceFunc;` — `UPROPERTY()`
- L67 _private member_ `FOnBeginClickSequenceDelegate OnBeginClickSequenceFunc;` — `UPROPERTY()`
- L70 _private member_ `FOnNextSequencePreviewDelegate OnNextSequencePreviewFunc;` — `UPROPERTY()`
- L73 _private member_ `FOnNextSequenceClickDelegate OnNextSequenceClickFunc;` — `UPROPERTY()`
- L76 _private member_ `FOnTerminateClickSequenceDelegate OnTerminateClickSequenceFunc;` — `UPROPERTY()`
- L79 _private member_ `FRequestAbortClickSequenceDelegate RequestAbortClickSequenceFunc;` — `UPROPERTY()`
- L82 _private member_ `EScriptableToolMouseButton MouseButton;` — `UPROPERTY()`

### `Plugins/Runtime/ScriptableToolsFramework/Source/ScriptableToolsFramework/Private/Behaviors/ScriptableToolSingleClickBehavior.h` (Private)


#### class `UScriptableToolSingleClickBehavior`  
`class UScriptableToolSingleClickBehavior : public UScriptableToolBehavior, public IClickBehaviorTarget`  
_L15-55_
- reflection: `UCLASS()`
- inherits: `UScriptableToolBehavior,IClickBehaviorTarget`
- L20 _public function_ `UScriptableToolSingleClickBehavior()`
- L22 _public prototype_ `void Init(TObjectPtr<UScriptableModularBehaviorTool> BehaviorHostIn, FMouseBehaviorModiferCheckDelegate ModifierCheckFuncIn, FTestIfHitByClickDelegate TestIfHitByClickFuncIn, FOnHitByClickDelegate OnHitByClickFuncIn, EScriptableToolMouseButton MouseButtonIn, bool bHitTestOnReleaseIn);`
- L29 _public prototype_ `virtual USingleClickInputBehavior* CreateNewBehavior() const;`
- L30 _public prototype_ `virtual UInputBehavior* GetWrappedBehavior() override;`
- L32 _public prototype_ `virtual FInputRayHit IsHitByClick(const FInputDeviceRay& ClickPos) override;`
- L33 _public prototype_ `virtual void OnClicked(const FInputDeviceRay& ClickPos) override;`
- L34 _public prototype_ `virtual void OnUpdateModifierState(int ModifierID, bool bIsOn) override;`
- L39 _private member_ `TObjectPtr<UScriptableModularBehaviorTool> BehaviorHost;` — `UPROPERTY()`
- L42 _private member_ `TObjectPtr<USingleClickInputBehavior> Behavior;` — `UPROPERTY()`
- L45 _private member_ `FMouseBehaviorModiferCheckDelegate ModifierCheckFunc;` — `UPROPERTY()`
- L48 _private member_ `FTestIfHitByClickDelegate TestIfHitByClickFunc;` — `UPROPERTY()`
- L51 _private member_ `FOnHitByClickDelegate OnHitByClickFunc;` — `UPROPERTY()`
- L54 _private member_ `EScriptableToolMouseButton MouseButton;` — `UPROPERTY()`

### `Plugins/Runtime/ScriptableToolsFramework/Source/ScriptableToolsFramework/Private/Behaviors/ScriptableToolSingleClickOrDragBehavior.h` (Private)


#### class `UScriptableToolSingleClickOrDragBehavior`  
`class UScriptableToolSingleClickOrDragBehavior : public UScriptableToolBehavior, public IClickDragBehaviorTarget, public IClickBehaviorTarget`  
_L16-81_
- reflection: `UCLASS()`
- inherits: `UScriptableToolBehavior,IClickDragBehaviorTarget,IClickBehaviorTarget`
- L21 _public function_ `UScriptableToolSingleClickOrDragBehavior()`
- L23 _public prototype_ `void Init(TObjectPtr<UScriptableModularBehaviorTool> BehaviorHostIn, FMouseBehaviorModiferCheckDelegate ModifierCheckFuncIn, FTestIfHitByClickDelegate TestIfHitByClickFuncIn, FOnHitByClickDelegate OnHitByClickFuncIn, FTestCanBeginClickDragSequenceDelegate TestCanBeginClickDragSequenceFuncIn, FOnClickPressDelegate OnClickPressFuncIn, FOnClickDragDelegate OnClickDragFuncIn, FOnClickReleaseDelegate OnClickReleaseFuncIn, FOnTerminateDragSequenceDelegate OnTerminateDragSequenceFuncIn, EScriptableToolMouseButton MouseButtonIn, bool bBeginDragIfClickTargetNotHitIn, float ClickDistanceThresholdIn);`
- L36 _public prototype_ `virtual UInputBehavior* GetWrappedBehavior() override;`
- L38 _public prototype_ `virtual FInputRayHit IsHitByClick(const FInputDeviceRay& ClickPos) override;`
- L39 _public prototype_ `virtual void OnClicked(const FInputDeviceRay& ClickPos) override;`
- L40 _public prototype_ `virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& PressPos) override;`
- L41 _public prototype_ `virtual void OnClickPress(const FInputDeviceRay& PressPos) override;`
- L42 _public prototype_ `virtual void OnClickDrag(const FInputDeviceRay& DragPos) override;`
- L43 _public prototype_ `virtual void OnClickRelease(const FInputDeviceRay& ReleasePos) override;`
- L44 _public prototype_ `virtual void OnTerminateDragSequence() override;`
- L45 _public prototype_ `virtual void OnUpdateModifierState(int ModifierID, bool bIsOn) override;`
- L50 _private member_ `TObjectPtr<UScriptableModularBehaviorTool> BehaviorHost;` — `UPROPERTY()`
- L53 _private member_ `TObjectPtr<USingleClickOrDragInputBehavior> Behavior;` — `UPROPERTY()`
- L56 _private member_ `FMouseBehaviorModiferCheckDelegate ModifierCheckFunc;` — `UPROPERTY()`
- L59 _private member_ `FTestIfHitByClickDelegate TestIfHitByClickFunc;` — `UPROPERTY()`
- L62 _private member_ `FOnHitByClickDelegate OnHitByClickFunc;` — `UPROPERTY()`
- L65 _private member_ `FTestCanBeginClickDragSequenceDelegate TestCanBeginClickDragSequenceFunc;` — `UPROPERTY()`
- L68 _private member_ `FOnClickPressDelegate OnClickPressFunc;` — `UPROPERTY()`
- L71 _private member_ `FOnClickDragDelegate OnClickDragFunc;` — `UPROPERTY()`
- L74 _private member_ `FOnClickReleaseDelegate OnClickReleaseFunc;` — `UPROPERTY()`
- L77 _private member_ `FOnTerminateDragSequenceDelegate OnTerminateDragSequenceFunc;` — `UPROPERTY()`
- L80 _private member_ `EScriptableToolMouseButton MouseButton;` — `UPROPERTY()`

### `Plugins/Runtime/ScriptableToolsFramework/Source/ScriptableToolsFramework/Public/BaseTools/ScriptableClickDragTool.h` (Public)


#### class `UScriptableClickDragTool`  
`class UScriptableClickDragTool : public UScriptableInteractiveTool, public IClickDragBehaviorTarget, public IHoverBehaviorTarget`  
_L25-192_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UScriptableInteractiveTool,IClickDragBehaviorTarget,IHoverBehaviorTarget`
- desc: UScriptableClickDragTool is an extension of UScriptableInteractiveTool that supports a "click-drag" interaction, ie capture the input device on press-down and collect any device movement events until release. Hover is also supported. Note: Currently these interactions are only supported for mouse devices, or devices remapped to be a mouse by the UInputRouter. Also currently only the left-mouse-button is supported.
- L35 _public member_ `bool bWantMouseHover = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SingleClick Tool Settings")` — Enable Hover support API functions OnHoverHitTest / OnHoverBegin / OnHoverUpdate / OnHoverEnd for Mouse devices. Defaults to disabled. Cannot be changed dynamically after Setup runs.
- L42 _public member_ `bool bUpdateModifiersDuringDrag = true;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SingleClick Tool Settings")` — Allow Modifiers states to be updated during ClickDrag sequence. Defaults to enabled. Cannot be changed dynamically after Setup runs.
- L50 _public prototype_ `FInputRayHit TestIfCanBeginClickDrag(FInputDeviceRay ClickPos, const FScriptableToolModifierStates& Modifiers);` — `UFUNCTION(BlueprintNativeEvent, Category = "ClickDrag Events")`
- L52 _public prototype_ `virtual FInputRayHit TestIfCanBeginClickDrag_Implementation(FInputDeviceRay ClickPos, const FScriptableToolModifierStates& Modifiers);`
- L56 _public prototype_ `void OnDragBegin(FInputDeviceRay StartPosition, const FScriptableToolModifierStates& Modifiers);` — `UFUNCTION(BlueprintNativeEvent, Category = "ClickDrag Events")`
- L58 _public prototype_ `virtual void OnDragBegin_Implementation(FInputDeviceRay StartPosition, const FScriptableToolModifierStates& Modifiers);`
- L62 _public prototype_ `void OnDragUpdatePosition(FInputDeviceRay NewPosition, const FScriptableToolModifierStates& Modifiers);` — `UFUNCTION(BlueprintNativeEvent, Category = "ClickDrag Events")`
- L64 _public prototype_ `virtual void OnDragUpdatePosition_Implementation(FInputDeviceRay NewPosition, const FScriptableToolModifierStates& Modifiers);`
- L68 _public prototype_ `void OnDragEnd(FInputDeviceRay EndPosition, const FScriptableToolModifierStates& Modifiers);` — `UFUNCTION(BlueprintNativeEvent, Category = "ClickDrag Events")`
- L70 _public prototype_ `virtual void OnDragEnd_Implementation(FInputDeviceRay EndPosition, const FScriptableToolModifierStates& Modifiers);`
- L74 _public prototype_ `void OnDragSequenceCancelled();` — `UFUNCTION(BlueprintNativeEvent, Category = "ClickDrag Events")`
- L76 _public prototype_ `virtual void OnDragSequenceCancelled_Implementation();`
- L79 _public prototype_ `UPARAM(DisplayName="In ClickDrag State") bool InActive` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Input")`
- L100 _public prototype_ `FInputRayHit OnHoverHitTest(FInputDeviceRay HoverPos, const FScriptableToolModifierStates& Modifiers);` — `UFUNCTION(BlueprintNativeEvent, Category = "Hover Events")` — OnHoverHitTest is called to allow the Tool to indicate if it would like to start consuing "hover" input at HoverPos. The Tool can return yes/no and a "hit depth", which will be used to determine if the Tool is given the active hover input stream. The default OnHoverHitTest implement always captures the hover. Once the hover is accepted, the OnHoverBegin event will fire, and then a stream of OnHoverUpdate events. If at any point the hover is no longer relevant, OnHoverUpdate should return false. OnHoverEnd will be called at that point, or if the hover is cancelled for any reason (eg mouse goes out of window, button is pressed, etc) @param HoverPos the current position of the cursor/device, including both a 3D ray from the eye, and (optionally) a 2D mouse position @param Modifiers current modifier key/button state @return a FInputRayHit indicating a hit (true/false) and the hit depth along the hit-ray (0 for "always consume")
- L102 _public prototype_ `virtual FInputRayHit OnHoverHitTest_Implementation(FInputDeviceRay HoverPos, const FScriptableToolModifierStates& Modifiers);`
- L110 _public prototype_ `void OnHoverBegin(FInputDeviceRay HoverPos, const FScriptableToolModifierStates& Modifiers);` — `UFUNCTION(BlueprintNativeEvent, Category = "Hover Events")` — Begin a sequence of Hover input events @param HoverPos the current position of the cursor/device, including both a 3D ray from the eye, and (optionally) a 2D mouse position @param Modifiers current modifier key/button state
- L112 _public prototype_ `virtual void OnHoverBegin_Implementation(FInputDeviceRay HoverPos, const FScriptableToolModifierStates& Modifiers);`
- L121 _public prototype_ `UPARAM(DisplayName="Continue Hovering") bool OnHoverUpdate(FInputDeviceRay HoverPos, const FScriptableToolModifierStates& Modifiers);` — `UFUNCTION(BlueprintNativeEvent, Category = "Hover Events")` — Update an active Hover sequence. OnHoverUpdate is only ever called between OnHoverBegin and OnHoverEnd @param HoverPos the current position of the cursor/device, including both a 3D ray from the eye, and (optionally) a 2D mouse position @param Modifiers current modifier key/button state @return true to continue hovering, false to stop receiving additional hover events
- L124 _public prototype_ `virtual bool OnHoverUpdate_Implementation(FInputDeviceRay HoverPos, const FScriptableToolModifierStates& Modifiers);`
- L131 _public prototype_ `void OnHoverEnd(const FScriptableToolModifierStates& Modifiers);` — `UFUNCTION(BlueprintNativeEvent, Category = "Hover Events")` — Indicate that an active captured Hover sequence has ended. The device may no longer be in the viewport, so no position can be provided. @param Modifiers current modifier key/button state
- L133 _public prototype_ `virtual void OnHoverEnd_Implementation(const FScriptableToolModifierStates& Modifiers);`
- L136 _public prototype_ `UPARAM(DisplayName="In Hover State") bool InActive` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Input")`
- L145 _public prototype_ `UPARAM(DisplayName="Shift Down") bool IsShiftDow` — `UFUNCTION(BlueprintCallable, Category="ScriptableTool|Input")` — @return true if the Shift key is currently held down
- L149 _public prototype_ `UPARAM(DisplayName="Ctrl Down") bool IsCtrlDown` — `UFUNCTION(BlueprintCallable, Category="ScriptableTool|Input")` — @return true if the Ctrl key is currently held down
- L153 _public prototype_ `UPARAM(DisplayName="Alt Down") bool IsAltDown(` — `UFUNCTION(BlueprintCallable, Category="ScriptableTool|Input")` — @return true if the Alt key is currently held down
- L157 _public prototype_ `FScriptableToolModifierStates GetActiveModifiers();` — `UFUNCTION(BlueprintCallable, Category="ScriptableTool|Input")` — @return a struct containing the current Modifier key states
- L162 _public prototype_ `virtual void Setup() override;`
- L165 _public member_ `TObjectPtr<UClickDragInputBehavior> ClickDragBehavior;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional, SkipSerialization)`
- L167 _public member_ `bool bInClickDrag = false;`
- L170 _public member_ `TObjectPtr<UMouseHoverBehavior> MouseHoverBehavior;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional, SkipSerialization)`
- L172 _public member_ `bool bInHover = false;`
- L174 _public member_ `bool bShiftModifier = false;`
- L175 _public member_ `bool bCtrlModifier = false;`
- L176 _public member_ `bool bAltModifier = false;`
- L179 _public prototype_ `virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& PressPos) override;` — IClickDragBehaviorTarget API
- L180 _public prototype_ `virtual void OnClickPress(const FInputDeviceRay& PressPos) override;`
- L181 _public prototype_ `virtual void OnClickDrag(const FInputDeviceRay& DragPos) override;`
- L182 _public prototype_ `virtual void OnClickRelease(const FInputDeviceRay& ReleasePos) override;`
- L183 _public prototype_ `virtual void OnTerminateDragSequence() override;`
- L184 _public prototype_ `virtual void OnUpdateModifierState(int ModifierID, bool bIsOn);`
- L187 _public prototype_ `virtual FInputRayHit BeginHoverSequenceHitTest(const FInputDeviceRay& PressPos);` — IHoverBehaviorTarget API
- L188 _public prototype_ `virtual void OnBeginHover(const FInputDeviceRay& DevicePos);`
- L189 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos);`
- L190 _public prototype_ `virtual void OnEndHover();`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API SCRIPTABLETOOLSFRAMEWORK_API`

### `Plugins/Runtime/ScriptableToolsFramework/Source/ScriptableToolsFramework/Public/BaseTools/ScriptableModularBehaviorTool.h` (Public)


#### class `UScriptableModularBehaviorTool`  
`class UScriptableModularBehaviorTool : public UScriptableInteractiveTool`  
_L26-377_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UScriptableInteractiveTool`
- desc: A Scriptable tool base blueprint class which provides support for user defined mouse interaction behaviors
- L52 _public prototype_ `void AddSingleClickBehavior( const FTestIfHitByClickDelegate IfHitByClick, const FOnHitByClickDelegate OnHitByClick, const FMouseBehaviorModiferCheckDelegate CaptureCheck, int CapturePriority = 100, EScriptableToolMouseButton MouseButton = EScriptableToolMouseButton::LeftButton, bool bHitTestOnRelease = true );` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Input", meta = (AdvancedDisplay = "CaptureCheck, CapturePriority, MouseButton, bHitTestOnRelease"))` — Implements a standard "button-click"-style input behavior The state machine works as follows: 1) on input-device-button-press, hit-test the target. If hit, begin capture 2) on input-device-button-release, hit-test the target. If hit, call OnHitByClick(). If not hit, ignore click. The second hit-test is required to allow the click to be "cancelled" by moving away from the target. This is standard GUI behavior. You can disable this second hit test using the HitTestOnRelease property. This is strongly discouraged. @param IfHitByClick Test if hit by a click @param OnHitByClick Notify that click occurred @param CaptureCheck Only enable capture if returns true @param CapturePriority The priority is used to resolve situations where multiple behaviors want the same capture. Lower values, including negative, have higher priority. @param MouseButton Determines which mouse button the behavior captures on
- L78 _public prototype_ `void AddDoubleClickBehavior( const FTestIfHitByClickDelegate IfHitByClick, const FOnHitByClickDelegate OnHitByClick, const FMouseBehaviorModiferCheckDelegate CaptureCheck, int CapturePriority = 100, EScriptableToolMouseButton MouseButton = EScriptableToolMouseButton::LeftButton, bool bHitTestOnRelease = true );` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Input", meta = (AdvancedDisplay = "CaptureCheck, CapturePriority, MouseButton, bHitTestOnRelease"))` — Implements a standard "button-click"-style input behavior The state machine works as follows: 1) on input-device-button-press, hit-test the target. If hit, begin capture 2) on input-device-button-release, hit-test the target. If hit, call OnHitByClick(). If not hit, ignore click. The second hit-test is required to allow the click to be "cancelled" by moving away from the target. This is standard GUI behavior. You can disable this second hit test using the HitTestOnRelease property. This is strongly discouraged. @param IfHitByClick Test if hit by a click @param OnHitByClick Notify that double click occurred @param CaptureCheck Only enable capture if returns true @param CapturePriority The priority is used to resolve situations where multiple behaviors want the same capture. Lower values, including negative, have higher priority. @param MouseButton Determines which mouse button the behavior captures on
- L107 _public prototype_ `void AddClickDragBehavior( const FTestCanBeginClickDragSequenceDelegate CanBeginClickDragSequence, const FOnClickPressDelegate OnClickPress, const FOnClickDragDelegate OnClickDrag, const FOnClickReleaseDelegate OnClickRelease, const FOnTerminateDragSequenceDelegate OnTerminateDragSequence, const FMouseBehaviorModiferCheckDelegate CaptureCheck, int CapturePriority = 100, EScriptableToolMouseButton MouseButton = EScriptableToolMouseButton::LeftButton, bool bUpdateModifiersDuringDrag = false );` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Input", meta = (AdvancedDisplay = "CaptureCheck, CapturePriority, MouseButton, bUpdateModifiersDuringDrag"))` — Implements a standard "button-click-drag"-style input behavior. The state machine works as follows: 1) on input-device-button-press, call CanBeginClickDragSequence to determine if capture should begin 2) on input-device-move, call OnClickDrag 3) on input-device-button-release, call OnClickRelease If a ForceEndCapture occurs we call OnTerminateDragSequence @param CanBeginClickDragSequence Test if target can begin click-drag interaction at this point @param OnClickPress Notify Target that click press occurred @param OnClickDrag Notify Target that input position has changed @param OnClickRelease Notify Target that click release occurred @param OnTerminateDragSequence Notify Target that click-drag sequence has been explicitly terminated (eg by escape key) @param CaptureCheck Only enable capture if returns true @param CapturePriority The priority is used to resolve situations where multiple behaviors want the same capture. Lower values, including negative, have higher priority. @param MouseButton Determines which mouse button the behavior captures on
- L145 _public prototype_ `void AddSingleClickOrDragBehavior( FTestIfHitByClickDelegate IfHitByClick, FOnHitByClickDelegate OnHitByClick, FTestCanBeginClickDragSequenceDelegate CanBeginClickDragSequence, FOnClickPressDelegate OnClickPress, FOnClickDragDelegate OnClickDrag, FOnClickReleaseDelegate OnClickRelease, FOnTerminateDragSequenceDelegate OnTerminateDragSequence, FMouseBehaviorModiferCheckDelegate CaptureCheck, int CapturePriority = 100, EScriptableToolMouseButton MouseButton = EScriptableToolMouseButton::LeftButton, bool bBeginDragIfClickTargetNotHit = true, float ClickDistanceThreshold = 5.0 );` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Input", meta = (AdvancedDisplay = "CaptureCheck, CapturePriority, MouseButton, bBeginDragIfClickTargetNotHit, ClickDistanceThreshold"))` — SingleClickOrDragBehavior is a combination of a SingleClickBehavior and ClickDragBehavior, and allows for the common UI interaction where a click-and-release does one action, but if the mouse is moved, then a drag interaction is started. For example click-to-select is often combined with a drag-marquee-rectangle in this way. This can be directly implemented with a ClickDragBehavior but requires the client to (eg) detect movement thresholds, etc. This class encapsulates all that state/logic. The ClickDistanceThreshold parameter determines how far the mouse must move (in whatever device units are in use) to switch from a click to drag interaction The bBeginDragIfClickTargetNotHit parameter determines if the drag interaction will be immediately initiated if the initial 'click' mouse-down does not hit a valid clickable target. Defaults to true. @param IfHitByClick Test if hit by a click @param OnHitByClick Notify that click occurred @param CanBeginClickDragSequence Test if target can begin click-drag interaction at this point @param OnClickPress Notify Target that click press occurred @param OnClickDrag Notify Target that input position has changed @param OnClickRelease Notify Target that click release occurred @param OnTerminateDragSequence Notify Target that click-drag sequence has been explicitly terminated (eg by escape key) @param CaptureCheck Only enable capture if returns true @param CapturePriority The priority is used to resolve situations where multiple behaviors want t
- L172 _public prototype_ `void AddMouseWheelBehavior( FTestShouldRespondToMouseWheelDelegate TestShouldRespondToMouseWheel, FOnMouseWheelScrollUpDelegate OnMouseWheelScrollUp, FOnMouseWheelScrollDownDelegate OnMouseWheelScrollDown, FMouseBehaviorModiferCheckDelegate CaptureCheck, int CapturePriority = 100 );` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Input", meta = (AdvancedDisplay = "CaptureCheck, CapturePriority"))` — AddMouseWheelBehavior will run the event "OnMouseWheelScrollUp" and "OnMouseWheelScrollDown" each time the mouse wheel is rotated. It is up to the user to record these in variables or otherwise react to these events. @param TestShouldRespondToMouseWheel The result's bHit property determines whether the mouse wheel action will be captured. (Perhaps the mouse wheel only does something when mousing over some part of a mesh) @param OnMouseWheelScrollUp CurrentPos device position/ray at point where mouse wheel is engaged @param OnMouseWheelScrollDown CurrentPos device position/ray at point where mouse wheel is engaged @param CaptureCheck Only enable capture if returns true @param CapturePriority The priority is used to resolve situations where multiple behaviors want the same capture. Lower values, including negative, have higher priority.
- L207 _public prototype_ `void AddMultiClickSequenceBehavior( FOnBeginSequencePreviewDelegate OnBeginSequencePreview, FCanBeginClickSequenceDelegate CanBeginClickSequence, FOnBeginClickSequenceDelegate OnBeginClickSequence, FOnNextSequencePreviewDelegate OnNextSequencePreview, FOnNextSequenceClickDelegate OnNextSequenceClick, FOnTerminateClickSequenceDelegate OnTerminateClickSequence, FRequestAbortClickSequenceDelegate RequestAbortClickSequence, FMouseBehaviorModiferCheckDelegate CaptureCheck, const FMouseBehaviorModiferCheckDelegate HoverCaptureCheck, int CapturePriority = 100, EScriptableToolMouseButton MouseButton = EScriptableToolMouseButton::LeftButton );` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Input", meta = (AdvancedDisplay = "CaptureCheck, HoverCaptureCheck, CapturePriority, MouseButton"))` — MultiClickSequenceBehavior implements a generic multi-click-sequence input behavior. For example this behavior could be used to implement a multi-click polygon-drawing interaction. The internal state machine works as follows: 1) on input-device-button-press, check if target wants to begin sequence. If so, begin capture. 2) on button *release*, check if target wants to continue or terminate sequence a) if terminate, release capture b) if continue, do nothing (capture continues between presses) The target will receive "preview" notifications (basically hover) during updates where there is not a release. This can be used to (eg) update a rubber-band selection end point @param OnBeginSequencePreview Notify Target device position has changed but a click sequence hasn't begun yet (eg for interactive previews) @param CanBeginClickSequence Test if target would like to begin sequence based on this click. Gets checked both on mouse down and mouse up. @param OnBeginClickSequence Notify Target about the first click in the sequence. @param OnNextSequencePreview Notify Target device position has changed but a click hasn't occurred yet (eg for interactive previews) @param OnNextSequenceClick  Notify Target about next click in sqeuence, returns false to terminate sequence @param OnTerminateClickSequence Notify Target that click sequence has been explicitly terminated (eg by escape key, cancel tool, etc). @param RequestAbortClickSequence Target overrides this and returns true if it wants to a
- L234 _public prototype_ `void AddMouseHoverBehavior( FBeginHoverSequenceHitTestDelegate BeginHoverSequenceHitTest, FOnBeginHoverDelegate OnBeginHover, FOnUpdateHoverDelegate OnUpdateHover, FOnEndHoverDelegate OnEndHover, const FMouseBehaviorModiferCheckDelegate HoverCaptureCheck, int CapturePriority = 100 );` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Input", meta = (AdvancedDisplay = "CaptureCheck, CapturePriority"))` — AddMouseHoverBehavior implements a generic mouse hover behavior. For example, this can be used to change the "mode" of the current tool depending on what actor (if any) the mouse is hovering over. @param BeginHoverSequenceHitTest  Do hover hit-test. If this returns False, no further events below are executed. @param OnBeginHover Initialize hover sequence at given position @param OnUpdateHover Update active hover sequence with new input position @param OnEndHover Terminate active hover sequence @param HoverCaptureCheck  Only enable hover capture if returns true @param CapturePriority The priority is used to resolve situations where multiple behaviors want the same capture. Lower values, including negative, have higher priority.
- L261 _public prototype_ `void AddSingleKeyInputBehavior( FOnKeyStateToggleDelegate OnKeyPressed, FOnKeyStateToggleDelegate OnKeyReleased, FOnForceEndCaptureDelegate_ScriptableTools OnForceEndCaptureFuncIn, FKey Key, const FMouseBehaviorModiferCheckDelegate CaptureCheck, int CapturePriority );` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Input", meta = (AdvancedDisplay = "CaptureCheck, CapturePriority"))`
- L271 _public function_ `void AddSingleKeyInputBehavior( FOnKeyStateToggleDelegate OnKeyPressed, FOnKeyStateToggleDelegate OnKeyReleased, FKey Key, const FMouseBehaviorModiferCheckDelegate CaptureCheck, int CapturePriority)` — `UE_DEPRECATED(5.6, "Use overload that takes an OnForceEndCaptureFunc parameter as well")`
- L296 _public prototype_ `void AddMultiKeyInputBehavior( FOnKeyStateToggleDelegate OnKeyPressed, FOnKeyStateToggleDelegate OnKeyReleased, FOnForceEndCaptureDelegate_ScriptableTools OnForceEndCaptureFuncIn, TArray<FKey> Keys, bool bRequireAllKeys, const FMouseBehaviorModiferCheckDelegate CaptureCheck, int CapturePriority );` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Input", meta = (AdvancedDisplay = "CaptureCheck, CapturePriority"))`
- L307 _public function_ `void AddMultiKeyInputBehavior( FOnKeyStateToggleDelegate OnKeyPressed, FOnKeyStateToggleDelegate OnKeyReleased, TArray<FKey> Keys, bool bRequireAllKeys, const FMouseBehaviorModiferCheckDelegate CaptureCheck, int CapturePriority)` — `UE_DEPRECATED(5.6, "Use overload that takes an OnForceEndCaptureFunc parameter as well")`
- L320 _private member_ `TArray< TObjectPtr<UScriptableToolSingleClickBehavior> > SingleClickBehaviors;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional, SkipSerialization)`
- L323 _private member_ `TArray< TObjectPtr<UScriptableToolDoubleClickBehavior> > DoubleClickBehaviors;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional, SkipSerialization)`
- L326 _private member_ `TArray< TObjectPtr<UScriptableToolClickDragBehavior> > ClickDragBehaviors;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional, SkipSerialization)`
- L329 _private member_ `TArray< TObjectPtr<UScriptableToolSingleClickOrDragBehavior> > SingleClickOrDragBehaviors;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional, SkipSerialization)`
- L332 _private member_ `TArray< TObjectPtr<UScriptableToolMouseWheelBehavior> > MouseWheelBehaviors;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional, SkipSerialization)`
- L335 _private member_ `TArray< TObjectPtr<UScriptableToolClickSequenceBehavior> > MultiClickSequenceBehaviors;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional, SkipSerialization)`
- L338 _private member_ `TArray< TObjectPtr<UScriptableToolMouseHoverBehavior> > MouseHoverBehaviors;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional, SkipSerialization)`
- L341 _private member_ `TArray< TObjectPtr<UScriptableToolKeyInputBehavior> > KeyInputBehaviors;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional, SkipSerialization)`
- L354 _public prototype_ `UPARAM(DisplayName="Shift Down") bool IsShiftDow` — `UFUNCTION(BlueprintCallable, Category="ScriptableTool|Input")` — @return true if the Shift key is currently held down
- L358 _public prototype_ `UPARAM(DisplayName="Ctrl Down") bool IsCtrlDown` — `UFUNCTION(BlueprintCallable, Category="ScriptableTool|Input")` — @return true if the Ctrl key is currently held down
- L362 _public prototype_ `UPARAM(DisplayName="Alt Down") bool IsAltDown(` — `UFUNCTION(BlueprintCallable, Category="ScriptableTool|Input")` — @return true if the Alt key is currently held down
- L366 _public prototype_ `FScriptableToolModifierStates GetActiveModifiers();` — `UFUNCTION(BlueprintCallable, Category="ScriptableTool|Input")` — @return a struct containing the current Modifier key states
- L368 _public prototype_ `void OnUpdateModifierState(int ModifierID, bool bIsOn);`
- L372 _private member_ `bool bShiftModifier = false;`
- L373 _private member_ `bool bCtrlModifier = false;`
- L374 _private member_ `bool bAltModifier = false;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API SCRIPTABLETOOLSFRAMEWORK_API`

### `Plugins/Runtime/ScriptableToolsFramework/Source/ScriptableToolsFramework/Public/BaseTools/ScriptableSingleClickTool.h` (Public)


#### class `UScriptableSingleClickTool`  
`class UScriptableSingleClickTool : public UScriptableInteractiveTool, public IClickBehaviorTarget, public IHoverBehaviorTarget`  
_L30-180_
- reflection: `UCLASS(MinimalAPI, Hidden)`
- inherits: `UScriptableInteractiveTool,IClickBehaviorTarget,IHoverBehaviorTarget`
- desc: UScriptableSingleClickTool is an extension of UScriptableInteractiveTool that supports a "click" interaction, ie button press-down-and-release on an arbitrary Target (defined by the Tool). Note that like a standard GUI click interaction, if the device is moved off the "Target" before the button is released, the click is cancelled. Note that in this context, the Target is defined implicitly by the Tool returning a "hit" for a given input device location, rather than any specific geometry. Hover is also supported. Note: Currently these interactions are only supported for mouse devices, or devices remapped to be a mouse by the UInputRouter. Also currently only the left-mouse-button is supported.
- L40 _public member_ `bool bWantMouseHover = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SingleClick Tool Settings")` — Enable Hover support API functions OnHoverHitTest / OnHoverBegin / OnHoverUpdate / OnHoverEnd for Mouse devices. Defaults to disabled.
- L59 _public prototype_ `FInputRayHit TestIfHitByClick(FInputDeviceRay ClickPos, const FScriptableToolModifierStates& Modifiers);` — `UFUNCTION(BlueprintNativeEvent, Category = "Click Events")` — TestIfHitByClick is called to allow the Tool to indicate if it would like to consume a potential click at ClickPos. The Tool can return yes/no and a "hit depth", which will be used to determine if the Tool is given the click (ie if it has the nearest depth), at which point the OnHitByClick event will fire. The default TestIfHitByClick implementation always captures the click (at depth 0). Note that this function will be called twice for a particular hit - once on mouse-down and once on mouse-up, and if it returns no-hit on mouse-up, the click will be "cancelled", similar to standard GUI click interactions. @param ClickPos the position of the click, including both a 3D ray from the eye, and (optionally) a 2D mouse position @param Modifiers current modifier key/button state @return a FInputRayHit indicating a hit (true/false) and the hit depth along the hit-ray (0 for "always consume")
- L61 _public prototype_ `virtual FInputRayHit TestIfHitByClick_Implementation(FInputDeviceRay ClickPos, const FScriptableToolModifierStates& Modifiers);`
- L70 _public prototype_ `void OnHitByClick(FInputDeviceRay ClickPos, const FScriptableToolModifierStates& Modifiers);` — `UFUNCTION(BlueprintNativeEvent, Category = "Click Events")` — OnHitByClick is called when the Tool has indicated it would like to consume a click event (via TestIfHitByClick), and the click was not cancelled or consumed by a nearer object. @param ClickPos the position of the click, including both a 3D ray from the eye, and (optionally) a 2D mouse position @param Modifiers current modifier key/button state
- L72 _public prototype_ `virtual void OnHitByClick_Implementation(FInputDeviceRay ClickPos, const FScriptableToolModifierStates& Modifiers);`
- L94 _public prototype_ `FInputRayHit OnHoverHitTest(FInputDeviceRay HoverPos, const FScriptableToolModifierStates& Modifiers);` — `UFUNCTION(BlueprintNativeEvent, Category = "Hover Events")` — OnHoverHitTest is called to allow the Tool to indicate if it would like to start consuing "hover" input at HoverPos. The Tool can return yes/no and a "hit depth", which will be used to determine if the Tool is given the active hover input stream. The default OnHoverHitTest implement always captures the hover. Once the hover is accepted, the OnHoverBegin event will fire, and then a stream of OnHoverUpdate events. If at any point the hover is no longer relevant, OnHoverUpdate should return false. OnHoverEnd will be called at that point, or if the hover is cancelled for any reason (eg mouse goes out of window, button is pressed, etc) @param HoverPos the current position of the cursor/device, including both a 3D ray from the eye, and (optionally) a 2D mouse position @param Modifiers current modifier key/button state @return a FInputRayHit indicating a hit (true/false) and the hit depth along the hit-ray (0 for "always consume")
- L96 _public prototype_ `virtual FInputRayHit OnHoverHitTest_Implementation(FInputDeviceRay HoverPos, const FScriptableToolModifierStates& Modifiers);`
- L104 _public prototype_ `void OnHoverBegin(FInputDeviceRay HoverPos, const FScriptableToolModifierStates& Modifiers);` — `UFUNCTION(BlueprintNativeEvent, Category = "Hover Events")` — Begin a sequence of Hover input events @param HoverPos the current position of the cursor/device, including both a 3D ray from the eye, and (optionally) a 2D mouse position @param Modifiers current modifier key/button state
- L106 _public prototype_ `virtual void OnHoverBegin_Implementation(FInputDeviceRay HoverPos, const FScriptableToolModifierStates& Modifiers);`
- L115 _public prototype_ `UPARAM(DisplayName="Continue Hovering") bool OnHoverUpdate(FInputDeviceRay HoverPos, const FScriptableToolModifierStates& Modifiers);` — `UFUNCTION(BlueprintNativeEvent, Category = "Hover Events")` — Update an active Hover sequence. OnHoverUpdate is only ever called between OnHoverBegin and OnHoverEnd @param HoverPos the current position of the cursor/device, including both a 3D ray from the eye, and (optionally) a 2D mouse position @param Modifiers current modifier key/button state @return true to continue hovering, false to stop receiving additional hover events
- L118 _public prototype_ `virtual bool OnHoverUpdate_Implementation(FInputDeviceRay HoverPos, const FScriptableToolModifierStates& Modifiers);`
- L125 _public prototype_ `void OnHoverEnd(const FScriptableToolModifierStates& Modifiers);` — `UFUNCTION(BlueprintNativeEvent, Category = "Hover Events")` — Indicate that an active captured Hover sequence has ended. The device may no longer be in the viewport, so no position can be provided. @param Modifiers current modifier key/button state
- L127 _public prototype_ `virtual void OnHoverEnd_Implementation(const FScriptableToolModifierStates& Modifiers);`
- L130 _public prototype_ `UPARAM(DisplayName="In Hover State") bool InActive` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Input")`
- L139 _public prototype_ `UPARAM(DisplayName="Shift Down") bool IsShiftDow` — `UFUNCTION(BlueprintCallable, Category="ScriptableTool|Input")` — @return true if the Shift key is currently held down
- L143 _public prototype_ `UPARAM(DisplayName="Ctrl Down") bool IsCtrlDown` — `UFUNCTION(BlueprintCallable, Category="ScriptableTool|Input")` — @return true if the Ctrl key is currently held down
- L147 _public prototype_ `UPARAM(DisplayName="Alt Down") bool IsAltDown(` — `UFUNCTION(BlueprintCallable, Category="ScriptableTool|Input")` — @return true if the Alt key is currently held down
- L151 _public prototype_ `FScriptableToolModifierStates GetActiveModifiers();` — `UFUNCTION(BlueprintCallable, Category="ScriptableTool|Input")` — @return a struct containing the current Modifier key states
- L156 _public prototype_ `virtual void Setup() override;`
- L159 _public member_ `TObjectPtr<USingleClickInputBehavior> SingleClickBehavior;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional, SkipSerialization)`
- L162 _public member_ `TObjectPtr<UMouseHoverBehavior> MouseHoverBehavior;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional, SkipSerialization)`
- L164 _public member_ `bool bInHover = false;`
- L166 _public member_ `bool bShiftModifier = false;`
- L167 _public member_ `bool bCtrlModifier = false;`
- L168 _public member_ `bool bAltModifier = false;`
- L171 _public prototype_ `virtual FInputRayHit IsHitByClick(const FInputDeviceRay& ClickPos);` — IClickBehaviorTarget API
- L172 _public prototype_ `virtual void OnClicked(const FInputDeviceRay& ClickPos);`
- L173 _public prototype_ `virtual void OnUpdateModifierState(int ModifierID, bool bIsOn);`
- L176 _public prototype_ `virtual FInputRayHit BeginHoverSequenceHitTest(const FInputDeviceRay& PressPos);` — IHoverBehaviorTarget API
- L177 _public prototype_ `virtual void OnBeginHover(const FInputDeviceRay& DevicePos);`
- L178 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos);`
- L179 _public prototype_ `virtual void OnEndHover();`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API SCRIPTABLETOOLSFRAMEWORK_API`

### `Plugins/Runtime/ScriptableToolsFramework/Source/ScriptableToolsFramework/Public/Behaviors/ScriptableToolBehaviorDelegates.h` (Public)


#### enum `EScriptableToolMouseButton`  
`enum class EScriptableToolMouseButton : uint8`  
_L11-16_
- reflection: `UENUM(BlueprintType)`
- L13 _public enumerator_ `LeftButton`
- L14 _public enumerator_ `RightButton`
- L15 _public enumerator_ `MiddleButton`

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(bool, FMouseBehaviorModiferCheckDelegate, const FInputDeviceState&, InputDeviceState);`
- L18 _prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(bool, FMouseBehaviorModiferCheckDelegate, const FInputDeviceState&, InputDeviceState);`
- L20 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(FInputRayHit, FTestIfHitByClickDelegate, FInputDeviceRay, ClickPos, EScriptableToolMouseButton, MouseButton);`
- L20 _prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(FInputRayHit, FTestIfHitByClickDelegate, FInputDeviceRay, ClickPos, EScriptableToolMouseButton, MouseButton);`
- L21 _delegate_ `DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnHitByClickDelegate, FInputDeviceRay, ClickPos, FScriptableToolModifierStates, Modifiers, EScriptableToolMouseButton, MouseButton);`
- L21 _prototype_ `DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnHitByClickDelegate, FInputDeviceRay, ClickPos, FScriptableToolModifierStates, Modifiers, EScriptableToolMouseButton, MouseButton);`
- L23 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal_ThreeParams(FInputRayHit, FTestCanBeginClickDragSequenceDelegate, FInputDeviceRay, PressPos, FScriptableToolModifierStates, Modifiers, EScriptableToolMouseButton, MouseButton);`
- L23 _prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal_ThreeParams(FInputRayHit, FTestCanBeginClickDragSequenceDelegate, FInputDeviceRay, PressPos, FScriptableToolModifierStates, Modifiers, EScriptableToolMouseButton, MouseButton);`
- L24 _delegate_ `DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnClickPressDelegate, FInputDeviceRay, PressPos, FScriptableToolModifierStates, Modifiers, EScriptableToolMouseButton, MouseButton);`
- L24 _prototype_ `DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnClickPressDelegate, FInputDeviceRay, PressPos, FScriptableToolModifierStates, Modifiers, EScriptableToolMouseButton, MouseButton);`
- L25 _delegate_ `DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnClickDragDelegate, FInputDeviceRay, DragPos, FScriptableToolModifierStates, Modifiers, EScriptableToolMouseButton, MouseButton);`
- L25 _prototype_ `DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnClickDragDelegate, FInputDeviceRay, DragPos, FScriptableToolModifierStates, Modifiers, EScriptableToolMouseButton, MouseButton);`
- L26 _delegate_ `DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnClickReleaseDelegate, FInputDeviceRay, ReleasePos, FScriptableToolModifierStates, Modifiers, EScriptableToolMouseButton, MouseButton);`
- L26 _prototype_ `DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnClickReleaseDelegate, FInputDeviceRay, ReleasePos, FScriptableToolModifierStates, Modifiers, EScriptableToolMouseButton, MouseButton);`
- L27 _delegate_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnTerminateDragSequenceDelegate, FScriptableToolModifierStates, Modifiers, EScriptableToolMouseButton, MouseButton);`
- L27 _prototype_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnTerminateDragSequenceDelegate, FScriptableToolModifierStates, Modifiers, EScriptableToolMouseButton, MouseButton);`
- L29 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(FInputRayHit, FTestShouldRespondToMouseWheelDelegate, FInputDeviceRay, CurrentPos);`
- L29 _prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(FInputRayHit, FTestShouldRespondToMouseWheelDelegate, FInputDeviceRay, CurrentPos);`
- L30 _delegate_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnMouseWheelScrollUpDelegate, FInputDeviceRay, CurrentPos, FScriptableToolModifierStates, Modifiers);`
- L30 _prototype_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnMouseWheelScrollUpDelegate, FInputDeviceRay, CurrentPos, FScriptableToolModifierStates, Modifiers);`
- L31 _delegate_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnMouseWheelScrollDownDelegate, FInputDeviceRay, CurrentPos, FScriptableToolModifierStates, Modifiers);`
- L31 _prototype_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnMouseWheelScrollDownDelegate, FInputDeviceRay, CurrentPos, FScriptableToolModifierStates, Modifiers);`
- L33 _delegate_ `DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeginSequencePreviewDelegate, FInputDeviceRay, ClickPos, FScriptableToolModifierStates, Modifiers, EScriptableToolMouseButton, MouseButton);`
- L33 _prototype_ `DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeginSequencePreviewDelegate, FInputDeviceRay, ClickPos, FScriptableToolModifierStates, Modifiers, EScriptableToolMouseButton, MouseButton);`
- L34 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FCanBeginClickSequenceDelegate, FInputDeviceRay, ClickPos, EScriptableToolMouseButton, MouseButton);`
- L34 _prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FCanBeginClickSequenceDelegate, FInputDeviceRay, ClickPos, EScriptableToolMouseButton, MouseButton);`
- L35 _delegate_ `DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeginClickSequenceDelegate, FInputDeviceRay, ClickPos, FScriptableToolModifierStates, Modifiers, EScriptableToolMouseButton, MouseButton);`
- L35 _prototype_ `DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeginClickSequenceDelegate, FInputDeviceRay, ClickPos, FScriptableToolModifierStates, Modifiers, EScriptableToolMouseButton, MouseButton);`
- L36 _delegate_ `DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnNextSequencePreviewDelegate, FInputDeviceRay, ClickPos, FScriptableToolModifierStates, Modifiers, EScriptableToolMouseButton, MouseButton);`
- L36 _prototype_ `DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnNextSequencePreviewDelegate, FInputDeviceRay, ClickPos, FScriptableToolModifierStates, Modifiers, EScriptableToolMouseButton, MouseButton);`
- L37 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal_ThreeParams(bool, FOnNextSequenceClickDelegate, FInputDeviceRay, ClickPos, FScriptableToolModifierStates, Modifiers, EScriptableToolMouseButton, MouseButton);`
- L37 _prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal_ThreeParams(bool, FOnNextSequenceClickDelegate, FInputDeviceRay, ClickPos, FScriptableToolModifierStates, Modifiers, EScriptableToolMouseButton, MouseButton);`
- L38 _delegate_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnTerminateClickSequenceDelegate, FScriptableToolModifierStates, Modifiers, EScriptableToolMouseButton, MouseButton);`
- L38 _prototype_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnTerminateClickSequenceDelegate, FScriptableToolModifierStates, Modifiers, EScriptableToolMouseButton, MouseButton);`
- L39 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal(bool, FRequestAbortClickSequenceDelegate);`
- L39 _prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal(bool, FRequestAbortClickSequenceDelegate);`
- L41 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(FInputRayHit, FBeginHoverSequenceHitTestDelegate, FInputDeviceRay, CurrentPos, FScriptableToolModifierStates, Modifiers);`
- L41 _prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(FInputRayHit, FBeginHoverSequenceHitTestDelegate, FInputDeviceRay, CurrentPos, FScriptableToolModifierStates, Modifiers);`
- L42 _delegate_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBeginHoverDelegate, FInputDeviceRay, CurrentPos, FScriptableToolModifierStates, Modifiers);`
- L42 _prototype_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBeginHoverDelegate, FInputDeviceRay, CurrentPos, FScriptableToolModifierStates, Modifiers);`
- L43 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FOnUpdateHoverDelegate, FInputDeviceRay, CurrentPos, FScriptableToolModifierStates, Modifiers);`
- L43 _prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FOnUpdateHoverDelegate, FInputDeviceRay, CurrentPos, FScriptableToolModifierStates, Modifiers);`
- L44 _delegate_ `DECLARE_DYNAMIC_DELEGATE(FOnEndHoverDelegate);`
- L44 _prototype_ `DECLARE_DYNAMIC_DELEGATE(FOnEndHoverDelegate);`
- L46 _delegate_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnKeyStateToggleDelegate, FKey, Key, FScriptableToolModifierStates, Modifiers);`
- L46 _prototype_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnKeyStateToggleDelegate, FKey, Key, FScriptableToolModifierStates, Modifiers);`
- L47 _delegate_ `DECLARE_DYNAMIC_DELEGATE(FOnForceEndCaptureDelegate_ScriptableTools);`
- L47 _prototype_ `DECLARE_DYNAMIC_DELEGATE(FOnForceEndCaptureDelegate_ScriptableTools);`

### `Plugins/Runtime/ScriptableToolsFramework/Source/ScriptableToolsFramework/Public/Drawing/ScriptableToolLine.h` (Public)


#### class `UScriptableToolLine`  
`class UScriptableToolLine : public UObject`  
_L16-83_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- L22 _public prototype_ `void SetLineID(int32 LineIDIn);`
- L23 _public prototype_ `int32 GetLineID() const;`
- L25 _public prototype_ `bool IsDirty() const;`
- L26 _public prototype_ `FRenderableLine GenerateLineDescription();`
- L33 _public prototype_ `void SetLineStart(FVector Start);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Drawing|Lines")` — Set the starting position of the line @param Start The position in space of the start of the line
- L40 _public prototype_ `void SetLineEnd(FVector End);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Drawing|Lines")` — Set the ending position of the line @param End The position in space of the end of the line
- L48 _public prototype_ `void SetLineEndPoints(FVector Start, FVector End);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Drawing|Lines")` — Set the starting and ending positions of the line @param Start The position in space of the start of the line @param End The position in space of the end of the line
- L55 _public prototype_ `void SetLineColor(FColor Color);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Drawing|Lines")` — Set the line's color @param Color The color the line should be rendered as
- L62 _public prototype_ `void SetLineThickness(float Thickness);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Drawing|Lines")` — Set the line's thickness @param Thickness The visual thickness in pixels the line should be rendered as
- L71 _public prototype_ `void SetLineDepthBias(float DepthBias);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Drawing|Lines")` — Set the line's depth bias. The depth bias controls small micro adjustments in effective displacement towards or away from the camera, to prevent the line from causing clipping or z-fighting with other objects in the scene it's overlaid directly on top of. @param DepthBias The depth bias adjustment for the line
- L75 _private member_ `FRenderableLine LineDescription;`
- L78 _private member_ `bool bIsDirty = false;` — `UPROPERTY()`
- L81 _private member_ `int32 LineID;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API SCRIPTABLETOOLSFRAMEWORK_API`

### `Plugins/Runtime/ScriptableToolsFramework/Source/ScriptableToolsFramework/Public/Drawing/ScriptableToolLineSet.h` (Public)


#### class `UScriptableToolLineSet`  
`class UScriptableToolLineSet : public UObject`  
_L17-76_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- L23 _public prototype_ `void Initialize(TObjectPtr<UPreviewGeometry> PreviewGeometry);`
- L25 _public prototype_ `void OnTick();`
- L33 _public prototype_ `UPARAM(DisplayName = "LineComponent") UScriptableToolLin` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Drawing|LineSet")` — Create and return a new line object. Users should save a reference to this object for future updates or removal from the set. @return The new line object added to the set.
- L40 _public prototype_ `void RemoveLine(UScriptableToolLine* Line);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Drawing|LineSet")` — Remove a specific line object from the set, removing it fromt the scene. @param Line A reference to a line to be removed from the set.
- L47 _public prototype_ `void RemoveAllLines();` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Drawing|LineSet")` — Remove all current lines in the set.
- L53 _public prototype_ `void SetAllLinesColor(FColor Color);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Drawing|LineSet")` — Set the color of all lines in the set simultaneously.
- L59 _public prototype_ `void SetAllLinesThickness(float Thickness);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Drawing|LineSet")` — Set the thickness of all lines in the set simultaneously.
- L64 _protected member_ `TObjectPtr<UPreviewGeometry> ToolDrawableGeometry = nullptr;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional, SkipSerialization)`
- L68 _protected member_ `TObjectPtr<ULineSetComponent> LineSet = nullptr;` — `UE_DEPRECATED(5.7, "Use WeakLineSet instead.")` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional, SkipSerialization)`
- L71 _protected member_ `TWeakObjectPtr<ULineSetComponent> WeakLineSet = nullptr;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional, SkipSerialization)`
- L74 _protected member_ `TArray<TObjectPtr<UScriptableToolLine>> LineComponents;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional, SkipSerialization)`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SCRIPTABLETOOLSFRAMEWORK_API`

### `Plugins/Runtime/ScriptableToolsFramework/Source/ScriptableToolsFramework/Public/Drawing/ScriptableToolPoint.h` (Public)


#### class `UScriptableToolPoint`  
`class UScriptableToolPoint : public UObject`  
_L16-68_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- L22 _public prototype_ `void SetPointID(int32 PointIDIn);`
- L23 _public prototype_ `int32 GetPointID() const;`
- L25 _public prototype_ `bool IsDirty() const;`
- L26 _public prototype_ `FRenderablePoint GeneratePointDescription();`
- L33 _public prototype_ `void SetPointPosition(FVector Position);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Drawing|Points")` — Set the position of the point @param Position The position in space of the point
- L40 _public prototype_ `void SetPointColor(FColor Color);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Drawing|Points")` — Set the point's color @param Color The color the point should be rendered as
- L47 _public prototype_ `void SetPointSize(float Thickness);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Drawing|Points")` — Set the point's size @param Size The visual size in pixels the point should be rendered as
- L56 _public prototype_ `void SetPointDepthBias(float DepthBias);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Drawing|Points")` — Set the point's depth bias. The depth bias controls small micro adjustments in effective displacement towards or away from the camera, to prevent the point from causing clipping or z-fighting with other objects in the scene it's overlaid directly on top of. @param DepthBias The depth bias adjustment for the point
- L60 _private member_ `FRenderablePoint PointDescription;`
- L63 _private member_ `bool bIsDirty = false;` — `UPROPERTY()`
- L66 _private member_ `int32 PointID;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API SCRIPTABLETOOLSFRAMEWORK_API`

### `Plugins/Runtime/ScriptableToolsFramework/Source/ScriptableToolsFramework/Public/Drawing/ScriptableToolPointSet.h` (Public)


#### class `UScriptableToolPointSet`  
`class UScriptableToolPointSet : public UObject`  
_L17-75_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- L23 _public prototype_ `void Initialize(TObjectPtr<UPreviewGeometry> PreviewGeometry);`
- L25 _public prototype_ `void OnTick();`
- L32 _public prototype_ `UPARAM(DisplayName = "PointComponent") UScriptableToolPoin` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Drawing|PointSet")` — Create and return a new point object. Users should save a reference to this object for future updates or removal from the set. @return The new point object added to the set.
- L40 _public prototype_ `void RemovePoint(UScriptableToolPoint* Point);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Drawing|PointSet")` — Remove a specific point object from the set, removing it from the scene. @param Point A reference to a point to be removed from the set.
- L46 _public prototype_ `void RemoveAllPoints();` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Drawing|PointSet")` — Remove all current points in the set.
- L52 _public prototype_ `void SetAllPointsColor(FColor Color);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Drawing|PointSet")` — Set the color of all points in the set simultaneously.
- L58 _public prototype_ `void SetAllPointsSize(float Size);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Drawing|PointSet")` — Set the size of all points in the set simultaneously.
- L63 _protected member_ `TObjectPtr<UPreviewGeometry> ToolDrawableGeometry = nullptr;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional, SkipSerialization)`
- L67 _protected member_ `TObjectPtr<UPointSetComponent> PointSet = nullptr;` — `UE_DEPRECATED(5.7, "Use WeakPointSet instead.")` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional, SkipSerialization)`
- L70 _protected member_ `TWeakObjectPtr<UPointSetComponent> WeakPointSet = nullptr;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional, SkipSerialization)`
- L73 _protected member_ `TArray<TObjectPtr<UScriptableToolPoint>> PointComponents;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional, SkipSerialization)`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SCRIPTABLETOOLSFRAMEWORK_API`

### `Plugins/Runtime/ScriptableToolsFramework/Source/ScriptableToolsFramework/Public/Drawing/ScriptableToolTriangle.h` (Public)


#### class `UScriptableToolTriangle`  
`class UScriptableToolTriangle : public UObject`  
_L16-89_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- L22 _public prototype_ `UScriptableToolTriangle();`
- L24 _public prototype_ `void SetTriangleID(int32 TriangleIDIn);`
- L25 _public prototype_ `int32 GetTriangleID() const;`
- L27 _public prototype_ `bool IsDirty() const;`
- L28 _public prototype_ `FRenderableTriangle GenerateTriangleDescription();`
- L36 _public prototype_ `void SetTriangleMaterial(UMaterialInterface* Material);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Drawing|Triangles")` — Set the material of the triangle @param Material The new material that should be assigned to the triangle
- L46 _public prototype_ `void SetTrianglePoints(FVector A, FVector B, FVector C);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Drawing|Triangles")` — Set the points of the triangle @param A The position of the first corner of the triangle @param B The position of the second corner of the triangle @param C The position of the third corner of the triangle
- L56 _public prototype_ `void SetTriangleUVs(FVector2D A, FVector2D B, FVector2D C);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Drawing|Triangles")` — Set the UV coordinates of the triangle @param A The UV coordinate of the first corner of the triangle @param B The UV coordinate of the second corner of the triangle @param C The UV coordinate of the third corner of the triangle
- L66 _public prototype_ `void SetTriangleNormals(FVector A, FVector B, FVector C);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Drawing|Triangles")` — Set the normal values of the triangle @param A The normal of the first corner of the triangle @param B The normal of the second corner of the triangle @param C The normal of the third corner of the triangle
- L77 _public prototype_ `void SetTriangleColors(FColor A, FColor B, FColor C);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Drawing|Triangles")` — Set the vertex colors of the triangle @param A The vertex color of the first corner of the triangle @param B The vertex color of the second corner of the triangle @param C The vertex color of the third corner of the triangle
- L81 _private member_ `FRenderableTriangle TriangleDescription;`
- L84 _private member_ `bool bIsDirty = false;` — `UPROPERTY()`
- L87 _private member_ `int32 TriangleID;` — `UPROPERTY()`

#### class `UScriptableToolQuad`  
`class UScriptableToolQuad : public UObject`  
_L92-168_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- L98 _public prototype_ `UScriptableToolQuad();`
- L100 _public prototype_ `void SetTriangleAID(int32 TriangleIDIn);`
- L101 _public prototype_ `int32 GetTriangleAID() const;`
- L102 _public prototype_ `void SetTriangleBID(int32 TriangleIDIn);`
- L103 _public prototype_ `int32 GetTriangleBID() const;`
- L105 _public prototype_ `bool IsDirty() const;`
- L106 _public prototype_ `TPair<FRenderableTriangle, FRenderableTriangle> GenerateQuadDescription();`
- L113 _public prototype_ `void SetQuadMaterial(UMaterialInterface* Material);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Drawing|Quads")` — Set the material of the quad @param Material The new material that should be assigned to the quad
- L123 _public prototype_ `void SetQuadPoints(FVector A, FVector B, FVector C, FVector D);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Drawing|Quads")` — Set the points of the quad @param A The position of the first corner of the quad @param B The position of the second corner of the quad @param C The position of the third corner of the quad @param D The position of the fourth corner of the quad
- L133 _public prototype_ `void SetQuadUVs(FVector2D A, FVector2D B, FVector2D C, FVector2D D);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Drawing|Quads")` — Set the UV coordinates of the quad @param A The UV coordinate of the first corner of the quad @param B The UV coordinate of the second corner of the quad @param C The UV coordinate of the third corner of the quad @param D The UV coordinate of the fourth corner of the quad
- L143 _public prototype_ `void SetQuadNormals(FVector A, FVector B, FVector C, FVector D);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Drawing|Quads")` — Set the normal values of the quad @param A The normal of the first corner of the quad @param B The normal of the second corner of the quad @param C The normal of the third corner of the quad @param D The normal of the fourth corner of the quad
- L153 _public prototype_ `void SetQuadColors(FColor A, FColor B, FColor C, FColor D);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Drawing|Quads")` — Set the vertex colors of the quad @param A The vertex color of the first corner of the quad @param B The vertex color of the second corner of the quad @param C The vertex color of the third corner of the quad @param D The vertex color of the fourth corner of the quad
- L156 _private member_ `FRenderableTriangle TriangleADescription;`
- L157 _private member_ `FRenderableTriangle TriangleBDescription;`
- L160 _private member_ `bool bIsDirty = false;` — `UPROPERTY()`
- L163 _private member_ `int32 TriangleAID;` — `UPROPERTY()`
- L166 _private member_ `int32 TriangleBID;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API SCRIPTABLETOOLSFRAMEWORK_API`

### `Plugins/Runtime/ScriptableToolsFramework/Source/ScriptableToolsFramework/Public/Drawing/ScriptableToolTriangleSet.h` (Public)


#### class `UScriptableToolTriangleSet`  
`class UScriptableToolTriangleSet : public UObject`  
_L18-92_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- L24 _public prototype_ `void Initialize(TObjectPtr<UPreviewGeometry> PreviewGeometry);`
- L26 _public prototype_ `void OnTick();`
- L33 _public prototype_ `UPARAM(DisplayName = "TriangleComponent") UScriptableToolTriangl` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Drawing|TriangleSet")` — Create and return a new triangle object. Users should save a reference to this object for future updates or removal from the set. @return The new triangle object added to the set
- L40 _public prototype_ `UPARAM(DisplayName = "QuadComponent") UScriptableToolQua` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Drawing|TriangleSet")` — Create and return a new quad object. Quad objects are two paired triangles. Users should save a reference to this object for future updates or removal from the set. @return The new quad object added to the set
- L47 _public prototype_ `void RemoveTriangle(UScriptableToolTriangle* Triangle);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Drawing|TriangleSet")` — Remove a specific triangle object from the set, removing it from the scene. @param Triangle A reference to a triangle to be removed from the set.
- L54 _public prototype_ `void RemoveQuad(UScriptableToolQuad* Quad);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Drawing|TriangleSet")` — Remove a specific quad object from the set, removing it from the scene. @param Quad A reference to a quad to be removed from the set.
- L60 _public prototype_ `void RemoveAllFaces();` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Drawing|TriangleSet")` — Remove all current triangles and quads in the set.
- L66 _public prototype_ `void SetAllTrianglesColor(FColor Color);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Drawing|TriangleSet")` — Set the color of all triangles and quads in the set simultaneously .
- L72 _public prototype_ `void SetAllTrianglesMaterial(UMaterialInterface* Material);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Drawing|TriangleSet")` — Set the material of all triangles and quads in the set simultaneously .
- L77 _protected member_ `TObjectPtr<UPreviewGeometry> ToolDrawableGeometry = nullptr;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional, SkipSerialization)`
- L81 _protected member_ `TObjectPtr<UTriangleSetComponent> TriangleSet = nullptr;` — `UE_DEPRECATED(5.7, "Use WeakTriangleSet instead.")` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional, SkipSerialization)`
- L84 _protected member_ `TWeakObjectPtr<UTriangleSetComponent> WeakTriangleSet = nullptr;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional, SkipSerialization)`
- L87 _protected member_ `TArray<TObjectPtr<UScriptableToolTriangle>> TriangleComponents;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional, SkipSerialization)`
- L90 _protected member_ `TArray<TObjectPtr<UScriptableToolQuad>> QuadComponents;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional, SkipSerialization)`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SCRIPTABLETOOLSFRAMEWORK_API`

### `Plugins/Runtime/ScriptableToolsFramework/Source/ScriptableToolsFramework/Public/ScriptableInteractiveTool.h` (Public)


#### enum `EToolsFrameworkOutcomePins`  
`enum class EToolsFrameworkOutcomePins : uint8`  
_L34-38_
- reflection: `UENUM(BlueprintType)`
- L36 _public enumerator_ `Success`
- L37 _public enumerator_ `Failure`

#### enum `EScriptableToolShutdownType`  
`enum class EScriptableToolShutdownType : uint8`  
_L42-46_
- reflection: `UENUM(BlueprintType)`
- L44 _public enumerator_ `Complete = 0`
- L45 _public enumerator_ `AcceptCancel = 1`

#### struct `FScriptableToolModifierStates`  
`struct FScriptableToolModifierStates`  
_L49-61_
- reflection: `USTRUCT(BlueprintType)`
- L54 _public member_ `bool bShiftDown = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modifiers)`
- L57 _public member_ `bool bCtrlDown = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modifiers)`
- L60 _public member_ `bool bAltDown = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modifiers)`

#### enum `EScriptableToolGizmoMode`  
`enum class EScriptableToolGizmoMode : uint8`  
_L66-73_
- reflection: `UENUM(BlueprintType)`
- L68 _public enumerator_ `TranslationOnly = 0`
- L69 _public enumerator_ `RotationOnly = 1`
- L70 _public enumerator_ `ScaleOnly = 2`
- L71 _public enumerator_ `Combined = 3`
- L72 _public enumerator_ `FromViewportSettings = 4`

#### enum `EScriptableToolGizmoCoordinateSystem`  
`enum class EScriptableToolGizmoCoordinateSystem : uint8`  
_L76-81_
- reflection: `UENUM(BlueprintType)`
- L78 _public enumerator_ `World = 0`
- L79 _public enumerator_ `Local = 1`
- L80 _public enumerator_ `FromViewportSettings = 2`

#### enum `EScriptableToolGizmoStateChangeType`  
`enum class EScriptableToolGizmoStateChangeType : uint8`  
_L84-89_
- reflection: `UENUM(BlueprintType)`
- L86 _public enumerator_ `BeginTransform = 0`
- L87 _public enumerator_ `EndTransform = 1`
- L88 _public enumerator_ `UndoRedo = 2`

#### enum `EScriptableToolGizmoTranslation`  
`enum class EScriptableToolGizmoTranslation : uint8`  
_L92-105_
- reflection: `UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- L94 _public enumerator_ `None = 0`
- L96 _public enumerator_ `TranslateAxisX = 1 << 1`
- L97 _public enumerator_ `TranslateAxisY = 1 << 2`
- L98 _public enumerator_ `TranslateAxisZ = 1 << 3`
- L99 _public enumerator_ `TranslatePlaneXY = 1 << 4`
- L100 _public enumerator_ `TranslatePlaneXZ = 1 << 5`
- L101 _public enumerator_ `TranslatePlaneYZ = 1 << 6`
- L102 _public enumerator_ `FreeTranslate = 1 << 7`
- L104 _public enumerator_ `All = 0xFF UMETA(Hidden)`

#### enum `EScriptableToolGizmoRotation`  
`enum class EScriptableToolGizmoRotation : uint8`  
_L110-121_
- reflection: `UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- L112 _public enumerator_ `None = 0`
- L114 _public enumerator_ `RotateAxisX = 1 << 1`
- L115 _public enumerator_ `RotateAxisY = 1 << 2`
- L116 _public enumerator_ `RotateAxisZ = 1 << 3`
- L118 _public enumerator_ `FreeRotate = 1 << 7`
- L120 _public enumerator_ `All = 0xFF UMETA(Hidden)`

#### enum `EScriptableToolGizmoScale`  
`enum class EScriptableToolGizmoScale : uint8`  
_L126-139_
- reflection: `UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- L128 _public enumerator_ `None = 0`
- L130 _public enumerator_ `ScaleAxisX = 1 << 1`
- L131 _public enumerator_ `ScaleAxisY = 1 << 2`
- L132 _public enumerator_ `ScaleAxisZ = 1 << 3`
- L133 _public enumerator_ `ScalePlaneXY = 1 << 4`
- L134 _public enumerator_ `ScalePlaneXZ = 1 << 5`
- L135 _public enumerator_ `ScalePlaneYZ = 1 << 6`
- L136 _public enumerator_ `ScaleUniform = 1 << 7`
- L138 _public enumerator_ `All = 0xFF UMETA(Hidden)`

#### enum `EScriptableToolStartupRequirements`  
`enum class EScriptableToolStartupRequirements : uint8`  
_L143-151_
- reflection: `UENUM(BlueprintType)`
- L146 _public enumerator_ `None` — No startup requirements needed. Tool can run any time.
- L148 _public enumerator_ `ToolTarget` — A custom tool builder blueprint class that is configured with tool target requirements to filter selected objects.
- L150 _public enumerator_ `Custom` — A custom tool builder blueprint class is provided to determine if the tool can start. Caution: OnCanBuildTool is run every tick, and may slow down editor performance.

#### struct `FScriptableToolGizmoOptions`  
`struct FScriptableToolGizmoOptions`  
_L158-191_
- reflection: `USTRUCT(BlueprintType)`
- desc: FScriptableToolGizmoOptions is a configuration struct passed to the CreateTRSGizmo function of UScriptableInteractiveTool.
- L163 _public member_ `EScriptableToolGizmoMode GizmoMode = EScriptableToolGizmoMode::Combined;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gizmo)`
- L167 _public member_ `int32 TranslationParts = static_cast<int32>(EScriptableToolGizmoTranslation::All);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gizmo, meta = (DisplayName = "Translation Elements", Bitmask, BitmaskEnum = "/Script/ScriptableToolsFramework.EScriptableToolGizmoTranslation", ValidEnumValues = "TranslateAxisX, TranslateAxisY, TranslateAxisZ, TranslatePlaneXY, TranslatePlaneXZ, TranslatePlaneYZ"))`
- L171 _public member_ `int32 RotationParts = static_cast<int32>(EScriptableToolGizmoRotation::All);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gizmo, meta = (DisplayName = "Rotation Elements", Bitmask, BitmaskEnum = "/Script/ScriptableToolsFramework.EScriptableToolGizmoRotation", ValidEnumValues = "RotateAxisX, RotateAxisY, RotateAxisZ"))`
- L175 _public member_ `int32 ScaleParts = static_cast<int32>(EScriptableToolGizmoScale::All);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gizmo, meta = (DisplayName = "Scale Elements", Bitmask, BitmaskEnum = "/Script/ScriptableToolsFramework.EScriptableToolGizmoScale", ValidEnumValues = "ScaleAxisX, ScaleAxisY, ScaleAxisZ, ScalePlaneXY, ScalePlaneXZ, ScalePlaneYZ"))`
- L178 _public member_ `EScriptableToolGizmoCoordinateSystem CoordSystem = EScriptableToolGizmoCoordinateSystem::Local;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gizmo)`
- L181 _public member_ `bool bSnapTranslation = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gizmo)`
- L184 _public member_ `bool bSnapRotation = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gizmo)`
- L187 _public member_ `bool bRepositionable = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gizmo)`
- L190 _public member_ `bool bAllowNegativeScaling = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gizmo)`

#### class `UScriptableTool_RenderAPI`  
`class UScriptableTool_RenderAPI : public UObject`  
_L201-222_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UObject`
- desc: UScriptableTool_RenderAPI is helper Object that is created internally by a UScriptableInteractiveTool to allow Blueprints to access basic 3D rendering functionality, in the context of a specific Tool. The OnScriptRender event is called with an instance of this type.
- L206 _public prototype_ `UPARAM(DisplayName="Render Object") UScriptableTool_RenderAPI* DrawLine(FVector Start, FVector End, FLinearColor Color, float Thickness = 1.0, float DepthBias = 0.0f, bool bDepthTested = true);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Render")`
- L210 _public prototype_ `UPARAM(DisplayName="Render Object") UScriptableTool_RenderAPI* DrawRectWidthHeightXY(FTransform Transform, double Width, double Height, FLinearColor Color, float LineThickness = 1.0, float DepthBias = 0.0f, bool bDepthTested = true, bool bCentered = true);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Render")`
- L221 _protected member_ `FToolDataVisualizer* ActiveVisualizer = nullptr;`

#### class `UScriptableTool_HUDAPI`  
`class UScriptableTool_HUDAPI : public UObject`  
_L230-255_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UObject`
- desc: UScriptableTool_HUDAPI is helper Object that is created internally by a UScriptableInteractiveTool to allow Blueprints to access basic 2D rendering functionality, in the context of a specific Tool. The OnScriptDrawHUD event is called with an instance of this type.
- L235 _public prototype_ `UPARAM(DisplayName="HUD Object") UScriptableTool_HUDAPI* DrawTextAtLocation(FVector Location, FString String, FLinearColor Color, bool bCentered, float ShiftRowsY);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|DrawHUD", Meta = (Color = "(R=1.0,G=1.0,B=1.0,A=1.0)"))`
- L239 _public prototype_ `UPARAM(DisplayName="HUD Object") UScriptableTool_HUDAPI* DrawTextArrayAtLocation(FVector Location, TArray<FString> Strings, FLinearColor Color, bool bCentered, float ShiftRowsY);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|DrawHUD", Meta = (Color = "(R=1.0,G=1.0,B=1.0,A=1.0)"))`
- L243 _public prototype_ `UPARAM(DisplayName="HUD Object") UScriptableTool_HUDAPI* GetCanvasLocation(FVector Location, FVector2D& CanvasLocation );` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|DrawHUD")`
- L253 _protected member_ `FCanvas* ActiveCanvas = nullptr;`
- L254 _protected member_ `const FSceneView* ActiveSceneView = nullptr;`

#### class `UScriptableInteractiveToolPropertySet`  
`class UScriptableInteractiveToolPropertySet : public UInteractiveToolPropertySet`  
_L275-300_
- reflection: `UCLASS(MinimalAPI, Transient, Blueprintable)`
- inherits: `UInteractiveToolPropertySet`
- desc: UScriptableInteractiveToolPropertySet is a Blueprintable extension of UInteractiveToolPropertySet. This is a helper type meant to be used with UScriptableInteractiveTool. The intention is that the "Settings" of a particular Tool are stored in UScriptableInteractiveToolPropertySet ("Property Set") instances. The function UScriptableInteractiveTool::AddPropertySetOfType can be used to create and attach a new Property Set. Then these settings can be automatically exposed by, for example, the Editor Mode UI, similar to (eg) Modeling Mode in the UE Editor. In addition, UScriptableInteractiveTool has a set of functions like WatchFloatProperty, WatchBoolProperty, etc, that can be used to detect and respond to changes in the Property Set. This works with both changes caused by Editor UI (eg a Details Panel) as well as done directly in Blueprints or even C++ code. Note, however, that this Property Set mechanism completely optional, a Tool builder is free to use any method whatsoever to store/modify Tool settings.
- L281 _private prototype_ `UScriptableInteractiveTool* GetOwningTool( EToolsFrameworkOutcomePins& Outcome);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool", Meta = (ExpandEnumAsExecs = "Outcome"))` — Access the Tool that owns this PropertySet
- L286 _private prototype_ `UPARAM(DisplayName = "Property Set") UScriptableInteractiveToolPropertySet* SetPropertyAsReadOnly(FString PropertyName, bool` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool")` — Toggle whether or not the named property should be displayed as a readonly field in the tool's details view.
- L290 _private prototype_ `UPARAM(DisplayName = "Property Set") UScriptableInteractiveToolPropertySet* SetPropertyAsHidden(FString PropertyName, bo` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool")` — Toggle whether or not the named property should be displayed at all as a field in the tool's details view.
- L293 _private prototype_ `UPARAM(DisplayName = "Property Set") UScriptableInteractiveToolPropertySet* MakeTran` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool")`
- L295 _private prototype_ `virtual UWorld* GetWorld() const override;` — must implement this for WorldContextObject dependent BP functions to show.
- L298 _protected member_ `TWeakObjectPtr<UScriptableInteractiveTool> ParentTool;`

#### class `UScriptableInteractiveTool`  
`class UScriptableInteractiveTool : public UInteractiveTool`  
_L320-964_
- reflection: `UCLASS(MinimalAPI, Transient, Blueprintable)`
- inherits: `UInteractiveTool`
- desc: UScriptableInteractiveTool is an extension of UInteractiveTool that allows the Tool functionality to be defined via Blueprints.
- L326 _public member_ `FText ToolName;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Scriptable Tool Settings")` — Name of this Tool, will be used in (eg) Toolbars
- L330 _public member_ `FText ToolLongName;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Scriptable Tool Settings", meta=(DisplayName="Long Name"))` — Long Name of this Tool, will be used in (eg) longer labels like the Accept/Cancel toolbar
- L334 _public member_ `FText ToolCategory;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Scriptable Tool Settings", meta=(DisplayName="Category"))` — Category of this Tool, will be used in (eg) Tool Palette Section headers
- L338 _public member_ `FText ToolTooltip;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Scriptable Tool Settings", meta=(DisplayName="Tooltip"))` — Tooltip used for this Tool in (eg) icons/etc
- L352 _public member_ `FString CustomIconPath;` — `UE_DEPRECATED(5.7, "Use ToolIconTexture instead.")` — `UPROPERTY(meta = (DisplayName = "Custom Icon Path", DeprecatedProperty, DeprecationMessage="Use ToolIconTexture instead."))` — Relative Path to a custom Icon Image for this Tool. The Image file format must be png or svg. The Image file must reside in the same Content folder hierarchy as contains the Tool Class (ie Blueprint asset), i.e. either the Project Content folder or a Plugin Content folder. So for example if the Tool BP is in a plugin named MyCustomTools, the icon must be in MyProject/Plugins/MyCustomTools/Content/<SubFolders>/MyToolIcon.png, and the relative path to use here would be <SubFolders>/MyToolIcon.png
- L355 _public member_ `TObjectPtr<UTexture2D> ToolIconTexture;` — `UPROPERTY(EditDefaultsOnly, Category = "Scriptable Tool Settings", meta = (DisplayName = "Tool Icon"))`
- L359 _public member_ `bool bShowToolInEditor = true;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Scriptable Tool Settings", meta=(DisplayName="Visible in Editor"))` — A generic flag to indicate whether this Tool should be shown in the UE Editor. This may be interpreted in different ways
- L363 _public member_ `EScriptableToolShutdownType ToolShutdownType = EScriptableToolShutdownType::Complete;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Scriptable Tool Settings", meta=(DisplayName="Shutdown Type"))` — Specifies how the user exits this Tool, either Accept/Cancel-style or Complete-style
- L366 _public member_ `EScriptableToolStartupRequirements ToolStartupRequirements = EScriptableToolStartupRequirements::None;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Scriptable Tool Settings", meta = (DisplayName = "Tool Startup Requirements"))`
- L372 _public member_ `TSubclassOf<UCustomScriptableToolBuilder> CustomToolBuilderClass;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Scriptable Tool Settings", meta = (DisplayName = "Tool Builder Class", EditCondition = "ToolStartupRequirements==EScriptableToolStartupRequirements::Custom", EditConditionHides, MustImplement = "/Script/ScriptableToolsFramework.CustomScriptableToolBuilderBaseInterface"))`
- L378 _public member_ `TSubclassOf<UToolTargetScriptableToolBuilder> ToolTargetToolBuilderClass;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Scriptable Tool Settings", meta = (DisplayName = "Tool Builder Class", EditCondition = "ToolStartupRequirements==EScriptableToolStartupRequirements::ToolTarget", EditConditionHides, MustImplement="/Script/ScriptableToolsFramework.CustomScriptableToolBuilderBaseInterface"))`
- L387 _public prototype_ `void OnScriptSetup();` — `UFUNCTION(BlueprintImplementableEvent, Category = "ScriptableTool|Events")` — Implement OnScriptSetup to do initial setup/configuration of the Tool, such as adding Property Sets, creating Gizmos, etc
- L389 _public prototype_ `virtual void Setup() override;`
- L397 _public prototype_ `void OnScriptTick(float DeltaTime);` — `UFUNCTION(BlueprintImplementableEvent, Category = "ScriptableTool|Events")` — OnScriptTick is called every Editor Tick, ie basically every frame. Implement per-frame processing here.
- L399 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L407 _public prototype_ `bool OnScriptCanAccept() const;` — `UFUNCTION(BlueprintNativeEvent, Category = "ScriptableTool|Events")` — CanAccept function. Implement this function for AcceptCancel Tools, and return true when it is valid for the Tool Accept button to be active. Defaults to always true.
- L409 _public prototype_ `bool OnScriptCanAccept_Implementation() const;`
- L411 _public prototype_ `virtual bool HasAccept() const override;`
- L412 _public prototype_ `virtual bool HasCancel() const override;`
- L413 _public prototype_ `virtual bool CanAccept() const override;`
- L427 _public prototype_ `void OnScriptShutdown(EToolShutdownType ShutdownType);` — `UFUNCTION(BlueprintImplementableEvent, Category = "ScriptableTool|Events")` — OnScriptShutdown is called when the Tool is shutting down. The ShutdownType defines what the Tool should do. For Complete-style Tools, there is no difference, but for Accept/Cancel-style Tools, on Accept the Tool should "commit" whatever it is previewing/etc, and on Cancel it should roll back / do-nothing. Which of these occurs is based on the ToolShutdownType property. Tool Shutdown cannot be interrupted/aborted
- L429 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L437 _public prototype_ `void RequestToolShutdown( bool bAccept, bool bShowUserPopupMessage, FText UserMessage);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool", Meta = (Identifier="Settings"))` — Request that the active Tool be shut down. The Tool can post this to shut itself down (eg in a Tool where the interaction paradigm is "click to do something and exit"). @param bAccept if this is an Accept/Cancel Tool, Accept it, otherwise Cancel. Ignored for Complete-type Tools.
- L445 _protected prototype_ `virtual void PostInitProperties() override;`
- L449 _protected prototype_ `virtual UBaseScriptableToolBuilder* GetNewCustomToolBuilderInstance(UObject* Outer);` — return instance of custom tool builder. Should only be called on CDO.
- L455 _protected member_ `TWeakObjectPtr<UWorld> TargetWorld;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional, SkipSerialization)`
- L458 _public prototype_ `virtual UWorld* GetWorld() const override;` — must implement this for WorldContextObject dependent BP functions to show.
- L460 _public prototype_ `virtual void SetTargetWorld(UWorld* World);` — needs to be accessible to ToolBuilder
- L466 _public prototype_ `UWorld* GetToolWorld();` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool")` — Access the World this Tool is currently operating on.
- L473 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L481 _public prototype_ `void OnScriptRender( UPARAM(DisplayName="Render Object") UScriptableTool_RenderAPI` — `UFUNCTION(BlueprintImplementableEvent, Category = "ScriptableTool|Events")` — OnScriptRender is called every frame. Use the RenderAPI object to draw various simple geometric elements like lines and points. This drawing is not very efficient but is useful for basic Tool visualization/feedback.
- L483 _public prototype_ `virtual void DrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI) override;`
- L491 _public prototype_ `void OnScriptDrawHUD( UPARAM(DisplayName="HUD Object") UScriptableTool_HUDAPI* Dr` — `UFUNCTION(BlueprintImplementableEvent, Category = "ScriptableTool|Events")` — OnScriptDrawHUD is called every frame. Use the DrawHUDAPI to draw various simple HUD elements like text. This drawing is not very efficient but is useful for basic Tool visualization/feedback.
- L496 _protected member_ `TObjectPtr<UScriptableTool_RenderAPI> RenderHelper;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional, SkipSerialization)`
- L499 _protected member_ `TObjectPtr<UScriptableTool_HUDAPI> DrawHUDHelper;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional, SkipSerialization)`
- L513 _public prototype_ `UPARAM(DisplayName="New Property Set") UScriptableInteractiveToolPropertySet* AddPropertySetOfType( TSubclassOf<UScriptableInteractiveToolPropertySet> PropertySetType, FString Identifier, EToolsFrameworkOutcomePins& Outcome);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|PropertySets", Meta = (ExpandEnumAsExecs = "Outcome", Identifier="Settings"))` — Create a new Tool Property Set (ie BP subclass of UScriptableInteractiveToolPropertySet) with the given string Identifier and attach it to the Tool. The public variables of this Property Set object will appear in (eg) Mode Details Panels, etc. Multiple Property Sets of the same Type can be attached to a Tool, but each must have a unique Identifier.
- L524 _public prototype_ `void RemovePropertySetByName( FString Identifier, EToolsFrameworkOutcomePins& Outcome);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|PropertySets", Meta = (ExpandEnumAsExecs = "Outcome", Identifier="Settings"))` — Remove a Property Set from the current Tool, found via it's unique Identifier. Unless the Property Set absolutely needs to stop existing, it is likely preferable to use SetPropertySetVisibleByName() to simply hide it.
- L532 _public prototype_ `void SetPropertySetVisibleByName( FString Identifier, bool bVisible);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|PropertySets", Meta = (Identifier="Settings"))` — Set the visibility of a Property Set that is paired with the given unique Identifier.
- L543 _public prototype_ `void ForcePropertySetUpdateByName( FString Identifier);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|PropertySets", Meta = (Identifier="Settings"))` — Force the Property Set associated with the given Identifier to be updated. This may be necessary if you change the Property Set values directly via Blueprints, and want to see your changes reflected in (eg) a Details Panel showing the Tool Property values. Currently these changes cannot be detected automatically, necessitating this function.
- L552 _public prototype_ `UPARAM(DisplayName="Property Set") UScriptableInteractiveToolPropertySet* RestorePropertySetSettings( UScriptableInteractiveToolPropertySet* PropertySet, FString SaveKey);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|PropertySets", Meta = (Identifier="Settings"))` — Restore the values of the specified PropertySet, optionally with a specific SaveKey string. This will have no effect unless SavePropertySetSettings() has been called on a compatible Property Set in the same Engine session (ie in a previous invocation of the Tool, or another Tool that uses the same Property Set)
- L561 _public prototype_ `UPARAM(DisplayName="Property Set") UScriptableInteractiveToolPropertySet* SavePropertySetSettings( UScriptableInteractiveToolPropertySet* PropertySet, FString SaveKey);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|PropertySets", Meta = (Identifier="Settings"))` — Save the values of the specified PropertySet, optionally with a specific SaveKey string. These saved values can be restored in future Tool invocations based on the SaveKey.
- L578 _public prototype_ `UPARAM(DisplayName="Property Set") UScriptableInteractiveToolPropertySet* WatchFloatProperty( UScriptableInteractiveToolPropertySet* PropertySet, FString PropertyName, const FToolFloatPropertyModifiedDelegate& OnModified );` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|PropertySets")` — Watch a Float-valued Property for changes (double precision) @param PropertySet the Property Set which contains the desired Property to watch. @param PropertyName the string name of the Property in the given Property Set @param OnModified this delegate will be called if the Property value changes.
- L590 _public prototype_ `UPARAM(DisplayName="Property Set") UScriptableInteractiveToolPropertySet* WatchIntProperty( UScriptableInteractiveToolPropertySet* PropertySet, FString PropertyName, const FToolIntPropertyModifiedDelegate& OnModified );` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|PropertySets")` — Watch an Integer-valued Property for changes @param PropertySet the Property Set which contains the desired Property to watch. @param PropertyName the string name of the Property in the given Property Set @param OnModified this delegate will be called if the Property value changes.
- L602 _public prototype_ `UPARAM(DisplayName="Property Set") UScriptableInteractiveToolPropertySet* WatchBoolProperty( UScriptableInteractiveToolPropertySet* PropertySet, FString PropertyName, const FToolBoolPropertyModifiedDelegate& OnModified );` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|PropertySets")` — Watch a Bool-valued Property for changes @param PropertySet the Property Set which contains the desired Property to watch. @param PropertyName the string name of the Property in the given Property Set @param OnModified this delegate will be called if the Property value changes.
- L615 _public prototype_ `UPARAM(DisplayName="Property Set") UScriptableInteractiveToolPropertySet* WatchEnumProperty( UScriptableInteractiveToolPropertySet* PropertySet, FString PropertyName, const FToolEnumPropertyModifiedDelegate& OnModified );` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|PropertySets")` — Watch an Enum-valued Property for changes. Note that in this case the OnModified delegate will be called with a uint8 integer, which can be cast back to the original Enum type. @param PropertySet the Property Set which contains the desired Property to watch. @param PropertyName the string name of the Property in the given Property Set @param OnModified this delegate will be called if the Property value changes.
- L627 _public prototype_ `UPARAM(DisplayName="Property Set") UScriptableInteractiveToolPropertySet* WatchStringProperty( UScriptableInteractiveToolPropertySet* PropertySet, FString PropertyName, const FToolStringPropertyModifiedDelegate& OnModified );` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|PropertySets")` — Watch a String-valued Property for changes @param PropertySet the Property Set which contains the desired Property to watch. @param PropertyName the string name of the Property in the given Property Set @param OnModified this delegate will be called if the Property value changes.
- L639 _public prototype_ `UPARAM(DisplayName="Property Set") UScriptableInteractiveToolPropertySet* WatchNameProperty( UScriptableInteractiveToolPropertySet* PropertySet, FString PropertyName, const FToolFNamePropertyModifiedDelegate& OnModified );` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|PropertySets")` — Watch an (F)Name-valued Property for changes @param PropertySet the Property Set which contains the desired Property to watch. @param PropertyName the string name of the Property in the given Property Set @param OnModified this delegate will be called if the Property value changes.
- L651 _public prototype_ `UPARAM(DisplayName="Property Set") UScriptableInteractiveToolPropertySet* WatchObjectProperty( UScriptableInteractiveToolPropertySet* PropertySet, FString PropertyName, const FToolObjectPropertyModifiedDelegate& OnModified );` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|PropertySets")` — Watch an Object-valued Property for changes (ie UObject, UClass, etc) @param PropertySet the Property Set which contains the desired Property to watch. @param PropertyName the string name of the Property in the given Property Set @param OnModified this delegate will be called if the Property value changes.
- L669 _public prototype_ `UPARAM(DisplayName="Property Set") UScriptableInteractiveToolPropertySet* WatchProperty( UScriptableInteractiveToolPropertySet* PropertySet, FString PropertyName, const FToolPropertyModifiedDelegate& OnModified );` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|PropertySets")` — Watch any Property in a PropertySet for changes. This function handles most basic properties, as well as Struct and Array properties, at some cost. The OnModified delegate cannot be passed the new property value, it must be fetched from the PropertySet. Note also that in the case of Structs and Arrays, changes are currently detected by hashes, and there is always a small chance of hash collision. @param PropertySet the Property Set which contains the desired Property to watch. @param PropertyName the string name of the Property in the given Property Set @param OnModified this delegate will be called if the Property value changes.
- L675 _protected member_ `TMap<FString, TWeakObjectPtr<UScriptableInteractiveToolPropertySet>> NamedPropertySets;`
- L677 _protected member_ `TArray<FToolFloatPropertyModifiedDelegate> WatchFloatPropertyDelegates;`
- L678 _protected member_ `TArray<FToolIntPropertyModifiedDelegate> WatchIntPropertyDelegates;`
- L679 _protected member_ `TArray<FToolBoolPropertyModifiedDelegate> WatchBoolPropertyDelegates;`
- L680 _protected member_ `TArray<FToolEnumPropertyModifiedDelegate> WatchEnumPropertyDelegates;`
- L681 _protected member_ `TArray<FToolStringPropertyModifiedDelegate> WatchStringPropertyDelegates;`
- L682 _protected member_ `TArray<FToolFNamePropertyModifiedDelegate> WatchFNamePropertyDelegates;`
- L683 _protected member_ `TArray<FToolObjectPropertyModifiedDelegate> WatchObjectPropertyDelegates;`
- L708 _protected member_ `TArray<FAnyPropertyWatchInfo> WatchAnyPropertyInfo;`
- L722 _public prototype_ `void CreateTRSGizmo( FString Identifier, FTransform InitialTransform, FScriptableToolGizmoOptions GizmoOptions, EToolsFrameworkOutcomePins& Outcome);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Gizmos", Meta = (ExpandEnumAsExecs = "Outcome", Identifier="Gizmo1"))` — Create a Translate/Rotate/Scale Gizmo with the given Options at the specified InitialTransform. The Gizmo must be given a unique Identifier, which will be used to access it in other functions. The Gizmo can be explicitly destroyed with DestroyTRSGizmo(), or it will be automatically destroyed when the Tool exits
- L732 _public prototype_ `void DestroyTRSGizmo( FString Identifier, EToolsFrameworkOutcomePins& Outcome);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Gizmos", Meta = (ExpandEnumAsExecs = "Outcome", Identifier="Gizmo1"))` — Destroy a created Gizmo by name Identifier
- L740 _public prototype_ `void SetGizmoVisible( FString Identifier, bool bVisible);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Gizmos", Meta = (Identifier="Gizmo1"))` — Set an existing Gizmo visible/hidden based on its name Identifier
- L749 _public prototype_ `void SetGizmoTransform( FString Identifier, FTransform NewTransform, bool bUndoable );` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Gizmos", Meta = (Identifier="Gizmo1"))` — Update the Transform on the Gizmo specified by the name Identifier @param bUndoable if true, this transform change will be transacted into the undo/redo history, ie undoable
- L758 _public prototype_ `UPARAM(DisplayName="Transform") FTransform GetGizmoTransform( FString Identifier);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Gizmos", Meta = (Identifier="Gizmo1"))` — Get the current Transform on the Gizmo specified by the name Identifier
- L766 _public prototype_ `void OnGizmoTransformChanged(const FString& GizmoIdentifier, FTransform NewTransform);` — `UFUNCTION(BlueprintImplementableEvent, Category = "ScriptableTool|Events")` — The OnGizmoTransformChanged event fires whenever the transform on any Gizmo created by CreateTRSGizmo() is modified. The GizmoIdentifier can be used to disambiguate multiple active Gizmos.
- L774 _public prototype_ `void OnGizmoTransformStateChange(const FString& GizmoIdentifier, FTransform CurrentTransform, EScriptableToolGizmoStateChangeType ChangeType);` — `UFUNCTION(BlueprintImplementableEvent, Category = "ScriptableTool|Events")` — The OnGizmoTransformStateChange event fires whenever the user start/ends a Gizmo transform, or when an Undo/Redo event occurs. Note that when Undo/Redo occurs, OnGizmoTransformChanged will also fire. The GizmoIdentifier can be used to disambiguate multiple active Gizmos.
- L780 _protected member_ `TMap<FString, TObjectPtr<UCombinedTransformGizmo>> Gizmos;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional, SkipSerialization)` — trying to avoid making a UStruct for this internal stuff
- L782 _protected prototype_ `virtual void OnGizmoTransformChanged_Handler(FString GizmoIdentifier, FTransform NewTransform);`
- L783 _protected prototype_ `virtual void OnGizmoTransformStateChange_Handler(FString GizmoIdentifier, FTransform CurrentTransform, EScriptableToolGizmoStateChangeType ChangeType);`
- L796 _public prototype_ `void AddLogMessage( FText Message, bool bHighlighted = false );` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Messaging")` — Append a Message to the UE Editor Log. @param bHighlighted if true, the message is emitted as a Warning, otherwise as a Log (normal)
- L803 _public prototype_ `void DisplayUserHelpMessage( FText Message );` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Messaging")` — Display a short Help message for the user, ie to guide them in Tool usage. In the UE5 Editor this message appears in the bottom bar of the window.
- L809 _public prototype_ `void DisplayUserWarningMessage( FText Message );` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Messaging")` — Display a Warning message to the user, ie to indicate a problem/issue occurred.
- L815 _public prototype_ `void ClearUserMessages( bool bHelpMessage = true, bool bWarningMessage = true );` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Messaging")` — Clear any active message shown via DisplayUserHelpMessage and/or DisplayUserWarningMessage
- L828 _public prototype_ `void SetTargets(TArray<TObjectPtr<UToolTarget>> TargetsIn);`
- L831 _public prototype_ `UPARAM(DisplayName = "Targets") TArray<UToolTarget*> GetToolTargets()` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|ToolTargets")`
- L836 _protected member_ `TArray<TObjectPtr<UToolTarget>> Targets;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional, SkipSerialization)`
- L848 _public prototype_ `AActor* GetDrawableGeometryActor() const;` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Drawing")` — Return the actor that owns any line, point and triangle sets added to this tool. @return A reference to the actor object that owns drawable geometry sets.
- L855 _public prototype_ `UScriptableToolLineSet* GetDefaultLineSet() const;` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Drawing")` — Retrieve the default line set object for the tool, used for drawing persistent line objects in the scene. @return A reference to the tool's default line set object
- L863 _public prototype_ `UScriptableToolLineSet* AddLineSet();` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Drawing")` — Create and return a new, independent line set, used for drawing persistent line objects in the scene. Users must save a reference to the created object for future access. @return A reference to a new line set object
- L870 _public prototype_ `UScriptableToolPointSet* GetDefaultPointSet() const;` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Drawing")` — Retrieve the default point set object for the tool, used for drawing persistent point objects in the scene. @return A reference to the tool's default point set object
- L878 _public prototype_ `UScriptableToolPointSet* AddPointSet();` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Drawing")` — Create and return a new, independent point set, used for drawing persistent point objects in the scene. Users must save a reference to the created object for future access. @return A reference to a new point set object
- L885 _public prototype_ `UScriptableToolTriangleSet* GetDefaultTriangleSet() const;` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Drawing")` — Retrieve the default triangle set object for the tool, used for drawing persistent triangle and quad objects in the scene. @return A reference to the tool's default triangle set object
- L893 _public prototype_ `UScriptableToolTriangleSet* AddTriangleSet();` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Drawing")` — Create and return a new, independent triangle set, used for drawing persistent triangle and quad objects in the scene. Users must save a reference to the created object for future access. @return A reference to a new triangle set object
- L897 _protected member_ `TObjectPtr<UScriptableToolLineSet> DefaultLineSet;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional, SkipSerialization)`
- L900 _protected member_ `TArray<TObjectPtr<UScriptableToolLineSet> > LineSets;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional, SkipSerialization)`
- L903 _protected member_ `TObjectPtr<UScriptableToolPointSet> DefaultPointSet;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional, SkipSerialization)`
- L906 _protected member_ `TArray<TObjectPtr<UScriptableToolPointSet> > PointSets;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional, SkipSerialization)`
- L909 _protected member_ `TObjectPtr<UScriptableToolTriangleSet> DefaultTriangleSet;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional, SkipSerialization)`
- L912 _protected member_ `TArray<TObjectPtr<UScriptableToolTriangleSet> > TriangleSets;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional, SkipSerialization)`
- L915 _protected member_ `TObjectPtr<UPreviewGeometry> ToolDrawableGeometry = nullptr;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional, SkipSerialization)`
- L928 _public prototype_ `void SetToolPanelToolHeaderWidget(UUserWidget* Widget);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Widgets")` — Set a UUserWidget to display at the head of the Scriptable Tool panel details view. Will only take effect when set during OnScriptSetup. @param Widget The UUserWidget to set.
- L935 _public prototype_ `TSharedRef<SWidget> GetToolPanelToolHeaderWidget() const;` — Retrieve an SWidget reference from the Scriptable Tool panel details view header widget. @return A reference to an SWidget
- L940 _private member_ `TObjectPtr<UUserWidget> ToolPanelToolHeaderWidget;` — `UPROPERTY(Transient)`
- L947 _public prototype_ `void SetOverlayWidget(UUserWidget* Widget, bool bMakeDraggable=true);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Widgets")`
- L950 _public prototype_ `void ClearOverlayWidget();` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Widgets")`
- L956 _public member_ `FScriptableToolGroupSet GroupTags;` — `UPROPERTY(EditAnywhere, Transient, Category = "Scriptable Tool Settings")`
- L963 _public prototype_ `void SetFocusInViewport();` — `UFUNCTION(BlueprintCallable, Category = "ScriptableTool|Viewport")`

#### enum `UScriptableInteractiveTool::EAnyPropertyWatchTypes`  
`enum class EAnyPropertyWatchTypes`  
_L686-701_
- L688 _public enumerator_ `Integer = 0`
- L689 _public enumerator_ `Bool = 1`
- L690 _public enumerator_ `Double = 2`
- L691 _public enumerator_ `Enum = 3`
- L692 _public enumerator_ `String = 4`
- L693 _public enumerator_ `FName = 5`
- L694 _public enumerator_ `Object = 6`
- L696 _public enumerator_ `Struct = 20`
- L697 _public enumerator_ `Array = 30`
- L700 _public enumerator_ `Unknown = 100`

#### struct `UScriptableInteractiveTool::FAnyPropertyWatchInfo`  
`struct FAnyPropertyWatchInfo`  
_L702-707_
- L704 _public member_ `EAnyPropertyWatchTypes KnownType = EAnyPropertyWatchTypes::Unknown;`
- L705 _public member_ `TArray<uint8> TempBuffer;`
- L706 _public member_ `FToolPropertyModifiedDelegate Delegate;`

#### class `UScriptableToolsUtilityLibrary`  
`class UScriptableToolsUtilityLibrary : public UBlueprintFunctionLibrary`  
_L968-985_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "ScriptableTools_Util"))`
- inherits: `UBlueprintFunctionLibrary`
- L974 _public prototype_ `static UPARAM(DisplayName = "RayHit Result") FInputRayHit MakeInputRayHit_Miss();` — `UFUNCTION(BlueprintPure, Category="ScriptableTool|Util")`
- L978 _public prototype_ `static UPARAM(DisplayName = "RayHit Result") FInputRayHit MakeInputRayHit_MaxDepth();` — `UFUNCTION(BlueprintPure, Category="ScriptableTool|Util")`
- L982 _public prototype_ `static UPARAM(DisplayName = "RayHit Result") FInputRayHit MakeInputRayHit(double HitDepth, UObject* OptionalHitObject);` — `UFUNCTION(BlueprintPure, Category="ScriptableTool|Util")`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API SCRIPTABLETOOLSFRAMEWORK_API`
- L106 _prototype_ `ENUM_CLASS_FLAGS(EScriptableToolGizmoTranslation);`
- L122 _prototype_ `ENUM_CLASS_FLAGS(EScriptableToolGizmoRotation);`
- L140 _prototype_ `ENUM_CLASS_FLAGS(EScriptableToolGizmoScale);`
- L305 _delegate_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FToolPropertyModifiedDelegate, UScriptableInteractiveToolPropertySet*, PropertySet, FString, PropertyName);` — these are delegates for the various property-watchers below
- L305 _prototype_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FToolPropertyModifiedDelegate, UScriptableInteractiveToolPropertySet*, PropertySet, FString, PropertyName);` — these are delegates for the various property-watchers below
- L306 _delegate_ `DECLARE_DYNAMIC_DELEGATE_ThreeParams(FToolFloatPropertyModifiedDelegate, UScriptableInteractiveToolPropertySet*, PropertySet, FString, PropertyName, double, NewValue);`
- L306 _prototype_ `DECLARE_DYNAMIC_DELEGATE_ThreeParams(FToolFloatPropertyModifiedDelegate, UScriptableInteractiveToolPropertySet*, PropertySet, FString, PropertyName, double, NewValue);`
- L307 _delegate_ `DECLARE_DYNAMIC_DELEGATE_ThreeParams(FToolIntPropertyModifiedDelegate, UScriptableInteractiveToolPropertySet*, PropertySet, FString, PropertyName, int, NewValue);`
- L307 _prototype_ `DECLARE_DYNAMIC_DELEGATE_ThreeParams(FToolIntPropertyModifiedDelegate, UScriptableInteractiveToolPropertySet*, PropertySet, FString, PropertyName, int, NewValue);`
- L308 _delegate_ `DECLARE_DYNAMIC_DELEGATE_ThreeParams(FToolBoolPropertyModifiedDelegate, UScriptableInteractiveToolPropertySet*, PropertySet, FString, PropertyName, bool, bNewValue);`
- L308 _prototype_ `DECLARE_DYNAMIC_DELEGATE_ThreeParams(FToolBoolPropertyModifiedDelegate, UScriptableInteractiveToolPropertySet*, PropertySet, FString, PropertyName, bool, bNewValue);`
- L309 _delegate_ `DECLARE_DYNAMIC_DELEGATE_ThreeParams(FToolEnumPropertyModifiedDelegate, UScriptableInteractiveToolPropertySet*, PropertySet, FString, PropertyName, uint8, NewValue);`
- L309 _prototype_ `DECLARE_DYNAMIC_DELEGATE_ThreeParams(FToolEnumPropertyModifiedDelegate, UScriptableInteractiveToolPropertySet*, PropertySet, FString, PropertyName, uint8, NewValue);`
- L310 _delegate_ `DECLARE_DYNAMIC_DELEGATE_ThreeParams(FToolStringPropertyModifiedDelegate, UScriptableInteractiveToolPropertySet*, PropertySet, FString, PropertyName, FString, NewValue);`
- L310 _prototype_ `DECLARE_DYNAMIC_DELEGATE_ThreeParams(FToolStringPropertyModifiedDelegate, UScriptableInteractiveToolPropertySet*, PropertySet, FString, PropertyName, FString, NewValue);`
- L311 _delegate_ `DECLARE_DYNAMIC_DELEGATE_ThreeParams(FToolFNamePropertyModifiedDelegate, UScriptableInteractiveToolPropertySet*, PropertySet, FString, PropertyName, FName, NewValue);`
- L311 _prototype_ `DECLARE_DYNAMIC_DELEGATE_ThreeParams(FToolFNamePropertyModifiedDelegate, UScriptableInteractiveToolPropertySet*, PropertySet, FString, PropertyName, FName, NewValue);`
- L312 _delegate_ `DECLARE_DYNAMIC_DELEGATE_ThreeParams(FToolObjectPropertyModifiedDelegate, UScriptableInteractiveToolPropertySet*, PropertySet, FString, PropertyName, UObject*, NewValue);`
- L312 _prototype_ `DECLARE_DYNAMIC_DELEGATE_ThreeParams(FToolObjectPropertyModifiedDelegate, UScriptableInteractiveToolPropertySet*, PropertySet, FString, PropertyName, UObject*, NewValue);`

### `Plugins/Runtime/ScriptableToolsFramework/Source/ScriptableToolsFramework/Public/ScriptableToolBuilder.h` (Public)


#### class `UBaseScriptableToolBuilder`  
`class UBaseScriptableToolBuilder : public UInteractiveToolBuilder`  
_L23-32_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolBuilder`
- desc: UBaseScriptableToolBuilder is a trivial base UInteractiveToolBuilder for any UScriptableInteractiveTool subclass. CanBuildTool will return true as long as the ToolClass is a valid UClass.
- L28 _public member_ `TWeakObjectPtr<UClass> ToolClass;`
- L30 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L31 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`

#### class `UCustomScriptableToolBuilderBaseInterface`  
`class UCustomScriptableToolBuilderBaseInterface : public UInterface`  
_L35-38_
- reflection: `UINTERFACE(MinimalAPI, BlueprintType)`
- inherits: `UInterface`

#### class `ICustomScriptableToolBuilderBaseInterface`  
`class ICustomScriptableToolBuilderBaseInterface`  
_L40-48_
- L46 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const = 0;`
- L47 _public prototype_ `virtual void SetupTool(const FToolBuilderState& SceneState, UInteractiveTool* Tool) const = 0;`

#### class `UCustomScriptableToolBuilderComponentBase`  
`class UCustomScriptableToolBuilderComponentBase : public UObject`  
_L51-57_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`

#### class `UCustomScriptableToolBuilderContainer`  
`class UCustomScriptableToolBuilderContainer : public UBaseScriptableToolBuilder`  
_L61-77_
- reflection: `UCLASS(MinimalAPI, Transient, Blueprintable, Hidden)`
- inherits: `UBaseScriptableToolBuilder`
- L68 _public prototype_ `void Initialize(TObjectPtr<UCustomScriptableToolBuilderComponentBase> BuilderInstanceIn);`
- L70 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L71 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`
- L76 _private member_ `TObjectPtr<UCustomScriptableToolBuilderComponentBase> BuilderInstance;` — `UPROPERTY()`

#### class `UCustomScriptableToolBuilder`  
`class UCustomScriptableToolBuilder : public UCustomScriptableToolBuilderComponentBase, public ICustomScriptableToolBuilderBaseInterface`  
_L86-104_
- reflection: `UCLASS(MinimalAPI, Transient, Blueprintable, Abstract)`
- inherits: `UCustomScriptableToolBuilderComponentBase,ICustomScriptableToolBuilderBaseInterface`
- L93 _public prototype_ `bool OnCanBuildTool(const TArray<AActor*>& SelectedActors, const TArray<UActorComponent*>& SelectedComponents) const;` — `UFUNCTION(BlueprintNativeEvent, Category = "ScriptableToolBuilder|Events")`
- L95 _public prototype_ `bool OnCanBuildTool_Implementation(const TArray<AActor*>& SelectedActors, const TArray<UActorComponent*>& SelectedComponents) const;`
- L98 _public prototype_ `void OnSetupTool(UScriptableInteractiveTool* Tool, const TArray<AActor*>& SelectedActors, const TArray<UActorComponent*>& SelectedComponents) const;` — `UFUNCTION(BlueprintNativeEvent, Category = "ScriptableToolBuilder|Events")`
- L100 _public prototype_ `void OnSetupTool_Implementation(UScriptableInteractiveTool* Tool, const TArray<AActor*>& SelectedActors, const TArray<UActorComponent*>& SelectedComponents) const;`
- L102 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L103 _public prototype_ `virtual void SetupTool(const FToolBuilderState& SceneState, UInteractiveTool* Tool) const override;`

#### class `UScriptableToolTargetRequirements`  
`class UScriptableToolTargetRequirements : public UObject`  
_L114-135_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UObject`
- L120 _public prototype_ `static UPARAM(DisplayName = "New Target Requirements") UScriptableToolTargetRequirements* BuildToolTargetRequirements(TArray<UClass*> RequirementInterfaces);` — `UFUNCTION(BlueprintCallable, Category = "ScriptableToolBuilder|ToolTargets")`
- L123 _public function_ `const FToolTargetTypeRequirements& GetRequirements() const`
- L126 _public member_ `int MinMatchingTargets = 0;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Requirements")`
- L129 _public member_ `int MaxMatchingTargets = 1;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Requirements")`
- L133 _private member_ `FToolTargetTypeRequirements Requirements;`

#### class `UToolTargetScriptableToolBuilder`  
`class UToolTargetScriptableToolBuilder: public UCustomScriptableToolBuilderComponentBase, public ICustomScriptableToolBuilderBaseInterface`  
_L138-164_
- reflection: `UCLASS(MinimalAPI, Transient, Blueprintable, Abstract)`
- inherits: `UCustomScriptableToolBuilderComponentBase,ICustomScriptableToolBuilderBaseInterface`
- L144 _public prototype_ `void Initialize();`
- L147 _public prototype_ `UScriptableToolTargetRequirements* GetToolTargetRequirements() const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Tool Targets")`
- L149 _public prototype_ `virtual UScriptableToolTargetRequirements* GetToolTargetRequirements_Implementation() const;`
- L152 _public prototype_ `void OnSetupTool(UScriptableInteractiveTool* Tool) const;` — `UFUNCTION(BlueprintNativeEvent, Category = "ScriptableToolBuilder|Events")`
- L154 _public prototype_ `void OnSetupTool_Implementation(UScriptableInteractiveTool* Tool) const;`
- L156 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L157 _public prototype_ `virtual void SetupTool(const FToolBuilderState& SceneState, UInteractiveTool* Tool) const override;`
- L162 _private member_ `TObjectPtr<UScriptableToolTargetRequirements> Requirements;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SCRIPTABLETOOLSFRAMEWORK_API`
- L11 _namespace_ `namespace ScriptableToolBuilderHelpers`

### `Plugins/Runtime/ScriptableToolsFramework/Source/ScriptableToolsFramework/Public/ScriptableToolsFrameworkModule.h` (Public)


#### class `FScriptableToolsFrameworkModule`  
`class FScriptableToolsFrameworkModule : public IModuleInterface`  
_L8-15_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Runtime/ScriptableToolsFramework/Source/ScriptableToolsFramework/Public/Tags/ScriptableToolGroupSet.h` (Public)


#### struct `FScriptableToolGroupSet`  
`struct FScriptableToolGroupSet`  
_L14-52_
- reflection: `USTRUCT()`
- L21 _public typedef_ `typedef TSet<TSubclassOf<UScriptableToolGroupTag>> FGroupSet;` — Note: This type needs to be specified explicitly for Groups because we can't use a typedef for a UPROPERTY.
- L25 _public function_ `bool Matches(const FScriptableToolGroupSet& OtherSet) const`
- L30 _public function_ `void SetGroups(const FGroupSet& GroupsIn)`
- L36 _public function_ `const FGroupSet& GetGroups() const`
- L41 _public function_ `FGroupSet& GetGroups()`
- L48 _private prototype_ `void SanitizeGroups();`
- L51 _private member_ `TSet<TSubclassOf<UScriptableToolGroupTag>> Groups;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API SCRIPTABLETOOLSFRAMEWORK_API`

### `Plugins/Runtime/ScriptableToolsFramework/Source/ScriptableToolsFramework/Public/Tags/ScriptableToolGroupTag.h` (Public)


#### class `UScriptableToolGroupTag`  
`class UScriptableToolGroupTag : public UObject`  
_L10-18_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable, Const)`
- inherits: `UObject`
- L17 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, Category = "General")`

### `Plugins/Runtime/ScriptableToolsFramework/Source/ScriptableToolsFramework/Public/Utility/ScriptableToolContextObjects.h` (Public)


#### class `UScriptableToolContextObject`  
`class UScriptableToolContextObject : public UObject`  
_L16-31_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Base class for context objects used in the Scriptable Tools Framework.
- L24 _public function_ `virtual void Shutdown()` — Called by the mode when shutting context objects down, allowing them to do any cleanup. Initialization, on the other hand is usually done by some class-specific Initialize() method.
- L30 _public function_ `virtual void OnToolEnded(UInteractiveTool* DeadTool)` — Called whenever a tool is ended, for instance to let a context object remove listeners associated with that tool (it shouldn't have to do so, but may choose to for robustness).

#### class `UScriptableToolViewportWidgetAPI`  
`class UScriptableToolViewportWidgetAPI : public UScriptableToolContextObject`  
_L35-93_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UScriptableToolContextObject`
- L41 _public function_ `void Initialize(TUniqueFunction<void(TSharedRef<SWidget> InOverlaidWidget)> ReplaceOverlaidWidgetFuncIn, TUniqueFunction<void(TSharedRef<SWidget> InOverlaidWidget)> ClearOverlaidWidgetFuncIn)`
- L48 _public function_ `void SetOverlayWidget(TSharedRef<SWidget> InOverlaidWidget)`
- L62 _public function_ `void ClearOverlayWidget()`
- L74 _public function_ `virtual void Shutdown() override`
- L80 _public function_ `virtual void OnToolEnded(UInteractiveTool* DeadTool) override`
- L85 _public member_ `TUniqueFunction<TSharedRef<SWidget>(TSharedRef<SWidget> Content)> MakeDraggableWidgetFunc;`
- L89 _private member_ `TUniqueFunction<void(TSharedRef<SWidget> InOverlaidWidget)> ReplaceOverlaidWidgetFunc;`
- L90 _private member_ `TUniqueFunction<void(TSharedRef<SWidget> InOverlaidWidget)> ClearOverlaidWidgetFunc;`
- L92 _private member_ `TWeakPtr<SWidget> CurrentOverlaidWidget;`

#### class `UScriptableToolViewportFocusAPI`  
`class UScriptableToolViewportFocusAPI : public UScriptableToolContextObject`  
_L96-126_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UScriptableToolContextObject`
- L102 _public function_ `void Initialize(TUniqueFunction<void()> SetFocusInViewportFuncIn)`
- L107 _public function_ `void SetFocusInViewport()`
- L115 _public function_ `virtual void Shutdown() override`
- L119 _public function_ `virtual void OnToolEnded(UInteractiveTool* DeadTool) override`
- L125 _private member_ `TUniqueFunction<void()> SetFocusInViewportFunc;`

### `Plugins/Runtime/ScriptableToolsFramework/Source/ScriptableToolsFramework/Public/Utility/ScriptableToolLogging.h` (Public)
_(no declarations extracted)_
