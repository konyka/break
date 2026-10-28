# Plugins / SceneStateTasks

- module root: `Plugins/VirtualProduction/SceneState/Source/SceneStateTasks`
- headers: 16; symbols: 181
- symbol kinds: delegate=1, function=10, macro=2, member=47, namespace=2, prototype=47, struct=53, typedef=19
- PrivateDependencyModuleNames: UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine, SceneState, SceneStateBinding

### `Plugins/VirtualProduction/SceneState/Source/SceneStateTasks/Public/Functions/SceneStateBooleanFunctions.h` (Public)


#### struct `FSceneStateBooleanOpFunctionInstance`  
`struct FSceneStateBooleanOpFunctionInstance`  
_L10-22_
- reflection: `USTRUCT()`
- desc: Function instance for all boolean operation functions involving two operands, left and right, and a result
- L15 _public member_ `bool bLeft = false;` — `UPROPERTY(EditAnywhere, Category="Math")`
- L18 _public member_ `bool bRight = false;` — `UPROPERTY(EditAnywhere, Category="Math")`
- L21 _public member_ `bool bOutput = false;` — `UPROPERTY(EditAnywhere, Category="Math", meta=(Output))`

#### struct `FSceneStateBooleanFunction`  
`struct FSceneStateBooleanFunction : public FSceneStateFunction`  
_L26-38_
- reflection: `USTRUCT(meta=(Hidden))`
- inherits: `FSceneStateFunction`
- desc: Base class for boolean operations where there are two operands, left and right, and a result
- L30 _public typedef_ `using FInstanceDataType = FSceneStateBooleanOpFunctionInstance;`
- L35 _protected prototype_ `virtual const UScriptStruct* OnGetFunctionDataType() const override;`

#### struct `FSceneStateBooleanAndFunction`  
`struct FSceneStateBooleanAndFunction : public FSceneStateBooleanFunction`  
_L42-50_
- reflection: `USTRUCT(DisplayName="And", Category="Math")`
- inherits: `FSceneStateBooleanFunction`
- desc: Performs boolean AND (Left AND Right)
- L48 _protected prototype_ `virtual void OnExecute(const FSceneStateExecutionContext& InContext, FStructView InFunctionInstance) const override;`

#### struct `FSceneStateBooleanOrFunction`  
`struct FSceneStateBooleanOrFunction : public FSceneStateBooleanFunction`  
_L54-62_
- reflection: `USTRUCT(DisplayName="Or", Category="Math")`
- inherits: `FSceneStateBooleanFunction`
- desc: Performs boolean OR (Left AND Right)
- L60 _protected prototype_ `virtual void OnExecute(const FSceneStateExecutionContext& InContext, FStructView InFunctionInstance) const override;`

#### struct `FSceneStateBooleanXorFunction`  
`struct FSceneStateBooleanXorFunction : public FSceneStateBooleanFunction`  
_L66-74_
- reflection: `USTRUCT(DisplayName="XOr", Category="Math")`
- inherits: `FSceneStateBooleanFunction`
- desc: Performs boolean XOR (Left XOR Right)
- L72 _protected prototype_ `virtual void OnExecute(const FSceneStateExecutionContext& InContext, FStructView InFunctionInstance) const override;`

#### struct `FSceneStateBooleanNotFunctionInstance`  
`struct FSceneStateBooleanNotFunctionInstance`  
_L78-87_
- reflection: `USTRUCT()`
- desc: Function instance the boolean NOT operation where only one input is required
- L83 _public member_ `bool bInput = false;` — `UPROPERTY(EditAnywhere, Category="Math")`
- L86 _public member_ `bool bOutput = false;` — `UPROPERTY(EditAnywhere, Category="Math", meta=(Output))`

