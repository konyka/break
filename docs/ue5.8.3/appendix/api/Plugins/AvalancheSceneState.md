# Plugins / AvalancheSceneState

- module root: `Plugins/VirtualProduction/AvalancheSceneState/Source/AvalancheSceneState`
- headers: 12; symbols: 90
- symbol kinds: class=6, delegate=1, function=3, macro=3, member=18, namespace=7, prototype=39, struct=8, typedef=4, variable=1
- PrivateDependencyModuleNames: Avalanche, Engine, PropertyBindingUtils, RemoteControl, RemoteControlLogic, SceneStateBlueprint, SceneStateBlueprintEditor, SceneStateEvent
- PublicDependencyModuleNames: AvalancheRemoteControl, AvalancheSequence, AvalancheTag, Core, CoreUObject, SceneState, SceneStateBinding, SceneStateGameplay, SceneStateTasks

### `Plugins/VirtualProduction/AvalancheSceneState/Source/AvalancheSceneState/Private/AvaSceneStateLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvaSceneState, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvaSceneState, Log, All);`

### `Plugins/VirtualProduction/AvalancheSceneState/Source/AvalancheSceneState/Private/AvaSceneStateUtils.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace AvaSceneState` (scope `UE`)
- L10 _prototype_ `IAvaSceneInterface* FindSceneInterface(const FSceneStateExecutionContext& InContext);` (scope `UE::AvaSceneState`)

### `Plugins/VirtualProduction/AvalancheSceneState/Source/AvalancheSceneState/Public/AvaSceneStateActor.h` (Public)


#### class `AAvaSceneStateActor`  
`class AAvaSceneStateActor : public ASceneStateActor`  
_L18-66_
- reflection: `UCLASS(MinimalAPI, NotBlueprintable, NotPlaceable, DisplayName="Motion Design Scene State Actor", HideCategories=(Actor, Collision, Cooking, DataLayers, HLOD, Input, LevelInstance, Networking, Physics, Rendering, Replication, WorldPartition))`
- inherits: `ASceneStateActor`
- desc: Scene State Actor that has additional editor-only data holding the Scene State Blueprint
- L23 _public prototype_ `AAvaSceneStateActor(const FObjectInitializer& InObjectInitializer);`
- L28 _protected prototype_ `virtual FString GetDefaultActorLabel() const override;`
- L29 _protected function_ `virtual bool IsUserManaged() const override`
- L30 _protected function_ `virtual bool SupportsExternalPackaging() const override`
- L34 _protected prototype_ `virtual void PostLoad() override;`
- L35 _protected prototype_ `virtual void PostDuplicate(bool bInDuplicateForPIE) override;`
- L36 _protected prototype_ `virtual void BeginDestroy() override;`
- L40 _protected prototype_ `void UpdateSceneStateClass();` — Updates the scene state class to the latest generated class from the scene state blueprint if valid
- L42 _protected prototype_ `void SetSceneStateBlueprint(USceneStateBlueprint* InSceneStateBlueprint);`
- L45 _protected prototype_ `void OnSceneStateRecompiled(UBlueprint* InCompiledBlueprint);` — Called when the scene state blueprint is compiled
- L48 _protected prototype_ `void OnWorldRenamed(UWorld* InNewWorld);` — Called when the world is renamed
- L51 _protected prototype_ `void OnWorldCleanup(UWorld* InWorld, bool bInSessionEnded, bool bInCleanupResources);` — Called on World destruction / change to clean up scene state blueprint resources
- L57 _private prototype_ `void CleanupSceneState();` — Cleans up scene state resources
- L62 _private member_ `TObjectPtr<UBlueprint> SceneStateBlueprint;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AVALANCHESCENESTATE_API`

### `Plugins/VirtualProduction/AvalancheSceneState/Source/AvalancheSceneState/Public/AvaSceneStateComponent.h` (Public)


#### class `UAvaSceneStateComponent`  
`class UAvaSceneStateComponent : public USceneStateComponent`  
_L9-14_
- reflection: `UCLASS(HideCategories=(Activation, AssetUserData, Cooking, Input, Navigation, Tags))`
- inherits: `USceneStateComponent`
- L13 _private prototype_ `UAvaSceneStateComponent(const FObjectInitializer& InObjectInitializer);`

