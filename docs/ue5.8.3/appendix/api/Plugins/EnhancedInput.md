# Plugins / EnhancedInput

- module root: `Plugins/EnhancedInput/Source/EnhancedInput`
- headers: 21; symbols: 1067
- symbol kinds: class=46, delegate=17, enum=18, enumerator=82, function=157, macro=23, member=277, namespace=5, prototype=405, struct=31, typedef=3, variable=3
- PrivateDependencyModuleNames: ApplicationCore, Core, CoreUObject, DeveloperSettings, Engine, GameplayTags, InputCore, Slate, SlateCore

### `Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedActionKeyMapping.h` (Public)


#### enum `EPlayerMappableKeySettingBehaviors`  
`enum class EPlayerMappableKeySettingBehaviors : uint8`  
_L20-28_
- reflection: `UENUM(BlueprintType)`
- desc: Defines which Player Mappable Key Setting to use for a Action Key Mapping.
- L23 _public enumerator_ `InheritSettingsFromAction` — Use the Settings specified in the Input Action.
- L25 _public enumerator_ `OverrideSettings` — Use the Settings specified in the Action Key Mapping overriding the ones specified in the Input action.
- L27 _public enumerator_ `IgnoreSettings` — Don't use any Settings even if one is specified in the Input Action.

#### struct `FEnhancedActionKeyMapping`  
`struct FEnhancedActionKeyMapping`  
_L37-214_
- reflection: `USTRUCT(BlueprintType)`
- desc: Defines a mapping between a key activation and the resulting enhanced action An key could be a button press, joystick axis movement, etc. An enhanced action could be MoveForward, Jump, Fire, etc.
- L44 _public prototype_ `FEnhancedActionKeyMapping(const UInputAction* InAction = nullptr, const FKey InKey = EKeys::Invalid);`
- L49 _public prototype_ `UPlayerMappableKeySettings* GetPlayerMappableKeySettings() const;` — Returns the Player Mappable Key Settings owned by the Action Key Mapping or by the referenced Input Action, or nothing based of the Setting Behavior.
- L54 _public prototype_ `FName GetMappingName() const;` — Returns the name of the mapping based on setting behavior used. If no name is found in the Mappable Key Settings it will return the name set in Player Mappable Options if bIsPlayerMappable is true.
- L57 _public prototype_ `const FText& GetDisplayName() const;` — The localized display name of this key mapping
- L60 _public prototype_ `const FText& GetDisplayCategory() const;` — The localized display category of this key mapping
- L65 _public prototype_ `bool IsPlayerMappable() const;` — Returns true if this Action Key Mapping either holds a Player Mappable Key Settings or is set bIsPlayerMappable.
- L68 _public prototype_ `EDataValidationResult IsDataValid(FDataValidationContext& Context) const;`
- L72 _public prototype_ `bool operator==(const FEnhancedActionKeyMapping& Other) const;` — Identical comparison, including Triggers and Modifiers current inner values.
- L80 _public member_ `TArray<TObjectPtr<UInputTrigger>> Triggers;` — `UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = "Input")` — Trigger qualifiers. If any trigger qualifiers exist the mapping will not trigger unless: If there are any Explicit triggers in this list at least one of them must be met. All Implicit triggers in this list must be met.
- L90 _public member_ `TArray<TObjectPtr<UInputModifier>> Modifiers;` — `UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = "Input")` — Modifiers applied to the raw key value. These are applied sequentially in array order. Note: Modifiers defined in individual key mappings will be applied before those defined in the Input Action asset. Modifiers will not override any that are defined on the Input Action asset, they will be combined together during evaluation.
- L94 _public member_ `TObjectPtr<const UInputAction> Action = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")` — Action to be affected by the key
- L98 _public member_ `FKey Key;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")` — Key that affect the action.
- L107 _public member_ `uint8 bShouldBeIgnored : 1;` — `UPROPERTY(Transient)` — If true, then this Key Mapping should be ignored. This is set to true if the key is down during a rebuild of it's owning PlayerInput ControlMappings. @see IEnhancedInputSubsystemInterface::RebuildControlMappings
- L118 _public member_ `uint8 bHasAlwaysTickTrigger : 1;` — `UPROPERTY(Transient)` — True if any triggers on this mapping or its associated UInputAction are flagged as "always tick" triggers. This is only set when control mappings are rebuilt. @see UInputTrigger::bShouldAlwaysTick @see IEnhancedInputSubsystemInterface::ReorderMappings
- L126 _protected member_ `EPlayerMappableKeySettingBehaviors SettingBehavior = EPlayerMappableKeySettingBehaviors::InheritSettingsFromAction;` — `UPROPERTY(EditAnywhere, Category = "Input|Settings")` — Defines which Player Mappable Key Setting to use for a Action Key Mapping.
- L132 _protected member_ `TObjectPtr<UPlayerMappableKeySettings> PlayerMappableKeySettings = nullptr;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Input|Settings", meta = (EditCondition = "SettingBehavior == EPlayerMappableKeySettingBehaviors::OverrideSettings", DisplayAfter = "SettingBehavior"))` — Used to expose this mapping or to opt-out of settings completely.
- L137 _public function_ `template<typename T = UPlayerMappableKeySettings> T* GetPlayerMappableKeySettings() const`
- L148 _public function_ `template<bool bIgnoreModifierAndTriggerValues = true> bool Equals(const FEnhancedActionKeyMapping& Other) const` — If the template bIgnoreModifierAndTriggerValues is true, compare to Other ignoring different trigger states, like pending activation time, but only accept both as equal if the Trigger types are the same and in the same order.
- L172 _public function_ `template<typename T> static bool CompareByObjectTypes(const TArray<TObjectPtr<T>>& A, const TArray<TObjectPtr<T>>& B)` — Compares if two TArray of UObjects contain the same number and types of objects, but doesn't compare their values. This is needed because TArray::operator== returns false when the objects' inner values differ. And for keeping old Trigger states, we need their comparison to ignore their current values.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ENHANCEDINPUT_API`

### `Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputActionDelegateBinding.h` (Public)


#### struct `FBlueprintEnhancedInputActionBinding`  
`struct FBlueprintEnhancedInputActionBinding`  
_L14-28_
- reflection: `USTRUCT()`
- L19 _public member_ `TObjectPtr<const UInputAction> InputAction = nullptr;` — `UPROPERTY()`
- L22 _public member_ `ETriggerEvent TriggerEvent = ETriggerEvent::None;` — `UPROPERTY()`
- L25 _public member_ `FName FunctionNameToBind = NAME_None;` — `UPROPERTY()`

#### class `UEnhancedInputActionDelegateBinding`  
`class UEnhancedInputActionDelegateBinding : public UInputDelegateBinding`  
_L33-43_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInputDelegateBinding`
- L38 _private member_ `TArray<FBlueprintEnhancedInputActionBinding> InputActionDelegateBindings;` — `UPROPERTY()`
- L41 _private prototype_ `virtual void BindToInputComponent(UInputComponent* InputComponent, UObject* ObjectToBindTo) const override;`

#### class `UEnhancedInputActionValueBinding`  
`class UEnhancedInputActionValueBinding : public UInputDelegateBinding`  
_L46-56_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInputDelegateBinding`
- L51 _private member_ `TArray<FBlueprintEnhancedInputActionBinding> InputActionValueBindings;` — `UPROPERTY()`
- L54 _private prototype_ `virtual void BindToInputComponent(UInputComponent* InputComponent, UObject* ObjectToBindTo) const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ENHANCEDINPUT_API`

### `Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h` (Public)


#### struct `TEnhancedInputUnifiedDelegate`  
`template<typename TSignature> struct TEnhancedInputUnifiedDelegate`  
_L46-141_
- desc: Unified storage for both native and dynamic delegates with any signature
- L50 _protected member_ `TSharedPtr<TSignature> Delegate;` — Holds the delegate to call.
- L53 _protected member_ `bool bShouldFireWithEditorScriptGuard = false;` — Should this delegate fire with an Editor Script function guard?
- L56 _public function_ `UObject* GetUObject() const`
- L61 _public function_ `bool IsBound() const`
- L66 _public function_ `bool IsBoundToObject(FDelegateUserObjectConst Object) const`
- L71 _public function_ `void Unbind()`
- L79 _public function_ `void SetShouldFireWithEditorScriptGuard(const bool bNewValue)`
- L81 _public function_ `bool ShouldFireWithEditorScriptGuard() const`
- L87 _public function_ `void BindDelegate(UserClass* Object, typename TSig::template TMethodPtr<UserClass, TVars...> Func, TVars... Vars)`
- L96 _public function_ `void BindDelegate(UObject* Object, const FName FuncName)`
- L105 _public function_ `template<typename TSig = TSignature, typename FunctorType, typename... VarTypes> void BindLambda(FunctorType&& InFunctor, VarTypes&&... Vars)` — Binds a lambda expression
- L113 _public function_ `template<typename TSig = TSignature> TSig& MakeDelegate()`
- L121 _public function_ `template<typename... TArgs> void Execute(TArgs... Args) const`

#### enum `EInputBindingClone`  
`enum class EInputBindingClone : uint8`  
_L145-145_
- desc: Used to force clone constructor calls only
- L145 _public enumerator_ `enum class EInputBindingClone : uint8 { ForceClone }; struct FInputBindingHandle { private: uint32 Handle = 0;` — Used to force clone constructor calls only

#### struct `FInputBindingHandle`  
`struct FInputBindingHandle`  
_L148-166_
- desc: A basic binding unique identifier
- L151 _private member_ `uint32 Handle = 0;`
- L154 _protected prototype_ `FInputBindingHandle();` — Generates a handle
- L155 _protected function_ `FInputBindingHandle(const FInputBindingHandle& CloneFrom, EInputBindingClone) : Handle(CloneFrom.Handle)` — Clones a handle
- L158 _public prototype_ `virtual ~FInputBindingHandle() = default;`
- L160 _public function_ `bool operator==(const FInputBindingHandle& Rhs) const`
- L165 _public function_ `uint32 GetHandle() const`

#### struct `FEnhancedInputActionEventBinding`  
`struct FEnhancedInputActionEventBinding : public FInputBindingHandle`  
_L169-212_
- inherits: `FInputBindingHandle`
- desc: A binding to an input action trigger event.
- L174 _private member_ `TWeakObjectPtr<const UInputAction> Action;` — Action against which we are bound
- L177 _private member_ `ETriggerEvent TriggerEvent = ETriggerEvent::None;` — Trigger event that raises the delegate
- L183 _private member_ `uint8 bConsumes : 1 = false;` — If true, then this event binding will stop any other listeners to the same UInputAction with a lower input component priority on the stack.
- L187 _protected function_ `FEnhancedInputActionEventBinding(const FEnhancedInputActionEventBinding& CloneFrom, EInputBindingClone Clone) : FInputBindingHandle(CloneFrom, Clone), Action(CloneFrom.Action), TriggerEvent(CloneFrom.TriggerEvent), bConsumes(CloneFrom.bConsumes)` — Clone constructor
- L194 _public prototype_ `FEnhancedInputActionEventBinding() = default;`
- L195 _public function_ `FEnhancedInputActionEventBinding( const UInputAction* InAction, ETriggerEvent InTriggerEvent, const bool bRequestsConsumption = false) : Action(InAction), TriggerEvent(InTriggerEvent), bConsumes(bRequestsConsumption)`
- L201 _public function_ `const UInputAction* GetAction() const`
- L202 _public function_ `bool ShouldConsume() const`
- L203 _public function_ `ETriggerEvent GetTriggerEvent() const`
- L205 _public function_ `void SetShouldConsume(const bool bNewConsumeValue)`
- L207 _public prototype_ `virtual void Execute(const FInputActionInstance& ActionData) const = 0;`
- L208 _public prototype_ `virtual TUniquePtr<FEnhancedInputActionEventBinding> Clone() const = 0;`
- L209 _public prototype_ `virtual void SetShouldFireWithEditorScriptGuard(const bool bNewValue) = 0;`
- L210 _public prototype_ `virtual bool IsBoundToObject(FDelegateUserObjectConst Object) const = 0;`
- L211 _public function_ `virtual UObject* GetUObject() const`

#### struct `FEnhancedInputActionValueBinding`  
`struct FEnhancedInputActionValueBinding : public FInputBindingHandle`  
_L215-232_
- inherits: `FInputBindingHandle`
- desc: Binds an action value for later reference. CurrentValue will be kept up to date with the value of the bound action
- L221 _private member_ `TWeakObjectPtr<const UInputAction> Action;` — Action against which we are bound
- L224 _private member_ `mutable FInputActionValue CurrentValue;` — Copy of the current value of the action
- L227 _public prototype_ `FEnhancedInputActionValueBinding() = default;`
- L228 _public function_ `FEnhancedInputActionValueBinding(const UInputAction* InAction) : Action(InAction)`
- L230 _public function_ `const UInputAction* GetAction() const`
- L231 _public function_ `FInputActionValue GetValue() const`

#### struct `FInputDebugKeyBinding`  
`struct FInputDebugKeyBinding : public FInputBindingHandle`  
_L235-266_
- inherits: `FInputBindingHandle`
- desc: Binds a delegate to an event on a key chord.
- L239 _protected function_ `FInputDebugKeyBinding(const FInputDebugKeyBinding& CloneFrom, EInputBindingClone Clone) : FInputBindingHandle(CloneFrom, Clone) , KeyEvent(CloneFrom.KeyEvent) , bExecuteWhenPaused(CloneFrom.bExecuteWhenPaused) , Chord(CloneFrom.Chord)` — Clone constructor
- L248 _public member_ `TEnumAsByte<EInputEvent> KeyEvent = EInputEvent::IE_Pressed;` — Key event to bind it to (e.g. pressed, released, double click)
- L250 _public member_ `bool bExecuteWhenPaused = false;`
- L253 _public member_ `FInputChord Chord;` — Input Chord to bind to
- L257 _public prototype_ `FInputDebugKeyBinding() = default;`
- L258 _public function_ `FInputDebugKeyBinding(const FInputChord InChord, const EInputEvent InKeyEvent, bool bInExecuteWhenPaused) : KeyEvent(InKeyEvent) , bExecuteWhenPaused(bInExecuteWhenPaused) , Chord(InChord)`
- L264 _public prototype_ `virtual void Execute(const FInputActionValue& ActionValue) const = 0;`
- L265 _public prototype_ `virtual TUniquePtr<FInputDebugKeyBinding> Clone() const = 0;`

#### struct `FEnhancedInputActionEventDelegateBinding`  
`template<typename TSignature> struct FEnhancedInputActionEventDelegateBinding : FEnhancedInputActionEventBinding`  
_L276-312_
- inherits: `FEnhancedInputActionEventBinding`
- L279 _private function_ `FEnhancedInputActionEventDelegateBinding(const FEnhancedInputActionEventDelegateBinding<TSignature>& CloneFrom, EInputBindingClone Clone) : FEnhancedInputActionEventBinding(CloneFrom, Clone), Delegate(CloneFrom.Delegate)`
- L285 _public function_ `FEnhancedInputActionEventDelegateBinding(const UInputAction* Action, ETriggerEvent InTriggerEvent, const bool bRequestsConsumption = false) : FEnhancedInputActionEventBinding(Action, InTriggerEvent, bRequestsConsumption)`
- L290 _public prototype_ `virtual void Execute(const FInputActionInstance& ActionData) const override;` — Implemented below.
- L291 _public function_ `virtual TUniquePtr<FEnhancedInputActionEventBinding> Clone() const override`
- L296 _public function_ `virtual void SetShouldFireWithEditorScriptGuard(const bool bNewValue) override`
- L301 _public function_ `virtual bool IsBoundToObject(FDelegateUserObjectConst Object) const override`
- L306 _public function_ `virtual UObject* GetUObject() const override`
- L311 _public member_ `TEnhancedInputUnifiedDelegate<TSignature> Delegate;`
- L338 _function_ `template<> inline void FEnhancedInputActionEventDelegateBinding<FEnhancedInputActionHandlerSignature>::Execute(const FInputActionInstance& ActionData) const`
- L344 _function_ `template<> inline void FEnhancedInputActionEventDelegateBinding<FEnhancedInputActionHandlerValueSignature>::Execute(const FInputActionInstance& ActionData) const`
- L350 _function_ `template<> inline void FEnhancedInputActionEventDelegateBinding<FEnhancedInputActionHandlerInstanceSignature>::Execute(const FInputActionInstance& ActionData) const`
- L356 _function_ `template<> inline void FEnhancedInputActionEventDelegateBinding<FEnhancedInputActionHandlerDynamicSignature>::Execute(const FInputActionInstance& ActionData) const`

#### struct `FInputDebugKeyDelegateBinding`  
`template<typename TSignature> struct FInputDebugKeyDelegateBinding : FInputDebugKeyBinding`  
_L315-332_
- inherits: `FInputDebugKeyBinding`
- L318 _private function_ `FInputDebugKeyDelegateBinding(const FInputDebugKeyDelegateBinding<TSignature>& CloneFrom, EInputBindingClone Clone) : FInputDebugKeyBinding(CloneFrom, Clone), Delegate(CloneFrom.Delegate)`
- L320 _public function_ `FInputDebugKeyDelegateBinding(const FInputChord Chord, const EInputEvent KeyEvent, bool bExecuteWhenPaused) : FInputDebugKeyBinding(Chord, KeyEvent, bExecuteWhenPaused)`
- L322 _public function_ `virtual void Execute(const FInputActionValue& ActionValue) const override`
- L326 _public function_ `virtual TUniquePtr<FInputDebugKeyBinding> Clone() const override`
- L331 _public member_ `TEnhancedInputUnifiedDelegate<TSignature> Delegate;`

#### class `UEnhancedInputComponent`  
`class UEnhancedInputComponent : public UInputComponent`  
_L373-636_
- reflection: `UCLASS(MinimalAPI, transient, config=Input, hidecategories=(Activation, "Components|Activation"))`
- inherits: `UInputComponent`
- desc: Implement an Actor component for input bindings. An Enhanced Input Component is a transient component that enables an Actor to bind enhanced actions to delegate functions, or monitor those actions. Input components are processed from a stack managed by the PlayerController and processed by the PlayerInput. These bindings will not consume input events, but this behaviour can be replicated using UInputMappingContext::Priority. @see https://docs.unrealengine.com/latest/INT/Gameplay/Input/index.html
- L381 _protected member_ `TArray<TUniquePtr<FEnhancedInputActionEventBinding>> EnhancedActionEventBindings;` — The collection of action bindings.
- L384 _protected member_ `TArray<FEnhancedInputActionValueBinding> EnhancedActionValueBindings;` — The collection of action value bindings. These do not have delegates and are used to store a copy of the current action value only.
- L387 _protected member_ `TArray<TUniquePtr<FInputDebugKeyBinding>> DebugKeyBindings;` — Debug key bindings, available in non-shipping builds only.
- L395 _protected member_ `bool bShouldFireDelegatesInEditor = false;` — If true, then this input component's delegate bindings will fire with a FEditorScriptExecutionGuard around it. This means that the events bound to this component can be triggered outside of "-game" scenarios, such as in the level editor. NOTE: Enabling this can interfere with events processed on gameplay actors (UE-148305)
- L398 _protected member_ `bool bShouldCheckForLegacyKeyConsumption = false;` — Whether to check when evaluating the input stack whether legacy inputs can consume keys
- L406 _public function_ `void SetShouldCheckForLegacyKeyConsumption(bool bNewValue)` — Sets whether this component supports checking for legacy input binds that might consume keys
- L412 _public prototype_ `bool ShouldCheckForLegacyKeyConsumption() const;` — Whether this component supports checking for legacy input binds that might consume keys
- L414 _public prototype_ `void SetShouldFireDelegatesInEditor(const bool bInNewValue);`
- L416 _public function_ `bool ShouldFireDelegatesInEditor() const`
- L423 _public prototype_ `virtual bool HasBindings() const override;` — Checks whether this component has any input bindings. @return true if any bindings are set, false otherwise.
- L429 _public function_ `void ClearActionEventBindings()` — Removes all action bindings.
- L430 _public function_ `void ClearActionValueBindings()`
- L431 _public function_ `void ClearDebugKeyBindings()`
- L434 _public prototype_ `virtual void ClearActionBindings() override;` — Removes all action bindings.
- L437 _public prototype_ `virtual void ClearBindingsForObject(UObject* InOwner) override;` — Clears any input callback delegates from the given UObject
- L444 _public function_ `const TArray<TUniquePtr<FEnhancedInputActionEventBinding>>& GetActionEventBindings() const` — Gets all action bindings of type @see BindAction, ClearActionEventBindings, GetNumActionEventBindings, RemoveActionEventBinding
- L445 _public function_ `const TArray<FEnhancedInputActionValueBinding>& GetActionValueBindings() const`
- L446 _public function_ `const TArray<TUniquePtr<FInputDebugKeyBinding>>& GetDebugKeyBindings() const`
- L455 _public prototype_ `bool RemoveActionEventBinding(const int32 BindingIndex);` — Removes the action binding at the specified index. @param BindingIndex The index of the binding to remove. @return Whether the binding was successfully removed. @see BindAction, ClearActionEventBindings, GetActionEventBinding, GetNumActionEventBindings
- L456 _public prototype_ `bool RemoveDebugKeyBinding(const int32 BindingIndex);`
- L457 _public prototype_ `bool RemoveActionValueBinding(const int32 BindingIndex);`
- L466 _public prototype_ `bool RemoveBindingByHandle(const uint32 Handle);` — Removes the binding with the specified handle. Binding handles are unique across all bindings. @param Handle The handle of the binding to remove. @return Whether the binding was successfully removed. @see BindAction, ClearActionEventBindings, GetActionEventBinding, GetNumActionEventBindings
- L475 _public prototype_ `bool RemoveBinding(const FInputBindingHandle& BindingToRemove);` — Removes an arbitrary binding @param BindingToRemove The binding to remove, as returned by BindAction/BindActionValue/BindDebugKey @return Whether the binding was successfully removed. @see BindAction, BindDebugKey, ClearActionEventBindings, ClearDebugKeyBindings
- L490 _public prototype_ `DEFINE_BIND_ACTION(FEnhancedInputActionHandlerSignature);`
- L491 _public prototype_ `DEFINE_BIND_ACTION(FEnhancedInputActionHandlerValueSignature);`
- L492 _public prototype_ `DEFINE_BIND_ACTION(FEnhancedInputActionHandlerInstanceSignature);`
- L497 _public function_ `FEnhancedInputActionEventBinding& BindAction(const UInputAction* Action, ETriggerEvent TriggerEvent, UObject* Object, FName FunctionName)` — Binds to an object UFUNCTION
- L517 _public function_ `template<typename FunctorType, typename... VarTypes> FEnhancedInputActionEventBinding& BindActionValueLambda(const UInputAction* Action, ETriggerEvent TriggerEvent, FunctorType&& InFunctor, VarTypes&&... Vars)` — Binds a lambda expression to receive the input action value form an input event. Example: InputComponent->BindActionValueLambda( TestAction, ETriggerEvent::Triggered, [](const FInputActionValue& InputActionValue) { // Do you work here! });
- L539 _public function_ `template<typename FunctorType, typename... VarTypes> FEnhancedInputActionEventBinding& BindActionInstanceLambda(const UInputAction* Action, ETriggerEvent TriggerEvent, FunctorType&& InFunctor, VarTypes&&... Vars)` — Bind a lambda to receive the action instance data from an input event. Example: InputComponent->BindActionInstanceLambda( TestAction, ETriggerEvent::Triggered, [](const FInputActionInstance& ActionInstance) { // Do you work here! });
- L553 _public function_ `FEnhancedInputActionValueBinding& BindActionValue(const UInputAction* Action)` — Binds a UInputAction assigned via UInputMappingContext to this component. No delegate will be called when this action triggers. The binding simply reflects the current value of the action.
- L568 _public function_ `template<class UserClass> FInputDebugKeyBinding& BindDebugKey(const FInputChord Chord, const EInputEvent KeyEvent, UserClass* Object, typename FInputDebugKeyHandlerSignature::TMethodPtr< UserClass > Func, bool bExecuteWhenPaused = true)` — Binds a chord event to a delegate function in development builds only.
- L581 _public function_ `FInputDebugKeyBinding& BindDebugKey(const FInputChord Chord, const EInputEvent KeyEvent, UObject* Object, FName FunctionName, bool bExecuteWhenPaused = true)` — Binds to an object UFUNCTION
- L596 _public prototype_ `FInputActionValue GetBoundActionValue(const UInputAction* Action) const;` — `UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", HideSelfPin = "true", HidePin = "Action"))` — Helper function to pull the action value for a bound action value.
- L613 _public prototype_ `template<class UserClass> FInputActionBinding& BindAction(const FName ActionName, const EInputEvent KeyEvent, UserClass* Object, typename FInputActionHandlerSignature::TMethodPtr< UserClass > Func) = delete;` — Delete all InputComponent binding helpers. Indicates intentions going forward and improves intellisense/VAX when working with EnhancedInputCompoennts.
- L615 _public prototype_ `template<class UserClass> FInputActionBinding& BindAction(const FName ActionName, const EInputEvent KeyEvent, UserClass* Object, typename FInputActionHandlerWithKeySignature::TMethodPtr< UserClass > Func) = delete;`
- L617 _public prototype_ `template< class DelegateType, class UserClass, typename... VarTypes > FInputActionBinding& BindAction(const FName ActionName, const EInputEvent KeyEvent, UserClass* Object, typename DelegateType::template TMethodPtr< UserClass > Func, VarTypes... Vars) = delete;`
- L619 _public prototype_ `template<class UserClass> FInputAxisBinding& BindAxis(const FName AxisName, UserClass* Object, typename FInputAxisHandlerSignature::TMethodPtr< UserClass > Func) = delete;`
- L620 _public prototype_ `FInputAxisBinding& BindAxis(const FName AxisName) = delete;`
- L622 _public prototype_ `template<class UserClass> FInputAxisKeyBinding& BindAxisKey(const FKey AxisKey, UserClass* Object, typename FInputAxisHandlerSignature::TMethodPtr< UserClass > Func) = delete;`
- L623 _public prototype_ `FInputAxisKeyBinding& BindAxisKey(const FKey AxisKey) = delete;`
- L625 _public prototype_ `template<class UserClass> FInputVectorAxisBinding& BindVectorAxis(const FKey AxisKey, UserClass* Object, typename FInputVectorAxisHandlerSignature::TMethodPtr< UserClass > Func) = delete;`
- L626 _public prototype_ `FInputVectorAxisBinding& BindVectorAxis(const FKey AxisKey) = delete;`
- L628 _public prototype_ `template<class UserClass> FInputKeyBinding& BindKey(const FInputChord Chord, const EInputEvent KeyEvent, UserClass* Object, typename FInputActionHandlerSignature::TMethodPtr< UserClass > Func) = delete;`
- L630 _public prototype_ `template<class UserClass> FInputKeyBinding& BindKey(const FKey Key, const EInputEvent KeyEvent, UserClass* Object, typename FInputActionHandlerSignature::TMethodPtr< UserClass > Func) = delete;`
- L632 _public prototype_ `template<class UserClass> FInputTouchBinding& BindTouch(const EInputEvent KeyEvent, UserClass* Object, typename FInputTouchHandlerSignature::TMethodPtr< UserClass > Func) = delete;`
- L634 _public prototype_ `template<class UserClass> FInputGestureBinding& BindGesture(const FKey GestureKey, UserClass* Object, typename FInputGestureHandlerSignature::TMethodPtr< UserClass > Func) = delete;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ENHANCEDINPUT_API`
- L14 _macro_ `#define DEV_ONLY_KEY_BINDINGS_AVAILABLE (!UE_BUILD_SHIPPING)`
- L20 _delegate_ `DECLARE_DELEGATE_TwoParams(FInputDebugKeyHandlerSignature, FKey, FInputActionValue);` — Delegate signature for debug key events.
- L20 _prototype_ `DECLARE_DELEGATE_TwoParams(FInputDebugKeyHandlerSignature, FKey, FInputActionValue);` — Delegate signature for debug key events.
- L21 _delegate_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FInputDebugKeyHandlerDynamicSignature, FKey, Key, FInputActionValue, ActionValue);`
- L21 _prototype_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FInputDebugKeyHandlerDynamicSignature, FKey, Key, FInputActionValue, ActionValue);`
- L24 _delegate_ `DECLARE_DELEGATE(FEnhancedInputActionHandlerSignature);` — Delegate signature for action events.
- L24 _prototype_ `DECLARE_DELEGATE(FEnhancedInputActionHandlerSignature);` — Delegate signature for action events.
- L25 _delegate_ `DECLARE_DELEGATE_OneParam(FEnhancedInputActionHandlerValueSignature, const FInputActionValue&);`
- L25 _prototype_ `DECLARE_DELEGATE_OneParam(FEnhancedInputActionHandlerValueSignature, const FInputActionValue&);`
- L26 _delegate_ `DECLARE_DELEGATE_OneParam(FEnhancedInputActionHandlerInstanceSignature, const FInputActionInstance&);`
- L26 _prototype_ `DECLARE_DELEGATE_OneParam(FEnhancedInputActionHandlerInstanceSignature, const FInputActionInstance&);` — Provides full access to value and timers
- L33 _delegate_ `DECLARE_DYNAMIC_DELEGATE_FourParams(FEnhancedInputActionHandlerDynamicSignature, FInputActionValue, ActionValue, float, ElapsedTime, float, TriggeredTime, const UInputAction*, SourceAction);` — @param ActionValue		The combined value of all inputs mapped to this action. @param ElapsedTime		The amount of time in seconds that has elapsed since this input action has begun processing its input values. @param TriggeredTime		The amount of time in seconds that this input action has been in the "triggered" state. @param SourceAction		The input action which caused this event to fire.
- L33 _prototype_ `DECLARE_DYNAMIC_DELEGATE_FourParams(FEnhancedInputActionHandlerDynamicSignature, FInputActionValue, ActionValue, float, ElapsedTime, float, TriggeredTime, const UInputAction*, SourceAction);` — @param ActionValue		The combined value of all inputs mapped to this action. @param ElapsedTime		The amount of time in seconds that has elapsed since this input action has begun processing its input values. @param TriggeredTime		The amount of time in seconds that this input action has been in the "triggered" state. @param SourceAction		The input action which caused this event to fire.
- L39 _macro_ `#define ENABLE_EDITOR_CALLABLE_INPUT_DELEGATES WITH_EDITOR`
- L41 _macro_ `#define ENABLE_EDITOR_CALLABLE_INPUT_DELEGATES 0`
- L480 _macro_ `#define DEFINE_BIND_ACTION(HANDLER_SIG) \` — Binds a delegate function matching any of the handler signatures to a UInputAction assigned via UInputMappingContext to the owner of this component.
- L556 _function_ `if (FEnhancedInputActionValueBinding* Existing = EnhancedActionValueBindings.FindByPredicate([Action](const FEnhancedInputActionValueBinding& TestBinding) { return TestBinding.GetAction() == Action; }))` (scope `UEnhancedInputComponent::BindActionValue`) — Only one action value binding is required per action
- L607 _macro_ `#define ENHANCED_INPUT_ALLOW_LEGACY_BINDING 0`