#### struct `FSceneStateBooleanNotFunction`  
`struct FSceneStateBooleanNotFunction : public FSceneStateBooleanFunction`  
_L91-104_
- reflection: `USTRUCT(DisplayName="Not", Category="Math")`
- inherits: `FSceneStateBooleanFunction`
- desc: Performs boolean NOT
- L95 _public typedef_ `using FInstanceDataType = FSceneStateBooleanNotFunctionInstance;`
- L100 _protected prototype_ `virtual const UScriptStruct* OnGetFunctionDataType() const override;`
- L102 _protected prototype_ `virtual void OnExecute(const FSceneStateExecutionContext& InContext, FStructView InFunctionInstance) const override;`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateTasks/Public/Functions/SceneStateFloatFunctions.h` (Public)


#### struct `FSceneStateDoubleOpFunctionInstance`  
`struct FSceneStateDoubleOpFunctionInstance`  
_L10-22_
- reflection: `USTRUCT()`
- desc: Function instance for all double-precision float operation functions involving two operands, left and right, and a result
- L15 _public member_ `double Left = 0.0;` — `UPROPERTY(EditAnywhere, Category="Math")`
- L18 _public member_ `double Right = 0.0;` — `UPROPERTY(EditAnywhere, Category="Math")`
- L21 _public member_ `double Output = 0.0;` — `UPROPERTY(EditAnywhere, Category="Math", meta=(Output))`

#### struct `FSceneStateDoubleFunction`  
`struct FSceneStateDoubleFunction : public FSceneStateFunction`  
_L26-38_
- reflection: `USTRUCT(meta=(Hidden))`
- inherits: `FSceneStateFunction`
- desc: Base class for double-precision float operations where there are two operands, left and right, and a result
- L30 _public typedef_ `using FInstanceDataType = FSceneStateDoubleOpFunctionInstance;`
- L35 _protected prototype_ `virtual const UScriptStruct* OnGetFunctionDataType() const override;`

#### struct `FSceneStateAddDoubleFunction`  
`struct FSceneStateAddDoubleFunction : public FSceneStateDoubleFunction`  
_L42-50_
- reflection: `USTRUCT(DisplayName="Add", Category="Math")`
- inherits: `FSceneStateDoubleFunction`
- desc: Performs addition (Left + Right)
- L48 _protected prototype_ `virtual void OnExecute(const FSceneStateExecutionContext& InContext, FStructView InFunctionInstance) const override;`

#### struct `FSceneStateSubtractDoubleFunction`  
`struct FSceneStateSubtractDoubleFunction : public FSceneStateDoubleFunction`  
_L54-62_
- reflection: `USTRUCT(DisplayName="Subtract", Category="Math")`
- inherits: `FSceneStateDoubleFunction`
- desc: Performs subtraction (Left - Right)
- L60 _protected prototype_ `virtual void OnExecute(const FSceneStateExecutionContext& InContext, FStructView InFunctionInstance) const override;`

#### struct `FSceneStateMultiplyDoubleFunction`  
`struct FSceneStateMultiplyDoubleFunction : public FSceneStateDoubleFunction`  
_L66-74_
- reflection: `USTRUCT(DisplayName="Multiply", Category="Math")`
- inherits: `FSceneStateDoubleFunction`
- desc: Performs multiplication (Left * Right)
- L72 _protected prototype_ `virtual void OnExecute(const FSceneStateExecutionContext& InContext, FStructView InFunctionInstance) const override;`

#### struct `FSceneStateDivideDoubleFunction`  
`struct FSceneStateDivideDoubleFunction : public FSceneStateDoubleFunction`  
_L78-86_
- reflection: `USTRUCT(DisplayName="Divide", Category="Math")`
- inherits: `FSceneStateDoubleFunction`
- desc: Performs division (Left / Right)
- L84 _protected prototype_ `virtual void OnExecute(const FSceneStateExecutionContext& InContext, FStructView InFunctionInstance) const override;`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateTasks/Public/Functions/SceneStateFromStringFunctions.h` (Public)


#### struct `FSceneStateFromStringFunctionInstance`  
`struct FSceneStateFromStringFunctionInstance`  
_L10-16_
- reflection: `USTRUCT()`
- desc: Base function instance for all "FromString" functions
- L15 _public member_ `FString String;` — `UPROPERTY(EditAnywhere, Category="String")`

#### struct `FSceneStateTextFromStringFunctionInstance`  
`struct FSceneStateTextFromStringFunctionInstance : public FSceneStateFromStringFunctionInstance`  
_L22-28_
- reflection: `USTRUCT()`
- inherits: `FSceneStateFromStringFunctionInstance`
- L27 _public member_ `FText Output;` — `UPROPERTY(EditAnywhere, Category="String", meta=(Output))`

#### struct `FSceneStateTextFromStringFunction`  
`struct FSceneStateTextFromStringFunction : public FSceneStateFunction`  
_L31-47_
- reflection: `USTRUCT(DisplayName="String to Text", Category="String")`
- inherits: `FSceneStateFunction`
- L35 _public typedef_ `using FInstanceDataType = FSceneStateTextFromStringFunctionInstance;`
- L40 _protected function_ `virtual const UScriptStruct* OnGetFunctionDataType() const override`
- L45 _protected prototype_ `virtual void OnExecute(const FSceneStateExecutionContext& InContext, FStructView InFunctionInstance) const override;`

