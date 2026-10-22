# Plugins / GameplayBehaviorsModule

- module root: `Plugins/Experimental/GameplayBehaviors/Source/GameplayBehaviorsModule`
- headers: 14; symbols: 193
- symbol kinds: class=14, delegate=1, enum=2, enumerator=4, function=20, macro=11, member=47, prototype=87, struct=5, typedef=1, union=1
- PublicDependencyModuleNames: AIModule, Core, CoreUObject, Engine, GameplayAbilities, GameplayTags, GameplayTasks

### `Plugins/Experimental/GameplayBehaviors/Source/GameplayBehaviorsModule/Public/AI/BTDecorator_GameplayTagQuery.h` (Public)


#### class `UBTDecorator_GameplayTagQuery`  
`class UBTDecorator_GameplayTagQuery : public UBTDecorator`  
_L21-68_
- reflection: `UCLASS(MinimalAPI, HideCategories=(Condition))`
- inherits: `UBTDecorator`
- L24 _private prototype_ `UBTDecorator_GameplayTagQuery(const FObjectInitializer& ObjectInitializer);`
- L26 _private prototype_ `virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;`
- L29 _private prototype_ `void OnGameplayTagInQueryChanged(const FGameplayTag InTag, int32 NewCount, TWeakObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent);` — Callback for when a tag in our query changes
- L31 _private prototype_ `virtual FString GetStaticDescription() const override;`
- L33 _private prototype_ `virtual void InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const override;`
- L34 _private prototype_ `virtual void CleanupMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryClear::Type CleanupType) const override;`
- L39 _protected member_ `FBlackboardKeySelector ActorForGameplayTagQuery;` — `UPROPERTY(EditAnywhere, Category=GameplayTagQuery, Meta=(ToolTips="Which Actor (from the blackboard) should be checked for this gameplay tag query?"))`
- L43 _protected member_ `FGameplayTagQuery GameplayTagQuery;` — `UPROPERTY(EditAnywhere, Category=GameplayTagQuery)` — Gameplay tag query to match
- L46 _protected member_ `TArray<FGameplayTag> QueryTags;` — `UPROPERTY()`
- L49 _protected prototype_ `virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;` — called when execution flow controller becomes active
- L52 _protected prototype_ `virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;` — called when execution flow controller becomes inactive
- L54 _protected prototype_ `virtual uint16 GetInstanceMemorySize() const override;`
- L62 _protected prototype_ `virtual void CacheGameplayTagsInsideQuery();` — Get the array of tags onto which we need to add delegates The gameplay tag interface forces us to allocate everytime we want to know the list of gameplay tags inside a query so we do this only once and cache it.
- L63 _protected prototype_ `virtual FString GetErrorMessage() const override;`
- L64 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L67 _protected prototype_ `virtual void InitializeFromAsset(UBehaviorTree& Asset) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GAMEPLAYBEHAVIORSMODULE_API`

### `Plugins/Experimental/GameplayBehaviors/Source/GameplayBehaviorsModule/Public/AI/BTTask_SetKeyValueGameplayTag.h` (Public)


#### class `UBTTask_SetKeyValueGameplayTag`  
`class UBTTask_SetKeyValueGameplayTag : public UBTTask_BlackboardBase`  
_L10-23_
- reflection: `UCLASS(DisplayName = "Set GameplayTag Key")`
- inherits: `UBTTask_BlackboardBase`
- L15 _public prototype_ `UBTTask_SetKeyValueGameplayTag(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L17 _public prototype_ `virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L18 _public prototype_ `virtual FString GetStaticDescription() const override;`
- L22 _private member_ `FValueOrBBKey_GameplayTagContainer Value;` — `UPROPERTY(EditAnywhere, Category = Blackboard)`

### `Plugins/Experimental/GameplayBehaviors/Source/GameplayBehaviorsModule/Public/AI/BTTask_StopGameplayBehavior.h` (Public)