### `Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputDeveloperSettings.h` (Public)


#### struct `FDefaultContextSetting`  
`struct FDefaultContextSetting`  
_L20-39_
- reflection: `USTRUCT()`
- desc: Represents a single input mapping context and the priority that it should be applied with
- L26 _public member_ `TSoftObjectPtr<const UInputMappingContext> InputMappingContext = nullptr;` — `UPROPERTY(EditAnywhere, Config, Category = "Input")` — Input Mapping Context that should be Added to the EnhancedInputEditorSubsystem when it starts listening for input
- L30 _public member_ `int32 Priority = 0;` — `UPROPERTY(EditAnywhere, Config, Category = "Input")` — The prioirty that should be given to this mapping context when it is added
- L34 _public member_ `bool bAddImmediately = true;` — `UPROPERTY(EditAnywhere, Config, Category = "Input")` — If true, then this IMC will be applied immediately when the EI subsystem is ready
- L38 _public member_ `bool bRegisterWithUserSettings = false;` — `UPROPERTY(EditAnywhere, Config, Category = "Input")` — If true, then this IMC will be registered with the User Input Settings (if one is available) immediately when the Enhanced Input subsystem starts.

#### class `UEnhancedInputDeveloperSettings`  
`class UEnhancedInputDeveloperSettings : public UDeveloperSettingsBackedByCVars`  
_L43-164_
- reflection: `UCLASS(MinimalAPI, config = Input, defaultconfig, meta = (DisplayName = "Enhanced Input"))`
- inherits: `UDeveloperSettingsBackedByCVars`
- desc: Developer settings for Enhanced Input
- L48 _public prototype_ `UEnhancedInputDeveloperSettings(const FObjectInitializer& Initializer);`
- L55 _public member_ `TArray<FDefaultContextSetting> DefaultMappingContexts;` — `UPROPERTY(config, EditAnywhere, Category = "Enhanced Input", meta = (editCondition = "bEnableDefaultMappingContexts"))` — Array of any input mapping contexts that you want to be applied by default to the Enhanced Input local player subsystem. NOTE: These mapping context's can only be from your game's root content directory, not plugins.
- L62 _public member_ `TArray<FDefaultContextSetting> DefaultWorldSubsystemMappingContexts;` — `UPROPERTY(config, EditAnywhere, Category = "Enhanced Input|World Subsystem", meta = (editCondition = "bEnableDefaultMappingContexts && bEnableWorldSubsystem"))` — Array of any input mapping contexts that you want to be applied by default to the Enhanced Input world subsystem. NOTE: These mapping context's can only be from your game's root content directory, not plugins.
- L69 _public member_ `FPerPlatformSettings PlatformSettings;` — `UPROPERTY(EditAnywhere, Category = "Enhanced Input")` — Platform specific settings for Enhanced Input. @see UEnhancedInputPlatformSettings
- L78 _public member_ `TSoftClassPtr<UEnhancedInputUserSettings> UserSettingsClass;` — `UPROPERTY(config, EditAnywhere, NoClear, Category = "Enhanced Input|User Settings", meta=(editCondition = "bEnableUserSettings"))` — The class that should be used for the User Settings by each Enhanced Input subsystem. An instance of this class will be spawned by each Enhanced Input subsytem as a place to store user settings such as keymappings, accessibility settings, etc. Subclass this to add more custom options to your game.
- L84 _public member_ `TSoftClassPtr<UEnhancedPlayerMappableKeyProfile> DefaultPlayerMappableKeyProfileClass;` — `UPROPERTY(config, EditAnywhere, NoClear, Category = "Enhanced Input|User Settings", meta=(editCondition = "bEnableUserSettings"))` — The default class for the player mappable key profile, used to store the key mappings set by the player in the user settings.
- L95 _public member_ `FString InputSettingsSaveSlotName = TEXT("Enh` — `UPROPERTY(config, EditAnywhere, NoClear, Category = "Enhanced Input|User Settings", meta=(editCondition = "bEnableUserSettings"))` — The default SaveGame slot name to use when loading/saving Enhanced Input user settings. The file name will be this string with ".sav" appended to the end of it. So, on disk, the file would be "<InputSettingsSaveSlotName>.sav". This file will be written to the "SaveGames" directory, which is "<Project Folder>/Saved/SaveGames" in the editor.
- L99 _public member_ `TSoftClassPtr<UEnhancedPlayerInput> DefaultWorldInputClass;` — `UPROPERTY(config, EditAnywhere, NoClear, Category = "Enhanced Input|World Subsystem", meta=(editCondition = "bEnableWorldSubsystem"))` — The default player input class that the Enhanced Input world subsystem will use.
- L108 _public member_ `uint8 bSendTriggeredEventsWhenInputIsFlushed : 1;` — `UPROPERTY(config, EditAnywhere, Category = "Enhanced Input")` — If true, then any in progress Enhanced Input Actions will fire Cancelled and Triggered events when input is flushed (i.e. the viewport has lost focus, or UEnhancedPlayerInput::FlushPressedKeys has been called) If false, then enhanced input actions may not fire their delegates when input is flushed and their key state would be retained.
- L114 _public member_ `uint8 bEnableUserSettings : 1;` — `UPROPERTY(config, EditAnywhere, Category = "Enhanced Input|User Settings", meta=(DisplayName="Enable User Settings", DisplayPriority = 1))` — If true, then an instance of the User Settings Class will be created on each Enhanced Input subsystem.
- L118 _public member_ `uint8 bEnableDefaultMappingContexts : 1;` — `UPROPERTY(config, EditAnywhere, Category = "Enhanced Input", meta = (ConsoleVariable = "EnhancedInput.EnableDefaultMappingContexts"))` — If true, then the DefaultMappingContexts will be applied to all Enhanced Input Subsystems.
- L127 _public member_ `uint8 bShouldOnlyTriggerLastActionInChord : 1;` — `UPROPERTY(config, EditAnywhere, Category = "Enhanced Input", meta=(ConsoleVariable="EnhancedInput.OnlyTriggerLastActionInChord"))` — If true, then only the last action in a ChordedAction trigger will be fired. This means that only the action that has the ChordedTrigger on it will be fired, not the individual steps. Default value is true.
- L140 _public member_ `uint8 bEnableInputModeFiltering : 1;` — `UPROPERTY(config, EditAnywhere, Category = "Enhanced Input|Input Modes")` — If true, then Enhanced Input will filter which Input Mapping Context mappings are processed based on the current value of the "Current Input Mode". If a mapping context's query does not match with the current input mode tag container, then its mappings will not be processed. Default Value is true. @see IEnhancedInputSubsystemInterface::RebuildControlMappings @see UEnhancedPlayerInput::CurrentInputMode
- L144 _public member_ `uint8 bEnableWorldSubsystem : 1;` — `UPROPERTY(config, EditAnywhere, Category = "Enhanced Input|World Subsystem", meta=(DisplayName="Enable World Subsystem (Experimental)", DisplayPriority = 1))` — If true, then the world subsystem will be created.
- L151 _public member_ `uint8 bShouldLogAllWorldSubsystemInputs : 1 = false;` — `UE_DEPRECATED(5.6, "bShouldLogAllWorldSubsystemInputs is deprecated, use the log category on VeryVerbose for LogWorldSubsystemInput instead.")` — If true then the Enhanced Input world subsystem will log all input that is being processed by it (keypresses, analog values, etc) Note: This can produce A LOT of logs, so only use this if you are debugging something. Does nothing in shipping builds
- L157 _public member_ `FGameplayTagQuery DefaultMappingContextInputModeQuery;` — `UPROPERTY(config, EditAnywhere, Category = "Enhanced Input|Input Modes", meta = (EditCondition="bEnableInputModeFiltering"))` — This value will be used to populate the default InputModeQuery on Input Mapping Contexts.
- L163 _public member_ `FGameplayTagContainer DefaultInputMode;` — `UPROPERTY(config, EditAnywhere, Category = "Enhanced Input|Input Modes", meta = (EditCondition="bEnableInputModeFiltering"))` — The default input mode which will be set when a UEnhancedPlayerInput object is created.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API ENHANCEDINPUT_API`

### `Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputLibrary.h` (Public)


#### class `UEnhancedInputLibrary`  
`class UEnhancedInputLibrary : public UBlueprintFunctionLibrary`  
_L21-108_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L29 _public prototype_ `static void ForEachSubsystem(TFunctionRef<void(IEnhancedInputSubsystemInterface*)> SubsystemPredicate);` — Call SubsystemPredicate on each registered player and standalone enhanced input subsystem.
- L37 _public prototype_ `static void RequestRebuildControlMappingsUsingContext(const UInputMappingContext* Context, bool bForceImmediately = false);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Input")` — Flag all enhanced input subsystems making use of the mapping context for reapplication of all control mappings at the end of this frame. @param Context				Mappings will be rebuilt for all subsystems utilizing this context. @param bForceImmediately		The mapping changes will be applied synchronously, rather than at the end of the frame, making them available to the input system on the same frame.
- L42 _public prototype_ `static void BreakInputActionValue(FInputActionValue InActionValue, double& X, double& Y, double& Z, EInputActionValueType& Type);` — `UFUNCTION(BlueprintPure, Category = "Input", meta = (NativeBreakFunc))` — Breaks an ActionValue into X, Y, Z. Axes not supported by value type will be 0.
- L49 _public prototype_ `static FInputActionValue MakeInputActionValueOfType(double X, double Y, double Z, const EInputActionValueType ValueType);` — `UFUNCTION(BlueprintPure, Category = "Input", meta = (Keywords = "construct build", NativeMakeFunc))` — Builds an ActionValue from X, Y, Z. Inherits type from an existing ActionValue. Ignores axis values unused by the provided value type. @note Intended for use in Input Modifier Modify Raw overloads to modify an existing Input Action Value.
- L55 _public prototype_ `static UPlayerMappableKeySettings* GetPlayerMappableKeySettings(UPARAM(ref) const FEnhancedActionKeyMapping& ActionKeyMapping);` — `UFUNCTION(BlueprintPure, Category = "Input", meta = (ReturnDisplayName = "Player Mappable Key Settings"))` — Returns the Player Mappable Key Settings owned by the Action Key Mapping or by the referenced Input Action, or nothing based of the Setting Behavior.
- L61 _public prototype_ `static FName GetMappingName(UPARAM(ref) const FEnhancedActionKeyMapping& ActionKeyMapping);` — `UFUNCTION(BlueprintPure, Category = "Input", meta = (ReturnDisplayName = "Mapping Name"))` — Returns the name of the mapping based on setting behavior used. If no name is found in the Mappable Key Settings it will return the name set in Player Mappable Options if bIsPlayerMappable is true.
- L67 _public prototype_ `static bool IsActionKeyMappingPlayerMappable(UPARAM(ref) const FEnhancedActionKeyMapping& ActionKeyMapping);` — `UFUNCTION(BlueprintPure, Category = "Input", meta = (ReturnDisplayName = "Is Player Mappable"))` — Returns true if this Action Key Mapping either holds a Player Mappable Key Settings or is set bIsPlayerMappable.
- L73 _public prototype_ `static FInputActionValue GetBoundActionValue(AActor* Actor, const UInputAction* Action);` — `UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, meta = (HidePin = "Action"))` — GetInputActionvalue internal accessor function for actions that have been bound to from a UEnhancedInputComponent
- L79 _public prototype_ `static bool Conv_InputActionValueToBool(FInputActionValue InValue);` — `UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, meta = (BlueprintAutocast))` — Interpret an InputActionValue as a boolean input
- L83 _public prototype_ `static double Conv_InputActionValueToAxis1D(FInputActionValue InValue);` — `UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, meta = (BlueprintAutocast))` — Interpret an InputActionValue as a 1D axis (double) input
- L87 _public prototype_ `static FVector2D Conv_InputActionValueToAxis2D(FInputActionValue InValue);` — `UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, meta = (BlueprintAutocast))` — Interpret an InputActionValue as a 2D axis (Vector2D) input
- L91 _public prototype_ `static FVector Conv_InputActionValueToAxis3D(FInputActionValue ActionValue);` — `UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, meta = (BlueprintAutocast))` — Interpret an InputActionValue as a 3D axis (Vector) input
- L95 _public prototype_ `static FString Conv_InputActionValueToString(FInputActionValue ActionValue);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "To String (InputActionValue)", CompactNodeTitle = "->", BlueprintAutocast), Category = "Utilities|String")` — Converts a FInputActionValue to a string
- L99 _public prototype_ `static FString Conv_TriggerEventValueToString(const ETriggerEvent TriggerEvent);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "To String (ETriggerEvent)", CompactNodeTitle = "->", BlueprintAutocast), Category = "Utilities|String")` — Converts an ETriggerEvent to a string
- L107 _public prototype_ `static void FlushPlayerInput(APlayerController* PlayerController);` — `UFUNCTION(BlueprintCallable, Category="Input")` — Flushes the player controller's pressed keys @see APlayerController::FlushPressedKeys

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ENHANCEDINPUT_API`

### `Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputModule.h` (Public)


#### struct `FEnhancedInputKeys`  
`struct FEnhancedInputKeys`  
_L17-22_
- L21 _public member_ `static const FKey ComboKey;` — `UE_DEPRECATED(5.8, "The combo trigger and key have been deprecated")` — Combo FKey that serves as the key combo triggers are automatically mapped to - is not action bindable

#### class `IEnhancedInputModule`  
`class IEnhancedInputModule : public IModuleInterface`  
_L27-58_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L38 _public function_ `static inline IEnhancedInputModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L50 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L56 _public prototype_ `virtual UEnhancedInputLibrary* GetLibrary() = 0;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ENHANCEDINPUT_API`
- L15 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogEnhancedInput, Log, All);`

### `Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputPlatformSettings.h` (Public)


#### class `UEnhancedInputPlatformData`  
`class UEnhancedInputPlatformData : public UObject`  
_L20-47_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable, ClassGroup = Input, meta = (Category = "EnhancedInput"))`
- inherits: `UObject`
- desc: A base class that can be used to store platform specific data for Enhanced Input. Make a subclass of this to add some additional options for per-platform settings
- L28 _public prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;`
- L34 _public prototype_ `const UInputMappingContext* GetContextRedirect(UInputMappingContext* InContext) const;` — `UFUNCTION(BlueprintCallable, Category = "EnhancedInput")` — Returns a pointer to the desired redirect mapping context. If there isn't one, then this returns InContext.
- L37 _public function_ `const TMap<TObjectPtr<const UInputMappingContext>, TObjectPtr<const UInputMappingContext>>& GetMappingContextRedirects() const` — Return the map of all Context Redirects in this platform data.
- L46 _protected member_ `TMap<TObjectPtr<const UInputMappingContext>, TObjectPtr<const UInputMappingContext>> MappingContextRedirects;` — `UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "EnhancedInput")` — Maps one Input Mapping Context to another. This can be used to replace specific Input Mapping Contexts with another on a per-platform basis.

#### class `UEnhancedInputPlatformSettings`  
`class UEnhancedInputPlatformSettings : public UPlatformSettings`  
_L51-95_
- reflection: `UCLASS(MinimalAPI, config = Input, defaultconfig)`
- inherits: `UPlatformSettings`
- desc: Settings for Enhanced Input that can be set per-platform
- L57 _public function_ `static UEnhancedInputPlatformSettings* Get()`
- L63 _public function_ `const TArray<TSoftClassPtr<UEnhancedInputPlatformData>>& GetInputData() const` — Get the current Enhanced Input platform data
- L66 _public prototype_ `void GetAllMappingContextRedirects(OUT TMap<TObjectPtr<const UInputMappingContext>, TObjectPtr<const UInputMappingContext>>& OutRedirects);` — Populates the given map with all mapping context redirects in the current platform's InputData.
- L69 _public prototype_ `void ForEachInputData(TFunctionRef<void(const UEnhancedInputPlatformData&)> Predicate);` — Iterates each valid UEnhancedInputPlatformData that is on this platform.
- L72 _public function_ `bool ShouldLogMappingContextRedirects() const` — Returns true if this platform has specified that it should log what mapping context redirects occur
- L78 _protected prototype_ `void LoadInputDataClasses();` — `UE_DEPRECATED(5.7, "LoadInputDataClasses is now deprecated")` — Load the input data subclasses and cache them for later use in the InputDataClasses array.
- L82 _protected member_ `TArray<TSoftClassPtr<UEnhancedInputPlatformData>> InputData;` — `UPROPERTY(config, EditAnywhere, Category = "Default")` — Input data that can be populated with Enhanced Input Platform Data blueprints
- L90 _protected member_ `TArray<TSubclassOf<UEnhancedInputPlatformData>> InputDataClasses;` — `UE_DEPRECATED(5.7, "InputDataClasses is now deprecated")` — `UPROPERTY(Transient)` — A transient array of the subclasses for the Enhanced Input Platform data. This will prevent us from from having to load the class' default object during game time.
- L94 _protected member_ `bool bShouldLogMappingContextRedirects = false;` — `UPROPERTY(Config, EditAnywhere, Category = "Default")` — If true, then Enhanced Input will log which mapping contexts have been redirected when building the control mappings.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ENHANCEDINPUT_API`

### `Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystemInterface.h` (Public)


#### class `UEnhancedInputSubsystemInterface`  
`class UEnhancedInputSubsystemInterface : public UInterface`  
_L29-32_
- reflection: `UINTERFACE(MinimalAPI, meta=(CannotImplementInterfaceInBlueprint, CannotGenerateMessageNodes=true))`
- inherits: `UInterface`
- desc: Subsystem interface

#### enum `EInputMappingRebuildType`  
`enum class EInputMappingRebuildType : uint8`  
_L35-43_
- reflection: `UENUM()`
- L38 _public enumerator_ `None` — No rebuild required.
- L40 _public enumerator_ `Rebuild` — Standard mapping rebuild. Retains existing triggers and modifiers for actions that were previously mapped.
- L42 _public enumerator_ `RebuildWithFlush` — If you have made changes to the triggers/modifiers associated with a UInputAction that was previously mapped a flush is required to reset the tracked data for that action.

#### struct `FModifyContextOptions`  
`struct FModifyContextOptions`  
_L47-100_
- reflection: `USTRUCT(BlueprintType)`
- desc: Passed in as params for Adding/Remove input contexts
- L51 _public function_ `FModifyContextOptions() : bIgnoreAllPressedKeysUntilRelease(true) , bForceImmediately(false) , bNotifyUserSettings(false)`
- L75 _public member_ `uint8 bIgnoreAllPressedKeysUntilRelease : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")` — If true, then any keys that are "down" or "pressed" during the rebuild of control mappings will not be processed by Enhanced Input until after they are "released". For example, if you are adding a mapping context with a key mapping to "X", and the player is holding down "X" while that IMC is added, there will not be a "Triggered" event until the player releases "X" and presses it again. If this is set to false for the above example, then the "Triggered" would fire immediately as soon as the IMC is finished being added. Default: True Note: This will only do something for keys bound to boolean Input Action types. Note: This includes all keys that the player has pressed, not just the keys that are previously mapped in Enhanced Input before the call to RebuildControlMappings.
- L87 _public member_ `uint8 bForceImmediately : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")` — The mapping changes will be applied synchronously, rather than at the end of the frame, making them available to the input system on the same frame. This is not recommended to be set to true if you are adding multiple mapping contexts as it will have poor performance. Default: False
- L99 _public member_ `uint8 bNotifyUserSettings : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")` — If true, then this Mapping Context will be registered or unregistered with the Enhanced Input User Settings on this subsystem, if they exist. Default: False Note: You need to enable and configure your UEnhancedInputUserSettings class in the project settings for this to do anything.

