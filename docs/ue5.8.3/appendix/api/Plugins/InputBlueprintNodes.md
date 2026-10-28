# Plugins / InputBlueprintNodes

- module root: `Plugins/EnhancedInput/Source/InputBlueprintNodes`
- headers: 8; symbols: 121
- symbol kinds: class=9, function=7, macro=5, member=22, namespace=3, prototype=75
- PrivateDependencyModuleNames: BlueprintGraph, Core, CoreUObject, DataValidation, Engine, EnhancedInput, GraphEditor, InputCore, KismetCompiler, PropertyEditor, Slate, SlateCore, UMG, UMGEditor, UnrealEd
- PublicDependencyModuleNames: InputEditor

### `Plugins/EnhancedInput/Source/InputBlueprintNodes/Private/EnhancedInputUserWidgetValidator.h` (Private)


#### class `UEnhancedInputUserWidgetValidator`  
`class UEnhancedInputUserWidgetValidator : public UEditorValidatorBase`  
_L21-37_
- reflection: `UCLASS(NotBlueprintType)`
- inherits: `UEditorValidatorBase`
- desc: Validates Widget Blueprints that have any Enhanced Input nodes in them to ensure that they have the correct "bAutomaticallyRegisterInputOnConstruction" setting value. Widgets require bAutomaticallyRegisterInputOnConstruction to be true in order to receive callbacks from Enhanced Input.
- L27 _public prototype_ `UEnhancedInputUserWidgetValidator() = default;`
- L31 _protected prototype_ `virtual bool CanValidateAsset_Implementation(const FAssetData& InAssetData, UObject* InAsset, FDataValidationContext& InContext) const override;`
- L32 _protected prototype_ `virtual EDataValidationResult ValidateLoadedAsset_Implementation(const FAssetData& InAssetData, UObject* InAsset, FDataValidationContext& InContext) override;`
- L36 _private prototype_ `EDataValidationResult ValidateWidgetBlueprint(const FAssetData& InAssetData, const UWidgetBlueprint* InAsset, FDataValidationContext& InContext);`

### `Plugins/EnhancedInput/Source/InputBlueprintNodes/Private/K2Node_EnhancedInputActionEvent.h` (Private)


#### class `UK2Node_EnhancedInputActionEvent`  
`class UK2Node_EnhancedInputActionEvent : public UK2Node_Event`  
_L16-30_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_Event`
- L21 _private member_ `TObjectPtr<const UInputAction> InputAction;` — `UPROPERTY()`
- L24 _private member_ `ETriggerEvent TriggerEvent;` — `UPROPERTY()`
- L27 _private prototype_ `virtual UClass* GetDynamicBindingClass() const override;`
- L28 _private prototype_ `virtual void RegisterDynamicBinding(UDynamicBlueprintBinding* BindingObject) const override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API INPUTBLUEPRINTNODES_API`

### `Plugins/EnhancedInput/Source/InputBlueprintNodes/Private/K2Node_InputActionValueAccessor.h` (Private)


#### class `UK2Node_InputActionValueAccessor`  
`class UK2Node_InputActionValueAccessor : public UK2Node_CallFunction`  
_L13-38_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_CallFunction`
- L19 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L23 _public prototype_ `virtual UClass* GetDynamicBindingClass() const override;`
- L24 _public prototype_ `virtual void RegisterDynamicBinding(class UDynamicBlueprintBinding* BindingObject) const override;`
- L25 _public function_ `virtual bool IsNodePure() const override`
- L28 _public prototype_ `void Initialize(const UInputAction* Action);`
- L32 _protected function_ `virtual bool CanToggleNodePurity() const override`
- L37 _private member_ `TObjectPtr<const UInputAction> InputAction;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API INPUTBLUEPRINTNODES_API`

### `Plugins/EnhancedInput/Source/InputBlueprintNodes/Private/K2Node_InputDebugKey.h` (Private)


#### class `UInputDebugKeyEventNodeSpawner`  
`class UInputDebugKeyEventNodeSpawner final : public UBlueprintNodeSpawner`  
_L26-38_
- reflection: `UCLASS(Transient)`
- inherits: `UBlueprintNodeSpawner`
- desc: A node spawner which will check if there is already adebug key event node (UInputDebugKeyEventNodeSpawner) before spawning a new one in the graph. This makes the behavior of debug key nodes the same as other event nodes.
- L30 _public prototype_ `static UInputDebugKeyEventNodeSpawner* Create(TSubclassOf<UEdGraphNode> const NodeClass, const FKey& DebugKey);`
- L32 _private prototype_ `virtual UEdGraphNode* Invoke(UEdGraph* ParentGraph, FBindingSet const& Bindings, FVector2D const Location) const override;`
- L34 _private prototype_ `UK2Node* FindExistingNode(const UBlueprint* Blueprint) const;`
- L37 _private member_ `FKey DebugKey = EKeys::Invalid;` — `UPROPERTY()`

