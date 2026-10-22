# Plugins / GameplayInteractionsModule

- module root: `Plugins/Runtime/GameplayInteractions/Source/GameplayInteractionsModule`
- headers: 19; symbols: 410
- symbol kinds: class=5, delegate=1, enum=9, enumerator=29, externvar=5, function=58, macro=3, member=129, namespace=6, prototype=116, struct=34, typedef=15
- PublicDependencyModuleNames: AIModule, ContextualAnimation, Core, CoreUObject, Engine, GameplayStateTreeModule, GameplayTags, GameplayTasks, NavCorridor, NavigationSystem, SmartObjectsModule, StateTreeModule

### `Plugins/Runtime/GameplayInteractions/Source/GameplayInteractionsModule/Private/AI/AITask_UseGameplayInteraction.h` (Private)


#### class `UAITask_UseGameplayInteraction`  
`class UAITask_UseGameplayInteraction : public UAITask`  
_L17-88_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAITask`
- L22 _public prototype_ `explicit UAITask_UseGameplayInteraction(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L33 _public prototype_ `static UAITask_UseGameplayInteraction* UseSmartObjectWithGameplayInteraction(AAIController* Controller, FSmartObjectClaimHandle ClaimHandle, bool bLockAILogic = true);` — `UFUNCTION(BlueprintCallable, Category = "AI|Tasks", meta = (DefaultToSelf = "Controller" , BlueprintInternalUseOnly = "true"))` — Helper function to create an AITask that interacts with the SmartObject slot using the GameplayInteraction definition. This version will start the interaction on spot so the actor needs to be at the desired position. @param Controller The controller that (or its attached pawn if available) will take part to the interaction. @param ClaimHandle The handle to an already claimed slot. @param bLockAILogic Indicates if the task adds UAIResource_Logic to the set of Claimed resources @return The AITask executing the GameplayInteraction.
- L43 _public prototype_ `static UAITask_UseGameplayInteraction* MoveToAndUseSmartObjectWithGameplayInteraction(AAIController* Controller, FSmartObjectClaimHandle ClaimHandle, bool bLockAILogic = true);` — `UFUNCTION(BlueprintCallable, Category = "AI|Tasks", meta = (DefaultToSelf = "Controller" , BlueprintInternalUseOnly = "true"))` — Helper function to create an AITask that reaches and interacts with the SmartObject slot using the GameplayInteraction definition @param Controller The controller that will move to the slot location and that will (or its attached pawn if available) take part to the interaction. @param ClaimHandle The handle to an already claimed slot. @param bLockAILogic Indicates if the task adds UAIResource_Logic to the set of Claimed resources @return The AITask executing the move and the interaction.
- L46 _public prototype_ `void RequestAbort();` — `UFUNCTION(BlueprintCallable, Category = "AI|Tasks")`
- L48 _public function_ `void SetShouldReachSlotLocation(const bool bUseMoveTo)`
- L49 _public function_ `void SetClaimHandle(const FSmartObjectClaimHandle& Handle)`
- L52 _protected prototype_ `virtual void Activate() override;`
- L53 _protected prototype_ `virtual void TickTask(float DeltaTime) override;`
- L54 _protected prototype_ `virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) override;`
- L55 _protected prototype_ `virtual void OnDestroy(bool bInOwnerFinished) override;`
- L57 _protected prototype_ `bool StartInteraction();`
- L58 _protected prototype_ `void OnSlotInvalidated(const FSmartObjectClaimHandle& ClaimHandle, const ESmartObjectSlotState State);`
- L59 _protected prototype_ `void Abort(EGameplayInteractionAbortReason Reason);`
- L62 _protected member_ `FGenericGameplayTaskDelegate OnFinished;` — `UPROPERTY(BlueprintAssignable)`
- L65 _protected member_ `FGenericGameplayTaskDelegate OnSucceeded;` — `UPROPERTY(BlueprintAssignable)`
- L68 _protected member_ `FGenericGameplayTaskDelegate OnFailed;` — `UPROPERTY(BlueprintAssignable)`
- L71 _protected member_ `FGenericGameplayTaskDelegate OnMoveToFailed;` — `UPROPERTY(BlueprintAssignable)`
- L74 _protected member_ `FGameplayInteractionContext GameplayInteractionContext;` — `UPROPERTY()`
- L77 _protected member_ `TObjectPtr<UAITask_MoveTo> MoveToTask;` — `UPROPERTY()`
- L80 _protected member_ `FSmartObjectClaimHandle ClaimedHandle;` — `UPROPERTY()`
- L83 _protected member_ `FGameplayInteractionAbortContext AbortContext;` — `UPROPERTY()`
- L85 _protected member_ `bool bInteractionCompleted;`
- L87 _protected member_ `bool bShouldUseMoveTo;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEPLAYINTERACTIONSMODULE_API`

### `Plugins/Runtime/GameplayInteractions/Source/GameplayInteractionsModule/Private/StateTree/GameplayInteractionConditions.h` (Private)


#### enum `EGameplayInteractionMatchSlotTagSource`  
`enum class EGameplayInteractionMatchSlotTagSource : uint8`  
_L11-18_
- reflection: `UENUM()`
- L14 _public enumerator_ `ActivityTags` — Test slot definition activity Tags.
- L17 _public enumerator_ `RuntimeTags` — Test slot Runtime tags.

#### struct `FGameplayInteractionMatchSlotTagsConditionInstanceData`  
`struct FGameplayInteractionMatchSlotTagsConditionInstanceData`  
_L21-30_
- reflection: `USTRUCT()`
- L26 _public member_ `FSmartObjectSlotHandle Slot;` — `UPROPERTY(EditAnywhere, Category = "Input")`
- L29 _public member_ `FGameplayTagContainer TagsToMatch;` — `UPROPERTY(EditAnywhere, Category = "Parameter")`

#### struct `FGameplayInteractionSlotTagsMatchCondition`  
`struct FGameplayInteractionSlotTagsMatchCondition : public FGameplayInteractionStateTreeCondition`  
_L36-73_
- reflection: `USTRUCT(DisplayName="Match Slot Tags", Category="Gameplay Interactions|Smart Object")`
- inherits: `FGameplayInteractionStateTreeCondition`
- desc: Condition to check if Gameplay Tags on a Smart Object slot match the specified tags.
- L40 _public typedef_ `using FInstanceDataType = FGameplayInteractionMatchSlotTagsConditionInstanceData;`
- L42 _public prototype_ `FGameplayInteractionSlotTagsMatchCondition() = default;`
- L44 _public prototype_ `virtual bool Link(FStateTreeLinker& Linker) override;`
- L45 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L46 _public prototype_ `virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;`
- L48 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;`
- L49 _public function_ `virtual FName GetIconName() const override`
- L53 _public function_ `virtual FColor GetIconColor() const override`
- L60 _public member_ `EGameplayInteractionMatchSlotTagSource Source = EGameplayInteractionMatchSlotTagSource::RuntimeTags;` — `UPROPERTY(EditAnywhere, Category = "Condition")`
- L63 _public member_ `EGameplayContainerMatchType MatchType = EGameplayContainerMatchType::Any;` — `UPROPERTY(EditAnywhere, Category = "Condition")`
- L66 _public member_ `bool bExactMatch = false;` — `UPROPERTY(EditAnywhere, Category = "Condition")`
- L69 _public member_ `bool bInvert = false;` — `UPROPERTY(EditAnywhere, Category = "Condition")`
- L72 _public member_ `TStateTreeExternalDataHandle<USmartObjectSubsystem> SmartObjectSubsystemHandle;` — Handle to retrieve USmartObjectSubsystem.

#### struct `FGameplayInteractionQuerySlotTagsConditionInstanceData`  
`struct FGameplayInteractionQuerySlotTagsConditionInstanceData`  
_L77-83_
- reflection: `USTRUCT()`
- L82 _public member_ `FSmartObjectSlotHandle Slot;` — `UPROPERTY(EditAnywhere, Category = "Input")`

#### struct `FGameplayInteractionQuerySlotTagCondition`  
`struct FGameplayInteractionQuerySlotTagCondition : public FGameplayInteractionStateTreeCondition`  
_L89-123_
- reflection: `USTRUCT(DisplayName="Query Slot Tags", Category="Gameplay Interactions|Smart Object")`
- inherits: `FGameplayInteractionStateTreeCondition`
- desc: Condition to check if Gameplay Tags on a Smart Object slot match the Gameplay Tag query.
- L93 _public typedef_ `using FInstanceDataType = FGameplayInteractionQuerySlotTagsConditionInstanceData;`
- L95 _public prototype_ `FGameplayInteractionQuerySlotTagCondition() = default;`
- L97 _public prototype_ `virtual bool Link(FStateTreeLinker& Linker) override;`
- L98 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L99 _public prototype_ `virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;`
- L101 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;`
- L102 _public function_ `virtual FName GetIconName() const override`
- L106 _public function_ `virtual FColor GetIconColor() const override`
- L113 _public member_ `EGameplayInteractionMatchSlotTagSource Source = EGameplayInteractionMatchSlotTagSource::RuntimeTags;` — `UPROPERTY(EditAnywhere, Category = "Condition")`
- L116 _public member_ `FGameplayTagQuery TagQuery;` — `UPROPERTY(EditAnywhere, Category = "Condition")`
- L119 _public member_ `bool bInvert = false;` — `UPROPERTY(EditAnywhere, Category = "Condition")`
- L122 _public member_ `TStateTreeExternalDataHandle<USmartObjectSubsystem> SmartObjectSubsystemHandle;` — Handle to retrieve USmartObjectSubsystem.

#### struct `FGameplayInteractionIsSlotHandleValidConditionInstanceData`  
`struct FGameplayInteractionIsSlotHandleValidConditionInstanceData`  
_L126-132_
- reflection: `USTRUCT()`
- L131 _public member_ `FSmartObjectSlotHandle Slot;` — `UPROPERTY(EditAnywhere, Category="Input")`

#### struct `FGameplayInteractionIsSlotHandleValidCondition`  
`struct FGameplayInteractionIsSlotHandleValidCondition : public FGameplayInteractionStateTreeCondition`  
_L138-158_
- reflection: `USTRUCT(DisplayName="Is Slot Handle Valid", Category="Gameplay Interactions|Smart Object")`
- inherits: `FGameplayInteractionStateTreeCondition`
- desc: Condition to check if a Smart Object slot handle is valid.
- L142 _public typedef_ `using FInstanceDataType = FGameplayInteractionIsSlotHandleValidConditionInstanceData;`
- L144 _public prototype_ `FGameplayInteractionIsSlotHandleValidCondition() = default;`
- L146 _public prototype_ `virtual bool Link(FStateTreeLinker& Linker) override;`
- L147 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L148 _public prototype_ `virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;`
- L150 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;`
- L154 _public member_ `bool bInvert = false;` — `UPROPERTY(EditAnywhere, Category = "Condition")`
- L157 _public member_ `TStateTreeExternalDataHandle<USmartObjectSubsystem> SmartObjectSubsystemHandle;` — Handle to retrieve USmartObjectSubsystem.

### `Plugins/Runtime/GameplayInteractions/Source/GameplayInteractionsModule/Private/StateTree/GameplayInteractionFindSlotTask.h` (Private)


#### enum `EGameplayInteractionSlotReferenceType`  
`enum class EGameplayInteractionSlotReferenceType : uint8`  
_L11-18_
- reflection: `UENUM()`
- L14 _public enumerator_ `ByActivityTag` — Consider all slots on the Reference Slot's Smart Object. Match by activity tag.
- L17 _public enumerator_ `ByLinkTag` — Consider slots linked via Link Annotations on Reference Slot. Match by link's tag.

#### struct `FGameplayInteractionFindSlotTaskInstanceData`  
`struct FGameplayInteractionFindSlotTaskInstanceData`  
_L21-32_
- reflection: `USTRUCT()`
- L27 _public member_ `FSmartObjectSlotHandle ReferenceSlot;` — `UPROPERTY(EditAnywhere, Category="Input")` — Slot to use as reference to find the result slot.
- L31 _public member_ `FSmartObjectSlotHandle ResultSlot;` — `UPROPERTY(EditAnywhere, Category="Output")` — Result slot.

#### struct `FGameplayInteractionFindSlotTask`  
`struct FGameplayInteractionFindSlotTask : public FGameplayInteractionStateTreeTask`  
_L41-78_
- reflection: `USTRUCT(meta = (DisplayName = "Find Slot", Category="Gameplay Interactions|Smart Object"))`
- inherits: `FGameplayInteractionStateTreeTask`
- desc: Task to find a Smart Object slot based on a reference slot. The search can look up slots in the whole Smart Object based on Activity tags, or use Smart Object Slot Link annotations on the reference slot.
- L45 _public prototype_ `FGameplayInteractionFindSlotTask();`
- L47 _public typedef_ `using FInstanceDataType = FGameplayInteractionFindSlotTaskInstanceData;`
- L50 _protected function_ `virtual const UStruct* GetInstanceDataType() const override`
- L52 _protected prototype_ `virtual bool Link(FStateTreeLinker& Linker) override;`
- L53 _protected prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L55 _protected prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;`
- L56 _protected function_ `virtual FName GetIconName() const override`
- L60 _protected function_ `virtual FColor GetIconColor() const override`
- L66 _protected prototype_ `bool UpdateResult(const FStateTreeExecutionContext& Context) const;`
- L70 _protected member_ `EGameplayInteractionSlotReferenceType ReferenceType = EGameplayInteractionSlotReferenceType::ByLinkTag;` — `UPROPERTY(EditAnywhere, Category="Parameter")` — Specified which slots to consider when finding the slot.
- L74 _protected member_ `FGameplayTag FindByTag;` — `UPROPERTY(EditAnywhere, Category="Parameter")` — Tag to use to lookup the slot.
- L77 _protected member_ `TStateTreeExternalDataHandle<USmartObjectSubsystem> SmartObjectSubsystemHandle;` — Handle to retrieve USmartObjectSubsystem.

### `Plugins/Runtime/GameplayInteractions/Source/GameplayInteractionsModule/Private/StateTree/GameplayInteractionGetSlotActorTask.h` (Private)


#### struct `FGameplayInteractionGetSlotActorTaskInstanceData`  
`struct FGameplayInteractionGetSlotActorTaskInstanceData`  
_L11-22_
- reflection: `USTRUCT()`
- L17 _public member_ `FSmartObjectSlotHandle TargetSlot;` — `UPROPERTY(EditAnywhere, Category = "Input")` — Target slot to get the Actor from.
- L21 _public member_ `TObjectPtr<AActor> ResultActor;` — `UPROPERTY(EditAnywhere, Category = "Output")` — Actor in the specified target slot, or empty if target slot is not valid or there is not Actor present.

#### struct `FGameplayInteractionGetSlotActorTask`  
`struct FGameplayInteractionGetSlotActorTask : public FGameplayInteractionStateTreeTask`  
_L28-51_
- reflection: `USTRUCT(meta = (DisplayName = "Get Slot Actor", Category="Gameplay Interactions|Smart Object"))`
- inherits: `FGameplayInteractionStateTreeTask`
- desc: Task to get an Actor on a specified Smart Object slot.
- L32 _public prototype_ `FGameplayInteractionGetSlotActorTask();`
- L34 _public typedef_ `using FInstanceDataType = FGameplayInteractionGetSlotActorTaskInstanceData;`
- L37 _protected function_ `virtual const UStruct* GetInstanceDataType() const override`
- L39 _protected prototype_ `virtual bool Link(FStateTreeLinker& Linker) override;`
- L40 _protected prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L42 _protected prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;`
- L47 _protected member_ `bool bFailIfNotFound = true;` — `UPROPERTY(EditAnywhere, Category = "Parameter")` — If true, and no valid actor is found, the task will fail.
- L50 _protected member_ `TStateTreeExternalDataHandle<USmartObjectSubsystem> SmartObjectSubsystemHandle;` — Handle to retrieve USmartObjectSubsystem.

### `Plugins/Runtime/GameplayInteractions/Source/GameplayInteractionsModule/Private/StateTree/GameplayInteractionListenSlotEventsTask.h` (Private)


#### struct `FGameplayInteractionListenSlotEventsTaskInstanceData`  
`struct FGameplayInteractionListenSlotEventsTaskInstanceData`  
_L11-19_
- reflection: `USTRUCT()`
- L16 _public member_ `FSmartObjectSlotHandle TargetSlot;` — `UPROPERTY(EditAnywhere, Category = "Input")`
- L18 _public member_ `FDelegateHandle OnEventHandle;`

#### struct `FGameplayInteractionListenSlotEventsTask`  
`struct FGameplayInteractionListenSlotEventsTask : public FGameplayInteractionStateTreeTask`  
_L26-54_
- reflection: `USTRUCT(meta = (DisplayName = "Listen Slot Events", Category="Gameplay Interactions|Smart Object"))`
- inherits: `FGameplayInteractionStateTreeTask`
- desc: Task to listen Smart Object slot events on a specified slot. Any event sent to the specified Smart Object slot will be translated to a State Tree event.
- L30 _public prototype_ `FGameplayInteractionListenSlotEventsTask();`
- L32 _public typedef_ `using FInstanceDataType = FGameplayInteractionListenSlotEventsTaskInstanceData;`
- L35 _protected function_ `virtual const UStruct* GetInstanceDataType() const override`
- L37 _protected prototype_ `virtual bool Link(FStateTreeLinker& Linker) override;`
- L38 _protected prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L39 _protected prototype_ `virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L41 _protected prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;`
- L42 _protected function_ `virtual FName GetIconName() const override`
- L46 _protected function_ `virtual FColor GetIconColor() const override`
- L53 _protected member_ `TStateTreeExternalDataHandle<USmartObjectSubsystem> SmartObjectSubsystemHandle;` — Handle to retrieve USmartObjectSubsystem.

### `Plugins/Runtime/GameplayInteractions/Source/GameplayInteractionsModule/Private/StateTree/GameplayInteractionModifySlotTagTask.h` (Private)


#### struct `FGameplayInteractionModifySlotTagTaskInstanceData`  
`struct FGameplayInteractionModifySlotTagTaskInstanceData`  
_L13-24_
- reflection: `USTRUCT()`
- L19 _public member_ `FSmartObjectSlotHandle TargetSlot;` — `UPROPERTY(EditAnywhere, Category = "Input")` — Target slot whose tags are modified.
- L23 _public member_ `bool bTagRemoved = false;` — `UPROPERTY()` — When using OnEnterStateUndoOnExitState, indicates if a tag was removed, and whether is should be restored on ExitState().

#### struct `FGameplayInteractionModifySlotTagTask`  
`struct FGameplayInteractionModifySlotTagTask : public FGameplayInteractionStateTreeTask`  
_L32-77_
- reflection: `USTRUCT(meta = (DisplayName = "Modify Slot Tag", Category="Gameplay Interactions|Smart Object"))`
- inherits: `FGameplayInteractionStateTreeTask`
- desc: Task to modify Smart Object Slot tags. The tags can be added or removed, and they can be modified for the duration of the task (OnEnterStateUndoOnExitState), or permanently modified at the beginning or end of the state.
- L36 _public prototype_ `FGameplayInteractionModifySlotTagTask();`
- L38 _public typedef_ `using FInstanceDataType = FGameplayInteractionModifySlotTagTaskInstanceData;`
- L41 _protected function_ `virtual const UStruct* GetInstanceDataType() const override`
- L43 _protected prototype_ `virtual bool Link(FStateTreeLinker& Linker) override;`
- L44 _protected prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L45 _protected prototype_ `virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L47 _protected prototype_ `virtual EDataValidationResult Compile(UE::StateTree::ICompileNodeContext& Context) override;`
- L48 _protected prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;`
- L49 _protected function_ `virtual FName GetIconName() const override`
- L53 _protected function_ `virtual FColor GetIconColor() const override`
- L61 _protected member_ `EGameplayInteractionTaskModify Modify = EGameplayInteractionTaskModify::OnEnterStateUndoOnExitState;` — `UPROPERTY(EditAnywhere, Category = "Parameter")` — When to modify the tags.
- L65 _protected member_ `bool bHandleExternalStopAsFailure = true;` — `UPROPERTY(EditAnywhere, Category = "Parameter")` — If true, handle external State Tree stop as a failure.
- L69 _protected member_ `EGameplayInteractionModifyGameplayTagOperation Operation = EGameplayInteractionModifyGameplayTagOperation::Add;` — `UPROPERTY(EditAnywhere, Category = "Parameter")` — How to modify the tags.
- L73 _protected member_ `FGameplayTag Tag;` — `UPROPERTY(EditAnywhere, Category = "Parameter")` — Tag to add or remove.
- L76 _protected member_ `TStateTreeExternalDataHandle<USmartObjectSubsystem> SmartObjectSubsystemHandle;` — Handle to retrieve USmartObjectSubsystem.

### `Plugins/Runtime/GameplayInteractions/Source/GameplayInteractionsModule/Private/StateTree/GameplayInteractionSendSlotEventTask.h` (Private)


#### struct `FGameplayInteractionSendSlotEventTaskInstanceData`  
`struct FGameplayInteractionSendSlotEventTaskInstanceData`  
_L13-20_
- reflection: `USTRUCT()`
- L19 _public member_ `FSmartObjectSlotHandle TargetSlot;` — `UPROPERTY(EditAnywhere, Category="Input")` — The slot to send the event to.

#### struct `FGameplayInteractionSendSlotEventTask`  
`struct FGameplayInteractionSendSlotEventTask : public FGameplayInteractionStateTreeTask`  
_L26-75_
- reflection: `USTRUCT(meta = (DisplayName = "Send Slot Event", Category="Gameplay Interactions|Smart Object"))`
- inherits: `FGameplayInteractionStateTreeTask`
- desc: Task to send event to a specified Smart Object Slot based on the tasks lifetime.
- L30 _public prototype_ `FGameplayInteractionSendSlotEventTask();`
- L32 _public typedef_ `using FInstanceDataType = FGameplayInteractionSendSlotEventTaskInstanceData;`
- L35 _protected function_ `virtual const UStruct* GetInstanceDataType() const override`
- L37 _protected prototype_ `virtual bool Link(FStateTreeLinker& Linker) override;`
- L38 _protected prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L39 _protected prototype_ `virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L41 _protected prototype_ `virtual EDataValidationResult Compile(UE::StateTree::ICompileNodeContext& Context) override;`
- L42 _protected prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;`
- L43 _protected function_ `virtual FName GetIconName() const override`
- L47 _protected function_ `virtual FColor GetIconColor() const override`
- L55 _protected member_ `FGameplayTag EventTag;` — `UPROPERTY(EditAnywhere, Category = Parameter)` — Tag of the event to send.
- L59 _protected member_ `FInstancedStruct Payload;` — `UPROPERTY(EditAnywhere, Category = Parameter)` — Payload of the event to send.
- L63 _protected member_ `EGameplayInteractionTaskTrigger Trigger = EGameplayInteractionTaskTrigger::OnEnterState;` — `UPROPERTY(EditAnywhere, Category = Parameter)` — Specifies under which conditions to send the event.
- L67 _protected member_ `bool bHandleExternalStopAsFailure = true;` — `UPROPERTY(EditAnywhere, Category = "Parameter")` — If true, handle external State Tree stop as a failure.
- L71 _protected member_ `bool bShouldTriggerOnReselect = true;` — `UPROPERTY(EditAnywhere, Category = Parameter)` — If false, will not trigger on state reselection.
- L74 _protected member_ `TStateTreeExternalDataHandle<USmartObjectSubsystem> SmartObjectSubsystemHandle;` — Handle to retrieve USmartObjectSubsystem.

### `Plugins/Runtime/GameplayInteractions/Source/GameplayInteractionsModule/Private/StateTree/GameplayInteractionSetSlotEnabledTask.h` (Private)


#### struct `FGameplayInteractionSetSlotEnabledInstanceData`  
`struct FGameplayInteractionSetSlotEnabledInstanceData`  
_L11-22_
- reflection: `USTRUCT()`
- L17 _public member_ `FSmartObjectSlotHandle TargetSlot;` — `UPROPERTY(EditAnywhere, Category = "Input")` — Target slot whose tags are modified.
- L21 _public member_ `bool bInitialState = false;` — `UPROPERTY()` — When using OnEnterStateUndoOnExitState, indicates initial enabled state to be restored on ExitState().

#### struct `FGameplayInteractionSetSlotEnabledTask`  
`struct FGameplayInteractionSetSlotEnabledTask : public FGameplayInteractionStateTreeTask`  
_L30-70_
- reflection: `USTRUCT(meta = (DisplayName = "Set Slot Enabled", Category="Gameplay Interactions|Smart Object"))`
- inherits: `FGameplayInteractionStateTreeTask`
- desc: Task to set a Smart Object Slot enabled to disabled. The slot can be enabled or disable for the duration of the task (OnEnterStateUndoOnExitState), or permanently at the beginning or end of the state.
- L34 _public prototype_ `FGameplayInteractionSetSlotEnabledTask();`
- L36 _public typedef_ `using FInstanceDataType = FGameplayInteractionSetSlotEnabledInstanceData;`
- L39 _protected function_ `virtual const UStruct* GetInstanceDataType() const override`
- L41 _protected prototype_ `virtual bool Link(FStateTreeLinker& Linker) override;`
- L42 _protected prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L43 _protected prototype_ `virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L45 _protected prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;`
- L46 _protected function_ `virtual FName GetIconName() const override`
- L50 _protected function_ `virtual FColor GetIconColor() const override`
- L58 _protected member_ `EGameplayInteractionTaskModify Modify = EGameplayInteractionTaskModify::OnEnterStateUndoOnExitState;` — `UPROPERTY(EditAnywhere, Category = "Parameter")` — When to modify the tags.
- L62 _protected member_ `bool bHandleExternalStopAsFailure = true;` — `UPROPERTY(EditAnywhere, Category = "Parameter")` — If true, handle external State Tree stop as a failure.
- L66 _protected member_ `bool bEnableSlot = true;` — `UPROPERTY(EditAnywhere, Category = "Parameter")` — Whether to enable or disable the slot.
- L69 _protected member_ `TStateTreeExternalDataHandle<USmartObjectSubsystem> SmartObjectSubsystemHandle;` — Handle to retrieve USmartObjectSubsystem.

### `Plugins/Runtime/GameplayInteractions/Source/GameplayInteractionsModule/Private/StateTree/GameplayInteractionSyncSlotTagStateTask.h` (Private)


#### struct `FGameplayInteractionSyncSlotTagStateInstanceData`  
`struct FGameplayInteractionSyncSlotTagStateInstanceData`  
_L13-23_
- reflection: `USTRUCT()`
- L19 _public member_ `FSmartObjectSlotHandle TargetSlot;` — `UPROPERTY(EditAnywhere, Category="Input")` — The target slot to monitor
- L21 _public member_ `FDelegateHandle OnEventHandle;`
- L22 _public member_ `bool bBreakSignalled = false;`

#### struct `FGameplayInteractionSyncSlotTagStateTask`  
`struct FGameplayInteractionSyncSlotTagStateTask : public FGameplayInteractionStateTreeTask`  
_L31-68_
- reflection: `USTRUCT(meta = (DisplayName = "Sync Slot Tag State", Category="Gameplay Interactions|Smart Object"))`
- inherits: `FGameplayInteractionStateTreeTask`
- desc: Task to monitor existence of a Gameplay Tag on the specified Smart Object slot. If the monitored Gameplay Tag does not exists on the target slot, or this task completes, a BreakEventTag is sent to the the target slot as well as on the running State Tree. This allows to the task to be used to sync State Tree execution between State Tree instances via a Smart Object slot.
- L35 _public prototype_ `FGameplayInteractionSyncSlotTagStateTask();`
- L37 _public typedef_ `using FInstanceDataType = FGameplayInteractionSyncSlotTagStateInstanceData;`
- L40 _protected function_ `virtual const UStruct* GetInstanceDataType() const override`
- L42 _protected prototype_ `virtual bool Link(FStateTreeLinker& Linker) override;`
- L43 _protected prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L44 _protected prototype_ `virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L46 _protected prototype_ `virtual EDataValidationResult Compile(UE::StateTree::ICompileNodeContext& Context) override;`
- L47 _protected prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;`
- L48 _protected function_ `virtual FName GetIconName() const override`
- L52 _protected function_ `virtual FColor GetIconColor() const override`
- L60 _protected member_ `FGameplayTag TagToMonitor;` — `UPROPERTY(EditAnywhere, Category = "Parameter")` — The tag to monitor on the target slot.
- L64 _protected member_ `FGameplayTag BreakEventTag;` — `UPROPERTY(EditAnywhere, Category = "Parameter")` — Event to send when the monitored tag is not present anymore, or when this task becomes inactive.
- L67 _protected member_ `TStateTreeExternalDataHandle<USmartObjectSubsystem> SmartObjectSubsystemHandle;` — Handle to retrieve USmartObjectSubsystem.

### `Plugins/Runtime/GameplayInteractions/Source/GameplayInteractionsModule/Private/StateTree/GameplayInteractionSyncSlotTagTransition.h` (Private)


#### enum `EGameplayInteractionSyncSlotTransitionState`  
`enum class EGameplayInteractionSyncSlotTransitionState : uint8`  
_L13-18_
- reflection: `UENUM()`
- L15 _public enumerator_ `WaitingForFromTag`
- L16 _public enumerator_ `WaitingForToTag`
- L17 _public enumerator_ `Completed`

#### struct `FGameplayInteractionSyncSlotTagTransitionInstanceData`  
`struct FGameplayInteractionSyncSlotTagTransitionInstanceData`  
_L21-34_
- reflection: `USTRUCT()`
- L27 _public member_ `FSmartObjectSlotHandle TargetSlot;` — `UPROPERTY(EditAnywhere, Category="Input")` — The target slot to monitor
- L30 _public member_ `FDelegateHandle OnEventHandle;` — Smart Object Slot event handle
- L33 _public member_ `EGameplayInteractionSyncSlotTransitionState State = EGameplayInteractionSyncSlotTransitionState::WaitingForFromTag;` — Transition monitoring state

#### struct `FGameplayInteractionSyncSlotTagTransitionTask`  
`struct FGameplayInteractionSyncSlotTagTransitionTask : public FGameplayInteractionStateTreeTask`  
_L46-87_
- reflection: `USTRUCT(meta = (DisplayName = "Sync Slot Tag Transition", Category="Gameplay Interactions|Smart Object"))`
- inherits: `FGameplayInteractionStateTreeTask`
- desc: Task to monitor transition of a Gameplay Tag on the specified Smart Object slot. First the task will wait until it sees TransitionFromTag tag on the target Smart Object slot. - TransitionEventTag event is sent to the target slot, which is assumed to trigger a transition to a state that sets TransitionToTag on the Smart Object slot. Then the task will wait until it sees TransitionToTag tag on the target Smart Object slot. - TransitionEventTag event is sent to running State Tree, which allows the running State Tree to transition a new state that is now executed in sync with the other tree.
- L50 _public prototype_ `FGameplayInteractionSyncSlotTagTransitionTask();`
- L52 _public typedef_ `using FInstanceDataType = FGameplayInteractionSyncSlotTagTransitionInstanceData;`
- L55 _protected function_ `virtual const UStruct* GetInstanceDataType() const override`
- L57 _protected prototype_ `virtual bool Link(FStateTreeLinker& Linker) override;`
- L58 _protected prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L59 _protected prototype_ `virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L61 _protected prototype_ `virtual EDataValidationResult Compile(UE::StateTree::ICompileNodeContext& Context) override;`
- L62 _protected prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;`
- L63 _protected function_ `virtual FName GetIconName() const override`
- L67 _protected function_ `virtual FColor GetIconColor() const override`
- L75 _protected member_ `FGameplayTag TransitionFromTag;` — `UPROPERTY(EditAnywhere, Category = "Parameter")` — Tag to monitor to see if the slot is ready to transition.
- L79 _protected member_ `FGameplayTag TransitionToTag;` — `UPROPERTY(EditAnywhere, Category = "Parameter")` — Tag to monitor to see if the slot has transitioned.
- L83 _protected member_ `FGameplayTag TransitionEventTag;` — `UPROPERTY(EditAnywhere, Category = "Parameter")` — Event that is sent to target slot when TransitionFromTag is seen, and event that is send to running State Tree when TransitionToTag is seen.
- L86 _protected member_ `TStateTreeExternalDataHandle<USmartObjectSubsystem> SmartObjectSubsystemHandle;` — Handle to retrieve USmartObjectSubsystem.

### `Plugins/Runtime/GameplayInteractions/Source/GameplayInteractionsModule/Private/StateTree/PlayMontageStateTreeTask.h` (Private)


#### struct `FPlayMontageStateTreeTaskInstanceData`  
`struct FPlayMontageStateTreeTaskInstanceData`  
_L14-27_
- reflection: `USTRUCT()`
- L19 _public member_ `TObjectPtr<AActor> Actor = nullptr;` — `UPROPERTY(EditAnywhere, Category="Context")`
- L22 _public member_ `float ComputedDuration = 0.0f;` — `UPROPERTY()`
- L26 _public member_ `float Time = 0.f;` — `UPROPERTY()` — Accumulated time used to stop task if a montage is set

#### struct `FPlayMontageStateTreeTask`  
`struct FPlayMontageStateTreeTask : public FGameplayInteractionStateTreeTask`  
_L31-55_
- reflection: `USTRUCT(meta = (DisplayName = "Play Anim Montage", Category="Gameplay Interactions"))`
- inherits: `FGameplayInteractionStateTreeTask`
- L35 _public typedef_ `typedef FPlayMontageStateTreeTaskInstanceData FInstanceDataType;`
- L38 _protected function_ `virtual const UStruct* GetInstanceDataType() const override`
- L40 _protected prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L41 _protected prototype_ `virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;`
- L43 _protected prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;`
- L44 _protected function_ `virtual FName GetIconName() const override`
- L48 _protected function_ `virtual FColor GetIconColor() const override`
- L54 _protected member_ `TObjectPtr<UAnimMontage> Montage = nullptr;` — `UPROPERTY(EditAnywhere, Category = Parameter)`

### `Plugins/Runtime/GameplayInteractions/Source/GameplayInteractionsModule/Private/StateTree/StateTreeTask_GetSlotEntranceTags.h` (Private)


#### struct `FStateTreeTask_GetSlotEntranceTags_InstanceData`  
`struct FStateTreeTask_GetSlotEntranceTags_InstanceData`  
_L14-25_
- reflection: `USTRUCT()`
- L20 _public member_ `FSmartObjectSlotEntranceHandle SlotEntranceHandle;` — `UPROPERTY(EditAnywhere, Category = "Input")` — Handle to the slot entrance to get the tags from.
- L24 _public member_ `FGameplayTagContainer EntranceTags;` — `UPROPERTY(EditAnywhere, Category = "Output")` — Tags defined on the slot entrance.

#### struct `FStateTreeTask_GetSlotEntranceTags`  
`struct FStateTreeTask_GetSlotEntranceTags : public FGameplayInteractionStateTreeTask`  
_L31-59_
- reflection: `USTRUCT(meta = (DisplayName = "Get Slot Entrance Tags", Category="Gameplay Interactions|Smart Object"))`
- inherits: `FGameplayInteractionStateTreeTask`
- desc: Gets Gameplay Tags defined at specified Smart Object slot entrance.
- L35 _public prototype_ `FStateTreeTask_GetSlotEntranceTags();`
- L37 _public typedef_ `using FInstanceDataType = FStateTreeTask_GetSlotEntranceTags_InstanceData;`
- L40 _protected function_ `virtual const UStruct* GetInstanceDataType() const override`
- L42 _protected prototype_ `virtual bool Link(FStateTreeLinker& Linker) override;`
- L43 _protected prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L45 _protected prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;`
- L46 _protected function_ `virtual FName GetIconName() const override`
- L50 _protected function_ `virtual FColor GetIconColor() const override`
- L55 _protected prototype_ `bool UpdateResult(const FStateTreeExecutionContext& Context) const;`
- L58 _protected member_ `TStateTreeExternalDataHandle<USmartObjectSubsystem> SmartObjectSubsystemHandle;` — Handle to retrieve USmartObjectSubsystem.

### `Plugins/Runtime/GameplayInteractions/Source/GameplayInteractionsModule/Private/StateTree/StateTreeTask_PlayContextualAnim.h` (Private)


#### enum `EPlayContextualAnimExecutionMethod`  
`enum class EPlayContextualAnimExecutionMethod : uint8`  
_L13-26_
- reflection: `UENUM(BlueprintType)`
- L16 _public enumerator_ `StartInteraction` — Start a new interaction
- L19 _public enumerator_ `JoinInteraction` — Join an existing interaction
- L22 _public enumerator_ `TransitionAllActors` — Transition a single actor in an interaction to a different section
- L25 _public enumerator_ `TransitionSingleActor` — Transition all the actors in an interaction to a different sections

#### class `UStateTreeTask_PlayContextualAnim_InstanceData`  
`class UStateTreeTask_PlayContextualAnim_InstanceData : public UObject`  
_L29-140_
- reflection: `UCLASS()`
- inherits: `UObject`
- L35 _public member_ `TObjectPtr<AActor> PrimaryActor = nullptr;` — `UPROPERTY(EditAnywhere, Category = Input)`
- L38 _public member_ `TObjectPtr<AActor> SecondaryActor = nullptr;` — `UPROPERTY(EditAnywhere, Category = Input)`
- L41 _public member_ `FName SecondaryRole;` — `UPROPERTY(EditAnywhere, Category = Parameter)`
- L44 _public member_ `TObjectPtr<AActor> TertiaryActor = nullptr;` — `UPROPERTY(EditAnywhere, Category = Parameter)`
- L47 _public member_ `FName TertiaryRole;` — `UPROPERTY(EditAnywhere, Category = Parameter)`
- L50 _public member_ `TObjectPtr<const UContextualAnimSceneAsset> SceneAsset = nullptr;` — `UPROPERTY(EditAnywhere, Category = Parameter)`
- L53 _public member_ `FName SectionName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = Parameter)`
- L56 _public member_ `EPlayContextualAnimExecutionMethod ExecutionMethod = EPlayContextualAnimExecutionMethod::StartInteraction;` — `UPROPERTY(EditAnywhere, Category = Parameter)`
- L66 _public member_ `bool bWaitForNotifyEventToEnd = false;` — `UPROPERTY(EditAnywhere, Category = Parameter)` — There are cases where we may be 'chaining' multiple interactions animations through different state tree tasks (e.g start -> loop -> end) This could cause visual artifacts specially noticeable in multiplayer environment when the replicated package to start the next animation may not arrive right after the current animation ends. To avoid this we can set the montage to do not auto blend out and add a Montage Notify at the end of the animation to let us know that we reached the end Note: This is really a workaround. Ideally we should have an event that let us know when the montage reaches its end regardless of the Auto Blend Out property.
- L70 _public member_ `FName NotifyEventNameToEnd = NAME_None;` — `UPROPERTY(EditAnywhere, Category = Parameter, meta = (EditCondition = "bWaitForNotifyEventToEnd"))` — When bWaitForNotifyEventToEnd is set to true this is the name of the notify that we will look for to signal the end of the task
- L74 _public member_ `int32 LoopsToRun = 1;` — `UPROPERTY(EditAnywhere, Category = Parameter, meta = (EditCondition = "!bLoopForever", ClampMin = "1"))` — How many times the animation should be run before completing the task.
- L78 _public member_ `bool bLoopForever = false;` — `UPROPERTY(EditAnywhere, Category = Parameter)` — If true the animation will loop forever until a transition stops it.
- L82 _public member_ `float DelayBetweenLoops = 0.f;` — `UPROPERTY(EditAnywhere, Category = Parameter, meta = (ClampMin = "0.0"))` — How many seconds should we wait between each animation loop (won't be used if RunLoops is equal 1).
- L86 _public member_ `float RandomDeviationBetweenLoops = 0.f;` — `UPROPERTY(EditAnywhere, Category = Parameter, meta = (ClampMin = "0.0"))` — Adds random range to the DelayBetweenLoops.
- L90 _public member_ `TArray<FContextualAnimWarpTarget> WarpTargets;` — `UPROPERTY(EditAnywhere, Category = Parameter)` — Manual warp targets for specific roles.
- L93 _public member_ `int32 CompletedLoops = 0;` — Internal count of how many loops have been completed. The Task finishes when the this is equal the provided RunLoops.
- L96 _public member_ `bool bMontageInterrupted = false;` — It can happen that the montage is interrupted, in which case we want to fail the task.
- L99 _public member_ `bool bExpectInterruptionFromNotifyEventLoop = false;` — Handling of specific case: when we forcibly start a new montage from a notify event, an interruption will happen from the previous event, so we need to make sure to ignore the first occurrence.
- L102 _public member_ `TOptional<float> TimeBeforeStartingNewLoop;` — Used internally to handle the delay between loops. When is set and <= 0 we run a new animation loop.
- L105 _public member_ `bool bPreviousForceControlRotationFromPawnOrientationForPrimaryActor = false;` — Cached value that we reset on task exit.
- L108 _public member_ `bool bPreviousForceControlRotationFromPawnOrientationForSecondaryActor = false;` — Cached value that we reset on task exit.
- L111 _public member_ `bool bPreviousForceControlRotationFromPawnOrientationForTertiaryActor = false;` — Cached value that we reset on task exit.
- L113 _public prototype_ `EStateTreeRunStatus OnEnterState(const FStateTreeExecutionContext& Context);`
- L116 _public prototype_ `bool StartContextualAnim(const FStateTreeExecutionContext& Context) const;` — Start a new interaction
- L119 _public prototype_ `bool JoinContextualAnim(const FStateTreeExecutionContext& Context) const;` — Join an existing interaction
- L122 _public prototype_ `bool TransitionSingleActor(const FStateTreeExecutionContext& Context) const;` — Transition a single actor in an interaction to a different section
- L125 _public prototype_ `bool TransitionAllActors(const FStateTreeExecutionContext& Context) const;` — Transition all the actors in an interaction to a different sections
- L127 _public prototype_ `void OnExitState();`
- L129 _public prototype_ `EStateTreeRunStatus OnTick(const FStateTreeExecutionContext& Context, float DeltaTime);`
- L131 _public prototype_ `EStateTreeRunStatus Play(const FStateTreeExecutionContext& Context);`
- L133 _public prototype_ `void CleanUp();`
- L136 _public prototype_ `void OnMontageEnded(UAnimMontage* const EndedMontage, const bool bInterrupted);` — `UFUNCTION()`
- L139 _public prototype_ `void OnNotifyBeginReceived(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload);` — `UFUNCTION()`

#### struct `FStateTreeTask_PlayContextualAnim`  
`struct FStateTreeTask_PlayContextualAnim : public FStateTreeTaskCommonBase`  
_L143-171_
- reflection: `USTRUCT(meta = (DisplayName = "Play Contextual Anim"))`
- inherits: `FStateTreeTaskCommonBase`
- L147 _public typedef_ `using UInstanceDataType = UStateTreeTask_PlayContextualAnim_InstanceData;`
- L149 _public prototype_ `FStateTreeTask_PlayContextualAnim();`
- L151 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L153 _public prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L155 _public prototype_ `virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L157 _public prototype_ `virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;`
- L160 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;`
- L161 _public function_ `virtual FName GetIconName() const override`
- L165 _public function_ `virtual FColor GetIconColor() const override`

### `Plugins/Runtime/GameplayInteractions/Source/GameplayInteractionsModule/Public/GameplayInteractionContext.h` (Public)


#### struct `FGameplayInteractionContext`  
`struct FGameplayInteractionContext`  
_L22-122_
- reflection: `USTRUCT()`
- desc: Struct that holds data required to perform the interaction and wraps StateTree execution
- L27 _public function_ `const FSmartObjectClaimHandle& GetClaimedHandle() const`
- L32 _public function_ `void SetClaimedHandle(const FSmartObjectClaimHandle& InClaimedHandle)`
- L37 _public function_ `void SetSlotEntranceHandle(const FSmartObjectSlotEntranceHandle InSlotEntranceHandle)`
- L42 _public function_ `void SetContextActor(AActor* InContextActor)`
- L47 _public function_ `void SetSmartObjectActor(AActor* InSmartObjectActor)`
- L52 _public function_ `void SetAbortContext(const FGameplayInteractionAbortContext& InAbortContext)`
- L57 _public function_ `bool IsValid() const`
- L62 _public function_ `EStateTreeRunStatus GetLastRunStatus() const`
- L71 _public prototype_ `bool Activate(const UGameplayInteractionSmartObjectBehaviorDefinition& Definition);` — Prepares the StateTree execution context using provided Definition then starts the underlying StateTree @return True if interaction has been properly initialized and ready to be ticked.
- L77 _public prototype_ `bool Tick(const float DeltaTime);` — Updates the underlying StateTree @return True if still requires to be ticked, false if done.
- L82 _public prototype_ `void Deactivate();` — Stops the underlying StateTree
- L85 _public prototype_ `void SendEvent(const FGameplayTag Tag, const FConstStructView Payload = FConstStructView(), const FName Origin = FName());` — Sends event for the StateTree. Will be received on the next tick by the StateTree.
- L92 _protected prototype_ `bool SetContextRequirements(FStateTreeExecutionContext& StateTreeContext);` — Updates all external data views from the provided interaction context. @return True if all external data views are valid, false otherwise.
- L95 _protected prototype_ `bool ValidateSchema(const FStateTreeExecutionContext& StateTreeContext) const;` — @return true of the ContextActor and SmartObjectActor match the ones set in schema.
- L98 _protected member_ `FStateTreeInstanceData StateTreeInstanceData;` — `UPROPERTY()`
- L101 _protected member_ `FSmartObjectClaimHandle ClaimedHandle;` — `UPROPERTY()`
- L104 _protected member_ `FSmartObjectSlotEntranceHandle SlotEntranceHandle;` — `UPROPERTY()`
- L107 _protected member_ `FGameplayInteractionAbortContext AbortContext;` — `UPROPERTY()`
- L110 _protected member_ `TObjectPtr<AActor> ContextActor = nullptr;` — `UPROPERTY()`
- L113 _protected member_ `TObjectPtr<AActor> SmartObjectActor = nullptr;` — `UPROPERTY()`
- L116 _protected member_ `TObjectPtr<const UGameplayInteractionSmartObjectBehaviorDefinition> Definition = nullptr;` — `UPROPERTY()`
- L118 _protected member_ `EStateTreeRunStatus LastRunStatus = EStateTreeRunStatus::Unset;`
- L121 _private member_ `FStateTreeExecutionContext* CurrentlyRunningExecContext = nullptr;`

### `Plugins/Runtime/GameplayInteractions/Source/GameplayInteractionsModule/Public/GameplayInteractionSmartObjectBehaviorDefinition.h` (Public)


#### class `UGameplayInteractionSmartObjectBehaviorDefinition`  
`class UGameplayInteractionSmartObjectBehaviorDefinition : public USmartObjectBehaviorDefinition`  
_L15-39_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `USmartObjectBehaviorDefinition`
- desc: SmartObject behavior definition for the GameplayInteractions
- L20 _public member_ `FStateTreeReference StateTreeReference;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SmartObject", DisplayName = "State Tree", meta=(Schema="/Script/GameplayInteractionsModule.GameplayInteractionStateTreeSchema"))`
- L23 _public function_ `void SetStateTree(UStateTree* NewStateTree)` — `UFUNCTION(BlueprintCallable, Category = "StateTree")`
- L29 _public function_ `const UStateTree* GetStateTree() const` — `UFUNCTION(BlueprintPure, Category = "StateTree")`
- L37 _public prototype_ `virtual void GetPreloadDependencies(TArray<UObject*>& OutDeps) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEPLAYINTERACTIONSMODULE_API`

### `Plugins/Runtime/GameplayInteractions/Source/GameplayInteractionsModule/Public/GameplayInteractionStateTreeSchema.h` (Public)


#### class `UGameplayInteractionStateTreeSchema`  
`class UGameplayInteractionStateTreeSchema : public UStateTreeSchema`  
_L15-49_
- reflection: `UCLASS(MinimalAPI, BlueprintType, EditInlineNew, CollapseCategories, meta = (DisplayName = "Gameplay Interactions"))`
- inherits: `UStateTreeSchema`
- L20 _public prototype_ `UGameplayInteractionStateTreeSchema();`
- L22 _public function_ `UClass* GetContextActorClass() const`
- L23 _public function_ `UClass* GetSmartObjectActorClass() const`
- L26 _protected prototype_ `virtual bool IsStructAllowed(const UScriptStruct* InScriptStruct) const override;`
- L27 _protected prototype_ `virtual bool IsClassAllowed(const UClass* InScriptStruct) const override;`
- L28 _protected prototype_ `virtual bool IsExternalItemAllowed(const UStruct& InStruct) const override;`
- L30 _protected function_ `virtual TConstArrayView<FStateTreeExternalDataDesc> GetContextDataDescs() const override`
- L32 _protected prototype_ `virtual void PostLoad() override;`
- L35 _protected prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L40 _protected member_ `TSubclassOf<AActor> ContextActorClass;` — `UPROPERTY(EditAnywhere, Category="Defaults")` — Actor class the StateTree is expected to run on. Allows to bind to specific Actor class' properties.
- L44 _protected member_ `TSubclassOf<AActor> SmartObjectActorClass;` — `UPROPERTY(EditAnywhere, Category="Defaults")` — Actor class of the SmartObject the StateTree is expected to run with. Allows to bind to specific Actor class' properties.
- L48 _protected member_ `TArray<FStateTreeExternalDataDesc> ContextDataDescs;` — `UPROPERTY()` — List of named external data required by schema and provided to the state tree through the execution context.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GAMEPLAYINTERACTIONSMODULE_API`

### `Plugins/Runtime/GameplayInteractions/Source/GameplayInteractionsModule/Public/GameplayInteractionsModule.h` (Public)


#### class `IGameplayInteractionsModule`  
`class IGameplayInteractionsModule : public IModuleInterface`  
_L10-29_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L21 _public prototype_ `static IGameplayInteractionsModule& Get();` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L28 _public prototype_ `static bool IsAvailable();` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/Runtime/GameplayInteractions/Source/GameplayInteractionsModule/Public/GameplayInteractionsTypes.h` (Public)


