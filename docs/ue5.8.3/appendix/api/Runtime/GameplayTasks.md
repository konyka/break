# Runtime / GameplayTasks

- module root: `Source/Runtime/GameplayTasks`
- headers: 11; symbols: 291
- symbol kinds: class=10, delegate=7, enum=5, enumerator=17, function=72, macro=1, member=53, namespace=1, prototype=114, struct=5, typedef=4, variable=2
- PrivateDependencyModuleNames: EditorFramework, GameplayTagsEditor, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine, GameplayTags, NetCore

### `Source/Runtime/GameplayTasks/Classes/GameplayTask.h` (Public)


#### enum `EGameplayTaskState`  
`enum class EGameplayTaskState : uint8`  
_L22-29_
- reflection: `UENUM()`
- L24 _public enumerator_ `Uninitialized`
- L25 _public enumerator_ `AwaitingActivation`
- L26 _public enumerator_ `Paused`
- L27 _public enumerator_ `Active`
- L28 _public enumerator_ `Finished`

#### enum `ETaskResourceOverlapPolicy`  
`enum class ETaskResourceOverlapPolicy : uint8`  
_L32-42_
- reflection: `UENUM()`
- L35 _public enumerator_ `StartOnTop` — Pause overlapping same-priority tasks.
- L37 _public enumerator_ `StartAtEnd` — Wait for other same-priority tasks to finish.
- L39 _public enumerator_ `RequestCancelAndStartOnTop` — Request to cancel same or lower priority tasks, if tasks not ended pause overlapping same-priority tasks.
- L41 _public enumerator_ `RequestCancelAndStartAtEnd` — Request to cancel same or lower priority tasks, wait for any remaining overlapping same-priority tasks to finish.

#### struct `FGameplayResourceSet`  
`struct FGameplayResourceSet`  
_L45-142_
- reflection: `USTRUCT(BlueprintType)`
- L49 _public typedef_ `typedef uint16 FFlagContainer;`
- L50 _public typedef_ `typedef uint8 FResourceID;`
- L58 _private member_ `FFlagContainer Flags;`
- L62 _public function_ `explicit FGameplayResourceSet(FFlagContainer InFlags = 0) : Flags(InFlags)` — Mind that this constructor takes _flags_ not individual IDs
- L65 _public function_ `FFlagContainer GetFlags() const`
- L69 _public function_ `bool IsEmpty() const`
- L73 _public function_ `FGameplayResourceSet& AddID(uint8 ResourceID)`
- L79 _public function_ `FGameplayResourceSet& RemoveID(uint8 ResourceID)`
- L85 _public function_ `bool HasID(uint8 ResourceID) const`
- L90 _public function_ `FGameplayResourceSet& AddSet(FGameplayResourceSet Other)`
- L95 _public function_ `FGameplayResourceSet& RemoveSet(FGameplayResourceSet Other)`
- L100 _public function_ `void Clear()`
- L104 _public function_ `bool HasAllIDs(FGameplayResourceSet Other) const`
- L108 _public function_ `bool HasAnyID(FGameplayResourceSet Other) const`
- L112 _public function_ `FGameplayResourceSet GetOverlap(FGameplayResourceSet Other) const`
- L116 _public function_ `FGameplayResourceSet GetDifference(FGameplayResourceSet Other) const`
- L121 _public function_ `bool operator==(const FGameplayResourceSet& Other) const`
- L126 _public function_ `bool operator!=(const FGameplayResourceSet& Other) const`
- L131 _public function_ `static FGameplayResourceSet AllResources()`
- L136 _public function_ `static FGameplayResourceSet NoResources()`
- L141 _public prototype_ `FString GetDebugDescription() const;`

#### enum `FGameplayResourceSet::(anonymous)`  
``  
_L53-55_