#### struct `FSceneStateNameFromStringFunctionInstance`  
`struct FSceneStateNameFromStringFunctionInstance : public FSceneStateFromStringFunctionInstance`  
_L53-59_
- reflection: `USTRUCT()`
- inherits: `FSceneStateFromStringFunctionInstance`
- L58 _public member_ `FName Output;` — `UPROPERTY(EditAnywhere, Category="String", meta=(Output))`

#### struct `FSceneStateNameFromStringFunction`  
`struct FSceneStateNameFromStringFunction : public FSceneStateFunction`  
_L62-78_
- reflection: `USTRUCT(DisplayName="String to Name", Category="String")`
- inherits: `FSceneStateFunction`
- L66 _public typedef_ `using FInstanceDataType = FSceneStateNameFromStringFunctionInstance;`
- L71 _protected function_ `virtual const UScriptStruct* OnGetFunctionDataType() const override`
- L76 _protected prototype_ `virtual void OnExecute(const FSceneStateExecutionContext& InContext, FStructView InFunctionInstance) const override;`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateTasks/Public/Functions/SceneStateIntegerFunctions.h` (Public)


#### struct `FSceneStateIntegerOpFunctionInstance`  
`struct FSceneStateIntegerOpFunctionInstance`  
_L10-22_
- reflection: `USTRUCT()`
- desc: Function instance for all integer operation functions involving two operands, left and right, and an integer result
- L15 _public member_ `int32 Left = 0;` — `UPROPERTY(EditAnywhere, Category="Math")`
- L18 _public member_ `int32 Right = 0;` — `UPROPERTY(EditAnywhere, Category="Math")`
- L21 _public member_ `int32 Output = 0;` — `UPROPERTY(EditAnywhere, Category="Math", meta=(Output))`

#### struct `FSceneStateIntegerFunction`  
`struct FSceneStateIntegerFunction : public FSceneStateFunction`  
_L26-38_
- reflection: `USTRUCT(meta=(Hidden))`
- inherits: `FSceneStateFunction`
- desc: Base class for integer operations where there are two operands, left and right, and an integer result
- L30 _public typedef_ `using FInstanceDataType = FSceneStateIntegerOpFunctionInstance;`
- L35 _protected prototype_ `virtual const UScriptStruct* OnGetFunctionDataType() const override;`

#### struct `FSceneStateAddIntegerFunction`  
`struct FSceneStateAddIntegerFunction : public FSceneStateIntegerFunction`  
_L42-50_
- reflection: `USTRUCT(DisplayName="Add", Category="Math")`
- inherits: `FSceneStateIntegerFunction`
- desc: Performs addition (Left + Right)
- L48 _protected prototype_ `virtual void OnExecute(const FSceneStateExecutionContext& InContext, FStructView InFunctionInstance) const override;`

#### struct `FSceneStateSubtractIntegerFunction`  
`struct FSceneStateSubtractIntegerFunction : public FSceneStateIntegerFunction`  
_L54-62_
- reflection: `USTRUCT(DisplayName="Subtract", Category="Math")`
- inherits: `FSceneStateIntegerFunction`
- desc: Performs subtraction (Left - Right)
- L60 _protected prototype_ `virtual void OnExecute(const FSceneStateExecutionContext& InContext, FStructView InFunctionInstance) const override;`

#### struct `FSceneStateMultiplyIntegerFunction`  
`struct FSceneStateMultiplyIntegerFunction : public FSceneStateIntegerFunction`  
_L66-74_
- reflection: `USTRUCT(DisplayName="Multiply", Category="Math")`
- inherits: `FSceneStateIntegerFunction`
- desc: Performs multiplication (Left * Right)
- L72 _protected prototype_ `virtual void OnExecute(const FSceneStateExecutionContext& InContext, FStructView InFunctionInstance) const override;`

#### struct `FSceneStateDivideIntegerFunction`  
`struct FSceneStateDivideIntegerFunction : public FSceneStateIntegerFunction`  
_L78-86_
- reflection: `USTRUCT(DisplayName="Divide", Category="Math")`
- inherits: `FSceneStateIntegerFunction`
- desc: Performs division (Left / Right)
- L84 _protected prototype_ `virtual void OnExecute(const FSceneStateExecutionContext& InContext, FStructView InFunctionInstance) const override;`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateTasks/Public/Functions/SceneStateStringFunctions.h` (Public)