#### enum `EGameplayInteractionAbortReason`  
`enum class EGameplayInteractionAbortReason : uint8`  
_L27-32_
- reflection: `UENUM(BlueprintType)`
- desc: Reason why the interaction is ended prematurely.
- L29 _public enumerator_ `Unset`
- L30 _public enumerator_ `ExternalAbort`
- L31 _public enumerator_ `InternalAbort` — Internal failure from slot invalidation (e.g. slot unregistered, destroyed)

#### struct `FGameplayInteractionAbortContext`  
`struct FGameplayInteractionAbortContext`  
_L38-47_
- reflection: `USTRUCT(BlueprintType)`
- desc: Struct holding data related to the abort action
- L42 _public prototype_ `FGameplayInteractionAbortContext() = default;`
- L43 _public function_ `explicit FGameplayInteractionAbortContext(const EGameplayInteractionAbortReason& InReason) : Reason(InReason)`
- L46 _public member_ `EGameplayInteractionAbortReason Reason = EGameplayInteractionAbortReason::Unset;` — `UPROPERTY()`

#### struct `FGameplayInteractionSlotUserData`  
`struct FGameplayInteractionSlotUserData : public FSmartObjectSlotStateData`  
_L53-61_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FSmartObjectSlotStateData`
- desc: Data added to a Smart Object slot when interaction is started on it. Allows to look up the user.
- L57 _public prototype_ `FGameplayInteractionSlotUserData() = default;`
- L58 _public function_ `explicit FGameplayInteractionSlotUserData(AActor* InUserActor) : UserActor(InUserActor)`
- L60 _public member_ `TWeakObjectPtr<AActor> UserActor = nullptr;`

#### struct `FGameplayInteractionStateTreeTask`  
`struct FGameplayInteractionStateTreeTask : public FStateTreeTaskBase`  
_L70-74_
- reflection: `USTRUCT(meta = (Hidden))`
- inherits: `FStateTreeTaskBase`
- desc: Base class (namespace) for all StateTree Tasks related to AI/Gameplay. This allows schemas to safely include all tasks child of this struct.

#### struct `FGameplayInteractionStateTreeCondition`  
`struct FGameplayInteractionStateTreeCondition : public FStateTreeConditionBase`  
_L77-81_
- reflection: `USTRUCT(meta = (Hidden))`
- inherits: `FStateTreeConditionBase`

#### enum `EGameplayInteractionModifyGameplayTagOperation`  
`enum class EGameplayInteractionModifyGameplayTagOperation : uint8`  
_L87-94_
- reflection: `UENUM()`
- desc: Value specifying how GameplayTag container should be modified.
- L90 _public enumerator_ `Add` — The tag modified during the lifetime of the task.
- L93 _public enumerator_ `Remove` — The tag modified when the state becomes active.

#### enum `EGameplayInteractionTaskModify`  
`enum class EGameplayInteractionTaskModify : uint8`  
_L100-116_
- reflection: `UENUM()`
- desc: Value specifying when a State Tree task based modification should take place.
- L103 _public enumerator_ `OnEnterStateUndoOnExitState` — The modification takes effect when the state becomes active, and is undone when the state becomes inactive.
- L106 _public enumerator_ `OnEnterState` — The modification takes place when the state becomes active.
- L109 _public enumerator_ `OnExitState` — The modification takes place when the state becomes inactive.
- L112 _public enumerator_ `OnExitStateFailed` — The modification takes place if the state fails.
- L115 _public enumerator_ `OnExitStateSucceeded` — The modification takes place if the state succeeds.

#### enum `EGameplayInteractionTaskTrigger`  
`enum class EGameplayInteractionTaskTrigger : uint8`  
_L122-135_
- reflection: `UENUM()`
- desc: Value specifying when a State Tree task based action should be triggered.
- L125 _public enumerator_ `OnEnterState` — Execute when state becomes active.
- L128 _public enumerator_ `OnExitState` — Execute when state becomes inactive.
- L131 _public enumerator_ `OnExitStateFailed` — Execute if the state fails.
- L134 _public enumerator_ `OnExitStateSucceeded` — Execute if the state succeeds.

#### enum `EGameplayTaskActuationResult`  
`enum class EGameplayTaskActuationResult : uint8`  
_L139-145_
- reflection: `UENUM()`
- L141 _public enumerator_ `None`
- L142 _public enumerator_ `RequestFailed`
- L143 _public enumerator_ `Failed`
- L144 _public enumerator_ `Succeeded`

#### Free symbols / members of external scopes

- L14 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGameplayInteractions, Warning, All);`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace GameplayInteraction` (scope `UE`)
- L16 _namespace_ `namespace Names` (scope `UE::GameplayInteraction`)
- L18 _externvar_ `extern const FName ContextActor;` (scope `UE::GameplayInteraction::Names`) — The actor performing the interaction, using short name to be consistent with naming with StateTreeComponentSchema.
- L19 _externvar_ `extern const FName SmartObjectActor;` (scope `UE::GameplayInteraction::Names`) — The SmartObjectActor participating in the interaction.
- L20 _externvar_ `extern const FName SmartObjectClaimedHandle;` (scope `UE::GameplayInteraction::Names`)
- L21 _externvar_ `extern const FName SlotEntranceHandle;` (scope `UE::GameplayInteraction::Names`)
- L22 _externvar_ `extern const FName AbortContext;` (scope `UE::GameplayInteraction::Names`)
- L147 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGameplayTaskActuationCompleted, EGameplayTaskActuationResult, Result, AActor*, Actor);`
- L147 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGameplayTaskActuationCompleted, EGameplayTaskActuationResult, Result, AActor*, Actor);`
- L149 _namespace_ `namespace UE`
- L149 _namespace_ `namespace GameplayInteraction` (scope `UE`)
- L149 _namespace_ `namespace Debug` (scope `UE::GameplayInteraction`)
- L151 _prototype_ `void VLogPath(const UObject* LogOwner, const FNavigationPath& Path);` (scope `UE::GameplayInteraction::Debug`)
- L152 _prototype_ `void VLogCorridor(const UObject* LogOwner, const FNavCorridor& Corridor);` (scope `UE::GameplayInteraction::Debug`)

### `Plugins/Runtime/GameplayInteractions/Source/GameplayInteractionsModule/Public/StateTree/StateTreeTask_FindSlotEntranceLocation.h` (Public)


#### struct `FStateTreeTask_FindSlotEntranceLocation_InstanceData`  
`struct FStateTreeTask_FindSlotEntranceLocation_InstanceData`  
_L17-33_
- reflection: `USTRUCT()`
- L22 _public member_ `TObjectPtr<AActor> UserActor = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Context")`
- L26 _public member_ `FSmartObjectSlotHandle ReferenceSlot;` — `UPROPERTY(EditAnywhere, Category = "Input")` — Slot to use as reference to find the result slot.
- L29 _public member_ `FTransform EntryTransform;` — `UPROPERTY(EditAnywhere, Category = "Output")` — @todo: rename EntranceTransform
- L32 _public member_ `FGameplayTagContainer EntranceTags;` — `UPROPERTY(EditAnywhere, Category = "Output")`