#### class `UK2Node_InputDebugKey`  
`class UK2Node_InputDebugKey : public UK2Node, public IK2Node_EventNodeInterface`  
_L41-115_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node,IK2Node_EventNodeInterface`
- L47 _private member_ `FKey InputKey;` — `UPROPERTY(VisibleDefaultsOnly, Category="Input")` — The key that is bound to this debug event. Pressing this key while the game is running will trigger this node's events.
- L51 _private member_ `uint32 bExecuteWhenPaused:1;` — `UPROPERTY(EditAnywhere, Category="Input")` — Should the binding execute even when the game is paused
- L55 _private member_ `uint32 bControl:1;` — `UPROPERTY(EditAnywhere, Category="Modifier")` — Does this binding require the control key on PC or the command key on Mac to be held
- L59 _private member_ `uint32 bAlt:1;` — `UPROPERTY(EditAnywhere, Category="Modifier")` — Does this binding require the alt key to be held
- L63 _private member_ `uint32 bShift:1;` — `UPROPERTY(EditAnywhere, Category="Modifier")` — Does this binding require the shift key to be held
- L67 _private member_ `uint32 bCommand:1;` — `UPROPERTY(EditAnywhere, Category="Modifier")` — Does this binding require the windows key on PC or the control key on Mac to be held
- L70 _private prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L74 _private function_ `virtual bool ShouldShowNodeProperties() const override`
- L75 _private prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L76 _private prototype_ `virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L77 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L78 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L79 _private prototype_ `virtual FBlueprintNodeSignature GetSignature() const override;`
- L83 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L84 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L85 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L86 _private prototype_ `virtual FText GetTooltipText() const override;`
- L87 _private prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L88 _private prototype_ `virtual bool IsCompatibleWithGraph(UEdGraph const* Graph) const override;`
- L92 _private prototype_ `virtual TSharedPtr<FEdGraphSchemaAction> GetEventNodeAction(const FText& ActionCategory) override;`
- L96 _private prototype_ `FText GetModifierText() const;`
- L98 _private prototype_ `FName GetModifierName() const;`
- L100 _private prototype_ `FText GetKeyText() const;`
- L103 _private prototype_ `UEdGraphPin* GetPressedPin() const;` — Get the 'pressed' input pin
- L106 _private prototype_ `UEdGraphPin* GetReleasedPin() const;` — Get the 'released' input pin
- L109 _private prototype_ `UEdGraphPin* GetActionValuePin() const;` — Get the 'Action Value' input pin
- L113 _private member_ `FNodeTextCache CachedTooltip;` — Constructing FText strings can be costly, so we cache the node's title/tooltip
- L114 _private member_ `FNodeTextCache CachedNodeTitle;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API INPUTBLUEPRINTNODES_API`
- L14 _namespace_ `namespace ENodeTitleType`

### `Plugins/EnhancedInput/Source/InputBlueprintNodes/Private/K2Node_InputDebugKeyEvent.h` (Private)