#### struct `FSceneStateConcatenateStringFunctionInstance`  
`struct FSceneStateConcatenateStringFunctionInstance`  
_L9-21_
- reflection: `USTRUCT()`
- L14 _public member_ `FString Left;` — `UPROPERTY(EditAnywhere, Category="String")`
- L17 _public member_ `FString Right;` — `UPROPERTY(EditAnywhere, Category="String")`
- L20 _public member_ `FString Output;` — `UPROPERTY(EditAnywhere, Category="String", meta=(Output))`

#### struct `FSceneStateConcatenateStringFunction`  
`struct FSceneStateConcatenateStringFunction : public FSceneStateFunction`  
_L25-38_
- reflection: `USTRUCT(DisplayName="Concatenate String", Category="String")`
- inherits: `FSceneStateFunction`
- desc: Concatenates two strings (Left + Right) together
- L29 _public typedef_ `using FInstanceDataType = FSceneStateConcatenateStringFunctionInstance;`
- L34 _protected prototype_ `virtual const UScriptStruct* OnGetFunctionDataType() const override;`
- L36 _protected prototype_ `virtual void OnExecute(const FSceneStateExecutionContext& InContext, FStructView InFunctionInstance) const override;`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateTasks/Public/Functions/SceneStateToStringFunctions.h` (Public)


#### struct `FSceneStateToStringFunctionInstance`  
`struct FSceneStateToStringFunctionInstance`  
_L10-16_
- reflection: `USTRUCT()`
- desc: Base function instance for all "ToString" functions
- L15 _public member_ `FString Output;` — `UPROPERTY(EditAnywhere, Category="String", meta=(Output))`

#### struct `FSceneStateTextToStringFunctionInstance`  
`struct FSceneStateTextToStringFunctionInstance : public FSceneStateToStringFunctionInstance`  
_L22-28_
- reflection: `USTRUCT()`
- inherits: `FSceneStateToStringFunctionInstance`
- L27 _public member_ `FText Value;` — `UPROPERTY(EditAnywhere, Category="String")`

#### struct `FSceneStateTextToStringFunction`  
`struct FSceneStateTextToStringFunction : public FSceneStateFunction`  
_L31-47_
- reflection: `USTRUCT(DisplayName="Text to String", Category="String")`
- inherits: `FSceneStateFunction`
- L35 _public typedef_ `using FInstanceDataType = FSceneStateTextToStringFunctionInstance;`
- L40 _protected function_ `virtual const UScriptStruct* OnGetFunctionDataType() const override`
- L45 _protected prototype_ `virtual void OnExecute(const FSceneStateExecutionContext& InContext, FStructView InFunctionInstance) const override;`

#### struct `FSceneStateNameToStringFunctionInstance`  
`struct FSceneStateNameToStringFunctionInstance : public FSceneStateToStringFunctionInstance`  
_L53-59_
- reflection: `USTRUCT()`
- inherits: `FSceneStateToStringFunctionInstance`
- L58 _public member_ `FName Value;` — `UPROPERTY(EditAnywhere, Category="String")`

#### struct `FSceneStateNameToStringFunction`  
`struct FSceneStateNameToStringFunction : public FSceneStateFunction`  
_L62-78_
- reflection: `USTRUCT(DisplayName="Name to String", Category="String")`
- inherits: `FSceneStateFunction`
- L66 _public typedef_ `using FInstanceDataType = FSceneStateNameToStringFunctionInstance;`
- L71 _protected function_ `virtual const UScriptStruct* OnGetFunctionDataType() const override`
- L76 _protected prototype_ `virtual void OnExecute(const FSceneStateExecutionContext& InContext, FStructView InFunctionInstance) const override;`

#### struct `FSceneStateIntegerToStringFunctionInstance`  
`struct FSceneStateIntegerToStringFunctionInstance : public FSceneStateToStringFunctionInstance`  
_L84-90_
- reflection: `USTRUCT()`
- inherits: `FSceneStateToStringFunctionInstance`
- L89 _public member_ `int32 Value = 0;` — `UPROPERTY(EditAnywhere, Category="String")`

#### struct `FSceneStateIntegerToStringFunction`  
`struct FSceneStateIntegerToStringFunction : public FSceneStateFunction`  
_L93-109_
- reflection: `USTRUCT(DisplayName="Integer to String", Category="String")`
- inherits: `FSceneStateFunction`
- L97 _public typedef_ `using FInstanceDataType = FSceneStateIntegerToStringFunctionInstance;`
- L102 _protected function_ `virtual const UScriptStruct* OnGetFunctionDataType() const override`
- L107 _protected prototype_ `virtual void OnExecute(const FSceneStateExecutionContext& InContext, FStructView InFunctionInstance) const override;`

#### struct `FSceneStateDoubleToStringFunctionInstance`  
`struct FSceneStateDoubleToStringFunctionInstance : public FSceneStateToStringFunctionInstance`  
_L115-121_
- reflection: `USTRUCT()`
- inherits: `FSceneStateToStringFunctionInstance`
- L120 _public member_ `double Value = 0.0;` — `UPROPERTY(EditAnywhere, Category="String")`

#### struct `FSceneStateDoubleToStringFunction`  
`struct FSceneStateDoubleToStringFunction : public FSceneStateFunction`  
_L124-140_
- reflection: `USTRUCT(DisplayName="Float to String", Category="String")`
- inherits: `FSceneStateFunction`
- L128 _public typedef_ `using FInstanceDataType = FSceneStateDoubleToStringFunctionInstance;`
- L133 _protected function_ `virtual const UScriptStruct* OnGetFunctionDataType() const override`
- L138 _protected prototype_ `virtual void OnExecute(const FSceneStateExecutionContext& InContext, FStructView InFunctionInstance) const override;`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateTasks/Public/SceneStateDelayTask.h` (Public)