#### class `IEnhancedInputSubsystemInterface`  
`class IEnhancedInputSubsystemInterface`  
_L103-522_
- desc: Includes native functionality shared between all subsystems
- L111 _public prototype_ `virtual UEnhancedPlayerInput* GetPlayerInput() const = 0;`
- L114 _public prototype_ `virtual UEnhancedInputUserSettings* GetUserSettings() const;` — `UFUNCTION(BlueprintCallable, Category="Enhanced Input|User Settings", meta=(DisplayName="Get Enhanced Input User Settings"))`
- L119 _public prototype_ `static bool TrackingKeysForAllActionMappings();` — Getter for the CVar EnhancedInput.TrackKeysForAllActionMappings which enables Enhanced Input to respect Key consumption.
- L128 _protected prototype_ `virtual void InitalizeUserSettings();` — Create a new user settings object if it is enabled in the EI developer settings. Not every enhanced input subsystem needs user settings, so this is an optional feature.
- L131 _protected prototype_ `virtual void BindUserSettingDelegates();` — Binds to any delegates of interest on the UEnhancedInputUserSettings if they are enabled in the developer settings.
- L135 _protected prototype_ `virtual void OnUserSettingsChanged(UEnhancedInputUserSettings* Settings);` — `UFUNCTION()` — Callback for when any Enhanced Input user settings have been changed (a new key mapping for example)
- L139 _protected prototype_ `virtual void OnUserKeyProfileChanged(const UEnhancedPlayerMappableKeyProfile* InNewProfile);` — `UFUNCTION()` — A callback for when the user has applied a new mappable key profile.
- L153 _public prototype_ `virtual void InjectInputForAction(const UInputAction* Action, FInputActionValue RawValue, const TArray<UInputModifier*>& Modifiers, const TArray<UInputTrigger*>& Triggers);` — `UFUNCTION(BlueprintCallable, Category="Input", meta=(AutoCreateRefTerm="Modifiers,Triggers"))` — Input simulation via injection. Runs modifiers and triggers delegates as if the input had come through the underlying input system as FKeys. Applies action modifiers and triggers on top. @param Action		The Input Action to set inject input for @param RawValue		The value to set the action to @param Modifiers		The modifiers to apply to the injected input. @param Triggers		The triggers to apply to the injected input.
- L165 _public prototype_ `virtual void InjectInputVectorForAction(const UInputAction* Action, FVector Value, const TArray<UInputModifier*>& Modifiers, const TArray<UInputTrigger*>& Triggers);` — `UFUNCTION(BlueprintCallable, Category="Input", meta=(AutoCreateRefTerm="Modifiers,Triggers"))` — Input simulation via injection. Runs modifiers and triggers delegates as if the input had come through the underlying input system as FKeys. Applies action modifiers and triggers on top. @param Action		The Input Action to set inject input for @param Value			The value to set the action to (the type will be controlled by the Action) @param Modifiers		The modifiers to apply to the injected input. @param Triggers		The triggers to apply to the injected input.
- L177 _public prototype_ `virtual void InjectInputForPlayerMapping(UPARAM(Meta=(GetOptions="EnhancedInput.PlayerMappableKeySettings.GetKnownMappingNames")) const FName MappingName, FInputActionValue RawValue, const TArray<UInputMod` — `UFUNCTION(BlueprintCallable, Category="Input", meta=(AutoCreateRefTerm="Modifiers,Triggers"))` — Input simulation via injection. Runs modifiers and triggers delegates as if the input had come through the underlying input system as FKeys. Applies action modifiers and triggers on top. @param MappingName		The name of the player mapping that can be used for look up an associated UInputAction object. @param RawValue			The value to set the action to @param Modifiers			The modifiers to apply to the injected input. @param Triggers			The triggers to apply to the injected input.
- L189 _public prototype_ `virtual void InjectInputVectorForPlayerMapping(UPARAM(Meta=(GetOptions="EnhancedInput.PlayerMappableKeySettings.GetKnownMappingNames")) const FName MappingName, FVector Value, const TArray<UInputMod` — `UFUNCTION(BlueprintCallable, Category="Input", meta=(AutoCreateRefTerm="Modifiers,Triggers"))` — Input simulation via injection. Runs modifiers and triggers delegates as if the input had come through the underlying input system as FKeys. Applies action modifiers and triggers on top. @param MappingName		The name of the player mapping that can be used for look up an associated UInputAction object. @param Value				The value to set the action to (the type will be controlled by the Action) @param Modifiers			The modifiers to apply to the injected input. @param Triggers			The triggers to apply to the injected input.
- L200 _public prototype_ `virtual void StartContinuousInputInjectionForAction(const UInputAction* Action, FInputActionValue RawValue, const TArray<UInputModifier*>& Modifiers, const TArray<UInputTrigger*>& Triggers);` — `UFUNCTION(BlueprintCallable, Category="Input", meta=(AutoCreateRefTerm="Modifiers,Triggers"))` — Starts simulation of input via injection. This injects the given input every tick until it is stopped with StopContinuousInputInjectionForAction. @param Action		The Input Action to set inject input for @param RawValue		The value to set the action to (the type will be controlled by the Action) @param Modifiers		The modifiers to apply to the injected input. @param Triggers		The triggers to apply to the injected input.
- L211 _public prototype_ `virtual void StartContinuousInputInjectionForPlayerMapping(UPARAM(Meta=(GetOptions="EnhancedInput.PlayerMappableKeySettings.GetKnownMappingNames")) const FName MappingName, FInputActionValue RawValue, const TArray<UInputMod` — `UFUNCTION(BlueprintCallable, Category="Input", meta=(AutoCreateRefTerm="Modifiers,Triggers"))` — Starts simulation of input via injection. This injects the given input every tick until it is stopped with StopContinuousInputInjectionForAction. @param MappingName		The name of the player mapping that can be used for look up an associated UInputAction object. @param RawValue			The value to set the action to (the type will be controlled by the Action) @param Modifiers			The modifiers to apply to the injected input. @param Triggers			The triggers to apply to the injected input.
- L220 _public prototype_ `virtual void UpdateValueOfContinuousInputInjectionForAction(const UInputAction* Action, FInputActionValue RawValue);` — `UFUNCTION(BlueprintCallable, Category="Input")` — Update the value of a continuous input injection, preserving the state of triggers and modifiers. @param Action	The Input Action to set inject input for @param RawValue	The value to set the action to (the type will be controlled by the Action)
- L229 _public prototype_ `virtual void UpdateValueOfContinuousInputInjectionForPlayerMapping(UPARAM(Meta=(GetOptions="EnhancedInput.PlayerMappableKeySettings.GetKnownMappingNa` — `UFUNCTION(BlueprintCallable, Category="Input")` — Update the value of a continuous input injection for the given player mapping name, preserving the state of triggers and modifiers. @param MappingName	The name of the player mapping that can be used for look up an associated UInputAction object. @param RawValue		The value to set the action to (the type will be controlled by the Action)
- L237 _public prototype_ `virtual void StopContinuousInputInjectionForAction(const UInputAction* Action);` — `UFUNCTION(BlueprintCallable, Category="Input")` — Stops continuous input injection for the given action. @param Action		The action to stop injecting input for
- L245 _public prototype_ `virtual void StopContinuousInputInjectionForPlayerMapping(UPARAM(Meta=(GetOptions="EnhancedInput.PlayerMappableK` — `UFUNCTION(BlueprintCallable, Category="Input")` — Stops continuous input injection for the given player mapping name. @param MappingName		The name of the player mapping that can be used for look up an associated UInputAction object.
- L250 _public prototype_ `bool HasContinuousInputInjectionForAction(const UInputAction* Action) const;` — Determines if there is a continuous input injection for the given action.
- L256 _public prototype_ `virtual void ClearAllMappings();` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Input")` — Remove all applied mapping contexts.
- L265 _public prototype_ `virtual void AddMappingContext(const UInputMappingContext* MappingContext, int32 Priority, const FModifyContextOptions& Options = FModifyContextOptions());` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Input", meta=(AutoCreateRefTerm = "Options"))` — Add a control mapping context. @param MappingContext		A set of key to action mappings to apply to this player @param Priority				Higher priority mappings will be applied first and, if they consume input, will block lower priority mappings. @param Options				Options to consider when adding this mapping context.
- L274 _public prototype_ `virtual void RemoveMappingContext(const UInputMappingContext* MappingContext, const FModifyContextOptions& Options = FModifyContextOptions());` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Input", meta=(AutoCreateRefTerm = "Options"))` — Remove a specific control context. This is safe to call even if the context is not applied. @param MappingContext		Context to remove from the player @param Options			Options to consider when removing this input mapping context
- L282 _public prototype_ `virtual FGameplayTagContainer GetInputMode() const;` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Input")` — Returns the current input mode set on Enhanced Input. This mode will control what mappings are currently being processed by the player. If the Input Mapping Context's InputModeQuery is not empty and does not match this tag container, then it's mappings will not be processed.
- L291 _public prototype_ `virtual void SetInputMode(const FGameplayTagContainer& NewMode, const FModifyContextOptions& Options = FModifyContextOptions());` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Input", meta=(AutoCreateRefTerm = "Options", AdvancedDisplay = "Options"))` — Sets the current input mode on the player and triggers a rebuild of control mappings. @param NewMode The new input mode tag container to use @param Options Options for how to treat the control mappings rebuild.
- L300 _public prototype_ `virtual void AppendTagsToInputMode(const FGameplayTagContainer& TagsToAdd, const FModifyContextOptions& Options = FModifyContextOptions());` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Input", meta=(AutoCreateRefTerm = "Options", AdvancedDisplay = "Options"))` — Appends the given "TagsToAdd" to the current input mode tag container and triggers a rebuild of control mappings. @param TagsToAdd	The gameplay tag container to append @param Options	Options for how to treat the control mappings rebuild
- L309 _public prototype_ `virtual void AddTagToInputMode(const FGameplayTag& TagToAdd, const FModifyContextOptions& Options = FModifyContextOptions());` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Input", meta=(AutoCreateRefTerm = "Options", AdvancedDisplay = "Options"))` — Adds the given "TagToAdd" to the current input mode tag container and triggers a rebuild of control mappings. @param TagToAdd	The gameplay tag to add to the current input mode tag container @param Options	Options for how to treat the control mappings rebuild
- L318 _public prototype_ `virtual void RemoveTagsFromInputMode(const FGameplayTagContainer& TagsToRemove, const FModifyContextOptions& Options = FModifyContextOptions());` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Input", meta=(AutoCreateRefTerm = "Options", AdvancedDisplay = "Options"))` — Removes tags from the current input mode and triggers a rebuild of control mappings. @param TagsToRemove Tags to remove from the current input mode tag container @param Options		Options for how to treat the control mappings rebuild
- L327 _public prototype_ `virtual void RemoveTagFromInputMode(const FGameplayTag& TagToRemove, const FModifyContextOptions& Options = FModifyContextOptions());` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Input", meta=(AutoCreateRefTerm = "Options", AdvancedDisplay = "Options"))` — Removes the given tag from the current input mode and triggers a rebuild of control mappings. @param TagToRemove	The tag to remove from the current input mode @param Options		Options for how to treat the control mappings rebuild
- L336 _public prototype_ `virtual void RequestRebuildControlMappings(const FModifyContextOptions& Options = FModifyContextOptions(), EInputMappingRebuildType RebuildType = EInputMappingRebuildType::Rebuild);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Input", meta=(AutoCreateRefTerm = "Options"))` — Flag player for reapplication of all mapping contexts at the end of this frame. This is called automatically when adding or removing mappings contexts. @param Options		Options to consider when removing this input mapping context
- L349 _public prototype_ `virtual EMappingQueryResult QueryMapKeyInActiveContextSet(const UInputMappingContext* InputContext, const UInputAction* Action, FKey Key, TArray<FMappingQueryIssue>& OutIssues, EMappingQueryIssue BlockingIssues );` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Input|Mapping Queries")` — Check if a key mapping is safe to add to a given mapping context within the set of active contexts currently applied to the player controller. @param InputContext		Mapping context to which the action/key mapping is intended to be added @param Action			Action that can be triggered by the key @param Key				Key that will provide input values towards triggering the action @param OutIssues			Issues that may cause this mapping to be invalid (at your discretion). Any potential issues will be recorded, even if not present in FatalIssues. @param BlockingIssues	All issues that should be considered fatal as a bitset. @return					Summary of resulting issues. @see QueryMapKeyInContextSet
- L363 _public prototype_ `virtual EMappingQueryResult QueryMapKeyInContextSet(const TArray<UInputMappingContext*>& PrioritizedActiveContexts, const UInputMappingContext* InputContext, const UInputAction* Action, FKey Key, TArray<FMappingQueryIssue>& OutIssues, EMappingQueryIssue BlockingIssues );` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Input|Mapping Queries")` — Check if a key mapping is safe to add to a collection of mapping contexts @param PrioritizedActiveContexts	Set of mapping contexts to test against ordered by priority such that earlier entries take precedence over later ones. @param InputContext		Mapping context to which the action/key mapping is intended to be applied. NOTE: This context must be present in PrioritizedActiveContexts. @param Action			Action that is triggered by the key @param Key				Key that will provide input values towards triggering the action @param OutIssues			Issues that may cause this mapping to be invalid (at your discretion). Any potential issues will be recorded, even if not present in FatalIssues. @param BlockingIssues	All issues that should be considered fatal as a bitset. @return					Summary of resulting issues. @see QueryMapKeyInActiveContextSet
- L368 _public prototype_ `virtual bool HasMappingContext(const UInputMappingContext* MappingContext) const;` — Check if a mapping context is applied to this subsystem's owner.
- L378 _public prototype_ `virtual bool HasMappingContext(const UInputMappingContext* MappingContext, int32& OutFoundPriority) const;` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Input|Mapping Queries")` — Check if a mapping context is applied to this subsystem's owner. @param MappingContext		The mapping context to search for on the subsystem's owner. @param OutFoundPriority		The priority of the mapping context if it is applied. -1 if the context is not applied @return	True if the mapping context is applied
- L384 _public prototype_ `virtual TArray<FKey> QueryKeysMappedToAction(const UInputAction* Action) const;` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Input|Mapping Queries")` — Returns the keys mapped to the given action in the active input mapping contexts.
- L390 _public prototype_ `virtual TArray<FEnhancedActionKeyMapping> GetAllPlayerMappableActionKeyMappings() const;` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Input|Mapping Queries")` — Get an array of the currently applied key mappings that are marked as Player Mappable.
- L393 _public prototype_ `void ValidateTrackedMappingContextsAreUnregistered() const;` — Logs warnings for any currently applied Input Mapping Contexts that have a tracked RegistrationTrackingMode to detect leaks
- L401 _protected prototype_ `void TickForcedInput(float DeltaTime);` — Ticks any forced/injected input to the subsystem's player input. If you want support for ApplyForcedInput in a subsytem implementing this interface, then you must call this function.
- L411 _protected prototype_ `void HandleControlMappingRebuildDelegate();` — Called each tick from the Enhanced Input module. If bControlMappingsRebuiltThisTick is true this tick, then call the ControlMappingsRebuiltThisFrame function and reset the bControlMappingsRebuiltThisTick flag to false. This gives an implementor of this interface an oppurtunity to add in a nice blueprint useable delegate.
- L414 _protected function_ `virtual void ControlMappingsRebuiltThisFrame()` — Function that will be called when Control Mappings have been rebuilt this tick.
- L417 _protected prototype_ `void ShowMappingContextDebugInfo(UCanvas* Canvas, const UEnhancedPlayerInput* PlayerInput);` — helper function to display debug about mapping context info
- L424 _protected prototype_ `virtual TMap<TObjectPtr<const UInputAction>, FInjectedInput>& GetContinuouslyInjectedInputs() = 0;` — Pure-virtual getter for the map of inputs that should be injected every frame. These inputs will be injected when ForcedInput is ticked. Any classes that implement this interface should have this function return a managed map to avoid GC and unreachibility issues.
- L429 _private prototype_ `void ApplyForcedInput(const UInputAction* Action, FInputActionValue Value);` — Forced actions/keys for debug. These will be applied each tick once set even if zeroed, until removed.
- L430 _private prototype_ `void ApplyForcedInput(FKey Key, FInputActionValue Value);`
- L431 _private prototype_ `void RemoveForcedInput(const UInputAction* Action);`
- L432 _private prototype_ `void RemoveForcedInput(FKey Key);`
- L434 _private prototype_ `void InjectChordBlockers(const TArray<int32>& ChordedMappings);`
- L435 _private prototype_ `bool HasTriggerWith(TFunctionRef<bool(const class UInputTrigger*)> TestFn, const TArray<class UInputTrigger*>& Triggers);`
- L443 _private prototype_ `TArray<FEnhancedActionKeyMapping> ReorderMappings(const TArray<FEnhancedActionKeyMapping>& UnorderedMappings, TArray<UEnhancedPlayerInput::FDependentChordTracker>& OUT DependentChordActions);` — Reorder the given UnordedMappings such that chording mappings > chorded mappings > everything else. This is used to ensure mappings within a single context are evaluated in the correct order to support chording. Populate the DependentChordActions array with any chorded triggers so that we can detect which ones should be triggered later.
- L448 _private prototype_ `void RebuildControlMappings();` — Reapply all control mappings to players pending a rebuild
- L451 _private prototype_ `void ApplyAxisPropertyModifiers(UEnhancedPlayerInput* PlayerInput, struct FEnhancedActionKeyMapping& Mapping) const;` — Convert input settings axis config to modifiers for a given mapping
- L453 _private member_ `TMap<TWeakObjectPtr<const UInputAction>, FInputActionValue> ForcedActions;`
- L482 _private member_ `TMap<FKey, FInjectedKeyData> ForcedKeys;` — Map of FKey's to any input data that we are injecting to the player right now.
- L488 _private member_ `TMap<TObjectPtr<const UInputAction>, TObjectPtr<const UInputAction>> ChordedActionDependencies;` — A map of input actions with a Chorded trigger, mapped to the action they are dependent on. The Key is the Input Action with the Chorded Trigger, and the value is the action it is dependant on.
- L494 _private member_ `TMap<TObjectPtr<const UInputMappingContext>, TObjectPtr<const UInputMappingContext>> AppliedContextRedirects;` — A map of the currently applied mapping context redirects. This is populated in RebuildControlMappings with any InputMappingContexts that have been redirected on this local player from the platform settings.
- L496 _private member_ `EInputMappingRebuildType MappingRebuildPending = EInputMappingRebuildType::None;`
- L504 _private member_ `bool bIgnoreAllPressedKeysUntilReleaseOnRebuild = true;` — A flag that will be set when adding/removing a mapping context. If this is true, then any keys that are pressed when control mappings are rebuilt will be ignored by the new Input context after being until the key is lifted
- L506 _private member_ `bool bMappingRebuildPending = false;`
- L512 _private member_ `bool bControlMappingsRebuiltThisTick = false;` — If true then the control mappings have been rebuilt on this frame. This is reset to false every tick in the EnhancedInputModule
- L515 _private prototype_ `virtual void ShowDebugInfo(UCanvas* Canvas);` — Debug visualization for enhanced input local player subsystem
- L518 _private prototype_ `static void GetAllRelevantInputModifiersForDebug(const UEnhancedPlayerInput* PlayerInput, const FInputActionInstance* InstanceData, OUT TArray<UInputModifier*>& OutModifiers);` — Gather any UInputModifiers on the given Player Input and Instance data that need to be visualized for debugging
- L520 _private prototype_ `void ShowDebugActionModifiers(UCanvas* Canvas, const UInputAction* Action);`
- L521 _private prototype_ `static void PurgeDebugVisualizations();`

#### struct `IEnhancedInputSubsystemInterface::FInjectedKeyData`  
`struct FInjectedKeyData`  
_L458-477_
- desc: Data storing the state of input values we inject for specific FKeys
- L460 _public prototype_ `FInjectedKeyData() = default;`
- L462 _public function_ `FInjectedKeyData(const FInputActionValue& Value) : InputValue(Value) , LastInjectedValue(FInputActionValue(FVector::ZeroVector))`
- L470 _public member_ `FInputActionValue InputValue = FInputActionValue(FVector::ZeroVector);` — The desired input action value to inject when we tick.
- L476 _public member_ `FInputActionValue LastInjectedValue = FInputActionValue(FVector::ZeroVector);` — The last input value which was injected for this key. This is set on tick after we have injected the input for this key at least once.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ENHANCEDINPUT_API`

### `Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h` (Public)


#### class `UEnhancedInputLocalPlayerSubsystem`  
`class UEnhancedInputLocalPlayerSubsystem : public ULocalPlayerSubsystem, public IEnhancedInputSubsystemInterface`  
_L21-97_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `ULocalPlayerSubsystem,IEnhancedInputSubsystemInterface`
- desc: Per local player input subsystem
- L28 _public prototype_ `virtual void Deinitialize() override;`
- L29 _public prototype_ `virtual void PlayerControllerChanged(APlayerController* NewPlayerController) override;`
- L33 _public prototype_ `virtual UEnhancedPlayerInput* GetPlayerInput() const override;`
- L34 _public prototype_ `virtual UEnhancedInputUserSettings* GetUserSettings() const override;`
- L35 _public prototype_ `virtual void InitalizeUserSettings() override;`
- L36 _public prototype_ `virtual void ControlMappingsRebuiltThisFrame() override;`
- L37 _public prototype_ `virtual void AddMappingContext(const UInputMappingContext* MappingContext, int32 Priority, const FModifyContextOptions& Options = FModifyContextOptions()) override;`
- L38 _public prototype_ `virtual void RemoveMappingContext(const UInputMappingContext* MappingContext, const FModifyContextOptions& Options = FModifyContextOptions()) override;`
- L40 _protected function_ `virtual TMap<TObjectPtr<const UInputAction>, FInjectedInput>& GetContinuouslyInjectedInputs() override`
- L46 _public function_ `template<class UserSettingClass = UEnhancedInputUserSettings> inline UserSettingClass* GetUserSettings() const`
- L52 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnControlMappingsRebuilt);` — A delegate that will be called when control mappings have been rebuilt this frame.
- L53 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMappingContextAdded, const UInputMappingContext*, MappingContext);`
- L54 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMappingContextRemoved, const UInputMappingContext*, MappingContext);`
- L55 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUserSettingsPostInitialized, const UEnhancedInputUserSettings*, Settings);`
- L61 _public member_ `FOnControlMappingsRebuilt ControlMappingsRebuiltDelegate;` — `UPROPERTY(BlueprintAssignable, DisplayName=OnControlMappingsRebuilt, Category = "Input")` — Blueprint Event that is called at the end of any frame that Control Mappings have been rebuilt.
- L70 _public member_ `FOnMappingContextAdded OnMappingContextAdded;` — `UPROPERTY(BlueprintAssignable, Category = "Input")` — A callback fired when a mapping context is added (AddMappingContext is called on this subsystem) Note:  This does not make any guarantee that the control mappings will have been rebuilt. If you need that, then listen to the ControlMappingsRebuiltDelegate instead.
- L79 _public member_ `FOnMappingContextRemoved OnMappingContextRemoved;` — `UPROPERTY(BlueprintAssignable, Category = "Input")` — A callback fired when a mapping context is removed (RemoveMappingContext is called on this subsystem) Note:  This does not make any guarantee that the control mappings will have been rebuilt. If you need that, then listen to the ControlMappingsRebuiltDelegate instead.
- L85 _public member_ `FOnUserSettingsPostInitialized OnPostUserSettingsInitialized;` — `UPROPERTY(BlueprintAssignable, Category = "Input")` — Delegate that is fired after this local player's User Settings object has been created and loaded for the first time.
- L91 _protected member_ `TObjectPtr<UEnhancedInputUserSettings> UserSettings;` — `UPROPERTY()` — The user settings for this subsystem used to store each user's input related settings
- L95 _protected member_ `TMap<TObjectPtr<const UInputAction>, FInjectedInput> ContinuouslyInjectedInputs;` — `UPROPERTY(Transient)` — Map of inputs that should be injected every frame. These inputs will be injected when ForcedInput is ticked.

#### class `UEnhancedInputWorldSubsystem`  
`class UEnhancedInputWorldSubsystem : public UWorldSubsystem, public IEnhancedInputSubsystemInterface`  
_L108-187_
- reflection: `UCLASS(MinimalAPI, DisplayName="Enhanced Input World Subsystem (Experimental)")`
- inherits: `UWorldSubsystem,IEnhancedInputSubsystemInterface`
- desc: Per world input subsystem that allows you to bind input delegates to actors without an owning Player Controller. This should be used when an actor needs to receive input delegates but will never have an owning Player Controller. For example, you can add input delegates to unlock a door when the user has a certain set of keys pressed. Be sure to enable input on the actor, or else the input delegates won't fire! Note: if you do have an actor with an owning Player Controller use the local player input subsystem instead.
- L121 _public prototype_ `virtual bool ShouldCreateSubsystem(UObject* Outer) const override;`
- L122 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L123 _public prototype_ `virtual void Deinitialize() override;`
- L125 _protected prototype_ `virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const;`
- L130 _public prototype_ `virtual UEnhancedPlayerInput* GetPlayerInput() const override;`
- L131 _public prototype_ `virtual void ShowDebugInfo(UCanvas* Canvas) override;`
- L133 _protected function_ `virtual TMap<TObjectPtr<const UInputAction>, FInjectedInput>& GetContinuouslyInjectedInputs() override`
- L139 _public prototype_ `void AddActorInputComponent(AActor* Actor);` — `UFUNCTION(BlueprintCallable, Category = "Input|World", meta=(DefaultToSelf = "Actor"))` — Adds this Actor's input component onto the stack to be processed by this subsystem's tick function
- L143 _public prototype_ `bool RemoveActorInputComponent(AActor* Actor);` — `UFUNCTION(BlueprintCallable, Category = "Input|World", meta = (DefaultToSelf = "Actor"))` — Removes this Actor's input component from the stack to be processed by this subsystem's tick function
- L152 _protected prototype_ `bool InputKey(const FInputKeyEventArgs& Params);` — Inputs a key on this subsystem's player input which can then be processed as normal during Tick. This should only be called by the FEnhancedInputWorldProcessor
- L163 _protected prototype_ `void TickPlayerInput(float DeltaTime);` — Builds the current input stack and ticks the world subsystem's player input. Called from the Enhanced Input Module Tick. The Enhanced Input local player subsystem will have their Player Input's ticked by their owning Player Controller in APlayerController::TickPlayerInput, but because the world subsystem has no owning controller we need to tick it elsewhere.
- L166 _protected prototype_ `void AddDefaultMappingContexts();` — Adds all the default mapping contexts
- L169 _protected prototype_ `void RemoveDefaultMappingContexts();` — Removes all the default mapping contexts
- L173 _protected member_ `TObjectPtr<UEnhancedPlayerInput> PlayerInput = nullptr;` — `UPROPERTY()` — The player input that is processing the input within this subsystem
- L178 _protected member_ `TSharedPtr<FEnhancedInputWorldProcessor> InputPreprocessor = nullptr;` — Input processor that is created on Initalize.
- L182 _protected member_ `TArray<TWeakObjectPtr<UInputComponent>> CurrentInputStack;` — `UPROPERTY(Transient)` — Internal. This is the current stack of InputComponents that is being processed by the PlayerInput.
- L186 _protected member_ `TMap<TObjectPtr<const UInputAction>, FInjectedInput> ContinuouslyInjectedInputs;` — `UPROPERTY(Transient)` — Map of inputs that should be injected every frame. These inputs will be injected when ForcedInput is ticked.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API ENHANCEDINPUT_API`
- L17 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogWorldSubsystemInput, Log, All);`
- L17 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogWorldSubsystemInput, Log, All);`
- L52 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnControlMappingsRebuilt);` — A delegate that will be called when control mappings have been rebuilt this frame.
- L53 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMappingContextAdded, const UInputMappingContext*, MappingContext);`
- L54 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMappingContextRemoved, const UInputMappingContext*, MappingContext);`
- L55 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUserSettingsPostInitialized, const UEnhancedInputUserSettings*, Settings);`

### `Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputWorldProcessor.h` (Public)