#### class `UGameplayTask`  
`class UGameplayTask : public UObject, public IGameplayTaskOwnerInterface`  
_L145-393_
- reflection: `UCLASS(Abstract, BlueprintType, meta = (ExposedAsyncProxy=AsyncTask), config = Game, MinimalAPI)`
- inherits: `UObject,IGameplayTaskOwnerInterface`
- L151 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGenericGameplayTaskDelegate);`
- L153 _public prototype_ `UGameplayTask(const FObjectInitializer& ObjectInitializer);`
- L157 _public prototype_ `void ReadyForActivation();` — `UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Gameplay Tasks")` — Called to trigger the actual task once the delegates have been set up
- L162 _protected prototype_ `virtual void Activate();` — Called to trigger the actual task once the delegates have been set up Note that the default implementation does nothing and you don't have to call it
- L165 _protected prototype_ `void InitTask(IGameplayTaskOwnerInterface& InTaskOwner, uint8 InPriority);` — Initializes the task with the task owner interface instance but does not activate until Activate() is called
- L168 _public prototype_ `virtual void InitSimulatedTask(UGameplayTasksComponent& InGameplayTasksComponent);`
- L171 _public function_ `virtual void TickTask(float DeltaTime)` — Tick function for this task, if bTickingTask == true
- L174 _public prototype_ `virtual void ExternalConfirm(bool bEndTask);` — Called when the task is asked to confirm from an outside node. What this means depends on the individual task. By default, this does nothing other than ending if bEndTask is true.
- L177 _public prototype_ `virtual void ExternalCancel();` — Called when the task is asked to cancel from an outside node. What this means depends on the individual task. By default, this does nothing other than ending the task.
- L180 _public function_ `void MarkOwnerFinished()` — Called when a task owner wants to inform the task that it's done and don't want to get notified on task deactivation (i.e. OnGameplayTaskDeactivated).
- L183 _public prototype_ `virtual FString GetDebugString() const;` — Return debug string describing task
- L186 _public prototype_ `virtual UWorld* GetWorld() const override;` — Helper function for getting UWorld off a task
- L189 _public prototype_ `AActor* GetOwnerActor() const;` — Proper way to get the owning actor of task owner. This can be the owner itself since the owner is given as a interface
- L192 _public prototype_ `AActor* GetAvatarActor() const;` — Proper way to get the avatar actor associated with the task owner (usually a pawn, tower, etc)
- L196 _public function_ `template <class T> inline static T* NewTask(UObject* WorldContextObject, FName InstanceName = FName())` — Helper function for instantiating and initializing a new task
- L202 _public function_ `template <class T> inline static T* NewTask(TScriptInterface<IGameplayTaskOwnerInterface> TaskOwner, FName InstanceName = FName())`
- L208 _public prototype_ `template <class T> inline static T* NewTask(UObject& WorldContextObject, FName InstanceName = FName());`
- L211 _public prototype_ `template <class T> inline static T* NewTask(IGameplayTaskOwnerInterface& TaskOwner, FName InstanceName = FName());`
- L216 _public function_ `template <class T> inline static T* NewTaskUninitialized()` — Added for consistency with NewTask, but to indicate that a task requires manual call to InitTask This path is used to manually configure some aspects of the task, like Priority
- L222 _public prototype_ `void TaskOwnerEnded();` — Called when task owner has "ended" (before the task ends) kills the task. Calls OnDestroy.
- L229 _public prototype_ `void EndTask();` — `UFUNCTION(BlueprintCallable, Category="GameplayTasks")` — Called explicitly to end the task (usually by the task itself). Calls OnDestroy. @NOTE: you need to call EndTask before sending out any "on completed" delegates. If you don't the task will still be in an "active" state while the event receivers may assume it's already "finished"
- L231 _public function_ `virtual bool IsSupportedForNetworking() const override`
- L233 _public function_ `inline FName GetInstanceName() const`
- L234 _public function_ `inline bool IsTickingTask() const`
- L235 _public function_ `inline bool IsSimulatedTask() const`
- L236 _public function_ `inline bool IsSimulating() const`
- L237 _public function_ `inline bool IsPausable() const`
- L238 _public function_ `inline bool HasOwnerFinished() const`
- L239 _public function_ `inline uint8 GetPriority() const`
- L240 _public function_ `inline bool RequiresPriorityOrResourceManagement() const`
- L241 _public function_ `inline FGameplayResourceSet GetRequiredResources() const`
- L242 _public function_ `inline FGameplayResourceSet GetClaimedResources() const`
- L244 _public function_ `inline EGameplayTaskState GetState() const`
- L245 _public function_ `inline bool IsActive() const`
- L246 _public function_ `inline bool IsPaused() const`
- L247 _public function_ `inline bool IsFinished() const`
- L249 _public function_ `UGameplayTask* GetChildTask() const`
- L250 _public function_ `IGameplayTaskOwnerInterface* GetTaskOwner() const`
- L251 _public function_ `UGameplayTasksComponent* GetGameplayTasksComponent()`
- L252 _public function_ `UGameplayTasksComponent* GetGameplayTasksComponent() const`
- L253 _public function_ `bool IsOwnedByTasksComponent() const`
- L256 _public function_ `template <class T> inline void AddRequiredResource()`
- L262 _public function_ `template <class T> inline void AddClaimedResource()`
- L273 _public prototype_ `void AddRequiredResource(TSubclassOf<UGameplayTaskResource> RequiredResource);` — Marks this task as requiring specified resource which has a number of consequences, like task not being able to run if the resource is already taken. @note: Calling this function makes sense only until the task is being passed over to the GameplayTasksComponent. Once that's that resources data is consumed and further changes won't get applied
- L274 _public prototype_ `void AddRequiredResourceSet(const TArray<TSubclassOf<UGameplayTaskResource> >& RequiredResourceSet);`
- L275 _public prototype_ `void AddRequiredResourceSet(FGameplayResourceSet RequiredResourceSet);`
- L279 _public prototype_ `void AddClaimedResource(TSubclassOf<UGameplayTaskResource> ClaimedResource);`
- L280 _public prototype_ `void AddClaimedResourceSet(const TArray<TSubclassOf<UGameplayTaskResource> >& AdditionalResourcesToClaim);`
- L281 _public prototype_ `void AddClaimedResourceSet(FGameplayResourceSet AdditionalResourcesToClaim);`
- L283 _public function_ `ETaskResourceOverlapPolicy GetResourceOverlapPolicy() const`
- L285 _public function_ `virtual bool IsWaitingOnRemotePlayerdata() const`
- L287 _public function_ `virtual bool IsWaitingOnAvatar() const`
- L289 _public prototype_ `FString GetTaskStateName() const;`
- L297 _protected prototype_ `virtual void OnDestroy(bool bInOwnerFinished);` — End and CleanUp the task - may be called by the task itself or by the task owner if the owner is ending. IMPORTANT! Do NOT call directly! Call EndTask() or TaskOwnerEnded() IMPORTANT! When overriding this function make sure to call Super::OnDestroy(bOwnerFinished) as the last thing, since the function internally marks the task as "Pending Kill", and this may interfere with internal BP mechanics
- L299 _protected prototype_ `static IGameplayTaskOwnerInterface* ConvertToTaskOwner(UObject& OwnerObject);`
- L300 _protected prototype_ `static IGameplayTaskOwnerInterface* ConvertToTaskOwner(AActor& OwnerActor);`
- L303 _protected prototype_ `virtual void Pause();` — protected by design. Not meant to be called outside from GameplayTaskComponent mechanics
- L304 _protected prototype_ `virtual void Resume();`
- L307 _protected prototype_ `virtual UGameplayTasksComponent* GetGameplayTasksComponent(const UGameplayTask& Task) const override;` — IGameplayTaskOwnerInterface BEGIN
- L308 _protected prototype_ `virtual AActor* GetGameplayTaskOwner(const UGameplayTask* Task) const override;`
- L309 _protected prototype_ `virtual AActor* GetGameplayTaskAvatar(const UGameplayTask* Task) const override;`
- L310 _protected prototype_ `virtual uint8 GetGameplayTaskDefaultPriority() const override;`
- L311 _protected prototype_ `virtual void OnGameplayTaskInitialized(UGameplayTask& Task) override;`
- L312 _protected prototype_ `virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) override;`
- L316 _protected prototype_ `virtual void RegisterReplicationFragments(UE::Net::FFragmentRegistrationContext& Context, UE::Net::EFragmentRegistrationFlags RegistrationFlags) override;` — Register all replication fragments
- L321 _private prototype_ `void ActivateInTaskQueue();`
- L322 _private prototype_ `void PauseInTaskQueue();`
- L324 _private prototype_ `void PerformActivation();`
- L330 _protected member_ `FName InstanceName;` — `UPROPERTY()` — This name allows us to find the task later so that we can end it.
- L334 _protected member_ `uint8 Priority;` — This controls how this task will be treated in relation to other, already running tasks, provided GameplayTasksComponent is configured to care about priorities (the default behavior)
- L338 _protected member_ `EGameplayTaskState TaskState;` — You should _never_ access it directly. We'll make it private once we have a good way of "deprecating: direct access
- L341 _protected member_ `ETaskResourceOverlapPolicy ResourceOverlapPolicy;` — `UPROPERTY(config)`
- L344 _protected member_ `uint32 bTickingTask : 1;` — If true, this task will receive TickTask calls from TasksComponent
- L347 _protected member_ `uint32 bSimulatedTask : 1;` — Should this task run on simulated clients? This should only be used in rare cases, such as movement tasks. Simulated Tasks do not broadcast their end delegates.
- L350 _protected member_ `uint32 bIsSimulating : 1;` — Am I actually running this as a simulated task. (This will be true on clients that simulating. This will be false on the server and the owning client)
- L352 _protected member_ `uint32 bIsPausable : 1;`
- L354 _protected member_ `uint32 bCaresAboutPriority : 1;`
- L357 _protected member_ `uint32 bOwnedByTasksComponent : 1;` — this is set to avoid duplicate calls to task's owner and TasksComponent when both are the same object
- L359 _protected member_ `uint32 bClaimRequiredResources : 1;`
- L361 _protected member_ `uint32 bOwnerFinished : 1;`
- L364 _protected member_ `FGameplayResourceSet RequiredResources;` — Abstract "resource" IDs this task needs available to be able to get activated.
- L369 _protected member_ `FGameplayResourceSet ClaimedResources;` — Resources that are going to be locked when this task gets activated, but are not required to get this task started
- L372 _protected member_ `TWeakInterfacePtr<IGameplayTaskOwnerInterface> TaskOwner;` — Task Owner that created us
- L374 _protected member_ `TWeakObjectPtr<UGameplayTasksComponent> TasksComponent;`
- L378 _protected member_ `TObjectPtr<UGameplayTask> ChildTask;` — `UPROPERTY()` — child task instance
- L381 _protected member_ `mutable FString DebugDescription;`
- L383 _public function_ `const FString& GetDebugDescription() const`
- L391 _public prototype_ `virtual FString GenerateDebugDescription() const;`
- L396 _function_ `template <class T> T* UGameplayTask::NewTask(UObject& WorldContextObject, FName InstanceName)`
- L403 _function_ `template <class T> T* UGameplayTask::NewTask(IGameplayTaskOwnerInterface& TaskOwner, FName InstanceName)`