#### struct `FSceneStateDelayTaskInstance`  
`struct FSceneStateDelayTaskInstance : public FSceneStateTaskInstance`  
_L10-20_
- reflection: `USTRUCT()`
- inherits: `FSceneStateTaskInstance`
- L15 _public member_ `float ElapsedTime = 0.f;` — The amount of time elapsed
- L19 _public member_ `float Delay = 0.5f;` — `UPROPERTY(EditAnywhere, Category="Delay", meta=(ClampMin="0"))` — The amount to wait for, in seconds

#### struct `FSceneStateDelayTask`  
`struct FSceneStateDelayTask : public FSceneStateTask`  
_L24-40_
- reflection: `USTRUCT(DisplayName="Delay", Category="Utility", meta=(UtilityTask))`
- inherits: `FSceneStateTask`
- desc: Waits for a set amount of seconds
- L28 _public typedef_ `using FInstanceDataType = FSceneStateDelayTaskInstance;`
- L30 _public prototype_ `FSceneStateDelayTask();`
- L35 _protected prototype_ `virtual const UScriptStruct* OnGetTaskInstanceType() const override;`
- L37 _protected prototype_ `virtual void OnStart(const FSceneStateExecutionContext& InContext, FStructView InTaskInstance) const override;`
- L38 _protected prototype_ `virtual void OnTick(const FSceneStateExecutionContext& InContext, FStructView InTaskInstance, float InDeltaSeconds) const override;`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateTasks/Public/SceneStatePrintStringTask.h` (Public)


#### struct `FSceneStatePrintSettings`  
`struct FSceneStatePrintSettings`  
_L10-33_
- reflection: `USTRUCT()`
- L16 _public member_ `bool bPrintToLog = true;` — `UPROPERTY(EditAnywhere, Category="Print Settings")` — Whether to print the message to the console
- L20 _public member_ `bool bPrintToScreen = true;` — `UPROPERTY(EditAnywhere, Category="Print Settings")` — Whether to print the message to the screen
- L24 _public member_ `FLinearColor TextColor = FLinearColor(0.0f, 0.66f, 1.0f);` — `UPROPERTY(EditAnywhere, Category="Print Settings", meta=(EditCondition="bPrintToScreen", EditConditionHides))` — The color of the text to display
- L28 _public member_ `float Duration = 2.f;` — `UPROPERTY(EditAnywhere, Category="Print Settings", meta=(EditCondition="bPrintToScreen", EditConditionHides))` — the display duration. Using negative number will result in loading the duration time from the config
- L32 _public member_ `FName Key = NAME_None;` — `UPROPERTY(EditAnywhere, Category="Print Settings", meta=(EditCondition="bPrintToScreen", EditConditionHides))` — If a non-empty key is provided, the message will replace any existing on-screen messages with the same key

#### struct `FSceneStatePrintStringTaskInstance`  
`struct FSceneStatePrintStringTaskInstance : public FSceneStateTaskInstance`  
_L36-47_
- reflection: `USTRUCT()`
- inherits: `FSceneStateTaskInstance`
- L42 _public member_ `FString Message;` — `UPROPERTY(EditAnywhere, Category="Print Task")` — The message to print to screen/log
- L46 _public member_ `FSceneStatePrintSettings PrintSettings;` — `UPROPERTY(EditAnywhere, Category="Print Task")` — Additional settings for how to print the string

#### struct `FSceneStatePrintStringTask`  
`struct FSceneStatePrintStringTask : public FSceneStateTask`  
_L50-63_
- reflection: `USTRUCT(DisplayName="Print String", Category="Utility", meta=(UtilityTask))`
- inherits: `FSceneStateTask`
- L54 _public typedef_ `using FInstanceDataType = FSceneStatePrintStringTaskInstance;`
- L59 _protected prototype_ `virtual const UScriptStruct* OnGetTaskInstanceType() const override;`
- L61 _protected prototype_ `virtual void OnStart(const FSceneStateExecutionContext& InContext, FStructView InTaskInstance) const override;`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateTasks/Public/SceneStateSpawnActorTask.h` (Public)