#### class `FEnhancedInputWorldProcessor`  
`class FEnhancedInputWorldProcessor : public IInputProcessor`  
_L18-52_
- inherits: `IInputProcessor`
- desc: The Enhanced Input World Processor is used to pass InputKey events to the Enhanced Input World Subsystem. It will not steal input, and all the functions here will return "False" so that other Input Processors still run with all their normal considerations.
- L22 _public prototype_ `virtual void Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor) override;`
- L23 _public prototype_ `virtual bool HandleKeyDownEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent) override;`
- L24 _public prototype_ `virtual bool HandleKeyUpEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent) override;`
- L25 _public prototype_ `virtual bool HandleAnalogInputEvent(FSlateApplication& SlateApp, const FAnalogInputEvent& InAnalogInputEvent) override;`
- L26 _public prototype_ `virtual bool HandleMouseMoveEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent) override;`
- L27 _public prototype_ `virtual bool HandleMouseButtonDownEvent( FSlateApplication& SlateApp, const FPointerEvent& MouseEvent) override;`
- L28 _public prototype_ `virtual bool HandleMouseButtonUpEvent( FSlateApplication& SlateApp, const FPointerEvent& MouseEvent) override;`
- L29 _public prototype_ `virtual bool HandleMouseButtonDoubleClickEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent) override;`
- L30 _public prototype_ `virtual bool HandleMouseWheelOrGestureEvent(FSlateApplication& SlateApp, const FPointerEvent& InWheelEvent, const FPointerEvent* InGestureEvent) override;`
- L31 _public function_ `virtual const TCHAR* GetDebugName() const`
- L36 _protected prototype_ `void UpdateCachedPointerPosition(const FPointerEvent& MouseEvent);`
- L39 _protected prototype_ `void ProcessAccumulatedPointerInput(float DeltaTime);` — Called on Tick to process any accumulated mouse input
- L42 _protected prototype_ `bool InputKeyToSubsystem(const struct FInputKeyEventArgs& Params);` — Tells the Enhanced Input World subsystem about the given key event
- L48 _protected member_ `FIntPoint NumCursorSamplesThisFrame = FIntPoint::ZeroValue;` — The number of cursor samples that happened this frame. The X and Y will be incremented when there is a mouse move event this frame and it will be reset on ProcessAccumulatedPointerInput.
- L51 _protected member_ `FVector2D CachedCursorDelta = FVector2D::ZeroVector;` — The value of the mouse cursor from the most recent mouse event

### `Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedPlayerInput.h` (Public)


#### struct `FInjectedInput`  
`struct FInjectedInput`  
_L41-51_
- reflection: `USTRUCT()`
- desc: ContinuouslyInjectedInputs Map is not managed. Continuous input injections seem to be getting garbage collected and crashing in UObject::ProcessEvent when calling ModifyRaw. Band-aid fix: Making these managed references. Also check modifications to IEnhancedInputSubsystemInterface::Start/StopContinuousInputInjectionForAction.
- L45 _public member_ `FInputActionValue RawValue;`
- L48 _public member_ `TArray<TObjectPtr<UInputTrigger>> Triggers;` — `UPROPERTY(Transient)`
- L50 _public member_ `TArray<TObjectPtr<UInputModifier>> Modifiers;` — `UPROPERTY(Transient)`

#### struct `FKeyConsumptionOptions`  
`struct FKeyConsumptionOptions`  
_L54-63_
- reflection: `USTRUCT()`
- L59 _public member_ `TArray<FKey> KeysToConsume;` — Keys that should be consumed if the trigger state is reached
- L62 _public member_ `ETriggerEvent EventsToCauseConsumption = ETriggerEvent::None;` — A bitmask of trigger events that when reached, should cause the key to be marked as consumed.

#### struct `FInjectedInputArray`  
`struct FInjectedInputArray`  
_L66-72_
- reflection: `USTRUCT()`
- L71 _public member_ `TArray<FInjectedInput> Injected;` — `UPROPERTY(Transient)`

#### struct `FAppliedInputContextData`  
`struct FAppliedInputContextData`  
_L75-88_
- reflection: `USTRUCT()`
- L80 _public member_ `int32 Priority = 0;` — `UPROPERTY()`
- L87 _public member_ `int32 RegistrationCount = 0;` — `UPROPERTY()` — Used when RegistrationTrackingMode is set to CountRegistrations This is how many times the IMC has been added minus how many times it has been removed. The IMC is unregistered when this hits 0.

#### class `UEnhancedPlayerInput`  
`class UEnhancedPlayerInput : public UPlayerInput`  
_L94-331_
- reflection: `UCLASS(MinimalAPI, config = Input, transient)`
- inherits: `UPlayerInput`
- desc: UEnhancedPlayerInput : UPlayerInput extensions for enhanced player input system
- L104 _public prototype_ `UEnhancedPlayerInput();`
- L107 _public prototype_ `virtual void FlushPressedKeys() override;`
- L113 _public function_ `const FInputActionInstance* FindActionInstanceData(TObjectPtr<const UInputAction> ForAction) const` — Returns the action instance data for the given input action if there is any. Returns nullptr if the action is not available.
- L118 _public prototype_ `FInputActionValue GetActionValue(TObjectPtr<const UInputAction> ForAction) const;` — Retrieve the current value of an action for this player. Note: If the action is not currently triggering this will return a zero value of the appropriate value type, ignoring any ongoing inputs.
- L121 _public prototype_ `void InjectInputForAction(TObjectPtr<const UInputAction> Action, FInputActionValue RawValue, const TArray<UInputModifier*>& Modifiers = {}, const TArray<UInputTrigger*>& Triggers = {});` — Input simulation via injection. Runs modifiers and triggers delegates as if the input had come through the underlying input system as FKeys. Applies action modifiers and triggers on top.
- L123 _public prototype_ `virtual bool InputKey(const FInputKeyEventArgs& Params) override;`
- L126 _public prototype_ `float GetEffectiveTimeDilation() const;` — Returns the Time Dilation value that is currently effecting this input.
- L131 _public prototype_ `const FGameplayTagContainer& GetCurrentInputMode() const;` — Returns a const ref to the current input mode.
- L137 _public prototype_ `virtual FString GetUserSettingsSaveFileName() const;` — @return The name which should be used to save the input settings to. By default, this will return InputSettingsSaveSlotName from the developer settings.
- L146 _public prototype_ `TConstArrayView<const FEnhancedActionKeyMapping> GetEnhancedActionMappingsView() const;` — Returns a const array view of the current enhanced input action mappings. Note: Do NOT hold onto any references to these mappings or their input triggers/modifiers, as they will get re-instanced every time the control mappings are rebuilt. This is for read-only access to view the current mappings which may be useful for systems which want to query specific data about the current trigger states of specific mappings.
- L155 _protected prototype_ `void SetCurrentInputMode(const FGameplayTagContainer& NewMode);` — Sets the current input mode to be the given NewMode. This should only be called by the Enhanced Input subsystem interface, and followed up by a call to RequestRebuildControlMappings.
- L162 _protected prototype_ `FGameplayTagContainer& GetCurrentInputMode();` — Returns a mutable reference to the current input mode This should only be called by the Enhanced Input subsystem interface, and followed up by a call to RequestRebuildControlMappings.
- L164 _protected prototype_ `virtual void EvaluateKeyMapState(const float DeltaTime, const bool bGamePaused, OUT TArray<TPair<FKey, FKeyState*>>& KeysWithEvents) override;`
- L165 _protected prototype_ `virtual void EvaluateInputDelegates(const TArray<UInputComponent*>& InputComponentStack, const float DeltaTime, const bool bGamePaused, const TArray<TPair<FKey, FKeyState*>>& KeysWithEvents) override;`
- L166 _protected prototype_ `virtual void PrepareInputDelegatesForEvaluation(const TArray<UInputComponent*>& InputComponentStack, const float DeltaTime, const bool bGamePaused, const TArray<TPair<FKey, FKeyState*>>& KeysWithEvents) override;`
- L167 _protected prototype_ `virtual bool EvaluateInputComponentDelegates(UInputComponent* const IC, const TArray<TPair<FKey, FKeyState*>>& KeysWithEvents, const float DeltaTime, const bool bGamePaused) override;`
- L168 _protected prototype_ `virtual void EvaluateBlockedInputComponent(UInputComponent* InputComponent) override;`
- L171 _protected prototype_ `virtual bool IsKeyHandledByAction(FKey Key) const override;` — Causes key to be consumed if it is affecting an action.
- L174 _protected function_ `const TMap<TObjectPtr<const UInputMappingContext>, FAppliedInputContextData>& GetAppliedInputContextData() const` — Note: Source reference only. Use GetEnhancedActionMappings() for the actual mappings (with properly instanced triggers/modifiers)
- L176 _protected function_ `const TMap<TObjectPtr<const UInputMappingContext>, int32>& GetAppliedInputContexts() const` — `UE_DEPRECATED(5.6, "GetAppliedInputContexts() is deprecated, use GetAppliedInputContextData() instead")`
- L184 _protected function_ `const TArray<FEnhancedActionKeyMapping>& GetEnhancedActionMappings() const` — This player's version of the Action Mappings
- L189 _protected prototype_ `void NotifyInputActionsUnmapped(const TSet<const UInputAction*>& RemovedInputActions);` — Notifies that the given Input Actions are no longer mapped to any keys, and should have their state reset.
- L193 _protected member_ `TMap<TObjectPtr<const UInputAction>, FKeyConsumptionOptions> KeyConsumptionData;` — `UPROPERTY()` — Array of data that represents what keys should be consumed if an enhanced input action is in a specific triggered state
- L197 _protected member_ `mutable TMap<TObjectPtr<const UInputAction>, FInputActionInstance> ActionInstanceData;` — `UPROPERTY(Transient)` — Tracked action values. Queryable.
- L204 _protected member_ `TSet<TObjectPtr<const UInputAction>> ConsumedInputActions;` — `UPROPERTY(Transient)` — Set of consumed input actions this frame. Populated during the evaluation of input delegates and cleared at the end of the evaluation
- L211 _private prototype_ `int32 AddMapping(const FEnhancedActionKeyMapping& Mapping);` — Add a player specific action mapping. Returns index into EnhancedActionMappings array.
- L212 _private prototype_ `void ClearAllMappings();`
- L214 _private prototype_ `virtual void ConditionalBuildKeyMappings_Internal() const override;`
- L217 _private prototype_ `void InitializeMappingActionModifiers(const FEnhancedActionKeyMapping& Mapping);` — Perform a first pass run of modifiers on an action instance
- L219 _private prototype_ `FInputActionValue ApplyModifiers(const TArray<UInputModifier*>& Modifiers, FInputActionValue RawValue, float DeltaTime) const;` — Pre-modified (raw) value
- L220 _private prototype_ `ETriggerEventInternal GetTriggerStateChangeEvent(ETriggerState LastTriggerState, ETriggerState NewTriggerState) const;`
- L221 _private prototype_ `ETriggerEvent ConvertInternalTriggerEvent(ETriggerEventInternal Event) const;` — Collapse a detailed internal trigger event into a friendly representation
- L223 _private prototype_ `void ProcessActionMappingEvent( TObjectPtr<const UInputAction> Action, float DeltaTime, bool bGamePaused, FInputActionValue RawValue, EKeyEvent KeyEvent, const TArray<UInputModifier*>& Modifiers, const TArray<UInputTrigger*>& Triggers, const bool bHasAlwaysTickTrigger = false);`
- L233 _private prototype_ `FInputActionInstance& FindOrAddActionEventData(TObjectPtr<const UInputAction> Action) const;`
- L236 _private prototype_ `template<typename T> void GatherActionEventDataForActionMap(const T& ActionMap, TMap<TObjectPtr<const UInputAction>, FInputActionInstance>& FoundActionEventData) const;`
- L246 _private member_ `TMap<TObjectPtr<const UInputMappingContext>, FAppliedInputContextData> AppliedInputContextData;` — `UPROPERTY(Transient)` — Currently applied key mappings Note: Source reference only. Use EnhancedActionMappings for the actual mappings (with properly instanced triggers/modifiers) These mapping contexts will only have their mappings processed if the current input mode matches the query set on them.
- L249 _private member_ `TMap<TObjectPtr<const UInputMappingContext>, int32> AppliedInputContexts;` — `UE_DEPRECATED(5.6, "AppliedInputContexts is deprecated, use AppliedInputContextData instead")` — `UPROPERTY(Transient)`
- L253 _private member_ `TArray<FEnhancedActionKeyMapping> EnhancedActionMappings;` — `UPROPERTY(Transient)` — This player's version of the Action Mappings
- L260 _private member_ `FGameplayTagContainer CurrentInputMode;` — `UPROPERTY(Transient)` — The current input mode that is active on this player. If Input Mapping contexts have requirements which this container does not meet, then their mappings will not be applied.
- L263 _private member_ `TMap<FKey, int32> EnhancedKeyBinds;` — Number of active binds by key
- L266 _private member_ `TSet<TObjectPtr<const UInputAction>> ActionsWithEventsThisTick;` — Actions which had actuated events at the last call to ProcessInputStack (held/pressed/released)
- L269 _private member_ `TSet<TObjectPtr<const UInputAction>> TriggeredActionsThisTick;` — Actions that have been triggered this tick and have a delegate that may be fired
- L272 _private member_ `TSet<TObjectPtr<const UInputAction>> ActionsThatHaveBeenRemovedFromMappings;` — A set of input actions that have been removed from the player's input mappings in a previous rebuild of the key mappings.
- L279 _private member_ `TMap<FKey, FVector> KeysPressedThisTick;` — `UPROPERTY(Transient)` — A map of Keys to the amount they were depressed this frame. This is reset with each call to ProcessInputStack and is populated within UEnhancedPlayerInput::InputKey.
- L283 _private member_ `TMap<TObjectPtr<const UInputAction>, FInjectedInputArray> InputsInjectedThisTick;` — `UPROPERTY(Transient)` — Inputs injected since the last call to ProcessInputStack
- L287 _private member_ `TSet<TObjectPtr<const UInputAction>> LastInjectedActions;` — `UPROPERTY(Transient)` — Last frame's injected inputs
- L303 _private member_ `TArray<FDependentChordTracker> DependentChordActions;` — Array of all dependant Input Action's with Chord triggers on them. Populated by IEnhancedInputSubsystemInterface::ReorderMappings
- L308 _protected member_ `TMap<FKey, bool> KeyDownPrevious;` — We need to grab the down states of all keys before calling Super::ProcessInputStack as it will leave bDownPrevious in the same state as bDown (i.e. this frame, not last).
- L316 _protected member_ `uint8 bIsFlushingInputThisFrame : 1;` — If true, then FlushPressedKeys has been called and the input key state map has been flushed. This will be set to true in UEnhancedPlayerInput::FlushPressedKeys, and reset to false at the end of UEnhancedPlayerInput::ProcessInputStack
- L322 _protected member_ `FName CurrentlyInUseAnyKeySubstitute;` — If there is a key mapping to EKeys::AnyKey, we will keep track of what key was used when we first found a "Pressed" event. That way we can use the same key when we wait for a "Released" event.
- L327 _private member_ `float LastFrameTime = 0.0f;` — The last time of the last frame that was processed in ProcessPlayerInput
- L330 _private member_ `float RealTimeDeltaSeconds = 0.0f;` — Delta seconds between frames calculated with UWorld::GetRealTimeSeconds

#### struct `UEnhancedPlayerInput::FDependentChordTracker`  
`struct FDependentChordTracker`  
_L290-297_
- desc: Used to keep track of Input Actions that have UInputTriggerChordAction triggers on them
- L293 _public member_ `TObjectPtr<const UInputAction> SourceAction;` — The Input Action that has the UInputTriggerChordAction on it
- L296 _public member_ `TObjectPtr<const UInputAction> DependantAction;` — The action that is referenced by the SourceAction's Chord trigger

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API ENHANCEDINPUT_API`
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace EnhancedInput` (scope `UE`)
- L32 _prototype_ `UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputMode_Default);` (scope `UE::EnhancedInput`) — The default input mode of Enhanced Input. Every Input Mapping Context will it's default filtering query set to check for this exact tag.

### `Plugins/EnhancedInput/Source/EnhancedInput/Public/InputAction.h` (Public)


#### enum `EInputActionAccumulationBehavior`  
`enum class EInputActionAccumulationBehavior : uint8`  
_L24-41_
- reflection: `UENUM()`
- desc: This is an advanced setting that allows you to change how the value of an Input Action is calculated when there are multiple mappings to the same Input Action. The default behavior is to accept highest absolute value.
- L31 _public enumerator_ `TakeHighestAbsoluteValue` — Take the value from the mapping with the highest Absolute Value. For example, given a value of -0.3 and 0.5, the input action's value would be 0.5.
- L40 _public enumerator_ `Cumulative` — Cumulatively adds the key values for each mapping. For example, a value of -0.7 and +0.75 on the same input action would result in a value of 0.05. A practical example of when to use this would be for something like WASD movement, if you want pressing W and S to cancel each other out.

#### class `UInputAction`  
`class UInputAction : public UDataAsset`  
_L55-154_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UDataAsset`
- desc: An Input Action is a logical representation of something the user can do, such as "Jump" or "Crouch". These are what your gameplay code binds to in order to listen for input state changes. For most scenarios your gameplay code should be listening for the "Triggered" event on an input action. This will allow for the most scalable and customizable input configuration because you can add different triggers for each key mapping in the Input Mapping Context. They are the conceptual equivalent to "Action" and "Axis" mapping names from the Legacy Input System. Note: These are instanced per player (via FInputActionInstance)
- L63 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — Track actions that have had their ValueType changed to update blueprints referencing them.
- L64 _public prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;`
- L66 _public member_ `static TSet<const UInputAction*> ActionsWithModifiedValueTypes;`
- L67 _public member_ `static TSet<const UInputAction*> ActionsWithModifiedTriggers;`
- L72 _public prototype_ `ETriggerEventsSupported GetSupportedTriggerEvents() const;` — Returns a bitmask of supported trigger events that is built from each UInputTrigger on this Action.
- L74 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FTriggersChanged);`
- L75 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FModifiersChanged);`
- L77 _public member_ `FTriggersChanged OnTriggersChanged;`
- L78 _public member_ `FModifiersChanged OnModifiersChanged;`
- L84 _public function_ `const TObjectPtr<UPlayerMappableKeySettings>& GetPlayerMappableKeySettings() const` — Returns the Player Mappable Key Settings for this Input Action.
- L88 _public member_ `FText ActionDescription = FText::GetEmpty();` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Description")` — A localized descriptor of this input action
- L92 _public member_ `bool bTriggerWhenPaused = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Action)` — Should this action be able to trigger whilst the game is paused - Replaces bExecuteWhenPaused
- L96 _public member_ `bool bConsumeInput = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Consumption", meta=(DisplayName="Consume Lower Priority Enhanced Input Mappings"))` — Should this action swallow any inputs bound to it or allow them to pass through to affect lower priority bound actions?
- L104 _public member_ `bool bConsumesActionAndAxisMappings = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Consumption")` — Should this Input Action consume any legacy Action and Axis key mappings? If true, then any key mapping to this input action will consume(aka block) the legacy key mapping from firing delegates.
- L108 _public member_ `bool bReserveAllMappings = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Action)` — This action's mappings are not intended to be automatically overridden by higher priority context mappings. Users must explicitly remove the mapping first. NOTE: It is the responsibility of the author of the mapping code to enforce this!
- L112 _public member_ `int32 TriggerEventsThatConsumeLegacyKeys;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Consumption", meta=(EditCondition = "bConsumesActionAndAxisMappings", Bitmask, BitmaskEnum="/Script/EnhancedInput.ETriggerEvent"))` — A bitmask of trigger events that, when reached, will consume any FKeys mapped to this input action.
- L116 _public member_ `EInputActionValueType ValueType = EInputActionValueType::Boolean;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Action, AssetRegistrySearchable)` — The type that this action returns from a GetActionValue query or action event
- L127 _public member_ `EInputActionAccumulationBehavior AccumulationBehavior = EInputActionAccumulationBehavior::TakeHighestAbsoluteValue;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Action, AdvancedDisplay)` — This defines how the value of this input action will be calcuated in the case that there are multiple key mappings to the same input action. When TakeHighestAbsoluteValue is selected, then the key mapping with the highest absolutle value will be utilized. (Default) When Cumulative is selected, then each key mapping will be added together to get the key value. @see UEnhancedPlayerInput::ProcessActionMappingEvent, where this property is read from.
- L135 _public member_ `TArray<TObjectPtr<UInputTrigger>> Triggers;` — `UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = Action)` — Trigger qualifiers. If any trigger qualifiers exist the action will not trigger unless: At least one Explicit trigger in this list has been met. All Implicit triggers in this list are met.
- L145 _public member_ `TArray<TObjectPtr<UInputModifier>> Modifiers;` — `UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = Action, meta=(DisplayAfter="Triggers"))` — Modifiers are applied to the final action value. These are applied sequentially in array order. They are applied on top of any FEnhancedActionKeyMapping modifiers that drove the initial input Note: Modifiers defined in the Input Action asset will be applied AFTER any modifiers defined in individual key mappings in the Input Mapping Context asset.
- L153 _protected member_ `TObjectPtr<UPlayerMappableKeySettings> PlayerMappableKeySettings;` — `UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = "User Settings", meta=(AllowPrivateAccess))` — Holds setting information about this Action Input for setting screen and save purposes.

#### struct `FTriggerStateTracker`  
`struct FTriggerStateTracker`  
_L157-201_
- desc: Calculate a collective representation of trigger state from evaluations of all triggers in one or more trigger groups.
- L167 _public prototype_ `ETriggerState EvaluateTriggers(const UEnhancedPlayerInput* PlayerInput, const TArray<UInputTrigger*>& Triggers, FInputActionValue ModifiedValue, float DeltaTime);` — Add a group of triggers to the evaluated state, returning the new trigger state.
- L169 _public prototype_ `ETriggerState GetState() const;`
- L171 _public function_ `void SetMappingTriggerApplied(bool bNewVal)`
- L172 _public function_ `bool GetMappingTriggerApplied() const`
- L174 _public function_ `bool operator>=(const FTriggerStateTracker& Other) const`
- L180 _public function_ `bool operator< (const FTriggerStateTracker& Other) const`
- L188 _public prototype_ `void SetStateForNoTriggers(ETriggerState State);` — TODO: Hacky. This is the state we should return if we have evaluated no valid triggers. Set during action evaluation based on final ModifiedValue.
- L191 _private member_ `ETriggerState NoTriggerState = ETriggerState::None;`
- L193 _private member_ `bool bEvaluatedInput = false;` — Non-zero input value was provided at some point in the evaluation
- L194 _private member_ `bool bEvaluatedTriggers = false;` — At least one valid trigger was evaluated
- L195 _private member_ `bool bFoundActiveTrigger = false;` — If any trigger is in an ongoing or triggered state the final state must be at least ongoing (with the exception of blocking triggers!)
- L196 _private member_ `bool bAnyExplictTriggered = false;`
- L197 _private member_ `bool bFoundExplicit = false;` — If no explicits are found the trigger may fire through implicit testing only. If explicits exist at least one must be met.
- L198 _private member_ `bool bAllImplicitsTriggered = true;`
- L199 _private member_ `bool bBlocking = false;` — If any trigger is blocking, we can't fire.
- L200 _private member_ `bool bMappingTriggerApplied = false;` — Set to true when an actionmapping is processed and triggers were found