#### struct `FGameplayTaskInstanceNamePredicate`  
`struct FGameplayTaskInstanceNamePredicate`  
_L412-425_
- desc: For searching through lists of task instances
- L414 _public function_ `FGameplayTaskInstanceNamePredicate(FName DesiredInstanceName)`
- L419 _public function_ `bool operator()(const UGameplayTask* A) const`
- L424 _public member_ `FName InstanceName;`

#### struct `FGameplayTaskInstanceClassPredicate`  
`struct FGameplayTaskInstanceClassPredicate`  
_L428-441_
- L430 _public function_ `FGameplayTaskInstanceClassPredicate(TSubclassOf<UGameplayTask> Class)`
- L435 _public function_ `bool operator()(const UGameplayTask* A) const`
- L440 _public member_ `TSubclassOf<UGameplayTask> TaskClass;`

#### Free symbols / members of external scopes

- L19 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGameplayTasks, Log, All);`
- L54 _enumerator_ `MaxResources = sizeof(FFlagContainer)* 8` (scope `FGameplayResourceSet::__anonfec2c4c40103`)
- L151 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGenericGameplayTaskDelegate);`

### `Source/Runtime/GameplayTasks/Classes/GameplayTaskOwnerInterface.h` (Public)


#### class `UGameplayTaskOwnerInterface`  
`class UGameplayTaskOwnerInterface : public UInterface`  
_L15-18_
- reflection: `UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `IGameplayTaskOwnerInterface`  
`class IGameplayTaskOwnerInterface`  
_L20-45_
- L26 _public prototype_ `virtual UGameplayTasksComponent* GetGameplayTasksComponent(const UGameplayTask& Task) const PURE_VIRTUAL(IGameplayTaskOwnerInterface::GetGameplayTasksComponent, return nullptr;);` — Finds tasks component for given GameplayTask, Task.GetGameplayTasksComponent() may not be initialized at this point!
- L29 _public prototype_ `virtual AActor* GetGameplayTaskOwner(const UGameplayTask* Task) const PURE_VIRTUAL(IGameplayTaskOwnerInterface::GetGameplayTaskOwner, return nullptr;);` — Get owner of a task or default one when task is null
- L32 _public function_ `virtual AActor* GetGameplayTaskAvatar(const UGameplayTask* Task) const` — Get "body" of task's owner / default, having location in world (e.g. Owner = AIController, Avatar = Pawn)
- L35 _public function_ `virtual uint8 GetGameplayTaskDefaultPriority() const` — Get default priority for running a task
- L38 _public function_ `virtual void OnGameplayTaskInitialized(UGameplayTask& Task)` — Notify called after GameplayTask finishes initialization (not active yet)
- L41 _public function_ `virtual void OnGameplayTaskActivated(UGameplayTask& Task)` — Notify called after GameplayTask changes state to Active (initial activation or resuming)
- L44 _public function_ `virtual void OnGameplayTaskDeactivated(UGameplayTask& Task)` — Notify called after GameplayTask changes state from Active (finishing or pausing)

### `Source/Runtime/GameplayTasks/Classes/GameplayTaskResource.h` (Public)


#### class `UGameplayTaskResource`  
`class UGameplayTaskResource : public UObject`  
_L14-71_
- reflection: `UCLASS(Abstract, config = "Game", hidedropdown, MinimalAPI)`
- inherits: `UObject`
- L21 _protected member_ `int32 ManualResourceID;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Task Resource", meta = (ClampMin = "-1", ClampMax = "15", UIMin = "-1", UIMax = "15", EditCondition = "bManuallySetID"), config)` — Overrides AutoResourceID. -1 means auto ID will be applied
- L25 _private member_ `int8 AutoResourceID;` — `UPROPERTY()`
- L29 _public member_ `uint32 bManuallySetID : 1;` — `UPROPERTY(EditDefaultsOnly, Category = "Task Resource", meta=(InlineEditConditionToggle))`
- L33 _public prototype_ `UGameplayTaskResource(const FObjectInitializer& ObjectInitializer);`
- L35 _public function_ `uint8 GetResourceID() const`
- L41 _public function_ `template <class T> static uint8 GetResourceID()`
- L46 _public function_ `static uint8 GetResourceID(const TSubclassOf<UGameplayTaskResource>& RequiredResource)`
- L51 _public prototype_ `virtual void PostInitProperties() override;`
- L55 _protected prototype_ `void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);`
- L58 _protected prototype_ `void UpdateAutoResourceID();`
- L62 _protected member_ `static TArray<FString> ResourceDescriptions;`
- L63 _protected prototype_ `virtual FString GenerateDebugDescription() const;`
- L66 _public function_ `static FString GetDebugDescription(uint8 ResourceId)`