#### struct `FSceneStateActorTemplate`  
`struct FSceneStateActorTemplate`  
_L18-25_
- reflection: `USTRUCT()`
- desc: Represents the actor template to use
- L24 _public member_ `TObjectPtr<AActor> Template;` — `UPROPERTY(VisibleAnywhere, Instanced, Category="Scene State")` — The actor template to use

#### struct `FSceneStateSpawnActorTaskInstance`  
`struct FSceneStateSpawnActorTaskInstance : public FSceneStateTaskInstance`  
_L28-47_
- reflection: `USTRUCT()`
- inherits: `FSceneStateTaskInstance`
- L34 _public member_ `FSceneStateActorTemplate ActorTemplate;` — `UPROPERTY(EditAnywhere, Category="Scene State", meta=(NoBindingSelfOnly))` — The actor template to use
- L38 _public member_ `FTransform SpawnTransform = FTransform::Identity;` — `UPROPERTY(EditAnywhere, Category="Scene State")` — The spawn transform for the actor
- L42 _public member_ `ESpawnActorCollisionHandlingMethod SpawnCollisionHandling = ESpawnActorCollisionHandlingMethod::Undefined;` — `UPROPERTY(EditAnywhere, Category="Scene State")` — Method for resolving collisions at the spawn point. Default (unspecified) means no override, use the actor's setting
- L46 _public member_ `FSceneStatePropertyReference SpawnedActor;` — `UPROPERTY(EditAnywhere, Category="Scene State", meta=(RefType="/Script/Engine.Actor"))` — Optional: Sets the actor that was spawned from this task

#### struct `FSceneStateSpawnActorTask`  
`struct FSceneStateSpawnActorTask : public FSceneStateTask`  
_L51-102_
- reflection: `USTRUCT(DisplayName="Spawn Actor", Category="Utility", meta=(UtilityTask, RequiresContextWorld))`
- inherits: `FSceneStateTask`
- desc: Spawns an actor of a given class
- L55 _public typedef_ `using FInstanceDataType = FSceneStateSpawnActorTaskInstance;`
- L60 _protected prototype_ `virtual const UScriptStruct* OnGetTaskInstanceType() const override;`
- L61 _protected prototype_ `virtual void OnPostTaskEditChange(UE::SceneState::FTaskEditChange& InEditChange, FStructView InTaskInstance) override;`
- L63 _protected prototype_ `virtual void OnStart(const FSceneStateExecutionContext& InContext, FStructView InTaskInstance) const override;`
- L68 _protected prototype_ `void UpdateActorTemplate(UObject* InOuter, FStructView InTaskInstance) const;` — Called to update the actor template from the task instance to match the current actor class
- L77 _protected prototype_ `void SetSpawnedActor(const FSceneStateExecutionContext& InContext, AActor* InSpawnedActor, const FSceneStatePropertyReference& InSpawnedActorReference) const;` — Updates the spawned actor reference value (if set) to the newly spawned actor @param InContext the execution context that is running this task @param InSpawnedActor the value to set the property reference to @param InSpawnedActorReference the actor property reference to set
- L85 _protected function_ `virtual bool ShouldSpawnActor(FStructView InTaskInstance, FText& OutErrorMessage) const` — Determines whether the actor should be spawned @param InTaskInstance data view to the task instance of the execution. @param OutErrorMessage the error message indicating why an actor should not be spawned. @return True if the actor should be spawned, false otherwise ideally accompanied by an error message.
- L95 _protected function_ `virtual void OnActorSpawned(AActor* InActorChecked, FStructView InTaskInstance) const` — Called after the actor has spawned for additional handling @param InActorChecked the spawned actor, already checked to be valid @param InTaskInstance data view to the task instance of the execution.
- L101 _protected member_ `TSubclassOf<AActor> ActorClass;` — `UPROPERTY(EditAnywhere, Category="Scene State")` — Actor class to spawn

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API SCENESTATETASKS_API`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateTasks/Public/SceneStateTasksLog.h` (Public)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSceneStateTasks, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSceneStateTasks, Log, All);`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateTasks/Public/Setters/SceneStateSetBoolTask.h` (Public)