#### struct `FInputActionInstance`  
`struct FInputActionInstance`  
_L207-281_
- reflection: `USTRUCT(BlueprintType)`
- desc: Run time queryable action instance Generated from UInputAction templates above
- L217 _private member_ `TObjectPtr<const UInputAction> SourceAction = nullptr;` — `UPROPERTY(BlueprintReadOnly, Category = "Input", Meta = (AllowPrivateAccess))` — The source action that this instance is created from
- L220 _private member_ `ETriggerState LastTriggerState = ETriggerState::None;` — Internal trigger states
- L221 _private member_ `FTriggerStateTracker TriggerStateTracker;`
- L222 _private member_ `ETriggerEventInternal TriggerEventInternal = ETriggerEventInternal(0);`
- L228 _protected member_ `ETriggerEvent TriggerEvent = ETriggerEvent::None;` — `UPROPERTY(BlueprintReadOnly, Transient, Category = Action)` — Trigger state
- L232 _protected member_ `float LastTriggeredWorldTime = 0.0f;` — `UPROPERTY(BlueprintReadOnly, Transient, Category = Action)` — The last time that this evaluated to a Triggered State
- L235 _protected member_ `TArray<TObjectPtr<UInputTrigger>> Triggers;` — `UPROPERTY(Instanced, BlueprintReadOnly, Category = Config)`
- L238 _protected member_ `TArray<TObjectPtr<UInputModifier>> Modifiers;` — `UPROPERTY(Instanced, BlueprintReadOnly, Category = Config)`
- L241 _protected member_ `FInputActionValue Value;` — Combined value of all inputs mapped to this action
- L245 _protected member_ `float ElapsedProcessedTime = 0.f;` — `UPROPERTY(BlueprintReadOnly, Category = Action)` — Total trigger processing/evaluation time (How long this action has been in event Started, Ongoing, or Triggered
- L249 _protected member_ `float ElapsedTriggeredTime = 0.f;` — `UPROPERTY(BlueprintReadOnly, Category = Action)` — Triggered time (How long this action has been in event Triggered only)
- L252 _public prototype_ `FInputActionInstance() = default;`
- L253 _public prototype_ `FInputActionInstance(const UInputAction* InSourceAction);`
- L256 _public function_ `ETriggerEvent GetTriggerEvent() const` — Current trigger event
- L259 _public prototype_ `FInputActionValue GetValue() const;` — Current action value - Will be zero if the current trigger event is not ETriggerEvent::Triggered!
- L262 _public prototype_ `ETriggerState GetEvaluatedActionTriggerState() const;` — Returns the evaluated trigger state
- L265 _public function_ `float GetElapsedTime() const` — Total time the action has been evaluating triggering (Ongoing & Triggered)
- L268 _public function_ `float GetTriggeredTime() const` — Time the action has been actively triggered (Triggered only)
- L271 _public function_ `float GetLastTriggeredWorldTime() const` — Time that this action was last actively triggered
- L273 _public function_ `const TArray<TObjectPtr<UInputTrigger>>& GetTriggers() const`
- L274 _public function_ `const TArray<TObjectPtr<UInputModifier>>& GetModifiers() const`
- L277 _public function_ `TObjectPtr<const UInputAction> GetSourceAction() const` — The source action that this instance is created from
- L279 _public function_ `void AddInputTrigger(UInputTrigger* InputTrigger)`
- L280 _public function_ `void RemoveInputTrigger(UInputTrigger* InputTrigger)`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API ENHANCEDINPUT_API`
- L74 _delegate_ `DECLARE_MULTICAST_DELEGATE(FTriggersChanged);`
- L75 _delegate_ `DECLARE_MULTICAST_DELEGATE(FModifiersChanged);`

### `Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h` (Public)


#### enum `EInputActionValueType`  
`enum class EInputActionValueType : uint8`  
_L10-19_
- reflection: `UENUM(BlueprintType)`
- L15 _public enumerator_ `Boolean UMETA(DisplayName = "Digital (bool)")`
- L16 _public enumerator_ `Axis1D UMETA(DisplayName = "Axis1D (float)")`
- L17 _public enumerator_ `Axis2D UMETA(DisplayName = "Axis2D (Vector2D)")`
- L18 _public enumerator_ `Axis3D UMETA(DisplayName = "Axis3D (Vector)")`

#### struct `FInputActionValue`  
`struct FInputActionValue`  
_L23-201_
- reflection: `USTRUCT(BlueprintType, meta = (HasNativeMake = "/Script/EnhancedInput.EnhancedInputLibrary.MakeInputActionValueOfType", HasNativeBreak = "/Script/EnhancedInput.EnhancedInputLibrary.BreakInputActionValue"))`
- L29 _public typedef_ `using Axis1D = float;` — using Button = bool;
- L30 _public typedef_ `using Axis2D = FVector2D;`
- L31 _public typedef_ `using Axis3D = FVector;`
- L34 _public prototype_ `FInputActionValue() = default;` — Support all relevant default constructors (FInputActionValue isn't movable)
- L35 _public prototype_ `FInputActionValue(const FInputActionValue&) = default;`
- L36 _public prototype_ `FInputActionValue& operator= (const FInputActionValue&) = default;`
- L39 _public function_ `FInputActionValue(FKey KeyDefault) : Value(0.f), ValueType(GetValueTypeFromKey(KeyDefault))` — Construct default value for a key
- L43 _public function_ `explicit FInputActionValue(bool bInValue) : Value(bInValue ? 1.f : 0.f, 0.f, 0.f), ValueType(EInputActionValueType::Boolean)` — Specialized constructors for supported types Converting a value to a different type (e.g. Val = FVector(1, 1, 1); Val = true;) zeroes out any unused components to ensure getters continue to function correctly.
- L44 _public function_ `FInputActionValue(Axis1D InValue) : Value(InValue, 0.f, 0.f), ValueType(EInputActionValueType::Axis1D)`
- L45 _public function_ `FInputActionValue(Axis2D InValue) : Value(InValue, 0.f), ValueType(EInputActionValueType::Axis2D)`
- L46 _public function_ `FInputActionValue(Axis3D InValue) : Value(InValue), ValueType(EInputActionValueType::Axis3D)`
- L49 _public function_ `FInputActionValue(EInputActionValueType InValueType, Axis3D InValue) : Value(InValue), ValueType(InValueType)` — Build a specific type with an arbitrary Axis3D value
- L68 _public function_ `void Reset()` — Resets Value without affecting ValueType
- L73 _public function_ `FInputActionValue& operator+=(const FInputActionValue& Rhs)`
- L89 _public function_ `FInputActionValue& operator*=(float Scalar)` — Scalar operators
- L106 _public function_ `template<typename T> inline T Get() const`
- L109 _public function_ `float operator[](int32 Index) const` — Read only index based value accessor, doesn't care about type. Expect 0 when accessing unused components.
- L111 _public function_ `bool IsNonZero(float Tolerance = KINDA_SMALL_NUMBER) const`
- L114 _public function_ `FInputActionValue& ConvertToType(EInputActionValueType Type)` — In-place type conversion
- L122 _public function_ `FInputActionValue& ConvertToType(const FInputActionValue& Other)`
- L124 _public function_ `EInputActionValueType GetValueType() const`
- L125 _public function_ `static EInputActionValueType GetValueTypeFromKey(FKey Key)`
- L142 _public function_ `float GetMagnitudeSq() const`
- L159 _public function_ `float GetMagnitude() const`
- L177 _public function_ `inline FString ToString() const` — Type sensitive debug stringify
- L197 _protected member_ `FVector Value = FVector::ZeroVector;`
- L199 _protected member_ `EInputActionValueType ValueType = EInputActionValueType::Boolean;`
- L205 _function_ `template<> inline bool FInputActionValue::Get() const` — Supported getter specializations
- L212 _function_ `template<> inline FInputActionValue::Axis1D FInputActionValue::Get() const`
- L218 _function_ `template<> inline FInputActionValue::Axis2D FInputActionValue::Get() const`
- L224 _function_ `template<> inline FInputActionValue::Axis3D FInputActionValue::Get() const`

#### Free symbols / members of external scopes

- L81 _function_ `friend FInputActionValue operator+(const FInputActionValue& Lhs, const FInputActionValue& Rhs)`
- L95 _function_ `friend FInputActionValue operator*(const FInputActionValue& Lhs, const float Rhs)`

### `Plugins/EnhancedInput/Source/EnhancedInput/Public/InputDebugKeyDelegateBinding.h` (Public)


#### struct `FBlueprintInputDebugKeyDelegateBinding`  
`struct FBlueprintInputDebugKeyDelegateBinding`  
_L15-32_
- reflection: `USTRUCT()`
- L20 _public member_ `FInputChord InputChord;` — `UPROPERTY()`
- L23 _public member_ `TEnumAsByte<EInputEvent> InputKeyEvent = IE_Pressed;` — `UPROPERTY()`
- L26 _public member_ `FName FunctionNameToBind = NAME_None;` — `UPROPERTY()`
- L29 _public member_ `bool bExecuteWhenPaused = false;` — `UPROPERTY()`

#### class `UInputDebugKeyDelegateBinding`  
`class UInputDebugKeyDelegateBinding : public UInputDelegateBinding`  
_L35-46_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInputDelegateBinding`
- L41 _public member_ `TArray<FBlueprintInputDebugKeyDelegateBinding> InputDebugKeyDelegateBindings;` — `UPROPERTY()`
- L44 _public prototype_ `virtual void BindToInputComponent(UInputComponent* InputComponent, UObject* ObjectToBindTo) const override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ENHANCEDINPUT_API`

### `Plugins/EnhancedInput/Source/EnhancedInput/Public/InputMappingContext.h` (Public)


#### enum `EMappingContextInputModeFilterOptions`  
`enum class EMappingContextInputModeFilterOptions : uint8`  
_L20-41_
- reflection: `UENUM()`
- desc: Options for an input mapping context being filtered based on the current input mode of the player.
- L29 _public enumerator_ `UseProjectDefaultQuery` — This mapping context should use the project's default input mode query. @see UEnhancedInputDeveloperSettings::DefaultMappingContextInputModeQuery (Project Settings -> Engine -> Enhanced Input -> Input Modes)
- L34 _public enumerator_ `UseCustomQuery` — This mapping context should use a custom input mode query instead of the project default.
- L40 _public enumerator_ `DoNotFilter` — This Input mapping context should not be filtered based on the current mode, effectively ignoring the current mode.

#### enum `EMappingContextRegistrationTrackingMode`  
`enum class EMappingContextRegistrationTrackingMode : uint8`  
_L47-64_
- reflection: `UENUM()`
- desc: Options for how multiple registrations of an input mapping context should be tracked.
- L53 _public enumerator_ `Untracked` — This is the default behavior. Registrations of the Input Mapping Context are not tracked. The mapping context will be unregistered when removing it the first time, no matter how many times it has been added.
- L63 _public enumerator_ `CountRegistrations` — Track how many times the IMC is added and keeps the IMC applied until the IMC is removed the same number of times. This allows multiple systems to use the same Input Mapping Context without needing to check if any other systems are still using the same Input Mapping Context. Warnings will be logged if Input Mapping Contexts with this tracking mode are still applied at deinitialization, the expectation is that there will be a RemoveMappingContext() call for every call to AddMappingContext() when using this mode. @see IEnhancedInputSubsystemInterface::ValidateTrackedMappingContextsAreUnregistered

#### struct `FInputMappingContextMappingData`  
`struct FInputMappingContextMappingData`  
_L67-76_
- reflection: `USTRUCT(BlueprintType)`
- L75 _public member_ `TArray<FEnhancedActionKeyMapping> Mappings;` — `UPROPERTY(config, BlueprintReadOnly, EditAnywhere, Category = "Mappings")` — List of Input Actions and which keys they are mapped to.

#### class `UInputMappingContext`  
`class UInputMappingContext : public UDataAsset`  
_L87-247_
- reflection: `UCLASS(MinimalAPI, BlueprintType, config = Input)`
- inherits: `UDataAsset`
- desc: UInputMappingContext : A collection of key to action mappings for a specific input context Could be used to: Store predefined controller mappings (allow switching between controller config variants). TODO: Build a system allowing redirects of UInputMappingContexts to handle this. Define per-vehicle control mappings Define context specific mappings (e.g. I switch from a gun (shoot action) to a grappling hook (reel in, reel out, disconnect actions). Define overlay mappings to be applied on top of existing control mappings (e.g. Hero specific action mappings in a MOBA)
- L95 _protected member_ `TArray<FEnhancedActionKeyMapping> Mappings;` — `UE_DEPRECATED(5.7, "Use the DefaultKeyMappings struct instead.")` — `UPROPERTY(config, BlueprintReadOnly, Category = "Mappings", meta = (DeprecatedProperty="Note", DeprecationMessage = "Use the DefaultKeyMappings struct instead."))` — List of key to action mappings.
- L101 _protected member_ `FInputMappingContextMappingData DefaultKeyMappings;` — `UPROPERTY(config, BlueprintReadOnly, EditAnywhere, Category = "Mappings")` — List of Input Actions to which FKeys they are mapped to.
- L110 _protected member_ `TMap<FString, FInputMappingContextMappingData> MappingProfileOverrides;` — `UPROPERTY(config, BlueprintReadOnly, EditAnywhere, Category = "Mappings")` — Key mappings that should be used INSTEAD of the default "Mappings" array above then the provided Remappable Key Profile of the given name is currently active. If there are no override mappings specified for a set for a specific mapping profile, then the default mappings will be used.
- L115 _public prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;`
- L118 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L119 _public prototype_ `virtual void PostLoad() override;`
- L131 _protected member_ `EMappingContextInputModeFilterOptions InputModeFilterOptions = EMappingContextInputModeFilterOptions::UseProjectDefaultQuery;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input Modes", meta = (EditCondition="ShouldShowInputModeQuery()"))` — Defines how this input mapping context should be filtered based on the current input mode. Default is Use Project Default Query. @Note: bEnableInputModeFiltering must be enabled in the UEnhancedInputDeveloperSettings for this to be considered.
- L142 _protected member_ `FGameplayTagQuery InputModeQueryOverride;` — `UPROPERTY(config, BlueprintReadOnly, EditAnywhere, Category = "Input Modes", meta = (EditConditionHides, EditCondition="ShouldShowInputModeQuery() && InputModeFilterOptions == EMappingContextInputModeFilterOptions::UseCustomQuery"))` — Tag Query which will be matched against the current Enhanced Input Subsystem's input mode if InputModeFilterOptions is set to UseCustomQuery. If this tag query does not match with the current input mode tag container, then the mappings will not be processed. @Note: bEnableInputModeFiltering must be enabled in the UEnhancedInputDeveloperSettings for this to be considered.
- L148 _protected member_ `EMappingContextRegistrationTrackingMode RegistrationTrackingMode = EMappingContextRegistrationTrackingMode::Untracked;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Registration")` — Select the behaviour when multiple AddMappingContext() calls are made for this Input Mapping Context
- L157 _public prototype_ `void ForEachKeyMapping(TFunctionRef<void(const FEnhancedActionKeyMapping&)>&& Func) const;` — Executes the given lambda on every default and override key mapping specified on this mapping context. @param Func Lambda function to execute on a given key mapping
- L162 _public prototype_ `bool ShouldFilterMappingByInputMode() const;` — @return True if this mapping context should be filtered based on the current input mode.
- L168 _public prototype_ `FGameplayTagQuery GetInputModeQuery() const;` — @return The tag query which should be used when deciding whether this mapping context should be filtered out based on the current input mode or not.
- L173 _public function_ `EMappingContextRegistrationTrackingMode GetRegistrationTrackingMode() const` — @return The registration tracking mode that this IMC is using.
- L176 _public function_ `EMappingContextInputModeFilterOptions GetInputModeFilterOptions() const` — @return The input mode filter options set on this mapping context.
- L180 _public member_ `FText ContextDescription;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Description", DisplayName = "Description")` — Localized context descriptor
- L187 _public prototype_ `static bool ShouldShowInputModeQuery();` — `UFUNCTION()` — UFUNCTION helper to be used as en edit condition for displaying input mode query releated properties.
- L193 _public prototype_ `bool HasMappingsForProfile(const FString& ProfileId) const;` — @param ProfileId The Player Mappable Key Profile ID @return True if this Input Mapping Context has some specific override mappings for the given profile.
- L198 _public prototype_ `TArray<FString> GetProfilesWithOverridenMappings() const;` — @return An array of profile identifiers which this IMC specifies overrides for.
- L205 _public prototype_ `const TArray<FEnhancedActionKeyMapping>& GetMappingsForProfile(const FString& ProfileId) const;` — @param ProfileId The Player Mappable Key Profile ID @return Reference to the key mappings to use for the given profile. If there is no override mapping specified for the given profile, then the default mappings will be returned.
- L210 _public prototype_ `bool HasMappingForInputAction(const UInputAction* Action) const;` — Returns true if this Input Mapping Context contains a reference to the given Input Action in its default or profile override mappings.
- L219 _public function_ `const TArray<FEnhancedActionKeyMapping>& GetMappings() const` — Mapping accessors. Note: Use UEnhancedInputLibrary::RequestRebuildControlMappingsForContext to invoke changes made to an FEnhancedActionKeyMapping
- L220 _public function_ `FEnhancedActionKeyMapping& GetMapping(TArray<FEnhancedActionKeyMapping>::SizeType Index)`
- L228 _public prototype_ `FEnhancedActionKeyMapping& MapKey(const UInputAction* Action, FKey ToKey);` — `UFUNCTION(BlueprintCallable, Category = "Mapping")` — Map a key to an action within the mapping context.
- L234 _public prototype_ `void UnmapKey(const UInputAction* Action, FKey Key);` — `UFUNCTION(BlueprintCallable, Category = "Mapping")` — Unmap a key from an action within the mapping context.
- L240 _public prototype_ `void UnmapAllKeysFromAction(const UInputAction* Action);` — `UFUNCTION(BlueprintCallable, Category = "Mapping")` — Unmap all key maps to an action within the mapping context.
- L246 _public prototype_ `void UnmapAll();` — `UFUNCTION(BlueprintCallable, Category = "Mapping")` — Unmap everything within the mapping context.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ENHANCEDINPUT_API`

### `Plugins/EnhancedInput/Source/EnhancedInput/Public/InputMappingQuery.h` (Public)


#### enum `EMappingQueryResult`  
`enum class EMappingQueryResult : uint8`  
_L10-26_
- reflection: `UENUM(BlueprintType)`
- desc: Result summary from a QueryMapKeyIn... call
- L13 _public enumerator_ `Error_EnhancedInputNotEnabled` — Query failed because the player controller being queried is not configured to support enhanced input (PlayerInput is not Enhanced).
- L16 _public enumerator_ `Error_InputContextNotInActiveContexts` — Query failed because the input context being queried against is not part of the active context list.
- L19 _public enumerator_ `Error_InvalidAction` — Query failed because the action being queried against is None/null
- L22 _public enumerator_ `NotMappable` — Mapping cannot be applied due to blocking issues. Check OutIssues for details.
- L25 _public enumerator_ `MappingAvailable` — Mapping will not affect any existing mappings and is safe to apply.

#### enum `EMappingQueryIssue`  
`enum class EMappingQueryIssue : uint8`  
_L30-52_
- reflection: `UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true", ScriptName = "MappingQueryIssueFlag"))`
- desc: Mapping issues arising from a QueryMapKeyIn... call
- L33 _public enumerator_ `NoIssue = 0x00` — Mapping will not affect any existing mappings and is safe to apply.
- L36 _public enumerator_ `ReservedByAction = 0x01` — Mapping has been reserved for the exclusive use of another action. The new mapping should be refused.
- L39 _public enumerator_ `HidesExistingMapping = 0x02` — Mapping will cause an existing mapping to be hidden and/or need remapping.
- L42 _public enumerator_ `HiddenByExistingMapping = 0x04` — Mapping will not be functional, due to an existing mapping blocking it.
- L45 _public enumerator_ `CollisionWithMappingInSameContext = 0x08` — Mapping will be functional, but a collision with another mapping within this context may cause issues.
- L48 _public enumerator_ `ForcesTypePromotion = 0x10` — Trying to bind an FKey with a less complex type than the bound action expects (e.g. Keyboard key bound to a 2D Gamepad axis. May not be desirable). Note: bool -> Axis1D promotions are never considered forced.
- L51 _public enumerator_ `ForcesTypeDemotion = 0x20` — Trying to bind an FKey with a more complex type than the bound action supports (this could behave oddly e.g. 2D Gamepad axis bound to a 1D axis will ignore Y axis)

#### struct `FMappingQueryIssue`  
`struct FMappingQueryIssue`  
_L68-85_
- reflection: `USTRUCT(BlueprintType)`
- desc: Potential issue raised with a mapping request
- L72 _public prototype_ `FMappingQueryIssue() = default;`
- L73 _public function_ `FMappingQueryIssue(EMappingQueryIssue InIssue) : Issue(InIssue)`
- L76 _public member_ `EMappingQueryIssue Issue = EMappingQueryIssue::NoIssue;` — `UPROPERTY(BlueprintReadOnly, Category = Result)`
- L80 _public member_ `TObjectPtr<const UInputMappingContext> BlockingContext = nullptr;` — `UPROPERTY(BlueprintReadOnly, Category = Result)` — Input context that contains a blocking action bound to the queried key
- L84 _public member_ `TObjectPtr<const UInputAction> BlockingAction = nullptr;` — `UPROPERTY(BlueprintReadOnly, Category = Result)` — Action within the input context that caused the blockage

#### Free symbols / members of external scopes

- L53 _prototype_ `ENUM_CLASS_FLAGS(EMappingQueryIssue);`
- L56 _namespace_ `namespace DefaultMappingIssues`
- L58 _variable_ `inline constexpr EMappingQueryIssue NoCollisions = EMappingQueryIssue::HidesExistingMapping | EMappingQueryIssue::HiddenByExistingMapping | EMappingQueryIssue::CollisionWithMappingInSameContext;` (scope `DefaultMappingIssues`)
- L59 _variable_ `inline constexpr EMappingQueryIssue TypeMismatch = EMappingQueryIssue::ForcesTypePromotion | EMappingQueryIssue::ForcesTypeDemotion;` (scope `DefaultMappingIssues`)
- L60 _variable_ `inline constexpr EMappingQueryIssue StandardFatal = EMappingQueryIssue::ReservedByAction | NoCollisions | TypeMismatch;` (scope `DefaultMappingIssues`) — Default fatal value for QueryMapKeyIn... function calls.

### `Plugins/EnhancedInput/Source/EnhancedInput/Public/InputModifiers.h` (Public)


#### class `UInputModifier`  
`class UInputModifier : public UObject`  
_L16-77_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable, EditInlineNew, CollapseCategories, Config = Input, defaultconfig, configdonotcheckdefaults)`
- inherits: `UObject`
- desc: Base class for building modifiers.
- L27 _protected function_ `virtual FInputActionValue ModifyRaw_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue CurrentValue, float DeltaTime)` — ModifyRaw implementation. Override this to alter input values in native code. @param CurrentValue - The modified value returned by the previous modifier in the chain, or the base input device value if this is the first modifier in the chain. @param DeltaTime - Elapsed time since last input tick. @return Modified value. Note that whilst the returned value can be of any FInputActionValueType it will be reset to the value type of the associated action before any further processing.
- L32 _protected function_ `virtual FLinearColor GetVisualizationColor_Implementation(FInputActionValue SampleValue, FInputActionValue FinalValue) const`
- L46 _public prototype_ `FInputActionValue ModifyRaw(const UEnhancedPlayerInput* PlayerInput, FInputActionValue CurrentValue, float DeltaTime) const;` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Modifier")` — ModifyRaw Will be called by each modifier in the modifier chain @param CurrentValue - The modified value returned by the previous modifier in the chain, or the base raw value if this is the first modifier in the chain.
- L54 _public prototype_ `FLinearColor GetVisualizationColor(FInputActionValue SampleValue, FInputActionValue FinalValue) const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Modifier")` — Helper to allow debug visualization of the modifier. @param SampleValue - The base input action value pre-modification (ranging -1 -> 1 across all applicable axes). @param FinalValue - The post-modification input action value for the provided SampleValue.
- L65 _public prototype_ `void OnModifierReinstanced(const UInputModifier* OldModifier);` — Called during RebuildControlMappings when this modifier instance replaces an older instance of the same class. Transfers runtime state from the old modifier so that stateful modifiers like Smooth don't lose their accumulated state. The old modifier is guaranteed to be the same class (verified by FEnhancedActionKeyMapping::Equals). This function dispatches to ReceiveModifierReinstanced for subclass state.
- L75 _protected prototype_ `void ReceiveModifierReinstanced(const UInputModifier* OldModifier);` — `UFUNCTION(BlueprintNativeEvent, Category = "Modifier")` — Override to transfer custom runtime state from a previous modifier instance of the same class. Called by OnModifierReinstanced. Subclasses should call Super to ensure parent state is transferred.
- L76 _protected function_ `virtual void ReceiveModifierReinstanced_Implementation(const UInputModifier* OldModifier)`

#### enum `ENormalizeInputSmoothingType`  
`enum class ENormalizeInputSmoothingType : uint8`  
_L81-99_
- reflection: `UENUM()`
- desc: Behavior options for how the value is calculated in UInputModifierSmoothDelta.
- L83 _public enumerator_ `None UMETA(Hidden)`
- L84 _public enumerator_ `Lerp`
- L85 _public enumerator_ `Interp_To`
- L86 _public enumerator_ `Interp_Constant_To`
- L87 _public enumerator_ `Interp_Circular_In`
- L88 _public enumerator_ `Interp_Circular_Out`
- L89 _public enumerator_ `Interp_Circular_In_Out`
- L90 _public enumerator_ `Interp_Ease_In`
- L91 _public enumerator_ `Interp_Ease_Out`
- L92 _public enumerator_ `Interp_Ease_In_Out`
- L93 _public enumerator_ `Interp_Expo_In`
- L94 _public enumerator_ `Interp_Expo_Out`
- L95 _public enumerator_ `Interp_Expo_In_Out`
- L96 _public enumerator_ `Interp_Sin_In`
- L97 _public enumerator_ `Interp_Sin_Out`
- L98 _public enumerator_ `Interp_Sin_In_Out`

#### class `UInputModifierSmoothDelta`  
`class UInputModifierSmoothDelta : public UInputModifier`  
_L108-136_
- reflection: `UCLASS(NotBlueprintable, MinimalAPI, meta = (DisplayName = "Smooth Delta"))`
- inherits: `UInputModifier`
- desc: Normalized Smooth Delta Produces a smoothed normalized delta of the current(new) and last(old) input value. Boolean input values will be returned as is.
- L115 _public member_ `ENormalizeInputSmoothingType SmoothingMethod = ENormalizeInputSmoothingType::Lerp;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, Config)`
- L119 _public member_ `float Speed = 0.5f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, Config)` — Speed, or Alpha. If the speed given is 0, then jump to the target.
- L127 _public member_ `float EasingExponent = 2.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, Config, meta=(EditCondition="SmoothingMethod == ENormalizeInputSmoothingType::Interp_Ease_In ||SmoothingMethod == ENormalizeInputSmoothingType::Interp_Ease_Out || SmoothingMethod == ENormalizeInputSmoothingType::Interp_Ease_In_Out"))` — For ease functions, this controls the degree of the curve. This only affects the Interp_Ease_In, Interp_Ease_Out, and Interp_Ease_In_Out smoothing methods
- L130 _protected prototype_ `virtual FInputActionValue ModifyRaw_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue CurrentValue, float DeltaTime) override;`
- L131 _protected prototype_ `virtual void ReceiveModifierReinstanced_Implementation(const UInputModifier* OldModifier) override;`
- L133 _protected member_ `FVector OldValue = FVector::ZeroVector;`
- L135 _protected member_ `FVector Delta = FVector::ZeroVector;`

#### enum `EDeadZoneType`  
`enum class EDeadZoneType : uint8`  
_L140-163_
- reflection: `UENUM()`
- L144 _public enumerator_ `Axial` — Apply dead zone to axes individually. This will result in input being chamfered at the corners for 2d/3d axis inputs, and matches the original UE4 deadzone logic.
- L151 _public enumerator_ `Radial UMETA(DisplayName="Smoothed Radial")` — Apply dead zone logic to all axes simultaneously. This gives smooth input (circular/spherical coverage). On a 1d axis input this works identically to Axial. For most games, this will give the smoothest feeling analog values. The input is smoothed to avoid "jumpiness" when you are moving the analog axis.
- L162 _public enumerator_ `UnscaledRadial` — Apply dead zone logic to all axes simultaneously without any smooth input which the normal "Radial" deadzone applies. The behavior of this deadzone type is as follows: If the magnitude of the input is less then the lower threshold, ignore it. Clamp the magnitude of the input to the upper threshold value. For some games, this may result in feeling "jumpy", because the value goes from 0.0 to the lower threshold immediately instead of being smoothed, like the normal "Radial" deadzone option.

#### class `UInputModifierDeadZone`  
`class UInputModifierDeadZone : public UInputModifier`  
_L170-207_
- reflection: `UCLASS(NotBlueprintable, MinimalAPI, meta = (DisplayName = "Dead Zone"))`
- inherits: `UInputModifier`
- desc: Dead Zone Input values within the range LowerThreshold -> UpperThreshold will be remapped from 0 -> 1. Values outside this range will be clamped.
- L182 _public member_ `float LowerThreshold = 0.2f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Settings, Config, meta=(ClampMin=0, ClampMax=1))` — Threshold below which input is ignored. This value should always be less than the UpperThreshold.
- L190 _public member_ `float UpperThreshold = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Settings, Config, meta=(ClampMin=0, ClampMax=1))` — Threshold above which input is clamped to 1.0. This value should always be greater than the "Lower Threshold" value.
- L193 _public member_ `EDeadZoneType Type = EDeadZoneType::Radial;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Settings, Config)`
- L198 _protected prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;`
- L199 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L202 _protected prototype_ `virtual FInputActionValue ModifyRaw_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue CurrentValue, float DeltaTime) override;`
- L206 _protected prototype_ `virtual FLinearColor GetVisualizationColor_Implementation(FInputActionValue SampleValue, FInputActionValue FinalValue) const override;` — Visualize as black when unmodified. Red when blocked (with differing intensities to indicate axes) Mirrors visualization in https://www.gamasutra.com/blogs/JoshSutphin/20130416/190541/Doing_Thumbstick_Dead_Zones_Right.php.

#### class `UInputModifierScalar`  
`class UInputModifierScalar : public UInputModifier`  
_L213-235_
- reflection: `UCLASS(NotBlueprintable, MinimalAPI, meta = (DisplayName = "Scalar"))`
- inherits: `UInputModifier`
- desc: Scalar Scales input by a set factor per axis
- L220 _public prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;`
- L231 _public member_ `FVector Scalar = FVector::OneVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Settings)` — The scalar that will be applied to the input value. For example, if you have a scalar of (2.0, 2.0, 2.0), each input axis will be multiplied by 2.0. Note: This will do nothing on boolean input action types, as they can only be true or false.
- L234 _protected prototype_ `virtual FInputActionValue ModifyRaw_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue CurrentValue, float DeltaTime) override;`