### `Source/Runtime/GameplayTasks/Classes/GameplayTasksComponent.h` (Public)


#### enum `EGameplayTaskEvent`  
`enum class EGameplayTaskEvent : uint8`  
_L23-27_
- L25 _public enumerator_ `Add`
- L26 _public enumerator_ `Remove`

#### enum `EGameplayTaskRunResult`  
`enum class EGameplayTaskRunResult : uint8`  
_L30-41_
- reflection: `UENUM()`
- L33 _public enumerator_ `Error` — When tried running a null-task
- L34 _public enumerator_ `Failed`
- L36 _public enumerator_ `Success_Paused` — Successfully registered for running, but currently paused due to higher priority tasks running
- L38 _public enumerator_ `Success_Active` — Successfully activated
- L40 _public enumerator_ `Success_Finished` — Successfully activated, but finished instantly

#### struct `FGameplayTaskEventData`  
`struct FGameplayTaskEventData`  
_L43-53_
- L45 _public member_ `EGameplayTaskEvent Event;`
- L46 _public member_ `UGameplayTask& RelatedTask;`
- L48 _public function_ `FGameplayTaskEventData(EGameplayTaskEvent InEvent, UGameplayTask& InRelatedTask) : Event(InEvent), RelatedTask(InRelatedTask)`