#### struct `FSceneStateSetBoolTaskInstance`  
`struct FSceneStateSetBoolTaskInstance : public FSceneStateTaskInstance`  
_L11-22_
- reflection: `USTRUCT()`
- inherits: `FSceneStateTaskInstance`
- L17 _public member_ `FSceneStatePropertyReference Target;` — `UPROPERTY(EditAnywhere, Category="Setter", meta=(RefType="bool"))` — Target bool property to set
- L21 _public member_ `bool Value = false;` — `UPROPERTY(EditAnywhere, Category="Setter")` — The boolean value to set.

#### struct `FSceneStateSetBoolTask`  
`struct FSceneStateSetBoolTask : public FSceneStateTask`  
_L26-39_
- reflection: `USTRUCT(DisplayName="Set Boolean", Category="Setter", meta=(CoreTask))`
- inherits: `FSceneStateTask`
- desc: Sets a boolean value to the bound property reference
- L30 _public typedef_ `using FInstanceDataType = FSceneStateSetBoolTaskInstance;`
- L35 _protected prototype_ `virtual const UScriptStruct* OnGetTaskInstanceType() const override;`
- L37 _protected prototype_ `virtual void OnStart(const FSceneStateExecutionContext& InContext, FStructView InTaskInstance) const override;`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateTasks/Public/Setters/SceneStateSetFloatTask.h` (Public)


#### struct `FSceneStateSetFloatTaskInstance`  
`struct FSceneStateSetFloatTaskInstance : public FSceneStateTaskInstance`  
_L11-22_
- reflection: `USTRUCT()`
- inherits: `FSceneStateTaskInstance`
- L17 _public member_ `FSceneStatePropertyReference Target;` — `UPROPERTY(EditAnywhere, Category="Setter", meta=(RefType="double,float"))` — Target float property to set
- L21 _public member_ `double Value = 0.0;` — `UPROPERTY(EditAnywhere, Category="Setter")` — The float value to set

#### struct `FSceneStateSetFloatTask`  
`struct FSceneStateSetFloatTask : public FSceneStateTask`  
_L26-39_
- reflection: `USTRUCT(DisplayName="Set Float", Category="Setter", meta=(CoreTask))`
- inherits: `FSceneStateTask`
- desc: Sets a float value to the bound property reference
- L30 _public typedef_ `using FInstanceDataType = FSceneStateSetFloatTaskInstance;`
- L35 _protected prototype_ `virtual const UScriptStruct* OnGetTaskInstanceType() const override;`
- L37 _protected prototype_ `virtual void OnStart(const FSceneStateExecutionContext& InContext, FStructView InTaskInstance) const override;`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateTasks/Public/Setters/SceneStateSetIntegerTask.h` (Public)


#### struct `FSceneStateSetIntegerTaskInstance`  
`struct FSceneStateSetIntegerTaskInstance : public FSceneStateTaskInstance`  
_L11-22_
- reflection: `USTRUCT()`
- inherits: `FSceneStateTaskInstance`
- L17 _public member_ `FSceneStatePropertyReference Target;` — `UPROPERTY(EditAnywhere, Category="Setter", meta=(RefType="int32"))` — Target integer property to set
- L21 _public member_ `int32 Value = 0;` — `UPROPERTY(EditAnywhere, Category="Setter")` — The integer value to set.

