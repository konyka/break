# Plugins / GameplayBehaviorSmartObjectsModule

- module root: `Plugins/Runtime/GameplayBehaviorSmartObjects/Source/GameplayBehaviorSmartObjectsModule`
- headers: 5; symbols: 58
- symbol kinds: class=5, function=3, macro=4, member=17, prototype=28, struct=1
- PrivateDependencyModuleNames: CoreUObject, Engine
- PublicDependencyModuleNames: AIModule, Core, GameplayBehaviorsModule, GameplayTags, GameplayTasks, SmartObjectsModule

### `Plugins/Runtime/GameplayBehaviorSmartObjects/Source/GameplayBehaviorSmartObjectsModule/Public/AI/AITask_UseGameplayBehaviorSmartObject.h` (Public)


#### class `UAITask_UseGameplayBehaviorSmartObject`  
`class UAITask_UseGameplayBehaviorSmartObject : public UAITask`  
_L18-92_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAITask`
- L23 _public prototype_ `UAITask_UseGameplayBehaviorSmartObject(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L34 _public prototype_ `static UAITask_UseGameplayBehaviorSmartObject* UseSmartObjectWithGameplayBehavior(AAIController* Controller, FSmartObjectClaimHandle ClaimHandle, bool bLockAILogic = true, ESmartObjectClaimPriority ClaimPriority = ESmartObjectClaimPriority::Normal);` — `UFUNCTION(BlueprintCallable, Category = "AI|Tasks", meta = (DefaultToSelf = "Controller" , BlueprintInternalUseOnly = "true"))` — Helper function to create an AITask that interacts with the SmartObject slot using the GameplayBehavior definition This version starts the interaction on spot so the actor needs to be at the desired position. @param Controller The controller for which the attached pawn will take part to the GameplayBehavior. @param ClaimHandle The handle to an already claimed slot. @param bLockAILogic Indicates if the task adds UAIResource_Logic to the set of Claimed resources @return The AITask executing the GameplayBehavior.
- L44 _public prototype_ `static UAITask_UseGameplayBehaviorSmartObject* MoveToAndUseSmartObjectWithGameplayBehavior(AAIController* Controller, FSmartObjectClaimHandle ClaimHandle, bool bLockAILogic = true, ESmartObjectClaimPriority ClaimPriority = ESmartObjectClaimPriority::Normal);` — `UFUNCTION(BlueprintCallable, Category = "AI|Tasks", meta = (DefaultToSelf = "Controller" , BlueprintInternalUseOnly = "true"))` — Helper function to create an AITask that reaches and interacts with the SmartObject slot using the GameplayBehavior definition. @param Controller The controller that will move to the slot location and for which the attached pawn will take part to the GameplayBehavior. @param ClaimHandle The handle to an already claimed slot. @param bLockAILogic Indicates if the task adds UAIResource_Logic to the set of Claimed resources @return The AITask performing the move to slot location and then executing the GameplayBehavior.
- L48 _public prototype_ `static UAITask_UseGameplayBehaviorSmartObject* UseGameplayBehaviorSmartObject(AAIController* Controller, AActor* SmartObjectActor, USmartObjectComponent* SmartObjectComponent, bool bLockAILogic = true);` — `UE_DEPRECATED(5.3, "Please use one of the UseSmartObjectWithGameplayBehavior functions using claim handle instead")` — `UFUNCTION(BlueprintCallable, Category = "AI|Tasks", meta = (DefaultToSelf = "Controller" , BlueprintInternalUseOnly = "true"), meta = (DeprecatedFunction, DeprecationMessage = "Use one of the UseSmartObjectWithGameplayBehavior functions using claim handle instead"))`
- L50 _public function_ `void SetShouldReachSlotLocation(const bool bUseMoveTo)`
- L51 _public function_ `void SetClaimHandle(const FSmartObjectClaimHandle& Handle)`
- L54 _protected prototype_ `virtual void Activate() override;`
- L55 _protected prototype_ `virtual void TickTask(float DeltaTime) override;`
- L56 _protected prototype_ `virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) override;`
- L57 _protected prototype_ `virtual void OnDestroy(bool bInOwnerFinished) override;`
- L59 _protected prototype_ `bool StartInteraction();`
- L61 _protected prototype_ `void Abort();`
- L63 _protected prototype_ `void OnSmartObjectBehaviorFinished(UGameplayBehavior& Behavior, AActor& Avatar, const bool bInterrupted);`
- L65 _protected prototype_ `void OnSlotInvalidated(const FSmartObjectClaimHandle& ClaimHandle, const ESmartObjectSlotState State);`
- L67 _protected prototype_ `static UAITask_UseGameplayBehaviorSmartObject* UseSmartObjectComponent(AAIController& Controller, const USmartObjectComponent& SmartObjectComponent, bool bLockAILogic, ESmartObjectClaimPriority ClaimPriority = ESmartObjectClaimPriority::Normal);`
- L68 _protected prototype_ `static UAITask_UseGameplayBehaviorSmartObject* UseClaimedSmartObject(AAIController& Controller, FSmartObjectClaimHandle ClaimHandle, bool bLockAILogic);`
- L72 _protected member_ `FGenericGameplayTaskDelegate OnSucceeded;` — `UPROPERTY(BlueprintAssignable)`
- L75 _protected member_ `FGenericGameplayTaskDelegate OnFailed;` — `UPROPERTY(BlueprintAssignable)`
- L78 _protected member_ `FGenericGameplayTaskDelegate OnMoveToFailed;` — `UPROPERTY(BlueprintAssignable)`
- L81 _protected member_ `TObjectPtr<UAITask_MoveTo> MoveToTask;` — `UPROPERTY()`
- L84 _protected member_ `TObjectPtr<UGameplayBehavior> GameplayBehavior;` — `UPROPERTY()`
- L86 _protected member_ `FSmartObjectClaimHandle ClaimedHandle;`
- L87 _protected member_ `FDelegateHandle OnBehaviorFinishedNotifyHandle;`
- L89 _protected member_ `bool bBehaviorFinished;`
- L91 _protected member_ `bool bShouldUseMoveTo;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEPLAYBEHAVIORSMARTOBJECTSMODULE_API`

### `Plugins/Runtime/GameplayBehaviorSmartObjects/Source/GameplayBehaviorSmartObjectsModule/Public/AI/BTTask_FindAndUseGameplayBehaviorSmartObject.h` (Public)


#### struct `FBTUseSOTaskMemory`  
`struct FBTUseSOTaskMemory`  
_L16-20_
- L18 _public member_ `TWeakObjectPtr<UAITask_UseGameplayBehaviorSmartObject> TaskInstance;`
- L19 _public member_ `int32 EQSRequestID;`

#### class `UBTTask_FindAndUseGameplayBehaviorSmartObject`  
`class UBTTask_FindAndUseGameplayBehaviorSmartObject : public UBTTaskNode`  
_L26-66_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBTTaskNode`
- L30 _public prototype_ `UBTTask_FindAndUseGameplayBehaviorSmartObject();`
- L33 _protected prototype_ `virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L34 _protected prototype_ `virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L35 _protected prototype_ `virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;`
- L36 _protected function_ `virtual uint16 GetInstanceMemorySize() const override`
- L37 _protected prototype_ `virtual void InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const override;`
- L38 _protected prototype_ `virtual void CleanupMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryClear::Type CleanupType) const override;`
- L40 _protected prototype_ `virtual FString GetStaticDescription() const override;`
- L42 _protected prototype_ `virtual void InitializeFromAsset(UBehaviorTree& Asset) override;`
- L44 _protected prototype_ `void OnQueryFinished(TSharedPtr<FEnvQueryResult> Result);`
- L46 _protected prototype_ `void UseClaimedSmartObject(UBehaviorTreeComponent& OwnerComp, FSmartObjectClaimHandle ClaimHandle, FBTUseSOTaskMemory& MyMemory);`
- L53 _protected member_ `FGameplayTagQuery ActivityRequirements;` — `UPROPERTY(EditAnywhere, Category = SmartObjects)` — Additional tag query to filter available smart objects. We'll query for smart objects that support activities tagged in a way matching the filter. Note that regular tag-base filtering is going to take place as well
- L56 _protected member_ `ESmartObjectClaimPriority ClaimPriority = ESmartObjectClaimPriority::Normal;` — `UPROPERTY(EditAnywhere, Category = SmartObjects)`
- L59 _protected member_ `FEQSParametrizedQueryExecutionRequest EQSRequest;` — `UPROPERTY(EditAnywhere, Category = SmartObjects)`
- L63 _protected member_ `float Radius;` — `UPROPERTY(EditAnywhere, Category = SmartObjects, meta=(DisplayName="Fallback Radius"))` — Used for smart object querying if EQSRequest is not configured
- L65 _protected member_ `FQueryFinishedSignature EQSQueryFinishedDelegate;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GAMEPLAYBEHAVIORSMARTOBJECTSMODULE_API`

### `Plugins/Runtime/GameplayBehaviorSmartObjects/Source/GameplayBehaviorSmartObjectsModule/Public/GameplayBehaviorSmartObjectBehaviorDefinition.h` (Public)


#### class `UGameplayBehaviorSmartObjectBehaviorDefinition`  
`class UGameplayBehaviorSmartObjectBehaviorDefinition : public USmartObjectBehaviorDefinition`  
_L16-29_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USmartObjectBehaviorDefinition`
- desc: SmartObject behavior definition for the GameplayBehavior framework
- L22 _public member_ `TObjectPtr<UGameplayBehaviorConfig> GameplayBehaviorConfig;` — `UPROPERTY(EditDefaultsOnly, Category = SmartObject, Instanced)`
- L27 _public prototype_ `virtual void GetPreloadDependencies(TArray<UObject*>& OutDeps) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GAMEPLAYBEHAVIORSMARTOBJECTSMODULE_API`