### `Plugins/VirtualProduction/AvalancheSceneState/Source/AvalancheSceneState/Public/AvaSceneStatePlayer.h` (Public)


#### class `UAvaSceneStatePlayer`  
`class UAvaSceneStatePlayer : public USceneStateComponentPlayer`  
_L9-14_
- reflection: `UCLASS()`
- inherits: `USceneStateComponentPlayer`
- L13 _private prototype_ `UAvaSceneStatePlayer();`

### `Plugins/VirtualProduction/AvalancheSceneState/Source/AvalancheSceneState/Public/AvaSceneStateSchema.h` (Public)


#### class `UAvaSceneStateSchema`  
`class UAvaSceneStateSchema : public USceneStateGameplaySchema`  
_L23-33_
- reflection: `UCLASS(MinimalAPI, DisplayName="Motion Design Scene State Schema")`
- inherits: `USceneStateGameplaySchema`
- desc: Schema for Motion Design scene states.
- L30 _protected prototype_ `virtual bool OnIsTaskStructAllowed(TSubScriptStructOf<FSceneStateTask> InTaskStruct) const override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API AVALANCHESCENESTATE_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace AvaSceneState` (scope `UE`)
- L11 _namespace_ `namespace Editor` (scope `UE::AvaSceneState`)
- L17 _variable_ `const FLazyName MD_MotionDesignTask(TEXT("Moti` (scope `UE::AvaSceneState::Editor`) — Metadata to identify a task as a Motion Design task Derived tasks will NOT be recognized as 'MotionDesignTask' unless they also specify this metadata.

### `Plugins/VirtualProduction/AvalancheSceneState/Source/AvalancheSceneState/Public/RemoteControl/AvaSceneStateRCEventBehavior.h` (Public)


#### class `UAvaSceneStateRCEventBehavior`  
`class UAvaSceneStateRCEventBehavior : public URCBehaviour`  
_L9-12_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `URCBehaviour`

### `Plugins/VirtualProduction/AvalancheSceneState/Source/AvalancheSceneState/Public/RemoteControl/AvaSceneStateRCEventBehaviorNode.h` (Public)


#### class `UAvaSceneStateRCEventBehaviorNode`  
`class UAvaSceneStateRCEventBehaviorNode : public URCBehaviourNode`  
_L10-28_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `URCBehaviourNode`
- L15 _public prototype_ `UAvaSceneStateRCEventBehaviorNode();`
- L19 _protected prototype_ `bool Execute(URCBehaviour* InBehavior) const override;`
- L20 _protected prototype_ `bool IsSupported(URCBehaviour* InBehavior) const override;`
- L21 _protected prototype_ `void OnPassed(URCBehaviour* InBehavior) const;`
- L22 _protected prototype_ `UClass* GetBehaviourClass() const override;`
- L27 _private member_ `FSceneStateEventTemplate Event;` — `UPROPERTY(EditAnywhere, Category="Scene State")`

### `Plugins/VirtualProduction/AvalancheSceneState/Source/AvalancheSceneState/Public/RemoteControl/AvaSceneStateRCTask.h` (Public)


#### struct `FAvaSceneStateRCControllerMapping`  
`struct FAvaSceneStateRCControllerMapping`  
_L17-33_
- reflection: `USTRUCT()`
- L21 _public function_ `bool operator==(const FGuid& InPropertyId) const`
- L28 _public member_ `FAvaRCControllerId TargetController;` — `UPROPERTY(EditAnywhere, Category="Scene State")` — Id to the controller to copy the value to
- L32 _public member_ `FGuid SourcePropertyId;` — `UPROPERTY(EditAnywhere, Category="Scene State")` — Id of the property (in property bag) whose value will be copied into the target controller