#### struct `FSceneStateSetIntegerTask`  
`struct FSceneStateSetIntegerTask : public FSceneStateTask`  
_L26-39_
- reflection: `USTRUCT(DisplayName="Set Integer", Category="Setter", meta=(CoreTask))`
- inherits: `FSceneStateTask`
- desc: Sets a integer value to the bound property reference
- L30 _public typedef_ `using FInstanceDataType = FSceneStateSetIntegerTaskInstance;`
- L35 _protected prototype_ `virtual const UScriptStruct* OnGetTaskInstanceType() const override;`
- L37 _protected prototype_ `virtual void OnStart(const FSceneStateExecutionContext& InContext, FStructView InTaskInstance) const override;`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateTasks/Public/Setters/SceneStateSetStringTask.h` (Public)


#### struct `FSceneStateSetStringTaskInstance`  
`struct FSceneStateSetStringTaskInstance : public FSceneStateTaskInstance`  
_L11-22_
- reflection: `USTRUCT()`
- inherits: `FSceneStateTaskInstance`
- L17 _public member_ `FSceneStatePropertyReference Target;` — `UPROPERTY(EditAnywhere, Category="Setter", meta=(RefType="String"))` — Target string property to set
- L21 _public member_ `FString Value;` — `UPROPERTY(EditAnywhere, Category="Setter")` — The string value to set.

#### struct `FSceneStateSetStringTask`  
`struct FSceneStateSetStringTask : public FSceneStateTask`  
_L26-39_
- reflection: `USTRUCT(DisplayName="Set String", Category="Setter", meta=(CoreTask))`
- inherits: `FSceneStateTask`
- desc: Sets a string value to the bound property reference
- L30 _public typedef_ `using FInstanceDataType = FSceneStateSetStringTaskInstance;`
- L35 _protected prototype_ `virtual const UScriptStruct* OnGetTaskInstanceType() const override;`
- L37 _protected prototype_ `virtual void OnStart(const FSceneStateExecutionContext& InContext, FStructView InTaskInstance) const override;`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateTasks/Public/Setters/SceneStateSetTextTask.h` (Public)


#### struct `FSceneStateSetTextTaskInstance`  
`struct FSceneStateSetTextTaskInstance : public FSceneStateTaskInstance`  
_L11-22_
- reflection: `USTRUCT()`
- inherits: `FSceneStateTaskInstance`
- L17 _public member_ `FSceneStatePropertyReference Target;` — `UPROPERTY(EditAnywhere, Category="Setter", meta=(RefType="Text"))` — Target text property to set
- L21 _public member_ `FText Value;` — `UPROPERTY(EditAnywhere, Category="Setter")` — The text value to set.

#### struct `FSceneStateSetTextTask`  
`struct FSceneStateSetTextTask : public FSceneStateTask`  
_L26-39_
- reflection: `USTRUCT(DisplayName="Set Text", Category="Setter", meta=(CoreTask))`
- inherits: `FSceneStateTask`
- desc: Sets a text value to the bound property reference
- L30 _public typedef_ `using FInstanceDataType = FSceneStateSetTextTaskInstance;`
- L35 _protected prototype_ `virtual const UScriptStruct* OnGetTaskInstanceType() const override;`
- L37 _protected prototype_ `virtual void OnStart(const FSceneStateExecutionContext& InContext, FStructView InTaskInstance) const override;`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateTasks/Public/Setters/SceneStateSetterUtils.h` (Public)


#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SCENESTATETASKS_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace SceneState` (scope `UE`)
- L24 _prototype_ `bool CallValueSetter(uint8* InDestValuePtr, const FSceneStateBindingResolvedReference& InPropertyReference, const uint8* InSourceValuePtr, int32 InArrayIndex = 0);` (scope `UE::SceneState`) — Attempts to call the Dest Property's setter with a provided source value @param InDestValuePtr the value pointer to get the container ptr from (to pass back into FProperty::CallSetter) @param InPropertyReference the property reference describing the destination value ptr @param InSourceValuePtr pointer to the source data to copy from @param InArrayIndex the array index to set within the destination property (necessary if property has an Array Dim > 1, 0 otherwise) @return true if the setter call was made
- L45 _function_ `template<typename InTargetType, typename InValueType> bool SetValue(uint8* InDestValuePtr, const FSceneStateBindingResolvedReference& InPropertyReference, const InValueType& InValue)` (scope `UE::SceneState`) — Copies the provided value to the given destination address, calling a Setter if available @param InDestValuePtr pointer of the destination address to set @param InPropertyReference the property reference describing the destination value ptr @param InValue the value to copy from
- L67 _function_ `template<typename... InTargetTypes, CSetterTaskTypeable InTaskType> bool SetValue(const InTaskType& InTask, const FSceneStateExecutionContext& InContext, FStructView InTaskInstance)` (scope `UE::SceneState`) — Sets the Task Instance's value to the Task Instance's property reference @param InTask the FSceneStateTask object @param InContext the current execution context @param InTaskInstance view of the task instance data