#### class `UGameplayTasksComponent`  
`class UGameplayTasksComponent : public UActorComponent, public IGameplayTaskOwnerInterface, public IVisualLoggerDebugSnapshotInterface`  
_L61-213_
- reflection: `UCLASS(ClassGroup = GameplayTasks, hidecategories = (Object, LOD, Lighting, Transform, Sockets, TextureStreaming), editinlinenew, meta = (BlueprintSpawnableComponent), MinimalAPI)`
- inherits: `UActorComponent,IGameplayTaskOwnerInterface,IVisualLoggerDebugSnapshotInterface`
- desc: The core ActorComponent for interfacing with the GameplayAbilities System
- L68 _private member_ `int32 EventLockCounter;`
- L70 _private member_ `uint8 bInEventProcessingInProgress : 1;`
- L74 _protected member_ `uint8 TopActivePriority;` — Indicates what's the highest priority among currently running tasks
- L77 _protected member_ `FGameplayResourceSet CurrentlyClaimedResources;` — Resources used by currently active tasks
- L80 _protected function_ `const TArray<UGameplayTask*>& GetSimulatedTasks()` — Tasks that run on simulated proxies
- L86 _protected prototype_ `void SetSimulatedTasks(const TArray<UGameplayTask*>& NewSimulatedTasks);` — Remove all current tasks and register the one in the passed array. It's optimal to use Add/Remove of single tasks directly if possible.
- L89 _protected prototype_ `bool AddSimulatedTask(UGameplayTask* NewTask);` — Add a new simulated task. Returns true if the task was added to the list. Returns false if the task was already registered.
- L92 _protected prototype_ `void RemoveSimulatedTask(UGameplayTask* NewTask);` — Remove an existing simulated task
- L95 _protected member_ `TArray<TObjectPtr<UGameplayTask>> TaskPriorityQueue;` — `UPROPERTY()`
- L101 _protected member_ `TArray<FGameplayTaskEventData> TaskEvents;` — Transient array of events whose main role is to avoid long chain of recurrent calls if an activated/paused/removed task wants to push/pause/kill other tasks. Note: this TaskEvents is assumed to be used in a single thread
- L105 _protected member_ `TArray<TObjectPtr<UGameplayTask>> TickingTasks;` — `UPROPERTY()` — Array of currently active UGameplayTask that require ticking
- L109 _protected member_ `TArray<TObjectPtr<UGameplayTask>> KnownTasks;` — `UPROPERTY(transient)` — All known tasks (processed by this component) referenced for GC
- L113 _public member_ `FOnClaimedResourcesChangeSignature OnClaimedResourcesChange;` — `UPROPERTY(BlueprintReadWrite, Category = "Gameplay Tasks")`
- L115 _public prototype_ `UGameplayTasksComponent(const FObjectInitializer& ObjectInitializer);`
- L118 _public prototype_ `void OnRep_SimulatedTasks();` — `UFUNCTION()`
- L120 _public prototype_ `virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;`
- L121 _public prototype_ `virtual bool ReplicateSubobjects(UActorChannel *Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;`
- L123 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L124 _public prototype_ `void UpdateShouldTick();`
- L128 _public prototype_ `virtual bool GetShouldTick() const;` — retrieves information whether this component should be ticking taken current activity into consideration
- L132 _public prototype_ `void AddTaskReadyForActivation(UGameplayTask& NewTask);` — processes the task and figures out if it should get triggered instantly or wait based on task's RequiredResources, Priority and ResourceOverlapPolicy
- L134 _public prototype_ `void RemoveResourceConsumingTask(UGameplayTask& Task);`
- L135 _public prototype_ `void EndAllResourceConsumingTasksOwnedBy(const IGameplayTaskOwnerInterface& TaskOwner);`
- L137 _public prototype_ `bool FindAllResourceConsumingTasksOwnedBy(const IGameplayTaskOwnerInterface& TaskOwner, TArray<UGameplayTask*>& FoundTasks) const;`
- L140 _public prototype_ `UGameplayTask* FindResourceConsumingTaskByName(const FName TaskInstanceName) const;` — finds first resource-consuming task of given name
- L142 _public prototype_ `bool HasActiveTasks(UClass* TaskClass) const;`
- L144 _public function_ `inline FGameplayResourceSet GetCurrentlyUsedResources() const`
- L147 _public function_ `virtual UGameplayTasksComponent* GetGameplayTasksComponent(const UGameplayTask& Task) const` — BEGIN IGameplayTaskOwnerInterface
- L148 _public function_ `virtual AActor* GetGameplayTaskOwner(const UGameplayTask* Task) const override`
- L149 _public function_ `virtual AActor* GetGameplayTaskAvatar(const UGameplayTask* Task) const override`
- L150 _public prototype_ `virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;`
- L151 _public prototype_ `virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) override;`
- L155 _public prototype_ `virtual void ReadyForReplication() override;` — ActorComponent overrides
- L158 _public prototype_ `static EGameplayTaskRunResult K2_RunGameplayTask(TScriptInterface<IGameplayTaskOwnerInterface> TaskOwner, UGameplayTask* Task, uint8 Priority, TArray<TSubclassOf<UGameplayTaskResource> > AdditionalRequiredResources, TArray<TSubclassOf<UGameplayTaskResource> > AdditionalClaimedResources);` — `UFUNCTION(BlueprintCallable, DisplayName="Run Gameplay Task", meta=(ScriptName="RunGameplayTask"), Category = "Gameplay Tasks", meta = (AutoCreateRefTerm = "AdditionalRequiredResources, AdditionalClaimedResources", AdvancedDisplay = "AdditionalRequiredResources, AdditionalClaimedResources"))`
- L160 _public prototype_ `static EGameplayTaskRunResult RunGameplayTask(IGameplayTaskOwnerInterface& TaskOwner, UGameplayTask& Task, uint8 Priority, FGameplayResourceSet AdditionalRequiredResources, FGameplayResourceSet AdditionalClaimedResources);`
- L163 _public prototype_ `FString GetTickingTasksDescription() const;`
- L164 _public prototype_ `FString GetKnownTasksDescription() const;`
- L165 _public prototype_ `FString GetTasksPriorityQueueDescription() const;`
- L166 _public prototype_ `static FString GetTaskStateName(EGameplayTaskState Value);`
- L168 _public typedef_ `using GameplayTaskContainerType = decltype(TickingTasks);`
- L169 _public prototype_ `GameplayTaskContainerType::TConstIterator GetTickingTaskIterator() const;`
- L170 _public prototype_ `GameplayTaskContainerType::TConstIterator GetKnownTaskIterator() const;`
- L171 _public prototype_ `GameplayTaskContainerType::TConstIterator GetPriorityQueueIterator() const;`
- L172 _public prototype_ `GameplayTaskContainerType::TConstIterator GetSimulatedTaskIterator() const;`
- L175 _public prototype_ `virtual void GrabDebugSnapshot(FVisualLogEntry* Snapshot) const override;`
- L176 _public prototype_ `void DescribeSelfToVisLog(struct FVisualLogEntry* Snapshot) const;`
- L189 _protected prototype_ `void RequestTicking();`
- L190 _protected prototype_ `void ProcessTaskEvents();`
- L191 _protected prototype_ `void UpdateTaskActivations();`
- L193 _protected prototype_ `void SetCurrentlyClaimedResources(FGameplayResourceSet NewClaimedSet);`
- L197 _private prototype_ `void OnTaskEnded(UGameplayTask& Task);` — called when a task gets ended with an external call, meaning not coming from UGameplayTasksComponent mechanics
- L199 _private prototype_ `void AddTaskToPriorityQueue(UGameplayTask& NewTask);`
- L200 _private prototype_ `void RemoveTaskFromPriorityQueue(UGameplayTask& Task);`
- L202 _private function_ `inline bool CanProcessEvents() const`
- L204 _private prototype_ `void SetSimulatedTasksNetDirty();`
- L208 _private member_ `TArray<TObjectPtr<UGameplayTask>> SimulatedTasks;` — `UPROPERTY(Transient, ReplicatedUsing = OnRep_SimulatedTasks)` — Tasks that run on simulated proxies
- L211 _private member_ `TArray<TWeakObjectPtr<UGameplayTask>> PreviousOnRepSimulatedTasks;` — Previously replicated tasks that run on simulated proxies