#### class `UInputModifierScaleByDeltaTime`  
`class UInputModifierScaleByDeltaTime : public UInputModifier`  
_L241-247_
- reflection: `UCLASS(NotBlueprintable, MinimalAPI, meta = (DisplayName = "Scale By Delta Time"))`
- inherits: `UInputModifier`
- desc: Scalar Multiplies the input value by Delta Time this frame
- L246 _protected prototype_ `virtual FInputActionValue ModifyRaw_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue CurrentValue, float DeltaTime) override;`

#### class `UInputModifierNegate`  
`class UInputModifierNegate : public UInputModifier`  
_L253-269_
- reflection: `UCLASS(NotBlueprintable, MinimalAPI, meta = (DisplayName = "Negate"))`
- inherits: `UInputModifier`
- desc: Negate Inverts input per axis
- L260 _public member_ `bool bX = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)`
- L262 _public member_ `bool bY = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)`
- L264 _public member_ `bool bZ = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)`
- L267 _protected prototype_ `virtual FInputActionValue ModifyRaw_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue CurrentValue, float DeltaTime) override;`
- L268 _protected prototype_ `virtual FLinearColor GetVisualizationColor_Implementation(FInputActionValue SampleValue, FInputActionValue FinalValue) const override;`

#### class `UInputModifierSmooth`  
`class UInputModifierSmooth : public UInputModifier`  
_L275-300_
- reflection: `UCLASS(NotBlueprintable, MinimalAPI, meta = (DisplayName = "Smooth"))`
- inherits: `UInputModifier`
- desc: Smooth Smooth inputs out over multiple frames
- L279 _private prototype_ `void ClearSmoothedAxis();`
- L286 _protected member_ `float ZeroTime = 0.f;` — How long input has been zero.
- L289 _protected member_ `FInputActionValue AverageValue;` — Current average input/sample
- L292 _protected member_ `int32 Samples = 0;` — Number of samples since input  has been zero
- L296 _protected member_ `float TotalSampleTime = SMOOTH_TOTAL_SAMPLE_TIME_DEFAULT;` — Input sampling total time.
- L298 _protected prototype_ `virtual FInputActionValue ModifyRaw_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue CurrentValue, float DeltaTime) override;`
- L299 _protected prototype_ `virtual void ReceiveModifierReinstanced_Implementation(const UInputModifier* OldModifier) override;`

#### class `UInputModifierResponseCurveExponential`  
`class UInputModifierResponseCurveExponential : public UInputModifier`  
_L306-317_
- reflection: `UCLASS(NotBlueprintable, MinimalAPI, meta = (DisplayName = "Response Curve - Exponential"))`
- inherits: `UInputModifier`
- desc: Response Curve Exponential Apply a simple exponential response curve to input values, per axis
- L313 _public member_ `FVector CurveExponent = FVector::OneVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, Config)`
- L316 _protected prototype_ `virtual FInputActionValue ModifyRaw_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue CurrentValue, float DeltaTime) override;`

#### class `UInputModifierResponseCurveUser`  
`class UInputModifierResponseCurveUser : public UInputModifier`  
_L325-340_
- reflection: `UCLASS(NotBlueprintable, MinimalAPI, meta = (DisplayName = "Response Curve - User Defined"))`
- inherits: `UInputModifier`
- desc: Response Curve User Defined Apply a custom response curve to input values, per axis
- L332 _public member_ `TObjectPtr<UCurveFloat> ResponseX;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (DisplayThumbnail = "false"))`
- L334 _public member_ `TObjectPtr<UCurveFloat> ResponseY;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (DisplayThumbnail = "false"))`
- L336 _public member_ `TObjectPtr<UCurveFloat> ResponseZ;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (DisplayThumbnail = "false"))`
- L339 _protected prototype_ `virtual FInputActionValue ModifyRaw_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue CurrentValue, float DeltaTime) override;`

#### enum `EFOVScalingType`  
`enum class EFOVScalingType : uint8`  
_L343-350_
- reflection: `UENUM()`
- L346 _public enumerator_ `Standard` — FOV scaling to apply scaled movement deltas to inputs dependent upon the player's selected FOV
- L349 _public enumerator_ `UE4_BackCompat` — FOV scaling was incorrectly calculated in UE4's UPlayerInput::MassageAxisInput. This implementation is intended to aid backwards compatibility, but should not be used by new projects.

#### class `UInputModifierFOVScaling`  
`class UInputModifierFOVScaling : public UInputModifier`  
_L356-371_
- reflection: `UCLASS(NotBlueprintable, MinimalAPI, meta = (DisplayName = "FOV Scaling"))`
- inherits: `UInputModifier`
- desc: FOV Scaling Apply FOV dependent scaling to input values, per axis
- L364 _public member_ `float FOVScale = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, Config)` — Extra scalar applied on top of basic FOV scaling.
- L367 _public member_ `EFOVScalingType FOVScalingType = EFOVScalingType::Standard;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, Config)` — TODO: UE4_BackCompat by default?
- L370 _protected prototype_ `virtual FInputActionValue ModifyRaw_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue CurrentValue, float DeltaTime) override;`

#### class `UInputModifierToWorldSpace`  
`class UInputModifierToWorldSpace : public UInputModifier`  
_L379-386_
- reflection: `UCLASS(NotBlueprintable, MinimalAPI, meta = (DisplayName = "To World Space"))`
- inherits: `UInputModifier`
- desc: Input space to World space conversion Auto-converts axes within the Input Action Value into world space	allowing the result to be directly plugged into functions that take world space values. E.g. For a 2D input axis up/down is mapped to world X (forward), whilst axis left/right is mapped to world Y (right).
- L384 _protected prototype_ `virtual FInputActionValue ModifyRaw_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue CurrentValue, float DeltaTime) override;`
- L385 _protected prototype_ `virtual FLinearColor GetVisualizationColor_Implementation(FInputActionValue SampleValue, FInputActionValue FinalValue) const override;`

#### enum `EInputAxisSwizzle`  
`enum class EInputAxisSwizzle : uint8`  
_L390-406_
- reflection: `UENUM()`
- L393 _public enumerator_ `YXZ` — Swap X and Y axis. Useful for binding 1D inputs to the Y axis for 2D actions.
- L396 _public enumerator_ `ZYX` — Swap X and Z axis
- L399 _public enumerator_ `XZY` — Swap Y and Z axis
- L402 _public enumerator_ `YZX` — Reorder all axes, Y first
- L405 _public enumerator_ `ZXY` — Reorder all axes, Z first

#### class `UInputModifierSwizzleAxis`  
`class UInputModifierSwizzleAxis : public UInputModifier`  
_L412-425_
- reflection: `UCLASS(NotBlueprintable, MinimalAPI, meta = (DisplayName = "Swizzle Input Axis Values"))`
- inherits: `UInputModifier`
- desc: Swizzle axis components of an input value. Useful to map a 1D input onto the Y axis of a 2D action.
- L420 _public member_ `EInputAxisSwizzle Order = EInputAxisSwizzle::YXZ;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)` — Default to XY swap, useful for binding 1D inputs to the Y axis.
- L423 _protected prototype_ `virtual FInputActionValue ModifyRaw_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue CurrentValue, float DeltaTime) override;`
- L424 _protected prototype_ `virtual FLinearColor GetVisualizationColor_Implementation(FInputActionValue SampleValue, FInputActionValue FinalValue) const override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ENHANCEDINPUT_API`
- L294 _macro_ `#define SMOOTH_TOTAL_SAMPLE_TIME_DEFAULT (0.0083f)`

### `Plugins/EnhancedInput/Source/EnhancedInput/Public/InputTriggers.h` (Public)


#### enum `ETriggerState`  
`enum class ETriggerState : uint8`  
_L18-28_
- reflection: `UENUM()`
- desc: Trigger states are a light weight interpretation of the provided input values used in trigger UpdateState responses.
- L21 _public enumerator_ `None` — No inputs
- L24 _public enumerator_ `Ongoing` — Triggering is being monitored, but not yet been confirmed (e.g. a time based trigger that requires the trigger state to be maintained over several frames)
- L27 _public enumerator_ `Triggered` — The trigger state has been met

#### enum `ETriggerEvent`  
`enum class ETriggerEvent : uint8`  
_L34-56_
- reflection: `UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- desc: Trigger events are the Action's interpretation of all Trigger State transitions that occurred for the action in the last tick
- L37 _public enumerator_ `None = (0x0) UMETA(Hidden)` — No significant trigger state changes occurred and there are no active device inputs
- L39 _public enumerator_ `Triggered = (1 << 0)` — Triggering occurred after one or more processing ticks
- L42 _public enumerator_ `Started = (1 << 1)` — An event has occurred that has begun Trigger evaluation. Note: Triggered may also occur this frame, but this event will always be fired first.
- L46 _public enumerator_ `Ongoing = (1 << 2)` — Triggering is still being processed. For example, an action with a "Press and Hold" trigger will be "Ongoing" while the user is holding down the key but the time threshold has not been met yet.
- L50 _public enumerator_ `Canceled = (1 << 3)` — Triggering has been canceled. For example,  the user has let go of a key before the "Press and Hold" time threshold. The action has started to be evaluated, but never completed.
- L55 _public enumerator_ `Completed = (1 << 4)` — The trigger state has transitioned from Triggered to None this frame, i.e. Triggering has finished. Note: Using this event restricts you to one set of triggers for Started/Completed events. You may prefer two actions, each with its own trigger rules. Completed will not fire if any trigger reports Ongoing on the same frame, but both should fire. e.g. Tick 2 of Hold (= Ongoing) + Pressed (= None) combo will raise Ongoing event only.

#### enum `ETriggerType`  
`enum class ETriggerType : uint8`  
_L69-79_
- reflection: `UENUM()`
- desc: Trigger type determine how the trigger contributes to an action's overall trigger event the behavior of the trigger
- L72 _public enumerator_ `Explicit` — Input may trigger if any explicit trigger is triggered.
- L75 _public enumerator_ `Implicit` — Input may trigger only if all implicit triggers are triggered.
- L78 _public enumerator_ `Blocker` — Inverted trigger that will block all other triggers when IsBlocking returns true

#### enum `ETriggerEventsSupported`  
`enum class ETriggerEventsSupported : uint8`  
_L87-105_
- reflection: `UENUM()`
- desc: Represents what ETriggerEvent types can be triggered off of a give UInputTrigger. Used to determine if a warning should be placed on a exec pin that would never get called on a K2Node_EnhancedInputAction node
- L90 _public enumerator_ `None = (0x0)` — This trigger supports no trigger events.
- L93 _public enumerator_ `Instant = (1 << 0)` — This trigger supports just the Triggered event type. This include ETriggerEvent::Triggered
- L97 _public enumerator_ `Uninterruptible = (1 << 1)` — This trigger cannot be canceled, once it is started it cannot be stopped from being triggered This includes the ETriggerEvents of Started, Ongoing, and Triggered
- L101 _public enumerator_ `Ongoing = (1 << 2)` — This represents a trigger than can be held down and have a duration, and be canceled. This includes the ETriggerEvents of Started, Ongoing, Canceled, and Triggered.
- L104 _public enumerator_ `All = (Instant | Uninterruptible | Ongoing)` — This trigger supports all trigger events

#### class `UInputTrigger`  
`class UInputTrigger : public UObject`  
_L113-203_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable, EditInlineNew, CollapseCategories, Config = Input, defaultconfig, configdonotcheckdefaults)`
- inherits: `UObject`
- desc: Base class for building triggers. Transitions to Triggered state once the input meets or exceeds the actuation threshold.
- L122 _protected function_ `virtual ETriggerType GetTriggerType_Implementation() const` — Default implementations of overridable functionality. C++ trigger implementations should override these directly.
- L125 _protected prototype_ `virtual ETriggerState UpdateState_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue ModifiedValue, float DeltaTime);` — Triggers on actuation.
- L130 _public member_ `float ActuationThreshold = 0.5f;` — `UPROPERTY(EditAnywhere, Config, BlueprintReadWrite, Category = "Trigger Settings")` — Point at which this trigger fires
- L136 _public member_ `bool bShouldAlwaysTick = false;` — `UPROPERTY(Config, BlueprintReadOnly, Category = "Trigger Settings")` — Decides whether this trigger ticks every frame or not. This WILL affect performance and should only be used in specific custom triggers.
- L143 _public function_ `bool IsActuated(const FInputActionValue& ForValue) const` — `UFUNCTION(BlueprintCallable, Category="Trigger")` — Is the value passed in sufficiently large to be of interest to the trigger. This is a helper function that implements the most obvious (>=) interpretation of the actuation threshold.
- L147 _public member_ `FInputActionValue LastValue;` — `UPROPERTY(BlueprintReadOnly, Category = "Trigger Settings")` — Value passed to UpdateState on the previous tick. This will be updated automatically after the trigger is updated.
- L155 _public prototype_ `ETriggerType GetTriggerType() const;` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Trigger")` — Changes the way this trigger affects an action with multiple triggers: All implicit triggers must be triggering to trigger the action. If there are any explicit triggers at least one must be triggering to trigger the action.
- L164 _public prototype_ `ETriggerState UpdateState(const UEnhancedPlayerInput* PlayerInput, FInputActionValue ModifiedValue, float DeltaTime);` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Trigger")` — This function checks if the requisite conditions have been met for the trigger to fire. Returns Trigger State None		 - No trigger conditions have been met. Trigger is inactive. Trigger State Ongoing	 - Some trigger conditions have been met. Trigger is processing but not yet active. Trigger State Triggered - All trigger conditions have been met to fire. Trigger is active.
- L167 _public function_ `virtual ETriggerEventsSupported GetSupportedTriggerEvents() const` — Determines what kind of trigger events can happen from the behavior of this trigger.
- L172 _public prototype_ `static bool IsSupportedTriggerEvent(const ETriggerEventsSupported SupportedEvents, const ETriggerEvent Event);` — Returns true if the the ETriggerEvent is can be triggered based off of the ETriggerEventsSupported.
- L183 _public prototype_ `void OnTriggerReinstanced(const UInputTrigger* OldTrigger);` — Called during RebuildControlMappings when this trigger instance replaces an older instance of the same class. Transfers runtime state from the old trigger so that state-dependent triggers like Pressed don't see false transitions, and timed triggers don't restart. The old trigger is guaranteed to be the same class (verified by FEnhancedActionKeyMapping::Equals). This function copies LastValue, then dispatches to ReceiveTriggerReinstanced for subclass state.
- L193 _protected prototype_ `void ReceiveTriggerReinstanced(const UInputTrigger* OldTrigger);` — `UFUNCTION(BlueprintNativeEvent, Category = "Trigger")` — Override to transfer custom runtime state from a previous trigger instance of the same class. Called by OnTriggerReinstanced after LastValue has already been copied. Subclasses should call Super to ensure parent state is transferred.
- L194 _protected function_ `virtual void ReceiveTriggerReinstanced_Implementation(const UInputTrigger* OldTrigger)`
- L199 _public function_ `virtual bool IsBlocking(const ETriggerState State) const` — Returns true when all other triggers should be blocked, i.e. chords block when not triggered.
- L202 _public function_ `virtual FString GetDebugState() const` — Provide debug output for use with ShowDebug EnhancedInput. Return an empty string to disable display.

#### class `UInputTriggerTimedBase`  
`class UInputTriggerTimedBase : public UInputTrigger`  
_L212-248_
- reflection: `UCLASS(MinimalApi, Abstract, Config = Input)`
- inherits: `UInputTrigger`
- desc: Base class for building triggers that have firing conditions governed by elapsed time. This class transitions state to Ongoing once input is actuated, and will track Ongoing input time until input is released. Inheriting classes should provide the logic for Triggered transitions.
- L220 _protected member_ `float HeldDuration = 0.0f;` — `UPROPERTY(BlueprintReadWrite, Category = "Trigger Settings")` — How long have we been actuating this trigger?
- L223 _protected prototype_ `virtual ETriggerState UpdateState_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue ModifiedValue, float DeltaTime) override;` — Transitions to Ongoing on actuation. Never triggers.
- L226 _protected prototype_ `float CalculateHeldDuration(const UEnhancedPlayerInput* const PlayerInput, const float DeltaTime) const;` — Calculates the new held duration given the current player input and delta time
- L228 _protected prototype_ `virtual void ReceiveTriggerReinstanced_Implementation(const UInputTrigger* OldTrigger) override;`
- L232 _public function_ `virtual ETriggerEventsSupported GetSupportedTriggerEvents() const override`
- L245 _public member_ `bool bAffectedByTimeDilation = false;` — `UPROPERTY(EditAnywhere, Config, BlueprintReadWrite, Category = "Trigger Settings")` — Should global time dilation be applied to the held duration? Default is set to false. If this is set to true, then the owning Player Controller's actor time dilation will be used when calculating the HeldDuration. @see UInputTriggerTimedBase::CalculateHeldDuration @see AWorldSettings::GetEffectiveTimeDilation
- L247 _public function_ `virtual FString GetDebugState() const override`

#### class `UInputTriggerDown`  
`class UInputTriggerDown final : public UInputTrigger`  
_L262-272_
- reflection: `UCLASS(NotBlueprintable, MinimalAPI, meta = (DisplayName = "Down"))`
- inherits: `UInputTrigger`
- desc: UInputTriggerDown Trigger fires when the input exceeds the actuation threshold. Note: When no triggers are bound Down (with an actuation threshold of > 0) is the default behavior.
- L267 _public function_ `virtual ETriggerEventsSupported GetSupportedTriggerEvents() const override`
- L271 _protected prototype_ `virtual ETriggerState UpdateState_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue ModifiedValue, float DeltaTime) override;`

#### class `UInputTriggerPressed`  
`class UInputTriggerPressed final : public UInputTrigger`  
_L279-290_
- reflection: `UCLASS(NotBlueprintable, MinimalAPI, meta=(DisplayName="Pressed"))`
- inherits: `UInputTrigger`
- desc: UInputTriggerPressed Trigger fires once only when input exceeds the actuation threshold. Holding the input will not cause further triggers.
- L284 _public function_ `virtual ETriggerEventsSupported GetSupportedTriggerEvents() const override`
- L288 _protected prototype_ `virtual ETriggerState UpdateState_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue ModifiedValue, float DeltaTime) override;`
- L289 _protected function_ `virtual FString GetDebugState() const`

#### class `UInputTriggerReleased`  
`class UInputTriggerReleased final : public UInputTrigger`  
_L298-309_
- reflection: `UCLASS(NotBlueprintable, MinimalAPI, meta = (DisplayName = "Released"))`
- inherits: `UInputTrigger`
- desc: UInputTriggerReleased Trigger returns Ongoing whilst input exceeds the actuation threshold. Trigger fires once only when input drops back below actuation threshold.
- L303 _public function_ `virtual ETriggerEventsSupported GetSupportedTriggerEvents() const override`
- L307 _protected prototype_ `virtual ETriggerState UpdateState_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue ModifiedValue, float DeltaTime) override;`
- L308 _protected function_ `virtual FString GetDebugState() const`

#### class `UInputTriggerHold`  
`class UInputTriggerHold final : public UInputTriggerTimedBase`  
_L318-341_
- reflection: `UCLASS(NotBlueprintable, MinimalAPI, meta = (DisplayName = "Hold"))`
- inherits: `UInputTriggerTimedBase`
- desc: UInputTriggerHold Trigger fires once input has remained actuated for HoldTimeThreshold seconds. Trigger may optionally fire once, or repeatedly fire.
- L322 _private member_ `bool bTriggered = false;`
- L326 _protected prototype_ `virtual ETriggerState UpdateState_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue ModifiedValue, float DeltaTime) override;`
- L327 _protected prototype_ `virtual void ReceiveTriggerReinstanced_Implementation(const UInputTrigger* OldTrigger) override;`
- L330 _public function_ `virtual ETriggerEventsSupported GetSupportedTriggerEvents() const override`
- L334 _public member_ `float HoldTimeThreshold = 1.0f;` — `UPROPERTY(EditAnywhere, Config, BlueprintReadWrite, Category = "Trigger Settings", meta = (ClampMin = "0"))` — How long does the input have to be held to cause trigger?
- L338 _public member_ `bool bIsOneShot = false;` — `UPROPERTY(EditAnywhere, Config, BlueprintReadWrite, Category = "Trigger Settings")` — Should this trigger fire only once, or fire every frame once the hold time threshold is met?
- L340 _public function_ `virtual FString GetDebugState() const override`

#### class `UInputTriggerHoldAndRelease`  
`class UInputTriggerHoldAndRelease final : public UInputTriggerTimedBase`  
_L347-359_
- reflection: `UCLASS(NotBlueprintable, MinimalAPI, meta = (DisplayName = "Hold And Release"))`
- inherits: `UInputTriggerTimedBase`
- desc: UInputTriggerHoldAndRelease Trigger fires when input is released after having been actuated for at least HoldTimeThreshold seconds.
- L353 _protected prototype_ `virtual ETriggerState UpdateState_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue ModifiedValue, float DeltaTime) override;`
- L358 _public member_ `float HoldTimeThreshold = 0.5f;` — `UPROPERTY(EditAnywhere, Config, BlueprintReadWrite, Category = "Trigger Settings", meta = (ClampMin = "0"))` — How long does the input have to be held to cause trigger?

#### class `UInputTriggerTap`  
`class UInputTriggerTap final : public UInputTriggerTimedBase`  
_L365-379_
- reflection: `UCLASS(NotBlueprintable, MinimalAPI, meta = (DisplayName = "Tap"))`
- inherits: `UInputTriggerTimedBase`
- desc: UInputTriggerTap Input must be actuated then released within TapReleaseTimeThreshold seconds to trigger.
- L371 _protected prototype_ `virtual ETriggerState UpdateState_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue ModifiedValue, float DeltaTime) override;`
- L374 _public function_ `virtual ETriggerEventsSupported GetSupportedTriggerEvents() const override`
- L378 _public member_ `float TapReleaseTimeThreshold = 0.2f;` — `UPROPERTY(EditAnywhere, Config, BlueprintReadWrite, Category = "Trigger Settings", meta = (ClampMin = "0"))` — Release within this time-frame to trigger a tap

#### class `UInputTriggerRepeatedTap`  
`class UInputTriggerRepeatedTap : public UInputTriggerTimedBase`  
_L387-449_
- reflection: `UCLASS(NotBlueprintable, MinimalAPI, meta = (DisplayName = "Repeated Tap"))`
- inherits: `UInputTriggerTimedBase`
- desc: Fires the "Triggered" event upon a repeated taps of a key. Note: You can use this trigger to easily make a "Double Tap" effect.
- L392 _protected prototype_ `virtual ETriggerState UpdateState_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue ModifiedValue, float DeltaTime) override;`
- L393 _protected prototype_ `virtual FString GetDebugState() const override;`
- L396 _public prototype_ `UInputTriggerRepeatedTap();`
- L411 _public member_ `double RepeatDelay = 0.5;` — `UPROPERTY(EditAnywhere, Config, BlueprintReadWrite, Category="Trigger Settings", meta = (ClampMin = "0"))` — The max amount of time which can pass in between single taps that can pass and still be considered a repeat tap. For example: -> Single Key Tap (the first tap) -- -- ... Some time passes -- -> Another single key tap (the second tap) -- if (time passed <= RepeatDelay) then trigger repeat tap
- L419 _public member_ `int32 NumberOfTapsWhichTriggerRepeat = 2;` — `UPROPERTY(EditAnywhere, Config, BlueprintReadWrite, Category="Trigger Settings", meta = (ClampMin = "1"))` — The number of taps in a row it takes for this to be considered triggered. Note: To create a "Double tap" trigger, this value should be 2.
- L423 _public member_ `float TapReleaseTimeThreshold = 0.2f;` — `UPROPERTY(EditAnywhere, Config, BlueprintReadWrite, Category = "Trigger Settings", meta = (ClampMin = "0"))` — Release within this time-frame to trigger a tap
- L433 _protected member_ `double RepeatTime = 0.0;` — `UPROPERTY()` — This is the time at which we need to be <= on the next detection of a tap in order to be considered a double tap. This is set to (FPlatform::Seconds() + RepeatDelay) whenever we detect a tap
- L439 _protected member_ `int32 NumberOfTapsSinceLastTrigger = 0;` — `UPROPERTY()` — Tracks the number of individual taps that have occured since the last time we met
- L448 _protected member_ `bool bAwaitingRepeatTap = false;` — `UPROPERTY()` — True once we've detected a single tap and are still within the repeat window, waiting for the next tap. Keeps the trigger state Ongoing on idle frames between taps (the first tap doesn't increment NumberOfTapsSinceLastTrigger, so we need a separate flag to represent "a repeat sequence is in progress"). Cleared when the sequence triggers or is cancelled.

#### class `UInputTriggerPulse`  
`class UInputTriggerPulse final : public UInputTriggerTimedBase`  
_L457-484_
- reflection: `UCLASS(NotBlueprintable, MinimalAPI, meta = (DisplayName = "Pulse"))`
- inherits: `UInputTriggerTimedBase`
- desc: UInputTriggerPulse Trigger that fires at an Interval, in seconds, while input is actuated. Note:	Completed only fires when the repeat limit is reached or when input is released immediately after being triggered. Otherwise, Canceled is fired when input is released.
- L463 _private member_ `int32 TriggerCount = 0;`
- L467 _protected prototype_ `virtual ETriggerState UpdateState_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue ModifiedValue, float DeltaTime) override;`
- L468 _protected prototype_ `virtual void ReceiveTriggerReinstanced_Implementation(const UInputTrigger* OldTrigger) override;`
- L473 _public member_ `bool bTriggerOnStart = true;` — `UPROPERTY(EditAnywhere, Config, BlueprintReadWrite, Category = "Trigger Settings")` — Whether to trigger when the input first exceeds the actuation threshold or wait for the first interval?
- L477 _public member_ `float Interval = 1.0f;` — `UPROPERTY(EditAnywhere, Config, BlueprintReadWrite, Category = "Trigger Settings", meta = (ClampMin = "0"))` — How long between each trigger fire while input is held, in seconds?
- L481 _public member_ `int32 TriggerLimit = 0;` — `UPROPERTY(EditAnywhere, Config, BlueprintReadWrite, Category = "Trigger Settings", meta = (ClampMin = "0"))` — How many times can the trigger fire while input is held? (0 = no limit)
- L483 _public function_ `virtual FString GetDebugState() const override`