#### class `UK2Node_InputDebugKeyEvent`  
`class UK2Node_InputDebugKeyEvent : public UK2Node_Event`  
_L16-33_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_Event`
- L21 _private member_ `FInputChord InputChord;` — `UPROPERTY()`
- L24 _private member_ `TEnumAsByte<EInputEvent> InputKeyEvent;` — `UPROPERTY()`
- L27 _private member_ `bool bExecuteWhenPaused = false;` — `UPROPERTY()`
- L30 _private prototype_ `virtual UClass* GetDynamicBindingClass() const override;`
- L31 _private prototype_ `virtual void RegisterDynamicBinding(UDynamicBlueprintBinding* BindingObject) const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INPUTBLUEPRINTNODES_API`

### `Plugins/EnhancedInput/Source/InputBlueprintNodes/Public/InputBlueprintNodesModule.h` (Public)
_(no declarations extracted)_

### `Plugins/EnhancedInput/Source/InputBlueprintNodes/Public/K2Node_EnhancedInputAction.h` (Public)


#### class `UInputActionEventNodeSpawner`  
`class UInputActionEventNodeSpawner final : public UBlueprintNodeSpawner`  
_L28-42_
- reflection: `UCLASS(Transient)`
- inherits: `UBlueprintNodeSpawner`
- desc: A node spawner which will check if there is already an enhanced input event node (UK2Node_EnhancedInputAction) before spawning a new one in the graph. This makes the behavior of enhanced input action nodes the same as other event nodes.
- L32 _public prototype_ `static UInputActionEventNodeSpawner* Create(TSubclassOf<UEdGraphNode> const NodeClass, TObjectPtr<const UInputAction> InAction);`
- L34 _private prototype_ `virtual UEdGraphNode* Invoke(UEdGraph* ParentGraph, FBindingSet const& Bindings, FVector2D const Location) const override;`
- L36 _private prototype_ `UK2Node* FindExistingNode(const UBlueprint* Blueprint) const;`
- L41 _private member_ `TWeakObjectPtr<const UInputAction> WeakActionPtr = nullptr;` — `UPROPERTY()` — We don't want references to node spawners to be keeping any input action assets from GC if you unload a plugin for example, so we keep it as a weak pointer.

#### class `UK2Node_EnhancedInputAction`  
`class UK2Node_EnhancedInputAction : public UK2Node, public IK2Node_EventNodeInterface`  
_L45-95_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node,IK2Node_EventNodeInterface`
- L50 _private member_ `TObjectPtr<const UInputAction> InputAction;` — `UPROPERTY()`
- L53 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L54 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L55 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L56 _private prototype_ `virtual FText GetTooltipText() const override;`
- L57 _private prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L58 _private prototype_ `virtual bool IsCompatibleWithGraph(UEdGraph const* Graph) const override;`
- L59 _private prototype_ `virtual UObject* GetJumpTargetForDoubleClick() const override;`
- L60 _private prototype_ `virtual void JumpToDefinition() const override;`
- L64 _private prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L65 _private function_ `virtual bool ShouldShowNodeProperties() const override`
- L66 _private prototype_ `virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L67 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L68 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L69 _private function_ `virtual bool CanUserEditPinAdvancedViewFlag() const override`
- L70 _private prototype_ `virtual FBlueprintNodeSignature GetSignature() const override;`
- L71 _private prototype_ `virtual void PostReconstructNode();`
- L72 _private prototype_ `virtual void PinConnectionListChanged(UEdGraphPin* Pin);`
- L73 _private prototype_ `virtual bool IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const override;`
- L77 _private prototype_ `virtual TSharedPtr<FEdGraphSchemaAction> GetEventNodeAction(const FText& ActionCategory) override;`
- L80 _private prototype_ `bool HasAnyConnectedEventPins() const;`
- L83 _private prototype_ `FName GetActionName() const;`
- L84 _private prototype_ `void HideEventPins(UEdGraphPin* RetainPin);`
- L87 _private prototype_ `void ForEachActiveEventPin(TFunctionRef<bool(ETriggerEvent, UEdGraphPin&)> Predicate) const;` — Iterates each connected trigger event pin until Predicate returns false or we've iterated all active pins
- L90 _private prototype_ `const ETriggerEvent GetTriggerTypeFromExecPin(const UEdGraphPin* ExecPin) const;` — Gets the ETriggerEvent from an exec pin based on the Pins name.
- L93 _private member_ `FNodeTextCache CachedTooltip;` — Constructing FText strings can be costly, so we cache the node's title/tooltip
- L94 _private member_ `FNodeTextCache CachedNodeTitle;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API INPUTBLUEPRINTNODES_API`
- L16 _namespace_ `namespace ENodeTitleType`

### `Plugins/EnhancedInput/Source/InputBlueprintNodes/Public/K2Node_GetInputActionValue.h` (Public)


#### class `UK2Node_GetInputActionValue`  
`class UK2Node_GetInputActionValue : public UK2Node`  
_L17-56_
- reflection: `UCLASS(MinimalAPI, meta=(Keywords = "Get, Input"))`
- inherits: `UK2Node`
- L22 _private member_ `TObjectPtr<const UInputAction> InputAction;` — `UPROPERTY()`
- L25 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L26 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L27 _private prototype_ `virtual FText GetTooltipText() const override;`
- L28 _private prototype_ `virtual bool IsCompatibleWithGraph(UEdGraph const* Graph) const override;`
- L29 _private prototype_ `virtual UObject* GetJumpTargetForDoubleClick() const override;`
- L30 _private prototype_ `virtual void JumpToDefinition() const override;`
- L34 _private prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L35 _private function_ `virtual bool ShouldShowNodeProperties() const override`
- L36 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L37 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L38 _private prototype_ `virtual FBlueprintNodeSignature GetSignature() const override;`
- L39 _private prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L40 _private function_ `virtual bool IsNodePure() const override`
- L43 _private prototype_ `void Initialize(const UInputAction* Action);`
- L46 _private prototype_ `static FName GetValueCategory(const UInputAction* InputAction);` — Auto pin generation helpers
- L47 _private prototype_ `static FName GetValueSubCategory(const UInputAction* InputAction);`
- L48 _private prototype_ `static UScriptStruct* GetValueSubCategoryObject(const UInputAction* InputAction);`
- L51 _private prototype_ `FName GetActionName() const;`
- L54 _private member_ `FNodeTextCache CachedTooltip;` — Constructing FText strings can be costly, so we cache the node's title/tooltip
- L55 _private member_ `FNodeTextCache CachedNodeTitle;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace ENodeTitleType`