#### struct `FAvaSceneStateRCTaskInstance`  
`struct FAvaSceneStateRCTaskInstance : public FSceneStateTaskInstance`  
_L40-55_
- reflection: `USTRUCT()`
- inherits: `FSceneStateTaskInstance`
- desc: Instance Data for the RC Task @see FAvaSceneStateRCTask
- L47 _public member_ `FGuid ControllerValuesId;` — `UPROPERTY(VisibleAnywhere, Category="Scene State", meta=(NoBinding))` — Struct Id uniquely identifying ControllerValues
- L51 _public member_ `TArray<FAvaSceneStateRCControllerMapping> ControllerMappings;` — `UPROPERTY(EditAnywhere, Category="Scene State")`
- L54 _public member_ `FInstancedPropertyBag ControllerValues;` — `UPROPERTY(EditAnywhere, Category="Scene State")`

#### struct `FAvaSceneStateRCTask`  
`struct FAvaSceneStateRCTask : public FSceneStateTask`  
_L58-81_
- reflection: `USTRUCT(DisplayName="Set RC Controller Values", Category="Motion Design", meta=(MotionDesignTask, RequiresContextWorld))`
- inherits: `FSceneStateTask`
- L62 _public typedef_ `using FInstanceDataType = FAvaSceneStateRCTaskInstance;`
- L64 _public prototype_ `FAvaSceneStateRCTask();`
- L69 _protected prototype_ `virtual const UScriptStruct* OnGetTaskInstanceType() const override;`
- L70 _protected prototype_ `virtual void OnBuildTaskInstance(UObject* InOuter, FStructView InTaskInstance) const override;`
- L72 _protected prototype_ `virtual const FSceneStateTaskBindingExtension* OnGetBindingExtension() const override;`
- L73 _protected prototype_ `virtual void OnStart(const FSceneStateExecutionContext& InContext, FStructView InTaskInstance) const override;`
- L77 _private prototype_ `bool GetControllerDataView(const FSceneStateExecutionContext& InContext, FStructView& OutControllerView, URemoteControlPreset*& OutPreset) const;`
- L80 _private member_ `FAvaSceneStateRCTaskBinding Binding;` — `UPROPERTY()`

### `Plugins/VirtualProduction/AvalancheSceneState/Source/AvalancheSceneState/Public/RemoteControl/AvaSceneStateRCTaskBinding.h` (Public)


#### struct `FAvaSceneStateRCTaskBinding`  
`struct FAvaSceneStateRCTaskBinding : public FSceneStateTaskBindingExtension`  
_L11-34_
- reflection: `USTRUCT()`
- inherits: `FSceneStateTaskBindingExtension`
- L15 _public typedef_ `using FInstanceDataType = FAvaSceneStateRCTaskInstance;`
- L18 _public member_ `static constexpr uint16 CONTROLLER_VALUES_DATA_INDEX = 0;` — Data View Indices
- L23 _protected prototype_ `virtual void VisitBindingDescs(FStructView InTaskInstance, TFunctionRef<void(const UE::SceneState::FTaskBindingDesc&)> InFunctor) const override;`
- L24 _protected prototype_ `virtual void SetBindingBatch(uint16 InDataIndex, uint16 InBatchIndex) override;`
- L25 _protected prototype_ `virtual bool FindDataById(FStructView InTaskInstance, const FGuid& InStructId, FStructView& OutDataView, uint16& OutDataIndex) const override;`
- L27 _protected prototype_ `virtual bool FindDataByIndex(FStructView InTaskInstance, uint16 InDataIndex, FStructView& OutDataView) const override;`
- L28 _protected prototype_ `virtual void VisitBindingBatches(FStructView InTaskInstance, TFunctionRef<void(uint16, FStructView)> InFunctor) const override;`
- L33 _private member_ `uint16 ControllerValuesBatchIndex = std::numeric_limits<uint16>::max();` — `UPROPERTY()`

### `Plugins/VirtualProduction/AvalancheSceneState/Source/AvalancheSceneState/Public/Sequence/AvaSceneStatePlaySequenceTask.h` (Public)