#### struct `UGameplayTasksComponent::FEventLock`  
`struct FEventLock`  
_L180-187_
- L182 _public prototype_ `FEventLock(UGameplayTasksComponent* InOwner);`
- L183 _public prototype_ `~FEventLock();`
- L186 _protected member_ `UGameplayTasksComponent* Owner;`

#### Free symbols / members of external scopes

- L55 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnClaimedResourcesChangeSignature, FGameplayResourceSet, NewlyClaimed, FGameplayResourceSet, FreshlyReleased);`
- L55 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnClaimedResourcesChangeSignature, FGameplayResourceSet, NewlyClaimed, FGameplayResourceSet, FreshlyReleased);`
- L215 _typedef_ `typedef UGameplayTasksComponent::GameplayTaskContainerType::TConstIterator FConstGameplayTaskIterator;`

### `Source/Runtime/GameplayTasks/Classes/Tasks/GameplayTask_ClaimResource.h` (Public)


#### class `UGameplayTask_ClaimResource`  
`class UGameplayTask_ClaimResource : public UGameplayTask`  
_L15-29_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UGameplayTask`
- L19 _public prototype_ `UGameplayTask_ClaimResource(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L22 _public prototype_ `static UGameplayTask_ClaimResource* ClaimResource(TScriptInterface<IGameplayTaskOwnerInterface> InTaskOwner, TSubclassOf<UGameplayTaskResource> ResourceClass, const uint8 Priority = 192, const FName TaskInstanceName = NAME_None);` — `UFUNCTION(BlueprintCallable, Category = "AI|Tasks", meta = (AdvancedDisplay = "Priority, TaskInstanceName"))`
- L25 _public prototype_ `static UGameplayTask_ClaimResource* ClaimResources(TScriptInterface<IGameplayTaskOwnerInterface> InTaskOwner, TArray<TSubclassOf<UGameplayTaskResource> > ResourceClasses, const uint8 Priority = 192, const FName TaskInstanceName = NAME_None);` — `UFUNCTION(BlueprintCallable, Category = "AI|Tasks", meta = (AdvancedDisplay = "Priority, TaskInstanceName"))`
- L27 _public prototype_ `static UGameplayTask_ClaimResource* ClaimResource(IGameplayTaskOwnerInterface& InTaskOwner, const TSubclassOf<UGameplayTaskResource> ResourceClass, const uint8 Priority = FGameplayTasks::DefaultPriority, const FName TaskInstanceName = NAME_None);`
- L28 _public prototype_ `static UGameplayTask_ClaimResource* ClaimResources(IGameplayTaskOwnerInterface& InTaskOwner, const TArray<TSubclassOf<UGameplayTaskResource> >& ResourceClasses, const uint8 Priority = FGameplayTasks::DefaultPriority, const FName TaskInstanceName = NAME_None);`

### `Source/Runtime/GameplayTasks/Classes/Tasks/GameplayTask_SpawnActor.h` (Public)


#### class `UGameplayTask_SpawnActor`  
`class UGameplayTask_SpawnActor : public UGameplayTask`  
_L29-55_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGameplayTask`
- L34 _public member_ `FGameplayTaskSpawnActorDelegate Success;` — `UPROPERTY(BlueprintAssignable)`
- L38 _public member_ `FGameplayTaskSpawnActorDelegate DidNotSpawn;` — `UPROPERTY(BlueprintAssignable)` — Called when we can't spawn: on clients or potentially on server if they fail to spawn (rare)
- L42 _public prototype_ `static UGameplayTask_SpawnActor* SpawnActor(TScriptInterface<IGameplayTaskOwnerInterface> TaskOwner, FVector SpawnLocation, FRotator SpawnRotation, TSubclassOf<AActor> Class, bool bSpawnOnlyOnAuthority = false);` — `UFUNCTION(BlueprintCallable, Category = "GameplayTasks", meta = (DisplayName="Spawn Actor for Gameplay Task", AdvancedDisplay = "TaskOwner, bSpawnOnlyOnAuthority", DefaultToSelf = "TaskOwner", BlueprintInternalUseOnly = "TRUE"))` — Spawn new Actor on the network authority (server)
- L45 _public prototype_ `virtual bool BeginSpawningActor(UObject* WorldContextObject, AActor*& SpawnedActor);` — `UFUNCTION(BlueprintCallable, meta = (WorldContext="WorldContextObject", BlueprintInternalUseOnly = "true"), Category = "GameplayTasks")`
- L48 _public prototype_ `virtual void FinishSpawningActor(UObject* WorldContextObject, AActor* SpawnedActor);` — `UFUNCTION(BlueprintCallable, meta = (WorldContext="WorldContextObject", BlueprintInternalUseOnly = "true"), Category = "GameplayTasks")`
- L51 _protected member_ `FVector CachedSpawnLocation;`
- L52 _protected member_ `FRotator CachedSpawnRotation;`
- L54 _protected member_ `TSubclassOf<AActor> ClassToSpawn;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameplayTaskSpawnActorDelegate, AActor*, SpawnedActor);`
- L13 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameplayTaskSpawnActorDelegate, AActor*, SpawnedActor);`