### `Plugins/Runtime/GameplayBehaviorSmartObjects/Source/GameplayBehaviorSmartObjectsModule/Public/GameplayBehaviorSmartObjectsBlueprintFunctionLibrary.h` (Public)


#### class `UGameplayBehaviorSmartObjectsBlueprintFunctionLibrary`  
`class UGameplayBehaviorSmartObjectsBlueprintFunctionLibrary : public UBlueprintFunctionLibrary`  
_L13-20_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GameplayBehaviorsLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- L19 _public prototype_ `static bool UseGameplayBehaviorSmartObject(AActor* Avatar, AActor* SmartObject);` — `UE_DEPRECATED(5.3, "Use MoveToAndUseSmartObjectWithGameplayBehavior or UseSmartObjectWithGameplayBehavior using a claim handle from UAITask_UseGameplayBehaviorSmartObject instead.")` — `UFUNCTION(BlueprintCallable, Category = "SmartObject", meta = (DeprecatedFunction, DeprecationMessage = "Use MoveToAndUseSmartObjectWithGameplayBehavior or UseSmartObjectWithGameplayBehavior using a claim handle from UAITask_UseGameplayBehaviorSmartObject instead."))`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GAMEPLAYBEHAVIORSMARTOBJECTSMODULE_API`

### `Plugins/Runtime/GameplayBehaviorSmartObjects/Source/GameplayBehaviorSmartObjectsModule/Public/GameplayBehaviorSmartObjectsModule.h` (Public)


#### class `IGameplayBehaviorSmartObjectsModule`  
`class IGameplayBehaviorSmartObjectsModule : public IModuleInterface`  
_L10-29_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L21 _public prototype_ `static IGameplayBehaviorSmartObjectsModule& Get();` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L28 _public prototype_ `static bool IsAvailable();` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