#### class `UInputTriggerChordAction`  
`class UInputTriggerChordAction : public UInputTrigger`  
_L494-514_
- reflection: `UCLASS(MinimalAPI, NotBlueprintable, meta = (DisplayName = "Chorded Action", NotInputConfigurable = "true"))`
- inherits: `UInputTrigger`
- desc: UInputTriggerChordAction Applies a chord action that must be triggering for this trigger's action to trigger
- L499 _public prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;`
- L504 _protected function_ `virtual ETriggerType GetTriggerType_Implementation() const override` — Implicit, so action cannot fire unless this is firing.
- L506 _protected prototype_ `virtual ETriggerState UpdateState_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue ModifiedValue, float DeltaTime) override;`
- L507 _protected function_ `virtual bool IsBlocking(const ETriggerState State) const override`
- L513 _public member_ `TObjectPtr<const UInputAction> ChordAction = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger Settings", meta = (DisplayThumbnail = "false"))` — The action that must be triggering for this trigger's action to trigger

#### class `UInputTriggerChordBlocker`  
`class UInputTriggerChordBlocker final : public UInputTriggerChordAction`  
_L521-527_
- reflection: `UCLASS(NotBlueprintable, MinimalAPI, HideDropdown)`
- inherits: `UInputTriggerChordAction`
- desc: UInputTriggerChordBlocker Automatically instantiated  to block mappings that are masked by a UInputTriggerChordAction chord from firing whilst the chording key is active. NOTE: Do not attempt to add these manually.
- L525 _protected function_ `virtual ETriggerType GetTriggerType_Implementation() const override`
- L526 _protected function_ `virtual bool IsBlocking(const ETriggerState State) const override`

#### struct `FInputComboStepData`  
`struct UE_DEPRECATED(5.8, "The Input combo trigger and related types are deprecated") FInputComboStepData`  
_L530-548_
- reflection: `USTRUCT(BlueprintType)`
- L536 _public member_ `TObjectPtr<const UInputAction> ComboStepAction = nullptr;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Trigger Settings", meta = (DisplayThumbnail = "false"))` — The action that must be completed (according to Combo Step Completion States) to progress the combo
- L540 _public member_ `uint8 ComboStepCompletionStates = static_cast<uint8>(ETriggerEvent::Triggered);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger Settings", config, meta = (Bitmask, BitmaskEnum="/Script/EnhancedInput.ETriggerEvent"))` — Trigger events that will complete this step - what events from this action should progress the combo
- L547 _public member_ `float TimeToPressKey = 0.5f;` — `UPROPERTY(EditAnywhere, Config, BlueprintReadWrite, Category = "Trigger Settings")` — Time to press the key before combo is cancelled - starts once the previous step in the combo is completed Note: This can be safely ignored for the first action in the combo

#### struct `FInputCancelAction`  
`struct UE_DEPRECATED(5.8, "The Input combo trigger and related types are deprecated") FInputCancelAction`  
_L551-562_
- reflection: `USTRUCT(BlueprintType)`
- L557 _public member_ `TObjectPtr<const UInputAction> CancelAction = nullptr;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Trigger Settings", meta = (DisplayThumbnail = "false"))` — The action that must be completed (according to Cancellation States) to cancel the combo
- L561 _public member_ `uint8 CancellationStates = static_cast<uint8>(ETriggerEvent::Triggered);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger Settings", config, meta = (Bitmask, BitmaskEnum="/Script/EnhancedInput.ETriggerEvent"))` — Trigger events for this action that will cancel the combo - what events from this action should cancel the combo

#### class `UInputTriggerCombo`  
`class UE_DEPRECATED(5.8, "UInputTriggerCombo has been deprecated.") UInputTriggerCombo final : public UInputTrigger`  
_L571-614_
- reflection: `UCLASS(MinimalAPI, NotBlueprintable, meta = (DisplayName = "Combo (Beta)", NotInputConfigurable = "true"))`
- inherits: `UInputTrigger`
- desc: UInputTriggerCombo All actions in the combo array must be completed (based on combo completion event specified - triggered, completed, etc.) to trigger the action this trigger is on. Actions must also be completed in the order specified by the combo actions array (starting at index 0). Note: This will only trigger for one frame before resetting the combo trigger's progress
- L575 _private prototype_ `UInputTriggerCombo();`
- L579 _protected function_ `virtual ETriggerType GetTriggerType_Implementation() const override` — Implicit, so action cannot fire unless this is firing.
- L581 _protected prototype_ `virtual ETriggerState UpdateState_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue ModifiedValue, float DeltaTime) override;`
- L585 _protected member_ `int32 CurrentComboStepIndex = 0;` — `UPROPERTY(BlueprintReadOnly, Category = "Trigger Settings")` — Keeps track of what action we're currently at in the combo
- L589 _protected member_ `float CurrentTimeBetweenComboSteps = 0.0f;` — `UPROPERTY(BlueprintReadOnly, Category = "Trigger Settings")` — Time elapsed between last combo InputAction trigger and current time
- L594 _public prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;`
- L604 _public member_ `TArray<FInputComboStepData> ComboActions;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger Settings", meta = (DisplayThumbnail = "false", TitleProperty = "ComboStepAction"))` — List of input actions that need to be completed (according to Combo Step Completion States) to trigger this action. Input actions must be triggered in order (starting at index 0) to count towards the triggering of the combo.
- L608 _public member_ `TArray<FInputCancelAction> InputCancelActions;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger Settings", meta = (DisplayThumbnail = "false", DisplayName = "Cancel Actions"))` — Actions that will cancel the combo if they are completed (according to Cancellation States)
- L613 _public function_ `virtual ETriggerEventsSupported GetSupportedTriggerEvents() const override` — Determines what kind of trigger events can happen from the behavior of this trigger.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ENHANCEDINPUT_API`
- L59 _namespace_ `namespace UE`
- L59 _namespace_ `namespace Input` (scope `UE`)
- L62 _prototype_ `FString LexToString(const ETriggerEvent TriggerEvent);` (scope `UE::Input`) — Returns an FString that represents the given ETriggerEvent

### `Plugins/EnhancedInput/Source/EnhancedInput/Public/PlayerMappableInputConfig.h` (Public)


#### class `UPlayerMappableInputConfig`  
`class UE_DEPRECATED(5.3, "UPlayerMappableInputConfig has been deprecated. Please use UEnhancedInputUserSettings instead.") UPlayerMappableInputConfig : public UPrimaryDataAsset`  
_L23-94_
- reflection: `UCLASS(BlueprintType, Meta = (DisplayName = "Player Mappable Input Config", ShortTooltip = "Data asset used to define a set of player mappable controller/keyboard mappings."))`
- inherits: `UPrimaryDataAsset`
- desc: UPlayerMappableInputConfig This represents one set of Player Mappable controller/keymappings. You can use this input config to create the default mappings for your player to start with in your game. It provides an easy way to get only the player mappable key actions, and it can be used to add multiple UInputMappingContext's at once to the player. Populate this data asset with Input Mapping Contexts that have player mappable actions in them.
- L27 _private prototype_ `UPlayerMappableInputConfig(const FObjectInitializer& ObjectInitializer);`
- L32 _public prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;`
- L36 _public prototype_ `void ForEachDefaultPlayerMappableKey(TFunctionRef<void(const FEnhancedActionKeyMapping&)> Operation) const;` — Iterate all the player mappable keys in this config in the default input mapping contexts
- L40 _public prototype_ `TArray<FEnhancedActionKeyMapping> GetPlayerMappableKeys() const;` — `UFUNCTION(BlueprintCallable, Category = "Input|PlayerMappable")` — Get all the player mappable keys in this config.
- L44 _public prototype_ `FEnhancedActionKeyMapping GetMappingByName(const FName MappingName) const;` — `UFUNCTION(BlueprintCallable, Category = "Input|PlayerMappable")` — Returns the action key mapping for the mapping that matches the given name
- L48 _public prototype_ `TArray<FEnhancedActionKeyMapping> GetKeysBoundToAction(const UInputAction* InAction) const;` — `UFUNCTION(BlueprintCallable, Category = "Input|PlayerMappable")` — Returns all the keys mapped to a specific Input Action in this mapping config.
- L52 _public prototype_ `void ResetToDefault();` — `UFUNCTION(BlueprintCallable, Category = "Input|PlayerMappable")` — Resets this mappable config to use the keys
- L58 _protected member_ `FName ConfigName;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|PlayerMappable")` — The unique name of this config that can be used when saving it
- L62 _protected member_ `FText ConfigDisplayName;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|PlayerMappable")` — The display name that can be used
- L66 _protected member_ `bool bIsDeprecated = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|PlayerMappable")` — A flag that can be used to mark this Input Config as deprecated to your player/designers.
- L70 _protected member_ `TObjectPtr<UObject> Metadata = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|PlayerMappable")` — Metadata that can used to store any other related items to your key mapping such as icons, ability assets, etc.
- L74 _protected member_ `TMap<TObjectPtr<UInputMappingContext>, int32> Contexts;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|PlayerMappable")` — Mapping contexts that make up this Input Config with their associated priority.
- L80 _public function_ `const TMap<TObjectPtr<UInputMappingContext>, int32>& GetMappingContexts() const` — `UFUNCTION(BlueprintCallable, Category = "Input|PlayerMappable")` — Return all the Input Mapping contexts that
- L83 _public function_ `const FName GetConfigName() const` — `UFUNCTION(BlueprintCallable, Category = "Input|PlayerMappable")`
- L86 _public function_ `const FText& GetDisplayName() const` — `UFUNCTION(BlueprintCallable, Category = "Input|PlayerMappable")`
- L89 _public function_ `const bool IsDeprecated() const` — `UFUNCTION(BlueprintCallable, Category = "Input|PlayerMappable")`
- L93 _public function_ `UObject* GetMetadata() const` — `UFUNCTION(BlueprintCallable, Category = "Input|PlayerMappable")` — Get all the player mappable keys in this config.

### `Plugins/EnhancedInput/Source/EnhancedInput/Public/PlayerMappableKeySettings.h` (Public)


#### class `UPlayerMappableKeySettings`  
`class UPlayerMappableKeySettings : public UObject`  
_L17-73_
- reflection: `UCLASS(MinimalAPI, DefaultToInstanced, EditInlineNew, DisplayName="Player Mappable Key Settings")`
- inherits: `UObject`
- desc: Hold setting information of an Action Input or a Action Key Mapping for setting screen and save purposes.
- L23 _public function_ `virtual FName MakeMappingName(const FEnhancedActionKeyMapping* OwningActionKeyMapping) const`
- L24 _public function_ `virtual FName GetMappingName() const`
- L27 _public prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;`
- L28 _public prototype_ `virtual void PostLoad() override;`
- L38 _public prototype_ `static const TArray<FName>& GetKnownMappingNames();` — `UFUNCTION()` — Get the known mapping names that are current in use. This is a helper function if you want to use a "GetOptions" metadata on a UPROPERTY. For example, the following will display a little drop down menu to select from all current mapping names: UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(GetOptions="EnhancedInput.PlayerMappableKeySettings.GetKnownMappingNames")) FName MappingName;
- L43 _public member_ `TObjectPtr<UObject> Metadata = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")` — Metadata that can used to store any other related items to this key mapping such as icons, ability assets, etc.
- L47 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")` — A unique name for this player mapping to be saved with.
- L51 _public member_ `FText DisplayName;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")` — The localized display name of this key mapping. Use this when displaying the mappings to a user.
- L55 _public member_ `FText DisplayCategory = FText::GetEmpty();` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")` — The category that this player mapping is in
- L64 _public member_ `FGameplayTagContainer SupportedKeyProfiles;` — `UE_DEPRECATED(5.6, "Use SupportedKeyProfileIds instead")` — `UPROPERTY()` — If this key mapping should only be added when a specific key profile is equipped, then set those here. If this is empty, then the key mapping will not be filtered out based on the current profile.
- L72 _public member_ `TArray<FString> SupportedKeyProfileIds;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")` — If this key mapping should only be added when a specific key profile is equipped, then set those here. If this is empty, then the key mapping will not be filtered out based on the current profile.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ENHANCEDINPUT_API`

### `Plugins/EnhancedInput/Source/EnhancedInput/Public/UserSettings/EnhancedInputUserSettings.h` (Public)


#### enum `EPlayerMappableKeySlot`  
`enum class EPlayerMappableKeySlot : uint8`  
_L30-47_
- reflection: `UENUM(BlueprintType)`
- desc: The "Slot" that a player mappable key is in. Used by UI to allow for multiple keys to be bound by the player for a single player mapping | <Mapping Name>  | Slot 1 | Slot 2 | Slot 3 | Slot.... N |
- L33 _public enumerator_ `First = 0` — The first key slot
- L36 _public enumerator_ `Second` — The second mappable key slot. This is the default max in the project settings
- L38 _public enumerator_ `Third`
- L39 _public enumerator_ `Fourth`
- L40 _public enumerator_ `Fifth`
- L41 _public enumerator_ `Sixth`
- L42 _public enumerator_ `Seventh`
- L45 _public enumerator_ `Unspecified` — A key that isn't in any slot
- L46 _public enumerator_ `Max`

#### struct `FMapPlayerKeyArgs`  
`struct FMapPlayerKeyArgs final`  
_L53-105_
- reflection: `USTRUCT(BlueprintType)`
- desc: Arguments that can be used when mapping a player key
- L58 _public prototype_ `FMapPlayerKeyArgs();`
- L59 _public prototype_ `~FMapPlayerKeyArgs() = default;`
- L60 _public prototype_ `FMapPlayerKeyArgs(const FMapPlayerKeyArgs&) = default;`
- L61 _public prototype_ `FMapPlayerKeyArgs(FMapPlayerKeyArgs&&) = default;`
- L62 _public prototype_ `FMapPlayerKeyArgs& operator=(const FMapPlayerKeyArgs&) = default;`
- L63 _public prototype_ `FMapPlayerKeyArgs& operator=(FMapPlayerKeyArgs&&) = default;`
- L71 _public member_ `FName MappingName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enhanced Input|User Settings")` — The name of the mapping for this key. This is either the default mapping name from an Input Action asset, or one that is overridden in the Input Mapping Context.
- L75 _public member_ `EPlayerMappableKeySlot Slot;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enhanced Input|User Settings")` — What slot this key mapping is for
- L79 _public member_ `FKey NewKey;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enhanced Input|User Settings")` — The new Key that this should be mapped to
- L83 _public member_ `FName HardwareDeviceId;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enhanced Input|User Settings", meta = (AllowPrivateAccess = true, GetOptions = "Engine.InputPlatformSettings.GetAllHardwareDeviceNames"))` — An OPTIONAL specifier about what kind of hardware this mapping is for.
- L88 _public member_ `FGameplayTag ProfileId;` — `UE_DEPRECATED(5.6, "Use ProfileIdString instead.")` — `UPROPERTY(meta=(DeprecatedProperty, DeprecationMessage="Use ProfileIdString instead."))` — The Key Mapping Profile identifier that this mapping should be set on. If this is empty, then the currently equipped profile will be used.
- L96 _public member_ `FString ProfileIdString;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enhanced Input|User Settings")` — The Key Mapping Profile identifier that this mapping should be set on. If this is empty, then the currently equipped profile will be used.
- L100 _public member_ `uint8 bCreateMatchingSlotIfNeeded : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enhanced Input|User Settings")` — If there is not a player mapping already with the same Slot and Hardware Device ID, then create a new mapping for this slot.
- L104 _public member_ `uint8 bDeferOnSettingsChangedBroadcast : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enhanced Input|User Settings")` — Defers setting changed delegates until the next frame if set to true.

#### struct `FPlayerKeyMapping`  
`struct FPlayerKeyMapping final`  
_L109-244_
- reflection: `USTRUCT(BlueprintType)`
- desc: Represents a single key mapping that is set by the player
- L116 _public prototype_ `FPlayerKeyMapping();`
- L118 _public prototype_ `FPlayerKeyMapping( const FEnhancedActionKeyMapping& OriginalMapping, EPlayerMappableKeySlot InSlot = EPlayerMappableKeySlot::Unspecified, const FHardwareDeviceIdentifier& InHardwareDevice = FHardwareDeviceIdentifier::Invalid);`
- L124 _public member_ `static FPlayerKeyMapping InvalidMapping;` — A static invalid player key mapping to be used for easy comparisons in blueprint
- L127 _public prototype_ `bool IsCustomized() const;` — Returns true if this mapping has been customized by the player, and false if it has not been.
- L130 _public prototype_ `bool IsValid() const;` — Returns true if this player mapping is valid
- L136 _public prototype_ `const FKey& GetCurrentKey() const;` — Returns the key that the player has mapped. If the player has not mapped one yet, then this returns the default key mapping from the input mapping context.
- L139 _public prototype_ `const FKey& GetDefaultKey() const;` — Returns the default key that this mapping is to
- L142 _public prototype_ `FString ToString() const;` — Print out some debug information about this player key mappings
- L148 _public prototype_ `const FName GetMappingName() const;` — The unique FName associated with this mapping. This is defined by this mappings owning Input Action or the individual Enhanced Action Key Mapping if it is overridden
- L151 _public prototype_ `const FText& GetDisplayName() const;` — The localized display name to use for this mapping
- L154 _public prototype_ `const FText& GetDisplayCategory() const;` — The localized display name for the category to use for this mapping
- L157 _public prototype_ `EPlayerMappableKeySlot GetSlot() const;` — Returns what player mappable slot this mapping is in
- L160 _public prototype_ `const FHardwareDeviceIdentifier& GetHardwareDeviceId() const;` — Returns the optional hardware device ID that this mapping is specific to
- L163 _public prototype_ `EHardwareDevicePrimaryType GetPrimaryDeviceType() const;` — Gets the primary device type associated with this key mapping. Taken from the HardwareDeviceId.
- L166 _public prototype_ `EHardwareDeviceSupportedFeatures::Type GetHardwareDeviceSupportedFeatures() const;` — Gets the supported hardware device feature flags associated with this key mapping. Taken from the HardwareDeviceId.
- L169 _public prototype_ `const UInputAction* GetAssociatedInputAction() const;` — Returns the input action asset associated with this player key mapping
- L172 _public prototype_ `void ResetToDefault();` — Resets the current mapping to the default one
- L175 _public prototype_ `void SetCurrentKey(const FKey& NewKey);` — Sets the value of the current key to the one given
- L178 _public prototype_ `void SetHardwareDeviceId(const FHardwareDeviceIdentifier& InDeviceId);` — Sets the value of the hardware device ID that this custom key mapping is associated with. This can be used to filter key mappings per input device
- L184 _public prototype_ `void UpdateDefaultKeyFromActionKeyMapping(const FEnhancedActionKeyMapping& OriginalMapping);` — Sets the Default Key on this mapping to that of the given ActionKeyMapping. Checks for customization of this key. This is for use during player key registration.
- L191 _public prototype_ `void UpdateMetadataFromActionKeyMapping(const FEnhancedActionKeyMapping& OriginalMapping);` — Updates the metadata properties on this player mapped key based on the given enhanced action mapping. This will populate the fields on this struct that are not editable by the player such as the localized display name and default key.
- L194 _public prototype_ `bool operator==(const FPlayerKeyMapping& Other) const;`
- L195 _public prototype_ `bool operator!=(const FPlayerKeyMapping& Other) const;`
- L196 _public prototype_ `FPlayerKeyMapping& operator=(FPlayerKeyMapping& Other);`
- L197 _public prototype_ `FPlayerKeyMapping& operator=(const FPlayerKeyMapping& Other);`
- L198 _public prototype_ `FPlayerKeyMapping(const FPlayerKeyMapping& Other);`
- L201 _public prototype_ `const bool IsDirty() const;` — Returns true if this mapping has been modified since it was registered from an IMC
- L207 _protected member_ `FName MappingName;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Enhanced Input|User Settings")` — The name of the mapping for this key
- L211 _protected member_ `FText DisplayName;` — `UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category="Enhanced Input|User Settings")` — Localized display name of this mapping
- L215 _protected member_ `FText DisplayCategory;` — `UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category="Enhanced Input|User Settings")` — Localized display category of this mapping
- L219 _protected member_ `EPlayerMappableKeySlot Slot;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Enhanced Input|User Settings")` — What slot this key is mapped to
- L223 _protected member_ `uint8 bIsDirty : 1;` — `UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category="Enhanced Input|User Settings")` — True if this key mapping is dirty (i.e. has been changed by the player)
- L227 _protected member_ `FKey DefaultKey;` — `UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category="Enhanced Input|User Settings", meta = (AllowPrivateAccess = "True"))` — The default key that this mapping was set to in its input mapping context
- L231 _protected member_ `FKey CurrentKey;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Enhanced Input|User Settings", meta = (AllowPrivateAccess = "True"))` — The key that the player has mapped to
- L235 _protected member_ `FHardwareDeviceIdentifier HardwareDeviceId;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Enhanced Input|User Settings")` — An optional Hardware Device specifier for this mapping
- L239 _protected member_ `TObjectPtr<const UInputAction> AssociatedInputAction;` — `UE_DEPRECATED(5.6, "This property is deprecated, use AssociatedInputActionSoft instead.")` — `UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category="Enhanced Input|User Settings", meta=(DeprecatedProperty, DeprecationMessage = "This property is deprecated, use AssociatedInputActionSoft instead."))`
- L243 _protected member_ `TSoftObjectPtr<const UInputAction> AssociatedInputActionSoft;` — `UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category="Enhanced Input|User Settings")` — The input action associated with this player key mapping