### `Source/Runtime/GameplayTasks/Classes/Tasks/GameplayTask_TimeLimitedExecution.h` (Public)


#### class `UGameplayTask_TimeLimitedExecution`  
`class UGameplayTask_TimeLimitedExecution : public UGameplayTask`  
_L18-53_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGameplayTask`
- desc: Adds time limit for running a child task - child task needs to be created with UGameplayTask_TimeLimitedExecution passed as TaskOwner - activations are tied together and when either UGameplayTask_TimeLimitedExecution or child task is activated, other one starts as well - OnFinished and OnTimeExpired are mutually exclusive
- L22 _private prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTaskFinishDelegate);`
- L25 _public prototype_ `UGameplayTask_TimeLimitedExecution(const FObjectInitializer& ObjectInitializer);`
- L29 _public member_ `FTaskFinishDelegate OnFinished;` — `UPROPERTY(BlueprintAssignable)` — called when child task finishes execution before time runs out
- L33 _public member_ `FTaskFinishDelegate OnTimeExpired;` — `UPROPERTY(BlueprintAssignable)` — called when time runs out
- L35 _public prototype_ `virtual void Activate() override;`
- L36 _public prototype_ `virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;`
- L37 _public prototype_ `virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) override;`
- L40 _public prototype_ `virtual FString GetDebugString() const override;` — Return debug string describing task
- L42 _public prototype_ `static UGameplayTask_TimeLimitedExecution* LimitExecutionTime(IGameplayTaskOwnerInterface& InTaskOwner, float Time, const uint8 Priority = FGameplayTasks::DefaultPriority, const FName InInstanceName = FName());`
- L46 _private prototype_ `void OnTimer();`
- L48 _private member_ `double Time;`
- L49 _private member_ `double TimeStarted;`
- L51 _private member_ `uint32 bTimeExpired : 1;`
- L52 _private member_ `uint32 bChildTaskFinished : 1;`