#### struct `FAvaSceneStatePlaySequenceTaskInstance`  
`struct FAvaSceneStatePlaySequenceTaskInstance : public FSceneStateTaskInstance`  
_L22-50_
- reflection: `USTRUCT()`
- inherits: `FSceneStateTaskInstance`
- L28 _public member_ `EAvaTransitionSequenceQueryType SequenceQueryType = EAvaTransitionSequenceQueryType::Name;` — `UPROPERTY(EditAnywhere, Category="Sequence")` — The method to find the sequence to play
- L32 _public member_ `FAvaSequenceName SequenceName;` — `UPROPERTY(EditAnywhere, Category="Sequence", meta=(EditCondition="SequenceQueryType==EAvaTransitionSequenceQueryType::Name", EditConditionHides))` — The name of the sequences to play (if query type is set to name)
- L36 _public member_ `FAvaTagHandle SequenceTag;` — `UPROPERTY(EditAnywhere, Category="Sequence", meta=(EditCondition="SequenceQueryType==EAvaTransitionSequenceQueryType::Tag", EditConditionHides))` — The tag of the sequences to play (if query type is set to tag)
- L39 _public member_ `FAvaSequencePlayParams PlaySettings;` — `UPROPERTY(EditAnywhere, Category="Sequence")`
- L43 _public member_ `EAvaTransitionSequenceWaitType WaitType = EAvaTransitionSequenceWaitType::WaitUntilStop;` — `UPROPERTY(EditAnywhere, Category="Sequencer")` — The wait type before this task completes
- L47 _public member_ `TArray<TObjectPtr<UAvaSequencePlayer>> SequencePlayers;` — `UPROPERTY(Transient)` — Active sequence players on this instance
- L49 _public member_ `FDelegateHandle OnSequenceFinishedHandle;`

#### struct `FAvaSceneStatePlaySequenceTask`  
`struct FAvaSceneStatePlaySequenceTask : public FSceneStateTask`  
_L53-70_
- reflection: `USTRUCT(DisplayName="Play Sequence", Category="Motion Design", meta=(MotionDesignTask, RequiresContextWorld, ToolTip="Plays a Motion Design Sequence"))`
- inherits: `FSceneStateTask`
- L57 _public typedef_ `using FInstanceDataType = FAvaSceneStatePlaySequenceTaskInstance;`
- L62 _protected prototype_ `virtual const UScriptStruct* OnGetTaskInstanceType() const override;`
- L64 _protected prototype_ `virtual void OnStart(const FSceneStateExecutionContext& InContext, FStructView InTaskInstance) const override;`
- L65 _protected prototype_ `virtual void OnStop(const FSceneStateExecutionContext& InContext, FStructView InTaskInstance, ESceneStateTaskStopReason InStopReason) const override;`
- L69 _private prototype_ `static void OnSequenceStopped(UAvaSequencePlayer* InPlayer, UAvaSequence* InSequence, UE::SceneState::FTaskExecutionContext InTaskContext);`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace SceneState` (scope `UE`)

### `Plugins/VirtualProduction/AvalancheSceneState/Source/AvalancheSceneState/Public/Ticker/AvaSceneStateSpawnerTickerTask.h` (Public)


#### struct `FAvaSceneStateTickerTaskInstance`  
`struct FAvaSceneStateTickerTaskInstance : public FSceneStateSpawnActorTaskInstance`  
_L11-18_
- reflection: `USTRUCT()`
- inherits: `FSceneStateSpawnActorTaskInstance`
- L17 _public member_ `TObjectPtr<AActor> Ticker;` — `UPROPERTY(EditAnywhere, Category="Ticker")` — The actor to find the ticker component for

#### struct `FAvaSceneStateSpawnerTickerTask`  
`struct FAvaSceneStateSpawnerTickerTask : public FSceneStateSpawnActorTask`  
_L25-42_
- reflection: `USTRUCT(DisplayName="Spawn Actor to Ticker", Category="Motion Design", meta=(MotionDesignTask))`
- inherits: `FSceneStateSpawnActorTask`
- desc: Spawns an actor and adds it to the Ticker. Note: if the Ticker actor is invalid or does not contain a Ticker Component, the actor will not spawn.
- L29 _public typedef_ `using FInstanceDataType = FAvaSceneStateTickerTaskInstance;`
- L34 _protected prototype_ `virtual const UScriptStruct* OnGetTaskInstanceType() const override;`
- L39 _protected prototype_ `virtual bool ShouldSpawnActor(FStructView InTaskInstance, FText& OutErrorMessage) const override;`
- L40 _protected prototype_ `virtual void OnActorSpawned(AActor* InActorChecked, FStructView InTaskInstance) const override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API AVALANCHESCENESTATE_API`