#### struct `FKeyMappingRow`  
`struct FKeyMappingRow final`  
_L253-262_
- reflection: `USTRUCT(BlueprintType)`
- desc: Stores all mappings bound to a single mapping name. Since a single mapping can have multiple bindings to it and this system should be Blueprint friendly, this needs to be a struct (blueprint don't support nested containers).
- L258 _public member_ `TSet<FPlayerKeyMapping> Mappings;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Enhanced Input|User Settings")`
- L261 _public prototype_ `bool HasAnyMappings() const;` — Returns true if this row has any mappings in it

#### struct `FPlayerMappableKeyQueryOptions`  
`struct FPlayerMappableKeyQueryOptions final`  
_L269-302_
- reflection: `USTRUCT(BlueprintType)`
- desc: Options when querying what keys are mapped to a specific action on the player mappable key profile.
- L273 _public prototype_ `FPlayerMappableKeyQueryOptions();`
- L277 _public member_ `FName MappingName;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Query Options")` — The mapping name to search for
- L281 _public member_ `FKey KeyToMatch;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Query Options")` — If specified, then this key will be used to match against when checking if the key types and axis are the same.
- L285 _public member_ `EPlayerMappableKeySlot SlotToMatch;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Query Options")` — The key slot that will be required to match if set. By default this is EPlayerMappableKeySlot::Unspecified, which will not filter by the slot at all.
- L289 _public member_ `uint8 bMatchBasicKeyTypes : 1;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Query Options")` — If true, then only keys that have the same value for IsGamepadKey, IsTouch, and IsGesture will be included in the results of this query
- L293 _public member_ `uint8 bMatchKeyAxisType : 1;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Query Options")` — If true, then only keys that have the same value of IsAxis1D, IsAxis2D, and IsAxis3D will be included in the results of this query
- L297 _public member_ `EHardwareDevicePrimaryType RequiredDeviceType;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Query Options")` — If set, then only player mappings whose hardware device identifier that has the same primary input device type will be included in the results of this query
- L301 _public member_ `int32 RequiredDeviceFlags;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Query Options", meta=(Bitmask, BitmaskEnum="/Script/Engine.EHardwareDeviceSupportedFeatures"))` — If set, then only player mappings whose Hardware Device Identifier that has the same flags as this will be included in the results

#### class `UEnhancedPlayerMappableKeyProfile`  
`class UEnhancedPlayerMappableKeyProfile : public UObject`  
_L306-460_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: Represents one "Profile" that a user can have for their player mappable keys
- L321 _public prototype_ `virtual void Serialize(FArchive& Ar) override final;` — Because the key mapping profile is serialized as a subobject of the UEnhancedInputUserSettings and requires some custom serialization logic, you should not override the Serialize method on your custom key profile. If you need to add custom serialization logic then you can create a struct UPROPERTY and override the struct's serialization logic, which will prevent you from running into possible issues with subobjects.
- L325 _public prototype_ `virtual void SetDisplayName(const FText& NewDisplayName);` — `UFUNCTION(BlueprintCallable, Category="Enhanced Input|User Settings")`
- L328 _public prototype_ `const FGameplayTag& GetProfileIdentifer() const;` — `UE_DEPRECATED(5.6, "Use GetProfileIdString instead")`
- L331 _public prototype_ `const FString& GetProfileIdString() const;` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category="Enhanced Input|User Settings")`
- L335 _public prototype_ `const FText& GetProfileDisplayName() const;` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category="Enhanced Input|User Settings")` — Get the localized display name for this profile
- L343 _public prototype_ `const TMap<FName, FKeyMappingRow>& GetPlayerMappingRows() const;` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category="Enhanced Input|User Settings")` — Get all known key mappings for this profile. This returns a map of "Mapping Name" -> Player Mappings to that name
- L347 _public prototype_ `void ResetMappingToDefault(UPARAM(Meta=(GetOptions="EnhancedInput.PlayerMappableKey` — `UFUNCTION(BlueprintCallable, Category="Enhanced Input|User Settings")` — Resets every player key mapping to this mapping back to it's default value
- L350 _public prototype_ `FKeyMappingRow* FindKeyMappingRowMutable(const FName InMappingName);` — Get all the key mappings associated with the given mapping name on this profile
- L353 _public prototype_ `const FKeyMappingRow* FindKeyMappingRow(const FName InMappingName) const;` — Get all the key mappings associated with the given mapping name on this profile
- L357 _public prototype_ `virtual void DumpProfileToLog() const;` — `UFUNCTION(BlueprintCallable, Category="Enhanced Input|User Settings")` — A helper function to print out all the current profile settings to the log.
- L361 _public prototype_ `virtual FString ToString() const;` — `UFUNCTION(BlueprintCallable, Category="Enhanced Input|User Settings")` — Returns a string that can be used to debug the current key mappings.
- L369 _public prototype_ `virtual int32 GetMappedKeysInRow(UPARAM(Meta=(GetOptions="EnhancedInput.PlayerMappableKeySettings.GetKnownMappingNames")) co` — `UFUNCTION(BlueprintCallable, Category="Enhanced Input|User Settings", meta = (ReturnDisplayName = "Number of keys"))` — Returns all FKey's bound to the given mapping Name on this profile. Returns the number of keys for the given mapping name
- L379 _public prototype_ `virtual int32 GetPlayerMappedKeysForRebuildControlMappings(const FEnhancedActionKeyMapping& DefaultMapping, TArray<FKey>& OutKeys) const;` — Called during IEnhancedInputSubsystemInterface::RebuildControlMappings, this provides your user settings the opportunity to decide what key mappings get added for a given FEnhancedActionKeyMapping, and applied to the player. Override this to change what query options are being used during the controls being rebuilt of enhanced input. If the given Out Array is empty, then the Default Mapping will be applied to the player, but no player mapped keys will be.
- L390 _public prototype_ `virtual int32 QueryPlayerMappedKeys(const FPlayerMappableKeyQueryOptions& Options, TArray<FKey>& OutKeys) const;` — `UFUNCTION(BlueprintCallable, Category="Enhanced Input|User Settings", meta = (ReturnDisplayName = "Number of mappings"))` — Populates the OutKeys array with any player mapped FKeys for the given default mapping. This is what IEnhancedInputSubsystemInterface::RebuildControlMappings calls to determine what keys should actually be applied when building the control mappings. Returns the number of player mapped keys to the given Default Mapping
- L398 _public prototype_ `virtual int32 GetMappingNamesForKey(const FKey& InKey, TArray<FName>& OutMappingNames) const;` — `UFUNCTION(BlueprintCallable, Category="Enhanced Input|User Settings", meta = (ReturnDisplayName = "Number of mappings"))` — Populates the OutMappedMappingNames with every mapping on this profile that has a mapping to the given key. Returns the number of mappings to this key
- L401 _public prototype_ `virtual FPlayerKeyMapping* FindKeyMapping(const FMapPlayerKeyArgs& InArgs) const;` — Returns a pointer to the player key mapping that fits with the given arguments. Returns null if none exist.
- L404 _public prototype_ `void K2_FindKeyMapping(FPlayerKeyMapping& OutKeyMapping, const FMapPlayerKeyArgs& InArgs) const;` — `UFUNCTION(BlueprintCallable, Category="Enhanced Input|User Settings", meta=(DisplayName="Find Key Mapping", AutoCreateRefTerm="OutKeyMapping"))`
- L410 _public prototype_ `virtual void ResetToDefault();` — `UFUNCTION(BlueprintCallable, Category="Enhanced Input|User Settings")` — Resets all the key mappings in this profile to their default value from their Input Mapping Context.
- L416 _public prototype_ `virtual bool DoesMappingPassQueryOptions(const FPlayerKeyMapping& PlayerMapping, const FPlayerMappableKeyQueryOptions& Options) const;` — `UFUNCTION(BlueprintCallable, Category="Enhanced Input|User Settings")` — Returns true if the given player key mapping passes the query filter provided.
- L427 _protected prototype_ `virtual void EquipProfile();` — Equips the current key profile. This will always be called after the previous key profile's UnEquip function. Make any changes to the given Enhanced Player input object that may be necessary for your custom profile. This function will only ever be called by UEnhancedInputUserSettings::SetKeyProfile.
- L435 _protected prototype_ `virtual void UnEquipProfile();` — UnEquips the current profile. Make any changes to the given Enhanced Player input object that may be necessary for your custom profile. This function will only ever be called by UEnhancedInputUserSettings::SetKeyProfile
- L440 _protected member_ `FGameplayTag ProfileIdentifier;` — `UE_DEPRECATED(5.6, "Use ProfileIdentifierString instead")` — `UPROPERTY(SaveGame, meta=(DeprecatedProperty, DeprecationMessage = "Use ProfileIdentifierString"))` — The ID of this profile. This can be used by each Key Mapping to filter down which profile is required for it be equipped.
- L444 _protected member_ `FString ProfileIdentifierString;` — `UPROPERTY(BlueprintReadOnly, SaveGame, EditAnywhere, Category="Enhanced Input|User Settings")` — The ID of this profile. This can be used by each Key Mapping to filter down which profile is required for it be equipped.
- L448 _protected member_ `FPlatformUserId OwningUserId;` — `UPROPERTY(Transient, BlueprintReadOnly, VisibleAnywhere, Category="Enhanced Input|User Settings")` — The platform user id of the owning Local Player of this profile.
- L452 _protected member_ `FText DisplayName;` — `UPROPERTY(BlueprintReadWrite, SaveGame, EditAnywhere, Category="Enhanced Input|User Settings")` — The localized display name of this profile
- L459 _protected member_ `TMap<FName, FKeyMappingRow> PlayerMappedKeys;` — `UPROPERTY(BlueprintReadOnly, Transient, EditAnywhere, Category="Enhanced Input|User Settings")` — A map of "Mapping Row Name" to all key mappings associated with it. Note: Dirty mappings will be serialized from UEnhancedInputUserSettings::Serialize

#### struct `FPlayerMappableKeyProfileCreationArgs`  
`struct FPlayerMappableKeyProfileCreationArgs final`  
_L464-499_
- reflection: `USTRUCT(BlueprintType)`
- desc: Arguments that can be used when creating a new mapping profile
- L469 _public prototype_ `FPlayerMappableKeyProfileCreationArgs();`
- L470 _public prototype_ `~FPlayerMappableKeyProfileCreationArgs() = default;`
- L471 _public prototype_ `FPlayerMappableKeyProfileCreationArgs(const FPlayerMappableKeyProfileCreationArgs&) = default;`
- L472 _public prototype_ `FPlayerMappableKeyProfileCreationArgs(FPlayerMappableKeyProfileCreationArgs&&) = default;`
- L473 _public prototype_ `FPlayerMappableKeyProfileCreationArgs& operator=(const FPlayerMappableKeyProfileCreationArgs&) = default;`
- L474 _public prototype_ `FPlayerMappableKeyProfileCreationArgs& operator=(FPlayerMappableKeyProfileCreationArgs&&) = default;`
- L478 _public member_ `TSubclassOf<UEnhancedPlayerMappableKeyProfile> ProfileType;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Enhanced Input|User Settings")`
- L483 _public member_ `FGameplayTag ProfileIdentifier;` — `UE_DEPRECATED(5.6, "Use ProfileStringIdentifier instead.")` — `UPROPERTY(meta=(DeprecatedProperty, DeprecationMessage="Use ProfileStringIdentifier instead."))` — The unique identifier that this profile should have
- L487 _public member_ `FString ProfileStringIdentifier;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Enhanced Input|User Settings")` — The unique identifier that this profile should have
- L491 _public member_ `FPlatformUserId UserId;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Enhanced Input|User Settings")` — The user ID of the ULocalPlayer that this profile is associated with
- L495 _public member_ `FText DisplayName;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Enhanced Input|User Settings")` — The display name of this profile
- L498 _public member_ `uint8 bSetAsCurrentProfile : 1;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Enhanced Input|User Settings")`

#### class `UEnhancedInputUserSettings`  
`class UEnhancedInputUserSettings : public USaveGame`  
_L516-913_
- reflection: `UCLASS(MinimalAPI, config=GameUserSettings, DisplayName="Enhanced Input User Settings", Category="Enhanced Input|User Settings")`
- inherits: `USaveGame`
- desc: The Enhanced Input User Settings class is a place where you can put all of your Input Related settings that you want your user to be able to change. Things like their key mappings, aim sensitivity, accessibility settings, etc. This also provides a Registration point for Input Mappings Contexts (IMC) from possibly unloaded plugins (i.e. Game Feature Plugins). You can register your IMC from a Game Feature Action plugin here, and then have access to all the key mappings available. This is very useful for building settings screens because you can now access all the mappings in your game, even if the entire plugin isn't loaded yet. The user settings are stored on each UEnhancedPlayerInput object, so each instance of the settings can represent a single User or Local Player. To customize this for your game, you can create a subclass of it and change the "UserSettingsClass" in the Enhanced Input Project Settings.
- L523 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L527 _public prototype_ `static UEnhancedInputUserSettings* LoadOrCreateSettings(ULocalPlayer* LP);` — Loads or creates new user settings for the owning local player of the given player input
- L528 _public prototype_ `virtual void Initialize(ULocalPlayer* LP);`
- L535 _public prototype_ `virtual void ApplySettings();` — `UFUNCTION(BlueprintCallable, Category="Enhanced Input|User Settings")` — Apply any custom input settings to your user. By default, this will just broadcast the OnSettingsApplied delegate which is a useful hook to maybe rebuild some UI or do other user facing updates.
- L542 _public prototype_ `virtual void SaveSettings();` — `UFUNCTION(BlueprintCallable, Category="Enhanced Input|User Settings")` — Synchronously save the settings to a hardcoded save game slot. This will work for simple games, but if you need to integrate it into an advanced save system you should Serialize this object out with the rest of your save data.
- L551 _public prototype_ `virtual void AsyncSaveSettings();` — `UFUNCTION(BlueprintCallable, Category="Enhanced Input|User Settings")` — Asynchronously save the settings to a hardcoded save game slot. This will work for simple games, but if you need to integrate it into an advanced save system you should Serialize this object out with the rest of your save data. OnAsyncSaveComplete will be called upon save completion.
- L560 _private prototype_ `void HandleSettingsClassChangedOnLoad(UEnhancedInputUserSettings* OldSettingsObject);` — Called when a save file is loaded from disk but has a different class then the one specified in the developer settings. @param OldSettingsObject Pointer to the old user settings object
- L569 _protected prototype_ `virtual void HandleSettingsClassChangedOnLoad_Impl(UEnhancedInputUserSettings* OldSettingsObject);` — Override this function to be notified of when the user settings class has changed. @param OldSettingsObject Pointer to the old user settings object
- L574 _protected prototype_ `static FString GetSaveFilename(const ULocalPlayer* LP);` — Returns the save file name to use when saving the settings file for the given local player
- L576 _protected prototype_ `virtual void OnAsyncSaveComplete(const FString& SlotName, const int32 UserIndex, bool bSuccess);`
- L589 _protected prototype_ `virtual void OnKeyMappingUpdated(FPlayerKeyMapping* ChangedMapping, const FMapPlayerKeyArgs& InArgs, const bool bIsBeingUnmapped);` — A virtual function that will be called whenever a player key mapping has been updated, before OnSettingsChanged is called. This provides subclasses the opportunity to modify this key mapping before any settings screens are updated This does nothing by default, but some subclasses may want to modify the mapping. Perhaps to change to a specific hardware device ID or something like that @param ChangedMapping	The key mapping that has changed @param InArgs			The arguments that were used to change this mapping. @param bIsBeingUnmapped	True if this key mapping is being unmapped. False if the key mapping is just being changed
- L605 _protected prototype_ `virtual void OnKeyMappingRegistered(FPlayerKeyMapping& RegisteredMapping, const FEnhancedActionKeyMapping& SourceMapping) final;` — `UE_DEPRECATED(5.7, "Use OnKeyMappingRegisteredToProfile instead.")` — A virtual function that will be called whenever a player key mapping is first registered. This will be called once by UEnhancedInputUserSettings::RegisterKeyMappingsToProfile for each mapping that is created from the Input Mapping Context. This is a good place to do any "Post Registration" setup you may want to for you key mappings such as changing the key that is mapped based on some other settings or data outside of this system (i.e. you are upgrading to this system and already had a key mapping system in place, you can set the key here!) This does nothing by default. @param RegisteredMapping		The newly registered player key mapping @param SourceMapping			The source mapping that the registered mapping was created from.
- L622 _protected prototype_ `virtual void OnKeyMappingRegisteredToProfile(UEnhancedPlayerMappableKeyProfile* Profile, FPlayerKeyMapping& RegisteredMapping, const FEnhancedActionKeyMapping& SourceMapping);` — A virtual function that will be called whenever a player key mapping is first registered. This will be called once by UEnhancedInputUserSettings::RegisterKeyMappingsToProfile for each mapping that is created from the Input Mapping Context. This is a good place to do any "Post Registration" setup you may want to for you key mappings such as changing the key that is mapped based on some other settings or data outside of this system (i.e. you are upgrading to this system and already had a key mapping system in place, you can set the key here!) This does nothing by default. @param Profile				The key profile which this mapping was registered to @param RegisteredMapping		The newly registered player key mapping @param SourceMapping			The source mapping that the registered mapping was created from.
- L626 _public prototype_ `ULocalPlayer* GetLocalPlayer() const;`
- L630 _protected member_ `FTimerHandle DeferredSettingsChangedTimerHandle;` — Used to track when a settings change callback has been deferred till the next frame.
- L634 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEnhancedInputUserSettingsChanged, UEnhancedInputUserSettings*, Settings);` — Fired when the user settings have changed, such as their key mappings.
- L636 _public member_ `FEnhancedInputUserSettingsChanged OnSettingsChanged;` — `UPROPERTY(BlueprintAssignable, Transient, Category = "Enhanced Input|User Settings")`
- L639 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEnhancedInputUserSettingsApplied);` — Called after the settings have been applied from the ApplySettings call.
- L641 _public member_ `FEnhancedInputUserSettingsApplied OnSettingsApplied;` — `UPROPERTY(BlueprintAssignable, Transient, Category = "Enhanced Input|User Settings")`
- L649 _public prototype_ `virtual void MapPlayerKey(const FMapPlayerKeyArgs& InArgs, FGameplayTagContainer& FailureReason);` — `UFUNCTION(BlueprintCallable, Category="Enhanced Input|User Settings", meta = (AutoCreateRefTerm = "FailureReason"))` — Sets the player mapped key on the current key profile.
- L655 _public prototype_ `virtual void UnMapPlayerKey(const FMapPlayerKeyArgs& InArgs, FGameplayTagContainer& FailureReason);` — `UFUNCTION(BlueprintCallable, Category="Enhanced Input|User Settings", meta = (AutoCreateRefTerm = "FailureReason"))` — Unmaps a single player mapping that matches the given Mapping name, slot, and hardware device.
- L665 _public prototype_ `virtual void ResetAllPlayerKeysInRow(const FMapPlayerKeyArgs& InArgs, FGameplayTagContainer& FailureReason);` — `UFUNCTION(BlueprintCallable, Category="Enhanced Input|User Settings", meta = (AutoCreateRefTerm = "FailureReason"))` — Resets each player mapped key to it's default value from the Input Mapping Context that it was registered from. If a key did not come from an IMC (i.e. it was added additionally by the player) then it will be reset to EKeys::Invalid. @param InArgs				Arguments that contain the mapping name and profile ID to find the mapping to reset. @param FailureReason		Populated with failure reasons if the operation fails.
- L675 _public prototype_ `virtual void ResetKeyProfileToDefault(const FGameplayTag& ProfileId, FGameplayTagContainer& FailureReason) final;` — `UE_DEPRECATED(5.6, "Use the version which takes an FString instead.")` — `UFUNCTION(BlueprintCallable, Category="Enhanced Input|User Settings", meta = (AutoCreateRefTerm = "FailureReason"))` — Resets the given key profile to default key mappings @param ProfileId		The ID of the key profile to reset @param FailureReason	Populated with failure reasons if the operation fails.
- L684 _public prototype_ `virtual void ResetKeyProfileIdToDefault(const FString& ProfileId, FGameplayTagContainer& FailureReason);` — `UFUNCTION(BlueprintCallable, Category="Enhanced Input|User Settings", meta = (AutoCreateRefTerm = "FailureReason"))` — Resets the given key profile to default key mappings @param ProfileId		The ID of the key profile to reset @param FailureReason	Populated with failure reasons if the operation fails.
- L688 _public prototype_ `virtual const TSet<FPlayerKeyMapping>& FindMappingsInRow(UPARAM(Meta=(GetOptions="EnhancedInput.PlayerMappableKeySett` — `UFUNCTION(BlueprintCallable, Category="Enhanced Input|User Settings")` — Returns a set of all player key mappings for the given mapping name.
- L691 _public prototype_ `virtual const FPlayerKeyMapping* FindCurrentMappingForSlot(const FName MappingName, const EPlayerMappableKeySlot InSlot) const;` — Returns the current player key mapping for the given row name in the given slot
- L694 _public prototype_ `const UInputAction* FindInputActionForMapping(const FName MappingName) const;` — Returns the Input Action associated with the given player mapping name
- L699 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMappableKeyProfileChanged, const UEnhancedPlayerMappableKeyProfile*, NewProfile);` — Fired when you equip a different key profile
- L701 _public member_ `FMappableKeyProfileChanged OnKeyProfileChanged;` — `UPROPERTY(BlueprintAssignable, Transient, Category = "Enhanced Input|User Settings")`
- L707 _public prototype_ `virtual bool SetKeyProfile(const FGameplayTag& InProfileId) final;` — `UE_DEPRECATED(5.6, "Use the version that takes an FString instead.")` — Changes the currently active key profile to the one with the given name. Returns true if the operation was successful.
- L713 _public prototype_ `virtual bool SetActiveKeyProfile(const FString& InProfileId);` — `UFUNCTION(BlueprintCallable, Category="Enhanced Input|User Settings", meta=(ReturnDisplayName = "Was Successful"))` — Changes the currently active key profile to the one with the given name. Returns true if the operation was successful.
- L719 _public prototype_ `bool SetKeyProfileToDefault();` — `UFUNCTION(BlueprintCallable, Category="Enhanced Input|User Settings", meta=(ReturnDisplayName = "Was Successful"))` — Changes the currently active key profile the default profile. Returns true if the operation was successful.
- L723 _public prototype_ `virtual const FGameplayTag& GetCurrentKeyProfileIdentifier() const final;` — `UE_DEPRECATED(5.6, "Use GetActiveKeyProfileId instead ")` — Gets the currently selected key profile
- L727 _public prototype_ `virtual const FString& GetActiveKeyProfileId() const;` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category="Enhanced Input|User Settings")` — Gets the currently selected key profile
- L731 _public prototype_ `UEnhancedPlayerMappableKeyProfile* GetCurrentKeyProfile() const;` — `UE_DEPRECATED(5.6, "Use GetActiveKeyProfile instead.")` — Get the current key profile that the user has set
- L735 _public prototype_ `UEnhancedPlayerMappableKeyProfile* GetActiveKeyProfile() const;` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category="Enhanced Input|User Settings")` — Get the currently active key profile that the user has set
- L739 _public function_ `template<class T> UE_DEPRECATED(5.6, "Use GetActiveKeyProfileAs instead.") inline T* GetCurrentKeyProfileAs() const` — Get the current key profile that the user has set
- L747 _public function_ `template<class T> inline T* GetActiveKeyProfileAs() const` — Get the current key profile that the user has set, casted to type T
- L755 _public prototype_ `const TMap<FGameplayTag, TObjectPtr<UEnhancedPlayerMappableKeyProfile>>& GetAllSavedKeyProfiles() const;` — `UE_DEPRECATED(5.6, "Use GetAllAvailableKeyProfiles instead.")` — Returns all player saved key profiles
- L758 _public prototype_ `const TMap<FString, TObjectPtr<UEnhancedPlayerMappableKeyProfile>>& GetAllAvailableKeyProfiles() const;` — Returns all player saved key profiles
- L761 _public prototype_ `bool IsKeyProfileAvailable(const FString& ProfileId) const;` — Returns true if the given ProfileId is currently available in the user settings.
- L767 _public prototype_ `UEnhancedPlayerMappableKeyProfile* GetDefaultKeyProfile() const;` — Returns a pointer to the default key profile created by Enhanced Input. This profile has an ID of "InputUserSettings.Profiles.Default"
- L773 _public prototype_ `virtual UEnhancedPlayerMappableKeyProfile* CreateNewKeyProfile(const FPlayerMappableKeyProfileCreationArgs& InArgs);` — `UFUNCTION(BlueprintCallable, Category="Enhanced Input|User Settings", meta = (DeterminesOutputType = "InArgs.ProfileType"))` — Creates a new profile with this name and type.
- L777 _public prototype_ `virtual UEnhancedPlayerMappableKeyProfile* GetKeyProfileWithIdentifier(const FGameplayTag& ProfileId) const final;` — `UE_DEPRECATED(5.6, "Use the version which takes an FString instead")` — Returns the key profile with the given name if one exists. Null if one doesn't exist
- L780 _public prototype_ `virtual UEnhancedPlayerMappableKeyProfile* GetKeyProfileWithId(const FString& ProfileId) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category="Enhanced Input|User Settings")`
- L785 _public function_ `inline T* GetKeyProfileWithIdentifierAs(const FGameplayTag& ProfileId) const` — `UE_DEPRECATED(5.6, "Use the version which takes an FString instead.")`
- L793 _public function_ `template<class T> inline T* GetKeyProfileWithIdAs(const FString& ProfileId) const` — Returns the key profile with the given name if one exists. Null if one doesn't exist
- L803 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMappingContextRegisteredWithSettings, const UInputMappingContext*, IMC);` — Fired when a new input mapping context is registered. Useful if you need to update your UI
- L804 _public member_ `FMappingContextRegisteredWithSettings OnMappingContextRegistered;`
- L811 _public prototype_ `virtual bool RegisterInputMappingContext(const UInputMappingContext* IMC);` — `UFUNCTION(BlueprintCallable, Category="Enhanced Input|User Settings")` — Registers this mapping context with the user settings. This will iterate all the key mappings in the context and create an initial Player Mappable Key for every mapping that is marked as mappable.
- L815 _public prototype_ `bool RegisterInputMappingContexts(const TSet<UInputMappingContext*>& MappingContexts);` — `UFUNCTION(BlueprintCallable, Category="Enhanced Input|User Settings")` — Registers multiple mapping contexts with the settings
- L819 _public prototype_ `virtual bool UnregisterInputMappingContext(const UInputMappingContext* IMC);` — `UFUNCTION(BlueprintCallable, Category="Enhanced Input|User Settings")` — Removes this mapping context from the registered mapping contexts
- L823 _public prototype_ `bool UnregisterInputMappingContexts(const TSet<UInputMappingContext*>& MappingContexts);` — `UFUNCTION(BlueprintCallable, Category="Enhanced Input|User Settings")` — Removes multiple mapping contexts from the registered mapping contexts
- L826 _public prototype_ `const TSet<TObjectPtr<const UInputMappingContext>>& GetRegisteredInputMappingContexts() const;` — Gets all the currently registered mapping contexts with the settings
- L830 _public prototype_ `bool IsMappingContextRegistered(const UInputMappingContext* IMC) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category="Enhanced Input|User Settings")` — Returns true if this mapping context is currently registered with the settings
- L833 _public prototype_ `void ShowDebugInfo(UCanvas* Canvas) const;` — Draw debug information on the screen for these user settings.
- L845 _protected prototype_ `bool RegisterInputMappingContextInternal(const UInputMappingContext* IMC);` — This will register the given IMC to the settings system. If an IMC specified mappings which should have different defaults based on a certain key profile ID, then we will also create the profile here if needed. This will do so regardless of if the IMC has been registered already.
- L856 _protected prototype_ `virtual bool RegisterKeyMappingsToProfile(UEnhancedPlayerMappableKeyProfile& Profile, const UInputMappingContext* IMC);` — This will register individual key mappings from the given Input Mapping context on the profile id. If the mappings exist on the profile already, then they will be updated based on the latest data from the IMC otherwise, they will be added as new FPlayerKeyMapping. This will be called for each key profile when users initially call RegisterInputMappingContext, and on load during Serialize to correctly populate a loaded profile with all the known registered IMC's mappings.
- L859 _protected function_ `virtual FHardwareDeviceIdentifier DetermineHardwareDeviceForActionMapping(const FEnhancedActionKeyMapping& ActionMapping) const final` — `UE_DEPRECATED(5.6, "Use DetermineHardwareDeviceForActionMapping which takes in a mapping context instead")`
- L871 _protected prototype_ `virtual FHardwareDeviceIdentifier DetermineHardwareDeviceForActionMapping(const FEnhancedActionKeyMapping& ActionMapping, const UInputMappingContext* IMC = nullptr) const;` — Determines the hardware device that an action key mapping is associated with. By default, the hardware will be FHardwareDeviceIdentifier::Invalid. Override this function if you wish to have Input Device Specific Player Key mappings. For example, specify hardware devices based on some metadata on the UPlayerMappableKeySettings of the action mapping, or infer a device based on the type of FKey it is.
- L877 _protected prototype_ `virtual void ShowDebugInfoInternal(UCanvas* Canvas) const;` — Provides a space for subclasses to add additional debug info if desired. By default, this will draw info about all player mapped keys.
- L882 _protected member_ `FGameplayTag CurrentProfileIdentifier;` — `UE_DEPRECATED(5.6, "Use the CurrentProfileIdentifierString instead.")` — `UPROPERTY(SaveGame, meta=(DeprecatedProperty))` — The current key profile that is equipped by the user.
- L888 _protected member_ `FString CurrentProfileIdentifierString;` — `UPROPERTY(SaveGame)` — The current key profile that is equipped by the user.
- L895 _protected member_ `TMap<FGameplayTag, TObjectPtr<UEnhancedPlayerMappableKeyProfile>> SavedKeyProfiles;` — `UE_DEPRECATED(5.6, "Use the CurrentProfileIdentifierString instead.")` — `UPROPERTY(Transient)` — All of the known Key Profiles for this user, including the currently active profile.
- L901 _protected member_ `TMap<FString, TObjectPtr<UEnhancedPlayerMappableKeyProfile>> SavedKeyProfilesMap;` — `UPROPERTY(Transient)` — All of the known Key Profiles for this user, including the currently active profile.
- L905 _protected member_ `TWeakObjectPtr<ULocalPlayer> OwningLocalPlayer;` — `UPROPERTY(Transient)` — The owning Local Player object of these settings
- L912 _protected member_ `TSet<TObjectPtr<const UInputMappingContext>> RegisteredMappingContexts;` — `UPROPERTY(Transient)` — Set of currently registered input mapping contexts that may not be currently active on the user, but you want to track for creating a menu for key mappings.

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API ENHANCEDINPUT_API`
- L49 _prototype_ `ENUM_RANGE_BY_FIRST_AND_LAST(EPlayerMappableKeySlot, EPlayerMappableKeySlot::First, EPlayerMappableKeySlot::Seventh);`
- L634 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEnhancedInputUserSettingsChanged, UEnhancedInputUserSettings*, Settings);` — Fired when the user settings have changed, such as their key mappings.
- L639 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEnhancedInputUserSettingsApplied);` — Called after the settings have been applied from the ApplySettings call.
- L699 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMappableKeyProfileChanged, const UEnhancedPlayerMappableKeyProfile*, NewProfile);` — Fired when you equip a different key profile
- L803 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMappingContextRegisteredWithSettings, const UInputMappingContext*, IMC);` — Fired when a new input mapping context is registered. Useful if you need to update your UI