#### Free symbols / members of external scopes

- L22 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTaskFinishDelegate);`

### `Source/Runtime/GameplayTasks/Classes/Tasks/GameplayTask_WaitDelay.h` (Public)


#### class `UGameplayTask_WaitDelay`  
`class UGameplayTask_WaitDelay : public UGameplayTask`  
_L12-41_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGameplayTask`
- L16 _private prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTaskDelayDelegate);`
- L19 _public prototype_ `UGameplayTask_WaitDelay(const FObjectInitializer& ObjectInitializer);`
- L22 _public member_ `FTaskDelayDelegate OnFinish;` — `UPROPERTY(BlueprintAssignable)`
- L24 _public prototype_ `virtual void Activate() override;`
- L27 _public prototype_ `virtual FString GetDebugString() const override;` — Return debug string describing task
- L31 _public prototype_ `static UGameplayTask_WaitDelay* TaskWaitDelay(TScriptInterface<IGameplayTaskOwnerInterface> TaskOwner, float Time, const uint8 Priority = 192);` — `UFUNCTION(BlueprintCallable, Category = "GameplayTasks", meta = (AdvancedDisplay = "TaskOwner, Priority", DefaultToSelf = "TaskOwner", BlueprintInternalUseOnly = "TRUE"))` — Wait specified time. This is functionally the same as a standard Delay node.
- L33 _public prototype_ `static UGameplayTask_WaitDelay* TaskWaitDelay(IGameplayTaskOwnerInterface& InTaskOwner, float Time, const uint8 Priority = FGameplayTasks::DefaultPriority);`
- L37 _private prototype_ `void OnTimeFinish();`
- L39 _private member_ `double Time;`
- L40 _private member_ `double TimeStarted;`

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTaskDelayDelegate);`

### `Source/Runtime/GameplayTasks/Private/GameplayTasksPrivate.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_STATS_GROUP(TEXT("GameplayTasks"), STATGROUP_GameplayTasks, STATC`
- L9 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("TickGameplayTasks"), STAT_TickGameplayTasks, STATGROUP_`

### `Source/Runtime/GameplayTasks/Public/GameplayTaskTypes.h` (Public)


#### Free symbols / members of external scopes

- L12 _macro_ `#define WITH_GAMEPLAYTASK_DEBUG (WITH_UNREAL_DEVELOPER_TOOLS || !(UE_BUILD_SHIPPING || UE_BUILD_TEST) || UE_DEBUG_RENDERING_ENABLED)`
- L15 _namespace_ `namespace FGameplayTasks`
- L17 _variable_ `inline constexpr uint8 DefaultPriority = 127;` (scope `FGameplayTasks`)
- L18 _variable_ `inline constexpr uint8 ScriptedPriority = 192;` (scope `FGameplayTasks`)

### `Source/Runtime/GameplayTasks/Public/GameplayTasksModule.h` (Public)


#### class `IGameplayTasksModule`  
`class IGameplayTasksModule : public IModuleInterface`  
_L13-38_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L24 _public function_ `static inline IGameplayTasksModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L34 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