#### struct `FStateTreeTask_FindSlotEntranceLocation`  
`struct FStateTreeTask_FindSlotEntranceLocation : public FGameplayInteractionStateTreeTask`  
_L40-108_
- reflection: `USTRUCT(meta = (DisplayName = "Find Slot Entrance Location", Category="Gameplay Interactions|Smart Object"))`
- inherits: `FGameplayInteractionStateTreeTask`
- desc: Finds entrance location for a Smart Object slot. The query will use slot entrance annotations as candidates. Each candidate is ranked (e.g. based on distance), and optionally validated to be close to a navigable space and without collisions.
- L44 _public prototype_ `FStateTreeTask_FindSlotEntranceLocation();`
- L46 _public typedef_ `using FInstanceDataType = FStateTreeTask_FindSlotEntranceLocation_InstanceData;`
- L49 _protected function_ `virtual const UStruct* GetInstanceDataType() const override`
- L51 _protected prototype_ `virtual bool Link(FStateTreeLinker& Linker) override;`
- L52 _protected prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L54 _protected prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;`
- L55 _protected function_ `virtual FName GetIconName() const override`
- L59 _protected function_ `virtual FColor GetIconColor() const override`
- L64 _protected prototype_ `virtual bool UpdateResult(const FStateTreeExecutionContext& Context) const;`
- L68 _protected member_ `FSmartObjectSlotEntrySelectionMethod SelectMethod;` — `UPROPERTY(EditAnywhere, Category="Default")` — Method to select an entry when multiple entries are present.
- L72 _protected member_ `bool bProjectNavigationLocation = true;` — `UPROPERTY(EditAnywhere, Category="Default")` — If true, the result is required to be in or close to a navigable space.
- L76 _protected member_ `bool bTraceGroundLocation = true;` — `UPROPERTY(EditAnywhere, Category="Default")` — If true, try to trace the location on ground. If trace fails, an entry is discarded.
- L80 _protected member_ `bool bCheckTransitionTrajectory = true;` — `UPROPERTY(EditAnywhere, Category="Default")` — If true, check collisions between navigation location and slot location. If collisions are found, an entry is discarded.
- L84 _protected member_ `bool bCheckEntranceLocationOverlap = true;` — `UPROPERTY(EditAnywhere, Category="Default")` — If true, check user capsule collisions at the entrance location. Uses capsule dimensions set in the validation filter.
- L88 _protected member_ `bool bCheckSlotLocationOverlap = true;` — `UPROPERTY(EditAnywhere, Category="Default")` — If true, check user capsule collisions at the slot location. Uses capsule dimensions set in an annotation on the slot.
- L92 _protected member_ `bool bUseUpAxisLockedRotation = true;` — `UPROPERTY(EditAnywhere, Category="Default")` — If true, the result rotation will only contain rotation around the UP axis (i.e., Yaw only; Pitch and Roll set to 0).
- L96 _protected member_ `bool bUseSlotLocationAsFallbackCandidate = false;` — `UPROPERTY(EditAnywhere, Category="Default")` — If true, include slot location as candidate if no entry annotation is present.
- L100 _protected member_ `ESmartObjectSlotNavigationLocationType LocationType = ESmartObjectSlotNavigationLocationType::Entry;` — `UPROPERTY(EditAnywhere, Category="Default")` — Whether we're looking for an entry or exit location.
- L104 _protected member_ `TSubclassOf<USmartObjectSlotValidationFilter> ValidationFilter;` — `UPROPERTY(EditAnywhere, Category="Default")` — Validation filter to apply to query.
- L107 _protected member_ `TStateTreeExternalDataHandle<USmartObjectSubsystem> SmartObjectSubsystemHandle;` — Handle to retrieve USmartObjectSubsystem.