#### class `UBTTask_StopGameplayBehavior`  
`class UBTTask_StopGameplayBehavior : public UBTTaskNode`  
_L16-31_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBTTaskNode`
- L20 _public prototype_ `UBTTask_StopGameplayBehavior(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L22 _public prototype_ `virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L23 _public function_ `virtual uint16 GetInstanceMemorySize() const override`
- L25 _public prototype_ `virtual FString GetStaticDescription() const override;`
- L30 _protected member_ `TSubclassOf<UGameplayBehavior> BehaviorToStop;` — `UPROPERTY(EditAnywhere, Category = "Node")` — If None (the default) will stop any and all gameplay behaviors instigated by the agent

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GAMEPLAYBEHAVIORSMODULE_API`

### `Plugins/Experimental/GameplayBehaviors/Source/GameplayBehaviorsModule/Public/AI/GameplayBehaviorConfig_BehaviorTree.h` (Public)


#### class `UGameplayBehaviorConfig_BehaviorTree`  
`class UGameplayBehaviorConfig_BehaviorTree : public UGameplayBehaviorConfig`  
_L15-30_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGameplayBehaviorConfig`
- L19 _public prototype_ `UGameplayBehaviorConfig_BehaviorTree(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L21 _public prototype_ `UBehaviorTree* GetBehaviorTree() const;`
- L22 _public function_ `bool ShouldStorePreviousBT() const`
- L26 _protected member_ `mutable TSoftObjectPtr<UBehaviorTree> BehaviorTree;` — `UPROPERTY(EditAnywhere, Category = SmartObject)`
- L29 _protected member_ `uint32 bRevertToPreviousBTOnFinish : 1;` — `UPROPERTY(EditAnywhere, Category = SmartObject)`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEPLAYBEHAVIORSMODULE_API`

### `Plugins/Experimental/GameplayBehaviors/Source/GameplayBehaviorsModule/Public/AI/GameplayBehavior_BehaviorTree.h` (Public)


#### class `UGameplayBehavior_BehaviorTree`  
`class UGameplayBehavior_BehaviorTree : public UGameplayBehavior`  
_L16-43_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGameplayBehavior`
- desc: NOTE: this behavior works only for AIControlled pawns
- L20 _public prototype_ `UGameplayBehavior_BehaviorTree(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L23 _protected prototype_ `virtual bool Trigger(AActor& InAvatar, const UGameplayBehaviorConfig* Config = nullptr, AActor* SmartObjectOwner = nullptr) override;`
- L24 _protected prototype_ `virtual void EndBehavior(AActor& InAvatar, const bool bInterrupted) override;`
- L25 _protected prototype_ `virtual bool NeedsInstance(const UGameplayBehaviorConfig* Config) const override;`
- L27 _protected prototype_ `void OnTimerTick();`
- L30 _protected prototype_ `void OnPossessedPawnChanged(APawn* OldPawn, APawn* NewPawn);` — `UFUNCTION()`
- L33 _protected member_ `TObjectPtr<UBehaviorTree> PreviousBT;` — `UPROPERTY()`
- L36 _protected member_ `TObjectPtr<AAIController> AIController;` — `UPROPERTY()`
- L40 _protected member_ `bool bSingleRun = true;` — `UPROPERTY(EditAnywhere, Category = SmartObject)` — Indicates if BehaviorTree should run only once or in loop.
- L42 _protected member_ `FTimerHandle TimerHandle;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEPLAYBEHAVIORSMODULE_API`

### `Plugins/Experimental/GameplayBehaviors/Source/GameplayBehaviorsModule/Public/AI/ValueOrBBKey_GameplayTag.h` (Public)


#### struct `FValueOrBBKey_GameplayTagContainer`  
`struct FValueOrBBKey_GameplayTagContainer : public FValueOrBlackboardKeyBase`  
_L11-33_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FValueOrBlackboardKeyBase`
- L15 _public function_ `FValueOrBBKey_GameplayTagContainer(FGameplayTagContainer Default = FGameplayTagContainer()) : DefaultValue(MoveTemp(Default))`
- L17 _public prototype_ `FGameplayTagContainer GetValue(const UBehaviorTreeComponent& BehaviorComp) const;`
- L18 _public prototype_ `FGameplayTagContainer GetValue(const UBehaviorTreeComponent* BehaviorComp) const;`
- L19 _public prototype_ `FGameplayTagContainer GetValue(const UBlackboardComponent& Blackboard) const;`
- L20 _public prototype_ `FGameplayTagContainer GetValue(const UBlackboardComponent* Blackboard) const;`
- L22 _public prototype_ `bool SerializeFromMismatchedTag(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot);`
- L25 _public prototype_ `virtual bool IsCompatibleType(const UBlackboardKeyType* KeyType) const override;`
- L28 _public prototype_ `virtual FString ToString() const override;`
- L32 _protected member_ `FGameplayTagContainer DefaultValue;` — `UPROPERTY(EditAnywhere, Category = "Value")`

#### class `UValueOrBBKey_GameplayTagBlueprintUtility`  
`class UValueOrBBKey_GameplayTagBlueprintUtility : public UBlueprintFunctionLibrary`  
_L36-42_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L41 _public prototype_ `static FGameplayTagContainer GetTagContainer(const FValueOrBBKey_GameplayTagContainer& Value, const UBehaviorTreeComponent* BehaviorTreeComp);` — `UFUNCTION(BlueprintPure, Category = Blackboard)`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FValueOrBBKey_GameplayTagContainer> : public TStructOpsTypeTraitsBase2<FValueOrBBKey_GameplayTagContainer>`  
_L45-51_
- inherits: `TStructOpsTypeTraitsBase2<FValueOrBBKey_GameplayTagContainer>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L48-50_

#### Free symbols / members of external scopes

- L49 _enumerator_ `WithStructuredSerializeFromMismatchedTag = true` (scope `TStructOpsTypeTraits::__anon7034d9210103`)

### `Plugins/Experimental/GameplayBehaviors/Source/GameplayBehaviorsModule/Public/BlackboardKeyType_GameplayTag.h` (Public)


#### class `UBlackboardKeyType_GameplayTag`  
`class UBlackboardKeyType_GameplayTag : public UBlackboardKeyType`  
_L14-40_
- reflection: `UCLASS(MinimalAPI, EditInlineNew, meta = (DisplayName = "Gameplay Tag"))`
- inherits: `UBlackboardKeyType`
- L19 _public prototype_ `UBlackboardKeyType_GameplayTag(const FObjectInitializer& ObjectInitializer);`
- L21 _public typedef_ `typedef FGameplayTagContainer FDataType;`
- L22 _public member_ `static const FDataType InvalidValue;`
- L24 _public prototype_ `static FGameplayTagContainer GetValue(const UBlackboardKeyType_GameplayTag* KeyOb, const uint8* RawData);`
- L25 _public prototype_ `static bool SetValue(UBlackboardKeyType_GameplayTag* KeyOb, uint8* RawData, const FGameplayTagContainer& Value);`
- L27 _public prototype_ `virtual EBlackboardCompare::Type CompareValues(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock, const UBlackboardKeyType* OtherKeyOb, const uint8* OtherMemoryBlock) const override;`
- L31 _public member_ `FGameplayTagContainer DefaultValue = InvalidValue;` — `UPROPERTY(EditDefaultsOnly, Category = Blackboard)`
- L34 _protected prototype_ `virtual FString DescribeValue(const UBlackboardComponent& OwnerComp, const uint8* RawData) const override;`
- L35 _protected prototype_ `virtual bool TestTextOperation(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock, ETextKeyOperation::Type Op, const FString& OtherString) const override;`
- L36 _protected prototype_ `virtual void CopyValues(UBlackboardComponent& OwnerComp, uint8* MemoryBlock, const UBlackboardKeyType* SourceKeyOb, const uint8* SourceBlock) override;`
- L37 _protected prototype_ `virtual void InitializeMemory(UBlackboardComponent& OwnerComp, uint8* MemoryBlock) override;`
- L38 _protected prototype_ `virtual void Clear(UBlackboardComponent& OwnerComp, uint8* MemoryBlock) override;`
- L39 _protected prototype_ `virtual bool IsEmpty(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock) const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEPLAYBEHAVIORSMODULE_API`

### `Plugins/Experimental/GameplayBehaviors/Source/GameplayBehaviorsModule/Public/GameplayBehavior.h` (Public)


#### enum `EGameplayBehaviorInstantiationPolicy`  
`enum class EGameplayBehaviorInstantiationPolicy : uint8`  
_L27-32_
- reflection: `UENUM()`
- L29 _public enumerator_ `Instantiate`
- L30 _public enumerator_ `ConditionallyInstantiate`
- L31 _public enumerator_ `DontInstantiate`

#### class `UGameplayBehavior`  
`class UGameplayBehavior : public UObject, public IGameplayTaskOwnerInterface`  
_L36-189_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable, BlueprintType)`
- inherits: `UObject,IGameplayTaskOwnerInterface`
- L40 _public prototype_ `UGameplayBehavior(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L42 _public prototype_ `virtual void PostInitProperties() override;`
- L43 _public prototype_ `virtual void BeginDestroy() override;`
- L44 _public prototype_ `virtual UWorld* GetWorld() const override;`
- L60 _public prototype_ `virtual bool Trigger(AActor& Avatar, const UGameplayBehaviorConfig* Config = nullptr, AActor* SmartObjectOwner = nullptr);` — Default implementation will trigger the appropriate Blueprint event based on their presence in the script and in the following priority: 1. OnTriggeredCharacter if used and Avatar is a Character 2. OnTriggeredPawn if used and Avatar is a Pawn 3. OnTriggered if used Subclasses can override this method to control the whole flow @param Avatar The actor on which the behavior should be execute @param Config Configuration parameters of the behavior @param SmartObjectOwner The actor associated to the smart object @return True if behavior was triggered and caller should register to OnBehaviorFinished to be notified on completion
- L61 _public prototype_ `virtual void EndBehavior(AActor& Avatar, const bool bInterrupted = false);`
- L62 _public function_ `void AbortBehavior(AActor& Avatar)`
- L64 _public function_ `FOnGameplayBehaviorFinished& GetOnBehaviorFinishedDelegate()`
- L67 _public prototype_ `virtual TOptional<FVector> GetDynamicLocation(const AActor* InAvatar = nullptr, const UGameplayBehaviorConfig* InConfig = nullptr, const AActor* InSmartObjectOwner = nullptr) const;` — Can return (it's optional) a dynamic location to use this gameplay behavior
- L75 _public function_ `bool IsInstanced(const UGameplayBehaviorConfig* Config) const` — Returns true if this behavior instance is either a non-CDO object or is a CDO, but the class is intended to be used via its instances. If InstantiationPolicy is "ConditionallyInstantiate" then NeedsInstance will be called to see if class wants to spawn an instance depending on @param Config
- L83 _public function_ `void SetRelevantActors(const TArray<AActor*>& InRelevantActors)`
- L84 _public function_ `AActor* GetAvatar() const`
- L87 _public prototype_ `virtual UGameplayTasksComponent* GetGameplayTasksComponent(const UGameplayTask& Task) const override;` — BEGIN IGameplayTaskOwnerInterface
- L88 _public prototype_ `virtual AActor* GetGameplayTaskOwner(const UGameplayTask* Task) const override;`
- L89 _public prototype_ `virtual AActor* GetGameplayTaskAvatar(const UGameplayTask* Task) const override;`
- L90 _public function_ `virtual uint8 GetGameplayTaskDefaultPriority() const override`
- L91 _public prototype_ `virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;`
- L92 _public prototype_ `virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) override;`
- L102 _public prototype_ `void K2_OnTriggered(AActor* Avatar, const UGameplayBehaviorConfig* Config = nullptr, AActor* SmartObjectOwner = nullptr);` — `UFUNCTION(BlueprintImplementableEvent, Category = GameplayBehavior, meta = (AdvancedDisplay="TagPayload", DisplayName="OnTriggered"))`
- L105 _public prototype_ `void K2_OnTriggeredPawn(APawn* Avatar, const UGameplayBehaviorConfig* Config = nullptr, AActor* SmartObjectOwner = nullptr);` — `UFUNCTION(BlueprintImplementableEvent, Category = GameplayBehavior, meta = (AdvancedDisplay = "TagPayload", DisplayName = "OnTriggeredPawn"))`
- L108 _public prototype_ `void K2_OnTriggeredCharacter(ACharacter* Avatar, const UGameplayBehaviorConfig* Config = nullptr, AActor* SmartObjectOwner = nullptr);` — `UFUNCTION(BlueprintImplementableEvent, Category = GameplayBehavior, meta = (AdvancedDisplay = "TagPayload", DisplayName = "OnTriggeredCharacter"))`
- L111 _public prototype_ `void K2_OnFinished(AActor* Avatar, bool bWasInterrupted);` — `UFUNCTION(BlueprintImplementableEvent, Category = GameplayBehavior, meta = (AdvancedDisplay = "TagPayload", DisplayName = "OnFinished"))`
- L114 _public prototype_ `void K2_OnFinishedPawn(APawn* Avatar, bool bWasInterrupted);` — `UFUNCTION(BlueprintImplementableEvent, Category = GameplayBehavior, meta = (AdvancedDisplay = "TagPayload", DisplayName = "OnFinishedPawn"))`
- L117 _public prototype_ `void K2_OnFinishedCharacter(ACharacter* Avatar, bool bWasInterrupted);` — `UFUNCTION(BlueprintImplementableEvent, Category = GameplayBehavior, meta = (AdvancedDisplay = "TagPayload", DisplayName = "OnFinishedCharacter"))`
- L120 _public prototype_ `void K2_EndBehavior(AActor* Avatar);` — `UFUNCTION(BlueprintCallable, Category = GameplayBehavior, meta = (DisplayName = "EndBehavior"))`
- L123 _public prototype_ `void K2_AbortBehavior(AActor* Avatar);` — `UFUNCTION(BlueprintCallable, Category = GameplayBehavior, meta = (DisplayName = "AbortBehavior"))`
- L126 _public prototype_ `void K2_TriggerBehavior(AActor* Avatar, UGameplayBehaviorConfig* Config = nullptr, AActor* SmartObjectOwner = nullptr);` — `UFUNCTION(BlueprintCallable, Category = GameplayBehavior, meta = (DisplayName = "TriggerBehavior"))`
- L130 _public prototype_ `int32 K2_GetNextActorIndexInSequence(int32 CurrentIndex = 0) const;` — `UFUNCTION(BlueprintCallable, Category = GameplayBehavior, meta = (DisplayName = "GetNextActorIndexInSequence"))` — @return None if there's no actors or only the one under the index of CurrentIndex is valid
- L133 _protected function_ `virtual bool NeedsInstance(const UGameplayBehaviorConfig* Config) const`
- L153 _protected member_ `uint32 bTransientIsTriggering : 1;`
- L154 _protected member_ `uint32 bTransientIsActive : 1;`
- L155 _protected member_ `uint32 bTransientIsEnding : 1;`
- L157 _protected member_ `EGameplayBehaviorInstantiationPolicy InstantiationPolicy;`
- L161 _protected member_ `FGameplayTag ActionTag;` — `UPROPERTY(EditDefaultsOnly, Category = GameplayBehavior)` — Tag identifying behavior this class represents
- L164 _protected member_ `FOnGameplayBehaviorFinished OnBehaviorFinished;` — Note that it's not going to be called if the behavior finishes as part of Trigger call
- L171 _protected member_ `TArray<TObjectPtr<AActor>> RelevantActors;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameplayBehavior)` — It's up to the behavior implementation to decide how to use these actors. Can be used as patrol points, investigation location, etc.
- L175 _protected member_ `TObjectPtr<AActor> TransientSmartObjectOwner = nullptr;` — `UPROPERTY(Transient)` — SmartObject Actor Owner, can be null
- L183 _protected member_ `TObjectPtr<AActor> TransientAvatar = nullptr;` — `UPROPERTY()` — Used mostly as world context for IGameplayTaskOwnerInterface function. Use with caution if working with CDOs. Set automatically as part of Trigger call
- L188 _private member_ `TArray<TObjectPtr<UGameplayTask>> ActiveTasks;` — `UPROPERTY()` — List of currently active tasks, do not modify directly

#### union `UGameplayBehavior::(anonymous)`  
``  
_L137-149_

#### struct `UGameplayBehavior::__anon42f0c632010a::(anonymous)`  
``  
_L139-146_

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEPLAYBEHAVIORSMODULE_API`
- L22 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGameplayBehavior, Warning, All);`
- L24 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnGameplayBehaviorFinished, UGameplayBehavior& , AActor& , const bool ) UENUM() enum class EGameplayBehaviorInstantiationPolicy : uint8 { Instantiate, ConditionallyInstantiate, DontInstantiate, };`
- L140 _member_ `uint32 bTriggerGeneric : 1;` (scope `UGameplayBehavior::__anon42f0c632010a::__anon42f0c6320208`)
- L141 _member_ `uint32 bTriggerPawn : 1;` (scope `UGameplayBehavior::__anon42f0c632010a::__anon42f0c6320208`)
- L142 _member_ `uint32 bTriggerCharacter : 1;` (scope `UGameplayBehavior::__anon42f0c632010a::__anon42f0c6320208`)
- L143 _member_ `uint32 bFinishedGeneric : 1;` (scope `UGameplayBehavior::__anon42f0c632010a::__anon42f0c6320208`)
- L144 _member_ `uint32 bFinishedPawn : 1;` (scope `UGameplayBehavior::__anon42f0c632010a::__anon42f0c6320208`)
- L145 _member_ `uint32 bFinishedCharacter : 1;` (scope `UGameplayBehavior::__anon42f0c632010a::__anon42f0c6320208`)
- L148 _member_ `uint32 TransientProps;` (scope `UGameplayBehavior::__anon42f0c632010a`)

### `Plugins/Experimental/GameplayBehaviors/Source/GameplayBehaviorsModule/Public/GameplayBehaviorConfig.h` (Public)


#### class `UGameplayBehaviorConfig`  
`class UGameplayBehaviorConfig : public UObject`  
_L15-27_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType, EditInlineNew, CollapseCategories)`
- inherits: `UObject`
- L22 _public prototype_ `virtual UGameplayBehavior* GetBehavior(UWorld& World) const;` — Depending on the specific UGameplayBehavior class returns an instance or CDO of BehaviorClass.
- L26 _protected member_ `TSubclassOf<UGameplayBehavior> BehaviorClass;` — `UPROPERTY(EditDefaultsOnly, Category = GameplayBehavior)`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GAMEPLAYBEHAVIORSMODULE_API`

### `Plugins/Experimental/GameplayBehaviors/Source/GameplayBehaviorsModule/Public/GameplayBehaviorConfig_Animation.h` (Public)


#### class `UGameplayBehaviorConfig_Animation`  
`class UGameplayBehaviorConfig_Animation : public UGameplayBehaviorConfig`  
_L13-41_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGameplayBehaviorConfig`
- L17 _public prototype_ `UGameplayBehaviorConfig_Animation(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L22 _public function_ `UAnimMontage* GetMontage() const`
- L23 _public function_ `float GetPlayRate() const`
- L24 _public function_ `FName GetStartSectionName() const`
- L25 _public function_ `bool IsLooped() const`
- L31 _protected member_ `mutable TSoftObjectPtr<UAnimMontage> AnimMontage;` — `UPROPERTY(EditAnywhere, Category = SmartObject)` — UPROPERTY(EditDefaultsOnly, Category = GameplayBehavior) TSubclassOf<UGameplayBehavior> BehaviorClass;
- L34 _protected member_ `float PlayRate = 1.f;` — `UPROPERTY(EditAnywhere, Category = SmartObject)`
- L37 _protected member_ `FName StartSectionName;` — `UPROPERTY(EditAnywhere, Category = SmartObject)`
- L40 _protected member_ `uint32 bLoop : 1;` — `UPROPERTY(EditAnywhere, Category = SmartObject)`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEPLAYBEHAVIORSMODULE_API`

### `Plugins/Experimental/GameplayBehaviors/Source/GameplayBehaviorsModule/Public/GameplayBehaviorSubsystem.h` (Public)


#### struct `FAgentGameplayBehaviors`  
`struct FAgentGameplayBehaviors`  
_L19-25_
- reflection: `USTRUCT()`
- L24 _public member_ `TArray<TObjectPtr<UGameplayBehavior>> Behaviors;` — `UPROPERTY()`

#### class `UGameplayBehaviorSubsystem`  
`class UGameplayBehaviorSubsystem : public UWorldSubsystem`  
_L28-44_
- reflection: `UCLASS(MinimalAPI, config = Game, defaultconfig, Transient)`
- inherits: `UWorldSubsystem`
- L32 _public prototype_ `static UGameplayBehaviorSubsystem* GetCurrent(const UWorld* World);`
- L33 _public prototype_ `static bool TriggerBehavior(const UGameplayBehaviorConfig& Config, AActor& Avatar, AActor* SmartObjectOwner = nullptr);`
- L34 _public prototype_ `static bool TriggerBehavior(UGameplayBehavior& Behavior, AActor& Avatar, const UGameplayBehaviorConfig* Config, AActor* SmartObjectOwner = nullptr);`
- L35 _public prototype_ `bool StopBehavior(AActor& Avatar, TSubclassOf<UGameplayBehavior> BehaviorToStop);`
- L38 _protected prototype_ `void OnBehaviorFinished(UGameplayBehavior& Behavior, AActor& Avatar, const bool bInterrupted);`
- L40 _protected prototype_ `virtual bool TriggerBehaviorImpl(UGameplayBehavior& Behavior, AActor& Avatar, const UGameplayBehaviorConfig* Config, AActor* SmartObjectOwner = nullptr);`
- L43 _protected member_ `TMap<TObjectPtr<AActor>, FAgentGameplayBehaviors> AgentGameplayBehaviors;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GAMEPLAYBEHAVIORSMODULE_API`

### `Plugins/Experimental/GameplayBehaviors/Source/GameplayBehaviorsModule/Public/GameplayBehavior_AnimationBased.h` (Public)


#### struct `FMontagePlaybackData`  
`struct FMontagePlaybackData`  
_L18-50_
- reflection: `USTRUCT()`
- L23 _public member_ `TObjectPtr<AActor> Avatar;` — `UPROPERTY()`
- L26 _public member_ `TObjectPtr<UAnimMontage> AnimMontage;` — `UPROPERTY()`
- L29 _public member_ `TObjectPtr<UAbilitySystemComponent> AbilityComponent;` — `UPROPERTY()`
- L31 _public member_ `float PlayRate;`
- L32 _public member_ `FName SectionName;`
- L33 _public member_ `FTimerHandle TimerHandle;`
- L34 _public member_ `FTimerDelegate TimerDelegate;`
- L35 _public member_ `uint8 bLoop : 1;`
- L37 _public function_ `FMontagePlaybackData()`
- L42 _public function_ `FMontagePlaybackData(AActor& InAvatar, UAnimMontage& InAnimMontage, const float InPlayRate = 1.f, const FName InSectionName = NAME_None, const bool bInLoop = false) : Avatar(&InAvatar), AnimMontage(&InAnimMontage) , AbilityComponent(nullptr), PlayRate(InPlayRate) , SectionName(InSectionName), bLoop(bInLoop)`
- L48 _public function_ `bool operator==(const FMontagePlaybackData& Other) const`
- L49 _public function_ `bool operator==(const AActor* InAvatar) const`

#### class `UGameplayBehavior_AnimationBased`  
`class UGameplayBehavior_AnimationBased : public UGameplayBehavior`  
_L58-79_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGameplayBehavior`
- desc: Note that this behavior is supporting playing only a single montage for a given Avatar at a time. Trying to play multiple or using multiple UGameplayBehavior_AnimationBased instances will result in requests overriding and interfering.
- L62 _public prototype_ `UGameplayBehavior_AnimationBased(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L64 _public prototype_ `virtual bool Trigger(AActor& InAvatar, const UGameplayBehaviorConfig* Config = nullptr, AActor* SmartObjectOwner = nullptr) override;`
- L65 _public prototype_ `virtual void EndBehavior(AActor& InAvatar, const bool bInterrupted) override;`
- L67 _public prototype_ `bool PlayMontage(AActor& InAvatar, UAnimMontage& AnimMontage, const float InPlayRate = 1.f, const FName StartSectionName = NAME_None, const bool bLoop = false);`
- L71 _protected prototype_ `void OnMontageFinished(UAnimMontage* Montage, bool bInterrupted, AActor* InAvatar);` — `UFUNCTION()`
- L78 _protected member_ `mutable TArray<FMontagePlaybackData> ActivePlayback;` — `UPROPERTY()` — If this array ever gets more than couple elements at a time we should consider switching over to a TMap

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEPLAYBEHAVIORSMODULE_API`

### `Plugins/Experimental/GameplayBehaviors/Source/GameplayBehaviorsModule/Public/GameplayBehaviorsBlueprintFunctionLibrary.h` (Public)


#### class `UGameplayBehaviorsBlueprintFunctionLibrary`  
`class UGameplayBehaviorsBlueprintFunctionLibrary : public UBlueprintFunctionLibrary`  
_L21-44_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GameplayBehaviorLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- L27 _public prototype_ `static bool StopGameplayBehavior(TSubclassOf<UGameplayBehavior> GameplayBehaviorClass, AActor* Avatar);` — Will force-stop GameplayBehavior on given Avatar assuming the current behavior is of GameplayBehaviorClass class
- L30 _public prototype_ `static FGameplayTagContainer GetBlackboardValueAsGameplayTag(UBTNode* NodeOwner, const FBlackboardKeySelector& Key);` — `UFUNCTION(BlueprintPure, Category = "AI|BehaviorTree", Meta = (HidePin = "NodeOwner", DefaultToSelf = "NodeOwner"))`
- L33 _public prototype_ `static void SetBlackboardValueAsGameplayTag(UBTNode* NodeOwner, const FBlackboardKeySelector& Key, FGameplayTagContainer Value);` — `UFUNCTION(BlueprintCallable, Category = "AI|BehaviorTree", Meta = (HidePin = "NodeOwner", DefaultToSelf = "NodeOwner"))`
- L36 _public prototype_ `static void AddGameplayTagFilterToBlackboardKeySelector(FBlackboardKeySelector& InSelector, UObject* Owner, FName PropertyName);` — `UFUNCTION(BlueprintCallable, Category = "AI|BehaviorTree")`
- L39 _public prototype_ `static FGameplayTagContainer GetBlackboardValueAsGameplayTagFromBlackboardComp(UBlackboardComponent* BlackboardComp, const FName& KeyName);` — `UFUNCTION(BlueprintCallable, Category = "AI|BehaviorTree")`
- L42 _public prototype_ `static void SetValueAsGameplayTagForBlackboardComp(UBlackboardComponent* BlackboardComp, const FName& KeyName, FGameplayTagContainer GameplayTagValue);` — `UFUNCTION(BlueprintCallable, Category = "AI|BehaviorTree")`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GAMEPLAYBEHAVIORSMODULE_API`

### `Plugins/Experimental/GameplayBehaviors/Source/GameplayBehaviorsModule/Public/GameplayBehaviorsModule.h` (Public)


#### class `IGameplayBehaviorsModule`  
`class IGameplayBehaviorsModule : public IModuleInterface`  
_L10-35_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L21 _public function_ `static inline IGameplayBehaviorsModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L31 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
